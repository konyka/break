# Runtime / AudioLinkEngine

- module root: `Source/Runtime/AudioLink/AudioLinkEngine`
- headers: 9; symbols: 227
- symbol kinds: class=13, delegate=9, function=21, member=68, prototype=99, struct=13, typedef=4
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, SignalProcessing

### `Source/Runtime/AudioLink/AudioLinkEngine/Public/AudioLinkLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioLink, Log, All);`

### `Source/Runtime/AudioLink/AudioLinkEngine/Public/BufferedListenerBase.h` (Public)


#### class `FLockingCircularSampleBuffer`  
`class FLockingCircularSampleBuffer`  
_L15-140_
- desc: Simple locking circular buffer Uses 32bit wrap around logic explained here: https://www.snellman.net/blog/archive/2016-12-13-ring-buffers/
- L18 _public function_ `FLockingCircularSampleBuffer(int32 InInitialCapacity)`
- L24 _public function_ `FCriticalSection& GetCriticialSection()` — Allow the caller to lock the CS ahead of calling (if necessary)
- L25 _public function_ `const FCriticalSection& GetCriticialSection() const`
- L28 _public function_ `void SetCapacity(int32 InCapacity)` — This doesn't preserve contents.
- L45 _public function_ `int32 GetCapacity() const`
- L50 _public function_ `int32 Num() const`
- L57 _public function_ `int32 Remainder() const` — Get number of samples that can be pushed onto the buffer before it is full.
- L63 _public function_ `int32 Push(const float* InBuffer, int32 InSize)`
- L73 _public function_ `int32 Pop(float* OutBuffer, int32 InNumSamples)`
- L84 _public function_ `int32 PushZeros(int32 InNumSamplesOfSilence)`
- L96 _public function_ `void Flush()` — Reset read/write pointers, discarding all buffered data without reallocating.
- L105 _public function_ `void EnsureCapacity(int32 InMinCapacity)` — Grow the buffer to at least InMinCapacity if current capacity is insufficient. Never shrinks. Flushes read/write pointers (does not preserve contents).
- L125 _private member_ `uint32 Read = 0;` — These grow indefinitely until wrap at 2^32,
- L126 _private member_ `uint32 Read = 0;` — this allows us to use full capacity as write >= read.
- L127 _private member_ `uint32 Mask = 0;`
- L128 _private member_ `TArray<float> Buffer;`
- L129 _private member_ `mutable FCriticalSection CS;`
- L132 _private function_ `void Enqueue(const float InFloat)` — NOTE: Not forceinline as compiler does better job without.
- L136 _private function_ `float Dequeue()`

#### class `FBufferedListenerBase`  
`class FBufferedListenerBase : public IBufferedAudioOutput`  
_L144-207_
- inherits: `IBufferedAudioOutput`
- desc: Common base class of Buffered Listener objects.
- L147 _protected prototype_ `FBufferedListenerBase(int32 InDefaultCircularBufferSize);`
- L148 _protected prototype_ `virtual ~FBufferedListenerBase() = default;`
- L151 _protected prototype_ `bool PopBuffer(float* InBuffer, int32 InBufferSizeInSamples, int32& OutSamplesWritten) override;`
- L152 _protected prototype_ `bool GetFormat(IBufferedAudioOutput::FBufferFormat& OutFormat) const override;`
- L153 _protected prototype_ `void Reserve(int32 InNumSamplesToReserve, int32 InNumSamplesOfSilence) override;`
- L154 _protected prototype_ `void SetFormatKnownDelegate(FOnFormatKnown InFormatKnownDelegate) override;`
- L155 _protected function_ `void SetBufferStreamEndDelegate(FOnBufferStreamEnd) override`
- L159 _protected prototype_ `void OnBufferReceived(const FBufferFormat& InFormat, TArrayView<const float> InBuffer);` — /  Common path to receive a new buffer, call from derived classes
- L162 _protected prototype_ `void ResetFormat();` — /  Reset the format of the buffer
- L165 _protected prototype_ `void SetFormat(const FBufferFormat& InFormat);` — /  Set the format of the buffer
- L168 _protected prototype_ `bool IsStartedNonAtomic() const;` — /  Ask if the started flag has been set. Note this is non-atomic, as it could change during the call
- L171 _protected prototype_ `bool TrySetStartedFlag();` — /  Attempt to set our state to started. Not this can fail if we're already started.
- L174 _protected prototype_ `bool TryUnsetStartedFlag();` — /  Attempt to set started to false. This can fail if we're already stopped.
- L176 _protected prototype_ `bool TrySetStoppingFlag();`
- L179 _protected prototype_ `int32 GetNumBufferedSamples();` — /  Return the number of samples able to be popped off the queue
- L182 _protected prototype_ `void FlushAndResetFormat();` — /  Flush the circular buffer and reset the known format so OnFormatKnown re-fires on the next buffer
- L185 _protected prototype_ `void FlushAndEnsureCapacity(int32 InMinCapacity);` — /  Flush the circular buffer, grow capacity if needed (never shrinks), and reset format
- L188 _private prototype_ `void PushSilence(int32 InNumSamplesOfSilence);`
- L191 _private member_ `FLockingCircularSampleBuffer CircularBuffer;` — Buffer to hold the data for the single source we're listening to, interleaved.
- L194 _private member_ `mutable FRWLock FormatKnownRwLock;` — Read/Write slim lock protects format known optional
- L197 _private member_ `TOptional<FBufferFormat> KnownFormat;` — Optional that holds the buffer format, if (and when) it's known. Protected by r/w Slim-lock
- L200 _private member_ `FOnFormatKnown OnFormatKnown;` — Delegate that fires when the format it known. Normally on the first buffer received.
- L203 _private member_ `std::atomic<bool> bStarted{ false };` — Atomic flag we've been started
- L206 _private member_ `std::atomic<bool> bStopping{ false };` — Atomic flag we've been told to stop

### `Source/Runtime/AudioLink/AudioLinkEngine/Public/BufferedSourceListener.h` (Public)


#### class `FBufferedSourceListener`  
`class FBufferedSourceListener : public ISourceBufferListener, public FBufferedListenerBase`  
_L12-40_
- inherits: `ISourceBufferListener,FBufferedListenerBase`
- desc: FBufferedSourceListener: Concrete implementation of both a buffer listener and buffered output. Contains a circular buffer.
- L15 _public prototype_ `FBufferedSourceListener(int32 InDefaultCircularBufferSize);`
- L16 _public prototype_ `virtual ~FBufferedSourceListener();`
- L23 _public prototype_ `bool Start(FAudioDevice* InDevice) override;` — @param  InDevice Audio Device to register this listener with. @return  success true, false otherwise.
- L26 _public prototype_ `void Stop(FAudioDevice* InDevice) override;` — Stop the buffer by unregistering the buffer listener
- L30 _private prototype_ `void OnNewBuffer(const ISourceBufferListener::FOnNewBufferParams& InParams) override;`
- L31 _private prototype_ `void OnSourceReleased(const int32 SourceId) override;`
- L35 _private prototype_ `void SetBufferStreamEndDelegate(FOnBufferStreamEnd InBufferStreamEndDelegate) override;`
- L38 _private member_ `std::atomic<int32> CurrentSourceId = INDEX_NONE;` — r/w AudioMixer thread.
- L39 _private member_ `FOnBufferStreamEnd OnBufferStreamEndDelegate;`

### `Source/Runtime/AudioLink/AudioLinkEngine/Public/BufferedSubmixListener.h` (Public)


#### class `FBufferedSubmixListener`  
`class FBufferedSubmixListener : public ISubmixBufferListener, public FBufferedListenerBase`  
_L11-48_
- inherits: `ISubmixBufferListener,FBufferedListenerBase`
- desc: Concrete Submix Buffer Listener
- L19 _public prototype_ `FBufferedSubmixListener(int32 InDefaultCircularBufferSize, bool bInZeroInputBuffer, const FString* InName);` — Constructor @param  InDefaultCircularBufferSize: Size of the circular buffer in samples by default. @param  bInZeroInputBuffer: If set, AudioData input buffer will be zeroed out after data is queued @param  InName(Optional): Optional name to track listener lifetime with.
- L21 _public prototype_ `virtual ~FBufferedSubmixListener();`
- L30 _public prototype_ `bool Start(FAudioDevice* InDevice, USoundSubmix* InSubmix);` — Starts the Submix buffer listener by registering it with the passed in Audio Device. @param  InDevice: Audio Device to register this submix listener with. @param  InSubmix: The submix being listened to (default is main output) @return  success true, false otherwise.
- L32 _public prototype_ `bool Start(FAudioDevice* InDevice) override;`
- L33 _public prototype_ `void Stop(FAudioDevice* InDevice) override;`
- L38 _protected prototype_ `void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 InNumSamples, int32 InNumChannels, const int32 InSampleRate, double) override;`
- L39 _protected prototype_ `const FString& GetListenerName() const override;`
- L42 _protected member_ `bool bZeroInputBuffer = false;`
- L44 _private member_ `Audio::FDeviceId DeviceId;`
- L45 _private member_ `FString Name;`
- L47 _private member_ `TWeakObjectPtr<USoundSubmix> Submix;`

### `Source/Runtime/AudioLink/AudioLinkEngine/Public/DownmixedBufferedSubmixListener.h` (Public)


#### class `FDownmixedBufferedSubmixListener`  
`class FDownmixedBufferedSubmixListener : public FBufferedSubmixListener`  
_L13-86_
- inherits: `FBufferedSubmixListener`
- L21 _public prototype_ `FDownmixedBufferedSubmixListener(int32 InNumOutputChannels, int32 InSampleRate, const FString* InName);` — Constructor @param  InNumOutputChannels: channel config for output @param  InSampleRate: Desired sample rate @param  InName(Optional): Optional name to track listener lifetime with.
- L23 _public function_ `virtual ~FDownmixedBufferedSubmixListener()`
- L26 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnSubmixBufferWritten, const float* , int32 , int32 );` — Delegate to signal to the consumer that data is ready
- L27 _public member_ `FOnSubmixBufferWritten OnSubmixBufferWritten;`
- L32 _public prototype_ `int32 GetNumAvailableSamples();` — Query the number of samples waiting in the queue @return total number of samples, e.g. for 480 frames of 2 channels, would return 960
- L41 _public prototype_ `bool GetBuffer(float* InBuffer, int32 InBufferSizeInSamples, int32& OutSamplesWritten);` — Retrieve samples from the queue @param  InBuffer: memory provided by the caller to copy samples into @param  InBufferSizeInSamples: total number of samples to be retrieved, frame count * channel count @param  OutSamplesWritten: total number of samples written into the provided buffer @return if the queue is still active, it will return true, otherwise, return indicates if there are more samples in the queue
- L48 _public prototype_ `void EnableZeroInputBuffer(bool bInZeroInputBuffer);` — If set to true, AudioData input buffer will be zeroed out after data is queued. NOTE: Only set this to true if you can be sure that this is the only listener registered on this Submix. As such, listeners after this will have a silent buffer and the Submix may be considered disabled if bAutoDisable is on for that Submix. Use with caution. @param  bInZeroInputBuffer: bool value to set bZeroInputBuffer to
- L53 _public prototype_ `void EnableSkipSilentBuffers(bool bInSkipSilentBuffers);` — If set to true, only buffers that contain at least one non-silent sample will be written to the circular buffer. @param  bInSkipSilentBuffers: bool value to set bSkipSilentBuffers to
- L65 _public prototype_ `void SetOutputFormat(int32 InNumOutputChannels, int32 InSampleRate);` — Change the output format of the listener. Safe to call from any thread. Flushes the circular buffer immediately so that subsequent PopBuffer() calls will not return stale data in the old format. The audio render thread will pick up the new format on the next OnNewSubmixBuffer() callback and rebuild internal DSP state accordingly. Callers should expect up to one buffer period of silence after the transition. @param  InNumOutputChannels: New output channel count (max 8) @param  InSampleRate: New output sample rate
- L69 _private prototype_ `void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 InNumSamples, int32 InNumChannels, const int32 InSampleRate, double) override;`
- L72 _private member_ `int32 NumOutputChannels;`
- L73 _private member_ `int32 OutputSampleRate;`
- L74 _private member_ `bool bSkipSilentBuffers = false;`
- L77 _private member_ `std::atomic<int32> PendingOutputChannels{0};` — Pending output format change, set by SetOutputFormat(), consumed by OnNewSubmixBuffer()
- L78 _private member_ `std::atomic<int32> PendingOutputSampleRate{0};` — 0 = no pending change (gate variable)
- L80 _private member_ `TArray<float> ChannelGainMap;`
- L81 _private member_ `Audio::FAlignedFloatBuffer DownMixBuffer;`
- L82 _private member_ `Audio::FAlignedFloatBuffer RateConvertedBuffer;`
- L83 _private member_ `Audio::FRuntimeResampler Resampler;`
- L84 _private member_ `int32 NumInputChannels = 0;`
- L85 _private member_ `int32 InputSampleRate = 0;`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnSubmixBufferWritten, const float* , int32 , int32 );` — Delegate to signal to the consumer that data is ready

### `Source/Runtime/AudioLink/AudioLinkEngine/Public/IAudioLink.h` (Public)


#### class `IAudioLink`  
`class IAudioLink`  
_L13-19_
- desc: IAudioLink Abstract interface for AudioLink instances. Purely opaque.
- L16 _protected prototype_ `IAudioLink();`
- L18 _public prototype_ `virtual ~IAudioLink() = default;`

#### class `IAudioLinkSourcePushed`  
`class IAudioLinkSourcePushed : public IAudioLink`  
_L24-49_
- inherits: `IAudioLink`
- desc: IAudioLinkSourcePushed Where the owning object needs to push it's state
- L27 _protected prototype_ `IAudioLinkSourcePushed() = default;`
- L29 _public prototype_ `virtual ~IAudioLinkSourcePushed() = default;`
- L35 _public prototype_ `virtual void OnUpdateWorldState(const FOnUpdateWorldStateParams&) = 0;`
- L42 _public prototype_ `virtual void OnNewBuffer(const FOnNewBufferParams&) = 0;`
- L44 _public prototype_ `virtual void OnSourceDone(const int32 SourceId) = 0;`
- L46 _public prototype_ `virtual void OnSourceReleased(const int32 SourceId) = 0;`

#### struct `IAudioLinkSourcePushed::FOnUpdateWorldStateParams`  
`struct FOnUpdateWorldStateParams`  
_L31-34_
- L33 _public member_ `FTransform WorldTransform;`

#### struct `IAudioLinkSourcePushed::FOnNewBufferParams`  
`struct FOnNewBufferParams`  
_L37-41_
- L39 _public member_ `TArrayView<float> Buffer;`
- L40 _public member_ `int32 SourceId = INDEX_NONE;`

#### class `IAudioLinkSynchronizer`  
`class IAudioLinkSynchronizer`  
_L54-124_
- desc: IAudioLinkSynchronizer Provides delegates for hooking and external AudioLinks synchronization callbacks.
- L57 _protected prototype_ `IAudioLinkSynchronizer() = default;`
- L59 _public prototype_ `virtual ~IAudioLinkSynchronizer() = default;`
- L61 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSuspend);`
- L62 _public prototype_ `virtual FDelegateHandle RegisterSuspendDelegate(const FOnSuspend::FDelegate&) = 0;`
- L63 _public prototype_ `virtual bool RemoveSuspendDelegate(const FDelegateHandle&) = 0;`
- L65 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnResume);`
- L66 _public prototype_ `virtual FDelegateHandle RegisterResumeDelegate(const FOnResume::FDelegate&) = 0;`
- L67 _public prototype_ `virtual bool RemoveResumeDelegate(const FDelegateHandle&) = 0;`
- L97 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpenStream, const FOnOpenStreamParams&);`
- L98 _public prototype_ `virtual FDelegateHandle RegisterOpenStreamDelegate(const FOnOpenStream::FDelegate&) = 0;`
- L99 _public prototype_ `virtual bool RemoveOpenStreamDelegate(const FDelegateHandle&) = 0;`
- L101 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCloseStream);`
- L102 _public prototype_ `virtual FDelegateHandle RegisterCloseStreamDelegate(const FOnCloseStream::FDelegate&) = 0;`
- L103 _public prototype_ `virtual bool RemoveCloseStreamDelegate(const FDelegateHandle&) = 0;`
- L111 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginRender, const FOnRenderParams&);`
- L112 _public prototype_ `virtual FDelegateHandle RegisterBeginRenderDelegate(const FOnBeginRender::FDelegate&) = 0;`
- L113 _public prototype_ `virtual bool RemoveBeginRenderDelegate(const FDelegateHandle&) = 0;`
- L115 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndRender, const FOnRenderParams&);`
- L116 _public prototype_ `virtual FDelegateHandle RegisterEndRenderDelegate(const FOnEndRender::FDelegate&) = 0;`
- L117 _public prototype_ `virtual bool RemoveEndRenderDelegate(const FDelegateHandle&) = 0;`
- L123 _public function_ `virtual TOptional<FOnOpenStreamParams> GetCachedOpenStreamParams() const` — Gets any OpenStreamParams that were sent ahead of synchronizing existing. @return TOptional<FOpenStreamParams> (set if data is available).

#### struct `IAudioLinkSynchronizer::FOnOpenStreamParams`  
`struct FOnOpenStreamParams`  
_L69-95_
- L74 _public member_ `FString Name;` — Name of Implementation.
- L79 _public member_ `int32 NumFrames = INDEX_NONE;` — Number of frames per callback buffer. INDEX_NONE if not set.
- L84 _public member_ `int32 NumChannels = INDEX_NONE;` — Number of channels we're rendering at i.e. Stereo=2. INDEX_NONE if not set.
- L89 _public member_ `int32 SampleRate = INDEX_NONE;` — Sample rate of AL implementation. INDEX_NONE if not set.
- L94 _public member_ `int32 NumSources = INDEX_NONE;` — Num of Sources that AL is limited to. INDEX_NONE if not set.

#### struct `IAudioLinkSynchronizer::FOnRenderParams`  
`struct FOnRenderParams`  
_L105-109_
- L107 _public member_ `uint64 BufferTickID = 0;`
- L108 _public member_ `int32 NumFrames = INDEX_NONE;`

#### Free symbols / members of external scopes

- L61 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSuspend);`
- L65 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnResume);`
- L97 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpenStream, const FOnOpenStreamParams&);`
- L101 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCloseStream);`
- L111 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginRender, const FOnRenderParams&);`
- L115 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndRender, const FOnRenderParams&);`

### `Source/Runtime/AudioLink/AudioLinkEngine/Public/IAudioLinkBlueprintInterface.h` (Public)


#### class `UAudioLinkBlueprintInterface`  
`class UAudioLinkBlueprintInterface : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint), MinimalAPI)`
- inherits: `UInterface`

#### class `IAudioLinkBlueprintInterface`  
`class IAudioLinkBlueprintInterface : public IInterface`  
_L21-38_
- inherits: `IInterface`
- L27 _public prototype_ `virtual void SetLinkSound(USoundBase* NewSound) = 0;` — `UFUNCTION(BlueprintCallable, Category = "AudioLink")`
- L30 _public prototype_ `virtual void PlayLink(float StartTime = 0.0f) = 0;` — `UFUNCTION(BlueprintCallable, Category = "AudioLink")`
- L34 _public prototype_ `virtual void StopLink() = 0;` — `UFUNCTION(BlueprintCallable, Category = "AudioLink")` — Stop an audio component's sound, issue any delegates if needed
- L37 _public prototype_ `virtual bool IsLinkPlaying() const = 0;` — `UFUNCTION(BlueprintCallable, Category = "AudioLink")`

### `Source/Runtime/AudioLink/AudioLinkEngine/Public/IAudioLinkFactory.h` (Public)


#### class `IAudioLinkFactory`  
`class IAudioLinkFactory : public IModularFeature`  
_L20-148_
- inherits: `IModularFeature`
- desc: IAudioLinkFactory Abstract interface for AudioLink factory objects.
- L24 _protected prototype_ `IAudioLinkFactory();` — Constructor will auto register this instance.
- L27 _public prototype_ `virtual ~IAudioLinkFactory();` — Destructor will auto unregister this instance.
- L33 _public prototype_ `virtual FName GetFactoryName() const = 0;` — Gets the name of this factory type. This will uniquely identity itself, so it can be found by the FindFactory call below @return Name of factory
- L40 _public prototype_ `virtual TSubclassOf<UAudioLinkSettingsAbstract> GetSettingsClass() const = 0;` — Gets the type of of the settings object that this factory uses to define its specific settings. All settings for each AudioLink factory will derive from UAudioLinkSettingsAbstract @return Class of the Settings Object
- L49 _public prototype_ `virtual FSharedBufferedOutputPtr CreateSourceBufferListener(const FSourceBufferListenerCreateParams&);`
- L56 _public prototype_ `virtual FSharedBufferedOutputPtr CreatePushableBufferListener(const FPushedBufferListenerCreateParams&);`
- L63 _public prototype_ `virtual FSharedBufferedOutputPtr CreateSubmixBufferListener(const FSubmixBufferListenerCreateParams&);`
- L80 _public prototype_ `virtual TUniquePtr<IAudioLink> CreateSubmixAudioLink(const FAudioLinkSubmixCreateArgs& InCreateArgs) = 0;` — Create a Submix Audio Link. @param InCreateArgs Arguments used to create the AudioLink instance @return The newly created Link instance (if successful).
- L97 _public prototype_ `virtual TUniquePtr<IAudioLink> CreateSourceAudioLink(const FAudioLinkSourceCreateArgs&) = 0;` — Create a Source Audio Link. @param InCreateArgs Arguments used to create the AudioLink instance @return The newly created Link instance (if successful).
- L108 _public typedef_ `using FAudioLinkSourcePushedSharedPtr = TSharedPtr<IAudioLinkSourcePushed, ESPMode::ThreadSafe>;`
- L109 _public prototype_ `virtual FAudioLinkSourcePushedSharedPtr CreateSourcePushedAudioLink(const FAudioLinkSourcePushedCreateArgs&) = 0;`
- L115 _public typedef_ `using FAudioLinkSynchronizerSharedPtr = TSharedPtr<IAudioLinkSynchronizer, ESPMode::ThreadSafe>;` — Create a AudioLinkSynchronizer callback @return The newly created Link instance (if successful).
- L116 _public prototype_ `virtual FAudioLinkSynchronizerSharedPtr CreateSynchronizerAudioLink() = 0;`
- L123 _public function_ `inline static FName GetModularFeatureName()`
- L133 _public prototype_ `static TArray<IAudioLinkFactory*> GetAllRegisteredFactories();` — Gets all registered factory instances. @return Array of all factories.
- L139 _public prototype_ `static TArray<FName> GetAllRegisteredFactoryNames();` — Gets all registered factory names @return Array of all factory names
- L145 _public prototype_ `static IAudioLinkFactory* FindFactory(const FName InFactoryName);` — Gets all registered factory names @return Array of all factory names

#### struct `IAudioLinkFactory::FSourceBufferListenerCreateParams`  
`struct FSourceBufferListenerCreateParams`  
_L42-48_
- L44 _public member_ `int32 SizeOfBufferInFrames = 0;`
- L45 _public member_ `bool bShouldZeroBuffer = false;`
- L46 _public member_ `TWeakObjectPtr<UAudioComponent> AudioComponent;`
- L47 _public member_ `TWeakObjectPtr<USceneComponent> OwningComponent;`

#### struct `IAudioLinkFactory::FPushedBufferListenerCreateParams`  
`struct FPushedBufferListenerCreateParams`  
_L51-55_
- L53 _public member_ `int32 SizeOfBufferInFrames = INDEX_NONE;`
- L54 _public member_ `bool bShouldZeroBuffer = false;`

#### struct `IAudioLinkFactory::FSubmixBufferListenerCreateParams`  
`struct FSubmixBufferListenerCreateParams`  
_L58-62_
- L60 _public member_ `int32 SizeOfBufferInFrames = 0;`
- L61 _public member_ `bool bShouldZeroBuffer = false;`

#### struct `IAudioLinkFactory::FAudioLinkSubmixCreateArgs`  
`struct FAudioLinkSubmixCreateArgs`  
_L68-73_
- desc: Parameters use when creating a Submix Audio Link
- L70 _public member_ `TWeakObjectPtr<const USoundSubmix> Submix;`
- L71 _public member_ `FAudioDevice* Device = nullptr;`
- L72 _public member_ `TWeakObjectPtr<const UAudioLinkSettingsAbstract> Settings;`

#### struct `IAudioLinkFactory::FAudioLinkSourceCreateArgs`  
`struct FAudioLinkSourceCreateArgs`  
_L85-90_
- desc: Parameters use when creating a Source Audio Link
- L87 _public member_ `TWeakObjectPtr<UAudioComponent> AudioComponent;`
- L88 _public member_ `TWeakObjectPtr<USceneComponent> OwningComponent;`
- L89 _public member_ `TWeakObjectPtr<UAudioLinkSettingsAbstract> Settings;`

#### struct `IAudioLinkFactory::FAudioLinkSourcePushedCreateArgs`  
`struct FAudioLinkSourcePushedCreateArgs`  
_L99-107_
- L101 _public member_ `FName OwnerName;`
- L102 _public member_ `int32 NumChannels = INDEX_NONE;`
- L103 _public member_ `int32 SampleRate = INDEX_NONE;`
- L104 _public member_ `int32 NumFramesPerBuffer = INDEX_NONE;`
- L105 _public member_ `int32 TotalNumFramesInSource = INDEX_NONE;`
- L106 _public member_ `UAudioLinkSettingsAbstract::FSharedSettingsProxyPtr Settings;`

### `Source/Runtime/AudioLink/AudioLinkEngine/Public/IBufferedAudioOutput.h` (Public)


#### class `IPushableAudioOutput`  
`class IPushableAudioOutput`  
_L10-23_
- L21 _public prototype_ `virtual void PushNewBuffer(const FOnNewBufferParams&) = 0;`
- L22 _public prototype_ `virtual void LastBuffer(int32 InId) = 0;`

#### struct `IPushableAudioOutput::FOnNewBufferParams`  
`struct FOnNewBufferParams`  
_L13-20_
- L15 _public member_ `const float* AudioData = nullptr;`
- L16 _public member_ `int32 Id = INDEX_NONE;`
- L17 _public member_ `int32 NumSamples = INDEX_NONE;`
- L18 _public member_ `int32 NumChannels = INDEX_NONE;`
- L19 _public member_ `int32 SampleRate = INDEX_NONE;`

#### class `IBufferedAudioOutput`  
`class IBufferedAudioOutput`  
_L30-101_
- L33 _protected prototype_ `IBufferedAudioOutput() = default;`
- L36 _public prototype_ `virtual ~IBufferedAudioOutput() = default;`
- L56 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnFormatKnown, FBufferFormat);` — Delegates.
- L57 _public prototype_ `virtual void SetFormatKnownDelegate(FOnFormatKnown InFormatKnownDelegate) = 0;`
- L68 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnBufferStreamEnd, FBufferStreamEnd);` — Delegates.
- L69 _public prototype_ `virtual void SetBufferStreamEndDelegate(FOnBufferStreamEnd InBufferStreamEndDelegate) = 0;`
- L71 _public prototype_ `virtual bool Start(FAudioDevice* InAudioDevice) = 0;`
- L72 _public prototype_ `virtual void Stop(FAudioDevice* InAudioDevice) = 0;`
- L83 _public prototype_ `virtual bool PopBuffer(float* InBuffer, int32 InBufferSizeInSamples, int32& OutSamplesWritten) = 0;` — Attempts to Atomically copy a buffer sized amount of Buffered Sample data from the interface. @param InBuffer Sample Buffer to Write to @param InBufferSizeInSamples Buffer Size in total samples. @param OutSamplesWritten Number of Samples Written to the buffer @return false no more data, true more data to come
- L90 _public prototype_ `virtual bool GetFormat(FBufferFormat& OutFormat) const = 0;` — Gets the format of the buffer, if its known. @return  success true, false otherwise.
- L97 _public prototype_ `virtual void Reserve(int32 InNumSamplesToReserve, int32 InNumSamplesOfSilence = 0) = 0;` — Reserve at least this many samples in buffer. @param InNumSamplesToReserve Reserve this number of samples.
- L99 _public function_ `virtual IPushableAudioOutput* GetPushableInterface()`
- L100 _public function_ `virtual const IPushableAudioOutput* GetPushableInterface() const`

#### struct `IBufferedAudioOutput::FBufferFormat`  
`struct FBufferFormat`  
_L41-53_
- desc: The format of a buffer.
- L43 _public member_ `int32 NumSamplesPerBlock = 0;`
- L44 _public member_ `int32 NumChannels = 0;`
- L45 _public member_ `int32 NumSamplesPerSec = 0;`
- L47 _public function_ `bool operator==(const FBufferFormat& InRhs) const`

#### struct `IBufferedAudioOutput::FBufferStreamEnd`  
`struct FBufferStreamEnd`  
_L62-65_
- desc: Stream of buffers ended.
- L64 _public member_ `int32 Id = INDEX_NONE;`

#### Free symbols / members of external scopes

- L56 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFormatKnown, FBufferFormat);` — Delegates.
- L68 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBufferStreamEnd, FBufferStreamEnd);` — Delegates.
- L103 _typedef_ `using FWeakBufferedOutputPtr = TWeakPtr<IBufferedAudioOutput, ESPMode::ThreadSafe>;`
- L104 _typedef_ `using FSharedBufferedOutputPtr = TSharedPtr<IBufferedAudioOutput, ESPMode::ThreadSafe>;`
