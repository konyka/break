# Runtime / AudioMixerPlatformAudioLink

- module root: `Source/Runtime/AudioLink/AudioMixerPlatformAudioLink`
- headers: 1; symbols: 34
- symbol kinds: class=1, function=1, member=11, namespace=1, prototype=20
- PrivateDependencyModuleNames: AudioLinkEngine, AudioMixer, AudioMixerCore, Core, CoreUObject, Engine
- PrivateIncludePathModuleNames: TargetPlatform
- PublicIncludePathModuleNames: AudioMixer

### `Source/Runtime/AudioLink/AudioMixerPlatformAudioLink/Private/AudioMixerPlatformAudioLink.h` (Private)


#### class `Audio::FAudioMixerPlatformAudioLink`  
`class FAudioMixerPlatformAudioLink : public IAudioMixerPlatformInterface`  
_L10-59_
- inherits: `IAudioMixerPlatformInterface`
- L14 _public prototype_ `FAudioMixerPlatformAudioLink();`
- L15 _public prototype_ `virtual ~FAudioMixerPlatformAudioLink() = default;`
- L19 _protected function_ `FString GetPlatformApi() const override`
- L20 _protected prototype_ `bool InitializeHardware() override;`
- L21 _protected prototype_ `bool TeardownHardware() override;`
- L22 _protected prototype_ `bool IsInitialized() const override;`
- L23 _protected prototype_ `bool GetNumOutputDevices(uint32& OutNumOutputDevices) override;`
- L24 _protected prototype_ `bool GetOutputDeviceInfo(const uint32 InDeviceIndex, FAudioPlatformDeviceInfo& OutInfo) override;`
- L25 _protected prototype_ `bool GetDefaultOutputDeviceIndex(uint32& OutDefaultDeviceIndex) const override;`
- L26 _protected prototype_ `virtual bool OpenAudioStream(const FAudioMixerOpenStreamParams& Params) override;`
- L27 _protected prototype_ `bool CloseAudioStream() override;`
- L28 _protected prototype_ `bool StartAudioStream() override;`
- L29 _protected prototype_ `bool StopAudioStream() override;`
- L30 _protected prototype_ `FAudioPlatformDeviceInfo GetPlatformDeviceInfo() const override;`
- L31 _protected prototype_ `FString GetDefaultDeviceName() override;`
- L32 _protected prototype_ `FAudioPlatformSettings GetPlatformSettings() const override;`
- L36 _private prototype_ `void MakeDeviceInfo(int32 InNumChannels, int32 InSampleRate, const FString& InName);`
- L38 _private prototype_ `void OnLinkOpenStream(const IAudioLinkSynchronizer::FOnOpenStreamParams&);`
- L39 _private prototype_ `void OnLinkRenderBegin(const IAudioLinkSynchronizer::FOnRenderParams&);`
- L40 _private prototype_ `void OnLinkRenderEnd(const IAudioLinkSynchronizer::FOnRenderParams&);`
- L42 _private prototype_ `IAudioLinkSynchronizer* GetOrCreateSynchronizer() const;`
- L44 _private member_ `bool bSuspended = false;`
- L45 _private member_ `bool bInitialized = false;`
- L48 _private member_ `std::atomic<bool> bAtomicStreamRunning;` — Atomic flag that's set by unreal, but read in callback from other host engines.
- L50 _private member_ `IAudioLinkFactory* Factory = nullptr;`
- L51 _private member_ `mutable IAudioLinkFactory::FAudioLinkSynchronizerSharedPtr SynchronizeLink;`
- L52 _private member_ `FAudioPlatformDeviceInfo DeviceInfo;`
- L53 _private member_ `uint32 LastBufferTickID = 0;`
- L54 _private member_ `int32 FrameRemainder = 0;`
- L56 _private member_ `FDelegateHandle OpenStreamHandle;`
- L57 _private member_ `FDelegateHandle RenderBeginHandle;`
- L58 _private member_ `FDelegateHandle RenderEndHandle;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
