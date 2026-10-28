# Runtime / AudioMixerWasapi

- module root: `Source/Runtime/Windows/AudioMixerWasapi`
- headers: 11; symbols: 267
- symbol kinds: class=13, delegate=3, function=22, member=63, namespace=10, prototype=151, struct=4, typedef=1
- PrivateDependencyModuleNames: AudioMixer, AudioMixerCore, AudioPlatformSupportWasapi, Core, CoreUObject, Engine, SignalProcessing, WindowsMMDeviceEnumeration
- PrivateIncludePathModuleNames: TargetPlatform

### `Source/Runtime/Windows/AudioMixerWasapi/Private/AudioMixerWasapi.h` (Private)


#### struct `Audio::FWasapiDeviceSwapContext`  
`struct FWasapiDeviceSwapContext : public FDeviceSwapContext`  
_L31-43_
- inherits: `FDeviceSwapContext`
- L33 _public prototype_ `FWasapiDeviceSwapContext() = delete;`
- L34 _public function_ `FWasapiDeviceSwapContext(const FString& InRequestedDeviceID, const FString& InReason) : FDeviceSwapContext(InRequestedDeviceID, InReason)`
- L38 _public member_ `FAudioPlatformSettings PlatformSettings;`
- L39 _public member_ `TArray<FWasapiRenderStreamParams> StreamParams;`
- L40 _public member_ `TFunction<void()> ReadNextBufferCallback;`
- L41 _public member_ `TUniquePtr<IAudioMixerWasapiDeviceManager> OldDeviceManager;`
- L42 _public member_ `bool bIsAggregateDevice = false;`

#### struct `Audio::FWasapiDeviceSwapResult`  
`struct FWasapiDeviceSwapResult : public FDeviceSwapResult`  
_L45-54_
- inherits: `FDeviceSwapResult`
- L47 _public function_ `virtual bool IsNewDeviceReady() const override`
- L52 _public member_ `TUniquePtr<IAudioMixerWasapiDeviceManager> NewDeviceManager;`
- L53 _public member_ `bool bIsAggregateDevice = false;`

#### class `Audio::FAudioMixerWasapi`  
`class FAudioMixerWasapi : public FAudioMixerPlatformSwappable`  
_L59-201_
- inherits: `FAudioMixerPlatformSwappable`
- desc: FAudioMixerWasapi - Wasapi audio backend for Windows and Xbox
- L63 _public prototype_ `FAudioMixerWasapi();`
- L67 _public function_ `virtual FString GetPlatformApi() const override`
- L68 _public prototype_ `virtual bool InitializeHardware() override;`
- L69 _public prototype_ `virtual bool TeardownHardware() override;`
- L70 _public prototype_ `virtual bool IsInitialized() const override;`
- L71 _public prototype_ `virtual int32 GetNumFrames(const int32 InNumRequestedFrames) override;`
- L72 _public prototype_ `virtual bool GetNumOutputDevices(uint32& OutNumOutputDevices) override;`
- L73 _public prototype_ `virtual bool GetOutputDeviceInfo(const uint32 InDeviceIndex, FAudioPlatformDeviceInfo& OutInfo) override;`
- L74 _public prototype_ `virtual bool GetDefaultOutputDeviceIndex(uint32& OutDefaultDeviceIndex) const override;`
- L75 _public prototype_ `virtual bool OpenAudioStream(const FAudioMixerOpenStreamParams& Params) override;`
- L76 _public prototype_ `virtual bool CloseAudioStream() override;`
- L77 _public prototype_ `virtual bool StartAudioStream() override;`
- L78 _public prototype_ `virtual bool StopAudioStream() override;`
- L79 _public prototype_ `virtual FAudioPlatformDeviceInfo GetPlatformDeviceInfo() const override;`
- L80 _public prototype_ `virtual void SubmitBuffer(const uint8* Buffer) override;`
- L81 _public prototype_ `virtual void SubmitDirectOutBuffer(const int32 InDirectOutIndex, const FAlignedFloatBuffer& InBuffer) override;`
- L82 _public prototype_ `virtual FString GetDefaultDeviceName() override;`
- L83 _public prototype_ `virtual FAudioPlatformSettings GetPlatformSettings() const override;`
- L84 _public prototype_ `virtual IAudioPlatformDeviceInfoCache* GetDeviceInfoCache() const override;`
- L85 _public prototype_ `virtual bool IsDeviceInfoValid(const FAudioPlatformDeviceInfo& InDeviceInfo) const override;`
- L86 _public function_ `virtual bool ShouldUseDeviceInfoCache() const override`
- L87 _public prototype_ `virtual void ResumePlaybackOnNewDevice() override;`
- L91 _public prototype_ `virtual void RegisterDeviceChangedListener() override;`
- L92 _public prototype_ `virtual void UnregisterDeviceChangedListener() override;`
- L93 _public prototype_ `virtual void OnDefaultCaptureDeviceChanged(const EAudioDeviceRole InAudioDeviceRole, const FString& DeviceId) override;`
- L94 _public prototype_ `virtual void OnDefaultRenderDeviceChanged(const EAudioDeviceRole InAudioDeviceRole, const FString& DeviceId) override;`
- L95 _public prototype_ `virtual void OnDeviceAdded(const FString& DeviceId, bool bIsRenderDevice) override;`
- L96 _public prototype_ `virtual void OnDeviceRemoved(const FString& DeviceId, bool bIsRenderDevice) override;`
- L97 _public prototype_ `virtual void OnDeviceStateChanged(const FString& DeviceId, const EAudioDeviceState InState, bool bIsRenderDevice) override;`
- L98 _public prototype_ `virtual void OnFormatChanged(const FString& InDeviceId, const FFormatChangedData& InFormat) override;`
- L99 _public prototype_ `virtual void OnSessionDisconnect(Audio::IAudioMixerDeviceChangedListener::EDisconnectReason InReason) override;`
- L100 _public prototype_ `virtual FString GetDeviceId() const override;`
- L104 _public prototype_ `virtual bool InitializeDeviceSwapContext(const FString& InRequestedDeviceID, const TCHAR* InReason) override;`
- L105 _public prototype_ `virtual bool CheckThreadedDeviceSwap() override;`
- L106 _public prototype_ `virtual bool PreDeviceSwap() override;`
- L107 _public prototype_ `virtual void EnqueueAsyncDeviceSwap() override;`
- L108 _public prototype_ `virtual void SynchronousDeviceSwap() override;`
- L109 _public prototype_ `virtual bool PostDeviceSwap() override;`
- L116 _public function_ `bool IsAudioServiceAvailable() const` — Returns false if we have observed an audsrv shutdown (IAudioSessionEvents::OnSessionDisconnected with reason ServerShutdown) and have not yet seen the service come back. While false, no new WASAPI calls should be issued: they would block on a dead service. The SCM watcher (future CL) is responsible for calling MarkAudioServiceAvailable() once the service is confirmed running.
- L121 _public function_ `void MarkAudioServiceAvailable()` — Called when the SCM watcher confirms Audiosrv/AudioEndpointBuilder are RUNNING again (or by tests that simulate recovery). Caller is responsible for issuing a fresh RequestDeviceSwap to bring real audio back.
- L128 _public prototype_ `void OnAudioServiceRestarted();` — Recovery handler invoked by FWasapiServiceWatcher when both Audiosrv and AudioEndpointBuilder have returned to SERVICE_RUNNING after either was observed non-RUNNING. Smoke-tests audsrv readiness via CoCreateInstance, then marks the service available and issues a recovery swap. Runs on the watcher thread; RequestDeviceSwap is thread-safe so no explicit marshalling is required.
- L134 _protected prototype_ `bool InitDeviceSwapContextInternal(const FString& InRequestedDeviceID, const TCHAR* InReason, const TOptional<FAudioPlatformDeviceInfo>& InDeviceInfo);` — Can be used by subclasses to initialize a device swap context by supplying a specific FAudioPlatformDeviceInfo rather than looking it up via the requested device Id.
- L137 _protected function_ `virtual EAudioDeviceRole GetDefaultDeviceRole() const` — Returns the device role to be used when swapping to the default device.
- L142 _private member_ `TUniquePtr<IAudioPlatformDeviceInfoCache> DeviceInfoCache;` — Cache for holding information about MM audio devices (IMMDevice).
- L145 _private member_ `TUniquePtr<IAudioMixerWasapiDeviceManager> DeviceManager;` — Manages either a single, default device or an aggregate of several devices belonging to the same hardware
- L148 _private member_ `bool bIsInitialized = false;` — Indicates if this object has been successfully initialized.
- L159 _private member_ `std::atomic<bool> bAudioServiceAvailable = true;` — True while the Windows audio service is believed to be alive. Writers (publish-only, never take DeviceSwapCriticalSection): - FAudioMixerWasapi::OnSessionDisconnect(ServerShutdown) on COM session-events thread - FAudioMixerWasapi::OnDeviceRemoved / OnDeviceStateChanged on COM device-events thread (gated on IsAudsrvCurrentlyRunning() SCM probe) - MarkAudioServiceAvailable() on the SCM watcher thread (from OnAudioServiceRestarted) Consumers: - FAudioMixerWasapi::CheckThreadedDeviceSwap on the audio thread - parks on null renderer when false, gates recovery swaps when true.
- L165 _private member_ `TUniquePtr<FWasapiServiceWatcher> ServiceWatcher;` — Watches Audiosrv / AudioEndpointBuilder for SCM state transitions. Started in InitializeHardware (gated on au.AudioMixerWasapi.AudsrvWatcher.Enabled), stopped in TeardownHardware. Calls OnAudioServiceRestarted on its thread when both services return to RUNNING after either was observed non-RUNNING.
- L168 _private member_ `TUniquePtr<FWasapiDeviceSwapContext> DeviceSwapContext;` — Device swap context which holds necessary data required to perform a device wap.
- L171 _private prototype_ `TComPtr<IMMDevice> GetMMDevice(const FString& InDeviceID) const;` — Fetches an IMMDevice with the given ID. May invalidate or refresh the device info cache when the OS reports the ID unresolvable .
- L177 _private prototype_ `void UpdateCacheFromFailedDevice(const FString& InDeviceID) const;` — Recovery dispatch when a cached IAudioPlatformDeviceInfoCache entry is out of sync with the OS: either GetMMDevice could not resolve the ID, or the render thread observed AUDCLNT_E_DEVICE_INVALIDATED / AUDCLNT_E_SERVICE_NOT_RUNNING. Governed by au.AudioMixerWasapi.{Refresh,Invalidate}DeviceOnGetFailure. No-op if no cache is in use.
- L182 _private prototype_ `FString ExtractAggregateDeviceName(const FString& InDeviceID) const;` — Extracts the hardware device name from a logical device name. The OS places the hardware name in parentheses at the end of the string).
- L185 _private prototype_ `static void CreateDeviceManager(const bool bInUseAggregateDevice, TUniquePtr<IAudioMixerWasapiDeviceManager>& InDeviceManager);` — Device manager factory
- L188 _private prototype_ `bool InitStreamParams(const uint32 InDeviceIndex, const int32 InNumBufferFrames, const int32 InNumBuffers, const int32 InSampleRate, TArray<FWasapiRenderStreamParams>& OutParams);` — Initializes a Wasapi stream parameters struct with the give values.
- L189 _private prototype_ `bool InitStreamParams(const FAudioPlatformDeviceInfo& InDeviceInfo, const int32 InNumBufferFrames, const int32 InNumBuffers, const int32 InSampleRate, TArray<FWasapiRenderStreamParams>& OutParams) const;`
- L192 _private prototype_ `static TUniquePtr<FDeviceSwapResult> PerformDeviceSwap(TUniquePtr<FWasapiDeviceSwapContext>&& InDeviceContext);` — Performs a device swap with the given context. Static method enforces no other state sharing occurs.
- L196 _private prototype_ `static void RegisterForSessionEvents(const FString& InDeviceId);` — Register with the Windows MM Notification Client for updates
- L197 _private prototype_ `static void UnregisterForSessionEvents();`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace Audio`

### `Source/Runtime/Windows/AudioMixerWasapi/Private/AudioMixerWasapiDeviceThread.h` (Private)


#### class `Audio::FAudioMixerWasapiRunnable`  
`class FAudioMixerWasapiRunnable : public FRunnable`  
_L30-73_
- inherits: `FRunnable`
- desc: FAudioMixerWasapiRunnable - The runnable which executes the main thread loop for FWasapiCaptureThread.
- L33 _public prototype_ `FAudioMixerWasapiRunnable() = delete;`
- L38 _public prototype_ `FAudioMixerWasapiRunnable(const TFunction<void()>& InDeviceRenderCallback, HANDLE& OutEventHandle);` — FAudioMixerWasapiRunnable
- L43 _public prototype_ `FAudioMixerWasapiRunnable(const TFunction<void()>& InDeviceRenderCallback, TArray<HANDLE>& OutEventHandles, const int32 InNumRequestedHandles);` — FAudioMixerWasapiRunnable
- L46 _public prototype_ `virtual ~FAudioMixerWasapiRunnable() = default;` — Default destructor
- L49 _public prototype_ `virtual uint32 Run() override;`
- L50 _public prototype_ `virtual void Stop() override;`
- L55 _private member_ `std::atomic<bool> bIsRunning;` — The main run loop for this runnable will continue iterating while this flag is true.
- L61 _private member_ `TArray<HANDLE> EventHandles;` — Event handle which our audio thread waits on prior to each callback. WASAPI signals this object each quanta when a buffer of audio has been rendered and is ready for more data.
- L67 _private member_ `uint32 OutputStreamTimeoutsDetected = 0;` — Accumulates timeouts which occur when the thread event timeout is reached prior to the event being signaled for new data being available.
- L70 _private member_ `TFunction<void()> DeviceRenderCallback;` — Callback function to be called each time the device signals it is ready for another buffer of audio.
- L72 _private prototype_ `bool CreateEventHandles(const uint32 InNumRequestedHandles = 1);`

#### class `Audio::FAudioMixerWasapiDeviceThread`  
`class FAudioMixerWasapiDeviceThread`  
_L78-120_
- desc: FAudioMixerWasapiDeviceThread - Manages both the FAudioMixerWasapiRunnable object and the thread whose context it runs in.
- L81 _public prototype_ `FAudioMixerWasapiDeviceThread() = delete;`
- L86 _public prototype_ `FAudioMixerWasapiDeviceThread(const TFunction<void()>& InDeviceRenderCallback, HANDLE& OutEventHandle);` — FAudioMixerWasapiDeviceThread
- L91 _public prototype_ `FAudioMixerWasapiDeviceThread(const TFunction<void()>& InDeviceRenderCallback, TArray<HANDLE>& OutEventHandles, const int32 InNumRequestedHandles);` — FAudioMixerWasapiDeviceThread
- L98 _public prototype_ `bool Start();` — Start - Creates the FRunnableThread object which immediately begins running the FAudioMixerWasapiRunnable member. @return - Boolean indicating of the thread was successfully created.
- L103 _public prototype_ `void Stop();` — Stop - Gracefully shuts down the thread.
- L109 _public prototype_ `void Abort();` — Abort - Performs non-graceful shutdown of thread which will close the underlying thread handle without waiting for it to finish.
- L113 _private member_ `static std::atomic<uint32> AudioDeviceThreadCounter;` — Tracks number of device threads created.
- L116 _private member_ `TUniquePtr<FRunnableThread> DeviceRenderThread;` — The thread which is the context that the runnable executes in.
- L119 _private member_ `TUniquePtr<FAudioMixerWasapiRunnable> DeviceRenderRunnable;` — The runnable which manages the run loop for the render stream.

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace Audio`

### `Source/Runtime/Windows/AudioMixerWasapi/Private/AudioMixerWasapiLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioMixerWasapi, Log, All);`

### `Source/Runtime/Windows/AudioMixerWasapi/Private/AudioMixerWasapiModule.h` (Private)


#### class `FAudioMixerModuleWasapi`  
`class FAudioMixerModuleWasapi : public IAudioDeviceModule`  
_L8-14_
- inherits: `IAudioDeviceModule`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual bool IsAudioMixerModule() const override;`
- L13 _public prototype_ `virtual Audio::IAudioMixerPlatformInterface* CreateAudioMixerPlatformInterface() override;`

### `Source/Runtime/Windows/AudioMixerWasapi/Private/AudioMixerWasapiRenderStream.h` (Private)


#### class `Audio::FAudioMixerWasapiRenderStream`  
`class FAudioMixerWasapiRenderStream : public IDeviceRenderCallback`  
_L47-129_
- inherits: `IDeviceRenderCallback`
- desc: FAudioMixerWasapiRenderStream
- L51 _public prototype_ `FAudioMixerWasapiRenderStream();`
- L52 _public prototype_ `virtual ~FAudioMixerWasapiRenderStream();`
- L54 _public prototype_ `virtual bool InitializeHardware(const FWasapiRenderStreamParams& InParams);`
- L55 _public prototype_ `virtual bool TeardownHardware();`
- L56 _public prototype_ `virtual bool IsInitialized() const;`
- L57 _public prototype_ `virtual int32 GetNumFrames(const int32 InNumRequestedFrames) const;`
- L58 _public prototype_ `virtual bool OpenAudioStream(const FWasapiRenderStreamParams& InParams, HANDLE InEventHandle);`
- L59 _public prototype_ `virtual bool CloseAudioStream();`
- L60 _public prototype_ `virtual bool StartAudioStream();`
- L61 _public prototype_ `virtual bool StopAudioStream();`
- L62 _public function_ `virtual void SubmitBuffer(const uint8* Buffer, const SIZE_T InNumFrames)`
- L63 _public function_ `virtual void SubmitDirectOutBuffer(const int32 InChannelIndex, const FAlignedFloatBuffer& InBuffer)`
- L68 _public function_ `bool IsDeviceLost() const` — Returns true if the render thread has observed AUDCLNT_E_DEVICE_INVALIDATED or AUDCLNT_E_SERVICE_NOT_RUNNING from a WASAPI call since the last ClearDeviceLost(). Set on the WASAPI render thread, polled on the audio thread.
- L73 _public function_ `void SetDeviceLost()` — Forces the device-lost kill switch on. Used by the audio thread when parking the WASAPI render callback before audsrv has had a chance to fail a call. Sets the flag without logging; the parking site logs once.
- L76 _public function_ `void ClearDeviceLost()` — Clears the device-lost flag. Called by the audio thread after a recovery swap is requested.
- L79 _public prototype_ `static uint32 GetMinimumBufferSize(const uint32 InSampleRate);` — `UE_DEPRECATED(5.7, "GetMinimumBufferSize() is deprecated. Please use GetDefaultDevicePeriod() in the future.")`
- L84 _protected function_ `uint32 GetDefaultDevicePeriod() const` — Returns the default callback period for as reported by the device.
- L87 _protected member_ `TComPtr<IAudioClient2> AudioClient;` — COM pointer to the WASAPI audio client object.
- L90 _protected member_ `TComPtr<IAudioRenderClient> RenderClient;` — COM pointer to the WASAPI render client object.
- L93 _protected member_ `FWasapiAudioFormat AudioFormat;` — Holds the audio format configuration for this stream.
- L96 _protected member_ `std::atomic<bool> bIsInitialized = false;` — Indicates if this object has been successfully initialized.
- L99 _protected member_ `std::atomic<EAudioOutputStreamState::Type> StreamState = EAudioOutputStreamState::Closed;` — The state of the output audio stream.
- L102 _protected member_ `FWasapiRenderStreamParams RenderStreamParams;` — Render output device info.
- L105 _protected member_ `uint32 DefaultDevicePeriod = 0;` — The default callback period for this WASAPI render device.
- L109 _protected member_ `uint32 NumFramesPerDeviceBuffer = 0;` — Number of frames of audio data which will be used for each audio callback. This value is determined by the WASAPI audio client and can be equal or greater than the number of frames requested.
- L112 _protected member_ `uint32 CallbackBufferErrors = 0;` — Accumulates errors that occur in the audio callback.
- L117 _protected member_ `std::atomic<bool> bDeviceLost = false;` — Set by the WASAPI render thread when a device-invalidation HRESULT is observed (AUDCLNT_E_DEVICE_INVALIDATED, AUDCLNT_E_SERVICE_NOT_RUNNING). Polled by the audio thread (FAudioMixerWasapi::CheckThreadedDeviceSwap) to trigger a swap.
- L120 _protected member_ `FAlignedFloatBuffer DownmixScratchBuffer;` — Scratch buffer used for downmixing output.
- L123 _protected member_ `TArray<float> MixdownGainsMap;` — Per-channel gains used when downmixing.
- L128 _private prototype_ `void InitializeDownmixBuffers(const int32 InNumInputChannels, const int32 InNumFrames, const FWasapiAudioFormat& InAudioOutputFormat);` — Initializes the necessary data structures needed for downmixing audio buffers.

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DELEGATE(FAudioMixerReadNextBufferDelegate);`
- L25 _prototype_ `DECLARE_DELEGATE(FAudioMixerReadNextBufferDelegate);`
- L27 _namespace_ `namespace Audio`
- L33 _function_ `inline bool IsDeviceLostHResult(HRESULT InResult)` (scope `Audio`) — Returns true for HRESULTs that mean the existing IAudioClient is no longer usable and the engine should request a device swap to recover. Defined inline in the header so both FWasapiDefaultRenderStream and FWasapiAggregateRenderStream can share one definition

### `Source/Runtime/Windows/AudioMixerWasapi/Private/IAudioMixerWasapiDeviceManager.h` (Private)


#### struct `Audio::FWasapiRenderStreamParams`  
`struct FWasapiRenderStreamParams`  
_L27-58_
- desc: Defines parameters needed for opening a new audio stream to device.
- L30 _public member_ `TComPtr<IMMDevice> MMDevice;` — The audio device to open.
- L33 _public member_ `FAudioPlatformDeviceInfo HardwareDeviceInfo;` — Hardware device configuration info.
- L36 _public member_ `uint32 NumFrames = 0;` — The number of desired audio frames in audio callback.
- L39 _public member_ `int32 NumBuffers = 0;` — The number of buffers to keep enqueued. More buffers increases latency, but can compensate for variable compute availability in audio callbacks on some platforms.
- L42 _public member_ `uint32 SampleRate = 0;` — The desired sample rate
- L44 _public prototype_ `FWasapiRenderStreamParams() = default;`
- L46 _public function_ `FWasapiRenderStreamParams(const TComPtr<IMMDevice>& InMMDevice, const FAudioPlatformDeviceInfo& InDeviceInfo, const uint32 InNumFrames, const uint32 InNumBuffers, const uint32 InSampleRate) : MMDevice(InMMDevice), HardwareDeviceInfo(InDeviceInfo), NumFrames(InNumFrames), NumBuffers(InNumBuffers), SampleRate(InSampleRate)`

#### class `Audio::IAudioMixerWasapiDeviceManager`  
`class IAudioMixerWasapiDeviceManager`  
_L63-91_
- desc: IAudioMixerWasapiDeviceManager - classes implementing this interface manage underlying render device streams
- L67 _public prototype_ `IAudioMixerWasapiDeviceManager() = default;`
- L68 _public prototype_ `virtual ~IAudioMixerWasapiDeviceManager() = default;`
- L70 _public prototype_ `virtual bool InitializeHardware(const TArray<FWasapiRenderStreamParams>& InParams, const TFunction<void()>& InCallback) = 0;`
- L71 _public prototype_ `virtual bool TeardownHardware() = 0;`
- L72 _public prototype_ `virtual bool IsInitialized() const = 0;`
- L73 _public prototype_ `virtual int32 GetNumDirectOutChannels() const = 0;`
- L74 _public prototype_ `virtual int32 GetNumFrames(const int32 InNumRequestedFrames) const = 0;`
- L75 _public prototype_ `virtual bool OpenAudioStream(const TArray<FWasapiRenderStreamParams>& InParams) = 0;`
- L76 _public prototype_ `virtual bool CloseAudioStream() = 0;`
- L77 _public prototype_ `virtual bool StartAudioStream() = 0;`
- L78 _public prototype_ `virtual bool StopAudioStream() = 0;`
- L79 _public prototype_ `virtual void SubmitBuffer(const uint8* InBuffer, const SIZE_T InNumFrames) = 0;`
- L80 _public prototype_ `virtual void SubmitDirectOutBuffer(const int32 InDirectOutIndex, const FAlignedFloatBuffer& InBuffer) = 0;`
- L83 _public prototype_ `virtual bool IsDeviceLost() const = 0;` — Returns true if the underlying main render stream observed a device-invalidation HRESULT.
- L87 _public prototype_ `virtual void SetDeviceLost() = 0;` — Forces the device-lost flag on. Called by the audio thread when parking the WASAPI render callback ahead of audsrv-driven failure.
- L90 _public prototype_ `virtual void ClearDeviceLost() = 0;` — Clears the device-lost flag on the underlying main render stream.

#### class `Audio::IDeviceRenderCallback`  
`class IDeviceRenderCallback`  
_L97-103_
- L100 _public prototype_ `virtual ~IDeviceRenderCallback() = default;`
- L102 _public prototype_ `virtual void DeviceRenderCallback() = 0;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE(FAudioMixerReadNextBufferDelegate);`
- L22 _prototype_ `DECLARE_DELEGATE(FAudioMixerReadNextBufferDelegate);`
- L24 _namespace_ `namespace Audio`

### `Source/Runtime/Windows/AudioMixerWasapi/Private/WasapiAggregateDeviceMgr.h` (Private)


#### class `Audio::FWasapiAggregateDeviceMgr`  
`class FWasapiAggregateDeviceMgr : public IAudioMixerWasapiDeviceManager, public IDeviceRenderCallback`  
_L18-64_
- inherits: `IAudioMixerWasapiDeviceManager,IDeviceRenderCallback`
- desc: FWasapiAggregateDeviceMgr Manages the software device streams associated with a single, physical hardware device. This provides the ability to address more than 8 channels of a physical device using the Windows Audio Streaming API (WASAPI).
- L22 _public prototype_ `FWasapiAggregateDeviceMgr();`
- L23 _public prototype_ `virtual ~FWasapiAggregateDeviceMgr() = default;`
- L26 _public prototype_ `virtual bool InitializeHardware(const TArray<FWasapiRenderStreamParams>& InParams, const TFunction<void()>& InCallback) override;`
- L27 _public prototype_ `virtual bool TeardownHardware() override;`
- L28 _public prototype_ `virtual bool IsInitialized() const override;`
- L29 _public function_ `virtual int32 GetNumDirectOutChannels() const override`
- L30 _public prototype_ `virtual int32 GetNumFrames(const int32 InNumRequestedFrames) const override;`
- L31 _public prototype_ `virtual bool OpenAudioStream(const TArray<FWasapiRenderStreamParams>& InParams) override;`
- L32 _public prototype_ `virtual bool CloseAudioStream() override;`
- L33 _public prototype_ `virtual bool StartAudioStream() override;`
- L34 _public prototype_ `virtual bool StopAudioStream() override;`
- L35 _public prototype_ `virtual void SubmitBuffer(const uint8* InBuffer, const SIZE_T InNumFrames) override;`
- L36 _public prototype_ `virtual void SubmitDirectOutBuffer(const int32 InDirectOutIndex, const FAlignedFloatBuffer& InBuffer) override;`
- L37 _public prototype_ `virtual bool IsDeviceLost() const override;`
- L38 _public prototype_ `virtual void SetDeviceLost() override;`
- L39 _public prototype_ `virtual void ClearDeviceLost() override;`
- L43 _public prototype_ `virtual void DeviceRenderCallback() override;`
- L48 _private member_ `bool bIsInitialized = false;`
- L51 _private member_ `int32 NumChannelsPerDevice = 0;` — The number of channels per WASAPI deivce (max 8 channels)
- L57 _private member_ `int32 NumDirectOutChannels = 0;` — The number of direct output channels supported by the physical device. The sum total channels of all WASAPI audio devices belonging to the physical device, minus the number of main out channels (typically the first 8 channels)
- L60 _private member_ `TArray<TUniquePtr<FAudioMixerWasapiRenderStream>> RenderStreamDevices;` — The render streams associated with this aggregate device
- L63 _private member_ `TUniquePtr<FAudioMixerWasapiDeviceThread> RenderDeviceThread;` — The thread which provides an execution context during audio playback.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/Windows/AudioMixerWasapi/Private/WasapiAggregateRenderStream.h` (Private)


#### class `Audio::FWasapiAggregateRenderStream`  
`class FWasapiAggregateRenderStream : public FAudioMixerWasapiRenderStream`  
_L15-37_
- inherits: `FAudioMixerWasapiRenderStream`
- desc: FWasapiAggregateRenderStream A render stream which can be sent to direct output channels which are channels of an aggregate device above the first 8 channels which are reserved for the main output of the editor/game.
- L19 _public prototype_ `virtual ~FWasapiAggregateRenderStream() = default;`
- L22 _public prototype_ `virtual bool InitializeHardware(const FWasapiRenderStreamParams& InParams) override;`
- L23 _public prototype_ `virtual bool StartAudioStream() override;`
- L24 _public prototype_ `virtual void SubmitDirectOutBuffer(const int32 InChannelIndex, const FAlignedFloatBuffer& InBuffer) override;`
- L28 _public prototype_ `virtual void DeviceRenderCallback() override;`
- L33 _private member_ `TArray<FAlignedFloatBuffer> InterleaveBuffers;`
- L34 _private member_ `TArray<TCircularAudioBuffer<float>> DirectOutBuffers;`
- L36 _private prototype_ `void InterleaveOutput(float* InRenderBufferPtr, const uint32 InNumFrames);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/Windows/AudioMixerWasapi/Private/WasapiDefaultDeviceMgr.h` (Private)


#### class `Audio::FWasapiDefaultDeviceMgr`  
`class FWasapiDefaultDeviceMgr : public IAudioMixerWasapiDeviceManager`  
_L15-46_
- inherits: `IAudioMixerWasapiDeviceManager`
- desc: FAudioMixerWasapi Manages a single audio device which is used for the main (first eight) output channels.
- L19 _public prototype_ `FWasapiDefaultDeviceMgr() = default;`
- L20 _public prototype_ `virtual ~FWasapiDefaultDeviceMgr() = default;`
- L23 _public prototype_ `virtual bool InitializeHardware(const TArray<FWasapiRenderStreamParams>& InParams, const TFunction<void()>& InCallback) override;`
- L24 _public prototype_ `virtual bool TeardownHardware() override;`
- L25 _public prototype_ `virtual bool IsInitialized() const override;`
- L26 _public function_ `virtual int32 GetNumDirectOutChannels() const override`
- L27 _public prototype_ `virtual int32 GetNumFrames(const int32 InNumRequestedFrames) const override;`
- L28 _public prototype_ `virtual bool OpenAudioStream(const TArray<FWasapiRenderStreamParams>& InParams) override;`
- L29 _public prototype_ `virtual bool CloseAudioStream() override;`
- L30 _public prototype_ `virtual bool StartAudioStream() override;`
- L31 _public prototype_ `virtual bool StopAudioStream() override;`
- L32 _public prototype_ `virtual void SubmitBuffer(const uint8* InBuffer, const SIZE_T InNumFrames) override;`
- L33 _public function_ `virtual void SubmitDirectOutBuffer(const int32 InDirectOutIndex, const FAlignedFloatBuffer& InBuffer) override`
- L34 _public prototype_ `virtual bool IsDeviceLost() const override;`
- L35 _public prototype_ `virtual void SetDeviceLost() override;`
- L36 _public prototype_ `virtual void ClearDeviceLost() override;`
- L42 _private member_ `TUniquePtr<FWasapiDefaultRenderStream> MainRenderStreamDevice;` — The main audio device for outputting up to 8 channels.
- L45 _private member_ `TUniquePtr<FAudioMixerWasapiDeviceThread> RenderDeviceThread;` — The thread which provides an execution context during audio playback.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/Windows/AudioMixerWasapi/Private/WasapiDefaultRenderStream.h` (Private)


#### class `Audio::FWasapiDefaultRenderStream`  
`class FWasapiDefaultRenderStream : public FAudioMixerWasapiRenderStream`  
_L16-48_
- inherits: `FAudioMixerWasapiRenderStream`
- desc: FWasapiDefaultRenderStream The default channel output stream. This is the first eight channels which are reserved for the main outputs of the editor/game.
- L20 _public prototype_ `virtual ~FWasapiDefaultRenderStream() = default;`
- L23 _public prototype_ `virtual bool InitializeHardware(const FWasapiRenderStreamParams& InParams) override;`
- L24 _public prototype_ `virtual bool TeardownHardware() override;`
- L25 _public prototype_ `virtual void SubmitBuffer(const uint8* Buffer, const SIZE_T InNumFrames) override;`
- L29 _public prototype_ `virtual void DeviceRenderCallback() override;`
- L32 _public function_ `FAudioMixerReadNextBufferDelegate& OnReadNextBuffer()`
- L37 _private member_ `int32 EngineBufferNumFrames = 0;` — Number of frames to write every Wasapi period (must be at least the minimum required for current driver)
- L41 _private member_ `SIZE_T EngineBufferNumBytes = 0;` — Number of bytes per partial buffer where a partial buffer is used when the engine buffer size is less than the Wasapi drivers buffer size.
- L44 _private member_ `FAudioMixerReadNextBufferDelegate ReadNextBufferDelegate;` — Delegate called each buffer callback to signal the mixer to process the next buffer.
- L47 _private member_ `TArrayView<uint8> RenderBufferView;` — Pointer to WASAPI render audio buffer filled in each callback by the mixer in SubmitBuffer().

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_DELEGATE(FAudioMixerReadNextBufferDelegate);`
- L7 _prototype_ `DECLARE_DELEGATE(FAudioMixerReadNextBufferDelegate);`
- L9 _namespace_ `namespace Audio`

### `Source/Runtime/Windows/AudioMixerWasapi/Private/WasapiServiceWatcher.h` (Private)


#### class `Audio::FWasapiServiceWatcher`  
`class FWasapiServiceWatcher : public FRunnable`  
_L42-104_
- inherits: `FRunnable`
- desc: FWasapiServiceWatcher Watches Windows Service Control Manager state for Audiosrv and AudioEndpointBuilder via NotifyServiceStatusChangeW. Fires the registered callback (on the watcher thread) when both services transition back to SERVICE_RUNNING after either was observed non-RUNNING. The handler is responsible for marshalling work to the audio thread if needed; RequestDeviceSwap is thread-safe so it can be called directly. Lifecycle: construct, StartWatching(...), StopWatching(). Safe to destroy after Stop. Internally owns one dedicated OS thread that sits in an alertable wait - APC delivery is how SCM gives us notifications, so the wait must be alertable. Stop signaling uses a manual-reset event plus a no-op QueueUserAPC fallback for clean wakeup.
- L45 _public typedef_ `using FOnServicesRunningCallback = TFunction<void()>;`
- L47 _public prototype_ `FWasapiServiceWatcher();`
- L48 _public prototype_ `virtual ~FWasapiServiceWatcher();`
- L51 _public prototype_ `bool StartWatching(FOnServicesRunningCallback InCallback);` — Start the watcher thread. Returns false if SCM open / notification setup fails.
- L54 _public prototype_ `void StopWatching();` — Stop the watcher thread and release SCM handles. Blocks until the thread exits.
- L57 _public prototype_ `virtual uint32 Run() override;`
- L58 _public prototype_ `virtual void Stop() override;` — Sets stop flag and signals the wait event.
- L62 _public function_ `bool IsStopping() const` — Used by the static APC callback to decide whether to re-arm.
- L77 _private prototype_ `static VOID WINAPI ServiceNotifyAPC(void* pParam);` — Static APC trampoline; recovers the FServiceWatchState from pNotify->pContext.
- L80 _private prototype_ `void OnServiceStateChanged(FServiceWatchState& State, DWORD NewState);` — Called from ServiceNotifyAPC on the watcher thread when a service state arrives.
- L83 _private prototype_ `bool ArmNotification(FServiceWatchState& State);` — Calls NotifyServiceStatusChangeW with our mask and re-arms the callback.
- L86 _private prototype_ `bool BothServicesRunning() const;` — True if both services are last-known RUNNING.
- L91 _private prototype_ `void CloseServiceHandles();` — Closes ScmHandle and both per-service handles if open. Null-safe; pairs with the synchronous opens in StartWatching. Called from StopWatching after the watcher thread has joined, and from StartWatching's failure cleanup paths.
- L93 _private member_ `SC_HANDLE ScmHandle = nullptr;`
- L94 _private member_ `FServiceWatchState AudsrvState;`
- L95 _private member_ `FServiceWatchState AebState;`
- L98 _private member_ `bool bSawNonRunningStatus = false;` — Latched when either service is observed non-RUNNING; cleared when recovery fires.
- L100 _private member_ `FOnServicesRunningCallback RecoveryCallback;`
- L101 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L102 _private member_ `HANDLE StopEvent = nullptr;` — manual-reset; signaled to wake the alertable wait
- L103 _private member_ `std::atomic<bool> bShouldStop = false;`
- L119 _public function_ `bool StartWatching(FOnServicesRunningCallback)`
- L120 _public function_ `void StopWatching()`

#### struct `Audio::FWasapiServiceWatcher::FServiceWatchState`  
`struct FServiceWatchState`  
_L67-74_
- desc: Per-service watch state. Holds the SERVICE_NOTIFYW that NotifyServiceStatusChangeW needs to outlive the call (the OS writes to it asynchronously).
- L69 _public member_ `SERVICE_NOTIFYW Notify = {};`
- L70 _public member_ `SC_HANDLE Handle = nullptr;`
- L71 _public member_ `const TCHAR* DisplayName = nullptr;`
- L72 _public member_ `DWORD LastState = 0;` — SERVICE_RUNNING / SERVICE_STOPPED / SERVICE_*_PENDING
- L73 _public member_ `FWasapiServiceWatcher* Owner = nullptr;`

#### class `Audio::FWasapiServiceWatcher`  
`class FWasapiServiceWatcher`  
_L115-121_
- L45 _public typedef_ `using FOnServicesRunningCallback = TFunction<void()>;`
- L47 _public prototype_ `FWasapiServiceWatcher();`
- L48 _public prototype_ `virtual ~FWasapiServiceWatcher();`
- L51 _public prototype_ `bool StartWatching(FOnServicesRunningCallback InCallback);` — Start the watcher thread. Returns false if SCM open / notification setup fails.
- L54 _public prototype_ `void StopWatching();` — Stop the watcher thread and release SCM handles. Blocks until the thread exits.
- L57 _public prototype_ `virtual uint32 Run() override;`
- L58 _public prototype_ `virtual void Stop() override;` — Sets stop flag and signals the wait event.
- L62 _public function_ `bool IsStopping() const` — Used by the static APC callback to decide whether to re-arm.
- L77 _private prototype_ `static VOID WINAPI ServiceNotifyAPC(void* pParam);` — Static APC trampoline; recovers the FServiceWatchState from pNotify->pContext.
- L80 _private prototype_ `void OnServiceStateChanged(FServiceWatchState& State, DWORD NewState);` — Called from ServiceNotifyAPC on the watcher thread when a service state arrives.
- L83 _private prototype_ `bool ArmNotification(FServiceWatchState& State);` — Calls NotifyServiceStatusChangeW with our mask and re-arms the callback.
- L86 _private prototype_ `bool BothServicesRunning() const;` — True if both services are last-known RUNNING.
- L91 _private prototype_ `void CloseServiceHandles();` — Closes ScmHandle and both per-service handles if open. Null-safe; pairs with the synchronous opens in StartWatching. Called from StopWatching after the watcher thread has joined, and from StartWatching's failure cleanup paths.
- L93 _private member_ `SC_HANDLE ScmHandle = nullptr;`
- L94 _private member_ `FServiceWatchState AudsrvState;`
- L95 _private member_ `FServiceWatchState AebState;`
- L98 _private member_ `bool bSawNonRunningStatus = false;` — Latched when either service is observed non-RUNNING; cleared when recovery fires.
- L100 _private member_ `FOnServicesRunningCallback RecoveryCallback;`
- L101 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L102 _private member_ `HANDLE StopEvent = nullptr;` — manual-reset; signaled to wake the alertable wait
- L103 _private member_ `std::atomic<bool> bShouldStop = false;`
- L119 _public function_ `bool StartWatching(FOnServicesRunningCallback)`
- L120 _public function_ `void StopWatching()`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace Audio`
- L113 _namespace_ `namespace Audio`
