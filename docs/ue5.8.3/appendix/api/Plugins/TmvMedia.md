# Plugins / TmvMedia

- module root: `Plugins/Media/TmvMedia/Source/TmvMedia`
- headers: 62; symbols: 1287
- symbol kinds: class=51, delegate=11, enum=27, enumerator=94, function=147, macro=28, member=401, namespace=36, prototype=432, struct=58, typedef=2
- PrivateDependencyModuleNames: CQTest, D3D12RHI, ImageCore, ImageWrapper, Json, JsonUtilities, MediaAssets, MediaUtils, Projects, RenderCore, Renderer
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Media, RHI, TmvMediaShaders

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/SampleConverter/SparseOutputMip/TmvSparseOutputManager.h` (Internal)


#### struct `FTmvSparseOutputFrameRequest`  
`struct FTmvSparseOutputFrameRequest`  
_L24-37_
- desc: Per-clip request describing the smallest sparse-mip index the converter intends to write/sample this frame. Derived from the minimum key in FTmvMediaTextureSampleConverterParameters::Viewports at converter entry.
- L27 _public member_ `FRHITexture* Texture = nullptr;` — The output media texture this request applies to.
- L36 _public member_ `int32 TargetFloor = 0;` — Smallest mip index the converter is about to write this frame. The manager commits all sparse-eligible mips in [TargetFloor, MaxSparse] that are not yet committed. Mips below TargetFloor are left committed (no timer ever decommits); physical memory is released only when the texture unregisters - see the class header.

#### class `FTmvSparseOutputManager`  
`class FTmvSparseOutputManager`  
_L71-154_
- desc: Platform-agnostic owner of sparse-output residency state. Holds per-texture sparse-eligibility bitsets, LRU clip ordering, and the published ResidentFloor the converter uses to skip below-floor write passes. Physical commit/steal on the GPU is delegated to a platform-specific FTmvSparseOutputBackend (demand-driven chunk pool; see backend docs). Read-side safety: the sparse path only activates for textures created as D3D12 reserved resources, which the RHI enables only on Tiled Resources Tier 2+ (see GRHIGlobals.ReservedResources.Supported). On that hardware, sampling a non-resident (unmapped) tile returns 0 rather than faulting, so a material that samples below the current ResidentFloor during a transient commit/camera mismatch reads black for a frame instead of crashing. An explicit read-side MostDetailedMip clamp on the sampling SRV would turn that black into the next-coarser resident mip; it is a deferred quality enhancement, NOT a crash-safety requirement. Lifecycle: RequestFloor commits everything in [TargetFloor, MaxSparse] that isn't already mapped. The backend may steal from another texture to satisfy a commit - when it does, the manager raises the prior owner's ResidentFloor and the swizzler's below-floor write skip picks up the new floor on the next pass. No timer ever decommits. Physical memory is released only when an FRHITexture unregisters explicitly (called from process drain at OnEnginePreExit); there is no in-session GC tick, because FMediaTextureResource may
- L75 _public prototype_ `static FTmvSparseOutputManager& Get();` — Process-wide singleton. Lazily constructs on first access.
- L78 _public function_ `bool IsEnabled() const` — Returns true iff the manager resolved a backend for the running RHI at startup.
- L86 _public prototype_ `bool RegisterOutput(FRHITexture* Texture, const FTmvSparseOutputLayout& Layout);` — Per-resource setup. Forwards to the backend for tile-count query and always-resident pre-commit; tracks the texture in the LRU and the total-committed-bytes accounting. Returns false on any backend failure; caller should treat the texture as non-sparse in that case.
- L89 _public prototype_ `void UnregisterOutput(FRHITexture* Texture);` — Per-resource teardown. Forwards to the backend, drops LRU entry.
- L103 _public prototype_ `void RequestFloor(const FTmvSparseOutputFrameRequest& Request);` — Converter entry point. Eager-commits sparse mips at or above TargetFloor; publishes the new resident_floor so the swizzler skips write passes for non-resident mips (read-side safety comes from the Tier-2 reserved-resource read-zero guarantee - see the class header). If a commit steals from another texture (oldest-LRU chunk past hysteresis), the manager raises that texture's ResidentFloor in the same call. Pool growth is gated by the configured budget; if the cap is hit, the backend force-steals the oldest chunk regardless of hysteresis. No timer ever decommits.
- L111 _public prototype_ `void RequestFullResidency(FRHITexture* Texture);` — Pin all sparse mips committed for a specific texture, ignoring the camera-derived floor for the duration of a render pass. Used by MRQ / capture passes that sample mip 0 outside the player camera prediction. Released by the matching ReleaseFullResidency call.
- L112 _public prototype_ `void ReleaseFullResidency(FRHITexture* Texture);`
- L121 _public prototype_ `int32 GetResidentFloor(FRHITexture* Texture) const;` — Smallest mip index currently backed by physical memory for this texture. The swizzler uses this to skip below-floor write passes; a read-side MostDetailedMip clamp on the sampling SRV is optional (see the class header - Tier-2 read-zero makes below-floor sampling safe). Takes the manager lock for the duration of the read.
- L124 _public prototype_ `void Dump(FOutputDevice& Ar) const;` — Backend for tmvmedia.dumpmipbuffers - emits per-texture, per-mip committed-byte rows.
- L127 _private prototype_ `FTmvSparseOutputManager();`
- L128 _private prototype_ `~FTmvSparseOutputManager();`
- L130 _private prototype_ `FTmvSparseOutputManager(const FTmvSparseOutputManager&) = delete;`
- L131 _private prototype_ `FTmvSparseOutputManager& operator=(const FTmvSparseOutputManager&) = delete;`
- L142 _private prototype_ `void DrainAll_NoLock();`
- L144 _private prototype_ `void HandleMediaTextureReleased(FRHITexture* Texture);`
- L147 _private member_ `mutable FCriticalSection Lock;` — Backend ownership and per-texture state are guarded by Lock.
- L148 _private member_ `TSharedPtr<FTmvSparseOutputBackend, ESPMode::ThreadSafe> Backend;`
- L149 _private member_ `TMap<FRHITexture*, FTextureState> States;`
- L150 _private member_ `TArray<FRHITexture*> Lru;` — most-recently-requested at end
- L152 _private member_ `FDelegateHandle OnEnginePreExitHandle;`
- L153 _private member_ `FDelegateHandle OnMediaTextureReleasedHandle;`

#### struct `FTmvSparseOutputManager::FTextureState`  
`struct FTextureState`  
_L133-140_
- L135 _public member_ `int32 NumMips = 0;`
- L136 _public member_ `int32 MaxSparseMipIndex = -1;`
- L137 _public member_ `int32 ResidentFloor = MAX_int32;` — smallest committed sparse mip index
- L138 _public member_ `int32 FullResidencyRefCount = 0;`
- L139 _public member_ `TBitArray<> SparseEligible;` — size NumMips

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/SampleConverter/TmvMediaFrameMipBuffer.h` (Internal)


#### class `FTmvMediaFrameMipBuffer`  
`class FTmvMediaFrameMipBuffer : public TSharedFromThis<FTmvMediaFrameMipBuffer>`  
_L27-274_
- inherits: `TSharedFromThis<FTmvMediaFrameMipBuffer>`
- desc: Abstract based class for a Tmv Frame mip buffer. A mip buffer for a Tmv frame supports partial updates by a decoder that will write some tiles on the cpu buffer. Then the modified regions of the buffer will be uploaded to the gpu to be used by the Tmv Sample converter shaders to also partially update the final converted texture. The memory storage and gpu buffer implementations are abstracted to be able to support different layouts (i.e. tiled vs scanline) depending on the decoder needs.
- L31 _public prototype_ `FTmvMediaFrameMipBuffer() = default;` — Constructor
- L34 _public prototype_ `virtual ~FTmvMediaFrameMipBuffer() = default;` — Destructor to clean up render resources
- L37 _public function_ `SIZE_T GetAllocatedBufferSize() const` — Returns the total allocation size in bytes.
- L43 _public function_ `const FTmvMediaFrameMipInfo& GetMipInfoRef() const` — Returns the descriptor of the memory layout and color format.
- L56 _public prototype_ `virtual bool RequestAllocation(const FTmvMediaFrameMipInfo& InMipInfo) = 0;` — Requests an allocation of the buffer suitable for the given mip descriptor. If the allocation is performed on the render thread, the Mapped buffer is not available immediately. To ensure the allocation is available, call WaitAllocation. @param InMipInfo Descriptor for the allocation. @return true if the allocation is valid, false otherwise.
- L62 _public prototype_ `virtual void WaitAllocation() = 0;` — If the allocation is done on the render thread, wait for it to be completed. Should we do this internally in the buffer accessor instead? (probably)
- L73 _public prototype_ `virtual bool TryUpdateMipInfo(const FTmvMediaFrameMipInfo& InMipInfo) = 0;` — Determines from the given allocation descriptor if the current buffer can be used, if it can, update it. This is used when recycling buffers from the pool to make sure the buffer is compatible with the requested memory layout. @param InMipInfo Descriptor for the allocation. @return true if the buffer can be used for the given allocation.
- L76 _public prototype_ `virtual void* GetMappedBuffer() = 0;` — Access the full mapped buffer. Only available for structured buffer.
- L84 _public prototype_ `virtual void* GetPlaneBufferForComponent(int32 InComponentIndex) = 0;` — Returns the start address of the memory plane buffer that contains the given component. @remark In the case of interleaved components in a memory plane, an additional offset provided by GetStartComponentOffsetInBytes(), must be applied to the returned value to get the start of the component within the plane buffer.
- L92 _public prototype_ `virtual FShaderResourceViewRHIRef GetShaderResourceView(int32 InComponentIndex) const = 0;` — Returns the shader resource view that contains the given component. @remark A single shader resource can have multiple components (either packed or interleaved). @param InComponentIndex Index of the component to retrieve. @return Shader resource view of the plane that has this component.
- L107 _public prototype_ `virtual void CopyTileRegions(int32 InFrameId, const FTmvMediaFrameMipInfo& InTmvMipInfo, TConstArrayView<FIntRect> InTileRegions, TConstArrayView<FTmvMediaShaderTileDesc> InTileInfos) = 0;` — Enqueues the render commands to update the buffer regions corresponding to the specified set of tile regions. @remark Expected to be called from the decoder/reader worker thread. @param InFrameId Id of the current frame being updated. Used for stats and debugging. @param InTmvMipInfo Current frame mip info. @param InTileRegions Tile regions (specified in tile coordinates) to update. @param InTileInfos Lookup table for tile buffer memory layout. This maps tile coordinates with buffer offsets. Shared-pool buffers consult their own member-captured upload/shader-access refs (snapshotted by the decoder via CaptureWriteState() under the pool read lock). No captured refs travel through this signature.
- L121 _public function_ `virtual void CaptureWriteState()` — Snapshot the buffer's current pool-side GPU resources for the imminent decode + render-thread CopyTileRegions pair. Called by the decoder once per buffer after it has acquired the pool read lock(s) but before any tile bytes are written. Default no-op; FTmvMediaFrameMipStructuredBuffer (shared mode) overrides to capture its SharedPool->GetUploadBuffer() / GetShaderAccessBuffer() into private members. The captures stay valid until the following CopyTileRegions consumes them; CopyTileRegions clears them at end of call so a stale capture is never reused across frames.
- L124 _public prototype_ `virtual bool IsValidForRendering() const = 0;` — Returns true if the buffer can be used for rendering.
- L127 _public function_ `virtual bool IsStructuredBuffer() const` — Returns true if the buffer is implemented as a structured buffer.
- L144 _public function_ `virtual bool EnsureCapacityFor(int32 InMinCapacity)` — Grow the underlying GPU storage so it can hold at least InMinCapacity tile slots, expanding the residency map in lockstep. No-op (returns true) if Residency.Capacity is already >= InMinCapacity. Returns false if the buffer either doesn't support growth (non-virtualized, or non-structured variant) or can't grow further (already at the GetMaxGrowSlotCount cap). Synchronously reallocates the RHI buffer and GPU-copies existing slot contents to the new allocation, so on return the buffer can be addressed via the same slot indices it previously held. Caller is responsible for holding the buffer alive (via its FTmvMediaFrameMipBufferHandle).
- L159 _public function_ `virtual FTmvMediaTileResidency* GetResidency()` — Tile residency map for virtualized buffers, or nullptr for buffer variants that don't virtualize (the scanline texture/memory/image buffers). Only FTmvMediaFrameMipStructuredBuffer owns one; keeping the data off this base avoids the dead Capacity==0 member every other variant used to inherit. The decoder/pool/converter reach a buffer's residency polymorphically through this accessor.
- L160 _public function_ `virtual const FTmvMediaTileResidency* GetResidency() const`
- L174 _public prototype_ `bool IsAllocatedVirtualized() const;` — True when this buffer was allocated with a virtualized (budgeted) residency. This is the latched allocation-time decision: RequestAllocation initializes the residency to a positive capacity (or shared-pool mode) only for virtualized mips, and TryUpdateMipInfo keeps it in sync on pool reuse. Consumers downstream of allocation (the reader's slot assignment and the post-decode descriptor rebuild) MUST read this rather than FTmvMediaFrameMipInfo::IsVirtualized(), which re-reads the live CVars on every call - a mid-clip toggle would otherwise make those consumers disagree with how the buffer was actually sized.
- L189 _public function_ `void ResetUploadTracking()` — Reset on pool acquire/reuse so the gate starts clean for the new owner.
- L203 _public function_ `uint64 BeginUpload()` — Decode/worker thread: call once per upload, BEFORE enqueuing the GPU copy. Returns the sequence to hand to RecordUploadExecuted from the copy command.
- L209 _public function_ `void RecordUploadExecuted(uint64 InSeq)` — Render thread: the GPU copy for sequence InSeq has been recorded.
- L227 _public function_ `bool IsUploadPending() const` — Render gate. True when an upload has been enqueued (BeginUpload) whose GPU copy has not yet been recorded on the render thread - i.e. the converter is about to sample this buffer before its newest decoded tiles have landed. The converter skips/falls back for such a mip (keep-last or coarse-current) instead of sampling not-yet-uploaded slots. Unlike a frame-id-keyed gate this stays correct under paused-refresh (same media frame, many refreshes).
- L241 _public function_ `void SetPendingDecodeRouting(TArray<FIntPoint>&& InTileCoords, TArray<int32>&& InTileDstSlots)` — Reader: publish this frame's explicit (tile coord, dst slot) decode list.
- L248 _public function_ `const TArray<FIntPoint>& GetPendingDecodeTileCoords() const` — Decoder: parallel tile-coord / dst-slot arrays for virtualized routing (empty = legacy TileRegions path).
- L249 _public function_ `const TArray<int32>& GetPendingDecodeTileDstSlots() const`
- L252 _public function_ `void SetPendingDecodeOverflowCount(int32 InCount)` — Reader: count of visible tiles that overflowed (no slot) this frame, for the overflow hysteresis.
- L253 _public function_ `int32 GetPendingDecodeOverflowCount() const`
- L257 _protected member_ `SIZE_T AllocatedBufferSize = 0;` — Allocated buffer size, used for debugging.
- L260 _protected member_ `FTmvMediaFrameMipInfo MipInfo;` — Memory frame info this buffer was allocated with.
- L265 _protected member_ `uint64 UploadEnqueuedSeq = 0;` — Render-gate upload tracking (see BeginUpload / RecordUploadExecuted / IsUploadPending). Monotonic; EnqueuedSeq written on the worker in CopyTileRegions, RecordedSeq written on the render thread in the copy command.
- L266 _protected member_ `uint64 UploadRecordedSeq = 0;`
- L271 _protected member_ `TArray<FIntPoint> PendingDecodeTileCoords;` — Virtualized decode routing (see SetPendingDecodeRouting / GetPendingDecode*). Set by the reader, read by the decoder via the request's MipBuffer handle; held here so FTmvMediaDecoderMipRequest's public layout stays ABI-frozen.
- L272 _protected member_ `TArray<int32> PendingDecodeTileDstSlots;`
- L273 _protected member_ `int32 PendingDecodeOverflowCount = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/SampleConverter/TmvMediaFrameMipImageBuffer.h` (Internal)


#### class `FTmvMediaFrameMipImageBuffer`  
`class FTmvMediaFrameMipImageBuffer : public FTmvMediaFrameMipBuffer`  
_L18-47_
- inherits: `FTmvMediaFrameMipBuffer`
- desc: Implementation of texture cpu buffering backed by FImage. If we needed to upload that to rhi textures, we could have a version inheriting from FTmvMediaFrameMipTextureBuffer where the FImage is the "plane buffer". Note: FImage doesn't support R8 nor R16, severely limiting the usefulness for plane formats.
- L22 _public prototype_ `FTmvMediaFrameMipImageBuffer();` — Constructor
- L25 _public prototype_ `FTmvMediaFrameMipImageBuffer(const TSharedPtr<FImage>& InImage, int32 InMipLevel);` — Construct from an existing image, using the image as backing buffer.
- L31 _public prototype_ `virtual bool RequestAllocation(const FTmvMediaFrameMipInfo& InMipInfo) override;`
- L32 _public function_ `virtual void WaitAllocation() override`
- L33 _public function_ `virtual bool TryUpdateMipInfo(const FTmvMediaFrameMipInfo& InMipInfo) override`
- L34 _public prototype_ `virtual void* GetMappedBuffer() override;`
- L35 _public prototype_ `virtual void* GetPlaneBufferForComponent(int32 InComponentIndex) override;`
- L36 _public prototype_ `virtual FShaderResourceViewRHIRef GetShaderResourceView(int32 InComponentIndex) const override;`
- L37 _public function_ `virtual void CopyTileRegions(int32 InFrameId, const FTmvMediaFrameMipInfo& InTmvMipInfo, TConstArrayView<FIntRect> InTileRegions, TConstArrayView<FTmvMediaShaderTileDesc> InTileInfos) override`
- L38 _public function_ `virtual bool IsValidForRendering() const override`
- L46 _private member_ `TArray<TSharedPtr<FImage>> PlaneImages;` — Image buffer for each plane.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/SampleConverter/TmvMediaTextureSampleConverter.h` (Internal)


#### struct `FTmvMediaTextureSampleConverterParameters`  
`struct FTmvMediaTextureSampleConverterParameters`  
_L17-54_
- desc: Tmv Sample conversion parameters.
- L20 _public member_ `bool bHasTiles = false;` — Does this frame has tiles?
- L23 _public member_ `int32 FrameId = 0;` — Frame Id.
- L26 _public member_ `FIntPoint FullResolution = FIntPoint(0, 0);` — Resolution of the highest quality mip.
- L29 _public member_ `FIntPoint TileDimWithBorders = FIntPoint(0, 0);` — Dimension of the tile including the overscan borders.
- L32 _public member_ `TSortedMap<int32, TArray<FIntRect>> Viewports;` — Used for rendering tiles in bulk regions per mip level.
- L41 _public member_ `TSortedMap<int32, TArray<FIntRect>> FullVisibleViewports;` — Per mip level, the FULL visible region for this frame (intended coverage), regardless of how much has actually been decoded into Viewports yet. The coarse-current fallback (r.TmvMedia.CoarseCurrentFallback) compares this to Viewports to detect an under-decoded mip and fill only that case from a coarser ready mip - so good (fully decoded) frames pay nothing.
- L47 _public member_ `TArray<TArray<FTmvMediaShaderTileDesc>> TileInfoPerMipLevel;` — Contain information about individual tiles. Used to convert buffer data into a 2D Texture. The size of this array is the exact number of complete and partial tiles for each mip level.
- L50 _public member_ `int32 UpscaleMip = -1;` — A lower quality mip will be upscaled if value is 0 or above. At 0 highest quality mip will always be read fully.
- L53 _public member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> SourceColorSettings;` — Manual source color space & encoding overrides.

#### class `FTmvMediaTextureSampleConverter`  
`class FTmvMediaTextureSampleConverter : public IMediaTextureSampleConverter`  
_L65-140_
- inherits: `IMediaTextureSampleConverter`
- desc: Implementation of a sample converter for Tmv Frames. It supports: - Converting planar formats (i.e. components separated in memory planes) with either tiled or scanline memory layouts. - Partial and incremental updates of the buffer regions. - YUV color model - Debugging features like mip tinting.
- L74 _public prototype_ `FTmvMediaTextureSampleConverter();`
- L78 _public prototype_ `virtual bool Convert(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, const FConversionHints& Hints) override;`
- L82 _public prototype_ `bool HasMipLevelBuffer(int32 RequestedMipLevel) const;` — Returns true if the given mip level already has a cached mip buffer in the converter.
- L85 _public prototype_ `FTmvMediaFrameMipBufferHandle GetOrCreateMipLevelBuffer(int32 RequestedMipLevel, TFunction<FTmvMediaFrameMipBufferHandle()> AllocatorFunc);` — A Mip Buffer for the given mip level will either be acquired from the internal cache if available or created using the provided function if not.
- L100 _public prototype_ `void ClearInactiveOwnerVisibility(const TSet<int32>& InActiveMipLevels);` — Publish empty owner-visibility on the shared tile pool for every cached mip buffer not in the active set this frame. Without this, a mip the plate stopped using (e.g. mip 1+2 when it zooms out to mip 4+5) keeps its old `VisibleTiles` snapshot in that pool - those slots stay non-evictable, other plates can't reuse them, and the pool grows past the actual concurrent demand. This is the root of the "we're allocating much more than visible tiles need" behavior. Call this in the reader, just before iterating MipTilesCopy. The iteration will re-set the visibility for active mips; this clears stale visibility for the rest in one pass.
- L103 _public function_ `FTmvMediaTextureSampleConverterParameters GetParams_ThreadSafe()` — Safely get a copy of the converter parameters.
- L110 _public function_ `void SetParams_ThreadSafe(const FTmvMediaTextureSampleConverterParameters& InParams)` — Safely set the converter parameters.
- L118 _private member_ `mutable FCriticalSection ParamsCriticalSection;` — These are all required parameters to convert the buffer into texture successfully.
- L119 _private member_ `FTmvMediaTextureSampleConverterParameters ConverterParams;`
- L122 _private member_ `mutable FCriticalSection MipBufferCriticalSection;` — Lock to be used exclusively on reader threads.
- L125 _private member_ `TMap<int32,FTmvMediaFrameMipBufferHandle> MipBuffers;` — Cached mip buffers that will be used in the render thread for updating the final texture.
- L139 _private member_ `TUniquePtr<FTileDescGpuCache> TileDescGpuCache;` — Per-mip GPU cache of the tile-descriptor structured buffer + SRV used by the conversion shader to look up tile locations within the mip's data buffer. Without this, RenderMip_StructuredBuffer creates a fresh FRHIBuffer + SRV every visible mip every frame, even when the tile-descriptor set is unchanged. The resulting per-frame churn fills the RHI deferred-delete queue during mip transitions on zoom and triggers FlushPendingDeleteRHIResources_NonRealtime stalls on the render thread. PIMPL'd to keep FBufferRHIRef / FShaderResourceViewRHIRef out of any consumer of this header. Only accessed from the render thread (inside Convert()), so no locking required.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/SampleConverter/TmvMediaTileResidency.h` (Internal)


#### struct `FTmvMediaTileResidency`  
`struct FTmvMediaTileResidency`  
_L27-167_
- desc: Logical-to-physical tile mapping for a virtualized mip buffer. When mip-buffer virtualization is enabled (r.TmvMedia.VirtualizeMipBuffers), the underlying GPU buffer holds a bounded number of physical tile slots instead of one slot per worst-case tile. This struct tracks which logical tile coordinate (X, Y) occupies which physical slot, plus an LRU ordering so newly-visible tiles can evict the oldest non-visible slot. Lifetime: persists across game-frame renders of the SAME TMV frame, so incremental decode keeps working (only newly-visible tiles re-decode). Reset on pool reuse (different TMV frame / potentially different clip).
- L30 _public function_ `static FIntPoint InvalidTile()` — Sentinel for "no tile here" in SlotToTile.
- L32 _public member_ `int32 Capacity = 0;`
- L35 _public member_ `TArray<FIntPoint> SlotToTile;` — Slot index -> logical tile, or InvalidTile() if empty. Size == Capacity. (local mode only)
- L38 _public member_ `TMap<FIntPoint, int32> TileToSlot;` — Logical tile -> slot index. Contains currently-known tiles for this buffer.
- L41 _public member_ `TArray<int32> LruOrder;` — Slot LRU ordering (local mode only).
- L49 _public member_ `TSharedPtr<FTmvSharedTilePool, ESPMode::ThreadSafe> SharedPool;` — Shared-pool mode: when SharedPool is set, slot allocation routes through the pool and TileToSlot is a per-frame mirror of the pool's view for this owner. SlotToTile / LruOrder are unused; the pool manages those globally.
- L50 _public member_ `FTmvSharedTilePool::FOwnerHandle SharedOwner;`
- L52 _public function_ `bool IsShared() const`
- L55 _public function_ `void Initialize(int32 InCapacity)` — Local-mode init: sets capacity and resets to all-empty.
- L68 _public function_ `void InitializeShared(const TSharedPtr<FTmvSharedTilePool, ESPMode::ThreadSafe>& InPool, FTmvSharedTilePool::FOwnerHandle InOwner)` — Switch to shared-pool mode. The buffer must already be registered with the pool.
- L79 _public function_ `void Reset()` — Clear residency without resizing slots. Called when a pooled buffer is reused.
- L95 _public function_ `int32 GetSlot(FIntPoint InTile) const`
- L108 _public function_ `bool IsResident(FIntPoint InTile) const`
- L117 _public function_ `int32 AllocateSlot(FIntPoint InTile, const TSet<FIntPoint>& InVisibleSet)`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/SampleConverter/TmvSharedTilePool.h` (Internal)


#### class `FTmvSharedTilePool`  
`class FTmvSharedTilePool : public TSharedFromThis<FTmvSharedTilePool, ESPMode::ThreadSafe>`  
_L50-353_
- inherits: `TSharedFromThis<FTmvSharedTilePool,ESPMode::ThreadSafe>`
- desc: Global shared tile pool for virtualized mip buffers. One FTmvSharedTilePool owns a single large GPU structured buffer carved into fixed-size slots. Multiple FTmvMediaFrameMipBuffer instances (across different clips and mip levels) act as "owners" of slots in the same pool, subject to the constraint that all owners agree on per-slot byte size and plane count. The pool is keyed by (per-tile-bytes, plane-count) so plates of the same APV format coalesce while incompatible plates land in separate pools (see FKey for why per-plane layout is deliberately excluded from the key). Lifetime: pools are owned by the FTmvSharedTilePoolManager singleton. They are created lazily on first request and live for the duration of the TmvMedia module. Owners register/unregister via opaque OwnerHandle. Eviction (two-LRU): slots live in one of three intrusive doubly-linked lists keyed by their current state - Free, VisibleLRU, or NonVisibleLRU. AllocateSlot pops the Free list head first (no eviction work), else the tail (LRU end) of NonVisibleLRU; if both are empty every slot is pinned to some owner's visible set and the caller must grow. Touch on an existing slot moves it to the head (MRU) of VisibleLRU. SetOwnerVisibility walks only this owner's slots (FOwnerInfo::SlotIndices), reclassifying each into VisibleLRU or NonVisibleLRU. All pool ops are O(1) amortized (allocations / touches) or O(per-owner-slots) (visibility updates). Critical-section guarded; safe under concurrent decode threads. Growth:
- L80 _public function_ `friend uint32 GetTypeHash(const FKey& K)`
- L93 _public prototype_ `static FKey MakeKey(const FTmvMediaFrameMipInfo& InMipInfo);`
- L95 _public prototype_ `FTmvSharedTilePool(const FKey& InKey, int32 InInitialCapacity);`
- L96 _public prototype_ `~FTmvSharedTilePool();`
- L98 _public prototype_ `FOwnerHandle RegisterOwner();`
- L99 _public prototype_ `void UnregisterOwner(FOwnerHandle InHandle);`
- L102 _public prototype_ `int32 GetOwnerCount() const;` — Number of currently-registered owners. Zero means the pool is unused.
- L105 _public prototype_ `int32 GetSlot(FOwnerHandle InOwner, FIntPoint InTile) const;` — Returns slot index for the given owner+tile, or INDEX_NONE if not resident.
- L112 _public prototype_ `int32 AllocateSlot(FOwnerHandle InOwner, FIntPoint InTile);` — Allocates a slot for the given owner+tile. Returns the slot index, or INDEX_NONE if the pool is full of currently-visible tiles across all owners (caller should grow or fall back to shader discard).
- L115 _public prototype_ `void SetOwnerVisibility(FOwnerHandle InOwner, const TSet<FIntPoint>& InVisible);` — Publishes the owner's currently-visible tile set; used by eviction.
- L124 _public prototype_ `bool EnsureCapacityFor(int32 InMinCapacity);` — Request the GPU buffer grow so total slot count >= InMinCapacity. Non-blocking: enqueues the grow render command and returns immediately. If another grow is already in flight, this is a no-op (the next call after grow completes will see the larger pool). Returns true if grow was initiated or already sufficient.
- L131 _public function_ `bool IsReady() const` — True once the initial GPU allocation has completed. Until then, GetMappedBuffer / GetShaderResourceView return null and AllocateSlot returns INDEX_NONE. Lock-free read.
- L143 _public prototype_ `void WaitForReady();` — Block the calling thread until the initial GPU allocation completes (bGpuReady transitions to true). No-op if already ready. Used by the shared-mode FTmvMediaFrameMipStructuredBuffer::WaitAllocation so the decoder doesn't try to write through a still-null mapped pointer in the window between RequestAllocation and the render thread completing the async alloc - that race was producing 10s blocking-media timeouts (ImgMedia.BlockingFetch deadline) and stale slot reads ("green frames") during multi-plate ramp-up.
- L157 _public prototype_ `void WaitForGrowComplete();` — Block the calling (worker / decode) thread until any in-flight grow completes - i.e. until bGrowing transitions back to false. No-op if no grow is pending. Used by the reader's slot-allocation path to make AllocateSlot effectively non-failing under blocking-media mode: when AllocateSlot returns INDEX_NONE (pool full of pinned tiles), the reader triggers a grow, calls this, then retries. The cost is a brief (~30 ms typical) worker stall during the grow; the alternative is shipping a sample with missing tiles which the shader then either upscales from a lower mip (perf hit on the upscale-fallback path) or reads as stale slot bytes ("green frames").
- L190 _public function_ `void AcquireReadLock() const` — Manual read-lock entry points for callers that need to hold read locks on multiple pools simultaneously (e.g., the decoder, when a single ApvMediaTmvDecoder::Decode call writes to N pools at once). Callers MUST sort the pool list by pointer-address before calling AcquireRead on each, to ensure deterministic global lock ordering and avoid deadlock between concurrent decode threads.
- L191 _public function_ `void ReleaseReadLock() const`
- L194 _public prototype_ `bool MatchesMipInfo(const FTmvMediaFrameMipInfo& InMipInfo) const;` — Returns true if a buffer-info matches this pool's compatibility class.
- L199 _public prototype_ `void* GetMappedBuffer() const;` — GPU resource accessors (used by FTmvMediaFrameMipBuffer in shared mode). Return null until the pool is Ready. Callers must hold an FReadLockScope across any decoder writes that use the mapped pointer.
- L200 _public prototype_ `FShaderResourceViewRHIRef GetShaderResourceView() const;`
- L201 _public prototype_ `FBufferRHIRef GetUploadBuffer() const;`
- L202 _public prototype_ `FBufferRHIRef GetShaderAccessBuffer() const;`
- L204 _public function_ `int32 GetCapacity() const`
- L205 _public function_ `int32 GetSlotBytes() const`
- L206 _public function_ `const FKey& GetKey() const`
- L207 _public function_ `SIZE_T GetAllocatedBufferSize() const`
- L217 _public prototype_ `int32 GetTotalVisibleTileCount() const;` — Sum of per-owner VisibleTiles counts. This is the *true minimum* capacity needed to never return INDEX_NONE from AllocateSlot at the current moment - every owner's visible tile must have a slot. Used by the reader's INDEX_NONE-retry path to size the grow precisely to demand instead of blindly doubling. Thread-safe via the Cs critical section.
- L254 _private member_ `int32 FreeHead = INDEX_NONE;` — LRU list heads/tails. Head = MRU (recently touched), Tail = LRU (will be evicted next). Free list only needs head; pops/pushes from head are O(1).
- L255 _private member_ `int32 VisibleLruHead = INDEX_NONE;`
- L256 _private member_ `int32 VisibleLruTail = INDEX_NONE;`
- L257 _private member_ `int32 NonVisibleLruHead = INDEX_NONE;`
- L258 _private member_ `int32 NonVisibleLruTail = INDEX_NONE;`
- L261 _private prototype_ `void ListRemove(int32 SlotIdx);` — Intrusive list ops. All callers must hold Cs.
- L262 _private prototype_ `void ListInsertAtHead_Free(int32 SlotIdx);`
- L263 _private prototype_ `void ListInsertAtHead_VisibleLRU(int32 SlotIdx);`
- L264 _private prototype_ `void ListInsertAtHead_NonVisibleLRU(int32 SlotIdx);`
- L265 _private prototype_ `void MoveToList(int32 SlotIdx, ESlotList NewList);`
- L268 _private prototype_ `int32 PickFreeOrEvictableSlot();` — Returns INDEX_NONE if neither a free slot nor an evictable non-visible slot is available (caller will trigger grow).
- L276 _private prototype_ `void EnqueueInitialAllocation_GameOrDecodeThread(int32 InCapacity, SIZE_T InAllocSize);` — Async initial allocation: enqueues the render command, returns immediately. On render thread the command sets the RHI refs and flips bGpuReady to true. Must be called by the manager AFTER the pool is owned by a TSharedPtr (AsWeak asserts otherwise).
- L281 _public function_ `void BeginInitialAllocation()` — Called by FTmvSharedTilePoolManager::GetOrCreatePool once the pool's TSharedPtr is established. Initiates async GPU allocation.
- L291 _private member_ `FKey Key;`
- L292 _private member_ `int32 Capacity = 0;`
- L293 _private member_ `SIZE_T AllocatedBufferSize = 0;`
- L295 _private member_ `mutable FCriticalSection Cs;`
- L303 _private member_ `mutable FRWLock GrowLock;` — Grow lock. Decoders take a read lock around their mapped-buffer writes; the async grow takes a write lock for the buffer-swap step. Public via FReadLockScope (above) so the lock is visible at the decoder call site but the lock object itself stays private.
- L306 _private member_ `std::atomic<bool> bGpuReady{false};` — True once initial GPU allocation completed.
- L314 _private member_ `FEvent* GpuReadyEvent = nullptr;` — Triggered by the initial-alloc render command immediately after bGpuReady is set true. Used by WaitForReady() to block callers cleanly (no spin-wait) until the GPU side of the pool exists. Manual-reset: once triggered, stays signaled for the pool's lifetime.
- L317 _private member_ `std::atomic<bool> bGrowing{false};` — True while an async grow render command is in flight; suppresses duplicate triggers.
- L332 _private member_ `FEvent* GrowDoneEvent = nullptr;` — Auto-reset event triggered when bGrowing transitions back to false at the end of a grow render command. Workers blocked in WaitForGrowComplete wake up here. Auto-reset (not manual-reset like GpuReadyEvent) because grows happen repeatedly - each grow should wake exactly the threads that were waiting for it, and the next grow's waiters should block again until that grow's own trigger. Multi-waiter pattern: many workers can call WaitForGrowComplete concurrently; the grow render command should Trigger() this event enough times for all of them. We track the wait count atomically and Trigger as many times as needed.
- L339 _private member_ `std::atomic<int32> GrowWaiters{0};` — Number of threads currently parked inside WaitForGrowComplete. The grow-completion code uses this to Trigger() the auto-reset event the right number of times (one trigger per blocked thread).
- L341 _private member_ `TArray<FSlot> Slots;`
- L342 _private member_ `TMap<TPair<int32, FIntPoint>, int32> OwnerKeyToSlot;`
- L343 _private member_ `TMap<int32, FOwnerInfo> Owners;`
- L344 _private member_ `int32 NextOwnerId = 0;`
- L349 _private member_ `FBufferRHIRef UploadBufferRef;` — GPU resources (allocated on render thread). UploadBufferMapped is updated under the write lock during grow so decoders holding read locks see consistent state.
- L350 _private member_ `void* UploadBufferMapped = nullptr;`
- L351 _private member_ `FBufferRHIRef ShaderAccessBufferRef;`
- L352 _private member_ `FShaderResourceViewRHIRef ShaderResourceView;`

#### struct `FTmvSharedTilePool::FKey`  
`struct FKey`  
_L69-84_
- desc: Identifies a pool's tile compatibility class. Same key = same pool. Keyed by (PerTileBytes, NumPlanes) only - deliberately NOT by per-plane dimensions/stride. Different mips of the same APV format have the same tile byte size and plane count (TMV pads tiles to a uniform per-mip- level size that happens to agree across mips for this format) but different per-plane width/height/stride. We unify them anyway because the pool only stores opaque bytes; the per-mip layout (Offsets, Strides) is carried in the per-tile shader descriptor on the converter side, not in the pool. Unifying lets cross-mip slot reuse work: when a plate stops using mip 0 (zooms out), its mip-0 tiles' slots become evictable and the next plate's mip-3 tiles can take them. Total VRAM tracks the peak across-all-mips concurrent residency, not the sum of per-mip peaks.
- L71 _public member_ `int32 PerTileBytes = 0;`
- L72 _public member_ `int32 NumPlanes = 0;`
- L74 _public function_ `bool operator==(const FKey& Other) const`

#### struct `FTmvSharedTilePool::FOwnerHandle`  
`struct FOwnerHandle`  
_L87-91_
- desc: Per-owner handle into the pool. Treat as opaque.
- L89 _public member_ `int32 OwnerId = INDEX_NONE;`
- L90 _public function_ `bool IsValid() const`

#### struct `FTmvSharedTilePool::FReadLockScope`  
`struct FReadLockScope`  
_L173-180_
- desc: Public read-lock helper for decoders. A decoder thread must hold a read lock on GrowLock for the duration of its mapped-buffer accesses (from GetPlaneBufferForComponent through the last write in oapvd_decode_*). The async grow path takes the write lock around its buffer swap so decoders can't observe a torn pointer/buffer pair. Use the RAII helper below: { FTmvSharedTilePool::FReadLockScope Lock(*SharedPool); // safe to call GetMappedBuffer(), write into it, etc. }
- L175 _public function_ `explicit FReadLockScope(FTmvSharedTilePool& InPool) : Scope(InPool.GrowLock, SLT_ReadOnly)`
- L179 _private member_ `FRWScopeLock Scope;`

#### enum `FTmvSharedTilePool::ESlotList`  
`enum class ESlotList : uint8`  
_L226-231_
- desc: Which intrusive doubly-linked list a slot is currently a member of. Used by the two-LRU eviction scheme below: visible-pinned slots and evictable slots live in separate lists so allocation can pop the non-visible tail in O(1) without scanning past pinned slots.
- L228 _public enumerator_ `Free` — OwnerId == INDEX_NONE, no tile
- L229 _public enumerator_ `VisibleLRU` — Assigned, tile is in owner's VisibleTiles -> pinned
- L230 _public enumerator_ `NonVisibleLRU` — Assigned, tile NOT in owner's VisibleTiles -> evictable

#### struct `FTmvSharedTilePool::FSlot`  
`struct FSlot`  
_L233-241_
- L235 _public member_ `int32 OwnerId = INDEX_NONE;`
- L236 _public member_ `FIntPoint Tile = FIntPoint(INT32_MIN, INT32_MIN);`
- L238 _public member_ `int32 PrevInList = INDEX_NONE;` — Intrusive doubly-linked list pointers (slot indices, INDEX_NONE = end).
- L239 _public member_ `int32 NextInList = INDEX_NONE;`
- L240 _public member_ `ESlotList List = ESlotList::Free;`

#### struct `FTmvSharedTilePool::FOwnerInfo`  
`struct FOwnerInfo`  
_L243-250_
- L245 _public member_ `TSet<FIntPoint> VisibleTiles;`
- L249 _public member_ `TArray<int32> SlotIndices;` — Slot indices currently owned by this owner (in either VisibleLRU or NonVisibleLRU). Lets SetOwnerVisibility iterate only this owner's slots instead of the whole pool.

#### class `FTmvSharedTilePoolManager`  
`class FTmvSharedTilePoolManager`  
_L356-378_
- desc: Singleton manager that keeps one pool per compatibility key.
- L359 _public prototype_ `static FTmvSharedTilePoolManager& Get();`
- L361 _public prototype_ `TSharedPtr<FTmvSharedTilePool, ESPMode::ThreadSafe> GetOrCreatePool(const FTmvMediaFrameMipInfo& InMipInfo, int32 InitialCapacity);`
- L371 _public prototype_ `void ReleaseOwner(const TSharedPtr<FTmvSharedTilePool, ESPMode::ThreadSafe>& InPool, FTmvSharedTilePool::FOwnerHandle InOwner);` — Unregister an owner from its pool and, if that was the pool's last owner, drop the pool from the manager so its GPU buffers are freed now rather than lingering for the whole process. Re-opening a clip of the same format recreates the pool on demand. Callers should release their own TSharedPtr to the pool after this returns (the structured buffer does so when it is destroyed) so the final reference goes away and ~FTmvSharedTilePool runs.
- L373 _public prototype_ `void ReleaseAll();` — for shutdown
- L376 _private member_ `TMap<FTmvSharedTilePool::FKey, TSharedPtr<FTmvSharedTilePool, ESPMode::ThreadSafe>> Pools;`
- L377 _private member_ `FCriticalSection PoolsLock;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/SampleConverter/TmvSharedTileSession.h` (Internal)


#### class `FTmvSharedTileSession`  
`class FTmvSharedTileSession`  
_L24-69_
- desc: Per-(mip-buffer) helper for one frame's virtualized slot assignment. Wraps the shared-tile-pool interaction the reader (FTmvImgMediaReader) used to inline: capacity growth, this owner's visibility publishing + local residency mirror, and the bounded grow-and-retry on slot exhaustion. Constructed cheaply per mip request (holds references, owns no state). The pool's own locking still governs concurrency; this only relocates the policy (retry bound, grow-target math) off the reader so the reader is left with just decode-list building.
- L43 _public prototype_ `explicit FTmvSharedTileSession(FTmvMediaFrameMipBuffer& InBuffer);`
- L46 _public prototype_ `void EnsureCapacityFor(int32 InVisibleCount);` — Grow the buffer to hold at least InVisibleCount slots if it is currently short.
- L54 _public prototype_ `void PublishVisibility(const TSet<FIntPoint>& InVisibleSet);` — Shared mode: publish this owner's visible set for cross-owner eviction protection and clear the local TileToSlot mirror (the pool may have evicted slots since last frame; ResolveSlot re-resolves them). No-op in local mode.
- L61 _public prototype_ `FSlotResolution ResolveSlot(FIntPoint InTile, const TSet<FIntPoint>& InVisibleSet);` — Resolve a slot for InTile: returns its existing slot if resident (mirroring it locally in shared mode), otherwise allocates; on exhaustion runs a bounded grow-and-retry. See FSlotResolution::Result for the three outcomes.
- L64 _public member_ `static constexpr int32 MaxGrowRetries = 8;` — Max blocking grow-and-retry attempts before a tile is declared overflowed.
- L67 _private member_ `FTmvMediaFrameMipBuffer& Buffer;`
- L68 _private member_ `FTmvMediaTileResidency& Residency;`

#### enum `FTmvSharedTileSession::ESlotResult`  
`enum class ESlotResult : uint8`  
_L27-35_
- L30 _public enumerator_ `AlreadyResident` — Tile already had a slot; no decode needed (slot mirrored for descriptor rebuild).
- L32 _public enumerator_ `Allocated` — A slot was assigned; the tile must be decoded into it.
- L34 _public enumerator_ `Overflowed` — No slot available even after grow-and-retry; caller treats as overflow.

#### struct `FTmvSharedTileSession::FSlotResolution`  
`struct FSlotResolution`  
_L37-41_
- L39 _public member_ `ESlotResult Result = ESlotResult::Overflowed;`
- L40 _public member_ `int32 Slot = INDEX_NONE;`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/SampleConverter/TmvTileDescriptorBuilder.h` (Internal)


#### struct `FTmvTileDescriptorBuilder`  
`struct FTmvTileDescriptorBuilder`  
_L20-39_
- desc: Builds the per-tile GPU descriptor array (one FTmvMediaShaderTileDesc per tile) that the structured-buffer swizzle shader and the CPU partial-copy logic use to locate each tile inside a tile-major mip buffer. Pure transform over (mip-info [+ residency]) -> descriptor array: no engine, RHI, or threading state, so it can be unit-tested in isolation. Extracted from FTmvImgMediaReader, which previously owned both fill paths inline.
- L29 _public prototype_ `static void BuildNaturalIndex(const FTmvMediaFrameMipInfo& InMipInfo, TArray<FTmvMediaShaderTileDesc>& OutDescs);` — Non-virtualized tiled mip: the tile at natural index (Y*NumTilesX + X) lives at byte base TileBytes*Idx. Sizes OutDescs to the tile count, zeroes it, then fills every tile. For a virtualized mip the descriptors instead come from the residency map post-decode (slots don't track tile coords), so OutDescs is only sized+zeroed here. No-op when the mip has no tiles.
- L38 _public prototype_ `static void BuildFromResidency(const FTmvMediaFrameMipInfo& InMipInfo, const FTmvMediaTileResidency& InResidency, TArray<FTmvMediaShaderTileDesc>& OutDescs);` — Virtualized tiled mip: each resident tile (X,Y) lives at byte base TileBytes*Slot per the residency map; non-resident tiles stay zeroed so they trip the shader's "no tile here" sentinel. Reuses the existing OutDescs allocation when the tile count is unchanged (only re-zeroing it), otherwise resizes. No-op when the mip has no tiles.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/TmvMediaTuningCVars.h` (Internal)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace TmvMedia` (scope `UE`)
- L14 _prototype_ `bool IsSharedTilePoolEnabled();` (scope `UE::TmvMedia`) — True when r.TmvMedia.UseSharedTilePool routes virtualized buffers through the global shared pool.
- L26 _prototype_ `bool IsSparseOutputMipEnabled();` (scope `UE::TmvMedia`) — True when r.TmvMedia.SparseOutputMip is on. Primary switch for sparse output residency.
- L34 _prototype_ `int32 GetSparseOutputMipMinBytesMB();` (scope `UE::TmvMedia`) — Per-mip byte-threshold for sparse eligibility. A mip is sparse-managed when mip_bytes >= GetSparseOutputMipMinBytesMB() * 1 MB. Default 128 MB so an HD-plate output texture skips the sparse path (all mips below threshold) while a 16K plate puts mips 0..3 in the sparse set.
- L44 _prototype_ `int32 GetSparseOutputMipBudgetMB();` (scope `UE::TmvMedia`) — Hard ceiling on heap-pool size across all sparse output mips. When a fresh allocation would push the pool past this, the backend force-steals the oldest-LRU owned chunk regardless of hysteresis (safety valve). In normal operation the pool sits at peak concurrent demand, well below the budget; the budget only matters under pathological pressure or when intentionally tightened for testing. Default 2048 MB.
- L54 _prototype_ `int32 GetSparseOutputMipHysteresisSeconds();` (scope `UE::TmvMedia`) — Minimum wall-clock age of an owned chunk before it becomes eligible to be stolen by another texture's commit. Prevents ping-pong thrash on rapid camera cuts; no decommit ever fires at this threshold (memory is only released at UnregisterOutput). Independent of frame rate. Default 2 (seconds) - long enough to ride out rapid camera cuts without re-committing, short enough to release VRAM promptly.
- L63 _prototype_ `int32 GetSparseOutputMipDebugForceFloor();` (scope `UE::TmvMedia`) — Debug: pin the target floor for all sparse output textures. -1 (default) means "follow Viewports". 0 means "always commit mip 0 too"; a positive N means "never commit mips finer than N." Used to A/B what the residency tradeoff looks like without depending on camera motion.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/Transcoder/TmvMediaContainerTranscodeMuxer.h` (Internal)


#### class `UTmvMediaContainerTranscodeMuxer`  
`class UTmvMediaContainerTranscodeMuxer : public UTmvMediaTranscodeMuxer`  
_L26-125_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTmvMediaTranscodeMuxer`
- desc: Container muxer: muxes access units into a container file using ITmvMediaMuxer. Bridges the push-based transcoder pipeline (ReceiveAccessUnit) with the pull-based ITmvMediaMuxer (FSampleRequestDelegate). Incoming access units are buffered and delivered when the muxer's worker thread requests them. @see UTmvMediaTranscodeMuxer
- L30 _public prototype_ `UTmvMediaContainerTranscodeMuxer();`
- L33 _public prototype_ `virtual bool Start(UTmvMediaTranscodeJob* InParentJob) override;`
- L34 _public prototype_ `virtual void RequestStop(UTmvMediaTranscodeJob* InParentJob) override;`
- L38 _public prototype_ `virtual int32 OpenStream(UTmvMediaTranscodeJob* InParentJob, const FString& InStreamName, const FString& InExtension) override;`
- L39 _public prototype_ `virtual void ReceiveAccessUnit( UTmvMediaTranscodeJob* InParentJob, int32 InStreamId, const FTmvMediaFrameTimeInfo& TimeInfo, TSharedPtr<TArray64<uint8>>&& InAccessUnit) override;`
- L52 _public prototype_ `void SetStreamTrackConfig(int32 InStreamId, const FTmvMediaMuxerTrackConfig& InTrackConfig);` — Set the track configuration for a stream opened with OpenStream. Must be called before the first ReceiveAccessUnit for this stream. @param InStreamId Stream index returned by OpenStream. @param InTrackConfig Track configuration for the container.
- L63 _private prototype_ `void FlushPendingRequests();` — Try to fulfill pending muxer requests from the buffer.
- L78 _private member_ `TArray<FContainerStreamInfo> ContainerStreams;`
- L81 _private member_ `TSharedPtr<ITmvMediaMuxer, ESPMode::ThreadSafe> Muxer;` — The underlying container muxer implementation.
- L84 _private member_ `bool bMuxerStarted = false;` — Whether the muxer has been started (ITmvMediaMuxer::Start called).
- L87 _private member_ `bool bMuxerFailed = false;` — Whether the muxer has failed to start and shouldn't be started again.
- L90 _private member_ `std::atomic<bool> bStopRequested = false;` — Whether stop has been requested (signals final samples).
- L112 _private member_ `FCriticalSection SampleBufferCS;` — Critical section protecting StreamBuffers, MuxerTrackToStreamIndex, PendingRequests, bMuxerStarted and bMuxerFailed.
- L115 _private member_ `TArray<TUniquePtr<FStreamBufferState>> StreamBuffers;` — Per-stream buffer state. One entry per stream opened with OpenStream.
- L118 _private member_ `TMap<int32, int32> MuxerTrackToStreamIndex;` — Maps muxer track index to stream index. Populated in SetStreamTrackConfig.
- L121 _private member_ `TArray<ITmvMediaMuxer::FSampleRequest> PendingRequests;` — Pending requests from the muxer worker thread. May contain multiple requests per track.
- L124 _private member_ `FEventRef MuxerFinishedEvent;` — Event signaled by the muxer status delegate when muxing finishes or fails.

#### struct `UTmvMediaContainerTranscodeMuxer::FBufferedSample`  
`struct FBufferedSample`  
_L56-60_
- desc: Buffered access unit waiting to be consumed by the muxer worker thread.
- L58 _public member_ `TSharedPtr<TArray64<uint8>> Data;`
- L59 _public member_ `uint32 SampleNumber = 0;`

#### struct `UTmvMediaContainerTranscodeMuxer::FContainerStreamInfo`  
`struct FContainerStreamInfo`  
_L66-76_
- desc: Extended stream info with container track mapping.
- L69 _public member_ `int32 MuxerTrackIndex = INDEX_NONE;` — Track index in the ITmvMediaMuxer (-1 if not yet added).
- L72 _public member_ `FTmvMediaMuxerTrackConfig TrackConfig;` — Track configuration (set via SetStreamTrackConfig).
- L75 _public member_ `bool bHasTrackConfig = false;` — Whether track config has been set.

#### struct `UTmvMediaContainerTranscodeMuxer::FStreamBufferState`  
`struct FStreamBufferState`  
_L96-106_
- desc: Per-stream buffer state for the push-to-pull bridge. One instance per stream, all fields protected by SampleBufferCS.
- L99 _public member_ `TMap<uint32, FBufferedSample> Samples;` — Buffered samples keyed by sample number.
- L102 _public member_ `uint32 HighestReceivedSampleNumber = 0;` — Highest sample number received from the encoder (to detect last sample on stop).
- L105 _public member_ `TSet<uint32> DeliveredSampleNumbers;` — Set of sample numbers that have been successfully delivered to the muxer.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/Transcoder/TmvMediaFileSequenceFrameProducer.h` (Internal)


#### class `UTmvMediaFileSequenceFrameProducer`  
`class UTmvMediaFileSequenceFrameProducer : public UTmvMediaFrameProducer`  
_L13-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTmvMediaFrameProducer`
- desc: Transcoding Frame Producer Stage implementation for image file sequence using ImageCore.
- L17 _public prototype_ `UTmvMediaFileSequenceFrameProducer();`
- L20 _public prototype_ `virtual bool Start(UTmvMediaTranscodeJob* InParentJob) override;`
- L21 _public prototype_ `virtual void RequestStop(UTmvMediaTranscodeJob* InParentJob) override;`
- L26 _private prototype_ `void ProcessAllImages(UTmvMediaTranscodeJob* InParentJob, const FString& InSequencePath);` — Main loop of the frame producer.
- L29 _private prototype_ `bool ProcessImage(UTmvMediaTranscodeJob* InParentJob, const FString& InImagePath, int32 InFirstFrameIndex);` — Process one image.
- L32 _private prototype_ `bool IsCancelled(const UTmvMediaTranscodeJob* InParentJob) const;` — Returns true if the job is cancelled.
- L35 _private member_ `std::atomic<int32> NumActiveFrames = 0;` — Number of frame being currently processed (in flight).
- L41 _private member_ `std::atomic<uint64> MeasuredMip0Bytes = 0;` — Size in bytes of the first frame's decoded mip 0, recorded once by ProcessImage. Used to size the concurrency budget: the source resolution is only known after an image has been decoded.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/Transcoder/TmvMediaFileSequenceTranscodeMuxer.h` (Internal)


#### class `UTmvMediaFileSequenceTranscodeMuxer`  
`class UTmvMediaFileSequenceTranscodeMuxer : public UTmvMediaTranscodeMuxer`  
_L16-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTmvMediaTranscodeMuxer`
- desc: File sequence muxer: writes each access unit as a separate file. @see UTmvMediaTranscodeMuxer
- L20 _public prototype_ `virtual int32 OpenStream(UTmvMediaTranscodeJob* InParentJob, const FString& InStreamName, const FString& InExtension) override;`
- L22 _public prototype_ `virtual void ReceiveAccessUnit( UTmvMediaTranscodeJob* InParentJob, int32 InStreamId, const FTmvMediaFrameTimeInfo& TimeInfo, TSharedPtr<TArray64<uint8>>&& InAccessUnit) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/Transcoder/TmvMediaPlayerFrameProducer.h` (Internal)


#### class `UTmvMediaPlayerFrameProducer`  
`class UTmvMediaPlayerFrameProducer : public UTmvMediaFrameProducer`  
_L31-198_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTmvMediaFrameProducer`
- desc: Transcoding Frame Producer Stage implementation using a media player and media texture. This will control the player using block on range in order to produce each frame of the sequence. It also uses the media texture rendering callback to capture the rendered media samples and feed it to the following transcoder stage (which should be the converter). Refactor notes: - The player controller aspect could be made into its own class to be more reusable. - The media texture sample capture could also be made into its own class, for the same reason.
- L35 _public prototype_ `UTmvMediaPlayerFrameProducer();`
- L38 _public prototype_ `virtual bool Start(UTmvMediaTranscodeJob* InParentJob) override;`
- L39 _public prototype_ `virtual void RequestStop(UTmvMediaTranscodeJob* InParentJob) override;`
- L40 _public prototype_ `virtual void Tick(UTmvMediaTranscodeJob* InParentJob, const FTmvMediaTranscodeJobTime& InTime) override;`
- L45 _protected prototype_ `void HandlePlaying(UTmvMediaTranscodeJob* InParentJob, float InDeltaTime);` — Sub-Tick function that handles the "playing" state.
- L55 _protected prototype_ `void TryApplyMemoryAwareConcurrencyLimit();` — Caps MaxProcessingFrames to what memory can hold, from the per-frame readback footprint. No-op until the resource reports a size (after the first frame renders), and applied only once. Deliberately one-shot. Free memory has the in-flight frames subtracted from it, so re-measuring once the job is running reads its own footprint back as external pressure and ratchets the ceiling down. See the comment on the definition.
- L65 _protected prototype_ `bool TryFailOnInsufficientMemory(UTmvMediaTranscodeJob* InParentJob);` — Fails the job if the render thread refused a frame readback for lack of memory. Polled every tick, though the flag behind it can only be set when the per-frame footprint changes - the first frame, or a resolution/format change - so this catches a frame that never fit, not pressure that arrives later. Failing is the only safe response: refusing the readback drops that frame from the output, and the play head has already advanced past it by this point. @return true if the job was failed.
- L68 _protected prototype_ `void Close(const UTmvMediaTranscodeJob* InParentJob);` — CLose the player and associated resources.
- L71 _protected prototype_ `void TryUpdateMediaInfo();` — Queries playback range, frame rate, frame duration, from the player if available.
- L74 _protected prototype_ `void TryUpdatePlaybackRange();` — Queries the player for the playback range, if it is available, will update local value.
- L77 _protected prototype_ `void TryUpdateFrameDuration();` — Queries the player for the frame duration, if it is available, will update local value.
- L81 _protected prototype_ `void OnMediaClosed();` — `UFUNCTION()` — Internal MediaPlayer's OnMediaClosed callback function.
- L85 _protected prototype_ `void OnMediaOpened(FString InURL);` — `UFUNCTION()` — Internal MediaPlayer's OnMediaOpened callback function.
- L89 _protected prototype_ `void OnMediaOpenFailed(FString InURL);` — `UFUNCTION()` — Internal MediaPlayer's OnMediaOpenFailed callback function.
- L93 _protected prototype_ `void OnMediaEndReached();` — `UFUNCTION()` — Internal MediaPlayer's OnEndReached callback function.
- L97 _protected prototype_ `void OnMediaResumed();` — `UFUNCTION()` — Internal MediaPlayer's OnPlaybackResumed callback function.
- L101 _protected prototype_ `void OnMediaSuspended();` — `UFUNCTION()` — Internal MediaPlayer's OnPlaybackSuspended callback function.
- L105 _protected prototype_ `void OnMediaSeekCompleted();` — `UFUNCTION()` — Internal MediaPlayer's OnSeekCompleted callback function.
- L109 _protected prototype_ `void OnMediaTrackChanged();` — `UFUNCTION()` — Internal MediaPlayer's OnTracksChanged callback function.
- L113 _protected prototype_ `void OnMediaBuffering();` — `UFUNCTION()` — Internal MediaPlayer's OnBufferingStart callback function.
- L117 _protected prototype_ `void OnMediaBufferingCompleted();` — `UFUNCTION()` — Internal MediaPlayer's OnBufferingCompleted callback function.
- L125 _protected prototype_ `void HandleMediaPlayerEvent(EMediaEvent Event);` — Handler for the player's low-level event multicast (FOnMediaEvent). Unlike the UFUNCTION OnMediaOpened, this fires early enough during media open processing that a Seek issued here lands before any auto-emitted first sample. Mirrors the seek-on-open pattern used by FMovieSceneMediaData::HandleMediaPlayerEvent.
- L129 _protected member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — `UPROPERTY()` — Used to read in media.
- L133 _protected member_ `TObjectPtr<UMediaTexture> MediaTexture;` — `UPROPERTY()` — Media Texture for the player.
- L137 _protected member_ `TObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY()` — Source for the player.
- L140 _protected member_ `TSharedPtr<FTmvMediaPlayerFrameProducerResource> ProducerResource;` — Render Resource for the frame producer.
- L143 _protected member_ `FTimespan MediaFrameDuration;` — How long a frame is.
- L146 _protected member_ `FFrameRate MediaFrameRate;` — Media Frame Rate
- L149 _protected member_ `TRange<FTimespan> MediaPlaybackRange;` — Playback range of the media.
- L152 _protected member_ `FTimespan MediaStartTime;` — What we consider to be the start time of the media (derived from the first decoded sample).
- L155 _protected member_ `FTimespan CurrentTime;` — The current time we are processing.
- L158 _protected member_ `FTimespan PreviousRenderedSampleTime;` — Keep track of the previous tick's rendered sample time to detect when new frames are rendered.
- L161 _protected member_ `int32 MaxProcessingFrames = 1;` — Maximum number of concurrently processing frames.
- L167 _protected member_ `int32 RequestedMaxProcessingFrames = 1;` — Settings-requested ceiling on concurrent in-flight frames (core-capped). MaxProcessingFrames starts at 1 and opens up to this once the memory-aware limit is computed.
- L170 _protected member_ `bool bConcurrencyLimitApplied = false;` — True once TryApplyMemoryAwareConcurrencyLimit has run (needs the first frame's readback size).
- L176 _protected member_ `int32 LastSubmittedCount = 0;` — Once the media is completed (MediaCompleted state), this counter keeps track of how many frames still in flight we are waiting on before the job is completed (other stages).
- L194 _protected member_ `EState CurrentState = EState::Closed;` — Current state of the frame producer.
- L197 _protected member_ `float WatchdogTimeRemaining = 0.0f;` — Watch dog counter for states that can get stuck and time out.

#### enum `UTmvMediaPlayerFrameProducer::EState`  
`enum class EState`  
_L179-191_
- desc: Enum for the frame producer's states.
- L181 _public enumerator_ `Closed`
- L182 _public enumerator_ `Opening`
- L183 _public enumerator_ `Open`
- L184 _public enumerator_ `Preparing`
- L185 _public enumerator_ `Playing`
- L186 _public enumerator_ `MediaCompleted`
- L187 _public enumerator_ `NotSupported`
- L188 _public enumerator_ `Failed`
- L189 _public enumerator_ `TimedOut`
- L190 _public enumerator_ `Errored`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/Transcoder/TmvMediaTestFrameEncoder.h` (Internal)


#### class `UTmvMediaTestFrameEncoder`  
`class UTmvMediaTestFrameEncoder : public UTmvMediaFrameEncoder`  
_L14-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTmvMediaFrameEncoder`
- desc: Implementation of an encoder stage that writes to files directly. Bypass muxer stage. For testing only.
- L19 _public prototype_ `virtual bool Start(UTmvMediaTranscodeJob* InParentJob) override;`
- L23 _public prototype_ `virtual void ReceiveMips(UTmvMediaTranscodeJob* InParentJob, TUniquePtr<FTmvMediaFrameMips>&& InMips) override;`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/Transcoder/TmvMediaTmvFrameEncoder.h` (Internal)


#### class `UTmvMediaTmvFrameEncoder`  
`class UTmvMediaTmvFrameEncoder : public UTmvMediaFrameEncoder`  
_L17-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTmvMediaFrameEncoder`
- desc: Implementation of an encoder stage of the transcode pipeline that wraps a TMV encoder. @see UTmvMediaTranscodeJob
- L22 _public prototype_ `virtual bool Start(UTmvMediaTranscodeJob* InParentJob) override;`
- L23 _public prototype_ `virtual void RequestStop(UTmvMediaTranscodeJob* InParentJob) override;`
- L27 _public prototype_ `virtual void SetEncoderOptions(const TInstancedStruct<FTmvMediaEncoderOptions>& InOptions) override;`
- L28 _public prototype_ `virtual const FTmvMediaEncoderOptions* GetEncoderOptions() const override;`
- L29 _public prototype_ `virtual bool RequestMipInfos(UTmvMediaTranscodeJob* InParentJob, const FTmvMediaFrameTimeInfo& InSourceTimeInfo, const FTmvMediaFrameMipInfo& InSourceMipInfo, TArray<FTmvMediaFrameMipInfo>& OutFrameMipInfo) override;`
- L30 _public prototype_ `virtual void ReceiveMips(UTmvMediaTranscodeJob* InParentJob, TUniquePtr<FTmvMediaFrameMips>&& InMips) override;`
- L35 _private member_ `TInstancedStruct<FTmvMediaEncoderOptions> EncoderOptions;` — Encoder options, must be set before the job is started and can't be modified.
- L38 _private member_ `TSharedPtr<FTmvMediaTmvEncoderPool> EncoderPool;` — Encoder pool to keep encoder objects around between the worker threads.
- L41 _private member_ `int32 StreamId = INDEX_NONE;` — StreamId when opening a stream with the muxer.
- L44 _private member_ `FString StreamName;` — Name of the currently opened stream.
- L48 _private member_ `TObjectPtr<UTmvMediaContainerTranscodeMuxer> ContainerMuxer;` — `UPROPERTY(Transient)` — Pointer to container muxer if using container output (null for file sequence).
- L51 _private member_ `bool bContainerTrackConfigSet = false;` — Whether the track config has been set on the container muxer.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/Transcoder/TmvMediaTranscodeSerialization.h` (Internal)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TMVMEDIA_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace TmvMedia` (scope `UE`)
- L16 _namespace_ `namespace TranscodeSerialization` (scope `UE::TmvMedia`)
- L19 _prototype_ `bool SerializeTranscodeJobSettingsToJson( FArchive& InArchive, const FTmvMediaTranscodeJobSettings* InJobSettings, const TInstancedStruct<FTmvMediaEncoderOptions>& InEncoderOptions);` (scope `UE::TmvMedia::TranscodeSerialization`) — Serialize the given job settings and options to the given archive in json format.
- L25 _prototype_ `bool DeserializeTranscodeJobSettingsFromJson( FArchive& InArchive, FTmvMediaTranscodeJobSettings* OutJobSettings, TInstancedStruct<FTmvMediaEncoderOptions>& OutEncoderOptions);` (scope `UE::TmvMedia::TranscodeSerialization`) — Deserialize the given job settings and options from the given archive in json format.
- L31 _prototype_ `bool SerializeTranscodeListToJson( FArchive& InArchive, const UTmvMediaTranscodeList& InTranscodeList);` (scope `UE::TmvMedia::TranscodeSerialization`) — Serialize the given transcode list to the given archive in json format.
- L36 _prototype_ `bool DeserializeTranscodeListFromJson( FArchive& InArchive, UTmvMediaTranscodeList& OutTranscodeList);` (scope `UE::TmvMedia::TranscodeSerialization`) — Deserialize the given transcode list from the given archive in json format.
- L41 _prototype_ `bool SerializeTranscodeListItemsToJson( FArchive& InArchive, const TArray<FTmvMediaTranscodeListItem>& InTranscodeListItems);` (scope `UE::TmvMedia::TranscodeSerialization`) — Serialize the given transcode list items to the given archive in json format.
- L46 _prototype_ `bool DeserializeTranscodeListItemsFromJson( FArchive& InArchive, TArray<FTmvMediaTranscodeListItem>& OutTranscodeListItems);` (scope `UE::TmvMedia::TranscodeSerialization`) — Deserialize the given transcode list items from the given archive in json format.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/Utils/TmvMediaFrameUtils.h` (Internal)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TMVMEDIA_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace TmvMedia` (scope `UE`)
- L16 _namespace_ `namespace FrameUtils` (scope `UE::TmvMedia`)
- L24 _prototype_ `FVector GetYuvOffset(ETmvMediaFrameComponentType InType, ETmvMediaFrameColorMatrixRange InColorMatrixRange, uint8 InBitDepth);` (scope `UE::TmvMedia::FrameUtils`) — Returns the YUV offset to apply in YUV <-> RGB conversion. @param InType Component type (float, int) @param InColorMatrixRange Matrix coefficient range (full, limited) @param InBitDepth Component bit depth
- L31 _prototype_ `FMatrix GetRgbToYuvMatrix(ETmvMediaFrameColorMatrix InColorMatrix, ETmvMediaFrameColorMatrixRange InColorMatrixRange);` (scope `UE::TmvMedia::FrameUtils`) — Returns the RGB to YUV conversion matrix (without the YUV offset). Only 3x3 sub-matrix is populated. @param InColorMatrix Specify Yuv matrix @param InColorMatrixRange Specify coefficient range
- L38 _prototype_ `FMatrix GetYuvToRgbMatrix(ETmvMediaFrameColorMatrix InColorMatrix, ETmvMediaFrameColorMatrixRange InColorMatrixRange);` (scope `UE::TmvMedia::FrameUtils`) — Returns the YUV to RGB conversion matrix (without the YUV offset). Only 3x3 sub-matrix is populated. @param InColorMatrix Specify Yuv matrix @param InColorMatrixRange Specify coefficient range
- L47 _prototype_ `bool PopulateImageInfo(const FTmvMediaFrameMipInfo& InMipInfo, FImageInfo& OutImageInfo, FString* OutError = nullptr);` (scope `UE::TmvMedia::FrameUtils`) — Utility function to populate an FImageInfo from the FrameMipInfo if the format allows, i.e. single plane packed format. @param InMipInfo Source frame mip info. @param OutImageInfo Populated image info. @param OutError Optional string populated with the specific reason for the incompatibility. @return true if the format is supported by FImage, false otherwise.
- L55 _prototype_ `void PopulateMipInfoFromImageInfo(int32 InMipLevel, const FImageInfo& InImageInfo, FTmvMediaFrameMipInfo& OutMipInfo);` (scope `UE::TmvMedia::FrameUtils`) — Utility function to populate a FrameMipInfo from an ImageInfo. @param InMipLevel Mip level corresponding to this frame mip buffer @param InImageInfo Source image info @param OutMipInfo  Populated FrameMipInfo
- L64 _prototype_ `EPixelFormat GetPlanePixelFormat(const FTmvMediaFramePlaneInfo& InPlaneInfo, bool bInNormalized);` (scope `UE::TmvMedia::FrameUtils`) — Get the packed pixel format exactly matching the plane's memory layout. Mostly support 1, 2 and 4 component(s) packed formats. Mainly validated against DXGI formats. @param InPlaneInfo Plane configuration @param bInNormalized In case of an integer format indicate if the format should be normalized or not. @return Request pixel format if supported, PF_Unknown if not.
- L75 _prototype_ `bool WriteMipBufferToFile(const FString& InFilepath, const FTmvMediaFrameMipBufferHandle& InMipBuffer);` (scope `UE::TmvMedia::FrameUtils`) — Helper function to save mip buffers to file for inspection. The file format to use is internally determined depending on the mip buffer memory layout and color model. @param InFilepath Destination file path, excluding extension. @param InMipBuffer Mip Buffer to save. @return true if operation succeeded.
- L79 _namespace_ `namespace UE`
- L79 _namespace_ `namespace TmvMedia` (scope `UE`)
- L79 _namespace_ `namespace FrameUtils` (scope `UE::TmvMedia`)
- L79 _namespace_ `namespace Y4M` (scope `UE::TmvMedia::FrameUtils`)
- L82 _prototype_ `bool WriteHeader(IFileHandle& InArchive, const FTmvMediaFrameMipInfo& InMipInfo);` (scope `UE::TmvMedia::FrameUtils::Y4M`) — Write Y4M header to the given archive.
- L85 _prototype_ `bool WriteFrameHeader(IFileHandle& InArchive);` (scope `UE::TmvMedia::FrameUtils::Y4M`) — Write the Y4M frame header (marker) to the given archive.
- L88 _prototype_ `bool WriteFrameBody(IFileHandle& InArchive, const FTmvMediaFrameMipBufferHandle& InMipBuffer);` (scope `UE::TmvMedia::FrameUtils::Y4M`) — Write the Y4M frame body to the given archive.
- L91 _prototype_ `bool WriteFrame(IFileHandle& InArchive, const FTmvMediaFrameMipBufferHandle& InMipBuffer);` (scope `UE::TmvMedia::FrameUtils::Y4M`) — Write the Y4M frame (frame header + frame body) to the given archive.
- L94 _prototype_ `bool IsWriteFrameSupported(const FTmvMediaFrameMipInfo& InMipInfo);` (scope `UE::TmvMedia::FrameUtils::Y4M`) — Returns true if the given frame format is supported by Y4M writer.
- L98 _namespace_ `namespace UE`
- L98 _namespace_ `namespace TmvMedia` (scope `UE`)
- L98 _namespace_ `namespace FrameUtils` (scope `UE::TmvMedia`)
- L98 _namespace_ `namespace Pfm` (scope `UE::TmvMedia::FrameUtils`)
- L105 _prototype_ `bool WriteFrame(IFileHandle& InArchive, const FImageView& InImageView);` (scope `UE::TmvMedia::FrameUtils::Pfm`) — Write the frame to the given archive in PFM (portable float map) format. @param InArchive file archive to write to. @param InImageView image view to write.
- L114 _prototype_ `bool IsWriteFrameSupported(const FTmvMediaFrameMipInfo& MipInfo, FString* OutError = nullptr);` (scope `UE::TmvMedia::FrameUtils::Pfm`) — Validate if the WriteFrame supports the given mip buffer format. @param MipInfo mip buffer format to validate. @param OutError Optional string populated with specific reason why format is not supported. @return true if the format is supported. @see WriteFrame
- L125 _prototype_ `bool WriteFrame(IFileHandle& InArchive, const FTmvMediaFrameMipBufferHandle& InMipBuffer, FString* OutError = nullptr);` (scope `UE::TmvMedia::FrameUtils::Pfm`) — Write the frame to the given archive in PFM (portable float map) format. This function is extremely slow, use only for troubleshooting color conversions. @param InArchive file archive to write to. @param InMipBuffer Mip buffer to write. @param OutError Optional parameter to be populated with an error message if the format is not supported. @remark Not all possible formats are supported, only the ones that convert trivially to rgb float16 or float32.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/Utils/TmvMediaPathUtils.h` (Internal)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TMVMEDIA_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TmvMedia` (scope `UE`)
- L15 _namespace_ `namespace PathUtils` (scope `UE::TmvMedia`)
- L21 _prototype_ `FString EnsureStartWithDotSlash(const FString& InPath);` (scope `UE::TmvMedia::PathUtils`) — Utility function to ensure the path is starting with a "./". This is the format of the img/file media source use for internal relative paths.
- L30 _prototype_ `FString GetDirectoryFullPath(const FString& InSanitizedPath);` (scope `UE::TmvMedia::PathUtils`) — Utility function to extract the full directory path from a given sanitized file or directory path. This function will work reliably for existing paths, otherwise, it will fall back to FPaths::GetPath. @remark Relative paths are assumed to be relative to the project directory, unless using explicit tokens. @param InSanitizedPath Can be a file or directory path in the sanitized format.
- L42 _prototype_ `FString GetSanitizedPath(const FString& InPath);` (scope `UE::TmvMedia::PathUtils`) — Utility function to convert a given path (file or directory) to a sanitized version according to the tmv media supported paths format: - relative path under project folder (will start with ./) - absolute path if outside of project folder. - support path tokens, i.e. supported tokens will remain. @param InPath Input path, can be a file or folder. @return Sanitized path (file or folder).
- L51 _prototype_ `FString ConvertSanitizedPathToFull(const FString& InSanitizedPath);` (scope `UE::TmvMedia::PathUtils`) — Utility function to convert the given path (file or directory, relative or absolute) to a full path. This is intended to be the inverse operation of GetSanitizedPath(). @param InSanitizedPath Path to convert to absolute, can be a directory or file, relative or absolute. Also support path tokens. @return Absolute path
- L62 _prototype_ `FString MakeFrameFilename(const FString& InBaseName, int32 InFrameIndex, int32 InZeroPadFrameNumbers, const FString& InExtension);` (scope `UE::TmvMedia::PathUtils`) — Utility function to make a filename from a given base name, possibly including tokens. @param InBaseName Base name to use, may contain token {frame_number} (only token supported for now) @param InFrameIndex Frame index (or frame number) of the frame. @param InZeroPadFrameNumbers Number of zeros to pad the frame number with. @param InExtension file extension to append. @return formatted filename with frame index and extension appended.
- L69 _prototype_ `FString GetMediaSourceMediaFullPath(const UMediaSource* InMediaSource);` (scope `UE::TmvMedia::PathUtils`) — Utility function to retrieve the path that a media source is pointing to. @param InMediaSource Media source @return cleaned up path to an existing file or folder, or empty string if not supported by the media source.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/Utils/TmvMediaSerializationUtils.h` (Internal)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TMVMEDIA_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TmvMedia` (scope `UE`)
- L15 _namespace_ `namespace SerializationUtils` (scope `UE::TmvMedia`)
- L20 _prototype_ `bool DeserializeFromJson( const TSharedRef<FJsonObject>& InJsonObject, const UStruct* InStruct, void* InNativeObject, FText& OutErrorMessage);` (scope `UE::TmvMedia::SerializationUtils`) — Utility function to deserialize a struct object from json which supports InstancedStruct fields.
- L29 _prototype_ `TSharedPtr<FJsonObject> SerializeToJson(const UStruct* InStruct, const void* InObject);` (scope `UE::TmvMedia::SerializationUtils`) — Utility function to serialize a struct object to json which supports InstancedStruct fields.
- L32 _prototype_ `FString BytesToString(const TArray<uint8>& InValueAsBytes);` (scope `UE::TmvMedia::SerializationUtils`) — Converts a serialized value stored as raw bytes into a string.
- L35 _function_ `inline TArrayView<const uint8> ValueToConstBytesView(const FString& InValueAsString)` (scope `UE::TmvMedia::SerializationUtils`) — This ArrayView version is meant to work with FMemoryReaderView.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Internal/Utils/TmvMediaTimeUtils.h` (Internal)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace TmvMedia` (scope `UE`)
- L6 _namespace_ `namespace TimeUtils` (scope `UE::TmvMedia`)
- L12 _function_ `inline FFrameRate GetFrameRate(const double InFrameRate)` (scope `UE::TmvMedia::TimeUtils`) — Compute the frame rate (num, den) for the given frame rate decimal value. This function will consider the frame rate with a fractional part as "drop frame".
- L29 _function_ `inline FFrameRate ComputeFrameRateFromDuration(const double InDurationInSeconds, const FFrameRate& InDefaultFrameRate)` (scope `UE::TmvMedia::TimeUtils`) — Compute the frame rate (num, den) for the given duration in seconds. @param InDurationInSeconds Interval duration in seconds. @param InDefaultFrameRate Default frame rate returns in case duration is invalid. @return computed frame rate or default.
- L46 _function_ `inline FFrameRate ComputeFrameRateFromDuration(const FTimespan& InIntervalDuration, const FFrameRate& InDefaultFrameRate)` (scope `UE::TmvMedia::TimeUtils`) — Compute the frame rate (num, den) for the given interval duration. This function will consider the fractional frame rate as "drop frame". @param InIntervalDuration interval duration @param InDefaultFrameRate Default frame rate returns in case duration is invalid. @return Computed frame rate or default.
- L57 _function_ `inline FFrameRate GetOrComputeFrameRate(const FFrameRate& InMediaFrameRate, const FTimespan& InSampleDuration)` (scope `UE::TmvMedia::TimeUtils`) — Returns the given media frame rate if valid, otherwise compute it from the given sample duration. @param InMediaFrameRate Media's frame rate determined by the player. @param InSampleDuration Current sample duration @return the resulting framerate, can be invalid.
- L74 _function_ `inline int32 RoundToFrameIndex(const FFrameRate& InFrameRate, double InSeconds)` (scope `UE::TmvMedia::TimeUtils`) — Snap a time-on-the-frame-grid (in seconds) to its nearest frame index at the given rate. FFrameRate::AsFrameNumber() floors, which under-counts by one when a sample time has lost sub-tick precision (e.g. 23.976 fps frames at N * 1001 / 24000 seconds can't be represented exactly in FTimespan's 100-ns ticks for most N). RoundToFrame on the FFrameTime split handles that case correctly.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/Commandlets/TmvMediaTranscodeCommandlet.h` (Private)


#### class `UTmvMediaTranscodeCommandlet`  
`class UTmvMediaTranscodeCommandlet : public UCommandlet`  
_L40-54_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Execute TmvMedia transcode jobs headlessly from a commandlet. Usage: UnrealEditor.exe <Project.uproject> -run=TmvMediaTranscode -AllowCommandletRendering [options] Job source (pick one): -JobList=<path>      Load a serialized UTmvMediaTranscodeList from json; runs every item. -JobItem=<path>      Load a single serialized job item from json; wrapped in a one-item list. (otherwise)          Build a single job item from the command line. See "CLI job" below. CLI job: -Encoder=<name>      Required. Name or unique case-insensitive substring of a registered encoder factory (e.g. "apv", "exr"). Selects the encoder options struct. -JobName=<name>      Optional display name for the item. Defaults to "CommandLineJob". -<Property>=<Value>  Any property of FTmvMediaTranscodeJobSettings or of the selected encoder options struct, set via reflection. Sub-fields use dot or slash notation. Examples: -InputPath=<path>, -OutputPath=<path>, -OutputFormat=Container, -Muxer.Name=Tmv, -bUseMediaPlayer=false. FFilePath and FDirectoryPath properties accept a bare string. After parsing, the item is validated (input/output paths set, and OutputAssetDirectory consistent with bMakeOutputAsset). Other switches: -JobTimeoutSeconds=<s>  Optional per-job wall-clock timeout. When exceeded the job is cancelled and the runner proceeds to the next item. 0 (default) disables the watchdog. -Debug               Raise LogMediaAssets and LogMediaUtils verbosity to VeryVerbose. -LoadModule="A,B,…"  Comma-separated lis
- L46 _public prototype_ `UTmvMediaTranscodeCommandlet();` — Default Constructor
- L49 _public prototype_ `virtual int32 Main(const FString& InParams) override;`
- L53 _private prototype_ `void PrintUsage() const;`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/Platforms/Windows/TmvSparseOutputBackendD3D12.h` (Private)


#### class `FTmvSparseOutputBackendD3D12`  
`class FTmvSparseOutputBackendD3D12 : public FTmvSparseOutputBackend`  
_L46-187_
- inherits: `FTmvSparseOutputBackend`
- desc: D3D12 backend for the TMV sparse-output media-texture path. Uses ID3D12DynamicRHI (the public extension surface DLSS/FSR/RTX plugins use) to issue per-mip UpdateTileMappings on a reserved (tiled) texture without extending the engine RHI. See plan `we-ve-improved-performance-reduced-agile-journal.md` and memory `tmv-sparse-output-mip-rhi-gap` for why the public RHI is insufficient on this branch. Demand-driven chunk pool. Physical tile-spans stay mapped to whoever last owned them; CommitMip prefers to steal an eligible chunk (oldest LRU, matching tile count, past hysteresis) and rebind it via UpdateTileMappings rather than free + re-alloc. Memory is released only at UnregisterOutput, which walks the texture's owned chunks, unmaps them, and drops trailing empty heaps from the pool. Heap pool grows exponentially (64 -> 128 -> 256 -> 512 MB, capped) up to the configured budget; over-budget pressure force-steals the oldest chunk regardless of hysteresis as a safety valve.
- L49 _public prototype_ `FTmvSparseOutputBackendD3D12();`
- L53 _public prototype_ `virtual bool RegisterOutput(FRHITexture* Texture, const FTmvSparseOutputLayout& Layout) override;`
- L54 _public prototype_ `virtual void UnregisterOutput(FRHITexture* Texture) override;`
- L55 _public prototype_ `virtual FTmvSparseMipCommitResult CommitMip(FRHITexture* Texture, int32 MipIndex) override;`
- L56 _public prototype_ `virtual void SetTexturePinned(FRHITexture* Texture, bool bPinned) override;`
- L57 _public prototype_ `virtual bool IsMipCommitted(FRHITexture* Texture, int32 MipIndex) const override;`
- L58 _public prototype_ `virtual int64 GetCommittedBytes(FRHITexture* Texture, int32 MipIndex) const override;`
- L59 _public prototype_ `virtual int64 GetTotalCommittedBytes() const override;`
- L60 _public prototype_ `virtual void Dump(FOutputDevice& Ar) const override;`
- L64 _public prototype_ `static TSharedPtr<FTmvSparseOutputBackend, ESPMode::ThreadSafe> CreateInstance();` — Creator registered with FTmvSparseOutputBackendFactory at static init.
- L67 _private member_ `static constexpr int64 TileSizeInBytes = 65536;` — D3D12 standard tile size
- L118 _private prototype_ `bool IsRenderTargetOrDepthStencil(FRHITexture* Texture) const;` — Returns true if the entry's referenced texture has render-target or depth-stencil flags; controls heap-flag selection.
- L125 _private prototype_ `bool AllocateSpans_NoLock(int32 NumTiles, bool bRenderTargetable, TArray<FMipHeapSpan>& OutSpans, bool bForceAllocation = false);` — Allocate K tiles, possibly across multiple heaps. Appends spans to OutSpans and returns true on success. Holds Lock; assumes caller already holds it. bForceAllocation = true bypasses the budget cap - used for always-resident commits at RegisterOutput that have no stealable fallback. Sparse-mip commits leave it false so the budget cap forces a steal-or-fail.
- L128 _private prototype_ `void FreeSpans_NoLock(TConstArrayView<FMipHeapSpan> Spans);` — Mark spans free. Holds Lock; assumes caller already holds it.
- L134 _private prototype_ `int32 AllocateHeap_NoLock(int32 MinTiles, bool bRenderTargetable, bool bForceAllocation = false);` — Allocate a new heap large enough to hold at least MinTiles tiles, capped at MaxHeapSizeInBytes. Returns new heap index, or INDEX_NONE on failure (CreateHeap failed, or would exceed budget). bForceAllocation = true bypasses the budget cap for callers that must succeed.
- L137 _private prototype_ `void ReleaseEmptyTrailingHeaps_NoLock();` — Drop trailing fully-empty heaps. Holds Lock; assumes caller already holds it.
- L150 _private prototype_ `FStealTarget FindStealableMip_NoLock( FRHITexture* RequestingTexture, int32 RequestingMipIndex, int32 RequiredTiles, double NowSeconds, bool bIgnoreHysteresis) const;`
- L162 _private prototype_ `void RebindChunk_NoLock( FTextureEntry& FromEntry, int32 FromMipIndex, FTextureEntry& ToEntry, int32 ToMipIndex);` — Move the existing chunk owned by (FromTex, FromMip) to back (ToTex, ToMip). Issues unmap from FromTex's VA then map to ToTex's VA on the GPU queue; the ExecuteCommandLists ordering against subsequent draws ensures mappings are live before sampling. Caller must have raised FromTex's residency floor (or be about to) before any draw that samples FromTex's now-stale mip.
- L169 _private prototype_ `void SubmitMappingForSpan( ID3D12Resource* Resource, uint32 Subresource, uint32 MipStartTileOffset, uint32 MipWidthInTiles, uint32 MipHeightInTiles, ID3D12Heap* Heap, uint32 HeapStartTile, uint32 TileCount, bool bCommit);` — Submit one UpdateTileMappings call for a single span. Issued via RHIRunOnQueue.
- L180 _private member_ `mutable FCriticalSection Lock;`
- L181 _private member_ `TMap<FRHITexture*, FTextureEntry> Entries;`
- L182 _private member_ `TArray<FHeapEntry> HeapPool;`
- L183 _private member_ `int64 TotalCommittedBytes = 0;`
- L186 _private member_ `int32 NextHeapGrowthStep = 0;` — Heap growth schedule: 64, 128, 256, 512 MB (cap). Index = next-heap-to-allocate position.

#### struct `FTmvSparseOutputBackendD3D12::FHeapEntry`  
`struct FHeapEntry`  
_L69-75_
- L71 _public member_ `TRefCountPtr<ID3D12Heap> Heap;`
- L72 _public member_ `int32 TilesInHeap = 0;`
- L73 _public member_ `int32 NumFreeTiles = 0;`
- L74 _public member_ `TBitArray<> FreeTiles;` — bit set = free

#### struct `FTmvSparseOutputBackendD3D12::FMipHeapSpan`  
`struct FMipHeapSpan`  
_L78-83_
- desc: One contiguous range of tiles allocated to a single mip from one heap.
- L80 _public member_ `int32 HeapIndex = INDEX_NONE;`
- L81 _public member_ `int32 HeapStartTile = 0;`
- L82 _public member_ `int32 TileCount = 0;`

#### struct `FTmvSparseOutputBackendD3D12::FMipMapping`  
`struct FMipMapping`  
_L85-97_
- L87 _public member_ `int32 WidthInTiles = 0;`
- L88 _public member_ `int32 HeightInTiles = 0;`
- L89 _public member_ `int32 DepthInTiles = 1;`
- L90 _public member_ `int32 NumTiles = 0;`
- L91 _public member_ `bool bCommitted = false;`
- L92 _public member_ `bool bPackedMip = false;`
- L93 _public member_ `bool bAlwaysResident = false;` — packed tail or below-threshold: never stealable, never decommitted
- L94 _public member_ `TArray<FMipHeapSpan> Spans;`
- L95 _public member_ `int64 CommittedBytes = 0;`
- L96 _public member_ `double LastUsedTime = 0.0;` — wall-clock seconds; refreshed by CommitMip touch path

#### struct `FTmvSparseOutputBackendD3D12::FTextureEntry`  
`struct FTextureEntry`  
_L99-114_
- L105 _public member_ `FTextureRHIRef Texture;` — Holds the FRHITexture refcount so the underlying ID3D12Resource stays alive from RegisterOutput until UnregisterOutput, regardless of when external owners (FMediaTextureResource) drop their refs. Without this, the engine-exit drain path dereferences a Resource that's already been freed by deferred-delete.
- L106 _public member_ `ID3D12Resource* Resource = nullptr;` — observer of Texture's underlying D3D12 object
- L107 _public member_ `FTmvSparseOutputLayout Layout;`
- L108 _public member_ `TArray<FMipMapping> Mips;`
- L109 _public member_ `uint32 NumStandardMips = 0;`
- L110 _public member_ `uint32 NumPackedMips = 0;`
- L111 _public member_ `uint32 NumTilesForPackedMips = 0;`
- L112 _public member_ `uint32 PackedMipStartTileIndex = 0;`
- L113 _public member_ `bool bPinned = false;` — manager-side FullResidencyRefCount > 0: chunks not stealable

#### struct `FTmvSparseOutputBackendD3D12::FStealTarget`  
`struct FStealTarget`  
_L145-149_
- desc: Find an existing committed mip elsewhere in Entries that can give up its chunk to satisfy a NumTiles request. Returns {nullptr, INDEX_NONE} on miss. LRU among eligible chunks: oldest LastUsedTime wins. Skips pinned textures, skips always-resident mips (packed tail + below-threshold), skips the requesting (Texture, MipIndex) itself. If bIgnoreHysteresis is false the chunk must be at least HysteresisSeconds wall-clock old.
- L147 _public member_ `FRHITexture* OwnerTexture = nullptr;`
- L148 _public member_ `int32 MipIndex = INDEX_NONE;`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/SampleConverter/SparseOutputMip/TmvSparseOutputBackend.h` (Private)


#### struct `FTmvSparseOutputLayout`  
`struct FTmvSparseOutputLayout`  
_L23-46_
- desc: Per-output-texture layout snapshot passed to the backend at registration time. The manager fills this from the texture create description; the backend uses it to decide which mips are sparse-eligible, query tile counts from the underlying API, and pre-commit always-resident mips (those below the byte threshold or in a hardware-packed mip tail).
- L25 _public member_ `FIntPoint Dim = FIntPoint::ZeroValue;`
- L26 _public member_ `EPixelFormat Format = PF_Unknown;`
- L27 _public member_ `int32 NumMips = 0;`
- L28 _public member_ `int32 BytesPerPixel = 0;`
- L29 _public member_ `int64 MinSparseBytes = 0;` — bytes; mips with W*H*BytesPerPixel below this are not sparse-managed.
- L31 _public function_ `int64 ComputeMipBytes(int32 MipIndex) const`
- L42 _public function_ `bool IsMipSparseEligible(int32 MipIndex) const`

#### struct `FTmvSparseMipCommitResult`  
`struct FTmvSparseMipCommitResult`  
_L55-59_
- desc: Result of a CommitMip call. If a fresh chunk was allocated, both fields are zero/null. If an existing chunk was stolen from another texture/mip to satisfy the commit, StolenFromTexture/StolenFromMip identify the previous owner so the manager can raise its ResidentFloor and republish its SRV before any draw samples the now-unmapped subresource.
- L57 _public member_ `FRHITexture* StolenFromTexture = nullptr;`
- L58 _public member_ `int32 StolenFromMip = INDEX_NONE;`

#### class `FTmvSparseOutputBackend`  
`class FTmvSparseOutputBackend`  
_L82-132_
- desc: Platform/RHI-agnostic interface for the sparse output media-texture backend. Each backend implements per-mip commit on a reserved (tiled) resource using its API of choice (D3D12 UpdateTileMappings, Vulkan vkBindSparseImageMemory, etc). Backends self-register with the factory during static init; the platform-specific file lives under Private/Platforms/<Platform>/ and is automatically excluded by UBT on non-matching targets. Memory model: demand-driven chunk pool. Physical tile-spans stay mapped to whoever last owned them; a new commit prefers to steal a chunk past its hysteresis age via UpdateTileMappings rebind rather than free + re-alloc. Memory is physically released only at UnregisterOutput (and the stale-GC path that calls it). No timer ever decommits. Threading: all methods are called from the render thread. Backends may dispatch actual GPU/queue work asynchronously (RHIRunOnQueue or equivalent) but must guarantee that a CommitMip issued before a converter pass has produced a valid mapping by the time that pass executes on the GPU. UpdateTileMappings + ExecuteCommandLists ordering on D3D12 gives this for free; other backends must reproduce the equivalent.
- L85 _public prototype_ `virtual ~FTmvSparseOutputBackend() = default;`
- L93 _public prototype_ `virtual bool RegisterOutput(FRHITexture* Texture, const FTmvSparseOutputLayout& Layout) = 0;` — One-time per-resource setup: caches the underlying API handle, queries per-mip tile counts, pre-commits always-resident mips. Returns false on any failure; manager will keep the texture non-sparse in that case and the per-clip cost reverts to baseline.
- L96 _public prototype_ `virtual void UnregisterOutput(FRHITexture* Texture) = 0;` — Tear down per-resource state. Waits for any in-flight GPU work that references the resource.
- L107 _public prototype_ `virtual FTmvSparseMipCommitResult CommitMip(FRHITexture* Texture, int32 MipIndex) = 0;` — Commit physical backing for the given mip subresource. Idempotent: a second call when the mip is already committed refreshes the chunk's last-used timestamp and returns an empty result. On fresh commit the backend prefers to steal an eligible owned chunk (returns StolenFrom* identifying the prior owner) rather than allocate; the manager must raise the prior owner's ResidentFloor and republish its SRV before the next draw.
- L115 _public prototype_ `virtual void SetTexturePinned(FRHITexture* Texture, bool bPinned) = 0;` — Mark all of a texture's owned chunks as pinned (not eligible for steal) or unpinned. Set true when a manager-side FullResidencyRefCount goes 0 -> 1, false on the 1 -> 0 transition. Backends with no pinning concept may treat as a no-op.
- L118 _public prototype_ `virtual bool IsMipCommitted(FRHITexture* Texture, int32 MipIndex) const = 0;` — Returns true iff the named mip currently has physical backing.
- L125 _public prototype_ `virtual int64 GetCommittedBytes(FRHITexture* Texture, int32 MipIndex) const = 0;` — Committed bytes for a specific mip, summed across all tiles that actually have physical backing right now (NOT the nominal mip size). Used by tmvmedia.dumpmipbuffers to surface real VRAM impact.
- L128 _public prototype_ `virtual int64 GetTotalCommittedBytes() const = 0;` — Sum of committed bytes across all sparse output textures the backend is managing.
- L131 _public prototype_ `virtual void Dump(FOutputDevice& Ar) const = 0;` — Free-form dump for tmvmedia.dumpmipbuffers; includes per-texture, per-mip rows.

#### class `FTmvSparseOutputBackendFactory`  
`class FTmvSparseOutputBackendFactory`  
_L141-154_
- desc: Singleton registry: each platform/RHI backend self-registers its creator at static-init time, keyed by ERHIInterfaceType. The manager queries this at startup and resolves to whichever backend matches the running RHI; on an RHI with no registered backend, manager startup logs once and the sparse-output path stays disabled regardless of CVar.
- L144 _public typedef_ `using FCreator = TSharedPtr<FTmvSparseOutputBackend, ESPMode::ThreadSafe>(*)();`
- L146 _public prototype_ `bool RegisterBackendForRhi(ERHIInterfaceType RhiType, FCreator Creator);`
- L147 _public prototype_ `TSharedPtr<FTmvSparseOutputBackend, ESPMode::ThreadSafe> CreateInstanceForRhi(ERHIInterfaceType RhiType);`
- L148 _public prototype_ `bool HasBackendForRhi(ERHIInterfaceType RhiType) const;`
- L150 _public prototype_ `static FTmvSparseOutputBackendFactory* Get();`
- L153 _private member_ `TMap<ERHIInterfaceType, FCreator> BackendCreators;`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/SampleConverter/TmvMediaFrameMipMemoryBuffer.h` (Private)


#### class `FTmvMediaFrameMipMemoryBuffer`  
`class FTmvMediaFrameMipMemoryBuffer : public FTmvMediaFrameMipBuffer`  
_L14-41_
- inherits: `FTmvMediaFrameMipBuffer`
- desc: Implementation of texture cpu buffering backed by a memory buffer. Generic memory implementation to be used mostly to store the result of cpu conversion sent to the encoder.
- L18 _public prototype_ `virtual bool RequestAllocation(const FTmvMediaFrameMipInfo& InMipInfo) override;`
- L19 _public function_ `virtual void WaitAllocation() override`
- L20 _public function_ `virtual bool TryUpdateMipInfo(const FTmvMediaFrameMipInfo& InMipInfo) override`
- L21 _public prototype_ `virtual void* GetMappedBuffer() override;`
- L22 _public prototype_ `virtual void* GetPlaneBufferForComponent(int32 InComponentIndex) override;`
- L23 _public prototype_ `virtual FShaderResourceViewRHIRef GetShaderResourceView(int32 InComponentIndex) const override;`
- L24 _public function_ `virtual void CopyTileRegions(int32 InFrameId, const FTmvMediaFrameMipInfo& InTmvMipInfo, TConstArrayView<FIntRect> InTileRegions, TConstArrayView<FTmvMediaShaderTileDesc> InTileInfos) override`
- L25 _public function_ `virtual bool IsValidForRendering() const override`
- L40 _private member_ `TArray<TSharedPtr<FPlaneTextureBuffer>> PlaneBuffers;` — Plane Buffer array.

#### struct `FTmvMediaFrameMipMemoryBuffer::FPlaneTextureBuffer`  
`struct FPlaneTextureBuffer`  
_L33-37_
- desc: Plane Cpu buffer accessed by the encoder.
- L35 _public member_ `int32 Pitch = 0;`
- L36 _public member_ `TArray64<uint8> Buffer;`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/SampleConverter/TmvMediaFrameMipStructuredBuffer.h` (Private)


#### class `FTmvMediaFrameMipStructuredBuffer`  
`class FTmvMediaFrameMipStructuredBuffer : public FTmvMediaFrameMipBuffer`  
_L12-90_
- inherits: `FTmvMediaFrameMipBuffer`
- desc: Implementation of a structured buffer that can be memory mapped and partially updated. This is best suited for tiled memory layouts.
- L16 _public prototype_ `FTmvMediaFrameMipStructuredBuffer();` — Constructor
- L22 _public prototype_ `virtual bool RequestAllocation(const FTmvMediaFrameMipInfo& InMipInfo) override;`
- L23 _public prototype_ `virtual void WaitAllocation() override;`
- L24 _public prototype_ `virtual bool TryUpdateMipInfo(const FTmvMediaFrameMipInfo& InMipInfo) override;`
- L25 _public prototype_ `virtual void* GetMappedBuffer() override;`
- L26 _public prototype_ `virtual void* GetPlaneBufferForComponent(int32 InComponentIndex) override;`
- L27 _public prototype_ `virtual FShaderResourceViewRHIRef GetShaderResourceView(int32 InComponentIndex) const override;`
- L28 _public prototype_ `virtual void CopyTileRegions(int32 InFrameId, const FTmvMediaFrameMipInfo& InTmvMipInfo, TConstArrayView<FIntRect> InTileRegions, TConstArrayView<FTmvMediaShaderTileDesc> InTileInfos) override;`
- L29 _public prototype_ `virtual void CaptureWriteState() override;`
- L30 _public prototype_ `virtual bool IsValidForRendering() const override;`
- L31 _public function_ `virtual bool IsStructuredBuffer() const override`
- L35 _public prototype_ `virtual bool EnsureCapacityFor(int32 InMinCapacity) override;`
- L36 _public function_ `virtual FTmvMediaTileResidency* GetResidency() override`
- L37 _public function_ `virtual const FTmvMediaTileResidency* GetResidency() const override`
- L41 _public function_ `bool IsSharedMode() const` — True when this buffer is in shared-pool mode (no per-buffer GPU resources).
- L50 _private member_ `FTmvMediaTileResidency Residency;` — Logical-to-physical tile mapping for virtualized mips. Only the structured buffer virtualizes, so the residency lives here rather than on the base (see FTmvMediaFrameMipBuffer::GetResidency). Populated in RequestAllocation when MipInfo.IsVirtualized(); reset on pool reuse / fresh allocation.
- L53 _private member_ `TSharedPtr<FTmvSharedTilePool, ESPMode::ThreadSafe> SharedPool;` — Shared-pool reference (set when in shared mode).
- L54 _private member_ `FTmvSharedTilePool::FOwnerHandle SharedOwnerHandle;`
- L60 _private member_ `FBufferRHIRef UploadBufferRef;` — This is the actual buffer reference that we need to keep after it is locked and until it is unlocked. The buffer is used as an upload heap and will not be accessed by shader if CVar "r.TmvConverter.UseUploadHeap" is set.
- L65 _private member_ `void* UploadBufferMapped = nullptr;` — A pointer to mapped GPU memory.
- L70 _private member_ `FBufferRHIRef ShaderAccessBufferRef;` — This buffer is used by the swizzling shader if CVar "r.TmvConverter.UseUploadHeap" is set and UploadBufferRef contents are copied into it.
- L75 _private member_ `FShaderResourceViewRHIRef ShaderResourceView;` — Resource View used by swizzling shader.
- L78 _private member_ `FEvent* AllocationReadyEvent;` — Event used to wait for completed buffer allocations.
- L88 _private member_ `FBufferRHIRef CapturedUploadBuffer;` — Shared-pool snapshot captured by CaptureWriteState() under the pool's read lock just before decode writes. Consumed (and cleared) by the following CopyTileRegions so the GPU per-tile copy targets the same pair the decoder wrote into - even if a concurrent grow has since swapped the pool's current refs to fresh buffers. Null outside the decode -> CopyTileRegions pair and on non-shared buffers.
- L89 _private member_ `FBufferRHIRef CapturedShaderAccessBuffer;`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/SampleConverter/TmvMediaFrameMipTextureBuffer.h` (Private)


#### class `FTmvMediaFrameMipTextureBuffer`  
`class FTmvMediaFrameMipTextureBuffer : public FTmvMediaFrameMipBuffer`  
_L13-60_
- inherits: `FTmvMediaFrameMipBuffer`
- desc: Implementation of texture cpu buffering that can update regions. This is best suited for storing the components on different planes.
- L17 _public prototype_ `FTmvMediaFrameMipTextureBuffer();` — Constructor
- L23 _public prototype_ `virtual bool RequestAllocation(const FTmvMediaFrameMipInfo& InMipInfo) override;`
- L24 _public prototype_ `virtual void WaitAllocation() override;`
- L25 _public prototype_ `virtual bool TryUpdateMipInfo(const FTmvMediaFrameMipInfo& InMipInfo) override;`
- L26 _public prototype_ `virtual void* GetMappedBuffer() override;`
- L27 _public prototype_ `virtual void* GetPlaneBufferForComponent(int32 InComponentIndex) override;`
- L28 _public prototype_ `virtual FShaderResourceViewRHIRef GetShaderResourceView(int32 InComponentIndex) const override;`
- L29 _public prototype_ `virtual void CopyTileRegions(int32 InFrameId, const FTmvMediaFrameMipInfo& InTmvMipInfo, TConstArrayView<FIntRect> InTileRegions, TConstArrayView<FTmvMediaShaderTileDesc> InTileInfos) override;`
- L30 _public prototype_ `virtual bool IsValidForRendering() const override;`
- L40 _private member_ `TArray<TSharedPtr<FPlaneTextureBuffer>> PlaneBuffers;`
- L59 _private member_ `TSharedPtr<FPlaneTextureResources> PlaneTextureResources;` — Reference to the render thread resources.

#### struct `FTmvMediaFrameMipTextureBuffer::FPlaneTextureBuffer`  
`struct FPlaneTextureBuffer`  
_L35-39_
- desc: Plane Cpu buffer accessed by the decoder
- L37 _public member_ `int32 Pitch = 0;`
- L38 _public member_ `TArray64<uint8> Buffer;`

#### struct `FTmvMediaFrameMipTextureBuffer::FPlaneTextureResource`  
`struct FPlaneTextureResource`  
_L43-50_
- desc: Render thread resource: Texture for the memory plane.
- L45 _public member_ `FTmvMediaFramePlaneInfo Info;`
- L46 _public member_ `EPixelFormat PixelFormat;`
- L47 _public member_ `TRefCountPtr<FRHITexture> Texture;`
- L48 _public member_ `FShaderResourceViewRHIRef ShaderResourceView;`
- L49 _public member_ `TSharedPtr<FPlaneTextureBuffer> CpuBuffer;`

#### struct `FTmvMediaFrameMipTextureBuffer::FPlaneTextureResources`  
`struct FPlaneTextureResources`  
_L53-56_
- desc: Container for all the render thread resources.
- L55 _public member_ `TArray<TSharedPtr<FPlaneTextureResource>> PlaneTextures;`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/TmvMediaLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTmvMedia, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTmvMedia, Log, All);`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/Transcoder/TmvMediaFrameRender.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TmvMedia` (scope `UE`)
- L19 _prototype_ `void AddCopyTexturePass(FRDGBuilder& InBuilder, FRDGTexture* InSourceTexture, FRDGTexture* InDestTarget);` (scope `UE::TmvMedia`) — Add a texture copy pass from source to destination for all mips. Can do basic format conversion with a simple "draw texture" pass.
- L24 _prototype_ `void AddConvertTexturePass(FRDGBuilder& InBuilder, FRDGTexture* InSourceTexture, FRDGTexture* InDestTarget, const FTmvMediaFrameMipInfo& InTargetMipInfo);` (scope `UE::TmvMedia`) — Add a texture conversion pass from source to destination.
- L29 _prototype_ `void AddEnqueueCopyPass(FRDGBuilder& InBuilder, FTmvMediaGpuTextureReadback* InReadback, FRDGTextureRef InSourceTexture, uint32 InMipIndex);` (scope `UE::TmvMedia`) — Add a texture copy pass for readback in a staging cpu buffer.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/Transcoder/TmvMediaPlayerFrameProducerResource.h` (Private)


#### class `FTmvMediaPlayerFrameProducerResource`  
`class FTmvMediaPlayerFrameProducerResource : public TSharedFromThis<FTmvMediaPlayerFrameProducerResource>`  
_L38-209_
- inherits: `TSharedFromThis<FTmvMediaPlayerFrameProducerResource>`
- desc: Render thread object for the media player frame producer. Handles the render thread callbacks and holds the rhi resources.
- L41 _public prototype_ `FTmvMediaPlayerFrameProducerResource(UTmvMediaTranscodeJob* InParentJob, UMediaTexture* InMediaTexture);`
- L43 _public prototype_ `~FTmvMediaPlayerFrameProducerResource();`
- L48 _public prototype_ `void InitRHI(FRHICommandListImmediate& InRHICmdList);` — Initializes the dynamic RHI resource on the render thread.
- L53 _public prototype_ `void ReleaseRHI();` — Releases the dynamic RHI resource on the render thread.
- L58 _public prototype_ `void ProcessPendingReadbackRequests(FRHICommandListImmediate& InRHICmdList, const FTmvMediaTranscodeJobTime& InTime);` — Poll all pending readback requests and process the ones that are ready.
- L63 _public function_ `FTimespan GetLastRenderedSampleTime() const` — Returns the last sample time that was rendered by the media texture.
- L71 _public function_ `FTimespan GetLastRenderedSampleDuration() const` — Returns the last sample duration that was rendered by the media texture.
- L79 _public function_ `int32 GetSubmittedCount() const` — Returns the number of concurrent samples that are being processed (submitted to transcoding pipeline).
- L87 _public function_ `void SetMediaFrameRate_RenderThread(const FFrameRate& InFrameRate)` — Set the media frame rate to use to compute the frame indices.
- L99 _public function_ `uint64 GetEstimatedFrameStagingBytes() const` — Returns the size in bytes of one in-flight frame's readback staging (all mips), as measured from the most recently rendered frame. 0 until the first frame has rendered. This is the raw staging size, not a per-pool cost: ComputeReadbackFrameBudget charges it unscaled to the GPU-shared pool and scaled to the physical one.
- L111 _public function_ `bool TryGetRefusedFrameBudget(UE::TmvMedia::FFrameMemoryBudget& OutBudget) const` — Retrieves the budget the render thread actually refused on, so the failure is reported with the figures that made the decision. Re-measuring on the game thread instead would take a fresh reading a moment later and print a second, different set of numbers for the same refusal. @return false if no frame has been refused, leaving OutBudget untouched.
- L126 _private prototype_ `const FTextureResource* GetMediaTextureResource() const;` — Returns the texture resource from the associated media texture.
- L129 _private prototype_ `void CreateRenderTarget_RenderThread(FRHICommandListImmediate& InRHICmdList, const FRHITextureDesc& InRenderTargetDesc);` — Create the intermediate conversion render target.
- L132 _private prototype_ `void OnMediaTextureRendered_RenderThread(const FTextureResource* InMediaTextureResource, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe> InMediaTextureSample);` — Callback for the media texture rendering delegate.
- L135 _private prototype_ `void ProcessAndDispatch(TSharedPtr<UE::TmvMedia::FFrameReadbackRequest>&& InReadbackRequest);` — Process the given readback request and dispatch the mips to the next transcoding stage.
- L138 _private prototype_ `TSharedPtr<UE::TmvMedia::FFrameReadbackRequest> AcquireReadbackRequest();` — Acquire a readback request from the pool if possible, or create a new one otherwise.
- L141 _private prototype_ `void ReleaseReadbackRequest(TSharedPtr<UE::TmvMedia::FFrameReadbackRequest>&& InReadbackRequest);` — Returns the request to the pool for recycling.
- L145 _private member_ `TWeakObjectPtr<UTmvMediaTranscodeJob> ParentJob_RenderThread;` — Pointer to parent job used in render thread.
- L148 _private member_ `TWeakObjectPtr<UMediaTexture> MediaTexture_RenderThread;` — Pointer to the parent media texture used in render thread.
- L151 _private member_ `FTextureRHIRef RenderTargetRhi;` — Intermediate render target to convert the media texture to desired format for conversion.
- L154 _private member_ `FFrameRate MediaFrameRate_RenderThread;` — Media Frame rate from the player. Used to compute frame index.
- L157 _private member_ `FTimespan FirstRenderedSampleTime;` — Keep track of the first rendered sample time to compute the frame index.
- L160 _private member_ `std::atomic<FTimespan> LastRenderedSampleTime;` — This is updated on the render thread to keep track of the rendered "play head".
- L163 _private member_ `std::atomic<FTimespan> LastRenderedSampleDuration;` — This is updated on the render thread as additional information for controller the player.
- L166 _private member_ `std::atomic_int32_t SubmittedCount = 0;` — Number of frames submitted to the converter/decoder (in flight after the producer).
- L178 _private member_ `std::atomic<uint64> EstimatedFrameStagingBytes = 0;` — Size in bytes of one in-flight frame's readback staging, all mips. Written on the render thread from the readback texture desc and read on the game thread to size the producer's concurrency ceiling. 0 until the first frame has rendered. Republished on every rendered frame rather than latched at the first, so a resolution or format change is picked up; a steady-state job just rewrites the same value. Readback heaps are D3D12 system/shared memory, so this figure is charged unscaled to the GPU-shared pool and scaled by MediaPlayer.HostBytesPerFrameScale for the physical pool - see ComputeReadbackFrameBudget.
- L184 _private member_ `std::atomic<bool> bInsufficientMemoryForFrame = false;` — Set on the render thread when one frame's cost exceeds the budgeted share of a pool it draws on - physical or GPU-shared, whichever failed. RefusedFrameBudget records which.
- L191 _private member_ `UE::TmvMedia::FFrameMemoryBudget RefusedFrameBudget;` — The budget as evaluated at the moment of refusal. Written on the render thread before bInsufficientMemoryForFrame is set and read on the game thread only after observing that flag, so the release/acquire pair on the flag publishes it safely without needing to be atomic itself.
- L199 _private member_ `TArray<TSharedPtr<UE::TmvMedia::FFrameReadbackRequest>> PendingRequests;` — Array of pending readback requests. Those are requests that have been submitted to the gpu and are being polled (on the render thread) until they become "ready", i.e. the gpu has done the work and it is ready to be processed, i.e. locked-copied-unlocked without causing a cpu-gpu stall.
- L202 _private member_ `FCriticalSection AvailableRequestsLock;` — Critical Section for accessing the AvailableRequests.
- L205 _private member_ `TArray<TSharedPtr<UE::TmvMedia::FFrameReadbackRequest>> AvailableRequests;` — Array of free available requests (for reuse).
- L208 _private member_ `TArray<FTmvMediaFrameMipInfo> TargetMipInfo;` — Information about the desired mip formats for the encoder.

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace TmvMedia` (scope `UE`)
- L31 _prototype_ `FFrameMemoryBudget ComputeReadbackFrameBudget(uint64 InStagingBytesPerFrame);` (scope `UE::TmvMedia`) — Budgets one in-flight readback frame, applying the readback stage's own peak-footprint scale to the measured staging size. Queries live memory stats, so the result reflects conditions now.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/Transcoder/TmvMediaTranscodeJobManager.h` (Private)


#### class `FTmvMediaTranscodeJobManager`  
`class FTmvMediaTranscodeJobManager : public TSharedFromThis<FTmvMediaTranscodeJobManager>, public ITmvMediaTranscodeJobManager`  
_L12-55_
- inherits: `TSharedFromThis<FTmvMediaTranscodeJobManager>,ITmvMediaTranscodeJobManager`
- desc: Singleton manager for all transcode jobs.
- L15 _public prototype_ `virtual ~FTmvMediaTranscodeJobManager() override = default;`
- L18 _public prototype_ `virtual void GetTranscodeJobs(TArray<TWeakObjectPtr<UTmvMediaTranscodeJob>>& OutTranscodeJobs) const override;`
- L20 _public prototype_ `virtual UTmvMediaTranscodeJob* GetTranscodeJob(const FGuid& InJobId) const override;`
- L22 _public prototype_ `virtual void RegisterTranscodeJob(UTmvMediaTranscodeJob* InTranscodeJob) override;`
- L24 _public prototype_ `virtual void UnregisterTranscodeJob(UTmvMediaTranscodeJob* InTranscodeJob) override;`
- L26 _public function_ `virtual FOnTranscodeJobEvent& GetOnTranscodeJobAdded() override`
- L31 _public function_ `virtual FOnTranscodeJobEvent& GetOnTranscodeJobRemoved() override`
- L39 _private prototype_ `void PruneStaleTranscodeJobs();` — Helper function to remove stale jobs from the internal containers.
- L42 _private member_ `FOnTranscodeJobEvent OnTranscodeJobAdded;` — Delegate for OnTranscodeJobAdded.
- L45 _private member_ `FOnTranscodeJobEvent OnTranscodeJobRemoved;` — Delegate for OnTranscodeJobRemoved.
- L48 _private member_ `mutable FCriticalSection TranscodeJobsLock;` — Critical section for TranscodeJobs containers.
- L51 _private member_ `TArray<TWeakObjectPtr<UTmvMediaTranscodeJob>> TranscodeJobs;` — Container for all registered jobs, regardless of ids.
- L54 _private member_ `TMap<FGuid, TWeakObjectPtr<UTmvMediaTranscodeJob>> TranscodeJobsById;` — Container for registered jobs with an Id.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/Transcoder/TmvMediaTranscodeJobRunner.h` (Private)


#### class `FTmvMediaTranscodeJobRunner`  
`class FTmvMediaTranscodeJobRunner final : public ITmvMediaTranscodeJobRunner, public FTickableGameObject`  
_L18-74_
- inherits: `ITmvMediaTranscodeJobRunner,FTickableGameObject`
- desc: Game-thread implementation of the transcode job runner. Ticked by FTickableGameObject so the active job advances independently of Slate window state (minimize / hide / close).
- L21 _public prototype_ `FTmvMediaTranscodeJobRunner();`
- L25 _public prototype_ `virtual void EnqueueJob(UTmvMediaTranscodeJob* InJob, const FTmvMediaTranscodeJobRunOptions& InOptions = {}) override;`
- L26 _public prototype_ `virtual void CancelAll() override;`
- L27 _public prototype_ `virtual void CancelJob(const FGuid& InJobId) override;`
- L28 _public prototype_ `virtual bool IsJobActiveOrPending(const FGuid& InJobId) const override;`
- L29 _public prototype_ `virtual bool HasActiveOrPendingJobs() const override;`
- L31 _public function_ `virtual FOnRunnerJobEvent& GetOnJobStarted() override`
- L32 _public function_ `virtual FOnRunnerJobEvent& GetOnJobFinished() override`
- L33 _public function_ `virtual FOnAllJobsFinished& GetOnAllJobsFinished() override`
- L37 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L38 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L39 _public prototype_ `virtual bool IsTickable() const override;`
- L40 _public function_ `virtual bool IsTickableInEditor() const override`
- L41 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L42 _public prototype_ `virtual TStatId GetStatId() const override;`
- L47 _private prototype_ `bool StartNextJob();` — Pop and start jobs from the head of the queue until one starts or the queue is drained.
- L50 _private prototype_ `void DiscardCurrentJob(double InCurrentTime);` — Discard the active job and clear active-job state. Broadcasts OnJobFinished.
- L53 _private prototype_ `void OnEnginePreExit();` — Cancel any in-flight work while plugin modules are still loaded (pre-shutdown hook).
- L56 _private member_ `FDelegateHandle EnginePreExitHandle;` — Handle returned by FCoreDelegates::OnEnginePreExit.Add, removed in the destructor.
- L64 _private member_ `TStrongObjectPtr<UTmvMediaTranscodeJob> CurrentJob;`
- L65 _private member_ `FTmvMediaTranscodeJobRunOptions CurrentJobOptions;`
- L66 _private member_ `double CurrentJobStartTime = 0.0;`
- L67 _private member_ `bool bCurrentJobTimedOut = false;`
- L69 _private member_ `TArray<FQueuedJob> PendingJobs;`
- L71 _private member_ `FOnRunnerJobEvent OnJobStartedDelegate;`
- L72 _private member_ `FOnRunnerJobEvent OnJobFinishedDelegate;`
- L73 _private member_ `FOnAllJobsFinished OnAllJobsFinishedDelegate;`

#### struct `FTmvMediaTranscodeJobRunner::FQueuedJob`  
`struct FQueuedJob`  
_L58-62_
- L60 _public member_ `TStrongObjectPtr<UTmvMediaTranscodeJob> Job;`
- L61 _public member_ `FTmvMediaTranscodeJobRunOptions Options;`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/Transcoder/TmvMediaTranscodeMemoryBudget.h` (Private)


#### enum `UE::TmvMedia::EFrameMemoryPool`  
`enum class EFrameMemoryPool : uint8`  
_L11-29_
- desc: A pool that can bound the frames a transcode stage keeps in flight.
- L14 _public enumerator_ `Host` — OS physical memory: CPU buffers, plus the host side of anything staged through the GPU.
- L28 _public enumerator_ `GpuShared` — The D3D shared-memory heaps that GPU readbacks stage through. Only consulted when the RHI reports memory stats. RHIGetMemoryStats is a no-op on RHIs that do not implement it, and the D3D12 RHI collects the stats only under STATS || CSV_PROFILER_STATS - true in every configuration except Shipping. Transcoding is driven from the editor, which has no Shipping configuration, so in practice the pool is always available; the fallback below exists because this module is Runtime-type and so still compiles into a packaged game. When the stats are unavailable the budget falls back to physical memory alone and FFrameMemoryBudget::bGpuSharedConsulted stays false.

#### struct `UE::TmvMedia::FFrameMemoryCost`  
`struct FFrameMemoryCost`  
_L38-45_
- desc: What one in-flight frame costs, per pool. Stated separately because the pools charge for different things: a readback frame occupies the GPU-shared heap only for its staging, while its host cost also covers the CPU copy handed to the encoder and the decoder's read-ahead. Collapsing the two into one figure and testing it against the tighter pool understates what fits in the GPU-shared pool by the whole host multiplier.
- L41 _public member_ `uint64 HostBytes = 0;` — Peak physical-memory footprint of one in-flight frame, including any GPU staging.
- L44 _public member_ `uint64 GpuSharedBytes = 0;` — Portion of the frame held in GPU-shared memory. 0 for stages that never stage through the GPU.

#### struct `UE::TmvMedia::FFrameMemoryBudget`  
`struct FFrameMemoryBudget`  
_L48-92_
- desc: How much memory one in-flight frame needs, against how much the stage may use.
- L51 _public member_ `FFrameMemoryCost Cost;` — The per-pool cost this budget was computed against.
- L54 _public member_ `float Fraction = 0.0f;` — Fraction of each pool's free memory the in-flight set may occupy, after clamping.
- L57 _public member_ `uint64 AvailablePhysical = 0;` — OS physical memory currently available.
- L63 _public member_ `uint64 AvailableGpuShared = 0;` — GPU-shared memory currently available. Only meaningful when bGpuSharedConsulted is true, and legitimately 0 there: the RHI clamps it to zero once the pool is over budget.
- L70 _public member_ `uint64 GpuSharedOverBudget = 0;` — How far the GPU-shared pool is past its budget, when it is. Non-zero only alongside an AvailableGpuShared of 0, and separates "exactly no headroom left" from "already well over" - the first thing worth knowing when a budget collapses.
- L73 _public member_ `uint64 AllowedFrames = 0;` — Frames that fit, before the caller's own ceiling. MAX_uint64 when a frame costs nothing.
- L76 _public member_ `EFrameMemoryPool BindingPool = EFrameMemoryPool::Host;` — The pool that allowed the fewest frames, and so decided the budget.
- L79 _public member_ `uint64 BytesPerFrame = 0;` — BindingPool's per-frame cost, budgeted share and free memory: the numbers that decided.
- L80 _public member_ `uint64 BudgetedBytes = 0;`
- L81 _public member_ `uint64 Available = 0;`
- L88 _public member_ `bool bGpuSharedConsulted = false;` — True when the GPU-shared pool was charged for and the RHI reported usable stats. False means the budget rests on physical memory alone - either the frame has no GPU-shared cost, or the stats were unavailable in this build/RHI.
- L91 _public member_ `bool bFitsSingleFrame = true;` — False when a single in-flight frame exceeds the budgeted share of any pool it draws on.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TmvMedia` (scope `UE`)
- L95 _prototype_ `bool IsMemoryAwareConcurrencyEnabled();` (scope `UE::TmvMedia`) — Returns whether transcode stages should size their concurrency to available memory.
- L102 _prototype_ `FFrameMemoryBudget ComputeFrameMemoryBudget(const FFrameMemoryCost& InCost, float InBudgetFraction);` (scope `UE::TmvMedia`) — Budgets one in-flight frame against live memory stats, charging each pool only for the part of the frame that lives in it. InCost is the caller's own peak estimate, since each stage holds a different mix of buffers. The GPU-shared pool is consulted only when InCost charges it.
- L108 _prototype_ `FString DescribeBudgetPools(const FFrameMemoryBudget& InBudget);` (scope `UE::TmvMedia`) — Describes the pools behind the budget, naming the one that bound it. For logs and error reporting: which pool ran out is the question every budget-driven clamp or refusal raises.
- L114 _prototype_ `int32 ClampConcurrencyToBudget(const FFrameMemoryBudget& InBudget, int32 InRequestedFrames, const TCHAR* InLogContext);` (scope `UE::TmvMedia`) — Converts a budget into a frame count, never exceeding InRequestedFrames and never below 1, and logs the decision. InLogContext names the calling stage.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Private/Utils/TmvMediaGpuReadback.h` (Private)


#### struct `FTmvMediaTextureReadbackParams`  
`struct FTmvMediaTextureReadbackParams`  
_L22-35_
- desc: Parameters for the readback copy request.
- L25 _public member_ `FIntVector Size = FIntVector::ZeroValue;` — Number of texels to copy. By default, it will copy the whole resource if no size is specified.
- L28 _public member_ `FIntVector SourcePosition = FIntVector::ZeroValue;` — Position to read from in the source texture.
- L31 _public member_ `uint32 SourceSlice = 0;` — Indicate which slice to read from.
- L34 _public member_ `uint32 SourceMip = 0;` — Indicate which mip to read from.

#### class `FTmvMediaGpuReadback`  
`class FTmvMediaGpuReadback`  
_L50-114_
- desc: Represents a readback request scheduled with CopyToStagingBuffer Wraps a staging buffer with a FRHIGPUFence for synchronization. Forked from FRHIGPUMemoryReadback / FRHIGPUTextureReadback, which diverge in four ways: - EnqueueCopy takes a source mip index; - Lock/Unlock may run outside the render thread where the RHI allows it, keeping the readback copy off the render thread on those platforms. Gated on SupportsAnyThreadReadback, which is false on Metal; callers must branch on it rather than assume, since Lock returns nullptr and Unlock is fatal if called off the render thread where it is unsupported; - staging reuse revalidates extent and format, not just dimension; - the deprecated Lock/Unlock overloads are dropped.
- L53 _public function_ `FTmvMediaGpuReadback(FName InRequestName)`
- L59 _public prototype_ `virtual ~FTmvMediaGpuReadback() = default;`
- L62 _public function_ `bool IsReady()` — Indicates if the data is in place and ready to be read.
- L68 _public function_ `bool IsReady(FRHIGPUMask InGPUMask)` — Indicates if the data is in place and ready to be read on a subset of GPUs.
- L74 _public function_ `void ResetReady()` — Reset the ready state
- L83 _public function_ `void Wait(FRHICommandListImmediate& InRHICmdList, FRHIGPUMask InGPUMask) const` — Block until the readback is ready.
- L97 _public prototype_ `virtual void EnqueueCopy(FRHICommandList& InRHICmdList, FRHITexture* InSourceTexture, const FTmvMediaTextureReadbackParams& InReadbackParams) = 0;` — Copy the current state of the resource to the readback data. @param InRHICmdList The command list to enqueue the copy request on. @param InSourceTexture The texture holding the source data. @param InReadbackParams Description of all source parameters (size, position, mip, slice) to readback from.
- L99 _public function_ `const FRHIGPUMask& GetLastCopyGPUMask() const`
- L101 _public function_ `FName GetName() const`
- L105 _protected member_ `FGPUFenceRHIRef Fence;`
- L106 _protected member_ `FRHIGPUMask LastCopyGPUMask;`
- L113 _protected member_ `uint32 LastLockGPUIndex;` — We need to separately track which GPU buffer was last locked.  It's possible for a new copy operation to be enqueued (writing to LastCopyGPUMask) while the buffer is technically locked, with the unlock and enqueued copy on the GPU itself happening later, during pass execution in FRDGBuilder::Execute (for example, this happens with Nanite streaming).  It's not unsafe, because the operations are occurring in order on both the render thread and later pass Execute, but our locking logic needs to handle that scenario.

#### class `FTmvMediaGpuTextureReadback`  
`class FTmvMediaGpuTextureReadback final : public FTmvMediaGpuReadback`  
_L117-145_
- inherits: `FTmvMediaGpuReadback`
- desc: Texture readback implementation.
- L120 _public prototype_ `FTmvMediaGpuTextureReadback(FName InRequestName);`
- L125 _public prototype_ `virtual void EnqueueCopy(FRHICommandList& InRHICmdList, FRHITexture* InSourceTexture, const FTmvMediaTextureReadbackParams& InReadbackParams) override;`
- L132 _public prototype_ `static bool SupportsAnyThreadReadback();` — Some RHI implementation support locking/unlocking the staging buffers outside the render thread. If it is the case, this function will return true.
- L135 _public prototype_ `void* Lock(int32& OutRowPitchInPixels, int32* OutBufferHeight = nullptr);` — Locks the staging buffer and returns a memory pointer. Can be called on any thread if supported.
- L138 _public prototype_ `void Unlock();` — Releases the staging buffer. Can be called on any thread if supported.
- L141 _public prototype_ `uint64 GetGPUSizeBytes() const;` — Returns the total size in bytes of the memory buffer.
- L144 _public member_ `FTextureRHIRef DestinationStagingTextures[MAX_NUM_GPUS];` — Array of staging textures per gpu.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Decoder/ITmvMediaDecoder.h` (Public)


#### enum `ETmvMediaDecoderResult`  
`enum class ETmvMediaDecoderResult`  
_L14-20_
- desc: Decoder return code.
- L16 _public enumerator_ `Success`
- L17 _public enumerator_ `Fail`
- L18 _public enumerator_ `Cancelled`
- L19 _public enumerator_ `Skipped`

#### class `ITmvMediaDecoderAccessUnit`  
`class ITmvMediaDecoderAccessUnit`  
_L28-74_
- desc: Interface for the decoder's access unit. This is used by the decoder to read data from the input buffer. It is abstracted as an input stream so that the access unit doesn't have to be fully loaded in memory. With this, we should be able to encapsulate access units from different parser implementations (containers or separate files).
- L31 _public prototype_ `virtual ~ITmvMediaDecoderAccessUnit() = default;`
- L36 _public prototype_ `virtual int64 Tell() const = 0;` — Returns the offset in bytes from the start of the access unit.
- L41 _public prototype_ `virtual int64 GetTotalSize() const = 0;` — Returns the total size in bytes of the access unit.
- L48 _public prototype_ `virtual bool Seek(int64 InOffset) = 0;` — Seek at the specified offset in bytes from the start of the access unit. @param InOffset Offset in bytes. @return true if the operation completed successfully, false otherwise.
- L57 _public prototype_ `virtual int64 Read(void *OutBuffer, int64 InSize) = 0;` — Read from the current position the specified amount of data. @param OutBuffer Destination buffer @param InSize Size in bytes that will be read. @return Size read.
- L62 _public prototype_ `virtual int32 GetFrameId() const = 0;` — Returns the frame id for this access unit.
- L67 _public prototype_ `virtual const FString& GetFilename() const = 0;` — Returns the filename. (TMP)
- L73 _public prototype_ `virtual FArchive* GetUnderlyingArchive() const = 0;` — Directly access the underlying archive. (TMP) This is expected to be an archive for only the access unit (not the whole container).

#### struct `FTmvMediaDecoderMipRequest`  
`struct FTmvMediaDecoderMipRequest`  
_L79-95_
- desc: Mip decoding request.
- L82 _public member_ `FTmvMediaFrameMipInfo MipInfo;` — Mip Info
- L85 _public member_ `TArray<FIntRect> TileRegions;` — Specify the tile regions to load.
- L88 _public member_ `FTmvMediaFrameMipBufferHandle MipBuffer;` — Destination mip buffer.
- L91 _public member_ `ETmvMediaDecoderResult OutResult = ETmvMediaDecoderResult::Fail;` — (Set by decoder) Result of the decoding operation.
- L94 _public member_ `int32 OutNumTilesDecoded = 0;` — (Set by decoder) Number of tiles decoded.

#### class `ITmvMediaParser`  
`class ITmvMediaParser`  
_L102-117_
- desc: TMV access unit parser interface.
- L105 _public function_ `virtual ~ITmvMediaParser()`
- L113 _public prototype_ `virtual ETmvMediaDecoderResult ParseMipInfos(ITmvMediaDecoderAccessUnit& InAccessUnit, TArray<FTmvMediaFrameMipInfo>& OutMipInfos) = 0;` — Parse the access unit for the mip infos. @param InAccessUnit Access unit for the current frame's encoded stream. @param OutMipInfos Populated array of mip information. @return result of the operation.

#### class `ITmvMediaDecoder`  
`class ITmvMediaDecoder`  
_L124-136_
- desc: TMV (Tile-Based) Decoder interface. Reads data from the input access unit and decode the requested mips and tiles.
- L127 _public function_ `virtual ~ITmvMediaDecoder()`
- L135 _public prototype_ `virtual ETmvMediaDecoderResult Decode(ITmvMediaDecoderAccessUnit& InAccessUnit, TArrayView<FTmvMediaDecoderMipRequest> InMipRequests) = 0;` — Decode the given mip requests. @param InAccessUnit Access unit for the current frame's encoded stream. @param InMipRequests Array of mip decoding requests. @return Result code depending on the success of the operation.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Decoder/ITmvMediaDecoderFactory.h` (Public)


#### class `ITmvMediaDecoderFactory`  
`class ITmvMediaDecoderFactory`  
_L17-67_
- desc: Interface for a ITmvMediaDecoder factory.
- L20 _public prototype_ `virtual ~ITmvMediaDecoderFactory() = default;`
- L25 _public prototype_ `virtual const FString& GetName() const = 0;` — Returns the name of this decoder implementation.
- L30 _public prototype_ `virtual TArray<FString> GetSupportedFileExtensions() const = 0;` — Return the list of file extensions this factory supports.
- L38 _public prototype_ `virtual int32 SupportsFormat(const FString& InCodecFormat, const TMap<FString, FVariant>& InOptions) const = 0;` — Queries support status of the given codec. @param InCodecFormat FOURCC of the codec, ex: "aPv1" @param InOptions Additional options may be provided to specify the format more closely, which may help selecting the best suited implementation. @return 0 if not supported. If supported, the return value indicates a priority value for the implementation.
- L44 _public prototype_ `virtual void GetParserOptions(TMap<FString, FVariant>& OutOptions) const = 0;` — Populates the provided map with parser configuration options. @param OutOptions Populated options.
- L52 _public prototype_ `virtual TSharedPtr<ITmvMediaParser, ESPMode::ThreadSafe> CreateParser(const FString& InCodecFormat, const TMap<FString, FVariant>& InOptions) = 0;` — Creates a parser for the given access unit format. @param InCodecFormat Either FOURCC of codec or filename extension of the container. @param InOptions Additional options may be provided to specify the format more closely, which may help selecting the best suited implementation. @return created parser or null if failed.
- L58 _public prototype_ `virtual void GetDecoderOptions(TMap<FString, FVariant>& OutOptions) const = 0;` — Populates the provided map with decoder configuration options. @param OutOptions Populated options.
- L66 _public prototype_ `virtual TSharedPtr<ITmvMediaDecoder, ESPMode::ThreadSafe> CreateDecoder(const FString& InCodecFormat, const TMap<FString, FVariant>& InOptions) = 0;` — Creates a decoder for the given format and options. @param InCodecFormat Either FOURCC of the codec, ex: "aPv1", or file extension (if each AU is a separate file). @param InOptions Additional options may be provided to specify the format more closely, which may help selecting the best suited implementation. @return created decoder, or null if failed.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Decoder/ITmvMediaDemuxer.h` (Public)


#### struct `FTmvMediaDemuxerTrackInfo`  
`struct FTmvMediaDemuxerTrackInfo : public FTmvMediaTrackInfo`  
_L16-29_
- inherits: `FTmvMediaTrackInfo`
- desc: Information about a single track in a demuxed container. Extends the common track descriptor with demuxer-specific fields.
- L19 _public member_ `int32 TrackIndex = -1;` — Track index (0-based).
- L22 _public member_ `int64 Duration = 0;` — Total duration of the track in its timescale units.
- L25 _public member_ `uint32 NumSamples = 0;` — Total number of samples in this track.
- L28 _public member_ `FString LanguageCode;` — Language code (3-letter ISO 639-2T).

#### struct `FTmvMediaDemuxerSample`  
`struct FTmvMediaDemuxerSample : public FTmvMediaTrackSampleInfo`  
_L35-45_
- inherits: `FTmvMediaTrackSampleInfo`
- desc: A single sample read from a demuxed container. Extends the common sample metadata with demuxer-specific fields.
- L38 _public member_ `TArray64<uint8> Data;` — Raw coded sample data.
- L41 _public member_ `int64 FileOffset = 0;` — File byte offset of this sample.
- L44 _public member_ `int64 SampleSize = 0;` — Size in bytes (matches Data.Num() when data is populated).

#### class `ITmvMediaDemuxer`  
`class ITmvMediaDemuxer`  
_L63-153_
- desc: Abstract interface for demuxing media samples from a container. Workflow: 1. Open() the container (from file path or from memory buffer). 2. GetTrackCount() / GetTrackInfo() to enumerate available tracks. 3. ReadSample() to iterate through samples on a given track. 4. Seek() to jump to a particular time or keyframe. 5. Close() when done. The demuxer extracts raw coded samples (access units) from the container that can then be fed into ITmvMediaDecoder for decoding. Thread safety: implementations are NOT internally synchronized. Callers must serialize all calls to the same demuxer instance (e.g. with a mutex).
- L66 _public prototype_ `virtual ~ITmvMediaDemuxer() = default;`
- L74 _public prototype_ `virtual ETmvMediaContainerResult OpenFile(const FString& InFilePath) = 0;` — Open a container from a file path. Parses the container structure and prepares track metadata. @param InFilePath Absolute path to the container file. @return Success if the container was parsed successfully.
- L81 _public prototype_ `virtual ETmvMediaContainerResult OpenBuffer(TConstArrayView<uint8> InData) = 0;` — Open a container from an in-memory buffer. @param InData Buffer containing the complete container data. @return Success if the container was parsed successfully.
- L86 _public prototype_ `virtual int32 GetTrackCount() const = 0;` — Returns the number of tracks found in the container.
- L94 _public prototype_ `virtual ETmvMediaContainerResult GetTrackInfo(int32 InTrackIndex, FTmvMediaDemuxerTrackInfo& OutTrackInfo) const = 0;` — Retrieve metadata for a specific track. @param InTrackIndex Track index (0-based, must be < GetTrackCount()). @param OutTrackInfo Populated track information. @return Success if the track info was retrieved.
- L103 _public prototype_ `virtual ETmvMediaContainerResult ReadSample(int32 InTrackIndex, FTmvMediaDemuxerSample& OutSample) = 0;` — Read the next sample from the specified track. Advances the internal read position for that track. @param InTrackIndex Track index. @param OutSample Populated with the sample data and metadata. @return Success if a sample was read, EndOfStream if no more samples.
- L112 _public prototype_ `virtual ETmvMediaContainerResult ReadSampleInfo(int32 InTrackIndex, FTmvMediaDemuxerSample& OutSample) = 0;` — Read only the sample metadata (no data copy) from the specified track. Useful for building sample tables or scanning without loading sample data. @param InTrackIndex Track index. @param OutSample Populated with metadata (Data array will be empty, SampleSize set). @return Success if metadata was read, EndOfStream if no more samples.
- L122 _public prototype_ `virtual ETmvMediaContainerResult Seek(int32 InTrackIndex, FTimespan InTime, FTimespan InLaterTimeThreshold = FTimespan::Zero()) = 0;` — Seek to a keyframe at or before the given time. After seeking, the next ReadSample call will return the keyframe sample. @param InTrackIndex Track index. @param InTime Target time. @param InLaterTimeThreshold If a keyframe is found within this threshold after InTime, prefer it. @return Success if a valid seek point was found.
- L130 _public prototype_ `virtual ETmvMediaContainerResult SeekToSample(int32 InTrackIndex, uint32 InSampleNumber) = 0;` — Seek to a specific sample number. @param InTrackIndex Track index. @param InSampleNumber Target sample number (0-based). @return Success if the sample number is valid.
- L135 _public prototype_ `virtual void Close() = 0;` — Close the container and release resources.
- L140 _public prototype_ `virtual FString GetLastError() const = 0;` — Returns a human-readable error message if the last operation failed.
- L146 _public function_ `virtual TOptional<FString> GetStartTimecode() const` — Returns the start timecode as a formatted string (e.g., "01:00:00:00"), if available. Must be called after Open.
- L152 _public function_ `virtual TOptional<FString> GetStartTimecodeRate() const` — Returns the start timecode frame rate as a string (e.g., "30000/1001"), if available. Must be called after Open.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Decoder/ITmvMediaDemuxerFactory.h` (Public)


#### class `ITmvMediaDemuxerFactory`  
`class ITmvMediaDemuxerFactory`  
_L16-38_
- desc: Interface for an ITmvMediaDemuxer factory.
- L19 _public prototype_ `virtual ~ITmvMediaDemuxerFactory() = default;`
- L22 _public prototype_ `virtual FName GetName() const = 0;` — Returns the name of this demuxer implementation.
- L25 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the display name of this demuxer implementation.
- L31 _public prototype_ `virtual TArray<FString> GetSupportedContainerFormats() const = 0;` — Return the list of container format identifiers this factory supports. Ex: "mp4", "fmp4", "mov"
- L37 _public prototype_ `virtual TSharedPtr<ITmvMediaDemuxer, ESPMode::ThreadSafe> CreateDemuxer() = 0;` — Creates a demuxer instance. @return Created demuxer, or null if failed.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Encoder/ITmvMediaEncoder.h` (Public)


#### enum `ETmvMediaEncoderResult`  
`enum class ETmvMediaEncoderResult`  
_L19-25_
- desc: Encoder return code.
- L21 _public enumerator_ `Success`
- L22 _public enumerator_ `Fail`
- L23 _public enumerator_ `Cancelled`
- L24 _public enumerator_ `Skipped`

#### class `ITmvMediaEncoderAccessUnit`  
`class ITmvMediaEncoderAccessUnit`  
_L31-77_
- desc: Interface for the encoder's access unit. This is used by the encoder to write data to the output buffer.
- L34 _public prototype_ `virtual ~ITmvMediaEncoderAccessUnit() = default;`
- L39 _public prototype_ `virtual int64 Tell() const = 0;` — Returns the offset in bytes from the start of the access unit.
- L44 _public prototype_ `virtual int64 GetTotalSize() const = 0;` — Returns the total size in bytes of the access unit.
- L51 _public prototype_ `virtual bool Seek(int64 InOffset) = 0;` — Seek at the specified offset in bytes from the start of the access unit. @param InOffset Offset in bytes. @return true if the operation completed successfully, false otherwise.
- L60 _public prototype_ `virtual int64 Write(const void *InBuffer, int64 InSize) = 0;` — Write the give data to the current position the specified amount of data. @param InBuffer Source buffer @param InSize Size in bytes that will be written. @return Size written.
- L65 _public prototype_ `virtual int32 GetFrameId() const = 0;` — Returns the frame id for this access unit.
- L70 _public prototype_ `virtual const FString& GetFilename() const = 0;` — Returns the filename. (TMP)
- L76 _public prototype_ `virtual FArchive* GetUnderlyingArchive() const = 0;` — Directly access the underlying archive. (TMP) This is expected to be an archive for only the access unit (not the whole container).

#### struct `FTmvMediaEncoderMipRequest`  
`struct FTmvMediaEncoderMipRequest`  
_L82-89_
- desc: Mip encoding request.
- L85 _public member_ `FTmvMediaFrameMipBufferHandle MipBuffer;` — Mip buffer to encode.
- L88 _public member_ `ETmvMediaEncoderResult OutResult = ETmvMediaEncoderResult::Fail;` — (Set by encoder) Result of the encoding operation.

#### struct `FTmvMediaEncoderMipInfo`  
`struct FTmvMediaEncoderMipInfo`  
_L96-115_
- desc: All the parameters needed to request a mip memory layout for the encoder.
- L99 _public member_ `int32 Width = 0;` — Width of the largest mip for the frame.
- L102 _public member_ `int32 Height = 0;` — Height of the largest mip for the frame.
- L108 _public member_ `bool bEnableMips = false;` — Indicate if mip info must be generated. The encoder will determine which mip can be produced (if possible at all).
- L114 _public member_ `FTmvMediaFrameColorInfo ColorInfo;` — Color Specification to be encoded in the frame headers. Note: Not all encoders can save all the color space info (if any at all).

#### class `ITmvMediaEncoder`  
`class ITmvMediaEncoder`  
_L122-157_
- desc: TMV (Tile-Based) Encoder interface. Encodes data from the provided mip buffers and writes encoded bytes to the output access unit.
- L125 _public function_ `virtual ~ITmvMediaEncoder()`
- L137 _public prototype_ `virtual ETmvMediaEncoderResult RequestMipInfos( const FTmvMediaFrameTimeInfo& InTimeInfo, const FTmvMediaEncoderMipInfo& InFrameInfo, TArray<FTmvMediaFrameMipInfo>& OutFrameMipInfo, FTmvMediaMessageContext* OutMessageContext) = 0;` — Queries the encoder for the memory layout and format for frames of the given size, and doing so for each mips. Can fail if the encoder doesn't support the given input format. @param InTimeInfo Time information needed by some encoders to estimate bitrate and compression. @param InFrameInfo Mip0 information of incoming frame. @param OutFrameMipInfo output array populated with the request mip info. @param OutMessageContext Optional message context for the given operation. @return Result code depending on the success of the operation.
- L152 _public prototype_ `virtual ETmvMediaEncoderResult Encode( const FTmvMediaFrameTimeInfo& InTimeInfo, ITmvMediaEncoderAccessUnit& InAccessUnit, TArrayView<FTmvMediaEncoderMipRequest> InMipRequests, FTmvMediaMessageContext* OutMessageContext) = 0;` — Encode the given mip requests. @param InTimeInfo Time information needed by some encoders to encode in the frame. @param InAccessUnit Access unit for the current frame's encoded stream. @param InMipRequests Array of mip encoding requests. @param OutMessageContext Optional message context for the given operation. @return Result code depending on the success of the operation.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Encoder/ITmvMediaEncoderFactory.h` (Public)


#### class `ITmvMediaEncoderFactory`  
`class ITmvMediaEncoderFactory`  
_L15-50_
- desc: Interface for a ITmvMediaEncoder factory.
- L18 _public prototype_ `virtual ~ITmvMediaEncoderFactory() = default;`
- L23 _public prototype_ `virtual FName GetName() const = 0;` — Returns the name of this encoder implementation.
- L28 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the display name of this encoder implementation.
- L35 _public prototype_ `virtual bool SupportsMemoryAccessUnit() const = 0;` — Return true if the encoder supports memory only access unit interface. Some encoders can only write to file because of third party implementations and don't support having an intermediate memory access unit that can be muxed independently.
- L41 _public prototype_ `virtual void GetEncoderOptions(TInstancedStruct<FTmvMediaEncoderOptions>& OutOptions) const = 0;` — Populates the provided instanced struct with encoder configuration options. @param OutOptions Populated options.
- L49 _public prototype_ `virtual TSharedPtr<ITmvMediaEncoder, ESPMode::ThreadSafe> CreateEncoder(const FString& InCodecFormat, const TInstancedStruct<FTmvMediaEncoderOptions>& InOptions) = 0;` — Creates an encoder for the given format and options. @param InCodecFormat Either FOURCC of the codec, ex: "apv1", or file extension (if each AU is a separate file). @param InOptions Additional options may be provided to specify the format more closely, which may help selecting the best suited implementation. @return created encoder, or null if failed.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Encoder/ITmvMediaMuxer.h` (Public)


#### struct `FTmvMediaMuxerTrackConfig`  
`struct FTmvMediaMuxerTrackConfig : public FTmvMediaTrackInfo`  
_L19-35_
- inherits: `FTmvMediaTrackInfo`
- desc: Configuration for a single track in the muxer. Extends the common track descriptor with muxer-specific fields.
- L25 _public member_ `bool bIsAllKeyframes = true;` — If true, every sample in this track is independently decodable (sync sample). If false, samples may depend on other samples.
- L28 _public member_ `FString CompressorName;` — Optional compressor name string (video tracks only).
- L34 _public member_ `TOptional<uint32> SubSampleFlags;` — If set, enables subsample information for each sample. The value is the 24-bit flags for the subsample box.

#### struct `FTmvMediaMuxerConfig`  
`struct FTmvMediaMuxerConfig`  
_L40-68_
- desc: Configuration for the muxer output.
- L54 _public member_ `FString OutputFilename;` — Output file path.
- L57 _public member_ `FString TemporaryFilename;` — Temporary file path (required for WebOptimized mode).
- L60 _public member_ `EOutputMode OutputMode = EOutputMode::Standard;` — Output mode.
- L67 _public member_ `FTimespan InterleaveDuration = FTimespan::FromMilliseconds(500);` — Duration for interleaving chunks of sample data. Samples are collected per track until this duration is reached, then written. Typical value: 500ms.

#### enum `FTmvMediaMuxerConfig::EOutputMode`  
`enum class EOutputMode : uint8`  
_L43-51_
- desc: Output mode for the container.
- L46 _public enumerator_ `Standard` — Standard mode. Container metadata at end.
- L48 _public enumerator_ `WebOptimized` — Web-optimized mode. Container metadata at front (requires temporary file + 2nd pass).
- L50 _public enumerator_ `Fragmented` — Fragmented mode. Metadata interleaved with data.

#### struct `FTmvMediaMuxerSample`  
`struct FTmvMediaMuxerSample : public FTmvMediaTrackSampleInfo`  
_L74-93_
- inherits: `FTmvMediaTrackSampleInfo`
- desc: A single sample to be muxed into a track. Extends the common sample metadata with muxer-specific fields.
- L86 _public member_ `TConstArrayView64<uint8> Data;` — Raw coded sample data. Written verbatim to the container.
- L89 _public member_ `bool bIsFinalSample = false;` — Whether this is the final sample for this track.
- L92 _public member_ `TArray<FSubSampleInfo> SubSamples;` — Optional subsample information.

#### struct `FTmvMediaMuxerSample::FSubSampleInfo`  
`struct FSubSampleInfo`  
_L77-83_
- desc: Subsample information entry.
- L79 _public member_ `uint32 CodecSpecificParameters = 0;`
- L80 _public member_ `uint32 SubSampleSize = 0;`
- L81 _public member_ `uint8 SubSamplePriority = 0;`
- L82 _public member_ `uint8 Discardable = 0;`

#### class `ITmvMediaMuxer`  
`class ITmvMediaMuxer`  
_L108-193_
- desc: Abstract interface for muxing encoded access units into a media container. Workflow: 1. Configure() with output settings. 2. AddTrack() for each media track, receiving a track index. 3. Start() to begin the muxing process. 4. AddSample() for each sample on each track (called from the sample request callback). 5. Finalize() once all tracks signal their final sample. Sample delivery is asynchronous: the muxer calls back via FSampleRequestDelegate to request samples. The caller provides them via AddSample().
- L111 _public prototype_ `virtual ~ITmvMediaMuxer() = default;`
- L121 _public prototype_ `DECLARE_DELEGATE_OneParam(FSampleRequestDelegate, const TArray<FSampleRequest>& );` — Delegate invoked when the muxer needs samples for one or more tracks.
- L131 _public prototype_ `DECLARE_DELEGATE_OneParam(FStatusDelegate, EStatus );` — Delegate invoked when muxing completes or fails.
- L139 _public prototype_ `virtual ETmvMediaContainerResult Configure(const FTmvMediaMuxerConfig& InConfig) = 0;` — Configure the muxer with output settings. Must be called before AddTrack(). @param InConfig Muxer configuration. @return Success if configuration is valid, Fail otherwise.
- L147 _public prototype_ `virtual int32 AddTrack(const FTmvMediaMuxerTrackConfig& InTrackConfig) = 0;` — Add a track to the container. Must be called after Configure() and before Start(). @param InTrackConfig Track configuration. @return Track index (>= 0) on success, or -1 on failure.
- L152 _public function_ `virtual bool SupportsStartTimecode() const` — Whether this muxer supports writing a start timecode into the container.
- L163 _public function_ `virtual bool SetStartTimecode(const FTimecode& InTimecode, const FFrameRate& InFrameRate)` — Set the starting timecode to be written into the container. Must be called after Configure() and before Start(). Implementations decide how to represent the timecode in their container format (e.g., as a timecode track, user-data metadata, or not at all). @param InTimecode The starting timecode. @param InFrameRate The frame rate associated with the timecode. @return true if the timecode was accepted, false on error.
- L172 _public prototype_ `virtual ETmvMediaContainerResult Start(FSampleRequestDelegate InSampleRequestDelegate, FStatusDelegate InStatusDelegate) = 0;` — Start the muxing process. The muxer will begin calling InSampleRequestDelegate to request samples. @param InSampleRequestDelegate Called when the muxer needs more sample data. @param InStatusDelegate Called when muxing completes or fails. @return Success if started, Fail otherwise.
- L181 _public prototype_ `virtual ETmvMediaContainerResult AddSample(int32 InTrackIndex, const FTmvMediaMuxerSample& InSample) = 0;` — Provide a sample to the muxer for the specified track. Called in response to FSampleRequestDelegate. @param InTrackIndex Index returned by AddTrack(). @param InSample The sample data and metadata. @return Success if the sample was accepted.
- L187 _public prototype_ `virtual ETmvMediaContainerResult Finalize() = 0;` — Stop muxing and finalize the output file. @return Success if the file was closed properly.
- L192 _public prototype_ `virtual FString GetLastError() const = 0;` — Returns a human-readable error message if the last operation failed.

#### struct `ITmvMediaMuxer::FSampleRequest`  
`struct FSampleRequest`  
_L114-118_
- desc: Defines an entry in the sample request array indicating which track needs a sample.
- L116 _public member_ `int32 TrackIndex = -1;`
- L117 _public member_ `uint32 SampleNumber = 0;`

#### enum `ITmvMediaMuxer::EStatus`  
`enum class EStatus`  
_L124-128_
- desc: Status reported upon completion or failure.
- L126 _public enumerator_ `Failed`
- L127 _public enumerator_ `Finished`

#### Free symbols / members of external scopes

- L121 _delegate_ `DECLARE_DELEGATE_OneParam(FSampleRequestDelegate, const TArray<FSampleRequest>& );` — Delegate invoked when the muxer needs samples for one or more tracks.
- L131 _delegate_ `DECLARE_DELEGATE_OneParam(FStatusDelegate, EStatus );` — Delegate invoked when muxing completes or fails.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Encoder/ITmvMediaMuxerFactory.h` (Public)


#### class `ITmvMediaMuxerFactory`  
`class ITmvMediaMuxerFactory`  
_L16-44_
- desc: Interface for an ITmvMediaMuxer factory.
- L19 _public prototype_ `virtual ~ITmvMediaMuxerFactory() = default;`
- L22 _public prototype_ `virtual FName GetName() const = 0;` — Returns the name of this muxer implementation.
- L25 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the display name of this muxer implementation.
- L31 _public prototype_ `virtual TArray<FString> GetSupportedContainerFormats() const = 0;` — Return the list of container format identifiers this factory supports. Ex: "tmv"
- L37 _public prototype_ `virtual FString GetFileExtension() const = 0;` — Returns the file extension for the output container (without leading dot). Ex: "tmv"
- L43 _public prototype_ `virtual TSharedPtr<ITmvMediaMuxer, ESPMode::ThreadSafe> CreateMuxer() = 0;` — Creates a muxer instance. @return Created muxer, or null if failed.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Encoder/TmvMediaEncoderOptions.h` (Public)


#### enum `ETmvMediaEncoderEncoding`  
`enum class ETmvMediaEncoderEncoding : uint8`  
_L15-29_
- reflection: `UENUM()`
- desc: List of supported encoder transfer functions (a.k.a encodings), matching the list in ColorManagementDefines.h.
- L18 _public enumerator_ `None = 0` — Unspecified (no override).
- L20 _public enumerator_ `Linear = 1` — Linear encoding.
- L22 _public enumerator_ `sRGB = 2 UMETA(DisplayName="sRGB")` — sRGB encoding.
- L24 _public enumerator_ `ST2084 = 3 UMETA(DisplayName="ST 2084/PQ")` — SMPTE ST 2084/PQ: input is absolute nits. Paired with ReferenceWhite BT.2408 by default.
- L26 _public enumerator_ `SLog3 = 12` — Sony S-Log3 encoding.
- L28 _public enumerator_ `HLG = 17` — HLG (BT.2100): input is normalized in the [0, 1] range. Paired with ReferenceWhite BT.2408 by default.

#### enum `ETmvMediaEncoderReferenceWhite`  
`enum class ETmvMediaEncoderReferenceWhite : uint8`  
_L35-47_
- reflection: `UENUM()`
- desc: Reference-white standards for HDR encoder input. Integer values match UE::Color::EReferenceWhite.
- L38 _public enumerator_ `None = 0` — The source reference white is not overridden, defer to system/default behavior.
- L40 _public enumerator_ `DisableNormalization = 1 UMETA(DisplayName = "Disable Normalization")` — Explicitly preserve input/native scaling.
- L42 _public enumerator_ `BT2408 = 2 UMETA(DisplayName = "BT.2408 (203 nits)")` — ITU-R BT.2408 Reference White. 203 cd/m2 for PQ (ST2084), 75% signal for HLG scale to scene linear white (1.0).
- L44 _public enumerator_ `BT1886 = 3 UMETA(DisplayName = "BT.1886 (100 nits)")` — ITU-R BT.1886 SDR reference white (100 cd/m2). Scales PQ (100-nit paper white) and HLG (in-house 100-nit convention on a 1000 cd/m2 BT.2100 reference display) to scene linear white (1.0).
- L46 _public enumerator_ `Max = 4 UMETA(Hidden)`

#### enum `ETmvMediaEncoderColorMatrix`  
`enum class ETmvMediaEncoderColorMatrix : uint8`  
_L54-66_
- reflection: `UENUM()`
- desc: Carries the information about the YUV conversion matrix. Note: this is independent of the color space. YUV conversion is done prior to the application of the transfer function.
- L57 _public enumerator_ `None = 0` — Unspecified (no override).
- L59 _public enumerator_ `Identity = 1` — Identity, i.e. no yuv conversion (rgb color model).
- L61 _public enumerator_ `Rec601 = 2 UMETA(DisplayName="Rec601")` — Rec. ITU-R BT.601-7 525 (Kr = 0.299, Kb = 0.114)
- L63 _public enumerator_ `Rec709 = 3 UMETA(DisplayName="Rec709")` — Rec. ITU-R BT.709-6 (Kr = 0.2126, Kb = 0.0722)
- L65 _public enumerator_ `Rec2020 = 4 UMETA(DisplayName="Rec2020")` — Rec. ITU-R BT.2020-2 (Kr = 0.2627, Kb = 0.0593)

#### enum `ETmvMediaEncoderColorMatrixRange`  
`enum class ETmvMediaEncoderColorMatrixRange : uint8`  
_L72-84_
- reflection: `UENUM()`
- desc: Carries the information about the range of the YUV conversion matrix (Scaled vs UnScaled)
- L78 _public enumerator_ `Limited` — Limited (studio) range, defined by spec. Typical [16, 235] for luma on 8 bits limited range. This range definition corresponds to the "scaled" yuv matrices and offsets from MediaShaders.
- L83 _public enumerator_ `Full` — Full [0, 255] range. This range definition corresponds to the "unscaled" yuv matrices and offsets from MediaShaders.

#### struct `FTmvMediaEncoderOptions`  
`struct FTmvMediaEncoderOptions`  
_L90-140_
- reflection: `USTRUCT()`
- desc: Encoder options.
- L95 _public function_ `virtual FName GetEncoderName() const` — Returns the encoder name used to find the corresponding factory.
- L98 _public function_ `virtual FString GetFileSequenceExtension() const` — Returns the extension used for saving to file sequence.
- L101 _public function_ `virtual uint32 GetCodecFourCC() const` — Returns the FOURCC sample entry format identifying the codec (e.g. 'apv1'). Used for container muxing.
- L106 _public function_ `virtual void GetSupportedDestinationColorSpaces(TArray<ETextureColorSpace>& OutSupportedColorSpaces) const` — Returns the destination color spaces supported by this encoder. An empty array means all values are allowed.
- L111 _public function_ `virtual void GetSupportedDestinationEncodings(TArray<ETmvMediaEncoderEncoding>& OutSupportedEncodings) const` — Returns the destination encodings (transfer functions) supported by this encoder. An empty array means all values are allowed.
- L113 _public prototype_ `virtual ~FTmvMediaEncoderOptions() = default;`
- L119 _public member_ `bool bEnableColorManagement = false;` — `UPROPERTY(EditAnywhere, Category = "Color Management")` — Enables the color management specification for the encoder.
- L123 _public member_ `ETextureColorSpace DestinationColorSpace = ETextureColorSpace::TCS_None;` — `UPROPERTY(EditAnywhere, Category = "Color Management", meta = (EditCondition = "bEnableColorManagement", EditConditionHides))` — Specify the destination color space.
- L127 _public member_ `ETmvMediaEncoderEncoding DestinationEncoding = ETmvMediaEncoderEncoding::Linear;` — `UPROPERTY(EditAnywhere, Category = "Color Management", meta = (EditCondition = "bEnableColorManagement", EditConditionHides))` — Specify the destination color encoding.
- L131 _public member_ `ETmvMediaEncoderReferenceWhite ReferenceWhite = ETmvMediaEncoderReferenceWhite::BT2408;` — `UPROPERTY(EditAnywhere, Category = "Color Management", meta = (EditCondition = "bEnableColorManagement && (DestinationEncoding == ETmvMediaEncoderEncoding::ST2084 || DestinationEncoding == ETmvMediaEncoderEncoding::HLG)", EditConditionHides))` — Reference-white standard used to scale UE scene-linear 1.0 to diffuse white.
- L135 _public member_ `ETmvMediaEncoderColorMatrix YuvMatrix = ETmvMediaEncoderColorMatrix::Identity;` — `UPROPERTY(EditAnywhere, Category = "Color Management", meta = (EditCondition = "bEnableColorManagement", EditConditionHides))` — Specify the YUV encoding color matrix.
- L139 _public member_ `ETmvMediaEncoderColorMatrixRange YuvMatrixRange = ETmvMediaEncoderColorMatrixRange::Full;` — `UPROPERTY(EditAnywhere, Category = "Color Management", meta = (EditCondition = "bEnableColorManagement", EditConditionHides))` — Specify the YUV encoding color matrix range.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/ITmvMediaModule.h` (Public)


#### class `ITmvMediaModule`  
`class ITmvMediaModule : public IModuleInterface`  
_L22-128_
- inherits: `IModuleInterface`
- desc: Interface for the Tiled-Mipmap Video (TMV) module.
- L28 _public prototype_ `static ITmvMediaModule* Get();` — Returns a pointer to the module instance if loaded, null otherwise.
- L34 _public prototype_ `static ITmvMediaModule& GetOrLoad();` — Returns existing instance of the module, loads it if it was not already loaded. Beware of calling this during the shutdown phase, though. The module might have been unloaded already.
- L39 _public prototype_ `virtual void RegisterDecoderFactory(TSharedPtr<ITmvMediaDecoderFactory, ESPMode::ThreadSafe> InDecoderFactory) = 0;` — Register a decoder factory in the module.
- L44 _public prototype_ `virtual void UnregisterDecoderFactory(TSharedPtr<ITmvMediaDecoderFactory, ESPMode::ThreadSafe> InDecoderFactory) = 0;` — Unregister a decoder factory from the module.
- L49 _public prototype_ `virtual void GetDecoderFactories(TArray<TWeakPtr<ITmvMediaDecoderFactory, ESPMode::ThreadSafe>>& OutDecoderFactories) const = 0;` — Get a list of all currently registered factories.
- L57 _public prototype_ `virtual TSharedPtr<ITmvMediaDecoderFactory, ESPMode::ThreadSafe> GetBestDecoderFactoryForFormat(const FString& InCodecFormat, const TMap<FString, FVariant>& InOptions) const = 0;` — Returns the best decoder factory for the given format. @param InCodecFormat FOURCC of the codec, ex: "aPv1" @param InOptions Additional options may be provided to specify the format more closely, which may help selecting the best suited implementation. @return Highest priority decoder factory if found, null otherwise.
- L62 _public prototype_ `virtual void RegisterEncoderFactory(TSharedPtr<ITmvMediaEncoderFactory, ESPMode::ThreadSafe> InEncoderFactory) = 0;` — Register an encoder factory in the module.
- L67 _public prototype_ `virtual void UnregisterEncoderFactory(TSharedPtr<ITmvMediaEncoderFactory, ESPMode::ThreadSafe> InEncoderFactory) = 0;` — Unregister an encoder factory from the module.
- L72 _public prototype_ `virtual void GetEncoderFactories(TArray<TWeakPtr<ITmvMediaEncoderFactory, ESPMode::ThreadSafe>>& OutEncoderFactories) const = 0;` — Get a list of all currently registered encoder factories.
- L79 _public prototype_ `virtual TSharedPtr<ITmvMediaEncoderFactory, ESPMode::ThreadSafe> FindEncoderFactory(FName InEncoderFactoryName) const = 0;` — Find the encoder factory by name. @param InEncoderFactoryName Name of the factory. @return The requested factory if found.
- L84 _public prototype_ `virtual void RegisterMuxerFactory(TSharedPtr<ITmvMediaMuxerFactory, ESPMode::ThreadSafe> InMuxerFactory) = 0;` — Register a muxer factory in the module.
- L89 _public prototype_ `virtual void UnregisterMuxerFactory(TSharedPtr<ITmvMediaMuxerFactory, ESPMode::ThreadSafe> InMuxerFactory) = 0;` — Unregister a muxer factory from the module.
- L94 _public prototype_ `virtual void GetMuxerFactories(TArray<TWeakPtr<ITmvMediaMuxerFactory, ESPMode::ThreadSafe>>& OutMuxerFactories) const = 0;` — Get a list of all currently registered muxer factories.
- L99 _public prototype_ `virtual void RegisterDemuxerFactory(TSharedPtr<ITmvMediaDemuxerFactory, ESPMode::ThreadSafe> InDemuxerFactory) = 0;` — Register a demuxer factory in the module.
- L104 _public prototype_ `virtual void UnregisterDemuxerFactory(TSharedPtr<ITmvMediaDemuxerFactory, ESPMode::ThreadSafe> InDemuxerFactory) = 0;` — Unregister a demuxer factory from the module.
- L109 _public prototype_ `virtual void GetDemuxerFactories(TArray<TWeakPtr<ITmvMediaDemuxerFactory, ESPMode::ThreadSafe>>& OutDemuxerFactories) const = 0;` — Get a list of all currently registered demuxer factories.
- L116 _public prototype_ `virtual TSharedPtr<ITmvMediaDemuxerFactory, ESPMode::ThreadSafe> FindDemuxerFactoryForExtension(const FString& InFileExtension) const = 0;` — Find the demuxer factory that supports the given file extensions. @param InFileExtension File extension without dot @return Demuxer factory if found, null otherwise.
- L121 _public prototype_ `virtual ITmvMediaTranscodeJobManager* GetTranscodeJobManager() const = 0;` — Access the global transcode job manager.
- L127 _public prototype_ `virtual ITmvMediaTranscodeJobRunner* GetTranscodeJobRunner() const = 0;` — Access the global transcode job runner, which owns the active and pending jobs and ticks them from an engine system independent of Slate.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/SampleConverter/TmvMediaFrameMipBufferFwd.h` (Public)


#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TSharedPtr<FTmvMediaFrameMipBuffer, ESPMode::ThreadSafe> FTmvMediaFrameMipBufferHandle;` — A shared mip buffer acquired from a pool that handles returning to the pool upon release.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/SampleConverter/TmvMediaFrameMipBufferPool.h` (Public)


#### class `FTmvMediaFrameMipBufferPool`  
`class FTmvMediaFrameMipBufferPool : public TSharedFromThis<FTmvMediaFrameMipBufferPool, ESPMode::ThreadSafe>`  
_L23-46_
- inherits: `TSharedFromThis<FTmvMediaFrameMipBufferPool,ESPMode::ThreadSafe>`
- desc: Tmv Frame Mip Buffer Pool. This pool is held by the tmv player to allow recycling of frame buffers between decoded samples.
- L26 _public prototype_ `FTmvMediaFrameMipBufferPool() = default;`
- L27 _public prototype_ `~FTmvMediaFrameMipBufferPool();`
- L30 _public prototype_ `FTmvMediaFrameMipBufferHandle AcquireBuffer(const FTmvMediaFrameMipInfo& InMipInfo);` — Acquire a buffer suitable for the given frame mip.
- L34 _private prototype_ `void ReleaseBuffer(SIZE_T InAllocSize, FTmvMediaFrameMipBuffer* InBuffer);` — Either return or Add new chunk of memory to the pool based on its size.
- L37 _private prototype_ `FTmvMediaFrameMipBufferPool(const FTmvMediaFrameMipBufferPool&) = delete;` — Non-copyable
- L38 _private prototype_ `FTmvMediaFrameMipBufferPool& operator=(const FTmvMediaFrameMipBufferPool&) = delete;`
- L42 _private member_ `FCriticalSection MemoryPoolCriticalSection;` — A critical section used for memory allocation and pool management.
- L45 _private member_ `TMultiMap<SIZE_T, FTmvMediaFrameMipBuffer*> MemoryPool;` — Memory pool from where we are allowed to take buffers.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/TmvMediaFrameColorInfo.h` (Public)


#### enum `ETmvMediaFrameColorMatrix`  
`enum class ETmvMediaFrameColorMatrix : uint8`  
_L11-23_
- desc: Carries the information about the YUV conversion matrix. Note: this is independent of the final RGB color space. YUV conversion is done prior to the application of the transfer function.
- L14 _public enumerator_ `None = 0` — Unspecified.
- L16 _public enumerator_ `Identity = 1` — Identity, i.e. no yuv conversion (rgb color model).
- L18 _public enumerator_ `Rec601 = 2` — Rec. ITU-R BT.601-7 525 (Kr = 0.299, Kb = 0.114)
- L20 _public enumerator_ `Rec709 = 3` — Rec. ITU-R BT.709-6 (Kr = 0.2126, Kb = 0.0722)
- L22 _public enumerator_ `Rec2020 = 4` — Rec. ITU-R BT.2020-2 (Kr = 0.2627, Kb = 0.0593)

#### enum `ETmvMediaFrameColorMatrixRange`  
`enum class ETmvMediaFrameColorMatrixRange : uint8`  
_L28-41_
- desc: Carries the information about the range of the YUV conversion matrix (Scaled vs UnScaled)
- L34 _public enumerator_ `Limited = 0` — Typical [16,219] (on 8 bits) limited range. Defined by spec. This range definition corresponds to the "scaled" yuv matrices and offsets from MediaShaders.
- L40 _public enumerator_ `Full = 1` — Full [0, 255] range. This range definition corresponds to the "unscaled" yuv matrices and offsets from MediaShaders.

#### struct `FTmvMediaFrameColorInfo`  
`struct FTmvMediaFrameColorInfo`  
_L46-102_
- desc: Defines the color space, encoding and yuv matrix of a frame buffer in the tmv framework.
- L49 _public member_ `UE::Color::EEncoding Encoding = UE::Color::EEncoding::None;` — Information about the color encoding of the corresponding frame buffer.
- L56 _public member_ `UE::Color::EColorSpace ColorSpace = UE::Color::EColorSpace::None;` — Information about the color space of the corresponding frame buffer. @remark For color space conversions, If the color space is left to "None", it will be assumed to be the current engine's "working" color space by default.
- L59 _public member_ `UE::Color::EReferenceWhite ReferenceWhiteOverride = UE::Color::EReferenceWhite::None;` — Reference-white standard used to scale UE scene-linear 1.0 to diffuse white.
- L62 _public member_ `ETmvMediaFrameColorMatrix YuvMatrix = ETmvMediaFrameColorMatrix::Rec709;` — Information about the YUV color matrix of the corresponding frame buffer.
- L65 _public member_ `ETmvMediaFrameColorMatrixRange YuvMatrixRange = ETmvMediaFrameColorMatrixRange::Limited;` — Information about the YUV color matrix range of the corresponding frame buffer.
- L71 _public function_ `static FTmvMediaFrameColorInfo MakeNeutral()` — Make a neutral "no-overrides" color info that leaves everything unspecified. This is used when requesting the desired format of the encoder in case there are no overrides.
- L82 _public function_ `void ApplyOverrides(const FTmvMediaFrameColorInfo& InOverrides)` — Apply the color info overrides, i.e. everything that has a value set. @param InOverrides Specify the overrides to apply to current color settings.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/TmvMediaFrameInfo.h` (Public)


#### enum `ETmvMediaFrameComponentType`  
`enum class ETmvMediaFrameComponentType : int8`  
_L52-58_
- desc: Defines currently supported component data types.
- L55 _public enumerator_ `Int = 0` — Component is stored as an integer.
- L57 _public enumerator_ `Float` — Component is stored as a float.

#### enum `ETmvMediaFrameBufferLayout`  
`enum class ETmvMediaFrameBufferLayout : int8`  
_L65-71_
- desc: Defines buffer memory data layout, i.e. the overall way the memory is organized in the whole frame buffer. Tiling allows for better memory locality for certain type of processing, especially for decoding.
- L68 _public enumerator_ `ScanLine = 0` — Scan line layout
- L70 _public enumerator_ `Tiled` — Tiled layout

#### enum `ETmvMediaFrameComponentLayout`  
`enum class ETmvMediaFrameComponentLayout : int8`  
_L74-86_
- desc: Defines the layout of components in a memory plane.
- L80 _public enumerator_ `Packed = 0` — Components are packed. Ex: R0G0B0|R1G1B1|... Example of formats with packed components in a plane: NV12 has UV packed.
- L85 _public enumerator_ `Interleaved` — Components are interleaved on each scan line. Ex: R0R1...|G0G1...|B0B1... Example of formats with interleaved components in a plane: IMC2, IMC4

#### enum `ETmvMediaFrameColorModel`  
`enum class ETmvMediaFrameColorModel : int8`  
_L93-98_
- desc: Defines the color model the components are representing. The usage is for the sample converter implementation to convert to the final RGBA format for the final media texture. It is not intended to be a fully generalized format.
- L95 _public enumerator_ `YUV = 0`
- L96 _public enumerator_ `RGB`

#### struct `FTmvMediaFramePlaneInfo`  
`struct FTmvMediaFramePlaneInfo`  
_L115-213_
- desc: Defines the layout and format of a video frame memory plane. A memory plane is one contiguous memory region that can contain more than one component. Ex: NV12 has a packed UV plane (semi-planar formats), or IMC2 has interleaved U and V scan lines in a single memory plane. A "sample" is an element of the current plane (interleaved or not). No start offset is provided, we assume the valid pixels start at offset 0 in the plane. The stride is the offset between the start of 2 scan lines, includes padding and interleaved components. If there is padding between planes, it is included in the extra lines (see NumLines). It is assumed those extra lines are at the end of the plane buffer.
- L118 _public member_ `uint8 NumComponents = 0;` — Number of components packed per sample in this plane.
- L125 _public member_ `uint8 BitDepth = 0;` — Number of bits per component of this plane. Used by the sample converter. @remark Memory layouts are always aligned to the next full byte. Ex: 10, 12 bits are still memory aligned to 16 bits.
- L131 _public member_ `ETmvMediaFrameComponentType Type = ETmvMediaFrameComponentType::Int;` — Defines the components data type. Used by the sampler converter.
- L134 _public member_ `uint32 Width = 0;` — Number of horizontal samples in this plane.
- L137 _public member_ `uint32 Height = 0;` — Number of vertical samples in this plane.
- L145 _public member_ `uint32 Stride = 0;` — Number of memory bytes per scan line of this memory plane. This must include padding at the end of the line. In case of interleaved component layouts, this stride is for the whole scan line including all components and any additional padding need by the decoder for macroblock or cache alignment.
- L151 _public member_ `uint32 NumLines = 0;` — Number of scan lines in this plane. This could include more lines for inter-plane (or inter-tile) padding.
- L158 _public member_ `ETmvMediaFrameComponentLayout ComponentLayout = ETmvMediaFrameComponentLayout::Packed;` — Defines the component layout within the plane. This is used to define planes with interleaved scan lines, such as IMC2 or IMC4 where the U and V planes have the scan lines interleaved.
- L164 _public member_ `int8 WidthRatio = 1;` — Width ratio defined as Frame Width / Plane Width. Used for chroma subsampling. Ex: for 422 or 420, width ratio is 2 for U and V planes.
- L170 _public member_ `int8 HeightRatio = 1;` — Height ratio defined as Frame Height / Plane Height. Used for chroma subsampling. Ex: for 420, height ratio is 2 for U and V planes.
- L176 _public function_ `uint32 GetBytesPerComponent() const` — Returns the number of bytes per component for this memory plane. The memory layouts are always aligned to bytes.
- L184 _public function_ `SIZE_T GetMemorySizeInBytes() const` — Returns the memory size in bytes of this memory plane.
- L194 _public function_ `uint32 GetStartComponentOffsetInBytes(int32 InComponentIndexInPlane) const` — Computes the offset, in bytes, to the start of the given component in the plane buffer. @param InComponentIndexInPlane Index of the given component in the current plane. Ex: in a UV plane, U would have index 0 and V, index 1. @return Offset to apply to the start of the plane buffer to get the first pixel of the given component.

#### struct `FTmvMediaFrameMipInfo`  
`struct FTmvMediaFrameMipInfo`  
_L247-473_
- desc: This struct describes information (memory layout, color model, component type) about a mipmap buffer for a video frame. A complete TMV frame for a given time index will be composed of multiple mips each of which is described by this struct. The goal is to allow decoders to provide the sample conversion implementation enough information to prepare mip frame buffers with the needed layout for the decoder, and then be able to handle the conversion on the GPU through PS or CS shaders. Memory Surface Layout: The pixel components may be packed in a single memory plane, separated in different planes or mixed (semi-planar ex: NV12). Chroma subsampling for YUV color model is supported by having planes with different dimensions. The memory data layout can be either tiled or scanline. If the layout is tiled, the plane definitions (dimensions, stride, padding, etc) are per tile rather than for the whole frame. FOURCC is not enough: There are FOURCC types for fully planar YUV types such as P010 (420 10 bits) or P210 (422, 10 bits). However, those formats don't describe custom padding for decoder tile or macro block memory alignment for best performance. This is why at this level of the api, it is preferable to not try to align with existing FOURCC. The current descriptor is still probably incomplete as it only targets a subset of implementations, but it is expected to evolve over time. Some reference on the subject: - https://github.com/torvalds/linux/blob/master/include/uapi/drm/drm_four
- L250 _public member_ `int32 MipLevel = 0;` — Mip level
- L253 _public member_ `int32 Width = 0;` — Number of horizontal samples in this mip.
- L256 _public member_ `int32 Height = 0;` — Number of vertical samples in this mip.
- L259 _public member_ `int32 NumComponents = 0;` — Total number of components per sample. May be packed in planes.
- L262 _public member_ `ETmvMediaFrameColorModel ColorModel = ETmvMediaFrameColorModel::RGB;` — Indicate the color model that allow to determine how the component should be interpreted.
- L265 _public member_ `FTmvMediaFrameColorInfo ColorInfo;` — Specifies the color information (color space, encoding, yuv matrix and range) for the given frame.
- L268 _public member_ `int32 TileWidth = 0;` — Number of horizontal samples in a tile.
- L271 _public member_ `int32 TileHeight = 0;` — Number of vertical samples in a tile.
- L274 _public member_ `FIntPoint NumTiles = FIntPoint(0,0);` — Number of tiles on each dimensions in this mip.
- L277 _public member_ `ETmvMediaFrameBufferLayout Layout = ETmvMediaFrameBufferLayout::ScanLine;` — Defines the memory layout of all mip planes.
- L289 _public member_ `TArray<FTmvMediaFramePlaneInfo, TInlineAllocator<4>> Planes;` — Description of memory planes. The planes are defined in this array in the order they are in memory. Interleaved planes must be in order and grouped in the planes array as well. For tiled layout, defines the planes per-tile. For YUV 420, 422, planes have different sizes because of chroma subsampling.
- L295 _public function_ `SIZE_T GetAllPlaneMemorySizeInBytes() const` — Returns the memory size in bytes for all planes. @remark This will include padding (either between planes or between tiles).
- L312 _public function_ `bool GetPlaneBufferOffset(int32 InPlaneIndex, SIZE_T& OutPlaneBufferOffset) const` — Gets the plane buffer offset accounting for the size of all previous planes. This is used for memory layout where all the planes are in one large memory block. @param InPlaneIndex Index of the plane we want to get the start offset of. @param OutPlaneBufferOffset Value populated with the plane buffer offset. @return true if the plane buffer offset could be calculated, false otherwise.
- L333 _public function_ `SIZE_T GetMemorySizeInBytes() const` — Returns the total memory size in bytes.
- L353 _public function_ `int32 GetWorstCaseTileCount() const` — Returns the worst-case tile count for this mip (NumTiles.X * NumTiles.Y). Used as the clamp for the slot budget so we never allocate MORE slots than the mip actually has tiles.
- L370 _public function_ `int32 GetBudgetedSlotCount() const` — Returns the effective number of resident tile slots for this mip, accounting for the global virtualization CVar and the per-mip budget. When virtualization is off OR the worst-case tile count is already below the budget, this returns the worst case (i.e. legacy behavior). Budget source: - r.TmvMedia.MipBudgetBase > 0 -> legacy fixed formula via GetMipBudget - r.TmvMedia.MipBudgetBase == 0 (default) -> UHD heuristic via ComputeHeuristicMipBudget(TileWidth, TileHeight), same value at every mip and clamped to worst case here.
- L393 _public function_ `bool IsVirtualized() const` — Returns true when this mip is actually virtualized - i.e. the budget is strictly below the worst-case tile count, so a logical-to-physical tile indirection is needed. When false, the buffer layout is identity-mapped (slot index == tile index) and decode/sample paths can take the fast path that pre-dates virtualization.
- L414 _public function_ `SIZE_T GetBudgetedMemorySizeInBytes() const` — Returns the memory size in bytes accounting for the virtualization budget. Equivalent to GetMemorySizeInBytes() unless this mip is virtualized, in which case the size shrinks from (WorstCaseTiles * AllPlaneBytes) to (BudgetedSlots * AllPlaneBytes).
- L430 _public function_ `int32 GetMaxGrowSlotCount() const` — Returns the maximum slot count the buffer can grow to for this mip, given the r.TmvMedia.MipBudgetMax CVar and the mip's worst-case tile count. When grow-on-demand is disabled this matches GetBudgetedSlotCount() (no growth possible). When MipBudgetMax is 0 (default), the ceiling is the worst-case tile count - past which there's nothing to virtualize.
- L453 _public function_ `int32 GetPlaneIndexForComponent(int32 InComponentIndex, int32* OutComponentIndexInPlane = nullptr) const` — Finds the plane index for the given component. @param InComponentIndex Component index to find. @param OutComponentIndexInPlane If specified, this will be populated with the index of the specified component within the plane. @return plane index or INDEX_NONE if error.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TMVMEDIA_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace TmvMedia` (scope `UE`)
- L21 _prototype_ `bool IsVirtualizationEnabled();` (scope `UE::TmvMedia`) — True when mip-buffer virtualization (r.TmvMedia.VirtualizeMipBuffers) is on.
- L29 _prototype_ `int32 GetMipBudget(int32 MipLevel);` (scope `UE::TmvMedia`) — Legacy fixed-formula per-mip slot budget: budget(mip) = max(MipBudgetMin, MipBudgetBase >> mip). Used only when MipBudgetBase > 0 (explicit override). Callers should clamp against the mip's worst-case tile count themselves.
- L38 _prototype_ `int32 ComputeHeuristicMipBudget(int32 TileWidth, int32 TileHeight);` (scope `UE::TmvMedia`) — UHD-viewport heuristic for the per-mip slot budget: budget = K * (3840 * 2160) / (TileWidth * TileHeight), floored by MipBudgetMin. Same value applies at every mip; per-mip worst-case clamping (in FTmvMediaFrameMipInfo) handles small mips. Used when MipBudgetBase == 0 (the default).
- L41 _prototype_ `bool IsGrowOnDemandEnabled();` (scope `UE::TmvMedia`) — True when r.TmvMedia.GrowMipBuffersOnDemand allows runtime growth.
- L48 _prototype_ `int32 GetMipBudgetMax();` (scope `UE::TmvMedia`) — Returns the per-mip slot growth ceiling (r.TmvMedia.MipBudgetMax). A return of 0 means "no cap from the CVar"; callers must still clamp to the mip's worst-case tile count.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/TmvMediaTrackInfo.h` (Public)


#### enum `ETmvMediaTrackType`  
`enum class ETmvMediaTrackType : uint8`  
_L11-16_
- desc: Track type for muxer/demuxer tracks.
- L13 _public enumerator_ `Unspecified`
- L14 _public enumerator_ `Video`
- L15 _public enumerator_ `Audio`

#### struct `FTmvMediaTrackInfo`  
`struct FTmvMediaTrackInfo`  
_L22-66_
- desc: Common descriptor for a media track, shared by muxer and demuxer. Describes the codec, format, and media-type-specific properties of a track.
- L25 _public member_ `ETmvMediaTrackType TrackType = ETmvMediaTrackType::Unspecified;` — Track type.
- L31 _public member_ `uint32 SampleEntryFormat = 0;` — FOURCC sample entry format identifying the codec. Ex: 'apv1' for APV, 'avc1' for H.264, 'hev1' for HEVC.
- L37 _public member_ `uint32 Timescale = 0;` — Number of ticks per second for this track's timing. All DTS, PTS, and duration values are measured in this timescale.
- L44 _public member_ `uint32 ConstantSampleDuration = 0;` — If every sample has the same duration, this holds the constant value in timescale units. 0 means variable or unknown duration. Frame rate can be computed as FFrameRate(Timescale, ConstantSampleDuration).
- L47 _public member_ `uint32 DisplayWidth = 0;` — Display width (video tracks only).
- L50 _public member_ `uint32 DisplayHeight = 0;` — Display height (video tracks only).
- L53 _public member_ `uint32 SamplingRate = 0;` — Sampling rate in Hz (audio tracks only).
- L56 _public member_ `uint16 NumberOfChannels = 0;` — Number of channels (audio tracks only).
- L62 _public member_ `TArray<TArray<uint8>> CodecSpecificBoxes;` — Codec-specific configuration boxes, pre-built as raw box data. Each entry is a complete box (size + type + payload).
- L65 _public member_ `FString TrackName;` — Optional human-readable track name.

#### enum `ETmvMediaContainerResult`  
`enum class ETmvMediaContainerResult`  
_L71-76_
- desc: Common result code for container muxer/demuxer operations.
- L73 _public enumerator_ `Success`
- L74 _public enumerator_ `Fail`
- L75 _public enumerator_ `EndOfStream`

#### struct `FTmvMediaTrackSampleInfo`  
`struct FTmvMediaTrackSampleInfo`  
_L81-97_
- desc: Common sample metadata shared by muxer and demuxer sample structs.
- L84 _public member_ `uint32 Duration = 0;` — Presentation duration of this sample, in the track's timescale units.
- L87 _public member_ `int64 DTS = 0;` — Decode timestamp in the track's timescale units.
- L90 _public member_ `int64 PTS = 0;` — Presentation (composition) timestamp in the track's timescale units.
- L93 _public member_ `uint32 SampleNumber = 0;` — Sequential sample number (0-based).
- L96 _public member_ `bool bIsKeyframe = false;` — Whether this sample is a sync sample (keyframe).

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Transcoder/ITmvMediaTranscodeJobManager.h` (Public)


#### class `ITmvMediaTranscodeJobManager`  
`class ITmvMediaTranscodeJobManager`  
_L17-72_
- desc: Singleton manager for all transcode jobs.
- L21 _public prototype_ `static ITmvMediaTranscodeJobManager* Get();` — Returns a pointer to the global transcode job manager.
- L24 _public function_ `static void SafeRegisterTranscodeJob(UTmvMediaTranscodeJob* InTranscodeJob)` — Register transcode job to the global transcode job manager.
- L33 _public function_ `static void SafeUnregisterTranscodeJob(UTmvMediaTranscodeJob* InTranscodeJob)` — Unregister transcode job from the global transcode job manager.
- L44 _public prototype_ `virtual void GetTranscodeJobs(TArray<TWeakObjectPtr<UTmvMediaTranscodeJob>>& OutTranscodeJobs) const = 0;` — Get a list of all currently registered jobs.
- L49 _public prototype_ `virtual UTmvMediaTranscodeJob* GetTranscodeJob(const FGuid& InJobId) const = 0;` — Get the transcode job with the given JobId, if found.
- L54 _public prototype_ `virtual void RegisterTranscodeJob(UTmvMediaTranscodeJob* InTranscodeJob) = 0;` — Register the given transcode job to this manager.
- L59 _public prototype_ `virtual void UnregisterTranscodeJob(UTmvMediaTranscodeJob* InTranscodeJob) = 0;` — Unregister the given transcode job from this manager.
- L62 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTranscodeJobEvent, UTmvMediaTranscodeJob* ) virtual FOnTranscodeJobEvent& GetOnTranscodeJobAdded() = 0;` — Job Event Delegate.
- L68 _public prototype_ `virtual FOnTranscodeJobEvent& GetOnTranscodeJobRemoved() = 0;` — Delegate called when a job is removed/unregistered from this manager.
- L71 _protected prototype_ `virtual ~ITmvMediaTranscodeJobManager() = default;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TMVMEDIA_API`
- L62 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTranscodeJobEvent, UTmvMediaTranscodeJob* ) virtual FOnTranscodeJobEvent& GetOnTranscodeJobAdded() = 0;` — Job Event Delegate.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Transcoder/ITmvMediaTranscodeJobRunner.h` (Public)


#### struct `FTmvMediaTranscodeJobRunOptions`  
`struct FTmvMediaTranscodeJobRunOptions`  
_L20-27_
- desc: Per-job runtime options applied when a job is enqueued in the runner.
- L23 _public member_ `double TimeoutSeconds = 0.0;` — Optional wall-clock timeout. <= 0 disables the watchdog.
- L26 _public member_ `FOnTranscodeJobStarting OnPreStart;` — Hook fired immediately before the runner starts the job (see FOnTranscodeJobStarting).

#### class `ITmvMediaTranscodeJobRunner`  
`class ITmvMediaTranscodeJobRunner`  
_L36-86_
- desc: Singleton runner that owns the active transcode job and a pending queue, and ticks the active job from an engine system (FTickableGameObject) so jobs progress regardless of Slate window visibility. Sequential: at most one job runs at a time; the next is started when the current completes.
- L40 _public prototype_ `static ITmvMediaTranscodeJobRunner* Get();` — Returns a pointer to the global transcode job runner, if the TmvMedia module is loaded.
- L47 _public prototype_ `virtual void EnqueueJob(UTmvMediaTranscodeJob* InJob, const FTmvMediaTranscodeJobRunOptions& InOptions = {}) = 0;` — Enqueue a job for execution. If the runner is idle, the job is started immediately; otherwise it is queued behind the active and earlier-pending jobs. The runner takes over the job's tick / stop / discard lifecycle until completion.
- L50 _public prototype_ `virtual void CancelAll() = 0;` — Cancel the active job and discard all pending jobs.
- L53 _public prototype_ `virtual void CancelJob(const FGuid& InJobId) = 0;` — Cancel a specific job by id, whether it is currently active or pending.
- L56 _public prototype_ `virtual bool IsJobActiveOrPending(const FGuid& InJobId) const = 0;` — Returns true if the job with the given id is currently active or queued.
- L59 _public prototype_ `virtual bool HasActiveOrPendingJobs() const = 0;` — Returns true if there is at least one job active or pending.
- L65 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRunnerJobEvent, UTmvMediaTranscodeJob* );` — Delegate fired (game thread) when a job's Start() returned true and the job is now active. Not fired for jobs whose Start() failed synchronously — those go straight to OnJobFinished.
- L66 _public prototype_ `virtual FOnRunnerJobEvent& GetOnJobStarted() = 0;`
- L73 _public prototype_ `virtual FOnRunnerJobEvent& GetOnJobFinished() = 0;` — Delegate fired (game thread) when a job leaves the runner. Fires for completed jobs, cancelled active jobs, cancelled pending jobs, and jobs whose Start() failed synchronously. Safe to access the job pointer for read-only inspection until the broadcast returns.
- L81 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAllJobsFinished);` — Delegate fired (game thread) when the runner observes the last active job complete via Tick with no pending jobs left. Does NOT fire when EnqueueJob() drains the queue synchronously (e.g., a single submission whose Start() fails); callers wanting to detect that case should check HasActiveOrPendingJobs() after EnqueueJob() instead.
- L82 _public prototype_ `virtual FOnAllJobsFinished& GetOnAllJobsFinished() = 0;`
- L85 _protected prototype_ `virtual ~ITmvMediaTranscodeJobRunner() = default;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TMVMEDIA_API`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTranscodeJobStarting, UTmvMediaTranscodeJob* );` — Fired on the game thread immediately before the runner calls Start() on the job. Lets callers attach per-job state (notification handler, listeners, ...) only for jobs that are actually about to run, instead of eagerly at enqueue time.
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTranscodeJobStarting, UTmvMediaTranscodeJob* );` — Fired on the game thread immediately before the runner calls Start() on the job. Lets callers attach per-job state (notification handler, listeners, ...) only for jobs that are actually about to run, instead of eagerly at enqueue time.
- L65 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRunnerJobEvent, UTmvMediaTranscodeJob* );` — Delegate fired (game thread) when a job's Start() returned true and the job is now active. Not fired for jobs whose Start() failed synchronously — those go straight to OnJobFinished.
- L81 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAllJobsFinished);` — Delegate fired (game thread) when the runner observes the last active job complete via Tick with no pending jobs left. Does NOT fire when EnqueueJob() drains the queue synchronously (e.g., a single submission whose Start() fails); callers wanting to detect that case should check HasActiveOrPendingJobs() after EnqueueJob() instead.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Transcoder/TmvMediaFrameConverter.h` (Public)


#### class `UTmvMediaFrameConverter`  
`class UTmvMediaFrameConverter : public UTmvMediaTranscodeStage`  
_L17-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTmvMediaTranscodeStage`
- desc: Base class for converter stage of transcode pipeline. @see UTmvMediaTranscodeJob
- L22 _public prototype_ `virtual void ReceiveMips(UTmvMediaTranscodeJob* InParentJob, TUniquePtr<FTmvMediaFrameMips>&& InMips);` — Receive mips for processing.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Transcoder/TmvMediaFrameEncoder.h` (Public)


#### class `UTmvMediaFrameEncoder`  
`class UTmvMediaFrameEncoder : public UTmvMediaTranscodeStage`  
_L22-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTmvMediaTranscodeStage`
- desc: Base class for encoder stage of the transcode pipeline. @see UTmvMediaTranscodeJob
- L30 _public function_ `virtual void SetEncoderOptions(const TInstancedStruct<FTmvMediaEncoderOptions>& InOptions)` — Set the encoder options. This should be done before the stage is started. @param InOptions Encoder options. This is used to create internal encoder and must not change during encoding.
- L35 _public function_ `virtual const FTmvMediaEncoderOptions* GetEncoderOptions() const` — Returns the current encoder options if set or null otherwise.
- L45 _public function_ `virtual bool RequestMipInfos(UTmvMediaTranscodeJob* InParentJob, const FTmvMediaFrameTimeInfo& InSourceTimeInfo, const FTmvMediaFrameMipInfo& InSourceMipInfo, TArray<FTmvMediaFrameMipInfo>& OutFrameMipInfo)` — Queries the encoder for the memory layout and format for frames of the given size, and doing so for each mips. @param InParentJob Pointer to the parent job that contains the overall job settings. @param InSourceTimeInfo Source sample time info, needed for frame duration (frame rate). Encoder might need it to compute some bitrate related settings. @param InSourceMipInfo Source Mip Info from the prior stage (ex Frame Producer). @param OutFrameMipInfo Populated mip info with the memory layout the encoder needs. @return true if the requested info can be produced, or false if there is a validation error or the encoder doesn't support requested format.
- L55 _public function_ `virtual void ReceiveMips(UTmvMediaTranscodeJob* InParentJob, TUniquePtr<FTmvMediaFrameMips>&& InMips)` — Receive mips for processing. @param InParentJob Pointer to the parent job that contains the overall job settings. @param InMips Mips from prior stage. Note that ownership is transferred.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Transcoder/TmvMediaFrameMips.h` (Public)


#### struct `FTmvMediaFrameTimeInfo`  
`struct FTmvMediaFrameTimeInfo`  
_L16-29_
- desc: Time information for a frame.
- L19 _public member_ `int32 FrameIndex = 0;` — Frame index (for index based muxers).
- L22 _public member_ `int32 FrameIndexNoOffset = 0;` — Zero-based Frame index (for index based muxers).
- L25 _public member_ `FTimespan FrameTime;` — Frame time stamp (for time span based muxers).
- L28 _public member_ `FTimespan FrameDuration;` — Frame time duration.

#### struct `FTmvMediaFrameMips`  
`struct FTmvMediaFrameMips`  
_L34-48_
- desc: Container of an array of frame mip buffers with time info for the transcoder pipeline.
- L37 _public member_ `FTmvMediaFrameTimeInfo TimeInfo;` — Time indexing information.
- L40 _public member_ `TArray<FTmvMediaFrameMipBufferHandle> MipBuffers;` — Array of mips buffers.
- L47 _public prototype_ `bool Init(const TSharedPtr<FImage>& InMip0, bool bInGenerateMips);` — Helper to initialize the mip buffers from the provided mip0. @param InMip0 Image to use for mip 0. Keeps a reference to the image. @param bInGenerateMips if true, mips will be generated from mip 0.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Transcoder/TmvMediaFrameProducer.h` (Public)


#### struct `FTmvMediaFrameProducerTrackInfo`  
`struct FTmvMediaFrameProducerTrackInfo`  
_L19-30_
- reflection: `USTRUCT()`
- desc: Track information for the currently playing tracks from the frame producer stage.
- L25 _public member_ `FFrameRate FrameRate = FFrameRate(24, 1);` — `UPROPERTY()` — Track's frame rate.
- L29 _public member_ `FTimespan Duration = FTimespan::Zero();` — `UPROPERTY()` — Track's duration.

#### class `UTmvMediaFrameProducer`  
`class UTmvMediaFrameProducer : public UTmvMediaTranscodeStage`  
_L37-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTmvMediaTranscodeStage`
- desc: Base class for producer stage of transcode pipeline. @see UTmvMediaTranscodeJob
- L44 _public prototype_ `FTmvMediaFrameProducerTrackInfo GetVideoTrackInfo() const;` — Returns a copy of the current video track info.
- L47 _public prototype_ `void SetVideoTrackInfo(const FTmvMediaFrameProducerTrackInfo& InVideoTrackInfo);` — Set the video track info.
- L50 _public prototype_ `TOptional<FTimecode> GetStartTimecode() const;` — Returns the start timecode for the current media, if available.
- L53 _public prototype_ `TOptional<FFrameRate> GetStartTimecodeRate() const;` — Returns the start timecode rate for the current media, if available.
- L56 _public prototype_ `void SetStartTimecode(const FTimecode& InStartTimecode);` — Set the start timecode for the current media.
- L59 _public prototype_ `void SetStartTimecodeRate(const FFrameRate& InStartTimecodeRate);` — Set the start timecode rate for the current media.
- L63 _protected member_ `mutable FCriticalSection TrackInfoLock;` — Track Info critical section.
- L66 _protected member_ `FTmvMediaFrameProducerTrackInfo VideoTrackInfo;` — Information about the currently playing video track.
- L69 _protected member_ `TOptional<FTimecode> StartTimecode;` — The current media's start timecode, if available.
- L72 _protected member_ `TOptional<FFrameRate> StartTimecodeRate;` — The current media's start timecode rate, if available.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Transcoder/TmvMediaTranscodeJob.h` (Public)


#### class `ITmvMediaTranscodeNotification`  
`class ITmvMediaTranscodeNotification`  
_L21-31_
- desc: Interface for the notifications. This can be implemented by a slate notification or logs. @remark Important: the implementations must be thread safe. Notifications may be called from worker threads.
- L24 _public prototype_ `virtual ~ITmvMediaTranscodeNotification() = default;`
- L27 _public prototype_ `virtual void SetText(const FText& InText) = 0;` — Sets the text to be displayed in the notification.
- L30 _public prototype_ `virtual void Close(bool bInSuccess) = 0;` — Close the notification.

#### enum `ETmvMediaTranscodeInputSource`  
`enum class ETmvMediaTranscodeInputSource : uint8`  
_L37-43_
- reflection: `UENUM(BlueprintType)`
- desc: Selection of the input source/
- L40 _public enumerator_ `File` — External media file in any of the supported format.
- L42 _public enumerator_ `MediaSource` — Existing media source asset in the project.

#### enum `ETmvMediaTranscodeOutputFormat`  
`enum class ETmvMediaTranscodeOutputFormat : uint8`  
_L49-55_
- reflection: `UENUM(BlueprintType)`
- desc: Selection of the output format.
- L52 _public enumerator_ `FileSequence UMETA(DisplayName="TMV Image Sequence")` — Output each access unit as a separate file.
- L54 _public enumerator_ `Container UMETA(DisplayName="TMV Video File")` — Mux access units into a single container file.

#### struct `FTmvMediaTranscodeMuxerSettings`  
`struct FTmvMediaTranscodeMuxerSettings`  
_L59-68_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure for muxer settings used to select the muxer.
- L67 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — The name of the selected muxer

#### struct `FTmvMediaTranscodeJobSettings`  
`struct FTmvMediaTranscodeJobSettings`  
_L74-176_
- reflection: `USTRUCT(BlueprintType)`
- desc: Common Transcode Job Settings
- L79 _public prototype_ `FString GetInputPath() const;` — Returns the input url (either media source or file).
- L82 _public prototype_ `FString GetAbsoluteInputPath() const;` — Returns the absolute file path of the media.
- L85 _public prototype_ `bool IsInputPathSet() const;` — Returns true if the input path is set.
- L91 _public prototype_ `FFrameRate GetInputFramerate() const;` — Returns the input frame rate setting. @remark will return the frame rate from the media source if specified.
- L94 _public prototype_ `bool IsOutputPathSet() const;` — Returns true if the output path is set.
- L97 _public prototype_ `FString GetAbsoluteOutputPath() const;` — Returns the absolute output directory path.
- L101 _public member_ `ETmvMediaTranscodeInputSource InputSource = ETmvMediaTranscodeInputSource::File;` — `UPROPERTY(EditAnywhere, Category = "Input Sequence", meta = (SegmentedDisplay))` — Select the input source.
- L107 _public member_ `FFilePath InputPath;` — `UPROPERTY(EditAnywhere, Category = "Input Sequence", meta = (EditCondition = "InputSource == ETmvMediaTranscodeInputSource::File", EditConditionHides))` — The directory that contains the source media (image sequence files or container).
- L114 _public member_ `FFrameRate FrameRate = FFrameRate(24, 1);` — `UPROPERTY(EditAnywhere, Category = "Input Sequence", meta = (EditCondition = "InputSource == ETmvMediaTranscodeInputSource::File", EditConditionHides))` — Allow to specify a frame rate if the media sources don't provide it. Remark: Overriding the source frame rate is not possible with the current implementation.
- L123 _public member_ `TSoftObjectPtr<UMediaSource> InputMediaSource;` — `UPROPERTY(EditAnywhere, Category = "Input Sequence", meta = (EditCondition = "InputSource == ETmvMediaTranscodeInputSource::MediaSource", EditConditionHides, AllowedClasses = "/Script/MediaAssets.FileMediaSource,/Script/ImgMedia.ImgMediaSource"))` — Specify an existing media source as the input. @remark Restricted to UFileMediaSource and UImgMediaSource: these are the only source types the transcoder pipeline can consume.
- L126 _public member_ `bool bEnableStartTimecodeOverride = false;` — `UPROPERTY(EditAnywhere, Category = "Input Sequence", AdvancedDisplay, meta = (InlineEditConditionToggle))`
- L130 _public member_ `FTimecode StartTimecodeOverride;` — `UPROPERTY(EditAnywhere, Category = "Input Sequence", AdvancedDisplay, meta = (EditCondition = "bEnableStartTimecodeOverride"))` — Specify a start time code for the input sequence. This will override the start time code from the input media.
- L134 _public member_ `ETmvMediaTranscodeOutputFormat OutputFormat = ETmvMediaTranscodeOutputFormat::Container;` — `UPROPERTY(EditAnywhere, Category = "Output Sequence", meta = (SegmentedDisplay))` — Select the output format.
- L137 _public member_ `FTmvMediaTranscodeMuxerSettings Muxer;` — `UPROPERTY(EditAnywhere, Category = "Output Sequence", AdvancedDisplay, meta = (EditCondition = "OutputFormat == ETmvMediaTranscodeOutputFormat::Container", EditConditionHides))`
- L141 _public member_ `FDirectoryPath OutputPath;` — `UPROPERTY(EditAnywhere, Category = "Output Sequence")` — The directory to output the processed image sequence files to.
- L145 _public member_ `FString OutputBaseName;` — `UPROPERTY(EditAnywhere, Category = "Output Sequence")` — Specify the output base name. Supports {frame_number} token.
- L149 _public member_ `int32 ZeroPadFrameNumbers = 5;` — `UPROPERTY(EditAnywhere, Category = "Output Sequence", AdvancedDisplay, meta=(ClampMin=0, UIMin=0, EditCondition = "OutputFormat == ETmvMediaTranscodeOutputFormat::FileSequence", EditConditionHides))` — Specify the zero padding on the frame number in the output sequence files.
- L153 _public member_ `bool bMakeOutputAsset = false;` — `UPROPERTY(EditAnywhere, Category = "Output Sequence")` — If enabled, a media source asset will be made for the output sequence.
- L160 _public member_ `FDirectoryPath OutputAssetDirectory;` — `UPROPERTY(EditAnywhere, Category = "Output Sequence", meta = (EditCondition = "bMakeOutputAsset", EditConditionHides, ContentDir))` — Destination content directory for the MediaSource asset to create or update (e.g. /Game/MediaSources) for the output sequence. The asset name itself will be the current job name.
- L167 _public member_ `bool bEnableMipMapping = true;` — `UPROPERTY(EditAnywhere, Category = "Frame Producer")` — If checked, mip maps will be generated and encoded in the final destination. The encoder may restrict the generated mip chain depending on the format requirements.
- L171 _public member_ `bool bUseMediaPlayer = true;` — `UPROPERTY(EditAnywhere, Category = "Frame Producer")` — Use a media player to read the source media.
- L175 _public member_ `int32 NumProducerThreads = 0;` — `UPROPERTY(EditAnywhere, Category = "Frame Producer")` — Number of threads for the frame producer pipeline.

#### enum `ETmvMediaTranscodeJobEvent`  
`enum class ETmvMediaTranscodeJobEvent : uint8`  
_L179-185_
- desc: Job event enumeration used in delegates (for UI refresh mostly)
- L181 _public enumerator_ `JobStarted`
- L182 _public enumerator_ `JobStopped`
- L183 _public enumerator_ `StageStarted`
- L184 _public enumerator_ `StageStopped`

#### enum `ETmvMediaTranscodeJobStatus`  
`enum class ETmvMediaTranscodeJobStatus : int8`  
_L188-194_
- desc: Transcode Job Status.
- L190 _public enumerator_ `None`
- L191 _public enumerator_ `Running`
- L192 _public enumerator_ `Stopping`
- L193 _public enumerator_ `Stopped`

#### enum `ETmvMediaTranscodeJobStopReason`  
`enum class ETmvMediaTranscodeJobStopReason : uint8`  
_L201-207_
- reflection: `UENUM(BlueprintType)`
- desc: Information about the reason for job to be stopped. This is used for monitoring the job's state.
- L203 _public enumerator_ `None`
- L204 _public enumerator_ `Completed`
- L205 _public enumerator_ `Cancelled`
- L206 _public enumerator_ `Discarded`

#### struct `FTmvMediaTranscodingJobStats`  
`struct FTmvMediaTranscodingJobStats`  
_L210-229_
- reflection: `USTRUCT()`
- L216 _public member_ `double StartTime = 0.0;` — `UPROPERTY()` — Absolute start time. Allows to measure how long it has been running.
- L220 _public member_ `double StopTime = 0.0;` — `UPROPERTY()` — Absolute stop time. Allows to measure how long it has been running. Only valid once the job is stopped.
- L224 _public member_ `int32 ProcessedFrame = 0;` — `UPROPERTY()` — Current processed frame.
- L228 _public member_ `int32 TotalFramesToProcess = 0;` — `UPROPERTY()` — Total number of frames to process.

#### class `UTmvMediaTranscodeJob`  
`class UTmvMediaTranscodeJob : public UObject`  
_L247-455_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The transcode job implements a staged transcoding pipeline. The stages are pre-determined and described as follows (in that order): - FrameProducer: media source, produces the frames that are pushed to the frame converter. - FrameConverter: Bridges the producer and encoder. It will inspect the needed format for encoder and produce the appropriate conversion. - FrameEncoder: Receives frames ready (in the right format) to be encoded by a tmv encoder. It will query the muxer stage to get an access unit. - FrameMuxer: Final stage of the pipeline that will typically write to file or media container. There can only be one stage of each class per pipeline and the order is fixed as listed above. Todo - Audio and other streams: The current implementation only deals with a single video stream. For audio streams, we will need to make the pipeline more complex and deal with different streams into a common muxer stage.
- L251 _public prototype_ `UTmvMediaTranscodeJob();`
- L254 _public prototype_ `void SetId(const FGuid& InId);` — Update the id of a job.
- L257 _public function_ `const FGuid& GetId() const` — Returns Job Id.
- L266 _public prototype_ `bool Start(double InCurrentTime);` — Start the job. @param InCurrentTime Absolute application time
- L276 _public prototype_ `void RequestStop(double InCurrentTime, ETmvMediaTranscodeJobStopReason InReason);` — Request Stop (cancel) the job. This will request a stop for all stages and return immediately. The async tasks will not stop immediately. The job should keep ticking until then. @param InCurrentTime Absolute application time @param InReason Indicate the reason for stopping (completed, cancelled, etc)
- L284 _public prototype_ `void Discard(double InCurrentTime);` — When the job is done and will not be used anymore, explicitly discarding it to remove it from the job manager. @param InCurrentTime Absolute application time
- L287 _public prototype_ `void Tick(const FTmvMediaTranscodeJobTime& InTime);` — Tick called in the main thread. Performs sync tasks.
- L290 _public prototype_ `bool IsCompleted() const;` — Determine the global status of the jobs to see if it is completed or not.
- L293 _public prototype_ `bool AreStagesStopped() const;` — Returns true if all the stages are stopped.
- L296 _public function_ `bool IsRunning() const` — Returns true if overall job status is running.
- L306 _public function_ `template <typename TStageClass> TStageClass* GetStage() const` — Get the specified stage from the stage class. There is only one stage of each type in the pipeline.
- L320 _public function_ `bool AddStage(UTmvMediaTranscodeStage* InStage)` — Add the specified stage to the pipeline.
- L332 _public function_ `void SetNotificationHandler(const TSharedPtr<ITmvMediaTranscodeNotification>& InNotification)` — (Optional) Set a notification handler that will be used for progress update display.
- L341 _public function_ `static void SafeReportError(UTmvMediaTranscodeJob* InJob, const FText& InErrorMessage)` — Called by the processing stages in case a fatal error requires the job to stop. Checks if the job is valid before reporting the error.
- L356 _public function_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnTranscodeJobEvent, UTmvMediaTranscodeJob* , ETmvMediaTranscodeJobEvent , UTmvMediaTranscodeStage* ) FOnTranscodeJobEvent& GetOnTranscodeJobEvent()` — Job Event Delegate.
- L363 _public function_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnTranscodeJobFinished, UTmvMediaTranscodeJob* ) FOnTranscodeJobFinished& GetOnTranscodeJobFinished()` — Job Finished Delegate.
- L370 _public function_ `static void SafeBroadcastJobEvent(UTmvMediaTranscodeJob* InJob, ETmvMediaTranscodeJobEvent InEvent, UTmvMediaTranscodeStage* InStage)` — Helper function to broadcast a job event.
- L379 _public function_ `static void SafeBroadcastJobFinished(UTmvMediaTranscodeJob* InJob)` — Helper function to broadcast job finished event.
- L388 _public function_ `static void SafeUpdateProgress(UTmvMediaTranscodeJob* InJob, int32 InCurrentFrame, int32 InTotalFrames)` — Helper function to update the job progress stats.
- L397 _public prototype_ `void UpdateProgress(int32 InCurrentFrame, int32 InTotalFrames);` — Update job progress stats.
- L400 _public prototype_ `FTmvMediaTranscodingJobStats GetJobStats() const;` — Returns a copy of job stats (thread safe).
- L403 _public prototype_ `virtual void BeginDestroy() override;`
- L408 _private prototype_ `void OnStopped(double InCurrentTime);` — Called when the job stopped (all stages have stopped).
- L412 _public member_ `FString JobName;` — Original Job Item Name.
- L416 _public member_ `FTmvMediaTranscodeJobSettings Settings;` — `UPROPERTY()` — Common job settings.
- L420 _public member_ `TArray<TObjectPtr<UTmvMediaTranscodeStage>> Stages;` — `UPROPERTY()` — Stages in this pipeline.
- L427 _public member_ `std::atomic<ETmvMediaTranscodeJobStatus> JobStatus = ETmvMediaTranscodeJobStatus::None;` — Overall job state. It is driven by control functions like Start, Stop and then synchronized with the stage's state in the Tick function.
- L430 _public member_ `std::atomic<bool> bIsError = false;` — Indicate a stage had an error somewhere that requires the job to stop.
- L433 _public member_ `ETmvMediaTranscodeJobStopReason StopReason = ETmvMediaTranscodeJobStopReason::None;` — Keep track of the stopping reason. This is mostly used for UI and logging.
- L437 _protected member_ `TSharedPtr<ITmvMediaTranscodeNotification> Notification;` — Notification object that lets the job propagate notifications to UI.
- L439 _protected member_ `FOnTranscodeJobFinished TranscodeJobFinishedDelegate;`
- L440 _protected member_ `FOnTranscodeJobEvent TranscodeJobEventDelegate;`
- L443 _protected member_ `mutable FCriticalSection JobStatsLock;` — Job Stats critical section.
- L446 _protected member_ `FTmvMediaTranscodingJobStats JobStats;` — Job statistics.
- L454 _private member_ `FGuid Id;` — `UPROPERTY()` — Unique Id of this job item (from a corresponding job list). Used to find the executing job in the job manager (local thread, remote process).

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TMVMEDIA_API`
- L356 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnTranscodeJobEvent, UTmvMediaTranscodeJob* , ETmvMediaTranscodeJobEvent , UTmvMediaTranscodeStage* ) FOnTranscodeJobEvent& GetOnTranscodeJobEvent() { return TranscodeJobEventDelegate; } DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnTranscodeJobFinished, UTmvMediaTranscodeJob* ) FOnTranscodeJobFinished& GetOnTranscodeJobFinished() { return TranscodeJobFinishedDelegate; } static void SafeBroadcastJobEvent(UTmvMediaTranscodeJob* InJob, ETmvMediaTranscodeJobEvent InEvent, UTmvMediaTranscodeStage* InStage) { if (IsValid(InJob)) { InJob->TranscodeJobEventDelegate.Broadcast(InJob, InEvent, InStage); } } static void SafeBroadcastJobFinished(UTmvMediaTranscodeJob* InJob) { if (IsValid(InJob)) { InJob->TranscodeJobFinishedDelegate.Broadcast(InJob); } } static void SafeUpdateProgress(UTmvMediaTranscodeJob* InJob, int32 InCurrentFrame, int32 InTotalFrames) { if (IsValid(InJob)) { InJob->UpdateProgress(InCurrentFrame, InTotalFrames); } }` — Job Event Delegate.
- L363 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnTranscodeJobFinished, UTmvMediaTranscodeJob* ) FOnTranscodeJobFinished& GetOnTranscodeJobFinished() { return TranscodeJobFinishedDelegate; } static void SafeBroadcastJobEvent(UTmvMediaTranscodeJob* InJob, ETmvMediaTranscodeJobEvent InEvent, UTmvMediaTranscodeStage* InStage) { if (IsValid(InJob)) { InJob->TranscodeJobEventDelegate.Broadcast(InJob, InEvent, InStage); } } static void SafeBroadcastJobFinished(UTmvMediaTranscodeJob* InJob) { if (IsValid(InJob)) { InJob->TranscodeJobFinishedDelegate.Broadcast(InJob); } } static void SafeUpdateProgress(UTmvMediaTranscodeJob* InJob, int32 InCurrentFrame, int32 InTotalFrames) { if (IsValid(InJob)) { InJob->UpdateProgress(InCurrentFrame, InTotalFrames); } } void UpdateProgress(int32 InCurrentFrame, int32 InTotalFrames);` — Job Finished Delegate.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Transcoder/TmvMediaTranscodeJobBuilder.h` (Public)


#### class `FTmvMediaTranscodeJobBuilder`  
`class FTmvMediaTranscodeJobBuilder`  
_L59-114_
- desc: Fluent builder for UTmvMediaTranscodeJob. Assembles the standard pipeline stages (frame producer, frame converter, frame encoder, muxer) from a transcode list item. Each stage class can be overridden independently; omitted overrides pick sensible defaults based on the item's settings: - Frame producer : UTmvMediaPlayerFrameProducer or UTmvMediaFileSequenceFrameProducer based on Settings.bUseMediaPlayer. - Frame converter: UTmvMediaFrameConverter. - Frame encoder  : UTmvMediaTmvFrameEncoder. Receives the item's EncoderOptions. - Muxer          : UTmvMediaContainerTranscodeMuxer when Settings.OutputFormat == Container, UTmvMediaFileSequenceTranscodeMuxer otherwise. A post-build hook can be registered to run additional configuration after every stage has been created and the encoder options applied (e.g. setting track info on the producer, adding editor-only extension tasks). The builder captures the provided job item by reference; callers must keep it alive until Build() returns. Binding to a temporary is rejected at compile time (see the deleted rvalue constructor overload below). The returned job is NOT started. Example: @code UTmvMediaTranscodeJob* Job = FTmvMediaTranscodeJobBuilder(Item) .WithFrameProducerClass(UTmvMediaFrameProducer::StaticClass()) .OnPostBuild(FOnTranscodeJobBuilt::CreateLambda([Rate](UTmvMediaTranscodeJob* Job) { if (UTmvMediaFrameProducer* P = Job->GetStage<UTmvMediaFrameProducer>()) { FTmvMediaFrameProducerTrackInfo Info; Info.FrameRate = Rate; P->SetV
- L63 _public prototype_ `explicit FTmvMediaTranscodeJobBuilder(const FTmvMediaTranscodeListItem& InJobItem);` — Construct a builder for the given job item. The item must outlive Build().
- L66 _public prototype_ `FTmvMediaTranscodeJobBuilder(FTmvMediaTranscodeListItem&&) = delete;` — The builder stores InJobItem by reference, so a temporary would dangle immediately. Reject at compile time.
- L69 _public prototype_ `FTmvMediaTranscodeJobBuilder& WithOuter(UObject* InOuter);` — Outer for the created job. Defaults to the transient package when not set.
- L72 _public prototype_ `FTmvMediaTranscodeJobBuilder& WithFrameProducerClass(TSubclassOf<UTmvMediaFrameProducer> InClass);` — Override the frame producer class.
- L75 _public prototype_ `FTmvMediaTranscodeJobBuilder& WithFrameConverterClass(TSubclassOf<UTmvMediaFrameConverter> InClass);` — Override the frame converter class.
- L78 _public prototype_ `FTmvMediaTranscodeJobBuilder& WithFrameEncoderClass(TSubclassOf<UTmvMediaFrameEncoder> InClass);` — Override the frame encoder class.
- L81 _public prototype_ `FTmvMediaTranscodeJobBuilder& WithMuxerClass(TSubclassOf<UTmvMediaTranscodeMuxer> InClass);` — Override the muxer class.
- L84 _public prototype_ `FTmvMediaTranscodeJobBuilder& OnPostBuild(FOnTranscodeJobBuilt InDelegate);` — Register a hook invoked on the assembled job before Build returns.
- L91 _public prototype_ `[[nodiscard]] UTmvMediaTranscodeJob* Build(FTmvMediaMessageContext* OutMessageContext = nullptr) const;` — Instantiate the job and return it. Does not call Start. @param OutMessageContext Optional message context to accumulate build errors. @return Instantiated job or null if there is a build error.
- L94 _private member_ `const FTmvMediaTranscodeListItem& JobItem;`
- L95 _private member_ `TObjectPtr<UObject> Outer;`
- L99 _private member_ `TSubclassOf<UTmvMediaFrameProducer> FrameProducerClass;` — Caller override for the frame producer stage class. When null, Build picks UTmvMediaPlayerFrameProducer or UTmvMediaFileSequenceFrameProducer based on JobItem.Settings.bUseMediaPlayer.
- L102 _private member_ `TSubclassOf<UTmvMediaFrameConverter> FrameConverterClass;` — Caller override for the frame converter stage class. When null, Build uses UTmvMediaFrameConverter.
- L105 _private member_ `TSubclassOf<UTmvMediaFrameEncoder> FrameEncoderClass;` — Caller override for the frame encoder stage class. When null, Build uses UTmvMediaTmvFrameEncoder.
- L109 _private member_ `TSubclassOf<UTmvMediaTranscodeMuxer> MuxerClass;` — Caller override for the muxer stage class. When null, Build picks UTmvMediaContainerTranscodeMuxer or UTmvMediaFileSequenceTranscodeMuxer based on JobItem.Settings.OutputFormat.
- L113 _private member_ `FOnTranscodeJobBuilt PostBuildDelegate;` — Delegate fired on the assembled job just before Build returns. Used by callers to perform extra wiring (e.g. SetVideoTrackInfo on the producer, adding editor-only extension tasks) on top of the standard pipeline.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TMVMEDIA_API`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTranscodeJobBuilt, UTmvMediaTranscodeJob* );` — Delegate invoked on a fully-assembled job just before the builder returns it (Start has not been called).
- L21 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTranscodeJobBuilt, UTmvMediaTranscodeJob* );` — Delegate invoked on a fully-assembled job just before the builder returns it (Start has not been called).

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Transcoder/TmvMediaTranscodeList.h` (Public)


#### struct `FTmvMediaTranscodeListItem`  
`struct FTmvMediaTranscodeListItem`  
_L18-41_
- reflection: `USTRUCT(BlueprintType)`
- desc: Transcode Job item Holds all the settings to be able to execute a transcode job.
- L28 _public member_ `FGuid Id;` — `UPROPERTY()` — Unique Id of this job item. Used to find the executing job in the job manager (local or external, etc).
- L32 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Media")` — Job name for display purposes.
- L36 _public member_ `FTmvMediaTranscodeJobSettings Settings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Media")` — Common job settings.
- L40 _public member_ `TInstancedStruct<FTmvMediaEncoderOptions> EncoderOptions;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Media")` — Encoder specific settings.

#### enum `ETmvMediaTranscodeListItemEventType`  
`enum class ETmvMediaTranscodeListItemEventType`  
_L44-56_
- desc: Transcode list editing events
- L47 _public enumerator_ `None` — Unspecified event type.
- L49 _public enumerator_ `ItemsAdded` — Item(s) added to the list.
- L51 _public enumerator_ `ItemsRemoved` — Item(s) removed from the list.
- L53 _public enumerator_ `ItemsReordered` — Item(s) reordered in the list.
- L55 _public enumerator_ `ItemsModified` — Item(s) properties modified.

#### struct `FTmvMediaTranscodeListItemEventArgs`  
`struct FTmvMediaTranscodeListItemEventArgs`  
_L59-63_
- desc: Transcode list editing event arguments
- L61 _public member_ `ETmvMediaTranscodeListItemEventType Type = ETmvMediaTranscodeListItemEventType::None;`
- L62 _public member_ `TArray<int32, TInlineAllocator<1>> ItemIndices;`

#### class `UTmvMediaTranscodeList`  
`class UTmvMediaTranscodeList : public UObject`  
_L71-159_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, BlueprintType)`
- inherits: `UObject`
- desc: Transcode Job (settings) List This object is a container for transcode job settings.
- L76 _public member_ `static FTmvMediaTranscodeListItem InvalidItem;`
- L79 _public function_ `int32 GetNumItems() const` — Returns the number of job items in the list.
- L85 _public function_ `bool IsValidItemIndex(int32 InItemIndex) const` — Returns true if the given index is a valid item.
- L91 _public function_ `const FTmvMediaTranscodeListItem& GetItem(int32 InItemIndex) const` — Returns the job item at given index.
- L97 _public function_ `FTmvMediaTranscodeListItem* GetItemMutable(int32 InItemIndex)` — Returns the job item at given index.
- L107 _public prototype_ `void InsertItemAt(int32 InItemIndex, const FTmvMediaTranscodeListItem* InItem = nullptr);` — Insert a new item or duplicate provided one at the given index in the list. @param InItemIndex Index in the list where to insert the new item. @param InItem Item to be duplicated if provided.
- L110 _public prototype_ `bool RemoveItemAt(int32 InItemIndex);` — Remove item at the given index.
- L113 _public prototype_ `void RemoveItems(TConstArrayView<int32> InItemIndices);` — Remove items at given indices.
- L120 _public prototype_ `bool ReorderItems(int32 InFromIndex, int32 InToIndex);` — Reorder an item from the given source index to the destination index. @remark This function will broadcast the FOnItemEvent. @return true if the operation completed, false if the indices where not valid.
- L130 _public prototype_ `static bool ValidateJobItem(const FTmvMediaTranscodeListItem& InJobItem, FString* OutError = nullptr);` — Returns true if the given job item has the minimum configuration required to be executed. Checks that the input/output paths are set and that bMakeOutputAsset is consistent with OutputAssetDirectory. @param InJobItem Item to validate. @param OutError  Optional. When the item is invalid, receives a newline-separated list of reasons. @return true if the item is valid.
- L133 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemEvent, const UTmvMediaTranscodeList* , const FTmvMediaTranscodeListItemEventArgs&);` — Delegate for item editing events.
- L134 _public function_ `FOnItemEvent& GetOnItemEvent()`
- L140 _public prototype_ `virtual void PostLoad() override;`
- L142 _public prototype_ `virtual void PostEditUndo() override;`
- L148 _private prototype_ `FString GenerateNewItemName() const;` — Generates a unique new item name of the form "JobItem_N".
- L151 _private prototype_ `FString GenerateDuplicateName(const FString& InSourceName) const;` — Generates a unique duplicate name for the given source name, e.g. "Foo_Dup", "Foo_Dup2".
- L155 _private member_ `TArray<FTmvMediaTranscodeListItem> Items;` — `UPROPERTY()` — Main list of all job items.
- L158 _private member_ `FOnItemEvent OnItemEvent;` — Delegate for item editing events.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TMVMEDIA_API`
- L133 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemEvent, const UTmvMediaTranscodeList* , const FTmvMediaTranscodeListItemEventArgs&);` — Delegate for item editing events.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Transcoder/TmvMediaTranscodeMuxer.h` (Public)


#### class `UTmvMediaTranscodeMuxer`  
`class UTmvMediaTranscodeMuxer : public UTmvMediaTranscodeStage`  
_L20-71_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UTmvMediaTranscodeStage`
- desc: Abstract base class for muxer stage of transcode pipeline. @see UTmvMediaTranscodeJob
- L32 _public prototype_ `virtual int32 OpenStream(UTmvMediaTranscodeJob* InParentJob, const FString& InStreamName, const FString& InExtension) PURE_VIRTUAL(UTmvMediaTranscodeMuxer::OpenStream, return INDEX_NONE;);` — Opens a stream. @param InParentJob Parent Job this stage is part of. @param InStreamName Name given to the stream (will be used for filename prefix in case of file sequence muxer). @param InExtension Extension for the filename in case of file sequence muxer. @return Index of the stream or INDEX_NONE in case of error.
- L37 _public prototype_ `virtual void ReceiveAccessUnit( UTmvMediaTranscodeJob* InParentJob, int32 InStreamId, const FTmvMediaFrameTimeInfo& TimeInfo, TSharedPtr<TArray64<uint8>>&& InAccessUnit) PURE_VIRTUAL(UTmvMediaTranscodeMuxer::ReceiveAccessUnit,);` — Push an access unit buffer in the stream at the given index (must call OpenStream first).
- L49 _public prototype_ `static FString GetContainerOutputFilePath(const UTmvMediaTranscodeJob* InParentJob, const TSharedPtr<ITmvMediaMuxerFactory, ESPMode::ThreadSafe>& InMuxerFactory = nullptr);` — Utility function to get the absolute container path from job settings. @param InParentJob Parent job to get settings from. @param InMuxerFactory Optional muxer factory. If not specified, the factory is retrieve from job settings. @return Absolute container path, including the extension.
- L56 _public prototype_ `static TSharedPtr<ITmvMediaMuxerFactory, ESPMode::ThreadSafe> FindMuxerFactoryByName(FName InFactoryName);` — Muxer Utility function to find a muxer factory by name. @param InFactoryName Name of the muxer factory to find. @return muxer factory if found, nullptr otherwise.
- L67 _protected member_ `TArray<FStreamInfo> Streams;` — Array of currently opened streams.
- L70 _protected member_ `FCriticalSection StreamsCS;` — Critical section for the stream array.

#### struct `UTmvMediaTranscodeMuxer::FStreamInfo`  
`struct FStreamInfo`  
_L60-64_
- desc: Stream information
- L62 _public member_ `FString StreamName;`
- L63 _public member_ `FString Extension;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Transcoder/TmvMediaTranscodeStage.h` (Public)


#### struct `FTmvMediaTranscodeJobTime`  
`struct FTmvMediaTranscodeJobTime`  
_L15-21_
- desc: Time arguments for job management.
- L18 _public member_ `double CurrentTime = 0.0;` — Absolute application time.
- L20 _public member_ `float DeltaTime = 0.0f;` — Time since last tick

#### enum `ETmvMediaTranscodeStageStatus`  
`enum class ETmvMediaTranscodeStageStatus : int8`  
_L24-29_
- desc: Transcode stage status.
- L26 _public enumerator_ `Stopped`
- L27 _public enumerator_ `Started`
- L28 _public enumerator_ `Stopping`

#### class `UTmvMediaTranscodeStage`  
`class UTmvMediaTranscodeStage : public UObject`  
_L36-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class for a media transcoding pipeline stage. @see UTmvMediaTranscodeJob
- L41 _public function_ `virtual bool Start(UTmvMediaTranscodeJob* InParentJob)` — Start the stage.
- L54 _public function_ `virtual void RequestStop(UTmvMediaTranscodeJob* InParentJob)` — This will request the stage to stop. The state of the stage will be set to either Stopping or Stopped. If the stage has async tasks, it will not stop immediately. The stage should be kept ticking until all async tasks stop.
- L61 _public function_ `virtual void Tick(UTmvMediaTranscodeJob* InParentJob, const FTmvMediaTranscodeJobTime& InTime)` — Tick the job in the main thread to perform the main thread coordination.
- L71 _public function_ `ETmvMediaTranscodeStageStatus GetStageStatus() const` — Returns the current status of the stage.
- L74 _public prototype_ `void SetStageStatus(ETmvMediaTranscodeStageStatus InStatus, UTmvMediaTranscodeJob* InParentJob);` — Change the status of the stage. This will propagate job events.
- L78 _protected member_ `bool bHasAsyncQueue = false;` — Flag indicating if the stage is implementing an async queue.
- L84 _protected prototype_ `void UpdateStatusFromFrameProducer(UTmvMediaTranscodeJob* InParentJob);` — Updates the status of this stage to mirror that of the producer stage. This is the default behavior unless a stage is implementing an async queue.
- L88 _private member_ `std::atomic<ETmvMediaTranscodeStageStatus> StageStatus = ETmvMediaTranscodeStageStatus::Stopped;` — Indicate the status of the stage.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TMVMEDIA_API`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Utils/TTmvMediaSharedObjectPool.h` (Public)


#### class `TTmvMediaSharedObjectPool`  
`template<class ObjectType> class TTmvMediaSharedObjectPool : public TSharedFromThis<TTmvMediaSharedObjectPool<ObjectType>>`  
_L15-116_
- inherits: `TSharedFromThis<TTmvMediaSharedObjectPool<ObjectType>>`
- desc: Pool for worker thread context objects that can be reused within the same stream (i.e. no options changes) to the next when available.
- L83 _public function_ `FHandle Acquire(TFunction<TSharedPtr<ObjectType>()> InAllocatorFunc)` — Acquire an available object from the pool or create a new one. @remark we assume this is for the same stream, no-sub pooling needed.
- L104 _public function_ `void Release(const TSharedPtr<ObjectType>& InObject)` — Returns unused objects to the pool.
- L114 _private member_ `UE::FMutex FreeObjectsMutex;`
- L115 _private member_ `TArray<TSharedPtr<ObjectType>> FreeObjects;`

#### struct `TTmvMediaSharedObjectPool::FHandle`  
`struct FHandle`  
_L20-77_
- desc: Auto clean up handle, puts the context back in the pool.
- L22 _public prototype_ `FHandle() = default;`
- L25 _public prototype_ `FHandle(const FHandle&) = delete;` — Disable copy to avoid adding object back to the pool multiple times.
- L26 _public prototype_ `FHandle& operator=(const FHandle&) = delete;`
- L28 _public function_ `FHandle(FHandle&& Other) noexcept : ReaderObject(MoveTemp(Other.ReaderObject)) , PoolWeak(MoveTemp(Other.PoolWeak))`
- L34 _public function_ `FHandle& operator=(FHandle&& Other) noexcept`
- L45 _public function_ `~FHandle()`
- L50 _public function_ `void Reset()`
- L62 _public function_ `bool IsValid() const`
- L67 _public function_ `ObjectType* operator->() const`
- L72 _public member_ `TSharedPtr<ObjectType> ReaderObject;`
- L75 _private member_ `TWeakPtr<TTmvMediaSharedObjectPool> PoolWeak;`

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Utils/TmvMediaMessageContext.h` (Public)


#### class `FTmvMediaMessageContext`  
`class FTmvMediaMessageContext`  
_L15-39_
- desc: Container for error messages that get accumulated during operations and can be compiled into a report for display in UI or dumped to Logs.
- L19 _public function_ `void Add(const FText& InMessage)` — Adds the given message at the end of the report.
- L25 _public function_ `void Add(FText&& InMessage)` — Adds the given message at the end of the report.
- L33 _public prototype_ `FText ToText() const;` — Compiles the set of errors in a formatted report with each error message on a different line.
- L38 _public member_ `TArray<FText> Messages;` — List of error messages for the given context.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TMVMEDIA_API`
- L52 _macro_ `#define UE_TMV_MEDIA_MESSAGE_LOG(MessageContext, LogCategory, Verbosity, SectionString, MessageText) \` — Helper macro to reduce boilerplate for message reporting. In most cases, we want to both log the message in a log category and add it to the report. We have to use a macro for this to preserve the file/line functionality of the logging system. @param MessageContext Message Report Context to accumulate messages @param LogCategory Log category to log to. @param Verbosity Verbosity of the log. @param SectionString Name of the section this log will be part of. @param MessageText Formatted message.

### `Plugins/Media/TmvMedia/Source/TmvMedia/Public/Utils/TmvMediaUtils.h` (Public)


#### struct `FTmvMediaUtils`  
`struct FTmvMediaUtils`  
_L14-35_
- desc: Collections of small utility functions to help implement Tmv related features. @remark Avoid requiring engine includes (if possible).
- L23 _public function_ `static int32 GetMaxMipCountFromDimensions(int32 InWidth, int32 InHeight)` — Returns the maximum number of mips that constitute a full mip chain for the given dimensions. @param InWidth Width in pixels of mip 0 to be considered. @param InHeight Height in of mip 0 to be considered. @return Number of mips, 0 in case of invalid calculation.

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace TmvMedia` (scope `UE`)
- L37 _namespace_ `namespace Utils` (scope `UE::TmvMedia`)
- L47 _function_ `template<typename InEnumType> FString StaticEnumToString(InEnumType InValue)` (scope `UE::TmvMedia::Utils`) — Converts an enum value to a string for logging purposes. @tparam InEnumType Enum type, must be UENUM defined. @param InValue Value @return short name of the value.
- L57 _function_ `template<typename InEnumType> FText StaticEnumToText(InEnumType InValue)` (scope `UE::TmvMedia::Utils`)
- L70 _function_ `inline constexpr uint32 MakeFourCC(const uint8 A, const uint8 B, const uint8 C, const uint8 D)` (scope `UE::TmvMedia::Utils`) — Constructs a FourCC integer from four 8-bit character codes, commonly used for identifying file formats, codec types, or pixel formats.
- L78 _function_ `inline FString FourCCToString(uint32 InFourCC)` (scope `UE::TmvMedia::Utils`) — Returns the string made out of the 4 character codes from the given FourCC value.
