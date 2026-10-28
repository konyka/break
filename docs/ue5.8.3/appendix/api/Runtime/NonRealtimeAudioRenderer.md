# Runtime / NonRealtimeAudioRenderer

- module root: `Source/Runtime/NonRealtimeAudioRenderer`
- headers: 1; symbols: 38
- symbol kinds: class=1, function=1, member=8, namespace=1, prototype=27
- PrivateDependencyModuleNames: AudioMixer, AudioMixerCore, Core, CoreUObject, Engine, SignalProcessing
- PrivateIncludePathModuleNames: TargetPlatform
- PublicIncludePathModuleNames: AudioMixer

### `Source/Runtime/NonRealtimeAudioRenderer/Public/AudioMixerPlatformNonRealtime.h` (Public)


#### class `Audio::FMixerPlatformNonRealtime`  
`class FMixerPlatformNonRealtime : public IAudioMixerPlatformInterface`  
_L11-70_
- inherits: `IAudioMixerPlatformInterface`
- L16 _public prototype_ `FMixerPlatformNonRealtime(float InSampleRate = 48000, float InNumChannels = 2);`
- L17 _public prototype_ `~FMixerPlatformNonRealtime();`
- L19 _public prototype_ `void RenderAudio(double NumSecondsToRender);`
- L20 _public prototype_ `void OpenFileToWriteAudioTo(const FString& OutPath);`
- L21 _public prototype_ `void CloseFile();`
- L24 _public function_ `virtual FString GetPlatformApi() const override`
- L25 _public prototype_ `virtual bool InitializeHardware() override;`
- L26 _public prototype_ `virtual bool CheckAudioDeviceChange() override;`
- L27 _public prototype_ `virtual bool TeardownHardware() override;`
- L28 _public prototype_ `virtual bool IsInitialized() const override;`
- L29 _public prototype_ `virtual bool GetNumOutputDevices(uint32& OutNumOutputDevices) override;`
- L30 _public prototype_ `virtual bool GetOutputDeviceInfo(const uint32 InDeviceIndex, FAudioPlatformDeviceInfo& OutInfo) override;`
- L31 _public prototype_ `virtual bool GetDefaultOutputDeviceIndex(uint32& OutDefaultDeviceIndex) const override;`
- L32 _public prototype_ `virtual bool OpenAudioStream(const FAudioMixerOpenStreamParams& Params) override;`
- L33 _public prototype_ `virtual bool CloseAudioStream() override;`
- L34 _public prototype_ `virtual bool StartAudioStream() override;`
- L35 _public prototype_ `virtual bool StopAudioStream() override;`
- L36 _public prototype_ `virtual bool MoveAudioStreamToNewAudioDevice(const FString& InNewDeviceId) override;`
- L37 _public prototype_ `virtual void ResumePlaybackOnNewDevice() override;`
- L38 _public prototype_ `virtual FAudioPlatformDeviceInfo GetPlatformDeviceInfo() const override;`
- L39 _public prototype_ `virtual void SubmitBuffer(const uint8* Buffer) override;`
- L40 _public prototype_ `virtual FString GetDefaultDeviceName() override;`
- L41 _public prototype_ `virtual FAudioPlatformSettings GetPlatformSettings() const override;`
- L42 _public prototype_ `virtual void OnHardwareUpdate() override;`
- L43 _public prototype_ `virtual bool IsNonRealtime() const override;`
- L44 _public prototype_ `virtual void FadeOut() override;`
- L46 _public prototype_ `virtual void FadeIn() override;`
- L51 _private member_ `float SampleRate;`
- L52 _private member_ `int32 NumChannels;`
- L55 _private member_ `double TotalDurationRendered;` — How much audio time has actually been rendered? Incremented by RenderAudio at fixed precision.
- L57 _private member_ `double TotalDesiredRender;` — How much time does the user want to have rendered? This prevents drift over time where we render more audio on a given frame than asked.
- L60 _private member_ `double TickDelta;` — This is retrieved from the tick interval on InitializeHardware.
- L62 _private member_ `uint32 bIsInitialized : 1;`
- L63 _private member_ `uint32 bIsDeviceOpen : 1;`
- L65 _private member_ `TUniquePtr<FAudioFileWriter> AudioFileWriter;`
- L68 _protected prototype_ `virtual uint32 RunInternal() override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
