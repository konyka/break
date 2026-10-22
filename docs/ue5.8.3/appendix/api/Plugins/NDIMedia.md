# Plugins / NDIMedia

- module root: `Plugins/Media/NDIMedia/Source/NDIMedia`
- headers: 20; symbols: 362
- symbol kinds: class=14, delegate=8, enum=5, enumerator=17, function=18, macro=1, member=130, namespace=5, prototype=148, struct=3, typedef=2, variable=11
- PrivateDependencyModuleNames: CoreUObject, DeveloperSettings, Engine, MediaIOCore, MediaUtils, NDIMediaRendering, NDISDK, OpenColorIO, Projects, RHI, RenderCore, Slate, SlateCore, TimeManagement, UnrealEd, XmlParser
- PublicDependencyModuleNames: Core, MediaAssets, MediaIOCore

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/NDIDeviceProvider.h` (Private)


#### class `FNDIDeviceProvider`  
`class FNDIDeviceProvider : public IMediaIOCoreDeviceProvider`  
_L20-55_
- inherits: `IMediaIOCoreDeviceProvider`
- desc: Implementation of IMediaIOCoreDeviceProvider for UNDIMediaSource "device" enumeration.
- L23 _public prototype_ `static FName GetProviderName();`
- L24 _public prototype_ `static FName GetProtocolName();`
- L27 _public prototype_ `virtual FName GetFName() override;`
- L29 _public prototype_ `virtual TArray<FMediaIOConnection> GetConnections() const override;`
- L30 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations() const override;`
- L31 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations(bool bInAllowInput, bool bInAllowOutput) const override;`
- L32 _public prototype_ `virtual TArray<FMediaIODevice> GetDevices() const override;`
- L33 _public prototype_ `virtual TArray<FMediaIOMode> GetModes(const FMediaIODevice& InDevice, bool bInOutput) const override;`
- L34 _public prototype_ `virtual TArray<FMediaIOInputConfiguration> GetInputConfigurations() const override;`
- L35 _public prototype_ `virtual TArray<FMediaIOOutputConfiguration> GetOutputConfigurations() const override;`
- L36 _public prototype_ `virtual TArray<FMediaIOVideoTimecodeConfiguration> GetTimecodeConfigurations() const override;`
- L38 _public prototype_ `virtual FMediaIOConfiguration GetDefaultConfiguration() const override;`
- L39 _public prototype_ `virtual FMediaIOMode GetDefaultMode() const override;`
- L40 _public prototype_ `virtual FMediaIOInputConfiguration GetDefaultInputConfiguration() const override;`
- L41 _public prototype_ `virtual FMediaIOOutputConfiguration GetDefaultOutputConfiguration() const override;`
- L42 _public prototype_ `virtual FMediaIOVideoTimecodeConfiguration GetDefaultTimecodeConfiguration() const override;`
- L44 _public prototype_ `virtual FText ToText(const FMediaIOConfiguration& InConfiguration, bool bInIsAutoDetected = false) const override;`
- L45 _public prototype_ `virtual FText ToText(const FMediaIOConnection& InConnection) const override;`
- L46 _public prototype_ `virtual FText ToText(const FMediaIOOutputConfiguration& InConfiguration) const override;`
- L49 _public function_ `virtual bool ShowInputTransportInSelector() const override`
- L50 _public function_ `virtual bool ShowInputKeyInSelector() const override`
- L51 _public function_ `virtual bool ShowOutputKeyInSelector() const override`

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/NDIMediaAPI.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/NDIMediaLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNDIMedia, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNDIMedia, Log, All);`

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/NDIMediaModule.h` (Private)


#### class `FNDIMediaRuntimeLibrary`  
`class FNDIMediaRuntimeLibrary`  
_L21-43_
- desc: Wrapper for the loaded NDI runtime library.
- L24 _public prototype_ `FNDIMediaRuntimeLibrary(const FString& InLibraryPath);`
- L25 _public prototype_ `~FNDIMediaRuntimeLibrary();`
- L27 _public function_ `bool IsLoaded() const`
- L33 _public member_ `const NDIlib_v5* Lib = nullptr;` — Dynamically loaded function pointers for the NDI lib API.
- L36 _public member_ `void* LibHandle = nullptr;` — Handle to the NDI runtime dll.
- L39 _public member_ `FString LibraryPath;` — Path the library was loaded from.
- L42 _public member_ `TSet<FString> Senders;` — Keep track of senders being created to detect source collisions and provide better error messages.

#### class `FNDIMediaModule`  
`class FNDIMediaModule : public IModuleInterface, public IMediaPlayerFactory`  
_L45-118_
- inherits: `IModuleInterface,IMediaPlayerFactory`
- L49 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L50 _public prototype_ `virtual void ShutdownModule() override;`
- L53 _public function_ `static FNDIMediaModule* Get()` — Returns the module, if loaded or null otherwise
- L62 _public function_ `static TSharedPtr<FNDIMediaRuntimeLibrary> GetNDIRuntimeLibrary()` — Returns a handle to the currently loaded NDI runtime library. Objects holding runtime resources should also keep a ref on the library.
- L72 _public prototype_ `TSharedPtr<FNDISourceFinder> GetFindInstance();` — Returns NDI source find instance.
- L75 _public function_ `TSharedPtr<FNDIDeviceProvider> GetDeviceProvider() const` — Access the ndi device provider
- L81 _public function_ `FNDIStreamReceiverManager& GetStreamReceiverManager() const` — Access the ndi stream receiver manager.
- L87 _public prototype_ `virtual bool CanPlayUrl(const FString& Url, const IMediaOptions* Options, TArray<FText>* OutWarnings, TArray<FText>* OutErrors) const override;`
- L88 _public prototype_ `virtual int32 GetPlayabilityConfidenceScore(const FString& Url, const IMediaOptions* Options, TArray<FText>* OutWarnings, TArray<FText>* OutErrors) const override;`
- L89 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& InEventSink) override;`
- L90 _public prototype_ `virtual FText GetDisplayName() const override;`
- L91 _public prototype_ `virtual FName GetPlayerName() const override;`
- L92 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L93 _public prototype_ `virtual const TArray<FString>& GetSupportedPlatforms() const override;`
- L94 _public prototype_ `virtual bool SupportsFeature(EMediaFeature Feature) const override;`
- L97 _public member_ `static const FGuid PlayerPluginGUID;`
- L100 _private prototype_ `bool LoadModuleDependencies();`
- L103 _private prototype_ `void OnNDIMediaSettingsChanged(UObject* InSettings, struct FPropertyChangedEvent& InPropertyChangedEvent);`
- L104 _private prototype_ `void OnRuntimeLibrarySettingsChanged(const UNDIMediaSettings* InSettings);`
- L107 _private member_ `TSharedPtr<FNDIMediaRuntimeLibrary> NDILib;`
- L110 _private member_ `TArray<FString> SupportedPlatforms;` — List of platforms that the media player support.
- L113 _private member_ `TArray<FString> SupportedUriSchemes;` — List of supported URI schemes.
- L115 _private member_ `TSharedPtr<FNDISourceFinder> FindInstance;`
- L116 _private member_ `TSharedPtr<FNDIDeviceProvider> DeviceProvider;`
- L117 _private member_ `TSharedPtr<FNDIStreamReceiverManager> StreamReceiverManager;`

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/NDISourceFinder.h` (Private)


#### class `FNDISourceFinder`  
`class FNDISourceFinder`  
_L12-39_
- desc: Wrapper for the NDI source finder instance.
- L15 _public prototype_ `FNDISourceFinder(const TSharedPtr<FNDIMediaRuntimeLibrary>& InNdiLib);`
- L16 _public prototype_ `~FNDISourceFinder();`
- L19 _public prototype_ `void Validate(const TSharedPtr<FNDIMediaRuntimeLibrary>& InNdiLib);` — Call prior to doing other calls to ensure the runtime lib is up to date.
- L29 _public prototype_ `TArray<FNDISourceInfo> GetSources() const;` — Returns current list of sources discovered on the network.
- L32 _private prototype_ `void Create();`
- L33 _private prototype_ `void Destroy();`
- L36 _private member_ `TSharedPtr<FNDIMediaRuntimeLibrary> NdiLib;`
- L37 _private member_ `NDIlib_find_instance_t FindInstance = nullptr;`
- L38 _private member_ `mutable FCriticalSection FindSyncContext;`

#### struct `FNDISourceFinder::FNDISourceInfo`  
`struct FNDISourceInfo`  
_L22-26_
- desc: NDI Source information
- L24 _public member_ `FString Name;`
- L25 _public member_ `FString Url;`

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/Player/NDIMediaHdrValidation.h` (Private)


#### Free symbols / members of external scopes

- L13 _macro_ `#define NDI_MEDIA_HDR_VALIDATION_TEST 0`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace NDIMediaStreamPlayer` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::NDIMediaStreamPlayer`)
- L19 _function_ `inline const TCHAR* EncodingToString(UE::Color::EEncoding InEncoding)` (scope `UE::NDIMediaStreamPlayer::Private`)
- L33 _function_ `inline FString ColorSpaceToString(const UE::Color::FColorSpace& InColorSpace)` (scope `UE::NDIMediaStreamPlayer::Private`)
- L52 _function_ `inline const TCHAR* FourCCToString(const int32 InFourCC)` (scope `UE::NDIMediaStreamPlayer::Private`)

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/Player/NDIMediaReceiverPerformanceData.h` (Private)


#### struct `FNDIMediaReceiverPerformanceData`  
`struct FNDIMediaReceiverPerformanceData`  
_L11-48_
- reflection: `USTRUCT(BlueprintType)`
- desc: NDI receiver's performance statistics on number of frames received and dropped.
- L18 _public member_ `int64 VideoFrames = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Information")` — The number of video frames received
- L22 _public member_ `int64 DroppedVideoFrames = 0;` — `UPROPERTY(BlueprintReadonly, VisibleAnywhere, Category = "Information")` — The number of video frames dropped
- L26 _public member_ `int64 AudioFrames = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Information")` — The number of audio frames received
- L30 _public member_ `int64 DroppedAudioFrames = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Information")` — The number of audio frames dropped
- L34 _public member_ `int64 MetadataFrames = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Information")` — The number of metadata frames received
- L38 _public member_ `int64 DroppedMetadataFrames = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Information")` — The number of metadata frames dropped
- L41 _public function_ `bool operator==(const FNDIMediaReceiverPerformanceData& other) const` — Compares this object to 'other' and returns a determination of whether they are equal

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/Player/NDIMediaSourceOptions.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NDIMediaSourceOptions` (scope `UE`)
- L10 _variable_ `static const FLazyName DeviceName("Dev` (scope `UE::NDIMediaSourceOptions`)
- L11 _variable_ `static const FLazyName Bandwidth("Ban` (scope `UE::NDIMediaSourceOptions`)
- L12 _variable_ `static const FLazyName SyncTimecodeToSource("Syn` (scope `UE::NDIMediaSourceOptions`)
- L13 _variable_ `static const FLazyName LogDropFrame("Log` (scope `UE::NDIMediaSourceOptions`)
- L14 _variable_ `static const FLazyName EncodeTimecodeInTexel("Enc` (scope `UE::NDIMediaSourceOptions`)
- L15 _variable_ `static const FLazyName CaptureAudio("Cap` (scope `UE::NDIMediaSourceOptions`)
- L16 _variable_ `static const FLazyName CaptureVideo("Cap` (scope `UE::NDIMediaSourceOptions`)
- L17 _variable_ `static const FLazyName CaptureAncillary("Cap` (scope `UE::NDIMediaSourceOptions`)
- L18 _variable_ `static const FLazyName MaxVideoFrameBuffer("Max` (scope `UE::NDIMediaSourceOptions`)
- L19 _variable_ `static const FLazyName MaxAudioFrameBuffer("Max` (scope `UE::NDIMediaSourceOptions`)
- L20 _variable_ `static const FLazyName MaxAncillaryFrameBuffer("Max` (scope `UE::NDIMediaSourceOptions`)

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/Player/NDIMediaStreamPlayer.h` (Private)


#### class `FNDIMediaStreamPlayer`  
`class FNDIMediaStreamPlayer : public FMediaIOCorePlayerBase`  
_L19-160_
- inherits: `FMediaIOCorePlayerBase`
- desc: Implementation of the Media player for an NDI stream.
- L21 _private typedef_ `using Super = FMediaIOCorePlayerBase;`
- L24 _public prototype_ `FNDIMediaStreamPlayer(IMediaEventSink& InEventSink);`
- L29 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L30 _public prototype_ `virtual bool Open(const FString& InUrl, const IMediaOptions* InOptions) override;`
- L31 _public prototype_ `virtual void Close() override;`
- L32 _public prototype_ `virtual FString GetStats() const override;`
- L33 _public prototype_ `virtual void TickInput(FTimespan InDeltaTime, FTimespan InTime) override;`
- L34 _public prototype_ `virtual void TickFetch(FTimespan InDeltaTime, FTimespan InTime) override;`
- L40 _public prototype_ `bool HasVideoSamplesWithCustomConverter() const;` — Inspects the pending NDI video samples to determine if they have a custom converter.
- L44 _protected prototype_ `virtual bool IsHardwareReady() const override;`
- L45 _protected prototype_ `virtual void SetupSampleChannels() override;`
- L46 _protected prototype_ `virtual uint32 GetNumVideoFrameBuffers() const override;`
- L47 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> AcquireTextureSample_AnyThread() const override;`
- L48 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleConverter> CreateTextureSampleConverter() const override;`
- L51 _protected function_ `virtual FString GetAnalyticsEventPrefix() const override`
- L52 _protected prototype_ `virtual void GetAnalyticsEventAttributes(const FString& EventName, TArray<FAnalyticsEventAttribute>& InOutAttributes) const override;`
- L53 _protected function_ `virtual bool ShouldAutoRecordSourceOpenedEvent() const override`
- L60 _public prototype_ `virtual const FSlateBrush* GetDisplayIcon() const override;`
- L66 _private prototype_ `void OnOptionsChanged(UObject* InOptions, FPropertyChangedEvent& InPropertyChanged);`
- L70 _private prototype_ `void HandleVideoFrameReceived(FNDIStreamReceiver* InReceiver, const NDIlib_video_frame_v2_t& InVideoFrame, const FTimespan& InTime);` — Callback handler for video frame reception.
- L73 _private prototype_ `void HandleAudioFrameReceived(FNDIStreamReceiver* InReceiver, const NDIlib_audio_frame_v2_t& InAudioFrame, const FTimespan& InTime);` — Callback handler for audio frame reception.
- L76 _private prototype_ `void HandleMetaDataReceived(FNDIStreamReceiver* InReceiver, FString InData, bool bInAttachedToVideoFrame);` — Callback handler for metadata reception.
- L78 _private prototype_ `void VerifyFrameDropCount();`
- L81 _private prototype_ `void UpdateNdiColorSettings();` — Update the color settings resulting from Ndi setting + media source overrides.
- L84 _private prototype_ `void ApplyNdiColorMetadata(const FString& InData);` — Parse and apply stream color metadata received from NDI.
- L87 _private prototype_ `void ClearNdiColorMetadata();` — Clear stream-derived color metadata.
- L91 _private member_ `FObjectKey OptionsObject;` — Keep track of the options (media source) object this player was opened with to filter global events.
- L94 _private member_ `bool bIsReopening = false;` — Indicate if currently in a reopening sequence.
- L98 _private member_ `bool bHasRecordedSourceOpenedEvent = false;` — One-shot guard so the source-opened analytics event fires at most once per open.
- L102 _private member_ `int32 MaxNumAudioFrameBuffer = 0;` — Maximum Audio Sample Pool size
- L105 _private member_ `int32 MaxNumMetadataFrameBuffer = 0;` — Maximum Metadata Sample Pool size
- L108 _private member_ `int32 MaxNumVideoFrameBuffer = 0;` — Maximum Video Sample Pool size
- L111 _private member_ `bool bCaptureVideo = true;` — Determines which of the sample streams to capture (mirrors MediaSource).
- L112 _private member_ `bool bCaptureAudio = false;`
- L113 _private member_ `bool bCaptureAncillary = false;`
- L116 _private member_ `bool bEncodeTimecodeInTexel = false;` — Whether to use the time code embedded in video frames.
- L119 _private member_ `EMediaIOSampleType SupportedSampleTypes = EMediaIOSampleType::None;` — Used to flag which sample types we advertise as supported for timed data monitoring
- L122 _private member_ `EMediaState NDIPlayerState = EMediaState::Closed;` — Current state of the media player.
- L125 _private member_ `uint32 NDIThreadAudioChannels = 0;` — Number of channels from the last audio frame received.
- L128 _private member_ `uint32 NDIThreadAudioSampleRate = 0;` — Sample rate from the last audio frame received.
- L131 _private member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> NdiColorSettings;` — Container for local stream color settings.
- L134 _private member_ `IMediaEventSink& EventSink;` — The media event sink.
- L137 _private member_ `TSharedPtr<FNDIStreamReceiver> Receiver;` — Current stream receiver
- L140 _private member_ `FDelegateHandle VideoReceivedHandle;` — Handles for the receiver delegates
- L141 _private member_ `FDelegateHandle AudioReceivedHandle;`
- L142 _private member_ `FDelegateHandle MetadataReceivedHandle;`
- L143 _private member_ `FDelegateHandle ConnectedHandle;`
- L144 _private member_ `FDelegateHandle DisconnectedHandle;`
- L147 _private member_ `mutable FCriticalSection MetadataColorSyncContext;` — Protects stream color metadata values when metadata is received from another thread.
- L150 _private member_ `UE::Color::EEncoding StreamEncodingOverride = UE::Color::EEncoding::None;` — Latest stream-derived color metadata interpreted from NDI metadata packets.
- L151 _private member_ `TOptional<UE::Color::FColorSpace> StreamColorSpaceOverride;`
- L154 _private member_ `FString LastAppliedMetadata;` — Last metadata blob fed to ApplyNdiColorMetadata; used to skip re-parsing identical frame-attached metadata.
- L157 _private member_ `TUniquePtr<FNDIMediaTextureSamplePool> TextureSamplePool;` — Media Sample pools
- L158 _private member_ `TUniquePtr<FNDIMediaAudioSamplePool> AudioSamplePool;`
- L159 _private member_ `TUniquePtr<FNDIMediaBinarySamplePool> MetadataSamplePool;`

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/Player/NDIMediaTextureSample.h` (Private)


#### class `FNDIMediaTextureSample`  
`class FNDIMediaTextureSample : public FMediaIOCoreTextureSampleBase`  
_L13-77_
- inherits: `FMediaIOCoreTextureSampleBase`
- desc: Implements a media texture sample for NDIMedia.
- L15 _private typedef_ `using Super = FMediaIOCoreTextureSampleBase;`
- L42 _public prototype_ `virtual FMatrix44f GetSampleToRGBMatrix() const override;`
- L44 _public prototype_ `virtual IMediaTextureSampleConverter* GetMediaTextureSampleConverter() override;`
- L49 _public prototype_ `void CopyConfiguration(const TSharedPtr<FMediaIOCoreTextureSampleBase>& SourceSample) override;`
- L50 _public prototype_ `virtual void FreeSample() override;`
- L61 _public prototype_ `bool Initialize(const NDIlib_video_frame_v2_t& InVideoFrame, TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> InSourceColorSettings, const FTimespan& InTime, const TOptional<FTimecode>& InTimecode);` — Initialize the sample. @param InVideoFrame Received Video frame data from NDI. @param InSourceColorSettings Information about the texture color encoding and color space. @param InTime Current playback time of the sample. @return true if the sample was correctly initialized, false otherwise.
- L64 _public member_ `bool bIsProgressive = true;` — Progressive vs Interlaced.
- L67 _public member_ `int32 FieldIndex = 0;` — If interlaced, which field.
- L70 _public member_ `bool bIsCustomFormat = false;` — Needs a custom conversion.
- L73 _public member_ `ECustomConversionMode CustomConversionMode = ECustomConversionMode::None;` — Custom conversion path to use for the current sample.
- L76 _public member_ `TSharedPtr<FNDIMediaTextureSampleConverter> CustomConverter;` — Custom converter.

#### enum `FNDIMediaTextureSample::ECustomConversionMode`  
`enum class ECustomConversionMode : uint8`  
_L26-39_
- desc: Selects which pixel shader FNDIMediaTextureSampleConverter dispatches for this sample. Formats that the base media pipeline already handles (UYVY, BGRA, RGBA/RGBX) use ECustomConversionMode::None and go through the default IMediaTextureSample path; no custom converter is involved. The modes below identify the NDI FourCCs that require NDIMedia-specific shaders (alpha plane layouts and 16-bit YUV).
- L29 _public enumerator_ `None` — No custom conversion; sample is rendered by the base media shader path.
- L32 _public enumerator_ `UYVA8` — NDI FourCC 'UYVA': 8-bit UYVY plane followed by an 8-bit alpha plane. Converted by FNDIMediaShaderUYVAtoBGRAPS.
- L35 _public enumerator_ `P216` — NDI FourCC 'P216': 16-bit 4:2:2 two-plane (Y + interleaved UV). Converted by FNDIMediaShaderP216toBGRAPS.
- L38 _public enumerator_ `PA16` — NDI FourCC 'PA16': 16-bit 4:2:2 three-plane (Y + interleaved UV + A). Converted by FNDIMediaShaderPA16toBGRAPS.

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/Player/NDIMediaTextureSampleConverter.h` (Private)


#### class `FNDIMediaTextureSampleConverter`  
`class FNDIMediaTextureSampleConverter : public IMediaTextureSampleConverter`  
_L9-47_
- inherits: `IMediaTextureSampleConverter`
- L13 _public prototype_ `void Setup(const TSharedPtr<FNDIMediaTextureSample>& InSample);` — Configures settings to convert incoming sample
- L16 _public prototype_ `virtual uint32 GetConverterInfoFlags() const override;`
- L17 _public prototype_ `virtual bool Convert(FRHICommandListImmediate& InRHICmdList, FTextureRHIRef& InDstTexture, const FConversionHints& InHints) override;`
- L22 _private prototype_ `bool UpdateInputTextures(FRHICommandList& InRHICmdList, const TSharedPtr<FNDIMediaTextureSample>& InSample);` — Prepare the input textures from the sample buffer.
- L25 _private member_ `TWeakPtr<FNDIMediaTextureSample> SampleWeak;` — Keep a reference to the sample to retrieve frame info and buffer.
- L28 _private member_ `FIntPoint PreviousFrameSize = FIntPoint(0, 0);` — Cache the last frame size of the texture objects.
- L31 _private member_ `uint8 PreviousConversionMode = 0;` — Cache the previous conversion mode (FNDIMediaTextureSample::ECustomConversionMode as uint8).
- L34 _private member_ `FTextureRHIRef SourceYUVTexture;` — Source texture for UYVA converter path.
- L37 _private member_ `FTextureRHIRef SourceAlphaTexture;` — Source alpha texture for UYVA converter path.
- L40 _private member_ `FTextureRHIRef SourceYTexture;` — Source luma texture for P216/PA16 converter paths.
- L43 _private member_ `FTextureRHIRef SourceUVTexture;` — Source chroma texture for P216/PA16 converter paths.
- L46 _private member_ `FTextureRHIRef SourceA16Texture;` — Source alpha texture for PA16 converter path.

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/Player/NDISourceSettings.h` (Private)


#### struct `FNDISourceSettings`  
`struct FNDISourceSettings`  
_L14-45_
- reflection: `USTRUCT(BlueprintType)`
- desc: Carries the NDI source and capture settings to the media receiver from either media source/player or timecode provider.
- L21 _public member_ `FString SourceName = FString("");` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Properties")` — NDI Source name
- L25 _public member_ `ENDIReceiverBandwidth Bandwidth = ENDIReceiverBandwidth::Highest;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Properties")` — Indicates the current bandwidth mode used for the connection to this source
- L29 _public member_ `bool bCaptureAudio = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Properties")` — Capture Audio from the NDI source.
- L33 _public member_ `bool bCaptureVideo = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Properties")` — Capture Video from the NDI source.
- L35 _public function_ `bool IsValid() const`
- L40 _public function_ `bool operator==(const FNDISourceSettings& InOther) const`

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/Player/NDIStreamReceiver.h` (Private)


#### class `FNDIStreamReceiver`  
`class FNDIStreamReceiver : public TSharedFromThis<FNDIStreamReceiver>`  
_L17-214_
- inherits: `TSharedFromThis<FNDIStreamReceiver>`
- desc: A Media object representing the NDI Receiver for being able to receive Audio, Video, and Metadata over an NDI stream.
- L20 _public prototype_ `explicit FNDIStreamReceiver(const TSharedPtr<FNDIMediaRuntimeLibrary>& InNdiLib);`
- L21 _public prototype_ `~FNDIStreamReceiver();`
- L37 _public prototype_ `bool Initialize(const FNDISourceSettings& InSourceSettings, ECaptureMode InCaptureMode);` — Initialize the stream receiver. If the source settings are valid, it will start the connection.
- L42 _public prototype_ `void StartConnection();` — Attempt to (re-)start the connection
- L47 _public prototype_ `void StopConnection();` — Stop the connection
- L52 _public prototype_ `void ChangeConnection(const FNDISourceSettings& InSourceSettings);` — Attempts to change the connection to another NDI sender source
- L55 _public prototype_ `int32 GetAudioChannels();` — Peek the audio stream to retrieve the number of audio channels.
- L58 _public prototype_ `void SetSyncTimecodeToSource(bool bInSyncTimecodeToSource);` — Sets whether the timecode should be synced to the Source Timecode value or the engine's.
- L64 _public prototype_ `void SendMetadataFrame(const FString& InData);` — This will send a metadata frame to the sender The data is expected to be valid XML
- L70 _public prototype_ `void SendMetadataFrameAttr(const FString& InElement, const FString& InElementData);` — This will send a metadata frame to the sender The data will be formatted as: <Element>ElementData</Element>
- L76 _public prototype_ `void SendMetadataFrameAttrs(const FString& InElement, const TMap<FString,FString>& InAttributes);` — This will send a metadata frame to the sender The data will be formatted as: <Element Key0="Value0" Key1="Value1" Keyn="Valuen"/>
- L81 _public prototype_ `void Shutdown();` — Attempts to immediately stop receiving frames.
- L88 _public prototype_ `bool FetchVideo(const FTimespan& InTime);` — Attempts to capture a frame from the connected source.  If a new frame is captured, broadcast it to interested receivers through the receive event.  Returns true if new data was captured. @param InTime Engine provided Sample time
- L89 _public prototype_ `bool FetchAudio(const FTimespan& InTime);`
- L90 _public prototype_ `bool FetchMetadata(const FTimespan& InTime);`
- L93 _public prototype_ `const FFrameRate& GetCurrentFrameRate() const;` — Returns the current framerate of the connected source
- L96 _public prototype_ `const FIntPoint& GetCurrentResolution() const;` — Returns the current resolution of the connected source
- L99 _public prototype_ `const FTimecode& GetCurrentTimecode() const;` — Returns the current timecode of the connected source
- L102 _public prototype_ `const FNDISourceSettings& GetCurrentSourceSettings() const;` — Returns the current connection information of the connected source
- L105 _public prototype_ `FNDIMediaReceiverPerformanceData GetPerformanceData() const;` — Returns the current performance data of the receiver while connected to the source
- L108 _public prototype_ `bool GetIsCurrentlyConnected() const;` — Returns a value indicating whether this object is currently connected to the sender source
- L111 _public function_ `FNDIMediaRuntimeLibrary* GetNdiLib() const` — Returns the current reference to the ndi runtime library used to create the receiver
- L120 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConnected, FNDIStreamReceiver*) FOnConnected OnConnected;` — Delegate called when the source is connected. @remark Called from the main thread.
- L127 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisconnected, FNDIStreamReceiver*) FOnDisconnected OnDisconnected;` — Delegate called when the source is disconnected @remark Called from the main thread.
- L131 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnVideoFrameReceived, FNDIStreamReceiver*, const NDIlib_video_frame_v2_t&, const FTimespan&) FOnVideoFrameReceived OnVideoFrameReceived;` — Delegate called when a video frame is received.
- L135 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnAudioFrameReceived, FNDIStreamReceiver*, const NDIlib_audio_frame_v2_t&, const FTimespan&) FOnAudioFrameReceived OnAudioFrameReceived;` — Delegate called when an audio frame is received.
- L139 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnMetadataFrameReceived, FNDIStreamReceiver*, const NDIlib_metadata_frame_t&, const FTimespan&) FOnMetadataFrameReceived OnMetadataFrameReceived;` — Delegate called when a metadata frame is received.
- L143 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnMetaDataReceived, FNDIStreamReceiver* , FString , bool );` — Delegate called when metadata is received (either from a metadata frame or attached to a video frame).
- L144 _public member_ `FOnMetaDataReceived OnMetaDataReceived;`
- L152 _private prototype_ `void SetIsCurrentlyConnected(bool bInConnected, bool bInDelayBroadcastEvents = true);` — Update the connection status and broadcast the events to delegates (OnConnected or OnDisconnected). @param bInConnected New connection status. @param bInDelayBroadcastEvents Broadcast events in game thread (if called from render thread).
- L155 _private prototype_ `void GatherPerformanceMetrics();` — Gathers the performance metrics of the connection to the remote source.
- L159 _private member_ `FTimecode Timecode;` — The current frame count, seconds, minutes, and hours in time-code notation
- L162 _private member_ `FFrameRate FrameRate;` — The desired number of frames (per second) for video to be displayed
- L165 _private member_ `FIntPoint Resolution;` — The width and height of the last received video frame
- L168 _private member_ `bool bSyncTimecodeToSource = true;` — Indicates whether the timecode should be synced to the Source Timecode value
- L171 _private member_ `bool bUseFrameSync = false;` — Enables the use of frame sync.
- L174 _private member_ `FNDISourceSettings SourceSettings;` — Information describing detailed information about the sender this receiver is currently connected to
- L177 _private member_ `FNDIMediaReceiverPerformanceData PerformanceData;` — Information describing detailed information about the receiver performance when connected to an NDI? sender
- L180 _private member_ `int64_t LastFrameTimestamp = 0;` — Keep track of the last VideoFrame timestamp received. Used to detect new frame.
- L183 _private member_ `NDIlib_frame_format_type_e LastFrameFormatType = NDIlib_frame_format_type_max;` — Keep track of the last VideoFrame format type received. Used to detect new frame.
- L186 _private member_ `int32 LastNumAudioChannels = 0;` — Keep track of the last AudioFrame's num audio channel received.
- L189 _private member_ `bool bIsCurrentlyConnected = false;` — Keep track of the current connection status with the source.
- L192 _private member_ `TSharedPtr<FNDIMediaRuntimeLibrary> NdiLib;` — Reference to the ndi runtime library used to create the receiver and frame sync instances.
- L195 _private member_ `NDIlib_recv_instance_t ReceiveInstance = nullptr;` — NDI receiver instance
- L198 _private member_ `NDIlib_framesync_instance_t FrameSyncInstance = nullptr;` — NDI FrameSync instance
- L201 _private member_ `mutable FCriticalSection RenderSyncContext;` — Critical section for VideoFrame processing related members.
- L204 _private member_ `FCriticalSection AudioSyncContext;` — Critical section for AudioFrame processing related members.
- L207 _private member_ `FCriticalSection MetadataSyncContext;` — Critical section for Metadata frame processing related members.
- L210 _private member_ `FCriticalSection ConnectionSyncContext;` — Critical section for current connection status (bIsCurrentlyConnected).
- L213 _private member_ `FDelegateHandle FrameEndRTHandle;` — Handle for the frame end render thread delegate.

#### enum `FNDIStreamReceiver::ECaptureMode`  
`enum class ECaptureMode`  
_L24-31_
- desc: Receiver's capture mode indicate how the receiver is going to call FetchVideo/Audio.
- L27 _public enumerator_ `Manual` — The user of the receiver manually triggers capturing frames through FetchVideo/Audio()
- L29 _public enumerator_ `OnEndFrameRT` — The receiver automatically captures frames every engine render frame (in the render thread)

#### Free symbols / members of external scopes

- L120 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConnected, FNDIStreamReceiver*) FOnConnected OnConnected;` — Delegate called when the source is connected. @remark Called from the main thread.
- L127 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisconnected, FNDIStreamReceiver*) FOnDisconnected OnDisconnected;` — Delegate called when the source is disconnected @remark Called from the main thread.
- L131 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnVideoFrameReceived, FNDIStreamReceiver*, const NDIlib_video_frame_v2_t&, const FTimespan&) FOnVideoFrameReceived OnVideoFrameReceived;` — Delegate called when a video frame is received.
- L135 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnAudioFrameReceived, FNDIStreamReceiver*, const NDIlib_audio_frame_v2_t&, const FTimespan&) FOnAudioFrameReceived OnAudioFrameReceived;` — Delegate called when an audio frame is received.
- L139 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnMetadataFrameReceived, FNDIStreamReceiver*, const NDIlib_metadata_frame_t&, const FTimespan&) FOnMetadataFrameReceived OnMetadataFrameReceived;` — Delegate called when a metadata frame is received.
- L143 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnMetaDataReceived, FNDIStreamReceiver* , FString , bool );` — Delegate called when metadata is received (either from a metadata frame or attached to a video frame).

### `Plugins/Media/NDIMedia/Source/NDIMedia/Private/Player/NDIStreamReceiverManager.h` (Private)


#### class `FNDIStreamReceiverManager`  
`class FNDIStreamReceiverManager : public TSharedFromThis<FNDIStreamReceiverManager>`  
_L16-38_
- inherits: `TSharedFromThis<FNDIStreamReceiverManager>`
- desc: Implementation of an NDI Stream manager NDI Stream receivers can be shared between media players or time code providers. This manager simply allows for the receivers to be shared.
- L24 _public prototype_ `TSharedPtr<FNDIStreamReceiver> FindReceiver(const FString& InSourceName);` — Finds a managed receiver for the given source. @param InSourceName Source name of the receiver to find. @return Found receiver, or null if none.
- L30 _public prototype_ `bool AddReceiver(const TSharedPtr<FNDIStreamReceiver>& InReceiver);` — The given receiver is going to be managed. This function may fail if a receiver of the same source is already added.
- L33 _private prototype_ `void RemoveExpiredEntries();`
- L37 _private member_ `TArray<TWeakPtr<FNDIStreamReceiver>> ReceiversWeak;` — Source name to receiver map.

### `Plugins/Media/NDIMedia/Source/NDIMedia/Public/NDIMediaCapture.h` (Public)


#### class `UNDIMediaCapture`  
`class UNDIMediaCapture : public UMediaCapture`  
_L14-58_
- reflection: `UCLASS()`
- inherits: `UMediaCapture`
- L19 _public prototype_ `virtual ~UNDIMediaCapture();`
- L23 _protected prototype_ `virtual void OnFrameCaptured_RenderingThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, void* InBuffer, int32 Width, int32 Height, int32 BytesPerRow) override;`
- L24 _protected prototype_ `virtual void OnFrameCaptured_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, const FMediaCaptureResourceData& InResourceData) override;`
- L25 _protected prototype_ `virtual bool InitializeCapture() override;`
- L26 _protected prototype_ `virtual bool PostInitializeCaptureViewport(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L27 _protected prototype_ `virtual bool PostInitializeCaptureRenderTarget(UTextureRenderTarget2D* InRenderTarget) override;`
- L28 _protected prototype_ `virtual bool PostInitializeCaptureRHIResource(const FRHICaptureResourceDescription& InResourceDescription) override;`
- L29 _protected prototype_ `virtual bool PostInitializeCaptureMediaTexture(UMediaTexture* InMediaTexture) override;`
- L30 _protected prototype_ `virtual bool UpdateAudioDeviceImpl(const FAudioDeviceHandle& InAudioDeviceHandle) override;`
- L31 _protected prototype_ `virtual void StopCaptureImpl(bool bAllowPendingFrameToBeProcess) override;`
- L32 _protected prototype_ `virtual bool SupportsAnyThreadCapture() const override;`
- L35 _protected prototype_ `virtual bool ShouldAutoRecordCaptureStartedEvent() const override;`
- L36 _protected prototype_ `virtual FString GetAnalyticsEventPrefix() const override;`
- L41 _private prototype_ `bool StartNewCapture();`
- L44 _private prototype_ `void OnFrameCapturedImpl(const FCaptureBaseData& InBaseData, void* InBuffer, int32 Width, int32 Height, int32 BytesPerRow);` — Sends the captured buffer to NDI.
- L47 _private member_ `FCriticalSection CaptureInstanceCriticalSection;`
- L57 _private member_ `FNDICaptureInstance* CaptureInstance = nullptr;`

### `Plugins/Media/NDIMedia/Source/NDIMedia/Public/NDIMediaDefines.h` (Public)


#### enum `ENDIReceiverBandwidth`  
`enum class ENDIReceiverBandwidth : uint8`  
_L11-24_
- reflection: `UENUM(BlueprintType)`
- desc: Receiver Bandwidth modes
- L14 _public enumerator_ `MetadataOnly = 0x00 UMETA(DisplayName = "Metadata Only")` — Receive metadata.
- L17 _public enumerator_ `AudioOnly = 0x01 UMETA(DisplayName = "Audio Only")` — Receive metadata, audio
- L20 _public enumerator_ `Lowest = 0x02 UMETA(DisplayName = "Lowest")` — Receive metadata, audio, video at a lower bandwidth and resolution.
- L23 _public enumerator_ `Highest = 0x03 UMETA(DisplayName = "Highest")` — Receive metadata, audio, video at full resolution.

### `Plugins/Media/NDIMedia/Source/NDIMedia/Public/NDIMediaOutput.h` (Public)


#### enum `ENDIMediaOutputPixelFormat`  
`enum class ENDIMediaOutputPixelFormat`  
_L15-18_
- reflection: `UENUM()`
- desc: Texture format supported by UNDIMediaOutput.
- L17 _public enumerator_ `B8G8R8A8 UMETA(DisplayName = "8bit RGBA")`

#### enum `ENDIMediaOutputAudioSampleRate`  
`enum class ENDIMediaOutputAudioSampleRate : uint32`  
_L25-33_
- reflection: `UENUM()`
- desc: NDI Audio supports any sample rate. The standard for live production is 48 kHz.
- L27 _public enumerator_ `SR_44_1k = 44100 UMETA(DisplayName = "44.1 kHz")`
- L28 _public enumerator_ `SR_48k = 48000 UMETA(DisplayName = "48 kHz")`
- L29 _public enumerator_ `SR_88_2k = 88200 UMETA(DisplayName = "88.2 kHz")`
- L30 _public enumerator_ `SR_96k = 96000 UMETA(DisplayName = "96 kHz")`
- L31 _public enumerator_ `SR_176_4k = 176400 UMETA(DisplayName = "176.4 kHz")`
- L32 _public enumerator_ `SR_192k = 192000 UMETA(DisplayName = "192 kHz")`

#### class `UNDIMediaOutput`  
`class UNDIMediaOutput : public UMediaOutput`  
_L53-155_
- reflection: `UCLASS(BlueprintType, PrioritizeCategories=(Media, Audio, Output, Synchronization), meta = (MediaIOCustomLayout = "NDI"))`
- inherits: `UMediaOutput`
- desc: Output information for a NDI media capture. @note	'Frame Buffer Pixel Format' must be set to RGBA8
- L58 _public prototype_ `UNDIMediaOutput(const FObjectInitializer& ObjectInitializer);`
- L65 _public member_ `FString SourceName = TEXT("Unr` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Media")` — Describes a user-friendly name of the output stream to differentiate from other output streams on the current machine
- L72 _public member_ `FString GroupName = TEXT("");` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Media")` — Defines the group this source is part of. If left empty, the source is "ungrouped" and will fall in the "Public" group by default in NDI Access Manager or NDI Bridge.
- L76 _public member_ `EMediaIOOutputType OutputType = EMediaIOOutputType::Fill;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Media")` — Whether to output the fill or the fill and key.
- L80 _public member_ `bool bInvertKeyOutput = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media")` — Options on how to save the images.
- L84 _public member_ `bool bOverrideDesiredSize = false;` — `UPROPERTY(BlueprintReadWrite, Category="Media")` — Use the default back buffer size or specify a specific size to capture.
- L88 _public member_ `FIntPoint DesiredSize;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media", meta=(EditCondition="bOverrideDesiredSize"))` — Use the default back buffer size or specify a specific size to capture.
- L92 _public member_ `bool bOverridePixelFormat = false;` — `UPROPERTY(BlueprintReadWrite, Category="Media")` — Use the default back buffer pixel format or specify a specific the pixel format to capture.
- L96 _public member_ `ENDIMediaOutputPixelFormat DesiredPixelFormat = ENDIMediaOutputPixelFormat::B8G8R8A8;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media", meta=(EditCondition="bOverridePixelFormat"))` — Use the default back buffer pixel format or specify a specific the pixel format to capture.
- L100 _public member_ `FFrameRate FrameRate = FFrameRate(60, 1);` — `UPROPERTY(BlueprintReadwrite, EditAnywhere, Category = "Media")` — Represents the desired number of frames (per second) for video to be sent over NDI
- L104 _public member_ `bool bOutputAudio = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")` — Whether to capture and output audio from the engine.
- L108 _public member_ `int32 AudioBufferSize = 5*1024;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")` — Size of the buffer that holds rendered audio samples, a bigger buffer will produce a more stable output signal but will introduce more delay.
- L117 _public member_ `int32 NumOutputAudioChannels = 2;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")` — An individual NDI stream can transport multiple audio channels. The number of channels supported depends on the codec used. PCM allows unlimited channels; in NDI, AAC can support 2 channels, while Opus can support up to 255 channels.
- L124 _public member_ `ENDIMediaOutputAudioSampleRate AudioSampleRate = ENDIMediaOutputAudioSampleRate::SR_48k;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")` — NDI Audio supports any sample rate. The standard for live production is 48 kHz.
- L131 _public member_ `bool bSendAudioOnlyIfReceiversConnected = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")` — As an optimization, the audio will not be converted and sent if there are no connected receivers. Setting this to false will result in audio being converted and sent regardless of receivers.
- L138 _public member_ `bool bWaitForSyncEvent = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Synchronization")` — Wait for the NDI source sync event. Caution: this will be blocking in the rendering thread and may cause performance issues in the engine.
- L142 _public prototype_ `virtual bool Validate(FString& FailureReason) const override;`
- L143 _public prototype_ `virtual FIntPoint GetRequestedSize() const override;`
- L144 _public prototype_ `virtual EPixelFormat GetRequestedPixelFormat() const override;`
- L145 _public prototype_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override;`
- L148 _public prototype_ `virtual FString GetDescriptionString() const override;`
- L149 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`
- L153 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`

### `Plugins/Media/NDIMedia/Source/NDIMedia/Public/NDIMediaSettings.h` (Public)


#### class `UNDIMediaSettings`  
`class UNDIMediaSettings : public UDeveloperSettings`  
_L10-38_
- reflection: `UCLASS(config=Engine, defaultconfig, meta = (DisplayName = "NDI Media"))`
- inherits: `UDeveloperSettings`
- L15 _public prototype_ `UNDIMediaSettings();`
- L21 _public member_ `bool bUseBundledLibrary = true;` — `UPROPERTY(config, EditAnywhere, Category=Library)` — Specify whether to use the bundled NDI runtime library or try to use the one installed on the system.
- L28 _public member_ `FString LibraryDirectoryOverride;` — `UPROPERTY(config, EditAnywhere, Category=Library, meta=(EditCondition="!bUseBundledLibrary"))` — Manually specify a directory for the NDI runtime library. If left empty, the default path is queried from "NDI_RUNTIME_DIR_V5" environment variable.
- L34 _public member_ `FString LibraryFullPath;` — `UPROPERTY(Transient, VisibleAnywhere, Category=Library)` — Full path of the currently loaded runtime library.
- L37 _public prototype_ `const TCHAR* GetNDILibRedistUrl() const;` — Returns the current SDK's values for NDI Lib Redist url.

### `Plugins/Media/NDIMedia/Source/NDIMedia/Public/NDIMediaSource.h` (Public)


#### class `UNDIMediaSource`  
`class UNDIMediaSource : public UCaptureCardMediaSource`  
_L16-109_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hideCategories=(Platforms,Object), PrioritizeCategories=(NDI, Video, ColorManagement, Audio, Ancillary, Synchronization, Debug), meta=(MediaIOCustomLayout="NDI"))`
- inherits: `UCaptureCardMediaSource`
- desc: Media source for NDI streams.
- L22 _public prototype_ `UNDIMediaSource();` — Default constructor.
- L26 _public member_ `FMediaIOConfiguration MediaConfiguration;` — `UPROPERTY(EditAnywhere, Category="NDI", meta=(DisplayName="Configuration"))` — The device, port and video settings that correspond to the input.
- L30 _public member_ `ENDIReceiverBandwidth Bandwidth = ENDIReceiverBandwidth::Highest;` — `UPROPERTY(EditAnywhere, Category="NDI")` — Indicates the current bandwidth mode used for the connection to this source
- L36 _public member_ `bool bSyncTimecodeToSource = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="NDI")` — Indicates whether the timecode should be synced to the Source Timecode value or engine's.
- L43 _public member_ `bool bCaptureAncillary;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ancillary")` — Capture Ancillary from the NDI source. It will decrease performance
- L47 _public member_ `int32 MaxNumAncillaryFrameBuffer;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category="Ancillary", meta=(EditCondition="bCaptureAncillary", ClampMin="1", ClampMax="32"))` — Maximum number of ancillary data frames to buffer.
- L51 _public member_ `bool bCaptureAudio;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Audio")` — Capture Audio from the NDI source.
- L55 _public member_ `int32 MaxNumAudioFrameBuffer;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category="Audio", meta=(EditCondition="bCaptureAudio", ClampMin="1", ClampMax="32"))` — Maximum number of audio frames to buffer.
- L59 _public member_ `bool bCaptureVideo;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Video")` — Capture Video from the NDI source.
- L63 _public member_ `int32 MaxNumVideoFrameBuffer;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category="Video", meta=(EditCondition="bCaptureVideo", ClampMin="1", ClampMax="32"))` — Maximum number of video frames to buffer.
- L67 _public member_ `bool bLogDropFrame;` — `UPROPERTY(EditAnywhere, Category="Debug")` — Log a warning when there's a drop frame.
- L74 _public member_ `bool bEncodeTimecodeInTexel;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Debug", meta=(DisplayName="Burn Frame Timecode"))` — Burn Frame Timecode in the input texture without any frame number clipping. @Note Only supported with progressive format.
- L82 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOptionChanged, UObject*, FPropertyChangedEvent&);` — Delegate called when an NDI Media Source is modified. This can be used to propagate the change to active players. @remark Called from the main thread.
- L83 _public member_ `static FOnOptionChanged OnOptionChanged;`
- L87 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const override;`
- L88 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const override;`
- L89 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const override;`
- L90 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
- L94 _public prototype_ `virtual FString GetUrl() const override;`
- L95 _public prototype_ `virtual bool Validate() const override;`
- L99 _public prototype_ `virtual void PostLoad() override;`
- L100 _public function_ `virtual bool SupportsFormatAutoDetection() const override`
- L102 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L108 _private prototype_ `void AssignDefaultConfiguration();` — Assigns a default configuration if the current configuration is invalid.

#### Free symbols / members of external scopes

- L82 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOptionChanged, UObject*, FPropertyChangedEvent&);` — Delegate called when an NDI Media Source is modified. This can be used to propagate the change to active players. @remark Called from the main thread.

### `Plugins/Media/NDIMedia/Source/NDIMedia/Public/NDIMediaTimecodeProvider.h` (Public)


#### class `UNDIMediaTimecodeProvider`  
`class UNDIMediaTimecodeProvider : public UGenlockedTimecodeProvider`  
_L17-63_
- reflection: `UCLASS(MinimalAPI, Blueprintable, editinlinenew, meta=(DisplayName="NDI Timecode Provider", MediaIOCustomLayout="NDI"))`
- inherits: `UGenlockedTimecodeProvider`
- desc: Timecode provider from an NDI source
- L23 _public prototype_ `virtual bool FetchTimecode(FQualifiedFrameTime& OutFrameTime) override;`
- L24 _public prototype_ `virtual ETimecodeProviderSynchronizationState GetSynchronizationState() const override;`
- L25 _public prototype_ `virtual bool Initialize(class UEngine* InEngine) override;`
- L26 _public prototype_ `virtual void Shutdown(class UEngine* InEngine) override;`
- L30 _public prototype_ `virtual void BeginDestroy() override;`
- L37 _public member_ `FMediaIOVideoTimecodeConfiguration TimecodeConfiguration;` — `UPROPERTY(EditAnywhere, Category="Timecode")` — Use the time code embedded in the video input stream.
- L41 _public member_ `ENDIReceiverBandwidth Bandwidth = ENDIReceiverBandwidth::Highest;` — `UPROPERTY(EditAnywhere, Category="NDI")` — Indicates the current bandwidth mode used for the connection to this source
- L44 _private prototype_ `void ReleaseResources();`
- L48 _private member_ `mutable FCriticalSection StateSyncContext;` — Critical section protecting "State"
- L51 _private member_ `ETimecodeProviderSynchronizationState State = ETimecodeProviderSynchronizationState::Closed;` — Current synchronization state
- L54 _private member_ `FQualifiedFrameTime MostRecentFrameTime;` — Last received frame time from the receiver.
- L57 _private member_ `TSharedPtr<FNDIStreamReceiver> Receiver;` — Current stream receiver
- L60 _private member_ `FDelegateHandle VideoFrameReceivedHandle;` — Handles for the stream receiver delegates
- L61 _private member_ `FDelegateHandle ConnectedHandle;`
- L62 _private member_ `FDelegateHandle DisconnectedHandle;`
