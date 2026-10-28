# Plugins / AvfMedia

- module root: `Plugins/Media/AvfMedia/Source/AvfMedia`
- headers: 9; symbols: 201
- symbol kinds: class=9, delegate=1, enum=1, enumerator=4, function=18, macro=8, member=70, namespace=1, prototype=88, struct=1
- DynamicallyLoadedModuleNames: Media
- PrivateDependencyModuleNames: ApplicationCore, AvfMediaFactory, Core, Engine, MediaUtils, MetalRHI, RHI, RenderCore
- PrivateIncludePathModuleNames: Media

### `Plugins/Media/AvfMedia/Source/AvfMedia/Private/AvfMediaPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvfMedia, Log, All);` — Log category for the AvfMedia module.
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvfMedia, Log, All);` — Log category for the AvfMedia module.
- L13 _macro_ `#define AVF_GAME_THREAD_BLOCK`
- L14 _macro_ `#define AVF_GAME_THREAD_RETURN`
- L15 _macro_ `#define AVF_GAME_THREAD_CALL(Block) GameThreadCall(Block, false)`
- L17 _macro_ `#define AVF_GAME_THREAD_BLOCK bool(void)`
- L18 _macro_ `#define AVF_GAME_THREAD_RETURN return true`
- L19 _macro_ `#define AVF_GAME_THREAD_CALL(Block) \`

### `Plugins/Media/AvfMedia/Source/AvfMedia/Private/Player/AvfMediaOverlaySample.h` (Private)


#### class `FAvfMediaOverlaySample`  
`class FAvfMediaOverlaySample : public IMediaOverlaySample`  
_L13-79_
- inherits: `IMediaOverlaySample`
- desc: Implements an overlay text sample for AvfMedia.
- L19 _public function_ `FAvfMediaOverlaySample() : Time(FTimespan::Zero())` — Default constructor.
- L24 _public prototype_ `virtual ~FAvfMediaOverlaySample() = default;` — Virtual destructor.
- L35 _public function_ `bool Initialize(const FString& InString, FTimespan InTime)` — Initialize the overlay sample. @param InString The overlay string. @param InTime The play time for which the sample was generated. @return true on success, false otherwise.
- L47 _public function_ `virtual FTimespan GetDuration() const override`
- L52 _public function_ `virtual TOptional<FVector2D> GetPosition() const override`
- L57 _public function_ `virtual FText GetText() const override`
- L62 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L67 _public function_ `virtual EMediaOverlaySampleType GetType() const override`
- L75 _private member_ `FText Text;` — The overlay text.
- L78 _private member_ `FTimespan Time;` — The play time for which the sample was generated.

### `Plugins/Media/AvfMedia/Source/AvfMedia/Private/Player/AvfMediaPlayer.h` (Private)


#### class `FAvfMediaPlayer`  
`class FAvfMediaPlayer : public IMediaPlayer , protected IMediaCache , protected IMediaControls , protected IMediaView`  
_L30-188_
- inherits: `IMediaPlayer,IMediaCache,IMediaControls,IMediaView`
- desc: Implements a media player using the AV framework.
- L43 _public prototype_ `FAvfMediaPlayer(IMediaEventSink& InEventSink);` — Create and initialize a new instance. @param InEventSink The object that receives media events from this player.
- L46 _public prototype_ `~FAvfMediaPlayer();` — Destructor.
- L51 _public prototype_ `void OnEndReached();` — Called by the delegate when the playback reaches the end.
- L54 _public prototype_ `void OnStatusNotification();` — Called by the delegate whenever the player item status changes.
- L60 _public prototype_ `virtual void Close() override;`
- L61 _public prototype_ `virtual IMediaCache& GetCache() override;`
- L62 _public prototype_ `virtual IMediaControls& GetControls() override;`
- L63 _public prototype_ `virtual FString GetInfo() const override;`
- L64 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L65 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L66 _public prototype_ `virtual FString GetStats() const override;`
- L67 _public prototype_ `virtual IMediaTracks& GetTracks() override;`
- L68 _public prototype_ `virtual FString GetUrl() const override;`
- L69 _public prototype_ `virtual IMediaView& GetView() override;`
- L70 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L71 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) override;`
- L72 _public prototype_ `virtual void TickAudio() override;`
- L73 _public prototype_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode) override;`
- L74 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L80 _protected prototype_ `virtual bool CanControl(EMediaControl Control) const override;`
- L81 _protected prototype_ `virtual FTimespan GetDuration() const override;`
- L82 _protected prototype_ `virtual float GetRate() const override;`
- L83 _protected prototype_ `virtual EMediaState GetState() const override;`
- L84 _protected prototype_ `virtual EMediaStatus GetStatus() const override;`
- L85 _protected prototype_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const override;`
- L86 _protected prototype_ `virtual FTimespan GetTime() const override;`
- L87 _protected prototype_ `virtual bool IsLooping() const override;`
- L88 _protected prototype_ `virtual bool Seek(const FTimespan& Time) override;`
- L89 _protected prototype_ `virtual bool SetLooping(bool Looping) override;`
- L90 _protected prototype_ `virtual bool SetRate(float Rate) override;`
- L92 _protected prototype_ `virtual bool SetNativeVolume(float Volume) override;`
- L97 _private prototype_ `void HandleApplicationHasEnteredForeground();` — Callback for when the application is resumed in the foreground
- L100 _private prototype_ `void HandleApplicationWillEnterBackground();` — Callback for when the applicaiton is being paused in the background
- L103 _private prototype_ `void HandleApplicationActivate();` — Callback for when the application is moved from the inactive to active state
- L106 _private prototype_ `void HandleApplicationDeactivate();` — Callback for when the application is moved from the active to inactive state
- L111 _private prototype_ `void HandleAudioRouteChanged(bool InDeviceAvailable);` — Callback for when the audio device is changed @param InDeviceAvailable - true if the device is available
- L114 _private prototype_ `void ClearTimeSync();` — Clears the Time Sync flag
- L117 _private prototype_ `FTimespan GetAudioTimeSync() const;` — Returns the consumed buffer type sync Points
- L118 _private prototype_ `FTimespan GetVideoTimeSync() const;`
- L121 _private member_ `float CurrentRate;` — The current playback rate.
- L124 _private member_ `EMediaState CurrentState;` — Media playback state.
- L127 _private member_ `FTimespan CurrentTime;` — The current time of the playback.
- L130 _private member_ `FTimespan Duration;` — The duration of the media.
- L133 _private member_ `IMediaEventSink& EventSink;` — The media event handler.
- L136 _private member_ `FString Info;` — Media information string.
- L139 _private member_ `FAVPlayerDelegate* MediaHelper;` — Cocoa helper object we can use to keep track of ns property changes in our media items
- L142 _private member_ `FAVMediaAssetResourceLoaderDelegate* MediaResourceLoader;` — Cocoa Media helper object for Pak file loading
- L145 _private member_ `AVPlayer* MediaPlayer;` — The AVFoundation media player
- L148 _private member_ `FString MediaUrl;` — The URL of the currently opened media.
- L151 _private member_ `AVPlayerItem* PlayerItem;` — The player item which the media player uses to progress.
- L154 _private member_ `TQueue<TFunction<void()>> PlayerTasks;` — Tasks to be executed on the player thread.
- L157 _private member_ `FAvfMediaSamples* Samples;` — The media sample queue.
- L160 _private member_ `bool ShouldLoop;` — Should the video loop to the beginning at completion
- L163 _private member_ `FAvfMediaTracks* Tracks;` — The media track collection.
- L166 _private member_ `bool bPrerolled;` — Playback primed and ready when set
- L169 _private member_ `bool bSeeking;` — Media Player is currently seeking
- L172 _private member_ `bool bTimeSynced;` — Set false until the first audio (or video if none) sample has been consumed after seeking or prerolling or, on non Engine mixer platforms first tick after seek
- L175 _private member_ `FCriticalSection CriticalSection;` — Mutex to ensure thread-safe access
- L178 _private member_ `FDelegateHandle EnteredForegroundHandle;` — Foreground/background delegate for resume
- L179 _private member_ `FDelegateHandle HasReactivatedHandle;`
- L182 _private member_ `FDelegateHandle EnteredBackgroundHandle;` — Foreground/background delegate for pause
- L183 _private member_ `FDelegateHandle WillDeactivateHandle;`
- L186 _private member_ `FDelegateHandle AudioRouteChangedHandle;` — Delegate for changing the audio device

### `Plugins/Media/AvfMedia/Source/AvfMedia/Private/Player/AvfMediaTracks.h` (Private)


#### class `FAvfMediaTracks`  
`class FAvfMediaTracks : public IMediaTracks`  
_L30-180_
- inherits: `IMediaTracks`
- L66 _public prototype_ `FAvfMediaTracks(FMediaSamples& InSamples);` — Default constructor.
- L69 _public prototype_ `virtual ~FAvfMediaTracks();` — Virtual destructor.
- L78 _public prototype_ `void AppendStats(FString &OutStats) const;` — Append track statistics information to the given string. @param OutStats The string to append the statistics to.
- L86 _public prototype_ `void Initialize(AVPlayerItem* InPlayerItem, FString& OutInfo);` — Initialize the track collection. @param PlayerItem The player item containing the track information. @param OutInfo Will contain information about the available media tracks.
- L99 _public prototype_ `void ProcessCaptions(AVPlayerItemLegibleOutput* Output, NSArray<NSAttributedString*>* Strings, NSArray* NativeSamples, CMTime ItemTime);` — Process caption frames. Called by the caption track delegate to provide the attributed strings for each timecode to the caption sink. @param Output The caption track output that generated the strings. @param Strings The attributed caption strings. @param ItemTime The display time for the strings. @see ProcessAudio, ProcessVideo
- L106 _public prototype_ `void ProcessVideo();` — Process video frames. @see ProcessAudio, ProcessCaptions
- L109 _public prototype_ `void Reset();` — Reset the stream collection.
- L117 _public prototype_ `void ApplyMuteState(bool bMute);` — Allow independant audio mute when producing audio buffers for play back through the engine Muting will stop sending audio buffers to the media audio sink e.g. Gives the option to have fast mute on reverse otherwise we can get a few bad buffers
- L124 _public prototype_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const override;`
- L125 _public prototype_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const override;`
- L126 _public prototype_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L127 _public prototype_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override;`
- L128 _public prototype_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L129 _public prototype_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L130 _public prototype_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L131 _public prototype_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L132 _public prototype_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L133 _public prototype_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override;`
- L134 _public prototype_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) override;`
- L139 _private member_ `TArray<FTrack> AudioTracks;` — The available audio tracks.
- L142 _private member_ `TArray<FTrack> CaptionTracks;` — The available caption tracks.
- L145 _private member_ `TArray<FTrack> VideoTracks;` — The available video tracks.
- L150 _private member_ `FAvfMediaAudioSamplePool* AudioSamplePool;` — Audio sample object pool.
- L153 _private member_ `mutable FCriticalSection CriticalSection;` — Synchronizes write access to track arrays, selections & sinks.
- L156 _private member_ `AVPlayerItem* PlayerItem;` — The player item containing the track information.
- L160 _private member_ `volatile bool bMuted;` — Current Mute State.
- L164 _private member_ `FMediaSamples& Samples;` — The media sample queue.
- L167 _private member_ `int32 SelectedAudioTrack;` — Index of the selected audio track.
- L170 _private member_ `int32 SelectedCaptionTrack;` — Index of the selected caption track.
- L173 _private member_ `int32 SelectedVideoTrack;` — Index of the selected video track.
- L176 _private member_ `AudioStreamBasicDescription TargetDesc;` — Target description for audio output required by Media framework audio sinks.
- L179 _private member_ `TSharedPtr<FAvfMediaVideoSampler, ESPMode::ThreadSafe> VideoSampler;` — Object to sample video frames

#### enum `FAvfMediaTracks::ESyncStatus`  
`enum ESyncStatus`  
_L33-39_
- L35 _public enumerator_ `Default` — Starting state
- L36 _public enumerator_ `Behind` — Frame is behind playback cursor.
- L37 _public enumerator_ `Ready` — Frame is within tolerance of playback cursor.
- L38 _public enumerator_ `Ahead` — Frame is ahead of playback cursor.

#### struct `FAvfMediaTracks::FTrack`  
`struct FTrack`  
_L41-61_
- L43 _public function_ `FTrack() : Loaded(false) , FrameSize(0, 0) , FrameRate(0.f) , bFullRangeVideo(false)`
- L50 _public member_ `AVAssetTrack* AssetTrack;`
- L51 _public member_ `FText DisplayName;`
- L52 _public member_ `bool Loaded;`
- L53 _public member_ `FString Name;`
- L54 _public member_ `NSObject* Output;`
- L55 _public member_ `int32 StreamIndex;`
- L58 _public member_ `FIntPoint FrameSize;` — Cached Video Track Data
- L59 _public member_ `float FrameRate;`
- L60 _public member_ `bool bFullRangeVideo;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define AUDIO_PLAYBACK_VIA_ENGINE (PLATFORM_MAC)`

### `Plugins/Media/AvfMedia/Source/AvfMedia/Private/Player/AvfMediaVideoSampler.h` (Private)


#### class `FAvfMediaVideoSampler`  
`class DLLEXPORT FAvfMediaVideoSampler`  
_L23-78_
- desc: Creates samples from video frames.
- L28 _public prototype_ `FAvfMediaVideoSampler(FMediaSamples& InSamples);` — Default constructor.
- L31 _public prototype_ `virtual ~FAvfMediaVideoSampler();` — Virtual destructor.
- L42 _public prototype_ `void SetOutput(AVPlayerItemVideoOutput* Output, float InFrameRate, bool bFullRange = false);` — Set the video output object to be sampled. This method must be called on the render thread. @param Output The output object.
- L45 _public prototype_ `void Tick();` — Tick the video sampler (on the render thread).
- L47 _public prototype_ `void ProcessFrame(CVPixelBufferRef Frame, FTimespan SampleTime, FTimespan SampleDuration);`
- L49 _public prototype_ `void Reset();`
- L53 _protected prototype_ `virtual void ProcessOutputSample(const TSharedRef<IMediaTextureSample, ESPMode::ThreadSafe>& Sample);`
- L57 _private member_ `FCriticalSection CriticalSection;` — Mutex to ensure thread-safe access
- L60 _private member_ `AVPlayerItemVideoOutput* Output;` — The track's video output handle
- L63 _private member_ `FMediaSamples& Samples;` — The media sample queue.
- L66 _private member_ `FAvfMediaTextureSamplePool* VideoSamplePool;` — Video sample object pool.
- L69 _private member_ `float FrameDuration;` — Current Video cached decode information
- L70 _private member_ `FMatrix const* ColorTransform;`
- L75 _private member_ `CVMetalTextureCacheRef MetalTextureCache;` — The Metal texture cache for unbuffered texture uploads.

### `Plugins/Media/AvfMedia/Source/AvfMedia/Private/Shared/AvfMediaUtils.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace AvfMedia`
- L22 _prototype_ `FString CodecTypeToString(CMVideoCodecType CodecType);` (scope `AvfMedia`) — Convert the given codec type to a human readable string. @param CodecType The codec type to convert. @return The codec type's strings representation.
- L30 _prototype_ `FString MediaTypeToString(NSString* MediaType);` (scope `AvfMedia`) — Convert the given media type to a human readable string. @param MediaType The media type to convert. @return The media type's strings representation.
- L40 _prototype_ `FString ConvertToIOSPath(const FString& Filename, bool bForWrite);` (scope `AvfMedia`) — Convert the given file name to an iOS compatible file path. @param Filename The file name to convert. @param bForWrite @return The iOS path.

### `Plugins/Media/AvfMedia/Source/AvfMedia/Public/AvfMediaAudioSample.h` (Public)


#### class `FAvfMediaAudioSample`  
`class FAvfMediaAudioSample : public IMediaAudioSample , public IMediaPoolable`  
_L15-144_
- inherits: `IMediaAudioSample,IMediaPoolable`
- desc: Audio sample generated by AvfMedia player.
- L22 _public function_ `FAvfMediaAudioSample() : Channels(0) , Duration(0) , Frames(0) , SampleRate(0) , Time(FTimespan::Zero()) , Format(EMediaAudioSampleFormat::Undefined)` — Default constructor.
- L32 _public prototype_ `virtual ~FAvfMediaAudioSample() = default;` — Virtual destructor.
- L41 _public function_ `uint8* GetMutableBuffer()` — Get a writable pointer to the sample buffer. @return Sample buffer.
- L56 _public function_ `bool Initialize( uint32 InBufferSize, uint32 InFrames, uint32 InChannels, uint32 InSampleRate, FTimespan InTime, FTimespan InDuration, EMediaAudioSampleFormat InFormat = EMediaAudioSampleFormat::Float)` — Initialize the sample. @param InBufferSize The size of the audio buffer. @param InFrames Number of frames in the buffer. @param InChannels Number of audio channels. @param InSampleRate The sample rate. @param InTime The sample time (in the player's local clock). @return true on success, false otherwise.
- L87 _public function_ `virtual const void* GetBuffer() override`
- L92 _public function_ `virtual uint32 GetChannels() const override`
- L97 _public function_ `virtual FTimespan GetDuration() const override`
- L102 _public function_ `virtual EMediaAudioSampleFormat GetFormat() const override`
- L107 _public function_ `virtual uint32 GetFrames() const override`
- L112 _public function_ `virtual uint32 GetSampleRate() const override`
- L117 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L125 _private member_ `TArray<uint8> Buffer;` — The sample's frame buffer.
- L128 _private member_ `uint32 Channels;` — Number of audio channels.
- L131 _private member_ `FTimespan Duration;` — Duration for which the sample is valid.
- L134 _private member_ `uint32 Frames;` — Number of frames in the buffer.
- L137 _private member_ `uint32 SampleRate;` — Audio sample rate (in samples per second).
- L140 _private member_ `FTimespan Time;` — Play time for which the sample was generated.
- L143 _private member_ `EMediaAudioSampleFormat Format;` — Sample Format  (8/16/24/32 Integer or 32 Float)

#### class `FAvfMediaAudioSamplePool`  
`class FAvfMediaAudioSamplePool : public TMediaObjectPool<FAvfMediaAudioSample>`  
_L148-148_
- inherits: `TMediaObjectPool<FAvfMediaAudioSample>`
- desc: Implements a pool for AVF audio sample objects.

### `Plugins/Media/AvfMedia/Source/AvfMedia/Public/AvfMediaTextureSample.h` (Public)


#### class `FAvfMediaTextureSample`  
`class DLLEXPORT FAvfMediaTextureSample : public IMediaTextureSample , public IMediaPoolable`  
_L34-140_
- inherits: `IMediaTextureSample,IMediaPoolable`
- desc: Texture sample generated by AvfMedia player.
- L41 _public prototype_ `virtual ~FAvfMediaTextureSample();` — Virtual destructor.
- L58 _public prototype_ `bool Initialize( TRefCountPtr<FRHITexture>& InTexture, const FIntPoint& InDim, const FIntPoint& InOutputDim, FTimespan InTime, FTimespan InDuration, CVPixelBufferRef InPixelBuffer = nullptr);` — Initialize the texture sample with a texture resource. @param InTexture The texture resource containing the video frame. @param InDim The sample buffer's width and height (in pixels). @param InOutputDim The sample's output width and height (in pixels). @param InTime The sample time (in the player's local clock). @param InDuration The duration for which the sample is valid. @param InPixelBuffer Optional CVPixelBuffer to retain for CPU access via GetBuffer(). @return true on success, false otherwise.
- L93 _public prototype_ `virtual const void* GetBuffer() override;`
- L94 _public prototype_ `virtual FIntPoint GetDim() const override;`
- L95 _public prototype_ `virtual FTimespan GetDuration() const override;`
- L96 _public prototype_ `virtual EMediaTextureSampleFormat GetFormat() const override;`
- L97 _public prototype_ `virtual FIntPoint GetOutputDim() const override;`
- L98 _public prototype_ `virtual uint32 GetStride() const override;`
- L99 _public prototype_ `virtual FRHITexture* GetTexture() const override;`
- L100 _public prototype_ `virtual FMediaTimeStamp GetTime() const override;`
- L101 _public prototype_ `virtual bool IsCacheable() const override;`
- L102 _public prototype_ `virtual bool IsOutputSrgb() const override;`
- L103 _public prototype_ `virtual void Reset() override;`
- L107 _public prototype_ `virtual void ShutdownPoolable() override;`
- L111 _private prototype_ `void UnlockAndReleasePixelBuffer();`
- L114 _private member_ `FIntPoint Dim;` — Width and height of the texture sample.
- L117 _private member_ `FTimespan Duration;` — Duration for which the sample is valid.
- L120 _private member_ `FIntPoint OutputDim;` — Width and height of the output.
- L123 _private member_ `FTimespan Time;` — Sample time.
- L127 _private member_ `TRefCountPtr<FRHITexture> Texture;` — The sample's texture resource.
- L131 _private member_ `TArray<uint8> Buffer;` — The sample's data buffer.
- L134 _private member_ `uint32 Stride;` — Number of bytes per pixel row.
- L139 _private member_ `CVPixelBufferRef LockedPixelBuffer = nullptr;` — Retained CVPixelBuffer for CPU access (locked read-only while sample is active).

#### class `FAvfMediaTextureSamplePool`  
`class FAvfMediaTextureSamplePool : public TMediaObjectPool<FAvfMediaTextureSample>`  
_L144-144_
- inherits: `TMediaObjectPool<FAvfMediaTextureSample>`
- desc: Implements a pool for AVF texture sample objects.

#### Free symbols / members of external scopes

- L23 _macro_ `#define FVector FVectorWorkaround`

### `Plugins/Media/AvfMedia/Source/AvfMedia/Public/IAvfMediaModule.h` (Public)


#### class `IAvfMediaModule`  
`class IAvfMediaModule : public IModuleInterface`  
_L15-32_
- inherits: `IModuleInterface`
- desc: Interface for the AvfMedia module.
- L26 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Create a AV Foundation based media player. @param EventSink The object that receives media events from the player. @return A new media player, or nullptr if a player couldn't be created.
- L31 _public prototype_ `virtual ~IAvfMediaModule() = default;` — Virtual destructor.
