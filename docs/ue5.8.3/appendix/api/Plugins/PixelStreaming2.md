# Plugins / PixelStreaming2

- module root: `Plugins/Media/PixelStreaming2/Source/PixelStreaming2`
- headers: 40; symbols: 698
- symbol kinds: class=36, delegate=33, externvar=6, function=67, macro=23, member=149, namespace=61, prototype=307, struct=5, typedef=8, variable=3
- PrivateDependencyModuleNames: Core, D3D11RHI, D3D12RHI, Engine, PixelStreaming2Settings, UnrealEd, VulkanRHI
- PublicDependencyModuleNames: AVCodecsCore, AVCodecsCoreRHI, AudioMixer, AudioPlatformConfiguration, CoreUObject, Json, MediaIOCore, MediaUtils, PixelCapture, PixelStreaming2Core, PixelStreaming2Input, RHI, RenderCore, Renderer, SignalProcessing, Slate, SlateCore, TraceLog, WebRTC

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/AudioCapturer.h` (Internal)


#### class `UE::PixelStreaming2::FMixAudioTask`  
`class FMixAudioTask : public FPixelStreamingTickableTask`  
_L19-33_
- inherits: `FPixelStreamingTickableTask`
- L22 _public prototype_ `FMixAudioTask(TSharedPtr<FAudioCapturer> Capturer);`
- L24 _public prototype_ `virtual ~FMixAudioTask() = default;`
- L27 _public prototype_ `virtual void Tick(float DeltaMs) override;`
- L28 _public prototype_ `virtual const FString& GetName() const override;`
- L32 _protected member_ `TWeakPtr<FAudioCapturer> Capturer;`

#### class `UE::PixelStreaming2::FAudioCapturer`  
`class FAudioCapturer : public Audio::FPatchMixer, public TSharedFromThis<FAudioCapturer>`  
_L35-94_
- inherits: `Audio::FPatchMixer,TSharedFromThis<FAudioCapturer>`
- L39 _public prototype_ `template <typename T> static TSharedPtr<T> Create(const int32 InSampleRate = 48000, const int32 InNumChannels = 2, const float InSampleSizeInSeconds = 0.5f);`
- L41 _public prototype_ `virtual ~FAudioCapturer() = default;`
- L44 _public prototype_ `void CreateAudioProducer(Audio::FDeviceId AudioDeviceId);` — AudioProducer lifecycle methods triggered by engine delegates
- L45 _public prototype_ `void RemoveAudioProducer(Audio::FDeviceId AudioDeviceId);`
- L48 _public prototype_ `void AddAudioProducer(TSharedPtr<IPixelStreaming2AudioProducer> AudioProducer);` — Methods for managing custom audio producers that will have their audio mixed in with engine audio
- L49 _public prototype_ `void RemoveAudioProducer(TSharedPtr<IPixelStreaming2AudioProducer> AudioProducer);`
- L52 _public prototype_ `virtual void PushAudio(const float* AudioData, int32 NumSamples, int32 NumChannels, int32 SampleRate);` — Called when mixed audio has been produced (and optionally dumped) and is ready to be sent for encoding
- L57 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_FourParams(FOnAudioBuffer, const int16_t*, int32, int32, const int32);` — This is broadcast each time audio is captured. Tracks should bind to this and push the audio into the track
- L58 _public member_ `FOnAudioBuffer OnAudioBuffer;`
- L61 _public prototype_ `void ProcessAudio();`
- L65 _protected prototype_ `FAudioCapturer(const int32 SampleRate = 48000, const int32 NumChannels = 2, const float SampleSizeInSeconds = 0.5f);`
- L69 _protected prototype_ `void Initialize();` — Required to be called by derived classes if the class is not constructed with FAudioCapturer::Create. It initializes members that require TSharedPtr to FAudioCapturer
- L71 _protected prototype_ `void OnDebugDumpAudioChanged(IConsoleVariable* Var);`
- L72 _protected prototype_ `void OnEnginePreExit();`
- L73 _protected prototype_ `void WriteDebugAudio();`
- L76 _protected prototype_ `int32 GetSampleRate() const;`
- L77 _protected prototype_ `int32 GetNumChannels() const;`
- L78 _protected prototype_ `int32 GetMaxBufferSize() const;`
- L82 _protected member_ `TSharedPtr<FMixAudioTask> MixerTask;`
- L85 _protected member_ `TMap<Audio::FDeviceId, TSharedPtr<FAudioProducer>> EngineAudioProducers;` — Audio producers created by the engine that capture audio from specific devices
- L87 _protected member_ `TMap<TSharedPtr<IPixelStreaming2AudioProducer>, TSharedPtr<FAudioProducer>> UserAudioProducers;` — Audio producers created by the user that push audio from arbitrary sources
- L89 _protected member_ `int32 SampleRate;`
- L90 _protected member_ `int32 NumChannels;`
- L91 _protected member_ `float SampleSizeSeconds;`
- L93 _protected member_ `Audio::TSampleBuffer<int16_t> DebugDumpAudioBuffer;`
- L97 _function_ `template <typename T> TSharedPtr<T> FAudioCapturer::Create(const int32 InSampleRate, const int32 InNumChannels, const float InSampleSizeInSeconds)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L57 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_FourParams(FOnAudioBuffer, const int16_t*, int32, int32, const int32);` — This is broadcast each time audio is captured. Tracks should bind to this and push the audio into the track
- L111 _function_ `FCoreDelegates::OnEnginePreExit.AddLambda([WeakAudioMixingCapturer]() { if (TSharedPtr<T> AudioCapturer = WeakAudioMixingCapturer.Pin()) { AudioCapturer->OnEnginePreExit(); } });` (scope `UE::PixelStreaming2::FAudioCapturer::Create`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/AudioProducer.h` (Internal)


#### class `UE::PixelStreaming2::FAudioProducer`  
`class FAudioProducer : public ISubmixBufferListener, public Audio::FPatchInput`  
_L21-44_
- inherits: `ISubmixBufferListener,Audio::FPatchInput`
- desc: An audio input capable of listening to UE submix's as well as receiving user audio via the OnPushedAudio method. Any received audio will be pushed into the FPatchInput interface for mixing
- L24 _public prototype_ `static TSharedPtr<FAudioProducer> Create(Audio::FDeviceId AudioDeviceId, int32 TargetSampleRate, int32 TargetNumChannels, const Audio::FPatchOutputStrongPtr& PatchOutput);`
- L25 _public prototype_ `static TSharedPtr<FAudioProducer> Create(TSharedPtr<IPixelStreaming2AudioProducer> AudioProducer, int32 TargetSampleRate, int32 TargetNumChannels, const Audio::FPatchOutputStrongPtr& PatchOutput);`
- L26 _public prototype_ `virtual ~FAudioProducer() = default;`
- L29 _public prototype_ `virtual void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 NumSamples, int32 NumChannels, const int32 SampleRate, double AudioClock) override;` — ISubmixBufferListener interface
- L32 _public prototype_ `void OnPushedAudio(const float* AudioData, int32 NumSamples, int32 NumChannels, int32 SampleRate);` — Listener for audio pushed from custom IPixelStreaming2AudioProducer implementations
- L35 _protected prototype_ `FAudioProducer(int32 TargetSampleRate, int32 TargetNumChannels, const Audio::FPatchOutputStrongPtr& PatchOutput);`
- L38 _protected member_ `const int32 TargetSampleRate;`
- L39 _protected member_ `const int32 TargetNumChannels;`
- L40 _protected member_ `bool bIsMuted;`
- L43 _private prototype_ `void OnRawAudio(const float* AudioData, int32 NumSamples, int32 NumChannels, int32 SampleRate);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/AudioSink.h` (Internal)


#### class `UE::PixelStreaming2::FAudioSink`  
`class FAudioSink : public IPixelStreaming2AudioSink`  
_L11-32_
- inherits: `IPixelStreaming2AudioSink`
- L15 _public prototype_ `virtual ~FAudioSink();` — Note: destructor will call destroy on any attached audio consumers
- L17 _public prototype_ `virtual void AddAudioConsumer(const TWeakPtrVariant<IPixelStreaming2AudioConsumer>& AudioConsumer) override;`
- L18 _public prototype_ `virtual void RemoveAudioConsumer(const TWeakPtrVariant<IPixelStreaming2AudioConsumer>& AudioConsumer) override;`
- L20 _public prototype_ `bool HasAudioConsumers();`
- L22 _public prototype_ `void SetMuted(bool bIsMuted);`
- L24 _public prototype_ `void OnAudioData(int16_t* AudioData, uint32 NumFrames, uint32 NumChannels, uint32 SampleRate);`
- L27 _protected member_ `TArray<TWeakPtrVariant<IPixelStreaming2AudioConsumer>> AudioConsumers;`
- L30 _private member_ `FCriticalSection AudioConsumersCS;`
- L31 _private member_ `bool bIsMuted = false;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/AudioSource.h` (Internal)


#### class `UE::PixelStreaming2::FAudioSource`  
`class FAudioSource`  
_L11-22_
- L14 _public prototype_ `virtual ~FAudioSource() = default;`
- L16 _public prototype_ `virtual void OnAudioBuffer(const int16_t* AudioData, int32 NumSamples, int32 NumChannels, const int32 SampleRate);`
- L18 _public prototype_ `void SetMuted(bool bIsMuted);`
- L21 _protected member_ `bool bIsMuted = false;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/Blueprints/PixelStreaming2InputComponent.h` (Internal)


#### class `UPixelStreaming2Input`  
`class UPixelStreaming2Input : public UActorComponent`  
_L15-61_
- reflection: `UCLASS(Blueprintable, ClassGroup = (PixelStreaming2), meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: This component may be attached to an actor to allow UI interactions to be handled as the delegate will be notified about the interaction and will be supplied with a generic descriptor string containing, for example, JSON data. Responses back to the source of the UI interactions may also be sent.
- L20 _public prototype_ `UPixelStreaming2Input(const FObjectInitializer& ObjectInitializer);`
- L21 _public prototype_ `void BeginPlay() override;`
- L22 _public prototype_ `void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L25 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInput, const FString&, Descriptor);` — The delegate which will be notified about a UI interaction.
- L27 _public member_ `FOnInput OnInputEvent;` — `UPROPERTY(BlueprintAssignable, Category = "PixelStreaming2 Input")`
- L34 _public prototype_ `void SendPixelStreaming2Response(const FString& Descriptor);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2 Input")` — Send a response back to the source of the UI interactions. @param Descriptor - A generic descriptor string.
- L48 _public prototype_ `void GetJsonStringValue(FString Descriptor, FString FieldName, FString& StringValue, bool& Success);` — `UFUNCTION(BlueprintPure, Category = "PixelStreaming2 Input")` — Helper function to extract a string field from a JSON descriptor of a UI interaction given its field name. The field name may be hierarchical, delimited by a period. For example, to access the Width value of a Resolution command above you should use "Resolution.Width" to get the width value. @param Descriptor - The UI interaction JSON descriptor. @param FieldName - The name of the field to look for in the JSON. @param StringValue - The string value associated with the field name. @param Success - True if the field exists in the JSON data.
- L60 _public prototype_ `void AddJsonStringValue(const FString& Descriptor, FString FieldName, FString StringValue, FString& NewDescriptor, bool& Success);` — `UFUNCTION(BlueprintPure, Category = "PixelStreaming2 Input")` — Helper function to add a string field to a JSON descriptor. This produces a new descriptor which may then be chained to add further string fields. @param Descriptor - The initial JSON descriptor which may be blank initially. @param FieldName - The name of the field to add to the JSON. @param StringValue - The string value associated with the field name. @param NewDescriptor - The JSON descriptor with the string field added. @param Success - True if the string field could be added successfully.

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInput, const FString&, Descriptor);` — The delegate which will be notified about a UI interaction.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/Blueprints/PixelStreaming2MediaTexture.h` (Internal)


#### class `UPixelStreaming2MediaTexture`  
`class UPixelStreaming2MediaTexture : public UTexture2DDynamic`  
_L21-48_
- reflection: `UCLASS(MinimalAPI, NotBlueprintType, NotBlueprintable, HideDropdown, HideCategories = (ImportSettings, Compression, Texture, Adjustments, Compositing, LevelOfDetail, Object), META = (DisplayName = "PixelStreaming Media Texture"))`
- inherits: `UTexture2DDynamic`
- desc: A Texture Object that can be used in materials etc. that takes updates from webrtc frames.
- L27 _public prototype_ `void ConsumeFrame(FTextureRHIRef Frame);` — IPixelStreamingVideoConsumer implementation
- L29 _public prototype_ `const FTextureResource* GetResource() const;`
- L33 _protected prototype_ `virtual void BeginDestroy() override;` — UObject overrides.
- L34 _protected prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L37 _protected prototype_ `virtual FTextureResource* CreateResource() override;` — UTexture implementation
- L40 _private prototype_ `void InitializeResources();`
- L43 _private prototype_ `void UpdateTextureReference(FRHICommandList& RHICmdList, FTextureRHIRef Reference);` — updates the internal texture resource after each frame.
- L45 _private member_ `FCriticalSection RenderSyncContext;`
- L47 _private member_ `UE::PixelStreaming2::FPixelStreaming2MediaTextureResource* CurrentResource;` — NOTE: This type has to be a raw ptr because UE will manage the lifetime of it

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/Blueprints/PixelStreaming2VideoProducer.h` (Internal)


#### class `UPixelStreaming2VideoProducerBase`  
`class UPixelStreaming2VideoProducerBase : public UObject`  
_L16-25_
- reflection: `UCLASS(MinimalAPI, NotBlueprintType, NotBlueprintable, Category = "PixelStreaming2", META = (DisplayName = "Video Producer"))`
- inherits: `UObject`
- desc: The base video producer blueprint class
- L21 _public function_ `virtual TSharedPtr<IPixelStreaming2VideoProducer> GetVideoProducer()`
- L24 _protected member_ `TSharedPtr<IPixelStreaming2VideoProducer> VideoProducer;`

#### class `UPixelStreaming2VideoProducerBackBuffer`  
`class UPixelStreaming2VideoProducerBackBuffer : public UPixelStreaming2VideoProducerBase`  
_L31-37_
- reflection: `UCLASS(MinimalAPI, NotBlueprintType, NotBlueprintable, Category = "PixelStreaming2", META = (DisplayName = "Back Buffer Video Producer"))`
- inherits: `UPixelStreaming2VideoProducerBase`
- desc: A video producer that streams the Unreal Engine's back buffer
- L36 _public prototype_ `virtual TSharedPtr<IPixelStreaming2VideoProducer> GetVideoProducer() override;`

#### class `UPixelStreaming2VideoProducerMediaCapture`  
`class UPixelStreaming2VideoProducerMediaCapture : public UPixelStreaming2VideoProducerBase`  
_L43-49_
- reflection: `UCLASS(MinimalAPI, NotBlueprintType, NotBlueprintable, Category = "PixelStreaming2", META = (DisplayName = "Media Capture Video Producer"))`
- inherits: `UPixelStreaming2VideoProducerBase`
- desc: A video producer that streams the Unreal Engine's back buffer but uses the MediaIO Framework to capture the frame rather than Pixel Capture
- L48 _public prototype_ `virtual TSharedPtr<IPixelStreaming2VideoProducer> GetVideoProducer() override;`

#### class `UPixelStreaming2VideoProducerRenderTarget`  
`class UPixelStreaming2VideoProducerRenderTarget : public UPixelStreaming2VideoProducerBase`  
_L55-64_
- reflection: `UCLASS(MinimalAPI, NotBlueprintType, NotBlueprintable, Category = "PixelStreaming2", META = (DisplayName = "Render Target Video Producer"))`
- inherits: `UPixelStreaming2VideoProducerBase`
- desc: A video producer that streams the specified render target
- L61 _public member_ `TObjectPtr<UTextureRenderTarget2D> Target;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Video, AssetRegistrySearchable)`
- L63 _public prototype_ `virtual TSharedPtr<IPixelStreaming2VideoProducer> GetVideoProducer() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PIXELSTREAMING2_API`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/PixelStreaming2Common.h` (Internal)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L10 _externvar_ `extern TThreadSafeMap<uintptr_t, UPixelStreaming2Input*> InputComponents;` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/PixelStreaming2MediaIOCapture.h` (Internal)


#### class `UPixelStreaming2MediaIOCapture`  
`class UPixelStreaming2MediaIOCapture : public UMediaCapture`  
_L15-80_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMediaCapture`
- L24 _public prototype_ `virtual void OnRHIResourceCaptured_RenderingThread( FRHICommandListImmediate& RHICmdList, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture) override;` — GPU copy methods
- L33 _public prototype_ `virtual void OnCustomCapture_RenderingThread( FRDGBuilder& GraphBuilder, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FRDGTextureRef InSourceTexture, FRDGTextureRef OutputTexture, const FRHICopyTextureInfo& CopyInfo, FVector2D CropU, FVector2D CropV) override;` — Custom conversion operation for Mac
- L43 _public prototype_ `virtual bool InitializeCapture() override;`
- L44 _public prototype_ `virtual bool PostInitializeCaptureViewport(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L45 _public function_ `virtual bool ShouldCaptureRHIResource() const`
- L46 _public prototype_ `virtual void StopCaptureImpl(bool bAllowPendingFrameToBeProcess) override;`
- L48 _public prototype_ `virtual ETextureCreateFlags GetOutputTextureFlags() const override;` — We override the texture flags because on Mac we want the texture to have the CPU_Readback flag
- L49 _public prototype_ `virtual void WaitForGPU(FRHITexture* InRHITexture) override;`
- L50 _public prototype_ `virtual TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> GetCaptureFrameUserData_GameThread() override;`
- L53 _public function_ `TSharedPtr<FSceneViewport> GetViewport() const`
- L54 _public prototype_ `virtual void ViewportResized(FViewport* Viewport, uint32 ResizeCode);`
- L55 _public function_ `bool WasViewportResized() const`
- L56 _public function_ `void SetVideoProducer(TSharedPtr<IPixelStreaming2VideoProducer> InVideoProducer)`
- L57 _public function_ `TWeakPtr<IPixelStreaming2VideoProducer> GetVideoProducer()`
- L59 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCaptureViewportInitialized);`
- L60 _public member_ `FOnCaptureViewportInitialized OnCaptureViewportInitialized;`
- L63 _private prototype_ `void HandleCapturedFrame(FTextureRHIRef InTexture, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData);`
- L64 _private prototype_ `void UpdateCaptureResolution(int32 Width, int32 Height);`
- L67 _private member_ `TWeakPtr<FSceneViewport> SceneViewport;`
- L68 _private member_ `TWeakPtr<IPixelStreaming2VideoProducer> VideoProducer;`
- L71 _private member_ `bool bViewportResized = false;` — We track whether the viewport has been resized since we created this capturer as resize means restart capturer.
- L74 _private member_ `TUniquePtr<FIntPoint> CaptureResolution;` — Tracks the captured resolution, we use this to determine if resize events contain a different resolution than what we previously captured.
- L77 _private member_ `bool bDoGPUCopy = true;` — Whether we want the UMediaCapture to read back to frame into cpu memory or not.
- L79 _private member_ `TStripedMap<32, uintptr_t, FGPUFenceRHIRef> Fences;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L59 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCaptureViewportInitialized);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/PixelStreaming2Trace.h` (Internal)
_(no declarations extracted)_

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/SoundGenerator.h` (Internal)


#### class `UE::PixelStreaming2::FSoundGenerator`  
`class FSoundGenerator : public ::ISoundGenerator`  
_L16-52_
- inherits: `::ISoundGenerator`
- desc: An `ISoundGenerator` implementation to pump some audio from EpicRtc into this synth component
- L19 _public prototype_ `FSoundGenerator();`
- L20 _public prototype_ `virtual ~FSoundGenerator() = default;`
- L23 _public prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;` — Called when a new buffer is required.
- L26 _public prototype_ `virtual int32 GetDesiredNumSamplesToRenderPerCallback() const;` — Returns the number of samples to render per callback
- L29 _public prototype_ `virtual void OnBeginGenerate();` — Optional. Called on audio generator thread right when the generator begins generating.
- L32 _public prototype_ `virtual void OnEndGenerate();` — Optional. Called on audio generator thread right when the generator ends generating.
- L35 _public prototype_ `virtual bool IsFinished() const;` — Optional. Can be overridden to end the sound when generating is finished.
- L37 _public prototype_ `void AddAudio(const int16* AudioData, int SampleRate, size_t NumChannels, size_t NumFrames);`
- L39 _public prototype_ `bool IsInitialized();`
- L40 _public prototype_ `void EmptyBuffers();`
- L41 _public prototype_ `void Initialize(const FSoundGeneratorInitParams& InitParams);`
- L44 _private member_ `FSoundGeneratorInitParams Params;`
- L45 _private member_ `TArray<float> Buffer;`
- L46 _private member_ `FCriticalSection CriticalSection;`
- L49 _public member_ `std::atomic<bool> bInitialized = false;`
- L50 _public member_ `std::atomic<bool> bGeneratingAudio = false;`
- L51 _public member_ `std::atomic<bool> bShouldGenerateAudio = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/StreamerReconnectTimer.h` (Internal)


#### class `UE::PixelStreaming2::FStreamerReconnectTimer`  
`class FStreamerReconnectTimer : public FTickableGameObject`  
_L19-44_
- inherits: `FTickableGameObject`
- desc: An interval timer that triggers reconnects when `IPixelStreaming2Streamer` has it session disconnect. Timer takes a `TWeakPtr<IPixelStreaming2Streamer>`, meaning the streamer object must exist for the timer to do anything. Note: this timer runs on the game thread and its reconnect interval is controlled by the CVar UPixelStreaming2PluginSettings::CVarSignalingReconnectInterval
- L22 _public prototype_ `FStreamerReconnectTimer() = default;`
- L23 _public prototype_ `virtual ~FStreamerReconnectTimer() = default;`
- L24 _public prototype_ `void Start(TWeakPtr<IPixelStreaming2Streamer> InWeakStreamer);`
- L25 _public prototype_ `void Stop();`
- L26 _public prototype_ `void Reset();`
- L29 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L30 _public function_ `virtual bool IsTickableInEditor() const override`
- L31 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L32 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L35 _public prototype_ `DECLARE_EVENT(FStreamerReconnectTimer, FOnExceededMaxReconnectAttempts);`
- L36 _public member_ `FOnExceededMaxReconnectAttempts OnExceededMaxReconnectAttempts;`
- L39 _private member_ `TWeakPtr<IPixelStreaming2Streamer> WeakStreamer;`
- L41 _private member_ `bool bEnabled = false;`
- L42 _private member_ `uint64 NumReconnectAttempts = 0;`
- L43 _private member_ `uint64 LastReconnectCycles = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L35 _delegate_ `DECLARE_EVENT(FStreamerReconnectTimer, FOnExceededMaxReconnectAttempts);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/ThreadSafeMap.h` (Internal)


#### class `UE::PixelStreaming2::TThreadSafeMap`  
`template <typename InKeyType, typename InValueType, typename SetAllocator = FDefaultSetAllocator, typename KeyFuncs = TDefaultMapHashableKeyFuncs<InKeyType, InValueType, false>> class TThreadSafeMap : protected TSortableMapBase<InKeyType, InValueType, SetAllocator, KeyFuncs>`  
_L13-338_
- inherits: `TSortableMapBase<InKeyType,InValueType,SetAllocator,KeyFuncs>`
- desc: A TThreadSafeMapBase specialization that only allows a single value associated with each key whilst being thread safe.
- L21 _public typedef_ `typedef InKeyType KeyType;`
- L22 _public typedef_ `typedef InValueType ValueType;`
- L23 _public typedef_ `typedef SetAllocator SetAllocatorType;`
- L24 _public typedef_ `typedef KeyFuncs KeyFuncsType;`
- L26 _public typedef_ `typedef TSortableMapBase<KeyType, ValueType, SetAllocator, KeyFuncs> Super;`
- L27 _public typedef_ `typedef typename Super::KeyInitType KeyInitType;`
- L31 _public typedef_ `typedef typename Super::KeyConstPointerType KeyConstPointerType;` — `UE_DEPRECATED(5.8, "KeyConstPointerType is deprecated - use KeyInitType instead.")`
- L34 _public prototype_ `TThreadSafeMap() = default;`
- L35 _public prototype_ `TThreadSafeMap(TThreadSafeMap&&) = default;`
- L36 _public prototype_ `TThreadSafeMap(const TThreadSafeMap&) = default;`
- L37 _public prototype_ `TThreadSafeMap& operator=(TThreadSafeMap&&) = default;`
- L38 _public prototype_ `TThreadSafeMap& operator=(const TThreadSafeMap&) = default;`
- L42 _public function_ `template <typename OtherSetAllocator> TThreadSafeMap(TThreadSafeMap<KeyType, ValueType, OtherSetAllocator, KeyFuncs>&& Other) : Super(MoveTemp(Other))` — Constructor for moving elements from a TThreadSafeMap with a different SetAllocator
- L49 _public function_ `template <typename OtherSetAllocator> TThreadSafeMap(const TThreadSafeMap<KeyType, ValueType, OtherSetAllocator, KeyFuncs>& Other) : Super(Other)` — Constructor for copying elements from a TThreadSafeMap with a different SetAllocator
- L55 _public function_ `TThreadSafeMap(std::initializer_list<TPairInitializer<const KeyType&, const ValueType&>> InitList)` — Constructor which gets its elements from a native initializer list
- L68 _public function_ `template <typename OtherSetAllocator> TThreadSafeMap& operator=(TThreadSafeMap<KeyType, ValueType, OtherSetAllocator, KeyFuncs>&& Other)` — Assignment operator for moving elements from a TThreadSafeMap with a different SetAllocator
- L84 _public function_ `template <typename OtherSetAllocator> TThreadSafeMap& operator=(const TThreadSafeMap<KeyType, ValueType, OtherSetAllocator, KeyFuncs>& Other)` — Assignment operator for copying elements from a TThreadSafeMap with a different SetAllocator
- L99 _public function_ `TThreadSafeMap& operator=(std::initializer_list<TPairInitializer<const KeyType&, const ValueType&>> InitList)` — Assignment operator which gets its elements from a native initializer list
- L119 _public function_ `FORCEINLINE bool RemoveAndCopyValue(KeyInitType Key, ValueType& OutRemovedValue)` — Remove the pair with the specified key and copies the value that was removed to the ref parameter @param Key The key to search for @param OutRemovedValue If found, the value that was removed (not modified if the key was not found) @return whether or not the key was found
- L136 _public function_ `template <typename ComparableKey> FORCEINLINE bool RemoveAndCopyValueByHash(uint32 KeyHash, const ComparableKey& Key, ValueType& OutRemovedValue)` — See RemoveAndCopyValue() and class documentation section on ByHash() functions
- L159 _public function_ `FORCEINLINE ValueType FindAndRemoveChecked(KeyInitType Key)` — Find a pair with the specified key, removes it from the map, and returns the value part of the pair. If no pair was found, an exception is thrown. @param Key the key to search for @return whether or not the key was found
- L177 _public function_ `template <typename OtherSetAllocator> void Append(TThreadSafeMap<KeyType, ValueType, OtherSetAllocator, KeyFuncs>&& OtherMap)` — Move all items from another map into our map (if any keys are in both, the value from the other map wins) and empty the other map. @param OtherMap The other map of items to move the elements from.
- L197 _public function_ `template <typename OtherSetAllocator> void Append(const TThreadSafeMap<KeyType, ValueType, OtherSetAllocator, KeyFuncs>& OtherMap)` — Add all items from another map to our map (if any keys are in both, the value from the other map wins). @param OtherMap The other map of items to add.
- L208 _public function_ `FORCEINLINE ValueType& operator[](KeyInitType Key)`
- L215 _public function_ `FORCEINLINE const ValueType& operator[](KeyInitType Key) const`
- L224 _public function_ `template <typename T> void Apply(T&& Visitor)` — Note: Do not call a map method inside a visitor or you will deadlock
- L235 _public function_ `template <typename T> void ApplyUntil(T&& Visitor)` — Note: Do not call a map method inside a visitor or you will deadlock
- L247 _public function_ `FORCEINLINE ValueType& FindOrAdd(KeyInitType Key)`
- L254 _public function_ `FORCEINLINE ValueType* Find(KeyInitType Key)`
- L261 _public function_ `FORCEINLINE ValueType FindRef(KeyInitType Key)`
- L268 _public function_ `FORCEINLINE int32 Remove(KeyInitType Key)`
- L275 _public function_ `FORCEINLINE bool IsEmpty()`
- L282 _public function_ `FORCEINLINE void Empty(int32 ExpectedNumElements = 0)`
- L294 _public function_ `template <typename InSetKeyFuncs, typename InSetAllocator> int32 GetKeys(TSet<KeyType, InSetKeyFuncs, InSetAllocator>& OutKeys)`
- L301 _public function_ `[[nodiscard]] FORCEINLINE bool Contains(KeyInitType Key)`
- L308 _public function_ `FORCEINLINE ValueType& Add(const KeyType& InKey, const ValueType& InValue)`
- L315 _public function_ `FORCEINLINE ValueType& Add(const KeyType& InKey, ValueType&& InValue)`
- L322 _public function_ `FORCEINLINE ValueType& Add(KeyType&& InKey, const ValueType& InValue)`
- L329 _public function_ `FORCEINLINE ValueType& Add(KeyType&& InKey, ValueType&& InValue)`
- L337 _private member_ `mutable FCriticalSection Mutex;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/TickableTask.h` (Internal)


#### class `UE::PixelStreaming2::FPixelStreamingTickableTask`  
`class FPixelStreamingTickableTask : public TSharedFromThis<FPixelStreamingTickableTask>`  
_L19-46_
- inherits: `TSharedFromThis<FPixelStreamingTickableTask>`
- desc: Base class for a tickable task. Inheriting from this class ensures that your task can be ticked by the PixelStreaming thread. Note it is important to destroy the task when it is no longer in use to save the tick thread.
- L28 _public prototype_ `template <typename T, typename... Args> static TSharedPtr<T> Create(Args&&... InArgs);` — Classes derived from FPixelStreamingTickableTask must construct themselves using this Create method. Using this Create method ensures the class is fully constructed at the time it is added to the PixelStreaming thread.
- L31 _public prototype_ `virtual ~FPixelStreamingTickableTask() = default;`
- L33 _public function_ `virtual void Tick(float DeltaMs)`
- L35 _public prototype_ `virtual const FString& GetName() const = 0;`
- L38 _protected prototype_ `FPixelStreamingTickableTask() = default;`
- L41 _private prototype_ `void Register();`
- L42 _private prototype_ `void Unregister();`
- L64 _function_ `template <typename T, typename... Args> TSharedPtr<T> FPixelStreamingTickableTask::Create(Args&&... InArgs)`

#### struct `UE::PixelStreaming2::FPixelStreamingTaskDeleter`  
`struct FPixelStreamingTaskDeleter`  
_L52-61_
- desc: TUniquePtr custom deleter that handle automatic unregistering of the task. This ensure that the task won't try to be ticked mid-deletion
- L55 _public function_ `template <typename T> void operator()(T* Ptr) const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L13 _typedef_ `template <typename T> using TUniqueTaskPtr = TUniquePtr<T, struct FPixelStreamingTaskDeleter>;` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/UtilsAsync.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L10 _function_ `template <typename T> void DoOnGameThread(T&& Func)` (scope `UE::PixelStreaming2`)
- L18 _function_ `AsyncTask(ENamedThreads::GameThread, [Func]() { Func(); });` (scope `UE::PixelStreaming2::DoOnGameThread`)
- L23 _function_ `template <typename T> void DoOnGameThreadAndWait(uint32 Timeout, T&& Func)` (scope `UE::PixelStreaming2`)
- L32 _function_ `AsyncTask(ENamedThreads::GameThread, [Func, TaskEvent]() { Func(); TaskEvent->Trigger(); });` (scope `UE::PixelStreaming2::DoOnGameThreadAndWait`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/UtilsAudio.h` (Internal)


#### struct `UE::PixelStreaming2::TRawAudio`  
`template <typename T> struct TRawAudio`  
_L15-22_
- L17 _public member_ `T* Data;`
- L18 _public member_ `int32 NumSamples;`
- L19 _public member_ `int32 SampleRate;`
- L20 _public member_ `int32 NumChannels;`
- L21 _public member_ `float Gain = 1.f;`

#### struct `UE::PixelStreaming2::FProcessedAudio`  
`struct FProcessedAudio`  
_L24-31_
- L26 _public member_ `Audio::FAlignedFloatBuffer& Data;`
- L27 _public member_ `int32 NumSamples;`
- L28 _public member_ `int32 SampleRate;`
- L29 _public member_ `int32 NumChannels;`
- L30 _public member_ `float Gain = 1.f;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L34 _function_ `template <typename T> bool ProcessAudio(const TRawAudio<T>& RawAudio, FProcessedAudio& OutProcessedAudio)` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/UtilsCoder.h` (Internal)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L32 _function_ `template <typename TCodec> bool IsHardwareEncoderSupported()` (scope `UE::PixelStreaming2`) — As windows supports many RHIs and many codecs, we need to check at runtime if the current codec and RHI is compatible. To remove nested switch-cases, this function is templated to take a video encoder config of the target codec. eg: IsHardwareEncoderSupported<FVideoEncoderConfigH264>(); OR IsHardwareEncoderSupported<FVideoEncoderConfigAV1>(); OR ...
- L58 _function_ `template <typename TCodec> bool IsSoftwareEncoderSupported()` (scope `UE::PixelStreaming2`)
- L65 _function_ `template <typename TCodec> bool IsEncoderSupported()` (scope `UE::PixelStreaming2`)
- L82 _function_ `template <typename TCodec> bool IsHardwareDecoderSupported()` (scope `UE::PixelStreaming2`) — As windows supports many RHIs and many codecs, we need to check at runtime if the current codec and RHI is compatible. To remove nested switch-cases, this function is templated to take a video decoder config of the target codec. eg: IsHardwareDecoderSupported<FVideoDecoderConfigVP8>(); OR IsHardwareDecoderSupported<FVideoDecoderConfigAV1>(); OR ...
- L108 _function_ `template <typename TCodec> bool IsSoftwareDecoderSupported()` (scope `UE::PixelStreaming2`)
- L115 _function_ `template <typename TCodec> bool IsDecoderSupported()` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/UtilsCore.h` (Internal)


#### struct `UE::PixelStreaming2::TFakeDeleter`  
`template<typename T> struct TFakeDeleter`  
_L21-26_
- desc: HACK (aidan.possemiers) the AVCodecs API surface wants a SharedPtr for the encoded data but EpicRtc already owns that and we don't want AVCodecs to delete it
- L23 _public function_ `void operator()(T* Object) const`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L28 _function_ `inline bool IsStreamingSupported()` (scope `UE::PixelStreaming2`)
- L39 _function_ `inline bool IsPlatformSupported()` (scope `UE::PixelStreaming2`)
- L48 _function_ `UE_CALL_ONCE([]() { FString ErrorString(TEXT("Failed to initialize Pixel Streaming plugin because minimum requirement is Windows 8")); FText ErrorText = FText::FromString(ErrorString); FText TitleText = FText::FromString(TEXT("Pixel Streaming Plugin")); FMessageDialog::Open(EAppMsgType::Ok, ErrorText, TitleText); });` (scope `UE::PixelStreaming2::IsPlatformSupported`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/UtilsVideo.h` (Internal)


#### struct `UE::PixelStreaming2::FPixelStreaming2SimulcastLayer`  
`struct FPixelStreaming2SimulcastLayer`  
_L21-26_
- desc: A struct representing the simulcast paramaters of a single simulcast layer used by PixelStreaming2. Specifically, each layer has a `Scaling`, `MinBitrate` and `MaxBitrate`.
- L23 _public member_ `float Scaling;`
- L24 _public member_ `int MinBitrate;`
- L25 _public member_ `int MaxBitrate;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L11 _variable_ `const TStaticArray<EVideoCodec, 4> SupportedVideoCodecs = { EVideoCodec::H264, EVideoCodec::AV1, EVideoCodec::VP8, EVideoCodec::VP9 };` (scope `UE::PixelStreaming2`) — List of video codecs supported by PS2
- L13 _variable_ `constexpr uint32_t NumSimulcastLayers = 3;` (scope `UE::PixelStreaming2`)
- L15 _variable_ `constexpr uint32_t ScalingFactor = 2;` (scope `UE::PixelStreaming2`) — Each subsequent layer is 1/ScalingFactor the size of the previous
- L28 _function_ `inline TArray<FPixelStreaming2SimulcastLayer> GetSimulcastParameters()` (scope `UE::PixelStreaming2`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/VideoCapturer.h` (Internal)


#### class `UE::PixelStreaming2::FVideoCapturer`  
`class FVideoCapturer : public IPixelCaptureCapturerSource, public TSharedFromThis<FVideoCapturer>`  
_L17-78_
- inherits: `IPixelCaptureCapturerSource,TSharedFromThis<FVideoCapturer>`
- desc: The start of PixelCapture pipeline. Frames enter the system when `OnFrameCaptured` is called. This class creates the underlying PixelCapture `FPixelCaptureCapturer` that handles frame capture when `RequestFormat` is called.
- L20 _public prototype_ `static TSharedPtr<FVideoCapturer> Create(bool bIsSRGB = false);`
- L21 _public prototype_ `virtual ~FVideoCapturer();`
- L24 _public prototype_ `virtual TSharedPtr<FPixelCaptureCapturer> CreateCapturer(int32 FinalFormat, FIntPoint OutputResolution) override;`
- L27 _public function_ `bool IsReady() const`
- L29 _public prototype_ `void SetVideoProducer(TSharedPtr<IPixelStreaming2VideoProducer> InVideoProducer);`
- L31 _public function_ `TSharedPtr<IPixelStreaming2VideoProducer> GetVideoProducer()`
- L33 _public prototype_ `TSharedPtr<IPixelCaptureOutputFrame> WaitForFormat(int32 Format, TOptional<FIntPoint> Resolution = TOptional<FIntPoint>(), uint32 MaxWaitTime = 5000);`
- L35 _public prototype_ `TSharedPtr<IPixelCaptureOutputFrame> RequestFormat(int32 Format, TOptional<FIntPoint> Resolution = TOptional<FIntPoint>());`
- L37 _public prototype_ `void ResetFrameCapturer();`
- L39 _public prototype_ `void OnFrame(const IPixelCaptureInputFrame& InputFrame);`
- L45 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFrameCaptured);` — This is broadcast each time a frame exits the adapt process. Used to synchronize framerates with input rates. This should be called once per frame taking into consideration all the target formats and layers within the frame.
- L46 _public member_ `FOnFrameCaptured OnFrameCaptured;`
- L52 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFrameCapturerCreated);` — Each time the frame capturer is created. This could be triggered by a multitude of situations such as cvar changes, frame resizes, etc
- L53 _public member_ `FOnFrameCapturerCreated OnFrameCapturerCreated;`
- L56 _protected prototype_ `FVideoCapturer(bool bIsSRGB);`
- L58 _protected member_ `int32 LastFrameWidth = -1;`
- L59 _protected member_ `int32 LastFrameHeight = -1;`
- L60 _protected member_ `int32 LastFrameType = -1;`
- L61 _protected member_ `bool bReady = false;`
- L62 _protected member_ `bool bIsSRGB = false;`
- L64 _protected member_ `TSharedPtr<IPixelStreaming2VideoProducer> VideoProducer;`
- L65 _protected member_ `TSharedPtr<FPixelCaptureCapturerMultiFormat> FrameCapturer;`
- L66 _protected member_ `FDelegateHandle CaptureCompleteHandle;`
- L67 _protected member_ `FDelegateHandle FramePushedHandle;`
- L69 _protected member_ `FDelegateHandle SimulcastEnabledChangedHandle;`
- L70 _protected member_ `FDelegateHandle CaptureUseFenceChangedHandle;`
- L71 _protected member_ `FDelegateHandle UseMediaCaptureChangedHandle;`
- L73 _protected prototype_ `void CreateFrameCapturer();`
- L74 _protected prototype_ `void OnSimulcastEnabledChanged(IConsoleVariable* Var);`
- L75 _protected prototype_ `void OnCaptureUseFenceChanged(IConsoleVariable* Var);`
- L76 _protected prototype_ `void OnUseMediaCaptureChanged(IConsoleVariable* Var);`
- L77 _protected prototype_ `void OnCaptureComplete();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFrameCaptured);` — This is broadcast each time a frame exits the adapt process. Used to synchronize framerates with input rates. This should be called once per frame taking into consideration all the target formats and layers within the frame.
- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFrameCapturerCreated);` — Each time the frame capturer is created. This could be triggered by a multitude of situations such as cvar changes, frame resizes, etc

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/VideoProducer.h` (Internal)


#### class `UE::PixelStreaming2::FVideoProducerUserData`  
`class FVideoProducerUserData : public FMediaCaptureUserData, public FPixelCaptureUserData`  
_L21-29_
- inherits: `FMediaCaptureUserData,FPixelCaptureUserData`
- L24 _public prototype_ `FVideoProducerUserData() = default;`
- L26 _public member_ `uint64 ProductionBeginCycles = 0;`
- L27 _public member_ `uint64 ProductionEndCycles = 0;`
- L28 _public member_ `FString ProducerName = TEXT("");`

#### class `UE::PixelStreaming2::FVideoProducerBase`  
`class FVideoProducerBase : public IPixelStreaming2VideoProducer`  
_L34-48_
- inherits: `IPixelStreaming2VideoProducer`
- desc: The base video producer implementation used by all other PS2 video producers as well as in tests.
- L37 _public prototype_ `static TSharedPtr<FVideoProducerBase> Create();`
- L38 _public prototype_ `virtual ~FVideoProducerBase() = default;`
- L40 _public prototype_ `virtual FString ToString() override;`
- L42 _public function_ `virtual EVideoProducerCapabilities GetCapabilities()`
- L45 _protected prototype_ `FVideoProducerBase() = default;`
- L47 _protected prototype_ `virtual ETextureCreateFlags GetTexCreateFlags();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L12 _namespace_ `namespace VideoProducerIdentifiers` (scope `UE::PixelStreaming2`)
- L14 _externvar_ `extern const FString FVideoProducerBase;` (scope `UE::PixelStreaming2::VideoProducerIdentifiers`)
- L15 _externvar_ `extern const FString FVideoProducerBackBuffer;` (scope `UE::PixelStreaming2::VideoProducerIdentifiers`)
- L16 _externvar_ `extern const FString FVideoProducerMediaCapture;` (scope `UE::PixelStreaming2::VideoProducerIdentifiers`)
- L17 _externvar_ `extern const FString FVideoProducerPIEViewport;` (scope `UE::PixelStreaming2::VideoProducerIdentifiers`)
- L18 _externvar_ `extern const FString FVideoProducerRenderTarget;` (scope `UE::PixelStreaming2::VideoProducerIdentifiers`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/VideoProducerBackBuffer.h` (Internal)


#### class `UE::PixelStreaming2::FVideoProducerBackBuffer`  
`class FVideoProducerBackBuffer : public FVideoProducerBase`  
_L16-30_
- inherits: `FVideoProducerBase`
- desc: Use this if you want to send the contents of the UE backbuffer.
- L19 _public prototype_ `static TSharedPtr<FVideoProducerBackBuffer> Create();`
- L20 _public prototype_ `virtual ~FVideoProducerBackBuffer();`
- L22 _public prototype_ `virtual FString ToString() override;`
- L25 _private prototype_ `FVideoProducerBackBuffer() = default;`
- L27 _private prototype_ `void OnBackBufferReady(SWindow& SlateWindow, ISlateViewportProvider& ViewportProvider);`
- L29 _private member_ `FDelegateHandle DelegateHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/VideoProducerMediaCapture.h` (Internal)


#### class `UPixelStreaming2MediaIOOutput`  
`class UPixelStreaming2MediaIOOutput : public UMediaOutput`  
_L14-26_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaOutput`
- L19 _public function_ `virtual FIntPoint GetRequestedSize() const override`
- L20 _public function_ `virtual EPixelFormat GetRequestedPixelFormat() const override`
- L21 _public function_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override`
- L25 _private member_ `TObjectPtr<UPixelStreaming2MediaIOCapture> MediaCapture = nullptr;` — `UPROPERTY(Transient)`

#### class `UE::PixelStreaming2::FVideoProducerMediaCapture`  
`class FVideoProducerMediaCapture : public FVideoProducerBase, public TSharedFromThis<FVideoProducerMediaCapture>`  
_L34-72_
- inherits: `FVideoProducerBase,TSharedFromThis<FVideoProducerMediaCapture>`
- desc: Use this if you want to send media capture frames as video input.
- L41 _public prototype_ `static TSharedPtr<FVideoProducerMediaCapture> CreateActiveViewportCapture();` — @brief Creates a MediaIO capture of the active viewport and starts capturing as soon as possible. @return A video input backed by the created MediaIO capture that sends frames from the active viewport.
- L50 _public prototype_ `static TSharedPtr<FVideoProducerMediaCapture> Create(TObjectPtr<UPixelStreaming2MediaIOCapture> MediaCapture);` — @brief Creates a video input where the user can specify their own MediaIO output and capture. This method does not does not configure or start capturing, this is left to the user. Use this constructor if you know how to configure the MediaIOCapture yourself or don't want to capture the active viewport. @param MediaCapture The custom MediaIOCapture that will pass its captured frames as video input. @return A video input backed by the passed in MediaIO capture.
- L52 _public prototype_ `virtual ~FVideoProducerMediaCapture();`
- L54 _public prototype_ `virtual FString ToString() override;`
- L56 _public function_ `virtual EVideoProducerCapabilities GetCapabilities()`
- L59 _protected prototype_ `void StartActiveViewportCapture();`
- L60 _protected prototype_ `void LateStartActiveViewportCapture();`
- L63 _private prototype_ `FVideoProducerMediaCapture() = default;`
- L64 _private prototype_ `FVideoProducerMediaCapture(TObjectPtr<UPixelStreaming2MediaIOCapture> MediaCapture);`
- L66 _private prototype_ `void OnCaptureActiveViewportStateChanged();`
- L69 _private member_ `TObjectPtr<UPixelStreaming2MediaIOCapture> MediaCapture = nullptr;`
- L71 _private member_ `TOptional<FDelegateHandle> OnFrameEndDelegateHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/VideoProducerPIEViewport.h` (Internal)


#### class `UE::PixelStreaming2::FVideoProducerPIEViewport`  
`class FVideoProducerPIEViewport : public FVideoProducerViewportBase`  
_L15-30_
- inherits: `FVideoProducerViewportBase`
- desc: An extension of the back buffer input that can handle PIE sessions. Primarily to be used in blueprints
- L18 _public prototype_ `static TSharedPtr<FVideoProducerPIEViewport> Create();`
- L19 _public prototype_ `virtual ~FVideoProducerPIEViewport() = default;`
- L21 _public prototype_ `virtual FString ToString() override;`
- L24 _protected prototype_ `virtual bool ShouldCaptureViewport() override;`
- L27 _private prototype_ `FVideoProducerPIEViewport() = default;`
- L29 _private prototype_ `void OnPreTick(float DeltaTime);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/VideoProducerRenderTarget.h` (Internal)


#### class `UE::PixelStreaming2::FVideoProducerRenderTarget`  
`class FVideoProducerRenderTarget : public FVideoProducerBase`  
_L16-30_
- inherits: `FVideoProducerBase`
- desc: Use this if you want to send the contents of a render target.
- L19 _public prototype_ `static TSharedPtr<FVideoProducerRenderTarget> Create(UTextureRenderTarget2D* Target);`
- L20 _public prototype_ `virtual ~FVideoProducerRenderTarget();`
- L22 _public prototype_ `virtual FString ToString() override;`
- L25 _private prototype_ `FVideoProducerRenderTarget(UTextureRenderTarget2D* InTarget);`
- L26 _private prototype_ `void OnEndFrameRenderThread();`
- L28 _private member_ `UTextureRenderTarget2D* Target = nullptr;`
- L29 _private member_ `FDelegateHandle DelegateHandle;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/VideoProducerViewportBase.h` (Internal)


#### class `UE::PixelStreaming2::FVideoProducerViewportBase`  
`class FVideoProducerViewportBase : public FVideoProducerBase`  
_L22-43_
- inherits: `FVideoProducerBase`
- desc: A base video producer for streaming a target viewport by way of cropping the entire backbuffer to the size of the viewport widget. Implementations MUST set the TargetViewport and TargetWidget and then call CalculateCaptureRegion at least once to configure the captured region. Additionally, implementations MUST override ShouldCaptureViewport with an optional check to prevent OnBackBufferReadyToPresent from sending frames.
- L25 _public prototype_ `virtual ~FVideoProducerViewportBase() = default;`
- L27 _public prototype_ `virtual EVideoProducerCapabilities GetCapabilities() override;`
- L30 _protected prototype_ `FVideoProducerViewportBase() = default;`
- L33 _protected prototype_ `virtual bool ShouldCaptureViewport();` — Viewport specific implementations should override this method with their own check
- L35 _protected prototype_ `void CalculateCaptureRegion(TSharedRef<SViewport> Viewport, TSharedRef<SWindow> Window);`
- L36 _protected prototype_ `void OnBackBufferReadyToPresent(SWindow& Window, ISlateViewportProvider& ViewportProvider);`
- L38 _protected member_ `FIntRect CaptureRect;`
- L39 _protected member_ `FCriticalSection CaptureRectCS;`
- L41 _protected member_ `TWeakPtr<SViewport> TargetViewport;`
- L42 _protected member_ `TWeakPtr<SWindow> TargetWindow;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/VideoSink.h` (Internal)


#### class `UE::PixelStreaming2::FVideoSink`  
`class FVideoSink : public IPixelStreaming2VideoSink`  
_L15-34_
- inherits: `IPixelStreaming2VideoSink`
- L18 _public prototype_ `virtual ~FVideoSink();`
- L20 _public prototype_ `virtual void AddVideoConsumer(const TWeakPtrVariant<IPixelStreaming2VideoConsumer>& VideoConsumer) override;`
- L21 _public prototype_ `virtual void RemoveVideoConsumer(const TWeakPtrVariant<IPixelStreaming2VideoConsumer>& VideoConsumer) override;`
- L23 _public prototype_ `bool HasVideoConsumers();`
- L25 _public prototype_ `void SetMuted(bool bIsMuted);`
- L27 _public prototype_ `void OnVideoData(FTextureRHIRef Frame);`
- L30 _protected member_ `FCriticalSection VideoConsumersCS;`
- L31 _protected member_ `TArray<TWeakPtrVariant<IPixelStreaming2VideoConsumer>> VideoConsumers;`
- L33 _protected member_ `bool bIsMuted = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/VideoSource.h` (Internal)


#### class `UE::PixelStreaming2::FVideoSource`  
`class FVideoSource`  
_L12-23_
- L15 _public prototype_ `virtual ~FVideoSource() = default;`
- L17 _public prototype_ `virtual void PushFrame();`
- L18 _public prototype_ `virtual void ForceKeyFrame();`
- L19 _public prototype_ `virtual void SetMuted(bool bIsMuted);`
- L22 _protected member_ `bool bIsMuted = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Internal/VideoSourceGroup.h` (Internal)


#### class `UE::PixelStreaming2::FVideoSourceGroup`  
`class FVideoSourceGroup : public TSharedFromThis<FVideoSourceGroup>`  
_L14-64_
- inherits: `TSharedFromThis<FVideoSourceGroup>`
- L17 _public prototype_ `static TSharedPtr<FVideoSourceGroup> Create(TSharedPtr<FVideoCapturer> InVideoCapturer);`
- L18 _public prototype_ `~FVideoSourceGroup();`
- L20 _public prototype_ `void SetFPS(int32 InFramesPerSecond);`
- L21 _public prototype_ `int32 GetFPS();`
- L23 _public prototype_ `void SetDecoupleFramerate(bool bDecouple);`
- L25 _public prototype_ `void AddVideoSource(TSharedPtr<FVideoSource> VideoSource);`
- L26 _public prototype_ `void RemoveVideoSource(const FVideoSource* ToRemove);`
- L27 _public prototype_ `void RemoveAllVideoSources();`
- L29 _public prototype_ `void Start();`
- L30 _public prototype_ `void Stop();`
- L31 _public prototype_ `void PushFrame();`
- L33 _public prototype_ `void ForceKeyFrame();`
- L36 _private prototype_ `FVideoSourceGroup();`
- L38 _private prototype_ `void StartThread();`
- L39 _private prototype_ `void StopThread();`
- L41 _private prototype_ `void OnFrameCaptured();`
- L43 _private prototype_ `void OnWebRtcFpsChanged(IConsoleVariable* Var);`
- L44 _private prototype_ `void OnDecoupleFramerateChanged(IConsoleVariable* Var);`
- L46 _private member_ `bool bFPSOverride = false;`
- L47 _private member_ `bool bDecoupleOverride = false;`
- L49 _private member_ `bool bRunning = false;`
- L50 _private member_ `bool bDecoupleFramerate = false;`
- L51 _private member_ `int32 FramesPerSecond = 30;`
- L53 _private member_ `TArray<TSharedPtr<FVideoSource>> VideoSources;`
- L55 _private member_ `FDelegateHandle FrameDelegateHandle;`
- L56 _private member_ `FDelegateHandle FpsDelegateHandle;`
- L57 _private member_ `FDelegateHandle DecoupleDelegateHandle;`
- L59 _private member_ `TSharedPtr<FRunnableThread> FrameThread = nullptr;` — constant FPS tick thread
- L60 _private member_ `TSharedPtr<FFrameRunnable> FrameRunnable = nullptr;` — constant fps runnable
- L62 _private member_ `mutable FCriticalSection CriticalSection;`
- L63 _private member_ `mutable FCriticalSection RunnableCriticalSection;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Private/Blueprints/PixelStreaming2AudioComponent.h` (Private)


#### class `UPixelStreaming2AudioComponent`  
`class UPixelStreaming2AudioComponent : public USynthComponent, public IPixelStreaming2AudioConsumer`  
_L21-92_
- reflection: `UCLASS(Blueprintable, ClassGroup = (PixelStreaming2), meta = (BlueprintSpawnableComponent))`
- inherits: `USynthComponent,IPixelStreaming2AudioConsumer`
- desc: Allows in-engine playback of incoming WebRTC audio from a particular Pixel Streaming player/peer using their mic in the browser. Note: Each audio component associates itself with a particular Pixel Streaming player/peer (using the the Pixel Streaming player id).
- L26 _protected prototype_ `UPixelStreaming2AudioComponent(const FObjectInitializer& ObjectInitializer);`
- L29 _protected prototype_ `virtual void OnBeginGenerate() override;`
- L30 _protected prototype_ `virtual void OnEndGenerate() override;`
- L31 _protected prototype_ `virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) override;`
- L35 _protected prototype_ `virtual void BeginDestroy() override;`
- L39 _protected prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L48 _public member_ `FString StreamerToHear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pixel Streaming Audio Component")` — The Pixel Streaming streamer of the player that we wish to listen to. If this is left blank this component will use the default Pixel Streaming streamer
- L56 _public member_ `FString PlayerToHear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pixel Streaming Audio Component")` — The Pixel Streaming player/peer whose audio we wish to listen to. If this is left blank this component will listen to the first non-listened to peer that connects after this component is ready. Note: that when the listened to peer disconnects this component is reset to blank and will once again listen to the next non-listened to peer that connects.
- L62 _public member_ `bool bAutoFindPeer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pixel Streaming Audio Component")` — If not already listening to a player/peer will try to attach for listening to the "PlayerToHear" each tick.
- L65 _private member_ `TWeakPtr<IPixelStreaming2AudioSink> AudioSink;`
- L66 _private member_ `TSharedPtr<UE::PixelStreaming2::FSoundGenerator, ESPMode::ThreadSafe> SoundGenerator;`
- L71 _public prototype_ `bool ListenTo(FString PlayerToListenTo);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Audio Component")` — Listen to a specific player on the default streamer. If the player is not found this component will be silent.
- L75 _public prototype_ `bool StreamerListenTo(FString StreamerId, FString PlayerToListenTo);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Audio Component")` — Listen to a specific player. If the player is not found this component will be silent.
- L79 _public prototype_ `bool IsListeningToPlayer();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Audio Component")` — True if listening to a connected WebRTC peer through Pixel Streaming.
- L81 _public prototype_ `bool WillListenToAnyPlayer();`
- L85 _public prototype_ `void Reset();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Audio Component")` — Stops listening to any connected player/peer and resets internal state so component is ready to listen again.
- L88 _public prototype_ `void ConsumeRawPCM(const int16_t* AudioData, int SampleRate, size_t NumChannels, size_t NumFrames);`
- L89 _public prototype_ `void OnAudioConsumerAdded();`
- L90 _public prototype_ `void OnAudioConsumerRemoved();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Private/Blueprints/PixelStreaming2Blueprints.h` (Private)


#### class `UPixelStreaming2Blueprints`  
`class UPixelStreaming2Blueprints : public UBlueprintFunctionLibrary`  
_L14-178_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L19 _public prototype_ `static void SendResponse(FString Descriptor);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")`
- L23 _public prototype_ `static void StreamerSendResponse(FString StreamerId, FString Descriptor);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")`
- L33 _public prototype_ `static void SendFileAsByteArray(TArray<uint8> ByteArray, FString MimeType, FString FileExtension);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Send a specified byte array over the WebRTC peer connection data channel. The extension and mime type are used for file reconstruction on the front end @param   ByteArray       The raw data that will be sent over the data channel @param   MimeType        The mime type of the file. Used for reconstruction on the front end @param   FileExtension   The file extension. Used for file reconstruction on the front end
- L44 _public prototype_ `static void StreamerSendFileAsByteArray(FString StreamerId, TArray<uint8> ByteArray, FString MimeType, FString FileExtension);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Send a specified byte array over the WebRTC peer connection data channel. The extension and mime type are used for file reconstruction on the front end @param	StreamerId		The streamer use when sending the data @param   ByteArray       The raw data that will be sent over the data channel @param   MimeType        The mime type of the file. Used for reconstruction on the front end @param   FileExtension   The file extension. Used for file reconstruction on the front end
- L54 _public prototype_ `static void SendFile(FString Filepath, FString MimeType, FString FileExtension);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Send a specified file over the WebRTC peer connection data channel. The extension and mime type are used for file reconstruction on the front end @param   FilePath        The path to the file that will be sent @param   MimeType        The mime type of the file. Used for file reconstruction on the front end @param   FileExtension   The file extension. Used for file reconstruction on the front end
- L65 _public prototype_ `static void StreamerSendFile(FString StreamerId, FString Filepath, FString MimeType, FString FileExtension);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Send a specified file over the WebRTC peer connection data channel. The extension and mime type are used for file reconstruction on the front end @param	StreamerId		The streamer use when sending the data @param   FilePath        The path to the file that will be sent @param   MimeType        The mime type of the file. Used for file reconstruction on the front end @param   FileExtension   The file extension. Used for file reconstruction on the front end
- L71 _public prototype_ `static void ForceKeyFrame();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Force a key frame to be sent to the default streamer (if there is one).
- L77 _public prototype_ `static void StreamerForceKeyFrame(FString StreamerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Force a key frame to be sent to the specified streamer.
- L84 _public prototype_ `static void FreezeFrame(UTexture2D* Texture);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Freeze the video stream of the default streamer (if there is one). @param   Texture         The freeze frame to display. If null then show the last frame that was streamed.
- L90 _public prototype_ `static void UnfreezeFrame();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Unfreeze the video stream of the default streamer (if there is one).
- L98 _public prototype_ `static void StreamerFreezeStream(FString StreamerId, UTexture2D* Texture);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Freeze the video stream of the specified video stream. @param	StreamerId		The id of the streamer to freeze. @param   Texture         The freeze frame to display. If null then show the last frame that was streamed.
- L105 _public prototype_ `static void StreamerUnfreezeStream(FString StreamerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Unfreeze the video stream of the specified streamer. @param StreamerId		The id of the streamer to unfreeze.
- L112 _public prototype_ `static void KickPlayer(FString PlayerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Kick a player that is connected to the default streamer (if there is a default streamer). @param   PlayerId         The ID of the player to kick.
- L120 _public prototype_ `static void StreamerKickPlayer(FString StreamerId, FString PlayerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Kick a player connected to the specified streamer. @param	StreamerId		The streamer which the player belongs @param   PlayerId        The ID of the player to kick.
- L128 _public prototype_ `static TArray<FString> GetConnectedPlayers();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — @brief Get the connected players @return TArray<FString> The connected players
- L137 _public prototype_ `static TArray<FString> StreamerGetConnectedPlayers(FString StreamerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — @brief Get the connected players @param StreamerId	The streamer whose list of players you wish to get @return TArray<FString> The connected players
- L143 _public prototype_ `static FString GetDefaultStreamerID();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Get the default Streamer ID
- L157 _public prototype_ `static void GetJsonStringValue(FString Descriptor, FString FieldName, FString& StringValue, bool& Success);` — `UFUNCTION(BlueprintPure, Category = "Pixel Streaming 2")` — Helper function to extract a string field from a JSON descriptor of a UI interaction given its field name. The field name may be hierarchical, delimited by a period. For example, to access the Width value of a Resolution command above you should use "Resolution.Width" to get the width value. @param Descriptor - The UI interaction JSON descriptor. @param FieldName - The name of the field to look for in the JSON. @param StringValue - The string value associated with the field name. @param Success - True if the field exists in the JSON data.
- L169 _public prototype_ `static void AddJsonStringValue(const FString& Descriptor, FString FieldName, FString StringValue, FString& NewDescriptor, bool& Success);` — `UFUNCTION(BlueprintPure, Category = "Pixel Streaming 2")` — Helper function to add a string field to a JSON descriptor. This produces a new descriptor which may then be chained to add further string fields. @param Descriptor - The initial JSON descriptor which may be blank initially. @param FieldName - The name of the field to add to the JSON. @param StringValue - The string value associated with the field name. @param NewDescriptor - The JSON descriptor with the string field added. @param Success - True if the string field could be added successfully.
- L177 _public prototype_ `static UPixelStreaming2Delegates* GetDelegates();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming 2")` — Get the singleton. This allows application-specific blueprints to bind to delegates of interest.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Private/Blueprints/PixelStreaming2StreamerComponent.h` (Private)


#### class `UPixelStreaming2StreamerComponent`  
`class UPixelStreaming2StreamerComponent : public UActorComponent`  
_L12-82_
- reflection: `UCLASS(BlueprintType, Blueprintable, Category = "PixelStreaming2", META = (DisplayName = "Streamer Component", BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L17 _public prototype_ `virtual void BeginPlay() override;`
- L18 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L21 _public prototype_ `FString GetId();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")`
- L24 _public prototype_ `void StartStreaming();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")`
- L27 _public prototype_ `void StopStreaming();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")`
- L30 _public prototype_ `bool IsStreaming();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")`
- L32 _public prototype_ `DECLARE_EVENT(UPixelStreaming2StreamerComponent, FStreamingStartedEvent);`
- L33 _public member_ `FStreamingStartedEvent OnStreamingStarted;`
- L35 _public prototype_ `DECLARE_EVENT(UPixelStreaming2StreamerComponent, FStreamingStoppedEvent);`
- L36 _public member_ `FStreamingStoppedEvent OnStreamingStopped;`
- L38 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInputReceived, FString , uint8 , TArray<uint8> );`
- L39 _public member_ `FOnInputReceived OnInputReceived;`
- L42 _public prototype_ `void ForceKeyFrame();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")`
- L45 _public prototype_ `void FreezeStream(UTexture2D* Texture);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")`
- L48 _public prototype_ `void UnfreezeStream();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")`
- L51 _public prototype_ `void SendAllPlayersMessage(FString MessageType, const FString& Descriptor);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")`
- L54 _public prototype_ `void SendPlayerMessage(FString PlayerId, FString MessageType, const FString& Descriptor);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming2")`
- L57 _public member_ `FString StreamerId = "St` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming2")`
- L60 _public member_ `FString SignallingServerURL = "ws` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming2")` — 127.0.0.1:8888";
- L63 _public member_ `bool UsePixelStreamingURL = false;` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming2")`
- L66 _public member_ `int32 StreamFPSOverride = -1;` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming2")`
- L69 _public member_ `bool CoupleFramerate = false;` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming2")`
- L72 _public member_ `TObjectPtr<UPixelStreaming2VideoProducerBase> VideoProducer = nullptr;` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming2")`
- L75 _private member_ `TSharedPtr<IPixelStreaming2Streamer> Streamer;`
- L77 _private prototype_ `void CreateStreamer();`
- L78 _private prototype_ `void SetupStreamerInput();`
- L80 _private prototype_ `void StreamingStarted(IPixelStreaming2Streamer*);`
- L81 _private prototype_ `void StreamingStopped(IPixelStreaming2Streamer*);`

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_EVENT(UPixelStreaming2StreamerComponent, FStreamingStartedEvent);`
- L35 _delegate_ `DECLARE_EVENT(UPixelStreaming2StreamerComponent, FStreamingStoppedEvent);`
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInputReceived, FString , uint8 , TArray<uint8> );`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Private/Blueprints/PixelStreaming2VideoComponent.h` (Private)


#### class `UPixelStreaming2VideoComponent`  
`class UPixelStreaming2VideoComponent : public USceneComponent, public IPixelStreaming2VideoConsumer`  
_L19-91_
- reflection: `UCLASS(Blueprintable, ClassGroup = (PixelStreaming2), meta = (BlueprintSpawnableComponent))`
- inherits: `USceneComponent,IPixelStreaming2VideoConsumer`
- desc: Allows in-engine playback of incoming WebRTC video from a particular Pixel Streaming player/peer using their camera in the browser. Note: Each video component associates itself with a particular Pixel Streaming player/peer (using the the Pixel Streaming player id).
- L24 _protected prototype_ `UPixelStreaming2VideoComponent(const FObjectInitializer& ObjectInitializer);`
- L27 _protected prototype_ `virtual void BeginDestroy() override;`
- L31 _protected prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L35 _protected prototype_ `virtual void ConsumeFrame(FTextureRHIRef Frame) override;`
- L36 _protected prototype_ `virtual void OnVideoConsumerAdded() override;`
- L37 _protected prototype_ `virtual void OnVideoConsumerRemoved() override;`
- L46 _public member_ `FString StreamerToWatch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pixel Streaming Video Component")` — The Pixel Streaming streamer of the player that we wish to watch. If this is left blank this component will use the default Pixel Streaming streamer
- L54 _public member_ `FString PlayerToWatch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pixel Streaming Video Component")` — The Pixel Streaming player/peer whose video we wish to watch. If this is left blank this component will watch the first non-watched to peer that connects after this component is ready. Note: that when the watched peer disconnects this component is reset to blank and will once again watch the next non-watched to peer that connects.
- L60 _public member_ `bool bAutoFindPeer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pixel Streaming Video Component")` — If not already watching a player/peer will try to attach for watching the "PlayerToWatch" each tick.
- L66 _public member_ `TObjectPtr<UPixelStreaming2MediaTexture> VideoConsumer = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Pixel Streaming Video Component", META = (DisplayName = "Pixel Streaming Video Consumer", AllowPrivateAccess = true))` — A sink for the video data received once this connection has finished negotiating.
- L69 _private member_ `TWeakPtr<IPixelStreaming2VideoSink> VideoSink;`
- L71 _private member_ `bool bIsWatchingPlayer;`
- L76 _public prototype_ `bool Watch(FString PlayerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Video Component")` — Watch a specific player on the default streamer. If the player is not found this component won't produce video.
- L80 _public prototype_ `bool StreamerWatch(FString StreamerId, FString PlayerId);` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Video Component")` — Watch a specific player. If the player is not found this component won't produce video.
- L84 _public prototype_ `bool IsWatchingPlayer();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Video Component")` — True if watching a connected WebRTC peer through Pixel Streaming.
- L86 _public prototype_ `bool WillWatchAnyPlayer();`
- L90 _public prototype_ `void Reset();` — `UFUNCTION(BlueprintCallable, Category = "Pixel Streaming Video Component")` — Stops watching any connected player/peer and resets internal state so component is ready to watch again.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Private/Logging.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2, Log, All);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Private/PixelStreaming2Module.h` (Private)


#### class `UE::PixelStreaming2::FPixelStreaming2Module`  
`class FPixelStreaming2Module : public IPixelStreaming2Module`  
_L15-60_
- inherits: `IPixelStreaming2Module`
- desc: This plugin allows the back buffer to be sent as a compressed video across a network.
- L18 _public prototype_ `static FPixelStreaming2Module* GetModule();`
- L20 _public prototype_ `virtual ~FPixelStreaming2Module() = default;`
- L22 _public prototype_ `virtual FReadyEvent& OnReady() override;`
- L23 _public prototype_ `virtual bool IsReady() override;`
- L24 _public prototype_ `virtual bool StartStreaming() override;`
- L25 _public prototype_ `virtual void StopStreaming() override;`
- L26 _public prototype_ `virtual TSharedPtr<IPixelStreaming2Streamer> CreateStreamer(const FString& StreamerId, TOptional<FString> Type = TOptional<FString>()) override;`
- L27 _public prototype_ `virtual TSharedPtr<IPixelStreaming2VideoProducer> CreateVideoProducer() override;`
- L28 _public prototype_ `virtual TSharedPtr<IPixelStreaming2AudioProducer> CreateAudioProducer() override;`
- L29 _public prototype_ `virtual TArray<FString> GetStreamerIds() override;`
- L30 _public prototype_ `virtual TSharedPtr<IPixelStreaming2Streamer> FindStreamer(const FString& StreamerId) override;`
- L31 _public prototype_ `virtual TSharedPtr<IPixelStreaming2Streamer> DeleteStreamer(const FString& StreamerId) override;`
- L32 _public prototype_ `virtual void DeleteStreamer(TSharedPtr<IPixelStreaming2Streamer> ToBeDeleted) override;`
- L33 _public prototype_ `virtual FString GetDefaultStreamerID() override;`
- L34 _public prototype_ `virtual FString GetDefaultConnectionURL() override;`
- L35 _public prototype_ `virtual void ForEachStreamer(const TFunction<void(TSharedPtr<IPixelStreaming2Streamer>)>& Func) override;`
- L37 _public prototype_ `TSharedPtr<class FPixelStreamingThread> GetOrCreatePixelStreamingThread();`
- L41 _private prototype_ `void StartupModule() override;`
- L42 _private prototype_ `void ShutdownModule() override;`
- L46 _private prototype_ `void InitDefaultStreamer();`
- L49 _private member_ `bool bModuleReady = false;`
- L50 _private member_ `FReadyEvent ReadyEvent;`
- L53 _private member_ `TSharedPtr<class FPixelStreamingThread> PixelStreamingThread;` — FPixelStreamingThread must exist before any AudioTask and AudioMixingCapturer(Which contains a audio task) to ensure it is destroyed last
- L55 _private member_ `TSharedPtr<IPixelStreaming2Streamer> DefaultStreamer;`
- L57 _private member_ `TThreadSafeMap<FString, TWeakPtr<IPixelStreaming2Streamer>> Streamers;`
- L59 _private member_ `static FPixelStreaming2Module* PixelStreaming2Module;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Private/PixelStreamingThread.h` (Private)


#### class `UE::PixelStreaming2::FPixelStreamingThread`  
`class FPixelStreamingThread`  
_L12-23_
- desc: The thread. Wraps both the RunnableThread and Runnable into a single point
- L15 _public prototype_ `FPixelStreamingThread();`
- L16 _public prototype_ `~FPixelStreamingThread();`
- L18 _public prototype_ `bool IsSleeping();`
- L21 _private member_ `TSharedPtr<class FRunnableThread> Thread;`
- L22 _private member_ `TSharedPtr<class FPixelStreamingRunnable> Runnable;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Public/IPixelStreaming2Module.h` (Public)


#### class `IPixelStreaming2Module`  
`class IPixelStreaming2Module : public IModuleInterface`  
_L19-144_
- inherits: `IModuleInterface`
- desc: The IPixelStreaming2Module interface manages the core functionality of the Pixel Streaming system. This class provides access to streamers, video and audio producers, and handles starting and stopping the streaming process. It also allows interaction with the signalling server and manages the lifecycle of streamers within the Pixel Streaming system.
- L28 _public function_ `static inline IPixelStreaming2Module& Get()` — Singleton-like access to this module's interface. Beware calling this during the shutdown phase, though. Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L38 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded. @return True if the module is loaded.
- L46 _public prototype_ `DECLARE_EVENT_OneParam(IPixelStreaming2Module, FReadyEvent, IPixelStreaming2Module&);` — Event fired when internal streamer is initialized and the methods on this module are ready for use.
- L52 _public prototype_ `virtual FReadyEvent& OnReady() = 0;` — A getter for the OnReady event. Intent is for users to call IPixelStreaming2Module::Get().OnReady().AddXXX. @return The bindable OnReady event.
- L58 _public prototype_ `virtual bool IsReady() = 0;` — Is the PixelStreaming2 module actually ready to use? Is the streamer created. @return True if Pixel Streaming module methods are ready for use.
- L64 _public prototype_ `virtual bool StartStreaming() = 0;` — Starts streaming on all streamers. @return False if the module was not able to start streaming.
- L69 _public prototype_ `virtual void StopStreaming() = 0;` — Stops all streamers from streaming.
- L76 _public prototype_ `virtual TSharedPtr<IPixelStreaming2Streamer> CreateStreamer(const FString& StreamerId, TOptional<FString> Type = TOptional<FString>()) = 0;` — Creates a new streamer. @param StreamerId - The ID of the Streamer to be created. @return SharedPtr to the streamer.
- L83 _public prototype_ `virtual TSharedPtr<IPixelStreaming2VideoProducer> CreateVideoProducer() = 0;` — `UE_DEPRECATED(5.7, "CreateVideoProducer has been deprecated. You can create a class that inherits from IPixelStreaming2VideoProducer and call PushFrame.")` — @brief Creates a new video producer. @return An video producer interface for you to push video frames in to.
- L91 _public prototype_ `virtual TSharedPtr<IPixelStreaming2AudioProducer> CreateAudioProducer() = 0;` — `UE_DEPRECATED(5.7, "CreateAudioProducer has been deprecated. You can create a class that inherits from IPixelStreaming2AudioProducer and call PushAudio.")` — @brief Creates a new audio producer. Any audio you push in with `PushAudio` will be mixed with other audio sources before being streamed. @note Users are responsible for the lifetime of this object. @return An audio producer interface for you to push audio in to.
- L97 _public prototype_ `virtual TArray<FString> GetStreamerIds() = 0;` — Returns a TArray containing the keys to the currently held streamers. @return TArray containing the keys to the currently held streamers.
- L104 _public prototype_ `virtual TSharedPtr<IPixelStreaming2Streamer> FindStreamer(const FString& StreamerId) = 0;` — Find a streamer by an ID. @param StreamerId	-	The ID of the streamer to be found. @return A pointer to the interface for a streamer. nullptr if the streamer isn't found.
- L111 _public prototype_ `virtual TSharedPtr<IPixelStreaming2Streamer> DeleteStreamer(const FString& StreamerId) = 0;` — Remove a streamer by an ID @param StreamerId	-	The ID of the streamer to be removed. @return The removed streamer. nullptr if the streamer wasn't found.
- L117 _public prototype_ `virtual void DeleteStreamer(TSharedPtr<IPixelStreaming2Streamer> ToBeDeleted) = 0;` — Remove a streamer by its pointer @param ToBeDeleted The streamer to remove from the internal management.
- L123 _public prototype_ `virtual FString GetDefaultStreamerID() = 0;` — Get the Default Streamer ID. @return FString The default streamer ID.
- L129 _public prototype_ `virtual FString GetDefaultConnectionURL() = 0;` — Get the Default Connection URL ("ws://127.0.0.1:8888"). @return FString The default connection url ("ws://127.0.0.1:8888").
- L136 _public function_ `virtual FString GetDefaultSignallingURL()` — `UE_DEPRECATED(5.6, "GetDefaultSignallingURL has been deprecated. Please use GetDefaultConnectionURL instead.")` — Get the Default Signaling URL ("ws://127.0.0.1:8888"). @return FString The default signaling url ("ws://127.0.0.1:8888").
- L143 _public prototype_ `virtual void ForEachStreamer(const TFunction<void(TSharedPtr<IPixelStreaming2Streamer>)>& Func) = 0;` — @brief A method for iterating through all of the streamers on the module. @param Func The lambda to execute with each streamer.

#### Free symbols / members of external scopes

- L46 _delegate_ `DECLARE_EVENT_OneParam(IPixelStreaming2Module, FReadyEvent, IPixelStreaming2Module&);` — Event fired when internal streamer is initialized and the methods on this module are ready for use.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Public/PixelStreaming2Delegates.h` (Public)


#### class `UPixelStreaming2Delegates`  
`class UPixelStreaming2Delegates : public UObject`  
_L18-175_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Pixel Streaming Delegates that can be invoked when pixel streaming events take place. Includes blueprint and native c++ delegates.
- L24 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConnectedToSignallingServer, FString, StreamerId);` — Blueprint delegate type for when a connection to the signalling server was made.
- L28 _public member_ `FConnectedToSignallingServer OnConnectedToSignallingServer;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")` — Invoked when a connection to the signalling server was made.
- L31 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FConnectedToSignallingServerNative, FString );` — Delegate type for when a connection to the signalling server was made.
- L34 _public member_ `FConnectedToSignallingServerNative OnConnectedToSignallingServerNative;` — Invoked when a connection to the signalling server was made.
- L37 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDisconnectedFromSignallingServer, FString, StreamerId);` — Blueprint delegate type for when a connection to the signalling server was lost.
- L41 _public member_ `FDisconnectedFromSignallingServer OnDisconnectedFromSignallingServer;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")` — Invoked when a connection to the signalling server was lost.
- L44 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FDisconnectedFromSignallingServerNative, FString );` — Delegate type for when a connection to the signalling server was lost.
- L47 _public member_ `FDisconnectedFromSignallingServerNative OnDisconnectedFromSignallingServerNative;` — Invoked when a connection to the signalling server was lost.
- L50 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNewConnection, FString, StreamerId, FString, PlayerId);` — Blueprint delegate type for when a new connection has been made to the session.
- L54 _public member_ `FNewConnection OnNewConnection;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")` — Invoked when a new connection has been made to the session.
- L57 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FNewConnectionNative, FString , FString );` — Delegate type for when a new connection has been made to the session.
- L60 _public member_ `FNewConnectionNative OnNewConnectionNative;` — Invoked when a new connection has been made to the session.
- L63 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FClosedConnection, FString, StreamerId, FString, PlayerId);` — Blueprint delegate type for when a connection to a player was lost.
- L67 _public member_ `FClosedConnection OnClosedConnection;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")` — Invoked when a connection to a player was lost.
- L70 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FClosedConnectionNative, FString , FString );` — Delegate type for when a connection to a player was lost.
- L73 _public member_ `FClosedConnectionNative OnClosedConnectionNative;` — Invoked when a connection to a player was lost.
- L76 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAllConnectionsClosed, FString, StreamerId);` — Blueprint delegate type for when all connections have closed and nobody is viewing or interacting with the app. This is an opportunity to reset the app.
- L80 _public member_ `FAllConnectionsClosed OnAllConnectionsClosed;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")` — Invoked when all connections have closed and nobody is viewing or interacting with the app. This is an opportunity to reset the app.
- L83 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FAllConnectionsClosedNative, FString);` — Delegate type for when all connections have closed and nobody is viewing or interacting with the app. This is an opportunity to reset the app.
- L86 _public member_ `FAllConnectionsClosedNative OnAllConnectionsClosedNative;` — Invoked when all connections have closed and nobody is viewing or interacting with the app. This is an opportunity to reset the app.
- L89 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDataTrackOpen, FString, StreamerId, FString, PlayerId);` — Blueprint delegate type for when a new data track has been opened.
- L93 _public member_ `FDataTrackOpen OnDataTrackOpen;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")` — Invoked when a new data track has been opened.
- L96 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FDataTrackOpenNative, FString , FString );` — Delegate type for when a new data track has been opened.
- L99 _public member_ `FDataTrackOpenNative OnDataTrackOpenNative;` — Invoked when a new data track has been opened.
- L102 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDataTrackClosed, FString, StreamerId, FString, PlayerId);` — Blueprint delegate type for when an existing data track has been closed.
- L106 _public member_ `FDataTrackClosed OnDataTrackClosed;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")` — Invoked when an existing data track has been closed.
- L109 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FDataTrackClosedNative, FString , FString );` — Delegate type for when an existing data track has been closed.
- L112 _public member_ `FDataTrackClosedNative OnDataTrackClosedNative;` — Invoked when an existing data track has been closed.
- L115 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FVideoTrackOpenNative, FString , FString , bool );` — Delegate type for when a new video track has been opened.
- L118 _public member_ `FVideoTrackOpenNative OnVideoTrackOpenNative;` — Invoked when a new video track has been opened.
- L121 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FVideoTrackClosedNative, FString , FString , bool );` — Delegate type for when an existing video track has been closed.
- L124 _public member_ `FVideoTrackClosedNative OnVideoTrackClosedNative;` — Invoked when an existing video track has been closed.
- L127 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FAudioTrackOpenNative, FString , FString , bool );` — Delegate type for when a new audio track has been opened.
- L130 _public member_ `FAudioTrackOpenNative OnAudioTrackOpenNative;` — Invoked when a new audio track has been opened.
- L133 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FAudioTrackClosedNative, FString , FString , bool );` — Delegate type for when an existing audio track has been closed.
- L136 _public member_ `FAudioTrackClosedNative OnAudioTrackClosedNative;` — Invoked when an existing audio track has been closed.
- L139 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FStatsChanged, FString, PlayerId, FName, StatName, float, StatValue);` — Blueprint delegate type for when a pixel streaming stat has changed.
- L143 _public member_ `FStatsChanged OnStatChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")` — Invoked when a pixel streaming stat has changed.
- L146 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FStatChangedNative, FString , FName , float);` — Delegate type for when a pixel streaming stat has changed.
- L149 _public member_ `FStatChangedNative OnStatChangedNative;` — Invoked when a pixel streaming stat has changed.
- L152 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFallbackToSoftwareEncoding);` — Blueprint delegate type for when the GPU ran out of available hardware encoders and fell back to software encoders.
- L156 _public member_ `FFallbackToSoftwareEncoding OnFallbackToSoftwareEncoding;` — `UPROPERTY(BlueprintAssignable, Category = "Pixel Streaming Delegates")` — Invoked when the GPU ran out of available hardware encoders and fell back to software encoders.
- L159 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FFallbackToSoftwareEncodingNative);` — Delegate type for when the GPU ran out of available hardware encoders and fell back to software encoders.
- L162 _public member_ `FFallbackToSoftwareEncodingNative OnFallbackToSoftwareEncodingNative;` — Invoked when the GPU ran out of available hardware encoders and fell back to software encoders.
- L168 _public prototype_ `static UPixelStreaming2Delegates* Get();` — @param Get the UPixelStreaming2Delegates singleton. @return UPixelStreaming2Delegates pointer.
- L170 _public prototype_ `virtual ~UPixelStreaming2Delegates();`
- L174 _private member_ `static UPixelStreaming2Delegates* Singleton;` — The singleton object.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L24 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConnectedToSignallingServer, FString, StreamerId);` — Blueprint delegate type for when a connection to the signalling server was made.
- L31 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FConnectedToSignallingServerNative, FString );` — Delegate type for when a connection to the signalling server was made.
- L37 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDisconnectedFromSignallingServer, FString, StreamerId);` — Blueprint delegate type for when a connection to the signalling server was lost.
- L44 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FDisconnectedFromSignallingServerNative, FString );` — Delegate type for when a connection to the signalling server was lost.
- L50 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNewConnection, FString, StreamerId, FString, PlayerId);` — Blueprint delegate type for when a new connection has been made to the session.
- L57 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FNewConnectionNative, FString , FString );` — Delegate type for when a new connection has been made to the session.
- L63 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FClosedConnection, FString, StreamerId, FString, PlayerId);` — Blueprint delegate type for when a connection to a player was lost.
- L70 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FClosedConnectionNative, FString , FString );` — Delegate type for when a connection to a player was lost.
- L76 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAllConnectionsClosed, FString, StreamerId);` — Blueprint delegate type for when all connections have closed and nobody is viewing or interacting with the app. This is an opportunity to reset the app.
- L83 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FAllConnectionsClosedNative, FString);` — Delegate type for when all connections have closed and nobody is viewing or interacting with the app. This is an opportunity to reset the app.
- L89 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDataTrackOpen, FString, StreamerId, FString, PlayerId);` — Blueprint delegate type for when a new data track has been opened.
- L96 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FDataTrackOpenNative, FString , FString );` — Delegate type for when a new data track has been opened.
- L102 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDataTrackClosed, FString, StreamerId, FString, PlayerId);` — Blueprint delegate type for when an existing data track has been closed.
- L109 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FDataTrackClosedNative, FString , FString );` — Delegate type for when an existing data track has been closed.
- L115 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FVideoTrackOpenNative, FString , FString , bool );` — Delegate type for when a new video track has been opened.
- L121 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FVideoTrackClosedNative, FString , FString , bool );` — Delegate type for when an existing video track has been closed.
- L127 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FAudioTrackOpenNative, FString , FString , bool );` — Delegate type for when a new audio track has been opened.
- L133 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FAudioTrackClosedNative, FString , FString , bool );` — Delegate type for when an existing audio track has been closed.
- L139 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FStatsChanged, FString, PlayerId, FName, StatName, float, StatValue);` — Blueprint delegate type for when a pixel streaming stat has changed.
- L146 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FStatChangedNative, FString , FName , float);` — Delegate type for when a pixel streaming stat has changed.
- L152 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFallbackToSoftwareEncoding);` — Blueprint delegate type for when the GPU ran out of available hardware encoders and fell back to software encoders.
- L159 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FFallbackToSoftwareEncodingNative);` — Delegate type for when the GPU ran out of available hardware encoders and fell back to software encoders.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Public/PixelStreaming2Utils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L17 _prototype_ `void ExtendJsonWithField(const FString& Descriptor, FString FieldName, FString StringValue, FString& OutNewDescriptor, bool& OutSuccess);` (scope `UE::PixelStreaming2`) — Extends an existing JSON string with a new name: value property. @param Descriptor The JSON string. @param FieldName The field name to add the json string. @param StringValue The value to set in the new field. @param OutNewDescriptor The new JSON string. @param OutSuccess True if we were able to extend the JSON string.
- L26 _prototype_ `void ExtractJsonFromDescriptor(FString Descriptor, FString FieldName, FString& OutStringValue, bool& OutSuccess);` (scope `UE::PixelStreaming2`) — Extract a field's value from a JSON string. @param Descriptor The JSON string. @param FieldName The field name to extract a value from. @param OutStringValue The value from the extracted field. @param OutSuccess True if we were able to extract the value.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2/Public/PixelStreaming2VideoProducers.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELSTREAMING2_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L13 _prototype_ `TSharedPtr<IPixelStreaming2VideoProducer> CreateVideoProducerBackBuffer();` (scope `UE::PixelStreaming2`)
- L14 _prototype_ `TSharedPtr<IPixelStreaming2VideoProducer> CreateVideoProducerRenderTarget(UTextureRenderTarget2D* Target);` (scope `UE::PixelStreaming2`)
- L15 _prototype_ `TSharedPtr<IPixelStreaming2VideoProducer> CreateVideoProducerPIEViewport();` (scope `UE::PixelStreaming2`)
