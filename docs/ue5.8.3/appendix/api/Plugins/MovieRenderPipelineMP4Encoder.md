# Plugins / MovieRenderPipelineMP4Encoder

- module root: `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineMP4Encoder`
- headers: 6; symbols: 150
- symbol kinds: class=5, enum=3, enumerator=26, function=18, macro=3, member=61, prototype=31, struct=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PublicDependencyModuleNames: MovieRenderPipelineCore, MovieRenderPipelineSettings, OpenColorIO, SlateCore

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineMP4Encoder/Private/GenericPlatform/MoviePipelineMP4Encoder.h` (Private)


#### class `FMoviePipelineMP4Encoder`  
`class FMoviePipelineMP4Encoder`  
_L15-41_
- desc: Dummy implementation for unsupported platforms which returns failure if used, to avoid doing rendering work and then having no output. This should have a matching public API to the implementation in the other platform folders.
- L18 _public function_ `FMoviePipelineMP4Encoder(const FMoviePipelineMP4EncoderOptions& InOptions) : Options(InOptions)`
- L22 _public prototype_ `~FMoviePipelineMP4Encoder() = default;`
- L24 _public function_ `bool Initialize()`
- L29 _public function_ `void Finalize()`
- L30 _public function_ `bool WriteFrame(const uint8* InFrameData)`
- L31 _public function_ `bool WriteAudioSample(const TArrayView<int16>& InAudioSamples)`
- L32 _public function_ `const FMoviePipelineMP4EncoderOptions& GetOptions() const`
- L33 _public function_ `bool IsInitialized() const`
- L37 _private prototype_ `bool InitializeEncoder();` — Configure and initialize the output file
- L40 _private member_ `FMoviePipelineMP4EncoderOptions Options;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineMP4Encoder/Private/Graph/MovieGraphMP4EncoderNodeCustomization.h` (Private)


#### class `FMovieGraphMP4EncoderNodeNodeCustomization`  
`class FMovieGraphMP4EncoderNodeNodeCustomization : public IDetailCustomization`  
_L16-65_
- inherits: `IDetailCustomization`
- desc: Customize how the MP4 Encoder node appears in the details panel.
- L19 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L26 _protected function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override`
- L31 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "MovieRenderPipelineMP4Encoder"`
- L36 _function_ `` (scope `FMovieGraphMP4EncoderNodeNodeCustomization::CustomizeDetails`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineMP4Encoder/Private/MoviePipelineMP4EncoderCommon.h` (Private)


#### enum `EMoviePipelineMP4EncodeProfile`  
`enum class EMoviePipelineMP4EncodeProfile : uint8`  
_L15-20_
- reflection: `UENUM(BlueprintType)`
- desc: Which encoding profile should be used for encoding? A higher profile usually means better quality for a given bitrate, but may not play back on older hardware.
- L17 _public enumerator_ `Baseline`
- L18 _public enumerator_ `Main`
- L19 _public enumerator_ `High`

#### enum `EMoviePipelineMP4EncodeLevel`  
`enum class EMoviePipelineMP4EncodeLevel : uint8`  
_L29-50_
- reflection: `UENUM(BlueprintType)`
- desc: A higher level generally results in a higher quality for a given bitrate, but a higher level requires newer encoders and decoders. Auto will let the encoder choose an appropriate one given the other parameters and is generally the best choice short of external needs.
- L32 _public enumerator_ `Auto = 0` — Let the encoder choose the best level based on other parameters.
- L33 _public enumerator_ `Level1 = 10`
- L34 _public enumerator_ `Level1_b = 11`
- L35 _public enumerator_ `Level1_1 = 11`
- L36 _public enumerator_ `Level1_2 = 12`
- L37 _public enumerator_ `Level1_3 = 13`
- L38 _public enumerator_ `Level2 = 20`
- L39 _public enumerator_ `Level2_1 = 21`
- L40 _public enumerator_ `Level2_2 = 22`
- L41 _public enumerator_ `Level3 = 30`
- L42 _public enumerator_ `Level3_1 = 31`
- L43 _public enumerator_ `Level3_2 = 32`
- L44 _public enumerator_ `Level4 = 40`
- L45 _public enumerator_ `Level4_1 = 41`
- L46 _public enumerator_ `Level4_2 = 42`
- L47 _public enumerator_ `Level5 = 50`
- L48 _public enumerator_ `Level5_1 = 51`
- L49 _public enumerator_ `Level5_2 = 52`

#### enum `EMoviePipelineMP4EncodeRateControlMode`  
`enum class EMoviePipelineMP4EncodeRateControlMode : uint8`  
_L53-69_
- reflection: `UENUM(BlueprintType)`
- L56 _public enumerator_ `ConstantQP UMETA(Hidden)` — Automatically chooses a bit rate to target the given quality. Valid ranges are 16-51.
- L59 _public enumerator_ `Quality` — Automatically chooses a bit rate to target the given quality.
- L62 _public enumerator_ `VariableBitRate` — Attempts to achieve a given mean bitrate for every frame. Can result in higher bitrates than necessary on simple frames, and lower bitrates than required on complex frames. Unconstrained and single-pass.
- L65 _public enumerator_ `VariableBitRate_Constrained UMETA(Hidden)` — Uses a variable bitrate that attempts to achieve a given mean bitrate, but can use a higher bitrate (with no max) on a given frame if needed. Value is in bytes per second.
- L68 _public enumerator_ `ConstantBitRate UMETA(Hidden)` — Uses a variable bitrate that attempts to achieve a given mean bitrate, but can specify a maximum bitrate at which point quality will drop if needed. Value is in bytes per second.

#### struct `FMoviePipelineMP4EncoderOptions`  
`struct FMoviePipelineMP4EncoderOptions`  
_L71-132_
- L73 _public function_ `FMoviePipelineMP4EncoderOptions() : OutputFilename() , Width(0) , Height(0) , FrameRate(30, 1) , bIncludeAudio(true) , AudioChannelCount(2) , AudioSampleRate(48000) , AudioAverageBitRate(24000)`
- L92 _public member_ `FString OutputFilename;` — The absolute path on disk to try and save the video file to.
- L95 _public member_ `uint32 Width;` — The width of the video file.
- L98 _public member_ `uint32 Height;` — The height of the video file.
- L101 _public member_ `FFrameRate FrameRate;` — Frame Rate of the output video.
- L104 _public member_ `bool bIncludeAudio;` — If false, then audio tracks will not be written and calls to WriteAudioSample will be ignored.
- L107 _public member_ `uint32 AudioChannelCount;` — Number of audio channels for the audio track.
- L110 _public member_ `uint32 AudioSampleRate;` — Number of samples per second (ie: 48'000) for the audio track.
- L113 _public member_ `uint32 AudioAverageBitRate;` — Average bitrate for audio track. (in bytes-per-second). Only supported values are 12'000, 16'000, 20'000, and 24'000
- L116 _public member_ `uint32 CommonMeanBitRate;` — Average bytes per second for ConstantBitRate, VariableBitRate_Constrained, VariableBitRate_Unconstrained rate control modes.
- L118 _public member_ `uint32 CommonMaxBitRate;` — Maximum bytes per second for VariableBitRate_Constrained
- L120 _public member_ `uint32 CommonQualityVsSpeed;` — Quality vs. Speed tradeoff during encode. 0 is faster but worse encode, 100 is slower but higher quality.
- L122 _public member_ `uint32 CommonConstantRateFactor;` — If using Constant Quality, what is the CRF value? 16-51 is the valid range.
- L125 _public member_ `EMoviePipelineMP4EncodeProfile EncodingProfile;` — Which profile should be used when encoding?
- L128 _public member_ `EMoviePipelineMP4EncodeLevel EncodingLevel;` — What level should the profile use?
- L131 _public member_ `EMoviePipelineMP4EncodeRateControlMode EncodingRateControl;` — Which encoding rate control method should be used?

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineMP4Encoder/Private/Windows/MoviePipelineMP4Encoder.h` (Private)


#### class `FMoviePipelineMP4Encoder`  
`class FMoviePipelineMP4Encoder`  
_L15-63_
- desc: Takes in 8-bit RGBA frames which have had an sRGB gamut applied, and outputs a YUV 4:2:0 encoded video. Targeted at non-realtime applications (ie: movie rendering) and not realtime encoding. Experimental. This should have a matching public API to the implementation in the other platform folders.
- L18 _public prototype_ `FMoviePipelineMP4Encoder(const FMoviePipelineMP4EncoderOptions& InOptions);`
- L19 _public prototype_ `~FMoviePipelineMP4Encoder();`
- L22 _public prototype_ `bool Initialize();` — Call to initialize the Sink Writer. This must be done before attempting to write data to it.
- L25 _public prototype_ `void Finalize();` — Finalize the video file and finish writing it to disk. Called by the destructor if not automatically called.
- L28 _public prototype_ `bool WriteFrame(const uint8* InFrameData);` — Appends a new frame onto the output file.
- L30 _public prototype_ `bool WriteAudioSample(const TArrayView<int16>& InAudioSamples);` — Appends a new audio sample onto the audio stream.
- L32 _public function_ `const FMoviePipelineMP4EncoderOptions& GetOptions() const`
- L34 _public function_ `bool IsInitialized() const`
- L38 _private prototype_ `bool InitializeEncoder();` — Configure and initialize the output file
- L42 _private member_ `FMoviePipelineMP4EncoderOptions Options;` — Input/Output options this writer was initialized with.
- L45 _private member_ `bool bInitialized;` — Has Initialize been successfully called?
- L48 _private member_ `bool bFinalized;` — Has Finalize been called?
- L51 _private member_ `uint64 NumVideoSamplesWritten;` — How many video samples (frames) have we written so far?
- L54 _private member_ `uint64 NumAudioSamplesWritten;` — How many audio samples (frames) have we written so far?
- L57 _private member_ `struct IMFSinkWriter* SinkWriter;` — The sink writer we are writing samples to.
- L60 _private member_ `uint32 VideoStreamIndex;` — Stream index for video within the Sink Writer
- L62 _private member_ `uint32 AudioStreamIndex;` — Stream index for audio within the Sink Writer

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineMP4Encoder/Public/Graph/MovieGraphMP4EncoderNode.h` (Public)


#### class `UMovieGraphMP4EncoderNode`  
`class UMovieGraphMP4EncoderNode final : public UMovieGraphVideoOutputNode, public IMovieGraphEvaluationNodeInjector`  
_L15-197_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphVideoOutputNode,IMovieGraphEvaluationNodeInjector`
- desc: A node which can output H264 mp4 files.
- L20 _public prototype_ `UMovieGraphMP4EncoderNode();`
- L23 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L24 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L25 _public prototype_ `virtual FText GetKeywords() const override;`
- L26 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L28 _public prototype_ `virtual FText GetBasicConfigShortDisplayName() const override;`
- L33 _protected prototype_ `virtual TUniquePtr<MovieRenderGraph::IVideoCodecWriter> Initialize_GameThread(const FMovieGraphVideoNodeInitializationContext& InInitializationContext) override;` — UMovieGraphVideoOutputNode Interface
- L34 _protected prototype_ `virtual bool Initialize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L35 _protected prototype_ `virtual void WriteFrame_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter, FImagePixelData* InPixelData, TArray<FMovieGraphPassData>&& InCompositePasses, TObjectPtr<UMovieGraphEvaluatedConfig> InEvaluatedConfig, const FString& InBranchName) override;`
- L36 _protected prototype_ `virtual void BeginFinalize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L37 _protected prototype_ `virtual void Finalize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L38 _protected prototype_ `virtual const TCHAR* GetFilenameExtension() const override;`
- L39 _protected prototype_ `virtual bool IsAudioSupported() const override;`
- L43 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;` — UMovieGraphSettingNode Interface
- L47 _protected prototype_ `virtual void InjectNodesPostEvaluation(const FName& InBranchName, UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<UMovieGraphSettingNode*>& OutInjectedNodes) override;` — IMovieGraphEvaluationNodeInjector Interface
- L58 _protected member_ `TWeakObjectPtr<UMovieGraphPipeline> CachedPipeline;` — The pipeline that is running this node.
- L62 _public member_ `uint8 bOverride_EncodingRateControl : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L65 _public member_ `uint8 bOverride_AverageBitrateInMbps : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L68 _public member_ `uint8 bOverride_MaxBitrateInMbps : 1;` — `UPROPERTY(BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L71 _public member_ `uint8 bOverride_ConstantRateFactor : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L74 _public member_ `uint8 bOverride_EncodingProfile : 1;` — `UPROPERTY(BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L77 _public member_ `uint8 bOverride_EncodingLevel : 1;` — `UPROPERTY(BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L80 _public member_ `uint8 bOverride_bIncludeAudio : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L83 _public member_ `uint8 bOverride_OCIOConfiguration : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L86 _public member_ `uint8 bOverride_OCIOContext : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L89 _public member_ `uint8 bOverride_bEnableBurnIn : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L92 _public member_ `uint8 bOverride_BurnInClass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L95 _public member_ `uint8 bOverride_bCompositeOntoFinalImage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L98 _public member_ `uint8 bOverride_BurnInFileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L105 _public member_ `EMoviePipelineMP4EncodeRateControlMode EncodingRateControl = EMoviePipelineMP4EncodeRateControlMode::VariableBitRate;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "H.264", meta=(EditCondition="bOverride_EncodingRateControl"))` — Specifies the bitrate control method used by the encoder. Quality lets the user target a given quality without concern to the filesize, while Variable targets an average bit rate per frame.
- L115 _public member_ `float AverageBitrateInMbps = 8.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "H.264", meta=(ClampMin=0.1, UIMin=0.1, UIMax=50, EditCondition="bOverride_AverageBitrateInMbps"))` — What is the average bitrate the encoder should target per second? Value is in Megabits per Second, so a value of 8 will become 8192Kbps (kilobits per second). Higher resolutions and higher framerates need higher bitrates, reasonable starting values are 8 for 1080p30, 45 for 4k. Only applies to encoding modes not related to Quality.
- L127 _public member_ `float MaxBitrateInMbps = 16.f;` — `UPROPERTY(BlueprintReadWrite, Category = "H.264", meta = (ClampMin = 0.1, UIMin = 0.1, UIMax = 50, EditCondition = "bOverride_MaxBitrateInMbps"))` — When using VariableBitRate_Constrained, what is the maximum bitrate that the encoder can briefly use for more complex scenes, while still trying to maintain the average set in AverageBitrateInMbps. In theory the maximum should be twice the average, but often in practice a smaller difference of 3-6Mbps is sufficient. Only applies to constrained max bit rate. Not exposed to the UI because it is expected most users do not need to change this, but is still available to be scripted.
- L138 _public member_ `int32 ConstantRateFactor = 20;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "H.264", meta=(ClampMin=16, UIMin=16, ClampMax=51, UIMax=51, EditCondition="bOverride_ConstantRateFactor"))` — What is the Constant Rate Factor (CRF) when targeting a specific quality. Values of 17-18 are generally considered perceptually lossless, while higher values produce smaller files with lower quality results. There is an absolute maximum value range of [16-51], where 16 is the highest quality possible and 51 is the lowest quality. This scale is logarithmic, so small changes can result in large differences in quality, and filesize cost. Only applies to Quality encoding rate control mode.
- L146 _public member_ `EMoviePipelineMP4EncodeProfile EncodingProfile = EMoviePipelineMP4EncodeProfile::High;` — `UPROPERTY(BlueprintReadWrite, Category = "H.264", meta=(AdvancedDisplay, EditCondition="bOverride_EncodingProfile"))` — A higher profile generally results in a better quality video for the same bitrate, but may not be supported for playback on old devices. Not exposed to the UI because it is expected most users do not need to change this, but is still available to be scripted.
- L155 _public member_ `EMoviePipelineMP4EncodeLevel EncodingLevel = EMoviePipelineMP4EncodeLevel::Auto;` — `UPROPERTY(BlueprintReadWrite, Category = "H.264", meta=(AdvancedDisplay, EditCondition="bOverride_EncodingLevel"))` — A higher encode level generally results in a better quality video for the same bitrate, but may not be supported for playback on old devices. Auto will let the encoder automatically select the best level given the resolution, profile, and bitrate. Not exposed to the UI because it is expected most users do not need to change this, but is still available to be scripted.
- L159 _public member_ `bool bIncludeAudio = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "H.264", meta = (EditCondition = "bOverride_bIncludeAudio"))` — If true, audio will be included in the video file.
- L170 _public member_ `FOpenColorIODisplayConfiguration OCIOConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", DisplayName="OCIO Configuration", meta = (DisplayAfter = "FileNameFormat", EditCondition = "bOverride_OCIOConfiguration"))` — OCIO configuration/transform settings. Note: There are differences from the previous implementation in MRQ given that we are now doing CPU-side processing. 1) This feature only works on desktop platforms when the OpenColorIO library is available. 2) Users are now responsible for setting the renderer output space to Final Color (HDR) in Linear Working Color Space (SCS_FinalColorHDR) by disabling the Tone Curve setting on the renderer node.
- L180 _public member_ `TMap<FString, FString> OCIOContext;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", DisplayName = "OCIO Context", meta = (DisplayAfter = "OCIOConfiguration", EditCondition = "bOverride_OCIOContext"))` — OCIO context of key-value string pairs, typically used to apply shot-specific looks (such as a CDL color correction, or a 1D grade LUT). Notes: 1) If a configuration asset base context was set, it remains active but can be overridden here with new key-values. 2) Format tokens such as {shot_name} are supported and will get resolved before submission.
- L184 _public member_ `bool bEnableBurnIn = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bEnableBurnIn"))` — If true, this output node will also generate a burn-in.
- L188 _public member_ `FSoftClassPath BurnInClass = FSoftClassPath(TEXT("/Mov` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Burn In", meta=(MetaClass="/Script/MovieRenderPipelineCore.MovieGraphBurnInWidget", EditCondition="bOverride_BurnInClass"))` — The widget that the burn-in should use.
- L192 _public member_ `bool bCompositeOntoFinalImage = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bCompositeOntoFinalImage"))` — If true, the burn-in that's generated will be composited onto this output. Otherwise, the burn-in will be written to a different file.
- L196 _public member_ `FString BurnInFileNameFormat = TEXT("{se` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_BurnInFileNameFormat", MrgTokenAutocomplete))` — The file name format used for writing out the burn-in video (if not composited).

#### struct `UMovieGraphMP4EncoderNode::FMP4CodecWriter`  
`struct FMP4CodecWriter : public MovieRenderGraph::IVideoCodecWriter`  
_L51-55_
- inherits: `MovieRenderGraph::IVideoCodecWriter`
- L53 _public member_ `bool bSkipColorConversions = false;`
- L54 _public member_ `TUniquePtr<FMoviePipelineMP4Encoder> Writer;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIERENDERPIPELINEMP4ENCODER_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineMP4Encoder/Public/MoviePipelineMP4EncoderOutput.h` (Public)


#### class `UMoviePipelineMP4EncoderOutput`  
`class UMoviePipelineMP4EncoderOutput final : public UMoviePipelineVideoOutputBase`  
_L14-107_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineVideoOutputBase`
- L18 _private function_ `UMoviePipelineMP4EncoderOutput() : UMoviePipelineVideoOutputBase()`
- L25 _protected prototype_ `virtual TUniquePtr<MovieRenderPipeline::IVideoCodecWriter> Initialize_GameThread(const FString& InFileName, FIntPoint InResolution, EImagePixelType InPixelType, ERGBFormat InPixelFormat, uint8 InBitDepth, uint8 InNumChannels) override;` — UMoviePipelineVideoOutputBase Interface
- L26 _protected prototype_ `virtual bool Initialize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter) override;`
- L27 _protected prototype_ `virtual void WriteFrame_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter, FImagePixelData* InPixelData, TArray<MoviePipeline::FCompositePassInfo>&& InCompositePasses) override;`
- L28 _protected prototype_ `virtual void BeginFinalize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter);`
- L29 _protected prototype_ `virtual void Finalize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter);`
- L30 _protected function_ `virtual const TCHAR* GetFilenameExtension() const override`
- L31 _protected function_ `virtual bool IsAudioSupported() const override`
- L35 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;` — UMoviePipelineSetting Interface
- L40 _protected function_ `virtual FText GetDisplayText() const override`
- L51 _public member_ `EMoviePipelineMP4EncodeRateControlMode EncodingRateControl = EMoviePipelineMP4EncodeRateControlMode::Quality;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — Specifies the bitrate control method used by the encoder. Quality lets the user target a given quality without concern to the filesize, while Average/Constant modes allow you to suggest desired sizes, though the resulting file may still end up larger or smaller than specified.
- L60 _public member_ `float AverageBitrateInMbps = 8.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta=(ClampMin=0.1, UIMin=0.1, UIMax=50, EditCondition="EncodingRateControl == EMoviePipelineMP4EncodeRateControlMode::VariableBitRate", EditConditionHides))` — What is the average bitrate the encoder should target per second? Value is in Megabits per Second, so a value of 8 will become 8192Kbps (kilobits per second). Higher resolutions and higher framerates need higher bitrates, reasonable starting values are 8 for 1080p30, 45 for 4k. Only applies to encoding modes not related to Quality.
- L70 _public member_ `float MaxBitrateInMbps = 16.f;` — `UPROPERTY(BlueprintReadWrite, Category = "Settings", meta = (ClampMin = 0.1, UIMin = 0.1, UIMax = 50))` — When using VariableBitRate_Constrained, what is the maximum bitrate that the encoder can briefly use for more complex scenes, while still trying to maintain the average set in AverageBitrateInMbps. In theory the maximum should be twice the average, but often in practice a smaller difference of 3-6Mbps is sufficient. Not exposed to the UI because it is expected most users do not need to change this, but is still available to be scripted.
- L79 _public member_ `int32 ConstantRateFactor = 20;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta=(ClampMin=16, UIMin=16, ClampMax=51, UIMax=51, EditCondition="EncodingRateControl == EMoviePipelineMP4EncodeRateControlMode::Quality", EditConditionHides))` — What is the Constant Rate Factor (CRF) when targeting a specific quality. Values of 17-18 are generally considered perceptually lossless, while higher values produce smaller files with lower quality results. There is an absolute maximum value range of [16-51], where 16 is the highest quality possible and 51 is the lowest quality. This scale is logarithmic, so small changes can result in large differences in quality, and filesize cost.
- L87 _public member_ `EMoviePipelineMP4EncodeProfile EncodingProfile = EMoviePipelineMP4EncodeProfile::High;` — `UPROPERTY(BlueprintReadWrite, Category = "Settings", meta=(AdvancedDisplay))` — A higher profile generally results in a better quality video for the same bitrate, but may not be supported for playback on old devices. Not exposed to the UI because it is expected most users do not need to change this, but is still available to be scripted.
- L96 _public member_ `EMoviePipelineMP4EncodeLevel EncodingLevel = EMoviePipelineMP4EncodeLevel::Auto;` — `UPROPERTY(BlueprintReadWrite, Category = "Settings", meta=(AdvancedDisplay))` — A higher encode level generally results in a better quality video for the same bitrate, but may not be supported for playback on old devices. Auto will let the encoder automatically select the best level given the resolution, profile, and bitrate. Not exposed to the UI because it is expected most users do not need to change this, but is still available to be scripted.
- L100 _public member_ `bool bIncludeAudio = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — If true, audio will be included in the video file.

#### struct `UMoviePipelineMP4EncoderOutput::FMP4CodecWriter`  
`struct FMP4CodecWriter : public MovieRenderPipeline::IVideoCodecWriter`  
_L103-106_
- inherits: `MovieRenderPipeline::IVideoCodecWriter`
- L105 _public member_ `TUniquePtr<FMoviePipelineMP4Encoder> Writer;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINEMP4ENCODER_API`
