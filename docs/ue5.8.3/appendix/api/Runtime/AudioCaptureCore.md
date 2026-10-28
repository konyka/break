# Runtime / AudioCaptureCore

- module root: `Source/Runtime/AudioCaptureCore`
- headers: 5; symbols: 120
- symbol kinds: class=6, enum=2, enumerator=11, function=23, macro=1, member=18, namespace=3, prototype=48, struct=2, typedef=2, variable=4
- PrivateDependencyModuleNames: Engine
- PublicDependencyModuleNames: Core, SignalProcessing

### `Source/Runtime/AudioCaptureCore/Private/AudioCaptureInternal.h` (Private)


#### class `Audio::FNullAudioCaptureDevice`  
`class FNullAudioCaptureDevice : public IAudioCaptureStream`  
_L13-32_
- inherits: `IAudioCaptureStream`
- desc: Null implementation for compiler
- L16 _public function_ `FNullAudioCaptureDevice()`
- L19 _public function_ `virtual bool GetCaptureDeviceInfo(FCaptureDeviceInfo& OutInfo, int32 DeviceIndex) override`
- L20 _public function_ `virtual bool OpenAudioCaptureStream(const FAudioCaptureDeviceParams& InParams, FOnAudioCaptureFunction OnCapture, uint32 NumFramesDesired) override`
- L21 _public function_ `virtual bool CloseStream() override`
- L22 _public function_ `virtual bool StartStream() override`
- L23 _public function_ `virtual bool StopStream() override`
- L24 _public function_ `virtual bool AbortStream() override`
- L25 _public function_ `virtual bool GetStreamTime(double& OutStreamTime) override`
- L26 _public function_ `virtual int32 GetSampleRate() const override`
- L27 _public function_ `virtual bool IsStreamOpen() const override`
- L28 _public function_ `virtual bool IsCapturing() const override`
- L29 _public function_ `virtual void OnAudioCapture(void* InBuffer, uint32 InBufferFrames, double StreamTime, bool bOverflow) override`
- L30 _public function_ `virtual bool GetInputDevicesAvailable(TArray<FCaptureDeviceInfo>& OutDevices) override`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`
- L34 _function_ `FORCEINLINE TUniquePtr<IAudioCaptureStream> FAudioCapture::CreateImpl()` (scope `Audio::FAudioCapture`)

### `Source/Runtime/AudioCaptureCore/Public/AudioCaptureCore.h` (Public)


#### enum `Audio::EHardwareInputFeature`  
`enum class EHardwareInputFeature : uint8`  
_L20-25_
- desc: Various hardware-accelerated features that an input device can have.
- L22 _public enumerator_ `EchoCancellation`
- L23 _public enumerator_ `NoiseSuppression`
- L24 _public enumerator_ `AutomaticGainControl`

#### class `Audio::FAudioCapture`  
`class FAudioCapture`  
_L28-88_
- desc: Class which handles audio capture internally, implemented with a back-end per platform
- L32 _public prototype_ `FAudioCapture();`
- L33 _public prototype_ `~FAudioCapture();`
- L36 _public prototype_ `int32 GetCaptureDevicesAvailable(TArray<FCaptureDeviceInfo>& OutDevices);` — Returns the total amount of audio devices.
- L39 _public prototype_ `bool RegisterUser(const TCHAR* UserId);` — Adds a user to the system so we can use its devices.
- L42 _public prototype_ `bool UnregisterUser(const TCHAR* UserId);` — Removes a user added with RegisterUser.
- L45 _public prototype_ `bool GetCaptureDeviceInfo(FCaptureDeviceInfo& OutInfo, int32 DeviceIndex = INDEX_NONE);` — Returns the audio capture device information at the given Id.
- L50 _public prototype_ `bool OpenCaptureStream(const FAudioCaptureDeviceParams& InParams, FOnCaptureFunction OnCapture, uint32 NumFramesDesired);` — `UE_DEPRECATED(5.3, "OpenCaptureStream is deprecated, please use OpenAudioCaptureStream instead.")` — Opens the audio capture stream with the given parameters
- L54 _public prototype_ `bool OpenAudioCaptureStream(const FAudioCaptureDeviceParams& InParams, FOnAudioCaptureFunction OnCapture, uint32 NumFramesDesired);` — Opens the audio capture stream with the given parameters
- L57 _public prototype_ `bool CloseStream();` — Closes the audio capture stream
- L60 _public prototype_ `bool StartStream();` — Start the audio capture stream
- L63 _public prototype_ `bool StopStream();` — Stop the audio capture stream
- L66 _public prototype_ `bool AbortStream();` — Abort the audio capture stream (stop and close)
- L69 _public prototype_ `bool GetStreamTime(double& OutStreamTime) const;` — Get the stream time of the audio capture stream
- L72 _public prototype_ `int32 GetSampleRate() const;` — Get the sample rate in use by the stream.
- L75 _public prototype_ `bool IsStreamOpen() const;` — Returns if the audio capture stream has been opened.
- L78 _public prototype_ `bool IsCapturing() const;` — Returns true if the audio capture stream is currently capturing audio
- L80 _public prototype_ `bool GetIfHardwareFeatureIsSupported(EHardwareInputFeature FeatureType);`
- L82 _public prototype_ `void SetHardwareFeatureEnabled(EHardwareInputFeature FeatureType, bool bIsEnabled);`
- L86 _private prototype_ `TUniquePtr<IAudioCaptureStream> CreateImpl();`
- L87 _private member_ `TUniquePtr<IAudioCaptureStream> Impl;`

#### class `Audio::FAudioCaptureSynth`  
`class FAudioCaptureSynth`  
_L91-148_
- desc: Class which contains an FAudioCapture object and performs analysis on the audio stream, only outputing audio if it matches a detection criteria.
- L94 _public prototype_ `FAudioCaptureSynth();`
- L95 _public prototype_ `virtual ~FAudioCaptureSynth();`
- L98 _public prototype_ `bool GetDefaultCaptureDeviceInfo(FCaptureDeviceInfo& OutInfo);` — Gets the default capture device info
- L101 _public prototype_ `bool OpenDefaultStream();` — Opens up a stream to the default capture device
- L104 _public prototype_ `bool StartCapturing();` — Starts capturing audio
- L107 _public prototype_ `void StopCapturing();` — Stops capturing audio
- L110 _public prototype_ `void AbortCapturing();` — Immediately stop capturing audio
- L113 _public prototype_ `bool IsStreamOpen() const;` — Returned if the capture synth is closed
- L116 _public prototype_ `bool IsCapturing() const;` — Returns true if the capture synth is capturing audio
- L120 _public prototype_ `bool GetAudioData(TArray<float>& OutAudioData);` — Retrieves audio data from the capture synth. This returns audio only if there was non-zero audio since this function was last called.
- L123 _public prototype_ `int32 GetNumSamplesEnqueued();` — Returns the number of samples enqueued in the capture synth
- L128 _private member_ `int32 NumSamplesEnqueued;` — Number of samples enqueued
- L131 _private member_ `FCaptureDeviceInfo CaptureInfo;` — Information about the default capture device we're going to use
- L134 _private member_ `FAudioCapture AudioCapture;` — Audio capture object dealing with getting audio callbacks
- L137 _private member_ `FCriticalSection CaptureCriticalSection;` — Critical section to prevent reading and writing from the captured buffer at the same time
- L140 _private member_ `TArray<float> AudioCaptureData;` — Buffer of audio capture data, yet to be copied to the output
- L144 _private member_ `bool bInitialized;` — If the object has been initialized
- L147 _private member_ `bool bIsCapturing;` — If we're capturing data

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AUDIOCAPTURECORE_API`
- L17 _namespace_ `namespace Audio`

### `Source/Runtime/AudioCaptureCore/Public/AudioCaptureCoreLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioCaptureCore, Log, All);`

### `Source/Runtime/AudioCaptureCore/Public/AudioCaptureCoreModule.h` (Public)


#### class `FAudioCaptureCoreModule`  
`class FAudioCaptureCoreModule : public IModuleInterface`  
_L13-18_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Runtime/AudioCaptureCore/Public/AudioCaptureDeviceInterface.h` (Public)


#### enum `Audio::EPCMAudioEncoding`  
`enum class EPCMAudioEncoding : uint8`  
_L15-25_
- desc: PCM audio format (bits per sample) supported by device layers (WASAPI, CoreAudio, etc.)
- L17 _public enumerator_ `UNKNOWN`
- L18 _public enumerator_ `PCM_8`
- L19 _public enumerator_ `PCM_16`
- L20 _public enumerator_ `PCM_24`
- L21 _public enumerator_ `PCM_24_IN_32`
- L22 _public enumerator_ `PCM_32`
- L23 _public enumerator_ `FLOATING_POINT_32`
- L24 _public enumerator_ `FLOATING_POINT_64`

#### struct `Audio::FCaptureDeviceInfo`  
`struct FCaptureDeviceInfo`  
_L27-34_
- L29 _public member_ `FString DeviceName;`
- L30 _public member_ `FString DeviceId;`
- L31 _public member_ `int32 InputChannels;`
- L32 _public member_ `int32 PreferredSampleRate;`
- L33 _public member_ `bool bSupportsHardwareAEC;`

#### struct `Audio::FAudioCaptureDeviceParams`  
`struct FAudioCaptureDeviceParams`  
_L45-57_
- L48 _public member_ `bool bUseHardwareAEC = false;` — Set to true to use this device's built-in echo cancellation, if possible.
- L50 _public member_ `int32 DeviceIndex = DefaultDeviceIndex;` — Set this to INDEX_NONE
- L52 _public member_ `int32 NumInputChannels = InvalidDeviceChannelCount;` — Number of input channels on the device available for recording audio
- L54 _public member_ `int32 SampleRate = InvalidDeviceSampleRate;` — The sample rate to use when recording audio on this device
- L56 _public member_ `EPCMAudioEncoding PCMAudioEncoding = DefaultDeviceEncoding;` — The bit depth to use when recording audio on this device

#### class `Audio::IAudioCaptureStream`  
`class IAudioCaptureStream : public IModularFeature`  
_L64-123_
- inherits: `IModularFeature`
- L67 _public function_ `IAudioCaptureStream()`
- L68 _public prototype_ `virtual ~IAudioCaptureStream() = default;`
- L72 _public function_ `virtual bool RegisterUser(const TCHAR* UserId)` — Lets us know which users are in the system.
- L74 _public function_ `virtual bool UnregisterUser(const TCHAR* UserId)` — Call this to remove a user that was added with RegisterUser.
- L76 _public prototype_ `virtual bool GetCaptureDeviceInfo(FCaptureDeviceInfo& OutInfo, int32 DeviceIndex) = 0;` — Returns the audio capture device information at the given Id.
- L80 _public function_ `virtual bool OpenCaptureStream(const FAudioCaptureDeviceParams& InParams, FOnCaptureFunction InOnCapture, uint32 NumFramesDesired)` — `UE_DEPRECATED(5.3, "OpenCaptureStream is deprecated, please use OpenAudioCaptureStream instead.")` — Opens the audio capture stream with the given parameters
- L91 _public prototype_ `virtual bool OpenAudioCaptureStream(const FAudioCaptureDeviceParams& InParams, FOnAudioCaptureFunction InOnCapture, uint32 NumFramesDesired) = 0;` — Opens the audio capture stream with the given parameters and using FOnAudioCaptureFunction for callbacks
- L93 _public prototype_ `virtual bool CloseStream() = 0;` — Closes the audio capture stream
- L95 _public prototype_ `virtual bool StartStream() = 0;` — Start the audio capture stream
- L97 _public prototype_ `virtual bool StopStream() = 0;` — Stop the audio capture stream
- L99 _public prototype_ `virtual bool AbortStream() = 0;` — Abort the audio capture stream (stop and close)
- L101 _public prototype_ `virtual bool GetStreamTime(double& OutStreamTime) = 0;` — Get the stream time of the audio capture stream
- L103 _public prototype_ `virtual int32 GetSampleRate() const = 0;` — Get the sample rate in use by the stream.
- L105 _public prototype_ `virtual bool IsStreamOpen() const = 0;` — Returns if the audio capture stream has been opened.
- L107 _public prototype_ `virtual bool IsCapturing() const = 0;` — Returns true if the audio capture stream is currently capturing audio.
- L110 _public prototype_ `virtual void OnAudioCapture(void* InBuffer, uint32 InBufferFrames, double StreamTime, bool bOverflow) = 0;` — This is the callback for querying audio from the input device.
- L113 _public prototype_ `virtual bool GetInputDevicesAvailable(TArray<FCaptureDeviceInfo>& OutDevices) = 0;` — Returns the total amount of audio devices.
- L115 _public function_ `virtual bool GetIfHardwareFeatureIsSupported(EHardwareInputFeature FeatureType)`
- L120 _public function_ `virtual void SetHardwareFeatureEnabled(EHardwareInputFeature FeatureType, bool bEnabled)`

#### class `Audio::IAudioCaptureFactory`  
`class IAudioCaptureFactory : public IModularFeature`  
_L125-139_
- inherits: `IModularFeature`
- L128 _public function_ `IAudioCaptureFactory()`
- L129 _public prototype_ `virtual ~IAudioCaptureFactory() = default;`
- L132 _public function_ `static FName GetModularFeatureName()` — IModularFeature name. Use this to register an implementation of IAudioCaptureDevice.
- L138 _public prototype_ `virtual TUniquePtr<IAudioCaptureStream> CreateNewAudioCaptureStream() = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L37 _variable_ `constexpr int32 DefaultDeviceIndex = INDEX_NONE;` (scope `Audio`) — Indicates the default, system capture device should be used for capturing audio
- L39 _variable_ `constexpr int32 InvalidDeviceSampleRate = -1;` (scope `Audio`) — Indicates invalid sample rate and that the default device's sample rate should be used
- L41 _variable_ `constexpr int32 InvalidDeviceChannelCount = -1;` (scope `Audio`) — Indicates invalid channel count and that the input channel count of the default device should be used
- L43 _variable_ `constexpr EPCMAudioEncoding DefaultDeviceEncoding = EPCMAudioEncoding::FLOATING_POINT_32;` (scope `Audio`) — Some clients such as UAudioCaptureComponent assume 32-bit float bit depth
- L60 _typedef_ `typedef TFunction<void(const float* InAudio, int32 NumFrames, int32 NumChannels, int32 SampleRate, double StreamTime, bool bOverFlow)> FOnCaptureFunction;` (scope `Audio`) — `UE_DEPRECATED(5.3, "FOnCaptureFunction is deprecated, please use FOnAudioCaptureFunction instead.")`
- L62 _typedef_ `typedef TFunction<void(const void* InAudio, int32 NumFrames, int32 NumChannels, int32 SampleRate, double StreamTime, bool bOverFlow)> FOnAudioCaptureFunction;` (scope `Audio`) — Callable function type used for audio capture callbacks.
- L83 _function_ `` (scope `Audio::IAudioCaptureStream::OpenCaptureStream`)
