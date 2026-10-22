# Runtime / MediaUtils

- module root: `Source/Runtime/MediaUtils`
- headers: 19; symbols: 602
- symbol kinds: class=24, delegate=7, enum=7, enumerator=25, function=107, macro=1, member=168, namespace=3, prototype=226, struct=16, typedef=17, union=1
- PrivateDependencyModuleNames: ImageWriteQueue
- PublicDependencyModuleNames: Core, CoreUObject, ImageWrapper, Media, SignalProcessing

### `Source/Runtime/MediaUtils/Private/LinearEase.h` (Private)


#### class `FLinearEase`  
`class FLinearEase`  
_L8-95_
- L11 _public function_ `FLinearEase() : StartValue(0.0f) , CurrentValue(0.0f) , DeltaValue(0.0f) , SampleRate(44100.0f) , DurationTicks(0) , DefaultDurationTicks(0) , CurrentTick(0)`
- L21 _public prototype_ `~FLinearEase() = default;`
- L23 _public function_ `bool IsDone() const`
- L28 _public function_ `void Init(float InSampleRate)`
- L33 _public function_ `void SetValueRange(const float Start, const float End, const float InTimeSec)`
- L40 _public function_ `float GetValue()`
- L55 _public function_ `void SetValueInterrupt(const float InValue)` — Updates the target value without changing the duration or tick data. Sets the state as if the new value was the target value all along
- L70 _public function_ `void SetValue(const float InValue, float InTimeSec = 0.0f)`
- L88 _private member_ `float StartValue;`
- L89 _private member_ `float CurrentValue;`
- L90 _private member_ `float DeltaValue;`
- L91 _private member_ `float SampleRate;`
- L92 _private member_ `int32 DurationTicks;`
- L93 _private member_ `int32 DefaultDurationTicks;`
- L94 _private member_ `int32 CurrentTick;`

### `Source/Runtime/MediaUtils/Private/MediaUtilsPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaUtils, Log, All);` — Declares a log category for this module.
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaUtils, Log, All);` — Declares a log category for this module.

### `Source/Runtime/MediaUtils/Public/AppMediaTimeSource.h` (Public)


#### class `FAppMediaTimeSource`  
`class FAppMediaTimeSource : public IMediaTimeSource`  
_L12-25_
- inherits: `IMediaTimeSource`
- desc: Implements the a media time source that derives its time from the application's global time.
- L18 _public prototype_ `virtual ~FAppMediaTimeSource() = default;` — Virtual destructor.
- L24 _public prototype_ `virtual FTimespan GetTimecode() override;`

### `Source/Runtime/MediaUtils/Public/IMediaPlayerLifecycleManager.h` (Public)


#### class `IMediaPlayerLifecycleManagerDelegate`  
`class IMediaPlayerLifecycleManagerDelegate`  
_L73-120_
- desc: Interface to receive global player lifetime events from media framework
- L97 _public typedef_ `typedef TSharedPtr<IOpenRequest, ESPMode::ThreadSafe> IOpenRequestRef;`
- L110 _public typedef_ `typedef TSharedPtr<IControl, ESPMode::ThreadSafe> IControlRef;`
- L112 _public prototype_ `virtual ~IMediaPlayerLifecycleManagerDelegate() = default;`
- L114 _public prototype_ `virtual bool OnMediaPlayerOpen(IControlRef Control, IOpenRequestRef OpenRequest) = 0;`
- L115 _public prototype_ `virtual void OnMediaPlayerCreated(IControlRef Control) = 0;`
- L116 _public prototype_ `virtual void OnMediaPlayerCreateFailed(IControlRef Control) = 0;`
- L117 _public prototype_ `virtual void OnMediaPlayerClosed(IControlRef Control) = 0;`
- L118 _public prototype_ `virtual void OnMediaPlayerDestroyed(IControlRef Control) = 0;`
- L119 _public prototype_ `virtual void OnMediaPlayerResourcesReleased(IControlRef Control, uint32 ResourceFlags) = 0;`

#### enum `IMediaPlayerLifecycleManagerDelegate::(anonymous)`  
`enum`  
_L76-82_

#### class `IMediaPlayerLifecycleManagerDelegate::IOpenRequest`  
`class IOpenRequest`  
_L85-96_
- desc: Request to create and open a player
- L88 _public prototype_ `virtual ~IOpenRequest() = default;`
- L90 _public prototype_ `virtual const FString& GetUrl() const = 0;`
- L91 _public prototype_ `virtual const IMediaOptions* GetOptions() const = 0;`
- L92 _public prototype_ `virtual const FMediaPlayerOptions* GetPlayerOptions() const = 0;`
- L93 _public prototype_ `virtual IMediaPlayerFactory* GetPlayerFactory() const = 0;`
- L94 _public prototype_ `virtual bool WillCreateNewPlayer() const = 0;`
- L95 _public prototype_ `virtual bool WillUseNewResources(uint32 ResourceFlags) const = 0;`

#### class `IMediaPlayerLifecycleManagerDelegate::IControl`  
`class IControl`  
_L100-109_
- desc: Control interface for lifecycle delegate
- L103 _public prototype_ `virtual ~IControl() = default;`
- L105 _public prototype_ `virtual bool SubmitOpenRequest(IOpenRequestRef && OpenRequest) = 0;`
- L107 _public prototype_ `virtual TSharedPtr<FMediaPlayerFacade, ESPMode::ThreadSafe> GetFacade() const = 0;`
- L108 _public prototype_ `virtual uint64 GetMediaPlayerInstanceID() const = 0;`

#### Free symbols / members of external scopes

- L77 _enumerator_ `ResourceFlags_Decoder = 1 << 0` (scope `IMediaPlayerLifecycleManagerDelegate::__anon5b8ded8e0103`)
- L78 _enumerator_ `ResourceFlags_OutputBuffers = 1 << 1` (scope `IMediaPlayerLifecycleManagerDelegate::__anon5b8ded8e0103`)
- L80 _enumerator_ `ResourceFlags_All = (1 << 2) - 1` (scope `IMediaPlayerLifecycleManagerDelegate::__anon5b8ded8e0103`)
- L81 _enumerator_ `ResourceFlags_Any = ResourceFlags_All` (scope `IMediaPlayerLifecycleManagerDelegate::__anon5b8ded8e0103`)

### `Source/Runtime/MediaUtils/Public/MediaAudioResampler.h` (Public)


#### class `FMediaAudioResampler`  
`class FMediaAudioResampler`  
_L19-117_
- L24 _public prototype_ `FMediaAudioResampler();` — Default constructor.
- L29 _public prototype_ `void Flush();` — Flush the resampler.
- L43 _public prototype_ `uint32 Generate(float* Output, FMediaTimeStamp& OutTime, const uint32 FramesRequested, float Rate, FTimespan Time, FMediaAudioSampleSource& SampleSource, uint32& JumpFrame);` — Generate the next frame of audio. @param Output The output sample buffer (will be incremented by the number of sample values written). @param OutTime The time of the first output frame that was returned. @param FramesRequested The maximum number of frames to get. @param Rate The current play rate. @param Time The current play time. @param SampleSource The object that provides more audio samples if needed. @param JumpFrame Frame that a jump in time occured on. @return The actual number of frames returned.
- L51 _public prototype_ `void Initialize(const uint32 InOutputChannels, const uint32 InOutputSampleRate);` — Initialize the resampler. @param InOutputSampleRate Desired output sample rate. @see SetAudioSamples
- L60 _protected prototype_ `void ClearInput();` — Clear the input samples. @see SetInput
- L69 _protected prototype_ `bool SetInput(const TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& Sample);` — Set the audio sample to be resampled. @param Sample The input audio sample. @return true on success, false otherwise. @see ClearInput
- L76 _private member_ `float CurrentFrame[8];` — Cached sample values of the current frame.
- L79 _private member_ `float NextFrame[8];` — Cached sample values of the next frame.
- L82 _private member_ `float FrameAlpha;` — Linear interpolation between current and next frame.
- L85 _private member_ `int64 FrameIndex;` — Index of the current input read position.
- L88 _private member_ `int64 LastFrameIndex;` — Index of the previously generated frame (to avoid calculating it again).
- L91 _private member_ `float LastRate;` — The play rate of the previously generated frame.
- L98 _private member_ `TArray<float> Input;` — The input buffer.
- L101 _private member_ `FTimespan InputDuration;` — Duration of the input buffer.
- L104 _private member_ `uint32 InputFrames;` — Number of frames in input buffer.
- L107 _private member_ `uint32 InputSampleRate;` — Sample rate of input buffer.
- L110 _private member_ `FMediaTimeStamp InputTime;` — Start time of the input buffer.
- L113 _private member_ `uint32 OutputChannels;` — Number of channels in the output.
- L116 _private member_ `uint32 OutputSampleRate;` — Sample rate of the output.

### `Source/Runtime/MediaUtils/Public/MediaCaptureSupport.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace MediaCaptureSupport`
- L19 _prototype_ `void EnumerateAudioCaptureDevices(TArray<FMediaCaptureDeviceInfo>& OutDeviceInfos);` (scope `MediaCaptureSupport`) — Enumerate available audio capture devices. @param OutDeviceInfos Will contain information about the devices. @see EnumerateVideoCaptureDevices
- L27 _prototype_ `void EnumerateVideoCaptureDevices(TArray<FMediaCaptureDeviceInfo>& OutDeviceInfos);` (scope `MediaCaptureSupport`) — Enumerate available video capture devices. @param OutDeviceInfos Will contain information about the devices. @see EnumerateAudioCaptureDevices

### `Source/Runtime/MediaUtils/Public/MediaDelegates.h` (Public)


#### class `FMediaDelegates`  
`class FMediaDelegates`  
_L17-60_
- L20 _public typedef_ `using TSharedMediaTextureSample = TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>;`
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSampleDiscardedDelegate, const UMediaTexture* , TSharedMediaTextureSample );`
- L23 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPreSampleRenderDelegate, const UMediaTexture* , bool , TSharedMediaTextureSample );`
- L24 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnSampleRenderedDelegate, const FTextureResource* , TSharedMediaTextureSample );`
- L25 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnMediaTextureResourceReleasedDelegate, FRHITexture* );`
- L34 _public member_ `static FOnSampleDiscardedDelegate OnSampleDiscarded_RenderThread;` — Callback when a sample is discarded from the MediaTexture renderer. Used to debug the samples queue. Only available in a development build. @see UE_MEDIAUTILS_DEVELOPMENT_DELEGATE
- L41 _public member_ `static FOnPreSampleRenderDelegate OnPreSampleRender_RenderThread;` — Callback when a sample is going to be used to update the MediaTexture. Used to debug the samples queue. Only available in a development build. @see UE_MEDIAUTILS_DEVELOPMENT_DELEGATE
- L49 _public member_ `static FOnSampleRenderedDelegate OnSampleRendered_RenderThread;` — Callback when a sample has been rendered in the MediaTexture. This can be used to extend the MediaTexture rendering pipeline.
- L59 _public member_ `static FOnMediaTextureResourceReleasedDelegate OnMediaTextureResourceReleased_RenderThread;` — Fires from FMediaTextureResource::ReleaseRHI immediately before the intermediate render target's RHI reference is dropped. Subscribers receive the FRHITexture* while it is still valid and must not retain it past the callback. Lets a subscriber drop per-texture GPU state while the underlying resource is alive (e.g. unmap reserved-resource tiles), avoiding stale-pointer dereference during process-exit drain.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_MEDIAUTILS_DEVELOPMENT_DELEGATE (UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG)`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSampleDiscardedDelegate, const UMediaTexture* , TSharedMediaTextureSample );`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPreSampleRenderDelegate, const UMediaTexture* , bool , TSharedMediaTextureSample );`
- L24 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnSampleRenderedDelegate, const FTextureResource* , TSharedMediaTextureSample );`
- L25 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnMediaTextureResourceReleasedDelegate, FRHITexture* );`

### `Source/Runtime/MediaUtils/Public/MediaHelpers.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace MediaUtils`
- L21 _prototype_ `FString EventToString(EMediaEvent Event);` (scope `MediaUtils`) — Convert a media event to a human readable string. @param Event The event. @return The corresponding string. @see StateToString, TrackTypeToString
- L30 _prototype_ `FString StateToString(EMediaState State);` (scope `MediaUtils`) — Convert a media state to a human readable string. @param State The state. @return The corresponding string. @see EventToString, TrackTypeToString
- L39 _prototype_ `FString TrackTypeToString(EMediaTrackType TrackType);` (scope `MediaUtils`) — Convert a media track type to a human readable string. @param TrackType The track type. @return The corresponding string. @see EventToString, StateToString

### `Source/Runtime/MediaUtils/Public/MediaObjectPool.h` (Public)


#### class `IMediaPoolable`  
`class IMediaPoolable`  
_L15-51_
- desc: Interface for objects that can be pooled.
- L27 _public function_ `virtual void InitializePoolable()` — Called when the object is removed from the pool. Override this method to initialize a poolable object before it is being reused. @see ShutdownPoolable
- L37 _public function_ `virtual void ShutdownPoolable()` — Called when the object added to the pool. Override this method to clean up a poolable object when it is no longer used. @see InitializePoolable
- L42 _public function_ `virtual bool IsReadyForReuse()` — Used to check if returned object is ready for reuse right away
- L50 _public prototype_ `virtual ~IMediaPoolable() = default;` — Virtual destructor.

#### class `TMediaPoolDefaultObjectAllocator`  
`template<typename ObjectType> class TMediaPoolDefaultObjectAllocator`  
_L54-58_
- L57 _public function_ `static ObjectType *Alloc()`

#### class `TMediaObjectPool`  
`template<typename ObjectType, typename ObjectAllocator=TMediaPoolDefaultObjectAllocator<ObjectType>> class TMediaObjectPool`  
_L69-398_
- desc: Template for media object pools. Poolable objects are required to implement the IMediaPoolable interface. @param ObjectType The type of objects managed by this pool. @todo gmp: Make media object pool lock-free
- L268 _public function_ `TMediaObjectPool(ObjectAllocator *ObjectAllocatorInstance = nullptr) : Storage(MakeShareable(new TStorage(ObjectAllocatorInstance)))` — Default constructor.
- L277 _public function_ `TMediaObjectPool(uint32 NumReserve) : Storage(MakeShareable(new TStorage(nullptr)))` — Create and initialize a new instance. @param NumReserve Number of objects to reserve.
- L296 _public function_ `ObjectType* Acquire(bool bAlloc = true)` — Acquire an untracked object from the pool. Use the Release method to return the object to the pool. You can use the ToShared and ToUnique methods to convert this object to a tracked shared object later if desired. bAlloc allows to chose if new object should be allocated and added to the pool. @return The object. @see AcquireShared, AcquireUnique, Release, ToShared, ToUnique
- L310 _public function_ `TSharedRef<ObjectType, ESPMode::ThreadSafe> AcquireShared()` — Acquire a shared object from the pool. Shared objects do not need to be returned to the pool. They'll be reclaimed automatically when their reference count goes to zero. @return The shared object. @see Acquire, AcquireUnique, Reset, ToShared
- L327 _public function_ `TSharedPtr<ObjectType, ESPMode::ThreadSafe> AcquireShared(bool bAlloc)` — Acquire a shared object from the pool. Shared objects do not need to be returned to the pool. They'll be reclaimed automatically when their reference count goes to zero. bAlloc allows to chose if new object should be allocated and added to the pool. @return The shared object. @see Acquire, AcquireUnique, Reset, ToShared
- L344 _public function_ `int32 Num() const` — Get the number of objects available in the pool. @return Number of available objects.
- L356 _public function_ `TSharedRef<ObjectType, ESPMode::ThreadSafe> ToShared(ObjectType* Object)` — Convert an object to a shared pooled object. @param Object The object to convert. @return The shared object. @see AcquireShared, ToUnique
- L370 _public function_ `void Release(ObjectType* Object)` — Return the given object to the pool. This method can return plain old C++ objects to the pool. Do not use this method with objects acquired via AcquireShared or AcquireUnique, because those are returned automatically. @see Acquire
- L381 _public function_ `void Reset(uint32 NumObjects = 0)` — Reset the pool and reserve a specified number of objects. @param NumObjects Number of objects to reserve (default = 0). @see GetObject
- L389 _public function_ `void Tick()` — Regular tick call
- L397 _private member_ `TSharedRef<TStorage, ESPMode::ThreadSafe> Storage;` — Storage for pooled objects.

#### class `TMediaObjectPool::TStorage`  
`class TStorage`  
_L74-231_
- desc: Object pool storage.
- L77 _public function_ `TStorage(ObjectAllocator *InObjectAllocatorInstance) : ObjectAllocatorInstance(InObjectAllocatorInstance)`
- L82 _public function_ `~TStorage()` — Destructor.
- L99 _public function_ `ObjectType* Acquire(bool bAlloc = true)` — Acquire an object from the pool. bAlloc allows to chose if new object should be allocated and added to the pool.
- L150 _public function_ `int32 Num() const` — Get the number of objects stored.
- L157 _public function_ `void Release(ObjectType* Object)` — Return the given object to the pool.
- L178 _public function_ `void Reserve(uint32 NumObjects)` — Reserve the specified number of objects.
- L194 _public function_ `void Tick()` — Regular tick call
- L221 _private member_ `mutable FCriticalSection CriticalSection;` — Critical section for synchronizing access to the free list.
- L224 _private member_ `TArray<ObjectType*> Pool;` — List of unused objects.
- L227 _private member_ `TQueue<ObjectType*> WaitReadyForReuse;` — List of unused objects, waiting for reuse-ability.
- L230 _private member_ `ObjectAllocator *ObjectAllocatorInstance;` — Object allocator instance (nullptr by default)

#### class `TMediaObjectPool::TDeleter`  
`class TDeleter`  
_L235-263_
- desc: Deleter for pooled objects.
- L240 _public function_ `TDeleter(const TSharedRef<TStorage, ESPMode::ThreadSafe>& InStorage) : StoragePtr(InStorage)` — Create and initialize a new instance.
- L245 _public function_ `void operator()(ObjectType* ObjectToDelete)` — Function operator to execute deleter.
- L262 _private member_ `TWeakPtr<TStorage, ESPMode::ThreadSafe> StoragePtr;` — Weak pointer to object pool storage.

### `Source/Runtime/MediaUtils/Public/MediaPlayerFacade.h` (Public)


#### class `FMediaPlayerFacade`  
`class FMediaPlayerFacade : public IMediaClockSink , public IMediaTickable , protected IMediaEventSink , public TSharedFromThis<FMediaPlayerFacade, ESPMode::ThreadSafe>`  
_L65-1141_
- inherits: `IMediaClockSink,IMediaTickable,IMediaEventSink,TSharedFromThis<FMediaPlayerFacade,ESPMode::ThreadSafe>`
- desc: Facade for low-level media player objects. The purpose of this class is to provide a simpler interface to low-level media player implementations. It implements common functionality, such as translating between time codes and play times, and manages the selection and creation of player implementations for a given media source. Note that, unlike the low-level methods in IMediaTracks, most track and track format related methods in this class allow for INDEX_NONE to be used as track and format indices in order to indicate the 'current selection'.
- L74 _public member_ `FName DesiredPlayerName;` — Name of the desired native player, if any.
- L77 _public member_ `FTimespan TimeDelay;` — Extra time to reduce from current player's time.
- L80 _public member_ `TOptional<FMediaPlayerOptions> ActivePlayerOptions;` — Active media player options.
- L85 _public prototype_ `FMediaPlayerFacade(TWeakObjectPtr<UMediaPlayer> InMediaPlayer);` — Default constructor.
- L88 _public prototype_ `virtual ~FMediaPlayerFacade();` — Virtual destructor.
- L98 _public prototype_ `void AddAudioSampleSink(const TSharedRef<FMediaAudioSampleSink, ESPMode::ThreadSafe>& SampleSink);` — Add the given audio sample sink to this player. @param SampleSink The sink to receive audio samples. @see  AddCaptionSampleSink, AddMetadataSampleSink, AddSubtitleSampleSink, AddVideoSampleSink
- L106 _public prototype_ `void AddCaptionSampleSink(const TSharedRef<FMediaOverlaySampleSink, ESPMode::ThreadSafe>& SampleSink);` — Add the given audio sample sink to this player. @param SampleSink The sink to receive caption samples. @see AddAudioSampleSink, AddMetadataSampleSink, AddSubtitleSampleSink, AddVideoSampleSink
- L114 _public prototype_ `void AddMetadataSampleSink(const TSharedRef<FMediaBinarySampleSink, ESPMode::ThreadSafe>& SampleSink);` — Add the given audio sample sink to this player. @param SampleSink The sink to receive metadata samples. @see AddAudioSampleSink, AddCaptionSampleSink, AddSubtitleSampleSink, AddVideoSampleSink
- L122 _public prototype_ `void AddSubtitleSampleSink(const TSharedRef<FMediaOverlaySampleSink, ESPMode::ThreadSafe>& SampleSink);` — Add the given audio sample sink to this player. @param SampleSink The sink to receive subtitle samples. @see AddAudioSampleSink, AddCaptionSampleSink, AddMetadataSampleSink, AddVideoSampleSink
- L130 _public prototype_ `void AddVideoSampleSink(const TSharedRef<FMediaTextureSampleSink, ESPMode::ThreadSafe>& SampleSink);` — Add the given audio sample sink to this player. @param SampleSink The sink to receive video samples. @see AddAudioSampleSink, AddCaptionSampleSink, AddMetadataSampleSink, AddSubtitleSampleSink
- L141 _public prototype_ `bool CanPause() const;` — Whether playback can be paused. Playback can be paused if the media supports pausing and if it is currently playing. @return true if pausing is allowed, false otherwise. @see CanResume, CanScrub, CanSeek, Pause
- L153 _public prototype_ `bool CanPlayUrl(const FString& Url, const IMediaOptions* Options);` — Whether the specified URL can be played by this player. If a desired player name is set for this player, it will only check whether that particular player type can play the specified URL. @param Url The URL to check. @param Options Optional media parameters. @see CanPlaySource, SetDesiredPlayerName
- L164 _public prototype_ `bool CanResume() const;` — Whether playback can be resumed. Playback can be resumed if media is loaded and if it is not already playing. @return true if resuming is allowed, false otherwise. @see CanPause, CanScrub, CanSeek, SetRate
- L172 _public prototype_ `bool CanScrub() const;` — Whether playback can be scrubbed. @return true if scrubbing is allowed, false otherwise. @see CanPause, CanResume, CanSeek, Seek
- L180 _public prototype_ `bool CanSeek() const;` — Whether playback can jump to a position. @return true if seeking is allowed, false otherwise. @see CanPause, CanResume, CanScrub, Seek
- L188 _public prototype_ `bool SupportsPlaybackTimeRange() const;` — Check whether the player supports playing back of range within the media. @return true if playing back a range is supported, false otherwise. @see GetPlaybackTimeRange, SetPlaybackTimeRange
- L193 _public prototype_ `void Close();` — Close the currently open media, if any.
- L203 _public prototype_ `uint32 GetAudioTrackChannels(int32 TrackIndex, int32 FormatIndex) const;` — Get the number of channels in the specified audio track. @param TrackIndex Index of the audio track. @param FormatIndex Index of the track format. @return Number of channels. @see GetAudioTrackSampleRate, GetAudioTrackType
- L213 _public prototype_ `uint32 GetAudioTrackSampleRate(int32 TrackIndex, int32 FormatIndex) const;` — Get the sample rate of the specified audio track. @param TrackIndex Index of the audio track. @param FormatIndex Index of the track format. @return Samples per second. @see GetAudioTrackChannels, GetAudioTrackType
- L223 _public prototype_ `FString GetAudioTrackType(int32 TrackIndex, int32 FormatIndex) const;` — Get the type of the specified audio track format. @param TrackIndex The index of the track. @param FormatIndex Index of the track format. @return Audio format type string. @see GetAudioTrackSampleRate, GetAudioTrackSampleRate
- L231 _public prototype_ `FTimespan GetDuration() const;` — Get the media's duration. @return A time span representing the duration. @see GetTime, Seek
- L239 _public prototype_ `const FGuid& GetGuid();` — Get the player's globally unique identifier. @return The Guid. @see SetGuid
- L247 _public prototype_ `FString GetInfo() const;` — Get debug information about the player and currently opened media. @return Information string. @see GetStats
- L256 _public prototype_ `FVariant GetMediaInfo(FName InfoName) const;` — Get information about the media that is playing. @param	InfoName		Name of the information we want. @returns					Requested information, or empty if not available. @see						UMediaPlayer::GetMediaInfo.
- L264 _public prototype_ `FText GetMediaName() const;` — Get the human readable name of the currently loaded media source. @return Media source name, or empty text if no media is opened @see GetPlayerName, GetUrl
- L272 _public prototype_ `TSharedPtr<TMap<FString, TArray<TUniquePtr<IMediaMetadataItem>>>, ESPMode::ThreadSafe> GetMediaMetadata() const;` — Get meta data contained in the current stream @return Map with arrays of IMediaMetaDataItem entries describing any metadata found in the current stream @note Listen to EMediaEvent::MetadataChanged to catch updates to this data
- L281 _public prototype_ `int32 GetNumTracks(EMediaTrackType TrackType) const;` — Get the number of tracks of the given type. @param TrackType The type of media tracks. @return Number of tracks. @see GetSelectedTrack, SelectTrack
- L291 _public prototype_ `int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const;` — Get the number of formats of the specified track. @param TrackType The type of media tracks. @param TrackIndex The index of the track. @return Number of formats. @see GetNumTracks, GetSelectedTrack, SelectTrack
- L298 _public function_ `TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> GetPlayer() const` — Get the low-level player associated with this object. @return The player, or nullptr if no player was created.
- L309 _public prototype_ `FName GetPlayerName() const;` — Get the name of the current native media player. @return Player name, or NAME_None if not available. @see GetMediaName
- L317 _public prototype_ `float GetRate() const;` — Get the media's current playback rate. @return The playback rate. @see SetRate, SupportsRate
- L326 _public prototype_ `int32 GetSelectedTrack(EMediaTrackType TrackType) const;` — Get the index of the currently selected track of the given type. @param TrackType The type of track to get. @return The index of the selected track, or INDEX_NONE if no track is active. @see GetNumTracks, SelectTrack
- L334 _public prototype_ `FString GetStats() const;` — Get playback statistics information. @return Information string. @see GetInfo
- L343 _public prototype_ `TRangeSet<float> GetSupportedRates(bool Unthinned = true) const;` — Get the supported playback rates. @param Unthinned Whether the rates are for unthinned playback (default = true). @return The ranges of supported rates. @see SetRate, SupportsRate
- L369 _public prototype_ `TRange<FTimespan> GetPlaybackTimeRange(EMediaTimeRangeType InRangeToGet) const;` — Returns the current playback range of the media. If playing back a range is not supported, the range returned will be equal to [ 0, GetDuration() ). The media may have an implicit default range provided by the container format or other means without having called SetPlaybackTimeRange(). The media may have internal time values not starting at 0, which are conveyed by the range. Since the range may be only a portion of the media, the duration of the returned range may be less than the media overall duration returned by GetDuration(). For live video streams the range may change dynamically as new content becomes available and old content falls off the timeline. @param InRangeToGet The type of range to get. `Absolute` returns the media's smallest and largest timeline values. Unless continuously changing in a Live stream this is usually the same as [ 0, GetDuration() ]. The base time does not have to be zero though. `Current` returns the currently set range, which is a subset of the absolute range. @return The playback range as queried for or an empty range if there is no open player. @see SupportsPlaybackTimeRange, SetPlaybackTimeRange, GetDuration
- L377 _public prototype_ `FTimespan GetTime() const;` — Get the media's current playback time. @return Playback time. @see GetDuration, Seek
- L384 _public prototype_ `FMediaTimeStamp GetTimeStamp() const;` — Get the media's current playback time stamp. @return Playback time stamp.
- L394 _public prototype_ `FMediaTimeStamp GetDisplayTimeStamp() const;` — Get the media's current playback time stamp in a "display" version @return Playback time stamp. @note The timestamp returned here will reflect a user-logic oriented version. (e.g. during seeks this will return the seek target rather than the last valid frame still displayed)
- L407 _public prototype_ `TOptional<FTimecode> GetVideoTimecode() const;` — Get the timecode from the video track, if one is available. If available, the returned value will be the timecode of the sample most recently sent into the video sink. @return Most recently delivered video timecode from the video track. @note Even if timecode is available, the value returned reflects the timecode that most recently delivered to the video sink. During a seek operation the timecode will be unset.
- L412 _public prototype_ `TRange<FMediaTimeStamp> GetLastProcessedVideoSampleTimeRange() const;` — Returns the last video sample time range that has been enqueued in the video sink.
- L422 _public prototype_ `FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const;` — Get the human readable name of the specified track. @param TrackType The type of track. @param TrackIndex The index of the track. @return Display name. @see GetNumTracks, GetTrackLanguage
- L432 _public prototype_ `int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const;` — Get the index of the active format of the specified track. @param TrackType The type of track. @param TrackIndex The index of the track. @return The index of the selected format. @see GetNumTrackFormats, GetSelectedTrack, SetTrackFormat
- L442 _public prototype_ `FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const;` — Get the language tag of the specified track. @param TrackType The type of track. @param TrackIndex The index of the track. @return Language tag, i.e. "en-US" for English, or "und" for undefined. @see GetNumTracks, GetTrackDisplayName
- L452 _public prototype_ `TOptional<FTimespan> GetTrackDuration(EMediaTrackType TrackType, int32 TrackIndex) const;` — Gets the duration of a specific track, if available. Availability depends on the media format and player implementation. If unset only the overall media duration can be used. @return An optional time span representing the duration. @see GetDuration
- L459 _public function_ `const FString& GetUrl() const` — Get the URL of the currently loaded media, if any. @return Media URL, or empty string if no media was loaded.
- L472 _public prototype_ `float GetVideoTrackAspectRatio(int32 TrackIndex, int32 FormatIndex) const;` — Get the aspect ratio of the specified video track. @param TrackIndex The index of the track. @param FormatIndex Index of the track format. @return Aspect ratio. @see GetVideoTrackDimensions, GetVideoTrackFrameRate, GetVideoTrackFrameRates, GetVideoTrackType
- L482 _public prototype_ `FIntPoint GetVideoTrackDimensions(int32 TrackIndex, int32 FormatIndex) const;` — Get the width and height of the specified video track. @param TrackIndex The index of the track. @param FormatIndex Index of the track format. @return Video dimensions. @see GetVideoTrackAspectRatio, GetVideoTrackFrameRate, GetVideoTrackFrameRates, GetVideoTrackType
- L492 _public prototype_ `float GetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex) const;` — Get frame rate of the specified video track. @param TrackIndex The index of the track. @param FormatIndex Index of the track format. @return Video frame rate. @see GetVideoTrackAspectRatio, GetVideoTrackDimensions, GetVideoTrackFrameRates, GetVideoTrackType
- L502 _public prototype_ `TRange<float> GetVideoTrackFrameRates(int32 TrackIndex, int32 FormatIndex) const;` — Get the supported range of frame rates of the specified video track. @param TrackIndex The index of the track. @param FormatIndex Index of the track format. @return Frame rate range (in frames per second). @see GetVideoTrackAspectRatio, GetVideoTrackDimensions, GetVideoTrackFrameRate, GetVideoTrackType
- L512 _public prototype_ `FString GetVideoTrackType(int32 TrackIndex, int32 FormatIndex) const;` — Get the type of the specified video track format. @param TrackIndex The index of the track. @param FormatIndex Index of the track format. @return Video format type string. @see GetVideoTrackAspectRatio, GetVideoTrackDimensions, GetVideoTrackFrameRate, GetVideoTrackFrameRates
- L522 _public prototype_ `bool GetViewField(float& OutHorizontal, float& OutVertical) const;` — Get the field of view. @param OutHorizontal Will contain the horizontal field of view. @param OutVertical Will contain the vertical field of view. @return true on success, false if feature is not available or if field of view has never been set. @see GetViewOrientation, SetViewField
- L531 _public prototype_ `bool GetViewOrientation(FQuat& OutOrientation) const;` — Get the view's orientation. @param OutOrientation Will contain the view orientation. @return true on success, false if feature is not available or if orientation has never been set. @see GetViewField, SetViewOrientation
- L538 _public prototype_ `bool HasError() const;` — Check whether the player is in an error state. @see IsReady
- L546 _public prototype_ `bool IsBuffering() const;` — Whether the player is currently buffering data. @return true if buffering, false otherwise. @see GetState, IsConnecting, IsLooping
- L554 _public prototype_ `bool IsConnecting() const;` — Whether the player is currently connecting to a media source. @return true if connecting, false otherwise. @see GetState, IsBuffering, IsLooping
- L562 _public prototype_ `bool IsLooping() const;` — Whether playback is looping. @return true if looping, false otherwise. @see GetState, IsBuffering, IsConnecting, SetLooping
- L570 _public prototype_ `bool IsPaused() const;` — Whether playback is currently paused. @return true if playback is paused, false otherwise. @see CanPause, IsPlaying, IsReady, Pause
- L578 _public prototype_ `bool IsPlaying() const;` — Whether playback is in progress. @return true if playback has started, false otherwise. @see CanPlay, IsPaused, IsReady, Play
- L586 _public prototype_ `bool IsPreparing() const;` — Whether the media is currently opening or buffering. @return true if playback is being prepared, false otherwise. @see CanPlay, IsPaused, IsReady, Play
- L593 _public prototype_ `bool IsClosed() const;` — Whether media is currently closed. @return true if media is closed, false otherwise.
- L604 _public prototype_ `bool IsReady() const;` — Whether media is ready for playback. A player is ready for playback if it has a media source opened that finished preparing and is not in an error state. @return true if media is ready, false otherwise. @see HasError, IsPaused, IsPlaying, Stop
- L614 _public prototype_ `bool Open(const FString& Url, const IMediaOptions* Options, const FMediaPlayerOptions* PlayerOptions = nullptr);` — Open a media source from a URL with optional parameters. @param Url The URL of the media to open (file name or web address). @param Options Optional media parameters. @param PlayerOptions Optional player parameters. @return true if the media is being opened, false otherwise.
- L622 _public prototype_ `void QueryCacheState(EMediaTrackType TrackType, EMediaCacheState State, TRangeSet<FTimespan>& OutTimeRanges) const;` — Query the time ranges of cached media samples for the specified caching state. @param State The sample state we're interested in. @param OutTimeRanges Will contain the set of matching sample time ranges.
- L631 _public prototype_ `bool Seek(const FTimespan& Time);` — Seeks to the specified playback time. @param Time The playback time to set. @return true on success, false otherwise. @see GetTime, Rewind
- L637 _public prototype_ `bool IsSeeking() const;` — A seek has been requested, waiting to receive samples. @see Seek
- L643 _public prototype_ `FMediaTimeStamp GetSeekTarget() const;` — If valid, returns the current seek request. @see Seek, IsSeeking
- L649 _public prototype_ `void SetNextSeek(const FTimespan& InTime);` — Set seek to be done after current seek is completed. @remark This value is reset if Seek is called directly.
- L663 _public prototype_ `bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex);` — Select the active track of the given type. The selected track will use its currently active format. Active formats will be remembered on a per track basis. The first available format is active by default. To switch the track format, use SetTrackFormat instead. @param TrackType The type of track to select. @param TrackIndex The index of the track to select, or INDEX_NONE to deselect. @return true if the track was selected, false otherwise. @see GetNumTracks, GetSelectedTrack, SetTrackFormat
- L675 _public prototype_ `void SetBlockOnTime(const FTimespan& Time);` — Set the time on which to block. If set, this player will block in TickFetch until the video sample for the specified time are actually available. @param Time The time to block on, or FTimespan::MinValue to disable. @see TickFetch @note Deprecated: Use SetBlockOnTimeRange instead
- L685 _public prototype_ `void SetBlockOnTimeRange(const TRange<FTimespan>& TimeRange);` — Set the time range on which to block. If set, this player will block in TickFetch until the video sample for the specified time are actually available. @param TimeRange The time range to block on, use empty range to disable
- L693 _public prototype_ `void SetCacheWindow(FTimespan Ahead, FTimespan Behind);` — Set sample caching options. @param Ahead Duration of samples to cache ahead of the play head. @param Behind Duration of samples to cache behind the play head.
- L701 _public prototype_ `void SetGuid(FGuid& Guid);` — Set the player's globally unique identifier. @param Guid The GUID to set. @see GetGuid
- L710 _public prototype_ `bool SetLooping(bool Looping);` — Enables or disables playback looping. @param Looping Whether playback should be looped. @return true on success, false otherwise. @see IsLooping
- L715 _public prototype_ `void SetMediaOptions(const IMediaOptions* Options);` — Changes media ooptions on the player.
- L724 _public prototype_ `bool SetRate(float Rate);` — Changes the media's playback rate. @param Rate The playback rate to set. @return true on success, false otherwise. @see GetRate, SupportsRate
- L739 _public prototype_ `bool SetPlaybackTimeRange(const TRange<FTimespan>& InTimeRange);` — Sets a new media playback range. Has an effect only if SupportsPlaybackTimeRange() returns true and the media supports it. A live stream cannot be constrained to a range. The range will be clamped if necessary to be within the media's absolute time range. Changing the time range may trigger an implicit Seek() depending on where the current playback position is located with regard to the new range. Unless prevented by the media a playback range can be cleared by passing an empty range. @param InTimeRange The new playback range to set. @return true if successful, false otherwise. @see SupportsPlaybackTimeRange, GetPlaybackTimeRange
- L748 _public prototype_ `bool SetNativeVolume(float Volume);` — Changes the media's native volume. @param Rate The volume to set. @return true on success, false otherwise. @see NativeAudioOut
- L763 _public prototype_ `bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex);` — Set the format on the specified track. Selecting the format will not switch to the specified track. To switch tracks, use SelectTrack instead. If the track is already selected, the format change will be applied immediately. @param TrackType The type of track to update. @param TrackIndex The index of the track to update. @param FormatIndex The index of the format to select (must be valid). @return true if the track was selected, false otherwise. @see GetNumTrackFormats, GetNumTracks, GetTrackFormat, SelectTrack
- L774 _public prototype_ `bool SetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex, float FrameRate);` — Set the frame rate of the specified video track. @param TrackIndex The index of the track, or INDEX_NONE for the selected one. @param FormatIndex Index of the track format, or INDEX_NONE for the selected one. @param FrameRate The frame rate to set (must be in range of format's supported frame rates). @return true on success, false otherwise. @see GetVideoTrackAspectRatio, GetVideoTrackDimensions, GetVideoTrackFrameRate, GetVideoTrackFrameRates, GetVideoTrackType
- L785 _public prototype_ `bool SetViewField(float Horizontal, float Vertical, bool Absolute);` — Set the field of view. @param Horizontal Horizontal field of view (in Euler degrees). @param Vertical Vertical field of view (in Euler degrees). @param Whether the field of view change should be absolute (true) or relative (false). @return true on success, false otherwise. @see GetViewField, SetViewOrientation
- L795 _public prototype_ `bool SetViewOrientation(const FQuat& Orientation, bool Absolute);` — Set the view's orientation. @param Orientation Quaternion representing the orientation. @param Whether the orientation change should be absolute (true) or relative (false). @return true on success, false otherwise. @see GetViewOrientation, SetViewField
- L804 _public prototype_ `bool SupportsRate(float Rate, bool Unthinned) const;` — Whether the specified playback rate is supported. @param Rate The playback rate to check. @param Unthinned Whether no frames should be dropped at the given rate. @see CanScrub, CanSeek
- L812 _public prototype_ `void SetLastAudioRenderedSampleTime(FTimespan SampleTime);` — Record last audio sample played to track audio sync (for automated tests) @param SampleTime Time of media sample currently being played @return true if playback is being prepared, false otherwise.
- L819 _public prototype_ `FTimespan GetLastAudioRenderedSampleTime() const;` — Get time of last audio sample played @return Time of last audio sample played.
- L826 _public prototype_ `void SetAreEventsSafeForAnyThread(bool bInAreEventsSafeForAnyThread);` — Sets whether the player can broadcast events when running on a thread other than the game thread. @param bInAreEventsSafeForAnyThread If true then allow broadcast when not on the game thread.
- L831 _public function_ `DECLARE_EVENT_OneParam(FMediaPlayerFacade, FOnMediaEvent, EMediaEvent ) FOnMediaEvent& OnMediaEvent()` — Get an event delegate that is invoked when a media event occurred.
- L841 _public prototype_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode) override;`
- L842 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L843 _public prototype_ `virtual void TickOutput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L849 _public prototype_ `virtual void TickTickable() override;`
- L858 _protected prototype_ `bool BlockOnFetch() const;` — Whether sample fetching should block. @return true if sample fetching should block, false otherwise.
- L861 _protected prototype_ `void Flush(bool bExcludePlayer = false, bool bOnSeek = false);` — Flush all media sample sinks & player plugin.
- L864 _protected prototype_ `FMediaTimeStamp GetTimeStampInternal(bool bForDisplay) const;` — Internal function to retrieve the current timestamp
- L875 _protected prototype_ `bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const;` — Get details about the specified audio track format. @param TrackIndex The index of the audio track. @param FormatIndex The index of the track's format. @param OutFormat Will contain the format details. @return true on success, false otherwise. @see GetVideoTrackFormat
- L884 _protected prototype_ `IMediaPlayerFactory *GetPlayerFactoryForUrl(const FString& Url, const IMediaOptions* Options) const;` — Get a player that can play the specified media URL. @param Url The URL to play. @param Options The media options for the URL. @return The player if found, or nullptr otherwise.
- L895 _protected prototype_ `bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const;` — Get details about the specified audio track format. @param TrackIndex The index of the audio track. @param FormatIndex The index of the track's format. @param OutFormat Will contain the format details. @return true on success, false otherwise. @see GetVideoTrackFormat
- L903 _protected prototype_ `void ProcessEvent(EMediaEvent Event, bool bIsBroadcastAllowed);` — Process the given media event. @param Event The event to process. @param bIsBroadcastAllowed If true then we can broadcast events, if false then they will sent when possible.
- L910 _private member_ `} TrackSelection;`
- L913 _private prototype_ `void ResetTracks();` — Reset all tracks.
- L916 _private prototype_ `void UpdateTrackSelectionWithPlayer();` — Setup track selection with player.
- L919 _private prototype_ `void SelectDefaultTracks();` — Select the default media tracks.
- L922 _protected prototype_ `bool HaveAudioPlayback() const;`
- L923 _protected prototype_ `bool HaveVideoPlayback() const;`
- L924 _protected prototype_ `float GetUnpausedRate() const;`
- L931 _protected prototype_ `void ReceiveMediaEvent(EMediaEvent Event) override;`
- L937 _private prototype_ `bool NotifyLifetimeManagerDelegate_PlayerOpen(IMediaPlayerLifecycleManagerDelegate::IControlRef& NewLifecycleManagerDelegateControl, const FString& InUrl, const IMediaOptions* Options, const FMediaPlayerOptions* InPlayerOptions, IMediaPlayerFactory* PlayerFactory, bool bWillCreatePlayer, uint32 WillUseNewResources, uint64 NewPlayerInstanceID);` — Internal
- L938 _private prototype_ `bool NotifyLifetimeManagerDelegate_PlayerCreated();`
- L939 _private prototype_ `bool NotifyLifetimeManagerDelegate_PlayerCreateFailed();`
- L940 _private prototype_ `bool NotifyLifetimeManagerDelegate_PlayerClosed();`
- L941 _private prototype_ `bool NotifyLifetimeManagerDelegate_PlayerDestroyed();`
- L942 _private prototype_ `bool NotifyLifetimeManagerDelegate_PlayerResourcesReleased(uint32 ResourceFlags);`
- L944 _private prototype_ `void ProcessAudioSamples(IMediaSamples& Samples, const TRange<FMediaTimeStamp>& TimeRange);`
- L945 _private prototype_ `bool ProcessVideoSamples(IMediaSamples& Samples, const TRange<FMediaTimeStamp>& TimeRange);`
- L946 _private prototype_ `void ProcessCaptionSamples(IMediaSamples& Samples, const TRange<FMediaTimeStamp>& TimeRange);`
- L947 _private prototype_ `void ProcessSubtitleSamples(IMediaSamples& Samples, const TRange<FMediaTimeStamp>& TimeRange);`
- L948 _private prototype_ `void ProcessMetadataSamples(IMediaSamples& Samples, const TRange<FMediaTimeStamp>& TimeRange);`
- L950 _private prototype_ `void ProcessAudioSamplesV1(IMediaSamples& Samples, TRange<FTimespan> TimeRange);`
- L951 _private prototype_ `void ProcessVideoSamplesV1(IMediaSamples& Samples, TRange<FTimespan> TimeRange);`
- L952 _private prototype_ `void ProcessSubtitleSamplesV1(IMediaSamples& Samples, TRange<FTimespan> TimeRange);`
- L953 _private prototype_ `void ProcessCaptionSamplesV1(IMediaSamples& Samples, TRange<FTimespan> TimeRange);`
- L954 _private prototype_ `void ProcessMetadataSamplesV1(IMediaSamples& Samples, TRange<FTimespan> TimeRange);`
- L956 _private prototype_ `bool IsVideoSampleStillGood(const TRange<FMediaTimeStamp>& LastSampleTimeRange, const TRange<FMediaTimeStamp>& TimeRange, bool bReverse) const;`
- L957 _private prototype_ `void MonitorAudioEnablement();`
- L958 _private prototype_ `void UpdateSeekStatus(const FMediaTimeStamp* pCheckTimeStamp = nullptr);`
- L959 _private prototype_ `void ExecuteNextSeek();`
- L960 _private prototype_ `void PrepareSampleQueueForSequenceIndex();`
- L961 _private prototype_ `void PreSampleProcessingTimeHandling();`
- L962 _private prototype_ `bool GetCurrentPlaybackTimeRange(TRange<FMediaTimeStamp>& TimeRange, float Rate, FTimespan DeltaTime, bool bPurgeSampleRelated) const;`
- L963 _private prototype_ `void PostSampleProcessingTimeHandling(FTimespan DeltaTime);`
- L965 _private prototype_ `void DestroyPlayer();`
- L967 _private prototype_ `bool ContinueOpen(IMediaPlayerLifecycleManagerDelegate::IControlRef NewLifecycleManagerDelegateControl, const FString& Url, const IMediaOptions* Options, const FMediaPlayerOptions* PlayerOptions, IMediaPlayerFactory* PlayerFactory, TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> ReusedPlayer, bool bCreateNewPlayer, uint64 NewPlayerInstanceID);`
- L969 _private prototype_ `void SendSinkEvent(EMediaSampleSinkEvent Event, const FMediaSampleSinkEventData& Data);`
- L972 _private member_ `TWeakPtr<FMediaAudioSampleSink, ESPMode::ThreadSafe> PrimaryAudioSink;` — Audio sample sinks.
- L973 _private member_ `FMediaAudioSampleSinks AudioSampleSinks;`
- L976 _private member_ `FMediaOverlaySampleSinks CaptionSampleSinks;` — Caption sample sinks.
- L979 _private member_ `FMediaBinarySampleSinks MetadataSampleSinks;` — Metadata sample sinks.
- L982 _private member_ `FMediaOverlaySampleSinks SubtitleSampleSinks;` — Subtitle sample sinks.
- L985 _private member_ `FMediaVideoSampleSinks VideoSampleSinks;` — Video sample sinks.
- L988 _private prototype_ `TRange<FMediaTimeStamp> GetAdjustedBlockOnRange() const;`
- L990 _private prototype_ `TRange<FTimespan> GetActivePlaybackRange() const;`
- L991 _private prototype_ `void ReInit();`
- L1039 _private member_ `FBlockOnRange BlockOnRange;`
- L1043 _private member_ `bool BlockOnRangeDisabled;` — Flag to indicate block on range feature as disabled for the current playback session due to previous timeout
- L1046 _private member_ `FMediaSampleCache* Cache;` — Media sample cache.
- L1049 _private member_ `FCriticalSection CriticalSection;` — Synchronizes access to Player.
- L1052 _private member_ `FString CurrentUrl;` — The URL of the currently loaded media source.
- L1055 _private member_ `float LastRate;` — The last used non-zero play rate (zero if playback never started).
- L1058 _private member_ `float CurrentRate;` — The last rate set with the facade (unfiltered by player).
- L1061 _private member_ `bool bHaveActiveAudio;` — Flag indicating that we have an active audio setup
- L1064 _private member_ `int32 VideoSampleAvailability;` — Flag indicating the current availability of media samples.
- L1065 _private member_ `int32 AudioSampleAvailability;`
- L1068 _private member_ `FOnMediaEvent MediaEvent;` — An event delegate that is invoked when a media event occurred.
- L1071 _private member_ `FTimespan NextVideoSampleTime;` — Time of the next expected video sample (used for block on fetch).
- L1074 _private member_ `TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> Player;` — The low-level player used to play the media source.
- L1077 _private member_ `uint64 PlayerInstanceID = ~0;` — Low level player instance ID
- L1080 _private member_ `bool PlayerUsesResourceReleaseNotification = false;` — Low level player will use callback to notify of resource release
- L1083 _private member_ `FGuid PlayerGuid;` — Media player Guid
- L1086 _private member_ `TQueue<EMediaEvent, EQueueMode::Mpsc> QueuedEvents;` — Media player event queue.
- L1089 _private member_ `TQueue<EMediaEvent, EQueueMode::Spsc> QueuedEventBroadcasts;` — Queue to hold events that we could not broadcast yet.
- L1092 _private member_ `mutable FCriticalSection TimeValueLock;` — CS to make last time values below thread safe
- L1095 _private member_ `FMediaTimeStampSample LastAudioRenderedSampleTime;` — Time of last audio sample played.
- L1098 _private member_ `FMediaTimeStampSample LastAudioSampleProcessedTime;` — Time of last audio sample decoded.
- L1101 _private member_ `TRange<FMediaTimeStamp> LastVideoSampleProcessedTimeRange;` — Time/Range of last video sample decoded.
- L1104 _private member_ `FMediaTimeStamp CurrentFrameAudioTimeStamp;` — Timestamp for audio considered "current" for this frame (use ONLY for return to outside code)
- L1107 _private member_ `FMediaTimeStamp CurrentFrameVideoTimeStamp;` — Timestamp for video considered "current" for this frame (stays valid even after a flush, until new data comes in)
- L1110 _private member_ `FMediaTimeStamp CurrentFrameVideoDisplayTimeStamp;` — Timestamp for video considered "current" for this frame for GUI / display purposes (stays valid even after a flush, until new data comes in)
- L1113 _private member_ `FMediaTimeStampSample NextEstVideoTimeAtFrameStart;` — Estimation for next frame's video timestamp (used when no audio present or active in stream)
- L1116 _private member_ `TOptional<FTimecode> MostRecentlyDeliveredVideoFrameTimecode;` — Timecode of the video frame most recently delivered to the video sinks
- L1119 _private member_ `FMediaTimeStamp SeekTargetTime;` — Timestamp of seek target location if seek is pending
- L1122 _private member_ `TOptional<FTimespan> NextSeekTime;` — When multiple consecutive seek are issued while seeking, we keep track of the most recent request.
- L1125 _private member_ `TOptional<int32> NextSequenceIndex;` — The next sequence index value we expect to see on the samples provided by a v2 timing enabled player.
- L1128 _private member_ `bool bDidRecentPlayerHaveError;` — Latch for error state of the most recently used player to be queried after it may have been closed.
- L1131 _private member_ `bool bAreEventsSafeForAnyThread;` — If true, then we can send out events even if we are not on the game thread.
- L1134 _private member_ `IMediaModule* MediaModule;` — Mediamodule we are working in
- L1137 _private member_ `TWeakObjectPtr<UMediaPlayer> MediaPlayer;` — UMediaplayer we are working with
- L1140 _private member_ `IMediaPlayerLifecycleManagerDelegate::IControlRef LifecycleManagerDelegateControl;` — Control interface for lifecycle manager delegate

#### struct `FMediaPlayerFacade::FTrackSelection`  
`struct FTrackSelection`  
_L906-910_
- L908 _public member_ `int32 UserSelection[(int32)EMediaTrackType::Num];`
- L909 _public member_ `int32 PlayerSelection[(int32)EMediaTrackType::Num];`

#### class `FMediaPlayerFacade::FBlockOnRange`  
`class FBlockOnRange`  
_L993-1037_
- L996 _public function_ `FBlockOnRange(FMediaPlayerFacade* InFacade) : Facade(InFacade)`
- L998 _public prototype_ `void SetRange(const TRange<FTimespan> & NewRange);`
- L1000 _public prototype_ `const TRange<FMediaTimeStamp> & GetRange() const;`
- L1001 _public prototype_ `bool IsSet() const;`
- L1003 _public prototype_ `void OnFlush();`
- L1004 _public prototype_ `void OnSeek(int32 PrimaryIndex);`
- L1006 _public function_ `void Reset()`
- L1018 _private member_ `FMediaPlayerFacade* Facade;` — The hosting player facade
- L1021 _private member_ `TRange<FTimespan> CurrentTimeRange;` — The most recently set time range to block on
- L1024 _private member_ `mutable TRange<FTimespan> LastProcessedTimeRange;` — Last user provided BlockOnRange value
- L1027 _private member_ `mutable TRange<FMediaTimeStamp> BlockOnRange;` — The time range to block on sample fetching.
- L1030 _private member_ `mutable bool RangeIsDirty;` — Flag to indicate if internal range is valid or not
- L1033 _private member_ `mutable int32 OnBlockSequenceIndex;` — Primary ("seek") sequence index used during blocked playback processing
- L1036 _private member_ `mutable int32 OnBlockLoopIndexOffset;` — Secondary (loop) sequence index offset used during blocked playback processing

#### Free symbols / members of external scopes

- L831 _delegate_ `DECLARE_EVENT_OneParam(FMediaPlayerFacade, FOnMediaEvent, EMediaEvent ) FOnMediaEvent& OnMediaEvent() { return MediaEvent; } public:` — Get an event delegate that is invoked when a media event occurred.

### `Source/Runtime/MediaUtils/Public/MediaPlayerOptions.h` (Public)


#### enum `EMediaPlayerOptionBooleanOverride`  
`enum class EMediaPlayerOptionBooleanOverride : uint8`  
_L14-19_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `UseMediaPlayerSetting`
- L17 _public enumerator_ `Enabled`
- L18 _public enumerator_ `Disabled`

#### enum `EMediaPlayerOptionSeekTimeType`  
`enum class EMediaPlayerOptionSeekTimeType : uint8`  
_L23-29_
- reflection: `UENUM(BlueprintType)`
- L26 _public enumerator_ `Ignored` — Ignore the given value and lets the media player choose.
- L28 _public enumerator_ `RelativeToStartTime` — Given seek time is relative to the start of the media.

#### enum `EMediaPlayerOptionTrackSelectMode`  
`enum class EMediaPlayerOptionTrackSelectMode : uint8`  
_L33-41_
- reflection: `UENUM(BlueprintType)`
- L36 _public enumerator_ `UseMediaPlayerDefaults UMETA(DisplayName="Media player selects default tracks")` — Let the media player choose defaults.
- L38 _public enumerator_ `UseTrackOptionIndices UMETA(DisplayName="Uses provided track indices")` — Use fixed track indices as specified with MediaPlayerTrackOptions
- L40 _public enumerator_ `UseLanguageCodes UMETA(DisplayName="Use provided language codes or have media player select defaults when there is no match")` — Use language codes as specified with MediaPlayerInitialTrackLanguageSelection

#### struct `FMediaPlayerTrackOptions`  
`struct FMediaPlayerTrackOptions`  
_L45-92_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public function_ `FMediaPlayerTrackOptions() : Audio(0), Caption(-1), Metadata(-1), Script(-1), Subtitle(-1), Text(-1), Video(0)`
- L61 _public function_ `bool operator!=(const FMediaPlayerTrackOptions& Other) const` — Check if this Media Player Track Options is not equal to another one.
- L73 _public member_ `int32 Audio;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks")`
- L76 _public member_ `int32 Caption;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks")`
- L79 _public member_ `int32 Metadata;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks")`
- L82 _public member_ `int32 Script;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks")`
- L85 _public member_ `int32 Subtitle;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks")`
- L88 _public member_ `int32 Text;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks")`
- L91 _public member_ `int32 Video;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks")`

#### struct `FMediaPlayerInitialTrackLanguageSelection`  
`struct FMediaPlayerInitialTrackLanguageSelection`  
_L96-121_
- reflection: `USTRUCT(BlueprintType)`
- L100 _public function_ `FMediaPlayerInitialTrackLanguageSelection()`
- L103 _public function_ `bool operator!=(const FMediaPlayerInitialTrackLanguageSelection& Other) const`
- L108 _public member_ `FString Video;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks", meta=(ToolTip="Comma separated RFC 4647 language ranges in order of priority, or keep empty for default."))` — Language code or codes of the video track to select. Useful when the video contains burned-in subtitles or localized scenes.
- L112 _public member_ `FString Audio;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks", meta=(ToolTip="Comma separated RFC 4647 language ranges in order of priority, or keep empty for default."))` — Language code or codes of the audio track to select.
- L116 _public member_ `FString Subtitle;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks", meta=(ToolTip="Comma separated RFC 4647 language ranges in order of priority, or keep empty for default."))` — Language code or codes of the subtitle track to select.
- L120 _public member_ `FString Caption;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks", meta=(ToolTip="Comma separated RFC 4647 language ranges in order of priority, or keep empty for default."))` — Language code or codes of the caption track to select. Captions may not provide language codes if carried in the video signal.

#### struct `FMediaPlayerOptions`  
`struct FMediaPlayerOptions`  
_L124-189_
- reflection: `USTRUCT(BlueprintType)`
- L128 _public function_ `FMediaPlayerOptions() : TrackSelection(EMediaPlayerOptionTrackSelectMode::UseTrackOptionIndices), SeekTime(0), SeekTimeType(EMediaPlayerOptionSeekTimeType::RelativeToStartTime), PlayOnOpen(EMediaPlayerOptionBooleanOverride::UseMediaPlayerSetting), Loop(EMediaPlayerOptionBooleanOverride::UseMediaPlayerSetting)`
- L137 _public function_ `void SetAllAsOptional()`
- L147 _public function_ `bool operator!=(const FMediaPlayerOptions& Other) const` — Check if this Media Options is not equal to another one.
- L160 _public member_ `FMediaPlayerTrackOptions Tracks;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks", meta=(DisplayName="Initial track indices", ToolTip="Indices of the media tracks to select for playback", EditCondition="TrackSelection==EMediaPlayerOptionTrackSelectMode::UseTrackOptionIndices"))` — Fixed indices of media tracks to select.
- L164 _public member_ `FMediaPlayerInitialTrackLanguageSelection TracksByLanguage;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks", meta=(DisplayName="Initial track language", ToolTip="Language of the media tracks to select for playback", EditCondition="TrackSelection==EMediaPlayerOptionTrackSelectMode::UseLanguageCodes"))` — Track selection by language. Not supported by all media players.
- L168 _public member_ `EMediaPlayerOptionTrackSelectMode TrackSelection;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tracks", meta=(DisplayName="Initial track selection mode", ToolTip="How the initial media tracks for playback are selected"))` — How to select the initial media tracks.
- L172 _public member_ `FTimespan SeekTime;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Misc", meta=(EditCondition="SeekTimeType!=EMediaPlayerOptionSeekTimeType::Ignored"))` — Initial media time to start playback at.
- L176 _public member_ `EMediaPlayerOptionSeekTimeType SeekTimeType;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Misc", meta=(DisplayName="Seek time interpretation"))` — How to interpret the initial seek time.
- L180 _public member_ `EMediaPlayerOptionBooleanOverride PlayOnOpen;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Misc")` — How to handle automatic playback when media opens.
- L184 _public member_ `EMediaPlayerOptionBooleanOverride Loop;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Misc")` — How to initially select looping of the media.
- L188 _public member_ `TMap<FName, FVariant> InternalCustomOptions;` — Custom options used internally. Must not be serialized or editable via blueprint.

#### Free symbols / members of external scopes

- L191 _namespace_ `namespace MediaPlayerOptionValues`
- L193 _function_ `inline const FName& Environment()` (scope `MediaPlayerOptionValues`)
- L195 _function_ `inline const FName& Environment_Sequencer()` (scope `MediaPlayerOptionValues`)
- L197 _function_ `inline const FName& Environment_Preview()` (scope `MediaPlayerOptionValues`)
- L200 _function_ `inline const FName& ImgMediaSmartCacheEnabled()` (scope `MediaPlayerOptionValues`)
- L202 _function_ `inline const FName& ImgMediaSmartCacheTimeToLookAhead()` (scope `MediaPlayerOptionValues`)
- L209 _function_ `inline const FName& ViewMediaTexture()` (scope `MediaPlayerOptionValues`) — Option to specify a view media texture (as a soft object path string) to allow players supporting mips and tiles to preload only the required set for the given texture.
- L215 _function_ `inline const FName& ParseTimecodeInfo()` (scope `MediaPlayerOptionValues`) — Requests parsing timecode meta data if available.

### `Source/Runtime/MediaUtils/Public/MediaRecorder.h` (Public)


#### class `FMediaRecorder`  
`class FMediaRecorder`  
_L23-128_
- desc: Records samples from a media player. Loop, seek or reverse and not supported. Currently only records texture samples and that support sample format 8bit BGRA, half float RBGA
- L28 _public prototype_ `FMediaRecorder();` — Default constructor.
- L73 _public prototype_ `void StartRecording(const FMediaRecorderData& InRecoderData);` — Start recording samples from a given media player.
- L78 _public prototype_ `void StopRecording();` — Stop recording media samples.
- L83 _public function_ `bool IsRecording() const` — Is currently recording media samples.
- L88 _public prototype_ `bool WaitPendingTasks(const FTimespan& InDuration);` — Blocking call that will wait for all frames to be recorded before returning.
- L97 _protected prototype_ `void TickRecording();` — Tick the recorder. @param Timecode The current timecode.
- L104 _private member_ `TSharedPtr<FMediaRecorderClockSink, ESPMode::ThreadSafe> ClockSink;` — The recorder's media clock sink.
- L107 _private member_ `TSharedPtr<FMediaTextureSampleQueue, ESPMode::ThreadSafe> SampleQueue;` — Texture sample queue.
- L110 _private member_ `bool bRecording;` — Whether recording is in progress.
- L113 _private member_ `bool bUnsupportedWarningShowed;` — Warning for unsupported format have been showed.
- L116 _private member_ `int32 FrameCount;` — Number of frames recorded.
- L119 _private member_ `FString BaseFilename;` — Media Recorder Data saved options.
- L120 _private member_ `EMediaRecorderNumerationStyle NumerationStyle;`
- L121 _private member_ `EImageFormat TargetImageFormat;`
- L122 _private member_ `bool bSetAlpha;`
- L123 _private member_ `int32 CompressionQuality;`
- L126 _private member_ `IImageWriteQueue* ImageWriteQueue;` — The image writer.
- L127 _private member_ `TFuture<void> CompletedFence;`

#### enum `FMediaRecorder::EMediaRecorderNumerationStyle`  
`enum class EMediaRecorderNumerationStyle`  
_L32-36_
- L34 _public enumerator_ `AppendFrameNumber`
- L35 _public enumerator_ `AppendSampleTime`

#### struct `FMediaRecorder::FMediaRecorderData`  
`struct FMediaRecorderData`  
_L38-66_
- L41 _public member_ `TSharedRef<FMediaPlayerFacade, ESPMode::ThreadSafe> PlayerFacade;` — The media player facade to record from.
- L43 _public member_ `FString BaseFilename;` — BaseFilename(including with path and filename) for each recorded frames.
- L45 _public member_ `EMediaRecorderNumerationStyle NumerationStyle;` — How to numerate the filename.
- L47 _public member_ `EImageFormat TargetImageFormat;` — The format to save the image to.
- L49 _public member_ `bool bResetAlpha;` — If the format support it, set the alpha to 1 (or 255)
- L55 _public member_ `int32 CompressionQuality;` — An image format specific compression setting. For EXRs, either 0 (Default) or 1 (Uncompressed) For others, a value between 1 (worst quality, best compression) and 100 (best quality, worst compression)
- L57 _public function_ `FMediaRecorderData(const TSharedRef<FMediaPlayerFacade, ESPMode::ThreadSafe>& InPlayerFacade, const FString& InBaseFilename) : PlayerFacade(InPlayerFacade) , BaseFilename(InBaseFilename) , NumerationStyle(EMediaRecorderNumerationStyle::AppendSampleTime) , TargetImageFormat(EImageFormat::EXR) , bResetAlpha(false) , CompressionQuality(0)`

### `Source/Runtime/MediaUtils/Public/MediaSampleCache.h` (Public)


#### class `FMediaSampleCache`  
`class FMediaSampleCache`  
_L30-168_
- desc: Implements a cache for media samples.
- L55 _private typedef_ `template<typename SampleType> using TSampleSet = TSet<TSharedPtr<SampleType, ESPMode::ThreadSafe>, TSampleKeyFuncs<SampleType>>;` — Template for sample cache sets.
- L60 _public prototype_ `FMediaSampleCache();` — Default constructor.
- L69 _public prototype_ `void Empty();` — Empty the cache. @see Update
- L80 _public prototype_ `TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe> GetAudioSample(FTimespan Time);` — Get the audio sample for the specified play time. This method returns the sample that contains the specified time code. @param Time The time to get the sample for (in the player's clock). @return The sample, or nullptr if no sample available. @see GetAudioSamples, GetCachedVideoSampleRanges, GetOverlaySamples
- L88 _public prototype_ `void GetCachedAudioSampleRanges(TRangeSet<FTimespan>& OutTimeRanges) const;` — Get the time ranges of audio samples currently in the cache. @param OutTimeRanges Will contain the set of cached sample time ranges. @see GetAudioSample, GetCachedVideoSampleRanges
- L96 _public prototype_ `void GetCachedVideoSampleRanges(TRangeSet<FTimespan>& OutTimeRanges) const;` — Get the time ranges of video samples currently in the cache. @param OutTimeRanges Will contain the set of cached sample time ranges. @see GetCachedAudioSampleRanges, GetVideoSample
- L105 _public prototype_ `void GetOverlaySamples(FTimespan Time, TArray<TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>>& OutSamples);` — Get the text overlay samples for the specified time. @param Time The time to get the sample for (in the player's clock). @param OutSamples Will contain the overlay samples. @see GetAudioSample, GetVideoSample
- L119 _public prototype_ `TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe> GetVideoSample(FTimespan Time, bool Forward);` — Get the video sample for the specified play time. This method will return the closest match for the given time code. If the current play rate is positive, the closest sample with an equal or older time is returned. If the current rate is negative, the closest sample with an equal or newer time is returned. @param Time The time to get the sample for (in the player's clock). @param Forward Whether the play direction is forward (true) or backward (false). @return The sample, or nullptr if no sample available. @see GetAudioSample, GetCachedVideoSampleRanges, GetOverlaySamples
- L127 _public function_ `void SetCacheWindow(FTimespan Ahead, FTimespan Behind)` — Set the time window of samples to cache. @param Ahead Maximum time of samples to cache ahead of the play position. @param Behind Maximum time of samples to cache behind the play position.
- L144 _public prototype_ `void Tick(FTimespan DeltaTime, float Rate, FTimespan Time);` — Tick the cache. This method fetches any unconsumed media samples from the player and removes expired samples from the cache. @param DeltaTime Time since the last tick. @param Rate The current play rate. @param Time The current play time. @see Initialize, Shutdown
- L149 _private member_ `TSampleSet<IMediaAudioSample> AudioSamples;` — Cached audio samples.
- L152 _private member_ `TSampleSet<IMediaBinarySample> MetadataSamples;` — Cached metadata samples.
- L155 _private member_ `TSampleSet<IMediaOverlaySample> OverlaySamples;` — Cached overlay samples.
- L158 _private member_ `TSampleSet<IMediaTextureSample> VideoSamples;` — Cached video samples.
- L162 _private member_ `FTimespan CacheAhead;`
- L164 _private member_ `FTimespan CacheBehind;`
- L167 _private member_ `mutable FCriticalSection CriticalSection;` — Synchronizes access to sample collections.

#### struct `FMediaSampleCache::TSampleKeyFuncs`  
`template<typename SampleType> struct TSampleKeyFuncs : BaseKeyFuncs<TSharedPtr<SampleType, ESPMode::ThreadSafe>, FTimespan, false>`  
_L34-51_
- inherits: `BaseKeyFuncs<TSharedPtr<SampleType,ESPMode::ThreadSafe>,FTimespan,false>`
- desc: Key functions template for the sample cache sets.
- L37 _public function_ `static inline FTimespan GetSetKey(const TSharedPtr<SampleType, ESPMode::ThreadSafe>& Element)`
- L42 _public function_ `static inline bool Matches(FTimespan A, FTimespan B)`
- L47 _public function_ `static inline uint32 GetKeyHash(FTimespan Key)`

### `Source/Runtime/MediaUtils/Public/MediaSampleQueue.h` (Public)


#### enum `EMediaSampleQueueFetchResult`  
`enum class EMediaSampleQueueFetchResult`  
_L25-30_
- L27 _public enumerator_ `Found`
- L28 _public enumerator_ `None`
- L29 _public enumerator_ `PurgedToEmpty`

#### class `TMediaSampleQueue`  
`template<typename SampleType, typename SinkType=TMediaSampleSink<SampleType>> class TMediaSampleQueue : public SinkType , public TMediaSampleSource<SampleType>`  
_L36-450_
- inherits: `SinkType,TMediaSampleSource<SampleType>`
- desc: Template for media sample queues.
- L42 _public function_ `TMediaSampleQueue(int32 InMaxSamplesInQueue = -1) : MaxSamplesInQueue(InMaxSamplesInQueue)`
- L47 _public prototype_ `virtual ~TMediaSampleQueue() = default;` — Virtual destructor.
- L61 _public function_ `int32 Num() const` — Get the number of samples in the queue. Note: The value returned by this function is only eventually consistent. It can be called by both consumer and producer threads, but it should not be used to query the actual state of the queue. Always use Dequeue and Peek instead! @return Number of samples. @see Enqueue, Dequeue, Peek
- L74 _public function_ `uint32 GetNumDroppedSamples(bool bInClearToZero)` — Returns the number of samples that were dropped in any of the member functions. This is only for tracking statistics and may not necessarily be accurate. The count is never implicitly cleared by any member function. To clear it call with bInClearToZero set to true. @return Number of samples that were dropped.
- L88 _public function_ `virtual bool Dequeue(TSharedPtr<SampleType, ESPMode::ThreadSafe>& OutSample) override`
- L111 _public function_ `virtual bool Peek(TSharedPtr<SampleType, ESPMode::ThreadSafe>& OutSample) override`
- L132 _public function_ `virtual void GetSampleTimes(TArray<TRange<FMediaTimeStamp>>& OutSampleTimeRanges) override`
- L144 _public function_ `virtual bool Pop() override`
- L163 _public function_ `bool Discard(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse)`
- L187 _public function_ `EMediaSampleQueueFetchResult FetchBestSampleForTimeRange(const TRange<FMediaTimeStamp>& TimeRange, TSharedPtr<SampleType, ESPMode::ThreadSafe>& OutSample, bool bReverse, bool bConsistentResult)`
- L301 _public function_ `uint32 PurgeOutdatedSamples(const FMediaTimeStamp& ReferenceTime, bool bReversed, FTimespan MaxAge)`
- L348 _public function_ `void PurgeUntilSequenceIndex(int32 InUntilIndex)`
- L362 _public function_ `virtual bool Enqueue(const TSharedRef<SampleType, ESPMode::ThreadSafe>& Sample) override`
- L375 _public function_ `virtual void RequestFlush() override`
- L382 _public function_ `virtual uint32 GetFlushCount() const`
- L388 _public function_ `virtual bool CanAcceptSamples(int32 NumSamples) const override`
- L394 _protected function_ `void FindRangeInQueue(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse, int32& FirstPossibleIndex, int32& LastPossibleIndex, int32& NumOldSamplesAtBegin)`
- L445 _protected member_ `mutable FCriticalSection CriticalSection;`
- L446 _protected member_ `TArray<TSharedPtr<SampleType, ESPMode::ThreadSafe>> Samples;`
- L447 _protected member_ `int32 MaxSamplesInQueue;`
- L448 _protected member_ `uint32 FlushCount = 0;`
- L449 _protected member_ `uint32 NumDroppedSamples = 0;`

#### class `FMediaAudioSampleQueue`  
`class FMediaAudioSampleQueue : public TMediaSampleQueue<class IMediaAudioSample, class FMediaAudioSampleSink>`  
_L454-496_
- inherits: `TMediaSampleQueue<classIMediaAudioSample,classFMediaAudioSampleSink>`
- desc: audio sample queue.
- L457 _public function_ `FMediaAudioSampleQueue(uint32 MaxSamplesInQueue = -1) : TMediaSampleQueue<class IMediaAudioSample, class FMediaAudioSampleSink>(MaxSamplesInQueue)`
- L461 _public function_ `void SetAudioTime(const FMediaTimeStampSample& InAudioTime)`
- L467 _public function_ `void SetAudioTimeIfEqualFlushCount(const FMediaTimeStampSample& InAudioTime, uint32 InFlushCount)`
- L476 _public function_ `FMediaTimeStampSample GetAudioTime() const override`
- L482 _public function_ `void InvalidateAudioTime() override`
- L488 _public function_ `virtual void RequestFlush() override`
- L495 _private member_ `FMediaTimeStampSample AudioTime;`

#### Free symbols / members of external scopes

- L499 _typedef_ `typedef TMediaSampleQueue<class IMediaBinarySample> FMediaBinarySampleQueue;` — Type definition for binary sample queue.
- L502 _typedef_ `typedef TMediaSampleQueue<class IMediaOverlaySample> FMediaOverlaySampleQueue;` — Type definition for overlay sample queue.
- L505 _typedef_ `typedef TMediaSampleQueue<class IMediaTextureSample> FMediaTextureSampleQueue;` — Type definition for texture sample queue.

### `Source/Runtime/MediaUtils/Public/MediaSampleQueueDepths.h` (Public)


#### struct `FMediaPlayerQueueDepths`  
`struct FMediaPlayerQueueDepths`  
_L10-17_
- desc: Legacy player output queue depth maximums @note These are not used inside MediaFramework and are meant to support older player sources code only.
- L12 _public member_ `static const int32 MaxAudioSinkDepth = 512;`
- L13 _public member_ `static const int32 MaxCaptionSinkDepth = 256;`
- L14 _public member_ `static const int32 MaxMetadataSinkDepth = 256;`
- L15 _public member_ `static const int32 MaxSubtitleSinkDepth = 256;`
- L16 _public member_ `static const int32 MaxVideoSinkDepth = 8;`

### `Source/Runtime/MediaUtils/Public/MediaSampleSink.h` (Public)


#### enum `EMediaSampleSinkEvent`  
`enum class EMediaSampleSinkEvent`  
_L15-25_
- desc: Events send from player to sink
- L17 _public enumerator_ `Attached` — Attached to a UMediaPlayer
- L18 _public enumerator_ `Detached` — Detached from a UMediaPlayer
- L19 _public enumerator_ `PlayerPluginChange` — Player plugin used changed
- L20 _public enumerator_ `SampleDataUpdate` — Sample data was updated
- L21 _public enumerator_ `FlushWasRequested` — Flush has been requested
- L22 _public enumerator_ `MediaClosed` — Media has been closed
- L23 _public enumerator_ `PlaybackEndReached` — End of playback has been reached
- L24 _public enumerator_ `PlaybackRateChanged` — Rate of playback changed

#### struct `FMediaSampleSinkEventData`  
`struct FMediaSampleSinkEventData`  
_L27-63_

#### union `FMediaSampleSinkEventData::(anonymous)`  
`union`  
_L29-62_

#### struct `FMediaSampleSinkEventData::__anon87b33d24010a::(anonymous)`  
``  
_L31-33_

#### struct `FMediaSampleSinkEventData::__anon87b33d24010a::(anonymous)`  
``  
_L35-37_

#### struct `FMediaSampleSinkEventData::__anon87b33d24010a::(anonymous)`  
``  
_L39-41_

#### struct `FMediaSampleSinkEventData::__anon87b33d24010a::(anonymous)`  
``  
_L43-45_

#### struct `FMediaSampleSinkEventData::__anon87b33d24010a::(anonymous)`  
``  
_L47-49_

#### struct `FMediaSampleSinkEventData::__anon87b33d24010a::(anonymous)`  
``  
_L51-53_

#### struct `FMediaSampleSinkEventData::__anon87b33d24010a::(anonymous)`  
``  
_L55-57_

#### struct `FMediaSampleSinkEventData::__anon87b33d24010a::(anonymous)`  
``  
_L59-61_

#### class `TMediaSampleSink`  
`template<typename SampleType> class TMediaSampleSink`  
_L73-144_
- desc: Interface for media sample sinks. This interface declares the write side of media sample queues. @see TMediaSampleQueue
- L84 _public prototype_ `virtual bool Enqueue(const TSharedRef<SampleType, ESPMode::ThreadSafe>& Sample) = 0;` — Add a sample to the head of the queue. @param Sample The sample to add. @return true if the item was added, false otherwise. @see Num, RequestFlush
- L92 _public prototype_ `virtual int32 Num() const = 0;` — Get the number of samples in the queue. @return Number of samples. @see Enqueue, RequestFlush
- L101 _public function_ `virtual bool CanAcceptSamples(int32 NumSamples) const` — Check if sink can accept new samples @param NumSamples How many samples we would like the sink to accept @return True if samples could be accepted, false otherwise @note Override in implementation as needed
- L112 _public prototype_ `virtual void RequestFlush() = 0;` — Request to flush the queue. @note To be called only from producer thread. @see Enqueue, Num
- L118 _public prototype_ `virtual uint32 GetFlushCount() const = 0;` — Returns the number of times the queue has been requested to flush already. @return Number of times RequestFlush() was called.
- L123 _public function_ `void ReceiveEvent(EMediaSampleSinkEvent Event, const FMediaSampleSinkEventData& Data)` — Receive event
- L131 _public function_ `DECLARE_EVENT_TwoParams(TMediaSampleSink<SampleType>, FOnMediaSampleSinkEvent, EMediaSampleSinkEvent , const FMediaSampleSinkEventData& ) FOnMediaSampleSinkEvent& OnMediaSampleSinkEvent()` — Register to receive events flowing to this sink
- L140 _public prototype_ `virtual ~TMediaSampleSink() = default;` — Virtual destructor.
- L143 _private member_ `FOnMediaSampleSinkEvent MediaSampleSinkEvent;`

#### class `FMediaAudioSampleSink`  
`class FMediaAudioSampleSink : public TMediaSampleSink<class IMediaAudioSample>`  
_L148-156_
- inherits: `TMediaSampleSink<classIMediaAudioSample>`
- desc: Type definition for audio sample sink.
- L154 _public prototype_ `virtual FMediaTimeStampSample GetAudioTime() const = 0;` — Get last sampled current audio timestamp being played
- L155 _public prototype_ `virtual void InvalidateAudioTime() = 0;`

#### Free symbols / members of external scopes

- L32 _member_ `UMediaPlayer* MediaPlayer;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a::__anon87b33d240208`)
- L33 _member_ `} Attached;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a`)
- L36 _member_ `UMediaPlayer* MediaPlayer;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a::__anon87b33d240308`)
- L37 _member_ `} Detached;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a`)
- L40 _member_ `UMediaPlayer* MediaPlayer;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a::__anon87b33d240408`)
- L41 _member_ `} PlayerPluginChange;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a`)
- L44 _member_ `uint32 Dummy;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a::__anon87b33d240508`)
- L45 _member_ `} SampleDataUpdate;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a`)
- L48 _member_ `UMediaPlayer* MediaPlayer;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a::__anon87b33d240608`)
- L49 _member_ `} FlushWasRequested;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a`)
- L52 _member_ `uint32 Dummy;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a::__anon87b33d240708`)
- L53 _member_ `} MediaClosed;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a`)
- L56 _member_ `uint32 Dummy;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a::__anon87b33d240808`)
- L57 _member_ `} PlaybackEndReached;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a`)
- L60 _member_ `float PlaybackRate;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a::__anon87b33d240908`)
- L61 _member_ `} PlaybackRateChanged;` (scope `FMediaSampleSinkEventData::__anon87b33d24010a`)
- L131 _delegate_ `DECLARE_EVENT_TwoParams(TMediaSampleSink<SampleType>, FOnMediaSampleSinkEvent, EMediaSampleSinkEvent , const FMediaSampleSinkEventData& ) FOnMediaSampleSinkEvent& OnMediaSampleSinkEvent() { return MediaSampleSinkEvent; } public: virtual ~TMediaSampleSink() = default;` — Register to receive events flowing to this sink
- L159 _typedef_ `typedef TMediaSampleSink<class IMediaBinarySample> FMediaBinarySampleSink;` — Type definition for binary sample sink.
- L162 _typedef_ `typedef TMediaSampleSink<class IMediaOverlaySample> FMediaOverlaySampleSink;` — Type definition for overlay sample sink.
- L165 _typedef_ `typedef TMediaSampleSink<class IMediaTextureSample> FMediaTextureSampleSink;` — Type definition for texture sample sink.

### `Source/Runtime/MediaUtils/Public/MediaSampleSinks.h` (Public)


#### class `TMediaSampleSinks`  
`template<typename SampleType, typename SinkType=TMediaSampleSink<SampleType>> class TMediaSampleSinks`  
_L18-183_
- desc: Collection of media sample sinks. @param SampleType The type of media samples that the sinks process.
- L28 _public function_ `void Add(const TSharedRef<SinkType, ESPMode::ThreadSafe>& SampleSink, UMediaPlayer* Player = nullptr)` — Add the given media sample sink to the collection. @param SampleSink The sink to add. @see Num, Remove
- L50 _public function_ `bool Enqueue(const TSharedRef<SampleType, ESPMode::ThreadSafe>& Sample)` — Enqueue the given media samples to the registered sinks. This method will also remove expired sinks that haven't been removed yet. @param Sample The media sample to enqueue. @param MaxQueueDepth The maximum depth of the sink queues before overflow. @return true if the sample was enqueued to all sinks, false if one or more sinks overflowed. @see Flush
- L87 _public function_ `void Flush(UMediaPlayer* MediaPlayer)` — Flush all registered sinks. This method will also remove expired sinks that haven't been removed yet. @see Enqueue
- L114 _public function_ `int32 Num() const` — Get the number of sinks in this collection. @return Number of sinks. @see Add, Remove
- L124 _public function_ `bool IsEmpty() const` — Check if any sinks are inserted @return True if empty, false otherwise
- L135 _public function_ `void Remove(const TSharedRef<SinkType, ESPMode::ThreadSafe>& SampleSink, UMediaPlayer* Player = nullptr)` — Remove the given media sample sink from the collection. @param SampleSink The sink to remove. @see Add, Num
- L148 _public function_ `void Cleanup()` — Remove any invalid sinks
- L162 _public function_ `void ReceiveEvent(EMediaSampleSinkEvent Event, const FMediaSampleSinkEventData& Data)` — Receive event and broadcast to sinks
- L182 _protected member_ `TArray<TWeakPtr<SinkType, ESPMode::ThreadSafe>> Sinks;` — The collection of registered sinks.

#### class `FMediaAudioSampleSinks`  
`class FMediaAudioSampleSinks : public TMediaSampleSinks<IMediaAudioSample, FMediaAudioSampleSink>`  
_L187-202_
- inherits: `TMediaSampleSinks<IMediaAudioSample,FMediaAudioSampleSink>`
- L193 _public function_ `TSharedPtr<FMediaAudioSampleSink, ESPMode::ThreadSafe> GetPrimaryAudioSink()` — Get primary audio sink and cleanup any invalid sinks

#### Free symbols / members of external scopes

- L185 _typedef_ `typedef TMediaSampleSinks<IMediaTextureSample, FMediaTextureSampleSink> FMediaVideoSampleSinks;`
- L204 _typedef_ `typedef TMediaSampleSinks<IMediaOverlaySample, FMediaOverlaySampleSink> FMediaOverlaySampleSinks;`
- L205 _typedef_ `typedef TMediaSampleSinks<IMediaBinarySample, FMediaBinarySampleSink> FMediaBinarySampleSinks;`

### `Source/Runtime/MediaUtils/Public/MediaSampleSource.h` (Public)


#### class `TMediaSampleSource`  
`template<typename SampleType> class TMediaSampleSource`  
_L19-59_
- desc: Interface for media sample sources. This interface declares the read side of media sample queues. @see TMediaSampleQueue
- L30 _public prototype_ `virtual bool Dequeue(TSharedPtr<SampleType, ESPMode::ThreadSafe>& OutSample) = 0;` — Remove and return the next sample in the queue. @param OutSample Will contain the sample if the queue is not empty. @return true if a sample has been returned, false if the queue was empty. @see Peek, Pop
- L39 _public prototype_ `virtual bool Peek(TSharedPtr<SampleType, ESPMode::ThreadSafe>& OutSample) = 0;` — Peek at the next sample in the queue without removing it. @param OutSample Will contain the sample if the queue is not empty. @return true if a sample has been returned, false if the queue was empty. @see Dequeue, Pop
- L45 _public prototype_ `virtual void GetSampleTimes(TArray<TRange<FMediaTimeStamp>>& OutSampleTimeRanges) = 0;` — Returns the sample start and end times of all samples currently in the queue. @param OutSampleTimeRanges Will contain the sample time ranges.
- L53 _public prototype_ `virtual bool Pop() = 0;` — Remove the next sample from the queue. @return true if a sample was removed, false otherwise. @see Dequeue, Peek
- L58 _public prototype_ `virtual ~TMediaSampleSource() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L63 _typedef_ `typedef TMediaSampleSource<class IMediaAudioSample> FMediaAudioSampleSource;` — Type definition for audio sample source.
- L66 _typedef_ `typedef TMediaSampleSource<class IMediaBinarySample> FMediaBinarySampleSource;` — Type definition for binary sample source.
- L69 _typedef_ `typedef TMediaSampleSource<class IMediaOverlaySample> FMediaOverlaySampleSource;` — Type definition for overlay sample source.
- L72 _typedef_ `typedef TMediaSampleSource<class IMediaTextureSample> FMediaTextureSampleSource;` — Type definition for texture sample source.

### `Source/Runtime/MediaUtils/Public/MediaSamples.h` (Public)


#### class `FMediaSamples`  
`class FMediaSamples : public IMediaSamples`  
_L23-264_
- inherits: `IMediaSamples`
- desc: General purpose media sample queue.
- L27 _public member_ `static constexpr uint32 MaxNumberOfQueuedVideoSamples = 4;`
- L28 _public member_ `static constexpr uint32 MaxNumberOfQueuedAudioSamples = 4;`
- L29 _public member_ `static constexpr uint32 MaxNumberOfQueuedCaptionSamples = 4;`
- L30 _public member_ `static constexpr uint32 MaxNumberOfQueuedSubtitlesSamples = 4;`
- L31 _public member_ `static constexpr uint32 MaxNumberOfQueuedMetaDataSamples = 4;`
- L33 _public prototype_ `FMediaSamples(uint32 InMaxNumberOfQueuedAudioSamples = MaxNumberOfQueuedAudioSamples, uint32 InMaxNumberOfQueuedVideoSamples = MaxNumberOfQueuedVideoSamples, uint32 InMaxNumberOfQueuedCaptionSamples = MaxNumberOfQueuedCaptionSamples, uint32 InMaxNumberOfQueuedSubtitlesSamples = MaxNumberOfQueuedSubtitlesSamples, uint32 InMaxNumberOfQueuedMetaDataSamples = MaxNumberOfQueuedMetaDataSamples);`
- L39 _public prototype_ `~FMediaSamples();`
- L47 _public prototype_ `void AddAudio(const TSharedRef<IMediaAudioSample, ESPMode::ThreadSafe>& Sample);` — Add the given audio sample to the cache. @param Sample The sample to add. @see AddCaption, AddMetadata, AddSubtitle, AddVideo, NumAudio
- L55 _public prototype_ `void AddCaption(const TSharedRef<IMediaOverlaySample, ESPMode::ThreadSafe>& Sample);` — Add the given caption sample to the cache. @param Sample The sample to add. @see AddAudio, AddMetadata, AddSubtitle, AddVideo, NumCaption
- L63 _public prototype_ `void AddMetadata(const TSharedRef<IMediaBinarySample, ESPMode::ThreadSafe>& Sample);` — Add the given audio sample to the cache. @param Sample The sample to add. @see AddAudio, AddCaption, AddSubtitle, AddVideo, NumMetadata
- L71 _public prototype_ `void AddSubtitle(const TSharedRef<IMediaOverlaySample, ESPMode::ThreadSafe>& Sample);` — Add the given subtitle sample to the cache. @param Sample The sample to add. @see AddAudio, AddCaption, AddMetadata, AddVideo, NumSubtitle
- L79 _public prototype_ `void AddVideo(const TSharedRef<IMediaTextureSample, ESPMode::ThreadSafe>& Sample);` — Add the given audio sample to the cache. @param Sample The sample to add. @see AddAudio, AddCaption, AddMetadata, AddSubtitle, NumVideo
- L86 _public function_ `int32 NumAudioSamples() const override` — Get the number of queued audio samples. @return Number of samples. @see AddAudio, NumCaption, NumMetadata, NumSubtitle, NumVideo
- L97 _public function_ `int32 NumCaptionSamples() const override` — Get the number of queued caption samples. @return Number of samples. @see AddCaption, NumAudio, NumMetadata, NumSubtitle, NumVideo
- L108 _public function_ `int32 NumMetadataSamples() const override` — Get the number of queued metadata samples. @return Number of samples. @see AddMetadata, NumAudio, NumCaption, NumSubtitle, NumVideo
- L119 _public function_ `int32 NumSubtitleSamples() const override` — Get the number of queued subtitle samples. @return Number of samples. @see AddSubtitle, NumAudio, NumCaption, NumMetadata, NumVideo
- L130 _public function_ `int32 NumVideoSamples() const override` — Get the number of queued video samples. @return Number of samples. @see AddVideo, NumAudio, NumCaption, NumMetadata, NumSubtitle
- L139 _public prototype_ `virtual bool FetchAudio(TRange<FTimespan> TimeRange, TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& OutSample) override;`
- L140 _public prototype_ `virtual bool FetchCaption(TRange<FTimespan> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample) override;`
- L141 _public prototype_ `virtual bool FetchMetadata(TRange<FTimespan> TimeRange, TSharedPtr<IMediaBinarySample, ESPMode::ThreadSafe>& OutSample) override;`
- L142 _public prototype_ `virtual bool FetchSubtitle(TRange<FTimespan> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample) override;`
- L143 _public prototype_ `virtual bool FetchVideo(TRange<FTimespan> TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample) override;`
- L144 _public prototype_ `virtual void FlushSamples() override;`
- L146 _public prototype_ `virtual bool FetchAudio(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& OutSample) override;`
- L147 _public prototype_ `virtual bool FetchCaption(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample) override;`
- L148 _public prototype_ `virtual bool FetchMetadata(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaBinarySample, ESPMode::ThreadSafe>& OutSample) override;`
- L149 _public prototype_ `virtual bool FetchSubtitle(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample) override;`
- L150 _public prototype_ `virtual bool FetchVideo(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample) override;`
- L152 _public prototype_ `virtual EFetchBestSampleResult FetchBestVideoSampleForTimeRange(const TRange<FMediaTimeStamp>& TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample, bool bReverse, bool bConsistentResult) override;`
- L154 _public prototype_ `virtual void SetMinExpectedNextSequenceIndex(TOptional<int32> InNextSequenceIndex) override;`
- L161 _public function_ `virtual bool PeekVideoSampleTime(FMediaTimeStamp & TimeStamp) override` — Peek next video sample's timestamp @return true if value could be retrieved, false otherwise
- L172 _public function_ `virtual bool PeekVideoSampleTimeRanges(TArray<TRange<FMediaTimeStamp>>& TimeRange) override`
- L177 _public function_ `virtual bool PeekAudioSampleTimeRanges(TArray<TRange<FMediaTimeStamp>>& TimeRange) override`
- L183 _public function_ `virtual bool DiscardVideoSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse) override`
- L188 _public function_ `virtual bool DiscardAudioSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse) override`
- L193 _public function_ `virtual bool DiscardCaptionSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse) override`
- L198 _public function_ `virtual bool DiscardSubtitleSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse) override`
- L203 _public function_ `virtual bool DiscardMetadataSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse) override`
- L208 _public function_ `virtual uint32 GetNumDroppedVideoSamples(bool bInClearToZero) override`
- L213 _public function_ `virtual uint32 GetNumDroppedAudioSamples(bool bInClearToZero) override`
- L218 _public function_ `virtual uint32 GetNumDroppedSubtitleSamples(bool bInClearToZero) override`
- L223 _public function_ `virtual uint32 GetNumDroppedCaptionSamples(bool bInClearToZero) override`
- L228 _public function_ `virtual uint32 GetNumDroppedMetadataSamples(bool bInClearToZero) override`
- L234 _public prototype_ `virtual uint32 PurgeOutdatedVideoSamples(const FMediaTimeStamp & ReferenceTime, bool bReversed, FTimespan MaxAge) override;`
- L235 _public prototype_ `virtual uint32 PurgeOutdatedSubtitleSamples(const FMediaTimeStamp & ReferenceTime, bool bReversed, FTimespan MaxAge) override;`
- L236 _public prototype_ `virtual uint32 PurgeOutdatedCaptionSamples(const FMediaTimeStamp& ReferenceTime, bool bReversed, FTimespan MaxAge) override;`
- L237 _public prototype_ `virtual uint32 PurgeOutdatedMetadataSamples(const FMediaTimeStamp& ReferenceTime, bool bReversed, FTimespan MaxAge) override;`
- L239 _public prototype_ `virtual bool CanReceiveVideoSamples(uint32 Num) const override;`
- L240 _public prototype_ `virtual bool CanReceiveAudioSamples(uint32 Num) const override;`
- L241 _public prototype_ `virtual bool CanReceiveSubtitleSamples(uint32 Num) const override;`
- L242 _public prototype_ `virtual bool CanReceiveCaptionSamples(uint32 Num) const override;`
- L243 _public prototype_ `virtual bool CanReceiveMetadataSamples(uint32 Num) const override;`
- L248 _private member_ `FMediaAudioSampleQueue AudioSampleQueue;` — Audio sample queue.
- L251 _private member_ `FMediaOverlaySampleQueue CaptionSampleQueue;` — Caption sample queue.
- L254 _private member_ `FMediaBinarySampleQueue MetadataSampleQueue;` — Metadata sample queue.
- L257 _private member_ `FMediaOverlaySampleQueue SubtitleSampleQueue;` — Subtitle sample queue.
- L260 _private member_ `FMediaTextureSampleQueue VideoSampleQueue;` — Video sample queue.
- L263 _private member_ `TOptional<int32> NextMinSequenceIndex;` — The next smallest expected sequence index if set.
