# Plugins / MovieRenderPipelineTmvEncoder

- module root: `Plugins/Media/TmvMediaUtils/Source/MovieRenderPipelineTmvEncoder`
- headers: 2; symbols: 74
- symbol kinds: class=2, enum=1, enumerator=2, function=4, member=39, prototype=25, struct=1
- PrivateDependencyModuleNames: ApvMedia, Core, CoreUObject, Engine, ImageCore, MovieRenderPipelineCore, OpenColorIO, RHI, SlateCore, TmvMedia

### `Plugins/Media/TmvMediaUtils/Source/MovieRenderPipelineTmvEncoder/Private/Graph/MovieGraphTmvEncoderNode.h` (Private)


#### enum `ETmvEncoderNodeOutputType`  
`enum class ETmvEncoderNodeOutputType : uint8`  
_L21-27_
- reflection: `UENUM(BlueprintType)`
- desc: Selection of the output types, defined as the extension (apv1, tmv). @remark This enum is different conceptually then the internal tmv output format which is a muxer enum (container, file sequence) not directly related to file extensions.
- L24 _public enumerator_ `Apv1ImageSequence UMETA(DisplayName="APV1 Image Sequence")` — Output each frame as a separate file in Apv1 format.
- L26 _public enumerator_ `TmvVideoFile UMETA(DisplayName="TMV Video File")` — Mux freams into a single tmv container file.

#### class `UMovieGraphTmvEncoderNode`  
`class UMovieGraphTmvEncoderNode final : public UMovieGraphVideoOutputNode, public IMovieGraphEvaluationNodeInjector`  
_L31-259_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieGraphVideoOutputNode,IMovieGraphEvaluationNodeInjector`
- desc: A node which can output TMV (Tiled-Mipmap Video) files using the APV encoder.
- L36 _public prototype_ `UMovieGraphTmvEncoderNode();`
- L39 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L40 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L41 _public prototype_ `virtual FText GetKeywords() const override;`
- L42 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L43 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L46 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L47 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L53 _protected prototype_ `virtual TUniquePtr<MovieRenderGraph::IVideoCodecWriter> Initialize_GameThread(const FMovieGraphVideoNodeInitializationContext& InInitializationContext) override;`
- L54 _protected prototype_ `virtual bool Initialize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L55 _protected prototype_ `virtual void WriteFrame_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter, FImagePixelData* InPixelData, TArray<FMovieGraphPassData>&& InCompositePasses, TObjectPtr<UMovieGraphEvaluatedConfig> InEvaluatedConfig, const FString& InBranchName) override;`
- L56 _protected prototype_ `virtual void BeginFinalize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L57 _protected prototype_ `virtual void Finalize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) override;`
- L58 _protected prototype_ `virtual const TCHAR* GetFilenameExtension() const override;`
- L59 _protected prototype_ `virtual bool IsAudioSupported() const override;`
- L64 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L68 _public prototype_ `virtual void InjectNodesPostEvaluation(const FName& InBranchName, UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<UMovieGraphSettingNode*>& OutInjectedNodes) override;`
- L75 _protected prototype_ `bool IsOcioEnabledRuntime() const;` — Returns true if the OCIO configuration is enabled in the runtime (evaluated) context.
- L81 _protected prototype_ `bool IsOcioEnabledEditor() const;` — Returns true if the OCIO configuration is enabled in the editor context (i.e. called on the edited node, not evaluated).
- L91 _protected member_ `TWeakObjectPtr<UMovieGraphPipeline> CachedPipeline;` — The pipeline that is running this node.
- L97 _public member_ `uint8 bOverride_OutputType : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L100 _public member_ `uint8 bOverride_bEnableMipMapping : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L103 _public member_ `uint8 bOverride_TileSize : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L106 _public member_ `uint8 bOverride_Profile : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L109 _public member_ `uint8 bOverride_Band : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L112 _public member_ `uint8 bOverride_Preset : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L115 _public member_ `uint8 bOverride_NumThreads : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L118 _public member_ `uint8 bOverride_DestinationColorSpace : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L121 _public member_ `uint8 bOverride_DestinationEncoding : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L124 _public member_ `uint8 bOverride_ReferenceWhite : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L127 _public member_ `uint8 bOverride_YuvMatrix : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L130 _public member_ `uint8 bOverride_YuvMatrixRange : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L133 _public member_ `uint8 bOverride_OCIOConfiguration : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L136 _public member_ `uint8 bOverride_OCIOContext : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L139 _public member_ `uint8 bOverride_bEnableBurnIn : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L142 _public member_ `uint8 bOverride_BurnInClass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L145 _public member_ `uint8 bOverride_bCompositeOntoFinalImage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L148 _public member_ `uint8 bOverride_BurnInFileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L154 _public member_ `ETmvEncoderNodeOutputType OutputType = ETmvEncoderNodeOutputType::TmvVideoFile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output", meta = (EditCondition = "bOverride_OutputType", DisplayPriority = 100))` — Select whether to output a single TMV container file or individual files per frame.
- L163 _public member_ `bool bEnableMipMapping = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APV", meta = (EditCondition = "bOverride_bEnableMipMapping"))` — If checked, mip maps will be generated and encoded in the final destination. The encoder may restrict the generated mip chain depending on the format requirements.
- L171 _public member_ `FIntPoint TileSize = FIntPoint(256, 256);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APV", meta = (EditCondition = "bOverride_TileSize", ClampMin = "0.0"))` — Dimensions of a tile in pixels. The tile size determines parallelism and performance. Frames are divided into rectangular tiles that can be encoded and decoded simultaneously, enabling high throughput on multicore processors.
- L178 _public member_ `EApvMediaProfile Profile = EApvMediaProfile::YCbCr422_10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APV", meta = (EditCondition = "bOverride_Profile"))` — Specify the color/chroma profile, includes bitdepth. Input video will be converted to the given profile.
- L185 _public member_ `EApvMediaBand Band = EApvMediaBand::Band2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APV", meta = (EditCondition = "bOverride_Band"))` — Coded data rate band setting. If the bitrate is not specified otherwise, this determines the max coded data rate (higher band leads to higher bit rate).
- L189 _public member_ `EApvMediaPreset Preset = EApvMediaPreset::Medium;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APV", meta = (EditCondition = "bOverride_Preset"))` — Specify the encoding optimization level.
- L193 _public member_ `int32 NumThreads = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "APV", meta = (EditCondition = "bOverride_NumThreads", ClampMin = "0"))` — Number of worker threads to encode tiles (0 = automatically use the available number of cores).
- L199 _public member_ `ETextureColorSpace DestinationColorSpace = ETextureColorSpace::TCS_sRGB;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Management", meta = (EditCondition = "bOverride_DestinationColorSpace", ValidEnumValues = "TCS_sRGB, TCS_Rec2020"))` — Specify the destination color space.
- L203 _public member_ `ETmvMediaEncoderEncoding DestinationEncoding = ETmvMediaEncoderEncoding::sRGB;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Management", meta = (EditCondition = "bOverride_DestinationEncoding", ValidEnumValues = "Linear, sRGB, ST2084, SLog3, HLG"))` — Specify the destination color encoding.
- L207 _public member_ `ETmvMediaEncoderReferenceWhite ReferenceWhite = ETmvMediaEncoderReferenceWhite::BT2408;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Management", meta = (EditCondition = "bOverride_ReferenceWhite && (DestinationEncoding == ETmvMediaEncoderEncoding::ST2084 || DestinationEncoding == ETmvMediaEncoderEncoding::HLG)", EditConditionHides))` — Reference-white standard used to scale UE scene-linear 1.0 to diffuse white.
- L211 _public member_ `ETmvMediaEncoderColorMatrix YuvMatrix = ETmvMediaEncoderColorMatrix::Rec709;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Management", meta = (EditCondition = "bOverride_YuvMatrix"))` — Specify the YUV encoding color matrix.
- L215 _public member_ `ETmvMediaEncoderColorMatrixRange YuvMatrixRange = ETmvMediaEncoderColorMatrixRange::Full;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Management", meta = (EditCondition = "bOverride_YuvMatrixRange"))` — Specify the YUV encoding color matrix range.
- L230 _public member_ `FOpenColorIODisplayConfiguration OCIOConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", DisplayName="OCIO Configuration", meta = (DisplayAfter = "FileNameFormat", EditCondition = "bOverride_OCIOConfiguration"))` — OCIO configuration/transform settings. If OCIO transform is enabled, the builtin color transform in Color Management will be ignored. Note: There are differences from the previous implementation in MRQ given that we are now doing CPU-side processing. 1) This feature only works on desktop platforms when the OpenColorIO library is available. 2) Users are now responsible for setting the renderer output space to Final Color (HDR) in Linear Working Color Space (SCS_FinalColorHDR) by disabling the Tone Curve setting on the renderer node.
- L240 _public member_ `TMap<FString, FString> OCIOContext;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", DisplayName = "OCIO Context", meta = (DisplayAfter = "OCIOConfiguration", EditCondition = "bOverride_OCIOContext"))` — OCIO context of key-value string pairs, typically used to apply shot-specific looks (such as a CDL color correction, or a 1D grade LUT). Notes: 1) If a configuration asset base context was set, it remains active but can be overridden here with new key-values. 2) Format tokens such as {shot_name} are supported and will get resolved before submission.
- L246 _public member_ `bool bEnableBurnIn = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bEnableBurnIn"))` — If true, this output node will also generate a burn-in.
- L250 _public member_ `FSoftClassPath BurnInClass = FSoftClassPath(TEXT("/Mov` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Burn In", meta=(MetaClass="/Script/MovieRenderPipelineCore.MovieGraphBurnInWidget", EditCondition="bOverride_BurnInClass"))` — The widget that the burn-in should use.
- L254 _public member_ `bool bCompositeOntoFinalImage = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bCompositeOntoFinalImage"))` — If true, the burn-in that's generated will be composited onto this output. Otherwise, the burn-in will be written to a different file.
- L258 _public member_ `FString BurnInFileNameFormat = TEXT("{se` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_BurnInFileNameFormat", MrgTokenAutocomplete))` — The file name format used for writing out the burn-in video (if not composited).

#### struct `UMovieGraphTmvEncoderNode::FTmvCodecWriter`  
`struct FTmvCodecWriter : public MovieRenderGraph::IVideoCodecWriter`  
_L84-88_
- inherits: `MovieRenderGraph::IVideoCodecWriter`
- L87 _public member_ `TStrongObjectPtr<UTmvMediaTranscodeJob> TranscodeJob;` — Transcode job that will convert and encode the produced frames.

### `Plugins/Media/TmvMediaUtils/Source/MovieRenderPipelineTmvEncoder/Private/SampleConverter/TmvMediaFrameMipPixelDataBuffer.h` (Private)


#### class `FTmvMediaFrameMipPixelDataBuffer`  
`class FTmvMediaFrameMipPixelDataBuffer : public FTmvMediaFrameMipBuffer`  
_L13-42_
- inherits: `FTmvMediaFrameMipBuffer`
- desc: Implementation of texture cpu buffering backed by FImagePixelData.
- L17 _public prototype_ `FTmvMediaFrameMipPixelDataBuffer();` — Constructor
- L20 _public prototype_ `FTmvMediaFrameMipPixelDataBuffer(TUniquePtr<FImagePixelData>&& InImage, int32 InMipLevel);` — Construct from an existing image, using the image as backing buffer.
- L26 _public prototype_ `virtual bool RequestAllocation(const FTmvMediaFrameMipInfo& InMipInfo) override;`
- L27 _public function_ `virtual void WaitAllocation() override`
- L28 _public function_ `virtual bool TryUpdateMipInfo(const FTmvMediaFrameMipInfo& InMipInfo) override`
- L29 _public prototype_ `virtual void* GetMappedBuffer() override;`
- L30 _public prototype_ `virtual void* GetPlaneBufferForComponent(int32 InComponentIndex) override;`
- L31 _public prototype_ `virtual FShaderResourceViewRHIRef GetShaderResourceView(int32 InComponentIndex) const override;`
- L32 _public function_ `virtual void CopyTileRegions(int32 InFrameId, const FTmvMediaFrameMipInfo& InTmvMipInfo, TConstArrayView<FIntRect> InTileRegions, TConstArrayView<FTmvMediaShaderTileDesc> InTileInfos) override`
- L33 _public function_ `virtual bool IsValidForRendering() const override`
- L41 _private member_ `TArray<TUniquePtr<FImagePixelData>> PlaneImages;` — Image buffer for each plane.
