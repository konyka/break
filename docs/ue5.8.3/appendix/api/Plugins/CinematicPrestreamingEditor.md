# Plugins / CinematicPrestreamingEditor

- module root: `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreamingEditor`
- headers: 7; symbols: 126
- symbol kinds: class=7, delegate=1, function=8, macro=1, member=54, prototype=50, struct=5
- PrivateDependencyModuleNames: CoreUObject, Engine, RenderCore, Slate, SlateCore
- PublicDependencyModuleNames: CinematicPrestreaming, Core, EditorSubsystem, LevelSequence, MovieRenderPipelineCore, MovieRenderPipelineEditor, MovieRenderPipelineRenderPasses, MovieScene, Sequencer, SequencerCore, UnrealEd

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreamingEditor/Private/CinePrestreamingDebugRender.h` (Private)


#### class `UCinePrestreamingDebugRender`  
`class UCinePrestreamingDebugRender : public UMoviePipelineDeferredPassBase`  
_L11-31_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMoviePipelineDeferredPassBase`
- L16 _public prototype_ `UCinePrestreamingDebugRender();`
- L18 _public prototype_ `virtual void SetupImpl(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings) override;`
- L19 _public prototype_ `virtual void TeardownImpl() override;`
- L21 _public prototype_ `virtual FText GetDisplayText() const override;`
- L23 _public prototype_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override;`
- L24 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`
- L27 _public member_ `EVirtualTextureVisualizationMode VirtualTextureDebugMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")`
- L30 _private member_ `EVirtualTextureVisualizationMode PreviousMode;`

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreamingEditor/Private/Styles/CinePrestreamingEditorStyle.h` (Private)


#### class `FCinePrestreamingEditorStyle`  
`class FCinePrestreamingEditorStyle final : public FSlateStyleSet`  
_L15-52_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the cinematic prestreaming sequence editor.
- L19 _public function_ `FCinePrestreamingEditorStyle() : FSlateStyleSet("CinePrestreamingEditorStyle")`
- L35 _public function_ `virtual ~FCinePrestreamingEditorStyle()`
- L40 _public function_ `static TSharedRef<FCinePrestreamingEditorStyle> Get()`
- L51 _private member_ `static TSharedPtr<FCinePrestreamingEditorStyle> Singleton;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define IMAGE_BRUSH_SVG(RelativePath, ...) FSlateVectorImageBrush(RootToContentDir(RelativePath, TEXT(".svg")), __VA_ARGS__)`

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreamingEditor/Private/TrackEditors/CinePrestreamingTrackEditor.h` (Private)


#### class `FCinePrestreamingTrackEditor`  
`class FCinePrestreamingTrackEditor : public FMovieSceneTrackEditor`  
_L15-45_
- inherits: `FMovieSceneTrackEditor`
- desc: A sequencer track editor for cinematic prestreaming tracks.
- L19 _public prototype_ `FCinePrestreamingTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L21 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);`
- L25 _protected prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L26 _protected prototype_ `TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L27 _protected prototype_ `bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L28 _protected prototype_ `bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L29 _protected prototype_ `const FSlateBrush* GetIconBrush() const override;`
- L30 _protected prototype_ `void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L31 _protected prototype_ `TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L35 _private prototype_ `UMovieSceneCinePrestreamingSection* AddNewSection(UMovieScene* MovieScene, UMovieSceneTrack* PrestreamingTrack);` — Adds a new section which spans the length of the owning movie scene.
- L38 _private prototype_ `void HandleAddTrack();` — Handles when the add track menu item is activated.
- L41 _private prototype_ `TSharedRef<SWidget> BuildAddPrestreamingMenu(UMovieSceneTrack* PrestreamingTrack);` — Builds the add prestreaming menu which is displayed on the track.
- L44 _private prototype_ `void HandleAddNewSection(UMovieSceneTrack* PrestreamingTrack);` — Called to add a new section.

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreamingEditor/Public/CinePrestreamingEditorModule.h` (Public)


#### class `FCinePrestreamingEditorModule`  
`class FCinePrestreamingEditorModule : public IModuleInterface`  
_L8-20_
- inherits: `IModuleInterface`
- L12 _public prototype_ `void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `void ShutdownModule() override;`
- L16 _private prototype_ `void RegisterTrackEditors();`
- L17 _private prototype_ `void UnregisterTrackEditors();`
- L19 _private member_ `FDelegateHandle CinePrestreamingCreateEditorHandle;`

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreamingEditor/Public/CinePrestreamingEditorSubsystem.h` (Public)


#### class `UCinePrestreamingEditorSubsystem`  
`class UCinePrestreamingEditorSubsystem : public UEditorSubsystem`  
_L9-18_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UEditorSubsystem`
- L14 _public prototype_ `UCinePrestreamingEditorSubsystem() = default;`
- L17 _public prototype_ `void CreatePackagesFromGeneratedData(TArray<struct FMoviePipelineCinePrestreamingGeneratedData>& InOutData);` — `UFUNCTION(BlueprintCallable, Category = "Cinematic Prestreaming|Editor")`

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreamingEditor/Public/CinePrestreamingGraphNode.h` (Public)


#### class `UCinePrestreamingGraphNode`  
`class UCinePrestreamingGraphNode : public UMovieGraphFileOutputNode`  
_L25-137_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphFileOutputNode`
- desc: A Movie Render Graph output node that records virtual texture page requests and Nanite geometry requests during rendering, then saves them as UCinePrestreamingData assets. These assets can be used at runtime to pre-stream content before it is needed during cinematic playback. This node provides the same recording functionality as UCinePrestreamingRecorderSetting (the Movie Render Queue version), but integrates with the Movie Render Graph pipeline instead. Note: Because delegates are registered lazily on the first completed output frame, the very first output frame's streaming requests are not captured. This is acceptable because warmup frames precede actual output frames and pre-establish the streaming state.
- L30 _public prototype_ `UCinePrestreamingGraphNode();`
- L33 _public prototype_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override;` — UMovieGraphNode Interface
- L35 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive) const override;`
- L36 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L37 _public prototype_ `virtual FText GetKeywords() const override;`
- L38 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L44 _protected prototype_ `virtual void OnReceiveImageDataImpl(UMovieGraphPipeline* InPipeline, UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, const TSet<FMovieGraphRenderDataIdentifier>& InMask) override;`
- L45 _protected prototype_ `virtual void OnAllFramesSubmittedImpl(UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph) override;`
- L46 _protected prototype_ `virtual void OnAllFramesFinalizedImpl(UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph) override;`
- L47 _protected prototype_ `virtual bool IsFinishedWritingToDiskImpl() const override;`
- L56 _public member_ `FDirectoryPath PackageDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ContentDir))` — Specifies the content browser directory where generated assets will be placed. Can contain format tokens such as {sequence_name} and {shot_name}.
- L60 _public member_ `bool bVirtualTextures = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record")` — Enable capture of virtual texture page requests.
- L64 _public member_ `bool bNanite = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record")` — Enable capture of Nanite geometry requests.
- L68 _public member_ `bool bModifyTargetSequence = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process")` — Automatically add the generated prestreaming track to the target sequence.
- L72 _public member_ `bool bMergeFrames = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimizations")` — Enable merging of frame data. Reduces asset size when consecutive frames have high request coherence.
- L76 _public member_ `int32 FrameCountMergeThreshold = 6;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimizations", meta = (EditCondition = "bMergeFrames", UIMin = "1", ClampMin = "1"))` — Maximum number of frames to merge data across.
- L80 _public member_ `int32 VirtualTextureRequestMergeThreshold = 2000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimizations", meta = (EditCondition = "bVirtualTextures && bMergeFrames", UIMin = "1", ClampMin = "1"))` — Threshold of virtual texture page requests. Frames are merged until this threshold is reached.
- L84 _public member_ `int32 NaniteRequestMergeThreshold = 500;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimizations", meta = (EditCondition = "bNanite && bMergeFrames", UIMin = "1", ClampMin = "1"))` — Threshold of Nanite page requests. Frames are merged until this threshold is reached.
- L92 _public member_ `bool bDisableAdvanceRenderFeatures = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimizations")` — Disable rendering features not required to generate prestreaming data (lighting, post processing, etc.). Makes recording significantly faster but produces unusable rendered images. Only enable this when using a dedicated recording graph with no image output nodes.
- L96 _public member_ `int32 StartFrame = 0;` — `UPROPERTY(BlueprintReadWrite, Category = "Settings", meta = (UIMin = "0", ClampMin = "0"))` — First frame to include in the recorded asset. Frames before this index are dropped.
- L100 _public member_ `int32 EndFrame = 0;` — `UPROPERTY(BlueprintReadWrite, Category = "Settings", meta = (UIMin = "0", ClampMin = "0"))` — Last frame to include in the recorded asset. Frames after this index are dropped. Set to 0 to include all frames.
- L104 _public member_ `FOnCinePrestreamingGenerateData OnGenerateData;` — `UPROPERTY(BlueprintAssignable)` — Broadcast after asset generation completes, with the generated data.
- L107 _private prototype_ `void OnBeginFrame_GameThread();`
- L108 _private prototype_ `void OnEndFrame_GameThread();`
- L109 _private prototype_ `void OnEndFrame_RenderThread();`
- L110 _private prototype_ `void CreateAssetsFromData(UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph);`
- L111 _private prototype_ `void ModifyTargetSequences(const TArray<FMoviePipelineCinePrestreamingGeneratedData>& InData);`
- L112 _private prototype_ `void ResetStaticState();`
- L130 _private member_ `inline static TWeakObjectPtr<UMovieGraphPipeline> ActivePipeline;` — The pipeline generates many CDO instances throughout execution. Static data provides shared state across all CDO calls for the lifetime of a single pipeline run.
- L131 _private member_ `inline static FDelegateHandle BeginFrameDelegate;`
- L132 _private member_ `inline static FDelegateHandle EndFrameRTDelegate;`
- L134 _private member_ `inline static TArray<FCollectedData> SegmentData;` — Pre-allocated once to avoid reallocation while the render thread may be writing.
- L135 _private member_ `inline static int32 PrevActiveShotIndex;`
- L136 _private member_ `inline static bool bShowFlagsDisabled;`

#### struct `UCinePrestreamingGraphNode::FFrameData`  
`struct FFrameData`  
_L115-119_
- desc: Per-frame collected data structures (same layout as MRQ recorder)
- L117 _public member_ `TMap<uint64, uint32> VirtualTextureRequestData;`
- L118 _public member_ `TMap<uint64, uint32> NaniteRequestData;`

#### struct `UCinePrestreamingGraphNode::FCollectedData`  
`struct FCollectedData`  
_L121-126_
- L123 _public member_ `bool bValid = false;`
- L125 _public member_ `TMap<FFrameNumber, FFrameData> FrameData;` — Map of shot-relative FFrameNumber to collected streaming requests.

### `Plugins/MovieScene/CinematicPrestreaming/Source/CinematicPrestreamingEditor/Public/CinePrestreamingRecorderSetting.h` (Public)


#### struct `FMoviePipelineCinePrestreamingGeneratedData`  
`struct FMoviePipelineCinePrestreamingGeneratedData`  
_L13-35_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public function_ `FMoviePipelineCinePrestreamingGeneratedData() : StreamingData(nullptr) , MovieScene(nullptr)`
- L23 _public member_ `TObjectPtr<UCinePrestreamingData> StreamingData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic Prestreaming")`
- L26 _public member_ `TObjectPtr<UMovieScene> MovieScene;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic Prestreaming")`
- L29 _public member_ `FString PackagePath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic Prestreaming")`
- L32 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic Prestreaming")`
- L34 _public member_ `TRange<FFrameNumber> Range;`

#### class `UCinePrestreamingRecorderSetting`  
`class UCinePrestreamingRecorderSetting : public UMoviePipelineOutputBase`  
_L40-134_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMoviePipelineOutputBase`
- L45 _public prototype_ `UCinePrestreamingRecorderSetting();`
- L49 _protected function_ `bool IsValidOnShots() const override` — UMoviePipelineSetting interface
- L50 _protected function_ `bool IsValidOnPrimary() const override`
- L52 _protected function_ `FText GetDisplayText() const override`
- L53 _protected prototype_ `FText GetFooterText(UMoviePipelineExecutorJob* InJob) const;`
- L56 _protected prototype_ `void SetupForPipelineImpl(UMoviePipeline* InPipeline) override;`
- L57 _protected prototype_ `void TeardownForPipelineImpl(UMoviePipeline* InPipeline) override;`
- L61 _private prototype_ `void OnBeginFrame_GameThread();`
- L62 _private prototype_ `void OnEndFrame_GameThread();`
- L63 _private prototype_ `void OnEndFrame_RenderThread();`
- L64 _private prototype_ `void ModifyTargetSequences(const TArray<FMoviePipelineCinePrestreamingGeneratedData>& InData);`
- L65 _private prototype_ `void CreateAssetsFromData();`
- L74 _public member_ `FDirectoryPath PackageDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta=(ContentDir))` — Specifies which directory the generated assets be placed in. Assumed to be relative to the root folder, ie it should start with /Game/ etc. Can contain MRQ format strings such as {shot_name} which will be resolved.
- L78 _public member_ `bool bVirtualTextures = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Record")` — Enable capture of virtual texture page requests.
- L81 _public member_ `bool bNanite = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record")` — Enable capture of nanite requests.
- L84 _public member_ `bool bModifyTargetSequence = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process")` — Automatically add the generated tracks to the target sequence
- L87 _public member_ `bool bMergeFrames = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimizations")` — Enable merging of frame data. This can reduce data overhead in the common case where there is high coherance of requests across frames.
- L90 _public member_ `int32 FrameCountMergeThreshold = 6;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimizations", meta = (EditCondition = "bMergeFrames", UIMin = "1", ClampMin = "1"))` — Maximum number of frames to merge data across.
- L93 _public member_ `int32 VirtualTextureRequestMergeThreshold = 2000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimizations", meta = (EditCondition = "bVirtualTextures && bMergeFrames", UIMin = "1", ClampMin = "1"))` — Threshold of virtual texture page requests. We merge frames until up to and including the frame where we pass this threshold.
- L96 _public member_ `int32 NaniteRequestMergeThreshold = 500;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimizations", meta = (EditCondition = "bNanite && bMergeFrames", UIMin = "1", ClampMin = "1"))` — Threshold of nanite page requests. We merge frames until up to and including the frame where we pass this threshold.
- L99 _public member_ `bool bDisableAdvanceRenderFeatures = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimizations")` — By default we disable any render features that aren't needed to generate the prestreaming data. This makes renders significantly faster, but also means that the final image generated by the renderer is unusable.
- L102 _public member_ `int32 StartFrame = 0;` — `UPROPERTY(BlueprintReadWrite, Category = "Settings", meta = (UIMin = "0", ClampMin="0"))` — First frame to output in each recorded asset. Frames before this are dropped.
- L105 _public member_ `int32 EndFrame = 0;` — `UPROPERTY(BlueprintReadWrite, Category = "Settings", meta = (UIMin = "0", ClampMin = "0"))` — Last frame to capture in each recorded asset. Frames after this are dropped. (Set to 0 to ignore).
- L108 _public member_ `FOnCinePrestreamingGenerateData OnGenerateData;` — `UPROPERTY(BlueprintAssignable)`
- L111 _private member_ `FDelegateHandle BeginFrameDelegate;`
- L112 _private member_ `FDelegateHandle EndFrameDelegate;`
- L131 _private member_ `TArray<FCollectedData> SegmentData;`
- L132 _private member_ `int32 PrevActiveShotIndex;`
- L133 _private member_ `TArray<FString> ShowFlagsToDisable;`

#### struct `UCinePrestreamingRecorderSetting::FFrameData`  
`struct FFrameData`  
_L114-118_
- L116 _public member_ `TMap<uint64, uint32> VirtualTextureRequestData;`
- L117 _public member_ `TMap<uint64, uint32> NaniteRequestData;`

#### struct `UCinePrestreamingRecorderSetting::FCollectedData`  
`struct FCollectedData`  
_L120-129_
- L122 _public member_ `bool bValid = false;`
- L124 _public member_ `TMap<FFrameNumber, FFrameData> FrameData;` — Map of time to recorded frame requests.
- L126 _public member_ `FMoviePipelineFrameOutputState OutputState;` — OutputState required for creating output file names.
- L128 _public member_ `FFrameNumber InitialShotTick;` — TickInRoot first tick in frame.

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCinePrestreamingGenerateData, TArray<FMoviePipelineCinePrestreamingGeneratedData>, GeneratedData);`
- L37 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCinePrestreamingGenerateData, TArray<FMoviePipelineCinePrestreamingGeneratedData>, GeneratedData);`
