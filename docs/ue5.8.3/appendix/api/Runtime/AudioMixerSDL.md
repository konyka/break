# Runtime / AudioMixerSDL

- module root: `Source/Runtime/Linux/AudioMixerSDL`
- headers: 2; symbols: 37
- symbol kinds: class=1, function=6, member=8, namespace=2, prototype=19, typedef=1
- PrivateDependencyModuleNames: AudioMixer, AudioMixerCore, Core, CoreUObject, Engine
- PrivateIncludePathModuleNames: AudioMixer, TargetPlatform

### `Source/Runtime/Linux/AudioMixerSDL/Private/AudioMixerPlatformSDL.h` (Private)


#### class `Audio::FMixerPlatformSDL`  
`class FMixerPlatformSDL : public IAudioMixerPlatformInterface`  
_L15-65_
- inherits: `IAudioMixerPlatformInterface`
- L20 _public prototype_ `FMixerPlatformSDL();`
- L21 _public prototype_ `virtual ~FMixerPlatformSDL();`
- L24 _public function_ `FString GetPlatformApi() const override`
- L25 _public prototype_ `bool InitializeHardware() override;`
- L26 _public prototype_ `bool TeardownHardware() override;`
- L27 _public prototype_ `bool IsInitialized() const override;`
- L28 _public prototype_ `bool GetNumOutputDevices(uint32& OutNumOutputDevices) override;`
- L29 _public prototype_ `bool GetOutputDeviceInfo(const uint32 InDeviceIndex, FAudioPlatformDeviceInfo& OutInfo) override;`
- L30 _public prototype_ `bool GetDefaultOutputDeviceIndex(uint32& OutDefaultDeviceIndex) const override;`
- L31 _public prototype_ `virtual bool OpenAudioStream(const FAudioMixerOpenStreamParams& Params) override;`
- L32 _public prototype_ `bool CloseAudioStream() override;`
- L33 _public prototype_ `bool StartAudioStream() override;`
- L34 _public prototype_ `bool StopAudioStream() override;`
- L35 _public prototype_ `FAudioPlatformDeviceInfo GetPlatformDeviceInfo() const override;`
- L36 _public prototype_ `void SubmitBuffer(const uint8* Buffer) override;`
- L37 _public prototype_ `FString GetDefaultDeviceName() override;`
- L38 _public prototype_ `FAudioPlatformSettings GetPlatformSettings() const override;`
- L39 _public prototype_ `void ResumeContext() override;`
- L40 _public prototype_ `void SuspendContext() override;`
- L43 _public prototype_ `void HandleOnBufferEnd(uint8* InOutputBuffer, int32 InOutputBufferLength);`
- L45 _public function_ `SDL_AudioFormat GetPlatformAudioFormat()`
- L46 _public function_ `Uint8 GetPlatformChannels()`
- L47 _public function_ `EAudioMixerStreamDataFormat::Type GetAudioStreamFormat()`
- L48 _public function_ `int32 GetAudioStreamChannelSize()`
- L49 _public function_ `int32 GetOutputBufferByteLength()`
- L52 _protected member_ `FCriticalSection OutputBufferMutex;`
- L56 _private member_ `SDL_AudioDeviceID AudioDeviceID;`
- L57 _private member_ `SDL_AudioSpec AudioSpec;`
- L58 _private member_ `SDL_AudioStream *AudioStream;`
- L60 _private member_ `uint8* OutputBuffer;`
- L61 _private member_ `int32 OutputBufferByteLength;`
- L63 _private member_ `bool bSuspended;`
- L64 _private member_ `bool bInitialized;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`

### `Source/Runtime/Linux/AudioMixerSDL/Private/Linux/LinuxAudioMixerSDLDefines.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
- L9 _typedef_ `using FAudioMixerPlatformSDL = FMixerPlatformSDL;` (scope `Audio`)
