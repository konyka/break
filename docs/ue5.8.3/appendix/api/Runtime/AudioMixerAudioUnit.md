# Runtime / AudioMixerAudioUnit

- module root: `Source/Runtime/Apple/AudioMixerAudioUnit`
- headers: 2; symbols: 52
- symbol kinds: class=1, function=1, member=18, namespace=2, prototype=30
- PrivateDependencyModuleNames: AudioMixerCore, Core, CoreUObject, Engine
- PrivateIncludePathModuleNames: TargetPlatform

### `Source/Runtime/Apple/AudioMixerAudioUnit/Private/AudioMixerPlatformAudioUnit.h` (Private)


#### class `Audio::FMixerPlatformAudioUnit`  
`class FMixerPlatformAudioUnit : public IAudioMixerPlatformInterface`  
_L14-94_
- inherits: `IAudioMixerPlatformInterface`
- L19 _public prototype_ `FMixerPlatformAudioUnit();`
- L20 _public prototype_ `~FMixerPlatformAudioUnit();`
- L23 _public function_ `virtual FString GetPlatformApi() const override`
- L24 _public prototype_ `virtual bool InitializeHardware() override;`
- L25 _public prototype_ `virtual bool CheckAudioDeviceChange() override;`
- L26 _public prototype_ `virtual bool TeardownHardware() override;`
- L27 _public prototype_ `virtual bool IsInitialized() const override;`
- L28 _public prototype_ `virtual bool GetNumOutputDevices(uint32& OutNumOutputDevices) override;`
- L29 _public prototype_ `virtual bool GetOutputDeviceInfo(const uint32 InDeviceIndex, FAudioPlatformDeviceInfo& OutInfo) override;`
- L30 _public prototype_ `virtual bool GetDefaultOutputDeviceIndex(uint32& OutDefaultDeviceIndex) const override;`
- L31 _public prototype_ `virtual bool OpenAudioStream(const FAudioMixerOpenStreamParams& Params) override;`
- L32 _public prototype_ `virtual bool CloseAudioStream() override;`
- L33 _public prototype_ `virtual bool StartAudioStream() override;`
- L34 _public prototype_ `virtual bool StopAudioStream() override;`
- L35 _public prototype_ `virtual bool MoveAudioStreamToNewAudioDevice(const FString& InNewDeviceId) override;`
- L36 _public prototype_ `virtual FAudioPlatformDeviceInfo GetPlatformDeviceInfo() const override;`
- L37 _public prototype_ `virtual void SubmitBuffer(const uint8* Buffer) override;`
- L38 _public prototype_ `virtual FString GetDefaultDeviceName() override;`
- L39 _public prototype_ `virtual FAudioPlatformSettings GetPlatformSettings() const override;`
- L40 _public prototype_ `virtual int32 GetNumFrames(const int32 InNumReqestedFrames) override;`
- L41 _public prototype_ `virtual void ResumeContext() override;`
- L42 _public prototype_ `virtual void SuspendContext() override;`
- L46 _public prototype_ `static void IncrementSuspendCounter();`
- L47 _public prototype_ `static void DecrementSuspendCounter();`
- L50 _private member_ `AudioStreamBasicDescription OutputFormat;`
- L52 _private member_ `bool bSuspended;`
- L55 _private member_ `bool bInitialized;` — True if the connection to the device has been initialized
- L58 _private member_ `bool bInCallback;` — True if execution is in the callback
- L60 _private member_ `AUGraph AudioUnitGraph;`
- L61 _private member_ `AUNode OutputNode;`
- L62 _private member_ `AudioUnit OutputUnit;`
- L63 _private member_ `uint8* SubmittedBufferPtr;`
- L64 _private member_ `int32 SubmittedBytes = 0;`
- L66 _private member_ `int32 RemainingBytesInCurrentSubmittedBuffer;`
- L67 _private member_ `int32 BytesPerSubmittedBuffer;`
- L69 _private member_ `double GraphSampleRate;`
- L71 _private member_ `bool bSupportsBackgroundAudio;`
- L75 _private prototype_ `void GrowCircularBufferIfNeeded(const int32 InNumSamplesPerRenderCallback, const int32 InNumSamplesPerDeviceCallback);` — We may have to grow the circular buffer capacity since Audio Unit callback size is not guaranteed to be constant Currently, this just zero's-out and reallocates, so it will pop. (We always keep largest capacity)
- L79 _private member_ `Audio::TCircularAudioBuffer<int8> CircularOutputBuffer;` — This buffer is pushed to and popped from in the SubmitBuffer callback. This is required for devices that require frame counts per callback that are not powers of two.
- L81 _private member_ `int32 NumSamplesPerRenderCallback;`
- L82 _private member_ `int32 NumSamplesPerDeviceCallback;`
- L83 _private member_ `mutable bool bInternalPlatformSettingsInitialized{ false };`
- L84 _private member_ `mutable FAudioPlatformSettings InternalPlatformSettings;`
- L86 _private prototype_ `void InterruptContext(bool Interrupted);`
- L88 _private prototype_ `bool PerformCallback(AudioBufferList* OutputBufferData);`
- L89 _private prototype_ `void HandleError(const TCHAR* InLogOutput, bool bTeardown = true);`
- L90 _private prototype_ `static OSStatus AudioRenderCallback(void* RefCon, AudioUnitRenderActionFlags* ActionFlags, const AudioTimeStamp* TimeStamp, UInt32 BusNumber, UInt32 NumFrames, AudioBufferList* IOData);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Audio`

### `Source/Runtime/Apple/AudioMixerAudioUnit/Public/AudioMixerPlatformAudioUnitUtils.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace Audio`
- L7 _prototype_ `void IncrementIOSAudioMixerPlatformSuspendCounter();` (scope `Audio`)
- L8 _prototype_ `void DecrementIOSAudioMixerPlatformSuspendCounter();` (scope `Audio`)
