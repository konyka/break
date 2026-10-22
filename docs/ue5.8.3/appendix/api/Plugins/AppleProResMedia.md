# Plugins / AppleProResMedia

- module root: `Plugins/Media/AppleProResMedia/Source/AppleProResMedia`
- headers: 8; symbols: 218
- symbol kinds: class=6, delegate=1, enum=6, enumerator=24, function=5, macro=6, member=79, namespace=2, prototype=85, struct=4
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MovieSceneCapture, Projects, WmfMedia, WmfMediaFactory
- PublicDependencyModuleNames: ImageWriteQueue, MovieRenderPipelineCore, OpenColorIO, ProResLib, ProResToolbox, SlateCore, WmfMedia, WmfMediaFactory

### `Plugins/Media/AppleProResMedia/Source/AppleProResMedia/Private/AppleProResEncoderProtocol.h` (Private)


#### enum `EAppleProResEncoderFormats`  
`enum class EAppleProResEncoderFormats : uint8`  
_L24-32_
- reflection: `UENUM()`
- L26 _public enumerator_ `F_422HQ UMETA(DisplayName = "422 HQ")`
- L27 _public enumerator_ `F_422 UMETA(DisplayName = "422")`
- L28 _public enumerator_ `F_422LT UMETA(DisplayName = "422 LT")`
- L29 _public enumerator_ `F_422Proxy UMETA(DisplayName = "422 Proxy")`
- L30 _public enumerator_ `F_4444 UMETA(DisplayName = "4444")`
- L31 _public enumerator_ `F_4444XQ UMETA(DisplayName = "4444 XQ")`

#### enum `EAppleProResEncoderColorDescription`  
`enum class EAppleProResEncoderColorDescription : uint8`  
_L35-40_
- reflection: `UENUM()`
- L37 _public enumerator_ `CD_SDREC601_525_60HZ UMETA(DisplayName = "SD Rec. 601 525/60Hz")`
- L38 _public enumerator_ `CD_SDREC601_625_50HZ UMETA(DisplayName = "SD Rec. 601 625/50Hz")`
- L39 _public enumerator_ `CD_HDREC709 UMETA(DisplayName = "HD Rec. 709")`

#### enum `EAppleProResEncoderScanType`  
`enum class EAppleProResEncoderScanType : uint8`  
_L43-48_
- reflection: `UENUM()`
- L45 _public enumerator_ `IM_PROGRESSIVE_SCAN UMETA(DisplayName = "Progressive encoding mode")`
- L46 _public enumerator_ `IM_INTERLACED_TOP_FIELD_FIRST UMETA(DisplayName = "Interlaced mode; first (top) image line belongs to first temporal field")`
- L47 _public enumerator_ `IM_INTERLATED_BOTTOM_FIRST_FIRST UMETA(DisplayName = "Interlaced mode; second (bottom) image line belongs to first temporal field")`

#### class `UAppleProResEncoderProtocol`  
`class UAppleProResEncoderProtocol : public UFrameGrabberProtocol`  
_L51-127_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Apple ProRes Encoder (mov)", CommandLineID = "AppleProRes"))`
- inherits: `UFrameGrabberProtocol`
- L56 _public prototype_ `UAppleProResEncoderProtocol(const FObjectInitializer& InObjInit);`
- L59 _public prototype_ `virtual bool SetupImpl() override;`
- L60 _public prototype_ `virtual void FinalizeImpl() override;`
- L61 _public prototype_ `virtual FFramePayloadPtr GetFramePayload(const FFrameMetrics& InFrameMetrics) override;`
- L62 _public prototype_ `virtual void ProcessFrame(FCapturedFrameData InFrame) override;`
- L63 _public prototype_ `virtual bool CanWriteToFileImpl(const TCHAR* InFilename, bool bInOverwriteExisting) const override;`
- L68 _public member_ `EAppleProResEncoderFormats EncodingFormat;` — `UPROPERTY(config, EditAnywhere, Category = "Apple ProRes Settings")`
- L71 _public member_ `EAppleProResEncoderColorDescription ColorDescription;` — `UPROPERTY(config, EditAnywhere, Category = "Apple ProRes Settings")`
- L74 _public member_ `EAppleProResEncoderScanType ScanType;` — `UPROPERTY(config, EditAnywhere, Category = "Apple ProRes Settings")`
- L77 _public member_ `int32 NumberOfEncodingThreads;` — `UPROPERTY(config, EditAnywhere, Category = "Apple ProRes Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "64.0", UIMax = "64.0"))`
- L80 _public member_ `bool bEmbedTimecodeTrack;` — `UPROPERTY(config, EditAnywhere, Category = "Apple ProRes Settings")`
- L84 _public member_ `bool bDropFrameTimecode;` — `UPROPERTY(config, EditAnywhere, Category = "Apple ProRes Settings")` — Use Drop Frame Timecode when applicable (29.97p or 59.94i).
- L88 _private prototype_ `void ParseCommandLine();`
- L89 _private prototype_ `bool CreateProResFile(const FString& InFilename);`
- L90 _private prototype_ `void ConvertFColorToRGBA4444(const TArray<FColor>& InColorbuffer);`
- L92 _private prototype_ `PRCodecType GetSelectedCodecType() const;`
- L93 _private prototype_ `PRVideoCodecType GetSelectedVideoCodecType() const;`
- L94 _private prototype_ `ProResFormatDescriptionColorPrimaries GetColorPrimaries() const;`
- L95 _private prototype_ `ProResFormatDescriptionTransferFunction GetTransferFunction() const;`
- L96 _private prototype_ `ProResFormatDescriptionYCbCrMatrix GetYCbCrMatrix() const;`
- L97 _private prototype_ `int32_t GetFrameHeaderColorPrimaries() const;`
- L98 _private prototype_ `int32_t GetFrameHeaderTransferCharacteristic() const;`
- L99 _private prototype_ `int32_t GetFrameHeaderMatrixCoefficients() const;`
- L100 _private prototype_ `PRInterlaceMode GetInterlaceMode() const;`
- L101 _private prototype_ `PRPixelFormat GetPixelFormat() const;`
- L102 _private prototype_ `uint32 GetPixelAspectRatioHorizontalSpacing() const;`
- L103 _private prototype_ `uint32 GetPixelAspectRatioVerticalSpacing() const;`
- L104 _private prototype_ `uint32 GetStride() const;`
- L105 _private prototype_ `uint32_t GetBitDepth() const;`
- L106 _private prototype_ `uint32_t GetFieldCount() const;`
- L107 _private prototype_ `ProResFormatDescriptionFieldDetail GetFieldDetail() const;`
- L108 _private prototype_ `bool HasAlpha() const;`
- L109 _private prototype_ `void ReleaseAndClearResources();`
- L113 _private member_ `ProResFileWriterRef FileWriter;`
- L114 _private member_ `PRPersistentTrackID VideoTrackID;`
- L115 _private member_ `PRPersistentTrackID TimecodeTrackID;`
- L116 _private member_ `PRTime CurrentTime;`
- L117 _private member_ `ProResFormatDescriptionRef FormatDescription;`
- L118 _private member_ `ProResTimecodeFormatDescriptionRef TimecodeFormatDescription;`
- L119 _private member_ `PREncoderRef Encoder;`
- L120 _private member_ `PRVideoDimensions Dimensions;`
- L122 _private member_ `FFrameRate FrameRate;`
- L123 _private member_ `int32 MaxCompressedFrameSize;`
- L124 _private member_ `int32 TargetCompressedFrameSize;`
- L125 _private member_ `TArray<uint8> IntermediateFrameBuffer;`
- L126 _private member_ `TArray<uint8> OutputFrameBuffer;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define __LLP64__ 1`
- L21 _macro_ `#define UE_API APPLEPRORESMEDIA_API`

### `Plugins/Media/AppleProResMedia/Source/AppleProResMedia/Private/AppleProResMediaModule.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define _byteswap_ulong(x) OSSwapInt32(x)`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleProResMedia, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleProResMedia, Log, All);`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace AppleProResMedia` (scope `UE`)
- L20 _prototype_ `bool LoadProResToolbox();` (scope `UE::AppleProResMedia`) — ProResToolbox is delay loaded but needs to be manually loaded because of search path limitations. @return true if the library was loaded, false otherwise.

### `Plugins/Media/AppleProResMedia/Source/AppleProResMedia/Private/AppleProResMediaSettings.h` (Private)


#### class `UAppleProResMediaSettings`  
`class UAppleProResMediaSettings : public UObject`  
_L15-33_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Settings for the AppleProResMedia plug-in.
- L23 _public prototype_ `UAppleProResMediaSettings();` — Default constructor.
- L29 _public member_ `int32 NumberOfCPUDecodingThreads;` — `UPROPERTY(config, EditAnywhere, DisplayName = "Number Of CPU Decoding Threads", Category = Media, meta = (ClampMin = "0.0", UIMin = "0.0"))` — Number of CPU decoding threads (Set this to 0 to have the decoder spawn according to the number of processors detected in the system.).

### `Plugins/Media/AppleProResMedia/Source/AppleProResMedia/Private/MovieGraphAppleProResNode.h` (Private)


#### class `UMovieGraphAppleProResNode`  
`class UMovieGraphAppleProResNode : public UMovieGraphVideoOutputNode, public IMovieGraphEvaluationNodeInjector`  
_L13-127_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieGraphVideoOutputNode,IMovieGraphEvaluationNodeInjector`
- desc: A node which can output Apple ProRes movies.
- L18 _public prototype_ `UMovieGraphAppleProResNode();`
- L21 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L22 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L23 _public prototype_ `virtual FText GetKeywords() const override;`
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L26 _public prototype_ `virtual FText GetBasicConfigShortDisplayName() const override;`
- L31 _protected prototype_ `virtual TUniquePtr<MovieRenderGraph::IVideoCodecWriter> Initialize_GameThread(const FMovieGraphVideoNodeInitializationContext& InInitializationContext) override;` — UMovieGraphVideoOutputNode Interface
- L32 _protected prototype_ `virtual bool Initialize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L33 _protected prototype_ `virtual void WriteFrame_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter, FImagePixelData* InPixelData, TArray<FMovieGraphPassData>&& InCompositePasses, TObjectPtr<UMovieGraphEvaluatedConfig> InEvaluatedConfig, const FString& InBranchName) override;`
- L34 _protected prototype_ `virtual void BeginFinalize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L35 _protected prototype_ `virtual void Finalize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L36 _protected prototype_ `virtual const TCHAR* GetFilenameExtension() const override;`
- L37 _protected prototype_ `virtual bool IsAudioSupported() const override;`
- L41 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;` — UMovieGraphSettingNode Interface
- L45 _protected prototype_ `virtual void InjectNodesPostEvaluation(const FName& InBranchName, UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<UMovieGraphSettingNode*>& OutInjectedNodes) override;` — IMovieGraphEvaluationNodeInjector Interface
- L56 _protected member_ `TWeakObjectPtr<UMovieGraphPipeline> CachedPipeline;` — The pipeline that is running this node.
- L60 _public member_ `uint8 bOverride_Quality : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L63 _public member_ `uint8 bOverride_bIncludeAudio : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L66 _public member_ `uint8 bOverride_OCIOConfiguration : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L69 _public member_ `uint8 bOverride_OCIOContext : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L72 _public member_ `uint8 bOverride_bEnableBurnIn : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L75 _public member_ `uint8 bOverride_BurnInClass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L78 _public member_ `uint8 bOverride_bCompositeOntoFinalImage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L81 _public member_ `uint8 bOverride_BurnInFileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L85 _public member_ `EAppleProResEncoderCodec Quality;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apple ProRes", meta = (EditCondition = "bOverride_Quality"))` — The Apple ProRes codec that should be used. See Apple documentation for more specifics. Uses Rec 709 color primaries.
- L89 _public member_ `bool bIncludeAudio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apple ProRes", meta = (EditCondition = "bOverride_bIncludeAudio"))` — If true, audio will be included in the video file.
- L100 _public member_ `FOpenColorIODisplayConfiguration OCIOConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", DisplayName="OCIO Configuration", meta = (DisplayAfter = "FileNameFormat", EditCondition = "bOverride_OCIOConfiguration"))` — OCIO configuration/transform settings. Note: There are differences from the previous implementation in MRQ given that we are now doing CPU-side processing. 1) This feature only works on desktop platforms when the OpenColorIO library is available. 2) Users are now responsible for setting the renderer output space to Final Color (HDR) in Linear Working Color Space (SCS_FinalColorHDR) by disabling the Tone Curve setting on the renderer node.
- L110 _public member_ `TMap<FString, FString> OCIOContext;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", DisplayName = "OCIO Context", meta = (DisplayAfter = "OCIOConfiguration", EditCondition = "bOverride_OCIOContext"))` — OCIO context of key-value string pairs, typically used to apply shot-specific looks (such as a CDL color correction, or a 1D grade LUT). Notes: 1) If a configuration asset base context was set, it remains active but can be overridden here with new key-values. 2) Format tokens such as {shot_name} are supported and will get resolved before submission.
- L114 _public member_ `bool bEnableBurnIn = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bEnableBurnIn"))` — If true, this output node will also generate a burn-in.
- L118 _public member_ `FSoftClassPath BurnInClass = FSoftClassPath(TEXT("/Mov` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Burn In", meta=(MetaClass="/Script/MovieRenderPipelineCore.MovieGraphBurnInWidget", EditCondition="bOverride_BurnInClass"))` — The widget that the burn-in should use.
- L122 _public member_ `bool bCompositeOntoFinalImage = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bCompositeOntoFinalImage"))` — If true, the burn-in that's generated will be composited onto this output. Otherwise, the burn-in will be written to a different file.
- L126 _public member_ `FString BurnInFileNameFormat = TEXT("{se` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_BurnInFileNameFormat", MrgTokenAutocomplete))` — The file name format used for writing out the burn-in video (if not composited).

#### struct `UMovieGraphAppleProResNode::FProResWriter`  
`struct FProResWriter : public MovieRenderGraph::IVideoCodecWriter`  
_L49-53_
- inherits: `MovieRenderGraph::IVideoCodecWriter`
- L51 _public member_ `bool bSkipColorConversions = false;`
- L52 _public member_ `TUniquePtr<FAppleProResEncoder> Writer;`

### `Plugins/Media/AppleProResMedia/Source/AppleProResMedia/Private/MoviePipelineAppleProResOutput.h` (Private)


#### class `UMoviePipelineAppleProResOutput`  
`class UMoviePipelineAppleProResOutput : public UMoviePipelineVideoOutputBase`  
_L13-74_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMoviePipelineVideoOutputBase`
- L17 _private function_ `UMoviePipelineAppleProResOutput() : UMoviePipelineVideoOutputBase() , Codec(EAppleProResEncoderCodec::ProRes_4444XQ) , bDropFrameTimecode(false) , bIncludeAudio(true) , bOverrideMaximumEncodingThreads(false) , MaxNumberOfEncodingThreads(0)`
- L29 _protected prototype_ `virtual TUniquePtr<MovieRenderPipeline::IVideoCodecWriter> Initialize_GameThread(const FString& InFileName, FIntPoint InResolution, EImagePixelType InPixelType, ERGBFormat InPixelFormat, uint8 InBitDepth, uint8 InNumChannels) override;` — UMoviePipelineVideoOutputBase Interface
- L30 _protected prototype_ `virtual bool Initialize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter) override;`
- L31 _protected prototype_ `virtual void WriteFrame_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter, FImagePixelData* InPixelData, TArray<MoviePipeline::FCompositePassInfo>&& InCompositePasses) override;`
- L32 _protected prototype_ `virtual void BeginFinalize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter);`
- L33 _protected prototype_ `virtual void Finalize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter);`
- L34 _protected function_ `virtual const TCHAR* GetFilenameExtension() const override`
- L35 _protected function_ `virtual bool IsAudioSupported() const`
- L40 _protected prototype_ `virtual FText GetDisplayText() const override;`
- L45 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;` — UMoviePipelineSetting Interface
- L51 _public member_ `EAppleProResEncoderCodec Codec;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Which Apple ProRes codec should we use? See Apple documentation for more specifics. Uses Rec 709 color primaries.
- L55 _public member_ `bool bDropFrameTimecode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Should the embedded timecode track be written using drop-frame format? Only applicable if the sequence framerate is 29.97
- L59 _public member_ `bool bIncludeAudio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — If true, audio will be included in the video file.
- L63 _public member_ `bool bOverrideMaximumEncodingThreads;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Should we override the maximum number of encoding threads?
- L67 _public member_ `int32 MaxNumberOfEncodingThreads;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin=0, ClampMin=0, EditCondition="bOverrideMaximumEncodingThreads"), Category = "Settings")` — What is the maximum number of threads the encoder should use to encode frames with? Zero means auto-determine based on hardware.

#### struct `UMoviePipelineAppleProResOutput::FProResWriter`  
`struct FProResWriter : public MovieRenderPipeline::IVideoCodecWriter`  
_L70-73_
- inherits: `MovieRenderPipeline::IVideoCodecWriter`
- L72 _public member_ `TUniquePtr<FAppleProResEncoder> Writer;`

### `Plugins/Media/AppleProResMedia/Source/AppleProResMedia/Private/ProResToolboxExtension.h` (Private)


#### Free symbols / members of external scopes

- L4 _macro_ `#define ProResToolboxExtension_h`
- L10 _prototype_ `PR_EXPORT PRStatus ProResFileWriterAddEncoderSampleBufferToTrack( ProResFileWriterRef writer, PRPersistentTrackID writerTrackID, PREncoderRef encoder, PRTime timestamp);` — Implementated on Mac, to reuse internal CMSampleBuffer between PREncoder and ProResFileWriter

### `Plugins/Media/AppleProResMedia/Source/AppleProResMedia/Private/Windows/WmfMediaAppleProResDecoder.h` (Private)


#### class `WmfMediaAppleProResDecoder`  
`class WmfMediaAppleProResDecoder : public WmfMediaDecoder`  
_L13-47_
- inherits: `WmfMediaDecoder`
- L19 _public prototype_ `WmfMediaAppleProResDecoder();`
- L20 _public prototype_ `virtual ~WmfMediaAppleProResDecoder();`
- L22 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppv) override;`
- L23 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetOutputAvailableType(DWORD dwOutputStreamID, DWORD dwTypeIndex, IMFMediaType** ppType) override;`
- L24 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE ProcessMessage(MFT_MESSAGE_TYPE eMessage, ULONG_PTR ulParam) override;`
- L25 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE ProcessOutput(DWORD dwFlags, DWORD cOutputBufferCount, MFT_OUTPUT_DATA_BUFFER* pOutputSamples, DWORD* pdwStatus) override;`
- L27 _public prototype_ `virtual bool IsExternalBufferSupported() const override;`
- L31 _public prototype_ `static bool IsSupported(const GUID& InGuid);`
- L32 _public prototype_ `static bool SetOutputFormat(const GUID& InGuid, GUID& OutVideoFormat);`
- L36 _private prototype_ `HRESULT InternalProcessOutput(IMFSample *InSample);`
- L37 _private prototype_ `virtual HRESULT InternalProcessInput(LONGLONG InTimeStamp, BYTE* InData, DWORD InDataSize) override;`
- L38 _private prototype_ `virtual HRESULT OnCheckInputType(IMFMediaType *InMediaType) override;`
- L39 _private prototype_ `virtual HRESULT OnSetInputType(IMFMediaType *InMediaType) override;`
- L41 _private prototype_ `virtual bool HasPendingOutput() const override;`
- L45 _protected member_ `PRDecoderRef Decoder;`
- L46 _protected member_ `TComPtr<IMFMediaBuffer> MediaBuffer;`

### `Plugins/Media/AppleProResMedia/Source/AppleProResMedia/Public/AppleProResEncoder/AppleProResEncoder.h` (Public)


#### enum `EAppleProResEncoderCodec`  
`enum class EAppleProResEncoderCodec : uint8`  
_L21-40_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `ProRes_422Proxy UMETA(DisplayName = "Apple ProRes 422 Proxy")` — Highest Compression. Approximately 45mbps @ 1920x1080@30fps
- L27 _public enumerator_ `ProRes_422LT UMETA(DisplayName = "Apple ProRes 422 LT")` — High compression. Approximately 100mbps @ 1920x1080@30fps
- L30 _public enumerator_ `ProRes_422 UMETA(DisplayName = "Apple ProRes 422")` — High Quality Compression for 422 RGB Sources. Approximately 150mbps @ 1920x1080@30fps
- L33 _public enumerator_ `ProRes_422HQ UMETA(DisplayName = "Apple ProRes 422 HQ")` — A higher bit-rate version of Apple ProRes 422. Approximately 225mbps @ 1920x1080@30fps
- L36 _public enumerator_ `ProRes_4444 UMETA(DisplayName = "Apple ProRes 4444")` — Extremely high quality and supports alpha channels. Can support both RGB and YCbCr formats. Very large file size. Approximately 330mbps @ 1920x1080@30fps
- L39 _public enumerator_ `ProRes_4444XQ UMETA(DisplayName = "Apple ProRes 4444 XQ")` — Highest quality storage with support for alpha channel with up to 12 bits precision for RGB and 16 bits for Alpha. Extremely large file size. Approximately 500mbps @ 1920x1080@30fps

#### enum `EAppleProResEncoderColorPrimaries`  
`enum class EAppleProResEncoderColorPrimaries : uint8`  
_L43-48_
- reflection: `UENUM(BlueprintType)`
- L45 _public enumerator_ `CD_SDREC601_525_60HZ UMETA(DisplayName = "SD Rec. 601 525/60Hz")`
- L46 _public enumerator_ `CD_SDREC601_625_50HZ UMETA(DisplayName = "SD Rec. 601 625/50Hz")`
- L47 _public enumerator_ `CD_HDREC709 UMETA(DisplayName = "HD Rec. 709")`

#### enum `EAppleProResEncoderScanMode`  
`enum class EAppleProResEncoderScanMode : uint8`  
_L51-56_
- reflection: `UENUM(BlueprintType)`
- L53 _public enumerator_ `IM_PROGRESSIVE_SCAN UMETA(DisplayName = "Progressive")`
- L54 _public enumerator_ `IM_INTERLACED_TOP_FIELD_FIRST UMETA(DisplayName = "Interlaced; first (top) image line belongs to first temporal field")`
- L55 _public enumerator_ `IM_INTERLATED_BOTTOM_FIRST_FIRST UMETA(DisplayName = "Interlaced; second (bottom) image line belongs to first temporal field")`

#### struct `FAppleProResEncoderOptions`  
`struct FAppleProResEncoderOptions`  
_L59-134_
- L63 _public function_ `FAppleProResEncoderOptions() : OutputFilename() , Width(0) , Height(0) , FrameRate(30, 1) , Codec(EAppleProResEncoderCodec::ProRes_422) , ColorPrimaries(EAppleProResEncoderColorPrimaries::CD_HDREC709) , bConvertToSrgb(true) , ScanMode(EAppleProResEncoderScanMode::IM_PROGRESSIVE_SCAN) , MaxNumberOfEncodingThreads(0) , bWriteAlpha(false) , bDropFrameTimecode(false) , FrameNumberOffset(0) , bIncludeAudio(true) , AudioSampleRate(48000) , AudioChannelCount(2)` — Disable deprecation warnings for bConvertToSrgb to make Clang happy.
- L81 _public prototype_ `FAppleProResEncoderOptions(FAppleProResEncoderOptions&) = default;`
- L82 _public prototype_ `~FAppleProResEncoderOptions() = default;`
- L83 _public prototype_ `FAppleProResEncoderOptions(const FAppleProResEncoderOptions&) = default;`
- L84 _public prototype_ `FAppleProResEncoderOptions(FAppleProResEncoderOptions&&) = default;`
- L85 _public prototype_ `FAppleProResEncoderOptions& operator=(const FAppleProResEncoderOptions&) = default;`
- L86 _public prototype_ `FAppleProResEncoderOptions& operator=(FAppleProResEncoderOptions&&) = default;`
- L90 _public member_ `FString OutputFilename;` — The absolute path on disk to try and save the video file to.
- L93 _public member_ `uint32 Width;` — The width of the video file.
- L96 _public member_ `uint32 Height;` — The height of the video file.
- L99 _public member_ `FFrameRate FrameRate;` — Frame Rate of the output video.
- L102 _public member_ `EAppleProResEncoderCodec Codec;` — Which ProRes codec should we use? Not all support alpha channels.
- L105 _public member_ `EAppleProResEncoderColorPrimaries ColorPrimaries;` — Which color primaries do we use? Only Rec 709 is well tested right now.
- L109 _public member_ `bool bConvertToSrgb;` — `UE_DEPRECATED(5.6, "The encoder currently always assumes Rec 709 input, and never used this parameter.")` — Whether the data should be converted to sRGB before being sent to the encoder. Should not be used when OCIO is active.
- L112 _public member_ `EAppleProResEncoderScanMode ScanMode;` — Which scan mode do we use? Only Progressive is tested right now.
- L115 _public member_ `int32 MaxNumberOfEncodingThreads;` — Maximum number of threads to use for encoding. Set to 0 for auto-determine based on hardware.
- L118 _public member_ `bool bWriteAlpha;` — If true, attempts to write the alpha channel from the incoming pixel data. Increases encoding time. Only works on some Codecs.
- L121 _public member_ `bool bDropFrameTimecode;` — If true, timecode track will use drop frame notation for the 29.97 frame rate.
- L124 _public member_ `int32 FrameNumberOffset;` — The number of frames to offset the Timecode track by.
- L127 _public member_ `bool bIncludeAudio;` — If false, then audio tracks will not be written and calls to WriteAudioSample will be ignored.
- L130 _public member_ `uint32 AudioSampleRate;` — The sample rate of the incoming audio data. Only tested with 48'000.
- L133 _public member_ `uint32 AudioChannelCount;` — The number of audio channels in the encoding data. Only tested with 2.

#### class `FAppleProResEncoder`  
`class FAppleProResEncoder`  
_L136-200_
- L145 _public prototype_ `FAppleProResEncoder(const FAppleProResEncoderOptions& InOptions);`
- L146 _public prototype_ `~FAppleProResEncoder();`
- L149 _public prototype_ `bool Initialize();` — Call to initialize the Sink Writer. This must be done before attempting to write data to it.
- L152 _public prototype_ `void Finalize();` — Finalize the video file and finish writing it to disk. Called by the destructor if not automatically called.
- L155 _public prototype_ `bool WriteFrame(const FImagePixelData* InPixelData);` — Appends a new frame onto the output file.
- L158 _public prototype_ `bool WriteAudioSample(const TArrayView<int16>& InAudioSamples);` — Appends a new audio sample onto the audio stream.
- L161 _public prototype_ `const FAppleProResEncoderOptions& GetOptions() const;` — Gets the options that the encoder was initialized with.
- L163 _public function_ `bool IsInitialized() const`
- L166 _private prototype_ `bool InitializeVideoTrack();`
- L167 _private prototype_ `bool InitializeTimecodeTrack();`
- L168 _private prototype_ `bool InitializeAudioTrack();`
- L169 _private prototype_ `void ReleaseAndClearResources();`
- L172 _private member_ `FAppleProResEncoderOptions Options;`
- L173 _private member_ `bool bInitialized;`
- L174 _private member_ `bool bFinalized;`
- L176 _private member_ `PRPersistentTrackID VideoTrackId;`
- L177 _private member_ `PRPersistentTrackID AudioTrackId;`
- L178 _private member_ `PRPersistentTrackID TimecodeTrackId;`
- L181 _private member_ `ProResVideoFormatDescriptionRef VideoFormatDescription;` — If valid, we own the memory and need to free it.
- L183 _private member_ `ProResAudioFormatDescriptionRef AudioFormatDescription;` — If valid, we own the memory and need to free it.
- L185 _private member_ `ProResTimecodeFormatDescriptionRef TimecodeFormatDescription;` — If valid, we own the memory and need to free it.
- L187 _private member_ `ProResFileWriterRef FileWriter;` — If valid, we own the memory and need to free it.
- L189 _private member_ `PREncoderRef Encoder;` — If valid, we own the memory and need to free it.
- L192 _private member_ `PRTime CurrentVideoTime;` — Time in the file for video tracks. Incremented by 1 frame for each new video sample. Video samples come in one at a time so this keeps track of how many have been added.
- L194 _private member_ `PRTime CurrentAudioTime;` — Time in the file for audio tracks. Uses a different timescale than Video, as it's in AudioSampleRate.
- L197 _private member_ `int32 MaxCompressedFrameSize;`
- L198 _private member_ `int32 TargetCompressedFrameSize;`
- L199 _private member_ `uint32 AudioSamplesPerFrame;`

#### struct `FAppleProResEncoder::FTimecodePayload`  
`struct FTimecodePayload : IImagePixelDataPayload`  
_L139-142_
- inherits: `IImagePixelDataPayload`
- L141 _public member_ `int32 ReferenceFrameNumber;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define __LLP64__ 1` — THIRDPARTY_INCLUDES_START
- L18 _macro_ `#define UE_API APPLEPRORESMEDIA_API`
