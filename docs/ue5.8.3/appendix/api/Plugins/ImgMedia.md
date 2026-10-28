# Plugins / ImgMedia

- module root: `Plugins/Media/ImgMedia/Source/ImgMedia`
- headers: 27; symbols: 700
- symbol kinds: class=26, delegate=3, enum=1, enumerator=4, function=110, macro=6, member=249, namespace=11, prototype=263, struct=16, typedef=2, variable=9
- DynamicallyLoadedModuleNames: Media
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, ExrReaderGpu, ImageCore, ImgMediaEngine, ImgMediaFactory, MediaUtils, MovieScene, OpenExrWrapper, RHI, RenderCore, Renderer, Slate, SlateCore, TmvMedia
- PrivateIncludePathModuleNames: Media
- PublicDependencyModuleNames: MediaAssets, TimeManagement, UnrealEd

### `Plugins/Media/ImgMedia/Source/ImgMedia/Internal/Assets/ImgMediaTileVisibilityResolver.h` (Internal)


#### class `FImgMediaTileVisibilityResolver`  
`class FImgMediaTileVisibilityResolver`  
_L15-77_
- desc: Per-loader manager that gathers tile-visibility requests from registered providers and produces a merged snapshot for loader workers to consume.
- L18 _public prototype_ `FImgMediaTileVisibilityResolver();`
- L21 _public prototype_ `~FImgMediaTileVisibilityResolver();` — Unsubscribes from every live provider so a late broadcast cannot reach the dying resolver.
- L24 _public prototype_ `void SetSequenceInfo(const FMediaSequenceInfo& InInfo);` — Set the sequence (size, tiling, mip count) used when resolving tiles. Invalidates the snapshot.
- L27 _public prototype_ `FMediaSequenceInfo GetSequenceInfo() const;` — Get the current sequence info. Thread-safe.
- L30 _public prototype_ `void RegisterProvider(TSharedRef<IMediaTileVisibilityProvider> InProvider);` — Add a provider. Deduplicates against existing weak refs; invalidates the snapshot on success.
- L33 _public prototype_ `void UnregisterProvider(const TSharedRef<IMediaTileVisibilityProvider>& InProvider);` — Remove a provider. Safe to call when not registered; invalidates the snapshot.
- L36 _public prototype_ `void ClearProviders();` — Drop all registered providers and the cached snapshot.
- L39 _public prototype_ `int32 NumProviders() const;` — Count of currently-alive providers (expired weak refs are pruned by this call).
- L42 _public prototype_ `bool HasProviders() const;` — True if at least one alive provider is registered.
- L45 _public prototype_ `void InvalidateSnapshot();` — Force the next GetSnapshot to rebuild. Called once per frame from FImgMediaLoader::TickFrame.
- L48 _public prototype_ `TSharedPtr<FMediaTileVisibilityRequest, ESPMode::ThreadSafe> GetSnapshot();` — Get the merged tile-visibility request, lazily rebuilt if invalidated. Thread-safe.
- L51 _public prototype_ `int32 GetMinimumMipLevelToUpscale();` — Convenience: returns the snapshot's MipLevelToUpscale, or -1 if disabled.
- L54 _public prototype_ `void AddVisibilitySnapshotDebugOverlay();` — Push the current snapshot's mip list and tile count to the on-screen debug overlay.
- L64 _private prototype_ `static void UnsubscribeFromProvider(FProviderEntry& InOutEntry);` — Removes the OnInputsChanged subscription if the provider is still alive and clears the handle.
- L67 _private member_ `mutable FCriticalSection Mutex;` — Guards Providers, SequenceInfo, and CachedSnapshot.
- L70 _private member_ `TArray<FProviderEntry> Providers;` — Registered providers held weakly; the consumer owns the strong reference.
- L73 _private member_ `FMediaSequenceInfo SequenceInfo;` — The sequence we resolve tiles for.
- L76 _private member_ `TSharedPtr<FMediaTileVisibilityRequest, ESPMode::ThreadSafe> CachedSnapshot;` — Lazily-built merged snapshot returned by GetSnapshot; null when invalidated.

#### struct `FImgMediaTileVisibilityResolver::FProviderEntry`  
`struct FProviderEntry`  
_L57-61_
- L59 _public member_ `TWeakPtr<IMediaTileVisibilityProvider> Weak;`
- L60 _public member_ `FDelegateHandle OnInputsChangedHandle;`

### `Plugins/Media/ImgMedia/Source/ImgMedia/Internal/Loader/ImgMediaLoader.h` (Internal)


#### struct `FImgMediaLoaderSmartCacheSettings`  
`struct FImgMediaLoaderSmartCacheSettings`  
_L34-47_
- desc: Settings for the smart cache.
- L37 _public member_ `bool bIsEnabled;` — True if we are using the smart cache.
- L39 _public member_ `float TimeToLookAhead;` — The cache will fill up with frames that are up to this time from the current time.
- L42 _public function_ `FImgMediaLoaderSmartCacheSettings(bool bInIsEnabled, float InTimeToLookAhead) : bIsEnabled(bInIsEnabled) , TimeToLookAhead(InTimeToLookAhead)` — Constructor.

#### struct `FImgMediaLoaderBandwidth`  
`struct FImgMediaLoaderBandwidth`  
_L52-75_
- desc: Sequence playback bandwidth requirements and estimates.
- L55 _public member_ `float Current;` — Number of bytes read per second from the last frame read.
- L57 _public member_ `float Effective;` — Average bandwidth over time (including idle time).
- L59 _public member_ `float Required;` — Minimum number of bytes per second needed to read all mip levels.
- L62 _public prototype_ `FImgMediaLoaderBandwidth();` — Constructor.
- L65 _public prototype_ `void Update(const TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe>& Frame, double WorkTime);` — Updated calculated current and effective bandwidth numbers.
- L68 _public prototype_ `void EmptyCache();` — Empty the read times cache and resets its index.
- L72 _private member_ `TArray<TPair<double, double>> ReadTimeCache;` — Work time cache for average bandwidth calculation.
- L74 _private member_ `int32 ReadTimeCacheIndex;` — Circular index for work time cache calculation.

#### class `FImgMediaLoader`  
`class FImgMediaLoader : public TSharedFromThis<FImgMediaLoader, ESPMode::ThreadSafe>`  
_L80-790_
- inherits: `TSharedFromThis<FImgMediaLoader,ESPMode::ThreadSafe>`
- desc: Loads image sequence frames from disk.
- L99 _public prototype_ `FImgMediaLoader(const TSharedRef<FImgMediaScheduler, ESPMode::ThreadSafe>& InScheduler, const TSharedRef<FImgMediaGlobalCache, ESPMode::ThreadSafe>& InGlobalCache, const TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe>& InSourceColorSettings, bool bInFillGapsInSequence, const FString& InLayerName, const FImgMediaLoaderSmartCacheSettings& InSmartCacheSettings, IMediaEventSink* InEventSink = nullptr, const FGuid& InPlayerGuid = FGuid());` — Create and initialize a new instance. @param InScheduler               The scheduler for image loading. @param InGlobalCache             The global frame cache shared across loaders. @param InSourceColorSettings     Color space and encoding overrides for the source, or null for defaults. @param bInFillGapsInSequence     If true, gaps in the image sequence are filled with blank frames. @param InLayerName               EXR layer to select. Empty string reads the default (un-prefixed) channels. @param InSmartCacheSettings      Settings controlling the smart cache pre-fetching behavior. @param InEventSink               Optional event sink for Internal_RequestVideoSampleRefresh; the caller owns the sink and must keep it alive. Null disables. @param InPlayerGuid              Player's identifier (same value lives on FMediaPlayerFacade and FImgMediaPlayer); used in log lines for cross-layer correlation. Defaults to an empty GUID.
- L109 _public prototype_ `virtual ~FImgMediaLoader();` — Virtual destructor.
- L117 _public prototype_ `void TickFrame();` — Per-frame tick driven from FImgMediaPlayer::TickInput. Invalidates the tile-visibility snapshot so the next frame's first worker rebuilds it, and (when enabled) draws the debug overlay for the previous frame's snapshot. Called on the game thread, bounded by the player's lifetime.
- L121 _public member_ `static constexpr int32 MAX_MIPMAP_LEVELS = 32;` — Max number of mip map levels supported.
- L128 _public prototype_ `uint64 GetBitRate() const;` — Get the data bit rate of the video frames. @return Data rate (in bits per second).
- L132 _public function_ `float GetCurrentBandwidth() const` — Get the number of bytes read per second from the last frame read.
- L134 _public function_ `float GetEffectiveBandwidth() const` — Get the effective bandwidth.
- L136 _public function_ `float GetRequiredBandwidth() const` — Get the minimum number of bytes per second needed to read all mip levels.
- L146 _public prototype_ `void GetBusyTimeRanges(TRangeSet<FTimespan>& OutRangeSet) const;` — Get the time ranges of frames that are being loaded right now. @param OutRangeSet Will contain the set of time ranges. @return true on success, false otherwise. @see GetCompletedTimeRanges, GetPendingTimeRanges
- L155 _public prototype_ `void GetCompletedTimeRanges(TRangeSet<FTimespan>& OutRangeSet) const;` — Get the time ranges of frames that are are already loaded. @param OutRangeSet Will contain the set of time ranges. @return true on success, false otherwise. @see GetBusyTimeRanges, GetPendingTimeRanges
- L163 _public function_ `const FString& GetInfo() const` — Get the information string for the currently loaded image sequence. @return Info string. @see GetSequenceDuration, GetSamples
- L171 _public prototype_ `void Seek(const FMediaTimeStamp& SeekTarget, bool bReverse);` — Notify loader out a seek
- L182 _public prototype_ `IMediaSamples::EFetchBestSampleResult FetchBestVideoSampleForTimeRange(const TRange<FMediaTimeStamp>& TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample, bool bIsLoopingEnabled, float PlayRate);` — Tries to get the best sample for a given time range. @param TimeRange is the range to check for. @param OutSample will be filled in with the sample if found. @param bIsLoopingEnabled True if we can loop. @param PlayRate How fast we are playing. @return Return code indicating status (ok, unsupported, no sample)
- L193 _public prototype_ `bool PeekVideoSampleTime(FMediaTimeStamp& TimeStamp, bool bIsLoopingEnabled, float PlayRate, const FTimespan& CurrentTime);` — Checks to see if a sample is available at the specificed time. @param TimeStamp Will be filled in with the time stamp of the sample if a sample is found. @param bIsLoopingEnabled True if we can loop. @param PlayRate How fast we are playing. @param CurrentTime Time to get a sample for. @return True if a sample is available.
- L198 _public prototype_ `bool DiscardVideoSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bIsLoopingEnabled, float PlayRate);` — Discard any samples in the given range from the output "queue" (logically)
- L207 _public prototype_ `void GetPendingTimeRanges(TRangeSet<FTimespan>& OutRangeSet) const;` — Get the time ranges of frames that are pending to be loaded. @param OutRangeSet Will contain the set of time ranges. @return true on success, false otherwise. @see GetBusyTimeRanges, GetCompletedTimeRanges
- L213 _public function_ `bool IsReaderValid() const` — Returns true if the reader is valid. Used to validate if it is safe to call GetReader().
- L223 _public function_ `TSharedRef<IImgMediaReader, ESPMode::ThreadSafe> GetReader() const` — Get the image reader object used by this loader. @return The image reader.
- L234 _public function_ `const TSharedPtr<FImgMediaTileVisibilityResolver, ESPMode::ThreadSafe>& GetTileVisibilityResolver() const` — Get the tile-visibility resolver used by this loader. Always non-null; consumers register providers on this to influence which tiles get loaded. When no providers register, the loader falls back to loading every tile at every mip level.
- L240 _public function_ `const FGuid& GetPlayerGuid() const` — Player identifier mirrored from FImgMediaPlayer; useful for cross-layer log correlation.
- L253 _public function_ `const FIntPoint& GetSequenceDim() const` — Get the width and height of the image sequence. The dimensions of the image sequence are determined by reading the attributes of the first image. The dimensions of individual image frames in the sequence are allowed to differ. However, this usually indicates a mistake in the content creation pipeline and will be logged out as such. @return Sequence dimensions. @see GetSequenceDuration, GetSequenceFps
- L264 _public function_ `FTimespan GetSequenceDuration() const` — Get the total duration of the image sequence. @return Duration. @see GetSequenceDim, GetSequenceFps
- L279 _public function_ `FFrameRate GetSequenceFrameRate() const` — Get the sequence's frame rate. The frame rate of the image sequence is determined by reading the attributes of the first image. Individual image frames may specify a different frame rate, but it will be ignored during playback. @return The frame rate. @see GetSequenceDuration, GetSequenceDim
- L291 _public prototype_ `const FString& GetImagePath(int32 FrameNumber, int32 MipLevel) const;` — Get the path to images in the sequence. @param FrameNumber Frame to get. @param MipLevel Mip level to get. @return Returns path and filename of image.
- L294 _public function_ `const FString& GetLayerName() const` — Gets the layer name being read in the sequence, if the images are EXR images
- L299 _public function_ `int32 GetNumMipLevels() const` — Get the number of mipmap levels we have.
- L307 _public function_ `SIZE_T GetNumBytesPerPixel() const` — Get the number of bytes per pixel for each image.
- L315 _public function_ `int32 GetMinimumLevelToUpscale() const` — Get the minumum mip level to upscale to lower quality mips (-1 if disabled).
- L323 _public function_ `bool MipsInSeparateFiles() const` — If mips are stored in separate files we should make sure to read it.
- L333 _public function_ `int32 GetNumImages() const` — Get the number of images/frames in a single mip level. @return Number of images.
- L343 _public function_ `bool IsContainerFile() const` — Whether the source is a container file (e.g. .tmv) rather than a file sequence.
- L351 _public function_ `int32 GetNumTilesX() const` — Get the number of tiles in the X direction.
- L359 _public function_ `int32 GetNumTilesY() const` — Get the number of tiles in the Y direction.
- L364 _public function_ `bool IsTiled() const`
- L376 _public prototype_ `IQueuedWork* GetWork();` — Get the next work item. This method is called by the scheduler. @return The work item, or nullptr if no work is available.
- L387 _public prototype_ `void Initialize(const FString& SequencePath, const FFrameRate& FrameRateOverride, bool Loop, bool bIsSequencerEnvironment);` — Initialize the image sequence loader. @param SequencePath Path to the image sequence. @param FrameRateOverride The frame rate to use (0/0 = do not override). @param Loop Whether the cache should loop around. @param bIsSequencerEnvironment Whether image sequence playback comes from sequencer, to decide on warmup behavior. @see IsInitialized
- L395 _public function_ `bool IsInitialized() const` — Whether this loader has been initialized yet. @return true if initialized, false otherwise. @see Initialize
- L408 _public prototype_ `void NotifyWorkComplete(FImgMediaLoaderWork& CompletedWork, int32 JobID, int32 FrameNumber, const TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe>& Frame, float WorkTime);` — Notify the loader that a work item completed. @param CompletedWork The work item that completed. @param FrameNumber Number of the frame that was read. @param Frame The frame that was read, or nullptr if reading failed. @param WorkTime How long to read this frame (in seconds).
- L419 _public prototype_ `bool RequestFrame(FTimespan Time, float PlayRate, bool Loop);` — Asynchronously request the image frame at the specified time. @param Time The time of the image frame to request (relative to the beginning of the sequence). @param PlayRate The current play rate (used by the look-ahead logic). @param Loop Whether the cache should loop around. @return bool if the frame will be loaded, false otherwise.
- L424 _public prototype_ `void Flush();` — Flush state if queue emulation
- L429 _public prototype_ `void SetIsPlaybackBlocking(bool bIsBlocking);` — Tell the loader if playback is blocking.
- L432 _public prototype_ `void SetIsPaused(bool bInIsPaused);` — Mirror the owning player's paused state into the loader; used by Update / IsCachedFrameInRange.
- L435 _public prototype_ `bool IsFrameFirst(const FTimespan& TimeStamp) const;` — Query if time represents last first frame or before
- L438 _public prototype_ `bool IsFrameLast(const FTimespan& TimeStamp) const;` — Query if time represents last last frame or later
- L443 _public function_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> GetSourceColorSettings() const` — Source color settings getter.
- L462 _protected prototype_ `void FrameNumbersToTimeRanges(const TArray<int32>& FrameNumbers, TRangeSet<FTimespan>& OutRangeSet) const;` — Convert a collection of frame numbers to corresponding time ranges. @param FrameNumbers The frame numbers to convert. @param OutRangeSet Will contain the time ranges.
- L471 _protected prototype_ `FTimespan FrameNumberToTime(uint32 FrameNumber) const;` — Get the play head time corresponding to the specified frame number. @param FrameNumber The frame number. @return The corresponding time. @see TimeToFrameNumber
- L482 _protected prototype_ `bool LoadSequence(const FString& SequencePath, const FFrameRate& FrameRateOverride, bool Loop, FImgMediaFrameInfo& OutFirstFrameInfo);` — Initialize the image sequence loader. @param SequencePath Path to the image sequence. @param FrameRateOverride The frame rate to use (0/0 = do not override). @param Loop Whether the cache should loop around. @param OutFirstFrameInfo Sequence information based on its first frame. @return True when loading succeeds.
- L491 _protected prototype_ `void WarmupSequence(const FImgMediaFrameInfo& InFirstFrameInfo, bool Loop, bool bIsSequencerEnvironment);` — Warms up the player and start issuing requests from the start of the sequence. @param InFirstFrameInfo Sequence information based on its first frame. @param Loop Whether the cache should loop around. @param bIsSequencerEnvironment Whether image sequence playback comes from sequencer.
- L499 _protected prototype_ `void FindFiles(const FString& SequencePath, TArray<FString>& OutputPaths);` — Finds all the files in a directory and gets their path. @param SequencePath Directory to look in. @param OutputPaths File paths will be added to this.
- L521 _protected prototype_ `void FindMips(const FString& SequencePath);` — Finds the mip map files for this sequence (if any). Typically with non mips, a single directory holds all the files of a single sequence. With mip maps, a directory will hold all the files of a single sequence of a specific mip level. The naming convention is for the directory name to end in _<SIZE>. SIZE does not need to be a power of 2. Each subsequent level should have SIZE be half of the level preceeding it. If SIZE does not divide evenly by 2, then round down. The part of the name preceding _<SIZE> should be the same for all mip levels. All mip levels of the same sequence should be in the same location E.g. /Sequence/Seq_256/, /Sequence/Seq_128/, /Sequence/Seq_64/, etc. FindMips will look for mip levels that are the at the level of SequencePath and below. E.g. if SequencePath is Seq_1024, then FindMips will look for Seq_1024, Seq_512, etc and will NOT look for Seq_2048 even if it is present. @param SequencePath Directory of sequence.
- L530 _protected prototype_ `uint32 TimeToFrameNumber(FTimespan Time) const;` — Get the frame number corresponding to the specified play head time. @param Time The play head time. @return The corresponding frame number, or INDEX_NONE. @see FrameNumberToTime
- L539 _protected prototype_ `int64 TimeToFrameNumberUnbound(FTimespan Time) const;` — Get the frame number corresponding to the specified play head time without any checks for media range bounds. @param Time The play head time. @return The corresponding frame number, or INDEX_NONE. @see FrameNumberToTime
- L548 _protected prototype_ `void Update(int32 PlayHeadFrame, float PlayRate, bool Loop);` — Update the loader based on the current play position. @param PlayHeadFrame Current play head frame number. @param PlayRate Current play rate. @param Loop Whether the cache should loop around.
- L556 _protected prototype_ `bool TryAddEmptyFrame(int32 FrameNumber);` — Adds an empty frame to the cache if no frame is present at the specified number. @param FrameNumber Frame number to add. @return True if the frame was added
- L564 _protected prototype_ `void AddFrameToCache(int32 FrameNumber, const TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe>& Frame);` — Adds a frame to the cache. @param FrameNumber Number of frame to add. @param Frame Frame information to add.
- L572 _protected prototype_ `void GetDesiredMipTiles(int32 FrameIndex, TMap<int32, FMediaTileSelection>& OutMipsAndTiles) const;` — Get what mip level and tiles we should be using for a given frame. @param FrameIndex Frame to get mip level for. @param OutMipsAndTiles Will be filled in with what tiles are actually needed.
- L579 _protected prototype_ `int32 GetDesiredMinimumMipLevelToUpscale() const;` — Get what mip level supporting readers should upscale. @return minimum mip level to upscale.
- L585 _protected prototype_ `FTimespan ModuloTime(FTimespan Time) const;` — Modulos the time so that it is between 0 and SequenceDuration. Handles negative numbers appropriately.
- L598 _protected prototype_ `bool GetNumberAtEndOfString(int32& Number, const FString& String, const FString& Extension) const;` — Helper function to get the number at the end of a string. The number does not have to be at the very end, e.g. test1.exr will get 1. @param Number Will be set to the number found if one is found. @param String String to search. @param Extension If the filename has an extension, it will be ignored (in case there is a number in the extension). @return True if it found a number.
- L611 _protected prototype_ `int32 GetSkipFrame(int32 FrameIndex) const;` — Convert FrameIndex to a frame that fits with our skipping logic. E.g. if SkipFramesLevel is 2, then this will return frames 4 frames apart. E.g. FrameIndex	Return value 0			3 1			3 2			3 3			3 4			7 5			7
- L616 _protected prototype_ `void UpdateBandwidthThrottling();` — Updates how we throttle bandwidth depending on current settings.
- L621 _protected prototype_ `const TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe>* GetCachedFrame(int32 InFrameNumber);` — Get frame from either the local or global cache, nullptr if not found.
- L626 _protected prototype_ `void ResetFetchLogic();` — Reset "queued fetch" related state used to emulate player output queue behavior
- L631 _protected prototype_ `bool HasMipsOrTilesEnabled() const;` — Check whether the current sequence has valid mip levels or tiles, and a valid mip map info object.
- L636 _private member_ `mutable FCriticalSection CriticalSection;` — Critical section for synchronizing access to Frames.
- L639 _private member_ `TLruCache<int32, TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe>> Frames;` — The currently loaded image sequence frames.
- L646 _private member_ `TArray<TArray<FString>> ImagePaths;` — Paths to each image for each mip map level in the currently opened sequence. This is an array of mip levels, and each mip level is an array of image paths. Not used for container files.
- L649 _private member_ `bool bIsContainerFile = false;` — Whether the source is a container file rather than a file sequence.
- L652 _private member_ `int32 NumContainerFrames = 0;` — Number of frames in the container (only valid when bIsContainerFile is true).
- L655 _private member_ `FString Info;` — Media information string.
- L658 _private member_ `bool Initialized;` — Whether this loader has been initialized yet.
- L661 _private member_ `const bool bFillGapsInSequence;` — If true, then any gaps in the sequence will be filled with blank frames.
- L664 _private member_ `FMediaTextureTilingDescription TilingDescription;` — Tiling description.
- L667 _private member_ `int32 NumLoadAhead;` — The number of frames to load ahead of the play head.
- L670 _private member_ `int32 NumLoadBehind;` — The number of frames to load behind the play head.
- L673 _private member_ `int32 NumFramesToLoad;` — Total number of frames to load.
- L676 _private member_ `int32 NumMipLevels;` — Stores number of mip levels.
- L679 _private member_ `SIZE_T NumBytesPerPixel;` — Stores number of bytes per pixel for each image.
- L682 _private member_ `TAtomic<int32> MinimumMipLevelToUpscale;` — Minumum mip level to upscale.
- L685 _private member_ `TSharedPtr<IImgMediaReader, ESPMode::ThreadSafe> Reader;` — The image sequence reader to use.
- L688 _private member_ `TSharedPtr<FImgMediaScheduler, ESPMode::ThreadSafe> Scheduler;` — The scheduler for image loading.
- L691 _private member_ `TSharedPtr<FImgMediaGlobalCache, ESPMode::ThreadSafe> GlobalCache;` — The scheduler for image loading.
- L694 _private member_ `TSharedPtr<FImgMediaTileVisibilityResolver, ESPMode::ThreadSafe> TileVisibilityResolver;` — Tile-visibility resolver. Always created; dormant until consumers register providers.
- L697 _private member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> SourceColorSettings;` — Container for media source color settings.
- L700 _private member_ `FString LayerName;` — Name of the EXR layer to read.
- L703 _private member_ `FIntPoint SequenceDim;` — Width and height of the image sequence (in pixels) .
- L706 _private member_ `FTimespan SequenceDuration;` — Total length of the image sequence.
- L709 _private member_ `FFrameRate SequenceFrameRate;` — Frame rate of the currently loaded sequence.
- L712 _private member_ `FName SequenceName;` — Identifying name of sequence files.
- L715 _private prototype_ `bool RequestFrame(int32 FrameNumber, float PlayRate, bool Loop);`
- L718 _private prototype_ `void HandleGlobalCacheFrameEviction();` — When using a global cache, handles the case when the last requested frame might have been evicted.
- L721 _private member_ `int32 LastRequestedFrame;` — Index of the previously requested frame.
- L724 _private member_ `bool LastRequestedLoop = false;` — Loop flag stashed from the last RequestFrame so TickFrame's paused-replay Update sees the right wrap-around state.
- L727 _private member_ `IMediaEventSink* EventSink = nullptr;` — Player-supplied sink for Internal_RequestVideoSampleRefresh events. Outlives the loader; null disables.
- L730 _private member_ `FGuid PlayerGuid;` — Player identifier (mirrors FImgMediaPlayer::PlayerGuid); included in log lines for cross-layer correlation.
- L733 _private member_ `std::atomic<bool> bIsPaused{false};` — Mirror of the owning player's paused state; pushed via SetIsPaused. Atomic because NotifyWorkComplete reads it from worker threads.
- L736 _private member_ `int32 RetryCount;` — Counter used to retry loading frames again.
- L739 _private member_ `TArray<int32> PendingFrameNumbers;` — Collection of frame numbers that need to be read.
- L742 _private member_ `TArray<FFrameNumberJobInfo> QueuedFrameNumbers;` — Collection of frame numbers that are being read.
- L743 _private member_ `int32 NextFrameNumberJobID;`
- L746 _private member_ `TArray<FImgMediaLoaderWork*> WorkPool;` — Object pool for reusable work items.
- L749 _private member_ `bool UseGlobalCache;` — True if we are using the global cache, false to use the local cache.
- L758 _private member_ `FQueuedSampleFetch QueuedSampleFetch;`
- L763 _private member_ `FImgMediaLoaderSmartCacheSettings SmartCacheSettings;` — Settings for the smart cache.
- L765 _private member_ `bool bIsPlaybackBlocking;` — True if the player is using blocked playback.
- L768 _private member_ `bool bIsBandwidthThrottlingEnabled;` — If we want to throttle bandwidth when there is not enough bandwidth.
- L770 _private member_ `bool bIsSkipFramesEnabled;` — If we can skip frames to throttle bandwidth.
- L772 _private member_ `int32 SkipFramesCounter;` — Keeps a count so we can raise/lower the skip level when this gets too high/low.
- L780 _private member_ `int32 SkipFramesLevel;` — The current level of skipping. The frame increment to the next frame is 1 << SkipFramesLevel. So level 0 -> next frame is +1, i.e. the next frame, i.e. no skipping. level 1 -> next frame is +2, i.e. we skip 1 frame. level 2 -> next frame is +4, i.e. we skip 3 frames.
- L782 _private member_ `const int32 SkipFramesCounterRaiseLevelThreshold = 10;` — When SkipFramesCounter is greater than this, then increase SkipFramesLevel.
- L784 _private member_ `const int32 SkipFramesCounterNewLevelValue = 5;` — When SkipFramesLevel changes, the value of SkipFramesCounter will reset to this.
- L788 _private member_ `FImgMediaLoaderBandwidth Bandwidth;` — Bandwidth estimation.

#### struct `FImgMediaLoader::FFrameNumberJobInfo`  
`struct FFrameNumberJobInfo`  
_L446-454_
- L448 _public prototype_ `FFrameNumberJobInfo() = default;`
- L449 _public function_ `FFrameNumberJobInfo(int32 InFrame, int32 InJobID) : Frame(InFrame), JobID(InJobID)`
- L451 _public member_ `int32 Frame;`
- L452 _public member_ `int32 JobID;`
- L453 _public function_ `bool operator==(const FFrameNumberJobInfo& Other) const`

#### struct `FImgMediaLoader::FQueuedSampleFetch`  
`struct FQueuedSampleFetch`  
_L752-757_
- desc: State related to "queue style" frame access functions
- L754 _public member_ `FMediaTimeStamp LastTimeStamp;` — Current playhead / last delivered sample PTS
- L755 _public member_ `FTimespan LastDuration;` — Duration of a frame / zero after seek or playback start
- L756 _public member_ `int32 LoopIndex;` — Current loop index to be encoded into sequence index of timestamp

### `Plugins/Media/ImgMedia/Source/ImgMedia/Internal/Player/ImgMediaPlayer.h` (Internal)


#### class `FImgMediaPlayer`  
`class FImgMediaPlayer final : public IMediaPlayer , protected IMediaCache , protected IMediaControls , protected IMediaSamples , protected IMediaTracks , public IMediaView`  
_L29-214_
- inherits: `IMediaPlayer,IMediaCache,IMediaControls,IMediaSamples,IMediaTracks,IMediaView`
- desc: Implements a media player for image sequences.
- L46 _public prototype_ `FImgMediaPlayer(IMediaEventSink& InEventSink, const TSharedRef<FImgMediaScheduler, ESPMode::ThreadSafe>& InScheduler, const TSharedRef<FImgMediaGlobalCache, ESPMode::ThreadSafe>& InGlobalCache);` — Create and initialize a new instance. @param InEventSink The object that receives media events from this player. @param InScheduler The image loading scheduler to use. @param InGlobalCache Optional global cache to use for this player.
- L53 _public function_ `TSharedPtr<FImgMediaLoader, ESPMode::ThreadSafe> GetLoader()` — Get the loader.
- L56 _public prototype_ `virtual void Close() override;`
- L57 _public prototype_ `virtual IMediaCache& GetCache() override;`
- L58 _public prototype_ `virtual IMediaControls& GetControls() override;`
- L59 _public prototype_ `virtual FString GetInfo() const override;`
- L60 _public prototype_ `virtual FVariant GetMediaInfo(FName InfoName) const override;`
- L61 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L62 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L63 _public prototype_ `virtual FString GetStats() const override;`
- L64 _public prototype_ `virtual IMediaTracks& GetTracks() override;`
- L65 _public prototype_ `virtual FString GetUrl() const override;`
- L66 _public prototype_ `virtual IMediaView& GetView() override;`
- L67 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L68 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options, const FMediaPlayerOptions* PlayerOptions) override;`
- L69 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) override;`
- L70 _public function_ `virtual void SetGuid(const FGuid& Guid) override`
- L71 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L72 _public prototype_ `virtual bool FlushOnSeekStarted() const override;`
- L73 _public prototype_ `virtual bool FlushOnSeekCompleted() const override;`
- L74 _public prototype_ `virtual bool GetPlayerFeatureFlag(EFeatureFlag flag) const override;`
- L77 _public prototype_ `virtual void RecordSourceOpenedEvent() const override;`
- L78 _public function_ `virtual bool ShouldAutoRecordSourceOpenedEvent() const override`
- L83 _public function_ `const FGuid& GetPlayerGuid() const` — Facade-supplied identifier; same value lives on FMediaPlayerFacade::PlayerGuid for cross-layer log correlation.
- L91 _protected prototype_ `bool IsInitialized() const;` — Check whether this player is initialized. @return true if initialized, false otherwise.
- L95 _public prototype_ `virtual bool QueryCacheState(EMediaCacheState State, TRangeSet<FTimespan>& OutTimeRanges) const override;`
- L99 _public prototype_ `virtual bool CanControl(EMediaControl Control) const override;`
- L100 _public prototype_ `virtual FTimespan GetDuration() const override;`
- L101 _public prototype_ `virtual float GetRate() const override;`
- L102 _public prototype_ `virtual EMediaState GetState() const override;`
- L103 _public prototype_ `virtual EMediaStatus GetStatus() const override;`
- L104 _public prototype_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const override;`
- L105 _public prototype_ `virtual FTimespan GetTime() const override;`
- L106 _public prototype_ `virtual bool IsLooping() const override;`
- L107 _public function_ `virtual bool Seek(const FTimespan& Time) override`
- L109 _public prototype_ `virtual bool Seek(const FTimespan& InNewTime, const FMediaSeekParams& InAdditionalParams) override;`
- L110 _public prototype_ `virtual bool SetLooping(bool Looping) override;`
- L111 _public prototype_ `virtual bool SetRate(float Rate) override;`
- L112 _public prototype_ `virtual void SetBlockingPlaybackHint(bool bFacadeWillUseBlockingPlayback) override;`
- L116 _public prototype_ `virtual bool FetchVideo(TRange<FTimespan> TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample) override;`
- L117 _public prototype_ `virtual void FlushSamples() override;`
- L118 _public prototype_ `virtual void SetMinExpectedNextSequenceIndex(TOptional<int32> InNextSequenceIndex) override;`
- L119 _public prototype_ `virtual EFetchBestSampleResult FetchBestVideoSampleForTimeRange(const TRange<FMediaTimeStamp>& TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample, bool bReverse, bool bConsistentResult) override;`
- L120 _public prototype_ `virtual bool PeekVideoSampleTime(FMediaTimeStamp & TimeStamp) override;`
- L121 _public prototype_ `virtual bool DiscardVideoSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse) override;`
- L125 _public prototype_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const override;`
- L126 _public prototype_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const override;`
- L127 _public prototype_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L128 _public prototype_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override;`
- L129 _public prototype_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L130 _public prototype_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L131 _public prototype_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L132 _public prototype_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L133 _public prototype_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L134 _public prototype_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override;`
- L135 _public prototype_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) override;`
- L140 _private prototype_ `void AddMediaTextureTrackerEventHandlers();` — Subscribe to FMediaTextureTracker's register/unregister delegates so providers added after Open() are picked up. Idempotent.
- L143 _private prototype_ `void RemoveMediaTextureTrackerEventHandlers();` — Drop the tracker delegate handles. Called from Close() and the destructor. Idempotent.
- L146 _private prototype_ `void RebuildTileVisibilityProviders();` — Re-register providers from the tracker objects bound to MediaTextureWeakPtr. Idempotent.
- L149 _private member_ `FTimespan CurrentDuration;` — The duration of the currently loaded media.
- L152 _private member_ `float CurrentRate;` — The current playback rate.
- L155 _private member_ `float LastNonZeroRate;` — The last playback rate not zero (zero if never played).
- L158 _private member_ `EMediaState CurrentState;` — The player's current state.
- L161 _private member_ `FTimespan CurrentTime;` — The current time of the playback.
- L164 _private member_ `int32 CurrentSeekIndex;` — Current seek index portion of sequence index
- L167 _private member_ `FString CurrentUrl;` — The URL of the currently opened media.
- L170 _private member_ `FGuid PlayerGuid;` — Stable per-facade identifier pushed down by FMediaPlayerFacade::SetGuid; used in logs to correlate across the facade and loader/reader layers.
- L173 _private member_ `bool DeltaTimeHackApplied;` — Whether an offset to delta time has been applied yet.
- L176 _private member_ `IMediaEventSink& EventSink;` — The media event handler.
- L179 _private member_ `FTimespan LastFetchTime;` — Sample time of the last fetched video sample.
- L182 _private member_ `TSharedPtr<FImgMediaLoader, ESPMode::ThreadSafe> Loader;` — The image sequence loader.
- L185 _private member_ `bool PlaybackRestarted;` — If playback just restarted from the Stopped state.
- L188 _private member_ `TSharedPtr<FImgMediaScheduler, ESPMode::ThreadSafe> Scheduler;` — The scheduler for image loading.
- L191 _private member_ `int32 SelectedVideoTrack;` — Index of the selected video track.
- L194 _private member_ `bool ShouldLoop;` — Should the video loop to the beginning at completion
- L197 _private member_ `TSharedPtr<FImgMediaGlobalCache, ESPMode::ThreadSafe> GlobalCache;` — The global cache to use.
- L200 _private member_ `bool RequestFrameHasRun;` — True if we have run RequestFrame already for this frame.
- L203 _private member_ `bool PlaybackIsBlocking;` — True if facade has signaled it uses blocking playback, false if not
- L206 _private member_ `TWeakObjectPtr<UMediaTexture> MediaTextureWeakPtr;` — Weak pointer to the active media texture.
- L209 _private member_ `TArray<TSharedPtr<IMediaTileVisibilityProvider, ESPMode::ThreadSafe>> OwnedTileVisibilityProviders;` — Strong refs to provider instances built by RebuildTileVisibilityProviders; the resolver holds them weakly.
- L212 _private member_ `FDelegateHandle TrackerObjectRegisteredHandle;` — FMediaTextureTracker delegate handles - subscribed in Open, removed in Close.
- L213 _private member_ `FDelegateHandle TrackerObjectUnregisteredHandle;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API IMGMEDIA_API`

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Assets/Providers/ImgMediaPlaneVisibilityProvider.h` (Private)


#### struct `FImgMediaPlaneVisibilityProviderParams`  
`struct FImgMediaPlaneVisibilityProviderParams : public FImgMediaVisibilityProviderParams`  
_L10-12_
- inherits: `FImgMediaVisibilityProviderParams`
- desc: Construction parameters for the plane visibility provider; no plane-specific fields today.

#### class `FImgMediaPlaneVisibilityProvider`  
`class FImgMediaPlaneVisibilityProvider final : public FMediaTileVisibilityProvider`  
_L19-39_
- inherits: `FMediaTileVisibilityProvider`
- desc: Visibility provider for media displayed on a flat (plane) mesh. Performs a quadtree-style frustum walk over the sequence's tile pyramid and emits tile selections per visible mip level.
- L22 _public prototype_ `explicit FImgMediaPlaneVisibilityProvider(const FImgMediaPlaneVisibilityProviderParams& InParams);`
- L25 _public prototype_ `virtual void GatherVisibleTiles(const FMediaSequenceInfo& InSequenceInfo, FMediaTileVisibilityRequest& OutRequest) const override;`
- L27 _public prototype_ `virtual bool IsAlive() const override;`
- L31 _private member_ `FImgMediaPlaneVisibilityProviderParams Params;`
- L38 _private member_ `FVector PlaneSize;` — Local-space mesh bounds captured at construction. Frozen by design - if the consumer's mesh is replaced or rebuilt at runtime, register a fresh provider rather than mutating this.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Assets/Providers/ImgMediaProviderUtils.h` (Private)


#### struct `FImgMediaVisibilityProviderParams`  
`struct FImgMediaVisibilityProviderParams`  
_L22-39_
- desc: Construction parameters common to every ImgMedia visibility provider implementation. Per-provider param structs (FImgMediaPlaneVisibilityProviderParams etc.) inherit from this and add only what they need on top.
- L25 _public member_ `TWeakObjectPtr<UMeshComponent> MeshComponent;` — Mesh component the media is rendered on. World-space bounds drive tile mip selection.
- L28 _public member_ `TWeakPtr<FImgMediaSceneViewExtension, ESPMode::ThreadSafe> SceneViewExtension;` — Source of cached camera view infos.
- L31 _public member_ `float MipMapLODBias = 0.f;` — LOD bias added to calculated mip level (negative biases toward higher quality).
- L34 _public member_ `int32 MipLevelToUpscale = -1;` — Mip level to upscale into lower quality mips, or -1 to disable.
- L37 _public member_ `EMediaTextureTargetViewResolution TargetViewResolutionMask = EMediaTextureTargetViewResolution::RenderResolution;` — Bitwise mask for which set of cached view infos to consume.

#### Free symbols / members of external scopes

- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace ImgMediaProviders` (scope `UE`)
- L51 _function_ `inline float GetMipLevelPadding()` (scope `UE::ImgMediaProviders`) — Padding added to the calculated mip-level range. CVar: ImgMedia.MipMapLevelPadding.
- L60 _function_ `inline bool GetDebugDrawEnabled()` (scope `UE::ImgMediaProviders`) — Whether to draw per-tile debug spheres in the editor. CVar: ImgMedia.EnableMipMapTileDebugDraw.
- L84 _function_ `FORCEINLINE int32 ComputeQuadtreeMaxMipLevel(int32 InNumMipLevels, const FIntPoint& InTileNum, bool bInIsTiled)` (scope `UE::ImgMediaProviders`) — Cap for quadtree-style tile traversals: the highest mip level at which the per-axis tile count is still >= 1. NumMipLevels counts texture downsamples; the quadtree halves tile counts per axis. Once 2^Mip exceeds min(NumTiles), GetPartialTileNum() drops below 1 and per-tile placement walks off the plate. Non-tiled sequences are not capped (their GetPartialTileNum is fixed at (1,1) so tile placement never degenerates). @param InNumMipLevels  Number of mip levels in the asset (>= 1 for normal sequences; 0 is tolerated and yields a cap of 0). @param InTileNum       Mip-0 tile count per axis (FMediaTextureTilingDescription::TileNum). Zero/negative components are treated as 1 to avoid FloorLog2(0). @param bInIsTiled      Pass FMediaSequenceInfo::IsTiled(). When false the cap is just NumMipLevels - 1 since there's no tile pyramid to degenerate. @return The highest mip level the quadtree may safely traverse, in [0, NumMipLevels-1].
- L119 _function_ `FORCEINLINE void EmitVisibilityAboveQuadtreeCap( const FIntPoint& InMipZeroResolution, const FIntPoint& InTileSize, int32 InMaxLevel, const FIntVector2& InMipLevelRange, FMediaTileVisibilityRequest& OutRequest)` (scope `UE::ImgMediaProviders`) — Emit "all-tiles-visible" entries for every mip in [InMipLevelRange[0], InMipLevelRange[1]] that lives above the quadtree cap (InMaxLevel). The quadtree only walks down to InMaxLevel; mips above it have no quadtree node to mark them visible, so a far-camera view would leave those mips out of the request entirely and the renderer would render black where it expects a coarse mip. Idempotent under repeated calls: each call overwrites the entry with a freshly computed all-visible selection, equivalent to bit-OR since dimensions are pinned by InMipZeroResolution / InTileSize. @param InMipZeroResolution  Pixel dimensions of the sequence at mip 0 (FMediaSequenceInfo::Dim). Used to compute per-mip tile counts via FMediaTileSelection::CreateForTargetMipLevel. @param InTileSize           Tile dimensions in pixels (FMediaTextureTilingDescription::TileSize). @param InMaxLevel           Quadtree cap (typically from ComputeQuadtreeMaxMipLevel). Mips at or below this level are the quadtree's responsibility and are left untouched. @param InMipLevelRange      Calculated mip-level range [floor, ceil] for the tile being processed. Must satisfy [0] <= [1]. When [1] <= InMaxLevel the call is a no-op. @param OutRequest           [in,out] Visibility request to extend in-place. Any existing entry at the same mip is replaced by the all-visible selection.
- L139 _function_ `inline bool IsPrimitiveComponentHidden(FPrimitiveComponentId ComponentId, const FImgMediaViewInfo& ViewInfo)` (scope `UE::ImgMediaProviders`) — Inverts the show-only / hidden semantics of FImgMediaViewInfo into a single hidden test.
- L146 _function_ `FORCEINLINE bool ProjectWorldToScreenFast(const FVector& WorldPosition, const FIntRect& ViewRect, const FMatrix& ViewProjectionMatrix, FVector2D& out_ScreenPos)` (scope `UE::ImgMediaProviders`) — Minimalized version of FSceneView::ProjectWorldToScreen - returns false when behind the camera.
- L166 _function_ `inline bool CalculateMipLevelAniso(const FImgMediaViewInfo& ViewInfo, const FVector& TexelWS, const FVector& TexelOffXWS, const FVector& TexelOffYWS, float& OutMipLevel)` (scope `UE::ImgMediaProviders`) — Approximates hardware mip-level selection with default anisotropic filtering. TexelWS is the world-space position of the texel being shaded; TexelOff{X,Y}WS are positions one source-texel away along each axis. Returns false if any of the three points is behind the camera.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Assets/Providers/ImgMediaSphereVisibilityProvider.h` (Private)


#### struct `FImgMediaSphereVisibilityProviderParams`  
`struct FImgMediaSphereVisibilityProviderParams : public FImgMediaVisibilityProviderParams`  
_L12-19_
- inherits: `FImgMediaVisibilityProviderParams`
- desc: Construction parameters for the sphere visibility provider; adds sphere-only fields on top of the base.
- L15 _public member_ `bool bAdaptivePoleMipUpscaling = false;` — Whether to dynamically raise the upscale level near sphere poles to reduce load.
- L18 _public member_ `FVector2D MeshRange = FVector2D(360.0, 180.0);` — Spherical mesh range (X = horizontal degrees, Y = vertical degrees).

#### class `FImgMediaSphereVisibilityProvider`  
`class FImgMediaSphereVisibilityProvider final : public FMediaTileVisibilityProvider`  
_L27-42_
- inherits: `FMediaTileVisibilityProvider`
- desc: Visibility provider for media displayed on a latlong sphere. Performs an analytical UV walk over the sphere's tile grid and emits tile selections per visible mip level. Optionally raises the upscale mip level near the poles when bAdaptivePoleMipUpscaling is set.
- L30 _public prototype_ `explicit FImgMediaSphereVisibilityProvider(const FImgMediaSphereVisibilityProviderParams& InParams);`
- L33 _public prototype_ `virtual void GatherVisibleTiles(const FMediaSequenceInfo& InSequenceInfo, FMediaTileVisibilityRequest& OutRequest) const override;`
- L35 _public prototype_ `virtual bool IsAlive() const override;`
- L39 _private member_ `static constexpr float DefaultSphereRadius = 50.0f;` — matches FMediaPlateCustomizationMesh::GenerateSphereMesh
- L41 _private member_ `FImgMediaSphereVisibilityProviderParams Params;`

#### Free symbols / members of external scopes

- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace ImgMediaSphereVisibility` (scope `UE`)
- L45 _namespace_ `namespace Tests` (scope `UE::ImgMediaSphereVisibility`)
- L48 _prototype_ `FVector TransformSphericalUVsToLocationWS(const FVector2f& InMeshRange, const FTransform& InMeshTransform, FVector2f InUV, float InSphereRadius);` (scope `UE::ImgMediaSphereVisibility::Tests`) — Maps a UV in [0,1]^2 (mesh space) to its world-space position on a partial-range latlong sphere.
- L56 _prototype_ `FVector2f TransformDirectionWSToSphericalUVs(const FVector2f& InMeshRange, const FTransform& InMeshTransform, const FVector& InDirection);` (scope `UE::ImgMediaSphereVisibility::Tests`) — Inverse of TransformSphericalUVsToLocationWS. Result UV may fall outside [0,1] when the direction lies outside a partial mesh's coverage - that is the correct semantic for "camera looking past the partial sphere".

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/IImgMediaModulePrivate.h` (Private)


#### class `IImgMediaModulePrivate`  
`class IImgMediaModulePrivate : public IImgMediaModule`  
_L10-30_
- inherits: `IImgMediaModule`
- desc: Extended Private Interface for the ImgMedia module.
- L17 _public function_ `static inline IImgMediaModulePrivate* Get()` — Returns a pointer to the module instance if loaded, null otherwise.
- L26 _public function_ `static IImgMediaModulePrivate& GetOrLoad()` — Returns existing instance of the module, loads it if it was not already loaded. Beware of calling this during the shutdown phase, though. The module might have been unloaded already.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/ImgMediaPrivate.h` (Private)


#### Free symbols / members of external scopes

- L14 _macro_ `#define IMGMEDIA_EXR_SUPPORTED_PLATFORM (PLATFORM_MAC || PLATFORM_WINDOWS || (PLATFORM_LINUX && PLATFORM_CPU_X86_FAMILY))` — The OpenEXR image reader is supported on macOS, Windows, and Linux only.
- L17 _macro_ `#define USE_IMGMEDIA_DEALLOC_POOL UE_BUILD_DEBUG` — Whether to use a separate thread pool for image frame deallocations.
- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogImgMedia, Log, All);` — Log category for this module.
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogImgMedia, Log, All);` — Log category for this module.
- L24 _delegate_ `DECLARE_STATS_GROUP(TEXT("ImgMediaPlugin"), STATGROUP_ImgMediaPlugin, STAT` — Stat category for this module.
- L29 _prototype_ `extern FQueuedThreadPool* GetImgMediaThreadPoolSlow();` — Thread pool used for deleting image frame buffers.
- L32 _namespace_ `namespace ImgMedia`
- L35 _variable_ `static const FFrameRate DefaultFrameRate(24, 1);` (scope `ImgMedia`) — Default frame rate for image sequences (24 fps).
- L38 _variable_ `static const FName FillGapsInSequenceOption("Fil` (scope `ImgMedia`) — Name of the FillGapsInSequence media option.
- L41 _variable_ `static const FName FrameRateOverrideDenonimatorOption("Fra` (scope `ImgMedia`) — Name of the FramesRateOverrideDenonimator media option.
- L44 _variable_ `static const FName FrameRateOverrideNumeratorOption("Fra` (scope `ImgMedia`) — Name of the FramesRateOverrideNumerator media option.
- L47 _variable_ `static const FName ProxyOverrideOption("Pro` (scope `ImgMedia`) — Name of the ProxyOverride media option.
- L50 _variable_ `static const FName LayerNameOption("Lay` (scope `ImgMedia`) — Name of the LayerName media option.
- L53 _variable_ `static const FName NumTilesXOption("Img` (scope `ImgMedia`) — Name of the NumTilesX media option.
- L56 _variable_ `static const FName NumTilesYOption("Img` (scope `ImgMedia`) — Name of the NumTilesY media option.
- L59 _variable_ `static const FName SourceColorSettingsOption("Sou` (scope `ImgMedia`) — Name of the SourceColorSettings media option.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Loader/ImgMediaLoaderUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ImgMediaLoaderUtils` (scope `UE`)
- L20 _function_ `inline uint32 TimeToFrameNumber(const FTimespan& InTime, const FFrameRate& InFrameRate)` (scope `UE::ImgMediaLoaderUtils`) — Converts the given time to a frame number at the given framerate. @param InTime Time (timespan in ticks) @param InFrameRate Frame rate in frames per second @return Frame number
- L31 _function_ `inline int64 TimeToFrameNumberUnbound(const FTimespan& InTime, const FFrameRate& InFrameRate)` (scope `UE::ImgMediaLoaderUtils`) — Converts the given time to a frame number at the given framerate. @param InTime Time (timespan in ticks) @param InFrameRate Frame rate in frames per second @return Frame number (can be very large)
- L43 _function_ `inline FTimespan GetFrameStartTime(uint32 InFrameNumber, const FFrameRate& InFrameRate)` (scope `UE::ImgMediaLoaderUtils`) — Returns the lower bound, start time, of the given frame number for the given frame rate. @param InFrameNumber Frame number @param InFrameRate Frame rate in frames per second @return A timespan in tick, where the tick number is the first tick that will return back the same frame number from TimeToFrameNumber.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Loader/ImgMediaLoaderWork.h` (Private)


#### class `FImgMediaLoaderWork`  
`class FImgMediaLoaderWork : public IQueuedWork`  
_L18-81_
- inherits: `IQueuedWork`
- desc: Loads a single image frame from disk.
- L29 _public prototype_ `FImgMediaLoaderWork(const TSharedRef<FImgMediaLoader, ESPMode::ThreadSafe>& InOwner, const TSharedRef<IImgMediaReader, ESPMode::ThreadSafe>& InReader);` — Create and initialize a new instance. @param InOwner The loader that created this work item. @param InReader The image reader to use.
- L43 _public prototype_ `void Initialize(int32 InJobID, int32 InFrameNumber, TMap<int32, FMediaTileSelection> InMipTiles, TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe> InExistingFrame);` — Initialize this work item. @param InJobID An ID to identify the job while in flight @param InFrameNumber The number of the image frame. @param InMipLevel Will read in this level and all higher levels. @param InTileSelection Which tiles to read. @param InExistingFrame If set, then use this frame to load into. @see Shutdown
- L49 _public prototype_ `virtual void Abandon() override;`
- L50 _public prototype_ `virtual void DoThreadedWork() override;`
- L60 _protected prototype_ `void Finalize(TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe> Frame, float WorkTime);` — Notify the owner of this work item, or self destruct. @param Frame The frame that was loaded by this work item. @param WorkTime How long to read this frame (in seconds).
- L65 _private member_ `int32 JobID;` — ID to identify this workload instance when in flight
- L68 _private member_ `int32 FrameNumber;` — The number of the image frame.
- L71 _private member_ `TMap<int32, FMediaTileSelection> MipTiles;` — Which tiles we should load per mip level.
- L74 _private member_ `TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe> ExistingFrame;` — If set, then load the image into this frame instead of making a new one.
- L77 _private member_ `TWeakPtr<FImgMediaLoader, ESPMode::ThreadSafe> OwnerPtr;` — The loader that created this reader task.
- L80 _private member_ `TSharedPtr<IImgMediaReader, ESPMode::ThreadSafe> Reader;` — The image sequence reader to use.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Player/ImgMediaTextureSample.h` (Private)


#### class `FImgMediaTextureSample`  
`class FImgMediaTextureSample : public IMediaTextureSample`  
_L18-212_
- inherits: `IMediaTextureSample`
- desc: Texture sample generated by image sequence players.
- L24 _public function_ `FImgMediaTextureSample() : Duration(FTimespan::Zero()) , OutputDim(FIntPoint::ZeroValue) , Time(FTimespan::Zero()) , NumMipMaps(1) , TilingDesc() , SourceColorSettings()` — Default constructor.
- L46 _public function_ `void Initialize( FImgMediaFrame& InFrame, const FIntPoint& InOutputDim, FMediaTimeStamp InTime, FTimespan InDuration, uint8 InNumMipMaps, FMediaTextureTilingDescription InTilingDesc, TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> InSourceColorSettings)` — Initialize the sample. @param InFrame The image frame to create the sample for. @param InOutputDim The sample's output width and height (in pixels). @param InTime The sample time (in the player's local clock). @param InDuration The duration for which the sample is valid. @param InNumMipMaps The sample's number of mip levels. @param InTilingDesc The sample's tiling description. @param InSourceColorSettings The sample's source color space & encoding overrides.
- L75 _public function_ `virtual const void* GetBuffer() override`
- L80 _public function_ `virtual FIntPoint GetDim() const override`
- L85 _public function_ `virtual uint8 GetNumMips() const override`
- L90 _public function_ `virtual FMediaTextureTilingDescription GetTilingDescription() const override`
- L95 _public function_ `virtual FTimespan GetDuration() const override`
- L100 _public function_ `virtual EMediaTextureSampleFormat GetFormat() const override`
- L105 _public function_ `virtual FIntPoint GetOutputDim() const override`
- L110 _public function_ `virtual uint32 GetStride() const override`
- L116 _public function_ `virtual FRHITexture* GetTexture() const override`
- L122 _public function_ `virtual IMediaTextureSampleConverter* GetMediaTextureSampleConverter() override`
- L127 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L132 _public function_ `virtual bool IsCacheable() const override`
- L137 _public function_ `virtual bool IsOutputSrgb() const override`
- L152 _public function_ `virtual const UE::Color::FColorSpace& GetSourceColorSpace() const override`
- L165 _public function_ `virtual UE::Color::EEncoding GetEncodingType() const override`
- L180 _public function_ `virtual UE::Color::EChromaticAdaptationMethod GetChromaticAdapationMethod() const override`
- L193 _private member_ `FTimespan Duration;` — Duration for which the sample is valid.
- L196 _private member_ `FImgMediaFrame Frame;` — The image frame that this sample represents.
- L199 _private member_ `FIntPoint OutputDim;` — Width and height of the output.
- L202 _private member_ `FMediaTimeStamp Time;` — Play time for which the sample was generated.
- L205 _private member_ `uint8 NumMipMaps;` — Number of mip levels in this sample.
- L208 _private member_ `FMediaTextureTilingDescription TilingDesc;` — Description of the number and size of tiles in this sample.
- L211 _private member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> SourceColorSettings;` — Manual source color space & encoding overrides.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Readers/DdsImgMediaReader.h` (Private)


#### class `FDdsImgMediaReader`  
`class FDdsImgMediaReader final : public IImgMediaReader`  
_L13-40_
- inherits: `IImgMediaReader`
- desc: Implements a reader for various image sequence formats.
- L23 _public prototype_ `FDdsImgMediaReader(const TSharedRef<FImgMediaLoader, ESPMode::ThreadSafe>& InLoader);` — Create and initialize a new instance. @param InImageWrapperModule The image wrapper module to use.
- L25 _public prototype_ `~FDdsImgMediaReader();`
- L31 _public prototype_ `virtual bool GetFrameInfo(const FString& ImagePath, FImgMediaFrameInfo& OutInfo) override;`
- L32 _public prototype_ `virtual bool ReadFrame(int32 FrameId, const TMap<int32, FMediaTileSelection>& InMipTiles, TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe> OutFrame) override;`
- L33 _public function_ `virtual void CancelFrame(int32 FrameNumber) override`
- L34 _public function_ `virtual void UncancelFrame(int32 FrameNumber) override`
- L39 _private member_ `TWeakPtr<FImgMediaLoader, ESPMode::ThreadSafe> LoaderPtr;` — Our parent loader.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Readers/ExrImgMediaReader.h` (Private)


#### class `FExrImgMediaReader`  
`class FExrImgMediaReader : public IImgMediaReader`  
_L22-117_
- inherits: `IImgMediaReader`
- desc: Implements a reader for EXR image sequences.
- L28 _public prototype_ `FExrImgMediaReader(const TSharedRef<FImgMediaLoader, ESPMode::ThreadSafe>& InLoader, const FString& InLayerName = FString());` — Constructor.
- L29 _public prototype_ `virtual ~FExrImgMediaReader();`
- L34 _public prototype_ `virtual bool GetFrameInfo(const FString& ImagePath, FImgMediaFrameInfo& OutInfo) override;`
- L35 _public prototype_ `virtual bool ReadFrame(int32 FrameId, const TMap<int32, FMediaTileSelection>& InMipTiles, TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe> OutFrame) override;`
- L36 _public prototype_ `virtual void CancelFrame(int32 FrameNumber) override;`
- L37 _public prototype_ `virtual void UncancelFrame(int32 FrameNumber) override;`
- L41 _public prototype_ `static TSharedPtr<IImgMediaReader, ESPMode::ThreadSafe> GetReader(const TSharedRef<FImgMediaLoader, ESPMode::ThreadSafe>& InLoader, FString FirstImageInSequencePath, const FString& InLayerName = FString());` — Gets reader type (GPU vs CPU) depending on size of EXR and its compression.
- L60 _protected prototype_ `static bool GetInfo(const FString& FilePath, FImgMediaFrameInfo& OutInfo, const TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe>& OutFrame = nullptr);` — Get the frame information from the given input file. @param FilePath The location of the exr file. @param OutInfo Will contain the frame information. @param OutFrame Optional frame to update. @return true on success, false otherwise.
- L74 _protected prototype_ `EReadResult ReadTiles ( uint16* Buffer , int64 BufferSize , const FString& ImagePath , const TArray<FIntRect>& TileRegions , FSampleConverterParameters& ConverterParams , const int32 CurrentMipLevel , TArray<UE::Math::TIntPoint<int64>>& OutBufferRegionsToCopy);` — Reads tiles from exr files in tile rows based on Tile region. If frame is pending for cancelation stops reading tiles at the current tile row. @param Buffer					A buffer to read into from hard drive. @param BufferSize				The total size of the buffer. Used to limit reader to buffer region. @param ImagePath					Path to the file to read. @param FrameId					Frame id used to determine if frame has been canceled. @param TileRegions				Rectangular tile regions that we read from the hard drive line by line. @param ConverterParams			Full information about the current frame. @param OutBufferRegionsToCopy	This buffer is used to issue copy commands on GPU Copy thread.
- L89 _protected prototype_ `SIZE_T GetMipBufferTotalSize(FIntPoint Dim, bool bInHasMips);` — Gets the total size needed for all mips. @param Dim Dimensions of the largest mip. @return Total size of all mip levels.
- L98 _protected prototype_ `bool ResolveLayer(const FString& ImagePath);` — Resolves the configured LayerName to concrete RGBA channel names. Reads the channel list from the given file and populates ResolvedChannel[R/G/B/A]. @param ImagePath Path to an EXR file to read channel names from. @return true if resolution succeeded.
- L101 _protected member_ `TSet<int32> CanceledFrames;`
- L102 _protected member_ `FCriticalSection CanceledFramesCriticalSection;`
- L103 _protected member_ `TMap<int32, FRgbaInputFile*> PendingFrames;`
- L104 _protected member_ `TWeakPtr<FImgMediaLoader, ESPMode::ThreadSafe> LoaderPtr;`
- L107 _protected member_ `FString LayerName;` — Configured layer name (may contain wildcards).
- L109 _protected member_ `FString ResolvedChannelR;` — Resolved channel names for each RGBA output slot.
- L110 _protected member_ `FString ResolvedChannelG;`
- L111 _protected member_ `FString ResolvedChannelB;`
- L112 _protected member_ `FString ResolvedChannelA;`
- L114 _protected member_ `FCriticalSection LayerResolveCriticalSection;` — Guards layer resolution state (separate from CanceledFramesCriticalSection).
- L116 _protected member_ `std::atomic_bool bLayerResolved{false};` — True after layer has been resolved to concrete channel names.

#### enum `FExrImgMediaReader::EReadResult`  
`enum EReadResult`  
_L44-50_
- L46 _public enumerator_ `Fail`
- L47 _public enumerator_ `Success`
- L48 _public enumerator_ `Cancelled`
- L49 _public enumerator_ `Skipped`

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Readers/ExrImgMediaReaderGpu.h` (Private)


#### struct `FStructuredBufferPoolItem`  
`struct FStructuredBufferPoolItem`  
_L17-48_
- L23 _public member_ `FBufferRHIRef UploadBufferRef;` — This is the actual buffer reference that we need to keep after it is locked and until it is unlocked. The buffer is used as an upload heap and will not be accessed by shader if CVarExrReaderUseUploadHeap is set.
- L28 _public member_ `void* UploadBufferMapped;` — A pointer to mapped GPU memory.
- L33 _public member_ `FBufferRHIRef ShaderAccessBufferRef;` — This buffer is used by the swizzling shader if CVarExrReaderUseUploadHeap is set and UploadBufferRef contents are copied into it.
- L38 _public member_ `FShaderResourceViewRHIRef ShaderResourceView;` — Resource View used by swizzling shader.
- L41 _public member_ `FEvent* AllocationReadyEvent;` — Event used to wait for completed buffer allocations.
- L44 _public prototype_ `FStructuredBufferPoolItem();` — Constructor
- L47 _public prototype_ `~FStructuredBufferPoolItem();` — Destructor to clean up render resources

#### class `FExrImgMediaReaderGpu`  
`class FExrImgMediaReaderGpu : public FExrImgMediaReader , public TSharedFromThis<FExrImgMediaReaderGpu, ESPMode::ThreadSafe>`  
_L58-137_
- inherits: `FExrImgMediaReader,TSharedFromThis<FExrImgMediaReaderGpu,ESPMode::ThreadSafe>`
- desc: Implements a reader for EXR image sequences.
- L65 _public prototype_ `FExrImgMediaReaderGpu(const TSharedRef<FImgMediaLoader, ESPMode::ThreadSafe>& InLoader, const FString& InLayerName = FString());` — Constructor.
- L66 _public prototype_ `virtual ~FExrImgMediaReaderGpu();`
- L71 _public prototype_ `virtual bool GetFrameInfo(const FString& ImagePath, FImgMediaFrameInfo& OutInfo) override;`
- L72 _public prototype_ `virtual bool ReadFrame(int32 FrameId, const TMap<int32, FMediaTileSelection>& InMipTiles, TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe> OutFrame) override;`
- L77 _public prototype_ `virtual void PreAllocateMemoryPool(int32 NumFrames, const FImgMediaFrameInfo& FrameInfo) override;` — For performance reasons we want to pre-allocate structured buffers to at least the number of concurrent frames.
- L85 _protected prototype_ `EReadResult ReadInChunks(uint16* Buffer, const FString& ImagePath, int32 FrameId, const FIntPoint& Dim, int32 BufferSize);` — This function reads file in 16 MB chunks and if it detects that Frame is pending for cancellation stops reading the file and returns false.
- L93 _protected prototype_ `static SIZE_T GetBufferSize(const FIntPoint& Dim, int32 NumChannels, bool bHasTiles, const FIntPoint& TileNum);` — Get the size of the buffer needed to load in an image. @param Dim Dimensions of the image. @param NumChannels Number of channels in the image.
- L98 _protected prototype_ `static void CreateSampleConverterCallback(TSharedPtr<FExrMediaTextureSampleConverter, ESPMode::ThreadSafe> SampleConverter);` — Creates Sample converter to be used by Media Texture Resource.
- L103 _protected prototype_ `EReadResult ReadMip ( const int32 CurrentMipLevel , const FMediaTileSelection& CurrentTileSelection , TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe> OutFrame , FSampleConverterParameters& ConverterParams , TSharedPtr<FExrMediaTextureSampleConverter, ESPMode::ThreadSafe> SampleConverter , const FString& ImagePath);` — A function that reads one mip level.
- L114 _public prototype_ `virtual FStructuredBufferPoolItemSharedPtr AllocateGpuBufferFromPool(uint32 AllocSize);` — Typically we would need the (ImageResolution.x*y)*NumChannels*ChannelSize
- L117 _public prototype_ `void ReturnGpuBufferToPool(uint32 AllocSize, FStructuredBufferPoolItem* Buffer);` — Either return or Add new chunk of memory to the pool based on its size.
- L124 _private member_ `FCriticalSection MemoryPoolCriticalSection;` — A critical section used for memory allocation and pool management.
- L127 _private member_ `TMultiMap<uint32, FStructuredBufferPoolItem*> MemoryPool;` — Memory pool from where we are allowed to take buffers.
- L130 _private member_ `uint64 LastTickedFrameCounter;` — Frame that was last ticked so we don't tick more than once.
- L133 _private member_ `bool bIsShuttingDown;` — A flag indicating this reader is being destroyed, therefore memory should not be returned.
- L136 _private member_ `std::atomic_bool bFallBackToCPU;` — If true, then just use the CPU to read the file. Written once with memory_order_release, read lock-free with memory_order_acquire.

#### struct `FSampleConverterParameters`  
`struct FSampleConverterParameters`  
_L143-181_
- desc: These are all the required parameters to convert Buffer to Texture converter.
- L146 _public member_ `FImgMediaFrameInfo FrameInfo;` — General file information including its header.
- L149 _public member_ `int32 FrameId;` — Frame Id.
- L152 _public member_ `FIntPoint FullResolution;` — Resolution of the highest quality mip.
- L155 _public member_ `FIntPoint TileDimWithBorders;` — Dimension of the tile including the overscan borders.
- L158 _public member_ `TSortedMap<int32, TArray<FIntRect>> Viewports;` — Used for rendering tiles in bulk regions per mip level.
- L164 _public member_ `TArray<TArray<FExrReader::FTileDesc>> TileInfoPerMipLevel;` — Contain information about individual tiles. Used to convert buffer data into a 2D Texture. The size of this array is the exact number of complete and partial tiles for each mip level.
- L168 _public member_ `int32 NumMipLevels;` — Number of mip levels read.
- L171 _public member_ `int32 PixelSize;` — Pixel stride in bytes. I.e. 2 bytes per pixel x 3 channels = 6.
- L174 _public member_ `bool bMipsInSeparateFiles;` — Indicates if mips stored in individual files.
- L177 _public member_ `int32 UpscaleMip = -1;` — A lower quality mip will be upscaled if value is 0 or above. At 0 highest quality mip will always be read fully.
- L180 _public member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> SourceColorSettings;` — Manual source color space & encoding overrides.

#### class `FExrMediaTextureSampleConverter`  
`class FExrMediaTextureSampleConverter: public IMediaTextureSampleConverter`  
_L186-260_
- inherits: `IMediaTextureSampleConverter`
- L190 _public prototype_ `virtual bool Convert(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, const FConversionHints& Hints) override;`
- L191 _public prototype_ `virtual ~FExrMediaTextureSampleConverter() = default;`
- L193 _public function_ `void AddCallback(FExrConvertBufferCallback&& Callback)`
- L203 _public function_ `bool HasMipLevelBuffer(int32 RequestedMipLevel) const`
- L209 _public function_ `FStructuredBufferPoolItemSharedPtr GetOrCreateMipLevelBuffer(int32 RequestedMipLevel, TFunction<FStructuredBufferPoolItemSharedPtr()> AllocatorFunc)`
- L232 _public function_ `FSampleConverterParameters GetParams()`
- L238 _public function_ `void SetParams(const FSampleConverterParameters& InParams)`
- L246 _private member_ `mutable FCriticalSection ParamsCriticalSection;` — These are all required parameters to convert the buffer into texture successfully.
- L247 _private member_ `FSampleConverterParameters ConverterParams;`
- L249 _private member_ `FCriticalSection ConverterCallbacksCriticalSection;`
- L250 _private member_ `FExrConvertBufferCallback ConvertExrBufferCallback;`
- L253 _private member_ `mutable FCriticalSection MipBufferCriticalSection;` — Lock to be used exclusively on reader threads.
- L256 _private member_ `TMap<int32,FStructuredBufferPoolItemSharedPtr> MipBuffers;` — An array of structured buffers that are big enough to fully contain corresponding mip levels used by reader threads and transferred into MipBuffersRenderThread.
- L259 _private member_ `TMap<int32, FStructuredBufferPoolItemSharedPtr> MipBuffersRenderThread;` — An array of structured buffers that are big enough to fully contain corresponding mip levels. Used exclusively on the Render thread.

#### Free symbols / members of external scopes

- L53 _typedef_ `typedef TSharedPtr<FStructuredBufferPoolItem, ESPMode::ThreadSafe> FStructuredBufferPoolItemSharedPtr;` — A shared pointer that will be released automatically and returned to UsedPool
- L184 _typedef_ `using FExrConvertBufferCallback = TDelegate<bool(FRHICommandListImmediate& RHICmdList, FTextureRHIRef RenderTargetTextureRHI, TMap<int32, FStructuredBufferPoolItemSharedPtr>& MipBuffers, const FSampleConverterParameters ConverterParams)>;`

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Readers/GenericImgMediaReader.h` (Private)


#### class `FGenericImgMediaReader`  
`class FGenericImgMediaReader : public IImgMediaReader`  
_L21-52_
- inherits: `IImgMediaReader`
- desc: Implements a reader for various image sequence formats.
- L29 _public prototype_ `FGenericImgMediaReader(const TSharedRef<FImgMediaLoader, ESPMode::ThreadSafe>& InLoader);` — Create and initialize a new instance.
- L32 _public prototype_ `virtual ~FGenericImgMediaReader() = default;` — Virtual destructor.
- L38 _public prototype_ `virtual bool GetFrameInfo(const FString& ImagePath, FImgMediaFrameInfo& OutInfo) override;`
- L39 _public prototype_ `virtual bool ReadFrame(int32 FrameId, const TMap<int32, FMediaTileSelection>& InMipTiles, TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe> OutFrame) override;`
- L40 _public function_ `virtual void CancelFrame(int32 FrameNumber) override`
- L41 _public function_ `virtual void UncancelFrame(int32 FrameNumber) override`
- L45 _private prototype_ `bool IsSupportedFormat(const ERawImageFormat::Type InFormat) const;` — Checks if the format is supported.
- L48 _private prototype_ `bool GetFrameInfoFromImage(const FString& ImagePath, const FImageInfo& Image, FImgMediaFrameInfo& OutInfo);` — Extract metadata from the loaded image.
- L51 _private member_ `TWeakPtr<FImgMediaLoader, ESPMode::ThreadSafe> LoaderPtr;` — Our parent loader.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ERawImageFormat`

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Readers/IImgMediaReader.h` (Private)


#### struct `FImgMediaFrameInfo`  
`struct FImgMediaFrameInfo`  
_L20-67_
- desc: Information about an image sequence frame.
- L23 _public member_ `FString CompressionName;` — Name of the image compression algorithm (i.e. "ZIP").
- L26 _public member_ `FIntPoint Dim;` — Width and height of the frame (in pixels).
- L29 _public member_ `FString FormatName;` — Name of the image format (i.e. "EXR").
- L39 _public member_ `FFrameRate FrameRate;` — Note that the frame rate here is not necessarily correct if the sequence uses a frame rate override. The override value is not always accessible from where this member gets set, and it might also not be all that useful since it is conceivable that the images end up in the image cache and are either referenced by different media sources with different frame rate overrides, or the frame rate override is changed after the images have been added to the cache.
- L42 _public member_ `bool Srgb = false;` — Whether the frame is in sRGB color space.
- L45 _public member_ `SIZE_T UncompressedSize = 0;` — Uncompressed size (in bytes). All mip levels included.
- L48 _public member_ `SIZE_T NumChannels = 0;` — Number of channels (RGB - 3 or RGBA - 4).
- L51 _public member_ `SIZE_T NumBytesPerPixel = 0;` — Number of bytes per pixel.
- L54 _public member_ `bool bHasTiles = false;` — Does this frame have tiles?.
- L57 _public member_ `FIntPoint NumTiles;` — Number of tiles in X and Y direction.
- L60 _public member_ `FIntPoint TileDimensions;` — Tile dimensions.
- L63 _public member_ `int32 TileBorder = 0;` — Tile border size in texels. This is required for more elaborate tile texel sampling.
- L66 _public member_ `int32 NumMipLevels = 0;` — Number of Mip Levels.

#### struct `FImgMediaMipTiles`  
`struct FImgMediaMipTiles final`  
_L73-285_
- desc: A thread-safe container for tile selections per mip level.
- L76 _public prototype_ `FImgMediaMipTiles() = default;` — Default constructor.
- L78 _public prototype_ `~FImgMediaMipTiles() = default;` — Default destructor.
- L81 _public function_ `FImgMediaMipTiles(FImgMediaMipTiles&& Other)` — Move constructor.
- L87 _public function_ `FImgMediaMipTiles(const FImgMediaMipTiles& Other)` — Copy constructor.
- L93 _public function_ `FImgMediaMipTiles& operator=(FImgMediaMipTiles&& Other)` — Move assignment operator.
- L100 _public function_ `FImgMediaMipTiles& operator=(const FImgMediaMipTiles& Other)` — Copy assignment operator.
- L112 _public function_ `bool Contains(const int32 InMipLevel) const` — Contains the specified mip level. @param InMipLevel mip level @return true when mip level is present.
- L123 _public function_ `bool IsEmpty() const` — Check if the container is empty. @return true when no mips/tiles are present.
- L130 _public function_ `void Reset()` — Reset the container.
- L142 _public function_ `bool ContainsMipTiles(const TMap<int32, FMediaTileSelection>& InRequestedMipTiles)` — Check if the existing tiles contain all of the requested ones. (Is the container a superset of requested?) @param InRequestedMipTiles Requested tile selection per mip level. @return true if the selection is entirely contained, or the request was empty.
- L162 _public function_ `bool ContainsTiles(const int32 InMipLevel, const FMediaTileSelection& InSelection)` — Check if the existing tiles contain all of the requested ones, at the specified mip level. @param InMipLevel Specified mip level. @param InSelection Requested tile selection. @return true if the selection is contained
- L182 _public function_ `void Include(const int32 InMipLevel, const FMediaTileSelection& InSelection)` — Include the selection at the specified mip level. @param InMipLevel Specified mip level. @param InSelection New tile selection.
- L202 _public function_ `void Emplace(const int32 InMipLevel, const FMediaTileSelection& InSelection)` — Emplace the selection at the specified mip level. @param InMipLevel Specified mip level. @param InSelection New tile selection.
- L216 _public function_ `bool GetSelection(const int32 InMipLevel, FMediaTileSelection& OutSelection) const` — Get a copy of the selection at the specified mip level. @param InMipLevel Specified mip level. @param OutSelection Returned tile selection. @return true if mip level was found
- L238 _public function_ `bool GetVisibleRegions(const int32 InMipLevel, const FMediaTileSelection& InSelection, TArray<FIntRect>& OutRegions) const` — Returns a calculated list of contiguous visible tile regions. Only provides regions for the missing tiles if CurrentTileSelection is specified. @param InMipLevel Specified mip level. @param InSelection Existing tile selection. @param OutRegions Visible tile regions array. @return true if mip level was found
- L252 _public function_ `TMap<int32, FMediaTileSelection>& GetDataUnsafe()` — Thread-unsafe data getter: the caller is responsible for locking.
- L258 _public function_ `const TMap<int32, FMediaTileSelection>& GetDataUnsafe() const` — Thread-unsafe data getter: the caller is responsible for locking.
- L266 _public member_ `mutable FCriticalSection CriticalSection;` — Critical section to lock when using unsafe methods.
- L269 _private function_ `void InternalMove(FImgMediaMipTiles&& Other)`
- L276 _private function_ `void InternalCopy(const FImgMediaMipTiles& Other)`
- L284 _private member_ `TMap<int32, FMediaTileSelection> MipTiles;` — Tiles present per mip level.

#### struct `FImgMediaFrame`  
`struct FImgMediaFrame final`  
_L290-420_
- desc: A single frame of an image sequence.
- L293 _public prototype_ `FImgMediaFrame() = default;` — Default constructor.
- L296 _public prototype_ `~FImgMediaFrame() = default;` — Default destructor.
- L299 _public function_ `FImgMediaFrame(const FImgMediaFrame& Other) : Data(Other.Data) , Format(Other.Format.load()) , MipTilesPresent(Other.MipTilesPresent) , NumTilesRead(Other.NumTilesRead.load()) , Stride(Other.Stride.load()) , Info()` — Copy constructor.
- L320 _public function_ `FImgMediaFrame& operator=(const FImgMediaFrame& Other)` — Copy assignment operator.
- L330 _public prototype_ `FImgMediaFrame(FImgMediaFrame&& Other) = delete;`
- L331 _public prototype_ `FImgMediaFrame& operator=(FImgMediaFrame&& Other) = delete;`
- L334 _public member_ `TSharedPtr<void, ESPMode::ThreadSafe> Data;` — The frame's data.
- L337 _public member_ `std::atomic<EMediaTextureSampleFormat> Format;` — The frame's sample format.
- L340 _public member_ `FImgMediaMipTiles MipTilesPresent;` — Tiles present per mip level.
- L343 _public member_ `std::atomic<int32> NumTilesRead = 0;` — Total number of tiles read.
- L346 _public member_ `std::atomic<uint32> Stride = 0;` — The frame's horizontal stride (in bytes).
- L349 _public function_ `IMediaTextureSampleConverter* GetSampleConverter()` — This should only be used if you do not need to make changes to sample converter.
- L355 _public function_ `template <class T> TSharedPtr<T, ESPMode::ThreadSafe> GetOrCreateSampleConverter()`
- L366 _public function_ `FImgMediaFrameInfo GetInfo() const` — Thread-safe info getter.
- L373 _public function_ `void SetInfo(FImgMediaFrameInfo InInfo)` — Thread-safe info setter.
- L380 _public function_ `FFrameRate GetFrameRate() const` — Thread-safe framerate getter.
- L387 _public function_ `FIntPoint GetDim() const` — Thread-safe dimensions getter.
- L394 _public function_ `bool IsOutputSrgb() const` — Thread-safe sRGB getter.
- L401 _public function_ `SIZE_T GetUncompressedSize() const` — Thread-safe uncompressed size.
- L410 _private member_ `mutable FCriticalSection InfoCriticalSection;` — Information critical section.
- L413 _private member_ `FImgMediaFrameInfo Info;` — Additional information about the frame.
- L416 _private member_ `mutable FCriticalSection SampleConverterCriticalSection;` — Lock to be used exclusively on reader threads. Note: this protects only the creation of the sample converter.
- L419 _private member_ `TSharedPtr<IMediaTextureSampleConverter, ESPMode::ThreadSafe> SampleConverter;` — Sample converter is used by Media Texture Resource to convert the texture or data.

#### class `IImgMediaReader`  
`class IImgMediaReader`  
_L426-497_
- desc: Interface for image sequence readers.
- L438 _public prototype_ `virtual bool GetFrameInfo(const FString& ImagePath, FImgMediaFrameInfo& OutInfo) = 0;` — Get information about an image sequence frame. @param ImagePath Path to the image file containing the frame. @param OutInfo Will contain the frame info. @return true on success, false otherwise. @see ReadFrame
- L450 _public prototype_ `virtual bool ReadFrame(int32 FrameId, const TMap<int32, FMediaTileSelection>& InMipTiles, TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe> OutFrame) = 0;` — Read a single image frame. @param FrameId Frame number to read. @param MipLevel Will read in this level and all higher levels. @param InTileSelection Which tiles to read. @param OutFrame Will contain the frame. @return true on success, false otherwise. @see GetFrameInfo
- L457 _public prototype_ `virtual void CancelFrame(int32 FrameNumber) = 0;` — Mark Frame to be canceled based on Frame number. Typically this will be @param FrameNumber used for frame lookup.
- L463 _public prototype_ `virtual void UncancelFrame(int32 FrameNumber) = 0;` — Makes sure a frame that was passed to CancelFrame is no longer marked to be cancelled. @param FrameNumber Frame that was passed to CancelFrame.
- L470 _public function_ `virtual void PreAllocateMemoryPool(int32 NumFrames, const FImgMediaFrameInfo& FrameInfo)` — For some readers this function allows to pre-allocate enough memory to support the maximum number of frames with as much efficiency as possible.
- L477 _public function_ `virtual void OnTick()` — Used in case reader needs to do some processing once per frame. Example: ExrImgMediaReaderGpu which returns unused memory to memory pool.
- L481 _public function_ `virtual FVariant GetMediaInfo(FName InfoName) const` — Query media metadata by name. Returns an empty variant if not available.
- L491 _public prototype_ `virtual TSharedPtr<FImgMediaTextureSample, ESPMode::ThreadSafe> CreateSample();` — Factory hook: produce the texture sample that the loader will hand to the media pipeline for this reader. Default returns a plain FImgMediaTextureSample. Reader subclasses can override to return a derived sample type that opts into per-reader behavior - e.g. TMV returns a sample that exposes the sparse-residency create-flags hint for its intermediate render target.
- L496 _public prototype_ `virtual ~IImgMediaReader() = default;` — Virtual destructor.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Readers/TmvImgMediaReader.h` (Private)


#### class `FTmvImgMediaReader`  
`class FTmvImgMediaReader : public IImgMediaReader`  
_L28-99_
- inherits: `IImgMediaReader`
- desc: Abstract base class for TMV image media readers. Provides the common decode pipeline (parse, decode, compose). Subclasses provide the access unit for each frame.
- L31 _public prototype_ `FTmvImgMediaReader(const TSharedRef<FImgMediaLoader>& InLoader, const TSharedRef<ITmvMediaDecoderFactory>& InDecoderFactory);`
- L35 _public prototype_ `static TArray<FString> GetSupportedImageFileExtensions();` — Get the list of supported image file extensions for TMV decoders.
- L38 _public prototype_ `static TArray<FString> GetSupportedContainerFileExtensions();` — Get the list of supported container file extensions for TMV demuxers.
- L43 _public prototype_ `static bool IsImageFileExtensionSupported(const FString& InExtension);` — Returns true if the given image file extension is supported by a Tmv Reader.
- L48 _public prototype_ `static bool IsContainerFileExtensionSupported(const FString& InExtension);` — Returns true if the given container file extension is supported by a Tmv Reader.
- L55 _public prototype_ `static TSharedPtr<FTmvImgMediaReader> CreateReader(const TSharedRef<FImgMediaLoader>& InLoader, const FString& InMediaFilePath);` — Creates a reader of the appropriate type depending on the context (input file, settings, etc). @param InLoader Parent Img Loader @param InMediaFilePath Full path of the media file, either the first image of the sequence or the container.
- L60 _public function_ `virtual const FTmvMediaDemuxerTrackInfo* GetVideoTrackInfo() const` — Returns the video track info if present, nullptr otherwise.
- L67 _public prototype_ `virtual bool GetFrameInfo(const FString& InImagePath, FImgMediaFrameInfo& OutInfo) override;`
- L68 _public prototype_ `virtual bool ReadFrame(int32 InFrameId, const TMap<int32, FMediaTileSelection>& InMipTiles, TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe> OutFrame) override;`
- L69 _public function_ `virtual void CancelFrame(int32 InFrameNumber) override`
- L70 _public function_ `virtual void UncancelFrame(int32 InFrameNumber) override`
- L71 _public prototype_ `virtual TSharedPtr<FImgMediaTextureSample, ESPMode::ThreadSafe> CreateSample() override;`
- L80 _protected prototype_ `virtual TUniquePtr<ITmvMediaDecoderAccessUnit> CreateAccessUnit(int32 InFrameId) = 0;` — Create an access unit for the given frame. @param InFrameId Frame index. @return A valid access unit, or null on failure.
- L83 _protected member_ `TWeakPtr<FImgMediaLoader> LoaderWeak;` — Parent loader.
- L86 _protected member_ `TSharedRef<ITmvMediaDecoderFactory> DecoderFactory;` — Decoder factory to create decoders on demand.
- L89 _protected member_ `TSharedPtr<UE::ImgMedia::FTmvParserPool> ParserPool;` — Parser Pool for this image reader. We need a parser per worker thread.
- L92 _protected member_ `TSharedPtr<UE::ImgMedia::FTmvDecoderPool> DecoderPool;` — Decoder Pool for this image reader. We need a decoder per worker thread.
- L95 _protected member_ `TSharedPtr<FTmvMediaFrameMipBufferPool> FrameMipBufferPool;` — Texture Sample Buffer Pool for this image reader.
- L98 _protected member_ `FTmvOverflowHysteresis OverflowHysteresis;` — Residency-overflow upscale-fallback hysteresis (see FTmvOverflowHysteresis).

#### class `FTmvFileSequenceImgMediaReader`  
`class FTmvFileSequenceImgMediaReader final : public FTmvImgMediaReader`  
_L104-113_
- inherits: `FTmvImgMediaReader`
- desc: TMV reader for file sequences: one file per frame.
- L107 _public prototype_ `FTmvFileSequenceImgMediaReader(const TSharedRef<FImgMediaLoader>& InLoader, const TSharedRef<ITmvMediaDecoderFactory>& InDecoderFactory);`
- L111 _protected prototype_ `virtual TUniquePtr<ITmvMediaDecoderAccessUnit> CreateAccessUnit(int32 InFrameId) override;`

#### class `FTmvContainerImgMediaReader`  
`class FTmvContainerImgMediaReader final : public FTmvImgMediaReader`  
_L119-162_
- inherits: `FTmvImgMediaReader`
- desc: TMV reader for container files: reads frames from a .tmv container via ITmvMediaDemuxer. Uses ReadSampleInfo (metadata only) + direct file reads (no intermediate memory buffer).
- L122 _public prototype_ `FTmvContainerImgMediaReader( const TSharedRef<FImgMediaLoader>& InLoader, const TSharedRef<ITmvMediaDecoderFactory>& InDecoderFactory, const TSharedPtr<ITmvMediaDemuxer, ESPMode::ThreadSafe>& InDemuxer, int32 InTrackIndex, const FString& InContainerFilePath);`
- L132 _public function_ `virtual const FTmvMediaDemuxerTrackInfo* GetVideoTrackInfo() const override`
- L139 _public prototype_ `virtual FVariant GetMediaInfo(FName InfoName) const override;`
- L144 _protected prototype_ `virtual TUniquePtr<ITmvMediaDecoderAccessUnit> CreateAccessUnit(int32 InFrameId) override;`
- L149 _private member_ `TSharedPtr<ITmvMediaDemuxer, ESPMode::ThreadSafe> Demuxer;` — Demuxer for reading sample info from the container.
- L152 _private member_ `FCriticalSection DemuxerCS;` — Serializes SeekToSample + ReadSampleInfo on the demuxer.
- L155 _private member_ `int32 DemuxerTrackIndex = 0;` — Video track index in the demuxer.
- L158 _private member_ `FTmvMediaDemuxerTrackInfo VideoTrackInfo;` — Cached video track info from the demuxer.
- L161 _private member_ `FString ContainerFilePath;` — Path to the container file (for creating per-thread file access units).

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ImgMedia` (scope `UE`)

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Readers/TmvImgMediaTextureSample.h` (Private)


#### class `FTmvImgMediaTextureSample`  
`class FTmvImgMediaTextureSample : public FImgMediaTextureSample`  
_L28-70_
- inherits: `FImgMediaTextureSample`
- desc: TMV-specific image media texture sample. Identical to FImgMediaTextureSample for all data-plane behavior. The only difference is that this sample opts the intermediate render target into a D3D12 reserved-resource allocation when sparse output residency is enabled and the texture is large enough to benefit. The actual per-mip commit / decommit is driven by FTmvSparseOutputManager from the converter; this sample just signals "create the texture in a way that the manager can manage" via the engine's CreateIntermediateRenderTarget hint hook. Eligibility is decided here (per sample) rather than globally so that: - HD-sized plates skip the sparse path entirely (no virtual allocation, no tracking overhead) when their largest mip is below the byte threshold. - The decision is bit-identical across the lifetime of the sample (it's a function of dimensions + format, not runtime state).
- L31 _public prototype_ `FTmvImgMediaTextureSample() = default;`
- L34 _public function_ `virtual ETextureCreateFlags GetIntermediateTargetCreateFlagsHint() const override`

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Readers/TmvOverflowHysteresis.h` (Private)


#### class `FTmvOverflowHysteresis`  
`class FTmvOverflowHysteresis`  
_L26-52_
- desc: Owns the residency-overflow upscale-fallback hysteresis that used to live as a bare atomic on FTmvImgMediaReader. When mip virtualization / the shared tile pool can't fit every visible tile in a frame, the swizzle shader discards the unmapped tiles. To avoid showing a hole, the reader forces the coarsest mip as a full-screen upscale source. That extra draw is expensive (~10 ms/frame across 9 plates), so it is gated to a short window after the last overflow rather than left always-on. Thread-safety: RecordFrame runs from ReadFrame on multiple worker threads concurrently (different access units, same reader). The counter is atomic; the increment/reset ordering races are tolerable because the fallback decision only needs approximately-fresh state - a one-frame drift either direction is invisible.
- L33 _public prototype_ `void RecordFrame(int32 InTotalOverflowed);` — Fold this frame's total overflow count into the clean-frame counter: reset to zero on any overflow, saturating-increment otherwise.
- L41 _public prototype_ `bool ShouldForceUpscaleFallback() const;` — True when the coarsest-mip upscale fallback should be forced this frame: virtualization is on and either grow-on-demand is off (overflows are persistent) or we are inside the post-overflow hysteresis window in shared-pool mode. Reads the virtualization CVars itself.
- L45 _private member_ `static constexpr int32 FallbackHysteresisFrames = 10;` — Frames the fallback stays on after the last overflow.
- L48 _private member_ `static constexpr int32 CleanFrameSaturation = 1024;` — Saturation cap; anything past the threshold means the same thing ("fallback off").
- L51 _private member_ `std::atomic<int32> ConsecutiveCleanFrames{TNumericLimits<int32>::Max()};` — Consecutive frames with no AllocateSlot==INDEX_NONE in any mip request.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Scheduler/IImgMediaScheduler.h` (Private)


#### class `IImgMediaScheduler`  
`class IImgMediaScheduler`  
_L9-27_
- L21 _public prototype_ `virtual IQueuedWork* GetWorkOrReturnToPool(FImgMediaSchedulerThread* Thread) = 0;` — Get the next available work item from the scheduler. If no work is available, the calling thread will be returned to the thread pool. @param Thread The thread that is requesting the work. @return Work item, or nullptr if no work available.
- L26 _public prototype_ `virtual ~IImgMediaScheduler() = default;` — Virtual destructor.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Scheduler/ImgMediaScheduler.h` (Private)


#### class `FImgMediaScheduler`  
`class FImgMediaScheduler : public IMediaClockSink , protected IImgMediaScheduler`  
_L18-112_
- inherits: `IMediaClockSink,IImgMediaScheduler`
- L25 _public prototype_ `FImgMediaScheduler();` — Default constructor.
- L28 _public prototype_ `virtual ~FImgMediaScheduler();` — Virtual destructor.
- L37 _public prototype_ `void Initialize();` — Initialize the scheduler. @see Shutdown
- L45 _public prototype_ `void RegisterLoader(const TSharedRef<FImgMediaLoader, ESPMode::ThreadSafe>& Loader);` — Register an image sequencer loader. @param Loader The loader to register. @see UnregisterLoader
- L52 _public prototype_ `void Shutdown();` — Shut down the scheduler. @see Initialize
- L60 _public prototype_ `void UnregisterLoader(const TSharedRef<FImgMediaLoader, ESPMode::ThreadSafe>& Loader);` — Unregister an image sequence loader. @param Loader The loader to unregister. @see RegisterLoader
- L66 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L75 _protected prototype_ `void RemoveLoader(int32 LoaderIndex);` — Remove the loader with the specified index. @param LoaderIndex Index of the loader to remove.
- L81 _protected prototype_ `virtual IQueuedWork* GetWorkOrReturnToPool(FImgMediaSchedulerThread* Thread) override;`
- L86 _private member_ `TArray<FImgMediaSchedulerThread*> AllThreads;` — Collection of all worker threads.
- L89 _private member_ `TArray<FImgMediaSchedulerThread*> AvailableThreads;` — Threads that are available to perform work.
- L92 _private member_ `FCriticalSection CriticalSection;` — Critical section for locking access to loader collection.
- L95 _private member_ `TArray<TWeakPtr<FImgMediaLoader, ESPMode::ThreadSafe>> Loaders;` — Collection of registered image sequence loaders.
- L98 _private member_ `int32 LoaderRoundRobin;` — Index of the last loader that provided a work item.
- L100 _private prototype_ `uint32 GetWorkerStackSize();`
- L101 _private prototype_ `void CreateWorker(uint32 StackSize);`
- L105 _private member_ `FDelegateHandle UpdateSettingsHandle;`
- L109 _private prototype_ `void UpdateSettings(const UImgMediaSettings* Settings);` — Updates our settings from ImgMediaAsettings.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Private/Scheduler/ImgMediaSchedulerThread.h` (Private)


#### class `FImgMediaSchedulerThread`  
`class FImgMediaSchedulerThread : public FRunnable , private FSingleThreadRunnable`  
_L17-73_
- inherits: `FRunnable,FSingleThreadRunnable`
- L28 _public prototype_ `FImgMediaSchedulerThread(IImgMediaScheduler& InOwner, uint32 StackSize, EThreadPriority ThreadPriority);` — Create and initialize a new instance. @param InOwner The scheduler that owns this thread.
- L31 _public prototype_ `virtual ~FImgMediaSchedulerThread();` — Virtual destructor.
- L42 _public prototype_ `void QueueWork(IQueuedWork* Work);` — Queue the specified work item. This method is called by the scheduler on threads that currently do not perform any work. @param Work The work item to queue.
- L48 _public prototype_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override;`
- L49 _public prototype_ `virtual uint32 Run() override;`
- L55 _protected prototype_ `virtual void Tick() override;`
- L60 _private member_ `IImgMediaScheduler& Owner;` — The scheduler that owns this thread.
- L63 _private member_ `IQueuedWork* QueuedWork;` — Queued work item to be processed by this thread.
- L66 _private member_ `TAtomic<bool> Stopping;` — Whether this thread is stopping.
- L69 _private member_ `FRunnableThread* Thread;` — The thread object.
- L72 _private member_ `FEvent* WorkEvent;` — Event signaling that work is available.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Public/IImgMediaModule.h` (Public)


#### class `IImgMediaModule`  
`class IImgMediaModule : public IModuleInterface`  
_L28-88_
- inherits: `IModuleInterface`
- desc: Interface for the ImgMedia module.
- L39 _public function_ `static inline IImgMediaModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L56 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventHandler) = 0;` — Creates a media player for image sequences. @param EventHandler The object that will receive the player's events. @return A new media player, or nullptr if a player couldn't be created.
- L59 _public prototype_ `virtual const TSharedPtr<FImgMediaSceneViewExtension, ESPMode::ThreadSafe>& GetSceneViewExtension() const = 0;` — Get scene view extension caching view information (for mip/tile calculations).
- L63 _public prototype_ `virtual ~IImgMediaModule() = default;` — Virtual destructor.
- L66 _public member_ `FOnImgMediaPlayerCreated OnImgMediaPlayerCreated;` — Add to this callback to get called whenever a player is created.
- L73 _public function_ `static FImgMediaGlobalCache* GetGlobalCache()` — Call this to get the global cache. @return Global cache.
- L76 _public member_ `static FLazyName CustomFormatAttributeName;` — Name of attribute in the Exr file that marks it as our custom format.
- L78 _public member_ `static FLazyName CustomFormatTileWidthAttributeName;` — Name of attribute in the Exr file for the tile width for our custom format.
- L80 _public member_ `static FLazyName CustomFormatTileHeightAttributeName;` — Name of attribute in the Exr file for the tile height for our custom format.
- L82 _public member_ `static FLazyName CustomFormatTileBorderAttributeName;` — Name of attribute in the Exr file for the tile border size for our custom format.
- L87 _protected member_ `static TSharedPtr<FImgMediaGlobalCache, ESPMode::ThreadSafe> GlobalCache;` — Holds the global cache.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IMGMEDIA_API`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnImgMediaPlayerCreated, const TSharedPtr<FImgMediaPlayer>&);` — Callback when a player gets created.
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnImgMediaPlayerCreated, const TSharedPtr<FImgMediaPlayer>&);` — Callback when a player gets created.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Public/ImgMediaGlobalCache.h` (Public)


#### class `FImgMediaGlobalCache`  
`class FImgMediaGlobalCache : public TSharedFromThis<FImgMediaGlobalCache, ESPMode::ThreadSafe>`  
_L21-217_
- inherits: `TSharedFromThis<FImgMediaGlobalCache,ESPMode::ThreadSafe>`
- desc: A global cache for all ImgMedia players. Uses Least Recently Used (LRU).
- L27 _public prototype_ `FImgMediaGlobalCache();` — Constructor.
- L32 _public prototype_ `~FImgMediaGlobalCache();` — Desctructor.
- L37 _public prototype_ `void Initialize();` — Initialize the cache.
- L42 _public prototype_ `void Shutdown();` — Shut down the cache.
- L53 _public prototype_ `void AddFrame(const FString& FileName, const FName& Sequence, int32 Index, const TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe>& Frame, bool bAdjustSizeForMipMaps = false);` — Adds a frame to the cache. @param	FileName		Filename of frame to add. @param	Sequence		Indentifying name of this sequence. @param	Index			Index of frame to add. @param	Frame			Actual frame to add. @param	bAdjustSizeForMipMaps	Whether this frame needs size adjustments for mip maps in separate folders.
- L61 _public prototype_ `bool Contains(const FName& Sequence, int32 Index);` — Check whether the entry with the specified sequence and index is present. @param	Sequence		Indentifying name of this sequence. @param	Index			Index of frame to touch.
- L69 _public prototype_ `TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe>* FindAndTouch(const FName& Sequence, int32 Index);` — Find the entry with the specified sequence and index and mark it as the most recently used. @param	Sequence		Indentifying name of this sequence. @param	Index			Index of frame to touch.
- L77 _public prototype_ `void GetIndices(const FName& Sequence, TArray<int32>& OutIndices) const;` — Find the indices of all cached entries of a particular sequence. @param	Sequence		Indentifying name of this sequence. @param OutIndices Will contain the collection of indices.
- L82 _public prototype_ `void EmptyCache();` — Empties the cache.
- L87 _public function_ `SIZE_T GetCurrentSize() const` — Get the current size (in bytess).
- L92 _public function_ `SIZE_T GetMaxSize() const` — Get the maximum size (in bytes).
- L132 _private member_ `FImgMediaGlobalCacheEntry* LeastRecent;` — Entry that was used first.
- L134 _private member_ `FImgMediaGlobalCacheEntry* MostRecent;` — Entry that was used last.
- L137 _private member_ `TMap<FName, FImgMediaGlobalCacheEntry*> MapSequenceToMostRecentEntry;` — Maps a sequence name to the most recent cache entry of that sequence.
- L139 _private member_ `TMap<FImgMediaGlobalCacheEntry*, FName> MapLeastRecentToSequence;` — Maps a cache entry that is the least recent entry to the name of its sequence.
- L141 _private member_ `TMap<TPair<FName, int32>, FImgMediaGlobalCacheEntry*> MapFrameToEntry;` — Maps a sequence name and frame index to an entry in the cache.
- L144 _private member_ `SIZE_T CurrentSize;` — Current size of the cache in bytes.
- L146 _private member_ `SIZE_T MaxSize;` — Maximum size of the cache in bytes.
- L149 _private member_ `mutable FCriticalSection CriticalSection;` — Critical section for synchronizing access to Frames.
- L154 _private member_ `FDelegateHandle UpdateSettingsDelegateHandle;` — Handle to registered UpdateSettings delegate.
- L161 _private member_ `TMap<FString, FDelegateHandle> MapSequenceToWatcher;` — Maps a sequence directory to a directory watcher.
- L163 _private member_ `TMap<FString, int32> MapFileToIndex;` — Maps a file name to the index of that file in the sequence.
- L170 _private prototype_ `void EnforceMaxSize(SIZE_T Extra);` — Empties the cache until the current size + Extra <= the max size of the cache.
- L178 _private prototype_ `void Remove(const FName& Sequence, FImgMediaGlobalCacheEntry& Entry);` — Removes an entry from the cache and deletes the entry. @param	Sequence		Indentifying name of this sequence. @param	Entry			Entry to remove.
- L187 _private prototype_ `void MarkAsRecent(const FName& Sequence, FImgMediaGlobalCacheEntry& Entry);` — Inserts an entry into the cache as the most recent entry. Assumes the entry is not already in the cache. @param	Sequence		Indentifying name of this sequence. @param	Entry			Entry to mark as recent.
- L195 _private prototype_ `void Unlink(const FName& Sequence, FImgMediaGlobalCacheEntry& Entry);` — Removes an entry from the cache but does not delete the entry. @param	Sequence		Indentifying name of this sequence. @param	Entry			Entry to remove.
- L202 _private prototype_ `void Empty();` — Empties the cache. Assumes CriticalSection is already locked.
- L207 _private prototype_ `void UpdateSettings(const UImgMediaSettings* Settings);` — Updates our settings from ImgMediaAsettings.
- L214 _private prototype_ `void OnDirectoryChanged(const TArray<FFileChangeData>& InFileChanges);` — Called when one of our source files changes.

#### struct `FImgMediaGlobalCache::FImgMediaGlobalCacheEntry`  
`struct FImgMediaGlobalCacheEntry`  
_L97-129_
- desc: An entry in the cache.
- L100 _public member_ `FString FileName;` — File name of this frame.
- L102 _public member_ `SIZE_T FrameSize;` — Size of this frame in bytes.
- L104 _public member_ `int32 Index;` — Frame index.
- L106 _public member_ `TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe> Frame;` — Actual frame.
- L109 _public member_ `FImgMediaGlobalCacheEntry* LessRecent;` — Previous entry in the cache.
- L111 _public member_ `FImgMediaGlobalCacheEntry* LessRecentSequence;` — Previous entry in the cache that is part of the same sequence.
- L113 _public member_ `FImgMediaGlobalCacheEntry* MoreRecent;` — Next entry in the cache.
- L115 _public member_ `FImgMediaGlobalCacheEntry* MoreRecentSequence;` — Next entry in the cache that is part of the same sequence.
- L118 _public function_ `FImgMediaGlobalCacheEntry(const FString& InFileName, SIZE_T InFrameSize, int32 InIndex, const TSharedPtr<FImgMediaFrame, ESPMode::ThreadSafe>& InFrame) : FileName(InFileName) , FrameSize(InFrameSize) , Index(InIndex) , Frame(InFrame) , LessRecent(nullptr) , LessRecentSequence(nullptr) , MoreRecent(nullptr) , MoreRecentSequence(nullptr)` — Constructor.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IMGMEDIA_API`

### `Plugins/Media/ImgMedia/Source/ImgMedia/Public/ImgMediaSceneViewExtension.h` (Public)


#### struct `FImgMediaViewInfo`  
`struct FImgMediaViewInfo`  
_L15-33_
- desc: Holds info on a camera which we can use for mipmap calculations.
- L18 _public member_ `FVector Location;` — Position of camera.
- L20 _public member_ `FVector ViewDirection;` — View direction of the camera.
- L22 _public member_ `FMatrix ViewProjectionMatrix;` — View-projection matrix of the camera.
- L24 _public member_ `FMatrix OverscanViewProjectionMatrix;` — View-projection matrix of the camera, optionally scaled for overscan frustum calculations.
- L26 _public member_ `FIntRect ViewportRect;` — Active viewport size.
- L28 _public member_ `float MaterialTextureMipBias;` — View mip bias.
- L30 _public member_ `bool bPrimitiveHiddenMode;` — Hidden or show-only mode for primitive components.
- L32 _public member_ `TSet<FPrimitiveComponentId> PrimitiveComponentIds;` — Hidden or show-only primitive components.

#### class `FImgMediaSceneViewExtension`  
`class FImgMediaSceneViewExtension final : public FSceneViewExtensionBase`  
_L38-95_
- inherits: `FSceneViewExtensionBase`
- desc: Scene view extension used to cache view information (primarily for visible mip/tile calculations).
- L41 _public prototype_ `explicit FImgMediaSceneViewExtension(const FAutoRegister& AutoReg);`
- L53 _public prototype_ `TArray<FImgMediaViewInfo> GetViewInfos(EMediaTextureTargetViewResolution InTargetViewResolutionMask) const;` — Select the appropriate set(s) of cached view infos based on the target resolution mask. When DisplayResolution is requested but the display-resolution cache is empty (which is the common case where render resolution equals display resolution), the render-resolution cache is returned instead. Callers that need to distinguish the two cases must check the cache state externally - this method does not signal which set was actually returned. @param InTargetViewResolutionMask Mask to select the set of view infos. @return Combined ViewInfos.
- L56 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L57 _public prototype_ `virtual int32 GetPriority() const override;`
- L62 _private prototype_ `void CacheViewInfo_NoLock(FSceneViewFamily& InViewFamily, const FSceneView& View);` — Cache camera view information for the current frame. Caller must hold ViewInfosMutex.
- L65 _private prototype_ `void ResetViewInfoCache_NoLock();` — Reset the view info cache. Caller must hold ViewInfosMutex.
- L74 _private member_ `mutable FCriticalSection ViewInfosMutex;` — Protects CachedViewInfos and DisplayResolutionCachedViewInfos. BeginRenderViewFamily holds it across the reset+populate sequence on the game thread; GetViewInfos holds it across the copy on worker threads. This closes the race where a worker iterating CachedViewInfos could observe a TArray::Add reallocation mid-iteration (UAF) or a torn Reset->Add transition.
- L81 _private member_ `TArray<FImgMediaViewInfo> CachedViewInfos;` — Array of info on each camera used for mipmap calculations. Updated on the game thread by BeginRenderViewFamily. Guarded by ViewInfosMutex.
- L89 _private member_ `TArray<FImgMediaViewInfo> DisplayResolutionCachedViewInfos;` — Array of cached camera information at display resolution for compositing. Will remain empty if the render resolution matches the display resolution. Updated on the game thread by BeginRenderViewFamily. Guarded by ViewInfosMutex.
- L94 _private member_ `uint64 LastFrameNumber = ~0ull;` — GFrameNumber when CachedViewInfos was last cleared+populated.

### `Plugins/Media/ImgMedia/Source/ImgMedia/Public/ImgMediaSource.h` (Public)


#### struct `FImgMediaSourceCustomizationSequenceProxy`  
`struct FImgMediaSourceCustomizationSequenceProxy`  
_L23-26_
- reflection: `USTRUCT()`
- desc: This provides customized editing of SequencePath.

#### class `UImgMediaSource`  
`class UImgMediaSource : public UBaseMediaSource`  
_L45-209_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidecategories=(Overrides, Playback))`
- inherits: `UBaseMediaSource`
- desc: Media source for EXR image sequences. Image sequence media sources point to a directory that contains a series of image files in which each image represents a single frame of the sequence. BMP, EXR, PNG and JPG images are currently supported. EXR image sequences are optimized for performance. The first frame of an image sequence is used to determine the image dimensions (all formats) and frame rate (EXR only). The image sequence directory may contain sub-directories, which are called 'proxies'. Proxies can be used to provide alternative media for playback during development and testing of a game. One common scenario is the use of low resolution versions of image sequence media on computers that are too slow or don't have enough storage to play the original high-res media.
- L53 _public prototype_ `UImgMediaSource();` — Default constructor.
- L59 _public member_ `bool IsPathRelativeToProjectRoot_DEPRECATED;` — `UPROPERTY()` — If true, then relative Sequence Paths are relative to the project root directory. If false, then relative to the Content directory.
- L63 _public member_ `FFrameRate FrameRateOverride;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Sequence, AdvancedDisplay)` — Overrides the default frame rate stored in the image files (0/0 = do not override).
- L67 _public member_ `FString ProxyOverride;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Sequence, AdvancedDisplay)` — Name of the proxy directory to use.
- L71 _public member_ `FString LayerName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Sequence, AdvancedDisplay, meta=(DisplayName="Layer Name (EXR)"))` — (EXR only) Name of the layer to read. Empty reads the default (un-prefixed) channels. Supports wildcards (* and ?).
- L75 _public member_ `bool bFillGapsInSequence;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Sequence)` — If true, then any gaps in the sequence will be filled with blank frames.
- L81 _public member_ `FImgMediaSourceCustomizationSequenceProxy SequenceProxy;` — `UPROPERTY(EditAnywhere, Transient, Category = Sequence)` — This is only used so we can customize editing of SequencePath.
- L87 _public member_ `FTimecode StartTimecode;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timecode")` — Specification of a timecode associated with the start of the sequence.
- L91 _public member_ `FMediaSourceColorSettings SourceColorSettings;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sequence", meta = (DisplayAfter = "SequencePath", ShowOnlyInnerProperties))` — Manual definition of media source color space & encoding.
- L102 _public prototype_ `void GetProxies(TArray<FString>& OutProxies) const;` — `UFUNCTION(BlueprintCallable, Category="ImgMedia|ImgMediaSource")` — Get the names of available proxy directories. @param OutProxies Will contain the names of available proxy directories, if any. @see GetSequencePath
- L111 _public prototype_ `const FString GetSequencePath() const;` — `UFUNCTION(BlueprintCallable, Category = "ImgMedia|ImgMediaSource")` — Get the path to the image sequence directory to be played. Supported tokens will be expanded. @return The file path. @see SetSequencePath
- L120 _public prototype_ `void SetSequencePath(const FString& Path);` — `UFUNCTION(BlueprintCallable, Category="ImgMedia|ImgMediaSource")` — Set the path to the image sequence directory this source represents. @param Path The path to an image file in the desired directory. @see GetSequencePath
- L129 _public prototype_ `void SetTokenizedSequencePath(const FString& Path);` — `UFUNCTION(BlueprintCallable, Category = "ImgMedia|ImgMediaSource")` — Set the path to the image sequence directory this source represents. @param Path The path to the desired image sequence directory. May contain supported tokens. @see GetSequencePath
- L140 _public prototype_ `void AddTargetObject(AActor* InActor);` — `UFUNCTION(BlueprintCallable, Category = "ImgMedia|ImgMediaSource", meta = (DeprecatedFunction, DeprecationMessage = "AddTargetObject is no longer needed. Tile-visibility consumers register through FMediaTextureTracker."))` — `UE_DEPRECATED(5.8, "AddTargetObject is no longer needed. Tile-visibility consumers register through FMediaTextureTracker.")` — Deprecated. Tile-visibility registration has moved to FMediaTextureTracker; consumers populate FMediaTextureTrackerObject::TileVisibilityProvider (or the legacy enum fields) directly instead of registering actors against the source. This function is now a no-op. @param InActor Ignored.
- L149 _public prototype_ `void RemoveTargetObject(AActor* InActor);` — `UFUNCTION(BlueprintCallable, Category = "ImgMedia|ImgMediaSource", meta = (DeprecatedFunction, DeprecationMessage = "RemoveTargetObject is no longer needed. Tile-visibility consumers register through FMediaTextureTracker."))` — `UE_DEPRECATED(5.8, "RemoveTargetObject is no longer needed. Tile-visibility consumers register through FMediaTextureTracker.")` — Deprecated. Pair to AddTargetObject; now a no-op for the same reason. @param InActor Ignored.
- L156 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const override;`
- L157 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const override;`
- L158 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const override;`
- L159 _public prototype_ `virtual TSharedPtr<FDataContainer, ESPMode::ThreadSafe> GetMediaOption(const FName& Key, const TSharedPtr<FDataContainer, ESPMode::ThreadSafe>& DefaultValue) const override;`
- L160 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
- L166 _public prototype_ `virtual FString GetUrl() const override;`
- L167 _public prototype_ `virtual bool Validate() const override;`
- L170 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`
- L172 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L179 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L184 _public prototype_ `static FString ExpandSequencePathTokens(const FString& InPath);` — Returns the path after replacing the supported tokens
- L187 _public prototype_ `static FString SanitizeTokenizedSequencePath(const FString& InPath);` — Returns a sanitized sequence path, but without expanding the tokens tokens
- L190 _public prototype_ `static bool IsPathUnderBasePath(const FString& InPath, const FString& InBasePath, FString& OutRelativePath);` — Returns true if InPath is under InBasePath. If so, fills out OutRelativePath with the relative path between them
- L195 _public prototype_ `FString GetFullPath() const;` — Get the full path to the image sequence.
- L205 _protected member_ `FDirectoryPath SequencePath;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Sequence, meta = (EditCondition = "false", EditConditionHides))` — The directory that contains the image sequence files. - Relative paths will be with respect to the current Project directory. - You may use {engine_dir} or {project_dir} tokens.
- L208 _protected member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> NativeSourceColorSettings;` — Native source color settings.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API IMGMEDIA_API`

### `Plugins/Media/ImgMedia/Source/ImgMedia/Public/ImgMediaSourceColorSettings.h` (Public)
_(no declarations extracted)_
