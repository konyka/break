# Runtime / AudioMixerAndroid

- module root: `Source/Runtime/Android/AudioMixerAndroid`
- headers: 1; symbols: 38
- symbol kinds: class=1, function=1, member=14, namespace=1, prototype=21
- PrivateDependencyModuleNames: AudioMixerCore, Core, Engine
- PrivateIncludePathModuleNames: TargetPlatform

### `Source/Runtime/Android/AudioMixerAndroid/Private/AudioMixerPlatformAndroid.h` (Private)


#### class `Audio::FMixerPlatformAndroid`  
`class FMixerPlatformAndroid : public IAudioMixerPlatformInterface`  
_L14-72_
- inherits: `IAudioMixerPlatformInterface`
- L19 _public prototype_ `FMixerPlatformAndroid();`
- L20 _public prototype_ `~FMixerPlatformAndroid();`
- L23 _public function_ `virtual FString GetPlatformApi() const override`
- L24 _public prototype_ `virtual bool InitializeHardware() override;`
- L25 _public prototype_ `virtual bool TeardownHardware() override;`
- L26 _public prototype_ `virtual bool IsInitialized() const override;`
- L27 _public prototype_ `virtual bool GetNumOutputDevices(uint32& OutNumOutputDevices) override;`
- L28 _public prototype_ `virtual bool GetOutputDeviceInfo(const uint32 InDeviceIndex, FAudioPlatformDeviceInfo& OutInfo) override;`
- L29 _public prototype_ `virtual bool GetDefaultOutputDeviceIndex(uint32& OutDefaultDeviceIndex) const override;`
- L30 _public prototype_ `virtual bool OpenAudioStream(const FAudioMixerOpenStreamParams& Params) override;`
- L31 _public prototype_ `virtual bool CloseAudioStream() override;`
- L32 _public prototype_ `virtual bool StartAudioStream() override;`
- L33 _public prototype_ `virtual bool StopAudioStream() override;`
- L34 _public prototype_ `virtual FAudioPlatformDeviceInfo GetPlatformDeviceInfo() const override;`
- L35 _public prototype_ `virtual void SubmitBuffer(const uint8* Buffer) override;`
- L36 _public prototype_ `virtual FString GetDefaultDeviceName() override;`
- L37 _public prototype_ `virtual FAudioPlatformSettings GetPlatformSettings() const override;`
- L38 _public prototype_ `virtual void SuspendContext() override;`
- L39 _public prototype_ `virtual void ResumeContext() override;`
- L44 _private prototype_ `const TCHAR* GetErrorString(SLresult Result);`
- L46 _private prototype_ `int32 GetDeviceBufferSize(int32 RenderCallbackSize) const;`
- L48 _private member_ `SLObjectItf SL_EngineObject;`
- L49 _private member_ `SLEngineItf SL_EngineEngine;`
- L50 _private member_ `SLObjectItf SL_OutputMixObject;`
- L51 _private member_ `SLObjectItf SL_PlayerObject;`
- L52 _private member_ `SLPlayItf SL_PlayerPlayInterface;`
- L53 _private member_ `SLAndroidSimpleBufferQueueItf SL_PlayerBufferQueue;`
- L55 _private member_ `FCriticalSection SuspendedCriticalSection;`
- L57 _private member_ `bool bSuspended;`
- L58 _private member_ `bool bInitialized;`
- L59 _private member_ `bool bInCallback;`
- L63 _private member_ `Audio::TCircularAudioBuffer<int16> CircularOutputBuffer;` — This buffer is pushed to and popped from in the SubmitBuffer callback. This is required for devices that require frame counts per callback that are not powers of two.
- L66 _private member_ `TArray<int16> DeviceBuffer;` — This is the buffer we pop CircularOutputBuffer into in SubmitBuffer.
- L68 _private member_ `int32 NumSamplesPerRenderCallback;`
- L69 _private member_ `int32 NumSamplesPerDeviceCallback;`
- L71 _private prototype_ `static void OpenSLBufferQueueCallback( SLAndroidSimpleBufferQueueItf InQueueInterface, void* pContext );`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Audio`
