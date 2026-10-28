# Runtime / Media

- module root: `Source/Runtime/Media`
- headers: 24; symbols: 568
- symbol kinds: class=29, enum=19, enumerator=136, function=170, member=37, namespace=2, prototype=163, struct=8, typedef=1, variable=3
- PublicDependencyModuleNames: Core, RenderCore
- PublicIncludePathModuleNames: RenderCore

### `Source/Runtime/Media/Private/MediaClock.h` (Private)


#### class `FMediaClock`  
`class FMediaClock : public IMediaClock`  
_L17-103_
- inherits: `IMediaClock`
- desc: Implements the media clock.
- L23 _public prototype_ `FMediaClock();` — Default constructor.
- L32 _public prototype_ `void TickInput();` — Tick all clock sinks in the Input stage. @see TickOutput, TickRender, TickUpdate
- L39 _public prototype_ `void TickOutput();` — Tick all clock sinks in the Output stage. @see TickInput, TickRender, TickUpdate
- L46 _public prototype_ `void TickRender();` — Tick all clock sinks in the Render stage. @see TickInput, TickOutput, TickUpdate
- L53 _public prototype_ `void TickFetch();` — Tick all clock sinks in the Update stage. @see TickInput, TickOutput, TickRender
- L61 _public prototype_ `void UpdateTimecode(const FTimespan NewTimecode, bool NewTimecodeLocked);` — Update the current time code. @param NewTimecode The new time code. @param NewTimecodeLocked Whether media objects should lock to the time code.
- L67 _public prototype_ `virtual void AddSink(const TSharedRef<IMediaClockSink, ESPMode::ThreadSafe>& Sink) override;`
- L68 _public prototype_ `virtual FTimespan GetTimecode() const override;`
- L69 _public prototype_ `virtual bool IsTimecodeLocked() const override;`
- L70 _public prototype_ `virtual void RemoveSink(const TSharedRef<IMediaClockSink, ESPMode::ThreadSafe>& Sink) override;`
- L75 _private member_ `FTimespan DeltaTime;` — The current delta time.
- L78 _private member_ `bool Locked;` — Whether media objects should lock to the media clock's time code.
- L81 _private member_ `TArray<TWeakPtr<IMediaClockSink, ESPMode::ThreadSafe>> Sinks;` — Registered clock sinks.
- L84 _private member_ `TArray<TWeakPtr<IMediaClockSink, ESPMode::ThreadSafe>> SinksToAdd;` — Sinks that need to be added.
- L87 _private member_ `TArray<TWeakPtr<IMediaClockSink, ESPMode::ThreadSafe>> SinksToRemove;` — Sinks that need to be removed.
- L90 _private member_ `mutable FCriticalSection SinkCriticalSection;` — Critical section for synchronizing access to sink.
- L93 _private member_ `FTimespan Timecode;` — The current time code.
- L96 _private member_ `bool TimecodeLocked;` — Whether the time code is locked to an external clock.
- L101 _private prototype_ `void UpdateSinkArray();` — Updates the Sink array to reflect what has been added and removed since the last call to UpdateSinkArray.

### `Source/Runtime/Media/Private/MediaTicker.h` (Private)


#### class `FMediaTicker`  
`class FMediaTicker : public FRunnable , public IMediaTicker`  
_L20-69_
- inherits: `FRunnable,IMediaTicker`
- desc: High frequency ticker thread.
- L27 _public prototype_ `FMediaTicker();` — Default constructor.
- L30 _public prototype_ `virtual ~FMediaTicker();` — Virtual destructor.
- L36 _public prototype_ `virtual bool Init() override;`
- L37 _public prototype_ `virtual uint32 Run() override;`
- L38 _public prototype_ `virtual void Stop() override;`
- L39 _public prototype_ `virtual void Exit() override;`
- L45 _public prototype_ `virtual void AddTickable(const TSharedRef<IMediaTickable, ESPMode::ThreadSafe>& Tickable) override;`
- L46 _public prototype_ `virtual void RemoveTickable(const TSharedRef<IMediaTickable, ESPMode::ThreadSafe>& Tickable) override;`
- L51 _protected prototype_ `void TickTickables();` — Tick all tickables.
- L56 _private member_ `FCriticalSection CriticalSection;` — Critical section for synchronizing access to high-frequency clock sinks.
- L59 _private member_ `TAtomic<bool> Stopping;` — Holds a flag indicating that the thread is stopping.
- L62 _private member_ `TArray<TWeakPtr<IMediaTickable, ESPMode::ThreadSafe>> Tickables;` — Collection of tickable objects.
- L65 _private member_ `TArray<TWeakPtr<IMediaTickable, ESPMode::ThreadSafe>> TickablesCopy;` — Variable to avoid rellocating the Tickables array repeatedly.
- L68 _private member_ `FEvent* WakeupEvent;` — Holds an event signaling the thread to wake up.

### `Source/Runtime/Media/Public/IMediaAudioSample.h` (Public)


#### enum `EMediaAudioSampleFormat`  
`enum class EMediaAudioSampleFormat`  
_L15-34_
- desc: Available formats for media audio samples.
- L18 _public enumerator_ `Undefined` — Format not defined.
- L21 _public enumerator_ `Double` — Uncompressed 64-bit double precision floating point samples.
- L24 _public enumerator_ `Float` — Uncompressed 32-bit single precision floating point samples.
- L27 _public enumerator_ `Int8` — Uncompressed 8-bit integer samples.
- L30 _public enumerator_ `Int16` — Uncompressed 16-bit integer samples.
- L33 _public enumerator_ `Int32` — Uncompressed 32-bit integer samples.

#### class `IMediaAudioSample`  
`class IMediaAudioSample`  
_L40-121_
- desc: Interface for media audio samples.
- L52 _public prototype_ `virtual const void* GetBuffer() = 0;` — Get the sample data. The returned buffer is only valid for the life time of this sample. @return Pointer to data buffer. @see GetChannels, GetDuration, GetFormat, GetFrames, GetRate, GetTime
- L60 _public prototype_ `virtual uint32 GetChannels() const = 0;` — Get the sample's number of channels. @return Number of channels. @see GetBuffer, GetDuration, GetFormat, GetFrames, GetRate, GetTime
- L71 _public prototype_ `virtual FTimespan GetDuration() const = 0;` — Get the amount of time for which the sample is valid. A duration of zero indicates that the sample is valid until the timecode of the next sample in the queue. @return Sample duration. @see GetBuffer, GetChannels, GetFormat, GetFrames, GetRate, GetTime
- L79 _public prototype_ `virtual EMediaAudioSampleFormat GetFormat() const = 0;` — Get the audio sample format. @return Sample type. @see GetBuffer, GetChannels, GetDuration, GetFrames, GetRate, GetTime
- L89 _public prototype_ `virtual uint32 GetFrames() const = 0;` — Get the number of frames in the buffer. A frame consists of one sample value per channel. @return Frame count. @see GetBuffer, GetChannels, GetDuration, GetFormat, GetRate, GetTime
- L97 _public prototype_ `virtual uint32 GetSampleRate() const = 0;` — Get the sample's sampling rate (in audio frames per second). @return Sample rate, i.e. 44100 Hz. @see GetBuffer, GetChannels, GetDuration, GetFormat, GetFrames, GetTime
- L107 _public prototype_ `virtual FMediaTimeStamp GetTime() const = 0;` — Get the sample time (in the player's local clock). This value is used primarily for debugging purposes. @return Sample time. @see GetBuffer, GetChannels, GetDuration, GetFormat, GetFrames, GetSampleRate
- L115 _public function_ `virtual TOptional<FTimecode> GetTimecode() const` — Get the sample timecode if available. @return Sample timecode. @see GetTime
- L120 _public prototype_ `virtual ~IMediaAudioSample() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaBinarySample.h` (Public)


#### class `IMediaBinarySample`  
`class IMediaBinarySample`  
_L16-77_
- desc: Interface for media binary data samples.
- L26 _public prototype_ `virtual const void* GetData() = 0;` — Get the sample data. @return Pointer to data buffer. @see GetDuration, GetSize, GetTime
- L37 _public prototype_ `virtual FTimespan GetDuration() const = 0;` — Get the amount of time for which the sample is valid. A duration of zero indicates that the sample is valid until the timecode of the next sample in the queue. @return Sample duration. @see GetData, GetSize, GetTime
- L44 _public prototype_ `virtual uint32 GetSize() const = 0;` — Get the size of the binary data. @see GetData, GetDuration, GetTime
- L54 _public prototype_ `virtual FMediaTimeStamp GetTime() const = 0;` — Get the sample time (in the player's local clock). This value is used primarily for debugging purposes. @return Sample time. @see GetData, GetDuration, GetSize, GetTime
- L62 _public function_ `virtual TOptional<FTimecode> GetTimecode() const` — Get the sample timecode if available. @return Sample timecode. @see GetTime
- L71 _public function_ `virtual FGuid GetGUID() const` — Get the GUID identifying the derived type that may implement additional, type specific methods. If the GUID matches a type known type it is safe to static cast this class to the derived type. This is usually done to identify the format of the binary data carried here.
- L76 _public prototype_ `virtual ~IMediaBinarySample() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaCache.h` (Public)


#### enum `EMediaCacheState`  
`enum class EMediaCacheState`  
_L15-28_
- desc: Enumerates status types of media samples. @see IMediaSamples.GetSampleState
- L18 _public enumerator_ `Cached` — Sample has been cached (reserved for high-level caching; use Loaded in player plug-ins).
- L21 _public enumerator_ `Loaded` — Sample has finished loading.
- L24 _public enumerator_ `Loading` — Sample is currently being loaded.
- L27 _public enumerator_ `Pending` — Sample is scheduled to be loaded.

#### class `IMediaCache`  
`class IMediaCache`  
_L36-72_
- desc: Interface for access to a media player's cache. @see IMediaControls, IMediaPlayer, IMediaSamples, IMediaTracks, IMediaView
- L52 _public function_ `virtual bool QueryCacheState(EMediaCacheState State, TRangeSet<FTimespan>& OutTimeRanges) const` — Query the time ranges of cached media samples for the specified caching state. This method can be used to probe a media player's decoder for which samples are scheduled for loading, being loaded, or finished loading. This is generally only supported by those players that expose some kind of internal sample caching or load/decode scheduling mechanism, and most players may simply ignore this call. @param State The sample state we're interested in. @param OutTimeRanges Will contain the set of matching sample time ranges. @return true on success, false if not supported.
- L63 _public function_ `virtual int32 GetSampleCount(EMediaCacheState State) const` — Query the number of samples for the specified caching state. @param State The sample state we're interested in. @return Sample count.
- L71 _public prototype_ `virtual ~IMediaCache() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaCaptureSupport.h` (Public)


#### enum `EMediaCaptureDeviceType`  
`enum class EMediaCaptureDeviceType : uint32`  
_L14-51_
- desc: Known capture device types.
- L17 _public enumerator_ `Unknown` — Unknown capture device type.
- L20 _public enumerator_ `Audio` — Unspecified audio capture device.
- L23 _public enumerator_ `AudioCard` — Audio capture card.
- L26 _public enumerator_ `AudioSoftware` — Software audio capture device.
- L29 _public enumerator_ `DepthSensor` — Depth sensors.
- L32 _public enumerator_ `Microphone` — Microphone.
- L35 _public enumerator_ `Video` — Unspecified video capture device.
- L38 _public enumerator_ `VideoCard` — Video capture card.
- L41 _public enumerator_ `VideoSoftware` — Software video capture device.
- L44 _public enumerator_ `Webcam` — Unspecified web cam.
- L47 _public enumerator_ `WebcamFront` — Front facing web cams.
- L50 _public enumerator_ `WebcamRear` — Rear facing web cams.

#### struct `FMediaCaptureDeviceInfo`  
`struct FMediaCaptureDeviceInfo`  
_L57-70_
- desc: Information about a capture device.
- L60 _public member_ `FText DisplayName;` — Human readable display name.
- L63 _public member_ `FString Info;` — Device specific debug information.
- L66 _public member_ `EMediaCaptureDeviceType Type;` — The type of capture device.
- L69 _public member_ `FString Url;` — Media URL string for use with media players.

#### class `IMediaCaptureSupport`  
`class IMediaCaptureSupport`  
_L76-100_
- desc: Interface for media capture support classes.
- L86 _public prototype_ `virtual void EnumerateAudioCaptureDevices(TArray<FMediaCaptureDeviceInfo>& OutDeviceInfos) = 0;` — Enumerate available audio capture devices. @param OutDeviceInfos Will contain information about the devices. @see EnumerateVideoCaptureDevices
- L94 _public prototype_ `virtual void EnumerateVideoCaptureDevices(TArray<FMediaCaptureDeviceInfo>& OutDeviceInfos) = 0;` — Enumerate available video capture devices. @param OutDeviceInfos Will contain information about the devices. @see EnumerateAudioCaptureDevices
- L99 _public prototype_ `virtual ~IMediaCaptureSupport() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaClock.h` (Public)


#### class `IMediaClock`  
`class IMediaClock`  
_L14-56_
- desc: Interface for media framework clocks.
- L24 _public prototype_ `virtual FTimespan GetTimecode() const = 0;` — Get the clock's current time code. @return Time code. @see IsTimecodeLocked
- L32 _public prototype_ `virtual bool IsTimecodeLocked() const = 0;` — Whether the clock's time code is locked to an external time source. @return true if locked, false otherwise. @see GetTimecode
- L42 _public prototype_ `virtual void AddSink(const TSharedRef<IMediaClockSink, ESPMode::ThreadSafe>& Sink) = 0;` — Add a media clock sink. @param Sink The sink object to add. @see RemoveSink
- L50 _public prototype_ `virtual void RemoveSink(const TSharedRef<IMediaClockSink, ESPMode::ThreadSafe>& Sink) = 0;` — Remove a media clock sink. @param Sink The sink object to remove. @see AddSink
- L55 _public prototype_ `virtual ~IMediaClock() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaClockSink.h` (Public)


#### class `IMediaClockSink`  
`class IMediaClockSink`  
_L36-92_
- desc: Interface for media clock sinks. This interface can be implemented by classes that wish to be ticked by the Media Framework clock. The following tick stages are available (in the order in which they are called on clock sinks): TickInput Called each tick from the main thread before the Engine is being ticked. It is used by media player plug-ins to update their state and initiate the reading of new input samples. TickFetch Called each tick from the main thread after the Engine has been ticked, but before TickRender. It can be used by media players to fetch the results of the TickInput stage prior to rendering. TickRender Called each tick from the main thread after TickFetch is complete, but before the frame has finished rendering. It is mainly used by media sinks to render the fetched input samples, such as drawing video frames to a texture or playing audio samples on a sound component. TickOutput Called each tick from the main thread after the Engine has been ticked and the frame finished rendering. It can be used by output plug-ins to write the completed frame to disk or stream it over the network.
- L47 _public function_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode)` — Called each tick to handle updates after the Engine ticked. @param DeltaTime Time since this function was last called. @param Timecode The current media time code. @see TickInput, TickOutput, TickRender
- L59 _public function_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode)` — Called each tick to handle input before the Engine is ticked. @param DeltaTime Time since this function was last called. @param Timecode The current media time code. @see TickFetch, TickOutput, TickRender
- L71 _public function_ `virtual void TickOutput(FTimespan DeltaTime, FTimespan Timecode)` — Called each tick to output the rendered frame. @param DeltaTime Time since this function was last called. @param Timecode The current media time code. @see TickFetch, TickInput, TickRender
- L83 _public function_ `virtual void TickRender(FTimespan DeltaTime, FTimespan Timecode)` — Called each tick before the frame finished rendering. @param DeltaTime Time since this function was last called. @param Timecode The current media time code. @see TickFetch, TickInput, TickOutput
- L91 _public prototype_ `virtual ~IMediaClockSink() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaControls.h` (Public)


#### enum `EMediaControl`  
`enum class EMediaControl`  
_L15-34_
- desc: Available media controls.
- L18 _public enumerator_ `BlockOnFetch` — Block on fetch.
- L21 _public enumerator_ `Pause` — Pause playback.
- L24 _public enumerator_ `Resume` — Resume playback.
- L27 _public enumerator_ `Scrub` — Seek to playback position (while updating output).
- L30 _public enumerator_ `Seek` — Seek to playback position.
- L33 _public enumerator_ `PlaybackRange` — Playback of a range.

#### enum `EMediaSeekDirection`  
`enum class EMediaSeekDirection`  
_L40-53_
- desc: Directions for seeking in media.
- L43 _public enumerator_ `Backward` — Seek backwards from current position.
- L46 _public enumerator_ `Beginning` — Seek from the beginning of the media.
- L49 _public enumerator_ `End` — Seek from the end of the media.
- L52 _public enumerator_ `Forward` — Seek forward from current position.

#### enum `EMediaRateThinning`  
`enum class EMediaRateThinning`  
_L59-66_
- desc: Thinning modes for playback rates.
- L62 _public enumerator_ `Thinned` — Frames will be skipped to accommodate play rate.
- L65 _public enumerator_ `Unthinned` — No frames will be skipped.

#### enum `EMediaState`  
`enum class EMediaState`  
_L72-91_
- desc: Possible states of media playback.
- L75 _public enumerator_ `Closed` — Media has been closed and cannot be played again.
- L78 _public enumerator_ `Error` — Unrecoverable error occurred during playback.
- L81 _public enumerator_ `Paused` — Playback has been paused, but can be resumed.
- L84 _public enumerator_ `Playing` — Media is currently playing.
- L87 _public enumerator_ `Preparing` — Media is being prepared for playback.
- L90 _public enumerator_ `Stopped` — Playback has been stopped, but can be restarted.

#### enum `EMediaStatus`  
`enum class EMediaStatus`  
_L97-107_
- desc: Available media player status flags.
- L100 _public enumerator_ `None = 0x0` — No flags set.
- L103 _public enumerator_ `Buffering = 0x1` — Player is buffering data.
- L106 _public enumerator_ `Connecting = 0x2` — Player is connecting to a media source.

#### enum `EMediaTimeRangeType`  
`enum class EMediaTimeRangeType`  
_L116-123_
- desc: Different types of media timeline ranges.
- L119 _public enumerator_ `Absolute` — Total absolute time range as defined by the media.
- L122 _public enumerator_ `Current` — Current time range of the media, set by media internal means or through API calls.

#### struct `FMediaSeekParams`  
`struct FMediaSeekParams`  
_L129-133_
- desc: Additional parameters passed to Seek().
- L132 _public member_ `TOptional<int32> NewSequenceIndex;` — If set, the new sequence index a v2 timing enabled media player must be using now.

#### class `IMediaControls`  
`class IMediaControls`  
_L141-337_
- desc: Interface for controlling media playback. @see IMediaCache, IMediaPlayer, IMediaSamples, IMediaTracks, IMediaView
- L150 _public prototype_ `virtual bool CanControl(EMediaControl Control) const = 0;` — Whether the specified control is currently available. @return true if the control is available, false otherwise.
- L158 _public prototype_ `virtual FTimespan GetDuration() const = 0;` — Get the media's duration. @return A time span representing the duration. @see GetTime
- L166 _public prototype_ `virtual float GetRate() const = 0;` — Get the nominal playback rate, i.e. 1.0 for real time. @return Playback rate. @see Pause, Play, SetRate
- L174 _public prototype_ `virtual EMediaState GetState() const = 0;` — Get the state of the media. @return Media state. @see IsLooping
- L181 _public prototype_ `virtual EMediaStatus GetStatus() const = 0;` — Get media player status flags. @return Status flags.
- L190 _public prototype_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const = 0;` — Get the supported playback rates. @param Thinning The desired rate thinning mode. @return The ranges of supported rates. @see SetRate, SupportsRate
- L198 _public prototype_ `virtual FTimespan GetTime() const = 0;` — Get the player's current playback time. @return Playback time. @see Seek
- L206 _public prototype_ `virtual bool IsLooping() const = 0;` — Check whether playback is currently looping. @return true if playback is looping, false otherwise. @see GetState, SetLooping
- L215 _public prototype_ `virtual bool Seek(const FTimespan& Time) = 0;` — Change the media's playback time. @param Time The playback time to set. @return true on success, false otherwise. @see GetTime
- L223 _public prototype_ `virtual bool SetLooping(bool Looping) = 0;` — Set whether playback should be looping. @param Looping Enables or disables looping. @see IsLooping
- L237 _public prototype_ `virtual bool SetRate(float Rate) = 0;` — Set the current playback rate. A playback rate of 1.0 will play the media normally at real-time. A rate of 0.0 corresponds to pausing playback. A negative rate, if supported, plays the media in reverse, and a rate larger than 1.0 fast forwards playback. @param Rate The playback rate to set. @return true on success, false otherwise. @see GetRate, Pause, Play
- L246 _public function_ `virtual void SetBlockingPlaybackHint(bool bFacadeWillUseBlockingPlayback)` — Hint for player indicating that blocked playback mode will be used / not used @param bFacadeWillUseBlockingPlayback True if blocked playback will be used, false otherwiese @note Implement as needed by the player.
- L255 _public function_ `virtual bool Seek(const FTimespan& InNewTime, const FMediaSeekParams& InAdditionalParams)` — Same as Seek(), but with additional options. This default implementation just calls Seek() and ignores options.
- L270 _public function_ `inline bool Pause()` — Pause media playback. This is the same as setting the playback rate to 0.0. @return true if the media is being paused, false otherwise. @see Play, Stop
- L283 _public function_ `inline bool Play()` — Start media playback at the default rate of 1.0. This is the same as setting the playback rate to 1.0. @return true if playback is starting, false otherwise. @see Pause, Stop
- L297 _public function_ `bool Seek(const FTimespan& TimeOffset, EMediaSeekDirection Direction)` — `UE_DEPRECATED(5.6, "Use absolute seeking only. This method will be removed soon.")` — Change the playback time of the media by a relative offset in the given direction. @param TimeOffset The offset to apply to the time. @param Direction The direction to seek in. @return true on success, false otherwise. @see GetDuration, GetTime
- L323 _public function_ `virtual TRange<FTimespan> GetPlaybackTimeRange(EMediaTimeRangeType InRangeToGet) const`
- L328 _public function_ `virtual bool SetPlaybackTimeRange(const TRange<FTimespan>& InTimeRange)`
- L336 _public prototype_ `virtual ~IMediaControls() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L110 _prototype_ `ENUM_CLASS_FLAGS(EMediaStatus);`

### `Source/Runtime/Media/Public/IMediaEventSink.h` (Public)


#### enum `EMediaEvent`  
`enum class EMediaEvent`  
_L9-67_
- desc: Enumerates media player related events.
- L12 _public enumerator_ `MediaBuffering` — The media source started buffering data.
- L15 _public enumerator_ `MediaBufferingComplete` — The media source completed buffering data.
- L18 _public enumerator_ `MediaClosed` — The current media source has been closed.
- L21 _public enumerator_ `MediaConnecting` — The player started connecting to the media source.
- L24 _public enumerator_ `MediaOpened` — A new media source has been opened.
- L27 _public enumerator_ `MediaOpenFailed` — A media source failed to open.
- L30 _public enumerator_ `PlaybackEndReached` — The end of the media (or beginning if playing in reverse) has been reached.
- L33 _public enumerator_ `PlaybackResumed` — Playback has been resumed.
- L36 _public enumerator_ `PlaybackSuspended` — Playback has been suspended.
- L39 _public enumerator_ `SeekCompleted` — Seek operation has completed successfully.
- L42 _public enumerator_ `TracksChanged` — Media tracks have changed.
- L45 _public enumerator_ `MetadataChanged` — Media metadata has changed.
- L50 _public enumerator_ `Internal_Start` — Start of internal events not sent out to user code.
- L53 _public enumerator_ `Internal_PurgeVideoSamplesHint = Internal_Start` — Player requests purge of outdated video samples from queues.
- L56 _public enumerator_ `Internal_VideoSamplesAvailable` — Player notifies about availability or unavailablity of media samples.
- L57 _public enumerator_ `Internal_VideoSamplesUnavailable`
- L58 _public enumerator_ `Internal_AudioSamplesAvailable`
- L59 _public enumerator_ `Internal_AudioSamplesUnavailable`
- L66 _public enumerator_ `Internal_RequestVideoSampleRefresh` — Player requests the facade to clear its "last sample still good" cache so the next TickInput fetches and delivers a fresh sample even if the playback time range has not advanced.

#### class `IMediaEventSink`  
`class IMediaEventSink`  
_L73-89_
- desc: Interface for classes that receive media player events.
- L83 _public prototype_ `virtual void ReceiveMediaEvent(EMediaEvent Event) = 0;` — Receive the given media event. @param Event The event to receive. @note Implementors must be thread-safe as this method may be called from arbitrary worker threads.
- L88 _public prototype_ `virtual ~IMediaEventSink() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaMetadataItem.h` (Public)


#### class `IMediaMetadataItem`  
`class IMediaMetadataItem`  
_L11-35_
- desc: This structure describes a metadata item.
- L14 _public prototype_ `virtual ~IMediaMetadataItem() = default;`
- L21 _public prototype_ `virtual const FString& GetLanguageCode() const = 0;` — Language this item is described in. This should a three letter ISO 639-2 code. If no language is specified this item is intended to be used when no other item exists in the user's preferred language.
- L29 _public prototype_ `virtual const FString& GetMimeType() const = 0;` — Optional mime type of the item described by Value. This should be set when Value is of type EVariantTypes::ByteArray For example, if this item is a binary JPEG image the mime type should be set as "image/jpeg" to identify the type of the payload.
- L34 _public prototype_ `virtual const FVariant& GetValue() const = 0;` — The value of the metadata item.

### `Source/Runtime/Media/Public/IMediaModule.h` (Public)


#### class `IMediaModule`  
`class IMediaModule : public IModuleInterface`  
_L33-227_
- inherits: `IModuleInterface`
- desc: Interface for the Media module. Media Framework is ticked in several stages. The Input tick happens after the Engine (including Sequencer, game world, and Blueprints) were ticked. This allows any game logic to modify the state of tickable media objects before they fetch input. The Update tick happens right after the Input tick when all tickable media objects have fetched the latest input based on their current state. Finally, the Output tick happens after all game and core ticking completed, and after all render commands have been enqueued. It is the very last thing to happen before the frame is complete.
- L43 _public prototype_ `virtual FName GetPlatformName(const FGuid& PlatformGuid) const = 0;` — Get a nice platform name from a GUID
- L48 _public prototype_ `virtual FGuid GetPlatformGuid(const FName & PlatformName) const = 0;` — Get a GUID from a nice platform name
- L58 _public prototype_ `virtual const TArray<IMediaCaptureSupport*>& GetCaptureSupports() const = 0;` — Get all registered capture device support objects. @return Collection of registered objects. @see RegisterCaptureDevices, UnregisterCaptureDevices
- L66 _public prototype_ `virtual void RegisterCaptureSupport(IMediaCaptureSupport& Support) = 0;` — Register a media capture devices support object. @param Support The support object to register. @see GetCaptureDevices, UnregisterCaptureDevices
- L74 _public prototype_ `virtual void UnregisterCaptureSupport(IMediaCaptureSupport& Support) = 0;` — Unregister a media capture device support object. @param Support The support object to unregister. @see GetCaptureDevices, RegisterCaptureDevices
- L86 _public prototype_ `virtual const TArray<IMediaPlayerFactory*>& GetPlayerFactories() const = 0;` — Get the list of installed media player factories. @return Collection of media player factories. @see GetPlayerFactory, RegisterPlayerFactory, UnregisterPlayerFactory
- L95 _public prototype_ `virtual IMediaPlayerFactory* GetPlayerFactory(const FName& FactoryName) const = 0;` — Get a media player factory by name. @param FactoryName The name of the factory. @return The factory, or nullptr if not found. @see GetPlayerFactories, RegisterPlayerFactory, UnregisterPlayerFactory
- L104 _public prototype_ `virtual IMediaPlayerFactory* GetPlayerFactory(const FGuid& PlayerPluginGuid) const = 0;` — Get a media player factory by GUID. @param FactoryGuid The GUID of the factory / player. @return The factory, or nullptr if not found. @see GetPlayerFactories, RegisterPlayerFactory, UnregisterPlayerFactory
- L112 _public prototype_ `virtual void RegisterPlayerFactory(IMediaPlayerFactory& Factory) = 0;` — Register a media player factory. @param Factory The media player factory to register. @see GetPlayerFactories, RegisterPlayerFactory, UnregisterPlayerFactory
- L120 _public prototype_ `virtual void UnregisterPlayerFactory(IMediaPlayerFactory& Factory) = 0;` — Unregister a media player factory. @param Factory The media player factory to unregister. @see GetPlayerFactories, RegisterPlayerFactory, RegisterPlayerFactory
- L126 _public prototype_ `virtual void SetPlayerLifecycleManagerDelegate(IMediaPlayerLifecycleManagerDelegate* Delegate) = 0;` — Set player lifetime delegate @param Delegate Delegate instance to set for use. Use nullptr to reset delegate.
- L131 _public prototype_ `virtual IMediaPlayerLifecycleManagerDelegate* GetPlayerLifecycleManagerDelegate() = 0;` — Get player lifetime delegate
- L136 _public prototype_ `virtual uint64 CreateMediaPlayerInstanceID() = 0;` — Get new media player instance ID
- L148 _public prototype_ `virtual IMediaClock& GetClock() = 0;` — Get the media clock. @return Media clock. @see GetTicker, LockToTimecode
- L156 _public prototype_ `virtual IMediaTicker& GetTicker() = 0;` — Get the high-frequency ticker. @return The ticker. @see GetClock
- L161 _public prototype_ `virtual double GetFrameStartTime() const = 0;` — Get frame's processing approximate real time start time in seconds
- L168 _public prototype_ `virtual FSimpleMulticastDelegate& GetOnTickPreEngineCompleted() = 0;` — Get a Delegate that is trigger once all MediaClockSink are TickInput @return the OnTickPreEngineCompleted
- L178 _public prototype_ `virtual void LockToTimecode(bool Locked) = 0;` — Whether media objects should lock to the media clock's time code. Time code locking changes will take effect next frame. @param Locked true to enable time code locking, false to disable. @see GetClock
- L185 _public prototype_ `virtual void SetTimeSource(const TSharedPtr<IMediaTimeSource, ESPMode::ThreadSafe>& NewTimeSource) = 0;` — Set the time source for the media clock. @param NewTimeSource The time source to set.
- L193 _public prototype_ `virtual TSharedPtr<IMediaTimeSource, ESPMode::ThreadSafe> GetTimeSource() = 0;` — Get the time source for the media clock. @return The current time source.
- L200 _public prototype_ `virtual void TickPostEngine() = 0;` — Called by the main loop after the game engine has been ticked. @see TickPostRender, TickPreEngine, TickPreSlate
- L207 _public prototype_ `virtual void TickPostRender() = 0;` — Called by the main loop after the entire frame has been rendered. @see TickPostEngine, TickPreEngine, TickPreSlate
- L214 _public prototype_ `virtual void TickPreEngine() = 0;` — Called by the main loop before the game engine is ticked. @see TickPostEngine, TickPostRender, TickPreSlate
- L221 _public prototype_ `virtual void TickPreSlate() = 0;` — Called by the main loop before Slate is ticked. @see TickPostEngine, TickPostRender, TickPreEngine
- L226 _public prototype_ `virtual ~IMediaModule() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaOptions.h` (Public)


#### class `IMediaOptions`  
`class IMediaOptions`  
_L14-102_
- desc: Interface for media options.
- L29 _public prototype_ `virtual FName GetDesiredPlayerName() const = 0;` — Get the name of the desired native player. @return Native player name, or NAME_None to auto select.
- L38 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const = 0;` — Get a Boolean media option. @param Key The name of the option to get. @param DefaultValue The default value to return if the option is not set. @return The option value.
- L47 _public prototype_ `virtual double GetMediaOption(const FName& Key, double DefaultValue) const = 0;` — Get a double precision floating point media option. @param Key The name of the option to get. @param DefaultValue The default value to return if the option is not set. @return The option value.
- L56 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const = 0;` — Get a signed integer media option. @param Key The name of the option to get. @param DefaultValue The default value to return if the option is not set. @return The option value.
- L65 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const = 0;` — Get a string media option. @param Key The name of the option to get. @param DefaultValue The default value to return if the option is not set. @return The option value.
- L74 _public prototype_ `virtual FText GetMediaOption(const FName& Key, const FText& DefaultValue) const = 0;` — Get a localized text media option. @param Key The name of the option to get. @param DefaultValue The default value to return if the option is not set. @return The option value.
- L84 _public function_ `virtual TSharedPtr<FDataContainer, ESPMode::ThreadSafe> GetMediaOption(const FName& Key, const TSharedPtr<FDataContainer, ESPMode::ThreadSafe>& DefaultValue) const` — Get a complex data type media option. @param Key The name of the option to get. @param DefaultValue The default value to return if the option is not set. @return The option value.
- L95 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const = 0;` — Check whether the specified option is set. @param Key The name of the option to check. @return true if the option is set, false otherwise.
- L101 _public prototype_ `virtual const UObject* ToUObject() const = 0;` — @return a object that can be used by the UObject garbage collection system to keep this object alive. Players should not store a pointer of the interface but some players use the interface in async functionality and the object needs to be kept alive during those.

#### class `IMediaOptions::FDataContainer`  
`class FDataContainer : public TSharedFromThis<FDataContainer, ESPMode::ThreadSafe>`  
_L18-22_
- inherits: `TSharedFromThis<FDataContainer,ESPMode::ThreadSafe>`
- L21 _public prototype_ `virtual ~FDataContainer() = default;`

### `Source/Runtime/Media/Public/IMediaOverlaySample.h` (Public)


#### enum `EMediaOverlaySampleType`  
`enum class EMediaOverlaySampleType`  
_L15-25_
- desc: Type of text overlay samples.
- L18 _public enumerator_ `Caption` — Caption text for hearing impaired users.
- L21 _public enumerator_ `Subtitle` — Subtitle text for non-native speakers.
- L24 _public enumerator_ `Text` — Generic text.

#### class `IMediaOverlaySample`  
`class IMediaOverlaySample`  
_L31-95_
- desc: Interface for media overlay text samples.
- L40 _public prototype_ `virtual FTimespan GetDuration() const = 0;` — Get the amount of time for which the sample should be displayed. @return Sample duration.
- L48 _public prototype_ `virtual TOptional<FVector2D> GetPosition() const = 0;` — Get the position at which to display the text. @return Display position (relative to top-left corner, in pixels). @see GetText
- L56 _public prototype_ `virtual FText GetText() const = 0;` — Get the sample's text. @return The overlay text. @see GetPosition, GetType
- L65 _public prototype_ `virtual FMediaTimeStamp GetTime() const = 0;` — Get the sample time (in the player's local clock). This value is used primarily for debugging purposes. @return Sample time.
- L73 _public function_ `virtual TOptional<FTimecode> GetTimecode() const` — Get the sample timecode if available. @return Sample timecode. @see GetTime
- L81 _public prototype_ `virtual EMediaOverlaySampleType GetType() const = 0;` — Get the sample type. @return Sample type. @see GetText
- L88 _public function_ `virtual FGuid GetGUID() const` — Get the GUID identifying the derived type that may implement additional, type specific methods. If the GUID matches a type known type it is safe to static cast this class to the derived type.
- L93 _public prototype_ `virtual ~IMediaOverlaySample() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaPlayer.h` (Public)


#### class `IMediaPlayer`  
`class IMediaPlayer`  
_L34-393_
- desc: Interface for media players. @see IMediaPlayerFactory
- L53 _public prototype_ `virtual void Close() = 0;` — Close a previously opened media source. Call this method to free up all resources associated with an opened media source. If no media is open, this function has no effect. The media may not necessarily be closed after this function succeeds, because closing may happen asynchronously. Subscribe to the MediaClosed event to detect when the media finished closing. This events is only triggered if Close returns true. @see IsReady, Open
- L63 _public prototype_ `virtual IMediaCache& GetCache() = 0;` — Get the player's cache controls. The interface returned by this method must remain valid for the player's life time. @return Cache controls. @see GetControls, GetSamples, GetTracks, GetView
- L73 _public prototype_ `virtual IMediaControls& GetControls() = 0;` — Get the player's playback controls. The interface returned by this method must remain valid for the player's life time. @return Playback controls. @see GetCache, GetSamples, GetTracks, GetView
- L81 _public prototype_ `virtual FString GetInfo() const = 0;` — Get debug information about the player and currently opened media. @return Information string. @see GetStats
- L89 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const = 0;` — Get the GUID for this player plugin. @return Media player GUID (usually corresponds to a player name) @see GetPlayerName
- L99 _public prototype_ `virtual IMediaSamples& GetSamples() = 0;` — Get the player's sample queue. The interface returned by this method must remain valid for the player's life time. @return Cache interface. @see GetCache, GetControls, GetTracks, GetView
- L107 _public prototype_ `virtual FString GetStats() const = 0;` — Get playback statistics information. @return Information string. @see GetInfo
- L117 _public prototype_ `virtual IMediaTracks& GetTracks() = 0;` — Get the player's track collection. The interface returned by this method must remain valid for the player's life time. @return Tracks interface. @see GetCache, GetControls, GetSamples, GetView
- L124 _public prototype_ `virtual FString GetUrl() const = 0;` — Get the URL of the currently loaded media. @return Media URL.
- L134 _public prototype_ `virtual IMediaView& GetView() = 0;` — Get the player's view settings. The interface returned by this method must remain valid for the player's life time. @return View interface. @see GetCache, GetControls, GetSamples, GetTracks
- L153 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) = 0;` — Open a media source from a URL with optional parameters. The media may not necessarily be opened after this function succeeds, because opening may happen asynchronously. Subscribe to the MediaOpened and MediaOpenFailed events to detect when the media finished or failed to open. These events are only triggered if Open returns true. The optional parameters can be used to configure aspects of media playback and are specific to the type of media source and the underlying player. Check their documentation for available keys and values. @param Url The URL of the media to open (file name or web address). @param Options Optional media parameters. @return true if the media is being opened, false otherwise. @see Close, IsReady, OnOpen, OnOpenFailed
- L173 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) = 0;` — Open a media source from a file or memory archive with optional parameters. The media may not necessarily be opened after this function succeeds, because opening may happen asynchronously. Subscribe to the MediaOpened and MediaOpenFailed events to detect when the media finished or failed to open. These events are only triggered if Open returns true. The optional parameters can be used to configure aspects of media playback and are specific to the type of media source and the underlying player. Check their documentation for available keys and values. @param Archive The archive holding the media data. @param OriginalUrl The original URL of the media that was loaded into the buffer. @param Options Optional media parameters. @return true if the media is being opened, false otherwise. @see Close, IsReady, OnOpen, OnOpenFailed
- L183 _public function_ `virtual bool Open(const FString& Url, const IMediaOptions* Options, const FMediaPlayerOptions* PlayerOptions)` — Open a media source from a URL with optional asset and player parameters.
- L195 _public function_ `virtual FVariant GetMediaInfo(FName InfoName) const` — Get information about the media that is playing. @param	InfoName		Name of the information we want. @returns					Requested information, or empty if not available. @see						UMediaPlayer::GetMediaInfo.
- L212 _public function_ `virtual TSharedPtr<TMap<FString, TArray<TUniquePtr<IMediaMetadataItem>>>, ESPMode::ThreadSafe> GetMediaMetadata() const` — Gets the current metadata of the media source. Metadata is optional and if present is typically a collection of key/value items without a well defined meaning. It may contain information on copyright, album name, artist and such, but the availability of any item is not mandatory and the representation will vary with the type of media. Interpretation therefor requires the application to be aware of the type of media being loaded and the possible metadata it may carry. Metadata may change over time. Its presence or change is reported by a MetadataChanged event.
- L228 _public function_ `virtual FText GetMediaName() const` — Get the human readable name of the currently loaded media source. Depending on the type of media source, this might be the name of a file, the display name of a capture device, or some other identifying string. If the player does not provide a specialized implementation for this method, the media name will be derived from the current media URL. @return Media source name, or empty text if no media is opened @see GetPlayerName, GetUrl
- L245 _public function_ `virtual void SetGuid(const FGuid& Guid)` — Set the player's globally unique identifier. @param Guid The GUID to set.
- L256 _public function_ `virtual bool SetNativeVolume(float Volume)` — Set the player's native volume if supported. @param Volume The volume to set. @return true on success, false otherwise.
- L266 _public function_ `virtual void SetLastAudioRenderedSampleTime(FTimespan SampleTime)` — Notify player of last sample time of audio used. @param SampleTime The last audio sample dequeued by one of the audio sinks.
- L279 _public function_ `virtual void TickAudio()` — Tick the player's audio related code. This is a high-frequency tick function. Media players override this method to fetch and process audio samples, or to perform other time critical tasks. @see TickInput, TickFetch
- L294 _public function_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode)` — Tick the player in the Fetch phase. Media players may override this method to fetch newly decoded input samples before they are rendered on textures or audio components. @param DeltaTime Time since last tick. @param Timecode The current media time code. @see TickAudio, TickInput
- L309 _public function_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode)` — Tick the player in the Input phase. Media players may override this method to update their state before the Engine is being ticked, or to initiate the processing of input samples. @param DeltaTime Time since last tick. @param Timecode The current media time code. @see TickAudio, TickFetch
- L319 _public function_ `virtual bool FlushOnSeekStarted() const` — Flush sinks when seek begins @return true if sinks should be flushed when a seek starts
- L329 _public function_ `virtual bool FlushOnSeekCompleted() const` — Flush sinks when seek ends @return true if sinks should be flushed when a seek finishes
- L345 _public function_ `virtual bool GetPlayerFeatureFlag(EFeatureFlag ) const`
- L357 _public typedef_ `typedef TSharedRef<IAsyncResourceReleaseNotification, ESPMode::ThreadSafe> IAsyncResourceReleaseNotificationRef;`
- L362 _public function_ `virtual bool SetAsyncResourceReleaseNotification(IAsyncResourceReleaseNotificationRef AsyncDestructNotification)` — Set async resource release notification for use with IMediaPlayerLifecycleManagerDelegate
- L371 _public function_ `virtual uint32 GetNewResourcesOnOpen() const` — Return IMediaPlayerLifecycleManagerDelegate::ResourceFlags bitmask to indicate resource types recreated on a open call
- L380 _public function_ `virtual void RecordSourceOpenedEvent() const` — Records a source opened event to engine analytics, called when a player has successfully opened a media source
- L386 _public function_ `virtual bool ShouldAutoRecordSourceOpenedEvent() const` — Gets whether a source opened event should be automatically recorded after Open is called and returns true on a media player. Media players that operate asynchronously should set this to false and call RecordSourceOpenedEvent manually when appropriate.
- L392 _public prototype_ `virtual ~IMediaPlayer() = default;` — Virtual destructor.

#### enum `IMediaPlayer::EFeatureFlag`  
`enum class EFeatureFlag`  
_L334-343_
- L336 _public enumerator_ `AllowShutdownOnClose = 0` — Allow player to be shutdown right after 'close' event is received from it
- L337 _public enumerator_ `UsePlaybackTimingV2` — Use v2 playback timing and AV sync
- L338 _public enumerator_ `UseRealtimeWithVideoOnly` — Use realtime rather then game deltatime to control video playback if no audio is present
- L339 _public enumerator_ `AlwaysPullNewestVideoFrame` — Mediaframework will not gate video frame output with its own timing, but assumes "ASAP" as output time for every sample
- L340 _public enumerator_ `PlayerUsesInternalFlushOnSeek` — The player implements an internal flush logic on seeks and Mediaframework will not issue an explicit Flush() call to it on seeks
- L341 _public enumerator_ `IsTrackSwitchSeamless` — If track switching is seamless then a flush of sinks is not necessary.
- L342 _public enumerator_ `PlayerSelectsDefaultTracks` — Whether or not the player selects suitable track defaults.

#### class `IMediaPlayer::IAsyncResourceReleaseNotification`  
`class IAsyncResourceReleaseNotification`  
_L351-356_
- L354 _public prototype_ `virtual ~IAsyncResourceReleaseNotification() = default;`
- L355 _public prototype_ `virtual void Signal(uint32 ResourceFlags) = 0;`

### `Source/Runtime/Media/Public/IMediaPlayerFactory.h` (Public)


#### enum `EMediaFeature`  
`enum class EMediaFeature`  
_L19-53_
- desc: Enumerates available media player features.
- L22 _public enumerator_ `AudioSamples` — Audio output via Engine.
- L25 _public enumerator_ `AudioTracks` — Audio tracks.
- L28 _public enumerator_ `CaptionTracks` — Caption tracks.
- L31 _public enumerator_ `MetadataTracks` — Metadata tracks (implies output via Engine).
- L34 _public enumerator_ `OverlaySamples` — Captions, subtitle and text output via Engine.
- L37 _public enumerator_ `SubtitleTracks` — Subtitle tracks.
- L40 _public enumerator_ `TextTracks` — Generic text tracks.
- L43 _public enumerator_ `Video360` — 360 degree video controls.
- L46 _public enumerator_ `VideoSamples` — Video output via Engine.
- L49 _public enumerator_ `VideoStereo` — Stereoscopic video controls.
- L52 _public enumerator_ `VideoTracks` — Video tracks.

#### class `IMediaPlayerFactory`  
`class IMediaPlayerFactory`  
_L66-176_
- desc: Interface for media player factories. Media player factories are used to create instances of media player implementations. Most media players will be implemented inside plug-ins, which will register their factories on startup. The Media module will use the CanPlayUrl() method on this interface to determine which media player to instantiate for a given media source. @see IMediaPlayer
- L79 _public prototype_ `virtual bool CanPlayUrl(const FString& Url, const IMediaOptions* Options, TArray<FText>* OutWarnings, TArray<FText>* OutErrors) const = 0;` — Whether the player can play the specified source URL. @param Url The media source URL to check. @param Options Optional media player parameters. @param OutWarnings Will contain warning messages (optional). @param OutErrors will contain error messages (optional). @return true if the source can be played, false otherwise.
- L87 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Creates a media player. @param EventSink The object that will receive the player's events. @return A new media player, or nullptr if a player couldn't be created.
- L95 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Get the human readable name of the player. @return Display name text. @see GetName
- L103 _public prototype_ `virtual FName GetPlayerName() const = 0;` — Get the unique name of the media player. @return Media player name, i.e. 'AndroidMedia' or 'WmfMedia'. @see GetDisplayName
- L111 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const = 0;` — Get the GUID for this player plugin. @return Media player GUID (usually corresponds to a player name) @see GetPlayerName
- L122 _public prototype_ `virtual const TArray<FString>& GetSupportedPlatforms() const = 0;` — Get the names of platforms that the media player supports. The returned platforms names must match the ones returned by FPlatformProperties::IniPlatformName, i.e. "Windows", "Android", etc. @return Platform name collection. @see GetOptionalParameters, GetRequiredParameters, GetSupportedFileExtensions, GetSupportedUriSchemes
- L130 _public prototype_ `virtual bool SupportsFeature(EMediaFeature Feature) const = 0;` — Check whether the media player supports the specified feature. @param Feature The feature to check. @return true if the feature is supported, false otherwise.
- L141 _public function_ `bool CanPlayUrl(const FString& Url, const IMediaOptions* Options) const` — Whether the player can play the specified source URL. @param Url The media source URL to check. @param Options Optional media player parameters. @return true if the source can be played, false otherwise.
- L155 _public function_ `virtual int32 GetPlayabilityConfidenceScore(const FString& Url, const IMediaOptions* Options, TArray<FText>* OutWarnings, TArray<FText>* OutErrors) const` — Returns a confidence score how sure the player thinks it is to be able to play the specified source URL. @param Url The media source URL to check. @param Options Optional media player parameters. @param OutWarnings Will contain warning messages (optional). @param OutErrors will contain error messages (optional). @return A score giving a probability (0-100 (or higher if necessary)) whether or not the media can be played.
- L167 _public function_ `bool SupportsPlatform(const FString& PlatformName) const` — Whether the player works on the given platform. @param PlatformName The name of the platform to check. @return true if the platform is supported, false otherwise. @see GetSupportedPlatforms
- L175 _public prototype_ `virtual ~IMediaPlayerFactory() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaSamples.h` (Public)


#### class `IMediaSamples`  
`class IMediaSamples`  
_L23-174_
- desc: Interface for access to a media player's sample queue. @see IMediaCache, IMediaControls, IMediaPlayer, IMediaTracks, IMediaView
- L37 _public function_ `virtual bool FetchAudio(TRange<FTimespan> TimeRange, TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& OutSample)` — Fetch the next audio sample. @param TimeRange The range of present times that the sample is allowed to have. @param OutSample Will contain the sample if the queue is not empty. @return true if the returned sample is valid, false otherwise. @see FetchCaption, FetchMetadata, FetchSubtitle, FetchVideo
- L41 _public function_ `virtual bool FetchAudio(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& OutSample)`
- L54 _public function_ `virtual bool FetchCaption(TRange<FTimespan> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample)` — Fetch the next caption sample. @param TimeRange The range of present times that the sample is allowed to have. @param OutSample Will contain the sample if the queue is not empty. @return true if the returned sample is valid, false otherwise. @see FetchAudio, FetchMetadata, FetchSubtitle, FetchVideo
- L58 _public function_ `virtual bool FetchCaption(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample)`
- L71 _public function_ `virtual bool FetchMetadata(TRange<FTimespan> TimeRange, TSharedPtr<IMediaBinarySample, ESPMode::ThreadSafe>& OutSample)` — Fetch the next metadata sample. @param TimeRange The range of present times that the sample is allowed to have. @param OutSample Will contain the sample if the queue is not empty. @return true if the returned sample is valid, false otherwise. @see FetchAudio, FetchCaption, FetchSubtitle, FetchVideo
- L75 _public function_ `virtual bool FetchMetadata(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaBinarySample, ESPMode::ThreadSafe>& OutSample)`
- L88 _public function_ `virtual bool FetchSubtitle(TRange<FTimespan> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample)` — Fetch the next subtitle sample. @param TimeRange The range of present times that the sample is allowed to have. @param OutSample Will contain the sample if the queue is not empty. @return true if the returned sample is valid, false otherwise. @see FetchAudio, FetchCaption, FetchMetadata, FetchVideo
- L92 _public function_ `virtual bool FetchSubtitle(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample)`
- L105 _public function_ `virtual bool FetchVideo(TRange<FTimespan> TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample)` — Fetch the next video sample. @param TimeRange The range of present times that the sample is allowed to have. @param OutSample Will contain the sample if the queue is not empty. @return true if the returned sample is valid, false otherwise. @see FetchAudio, FetchCaption, FetchMetadata, FetchSubtitle
- L109 _public function_ `virtual bool FetchVideo(TRange<FMediaTimeStamp> TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample)`
- L115 _public function_ `virtual void FlushSamples()` — Discard any outstanding media samples.
- L121 _public function_ `virtual void SetSampleBufferSize(int32 BufferSize)` — Sets the number of samples to be stored in sample container.
- L130 _public function_ `virtual EFetchBestSampleResult FetchBestVideoSampleForTimeRange(const TRange<FMediaTimeStamp>& TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample, bool bReverse, bool bConsistentResult)`
- L134 _public function_ `virtual void SetMinExpectedNextSequenceIndex(TOptional<int32> InNextSequenceIndex)`
- L136 _public prototype_ `virtual bool PeekVideoSampleTime(FMediaTimeStamp& TimeStamp) = 0;`
- L138 _public function_ `virtual bool PeekVideoSampleTimeRanges(TArray<TRange<FMediaTimeStamp>>& TimeRange)`
- L139 _public function_ `virtual bool PeekAudioSampleTimeRanges(TArray<TRange<FMediaTimeStamp>>& TimeRange)`
- L141 _public function_ `virtual bool DiscardVideoSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse)`
- L142 _public function_ `virtual bool DiscardAudioSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse)`
- L143 _public function_ `virtual bool DiscardCaptionSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse)`
- L144 _public function_ `virtual bool DiscardSubtitleSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse)`
- L145 _public function_ `virtual bool DiscardMetadataSamples(const TRange<FMediaTimeStamp>& TimeRange, bool bReverse)`
- L147 _public function_ `virtual uint32 PurgeOutdatedVideoSamples(const FMediaTimeStamp& ReferenceTime, bool bReversed, FTimespan MaxAge)`
- L148 _public function_ `virtual uint32 PurgeOutdatedCaptionSamples(const FMediaTimeStamp& ReferenceTime, bool bReversed, FTimespan MaxAge)`
- L149 _public function_ `virtual uint32 PurgeOutdatedSubtitleSamples(const FMediaTimeStamp& ReferenceTime, bool bReversed, FTimespan MaxAge)`
- L150 _public function_ `virtual uint32 PurgeOutdatedMetadataSamples(const FMediaTimeStamp& ReferenceTime, bool bReversed, FTimespan MaxAge)`
- L152 _public function_ `virtual bool CanReceiveVideoSamples(uint32 Num) const`
- L153 _public function_ `virtual bool CanReceiveAudioSamples(uint32 Num) const`
- L154 _public function_ `virtual bool CanReceiveSubtitleSamples(uint32 Num) const`
- L155 _public function_ `virtual bool CanReceiveCaptionSamples(uint32 Num) const`
- L156 _public function_ `virtual bool CanReceiveMetadataSamples(uint32 Num) const`
- L158 _public function_ `virtual int32 NumAudioSamples() const`
- L159 _public function_ `virtual int32 NumCaptionSamples() const`
- L160 _public function_ `virtual int32 NumMetadataSamples() const`
- L161 _public function_ `virtual int32 NumSubtitleSamples() const`
- L162 _public function_ `virtual int32 NumVideoSamples() const`
- L164 _public function_ `virtual uint32 GetNumDroppedVideoSamples(bool bInClearToZero)`
- L165 _public function_ `virtual uint32 GetNumDroppedAudioSamples(bool bInClearToZero)`
- L166 _public function_ `virtual uint32 GetNumDroppedSubtitleSamples(bool bInClearToZero)`
- L167 _public function_ `virtual uint32 GetNumDroppedCaptionSamples(bool bInClearToZero)`
- L168 _public function_ `virtual uint32 GetNumDroppedMetadataSamples(bool bInClearToZero)`
- L173 _public prototype_ `virtual ~IMediaSamples() = default;` — Virtual destructor.

#### enum `IMediaSamples::EFetchBestSampleResult`  
`enum class EFetchBestSampleResult`  
_L123-129_
- L125 _public enumerator_ `Ok = 0`
- L126 _public enumerator_ `NoSample`
- L127 _public enumerator_ `PurgedToEmpty`
- L128 _public enumerator_ `NotSupported`

### `Source/Runtime/Media/Public/IMediaTextureSample.h` (Public)


#### enum `EMediaTextureSampleFormat`  
`enum class EMediaTextureSampleFormat`  
_L41-132_
- desc: Available formats for media texture samples. Depending on the decoder, the pixel data of a media texture frame may be stored in one of the listed formats. Some of these may be supported natively by the renderer, others may require a conversion step to a natively supported format. The media texture sink is responsible for performing any necessary conversions. For details on the various YUV packings see: https://www.fourcc.org/yuv.php
- L44 _public enumerator_ `Undefined` — Format not defined.
- L47 _public enumerator_ `CharAYUV` — Four 8-bit unsigned integer components (AYUV packing) per texel.
- L50 _public enumerator_ `CharBGRA` — Four 8-bit unsigned integer components (Blue, Green, Red, Alpha) per texel.
- L53 _public enumerator_ `CharRGBA` — Four 8-bit unsigned integer components (Blue, Green, Red, Alpha) per texel.
- L56 _public enumerator_ `CharBGR10A2` — Four 10-bit unsigned integer components (Blue, Green, Red) & 2-bit alpha per texel.
- L59 _public enumerator_ `CharBMP` — Windows bitmap (like CharBGRA, but flipped vertically).
- L62 _public enumerator_ `CharNV12` — NV12 encoded monochrome texture with 8 bits per channel.
- L65 _public enumerator_ `CharNV21` — NV21 encoded monochrome texture with 8 bits per channel.
- L68 _public enumerator_ `CharUYVY` — Four 8-bit unsigned integer components (UYVY packing aka. HDYC, IUYV, UYNV, Y422) per texel.
- L71 _public enumerator_ `CharYUY2` — Four 8-bit unsigned integer components (YUY2 packing aka. YUNV, YUYV) per texel.
- L74 _public enumerator_ `Char2VUY` — Four 8-bit unsigned integer components (UYVY) per texel.
- L77 _public enumerator_ `CharYVYU` — Four 8-bit unsigned integer components (YVYU packing) per texel.
- L80 _public enumerator_ `FloatRGB` — Three 16-bit floating point components (Red, Green, Blue) per texel.
- L83 _public enumerator_ `FloatRGBA` — Four 16-bit floating point components (Red, Green, Blue, Alpha) per texel.
- L86 _public enumerator_ `YUVv210` — YUV v210 format which pack 6 pixel using 12 x 10bits components (128 bits block).
- L89 _public enumerator_ `YUVv216` — YUV v216 format which pack 2 pixel using 4 x 16bits components
- L92 _public enumerator_ `ShortYUY2` — Packed YUYV (Y0CbY1Cr) on 16-bit unsigned integer components.
- L95 _public enumerator_ `Y416` — 4:4:4:4 AY'CbCr 16-bit little endian full range alpha, video range Y'CbCr.
- L98 _public enumerator_ `R4FL` — 4:4:4:4 AY'CbCr 32-bit little endian full range alpha, video range Y'CbCr.
- L101 _public enumerator_ `P010` — NV12-style encoded monochrome texture with 16 bits per channel, with the upper 10 bits used.
- L104 _public enumerator_ `DXT1` — DXT1.
- L107 _public enumerator_ `DXT5` — DXT5.
- L110 _public enumerator_ `BC4` — BC4.
- L113 _public enumerator_ `YCoCg_DXT5` — YCoCg colour space encoded in DXT5.
- L116 _public enumerator_ `YCoCg_DXT5_Alpha_BC4` — YCoCg colour space encoded in DXT5, with a separate alpha texture encoded in BC4.
- L119 _public enumerator_ `P010_RGB1010102` — 3 planes of RGB1010102 data representing Y, U & V at 4:2:0 sampling.
- L122 _public enumerator_ `RGBA16` — RGBA 16-bit per component
- L125 _public enumerator_ `ABGR16` — ABGR 16-bit per component
- L128 _public enumerator_ `ARGB16_BIG` — ARGB 16-bit per component, big endian
- L131 _public enumerator_ `ExternalVYU` — External texture with 4 components (VYUX) per texel.

#### struct `FMediaTextureTilingDescription`  
`struct FMediaTextureTilingDescription`  
_L156-166_
- desc: Description of how the media texture sample is tiled (only used by tiled image sequences currently).
- L158 _public member_ `FIntPoint TileNum = FIntPoint::ZeroValue;`
- L159 _public member_ `FIntPoint TileSize = FIntPoint::ZeroValue;`
- L160 _public member_ `int32 TileBorderSize = 0;`
- L162 _public function_ `inline bool IsValid() const`

#### enum `EMediaOrientation`  
`enum class EMediaOrientation`  
_L168-174_
- L170 _public enumerator_ `Original = 0`
- L171 _public enumerator_ `CW90`
- L172 _public enumerator_ `CW180`
- L173 _public enumerator_ `CW270`

#### class `IMediaTextureSample`  
`class IMediaTextureSample`  
_L204-593_
- desc: Interface for media texture samples. Media texture samples are generated by media players and sent to the registered media texture sink. They contain a single frame of texture data along with extra metadata, such as dimensions, time codes, and durations. Depending on the decoder, a frame's pixel data may be stored in a CPU memory buffer, or in an RHI texture resource (only available when compiling against the Engine). The media texture sample API supports both models via the GetBuffer and the GetTexture methods. Sample instances need to implement only one of these.
- L215 _public prototype_ `virtual const void* GetBuffer() = 0;` — Get the sample's frame buffer. The returned buffer is only valid for the life time of this sample. @return Buffer containing the texels, or nullptr if the sample holds an FTexture. @see GetDim, GetDuration, GetFormat, GetOutputDim, GetStride, GetTexture, GetTime
- L226 _public prototype_ `virtual FIntPoint GetDim() const = 0;` — Get the width and height of the sample. The sample may be larger than the output dimensions, because of horizontal or vertical padding required by some formats. @return Buffer dimensions (in texels). @see GetBuffer, GetDuration, GetFormat, GetOutputDim, GetStride, GetTexture, GetTime
- L234 _public function_ `virtual uint8 GetNumMips() const` — Get the number of mips encoded in the sample @return Number of mips in the sample (including base level) @note Default implementation provided as most samples will not feature mips
- L245 _public function_ `virtual FMediaTextureTilingDescription GetTilingDescription() const` — Get tile information (number, size and border size) of the sample. @return TileInfo struct @note Default implementation provided as most samples will not feature tiles
- L259 _public prototype_ `virtual FTimespan GetDuration() const = 0;` — Get the amount of time for which the sample is valid. A duration of zero indicates that the sample is valid until the timecode of the next sample in the queue. @return Sample duration. @see GetBuffer, GetDim, GetFormat, GetOutputDim, GetStride, GetTexture, GetTime
- L267 _public prototype_ `virtual EMediaTextureSampleFormat GetFormat() const = 0;` — Get the texture sample format. @return Sample format. @see GetBuffer, GetDim, GetDuration, GetOutputDim, GetStride, GetTexture, GetTime
- L278 _public prototype_ `virtual FIntPoint GetOutputDim() const = 0;` — Get the sample's desired output width and height. The output dimensions may be smaller than the frame buffer dimensions, because of horizontal and/or vertical padding that may be required for some formats. @return Output dimensions (in pixels). @see GetBuffer, GetDim, GetDuration, GetFormat, GetStride, GetTexture, GetTime
- L286 _public prototype_ `virtual uint32 GetStride() const = 0;` — Get the horizontal stride (aka. pitch) of the sample's frame buffer. @return The buffer stride (in number of bytes). @see GetBuffer, GetDim, GetDuration, GetFormat, GetOutputDim, GetTexture, GetTime
- L292 _public function_ `virtual bool ShouldApplyColorConversion() const` — Whether samples should be converted based on a mismatch with the working color space. If this is false, samples will not go through the conversion process even if their encoding or chromaticity doesn't match the working color space.
- L302 _public prototype_ `virtual FRHITexture* GetTexture() const = 0;` — Get the sample's texture resource. @return Texture resource, or nullptr if the sample holds a frame buffer. @see GetBuffer, GetDim, GetDuration, GetFormat, GetOutputDim, GetStride, GetTime
- L309 _public function_ `virtual IMediaTextureSampleConverter* GetMediaTextureSampleConverter()` — Get media texture sample converter if sample implements it @return texture sample converter
- L319 _public function_ `virtual IMediaTextureSampleColorConverter* GetMediaTextureSampleColorConverter()` — Get a media texture sample color converter if sample implements it @Note IMediaTextureSampleColorConverter will be applied after IMediaTextureSampleConverter if one is provided. @return texture sample color converter
- L329 _public function_ `virtual ETextureCreateFlags GetIntermediateTargetCreateFlagsHint() const` — Extra ETextureCreateFlags to OR into the intermediate render target for this sample. Lets samples opt into create-time policies (e.g. ReservedResource for sparse residency) without an RHI-wide engine change. Default: no extra flags.
- L344 _public prototype_ `virtual FMediaTimeStamp GetTime() const = 0;` — Get the sample time (in the player's local clock). This value is used primarily for debugging purposes. @return Sample time. @see GetBuffer, GetDim, GetDuration, GetFormat, GetOutputDim, GetStride, GetTexture
- L352 _public function_ `virtual TOptional<FTimecode> GetTimecode() const` — Get the sample timecode if available. @return Sample timecode. @see GetTime
- L361 _public function_ `virtual TOptional<FFrameRate> GetFramerate() const` — Get the sample framerate if available. This is the rate in which the timecode is measured. It is not necessarily the display frame rate. @return Sample framerate. May be needed for converting GetTimecode(). @see GetTime
- L371 _public prototype_ `virtual bool IsCacheable() const = 0;` — Whether the sample can be held in a cache. Non-cacheable video samples become invalid when the next sample is available, and only the latest sample should be kept by video sample consumers. @return true if cacheable, false otherwise.
- L378 _public prototype_ `virtual bool IsOutputSrgb() const = 0;` — Whether the output of the sample is in sRGB color space. @return true if sRGB, false otherwise.
- L385 _public function_ `virtual EMediaOrientation GetOrientation() const` — Get image orientation vs. physically returned image data @return Image orientation
- L395 _public function_ `virtual double GetAspectRatio() const` — Get pixel aspect ratio @return Pixel aspect ratio
- L404 _public function_ `virtual bool IsExternalImage() const` — Indicate if this sample references an "external image"
- L417 _public function_ `virtual FLinearColor GetScaleRotation() const` — Get the ScaleRotation (2x2 matrix) for the sample. @return FLinearColor with xy = row 0 (dotted with U), zw = row 1 (dotted with V) @note For use with "external image" style output only. Use GetOrientation() otherwise
- L430 _public function_ `virtual FLinearColor GetOffset() const` — Get the Offset applied after ScaleRotation for the sample. @return FLinearColor with xy = offset, zw must be zero @note For use with "external image" style output only
- L442 _public function_ `virtual const FMatrix& GetYUVToRGBMatrix() const` — Get the YUV to RGB conversion matrix. Default is equivalent to MediaShaders::YuvToRgbRec709Scaled Matrix. NOTE: previously in UE4 this was YuvToRgbRec601Scaled @return Conversion Matrix
- L450 _public function_ `virtual bool GetFullRange() const` — Get full range color flag
- L460 _public function_ `virtual FMatrix44f GetSampleToRGBMatrix() const` — Get complete 4x4 matrix to apply to the sample's pixels to yield RGB data in the sample's gamut @return Conversion Matrix
- L483 _public function_ `virtual const UE::Color::FColorSpace& GetSourceColorSpace() const` — Get sample source color space (defaults to the sRGB/Rec709 gamut)
- L489 _public function_ `virtual FMatrix44d GetGamutToXYZMatrix() const` — `UE_DEPRECATED(5.5, "GetGamutToXYZMatrix is deprecated, please use GetSourceColorSpace instead.")`
- L495 _public function_ `virtual FVector2d GetWhitePoint() const` — `UE_DEPRECATED(5.5, "GetWhitePoint is deprecated, please use GetSourceColorSpace instead.")`
- L501 _public function_ `virtual FVector2d GetDisplayPrimaryRed() const` — `UE_DEPRECATED(5.5, "GetDisplayPrimaryRed is deprecated, please use GetMasteringDisplayColorSpace instead.")`
- L507 _public function_ `virtual FVector2d GetDisplayPrimaryGreen() const` — `UE_DEPRECATED(5.5, "GetDisplayPrimaryGreen is deprecated, please use GetMasteringDisplayColorSpace instead.")`
- L513 _public function_ `virtual FVector2d GetDisplayPrimaryBlue() const` — `UE_DEPRECATED(5.5, "GetDisplayPrimaryBlue is deprecated, please use GetMasteringDisplayColorSpace instead.")`
- L521 _public function_ `virtual UE::Color::EChromaticAdaptationMethod GetChromaticAdapationMethod() const` — Chromatic adaptation method to be used when applying a color space transform (i.e. from source to working color space).
- L529 _public function_ `virtual UE::Color::EEncoding GetEncodingType() const` — Get EOTF / "Gamma" / encoding type of data
- L547 _public function_ `virtual float GetHDRNitsNormalizationFactor() const` — Linear-side scale that consumers may apply to normalize decoded transfer-function output to UE scene-linear (diffuse white = 1.0). Consumers typically multiply the color-space conversion matrix by this factor; how and when it is applied is up to the consumer. Subclasses should override this when the source metadata indicates a specific reference white. The canonical implementation calls UE::Color::GetReferenceWhiteLinearScale(GetEncodingType(), EReferenceWhite::XXX) so the scale resolves per encoding (e.g. 1/203 for PQ + BT2408, 1/DecodeHLG(0.75) for HLG + BT2408). The base default returns 1.0 so projects without tagging see spec-literal decoded values.
- L555 _public function_ `virtual bool GetDisplayMasteringLuminance(float& OutMin, float& OutMax) const` — Get display mastering luminance information
- L563 _public function_ `virtual TOptional<UE::Color::FColorSpace> GetDisplayMasteringColorSpace() const` — Get display mastering color space
- L571 _public function_ `virtual bool GetMaxLuminanceLevels(uint16& OutCLL, uint16& OutFALL) const` — Get maximum luminance information
- L579 _public function_ `virtual MediaShaders::EToneMapMethod GetToneMapMethod() const` — Get an optional tonemapping method, for application on HDR inputs.
- L587 _public function_ `virtual void Reset()` — Reset sample to empty state
- L592 _public prototype_ `virtual ~IMediaTextureSample() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L134 _namespace_ `namespace MediaTextureSampleFormat`
- L136 _prototype_ `const TCHAR* EnumToString(const EMediaTextureSampleFormat InSampleFormat);` (scope `MediaTextureSampleFormat`)
- L138 _function_ `static inline bool IsBlockCompressedFormat(EMediaTextureSampleFormat InSampleFormat)` (scope `MediaTextureSampleFormat`)
- L176 _namespace_ `namespace MediaTextureSample`
- L180 _variable_ `static constexpr float kLinearToNitsScale_UE = 100.0f;` (scope `MediaTextureSample`) — `UE_DEPRECATED(5.8, "Use UE::Color::GetReferenceWhiteLinearScale for pipeline normalization; any additional white-level adjustment should happen in the consuming material.")` — UE's historical reference white level for mapping scene-referred colors to nits (see TonemapCommon.ush).
- L184 _variable_ `static constexpr float kLinearToNitsScale_BT2408 = 203.0f;` (scope `MediaTextureSample`) — `UE_DEPRECATED(5.8, "Use UE::Color::GetReferenceWhiteLinearScale(EEncoding, EReferenceWhite::BT2408) for pipeline normalization; any additional white-level adjustment should happen in the consuming material.")` — This the reference white level for mapping SDR 1.0 to nits, as defined by ITU-R Report BT.2408.
- L189 _variable_ `static constexpr float kMediaSample_HDR_NitsNormalizationFactor = 1.0f / MediaTextureSample::kLinearToNitsScale_UE;` — `UE_DEPRECATED(5.8, "Use UE::Color::GetReferenceWhiteLinearScale(EEncoding, EReferenceWhite) for pipeline normalization; any additional white-level adjustment should happen in the consuming material.")`

### `Source/Runtime/Media/Public/IMediaTextureSampleConverter.h` (Public)


#### class `IMediaTextureSampleConverter`  
`class IMediaTextureSampleConverter`  
_L14-44_
- desc: Interface class to implement custom sample conversion
- L17 _public prototype_ `virtual ~IMediaTextureSampleConverter() = default;`
- L32 _public function_ `virtual uint32 GetConverterInfoFlags() const`
- L37 _public prototype_ `virtual bool Convert(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, const FConversionHints& Hints) = 0;`
- L40 _public function_ `bool Convert(FTextureRHIRef& InDstTexture, const FConversionHints& Hints)` — `UE_DEPRECATED(5.5, "The overload of IMediaTextureSampleConverter::Convert which does not take an RHI command list is deprecated.")`

#### enum `IMediaTextureSampleConverter::EConverterInfoFlags`  
`enum EConverterInfoFlags`  
_L19-25_
- L21 _public enumerator_ `ConverterInfoFlags_Default = 0`
- L22 _public enumerator_ `ConverterInfoFlags_WillCreateOutputTexture = 1 << 0`
- L23 _public enumerator_ `ConverterInfoFlags_PreprocessOnly = 1 << 1`
- L24 _public enumerator_ `ConverterInfoFlags_NeedUAVOutputTexture = 1 << 2`

#### struct `IMediaTextureSampleConverter::FConversionHints`  
`struct FConversionHints`  
_L27-30_
- L29 _public member_ `uint8 NumMips;`

#### class `IMediaTextureSampleColorConverter`  
`class IMediaTextureSampleColorConverter`  
_L49-65_
- desc: Interface class to implement custom sample color conversion
- L52 _public prototype_ `virtual ~IMediaTextureSampleColorConverter() = default;`
- L58 _public prototype_ `virtual bool ApplyColorConversion(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InSrcTexture, FTextureRHIRef& InDstTexture) = 0;` — Apply a color conversion on the input and store the result in the destination texture. @return true If the color conversion was successfully applied.
- L61 _public function_ `bool ApplyColorConversion(FTextureRHIRef& InSrcTexture, FTextureRHIRef& InDstTexture)` — `UE_DEPRECATED(5.5, "The overload of IMediaTextureSampleColorConverter::ApplyColorConversion which does not take an RHI command list is deprecated.")`

### `Source/Runtime/Media/Public/IMediaTickable.h` (Public)


#### class `IMediaTickable`  
`class IMediaTickable`  
_L9-20_
- desc: Interface for objects that can be ticked from the high-frequency media thread.
- L14 _public prototype_ `virtual void TickTickable() = 0;` — Tick the object.
- L19 _public prototype_ `virtual ~IMediaTickable() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaTicker.h` (Public)


#### class `IMediaTicker`  
`class IMediaTicker`  
_L13-37_
- desc: Interface for the high-frequency media ticker.
- L23 _public prototype_ `virtual void AddTickable(const TSharedRef<IMediaTickable, ESPMode::ThreadSafe>& Tickable) = 0;` — Add a media tickable object. @param Tickable The object to register. @see UnregisterTickable
- L31 _public prototype_ `virtual void RemoveTickable(const TSharedRef<IMediaTickable, ESPMode::ThreadSafe>& Tickable) = 0;` — Remove a media tickable object. @param Tickable The object to register. @see RegisterTickable
- L36 _public prototype_ `virtual ~IMediaTicker() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaTimeSource.h` (Public)


#### class `FMediaTimeStamp`  
`class FMediaTimeStamp`  
_L27-194_
- desc: Timestamp value for media playback - Time: Time value - SequenceIndex Sequence that is current for this time value Within a single sequence time values will increase or decrease monotonically. A new sequence index is generated on each event that causes the time to no longer be monotonic. (e.g. seek or loop) A sequence index does not offer any information about the ordering of the time stamps on the timeline. Time values are comparable between all timestamps from a single playback, though, one needs to be careful to consider non-monotonic behavior if the sequence indices are not identical. Sequence indices can very much offer ordering information as far as playback progression is concerned. Higher indices are also later in playback. (even if time values may be smaller: e.g. looping) All comparison operators of this class will operate to indicate ordering relative to playback, not position on the timeline!
- L30 _public function_ `FMediaTimeStamp() : Time(FTimespan::MinValue())`
- L32 _public function_ `explicit FMediaTimeStamp(const FTimespan& InTime) : Time(InTime)`
- L34 _public function_ `explicit FMediaTimeStamp(const FTimespan& InTime, int64 InSequenceValue) : Time(InTime) , SequenceIndex(GetSequenceIndex(InSequenceValue)) , LoopIndex(GetLoopIndex(InSequenceValue))`
- L39 _public function_ `explicit FMediaTimeStamp(const FTimespan& InTime, int32 InSequenceIndex, int32 InLoopIndex) : Time(InTime) , SequenceIndex(InSequenceIndex) , LoopIndex(InLoopIndex)`
- L45 _public function_ `void Invalidate()`
- L49 _public function_ `bool IsValid() const`
- L54 _public function_ `bool operator == (const FMediaTimeStamp& Other) const`
- L58 _public function_ `bool operator != (const FMediaTimeStamp& Other) const`
- L62 _public function_ `bool operator < (const FMediaTimeStamp& Other) const`
- L68 _public function_ `bool operator <= (const FMediaTimeStamp& Other) const`
- L72 _public function_ `bool operator > (const FMediaTimeStamp& Other) const`
- L76 _public function_ `bool operator >= (const FMediaTimeStamp & Other) const`
- L81 _public function_ `FMediaTimeStamp& SetTimeAndIndexValue(const FTimespan &InTime, int64 InIndexValue)`
- L88 _public function_ `FMediaTimeStamp& SetTime(const FTimespan &InTime)`
- L94 _public function_ `FMediaTimeStamp& SetSequenceIndex(int32 InSequenceIndex)`
- L99 _public function_ `FMediaTimeStamp& SetLoopIndex(int32 InLoopIndex)`
- L105 _public function_ `const FTimespan& GetTime() const`
- L109 _public function_ `int64 GetIndexValue() const`
- L114 _public function_ `FMediaTimeStamp& AdjustLoopIndex(int32 Add)`
- L120 _public function_ `int32 GetSequenceIndex() const`
- L125 _public function_ `int32 GetLoopIndex() const`
- L131 _public function_ `static int64 MakeIndexValue(int32 InSequenceIndex, int32 InLoopIndex)`
- L136 _public function_ `static int32 GetSequenceIndex(int64 InSequenceIndex)`
- L141 _public function_ `static int32 GetLoopIndex(int64 InSequenceIndex)`
- L146 _public function_ `FMediaTimeStamp operator + (const FTimespan& Other) const`
- L150 _public function_ `FMediaTimeStamp operator - (const FTimespan& Other) const`
- L155 _public function_ `FMediaTimeStamp operator - (const FMediaTimeStamp& Other) const`
- L171 _public function_ `FMediaTimeStamp& operator += (const FTimespan& Other)`
- L176 _public function_ `FMediaTimeStamp& operator -= (const FTimespan& Other)`
- L182 _public function_ `FMediaTimeStamp& operator -= (const FMediaTimeStamp& Other)`
- L190 _public member_ `FTimespan Time;`
- L192 _private member_ `int32 SequenceIndex = 0;`
- L193 _private member_ `int32 LoopIndex = 0;`

#### class `FMediaTimeStampSample`  
`class FMediaTimeStampSample`  
_L196-207_
- L199 _public function_ `FMediaTimeStampSample() : SampledAtTime(-1.0)`
- L200 _public function_ `FMediaTimeStampSample(const FMediaTimeStamp & InTimeStamp, double InSampledAtTime) : TimeStamp(InTimeStamp), SampledAtTime(InSampledAtTime)`
- L202 _public function_ `void Invalidate()`
- L203 _public function_ `bool IsValid() const`
- L205 _public member_ `FMediaTimeStamp TimeStamp;`
- L206 _public member_ `double SampledAtTime;`

#### class `IMediaTimeSource`  
`class IMediaTimeSource`  
_L212-227_
- desc: Interface for media clock time sources.
- L221 _public prototype_ `virtual FTimespan GetTimecode() = 0;` — Get the current time code. @return Time code.
- L226 _public prototype_ `virtual ~IMediaTimeSource() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaTracks.h` (Public)


#### enum `EMediaTrackType`  
`enum class EMediaTrackType`  
_L18-42_
- desc: Enumerates available media track types. Note: Keep this in sync with EMediaTrackType
- L21 _public enumerator_ `Audio` — Audio track.
- L24 _public enumerator_ `Caption` — Closed caption track.
- L27 _public enumerator_ `Metadata` — Metadata track.
- L30 _public enumerator_ `Script` — Script track.
- L33 _public enumerator_ `Subtitle` — Subtitle track.
- L36 _public enumerator_ `Text` — Generic text track.
- L39 _public enumerator_ `Video` — Video track.
- L41 _public enumerator_ `Num`

#### struct `FMediaAudioTrackFormat`  
`struct FMediaAudioTrackFormat`  
_L48-61_
- desc: Audio track format details.
- L51 _public member_ `uint32 BitsPerSample;` — Number of bits per sample.
- L54 _public member_ `uint32 NumChannels;` — Number of audio channels.
- L57 _public member_ `uint32 SampleRate;` — Sample rate (in samples per second).
- L60 _public member_ `FString TypeName;` — Name of the format type.

#### struct `FMediaVideoTrackFormat`  
`struct FMediaVideoTrackFormat`  
_L67-80_
- desc: Video track format details.
- L70 _public member_ `FIntPoint Dim;` — Width and height of the video (in pixels).
- L73 _public member_ `float FrameRate;` — Active frame rate (in frames per second).
- L76 _public member_ `TRange<float> FrameRates;` — Supported frame rate range.
- L79 _public member_ `FString TypeName;` — Name of the format type.

#### class `IMediaTracks`  
`class IMediaTracks`  
_L88-249_
- desc: Interface for access to a media player's tracks. @see IMediaCache, IMediaControls, IMediaPlayer, IMediaSamples, IMediaView
- L106 _public function_ `virtual TOptional<FTimespan> GetTrackDuration(EMediaTrackType TrackType, int32 TrackIndex) const` — Returns the duration of a specific track. If a media file contains multiple tracks each track may have different duration and the overall media duration is typically reported as that from the longest track. For some applications it may be required to know the exact track duration for processing, which is what this method returns if the media container, as well as the media player used for playback has the ability to provide it. @param TrackType The type of track to query. @param TrackIndex The index of the track to query. @return The duration of the track if known.
- L118 _public prototype_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const = 0;` — Get details about the specified audio track format. @param TrackIndex The index of the audio track (must be valid). @param FormatIndex The index of the track's format (must be valid). @param OutFormat Will contain the format details. @return true on success, false otherwise. @see GetVideoTrackFormat
- L127 _public prototype_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const = 0;` — Get the number of media tracks of the given type. @param TrackType The type of media tracks. @return Number of tracks. @see GetNumTrackFormats, GetSelectedTrack, SelectTrack
- L137 _public prototype_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const = 0;` — Get the number of formats of the specified track. @param TrackType The type of track. @param TrackIndex The index of the track (must be valid). @return Number of formats. @see GetNumTracks, GetTrackFormatType, GetTrackDisplayName
- L146 _public prototype_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const = 0;` — Get the index of the currently selected track of the given type. @param TrackType The type of track to get. @return The index of the selected track, or INDEX_NONE if no track is active. @see GetNumTracks, SelectTrack
- L156 _public prototype_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const = 0;` — Get the human readable name of the specified track. @param TrackType The type of track. @param TrackIndex The index of the track (must be valid). @return Display name. @see GetTrackLanguage, GetTrackName
- L166 _public prototype_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const = 0;` — Get the index of the currently selected format of the given track type. @param TrackType The type of track. @param TrackIndex The index of the track (must be valid). @return The index of the selected format. @see GetNumTrackFormats, GetSelectedTrack, SetTrackFormat
- L176 _public prototype_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const = 0;` — Get the language tag of the specified track. @param TrackType The type of track. @param TrackIndex The index of the track (must be valid). @return Language tag, i.e. "en-US" for English, or "und" for undefined. @see GetTrackDisplayName, GetTrackName
- L186 _public prototype_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const = 0;` — Get the internal name of the specified track. @param TrackType The type of track. @param TrackIndex The index of the track (must be valid). @return Track name. @see GetTrackDisplayName, GetTrackLanguage
- L197 _public prototype_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const = 0;` — Get details about the specified video track format. @param TrackIndex The index of the video track (must be valid). @param FormatIndex The index of the track's format (must be valid). @param OutFormat Will contain the format details. @return true on success, false otherwise. @see GetAudioTrackFormat
- L211 _public prototype_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) = 0;` — Select the active track of the given type. The selected track will use its currently active format. Active formats will be remembered on a per track basis. The first available format is active by default. To switch the track format, use SetTrackFormat instead. @param TrackType The type of track to select. @param TrackIndex The index of the track to select, or INDEX_NONE to deselect. @return true if the track was selected, false otherwise. @see GetNumTracks, GetSelectedTrack, SetTrackFormat
- L226 _public prototype_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) = 0;` — Select the active format on the specified track. Selecting the format will not switch to the specified track. To switch tracks, use SelectTrack instead. If the track is already selected, the format change will be applied immediately. @param TrackType The type of track to update. @param TrackIndex The index of the track to update (must be valid). @param FormatIndex The index of the format to select (must be valid). @return true if the format was selected, false otherwise. @see GetNumTrackFormats, GetNumTracks, GetTrackFormat, SelectTrack
- L240 _public function_ `virtual bool SetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex, float FrameRate)` — Set the frame rate of the specified video track. Note that most players may not support overriding the video frame rate. This feature is often only available on video capture media sources. @param TrackIndex The index of the track (must be valid). @param FormatIndex Index of the track format (must be valid). @param FrameRate The frame rate to set (must be in range of format's supported frame rates). @return true on success, false otherwise. @see GetTrackFormat, SetTrackFormat
- L248 _public prototype_ `virtual ~IMediaTracks() = default;` — Virtual destructor.

### `Source/Runtime/Media/Public/IMediaView.h` (Public)


#### struct `FMediaTileCoordinate`  
`struct UE_DEPRECATED(5.7, "Unused since virtual texture support was never fully submitted.") FMediaTileCoordinate`  
_L12-51_
- desc: Tile coordinate of a tiled media source/texture.
- L14 _public member_ `uint16 X, Y;`
- L14 _public member_ `uint16 X, Y;`
- L16 _public prototype_ `FMediaTileCoordinate() = default;`
- L18 _public function_ `inline explicit FMediaTileCoordinate(uint16 InX, uint16 InY) : X(InX) , Y(InY)`
- L24 _public function_ `inline explicit FMediaTileCoordinate(int32 InX, int32 InY) : X(IntCastChecked<uint16>(InX)) , Y(IntCastChecked<uint16>(InY))`
- L30 _public function_ `inline FMediaTileCoordinate(EForceInit) : X(0u) , Y(0u)`
- L36 _public function_ `inline bool operator==(const FMediaTileCoordinate& Other) const`
- L42 _public function_ `inline bool operator!=(const FMediaTileCoordinate& Other) const`
- L47 _public function_ `inline static FMediaTileCoordinate Zero()`

#### enum `TIsPODType::(anonymous)`  
`template <> struct TIsPODType<FMediaTileCoordinate>`  
_L54-54_

#### struct `TIsPODType`  
`template <> struct TIsPODType<FMediaTileCoordinate>`  
_L54-54_

#### class `IMediaView`  
`class IMediaView`  
_L89-260_
- desc: Interface for a media player's viewing settings. This interface is used to control viewing parameters in media players that support 360-degree or stereoscopic video output, or spatial audio output. There are currently three sets of configurable parameters: view, view focus and user settings. The view is the area that the user is looking at. Media players may use it to optimize the decoding of the media, i.e. only decode the sub-section of the video that is actually visible. The view focus is an optional area that allows for specifying which area the user is or should be focusing on. Media players may use it for foveated video rendering or for making the focused area more audible. The user settings can be used by media players to customize the generated audio or video output for specific users. Note: This view class has now been extended to also support tiled media sources such as tiled exr image sequences. Sets of visible tiles can be specified per mip level. @see IMediaCache, IMediaControls, IMediaPlayer, IMediaSamples, IMediaTracks
- L103 _public function_ `virtual bool GetViewField(float& OutHorizontal, float& OutVertical) const` — Get the field of view. @param OutHorizontal Will contain the horizontal field of view. @param OutVertical Will contain the vertical field of view. @return true on success, false if feature is not available or if field of view has never been set. @see GetViewOrientation, SetViewField
- L115 _public function_ `virtual bool GetViewOrientation(FQuat& OutOrientation) const` — Get the view's orientation. @param OutOrientation Will contain the view orientation. @return true on success, false if feature is not available or if orientation has never been set. @see GetViewField, SetViewOrientation
- L129 _public function_ `virtual bool SetViewField(float Horizontal, float Vertical, bool Absolute)` — Set the field of view. @param Horizontal Horizontal field of view (in Euler degrees). @param Vertical Vertical field of view (in Euler degrees). @param Whether the field of view change should be absolute (true) or relative (false). @return true on success, false otherwise. @see GetViewField, SetViewFocusField, SetViewOrientation
- L142 _public function_ `virtual bool SetViewOrientation(const FQuat& Orientation, bool Absolute)` — Set the view's orientation. @param Orientation Quaternion representing the orientation. @param Whether the orientation change should be absolute (true) or relative (false). @return true on success, false otherwise. @see GetViewOrientation, SetViewField
- L156 _public function_ `virtual bool IsViewFocusEnabled() const` — Whether the view focus is enabled. @return true if enabled, false otherwise.
- L168 _public function_ `virtual bool SetViewFocusEnabled(bool Enabled)` — Enable or disable view focus. @param Enabled true to enable, false to disable. @return true on success, false otherwise. @see IsViewFocusEnabled, SetViewFocusField, SetViewFocusOffImportance, SetViewFocusOrientation
- L181 _public function_ `virtual bool SetViewFocusField(float Horizontal, float Vertical)` — Set the view's focused field of view. @param Horizontal Horizontal field of view (in Euler degrees). @param Vertical Vertical field of view (in Euler degrees). @return true on success, false otherwise. @see SetViewFocusEnabled, SetViewFocusOffImportance, SetViewField, SetViewFocusOrientation
- L193 _public function_ `virtual bool SetViewFocusOffImportance(float Importance)` — Set the importance of the area that is not in focus. @param Importance Off-area importance (0.0 = no importance, 1.0 = important). @return true on success, false otherwise. @see SetViewFocusEnabled, SetViewFocusField, SetViewFocusOrientation
- L205 _public function_ `virtual bool SetViewFocusOrientation(const FQuat& Orientation)` — Set the view's focused orientation. @param Orientation Quaternion representing the viewer's orientation. @return true on success, false otherwise. @see SetViewFocusEnabled, SetViewFocusOffImportance, SetViewFocusField, SetViewField
- L220 _public function_ `virtual bool SetInteroccularDistance(float Distance)` — Set the inter-ocular distance. @param Distance The inter-ocular distance (in centimeters). @return true on success, false otherwise.
- L237 _public function_ `virtual bool GetVisibleTiles(TMap<int32, TSet<FMediaTileCoordinate>>& OutTiles) const` — `UE_DEPRECATED(5.7, "Unused since virtual texture support was never fully submitted.")` — Get the visible tiles per mip-level. @param OutTiles Map of visible tile sets per mip level index. @return true on success, false if feature is not available. @see SetVisibleTiles
- L250 _public function_ `virtual bool SetVisibleTiles(TMap<int32, TSet<FMediaTileCoordinate>>&& InTiles)` — `UE_DEPRECATED(5.7, "Unused since virtual texture support was never fully submitted.")` — Set the visible tiles per mip-level. @param InTiles Map of visible tile sets per mip level index. @return true on success, false if feature is not available. @see GetVisibleTiles
- L259 _public function_ `virtual ~IMediaView()` — Virtual destructor.

#### Free symbols / members of external scopes

- L54 _enumerator_ `template <> struct TIsPODType<FMediaTileCoordinate> { enum { Value = true }; }; inline uint32 GetTypeHash(const FMediaTileCoordinate& Coord) { return FCrc::TypeCrc32(Coord); } PRAGMA_ENABLE_DEPRECATION_WARNINGS` (scope `TIsPODType::__anona897d2600103`)
- L57 _function_ `inline uint32 GetTypeHash(const FMediaTileCoordinate& Coord)`
