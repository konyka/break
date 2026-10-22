# Plugins / ElectraProtron

- module root: `Plugins/Media/ElectraPlayer/Source/ElectraProtron`
- headers: 5; symbols: 498
- symbol kinds: class=7, delegate=3, enum=4, enumerator=14, function=36, member=225, prototype=185, struct=20, typedef=4
- DynamicallyLoadedModuleNames: Media
- PrivateDependencyModuleNames: Core, D3D12RHI, ElectraBase, ElectraDecoders, ElectraProtronFactory, ElectraSamples, Engine, MP4Boxes, MP4Utilities, MediaUtils, RHI, RenderCore
- PrivateIncludePathModuleNames: Media

### `Plugins/Media/ElectraPlayer/Source/ElectraProtron/Private/ElectraProtronPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraProtron, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraProtron, Log, All);`

### `Plugins/Media/ElectraPlayer/Source/ElectraProtron/Private/Player/ElectraProtronPlayer.h` (Private)


#### class `FElectraProtronPlayer`  
`class FElectraProtronPlayer : public TSharedFromThis<FElectraProtronPlayer, ESPMode::ThreadSafe> , public IMediaPlayer , protected IMediaCache , protected IMediaControls , protected IMediaTracks , protected IMediaView , protected IMediaSamples`  
_L27-161_
- inherits: `TSharedFromThis<FElectraProtronPlayer,ESPMode::ThreadSafe>,IMediaPlayer,IMediaCache,IMediaControls,IMediaTracks,IMediaView,IMediaSamples`
- L42 _public prototype_ `FElectraProtronPlayer(IMediaEventSink& InEventSink);` — Create and initialize a new instance. @param InEventSink The object that receives media events from this player.
- L45 _public prototype_ `virtual ~FElectraProtronPlayer();` — Virtual destructor.
- L51 _public prototype_ `void Close() override;`
- L52 _public prototype_ `IMediaCache& GetCache() override;`
- L53 _public prototype_ `IMediaControls& GetControls() override;`
- L54 _public prototype_ `FString GetInfo() const override;`
- L55 _public prototype_ `FGuid GetPlayerPluginGUID() const override;`
- L56 _public prototype_ `IMediaSamples& GetSamples() override;`
- L57 _public prototype_ `FString GetStats() const override;`
- L58 _public prototype_ `IMediaTracks& GetTracks() override;`
- L59 _public prototype_ `FString GetUrl() const override;`
- L60 _public prototype_ `IMediaView& GetView() override;`
- L61 _public prototype_ `bool Open(const FString& InUrl, const IMediaOptions* InOptions) override;`
- L62 _public prototype_ `bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& InArchive, const FString& InOriginalUrl, const IMediaOptions* InOptions) override;`
- L63 _public prototype_ `bool Open(const FString& InUrl, const IMediaOptions* InOptions, const FMediaPlayerOptions* InPlayerOptions) override;`
- L64 _public prototype_ `FVariant GetMediaInfo(FName InInfoName) const override;`
- L65 _public prototype_ `bool GetPlayerFeatureFlag(EFeatureFlag InWhichFeature) const override;`
- L66 _public prototype_ `void TickFetch(FTimespan InDeltaTime, FTimespan InTimecode) override;`
- L67 _public prototype_ `void TickInput(FTimespan InDeltaTime, FTimespan InTimecode) override;`
- L71 _protected prototype_ `bool CanControl(EMediaControl InControl) const override;`
- L72 _protected prototype_ `FTimespan GetDuration() const override;`
- L73 _protected prototype_ `float GetRate() const override;`
- L74 _protected prototype_ `EMediaState GetState() const override;`
- L75 _protected prototype_ `EMediaStatus GetStatus() const override;`
- L76 _protected prototype_ `TRangeSet<float> GetSupportedRates(EMediaRateThinning InThinning) const override;`
- L77 _protected prototype_ `FTimespan GetTime() const override;`
- L78 _protected prototype_ `bool IsLooping() const override;`
- L79 _protected function_ `bool Seek(const FTimespan& Time) override`
- L81 _protected prototype_ `bool Seek(const FTimespan& InNewTime, const FMediaSeekParams& InAdditionalParams) override;`
- L82 _protected prototype_ `bool SetLooping(bool bInLooping) override;`
- L83 _protected prototype_ `bool SetRate(float InRate) override;`
- L84 _protected prototype_ `TRange<FTimespan> GetPlaybackTimeRange(EMediaTimeRangeType InRangeToGet) const override;`
- L85 _protected prototype_ `bool SetPlaybackTimeRange(const TRange<FTimespan>& InTimeRange) override;`
- L89 _protected prototype_ `bool GetAudioTrackFormat(int32 InTrackIndex, int32 InFormatIndex, FMediaAudioTrackFormat& OutFormat) const override;`
- L90 _protected prototype_ `int32 GetNumTracks(EMediaTrackType InTrackType) const override;`
- L91 _protected prototype_ `int32 GetNumTrackFormats(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L92 _protected prototype_ `int32 GetSelectedTrack(EMediaTrackType InTrackType) const override;`
- L93 _protected prototype_ `FText GetTrackDisplayName(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L94 _protected prototype_ `int32 GetTrackFormat(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L95 _protected prototype_ `FString GetTrackLanguage(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L96 _protected prototype_ `FString GetTrackName(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L97 _protected prototype_ `bool GetVideoTrackFormat(int32 InTrackIndex, int32 InFormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L98 _protected prototype_ `bool SelectTrack(EMediaTrackType InTrackType, int32 InTrackIndex) override;`
- L99 _protected prototype_ `bool SetTrackFormat(EMediaTrackType InTrackType, int32 InTrackIndex, int32 InFormatIndex) override;`
- L100 _protected prototype_ `TOptional<FTimespan> GetTrackDuration(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L103 _protected prototype_ `bool QueryCacheState(EMediaCacheState InState, TRangeSet<FTimespan>& OutTimeRanges) const override;`
- L104 _protected prototype_ `int32 GetSampleCount(EMediaCacheState InState) const override;`
- L107 _protected prototype_ `EFetchBestSampleResult FetchBestVideoSampleForTimeRange(const TRange<FMediaTimeStamp>& InTimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample, bool bInReverse, bool bInConsistentResult) override;`
- L108 _protected prototype_ `bool FetchAudio(TRange<FMediaTimeStamp> InTimeRange, TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& OutSample) override;`
- L109 _protected prototype_ `bool FetchCaption(TRange<FMediaTimeStamp> InTimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample) override;`
- L110 _protected prototype_ `bool FetchMetadata(TRange<FMediaTimeStamp> InTimeRange, TSharedPtr<IMediaBinarySample, ESPMode::ThreadSafe>& OutSample) override;`
- L111 _protected prototype_ `bool FetchSubtitle(TRange<FMediaTimeStamp> InTimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample) override;`
- L112 _protected prototype_ `void FlushSamples() override;`
- L113 _protected prototype_ `void SetMinExpectedNextSequenceIndex(TOptional<int32> InNextSequenceIndex) override;`
- L114 _protected prototype_ `bool PeekVideoSampleTime(FMediaTimeStamp& OutTimeStamp) override;`
- L115 _protected prototype_ `bool CanReceiveVideoSamples(uint32 InNum) const override;`
- L116 _protected prototype_ `bool CanReceiveAudioSamples(uint32 InNum) const override;`
- L117 _protected prototype_ `bool CanReceiveSubtitleSamples(uint32 InNum) const override;`
- L118 _protected prototype_ `bool CanReceiveCaptionSamples(uint32 InNum) const override;`
- L119 _protected prototype_ `bool CanReceiveMetadataSamples(uint32 InNum) const override;`
- L120 _protected prototype_ `int32 NumAudioSamples() const override;`
- L121 _protected prototype_ `int32 NumCaptionSamples() const override;`
- L122 _protected prototype_ `int32 NumMetadataSamples() const override;`
- L123 _protected prototype_ `int32 NumSubtitleSamples() const override;`
- L124 _protected prototype_ `int32 NumVideoSamples() const override;`
- L129 _private function_ `TSharedPtr<FImpl, ESPMode::ThreadSafe> GetCurrentPlayer() const`
- L142 _private prototype_ `void CheckForStateChanges();`
- L145 _private member_ `TSharedPtr<FImpl, ESPMode::ThreadSafe> CurrentPlayer;`
- L146 _private member_ `TOptional<TRange<FTimespan>> CurrentPlaybackRange;`
- L147 _private member_ `int32 CurrentSequenceIndex = 0;`
- L148 _private member_ `EInternalState CurrentInternalState = EInternalState::Closed;`
- L150 _private member_ `IMediaEventSink& EventSink;`
- L152 _private member_ `FString LastError;`
- L153 _private member_ `FString CurrentURL;`
- L155 _private member_ `TSharedPtr<FElectraTextureSamplePool, ESPMode::ThreadSafe> CurrentTexturePool;`
- L156 _private member_ `TSharedPtr<FElectraAudioSamplePool, ESPMode::ThreadSafe> CurrentAudioSamplePool;`
- L159 _private member_ `EMediaState CurrentState;` — Current player state.
- L160 _private member_ `EMediaStatus CurrentStatus;`

#### enum `FElectraProtronPlayer::EInternalState`  
`enum class EInternalState`  
_L134-141_
- L136 _public enumerator_ `Closed`
- L137 _public enumerator_ `Opening`
- L138 _public enumerator_ `Opened`
- L139 _public enumerator_ `Ready`
- L140 _public enumerator_ `Failed`

### `Plugins/Media/ElectraPlayer/Source/ElectraProtron/Private/Player/ElectraProtronPlayerCache.h` (Private)


#### class `FProtronVideoCache`  
`class FProtronVideoCache`  
_L14-67_
- L17 _public prototype_ `FProtronVideoCache();`
- L18 _public prototype_ `void SetMaxFramesToCache(int32 InNumVideoFramesToCacheAhead, int32 InNumVideoFramesToCacheBehind);`
- L19 _public prototype_ `void SetPlaybackRange(TRange<FTimespan> InRange);`
- L20 _public prototype_ `void SeekIssuedTo(FTimespan InNewPosition);`
- L21 _public prototype_ `void SetPlaybackRate(float InNewRate);`
- L23 _public prototype_ `bool Contains(FTimespan InPTS);`
- L24 _public prototype_ `int32 Find(FTimespan InPTS);`
- L25 _public prototype_ `bool CanAccept(FTimespan InPTS);`
- L26 _public prototype_ `void Empty();`
- L28 _public prototype_ `void QueryCacheState(TRangeSet<FTimespan>& OutTimeRanges);`
- L37 _public prototype_ `EGetResult GetFrame(TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutFrame, const TRange<FMediaTimeStamp>& InTimeRange, bool bIsLooping, bool bInReverse, bool bInUseFirstMatch);`
- L39 _public prototype_ `void PerformMaintenance(int32 InAtIndex, bool bIsLooping, bool bInReverse);`
- L41 _public prototype_ `void AddFrame(TSharedRef<IMediaTextureSample, ESPMode::ThreadSafe> InFrame, FTimespan InRawPTS, FTimespan InRawDuration);`
- L44 _private member_ `FCriticalSection Lock;`
- L51 _private prototype_ `int32 GetConsecutiveFutureSamples(TArray<int32>& OutIndices, int32& OutWrapIndex, int32 InStartFrameIndex, bool bInLooping);`
- L52 _private prototype_ `int32 GetConsecutivePreviousSamples(TArray<int32>& OutIndices, int32& OutWrapIndex, int32 InStartFrameIndex, bool bInLooping);`
- L56 _private member_ `TArray<FEntry> Entries;`
- L57 _private member_ `TRange<FTimespan> PlaybackRange;`
- L58 _private member_ `FTimespan PlaybackRangeEndInclusive;`
- L61 _private member_ `TOptional<FTimespan> CurrentReadTime;` — The position around which to check for consecutive future and past samples when adding.
- L63 _private member_ `float PlaybackRate = 0.0f;`
- L64 _private member_ `int32 MaxFramesToCache = 0;`
- L65 _private member_ `int32 NumVideoFramesToCacheAhead = 0;`
- L66 _private member_ `int32 NumVideoFramesToCacheBehind = 0;`

#### enum `FProtronVideoCache::EGetResult`  
`enum class EGetResult`  
_L30-35_
- L32 _public enumerator_ `Hit`
- L33 _public enumerator_ `Miss`
- L34 _public enumerator_ `PurgedEmpty`

#### struct `FProtronVideoCache::FEntry`  
`struct FEntry`  
_L45-49_
- L47 _public member_ `TRange<FTimespan> RawRange;`
- L48 _public member_ `TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe> Frame;`

### `Plugins/Media/ElectraPlayer/Source/ElectraProtron/Private/Player/ElectraProtronPlayerImpl.h` (Private)


#### class `FElectraProtronPlayer::FImpl`  
`class FElectraProtronPlayer::FImpl : public TSharedFromThis<FElectraProtronPlayer::FImpl, ESPMode::ThreadSafe>, public FRunnable`  
_L33-755_
- inherits: `TSharedFromThis<FElectraProtronPlayer::FImpl,ESPMode::ThreadSafe>,FRunnable`
- desc: Private player implementation managed through a thread-safe pointer and a worker thread to not block the game thread.
- L253 _public typedef_ `using ImplPointer = TSharedPtr<FImpl, ESPMode::ThreadSafe>;` — Define pointer type to get around the ',' in the name that confuses the delegate declaration macro.
- L254 _public prototype_ `DECLARE_DELEGATE_OneParam(FCompletionDelegate, ImplPointer);`
- L256 _public prototype_ `FImpl();`
- L257 _public prototype_ `~FImpl();`
- L266 _public prototype_ `void Open(const FOpenParam& InParam, FCompletionDelegate InCompletionDelegate);`
- L267 _public prototype_ `void Close(FCompletionDelegate InCompletionDelegate);`
- L268 _public prototype_ `FString GetLastError();`
- L269 _public prototype_ `bool HasReachedEnd();`
- L272 _public function_ `FTimespan GetDuration()` — Implementation methods from FElectraProtronPlayer
- L274 _public prototype_ `FVariant GetMediaInfo(FName InInfoName);`
- L275 _public prototype_ `bool GetAudioTrackFormat(int32 InTrackIndex, int32 InFormatIndex, FMediaAudioTrackFormat& OutFormat);`
- L276 _public prototype_ `int32 GetNumTracks(EMediaTrackType InTrackType);`
- L277 _public prototype_ `int32 GetNumTrackFormats(EMediaTrackType InTrackType, int32 InTrackIndex);`
- L278 _public prototype_ `int32 GetSelectedTrack(EMediaTrackType InTrackType);`
- L279 _public prototype_ `FText GetTrackDisplayName(EMediaTrackType InTrackType, int32 InTrackIndex);`
- L280 _public prototype_ `int32 GetTrackFormat(EMediaTrackType InTrackType, int32 InTrackIndex);`
- L281 _public prototype_ `FString GetTrackLanguage(EMediaTrackType InTrackType, int32 InTrackIndex);`
- L282 _public prototype_ `FString GetTrackName(EMediaTrackType InTrackType, int32 InTrackIndex);`
- L283 _public prototype_ `bool GetVideoTrackFormat(int32 InTrackIndex, int32 InFormatIndex, FMediaVideoTrackFormat& OutFormat);`
- L284 _public prototype_ `bool SelectTrack(EMediaTrackType InTrackType, int32 InTrackIndex);`
- L285 _public prototype_ `bool SetTrackFormat(EMediaTrackType InTrackType, int32 InTrackIndex, int32 InFormatIndex);`
- L286 _public prototype_ `TOptional<FTimespan> GetTrackDuration(EMediaTrackType InTrackType, int32 InTrackIndex);`
- L287 _public prototype_ `bool QueryCacheState(EMediaCacheState InState, TRangeSet<FTimespan>& OutTimeRanges);`
- L288 _public prototype_ `int32 GetSampleCount(EMediaCacheState InState);`
- L290 _public prototype_ `TRangeSet<float> GetSupportedRates(EMediaRateThinning InThinning);`
- L291 _public prototype_ `float GetRate();`
- L292 _public prototype_ `bool SetRate(float InRate);`
- L293 _public prototype_ `FTimespan GetTime();`
- L294 _public prototype_ `bool SetLooping(bool bInLooping);`
- L295 _public prototype_ `bool IsLooping();`
- L296 _public prototype_ `void Seek(const FTimespan& InTime, int32 InNewSequenceIndex, const TOptional<int32>& InNewLoopIndex);`
- L297 _public prototype_ `TRange<FTimespan> GetPlaybackTimeRange(EMediaTimeRangeType InRangeToGet);`
- L298 _public prototype_ `bool SetPlaybackTimeRange(const TRange<FTimespan>& InTimeRange);`
- L300 _public prototype_ `void TickFetch(FTimespan InDeltaTime, FTimespan InTimecode);`
- L301 _public prototype_ `void TickInput(FTimespan InDeltaTime, FTimespan InTimecode);`
- L304 _public prototype_ `uint32 Run() override;` — Inherited from FRunnable
- L305 _public prototype_ `void Exit() override;`
- L308 _public prototype_ `EFetchBestSampleResult FetchBestVideoSampleForTimeRange(const TRange<FMediaTimeStamp>& TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample, bool bInReverse, bool bInConsistentResult);` — Forwarded IMediaSamples interface methods from the enclosing FElectraProtronPlayer
- L309 _public prototype_ `bool FetchAudio(TRange<FMediaTimeStamp> InTimeRange, TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& OutSample);`
- L310 _public prototype_ `bool FetchCaption(TRange<FMediaTimeStamp> InTimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample);`
- L311 _public prototype_ `bool FetchMetadata(TRange<FMediaTimeStamp> InTimeRange, TSharedPtr<IMediaBinarySample, ESPMode::ThreadSafe>& OutSample);`
- L312 _public prototype_ `bool FetchSubtitle(TRange<FMediaTimeStamp> InTimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample);`
- L313 _public prototype_ `void FlushSamples();`
- L314 _public prototype_ `void SetMinExpectedNextSequenceIndex(TOptional<int32> InNextSequenceIndex);`
- L315 _public prototype_ `bool PeekVideoSampleTime(FMediaTimeStamp& OutTimeStamp);`
- L316 _public prototype_ `bool CanReceiveVideoSamples(uint32 InNum) const;`
- L317 _public prototype_ `bool CanReceiveAudioSamples(uint32 InNum) const;`
- L318 _public prototype_ `bool CanReceiveSubtitleSamples(uint32 InNum) const;`
- L319 _public prototype_ `bool CanReceiveCaptionSamples(uint32 InNum) const;`
- L320 _public prototype_ `bool CanReceiveMetadataSamples(uint32 InNum) const;`
- L321 _public prototype_ `int32 NumAudioSamples() const;`
- L322 _public prototype_ `int32 NumCaptionSamples() const;`
- L323 _public prototype_ `int32 NumMetadataSamples() const;`
- L324 _public prototype_ `int32 NumSubtitleSamples() const;`
- L325 _public prototype_ `int32 NumVideoSamples() const;`
- L328 _private function_ `static constexpr int32 CodecTypeIndex(const Electra::FCodecTypeFormat::EType InType)`
- L423 _private typedef_ `using FMP4SamplePtr = TSharedPtr<FMP4Sample, ESPMode::ThreadSafe>;`
- L425 _private typedef_ `using FTrackIterator = TSharedPtr<MP4Boxes::FMP4Track::FIterator, ESPMode::ThreadSafe>;`
- L440 _private typedef_ `using FMP4TrackSampleBufferPtr = TSharedPtr<FMP4TrackSampleBuffer, ESPMode::ThreadSafe>;`
- L443 _private prototype_ `void StartThread();`
- L444 _private prototype_ `void SendWorkerThreadMessage(FWorkerThreadMessage&& InMessage);`
- L446 _private prototype_ `void InternalOpen(const FString& InFilename);`
- L448 _private prototype_ `void UpdateTrackLoader(int32 InCodecTypeIndex);`
- L450 _private prototype_ `void HandleActiveTrackChanges();`
- L451 _private prototype_ `void HandleRateChanges();`
- L452 _private prototype_ `void HandleSeekRequest(const FSeekRequest& InSeekRequest);`
- L454 _private member_ `const int32 kCodecTrackIndexMap[(int32) Electra::FCodecTypeFormat::EType::MAX] = { CodecTypeIndex(Electra::FCodecTypeFormat::EType::Video), CodecTypeIndex(Electra::FCodecTypeFormat::EType::Audio), CodecTypeIndex(Electra::FCodecTypeFormat::EType::Subtitle), CodecTypeIndex(Electra::FCodecTypeFormat::EType::Timecode) };`
- L462 _private member_ `FConfig Config;`
- L464 _private member_ `FRunnableThread* Thread = nullptr;`
- L465 _private member_ `ImplPointer SelfDuringTerminate;`
- L466 _private member_ `FMediaEvent WorkMessageSignal;`
- L467 _private member_ `TQueue<FWorkerThreadMessage, EQueueMode::Mpsc> WorkMessages;`
- L468 _private member_ `FString LastErrorMessage;`
- L469 _private member_ `bool bAbort = false;`
- L470 _private member_ `TArray<TSharedPtr<MP4Boxes::FMP4BoxBase>> ParsedRootBoxes;`
- L471 _private member_ `TArray<TSharedPtr<FTrackInfo, ESPMode::ThreadSafe>> Tracks;`
- L472 _private member_ `TArray<TArray<int32>> UsableTrackArrayIndicesByType;`
- L474 _private member_ `MP4Utilities::FFractionalTime MovieDuration;`
- L475 _private member_ `FTimespan Duration;` — already converted `MovieDuration` for faster access
- L476 _private member_ `FTrackSelection TrackSelection;`
- L477 _private member_ `TRangeSet<float> UnthinnedRates;`
- L478 _private member_ `TRangeSet<float> ThinnedRates;`
- L479 _private member_ `bool bAreRatesValid = false;`
- L480 _private member_ `FTimespan CurrentPlayPosTime;`
- L481 _private member_ `TRange<FTimespan> CurrentPlaybackRange;`
- L482 _private member_ `float CurrentRate = 0.0f;`
- L483 _private member_ `float IntendedRate = 0.0f;`
- L485 _private member_ `FCriticalSection SeekRequestLock;`
- L486 _private member_ `TOptional<FSeekRequest> PendingSeekRequest;`
- L488 _private member_ `TMap<uint32, FMP4TrackSampleBufferPtr> TrackSampleBuffers;`
- L490 _private member_ `TSharedPtr<FSharedPlayParams, ESPMode::ThreadSafe> SharedPlayParams;`
- L492 _private member_ `TSharedPtr<FSampleQueueInterface, ESPMode::ThreadSafe> CurrentSampleQueueInterface;`
- L493 _private function_ `TSharedPtr<FSampleQueueInterface, ESPMode::ThreadSafe> GetCurrentSampleQueueInterface() const`
- L501 _private prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FMP4SamplePtr, FGetSampleDlg, FMP4TrackSampleBufferPtr , const FTrackIterator& , int32 );`
- L750 _private member_ `FLoaderThread VideoLoaderThread {Config, CodecTypeIndex(Electra::FCodecTypeFormat::EType::Video)};`
- L751 _private member_ `FLoaderThread AudioLoaderThread {Config, CodecTypeIndex(Electra::FCodecTypeFormat::EType::Audio)};`
- L753 _private member_ `FDecoderThread VideoDecoderThread {Config, CodecTypeIndex(Electra::FCodecTypeFormat::EType::Video)};`
- L754 _private member_ `FDecoderThread AudioDecoderThread {Config, CodecTypeIndex(Electra::FCodecTypeFormat::EType::Audio)};`

#### class `FElectraProtronPlayer::FImpl::FSampleQueueInterface`  
`class FSampleQueueInterface : public TSharedFromThis<FSampleQueueInterface, ESPMode::ThreadSafe>`  
_L36-249_
- inherits: `TSharedFromThis<FSampleQueueInterface,ESPMode::ThreadSafe>`
- L39 _public function_ `FSampleQueueInterface(int32 InNumVideoFramesToCacheAhead, int32 InNumVideoFramesToCacheBehind) : SampleQueue(MakeShared<FMediaSamples, ESPMode::ThreadSafe>()) , NumVideoFramesToCache(InNumVideoFramesToCacheAhead + InNumVideoFramesToCacheBehind)`
- L50 _public function_ `int32 GetMaxVideoFramesToCache()`
- L55 _public function_ `void SetMovieDuration(FTimespan InDuration)`
- L61 _public function_ `FTimespan GetMovieDuration()`
- L66 _public function_ `void SetPlaybackRange(TRange<FTimespan> InRange)`
- L71 _public function_ `TRange<FTimespan> GetPlaybackRange()`
- L76 _public function_ `void SetPlaybackRate(float InNewRate)`
- L82 _public function_ `void SeekIssuedTo(FTimespan InToTime, TOptional<int32> InNextSequenceIndex)`
- L94 _public function_ `void SetVideoTrackEnabled(bool bInEnabled)`
- L98 _public function_ `void SetAudioTrackEnabled(bool bInEnabled)`
- L102 _public function_ `bool IsVideoTrackEnabled() const`
- L106 _public function_ `bool IsAudioTrackEnabled() const`
- L110 _public function_ `void VideoSampleWillBeReady()`
- L114 _public function_ `void AudioSampleWillBeReady()`
- L118 _public function_ `bool AreRequiredSamplesReady() const`
- L124 _public function_ `bool CanEnqueueVideoSample(FTimespan InPTS)`
- L129 _public function_ `bool CanEnqueueAudioSample()`
- L134 _public function_ `void EnqueueVideoSample(const TSharedRef<IMediaTextureSample, ESPMode::ThreadSafe>& InSample, FTimespan InRawPTS, FTimespan InRawDuration)`
- L149 _public function_ `void EnqueueAudioSample(const TSharedRef<IMediaAudioSample, ESPMode::ThreadSafe>& InSample)`
- L154 _public function_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> GetCurrentSampleQueue()`
- L159 _public function_ `bool PeekVideoSampleTime(FMediaTimeStamp& OutTimeStamp)`
- L170 _public function_ `void UpdateLastHandedOutTimestamp(const TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& InSample)`
- L176 _public function_ `FMediaTimeStamp GetLastHandedOutTimestamp()`
- L182 _public function_ `void UpdateNextExpectedTimestamp(const TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& InSample, bool bInReverse, bool bInIsLooping)`
- L222 _public function_ `void ResetCurrentTimestamps()`
- L229 _public function_ `FProtronVideoCache& GetVideoCache()`
- L235 _private member_ `FProtronVideoCache VideoCache;`
- L236 _private member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> SampleQueue;`
- L237 _private member_ `FCriticalSection TimestampLock;`
- L238 _private member_ `FMediaTimeStamp NextExpectedTimestamp;`
- L239 _private member_ `FMediaTimeStamp LastHandedOutTimestamp;`
- L240 _private member_ `TOptional<int32> MinSeqIdx;`
- L241 _private member_ `FTimespan Duration;`
- L242 _private member_ `TRange<FTimespan> PlaybackRange;`
- L243 _private member_ `float PlaybackRate = 0.0f;`
- L244 _private member_ `int32 NumVideoFramesToCache = 0;`
- L245 _private member_ `bool bIsVideoTrackEnabled = false;`
- L246 _private member_ `bool bIsAudioTrackEnabled = false;`
- L247 _private member_ `bool bVideoSampleWillBeReady = false;`
- L248 _private member_ `bool bAudioSampleWillBeReady = false;`

#### struct `FElectraProtronPlayer::FImpl::FOpenParam`  
`struct FOpenParam`  
_L258-265_
- L260 _public member_ `FString Filename;`
- L261 _public member_ `TSharedPtr<FSampleQueueInterface, ESPMode::ThreadSafe> SampleQueueInterface;`
- L262 _public member_ `TSharedPtr<FElectraTextureSamplePool, ESPMode::ThreadSafe> TexturePool;`
- L263 _public member_ `TSharedPtr<FElectraAudioSamplePool, ESPMode::ThreadSafe> AudioSamplePool;`
- L264 _public member_ `TOptional<TRange<FTimespan>> InitialPlaybackRange;`

#### struct `FElectraProtronPlayer::FImpl::FConfig`  
`struct FConfig`  
_L331-338_
- L333 _public member_ `FTimespan DurationCacheAhead { ETimespan::TicksPerSecond * 2 };`
- L334 _public member_ `FTimespan DurationCacheBehind { ETimespan::TicksPerSecond * 1 };`
- L335 _public member_ `int32 NextKeyframeThresholdMillis { 2 };`
- L336 _public member_ `bool bReadFirstTimecode = true;`
- L337 _public member_ `bool bReadSampleTimecode = true;`

#### struct `FElectraProtronPlayer::FImpl::FSharedPlayParams`  
`struct FSharedPlayParams`  
_L340-345_
- L342 _public member_ `float DesiredPlayRate = 0.0f;`
- L343 _public member_ `float PlaybackDirection = 0.0f;`
- L344 _public member_ `bool bShouldLoop = false;`

#### struct `FElectraProtronPlayer::FImpl::FSeekRequest`  
`struct FSeekRequest`  
_L347-352_
- L349 _public member_ `FTimespan NewTime;`
- L350 _public member_ `int32 NewSequenceIndex = 0;`
- L351 _public member_ `TOptional<int32> NewLoopIndex;`

#### struct `FElectraProtronPlayer::FImpl::FWorkerThreadMessage`  
`struct FWorkerThreadMessage`  
_L354-374_
- L370 _public member_ `EType Type = EType::Nop;`
- L371 _public member_ `ImplPointer Self;`
- L372 _public member_ `FCompletionDelegate CompletionDelegate;`
- L373 _public member_ `TVariant<FParamOpen, FParamTerminate> Param;`

#### enum `FElectraProtronPlayer::FImpl::FWorkerThreadMessage::EType`  
`enum class EType`  
_L356-361_
- L358 _public enumerator_ `Nop`
- L359 _public enumerator_ `Open`
- L360 _public enumerator_ `Terminate`

#### struct `FElectraProtronPlayer::FImpl::FWorkerThreadMessage::FParamOpen`  
`struct FParamOpen`  
_L362-365_
- L364 _public member_ `FOpenParam Param;`

#### struct `FElectraProtronPlayer::FImpl::FWorkerThreadMessage::FParamTerminate`  
`struct FParamTerminate`  
_L366-368_

#### struct `FElectraProtronPlayer::FImpl::FTrackInfo`  
`struct FTrackInfo`  
_L376-398_
- L378 _public member_ `TArray<TWeakPtr<FTrackInfo, ESPMode::ThreadSafe>> IsReferencedByTracks;`
- L379 _public member_ `Electra::FCodecTypeFormat CodecInfo;`
- L380 _public member_ `Electra::FDRMTypeFormat DrmFormat;`
- L381 _public member_ `Electra::FDecoderInformation DecoderInformation;`
- L383 _public member_ `FTimespan Duration;`
- L384 _public member_ `TSharedPtr<MP4Boxes::FMP4BoxTRAK, ESPMode::ThreadSafe> TrackBox;`
- L385 _public member_ `TSharedPtr<MP4Boxes::FMP4Track::FFragmentInfo, ESPMode::ThreadSafe> FragmentInfo;`
- L386 _public member_ `TSharedPtr<MP4Boxes::FMP4Track, ESPMode::ThreadSafe> MP4Track;`
- L387 _public member_ `TWeakPtr<FTrackInfo, ESPMode::ThreadSafe> ReferencedTimecodeTrack;`
- L388 _public member_ `uint32 TrackID = 0;`
- L389 _public member_ `bool bIsUsable = false;`
- L390 _public member_ `bool bIsKeyframeOnlyFormat = false;`
- L397 _public member_ `TOptional<FFirstSampleTimecode> FirstSampleTimecode;`

#### struct `FElectraProtronPlayer::FImpl::FTrackInfo::FFirstSampleTimecode`  
`struct FFirstSampleTimecode`  
_L391-396_
- L393 _public member_ `FString Timecode;`
- L394 _public member_ `FString Framerate;`
- L395 _public member_ `uint32 TimecodeValue = 0;`

#### struct `FElectraProtronPlayer::FImpl::FTrackSelection`  
`struct FTrackSelection`  
_L400-405_
- L402 _public member_ `int32 SelectedTrackIndex[4] {-1, -1, -1, -1};`
- L403 _public member_ `int32 ActiveTrackIndex[4] {-1, -1, -1, -1};`
- L404 _public member_ `bool bChanged = false;`

#### struct `FElectraProtronPlayer::FImpl::FMP4Sample`  
`struct FMP4Sample`  
_L407-422_
- L409 _public member_ `TArray<uint8> Data;`
- L410 _public member_ `FTimespan DTS;`
- L411 _public member_ `FTimespan PTS;`
- L412 _public member_ `FTimespan EffectiveDTS;`
- L413 _public member_ `FTimespan EffectivePTS;`
- L414 _public member_ `FTimespan Duration;`
- L415 _public member_ `int64 SizeInBytes;`
- L416 _public member_ `int64 OffsetInFile;`
- L417 _public member_ `uint32 TrackID;`
- L418 _public member_ `uint32 SampleNumber;`
- L419 _public member_ `bool bIsSyncOrRap;`
- L420 _public member_ `TOptional<FTimecode> AssociatedTimecode;`
- L421 _public member_ `TOptional<FFrameRate> AssociatedTimecodeFramerate;`

#### struct `FElectraProtronPlayer::FImpl::FMP4TrackSampleBuffer`  
`struct FMP4TrackSampleBuffer`  
_L427-439_
- L429 _public member_ `FCriticalSection Lock;`
- L430 _public member_ `TRangeSet<uint32> SampleRanges;`
- L431 _public member_ `TSortedMap<uint32, FMP4SamplePtr> SampleMap;`
- L432 _public member_ `TSharedPtr<FTrackInfo, ESPMode::ThreadSafe> TrackAndCodecInfo;`
- L433 _public member_ `uint32 TrackID;`
- L436 _public member_ `TRange<FTimespan> CurrentPlaybackRange;` — Used by the sample loader
- L437 _public member_ `FTrackIterator FirstRangeSampleIt;`
- L438 _public member_ `FTrackIterator LastRangeSampleIt;`

#### class `FElectraProtronPlayer::FImpl::FLoaderThread`  
`class FLoaderThread : public FRunnable`  
_L503-588_
- inherits: `FRunnable`
- L506 _public function_ `FLoaderThread(const FConfig& InConfig, int32 InCodecTypeIndex) : Config(InConfig), LoaderTypeIndex(InCodecTypeIndex)`
- L510 _public function_ `FString GetLastError()`
- L514 _public prototype_ `uint32 Run() override;` — Inherited from FRunnable
- L517 _public prototype_ `void StartThread(const FString& InFilename, const TSharedPtr<FSharedPlayParams, ESPMode::ThreadSafe>& InSharedPlayParams);` — Thread start/stop
- L518 _public prototype_ `void StopThread();`
- L521 _public prototype_ `void SetPlaybackRange(TRange<FTimespan> InRange);` — Called by the player
- L522 _public prototype_ `void RequestLoad(FMP4TrackSampleBufferPtr InTrackSampleBuffer, FTimespan InTime);`
- L523 _public prototype_ `TRangeSet<FTimespan> GetTimeRangesToLoad();`
- L526 _public prototype_ `FMP4SamplePtr GetSample(FMP4TrackSampleBufferPtr InFromBuffer, const FTrackIterator& InAtIterator, int32 InWaitMicroseconds);` — Called by the decoder
- L546 _private member_ `const FConfig& Config;`
- L547 _private member_ `int32 LoaderTypeIndex;`
- L549 _private member_ `FRunnableThread* Thread = nullptr;`
- L550 _private member_ `FMediaEvent WorkSignal;`
- L551 _private member_ `volatile bool bTerminateThread = false;`
- L553 _private member_ `TSharedPtr<FSharedPlayParams, ESPMode::ThreadSafe> SharedPlayParams;`
- L554 _private member_ `TSharedPtr<MP4Utilities::FMP4FileDataReader, ESPMode::ThreadSafe> Reader;`
- L555 _private member_ `FString LastErrorMessage;`
- L557 _private member_ `FCriticalSection LoadRequestLock;`
- L558 _private member_ `FOpenRequest OpenRequest;`
- L559 _private member_ `FLoadRequest PendingLoadRequest;`
- L560 _private member_ `FLoadRequest ActiveLoadRequest;`
- L561 _private member_ `TRange<FTimespan> PlaybackRange;`
- L562 _private member_ `FCriticalSection TimeRangeLock;`
- L563 _private member_ `TRangeSet<FTimespan> TimeRangesToLoad;`
- L564 _private member_ `volatile int32 LoadRequestDirty = -1;`
- L573 _private prototype_ `ELoadResult Load(FMP4TrackSampleBufferPtr InTrackSampleBuffer, FTrackIterator InAtIterator);`
- L574 _private prototype_ `FMP4SamplePtr RetrieveSample(const FMP4TrackSampleBufferPtr& InTrackSampleBuffer, const FTrackIterator& InSampleIt, const FTrackIterator& InOptionalTimecodeIt, const Electra::FCodecTypeFormat::FTMCDTimecode& InTimecodeInfo);`
- L585 _private prototype_ `void CalcRangeToLoad(FSampleRange& OutRange, const FMP4TrackSampleBufferPtr& InTrackSampleBuffer, const FTrackIterator& InSampleIt);`
- L587 _private prototype_ `void GetUnreferencedFrames(TArray<uint32>& OutFramesToRemove, const FMP4TrackSampleBufferPtr& InTrackSampleBuffer, const FSampleRange& InActiveSampleRange);`

#### struct `FElectraProtronPlayer::FImpl::FLoaderThread::FOpenRequest`  
`struct FOpenRequest`  
_L528-532_
- L530 _public member_ `FString Filename;`
- L531 _public member_ `TSharedPtr<FSharedPlayParams, ESPMode::ThreadSafe> SharedPlayParams;`

#### struct `FElectraProtronPlayer::FImpl::FLoaderThread::FLoadRequest`  
`struct FLoadRequest`  
_L533-544_
- L535 _public function_ `void Empty()`
- L541 _public member_ `FMP4TrackSampleBufferPtr TrackSampleBuffer;`
- L542 _public member_ `FTrackIterator StartAtIterator;`
- L543 _public member_ `FTrackIterator UpdateAtIterator;`

#### enum `FElectraProtronPlayer::FImpl::FLoaderThread::ELoadResult`  
`enum class ELoadResult`  
_L566-571_
- L568 _public enumerator_ `Ok`
- L569 _public enumerator_ `Error`
- L570 _public enumerator_ `Canceled`

#### struct `FElectraProtronPlayer::FImpl::FLoaderThread::FSampleRange`  
`struct FSampleRange`  
_L576-584_
- L578 _public member_ `TRangeSet<FTimespan> TimeRanges;`
- L579 _public member_ `TRangeSet<uint32> SampleRanges;`
- L580 _public member_ `int32 NumSamplesAfter = 0;`
- L581 _public member_ `int32 NumSamplesBefore = 0;`
- L582 _public member_ `int32 NumRemainingToLoadAfter = 0;`
- L583 _public member_ `int32 NumRemainingToLoadBefore = 0;`

#### class `FElectraProtronPlayer::FImpl::FDecoderThread`  
`class FDecoderThread : public FRunnable`  
_L590-748_
- inherits: `FRunnable`
- L593 _public function_ `FDecoderThread(const FConfig& InConfig, int32 InCodecTypeIndex) : Config(InConfig), DecoderTypeIndex(InCodecTypeIndex)`
- L600 _public prototype_ `uint32 Run() override;` — Inherited from FRunnable
- L602 _public prototype_ `void StartThread(const FOpenParam& InParam, const TSharedPtr<FSharedPlayParams, ESPMode::ThreadSafe>& InSharedPlayParams);`
- L603 _public prototype_ `void StopThread();`
- L605 _public function_ `FString GetLastError()`
- L609 _public prototype_ `void SetRate(float InNewRate);` — Sets playback rate.
- L611 _public prototype_ `bool SetLooping(bool bInLooping);` — Whether or not to loop.
- L614 _public prototype_ `void SetPlaybackRange(TRange<FTimespan> InRange);` — Sets the active playback range.
- L617 _public prototype_ `bool HasReachedEnd();` — Did decoding reach the last sample (or first sample when going in reverse)?
- L620 _public prototype_ `void Pause();` — Pauses decoding. Used when switching buffers or setting a new position.
- L622 _public prototype_ `void Resume();` — Resumes decoding. Decoder starts in paused state and needs to be resumed after setting buffer and time.
- L624 _public prototype_ `void SetSampleBuffer(const FMP4TrackSampleBufferPtr& InTrackSampleBuffer, FGetSampleDlg InGetSampleDelegate);` — Set the buffer to get the samples to decode from.
- L625 _public prototype_ `void DisconnectSampleBuffer();`
- L627 _public prototype_ `bool IsPaused();`
- L628 _public prototype_ `void PauseForSeek();`
- L629 _public prototype_ `void ResumeAfterSeek();`
- L630 _public prototype_ `bool IsPausedForSeek();`
- L631 _public prototype_ `void SetTime(FTimespan InTime, int32 InSeqIdx, TOptional<int32> InLoopIdx);`
- L632 _public prototype_ `void SetEstimatedPlaybackTime(FTimespan InTime);`
- L633 _public prototype_ `FTimespan GetEstimatedPlaybackTime();`
- L635 _public prototype_ `void Flush(const TSharedPtr<FMediaEvent, ESPMode::ThreadSafe>& InFlushedSignal);`
- L638 _private prototype_ `void UpdateTrackSampleDurationMap();`
- L639 _private prototype_ `void HandlePlaybackRangeChanges();`
- L640 _private prototype_ `FTimespan ClampTimeIntoPlaybackRange(const FTimespan& InTime);`
- L641 _private prototype_ `void UpdateTrackIterator(const FTimespan& InForTime);`
- L642 _private prototype_ `void StepTrackIterator();`
- L643 _private prototype_ `bool CreateDecoder();`
- L644 _private prototype_ `void DestroyDecoder();`
- L645 _private prototype_ `void DecodeOneFrame();`
- L646 _private prototype_ `bool HandleOutputFrame();`
- L647 _private prototype_ `void FlushForEndOrLooping();`
- L648 _private prototype_ `void PerformFlush();`
- L685 _private member_ `const FConfig& Config;`
- L686 _private member_ `int32 DecoderTypeIndex;`
- L687 _private member_ `FRunnableThread* Thread = nullptr;`
- L688 _private member_ `FMediaEvent WorkSignal;`
- L689 _private member_ `bool bTerminate = false;`
- L690 _private member_ `FString LastErrorMessage;`
- L691 _private member_ `double MinLoopSleepTime = 0.0;`
- L693 _private member_ `FOpenParam Params;`
- L694 _private member_ `TSharedPtr<FSharedPlayParams, ESPMode::ThreadSafe> SharedPlayParams;`
- L695 _private member_ `TSharedPtr<FElectraProtronPlayer::FImpl::FMP4TrackSampleBuffer, ESPMode::ThreadSafe> TrackSampleBuffer;`
- L696 _private member_ `TSortedMap<FTimespan, FTimespan> SampleTimeToDurationMap;`
- L697 _private member_ `FGetSampleDlg GetSampleDelegate;`
- L698 _private member_ `FTrackIterator TrackIterator;`
- L699 _private member_ `FTrackIterator FirstRangeSampleIt;`
- L700 _private member_ `FTrackIterator LastRangeSampleIt;`
- L703 _private member_ `FCriticalSection TimeLock;`
- L704 _private member_ `FTimespan CurrentTime;`
- L705 _private member_ `TRange<FTimespan> PlaybackRange;`
- L706 _private member_ `float CurrentRate = 0.0f;`
- L707 _private member_ `float IntendedRate = 0.0f;`
- L708 _private member_ `float PlaybackDirection = 0.0f;`
- L709 _private member_ `bool bShouldLoop = false;`
- L710 _private member_ `bool bReachedEnd = false;`
- L711 _private member_ `volatile bool bIsPaused = true;`
- L712 _private member_ `volatile bool bPausedForSeek = false;`
- L714 _private member_ `TSharedPtr<FMediaEvent, ESPMode::ThreadSafe> FlushedSignal;`
- L715 _private member_ `volatile bool bFlushPending = false;`
- L716 _private member_ `volatile bool bIsDrainingAtEOS = false;`
- L718 _private member_ `FPendingBufferChange PendingBufferChange;`
- L720 _private member_ `FPendingPlayRange PendingPlayRangeChange;`
- L722 _private member_ `FPendingSeek PendingSeek;`
- L723 _private member_ `TOptional<FTimespan> SeekTimeToHandleTo;`
- L724 _private member_ `TOptional<FTimespan> SeekTimeToDecodeTo;`
- L725 _private member_ `int32 SeekTimeNumFramesDecoded = 0;`
- L726 _private member_ `int32 SeekTimeNumFramesSkipped = 0;`
- L728 _private member_ `TSharedPtr<IElectraDecoder, ESPMode::ThreadSafe> DecoderInstance;`
- L729 _private member_ `TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> DecoderBitstreamProcessor;`
- L731 _private member_ `TMap<FString, FVariant> CurrentCodecSpecificData;`
- L732 _private member_ `FElectraDecodersPlatformResources::IDecoderPlatformResource* DecoderPlatformResource = nullptr;`
- L733 _private member_ `TUniquePtr<FInDecoder> CurrentInputSample;`
- L734 _private member_ `TSharedPtr<IElectraDecoderOutput, ESPMode::ThreadSafe> CurrentDecoderOutput;`
- L735 _private member_ `TUniquePtr<FInDecoder> InputForCurrentDecoderOutput;`
- L736 _private member_ `TMap<uint64, TUniquePtr<FInDecoder>> InDecoderInput;`
- L737 _private member_ `TOptional<Electra::MPEG::FColorimetryHelper> CurrentColorimetry;`
- L738 _private member_ `TOptional<Electra::MPEG::FHDRHelper> CurrentHDR;`
- L739 _private member_ `Electra::FAudioChannelMapper AudioChannelMapper;`
- L741 _private member_ `uint64 NextUserValue = 0;`
- L742 _private member_ `int32 SequenceIndex = 0;`
- L743 _private member_ `int32 LoopIndex = 0;`
- L744 _private member_ `bool bWaitForSyncSample = true;`
- L745 _private member_ `bool bWarnedMissingSyncSample = false;`
- L747 _private member_ `TSharedPtr<FElectraTextureSamplePool, ESPMode::ThreadSafe> VideoDecoderOutputPool;`

#### struct `FElectraProtronPlayer::FImpl::FDecoderThread::FInDecoder`  
`struct FInDecoder`  
_L650-659_
- L652 _public member_ `TMap<FString, FVariant> CSDOptions;`
- L653 _public member_ `IElectraDecoder::FInputAccessUnit DecAU;`
- L654 _public member_ `TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe> BSI;`
- L655 _public member_ `FMP4SamplePtr Sample;`
- L656 _public member_ `TArray<uint8> DataCopy;`
- L657 _public member_ `int32 SequenceIndex = 0;`
- L658 _public member_ `int32 LoopIndex = 0;`

#### struct `FElectraProtronPlayer::FImpl::FDecoderThread::FPendingBufferChange`  
`struct FPendingBufferChange`  
_L661-667_
- L663 _public member_ `FCriticalSection Lock;`
- L664 _public member_ `TSharedPtr<FMP4TrackSampleBuffer, ESPMode::ThreadSafe> NewTrackSampleBuffer;`
- L665 _public member_ `FGetSampleDlg NewGetSampleDelegate;`
- L666 _public member_ `bool bIsSet = false;`

#### struct `FElectraProtronPlayer::FImpl::FDecoderThread::FPendingSeek`  
`struct FPendingSeek`  
_L669-676_
- L671 _public member_ `FCriticalSection Lock;`
- L672 _public member_ `FTimespan NewTime;`
- L673 _public member_ `int32 NewSeqIdx = 0;`
- L674 _public member_ `TOptional<int32> NewLoopIdx;`
- L675 _public member_ `bool bIsSet = false;`

#### struct `FElectraProtronPlayer::FImpl::FDecoderThread::FPendingPlayRange`  
`struct FPendingPlayRange`  
_L678-683_
- L680 _public member_ `FCriticalSection Lock;`
- L681 _public member_ `TRange<FTimespan> NewRange;`
- L682 _public member_ `bool bIsSet = false;`

#### Free symbols / members of external scopes

- L254 _delegate_ `DECLARE_DELEGATE_OneParam(FCompletionDelegate, ImplPointer);`
- L501 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FMP4SamplePtr, FGetSampleDlg, FMP4TrackSampleBufferPtr , const FTrackIterator& , int32 );`

### `Plugins/Media/ElectraPlayer/Source/ElectraProtron/Public/IElectraProtronModule.h` (Public)


#### class `IElectraProtronModule`  
`class IElectraProtronModule : public IModuleInterface`  
_L14-31_
- inherits: `IModuleInterface`
- desc: Interface for the AndroidMedia module.
- L25 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Create a media player. @param EventSink The object that receives media events from the player. @return A new media player, or nullptr if a player couldn't be created.
- L30 _public prototype_ `virtual ~IElectraProtronModule() = default;` — Virtual destructor.
