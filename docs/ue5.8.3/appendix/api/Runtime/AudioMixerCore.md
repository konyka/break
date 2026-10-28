# Runtime / AudioMixerCore

- module root: `Source/Runtime/AudioMixerCore`
- headers: 8; symbols: 420
- symbol kinds: class=9, delegate=2, enum=7, enumerator=49, externvar=25, function=68, macro=41, member=98, namespace=12, prototype=86, struct=8, typedef=3, variable=12
- PrivateDependencyModuleNames: Core, SignalProcessing, TraceLog
- PublicIncludePathModuleNames: SignalProcessing

### `Source/Runtime/AudioMixerCore/Public/AudioDefines.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define MAX_AUDIOCHANNELS 64` — Maximum number of channels that can be set using the ini setting
- L16 _macro_ `#define INDEFINITELY_LOOPING_DURATION 10000.0f` — Length of sound in seconds to be considered as looping forever
- L22 _macro_ `#define SPEAKER_COUNT 6` — Some defaults to help cross platform consistency
- L24 _macro_ `#define DEFAULT_LOW_FREQUENCY 600.0f`
- L25 _macro_ `#define DEFAULT_MID_FREQUENCY 1000.0f`
- L26 _macro_ `#define DEFAULT_HIGH_FREQUENCY 2000.0f`
- L28 _macro_ `#define MAX_VOLUME 4.0f`
- L29 _macro_ `#define MIN_PITCH 0.4f`
- L30 _macro_ `#define MAX_PITCH 2.0f`
- L32 _macro_ `#define MIN_VOLUME_LINEAR SMALL_NUMBER`
- L33 _macro_ `#define MIN_VOLUME_DECIBELS -160.f`
- L35 _macro_ `#define MIN_SOUND_PRIORITY 0.0f`
- L36 _macro_ `#define MAX_SOUND_PRIORITY 100.0f`
- L38 _macro_ `#define DEFAULT_SUBTITLE_PRIORITY 10000.0f`
- L44 _macro_ `#define MIN_FILTER_GAIN 0.126f` — Some filters don't work properly with extreme values, so these are the limits
- L45 _macro_ `#define MAX_FILTER_GAIN 7.94f`
- L47 _macro_ `#define MIN_FILTER_FREQUENCY 20.0f`
- L48 _macro_ `#define MAX_FILTER_FREQUENCY 20000.0f`
- L50 _macro_ `#define MIN_FILTER_BANDWIDTH 0.1f`
- L51 _macro_ `#define MAX_FILTER_BANDWIDTH 2.0f`
- L57 _macro_ `#define ENABLE_AUDIO_DEBUG !UE_BUILD_SHIPPING` — Debugger is Available on non-shipping builds
- L61 _namespace_ `namespace Audio`
- L66 _typedef_ `using FDeviceId = uint32;` (scope `Audio`) — Typed identifier for Audio Device Id
- L70 _variable_ `inline constexpr float MonoUpmixFullVolume = 1.0f;` (scope `Audio`) — Magic numbers for mono upmix method
- L71 _variable_ `inline constexpr float MonoUpmixEqualPower = 0.707f;` (scope `Audio`)
- L72 _variable_ `inline constexpr float MonoUpmixLinear = 0.5f;` (scope `Audio`)

### `Source/Runtime/AudioMixerCore/Public/AudioMixer.h` (Public)


#### struct `Audio::FAudioPlatformDeviceInfo`  
`struct FAudioPlatformDeviceInfo`  
_L93-136_
- desc: Structure to hold platform device information
- L96 _public member_ `FString Name;` — The name of the audio device
- L99 _public member_ `FString DeviceId;` — ID of the device.
- L102 _public member_ `int32 NumChannels;` — The number of channels supported by the audio device
- L105 _public member_ `int32 NumDirectOutChannels;` — The number of channels above the base stereo or 7.1 channels supported by the audio device
- L108 _public member_ `int32 SampleRate;` — The sample rate of the audio device
- L111 _public member_ `EAudioMixerStreamDataFormat::Type Format;` — The data format of the audio stream
- L114 _public member_ `TArray<EAudioMixerChannel::Type> OutputChannelArray;` — The output channel array of the audio device
- L117 _public member_ `uint8 bIsSystemDefault : 1;` — Whether or not this device is the system default
- L119 _public function_ `FAudioPlatformDeviceInfo()`
- L124 _public function_ `void Reset()`

#### class `Audio::IAudioMixer`  
`class IAudioMixer`  
_L139-168_
- desc: Platform independent audio mixer interface.
- L143 _public prototype_ `virtual bool OnProcessAudioStream(FAlignedFloatBuffer& OutputBuffer) = 0;` — Callback to generate a new audio stream buffer.
- L146 _public prototype_ `virtual void OnAudioStreamShutdown() = 0;` — Called when audio render thread stream is shutting down. Last function called. Allows cleanup on render thread.
- L148 _public function_ `bool IsMainAudioMixer() const`
- L151 _public prototype_ `static bool ShouldUseThreadedDeviceSwap();` — Called by AudioMixer to see if we should do a multithreaded device swap
- L154 _public prototype_ `static bool ShouldRecycleThreads();` — Called by AudioMixer to see if it should reycle the threads:
- L158 _public prototype_ `static bool ShouldUseDeviceInfoCache();` — `UE_DEPRECATED(5.6, "ShouldUseDeviceInfoCache functionality moved to IAudioMixerPlatformInterface.")` — Called by AudioMixer if it should use Cache for DeviceInfo Enumeration
- L163 _protected function_ `IAudioMixer() : bIsMainAudioMixer(false)`
- L167 _protected member_ `bool bIsMainAudioMixer;`

#### enum `Audio::EDeviceEndpointType`  
`enum class EDeviceEndpointType`  
_L170-170_
- L170 _public enumerator_ `enum class EDeviceEndpointType { Unknown, Render, Capture }; enum class EAudioDeviceRole { Console, Multimedia, Communications,`
- L170 _public enumerator_ `enum class EDeviceEndpointType { Unknown, Render, Capture }; enum class EAudioDeviceRole { Console, Multimedia, Communications,`
- L170 _public enumerator_ `enum class EDeviceEndpointType { Unknown, Render, Capture }; enum class EAudioDeviceRole { Console, Multimedia, Communications,`

#### enum `Audio::EAudioDeviceRole`  
`enum class EAudioDeviceRole`  
_L172-179_
- L174 _public enumerator_ `Console`
- L175 _public enumerator_ `Multimedia`
- L176 _public enumerator_ `Communications`
- L178 _public enumerator_ `COUNT`

#### enum `Audio::EAudioDeviceState`  
`enum class EAudioDeviceState`  
_L181-189_
- L183 _public enumerator_ `Active`
- L184 _public enumerator_ `Disabled`
- L185 _public enumerator_ `NotPresent`
- L186 _public enumerator_ `Unplugged`
- L188 _public enumerator_ `COUNT`

#### class `Audio::IAudioPlatformDeviceInfoCache`  
`class IAudioPlatformDeviceInfoCache`  
_L192-214_
- desc: Interface for Caching Device Info.
- L196 _public prototype_ `virtual ~IAudioPlatformDeviceInfoCache() = default;` — Pure Interface.
- L198 _public prototype_ `virtual FName GetDefaultOutputDevice(EAudioDeviceRole InRole) const = 0;`
- L199 _public prototype_ `virtual TOptional<FAudioPlatformDeviceInfo> FindActiveOutputDevice(FName InDeviceID) const = 0;`
- L200 _public prototype_ `virtual TArray<FAudioPlatformDeviceInfo> GetAllActiveOutputDevices() const = 0;`
- L201 _public prototype_ `virtual TOptional<FAudioPlatformDeviceInfo> FindDefaultOutputDevice() const = 0;`
- L204 _public prototype_ `virtual bool IsAggregateHardwareDeviceId(const FName InDeviceId) const = 0;` — Determines if the given device Id is that of an aggregate device which uses hardware Ids as device Ids.
- L207 _public prototype_ `virtual TArray<FAudioPlatformDeviceInfo> GetLogicalAggregateDevices(const FName InHardwareId, const EDeviceEndpointType InEndpointType) const = 0;` — Returns an array of logical audio devices which, when combined, form an aggregate device.
- L210 _public prototype_ `virtual void Refresh() = 0;` — Refresh the data in the cache
- L213 _public prototype_ `virtual void InvalidateDevice(FName InDeviceId) = 0;` — Mark a device inactive after a caller observed it unreachable at the OS level.

#### struct `Audio::FAudioMixerOpenStreamParams`  
`struct FAudioMixerOpenStreamParams`  
_L217-256_
- desc: Defines parameters needed for opening a new audio stream to device.
- L220 _public member_ `uint32 OutputDeviceIndex;` — The audio device index to open.
- L223 _public member_ `uint32 NumFrames;` — The number of desired audio frames in audio callback.
- L226 _public member_ `int32 NumBuffers;` — The number of queued buffers to use for the stream.
- L229 _public member_ `IAudioMixer* AudioMixer;` — Owning platform independent audio mixer ptr.
- L232 _public member_ `uint32 SampleRate;` — The desired sample rate
- L235 _public member_ `int32 MaxSources;` — The maximum number of sources we will try to decode or playback at once.
- L238 _public member_ `bool bRestoreIfRemoved;` — Whether or not to try and restore audio to this stream if the audio device is removed (and the device becomes available again).
- L241 _public member_ `bool bUseSystemAudioDevice;` — If true, use the system default audio device. If False, AudioDeviceId must contain a valid device Id.
- L244 _public member_ `FString AudioDeviceId;` — The device id of an audio output device. May be empty if bUseSystemAudioDevice is true.
- L246 _public function_ `FAudioMixerOpenStreamParams() : OutputDeviceIndex(INDEX_NONE) , NumFrames(1024) , NumBuffers(1) , AudioMixer(nullptr) , SampleRate(44100) , MaxSources(0) , bRestoreIfRemoved(false) , bUseSystemAudioDevice(true)`

#### struct `Audio::FAudioOutputStreamInfo`  
`struct FAudioOutputStreamInfo`  
_L258-293_
- L261 _public member_ `uint32 OutputDeviceIndex;` — The index of the output device for the audio stream.
- L263 _public member_ `FAudioPlatformDeviceInfo DeviceInfo;`
- L266 _public member_ `std::atomic<EAudioOutputStreamState::Type> StreamState;` — The state of the output audio stream.
- L269 _public member_ `IAudioMixer* AudioMixer;` — The callback to use for platform-independent layer.
- L272 _public member_ `uint32 NumBuffers;` — The number of queued buffers to use.
- L275 _public member_ `int32 NumOutputFrames;` — Number of output frames
- L277 _public function_ `FAudioOutputStreamInfo()`
- L282 _public prototype_ `~FAudioOutputStreamInfo() = default;`
- L284 _public function_ `void Reset()`

#### struct `Audio::FAudioRenderTimeAnalysis`  
`struct FAudioRenderTimeAnalysis`  
_L296-310_
- desc: Struct used to store render time analysis data.
- L298 _public member_ `double AvgRenderTime;`
- L299 _public member_ `double MaxRenderTime;`
- L300 _public member_ `double TotalRenderTime;`
- L301 _public member_ `double RenderTimeSinceLastLog;`
- L302 _public member_ `uint32 StartTime;`
- L303 _public member_ `double MaxSinceTick;`
- L304 _public member_ `uint64 RenderTimeCount;`
- L305 _public member_ `int32 RenderInstanceId;`
- L307 _public prototype_ `FAudioRenderTimeAnalysis();`
- L308 _public prototype_ `void Start();`
- L309 _public prototype_ `void End();`

#### class `Audio::FOutputBuffer`  
`class FOutputBuffer`  
_L313-357_
- desc: Class which wraps an output float buffer and handles conversion to device stream formats.
- L316 _public function_ `FOutputBuffer() : AudioMixer(nullptr) , DataFormat(EAudioMixerStreamDataFormat::Unknown)`
- L321 _public prototype_ `~FOutputBuffer() = default;`
- L324 _public prototype_ `void Init(IAudioMixer* InAudioMixer, const int32 InNumSamples, const int32 InNumBuffers, const EAudioMixerStreamDataFormat::Type InDataFormat);` — Initialize the buffer with the given samples and output format.
- L327 _public prototype_ `bool MixNextBuffer();` — Gets the next mixed buffer from the audio mixer. Returns false if our buffer is already full.
- L330 _public prototype_ `TArrayView<const uint8> PopBufferData(int32& OutBytesPopped) const;` — Gets the buffer data ptrs. Returns a TArrayView for the full buffer size requested, but in the case of an underrun, OutBytesPopped will be less that the size of the returned TArrayView.
- L333 _public prototype_ `int32 GetNumSamples() const;` — Gets the number of frames of the buffer.
- L336 _public function_ `EAudioMixerStreamDataFormat::Type GetFormat() const` — Returns the format of the buffer.
- L340 _private member_ `IAudioMixer* AudioMixer;`
- L343 _private member_ `mutable Audio::TCircularAudioBuffer<uint8> CircularBuffer;` — Circular buffer used to buffer audio between the audio render thread and the platform interface thread.
- L346 _private member_ `Audio::FAlignedFloatBuffer RenderBuffer;` — Buffer that we render audio to from the IAudioMixer instance associated with this output buffer.
- L349 _private member_ `mutable Audio::FAlignedByteBuffer PopBuffer;` — Buffer read by the platform interface thread.
- L352 _private member_ `FAlignedByteBuffer FormattedBuffer;` — For non-float situations, this buffer is used to convert RenderBuffer before pushing it to CircularBuffer.
- L353 _private member_ `EAudioMixerStreamDataFormat::Type DataFormat;`
- L355 _private prototype_ `static size_t GetSizeForDataFormat(EAudioMixerStreamDataFormat::Type InDataFormat);`
- L356 _private member_ `int32 CallCounterMixNextBuffer{ 0 };`

#### class `Audio::IAudioMixerDeviceChangedListener`  
`class IAudioMixerDeviceChangedListener`  
_L360-393_
- desc: Abstract interface for receiving audio device changed notifications
- L363 _public prototype_ `virtual ~IAudioMixerDeviceChangedListener() = default;`
- L382 _public function_ `virtual void RegisterDeviceChangedListener()`
- L383 _public function_ `virtual void UnregisterDeviceChangedListener()`
- L384 _public function_ `virtual void OnDefaultCaptureDeviceChanged(const EAudioDeviceRole InAudioDeviceRole, const FString& DeviceId)`
- L385 _public function_ `virtual void OnDefaultRenderDeviceChanged(const EAudioDeviceRole InAudioDeviceRole, const FString& DeviceId)`
- L386 _public function_ `virtual void OnDeviceAdded(const FString& DeviceId, bool bIsRenderDevice)`
- L387 _public function_ `virtual void OnDeviceRemoved(const FString& DeviceId, bool bIsRenderDevice)`
- L388 _public function_ `virtual void OnDeviceStateChanged(const FString& DeviceId, const EAudioDeviceState InState, bool bIsRenderDevice)`
- L389 _public function_ `virtual void OnFormatChanged(const FString& InDeviceId, const FFormatChangedData& InFormat)`
- L390 _public function_ `virtual void OnSessionDisconnect(EDisconnectReason InReason)`
- L392 _public function_ `virtual FString GetDeviceId() const`

#### struct `Audio::IAudioMixerDeviceChangedListener::FFormatChangedData`  
`struct FFormatChangedData`  
_L365-370_
- L367 _public member_ `int32 NumChannels = 0;`
- L368 _public member_ `int32 SampleRate = 0;`
- L369 _public member_ `uint32 ChannelBitmask = 0;`

#### enum `Audio::IAudioMixerDeviceChangedListener::EDisconnectReason`  
`enum class EDisconnectReason`  
_L372-380_
- L374 _public enumerator_ `DeviceRemoval`
- L375 _public enumerator_ `ServerShutdown`
- L376 _public enumerator_ `FormatChanged`
- L377 _public enumerator_ `SessionLogoff`
- L378 _public enumerator_ `SessionDisconnected`
- L379 _public enumerator_ `ExclusiveModeOverride`

#### struct `Audio::FDeviceSwapContext`  
`struct FDeviceSwapContext`  
_L396-408_
- L398 _public prototype_ `FDeviceSwapContext() = delete;`
- L399 _public function_ `FDeviceSwapContext(const FString& InRequestedDeviceID, const FString& InReason) : RequestedDeviceId(InRequestedDeviceID), DeviceSwapReason(InReason)`
- L403 _public prototype_ `virtual ~FDeviceSwapContext() = default;`
- L405 _public member_ `FString RequestedDeviceId;`
- L406 _public member_ `FString DeviceSwapReason;`
- L407 _public member_ `TOptional<FAudioPlatformDeviceInfo> NewDevice;`

#### struct `Audio::FDeviceSwapResult`  
`struct FDeviceSwapResult`  
_L410-419_
- L412 _public prototype_ `virtual ~FDeviceSwapResult() = default;`
- L414 _public function_ `virtual bool IsNewDeviceReady() const`
- L416 _public member_ `FAudioPlatformDeviceInfo DeviceInfo;`
- L417 _public member_ `FString SwapReason;`
- L418 _public member_ `double SuccessfulDurationMs = 0.0;`

#### class `Audio::IAudioMixerPlatformInterface`  
`class IAudioMixerPlatformInterface : public FRunnable, public FSingleThreadRunnable, public IAudioMixerDeviceChangedListener`  
_L422-765_
- inherits: `FRunnable,FSingleThreadRunnable,IAudioMixerDeviceChangedListener`
- desc: Abstract interface for mixer platform.
- L430 _public prototype_ `virtual ~IAudioMixerPlatformInterface();` — Virtual destructor.
- L433 _public prototype_ `virtual FString GetPlatformApi() const = 0;` — Returns the platform API name.
- L436 _public prototype_ `virtual bool InitializeHardware() = 0;` — Initialize the hardware.
- L439 _public function_ `virtual bool CheckAudioDeviceChange()` — Check if audio device changed if applicable. Return true if audio device changed.
- L442 _public function_ `virtual void ResumePlaybackOnNewDevice()` — Resumes playback on new audio device after device change.
- L445 _public prototype_ `virtual bool TeardownHardware() = 0;` — Teardown the hardware.
- L448 _public prototype_ `virtual bool IsInitialized() const = 0;` — Is the hardware initialized.
- L451 _public function_ `virtual bool GetNumOutputDevices(uint32& OutNumOutputDevices)` — Returns the number of output devices.
- L454 _public prototype_ `virtual bool GetOutputDeviceInfo(const uint32 InDeviceIndex, FAudioPlatformDeviceInfo& OutInfo) = 0;` — Gets the device information of the given device index.
- L459 _public function_ `virtual FString GetCurrentDeviceName() const` — Returns the name of the currently used audio device.
- L466 _public prototype_ `virtual int32 GetIndexForDevice(const FString& InDeviceName);` — Can be used to look up the current index for a given device name. On most platforms, this index may be invalidated if any devices are added or removed. Returns INDEX_NONE if no mapping is found
- L469 _public prototype_ `virtual FAudioPlatformSettings GetPlatformSettings() const = 0;` — Gets the platform specific audio settings.
- L472 _public function_ `virtual bool GetDefaultOutputDeviceIndex(uint32& OutDefaultDeviceIndex) const` — Returns the default device index.
- L475 _public prototype_ `virtual bool OpenAudioStream(const FAudioMixerOpenStreamParams& Params) = 0;` — Opens up a new audio stream with the given parameters.
- L478 _public prototype_ `virtual bool CloseAudioStream() = 0;` — Closes the audio stream (if it's open).
- L481 _public prototype_ `virtual bool StartAudioStream() = 0;` — Starts the audio stream processing and generating audio.
- L484 _public prototype_ `virtual bool StopAudioStream() = 0;` — Stops the audio stream (but keeps the audio stream open).
- L488 _public function_ `virtual bool MoveAudioStreamToNewAudioDevice(const FString& InNewDeviceId)` — `UE_DEPRECATED(5.6, "Please use new version MoveAudioStreamToNewAudioDevice which takes no parameters.")` — Resets the audio stream to use a new audio device with the given device ID (empty string means default).
- L489 _public function_ `virtual bool MoveAudioStreamToNewAudioDevice()`
- L492 _public function_ `virtual bool RequestDeviceSwap(const FString& DeviceID, bool bInForce, const TCHAR* InReason = nullptr)` — Sends a command to swap which output device is being used
- L495 _public function_ `virtual void LockDeviceSwap()` — Protects device swap related resources during device swaps
- L498 _public function_ `virtual void UnlockDeviceSwap()` — Unprotects device swap resources. Balance with LockDeviceSwap()
- L501 _public prototype_ `virtual FAudioPlatformDeviceInfo GetPlatformDeviceInfo() const = 0;` — Returns the platform device info of the currently open audio stream.
- L504 _public function_ `virtual void SubmitBuffer(const uint8* Buffer)` — Submit the given buffer to the platform's output audio device.
- L507 _public function_ `virtual void SubmitDirectOutBuffer(const int32 InDirectOutIndex, const Audio::FAlignedFloatBuffer& InBuffer)` — Submit a buffer that is to be output directly through a discreet device channel.
- L510 _public function_ `virtual int32 GetNumFrames(const int32 InNumReqestedFrames)` — Allows platforms to filter the requested number of frames to render. Some platforms only support specific frame counts.
- L514 _public function_ `virtual bool DisablePCMAudioCaching() const` — `UE_DEPRECATED(5.7, "PCM Audio Caching is a leagacy feature that is now disabled for all platforms")` — Whether or not the platform disables caching of decompressed PCM data (i.e. to save memory on fixed memory platforms)
- L517 _public function_ `virtual bool SupportsHardwareDecompression() const` — Whether or not this platform has hardware decompression.
- L520 _public function_ `virtual bool IsNonRealtime() const` — Whether this is an interface for a non-realtime renderer. If true, synch events will behave differently to avoid deadlocks.
- L523 _public prototype_ `virtual FString GetDefaultDeviceName() = 0;` — Return any optional device name defined in platform configuratio.
- L526 _public prototype_ `static bool GetChannelTypeAtIndex(const int32 Index, EAudioMixerChannel::Type& OutType);` — Helper function to gets the channel map type at the given index.
- L529 _public function_ `virtual void SuspendContext()` — Function to stop all audio from rendering. Used on mobile platforms which can suspend the application.
- L532 _public function_ `virtual void ResumeContext()` — Function to resume audio rendering. Used on mobile platforms which can suspend the application.
- L535 _public function_ `virtual void OnHardwareUpdate()` — Function called at the beginning of every call of UpdateHardware on the audio thread.
- L538 _public function_ `virtual IAudioPlatformDeviceInfoCache* GetDeviceInfoCache() const` — Get the DeviceInfo Cache if one exists.
- L541 _public function_ `virtual bool IsDeviceInfoValid(const FAudioPlatformDeviceInfo& InDeviceInfo) const` — Determine if the given device info struct is valid for use with this platform
- L544 _public function_ `virtual bool ShouldUseDeviceInfoCache() const` — Subclasses can override to determine if it should use Cache for DeviceInfo Enumeration
- L548 _public prototype_ `uint32 Run() override;`
- L555 _public function_ `virtual class FSingleThreadRunnable* GetSingleThreadInterface() override` — FSingleThreadRunnable accessor for ticking this FRunnable when multi-threading is disabled. @return FSingleThreadRunnable Interface for this FRunnable object.
- L558 _public prototype_ `virtual void Tick() override;`
- L562 _public prototype_ `IAudioMixerPlatformInterface();` — Constructor.
- L565 _public prototype_ `void ReadNextBuffer();` — Retrieves the next generated buffer and feeds it to the platform mixer output stream.
- L568 _public prototype_ `virtual void FadeIn();` — Reset the fade state (use if reusing audio platform interface, e.g. in main audio device.
- L571 _public prototype_ `virtual void FadeOut();` — Start a fadeout. Prevents pops during shutdown.
- L574 _public function_ `FString GetLastError() const` — Returns the last error generated.
- L577 _public prototype_ `void PostInitializeHardware();` — This is called after InitializeHardware() is called.
- L580 _public function_ `bool GetIsListeningForDeviceEvents() const` — Used to determine if this object is listening to system device change events.
- L581 _public function_ `void SetIsListeningForDeviceEvents(bool bInListeningForDeviceEvents)`
- L586 _protected prototype_ `uint32 MainAudioDeviceRun();` — Run the "main" audio device
- L589 _protected prototype_ `virtual uint32 RunInternal();` — Wrapper around the thread Run. This is virtualized so a platform can fundamentally override the render function.
- L592 _protected function_ `inline void AudioMixerPlatformLogOnce(const FString& LogDetails, const FString& FileName, int32 LineNumber, ELogVerbosity::Type InVerbosity = ELogVerbosity::Error)` — Is called when an error, warning or log is generated.
- L657 _protected prototype_ `void BeginGeneratingAudio();` — Start generating audio from our mixer.
- L660 _protected prototype_ `void StopGeneratingAudio();` — Stops the render thread from generating audio.
- L664 _protected prototype_ `void SignalStopGeneratingAudio();` — Non-blocking: signals the render thread to stop (sets Stopping state, triggers event) without waiting for the thread to exit. Use TryFinishStopGeneratingAudio() to complete cleanup.
- L669 _protected prototype_ `bool TryFinishStopGeneratingAudio();` — Checks if the render thread has stopped after SignalStopGeneratingAudio() was called. If the thread has stopped (or a timeout is reached), cleans up thread/events and returns true. If the thread is still running, returns false.
- L673 _protected prototype_ `void ApplyMasterAttenuation(TArrayView<const uint8>& InOutPoppedAudio);` — `UE_DEPRECATED(5.1, "ApplyMasterAttenuation is deprecated, please use ApplyPrimaryAttenuation instead.")` — Deprecated - use ApplyPrimaryAttenuation
- L676 _protected prototype_ `void ApplyPrimaryAttenuation(TArrayView<const uint8>& InOutPoppedAudio);` — Performs buffer fades for shutdown/startup of audio mixer.
- L679 _protected prototype_ `template<typename BufferType> void ApplyAttenuationInternal(TArrayView<BufferType>& InOutBuffer);`
- L682 _protected prototype_ `void StartRunningNullDevice();` — When called, spins up a thread to start consuming output when no audio device is available.
- L685 _protected prototype_ `void StopRunningNullDevice();` — When called, terminates the null device.
- L688 _protected prototype_ `void CreateNullDeviceThread(const TFunction<void()> InCallback, float InBufferDuration, bool bShouldPauseOnStart);` — Called by platform specific logic to pre-create or create the null renderer thread
- L693 _protected member_ `FAudioOutputStreamInfo AudioStreamInfo;` — The audio device stream info.
- L694 _protected member_ `FAudioMixerOpenStreamParams OpenStreamParams;`
- L697 _protected member_ `Audio::FOutputBuffer OutputBuffer;` — List of generated output buffers.
- L700 _protected member_ `bool bWarnedBufferUnderrun;` — Whether or not we warned of buffer underrun.
- L701 _protected member_ `int32 UnderrunCount = 0;`
- L702 _protected member_ `int32 CurrentUnderrunCount = 0;`
- L703 _protected member_ `uint64 TimeLastWarningCycles = 0;`
- L707 _protected member_ `TUniquePtr<FRunnableThread> AudioRenderThread;` — FRunnableThread* AudioRenderThread;
- L710 _protected member_ `FEvent* AudioRenderEvent;` — The render thread sync event.
- L713 _protected member_ `FCriticalSection DeviceSwapCriticalSection;` — Critical Section used for times when we need the render loop to halt for the device swap.
- L717 _protected member_ `FThreadSafeBool bIsInDeviceSwap;` — `UE_DEPRECATED(5.6, "bIsInDeviceSwap has been deprecated. AudioStreamInfo.StreamState can provide similar functionality.")` — This is used if we are attempting to TryLock on DeviceSwapCriticalSection, but a buffer callback is being called in the current thread.
- L720 _protected member_ `FEvent* AudioFadeEvent;` — Event allows you to block until fadeout is complete.
- L723 _protected member_ `int32 NumOutputBuffers;` — The number of mixer buffers to queue on the output source voice.
- L726 _protected member_ `float FadeVolume;` — The fade value. Used for fading in/out primary audio.
- L729 _protected member_ `FParam FadeParam;` — Source param used to fade in and out audio device.
- L732 _protected member_ `FString CurrentDeviceName;` — This device name can be used to override the default device being used on platforms that use strings to identify audio devices.
- L735 _protected member_ `FString LastError;` — String containing the last generated error.
- L737 _protected member_ `int32 CallCounterApplyAttenuationInternal{ 0 };`
- L738 _protected member_ `int32 CallCounterReadNextBuffer{ 0 };`
- L740 _protected member_ `FThreadSafeBool bPerformingFade;`
- L741 _protected member_ `FThreadSafeBool bFadedOut;`
- L742 _protected member_ `FThreadSafeBool bIsDeviceInitialized;`
- L745 _protected member_ `FThreadSafeBool bMoveAudioStreamToNewAudioDevice;` — `UE_DEPRECATED(5.6, "bMoveAudioStreamToNewAudioDevice has been deprecated. AudioStreamInfo.StreamState can provide similar functionality.")`
- L747 _protected member_ `FThreadSafeBool bIsUsingNullDevice;`
- L748 _protected member_ `FThreadSafeBool bIsGeneratingAudio;`
- L751 _protected member_ `double StopGeneratingAudioSignalTime = 0.0;` — Timestamp (seconds) when SignalStopGeneratingAudio was called, for timeout detection.
- L754 _protected member_ `static FThreadSafeCounter NextInstanceID;` — A Counter to provide the next unique id.
- L757 _protected member_ `const int32 InstanceID{ -1 };` — A Unique ID Identifying this instance. Mostly used for logging.
- L760 _private member_ `TUniquePtr<FMixerNullCallback> NullDeviceCallback;`
- L763 _private member_ `bool bIsListeningForDeviceEvents = true;` — Used to determine if this object is listening to system device change events.

#### class `Audio::FAudioMixerPlatformSwappable`  
`class FAudioMixerPlatformSwappable : public IAudioMixerPlatformInterface`  
_L768-839_
- inherits: `IAudioMixerPlatformInterface`
- desc: Audio mixer platform objects can subclass this in order to add device swap capabilities.
- L771 _public prototype_ `FAudioMixerPlatformSwappable();`
- L772 _public prototype_ `virtual ~FAudioMixerPlatformSwappable() override = default;`
- L775 _public prototype_ `virtual bool RequestDeviceSwap(const FString& DeviceID, const bool bInForce, const TCHAR* InReason) override;`
- L776 _public function_ `virtual void LockDeviceSwap() override`
- L777 _public function_ `virtual void UnlockDeviceSwap() override`
- L778 _public prototype_ `virtual bool CheckAudioDeviceChange() override;`
- L779 _public prototype_ `virtual bool MoveAudioStreamToNewAudioDevice() override;`
- L780 _public prototype_ `virtual void ResumePlaybackOnNewDevice() override;`
- L784 _public prototype_ `virtual bool AllowDeviceSwap(const bool bInForceSwap);` — Called to determine if the current device swap request should be allowed to proceed.
- L787 _public prototype_ `virtual bool InitializeDeviceSwapContext(const FString& InRequestedDeviceID, const TCHAR* InReason) = 0;` — Initializes a new device swap context with the given parameters
- L790 _public prototype_ `virtual bool CheckThreadedDeviceSwap();` — Called repeatedly to update an active, async device swap
- L793 _public function_ `virtual bool PreDeviceSwap()` — Called at the beginning of a device swap to perform any needed initialization
- L796 _public prototype_ `virtual void EnqueueAsyncDeviceSwap() = 0;` — Kicks of an async device swap task
- L799 _public prototype_ `virtual void SynchronousDeviceSwap() = 0;` — Performs a device swap synchronously in the current thread
- L802 _public function_ `virtual bool PostDeviceSwap()` — Called after a device swap completes, providing an opportunity for any needed cleanup
- L806 _protected function_ `FString GetOriginalAudioDeviceId() const` — Used in OnDeviceAdded for determining if an added device is the same as the original device.
- L807 _protected function_ `void SetOriginalAudioDeviceId(const FString& InAudioDeviceId)`
- L810 _protected function_ `void SetActiveDeviceSwapFuture(TFuture<TUniquePtr<FDeviceSwapResult>>&& InFuture)` — Future which holds result of device swap upon completion.
- L811 _protected function_ `void ResetActiveDeviceSwapFuture()`
- L816 _protected function_ `const FDeviceSwapResult* GetDeviceSwapResult() const` — The results produced from a device swap operation. The containing future retains memory ownership. Will be valid until PostDeviceSwap returns.
- L817 _protected function_ `FDeviceSwapResult* GetDeviceSwapResult()`
- L821 _private member_ `FString OriginalAudioDeviceId;` — Used in OnDeviceAdded for determining if an added device is the same as the original device.
- L824 _private member_ `TFuture<TUniquePtr<FDeviceSwapResult>> ActiveDeviceSwap;` — Future which holds result of device swap upon completion.
- L827 _private member_ `double LastDeviceSwapTime = 0.0;` — Used to rate limit device swap attempts to ignore multiple requests
- L831 _private member_ `bool bWaitingForRenderThreadStop = false;` — True when we've signaled the render thread to stop but haven't finished cleanup yet. Only read/written on the audio thread (inside CheckThreadedDeviceSwap).
- L837 _private member_ `TOptional<FString> DeferredDeviceSwapId;` — If a force device swap is requested while bWaitingForRenderThreadStop is true, the request is deferred here so it can be replayed after the current swap completes. Empty string means no deferred swap; non-empty or explicit default ("") is stored as a TOptional to distinguish "no request" from "request for default device".
- L838 _private member_ `FString DeferredDeviceSwapReason;`

#### class `Audio::FScopedDeviceSwapLock`  
`class FScopedDeviceSwapLock final`  
_L841-864_
- L844 _public prototype_ `FScopedDeviceSwapLock() = delete;`
- L845 _public function_ `explicit FScopedDeviceSwapLock(IAudioMixerPlatformInterface* InPlatform) : AudioMixerPlatform(InPlatform)`
- L854 _public function_ `~FScopedDeviceSwapLock()`
- L863 _private member_ `IAudioMixerPlatformInterface* AudioMixerPlatform = nullptr;`

#### class `IAudioDeviceModule`  
`class IAudioDeviceModule : public IModuleInterface`  
_L874-884_
- inherits: `IModuleInterface`
- desc: Defines the interface of a module implementing an audio device and associated classes.
- L879 _public function_ `virtual bool IsAudioMixerModule() const` — Creates a new instance of the audio device implemented by the module.
- L881 _public function_ `virtual bool IsAudioDeviceClassMulticlient() const` — Does this class of device support multiclient access to the driver
- L882 _public function_ `virtual FAudioDevice* CreateAudioDevice()`
- L883 _public function_ `virtual Audio::IAudioMixerPlatformInterface* CreateAudioMixerPlatformInterface()`

#### Free symbols / members of external scopes

- L37 _macro_ `#define UE_API AUDIOMIXERCORE_API`
- L42 _namespace_ `namespace Audio`
- L45 _macro_ `#define AUDIO_PLATFORM_LOG_ONCE(INFO, VERBOSITY) (AudioMixerPlatformLogOnce(INFO, FString(__FILE__), __LINE__, ELogVerbosity::VERBOSITY))` — defines used for AudioMixer.h
- L46 _macro_ `#define AUDIO_PLATFORM_ERROR(INFO) (AudioMixerPlatformLogOnce(INFO, FString(__FILE__), __LINE__, ELogVerbosity::Error))`
- L51 _macro_ `#define AUDIO_MIXER_ENABLE_DEBUG_MODE 0`
- L53 _macro_ `#define AUDIO_MIXER_ENABLE_DEBUG_MODE 1`
- L61 _macro_ `#define AUDIO_MIXER_CHECK(expr) ensure(expr)`
- L62 _macro_ `#define AUDIO_MIXER_CHECK_GAME_THREAD(_MixerDevice) (_MixerDevice->CheckAudioThread())`
- L63 _macro_ `#define AUDIO_MIXER_CHECK_AUDIO_PLAT_THREAD(_MixerDevice) (_MixerDevice->CheckAudioRenderingThread())`
- L65 _macro_ `#define AUDIO_MIXER_CHECK(expr)`
- L66 _macro_ `#define AUDIO_MIXER_CHECK_GAME_THREAD(_MixerDevice)`
- L67 _macro_ `#define AUDIO_MIXER_CHECK_AUDIO_PLAT_THREAD(_MixerDevice)`
- L70 _macro_ `#define AUDIO_MIXER_MAX_OUTPUT_CHANNELS 8 // Max number of speakers/channels supported (7.1)`
- L72 _macro_ `#define AUDIO_MIXER_DEFAULT_DEVICE_INDEX INDEX_NONE`
- L75 _delegate_ `DECLARE_STATS_GROUP(TEXT("AudioMixer"), STATGROUP_AudioMixer, STATCAT_` — Cycle stats for audio mixer
- L78 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Render Audio"), STAT_AudioMixerRenderAudio, STATGROUP_AudioMixer, AUDIOMIX` — Tracks the time for the full render block
- L86 _typedef_ `using FSoundWaveProxyPtr = TSharedPtr<FSoundWaveProxy, ESPMode::ThreadSafe>;`
- L87 _typedef_ `using FSoundWavePtr = TSharedPtr<FSoundWaveData, ESPMode::ThreadSafe>;`
- L90 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixerCore/Public/AudioMixerChannel.h` (Public)


#### enum `EAudioMixerChannel::Type`  
`enum Type`  
_L12-35_
- desc: Enumeration values represent sound file or speaker channel types.
- L14 _public enumerator_ `FrontLeft`
- L15 _public enumerator_ `FrontRight`
- L16 _public enumerator_ `FrontCenter`
- L17 _public enumerator_ `LowFrequency`
- L18 _public enumerator_ `BackLeft`
- L19 _public enumerator_ `BackRight`
- L20 _public enumerator_ `FrontLeftOfCenter`
- L21 _public enumerator_ `FrontRightOfCenter`
- L22 _public enumerator_ `BackCenter`
- L23 _public enumerator_ `SideLeft`
- L24 _public enumerator_ `SideRight`
- L25 _public enumerator_ `TopCenter`
- L26 _public enumerator_ `TopFrontLeft`
- L27 _public enumerator_ `TopFrontCenter`
- L28 _public enumerator_ `TopFrontRight`
- L29 _public enumerator_ `TopBackLeft`
- L30 _public enumerator_ `TopBackCenter`
- L31 _public enumerator_ `TopBackRight`
- L32 _public enumerator_ `Unknown`
- L33 _public enumerator_ `ChannelTypeCount`
- L34 _public enumerator_ `DefaultChannel = FrontLeft`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace EAudioMixerChannel`
- L39 _macro_ `#define FOREACH_EAUDIOMIXERCHANNEL(OP)\` — Foreach for each speaker (minus ChannelTypeCount and Default). Not reflected enum, so do this by hand.
- L60 _variable_ `inline constexpr int32 MaxSupportedChannel = TopCenter;` (scope `EAudioMixerChannel`)
- L62 _function_ `constexpr const TCHAR* ToString(const Type InType)` (scope `EAudioMixerChannel`)
- L65 _macro_ `#define CASE_TO_STRING(X) case X: return TEXT(#X);` — Define using FOREACH macro
- L75 _function_ `inline FName ToName(const Type InType)` (scope `EAudioMixerChannel`)
- L78 _macro_ `#define CASE_TO_NAME(X) case X:\` — Keep these static.
- L95 _function_ `inline TOptional<Type> FromName(const FName InType)` (scope `EAudioMixerChannel`)
- L98 _macro_ `#define COMPARE_RETURN_NAME(X) if (InType == ToName(X)) return X;` — Define using FOREACH macro.

### `Source/Runtime/AudioMixerCore/Public/AudioMixerCoreModule.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/AudioMixerCore/Public/AudioMixerLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioMixer, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioMixerDebug, Warning, All);`

### `Source/Runtime/AudioMixerCore/Public/AudioMixerNullDevice.h` (Public)


#### class `Audio::FMixerNullCallback`  
`class FMixerNullCallback : protected FRunnable`  
_L24-67_
- inherits: `FRunnable`
- desc: FMixerNullCallback This class, when started, spawns a new high priority thread that exists to query an FAudioMixerPlatformInterface and immediately throw out whatever buffers it receives.
- L32 _public prototype_ `FMixerNullCallback(float BufferDuration, TFunction<void()> InCallback, EThreadPriority ThreadPriority = TPri_TimeCritical, bool bStartedPaused = false);` — Constructing the FMixerNullCallback immediately begins calling InCallback every BufferDuration seconds.
- L37 _public prototype_ `virtual ~FMixerNullCallback() = default;` — The destructor waits on Callback to be completed before stopping the thread.
- L40 _public prototype_ `virtual uint32 Run() override;` — FRunnable override:
- L41 _public prototype_ `virtual void Stop() override;`
- L44 _public prototype_ `void Resume(const TFunction<void()>& InCallback, float InBufferDuration);` — Resume a paused null renderer.
- L47 _public prototype_ `void Pause();` — Pause the thread, making it sleep until woken, not consuming cycles or buffers.
- L52 _private prototype_ `FMixerNullCallback() = delete;` — Default constructor intentionally suppressed:
- L55 _private member_ `TFunction<void()> Callback;` — Callback used.
- L58 _private member_ `float CallbackTime;` — Used to determine amount of time we should wait between callbacks.
- L61 _private member_ `std::atomic<bool> bShouldShutdown;` — Flagged on Stop
- L62 _private member_ `std::atomic<bool> bShouldRecyle;`
- L63 _private member_ `FEvent* SleepEvent = nullptr;`
- L64 _private member_ `FEvent* WakeupEvent = nullptr;`
- L65 _private member_ `TUniquePtr<FRunnableThread> CallbackThread;`
- L66 _private member_ `double LastLog = 0.f;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Audio`

### `Source/Runtime/AudioMixerCore/Public/AudioMixerTrace.h` (Public)


#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_AUDIO_PROFILERTRACE_ENABLED UE_TRACE_ENABLED && !UE_BUILD_SHIPPING`
- L15 _macro_ `#define AUDIO_MIXER_TRACE_CPUPROFILER_EVENT_SCOPE(Name) TRACE_CPUPROFILER_EVENT_SCOPE(Name)`
- L16 _prototype_ `UE_TRACE_CHANNEL_EXTERN(AudioChannel);`
- L17 _prototype_ `UE_TRACE_CHANNEL_EXTERN(AudioMixerChannel);`
- L22 _macro_ `#define AUDIO_MIXER_TRACE_CPUPROFILER_EVENT_SCOPE(Name)`
- L29 _namespace_ `namespace Audio`
- L29 _namespace_ `namespace Trace` (scope `Audio`)
- L29 _namespace_ `namespace EventLog` (scope `Audio::Trace`)
- L29 _namespace_ `namespace ID` (scope `Audio::Trace::EventLog`)
- L32 _externvar_ `extern const FString SoundStart;` (scope `Audio::Trace::EventLog::ID`) — Active Sound : Playing Audio
- L33 _externvar_ `extern const FString SoundStop;` (scope `Audio::Trace::EventLog::ID`)
- L36 _externvar_ `extern const FString SoundVirtualized;` (scope `Audio::Trace::EventLog::ID`) — Virtualization
- L37 _externvar_ `extern const FString SoundRealized;` (scope `Audio::Trace::EventLog::ID`)
- L40 _externvar_ `extern const FString PlayRequestSoundHandle;` (scope `Audio::Trace::EventLog::ID`) — Triggers
- L41 _externvar_ `extern const FString StopRequestedSoundHandle;` (scope `Audio::Trace::EventLog::ID`)
- L43 _externvar_ `extern const FString PlayRequestAudioComponent;` (scope `Audio::Trace::EventLog::ID`)
- L44 _externvar_ `extern const FString StopRequestAudioComponent;` (scope `Audio::Trace::EventLog::ID`)
- L46 _externvar_ `extern const FString PlayRequestOneShot;` (scope `Audio::Trace::EventLog::ID`)
- L47 _externvar_ `extern const FString PlayRequestSoundAtLocation;` (scope `Audio::Trace::EventLog::ID`)
- L48 _externvar_ `extern const FString PlayRequestSound2D;` (scope `Audio::Trace::EventLog::ID`)
- L49 _externvar_ `extern const FString PlayRequestSlateSound;` (scope `Audio::Trace::EventLog::ID`)
- L52 _externvar_ `extern const FString PlayFailedNotPlayable;` (scope `Audio::Trace::EventLog::ID`) — Active Sound : Playing Audio Failures
- L53 _externvar_ `extern const FString PlayFailedOutOfRange;` (scope `Audio::Trace::EventLog::ID`)
- L54 _externvar_ `extern const FString PlayFailedDebugFiltered;` (scope `Audio::Trace::EventLog::ID`)
- L55 _externvar_ `extern const FString PlayFailedConcurrency;` (scope `Audio::Trace::EventLog::ID`)
- L57 _externvar_ `extern const FString StopRequestActiveSound;` (scope `Audio::Trace::EventLog::ID`)
- L58 _externvar_ `extern const FString StopRequestSoundsUsingResource;` (scope `Audio::Trace::EventLog::ID`)
- L59 _externvar_ `extern const FString StopRequestConcurrency;` (scope `Audio::Trace::EventLog::ID`)
- L61 _externvar_ `extern const FString PauseSoundRequested;` (scope `Audio::Trace::EventLog::ID`)
- L62 _externvar_ `extern const FString ResumeSoundRequested;` (scope `Audio::Trace::EventLog::ID`)
- L64 _externvar_ `extern const FString StopAllRequested;` (scope `Audio::Trace::EventLog::ID`)
- L65 _externvar_ `extern const FString FlushAudioDeviceRequested;` (scope `Audio::Trace::EventLog::ID`)
- L68 _externvar_ `extern const FString PIEStarted;` (scope `Audio::Trace::EventLog::ID`) — PIE Session
- L69 _externvar_ `extern const FString PIEStopped;` (scope `Audio::Trace::EventLog::ID`)

### `Source/Runtime/AudioMixerCore/Public/AudioMixerTypes.h` (Public)


#### enum `Audio::EAudioMixerStreamDataFormat::Type`  
`enum Type`  
_L10-16_
- L12 _public enumerator_ `Unknown`
- L13 _public enumerator_ `Float`
- L14 _public enumerator_ `Int16`
- L15 _public enumerator_ `Unsupported`

#### enum `Audio::EAudioOutputStreamState::Type`  
`enum Type`  
_L25-44_
- L28 _public enumerator_ `Closed` — The audio stream is shutdown or not uninitialized.
- L31 _public enumerator_ `Open` — The audio stream is open but not running.
- L34 _public enumerator_ `Stopped` — The audio stream is open but stopped.
- L37 _public enumerator_ `Stopping` — The audio output stream is stopping.
- L40 _public enumerator_ `Running` — The audio output stream is open and running.
- L43 _public enumerator_ `SwappingDevice` — The audio device hardware is being swapped

#### struct `FAudioPlatformSettings`  
`struct FAudioPlatformSettings`  
_L62-89_
- L65 _public member_ `int32 SampleRate;` — Sample rate to use on the platform for the mixing engine. Higher sample rates will incur more CPU cost.
- L68 _public member_ `int32 CallbackBufferFrameSize;` — The amount of audio to compute each callback block. Lower values decrease latency but may increase CPU cost.
- L71 _public member_ `int32 NumBuffers;` — The number of buffers to keep enqueued. More buffers increases latency, but can compensate for variable compute availability in audio callbacks on some platforms.
- L74 _public member_ `int32 MaxChannels;` — The max number of channels (simultaneous voices) to use as the limit for this platform. If given a value of 0, it will use the value from the active Global Audio Quality Settings
- L77 _public member_ `int32 NumSourceWorkers;` — The number of workers to use to compute source audio. Will only use up to the max number of sources. Will evenly divide sources to each source worker.
- L79 _public prototype_ `static FAudioPlatformSettings GetPlatformSettings(const TCHAR* PlatformSettingsConfigFile);`
- L81 _public function_ `FAudioPlatformSettings() : SampleRate(48000) , CallbackBufferFrameSize(1024) , NumBuffers(2) , MaxChannels(0)`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Audio`
- L8 _namespace_ `namespace EAudioMixerStreamDataFormat` (scope `Audio`)
- L23 _namespace_ `namespace EAudioOutputStreamState` (scope `Audio`)
- L48 _variable_ `inline FName NAME_PLATFORM_SPECIFIC("PLA` (scope `Audio`) — Indicates a platform-specific format
- L49 _variable_ `inline FName NAME_PROJECT_DEFINED("PRO` (scope `Audio`)
- L52 _variable_ `inline FName NAME_BINKA("BIN` (scope `Audio`) — Supported on all platforms:
- L53 _variable_ `inline FName NAME_ADPCM("ADP` (scope `Audio`)
- L54 _variable_ `inline FName NAME_PCM("PCM` (scope `Audio`)
- L55 _variable_ `inline FName NAME_OPUS("OPU` (scope `Audio`)
- L56 _variable_ `inline FName NAME_RADA("RAD` (scope `Audio`)
- L59 _variable_ `inline FName NAME_OGG("OGG` (scope `Audio`) — Not yet supported on all platforms as a selectable option so is included under "platform specific" enumeration for now.
