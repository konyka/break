# Plugins / AjaMedia

- module root: `Plugins/Media/AjaMedia/Source/AjaMedia`
- headers: 15; symbols: 298
- symbol kinds: class=13, delegate=2, enum=4, enumerator=9, function=17, macro=5, member=96, namespace=7, prototype=118, struct=4, typedef=3, variable=20
- DynamicallyLoadedModuleNames: Media
- PrivateDependencyModuleNames: AjaCore, Core, CoreUObject, Engine, MediaIOCore, MediaUtils, OpenColorIO, Projects, RHI, RenderCore, SlateCore, TimeManagement
- PrivateIncludePathModuleNames: Media
- PublicDependencyModuleNames: MediaAssets

### `Plugins/Media/AjaMedia/Source/AjaMedia/Private/Aja/Aja.h` (Private)


#### class `FAja`  
`class FAja`  
_L16-30_
- L19 _public prototype_ `static bool Initialize();`
- L20 _public prototype_ `static bool IsInitialized();`
- L21 _public prototype_ `static void Shutdown();`
- L24 _public prototype_ `static FTimecode ConvertAJATimecode2Timecode(const AJA::FTimecode& InTimecode, const FFrameRate& InFPS);` — Helpers
- L26 _public function_ `static bool CanUseAJACard()`
- L29 _private member_ `static bool bCanForceAJAUsage;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AJA`

### `Plugins/Media/AjaMedia/Source/AjaMedia/Private/AjaMediaPrivate.h` (Private)


#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAjaMedia, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAjaMedia, Log, All);`
- L19 _namespace_ `namespace AjaMediaOption`
- L21 _variable_ `static const FName DeviceIndex("Dev` (scope `AjaMediaOption`)
- L22 _variable_ `static const FName PortIndex("Por` (scope `AjaMediaOption`)
- L23 _variable_ `static const FName TransportType("Tra` (scope `AjaMediaOption`)
- L24 _variable_ `static const FName QuadTransportType("Qua` (scope `AjaMediaOption`)
- L25 _variable_ `static const FName TimecodeFormat("Tim` (scope `AjaMediaOption`)
- L26 _variable_ `static const FName LogDropFrame("Log` (scope `AjaMediaOption`)
- L27 _variable_ `static const FName EncodeTimecodeInTexel("Enc` (scope `AjaMediaOption`)
- L28 _variable_ `static const FName CaptureWithAutoCirculating("Cap` (scope `AjaMediaOption`)
- L29 _variable_ `static const FName StopOnTimeout("Sto` (scope `AjaMediaOption`)
- L30 _variable_ `static const FName CaptureAncillary("Cap` (scope `AjaMediaOption`)
- L31 _variable_ `static const FName CaptureAudio("Cap` (scope `AjaMediaOption`)
- L32 _variable_ `static const FName CaptureVideo("Cap` (scope `AjaMediaOption`)
- L33 _variable_ `static const FName MaxAncillaryFrameBuffer("Max` (scope `AjaMediaOption`)
- L34 _variable_ `static const FName AudioChannel("Aud` (scope `AjaMediaOption`)
- L35 _variable_ `static const FName MaxAudioFrameBuffer("Max` (scope `AjaMediaOption`)
- L36 _variable_ `static const FName AjaVideoFormat("Aja` (scope `AjaMediaOption`)
- L37 _variable_ `static const FName ColorFormat("Col` (scope `AjaMediaOption`)
- L38 _variable_ `static const FName SRGBInput("sRG` (scope `AjaMediaOption`)
- L39 _variable_ `static const FName MaxVideoFrameBuffer("Max` (scope `AjaMediaOption`)
- L41 _variable_ `static const AJA::FAJAVideoFormat DefaultVideoFormat = 9;` (scope `AjaMediaOption`) — 1080p3000

### `Plugins/Media/AjaMedia/Source/AjaMedia/Private/Player/AjaMediaAudioSample.h` (Private)


#### class `FAjaMediaAudioSample`  
`class FAjaMediaAudioSample : public FMediaIOCoreAudioSampleBase`  
_L11-33_
- inherits: `FMediaIOCoreAudioSampleBase`
- desc: Implements a media audio sample for AjaMedia.
- L14 _private typedef_ `using Super = FMediaIOCoreAudioSampleBase;`
- L18 _public function_ `bool Initialize(const AJA::AJAAudioFrameData& InAudioData, FTimespan InTime, const TOptional<FTimecode>& InTimecode)`
- L29 _public function_ `virtual void* RequestBuffer(uint32 InBufferSize) override`

#### class `FAjaMediaAudioSamplePool`  
`class FAjaMediaAudioSamplePool : public TMediaObjectPool<FAjaMediaAudioSample>`  
_L38-38_
- inherits: `TMediaObjectPool<FAjaMediaAudioSample>`
- desc: Implements a pool for AJA audio sample objects.

### `Plugins/Media/AjaMedia/Source/AjaMedia/Private/Player/AjaMediaBinarySample.h` (Private)


#### class `FAjaMediaBinarySamplePool`  
`class FAjaMediaBinarySamplePool : public TMediaObjectPool<FMediaIOCoreBinarySampleBase>`  
_L13-13_
- inherits: `TMediaObjectPool<FMediaIOCoreBinarySampleBase>`

### `Plugins/Media/AjaMedia/Source/AjaMedia/Private/Player/AjaMediaPlayer.h` (Private)


#### class `FAjaMediaPlayer`  
`class FAjaMediaPlayer : public FMediaIOCorePlayerBase , protected AJA::IAJAInputOutputChannelCallbackInterface`  
_L44-225_
- inherits: `FMediaIOCorePlayerBase,AJA::IAJAInputOutputChannelCallbackInterface`
- desc: Implements a media player using AJA. The processing of metadata and video frames is delayed until the fetch stage (TickFetch) in order to increase the window of opportunity for receiving AJA frames for the current render frame time code. Depending on whether the media source enables time code synchronization, the player's current play time (CurrentTime) is derived either from the time codes embedded in AJA frames or from the Engine's global time code.
- L48 _private typedef_ `using Super = FMediaIOCorePlayerBase;`
- L56 _public prototype_ `FAjaMediaPlayer(IMediaEventSink& InEventSink);` — Create and initialize a new instance. @param InEventSink The object that receives media events from this player.
- L59 _public prototype_ `virtual ~FAjaMediaPlayer();` — Virtual destructor.
- L65 _public prototype_ `virtual void Close() override;`
- L66 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L68 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L70 _public prototype_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode) override;`
- L71 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L73 _public prototype_ `virtual FString GetStats() const override;`
- L75 _public prototype_ `bool SetRate(float Rate) override;`
- L78 _public prototype_ `virtual bool ShouldAutoRecordSourceOpenedEvent() const override;`
- L83 _public prototype_ `virtual const FSlateBrush* GetDisplayIcon() const override;`
- L90 _protected prototype_ `virtual void OnInitializationCompleted(bool bSucceed) override;`
- L91 _protected prototype_ `virtual bool OnRequestInputBuffer(const AJA::AJARequestInputBufferData& InRequestBuffer, AJA::AJARequestedInputBufferData& OutRequestedBuffer) override;`
- L92 _protected prototype_ `virtual bool OnInputFrameReceived(const AJA::AJAInputFrameData& InInputFrame, const AJA::AJAAncillaryFrameData& InAncillaryFrame, const AJA::AJAAudioFrameData& AudioFrame, const AJA::AJAVideoFrameData& VideoFrame) override;`
- L93 _protected prototype_ `virtual bool OnOutputFrameCopied(const AJA::AJAOutputFrameData& InFrameData) override;`
- L94 _protected prototype_ `virtual void OnCompletion(bool bSucceed) override;`
- L95 _protected prototype_ `virtual void OnFormatChange(AJA::FAJAVideoFormat Format) override;`
- L103 _protected prototype_ `void ProcessFrame();` — Process pending audio and video frames, and forward them to the sinks.
- L108 _protected prototype_ `void VerifyFrameDropCount();` — Verify if we lost some frames since last Tick
- L110 _protected prototype_ `virtual bool IsHardwareReady() const override;`
- L113 _protected prototype_ `virtual void SetupSampleChannels() override;`
- L114 _protected function_ `virtual uint32 GetNumVideoFrameBuffers() const override`
- L118 _protected function_ `virtual EMediaIOCoreColorFormat GetColorFormat() const override`
- L123 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> AcquireTextureSample_AnyThread() const override;`
- L126 _protected prototype_ `virtual FString GetAnalyticsEventPrefix() const override;`
- L127 _protected prototype_ `virtual void GetAnalyticsEventAttributes(const FString& EventName, TArray<FAnalyticsEventAttribute>& InOutAttributes) const override;`
- L132 _private prototype_ `bool Open_Internal(const FString& Url, const IMediaOptions* Options, AJA::AJAInputOutputChannelOptions AjaOptions);`
- L133 _private prototype_ `void OpenFromFormatChange(AJA::AJADeviceOptions DeviceOptions, AJA::AJAInputOutputChannelOptions AjaOptions);`
- L134 _private prototype_ `void OnAutoDetected(TArray<FAjaDeviceProvider::FMediaIOConfigurationWithTimecodeFormat> Configurations, FString Url, const IMediaOptions* Options, bool bAutoDetectVideoFormat, bool bAutoDetectTimecodeFormat);`
- L142 _private prototype_ `void PublishAutoDetectedFormatToSource(const FMediaIOConfiguration& InDetectedConfiguration);` — Surface the auto-detected configuration on the source asset so the Media Profile editor can display the actual signal format instead of the stored default. Safe to call from any thread; the UObject mutation is dispatched onto the game thread.
- L148 _private member_ `TUniquePtr<FAjaMediaAudioSamplePool> AudioSamplePool;` — Audio, MetaData, Texture  sample object pool.
- L149 _private member_ `TUniquePtr<FAjaMediaBinarySamplePool> MetadataSamplePool;`
- L150 _private member_ `TUniquePtr<FAjaMediaTextureSamplePool> TextureSamplePool;`
- L152 _private member_ `TSharedPtr<FMediaIOCoreBinarySampleBase, ESPMode::ThreadSafe> AjaThreadCurrentAncSample;`
- L153 _private member_ `TSharedPtr<FMediaIOCoreBinarySampleBase, ESPMode::ThreadSafe> AjaThreadCurrentAncF2Sample;`
- L154 _private member_ `TSharedPtr<FAjaMediaAudioSample, ESPMode::ThreadSafe> AjaThreadCurrentAudioSample;`
- L155 _private member_ `TSharedPtr<FAjaMediaTextureSample, ESPMode::ThreadSafe> AjaThreadCurrentTextureSample;`
- L158 _private member_ `int32 MaxNumAudioFrameBuffer = 0;` — The media sample cache.
- L159 _private member_ `int32 MaxNumMetadataFrameBuffer = 0;`
- L160 _private member_ `int32 MaxNumVideoFrameBuffer = 0;`
- L163 _private member_ `EMediaState AjaThreadNewState = EMediaState::Closed;` — Current state of the media player.
- L166 _private member_ `IMediaEventSink& EventSink;` — The media event handler.
- L169 _private member_ `int32 AjaThreadAudioChannels = 0;` — Number of audio channels in the last received sample.
- L172 _private member_ `int32 AjaThreadAudioSampleRate = 0;` — Audio sample rate in the last received sample.
- L175 _private member_ `int32 AjaThreadFrameDropCount = 0;` — Number of frames drop from the last tick.
- L176 _private member_ `int32 PreviousMetadataFrameDropCount = 0;`
- L177 _private member_ `int32 PreviousAudioFrameDropCount = 0;`
- L178 _private member_ `int32 PreviousVideoFrameDropCount = 0;`
- L181 _private member_ `uint32 LastFrameDropCount = 0;` — Number of frames drop from the last tick.
- L182 _private member_ `uint32 PreviousFrameDropCount = 0;`
- L185 _private member_ `bool bEncodeTimecodeInTexel = false;` — Whether to use the time code embedded in AJA frames.
- L188 _private member_ `bool bUseFrameTimecode = false;` — Whether to use the timecode embedded in a frame.
- L191 _private member_ `bool bIsSRGBInput = false;` — Whether the input is in sRGB and can have a ToLinear conversion.
- L194 _private member_ `bool bUseAncillary = false;` — Which field need to be capture.
- L195 _private member_ `bool bUseAudio = false;`
- L196 _private member_ `bool bUseVideo = false;`
- L197 _private member_ `bool bVerifyFrameDropCount = true;`
- L200 _private member_ `AJA::AJAInputChannel* InputChannel = nullptr;` — Maps to the current input Device
- L203 _private member_ `EMediaIOSampleType SupportedSampleTypes = EMediaIOSampleType::None;` — Used to flag which sample types we advertise as supported for timed data monitoring
- L206 _private member_ `AJA::FTimecode AjaThreadPreviousFrameTimecode;` — Previous frame timecode for stats purpose
- L209 _private member_ `std::atomic<bool> bPauseRequested = false;` — Flag to indicate that pause is being requested
- L212 _private member_ `EAjaMediaSourceColorFormat AjaColorFormat = EAjaMediaSourceColorFormat::YUV2_8bit;` — AJA media source color format.
- L215 _private member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> AjaColorSettings;` — Container for local media source color setting overrides.
- L218 _private member_ `TPimplPtr<class FAjaDeviceProvider> DeviceProvider;` — Device provider used to autodetect input format.
- L221 _private member_ `EMediaIOTimecodeFormat TimecodeFormat = EMediaIOTimecodeFormat::None;` — Autodetected or specified Timecode format.
- L224 _private member_ `bool bAddedSynchronizedSamples = false;` — Whether samples have been added to the queue while the genlocked time step is synchronized. Reset when the time step is closed.

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace AJA`

### `Plugins/Media/AjaMedia/Source/AjaMedia/Private/Player/AjaMediaTextureSample.h` (Private)


#### class `FAjaMediaTextureSample`  
`class FAjaMediaTextureSample : public FMediaIOCoreTextureSampleBase`  
_L12-67_
- inherits: `FMediaIOCoreTextureSampleBase`
- desc: Implements a media texture sample for AjaMedia.
- L15 _private typedef_ `using Super = FMediaIOCoreTextureSampleBase;`
- L28 _public function_ `bool InitializeProgressive(const AJA::AJAVideoFrameData& InVideoData, EMediaTextureSampleFormat InSampleFormat, FTimespan InTime, const FFrameRate& InFrameRate, const TOptional<FTimecode>& InTimecode, TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> InSourceColorSettings)` — Initialize the sample. @param InVideoData The video frame data. @param InSampleFormat The sample format. @param InTime The sample time (in the player's own clock). @param InFrameRate The framerate of the media that produce the sample. @param InTimecode The sample timecode if available. @param InSourceColorSettings Information about the texture color encoding and color space.
- L53 _public function_ `bool InitializeInterlaced_Halfed(const AJA::AJAVideoFrameData& InVideoData, EMediaTextureSampleFormat InSampleFormat, FTimespan InTime, const FFrameRate& InFrameRate, const TOptional<FTimecode>& InTimecode, bool bInEven, TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> InSourceColorSettings)` — Initialize the sample. @param InVideoData The video frame data. @param InSampleFormat The sample format. @param InTime The sample time (in the player's own clock). @param InFrameRate The framerate of the media that produce the sample. @param InTimecode The sample timecode if available. @param bEven Only take the even frame from the image. @param InSourceColorSettings Information about the texture color encoding and color space.

#### class `FAjaMediaTextureSamplePool`  
`class FAjaMediaTextureSamplePool : public TMediaObjectPool<FAjaMediaTextureSample>`  
_L72-72_
- inherits: `TMediaObjectPool<FAjaMediaTextureSample>`
- desc: Implements a pool for AJA texture sample objects.

### `Plugins/Media/AjaMedia/Source/AjaMedia/Private/Shared/AjaMediaAllowPlatformTypes.h` (Private)


#### Free symbols / members of external scopes

- L4 _macro_ `#define AJA_PLATFORM_TYPES_GUARD`
- L13 _macro_ `#define DWORD ::DWORD`
- L14 _macro_ `#define FLOAT ::FLOAT`
- L17 _macro_ `#define TRUE 1`
- L21 _macro_ `#define FALSE 0`

### `Plugins/Media/AjaMedia/Source/AjaMedia/Private/Shared/AjaMediaHidePlatformTypes.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/AjaMedia/Source/AjaMedia/Public/AjaCustomTimeStep.h` (Public)


#### class `UAjaCustomTimeStep`  
`class UAjaCustomTimeStep : public UGenlockedCustomTimeStep`  
_L23-130_
- reflection: `UCLASS(Blueprintable, editinlinenew, meta=(DisplayName="AJA SDI Input", MediaIOCustomLayout="AJA"))`
- inherits: `UGenlockedCustomTimeStep`
- desc: Control the Engine TimeStep via the AJA card. When the signal is lost in the editor (not in PIE), the CustomTimeStep will try to re-synchronize every second.
- L29 _public prototype_ `virtual bool Initialize(UEngine* InEngine) override;`
- L30 _public prototype_ `virtual void Shutdown(UEngine* InEngine) override;`
- L31 _public prototype_ `virtual bool UpdateTimeStep(UEngine* InEngine) override;`
- L32 _public prototype_ `virtual ECustomTimeStepSynchronizationState GetSynchronizationState() const override;`
- L33 _public prototype_ `virtual FFrameRate GetFixedFrameRate() const override;`
- L36 _public prototype_ `virtual uint32 GetLastSyncCountDelta() const override;`
- L37 _public prototype_ `virtual bool IsLastSyncDataValid() const override;`
- L38 _public prototype_ `virtual FFrameRate GetSyncRate() const override;`
- L39 _public prototype_ `virtual bool WaitForSync() override;`
- L40 _public function_ `virtual bool SupportsFormatAutoDetection() const`
- L43 _public prototype_ `virtual void BeginDestroy() override;`
- L45 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L52 _private prototype_ `void ReleaseResources();`
- L53 _private prototype_ `bool VerifyGenlockSignal();`
- L54 _private prototype_ `bool Initialize_Internal(class UEngine* InEngine);`
- L55 _private prototype_ `void OnConfigurationAutoDetected(TArray<FAjaDeviceProvider::FMediaIOConfigurationWithTimecodeFormat> InConfigurations, class UEngine* InEngine, bool bReinitialize);`
- L56 _private prototype_ `void DetectConfiguration(class UEngine* InEngine, bool bReinitialize);`
- L57 _private prototype_ `bool IsInterlaced() const;`
- L65 _public member_ `bool bUseReferenceIn;` — `UPROPERTY(EditAnywhere, Category="Genlock")` — If true, the Engine will wait for a signal coming in from the Reference In pin. It will also configure the card Genlock mode and configure the selected Media Port as an output.
- L69 _public member_ `FMediaIOConfiguration MediaConfiguration;` — `UPROPERTY(EditAnywhere, Category="Genlock", meta=(DisplayName="Configuration"))` — The device, port and video settings that correspond to where the Genlock signal will be coming from
- L76 _public member_ `bool bStopOnCardTimeout = true;` — `UPROPERTY(EditAnywhere, Category = "Genlock")` — If this is disabled, genlock will attempt to recover if the SDK timeouts while waiting for an interrupt signal from the card. It will remain in the synchronizing state until the card receives a signal. Note: In editor outside of PIE and -game, the CustomTimeStep will try to restart itself automatically regardless of this setting.
- L86 _public member_ `bool bWaitForFrameToBeReady;` — `UPROPERTY(EditAnywhere, Category = "Genlock options", meta=(EditCondition="!bUseReferenceIn"))` — If true, the Engine will wait for the frame to be read. This will introduce random latency (the time it takes to read a frame). Use this option when you want to synchronize the engine with the incoming frame and discard the buffered frames. @note If false, there is no guarantee that the incoming frame will be ready since it takes some time to read a frame. @note This will not work as intended with interlaced transport because both fields are processed at the same time.
- L90 _public member_ `EMediaIOTimecodeFormat TimecodeFormat;` — `UPROPERTY(EditAnywhere, Category="Genlock options", meta=(EditCondition="!bUseReferenceIn"))` — The type of Timecode to read from SDI stream.
- L94 _public member_ `bool bEnableOverrunDetection;` — `UPROPERTY(EditAnywhere, Category="Genlock options", meta=(DisplayName="Display Dropped Frames Warning"))` — Enable mechanism to detect Engine loop overrunning the source
- L98 _private member_ `AJA::AJASyncChannel* SyncChannel;` — AJA Port to capture the Sync
- L99 _private member_ `FAJACallback* SyncCallback;`
- L104 _private member_ `TObjectPtr<UEngine> InitializedEngine;` — `UPROPERTY(Transient)` — Engine used to initialize the CustomTimeStep
- L107 _private member_ `double LastAutoSynchronizeInEditorAppTime;` — When Auto synchronize is enabled, the time the last attempt was triggered.
- L109 _private member_ `double LastAutoDetectInEditorAppTime;`
- L113 _private member_ `ECustomTimeStepSynchronizationState State;` — The current SynchronizationState of the CustomTimeStep
- L116 _private member_ `bool bWarnedAboutVSync;` — Warn if there is a CustomTimeStep and a vsync at the same time but only once.
- L119 _private member_ `bool bIsPreviousSyncCountValid;` — Remember the last Sync Count
- L120 _private member_ `uint32 PreviousSyncCount;`
- L121 _private member_ `uint32 SyncCountDelta;`
- L124 _private member_ `AJA::FAJAVideoFormat LastDetectedVideoFormat;` — Remember last detected video format
- L125 _private member_ `bool bLastDetectedVideoFormatInitialized;`
- L127 _private member_ `TUniquePtr<class FAjaDeviceProvider> DeviceProvider;`
- L128 _private member_ `bool bEncounteredInvalidAutoDetectFrame = false;`
- L129 _private member_ `bool bIgnoreWarningForOneFrame = true;`

### `Plugins/Media/AjaMedia/Source/AjaMedia/Public/AjaDeviceProvider.h` (Public)


#### struct `FAjaMediaTimecodeConfiguration`  
`struct FAjaMediaTimecodeConfiguration`  
_L15-45_
- reflection: `USTRUCT()`
- desc: Configuration of an AJA timecode from Video
- L19 _public prototype_ `FAjaMediaTimecodeConfiguration();`
- L22 _public prototype_ `static FAjaMediaTimecodeConfiguration GetDefault();` — Used by the UX to have a default selected value. May not be valid with every device.
- L27 _public member_ `FMediaIOConfiguration MediaConfiguration;` — `UPROPERTY(VisibleAnywhere, Category=AJA)` — Read the timecode from a video signal.
- L31 _public member_ `EMediaIOTimecodeFormat TimecodeFormat;` — `UPROPERTY(VisibleAnywhere, Category=AJA)` — Timecode format to read from a video signal.
- L36 _public prototype_ `bool IsValid() const;` — Return true if the configuration has been set properly
- L38 _public prototype_ `bool operator== (const FAjaMediaTimecodeConfiguration& Other) const;`
- L44 _public prototype_ `FText ToText() const;` — Get the configuration text representation. @return String representation, i.e. "Video/Single1/1080p30fps/LTC".

#### struct `FAjaMediaTimecodeReference`  
`struct FAjaMediaTimecodeReference`  
_L51-81_
- reflection: `USTRUCT()`
- desc: Configuration of an AJA timecode.
- L55 _public prototype_ `FAjaMediaTimecodeReference();`
- L58 _public prototype_ `static FAjaMediaTimecodeReference GetDefault();` — Used by the UX to have a default selected value. May not be valid with every device.
- L63 _public member_ `FMediaIODevice Device;` — `UPROPERTY(VisibleAnywhere, Category=AJA)` — The frame rate of the LTC from the reference pin.
- L67 _public member_ `int32 LtcIndex;` — `UPROPERTY(VisibleAnywhere, Category=AJA)` — The LTC index to read from the reference pin.
- L71 _public member_ `FFrameRate LtcFrameRate;` — `UPROPERTY(VisibleAnywhere, Category=AJA)` — The frame rate of the LTC from the reference pin.
- L75 _public prototype_ `bool IsValid() const;` — Return true if the configuration has been set properly
- L77 _public prototype_ `bool operator== (const FAjaMediaTimecodeReference& Other) const;`
- L80 _public prototype_ `FText ToText() const;` — Get the configuration text representation.

#### class `FAjaDeviceProvider`  
`class FAjaDeviceProvider : public IMediaIOCoreDeviceProvider`  
_L88-137_
- inherits: `IMediaIOCoreDeviceProvider`
- desc: Implementation of IMediaIOCoreDeviceProvider for AJA
- L91 _public prototype_ `static FName GetProviderName();`
- L92 _public prototype_ `static FName GetProtocolName();`
- L94 _public prototype_ `FAjaDeviceProvider();`
- L95 _public prototype_ `virtual ~FAjaDeviceProvider();`
- L96 _public prototype_ `FAjaDeviceProvider(const FAjaDeviceProvider&) = delete;`
- L97 _public prototype_ `FAjaDeviceProvider& operator=(const FAjaDeviceProvider&) = delete;`
- L100 _public prototype_ `bool CanDeviceDoAlpha(const FMediaIODevice& InDevice) const;` — Can device do fill and key
- L108 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnConfigurationAutoDetected, TArray<FMediaIOConfigurationWithTimecodeFormat>);`
- L111 _public prototype_ `void AutoDetectConfiguration(FOnConfigurationAutoDetected OnAutoDetected);` — Auto detect sources that are currently streaming to the device
- L112 _public prototype_ `void EndAutoDetectConfiguration();`
- L116 _public prototype_ `virtual FName GetFName() override;`
- L118 _public prototype_ `virtual TArray<FMediaIOConnection> GetConnections() const override;`
- L119 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations() const override;`
- L120 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations(bool bAllowInput, bool bAllowOutput) const override;`
- L121 _public prototype_ `virtual TArray<FMediaIOInputConfiguration> GetInputConfigurations() const override;`
- L122 _public prototype_ `virtual TArray<FMediaIOOutputConfiguration> GetOutputConfigurations() const override;`
- L123 _public prototype_ `virtual TArray<FMediaIODevice> GetDevices() const override;`
- L124 _public prototype_ `virtual TArray<FMediaIOMode> GetModes(const FMediaIODevice& InDevice, bool bInOutput) const override;`
- L125 _public prototype_ `virtual TArray<FMediaIOVideoTimecodeConfiguration> GetTimecodeConfigurations() const override;`
- L126 _public prototype_ `TArray<FAjaMediaTimecodeConfiguration> GetTimecodeConfiguration() const;`
- L127 _public prototype_ `TArray<FAjaMediaTimecodeReference> GetTimecodeReferences() const;`
- L129 _public prototype_ `virtual FMediaIOConfiguration GetDefaultConfiguration() const override;`
- L130 _public prototype_ `virtual FMediaIOMode GetDefaultMode() const override;`
- L131 _public prototype_ `virtual FMediaIOInputConfiguration GetDefaultInputConfiguration() const override;`
- L132 _public prototype_ `virtual FMediaIOOutputConfiguration GetDefaultOutputConfiguration() const override;`
- L133 _public prototype_ `virtual FMediaIOVideoTimecodeConfiguration GetDefaultTimecodeConfiguration() const override;`
- L136 _private member_ `TUniquePtr<FAJAAutoDetectChannelCallback> AutoDetectCallback;`

#### struct `FAjaDeviceProvider::FMediaIOConfigurationWithTimecodeFormat`  
`struct FMediaIOConfigurationWithTimecodeFormat`  
_L103-107_
- desc: Auto detect sources that are currently streaming to the device
- L105 _public member_ `FMediaIOConfiguration Configuration;`
- L106 _public member_ `EMediaIOTimecodeFormat TimecodeFormat;`

#### Free symbols / members of external scopes

- L108 _delegate_ `DECLARE_DELEGATE_OneParam(FOnConfigurationAutoDetected, TArray<FMediaIOConfigurationWithTimecodeFormat>);`

### `Plugins/Media/AjaMedia/Source/AjaMedia/Public/AjaMediaDefinitions.h` (Public)


#### enum `EAjaHDRMetadataEOTF`  
`enum class EAjaHDRMetadataEOTF : uint8`  
_L18-23_
- reflection: `UENUM()`
- desc: HDR Transfer function. Must match AJA::EAjaHDRMetadataEOTF.
- L20 _public enumerator_ `SDR`
- L21 _public enumerator_ `HLG`
- L22 _public enumerator_ `PQ`

#### enum `EAjaHDRMetadataGamut`  
`enum class EAjaHDRMetadataGamut : uint8`  
_L30-34_
- reflection: `UENUM()`
- desc: HDR Color Gamut. Must match AJA::EAjaHDRMetadataGamut.
- L32 _public enumerator_ `Rec709`
- L33 _public enumerator_ `Rec2020`

#### struct `FAjaMediaHDROptions`  
`struct FAjaMediaHDROptions`  
_L40-51_
- reflection: `USTRUCT()`
- desc: Set of metadata describing a HDR video signal.
- L46 _public member_ `EAjaHDRMetadataEOTF EOTF = EAjaHDRMetadataEOTF::SDR;` — `UPROPERTY(EditAnywhere, Category = "HDR")` — Transfer function to use for converting the video signal to an optical signal.
- L50 _public member_ `EAjaHDRMetadataGamut Gamut = EAjaHDRMetadataGamut::Rec709;` — `UPROPERTY(EditAnywhere, Category = "HDR")` — The color gamut of the video signal.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AJA`
- L53 _namespace_ `namespace UE`
- L53 _namespace_ `namespace AjaMedia` (scope `UE`)
- L56 _prototype_ `FAjaMediaHDROptions MakeAjaMediaHDROptions(const AJA::FAjaHDROptions& HDROptions);` (scope `UE::AjaMedia`) — Create Aja HDR UStruct from the AJALib's hdr struct.
- L58 _prototype_ `AJA::FAjaHDROptions MakeAjaHDROptions(const FAjaMediaHDROptions& HDROptions);` (scope `UE::AjaMedia`) — Create AJALib's hdr struct from the Aja HDR UStruct.

### `Plugins/Media/AjaMedia/Source/AjaMedia/Public/AjaMediaSettings.h` (Public)


#### class `UAjaMediaSettings`  
`class UAjaMediaSettings : public UObject`  
_L13-16_
- reflection: `UCLASS(config=AjaMedia)`
- inherits: `UObject`
- desc: Settings for the AjaMedia plug-in.

### `Plugins/Media/AjaMedia/Source/AjaMedia/Public/AjaMediaSource.h` (Public)


#### enum `EAjaMediaSourceColorFormat`  
`enum class EAjaMediaSourceColorFormat : uint8`  
_L16-20_
- reflection: `UENUM()`
- desc: Native data format.
- L18 _public enumerator_ `YUV2_8bit UMETA(DisplayName = "8bit YUV")`
- L19 _public enumerator_ `YUV_10bit UMETA(DisplayName = "10bit YUV")`

#### enum `EAjaMediaAudioChannel`  
`enum class EAjaMediaAudioChannel : uint8`  
_L26-30_
- reflection: `UENUM()`
- desc: Available number of audio channel supported by Unreal Engine & AJA
- L28 _public enumerator_ `Channel6`
- L29 _public enumerator_ `Channel8`

#### class `UAjaMediaSource`  
`class UAjaMediaSource : public UCaptureCardMediaSource`  
_L36-167_
- reflection: `UCLASS(BlueprintType, hideCategories=(Platforms,Object), PrioritizeCategories=(AJA, Video, ColorManagement, Audio, Ancillary, Synchronization, Debug), meta=(MediaIOCustomLayout="AJA"))`
- inherits: `UCaptureCardMediaSource`
- desc: Media source for AJA streams.
- L41 _private prototype_ `UAjaMediaSource();` — Default constructor.
- L46 _public member_ `FMediaIOConfiguration MediaConfiguration;` — `UPROPERTY(EditAnywhere, Category="AJA", meta=(DisplayName="Configuration"))` — The device, port and video settings that correspond to the input.
- L52 _public member_ `EMediaIOTimecodeFormat TimecodeFormat_DEPRECATED = EMediaIOTimecodeFormat::None;` — `UPROPERTY(meta=(DeprecatedProperty))` — Use the time code embedded in the input stream.
- L57 _public member_ `EMediaIOAutoDetectableTimecodeFormat AutoDetectableTimecodeFormat = EMediaIOAutoDetectableTimecodeFormat::Auto;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="AJA", meta = (DisplayName = "Timecode Format"))` — Use the time code embedded in the input stream.
- L64 _public member_ `bool bCaptureWithAutoCirculating;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="AJA")` — Use a ring buffer to capture and transfer data. This may decrease transfer latency but increase stability.
- L72 _public member_ `bool bCaptureAncillary;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ancillary")` — Capture Ancillary from the AJA source. It will decrease performance
- L76 _public member_ `int32 MaxNumAncillaryFrameBuffer;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category="Ancillary", meta=(EditCondition="bCaptureAncillary", ClampMin="1", ClampMax="32"))` — Maximum number of ancillary data frames to buffer.
- L82 _public member_ `bool bStopInputOnCardTimeout = true;` — `UPROPERTY(EditAnywhere, Category = "AJA")` — If this is disabled, input will keep going even if we hit a timeout when waiting for a vertical interrupt from the card.
- L87 _public member_ `bool bCaptureAudio;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Audio")` — Capture Audio from the AJA source.
- L91 _public member_ `EAjaMediaAudioChannel AudioChannel;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Audio", meta=(EditCondition="bCaptureAudio"))` — Desired number of audio channel to capture.
- L95 _public member_ `int32 MaxNumAudioFrameBuffer;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category="Audio", meta=(EditCondition="bCaptureAudio", ClampMin="1", ClampMax="32"))` — Maximum number of audio frames to buffer.
- L100 _public member_ `bool bCaptureVideo;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Video")` — Capture Video from the AJA source.
- L104 _public member_ `EAjaMediaSourceColorFormat ColorFormat;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Video", meta=(EditCondition="bCaptureVideo"))` — Native data format internally used by the device after being converted from SDI/HDMI signal.
- L113 _public member_ `bool bIsSRGBInput_DEPRECATED = false;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage = "Use ColorEncoding instead."))` — Whether the video input is in sRGB color space. A sRGB to Linear conversion will be applied resulting in a texture in linear space. @Note If the texture is not in linear space, it won't look correct in the editor. Another pass will be required either through Composure or other means.
- L118 _public member_ `int32 MaxNumVideoFrameBuffer;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category="Video", meta=(EditCondition="bCaptureVideo", ClampMin="1", ClampMax="32"))` — Maximum number of video frames to buffer.
- L123 _public member_ `bool bLogDropFrame;` — `UPROPERTY(EditAnywhere, Category="Debug")` — Log a warning when there's a drop frame.
- L130 _public member_ `bool bEncodeTimecodeInTexel;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Debug", meta=(DisplayName="Burn Frame Timecode"))` — Burn Frame Timecode in the input texture without any frame number clipping. @Note Only supported with progressive format.
- L136 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const override;`
- L137 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const override;`
- L138 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const override;`
- L139 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
- L144 _public prototype_ `virtual FString GetUrl() const override;`
- L145 _public prototype_ `virtual bool Validate() const override;`
- L148 _public prototype_ `virtual FString GetDescriptionString() const override;`
- L149 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<TTuple<FText, FText, FText>>& OutInfoElements) const override;`
- L156 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L157 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L160 _public prototype_ `virtual void PostLoad() override;`
- L161 _public function_ `virtual bool SupportsFormatAutoDetection() const override`
- L166 _private prototype_ `void AssignDefaultConfiguration();` — Assigns a default configuration if the current configuration is invalid.

### `Plugins/Media/AjaMedia/Source/AjaMedia/Public/AjaTimecodeProvider.h` (Public)


#### class `UAjaTimecodeProvider`  
`class UAjaTimecodeProvider : public UGenlockedTimecodeProvider, public FTickableGameObject`  
_L26-129_
- reflection: `UCLASS(Blueprintable, editinlinenew, meta=(DisplayName="AJA SDI Input", MediaIOCustomLayout="AJA"))`
- inherits: `UGenlockedTimecodeProvider,FTickableGameObject`
- desc: Class to fetch a timecode via an AJA card. When the signal is lost in the editor (not in PIE), the TimecodeProvider will try to re-synchronize every second.
- L31 _public prototype_ `UAjaTimecodeProvider();`
- L34 _public prototype_ `virtual bool FetchTimecode(FQualifiedFrameTime& OutFrameTime) override;`
- L35 _public function_ `virtual ETimecodeProviderSynchronizationState GetSynchronizationState() const override`
- L36 _public prototype_ `virtual bool Initialize(class UEngine* InEngine) override;`
- L37 _public prototype_ `virtual void Shutdown(class UEngine* InEngine) override;`
- L38 _public function_ `virtual bool SupportsAutoDetected() const override`
- L43 _public function_ `virtual void SetIsAutoDetected(bool bInIsAutoDetected) override`
- L48 _public function_ `virtual bool IsAutoDetected() const override`
- L54 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L55 _public prototype_ `virtual bool IsTickable() const override;`
- L56 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L57 _public function_ `virtual bool IsTickableInEditor() const override`
- L58 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L59 _public function_ `virtual TStatId GetStatId() const override`
- L62 _public prototype_ `virtual void BeginDestroy() override;`
- L63 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L64 _public prototype_ `virtual void PostLoad() override;`
- L70 _private prototype_ `void ReleaseResources();`
- L71 _private prototype_ `bool Initialize_Internal(class UEngine* InEngine, AJA::AJATimecodeChannelOptions InOptions);`
- L72 _private prototype_ `void OnConfigurationAutoDetected(TArray<FAjaDeviceProvider::FMediaIOConfigurationWithTimecodeFormat> InConfigurations, class UEngine* InEngine);`
- L80 _public member_ `bool bUseDedicatedPin;` — `UPROPERTY(EditAnywhere, Category="Timecode")` — Should we read the timecode from a dedicated LTC pin or an SDI input.
- L86 _public member_ `bool bUseReferenceIn;` — `UPROPERTY(EditAnywhere, Category="Timecode", meta = (EditCondition = "bUseDedicatedPin"))` — Read LTC timecode from reference pin. Will fail if device doesn't support that feature.
- L92 _public member_ `FAjaMediaTimecodeReference LTCConfiguration;` — `UPROPERTY(EditAnywhere, Category="Timecode", meta=(EditCondition="bUseDedicatedPin"))` — Where to read LTC timecode from with which FrameRate expected
- L100 _public member_ `FAjaMediaTimecodeConfiguration VideoConfiguration_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))` — It read the timecode from an input source.
- L106 _public member_ `FMediaIOVideoTimecodeConfiguration TimecodeConfiguration;` — Timecode format to read from a video signal.
- L109 _public member_ `bool bAutoDetectTimecode = true;` — `UPROPERTY()`
- L113 _private member_ `AJA::AJATimecodeChannel* TimecodeChannel;` — AJA channel associated with reading LTC timecode
- L114 _private member_ `FAJACallback* SyncCallback;`
- L119 _private member_ `TObjectPtr<UEngine> InitializedEngine;` — `UPROPERTY(Transient)` — Engine used to initialize the Provider
- L122 _private member_ `double LastAutoSynchronizeInEditorAppTime;` — The time the last attempt to auto synchronize was triggered.
- L126 _private member_ `ETimecodeProviderSynchronizationState State;` — The current SynchronizationState of the TimecodeProvider
- L128 _private member_ `TUniquePtr<FAjaDeviceProvider> DeviceProvider;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace AJA`

### `Plugins/Media/AjaMedia/Source/AjaMedia/Public/IAjaMediaModule.h` (Public)


#### class `IAjaMediaModule`  
`class IAjaMediaModule : public IModuleInterface`  
_L16-41_
- inherits: `IModuleInterface`
- desc: Interface for the AjaMedia module.
- L20 _public function_ `static inline IAjaMediaModule& Get()`
- L31 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Create an AJA based media player. @param EventSink The object that receives media events from the player. @return A new media player, or nullptr if a player couldn't be created.
- L34 _public prototype_ `virtual TSharedPtr<FSlateStyleSet> GetStyle() = 0;` — @return SlateStyleSet to be used across the AjaMedia module
- L37 _public prototype_ `virtual bool IsInitialized() const = 0;` — @return true if the Aja module and AJA dll could be loaded
- L40 _public prototype_ `virtual bool CanBeUsed() const = 0;` — @return true if the Aja card can be used
