# Plugins / WmfMedia

- module root: `Plugins/Media/WmfMedia/Source/WmfMedia`
- headers: 23; symbols: 693
- symbol kinds: class=32, delegate=3, enum=5, enumerator=22, function=103, macro=3, member=194, namespace=1, prototype=306, struct=10, typedef=2, variable=12
- DynamicallyLoadedModuleNames: Media
- PrivateDependencyModuleNames: Core, CoreUObject, D3D11RHI, Engine, HeadMountedDisplay, MediaUtils, Projects, RHI, RenderCore
- PrivateIncludePathModuleNames: Media
- PublicDependencyModuleNames: WmfMediaFactory

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Player/WmfMediaAudioSample.h` (Private)


#### class `FWmfMediaAudioSample`  
`class FWmfMediaAudioSample : public IMediaAudioSample , public IMediaPoolable`  
_L17-123_
- inherits: `IMediaAudioSample,IMediaPoolable`
- desc: Implements a media audio sample for WmfMedia.
- L24 _public function_ `FWmfMediaAudioSample() : Channels(0) , Duration(FTimespan::Zero()) , SampleRate(0) , Time(FTimespan::Zero(), 0)` — Default constructor.
- L32 _public prototype_ `virtual ~FWmfMediaAudioSample() = default;` — Virtual destructor.
- L44 _public function_ `bool Initialize( const uint8* InBuffer, uint32 InSize, uint32 InChannels, uint32 InSampleRate, FMediaTimeStamp InTime, FTimespan InDuration)` — Initialize the sample. @param InBuffer The sample's data buffer. @param InSize The size of the sample buffer (in bytes). @param InTime The sample time (relative to presentation clock). @param InDuration The duration for which the sample is valid.
- L72 _public function_ `virtual const void* GetBuffer() override`
- L77 _public function_ `virtual uint32 GetChannels() const override`
- L82 _public function_ `virtual FTimespan GetDuration() const override`
- L87 _public function_ `virtual EMediaAudioSampleFormat GetFormat() const override`
- L92 _public function_ `virtual uint32 GetFrames() const override`
- L97 _public function_ `virtual uint32 GetSampleRate() const override`
- L102 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L110 _private member_ `TArray<uint8> Buffer;` — The sample's data buffer.
- L113 _private member_ `uint32 Channels;` — Number of audio channels.
- L116 _private member_ `FTimespan Duration;` — The duration for which the sample is valid.
- L119 _private member_ `uint32 SampleRate;` — Audio sample rate (in samples per second).
- L122 _private member_ `FMediaTimeStamp Time;` — Presentation time for which the sample was generated.

#### class `FWmfMediaAudioSamplePool`  
`class FWmfMediaAudioSamplePool : public TMediaObjectPool<FWmfMediaAudioSample>`  
_L127-127_
- inherits: `TMediaObjectPool<FWmfMediaAudioSample>`
- desc: Implements a pool for WMF audio sample objects.

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Player/WmfMediaBinarySample.h` (Private)


#### class `FWmfMediaBinarySample`  
`class FWmfMediaBinarySample : public IMediaBinarySample`  
_L15-93_
- inherits: `IMediaBinarySample`
- desc: Implements a media binary data sample for WmfMedia.
- L21 _public function_ `FWmfMediaBinarySample() : Duration(FTimespan::Zero()) , Time(FTimespan::Zero())` — Default constructor.
- L27 _public prototype_ `virtual ~FWmfMediaBinarySample() = default;` — Virtual destructor.
- L39 _public function_ `bool Initialize( const void* InBuffer, uint32 InSize, FMediaTimeStamp InTime, FTimespan InDuration)` — Initialize the sample. @param InBuffer The sample's data buffer. @param InSize Size of the buffer. @param InTime The sample time (relative to presentation clock). @param InDuration The duration for which the sample is valid.
- L63 _public function_ `virtual const void* GetData() override`
- L68 _public function_ `virtual FTimespan GetDuration() const override`
- L73 _public function_ `virtual uint32 GetSize() const override`
- L78 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L86 _private member_ `TArray<uint8> Buffer;` — The sample's data buffer.
- L89 _private member_ `FTimespan Duration;` — Duration for which the sample is valid.
- L92 _private member_ `FMediaTimeStamp Time;` — Presentation time for which the sample was generated.

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Player/WmfMediaOverlaySample.h` (Private)


#### class `FWmfMediaOverlaySample`  
`class FWmfMediaOverlaySample : public IMediaOverlaySample`  
_L15-120_
- inherits: `IMediaOverlaySample`
- desc: Implements an overlay text sample for WmfMedia.
- L21 _public function_ `FWmfMediaOverlaySample() : Duration(FTimespan::Zero()) , Time(FTimespan::Zero())` — Default constructor.
- L27 _public prototype_ `virtual ~FWmfMediaOverlaySample() = default;` — Virtual destructor.
- L38 _public function_ `bool Initialize( const char* InBuffer, FMediaTimeStamp InTime, FTimespan InDuration)` — Initialize the sample. @param InBuffer The sample's data buffer. @param InTime The sample time (relative to presentation clock). @param InDuration The duration for which the sample is valid.
- L85 _public function_ `virtual FTimespan GetDuration() const override`
- L90 _public function_ `virtual TOptional<FVector2D> GetPosition() const override`
- L95 _public function_ `virtual FText GetText() const override`
- L100 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L105 _public function_ `virtual EMediaOverlaySampleType GetType() const override`
- L113 _private member_ `FTimespan Duration;` — The duration for which the sample is valid.
- L116 _private member_ `FText Text;` — The overlay text.
- L119 _private member_ `FMediaTimeStamp Time;` — Presentation time for which the sample was generated.

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Player/WmfMediaPlayer.h` (Private)


#### class `FWmfMediaPlayer`  
`class FWmfMediaPlayer : public IMediaPlayer , protected IMediaCache , protected IMediaView`  
_L26-97_
- inherits: `IMediaPlayer,IMediaCache,IMediaView`
- desc: Implements a media player using the Windows Media Foundation framework.
- L38 _public prototype_ `FWmfMediaPlayer(IMediaEventSink& InEventSink);` — Create and initialize a new instance. @param InEventSink The object that receives media events from this player.
- L41 _public prototype_ `virtual ~FWmfMediaPlayer();` — Virtual destructor.
- L47 _public prototype_ `virtual void Close() override;`
- L48 _public prototype_ `virtual IMediaCache& GetCache() override;`
- L49 _public prototype_ `virtual IMediaControls& GetControls() override;`
- L50 _public prototype_ `virtual FString GetInfo() const override;`
- L51 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L52 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L53 _public prototype_ `virtual FString GetStats() const override;`
- L54 _public prototype_ `virtual IMediaTracks& GetTracks() override;`
- L55 _public prototype_ `virtual FString GetUrl() const override;`
- L56 _public prototype_ `virtual IMediaView& GetView() override;`
- L57 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L58 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options, const FMediaPlayerOptions* PlayerOptions) override;`
- L59 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) override;`
- L61 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L63 _public prototype_ `virtual bool FlushOnSeekStarted() const override;`
- L64 _public prototype_ `virtual bool FlushOnSeekCompleted() const override;`
- L65 _public prototype_ `virtual bool GetPlayerFeatureFlag(EFeatureFlag flag) const override;`
- L77 _protected prototype_ `bool InitializePlayer(const TSharedPtr<FArchive, ESPMode::ThreadSafe>& Archive, const FString& Url, bool Precache, const FMediaPlayerOptions* PlayerOptions);` — Initialize the native AvPlayer instance. @param Archive The archive being used as a media source (optional). @param Url The media URL being opened. @param Precache Whether to precache media into RAM if InURL is a local file. @return true on success, false otherwise.
- L81 _private prototype_ `void Tick();` — Tick the player.
- L84 _private member_ `FTimespan Duration;` — The duration of the currently loaded media.
- L87 _private member_ `IMediaEventSink& EventSink;` — The media event handler.
- L90 _private member_ `FString MediaUrl;` — The URL of the currently opened media.
- L93 _private member_ `TComPtr<FWmfMediaSession> Session;` — Asynchronous callback object for the media session.
- L96 _private member_ `TSharedPtr<FWmfMediaTracks, ESPMode::ThreadSafe> Tracks;` — Media streams collection.

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Player/WmfMediaTextureSample.h` (Private)


#### class `FWmfMediaTextureSample`  
`class FWmfMediaTextureSample : public IMediaTextureSample , public IMediaPoolable`  
_L17-230_
- inherits: `IMediaTextureSample,IMediaPoolable`
- desc: Texture sample generated by WmfMedia player.
- L24 _public function_ `FWmfMediaTextureSample() : Dim(FIntPoint::ZeroValue) , Duration(FTimespan::Zero()) , OutputDim(FIntPoint::ZeroValue) , SampleFormat(EMediaTextureSampleFormat::Undefined) , Time(FTimespan::Zero()) , bIsBufferExternal(false) , Stride(0)` — Default constructor.
- L35 _public prototype_ `virtual ~FWmfMediaTextureSample() = default;` — Virtual destructor.
- L51 _public function_ `bool Initialize( const void* InBuffer, uint32 InSize, const FIntPoint& InDim, const FIntPoint& InOutputDim, EMediaTextureSampleFormat InSampleFormat, uint32 InStride, FMediaTimeStamp InTime, FTimespan InDuration)` — Initialize the sample. @param InBuffer The sample's data buffer. @param InSize Size of the buffer. @param InDim The sample buffer's width and height (in pixels). @param InOutputDim The sample's output width and height (in pixels). @param InSampleFormat The sample format. @param InStride Number of bytes per pixel row. @param InTime The sample time (relative to presentation clock). @param InDuration The duration for which the sample is valid.
- L97 _public function_ `bool InitializeExternal( TArray<uint8>* InBuffer, const FIntPoint& InDim, const FIntPoint& InOutputDim, EMediaTextureSampleFormat InSampleFormat, uint32 InStride, FMediaTimeStamp InTime, FTimespan InDuration)` — Initialize the sample. Use this when we are using external buffers. This will move the data out of InBuffer instead of copying it. @param InBuffer The sample's data buffer. @param InDim The sample buffer's width and height (in pixels). @param InOutputDim The sample's output width and height (in pixels). @param InSampleFormat The sample format. @param InStride Number of bytes per pixel row. @param InTime The sample time (relative to presentation clock). @param InDuration The duration for which the sample is valid.
- L135 _public function_ `bool IsBufferExternal() const` — See if we are using external buffers. @return True if so.
- L141 _public function_ `virtual const void* GetBuffer() override`
- L146 _public function_ `virtual FIntPoint GetDim() const override`
- L151 _public function_ `virtual FTimespan GetDuration() const override`
- L156 _public function_ `virtual EMediaTextureSampleFormat GetFormat() const override`
- L161 _public function_ `virtual FIntPoint GetOutputDim() const override`
- L166 _public function_ `virtual uint32 GetStride() const override`
- L172 _public function_ `virtual FRHITexture* GetTexture() const override`
- L178 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L183 _public function_ `virtual bool IsCacheable() const override`
- L188 _public function_ `virtual bool IsOutputSrgb() const override`
- L193 _public function_ `virtual void ShutdownPoolable() override`
- L205 _protected member_ `FIntPoint Dim;` — Width and height of the texture sample.
- L208 _protected member_ `FTimespan Duration;` — Duration for which the sample is valid.
- L211 _protected member_ `FIntPoint OutputDim;` — Width and height of the output.
- L214 _protected member_ `EMediaTextureSampleFormat SampleFormat;` — The sample format.
- L217 _protected member_ `FMediaTimeStamp Time;` — Presentation for which the sample was generated.
- L220 _protected member_ `bool bIsBufferExternal;` — If true, then Buffer is from WmfMediaDecoder and needs to be returned to it.
- L225 _private member_ `TArray<uint8> Buffer;` — The sample's data buffer.
- L228 _private member_ `uint32 Stride;` — Number of bytes per pixel row.

#### class `FWmfMediaTextureSamplePool`  
`class FWmfMediaTextureSamplePool : public TMediaObjectPool<FWmfMediaTextureSample>`  
_L234-234_
- inherits: `TMediaObjectPool<FWmfMediaTextureSample>`
- desc: Implements a pool for WMF texture samples.

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Player/WmfMediaTracks.h` (Private)


#### class `FWmfMediaTracks`  
`class FWmfMediaTracks : public IMediaSamples , public IMediaTracks`  
_L45-418_
- inherits: `IMediaSamples,IMediaTracks`
- desc: Track collection for Windows Media Foundation based media players.
- L96 _public prototype_ `FWmfMediaTracks();` — Default constructor.
- L99 _public prototype_ `virtual ~FWmfMediaTracks();` — Virtual destructor.
- L108 _public prototype_ `void AppendStats(FString& OutStats) const;` — Append track statistics information to the given string. @param OutStats The string to append the statistics to.
- L115 _public prototype_ `void ClearFlags();` — Clear the streams flags. @see GetFlags
- L122 _public prototype_ `TComPtr<IMFTopology> CreateTopology();` — Create the playback topology for the current track selection. @return The new topology.
- L130 _public prototype_ `FTimespan GetDuration() const;` — Get the total duration of the current media source. @return Media duration. @see GetInfo, GetSamples, Initialize
- L139 _public prototype_ `void GetFlags(bool& OutMediaSourceChanged, bool& OutSelectionChanged) const;` — Get the current flags. @param OutMediaSourceChanged Will indicate whether the media source changed. @param OutSelectionChanged Will indicate whether the track selection changed. @see ClearFlags
- L147 _public function_ `const FString& GetInfo() const` — Get the information string for the currently loaded media source. @return Info string. @see GetDuration, GetSamples
- L159 _public prototype_ `void Initialize(IMFMediaSource* InMediaSource, const FString& Url, const FMediaPlayerOptions* PlayerOptions);` — Initialize the track collection. @param InMediaSource The media source object. @param Url The media source URL. @see IsInitialized, Shutdown
- L166 _public prototype_ `void ReInitialize();` — Reinitialize the track collection @see IsInitialized, Shutdown
- L174 _public function_ `bool IsInitialized() const` — Whether this object has been initialized. @return true if initialized, false otherwise. @see Initialize, Shutdown
- L184 _public prototype_ `void Shutdown();` — Shut down the track collection. @see Initialize, IsInitialized
- L191 _public prototype_ `void SetSessionState(EMediaState InState);` — Call this to pass on the session state to us. @param InState State of session.
- L198 _public prototype_ `void SeekStarted(const FTimespan& InTime, int32 InNewSequenceIndex);` — Notify track of triggered seek
- L203 _public prototype_ `void LoopStarted(float UnpausedSessionRate);` — Notify track of triggered loop
- L205 _public function_ `void SetSession(FWmfMediaSession* InSession)`
- L210 _public prototype_ `void SessionEnded();`
- L212 _public prototype_ `void RequestMoreVideoDataFromStreamSink();`
- L214 _public prototype_ `bool ExecuteOnceMediaStreamSinkHasNoPendingRequests(TFunction<void()>&& ExecuteOnIdle);`
- L220 _public function_ `virtual bool FetchAudio(TRange<FTimespan> TimeRange, TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& OutSample) override`
- L221 _public function_ `virtual bool FetchCaption(TRange<FTimespan> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample) override`
- L222 _public function_ `virtual bool FetchMetadata(TRange<FTimespan> TimeRange, TSharedPtr<IMediaBinarySample, ESPMode::ThreadSafe>& OutSample) override`
- L223 _public function_ `virtual bool FetchVideo(TRange<FTimespan> TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample) override`
- L225 _public prototype_ `virtual bool FetchAudio(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& OutSample) override;`
- L226 _public prototype_ `virtual bool FetchCaption(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample) override;`
- L227 _public prototype_ `virtual bool FetchMetadata(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaBinarySample, ESPMode::ThreadSafe>& OutSample) override;`
- L228 _public prototype_ `virtual bool FetchVideo(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample) override;`
- L230 _public prototype_ `virtual void FlushSamples() override;`
- L232 _public prototype_ `virtual EFetchBestSampleResult FetchBestVideoSampleForTimeRange(const TRange<FMediaTimeStamp>& TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample, bool bReverse, bool bConsistentResult) override;`
- L233 _public prototype_ `virtual void SetMinExpectedNextSequenceIndex(TOptional<int32> InNextSequenceIndex) override;`
- L235 _public prototype_ `virtual bool DiscardVideoSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse) override;`
- L236 _public prototype_ `virtual bool DiscardAudioSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse) override;`
- L237 _public prototype_ `virtual bool DiscardCaptionSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse) override;`
- L238 _public prototype_ `virtual bool DiscardMetadataSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse) override;`
- L239 _public prototype_ `virtual bool PeekVideoSampleTime(FMediaTimeStamp & TimeStamp) override;`
- L245 _public prototype_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const override;`
- L246 _public prototype_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const override;`
- L247 _public prototype_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L248 _public prototype_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override;`
- L249 _public prototype_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L250 _public prototype_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L251 _public prototype_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L252 _public prototype_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L253 _public prototype_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L254 _public prototype_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override;`
- L255 _public prototype_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) override;`
- L256 _public prototype_ `virtual bool SetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex, float FrameRate) override;`
- L269 _protected prototype_ `bool AddStreamToTracks(uint32 StreamIndex, bool IsVideoDevice, FString& OutInfo);` — Add the specified stream to the track collection. @param StreamIndex The index of the stream to add. @param OutInfo Will contain appended debug information. @param IsVideoDevice Whether the stream belongs to a video capture device. @return true on success, false otherwise. @see AddTrackToTopology
- L279 _protected prototype_ `bool AddTrackToTopology(const FTrack& Track, IMFTopology& Topology);` — Add the given track to the specified playback topology. @param Track The track to add. @param Topology The playback topology. @return true on success, false otherwise. @see AddStreamToTracks
- L291 _private prototype_ `const FFormat* GetAudioFormat(int32 TrackIndex, int32 FormatIndex) const;` — Get the specified audio format. @param TrackIndex Index of the audio track that contains the format. @param FormatIndex Index of the format to return. @return Pointer to format, or nullptr if not found. @see GetVideoFormat
- L300 _private prototype_ `const FTrack* GetTrack(EMediaTrackType TrackType, int32 TrackIndex) const;` — Get the specified track information. @param TrackType The type of track. @param TrackIndex Index of the track to return. @return Pointer to track, or nullptr if not found.
- L310 _private prototype_ `const FFormat* GetVideoFormat(int32 TrackIndex, int32 FormatIndex) const;` — Get the specified video format. @param TrackIndex Index of the video track that contains the format. @param FormatIndex Index of the format to return. @return Pointer to format, or nullptr if not found. @see GetAudioFormat
- L315 _private prototype_ `void HandleMediaSamplerClock(EWmfMediaSamplerClockEvent Event, EMediaTrackType TrackType);` — Callback for handling media sampler pauses.
- L318 _private prototype_ `void HandleMediaSamplerAudioSample(const uint8* Buffer, uint32 Size, FTimespan Duration, FTimespan Time);` — Callback for handling new samples from the streams' media sample buffers.
- L321 _private prototype_ `void HandleMediaSamplerCaptionSample(const uint8* Buffer, uint32 Size, FTimespan Duration, FTimespan Time);` — Callback for handling new caption samples.
- L324 _private prototype_ `void HandleMediaSamplerMetadataSample(const uint8* Buffer, uint32 Size, FTimespan Duration, FTimespan Time);` — Callback for handling new metadata samples.
- L327 _private prototype_ `void HandleMediaSamplerVideoSample(const uint8* Buffer, uint32 Size, FTimespan Duration, FTimespan Time);` — Callback for handling new video samples.
- L330 _private prototype_ `FMediaTimeStamp AdjustTimeStamp(FTimespan Time, EMediaTrackType TrackType);` — Make sure sequence index is up to date and combine with given timestamp
- L333 _private prototype_ `bool IsSampleStillDesired();` — Check if the current sequence index to apply is still the one that is wanted.
- L337 _private member_ `FWmfMediaAudioSamplePool* AudioSamplePool;` — Audio sample object pool.
- L340 _private member_ `TMediaSampleQueue<IMediaAudioSample> AudioSampleQueue;` — Audio sample queue.
- L343 _private member_ `TArray<FTrack> AudioTracks;` — The available audio tracks.
- L346 _private member_ `TMediaSampleQueue<IMediaOverlaySample> CaptionSampleQueue;` — Overlay sample queue.
- L349 _private member_ `TArray<FTrack> CaptionTracks;` — The available caption tracks.
- L352 _private member_ `mutable FCriticalSection CriticalSection;` — Synchronizes write access to track arrays, selections & sinks.
- L355 _private member_ `FString Info;` — Media information string.
- L358 _private member_ `FString SourceUrl;` — The initial media url.
- L361 _private member_ `TComPtr<IMFMediaSource> MediaSource;` — The currently opened media.
- L364 _private member_ `TComPtr<FWmfMediaStreamSink> MediaStreamSink;` — Hardware Acccelerated Stream Sink
- L367 _private member_ `bool MediaSourceChanged;` — Whether the media source has changed.
- L370 _private member_ `TMediaSampleQueue<IMediaBinarySample> MetadataSampleQueue;` — Metadata sample queue.
- L373 _private member_ `TArray<FTrack> MetadataTracks;` — The available metadata tracks.
- L376 _private member_ `TComPtr<IMFPresentationDescriptor> PresentationDescriptor;` — The presentation descriptor of the currently opened media.
- L379 _private member_ `int32 SelectedAudioTrack;` — Index of the selected audio track.
- L382 _private member_ `int32 SelectedCaptionTrack;` — Index of the selected caption track.
- L385 _private member_ `int32 SelectedMetadataTrack;` — Index of the selected binary track.
- L388 _private member_ `int32 SelectedVideoTrack;` — Index of the selected video track.
- L391 _private member_ `bool SelectionChanged;` — Whether the track selection changed.
- L394 _private member_ `bool bVideoTrackRequestedHardwareAcceleration;` — Flag to display if the topology node has requested hardware acceleration.
- L397 _private member_ `FWmfMediaTextureSamplePool* VideoSamplePool;` — Video sample object pool.
- L398 _private member_ `TSharedPtr<FWmfMediaHardwareVideoDecodingTextureSamplePool> VideoHardwareVideoDecodingSamplePool;`
- L401 _private member_ `TMediaSampleQueue<IMediaTextureSample> VideoSampleQueue;` — Video sample queue.
- L404 _private member_ `TArray<FTrack> VideoTracks;` — The available video tracks.
- L407 _private member_ `FTimespan CachedDuration;` — Caches the value from GetDuration.
- L410 _private member_ `EMediaState SessionState;` — Current state of the session.
- L412 _private member_ `FWmfMediaSession* Session;`
- L415 _private member_ `TOptional<int32> NextMinSequenceIndex;` — SequenceIndex tracking
- L416 _private member_ `int32 SeekIndex;`
- L417 _private member_ `int32 LoopIndex;`

#### struct `FWmfMediaTracks::FFormat`  
`struct FFormat`  
_L50-76_
- desc: Track format.
- L52 _public member_ `TComPtr<IMFMediaType> InputType;`
- L53 _public member_ `TComPtr<IMFMediaType> OutputType;`
- L54 _public member_ `FString TypeName;`
- L62 _public member_ `Audio;`
- L75 _public member_ `Video;`

#### struct `FWmfMediaTracks::FFormat::(anonymous)`  
``  
_L57-61_

#### struct `FWmfMediaTracks::FFormat::(anonymous)`  
``  
_L65-74_

#### struct `FWmfMediaTracks::FTrack`  
`struct FTrack`  
_L80-91_
- desc: Track information.
- L82 _public member_ `TComPtr<IMFStreamDescriptor> Descriptor;`
- L83 _public member_ `FText DisplayName;`
- L84 _public member_ `TArray<FFormat> Formats;`
- L85 _public member_ `TComPtr<IMFMediaTypeHandler> Handler;`
- L86 _public member_ `FString Language;`
- L87 _public member_ `FString Name;`
- L88 _public member_ `bool Protected;`
- L89 _public member_ `int32 SelectedFormat;`
- L90 _public member_ `DWORD StreamIndex;`

#### Free symbols / members of external scopes

- L58 _member_ `uint32 BitsPerSample;` (scope `FWmfMediaTracks::FFormat::__anonb3701c960108`)
- L59 _member_ `uint32 NumChannels;` (scope `FWmfMediaTracks::FFormat::__anonb3701c960108`)
- L60 _member_ `uint32 SampleRate;` (scope `FWmfMediaTracks::FFormat::__anonb3701c960108`)
- L66 _member_ `uint32 BitRate;` (scope `FWmfMediaTracks::FFormat::__anonb3701c960208`)
- L67 _member_ `FIntPoint BufferDim;` (scope `FWmfMediaTracks::FFormat::__anonb3701c960208`)
- L68 _member_ `uint32 BufferStride;` (scope `FWmfMediaTracks::FFormat::__anonb3701c960208`)
- L69 _member_ `GUID FormatType;` (scope `FWmfMediaTracks::FFormat::__anonb3701c960208`)
- L70 _member_ `float FrameRate;` (scope `FWmfMediaTracks::FFormat::__anonb3701c960208`)
- L71 _member_ `TRange<float> FrameRates;` (scope `FWmfMediaTracks::FFormat::__anonb3701c960208`)
- L72 _member_ `FIntPoint OutputDim;` (scope `FWmfMediaTracks::FFormat::__anonb3701c960208`)
- L73 _member_ `EMediaTextureSampleFormat SampleFormat;` (scope `FWmfMediaTracks::FFormat::__anonb3701c960208`)

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaByteStream.h` (Private)


#### class `FWmfMediaByteStream`  
`class FWmfMediaByteStream : public IMFAsyncCallback , public IMFByteStream`  
_L15-76_
- inherits: `IMFAsyncCallback,IMFByteStream`
- desc: Implements a wrapper for media source data that is played from memory.
- L26 _public prototype_ `FWmfMediaByteStream(const TSharedRef<FArchive, ESPMode::ThreadSafe>& InArchive);` — Creates and initializes a new instance from the specified buffer. @param InArchive The archive to stream from.
- L32 _public prototype_ `STDMETHODIMP_(ULONG) AddRef();`
- L33 _public prototype_ `STDMETHODIMP GetParameters(unsigned long*, unsigned long*);`
- L34 _public prototype_ `STDMETHODIMP Invoke(IMFAsyncResult* AsyncResult);`
- L35 _public prototype_ `STDMETHODIMP QueryInterface(REFIID RefID, void** Object);`
- L36 _public prototype_ `STDMETHODIMP_(ULONG) Release();`
- L42 _public prototype_ `STDMETHODIMP BeginRead(BYTE* pb, ULONG cb, IMFAsyncCallback* pCallback, IUnknown* punkState);`
- L43 _public prototype_ `STDMETHODIMP BeginWrite(const BYTE* pb, ULONG cb, IMFAsyncCallback* pCallback, IUnknown* punkState);`
- L44 _public prototype_ `STDMETHODIMP Close();`
- L45 _public prototype_ `STDMETHODIMP EndRead(IMFAsyncResult* pResult, ULONG* pcbRead);`
- L46 _public prototype_ `STDMETHODIMP EndWrite(IMFAsyncResult* pResult, ULONG* pcbWritten);`
- L47 _public prototype_ `STDMETHODIMP Flush();`
- L48 _public prototype_ `STDMETHODIMP GetCapabilities(DWORD* pdwCapabilities);`
- L49 _public prototype_ `STDMETHODIMP GetCurrentPosition(QWORD* pqwPosition);`
- L50 _public prototype_ `STDMETHODIMP GetLength(QWORD* pqwLength);`
- L51 _public prototype_ `STDMETHODIMP IsEndOfStream(BOOL* pfEndOfStream);`
- L52 _public prototype_ `STDMETHODIMP Read(BYTE* pb, ULONG cb, ULONG* pcbRead);`
- L53 _public prototype_ `STDMETHODIMP Seek(MFBYTESTREAM_SEEK_ORIGIN SeekOrigin, LONGLONG qwSeekOffset, DWORD dwSeekFlags, QWORD* pqwCurrentPosition);`
- L54 _public prototype_ `STDMETHODIMP SetLength(QWORD qwLength);`
- L55 _public prototype_ `STDMETHODIMP SetCurrentPosition(QWORD qwPosition);`
- L56 _public prototype_ `STDMETHODIMP Write(const BYTE* pb, ULONG cb, ULONG* pcbWritten);`
- L61 _private prototype_ `virtual ~FWmfMediaByteStream();` — Hidden destructor.
- L66 _private member_ `bool AsyncReadInProgress;` — Whether the stream is currently being read asynchronously.
- L69 _private member_ `TSharedRef<FArchive, ESPMode::ThreadSafe> Archive;` — Holds the archive to stream from.
- L72 _private member_ `mutable FCriticalSection CriticalSection;` — Critical section for locking access to this class.
- L75 _private member_ `int32 RefCount;` — Holds a reference counter for this instance.

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaReadState.h` (Private)


#### class `FWmfMediaReadState`  
`class FWmfMediaReadState : public IUnknown`  
_L22-144_
- inherits: `IUnknown`
- desc: Implements the state information for asynchronous reads of byte buffer sources. The @see FWmfByteStream class uses this class to store the state for asynchronous read requests that are initiated with @see FWmfByteStream.BeginRead and completed with @see FWmfByteStream.EndRead
- L33 _public function_ `FWmfMediaReadState(BYTE* InReadBuffer, ULONG InReadBufferSize) : BytesRead(0) , ReadBuffer(InReadBuffer) , ReadBufferSize(InReadBufferSize) , RefCount(0)` — Creates and initializes a new instance. @param InReadBuffer The buffer that receives the read data. @param InReadBufferSize The size of the read buffer.
- L47 _public function_ `void AddBytesRead(uint64 BytesToAdd)` — Adds the specified number of bytes read. @param BytesToAdd The number of bytes to add.
- L57 _public function_ `BYTE* GetReadBuffer() const` — Gets a pointer to the buffer being read from. @return The buffer.
- L67 _public function_ `ULONG GetReadBufferSize() const` — Gets the size of the buffer being read from. @return The size of the buffer (in bytes).
- L77 _public function_ `uint64 GetBytesRead() const` — Gets the actual number of bytes read. @return Bytes read count.
- L91 _public function_ `STDMETHODIMP QueryInterface(REFIID RefID, void** Object)`
- L106 _public function_ `STDMETHODIMP_(ULONG) AddRef()`
- L111 _public function_ `STDMETHODIMP_(ULONG) Release()`
- L126 _private function_ `virtual ~FWmfMediaReadState()` — Hidden destructor (this class is reference counted).
- L134 _private member_ `uint64 BytesRead;` — Number of bytes read.
- L137 _private member_ `BYTE* ReadBuffer;` — The buffer that receives the read data.
- L140 _private member_ `ULONG ReadBufferSize;` — The size of the read buffer.
- L143 _private member_ `int32 RefCount;` — Holds a reference counter for this instance.

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaSampler.h` (Private)


#### enum `EWmfMediaSamplerClockEvent`  
`enum class EWmfMediaSamplerClockEvent`  
_L20-26_
- desc: Clock sink events.
- L22 _public enumerator_ `Paused`
- L23 _public enumerator_ `Restarted`
- L24 _public enumerator_ `Started`
- L25 _public enumerator_ `Stopped`

#### class `FWmfMediaSampler`  
`class FWmfMediaSampler : public IMFSampleGrabberSinkCallback`  
_L32-171_
- inherits: `IMFSampleGrabberSinkCallback`
- desc: Implements a callback object for the WMF sample grabber sink.
- L38 _public function_ `FWmfMediaSampler() : RefCount(0)` — Default constructor.
- L45 _public function_ `DECLARE_EVENT_OneParam(FWmfMediaSampler, FOnClock, EWmfMediaSamplerClockEvent ) FOnClock& OnClock()` — Get an event that gets fired when the sampler's presentation clock changed its state.
- L52 _public function_ `DECLARE_EVENT_FourParams(FWmfMediaSampler, FOnSample, const uint8* , uint32 , FTimespan , FTimespan ) FOnSample& OnSample()` — Get an event that gets fired when a new sample is ready (handler must be thread-safe).
- L62 _public function_ `STDMETHODIMP OnClockPause(MFTIME SystemTime)`
- L69 _public function_ `STDMETHODIMP OnClockRestart(MFTIME SystemTime)`
- L76 _public function_ `STDMETHODIMP OnClockSetRate(MFTIME SystemTime, float flRate)`
- L81 _public function_ `STDMETHODIMP OnClockStart(MFTIME SystemTime, LONGLONG llClockStartOffset)`
- L88 _public function_ `STDMETHODIMP OnClockStop(MFTIME SystemTime)`
- L95 _public function_ `STDMETHODIMP OnProcessSample(REFGUID MajorMediaType, DWORD SampleFlags, LONGLONG SampleTime, LONGLONG SampleDuration, const BYTE* SampleBuffer, DWORD SampleSize)`
- L102 _public function_ `STDMETHODIMP OnSetPresentationClock(IMFPresentationClock* Clock)`
- L107 _public function_ `STDMETHODIMP OnShutdown()`
- L116 _public function_ `STDMETHODIMP_(ULONG) AddRef()`
- L126 _public function_ `STDMETHODIMP QueryInterface(REFIID RefID, void** Object)`
- L141 _public function_ `STDMETHODIMP_(ULONG) Release()`
- L156 _private function_ `virtual ~FWmfMediaSampler()` — Hidden destructor (this class is reference counted).
- L164 _private member_ `FOnClock ClockEvent;` — Event that gets fired when the sampler's presentation clock changed state.
- L167 _private member_ `int32 RefCount;` — Holds a reference counter for this instance.
- L170 _private member_ `FOnSample SampleEvent;` — Event that gets fired when a new sample is ready.

#### Free symbols / members of external scopes

- L45 _delegate_ `DECLARE_EVENT_OneParam(FWmfMediaSampler, FOnClock, EWmfMediaSamplerClockEvent ) FOnClock& OnClock() { return ClockEvent; } DECLARE_EVENT_FourParams(FWmfMediaSampler, FOnSample, const uint8* , uint32 , FTimespan , FTimespan ) FOnSample& OnSample() { return SampleEvent; } public:` — Get an event that gets fired when the sampler's presentation clock changed its state.
- L52 _delegate_ `DECLARE_EVENT_FourParams(FWmfMediaSampler, FOnSample, const uint8* , uint32 , FTimespan , FTimespan ) FOnSample& OnSample() { return SampleEvent; } public:` — Get an event that gets fired when a new sample is ready (handler must be thread-safe).

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaSession.h` (Private)


#### class `FWmfMediaSession`  
`class FWmfMediaSession : public IMFAsyncCallback , public IMediaControls`  
_L36-383_
- inherits: `IMFAsyncCallback,IMediaControls`
- desc: Implements a media session that for handling asynchronous commands and callbacks. Many of the media playback features are asynchronous and do not take place immediately, such as seeking and playback rate changes. A media session may generate events during playback that are then handled by this class. Windows Media Foundation has a number of odd quirks and problems that require special handling, such as certain state changes not being allowed, and some calls causing occasional deadlocks. The added complexity in the implementation of this class is for working around those issues.
- L43 _public prototype_ `FWmfMediaSession();` — Default constructor.
- L53 _public function_ `DWORD GetCapabilities() const` — Gets the session capabilities. @return Capabilities bit mask. @see GetEvents
- L64 _public prototype_ `void GetEvents(TArray<EMediaEvent>& OutEvents);` — Gets all deferred player events. @param OutEvents Will contain the events. @see GetCapabilities
- L71 _public prototype_ `void SetTracks(TSharedPtr<FWmfMediaTracks, ESPMode::ThreadSafe> InTracks);` — Set which tracks object is being used by the player. @param InTracks Tracks object.
- L79 _public prototype_ `bool Initialize(bool LowLatency);` — Initialize the media session. @param LowLatency Whether to enable low latency processing. @see SetTopolgy, Shutdown
- L89 _public prototype_ `bool SetTopology(const TComPtr<IMFTopology>& InTopology, FTimespan InDuration);` — Set the playback topology to be used by this session. @param InTopology The topology to set. @param InDuration Total duration of the media being played. @return true on success, false otherwise. @see Initialize, Shutdown
- L96 _public prototype_ `void Shutdown();` — Close the media session. @see Initialize
- L102 _public prototype_ `virtual bool CanControl(EMediaControl Control) const override;`
- L103 _public prototype_ `virtual FTimespan GetDuration() const override;`
- L104 _public prototype_ `virtual float GetRate() const override;`
- L105 _public prototype_ `virtual EMediaState GetState() const override;`
- L106 _public prototype_ `virtual EMediaStatus GetStatus() const override;`
- L107 _public prototype_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const override;`
- L108 _public prototype_ `virtual FTimespan GetTime() const override;`
- L109 _public prototype_ `virtual bool IsLooping() const override;`
- L110 _public function_ `virtual bool Seek(const FTimespan& Time) override`
- L112 _public prototype_ `virtual bool Seek(const FTimespan& InNewTime, const FMediaSeekParams& InAdditionalParams) override;`
- L113 _public prototype_ `virtual bool SetLooping(bool Looping) override;`
- L114 _public prototype_ `virtual bool SetRate(float Rate) override;`
- L120 _public prototype_ `STDMETHODIMP_(ULONG) AddRef();`
- L121 _public prototype_ `STDMETHODIMP GetParameters(unsigned long* Flags, unsigned long* Queue);`
- L122 _public prototype_ `STDMETHODIMP Invoke(IMFAsyncResult* AsyncResult);`
- L123 _public prototype_ `STDMETHODIMP QueryInterface(REFIID RefID, void** Object);`
- L124 _public prototype_ `STDMETHODIMP_(ULONG) Release();`
- L127 _public prototype_ `void Flush();`
- L129 _public prototype_ `void RequestMoreVideoData();`
- L166 _public prototype_ `void EnqueueWorkItem(FWorkItem&& WorkItem);`
- L167 _public prototype_ `void JamWorkItem(FWorkItem&& WorkItem);`
- L222 _protected prototype_ `EWorkItemResult CommitRate(float Rate, FRateWorkItemState* State, MediaEventType EventType);` — Commit the specified play rate. The caller holds the lock to the critical section. @param Rate The play rate to commit. @see CommitTime, CommitTopology
- L232 _protected prototype_ `bool CommitTime(FTimespan Time, bool bIsSeek);` — Commit the specified play position. The caller holds the lock to the critical section. @param Time The play position to commit. @see CommitRate, CommitTopology
- L240 _protected prototype_ `EWorkItemResult CommitTopology(IMFTopology* Topology, FTopologyWorkItemState* State, MediaEventType EventType);` — Commit the given playback topology. @param Topology The topology to set. @see CommitRate, CommitTime
- L243 _protected prototype_ `void UpdateCharacteristics();` — Get the latest characteristics from the current media source.
- L245 _protected prototype_ `void ExecuteNextWorkItems(TComPtr<IMFMediaEvent> MediaEvent, MediaEventType EventType, HRESULT EventStatus);`
- L246 _protected prototype_ `void ResetWorkItemQueue();`
- L248 _protected prototype_ `void SetSessionRate(float Rate);`
- L253 _private prototype_ `void HandleError(HRESULT EventStatus);` — Callback for the MEError event.
- L256 _private prototype_ `void HandleSessionEnded();` — Callback for the MESessionEnded event.
- L258 _private prototype_ `void HandlePresentationEnded();`
- L261 _private prototype_ `void HandleSessionPaused(HRESULT EventStatus);` — Callback for the MESessionPaused event.
- L264 _private prototype_ `void HandleSessionRateChanged(HRESULT EventStatus, IMFMediaEvent& Event);` — Callback for the MESessionRateChanged event.
- L267 _private prototype_ `void HandleSessionStarted(HRESULT EventStatus);` — Callback for the MESessionStarted event.
- L270 _private prototype_ `void HandleSessionStopped(HRESULT EventStatus);` — Callback for the MESessionStopped event.
- L273 _private prototype_ `void HandleSessionTopologySet(HRESULT EventStatus, IMFMediaEvent& Event);` — Callback for the MESessionTopologySet event.
- L276 _private prototype_ `void HandleSessionTopologyStatus(HRESULT EventStatus, IMFMediaEvent& Event);` — Callback for the MESessionTopologyStatus event.
- L281 _private prototype_ `virtual ~FWmfMediaSession();` — Hidden destructor (this class is reference counted).
- L286 _private member_ `bool CanScrub;` — Whether the media session supports scrubbing.
- L289 _private member_ `DWORD Capabilities;` — The session's capabilities.
- L292 _private member_ `mutable FCriticalSection CriticalSection;` — Synchronizes write access to session state.
- L295 _private member_ `FTimespan CurrentDuration;` — The duration of the media.
- L298 _private member_ `TComPtr<IMFTopology> CurrentTopology;` — The full playback topology currently set on the media session.
- L301 _private member_ `TQueue<EMediaEvent> DeferredEvents;` — Media events to be forwarded to main thread.
- L304 _private member_ `TComPtr<IMFMediaSession> MediaSession;` — The media session that handles all playback.
- L307 _private member_ `FEvent* MediaSessionCloseEvent;` — MediaSession close event.
- L310 _private member_ `FTimespan LastTime;` — The last play head position before playback was stopped.
- L313 _private member_ `TComPtr<IMFPresentationClock> PresentationClock;` — The media session's clock.
- L316 _private member_ `TComPtr<IMFRateControl> RateControl;` — Optional interface for controlling playback rates.
- L319 _private member_ `TComPtr<IMFRateSupport> RateSupport;` — Optional interface for querying supported playback rates.
- L322 _private member_ `int32 RefCount;` — Holds a reference counter for this instance.
- L325 _private member_ `TOptional<float> RequestedRate;` — Deferred play rate change value.
- L328 _private member_ `TComPtr<IMFTopology> RequestedTopology;` — Deferred playback topology to set.
- L331 _private member_ `bool bIsRequestedTimeLoop;` — If true then RequestedTime is due to the video looping.
- L334 _private member_ `bool bIsRequestedTimeSeek;` — If true then RequestedTime is due to the video seeking.
- L336 _private member_ `float LastSetRate;`
- L339 _private member_ `float SessionRate;` — The session's internal playback rate (not necessarily the same as GetRate).
- L342 _private member_ `float UnpausedSessionRate;` — The session's last non-zero internal playback rate.
- L345 _private member_ `EMediaState SessionState;` — The session's current state (not necessarily the same as GetState).
- L348 _private member_ `bool ShouldLoop;` — Whether playback should loop to the beginning.
- L351 _private member_ `EMediaStatus Status;` — Current status flags.
- L354 _private member_ `bool bShuttingDown;` — Flag to signal shutdown in progress
- L357 _private member_ `TRangeSet<float> ThinnedRates;` — The thinned play rates that the current media session supports.
- L360 _private member_ `TRangeSet<float> UnthinnedRates;` — The unthinned play rates that the current media session supports.
- L363 _private member_ `TWeakPtr<FWmfMediaTracks, ESPMode::ThreadSafe> Tracks;` — Pointer to the tracks from the player.
- L366 _private member_ `bool bIsWaitingForEnd;` — True if we are waiting for the tracks to send out its last samples before we "end".
- L369 _private member_ `TOptional<int32> NextSequenceIndex;` — Next requested sequence index on a Seek() request.
- L372 _private member_ `bool bSeekActive;` — True if seek is logically in progress
- L375 _private member_ `TArray<FWorkItem> WorkItemQueue;` — Queue of work jobs for the player
- L378 _private member_ `FWorkItem CurrentWorkItem;` — The work item currently in progress (if valid)
- L381 _private member_ `int32 NumSeeksInWorkQueue;` — Number of seek wokr-items in the queue currently

#### enum `FWmfMediaSession::EWorkItemResult`  
`enum class EWorkItemResult`  
_L131-135_
- L133 _public enumerator_ `Done`
- L134 _public enumerator_ `RetryLater`

#### struct `FWmfMediaSession::FBaseWorkItemState`  
`struct FBaseWorkItemState`  
_L137-140_
- L139 _public prototype_ `virtual ~FBaseWorkItemState() = default;`

#### class `FWmfMediaSession::FWorkItem`  
`class FWorkItem`  
_L142-163_
- L145 _public typedef_ `typedef TFunction<EWorkItemResult(TComPtr<IMFMediaEvent> MediaEvent, MediaEventType EventType, HRESULT EventStatus, FBaseWorkItemState* BaseState)> FWorkLoadType;`
- L147 _public prototype_ `FWorkItem() = default;`
- L148 _public function_ `FWorkItem(FWorkLoadType&& InWorkLoad, TSharedPtr<FBaseWorkItemState, ESPMode::ThreadSafe> InState = nullptr) : WorkLoad(MoveTemp(InWorkLoad)), State(InState)`
- L150 _public member_ `FWorkLoadType WorkLoad;`
- L151 _public member_ `TSharedPtr<FBaseWorkItemState, ESPMode::ThreadSafe> State;`
- L153 _public function_ `bool IsValid() const`
- L158 _public function_ `void Reset()`

#### struct `FWmfMediaSession::FTopologyWorkItemState`  
`struct FTopologyWorkItemState : public FBaseWorkItemState`  
_L170-181_
- inherits: `FBaseWorkItemState`
- L180 _public member_ `EState State = EState::Begin;`

#### enum `FWmfMediaSession::FTopologyWorkItemState::EState`  
`enum class EState`  
_L172-178_
- L174 _public enumerator_ `Begin`
- L175 _public enumerator_ `Ready`
- L176 _public enumerator_ `ReadyNeedsRestart`
- L177 _public enumerator_ `WaitRestart`

#### struct `FWmfMediaSession::FRateWorkItemState`  
`struct FRateWorkItemState : public FBaseWorkItemState`  
_L183-201_
- inherits: `FBaseWorkItemState`
- L199 _public member_ `EState State = EState::Begin;`
- L200 _public member_ `FTimespan LastTime;`

#### enum `FWmfMediaSession::FRateWorkItemState::EState`  
`enum class EState`  
_L185-197_
- L187 _public enumerator_ `Begin`
- L188 _public enumerator_ `Ready`
- L189 _public enumerator_ `ReadyNeedsRestart`
- L190 _public enumerator_ `WaitForStopThenSetAndRestart`
- L191 _public enumerator_ `WaitForPauseThenSetAndRestart`
- L192 _public enumerator_ `WaitForSet`
- L193 _public enumerator_ `WaitForSetAndRestart`
- L194 _public enumerator_ `WaitForRestart`
- L195 _public enumerator_ `WaitForPause`
- L196 _public enumerator_ `WaitForStart`

#### struct `FWmfMediaSession::FTimeWorkItemState`  
`struct FTimeWorkItemState : public FBaseWorkItemState`  
_L203-212_
- inherits: `FBaseWorkItemState`
- L211 _public member_ `EState State = EState::Begin;`

#### enum `FWmfMediaSession::FTimeWorkItemState::EState`  
`enum class EState`  
_L205-209_
- L207 _public enumerator_ `Begin`
- L208 _public enumerator_ `WaitDone`

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaSink.h` (Private)


#### class `FWmfMediaSink`  
`class FWmfMediaSink : public IMFClockStateSink , public IMFGetService , public IMFMediaSink , public IMFRateSupport`  
_L20-115_
- inherits: `IMFClockStateSink,IMFGetService,IMFMediaSink,IMFRateSupport`
- desc: Implements a media sink object for the WMF pipeline.
- L29 _public prototype_ `FWmfMediaSink();` — Default constructor.
- L39 _public prototype_ `bool Initialize(TComPtr<FWmfMediaStreamSink> InStreamSink);` — Initialize this sink. @param InStreamSink The stream sink to use for the fixed stream. @return true on success, false otherwise.
- L45 _public prototype_ `STDMETHODIMP OnClockPause(MFTIME hnsSystemTime);`
- L46 _public prototype_ `STDMETHODIMP OnClockRestart(MFTIME hnsSystemTime);`
- L47 _public prototype_ `STDMETHODIMP OnClockSetRate(MFTIME hnsSystemTime, float flRate);`
- L48 _public prototype_ `STDMETHODIMP OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset);`
- L49 _public prototype_ `STDMETHODIMP OnClockStop(MFTIME hnsSystemTime);`
- L55 _public prototype_ `STDMETHODIMP GetService(__RPC__in REFGUID guidService, __RPC__in REFIID riid, __RPC__deref_out_opt LPVOID* ppvObject);`
- L61 _public prototype_ `STDMETHODIMP AddStreamSink(DWORD dwStreamSinkIdentifier, __RPC__in_opt IMFMediaType* pMediaType, __RPC__deref_out_opt IMFStreamSink** ppStreamSink);`
- L62 _public prototype_ `STDMETHODIMP GetCharacteristics(__RPC__out DWORD* pdwCharacteristics);`
- L63 _public prototype_ `STDMETHODIMP GetPresentationClock(__RPC__deref_out_opt IMFPresentationClock** ppPresentationClock);`
- L64 _public prototype_ `STDMETHODIMP GetStreamSinkById(DWORD dwIdentifier, __RPC__deref_out_opt IMFStreamSink** ppStreamSink);`
- L65 _public prototype_ `STDMETHODIMP GetStreamSinkByIndex(DWORD dwIndex, __RPC__deref_out_opt IMFStreamSink** ppStreamSink);`
- L66 _public prototype_ `STDMETHODIMP GetStreamSinkCount(__RPC__out DWORD* pcStreamSinkCount);`
- L67 _public prototype_ `STDMETHODIMP RemoveStreamSink(DWORD dwStreamSinkIdentifier);`
- L68 _public prototype_ `STDMETHODIMP SetPresentationClock(__RPC__in_opt IMFPresentationClock* pPresentationClock);`
- L69 _public prototype_ `STDMETHODIMP Shutdown();`
- L75 _public prototype_ `STDMETHODIMP GetFastestRate(MFRATE_DIRECTION eDirection, BOOL fThin, _Out_ float* pflRate);`
- L76 _public prototype_ `STDMETHODIMP GetSlowestRate(MFRATE_DIRECTION eDirection, BOOL fThin, _Out_ float* pflRate);`
- L77 _public prototype_ `STDMETHODIMP IsRateSupported(BOOL fThin, float flRate, __RPC__inout_opt float* pflNearestSupportedRate);`
- L83 _public prototype_ `STDMETHODIMP_(ULONG) AddRef();`
- L84 _public prototype_ `STDMETHODIMP QueryInterface(REFIID RefID, void** Object);`
- L85 _public prototype_ `STDMETHODIMP_(ULONG) Release();`
- L87 _public function_ `ID3D11DeviceContext* GetImmediateContext() const`
- L88 _public function_ `ID3D11Device* GetDevice() const`
- L93 _private prototype_ `virtual ~FWmfMediaSink();` — Hidden destructor (this class is reference counted).
- L95 _private prototype_ `bool CreateDXGIManagerAndDevice();`
- L100 _private member_ `FCriticalSection CriticalSection;` — Critical section for synchronizing access to this sink.
- L103 _private member_ `int32 RefCount;` — Holds a reference counter for this instance.
- L106 _private member_ `TComPtr<IMFPresentationClock> PresentationClock;` — The presentation clock used by this sink.
- L109 _private member_ `TComPtr<FWmfMediaStreamSink> StreamSink;` — The stream sink.
- L112 _private member_ `TComPtr<IMFDXGIDeviceManager> DXGIManager;` — Support for Hardware Accelerated
- L113 _private member_ `TComPtr<ID3D11Device> D3D11Device;`
- L114 _private member_ `TComPtr<ID3D11DeviceContext> D3DImmediateContext;`

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaStreamSink.h` (Private)


#### class `FWmfMediaStreamSink`  
`class FWmfMediaStreamSink : public IMFGetService , public IMFMediaTypeHandler , public IMFStreamSink`  
_L29-293_
- inherits: `IMFGetService,IMFMediaTypeHandler,IMFStreamSink`
- desc: Implements a stream sink object for the WMF pipeline.
- L43 _public prototype_ `static bool Create(const GUID& MajorType, TComPtr<FWmfMediaStreamSink>& OutSink);` — Creates a stream sink for the specified major type. @param MajorType The sink's major type. @param OutSink Will contain the created sink. @return true on success, false otherwise.
- L53 _public prototype_ `FWmfMediaStreamSink(const GUID& InMajorType, DWORD InStreamId);` — Create and initialize a new instance. @param InMajorType The sink's major media type, i.e. audio or video. @param InStreamId The sink's identifier.
- L64 _public prototype_ `bool Initialize(FWmfMediaSink& InOwner);` — Initialize this sink. @param InOwner The media sink that owns this stream sink. @return true on success, false otherwise. @see Shutdown
- L71 _public prototype_ `void SetDecoder(WmfMediaDecoder* InDecoder);` — Call this to set which decoder we belong to. @param InDecoder
- L81 _public prototype_ `HRESULT Pause();` — Pause the stream. This method is called by the owner media sink. @return Result code. @see Preroll, Restart, Start, Stop
- L91 _public prototype_ `HRESULT Restart();` — Restart the stream. This method is called by the owner media sink. @return Result code. @see Pause, Preroll, Start, Stop
- L98 _public prototype_ `void Shutdown();` — Shut down this sink. @see Initialize
- L108 _public prototype_ `HRESULT Start();` — Start the sink. This method is called by the owner media sink. @return Result code. @see Pause, Preroll, Restart, Stop
- L118 _public prototype_ `HRESULT Stop();` — Stop the stream. This method is called by the owner media sink. @return Result code. @see Pause, Preroll, Restart, Start
- L124 _public prototype_ `STDMETHODIMP GetService(__RPC__in REFGUID guidService, __RPC__in REFIID riid, __RPC__deref_out_opt LPVOID* ppvObject);`
- L130 _public prototype_ `STDMETHODIMP BeginGetEvent(IMFAsyncCallback* pCallback, IUnknown* pState);`
- L131 _public prototype_ `STDMETHODIMP EndGetEvent(IMFAsyncResult* pResult, IMFMediaEvent** ppEvent);`
- L132 _public prototype_ `STDMETHODIMP GetEvent(DWORD dwFlags, IMFMediaEvent** ppEvent);`
- L133 _public prototype_ `STDMETHODIMP QueueEvent(MediaEventType met, REFGUID extendedType, HRESULT hrStatus, const PROPVARIANT* pvValue);`
- L139 _public prototype_ `STDMETHODIMP GetCurrentMediaType(_Outptr_ IMFMediaType** ppMediaType);`
- L140 _public prototype_ `STDMETHODIMP GetMajorType(__RPC__out GUID* pguidMajorType);`
- L141 _public prototype_ `STDMETHODIMP GetMediaTypeByIndex(DWORD dwIndex, _Outptr_ IMFMediaType** ppType);`
- L142 _public prototype_ `STDMETHODIMP GetMediaTypeCount(__RPC__out DWORD* pdwTypeCount);`
- L143 _public prototype_ `STDMETHODIMP IsMediaTypeSupported(IMFMediaType* pMediaType, _Outptr_opt_result_maybenull_ IMFMediaType** ppMediaType);`
- L144 _public prototype_ `STDMETHODIMP SetCurrentMediaType(IMFMediaType* pMediaType);`
- L150 _public prototype_ `STDMETHODIMP Flush();`
- L151 _public prototype_ `STDMETHODIMP GetIdentifier(__RPC__out DWORD* pdwIdentifier);`
- L152 _public prototype_ `STDMETHODIMP GetMediaSink(__RPC__deref_out_opt IMFMediaSink** ppMediaSink);`
- L153 _public prototype_ `STDMETHODIMP GetMediaTypeHandler(__RPC__deref_out_opt IMFMediaTypeHandler** ppHandler);`
- L154 _public prototype_ `STDMETHODIMP PlaceMarker(MFSTREAMSINK_MARKER_TYPE eMarkerType, __RPC__in const PROPVARIANT* pvarMarkerValue, __RPC__in const PROPVARIANT* pvarContextValue);`
- L155 _public prototype_ `STDMETHODIMP ProcessSample(__RPC__in_opt IMFSample* pSample);`
- L161 _public prototype_ `STDMETHODIMP_(ULONG) AddRef();`
- L162 _public prototype_ `STDMETHODIMP QueryInterface(REFIID RefID, void** Object);`
- L163 _public prototype_ `STDMETHODIMP_(ULONG) Release();`
- L170 _public prototype_ `void SetClockRate(float InClockRate);` — Set current clock rate @param InClockRate Clock Rate
- L179 _public prototype_ `void SetMediaSamplePoolAndQueue(TSharedPtr<FWmfMediaHardwareVideoDecodingTextureSamplePool>& InVideoSamplePool, TMediaSampleQueue<IMediaTextureSample>* InVideoSampleQueue, TFunction<FMediaTimeStamp(FTimespan, EMediaTrackType)>&& InAdjustTimeStamp, TFunction<bool()>&& InIsSampleStillDesired);` — Set media sample pool and queue @param InVideoSamplePool sample pool to get sample from @param InVideoSampleQueue Sample queue to fill @param InSequenceIndex Pointer to current sequence index value
- L184 _public prototype_ `void OnRequestMoreData();` — Request more data being delivered to video output queue
- L189 _public prototype_ `void OnSeekStarted();` — Notify instance that a seek logically started
- L192 _public prototype_ `void OnSessionEnded();`
- L197 _public prototype_ `bool ExecuteOnceNoPendingRequests(TFunction<void()>&& ExecuteOnIdle);` — Register lambda to execute (once) as soon as any pending requests are done (if any are pending)
- L202 _private prototype_ `virtual ~FWmfMediaStreamSink();` — Hidden destructor (this class is reference counted).
- L209 _private prototype_ `void CopyTextureAndEnqueueSample(IMFSample* pSample);` — Copy decoder texture to shared texture and enqueue the sample @param pSample Sample from decoder
- L215 _private prototype_ `bool IsVideoSampleQueueFull() const;` — Check if video sample queue is full @return true when Video Sample Queue is full.
- L220 _private member_ `FCriticalSection CriticalSection;` — Critical section for synchronizing access to this sink.
- L223 _private member_ `TComPtr<IMFMediaEventQueue> EventQueue;` — The event queue.
- L226 _private member_ `TComPtr<IMFMediaType> CurrentMediaType;` — The sink's current media type.
- L229 _private member_ `TComPtr<FWmfMediaSink> Owner;` — The media sink that owns this stream sink.
- L232 _private member_ `TComPtr<WmfMediaDecoder> Decoder;` — The decoder we belong to.
- L235 _private member_ `int32 RefCount;` — Holds a reference counter for this instance.
- L238 _private member_ `DWORD StreamId;` — The stream identifier (currently fixed).
- L241 _private member_ `const GUID StreamType;` — The sink's major media type.
- L244 _private member_ `float ClockRate;` — ClockRate to support reverse playback
- L247 _private member_ `HANDLE WaitTimer;` — Timer on which we wait for the next sample
- L250 _private member_ `TSharedPtr<FWmfMediaHardwareVideoDecodingTextureSamplePool> VideoSamplePool;` — Video sample pool from which to get next free sample
- L253 _private member_ `TMediaSampleQueue<IMediaTextureSample>* VideoSampleQueue;` — Video sample queue which is filled with current sample
- L256 _private member_ `int32 NumRequestsInFlight;` — Number of requests for new video samples currently in flight
- L257 _private member_ `int32 NumRequestsInFlightWithSystem;`
- L258 _private member_ `TFunction<void()> OnIdleAction;`
- L261 _private member_ `bool bSeekInProgress;` — If true seek is in progress logically
- L264 _private member_ `bool bScrubbingInProgress;` — If true scrubbing is in progress logically
- L267 _private member_ `bool bSystemIsScrubbing;` — If true system is in scrubbing mode (play with rate==0)
- L270 _private member_ `bool bSegmentEnded;` — If true segment just ended, but is still logically being processed
- L273 _private member_ `TFunction<FMediaTimeStamp(FTimespan,EMediaTrackType)> AdjustTimeStamp;` — Callback to adjust given timestamp for the output queue
- L276 _private member_ `TFunction<bool()> IsSampleStillDesired;` — Callback to check if a newly decoded sample is still desired or should be discarded.
- L279 _private member_ `bool bShowSubTypeErrorMessage;` — Make sure we don't spam output with MF_MT_SUBTYPE error message

#### struct `FWmfMediaStreamSink::FQueuedSample`  
`struct FQueuedSample`  
_L282-292_
- desc: Structure for queued media samples & markers.
- L285 _public member_ `MFSTREAMSINK_MARKER_TYPE MarkerType;` — Stream marker type.
- L288 _public member_ `PROPVARIANT* MarkerContext;` — Stream marker context.
- L291 _public member_ `TComPtr<IMFSample> Sample;` — The media sample.

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaTopologyLoader.h` (Private)


#### class `WmfMediaTopologyLoader`  
`class WmfMediaTopologyLoader`  
_L13-24_
- desc: Custom topology loader used to check if video will be decoded on GPU or CPU even when hardware acceleration is enabled.
- L17 _public prototype_ `bool EnableHardwareAcceleration(const TComPtr<IMFTopology>& InTopology) const;`
- L21 _private prototype_ `bool ResolveActivationNode(const TComPtr<IMFTopology>& InTopology) const;`
- L22 _private prototype_ `bool SetHardwareAccelerationOnTransformNode(const TComPtr<IMFTopology>& InTopology) const;`
- L23 _private prototype_ `bool FindDeviceManager(const TComPtr<IMFTopology>& InTopology, TComPtr<IMFDXGIDeviceManager>& OutDeviceManager, TComPtr<IMFTopologyNode>& OutD3DManagerNode, TComPtr<IMFTransform>& OutTransformNode) const;`

### `Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaUtils.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace WmfMedia`
- L23 _prototype_ `FString AttributeToString(const GUID& Guid);` (scope `WmfMedia`) — Convert a media attribute identifier to string. @param Guid The unique identifier of the attribute. @return The corresponding name string.
- L32 _prototype_ `FString CaptureDeviceRoleToString(ERole Role);` (scope `WmfMedia`) — Convert a capture device role to string. @param Role The device role to convert. @return The corresponding string. @see CaptureDeviceRoleToString, GuidToString, MajorTypeToString, MarkerTypeToString, MediaEventToString, ResultToString, SubTypeToString, TopologyStatusToString
- L42 _prototype_ `HRESULT CopyAttribute(IMFAttributes* Src, IMFAttributes* Dest, const GUID& Key);` (scope `WmfMedia`) — Copy an attribute from one attribute collection to another. @param Src The attribute collection to copy from. @param Dest The attribute collection to copy to. @param Key The key of the attribute to copy. @return Result code.
- L52 _prototype_ `TComPtr<IMFMediaType> CreateOutputType(IMFMediaType& InputType, bool AllowNonStandardCodecs, bool IsVideoDevice);` (scope `WmfMedia`) — Create an output media type for the given input media type. @param InputType The input type to create the output type for. @param AllowNonStandardCodecs Whether non-standard codecs should be allowed. @param Whether the media source is a video capture device (there are some limitations with those). @return The output type, or NULL on error.
- L59 _prototype_ `FString DumpAttributes(IMFAttributes& Attributes);` (scope `WmfMedia`) — Dump information about the given media type to the output log. @param MediaType The media type.
- L70 _prototype_ `void EnumerateCaptureDevices(GUID DeviceType, TArray<TComPtr<IMFActivate>>& OutDevices);` (scope `WmfMedia`) — Enumerate the available capture devices. The supported device types are MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_GUID for audio capture devices and MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID for video capture devices. @param DeviceType The type of devices to enumerate. @param OutDevices Will contain the collection of found device source activators.
- L78 _prototype_ `FString FormatTypeToString(GUID FormatType);` (scope `WmfMedia`) — Convert an MF_MT_AM_FORMAT_TYPE value to string. @param FormatType The unique identifier of the format type. @return The corresponding string.
- L88 _prototype_ `bool FrameRateToRatio(float FrameRate, int32& OutNumerator, int32& OutDenominator);` (scope `WmfMedia`) — Convert a floating point frame rate to an integer ratio. @param OutNumerator Will contain the ratio's numerator. @param OutDenominator Will contain the ratio's denominator. @return true on success, false if the frame rate cannot be represented as a ratio. @see RatioToFrameRate
- L97 _prototype_ `FString FourccToString(unsigned long Fourcc);` (scope `WmfMedia`) — Convert a FOURCC code to string. @param Fourcc The code to convert. @return The corresponding string. @see CaptureDeviceRoleToString, GuidToString, MajorTypeToString, MarkerTypeToString, MediaEventToString, ResultToString, SubTypeToString, TopologyStatusToString
- L109 _prototype_ `bool GetCaptureDeviceInfo(IMFActivate& Device, FText& OutDisplayName, FString& OutInfo, bool& OutSoftwareDevice, FString& OutUrl);` (scope `WmfMedia`) — Get information about the given capture device. @param Device The device. @param OutDisplayName Will contain the device's human readable name. @param OutInfo Will contain a device specific information string. @param OutSoftwareDevice Will contain a flag indicating whether the device is software. @param OutUrl Will contain the device's media URL string. @return true on success, false otherwise.
- L118 _prototype_ `const TArray<TComPtr<IMFMediaType>>& GetSupportedMediaTypes(const GUID& MajorType);` (scope `WmfMedia`) — Get the list of supported media types for the specified major type. @param MajorType The major type to query, i.e. audio or video. @return Media type collection. @see IsSupportedMajorType
- L127 _prototype_ `HRESULT GetTopologyFromEvent(IMFMediaEvent& Event, TComPtr<IMFTopology>& OutTopology);` (scope `WmfMedia`) — Get the playback topology object from the given media event. @param Event The event object. @param OutTopology Will contain the topology. @return Result code.
- L136 _prototype_ `FString GuidToString(const GUID& Guid);` (scope `WmfMedia`) — Convert a Windows GUID to string. @param Guid The GUID to convert. @return The corresponding string. @see CaptureDeviceRoleToString, FourccToString, MajorTypeToString, MarkerTypeToString, MediaEventToString, ResultToString, SubTypeToString, TopologyStatusToString
- L144 _prototype_ `FString InterlaceModeToString(MFVideoInterlaceMode Mode);` (scope `WmfMedia`) — Convert a video interlace mode to string. @param Mode The interlace mode to convert. @return The corresponding string.
- L153 _prototype_ `bool IsSupportedMajorType(const GUID& MajorType);` (scope `WmfMedia`) — Check whether the given major media type is supported. @param Type The major type to check. @return true if the type is supported, false otherwise. @see GetSupportedMediaTypes
- L162 _prototype_ `FString MajorTypeToString(const GUID& MajorType);` (scope `WmfMedia`) — Convert a media major type to string. @param MajorType The major type GUID to convert. @return The corresponding string. @see CaptureDeviceRoleToString, FourccToString, GuidToString, MarkerTypeToString, MediaEventToString, ResultToString, SubTypeToString, TopologyStatusToString
- L171 _prototype_ `FString MarkerTypeToString(MFSTREAMSINK_MARKER_TYPE MarkerType);` (scope `WmfMedia`) — Convert a stream sink marker type to string. @param MarkerType The marker type to convert. @return The corresponding string. @see CaptureDeviceRoleToString, FourccToString, GuidToString, MajorTypeToString, MediaEventToString, ResultToString, SubTypeToString, TopologyStatusToString
- L180 _prototype_ `FString MediaEventToString(MediaEventType Event);` (scope `WmfMedia`) — Convert a media event to string. @param Event The event code to convert. @return The corresponding string. @see CaptureDeviceRoleToString, FourccToString, GuidToString, MajorTypeToString, MarkerTypeToString, ResultToString, SubTypeToString, TopologyStatusToString
- L190 _prototype_ `float RatioToFrameRate(int32 Numerator, int32 Denominator);` (scope `WmfMedia`) — Convert an integer ratio to a floating point frame rate. @param Numerator The ratio's numerator. @param Denominator The ratio's denominator. @return The corresponding floating point value. @see FrameRateToRatio
- L200 _prototype_ `TComPtr<IMFMediaSource> ResolveMediaSource(TSharedPtr<FArchive, ESPMode::ThreadSafe> Archive, const FString& Url, bool Precache);` (scope `WmfMedia`) — Resolve a media source from an archive or URL. @param Archive The archive to read media data from (optional). @param Url The media source URL. @param Precache Whether to precache media into RAM if URL is a local file. @return The media source object, or NULL if it couldn't be resolved.
- L209 _prototype_ `FString ResultToString(HRESULT Result);` (scope `WmfMedia`) — Convert an WMF HRESULT code to string. @param Result The result code to convert. @return The corresponding string. @see CaptureDeviceRoleToString, FourccToString, GuidToString, MajorTypeToString, MarkerTypeToString, MediaEventToString, SubTypeToString, TopologyStatusToString
- L218 _prototype_ `FString SubTypeToString(const GUID& SubType);` (scope `WmfMedia`) — Convert a media sub-type to string. @param SubType The sub-type GUID to convert. @return The corresponding string. @see CaptureDeviceRoleToString, FourccToString, GuidToString, MajorTypeToString, MarkerTypeToString, MediaEventToString, ResultToString, TopologyStatusToString
- L227 _prototype_ `FString TopologyStatusToString(MF_TOPOSTATUS Status);` (scope `WmfMedia`) — Convert a WMF topology status to string. @param Status The status to convert. @return The corresponding string. @see CaptureDeviceRoleToString, FourccToString, GuidToString, MajorTypeToString, MarkerTypeToString, MediaEventToString, ResultToString, SubTypeToString

### `Plugins/Media/WmfMedia/Source/WmfMedia/Public/IWmfMediaCodec.h` (Public)


#### class `IWmfMediaCodec`  
`class IWmfMediaCodec`  
_L12-27_
- L15 _public prototype_ `virtual ~IWmfMediaCodec() = default;`
- L16 _public function_ `virtual bool IsCodecSupported(const GUID& InMajorType, const GUID& InSubType) const`
- L17 _public function_ `virtual bool SetVideoFormat(const GUID& InSubType, GUID& OutVideoFormat) const`
- L18 _public function_ `virtual bool SetupDecoder( const GUID& InMajorType, const GUID& InSubType, TComPtr<IMFTopologyNode>& InDecoderNode, TComPtr<IMFTransform>& InTransform)`
- L26 _public function_ `virtual bool IsHardwareAccelerated() const`

### `Plugins/Media/WmfMedia/Source/WmfMedia/Public/IWmfMediaModule.h` (Public)


#### class `IWmfMediaModule`  
`class IWmfMediaModule : public IModuleInterface`  
_L17-52_
- inherits: `IModuleInterface`
- desc: Interface for the WmfMedia module.
- L26 _public prototype_ `virtual bool IsInitialized() const = 0;` — Is the Wmf media module initialized? @return True if the module is initialized.
- L29 _public function_ `static IWmfMediaModule* Get()` — Get this module
- L41 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Creates a Windows Media Foundation based media player. @param EventSink The object that receives media events from the player. @return A new media player, or nullptr if a player couldn't be created.
- L42 _public function_ `WmfMediaCodecManager* GetCodecManager()`
- L47 _public prototype_ `virtual ~IWmfMediaModule();` — Virtual destructor.
- L51 _protected member_ `TUniquePtr<WmfMediaCodecManager> CodecManager;` — Codec manager which handle codec from other plugin.

### `Plugins/Media/WmfMedia/Source/WmfMedia/Public/WmfMediaCodec/WmfMediaCodecGenerator.h` (Public)


#### class `WmfMediaCodecGenerator`  
`template <class T> class WmfMediaCodecGenerator : public IWmfMediaCodec`  
_L9-65_
- inherits: `IWmfMediaCodec`
- L13 _public function_ `WmfMediaCodecGenerator(bool bInIsHardwareAccelerated)`
- L18 _public prototype_ `virtual ~WmfMediaCodecGenerator() = default;`
- L20 _public function_ `virtual bool IsCodecSupported(const GUID& InMajorType, const GUID& InSubType) const override`
- L30 _public function_ `virtual bool SetVideoFormat(const GUID& InSubType, GUID& OutVideoFormat) const`
- L35 _public function_ `virtual bool SetupDecoder( const GUID& InMajorType, const GUID& InSubType, TComPtr<IMFTopologyNode>& InDecoderNode, TComPtr<IMFTransform>& InTransform)`
- L57 _public function_ `virtual bool IsHardwareAccelerated() const`
- L64 _private member_ `bool bIsHardwareAccelerated;`

### `Plugins/Media/WmfMedia/Source/WmfMedia/Public/WmfMediaCodec/WmfMediaCodecManager.h` (Public)


#### class `WmfMediaCodecManager`  
`class WmfMediaCodecManager : public IWmfMediaCodec`  
_L16-36_
- inherits: `IWmfMediaCodec`
- L19 _public prototype_ `WmfMediaCodecManager() = default;`
- L20 _public prototype_ `WmfMediaCodecManager(const WmfMediaCodecManager&) = delete;`
- L21 _public prototype_ `WmfMediaCodecManager(WmfMediaCodecManager&&) = delete;`
- L22 _public prototype_ `WmfMediaCodecManager& operator=(const WmfMediaCodecManager&) = delete;`
- L24 _public prototype_ `virtual bool IsCodecSupported(const GUID& InMajorType, const GUID& InSubType) const override;`
- L25 _public prototype_ `virtual bool SetVideoFormat(const GUID& InSubType, GUID& OutVideoFormat) const override;`
- L26 _public prototype_ `virtual bool SetupDecoder( const GUID& InMajorType, const GUID& InSubType, TComPtr<IMFTopologyNode>& InDecoderNode, TComPtr<IMFTransform>& InTransform) override;`
- L32 _public prototype_ `void AddCodec(TUniquePtr<IWmfMediaCodec> InCodec);`
- L35 _private member_ `TArray<TUniquePtr<IWmfMediaCodec>> RegisteredCodec;`

#### class `WmfMediaCodecManager`  
`class WmfMediaCodecManager`  
_L40-43_
- L19 _public prototype_ `WmfMediaCodecManager() = default;`
- L20 _public prototype_ `WmfMediaCodecManager(const WmfMediaCodecManager&) = delete;`
- L21 _public prototype_ `WmfMediaCodecManager(WmfMediaCodecManager&&) = delete;`
- L22 _public prototype_ `WmfMediaCodecManager& operator=(const WmfMediaCodecManager&) = delete;`
- L24 _public prototype_ `virtual bool IsCodecSupported(const GUID& InMajorType, const GUID& InSubType) const override;`
- L25 _public prototype_ `virtual bool SetVideoFormat(const GUID& InSubType, GUID& OutVideoFormat) const override;`
- L26 _public prototype_ `virtual bool SetupDecoder( const GUID& InMajorType, const GUID& InSubType, TComPtr<IMFTopologyNode>& InDecoderNode, TComPtr<IMFTransform>& InTransform) override;`
- L32 _public prototype_ `void AddCodec(TUniquePtr<IWmfMediaCodec> InCodec);`
- L35 _private member_ `TArray<TUniquePtr<IWmfMediaCodec>> RegisteredCodec;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API WMFMEDIA_API`

### `Plugins/Media/WmfMedia/Source/WmfMedia/Public/WmfMediaCodec/WmfMediaDecoder.h` (Public)


#### class `WmfMediaDecoder`  
`class WmfMediaDecoder : public IMFTransform`  
_L19-180_
- inherits: `IMFTransform`
- L31 _public prototype_ `WmfMediaDecoder();`
- L32 _public prototype_ `virtual ~WmfMediaDecoder();`
- L34 _public function_ `static GUID GetMajorType()`
- L36 _public prototype_ `virtual ULONG STDMETHODCALLTYPE AddRef() override;`
- L37 _public prototype_ `virtual ULONG STDMETHODCALLTYPE Release() override;`
- L38 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetStreamLimits(DWORD* pdwInputMinimum, DWORD* pdwInputMaximum, DWORD* pdwOutputMinimum, DWORD* pdwOutputMaximum) override;`
- L39 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetStreamCount(DWORD* pcInputStreams, DWORD* pcOutputStreams) override;`
- L40 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetStreamIDs(DWORD dwInputIDArraySize, DWORD* pdwInputIDs, DWORD dwOutputIDArraySize, DWORD* pdwOutputIDs) override;`
- L41 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetInputStreamInfo(DWORD dwInputStreamID, MFT_INPUT_STREAM_INFO* pStreamInfo) override;`
- L42 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetOutputStreamInfo(DWORD dwOutputStreamID, MFT_OUTPUT_STREAM_INFO* pStreamInfo) override;`
- L43 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetAttributes(IMFAttributes** pAttributes) override;`
- L44 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetInputStreamAttributes(DWORD dwInputStreamID, IMFAttributes** ppAttributes) override;`
- L45 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetOutputStreamAttributes(DWORD dwOutputStreamID, IMFAttributes **ppAttributes) override;`
- L46 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE DeleteInputStream(DWORD dwStreamID) override;`
- L47 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE AddInputStreams(DWORD cStreams, DWORD* adwStreamIDs) override;`
- L48 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetInputAvailableType(DWORD dwInputStreamID, DWORD dwTypeIndex, IMFMediaType** ppType) override;`
- L49 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE SetInputType(DWORD dwInputStreamID, IMFMediaType* pType, DWORD dwFlags) override;`
- L50 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE SetOutputType(DWORD dwOutputStreamID, IMFMediaType* pType, DWORD dwFlags) override;`
- L51 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetInputCurrentType(DWORD dwInputStreamID, IMFMediaType** ppType) override;`
- L52 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetOutputCurrentType(DWORD dwOutputStreamID, IMFMediaType** ppType) override;`
- L53 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetInputStatus(DWORD dwInputStreamID, DWORD* pdwFlags) override;`
- L54 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetOutputStatus(DWORD* pdwFlags) override;`
- L55 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE SetOutputBounds(LONGLONG hnsLowerBound, LONGLONG hnsUpperBound) override;`
- L56 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE ProcessEvent(DWORD dwInputStreamID, IMFMediaEvent* pEvent) override;`
- L57 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE ProcessInput(DWORD dwInputStreamID, IMFSample* pSample, DWORD dwFlags) override;`
- L59 _public prototype_ `virtual HRESULT OnSetOutputType(IMFMediaType *InMediaType);`
- L60 _public prototype_ `virtual HRESULT OnFlush();`
- L61 _public prototype_ `virtual HRESULT OnDiscontinuity();`
- L68 _public prototype_ `virtual bool IsExternalBufferSupported() const;` — See if this decoder supports external buffers. @return True if so.
- L75 _public prototype_ `void EnableExternalBuffer(bool bInEnable);` — Call this to use our external buffers and not Windows. @param bInEnable True to use external.
- L82 _public function_ `bool IsExternalBufferEnabled() const` — See if external buffers are enabled. @return True if so.
- L93 _public prototype_ `bool GetExternalBuffer(TArray<uint8>& InBuffer, uint64 TimeStamp);` — Call this to get a decoded external buffer from the decoder. InBuffer does not need to have any space. This will move the data to InBuffer. @return True if a buffer was found. @param InBuffer This will be updated with the data of the buffer. @param TimeStamp TimeStamp of the requested buffer.
- L101 _public prototype_ `static void ReturnExternalBuffer(TArray<uint8>& InBuffer);` — Call this to return an external buffer to the decoder. The data in InBuffer will be moved out. @param InBuffer Buffer to return.
- L111 _protected prototype_ `TArray<uint8>* AllocateExternalBuffer(uint64 InTimeStamp, int32 InSize);` — Call this to get an external buffer to decode into. @param InTimeStamp TimeStamp for the buffer. @param InSize Desired size of this buffer.
- L115 _private prototype_ `virtual HRESULT OnCheckInputType(IMFMediaType *InMediaType) = 0;`
- L116 _private prototype_ `virtual HRESULT OnSetInputType(IMFMediaType* InMediaType) = 0;`
- L117 _private prototype_ `virtual bool HasPendingOutput() const = 0;`
- L118 _private prototype_ `virtual HRESULT InternalProcessInput(LONGLONG InTimeStamp, BYTE* InData, DWORD InDataSize) = 0;`
- L120 _private prototype_ `void EmplyQueues();`
- L121 _private prototype_ `HRESULT OnCheckOutputType(IMFMediaType *InMediaType);`
- L128 _private prototype_ `void ReturnExternalBufferInternal(TArray<uint8>& InBuffer);` — Call this to return an external buffer to the decoder. @param InBuffer Buffer to return.
- L133 _private prototype_ `void RemoveDecoderFromMap();` — Removes this decoder from the map from GetMapBufferToDecoder.
- L138 _private prototype_ `static FCriticalSection& GetMapBufferCriticalSection();` — Access to the map from GetMapBufferToDecoder should be guarded with this.
- L144 _private prototype_ `static TMap<uint8*, WmfMediaDecoder*>& GetMapBufferToDecoder();` — Returns a map that lets you find which decoder a buffer is using. Lock GetMapBufferCriticalSection before using this.
- L148 _protected member_ `int32 RefCount;`
- L150 _protected member_ `FCriticalSection CriticalSection;`
- L152 _protected member_ `TComPtr<IMFMediaType> InputType;`
- L153 _protected member_ `TComPtr<IMFMediaType> OutputType;`
- L155 _protected member_ `UINT32 ImageWidthInPixels;`
- L156 _protected member_ `UINT32 ImageHeightInPixels;`
- L157 _protected member_ `MFRatio FrameRate;`
- L158 _protected member_ `DWORD InputImageSize;`
- L159 _protected member_ `DWORD OutputImageSize;`
- L161 _protected member_ `TComPtr<IMFDXGIDeviceManager> DXGIManager;`
- L162 _protected member_ `TComPtr<ID3D11Device> D3D11Device;`
- L163 _protected member_ `TComPtr<ID3D11DeviceContext> D3DImmediateContext;`
- L165 _protected member_ `LONGLONG InternalTimeStamp;`
- L166 _protected member_ `UINT64 SampleDuration;`
- L168 _protected member_ `TQueue<DataBuffer> InputQueue;`
- L169 _protected member_ `TQueue<DataBuffer> OutputQueue;`
- L172 _protected member_ `bool bIsExternalBufferEnabled;` — True if we are using our external buffers and not Windows.
- L174 _protected member_ `TMap<uint64, TArray<uint8>*> MapTimeStampToExternalBuffer;` — Maps a time stamp to a buffer.
- L176 _protected member_ `TArray<TArray<uint8>*> ExternalBufferPool;` — Holds all the buffers that are not being used.
- L178 _protected member_ `FCriticalSection BufferCriticalSection;` — Guards access to the buffers.

#### struct `WmfMediaDecoder::DataBuffer`  
`struct DataBuffer`  
_L23-28_
- L25 _public member_ `TArray<unsigned char> Color;`
- L26 _public member_ `TArray<unsigned char> Alpha;`
- L27 _public member_ `LONGLONG TimeStamp;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API WMFMEDIA_API`

### `Plugins/Media/WmfMedia/Source/WmfMedia/Public/WmfMediaCommon.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define WMFMEDIA_SUPPORTED_PLATFORM (PLATFORM_WINDOWS && !UE_SERVER)`
- L29 _variable_ `const GUID FORMAT_525WSS = { 0xc7ecf04d, 0x4582, 0x4869, { 0x9a, 0xbb, 0xbf, 0xb5, 0x23, 0xb6, 0x2e, 0xdf } };`
- L30 _variable_ `const GUID FORMAT_DvInfo = { 0x05589f84, 0xc356, 0x11ce, { 0xbf, 0x01, 0x00, 0xaa, 0x00, 0x55, 0x59, 0x5a } };`
- L31 _variable_ `const GUID FORMAT_MPEG2Video = { 0xe06d80e3, 0xdb46, 0x11cf, { 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea } };`
- L32 _variable_ `const GUID FORMAT_MPEGStreams = { 0x05589f83, 0xc356, 0x11ce, { 0xbf, 0x01, 0x00, 0xaa, 0x00, 0x55, 0x59, 0x5a } };`
- L33 _variable_ `const GUID FORMAT_MPEGVideo = { 0x05589f82, 0xc356, 0x11ce, { 0xbf, 0x01, 0x00, 0xaa, 0x00, 0x55, 0x59, 0x5a } };`
- L34 _variable_ `const GUID FORMAT_None = { 0x0F6417D6, 0xc318, 0x11d0, { 0xa4, 0x3f, 0x00, 0xa0, 0xc9, 0x22, 0x31, 0x96 } };`
- L35 _variable_ `const GUID FORMAT_VideoInfo = { 0x05589f80, 0xc356, 0x11ce, { 0xbf, 0x01, 0x00, 0xaa, 0x00, 0x55, 0x59, 0x5a } };`
- L36 _variable_ `const GUID FORMAT_VideoInfo2 = { 0xf72a76A0, 0xeb0a, 0x11d0, { 0xac, 0xe4, 0x00, 0x00, 0xc0, 0xcc, 0x16, 0xba } };`
- L37 _variable_ `const GUID FORMAT_WaveFormatEx = { 0x05589f81, 0xc356, 0x11ce,{ 0xbf, 0x01, 0x00, 0xaa, 0x00, 0x55, 0x59, 0x5a } };`
- L39 _variable_ `const GUID MR_VIDEO_ACCELERATION_SERVICE = { 0xefef5175, 0x5c7d, 0x4ce2, { 0xbb, 0xbd, 0x34, 0xff, 0x8b, 0xca, 0x65, 0x54 } };`
- L42 _variable_ `const GUID MF_LOW_LATENCY = { 0x9c27891a, 0xed7a, 0x40e1, { 0x88, 0xe8, 0xb2, 0x27, 0x27, 0xa0, 0x24, 0xee } };`
- L46 _variable_ `const GUID UE_WMF_PrivateFormatGUID = { 0x630d3c34, 0xefac, 0x42f0, {0xa9, 0x6f, 0x6e, 0xa2, 0x6f, 0xd4, 0x16, 0x6}};` — A private GUID used to add a wrapped format GUID to an IMFMediaType.
- L59 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWmfMedia, Log, All);` — Log category for the WmfMedia module.
- L59 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWmfMedia, Log, All);` — Log category for the WmfMedia module.

### `Plugins/Media/WmfMedia/Source/WmfMedia/Public/WmfMediaHardwareVideoDecodingRendering.h` (Public)


#### class `FWmfMediaHardwareVideoDecodingParameters`  
`class FWmfMediaHardwareVideoDecodingParameters`  
_L9-13_
- L12 _public prototype_ `static bool ConvertTextureFormat_RenderThread(FRHICommandListImmediate& RHICmdList, FWmfMediaHardwareVideoDecodingTextureSample* InSample, FTextureRHIRef InDstTexture);`

### `Plugins/Media/WmfMedia/Source/WmfMedia/Public/WmfMediaHardwareVideoDecodingShaders.h` (Public)


#### class `FWmfMediaHardwareVideoDecodingShader`  
`class FWmfMediaHardwareVideoDecodingShader : public FGlobalShader`  
_L28-90_
- inherits: `FGlobalShader`
- desc: Shaders which allow the conversion of NV12 texture data into RGB textures.
- L31 _public typedef_ `using FParameters = FHardwareVideoDecodingShaderParams;`
- L33 _public prototype_ `FWmfMediaHardwareVideoDecodingShader() = default;`
- L34 _public function_ `FWmfMediaHardwareVideoDecodingShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)`
- L39 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L45 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`
- L50 _public function_ `static FHardwareVideoDecodingShaderParams GetCommonParameters(bool InIsOutputSrgb)`
- L63 _public function_ `static FHardwareVideoDecodingShaderParams GetParameters(FRHIShaderResourceView* InTextureY, FRHIShaderResourceView* InTextureUV, bool InIsOutputSrgb, bool InFilterUV = true)`
- L83 _public function_ `static FHardwareVideoDecodingShaderParams GetParameters(FRHIShaderResourceView* InTextureRGBA, bool InIsOutputSrgb)`

#### class `FHardwareVideoDecodingVS`  
`class FHardwareVideoDecodingVS : public FWmfMediaHardwareVideoDecodingShader`  
_L92-97_
- inherits: `FWmfMediaHardwareVideoDecodingShader`
- L95 _public prototype_ `DECLARE_GLOBAL_SHADER(FHardwareVideoDecodingVS);`
- L96 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FHardwareVideoDecodingVS, FWmfMediaHardwareVideoDecodingShader);`

#### class `FHardwareVideoDecodingPS`  
`class FHardwareVideoDecodingPS : public FWmfMediaHardwareVideoDecodingShader`  
_L99-104_
- inherits: `FWmfMediaHardwareVideoDecodingShader`
- L102 _public prototype_ `DECLARE_GLOBAL_SHADER(FHardwareVideoDecodingPS);`
- L103 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FHardwareVideoDecodingPS, FWmfMediaHardwareVideoDecodingShader);`

#### class `FHardwareVideoDecodingPassThroughPS`  
`class FHardwareVideoDecodingPassThroughPS : public FWmfMediaHardwareVideoDecodingShader`  
_L106-111_
- inherits: `FWmfMediaHardwareVideoDecodingShader`
- L109 _public prototype_ `DECLARE_GLOBAL_SHADER(FHardwareVideoDecodingPassThroughPS);`
- L110 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FHardwareVideoDecodingPassThroughPS, FWmfMediaHardwareVideoDecodingShader);`

#### class `FHardwareVideoDecodingY416PS`  
`class FHardwareVideoDecodingY416PS : public FWmfMediaHardwareVideoDecodingShader`  
_L113-118_
- inherits: `FWmfMediaHardwareVideoDecodingShader`
- L116 _public prototype_ `DECLARE_GLOBAL_SHADER(FHardwareVideoDecodingY416PS);`
- L117 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FHardwareVideoDecodingY416PS, FWmfMediaHardwareVideoDecodingShader);`

#### class `FHardwareVideoDecodingYCoCgPS`  
`class FHardwareVideoDecodingYCoCgPS : public FWmfMediaHardwareVideoDecodingShader`  
_L121-126_
- inherits: `FWmfMediaHardwareVideoDecodingShader`
- L124 _public prototype_ `DECLARE_GLOBAL_SHADER(FHardwareVideoDecodingYCoCgPS);`
- L125 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FHardwareVideoDecodingYCoCgPS, FWmfMediaHardwareVideoDecodingShader);`

#### class `FHardwareVideoDecodingYCoCgAlphaPS`  
`class FHardwareVideoDecodingYCoCgAlphaPS : public FWmfMediaHardwareVideoDecodingShader`  
_L129-134_
- inherits: `FWmfMediaHardwareVideoDecodingShader`
- L132 _public prototype_ `DECLARE_GLOBAL_SHADER(FHardwareVideoDecodingYCoCgAlphaPS);`
- L133 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FHardwareVideoDecodingYCoCgAlphaPS, FWmfMediaHardwareVideoDecodingShader);`

### `Plugins/Media/WmfMedia/Source/WmfMedia/Public/WmfMediaHardwareVideoDecodingTextureSample.h` (Public)


#### class `FWmfMediaHardwareVideoDecodingTextureSample`  
`class FWmfMediaHardwareVideoDecodingTextureSample : public FWmfMediaTextureSample, public IMediaTextureSampleConverter`  
_L25-197_
- inherits: `FWmfMediaTextureSample,IMediaTextureSampleConverter`
- desc: Texture sample for hardware video decoding.
- L32 _public function_ `FWmfMediaHardwareVideoDecodingTextureSample() : FWmfMediaTextureSample() , Format(PF_Unknown) , AlphaFormat(PF_Unknown) , bIsDestinationTextureSRGB(false)` — Default constructor.
- L53 _public prototype_ `ID3D11Texture2D* InitializeSourceTexture(const TRefCountPtr<ID3D11Device>& InD3D11Device, FMediaTimeStamp InTime, FTimespan InDuration, const FIntPoint& InDim, EPixelFormat InFormat, EMediaTextureSampleFormat InMediaTextureSampleFormat);` — Initialize shared texture from Wmf device @param InD3D11Device WMF device to create shared texture from @param InTime The sample time (in the player's local clock). @param InDuration The sample duration @param InDim texture dimension to create @param InFormat texture format to create @param InMediaTextureSampleFormat Media texture sample format @param InCreateFlags texture create flag @return The texture resource object that will hold the sample data.
- L63 _public function_ `void SetPixelFormat(EPixelFormat InFormat)` — Call this to set the pixel format. InitializeSourceTexture does this so you only need to call this function if you don't call InitializeSourceTexture. @param InFormat Pixel format for texture.
- L70 _public function_ `void SetIsDestinationTextureSRGB(bool bIsSRGB)` — Call this to set whether DestinationTexture should be sRGB or not. @param bIsSRGB True if so.
- L77 _public function_ `void SetAlphaTexture(EPixelFormat InFormat)` — Call this to set what the alpha texture should be. @param InFormat Pixel format of alpha texture.
- L84 _public function_ `virtual IMediaTextureSampleConverter* GetMediaTextureSampleConverter() override` — Get media texture sample converter if sample implements it @return texture sample converter
- L97 _public function_ `virtual bool Convert(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, const FConversionHints& Hints) override` — Texture sample convert using hardware video decoding.
- L108 _public function_ `TComPtr<ID3D11Texture2D> GetSourceTexture() const` — Get source texture from WMF device @return Source texture
- L119 _public function_ `FTextureRHIRef GetOrCreateDestinationTexture(FRHICommandListBase& RHICmdList)` — Get Destination Texture of render thread device @param RHICmdList the command list used to create the texture. @return Destination texture
- L151 _public function_ `FTextureRHIRef GetOrCreateDestinationAlphaTexture(FRHICommandListBase& RHICmdList)` — Get Destination Texture of render thread device @param RHICmdList the command list used to create the texture. @return Destination texture
- L172 _public prototype_ `virtual void ShutdownPoolable() override;`
- L178 _private member_ `TComPtr<ID3D11Texture2D> SourceTexture;` — Source Texture resource (from Wmf device).
- L181 _private member_ `TRefCountPtr<ID3D11Device> D3D11Device;` — D3D11 Device which create the texture, used to release the keyed mutex when the sampled is returned to the pool
- L184 _private member_ `FTextureRHIRef DestinationTexture;` — Destination Texture resource (from Rendering device)
- L187 _private member_ `FTextureRHIRef DestinationAlphaTexture;` — Destination Texture resource (from Rendering device)
- L190 _private member_ `EPixelFormat Format;` — Texture format
- L193 _private member_ `EPixelFormat AlphaFormat;` — Texture format
- L196 _private member_ `bool bIsDestinationTextureSRGB;` — Whether DestinationTexture should be an sRGB texture or not.

#### class `FWmfMediaHardwareVideoDecodingTextureSamplePool`  
`class FWmfMediaHardwareVideoDecodingTextureSamplePool : public TMediaObjectPool<FWmfMediaHardwareVideoDecodingTextureSample>`  
_L200-200_
- inherits: `TMediaObjectPool<FWmfMediaHardwareVideoDecodingTextureSample>`
- desc: Implements a pool for WMF texture samples.
