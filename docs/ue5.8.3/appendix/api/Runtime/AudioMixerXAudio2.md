# Runtime / AudioMixerXAudio2

- module root: `Source/Runtime/Windows/AudioMixerXAudio2`
- headers: 3; symbols: 92
- symbol kinds: class=3, function=13, macro=1, member=20, namespace=2, prototype=51, struct=2
- PrivateDependencyModuleNames: AudioMixer, AudioMixerCore, Core, CoreUObject, Engine, WindowsMMDeviceEnumeration
- PrivateIncludePathModuleNames: TargetPlatform

### `Source/Runtime/Windows/AudioMixerXAudio2/Private/AudioMixerPlatformXAudio2.h` (Private)


#### class `Audio::FXAudio2VoiceCallback`  
`class FXAudio2VoiceCallback final : public IXAudio2VoiceCallback`  
_L27-43_
- inherits: `IXAudio2VoiceCallback`
- desc: FXAudio2VoiceCallback XAudio2 implementation of IXAudio2VoiceCallback This callback class is used to get event notifications on buffer end (when a buffer has finished processing). This is used to signal the I/O thread that it can request another buffer from the user callback.
- L30 _public function_ `FXAudio2VoiceCallback()`
- L31 _public prototype_ `~FXAudio2VoiceCallback() = default;`
- L34 _private function_ `void STDCALL OnVoiceProcessingPassStart(UINT32 BytesRequired)`
- L35 _private function_ `void STDCALL OnVoiceProcessingPassEnd()`
- L36 _private function_ `void STDCALL OnStreamEnd()`
- L37 _private function_ `void STDCALL OnBufferStart(void* BufferContext)`
- L38 _private function_ `void STDCALL OnLoopEnd(void* BufferContext)`
- L39 _private function_ `void STDCALL OnVoiceError(void* BufferContext, HRESULT Error)`
- L41 _private prototype_ `void STDCALL OnBufferEnd(void* BufferContext);`

#### struct `Audio::FXAudio2DeviceSwapContext`  
`struct FXAudio2DeviceSwapContext : public FDeviceSwapContext`  
_L45-58_
- inherits: `FDeviceSwapContext`
- L47 _public prototype_ `FXAudio2DeviceSwapContext() = delete;`
- L48 _public function_ `FXAudio2DeviceSwapContext(const FString& InRequestedDeviceID, const FString& InReason) : FDeviceSwapContext(InRequestedDeviceID, InReason)`
- L52 _public member_ `bool bUseDefaultDevice = false;`
- L53 _public member_ `IXAudio2* PreviousSystem = nullptr;`
- L54 _public member_ `IXAudio2MasteringVoice* PreviousMasteringVoice = nullptr;`
- L55 _public member_ `IXAudio2SourceVoice* PreviousSourceVoice = nullptr;`
- L56 _public member_ `FXAudio2VoiceCallback* Callbacks = nullptr;`
- L57 _public member_ `uint32 RenderingSampleRate = 0;`

#### struct `Audio::FXAudio2DeviceSwapResult`  
`struct FXAudio2DeviceSwapResult : public FDeviceSwapResult`  
_L60-70_
- inherits: `FDeviceSwapResult`
- L62 _public function_ `virtual bool IsNewDeviceReady() const override`
- L67 _public member_ `IXAudio2* NewSystem = nullptr;`
- L68 _public member_ `IXAudio2MasteringVoice* NewMasteringVoice = nullptr;`
- L69 _public member_ `IXAudio2SourceVoice* NewSourceVoice = nullptr;`

#### class `Audio::FMixerPlatformXAudio2`  
`class FMixerPlatformXAudio2 : public FAudioMixerPlatformSwappable, public IXAudio2EngineCallback`  
_L72-177_
- inherits: `FAudioMixerPlatformSwappable,IXAudio2EngineCallback`
- L78 _public prototype_ `FMixerPlatformXAudio2();`
- L82 _public function_ `virtual FString GetPlatformApi() const override`
- L83 _public prototype_ `virtual bool InitializeHardware() override;`
- L84 _public prototype_ `virtual bool CheckAudioDeviceChange() override;`
- L85 _public prototype_ `virtual bool TeardownHardware() override;`
- L86 _public prototype_ `virtual bool IsInitialized() const override;`
- L87 _public prototype_ `virtual bool GetNumOutputDevices(uint32& OutNumOutputDevices) override;`
- L88 _public prototype_ `virtual bool GetOutputDeviceInfo(const uint32 InDeviceIndex, FAudioPlatformDeviceInfo& OutInfo) override;`
- L89 _public prototype_ `virtual FString GetCurrentDeviceName() const override;`
- L90 _public prototype_ `virtual bool GetDefaultOutputDeviceIndex(uint32& OutDefaultDeviceIndex) const override;`
- L91 _public prototype_ `virtual bool OpenAudioStream(const FAudioMixerOpenStreamParams& Params) override;`
- L92 _public prototype_ `virtual bool CloseAudioStream() override;`
- L93 _public prototype_ `virtual bool StartAudioStream() override;`
- L94 _public prototype_ `virtual bool StopAudioStream() override;`
- L95 _public prototype_ `virtual bool MoveAudioStreamToNewAudioDevice() override;`
- L97 _public prototype_ `virtual FAudioPlatformDeviceInfo GetPlatformDeviceInfo() const override;`
- L98 _public prototype_ `virtual void SubmitBuffer(const uint8* Buffer) override;`
- L99 _public prototype_ `virtual FString GetDefaultDeviceName() override;`
- L100 _public prototype_ `virtual FAudioPlatformSettings GetPlatformSettings() const override;`
- L101 _public prototype_ `virtual void OnHardwareUpdate() override;`
- L102 _public prototype_ `virtual IAudioPlatformDeviceInfoCache* GetDeviceInfoCache() const override;`
- L103 _public prototype_ `virtual bool IsDeviceInfoValid(const FAudioPlatformDeviceInfo& InDeviceInfo) const override;`
- L104 _public function_ `virtual bool ShouldUseDeviceInfoCache() const override`
- L105 _public prototype_ `virtual void ResumePlaybackOnNewDevice() override;`
- L109 _public prototype_ `virtual void RegisterDeviceChangedListener() override;`
- L110 _public prototype_ `virtual void UnregisterDeviceChangedListener() override;`
- L111 _public prototype_ `virtual void OnDefaultCaptureDeviceChanged(const EAudioDeviceRole InAudioDeviceRole, const FString& DeviceId) override;`
- L112 _public prototype_ `virtual void OnDefaultRenderDeviceChanged(const EAudioDeviceRole InAudioDeviceRole, const FString& DeviceId) override;`
- L113 _public prototype_ `virtual void OnDeviceAdded(const FString& DeviceId, bool bIsRenderDevice) override;`
- L114 _public prototype_ `virtual void OnDeviceRemoved(const FString& DeviceId, bool bIsRenderDevice) override;`
- L115 _public prototype_ `virtual void OnDeviceStateChanged(const FString& DeviceId, const EAudioDeviceState InState, bool bIsRenderDevice) override;`
- L116 _public prototype_ `virtual void OnSessionDisconnect(Audio::IAudioMixerDeviceChangedListener::EDisconnectReason InReason) override;`
- L117 _public prototype_ `virtual FString GetDeviceId() const override;`
- L121 _public prototype_ `virtual bool InitializeDeviceSwapContext(const FString& InRequestedDeviceID, const TCHAR* InReason) override;`
- L122 _public prototype_ `virtual bool CheckThreadedDeviceSwap() override;`
- L123 _public prototype_ `virtual bool PreDeviceSwap() override;`
- L124 _public prototype_ `virtual void EnqueueAsyncDeviceSwap() override;`
- L125 _public prototype_ `virtual void SynchronousDeviceSwap() override;`
- L126 _public prototype_ `virtual bool PostDeviceSwap() override;`
- L130 _protected function_ `virtual uint32 GetCreateFlags() const`
- L131 _protected function_ `virtual bool ShouldUseDefaultDevice() const`
- L133 _protected prototype_ `static IXAudio2MasteringVoice* CreateMasteringVoice(IXAudio2& InXAudio2System, const FAudioPlatformDeviceInfo& NewDevice, bool bUseDefaultDevice);`
- L136 _protected prototype_ `virtual void OnCriticalError(HRESULT Error) override;`
- L137 _protected prototype_ `virtual void OnProcessingPassStart() override;`
- L138 _protected prototype_ `virtual void OnProcessingPassEnd() override;`
- L143 _protected prototype_ `bool ResetXAudio2System();` — Used to teardown and reinitialize XAudio2. This must be done to repopulate the playback device list in XAudio 2.7.
- L148 _protected prototype_ `bool InitDeviceSwapContextInternal(const FString& InRequestedDeviceID, const TCHAR* InReason, const TOptional<FAudioPlatformDeviceInfo>& InDeviceInfo);` — Can be used by subclasses to initialize a device swap context by supplying a specific FAudioPlatformDeviceInfo rather than looking it up via the requested device Id.
- L153 _protected member_ `FThreadSafeBool bDeviceChanged;` — `UE_DEPRECATED(5.6, "bDeviceChanged has been deprecated.")` — Bool indicating that the default audio device changed And that we need to restart the audio device.
- L155 _protected member_ `IXAudio2* XAudio2System;`
- L156 _protected member_ `IXAudio2MasteringVoice* OutputAudioStreamMasteringVoice;`
- L157 _protected member_ `IXAudio2SourceVoice* OutputAudioStreamSourceVoice;`
- L158 _protected member_ `FXAudio2VoiceCallback OutputVoiceCallback;`
- L162 _protected member_ `float TimeSinceNullDeviceWasLastChecked;` — When we are running the null device, we check whether a new audio device was connected every second or so.
- L164 _protected member_ `bool FirstBufferSubmitted{false};`
- L166 _protected member_ `TUniquePtr<IAudioPlatformDeviceInfoCache> DeviceInfoCache;`
- L168 _protected member_ `uint32 bIsInitialized : 1;`
- L169 _protected member_ `uint32 bIsDeviceOpen : 1;`
- L173 _private member_ `TUniquePtr<FXAudio2DeviceSwapContext> DeviceSwapContext;` — Context object holding state used during device swap.
- L176 _private prototype_ `static TUniquePtr<FDeviceSwapResult> PerformDeviceSwap(TUniquePtr<FXAudio2DeviceSwapContext>&& InDeviceContext);` — Performs a device swap with the given context. Static method enforces no other state sharing occurs.

#### Free symbols / members of external scopes

- L13 _macro_ `#define XAUDIO_SUPPORTS_DEVICE_DETAILS 1`
- L17 _namespace_ `namespace Audio`

### `Source/Runtime/Windows/AudioMixerXAudio2/Private/AudioMixerXAudio2.h` (Private)


#### class `FAudioMixerModuleXAudio2`  
`class FAudioMixerModuleXAudio2 : public IAudioDeviceModule`  
_L8-14_
- inherits: `IAudioDeviceModule`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual bool IsAudioMixerModule() const override;`
- L13 _public prototype_ `virtual Audio::IAudioMixerPlatformInterface* CreateAudioMixerPlatformInterface() override;`

### `Source/Runtime/Windows/AudioMixerXAudio2/Private/ToStringHelpers.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L10 _prototype_ `FString ToErrorFString(HRESULT InResult);` (scope `Audio`)
