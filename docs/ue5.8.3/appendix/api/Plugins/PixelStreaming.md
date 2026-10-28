# Plugins / PixelStreaming

- module root: `Plugins/Media/PixelStreaming/Source/PixelStreaming`
- headers: 72; symbols: 1722
- symbol kinds: class=76, delegate=33, enum=6, enumerator=19, externvar=57, function=192, member=332, namespace=84, prototype=842, struct=10, typedef=12, variable=59
- PrivateDependencyModuleNames: AVCodecsCore, AVCodecsCoreRHI, AudioMixer, AudioPlatformConfiguration, Core, CoreUObject, D3D11RHI, D3D12RHI, DeveloperSettings, Engine, EngineSettings, HTTP, InputCore, Json, MediaUtils, NVML, PixelCaptureShaders, PixelStreamingHMD, PixelStreamingServers, RHI, RenderCore, Renderer, SignalProcessing, Slate, SlateCore, Sockets, TraceLog, UnrealEd, VulkanRHI, WebRTC, WebSockets
- PublicDependencyModuleNames: ApplicationCore, InputDevice, MediaIOCore, PixelCapture, PixelStreamingInput, WebRTC

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Internal/PixelStreamingCoderUtils.h` (Internal)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L31 _function_ `template <typename TCodec> inline bool IsEncoderSupported()` (scope `UE::PixelStreaming`) — As windows supports many RHIs and many codecs, we need to check at runtime if the current codec and RHI is compatible. To remove nested switch-cases, this function is templated to take a video encoder config of the target codec. eg: IsEncoderSupported<FVideoEncoderConfigH264>(); OR IsEncoderSupported<FVideoEncoderConfigAV1>(); OR ...
- L68 _function_ `template <typename TCodec> inline bool IsDecoderSupported()` (scope `UE::PixelStreaming`) — As windows supports many RHIs and many codecs, we need to check at runtime if the current codec and RHI is compatible. To remove nested switch-cases, this function is templated to take a video decoder config of the target codec. eg: IsDecoderSupported<FVideoDecoderConfigVP8>(); OR IsDecoderSupported<FVideoDecoderConfigAV1>(); OR ...

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Internal/PixelStreamingMediaIOCapture.h` (Internal)


#### class `UPixelStreamingMediaIOCapture`  
`class UPixelStreamingMediaIOCapture : public UMediaCapture`  
_L13-95_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaCapture`
- L22 _public prototype_ `virtual void OnRHIResourceCaptured_RenderingThread( FRHICommandListImmediate& RHICmdList, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture) override;` — GPU copy methods
- L28 _public prototype_ `virtual void OnRHIResourceCaptured_AnyThread( const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture) override;`
- L36 _public prototype_ `virtual void OnFrameCaptured_RenderingThread( const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, void* InBuffer, int32 Width, int32 Height, int32 BytesPerRow) override;` — CPU readback methods
- L47 _public prototype_ `virtual void OnCustomCapture_RenderingThread( FRDGBuilder& GraphBuilder, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FRDGTextureRef InSourceTexture, FRDGTextureRef OutputTexture, const FRHICopyTextureInfo& CopyInfo, FVector2D CropU, FVector2D CropV) override;` — Custom conversion operation for Mac
- L57 _public prototype_ `virtual bool InitializeCapture() override;`
- L58 _public prototype_ `virtual bool PostInitializeCaptureViewport(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L59 _public function_ `virtual bool ShouldCaptureRHIResource() const`
- L60 _public prototype_ `virtual void StopCaptureImpl(bool bAllowPendingFrameToBeProcess) override;`
- L61 _public prototype_ `virtual bool SupportsAnyThreadCapture() const override;`
- L63 _public prototype_ `virtual ETextureCreateFlags GetOutputTextureFlags() const override;` — We override the texture flags because on Mac we want the texture to have the CPU_Readback flag
- L64 _public prototype_ `virtual void WaitForGPU(FRHITexture* InRHITexture) override;`
- L67 _public function_ `TSharedPtr<FSceneViewport> GetViewport() const`
- L68 _public prototype_ `virtual void ViewportResized(FViewport* Viewport, uint32 ResizeCode);`
- L69 _public function_ `bool WasViewportResized() const`
- L70 _public function_ `void SetVideoInput(TSharedPtr<FPixelStreamingVideoInput> InVideoInput)`
- L71 _public function_ `TWeakPtr<FPixelStreamingVideoInput> GetVideoInput()`
- L73 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCaptureViewportInitialized);`
- L74 _public member_ `FOnCaptureViewportInitialized OnCaptureViewportInitialized;`
- L77 _private prototype_ `void HandleCapturedFrame(FTextureRHIRef InTexture);`
- L78 _private prototype_ `void UpdateCaptureResolution(int32 Width, int32 Height);`
- L81 _private member_ `TWeakPtr<FSceneViewport> SceneViewport;`
- L82 _private member_ `TWeakPtr<FPixelStreamingVideoInput> VideoInput;`
- L85 _private member_ `bool bViewportResized = false;` — We track whether the viewport has been resized since we created this capturer as resize means restart capturer.
- L88 _private member_ `TUniquePtr<FIntPoint> CaptureResolution;` — Tracks the captured resolution, we use this to determine if resize events contain a different resolution than what we previously captured.
- L91 _private member_ `bool bDoGPUCopy = true;` — Whether we want the UMediaCapture to read back to frame into cpu memory or not.
- L94 _private member_ `TStripedMap<32, uintptr_t, FGPUFenceRHIRef> Fences;` — Thread safe map of fences used to wait on to ensure the media capture conversion is complete

#### Free symbols / members of external scopes

- L73 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCaptureViewportInitialized);`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Internal/PixelStreamingVideoInputMediaCapture.h` (Internal)


#### class `UPixelStreamingMediaIOOutput`  
`class UPixelStreamingMediaIOOutput : public UMediaOutput`  
_L13-25_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaOutput`
- L18 _public function_ `virtual FIntPoint GetRequestedSize() const override`
- L19 _public function_ `virtual EPixelFormat GetRequestedPixelFormat() const override`
- L20 _public function_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override`
- L24 _private member_ `TObjectPtr<UPixelStreamingMediaIOCapture> MediaCapture = nullptr;` — `UPROPERTY(Transient)`

#### class `FPixelStreamingVideoInputMediaCapture`  
`class FPixelStreamingVideoInputMediaCapture : public FPixelStreamingVideoInputRHI, public TSharedFromThis<FPixelStreamingVideoInputMediaCapture>`  
_L30-69_
- inherits: `FPixelStreamingVideoInputRHI,TSharedFromThis<FPixelStreamingVideoInputMediaCapture>`
- desc: Use this if you want to send VCam output as video input.
- L38 _public prototype_ `static TSharedPtr<FPixelStreamingVideoInputMediaCapture> CreateActiveViewportCapture();` — @brief Creates a MediaIO capture of the active viewport and starts capturing as soon as possible. @return A video input backed by the created MediaIO capture that sends frames from the active viewport.
- L47 _public prototype_ `static TSharedPtr<FPixelStreamingVideoInputMediaCapture> Create(TObjectPtr<UPixelStreamingMediaIOCapture> MediaCapture);` — @brief Creates a video input where the user can specify their own MediaIO output and capture. This method does not does not configure or start capturing, this is left to the user. Use this constructor if you know how to configure the MediaIOCapture yourself or don't want to capture the active viewport. @param MediaCapture The custom MediaIOCapture that will pass its captured frames as video input. @return A video input backed by the passed in MediaIO capture.
- L49 _public prototype_ `FPixelStreamingVideoInputMediaCapture();`
- L50 _public prototype_ `FPixelStreamingVideoInputMediaCapture(TObjectPtr<UPixelStreamingMediaIOCapture> MediaCapture);`
- L51 _public prototype_ `virtual ~FPixelStreamingVideoInputMediaCapture();`
- L53 _public prototype_ `virtual FString ToString() override;`
- L57 _protected prototype_ `virtual TSharedPtr<FPixelCaptureCapturer> CreateCapturer(int32 FinalFormat, FIntPoint Resolution) override;`
- L58 _protected prototype_ `void StartActiveViewportCapture();`
- L59 _protected prototype_ `void LateStartActiveViewportCapture();`
- L62 _private prototype_ `void CreateDefaultActiveViewportMediaCapture();`
- L63 _private prototype_ `void OnCaptureActiveViewportStateChanged();`
- L66 _private member_ `TObjectPtr<UPixelStreamingMediaIOCapture> MediaCapture = nullptr;`
- L68 _private member_ `TOptional<FDelegateHandle> OnFrameEndDelegateHandle;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/AdaptedVideoTrackSource.h` (Private)


#### class `UE::PixelStreaming::FAdaptedVideoTrackSource`  
`class FAdaptedVideoTrackSource : public webrtc::Notifier<webrtc::VideoTrackSourceInterface>`  
_L29-101_
- inherits: `webrtc::Notifier<webrtc::VideoTrackSourceInterface>`
- desc: Base class for sources which needs video adaptation, e.g., video capture sources. Sinks must be added and removed on one and only one thread, while AdaptFrame and OnFrame may be called on any thread.
- L32 _public prototype_ `FAdaptedVideoTrackSource();`
- L36 _public prototype_ `void AddOrUpdateSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink, const rtc::VideoSinkWants& wants) override;` — Implements rtc::VideoSourceInterface.
- L38 _public prototype_ `void RemoveSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) override;`
- L40 _public function_ `virtual void AddRef() const override`
- L41 _public function_ `virtual rtc::RefCountReleaseStatus Release() const override`
- L54 _protected prototype_ `explicit FAdaptedVideoTrackSource(int required_alignment);` — Allows derived classes to initialize |video_adapter_| with a custom alignment.
- L58 _protected prototype_ `void OnFrame(const webrtc::VideoFrame& frame);` — Checks the apply_rotation() flag. If the frame needs rotation, and it is a plain memory frame, it is rotated. Subclasses producing native frames must handle apply_rotation() themselves.
- L63 _protected prototype_ `bool AdaptFrame(int width, int height, int64_t time_us, int* out_width, int* out_height, int* crop_width, int* crop_height, int* crop_x, int* crop_y);` — Reports the appropriate frame size after adaptation. Returns true if a frame is wanted. Returns false if there are no interested sinks, or if the VideoAdapter decides to drop the frame.
- L78 _protected prototype_ `bool apply_rotation();` — Returns the current value of the apply_rotation flag, derived from the VideoSinkWants of registered sinks. The value is derived from sinks' wants, in AddOrUpdateSink and RemoveSink. Beware that when using this method from a different thread, the value may become stale before it is used.
- L80 _protected function_ `cricket::VideoAdapter* video_adapter()`
- L83 _private member_ `mutable webrtc::webrtc_impl::RefCounter RefCount{ 0 };`
- L86 _private prototype_ `bool GetStats(Stats* stats) override;` — Part of VideoTrackSourceInterface.
- L88 _private prototype_ `void OnSinkWantsChanged(const rtc::VideoSinkWants& wants);`
- L91 _private function_ `bool SupportsEncodedOutput() const override` — Encoded sinks not implemented for AdaptedVideoTrackSource.
- L92 _private function_ `void GenerateKeyFrame() override`
- L93 _private function_ `void AddEncodedSink(rtc::VideoSinkInterface<webrtc::RecordableEncodedFrame>* sink) override`
- L94 _private function_ `void RemoveEncodedSink(rtc::VideoSinkInterface<webrtc::RecordableEncodedFrame>* sink) override`
- L96 _private member_ `cricket::VideoAdapter video_adapter_;`
- L97 _private member_ `webrtc::Mutex stats_mutex_;`
- L98 _private prototype_ `absl::optional<Stats> stats_ RTC_GUARDED_BY(stats_mutex_);`
- L100 _private member_ `rtc::VideoBroadcaster broadcaster_;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/AudioCapturer.h` (Private)


#### struct `UE::PixelStreaming::FAudioCapturerListener`  
`struct FAudioCapturerListener : public ISubmixBufferListener`  
_L14-22_
- inherits: `ISubmixBufferListener`
- L16 _public prototype_ `FAudioCapturerListener(FAudioCapturer& InParent);`
- L19 _public prototype_ `virtual void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 NumSamples, int32 NumChannels, const int32 SampleRate, double AudioClock) override;` — ISubmixBufferListener interface
- L21 _public member_ `FAudioCapturer* Parent = nullptr;`

#### class `UE::PixelStreaming::FAudioCapturer`  
`class FAudioCapturer : public webrtc::AudioDeviceModule`  
_L26-212_
- inherits: `webrtc::AudioDeviceModule`
- desc: This class is only used if -PixelStreamingWebRTCUseLegacyAudioDevice or related CVar are used. This class will likely be removed in the future once the new ADM is confirmed stable.
- L29 _public prototype_ `FAudioCapturer();`
- L34 _private prototype_ `void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 NumSamples, int32 NumChannels, const int32 SampleRate, double AudioClock);`
- L39 _private prototype_ `int32 ActiveAudioLayer(AudioLayer* audioLayer) const override;` — webrtc::AudioDeviceModule interface
- L40 _private prototype_ `int32 RegisterAudioCallback(webrtc::AudioTransport* audioCallback) override;`
- L43 _private prototype_ `int32 Init() override;` — Main initialization and termination
- L44 _private prototype_ `int32 Terminate() override;`
- L45 _private prototype_ `bool Initialized() const override;`
- L48 _private prototype_ `int16 PlayoutDevices() override;` — Device enumeration
- L49 _private prototype_ `int16 RecordingDevices() override;`
- L50 _private prototype_ `int32 PlayoutDeviceName(uint16 index, char name[webrtc::kAdmMaxDeviceNameSize], char guid[webrtc::kAdmMaxGuidSize]) override;`
- L51 _private prototype_ `int32 RecordingDeviceName(uint16 index, char name[webrtc::kAdmMaxDeviceNameSize], char guid[webrtc::kAdmMaxGuidSize]) override;`
- L54 _private prototype_ `int32 SetPlayoutDevice(uint16 index) override;` — Device selection
- L55 _private prototype_ `int32 SetPlayoutDevice(WindowsDeviceType device) override;`
- L56 _private prototype_ `int32 SetRecordingDevice(uint16 index) override;`
- L57 _private prototype_ `int32 SetRecordingDevice(WindowsDeviceType device) override;`
- L60 _private prototype_ `int32 PlayoutIsAvailable(bool* available) override;` — Audio transport initialization
- L61 _private prototype_ `int32 InitPlayout() override;`
- L62 _private prototype_ `bool PlayoutIsInitialized() const override;`
- L63 _private prototype_ `int32 RecordingIsAvailable(bool* available) override;`
- L64 _private prototype_ `int32 InitRecording() override;`
- L65 _private prototype_ `bool RecordingIsInitialized() const override;`
- L68 _private prototype_ `virtual int32 StartPlayout() override;` — Audio transport control
- L69 _private prototype_ `virtual int32 StopPlayout() override;`
- L70 _private prototype_ `virtual bool Playing() const override;`
- L71 _private prototype_ `virtual int32 StartRecording() override;`
- L72 _private prototype_ `virtual int32 StopRecording() override;`
- L73 _private prototype_ `virtual bool Recording() const override;`
- L76 _private prototype_ `virtual int32 InitSpeaker() override;` — Audio mixer initialization
- L77 _private prototype_ `virtual bool SpeakerIsInitialized() const override;`
- L78 _private prototype_ `virtual int32 InitMicrophone() override;`
- L79 _private prototype_ `virtual bool MicrophoneIsInitialized() const override;`
- L82 _private function_ `virtual int32 SpeakerVolumeIsAvailable(bool* available) override` — Speaker volume controls
- L86 _private function_ `virtual int32 SetSpeakerVolume(uint32 volume) override`
- L90 _private function_ `virtual int32 SpeakerVolume(uint32* volume) const override`
- L94 _private function_ `virtual int32 MaxSpeakerVolume(uint32* maxVolume) const override`
- L98 _private function_ `virtual int32 MinSpeakerVolume(uint32* minVolume) const override`
- L104 _private function_ `virtual int32 MicrophoneVolumeIsAvailable(bool* available) override` — Microphone volume controls
- L108 _private function_ `virtual int32 SetMicrophoneVolume(uint32 volume) override`
- L112 _private function_ `virtual int32 MicrophoneVolume(uint32* volume) const override`
- L116 _private function_ `virtual int32 MaxMicrophoneVolume(uint32* maxVolume) const override`
- L120 _private function_ `virtual int32 MinMicrophoneVolume(uint32* minVolume) const override`
- L126 _private function_ `virtual int32 SpeakerMuteIsAvailable(bool* available) override` — Speaker mute control
- L130 _private function_ `virtual int32 SetSpeakerMute(bool enable) override`
- L134 _private function_ `virtual int32 SpeakerMute(bool* enabled) const override`
- L140 _private function_ `virtual int32 MicrophoneMuteIsAvailable(bool* available) override` — Microphone mute control
- L144 _private function_ `virtual int32 SetMicrophoneMute(bool enable) override`
- L148 _private function_ `virtual int32 MicrophoneMute(bool* enabled) const override`
- L154 _private prototype_ `virtual int32 StereoPlayoutIsAvailable(bool* available) const override;` — Stereo support
- L155 _private prototype_ `virtual int32 SetStereoPlayout(bool enable) override;`
- L156 _private prototype_ `virtual int32 StereoPlayout(bool* enabled) const override;`
- L157 _private prototype_ `virtual int32 StereoRecordingIsAvailable(bool* available) const override;`
- L158 _private prototype_ `virtual int32 SetStereoRecording(bool enable) override;`
- L159 _private prototype_ `virtual int32 StereoRecording(bool* enabled) const override;`
- L162 _private function_ `virtual int32 PlayoutDelay(uint16* delayMS) const override` — Playout delay
- L168 _private function_ `virtual bool BuiltInAECIsAvailable() const override` — Only supported on Android.
- L172 _private function_ `virtual bool BuiltInAGCIsAvailable() const override`
- L176 _private function_ `virtual bool BuiltInNSIsAvailable() const override`
- L182 _private function_ `virtual int32 EnableBuiltInAEC(bool enable) override` — Enables the built-in audio effects. Only supported on Android.
- L186 _private function_ `virtual int32 EnableBuiltInAGC(bool enable) override`
- L190 _private function_ `virtual int32 EnableBuiltInNS(bool enable) override`
- L195 _private member_ `FThreadSafeBool bInitialized = false;`
- L196 _private member_ `TArray<int16> PCM16;`
- L198 _private member_ `TUniquePtr<webrtc::AudioDeviceBuffer> DeviceBuffer;`
- L199 _private member_ `FCriticalSection DeviceBufferCS;` — protects capturing audio and sending it to WebRTC from simultaneous termination
- L201 _private member_ `TArray<uint8_t> RecordingBuffer;`
- L202 _private member_ `int RecordingBufferSize = 0;`
- L204 _private member_ `FThreadSafeBool bRecordingInitialized = false;`
- L205 _private member_ `static constexpr int SampleRate = 48000;`
- L206 _private member_ `static constexpr int NumChannels = 2;`
- L208 _private member_ `bool bFormatChecked = false;`
- L210 _private member_ `std::unique_ptr<webrtc::TaskQueueFactory> m_taskQueueFactory;`
- L211 _private member_ `TSharedPtr<FAudioCapturerListener, ESPMode::ThreadSafe> Listener;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/AudioInputMixer.h` (Private)


#### struct `UE::PixelStreaming::FMixers`  
`struct FMixers`  
_L21-29_
- L23 _public member_ `uint8 NumChannels = 2;`
- L24 _public member_ `uint32 SampleRate = 48000;`
- L25 _public member_ `float SampleSizeSeconds = 0.5f;`
- L26 _public member_ `uint32_t VolumeLevel = 14392;` — This magic number is a default from WebRTC
- L27 _public member_ `Audio::FPatchMixer Mixer;`
- L28 _public function_ `uint32 GetMaxBufferSize() const`

#### class `UE::PixelStreaming::FMixerRunnable`  
`class FMixerRunnable : public FRunnable, public FSingleThreadRunnable`  
_L34-54_
- inherits: `FRunnable,FSingleThreadRunnable`
- desc: Polls mixers for audio and passes it to the WebRTC callback on a fixed interval.
- L37 _public prototype_ `FMixerRunnable(webrtc::AudioTransport* InAudioCallback, TSharedPtr<FMixers> InMixers);`
- L38 _public prototype_ `virtual ~FMixerRunnable() = default;`
- L41 _public prototype_ `virtual bool Init() override;`
- L42 _public prototype_ `virtual uint32 Run() override;`
- L43 _public prototype_ `virtual void Stop() override;`
- L44 _public prototype_ `virtual void Exit() override;`
- L45 _public prototype_ `virtual void Tick() override;`
- L46 _public function_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override`
- L50 _private member_ `bool bIsRunning;`
- L51 _private member_ `webrtc::AudioTransport* AudioCallback;`
- L52 _private member_ `TSharedPtr<FMixers> Mixers;`
- L53 _private member_ `Audio::VectorOps::FAlignedFloatBuffer MixingBuffer;`

#### class `UE::PixelStreaming::FAudioInput`  
`class FAudioInput : public IPixelStreamingAudioInput`  
_L60-76_
- inherits: `IPixelStreamingAudioInput`
- desc: Allows pushing abitrary audio into Pixel Streaming, sample rate is assumed to be 48KHz. Note: All `PushAudio` methods should be called from the same single thread. Pushing from multiple threads is unsupported.
- L63 _public prototype_ `FAudioInput(class FAudioInputMixer& InMixer, int32 MaxSamples, float InGain);`
- L64 _public prototype_ `virtual ~FAudioInput() = default;`
- L67 _public prototype_ `void PushAudio(const float* InBuffer, int32 NumSamples, int32 NumChannels, int32 SampleRate) override;` — Pushes audio, which must match the underlying sample rate/num channels of the mixer.
- L69 _public function_ `const Audio::FPatchInput& GetPatchInput() const`
- L72 _private member_ `Audio::FResampler Resampler;`
- L73 _private member_ `Audio::FPatchInput PatchInput;`
- L74 _private member_ `uint8 NumChannels;`
- L75 _private member_ `uint32 SampleRate;`

#### class `UE::PixelStreaming::FAudioInputMixer`  
`class FAudioInputMixer`  
_L81-101_
- desc: Mixes audio from multiple inputs into stereo.
- L84 _public prototype_ `FAudioInputMixer();`
- L85 _public prototype_ `virtual ~FAudioInputMixer();`
- L86 _public prototype_ `TSharedPtr<FAudioInput> CreateInput();`
- L87 _public prototype_ `void DisconnectInput(TSharedPtr<FAudioInput> AudioInput);`
- L88 _public prototype_ `void RegisterAudioCallback(webrtc::AudioTransport* AudioCallback);`
- L89 _public prototype_ `void StartMixing();`
- L90 _public prototype_ `void StopMixing();`
- L93 _private member_ `TSharedPtr<FMixers> Mixers;`
- L94 _private member_ `bool bIsMixing;`
- L96 _private member_ `TUniquePtr<FRunnableThread> MixerThread;`
- L97 _private member_ `TUniquePtr<FMixerRunnable> Runnable;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace webrtc`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/AudioPlayoutRequester.h` (Private)


#### class `UE::PixelStreaming::FAudioPlayoutRequester`  
`class FAudioPlayoutRequester`  
_L23-69_
- desc: Requests audio from WebRTC at a regular interval (10ms) This is required so that WebRTC audio sinks actually have some audio data for their sinks. Without this WebRTC assumes there is no demand for audio and does not populate the sinks.
- L45 _public prototype_ `FAudioPlayoutRequester();`
- L46 _public prototype_ `virtual ~FAudioPlayoutRequester() = default;`
- L48 _public prototype_ `virtual void InitPlayout();`
- L49 _public prototype_ `virtual void StartPlayout();`
- L50 _public prototype_ `virtual void StopPlayout();`
- L51 _public prototype_ `virtual bool Playing() const;`
- L52 _public prototype_ `virtual bool PlayoutIsInitialized() const;`
- L53 _public prototype_ `virtual void Uninitialise();`
- L54 _public prototype_ `virtual void RegisterAudioCallback(webrtc::AudioTransport* AudioCallback);`
- L57 _public member_ `static int16_t const RequestIntervalMs = 10;`
- L60 _private member_ `FThreadSafeBool bIsPlayoutInitialised;`
- L61 _private member_ `FThreadSafeBool bIsPlaying;`
- L62 _private member_ `uint32 SampleRate;`
- L63 _private member_ `uint8 NumChannels;`
- L64 _private member_ `TUniquePtr<FAudioPlayoutRequester::Runnable> RequesterRunnable;`
- L65 _private member_ `TUniquePtr<FRunnableThread> RequesterThread;`
- L66 _private member_ `webrtc::AudioTransport* AudioCallback;`
- L67 _private member_ `FCriticalSection PlayoutCriticalSection;`
- L68 _private member_ `TArray<int16_t> PlayoutBuffer;`

#### class `UE::PixelStreaming::FAudioPlayoutRequester::Runnable`  
`class Runnable : public FRunnable`  
_L26-43_
- inherits: `FRunnable`
- L29 _public prototype_ `Runnable(TFunction<void()> RequestPlayoutFunc);`
- L30 _public prototype_ `virtual ~Runnable() = default;`
- L33 _public prototype_ `virtual bool Init() override;`
- L34 _public prototype_ `virtual uint32 Run() override;`
- L35 _public prototype_ `virtual void Stop() override;`
- L36 _public prototype_ `virtual void Exit() override;`
- L40 _private member_ `bool bIsRunning;`
- L41 _private member_ `int64_t LastAudioRequestTimeMs;`
- L42 _private member_ `TFunction<void()> RequestPlayoutFunc;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace webrtc`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/AudioSink.h` (Private)


#### class `UE::PixelStreaming::FAudioSink`  
`class FAudioSink : public IPixelStreamingAudioSink`  
_L13-37_
- inherits: `IPixelStreamingAudioSink`
- desc: This is a PixelStreaming sink AND a WebRTC sink. It collects audio coming in from a WebRTC audio source and passes into into UE's audio system.
- L16 _public function_ `FAudioSink() : AudioConsumers()`
- L20 _public prototype_ `virtual ~FAudioSink();` — Note: destructor will call destroy on any attached audio consumers
- L23 _public prototype_ `void OnData(const void* audio_data, int bits_per_sample, int sample_rate, size_t number_of_channels, size_t number_of_frames, absl::optional<int64_t> absolute_capture_timestamp_ms) override;`
- L27 _public prototype_ `void AddAudioConsumer(IPixelStreamingAudioConsumer* AudioConsumer) override;`
- L28 _public prototype_ `void RemoveAudioConsumer(IPixelStreamingAudioConsumer* AudioConsumer) override;`
- L29 _public prototype_ `bool HasAudioConsumers() override;`
- L33 _private prototype_ `void UpdateAudioSettings(int InNumChannels, int InSampleRate);`
- L36 _private member_ `TSet<IPixelStreamingAudioConsumer*> AudioConsumers;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/AudioSubmixCapturer.h` (Private)


#### class `UE::PixelStreaming::FAudioSubmixCapturer`  
`class FAudioSubmixCapturer : public ISubmixBufferListener`  
_L17-60_
- inherits: `ISubmixBufferListener`
- desc: Captures audio from UE and passes it along to WebRTC.
- L22 _public member_ `static const uint32_t MaxVolumeLevel = 14392;` — This magic number is the max volume used in webrtc fake audio device module.
- L24 _public prototype_ `FAudioSubmixCapturer();`
- L25 _public prototype_ `virtual ~FAudioSubmixCapturer() = default;`
- L27 _public prototype_ `bool Init();`
- L28 _public prototype_ `bool IsInitialised() const;`
- L29 _public prototype_ `bool IsCapturing() const;`
- L30 _public prototype_ `void Uninitialise();`
- L31 _public prototype_ `bool StartCapturing();`
- L32 _public prototype_ `bool EndCapturing();`
- L33 _public prototype_ `uint32_t GetVolume() const;`
- L34 _public prototype_ `void SetVolume(uint32_t NewVolume);`
- L35 _public prototype_ `void RegisterAudioCallback(webrtc::AudioTransport* AudioCb);`
- L36 _public prototype_ `void SetAudioInputMixerPatch(TSharedPtr<class FAudioInput> InPatchInput);`
- L39 _public prototype_ `const FString& GetListenerName() const override;` — ISubmixBufferListener interface
- L40 _public prototype_ `void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 NumSamples, int32 NumChannels, const int32 SampleRate, double AudioClock) override;`
- L45 _private prototype_ `int32 GetSamplesPerDurationSecs(float InSeconds) const;`
- L48 _private member_ `FThreadSafeBool bInitialised;`
- L49 _private member_ `FThreadSafeBool bCapturing;`
- L50 _private member_ `uint32 TargetSampleRate;`
- L51 _private member_ `uint8 TargetNumChannels;`
- L52 _private member_ `bool bReportedSampleRateMismatch;`
- L53 _private member_ `webrtc::AudioTransport* AudioCallback;`
- L54 _private member_ `uint32_t VolumeLevel;`
- L55 _private member_ `TArray<int16_t> RecordingBuffer;`
- L56 _private member_ `FCriticalSection CriticalSection;` — One thread captures audio from UE, the
- L59 _private member_ `TSharedPtr<class FAudioInput> AudioMixerPatchInput;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace webrtc`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/DebugGraph.h` (Private)


#### class `UE::PixelStreaming::FDebugGraph`  
`class FDebugGraph`  
_L10-38_
- L13 _public prototype_ `FDebugGraph(FName InName, int InSamples, float InMinRange, float InMaxRange, float InRefValue = 0.0f);`
- L14 _public prototype_ `FDebugGraph(const FDebugGraph& Other);`
- L15 _public prototype_ `~FDebugGraph() = default;`
- L17 _public prototype_ `void AddValue(float InValue);`
- L18 _public prototype_ `void Draw(FCanvas* Canvas, FVector2D Position, FVector2D Size) const;`
- L21 _private prototype_ `void AddValueInternal(float InValue);`
- L24 _private member_ `FName Name;`
- L25 _private member_ `int MaxSamples = 0;`
- L26 _private member_ `float MinRange = 0.0f;`
- L27 _private member_ `float MaxRange = 0.0f;`
- L28 _private member_ `float RefValue = 0.0f;`
- L30 _private member_ `float Sum = 0;`
- L31 _private member_ `TArray<float> Values;`
- L32 _private member_ `TArray<float> AvgValues;`
- L33 _private member_ `int InsertIndex = 0;`
- L34 _private member_ `int BufferedValues = 0;`
- L35 _private member_ `bool bFirstValue = true;`
- L37 _private member_ `mutable FCriticalSection CriticalSection;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/FrameBufferI420.h` (Private)


#### class `UE::PixelStreaming::WebRTCI420BufferWrapper`  
`class WebRTCI420BufferWrapper : public webrtc::I420BufferInterface`  
_L13-30_
- inherits: `webrtc::I420BufferInterface`
- desc: A wrapper to adapt the FPixelStreamingI420Buffer to webrtc's I420BufferInterface
- L16 _public function_ `WebRTCI420BufferWrapper(TSharedPtr<FPixelCaptureBufferI420> InCaptureBuffer) : CaptureBuffer(InCaptureBuffer)`
- L18 _public prototype_ `virtual ~WebRTCI420BufferWrapper() = default;`
- L19 _public function_ `virtual int width() const override`
- L20 _public function_ `virtual int height() const override`
- L21 _public function_ `virtual const uint8_t* DataY() const override`
- L22 _public function_ `virtual const uint8_t* DataU() const override`
- L23 _public function_ `virtual const uint8_t* DataV() const override`
- L24 _public function_ `virtual int StrideY() const override`
- L25 _public function_ `virtual int StrideU() const override`
- L26 _public function_ `virtual int StrideV() const override`
- L29 _private member_ `TSharedPtr<FPixelCaptureBufferI420> CaptureBuffer;`

#### class `UE::PixelStreaming::FFrameBufferI420`  
`class FFrameBufferI420 : public webrtc::VideoFrameBuffer`  
_L35-52_
- inherits: `webrtc::VideoFrameBuffer`
- desc: A frame buffer for our VPX encoders. Contains a single I420 buffer.
- L38 _public function_ `FFrameBufferI420(TSharedPtr<FPixelCaptureBufferI420> Buffer) : I420BufferWrapper(new rtc::RefCountedObject<WebRTCI420BufferWrapper>(Buffer))`
- L41 _public prototype_ `virtual ~FFrameBufferI420() = default;`
- L43 _public function_ `virtual webrtc::VideoFrameBuffer::Type type() const override`
- L44 _public function_ `virtual int width() const override`
- L45 _public function_ `virtual int height() const override`
- L47 _public function_ `virtual rtc::scoped_refptr<webrtc::I420BufferInterface> ToI420() override`
- L48 _public function_ `virtual const webrtc::I420BufferInterface* GetI420() const override`
- L51 _private member_ `rtc::scoped_refptr<WebRTCI420BufferWrapper> I420BufferWrapper;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/FrameBufferMultiFormat.h` (Private)


#### class `UE::PixelStreaming::FFrameBufferMultiFormatBase`  
`class FFrameBufferMultiFormatBase : public webrtc::VideoFrameBuffer`  
_L15-40_
- inherits: `webrtc::VideoFrameBuffer`
- desc: Base class for our multi format buffers.
- L18 _public prototype_ `FFrameBufferMultiFormatBase(TSharedPtr<FPixelCaptureCapturerMultiFormat> InFrameCapturer, uint32 InStreamId);`
- L19 _public prototype_ `virtual ~FFrameBufferMultiFormatBase() = default;`
- L21 _public function_ `virtual webrtc::VideoFrameBuffer::Type type() const override`
- L23 _public function_ `virtual rtc::scoped_refptr<webrtc::I420BufferInterface> ToI420() override`
- L29 _public function_ `virtual const webrtc::I420BufferInterface* GetI420() const override`
- L35 _public function_ `void SetSourceStreamId(uint32 InStreamId)`
- L38 _protected member_ `TSharedPtr<FPixelCaptureCapturerMultiFormat> FrameCapturer;`
- L39 _protected member_ `uint32 StreamId;`

#### class `UE::PixelStreaming::FFrameBufferMultiFormatLayered`  
`class FFrameBufferMultiFormatLayered : public FFrameBufferMultiFormatBase`  
_L45-58_
- inherits: `FFrameBufferMultiFormatBase`
- desc: A multi layered, multi format frame buffer for our encoder.
- L48 _public prototype_ `FFrameBufferMultiFormatLayered(TSharedPtr<FPixelCaptureCapturerMultiFormat> InFrameCapturer, uint32 InStreamId, FIntPoint SourceResolution);`
- L49 _public prototype_ `virtual ~FFrameBufferMultiFormatLayered() = default;`
- L51 _public prototype_ `virtual int width() const override;`
- L52 _public prototype_ `virtual int height() const override;`
- L54 _public prototype_ `rtc::scoped_refptr<FFrameBufferMultiFormat> GetLayer(FIntPoint Resolution) const;`
- L57 _private member_ `FIntPoint SourceResolution;`

#### class `UE::PixelStreaming::FFrameBufferMultiFormat`  
`class FFrameBufferMultiFormat : public FFrameBufferMultiFormatBase`  
_L63-81_
- inherits: `FFrameBufferMultiFormatBase`
- desc: A single layer, multi format frame buffer.
- L66 _public prototype_ `FFrameBufferMultiFormat(TSharedPtr<FPixelCaptureCapturerMultiFormat> InFrameCapturer, uint32 StreamId, FIntPoint InResolution);`
- L67 _public prototype_ `virtual ~FFrameBufferMultiFormat() = default;`
- L69 _public prototype_ `virtual int width() const override;`
- L70 _public prototype_ `virtual int height() const override;`
- L72 _public prototype_ `IPixelCaptureOutputFrame* RequestFormat(int32 Format) const;`
- L74 _public function_ `uint32 GetSourceStreamId() const`
- L77 _private member_ `FIntPoint Resolution;`
- L80 _private member_ `mutable TMap<int32, TSharedPtr<IPixelCaptureOutputFrame>> CachedFormat;` — we want the frame buffer to always refer to the same frame. so the first request for a format will fill this cache.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/FrameBufferRHI.h` (Private)


#### class `UE::PixelStreaming::FFrameBufferRHI`  
`class FFrameBufferRHI : public webrtc::VideoFrameBuffer`  
_L13-41_
- inherits: `webrtc::VideoFrameBuffer`
- desc: A frame buffer for RHI Video Resources.
- L16 _public function_ `FFrameBufferRHI(TSharedPtr<FVideoResourceRHI> VideoResourceRHI) : VideoResourceRHI(VideoResourceRHI)`
- L19 _public prototype_ `virtual ~FFrameBufferRHI() = default;`
- L21 _public function_ `virtual webrtc::VideoFrameBuffer::Type type() const override`
- L22 _public function_ `virtual int width() const override`
- L23 _public function_ `virtual int height() const override`
- L25 _public function_ `virtual rtc::scoped_refptr<webrtc::I420BufferInterface> ToI420() override`
- L31 _public function_ `virtual const webrtc::I420BufferInterface* GetI420() const override`
- L37 _public function_ `TSharedPtr<FVideoResourceRHI> GetVideoResource()`
- L40 _private member_ `TSharedPtr<FVideoResourceRHI> VideoResourceRHI;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/FreezeFrame.h` (Private)


#### class `UE::PixelStreaming::FFreezeFrame`  
`class FFreezeFrame : public TSharedFromThis<FFreezeFrame>`  
_L27-63_
- inherits: `TSharedFromThis<FFreezeFrame>`
- desc: The user of the Pixel Streaming application can trigger a freeze frame to happen at any time during stream. What a freeze frame will do is either: 1) Mode 1 - Send a known texture/image (effectively a still image, e.g. a loading screen). 2) Mode 2 - Send the current rendered frame out of UE as an image This freeze frame will displayed over the top of the video stream with no compression. So a crisp, high quality image, is guaranteed. While this is occuring the stream is not technically frozen, it still encodes and send frames; however, visually, the user is only shown this still. This technique can be used to hide large, known, cpu/gpu lags in the Pixel Streaming experience, for example during a level load or some expensive transition. The better solution is to not lag your application in the first place, but this can be a bandaid.
- L30 _public prototype_ `static TSharedPtr<FFreezeFrame> Create(TWeakPtr<TThreadSafeMap<FPixelStreamingPlayerId, FPlayerContext>> InPlayers);`
- L31 _public prototype_ `virtual ~FFreezeFrame();`
- L32 _public prototype_ `void SetVideoInput(TWeakPtr<FPixelStreamingVideoInput> VideoInput);`
- L33 _public prototype_ `void SetPlayers(TWeakPtr<TThreadSafeMap<FPixelStreamingPlayerId, FPlayerContext>> InPlayers);`
- L39 _public prototype_ `void StartFreeze(UTexture2D* Texture);` — @brief Start the freeze frame process, either mode 1 or 2 depending on if a texture is passed. @param Texture - The still image to send as a freeze frame, pass nullptr to use send the backbuffer instead.
- L40 _public prototype_ `void StopFreeze();`
- L41 _public prototype_ `void SendCachedFreezeFrameTo(FPixelStreamingPlayerId PlayerId) const;`
- L44 _protected prototype_ `FFreezeFrame() = default;`
- L47 _private prototype_ `void SendFreezeFrame(TArray<FColor> RawData, const FIntRect& Rect);`
- L48 _private prototype_ `void SetupFreezeFrameCapture();`
- L49 _private prototype_ `void RemoveFreezeFrameBinding();`
- L50 _private prototype_ `void FreezeFrameCapture();`
- L53 _private member_ `TWeakPtr<TThreadSafeMap<FPixelStreamingPlayerId, FPlayerContext>> WeakPlayers;`
- L56 _private member_ `TWeakPtr<FPixelStreamingVideoInput> VideoInput;` — Video input used to capture the frame if mode 2 is used.
- L59 _private member_ `TArray64<uint8> CachedJpegBytes;` — When we send a freeze frame we retain the data so we send freeze frame to new peers if they join during a freeze frame.
- L62 _private member_ `TOptional<FDelegateHandle> OnFrameCapturedForFreezeFrameHandle;` — Delegate handle for when we bind to the OnFrameCaptured delegate of the video input - we unbind from this once the freeze frame is captured

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/PixelStreamingAudioDeviceModule.h` (Private)


#### class `UE::PixelStreaming::FAudioDeviceModule`  
`class FAudioDeviceModule : public webrtc::AudioDeviceModule`  
_L17-124_
- inherits: `webrtc::AudioDeviceModule`
- desc: A custom audio device module for WebRTC. It lets us receive WebRTC audio in UE and also transmit UE audio to WebRTC.
- L21 _public prototype_ `FAudioDeviceModule();` — Use this constructor if the only audio source we want is the UE submix
- L24 _public prototype_ `FAudioDeviceModule(TSharedPtr<UE::PixelStreaming::FAudioInputMixer> InMixer);` — Use this constructor if we want to mix the submix with our audio sources.
- L25 _public prototype_ `virtual ~FAudioDeviceModule() = default;`
- L28 _private member_ `FThreadSafeBool bInitialized;` — True when we setup capturer/playout requester.
- L29 _private member_ `TSharedPtr<UE::PixelStreaming::FAudioSubmixCapturer, ESPMode::ThreadSafe> Capturer;`
- L30 _private member_ `TUniquePtr<UE::PixelStreaming::FAudioPlayoutRequester> Requester;`
- L31 _private member_ `TSharedPtr<UE::PixelStreaming::FAudioInputMixer> InputMixer;`
- L37 _private prototype_ `int32 ActiveAudioLayer(AudioLayer* audioLayer) const override;` — webrtc::AudioDeviceModule interface
- L38 _private prototype_ `int32 RegisterAudioCallback(webrtc::AudioTransport* audioCallback) override;`
- L41 _private prototype_ `int32 Init() override;` — Main initialization and termination
- L42 _private prototype_ `int32 Terminate() override;`
- L43 _private prototype_ `bool Initialized() const override;`
- L46 _private prototype_ `int16 PlayoutDevices() override;` — Device enumeration
- L47 _private prototype_ `int16 RecordingDevices() override;`
- L48 _private prototype_ `int32 PlayoutDeviceName(uint16 index, char name[webrtc::kAdmMaxDeviceNameSize], char guid[webrtc::kAdmMaxGuidSize]) override;`
- L49 _private prototype_ `int32 RecordingDeviceName(uint16 index, char name[webrtc::kAdmMaxDeviceNameSize], char guid[webrtc::kAdmMaxGuidSize]) override;`
- L52 _private prototype_ `int32 SetPlayoutDevice(uint16 index) override;` — Device selection
- L53 _private prototype_ `int32 SetPlayoutDevice(WindowsDeviceType device) override;`
- L54 _private prototype_ `int32 SetRecordingDevice(uint16 index) override;`
- L55 _private prototype_ `int32 SetRecordingDevice(WindowsDeviceType device) override;`
- L58 _private prototype_ `int32 PlayoutIsAvailable(bool* available) override;` — Audio transport initialization
- L59 _private prototype_ `int32 InitPlayout() override;`
- L60 _private prototype_ `bool PlayoutIsInitialized() const override;`
- L61 _private prototype_ `int32 RecordingIsAvailable(bool* available) override;`
- L62 _private prototype_ `int32 InitRecording() override;`
- L63 _private prototype_ `bool RecordingIsInitialized() const override;`
- L66 _private prototype_ `virtual int32 StartPlayout() override;` — Audio transport control
- L67 _private prototype_ `virtual int32 StopPlayout() override;`
- L70 _private prototype_ `virtual bool Playing() const override;` — True when audio is being pulled by the instance.
- L72 _private prototype_ `virtual int32 StartRecording() override;`
- L73 _private prototype_ `virtual int32 StopRecording() override;`
- L74 _private prototype_ `virtual bool Recording() const override;`
- L77 _private prototype_ `virtual int32 InitSpeaker() override;` — Audio mixer initialization
- L78 _private prototype_ `virtual bool SpeakerIsInitialized() const override;`
- L79 _private prototype_ `virtual int32 InitMicrophone() override;`
- L80 _private prototype_ `virtual bool MicrophoneIsInitialized() const override;`
- L83 _private prototype_ `virtual int32 SpeakerVolumeIsAvailable(bool* available) override;` — Speaker volume controls
- L84 _private prototype_ `virtual int32 SetSpeakerVolume(uint32 volume) override;`
- L85 _private prototype_ `virtual int32 SpeakerVolume(uint32* volume) const override;`
- L86 _private prototype_ `virtual int32 MaxSpeakerVolume(uint32* maxVolume) const override;`
- L87 _private prototype_ `virtual int32 MinSpeakerVolume(uint32* minVolume) const override;`
- L90 _private prototype_ `virtual int32 MicrophoneVolumeIsAvailable(bool* available) override;` — Microphone volume controls
- L91 _private prototype_ `virtual int32 SetMicrophoneVolume(uint32 volume) override;`
- L92 _private prototype_ `virtual int32 MicrophoneVolume(uint32* volume) const override;`
- L93 _private prototype_ `virtual int32 MaxMicrophoneVolume(uint32* maxVolume) const override;`
- L94 _private prototype_ `virtual int32 MinMicrophoneVolume(uint32* minVolume) const override;`
- L97 _private prototype_ `virtual int32 SpeakerMuteIsAvailable(bool* available) override;` — Speaker mute control
- L98 _private prototype_ `virtual int32 SetSpeakerMute(bool enable) override;`
- L99 _private prototype_ `virtual int32 SpeakerMute(bool* enabled) const override;`
- L102 _private prototype_ `virtual int32 MicrophoneMuteIsAvailable(bool* available) override;` — Microphone mute control
- L103 _private prototype_ `virtual int32 SetMicrophoneMute(bool enable) override;`
- L104 _private prototype_ `virtual int32 MicrophoneMute(bool* enabled) const override;`
- L107 _private prototype_ `virtual int32 StereoPlayoutIsAvailable(bool* available) const override;` — Stereo support
- L108 _private prototype_ `virtual int32 SetStereoPlayout(bool enable) override;`
- L109 _private prototype_ `virtual int32 StereoPlayout(bool* enabled) const override;`
- L110 _private prototype_ `virtual int32 StereoRecordingIsAvailable(bool* available) const override;`
- L111 _private prototype_ `virtual int32 SetStereoRecording(bool enable) override;`
- L112 _private prototype_ `virtual int32 StereoRecording(bool* enabled) const override;`
- L115 _private prototype_ `virtual int32 PlayoutDelay(uint16* delayMS) const override;` — Playout delay
- L116 _private prototype_ `virtual bool BuiltInAECIsAvailable() const override;`
- L117 _private prototype_ `virtual bool BuiltInAGCIsAvailable() const override;`
- L118 _private prototype_ `virtual bool BuiltInNSIsAvailable() const override;`
- L121 _private prototype_ `virtual int32 EnableBuiltInAEC(bool enable) override;` — Enables the built-in audio effects. Only supported on Android.
- L122 _private prototype_ `virtual int32 EnableBuiltInAGC(bool enable) override;`
- L123 _private prototype_ `virtual int32 EnableBuiltInNS(bool enable) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/PixelStreamingBlueprints.h` (Private)


#### class `UPixelStreamingBlueprints`  
`class UPixelStreamingBlueprints : public UBlueprintFunctionLibrary`  
_L14-164_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L26 _public prototype_ `static void SendFileAsByteArray(TArray<uint8> ByteArray, FString MimeType, FString FileExtension);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Send a specified byte array over the WebRTC peer connection data channel. The extension and mime type are used for file reconstruction on the front end @param   ByteArray       The raw data that will be sent over the data channel @param   MimeType        The mime type of the file. Used for reconstruction on the front end @param   FileExtension   The file extension. Used for file reconstruction on the front end
- L37 _public prototype_ `static void StreamerSendFileAsByteArray(FString StreamerId, TArray<uint8> ByteArray, FString MimeType, FString FileExtension);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Send a specified byte array over the WebRTC peer connection data channel. The extension and mime type are used for file reconstruction on the front end @param	StreamerId		The streamer use when sending the data @param   ByteArray       The raw data that will be sent over the data channel @param   MimeType        The mime type of the file. Used for reconstruction on the front end @param   FileExtension   The file extension. Used for file reconstruction on the front end
- L47 _public prototype_ `static void SendFile(FString Filepath, FString MimeType, FString FileExtension);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Send a specified file over the WebRTC peer connection data channel. The extension and mime type are used for file reconstruction on the front end @param   FilePath        The path to the file that will be sent @param   MimeType        The mime type of the file. Used for file reconstruction on the front end @param   FileExtension   The file extension. Used for file reconstruction on the front end
- L58 _public prototype_ `static void StreamerSendFile(FString StreamerId, FString Filepath, FString MimeType, FString FileExtension);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Send a specified file over the WebRTC peer connection data channel. The extension and mime type are used for file reconstruction on the front end @param	StreamerId		The streamer use when sending the data @param   FilePath        The path to the file that will be sent @param   MimeType        The mime type of the file. Used for file reconstruction on the front end @param   FileExtension   The file extension. Used for file reconstruction on the front end
- L64 _public prototype_ `static void ForceKeyFrame();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Force a key frame to be sent.
- L77 _public prototype_ `static void FreezeFrame(UTexture2D* Texture);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Freeze Pixel Streaming. @param   Texture         The freeze frame to display. If null then the back buffer is captured.
- L83 _public prototype_ `static void UnfreezeFrame();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Unfreeze Pixel Streaming.
- L91 _public prototype_ `static void StreamerFreezeStream(FString StreamerId, UTexture2D* Texture);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Freeze Pixel Streaming. @param	StreamerId		The id of the streamer to freeze. @param   Texture         The freeze frame to display. If null then the back buffer is captured.
- L98 _public prototype_ `static void StreamerUnfreezeStream(FString StreamerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Unfreeze Pixel Streaming. @param StreamerId		The id of the streamer to unfreeze.
- L105 _public prototype_ `static void KickPlayer(FString PlayerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Kick a player. @param   PlayerId         The ID of the player to kick.
- L113 _public prototype_ `static void StreamerKickPlayer(FString StreamerId, FString PlayerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Kick a player. @param	StreamerId		The streamer which the player belongs @param   PlayerId        The ID of the player to kick.
- L122 _public prototype_ `static void SetPlayerLayerPreference(FString PlayerId, int SpatialLayerId, int TemporalLayerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Set the layer preference for a specific player @param PlayerId			The ID of the player to set the layer preference for. @param SpatialLayerId	The spatial layer ID @param TemporalLayerId	The temporal layer ID
- L132 _public prototype_ `static void StreamerSetPlayerLayerPreference(FString StreamerId, FString PlayerId, int SpatialLayerId, int TemporalLayerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Set the layer preference for a specific player @param StreamerId 		The streamer which the player belongs @param PlayerId			The ID of the player to set the layer preference for. @param SpatialLayerId	The spatial layer ID @param TemporalLayerId	The temporal layer ID
- L140 _public prototype_ `static TArray<FString> GetConnectedPlayers();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — @brief Get the connected players @return TArray<FString> The connected players
- L149 _public prototype_ `static TArray<FString> StreamerGetConnectedPlayers(FString StreamerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — @brief Get the connected players @param StreamerId	The streamer whose list of players you wish to get @return TArray<FString> The connected players
- L155 _public prototype_ `static FString GetDefaultStreamerID();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Get the default Streamer ID
- L163 _public prototype_ `static UPixelStreamingDelegates* GetPixelStreamingDelegates();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming")` — Get the singleton. This allows application-specific blueprints to bind to delegates of interest.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/PixelStreamingModule.h` (Private)


#### class `UE::PixelStreaming::FPixelStreamingModule`  
`class FPixelStreamingModule : public IPixelStreamingModule`  
_L22-79_
- inherits: `IPixelStreamingModule`
- desc: This plugin allows the back buffer to be sent as a compressed video across a network.
- L25 _public prototype_ `static IPixelStreamingModule* GetModule();`
- L28 _public prototype_ `virtual void SetCodec(EPixelStreamingCodec Codec) override;` — IPixelStreamingModule implementation
- L29 _public prototype_ `virtual EPixelStreamingCodec GetCodec() const override;`
- L30 _public prototype_ `virtual FReadyEvent& OnReady() override;`
- L31 _public prototype_ `virtual bool IsReady() override;`
- L32 _public prototype_ `virtual bool StartStreaming() override;`
- L33 _public prototype_ `virtual void StopStreaming() override;`
- L34 _public prototype_ `virtual TSharedPtr<IPixelStreamingStreamer> CreateStreamer(const FString& StreamerId) override;`
- L35 _public prototype_ `virtual TArray<FString> GetStreamerIds() override;`
- L36 _public prototype_ `virtual TSharedPtr<IPixelStreamingStreamer> FindStreamer(const FString& StreamerId) override;`
- L37 _public prototype_ `virtual TSharedPtr<IPixelStreamingStreamer> DeleteStreamer(const FString& StreamerId) override;`
- L38 _public prototype_ `void DeleteStreamer(TSharedPtr<IPixelStreamingStreamer> ToBeDeleted) override;`
- L39 _public prototype_ `virtual FString GetDefaultStreamerID() override;`
- L40 _public prototype_ `virtual FString GetDefaultSignallingURL() override;`
- L43 _public prototype_ `virtual void AddInputComponent(UPixelStreamingInput* InInputComponent) override;` — These are staying on the module at the moment as theres no way of the BPs knowing which streamer they are relevant to
- L44 _public prototype_ `virtual void RemoveInputComponent(UPixelStreamingInput* InInputComponent) override;`
- L45 _public prototype_ `virtual const TArray<UPixelStreamingInput*> GetInputComponents() override;`
- L47 _public prototype_ `virtual void SetExternalVideoSourceFPS(uint32 InFPS) override;` — Don't delete, is used externally to PS
- L48 _public prototype_ `virtual void SetExternalVideoSourceCoupleFramerate(bool bShouldCoupleFPS) override;`
- L49 _public prototype_ `virtual void SetExternalVideoSourceInput(TSharedPtr<FPixelStreamingVideoInput> InVideoInput) override;`
- L50 _public prototype_ `virtual rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> CreateExternalVideoSource() override;`
- L51 _public prototype_ `virtual void ReleaseExternalVideoSource(const webrtc::VideoTrackSourceInterface* InVideoSource) override;`
- L52 _public prototype_ `virtual TUniquePtr<webrtc::VideoEncoderFactory> CreateVideoEncoderFactory() override;`
- L53 _public prototype_ `virtual void ForEachStreamer(const TFunction<void(TSharedPtr<IPixelStreamingStreamer>)>& Func) override;`
- L58 _private prototype_ `void StartupModule() override;` — IModuleInterface implementation
- L59 _private prototype_ `void ShutdownModule() override;`
- L63 _private prototype_ `void InitDefaultStreamer();` — Own methods
- L64 _private prototype_ `bool IsPlatformCompatible() const;`
- L65 _private prototype_ `void RegisterCustomHandlers(TSharedPtr<IPixelStreamingStreamer> Streamer);`
- L66 _private prototype_ `void HandleUIInteraction(FMemoryReader Ar);`
- L69 _private member_ `bool bModuleReady = false;`
- L70 _private member_ `bool bStartupCompleted = false;`
- L71 _private member_ `static IPixelStreamingModule* PixelStreamingModule;`
- L73 _private member_ `FReadyEvent ReadyEvent;`
- L74 _private member_ `TArray<UPixelStreamingInput*> InputComponents;`
- L75 _private member_ `TSharedPtr<FVideoSourceGroup> ExternalVideoSourceGroup;`
- L76 _private member_ `mutable FCriticalSection StreamersCS;`
- L77 _private member_ `TMap<FString, TWeakPtr<IPixelStreamingStreamer>> Streamers;`
- L78 _private member_ `TSharedPtr<IPixelStreamingStreamer> DefaultStreamer;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/PixelStreamingPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming, Log, All);`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/PlayerContext.h` (Private)


#### struct `UE::PixelStreaming::FPlayerContext`  
`struct FPlayerContext`  
_L11-16_
- L13 _public member_ `FPixelStreamingPlayerConfig Config;`
- L14 _public member_ `TSharedPtr<FPixelStreamingPeerConnection> PeerConnection;`
- L15 _public member_ `TSharedPtr<FPixelStreamingDataChannel> DataChannel;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/RTCStatsCollector.h` (Private)


#### class `UE::PixelStreaming::FRTCStatsCollector`  
`class FRTCStatsCollector : public webrtc::RTCStatsCollectorCallback`  
_L21-147_
- inherits: `webrtc::RTCStatsCollectorCallback`
- L24 _public prototype_ `FRTCStatsCollector();`
- L25 _public prototype_ `FRTCStatsCollector(FPixelStreamingPlayerId PlayerId);`
- L28 _public prototype_ `void OnStatsDelivered(const rtc::scoped_refptr<const webrtc::RTCStatsReport>& report) override;`
- L29 _public prototype_ `void AddRef() const override;`
- L30 _public prototype_ `rtc::RefCountReleaseStatus Release() const override;`
- L137 _private member_ `FPixelStreamingPlayerId AssociatedPlayerId;`
- L139 _private member_ `mutable int32 RefCount;`
- L141 _private member_ `uint64 LastCalculationCycles;`
- L143 _private member_ `bool bIsEnabled;`
- L146 _private member_ `TArray<TSharedPtr<FStatsSink>> RTCStatSinks;` — All sinks are given all webrtc::RTCStats contained in a report and they can choose which stats they wish to extract/process.

#### class `UE::PixelStreaming::FRTCStatsCollector::FRTCTrackedStat`  
`class FRTCTrackedStat`  
_L38-51_
- desc: ---------- FRTCTrackedStat ------------------- Tracks a stat from WebRTC. Stores the current value and previous value.
- L41 _public function_ `FRTCTrackedStat(FName StatName, int NDecimalPlaces) : LatestStat(StatName, 0.0, NDecimalPlaces)`
- L42 _public function_ `FRTCTrackedStat(FName StatName, int NDecimalPlaces, uint8 DisplayFlags) : LatestStat(StatName, 0.0, NDecimalPlaces)`
- L43 _public prototype_ `FRTCTrackedStat(FName StatName, FName Alias, int NDecimalPlaces, uint8 DisplayFlags);`
- L44 _public prototype_ `double CalculateDelta(double Period) const;`
- L45 _public prototype_ `double Average() const;`
- L46 _public function_ `const FStatData& GetLatestStat() const`
- L47 _public prototype_ `void SetLatestValue(double InValue);`
- L49 _private member_ `FStatData LatestStat;`
- L50 _private member_ `double PrevValue = 0.0;`

#### class `UE::PixelStreaming::FRTCStatsCollector::FStatsSink`  
`class FStatsSink`  
_L57-85_
- desc: ---------- FStatsSink ------------------- A sink for processing webrtc::RTCStats - processing will include extracting stats and storing them.
- L60 _public function_ `FStatsSink(FName InSinkType) : SinkType(InSinkType)`
- L61 _public prototype_ `virtual ~FStatsSink() = default;`
- L62 _public function_ `virtual bool Wants(const webrtc::RTCStats& InStats) const`
- L63 _public prototype_ `virtual void Process(const webrtc::RTCStats& InStats, FString PeerId);`
- L64 _public prototype_ `virtual void PostProcess(FString PeerId, double SecondsDelta);`
- L65 _public function_ `virtual FString DerivePeerId(const webrtc::RTCStats& InStats, FPixelStreamingPlayerId PlayerId) const`
- L67 _public prototype_ `virtual bool ExtractValueAndSet(const webrtc::RTCStatsMemberInterface* ExtractFrom, FRTCTrackedStat* SetValueHere);` — returns true if the value is worth storing (false if it started and remains zero)
- L68 _public function_ `virtual bool Contains(const FName StatName) const`
- L69 _public function_ `virtual bool ContainsCalculatedStat(const FName& StatName) const`
- L70 _public function_ `virtual void Add(FName StatName, int NDecimalPlaces)`
- L71 _public prototype_ `virtual void AddAliased(FName StatName, FName AliasedName, int NDecimalPlaces, uint8 DisplayFlags);`
- L72 _public function_ `virtual void AddNonRendered(FName StatName)`
- L73 _public function_ `virtual void AddStatCalculator(const TFunction<TOptional<FStatData>(FStatsSink&, double)>& Calculator)`
- L74 _public function_ `virtual FRTCTrackedStat* Get(const FName& StatName)`
- L75 _public function_ `virtual FStatData* GetCalculatedStat(const FName& StatName)`
- L78 _public member_ `TMap<FName, FRTCTrackedStat> Stats;` — Stats that are stored as is.
- L81 _public member_ `TMap<FName, FStatData> CalculatedStats;` — Stats we calculate based on the stats map above. This calculation is done in FStatsSink::PostProcess by the `Calculators` below.
- L82 _public member_ `TArray<TFunction<TOptional<FStatData>(FStatsSink&, double)>> Calculators;`
- L84 _protected member_ `FName SinkType;`

#### class `UE::PixelStreaming::FRTCStatsCollector::FRTPMediaStatsSink`  
`class FRTPMediaStatsSink : public FStatsSink`  
_L91-100_
- inherits: `FStatsSink`
- desc: ---------- FRTPMediaStatsSink ------------------- Sink useful for RTP media (audio or video) that is inbound or outbound.
- L94 _public prototype_ `FRTPMediaStatsSink(FName InSinkType, FString InMediaKind);`
- L95 _public prototype_ `virtual ~FRTPMediaStatsSink() = default;`
- L96 _public prototype_ `virtual bool Wants(const webrtc::RTCStats& InStats) const override;`
- L97 _public prototype_ `virtual FString DerivePeerId(const webrtc::RTCStats& InStats, FPixelStreamingPlayerId PlayerId) const override;`
- L99 _private member_ `FString MediaKind;`

#### class `UE::PixelStreaming::FRTCStatsCollector::FTrackStatsSink`  
`class FTrackStatsSink : public FStatsSink`  
_L106-111_
- inherits: `FStatsSink`
- desc: ---------- FTrackStatsSink ------------------- Stats sink for `track` stats
- L109 _public prototype_ `FTrackStatsSink();`
- L110 _public prototype_ `virtual ~FTrackStatsSink() = default;`

#### class `UE::PixelStreaming::FRTCStatsCollector::FVideoSourceStatsSink`  
`class FVideoSourceStatsSink : public FStatsSink`  
_L117-123_
- inherits: `FStatsSink`
- desc: ---------- FVideoSourceStatsSink ------------------- Stats sink for video `media-source` stats
- L120 _public prototype_ `FVideoSourceStatsSink();`
- L121 _public prototype_ `virtual ~FVideoSourceStatsSink() = default;`
- L122 _public prototype_ `virtual bool Wants(const webrtc::RTCStats& InStats) const override;`

#### class `UE::PixelStreaming::FRTCStatsCollector::FDataChannelStatsSink`  
`class FDataChannelStatsSink : public FStatsSink`  
_L129-134_
- inherits: `FStatsSink`
- desc: ---------- FDataChannelStatsSink ------------------- Stats sink `data-channel` stats
- L132 _public prototype_ `FDataChannelStatsSink();`
- L133 _public prototype_ `virtual ~FDataChannelStatsSink() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L12 _namespace_ `namespace RTCStatTypes` (scope `UE::PixelStreaming`)
- L14 _variable_ `const FName DataChannel = FName(TEXT("data` (scope `UE::PixelStreaming::RTCStatTypes`)
- L15 _variable_ `const FName OutboundRTP = FName(TEXT("outb` (scope `UE::PixelStreaming::RTCStatTypes`)
- L16 _variable_ `const FName InboundRTP = FName(TEXT("inbo` (scope `UE::PixelStreaming::RTCStatTypes`)
- L17 _variable_ `const FName Track = FName(TEXT("trac` (scope `UE::PixelStreaming::RTCStatTypes`)
- L18 _variable_ `const FName MediaSource = FName(TEXT("medi` (scope `UE::PixelStreaming::RTCStatTypes`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/Settings.h` (Private)


#### enum `UE::PixelStreaming::Settings::EInputControllerMode`  
`enum EInputControllerMode`  
_L82-88_
- desc: Pixel Streaming can limit who can send input (keyboard, mouse, etc).
- L85 _public enumerator_ `Any` — Any - Any peer can control input.
- L87 _public enumerator_ `Host` — Host - Only the "host" peer can control input.

#### enum `UE::PixelStreaming::Settings::EQualityControllerMode`  
`enum EQualityControllerMode : int32`  
_L90-94_
- L92 _public enumerator_ `GrantAllRequested = 0`
- L93 _public enumerator_ `GrantOnlyFirst = 1`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L15 _namespace_ `namespace Settings` (scope `UE::PixelStreaming`)
- L17 _prototype_ `extern void InitialiseSettings();` (scope `UE::PixelStreaming::Settings`)
- L20 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingEncoderTargetBitrate;` (scope `UE::PixelStreaming::Settings`)
- L21 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingEncoderMaxBitrate;` (scope `UE::PixelStreaming::Settings`)
- L22 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingDebugDumpFrame;` (scope `UE::PixelStreaming::Settings`)
- L23 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingEncoderMinQP;` (scope `UE::PixelStreaming::Settings`)
- L24 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingEncoderMaxQP;` (scope `UE::PixelStreaming::Settings`)
- L25 _externvar_ `extern TAutoConsoleVariable<FString> CVarPixelStreamingEncoderRateControl;` (scope `UE::PixelStreaming::Settings`)
- L26 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingEnableFillerData;` (scope `UE::PixelStreaming::Settings`)
- L27 _externvar_ `extern TAutoConsoleVariable<FString> CVarPixelStreamingEncoderMultipass;` (scope `UE::PixelStreaming::Settings`)
- L28 _externvar_ `extern TAutoConsoleVariable<FString> CVarPixelStreamingH264Profile;` (scope `UE::PixelStreaming::Settings`)
- L29 _externvar_ `extern TAutoConsoleVariable<FString> CVarPixelStreamingEncoderPreset;` (scope `UE::PixelStreaming::Settings`)
- L30 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingEncoderKeyframeInterval;` (scope `UE::PixelStreaming::Settings`)
- L31 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingEncoderIntraRefreshPeriodFrames;` (scope `UE::PixelStreaming::Settings`)
- L32 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingEncoderIntraRefreshCountFrames;` (scope `UE::PixelStreaming::Settings`)
- L33 _externvar_ `extern TAutoConsoleVariable<FString> CVarPixelStreamingEncoderCodec;` (scope `UE::PixelStreaming::Settings`)
- L34 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingEncoderMaxSessions;` (scope `UE::PixelStreaming::Settings`)
- L38 _externvar_ `extern TAutoConsoleVariable<FString> CVarPixelStreamingDegradationPreference;` (scope `UE::PixelStreaming::Settings`)
- L39 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingWebRTCFps;` (scope `UE::PixelStreaming::Settings`)
- L40 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingWebRTCStartBitrate;` (scope `UE::PixelStreaming::Settings`)
- L41 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingWebRTCMinBitrate;` (scope `UE::PixelStreaming::Settings`)
- L42 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingWebRTCMaxBitrate;` (scope `UE::PixelStreaming::Settings`)
- L43 _externvar_ `extern TAutoConsoleVariable<int> CVarPixelStreamingWebRTCLowQpThreshold;` (scope `UE::PixelStreaming::Settings`)
- L44 _externvar_ `extern TAutoConsoleVariable<int> CVarPixelStreamingWebRTCHighQpThreshold;` (scope `UE::PixelStreaming::Settings`)
- L45 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingWebRTCDisableReceiveAudio;` (scope `UE::PixelStreaming::Settings`)
- L46 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingWebRTCDisableTransmitAudio;` (scope `UE::PixelStreaming::Settings`)
- L47 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingWebRTCDisableTransmitVideo;` (scope `UE::PixelStreaming::Settings`)
- L48 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingWebRTCDisableAudioSync;` (scope `UE::PixelStreaming::Settings`)
- L49 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingWebRTCUseLegacyAudioDevice;` (scope `UE::PixelStreaming::Settings`)
- L50 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingWebRTCEnableFlexFec;` (scope `UE::PixelStreaming::Settings`)
- L51 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingWebRTCDisableStats;` (scope `UE::PixelStreaming::Settings`)
- L52 _externvar_ `extern TAutoConsoleVariable<float> CVarPixelStreamingWebRTCAudioGain;` (scope `UE::PixelStreaming::Settings`)
- L53 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingWebRTCNegotiateCodecs;` (scope `UE::PixelStreaming::Settings`)
- L54 _externvar_ `extern TAutoConsoleVariable<FString> CVarPixelStreamingWebRTCFieldTrials;` (scope `UE::PixelStreaming::Settings`)
- L55 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingWebRTCDisableFrameDropper;` (scope `UE::PixelStreaming::Settings`)
- L56 _externvar_ `extern TAutoConsoleVariable<float> CVarPixelStreamingWebRTCVideoPacingFactor;` (scope `UE::PixelStreaming::Settings`)
- L57 _externvar_ `extern TAutoConsoleVariable<float> CVarPixelStreamingWebRTCVideoPacingMaxDelay;` (scope `UE::PixelStreaming::Settings`)
- L58 _externvar_ `extern TAutoConsoleVariable<int> CVarPixelStreamingWebRTCMinPort;` (scope `UE::PixelStreaming::Settings`)
- L59 _externvar_ `extern TAutoConsoleVariable<int> CVarPixelStreamingWebRTCMaxPort;` (scope `UE::PixelStreaming::Settings`)
- L60 _externvar_ `extern TAutoConsoleVariable<FString> CVarPixelStreamingWebRTCPortAllocatorFlags;` (scope `UE::PixelStreaming::Settings`)
- L64 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingOnScreenStats;` (scope `UE::PixelStreaming::Settings`)
- L65 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingLogStats;` (scope `UE::PixelStreaming::Settings`)
- L66 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingFreezeFrameQuality;` (scope `UE::PixelStreaming::Settings`)
- L67 _externvar_ `extern TAutoConsoleVariable<bool> CVarSendPlayerIdAsInteger;` (scope `UE::PixelStreaming::Settings`)
- L68 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingDisableLatencyTester;` (scope `UE::PixelStreaming::Settings`)
- L69 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingVPXUseCompute;` (scope `UE::PixelStreaming::Settings`)
- L70 _externvar_ `extern TAutoConsoleVariable<FString> CVarPixelStreamingInputController;` (scope `UE::PixelStreaming::Settings`)
- L71 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingSuppressICECandidateErrors;` (scope `UE::PixelStreaming::Settings`)
- L72 _externvar_ `extern TAutoConsoleVariable<float> CVarPixelStreamingSignalingReconnectInterval;` (scope `UE::PixelStreaming::Settings`)
- L73 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingExperimentalAudioInput;` (scope `UE::PixelStreaming::Settings`)
- L74 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingCaptureUseFence;` (scope `UE::PixelStreaming::Settings`)
- L75 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingDecoupleFramerate;` (scope `UE::PixelStreaming::Settings`)
- L76 _externvar_ `extern TAutoConsoleVariable<float> CVarPixelStreamingDecoupleWaitFactor;` (scope `UE::PixelStreaming::Settings`)
- L77 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingUseMediaCapture;` (scope `UE::PixelStreaming::Settings`)
- L78 _externvar_ `extern TAutoConsoleVariable<int32> CVarPixelStreamingQualityControllerMode;` (scope `UE::PixelStreaming::Settings`)
- L97 _prototype_ `bool IsCoupledFramerate();` (scope `UE::PixelStreaming::Settings`)
- L98 _prototype_ `bool IsCodecVPX();` (scope `UE::PixelStreaming::Settings`)
- L99 _prototype_ `void SetCodec(EPixelStreamingCodec Codec);` (scope `UE::PixelStreaming::Settings`)
- L100 _prototype_ `EPixelStreamingCodec GetSelectedCodec();` (scope `UE::PixelStreaming::Settings`)
- L101 _prototype_ `ERateControlMode GetRateControlCVar();` (scope `UE::PixelStreaming::Settings`)
- L102 _prototype_ `EMultipassMode GetMultipassCVar();` (scope `UE::PixelStreaming::Settings`)
- L103 _prototype_ `webrtc::DegradationPreference GetDegradationPreference();` (scope `UE::PixelStreaming::Settings`)
- L104 _prototype_ `EH264Profile GetH264Profile();` (scope `UE::PixelStreaming::Settings`)
- L105 _prototype_ `EAVPreset GetEncoderPreset();` (scope `UE::PixelStreaming::Settings`)
- L106 _prototype_ `EInputControllerMode GetInputControllerMode();` (scope `UE::PixelStreaming::Settings`)
- L107 _prototype_ `FString GetDefaultStreamerID();` (scope `UE::PixelStreaming::Settings`)
- L108 _prototype_ `FString GetDefaultSignallingURL();` (scope `UE::PixelStreaming::Settings`)
- L109 _prototype_ `bool GetControlScheme(FString& OutControlScheme);` (scope `UE::PixelStreaming::Settings`)
- L110 _prototype_ `bool GetFastPan(float& OutFastPan);` (scope `UE::PixelStreaming::Settings`)
- L111 _prototype_ `bool GetSignallingServerUrl(FString& OutSignallingServerURL);` (scope `UE::PixelStreaming::Settings`)
- L112 _prototype_ `bool GetSignallingServerIP(FString& OutSignallingServerIP);` (scope `UE::PixelStreaming::Settings`)
- L113 _prototype_ `bool GetSignallingServerPort(uint16& OutSignallingServerPort);` (scope `UE::PixelStreaming::Settings`)
- L120 _prototype_ `bool GetVideoPacing(float& OutPacingFactor, float& OutMaxDelayMs);` (scope `UE::PixelStreaming::Settings`) — @param OutPacingFactor The pacing factor to use for the field trial. @param OutMaxDelayMs The max delay to use for the field trial. @return True if WebRTC-Video-Pacing field trial is enabled.
- L123 _externvar_ `extern FPixelStreamingSimulcastParameters SimulcastParameters;` (scope `UE::PixelStreaming::Settings`)
- L124 _externvar_ `extern uint32 PortAllocatorParameters;` (scope `UE::PixelStreaming::Settings`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/SignallingConnectionObserver.h` (Private)


#### class `UE::PixelStreaming::FPixelStreamingSignallingConnectionObserver`  
`class FPixelStreamingSignallingConnectionObserver : public IPixelStreamingSignallingConnectionObserver`  
_L10-38_
- inherits: `IPixelStreamingSignallingConnectionObserver`
- L13 _public prototype_ `FPixelStreamingSignallingConnectionObserver(FStreamer& InStreamer);`
- L14 _public prototype_ `virtual ~FPixelStreamingSignallingConnectionObserver() = default;`
- L16 _public prototype_ `virtual void OnSignallingConnected() override;`
- L17 _public prototype_ `virtual void OnSignallingDisconnected(int32 StatusCode, const FString& Reason, bool bWasClean) override;`
- L18 _public prototype_ `virtual void OnSignallingError(const FString& ErrorMsg) override;`
- L19 _public prototype_ `virtual void OnSignallingConfig(const webrtc::PeerConnectionInterface::RTCConfiguration& Config) override;`
- L22 _public prototype_ `virtual void OnSignallingSessionDescription(FPixelStreamingPlayerId PlayerId, webrtc::SdpType Type, const FString& Sdp) override;` — Streamer-only
- L23 _public prototype_ `virtual void OnSignallingRemoteIceCandidate(FPixelStreamingPlayerId PlayerId, const FString& SdpMid, int SdpMLineIndex, const FString& Sdp) override;`
- L24 _public prototype_ `virtual void OnSignallingPlayerConnected(FPixelStreamingPlayerId PlayerId, const FPixelStreamingPlayerConfig& PlayerConfig, bool bSendOffer) override;`
- L25 _public prototype_ `virtual void OnSignallingPlayerDisconnected(FPixelStreamingPlayerId PlayerId) override;`
- L26 _public prototype_ `virtual void OnSignallingSFUPeerDataChannels(FPixelStreamingPlayerId SFUId, FPixelStreamingPlayerId PlayerId, int32 SendStreamId, int32 RecvStreamId) override;`
- L27 _public prototype_ `virtual void OnPlayerRequestsBitrate(FPixelStreamingPlayerId PlayerId, int MinBitrate, int MaxBitrate) override;`
- L30 _public prototype_ `virtual void OnSignallingStreamerList(const TArray<FString>& StreamerList) override;` — Player-only
- L31 _public prototype_ `virtual void OnSignallingSessionDescription(webrtc::SdpType Type, const FString& Sdp) override;`
- L32 _public prototype_ `virtual void OnSignallingRemoteIceCandidate(const FString& SdpMid, int SdpMLineIndex, const FString& Sdp) override;`
- L33 _public prototype_ `virtual void OnSignallingPlayerCount(uint32 Count) override;`
- L34 _public prototype_ `virtual void OnSignallingPeerDataChannels(int32 SendStreamId, int32 RecvStreamId) override;`
- L37 _private member_ `FStreamer& Streamer;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/Stats.h` (Private)


#### class `UE::PixelStreaming::IStatsSource`  
`class IStatsSource`  
_L18-23_
- desc: An interface that allows us to collect webrtc stats from anything that implements it
- L21 _public prototype_ `virtual ~IStatsSource() = default;`
- L22 _public prototype_ `virtual void PollWebRTCStats() const = 0;`

#### struct `UE::PixelStreaming::FStatData`  
`struct FStatData`  
_L25-65_
- L35 _public function_ `FStatData(FName InStatName, double InStatValue, int InNDecimalPlacesToPrint, bool bInSmooth = false) : StatName(InStatName) , StatValue(InStatValue) , NDecimalPlacesToPrint(InNDecimalPlacesToPrint) , bSmooth(bInSmooth)`
- L43 _public function_ `bool operator==(const FStatData& Other) const`
- L48 _public function_ `bool Equals(const FStatData& Other) const`
- L53 _public function_ `bool IsHidden()`
- L54 _public function_ `bool ShouldGraph()`
- L55 _public function_ `bool ShouldDisplayText()`
- L57 _public member_ `FName StatName;`
- L58 _public member_ `double StatValue;`
- L59 _public member_ `int NDecimalPlacesToPrint;`
- L60 _public member_ `bool bSmooth;`
- L61 _public member_ `double LastEMA = 0;`
- L62 _public member_ `int NumSamples = 0;`
- L63 _public member_ `uint8 DisplayFlags = EDisplayFlags::TEXT;`
- L64 _public member_ `TOptional<FName> Alias;` — uint8 DisplayFlags = EDisplayFlags::TEXT;   Some stats we only wish to store or broadcast, but not display

#### enum `UE::PixelStreaming::FStatData::EDisplayFlags`  
`enum EDisplayFlags: uint8`  
_L28-33_
- L30 _public enumerator_ `HIDDEN = 0`
- L31 _public enumerator_ `TEXT = 1 << 0`
- L32 _public enumerator_ `GRAPH = 1 << 1`

#### struct `UE::PixelStreaming::FStoredStat`  
`struct FStoredStat`  
_L74-81_
- desc: Stat that can be optionally rendered
- L77 _public member_ `FStatData Stat;`
- L78 _public member_ `TOptional<FCanvasTextItem> Renderable;`
- L80 _public function_ `FStoredStat(FStatData& InStat) : Stat(InStat)`

#### class `UE::PixelStreaming::FStatGroup`  
`class FStatGroup`  
_L84-102_
- desc: A grouping of stats by some category name
- L87 _public function_ `FStatGroup(FName CategoryName) : GroupName(CategoryName) , CategoryCanvasItem(FVector2D(0, 0), FText::FromString(FString::Printf(TEXT("---%s---"), *CategoryName.ToString())), FSlateFontInfo(FSlateFontInfo(UEngine::GetSmallFont(), 15)), FLinearColor(0, 0.9f, 0.1f))`
- L94 _public prototype_ `virtual ~FStatGroup() = default;`
- L95 _public prototype_ `bool StoreStat(FStatData& StatToStore);`
- L96 _public function_ `const TMap<FName, FStoredStat>& GetStoredStats() const`
- L98 _private member_ `FName GroupName;`
- L99 _private member_ `TMap<FName, FStoredStat> StoredStats;`
- L101 _public member_ `FCanvasTextItem CategoryCanvasItem;`

#### class `UE::PixelStreaming::FPeerStats`  
`class FPeerStats`  
_L105-127_
- desc: Pixel Streaming stats that are associated with a specific peer.
- L109 _public function_ `FPeerStats(FPixelStreamingPlayerId InAssociatedPlayer) : AssociatedPlayer(InAssociatedPlayer) , PlayerIdCanvasItem(FVector2D(0, 0), FText::FromString(FString::Printf(TEXT("[Peer Stats(%s)]"), *AssociatedPlayer)), FSlateFontInfo(FSlateFontInfo(UEngine::GetSmallFont(), 15)), FLinearColor(0, 1, 0))`
- L116 _public prototype_ `bool StoreStat(FName StatCategory, FStatData& StatToStore);`
- L117 _public prototype_ `bool GetStat(FName StatCategory, FName StatToQuery, double& OutValue) const;`
- L118 _public function_ `const TMap<FName, FStatGroup>& GetStatGroups() const`
- L121 _private member_ `int DisplayId = 0;`
- L122 _private member_ `FPixelStreamingPlayerId AssociatedPlayer;`
- L123 _private member_ `TMap<FName, FStatGroup> StatGroups;`
- L126 _public member_ `FCanvasTextItem PlayerIdCanvasItem;`

#### class `UE::PixelStreaming::FStats`  
`class FStats : public FTickableGameObject, public IPixelStreamingStats`  
_L133-200_
- inherits: `FTickableGameObject,IPixelStreamingStats`
- desc: Stats about Pixel Streaming that can displayed either in the in-application HUD, in the log, or simply reported to some subscriber. Stats can be enabled to draw on screen with: `stat pixelstreaming` `stat pixelstreaminggraphs`
- L136 _public function_ `virtual bool IsTickableInEditor() const override`
- L138 _public member_ `static constexpr double SmoothingPeriod = 3.0 * 60.0;`
- L139 _public member_ `static constexpr double SmoothingFactor = 10.0 / 100.0;`
- L140 _public prototype_ `static FStats* Get();`
- L142 _public prototype_ `FStats(const FStats&) = delete;`
- L143 _public prototype_ `bool QueryPeerStat(FPixelStreamingPlayerId PlayerId, FName StatCategory, FName StatToQuery, double& OutValue) const;`
- L144 _public prototype_ `void RemovePeerStats(FPixelStreamingPlayerId PlayerId);`
- L145 _public prototype_ `void RemoveAllPeerStats();`
- L146 _public prototype_ `void StorePeerStat(FPixelStreamingPlayerId PlayerId, FName StatCategory, FStatData Stat);`
- L147 _public prototype_ `void StoreApplicationStat(FStatData PeerStat);`
- L148 _public prototype_ `void Tick(float DeltaTime);`
- L150 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnStatsPolled);`
- L151 _public member_ `FOnStatsPolled OnStatsPolled;`
- L153 _public prototype_ `void ExecStatPS();`
- L154 _public prototype_ `bool OnToggleStats(UWorld* World, FCommonViewportClient* ViewportClient, const TCHAR* Stream);`
- L155 _public prototype_ `int32 OnRenderStats(UWorld* World, FViewport* Viewport, FCanvas* Canvas, int32 X, int32 Y, const FVector* ViewLocation, const FRotator* ViewRotation);`
- L157 _public prototype_ `void ExecStatPSGraphs();`
- L158 _public prototype_ `bool OnToggleGraphs(UWorld* World, FCommonViewportClient* ViewportClient, const TCHAR* Stream);`
- L159 _public prototype_ `int32 OnRenderGraphs(UWorld* World, FViewport* Viewport, FCanvas* Canvas, int32 X, int32 Y, const FVector* ViewLocation, const FRotator* ViewRotation);`
- L161 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L163 _public prototype_ `double AddTimeStat(uint64 Millis, const FString& Label);`
- L164 _public prototype_ `double AddTimeDeltaStat(uint64 Millis1, uint64 Millis2, const FString& Label);`
- L165 _public prototype_ `void AddFrameTimingStats(const FPixelCaptureFrameMetadata& FrameMetadata);`
- L166 _public prototype_ `void AddCanvasTile(FName Name, const FCanvasTileItem& Tile);`
- L170 _public prototype_ `void GraphValue(FName InName, float Value, int InSamples, float InMinRange, float InMaxRange, float InRefValue = 0.0f) override;`
- L174 _private prototype_ `FStats();`
- L175 _private prototype_ `void RegisterEngineHooks();`
- L176 _private prototype_ `void PollPixelStreamingSettings();`
- L177 _private prototype_ `void FireStatChanged(FPixelStreamingPlayerId PlayerId, FName StatName, float StatValue);`
- L178 _private prototype_ `void UpdateConsoleAutoComplete(TArray<FAutoCompleteCommand>& AutoCompleteList);`
- L179 _private prototype_ `void GraphValue_GameThread(FName InName, float Value, int InSamples, float InMinRange, float InMaxRange, float InRefValue);`
- L180 _private prototype_ `void AddCanvasTile_GameThread(FName Name, const FCanvasTileItem& Tile);`
- L183 _private member_ `static FStats* Instance;`
- L185 _private member_ `bool bRegisterEngineStats = false;`
- L187 _private member_ `mutable FCriticalSection PeerStatsCS;`
- L188 _private member_ `TMap<FPixelStreamingPlayerId, FPeerStats> PeerStats;`
- L190 _private member_ `mutable FCriticalSection ApplicationStatsCS;`
- L191 _private member_ `TMap<FName, FStoredStat> ApplicationStats;`
- L193 _private member_ `int64 LastTimeSettingsPolledCycles = 0;`
- L194 _private member_ `float RTCStatsPolledDelta = 0.0f;`
- L196 _private member_ `TMap<FName, FDebugGraph> Graphs;`
- L197 _private member_ `TMap<FName, FCanvasTileItem> Tiles;`
- L199 _private member_ `FCriticalSection StatNotificationCS;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L67 _function_ `FORCEINLINE uint32 GetTypeHash(const FStatData& Obj)` (scope `UE::PixelStreaming`)
- L150 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnStatsPolled);`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/Streamer.h` (Private)


#### class `UE::PixelStreaming::FStreamer`  
`class FStreamer : public IPixelStreamingStreamer, public TSharedFromThis<FStreamer>`  
_L21-156_
- inherits: `IPixelStreamingStreamer,TSharedFromThis<FStreamer>`
- L26 _public prototype_ `static TSharedPtr<FStreamer> Create(const FString& StreamerId);`
- L27 _public prototype_ `virtual ~FStreamer();`
- L29 _public prototype_ `virtual void SetStreamFPS(int32 InFramesPerSecond) override;`
- L30 _public prototype_ `virtual int32 GetStreamFPS() override;`
- L31 _public prototype_ `virtual void SetCoupleFramerate(bool bCouple) override;`
- L33 _public prototype_ `virtual void SetVideoInput(TSharedPtr<FPixelStreamingVideoInput> Input) override;`
- L34 _public prototype_ `virtual TWeakPtr<FPixelStreamingVideoInput> GetVideoInput() override;`
- L35 _public prototype_ `virtual void SetTargetViewport(TWeakPtr<SViewport> InTargetViewport) override;`
- L36 _public prototype_ `virtual TWeakPtr<SViewport> GetTargetViewport() override;`
- L37 _public prototype_ `virtual void SetTargetWindow(TWeakPtr<SWindow> InTargetWindow) override;`
- L38 _public prototype_ `virtual TWeakPtr<SWindow> GetTargetWindow() override;`
- L39 _public prototype_ `virtual void SetTargetScreenRect(TWeakPtr<FIntRect> InTargetScreenRect) override;`
- L40 _public prototype_ `virtual TWeakPtr<FIntRect> GetTargetScreenRect() override;`
- L42 _public prototype_ `virtual TWeakPtr<IPixelStreamingSignallingConnection> GetSignallingConnection() override;`
- L43 _public prototype_ `virtual void SetSignallingConnection(TSharedPtr<IPixelStreamingSignallingConnection> InSignallingConnection) override;`
- L44 _public prototype_ `virtual TWeakPtr<IPixelStreamingSignallingConnectionObserver> GetSignallingConnectionObserver() override;`
- L45 _public prototype_ `virtual void SetSignallingServerURL(const FString& InSignallingServerURL) override;`
- L46 _public prototype_ `virtual FString GetSignallingServerURL() override;`
- L47 _public function_ `virtual FString GetId() override`
- L48 _public prototype_ `virtual bool IsSignallingConnected() override;`
- L49 _public prototype_ `virtual void StartStreaming() override;`
- L50 _public prototype_ `virtual void StopStreaming() override;`
- L51 _public function_ `virtual bool IsStreaming() const override`
- L53 _public prototype_ `virtual FPreConnectionEvent& OnPreConnection() override;`
- L54 _public prototype_ `virtual FStreamingStartedEvent& OnStreamingStarted() override;`
- L55 _public prototype_ `virtual FStreamingStoppedEvent& OnStreamingStopped() override;`
- L57 _public prototype_ `virtual void ForceKeyFrame() override;`
- L58 _public prototype_ `void PushFrame();`
- L60 _public prototype_ `virtual void FreezeStream(UTexture2D* Texture) override;`
- L61 _public prototype_ `virtual void UnfreezeStream() override;`
- L63 _public prototype_ `virtual void SendPlayerMessage(uint8 Type, const FString& Descriptor) override;`
- L64 _public prototype_ `virtual void SendPlayerMessage(FPixelStreamingPlayerId PlayerId, uint8 Type, const FString& Descriptor) override;`
- L65 _public prototype_ `virtual void SendFileData(const TArray64<uint8>& ByteData, FString& MimeType, FString& FileExtension) override;`
- L66 _public prototype_ `virtual void KickPlayer(FPixelStreamingPlayerId PlayerId) override;`
- L67 _public prototype_ `virtual void SetPlayerLayerPreference(FPixelStreamingPlayerId PlayerId, int SpatialLayerId, int TemporalLayerId) override;`
- L68 _public prototype_ `virtual TArray<FPixelStreamingPlayerId> GetConnectedPlayers() override;`
- L70 _public function_ `virtual void SetInputHandler(TSharedPtr<IPixelStreamingInputHandler> InInputHandler) override`
- L71 _public function_ `virtual TWeakPtr<IPixelStreamingInputHandler> GetInputHandler() override`
- L72 _public prototype_ `virtual void SetInputHandlerType(EPixelStreamingInputType InputType) override;`
- L74 _public prototype_ `virtual IPixelStreamingAudioSink* GetPeerAudioSink(FPixelStreamingPlayerId PlayerId) override;`
- L75 _public prototype_ `virtual IPixelStreamingAudioSink* GetUnlistenedAudioSink() override;`
- L76 _public prototype_ `TSharedPtr<IPixelStreamingAudioInput> CreateAudioInput() override;`
- L77 _public prototype_ `void RemoveAudioInput(TSharedPtr<IPixelStreamingAudioInput> AudioInput) override;`
- L79 _public prototype_ `virtual void SetConfigOption(const FName& OptionName, const FString& Value) override;`
- L80 _public prototype_ `virtual bool GetConfigOption(const FName& OptionName, FString& OutValue) override;`
- L83 _public prototype_ `void AddPlayerConfig(TSharedRef<FJsonObject>& JsonObject);` — TODO(Luke) hook this back up so that the Engine can change how the interface is working browser side
- L85 _public prototype_ `virtual void PlayerRequestsBitrate(FPixelStreamingPlayerId PlayerId, int MinBitrate, int MaxBitrate) override;`
- L87 _public prototype_ `virtual void RefreshStreamBitrate() override;`
- L89 _public prototype_ `void ForEachPlayer(const TFunction<void(FPixelStreamingPlayerId, FPlayerContext)>& Func);`
- L92 _private prototype_ `FStreamer(const FString& StreamerId);`
- L94 _private prototype_ `bool CreateSession(FPixelStreamingPlayerId PlayerId);`
- L95 _private prototype_ `void AddStreams(FPixelStreamingPlayerId PlayerId);`
- L98 _private prototype_ `void OnProtocolUpdated();` — own methods
- L99 _private prototype_ `void ConsumeStats(FPixelStreamingPlayerId PlayerId, FName StatName, float StatValue);`
- L100 _private prototype_ `void OnOffer(FPixelStreamingPlayerId PlayerId, const FString& Sdp);`
- L101 _private prototype_ `void OnAnswer(FPixelStreamingPlayerId PlayerId, const FString& Sdp);`
- L102 _private prototype_ `void OnPlayerConnected(FPixelStreamingPlayerId PlayerId, const FPixelStreamingPlayerConfig& PlayerConfig, bool bSendOffer);`
- L103 _private prototype_ `void DeletePlayerSession(FPixelStreamingPlayerId PlayerId);`
- L104 _private prototype_ `void DeleteAllPlayerSessions();`
- L105 _private prototype_ `void AddNewDataChannel(FPixelStreamingPlayerId PlayerId, TSharedPtr<FPixelStreamingDataChannel> NewChannel);`
- L106 _private prototype_ `void OnDataChannelOpen(FPixelStreamingPlayerId PlayerId);`
- L107 _private prototype_ `void OnDataChannelClosed(FPixelStreamingPlayerId PlayerId);`
- L108 _private prototype_ `void OnDataChannelMessage(FPixelStreamingPlayerId PlayerId, uint8 Type, const webrtc::DataBuffer& RawBuffer);`
- L109 _private prototype_ `void SendInitialSettings(FPixelStreamingPlayerId PlayerId) const;`
- L110 _private prototype_ `void SendProtocol(FPixelStreamingPlayerId PlayerId) const;`
- L111 _private prototype_ `void SendPeerControllerMessages(FPixelStreamingPlayerId PlayerId) const;`
- L112 _private prototype_ `void SendLatencyReport(FPixelStreamingPlayerId PlayerId) const;`
- L113 _private prototype_ `bool ShouldPeerGenerateFrames(FPixelStreamingPlayerId PlayerId) const;`
- L115 _private prototype_ `void HandleSetQualityControllerRequest(const FPixelStreamingPlayerId& PlayerId);`
- L116 _private prototype_ `void SetQualityController(FPixelStreamingPlayerId PlayerId);`
- L117 _private prototype_ `void TriggerMouseLeave(FString InStreamerId);`
- L120 _private member_ `FString StreamerId;`
- L121 _private member_ `FString CurrentSignallingServerURL;`
- L123 _private member_ `TSharedPtr<IPixelStreamingInputHandler> InputHandler;`
- L124 _private member_ `TSharedPtr<IPixelStreamingSignallingConnection> SignallingServerConnection;`
- L125 _private member_ `TSharedPtr<IPixelStreamingSignallingConnectionObserver> Observer;`
- L127 _private member_ `double LastSignallingServerConnectionAttemptTimestamp = 0;`
- L129 _private member_ `webrtc::PeerConnectionInterface::RTCConfiguration PeerConnectionConfig;`
- L131 _private member_ `TSharedPtr<TThreadSafeMap<FPixelStreamingPlayerId, FPlayerContext>> Players;`
- L133 _private member_ `FPixelStreamingPlayerId QualityControllingId = INVALID_PLAYER_ID;`
- L134 _private member_ `FPixelStreamingPlayerId SFUPlayerId = INVALID_PLAYER_ID;`
- L135 _private member_ `FPixelStreamingPlayerId InputControllingId = INVALID_PLAYER_ID;`
- L137 _private member_ `bool bStreamingStarted = false;`
- L139 _private member_ `FPreConnectionEvent StreamingPreConnectionEvent;`
- L140 _private member_ `FStreamingStartedEvent StreamingStartedEvent;`
- L141 _private member_ `FStreamingStoppedEvent StreamingStoppedEvent;`
- L143 _private member_ `TUniquePtr<webrtc::SessionDescriptionInterface> SFULocalDescription;`
- L144 _private member_ `TUniquePtr<webrtc::SessionDescriptionInterface> SFURemoteDescription;`
- L146 _private member_ `TSharedPtr<FVideoSourceGroup> VideoSourceGroup;`
- L148 _private member_ `FDelegateHandle ConsumeStatsHandle;`
- L149 _private member_ `FDelegateHandle AllConnectionsClosedHandle;`
- L151 _private member_ `IPixelStreamingModule& Module;`
- L153 _private member_ `TSharedPtr<FFreezeFrame> FreezeFrame;`
- L155 _private member_ `TMap<FName, FString> ConfigOptions;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/ThreadSafeMap.h` (Private)


#### class `UE::PixelStreaming::TThreadSafeMap`  
`template <typename KeyType, typename ValueType> class TThreadSafeMap`  
_L13-124_
- L19 _private typedef_ `using InternalElementType = TSharedPtr<ValueType>;` — We add a level of indirection here so when the map changes the location of the ValueType does not change. This allows Find to return a pointer to the ValueType and release the lock and not worry that changes to the map will change the location of the ValueType pointed to.
- L20 _private member_ `TMap<KeyType, InternalElementType> InnerMap;`
- L21 _private member_ `mutable FCriticalSection Mutex;`
- L24 _private function_ `InternalElementType NewEmptyElement()` — Helpers for manipulating internal elements
- L25 _private function_ `InternalElementType NewElement(const ValueType& Value)`
- L26 _private function_ `ValueType* GetValuePtr(const InternalElementType& Element) const`
- L27 _private function_ `ValueType& GetValue(const InternalElementType& Element) const`
- L30 _public function_ `bool Add(KeyType Key, const ValueType& Value)`
- L41 _public function_ `bool Remove(KeyType Key)`
- L47 _public function_ `ValueType& GetOrAdd(KeyType Key)`
- L58 _public function_ `ValueType* Find(KeyType Key)`
- L68 _public function_ `const ValueType* Find(KeyType Key) const`
- L78 _public function_ `void Empty()`
- L84 _public function_ `bool IsEmpty() const`
- L92 _public function_ `template <typename T> void Apply(T&& Visitor)` — Note: Do not call a map method inside a visitor or you will deadlock
- L108 _public function_ `template <typename T> void ApplyUntil(T&& Visitor)` — Note: Do not call a map method inside a visitor or you will deadlock

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/ToStringExtensions.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L18 _function_ `inline FString ToString(const std::string& Str)` (scope `UE::PixelStreaming`)
- L23 _function_ `inline std::string ToString(const FString& Str)` (scope `UE::PixelStreaming`)
- L28 _function_ `inline FString ToString(const TSharedPtr<FJsonObject>& JsonObj, bool bPretty = true)` (scope `UE::PixelStreaming`)
- L44 _function_ `inline const TCHAR* ToString(webrtc::PeerConnectionInterface::SignalingState Val)` (scope `UE::PixelStreaming`)
- L58 _function_ `inline const TCHAR* ToString(webrtc::PeerConnectionInterface::IceConnectionState Val)` (scope `UE::PixelStreaming`)
- L78 _function_ `inline FString ToString(const webrtc::SessionDescriptionInterface& Sdp)` (scope `UE::PixelStreaming`)
- L85 _function_ `inline FString ToString(const webrtc::IceCandidateInterface& IceCandidate)` (scope `UE::PixelStreaming`)
- L92 _function_ `inline const TCHAR* ToString(webrtc::PeerConnectionInterface::IceGatheringState Val)` (scope `UE::PixelStreaming`)
- L108 _function_ `inline const TCHAR* ToString(webrtc::VideoFrameType FrameType)` (scope `UE::PixelStreaming`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/Utils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L14 _function_ `template <typename T> inline void CommandLineParseValue(const TCHAR* Match, TAutoConsoleVariable<T>& CVar)` (scope `UE::PixelStreaming`)
- L21 _function_ `inline void CommandLineParseValue(const TCHAR* Match, TAutoConsoleVariable<FString>& CVar, bool bStopOnSeparator = false)` (scope `UE::PixelStreaming`)
- L28 _function_ `inline void CommandLineParseOption(const TCHAR* Match, TAutoConsoleVariable<bool>& CVar)` (scope `UE::PixelStreaming`)
- L51 _function_ `template <typename T> void DoOnGameThread(T&& Func)` (scope `UE::PixelStreaming`)
- L59 _function_ `AsyncTask(ENamedThreads::GameThread, [Func]() { Func(); });` (scope `UE::PixelStreaming::DoOnGameThread`)
- L64 _function_ `template <typename T> void DoOnGameThreadAndWait(uint32 Timeout, T&& Func)` (scope `UE::PixelStreaming`)
- L73 _function_ `AsyncTask(ENamedThreads::GameThread, [Func, TaskEvent]() { Func(); TaskEvent->Trigger(); });` (scope `UE::PixelStreaming::DoOnGameThreadAndWait`)
- L82 _function_ `inline webrtc::SdpVideoFormat CreateH264Format(webrtc::H264Profile profile, webrtc::H264Level level)` (scope `UE::PixelStreaming`)
- L94 _function_ `inline void MemCpyStride(void* Dest, const void* Src, size_t DestStride, size_t SrcStride, size_t Height)` (scope `UE::PixelStreaming`)
- L105 _function_ `inline size_t SerializeToBuffer(rtc::CopyOnWriteBuffer& Buffer, size_t Pos, const void* Data, size_t DataSize)` (scope `UE::PixelStreaming`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/VideoDecoderFactory.h` (Private)


#### class `UE::PixelStreaming::FVideoDecoderFactory`  
`class FVideoDecoderFactory : public webrtc::VideoDecoderFactory`  
_L8-13_
- inherits: `webrtc::VideoDecoderFactory`
- L11 _public prototype_ `virtual std::vector<webrtc::SdpVideoFormat> GetSupportedFormats() const override;`
- L12 _public prototype_ `virtual std::unique_ptr<webrtc::VideoDecoder> CreateVideoDecoder(const webrtc::SdpVideoFormat& format) override;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/VideoDecoderHardware.h` (Private)


#### class `UE::PixelStreaming::FVideoDecoderHardware`  
`class FVideoDecoderHardware : public webrtc::VideoDecoder`  
_L13-31_
- inherits: `webrtc::VideoDecoder`
- L16 _public prototype_ `FVideoDecoderHardware(EPixelStreamingCodec Codec);`
- L17 _public prototype_ `virtual ~FVideoDecoderHardware() = default;`
- L19 _public prototype_ `virtual bool Configure(const Settings& settings) override;`
- L20 _public prototype_ `virtual int32 Decode(const webrtc::EncodedImage& input_image, bool missing_frames, int64_t render_time_ms) override;`
- L21 _public prototype_ `virtual int32 RegisterDecodeCompleteCallback(webrtc::DecodedImageCallback* callback) override;`
- L22 _public prototype_ `virtual int32 Release() override;`
- L23 _public function_ `virtual const char* ImplementationName() const`
- L26 _private member_ `TSharedPtr<TVideoDecoder<FVideoResourceRHI>> Decoder;`
- L28 _private member_ `webrtc::DecodedImageCallback* Output = nullptr;`
- L30 _private member_ `uint32 FrameCount = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/VideoDecoderSoftware.h` (Private)


#### class `UE::PixelStreaming::FVideoDecoderSoftware`  
`class FVideoDecoderSoftware : public webrtc::VideoDecoder`  
_L10-24_
- inherits: `webrtc::VideoDecoder`
- L13 _public prototype_ `FVideoDecoderSoftware(EPixelStreamingCodec Codec);`
- L14 _public prototype_ `virtual ~FVideoDecoderSoftware() = default;`
- L16 _public prototype_ `virtual bool Configure(const Settings& settings) override;`
- L17 _public prototype_ `virtual int32 Decode(const webrtc::EncodedImage& input_image, bool missing_frames, int64_t render_time_ms) override;`
- L18 _public prototype_ `virtual int32 RegisterDecodeCompleteCallback(webrtc::DecodedImageCallback* callback) override;`
- L19 _public prototype_ `virtual int32 Release() override;`
- L20 _public function_ `virtual const char* ImplementationName() const`
- L23 _private member_ `std::unique_ptr<webrtc::VideoDecoder> VideoDecoder;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/VideoDecoderStub.h` (Private)


#### class `UE::PixelStreaming::FVideoDecoderStub`  
`class FVideoDecoderStub : public webrtc::VideoDecoder`  
_L8-15_
- inherits: `webrtc::VideoDecoder`
- L11 _public function_ `virtual bool Configure(const Settings& settings) override`
- L12 _public function_ `virtual int32_t Decode(const webrtc::EncodedImage& input_image, bool missing_frames, int64_t render_time_ms) override`
- L13 _public function_ `virtual int32_t RegisterDecodeCompleteCallback(webrtc::DecodedImageCallback* callback) override`
- L14 _public function_ `virtual int32_t Release() override`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/VideoEncoderFactoryLayered.h` (Private)


#### class `UE::PixelStreaming::FVideoEncoderFactoryLayered`  
`class FVideoEncoderFactoryLayered : public webrtc::VideoEncoderFactory`  
_L15-37_
- inherits: `webrtc::VideoEncoderFactory`
- desc: The main encoder factory for pixel streaming. This should be the factory used for all of Pixel Streaming. Provides Pixel Streaming peers with FVideoEncoderLayered encoders, which should be used regardless of whether simulcast is being used or not.
- L18 _public prototype_ `FVideoEncoderFactoryLayered();`
- L19 _public prototype_ `virtual ~FVideoEncoderFactoryLayered();`
- L20 _public prototype_ `virtual std::vector<webrtc::SdpVideoFormat> GetSupportedFormats() const ;`
- L22 _public prototype_ `virtual CodecSupport QueryCodecSupport(const webrtc::SdpVideoFormat& format, absl::optional<std::string> scalability_mode) const override;`
- L24 _public prototype_ `virtual CodecInfo QueryVideoEncoder(const webrtc::SdpVideoFormat& format) const override;`
- L26 _public prototype_ `virtual std::unique_ptr<webrtc::VideoEncoder> CreateVideoEncoder(const webrtc::SdpVideoFormat& format);`
- L28 _public prototype_ `FVideoEncoderFactorySingleLayer* GetEncoderFactory(int StreamIndex);`
- L30 _public prototype_ `void ForceKeyFrame();`
- L33 _private member_ `TArray<TUniquePtr<FVideoEncoderFactorySingleLayer>> EncoderFactories;`
- L34 _private member_ `FCriticalSection EncoderFactoriesGuard;`
- L36 _private member_ `TUniquePtr<FVideoEncoderFactorySingleLayer> PrimaryEncoderFactory;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/VideoEncoderFactorySingleLayer.h` (Private)


#### class `UE::PixelStreaming::FVideoEncoderFactorySingleLayer`  
`class FVideoEncoderFactorySingleLayer : public webrtc::VideoEncoderFactory`  
_L23-91_
- inherits: `webrtc::VideoEncoderFactory`
- desc: An encoder factory for a single layer. Do not use this directly. Use FVideoEncoderFactoryLayered even when not using simulcast specifically.
- L26 _public prototype_ `FVideoEncoderFactorySingleLayer() = default;`
- L27 _public prototype_ `virtual ~FVideoEncoderFactorySingleLayer() override = default;`
- L29 _public prototype_ `virtual std::vector<webrtc::SdpVideoFormat> GetSupportedFormats() const override;`
- L33 _public prototype_ `virtual CodecSupport QueryCodecSupport(const webrtc::SdpVideoFormat& Format, absl::optional<std::string> scalability_mode) const override;` — Always returns our H264 hardware encoders codec_info for now/
- L35 _public prototype_ `virtual CodecInfo QueryVideoEncoder(const webrtc::SdpVideoFormat& Format) const override;`
- L39 _public prototype_ `virtual std::unique_ptr<webrtc::VideoEncoder> CreateVideoEncoder(const webrtc::SdpVideoFormat& Format) override;` — Always returns our H264 hardware encoder for now.
- L41 _public prototype_ `void ReleaseVideoEncoder(FVideoEncoderSingleLayerHardware* Encoder);`
- L43 _public prototype_ `void ForceKeyFrame();`
- L44 _public prototype_ `bool ShouldForceKeyframe() const;`
- L45 _public prototype_ `void UnforceKeyFrame();`
- L46 _public prototype_ `void OnEncodedImage(const webrtc::EncodedImage& Encoded_image, const webrtc::CodecSpecificInfo* CodecSpecificInfo, uint32 StreamId);`
- L49 _public function_ `template <typename ConfigType> TWeakPtr<TVideoEncoder<FVideoResourceRHI>> GetOrCreateHardwareEncoder(uint32 StreamId, const ConfigType& VideoConfig)`
- L77 _private prototype_ `void FreeUnusedEncoders();`
- L78 _private prototype_ `bool CheckEncoderSessionAvailable() const;`
- L80 _private member_ `TThreadSafeMap<uint32, TSharedPtr<FVideoEncoderHardware>> HardwareEncoders;`
- L82 _private member_ `uint8 bForceNextKeyframe : 1;`
- L86 _private member_ `TArray<FVideoEncoderSingleLayerHardware*> ActiveEncoders;` — Encoders assigned to each peer. Each one of these will be assigned to one of the hardware encoders raw pointers here because the factory interface wants a unique_ptr here so we cant own the object.
- L87 _private member_ `FCriticalSection ActiveEncodersGuard;`
- L90 _private member_ `FCriticalSection InitEncoderGuard;` — Init encoder guard

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L15 _typedef_ `using FVideoEncoderHardware = TVideoEncoder<FVideoResourceRHI>;` (scope `UE::PixelStreaming`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/VideoEncoderLayered.h` (Private)


#### class `UE::PixelStreaming::FVideoEncoderLayered`  
`class FVideoEncoderLayered : public webrtc::VideoEncoder`  
_L21-85_
- inherits: `webrtc::VideoEncoder`
- desc: A highly modified version of webrtc::simulcast_encoder_adapter The main video encoder for Pixel Streaming peers whether simulcast is being used or not. Will pull a FVideoEncoderSingleLayerXXX from the given factory.
- L24 _public prototype_ `FVideoEncoderLayered(FVideoEncoderFactoryLayered& InSimulcastFactory, const webrtc::SdpVideoFormat& format);`
- L28 _public prototype_ `int Release() override;` — Implements VideoEncoder.
- L29 _public prototype_ `int InitEncode(const webrtc::VideoCodec* codec_settings, const webrtc::VideoEncoder::Settings& settings) override;`
- L30 _public prototype_ `int Encode(const webrtc::VideoFrame& input_image, const std::vector<webrtc::VideoFrameType>* frame_types) override;`
- L31 _public prototype_ `int RegisterEncodeCompleteCallback(webrtc::EncodedImageCallback* callback) override;`
- L33 _public prototype_ `void SetRates(const RateControlParameters& parameters) override;`
- L34 _public prototype_ `void OnPacketLossRateUpdate(float packet_loss_rate) override;`
- L35 _public prototype_ `void OnRttUpdate(int64_t rtt_ms) override;`
- L36 _public prototype_ `void OnLossNotification(const LossNotification& loss_notification) override;`
- L41 _public prototype_ `webrtc::EncodedImageCallback::Result OnEncodedImage( size_t stream_idx, const webrtc::EncodedImage& encoded_image, const webrtc::CodecSpecificInfo* codec_specific_info);` — Eventual handler for the contained encoders' EncodedImageCallbacks, but called from an internal helper that also knows the correct stream index.
- L46 _public prototype_ `EncoderInfo GetEncoderInfo() const override;`
- L76 _private prototype_ `bool IsInitialized() const;`
- L78 _private member_ `TAtomic<bool> Initialized;`
- L79 _private member_ `FVideoEncoderFactoryLayered& SimulcastEncoderFactory;`
- L80 _private member_ `const webrtc::SdpVideoFormat VideoFormat;`
- L81 _private member_ `webrtc::VideoCodec CurrentCodec;`
- L82 _private member_ `FCriticalSection StreamInfosGuard;`
- L83 _private member_ `std::vector<StreamInfo> StreamInfos;`
- L84 _private member_ `webrtc::EncodedImageCallback* EncodedCompleteCallback;`

#### struct `UE::PixelStreaming::FVideoEncoderLayered::StreamInfo`  
`struct StreamInfo`  
_L49-74_
- L51 _public function_ `StreamInfo(std::unique_ptr<webrtc::VideoEncoder> InEncoder, std::unique_ptr<webrtc::EncodedImageCallback> InCallback, std::unique_ptr<webrtc::FramerateController> InFramerateController, uint16_t InWidth, uint16_t InHeight, bool bInKeyFrame, bool bInSendStream) : Encoder(std::move(InEncoder)) , Callback(std::move(InCallback)) , FramerateController(std::move(InFramerateController)) , Width(InWidth) , Height(InHeight) , KeyFrameRequest(bInKeyFrame) , bSendStream(bInSendStream)`
- L67 _public member_ `std::unique_ptr<webrtc::VideoEncoder> Encoder;`
- L68 _public member_ `std::unique_ptr<webrtc::EncodedImageCallback> Callback;`
- L69 _public member_ `std::unique_ptr<webrtc::FramerateController> FramerateController;`
- L70 _public member_ `uint16_t Width;`
- L71 _public member_ `uint16_t Height;`
- L72 _public member_ `bool KeyFrameRequest;`
- L73 _public member_ `bool bSendStream;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace webrtc`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/VideoEncoderSingleLayerHardware.h` (Private)


#### class `UE::PixelStreaming::FVideoEncoderSingleLayerHardware`  
`class FVideoEncoderSingleLayerHardware : public webrtc::VideoEncoder`  
_L16-70_
- inherits: `webrtc::VideoEncoder`
- desc: A hardware encoder for a single layer of a frame.
- L19 _public prototype_ `FVideoEncoderSingleLayerHardware(FVideoEncoderFactorySingleLayer& InFactory, EPixelStreamingCodec Codec);`
- L23 _public prototype_ `virtual int InitEncode(webrtc::VideoCodec const* codec_settings, webrtc::VideoEncoder::Settings const& settings) override;` — WebRTC Interface
- L24 _public prototype_ `virtual int32 RegisterEncodeCompleteCallback(webrtc::EncodedImageCallback* callback) override;`
- L25 _public prototype_ `virtual int32 Release() override;`
- L26 _public prototype_ `virtual int32 Encode(webrtc::VideoFrame const& frame, std::vector<webrtc::VideoFrameType> const* frame_types) override;`
- L27 _public prototype_ `virtual void SetRates(RateControlParameters const& parameters) override;`
- L28 _public prototype_ `virtual webrtc::VideoEncoder::EncoderInfo GetEncoderInfo() const override;`
- L37 _public prototype_ `void SendEncodedImage(webrtc::EncodedImage const& encoded_image, webrtc::CodecSpecificInfo const* codec_specific_info, uint32 StreamId);`
- L40 _private prototype_ `void LateInitHardwareEncoder(uint32 StreamId);`
- L41 _private prototype_ `void UpdateConfig(uint32 width, uint32 height);`
- L42 _private prototype_ `void MaybeDumpFrame(webrtc::EncodedImage const& encoded_image);`
- L44 _private prototype_ `void UpdateFrameMetadataPreEncode(IPixelCaptureOutputFrame& Frame);`
- L45 _private prototype_ `void UpdateFrameMetadataPostEncode(IPixelCaptureOutputFrame& Frame);`
- L46 _private prototype_ `void UpdateFrameMetadataPrePacketization(IPixelCaptureOutputFrame& Frame);`
- L47 _private prototype_ `void UpdateFrameMetadataPostPacketization(IPixelCaptureOutputFrame& Frame);`
- L48 _private prototype_ `webrtc::VideoFrame WrapAdaptedFrame(const webrtc::VideoFrame& ExistingFrame, const IPixelCaptureOutputFrame& AdaptedLayer);`
- L50 _private member_ `FVideoEncoderFactorySingleLayer& Factory;`
- L51 _private member_ `EPixelStreamingCodec Codec;`
- L53 _private member_ `TUniquePtr<FVideoEncoderConfig> InitialVideoConfig;`
- L54 _private member_ `TWeakPtr<FVideoEncoderHardware> HardwareEncoder;`
- L57 _private member_ `int32 WebRtcProposedTargetBitrate = 5000000;` — We store this so we can restore back to it if the user decides to use then stop using the PixelStreaming.Encoder.TargetBitrate CVar.
- L59 _private member_ `webrtc::EncodedImageCallback* OnEncodedImageCallback = nullptr;`
- L63 _private member_ `TOptional<RateControlParameters> PendingRateChange;` — WebRTC may request a bitrate/framerate change using SetRates(), we only respect this if this encoder is actually encoding so we use this optional object to store a rate change and act upon it when this encoder does its next call to Encode().
- L66 _private member_ `uint32 EncodingStreamId;` — used to key into active hardware encoders and pull the correct encoder for the stream.
- L69 _private member_ `uint64 LastEncodedFrameId = 0;` — Used to track how often we encode the same frame

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/VideoEncoderSingleLayerVPX.h` (Private)


#### class `UE::PixelStreaming::FVideoEncoderSingleLayerVPX`  
`class FVideoEncoderSingleLayerVPX : public webrtc::VideoEncoder`  
_L12-32_
- inherits: `webrtc::VideoEncoder`
- desc: A VPX encoder for a single layer of a frame.
- L15 _public prototype_ `FVideoEncoderSingleLayerVPX(int VPXVersion);`
- L16 _public prototype_ `virtual ~FVideoEncoderSingleLayerVPX() = default;`
- L19 _public prototype_ `virtual int InitEncode(webrtc::VideoCodec const* codec_settings, webrtc::VideoEncoder::Settings const& settings) override;` — WebRTC Interface
- L20 _public prototype_ `virtual int32 RegisterEncodeCompleteCallback(webrtc::EncodedImageCallback* callback) override;`
- L21 _public prototype_ `virtual int32 Release() override;`
- L22 _public prototype_ `virtual int32 Encode(webrtc::VideoFrame const& frame, std::vector<webrtc::VideoFrameType> const* frame_types) override;`
- L23 _public prototype_ `virtual void SetRates(RateControlParameters const& parameters) override;`
- L24 _public prototype_ `virtual webrtc::VideoEncoder::EncoderInfo GetEncoderInfo() const override;`
- L27 _private prototype_ `void UpdateFrameMetadataPreEncode(IPixelCaptureOutputFrame& Frame);`
- L28 _private prototype_ `void UpdateFrameMetadataPostEncode(IPixelCaptureOutputFrame& Frame);`
- L29 _private prototype_ `webrtc::VideoFrame WrapAdaptedFrame(const webrtc::VideoFrame& ExistingFrame, const IPixelCaptureOutputFrame& AdaptedLayer);`
- L31 _private member_ `std::unique_ptr<webrtc::VideoEncoder> WebRTCVPXEncoder;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/VideoSource.h` (Private)


#### class `UE::PixelStreaming::FVideoSource`  
`class FVideoSource : public FAdaptedVideoTrackSource`  
_L21-46_
- inherits: `FAdaptedVideoTrackSource`
- desc: A source of video frames for a WebRTC peer. Has a video input which will provide frame data to this source. The source will then pass that data to an adapter which will have one or many adapt processes that are provided by the input object and are responsible for converting the frame data to the format required for the selected video encoder. This video source should be contained within a FVideoSourceGroup which is responsible for telling each source to push a frame to WebRTC at the expected rate. This source will make sure that the adapter has valid output and if so will create a frame for WebRTC. Otherwise it will continue to wait until the next frame.
- L24 _public prototype_ `FVideoSource(bool bInRequiresUniqueId, TSharedPtr<FPixelStreamingVideoInput> InVideoInput, const TFunction<bool()>& InShouldGenerateFramesCheck);`
- L25 _public prototype_ `virtual ~FVideoSource() = default;`
- L27 _public prototype_ `void MaybePushFrame();`
- L30 _public function_ `virtual webrtc::MediaSourceInterface::SourceState state() const override` — Begin UE::PixelStreaming::AdaptedVideoTrackSource overrides
- L31 _public function_ `virtual bool remote() const override`
- L32 _public function_ `virtual bool is_screencast() const override`
- L33 _public function_ `virtual absl::optional<bool> needs_denoising() const override`
- L37 _private member_ `webrtc::MediaSourceInterface::SourceState CurrentState;`
- L38 _private member_ `TSharedPtr<FPixelStreamingVideoInput> VideoInput;`
- L39 _private member_ `TFunction<bool()> ShouldGenerateFramesCheck;`
- L40 _private member_ `uint32 StreamId;`
- L41 _private member_ `bool bRequireUniqueId;`
- L43 _private prototype_ `void SetStreamId(rtc::scoped_refptr<webrtc::VideoFrameBuffer> FrameBuffer) const;`
- L44 _private prototype_ `void PushFrame();`
- L45 _private prototype_ `void PushEmptyFrame();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/VideoSourceGroup.h` (Private)


#### class `UE::PixelStreaming::FVideoSourceGroup`  
`class FVideoSourceGroup : public TSharedFromThis<FVideoSourceGroup>`  
_L15-90_
- inherits: `TSharedFromThis<FVideoSourceGroup>`
- L18 _public prototype_ `static TSharedPtr<FVideoSourceGroup> Create();`
- L19 _public prototype_ `~FVideoSourceGroup();`
- L21 _public prototype_ `void SetVideoInput(TSharedPtr<FPixelStreamingVideoInput> InVideoInput);`
- L22 _public function_ `TSharedPtr<FPixelStreamingVideoInput> GetVideoInput()`
- L23 _public prototype_ `void SetFPS(int32 InFramesPerSecond);`
- L24 _public prototype_ `int32 GetFPS();`
- L26 _public prototype_ `void SetCoupleFramerate(bool Couple);`
- L28 _public prototype_ `rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> CreateVideoSource(bool bInRequireUniqueId, const TFunction<bool()>& InShouldGenerateFramesCheck);`
- L29 _public prototype_ `void RemoveVideoSource(const webrtc::VideoTrackSourceInterface* ToRemove);`
- L30 _public prototype_ `void RemoveAllVideoSources();`
- L32 _public prototype_ `void Start();`
- L33 _public prototype_ `void Stop();`
- L34 _public prototype_ `void Tick();`
- L35 _public function_ `bool IsThreadRunning() const`
- L38 _private prototype_ `FVideoSourceGroup();`
- L40 _private prototype_ `void StartThread();`
- L41 _private prototype_ `void StopThread();`
- L42 _private prototype_ `void CheckStartStopThread();`
- L43 _private prototype_ `void OnFrameCaptured();`
- L78 _private member_ `bool bRunning = false;`
- L79 _private member_ `bool bThreadRunning = false;`
- L80 _private member_ `bool bCoupleFramerate = false;`
- L81 _private member_ `int32 FramesPerSecond = 30;`
- L82 _private member_ `TSharedPtr<FPixelStreamingVideoInput> VideoInput;`
- L83 _private member_ `TUniquePtr<FFrameThread> FrameRunnable;`
- L84 _private member_ `FRunnableThread* FrameThread = nullptr;` — constant FPS tick thread
- L85 _private member_ `TArray<rtc::scoped_refptr<FVideoSource>> VideoSources;`
- L87 _private member_ `FDelegateHandle FrameDelegateHandle;`
- L89 _private member_ `mutable FCriticalSection CriticalSection;`

#### class `UE::PixelStreaming::FVideoSourceGroup::FFrameThread`  
`class FFrameThread : public FRunnable, public FSingleThreadRunnable`  
_L45-76_
- inherits: `FRunnable,FSingleThreadRunnable`
- L48 _public function_ `FFrameThread(TWeakPtr<FVideoSourceGroup> InVideoSourceGroup) : OuterVideoSourceGroup(InVideoSourceGroup)`
- L52 _public prototype_ `virtual ~FFrameThread() = default;`
- L54 _public prototype_ `virtual bool Init() override;`
- L55 _public prototype_ `virtual uint32 Run() override;`
- L56 _public prototype_ `virtual void Stop() override;`
- L57 _public prototype_ `virtual void Exit() override;`
- L59 _public function_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override`
- L65 _public prototype_ `virtual void Tick() override;`
- L67 _public prototype_ `void PushFrame(TSharedPtr<FVideoSourceGroup> VideoSourceGroup);`
- L68 _public prototype_ `double CalculateSleepOffsetMs(double TargetSubmitMs, uint64 LastCaptureCycles, uint64 CyclesBetweenCaptures, bool& bResetOffset) const;`
- L70 _public member_ `bool bIsRunning = false;`
- L71 _public member_ `TWeakPtr<FVideoSourceGroup> OuterVideoSourceGroup = nullptr;`
- L72 _public member_ `uint64 LastSubmitCycles = 0;`
- L75 _public member_ `FEventRef FrameEvent;` — Use this event to signal when we should wake and also how long we should sleep for between transmitting a frame.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/WebRTCIncludes.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Private/WebRTCLogging.h` (Private)


#### Free symbols / members of external scopes

- L21 _prototype_ `void RedirectWebRtcLogsToUnreal(rtc::LoggingSeverity Verbosity);`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/IPixelStreamingAudioConsumer.h` (Public)


#### class `IPixelStreamingAudioConsumer`  
`class IPixelStreamingAudioConsumer`  
_L8-16_
- desc: Interface for consuming audio coming in from the browser.
- L11 _public function_ `IPixelStreamingAudioConsumer()`
- L12 _public function_ `virtual ~IPixelStreamingAudioConsumer()`
- L13 _public prototype_ `virtual void ConsumeRawPCM(const int16_t* AudioData, int InSampleRate, size_t NChannels, size_t NFrames) = 0;`
- L14 _public prototype_ `virtual void OnConsumerAdded() = 0;`
- L15 _public prototype_ `virtual void OnConsumerRemoved() = 0;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/IPixelStreamingAudioInput.h` (Public)


#### class `IPixelStreamingAudioInput`  
`class IPixelStreamingAudioInput`  
_L7-15_
- L10 _public function_ `IPixelStreamingAudioInput()`
- L11 _public function_ `virtual ~IPixelStreamingAudioInput()`
- L14 _public prototype_ `virtual void PushAudio(const float* InBuffer, int32 NumSamples, int32 NumChannels, int32 SampleRate) = 0;` — Pushes audio, which must match the underlying sample rate/num channels of the mixer.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/IPixelStreamingAudioSink.h` (Public)


#### class `IPixelStreamingAudioSink`  
`class IPixelStreamingAudioSink : public webrtc::AudioTrackSinkInterface`  
_L10-18_
- inherits: `webrtc::AudioTrackSinkInterface`
- desc: Interface for a sink that collects audio coming in from the browser and passes into into UE's audio system.
- L13 _public function_ `IPixelStreamingAudioSink()`
- L14 _public function_ `virtual ~IPixelStreamingAudioSink()`
- L15 _public prototype_ `virtual void AddAudioConsumer(IPixelStreamingAudioConsumer* AudioConsumer) = 0;`
- L16 _public prototype_ `virtual void RemoveAudioConsumer(IPixelStreamingAudioConsumer* AudioConsumer) = 0;`
- L17 _public prototype_ `virtual bool HasAudioConsumers() = 0;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/IPixelStreamingModule.h` (Public)


#### class `IPixelStreamingModule`  
`class IPixelStreamingModule : public IModuleInterface`  
_L22-185_
- inherits: `IModuleInterface`
- desc: The public interface of the Pixel Streaming module.
- L31 _public function_ `static inline IPixelStreamingModule& Get()` — Singleton-like access to this module's interface. Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L41 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded. @return True if the module is loaded.
- L50 _public prototype_ `virtual void SetCodec(EPixelStreamingCodec Codec) = 0;` — Sets the encoder codec for the whole Pixel Streaming module. Should be called before any streaming starts. @param Codec A valid EPixelStreamingCodec value.
- L56 _public prototype_ `virtual EPixelStreamingCodec GetCodec() const = 0;` — Gets the currently selected encoder codec for all of Pixel Streaming. @return A valid EPixelStreamingCodec value.
- L61 _public prototype_ `DECLARE_EVENT_OneParam(IPixelStreamingModule, FReadyEvent, IPixelStreamingModule&);` — Event fired when internal streamer is initialized and the methods on this module are ready for use.
- L67 _public prototype_ `virtual FReadyEvent& OnReady() = 0;` — A getter for the OnReady event. Intent is for users to call IPixelStreamingModule::Get().OnReady().AddXXX. @return The bindable OnReady event.
- L73 _public prototype_ `virtual bool IsReady() = 0;` — Is the PixelStreaming module actually ready to use? Is the streamer created. @return True if Pixel Streaming module methods are ready for use.
- L78 _public prototype_ `virtual bool StartStreaming() = 0;` — Starts streaming on all streamers.
- L83 _public prototype_ `virtual void StopStreaming() = 0;` — Stops all streamers from streaming.
- L89 _public prototype_ `virtual TSharedPtr<IPixelStreamingStreamer> CreateStreamer(const FString& StreamerId) = 0;` — Creates a new streamer. @param StreamerId - The ID of the Streamer to be created.
- L95 _public prototype_ `virtual TArray<FString> GetStreamerIds() = 0;` — Returns a TArray containing the keys to the currently held streamers. @return TArray containing the keys to the currently held streamers.
- L101 _public prototype_ `virtual TSharedPtr<IPixelStreamingStreamer> FindStreamer(const FString& StreamerId) = 0;` — Find a streamer by an ID. @return A pointer to the interface for a streamer. nullptr if the streamer isn't found
- L108 _public prototype_ `virtual TSharedPtr<IPixelStreamingStreamer> DeleteStreamer(const FString& StreamerId) = 0;` — Remove a streamer by an ID @param StreamerId	-	The ID of the streamer to be removed. @return The removed streamer. nullptr if the streamer wasn't found.
- L114 _public prototype_ `virtual void DeleteStreamer(TSharedPtr<IPixelStreamingStreamer> ToBeDeleted) = 0;` — Remove a streamer by its pointer @param ToBeDeleted The streamer to remove from the internal management.
- L120 _public prototype_ `virtual void SetExternalVideoSourceFPS(uint32 InFPS) = 0;` — Sets the target FPS for Externally Consumed video Tracks @param InFPS new FPS for the ExternalVideoSource to output at.
- L126 _public prototype_ `virtual void SetExternalVideoSourceCoupleFramerate(bool bShouldCoupleFPS) = 0;` — Control coupling the external video source framerate to the video input framerate @param bShouldCoupleFPS Flag for coupling the video source and video input framerates
- L131 _public prototype_ `virtual void SetExternalVideoSourceInput(TSharedPtr<FPixelStreamingVideoInput> InVideoInput) = 0;` — Hook to set the input to the external video source. Will also call Start() on the external video source
- L136 _public prototype_ `virtual rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> CreateExternalVideoSource() = 0;` — Allows the creation of Video Tracks that are fed the backbuffer
- L141 _public prototype_ `virtual void ReleaseExternalVideoSource(const webrtc::VideoTrackSourceInterface* InVideoSource) = 0;` — Used to clean up sources no longer needed
- L147 _public prototype_ `virtual void AddInputComponent(UPixelStreamingInput* InInputComponent) = 0;` — Tell the input device about a new pixel streaming input component. @param InInputComponent - The new pixel streaming input component.
- L153 _public prototype_ `virtual void RemoveInputComponent(UPixelStreamingInput* InInputComponent) = 0;` — Tell the input device that a pixel streaming input component is no longer relevant. @param InInputComponent - The pixel streaming input component which is no longer relevant.
- L159 _public prototype_ `virtual const TArray<UPixelStreamingInput*> GetInputComponents() = 0;` — Get the input components currently attached to Pixel Streaming. @return An array of input components.
- L165 _public prototype_ `virtual TUniquePtr<webrtc::VideoEncoderFactory> CreateVideoEncoderFactory() = 0;` — Create a webrtc::VideoEncoderFactory pointer. @return A WebRTC video encoder factory with its encoders populated by Pixel Streaming.
- L171 _public prototype_ `virtual FString GetDefaultStreamerID() = 0;` — Get the Default Streamer ID @return FString The default streamer ID
- L177 _public prototype_ `virtual FString GetDefaultSignallingURL() = 0;` — Get the Default Signaling URL ("ws://127.0.0.1:8888") @return FString The default signaling url ("ws://127.0.0.1:8888")
- L184 _public prototype_ `virtual void ForEachStreamer(const TFunction<void(TSharedPtr<IPixelStreamingStreamer>)>& Func) = 0;` — @brief A method for iterating through all of the streamers on the module @param Func The lambda to execute with each streamer

#### Free symbols / members of external scopes

- L61 _delegate_ `DECLARE_EVENT_OneParam(IPixelStreamingModule, FReadyEvent, IPixelStreamingModule&);` — Event fired when internal streamer is initialized and the methods on this module are ready for use.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/IPixelStreamingSignallingConnection.h` (Public)


#### class `IPixelStreamingSignallingConnection`  
`class IPixelStreamingSignallingConnection`  
_L14-124_
- desc: A specialized signalling server connection object for Pixel Streaming signalling servers.
- L18 _public function_ `virtual ~IPixelStreamingSignallingConnection()`
- L24 _public prototype_ `virtual void TryConnect(FString URL) = 0;` — Connect to a specified signalling server at ths given URL @param URL The url of the destination signalling server.
- L30 _public prototype_ `virtual void Disconnect() = 0;` — `UE_DEPRECATED(5.4, "Disconnect has been deprecated and will be removed in future versions. Please use: Disconnect(FString Reason)")` — Disconnects from the signalling server. Safe to call even when not connected.
- L35 _public prototype_ `virtual void Disconnect(FString Reason) = 0;` — Disconnects from the signalling server with a reason message. Safe to call even when not connected.
- L41 _public prototype_ `virtual bool IsConnected() const = 0;` — Checks if the connection is established. @returns True when the signalling server is connected.
- L48 _public prototype_ `virtual void SendOffer(FPixelStreamingPlayerId PlayerId, const webrtc::SessionDescriptionInterface& SDP) = 0;` — [Streamer only] Sends an offer to the specified player. @param PlayerId The Id of the destination player. @param SDP The offer session description for the player.
- L55 _public prototype_ `virtual void SendAnswer(FPixelStreamingPlayerId PlayerId, const webrtc::SessionDescriptionInterface& SDP) = 0;` — [Streamer only] Sends an answer to the specified player. @param PlayerId The Id of the destination player. @param SDP The answer session description for the player.
- L62 _public prototype_ `virtual void SendIceCandidate(FPixelStreamingPlayerId PlayerId, const webrtc::IceCandidateInterface& IceCandidate) = 0;` — [Streamer only] Sends ice candidate information to the specified player. @param PlayerId The Id of the destination player. @param IceCandidate The ice candidate information to send.
- L69 _public prototype_ `virtual void SendDisconnectPlayer(FPixelStreamingPlayerId PlayerId, const FString& Reason) = 0;` — [Streamer only] Send a disconnect message to the specified player. @param PlayerId The Id of the destination player. @param Reason An optional reason for the disconnection.
- L74 _public prototype_ `virtual void RequestStreamerList() = 0;` — Request a list of active streamers from the signalling server. This is a request to the signalling server so can be used by anyone.
- L80 _public prototype_ `virtual void SendSubscribe(const FString& StreamerId) = 0;` — [Stream receiver only] Send a subscription request to the signalling server. @param StreamerId The ID of the streamer to subscribe to.
- L85 _public prototype_ `virtual void SendUnsubscribe() = 0;` — [Stream receiver only] Send an unsubscribe request to the signalling server.
- L91 _public prototype_ `virtual void SendOffer(const webrtc::SessionDescriptionInterface& SDP) = 0;` — [Stream receiver only] Sends an offer to the streamer. @param SDP The local description offer.
- L97 _public prototype_ `virtual void SendAnswer(const webrtc::SessionDescriptionInterface& SDP) = 0;` — [Stream receiver only] Sends an answer back to the streamer after receiving an offer. @param SDP The local description answer.
- L103 _public prototype_ `virtual void SendIceCandidate(const webrtc::IceCandidateInterface& IceCandidate) = 0;` — [Stream receiver only] Sends ICE candidate information to the streamer. @param IceCandidate The ICE candidate information.
- L111 _public prototype_ `virtual void SetKeepAlive(bool bKeepAlive) = 0;` — Enables or disables the keep alive pings on this connection. Receiving connections should disable the keep alive since the reference signalling server will reject pings from players and close the connection. @param bKeepAlive True to enable keep alive pings. False to disable.
- L117 _public prototype_ `virtual void SetAutoReconnect(bool bAutoReconnect) = 0;` — Toggles automatic reconnecting when websocket is closed or unreachable. @param bAutoReconnect True to enable auto reconnect. False to disable.
- L123 _public prototype_ `virtual void SendMessage(const FString& Msg) = 0;` — Send a message to the signalling server. @param Msg A string message to send - typically a JSON payload.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/IPixelStreamingSignallingConnectionObserver.h` (Public)


#### class `IPixelStreamingSignallingConnectionObserver`  
`class IPixelStreamingSignallingConnectionObserver`  
_L10-32_
- desc: callback interface for `FPixelStreamingSignallingConnection`
- L13 _public prototype_ `virtual void OnSignallingConnected() = 0;`
- L14 _public prototype_ `virtual void OnSignallingDisconnected(int32 StatusCode, const FString& Reason, bool bWasClean) = 0;`
- L15 _public prototype_ `virtual void OnSignallingError(const FString& ErrorMsg) = 0;`
- L16 _public prototype_ `virtual void OnSignallingConfig(const webrtc::PeerConnectionInterface::RTCConfiguration& Config) = 0;`
- L19 _public prototype_ `virtual void OnSignallingSessionDescription(FPixelStreamingPlayerId PlayerId, webrtc::SdpType Type, const FString& Sdp) = 0;` — Streamer-only
- L20 _public prototype_ `virtual void OnSignallingRemoteIceCandidate(FPixelStreamingPlayerId PlayerId, const FString& SdpMid, int SdpMLineIndex, const FString& Sdp) = 0;`
- L21 _public prototype_ `virtual void OnSignallingPlayerConnected(FPixelStreamingPlayerId PlayerId, const FPixelStreamingPlayerConfig& PlayerConfig, bool bSendOffer) = 0;`
- L22 _public prototype_ `virtual void OnSignallingPlayerDisconnected(FPixelStreamingPlayerId PlayerId) = 0;`
- L23 _public prototype_ `virtual void OnSignallingSFUPeerDataChannels(FPixelStreamingPlayerId SFUId, FPixelStreamingPlayerId PlayerId, int32 SendStreamId, int32 RecvStreamId) = 0;`
- L24 _public prototype_ `virtual void OnPlayerRequestsBitrate(FPixelStreamingPlayerId PlayerId, int MinBitrate, int MaxBitrate) = 0;`
- L27 _public prototype_ `virtual void OnSignallingStreamerList(const TArray<FString>& StreamerList) = 0;` — Player-only
- L28 _public prototype_ `virtual void OnSignallingSessionDescription(webrtc::SdpType Type, const FString& Sdp) = 0;`
- L29 _public prototype_ `virtual void OnSignallingRemoteIceCandidate(const FString& SdpMid, int SdpMLineIndex, const FString& Sdp) = 0;`
- L30 _public prototype_ `virtual void OnSignallingPlayerCount(uint32 Count) = 0;`
- L31 _public prototype_ `virtual void OnSignallingPeerDataChannels(int32 SendStreamId, int32 RecvStreamId) = 0;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/IPixelStreamingStats.h` (Public)


#### class `IPixelStreamingStats`  
`class IPixelStreamingStats`  
_L11-30_
- L18 _public prototype_ `static IPixelStreamingStats& Get();` — Singleton-like access to the Pixel Streaming stats public API. @return Returns singleton instance of Pixel Streaming stats.
- L29 _public prototype_ `virtual void GraphValue(FName InName, float Value, int InSamples, float InMinRange, float InMaxRange, float InRefValue = 0.0f) = 0;` — Graphs a value in a real-time plot that is visible when `stat PixelStreamingGraphs` is used. If a graph of this name has not been graphed before this will also create the graph internally. @param InName The name of the stat to graph, this is used in the graph title and must be unique. @param InSamples The number of samples (along the x-axis) we wish to graph. @param InMinRange The minimum value we expect for this value we are graphing. @param InMaxRange The maximum value we expect for this value we are graphing. @param InRefValue A reference value that we draw in the graph as a horizontal line, this can be useful to see if we are within some threshold.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/IPixelStreamingStreamer.h` (Public)


#### class `IPixelStreamingStreamer`  
`class IPixelStreamingStreamer`  
_L20-306_
- L23 _public prototype_ `virtual ~IPixelStreamingStreamer() = default;`
- L29 _public prototype_ `virtual void SetStreamFPS(int32 InFramesPerSecond) = 0;` — @brief Set the Stream FPS @param InFramesPerSecond The number of frames per second the streamer will stream at
- L35 _public prototype_ `virtual int32 GetStreamFPS() = 0;` — @brief Get the Stream FPS @return - The number of frames per second the streamer will stream at
- L43 _public prototype_ `virtual void SetCoupleFramerate(bool bCouple) = 0;` — Setting this to true will cause the streamer to ignore the FPS value and instead push out frames as they are submitted from the video input. If the encode process takes longer than the time between frames, frames will be dropped. @param bCouple true to couple the streamer framerate to that of the video input.
- L49 _public prototype_ `virtual void SetVideoInput(TSharedPtr<FPixelStreamingVideoInput> Input) = 0;` — @brief Set the Video Input object @param Input The FPixelStreamingVideoInput that this streamer will stream
- L55 _public prototype_ `virtual TWeakPtr<FPixelStreamingVideoInput> GetVideoInput() = 0;` — @brief Get the Video Input object @return The FPixelStreamingVideoInput that this streamer will stream
- L61 _public prototype_ `virtual void SetTargetViewport(TWeakPtr<SViewport> InTargetViewport) = 0;` — @brief Set the Target Viewport for this streamer. This is used to ensure input between the browser and application scales correctly @param InTargetViewport The target viewport
- L67 _public prototype_ `virtual TWeakPtr<SViewport> GetTargetViewport() = 0;` — @brief Get the Target Viewport for this streamer @return The target viewport
- L74 _public prototype_ `virtual void SetTargetWindow(TWeakPtr<SWindow> InTargetWindow) = 0;` — @brief Set the target window for this streamer. This is used to ensure mouse events are directed to the correct window if multiple windows are tiled on top of one another as seen in the editor @param InTargetWindow The target window
- L80 _public prototype_ `virtual TWeakPtr<SWindow> GetTargetWindow() = 0;` — @brief Get the target window for this streamer @return The target window
- L87 _public prototype_ `virtual void SetTargetScreenRect(TWeakPtr<FIntRect> InTargetScreenRect) = 0;` — @brief Set the target screen rectangle for this streamer. This is used to when the streamer doesn't have a singular target window / viewport and as such we just use the manual scale @param InTargetScreenRect The target screen rectangle
- L93 _public prototype_ `virtual TWeakPtr<FIntRect> GetTargetScreenRect() = 0;` — @brief Get the target screen rectangle for this streamer @return The target screen rectangle
- L99 _public prototype_ `virtual void SetSignallingServerURL(const FString& InSignallingServerURL) = 0;` — @brief Set the Signalling Server URL @param InSignallingServerURL
- L105 _public prototype_ `virtual FString GetSignallingServerURL() = 0;` — @brief Get the Signalling Server URL @return The Signalling Server URL
- L111 _public prototype_ `virtual FString GetId() = 0;` — @brief Get this streamer's ID
- L116 _public prototype_ `virtual bool IsSignallingConnected() = 0;` — @return True if the streamer is connected to the signalling mechanism (e.g. websocket for signalling server).
- L121 _public prototype_ `virtual void StartStreaming() = 0;` — @brief Start streaming this streamer
- L126 _public prototype_ `virtual void StopStreaming() = 0;` — @brief Stop this streamer from streaming
- L133 _public prototype_ `virtual bool IsStreaming() const = 0;` — @brief Get the current state of this streamer @return true @return false
- L138 _public prototype_ `DECLARE_EVENT_OneParam(IPixelStreamingStreamer, FPreConnectionEvent, IPixelStreamingStreamer*);` — @brief Event fired just before the streamer begins connecting to signalling.
- L144 _public prototype_ `virtual FPreConnectionEvent& OnPreConnection() = 0;` — @brief A getter for the OnPreConnection event. Intent is for users to call IPixelStreamingModule::Get().FindStreamer(ID)->OnPreConnection().AddXXX. @return - The bindable OnPreConnection event.
- L149 _public prototype_ `DECLARE_EVENT_OneParam(IPixelStreamingStreamer, FStreamingStartedEvent, IPixelStreamingStreamer*);` — @brief Event fired when the streamer has connected to a signalling server and is ready for peers.
- L155 _public prototype_ `virtual FStreamingStartedEvent& OnStreamingStarted() = 0;` — @brief A getter for the OnStreamingStarted event. Intent is for users to call IPixelStreamingModule::Get().FindStreamer(ID)->OnStreamingStarted().AddXXX. @return - The bindable OnStreamingStarted event.
- L160 _public prototype_ `DECLARE_EVENT_OneParam(IPixelStreamingStreamer, FStreamingStoppedEvent, IPixelStreamingStreamer*);` — @brief Event fired when the streamer has disconnected from a signalling server and has stopped streaming.
- L165 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInputReceived, FPixelStreamingPlayerId, uint8, TArray<uint8>);` — Broadcast when data comes in from the data channel.
- L166 _public member_ `FOnInputReceived OnInputReceived;`
- L172 _public prototype_ `virtual FStreamingStoppedEvent& OnStreamingStopped() = 0;` — @brief A getter for the OnStreamingStopped event. Intent is for users to call IPixelStreamingModule::Get().FindStreamer(ID)->OnStreamingStopped().AddXXX. @return - The bindable OnStreamingStopped event.
- L177 _public prototype_ `virtual void ForceKeyFrame() = 0;` — @brief Force a key frame to be sent.
- L183 _public prototype_ `virtual void FreezeStream(UTexture2D* Texture) = 0;` — @brief Freeze Pixel Streaming. @param Texture 		- The freeze frame to display. If null then the back buffer is captured.
- L188 _public prototype_ `virtual void UnfreezeStream() = 0;` — @brief Unfreeze Pixel Streaming.
- L195 _public prototype_ `virtual void SendPlayerMessage(uint8 Type, const FString& Descriptor) = 0;` — @brief Send all players connected to this streamer a message @param Type The message type to be sent to the player @param Descriptor The contents of the message
- L203 _public prototype_ `virtual void SendPlayerMessage(FPixelStreamingPlayerId PlayerId, uint8 Type, const FString& Descriptor) = 0;` — @brief Send a single player connected to this streamer a message @param PlayerId The ID of the player to which to send the message @param Type The message type to be sent to the player @param Descriptor The contents of the message
- L211 _public prototype_ `virtual void SendFileData(const TArray64<uint8>& ByteData, FString& MimeType, FString& FileExtension) = 0;` — @brief Send a file to the browser where we are sending video. @param ByteData	 	- The raw byte data of the file. @param MimeType	 	- The files Mime type. Used for reconstruction on the front end. @param FileExtension - The files extension. Used for reconstruction on the front end.
- L217 _public prototype_ `virtual void KickPlayer(FPixelStreamingPlayerId PlayerId) = 0;` — @brief Kick a player by player id. @param PlayerId		- The ID of the player to kick
- L225 _public prototype_ `virtual void SetPlayerLayerPreference(FPixelStreamingPlayerId PlayerId, int SpatialLayerId, int TemporalLayerId) = 0;` — @brief Set the Layer Preference for a specific player. Only useful if using the SFU @param PlayerId The player id @param SpatialLayerId The id of the preferred spatial layer (resolution) @param TemporalLayerId The id of the preferred temporal layer (frame rate)
- L232 _public prototype_ `virtual TArray<FPixelStreamingPlayerId> GetConnectedPlayers() = 0;` — @brief Get the connected players @return TArray<FPixelStreamingPlayerId> The connected players
- L238 _public prototype_ `virtual void SetInputHandler(TSharedPtr<IPixelStreamingInputHandler> InInputHandler) = 0;` — @brief Set the streamer's input handler @param InInputHandler
- L244 _public prototype_ `virtual TWeakPtr<IPixelStreamingInputHandler> GetInputHandler() = 0;` — @brief Get the streamer's input handler @return The streamer's input handler
- L250 _public prototype_ `virtual TWeakPtr<IPixelStreamingSignallingConnection> GetSignallingConnection() = 0;` — @brief Get the connection to the signalling server. @return The connection to the signalling server.
- L257 _public prototype_ `virtual void SetSignallingConnection(TSharedPtr<IPixelStreamingSignallingConnection> InSignallingConnection) = 0;` — @brief Set the connection to the signalling server @param InSignallingConnection The connection to the signalling server
- L264 _public prototype_ `virtual TWeakPtr<IPixelStreamingSignallingConnectionObserver> GetSignallingConnectionObserver() = 0;` — @brief Get the Signalling Connection Observer object @return TWeakPtr<IPixelStreamingSignallingConnectionObserver>
- L269 _public prototype_ `virtual void SetInputHandlerType(EPixelStreamingInputType InputType) = 0;` — @brief Set the type for this streamers input handler. This controls whether input is routed to widgets or windows
- L274 _public prototype_ `virtual IPixelStreamingAudioSink* GetPeerAudioSink(FPixelStreamingPlayerId PlayerId) = 0;` — @brief Get the audio sink associated with a specific peer/player.
- L279 _public prototype_ `virtual IPixelStreamingAudioSink* GetUnlistenedAudioSink() = 0;` — @brief Get an audio sink that has no peers/players listening to it.
- L286 _public prototype_ `virtual TSharedPtr<IPixelStreamingAudioInput> CreateAudioInput() = 0;` — @brief Create an audio input that can be used to push audio into the Pixel Streaming mix. Note: Requires launching with -PixelStreamingExperimentalAudioInput. @return The audio input to push to.
- L291 _public prototype_ `virtual void RemoveAudioInput(TSharedPtr<IPixelStreamingAudioInput> AudioInput) = 0;` — @brief Remove the audio input from the Pixel Streaming mix.
- L298 _public prototype_ `virtual void SetConfigOption(const FName& OptionName, const FString& Value) = 0;` — @brief Allows sending arbitrary configuration options during initial connection @param Value Setting a value to an empty string clears it from the mapping and prevents it being sent
- L299 _public prototype_ `virtual bool GetConfigOption(const FName& OptionName, FString& OutValue) = 0;`
- L303 _public prototype_ `virtual void PlayerRequestsBitrate(FPixelStreamingPlayerId PlayerId, int MinBitrate, int MaxBitrate) = 0;`
- L305 _public prototype_ `virtual void RefreshStreamBitrate() = 0;`

#### Free symbols / members of external scopes

- L138 _delegate_ `DECLARE_EVENT_OneParam(IPixelStreamingStreamer, FPreConnectionEvent, IPixelStreamingStreamer*);` — @brief Event fired just before the streamer begins connecting to signalling.
- L149 _delegate_ `DECLARE_EVENT_OneParam(IPixelStreamingStreamer, FStreamingStartedEvent, IPixelStreamingStreamer*);` — @brief Event fired when the streamer has connected to a signalling server and is ready for peers.
- L160 _delegate_ `DECLARE_EVENT_OneParam(IPixelStreamingStreamer, FStreamingStoppedEvent, IPixelStreamingStreamer*);` — @brief Event fired when the streamer has disconnected from a signalling server and has stopped streaming.
- L165 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInputReceived, FPixelStreamingPlayerId, uint8, TArray<uint8>);` — Broadcast when data comes in from the data channel.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingAudioComponent.h` (Public)


#### class `FWebRTCSoundGenerator`  
`class FWebRTCSoundGenerator : public ISoundGenerator`  
_L16-51_
- inherits: `ISoundGenerator`
- desc: An `ISoundGenerator` implementation to pump some audio from WebRTC into this synth component
- L19 _public prototype_ `FWebRTCSoundGenerator();`
- L22 _public prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;` — Called when a new buffer is required.
- L25 _public prototype_ `virtual int32 GetDesiredNumSamplesToRenderPerCallback() const;` — Returns the number of samples to render per callback
- L28 _public function_ `virtual void OnBeginGenerate()` — Optional. Called on audio generator thread right when the generator begins generating.
- L31 _public function_ `virtual void OnEndGenerate()` — Optional. Called on audio generator thread right when the generator ends generating.
- L34 _public function_ `virtual bool IsFinished() const` — Optional. Can be overridden to end the sound when generating is finished.
- L36 _public prototype_ `void AddAudio(const int16_t* AudioData, int InSampleRate, size_t NChannels, size_t NFrames);`
- L38 _public function_ `int32 GetSampleRate()`
- L39 _public function_ `virtual int32 GetNumChannels() const override`
- L40 _public prototype_ `void EmptyBuffers();`
- L41 _public prototype_ `void SetParameters(const FSoundGeneratorInitParams& InitParams);`
- L44 _private member_ `FSoundGeneratorInitParams Params;`
- L45 _private member_ `TArray<int16_t> Buffer;`
- L46 _private member_ `FCriticalSection CriticalSection;`
- L49 _public member_ `FThreadSafeBool bGeneratingAudio = false;`
- L50 _public member_ `FThreadSafeBool bShouldGenerateAudio = false;`

#### class `UPixelStreamingAudioComponent`  
`class UPixelStreamingAudioComponent : public USynthComponent, public IPixelStreamingAudioConsumer`  
_L58-129_
- reflection: `UCLASS(Blueprintable, ClassGroup = (PixelStreaming), meta = (BlueprintSpawnableComponent))`
- inherits: `USynthComponent,IPixelStreamingAudioConsumer`
- desc: Allows in-engine playback of incoming WebRTC audio from a particular Pixel Streaming player/peer using their mic in the browser. Note: Each audio component associates itself with a particular Pixel Streaming player/peer (using the the Pixel Streaming player id).
- L63 _protected prototype_ `UPixelStreamingAudioComponent(const FObjectInitializer& ObjectInitializer);`
- L66 _protected prototype_ `virtual void OnBeginGenerate() override;`
- L67 _protected prototype_ `virtual void OnEndGenerate() override;`
- L68 _protected prototype_ `virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) override;`
- L72 _protected prototype_ `virtual void BeginDestroy() override;`
- L76 _protected prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L85 _public member_ `FString StreamerToHear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pixel Streaming Audio Component")` — The Pixel Streaming streamer of the player that we wish to listen to. If this is left blank this component will use the default Pixel Streaming streamer
- L93 _public member_ `FString PlayerToHear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pixel Streaming Audio Component")` — The Pixel Streaming player/peer whose audio we wish to listen to. If this is left blank this component will listen to the first non-listened to peer that connects after this component is ready. Note: that when the listened to peer disconnects this component is reset to blank and will once again listen to the next non-listened to peer that connects.
- L99 _public member_ `bool bAutoFindPeer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pixel Streaming Audio Component")` — If not already listening to a player/peer will try to attach for listening to the "PlayerToHear" each tick.
- L102 _private member_ `IPixelStreamingAudioSink* AudioSink;`
- L103 _private member_ `TSharedPtr<FWebRTCSoundGenerator, ESPMode::ThreadSafe> SoundGenerator;`
- L108 _public prototype_ `bool ListenTo(FString PlayerToListenTo);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Audio Component")` — Listen to a specific player on the default streamer. If the player is not found this component will be silent.
- L112 _public prototype_ `bool StreamerListenTo(FString StreamerId, FString PlayerToListenTo);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Audio Component")` — Listen to a specific player. If the player is not found this component will be silent.
- L116 _public prototype_ `bool IsListeningToPlayer();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Audio Component")` — True if listening to a connected WebRTC peer through Pixel Streaming.
- L118 _public prototype_ `bool WillListenToAnyPlayer();`
- L122 _public prototype_ `void Reset();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Audio Component")` — Stops listening to any connected player/peer and resets internal state so component is ready to listen again.
- L125 _public prototype_ `void ConsumeRawPCM(const int16_t* AudioData, int InSampleRate, size_t NChannels, size_t NFrames);`
- L126 _public prototype_ `void OnConsumerAdded();`
- L127 _public prototype_ `void OnConsumerRemoved();`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingBufferBuilder.h` (Public)


#### struct `UE::PixelStreaming::BufferBuilder`  
`struct BufferBuilder`  
_L35-51_
- L37 _public member_ `rtc::CopyOnWriteBuffer Buffer;`
- L38 _public member_ `size_t Pos;`
- L40 _public function_ `BufferBuilder(size_t size) : Buffer(size), Pos(0)`
- L44 _public function_ `template <typename T> void Insert(T&& Value)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L14 _function_ `template <typename T> inline size_t ValueSize(T&& Value)` (scope `UE::PixelStreaming`)
- L20 _function_ `template <typename T> inline const void* ValueLoc(T&& Value)` (scope `UE::PixelStreaming`)
- L25 _function_ `inline size_t ValueSize(FString&& Value)` (scope `UE::PixelStreaming`)
- L30 _function_ `inline const void* ValueLoc(FString&& Value)` (scope `UE::PixelStreaming`)

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingCodec.h` (Public)


#### enum `EPixelStreamingCodec`  
`enum class EPixelStreamingCodec`  
_L7-15_
- L9 _public enumerator_ `Invalid`
- L10 _public enumerator_ `H264`
- L11 _public enumerator_ `H265 UE_DEPRECATED(5.4, "EPixelStreamingCodec::H265 has been deprecated and is no longer supported. If your GPU supports it, consider using using AV1 instead")`
- L12 _public enumerator_ `AV1`
- L13 _public enumerator_ `VP8`
- L14 _public enumerator_ `VP9`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingDataChannel.h` (Public)


#### class `FPixelStreamingDataChannel`  
`class FPixelStreamingDataChannel : public webrtc::DataChannelObserver, public TSharedFromThis<FPixelStreamingDataChannel>`  
_L13-76_
- inherits: `webrtc::DataChannelObserver,TSharedFromThis<FPixelStreamingDataChannel>`
- desc: A specialized representation of a WebRTC data channel for Pixel Streaming.
- L16 _public prototype_ `static TSharedPtr<FPixelStreamingDataChannel> Create(rtc::scoped_refptr<webrtc::DataChannelInterface> InChannel);`
- L17 _public prototype_ `static TSharedPtr<FPixelStreamingDataChannel> Create(FPixelStreamingPeerConnection& Connection, int32 SendStreamId, int32 RecvStreamId);`
- L18 _public prototype_ `virtual ~FPixelStreamingDataChannel();`
- L26 _public function_ `template <typename... Args> bool SendMessage(uint8 Type, Args... VarArgs)` — Sends a series of arguments to the data channel with the given type. @param Type Should be the ID from a registered PixelStreamingProtocol message @returns True of the message was successfully sent.
- L45 _public prototype_ `bool SendArbitraryData(uint8 Type, const TArray64<uint8>& DataBytes) const;` — Sends a large buffer of data to the data channel. @param Type See SendMessage. The type of the message. @param DataBytes The raw byte buffer to send. @returns True when all data was successfully sent.
- L50 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpen, FPixelStreamingDataChannel&);` — Broadcast when the data channel state changes to open
- L51 _public member_ `FOnOpen OnOpen;`
- L56 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClosed, FPixelStreamingDataChannel&);` — Broadcast when the data channel state changes to closed
- L57 _public member_ `FOnClosed OnClosed;`
- L62 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMessage, uint8, const webrtc::DataBuffer&);` — Broadcast when data comes in from the data channel.
- L63 _public member_ `FOnMessage OnMessageReceived;`
- L67 _protected prototype_ `virtual void OnStateChange() override;` — webrtc::DataChannelObserver implementation.
- L68 _protected prototype_ `virtual void OnMessage(const webrtc::DataBuffer& Buffer) override;`
- L71 _private member_ `rtc::scoped_refptr<webrtc::DataChannelInterface> SendChannel;`
- L72 _private member_ `rtc::scoped_refptr<webrtc::DataChannelInterface> RecvChannel;`
- L74 _private prototype_ `FPixelStreamingDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> InChannel);`
- L75 _private prototype_ `FPixelStreamingDataChannel(FPixelStreamingPeerConnection& Connection, int32 SendStreamId, int32 RecvStreamId);`

#### Free symbols / members of external scopes

- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpen, FPixelStreamingDataChannel&);` — Broadcast when the data channel state changes to open
- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClosed, FPixelStreamingDataChannel&);` — Broadcast when the data channel state changes to closed
- L62 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMessage, uint8, const webrtc::DataBuffer&);` — Broadcast when data comes in from the data channel.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingDelegates.h` (Public)


#### class `UPixelStreamingDelegates`  
`class UPixelStreamingDelegates : public UObject`  
_L17-141_
- reflection: `UCLASS()`
- inherits: `UObject`
- L26 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConnectedToSignallingServer);` — BP Delegate
- L28 _public member_ `FConnectedToSignallingServer OnConnectedToSignallingServer;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")`
- L30 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FConnectedToSignallingServerNative);` — C++ Delegate
- L31 _public member_ `FConnectedToSignallingServerNative OnConnectedToSignallingServerNative;`
- L37 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisconnectedFromSignallingServer);` — BP Delegate
- L39 _public member_ `FDisconnectedFromSignallingServer OnDisconnectedFromSignallingServer;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")`
- L41 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FDisconnectedFromSignallingServerNative);` — C++ Delegate
- L42 _public member_ `FDisconnectedFromSignallingServerNative OnDisconnectedFromSignallingServerNative;`
- L48 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FNewConnection, FString, StreamerId, FString, PlayerId, bool, QualityController);` — BP Delegate
- L50 _public member_ `FNewConnection OnNewConnection;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")`
- L52 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FNewConnectionNative, FString, FPixelStreamingPlayerId, bool);` — C++ Delegate
- L53 _public member_ `FNewConnectionNative OnNewConnectionNative;`
- L59 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FClosedConnection, FString, StreamerId, FString, PlayerId, bool, WasQualityController);` — BP Delegate
- L61 _public member_ `FClosedConnection OnClosedConnection;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")`
- L63 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FClosedConnectionNative, FString, FPixelStreamingPlayerId, bool);` — C++ Delegate
- L64 _public member_ `FClosedConnectionNative OnClosedConnectionNative;`
- L71 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAllConnectionsClosed, FString, StreamerId);` — BP Delegate
- L73 _public member_ `FAllConnectionsClosed OnAllConnectionsClosed;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")`
- L75 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAllConnectionsClosedNative, FString);` — C++ Delegate
- L76 _public member_ `FAllConnectionsClosedNative OnAllConnectionsClosedNative;`
- L82 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FQualityControllerChanged, FString, FPixelStreamingPlayerId);` — C++ Delegate
- L83 _public member_ `FQualityControllerChanged OnQualityControllerChangedNative;`
- L89 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FDataChannelOpen, FString, FPixelStreamingPlayerId, FPixelStreamingDataChannel*);` — C++ Delegate
- L90 _public member_ `FDataChannelOpen OnDataChannelOpenNative;`
- L96 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDataChannelClosed, FString, FPixelStreamingPlayerId);` — C++ Delegate
- L97 _public member_ `FDataChannelClosed OnDataChannelClosedNative;`
- L103 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FStatsChanged, FString, PlayerId, FName, StatName, float, StatValue);` — BP Delegate
- L105 _public member_ `FStatsChanged OnStatChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")`
- L107 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FStatChangedNative, FPixelStreamingPlayerId, FName, float);` — C++ Delegate
- L108 _public member_ `FStatChangedNative OnStatChangedNative;`
- L114 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFallbackToSoftwareEncodering);` — BP Delegate
- L116 _public member_ `FFallbackToSoftwareEncodering OnFallbackToSoftwareEncodering;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")`
- L118 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FFallbackToSoftwareEncoderingNative);` — C++ Delegate
- L119 _public member_ `FFallbackToSoftwareEncoderingNative OnFallbackToSoftwareEncoderingNative;`
- L124 _public prototype_ `static UPixelStreamingDelegates* CreateInstance();` — Create the singleton.
- L126 _public function_ `static UPixelStreamingDelegates* GetPixelStreamingDelegates()`
- L131 _public function_ `virtual ~UPixelStreamingDelegates()`
- L139 _private member_ `static UPixelStreamingDelegates* Singleton;` — The singleton object.
- L140 _private member_ `static bool bIsExiting;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace webrtc`
- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConnectedToSignallingServer);` — BP Delegate
- L30 _delegate_ `DECLARE_MULTICAST_DELEGATE(FConnectedToSignallingServerNative);` — C++ Delegate
- L37 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisconnectedFromSignallingServer);` — BP Delegate
- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE(FDisconnectedFromSignallingServerNative);` — C++ Delegate
- L48 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FNewConnection, FString, StreamerId, FString, PlayerId, bool, QualityController);` — BP Delegate
- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FNewConnectionNative, FString, FPixelStreamingPlayerId, bool);` — C++ Delegate
- L59 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FClosedConnection, FString, StreamerId, FString, PlayerId, bool, WasQualityController);` — BP Delegate
- L63 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FClosedConnectionNative, FString, FPixelStreamingPlayerId, bool);` — C++ Delegate
- L71 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAllConnectionsClosed, FString, StreamerId);` — BP Delegate
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAllConnectionsClosedNative, FString);` — C++ Delegate
- L82 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FQualityControllerChanged, FString, FPixelStreamingPlayerId);` — C++ Delegate
- L89 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FDataChannelOpen, FString, FPixelStreamingPlayerId, FPixelStreamingDataChannel*);` — C++ Delegate
- L96 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDataChannelClosed, FString, FPixelStreamingPlayerId);` — C++ Delegate
- L103 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FStatsChanged, FString, PlayerId, FName, StatName, float, StatValue);` — BP Delegate
- L107 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FStatChangedNative, FPixelStreamingPlayerId, FName, float);` — C++ Delegate
- L114 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFallbackToSoftwareEncodering);` — BP Delegate
- L118 _delegate_ `DECLARE_MULTICAST_DELEGATE(FFallbackToSoftwareEncoderingNative);` — C++ Delegate

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingInputComponent.h` (Public)


#### class `UPixelStreamingInput`  
`class UPixelStreamingInput : public UActorComponent`  
_L15-65_
- reflection: `UCLASS(Blueprintable, ClassGroup = (PixelStreaming), meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: This component may be attached to an actor to allow UI interactions to be handled as the delegate will be notified about the interaction and will be supplied with a generic descriptor string containing, for example, JSON data. Responses back to the source of the UI interactions may also be sent.
- L20 _public prototype_ `UPixelStreamingInput(const FObjectInitializer& ObjectInitializer);`
- L21 _public prototype_ `void BeginPlay() override;`
- L22 _public prototype_ `void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L25 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInput, const FString&, Descriptor);` — The delegate which will be notified about a UI interaction.
- L27 _public member_ `FOnInput OnInputEvent;` — `UPROPERTY(BlueprintAssignable, Category = "PixelStreaming Input")`
- L34 _public prototype_ `void SendPixelStreamingResponse(const FString& Descriptor);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming Input")` — Send a response back to the source of the UI interactions. @param Descriptor - A generic descriptor string.
- L48 _public prototype_ `void GetJsonStringValue(FString Descriptor, FString FieldName, FString& StringValue, bool& Success);` — `UFUNCTION(BlueprintPure, Category = "PixelStreaming Input")` — Helper function to extract a string field from a JSON descriptor of a UI interaction given its field name. The field name may be hierarchical, delimited by a period. For example, to access the Width value of a Resolution command above you should use "Resolution.Width" to get the width value. @param Descriptor - The UI interaction JSON descriptor. @param FieldName - The name of the field to look for in the JSON. @param StringValue - The string value associated with the field name. @param Success - True if the field exists in the JSON data.
- L60 _public prototype_ `void AddJsonStringValue(const FString& Descriptor, FString FieldName, FString StringValue, FString& NewDescriptor, bool& Success);` — `UFUNCTION(BlueprintPure, Category = "PixelStreaming Input")` — Helper function to add a string field to a JSON descriptor. This produces a new descriptor which may then be chained to add further string fields. @param Descriptor - The initial JSON descriptor which may be blank initially. @param FieldName - The name of the field to add to the JSON. @param StringValue - The string value associated with the field name. @param NewDescriptor - The JSON descriptor with the string field added. @param Success - True if the string field could be added successfully.
- L64 _private member_ `IPixelStreamingModule* PixelStreamingModule;` — For convenience we keep a reference to the Pixel Streaming plugin.

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInput, const FString&, Descriptor);` — The delegate which will be notified about a UI interaction.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingPeerConnection.h` (Public)


#### class `IPixelStreamingStatsSource`  
`class IPixelStreamingStatsSource`  
_L20-26_
- desc: An interface that allows us to collect regular stats from anything that implements it (we use this for WebRTC stats polling internally).
- L23 _public prototype_ `virtual ~IPixelStreamingStatsSource() = default;`
- L25 _public prototype_ `virtual void PollStats() const = 0;` — Implement your function to poll whatever stats you are returning/storing.

#### class `FPixelStreamingPeerConnection`  
`class FPixelStreamingPeerConnection : public webrtc::PeerConnectionObserver`  
_L31-322_
- inherits: `webrtc::PeerConnectionObserver`
- desc: A specialized representation of a WebRTC peer connection for Pixel Streaming.
- L34 _public prototype_ `virtual ~FPixelStreamingPeerConnection();`
- L36 _public typedef_ `using FRTCConfig = webrtc::PeerConnectionInterface::RTCConfiguration;`
- L44 _public prototype_ `static TUniquePtr<FPixelStreamingPeerConnection> Create(const FRTCConfig& RTCConfig, bool IsSFU = false);` — Creates a new peer connection using the given RTC configuration. @param Config The RTC configuration for the connection. Usually provided from the signalling server. @param IsSFU Set to true to create a peer connection to an SFU. Controls whether it recieves simulcast and some audio settings are affected. @returns A new peer connection ready to be used.
- L49 _public prototype_ `static void Shutdown();` — Shuts down the WebRTC thread and destroys the peer connection factory. No peer connections should be in use after this call.
- L51 _public typedef_ `using VoidCallback = TFunction<void()>;`
- L52 _public typedef_ `using SDPCallback = TFunction<void(const webrtc::SessionDescriptionInterface*)>;`
- L53 _public typedef_ `using ErrorCallback = TFunction<void(const FString& Error)>;`
- L80 _public prototype_ `void CreateOffer(EReceiveMediaOption ReceiveOption, const SDPCallback& SuccessCallback, const ErrorCallback& ErrorCallback);` — Asynchronously creates an offer session description for this local peer connection. @param ReceiveOption Indicates what kind of media this connection intends to receive. @param SuccessCallback A callback to be called when the offer is ready. @param ErrorCallback A callback to be called on the event of an error.
- L88 _public prototype_ `void CreateAnswer(EReceiveMediaOption ReceiveOption, const SDPCallback& SuccessCallback, const ErrorCallback& ErrorCallback);` — Asynchronously creates an answer session description for this local peer connection. @param ReceiveOption Indicates what kind of media this connection intends to receive. @param SuccessCallback A callback to be called when the offer is ready. @param ErrorCallback A callback to be called on the event of an error.
- L96 _public prototype_ `void ReceiveOffer(const FString& SDP, const VoidCallback& SuccessCallback, const ErrorCallback& ErrorCallback);` — Asynchronously sets the remote description from a session description string offered from a signalling server. @param SDP The string representation of the remote session description. @param SuccessCallback A callback to be called when the remote description was successfully set. @param ErrorCallback A callback to be called on the event of an error.
- L104 _public prototype_ `void ReceiveAnswer(const FString& SDP, const VoidCallback& SuccessCallback, const ErrorCallback& ErrorCallback);` — Asynchronously sets the remote description from a session description string answered from a signalling server. @param SDP The string representation of the remote session description. @param SuccessCallback A callback to be called when the remote description was successfully set. @param ErrorCallback A callback to be called on the event of an error.
- L112 _public prototype_ `void SetLocalDescription(webrtc::SessionDescriptionInterface* SDP, const VoidCallback& SuccessCallback, const ErrorCallback& ErrorCallback);` — Asynchronously sets the local description using the given session description object. @param SDP The WebRTC session description object. @param SuccessCallback A callback to be called when the local description was successfully set. @param ErrorCallback A callback to be called on the event of an error.
- L120 _public prototype_ `void SetRemoteDescription(webrtc::SessionDescriptionInterface* SDP, const VoidCallback& SuccessCallback, const ErrorCallback& ErrorCallback);` — Asynchronously sets the remote description using the given session description object. @param SDP The WebRTC session description object. @param SuccessCallback A callback to be called when the remote description was successfully set. @param ErrorCallback A callback to be called on the event of an error.
- L126 _public prototype_ `const webrtc::SessionDescriptionInterface* GetLocalDescription() const;` — Gets the current local description. @returns The session description object representing the local description. Can be nullptr.
- L132 _public prototype_ `const webrtc::SessionDescriptionInterface* GetRemoteDescription() const;` — Gets the current remote description. @returns The session description object representing the remote description. Can be nullptr.
- L138 _public prototype_ `void SetVideoSource(rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> InVideoSource);` — Sets a video source that can supply this connection with frame data. @params InVideoSource The source of frame data.
- L144 _public prototype_ `void SetAudioSource(rtc::scoped_refptr<webrtc::AudioSourceInterface> InAudioSource);` — Sets an audio source that can supply this connection with audio data. @params InAudioSource The source of audio data.
- L150 _public function_ `rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> GetVideoSource() const` — Gets the currently set video source on this connection. @returns The currently set video source. Can be nullptr.
- L156 _public function_ `rtc::scoped_refptr<webrtc::AudioSourceInterface> GetAudioSource() const` — Gets the currently set audio source on this connection. @returns The currently set audio source. Can be nullptr.
- L162 _public prototype_ `void SetVideoSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* InSink);` — Sets a video sink on this connection that will receive frame data from this connection. @param InSink The sink that will receive the frame data.
- L168 _public prototype_ `void SetAudioSink(TSharedPtr<IPixelStreamingAudioSink> InSink);` — Sets an audio sink on this connection that will receive audio data from this connection. @param InSink The sink that will receive the audio data.
- L174 _public function_ `rtc::VideoSinkInterface<webrtc::VideoFrame>* GetVideoSink()` — Gets the currently set video sink on this connection. @return The currently set video sink. Can be nullptr.
- L180 _public function_ `TSharedPtr<IPixelStreamingAudioSink> GetAudioSink()` — Gets the currently set audio sink on this connection. @return The currently set audio sink. Can be nullptr.
- L187 _public prototype_ `virtual void ForEachTransceiver(const TFunction<void(rtc::scoped_refptr<webrtc::RtpTransceiverInterface>)>& Func);` — @brief A method for iterating through all of the tranceivers on the peer connection. You could use this to check for the existence of an audio/video transceiver @param Func The lambda to execute with each transceiver
- L195 _public prototype_ `void AddRemoteIceCandidate(const FString& SDPMid, int SDPMLineIndex, const FString& SDP);` — Adds ICE candidate data to the peer connection. Usually supplied from the signalling server. @param SDPMid @param SDPMLineIndex @param SDP
- L203 _public prototype_ `TSharedPtr<FPixelStreamingDataChannel> CreateDataChannel(int Id, bool Negotiated);` — Creates a data connection associated with this peer connection. @param Id The channel id to be used. 0 - 1023 @param Negotiated Whether the connection is negoriated or not. Id is ignored if Negotiated is false #returns The data channel object created.
- L209 _public prototype_ `void SetWebRTCStatsCallback(rtc::scoped_refptr<webrtc::RTCStatsCollectorCallback> InCallback);` — Sets the callback to be used when the stats collector comes knocking. Decides how stats should be collected. @param InCallback The callback object.
- L211 _public prototype_ `void RefreshStreamBitrate();`
- L217 _public prototype_ `EPixelStreamingCodec GetNegotiatedVideoCodec() const;` — @return The negotiated video codec as parsed from the SDP offer/answer. Note: This changes as new offer/answers come in potentially.
- L222 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIceCandidate, const webrtc::IceCandidateInterface*);` — Called when the ICE candidate is emitted.
- L223 _public member_ `FOnIceCandidate OnEmitIceCandidate;`
- L228 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataChannel, TSharedPtr<FPixelStreamingDataChannel>);` — Called when a data channel is opened from the remote side of this connection.
- L229 _public member_ `FOnDataChannel OnNewDataChannel;`
- L234 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIceStateChanged, webrtc::PeerConnectionInterface::IceConnectionState);` — Called when the ICE state changes.
- L235 _public member_ `FOnIceStateChanged OnIceStateChanged;`
- L241 _public prototype_ `static rtc::scoped_refptr<webrtc::AudioSourceInterface> GetApplicationAudioSource();` — Gets the global audio source. @returns The global audio source.
- L246 _public prototype_ `static void ForceVideoKeyframe();` — Causes the video stream to generate a keyframe
- L252 _public function_ `template <typename FunctorT> static void PostSignalingTask(FunctorT&& InFunc)` — Post a task onto the WebRTC signalling thread.
- L265 _public prototype_ `static TSharedPtr<IPixelStreamingAudioInput> CreateAudioInput();`
- L266 _public prototype_ `static void RemoveAudioInput(TSharedPtr<IPixelStreamingAudioInput> AudioInput);`
- L272 _protected prototype_ `virtual void OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState NewState) override;` — webrtc::PeerConnectionObserver implementation.
- L273 _protected prototype_ `virtual void OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> Stream) override;`
- L274 _protected prototype_ `virtual void OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> Stream) override;`
- L275 _protected prototype_ `virtual void OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> Channel) override;`
- L276 _protected prototype_ `virtual void OnRenegotiationNeeded() override;`
- L277 _protected prototype_ `virtual void OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState NewState) override;`
- L278 _protected prototype_ `virtual void OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState NewState) override;`
- L279 _protected prototype_ `virtual void OnIceCandidate(const webrtc::IceCandidateInterface* Candidate) override;`
- L280 _protected prototype_ `virtual void OnIceCandidatesRemoved(const std::vector<cricket::Candidate>& candidates) override;`
- L281 _protected prototype_ `virtual void OnIceConnectionReceivingChange(bool Receiving) override;`
- L282 _protected prototype_ `virtual void OnTrack(rtc::scoped_refptr<webrtc::RtpTransceiverInterface> Transceiver) override;`
- L283 _protected prototype_ `virtual void OnRemoveTrack(rtc::scoped_refptr<webrtc::RtpReceiverInterface> receiver) override;`
- L286 _private prototype_ `FPixelStreamingPeerConnection();`
- L294 _private prototype_ `void CreateSDP(ESDPType SDPType, EReceiveMediaOption ReceiveOption, const SDPCallback& SuccessCallback, const ErrorCallback& ErrorCallback);`
- L296 _private member_ `rtc::scoped_refptr<webrtc::PeerConnectionInterface> PeerConnection;`
- L298 _private member_ `rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> VideoSource;`
- L299 _private member_ `rtc::scoped_refptr<webrtc::AudioSourceInterface> AudioSource;`
- L301 _private member_ `rtc::VideoSinkInterface<webrtc::VideoFrame>* VideoSink = nullptr;`
- L302 _private member_ `TSharedPtr<IPixelStreamingAudioSink> AudioSink;`
- L305 _private member_ `EPixelStreamingCodec NegotiatedVideoCodec = EPixelStreamingCodec::Invalid;` — The video codec that is negotiated and extracted from the SDP.
- L308 _private member_ `TSharedPtr<IPixelStreamingStatsSource> StatsSource;` — Source of WebRTC stats that we poll regularly.
- L310 _private member_ `bool IsSFU = false;`
- L311 _private member_ `bool bIsDestroying = false;`
- L314 _private prototype_ `static void CreatePeerConnectionFactory();` — TODO these static methods can probably be moved off into a singleton or something
- L315 _private member_ `static TUniquePtr<rtc::Thread> SignallingThread;`
- L316 _private member_ `static rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> PeerConnectionFactory;`
- L317 _private member_ `static rtc::scoped_refptr<webrtc::AudioSourceInterface> ApplicationAudioSource;`
- L318 _private member_ `static TSharedPtr<UE::PixelStreaming::FAudioInputMixer> AudioMixer;`

#### enum `FPixelStreamingPeerConnection::EReceiveMediaOption`  
`enum EReceiveMediaOption : int`  
_L59-72_
- desc: Flags for CreateOffer/CreateAnswer that indicate what kind of media we indend to receive. Dictates what the resulting SDP will contain. To actually receive audio or video you will need to supply sinks via SetAudioSink/SetVideoSink
- L62 _public enumerator_ `Nothing = 0x00` — Receive no media
- L65 _public enumerator_ `Audio = 0x01` — Can receive audio
- L68 _public enumerator_ `Video = 0x02` — Can receive video
- L71 _public enumerator_ `All = Audio | Video` — Can receive both audio and video

#### enum `FPixelStreamingPeerConnection::ESDPType`  
`enum class ESDPType`  
_L288-292_
- L290 _public enumerator_ `Offer`
- L291 _public enumerator_ `Answer`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L222 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIceCandidate, const webrtc::IceCandidateInterface*);` — Called when the ICE candidate is emitted.
- L228 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataChannel, TSharedPtr<FPixelStreamingDataChannel>);` — Called when a data channel is opened from the remote side of this connection.
- L234 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIceStateChanged, webrtc::PeerConnectionInterface::IceConnectionState);` — Called when the ICE state changes.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingPlayerConfig.h` (Public)


#### struct `FPixelStreamingPlayerConfig`  
`struct FPixelStreamingPlayerConfig`  
_L7-11_
- L9 _public member_ `bool SupportsDataChannel = false;`
- L10 _public member_ `bool IsSFU = false;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingPlayerId.h` (Public)


#### Free symbols / members of external scopes

- L7 _typedef_ `using FPixelStreamingPlayerId = FString;`
- L9 _function_ `inline FPixelStreamingPlayerId ToPlayerId(FString PlayerIdString)`
- L14 _function_ `inline FPixelStreamingPlayerId ToPlayerId(int32 PlayerIdInteger)`
- L19 _function_ `inline int32 PlayerIdToInt(FPixelStreamingPlayerId PlayerId)`
- L24 _externvar_ `extern const FPixelStreamingPlayerId INVALID_PLAYER_ID;`
- L25 _externvar_ `extern const FPixelStreamingPlayerId SFU_PLAYER_ID;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingSessionDescriptionObservers.h` (Public)


#### class `FPixelStreamingSetSessionDescriptionObserver`  
`class FPixelStreamingSetSessionDescriptionObserver : public webrtc::SetSessionDescriptionObserver`  
_L18-51_
- inherits: `webrtc::SetSessionDescriptionObserver`
- desc: FPixelStreamingSetSessionDescriptionObserver WebRTC requires an implementation of `webrtc::SetSessionDescriptionObserver` interface as a callback for setting session description, either on receiving remote `offer` (`PeerConnection::SetRemoteDescription`) of on sending `answer` (`PeerConnection::SetLocalDescription`)
- L21 _public typedef_ `using FSuccessCallback = TFunction<void()>;`
- L22 _public typedef_ `using FFailureCallback = TFunction<void(const FString&)>;`
- L24 _public function_ `static FPixelStreamingSetSessionDescriptionObserver* Create(const FSuccessCallback& successCallback, const FFailureCallback& failureCallback)`
- L29 _public function_ `FPixelStreamingSetSessionDescriptionObserver(const FSuccessCallback& successCallback, const FFailureCallback& failureCallback) : SuccessCallback(successCallback) , FailureCallback(failureCallback)`
- L36 _public function_ `void OnSuccess() override` — we don't need to do anything on success
- L43 _public function_ `void OnFailure(webrtc::RTCError Error) override` — errors usually mean incompatibility between our session configuration (often H.264, its profile and level) and player, malformed SDP or if player doesn't support UnifiedPlan (whatever was used by proxy)
- L49 _private member_ `FSuccessCallback SuccessCallback;`
- L50 _private member_ `FFailureCallback FailureCallback;`

#### class `FPixelStreamingCreateSessionDescriptionObserver`  
`class FPixelStreamingCreateSessionDescriptionObserver : public webrtc::CreateSessionDescriptionObserver`  
_L53-83_
- inherits: `webrtc::CreateSessionDescriptionObserver`
- L56 _public typedef_ `using FSuccessCallback = TFunction<void(webrtc::SessionDescriptionInterface*)>;`
- L57 _public typedef_ `using FFailureCallback = TFunction<void(const FString&)>;`
- L59 _public function_ `static FPixelStreamingCreateSessionDescriptionObserver* Create(const FSuccessCallback& successCallback, const FFailureCallback& failureCallback)`
- L64 _public function_ `FPixelStreamingCreateSessionDescriptionObserver(const FSuccessCallback& successCallback, const FFailureCallback& failureCallback) : SuccessCallback(successCallback) , FailureCallback(failureCallback)`
- L70 _public function_ `void OnSuccess(webrtc::SessionDescriptionInterface* SDP) override`
- L75 _public function_ `void OnFailure(webrtc::RTCError Error) override`
- L81 _private member_ `FSuccessCallback SuccessCallback;`
- L82 _private member_ `FFailureCallback FailureCallback;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingSettings.h` (Public)


#### struct `FPixelStreamingSimulcastParameters`  
`struct FPixelStreamingSimulcastParameters`  
_L13-23_
- desc: A struct representing the simulcast paramaters used by PixelStreaming. The parameters contain an array of layers, with each layer having a Scale, MinBitrate and MaxBitrate
- L22 _public member_ `TArray<FPixelStreamingSimulcastLayer> Layers;`

#### struct `FPixelStreamingSimulcastParameters::FPixelStreamingSimulcastLayer`  
`struct FPixelStreamingSimulcastLayer`  
_L15-20_
- L17 _public member_ `float Scaling;`
- L18 _public member_ `int MinBitrate;`
- L19 _public member_ `int MaxBitrate;`

#### class `FPixelStreamingSettings`  
`class FPixelStreamingSettings`  
_L29-35_
- desc: A collection of static methods used to expose settings and their values to other modules dependedant on PixelStreaming
- L32 _public prototype_ `static FPixelStreamingSimulcastParameters GetSimulcastParameters();`
- L33 _public prototype_ `static bool GetCaptureUseFence();`
- L34 _public prototype_ `static bool GetVPXUseCompute();`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingSignallingConnection.h` (Public)


#### class `FPixelStreamingSignallingConnection`  
`class FPixelStreamingSignallingConnection : public IPixelStreamingSignallingConnection`  
_L17-117_
- inherits: `IPixelStreamingSignallingConnection`
- desc: A specialized signalling server connection object for web socket based Pixel Streaming signalling servers.
- L20 _public prototype_ `FPixelStreamingSignallingConnection(TSharedPtr<IPixelStreamingSignallingConnectionObserver> InObserver, FString InStreamerId = "", TSharedPtr<IWebSocket> InWebSocket = nullptr);`
- L21 _public prototype_ `virtual ~FPixelStreamingSignallingConnection();`
- L24 _public prototype_ `virtual void TryConnect(FString URL) override;` — IPixelStreamingSignallingConnection Interface
- L26 _public prototype_ `virtual void Disconnect() override;` — `UE_DEPRECATED(5.4, "Disconnect has been deprecated and will be removed in future versions. Please use: Disconnect(FString Reason)")`
- L27 _public prototype_ `virtual void Disconnect(FString Reason) override;`
- L28 _public prototype_ `virtual bool IsConnected() const override;`
- L29 _public prototype_ `virtual void SendOffer(FPixelStreamingPlayerId PlayerId, const webrtc::SessionDescriptionInterface& SDP) override;`
- L30 _public prototype_ `virtual void SendAnswer(FPixelStreamingPlayerId PlayerId, const webrtc::SessionDescriptionInterface& SDP) override;`
- L31 _public prototype_ `virtual void SendIceCandidate(FPixelStreamingPlayerId PlayerId, const webrtc::IceCandidateInterface& IceCandidate) override;`
- L32 _public prototype_ `virtual void SendDisconnectPlayer(FPixelStreamingPlayerId PlayerId, const FString& Reason) override;`
- L33 _public prototype_ `virtual void RequestStreamerList() override;`
- L34 _public prototype_ `virtual void SendSubscribe(const FString& StreamerId) override;`
- L35 _public prototype_ `virtual void SendUnsubscribe() override;`
- L36 _public prototype_ `virtual void SendOffer(const webrtc::SessionDescriptionInterface& SDP) override;`
- L37 _public prototype_ `virtual void SendAnswer(const webrtc::SessionDescriptionInterface& SDP) override;`
- L38 _public prototype_ `virtual void SendIceCandidate(const webrtc::IceCandidateInterface& IceCandidate) override;`
- L39 _public prototype_ `virtual void SetKeepAlive(bool bKeepAlive) override;`
- L40 _public prototype_ `virtual void SetAutoReconnect(bool bAutoReconnect) override;`
- L41 _public prototype_ `virtual void SendMessage(const FString& Msg) override;`
- L44 _private prototype_ `void Connect(FString Url, bool bIsReconnect);`
- L45 _private prototype_ `void OnConnected();`
- L46 _private prototype_ `void OnConnectionError(const FString& Error);`
- L47 _private prototype_ `void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);`
- L48 _private prototype_ `void OnMessage(const FString& Msg);`
- L49 _private prototype_ `void OnBinaryMessage(const uint8* Data, int32 Length, bool bIsLastFragment);`
- L51 _private typedef_ `using FJsonObjectPtr = TSharedPtr<FJsonObject>;`
- L52 _private prototype_ `void RegisterHandler(const FString& messageType, const TFunction<void(FJsonObjectPtr)>& handler);`
- L54 _private prototype_ `void OnIdRequested();`
- L55 _private prototype_ `void OnConfig(const FJsonObjectPtr& Json);`
- L56 _private prototype_ `void OnPing(const FJsonObjectPtr& Json);`
- L57 _private prototype_ `void OnPong(const FJsonObjectPtr& Json);`
- L58 _private prototype_ `void OnSessionDescription(const FJsonObjectPtr& Json);`
- L59 _private prototype_ `void OnIceCandidate(const FJsonObjectPtr& Json);`
- L60 _private prototype_ `void OnPlayerCount(const FJsonObjectPtr& Json);`
- L61 _private prototype_ `void OnPlayerConnected(const FJsonObjectPtr& Json);`
- L62 _private prototype_ `void OnPlayerDisconnected(const FJsonObjectPtr& Json);`
- L63 _private prototype_ `void OnSFUPeerDataChannels(const FJsonObjectPtr& Json);`
- L64 _private prototype_ `void OnPeerDataChannels(const FJsonObjectPtr& Json);`
- L65 _private prototype_ `void OnStreamerList(const FJsonObjectPtr& Json);`
- L66 _private prototype_ `void SetPlayerIdJson(FJsonObjectPtr& JsonObject, FPixelStreamingPlayerId PlayerId);`
- L67 _private prototype_ `bool GetPlayerIdJson(const FJsonObjectPtr& Json, FPixelStreamingPlayerId& OutPlayerId, const FString& FieldId = TEXT("play`
- L69 _private prototype_ `void StartKeepAliveTimer();`
- L70 _private prototype_ `void StopKeepAliveTimer();`
- L72 _private prototype_ `void StartReconnectTimer();`
- L73 _private prototype_ `void StopReconnectTimer();`
- L76 _private function_ `template <typename... T> void PlayerError(FPixelStreamingPlayerId PlayerId, UE::Core::TCheckedFormatString<FString::FmtCharType, T...> Msg, T... args)`
- L81 _private prototype_ `void PlayerError(FPixelStreamingPlayerId PlayerId, const FString& Msg);`
- L84 _private member_ `TSharedPtr<IPixelStreamingSignallingConnectionObserver> Observer;`
- L85 _private member_ `FString StreamerId;`
- L86 _private member_ `FString Url;`
- L88 _private member_ `TSharedPtr<IWebSocket> WebSocket;`
- L90 _private member_ `FDelegateHandle OnConnectedHandle;`
- L91 _private member_ `FDelegateHandle OnConnectionErrorHandle;`
- L92 _private member_ `FDelegateHandle OnClosedHandle;`
- L93 _private member_ `FDelegateHandle OnMessageHandle;`
- L94 _private member_ `FDelegateHandle OnBinaryMessageHandle;`
- L96 _private member_ `bool bAutoReconnectEnabled = true;`
- L97 _private member_ `bool bKeepAliveEnabled = true;`
- L98 _private member_ `bool bIsConnected = false;`
- L100 _private member_ `FTimerHandle TimerHandle_KeepAlive;` — Handle for efficient management of KeepAlive timer
- L101 _private member_ `FTimerHandle TimerHandle_Reconnect;`
- L102 _private member_ `const float KEEP_ALIVE_INTERVAL = 60.0f;`
- L104 _private member_ `TMap<FString, TFunction<void(FJsonObjectPtr)>> MessageHandlers;`
- L109 _private member_ `TSharedPtr<int> AliveSemaphore;` — we can used WeakPtrs pointing to this SharedPtr to detect when this class is destroyed that allows the following Safe... delayed executions to safely check if the connection no longer exists.
- L115 _private prototype_ `template<typename T> void SafeGameThreadExecute(T&& Func);` — These templates are defined in the cpp since theyre private and we dont want to include the private include file "Utils.h" here in this public header.
- L116 _private prototype_ `template<typename T> void SafeGameThreadExecute(T&& Func);` — These templates are defined in the cpp since theyre private and we dont want to include the private include file "Utils.h" here in this public header.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingStatNames.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PixelStreamingStatNames`
- L10 _variable_ `const FName Bitrate = FName(TEXT("bitr` (scope `PixelStreamingStatNames`) — Calculated stats
- L11 _variable_ `const FName BitrateMegabits = FName(TEXT("bitr` (scope `PixelStreamingStatNames`)
- L12 _variable_ `const FName TargetBitrateMegabits = FName(TEXT("targ` (scope `PixelStreamingStatNames`)
- L13 _variable_ `const FName MeanSendDelay = FName(TEXT("capt` (scope `PixelStreamingStatNames`)
- L14 _variable_ `const FName SourceFps = FName(TEXT("capt` (scope `PixelStreamingStatNames`)
- L15 _variable_ `const FName Fps = FName(TEXT("capt` (scope `PixelStreamingStatNames`)
- L16 _variable_ `const FName MeanEncodeTime = FName(TEXT("enco` (scope `PixelStreamingStatNames`)
- L17 _variable_ `const FName EncodedFramesPerSecond = FName(TEXT("enco` (scope `PixelStreamingStatNames`)
- L18 _variable_ `const FName DecodedFramesPerSecond = FName(TEXT("deco` (scope `PixelStreamingStatNames`)
- L19 _variable_ `const FName MeanQPPerSecond = FName(TEXT("qp")` (scope `PixelStreamingStatNames`)
- L20 _variable_ `const FName FramesSentPerSecond = FName(TEXT("tran` (scope `PixelStreamingStatNames`)
- L21 _variable_ `const FName FramesReceivedPerSecond = FName(TEXT("rece` (scope `PixelStreamingStatNames`)
- L24 _variable_ `const FName JitterBufferDelay = FName(TEXT("jitt` (scope `PixelStreamingStatNames`) — WebRTC stats
- L25 _variable_ `const FName FramesSent = FName(TEXT("fram` (scope `PixelStreamingStatNames`)
- L26 _variable_ `const FName FramesReceived = FName(TEXT("fram` (scope `PixelStreamingStatNames`)
- L27 _variable_ `const FName FramesPerSecond = FName(TEXT("fram` (scope `PixelStreamingStatNames`)
- L28 _variable_ `const FName FramesDecoded = FName(TEXT("fram` (scope `PixelStreamingStatNames`)
- L29 _variable_ `const FName FramesDropped = FName(TEXT("fram` (scope `PixelStreamingStatNames`)
- L30 _variable_ `const FName FramesCorrupted = FName(TEXT("fram` (scope `PixelStreamingStatNames`)
- L31 _variable_ `const FName PartialFramesLost = FName(TEXT("part` (scope `PixelStreamingStatNames`)
- L32 _variable_ `const FName FullFramesLost = FName(TEXT("full` (scope `PixelStreamingStatNames`)
- L33 _variable_ `const FName HugeFramesSent = FName(TEXT("huge` (scope `PixelStreamingStatNames`)
- L34 _variable_ `const FName JitterBufferTargetDelay = FName(TEXT("jitt` (scope `PixelStreamingStatNames`)
- L35 _variable_ `const FName InterruptionCount = FName(TEXT("inte` (scope `PixelStreamingStatNames`)
- L36 _variable_ `const FName TotalInterruptionDuration = FName(TEXT("tota` (scope `PixelStreamingStatNames`)
- L37 _variable_ `const FName FreezeCount = FName(TEXT("free` (scope `PixelStreamingStatNames`)
- L38 _variable_ `const FName PauseCount = FName(TEXT("paus` (scope `PixelStreamingStatNames`)
- L39 _variable_ `const FName TotalFreezesDuration = FName(TEXT("tota` (scope `PixelStreamingStatNames`)
- L40 _variable_ `const FName TotalPausesDuration = FName(TEXT("tota` (scope `PixelStreamingStatNames`)
- L41 _variable_ `const FName FirCount = FName(TEXT("firC` (scope `PixelStreamingStatNames`)
- L42 _variable_ `const FName PliCount = FName(TEXT("pliC` (scope `PixelStreamingStatNames`)
- L43 _variable_ `const FName NackCount = FName(TEXT("nack` (scope `PixelStreamingStatNames`)
- L44 _variable_ `const FName SliCount = FName(TEXT("sliC` (scope `PixelStreamingStatNames`)
- L45 _variable_ `const FName RetransmittedBytesSent = FName(TEXT("retr` (scope `PixelStreamingStatNames`)
- L46 _variable_ `const FName TargetBitrate = FName(TEXT("targ` (scope `PixelStreamingStatNames`)
- L47 _variable_ `const FName TotalEncodeBytesTarget = FName(TEXT("tota` (scope `PixelStreamingStatNames`)
- L48 _variable_ `const FName KeyFramesEncoded = FName(TEXT("keyF` (scope `PixelStreamingStatNames`)
- L49 _variable_ `const FName FrameWidth = FName(TEXT("fram` (scope `PixelStreamingStatNames`)
- L50 _variable_ `const FName FrameHeight = FName(TEXT("fram` (scope `PixelStreamingStatNames`)
- L51 _variable_ `const FName BytesSent = FName(TEXT("byte` (scope `PixelStreamingStatNames`)
- L52 _variable_ `const FName BytesReceived = FName(TEXT("byte` (scope `PixelStreamingStatNames`)
- L53 _variable_ `const FName QPSum = FName(TEXT("qpSu` (scope `PixelStreamingStatNames`)
- L54 _variable_ `const FName TotalEncodeTime = FName(TEXT("tota` (scope `PixelStreamingStatNames`)
- L55 _variable_ `const FName TotalPacketSendDelay = FName(TEXT("tota` (scope `PixelStreamingStatNames`)
- L56 _variable_ `const FName FramesEncoded = FName(TEXT("fram` (scope `PixelStreamingStatNames`)
- L57 _variable_ `const FName QualityController = FName(TEXT("qual` (scope `PixelStreamingStatNames`)
- L58 _variable_ `const FName AvgSendDelay = FName(TEXT("pack` (scope `PixelStreamingStatNames`)
- L59 _variable_ `const FName MessagesSent = FName(TEXT("mess` (scope `PixelStreamingStatNames`)
- L60 _variable_ `const FName MessagesReceived = FName(TEXT("mess` (scope `PixelStreamingStatNames`)
- L63 _variable_ `const FName DataChannelBytesSent = FName(TEXT("data` (scope `PixelStreamingStatNames`) — Data-channel stats
- L64 _variable_ `const FName DataChannelBytesReceived = FName(TEXT("data` (scope `PixelStreamingStatNames`)
- L65 _variable_ `const FName DataChannelMessagesSent = FName(TEXT("data` (scope `PixelStreamingStatNames`)
- L66 _variable_ `const FName DataChannelMessagesReceived = FName(TEXT("data` (scope `PixelStreamingStatNames`)
- L69 _variable_ `const FName InputController = FName(TEXT("inpu` (scope `PixelStreamingStatNames`) — Pixel Streaming specific stats

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingTrace.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L17 _prototype_ `void ExtendJsonWithField(const FString& Descriptor, FString FieldName, FString StringValue, FString& OutNewDescriptor, bool& OutSuccess);` (scope `UE::PixelStreaming`) — Extends an existing JSON string with a new name: value property. @param Descriptor The JSON string. @param FieldName The field name to add the json string. @param StringValue The value to set in the new field. @param OutNewDescriptor The new JSON string. @param OutSuccess True if we were able to extend the JSON string.
- L26 _prototype_ `void ExtractJsonFromDescriptor(FString Descriptor, FString FieldName, FString& OutStringValue, bool& OutSuccess);` (scope `UE::PixelStreaming`) — Extract a field's value from a JSON string. @param Descriptor The JSON string. @param FieldName The field name to extract a value from. @param OutStringValue The value from the extracted field. @param OutSuccess True if we were able to extract the value.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingVideoInput.h` (Public)


#### class `FPixelStreamingVideoInput`  
`class FPixelStreamingVideoInput : public IPixelCaptureCapturerSource`  
_L22-86_
- inherits: `IPixelCaptureCapturerSource`
- desc: The input of the Pixel Streaming system. Frames enter the system when OnFrame is called. The input buffers might need to be converted/adapted to suit the selected video encoder. CreateAdaptProcess should create a PixelStreamingFrameAdapterProcess that does this work.
- L25 _public prototype_ `FPixelStreamingVideoInput();`
- L26 _public prototype_ `virtual ~FPixelStreamingVideoInput() = default;`
- L28 _public prototype_ `void AddOutputFormat(int32 Format);`
- L34 _public prototype_ `virtual void OnFrame(const IPixelCaptureInputFrame& InputFrame);` — Feed the input with a new captured frame. @param InputFrame The raw input frame.
- L39 _public prototype_ `virtual FString ToString();` — A human readable identifier used when displaying what the streamer is streaming in the toolbar
- L41 _public function_ `bool IsReady() const`
- L46 _public prototype_ `rtc::scoped_refptr<webrtc::VideoFrameBuffer> GetFrameBuffer();` — Used internally by the encode process.
- L52 _public prototype_ `rtc::scoped_refptr<webrtc::VideoFrameBuffer> GetEmptyFrameBuffer();` — Used internally by the encode process. @return A frame buffer that has a null capturer.
- L57 _public prototype_ `TSharedPtr<IPixelCaptureOutputFrame> RequestFormat(int32 Format, TOptional<FIntPoint> Resolution = TOptional<FIntPoint>());`
- L63 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFrameCaptured);` — This is broadcast each time a frame exits the adapt process. Used to synchronize framerates with input rates. This should be called once per frame taking into consideration all the target formats and layers within the frame.
- L64 _public member_ `FOnFrameCaptured OnFrameCaptured;`
- L67 _private member_ `int32 LastFrameWidth = -1;`
- L68 _private member_ `int32 LastFrameHeight = -1;`
- L69 _private member_ `bool Ready = false;`
- L71 _private member_ `TSharedPtr<FPixelCaptureCapturerMultiFormat> FrameCapturer;`
- L72 _private member_ `FDelegateHandle CaptureCompleteHandle;`
- L73 _private member_ `TSet<int32> PreInitFormats;`
- L75 _private prototype_ `void CreateFrameCapturer();`
- L76 _private prototype_ `void OnCaptureComplete();`
- L78 _private prototype_ `static uint32 GetUniqueStreamId();`
- L81 _private member_ `uint32 StreamId = 0;` — video inputs need a unique stream id so we can properly divide hardware encoders between inputs
- L82 _private member_ `static uint32 NextStreamId;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PixelStreaming` (scope `UE`)
- L63 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFrameCaptured);` — This is broadcast each time a frame exits the adapt process. Used to synchronize framerates with input rates. This should be called once per frame taking into consideration all the target formats and layers within the frame.

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingVideoInputBackBuffer.h` (Public)


#### class `FPixelStreamingVideoInputBackBuffer`  
`class FPixelStreamingVideoInputBackBuffer : public FPixelStreamingVideoInputRHI`  
_L14-27_
- inherits: `FPixelStreamingVideoInputRHI`
- desc: Use this if you want to send the UE backbuffer as video input.
- L17 _public prototype_ `static TSharedPtr<FPixelStreamingVideoInputBackBuffer> Create();`
- L18 _public prototype_ `virtual ~FPixelStreamingVideoInputBackBuffer();`
- L20 _public prototype_ `virtual FString ToString() override;`
- L22 _private prototype_ `FPixelStreamingVideoInputBackBuffer() = default;`
- L24 _private prototype_ `void OnBackBufferReady(SWindow& SlateWindow, ISlateViewportProvider& ViewportProvider);`
- L26 _private member_ `FDelegateHandle DelegateHandle;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingVideoInputI420.h` (Public)


#### class `FPixelStreamingVideoInputI420`  
`class FPixelStreamingVideoInputI420 : public FPixelStreamingVideoInput`  
_L10-18_
- inherits: `FPixelStreamingVideoInput`
- desc: A Generic video input for I420 frames
- L13 _public prototype_ `FPixelStreamingVideoInputI420() = default;`
- L14 _public prototype_ `virtual ~FPixelStreamingVideoInputI420() = default;`
- L17 _protected prototype_ `virtual TSharedPtr<FPixelCaptureCapturer> CreateCapturer(int32 FinalFormat, FIntPoint Resolution) override;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingVideoInputNV12.h` (Public)


#### class `FPixelStreamingVideoInputNV12`  
`class FPixelStreamingVideoInputNV12 : public FPixelStreamingVideoInput`  
_L10-18_
- inherits: `FPixelStreamingVideoInput`
- desc: A Generic video input for NV12 frames
- L13 _public prototype_ `FPixelStreamingVideoInputNV12() = default;`
- L14 _public prototype_ `virtual ~FPixelStreamingVideoInputNV12() = default;`
- L17 _protected prototype_ `virtual TSharedPtr<FPixelCaptureCapturer> CreateCapturer(int32 FinalFormat, FIntPoint Resolution) override;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingVideoInputPIEViewport.h` (Public)


#### class `FPixelStreamingVideoInputPIEViewport`  
`class FPixelStreamingVideoInputPIEViewport : public FPixelStreamingVideoInputRHI`  
_L12-26_
- inherits: `FPixelStreamingVideoInputRHI`
- desc: An extension of the back buffer input that can handle PIE sessions. Primarily to be used in blueprints
- L15 _public prototype_ `static TSharedPtr<FPixelStreamingVideoInputPIEViewport> Create();`
- L16 _public prototype_ `virtual ~FPixelStreamingVideoInputPIEViewport();`
- L18 _public prototype_ `virtual FString ToString() override;`
- L21 _private prototype_ `FPixelStreamingVideoInputPIEViewport() = default;`
- L23 _private prototype_ `void OnViewportRendered(FViewport* InViewport);`
- L25 _private member_ `FDelegateHandle DelegateHandle;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingVideoInputRHI.h` (Public)


#### class `FPixelStreamingVideoInputRHI`  
`class FPixelStreamingVideoInputRHI : public FPixelStreamingVideoInput`  
_L10-18_
- inherits: `FPixelStreamingVideoInput`
- desc: A Generic video input for RHI frames
- L13 _public prototype_ `FPixelStreamingVideoInputRHI() = default;`
- L14 _public prototype_ `virtual ~FPixelStreamingVideoInputRHI() = default;`
- L17 _protected prototype_ `virtual TSharedPtr<FPixelCaptureCapturer> CreateCapturer(int32 FinalFormat, FIntPoint Resolution) override;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingVideoInputRenderTarget.h` (Public)


#### class `FPixelStreamingVideoInputRenderTarget`  
`class FPixelStreamingVideoInputRenderTarget : public FPixelStreamingVideoInputRHI`  
_L15-28_
- inherits: `FPixelStreamingVideoInputRHI`
- desc: Use this if you want to send the contents of a render target.
- L18 _public prototype_ `static TSharedPtr<FPixelStreamingVideoInputRenderTarget> Create(UTextureRenderTarget2D* Target);`
- L19 _public prototype_ `virtual ~FPixelStreamingVideoInputRenderTarget();`
- L21 _public prototype_ `virtual FString ToString() override;`
- L23 _private prototype_ `FPixelStreamingVideoInputRenderTarget(UTextureRenderTarget2D* InTarget);`
- L24 _private prototype_ `void OnEndFrameRenderThread();`
- L26 _private member_ `UTextureRenderTarget2D* Target = nullptr;`
- L27 _private member_ `FDelegateHandle DelegateHandle;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingVideoSink.h` (Public)


#### class `FPixelStreamingVideoSink`  
`class FPixelStreamingVideoSink : public rtc::VideoSinkInterface<webrtc::VideoFrame>`  
_L9-29_
- inherits: `rtc::VideoSinkInterface<webrtc::VideoFrame>`
- L12 _public prototype_ `FPixelStreamingVideoSink() = default;`
- L13 _public prototype_ `~FPixelStreamingVideoSink() = default;`
- L17 _public prototype_ `virtual void OnFrame(const webrtc::VideoFrame& Frame) override;` — This method handles the conversion from a WebRTC frame to a UE texture
- L22 _public function_ `virtual void OnFrame(FTextureRHIRef Frame)` — Derivative classes implement this method to handle how the decoded textures should actually be displayed eg PixelStreamingBlueprint/PixelStreamingPeerVideoSink
- L25 _private member_ `FCriticalSection RenderSyncContext;`
- L26 _private member_ `FPooledRenderTargetDesc RenderTargetDescriptor;`
- L27 _private member_ `TRefCountPtr<IPooledRenderTarget> RenderTarget;`
- L28 _private member_ `TArray<uint8_t> Buffer;`

### `Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingWebRTCIncludes.h` (Public)
_(no declarations extracted)_
