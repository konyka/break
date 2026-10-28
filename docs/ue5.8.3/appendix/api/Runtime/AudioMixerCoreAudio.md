# Runtime / AudioMixerCoreAudio

- module root: `Source/Runtime/Apple/AudioMixerCoreAudio`
- headers: 1; symbols: 39
- symbol kinds: class=1, function=1, member=12, namespace=1, prototype=24
- PrivateDependencyModuleNames: AudioMixerCore, Core, CoreUObject, Engine
- PrivateIncludePathModuleNames: AudioMixer, TargetPlatform

### `Source/Runtime/Apple/AudioMixerCoreAudio/Private/AudioMixerPlatformCoreAudio.h` (Private)


#### class `Audio::FMixerPlatformCoreAudio`  
`class FMixerPlatformCoreAudio : public IAudioMixerPlatformInterface`  
_L15-74_
- inherits: `IAudioMixerPlatformInterface`
- L20 _public prototype_ `FMixerPlatformCoreAudio();`
- L21 _public prototype_ `~FMixerPlatformCoreAudio();`
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
- L37 _public prototype_ `virtual FAudioPlatformDeviceInfo GetPlatformDeviceInfo() const override;`
- L38 _public prototype_ `virtual void SubmitBuffer(const uint8* Buffer) override;`
- L39 _public prototype_ `virtual FString GetDefaultDeviceName() override;`
- L40 _public prototype_ `virtual FAudioPlatformSettings GetPlatformSettings() const override;`
- L41 _public prototype_ `virtual int32 GetNumFrames(const int32 InNumReqestedFrames) override;`
- L42 _public prototype_ `virtual void ResumeContext() override;`
- L43 _public prototype_ `virtual void SuspendContext() override;`
- L47 _private member_ `AudioStreamBasicDescription OutputFormat;`
- L49 _private member_ `bool bSuspended;`
- L52 _private member_ `bool bInitialized;` — True if the connection to the device has been initialized
- L55 _private member_ `bool bInCallback;` — True if execution is in the callback
- L57 _private member_ `AUGraph AudioUnitGraph;`
- L58 _private member_ `AUNode OutputNode;`
- L59 _private member_ `AudioUnit OutputUnit;`
- L60 _private member_ `uint8* SubmittedBufferPtr;`
- L61 _private member_ `int32 SubmittedBytes = 0;`
- L63 _private member_ `int32 RemainingBytesInCurrentSubmittedBuffer;`
- L64 _private member_ `int32 BytesPerSubmittedBuffer;`
- L66 _private member_ `double GraphSampleRate;`
- L68 _private prototype_ `bool PerformCallback(AudioBufferList* OutputBufferData);`
- L69 _private prototype_ `void HandleError(const TCHAR* InLogOutput, bool bTeardown = true);`
- L70 _private prototype_ `static OSStatus AudioRenderCallback(void* RefCon, AudioUnitRenderActionFlags* ActionFlags, const AudioTimeStamp* TimeStamp, UInt32 BusNumber, UInt32 NumFrames, AudioBufferList* IOData);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`
