# Plugins / MoviePipelineMaskRenderPass

- module root: `Plugins/MovieScene/MoviePipelineMaskRenderPass/Source/MoviePipelineMaskRenderPass`
- headers: 8; symbols: 201
- symbol kinds: class=4, enum=1, enumerator=6, function=32, macro=3, member=72, namespace=5, prototype=67, struct=11
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, ImageCore, Json, MovieScene
- PublicDependencyModuleNames: ActorLayerUtilities, MovieRenderPipelineCore, MovieRenderPipelineRenderPasses, OpenColorIO, RHI, RenderCore, SlateCore, UnrealEd

### `Plugins/MovieScene/MoviePipelineMaskRenderPass/Source/MoviePipelineMaskRenderPass/Private/Graph/MovieGraphObjectIdPass.h` (Private)


#### struct `FMovieGraphObjectIdMaskSampleAccumulationArgs`  
`struct FMovieGraphObjectIdMaskSampleAccumulationArgs : UE::MovieGraph::Rendering::FMovieGraphRenderDataAccumulationArgs`  
_L12-25_
- inherits: `UE::MovieGraph::Rendering::FMovieGraphRenderDataAccumulationArgs`
- desc: This needs to inherit from FMovieGraphRenderDataAccumulationArgs because there's a static cast in the shared baseclass used for post-render accumulation.
- L15 _public member_ `int32 NumOutputLayers;` — The number of layers that the accumulator will be generating.
- L18 _public member_ `TSharedPtr<TMap<int32, UE::MoviePipeline::FMoviePipelineHitProxyCacheValue>> CacheData;` — The mapping of a HitProxy index to the data associated with the HitProxy.
- L21 _public member_ `FString JsonManifestCachedOutput;` — Serialized Cryptomatte manifest data captured on the game thread for use by the accumulation task.
- L24 _public member_ `TWeakObjectPtr<UMovieGraphRenderPassNode> RenderPassNode;` — The node that is using this accumulator.

#### struct `FMovieGraphObjectIdPass`  
`struct FMovieGraphObjectIdPass : UE::MovieGraph::Rendering::FMovieGraphDeferredPass`  
_L28-66_
- inherits: `UE::MovieGraph::Rendering::FMovieGraphDeferredPass`
- desc: The pass type that is capable of generating Object ID (Cryptomatte) data.
- L30 _public prototype_ `FMovieGraphObjectIdPass();`
- L33 _public prototype_ `virtual void Setup(TWeakObjectPtr<UMovieGraphDefaultRenderer> InRenderer, TWeakObjectPtr<UMovieGraphImagePassBaseNode> InRenderPassNode, const FMovieGraphRenderPassLayerData& InLayer) override;` — FMovieGraphImagePassBase Interface
- L34 _public prototype_ `virtual void Teardown() override;`
- L35 _public prototype_ `virtual void GatherOutputPasses(UMovieGraphEvaluatedConfig* InConfig, TArray<FMovieGraphRenderDataIdentifier>& OutExpectedPasses) const override;`
- L36 _public prototype_ `virtual UMovieGraphImagePassBaseNode* GetParentNode(UMovieGraphEvaluatedConfig* InConfig) const override;`
- L37 _public prototype_ `virtual TSharedRef<MoviePipeline::IMoviePipelineAccumulationArgs> GetOrCreateAccumulator(TObjectPtr<UMovieGraphDefaultRenderer> InGraphRenderer, const UE::MovieGraph::FMovieGraphSampleState& InSampleState) const override;`
- L38 _public prototype_ `virtual FAccumulatorSampleFunc GetAccumulateSampleFunction() const override;`
- L42 _public prototype_ `virtual void Render(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;` — FMovieGraphDeferredPass Interface
- L46 _public prototype_ `static UE::MoviePipeline::FObjectIdAccelerationData* GetAccelerationData(const FName& InBranchName);` — Gets the ObjectID acceleration data for a specific branch (will be nullptr if not found).
- L49 _protected prototype_ `virtual UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams GetRenderTargetInitParams(const FMovieGraphTimeStepData& InTimeData, const FIntPoint& InResolution) override;`
- L53 _protected member_ `TArray<FMovieGraphRenderDataIdentifier> RenderDataIdentifiers;` — The identifiers for all object ID layers that will be generated.
- L56 _protected member_ `bool bIncludeTranslucentObjects = false;` — Whether translucent objects should be included in the IDs.
- L62 _protected member_ `bool bPrevAllowSelectTranslucent = false;` — This pass will modify Editor Settings to activate/deactivate translucent object selection (which bIncludeTranslucentObjects relies on). This is the cached value of the property in Editor Settings (bAllowSelectTranslucent) before modifying it so it can be restored post-render.
- L65 _protected member_ `inline static TMap<FName, UE::MoviePipeline::FObjectIdAccelerationData> AccelerationDataByBranch;` — ObjectID acceleration data that needs to be consistent throughout a render (cached per branch).

### `Plugins/MovieScene/MoviePipelineMaskRenderPass/Source/MoviePipelineMaskRenderPass/Private/MoviePipelineHashUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace MoviePipeline`
- L9 _function_ `static FORCEINLINE uint32 Murmur32_ROTL(uint32 InHash)` (scope `MoviePipeline`)
- L17 _function_ `static uint32 Murmur32_x86_32(const uint8* InData, const uint32 InLength)` (scope `MoviePipeline`)
- L48 _function_ `static uint32 HashNameToId(ANSICHAR* InName)` (scope `MoviePipeline`)

### `Plugins/MovieScene/MoviePipelineMaskRenderPass/Source/MoviePipelineMaskRenderPass/Private/MoviePipelineObjectIdUtils.h` (Private)


#### enum `EMoviePipelineObjectIdPassIdType`  
`enum class EMoviePipelineObjectIdPassIdType : uint8`  
_L23-47_
- reflection: `UENUM(BlueprintType)`
- L26 _public enumerator_ `Full` — As much information as the renderer can provide - unique per material per primitive in the world.
- L29 _public enumerator_ `Material` — Grouped by material name. This means different objects that use the same material will be merged.
- L32 _public enumerator_ `Actor` — Grouped by Actor Name, all materials for a given actor are merged together, and all actors with that name are merged together as well.
- L35 _public enumerator_ `ActorWithHierarchy` — Grouped by Actor Name and Folder Hierarchy. This means actors with the same name in different folders will not be merged together.
- L38 _public enumerator_ `Folder` — Grouped by Folder Name. All actors within a given folder hierarchy in the World Outliner are merged together.
- L46 _public enumerator_ `Layer UMETA(DisplayName = "Actor Layer")` — Grouped by Actor Layer (the first layer found in the AActor::Layers array). May not do what you expect if an actor belongs to multiple layers. If used within a graph, this does NOT refer to the layer within the graph. In scripting, this option is referred to as "Layer" and not "ActorLayer".

#### struct `UE::MoviePipeline::FMoviePipelineHitProxyCacheKey`  
`struct FMoviePipelineHitProxyCacheKey`  
_L51-70_
- L53 _public member_ `const AActor* Actor;`
- L54 _public member_ `const UPrimitiveComponent* PrimComponent;`
- L56 _public function_ `FMoviePipelineHitProxyCacheKey(const AActor* InActor, const UPrimitiveComponent* InComponent) : Actor(InActor) , PrimComponent(InComponent)`
- L66 _public function_ `bool operator==(const FMoviePipelineHitProxyCacheKey& Other) const`

#### struct `UE::MoviePipeline::FMoviePipelineHitProxyCacheValue`  
`struct FMoviePipelineHitProxyCacheValue`  
_L72-81_
- L74 _public member_ `const AActor* Actor;`
- L75 _public member_ `const UPrimitiveComponent* PrimComponent;`
- L76 _public member_ `int32 SectionIndex;`
- L77 _public member_ `int32 MaterialIndex;`
- L78 _public member_ `float Hash;`
- L79 _public member_ `FString HashAsString;`
- L80 _public member_ `FString ProxyName;`

#### struct `UE::MoviePipeline::FObjectIdAccelerationData`  
`struct FObjectIdAccelerationData`  
_L83-103_
- L85 _public function_ `FObjectIdAccelerationData()`
- L88 _public function_ `FORCEINLINE bool IsDefault() const`
- L96 _public member_ `TSharedPtr<TMap<int32, FMoviePipelineHitProxyCacheValue>> Cache;` — Maps a HitProxy index to the data associated with the HitProxy.
- L99 _public member_ `TSharedPtr<FJsonObject> JsonManifest;` — The Cryptomatte JSON manifest data.
- L102 _public member_ `FString JsonManifestCachedOutput;` — A cached and serialized version of the JsonManifest data.

#### struct `UE::MoviePipeline::FObjectIdMaskSampleAccumulationArgs`  
`struct FObjectIdMaskSampleAccumulationArgs : ::MoviePipeline::IMoviePipelineAccumulationArgs`  
_L105-111_
- inherits: `::MoviePipeline::IMoviePipelineAccumulationArgs`
- L107 _public member_ `TSharedPtr<FMaskOverlappedAccumulator, ESPMode::ThreadSafe> Accumulator;`
- L108 _public member_ `TSharedPtr<FMoviePipelineOutputMerger, ESPMode::ThreadSafe> OutputMerger;`
- L109 _public member_ `int32 NumOutputLayers;`
- L110 _public member_ `TSharedPtr<TMap<int32, FMoviePipelineHitProxyCacheValue>> CacheData;`

#### Free symbols / members of external scopes

- L20 _prototype_ `extern const TSparseArray<HHitProxy*>& GetAllHitProxies();`
- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace MoviePipeline` (scope `UE`)
- L61 _function_ `friend inline uint32 GetTypeHash(const FMoviePipelineHitProxyCacheKey& Key)` (scope `UE::MoviePipeline`)
- L113 _function_ `static FString GenerateProxyIdGroup(const AActor* InActor, const UPrimitiveComponent* InPrimComponent, const EMoviePipelineObjectIdPassIdType IdType, const int32 InMaterialIndex, const int32 InSectionIndex)` (scope `UE::MoviePipeline`)
- L207 _function_ `static void UpdateManifestAccelerationData(FObjectIdAccelerationData& InAccelData, const EMoviePipelineObjectIdPassIdType IdType)` (scope `UE::MoviePipeline`)
- L317 _function_ `static void RemapHitProxyIdToCryptomatteHash(const FIntPoint& InImageSize, const FColor* InHitProxyBuffer, const TSharedPtr<TMap<int32, FMoviePipelineHitProxyCacheValue>> InHitProxyCache, TArray64<float>& OutCryptomatteBuffer)` (scope `UE::MoviePipeline`)
- L324 _function_ `` (scope `UE::MoviePipeline::RemapHitProxyIdToCryptomatteHash`)
- L348 _function_ `static void UpdateCryptomatteMetadata(const FString& InJsonManifestCachedOutput, const FString& InTypenameHash, const FString& InLayerName, TMap<FString, FString>& InOutMetadataMap)` (scope `UE::MoviePipeline`)
- L356 _function_ `static void UpdateCryptomatteMetadata(const FObjectIdAccelerationData& InAccelData, const FString& InTypenameHash, const FString& InLayerName, TMap<FString, FString>& InOutMetadataMap)` (scope `UE::MoviePipeline`)

### `Plugins/MovieScene/MoviePipelineMaskRenderPass/Source/MoviePipelineMaskRenderPass/Private/MoviePipelinePanoramicBlender.h` (Private)


#### class `UE::MoviePipeline::FMoviePipelinePanoramicBlender`  
`class FMoviePipelinePanoramicBlender : public ::MoviePipeline::IMoviePipelineOutputMerger`  
_L19-47_
- inherits: `::MoviePipeline::IMoviePipelineOutputMerger`
- desc: The FMoviePipelinePanoramicBlender acts as an intermediate destination before the regular OutputMerger of the MoviePipeline. To reuse the multi-sample accumulation code, we run those accumulations and tell them to send the results to the output merger, but we've replaced the standard Movie Pipeline output merger with an instance of this class, and it then takes all the samples for the frame and blends them into one larger output image. Then once all of the samples come in for a given output image, it is passed onto the regular MoviePipeline output merger.
- L22 _public prototype_ `FMoviePipelinePanoramicBlender(TSharedPtr<::MoviePipeline::IMoviePipelineOutputMerger> InOutputMerger, const FIntPoint InOutputResolution);`
- L24 _public prototype_ `virtual FMoviePipelineMergerOutputFrame& QueueOutputFrame_GameThread(const FMoviePipelineFrameOutputState& CachedOutputState) override;`
- L25 _public prototype_ `virtual void OnCompleteRenderPassDataAvailable_AnyThread(TUniquePtr<FImagePixelData>&& InData) override;`
- L26 _public prototype_ `virtual void OnSingleSampleDataAvailable_AnyThread(TUniquePtr<FImagePixelData>&& InData) override;`
- L27 _public prototype_ `virtual void AbandonOutstandingWork() override;`
- L28 _public prototype_ `virtual int32 GetNumOutstandingFrames() const override;`
- L40 _private member_ `TArray<TUniquePtr<FPoolEntry>> PendingData;` — Pool entries are allocated as pointers on the heap so that if the array is resized while a thread is working on a previous frame, it doesn't have the memory moved out from underneath it.
- L42 _private member_ `FCriticalSection GlobalQueueDataMutex;`
- L44 _private member_ `FIntPoint OutputResolution;`
- L46 _private member_ `TWeakPtr<::MoviePipeline::IMoviePipelineOutputMerger> OutputMerger;`

#### struct `UE::MoviePipeline::FMoviePipelinePanoramicBlender::FPoolEntry`  
`struct FPoolEntry`  
_L30-36_
- L32 _public member_ `FMoviePipelinePanoramicBlenderBase Blender;`
- L33 _public member_ `bool bActive;`
- L34 _public member_ `int32 OutputFrameNumber;`
- L35 _public member_ `std::atomic<int32> NumCompletedAccumulations;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MoviePipeline` (scope `UE`)

### `Plugins/MovieScene/MoviePipelineMaskRenderPass/Source/MoviePipelineMaskRenderPass/Private/MovieRenderOverlappedMask.h` (Private)


#### struct `FMaskPixelSamples`  
`struct FMaskPixelSamples`  
_L8-22_
- L10 _public function_ `FMaskPixelSamples()`
- L19 _public member_ `int32 Id[6];`
- L20 _public member_ `float Weight[6];`
- L21 _public member_ `int32 ExtraDataOffset;`

#### struct `FMaskOverlappedAccumulator`  
`struct FMaskOverlappedAccumulator : MoviePipeline::IMoviePipelineOverlappedAccumulator`  
_L27-111_
- inherits: `MoviePipeline::IMoviePipelineOverlappedAccumulator`
- desc: Contains all the image planes for the tiles.
- L33 _public function_ `FMaskOverlappedAccumulator() : bIsInitialized(false) , PlaneSize(0,0)` — Default constructor.
- L39 _public function_ `static FName GetName()`
- L54 _public prototype_ `void InitMemory(FIntPoint InPlaneSize);` — Allocates memory. @param InTileSizeX - Horizontal tile size. @param InTileSizeY - Vertical tile size. @param InNumTilesX - Num horizontal tiles. @param InNumTilesY - Num vertical tiles. @param InNumChannels - Num Channels.
- L61 _public prototype_ `void ZeroPlanes();` — Initializes memory. Resets the memory to 0s so that we can start a new frame.
- L66 _public prototype_ `void Reset();` — Resets the memory.
- L77 _public prototype_ `void AccumulatePixelData(float* InPixelData, FIntPoint InPixelDataSize, FIntPoint InTileOffset, FVector2D InSubpixelOffset, const MoviePipeline::FTileWeight1D & WeightX, const MoviePipeline::FTileWeight1D & WeightY);` — Given a rendered tile, accumulate the data to the full size image. @param InPixelData - Raw pixel data. @param InTileOffset - Tile offset in pixels. @param InSubPixelOffset - SubPixel offset, should be in the range [0,1) @param WeightX - 1D Weights in X @param WeightY - 1D Weights in Y
- L78 _public prototype_ `void AccumulatePixelData(const TArray<float>& InLayerIds, const FColor* InPixelWeights, FIntPoint InPixelDataSize, FIntPoint InTileOffset, FVector2D InSubpixelOffset, const MoviePipeline::FTileWeight1D& WeightX, const MoviePipeline::FTileWeight1D& WeightY);`
- L80 _public prototype_ `void FetchFinalPixelDataLinearColor(TArray<TArray64<FLinearColor>>& OutPixelDataLayers) const;`
- L83 _protected prototype_ `void AccumulateSingleRank(const float* InRawData, FIntPoint InSize, FIntPoint InOffset, float SubpixelOffsetX, float SubpixelOffsetY, FIntPoint SubRectOffset, FIntPoint SubRectSize, const TArray<float>& WeightDataX, const TArray<float>& WeightDataY);`
- L90 _protected prototype_ `void AccumulateMultipleRanks(const TArray<float>& InRankIds, const FColor* InPixelWeights, FIntPoint InSize, FIntPoint InOffset, float SubpixelOffsetX, float SubpixelOffsetY, FIntPoint SubRectOffset, FIntPoint SubRectSize, const TArray<float>& WeightDataX, const TArray<float>& WeightDataY);`
- L98 _public member_ `bool bIsInitialized;` — Has InitMemory been called to allocate memory for this accumulator.
- L101 _public member_ `FIntPoint PlaneSize;` — Width and height of each tile in pixels
- L104 _public member_ `TArray64<FMaskPixelSamples> ImageData;` — The data for this image. One entry per pixel in the output image.
- L107 _public member_ `TArray64<TSharedPtr<FMaskPixelSamples, ESPMode::ThreadSafe>> SparsePixelData;` — Sparse data for pixels that overflow the initial memory block. Use the offset from ImageData to index into this.
- L110 _public member_ `FImageOverlappedPlane WeightPlane;` — A grayscale mask used to generate the falloff needed for overlapped tiles.

### `Plugins/MovieScene/MoviePipelineMaskRenderPass/Source/MoviePipelineMaskRenderPass/Public/Graph/MovieGraphObjectIdNode.h` (Public)


#### class `UMovieGraphObjectIdNode`  
`class UMovieGraphObjectIdNode final : public UMovieGraphImagePassBaseNode`  
_L16-76_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphImagePassBaseNode`
- desc: A node which outputs layers compatible with the Cryptomatte standard.
- L21 _public prototype_ `UMovieGraphObjectIdNode();`
- L24 _public prototype_ `virtual FEngineShowFlags GetShowFlags() const override;` — UMovieGraphImagePassBaseNode Interface
- L25 _public prototype_ `virtual EViewModeIndex GetViewModeIndex() const override;`
- L26 _public prototype_ `virtual bool GetAllowsShowFlagsCustomization() const override;`
- L27 _public prototype_ `virtual bool GetAllowsCompositing() const override;`
- L28 _public prototype_ `virtual bool GetForceLosslessCompression() const override;`
- L29 _public function_ `virtual int32 GetNumSpatialSamples() const override`
- L30 _public prototype_ `virtual int32 GetNumSpatialSamplesDuringWarmUp(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) const override;`
- L31 _public prototype_ `virtual void GetFormatResolveArgs(FMovieGraphResolveArgs& OutMergedFormatArgs, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier) const override;`
- L33 _public function_ `virtual bool GetOverrideAntiAliasing() const override` — The ObjectID pass doesn't support any anti-aliasing so we force it to None so that their spatial samples turn into MRG-based camera jitter.
- L34 _public function_ `virtual EAntiAliasingMethod GetAntiAliasingMethod() const override`
- L39 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L40 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L41 _public prototype_ `virtual TArray<TPair<FName, UClass*>> GetHiddenProperties() const override;`
- L45 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L49 _protected prototype_ `virtual TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase> CreateInstance() const override;` — UMovieGraphImagePassBaseNode Interface
- L54 _public member_ `uint8 bOverride_SpatialSampleCount : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L57 _public member_ `uint8 bOverride_IdType : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L60 _public member_ `uint8 bOverride_bIncludeTranslucentObjects : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L67 _public member_ `int32 SpatialSampleCount = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 1, ClampMin = 1), Category = "Settings", meta = (EditCondition = "bOverride_SpatialSampleCount"))` — How many sub-pixel jitter renders should we do per temporal sample? This can be used to achieve high sample counts without Temporal Sub-Sampling (allowing high sample counts without motion blur being enabled).
- L71 _public member_ `EMoviePipelineObjectIdPassIdType IdType = EMoviePipelineObjectIdPassIdType::Full;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", DisplayName = "ID Type", meta = (EditCondition="bOverride_IdType"))` — How objects are grouped together within the Cryptomatte.
- L75 _public member_ `bool bIncludeTranslucentObjects = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition="bOverride_bIncludeTranslucentObjects"))` — If true, translucent objects will be included in the ObjectId pass (but as an opaque layer due to limitations). False will omit translucent objects.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIEPIPELINEMASKRENDERPASS_API`

### `Plugins/MovieScene/MoviePipelineMaskRenderPass/Source/MoviePipelineMaskRenderPass/Public/MoviePipelineObjectIdPass.h` (Public)


#### class `UMoviePipelineObjectIdRenderPass`  
`class UMoviePipelineObjectIdRenderPass final : public UMoviePipelineImagePassBase`  
_L12-51_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineImagePassBase`
- L17 _public prototype_ `UMoviePipelineObjectIdRenderPass();`
- L19 _public function_ `virtual FText GetDisplayText() const override`
- L20 _public prototype_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override;`
- L21 _public prototype_ `virtual void RenderSample_GameThreadImpl(const FMoviePipelineRenderPassMetrics& InSampleState) override;`
- L22 _public prototype_ `virtual void TeardownImpl() override;`
- L23 _public prototype_ `virtual void SetupImpl(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings) override;`
- L24 _public prototype_ `virtual void GatherOutputPassesImpl(TArray<FMoviePipelinePassIdentifier>& ExpectedRenderPasses) override;`
- L25 _public function_ `virtual bool IsScreenPercentageSupported() const override`
- L26 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`
- L27 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L29 _public prototype_ `virtual TWeakObjectPtr<UTextureRenderTarget2D> CreateViewRenderTargetImpl(const FIntPoint& InSize, IViewCalcPayload* OptPayload = nullptr) const override;`
- L30 _public prototype_ `virtual TSharedPtr<FMoviePipelineSurfaceQueue, ESPMode::ThreadSafe> CreateSurfaceQueueImpl(const FIntPoint& InSize, IViewCalcPayload* OptPayload = nullptr) const override;`
- L33 _protected prototype_ `void PostRendererSubmission(const FMoviePipelineRenderPassMetrics& InSampleState);`
- L37 _private prototype_ `FString GetTypenameHash() const;` — Gets the typename hash used as part of the cryptomatte metadata. Eg, "cryptomatte/<typename_hash>/..."
- L41 _public member_ `EMoviePipelineObjectIdPassIdType IdType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")`
- L45 _public member_ `bool bIncludeTranslucentObjects;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — If true, translucent objects will be included in the ObjectId pass (but as an opaque layer due to limitations). False will omit translucent objects.
- L48 _private member_ `TSharedPtr<FAccumulatorPool, ESPMode::ThreadSafe> AccumulatorPool;`
- L49 _private member_ `TArray<FMoviePipelinePassIdentifier> ExpectedPassIdentifiers;`
- L50 _private member_ `bool bPrevAllowSelectTranslucent;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MOVIEPIPELINEMASKRENDERPASS_API`

### `Plugins/MovieScene/MoviePipelineMaskRenderPass/Source/MoviePipelineMaskRenderPass/Public/MoviePipelinePanoramicPass.h` (Public)


#### struct `FPanoPane`  
`struct FPanoPane : public UMoviePipelineImagePassBase::IViewCalcPayload`  
_L21-26_
- inherits: `UMoviePipelineImagePassBase::IViewCalcPayload`
- L25 _public member_ `UE::MoviePipeline::FPanoramicPane Data;` — Need to split the shared data (between MoviePipeline and MovieGraph) and want to avoid multiple inheritance in this struct.

#### struct `FPanoramicImagePixelDataPayload`  
`struct FPanoramicImagePixelDataPayload : public FImagePixelDataPayload`  
_L28-59_
- inherits: `FImagePixelDataPayload`
- L30 _public function_ `virtual TSharedRef<FImagePixelDataPayload> Copy() const override`
- L35 _public function_ `virtual FIntPoint GetAccumulatorSize() const override`
- L40 _public function_ `virtual FIntPoint GetOverlapPaddedSize() const override`
- L45 _public function_ `virtual bool GetOverlapPaddedSizeIsValid(const FIntPoint InRawSize) const override`
- L51 _public function_ `virtual void GetWeightFunctionParams(MoviePipeline::FTileWeight1D& WeightFunctionX, MoviePipeline::FTileWeight1D& WeightFunctionY) const override`
- L58 _public member_ `FPanoPane Pane;`

#### class `UMoviePipelinePanoramicPass`  
`class UMoviePipelinePanoramicPass final : public UMoviePipelineImagePassBase`  
_L67-186_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineImagePassBase`
- desc: Generates a panoramic image (potentially in stereo, stored top/bottom in the final sheet) in equirectangular projection space. Each render is a traditional 2D render and then they are blended together afterwards. For each horizontal step we render n many vertical steps. Each of these renders is called a 'Pane' to avoid confusion with the High Resolution 'Tiles' which only apply to 2D.
- L72 _public prototype_ `UMoviePipelinePanoramicPass();`
- L76 _protected prototype_ `virtual void SetupImpl(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings) override;` — UMoviePipelineRenderPass API
- L77 _protected prototype_ `virtual void RenderSample_GameThreadImpl(const FMoviePipelineRenderPassMetrics& InSampleState) override;`
- L78 _protected prototype_ `virtual void TeardownImpl() override;`
- L80 _protected function_ `virtual FText GetDisplayText() const override`
- L82 _protected prototype_ `virtual void MoviePipelineRenderShowFlagOverride(FEngineShowFlags& OutShowFlag) override;`
- L83 _protected prototype_ `virtual void GatherOutputPassesImpl(TArray<FMoviePipelinePassIdentifier>& ExpectedRenderPasses) override;`
- L84 _protected function_ `virtual bool IsAntiAliasingSupported() const`
- L85 _protected function_ `virtual int32 GetOutputFileSortingOrder() const override`
- L86 _protected prototype_ `virtual FSceneViewStateInterface* GetSceneViewStateInterface(IViewCalcPayload* OptPayload) override;`
- L87 _protected prototype_ `virtual FSceneViewStateInterface* GetExposureSceneViewStateInterface(IViewCalcPayload* OptPayload, int32 CubeFaceIndex) override;`
- L88 _protected prototype_ `virtual void AddViewExtensions(FSceneViewFamilyContext& InContext, FMoviePipelineRenderPassMetrics& InOutSampleState) override;`
- L89 _protected function_ `virtual bool IsAutoExposureAllowed(const FMoviePipelineRenderPassMetrics& InSampleState) const override`
- L90 _protected prototype_ `virtual FSceneView* GetSceneViewForSampleState(FSceneViewFamily* ViewFamily, FMoviePipelineRenderPassMetrics& InOutSampleState, IViewCalcPayload* OptPayload = nullptr) override;`
- L91 _protected prototype_ `virtual TWeakObjectPtr<UTextureRenderTarget2D> GetOrCreateViewRenderTarget(const FIntPoint& InSize, IViewCalcPayload* OptPayload = nullptr) override;`
- L92 _protected prototype_ `virtual TSharedPtr<FMoviePipelineSurfaceQueue, ESPMode::ThreadSafe> GetOrCreateSurfaceQueue(const FIntPoint& InSize, IViewCalcPayload* OptPayload = nullptr) override;`
- L96 _protected prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);` — FGCObject Interface
- L99 _protected prototype_ `void ScheduleReadbackAndAccumulation(const FMoviePipelineRenderPassMetrics& InSampleState, const FPanoPane& InPane, FCanvas& InCanvas);`
- L100 _protected prototype_ `void GetFieldOfView(float& OutHorizontal, float& OutVertical, const bool bInStereo) const;`
- L101 _protected prototype_ `FIntPoint GetPaneResolution(const FIntPoint& InSize) const;`
- L102 _protected prototype_ `FIntPoint GetPayloadPaneResolution(const FIntPoint& InSize, IViewCalcPayload* OptPayload) const;`
- L104 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L112 _public member_ `int32 NumHorizontalSteps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panoramic Settings", meta = (UIMin = "1", ClampMin = "1"))` — How many different renders should the 360* horizontal view be broken into? Higher numbers are less distorted but longer to render.
- L119 _public member_ `int32 NumVerticalSteps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panoramic Settings", meta = (UIMin = "1", ClampMin = "1"))` — How many different renders should the 360* vertical view be broken into? Higher numbers are less distorted but longer to render. This is typically less than horizontal as the vertical poles of an image will always have distortion in equirectangular projections.
- L125 _public member_ `bool bFollowCameraOrientation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panoramic Settings")` — Should the Pitch, Yaw and Roll of the camera be respected? If false, only the location will be taken from the camera.
- L131 _public member_ `EMoviePipelinePanoramicFilterType Filter = EMoviePipelinePanoramicFilterType::Bilinear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panoramic Settings")` — Filter used when blending panoramic. Bilinear is fastest (Samples a 2x2 pixel grid) and produces nearly as good results as the others which require sampling 4x4 pixels.
- L138 _public member_ `bool bStereo;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panoramic Settings")` — If true we will capture a stereo panorama. This doubles everything (all render times, memory requirements, etc.) May need a significantly higher number of horizontal steps to look good when viewed in stereo.
- L141 _public member_ `float EyeSeparation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Panoramic Settings")`
- L144 _public member_ `float EyeConvergenceDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Panoramic Settings")`
- L148 _public member_ `float HorzFieldOfView = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Panoramic Settings", meta = (UIMin = "1", ClampMin = "1", UIMax="179", ClampMax = "179"))` — Advance used only. Allows you to override the Horizontal Field of View (if not zero). Can cause crashes or incomplete panoramas.
- L152 _public member_ `float VertFieldOfView = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Panoramic Settings", meta = (UIMin = "1", ClampMin = "1", UIMax = "179", ClampMax = "179"))` — Advance used only. Allows you to override the Vertical Field of View (if not zero). Can cause crashes or incomplete panoramas.
- L155 _public member_ `bool bAccumulatorIncludesAlpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panoramic Settings")`
- L162 _public member_ `bool bAllocateHistoryPerPane;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Panoramic Settings")` — Should we store the render scene history per individual render? This can consume a great deal of memory with many renders, but enables TAA and other history-based effects (denoisers, auto-exposure, Lumen, etc.) to work.
- L168 _public member_ `bool bPageToSystemMemory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render Settings")` — If true, persistent GPU data per panoramic pane is mirrored to system memory, allowing higher resolutions, but increasing render time.
- L171 _protected member_ `TSharedPtr<FAccumulatorPool, ESPMode::ThreadSafe> AccumulatorPool;`
- L174 _protected member_ `TArray<FSceneViewStateReference> OptionalPaneViewStates;` — ToDo: One per high-res tile per pano-pane?
- L177 _protected member_ `TArray<FSceneViewStateReference> AutoExposureViewStates;` — When using an auto exposure render pass, holds view states for 6 cube faces
- L180 _protected member_ `TSharedPtr<FOpenColorIODisplayExtension, ESPMode::ThreadSafe> OCIOSceneViewExtension;` — The lifetime of this SceneViewExtension is only during the rendering process. It is destroyed as part of TearDown.
- L182 _protected member_ `TSharedPtr<MoviePipeline::IMoviePipelineOutputMerger> PanoramicOutputBlender;`
- L183 _protected member_ `bool bHasWarnedSettings;`
- L185 _protected member_ `TPimplPtr<FSceneViewStateSystemMemoryMirror> SystemMemoryMirror;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIEPIPELINEMASKRENDERPASS_API`
