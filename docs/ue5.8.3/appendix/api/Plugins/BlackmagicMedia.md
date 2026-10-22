# Plugins / BlackmagicMedia

- module root: `Plugins/Media/BlackmagicMedia/Source/BlackmagicMedia`
- headers: 10; symbols: 179
- symbol kinds: class=9, delegate=1, enum=5, enumerator=13, function=16, macro=5, member=33, namespace=7, prototype=75, struct=1, typedef=1, variable=13
- DynamicallyLoadedModuleNames: Media
- PrivateDependencyModuleNames: BlackmagicCore, Engine, MediaUtils, OpenColorIO, Projects, SlateCore
- PrivateIncludePathModuleNames: Media
- PublicDependencyModuleNames: Core, CoreUObject, MediaAssets, MediaIOCore, RHI, RenderCore, TimeManagement

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMedia/Private/BlackmagicMediaPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlackmagicMedia, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlackmagicMedia, Log, All);`
- L10 _namespace_ `namespace BlackmagicMediaOption`
- L12 _variable_ `static const FName DeviceIndex("Dev` (scope `BlackmagicMediaOption`)
- L13 _variable_ `static const FName TimecodeFormat("Tim` (scope `BlackmagicMediaOption`)
- L14 _variable_ `static const FName CaptureAudio("Cap` (scope `BlackmagicMediaOption`)
- L15 _variable_ `static const FName AudioChannelOption("Aud` (scope `BlackmagicMediaOption`)
- L16 _variable_ `static const FName MaxAudioFrameBuffer("Max` (scope `BlackmagicMediaOption`)
- L17 _variable_ `static const FName CaptureVideo("Cap` (scope `BlackmagicMediaOption`)
- L18 _variable_ `static const FName BlackmagicVideoFormat("Bla` (scope `BlackmagicMediaOption`)
- L19 _variable_ `static const FName ColorFormat("Col` (scope `BlackmagicMediaOption`)
- L20 _variable_ `static const FName MaxVideoFrameBuffer("Max` (scope `BlackmagicMediaOption`)
- L21 _variable_ `static const FName LogDropFrame("Log` (scope `BlackmagicMediaOption`)
- L22 _variable_ `static const FName EncodeTimecodeInTexel("Enc` (scope `BlackmagicMediaOption`)
- L23 _variable_ `static const FName SRGBInput("sRG` (scope `BlackmagicMediaOption`)
- L25 _variable_ `static const BlackmagicDesign::FBlackmagicVideoFormat DefaultVideoFormat = 0x48703330;` (scope `BlackmagicMediaOption`) — 1080p 30fps

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMedia/Private/Player/BlackmagicMediaPlayer.h` (Private)


#### class `FBlackmagicMediaTextureSample`  
`class FBlackmagicMediaTextureSample : public FMediaIOCoreTextureSampleBase`  
_L26-63_
- inherits: `FMediaIOCoreTextureSampleBase`
- L29 _public function_ `virtual const FMatrix& GetYUVToRGBMatrix() const override`
- L36 _public function_ `virtual void ShutdownPoolable() override`
- L48 _public function_ `TSharedPtr<BlackmagicDesign::IInputEventCallback::FFrameBufferHolder>& GetBlackmagicInternalBufferLocker()` — Returns buffer guard so it can be initialized outside (for performance reason)
- L54 _public function_ `void ReleaseBlackmagicInternalBuffer()` — Unlock internal buffer referenced by this sample
- L62 _private member_ `TSharedPtr<BlackmagicDesign::IInputEventCallback::FFrameBufferHolder> VideoBufferGuard;` — Buffer guard instance

#### class `FBlackmagicMediaAudioSamplePool`  
`class FBlackmagicMediaAudioSamplePool : public TMediaObjectPool<FMediaIOCoreAudioSampleBase>`  
_L65-65_
- inherits: `TMediaObjectPool<FMediaIOCoreAudioSampleBase>`

#### class `FBlackmagicMediaTextureSamplePool`  
`class FBlackmagicMediaTextureSamplePool : public TMediaObjectPool<FBlackmagicMediaTextureSample>`  
_L66-66_
- inherits: `TMediaObjectPool<FBlackmagicMediaTextureSample>`

#### class `FBlackmagicMediaPlayer`  
`class FBlackmagicMediaPlayer : public FMediaIOCorePlayerBase`  
_L79-180_
- inherits: `FMediaIOCorePlayerBase`
- desc: Implements a media player for Blackmagic. The processing of metadata and video frames is delayed until the fetch stage (TickFetch) in order to increase the window of opportunity for receiving frames for the current render frame time code. Depending on whether the media source enables time code synchronization, the player's current play time (CurrentTime) is derived either from the time codes embedded in frames or from the Engine's global time code.
- L82 _private typedef_ `using Super = FMediaIOCorePlayerBase;`
- L91 _public prototype_ `FBlackmagicMediaPlayer(IMediaEventSink& InEventSink);` — Create and initialize a new instance. @param InEventSink The object that receives media events from this player.
- L94 _public prototype_ `virtual ~FBlackmagicMediaPlayer();` — Virtual destructor.
- L100 _public prototype_ `virtual void Close() override;`
- L101 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L103 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L105 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L106 _public prototype_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode) override;`
- L110 _public prototype_ `virtual const FSlateBrush* GetDisplayIcon() const override;`
- L116 _public prototype_ `void ProcessFrame();` — Process pending audio and video frames, and forward them to the sinks.
- L119 _public prototype_ `void VerifyFrameDropCount();` — Verify if we lost some frames since last Tick.
- L122 _public prototype_ `virtual bool IsHardwareReady() const override;` — Is Hardware initialized
- L126 _protected prototype_ `virtual void SetupSampleChannels() override;`
- L127 _protected function_ `virtual uint32 GetNumVideoFrameBuffers() const override`
- L131 _protected function_ `virtual EMediaIOCoreColorFormat GetColorFormat() const override`
- L135 _protected prototype_ `virtual void AddVideoSampleAfterGPUTransfer_RenderThread(const TSharedRef<FMediaIOCoreTextureSampleBase>& InSample) override;`
- L136 _protected function_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> AcquireTextureSample_AnyThread() const override`
- L142 _protected prototype_ `virtual FString GetAnalyticsEventPrefix() const override;`
- L143 _protected prototype_ `virtual void GetAnalyticsEventAttributes(const FString& EventName, TArray<FAnalyticsEventAttribute>& InOutAttributes) const override;`
- L150 _private member_ `BlackmagicMediaPlayerHelpers::FBlackmagicMediaPlayerEventCallback* EventCallback = nullptr;`
- L158 _private prototype_ `void PublishAutoDetectedFormatToSource(const BlackmagicDesign::FFormatInfo& NewFormat);` — Surface the SDK-detected format on the source asset so the Media Profile editor can display the actual signal format instead of the stored default. Safe to call from any thread; the UObject mutation is dispatched onto the game thread.
- L162 _private member_ `TUniquePtr<FBlackmagicMediaAudioSamplePool> AudioSamplePool;` — Audio, MetaData, Texture  sample object pool.
- L163 _private member_ `TUniquePtr<FBlackmagicMediaTextureSamplePool> TextureSamplePool;`
- L166 _private member_ `bool bVerifyFrameDropCount = false;` — Log warning about the amount of audio/video frame can't could not be cached .
- L169 _private member_ `int32 MaxNumAudioFrameBuffer = 0;` — Max sample count our different buffer can hold. Taken from MediaSource
- L170 _private member_ `int32 MaxNumVideoFrameBuffer = 0;`
- L173 _private member_ `EMediaIOSampleType SupportedSampleTypes;` — Used to flag which sample types we advertise as supported for timed data monitoring
- L176 _private member_ `EBlackmagicMediaSourceColorFormat BlackmagicColorFormat = EBlackmagicMediaSourceColorFormat::YUV8;` — Blackmagic media source color format.
- L179 _private member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> BlackmagicColorSettings;` — Container for local media source color setting overrides.

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace BlackmagicMediaPlayerHelpers`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMedia/Private/Shared/BlackmagicMediaAllowPlatformTypes.h` (Private)


#### Free symbols / members of external scopes

- L4 _macro_ `#define BLACKMAGIC_PLATFORM_TYPES_GUARD`
- L13 _macro_ `#define DWORD ::DWORD`
- L14 _macro_ `#define FLOAT ::FLOAT`
- L17 _macro_ `#define TRUE 1`
- L21 _macro_ `#define FALSE 0`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMedia/Private/Shared/BlackmagicMediaHidePlatformTypes.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMedia/Public/BlackmagicCustomTimeStep.h` (Public)


#### class `UBlackmagicCustomTimeStep`  
`class UBlackmagicCustomTimeStep : public UGenlockedCustomTimeStep`  
_L20-59_
- reflection: `UCLASS(Blueprintable, editinlinenew, meta=(DisplayName="Blackmagic SDI Input", MediaIOCustomLayout="Blackmagic"))`
- inherits: `UGenlockedCustomTimeStep`
- desc: Control the Engine TimeStep via the Blackmagic Design card.
- L26 _public prototype_ `virtual bool Initialize(class UEngine* InEngine) override;`
- L27 _public prototype_ `virtual void Shutdown(class UEngine* InEngine) override;`
- L28 _public prototype_ `virtual bool UpdateTimeStep(class UEngine* InEngine) override;`
- L29 _public prototype_ `virtual ECustomTimeStepSynchronizationState GetSynchronizationState() const override;`
- L30 _public prototype_ `virtual FFrameRate GetFixedFrameRate() const override;`
- L33 _public prototype_ `virtual uint32 GetLastSyncCountDelta() const override;`
- L34 _public prototype_ `virtual bool IsLastSyncDataValid() const override;`
- L35 _public prototype_ `virtual FFrameRate GetSyncRate() const override;`
- L36 _public prototype_ `virtual bool WaitForSync() override;`
- L37 _public function_ `virtual bool SupportsFormatAutoDetection() const`
- L40 _public prototype_ `virtual void BeginDestroy() override;`
- L43 _private prototype_ `void ReleaseResources();`
- L48 _public member_ `FMediaIOConfiguration MediaConfiguration;` — `UPROPERTY(EditAnywhere, Category="Genlock", meta=(DisplayName="Configuration"))` — The device, port and video settings that correspond to where the Genlock signal will be coming from
- L52 _public member_ `bool bEnableOverrunDetection;` — `UPROPERTY(EditAnywhere, Category="Genlock options", meta=(DisplayName="Display Dropped Frames Warning"))` — Enable mechanism to detect Engine loop overrunning the source
- L56 _private member_ `BlackmagicCustomTimeStepHelpers::FInputEventCallback* InputEventCallback;`
- L58 _private member_ `bool bWarnedAboutVSync;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BlackmagicCustomTimeStepHelpers`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMedia/Public/BlackmagicDeviceProvider.h` (Public)


#### enum `EBlackmagicMediaTimecodeFormat`  
`enum class EBlackmagicMediaTimecodeFormat : uint8`  
_L15-20_
- reflection: `UENUM()`
- desc: Available timecode formats that Blackmagic support.
- L17 _public enumerator_ `None`
- L18 _public enumerator_ `LTC`
- L19 _public enumerator_ `VITC`

#### class `FBlackmagicDeviceProvider`  
`class FBlackmagicDeviceProvider : public IMediaIOCoreDeviceProvider`  
_L25-61_
- inherits: `IMediaIOCoreDeviceProvider`
- desc: Implementation of IMediaIOCoreDeviceProvider for Blackmagic
- L28 _public prototype_ `static FName GetProviderName();`
- L29 _public prototype_ `static FName GetProtocolName();`
- L32 _public prototype_ `virtual FName GetFName() override;`
- L34 _public prototype_ `virtual TArray<FMediaIOConnection> GetConnections() const override;`
- L35 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations() const override;`
- L36 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations(bool bAllowInput, bool bAllowOutput) const override;`
- L37 _public prototype_ `virtual TArray<FMediaIODevice> GetDevices() const override;`
- L38 _public prototype_ `virtual TArray<FMediaIOMode> GetModes(const FMediaIODevice& InDevice, bool bInOutput) const override;`
- L39 _public prototype_ `virtual TArray<FMediaIOInputConfiguration> GetInputConfigurations() const override;`
- L40 _public prototype_ `virtual TArray<FMediaIOOutputConfiguration> GetOutputConfigurations() const override;`
- L41 _public prototype_ `virtual TArray<FMediaIOVideoTimecodeConfiguration> GetTimecodeConfigurations() const override;`
- L43 _public prototype_ `virtual FMediaIOConfiguration GetDefaultConfiguration() const override;`
- L44 _public prototype_ `virtual FMediaIOMode GetDefaultMode() const override;`
- L45 _public prototype_ `virtual FMediaIOInputConfiguration GetDefaultInputConfiguration() const override;`
- L46 _public prototype_ `virtual FMediaIOOutputConfiguration GetDefaultOutputConfiguration() const override;`
- L47 _public prototype_ `virtual FMediaIOVideoTimecodeConfiguration GetDefaultTimecodeConfiguration() const override;`
- L49 _public prototype_ `virtual UMediaSource* CreateMediaSource(const FMediaIOConfiguration& InConfiguration, UObject* Outer) const override;`
- L52 _public prototype_ `virtual FText ToText(const FMediaIOConfiguration& InConfiguration, bool bInIsAutoDetected = false) const override;`
- L53 _public prototype_ `virtual FText ToText(const FMediaIOConnection& InConnection) const override;`
- L54 _public prototype_ `virtual FText ToText(const FMediaIOOutputConfiguration& InConfiguration) const override;`
- L57 _public function_ `virtual bool ShowInputTransportInSelector() const override`
- L58 _public function_ `virtual bool ShowInputKeyInSelector() const override`
- L59 _public function_ `virtual bool ShowOutputKeyInSelector() const override`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMedia/Public/BlackmagicMediaDefinitions.h` (Public)


#### enum `EBlackmagicHDRMetadataEOTF`  
`enum class EBlackmagicHDRMetadataEOTF : uint8`  
_L18-24_
- reflection: `UENUM()`
- desc: HDR Transfer function. Must match Blackmagic::EBlackmagicHDRMetadataEOTF.
- L20 _public enumerator_ `SDR`
- L21 _public enumerator_ `HDR`
- L22 _public enumerator_ `PQ`
- L23 _public enumerator_ `HLG`

#### enum `EBlackmagicHDRMetadataGamut`  
`enum class EBlackmagicHDRMetadataGamut : uint8`  
_L31-35_
- reflection: `UENUM()`
- desc: HDR Color Gamut. Must match Blackmagic::EBlackmagicHDRMetadataGamut.
- L33 _public enumerator_ `Rec709`
- L34 _public enumerator_ `Rec2020`

#### struct `FBlackmagicMediaHDROptions`  
`struct FBlackmagicMediaHDROptions`  
_L41-52_
- reflection: `USTRUCT()`
- desc: Set of metadata describing a HDR video signal.
- L47 _public member_ `EBlackmagicHDRMetadataEOTF EOTF = EBlackmagicHDRMetadataEOTF::SDR;` — `UPROPERTY(EditAnywhere, Category = "HDR")` — Transfer function to use for converting the video signal to an optical signal.
- L51 _public member_ `EBlackmagicHDRMetadataGamut Gamut = EBlackmagicHDRMetadataGamut::Rec709;` — `UPROPERTY(EditAnywhere, Category = "HDR")` — The color gamut of the video signal.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BlackmagicDesign`
- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace BlackmagicMedia` (scope `UE`)
- L57 _prototype_ `FBlackmagicMediaHDROptions MakeBlackmagicMediaHDROptions(const BlackmagicDesign::FHDRMetaData& HDROptions);` (scope `UE::BlackmagicMedia`) — Create Blackmagic HDR UStruct from the BlackmagicLib's hdr struct.
- L59 _prototype_ `BlackmagicDesign::FHDRMetaData MakeBlackmagicHDROptions(const FBlackmagicMediaHDROptions& HDROptions);` (scope `UE::BlackmagicMedia`) — Create BlackmagicLib's hdr struct from the Blackmagic HDR UStruct.

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMedia/Public/BlackmagicMediaSource.h` (Public)


#### enum `EBlackmagicMediaSourceColorFormat`  
`enum class EBlackmagicMediaSourceColorFormat : uint8`  
_L17-21_
- reflection: `UENUM()`
- desc: Native data format.
- L19 _public enumerator_ `YUV8 UMETA(DisplayName = "8bit YUV")`
- L20 _public enumerator_ `YUV10 UMETA(DisplayName = "10bit YUV")`

#### enum `EBlackmagicMediaAudioChannel`  
`enum class EBlackmagicMediaAudioChannel : uint8`  
_L27-31_
- reflection: `UENUM(BlueprintType)`
- desc: Available number of audio channel supported by Unreal Engine & Capture card.
- L29 _public enumerator_ `Stereo2`
- L30 _public enumerator_ `Surround8`

#### class `UBlackmagicMediaSource`  
`class UBlackmagicMediaSource : public UCaptureCardMediaSource`  
_L37-143_
- reflection: `UCLASS(BlueprintType, hideCategories=(Platforms,Object), PrioritizeCategories=(Blackmagic, Video, ColorManagement, Audio, Ancillary, Synchronization, Debug), meta=(MediaIOCustomLayout="Blackmagic"))`
- inherits: `UCaptureCardMediaSource`
- desc: Media source description for Blackmagic.
- L44 _public prototype_ `UBlackmagicMediaSource();` — Default constructor.
- L50 _public member_ `FMediaIOConfiguration MediaConfiguration;` — `UPROPERTY(EditAnywhere, Category="Blackmagic", meta=(DisplayName="Configuration"))` — The device, port and video settings that correspond to the input.
- L56 _public member_ `EMediaIOTimecodeFormat TimecodeFormat_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))` — Use the time code embedded in the input stream.
- L61 _public member_ `EMediaIOAutoDetectableTimecodeFormat AutoDetectableTimecodeFormat = EMediaIOAutoDetectableTimecodeFormat::Auto;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Blackmagic")` — Use the time code embedded in the input stream.
- L65 _public member_ `bool bCaptureAudio;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Audio")` — Capture Audio from the Blackmagic source.
- L69 _public member_ `EBlackmagicMediaAudioChannel AudioChannels;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Audio, meta=(EditCondition="bCaptureAudio"))` — Desired number of audio channel to capture.
- L73 _public member_ `int32 MaxNumAudioFrameBuffer;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category="Audio", meta=(EditCondition="bCaptureAudio", ClampMin="1", ClampMax="32"))` — Maximum number of audio frames to buffer.
- L78 _public member_ `bool bCaptureVideo;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Video")` — Capture Video from the Blackmagic source.
- L82 _public member_ `EBlackmagicMediaSourceColorFormat ColorFormat;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Video", meta=(EditCondition="bCaptureVideo"))` — Native data format internally used by the device after being converted from SDI/HDMI signal.
- L91 _public member_ `bool bIsSRGBInput_DEPRECATED = false;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage = "Use ColorEncoding instead."))` — Whether the video input is in sRGB color space. A sRGB to Linear conversion will be applied resulting in a texture in linear space. @Note If the texture is not in linear space, it won't look correct in the editor. Another pass will be required either through Composure or other means.
- L96 _public member_ `int32 MaxNumVideoFrameBuffer;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category="Video", meta=(EditCondition="bCaptureVideo", ClampMin="1", ClampMax="32"))` — Maximum number of video frames to buffer.
- L101 _public member_ `bool bLogDropFrame;` — `UPROPERTY(EditAnywhere, Category="Debug")` — Log a warning when there's a drop frame.
- L108 _public member_ `bool bEncodeTimecodeInTexel;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Debug", meta = (DisplayName = "Burn Frame Timecode"))` — Burn Frame Timecode in the input texture without any frame number clipping. @Note Only supported in progressive format.
- L112 _public function_ `virtual bool SupportsFormatAutoDetection() const`
- L116 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const override;`
- L117 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const override;`
- L118 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const override;`
- L119 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
- L124 _public prototype_ `virtual FString GetUrl() const override;`
- L125 _public prototype_ `virtual bool Validate() const override;`
- L128 _public prototype_ `virtual FString GetDescriptionString() const override;`
- L129 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`
- L133 _public prototype_ `void AssignDefaultConfiguration();` — Assigns a default configuration (The first one in the list of configurations).
- L138 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L139 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L141 _public prototype_ `virtual void PostLoad() override;`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMedia/Public/BlackmagicTimecodeProvider.h` (Public)


#### class `UBlackmagicTimecodeProvider`  
`class UBlackmagicTimecodeProvider : public UGenlockedTimecodeProvider`  
_L20-81_
- reflection: `UCLASS(Blueprintable, editinlinenew, meta=(DisplayName="Blackmagic SDI Input", MediaIOCustomLayout="Blackmagic"))`
- inherits: `UGenlockedTimecodeProvider`
- desc: Class to fetch a timecode via a Blackmagic Design card.
- L25 _public prototype_ `UBlackmagicTimecodeProvider();`
- L28 _public prototype_ `virtual bool FetchTimecode(FQualifiedFrameTime& OutFrameTime) override;`
- L29 _public prototype_ `virtual ETimecodeProviderSynchronizationState GetSynchronizationState() const override;`
- L30 _public prototype_ `virtual bool Initialize(class UEngine* InEngine) override;`
- L31 _public prototype_ `virtual void Shutdown(class UEngine* InEngine) override;`
- L34 _public function_ `virtual bool SupportsAutoDetected() const override`
- L39 _public function_ `virtual void SetIsAutoDetected(bool bInIsAutoDetected) override`
- L44 _public function_ `virtual bool IsAutoDetected() const override`
- L50 _public prototype_ `virtual void BeginDestroy() override;`
- L51 _public prototype_ `virtual void PostLoad() override;`
- L54 _private prototype_ `void ReleaseResources();`
- L61 _public member_ `FMediaIOConfiguration MediaConfiguration_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))` — The device, port and video settings that correspond to the input.
- L67 _public member_ `EMediaIOTimecodeFormat TimecodeFormat_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))` — Timecode format to read from a video signal.
- L73 _public member_ `FMediaIOVideoTimecodeConfiguration TimecodeConfiguration;` — `UPROPERTY(EditAnywhere, Category = "Blackmagic")` — Timecode format to read from a video signal.
- L76 _public member_ `bool bAutoDetectTimecode = true;` — `UPROPERTY()`
- L80 _private member_ `BlackmagicTimecodeProviderHelpers::FEventCallback* EventCallback;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BlackmagicTimecodeProviderHelpers`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMedia/Public/IBlackmagicMediaModule.h` (Public)


#### class `IBlackmagicMediaModule`  
`class IBlackmagicMediaModule : public IModuleInterface`  
_L16-41_
- inherits: `IModuleInterface`
- desc: Interface for the Media module.
- L20 _public function_ `static inline IBlackmagicMediaModule& Get()`
- L31 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Create an Blackmagic based media player. @param EventSink The object that receives media events from the player. @return A new media player, or nullptr if a player couldn't be created.
- L34 _public prototype_ `virtual TSharedPtr<FSlateStyleSet> GetStyle() = 0;` — @return SlateStyleSet to be used across the BlackmagicMedia module
- L37 _public prototype_ `virtual bool IsInitialized() const = 0;` — @return true if the Blackmagic module and VideoIO.dll could be loaded
- L40 _public prototype_ `virtual bool CanBeUsed() const = 0;` — @return true if the Blackmagic card can be used
