# Plugins / AvidDNxMedia

- module root: `Plugins/Media/AvidDNxMedia/Source/Source`
- headers: 5; symbols: 138
- symbol kinds: class=4, delegate=1, enum=1, enumerator=5, function=5, member=65, prototype=46, struct=7, typedef=4
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MovieRenderPipelineCore, MovieSceneCapture, OpenColorIO, Projects, SlateCore
- PublicDependencyModuleNames: DNxHR, DNxMXF, DNxUncompressed

### `Plugins/Media/AvidDNxMedia/Source/Source/Private/AvidDNxEncoderProtocol.h` (Private)


#### class `UAvidDNxEncoderProtocol`  
`class UAvidDNxEncoderProtocol : public UFrameGrabberProtocol`  
_L21-69_
- reflection: `UCLASS(meta = (DisplayName = "Avid DNx Encoder (mxf)", CommandLineID = "AvidDNx"))`
- inherits: `UFrameGrabberProtocol`
- L26 _public prototype_ `UAvidDNxEncoderProtocol(const FObjectInitializer& InObjInit);`
- L29 _public prototype_ `virtual bool SetupImpl() override;`
- L30 _public prototype_ `virtual void FinalizeImpl() override;`
- L31 _public prototype_ `virtual FFramePayloadPtr GetFramePayload(const FFrameMetrics& InFrameMetrics) override;`
- L32 _public prototype_ `virtual void ProcessFrame(FCapturedFrameData InFrame) override;`
- L36 _public member_ `bool bUncompressed;` — `UPROPERTY(config, EditAnywhere, Category = "Avid DNX Settings")`
- L39 _public member_ `uint8 NumberOfEncodingThreads;` — `UPROPERTY(config, EditAnywhere, Category = "Avid DNX Settings", meta = (ClampMin = "1", UIMin = "1", ClampMax = "64", UIMax = "64"))`
- L48 _private prototype_ `bool InitializeEncoder();`
- L49 _private prototype_ `bool InitializeUncompressedEncoder(unsigned int& OutEncodedBufferSize);`
- L50 _private prototype_ `bool InitializeHRencoder(unsigned int& OutEncodedBufferSize);`
- L51 _private prototype_ `bool InitializeMXFwriter();`
- L53 _private prototype_ `void DestroyEncoder();`
- L54 _private prototype_ `void DestroyMXFwriter();`
- L57 _private member_ `bool bEncoderIsUncompressed;` — cached from bUncompressed
- L59 _private member_ `DNX_Encoder DNxHRencoder;`
- L61 _private member_ `DNXUncompressed_Encoder* DNxUncEncoder;`
- L62 _private member_ `DNXUncompressed_CompressedParams_t DNxUncCompressedParams;`
- L63 _private member_ `DNXUncompressed_UncompressedParams_t DNxUncUncompressedParams;`
- L65 _private member_ `DNXMXF_Writer* MXFwriter;`
- L67 _private member_ `TArray<FY0CbY1Cr, TAlignedHeapAllocator<16>> SubSampledBuffer;`
- L68 _private member_ `TArray<uint8, TAlignedHeapAllocator<16>> EncodedBuffer;`

#### struct `UAvidDNxEncoderProtocol::FY0CbY1Cr`  
`struct FY0CbY1Cr`  
_L42-45_
- L44 _public member_ `uint8 Y0, Cb, Y1, Cr;`
- L44 _public member_ `uint8 Y0, Cb, Y1, Cr;`
- L44 _public member_ `uint8 Y0, Cb, Y1, Cr;`
- L44 _public member_ `uint8 Y0, Cb, Y1, Cr;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using DNX_Encoder = struct _DNX_Encoder*;`
- L18 _typedef_ `using DNXMXF_Writer = struct DNXMXF_Writer;`

### `Plugins/Media/AvidDNxMedia/Source/Source/Private/AvidDNxMediaModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvidDNxMedia, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvidDNxMedia, Log, All);`

### `Plugins/Media/AvidDNxMedia/Source/Source/Private/MovieGraphAvidDNxHRNode.h` (Private)


#### class `UMovieGraphAvidDNxHRNode`  
`class UMovieGraphAvidDNxHRNode : public UMovieGraphVideoOutputNode, public IMovieGraphEvaluationNodeInjector`  
_L15-124_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieGraphVideoOutputNode,IMovieGraphEvaluationNodeInjector`
- desc: A node which can output Avid DNxHR movies.
- L20 _public prototype_ `UMovieGraphAvidDNxHRNode();`
- L23 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L24 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L25 _public prototype_ `virtual FText GetKeywords() const override;`
- L26 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L30 _public prototype_ `virtual FText GetBasicConfigShortDisplayName() const override;` — UMovieGraphFileOutputNode Interface
- L36 _protected prototype_ `virtual TUniquePtr<MovieRenderGraph::IVideoCodecWriter> Initialize_GameThread(const FMovieGraphVideoNodeInitializationContext& InInitializationContext) override;` — UMovieGraphVideoOutputNode Interface
- L37 _protected prototype_ `virtual bool Initialize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L38 _protected prototype_ `virtual void WriteFrame_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter, FImagePixelData* InPixelData, TArray<FMovieGraphPassData>&& InCompositePasses, TObjectPtr<UMovieGraphEvaluatedConfig> InEvaluatedConfig, const FString& InBranchName) override;`
- L39 _protected prototype_ `virtual void BeginFinalize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L40 _protected prototype_ `virtual void Finalize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L41 _protected prototype_ `virtual const TCHAR* GetFilenameExtension() const override;`
- L42 _protected prototype_ `virtual bool IsAudioSupported() const override;`
- L46 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;` — UMovieGraphSettingNode Interface
- L50 _protected prototype_ `virtual void InjectNodesPostEvaluation(const FName& InBranchName, UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<UMovieGraphSettingNode*>& OutInjectedNodes) override;` — IMovieGraphEvaluationNodeInjector Interface
- L60 _protected member_ `TWeakObjectPtr<UMovieGraphPipeline> CachedPipeline;` — The pipeline that is running this node.
- L64 _public member_ `uint8 bOverride_Quality : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L67 _public member_ `uint8 bOverride_OCIOConfiguration : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L70 _public member_ `uint8 bOverride_OCIOContext : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L73 _public member_ `uint8 bOverride_bEnableBurnIn : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L76 _public member_ `uint8 bOverride_BurnInClass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L79 _public member_ `uint8 bOverride_bCompositeOntoFinalImage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L82 _public member_ `uint8 bOverride_BurnInFileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L86 _public member_ `EAvidDNxEncoderQuality Quality = EAvidDNxEncoderQuality::HQ_8bit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Avid DNxHR", meta=(EditCondition="bOverride_Quality"))` — The quality that the movie will be encoded with.
- L97 _public member_ `FOpenColorIODisplayConfiguration OCIOConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", DisplayName="OCIO Configuration", meta = (DisplayAfter = "FileNameFormat", EditCondition = "bOverride_OCIOConfiguration"))` — OCIO configuration/transform settings. Note: There are differences from the previous implementation in MRQ given that we are now doing CPU-side processing. 1) This feature only works on desktop platforms when the OpenColorIO library is available. 2) Users are now responsible for setting the renderer output space to Final Color (HDR) in Linear Working Color Space (SCS_FinalColorHDR) by disabling the Tone Curve setting on the renderer node.
- L107 _public member_ `TMap<FString, FString> OCIOContext;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", DisplayName = "OCIO Context", meta = (DisplayAfter = "OCIOConfiguration", EditCondition = "bOverride_OCIOContext"))` — OCIO context of key-value string pairs, typically used to apply shot-specific looks (such as a CDL color correction, or a 1D grade LUT). Notes: 1) If a configuration asset base context was set, it remains active but can be overridden here with new key-values. 2) Format tokens such as {shot_name} are supported and will get resolved before submission.
- L111 _public member_ `bool bEnableBurnIn = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bEnableBurnIn"))` — If true, this output node will also generate a burn-in.
- L115 _public member_ `FSoftClassPath BurnInClass = FSoftClassPath(TEXT("/Mov` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Burn In", meta=(MetaClass="/Script/MovieRenderPipelineCore.MovieGraphBurnInWidget", EditCondition="bOverride_BurnInClass"))` — The widget that the burn-in should use.
- L119 _public member_ `bool bCompositeOntoFinalImage = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bCompositeOntoFinalImage"))` — If true, the burn-in that's generated will be composited onto this output. Otherwise, the burn-in will be written to a different file.
- L123 _public member_ `FString BurnInFileNameFormat = TEXT("{se` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_BurnInFileNameFormat", MrgTokenAutocomplete))` — The file name format used for writing out the burn-in video (if not composited).

#### struct `UMovieGraphAvidDNxHRNode::FAvidWriter`  
`struct FAvidWriter : public MovieRenderGraph::IVideoCodecWriter`  
_L54-57_
- inherits: `MovieRenderGraph::IVideoCodecWriter`
- L56 _public member_ `TUniquePtr<FAvidDNxEncoder> Writer;`

### `Plugins/Media/AvidDNxMedia/Source/Source/Private/MoviePipelineAvidDNxOutput.h` (Private)


#### class `UMoviePipelineAvidDNxOutput`  
`class UMoviePipelineAvidDNxOutput : public UMoviePipelineVideoOutputBase`  
_L13-59_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMoviePipelineVideoOutputBase`
- L17 _private function_ `UMoviePipelineAvidDNxOutput() : UMoviePipelineVideoOutputBase() , bUseCompression(true) , NumberOfEncodingThreads(4)`
- L26 _protected prototype_ `virtual TUniquePtr<MovieRenderPipeline::IVideoCodecWriter> Initialize_GameThread(const FString& InFileName, FIntPoint InResolution, EImagePixelType InPixelType, ERGBFormat InPixelFormat, uint8 InBitDepth, uint8 InNumChannels) override;` — UMoviePipelineVideoOutputBase Interface
- L27 _protected prototype_ `virtual bool Initialize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter) override;`
- L28 _protected prototype_ `virtual void WriteFrame_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter, FImagePixelData* InPixelData, TArray<MoviePipeline::FCompositePassInfo>&& InCompositePasses) override;`
- L29 _protected prototype_ `virtual void BeginFinalize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter);`
- L30 _protected prototype_ `virtual void Finalize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter);`
- L31 _protected function_ `virtual const TCHAR* GetFilenameExtension() const override`
- L32 _protected function_ `virtual bool IsAudioSupported() const`
- L37 _protected function_ `virtual FText GetDisplayText() const override`
- L42 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;` — UMoviePipelineSetting Interface
- L48 _public member_ `bool bUseCompression;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Should we use a lossy compression for the output?
- L52 _public member_ `int32 NumberOfEncodingThreads;` — `UPROPERTY(EditAnywhere, meta=(UIMin=1, ClampMin=1), BlueprintReadWrite, Category = "Settings")` — How many threads should the AvidDNx Encoders use to encode frames?

#### struct `UMoviePipelineAvidDNxOutput::FAvidWriter`  
`struct FAvidWriter : public MovieRenderPipeline::IVideoCodecWriter`  
_L55-58_
- inherits: `MovieRenderPipeline::IVideoCodecWriter`
- L57 _public member_ `TUniquePtr<FAvidDNxEncoder> Writer;`

### `Plugins/Media/AvidDNxMedia/Source/Source/Public/AvidDNxEncoder/AvidDNxEncoder.h` (Public)


#### enum `EAvidDNxEncoderQuality`  
`enum class EAvidDNxEncoderQuality`  
_L23-39_
- reflection: `UENUM()`
- desc: Quality settings available for the Avid DNx encoder.
- L26 _public enumerator_ `RGB444_12bit = DNX_444_COMPRESSION_ID UMETA(DisplayName = "DNxHR RGB 444 12-bit")` — Cinema quality, 12-bit 4:4:4 RGB.
- L29 _public enumerator_ `HQX_10bit = DNX_HQX_COMPRESSION_ID UMETA(DisplayName = "DNxHR HQX 10-bit")` — High quality extended, 10-bit 4:2:2 YCbCr.
- L32 _public enumerator_ `HQ_8bit = DNX_HQ_COMPRESSION_ID UMETA(DisplayName = "DNxHR HQ 8-bit")` — High quality, 8-bit 4:2:2 YCbCr.
- L35 _public enumerator_ `SQ_8bit = DNX_SQ_COMPRESSION_ID UMETA(DisplayName = "DNxHR SQ 8-bit")` — Standard quality, 8-bit 4:2:2 YCbCr.
- L38 _public enumerator_ `LB_8bit = DNX_LB_COMPRESSION_ID UMETA(DisplayName = "DNxHR LB 8-bit")` — Low bandwidth, 8-bit 4:2:2 YCbCr.

#### struct `FAvidDNxEncoderOptions`  
`struct FAvidDNxEncoderOptions`  
_L44-86_
- desc: Options to initialize the AvidDNx encoder with. Choosing compression will choose the AvidDNxHR HD compression.
- L46 _public function_ `FAvidDNxEncoderOptions() : OutputFilename() , Width(0) , Height(0) , Quality(EAvidDNxEncoderQuality::HQ_8bit) , FrameRate(30, 1) , bCompress(true) , NumberOfEncodingThreads(0) , bDropFrameTimecode(false)`
- L58 _public member_ `FString OutputFilename;` — The absolute path on disk to try and save the video file to.
- L61 _public member_ `uint32 Width;` — The width of the video file.
- L64 _public member_ `uint32 Height;` — The height of the video file.
- L67 _public member_ `EAvidDNxEncoderQuality Quality;` — The quality setting that the encoder should use.
- L70 _public member_ `bool bConvertToSrgb;` — Whether the data should be converted to sRGB before being sent to the encoder. Should not be used when OCIO is active.
- L73 _public member_ `FFrameRate FrameRate;` — Frame Rate of the output video.
- L76 _public member_ `bool bCompress;` — Should we use a compression codec or not
- L79 _public member_ `uint32 NumberOfEncodingThreads;` — Number of Encoding Threads. Must be at least 1.
- L82 _public member_ `bool bDropFrameTimecode;` — If true, timecode track will use drop frame notation for the 29.97 frame rate.
- L85 _public member_ `FTimecode StartTimecode;` — The timecode to start the movie at.

#### class `FAvidDNxEncoder`  
`class FAvidDNxEncoder`  
_L92-168_
- desc: Encoder class that takes sRGB 8-bit RGBA data and encodes it to AvidDNxHR or AvidDNxHD before placing it in an mxf container. The mxf container writer currently implemented does not support audio, so audio writing APIs have been omitted from this encoder.
- L95 _public prototype_ `FAvidDNxEncoder(const FAvidDNxEncoderOptions& InOptions);`
- L96 _public prototype_ `~FAvidDNxEncoder();`
- L99 _public prototype_ `bool Initialize();` — Call to initialize the encoder. This must be done before attempting to write data to it.
- L102 _public prototype_ `void Finalize();` — Finalize the video file and finish writing it to disk. Called by the destructor if not automatically called.
- L105 _public prototype_ `bool WriteFrame(const uint8* InFrameData);` — Appends a new frame onto the output file (8-bit).
- L108 _public prototype_ `bool WriteFrame_16bit(const FFloat16Color* InFrameData);` — Appends a new frame onto the output file (16-bit).
- L111 _public prototype_ `const FAvidDNxEncoderOptions& GetOptions() const;` — Gets the options that the encoder was initialized with.
- L114 _private prototype_ `bool InitializeCompressedEncoder();`
- L115 _private prototype_ `bool InitializeUncompressedEncoder();`
- L116 _private prototype_ `bool InitializeMXFWriter();`
- L119 _private prototype_ `bool WriteFrame_Avid(const void* InSubSampledBuffer, int32 InSubSampledBufferSize, void* OutEncodedBuffer, int32 InEncodedBufferSize);` — Ask the AVID SDK to encode and write the buffer.
- L123 _private prototype_ `template <typename EncodedBufferType> bool WriteFrame_16bit_Impl(const FFloat16Color* InFrameData);` — Templated implementation of WriteFrame_16bit(). EncodedBufferType supports FRGB_16bit and FY0CbY1Cr_16bit.
- L145 _private member_ `FAvidDNxEncoderOptions Options;`
- L146 _private member_ `bool bInitialized;`
- L147 _private member_ `bool bFinalized;`
- L150 _private member_ `double WriteStartTimeSeconds;` — When encoding and writing a frame started.
- L153 _private member_ `double WriteEndTimeSeconds;` — When encoding and writing a frame finished.
- L156 _private member_ `int32 EncodedBufferSize;` — How big each video sample is after compression based on given settings.
- L159 _private member_ `DNX_Encoder DNxHRencoder;` — Encoder used for compressed output.
- L162 _private member_ `DNXUncompressed_Encoder* DNxUncEncoder;` — Encoder used for uncompressed output.
- L164 _private member_ `DNXUncompressed_CompressedParams_t DNxUncCompressedParams;`
- L165 _private member_ `DNXUncompressed_UncompressedParams_t DNxUncUncompressedParams;`
- L167 _private member_ `DNXMXF_Writer* MXFwriter;`

#### struct `FAvidDNxEncoder::FY0CbY1Cr`  
`struct FY0CbY1Cr`  
_L127-130_
- desc: 8-bit sub-sampled YCbCr color.
- L129 _public member_ `uint8 Y0, Cb, Y1, Cr;`
- L129 _public member_ `uint8 Y0, Cb, Y1, Cr;`
- L129 _public member_ `uint8 Y0, Cb, Y1, Cr;`
- L129 _public member_ `uint8 Y0, Cb, Y1, Cr;`

#### struct `FAvidDNxEncoder::FY0CbY1Cr_16bit`  
`struct FY0CbY1Cr_16bit`  
_L133-136_
- desc: 16-bit sub-sampled YCbCr color.
- L135 _public member_ `unsigned short Y0, Cb, Y1, Cr;`
- L135 _public member_ `unsigned short Y0, Cb, Y1, Cr;`
- L135 _public member_ `unsigned short Y0, Cb, Y1, Cr;`
- L135 _public member_ `unsigned short Y0, Cb, Y1, Cr;`

#### struct `FAvidDNxEncoder::FRGB_16bit`  
`struct FRGB_16bit`  
_L139-142_
- desc: 16-bit RGB color.
- L141 _public member_ `unsigned short R, G, B;`
- L141 _public member_ `unsigned short R, G, B;`
- L141 _public member_ `unsigned short R, G, B;`

#### Free symbols / members of external scopes

- L18 _typedef_ `using DNX_Encoder = struct _DNX_Encoder*;`
- L19 _typedef_ `using DNXMXF_Writer = struct DNXMXF_Writer;`
