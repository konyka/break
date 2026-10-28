# Plugins / MovieRenderPipelineCore

- module root: `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore`
- headers: 114; symbols: 4549
- symbol kinds: class=162, delegate=40, enum=36, enumerator=133, function=646, macro=97, member=1537, namespace=58, prototype=1697, struct=128, typedef=11, variable=4
- PrivateDependencyModuleNames: AudioMixer, ChaosClothAssetEngine, ClassViewer, ClothingSystemRuntimeInterface, ContentBrowserData, Core, CoreUObject, DataLayerEditor, DeveloperSettings, EditorWidgets, HTTP, ImageCore, InputCore, Landscape, Layers, Networking, NonRealtimeAudioRenderer, OpenColorIOWrapper, RHI, RenderCore, Renderer, SceneOutliner, SettingsEditor, Slate, SlateCore, Sockets, UMG, UnrealEd
- PublicDependencyModuleNames: CinematicCamera, Engine, ImageWriteQueue, LevelSequence, MovieScene, MovieSceneTools, MovieSceneTracks, NamingTokens, OpenColorIO, SlateCore

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Private/Graph/MovieGraphCVarManager.h` (Private)


#### class `UE::MovieGraph::Private::FMovieGraphCVarManager`  
`class FMovieGraphCVarManager final`  
_L20-106_
- desc: Responsible for applying individual cvars, cvar presets, and console commands. CVars can be added to the manager with the Add*() methods, then applied via ApplyAllCVars(). Console commands can be added with their associated Add*() methods, and executed via the Run*() methods.
- L23 _public prototype_ `FMovieGraphCVarManager() = default;`
- L29 _public prototype_ `void AddCVar(const FString& InName, const float Value);` — Adds a cvar that should be applied with the given Value. If the cvar with InName already exists, its value will be updated.
- L35 _public prototype_ `void AddPreset(const TScriptInterface<IMovieSceneConsoleVariableTrackInterface>& InPreset);` — Adds a preset that should be applied. If the preset contains cvars that have already been added via other Add*() calls, the values in the preset will override values already added.
- L38 _public prototype_ `void AddStartConsoleCommands(const TArray<FString>& InStartConsoleCommands);` — Adds console commands that should be run before a shot starts rendering.
- L41 _public prototype_ `void AddEndConsoleCommands(const TArray<FString>& InEndConsoleCommands);` — Adds console commands that should be run after a shot finishes rendering.
- L44 _public prototype_ `void AddEvaluatedGraph(const UMovieGraphEvaluatedConfig* InEvaluatedGraph);` — For all cvar, cvar preset, and console command nodes in InEvaluatedGraph, calls either AddCVar(), AddPreset(), or Add*ConsoleCommands().
- L51 _public prototype_ `void AddShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot);` — Calls AddCvar() for all console variables that have been added via overrides on the shot, as well as the shot's parent job. Console variables set on the shot and job have priority over all other cvars that have been set (with shot-based cvars having the highest priority).
- L54 _public prototype_ `void ApplyAllCVars();` — Applies all cvars that have been gathered via the Add*() methods.
- L60 _public prototype_ `void RevertAllCVars();` — For all cvars that were gathered via the Add*() methods and applied, reverts their values to what they were before being applied. After calling this, ApplyAllCVars() is a no-op, and the Add*() methods need to be called again.
- L63 _public prototype_ `void RunStartConsoleCommands();` — Runs all start console commands that have been added.
- L66 _public prototype_ `void RunEndConsoleCommands();` — Runs all end console commands that have been added.
- L69 _public prototype_ `void SetWorld(UWorld* InWorld);` — Sets the world context that the console commands should use when executing.
- L73 _private prototype_ `static void ApplyCVar(IConsoleVariable* InCVar, float InValue);` — Sets the given cvar, InCVar, to InValue.
- L93 _private member_ `TArray<FMovieGraphCVarOverride> CVars;` — The merged result of both individual CVars and CVar presets.
- L96 _private member_ `TArray<float> PreviousConsoleVariableValues;` — The values of the gathered cvars before the the manager sets their values.
- L99 _private member_ `TArray<FString> StartConsoleCommands;` — The start console commands that were added.
- L102 _private member_ `TArray<FString> EndConsoleCommands;` — The end console commands that were added.
- L105 _private member_ `UWorld* WorldContext;` — The world that should be used as the context when executing console commands.

#### struct `UE::MovieGraph::Private::FMovieGraphCVarManager::FMovieGraphCVarOverride`  
`struct FMovieGraphCVarOverride`  
_L76-89_
- desc: Represents a console variable override.
- L78 _public function_ `FMovieGraphCVarOverride(const FString& InName, const float InValue) : Name(InName) , Value(InValue)`
- L85 _public member_ `FString Name;` — The name of the console variable.
- L88 _public member_ `float Value;` — The value of the console variable.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MovieGraph` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::MovieGraph`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Private/Graph/MovieGraphOutputMerger.h` (Private)


#### class `UE::MovieGraph::FMovieGraphOutputMerger`  
`class FMovieGraphOutputMerger : public UE::MovieGraph::IMovieGraphOutputMerger`  
_L20-54_
- inherits: `UE::MovieGraph::IMovieGraphOutputMerger`
- desc: When MRQ produces a single output frame, it's built out of many individual parts that are spread out over time. Different render passes within a single output frame may take longer to produce due to splitting out work onto the Task Graph, so this class is responsible for handling finished data for each render pass coming in at an arbitrary time, and once all of the pieces are there only then does this release it onto the actual pipeline saying the frame is finished.
- L23 _public prototype_ `FMovieGraphOutputMerger(UMovieGraphPipeline* InOwningMoviePipeline);`
- L26 _public prototype_ `virtual FMovieGraphOutputMergerFrame& AllocateNewOutputFrame_GameThread(const int32 InRenderedFrameNumber) override;` — IMovieGraphOutputMerger Interface
- L27 _public prototype_ `virtual FMovieGraphOutputMergerFrame& GetOutputFrame_GameThread(const int32 InRenderedFrameNumber) override;`
- L28 _public prototype_ `virtual void OnCompleteRenderPassDataAvailable_AnyThread(TUniquePtr<FImagePixelData>&& InData) override;`
- L29 _public prototype_ `virtual void OnSingleSampleDataAvailable_AnyThread(TUniquePtr<FImagePixelData>&& InData) override;`
- L30 _public prototype_ `virtual void AbandonOutstandingWork() override;`
- L31 _public function_ `virtual int32 GetNumOutstandingFrames() const override`
- L32 _public function_ `virtual TQueue<FMovieGraphOutputMergerFrame>& GetFinishedFrames() override`
- L40 _public member_ `TQueue<UE::MovieGraph::FMovieGraphOutputMergerFrame> FinishedFrames;` — A thread safe FIFO queue of finished frames that have had all of their render passes complete. All frames in the queue are processed on the next Game Thread tick and moved onto the output containers.
- L44 _private member_ `TWeakObjectPtr<UMovieGraphPipeline> WeakMoviePipeline;` — The Movie Pipeline that owns us.
- L47 _private member_ `TSortedMap<int32, FMovieGraphOutputMergerFrame> PendingData;` — Data that is expected but not fully available yet. Sorted by frame number.
- L50 _private member_ `FCriticalSection PendingDataMutex;` — Mutex that protects adding/updating/removing from PendingData
- L53 _private member_ `IImageWriteQueue* Debug_ImageWriteQueue;` — A debug image sequence writer (EXR-only). Typically used for writing out individual samples, bypassing accumulation and output containers.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MovieGraph` (scope `UE`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Private/Graph/MovieGraphUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Audio`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MovieGraph` (scope `UE`)
- L25 _prototype_ `FString GetUniqueName(const TArray<FString>& InExistingNames, const FString& InBaseName);` (scope `UE::MovieGraph`) — Generate a unique name given a set of existing names and the desired base name. The base name will be given a postfix value if it conflicts with an existing name (eg, if the base name is "Foo" but there's already an existing name "Foo", the generated name would be "Foo 1").
- L36 _prototype_ `bool ResolveConnectedPinValue(UMovieGraphPin* InFromPin, const TArray<UMovieGraphPin*>& InConnectedPins, const FMovieGraphEvaluationContext& InEvaluationContext, FString& OutResolvedValue);` (scope `UE::MovieGraph`) — Gets the resolved value of an input pin (InFromPin), given all of its connections (InConnectedPins). Providing an evaluation context is needed, mostly to ensure that recursion doesn't occur. The resolved value is provided in OutResolvedValue as the serialized representation. Returns true if a value could be resolved, else false. Generally the normal graph evaluation process should resolve values, and using this method might indicate you're doing the wrong thing. However, for some non-setting nodes, it may be necessary to resolve values manually since non-setting nodes are not evaluated like normal setting nodes.
- L38 _namespace_ `namespace Audio` (scope `UE::MovieGraph`)
- L41 _prototype_ `FAudioDevice* GetAudioDeviceFromWorldContext(const UObject* InWorldContextObject);` (scope `UE::MovieGraph::Audio`) — Gets the audio device from the supplied world context (or nullptr if it could not be determined).
- L44 _prototype_ `::Audio::FMixerDevice* GetAudioMixerDeviceFromWorldContext(const UObject* InWorldContextObject);` (scope `UE::MovieGraph::Audio`) — Gets the audio mixer from the supplied world context (or nullptr if it could not be determined).
- L47 _prototype_ `bool IsMoviePipelineAudioOutputSupported(const UObject* InWorldContextObject);` (scope `UE::MovieGraph::Audio`) — Determines if the pipeline can generate audio.
- L50 _namespace_ `namespace Capture` (scope `UE::MovieGraph`)
- L52 _prototype_ `FString PrepareCapturePath( const UMovieGraphPipeline* InPipeline, const TObjectPtr<UMovieGraphEvaluatedConfig>& InEvaluatedConfig, const FString& InPathFormat, const FString& InExt, bool InForShot);` (scope `UE::MovieGraph::Capture`)
- L59 _prototype_ `void ValidateAlphaProjectSettings(const FText& InRequestingFeatureLabel, bool bMandatePrimitiveAlphaHoldout = false);` (scope `UE::MovieGraph`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphBlueprintLibrary.h` (Public)


#### class `UMovieGraphBlueprintLibrary`  
`class UMovieGraphBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L19-300_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "MovieGraphLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L33 _public prototype_ `static FFrameRate GetEffectiveFrameRate(UMovieGraphGlobalOutputSettingNode* InNode, const FFrameRate& InDefaultRate);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — If InNode is valid, inspects the provided OutputsettingNode to determine if it wants to override the Frame Rate, and if so, returns the overwritten frame rate. If nullptr, or it does not have the bOverride_bUseCustomFrameRate flag set, then InDefaultrate is returned. @param	InNode			- Optional, setting to inspect for a custom framerate. @param	InDefaultRate	- The frame rate to use if the node is nullptr or doesn't want to override the rate. @return					- The effective frame rate (taking into account the node's desire to override it).
- L47 _public prototype_ `static FString ResolveFilenameFormatArguments(const FString& InFormatString, const FMovieGraphFilenameResolveParams& InParams, FMovieGraphResolveArgs& OutMergedFormatArgs);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Takes a Movie Graph format string (in the form of {token}), a list of parameters (which normally come from the running UMovieGraphPipeline) and resolves them into a file path. Unknown tokens are ignored. Which tokens can be resolved depends on the contents of InParams, tokens from settings rely on a evaluated config being provided, etc. @param	InFormatString		- Format string to attempt to resolve. Leave blank if just the format args should be populated. @param	InParams			- A list of parameters to use as source data for the resolve step. Normally comes from the UMovieGraphPipeline instance, - but takes (mostly) POD here to allow using this function outside of the render runtime. @param	OutMergedFormatArgs - The set of KVP for both filename formats and file metadata that is generated as a result of this. Provided in case you - needed to do your own string resolving with the final dataset. @return						- The resolved file path string. Returns an empty string if InFormatString is blank.
- L54 _public prototype_ `static FString ResolveFormatArguments(const FString& InFormatString, const FMovieGraphFilenameResolveParams& InParams, FMovieGraphResolveArgs& OutMergedFormatArgs);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Functions identically to ResolveFilenameFormatArguments(), with the exception that this variation does not resolve the format string to a file path (any non-path format string can be provided).
- L62 _public prototype_ `static int32 ResolveVersionNumber(FMovieGraphFilenameResolveParams InParams, const bool bGetNextVersion = true);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — If the version number is explicitly specified on the Output Setting node, returns that. Otherwise searches the output directory for the highest version that already exists (and increments it by one if bGetNextVersion is true). Returns -1 if the version could not be resolved.
- L71 _public prototype_ `static int32 GetCurrentVersionNumber(const UMovieGraphPipeline* InMovieGraphPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Retrieves the cached version number calculated for the current shot, which depends on where the version token was used in the File Name Output ie: If {version} comes before {shot_name} then all shots will use the same version number, but if it comes afterwards then each shot may have a different version (which is the highest number found of that particular shot). This function should retrieve what is used in the filename writing step either way.
- L81 _public prototype_ `static FIntPoint GetEffectiveOutputResolution(UMovieGraphEvaluatedConfig* InEvaluatedGraph, float DefaultOverscan = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph", meta=(DeprecatedFunction, DeprecationMessage = "Use GetOverscannedResolution instead"))` — `UE_DEPRECATED(5.6, "GetEffectiveOutputResolution is deprecated. Use GetOverscannedResolution instead")` — In case of overscan percentage being higher than 0, additional pixels are rendered. This function returns the resolution with overscan taken into account. @param	InEvaluatedGraph	- The evaluated graph that will provide context for resolving the resolution @param	DefaultOverscan		- The default overscan to use if there are no camera settings that provide an overscan override value, from 0.0 to 1.0 @return						- The output resolution, taking into account overscan
- L93 _public prototype_ `static FIntPoint GetDesiredOutputResolution(UMovieGraphEvaluatedConfig* InEvaluatedGraph, float CameraAspectRatio = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the desired output resolution for the movie render graph as specified by the user. Does not include overscan, tiling, or aspect ratio constraints, and is the target resolution that the pipeline will generally output (e.g. when cropping overscan in non-EXR formats). Use GetOverscannedResolution or GetBackbufferResolution to get resolutions that factor in overscan and tiling, respectively @param	InEvaluatedGraph	- The evaluated graph that will provide context for resolving the resolution @param	CameraAspectRatio	- The aspect ratio for the camera. Set to zero if you want to adapt to the output resolution's aspect ratio (otherwise resolution may be adapted to fit aspect ratio based on config settings). @return						- The desired output resolution
- L104 _public prototype_ `static FIntPoint GetOverscannedResolution(UMovieGraphEvaluatedConfig* InEvaluatedGraph, float DefaultOverscan = 0.0f, float CameraAspectRatio = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the desired output resolution scaled by any configured overscan for the movie render graph @param	InEvaluatedGraph	- The evaluated graph that will provide context for resolving the resolution @param	DefaultOverscan		- The default overscan to use if there are no camera settings that provide an overscan override value, from 0.0 to 1.0 @param	CameraAspectRatio	- The aspect ratio for the camera. Set to zero if you want to adapt to the output resolution's aspect ratio (otherwise resolution may be adapted to fit aspect ratio based on config settings). @return						- The overscan-scaled resolution
- L115 _public prototype_ `static FIntPoint GetBackbufferResolution(UMovieGraphEvaluatedConfig* InEvaluatedGraph, float DefaultOverscan = 0.0f, float CameraAspectRatio = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the resolution that frames will actually be rendered at in MRG, which includes factors such as overscan and tiling @param	InEvaluatedGraph	- The evaluated graph that will provide context for resolving the resolution @param	DefaultOverscan		- The default overscan to use if there are no camera settings that provide an overscan override value, from 0.0 to 1.0 @param	CameraAspectRatio	- The aspect ratio for the camera. Set to zero if you want to adapt to the output resolution's aspect ratio (otherwise resolution may be adapted to fit aspect ratio based on config settings). @return						- The resolution of a rendered frame
- L126 _public prototype_ `static FIntRect GetOverscanCropRectangle(UMovieGraphEvaluatedConfig* InEvaluatedGraph, float DefaultOverscan = 0.0f, float CameraAspectRatio = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets a rectangle that will crop out any overscan applied to the scene. If there is no overscan, the rectangle returned will match the backbuffer rectangle @param InEvaluatedGraph		- The evaluated graph that will provide context for resolving the resolution @param DefaultOverscan		- The default overscan to use if there are no camera settings that provide an overscan override value, from 0.0 to 1.0 @param	CameraAspectRatio	- The aspect ratio for the camera. Set to zero if you want to adapt to the output resolution's aspect ratio (otherwise resolution may be adapted to fit aspect ratio based on config settings). @return						- The crop rectangle, which will have a resolution matching the requested output resolution
- L133 _public prototype_ `static FText GetJobName(const UMovieGraphPipeline* InMovieGraphPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the name of the current job. @param	InMovieGraphPipeline	 - The pipeline to get the job name from.
- L140 _public prototype_ `static FText GetJobAuthor(const UMovieGraphPipeline* InMovieGraphPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the author of the current job, or the logged in user's username if the job has no specified author. @param	InMovieGraphPipeline	 - The pipeline to get the job author from.
- L144 _public prototype_ `static float GetCompletionPercentage(const UMovieGraphPipeline* InPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the completion percent of the Pipeline in 0-1
- L153 _public prototype_ `static void GetOverallOutputFrames(const UMovieGraphPipeline* InMovieGraphPipeline, int32& OutCurrentIndex, int32& OutTotalCount);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Determines the overall current frame number and total number of frames. @param	InMovieGraphPipeline	- The pipeline to get the frame information from. @param	OutCurrentIndex			- The current frame number. @param	OutTotalCount			- The total number of frames.
- L160 _public prototype_ `static FDateTime GetJobInitializationTime(const UMovieGraphPipeline* InMovieGraphPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the time the job was initialized. @param	InMovieGraphPipeline	- The pipeline to get the job initialization time from.
- L171 _public prototype_ `static bool GetEstimatedTimeRemaining(const UMovieGraphPipeline* InMovieGraphPipeline, FTimespan& OutEstimate);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Get the estimated amount of time remaining for the current pipeline. Based on looking at the total amount of samples to render vs. how many have been completed so far. Inaccurate when Time Dilation is used, and gets more accurate over the course of the render. @param	InMovieGraphPipeline	- The pipeline to get the time estimate from. @param	OutEstimate				- The resulting estimate, or FTimespan() if estimate is not valid. @return							- True if a valid estimate can be calculated, or false if it is not ready yet (ie: not enough samples rendered)
- L179 _public prototype_ `static EMovieRenderPipelineState GetPipelineState(const UMovieGraphPipeline* InMovieGraphPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Get the current state of the specified pipeline. See EMovieRenderPipelineState for more detail about each state. @param	InMovieGraphPipeline	- The pipeline to get the state for. @return							- The current state.
- L186 _public prototype_ `static EMovieRenderShotState GetCurrentSegmentState(const UMovieGraphPipeline* InMovieGraphPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the state of the segment (shot) currently being rendered. @param	InMovieGraphPipeline	- The pipeline to get segment information from.
- L193 _public prototype_ `static void GetCurrentSegmentName(const UMovieGraphPipeline* InMovieGraphPipeline, FText& OutOuterName, FText& OutInnerName);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the name of the segment (shot) currently being rendered. @param	InMovieGraphPipeline	- The pipeline to get segment information from.
- L200 _public prototype_ `static void GetOverallSegmentCounts(const UMovieGraphPipeline* InMovieGraphPipeline, int32& OutCurrentIndex, int32& OutTotalCount);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the number of segments (shots) that will be rendered. @param	InMovieGraphPipeline	- The pipeline to get segment information from.
- L207 _public prototype_ `static FMoviePipelineSegmentWorkMetrics GetCurrentSegmentWorkMetrics(const UMovieGraphPipeline* InMovieGraphPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the work metrics for the segment (shot) that is currently being rendered. @param	InMovieGraphPipeline	- The pipeline to get segment information from.
- L214 _public prototype_ `static FTimecode GetRootTimecode(const UMovieGraphPipeline* InMovieGraphPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the timecode of the current render at the root (sequence) level. @param	InMovieGraphPipeline	- The pipeline to get timecode information from.
- L221 _public prototype_ `static FFrameNumber GetRootFrameNumber(const UMovieGraphPipeline* InMovieGraphPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the frame number of the current render at the root (sequence) level. @param	InMovieGraphPipeline	- The pipeline to get frame number information from.
- L228 _public prototype_ `static FTimecode GetCurrentShotTimecode(const UMovieGraphPipeline* InMovieGraphPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the timecode of the current render at the shot level. @param	InMovieGraphPipeline	- The pipeline to get timecode information from.
- L235 _public prototype_ `static FFrameNumber GetCurrentShotFrameNumber(const UMovieGraphPipeline* InMovieGraphPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the frame number of the current render at the shot level. @param	InMovieGraphPipeline	- The pipeline to get frame number information from.
- L242 _public prototype_ `static float GetCurrentFocusDistance(const UMovieGraphPipeline* InMovieGraphPipeline, int32 InCameraIndex = -1);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the focus distance for the camera currently in use. @param	InMovieGraphPipeline	- The pipeline to get the camera information from.
- L249 _public prototype_ `static float GetCurrentFocalLength(const UMovieGraphPipeline* InMovieGraphPipeline, int32 InCameraIndex = -1);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the focal length for the camera currently in use. @param	InMovieGraphPipeline	- The pipeline to get the camera information from.
- L256 _public prototype_ `static float GetCurrentAperture(const UMovieGraphPipeline* InMovieGraphPipeline, int32 InCameraIndex = -1);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the aperture for the camera currently in use. @param	InMovieGraphPipeline	- The pipeline to get the camera information from.
- L263 _public prototype_ `static UCineCameraComponent* GetCurrentCineCamera(const UMovieGraphPipeline* InMovieGraphPipeline, int32 InCameraIndex = -1);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the currently active cine camera, or nullptr if one was not found. @param	InMovieGraphPipeline	- The pipeline to get the camera from.
- L272 _public prototype_ `static FMovieGraphNamedResolution NamedResolutionFromProfile(const FName& InResolutionProfileName);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Create a Named Resolution from the profile name. Throws a Kismet Exception if the profile name isn't found. The known profiles can be found in UMovieGraphProjectSettings's CDO.
- L279 _public prototype_ `static bool IsNamedResolutionValid(const FName& InResolutionProfileName);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Utility function for checking if a given resolution profile name is valid, since NamedResolutionFromProfile will throw a kismet exception, but blueprints can't actually try/catch them.
- L285 _public prototype_ `static FMovieGraphNamedResolution NamedResolutionFromSize(const int32 InResX, const int32 InResY);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Create a Named Resolution from the given resolution. Given named resolution will be named "Custom".
- L291 _public prototype_ `static UMoviePipelineExecutorShot* GetCurrentExecutorShot(const UMovieGraphPipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the current shot being rendered by the graph (could be nullptr if rendering hasn't started or has moved to Finalize!)
- L298 _public prototype_ `static UWorld* GetCurrentPlayWorld();` — `UFUNCTION(BlueprintPure, Category = "Movie Graph", meta = (DisplayName = "Get Current Play World"))` — Returns the current play world (PIE or Game). Useful when a Blueprint does not have a world context object, such as in MovieGraphScriptBase callbacks. Returns nullptr if no play world is active.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphBurnInWidget.h` (Public)


#### class `UMovieGraphBurnInWidget`  
`class UMovieGraphBurnInWidget : public UUserWidget`  
_L15-27_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UUserWidget`
- desc: Base class for graph-based level sequence burn-ins.
- L26 _public prototype_ `void UpdateForGraph(UMovieGraphPipeline* InGraphPipeline, UMovieGraphEvaluatedConfig* InEvaluatedConfig, int32 InCameraIndex, const FString& CameraName);` — `UFUNCTION(BlueprintImplementableEvent)` — Called on the first temporal and first spatial sample of each output frame. @param	InGraphPipeline		The graph pipeline the burn-in is for. This will be consistent throughout a burn-in widget's life. @param	InEvaluatedConfig	The evaluated graph that was used to generate this output frame.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphCommon.h` (Public)


#### enum `EMovieGraphValueType`  
`enum class EMovieGraphValueType : uint8`  
_L13-38_
- reflection: `UENUM()`
- desc: The type of a graph member's value.
- L15 _public enumerator_ `None UMETA(Hidden)`
- L16 _public enumerator_ `Bool`
- L17 _public enumerator_ `Byte`
- L18 _public enumerator_ `Int32`
- L19 _public enumerator_ `Int64`
- L20 _public enumerator_ `Float`
- L21 _public enumerator_ `Double`
- L22 _public enumerator_ `Name`
- L23 _public enumerator_ `String`
- L24 _public enumerator_ `Text`
- L25 _public enumerator_ `Enum`
- L26 _public enumerator_ `Struct`
- L27 _public enumerator_ `Object`
- L28 _public enumerator_ `SoftObject`
- L29 _public enumerator_ `Class`
- L30 _public enumerator_ `SoftClass`
- L31 _public enumerator_ `Int8` — Type not fully supported at UI, will work with restrictions to type editing
- L32 _public enumerator_ `Int16` — Type not fully supported at UI, will work with restrictions to type editing
- L33 _public enumerator_ `UInt16` — Type not fully supported at UI, will work with restrictions to type editing
- L34 _public enumerator_ `UInt32` — Type not fully supported at UI, will work with restrictions to type editing
- L35 _public enumerator_ `UInt64` — Type not fully supported at UI, will work with restrictions to type editing
- L37 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EMovieGraphContainerType`  
`enum class EMovieGraphContainerType : uint8`  
_L46-54_
- reflection: `UENUM()`
- desc: The container type of a graph member's value.
- L48 _public enumerator_ `None UMETA(Hidden)`
- L49 _public enumerator_ `Array`
- L50 _public enumerator_ `Set`
- L51 _public enumerator_ `Map`
- L53 _public enumerator_ `Count UMETA(Hidden)`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphConfig.h` (Public)


#### class `UMovieGraphMember`  
`class UMovieGraphMember : public UMovieGraphValueContainer`  
_L27-106_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMovieGraphValueContainer`
- L35 _public prototype_ `UMovieGraphMember() = default;`
- L38 _public prototype_ `UMovieGraphConfig* GetOwningGraph() const;` — Gets the graph that owns this member, or nullptr if one was not found.
- L42 _public function_ `FString GetMemberName() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the name of this member.
- L46 _public prototype_ `virtual bool SetMemberName(const FString& InNewName);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Sets the name of this member. Returns true if the rename was successful, else false.
- L53 _public prototype_ `virtual bool CanRename(const FText& InNewName, FText& OutError) const;` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Determines if this member can be renamed to the specified name. If the rename is not possible, returns false and OutError is populated with the reason, else returns true.
- L57 _public function_ `const FGuid& GetGuid() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the GUID that uniquely identifies this member.
- L60 _public function_ `void SetGuid(const FGuid& InGuid)` — Sets the GUID that uniquely identifies this member.
- L64 _public function_ `virtual bool IsDeletable() const` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Determines if this member can be deleted.
- L68 _public function_ `virtual bool IsEditable() const` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets whether this member is editable via the UI.
- L73 _protected function_ `template<class T> bool IsUniqueNameInMemberArray(const FText& InName, const TArray<T*>& InMemberArray) const` — Determines if InName is a unique name within the members in MemberArray.
- L90 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta=(EditCondition="bIsEditable", HideEditConditionToggle))` — The optional description of this member, which is user-facing.
- L95 _protected member_ `FString Name;` — `UPROPERTY()` — The name of this member, which is user-facing.
- L99 _protected member_ `FGuid Guid;` — `UPROPERTY()` — A GUID that uniquely identifies this member within its graph.
- L105 _protected member_ `bool bIsEditable = true;` — `UPROPERTY()` — Whether this member can be edited in the UI.

#### class `UMovieGraphVariable`  
`class UMovieGraphVariable : public UMovieGraphMember`  
_L114-157_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphMember`
- desc: A variable that can be used inside the graph. Most variables are created by the user, and can have their value changed at the job level. Global variables, however, are not user-created and their values are provided when the graph is evaluated. Overriding them at the job level is not possible.
- L122 _public prototype_ `UMovieGraphVariable() = default;`
- L126 _public prototype_ `bool IsGlobal() const;` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Returns true if this variable is a global variable.
- L130 _public prototype_ `const FString& GetCategory() const;` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the category (if any) assigned to this variable.
- L137 _public prototype_ `void SetCategory(const FString& InNewCategory);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Sets the variable to the provided category. Be aware that the category provided here may not be the final category set on the variable (InNewCategory will be put through FName::NameToDisplayString().
- L140 _public prototype_ `virtual bool IsDeletable() const override;`
- L141 _public prototype_ `virtual bool CanRename(const FText& InNewName, FText& OutError) const override;`
- L142 _public prototype_ `virtual bool SetMemberName(const FString& InNewName) override;`
- L146 _public member_ `FOnMovieGraphVariableChanged OnMovieGraphVariableChangedDelegate;`
- L149 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L156 _private member_ `FString Category;` — `UPROPERTY()` — The category assigned to the variable. Defaults to empty, which means no category.

#### class `UMovieGraphGlobalVariable`  
`class UMovieGraphGlobalVariable : public UMovieGraphVariable`  
_L164-178_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMovieGraphVariable`
- desc: Similar to normal UMovieGraphVariable instances. However, their values are provided by the graph, they cannot be edited/deleted, and they cannot be overridden at the job level.
- L169 _public prototype_ `UMovieGraphGlobalVariable();`
- L172 _public prototype_ `virtual void UpdateValue(const FMovieGraphTraversalContext* InTraversalContext, const UMovieGraphPipeline* InPipeline) PURE_VIRTUAL(UMovieGraphGlobalVariable::UpdateValue, );` — Update the internal value of the global variable.
- L175 _public prototype_ `virtual bool IsDeletable() const override;`
- L176 _public prototype_ `virtual bool CanRename(const FText& InNewName, FText& OutError) const override;`

#### class `UMovieGraphGlobalVariable_ShotName`  
`class UMovieGraphGlobalVariable_ShotName final : public UMovieGraphGlobalVariable`  
_L181-188_
- reflection: `UCLASS()`
- inherits: `UMovieGraphGlobalVariable`
- L186 _public prototype_ `UMovieGraphGlobalVariable_ShotName();`
- L187 _public prototype_ `virtual void UpdateValue(const FMovieGraphTraversalContext* InTraversalContext, const UMovieGraphPipeline* InPipeline) override;`

#### class `UMovieGraphGlobalVariable_SequenceName`  
`class UMovieGraphGlobalVariable_SequenceName final : public UMovieGraphGlobalVariable`  
_L191-198_
- reflection: `UCLASS()`
- inherits: `UMovieGraphGlobalVariable`
- L196 _public prototype_ `UMovieGraphGlobalVariable_SequenceName();`
- L197 _public prototype_ `virtual void UpdateValue(const FMovieGraphTraversalContext* InTraversalContext, const UMovieGraphPipeline* InPipeline) override;`

#### class `UMovieGraphGlobalVariable_FrameNumber`  
`class UMovieGraphGlobalVariable_FrameNumber final : public UMovieGraphGlobalVariable`  
_L201-208_
- reflection: `UCLASS()`
- inherits: `UMovieGraphGlobalVariable`
- L206 _public prototype_ `UMovieGraphGlobalVariable_FrameNumber();`
- L207 _public prototype_ `virtual void UpdateValue(const FMovieGraphTraversalContext* InTraversalContext, const UMovieGraphPipeline* InPipeline) override;`

#### class `UMovieGraphGlobalVariable_CameraName`  
`class UMovieGraphGlobalVariable_CameraName final : public UMovieGraphGlobalVariable`  
_L211-218_
- reflection: `UCLASS()`
- inherits: `UMovieGraphGlobalVariable`
- L216 _public prototype_ `UMovieGraphGlobalVariable_CameraName();`
- L217 _public prototype_ `virtual void UpdateValue(const FMovieGraphTraversalContext* InTraversalContext, const UMovieGraphPipeline* InPipeline) override;`

#### class `UMovieGraphInterfaceBase`  
`class UMovieGraphInterfaceBase : public UMovieGraphMember`  
_L224-232_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMovieGraphMember`
- desc: Common base class for input/output members on the graph.
- L231 _public member_ `bool bIsBranch = true;` — `UPROPERTY(EditAnywhere, Category = "Value", meta=(EditCondition="bIsEditable", HideEditConditionToggle))` — Whether this interface member represents a branch. If not a branch, then a value is associated with it.

#### class `UMovieGraphInput`  
`class UMovieGraphInput : public UMovieGraphInterfaceBase`  
_L238-259_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphInterfaceBase`
- desc: An input exposed on the graph that will be available for nodes to connect to.
- L243 _public prototype_ `UMovieGraphInput() = default;`
- L246 _public prototype_ `virtual bool IsDeletable() const override;`
- L247 _public prototype_ `virtual bool CanRename(const FText& InNewName, FText& OutError) const override;`
- L248 _public prototype_ `virtual bool SetMemberName(const FString& InNewName) override;`
- L253 _public member_ `FOnMovieGraphInputChanged OnMovieGraphInputChangedDelegate;`
- L256 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### class `UMovieGraphOutput`  
`class UMovieGraphOutput : public UMovieGraphInterfaceBase`  
_L265-286_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphInterfaceBase`
- desc: An output exposed on the graph that will be available for nodes to connect to.
- L270 _public prototype_ `UMovieGraphOutput() = default;`
- L273 _public prototype_ `virtual bool IsDeletable() const override;`
- L274 _public prototype_ `virtual bool CanRename(const FText& InNewName, FText& OutError) const override;`
- L275 _public prototype_ `virtual bool SetMemberName(const FString& InNewName) override;`
- L280 _public member_ `FOnMovieGraphOutputChanged OnMovieGraphOutputChangedDelegate;`
- L283 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### struct `FMovieGraphEvaluatedSettingsStack`  
`struct FMovieGraphEvaluatedSettingsStack`  
_L297-303_
- reflection: `USTRUCT()`
- L302 _public member_ `TArray<TObjectPtr<UMovieGraphNode>> NodeInstances;` — `UPROPERTY(Transient)`

#### struct `FMovieGraphEvaluatedBranchConfig`  
`struct FMovieGraphEvaluatedBranchConfig`  
_L311-379_
- reflection: `USTRUCT()`
- desc: A flattened list of configuration values for a given Graph Branch. For named branches, this includes the "Globals" branch (for any value not also overridden by the named branch).
- L315 _public function_ `UMovieGraphNode* GetNodeByClassExactMatch(const TSubclassOf<UMovieGraphNode>& InClass, const FString& InName) const`
- L331 _public function_ `TArray<TObjectPtr<UMovieGraphNode>> GetNodes() const`
- L343 _public function_ `void RemoveNodesOfType(const TSubclassOf<UMovieGraphNode>& InClass)` — Removes all nodes that are subclasses of the given type from the evaluated config.
- L378 _private member_ `TMap<FString, FMovieGraphEvaluatedSettingsStack> NamedNodes;` — `UPROPERTY(Transient)` — Nodes that have been evaluated in the branch. Key: the node instance name, value: the nodes that share the instance name. For nodes that do not have an instance name, an empty string is the key.

#### struct `FMovieGraphEvaluationContext_VisitedNodeInfo`  
`struct FMovieGraphEvaluationContext_VisitedNodeInfo`  
_L384-391_
- reflection: `USTRUCT()`
- desc: Information on visited nodes found during traversal.
- L390 _public member_ `TSet<TObjectPtr<UMovieGraphNode>> VisitedNodes;` — `UPROPERTY()` — The nodes that were visited during traversal.

#### struct `FMovieGraphEvaluationContext`  
`struct FMovieGraphEvaluationContext`  
_L399-447_
- reflection: `USTRUCT()`
- desc: This stores short-term information needed during traversal of the graph such as disabled nodes, already visited nodes, etc. This information is discarded after traversal.
- L409 _public member_ `FMovieGraphTraversalContext UserContext;` — `UPROPERTY()` — This is the user provided traversal context which specifies high level user decisions. This is the calling context such as what frame you're on, or what the shot name is, stuff generally driven by global variables.
- L415 _public member_ `TMap<TObjectPtr<const UMovieGraphConfig>, FMovieGraphEvaluationContext_VisitedNodeInfo> VisitedNodesByOwningGraph;` — `UPROPERTY()` — A list of nodes that have been visited, where the key is the graph where the node was found. Used for cycle detection right now.
- L421 _public member_ `TObjectPtr<UMovieGraphPin> PinBeingFollowed;` — `UPROPERTY()` — The pin that is currently being followed in the traversal process.
- L428 _public member_ `TArray<TObjectPtr<const UMovieGraphSubgraphNode>> SubgraphStack;` — `UPROPERTY()` — The current stack of subgraphs that are being visited. The last subgraph in the stack is the one currently being visited. If no subgraphs are in this stack, then the parent-most graph is being traversed currently.
- L434 _public member_ `bool bCircularGraphReferenceFound = false;` — `UPROPERTY()` — Whether a circular graph reference was found during traversal.
- L440 _public member_ `FText TraversalError;` — `UPROPERTY()` — The error that was generated during traversal. A non-empty string implies that the traversal did not complete successfully.
- L446 _public member_ `TArray<TSubclassOf<UMovieGraphSettingNode>> NodeTypesToRemoveStack;` — The stack of node types (exact match) that should be removed from the graph while it is being traversed. Each node which specifies a type to removed adds to the stack.

#### class `UMovieGraphEvaluatedConfig`  
`class UMovieGraphEvaluatedConfig : public UObject`  
_L456-606_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: An evaluated config for the current frame. Each named branch (including Globals) has its own copy of the config, fully resolved (so there is no need to check the Globals branch when looking at a named branch). You can use the functions to fetch a node by type from a given branch and it will return the right object (or the CDO if the node is NOT in the config).
- L462 _public function_ `const TArray<FName> GetBranchNames() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L470 _public function_ `UMovieGraphSettingNode* GetSettingForBranch(UClass* InClass, const FName InBranchName, bool bIncludeCDOs = true, bool bExactMatch = false) const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L482 _public function_ `TArray<UMovieGraphSettingNode*> GetSettingsForBranch(UClass* InClass, const FName InBranchName, bool bIncludeCDOs = true, bool bExactMatch = false) const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L513 _public function_ `template<typename InterfaceType> TArray<InterfaceType*> GetSettingsImplementing(const UClass* InInterfaceClass, const FName InBranchName) const` — Gets settings that implement a specific interface. InInterfaceClass should be the U-prefixed class; InterfaceType should be I-prefixed.
- L537 _public function_ `template<typename NodeType> NodeType* GetSettingForBranch(const FName InBranchName, bool bIncludeCDOs = true, bool bExactMatch = false) const`
- L543 _public function_ `template<typename NodeType> TArray<NodeType*> GetSettingsForBranch(const FName InBranchName, bool bIncludeCDOs = true, bool bExactMatch = false) const`
- L568 _public prototype_ `UPARAM(DisplayName = "Variable Name") const FString& InVariableName, UPARAM(DisplayName = "Value Container") UMovieGraphValueContainer*& OutVariab`
- L578 _public prototype_ `UPARAM(DisplayName = "Variable Name") const FString& InVariableName, UPARAM(DisplayName = "Default Value") const FString& InDefaultValue, UPARAM(DisplayName = "String Value") FString& OutVariableV`
- L584 _public prototype_ `const TArray<UMovieGraphConfig*>& GetEvaluatedGraphs() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets all of the graphs that were included in the evaluation process.
- L589 _public member_ `TMap<FName, FMovieGraphEvaluatedBranchConfig> BranchConfigMapping;` — `UPROPERTY(Transient)` — Mapping between named branches (at the root of the config) and their evaluated values.
- L602 _private member_ `TMap<FString, TArray<UMovieGraphValueContainer*>> VariablesByName;` — The fully-evaluated values of all variables used in all graphs traversed in the evaluated result. The key is the variable name, and the value is the resolved value of the variable. If there is more than one entry in the array, that means that multiple graphs used the same variable name. This is not an error, but it makes fetching a variable by name challenging without any additional context. For future use, all variables with the same name are gathered, where the first in the array is the variable from the parent-most graph, and so on down the chain of subgraphs.
- L605 _private member_ `TArray<UMovieGraphConfig*> EvaluatedGraphs;` — All of the graphs that were included in the evaluation process.

#### class `UMovieGraphTraversableObject`  
`class UMovieGraphTraversableObject : public UInterface`  
_L609-612_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMovieGraphTraversableObject`  
`class IMovieGraphTraversableObject`  
_L618-633_
- desc: Provides a way for objects, which would otherwise not be mergeable during a traversal, to merge in a well-defined way. Also allows objects to expose which properties have been affected by the merge.
- L624 _public function_ `virtual void Merge(const IMovieGraphTraversableObject* InSourceObject)` — Merges the contents of InSourceClass into this object.
- L632 _public function_ `virtual TArray<TPair<FString, FString>> GetMergedProperties() const` — Gets properties, and their associated values, which have been modified by a merge. Key = property name, value = stringified value The stringified value is a representation of the value which will usually be displayed in the UI. It does not need to be a serialized representation.

#### class `UMovieGraphConfig`  
`class UMovieGraphConfig : public UObject`  
_L641-1088_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: This is the runtime representation of the UMoviePipelineEdGraph which contains the actual strongly typed graph network that is read by the MoviePipeline. There is an editor-only representation of this graph (UMoviePipelineEdGraph).
- L646 _public prototype_ `UMovieGraphConfig();`
- L654 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FVisitNodesCallback, UMovieGraphNode*, const UMovieGraphPin*);` — Callback for when a node is visited. The node is the node being visited, and the pin is the pin which the node was accessed by (eg, if visiting downstream nodes, the pin will be the input pin that connects to the node that the traversal started from, or the node that was previously visited). Return true to continue traversal, or false to stop traversal.
- L657 _public prototype_ `virtual void PostLoad() override;`
- L666 _public prototype_ `bool AddLabeledEdge(UMovieGraphNode* FromNode, const FName& FromPinLabel, UMovieGraphNode* ToNode, const FName& ToPinLabel);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Add a connection in the graph between the given nodes and pin names. Pin name may be empty for basic nodes (if no name is displayed in the UI). Can be used for either input or output pins. Returns False if the pin could not be found, or the connection could not be made (type mismatches).
- L672 _public prototype_ `bool RemoveLabeledEdge(UMovieGraphNode* FromNode, const FName& FromPinName, UMovieGraphNode* ToNode, const FName& ToPinName);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Like AddLabeledEdge, removes the given connection between Node A and Node B (for the specified pins by name).
- L678 _public prototype_ `bool RemoveAllInboundEdges(UMovieGraphNode* InNode);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Convenience function which removes all Inbound (pins on the left side of a node) edges for the given node.
- L684 _public prototype_ `bool RemoveAllOutboundEdges(UMovieGraphNode* InNode);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Convenience function which removes all Outbound (pins on the right side of a node) edges for the given node.
- L690 _public prototype_ `bool RemoveInboundEdges(UMovieGraphNode* InNode, const FName& InPinName);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Convenience function which removes all Inbound (pins on the left side of a node) edges connected to the given inbound pin by name, for the given node.
- L696 _public prototype_ `bool RemoveOutboundEdges(UMovieGraphNode* InNode, const FName& InPinName);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Convenience function which removes all Outbound (pins on the right side of a node) edges connected to the given outbound pin by name, for the given node.
- L704 _public prototype_ `UMovieGraphNode* InsertBefore(UMovieGraphNode* InTargetNode, const TSubclassOf<UMovieGraphNode> InNodeClass, const FName& InTargetPinLabel = FName());` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Creates a new node of the given class and inserts it immediately upstream (to the left) of InTargetNode on the specified input pin (defaults to the unnamed pin). Any node previously connected to that input is reconnected upstream of the new node. Returns the newly created node, or nullptr on failure.
- L713 _public prototype_ `UMovieGraphNode* InsertAfter(UMovieGraphNode* InTargetNode, const TSubclassOf<UMovieGraphNode> InNodeClass, const FName& InTargetPinLabel = FName());` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Creates a new node of the given class and inserts it immediately downstream (to the right) of InTargetNode on the specified output pin (defaults to the unnamed pin). The first downstream connection on that pin is reconnected downstream of the new node; if the pin has multiple connections, the caller should manage additional reconnections manually. Returns the newly created node, or nullptr on failure.
- L722 _public prototype_ `void AddNode(UMovieGraphNode* InNode);` — Add the specified node instance to the graph. This will rename the node to ensure the graph is the outer and then it will add it to the internal list of nodes used by the graph. See ConstructRuntimeNode if you want to construct a node by class and don't already have an instance. Not currently exposed to the Blueprint API as it's generally internal use only.
- L726 _public prototype_ `bool RemoveNode(UMovieGraphNode* InNode);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Removes the specified node from the graph, disconnecting connected edges as it goes.
- L730 _public prototype_ `bool RemoveNodes(TArray<UMovieGraphNode*> InNodes);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Like RemoveNode but takes an entire array at once for convenience.
- L734 _public function_ `UMovieGraphNode* GetInputNode() const` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the automatically generated "Inputs" node in the Graph.
- L738 _public function_ `UMovieGraphNode* GetOutputNode() const` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Gets the automatically generated "Outputs" node in the Graph.
- L740 _public function_ `const TArray<TObjectPtr<UMovieGraphNode>>& GetNodes() const`
- L744 _public prototype_ `TArray<FName> GetBranchNames() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Returns an array of the branch names for the OutputNode on this Graph.
- L760 _public prototype_ `UMovieGraphNode* GetNodeForBranch(UClass* InClass, const FName& InBranchName, bool bExactMatch = false) const;` — `UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InClass"), Category = "Movie Graph")` — Finds a node (by type) for the given branch name (see GetBranchNames()). Returns the first result of that type found, even if there are multiple, following traversal order (ie: right to left). To prevent accidentally editing unrelated assets, does not dive into sub-graphs (but can continue traversal beyond them), so returned results should only exist in current asset. Does not contain the Input or Output nodes, see GetInputNode() and GetOutputNode(). @param InClass - The node class type to search for. Use UMovieGraphSettingNode to only include nodes that show up in the final evaluated graph (excludes nodes like the Branch node). @param InBranchName - The branch to search for these nodes on. @param bExactMatch - Defaults false. If true, will not consider inherited classes of InClass. (ie: If requesting a base class and only child classes exist, they will not count when using exact matching). @return First node found (if any) which are of the specified InClass type on the given branch.
- L776 _public prototype_ `TArray<UMovieGraphNode*> GetNodesForBranch(UClass* InClass, const FName& InBranchName, bool bExactMatch = false) const;` — `UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InClass"), Category = "Movie Graph")` — Finds all nodes (by type) for the given branch name (see GetBranchNames()). Returns all results of that type following traversal order (ie: right to left). To prevent accidentally editing unrelated assets, does not dive into sub-graphs (but can continue traversal beyond them), so returned results should only exist in current asset. Does not contain the Input or Output nodes, see GetInputNode() and GetOutputNode(). @param InClass - The node class type to search for. Use UMovieGraphSettingNode to only include nodes that show up in the final evaluated graph (excludes nodes like the Branch node). @param InBranchName - The branch to search for these nodes on. @param bExactMatch - Defaults false. If true, will not consider inherited classes of InClass. (ie: If requesting a base class and only child classes exist, they will not count when using exact matching). @return All nodes found (if any) which are of the specified InClass type on the given branch.
- L796 _public prototype_ `UMovieGraphNode* GetNodeForTag(const FString& ScriptTag, UClass* OptionalClassFilter = nullptr, const FName OptionalBranchFilter = NAME_None, bool bExactMatch = false) const;` — `UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "OptionalClassFilter"), Category = "Movie Graph")` — Finds a node by ScriptTag field. THIS SEARCH IS CASE SENSITIVE. Returns the first result of that tag found, even if there are multiple, following traversal order (ie: right to left). If OptionalClassFilter is specified, only matches against nodes that have the right class type and contain the correct tag. To prevent accidentally editing unrelated assets, does not dive into sub-graphs (but can continue traversal beyond them), so returned results should only exist in current asset. Does not contain the Input or Output nodes, see GetInputNode() and GetOutputNode(). @param ScriptTag - Case sensitive name into the "Script Tags" property on Nodes @param OptionalClassFilter - Defaults None. If specified, will only return a node of this class that matches the tag. Use UMovieGraphSettingNode to only include nodes that show up in the final evaluated graph (excludes nodes like the Branch node). @param OptionalBranchFilter - Defaults None. If specified, will only search the specified branch, otherwise searches all branches. @param bExactMatch - Defaults false. If true, will not consider inherited classes to pass the OptionalClassFilter. (ie: If requesting a base class and only child classes exist, they will not count when using exact matching). @return The first node found (if any) which contains the case-sensitive tag and is of the correct class type (if using OptionalClassFilter)
- L816 _public prototype_ `TArray<UMovieGraphNode*> GetNodesForTag(const FString& ScriptTag, UClass* OptionalClassFilter = nullptr, const FName OptionalBranchFilter = NAME_None, bool bExactMatch = false) const;` — `UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "OptionalClassFilter"), Category = "Movie Graph")` — Finds nodes by ScriptTag field. THIS SEARCH IS CASE SENSITIVE. Returns all results of that tag found, following traversal order (ie: right to left). If OptionalClassFilter is specified, only matches against nodes that have the right class type and contain the correct tag. To prevent accidentally editing unrelated assets, does not dive into sub-graphs (but can continue traversal beyond them), so returned results should only exist in current asset. Does not contain the Input or Output nodes, see GetInputNode(), GetOutputNode()) @param ScriptTag - Case sensitive name into the "Script Tags" property on Nodes @param OptionalClassFilter - Defaults None. If specified, will only return a node of this class that matches the tag. Use UMovieGraphSettingNode to only include nodes that show up in the final evaluated graph (excludes nodes like the Branch node). @param OptionalBranchFilter - Defaults None. If specified, will only search the specified branch, otherwise searches all branches. @param bExactMatch - Defaults false. If true, will not consider inherited classes to pass the OptionalClassFilter. (ie: If requesting a base class and only child classes exist, they will not count when using exact matching). @return All nodes found (if any) which contain the case-sensitive tag and are of the correct class type (if using OptionalClassFilter)
- L823 _public prototype_ `UMovieGraphVariable* AddVariable(const FName InCustomBaseName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Adds a new variable member with default values to the graph. The new variable will have a base name of "Variable" unless specified in InCustomBaseName. Returns the new variable on success, else nullptr.
- L832 _public prototype_ `UMovieGraphInput* AddInput(const FText& InBaseName = FText::GetEmpty());` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Adds a new input member to the graph. Returns the new input on success, else nullptr. The default name of the input is "Input". Optionally, InBaseName can be specified to add the input with a specific name. If the name "Input" (or the custom InBaseName) isn't available, a numerical suffix will be added.
- L841 _public prototype_ `UMovieGraphOutput* AddOutput(const FText& InBaseName = FText::GetEmpty());` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Adds a new output member to the graph. Returns the new output on success, else nullptr. The default name of the output is "Output". Optionally, InBaseName can be specified to add the output with a specific name. If the name "Output" (or the custom InBaseName) isn't available, a numerical suffix will be added.
- L845 _public prototype_ `UMovieGraphVariable* GetVariableByGuid(const FGuid& InGuid) const;` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Gets the variable in the graph with the specified GUID, else nullptr if one could not be found.
- L849 _public prototype_ `UMovieGraphVariable* GetVariableByName(const FString& InVariableName) const;` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Gets the variable in the graph with the specified name (including global variables), else nullptr if one could not be found.
- L856 _public prototype_ `TArray<UMovieGraphVariable*> GetVariables(const bool bIncludeGlobal = false) const;` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Gets all variables that are available to be used in the graph. Global variables can optionally be included if bIncludeGlobal is set to true.
- L860 _public prototype_ `void UpdateGlobalVariableValues(const UMovieGraphPipeline* InPipeline);` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Updates the values of all global variables.
- L864 _public prototype_ `TArray<UMovieGraphInput*> GetInputs() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets all inputs that have been defined on the graph.
- L868 _public prototype_ `TArray<UMovieGraphOutput*> GetOutputs() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets all outputs that have been defined on the graph.
- L872 _public prototype_ `bool DeleteMember(UMovieGraphMember* MemberToDelete);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Remove the specified member (input, output, variable) from the graph.
- L876 _public prototype_ `UMovieGraphVariable* DuplicateVariable(UMovieGraphVariable* InVariableToDuplicate);` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Duplicates the provided variable. Returns the new variable on success, else nullptr.
- L880 _public function_ `const TArray<TObjectPtr<UObject>>& GetEditorOnlyNodes() const` — Gets the editor-only nodes in this graph. Editor-only nodes do not have an equivalent runtime node.
- L883 _public prototype_ `void SetEditorOnlyNodes(const TArray<TObjectPtr<const UObject>>& InNodes);` — Sets the editor-only nodes in this graph.
- L891 _public prototype_ `UMovieGraphEvaluatedConfig* CreateFlattenedGraph(const FMovieGraphTraversalContext& InContext, FString& OutError);` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Given a user-defined evaluation context, evaluate the graph and build a "flattened" list of settings for each branch discovered. If there was an error while evaluating the graph, nullptr will be returned and OutError will be populated with a description of the problem.
- L894 _public prototype_ `static FBoolProperty* FindOverridePropertyForRealProperty(UClass* InClass, const FProperty* InRealProperty);` — Given a class and FProperty that belongs to that class, search for a FBoolProperty that matches the name "bOverride_<name of InRealProperty>.
- L900 _public prototype_ `void VisitUpstreamNodes(UMovieGraphNode* FromNode, const FVisitNodesCallback& VisitCallback) const;` — Visits all nodes upstream from FromNode, running VisitCallback on each one. Note this only follows branch connections, and does not recurse into subgraphs.
- L906 _public prototype_ `void VisitDownstreamNodes(UMovieGraphNode* FromNode, const FVisitNodesCallback& VisitCallback) const;` — Visits all nodes downstream from FromNode, running VisitCallback on each one. Note this only follows branch connections, and does not recurse into subgraphs.
- L913 _public prototype_ `TArray<FString> GetDownstreamBranchNames(UMovieGraphNode* FromNode, const UMovieGraphPin* FromPin, const bool bStopAtSubgraph = false) const;` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Determines the name(s) of the branches downstream from FromNode, starting at FromPin. Optionally, subgraph nodes can halt graph traversal if bStopAtSubgraph is set to true.
- L920 _public prototype_ `TArray<FString> GetUpstreamBranchNames(UMovieGraphNode* FromNode, const UMovieGraphPin* FromPin, const bool bStopAtSubgraph = false) const;` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Determines the name(s) of the branches upstream from FromNode, starting at FromPin. Optionally, subgraph nodes can halt graph traversal if bStopAtSubgraph is set to true.
- L924 _public prototype_ `void GetAllContainedSubgraphs(TSet<UMovieGraphConfig*>& OutSubgraphs) const;` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Get all subgraphs that this graph contains, recursively (ie, subgraphs of subgraphs are included, etc).
- L931 _public prototype_ `void GetOutputDirectory(FString& OutOutputDirectory) const;` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Walks the graph backward recursively from the output node searching for a UMovieGraphOutputSettings node. Traverses subgraphs as well. If a node is not found with an override set, value is taken from the CDO of UMovieGraphOutputSettings.
- L938 _public prototype_ `void MoveVariableBefore(UMovieGraphVariable* InTargetVariable, UMovieGraphVariable* InBeforeVariable);` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Moves one variable (InTargetVariable) before another variable (InBeforeVariable). Takes care of ensuring the variable's category is set properly after the move.
- L947 _public prototype_ `void MoveVariableToIndex(UMovieGraphVariable* InTargetVariable, int32 NewIndex);` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Moves one variable (InTargetVariable) to the specified index among all user graph variables. Note that MoveVariableBefore() should be used in almost all cases unless there is very specific use case. This method will not take care of setting the category for you after the move unlike MoveVariableBefore().
- L951 _public prototype_ `void MoveCategoryBefore(const FString& InCategoryToMove, const FString& InCategoryBefore);` — `UFUNCTION(BlueprintCallable, Category="Movie Graph")` — Moves one category (InCategoryToMove) and its variables before another category (InCategoryBefore).
- L955 _protected prototype_ `void RecurseUpGlobalsBranchToFindOutputDirectory(const UMovieGraphNode* InNode, FString& OutOutputDirectory, TArray<const UMovieGraphConfig*>& VisitedGraphStack) const;` — Look for the output directory in the UMovieGraphOutputSettings nodes found upstream of InNode.
- L958 _protected prototype_ `void CopyOverriddenProperties(UMovieGraphNode* FromNode, UMovieGraphNode* ToNode, const FMovieGraphEvaluationContext& InEvaluationContext);` — Copies properties in FromNode that are marked for override into ToNode, but only if ToNode doesn't already override that value.
- L961 _protected prototype_ `void InitializeFlattenedNode(UMovieGraphNode* InNode);` — Find all "Overrideable" marked properties, then find their edit condition properties, then set those to false.
- L967 _protected prototype_ `bool CreateFlattenedGraph_Recursive(UMovieGraphEvaluatedConfig* InOwningConfig, FMovieGraphEvaluatedBranchConfig& OutBranchConfig, FMovieGraphEvaluationContext& InEvaluationContext, UMovieGraphPin* InPinToFollow);` — Traverse the graph, generating a combined "flatten" graph as it goes. Returns false if there was an issue (and the evaluation context will be updated with more details regarding the failure).
- L971 _protected prototype_ `void VisitUpstreamNodes_Recursive(UMovieGraphNode* FromNode, const FVisitNodesCallback& VisitCallback, TSet<UMovieGraphNode*>& VisitedNodes) const;` — Recursive helper for VisitUpstreamNodes().
- L974 _protected prototype_ `void VisitDownstreamNodes_Recursive(UMovieGraphNode* FromNode, const FVisitNodesCallback& VisitCallback, TSet<UMovieGraphNode*>& VisitedNodes) const;` — Recursive helper for VisitDownstreamNodes().
- L978 _public member_ `FOnMovieGraphChanged OnGraphChangedDelegate;`
- L979 _public member_ `FOnMovieGraphVariablesChanged OnGraphVariablesChangedDelegate;`
- L980 _public member_ `FOnMovieGraphInputAdded OnGraphInputAddedDelegate;`
- L981 _public member_ `FOnMovieGraphOutputAdded OnGraphOutputAddedDelegate;`
- L982 _public member_ `FOnMovieGraphNodesDeleted OnGraphNodesDeletedDelegate;`
- L987 _protected member_ `TArray<TObjectPtr<UMovieGraphNode>> AllNodes;` — `UPROPERTY()`
- L990 _protected member_ `TObjectPtr<UMovieGraphNode> InputNode;` — `UPROPERTY()`
- L993 _protected member_ `TObjectPtr<UMovieGraphNode> OutputNode;` — `UPROPERTY()`
- L1006 _public member_ `TObjectPtr<UEdGraph> PipelineEdGraph;` — `UPROPERTY()` — Not strongly typed to avoid a circular dependency between the editor only module and the runtime module, but it should be a UMoviePipelineEdGraph. Note that the editor graph is saved with the runtime graph. This is done to prevent the runtime graph from being dirtied immediately upon loading (because the editor graph would have to be re-created from the runtime graph, thus dirtying the package). If the runtime graph representation is modified outside of the editor (eg, programmatically via the UMovieGraphConfig API directly), this should be nulled out so the editor can rebuild its representation the next time it is loaded. If the editor representation of the graph isn't important (ie, the graph is transient) then this is unnecessary.
- L1014 _public function_ `UMovieGraphNode* CreateNodeByClass(const TSubclassOf<UMovieGraphNode> InClass)` — `UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InClass"), Category = "Movie Graph")` — Creates the given node type in this graph. Does not create any connections, and a node will not be considered during evaluation unless it is connected to other nodes in the graph.
- L1037 _public function_ `template<class T> T* ConstructRuntimeNode(TSubclassOf<UMovieGraphNode> PipelineGraphNodeClass = T::StaticClass())`
- L1044 _private prototype_ `bool DeleteVariableMember(UMovieGraphVariable* VariableMemberToDelete);` — Remove the specified variable member from the graph.
- L1047 _private prototype_ `bool DeleteInputMember(UMovieGraphInput* InputMemberToDelete);` — Remove the specified input member from the graph.
- L1050 _private prototype_ `bool DeleteOutputMember(UMovieGraphOutput* OutputMemberToDelete);` — Remove the specified output member from the graph.
- L1057 _private prototype_ `template<typename RetType, typename ArrType> RetType* AddMember(TArray<TObjectPtr<ArrType>>& InMemberArray, const FName& InBaseName);` — Add a new member of type RetType to MemberArray (ArrType, which RetType must derive from), with a unique name that includes BaseName in it.
- L1061 _private prototype_ `template<typename T> T* AddGlobalVariable();` — Adds a global variable of type T to the graph.
- L1064 _private prototype_ `void AddDefaultMembers();` — Adds members to the graph that should always be available.
- L1069 _private member_ `TArray<TObjectPtr<UMovieGraphVariable>> Variables;` — `UPROPERTY()` — All user (not global) variables which are available for use in the graph.
- L1073 _private member_ `TArray<TObjectPtr<UMovieGraphGlobalVariable>> GlobalVariables;` — `UPROPERTY()` — All global variables which are available for use in the graph.
- L1077 _private member_ `TArray<TObjectPtr<UMovieGraphInput>> Inputs;` — `UPROPERTY()` — All inputs which have been defined on the graph.
- L1081 _private member_ `TArray<TObjectPtr<UMovieGraphOutput>> Outputs;` — `UPROPERTY()` — All outputs which have been defined on the graph.
- L1086 _private member_ `TArray<TObjectPtr<UObject>> EditorOnlyNodes;` — `UPROPERTY()` — Nodes which are only useful in the editor (like comments) and have no runtime equivalent

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphVariableChanged, class UMovieGraphMember*);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphVariableChanged, class UMovieGraphMember*);`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphInputChanged, class UMovieGraphMember*);`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphInputChanged, class UMovieGraphMember*);`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphOutputChanged, class UMovieGraphMember*);`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphOutputChanged, class UMovieGraphMember*);`
- L78 _function_ `` (scope `UMovieGraphMember::IsUniqueNameInMemberArray`)
- L289 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMovieGraphChanged);`
- L289 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMovieGraphChanged);`
- L290 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMovieGraphVariablesChanged);`
- L290 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMovieGraphVariablesChanged);`
- L291 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphInputAdded, UMovieGraphInput*);`
- L291 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphInputAdded, UMovieGraphInput*);`
- L292 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphOutputAdded, UMovieGraphOutput*);`
- L292 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphOutputAdded, UMovieGraphOutput*);`
- L293 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphNodesDeleted, TArray<UMovieGraphNode*>);`
- L293 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphNodesDeleted, TArray<UMovieGraphNode*>);`
- L351 _function_ `` (scope `FMovieGraphEvaluatedBranchConfig::RemoveNodesOfType`)
- L654 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FVisitNodesCallback, UMovieGraphNode*, const UMovieGraphPin*);` — Callback for when a node is visited. The node is the node being visited, and the pin is the pin which the node was accessed by (eg, if visiting downstream nodes, the pin will be the input pin that connects to the node that the traversal started from, or the node that was previously visited). Return true to continue traversal, or false to stop traversal.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphCoreTimeStep.h` (Public)


#### class `UMovieGraphCoreTimeStep`  
`class UMovieGraphCoreTimeStep : public UMovieGraphTimeStepBase`  
_L25-167_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMovieGraphTimeStepBase`
- desc: Provides common logic for typical time-step functionality. The number of temporal sub-samples is read from the graph for each output frame, and we then take the time the shutter is open and break it into that many sub-samples. Subclasses must implement GetNextTemporalRangeIndex() to indicate the index of the next temporal sub-sample.
- L29 _public prototype_ `UMovieGraphCoreTimeStep();`
- L32 _public prototype_ `virtual void Initialize() override;` — UMovieGraphTimeStepBase Interface
- L33 _public prototype_ `virtual void Shutdown() override;`
- L34 _public prototype_ `virtual void TickProducingFrames() override;`
- L35 _public function_ `virtual FMovieGraphTimeStepData GetCalculatedTimeData() const override`
- L36 _public prototype_ `virtual bool IsExpansionForTSRequired(const TObjectPtr<UMovieGraphEvaluatedConfig>& InConfig) const override;`
- L41 _protected prototype_ `virtual void UpdateShutterRanges();` — Update CurrentFrameData.RangeShutterOpen and CurrentFrameData.RangeShutterClosed.
- L44 _protected prototype_ `virtual void UpdateTemporalRanges();` — Update CurrentFrameData.TemporalRanges.
- L50 _protected prototype_ `virtual int32 GetNextTemporalRangeIndex() const PURE_VIRTUAL(UMovieGraphCoreTimeStep::GetNextTemporalRangeIndex, return 0; );` — Gets the index of the next temporal range. The index returned should not be the index returned by the prior call (this would result in a frame delta time of zero, causing the engine to crash).
- L53 _protected prototype_ `virtual bool IsLastTemporalSample() const;` — Determines if the current sample being rendered is the last.
- L56 _protected prototype_ `virtual int32 GetTemporalSampleCount() const PURE_VIRTUAL(UMovieGraphCoreTimeStep::UpdateTemporalSampleCount, return 0; );` — Gets the number of samples that should be used in each frame.
- L58 _protected prototype_ `virtual void UpdateFrameMetrics();`
- L59 _protected prototype_ `virtual bool IsFirstTemporalSample() const;`
- L60 _protected prototype_ `virtual void ResetForEndOfOutputFrame();`
- L61 _protected prototype_ `virtual float GetBlendedMotionBlurAmount();`
- L62 _protected prototype_ `virtual int32 GetTemporalSampleCountFromConfig(UMovieGraphEvaluatedConfig* InConfig) const;`
- L67 _protected member_ `FMovieGraphTimeStepData CurrentTimeStepData;` — `UPROPERTY(Transient)` — This is the output data needed by the rest of MRQ to produce a frame.
- L154 _protected member_ `FOutputFrameMetrics CurrentFrameMetrics;` — A set of cached values that are true for the current output frame. They will be recalculated at the start of the next output frame.
- L160 _protected member_ `FCurrentFrameData CurrentFrameData;` — Frame Metrics are constant data updated once per output frame, while CurrentFrameData is keeping track across engine ticks to work towards producing a single frame.
- L166 _protected member_ `bool bPrevWorldAllowTimeDilation = true;` — Was the world allowing time dilation before this render started? We'll cache and then restore this value to avoid changing any user settings.

#### struct `UMovieGraphCoreTimeStep::FOutputFrameMetrics`  
`struct FOutputFrameMetrics`  
_L69-109_
- L71 _public function_ `FOutputFrameMetrics() : MotionBlurAmount(0.f) , TimeDilation(1.f)`
- L77 _public member_ `FFrameRate FrameRate;` — The human readable frame rate, adjusted by the config file (24fps, 30fps, etc.)
- L80 _public member_ `FFrameRate TickResolution;` — The internal resolution data is actually stored at. (24,000, 120,000 etc.)
- L83 _public member_ `FFrameTime FrameTimePerOutputFrame;` — The amount of time (in Tick Resolution) that represents one output frame (ie: 1/24).
- L86 _public member_ `float MotionBlurAmount;` — The 0-1 Motion Blur amount the camera has.
- L89 _public member_ `float TimeDilation;` — The time dilation multiplier set by the world, 1.0 if there is no time dilation being applied.
- L92 _public member_ `FFrameTime FrameTimeWhileShutterOpen;` — The amount of time (in Tick Resolution) that the shutter is open for. Could be <= FrameTimePerOutputFrame.
- L99 _public member_ `FFrameTime FrameTimePerTemporalSample;` — The amount of time (in Tick Resolution) per temporal sample. The actual time slice for a temporal sub-sample may be different than this (as we have to jump over the time period that the shutter is closed too for one temporal sub-sample.
- L102 _public member_ `FFrameTime FrameTimeWhileShutterClosed;` — The inverse of FrameTimeWhileShutterOpen. ShutterClosed+ShutterOpen should add up to FrameTimePerOutputFrame.
- L105 _public member_ `FFrameTime ShutterOffsetFrameTime;` — A constant offset applied to the final evaluated time to allow users to influence what counts as a frame. (the time before, during, or after a frame)
- L108 _public member_ `FFrameTime MotionBlurCenteringOffsetTime;` — An offset to the evaluated time to get us into the center of the time period (since motion blur is bi-directional and centered)

#### struct `UMovieGraphCoreTimeStep::FCurrentFrameData`  
`struct FCurrentFrameData`  
_L111-148_
- L113 _public function_ `FCurrentFrameData() : TemporalSampleIndex(0) , TemporalSampleCount(0)`
- L120 _public member_ `int32 TemporalSampleIndex;` — Which temporal sub-sample are we working on? [0,TemporalSampleCount)
- L123 _public member_ `int32 TemporalSampleCount;` — How many temporal sub-samples are there for the current output frame?
- L126 _public member_ `TRange<FFrameTime> LastOutputFrameRange;` — A range of time (in Tick Resolution) for the last output frame being worked on. Updated before first TS of next frame.
- L129 _public member_ `TRange<FFrameTime> CurrentOutputFrameRange;` — A range of time (in Tick Resolution) for the current frame being worked on. Represents the whole output frame (shutter closed + open).
- L132 _public member_ `TRange<FFrameTime> RangeShutterOpen;` — A range of time (in Tick Resolution) that the shutter is opened.
- L135 _public member_ `TRange<FFrameTime> RangeShutterClosed;` — A range of time (in Tick Resolution) that the shutter is closed. Can be an empty range (when using MotionBlurAmount=1.0)
- L141 _public member_ `TRange<FFrameTime> LastSampleRange;` — A range of time (in Tick Resolution) for the last temporal sub-sample (ie: what the last tick rendered with). We don't track CurrentSampleRange as it's just TemporalRanges[TemporalSampleIndex].
- L144 _public member_ `TArray<TRange<FFrameTime>> TemporalRanges;` — A pre-calculated (when the output frame starts) range of time, breaking RangeShutterOpen into smaller chunks, one per temporal sub-sample.
- L147 _public member_ `TStrongObjectPtr<UMovieGraphEvaluatedConfig> EvaluatedConfig;` — Updated at the start of each Temporal Sample.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphDataTypes.h` (Public)


#### struct `FMovieGraphPreviewBannerMessage`  
`struct FMovieGraphPreviewBannerMessage`  
_L44-59_
- reflection: `USTRUCT(BlueprintType)`
- desc: A message that a render pass can overlay on its preview image in the Render Preview window.
- L50 _public member_ `FText Message;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — The message text to display over the preview tile.
- L54 _public member_ `FLinearColor TextColor = FLinearColor::White;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — The color used by the message text.
- L58 _public member_ `FLinearColor BackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.5f);` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — The background color of the banner behind the message text.

#### struct `FMovieGraphImagePreviewData`  
`struct FMovieGraphImagePreviewData`  
_L62-85_
- reflection: `USTRUCT(BlueprintType)`
- L66 _public function_ `FMovieGraphImagePreviewData() : Texture(nullptr)`
- L72 _public member_ `TObjectPtr<class UTexture> Texture;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — The texture this preview image was rendered to.
- L76 _public member_ `FMovieGraphRenderDataIdentifier Identifier;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — The identifier for the image, containing the branch name, renderer, etc.
- L80 _public member_ `bool bMultipleCameraNames = false;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — If true, then there is more than one camera name being used (ie: multi-camera rendering)
- L84 _public member_ `TArray<FMovieGraphPreviewBannerMessage> BannerMessages;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — Optional banner messages contributed by the render pass that produced this tile.

#### struct `FMovieGraphInitConfig`  
`struct FMovieGraphInitConfig`  
_L88-123_
- reflection: `USTRUCT(BlueprintType)`
- L92 _public prototype_ `FMovieGraphInitConfig();`
- L99 _public member_ `TSubclassOf<UMovieGraphRendererBase> RendererClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Which class should the UMovieGraphPipeline use to look for render layers and request renders from. Defaults to UMovieGraphDefaultRenderer.
- L107 _public member_ `TSubclassOf<UMovieGraphDataSourceBase> DataSourceClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Which class should the UMovieGraphPipeline use to build time ranges from, and during evaluation, send callbacks about the time actually evaluated so you can sync with an external source. Defaults to UMovieGraphSequenceDataSource.
- L114 _public member_ `TSubclassOf<UMovieGraphAudioRendererBase> AudioRendererClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Which class should the UMovieGraphPipeline use to generate audio. Defaults to UMovieGraphDefaultAudioOutput.
- L122 _public member_ `bool bRenderViewport;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Should the UMovieGraphPipeline render the full player viewport? Defaults to false (so no 3d content is rendered) so we can display the UMG widgets and MRQ rendering always happens in an off-screen render target.

#### class `UMovieGraphTimeStepBase`  
`class UMovieGraphTimeStepBase : public UObject`  
_L126-153_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UObject`
- L131 _public function_ `virtual void TickProducingFrames()` — Called each frame while the Movie Graph Pipeline is in a producing frames state.
- L134 _public function_ `virtual void Initialize()` — Called when this time step instance becomes active (ie: at the start of a shot).
- L136 _public function_ `virtual void Shutdown()` — Called when this time step instance is no longer active (ie: at the end of a shot).
- L144 _public function_ `virtual FMovieGraphTimeStepData GetCalculatedTimeData() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — TickProducingFrames will be called for a frame (before the frame starts) and then this will be called at the end of the frame when we kick off the renders for the frame. Should return data needed to calculate the correct rendering timestep.
- L150 _public function_ `virtual bool IsExpansionForTSRequired(const TObjectPtr<UMovieGraphEvaluatedConfig>& InConfig) const` — When expanding shots, do we need to expand the first frame by one extra to account for how temporal sub-sampling can sample outside the first frame (due to centered frame evals).
- L152 _public prototype_ `UMovieGraphPipeline* GetOwningGraph() const;`

#### class `UMovieGraphEngineTimeStep`  
`class UMovieGraphEngineTimeStep : public UEngineCustomTimeStep`  
_L157-220_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineCustomTimeStep`
- L161 _public prototype_ `UMovieGraphEngineTimeStep();`
- L202 _public prototype_ `void SetCachedFrameTiming(const FTimeStepCache& InTimeCache);`
- L205 _public prototype_ `virtual bool Initialize(UEngine* InEngine) override;` — UEngineCustomTimeStep Interface
- L206 _public prototype_ `virtual void Shutdown(UEngine* InEngine) override;`
- L207 _public prototype_ `virtual bool UpdateTimeStep(UEngine* InEngine) override;`
- L208 _public function_ `virtual ECustomTimeStepSynchronizationState GetSynchronizationState() const override`
- L212 _public member_ `FTimeStepCache TimeCache;` — We don't do any thinking on our own, instead we just spit out the numbers stored in our time cache.
- L215 _public member_ `FSharedData SharedTimeStepData;` — Data that should be shared between all shot time step instances.
- L218 _public member_ `float PrevMinUndilatedFrameTime;` — Not cached in TimeCache as TimeCache is reset every frame.
- L219 _public member_ `float PrevMaxUndilatedFrameTime;`

#### struct `UMovieGraphEngineTimeStep::FTimeStepCache`  
`struct FTimeStepCache`  
_L163-174_
- L165 _public function_ `FTimeStepCache() : UndilatedDeltaTime(0.0)`
- L169 _public function_ `FTimeStepCache(double InUndilatedDeltaTime) : UndilatedDeltaTime(InUndilatedDeltaTime)`
- L173 _public member_ `double UndilatedDeltaTime;`

#### struct `UMovieGraphEngineTimeStep::FSharedData`  
`struct FSharedData`  
_L176-199_
- L178 _public function_ `FSharedData() : OutputFrameNumber(0) , RenderedFrameNumber(0) , bHasTimeDilationBeenUsed(false)`
- L186 _public member_ `int32 OutputFrameNumber;` — Which output frame are we working on, relative to zero.
- L192 _public member_ `int32 RenderedFrameNumber;` — Index of which frames we've submitted for rendering. Doesn't line up with OutputFrameNumber when using warm-up frames. Used internally by the rendering engine to keep track of which frames need to be read back.
- L198 _public member_ `bool bHasTimeDilationBeenUsed;` — If true, a frame rendered for this job used time dilation, and all subsequent frame numbers must be their relative versions to avoid any frame overwriting an already produced one.

#### struct `UE::MovieGraph::FMinimalCameraInfo`  
`struct FMinimalCameraInfo`  
_L229-237_
- desc: When fetching multiple cameras from the Data Source, we need to know both the rendering information (ViewInfo), but also who the renderering object is, which isn't stored in the ViewInfo.
- L231 _public function_ `FMinimalCameraInfo() : ViewActor(nullptr)`
- L235 _public member_ `TWeakObjectPtr<AActor> ViewActor;`
- L236 _public member_ `FMinimalViewInfo ViewInfo;`

#### class `UMovieGraphRendererBase`  
`class UMovieGraphRendererBase : public UObject`  
_L241-263_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UObject`
- L249 _public function_ `virtual TArray<FMovieGraphImagePreviewData> GetPreviewData() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Get an array of image previews that are valid this frame.
- L251 _public function_ `virtual void Render(const FMovieGraphTimeStepData& InTimeData)`
- L252 _public function_ `virtual void SetupRenderingPipelineForShot(UMoviePipelineExecutorShot* InShot)`
- L253 _public function_ `virtual void TeardownRenderingPipelineForShot(UMoviePipelineExecutorShot* InShot)`
- L254 _public function_ `virtual UE::MovieGraph::FRenderTimeStatistics* GetRenderTimeStatistics(const int32 InFrameNumber)`
- L257 _public function_ `virtual UE::MovieGraph::FMinimalCameraInfo GetMinimalCameraInfo(UMovieGraphEvaluatedConfig* InConfig, const int32 InCameraIndex) const` — `UE_DEPRECATED(5.5, "Use the version that doesn't take a config instead. The information from the config is now derived from the index value.")`
- L260 _public function_ `virtual UE::MovieGraph::FMinimalCameraInfo GetMinimalCameraInfo(const int32 InCameraIndex) const` — InCameraIndex can be -1 (for primary camera when not using multi-layer rendering) or 0...n for sidecar cameras.
- L262 _public prototype_ `UMovieGraphPipeline* GetOwningGraph() const;`

#### class `UMovieGraphDataSourceBase`  
`class UMovieGraphDataSourceBase : public UObject`  
_L274-321_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UObject`
- desc: Movie Graph Pipeline is mostly interested in knowing about ranges of time that it should render, and less concerned with the specifics of where that data comes from (ie: a Level Sequence). This lets you synchronize with a different data source to provide the ranges of time to render, and then the UMovieGraphTimeStepBase class figures out how to move around within that time step, before calling some functions to synchronize your external data source to actually match the evaluated time.
- L279 _public function_ `virtual FFrameRate GetTickResolution() const` — An internal, high resolution framerate that seeks, etc. will be returned in. (ie: 24,000/1)
- L282 _public function_ `virtual FFrameRate GetDisplayRate() const` — A lower res, human readable Frame Rate. We convert to the Tick Resolution internally. (ie: 24/1)
- L285 _public function_ `virtual void SyncDataSourceTime(const FFrameTime& InTime)` — Called by the Time Step system when it wants the external data source to update. Time is in TickResolution scale.
- L288 _public function_ `virtual void PlayDataSource()` — Called by the Time Step system when the external data source should start playback (time values will have been set by SyncDataSourceTime
- L291 _public function_ `virtual void PauseDataSource()` — Called by the Time Step system when the external data source should pause playback.
- L294 _public function_ `virtual void StopDataSource()` — Called by the Time Step system when the external data source should stop playback (typically at the end of rendering).
- L297 _public function_ `virtual void JumpDataSource(const FFrameTime& InTimeToJumpTo)` — Called by the Time Step system when the external data source should jump to the given time. Time is in TickResolution scale.
- L303 _public function_ `virtual void CacheDataPreJob(const FMovieGraphInitConfig& InInitConfig)` — Called when the Movie Graph Pipeline starts before anything has happened, allowing you to cache your datasource before making any modifications to it as a result of rendering.
- L304 _public function_ `virtual void RestoreCachedDataPostJob()`
- L305 _public function_ `virtual void UpdateShotList()`
- L306 _public function_ `virtual void InitializeShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot, const FFrameTime& InEvalTime)`
- L307 _public function_ `virtual void CacheHierarchyForShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot)`
- L308 _public function_ `virtual void RestoreHierarchyForShot(const TObjectPtr<UMoviePipelineExecutorShot> &InShot)`
- L309 _public function_ `virtual void MuteShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot)`
- L310 _public function_ `virtual void UnmuteShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot)`
- L311 _public function_ `virtual void ExpandShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot, const int32 InLeftDeltaFrames, const int32 InLeftDeltaFramesUserPoV, const int32 InRightDeltaFrames, const bool bInPrepass)`
- L318 _public function_ `virtual TArray<UE::MovieGraph::FMinimalCameraInfo> GetCameraInformation(UMoviePipelineExecutorShot* InShot, bool bIncludeSidecar) const` — Returns camera info for the given shot. When bIncludeSidecar is true, results must align with InShot->SidecarCameras: return one entry per sidecar camera, leaving unresolved sidecar camera entries defaulted.
- L320 _public prototype_ `UMovieGraphPipeline* GetOwningGraph() const;`

#### class `UMovieGraphAudioRendererBase`  
`class UMovieGraphAudioRendererBase : public UObject`  
_L325-353_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UObject`
- desc: Base class for generating audio while the pipeline is running.
- L331 _public function_ `virtual void StartAudioRecording()` — Tell our submixes to start capturing the data they are generating. Should only be called once output frames are being produced.
- L334 _public function_ `virtual void StopAudioRecording()` — Tell our submixes to stop capturing the data, and then store a copy of it.
- L337 _public function_ `virtual void ProcessAudioTick()` — Attempt to process the audio thread work. This is complicated by non-linear time steps.
- L340 _public function_ `virtual void SetupAudioRendering()` — Prepares for audio rendering (ensuring volume is set correctly, the needed cvars are set, etc).
- L343 _public function_ `virtual void TeardownAudioRendering() const` — Undoes the work done in SetupAudioRendering().
- L346 _public prototype_ `UMovieGraphPipeline* GetOwningGraph() const;` — Gets the pipeline that owns this audio output instance.
- L349 _public prototype_ `const MoviePipeline::FAudioState& GetAudioState() const;` — Gets the current state of the audio renderer. This is the main data source that audio-related nodes can reference.
- L352 _protected member_ `MoviePipeline::FAudioState AudioState;`

#### struct `FMovieGraphRenderPassLayerData`  
`struct FMovieGraphRenderPassLayerData`  
_L356-374_
- desc: ToDo: Both of these can probably go into the Default Renderer implementation.
- L358 _public member_ `FName BranchName;`
- L359 _public member_ `FString LayerName;`
- L360 _public member_ `int32 CameraIndex;`
- L361 _public member_ `FString CameraName;`
- L364 _public member_ `int32 LayerIndex = 0;` — The index of this layer in the list of layers being rendered (0 being the first layer)
- L367 _public member_ `uint32 NumCameras = 1;` — The number of cameras that are being rendered.
- L373 _public member_ `TWeakObjectPtr<class UMovieGraphRenderPassNode> RenderPassNode;` — The render pass node that's associated with this layer data. WARNING: this node will ONLY be valid during initial pass setup! Post-setup, if a non-CDO node is needed, it needs to be fetched from the evaluated config.

#### struct `FMovieGraphRenderPassSetupData`  
`struct FMovieGraphRenderPassSetupData`  
_L377-382_
- L379 _public member_ `TWeakObjectPtr<class UMovieGraphDefaultRenderer> Renderer;`
- L380 _public member_ `TArray<FMovieGraphRenderPassLayerData> Layers;`
- L381 _public member_ `TObjectPtr<UMovieGraphEvaluatedConfig> EvaluatedConfig;`

#### struct `UE::MovieGraph::FMovieGraphOutputFutureData`  
`struct FMovieGraphOutputFutureData`  
_L388-413_
- desc: Supplemental data to store with a file future so we can retrieve information about what the future was doing once it finishes writing to disk.
- L390 _public function_ `FMovieGraphOutputFutureData() : Shot(nullptr) , OriginNodeClass(nullptr) , RenderLayerIndex(0)`
- L397 _public member_ `class UMoviePipelineExecutorShot* Shot;` — Which shot is this for?
- L400 _public member_ `FString FilePath;` — What was the filepath on disk that was generated by the future?
- L403 _public member_ `FString FrameTemplatedFilePath;` — The "frame templated" filepath. This groups together a set of output frames by frame number, eg "Seq.Shot.{frame_placeholder}.exr".
- L406 _public member_ `FMovieGraphRenderDataIdentifier DataIdentifier;` — Which render pass is this for?
- L409 _public member_ `UClass* OriginNodeClass;` — The node class that this file originated from.
- L412 _public member_ `int32 RenderLayerIndex;` — The index of the render layer this future belongs to. Index 0 is the first render layer rendered, and so on.

#### struct `UE::MovieGraph::FRenderTimeStatistics`  
`struct FRenderTimeStatistics`  
_L424-431_
- desc: Statistics tracked for a given frame during rendering, such as when the render started and when it ended. This can be added as metadata during file output to include useful information. ToDo: This could potentially be tracked as just regular filemetadata with a rendered sample but requires strong typing support and metadata merging support.
- L427 _public member_ `FDateTime StartTime;` — Time in UTC that the frame was first started.
- L430 _public member_ `FDateTime EndTime;` — Time in UTC that the frame was fully rendered and merged together.

#### struct `UE::MovieGraph::FMovieGraphSampleState`  
`struct FMovieGraphSampleState : IImagePixelDataPayload, public TSharedFromThis<FMovieGraphSampleState>`  
_L433-583_
- inherits: `IImagePixelDataPayload,TSharedFromThis<FMovieGraphSampleState>`
- L435 _public function_ `FMovieGraphSampleState() : bWriteSampleToDisk(false) , bRequiresAccumulator(false) , bFetchFromAccumulator(false) , bCompositeOnOtherRenders(false) , bAllowsCompositing(true) , bIsBeautyPass(false) , OverscanFraction(0.f) , CompositingSortOrder(0) , RenderLayerIndex(0) , bAllowOCIO(true) , bForceLosslessCompression(false)`
- L449 _public function_ `virtual TSharedRef<FMovieGraphSampleState> Copy() const`
- L455 _public member_ `FMovieGraphTraversalContext TraversalContext;` — The traversal context used to read graph values at the time of submission.
- L458 _public member_ `FIntPoint OverscannedResolution;` — The desired output resolution scaled by any configured overscan
- L461 _public member_ `FIntPoint BackbufferResolution;` — The backbuffer resolution of this render resource (ie: the resolution the sample was rendered at). Includes overscan and tiling
- L464 _public member_ `FIntPoint UnpaddedTileSize;` — The size of a tile without padding (ie: OverscannedResolution/TileCount)
- L470 _public member_ `FIntPoint AccumulatorResolution;` — The resolution the accumulation buffer is accumulating at. This may be different than our backbuffer resolution (due to tiling), and our final output resolution (due to overscan + crop).
- L473 _public member_ `bool bWriteSampleToDisk;` — Debug feature, should this sample be written to disk, not being accumulated?
- L479 _public member_ `FString Debug_OverrideFilename;` — When bWriteSampleToDisk is true, if this string is specified then the single-sample debug writing will use this filename for the format token instead of the default one. Useful for render passes with complex output cases (like Panoramics) that need pass-specific names.
- L482 _public member_ `FString FilenameFormatOverride;` — Specifies the filename format that this sample should use when being written to disk. Not used for debug like Debug_OverrideFilename.
- L485 _public member_ `bool bRequiresAccumulator;` — Set this to true for every sample if an accumulator is required (ie: has temporal/spatial sub-samples, or high res tiling).
- L488 _public member_ `bool bFetchFromAccumulator;` — Set this to true for the last sample for a given frame (if it requires accumulation) to fetch the accumulated data out of the accumulator.
- L491 _public member_ `bool bCompositeOnOtherRenders;` — Set this to true if this pass should be composited on top of other renders.
- L494 _public member_ `bool bAllowsCompositing;` — Set this to false if this pass should not allow other passes to be composited onto it.
- L497 _public member_ `bool bIsBeautyPass;` — Whether this sample represents a sample in the main beauty pass.
- L503 _public member_ `bool bForceOpaqueAlpha = false;` — When true, forces alpha to 1.0 in the output. Typically used for Post Process Material passes that don't explicitly output alpha, where the render target's clear color (alpha=0) would otherwise leak through.
- L506 _public member_ `FIntPoint OverlappedPad;` — When using high-res tiling, how many pixels does each tile overlap the adjacent tiles (on each side)? This should be zero if not using tiling.
- L509 _public member_ `FIntPoint OverlappedOffset;` — When using high-res tiling, how many pixels offset into the output image does this accumulation get added to.
- L512 _public member_ `FVector2D OverlappedSubpixelShift;` — When using spatial jitters, how much do we need to shift the output data during accumulation to counter-act the jitter.
- L515 _public member_ `float OverscanFraction;` — When using camera overscan, what fraction (0-1) did this render use? Needed so that exrs can take a center-out crop of the data.
- L522 _public member_ `FIntRect CropRectangle;` — The rectangle to use to crop the image prior to compositing and output. Used to crop out overscan from appropriate formats, and will generally have size equal to the originally requested resolution, whereas internal resolutions such as Backbuffer and Accumulator resolutions will be scaled up to include overscan
- L528 _public member_ `int32 CompositingSortOrder;` — If multiple passes are composited on top of a render, the sort order determines the order in which they're composited. Passes with a low sort order will composite on top of passes with a higher sort order.
- L531 _public member_ `int32 RenderLayerIndex;` — The index of the render layer this sample belongs to. Index 0 is the first render layer rendered, and so on.
- L534 _public member_ `bool bAllowOCIO;` — Allow OpenColorIO transform to be used on this render.
- L537 _public member_ `bool bForceLosslessCompression;` — Whether this sample must use lossless compression when written to a format that supports it.
- L540 _public member_ `ESceneCaptureSource SceneCaptureSource;` — Render scene capture source used for tracking the output color space (without OpenColorIO).
- L546 _public member_ `TMap<FString, FString> AdditionalFileMetadata;` — Additional metadata that should be added to the output. In most cases, the node's GetFormatResolveArgs() should be used to provide metadata unless the metadata is generated at a point in the pipeline where GetFormatResolveArgs() cannot be used.
- L552 _public member_ `TMap<FString, FString> AdditionalFormatArgs;` — Additional key/value pairs for filename format token substitution. Keys are token names without braces (e.g. "camera_name"). Use this when token values are only known at render time and GetFormatResolveArgs() cannot be used at that point.
- L569 _public member_ `TArray<FString> CameraNameTokenOverrides;` — By default, MRG injects a {camera_name} token before {frame_number} when rendering multiple cameras (if one is not already present in the filename format string). If set, and {camera_name} is not already in the filename format string, these tokens are always injected instead of {camera_name}, even when only one camera is active. Tokens already present in the format string are skipped. If set, forces multi-camera code paths even when only one camera is active. Does not cause additional cameras to render. Example with CameraNameTokenOverrides = {t_1}, {t_2}: {layer_name}.{frame_number} -> {layer_name}.{t_1},{t_2}.{frame_number} {t_2}.{layer_name}.{frame_number} -> {t_2}.{layer_name}.{t_1}.{frame_number}  ({t_2} already present, skipped)
- L576 _public member_ `FString LayerNameOverride;` — For multi-layer output formats, setting this allows the layer name to be explicitly specified. Normally the layer name will be procedurally generated from multiple data sources to avoid collision with other layer names, but there are scenarios where specifying an exact layer name may be needed.
- L582 _public member_ `TArray<FSoftClassPath> OutputTypeRestrictions;` — Specifies the output node class(es) that can output this sample. If this array is empty, this sample will be processed by all output nodes (which is typical).

#### struct `UE::MovieGraph::FMovieGraphRenderDataValidationInfo`  
`struct FMovieGraphRenderDataValidationInfo`  
_L588-595_
- desc: A collection of validation information extracted from the FMovieGraphOutputMergerFrame
- L590 _public member_ `int32 LayerCount = 0;`
- L591 _public member_ `int32 BranchCount = 0;`
- L592 _public member_ `int32 ActiveBranchRendererCount = 0;`
- L593 _public member_ `int32 ActiveRendererSubresourceCount = 0;`
- L594 _public member_ `int32 ActiveCameraCount = 0;`

#### struct `UE::MovieGraph::FMovieGraphOutputMergerFrame`  
`struct FMovieGraphOutputMergerFrame`  
_L603-638_
- desc: A collection of all of the data needed to produce the one output frame on disk. This holds all of the pixel data associated with the output frame at once, so we can pass it to our image writing/video encoders in one go, to ensure we can do things like Multilayer EXRs which embed all of the render passes inside of one file.
- L605 _public prototype_ `FMovieGraphOutputMergerFrame() = default;`
- L611 _public member_ `TStrongObjectPtr<UMovieGraphEvaluatedConfig> EvaluatedConfig;` — The configuraton file that was being used by this frame during submission. We store it here so that it doesn't have to go through the pipeline (which is difficult becuase it's a Garbage Collected object), and the Output Merger is the "join" step before we go back onto the Game Thread.
- L616 _public member_ `FMovieGraphTraversalContext TraversalContext;` — Traversal context for the Movie Pipeline that isn't layer specific. Each image layer will have its own traversal context within its payload, specific to itself.
- L622 _public member_ `TArray<FMovieGraphRenderDataIdentifier> ExpectedRenderPasses;` — An array of expected data identifiers this frame. This is generated when the frame starts, and this frame won't be complete until ImageOutputData contains an image for each expected pass.
- L625 _public member_ `TMap<FMovieGraphRenderDataIdentifier, TUniquePtr<FImagePixelData>> ImageOutputData;` — Stores the actual pixel data for each render pass.
- L628 _public member_ `TMap<FString, FString> FileMetadata;` — Additional metadata to be added to the output (if supported by the output container).
- L634 _public member_ `TMap<const UMovieGraphFileOutputNode*, TArray<UE::MovieGraph::FMovieGraphSampleState*>> NodeInstanceToPayloads;` — Specifies which payloads will be written from a specific output node instance. NOTE: This is only updated immediately prior to filename disambiguation and should not be used outside of that.
- L637 _public prototype_ `FMovieGraphRenderDataValidationInfo GetValidationInfo(const FMovieGraphRenderDataIdentifier& InRenderID, bool bInDiscardCompositedRenders = true) const;` — Get filename token validation info from the (expected) render passes.

#### struct `UE::MovieGraph::IMovieGraphOutputMerger`  
`struct IMovieGraphOutputMerger : public TSharedFromThis<IMovieGraphOutputMerger>`  
_L644-668_
- inherits: `TSharedFromThis<IMovieGraphOutputMerger>`
- desc: Interface for the intermediate threadsafe class that allocates new frames, holds onto the individual pieces as they come in, and eventually moves it back to the game thread once the data is complete.
- L646 _public prototype_ `virtual ~IMovieGraphOutputMerger() = default;`
- L649 _public prototype_ `virtual FMovieGraphOutputMergerFrame& AllocateNewOutputFrame_GameThread(const int32 InRenderedFrameNumber) = 0;` — Call once per output frame to generate a struct to hold data.
- L652 _public prototype_ `virtual FMovieGraphOutputMergerFrame& GetOutputFrame_GameThread(const int32 InRenderedFrameNumber) = 0;` — Getter for the Output Frame. Make sure you call AllocateNewOutputFrame_GameThread first, otherwise this trips a check.
- L655 _public prototype_ `virtual void OnCompleteRenderPassDataAvailable_AnyThread(TUniquePtr<FImagePixelData>&& InData) = 0;` — When a final accumulated render pass is available, call this function with the pixel data.
- L658 _public prototype_ `virtual void OnSingleSampleDataAvailable_AnyThread(TUniquePtr<FImagePixelData>&& InData) = 0;` — When a individual sample is read back from the GPU, call this function. Debug Feature, immediately writes to disk.
- L661 _public prototype_ `virtual void AbandonOutstandingWork() = 0;` — Abandon any frames we're waiting on, ie; render stopped in the middle of a many temporal sample count frame.
- L664 _public prototype_ `virtual int32 GetNumOutstandingFrames() const = 0;` — Number of frames that have been started (via AllocateNewOutputFrame_GameThread) but haven't had all of their data come in yet via OnCompleteRenderPassDataAvailable_AnyThread.
- L667 _public prototype_ `virtual TQueue<FMovieGraphOutputMergerFrame>& GetFinishedFrames() = 0;` — Get a thread-safe FIFO queue of finished frame data.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace MovieGraph` (scope `UE`)
- L38 _typedef_ `typedef TPair<FMovieGraphRenderDataIdentifier, TUniquePtr<FImagePixelData>> FMovieGraphPassData;` — Convenience type for passing around pass data plus its identifier.
- L222 _namespace_ `namespace UE`
- L222 _namespace_ `namespace MovieGraph` (scope `UE`)
- L385 _namespace_ `namespace UE`
- L385 _namespace_ `namespace MovieGraph` (scope `UE`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphDefaultAudioRenderer.h` (Public)


#### class `UMovieGraphDefaultAudioRenderer`  
`class UMovieGraphDefaultAudioRenderer : public UMovieGraphAudioRendererBase`  
_L15-30_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "Default Audio Renderer"))`
- inherits: `UMovieGraphAudioRendererBase`
- desc: Provides default audio rendering for the pipeline.
- L20 _public prototype_ `UMovieGraphDefaultAudioRenderer() = default;`
- L24 _protected prototype_ `virtual void StartAudioRecording() override;` — UMovieGraphAudioOutputBase interface
- L25 _protected prototype_ `virtual void StopAudioRecording() override;`
- L26 _protected prototype_ `virtual void ProcessAudioTick() override;`
- L27 _protected prototype_ `virtual void SetupAudioRendering() override;`
- L28 _protected prototype_ `virtual void TeardownAudioRendering() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphDefaultRenderer.h` (Public)


#### struct `UE::MovieGraph::DefaultRenderer::FMovieGraphTilingParams`  
`struct FMovieGraphTilingParams`  
_L30-43_
- L33 _public member_ `FVector2f OverlapPad = FVector2f::ZeroVector;` — The number of pixels that the tiles overlap each other.
- L36 _public member_ `FIntPoint TileSize = FIntPoint(0, 0);` — The size of the backbuffer in pixels.
- L39 _public member_ `FIntPoint TileIndexes = FIntPoint(0, 0);` — The index of this tile.
- L42 _public member_ `FIntPoint TileCount = FIntPoint(1, 1);` — The number of tiles there are in total.

#### struct `UE::MovieGraph::DefaultRenderer::FMovieGraphSamplingParams`  
`struct FMovieGraphSamplingParams`  
_L45-52_
- L47 _public member_ `int32 TemporalSampleIndex = 0;`
- L48 _public member_ `int32 TemporalSampleCount = 1;`
- L49 _public member_ `int32 SpatialSampleIndex = 0;`
- L50 _public member_ `int32 SpatialSampleCount = 1;`
- L51 _public member_ `int32 SeedOffset = 0;`

#### struct `UE::MovieGraph::DefaultRenderer::FCameraInfo`  
`struct FCameraInfo`  
_L54-89_
- L56 _public function_ `FCameraInfo() : ViewActor(nullptr) , bAllowCameraAspectRatio(true) , DoFSensorScale(1.0f) , bUseCameraManagerPostProcess(true)`
- L64 _public member_ `FMinimalViewInfo ViewInfo;` — Minimal view info describing the position and orientation in the world.
- L67 _public member_ `class AActor* ViewActor;` — The actor that is considered the "owner" of the view. Used by the renderer to respect bOnlyOwnerSee/bOwnerNoSee flags.
- L70 _public member_ `FString CameraName;` — The name to use for the {camera_name} token. Filled out by the renderer where possible.
- L73 _public member_ `bool bAllowCameraAspectRatio;` — should we respect the camera's aspect ratio settings.
- L77 _public member_ `float DoFSensorScale;` — When using tiling, we scale the sensor to counteract the view changes. This value comes from modifying the ProjectionMatrix.
- L79 _public member_ `FMovieGraphTilingParams TilingParams;`
- L80 _public member_ `FMovieGraphSamplingParams SamplingParams;`
- L83 _public member_ `FVector2D ProjectionMatrixJitterAmount;` — Sub-pixel jitter this camera should use. Only applied when using no AA.
- L87 _public member_ `bool bUseCameraManagerPostProcess;` — If true, we use the Post Process data from the Camera Manager, instead of deriving it from the camera location. This should be false when rendering multiple cameras.

#### struct `UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams`  
`struct FRenderTargetInitParams`  
_L91-132_
- L93 _public function_ `FRenderTargetInitParams() : Size(FIntPoint(0, 0)) , TargetGamma(0.f) , bForceLinearGamma(false) , PixelFormat(EPixelFormat::PF_Unknown) , bIncludeInPreviewWindow(true)`
- L102 _public member_ `FIntPoint Size;`
- L103 _public member_ `float TargetGamma;`
- L104 _public member_ `bool bForceLinearGamma;`
- L105 _public member_ `EPixelFormat PixelFormat;`
- L108 _public member_ `bool bIncludeInPreviewWindow;` — Whether this render target is shown in the "preview" window that displays during a render.
- L110 _public function_ `bool operator == (const FRenderTargetInitParams& InRHS) const`
- L119 _public function_ `bool operator != (const FRenderTargetInitParams& InRHS) const`

#### struct `UE::MovieGraph::DefaultRenderer::FMovieGraphImagePreviewDataPoolParams`  
`struct FMovieGraphImagePreviewDataPoolParams`  
_L134-155_
- L137 _public member_ `FRenderTargetInitParams RenderInitParams;` — The size of the render target, and the depth requested.
- L139 _public member_ `FMovieGraphRenderDataIdentifier Identifier;` — Identifier for which render resource this is used by.
- L141 _public function_ `bool operator == (const FMovieGraphImagePreviewDataPoolParams& InRHS) const`
- L146 _public function_ `bool operator != (const FMovieGraphImagePreviewDataPoolParams& InRHS) const`

#### struct `UE::MovieGraph::DefaultRenderer::FMovieGraphImagePreviewPoolState`  
`struct FMovieGraphImagePreviewPoolState`  
_L158-180_
- desc: State object to keep track of the state of image render targets in the image render target pool
- L160 _public function_ `FMovieGraphImagePreviewPoolState()`
- L166 _public member_ `uint64 LastUsedFrame;` — The last frame that the render target was used
- L169 _public function_ `void UpdateLastUsedFrame()` — Updates the last used frame to the current frame counter
- L175 _public function_ `bool IsStale() const` — Compares the last used frame to the current frame counter and returns true of the difference is larger than the specified threshold

#### struct `UE::MovieGraph::DefaultRenderer::FSurfaceAccumulatorPool`  
`struct FSurfaceAccumulatorPool : public TSharedFromThis<FSurfaceAccumulatorPool>`  
_L182-261_
- inherits: `TSharedFromThis<FSurfaceAccumulatorPool>`
- L210 _public typedef_ `typedef TSharedPtr<FInstance, ESPMode::ThreadSafe> FInstancePtr;`
- L212 _public member_ `TArray<TSharedPtr<FInstance, ESPMode::ThreadSafe>> Accumulators;`
- L213 _public member_ `FCriticalSection CriticalSection;`
- L216 _public function_ `template <typename AccumulatorType> FSurfaceAccumulatorPool::FInstancePtr GetAccumulatorInstance_GameThread(int32 InFrameNumber, const FMovieGraphRenderDataIdentifier& InPassIdentifier)`

#### struct `UE::MovieGraph::DefaultRenderer::FSurfaceAccumulatorPool::FInstance`  
`struct FInstance`  
_L184-208_
- L186 _public function_ `FInstance(TSharedPtr<MoviePipelineOverlappedAccumulatorInterface, ESPMode::ThreadSafe> InAccumulator)`
- L192 _public function_ `bool IsActive() const`
- L195 _public function_ `void SetIsActive(const bool bInIsActive)` — Changing the active state resets the internal state, so set it to active before configuring.
- L202 _public member_ `TSharedPtr<MoviePipelineOverlappedAccumulatorInterface, ESPMode::ThreadSafe> Accumulator;`
- L203 _public member_ `int32 ActiveFrameNumber;`
- L204 _public member_ `FMovieGraphRenderDataIdentifier ActivePassIdentifier;`
- L205 _public member_ `UE::Tasks::FTask TaskPrereq;`
- L207 _private member_ `FThreadSafeBool bIsActive;`

#### class `UE::MovieGraph::DefaultRenderer::FMovieGraphAccumulationTask`  
`class FMovieGraphAccumulationTask`  
_L263-287_
- L266 _public member_ `FGraphEventRef LastCompletionEvent;`
- L267 _public member_ `UE::Tasks::FTask TaskPrereq;`
- L270 _public function_ `FGraphEventRef Execute(TUniqueFunction<void()> InFunctor)`
- L283 _public function_ `inline TStatId GetStatId() const`

#### class `UMovieGraphDefaultRenderer`  
`class UMovieGraphDefaultRenderer : public UMovieGraphRendererBase`  
_L304-439_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphRendererBase`
- desc: This class is the default implementation for the Movie Graph Pipeline renderer. This is split off into a separate class to minimize the complexity of the core UMovieGraphPipeline, and to provide a better way to store render-specific data during runtime. It is responsible for taking all of the render passes and rendering them, and then moving their rendered data back to the main UMoviePipeline OutputMerger once finished. It is unlikely you will want to implement your own renderer. If you need to create new render passes, inherit from UMovieGraphRenderPassNode and add it to your configuration, at which point MRQ will call function on the CDO of it that allow you to set up your own render data.
- L310 _public prototype_ `virtual TArray<FMovieGraphImagePreviewData> GetPreviewData() const override;` — UMovieGraphRendererBase Interface
- L311 _public prototype_ `virtual void Render(const FMovieGraphTimeStepData& InTimeData) override;`
- L312 _public prototype_ `virtual void SetupRenderingPipelineForShot(UMoviePipelineExecutorShot* InShot) override;`
- L313 _public prototype_ `virtual void TeardownRenderingPipelineForShot(UMoviePipelineExecutorShot* InShot) override;`
- L314 _public prototype_ `virtual UE::MovieGraph::FRenderTimeStatistics* GetRenderTimeStatistics(const int32 InFrameNumber);`
- L318 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);` — UObject Interface
- L321 _public prototype_ `void AddOutstandingRenderTask_AnyThread(UE::Tasks::FTask InTask);`
- L332 _public prototype_ `UE::MovieGraph::DefaultRenderer::FCameraInfo GetCameraInfo(const int32 InCameraIndex, const FMovieGraphRenderCameraSource* InCameraSource = nullptr) const;` — Fetches information for the given camera index. First, if InCameraSource is provided with a non-negative camera index, its information is used. Otherwise, it is resolved against default sequence camera or the shot's sidecar camera data. @param InCameraIndex  Pass INDEX_NONE when using default sequence camera. Pass [0..N) for multi-camera rendering (shot's sidecar or custom source). @param InCameraSource Optional camera source. If provided but the camera index cannot be resolved, falls back to the default sequence camera.
- L333 _public function_ `void SetHasRenderedFirstViewThisFrame(bool bInValue)`
- L334 _public function_ `bool GetHasRenderedFirstViewThisFrame() const`
- L343 _public prototype_ `float GetCameraOverscan(int32 InCameraIndex, const FMovieGraphRenderCameraSource* InCameraSource = nullptr);` — Gets the overscan value for the specified camera. @param InCameraIndex  Pass INDEX_NONE when using default sequence camera. Pass [0..N) for multi-camera rendering (shot's sidecar or custom source). @param InCameraSource Optional camera source. If provided but the camera index cannot be resolved, falls back to the default sequence camera.
- L347 _public prototype_ `void WarnAboutAnimatedOverscan(float InInitialOverscan);` — `UE_DEPRECATED(5.6, "WarnAboutAnimatedOverscan is no longer used; animated overscan is supported in 5.6")` — Outputs a warning message regarding animated overscan to the MRQ log if one has not already been output
- L350 _public prototype_ `UTextureRenderTarget2D* GetOrCreateViewRenderTarget(const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InInitParams, const FMovieGraphRenderDataIdentifier& InIdentifier);`
- L351 _public prototype_ `FMoviePipelineSurfaceQueuePtr GetOrCreateSurfaceQueue(const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InInitParams);`
- L354 _public function_ `template <typename AccumulatorType> FMoviePipelineAccumulatorPoolPtr GetOrCreateAccumulatorPool()`
- L370 _public prototype_ `void UpdateRenderPassTelemetry(FMoviePipelineEndShotRenderTelemetryContext& InOutTelemetry) const;` — Updates telemetry as needed. Generally should only be called by the pipeline.
- L373 _protected prototype_ `TObjectPtr<UTextureRenderTarget2D> CreateViewRenderTarget(const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InInitParams) const;`
- L374 _protected prototype_ `FMoviePipelineSurfaceQueuePtr CreateSurfaceQueue(const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InInitParams) const;`
- L380 _protected prototype_ `void GetCameraLocationsForFrame(TArray<FVector>& OutLocations, UMoviePipelineExecutorShot* InShot, bool bIncludeSidecar = false) const;` — Gets the camera locations for the current frame to inform the grass system of where streaming is required. If bIncludeSidecar is false, only the primary camera location is considered, otherwise it'll provide all the camera locations for multi-camera streaming (which can increase resource requirements).
- L381 _protected prototype_ `void FlushAsyncEngineSystems(const TObjectPtr<UMovieGraphEvaluatedConfig>& InConfig) const;`
- L384 _protected prototype_ `UE::MovieGraph::DefaultRenderer::FCameraInfo GetCameraInfoImpl(const int32 InCameraIndex) const;` — Fetches information for the given camera index. Should be "-1" when not using multi-camera rendering, or [0, n] based on the shot's sidecar camera data when using multi-camera rendering.
- L389 _protected prototype_ `float GetCameraOverscanImpl(int32 InCameraIndex);` — Gets the overscan value for the specified camera. First checks to see if any cached overscan value exists and returning it, and if no cached value was found, gets the camera's live overscan value and caches it.
- L394 _protected member_ `TArray<TObjectPtr<UMovieGraphRenderPassNode>> RenderPassesInUse;` — `UPROPERTY(Transient)` — A pointer to the CDOs of the Render Pass nodes that are valid for the current shot render.
- L397 _protected member_ `FMoviePipelineEndShotRenderTelemetryContext CachedRenderPassTelemetry;` — Telemetry gathered from live render pass instances before they are torn down.
- L400 _protected member_ `bool bHasRenderedFirstViewThisFrame = false;` — For this engine tick, has any view been submitted yet?
- L403 _protected member_ `TMap<int32, UE::MovieGraph::FRenderTimeStatistics> RenderTimeStatistics;` — Keep track of some statistics about render frame data for metadata purposes.
- L410 _protected member_ `TMap<UE::MovieGraph::DefaultRenderer::FMovieGraphImagePreviewDataPoolParams, TObjectPtr<UTextureRenderTarget2D>> PooledViewRenderTargets;` — Render Target specify a transient backbuffer to draw the image to.We reuse these because we queue a copy onto a FMoviePipelineSurface so the only reason it is needed is for display in the UI.
- L413 _protected member_ `TMap<UE::MovieGraph::DefaultRenderer::FMovieGraphImagePreviewDataPoolParams, UE::MovieGraph::DefaultRenderer::FMovieGraphImagePreviewPoolState> PooledViewRenderTargetStates;` — States for the render targets stored in PooledViewRenderTargets
- L420 _protected member_ `TMap<UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams, FMoviePipelineSurfaceQueuePtr> PooledSurfaceQueues;` — This is a list of Surfaces that we can copy our render target to immediately after it is drawn to. This is read back to the CPU a frame later (to avoid blocking the GPU), and it's contents are then copied into a FImagePixelData.
- L427 _protected member_ `TMap<FName, TSharedPtr<UE::MovieGraph::DefaultRenderer::FSurfaceAccumulatorPool>> PooledAccumulators;` — Once a sample is copied back from the GPU, we need to potentially accumulate it over multiple frames, and to apply high-res tiling. To do this we have a pool of accumulators, where each unique render resource gets one per frame.
- L430 _protected member_ `FCriticalSection OutstandingTasksMutex;` — Accessed by the Render Thread when starting up a new task.Makes sure we don't add tasks to the array while we're removing finished ones.
- L432 _protected member_ `TArray<UE::Tasks::FTask> OutstandingTasks;` — Array of outstanding accumulation / blending tasks that are currently being worked on.
- L435 _protected member_ `TMap<int32, float> CameraOverscanCache;` — Caches the camera overscan used during setup to ensure that overscan-scaled resolution stays constant for every frame during a render
- L438 _protected member_ `bool bHasWarnedAboutAnimatedOverscan = false;` — Indicates if the user has already been warned about animate overscan if it is detected so that logs aren't flooded with warning messages

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L21 _namespace_ `namespace MoviePipeline`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MovieGraph` (scope `UE`)
- L22 _namespace_ `namespace DefaultRenderer` (scope `UE::MovieGraph`)
- L24 _typedef_ `typedef TSharedPtr<FMoviePipelineSurfaceQueue, ESPMode::ThreadSafe> FMoviePipelineSurfaceQueuePtr;`
- L25 _typedef_ `typedef MoviePipeline::IMoviePipelineOverlappedAccumulator MoviePipelineOverlappedAccumulatorInterface;`
- L26 _typedef_ `typedef TSharedPtr<UE::MovieGraph::DefaultRenderer::FSurfaceAccumulatorPool, ESPMode::ThreadSafe> FMoviePipelineAccumulatorPoolPtr;`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace MovieGraph` (scope `UE`)
- L28 _namespace_ `namespace DefaultRenderer` (scope `UE::MovieGraph`)
- L124 _function_ `friend uint32 GetTypeHash(FRenderTargetInitParams Params)` (scope `UE::MovieGraph::DefaultRenderer`)
- L151 _function_ `friend uint32 GetTypeHash(FMovieGraphImagePreviewDataPoolParams Params)` (scope `UE::MovieGraph::DefaultRenderer`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphEdge.h` (Public)


#### class `UMovieGraphEdge`  
`class UMovieGraphEdge : public UObject`  
_L14-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L20 _public member_ `TObjectPtr<UMovieGraphPin> InputPin;` — `UPROPERTY()`
- L23 _public member_ `TObjectPtr<UMovieGraphPin> OutputPin;` — `UPROPERTY()`
- L26 _public prototype_ `bool IsValid() const;` — Whether the edge is valid or not. Being valid means it contains a non-null input and output pin.
- L32 _public prototype_ `UMovieGraphPin* GetOtherPin(const UMovieGraphPin* InFirstPin, const bool bFollowRerouteConnections = false);` — Gets the pin on the other side of the edge. If bFollowRerouteConnections is true, reroute nodes will be passthrough, and this method will continue traversing edges until a pin on a non-reroute node is found.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphFilenameResolveParams.h` (Public)


#### struct `FMovieGraphResolveArgs`  
`struct FMovieGraphResolveArgs`  
_L28-41_
- reflection: `USTRUCT(BlueprintType)`
- desc: This data structure contains a list of key-value pairs (as strings) for both filename resolving, and file metadata. They are stored as two separate arrays (as metadata is often a bit more verbose/human friendly) and it is not required that the two arrays be in sync. When resolving final filenames, any {tokens} will be replaced with a matching key-value if found in the FilenameArguments variable. Because of this, FilenameArguments should be short and avoid illegal filename chars.
- L32 _public prototype_ `FMovieGraphResolveArgs() = default;`
- L36 _public member_ `TMap<FString, FString> FilenameArguments;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — A set of Key/Value pairs for output filename format strings (without {}) and their values.
- L40 _public member_ `TMap<FString, FString> FileMetadata;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — A set of Key/Value pairs for file metadata for file formats that support metadata.

#### struct `FMovieGraphFilenameResolveParams`  
`struct FMovieGraphFilenameResolveParams`  
_L52-182_
- reflection: `USTRUCT(BlueprintType)`
- desc: This data structure contains all of the information needed to resolve a filename format string from the Movie Graph. During runtime the values are generated by the actual rendering and then placed into this data structure before resolving an actual {format_string} using the UMovieGraphBlueprintLibrary. You can use this to resolve filenames when editing. If you wish to resolve a partial format string (such as {sequence_name}/{frame_number} but have it only resolve {sequence_name} you can add ("frame_number", "{frame_number}") to the FileNameFormatOverrides and that portion of the format string will be preserved so the resulting string back would say "my_seq_name/{frame_number}".
- L56 _public function_ `FMovieGraphFilenameResolveParams() : RootFrameNumber(0) , ShotFrameNumber(0) , RootFrameNumberRel(0) , ShotFrameNumberRel(0) , Version(0) , bForceRelativeFrameNumbers(false) , bEnsureAbsolutePath(true) , InitializationTime(0) , ZeroPadFrameNumberCount(0) , Job(nullptr) , Shot(nullptr) , EvaluatedConfig(nullptr) , FrameNumberOffset(0) , DefaultFrameRate(FFrameRate(24, 1))`
- L75 _public prototype_ `static FMovieGraphFilenameResolveParams MakeResolveParams( const FMovieGraphRenderDataIdentifier& InRenderId, const UMovieGraphPipeline* InPipeline, const TObjectPtr<UMovieGraphEvaluatedConfig>& InEvaluatedConfig, const FMovieGraphTraversalContext& InTraversalContext, const TMap<FString, FString>& InAdditionalFormatArgs = {}, const UE::MovieGraph::FMovieGraphSampleState* InSamplePayload = nullptr);` — Convenience function to make filename resolve parameters for output files, or OCIO contexts.
- L88 _public member_ `FMovieGraphRenderDataIdentifier RenderDataIdentifier;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — This is used to fill out tokens related to the render data that the file represents. Used to fill out the {camera_name}, {layer_name}, {renderer_name}, {renderer_sub_name} tokens.
- L95 _public member_ `int32 RootFrameNumber;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Frame Number for the Root (matching what you see in the Sequencer timeline. ie: If the Sequence PlaybackRange starts on 50, this value would be 50 on the first frame.) Used to fill out the {frame_number} token.
- L102 _public member_ `int32 ShotFrameNumber;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Frame Number for the Shot (matching what you would see in Sequencer at the sub-sequence level.) Used to fill out the {frame_number_shot} token.
- L109 _public member_ `int32 RootFrameNumberRel;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Frame Number for the Root (relative to the first RootFrameNumber for this render, ie: if your sequence started at 35, this would be 35 as well, but supports time dilation because it will count up based on the total number of frame rendered, not the closest Sequencer frame (like RootFrameNumber)) Used to fill out the {frame_number_rel} token.
- L116 _public member_ `int32 ShotFrameNumberRel;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Frame Number for the Shot (relative to the first ShotFrameNumber for this shot, ie: if your shot started at 35, this would be 35 as well, but supports time dilation because it will count up based on the total number of frame rendered, not the closest Sequencer frame (like ShotFrameNumber)) Used to fill out the {frame_number_shot_rel} token.
- L120 _public member_ `TMap<FString, FString> FileMetadata;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — A key/value pair that maps metadata names to their values. Output is only supported in exr formats at the moment.
- L124 _public member_ `int32 Version;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Used to resolve {version} format arguments.
- L128 _public member_ `bool bForceRelativeFrameNumbers;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — If true, force format strings (like {frame_number}) to resolve using the relative version. Used when slow-mo is detected as frame numbers would overlap.
- L132 _public member_ `FString FileNameOverride;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — If specified, this is the filename that will be used instead of building it from the Output Setting node.
- L139 _public member_ `bool bEnsureAbsolutePath;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — If true, If the format string is a relative path, then the resulting resolved path will be converted to an absolute path. Assumes that the relative path should be resolved relative to the engine/editor executable.
- L146 _public member_ `FDateTime InitializationTime;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — The initialization time for this job. Used to resolve time-based format arguments. This should be in UTC, if you want filenames in a local timezone then you should set InitializationTimeOffset to your offset from UTC.
- L150 _public member_ `FTimespan InitializationTimeOffset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — What offset should be applied to InitializationTime when generating {time} related filename tokens? Likely your offset from UTC if you want local time.
- L154 _public member_ `int32 ZeroPadFrameNumberCount;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — When converting frame numbers to strings, how many digits should we pad them up to? ie: 5 => 0005 with a count of 4.
- L161 _public member_ `TMap<FString, FString> FileNameFormatOverrides;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — A map between "{format}" tokens and their values. These are applied after the auto-generated ones from the system, which allows the caller to override things like {.ext}
- L165 _public member_ `TObjectPtr<UMoviePipelineExecutorJob> Job;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Optional. If specified, used to resolve some tokens related to the job.
- L169 _public member_ `TObjectPtr<UMoviePipelineExecutorShot> Shot;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Optional. If specified, used to resolve the shot name. No settings from this shot are ever used (they must come form the EvaluatedConfig instead).
- L173 _public member_ `TObjectPtr<UMovieGraphEvaluatedConfig> EvaluatedConfig;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Optional. If specified, used to resolve some tokens related to settings in the shot (such as {ts_count}).
- L177 _public member_ `int32 FrameNumberOffset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Added onto the various FrameNumber settings automatically. Can be used to offset values (such as starting your Level Sequence on frame 0, but outputting it to disk at 1001).
- L181 _public member_ `FFrameRate DefaultFrameRate;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — What is the default Frame Rate? This will be overwritten by the Output Setting from the evaluated config (if specified).

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MovieGraph` (scope `UE`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphLinearTimeStep.h` (Public)


#### class `UMovieGraphLinearTimeStep`  
`class UMovieGraphLinearTimeStep : public UMovieGraphCoreTimeStep`  
_L17-27_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "Linear Time Step"))`
- inherits: `UMovieGraphCoreTimeStep`
- desc: Advances time forward linearly until the end of the range of time that is being rendered is reached. This is useful for deferred rendering (where there's a small number of temporal sub-samples and no feedback mechanism for measuring noise in the final image).
- L22 _public prototype_ `UMovieGraphLinearTimeStep() = default;`
- L25 _protected prototype_ `virtual int32 GetNextTemporalRangeIndex() const override;`
- L26 _protected prototype_ `virtual int32 GetTemporalSampleCount() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphMultiValueContainer.h` (Public)


#### class `UMovieGraphMultiValueContainer`  
`class UMovieGraphMultiValueContainer final : public UObject`  
_L22-254_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Holds generic values, with an API for getting/setting values, as well as getting/setting the value types and value container types (eg, array). For a container that holds a single value, see UMovieGraphValueContainer.
- L27 _public prototype_ `UMovieGraphMultiValueContainer();`
- L34 _public prototype_ `bool AddProperty(const FName& InPropertyName, const EMovieGraphValueType ValueType, UObject* InValueTypeObject, const TMap<FName, FString>& InMetadata);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Adds a new property to the container. If a property by the given name already exists, no add operation will occur. Returns true on successful add, otherwise returns false.
- L38 _public prototype_ `bool RemoveProperty(const FName& InPropertyName);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Removes a property by the given name. Returns true on successful remove, otherwise returns false.
- L42 _public prototype_ `bool HasProperty(const FName& InPropertyName);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Returns true if a property by the given name exists in the container, else false.
- L46 _public prototype_ `int32 GetNumProperties() const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the number of properties that this container holds.
- L50 _public prototype_ `TArray<FName> GetPropertyNames() const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the names of properties in this container.
- L55 _public prototype_ `TMap<FName, FString> GetPropertyMetadata(const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the metadata for the given property.
- L60 _public prototype_ `bool GetValueBool(const FName& InPropertyName, bool& bOutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the bool value of the held data. Returns true on success, else false.
- L64 _public prototype_ `bool GetValueByte(const FName& InPropertyName, uint8& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the byte value of the held data. Returns true on success, else false.
- L68 _public prototype_ `bool GetValueInt32(const FName& InPropertyName, int32& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the int32 value of the held data. Returns true on success, else false.
- L72 _public prototype_ `bool GetValueInt64(const FName& InPropertyName, int64& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the int64 value of the held data. Returns true on success, else false.
- L76 _public prototype_ `bool GetValueFloat(const FName& InPropertyName, float& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the float value of the held data. Returns true on success, else false.
- L80 _public prototype_ `bool GetValueDouble(const FName& InPropertyName, double& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the double value of the held data. Returns true on success, else false.
- L84 _public prototype_ `bool GetValueName(const FName& InPropertyName, FName& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the FName value of the held data. Returns true on success, else false.
- L88 _public prototype_ `bool GetValueString(const FName& InPropertyName, FString& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the FString value of the held data. Returns true on success, else false.
- L92 _public prototype_ `bool GetValueText(const FName& InPropertyName, FText& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the FText value of the held data. Returns true on success, else false.
- L96 _public prototype_ `bool GetValueEnum(const FName& InPropertyName, uint8& OutValue, const UEnum* RequestedEnum = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the enum value (for a specific enum) of the held data. Returns true on success, else false.
- L99 _public prototype_ `bool GetValueStruct(const FName& InPropertyName, FStructView& OutValue, const UScriptStruct* RequestedStruct = nullptr) const;` — Gets the struct value (for a specific struct) of the held data. Returns true on success, else false.
- L103 _public prototype_ `bool GetValueObject(const FName& InPropertyName, UObject*& OutValue, const UClass* RequestedClass = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the object value (for a specific class) of the held data. Returns true on success, else false.
- L107 _public prototype_ `bool GetValueClass(const FName& InPropertyName, UClass*& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the UClass value of the held data. Returns true on success, else false.
- L111 _public prototype_ `FString GetValueSerializedString(const FName& InPropertyName);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the serialized string value of the held data.
- L115 _public function_ `template <typename T> bool GetValueEnum(const FName& InPropertyName, T& OutValue) const` — Gets the enum value of the held data. Returns true on success, else false.
- L122 _public function_ `template <typename T> bool GetValueStruct(const FName& InPropertyName, T*& OutValue) const` — Gets the struct value of the held data. Returns true on success, else false.
- L129 _public function_ `template <typename T> bool GetValueObject(const FName& InPropertyName, T*& OutValue) const` — Gets the object value of the held data. Returns true on success, else false.
- L136 _public prototype_ `bool SetValueBool(const FName& InPropertyName, const bool bInValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the bool value of the held data. Returns true on success, else false.
- L140 _public prototype_ `bool SetValueByte(const FName& InPropertyName, const uint8 InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the byte value of the held data. Returns true on success, else false.
- L144 _public prototype_ `bool SetValueInt32(const FName& InPropertyName, const int32 InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the int32 value of the held data. Returns true on success, else false.
- L148 _public prototype_ `bool SetValueInt64(const FName& InPropertyName, const int64 InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the int64 value of the held data. Returns true on success, else false.
- L152 _public prototype_ `bool SetValueFloat(const FName& InPropertyName, const float InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the float value of the held data. Returns true on success, else false.
- L156 _public prototype_ `bool SetValueDouble(const FName& InPropertyName, const double InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the double value of the held data. Returns true on success, else false.
- L160 _public prototype_ `bool SetValueName(const FName& InPropertyName, const FName InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the FName value of the held data. Returns true on success, else false.
- L164 _public prototype_ `bool SetValueString(const FName& InPropertyName, const FString& InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the FString value of the held data. Returns true on success, else false.
- L168 _public prototype_ `bool SetValueText(const FName& InPropertyName, const FText& InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the FText value of the held data. Returns true on success, else false.
- L172 _public prototype_ `bool SetValueEnum(const FName& InPropertyName, const uint8 InValue, const UEnum* Enum);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the enum value of the held data. Returns true on success, else false.
- L175 _public prototype_ `bool SetValueStruct(const FName& InPropertyName, FConstStructView InValue);` — Sets the struct value of the held data. Returns true on success, else false.
- L179 _public prototype_ `bool SetValueObject(const FName& InPropertyName, UObject* InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the object value of the held data. Returns true on success, else false.
- L183 _public prototype_ `bool SetValueClass(const FName& InPropertyName, UClass* InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the class value of the held data. Returns true on success, else false.
- L187 _public prototype_ `bool SetValueSerializedString(const FName& InPropertyName, const FString& NewValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the serialized value of the held data. The string should be the serialized representation of the value. Returns true on success, else false.
- L191 _public function_ `template <typename T> bool SetValueEnum(const FName& InPropertyName, const T InValue)` — Sets the enum value of the held data. Returns true on success, else false.
- L198 _public function_ `template <typename T> bool SetValueStruct(const FName& InPropertyName, const T& InValue)` — Sets the struct value of the held data. Returns true on success, else false.
- L205 _public function_ `template <typename T> bool SetValueObject(const FName& InPropertyName, T* InValue)` — Sets the object value of the held data. Returns true on success, else false.
- L212 _public prototype_ `EMovieGraphValueType GetValueType(const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the type of the stored data.
- L216 _public prototype_ `void SetValueType(const FName& InPropertyName, EMovieGraphValueType ValueType, UObject* InValueTypeObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the type of the stored data. Enums, structs, and classes must specify a value type object.
- L220 _public prototype_ `const UObject* GetValueTypeObject(const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the object that defines the enum, struct, or class.
- L224 _public prototype_ `void SetValueTypeObject(const FName& InPropertyName, const UObject* ValueTypeObject);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the object that defines the enum, struct, or class.
- L228 _public prototype_ `EMovieGraphContainerType GetValueContainerType(const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the container type of the stored value.
- L232 _public prototype_ `void SetValueContainerType(const FName& InPropertyName, EMovieGraphContainerType ContainerType);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the container type of the stored value.
- L238 _public prototype_ `TValueOrError<FPropertyBagArrayRef, EPropertyBagResult> GetArrayRef(const FName& InPropertyName);` — Gets a reference to the array backing the value, if any. GetValueContainerType() will return EMovieGraphContainerType::Array if the value is holding an array.
- L245 _private member_ `TObjectPtr<UMovieGraphMutableValueView> ValuesView = nullptr;` — `UPROPERTY(Transient)`
- L253 _private member_ `FInstancedPropertyBag Values;` — `UPROPERTY(EditAnywhere, meta=(ShowOnlyInnerProperties, FixedLayout), Category = "Value")` — The values held by this container.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphNamedResolution.h` (Public)


#### struct `FMovieGraphNamedResolution`  
`struct FMovieGraphNamedResolution`  
_L12-59_
- reflection: `USTRUCT(BlueprintType)`
- desc: Holds information about a screen resolution to be used for rendering.
- L18 _public prototype_ `FMovieGraphNamedResolution() = default;`
- L20 _public function_ `FMovieGraphNamedResolution( const FName& InResolutionProfileName, const FIntPoint InResolution, const FString& InDescription) : ProfileName(InResolutionProfileName) , Resolution(InResolution) , Description(InDescription)`
- L30 _public member_ `FName ProfileName = DefaultResolutionName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Movie Graph|Resolution")` — The name of the resolution this links to
- L34 _public member_ `FIntPoint Resolution = DefaultResolution;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Movie Graph|Resolution")` — The screen resolution (in pixels).
- L38 _public member_ `FString Description = FString();` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Movie Graph|Resolution")` — The description text for this screen resolution.
- L40 _public function_ `bool IsValid() const`
- L48 _public member_ `inline static FName DefaultResolutionName = TEXT("108` — The default resolution name to use when one is not defined.
- L53 _public member_ `inline static FIntPoint DefaultResolution = FIntPoint(1920, 1080);` — The default resolution name to use when one is not defined.
- L58 _public member_ `inline static FName CustomEntryName = TEXT("Cus` — Predefined name for the 'custom' resolution option in the combobox

#### Free symbols / members of external scopes

- L63 _function_ `inline FString LexToString(const FMovieGraphNamedResolution InResolution)` — Convert a FMovieGraphNamedResolution into a string

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphNode.h` (Public)


#### struct `FMovieGraphPropertyInfo`  
`struct FMovieGraphPropertyInfo`  
_L41-98_
- reflection: `USTRUCT(BlueprintType)`
- desc: Information about a property that currently is (or can be) exposed on a node.
- L47 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — The name of the property.
- L51 _public member_ `FText ContextMenuName;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — The display name of the property which will be shown in the context menu. If empty, the value from 'Name' will be used.
- L55 _public member_ `FName PromotionName;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — If this property is promoted, this is the name of the variable that is created. If empty, the value from 'Name' will be used.
- L59 _public member_ `bool bIsDynamicProperty = false;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — Whether this property is dynamic (ie, it does not correspond to a native UPROPERTY on the node).
- L63 _public member_ `EMovieGraphValueType ValueType = EMovieGraphValueType::None;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — The type of the value pointed to by the property.
- L67 _public member_ `TObjectPtr<const UObject> ValueTypeObject;` — `UPROPERTY()` — The associated value type object if the ValueType is an enum, struct, class, or object.
- L73 _public member_ `bool bIsPermanentlyExposed = false;` — `UPROPERTY()` — Whether this property is permanently exposed on the node. If true, it cannot be toggled on/off (via Expose Property as Pin).
- L83 _public function_ `bool IsSamePropertyAs(const FMovieGraphPropertyInfo& Other) const` — Determines if this struct represents the same property as another instance of this struct. The equality operator ensures equality of all members of the struct. However, there may be cases where, for example, a dynamic property changes its value type, and the ValueType member has not been changed yet. Two structs that have the same Name and bIsDynamicProperty values should still be considered identical for the purposes of determining if they identify the same property.
- L88 _public function_ `bool operator==(const FMovieGraphPropertyInfo& Other) const`

#### struct `FMovieGraphTokenResolveContext`  
`struct FMovieGraphTokenResolveContext`  
_L105-113_
- reflection: `USTRUCT(BlueprintType)`
- desc: Additional context provided to ResolveTokenContainingProperties(). May be helpful if the node needs to implement custom {token} resolve behavior that goes beyond the default resolve behavior that MRG provides.
- L109 _public prototype_ `FMovieGraphTokenResolveContext() = default;`
- L111 _public member_ `const FMovieGraphRenderDataIdentifier* RenderDataIdentifier = nullptr;`
- L112 _public member_ `const FMovieGraphTraversalContext* TraversalContext = nullptr;`

#### enum `EMovieGraphBranchRestriction`  
`enum class EMovieGraphBranchRestriction : uint8`  
_L117-122_
- reflection: `UENUM(BlueprintType)`
- desc: Describes a restriction on what kind of branch a node can be created in within the graph.
- L119 _public enumerator_ `Any` — The node can be created in any type of branch
- L120 _public enumerator_ `Globals` — The node must be created in the Globals branch
- L121 _public enumerator_ `RenderLayer` — The node must be created in a branch representing a render layer

#### class `UMovieGraphNode`  
`class UMovieGraphNode : public UObject`  
_L130-484_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: This is a base class for all nodes that can exist in the UMovieGraphConfig network. In the editor, each node in the network will have an editor-only representation too which contains data about it's visual position in the graph, comments, etc.
- L139 _public member_ `static FName GlobalsPinName;`
- L140 _public member_ `static FString GlobalsPinNameString;`
- L142 _public prototype_ `UMovieGraphNode();`
- L146 _public function_ `const TArray<UMovieGraphPin*>& GetInputPins() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets all input pins on the node. Note that the returned array is const, so input pins cannot be added/removed from the node via this array.
- L150 _public function_ `const TArray<UMovieGraphPin*>& GetOutputPins() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets all output pins on the node. Note that the returned array is const, so output pins cannot be added/removed from the node via this array.
- L154 _public function_ `virtual TArray<FMovieGraphPinProperties> GetInputPinProperties() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the properties for all input pins.
- L161 _public function_ `virtual TArray<FMovieGraphPinProperties> GetOutputPinProperties() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the properties for all output pins.
- L170 _public function_ `virtual FString GetResolvedValueForOutputPin(const FName& InPinName, const FMovieGraphTraversalContext* InContext) const` — Gets the resolved value of a named output pin (one that is returned in GetOutputPinProperties()). If the resolved value could not be determined, an empty string is returned.
- L179 _public function_ `virtual bool GetResolvedValueForOutputPin(const FName& InPinName, const FMovieGraphTraversalContext* InContext, TObjectPtr<UMovieGraphValueContainer>& OutValueContainer) const` — The same functionality as the other method that returns a string. However, this version returns true if a resolved value could be determined, and provides the value via a UMovieGraphValueContainer.
- L188 _public function_ `virtual TArray<FPropertyBagPropertyDesc> GetDynamicPropertyDescriptions() const` — Gets the descriptions of properties which can be dynamically added to the node. These types of properties do not correspond to a UPROPERTY defined on the node itself.
- L197 _public prototype_ `bool SetDynamicPropertyValue(const FName PropertyName, const FString& InNewValue);` — Sets the value of the dynamic property with the specified name. Note that the provided value must be the serialized representation of the value. Returns true upon success, else false.
- L203 _public prototype_ `virtual bool GetDynamicPropertyValue(const FName PropertyName, FString& OutValue);` — Gets the value of the dynamic property with the specified name. Provides the serialized value of the property in "OutValue". Returns true if "OutValue" was set and there were no errors, else returns false.
- L210 _public prototype_ `UMovieGraphMutableValueView* GetDynamicPropertiesView() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the dynamic properties as a view. The view provides a scripting-friendly way of getting and modifying the values within the dynamic properties.
- L213 _public prototype_ `const FBoolProperty* FindOverridePropertyForDynamicProperty(const FName& InPropertyName) const;` — Gets the override property for the specified dynamic property. If one does not exist, returns nullptr.
- L219 _public prototype_ `bool IsDynamicPropertyOverridden(const FName& InPropertyName) const;` — Returns true if the dynamic property with the provided name has been overridden, else false. Note that the name provided should not be prefixed with "bOverride_".
- L225 _public prototype_ `void SetDynamicPropertyOverridden(const FName& InPropertyName, const bool bIsOverridden);` — Sets the dynamic property with the provided name to the specified override state. Note that the name provided should not be prefixed with "bOverride_".
- L229 _public prototype_ `virtual TArray<FMovieGraphPropertyInfo> GetOverrideablePropertyInfo() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the information about properties which can be exposed as a pin on the node.
- L233 _public function_ `virtual TArray<FMovieGraphPropertyInfo> GetExposedProperties() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the information about properties which are currently exposed as pins on the node.
- L247 _public prototype_ `virtual TArray<UMovieGraphPin*> EvaluatePinsToFollow(FMovieGraphEvaluationContext& InContext) const;` — Used to determine which pins we should follow when trying to traverse the graph. By default we will follow any input pin (with Branch type) on the node, but override this in inherited classes and change that if you need custom logic, such as boolean nodes that want to choose one or the other based on the results of a conditional property. Note that if custom logic is provided, the case where the node is disabled should be handled as well.
- L255 _public function_ `virtual UMovieGraphValueContainer* GetPropertyValueContainerForPin(const FString& InPinName) const` — When a non-branch pin type is being evaluated on a node, the calling node will ask this node for the value connected to the given pin name. For example, a Branch node will call this function on whatever node is connected to the Conditional pin, and then will try to get a Boolean value out of the returned UMovieGraphValueContainer.
- L262 _public prototype_ `virtual void TogglePromotePropertyToPin(const FName& PropertyName);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Toggles the promotion of the property with the given name to a pin on the node.
- L266 _public prototype_ `virtual void PromotePropertyToPin(const FName& PropertyName);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Promotes the given PropertyName to a pinned property, if it is found in GetOverrideablePropertyInfo(). Throws a kismet (scripting) exception if it isn't a overridable property.
- L270 _public prototype_ `virtual void UnpromotePropertyFromPin(const FName& PropertyName);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Unpromotes a given PropertyName from being pinned. Throws a kismet (scripting) exception if it's not already exposed. See GetExposedProperties()
- L278 _public prototype_ `virtual bool GetCustomPromotionDefaultValue(const FMovieGraphPropertyInfo& InPropertyInfo, FString& OutSerializedValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Allows subclasses to provide a custom serialized default value when a property is promoted to a variable. Called during "Promote to Variable" before writing the variable's default. Return true and set OutSerializedValue to override; return false for normal behavior.
- L285 _public function_ `virtual bool CanBeAddedByUser() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Determines if this node type can be added to the graph interactively by a user or via the API when constructing a graph. @return true if the object can be added via the API, false otherwise
- L292 _public prototype_ `TArray<const FProperty*> GetAllOverrideableProperties() const;` — Gets all overrideable properties that are defined on the node. This includes UPROPERTY-defined properties, as well as dynamic properties. "Overrideable" means that the property has a corresponding property prefixed with "bOverride_".
- L294 _public prototype_ `void UpdatePins();`
- L295 _public prototype_ `void UpdateDynamicProperties();`
- L296 _public prototype_ `class UMovieGraphConfig* GetGraph() const;`
- L304 _public prototype_ `FInstancedPropertyBag* GetMutableDynamicProperties_Unsafe() const;` — Gets the property bag instance that backs the dynamic properties on this node. Should not be used except for very specific, niche cases where the property bag needs to be accessed/modified directly, like for details customizations. For normal uses, the other dynamic property methods should be used.
- L312 _public prototype_ `UMovieGraphPin* GetInputPin(const FName& InPinLabel, const EMovieGraphPinQueryRequirement PinRequirement = EMovieGraphPinQueryRequirement::BuiltInOrDynamic) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the input pin with the specified name, or nullptr if one could not be found. Most pins on a node are "built-in", meaning they ship with the node. Dynamic pins (pins which are not built-in) can potentially have the same name as a built-in (eg, the option pins on the Select node). To disambiguate between built-in and dynamic pins, specify bIsBuiltInPin = false if trying to fetch a pin that is not built-in.
- L316 _public prototype_ `UMovieGraphPin* GetOutputPin(const FName& InPinLabel) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the output pin with the specified name, or nullptr if one could not be found.
- L320 _public prototype_ `UMovieGraphPin* GetFirstConnectedInputPin() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the first input pin on the node which has a connection, or nullptr if no pins are connected.
- L324 _public prototype_ `UMovieGraphPin* GetFirstConnectedOutputPin() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the first output pin on the node which has a connection, or nullptr if no pins are connected.
- L327 _public function_ `const FGuid& GetGuid() const` — Gets the GUID which uniquely identifies this node.
- L331 _public function_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Determines which types of branches the node can be created in.
- L335 _public prototype_ `virtual bool CanBeDisabled() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Determines if this node can be disabled.
- L339 _public prototype_ `void SetDisabled(const bool bNewDisableState);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Set whether this node is currently disabled.
- L343 _public prototype_ `bool IsDisabled() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Determines if this node is currently disabled.
- L350 _public prototype_ `virtual bool GetNodeValidationErrors(const FName& InBranchName, const UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<FText>& OutValidationErrors) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets any validation errors that the node generated. Validation errors will halt the active render, if any. Called on the fully-evaluated node post-evaluation. Returns true if there were any errors (added to OutValidationErrors), else false.
- L354 _public function_ `int32 GetNodePosX() const` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")`
- L356 _public function_ `int32 GetNodePosY() const` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")`
- L359 _public function_ `void SetNodePosX(const int32 InNodePosX)` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L361 _public function_ `void SetNodePosY(const int32 InNodePosY)` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L364 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const;` — Gets the node's title color, as visible in the graph.
- L367 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const;` — Gets the node's icon and icon tint, as visible in the graph.
- L370 _public function_ `FString GetNodeComment() const` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")`
- L372 _public function_ `void SetNodeComment(const FString& InNodeComment)` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L375 _public function_ `bool IsCommentBubblePinned() const` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")`
- L377 _public function_ `void SetIsCommentBubblePinned(const uint8 bIsPinned)` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L380 _public function_ `bool IsCommentBubbleVisible() const` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")`
- L382 _public function_ `void SetIsCommentBubbleVisible(uint8 bIsVisible)` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L391 _public prototype_ `virtual TArray<TPair<FName, UClass*>> GetHiddenProperties() const;` — Gets the properties on this node that should be hidden by the base UMovieGraphNode customization. The FName in the pair is the property name, and the UClass* is the class that the property is defined on (may be a base class). Note that other customizations can easily override this behavior, but it's useful in cases where (for example) an inherited property should be hidden, and there aren't any other customizations needed.
- L395 _public prototype_ `virtual void PostLoad() override;`
- L396 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L400 _public member_ `FOnMovieGraphNodeChanged OnNodeChangedDelegate;`
- L407 _public member_ `TArray<FString> ScriptTags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")` — Tags that can be used to identify this node within a pre/post render script. Tags can be unique in order to identify this specific node, or the same tag can be applied to multiple nodes in order to identify a grouping of nodes.
- L412 _public member_ `TObjectPtr<UEdGraphNode> GraphNode;` — `UPROPERTY()` — Editor Node Graph representation. Not strongly typed to avoid circular dependency between editor/runtime modules.
- L414 _public prototype_ `class UEdGraphNode* GetGraphNode() const;`
- L423 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const PURE_VIRTUAL(UMovieGraphNode::GetNodeTitle, return FText(););` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the node's title. Optionally gets a more descriptive, multi-line title for the node if bGetDescriptive is set to true.
- L427 _public prototype_ `virtual FText GetMenuCategory() const PURE_VIRTUAL(UMovieGraphNode::GetMenuCategory, return FText(); );` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the category that the node belongs under.
- L431 _public function_ `virtual FText GetKeywords() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the keywords (space-separated) that will be searched in the node creation context menu.
- L436 _protected prototype_ `virtual TArray<FMovieGraphPinProperties> GetExposedPinProperties() const;` — Gets the pin properties for all properties which have been exposed on the node.
- L439 _protected function_ `virtual void RegisterDelegates()` — Register any delegates that need to be set up on the node. Called in PostLoad().
- L443 _protected member_ `TArray<TObjectPtr<UMovieGraphPin>> InputPins;` — `UPROPERTY()`
- L446 _protected member_ `TArray<TObjectPtr<UMovieGraphPin>> OutputPins;` — `UPROPERTY()`
- L450 _protected member_ `FInstancedPropertyBag DynamicProperties;` — `UPROPERTY(EditAnywhere, meta=(FixedLayout, ShowOnlyInnerProperties), Category = "Properties")` — Properties which can be dynamically declared on the node (vs. native properties which are always present).
- L454 _protected member_ `mutable TObjectPtr<UMovieGraphMutableValueView> DynamicPropertiesView = nullptr;` — `UPROPERTY(Transient)` — A property view which points to the dynamic properties on this node.
- L458 _protected member_ `TArray<FMovieGraphPropertyInfo> ExposedPropertyInfo;` — `UPROPERTY()` — Tracks which properties have been exposed on the node as inputs.
- L462 _protected member_ `int32 NodePosX = 0;` — `UPROPERTY()`
- L465 _protected member_ `int32 NodePosY = 0;` — `UPROPERTY()`
- L468 _protected member_ `FString NodeComment;` — `UPROPERTY()`
- L471 _protected member_ `uint8 bIsCommentBubblePinned : 1;` — `UPROPERTY()`
- L474 _protected member_ `uint8 bIsCommentBubbleVisible : 1;` — `UPROPERTY()`
- L479 _protected member_ `uint8 bIsDisabled : 1;` — `UPROPERTY()` — Whether this node is currently disabled in the graph.
- L483 _protected member_ `FGuid Guid;` — `UPROPERTY()` — A GUID which uniquely identifies this node.

#### class `UMovieGraphSettingNode`  
`class UMovieGraphSettingNode : public UMovieGraphNode`  
_L490-564_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UMovieGraphNode`
- desc: Nodes representing user settings should derive from this. This is the only node type copied into flattened eval.
- L496 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetInputPinProperties() const override;` — UMovieGraphNode Interface
- L497 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetOutputPinProperties() const override;`
- L505 _public function_ `virtual FString GetNodeInstanceName() const` — An identifier that distinguishes this node from other nodes of the same type within a branch. During graph traversal, nodes with the same type and identifier are considered the same node. An empty string is a valid identifier.
- L513 _public function_ `virtual void PrepareForFlattening(const UMovieGraphSettingNode* InSourceNode)` — In some very rare cases, a node needs to be "primed" from the node that the flattening is starting from before it's actually put through the flattening process. The need for this should be exceedingly uncommon, so only use if absolutely necessary.
- L528 _public function_ `virtual void PostFlatten()` — When the graph asset was loaded, any deprecated properties were converted to their "real" representations in PostLoad. However, scripting can edit these assets after load - either an editor script, or an ExecuteScript node, and these custom scripts may still be (re) setting the deprecated property, at which point the runtime code will ignore it. To catch these scenarios, after the graph is flattened, we call PostFlatten on each node in the graph which gives it one more chance to do the conversion from deprecated properties to real ones, and warn the user that they need to update their scripts. This is called on the flattened graph, so only one "merged" copy of the nodes exist at this point.
- L539 _public function_ `virtual void GetFormatResolveArgs(FMovieGraphResolveArgs& OutMergedFormatArgs, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier) const` — This is called either on the CDO, or on a "flattened" instance of the node every frame when generating filename/file metadata, allowing the node to add custom key-value pairs (FString, FString) to be used as {format_tokens} in filenames, or to be included in File metadata. Nodes can read their own settings (such as temporal sub-sample count) and add it to the available list of tokens. Because this is called either on the CDO or on a flattened instance, there is no need to worry about resolving the settings of the graph, the node only needs to read its own values.
- L557 _public prototype_ `virtual void ResolveTokenContainingProperties(TFunction<void(FString&)>& ResolveFunc, const FMovieGraphTokenResolveContext& InContext);` — Resolves the values of properties that contain {tokens} to their final value. Graph evaluation performs this step after after the graph has been completely flattened, and it's the node's responsibility to implement this method if any of its properties have {tokens} that need to be resolved. All properties that need to be resolved should have ResolveFunc() called on them; this will update the node's property with the resolved value. Regular MRG tokens, as well as tokens from the Naming Tokens (CAT) system, will be resolved. Nodes can also implement custom resolver behavior here if needed, using the additional context provided. Select MRG tokens may not be resolved correctly here due to the point in the graph evaluation lifecycle that this resolve step occurs (eg, {camera_name}). Nodes that implement this method should also take care to call the super class in order to ensure inherited properties are covered. If the properties resolved here should use the token autocomplete widget in the details panel, include the MrgTokenAutocomplete UPROPERTY metadata on them (eg, `meta=(MrgTokenAutocomplete)`). Note that this metadata will only take effect for top-level properties (ie, properties that are directly declared on the node); properties that are embedded in structs, for example, will not be detected.
- L560 _public function_ `virtual void BuildNewProcessCommandLineArgsImpl(TArray<FString>& InOutUnrealURLParams, TArray<FString>& InOutCommandLineArgs, TArray<FString>& InOutDeviceProfileCvars, TArray<FString>& InOutExecCmds) const` — Modify the Unreal URL and command line arguments when the node will be run in a new process. Only applies to nodes in the Globals branch.
- L563 _public function_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const` — Updates telemetry data for this node. Should only be used by nodes that ship with Movie Render Graph. Called on the fully-evaluated node in the flattened graph.

#### class `UMovieGraphPostRenderNode`  
`class UMovieGraphPostRenderNode : public UInterface`  
_L567-570_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMovieGraphPostRenderNode`  
`class IMovieGraphPostRenderNode`  
_L575-588_
- desc: A node which runs after renders have completed. Can run after a single shot renders and/or after a sequence renders all of its shots.
- L581 _public prototype_ `virtual void BeginExport(UMovieGraphPipeline* InMoviePipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph) = 0;` — Begins the export process for this node after all shots have completed.
- L584 _public prototype_ `virtual void BeginShotExport(UMovieGraphPipeline* InMoviePipeline) = 0;` — Begins the export process for this node after an individual shot completes.
- L587 _public prototype_ `virtual bool HasFinishedExporting() = 0;` — Returns true if this node has finished its export process, else false.

#### class `UMovieGraphEvaluationNodeInjector`  
`class UMovieGraphEvaluationNodeInjector : public UInterface`  
_L591-594_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintable)`
- inherits: `UInterface`

#### class `IMovieGraphEvaluationNodeInjector`  
`class IMovieGraphEvaluationNodeInjector : public IInterface`  
_L600-613_
- inherits: `IInterface`
- desc: Provides the interface that nodes must implement if they need to inject additional nodes into the graph at various points in the graph evaluation cycle.
- L612 _public prototype_ `virtual void InjectNodesPostEvaluation(const FName& InBranchName, UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<UMovieGraphSettingNode*>& OutInjectedNodes);` — `UFUNCTION(BlueprintCallable, Category = "Evaluation")` — Injects nodes into the EVALUATED graph. Called on the fully evaluated node. All new nodes should be outered to InEvaluatedConfig. Because these nodes are injected post-evaluation, the movie pipeline will be immediately shut down if any of the returned nodes already exist in the branch (having two nodes of the same type in the same branch post-evaluation is not allowed). Note that modifying the Globals branch is not typically advised because at this stage, it has already been merged into all other branches.

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphNodeChanged, const UMovieGraphNode*);`
- L35 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovieGraphNodeChanged, const UMovieGraphNode*);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphOCIOHelper.h` (Public)


#### class `FMovieGraphOCIOHelper`  
`class FMovieGraphOCIOHelper`  
_L15-72_
- desc: Provides utilities for nodes that need to include OCIO output functionality.
- L18 _public prototype_ `FMovieGraphOCIOHelper() = default;`
- L25 _public prototype_ `static bool GenerateOcioPixelPreProcessor( const UE::MovieGraph::FMovieGraphSampleState* InPayload, const UMovieGraphPipeline* InPipeline, const TObjectPtr<UMovieGraphEvaluatedConfig> InEvaluatedConfig, const FOpenColorIODisplayConfiguration& InConfiguration, const TMap<FString, FString>& InContext, TArray<FPixelPreProcessor>& OutPixelPreProcessors);` — Generates a new OCIO pixel PreProcessor and appends it to OutPixelPreProcessors. An OCIO context is generated based on the provided payload, pipeline, and evaluated graph.
- L33 _public prototype_ `static bool GenerateOcioPixelPreProcessorWithContext( const UE::MovieGraph::FMovieGraphSampleState* InPayload, const FOpenColorIODisplayConfiguration& InConfiguration, const TMap<FString, FString>& InResolvedContext, TArray<FPixelPreProcessor>& OutPixelPreProcessors);` — Generates a new OCIO pixel PreProcessor and appends it to OutPixelPreProcessors. The context used by OCIO is provided via InResolvedContext.
- L43 _public prototype_ `static TMap<FString, FString> ResolveOpenColorIOContext( const TMap<FString, FString>& InContext, const FMovieGraphRenderDataIdentifier& InRenderId, const UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig> InEvaluatedConfig, const FMovieGraphTraversalContext& InTraversalContext);` — Resolves an OpenColorIO context with supported tokens. @return The resolved key/value context.
- L67 _private prototype_ `static FPixelPreProcessor CreateOpenColorIOPixelPreProcessor(const FOpenColorIOColorConversionSettings& InConversionSettings, const TMap<FString, FString>& InContext);` — Convenience function to create an OpenColorIO CPU processor based on the specified conversion settings. We use the OpenColorIO processor wrapper directly to avoid concurrency issues with the uobjects lifetime. @return The pixel preprocessor if successful, nullptr otherwise.
- L71 _private prototype_ `static void ValidateDisableTonecurve(const UE::MovieGraph::FMovieGraphSampleState& InPayload);` — Utility function to warn the user in case they forgot to check "Disable Tone Curve", which in turn controls the render's scene capture source.

#### struct `FMovieGraphOCIOHelper::FOpenColorIOPixelPreProcessor`  
`struct FOpenColorIOPixelPreProcessor`  
_L52-59_
- L54 _public prototype_ `explicit FOpenColorIOPixelPreProcessor(FOpenColorIOWrapperProcessor&& InProcessor);`
- L56 _public prototype_ `void operator()(const FImagePixelData* PixelData) const;`
- L58 _public member_ `FOpenColorIOWrapperProcessor Processor;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphPin.h` (Public)


#### struct `FMovieGraphPinProperties`  
`struct FMovieGraphPinProperties`  
_L17-88_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public prototype_ `FMovieGraphPinProperties() = default;`
- L22 _public function_ `explicit FMovieGraphPinProperties(const FName& InLabel, const EMovieGraphValueType PinType, const TObjectPtr<const UObject>& TypeObject, bool bInAllowMultipleConnections) : Label(InLabel) , Type(PinType) , TypeObject(TypeObject) , bAllowMultipleConnections(bInAllowMultipleConnections)`
- L29 _public function_ `static FMovieGraphPinProperties MakeBranchProperties(const FName& InLabel = NAME_None)`
- L36 _public function_ `static FMovieGraphPinProperties MakeWildcardProperties(const FName& InLabel = NAME_None)`
- L45 _public member_ `FName Label = NAME_None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — The name assigned to the pin.
- L49 _public member_ `EMovieGraphValueType Type = EMovieGraphValueType::Float;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — The type of the pin. If the pin represents a branch, this type is ignored.
- L53 _public member_ `TObjectPtr<const UObject> TypeObject;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — The value type of the pin, if the type is an enum, struct, class, or object.
- L57 _public member_ `bool bAllowMultipleConnections = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — Whether this pin can accept multiple connections.
- L61 _public member_ `bool bIsBranch = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — Whether this pin represents a branch. If it does not represent a branch, then it is a value-providing pin.
- L65 _public member_ `bool bIsWildcard = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — Whether this pin represents a wildcard, which means it can be any type (including being a branch).
- L72 _public member_ `bool bIsBuiltIn = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — Whether this pin is built-in (ie, the pin ships with the node and cannot be removed). Option pins on the Select node would be an example of pins which are not built-in (they can be added and removed dynamically).
- L74 _public function_ `bool operator==(const FMovieGraphPinProperties& Other) const`
- L84 _public function_ `bool operator !=(const FMovieGraphPinProperties& Other) const`

#### enum `EMovieGraphPinQueryRequirement`  
`enum class EMovieGraphPinQueryRequirement : uint8`  
_L92-102_
- reflection: `UENUM(BlueprintType)`
- desc: Specifies a restriction on pin properties when searching for a pin on a node.
- L95 _public enumerator_ `BuiltIn` — The pin must be built-in, meaning that it is always present on the node.
- L98 _public enumerator_ `Dynamic` — The pin must be dynamic, meaning that it may not always exist on the node. These are typically user-created pins.
- L101 _public enumerator_ `BuiltInOrDynamic` — The pin can be either built-in or dynamic.

#### class `UMovieGraphPin`  
`class UMovieGraphPin : public UObject`  
_L106-212_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L113 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;`
- L117 _public prototype_ `bool AddEdgeTo(UMovieGraphPin* InOtherPin);`
- L118 _public prototype_ `bool BreakEdgeTo(UMovieGraphPin* InOtherPin);`
- L119 _public prototype_ `bool BreakAllEdges();`
- L120 _public prototype_ `FPinConnectionResponse CanCreateConnection_PinConnectionResponse(const UMovieGraphPin* InOtherPin) const;`
- L123 _public prototype_ `bool CanCreateConnection(const UMovieGraphPin* InOtherPin) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L126 _public prototype_ `bool IsConnected() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L129 _public prototype_ `bool IsInputPin() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L132 _public prototype_ `bool IsOutputPin() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L136 _public prototype_ `int32 EdgeCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the number of edges connected to this pin. May include invalid edges (which can happen if connected to an invalid node).
- L139 _public prototype_ `bool AllowsMultipleConnections() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L146 _public prototype_ `UMovieGraphPin* GetFirstConnectedPin(const bool bFollowRerouteConnections = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the first pin connected to this pin. Returns nullptr if no valid connection exists. If bFollowRerouteConnections is true, this method will continue traversing the graph past reroute nodes until a non-reroute pin is found.
- L150 _public prototype_ `TArray<UMovieGraphPin*> GetAllConnectedPins() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets all connected pins.
- L158 _public prototype_ `TArray<UMovieGraphNode*> GetConnectedNodes() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Utility function for scripting which gathers all of the nodes connected to this particular pin. Equivalent to looping through all of the edges, getting the connected pin, and then getting the node associated with that pin.
- L165 _public prototype_ `bool IsConnectionToBranchAllowed(const UMovieGraphPin* OtherPin, FText& OutError) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Determines if the connection between this pin and OtherPin follows branch restriction rules. OutError is populated with an error if the connection should be rejected and the function will return false.
- L169 _public prototype_ `bool IsPinDirectionCompatibleWith(const UMovieGraphPin* OtherPin) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Determines if this pin's direction is compatible with another pin's direction. One needs to be an input, and the other an output.
- L176 _public prototype_ `bool IsTypeCompatibleWith(const UMovieGraphPin* InOtherPin) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Determines if this pin's type is compatible with another pin's type. Generally the types have to match exactly in order to be compatible, but there may be cases where different types can be used interchangeably.
- L181 _public member_ `TObjectPtr<UMovieGraphNode> Node = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Properties")` — The node that this pin belongs to.
- L184 _public member_ `FMovieGraphPinProperties Properties;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Properties", meta = (ShowOnlyInnerProperties))`
- L191 _public member_ `TArray<TObjectPtr<UMovieGraphEdge>> Edges;` — `UPROPERTY(BlueprintReadOnly, TextExportTransient, Category = "Properties")` — A list of edges between pins. This is marked as TextExportTransient so that when we copy/paste nodes, we don't copy the edges, as they are rebuilt after paste based on the editor graph connections.
- L198 _private prototype_ `void PropagatePinType(const UMovieGraphPin* InInputPin, const UMovieGraphPin* InOutputPin);` — Given a pair of input and output pins which a connection was made between, propagate the type either upstream or downstream depending on the nodes the connection was made between.
- L201 _private prototype_ `void PropagatePinProperties(const FMovieGraphPinProperties PinProperties, const bool bPropagateUpstream) const;` — Propagate the given properties either upstream or downstream from this pin. This pin is not changed.
- L208 _private prototype_ `void MaybeRevertToWildcard(const UMovieGraphPin* InPin);` — Potentially reverts InPin (and the reroute nodes connected to/from it) to a wildcard if InPin no longer has any upstream or downstream connections that provide a type. In other words, InPin is part of a reroute "island" where the reroute nodes are only connected to other reroute nodes.
- L211 _private member_ `mutable bool bPropagateTypeRecursionGuard = false;` — Recursion guard boolean to prevent PropagatePinProperties from hanging if there is a cycle of reroute nodes.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphPipeline.h` (Public)


#### class `UMovieGraphPipeline`  
`class UMovieGraphPipeline : public UMoviePipelineBase`  
_L33-378_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineBase`
- L38 _public prototype_ `UMovieGraphPipeline();`
- L41 _public prototype_ `void Initialize(UMoviePipelineExecutorJob* InJob, const FMovieGraphInitConfig& InitConfig);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L49 _public function_ `UMoviePipelineExecutorJob* GetCurrentJob() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Returns the internal job being used by the Movie Graph Pipeline, which is a duplicate of the job provided originaly by Initialize. This allows scripting to mutate the job/configuration without leaking changes into assets or the original user-defined queue entry.
- L55 _public function_ `FDateTime GetInitializationTime() const` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Returns the time this movie pipeline was initialized at.
- L63 _public function_ `FTimespan GetInitializationTimeOffset() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — The offset that should be applied to the GetInitializationTime() when generating the {time} related filename tokens. GetInitializationTime() is in UTC so this is either zero (if you called SetInitializationTime) or your offset from UTC.
- L76 _public function_ `void SetInitializationTime(const FDateTime& InDateTime)` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Override the time this movie pipeline was initialized at. This can be used for render farms to ensure that jobs on all machines use the same date/time instead of each calculating it locally. Clears the auto-calculated InitializationTimeOffset, meaning time tokens will be written in UTC. Needs to be called after ::Initialize(...) @param InDateTime - Expected to be in UTC timezone.
- L79 _public prototype_ `UMovieGraphConfig* GetRootGraphForShot(UMoviePipelineExecutorShot* InShot) const;` — Gets the graph config for the shot if one was specified for the shot. Otherwise, gets the graph config for the associated primary job.
- L82 _public prototype_ `FMovieGraphTraversalContext GetCurrentTraversalContext(const bool bForShot = true) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")`
- L85 _public function_ `const TArray<TObjectPtr<UMoviePipelineExecutorShot>>& GetActiveShotList() const` — Get the Active Shot list, which is the full shot list generated from the external data source, with disabled shots removed.
- L88 _public function_ `int32 GetCurrentShotIndex() const` — Which index of the Active Shot List are we currently on
- L91 _public function_ `TObjectPtr<UMovieGraphEngineTimeStep> GetCustomEngineTimeStep() const` — Get the pointer to the Custom Engine Timestep we use to control engine ticking. Shared by all per-shot Time Steps.
- L94 _public prototype_ `void SetupShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot);` — Called by the TimeStepInstance when it's time to set up for another shot. Don't call this unless you know what you're doing.
- L97 _public prototype_ `void BeginShotSetup(const TObjectPtr<UMoviePipelineExecutorShot>& InShot);` — Prepares shot hierarchy and per-shot settings before the shot's first data source evaluation.
- L100 _public prototype_ `void FinishShotSetup(const TObjectPtr<UMoviePipelineExecutorShot>& InShot);` — Initializes render resources that require the shot's data source to have evaluated at least once.
- L103 _public prototype_ `void TeardownShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot);` — Called by the TimeStepInstance when it's time to tear down the current shot. Don't call this unless you know what you're doing.
- L107 _public prototype_ `UMovieGraphTimeStepBase* GetTimeStepInstance() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Used occasionally to cross-reference other components. Don't call this unless you know what you're doing.
- L111 _public function_ `UMovieGraphRendererBase* GetRendererInstance() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Used occasionally to cross-reference other components. Don't call this unless you know what you're doing.
- L114 _public function_ `UMovieGraphDataSourceBase* GetDataSourceInstance() const` — Used occasionally to cross-reference other components. Don't call this unless you know what you're doing.
- L117 _public function_ `UMovieGraphAudioRendererBase* GetAudioRendererInstance() const` — Used occasionally to cross-reference other components. Don't call this unless you know what you're doing.
- L120 _public function_ `TSharedPtr<UE::MovieGraph::IMovieGraphOutputMerger> GetOutputMerger() const` — Gets the Output Merger for this Movie Pipeline which is responsible for gathering all of the data coming in for a given output frame, before making it available to the MovieGraphPipeline.
- L123 _public function_ `const TMap<TWeakObjectPtr<UObject>, TArray<MoviePipeline::FClothSimSettingsCache>>& GetClothSimCache() const` — Gets cached data for cloth simulations, needed to save/restore cloth sub-stepping.
- L126 _public function_ `TMap<TWeakObjectPtr<UObject>, TArray<MoviePipeline::FClothSimSettingsCache>>& GetClothSimCache()` — Gets cached data for cloth simulations, needed to save/restore cloth sub-stepping.
- L129 _public prototype_ `void AddOutputFuture(TFuture<bool>&& InOutputFuture, const UE::MovieGraph::FMovieGraphOutputFutureData& InData);` — Writing images to disk is an async process. When you start writing, declare a future with the filename you will eventually write to, and complete the future once it is on disk.
- L132 _public function_ `void SetPreviewWidgetVisible(bool bInIsVisible)` — Used by the Renderer Instance to disable the preview widget before rendering so it isn't baked into the UI Renderer.
- L138 _public prototype_ `TArray<FMovieGraphRenderOutputData>& GetGeneratedOutputData();` — Gets render data that was generated for each shot. This data is mutable, so processes that run after renders complete can add their additional outputs to the generated data. Care should be taken when removing output data.
- L144 _public prototype_ `void CreateLayersInRenderLayerSubsystem(const UMovieGraphEvaluatedConfig* EvaluatedConfig) const;` — Resets the render layer subsystem and updates it to reflect the render layers that are present in the evaluated graph. Does not update the contents of the layers, however. See UpdateLayerContentsInRenderLayerSubsystem().
- L151 _public prototype_ `void UpdateLayerContentsInRenderLayerSubsystem(const UMovieGraphEvaluatedConfig* EvaluatedConfig) const;` — Updates the contents of the layers that are currently present in the render layer subsystem by evaluating all available collections and modifiers. To update the layers that are present in the subsystem, see CreateLayersInRenderLayerSubsystem().
- L155 _protected prototype_ `virtual void OnMoviePipelineFinishedImpl();` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")`
- L157 _protected prototype_ `virtual void OnEngineTickBeginFrame();`
- L158 _protected prototype_ `virtual void OnEngineTickEndFrame();`
- L159 _protected prototype_ `virtual void RenderFrame();`
- L160 _protected prototype_ `virtual void BuildShotListFromDataSource();`
- L167 _protected prototype_ `virtual void ProcessOutstandingFinishedFrames();` — Sends the rendered pixel data to all file output nodes (they will use the "mask" provided to determine if they need to process the data). OnReceiveImageData() will be called on each of these nodes, and in turn they will typically call AddOutputFuture() on the pipeline to provide a future that communicates the status of their write task.
- L175 _protected prototype_ `virtual void ProcessOutstandingFutures(const bool bStallAndProcessAllFutures = false);` — Processes any futures that have completed by updating GeneratedOutputData. Futures are processed sequentially in the order that they're generated. If the future next-in-line to be processed has not completed, this will early exit, and must be called again to continue processing futures. Optionally, all futures can be processed by setting "bStallAndProcessAllFutures" to true; this will still process all futures sequentially, but waits for the current one to finish before moving on to the next (and so on).
- L177 _protected prototype_ `virtual void TickProducingFrames();`
- L178 _protected prototype_ `virtual void TickPostFinalizeExport(const bool bInForceFinish);`
- L179 _protected prototype_ `virtual void TickFinalizeOutputContainers(const bool bInForceFinish);`
- L180 _protected prototype_ `virtual void TransitionToState(const EMovieRenderPipelineState InNewState);`
- L181 _protected prototype_ `virtual const TSet<TObjectPtr<UMovieGraphFileOutputNode>> GetOutputNodesUsed() const;`
- L182 _protected prototype_ `virtual void BeginFinalize();`
- L185 _protected prototype_ `virtual void BeginExport();` — Begins the export process for a primary job (not called for shot jobs).
- L188 _protected prototype_ `void StartUnrealInsightsCapture(UMovieGraphEvaluatedConfig* EvaluatedConfig);` — Attempts to start an Unreal Insights capture to a file on disk adjacent to the movie output.
- L190 _protected prototype_ `void StopUnrealInsightsCapture();` — Attempts to stop an already started Unreal Insights capture.
- L192 _protected prototype_ `virtual void LoadPreviewWidget();`
- L193 _protected prototype_ `virtual void SetPreviewWidgetVisibleImpl(bool bInIsVisible);`
- L195 _protected prototype_ `virtual void DuplicateJobAndConfiguration();`
- L196 _protected prototype_ `virtual void ExecutePreJobScripts();`
- L197 _protected prototype_ `virtual void ExecutePostJobScripts(const FMoviePipelineOutputData& InData);`
- L198 _protected prototype_ `virtual void ExecutePreShotScripts(const TObjectPtr<UMoviePipelineExecutorShot>& InShot);`
- L199 _protected prototype_ `virtual void ExecutePostShotScripts(const FMoviePipelineOutputData& InData);`
- L203 _protected prototype_ `template<typename JobType> void UpdateVariableAssignmentsHelper(JobType* InTargetJob, TMap<TObjectPtr<UMovieGraphConfig>, TObjectPtr<UMovieGraphConfig>>& InOriginalToDuplicateGraphMap);` — Helps update variable assignments on the provided job to use duplicated graphs (reflected in the original-to-duplicate graph mapping).
- L206 _protected prototype_ `virtual void SetSoloShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot);` — Update our data source to isolate the shot we're currently working on, so that expanded shots don't interfere with each other.
- L212 _protected prototype_ `virtual void ExpandShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot, const int32 InNumHandleFrames, const bool bInHasMultipleTemporalSamples, const bool bIsPrePass, const FFrameRate& InDisplayRate, const FFrameRate& InTickResolution, const int32 InWarmUpFrames);` — Expand our data source (for a specific shot) for various rendering features (such as handle frames). Gets called twice, once where it expands the ranges, and again later to actually expand the tracks. This is required due to wanting "Handle Frames" to get counted in total frame counts.
- L216 _protected prototype_ `int32 ResolveVersionForShot(const TObjectPtr<UMoviePipelineExecutorShot>& Shot, const TObjectPtr<UMovieGraphEvaluatedConfig>& EvaluatedConfig);` — Resolve the version number that should be used for the specified shot (in {version} tokens).
- L219 _protected prototype_ `virtual void RequestShutdownImpl(bool bIsError) override;` — UMoviePipelineBase Interface
- L220 _protected prototype_ `virtual void ShutdownImpl(bool bIsError) override;`
- L221 _protected function_ `virtual bool IsShutdownRequestedImpl() const override`
- L222 _protected function_ `virtual EMovieRenderPipelineState GetPipelineStateImpl() const override`
- L223 _protected prototype_ `virtual bool IsPostShotCallbackNeeded() const override;`
- L227 _protected prototype_ `virtual void BeginDestroy() override;` — UObject Interface
- L233 _protected member_ `TArray<TObjectPtr<UMovieGraphTimeStepBase>> GraphTimeStepInstances;` — `UPROPERTY(Transient)` — Time step instances for each shot, where the index into the array corresponds to the shot index.
- L241 _protected member_ `TObjectPtr<UMovieGraphTimeStepBase> PendingTimeStepInstance;` — `UPROPERTY(Transient)` — If set, on the next TickProducingFrames, the GraphTimeStepInstance pointer will be swapped with this one. Uses a deferred mechanism since SetupShot/TeardownShot are called by the current instance, so we don't want to swap until the current instance isn't actively being used.
- L249 _protected member_ `TObjectPtr<UMovieGraphTimeStepBase> GraphTimeStepInstance;` — `UPROPERTY(Transient)` — Sometimes the shot index can be incremented before the time step instance should be changed, so the current time step instance is tracked. This should generally be used to access the current time step instance, rather than indexing into GraphTimeStepInstances with the shot index.
- L252 _protected member_ `TObjectPtr<UMovieGraphRendererBase> GraphRendererInstance;` — `UPROPERTY(Transient)`
- L255 _protected member_ `TObjectPtr<UMovieGraphDataSourceBase> GraphDataSourceInstance;` — `UPROPERTY(Transient)`
- L258 _protected member_ `TObjectPtr<UMovieGraphAudioRendererBase> GraphAudioRendererInstance;` — `UPROPERTY(Transient)`
- L265 _protected member_ `TObjectPtr<UMovieGraphEvaluatedConfig> PostRenderEvaluatedGraph;` — `UPROPERTY(Transient)` — The evaluated graph that should be referenced after all shot rendering is complete. This graph will originate from a primary job (not shot) and can be used in post-rendering tasks.
- L273 _protected member_ `TObjectPtr<UMoviePipelineExecutorJob> CurrentJob;` — `UPROPERTY(Transient)` — This is the job as was provided to the ::Initialize() call, which we duplicate to allow modifications to scripting without leaking changes into assets.
- L283 _protected member_ `TObjectPtr<UMoviePipelineExecutorJob> CurrentJobDuplicate;` — `UPROPERTY(Transient)` — This is the duplicated job, parented to the pipeline. The shots inside have been duplicated as well, and their graph configurations duplicated. Graph configurations are assets and scripting may want to modify them, or it may want to modify the variables in a job, so we have to duplicate both to allow a cleanly mutable version for scripting.
- L290 _protected member_ `TMap<TObjectPtr<UMovieGraphConfig>, TObjectPtr<UMovieGraphConfig>> DuplicatedGraphs;` — `UPROPERTY(Transient)` — Contains all duplicated graphs (for scripting purposes). Maps the original graph (key) to the duplicated graph (value). Duplicated graphs are part of the transient package.
- L293 _protected member_ `TArray<TObjectPtr<UMoviePipelineExecutorShot>> ActiveShotList;` — `UPROPERTY(Transient)`
- L296 _protected member_ `TSubclassOf<UMovieGraphRenderPreviewWidget> PreviewWidgetClassToUse;` — `UPROPERTY(Transient)`
- L299 _protected member_ `TObjectPtr<UMovieGraphRenderPreviewWidget> PreviewWidget;` — `UPROPERTY(Transient)`
- L303 _protected member_ `TArray<TObjectPtr<UMovieGraphScriptBase>> CurrentScriptInstances;` — `UPROPERTY(Transient)`
- L311 _protected member_ `TSet<TObjectPtr<UMovieGraphFileOutputNode>> OutputNodesDataSentTo;` — `UPROPERTY(Transient)` — An array of Node CDOs that we sent data through to write data to disk. This is the list of output nodes that will have OnAllFramesSubmitted/IsFinishedWritingToDisk on them.
- L313 _protected member_ `int32 CurrentShotIndex;`
- L316 _protected member_ `int32 CurrentShotStartOutputFrameNumber = 0;` — Output frame number at the start of the current shot.
- L319 _protected member_ `bool bIsTransitioningState;` — True if we're in a TransitionToState call. Used to prevent reentrancy.
- L322 _protected member_ `bool bIsTearingDownShot;` — True if we're in a TeardownShot call. Used to prevent reentrancy.
- L325 _protected member_ `FTimespan InitializationTimeOffset;` — When we originally initialize we store the offset from UTC (which is what GetInitializationTime() is in), but we clear this if you call SetInitializationTime.
- L328 _protected member_ `FThreadSafeBool bShutdownRequested;` — True if RequestShutdown() was called. At the start of the next frame we will stop producing frames and start shutting down.
- L331 _protected member_ `FThreadSafeBool bShutdownSetErrorFlag;` — Set to true during Shutdown/RequestShutdown if we are shutting down due to an error.
- L334 _protected member_ `EMovieRenderPipelineState PipelineState;` — Which step of the rendering process is the graph currently in.
- L337 _protected member_ `FDateTime GraphInitializationTime;` — What time (in UTC) was Initialization called? Used internally for tracking total job duration.
- L340 _protected member_ `TSharedPtr<UE::MovieGraph::IMovieGraphOutputMerger> OutputMerger;` — This gathers all of the produced data for an output frame (which may come in async, many frames later) before passing them onto the Output Containers.
- L346 _protected member_ `TArray<UE::MovieGraph::FMovieGraphOutputFuture> OutstandingOutputFutures;` — An array of Output Futures for files that have started writing to disk, but have not finished. Each frame we take each future that finishes writing to disk and push it into the GeneratedOutputData array.
- L352 _protected member_ `TArray<FMovieGraphRenderOutputData> GeneratedOutputData;` — An array of output data, one per shot. This only keeps track of the filenames generated during rendering (and is only pushed to once the file is actually on disk), and does not store pixel data.
- L355 _protected member_ `TSharedPtr<UE::MovieGraph::Private::FMovieGraphCVarManager> CVarManager;` — Responsible for managing cvars throughout the lifetime of the pipeline.
- L361 _protected member_ `TObjectPtr<UMovieGraphEngineTimeStep> CustomEngineTimeStep;` — `UPROPERTY(Transient)` — A custom timestep created by the Movie Graph Pipeline to allow the time step managers to set what the delta times for the frame should be.
- L365 _protected member_ `TObjectPtr<UEngineCustomTimeStep> PrevCustomEngineTimeStep;` — `UPROPERTY(Transient)` — The previous custom timestep the engine was using, if any.
- L368 _protected member_ `TMap<TWeakObjectPtr<UObject>, TArray<MoviePipeline::FClothSimSettingsCache>> ClothSimCache;` — Simulation settings cache per cloth interactor object. Needs one per LOD, hence the array.
- L371 _protected member_ `bool bDidStartInsightsCapture;` — Whether an insights capture was started when the pipeline was initialized.
- L374 _protected member_ `bool bWasInitializedWithBasicConfig = false;` — Whether the original job used Basic config before it was converted to a graph.
- L377 _public member_ `static FString DefaultPreviewWidgetAsset;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MovieGraph` (scope `UE`)
- L24 _typedef_ `typedef TTuple<TFuture<bool>, UE::MovieGraph::FMovieGraphOutputFutureData> FMovieGraphOutputFuture;` (scope `UE::MovieGraph`)
- L26 _namespace_ `namespace Private` (scope `UE::MovieGraph`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphProjectSettings.h` (Public)


#### class `UMovieGraphProjectSettings`  
`class UMovieGraphProjectSettings : public UDeveloperSettings`  
_L19-52_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = MovieRenderPipeline, DefaultConfig, meta=(DisplayName = "Movie Graph Settings"))`
- inherits: `UDeveloperSettings`
- desc: Settings that apply to the Movie Graph.
- L24 _public prototype_ `UMovieGraphProjectSettings();`
- L27 _public function_ `virtual FName GetContainerName() const override` — Gets the settings container name for the settings, either Project or Editor
- L29 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L36 _public prototype_ `const FMovieGraphNamedResolution* FindNamedResolutionForOption(const FName& InOption) const;` — Tries to find a match for the given option in DefaultNamedResolutions. @param InOption The name of the option. @return A raw pointer to an FMovieGraphNamedResolution if a match is found, nullptr otherwise.
- L43 _public member_ `TArray<FMovieGraphNamedResolution> DefaultNamedResolutions;` — `UPROPERTY(Config, EditAnywhere, Category = "Movie Graph")` — A list of default resolutions to render with, defined in Config/BaseMovieRenderPipeline.ini or Project Settings. These resolutions will appear in the MovieGraph's various output settings nodes.
- L47 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L50 _private prototype_ `void EnsureUniqueNamesInDefaultNamedResolutions();`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphQuickRenderSettings.h` (Public)


#### enum `EMovieGraphQuickRenderButtonMode`  
`enum class EMovieGraphQuickRenderButtonMode : uint8`  
_L17-24_
- reflection: `UENUM(BlueprintType)`
- desc: The type of render that the Quick Render toolbar button performs.
- L20 _public enumerator_ `NormalMovieRenderQueue` — Uses the active queue in the Movie Render Queue editor to do a render.
- L23 _public enumerator_ `QuickRender` — Use the Quick Render configuration to do a render.

#### enum `EMovieGraphQuickRenderMode`  
`enum class EMovieGraphQuickRenderMode : uint8`  
_L28-44_
- reflection: `UENUM(BlueprintType)`
- desc: The available modes for Quick Render to be put into.
- L31 _public enumerator_ `CurrentSequence` — Renders the level sequence that is currently active in Sequencer.
- L34 _public enumerator_ `UseViewportCameraInSequence` — Renders the level sequence active in Sequencer, but uses the viewport's camera instead (for the entire duration of the render).
- L37 _public enumerator_ `CurrentViewport UMETA(DisplayName="Current Viewport (Still)")` — Renders a single frame using the current viewport's camera.
- L40 _public enumerator_ `SelectedCameras UMETA(DisplayName="Selected Cameras (Still)")` — Renders one frame for each camera actor selected in the Outliner.

#### enum `EMovieGraphQuickRenderFrameRangeType`  
`enum class EMovieGraphQuickRenderFrameRangeType : uint8`  
_L48-58_
- reflection: `UENUM(BlueprintType)`
- desc: The frame range within the active level sequence that a Quick Render should use.
- L51 _public enumerator_ `PlaybackRange` — Use the frame range specified by the sequence's start and end frame.
- L54 _public enumerator_ `SelectionRange` — Use the sequence's selection as the start and end frame.
- L57 _public enumerator_ `Custom` — Use a custom frame range.

#### enum `EMovieGraphQuickRenderViewportLookFlags`  
`enum class EMovieGraphQuickRenderViewportLookFlags : uint8`  
_L65-73_
- reflection: `UENUM(BlueprintType, Flags, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: The aspects of the viewport that should be applied to the quick render.
- L67 _public enumerator_ `None = 0 UMETA(Hidden)`
- L68 _public enumerator_ `Ocio = 1 << 0 UMETA(DisplayName = "OCIO")`
- L69 _public enumerator_ `ShowFlags = 1 << 1`
- L70 _public enumerator_ `ViewMode = 1 << 2`
- L71 _public enumerator_ `Visibility = 1 << 3`
- L72 _public enumerator_ `EditorOnlyActors = 1 << 4 UMETA(DisplayName = "Show Editor-Only Actors")`

#### class `UMovieGraphQuickRenderSettings`  
`class UMovieGraphQuickRenderSettings : public UObject`  
_L82-113_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Data that specifies user-configurable aspects of a quick render. Settings are stored for each mode separately.
- L87 _public prototype_ `UMovieGraphQuickRenderSettings() = default;`
- L91 _public prototype_ `static UMovieGraphQuickRenderModeSettings* GetSavedQuickRenderModeSettings(EMovieGraphQuickRenderMode SettingsMode);` — `UFUNCTION(BlueprintCallable, Category="Quick Render")` — Gets the Quick Render settings (for a specific mode) that have been persisted to disk (Saved/MovieRenderPipeline/QuickRenderSettings.uasset).
- L94 _private member_ `inline static const FString QuickRenderSettingsPackagePath = TEXT("/Te`
- L95 _private member_ `inline static FDelegateHandle OnEnginePreExitHandle;`
- L102 _private member_ `TMap<FName, TObjectPtr<UMovieGraphQuickRenderModeSettings>> ModeSettings;` — `UPROPERTY()` — Individual settings for each mode. Some modes have shared settings, hence why this is keyed by FName (an internal identifier) instead of the mode enum.
- L107 _private prototype_ `static void SaveSettings(const UMovieGraphQuickRenderSettings* InSettings);` — Saves the settings to a uasset file (Saved/MovieRenderPipeline/QuickRenderSettings.uasset). The file will be created if it doesn't exist.
- L111 _private prototype_ `void NotifyNeedsSave();`

#### class `UMovieGraphQuickRenderModeSettings`  
`class UMovieGraphQuickRenderModeSettings : public UObject`  
_L117-195_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Settings for a specific mode within Quick Render. Note that some modes share settings.
- L122 _public prototype_ `UMovieGraphQuickRenderModeSettings();`
- L130 _public prototype_ `static void RefreshVariableAssignments(UMovieGraphQuickRenderModeSettings* InSettings);` — `UFUNCTION(BlueprintCallable, Category="Quick Render")` — Within the settings object provided, refreshes the variable assignments in the settings to match the setting's GraphPreset. Note that changing the graph preset within the editor will do this automatically, but if changing the graph outside of the editor, this may need to be run manually.
- L139 _public prototype_ `UMovieJobVariableAssignmentContainer* GetVariableAssignmentsForGraph(const TSoftObjectPtr<UMovieGraphConfig>& InGraphConfigPath) const;` — `UFUNCTION(BlueprintCallable, Category="Quick Render")` — Gets the variable assignments for the specified graph asset. Note that there will normally only be one variable assignment container for these quick render settings (the assignments for the graph specified in `GraphPreset`). However, `GraphPreset` may have subgraphs, and subgraphs store their variable assignments in separate containers. If you need to update the variable assignments for those subgraph(s), this method provides a convenient way of getting their assignments (instead of iterating through `GraphVariableAssignments`).
- L142 _public member_ `FOnMovieGraphQuickRenderGraphChanged OnGraphChangedDelegate;`
- L147 _public member_ `TSoftObjectPtr<UMovieGraphConfig> GraphPreset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Configuration", DisplayName="Movie Render Graph Config")` — The graph preset that is used to configure the render. If not specified, the quick render default graph will be used.
- L155 _public member_ `TSoftObjectPtr<class ULevelSequence> LevelSequenceOverride = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category="Configuration")` — If this override is set, this sequence will be used instead of the level sequence that's active in Sequencer. In UI-based Quick Render, this property is never set directly because Sequencer is always used. However, for scripting purposes, there may be cases where Sequencer is not open, and a specific level sequence needs to be used.
- L159 _public member_ `EMoviePipelinePostRenderActionType PostRenderBehavior = EMoviePipelinePostRenderActionType::PlayRenderOutput;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Configuration", DisplayName="After Render")` — The action that quick render should perform after a render is finished.
- L163 _public member_ `bool bOverride_ViewportLookFlags = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quick Render", meta=(InlineEditConditionToggle))` — Enables/disables the ViewportLookFlags property from taking effect.
- L170 _public member_ `int32 ViewportLookFlags = static_cast<int32>(EMovieGraphQuickRenderViewportLookFlags::None);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quick Render", DisplayName="Apply Viewport Look", meta=(EditCondition="bOverride_ViewportLookFlags", Bitmask, BitmaskEnum="/Script/MovieRenderPipelineCore.EMovieGraphQuickRenderViewportLookFlags"))` — The properties of the viewport that should be applied to the quick render. These will override any equivalent properties specified in the graph.
- L174 _public member_ `EMovieGraphQuickRenderFrameRangeType FrameRangeType = EMovieGraphQuickRenderFrameRangeType::PlaybackRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quick Render", DisplayName="Sequencer Frame Range")` — The frame range that should be used to render from. Not applicable to modes that only render stills.
- L178 _public member_ `int32 CustomStartFrame = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quick Render", meta=(EditCondition="FrameRangeType == EMovieGraphQuickRenderFrameRangeType::Custom", EditConditionHides))` — The frame in the level sequence that the render will begin on. This frame number is inclusive, meaning that this frame will be included in the rendered frames.
- L182 _public member_ `int32 CustomEndFrame = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quick Render", meta=(EditCondition="FrameRangeType == EMovieGraphQuickRenderFrameRangeType::Custom", EditConditionHides))` — The frame in the level sequence that the render will end on. This frame number is exclusive, meaning that the rendered frames will include the frames up until (but excluding) this frame.
- L186 _public member_ `TArray<TObjectPtr<UMovieJobVariableAssignmentContainer>> GraphVariableAssignments;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Primary Graph Variables")` — Values that are set on the variables contained within the graph preset. See note on RefreshVariableAssignments().
- L191 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L192 _private prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L61 _typedef_ `typedef EMoviePipelinePostRenderActionType EMovieGraphQuickRenderPostRenderActionType;` — `UE_DEPRECATED(5.8, "Use EMoviePipelinePostRenderActionType instead")`
- L77 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMovieGraphQuickRenderGraphChanged);`
- L77 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMovieGraphQuickRenderGraphChanged);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphRenderCameraSource.h` (Public)


#### struct `FMovieGraphRenderCameraSource`  
`struct FMovieGraphRenderCameraSource`  
_L20-104_
- desc: Base class for a custom camera source created by a live UMovieGraphRenderPassNode instance (not the class default object). Supplies a set of cameras that replaces the cameras from the data source for the render pass node that created it.
- L22 _public prototype_ `virtual ~FMovieGraphRenderCameraSource() = default;`
- L31 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector)` — Adds any UObject references held by this source to the collector for GC tracking. Subclasses that hold UObject pointers must override this to prevent those objects from being garbage collected while the source is alive. @param Collector (in) The reference collector provided by the GC system.
- L39 _public function_ `virtual void OnBeginFrame(const UMovieGraphPipeline* InMoviePipeline, const FMovieGraphTimeStepData* InTimeData)` — Called once per frame to prepare the source for a new frame. Must be called before querying camera data. @param InMoviePipeline (in) The pipeline currently being evaluated. @param InTimeData      (in) Time step data for the current frame (frame time, delta time, etc.).
- L42 _public function_ `virtual int32 GetNumCameras() const` — Returns the number of cameras this source contributes for the current shot.
- L52 _public function_ `virtual bool GetCameraName(const int32 InCameraIndex, FString& OutCameraName) const` — Returns the unique camera name for the given camera index. Used by the renderer for the {camera_name} output token. @param InCameraIndex (in)  Index in range [0, NumCameras). @param OutCameraName (out) Receives the camera name for the requested index. @return              True if resolved; false to fall back to the shot's camera name.
- L62 _public function_ `virtual bool GetCameraViewActor(const int32 InCameraIndex, AActor*& OutCameraActor) const` — Returns the view actor for the specified camera index. Returning true with OutCameraActor = nullptr is valid and suppresses the default fallback. @param InCameraIndex  (in)  Index in range [0, NumCameras). @param OutCameraActor (out) Receives the actor used as the view origin, or nullptr. @return               True if the source handled this query; false to fall back to the player controller's view target.
- L71 _public function_ `virtual bool GetCameraOverscan(const int32 InCameraIndex, float& OutCameraOverscan) const` — Gets the overscan value for the specified camera. @param InCameraIndex     (in)  Index in range [0, NumCameras). @param OutCameraOverscan (out) Receives the overscan value for the camera. @return                  True if resolved; false to fall back to the default sequence camera overscan.
- L80 _public function_ `virtual bool GetCameraViewInfo(const int32 InCameraIndex, FMinimalViewInfo& OutViewInfo) const` — Returns the view info for the specified camera index. @param InCameraIndex (in)  Index in range [0, NumCameras). @param OutViewInfo   (out) Receives the view transform, FOV, and other camera parameters. @return              True if resolved; false to fall back to the primary sequence camera.
- L88 _public function_ `virtual void SetupCameraViewProjectionData(const int32 InCameraIndex, FSceneViewProjectionData& InOutProjectionData) const` — Applies camera-specific adjustments to the projection data after it has been computed. @param InCameraIndex       (in)     Index in range [0, NumCameras). @param InOutProjectionData (in,out) Projection data to adjust; already populated by the time this is called.
- L99 _public function_ `virtual bool GetCameraOverscannedResolution( const int32 InCameraIndex, FIntPoint& InOutOverscannedResolution, FIntRect& InOutOverscanCropRectangle, float& InOutOverscanFraction) const` — Returns the overscanned resolution and inner crop rectangle for the specified camera. @param InCameraIndex              (in)  Index in range [0, NumCameras). @param InOutOverscannedResolution (in,out) Receives the overscanned resolution. @param InOutOverscanCropRectangle (in,out) Receives the inner crop rectangle within the overscanned resolution. @param InOutOverscanFraction      (in,out) The final per-side overscan fraction [0..1] for this camera. @return                           True if resolved; false to fall back to the default resolution calculation.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphRenderDataIdentifier.h` (Public)


#### struct `FMovieGraphRenderDataIdentifier`  
`struct FMovieGraphRenderDataIdentifier`  
_L13-93_
- reflection: `USTRUCT(BlueprintType)`
- desc: This data structure can be used to identify what render data a set of pixels represents by knowing what the render layer name is, what renderer produced it, if it's a sub-resource, and what camera it is for. Can be used as the key in a TMap.
- L17 _public function_ `FMovieGraphRenderDataIdentifier()`
- L20 _public function_ `FMovieGraphRenderDataIdentifier(const FName& InRootBranchName, const FString& InLayerName, const FString& InRendererName, const FString& InSubRenderResourceName, const FString& InCameraName) : RootBranchName(InRootBranchName) , LayerName(InLayerName) , RendererName(InRendererName) , SubResourceName(InSubRenderResourceName) , CameraName(InCameraName)`
- L30 _public function_ `bool operator == (const FMovieGraphRenderDataIdentifier& InRHS) const`
- L39 _public function_ `bool operator != (const FMovieGraphRenderDataIdentifier& InRHS) const`
- L58 _public function_ `bool IsBranchAndCameraEqual(const FMovieGraphRenderDataIdentifier& InIdentifier) const`
- L71 _public member_ `FName RootBranchName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Graph")` — The root branch name from the Outputs node that this identifier is for. This is useful to know which branch it came from, as RenderLayer is user-defined and can be redefined multiple times within one graph.
- L80 _public member_ `FString LayerName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Graph")` — The Render Layer name (as defined by the "Render Layer" node.). This is effectively a "display" name for identifiers. If there is no Render Layer node then this will be the RootBranchName (so that the {render_layer} token works in the case of data from things on the Globals branch).
- L84 _public member_ `FString RendererName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Graph")` — Which renderer was used to produce this image ("panoramic" "deferred" "path tracer", etc.)
- L88 _public member_ `FString SubResourceName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Graph")` — A sub-resource name for the renderer (ie: "beauty", "object id", "depth", etc.)
- L92 _public member_ `FString CameraName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Graph")` — The name of the camera being used for this render.

#### struct `FMovieGraphStringArray`  
`struct FMovieGraphStringArray`  
_L97-103_
- reflection: `USTRUCT(BlueprintType)`
- desc: A simple struct wrapper around a string array so it can be included in a TMap.
- L102 _public member_ `TArray<FString> Array;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")`

#### struct `FMovieGraphRenderLayerOutputData`  
`struct FMovieGraphRenderLayerOutputData`  
_L106-129_
- reflection: `USTRUCT(BlueprintType)`
- L112 _public member_ `TArray<FString> FilePaths;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")` — A list of file paths on disk (in order) that were generated for this particular render pass.
- L120 _public member_ `TArray<FString> FrameTemplatedFilePaths;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")` — The "frame templated" file paths. This groups together a set of output frames by frame number, eg "Seq.Shot.{frame_placeholder}.exr". If the render layer has more than one output type in it (eg, EXR and JPEG), there may be more than one path here, but there should only be one per output type.
- L124 _public member_ `TMap<FSoftClassPath, FMovieGraphStringArray> NodeTypeToFilePaths;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")` — Maps a node type to all of the files that the node type generated.
- L128 _public member_ `int32 RenderLayerIndex = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")` — The index of the render layer these files belong to. Index 0 is the first render layer rendered, and so on.

#### struct `FMovieGraphRenderOutputData`  
`struct FMovieGraphRenderOutputData`  
_L132-146_
- reflection: `USTRUCT(BlueprintType)`
- L138 _public member_ `TWeakObjectPtr<class UMoviePipelineExecutorShot> Shot;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Graph")` — Which shot is this output data for.
- L145 _public member_ `TMap<FMovieGraphRenderDataIdentifier, FMovieGraphRenderLayerOutputData> RenderLayerData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Graph")` — A mapping between render layers (such as "beauty") and an array containing the files written for that shot. Will be multiple files if using image sequences.

#### Free symbols / members of external scopes

- L44 _function_ `friend uint32 GetTypeHash(FMovieGraphRenderDataIdentifier InIdentifier)`
- L53 _function_ `friend FString LexToString(const FMovieGraphRenderDataIdentifier InIdentifier)`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphRenderLayerSubsystem.h` (Public)


#### enum `EMovieGraphConditionGroupOpType`  
`enum class EMovieGraphConditionGroupOpType : uint8`  
_L22-32_
- reflection: `UENUM(BlueprintType)`
- desc: Operation types available on condition groups.
- L25 _public enumerator_ `Add` — Adds the contents of the condition group to the results from the previous condition group (if any).
- L28 _public enumerator_ `Subtract` — Removes the contents of the condition group from the result of the previous condition group (if any). Any items in this condition group that aren't also found in the previous condition group will be ignored.
- L31 _public enumerator_ `And` — Replaces the results of the previous condition group(s) with only the elements that exist in both that group, and this group. Intersecting with an empty condition group will result in an empty condition group.

#### enum `EMovieGraphConditionGroupQueryOpType`  
`enum class EMovieGraphConditionGroupQueryOpType : uint8`  
_L36-46_
- reflection: `UENUM(BlueprintType)`
- desc: Operation types available on condition group queries.
- L39 _public enumerator_ `Add` — Adds the results of the query to the results from the previous query (if any).
- L42 _public enumerator_ `Subtract` — Removes the results of the query from the results of the previous query (if any). Any items in this query result that aren't also found in the previous query result will be ignored.
- L45 _public enumerator_ `And` — Replaces the results of the previous queries with only the items that exist in both those queries, and this query result. Intersecting with a query which returns nothing will create an empty query result.

#### class `UMovieGraphConditionGroupQueryBase`  
`class UMovieGraphConditionGroupQueryBase : public UObject`  
_L50-169_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Base class that all condition group queries must inherit from.
- L55 _public prototype_ `UMovieGraphConditionGroupQueryBase();`
- L58 _public prototype_ `DECLARE_DELEGATE(FMovieGraphConditionGroupQueryContentsChanged) UFUNCTION(BlueprintCallable, Category = "Settings") void SetOperationType(const EMovieGraphConditionGroupQueryOpType OperationType);` — Delegate which is called when the contents of a query has changed.
- L69 _public prototype_ `EMovieGraphConditionGroupQueryOpType GetOperationType() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Gets the condition group query operation type.
- L77 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Determines which of the provided actors (in the given world) match the query. Matches are added to OutMatchingActors. Note that this method will not be called if ShouldEvaluateComponents() returns true; EvaluateActorsAndComponents() will be called instead.
- L84 _public prototype_ `virtual void EvaluateActorsAndComponents(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors, TSet<UActorComponent*>& OutMatchingComponents) const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Similar to Evaluate(), but returns both actors and components if the query can match both. Note that this method will only be called if ShouldEvaluateComponents() returns true.
- L93 _public prototype_ `virtual bool ShouldHidePropertyNames() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Determines if the public properties on the query class will have their names hidden in the details panel. Returns false by default. Most query subclasses will only have one property and do not need to clutter the UI with the property name (eg, the "Actor Name" query only shows one text box with entries for the actor names, no need to show the property name).
- L100 _public prototype_ `virtual bool ShouldEvaluateComponents() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Determines if this query should additionally match components, rather than just matching actors. Off by default. If this returns true, then EvaluateActorsAndComponents() will be called during evaluation instead of Evaluate().
- L103 _public prototype_ `virtual const FSlateIcon& GetIcon() const;` — Gets the icon that represents this query class in the UI.
- L106 _public prototype_ `virtual const FText& GetDisplayName() const;` — Gets the display name for this query class as shown in the UI.
- L113 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets();` — Gets the widgets that should be displayed for this query. If no custom widgets are specified (returning an empty array), the default name/value widgets will be shown for all query properties tagged with EditAnywhere.
- L120 _public prototype_ `virtual bool HasAddMenu() const;` — Returns true if this query should expose an Add menu, or false if no Add menu is visible. @see GetAddMenuContents()
- L129 _public prototype_ `virtual TSharedRef<SWidget> GetAddMenuContents(const FMovieGraphConditionGroupQueryContentsChanged& OnAddFinished);` — Gets the contents of the "Add" menu in the UI, if any. When the Add menu updates properties within the query, OnAddFinished should be called in order to give the UI a chance to update itself. Note that HasAddMenu() must return true in order for the contents returned from this method to be displayed in the UI. @see HasAddMenu()
- L134 _public prototype_ `virtual bool IsEditorOnlyQuery() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Determines if this query is only respected when run within the editor. Used for providing a UI hint.
- L138 _public prototype_ `void SetEnabled(const bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Sets whether this query is enabled.
- L142 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Determines if this query is enabled.
- L146 _public prototype_ `bool IsFirstConditionGroupQuery() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Determines if this is the first condition group query under the parent condition group.
- L154 _protected prototype_ `static AActor* GetActorForCurrentWorld(AActor* InActorToConvert);` — `UE_DEPRECATED(5.8, "Use GetActorForCurrentWorld(AActor*, const UWorld*) when an evaluation/render world is available.")` — Utility that returns the given actor in the current world. If currently in PIE, converts editor actors to PIE actors, and vice-versa. If no conversion is needed, returns the provided actor as-is.
- L159 _protected prototype_ `static AActor* GetActorForCurrentWorld(AActor* InActorToConvert, const UWorld* InTargetWorld);` — Utility that returns the given actor in the specified target world. This avoids relying on editor globals, which may be unavailable in remote renders.
- L164 _private member_ `EMovieGraphConditionGroupQueryOpType OpType;` — `UPROPERTY()` — The operation type that the query is using.
- L168 _private member_ `bool bIsEnabled;` — `UPROPERTY()` — Whether this query is currently enabled within the condition group.

#### struct `FMovieGraphActorQueryEntry`  
`struct FMovieGraphActorQueryEntry`  
_L173-189_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains the actors and components to match within the Actor condition group query.
- L177 _public prototype_ `bool operator==(const FMovieGraphActorQueryEntry& InOther) const;`
- L184 _public member_ `TSoftObjectPtr<AActor> ActorToMatch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")` — The query must match this actor in order to be a match. If these are editor actors, they will be converted to PIE actors automatically. If there are any ComponentsToMatch, they must be part of this actor.
- L188 _public member_ `TArray<TSoftObjectPtr<UActorComponent>> ComponentsToMatch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")` — The query must match these components in order to be a match. These must be contained within ActorToMatch.

#### class `UMovieGraphConditionGroupQuery_Actor`  
`class UMovieGraphConditionGroupQuery_Actor final : public UMovieGraphConditionGroupQueryBase`  
_L193-289_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors via an explicit actor list.
- L198 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L199 _public prototype_ `virtual void EvaluateActorsAndComponents(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors, TSet<UActorComponent*>& OutMatchingComponents) const override;`
- L200 _public prototype_ `virtual bool ShouldEvaluateComponents() const override;`
- L201 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L202 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L205 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L206 _public prototype_ `virtual bool HasAddMenu() const override;`
- L207 _public prototype_ `virtual TSharedRef<SWidget> GetAddMenuContents(const FMovieGraphConditionGroupQueryContentsChanged& OnAddFinished) override;`
- L210 _public prototype_ `virtual void PostLoad() override;`
- L215 _private prototype_ `void AddActors(const TArray<AActor*>& InActors, const FMovieGraphConditionGroupQueryContentsChanged& InOnAddFinished, const bool bCloseAddMenu = true);` — Adds the provided actors to the query, updating the UI as needed. Calls InOnAddFinished when done. Can optionally close the Add menu.
- L218 _private prototype_ `void RemoveEntries(const TArray<FMovieGraphActorQueryEntry>& InEntries);` — Removes the provided entries from the query, updating the UI as needed.
- L221 _private prototype_ `void GetListContextMenu(FMenuBuilder& InMenuBuilder, TArray<TSharedPtr<FMovieGraphActorQueryEntry>> SelectedEntries);` — Gets the context menu for an entry in the list widget.
- L224 _private prototype_ `void RefreshListDataSource();` — Refreshes the list's data source to reflect the data model.
- L231 _public member_ `TArray<TSoftObjectPtr<AActor>> ActorsToMatch;` — `UE_DEPRECATED(5.6, "This property is deprecated. Please use ActorsAndComponentsToMatch instead.")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="This property is deprecated. Please use ActorsAndComponentsToMatch instead."))` — The query must match one of the actors in order to be a match. If these are editor actors, they will be converted to PIE actors automatically.
- L235 _public member_ `TArray<FMovieGraphActorQueryEntry> ActorsAndComponentsToMatch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="General")` — The query must match one of the actors (or components on an actor) to be a match. If these are editor actors, they will be converted to PIE actors automatically.
- L264 _private member_ `static const inline FName ColumnID_ActorName = FName(TEXT("Acto`
- L265 _private member_ `static const inline FName ColumnID_ActorType = FName(TEXT("Acto`
- L266 _private member_ `static const inline FName ColumnID_Components = FName(TEXT("Comp`
- L280 _private member_ `TSharedPtr<class ISceneOutliner> ActorPickerWidget;`
- L283 _private member_ `TSharedPtr<SMovieGraphSimpleList<TSharedPtr<FMovieGraphActorQueryEntry>>> ActorsList;` — Displays the actors which have been chosen.
- L287 _private member_ `TArray<TSharedPtr<FMovieGraphActorQueryEntry>> ListDataSource;` — Not ideal to store a duplicate of ActorsToMatch, but SListView requires TSharedPtr<...> as the data source, and UPROPERTY does not support TSharedPtr<...>

#### class `UMovieGraphConditionGroupQuery_Actor::FActorSelectionColumn`  
`class FActorSelectionColumn final : public ISceneOutlinerColumn`  
_L240-262_
- inherits: `ISceneOutlinerColumn`
- desc: Custom outliner column that allows adding/removing an actor from an Actor condition group query (via checkbox).
- L243 _public function_ `explicit FActorSelectionColumn(const TWeakObjectPtr<UMovieGraphConditionGroupQuery_Actor> InWeakActorQuery) : WeakActorQuery(InWeakActorQuery)`
- L247 _public prototype_ `static FName GetID();`
- L248 _public prototype_ `virtual FName GetColumnID() override;`
- L249 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L250 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L254 _private prototype_ `ECheckBoxState IsRowChecked(const FActorTreeItem* InActorTreeItem) const;` — Determines if the given tree item (corresponding to one actor) is checked.
- L257 _private prototype_ `void OnCheckStateChanged(const ECheckBoxState NewState, const FActorTreeItem* InActorTreeItem) const;` — Updates the associated actor query when a row is checked or unchecked.
- L261 _private member_ `TWeakObjectPtr<UMovieGraphConditionGroupQuery_Actor> WeakActorQuery;` — The Actor condition group query that populates the data for this column.

#### class `UMovieGraphConditionGroupQuery_Actor::SActorListRow`  
`class SActorListRow final : public SMultiColumnTableRow<TSharedPtr<FMovieGraphActorQueryEntry>>`  
_L269-278_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMovieGraphActorQueryEntry>>`
- desc: Custom row widget for the actor list so multiple columns can be populated.
- L272 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedPtr<FMovieGraphActorQueryEntry> InEntry);`
- L274 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L277 _private member_ `TWeakPtr<FMovieGraphActorQueryEntry> WeakEntry;`

#### class `UMovieGraphConditionGroupQuery_ActorTagName`  
`class UMovieGraphConditionGroupQuery_ActorTagName final : public UMovieGraphConditionGroupQueryBase`  
_L293-322_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors via tags on actors.
- L298 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L299 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L300 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L303 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L321 _public member_ `FString TagsToMatch;` — `UPROPERTY(EditAnywhere, Category="General")` — Tags on the actor must match one or more of the specified tags to be a match. Not case sensitive. One tag per line. Wildcards ("?" and "*") are supported but not required. The "*" wildcard matches zero or more characters, and "?" matches exactly one character (and that character must be present). Wildcard examples: Foo* would match Foo, FooBar, and FooBaz, but not BarFoo. *Foo* would match the above in addition to BarFoo. Foo?Bar would match Foo.Bar and Foo_Bar, but not FooBar. Foo? would match Food, but not FooBar or BarFoo. Foo??? would match FooBar and FooBaz, but not Foo or Food. ?oo? would match Food, but not Foo. ?Foo* would match AFooBar, but not FooBar

#### class `UMovieGraphConditionGroupQuery_ActorName`  
`class UMovieGraphConditionGroupQuery_ActorName final : public UMovieGraphConditionGroupQueryBase`  
_L326-357_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors via their name (label).
- L331 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L332 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L333 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L336 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L339 _public prototype_ `virtual bool IsEditorOnly() const override;`
- L356 _public member_ `FString WildcardSearch;` — `UPROPERTY(EditAnywhere, Category="General")` — The name that the actor needs to have in order to be a match. Not case sensitive. One name per line. Wildcards ("?" and "*") are supported but not required. The "*" wildcard matches zero or more characters, and "?" matches exactly one character (and that character must be present). Wildcard examples: Foo* would match Foo, FooBar, and FooBaz, but not BarFoo. *Foo* would match the above in addition to BarFoo. Foo?Bar would match Foo.Bar and Foo_Bar, but not FooBar. Foo? would match Food, but not FooBar or BarFoo. Foo??? would match FooBar and FooBaz, but not Foo or Food. ?oo? would match Food, but not Foo. ?Foo* would match AFooBar, but not FooBar

#### class `UMovieGraphConditionGroupQuery_ActorType`  
`class UMovieGraphConditionGroupQuery_ActorType final : public UMovieGraphConditionGroupQueryBase`  
_L361-395_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors by type.
- L366 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L367 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L368 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L371 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L372 _public prototype_ `virtual bool HasAddMenu() const override;`
- L373 _public prototype_ `virtual TSharedRef<SWidget> GetAddMenuContents(const FMovieGraphConditionGroupQueryContentsChanged& OnAddFinished) override;`
- L379 _public member_ `TArray<TObjectPtr<UClass>> ActorTypes;` — `UPROPERTY(EditAnywhere, Category="General")` — The type (class) that the actor needs to have in order to be a match.
- L383 _private prototype_ `static const FSlateBrush* GetRowIcon(TObjectPtr<UClass> InActorType);`
- L384 _private prototype_ `static FText GetRowText(TObjectPtr<UClass> InActorType);`
- L387 _private prototype_ `void AddActorTypes(const TArray<UClass*>& InActorTypes, const FMovieGraphConditionGroupQueryContentsChanged& InOnAddFinished);` — Adds the provided actor types to the query, updating the UI as needed. Calls InOnAddFinished when done.
- L390 _private member_ `TSharedPtr<SMovieGraphSimpleList<TObjectPtr<UClass>>> ActorTypesList;` — Displays the actor types which have been chosen.
- L394 _private member_ `TSharedPtr<class SClassViewer> ClassViewerWidget;` — The class viewer widget to show in the Add menu.

#### class `UMovieGraphConditionGroupQuery_LightActorType`  
`class UMovieGraphConditionGroupQuery_LightActorType final : public UMovieGraphConditionGroupQueryBase`  
_L399-441_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors by light type.
- L404 _public prototype_ `UMovieGraphConditionGroupQuery_LightActorType();`
- L406 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L407 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L408 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L411 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L419 _public prototype_ `void SetEnableStateForLightType(UClass* InLightActorType, const bool bNewEnableState);` — `UFUNCTION(BlueprintCallable, Category = "Lights")` — Sets the enable state for the given light actor type. All enabled light types will be matched by the query. If the given actor type isn't one of the supported light types, this does nothing.
- L423 _public prototype_ `bool GetEnableStateForLightType(UClass* InLightActorType);` — `UFUNCTION(BlueprintCallable, Category = "Lights")` — Gets the enable state for the given light actor type. If the provided type isn't a supported light type, returns false.
- L428 _private member_ `TArray<TObjectPtr<UClass>> EnabledLightActorTypes;` — `UPROPERTY()` — The light types that are enabled (and will be matched by the query).
- L432 _private prototype_ `static TArray<UClass*>* GetSupportedLightActorTypes();` — Gets the supported light actor types.
- L435 _private prototype_ `static const FSlateBrush* GetRowIcon(UClass* InLightActorType);`
- L436 _private prototype_ `static FText GetRowText(UClass* InLightActorType);`
- L439 _private member_ `TSharedPtr<SMovieGraphSimpleList<UClass*>> LightActorTypesList;` — The list widget which displays the light actor types and their enable/disable state.

#### class `UMovieGraphConditionGroupQuery_ComponentTagName`  
`class UMovieGraphConditionGroupQuery_ComponentTagName final : public UMovieGraphConditionGroupQueryBase`  
_L445-486_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors by tags on their components.
- L450 _public prototype_ `UMovieGraphConditionGroupQuery_ComponentTagName();`
- L452 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L453 _public prototype_ `virtual void EvaluateActorsAndComponents(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors, TSet<UActorComponent*>& OutMatchingComponents) const override;`
- L454 _public prototype_ `virtual bool ShouldEvaluateComponents() const override;`
- L455 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L456 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L459 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L463 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L481 _public member_ `FString TagsToMatch;` — `UPROPERTY(EditAnywhere, Category="General")` — A component on the actor must have one or more of the specified tags to be a match. Not case sensitive. One tag per line. Wildcards ("?" and "*") are supported but not required. The "*" wildcard matches zero or more characters, and "?" matches exactly one character (and that character must be present). Wildcard examples: Foo* would match Foo, FooBar, and FooBaz, but not BarFoo. *Foo* would match the above in addition to BarFoo. Foo?Bar would match Foo.Bar and Foo_Bar, but not FooBar. Foo? would match Food, but not FooBar or BarFoo. Foo??? would match FooBar and FooBaz, but not Foo or Food. ?oo? would match Food, but not Foo. ?Foo* would match AFooBar, but not FooBar
- L485 _public member_ `bool bOnlyMatchComponents;` — `UPROPERTY(EditAnywhere, Category="General")` — Whether this should match components or actors. If false, any components that match will instead match their parent actor.

#### class `UMovieGraphConditionGroupQuery_ComponentType`  
`class UMovieGraphConditionGroupQuery_ComponentType final : public UMovieGraphConditionGroupQueryBase`  
_L490-533_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors via the component types contained in them.
- L495 _public prototype_ `UMovieGraphConditionGroupQuery_ComponentType();`
- L497 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L498 _public prototype_ `virtual void EvaluateActorsAndComponents(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors, TSet<UActorComponent*>& OutMatchingComponents) const override;`
- L499 _public prototype_ `virtual bool ShouldEvaluateComponents() const override;`
- L500 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L501 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L504 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L505 _public prototype_ `virtual bool HasAddMenu() const override;`
- L506 _public prototype_ `virtual TSharedRef<SWidget> GetAddMenuContents(const FMovieGraphConditionGroupQueryContentsChanged& OnAddFinished) override;`
- L510 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L515 _private prototype_ `static const FSlateBrush* GetRowIcon(TObjectPtr<UClass> InComponentType);`
- L516 _private prototype_ `static FText GetRowText(TObjectPtr<UClass> InComponentType);`
- L519 _private member_ `TSharedPtr<SMovieGraphSimpleList<TObjectPtr<UClass>>> ComponentTypesList;` — Displays the component types which have been chosen.
- L523 _private member_ `TSharedPtr<class SClassViewer> ClassViewerWidget;` — The class viewer widget to show in the Add menu.
- L528 _public member_ `TArray<TObjectPtr<UClass>> ComponentTypes;` — `UPROPERTY(EditAnywhere, Category="General")` — The actor must have one or more of the component type(s) in order to be a match.
- L532 _public member_ `bool bOnlyMatchComponents;` — `UPROPERTY(EditAnywhere, Category="General")` — Whether this should match components or actors. If false, any components that match will instead match their parent actor.

#### class `UMovieGraphConditionGroupQuery_ComponentName`  
`class UMovieGraphConditionGroupQuery_ComponentName final : public UMovieGraphConditionGroupQueryBase`  
_L537-562_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors via the components contained in them (by name).
- L542 _public prototype_ `UMovieGraphConditionGroupQuery_ComponentName();`
- L544 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L545 _public prototype_ `virtual void EvaluateActorsAndComponents(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors, TSet<UActorComponent*>& OutMatchingComponents) const override;`
- L546 _public prototype_ `virtual bool ShouldEvaluateComponents() const override;`
- L547 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L548 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L551 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L557 _public member_ `FString ComponentNames;` — `UPROPERTY(EditAnywhere, Category="General")` — The actor must have one or more of the component name(s) in order to be a match.
- L561 _public member_ `bool bOnlyMatchComponents;` — `UPROPERTY(EditAnywhere, Category="General")` — Whether this should match components or actors. If false, any components that match will instead match their parent actor.

#### class `UMovieGraphConditionGroupQuery_EditorFolder`  
`class UMovieGraphConditionGroupQuery_EditorFolder final : public UMovieGraphConditionGroupQueryBase`  
_L566-601_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors via the editor folder that they're contained in.
- L571 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L572 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L573 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L574 _public prototype_ `virtual bool IsEditorOnlyQuery() const override;`
- L577 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L578 _public prototype_ `virtual bool HasAddMenu() const override;`
- L579 _public prototype_ `virtual TSharedRef<SWidget> GetAddMenuContents(const FMovieGraphConditionGroupQueryContentsChanged& OnAddFinished) override;`
- L584 _private prototype_ `static const FSlateBrush* GetRowIcon(FName InFolderPath);`
- L585 _private prototype_ `static FText GetRowText(FName InFolderPath);`
- L588 _private prototype_ `void AddFolders(const TArray<FName>& InFolderPaths, const FMovieGraphConditionGroupQueryContentsChanged& InOnAddFinished);` — Adds the provided folders to the query, updating the UI as needed. Calls InOnAddFinished when done.
- L591 _private member_ `TSharedPtr<SMovieGraphSimpleList<FName>> FolderPathsList;` — Displays the paths of folders which have been chosen.
- L594 _private member_ `TSharedPtr<class ISceneOutliner> FolderPickerWidget;` — The folder browser widget to show in the Add menu.
- L600 _public member_ `TArray<FName> FolderPaths;` — `UPROPERTY(EditAnywhere, Category="General")` — The actor must be in one of the chosen folders in order to be a match.

#### class `UMovieGraphConditionGroupQuery_Sublevel`  
`class UMovieGraphConditionGroupQuery_Sublevel final : public UMovieGraphConditionGroupQueryBase`  
_L605-656_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors via the sublevel that they're contained in.
- L610 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L611 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L612 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L615 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L616 _public prototype_ `virtual bool HasAddMenu() const override;`
- L617 _public prototype_ `virtual TSharedRef<SWidget> GetAddMenuContents(const FMovieGraphConditionGroupQueryContentsChanged& OnAddFinished) override;`
- L622 _private prototype_ `static const FSlateBrush* GetRowIcon(TSharedPtr<TSoftObjectPtr<UWorld>> InSublevel);`
- L623 _private prototype_ `static FText GetRowText(TSharedPtr<TSoftObjectPtr<UWorld>> InSublevel);`
- L624 _private prototype_ `static bool IsSublevelInActivePersistentLevel(FName InSublevelPackageName);`
- L627 _private prototype_ `void AddLevels(const TArray<UWorld*>& InLevels, const FMovieGraphConditionGroupQueryContentsChanged& InOnAddFinished);` — Adds the provided levels to the query, updating the UI as needed. Calls InOnAddFinished when done.
- L630 _private prototype_ `void RefreshListDataSource();` — Refreshes the list's data source to reflect the data model.
- L633 _private member_ `TSharedPtr<SMovieGraphSimpleList<TSharedPtr<TSoftObjectPtr<UWorld>>>> SublevelsList;` — Displays the names of sublevels which have been chosen.
- L636 _private member_ `FRefreshAssetViewDelegate RefreshLevelPicker;` — Refreshes the contents of the level picker widget when called.
- L640 _private member_ `TArray<TSharedPtr<TSoftObjectPtr<UWorld>>> ListDataSource;` — Not ideal to store a duplicate of Sublevels, but SListView requires TSharedPtr<...> as the data source, and UPROPERTY does not support TSharedPtr<...>
- L649 _private member_ `bool bOnlyShowSublevelsFromActivePersistentLevel = true;` — `UPROPERTY()` — Whether the add menu should only show sublevels from the active persistent level. The value is persisted with the query, but only impacts how the UI is filtered.
- L655 _public member_ `TArray<TSoftObjectPtr<UWorld>> Sublevels;` — `UPROPERTY(EditAnywhere, Category="General")` — The actor must be in one of the chosen sublevels in order to be a match.

#### class `UMovieGraphConditionGroupQuery_ActorLayer`  
`class UMovieGraphConditionGroupQuery_ActorLayer final : public UMovieGraphConditionGroupQueryBase`  
_L660-695_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors via Actor Layers.
- L665 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L666 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L667 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L668 _public prototype_ `virtual bool IsEditorOnly() const override;`
- L671 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L672 _public prototype_ `virtual bool HasAddMenu() const override;`
- L673 _public prototype_ `virtual TSharedRef<SWidget> GetAddMenuContents(const FMovieGraphConditionGroupQueryContentsChanged& OnAddFinished) override;`
- L678 _private prototype_ `static const FSlateBrush* GetRowIcon(FName InLayerName);`
- L679 _private prototype_ `static FText GetRowText(FName InLayerName);`
- L682 _private prototype_ `void AddActorLayers(const TArray<FName>& InActorLayers, const FMovieGraphConditionGroupQueryContentsChanged& InOnAddFinished);` — Adds the provided actor layers to the query, updating the UI as needed. Calls InOnAddFinished when done.
- L685 _private member_ `TSharedPtr<SMovieGraphSimpleList<FName>> LayerNamesList;` — Displays the layers which have been chosen.
- L688 _private member_ `TArray<FName> LayerPickerDataSource;` — The data source for the layer picker widget (contains all layers which are available and not yet picked).
- L694 _public member_ `TArray<FName> LayerNames;` — `UPROPERTY(EditAnywhere, Category="General")` — The actor must be in one of the actor layers with these names in order to be a match.

#### class `UMovieGraphConditionGroupQuery_DataLayer`  
`class UMovieGraphConditionGroupQuery_DataLayer final : public UMovieGraphConditionGroupQueryBase`  
_L699-740_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors via World Partition Data Layers.
- L704 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L705 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L706 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L709 _public prototype_ `virtual TArray<TSharedRef<SWidget>> GetWidgets() override;`
- L710 _public prototype_ `virtual bool HasAddMenu() const override;`
- L711 _public prototype_ `virtual TSharedRef<SWidget> GetAddMenuContents(const FMovieGraphConditionGroupQueryContentsChanged& OnAddFinished) override;`
- L716 _private prototype_ `static const FSlateBrush* GetRowIcon(TSharedPtr<TSoftObjectPtr<UDataLayerAsset>> InDataLayer);`
- L717 _private prototype_ `static FText GetRowText(TSharedPtr<TSoftObjectPtr<UDataLayerAsset>> InDataLayer);`
- L720 _private prototype_ `void AddDataLayers(const TArray<const UDataLayerAsset*>& InDataLayers, const FMovieGraphConditionGroupQueryContentsChanged& InOnAddFinished);` — Adds the provided data layers to the query, updating the UI as needed. Calls InOnAddFinished when done.
- L723 _private prototype_ `void RefreshListDataSource();` — Refreshes the list's data source to reflect the data model.
- L726 _private member_ `TSharedPtr<SMovieGraphSimpleList<TSharedPtr<TSoftObjectPtr<UDataLayerAsset>>>> DataLayersList;` — Displays the layers which have been chosen.
- L730 _private member_ `TArray<TSharedPtr<TSoftObjectPtr<UDataLayerAsset>>> ListDataSource;` — Not ideal to store a duplicate of DataLayersList, but SListView requires TSharedPtr<...> as the data source, and UPROPERTY does not support TSharedPtr<...>
- L733 _private member_ `FRefreshAssetViewDelegate RefreshDataLayerPicker;` — Refreshes the contents of the data layer picker widget when called.
- L739 _public member_ `TArray<TSoftObjectPtr<UDataLayerAsset>> DataLayers;` — `UPROPERTY(EditAnywhere, Category="General")` — The actor must be in one of the these data layer assets in order to be a match.

#### class `UMovieGraphConditionGroupQuery_IsSpawnable`  
`class UMovieGraphConditionGroupQuery_IsSpawnable final : public UMovieGraphConditionGroupQueryBase`  
_L744-757_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphConditionGroupQueryBase`
- desc: Query type which filters actors by their spawnable status.
- L749 _public prototype_ `virtual void Evaluate(const TArray<AActor*>& InActorsToQuery, const UWorld* InWorld, TSet<AActor*>& OutMatchingActors) const override;`
- L750 _public prototype_ `virtual const FSlateIcon& GetIcon() const override;`
- L751 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L756 _public member_ `bool bIsSpawnable = false;` — `UPROPERTY(EditAnywhere, Category="General")` — Whether the actor is a spawnable or not.

#### struct `FMovieGraphEvaluationResult`  
`struct FMovieGraphEvaluationResult`  
_L761-794_
- reflection: `USTRUCT(BlueprintType)`
- desc: Provides the actors/components returned by a collection or condition group evaluation.
- L765 _public prototype_ `FMovieGraphEvaluationResult() = default;`
- L766 _public prototype_ `FMovieGraphEvaluationResult(TSet<TObjectPtr<AActor>>&& InActors, TSet<TObjectPtr<UActorComponent>>&& InComponents);`
- L769 _public prototype_ `void Reset();` — Empties this evaluation result and resets it to defaults.
- L772 _public prototype_ `void Append(const FMovieGraphEvaluationResult& InOther);` — Appends the actors/components in InOther to the actors/components in this evaluation result.
- L775 _public prototype_ `FMovieGraphEvaluationResult Union(const FMovieGraphEvaluationResult& InOther) const;` — Unions this evaluation result with InOther.
- L778 _public prototype_ `FMovieGraphEvaluationResult Intersect(const FMovieGraphEvaluationResult& InOther) const;` — Intersects this evaluation result with InOther.
- L781 _public prototype_ `FMovieGraphEvaluationResult Difference(const FMovieGraphEvaluationResult& InOther) const;` — Differences this evaluation result with InOther.
- L785 _public prototype_ `template<typename T> TArray<T*> GetAllComponentsOfType() const;` — Gets all components of the specified type across MatchingActors and MatchingComponents.
- L789 _public member_ `TSet<TObjectPtr<AActor>> MatchingActors;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — The actors that were matched during evaluation.
- L793 _public member_ `TSet<TObjectPtr<UActorComponent>> MatchingComponents;` — `UPROPERTY(BlueprintReadOnly, Category = "Movie Graph")` — The components that were matched during evaluation.

#### class `UMovieGraphConditionGroup`  
`class UMovieGraphConditionGroup : public UObject`  
_L798-882_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A group of queries which can be added to a collection.
- L803 _public prototype_ `UMovieGraphConditionGroup();`
- L810 _public prototype_ `void SetOperationType(const EMovieGraphConditionGroupOpType OperationType);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Sets how the condition group interacts with the collection. This call is ignored for the first condition group in the collection (the first is always Union).
- L814 _public prototype_ `EMovieGraphConditionGroupOpType GetOperationType() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Gets the condition group operation type.
- L819 _public prototype_ `TSet<AActor*> Evaluate(const UWorld* InWorld) const;` — `UE_DEPRECATED(5.6, "Please use EvaluateActorsAndComponents() instead.")` — `UFUNCTION(BlueprintCallable, Category = "Settings", meta = (DeprecatedFunction, DeprecationMessage = "Please use EvaluateActorsAndComponents() instead."))` — Determines the actors that match the condition group by running the queries contained in it.
- L823 _public prototype_ `FMovieGraphEvaluationResult EvaluateActorsAndComponents(const UWorld* InWorld) const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Determines the actors and components that match the condition group by running the queries contained in it.
- L831 _public prototype_ `UMovieGraphConditionGroupQueryBase* AddQuery(const TSubclassOf<UMovieGraphConditionGroupQueryBase>& InQueryType, const int32 InsertIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Adds a new condition group query to the condition group and returns a ptr to it. The condition group owns the created query. By default the query is added to the end, but an optional index can be provided if the query should be placed in a specific location among the existing queries.
- L835 _public prototype_ `const TArray<UMovieGraphConditionGroupQueryBase*>& GetQueries() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Gets all queries currently contained in the condition group.
- L839 _public prototype_ `bool RemoveQuery(UMovieGraphConditionGroupQueryBase* InQuery);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Removes the specified query from the condition group if it exists. Returns true on success, else false.
- L846 _public prototype_ `UMovieGraphConditionGroupQueryBase* DuplicateQuery(const int32 QueryIndex);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Duplicates the condition group query at the specified index. The duplicate is placed at the end of the query list. Returns the duplicate query on success, else nullptr.
- L850 _public prototype_ `bool IsFirstConditionGroup() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Determines if this is the first condition group under the parent collection.
- L857 _public prototype_ `bool MoveQueryToIndex(UMovieGraphConditionGroupQueryBase* InQuery, const int32 NewIndex);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Move the specified query to a new index within the condition group. Returns false if the query was not found or the index specified is invalid, else true.
- L860 _public prototype_ `const FGuid& GetId() const;` — Gets a persistent unique identifier for this condition group.
- L865 _private member_ `FGuid Id;` — `UPROPERTY()` — A unique identifier for this condition group. Needed in some cases because condition groups do not have names.
- L869 _private member_ `EMovieGraphConditionGroupOpType OpType;` — `UPROPERTY(EditAnywhere, Category="General")` — The operation type that the condition group is using.
- L873 _private member_ `TArray<TObjectPtr<UMovieGraphConditionGroupQueryBase>> Queries;` — `UPROPERTY(EditAnywhere, Category="General", Instanced)` — The queries that are contained within the condition group.
- L877 _private member_ `mutable FMovieGraphEvaluationResult QueryResult;` — `UPROPERTY(Transient, DuplicateTransient)` — Persisted actor set which can be re-used for query evaluations across frames to prevent constantly re-allocating it.
- L881 _private member_ `mutable FMovieGraphEvaluationResult EvaluationResult;` — `UPROPERTY(Transient, DuplicateTransient)` — Persisted actor set which can be re-used for condition group evaluations across frames to prevent constantly re-allocating it.

#### class `UMovieGraphCollection`  
`class UMovieGraphCollection : public UObject`  
_L886-964_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A group of actors generated by actor queries.
- L892 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMovieGraphCollectionNameChanged, UMovieGraphCollection*) UMovieGraphCollection() = default;` — Delegate which is called when the collection name changes.
- L898 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L904 _public prototype_ `void SetCollectionName(const FString& InName);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Sets the name of the collection as seen in the UI.
- L908 _public prototype_ `const FString& GetCollectionName() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Gets the name of the collection as seen in the UI.
- L916 _public prototype_ `TSet<AActor*> Evaluate(const UWorld* InWorld) const;` — `UE_DEPRECATED(5.6, "Please use EvaluateActorsAndComponents() instead.")` — `UFUNCTION(BlueprintCallable, Category = "Settings", meta = (DeprecatedFunction, DeprecationMessage = "Please use EvaluateActorsAndComponents() instead."))` — Gets matching actors by having condition groups evaluate themselves, and performing set operations on the condition group results (eg, union'ing condition group A and B).
- L923 _public prototype_ `FMovieGraphEvaluationResult EvaluateActorsAndComponents(const UWorld* InWorld) const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Gets matching actors and components by having condition groups evaluate themselves, and performing set operations on the condition group results (eg, union'ing condition group A and B).
- L930 _public prototype_ `UMovieGraphConditionGroup* AddConditionGroup();` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Adds a new condition group to the collection and returns a ptr to it. The collection owns the created condition group.
- L934 _public prototype_ `const TArray<UMovieGraphConditionGroup*>& GetConditionGroups() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Gets all condition groups currently contained in the collection.
- L941 _public prototype_ `bool RemoveConditionGroup(UMovieGraphConditionGroup* InConditionGroup);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Removes the specified condition group from the collection if it exists. Returns true on success, else false. Removes all child queries that belong to this group at the same time.
- L948 _public prototype_ `bool MoveConditionGroupToIndex(UMovieGraphConditionGroup* InConditionGroup, const int32 NewIndex);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Move the specified condition group to a new index within the collection. Returns false if the condition group was not found or the index specified is invalid, else true.
- L953 _public member_ `FMovieGraphCollectionNameChanged OnCollectionNameChangedDelegate;` — Called when the collection name changes.
- L959 _private member_ `FString CollectionName;` — `UPROPERTY(EditAnywhere, Category="Collection")` — The display name of the collection, shown in the UI. Does not need to be unique across collections.
- L963 _private member_ `TArray<TObjectPtr<UMovieGraphConditionGroup>> ConditionGroups;` — `UPROPERTY(EditAnywhere, Category="Collection")` — The condition groups that are contained within the collection.

#### class `UMovieGraphModifierBase`  
`class UMovieGraphModifierBase : public UObject`  
_L970-986_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: The base class that all modifiers should inherit from. Does not support collections (see UMovieGraphCollectionModifier).
- L977 _public prototype_ `virtual void ApplyModifier(const UWorld* World) PURE_VIRTUAL(UMovieGraphModifierBase::ApplyModifier, );` — `UFUNCTION(BlueprintCallable, Category = "Modifier")` — Applies this modifier in the provided world. Called once per layer.
- L981 _public prototype_ `virtual void UndoModifier() PURE_VIRTUAL(UMovieGraphModifierBase::UndoModifier, );` — `UFUNCTION(BlueprintCallable, Category = "Modifier")` — Undoes the effects of this modifier. The modifier is responsible for tracking changes that it makes. Called once per layer.
- L985 _public prototype_ `virtual FText GetModifierName() PURE_VIRTUAL(UMovieGraphModifierBase::GetModifierName, return FText::GetEmpty(););` — `UFUNCTION(BlueprintCallable, Category = "Modifier")` — Gets the name of this modifier. Typically used for UI display purposes.

#### class `UMovieGraphCollectionModifier`  
`class UMovieGraphCollectionModifier : public UMovieGraphModifierBase`  
_L992-1017_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMovieGraphModifierBase`
- desc: Base class for providing actor modification functionality via collections. For modifiers without collections, see UMovieGraphModifierBase.
- L999 _public prototype_ `void AddCollection(UMovieGraphCollection* Collection);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Adds a collection to the existing set of collections in this modifier.
- L1003 _public prototype_ `void SetCollections(const TArray<UMovieGraphCollection*> InCollections);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Overwrites the existing collections with the provided array of collections.
- L1007 _public prototype_ `TArray<UMovieGraphCollection*> GetCollections() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Gets all collections that this modifier is using.
- L1010 _public prototype_ `virtual FText GetModifierName() override;`
- L1016 _protected member_ `TArray<TObjectPtr<UMovieGraphCollection>> Collections;` — `UPROPERTY()` — The collections which this modifier will operate on.

#### class `UMovieGraphMaterialModifier`  
`class UMovieGraphMaterialModifier : public UMovieGraphCollectionModifier`  
_L1023-1050_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphCollectionModifier`
- desc: Modifies actor materials.
- L1029 _public function_ `void SetMaterial(TSoftObjectPtr<UMaterialInterface> InMaterial)` — `UFUNCTION(BlueprintCallable, Category = "Settings")`
- L1032 _public prototype_ `virtual void ApplyModifier(const UWorld* World) override;`
- L1033 _public prototype_ `virtual void UndoModifier() override;`
- L1034 _public prototype_ `virtual FText GetModifierName() override;`
- L1038 _private typedef_ `typedef TTuple<int32, TSoftObjectPtr<UMaterialInterface>> FMaterialSlotAssignment;`
- L1039 _private typedef_ `typedef TMap<TSoftObjectPtr<UPrimitiveComponent>, TArray<FMaterialSlotAssignment>> FComponentToMaterialMap;`
- L1042 _private member_ `FComponentToMaterialMap ModifiedComponents;` — Maps a component to its original material assignments (per index).
- L1046 _public member_ `uint8 bOverride_Material : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L1049 _public member_ `TSoftObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "bOverride_Material"))`

#### class `UMovieGraphRenderPropertyModifier`  
`class UMovieGraphRenderPropertyModifier : public UMovieGraphCollectionModifier`  
_L1056-1182_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphCollectionModifier`
- desc: Modifies actor visibility.
- L1061 _public prototype_ `UMovieGraphRenderPropertyModifier();`
- L1064 _public prototype_ `virtual void PostLoad() override;`
- L1066 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L1071 _public function_ `void SetHidden(const bool bInIsHidden)` — `UFUNCTION(BlueprintCallable, Category = "Settings")`
- L1074 _public function_ `bool IsHidden() const` — `UFUNCTION(BlueprintCallable, Category = "Settings")`
- L1077 _public prototype_ `virtual void ApplyModifier(const UWorld* World) override;`
- L1078 _public prototype_ `virtual void UndoModifier() override;`
- L1079 _public prototype_ `virtual FText GetModifierName() override;`
- L1110 _private prototype_ `void SetActorAndComponentState(const TArray<FActorState>& InActorState, const TArray<FComponentState>& InComponentState, const bool bUseStateFromNode);` — Updates actor/component state to the state contained in InActorState/InComponentState. If bUseStateFromNode is true, InActorState and InComponent state will be ignored; the node's state will be applied to all actors and components that are currently cached. This is typically used to set the state of actors and components before a render after their state has been cached out.
- L1113 _private prototype_ `void ValidateProjectSettings() const;` — Convenience function to ensure that output alpha and primitive alpha holdout settings are enabled if required.
- L1117 _private member_ `TArray<FActorState> CachedActorState;` — Tracks relevant actor state prior to having the modifier applied. Only actors that are affected are included in the cache.
- L1120 _private member_ `TArray<FComponentState> CachedComponentState;` — Tracks relevant component state prior to having the modifier applied. Only components that are affected are included in the cache.
- L1124 _public member_ `uint8 bOverride_bIsHidden : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L1127 _public member_ `uint8 bOverride_bCastsShadows : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L1130 _public member_ `uint8 bOverride_bCastShadowWhileHidden : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L1133 _public member_ `uint8 bOverride_bAffectIndirectLightingWhileHidden : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L1136 _public member_ `uint8 bOverride_bHoldout : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L1139 _public member_ `uint8 bOverride_bVisibleInReflections : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L1142 _public member_ `uint8 bOverride_bProcessEditorOnlyActors : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L1149 _public member_ `uint8 bIsHidden : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "bOverride_bIsHidden"))` — If true, the actor will not be visible and will not contribute to any secondary effects (shadows, indirect lighting) unless their respective flags are set below.
- L1153 _public member_ `uint8 bCastsShadows : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "bOverride_bCastsShadows"))` — If true, the primitive will cast shadows.
- L1157 _public member_ `uint8 bCastShadowWhileHidden : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "bOverride_bCastShadowWhileHidden"))` — If true, the primitive will cast shadows even if it is hidden.
- L1161 _public member_ `uint8 bAffectIndirectLightingWhileHidden : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "bOverride_bAffectIndirectLightingWhileHidden"))` — Controls whether the primitive should affect indirect lighting when hidden.
- L1168 _public member_ `uint8 bHoldout : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "bOverride_bHoldout"))` — If true, the primitive will render black with an alpha of 0, but all secondary effects (shadows, reflections, indirect lighting) remain. This feature requires activating the project setting(s) "Alpha Output", and "Support Primitive Alpha Holdout" if using the deferred renderer.
- L1172 _public member_ `uint8 bVisibleInReflections : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "bOverride_bVisibleInReflections"))` — If true, this component will be visible in ray traced reflections. Screen space traces will ignore this flag, as they directly sample SceneColor.
- L1181 _public member_ `uint8 bProcessEditorOnlyActors : 1;` — `UPROPERTY(BlueprintReadWrite, Category = "Settings")` — If true, this modifier will process editor-only actors (eg, the billboard icons that represent lights). Defaults to false. Generally, processing editor-only actors is a waste of cycles because they will never be shown in a render, and there's no point in messing with them. However there are some niche cases where they need to be modified (eg, Quick Render). This is not a property exposed to the UI or saved because it's only meant to be used temporarily (like by scripting; note that bOverride_bProcessEditorOnlyActors still needs to be set).

#### struct `UMovieGraphRenderPropertyModifier::FActorState`  
`struct FActorState`  
_L1084-1088_
- desc: Various visibility properties for an actor.
- L1086 _public member_ `TSoftObjectPtr<AActor> Actor = nullptr;`
- L1087 _public member_ `uint8 bIsHidden : 1 = false;`

#### struct `UMovieGraphRenderPropertyModifier::FComponentState`  
`struct FComponentState`  
_L1091-1103_
- desc: Various visibility properties for a component.
- L1093 _public member_ `TSoftObjectPtr<USceneComponent> Component = nullptr;`
- L1097 _public member_ `uint8 bCastsShadows : 1 = true;` — Note: The default values specified here reflect the defaults on the scene component. If a modifier property is marked as overridden, the override will initially be a no-op due to the defaults being the same.
- L1098 _public member_ `uint8 bCastShadowWhileHidden : 1 = false;`
- L1099 _public member_ `uint8 bAffectIndirectLightingWhileHidden : 1 = false;`
- L1100 _public member_ `uint8 bHoldout : 1 = false;`
- L1101 _public member_ `uint8 bVisibleInReflections : 1 = true;`
- L1102 _public member_ `uint8 bIsHidden : 1 = false;`

#### class `UMovieGraphRenderLayer`  
`class UMovieGraphRenderLayer : public UObject`  
_L1188-1239_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Provides a means of assembling modifiers together to generate a desired view of a scene.
- L1193 _public prototype_ `UMovieGraphRenderLayer() = default;`
- L1196 _public function_ `FName GetRenderLayerName() const` — `UFUNCTION(BlueprintCallable, Category = "Settings")`
- L1199 _public function_ `void SetRenderLayerName(const FName& NewName)` — `UFUNCTION(BlueprintCallable, Category = "Settings")`
- L1202 _public prototype_ `UMovieGraphCollection* GetCollectionByName(const FString& Name) const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")`
- L1206 _public prototype_ `void AddModifier(UMovieGraphCollectionModifier* Modifier);` — `UE_DEPRECATED(5.7, "Use AddLayerModifier() instead.")` — `UFUNCTION(BlueprintCallable, Category = "Settings", meta = (DeprecatedFunction, DeprecationMessage = "Use AddLayerModifier() instead."))`
- L1209 _public prototype_ `void AddLayerModifier(UMovieGraphModifierBase* InModifier);` — `UFUNCTION(BlueprintCallable, Category = "Settings")`
- L1213 _public prototype_ `TArray<UMovieGraphCollectionModifier*> GetModifiers() const;` — `UE_DEPRECATED(5.7, "Use GetLayerModifiers() instead.")` — `UFUNCTION(BlueprintCallable, Category = "Settings", meta = (DeprecatedFunction, DeprecationMessage = "Use GetLayerModifiers() instead."))`
- L1216 _public prototype_ `TArray<UMovieGraphModifierBase*> GetLayerModifiers() const;` — `UFUNCTION(BlueprintCallable, Category = "Settings")`
- L1220 _public prototype_ `void RemoveModifier(UMovieGraphCollectionModifier* Modifier);` — `UE_DEPRECATED(5.7, "Use RemoveLayerModifier() instead.")` — `UFUNCTION(BlueprintCallable, Category = "Settings", meta = (DeprecatedFunction, DeprecationMessage = "Use RemoveLayerModifier() instead."))`
- L1223 _public prototype_ `void RemoveLayerModifier(UMovieGraphModifierBase* Modifier);` — `UFUNCTION(BlueprintCallable, Category = "Settings")`
- L1226 _public prototype_ `void Apply(const UWorld* World);` — `UFUNCTION(BlueprintCallable, Category = "Settings")`
- L1229 _public prototype_ `void Revert();` — `UFUNCTION(BlueprintCallable, Category = "Settings")`
- L1234 _private member_ `FName RenderLayerName;` — `UPROPERTY()` — The name of this render layer.
- L1238 _private member_ `TArray<TObjectPtr<UMovieGraphModifierBase>> Modifiers;` — `UPROPERTY()` — The modifiers that are active when this render layer is active.

#### class `UMovieGraphRenderLayerSubsystem`  
`class UMovieGraphRenderLayerSubsystem : public UWorldSubsystem`  
_L1247-1314_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- desc: The primary means of controlling render layers in MRQ. Render layers can be added/registered with the subsystem, then made active in order to view them. Collections and modifiers can also be viewed, but they do not need to be added to the subsystem ahead of time.
- L1252 _public prototype_ `UMovieGraphRenderLayerSubsystem() = default;`
- L1256 _public prototype_ `static UMovieGraphRenderLayerSubsystem* GetFromWorld(const UWorld* World);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Get this subsystem for a specific world. Handy for use from Python.
- L1259 _public function_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override`
- L1260 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L1261 _public prototype_ `virtual void Deinitialize() override;`
- L1266 _public prototype_ `void Reset();` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Clear out all tracked render layers and collections.
- L1273 _public prototype_ `bool AddRenderLayer(UMovieGraphRenderLayer* RenderLayer);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Adds a render layer to the system, which can later be made active by SetActiveRenderLayer*(). Returns true if the layer was added successfully, else false.
- L1277 _public function_ `const TArray<UMovieGraphRenderLayer*>& GetRenderLayers()` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Gets all render layers which are currently tracked by the system.
- L1281 _public prototype_ `void RemoveRenderLayer(const FString& RenderLayerName);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Removes the render layer with the given name. After removal it can no longer be made active with SetActiveRenderLayerBy*().
- L1285 _public function_ `UMovieGraphRenderLayer* GetActiveRenderLayer() const` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Gets the currently active render layer (the layer with its modifiers applied).
- L1289 _public prototype_ `void SetActiveRenderLayerByName(const FName& RenderLayerName);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Applies the layer with the given name. The layer needs to have been registered with AddRenderLayer().
- L1293 _public prototype_ `void SetActiveRenderLayerByObj(UMovieGraphRenderLayer* RenderLayer);` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Applies the given layer. The layer does not need to have been registered with AddRenderLayer().
- L1297 _public prototype_ `void ClearActiveRenderLayer();` — `UFUNCTION(BlueprintCallable, Category = "Settings")` — Clears the currently active render layer and reverts its modifiers.
- L1301 _private prototype_ `void RevertAndClearActiveRenderLayer();` — Clears the currently active render layer and reverts its modifiers.
- L1304 _private prototype_ `void SetAndApplyRenderLayer(UMovieGraphRenderLayer* RenderLayer);` — Sets the active render layer and applies its modifiers.
- L1309 _private member_ `TArray<TObjectPtr<UMovieGraphRenderLayer>> RenderLayers;` — `UPROPERTY(Transient)` — Render layers which have been added/registered with the subsystem. These can be found by name.
- L1313 _private member_ `TObjectPtr<UMovieGraphRenderLayer> ActiveRenderLayer = nullptr;` — `UPROPERTY(Transient)` — The render layer that currently has its modifiers applied.

#### Free symbols / members of external scopes

- L58 _delegate_ `DECLARE_DELEGATE(FMovieGraphConditionGroupQueryContentsChanged) UFUNCTION(BlueprintCallable, Category = "Settings") void SetOperationType(const EMovieGraphConditionGroupQueryOpType OperationType);` — Delegate which is called when the contents of a query has changed.
- L892 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMovieGraphCollectionNameChanged, UMovieGraphCollection*) UMovieGraphCollection() = default;` — Delegate which is called when the collection name changes.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphSequenceDataSource.h` (Public)


#### struct `UE::MovieGraph::FMovieGraphSequenceTimeController`  
`struct FMovieGraphSequenceTimeController : public FMovieSceneTimeController`  
_L19-27_
- inherits: `FMovieSceneTimeController`
- L21 _public prototype_ `virtual FFrameTime OnRequestCurrentTime(const FQualifiedFrameTime& InCurrentTime, float InPlayRate) override;`
- L22 _public function_ `void SetCachedFrameTiming(const FQualifiedFrameTime& InTimeCache)`
- L26 _private member_ `FQualifiedFrameTime TimeCache;` — Simply store the number calculated and return it when requested.

#### class `UMovieGraphSequenceDataSource`  
`class UMovieGraphSequenceDataSource : public UMovieGraphDataSourceBase`  
_L37-79_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphDataSourceBase`
- desc: The UMovieGraphSequenceDataSource allows using a ULevelSequence as the external datasource for the Movie Graph. It will build the range of shots based on the contents of the level sequence (one shot per camera cut found inside the sequence hierarchy, not allowing overlapping Camera Cut sections), and then it will evaluate the level sequence for the given time when rendering.
- L42 _public prototype_ `UMovieGraphSequenceDataSource();`
- L43 _public prototype_ `virtual void CacheDataPreJob(const FMovieGraphInitConfig& InInitConfig) override;`
- L44 _public prototype_ `virtual void RestoreCachedDataPostJob() override;`
- L45 _public prototype_ `virtual void UpdateShotList() override;`
- L46 _public prototype_ `virtual FFrameRate GetTickResolution() const override;`
- L47 _public prototype_ `virtual FFrameRate GetDisplayRate() const override;`
- L48 _public prototype_ `virtual void SyncDataSourceTime(const FFrameTime& InTime) override;`
- L49 _public prototype_ `virtual void PlayDataSource() override;`
- L50 _public prototype_ `virtual void PauseDataSource() override;`
- L51 _public prototype_ `virtual void StopDataSource() override;`
- L52 _public prototype_ `virtual void JumpDataSource(const FFrameTime& InTimeToJumpTo) override;`
- L53 _public prototype_ `virtual void CacheHierarchyForShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot) override;`
- L54 _public prototype_ `virtual void RestoreHierarchyForShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot) override;`
- L55 _public prototype_ `virtual void MuteShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot) override;`
- L56 _public prototype_ `virtual void UnmuteShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot) override;`
- L57 _public prototype_ `virtual void ExpandShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot, const int32 InLeftDeltaFrames, const int32 InLeftDeltaFramesUserPoV, const int32 InRightDeltaFrames, const bool bInPrepass) override;`
- L59 _public prototype_ `virtual TArray<UE::MovieGraph::FMinimalCameraInfo> GetCameraInformation(UMoviePipelineExecutorShot* InShot, bool bIncludeSidecar) const override;`
- L60 _public prototype_ `virtual void InitializeShot(const TObjectPtr<UMoviePipelineExecutorShot>& InShot, const FFrameTime& InEvalTime) override;`
- L64 _public prototype_ `UMovieSceneSequencePlayer* GetSequencePlayer() const;` — Returns the sequence player used to evaluate the level sequence during rendering.
- L67 _protected prototype_ `void OverrideSequencePlaybackRangeFromGlobalOutputSettings(ULevelSequence* InSequence);`
- L68 _protected prototype_ `void CacheLevelSequenceData(ULevelSequence* InSequence);`
- L69 _protected prototype_ `void OnSequenceEvaluated(const UMovieSceneSequencePlayer& Player, FFrameTime CurrentTime, FFrameTime PreviousTime);`
- L73 _protected member_ `TObjectPtr<ALevelSequenceActor> LevelSequenceActor;` — `UPROPERTY(Transient)`
- L76 _protected member_ `TSharedPtr<UE::MovieGraph::FMovieGraphSequenceTimeController> CustomSequenceTimeController;` — Custom Time Controller for the Sequence Player, used to match Custom TimeStep without any floating point accumulation errors.
- L78 _protected member_ `TSharedPtr<MoviePipeline::FCameraCutSubSectionHierarchyNode> CachedSequenceHierarchyRoot;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MovieGraph` (scope `UE`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphSharedWidgets.h` (Public)


#### class `SMovieGraphSimpleList`  
`template<typename ListType> class SMovieGraphSimpleList final : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L31-360_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: A widget which lists items in rows w/ an alternating row color, where each item has an icon and text. A summary row appears at the end of the list indicating how many items are in the list.
- L34 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(const FSlateBrush*, FGetRowIcon, ListType);`
- L35 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetRowText, ListType);`
- L36 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<ITableRow>, FGetCustomRow, const TSharedRef<STableViewBase>&, ListType);`
- L37 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDelete, TArray<ListType>);`
- L38 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnGetContextMenuContent, FMenuBuilder&, TArray<ListType>);`
- L39 _public prototype_ `DECLARE_DELEGATE(FOnRefreshDataSourceRequested);`
- L40 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FGetRowEnableState, ListType);`
- L41 _public prototype_ `DECLARE_DELEGATE_TwoParams(FSetRowEnableState, ListType, bool);`
- L43 _public function_ `SLATE_BEGIN_ARGS(SMovieGraphSimpleList<ListType>) : _SelectionMode(ESelectionMode::Multi) , _ShowEnableDisable(false)`
- L49 _public prototype_ `SLATE_ATTRIBUTE(TArray<ListType>*, DataSource) SLATE_EVENT(FOnRefreshDataSourceRequested, OnRefreshDataSourceRequested) SLATE_ATTRIBUTE(FText, DataType) SLATE_ATTRIBUTE(FText, DataTypePlural) SLATE_ATTRIBUTE(TSharedPtr<SWidget>, CustomSummaryWidget);` — The source of data that the list will display.
- L71 _public prototype_ `SLATE_ATTRIBUTE(ESelectionMode::Type, SelectionMode) SLATE_EVENT(FGetRowIcon, OnGetRowIcon);` — The selection mode the list should be put into. Defaults to Multi.
- L77 _public prototype_ `SLATE_EVENT(FGetRowText, OnGetRowText);` — Gets the text for a row in the list. Use OnGetCustomRow if a custom HeaderRow is in use.
- L80 _public prototype_ `SLATE_EVENT(FGetCustomRow, OnGetCustomRow);` — If needed, custom rows can be generated. This is needed if using a custom header row.
- L83 _public prototype_ `SLATE_EVENT(FOnDelete, OnDelete) SLATE_EVENT(FOnGetContextMenuContent, OnGetContextMenuContent) SLATE_ATTRIBUTE(bool, ShowEnableDisable) SLATE_EVENT(FGetRowEnableState, OnGetRowEnableState) SLATE_EVENT(FSetRowEnableState, OnSetRowEnableState) SLATE_ARGUMENT_DEFAULT(TSharedPtr<SHeaderRow>, HeaderRow) = nullptr;` — Invoked when a delete operation is performed.
- L99 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L183 _public function_ `void Refresh()` — Refreshes the contents of the list.
- L194 _private function_ `const FSlateBrush* GetRowIcon(const ListType& InListData) const` — Gets the row icon associated with the given list data.
- L205 _private function_ `FText GetRowText(const ListType& InListData) const` — Gets the row text associated with the given list data.
- L216 _private function_ `bool IsRowEnabled(const ListType& InListData) const` — Determines if the row that displays the given data should be enabled.
- L227 _private function_ `void HandleDelete() const` — Deletes selected items in the list.
- L241 _private function_ `TSharedPtr<SWidget> OnContextMenuOpening()`
- L268 _private function_ `TSharedRef<ITableRow> GenerateRow(ListType InListData, const TSharedRef<STableViewBase>& InOwnerTable) const` — Generates a row in the list for the specified data.
- L331 _private function_ `virtual void PostUndo(bool bSuccess) override`
- L336 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L343 _private member_ `TSharedPtr<SListView<ListType>> ListView;`
- L344 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L345 _private member_ `FGetRowIcon OnGetRowIcon;`
- L346 _private member_ `FGetRowText OnGetRowText;`
- L347 _private member_ `FGetCustomRow OnGetCustomRow;`
- L348 _private member_ `FOnDelete OnDelete;`
- L349 _private member_ `FOnGetContextMenuContent OnGetContextMenuContent;`
- L350 _private member_ `FOnRefreshDataSourceRequested OnRefreshDataSourceRequested;`
- L351 _private member_ `bool bShowEnableDisable = false;`
- L352 _private member_ `FGetRowEnableState OnGetRowEnableState;`
- L353 _private member_ `FSetRowEnableState OnSetRowEnableState;`
- L354 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L355 _private member_ `FText DataType;`
- L356 _private member_ `FText DataTypePlural;`
- L357 _private member_ `TAttribute<TSharedPtr<SWidget>> CustomSummaryWidget;`
- L358 _private member_ `TArray<ListType>* DataSource = nullptr;`
- L359 _private member_ `ESelectionMode::Type SelectionMode = ESelectionMode::Multi;`

#### class `SMovieGraphSimplePicker`  
`template<typename DataType> class SMovieGraphSimplePicker : public SCompoundWidget`  
_L367-527_
- inherits: `SCompoundWidget`
- desc: A simple widget that displays a list that can be picked from. Meant for use within pop-ups. Shows a title above the list, and an optional message to be displayed (instead of the list) if the data source is empty.
- L370 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnItemPicked, DataType);`
- L371 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(const FSlateBrush*, FGetRowIcon, DataType);`
- L372 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetRowText, DataType);`
- L373 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilter, DataType);`
- L375 _public function_ `SLATE_BEGIN_ARGS(SMovieGraphSimplePicker)`
- L379 _public prototype_ `SLATE_EVENT(FOnItemPicked, OnItemPicked) SLATE_EVENT(FGetRowIcon, OnGetRowIcon);` — Called when an item is picked in the list.
- L385 _public prototype_ `SLATE_EVENT(FGetRowText, OnGetRowText);` — Gets the text for a row in the list.
- L388 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_ARGUMENT(FText, DataSourceEmptyMessage) SLATE_ARGUMENT(TArray<DataType>, DataSource);` — The title text shown within the picker widget.
- L395 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L453 _private function_ `void OnItemSelected(const DataType Item, ESelectInfo::Type Type) const` — Handles an item selected event.
- L464 _private function_ `const FSlateBrush* GetRowIcon(const DataType InItem) const` — Gets the row icon associated with the given item.
- L475 _private function_ `FText GetRowText(const DataType InListData) const` — Gets the row text associated with the given list data.
- L486 _private function_ `TSharedRef<ITableRow> GenerateRow(const DataType InItem, const TSharedRef<STableViewBase>& InOwnerTable) const` — Generates a row which displays a single item.
- L519 _protected member_ `TArray<DataType> DataSource;` — The data source for the list view widget. Names of the items that can be picked. Widgets that inherit from this class can optionally control this data member directly rather than providing it as an argument.
- L522 _private member_ `FOnItemPicked OnItemPicked;`
- L523 _private member_ `FGetRowIcon OnGetRowIcon;`
- L524 _private member_ `FGetRowText OnGetRowText;`
- L525 _private member_ `FText Title;`
- L526 _private member_ `FText DataSourceEmptyMessage;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define LOCTEXT_NAMESPACE "MovieGraphSharedWidgets"`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(const FSlateBrush*, FGetRowIcon, ListType);`
- L35 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetRowText, ListType);`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<ITableRow>, FGetCustomRow, const TSharedRef<STableViewBase>&, ListType);`
- L37 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDelete, TArray<ListType>);`
- L38 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetContextMenuContent, FMenuBuilder&, TArray<ListType>);`
- L39 _delegate_ `DECLARE_DELEGATE(FOnRefreshDataSourceRequested);`
- L40 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FGetRowEnableState, ListType);`
- L41 _delegate_ `DECLARE_DELEGATE_TwoParams(FSetRowEnableState, ListType, bool);`
- L125 _function_ `` (scope `SMovieGraphSimpleList::SLATE_END_ARGS`)
- L291 _function_ `` (scope `SMovieGraphSimpleList::GenerateRow`)
- L313 _function_ `.IsEnabled_Lambda([this, InListData]() { return IsRowEnabled(InListData); }) .Visibility_Lambda([RowIcon]() { return RowIcon ? EVisibility::Visible : EVisibility::Collapsed; }) .Image(RowIcon) ] + SHorizontalBox::Slot() .VAlign(VAlign_Center) .HAlign(HAlign_Fill) [ SNew(STextBlock) .IsEnabled_Lambda([this, InListData]() { return IsRowEnabled(InListData); }) .Font(FAppStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont"))) .Text(GetRowText(InListData)) ] ];` (scope `SMovieGraphSimpleList::GenerateRow`)
- L314 _function_ `.Visibility_Lambda([RowIcon]() { return RowIcon ? EVisibility::Visible : EVisibility::Collapsed; }) .Image(RowIcon) ] + SHorizontalBox::Slot() .VAlign(VAlign_Center) .HAlign(HAlign_Fill) [ SNew(STextBlock) .IsEnabled_Lambda([this, InListData]() { return IsRowEnabled(InListData); }) .Font(FAppStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont"))) .Text(GetRowText(InListData)) ] ];` (scope `SMovieGraphSimpleList::GenerateRow`)
- L323 _function_ `.IsEnabled_Lambda([this, InListData]() { return IsRowEnabled(InListData); }) .Font(FAppStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont"))) .Text(GetRowText(InListData)) ] ];` (scope `SMovieGraphSimpleList::GenerateRow`)
- L370 _delegate_ `DECLARE_DELEGATE_OneParam(FOnItemPicked, DataType);`
- L371 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(const FSlateBrush*, FGetRowIcon, DataType);`
- L372 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetRowText, DataType);`
- L373 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilter, DataType);`
- L428 _function_ `.WidgetIndex_Lambda([this] { return DataSource.IsEmpty() ? 0 : 1; }) + SWidgetSwitcher::Slot() .VAlign(VAlign_Center) .HAlign(HAlign_Center) [ SNew(STextBlock) .Text(DataSourceEmptyMessage) ] + SWidgetSwitcher::Slot() [ SNew(SListView<DataType>) .ListItemsSource(&DataSource) .SelectionMode(ESelectionMode::Single) .OnSelectionChanged(this, &SMovieGraphSimplePicker::OnItemSelected) .OnGenerateRow(this, &SMovieGraphSimplePicker::GenerateRow) ] ] ] ];` (scope `SMovieGraphSimplePicker::SLATE_END_ARGS`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphTimeStepData.h` (Public)


#### struct `FMovieGraphTimeStepData`  
`struct FMovieGraphTimeStepData`  
_L16-167_
- reflection: `USTRUCT(BlueprintType)`
- desc: This data structure needs to be filled out each frame by the UMovieGraphTimeStepBase, which will eventually be passed to the renderer. It controls per-sample behavior such as the delta time, if this is the first/last sample for an output frame, etc.
- L21 _public function_ `FMovieGraphTimeStepData() : OutputFrameNumber(0) , ShotOutputFrameNumber(0) , RenderedFrameNumber(0) , FrameDeltaTime(0.f) , WorldTimeDilation(0.f) , bHasRelativeTimeBeenUsed(false) , WorldSeconds(0.f) , MotionBlurFraction(0.f) , FrameRate(0, 0) , TemporalSampleIndex(0) , TemporalSampleCount(0) , SpatialSampleIndex(0) , SpatialSampleCount(0) , bIsFirstTemporalSampleForFrame(false) , bIsLastTemporalSampleForFrame(false) , bDiscardOutput(false) , bIsCameraCut(false) , bRequiresAccumulator(false)`
- L46 _public member_ `int32 OutputFrameNumber;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Relative to zero for the entire render.
- L52 _public member_ `int32 ShotOutputFrameNumber;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Relative to zero for the current shot.
- L55 _public member_ `int32 RenderedFrameNumber;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")`
- L58 _public member_ `float FrameDeltaTime;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")`
- L61 _public member_ `float WorldTimeDilation;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")`
- L65 _public member_ `bool bHasRelativeTimeBeenUsed;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — True if time dilation was used on this frame, or any in the past, even if WorldTimeDilation has returned to 1.0
- L68 _public member_ `float WorldSeconds;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")`
- L71 _public member_ `float MotionBlurFraction;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")`
- L74 _public member_ `FFrameRate FrameRate;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")`
- L81 _public member_ `int32 TemporalSampleIndex;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Index out of TemporalSampleCount we're on. No guarantee that we'll ever reach Index == Count-1, if bIsLastTemporalSampleForFrame has priority over that (to allow early outs)
- L87 _public member_ `int32 TemporalSampleCount;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — What is the maximum number of Temporal Samples this frame is expected to be able to process.
- L91 _public member_ `int32 SpatialSampleIndex;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Index out of SpatialSampleCount that we're on.
- L95 _public member_ `int32 SpatialSampleCount;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — The maximum number of Spatial Samples this frame is expected to be able to process.
- L103 _public member_ `bool bIsFirstTemporalSampleForFrame;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Should be set to true for the first sample of each output frame. Used to determine if various systems need to reset or gather data for a new frame. Can be true at the same time as bIsLastTemporalSampleForFrame (ie: 1TS)
- L110 _public member_ `bool bIsLastTemporalSampleForFrame;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Should be set to true for the last sample of each output frame. Can be true at the same time as bIsFirstTemporalSampleForFrame (ie: 1TS)
- L118 _public member_ `bool bDiscardOutput;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Should the rendered result be discarded after a render? This will skip any accumulators or readback and is used for frames that are only produced to warm up the renderer.
- L126 _public member_ `bool bIsCameraCut;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — When true, signals to the renderer that this sample is a camera cut. The velocity rendering pass skips most primitives (suppressing motion blur and TSR/TAA ghosting from stale previous-frame transform data), and TAA/TSR history buffers are cleared to force a fresh temporal accumulation.
- L134 _public member_ `bool bRequiresAccumulator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Should be set to true for every sample if there is more than one temporal sample making up this render. This will cause the renderer to allocate accumulators to store the multi-frame data into.
- L144 _public member_ `TObjectPtr<UMovieGraphEvaluatedConfig> EvaluatedConfig;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — The evaluated config holds the configuration used for this given frame. This pointer can potentially change each frame (if the graph for that frame is different) but users can rely on the EvaluatedConfig being correct for a given frame, thus all resolves (such as filenames) should use the config for that frame, not the latest one available.
- L148 _public member_ `FTimecode RootTimeCode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — The current timecode at the root (sequence) level. Note that this is adjusted according to the timecode settings on the Global Output Settings node.
- L155 _public member_ `FFrameNumber RootFrameNumber;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — The current frame number at the root (sequence) level. This is the same number as what is shown in sequencer when viewing the sequence.
- L159 _public member_ `FTimecode ShotTimeCode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — The current timecode at the shot level. Note that this is adjusted according to the timecode settings on the Global Output Settings node.
- L166 _public member_ `FFrameNumber ShotFrameNumber;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — The current frame number at the shot level. This is the same number as what is shown in sequencer when viewing the shot.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphTraversalContext.h` (Public)


#### struct `FMovieGraphBranch`  
`struct FMovieGraphBranch`  
_L16-23_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `FName BranchName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MovieGraph")`

#### struct `FMovieGraphTraversalContext`  
`struct FMovieGraphTraversalContext`  
_L27-64_
- reflection: `USTRUCT(BlueprintType)`
- L32 _public function_ `FMovieGraphTraversalContext() : ShotIndex(0) , ShotCount(0)`
- L39 _public member_ `int32 ShotIndex;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — Which shot (out of ShotCount) is this time step for?
- L43 _public member_ `int32 ShotCount;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — The total number of shots being rendered for this job. This is from the active shot list, not total in the Level Sequence.
- L47 _public member_ `TObjectPtr<UMoviePipelineExecutorJob> Job;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — The job in the queue this traversal context is for. Needed to fetch variable values from the job.
- L51 _public member_ `TObjectPtr<UMoviePipelineExecutorShot> Shot;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — The shot in the queue this traversal context is for (if any).
- L55 _public member_ `TObjectPtr<UMovieGraphConfig> RootGraph;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Graph")` — The root graph to start our traversal from. This could be a shared config for the whole job, or a shot-specific override.
- L59 _public member_ `FMovieGraphRenderDataIdentifier RenderDataIdentifier;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MovieGraph")` — The name of the render resource this state was captured for.
- L63 _public member_ `FMovieGraphTimeStepData Time;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MovieGraph")` — The time data(output frame, delta times, etc.)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphValueContainer.h` (Public)


#### class `UMovieGraphValueContainer`  
`class UMovieGraphValueContainer : public UObject`  
_L22-251_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Holds a generic value, with an API for getting/setting the value, as well as getting/setting its type and container type (eg, array). For a container that holds multiple values, see UMovieGraphMultiValueContainer.
- L27 _public prototype_ `UMovieGraphValueContainer();`
- L31 _public prototype_ `bool GetValueBool(bool& bOutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the bool value of the held data. Returns true on success, else false.
- L35 _public prototype_ `bool GetValueByte(uint8& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the byte value of the held data. Returns true on success, else false.
- L39 _public prototype_ `bool GetValueInt32(int32& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the int32 value of the held data. Returns true on success, else false.
- L43 _public prototype_ `bool GetValueInt64(int64& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the int64 value of the held data. Returns true on success, else false.
- L47 _public prototype_ `bool GetValueFloat(float& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the float value of the held data. Returns true on success, else false.
- L51 _public prototype_ `bool GetValueDouble(double& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the double value of the held data. Returns true on success, else false.
- L55 _public prototype_ `bool GetValueName(FName& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the FName value of the held data. Returns true on success, else false.
- L59 _public prototype_ `bool GetValueString(FString& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the FString value of the held data. Returns true on success, else false.
- L63 _public prototype_ `bool GetValueText(FText& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the FText value of the held data. Returns true on success, else false.
- L67 _public prototype_ `bool GetValueEnum(uint8& OutValue, const UEnum* RequestedEnum = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the enum value (for a specific enum) of the held data. Returns true on success, else false.
- L70 _public prototype_ `bool GetValueStruct(FStructView& OutValue, const UScriptStruct* RequestedStruct = nullptr) const;` — Gets the struct value (for a specific struct) of the held data. Returns true on success, else false.
- L74 _public prototype_ `bool GetValueObject(UObject*& OutValue, const UClass* RequestedClass = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the object value (for a specific class) of the held data. Returns true on success, else false.
- L78 _public prototype_ `bool GetValueClass(UClass*& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the UClass value of the held data. Returns true on success, else false.
- L82 _public prototype_ `FString GetValueSerializedString();` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the serialized string value of the held data.
- L86 _public function_ `template <typename T> bool GetValueEnum(T& OutValue) const` — Gets the enum value of the held data. Returns true on success, else false.
- L93 _public function_ `template <typename T> bool GetValueStruct(T*& OutValue) const` — Gets the struct value of the held data. Returns true on success, else false.
- L100 _public function_ `template <typename T> bool GetValueObject(T*& OutValue) const` — Gets the object value of the held data. Returns true on success, else false.
- L107 _public prototype_ `bool SetValueBool(const bool bInValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the bool value of the held data. Returns true on success, else false.
- L111 _public prototype_ `bool SetValueByte(const uint8 InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the byte value of the held data. Returns true on success, else false.
- L115 _public prototype_ `bool SetValueInt32(const int32 InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the int32 value of the held data. Returns true on success, else false.
- L119 _public prototype_ `bool SetValueInt64(const int64 InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the int64 value of the held data. Returns true on success, else false.
- L123 _public prototype_ `bool SetValueFloat(const float InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the float value of the held data. Returns true on success, else false.
- L127 _public prototype_ `bool SetValueDouble(const double InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the double value of the held data. Returns true on success, else false.
- L131 _public prototype_ `bool SetValueName(const FName InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the FName value of the held data. Returns true on success, else false.
- L135 _public prototype_ `bool SetValueString(const FString& InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the FString value of the held data. Returns true on success, else false.
- L139 _public prototype_ `bool SetValueText(const FText& InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the FText value of the held data. Returns true on success, else false.
- L143 _public prototype_ `bool SetValueEnum(const uint8 InValue, const UEnum* Enum);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the enum value of the held data. Returns true on success, else false.
- L146 _public prototype_ `bool SetValueStruct(FConstStructView InValue);` — Sets the struct value of the held data. Returns true on success, else false.
- L150 _public prototype_ `bool SetValueObject(UObject* InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the object value of the held data. Returns true on success, else false.
- L154 _public prototype_ `bool SetValueClass(UClass* InValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the class value of the held data. Returns true on success, else false.
- L158 _public prototype_ `bool SetValueSerializedString(const FString& NewValue);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the serialized value of the held data. The string should be the serialized representation of the value. Returns true on success, else false.
- L162 _public function_ `template <typename T> bool SetValueEnum(const T InValue)` — Sets the enum value of the held data. Returns true on success, else false.
- L169 _public function_ `template <typename T> bool SetValueStruct(const T& InValue)` — Sets the struct value of the held data. Returns true on success, else false.
- L176 _public function_ `template <typename T> bool SetValueObject(T* InValue)` — Sets the object value of the held data. Returns true on success, else false.
- L183 _public prototype_ `EMovieGraphValueType GetValueType() const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the type of the stored data.
- L187 _public prototype_ `void SetValueType(EMovieGraphValueType ValueType, UObject* InValueTypeObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the type of the stored data. Enums, structs, and classes must specify a value type object.
- L191 _public prototype_ `const UObject* GetValueTypeObject() const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the object that defines the enum, struct, or class.
- L195 _public prototype_ `void SetValueTypeObject(const UObject* ValueTypeObject);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the object that defines the enum, struct, or class.
- L199 _public prototype_ `EMovieGraphContainerType GetValueContainerType() const;` — `UFUNCTION(BlueprintCallable, Category="Config")` — Gets the container type of the stored value.
- L203 _public prototype_ `void SetValueContainerType(EMovieGraphContainerType ContainerType);` — `UFUNCTION(BlueprintCallable, Category="Config")` — Sets the container type of the stored value.
- L209 _public prototype_ `TValueOrError<FPropertyBagArrayRef, EPropertyBagResult> GetArrayRef();` — Gets a reference to the array backing the value, if any. GetValueContainerType() will return EMovieGraphContainerType::Array if the value is holding an array.
- L215 _public prototype_ `void SetPropertyName(const FName& InName);` — Sets the name of the property that the value container holds. This is mostly unneeded unless the display name of the property is important (eg, in the details panel).
- L218 _public prototype_ `FName GetPropertyName() const;` — Gets the name of the property that the value container holds.
- L221 _private prototype_ `virtual void PostLoad() override;`
- L229 _private prototype_ `void SetFromDesc(const FPropertyBagPropertyDesc* InDesc, const FString& InString);`
- L233 _private member_ `static const FName PropertyBagDefaultPropertyName;` — The default name of the single property stored in the property bag.
- L237 _private member_ `FName PropertyName;` — `UPROPERTY()` — The name of the single property stored in the property bag.
- L241 _private member_ `FInstancedPropertyBag Value;` — `UPROPERTY()` — UNUSED (kept for backwards compatibility purposes in PostLoad()). The value held by this object.
- L250 _private member_ `TObjectPtr<UMovieGraphMultiValueContainer> MultiValueContainer;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Value")` — The container that holds the single value. It's strange for a single-value class to internally hold a multi-value container. However, this was done in order to centralize the core logic of how MRG interacts with property bags in primarily one class (the multi-value container).

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphValueUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MovieGraph` (scope `UE`)
- L8 _namespace_ `namespace ValueUtils` (scope `UE::MovieGraph`)
- L11 _prototype_ `bool GetTypesForFProperty(const FProperty* InProperty, EMovieGraphValueType& OutValueType, TObjectPtr<UObject>& OutValueTypeObject);` (scope `UE::MovieGraph::ValueUtils`) — Gets the value type and value type object for a given FProperty. Returns true if the types could be determined, else false.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphValueView.h` (Public)


#### struct `FMovieGraphValueViewProperty`  
`struct FMovieGraphValueViewProperty`  
_L33-60_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a property that should be added to a property bag via UMovieGraphValueView.
- L37 _public prototype_ `FMovieGraphValueViewProperty() = default;`
- L39 _public prototype_ `FMovieGraphValueViewProperty( const FName& InPropertyName, const EMovieGraphValueType ValueType, const TObjectPtr<UObject>& InValueTypeObject, const TMap<FName, FString>& InMetadata);`
- L47 _public member_ `FName PropertyName;` — `UPROPERTY(BlueprintReadWrite, Category = "Property")` — The name of the property as it will appear in the property bag.
- L51 _public member_ `EMovieGraphValueType ValueType = EMovieGraphValueType::None;` — `UPROPERTY(BlueprintReadWrite, Category = "Property")` — The type of value the property holds.
- L55 _public member_ `TObjectPtr<UObject> ValueTypeObject = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = "Property")` — The value type object for object, struct, and enum-typed properties (nullptr for other types).
- L59 _public member_ `TMap<FName, FString> Metadata;` — `UPROPERTY(BlueprintReadWrite, Category = "Property")` — Metadata to apply to the property.

#### class `UMovieGraphValueView`  
`class UMovieGraphValueView : public UObject`  
_L69-316_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Provides a scripting-friendly way to get/set values, and add/remove properties, in a property bag. Does not protect against invalid property bags. When using, ensure that the property bag that the view is initialized with is valid. The view will also not take ownership of the property bag.
- L74 _public prototype_ `UMovieGraphValueView() = default;`
- L76 _public prototype_ `explicit UMovieGraphValueView(FInstancedPropertyBag* InPropertyBag);`
- L79 _public prototype_ `void ViewProperties(FInstancedPropertyBag* InPropertyBag);` — Update the view to use the specified property bag.
- L83 _public prototype_ `bool IsValid() const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Determines if this view is valid (meaning it points to a non-null property bag, and the bag is valid itself).
- L90 _public prototype_ `bool AddProperty(const FName& InPropertyName, const EMovieGraphValueType ValueType, UObject* InValueTypeObject, const TMap<FName, FString>& InMetadata);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Adds a new property to the container. If a property by the given name already exists, no add operation will occur. Returns true on successful add, otherwise returns false.
- L97 _public prototype_ `bool AddProperties(const TArray<FMovieGraphValueViewProperty>& InProperties);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Bulk adds properties to the container. Much more efficient than calling AddProperty() in a loop. Returns true if all properties were successfully added, else false.
- L101 _public prototype_ `bool RemoveProperty(const FName& InPropertyName);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Removes a property by the given name. Returns true on successful remove, otherwise returns false.
- L105 _public prototype_ `void RemoveAllProperties();` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Removes all properties and their values, effectively resetting the property bag.
- L109 _public prototype_ `bool HasProperty(const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Returns true if a property by the given name exists in the container, else false.
- L113 _public prototype_ `int32 GetNumProperties() const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the number of properties that this container holds.
- L117 _public prototype_ `TArray<FName> GetPropertyNames() const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the names of properties in this container.
- L122 _public prototype_ `TMap<FName, FString> GetPropertyMetadata(const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the metadata for the given property.
- L127 _public prototype_ `bool GetValueBool(const FName& InPropertyName, bool& bOutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the bool value of the held data. Returns true on success, else false.
- L131 _public prototype_ `bool GetValueByte(const FName& InPropertyName, uint8& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the byte value of the held data. Returns true on success, else false.
- L135 _public prototype_ `bool GetValueInt32(const FName& InPropertyName, int32& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the int32 value of the held data. Returns true on success, else false.
- L139 _public prototype_ `bool GetValueInt64(const FName& InPropertyName, int64& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the int64 value of the held data. Returns true on success, else false.
- L143 _public prototype_ `bool GetValueFloat(const FName& InPropertyName, float& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the float value of the held data. Returns true on success, else false.
- L147 _public prototype_ `bool GetValueDouble(const FName& InPropertyName, double& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the double value of the held data. Returns true on success, else false.
- L151 _public prototype_ `bool GetValueName(const FName& InPropertyName, FName& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the FName value of the held data. Returns true on success, else false.
- L155 _public prototype_ `bool GetValueString(const FName& InPropertyName, FString& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the FString value of the held data. Returns true on success, else false.
- L159 _public prototype_ `bool GetValueText(const FName& InPropertyName, FText& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the FText value of the held data. Returns true on success, else false.
- L163 _public prototype_ `bool GetValueEnum(const FName& InPropertyName, uint8& OutValue, const UEnum* RequestedEnum = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the enum value (for a specific enum) of the held data. Returns true on success, else false.
- L166 _public prototype_ `bool GetValueStruct(const FName& InPropertyName, FStructView& OutValue, const UScriptStruct* RequestedStruct = nullptr) const;` — Gets the struct value (for a specific struct) of the held data. Returns true on success, else false.
- L170 _public prototype_ `bool GetValueObject(const FName& InPropertyName, UObject*& OutValue, const UClass* RequestedClass = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the object value (for a specific class) of the held data. Returns true on success, else false.
- L174 _public prototype_ `bool GetValueClass(const FName& InPropertyName, UClass*& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the UClass value of the held data. Returns true on success, else false.
- L178 _public prototype_ `FString GetValueSerializedString(const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the serialized string value of the held data.
- L182 _public function_ `template <typename T> bool GetValueEnum(const FName& InPropertyName, T& OutValue) const` — Gets the enum value of the held data. Returns true on success, else false.
- L190 _public function_ `template <typename T> bool GetValueStruct(const FName& InPropertyName, T*& OutValue) const` — Gets the struct value of the held data. Returns true on success, else false.
- L198 _public function_ `template <typename T> bool GetValueObject(const FName& InPropertyName, T*& OutValue) const` — Gets the object value of the held data. Returns true on success, else false.
- L206 _public prototype_ `bool SetValueBool(const FName& InPropertyName, const bool bInValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the bool value of the held data. Returns true on success, else false.
- L210 _public prototype_ `bool SetValueByte(const FName& InPropertyName, const uint8 InValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the byte value of the held data. Returns true on success, else false.
- L214 _public prototype_ `bool SetValueInt32(const FName& InPropertyName, const int32 InValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the int32 value of the held data. Returns true on success, else false.
- L218 _public prototype_ `bool SetValueInt64(const FName& InPropertyName, const int64 InValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the int64 value of the held data. Returns true on success, else false.
- L222 _public prototype_ `bool SetValueFloat(const FName& InPropertyName, const float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the float value of the held data. Returns true on success, else false.
- L226 _public prototype_ `bool SetValueDouble(const FName& InPropertyName, const double InValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the double value of the held data. Returns true on success, else false.
- L230 _public prototype_ `bool SetValueName(const FName& InPropertyName, const FName InValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the FName value of the held data. Returns true on success, else false.
- L234 _public prototype_ `bool SetValueString(const FName& InPropertyName, const FString& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the FString value of the held data. Returns true on success, else false.
- L238 _public prototype_ `bool SetValueText(const FName& InPropertyName, const FText& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the FText value of the held data. Returns true on success, else false.
- L242 _public prototype_ `bool SetValueEnum(const FName& InPropertyName, const uint8 InValue, const UEnum* Enum);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the enum value of the held data. Returns true on success, else false.
- L245 _public prototype_ `bool SetValueStruct(const FName& InPropertyName, FConstStructView InValue);` — Sets the struct value of the held data. Returns true on success, else false.
- L249 _public prototype_ `bool SetValueObject(const FName& InPropertyName, UObject* InValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the object value of the held data. Returns true on success, else false.
- L253 _public prototype_ `bool SetValueClass(const FName& InPropertyName, UClass* InValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the class value of the held data. Returns true on success, else false.
- L257 _public prototype_ `bool SetValueSerializedString(const FName& InPropertyName, const FString& NewValue);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the serialized value of the held data. The string should be the serialized representation of the value. Returns true on success, else false.
- L261 _public function_ `template <typename T> bool SetValueEnum(const FName& InPropertyName, const T InValue)` — Sets the enum value of the held data. Returns true on success, else false.
- L268 _public function_ `template <typename T> bool SetValueStruct(const FName& InPropertyName, const T& InValue)` — Sets the struct value of the held data. Returns true on success, else false.
- L275 _public function_ `template <typename T> bool SetValueObject(const FName& InPropertyName, T* InValue)` — Sets the object value of the held data. Returns true on success, else false.
- L282 _public prototype_ `EMovieGraphValueType GetValueType(const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the type of the stored data.
- L286 _public prototype_ `void SetValueType(const FName& InPropertyName, EMovieGraphValueType ValueType, UObject* InValueTypeObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the type of the stored data. Enums, structs, and classes must specify a value type object.
- L290 _public prototype_ `const UObject* GetValueTypeObject(const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the object that defines the enum, struct, or class.
- L294 _public prototype_ `void SetValueTypeObject(const FName& InPropertyName, const UObject* ValueTypeObject);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the object that defines the enum, struct, or class.
- L298 _public prototype_ `EMovieGraphContainerType GetValueContainerType(const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the container type of the stored value.
- L302 _public prototype_ `void SetValueContainerType(const FName& InPropertyName, EMovieGraphContainerType ContainerType);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Sets the container type of the stored value.
- L308 _public prototype_ `TValueOrError<FPropertyBagArrayRef, EPropertyBagResult> GetArrayRef(const FName& InPropertyName);` — Gets a reference to the array backing the value, if any. GetValueContainerType() will return EMovieGraphContainerType::Array if the value is holding an array.
- L312 _protected member_ `bool bAllowPropertyAddRemove = false;` — Whether this view should allow properties to be added/removed from the property bag.
- L315 _private member_ `FInstancedPropertyBag* PropertyBag = nullptr;`

#### class `UMovieGraphFixedValueView`  
`class UMovieGraphFixedValueView final : public UMovieGraphValueView`  
_L322-342_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieGraphValueView`
- desc: Provides a scripting-friendly way to get/set values in a property bag. Does not allow adding/removing properties.
- L327 _public prototype_ `UMovieGraphFixedValueView();`
- L329 _public prototype_ `explicit UMovieGraphFixedValueView(FInstancedPropertyBag* InPropertyBag);`
- L334 _public prototype_ `bool AddProperty( const FName& InPropertyName, const EMovieGraphValueType ValueType, UObject* InValueTypeObject, const TMap<FName, FString>& InMetadata) = delete;` — The fixed view doesn't allow for adding/removing properties. Deleting these methods isn't foolproof, since a user could cast to the base class and call these methods there. However, these methods also have internal logic that cue off bAllowPropertyAddRemove to prevent these methods from performing any work.
- L339 _public prototype_ `bool AddProperties(const TArray<FMovieGraphValueViewProperty>& InProperties) = delete;`
- L340 _public prototype_ `bool RemoveProperty(const FName& InPropertyName) = delete;`
- L341 _public prototype_ `void RemoveAllProperties() = delete;`

#### class `UMovieGraphMutableValueView`  
`class UMovieGraphMutableValueView final : public UMovieGraphValueView`  
_L348-356_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieGraphValueView`
- desc: Provides a scripting-friendly way to get/set values, as well as add/remove properties, in a property bag.
- L353 _public prototype_ `UMovieGraphMutableValueView();`
- L355 _public prototype_ `explicit UMovieGraphMutableValueView(FInstancedPropertyBag* InPropertyBag);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MovieGraph` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::MovieGraph`)
- L17 _function_ `template<typename ReturnType> bool GetOptionalValue(TValueOrError<ReturnType, EPropertyBagResult>& PropertyBagValue, ReturnType& OutValue)` (scope `UE::MovieGraph::Private`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieRenderGraphEditorSettings.h` (Public)


#### enum `EMoviePipelineDefaultConfigType`  
`enum class EMoviePipelineDefaultConfigType : uint8`  
_L18-23_
- reflection: `UENUM()`
- desc: The default configuration type assigned to newly created jobs in the queue.
- L20 _public enumerator_ `Basic`
- L21 _public enumerator_ `MovieRenderGraph`
- L22 _public enumerator_ `LegacyPreset`

#### class `UMovieRenderGraphEditorSettings`  
`class UMovieRenderGraphEditorSettings : public UDeveloperSettings`  
_L26-57_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Config=EditorPerProjectUserSettings, meta=(DisplayName="Movie Render Graph"))`
- inherits: `UDeveloperSettings`
- L31 _public prototype_ `UMovieRenderGraphEditorSettings();`
- L33 _public prototype_ `virtual FName GetCategoryName() const override;`
- L36 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L41 _public member_ `FMovieGraphPostRenderSettings PostRenderSettings;` — `UPROPERTY(Config, EditAnywhere, Category="Play Render Output", meta=(ShowOnlyInnerProperties))` — If playing back media post-render, these settings dictate how that will be done.
- L45 _public member_ `EMoviePipelineDefaultConfigType DefaultConfigType = EMoviePipelineDefaultConfigType::Basic;` — `UPROPERTY(Config, EditAnywhere, Category="Queue Defaults")` — The configuration type assigned to newly created jobs within the editor.
- L52 _public member_ `TArray<FSoftClassPath> VisibleBasicConfigOutputTypes;` — `UPROPERTY(Config)` — Output types visible as toggle buttons in Basic Config mode. Each entry is the soft class path of a UMovieGraphFileOutputNode subclass.
- L56 _public member_ `bool bShowBurnInForBasicConfig = false;` — `UPROPERTY(Config)` — Whether the Burn In Class property is shown in Basic Config mode.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphApplyCVarPresetNode.h` (Public)


#### class `UMovieGraphApplyCVarPresetNode`  
`class UMovieGraphApplyCVarPresetNode : public UMovieGraphSettingNode`  
_L15-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- desc: A node which can apply a console variable preset.
- L20 _public prototype_ `UMovieGraphApplyCVarPresetNode() = default;`
- L22 _public prototype_ `virtual FString GetNodeInstanceName() const override;`
- L23 _public prototype_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override;`
- L24 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L25 _public prototype_ `virtual TArray<FMovieGraphPropertyInfo> GetOverrideablePropertyInfo() const override;`
- L26 _public prototype_ `virtual TArray<FPropertyBagPropertyDesc> GetDynamicPropertyDescriptions() const override;`
- L27 _public prototype_ `virtual bool GetDynamicPropertyValue(const FName PropertyName, FString& OutValue) override;`
- L28 _public prototype_ `virtual void TogglePromotePropertyToPin(const FName& PropertyName) override;`
- L29 _public prototype_ `virtual void PrepareForFlattening(const UMovieGraphSettingNode* InSourceNode) override;`
- L35 _public prototype_ `TArray<TPair<FString, float>> GetConsoleVariableOverrides() const;` — Gets the name and resolved value of any cvars that were overridden via promoted pins. This method only makes sense to call on a flattened (resolved) node.
- L38 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L39 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L40 _public prototype_ `virtual FText GetKeywords() const override;`
- L41 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L42 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L45 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L51 _public member_ `uint8 bOverride_ConsoleVariablePreset : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L55 _public member_ `TScriptInterface<IMovieSceneConsoleVariableTrackInterface> ConsoleVariablePreset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "bOverride_ConsoleVariablePreset"))` — The console variable preset that should be applied.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphApplyViewportLookNode.h` (Public)


#### class `UMovieGraphApplyViewportLookNode`  
`class UMovieGraphApplyViewportLookNode : public UMovieGraphSettingNode`  
_L20-77_
- reflection: `UCLASS(MinimalAPI, HideDropDown, NotBlueprintType)`
- inherits: `UMovieGraphSettingNode`
- desc: A node which applies the look of the viewport to the render (show flags, view mode, OCIO, etc).
- L25 _public prototype_ `UMovieGraphApplyViewportLookNode() = default;`
- L28 _public prototype_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override;`
- L33 _public prototype_ `static FLevelEditorViewportClient* GetViewportClient();` — Gets the viewport client for the currently active viewport.
- L36 _public prototype_ `bool GetViewportInfo(FEngineShowFlags& OutShowFlags, EViewModeIndex& OutViewModeIndex) const;` — Gets the show flags and view mode index for the currently active viewport.
- L39 _public prototype_ `void UpdateSceneView(FSceneView* InSceneView) const;` — Updates the given scene view to be like the current viewport's scene view.
- L42 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L43 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L44 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L45 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L51 _public member_ `uint8 bOverride_bOcio : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L54 _public member_ `uint8 bOverride_bShowFlags : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L57 _public member_ `uint8 bOverride_bViewMode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L60 _public member_ `uint8 bOverride_bVisibility : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L64 _public member_ `bool bOcio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Viewport Look", DisplayName="OCIO", meta=(EditCondition="bOverride_bOcio"))` — Set to true to apply the viewport's OCIO settings to the render. Only render nodes that have "Allow OCIO" turned on will be impacted.
- L68 _public member_ `bool bShowFlags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Viewport Look", meta=(EditCondition="bOverride_bShowFlags"))` — Set to true to apply the viewport's show flags to the render.
- L72 _public member_ `bool bViewMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Viewport Look", meta=(EditCondition="bOverride_bViewMode"))` — Set to true to apply the viewport's view mode to the render.
- L76 _public member_ `bool bVisibility;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Viewport Look", meta=(EditCondition="bOverride_bVisibility"))` — Set to true to apply editor visibility to actors in the render.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphAudioOutputNode.h` (Public)


#### class `UMovieGraphAudioOutputNode`  
`class UMovieGraphAudioOutputNode : public UMovieGraphFileOutputNode`  
_L16-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphFileOutputNode`
- desc: A node which outputs .wav audio after all renders have completed.
- L21 _public prototype_ `UMovieGraphAudioOutputNode();`
- L24 _public prototype_ `virtual void BuildNewProcessCommandLineArgsImpl(TArray<FString>& InOutUnrealURLParams, TArray<FString>& InOutCommandLineArgs, TArray<FString>& InOutDeviceProfileCvars, TArray<FString>& InOutExecCmds) const override;` — UMovieGraphSettingNode Interface
- L25 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L29 _public prototype_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override;` — UMovieGraphNode Interface
- L32 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive) const override;`
- L33 _public prototype_ `virtual FText GetKeywords() const override;`
- L34 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L35 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L39 _public prototype_ `virtual FText GetBasicConfigShortDisplayName() const override;` — UMovieGraphFileOutputNode interface
- L46 _public member_ `inline static const FString RendererName = TEXT("Aud` — Although this node does not represent a proper "renderer", it will sometimes be identified in data structures as a renderer. If that's the case, this is the name of the audio "renderer".
- L49 _public member_ `inline static const FString OutputExtension = TEXT("wav` — The extension of the audio files generated by this node.
- L54 _protected prototype_ `virtual void OnAllFramesSubmittedImpl(UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph) override;` — UMovieGraphFileOutputNode Interface
- L55 _protected prototype_ `virtual void OnAllShotFramesSubmittedImpl(UMovieGraphPipeline* InPipeline, const UMoviePipelineExecutorShot* InShot, TObjectPtr<UMovieGraphEvaluatedConfig>& InShotEvaluatedGraph, const bool bFlushToDisk) override;`
- L56 _protected prototype_ `virtual bool IsFinishedWritingToDiskImpl() const override;`
- L70 _private prototype_ `FString GenerateOutputPath(const FMovieGraphRenderDataIdentifier& InRenderIdentifier, const TObjectPtr<UMoviePipelineExecutorShot>& InShot) const;` — Generate the final output path for the audio file.
- L73 _private prototype_ `void GenerateFinalAudioData(TArray<FFinalAudioData>& OutFinalAudioData);` — Generates final audio data from all of the audio segments that were collected during render time.
- L76 _private prototype_ `void StartAudioExport();` — Begins the audio export process.
- L79 _private prototype_ `bool NeedsPerShotFlushing() const;` — Returns true if there should be one export per shot, else false.
- L85 _private member_ `inline static TArray<TUniquePtr<Audio::FSoundWavePCMWriter>> ActiveWriters;` — Kept alive during finalization because the writer writes async to disk but doesn't expect to fall out of scope.
- L88 _private member_ `inline static TSet<FGuid> AlreadyWrittenSegments;` — Keep track of segments that have already been written to disk to avoid re-writing them (and generating new output futures).
- L92 _private member_ `TWeakObjectPtr<UMovieGraphPipeline> CachedPipeline;` — The pipeline that is running this node.
- L98 _private member_ `TObjectPtr<UMovieGraphEvaluatedConfig> EvaluatedGraph;` — The graph that should be accessed during execution of the node. Do not access the graph from the pipeline as it may be invalid depending on if a shot-level or sequence-level export is being performed.

#### struct `UMovieGraphAudioOutputNode::FFinalAudioData`  
`struct FFinalAudioData`  
_L61-67_
- desc: Represents an audio file, with its associated audio data.
- L63 _public member_ `FString FilePath;`
- L64 _public member_ `Audio::TSampleBuffer<int16> SampleBuffer;`
- L65 _public member_ `int32 ShotIndex;`
- L66 _public member_ `FMovieGraphRenderDataIdentifier RenderIdentifier;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphBranchNode.h` (Public)


#### class `UMovieGraphBranchNode`  
`class UMovieGraphBranchNode : public UMovieGraphNode`  
_L17-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphNode`
- desc: A node which creates a True/False branching condition. A user Graph Variable can be plugged into the conditional pin and this will be evaluated when flattening the graph, choosing which branch path to follow.
- L22 _public prototype_ `UMovieGraphBranchNode() = default;`
- L24 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetInputPinProperties() const override;`
- L25 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetOutputPinProperties() const override;`
- L26 _public prototype_ `virtual TArray<UMovieGraphPin*> EvaluatePinsToFollow(FMovieGraphEvaluationContext& InContext) const override;`
- L29 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L30 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L31 _public prototype_ `virtual FText GetKeywords() const override;`
- L32 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L33 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphBurnInNode.h` (Public)


#### class `UMovieGraphBurnInNode`  
`class UMovieGraphBurnInNode : public UMovieGraphWidgetRendererBaseNode`  
_L23-95_
- reflection: `UCLASS(MinimalAPI, Hidden, HideDropdown, HideCategories = (Naming))`
- inherits: `UMovieGraphWidgetRendererBaseNode`
- desc: A node which generates a widget burn-in, rendered to a standalone image or composited on top of a render layer. DEPRECATED. Use the burn-in settings on output nodes instead to generate burn-ins.
- L28 _public prototype_ `UMovieGraphBurnInNode();`
- L31 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L32 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L33 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L40 _public prototype_ `TObjectPtr<UMovieGraphBurnInWidget> GetOrCreateBurnInWidget(UClass* WidgetClass, UWorld* InOwner);` — Gets an existing widget instance of type WidgetClass if one has been created. Otherwise, returns a new instance of WidgetClass with owner InOwner.
- L44 _public member_ `static const FString RendererName;` — `UE_DEPRECATED(5.7, "RendererName usage is deprecated, please use GetRendererName() instead.")`
- L47 _public member_ `static const FString DefaultBurnInWidgetAsset;` — The path to the default widget class that will be used for the burn-in.
- L50 _public member_ `uint8 bOverride_BurnInClass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L54 _public member_ `FSoftClassPath BurnInClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(MetaClass="/Script/MovieRenderPipelineCore.MovieGraphBurnInWidget", EditCondition="bOverride_BurnInClass"), Category="Widget Settings")` — The widget that the burn-in should use.
- L84 _private member_ `TMap<TObjectPtr<const UClass>, TObjectPtr<UMovieGraphBurnInWidget>> BurnInWidgetInstances;` — `UPROPERTY(Transient)` — Burn-in widget instances shared with all FMovieGraphBurnInPass instances, keyed by burn-in class.
- L88 _protected prototype_ `virtual TUniquePtr<FMovieGraphWidgetPass> GeneratePass() override;` — UMovieGraphWidgetRendererBaseNode Interface
- L92 _protected prototype_ `virtual void GatherOutputPassesImpl(UMovieGraphEvaluatedConfig* InConfig, TArray<FMovieGraphRenderDataIdentifier>& OutExpectedPasses) const override;` — UMovieGraphRenderPassNode Interface
- L93 _protected prototype_ `virtual void TeardownImpl() override;`

#### struct `UMovieGraphBurnInNode::FMovieGraphBurnInPass`  
`struct FMovieGraphBurnInPass final : public FMovieGraphWidgetPass`  
_L58-79_
- inherits: `FMovieGraphWidgetPass`
- desc: A burn-in pass for a specific render layer. Instances are stored on the UMovieGraphWidgetRendererBaseNode CDO.
- L60 _public prototype_ `virtual void Setup(TWeakObjectPtr<UMovieGraphDefaultRenderer> InRenderer, const FMovieGraphRenderPassLayerData& InLayer) override;`
- L61 _public prototype_ `virtual TSharedPtr<SWidget> GetWidget(UMovieGraphWidgetRendererBaseNode* InNodeThisFrame) override;`
- L62 _public prototype_ `virtual void Render(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;`
- L63 _public prototype_ `virtual int32 GetCompositingSortOrder() const override;`
- L64 _public prototype_ `virtual UMovieGraphWidgetRendererBaseNode* GetParentNode(UMovieGraphEvaluatedConfig* InConfig) const override;`
- L67 _public prototype_ `UClass* GetBurnInClass() const;` — Gets the burn-in class that this pass will be using.
- L70 _private prototype_ `TObjectPtr<UMovieGraphBurnInWidget> GetBurnInWidget(UMovieGraphWidgetRendererBaseNode* InNodeThisFrame) const;`
- L71 _private member_ `TSubclassOf<UMovieGraphBurnInWidget> CachedBurnInWidgetClass;`
- L78 _private member_ `FString RendererNodeInstanceName;` — If this is an output-specific burn-in (eg, just for JPG), the burn-in renderer node will have a specific instance name. That will identify it amongst all of the other output-specific burn-in nodes on the branch (if there are any others). If this is empty, then this pass doesn't represent an output-specific burn-in, and is for the legacy burn-in node.

#### class `UMovieGraphOutputBurnInNode`  
`class UMovieGraphOutputBurnInNode : public UMovieGraphBurnInNode`  
_L105-163_
- reflection: `UCLASS(MinimalAPI, Hidden, HideDropdown)`
- inherits: `UMovieGraphBurnInNode`
- desc: A node which generates a widget burn-in, rendered to a standalone image or composited on top of a render layer. This node is not meant to be added by the user directly. Instead, it's injected into the graph by a specific output node (eg, JPG). It can control which output type(s) write it out (see the OutputRestriction property).
- L110 _public prototype_ `UMovieGraphOutputBurnInNode() = default;`
- L113 _public prototype_ `virtual FString GetNodeInstanceName() const override;` — UMovieGraphSettingNode Interface
- L118 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive) const override;`
- L120 _public prototype_ `virtual bool GetNodeValidationErrors(const FName& InBranchName, const UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<FText>& OutValidationErrors) const override;`
- L124 _protected prototype_ `virtual TArray<FSoftClassPath> GetOutputTypeRestrictionsImpl() const override;`
- L125 _protected prototype_ `virtual FString GetRendererNameImpl() const override;`
- L128 _protected prototype_ `virtual FString GetFileNameFormatOverride() const override;` — UMovieGraphWidgetRendererBaseNode Interface
- L129 _protected prototype_ `virtual FString GetLayerNameOverride() const override;`
- L134 _public member_ `uint8 bOverride_OutputName : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L137 _public member_ `uint8 bOverride_FileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L140 _public member_ `uint8 bOverride_OutputRestriction : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L143 _public member_ `uint8 bOverride_LayerNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L150 _public member_ `FString OutputName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta=(EditCondition="bOverride_OutputName"))` — The name of the output that is associated with this burn-in (eg, "JPG"). Will be used as the instance name for the node, so it should be unique if multiple burn-in nodes need to co-exist in the same branch.
- L154 _public member_ `FSoftClassPath OutputRestriction;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta=(EditCondition="bOverride_OutputRestriction"))` — The type(s) of nodes that can write out this burn-in. If no output types are specified, all active output types will write out the burn-in.
- L158 _public member_ `FString FileNameFormat = "{s` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta=(EditCondition="bOverride_FileNameFormat"))` — If not composited, this is the format string used for the file name that the burn-in is written to.
- L162 _public member_ `FString LayerNameFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta=(EditCondition="bOverride_LayerNameFormat"))` — For multi-layer output formats, this is the format string used to generate the layer name.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphCameraNode.h` (Public)


#### class `UMovieGraphCameraSettingNode`  
`class UMovieGraphCameraSettingNode : public UMovieGraphSettingNode`  
_L13-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- desc: A node which configures global camera settings that are shared among all renders.
- L18 _public function_ `UMovieGraphCameraSettingNode() : ShutterTiming(EMoviePipelineShutterTiming::FrameCenter) , OverscanPercentage(0.f) , bRenderAllCameras(false)`
- L24 _public function_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override`
- L25 _public prototype_ `virtual void GetFormatResolveArgs(FMovieGraphResolveArgs& OutMergedFormatArgs, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier) const override;`
- L28 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L29 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L30 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L31 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L36 _public member_ `uint8 bOverride_ShutterTiming : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L39 _public member_ `uint8 bOverride_OverscanPercentage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L43 _public member_ `uint8 bOverride_bRenderAllCameras : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L70 _public member_ `EMoviePipelineShutterTiming ShutterTiming;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bOverride_ShutterTiming"))` — Shutter Timing allows you to bias the timing of your shutter angle to either be before, during, or after a frame. When set to FrameClose, it means that the motion gathered up to produce frame N comes from before and right up to frame N. When set to FrameCenter, the motion represents half the time before the frame and half the time after the frame. When set to FrameOpen, the motion represents the time from Frame N onwards. As an example, here are 4 temporal subsamples with 180 degree shutter angle (50% motion blur) between frames A & B: FrameClose F-------F-------F ----1234--------- ----AAAA--------- FrameCenter F-------F-------F ------1234------- ------AABB------- FrameOpen F-------F-------F --------1234----- --------BBBB-----
- L87 _public member_ `float OverscanPercentage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Overscan Percentage Override", UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "100"), Category = "Settings", meta = (EditCondition = "bOverride_OverscanPercentage"))` — Overscan percent enables rendering additional pixels beyond the current target resolution, and can be used in conjunction with the EXR output format to add post-processing effects such as lens distortion. Please note that using this feature may cause the render to appear different in some scenarios (for example, auto-exposure may be impacted due to the increased FoV picking up additional lighting). With EXR outputs, the non-overscanned pixel data is contained in the EXR "display window", and the overscanned pixel data is contained in the "data window". For example, a 1920x1080 render with 10% overscan will result in a 2112x1188 render; the display window will be 1920x1080, and the data window will be 2112x1188. For all other formats, the pixels are cropped to the original target resolution (ie, no extra pixel data is included). Note: This uses values in the [0-100] range, and not [0-1] like the preset system, to bring it in-line with other usages of overscan in the engine (like nDisplay).
- L98 _public member_ `bool bRenderAllCameras;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bOverride_bRenderAllCameras"))` — If enabled Movie Render Queue will examine your Level Sequence for additional cameras and create an additional render for each renderer for that camera. The Camera Cut Track/Section is still used to determine the range of time to render, and then all Camera Actors that are in the level sequence adjacent to the Camera Cut Track will be considered for rendering. They are expected to exist the entire time and do not support rendering sub-ranges. This increases render duration (100% per camera) and has increased VRAM/RAM requirements. However all cameras are rendered on the same engine tick so they should all see a consistent view of the world which can be useful for things like particle effects, etc.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphClassPropertyModifier.h` (Public)


#### struct `FMovieGraphPropertyReference`  
`struct FMovieGraphPropertyReference`  
_L16-92_
- reflection: `USTRUCT(BlueprintType)`
- desc: A scripting-friendly representation of a property on an AActor or UActorComponent.
- L21 _public prototype_ `FMovieGraphPropertyReference() = default;`
- L27 _public prototype_ `FMovieGraphPropertyReference( const TObjectPtr<UClass>& InPropertyClass, const TSubclassOf<UActorComponent>& InComponentClass, const FName& InPropertyName, FProperty* InProperty = nullptr);` — Providing the FProperty is optional. Providing it just bypasses the lookup of the FProperty that will occur if only the property name and class/component are provided.
- L34 _public prototype_ `EMovieGraphValueType GetValueType() const;` — Gets the value type of the referenced property.
- L37 _public prototype_ `UObject* GetValueTypeObject() const;` — Gets the value type object of the referenced property (for objects, structs, and enums).
- L40 _public prototype_ `FProperty* GetProperty() const;` — Gets the FProperty that backs this property reference.
- L43 _public prototype_ `FName GetPropertyName() const;` — Gets the name of the property that this reference refers to.
- L46 _public prototype_ `TSubclassOf<AActor> GetPropertyClass() const;` — Gets the actor class that this property exists in. If the property exists in a component, this is the class that the component belongs to.
- L49 _public prototype_ `TSubclassOf<UActorComponent> GetComponentClass() const;` — Gets the class of the component that the property exists in. Can be nullptr if the property does not exist in a component.
- L52 _public prototype_ `bool IsValidProperty() const;` — Determines if this property reference points to a valid property.
- L55 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Called by TStructOpsTypeTraits
- L63 _public member_ `FName AuxPropertyName;` — `UPROPERTY(BlueprintReadWrite, Category = "Property")` — An additional property name which may be used for other purposes. Does not affect any internal FMovieGraphPropertyReference functionality and can be left empty if not needed.
- L68 _private member_ `TSubclassOf<AActor> PropertyClass = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))` — The actor class that the property exists in. If the property exists within a component, this is the class that the component exists in.
- L72 _private member_ `TSubclassOf<UActorComponent> ComponentClass = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))` — The UActorComponent class that the property exists in, or nullptr if the property does not exist in a component.
- L76 _private member_ `FName PropertyName;` — `UPROPERTY(BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))` — The name of the property within either the class or the component class.
- L79 _private member_ `FProperty* Property = nullptr;` — Calculated (or optionally provided): The resolved FProperty that lives on the PropertyClass or ComponentClass.
- L83 _private member_ `EMovieGraphValueType ValueType = EMovieGraphValueType::None;` — `UPROPERTY(BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))` — Calculated: The value type of the referenced property.
- L87 _private member_ `TObjectPtr<UObject> ValueTypeObject = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))` — Calculated: The value type object of the referenced property (for objects, structs, and enums).
- L91 _private prototype_ `void PopulateDerivedData();` — Calculates and caches property-related information so it doesn't need to be constantly re-derived.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieGraphPropertyReference> : public TStructOpsTypeTraitsBase2<FMovieGraphPropertyReference>`  
_L95-101_
- inherits: `TStructOpsTypeTraitsBase2<FMovieGraphPropertyReference>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L98-100_

#### class `UMovieGraphPropertyModifier`  
`class UMovieGraphPropertyModifier final : public UMovieGraphCollectionModifier`  
_L111-193_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphCollectionModifier`
- desc: Modifies properties on specific actor or component type(s). The properties that should be modified are added via MovieGraphPropertyReference objects via AddProperties(). Note that the properties are matched to their EXACT AActor and/or UActorComponent class within the property reference (ie, subclass checks are not made).
- L116 _public prototype_ `UMovieGraphPropertyModifier();`
- L119 _public prototype_ `virtual void ApplyModifier(const UWorld* World) override;`
- L120 _public prototype_ `virtual void UndoModifier() override;`
- L121 _public prototype_ `virtual FText GetModifierName() override;`
- L129 _public prototype_ `static FMovieGraphPropertyReference MakePropertyReference( UClass* InPropertyClass, const TSubclassOf<UActorComponent>& InComponentClass, const FName& InPropertyName);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Scripting helper that makes unreal.MovieGraphPropertyReference instances for use with this node. Little use outside of scripting. See FMovieGraphPropertyReference documentation for further details about the property reference.
- L143 _public prototype_ `void AddProperties(const TArray<FMovieGraphPropertyReference>& InProperties);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Adds the properties which should be modified. The property reference can: 1) Specify an actor without its component to modify an actor's property. 2) Specify a component with an actor to modify that component's property only on specific actor types. 3) Specify a component without an actor type to modify that component property on all actors it exists on.
- L147 _public prototype_ `static FName GetPropertyNameForSettingCustomValue(const FMovieGraphPropertyReference& InPropertyReference);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets the property name that needs to be used with GetPropertiesForSettingValues() to set a "Custom" property value.
- L155 _public prototype_ `UMovieGraphFixedValueView* GetPropertiesForSettingValues();` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets a value view which allows property values to be set. Properties cannot be added/removed with this view. Note that in order to modify a property value, you must use the property name provided by GetPropertyNameForSettingCustomValue().
- L162 _private prototype_ `static FName GetInternalPropertyName(const FMovieGraphPropertyReference& InPropertyReference);` — Gets the unique internal property name for the given property reference. This property name is used to track the property within the internal property bags.
- L166 _private member_ `TMap<TSubclassOf<AActor>, TArray<FMovieGraphPropertyReference>> PropertiesToModifyByActorClass;` — All of the properties that will be modified by this modifier.
- L170 _private member_ `FInstancedPropertyBag UpdatedPropertyValues;` — `UPROPERTY(Transient)` — Holds all of the properties and their associated values which will be set when the modifier is applied.
- L174 _private member_ `FInstancedPropertyBag PreviousPropertyValues;` — `UPROPERTY(Transient)` — Holds all of the values of the properties prior to modification.
- L178 _private member_ `TObjectPtr<UMovieGraphMutableValueView> UpdatedPropertyValuesView = nullptr;` — `UPROPERTY(Transient)` — View for the UpdatedPropertyValues property bag.
- L182 _private member_ `TObjectPtr<UMovieGraphMutableValueView> PreviousPropertyValuesView = nullptr;` — `UPROPERTY(Transient)` — View for the PreviousPropertyValues property bag.
- L189 _private member_ `TObjectPtr<UMovieGraphFixedValueView> UserFacingPropertiesView = nullptr;` — `UPROPERTY(Transient)` — The property view that's user-facing and does not allow adding/removing properties (so this node can enforce how properties are added/removed internally). Created lazily via GetPropertiesForSettingValues().
- L192 _private member_ `TArray<TPair<UObject*, FMovieGraphPropertyReference>> ModifiedProperties;` — The actors and their properties that had values modified. Cached so the actor does not have to be re-resolved when undoing the modifier.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L99 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonc1e150200103`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphCollectionNode.h` (Public)


#### class `UMovieGraphCollectionNode`  
`class UMovieGraphCollectionNode : public UMovieGraphSettingNode`  
_L19-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- desc: A collection node specifies an interface for doing dynamic scene queries for actors in the world. Collections work in tandem with UMovieGraphModifiers to select which actors the modifiers should be run on.
- L24 _public prototype_ `UMovieGraphCollectionNode();`
- L27 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L28 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L29 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L30 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L33 _public prototype_ `virtual FString GetNodeInstanceName() const override;`
- L36 _protected prototype_ `virtual void RegisterDelegates() override;`
- L40 _public member_ `uint8 bOverride_Collection : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))` — The collection is customized in the details panel, so the override should always be enabled
- L43 _public member_ `TObjectPtr<UMovieGraphCollection> Collection;` — `UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "General", meta=(EditCondition="bOverride_Collection"))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphCommandLineEncoderNode.h` (Public)


#### class `UMovieGraphCommandLineEncoderNode`  
`class UMovieGraphCommandLineEncoderNode : public UMovieGraphSettingNode, public IMovieGraphPostRenderNode`  
_L18-207_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode,IMovieGraphPostRenderNode`
- desc: A node which kicks off an encode process after all renders have completed.
- L23 _public prototype_ `UMovieGraphCommandLineEncoderNode();`
- L26 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L27 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L28 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L29 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L33 _public prototype_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override;` — UMovieGraphNode interface
- L37 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;` — UMovieGraphSettingNode interface
- L41 _public prototype_ `void StartEncodingProcess(TArray<FMovieGraphRenderOutputData>& InGeneratedData, const bool bInIsShotEncode);` — Begins the encode process (as long as there are no validation errors).
- L44 _public prototype_ `virtual void BeginExport(UMovieGraphPipeline* InMoviePipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph) override;` — IMovieGraphPostRenderNode interface
- L45 _public prototype_ `virtual void BeginShotExport(UMovieGraphPipeline* InMoviePipeline) override;`
- L46 _public prototype_ `virtual bool HasFinishedExporting() override;`
- L51 _public member_ `uint8 bOverride_FileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L54 _public member_ `uint8 bOverride_bDeleteSourceFiles : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L57 _public member_ `uint8 bOverride_bSkipEncodeOnRenderCanceled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L60 _public member_ `uint8 bOverride_VideoCodec : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L63 _public member_ `uint8 bOverride_AudioCodec : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L66 _public member_ `uint8 bOverride_OutputFileExtension : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L69 _public member_ `uint8 bOverride_CommandLineFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L72 _public member_ `uint8 bOverride_VideoInputStringFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L75 _public member_ `uint8 bOverride_AudioInputStringFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L78 _public member_ `uint8 bOverride_EncodeSettings : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L81 _public member_ `uint8 bOverride_bRetainInputTextFiles : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L90 _public member_ `FString FileNameFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta=(EditCondition="bOverride_FileNameFormat", MrgTokenAutocomplete))` — File name format string override. If specified it will override the FileNameFormat from the Output setting. If {shot_name} or {camera_name} is used, encoding will begin after each shot finishes rendering. Can be different from the main one in the Output setting so you can render out frames to individual shot folders but encode to one file.
- L94 _public member_ `bool bDeleteSourceFiles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta=(EditCondition="bOverride_bDeleteSourceFiles"))` — Whether the source files should be deleted on disk after encoding.
- L98 _public member_ `bool bSkipEncodeOnRenderCanceled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta=(EditCondition="bOverride_bSkipEncodeOnRenderCanceled"))` — Whether encoding should be skipped on frames produced if rendering was canceled before finishing.
- L102 _public member_ `FString VideoCodec;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta=(EditCondition="bOverride_VideoCodec"))` — Which video codec should we use? Run 'MovieRenderPipeline.DumpCLIEncoderCodecs' for options.
- L106 _public member_ `FString AudioCodec;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta=(EditCondition="bOverride_AudioCodec"))` — Which audio codec should we use? Run 'MovieRenderPipeline.DumpCLIEncoderCodecs' for options.
- L110 _public member_ `FString OutputFileExtension;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta=(EditCondition="bOverride_OutputFileExtension"))` — Extension for the output files. Many encoders use this to determine the container type they are placed in. Should be without dot, ie: "webm".
- L114 _public member_ `FString CommandLineFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command Line Arguments", meta=(EditCondition="bOverride_CommandLineFormat", MultiLine=true))` — The format string used when building the final command line argument to launch.
- L118 _public member_ `FString VideoInputStringFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command Line Arguments", meta=(EditCondition="bOverride_VideoInputStringFormat", MultiLine=true))` — Format string used for each video input.
- L122 _public member_ `FString AudioInputStringFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command Line Arguments", meta=(EditCondition="bOverride_AudioInputStringFormat", MultiLine=true))` — Format string used for each audio input.
- L126 _public member_ `FString EncodeSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command Line Arguments", meta=(EditCondition="bOverride_EncodeSettings", MultiLine=true))` — Additional flags used for specifying encode quality.
- L130 _public member_ `bool bRetainInputTextFiles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta=(EditCondition="bOverride_bRetainInputTextFiles"))` — Retain the intermediate audio and video input text files that are passed to the encoder.
- L160 _private prototype_ `bool AreSettingsValid(TArray<FText>& OutErrors) const;` — Returns true if all project and node settings are valid. Returns false if there are validation errors (and provides the errors in OutErrors).
- L163 _private prototype_ `void OnTick();` — Manages the actively running encode jobs, potentially aborting them if pipeline needs to shut down.
- L166 _private prototype_ `bool NeedsPerShotFlushing() const;` — Returns true if there should be one export per shot, else false.
- L172 _private prototype_ `TMap<FMovieGraphRenderDataIdentifier, FEncoderParams> GenerateRenderLayerEncoderParams(TArray<FMovieGraphRenderOutputData>& InGeneratedData, const bool bInIsShotEncode) const;` — Generates encoder parameters for each shot (using only the first render layer that's found within the shot). Will only generate one set of params if bInIsShotEncode is set to false (ie, this is a sequence encode).
- L175 _private prototype_ `FString GetResolvedOutputFilename(const FMovieGraphRenderDataIdentifier& RenderIdentifier, const TWeakObjectPtr<UMoviePipelineExecutorShot>& Shot, const FString& FileNameFormatString) const;` — Gets the path to the file that the encode process should write to.
- L181 _private prototype_ `void GenerateTemporaryEncoderInputFiles(const FEncoderParams& InParams, TArray<FString>& OutVideoInputFilePaths, TArray<FString>& OutAudioInputFilePaths) const;` — Generates the temporary video and audio input files that will be passed to the encoder process. These inputs typically contain a list of the files (eg, image files) that will be used in the encode process.
- L184 _private prototype_ `FString BuildEncoderCommand(const FEncoderParams& InParams, TArray<FString>& InVideoInputFilePaths, TArray<FString>& InAudioInputFilePaths) const;` — Generates the encoder command that should be executed.
- L187 _private prototype_ `void LaunchEncoder(const FEncoderParams& InParams);` — Starts the actual encoder process. After the process is started, it will be monitored in OnTick().
- L191 _private prototype_ `template<typename T> T* GetSettingOnBranch(const bool bIncludeCDOs = true, const bool bExactMatch = true) const;` — Gets a setting on the branch that this node exists on.
- L194 _private prototype_ `TObjectPtr<UMovieGraphEvaluatedConfig> GetEvaluatedConfig() const;` — Determines the appropriate evaluated config to use for the current context (primary job encode or shot based encode).
- L200 _private member_ `static inline TArray<FActiveJob> ActiveEncodeJobs;` — Encode jobs which are currently running.
- L203 _private member_ `static inline TWeakObjectPtr<UMovieGraphPipeline> CachedPipeline;` — The pipeline that started the export.
- L206 _private member_ `static inline TObjectPtr<UMovieGraphEvaluatedConfig> PrimaryJobEvaluatedGraph;` — The job-level graph that should be accessed during execution of the node. Do not access the graph from the pipeline as it will be invalid.

#### struct `UMovieGraphCommandLineEncoderNode::FActiveJob`  
`struct FActiveJob`  
_L133-146_
- L135 _public function_ `FActiveJob() : ReadPipe(nullptr) , WritePipe(nullptr)`
- L140 _public member_ `FProcHandle ProcessHandle;`
- L141 _public member_ `void* ReadPipe;`
- L142 _public member_ `void* WritePipe;`
- L145 _public member_ `TArray<FString> FilesToDelete;` — Files that should be deleted after the process has finished.

#### struct `UMovieGraphCommandLineEncoderNode::FEncoderParams`  
`struct FEncoderParams`  
_L148-154_
- L150 _public member_ `FStringFormatNamedArguments NamedArguments;`
- L151 _public member_ `TMap<FString, TArray<FString>> FilesByExtensionType;`
- L152 _public member_ `TWeakObjectPtr<UMoviePipelineExecutorShot> Shot;`
- L153 _public member_ `FMovieGraphRenderDataIdentifier RenderDataIdentifier;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphDebugNode.h` (Public)


#### class `UMovieGraphDebugSettingNode`  
`class UMovieGraphDebugSettingNode : public UMovieGraphSettingNode`  
_L12-113_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- desc: A node which configures various debug settings that may be useful when debugging an issue.
- L17 _public prototype_ `UMovieGraphDebugSettingNode() = default;`
- L19 _public function_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override`
- L22 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L23 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L30 _public member_ `uint8 bOverride_bCaptureFramesWithRenderDoc : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L33 _public member_ `uint8 bOverride_RenderDocCaptureFrame : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L36 _public member_ `uint8 bOverride_bCaptureUnrealInsightsTrace : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L39 _public member_ `uint8 bOverride_UnrealInsightsTraceFileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L42 _public member_ `uint8 bOverride_bCaptureFramesWithDumpGpu : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L45 _public member_ `uint8 bOverride_DumpGpuCaptureFrameStart : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L48 _public member_ `uint8 bOverride_DumpGpuCaptureFrameStop : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L51 _public member_ `uint8 bOverride_DumpGpuCaptureFilePathFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L54 _public member_ `uint8 bOverride_DumpGpuCaptureUnifiedPassResourceFilters : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L61 _public member_ `bool bCaptureFramesWithRenderDoc;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderDoc", meta = (EditCondition = "bOverride_bCaptureFramesWithRenderDoc"))` — If true, automatically trigger RenderDoc to capture rendering information. RenderDoc plugin must be enabled, and the editor must have been launched with -AttachRenderDoc. Resulting capture will be in /Saved/RenderDocCaptures.
- L67 _public member_ `int32 RenderDocCaptureFrame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderDoc", meta = (EditCondition = "bOverride_RenderDocCaptureFrame"))` — If bCaptureFramesWithRenderDoc is true, which frame (on the root Sequencer time line) should we capture data for?
- L73 _public member_ `bool bCaptureUnrealInsightsTrace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unreal Insights", meta = (EditCondition = "bOverride_bCaptureUnrealInsightsTrace"))` — If true, automatically capture an Unreal Insights trace file for the duration of the render.
- L80 _public member_ `FString UnrealInsightsTraceFileNameFormat = TEXT("{se` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unreal Insights", meta = (EditCondition = "bOverride_UnrealInsightsTraceFileNameFormat", MrgTokenAutocomplete))` — If bCaptureUnrealInsightsTrace is true, name of the UnrealInsights trace. Resulting capture will be in the global Output Directory for the job.
- L86 _public member_ `bool bCaptureFramesWithDumpGpu;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DumpGPU", meta = (EditCondition = "bOverride_bCaptureFramesWithDumpGpu"))` — If true, automatically trigger DumpGPU to capture rendering information.
- L92 _public member_ `int32 DumpGpuCaptureFrameStart = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DumpGPU", meta = (EditCondition = "bOverride_DumpGpuCaptureFrameStart"))` — If bCaptureFramesWithDumpGpu is true, from which included frame (on the root Sequencer time line) start index should we capture? No start bound if negative.
- L98 _public member_ `int32 DumpGpuCaptureFrameStop = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DumpGPU", meta = (EditCondition = "bOverride_DumpGpuCaptureFrameStop"))` — If bCaptureFramesWithDumpGpu is true, up to which excluded frame (on the root Sequencer time line) stop index should we capture? No stop bound if negative.
- L104 _public member_ `FString DumpGpuCaptureFilePathFormat = TEXT("{se` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DumpGPU", meta = (EditCondition = "bOverride_DumpGpuCaptureFilePathFormat", MrgTokenAutocomplete))` — If bCaptureFramesWithDumpGpu is true, name of the output directory for the capture (related to frame output directory).
- L112 _public member_ `FString DumpGpuCaptureUnifiedPassResourceFilters = TEXT("*")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DumpGPU", meta = (EditCondition = "bOverride_DumpGpuCaptureUnifiedPassResourceFilters"))` — If bCaptureFramesWithDumpGpu is true, wildcard enabled filters to apply to the path of the passes to dump. Syntax: Separate pass names to resources with "@". Filter multiple passes:resources by separating them with "|" Example: "*TileClassificationMark*@StochasticLighting.EncodedReprojectionVector|*TemporalAccumulation*@MegaLights.ResolvedDiffuseLighting"

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphExecuteScriptNode.h` (Public)


#### class `UMovieGraphScriptBase`  
`class UMovieGraphScriptBase : public UObject`  
_L50-172_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, Abstract)`
- inherits: `UObject`
- desc: This is the base class used for writing scripts that can be executed as part of a Movie Graph Pipeline. After creating a UMovieGraphExecuteScriptNode (named 'Execute Script' in the UI) in your Movie Graph Configuration asset, and choosing the type of your script, an instance will be created when the job starts. This instance will persist until the end of the job. The instance will receive callbacks during the render which contain data that you can manipulate with your script, or data that was generated by the pipeline. This can be implemented in C++, Blueprints, or Python. For C++ you can use standard inheritance. Blueprints should use the MovieGraphScriptBase class. For Python, you need to write a UClass implemented in Python. This has slightly different syntax than standard Python (see below). In this example, create a "Python" folder in your Content folder. Then create a file named "MovieGraphPipelineScriptExample.py", and a file named "init_unreal.py" In "init_unreal.py" add "import MovieGraphPipelineScriptExample" as the contents. In "MovieGraphPipelineScriptExample.py" use the following: import unreal @unreal.uclass() class MovieGraphPipelineScriptExample(unreal.MovieGraphScriptBase): @unreal.ufunction(override=True) def on_job_start(self, in_job_copy): super().on_job_start(in_job_copy) unreal.log("OnJobStart") Save and restart Unreal Editor, then create a Movie Graph Configuration with an Execute Script Node, and set it to run MovieGraphPipelineScriptExample. When the 
- L80 _public prototype_ `void OnJobStart(UMoviePipelineExecutorJob* InJobCopy);` — `UFUNCTION(BlueprintNativeEvent, Category = "Movie Graph")` — This callback is called very early on in the Movie Graph Pipeline, before data is read from the job. The provided job is a duplicate of the job defined in the UMoviePipelineQueue, allowing you to make changes to the job without worrying about restoring them at the end of a render. Additionally, the Graph Configuration assets (for both the Primary configuration, and shot overrides) have been duplicated to allow mutation of the graph configuration without worrying about leaking these changes to the assets on disk. Other pointers to external packages (such as the Level Sequence on the job) have not been duplicated though, so be aware that changes to these assets will leak, unless you restore the changes in OnJobFinished. OnJobFinished will be called even if the job is canceled. For C++ implementations override `virtual void OnJobStart_Implementation(UMoviePipelineExecutorJob* InJobCopy) override` For Python implementations override @unreal.ufunction(override=True) def on_job_start(self, inJobCopy): super().on_job_start(inJobCopy) @param InJobCopy - A copy of the job being rendered with this graph config, with its Graph Preset configurations also copied to avoid accidental mutation of assests on disk.
- L81 _public function_ `virtual void OnJobStart_Implementation(UMoviePipelineExecutorJob* InJobCopy)`
- L107 _public prototype_ `void OnJobFinished(UMoviePipelineExecutorJob* InJobCopy, const FMoviePipelineOutputData& InOutputData);` — `UFUNCTION(BlueprintNativeEvent, Category = "Movie Graph")` — This callback is called at the very end of the Movie Graph Pipeline, right before shutting down. The files specified by the OutputData should have been written to disk by this point. This function will get called both in the case of a successful job, or one canceled by the user. You can use OutputData.bSuccess to determine if the render was successfuly completed. For C++ implementations override `virtual void OnJobFinished_Implementation(UMoviePipelineExecutorJob* InJobCopy, const FMovieGraphPipelineOutputData& OutputData) override` For Python implementations override @unreal.ufunction(override=True) def on_job_finished(self, inJobCopy, inOutputData): super().on_job_finished(inJobCopy, inOutputData) @param InJobCopy - A copy of the job being rendered with this graph config, with its Graph Preset configurations also copied to avoid accidental mutation of assests on disk. @param InOutputData - Information about the files generated during this render. Contains a flag (bSuccess) for checking if the job was successful or not, and contains a list of render layers, and the files written to disk for that render layer. Contains data for all shots rendered up to this point.
- L108 _public function_ `virtual void OnJobFinished_Implementation(UMoviePipelineExecutorJob* InJobCopy, const FMoviePipelineOutputData& InOutputData )`
- L127 _public prototype_ `void OnShotStart(UMoviePipelineExecutorJob* InJobCopy, UMoviePipelineExecutorShot* InShotCopy);` — `UFUNCTION(BlueprintNativeEvent, Category = "Movie Graph")` — This is similar to OnJobStart but called before a shot is set up. This is only called if IsPerShotCallbackNeeded() returns true. For C++ implementations override `virtual void OnShotStart_Implementation(UMoviePipelineExecutorJob* InJobCopy,  UMoviePipelineExecutorShot* InShotCopy) override` For Python implementations override @unreal.ufunction(override=True) def on_shot_start(self, inJobCopy, inShotCopy): super().on_shot_start(inJobCopy, inShotCopy) @param InJobCopy - A copy of the job being rendered with this graph config, with its Graph Preset configurations also copied to avoid accidental mutation of assests on disk. @param InShotCopy - A copy of the shot that is about to be started.
- L128 _public function_ `virtual void OnShotStart_Implementation(UMoviePipelineExecutorJob* InJobCopy, UMoviePipelineExecutorShot* InShotCopy)`
- L150 _public prototype_ `void OnShotFinished(UMoviePipelineExecutorJob* InJobCopy, UMoviePipelineExecutorShot* InShotCopy, const FMoviePipelineOutputData& OutputData);` — `UFUNCTION(BlueprintNativeEvent, Category = "Movie Graph")` — This is similar to OnJobFinished but called after a shot is completed. This is only called if IsPerShotCallbackNeeded() returns true. For C++ implementations override `virtual void OnShotFinished_Implementation(UMoviePipelineExecutorJob* InJobCopy,  UMoviePipelineExecutorShot* InShotCopy, const FMovieGraphPipelineOutputData& InOutputData) override` For Python implementations override @unreal.ufunction(override=True) def on_shot_finished(self, inJobCopy, inShotCopy, inOutputData): super().on_shot_finished(inJobCopy, inShotCopy, inOutputData) @param InJobCopy - A copy of the job being rendered with this graph config, with its Graph Preset configurations also copied to avoid accidental mutation of assests on disk. @param InShotCopy - A copy of the shot that was just finished. @param InOutputData - The data generated by this shot. Only contains the files rendered for this particular shot, not all files generated by the movie render (use OnJobFinished for that).
- L151 _public function_ `virtual void OnShotFinished_Implementation(UMoviePipelineExecutorJob* InJobCopy, UMoviePipelineExecutorShot* InShotCopy, const FMoviePipelineOutputData& OutputData)`
- L167 _public prototype_ `bool IsPerShotCallbackNeeded() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Movie Graph")` — If you return true here the system will stall at the end of every shot and wait until all files have been written to disk before invoking this callback. This can increase render times but is important if you need to operate on the files on disk as part of the callback. For C++ implementations override `virtual bool IsPerShotCallbackNeeded_Implementation() const override` For Python implementations override @unreal.ufunction(override=True) def is_per_shot_callback_needed(): return False
- L168 _public function_ `virtual bool IsPerShotCallbackNeeded_Implementation() const`

#### enum `EMovieGraphExecuteScriptMode`  
`enum class EMovieGraphExecuteScriptMode : uint8`  
_L176-186_
- reflection: `UENUM(BlueprintType)`
- desc: Designates the types of builds a script (specified in an Execute Script node) is allowed to execute in.
- L179 _public enumerator_ `EditorOnly = 0` — The script should only run in an editor context.
- L182 _public enumerator_ `EditorAndRuntime = 1` — The script can run both in the editor and in a runtime build.
- L185 _public enumerator_ `Count UMETA(Hidden)` — Invalid value, keep as the last entry in the enum.

#### class `UMovieGraphExecuteScriptNode`  
`class UMovieGraphExecuteScriptNode : public UMovieGraphSettingNode`  
_L195-280_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- desc: This node allows users to run code before and after a movie graph is being executed. Example use cases would be to run custom logic that overrides the output directory, or to trigger an event after a shot finishes. These bits of script can be implemented in either C++, or in Python (as a UClass) because we don't serialize the object and only create it at runtime during the render. See UMovieGraphScriptBase for details.
- L200 _public prototype_ `UMovieGraphExecuteScriptNode() = default;`
- L202 _public function_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override`
- L203 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L206 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L207 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L208 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L209 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L213 _public prototype_ `UMovieGraphScriptBase* AllocateScriptInstance() const;` — Allocates an instance of the script type specified on the node. Will return nullptr if the script type is invalid.
- L217 _protected prototype_ `virtual void PostLoad() override;`
- L220 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L227 _public member_ `uint8 bOverride_Script: 1;` — `UE_DEPRECATED(5.8, "Use the bOverride_EditorOnlyScript property or bOverride_EditorAndRuntimeScript property instead.")` — `UPROPERTY(BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle, DeprecatedProperty, DeprecationMessage = "Use the bOverride_EditorOnlyScript property or bOverride_EditorAndRuntimeScript property instead."))`
- L231 _public member_ `uint8 bOverride_EditorOnlyScript : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L235 _public member_ `uint8 bOverride_EditorAndRuntimeScript : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L238 _public member_ `uint8 bOverride_Mode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L248 _public member_ `FSoftClassPath Script;` — `UE_DEPRECATED(5.8, "Use the EditorOnlyScript property or EditorAndRuntimeScript property instead.")` — `UPROPERTY(BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bOverride_Script", MetaClass = "/Script/MovieRenderPipelineCore.MovieGraphScriptBase", DeprecatedProperty, DeprecationMessage = "Use the EditorOnlyScript property or EditorAndRuntimeScript property instead."))` — Which script should this node instantiate? The class will be instantiated when the job starts, and then different functions will be called on that instance throughout the life-time of the movie render. Scripts can be implemented in Python or C++, see MovieGraphExecuteScriptNode.h for more details.
- L252 _public member_ `EMovieGraphExecuteScriptMode Mode = EMovieGraphExecuteScriptMode::EditorOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bOverride_Mode"))` — The context that this script is allowed to execute in.
- L266 _public member_ `FSoftClassPath EditorOnlyScript;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", DisplayName = "Editor-Only Script", meta = (EditCondition = "bOverride_EditorOnlyScript", MetaClass = "/Script/MovieRenderPipelineCore.MovieGraphScriptBase"))` — The script that this node should run. The script will be created when the job starts, and different functions will be called on the script throughout the lifetime of the render. Scripts can be implemented in Python, Blueprints, or C++; see MovieGraphExecuteScriptNode.h for more details. Editor-only scripts will run in editor-based renders and not runtime builds (if attempting to use it in a runtime build, the script will not execute, and a warning will be logged). This is mainly intended for typical MRG renders using a Python-based script (but the script can be C++ or Blueprint-based as well). Using this script type allows the Asset Referencing Restrictions plugin to properly detect that this script will not execute in a runtime build.
- L279 _public member_ `FSoftClassPath EditorAndRuntimeScript;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", DisplayName = "Editor + Runtime Script", meta = (EditCondition = "bOverride_EditorAndRuntimeScript", MetaClass = "/Script/MovieRenderPipelineCore.MovieGraphScriptBase"))` — The script that this node should run. The script will be created when the job starts, and different functions will be called on the script throughout the lifetime of the render. Scripts can be implemented in Python, Blueprints, or C++; see MovieGraphExecuteScriptNode.h for more details. Editor and Runtime scripts will run both in the editor and in runtime builds. Note that if a Python-based script type is being used in a runtime build, the Asset Referencing Restrictions plugin will flag an issue. This script type is mostly intended for use with Blueprints and C++-based scripts.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphFileOutputNode.h` (Public)


#### class `UMovieGraphFileOutputNode`  
`class UMovieGraphFileOutputNode : public UMovieGraphSettingNode`  
_L19-115_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMovieGraphSettingNode`
- desc: The UMovieGraphFileOutputNode node defines a output file format that MRQ may place produced render data into. At runtime, the individual pieces of render data will be generated by the Movie Graph Renderer, and then all data will be collected into a single datastructure by the FMovieGraphOutputMerger before being passed back into the main Movie Graph Pipeline. Once this happens, the CDOs deriving from UMovieGraphFileOutputNode will be given a pointer to the information for the whole frame, so they can decide what to do with it. There are potentially multiple output formats at once (such as exr and jpeg).
- L23 _public prototype_ `UMovieGraphFileOutputNode() = default;`
- L30 _public function_ `void OnReceiveImageData(UMovieGraphPipeline* InPipeline, UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, const TSet<FMovieGraphRenderDataIdentifier>& InMask)` — This is called by the Game Thread containing the final output data for a given output frame. InRawFrameData contains a list of all of the data generated for this output frame, and InMask specifies which render layers within InRawFrameData should actually be written to disk by this output node.
- L36 _public function_ `void OnAllFramesSubmitted(UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph)` — This is called when the pipeline has finished rendering all shots, and the sequence export process has not begun yet. See OnAllShotFramesSubmitted() for a method that is called when an individual shot has finished rendering.
- L41 _public function_ `void OnAllFramesFinalized(UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph)` — This is called when the pipeline has finished rendering all shots, and the sequence export process is finishing up.
- L48 _public function_ `void OnAllShotFramesSubmitted(UMovieGraphPipeline* InPipeline, const UMoviePipelineExecutorShot* InShot, TObjectPtr<UMovieGraphEvaluatedConfig>& InShotEvaluatedGraph, const bool bFlushToDisk = false)` — This is called when a shot has finished rendering its last frame, and the shot export process has not begun yet. If bFlushToDisk is true, all files this node is generating for the current shot should be written to disk before returning. See OnAllFramesSubmitted() for a method that is called after all shots have finished rendering.
- L51 _public function_ `bool IsFinishedWritingToDisk() const` — Returns whether this node has finished writing all of its files to disk yet.
- L54 _public function_ `virtual TArray<FMovieGraphPinProperties> GetInputPinProperties() const override`
- L61 _public function_ `virtual TArray<FMovieGraphPinProperties> GetOutputPinProperties() const override`
- L70 _public function_ `virtual FText GetMenuCategory() const override`
- L79 _public prototype_ `virtual FText GetBasicConfigShortDisplayName() const;` — Short display name for use in Basic config toggle buttons (e.g., "EXR", "PNG", etc). Return empty FText to exclude this output type from the Basic config UI.
- L83 _public member_ `uint8 bOverride_FileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L87 _public member_ `FString FileNameFormat = "{s` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output", meta=(EditCondition="bOverride_FileNameFormat", MrgTokenAutocomplete))` — What format string should the final files use? Can include folder prefixes, and format string ({shot_name}, etc.)
- L90 _protected function_ `virtual void OnReceiveImageDataImpl(UMovieGraphPipeline* InPipeline, UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, const TSet<FMovieGraphRenderDataIdentifier>& InMask)`
- L91 _protected function_ `virtual void OnAllFramesSubmittedImpl(UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph)`
- L92 _protected function_ `virtual void OnAllFramesFinalizedImpl(UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph)`
- L93 _protected function_ `virtual void OnAllShotFramesSubmittedImpl(UMovieGraphPipeline* InPipeline, const UMoviePipelineExecutorShot* InShot, TObjectPtr<UMovieGraphEvaluatedConfig>& InShotEvaluatedGraph, const bool bFlushToDisk)`
- L96 _protected function_ `virtual void OnAllShotFramesSubmittedImpl(UMovieGraphPipeline* InPipeline, const UMoviePipelineExecutorShot* InShot, TObjectPtr<UMovieGraphEvaluatedConfig>& InShotEvaluatedGraph) final` — `UE_DEPRECATED(5.6, "Please use the version of OnAllShotFramesSubmittedImpl() that has the new bFlushToDisk argument at the end.")`
- L98 _protected function_ `virtual bool IsFinishedWritingToDiskImpl() const`
- L101 _protected function_ `virtual bool ShouldCropOverscanImpl() const` — Returns whether any overscan should be automatically cropped from the image before compositing and output
- L104 _protected prototype_ `static int32 GetNumFileOutputNodes(const UMovieGraphEvaluatedConfig& InEvaluatedConfig, const FName& InBranchName);` — Returns the number of evaluated (active) file nodes on the specified branch.
- L108 _protected prototype_ `static void DisambiguateFilename(FString& InOutFilenameFormatString, const UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, const FName& InNodeName, const FMovieGraphPassData& InRenderData);` — `UE_DEPRECATED(5.7, "Please use the version of DisambiguateFilename() that takes a UMovieGraphFileOutputNode instance. The new version supports enhanced disambiguation rules.")` — Updates InOutFilenameFormatString to include tokens (like {layer_name}) that will disambiguate the output if multiple outputs are attempting to write to the same file.
- L111 _protected prototype_ `static void DisambiguateFilename(FString& InOutFilenameFormatString, const UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, const UMovieGraphFileOutputNode* InParentNode, const FMovieGraphPassData& InRenderData);` — Updates InOutFilenameFormatString to include tokens (like {layer_name}) that will disambiguate the output if multiple outputs are attempting to write to the same file.
- L114 _protected prototype_ `static TArray<FMovieGraphPassData> GetCompositedPasses(UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData);` — Convenience function to get the list of active composite passes from render data.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphGlobalGameOverrides.h` (Public)


#### enum `EMovieGraphScalabilityQualityLevel`  
`enum class EMovieGraphScalabilityQualityLevel : uint8`  
_L14-21_
- reflection: `UENUM(BlueprintType)`
- desc: Scalability quality levels available for use in renders generated from the graph.
- L16 _public enumerator_ `Low = 0`
- L17 _public enumerator_ `Medium = 1`
- L18 _public enumerator_ `High = 2`
- L19 _public enumerator_ `Epic = 3`
- L20 _public enumerator_ `Cinematic = 4`

#### class `UMovieGraphGlobalGameOverridesNode`  
`class UMovieGraphGlobalGameOverridesNode : public UMovieGraphSettingNode`  
_L25-250_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- desc: A node which configures the global game overrides.
- L30 _public prototype_ `UMovieGraphGlobalGameOverridesNode();`
- L33 _public function_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override` — UMovieGraphNode interface
- L37 _public prototype_ `virtual void BuildNewProcessCommandLineArgsImpl(TArray<FString>& InOutUnrealURLParams, TArray<FString>& InOutCommandLineArgs, TArray<FString>& InOutDeviceProfileCvars, TArray<FString>& InOutExecCmds) const override;` — UMovieGraphSettingNode interface
- L38 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L42 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L50 _public prototype_ `void ApplySettings(const bool bOverrideValues, UWorld* InWorld);` — Applies any cvars, scalability settings, etc. to reflect the properties set on the node. Remembers what the settings are before they are set, so bOverrideValues can be set to false to revert them to their original values. The world needs to be provided as context for any commands that are executed.
- L56 _public prototype_ `static TSubclassOf<AGameModeBase> GetGameModeOverride(const UMoviePipelineExecutorJob* InJob);` — Gets the game mode override if the job specified is using a graph configuration, otherwise gets the game mode override from the legacy non-graph config system.
- L59 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L60 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L61 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L62 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L68 _public member_ `uint8 bOverride_GameModeOverride : 1;` — `UE_DEPRECATED(5.5, "Please use the bOverride_SoftGameModeOverride property instead.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle, DeprecatedProperty, DeprecationMessage = "Please use the bOverride_SoftGameModeOverride property instead."))`
- L71 _public member_ `uint8 bOverride_SoftGameModeOverride : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L74 _public member_ `uint8 bOverride_ScalabilityQualityLevel : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L77 _public member_ `uint8 bOverride_bDisableTextureStreaming : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (ScriptName="Override_DisableTextureStreaming;Override_bDisableTextureStreaming", InlineEditConditionToggle))`
- L80 _public member_ `uint8 bOverride_bDisableLODs : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (ScriptName="Override_DisableLods;Override_bDisableLODs", InlineEditConditionToggle))`
- L83 _public member_ `uint8 bOverride_bDisableHLODs : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (ScriptName="Override_DisableHlods;Override_bDisableHLODs", InlineEditConditionToggle))`
- L86 _public member_ `uint8 bOverride_bFlushLevelStreaming : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (ScriptName="Override_FlushLevelStreaming;Override_bFlushLevelStreaming", InlineEditConditionToggle))`
- L89 _public member_ `uint8 bOverride_bFlushAssetCompiler: 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (ScriptName="Override_FlushAssetCompiler;Override_bFlushAssetCompiler", InlineEditConditionToggle))`
- L92 _public member_ `uint8 bOverride_bFlushShaderCompiler : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (ScriptName="Override_FlushShaderCompiler;Override_bFlushShaderCompiler", InlineEditConditionToggle))`
- L95 _public member_ `uint8 bOverride_bFlushGrassStreaming : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (ScriptName="Override_FlushGrassStreaming;Override_bFlushGrassStreaming", InlineEditConditionToggle))`
- L98 _public member_ `uint8 bOverride_bFlushStreamingManagers : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (ScriptName="Override_FlushStreamingManagers;Override_bFlushStreamingManagers", InlineEditConditionToggle))`
- L101 _public member_ `uint8 bOverride_VirtualTextureFeedbackFactor : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L105 _public member_ `uint8 bOverride_bRebuildLumenSceneBetweenRenderLayers : 1;` — `UE_DEPRECATED(5.8, "Lumen scene rebuild is now automatically applied during layer warm-ups in the deferred renderer. Use Layer Warm Up Frames on the Warm Up Settings or Render Layer nodes instead.")` — `UPROPERTY(BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle, DeprecatedProperty, DeprecationMessage = "Lumen scene rebuild is now automatically applied during layer warm-ups in the deferred renderer. Use Layer Warm Up Frames on the Warm Up Settings or Render Layer nodes instead."))`
- L113 _public member_ `TSubclassOf<AGameModeBase> GameModeOverride;` — `UE_DEPRECATED(5.5, "Please use the SoftGameModeOverride property instead.")` — `UPROPERTY(BlueprintReadWrite, Category = "Game", meta = (EditCondition = "bOverride_GameModeOverride", DeprecatedProperty, DeprecationMessage = "Please use the SoftGameModeOverride property instead."))` — Optional game mode to override the map's default game mode with. This can be useful if the game's normal mode displays UI elements or loading screens that you don't want captured.
- L120 _public member_ `TSoftClassPtr<AGameModeBase> SoftGameModeOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", DisplayName = "Game Mode Override", meta = (EditCondition = "bOverride_SoftGameModeOverride"))` — Optional game mode to override the map's default game mode with. This can be useful if the game's normal mode displays UI elements or loading screens that you don't want captured.
- L127 _public member_ `EMovieGraphScalabilityQualityLevel ScalabilityQualityLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (EditCondition = "bOverride_ScalabilityQualityLevel"))` — The scalability quality level that should be used in renders. See the Scalability Reference documentation for information on how to edit cvars to add/change default quality values.
- L136 _public member_ `bool bDisableTextureStreaming;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (EditCondition = "bOverride_bDisableTextureStreaming"))` — Toggles whether texture streaming is disabled. Can solve objects being blurry after camera cuts. Configures the following cvars: - r.TextureStreaming
- L150 _public member_ `bool bDisableLODs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (ScriptName="bDisableLods;DisableLODs", EditCondition = "bOverride_bDisableLODs"))` — Disabling LODs will use the highest quality LOD for meshes and particle systems, regardless of distance. Note that this does not affect Nanite. Configures the following cvars: - r.ForceLOD - r.SkeletalMeshLODBias - r.ParticleLODBias - foliage.DitheredLOD - foliage.ForceLOD
- L157 _public member_ `bool bDisableHLODs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (ScriptName="bDisableHlods;bDisableHLODs", EditCondition = "bOverride_bDisableHLODs"))` — Determines if hierarchical LODs should be disabled and their real meshes used instead, regardless of distance. Note that this does not affect World Partition HLODs.
- L165 _public member_ `bool bFlushLevelStreaming;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (EditCondition = "bOverride_bFlushLevelStreaming"))` — Flushing level streaming ensures that any pending changes to sub-levels or world partition are fully processed before we render the frame. This feature generally only adds to render times on the frames that have level visibility state changes, so generally safe to leave turned on all the time.
- L173 _public member_ `bool bFlushAssetCompiler;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (EditCondition = "bOverride_bFlushAssetCompiler"))` — This ensures that any asynchronously compiled assets (static meshes, distance fields, etc.) required for rendering the frame are completed before rendering the frame. This feature generally only adds to render times on the frames where a new asset is introduced (ie, spawned) that may not be fully compiled. Results are stored in the DDC on subsequent uses.
- L182 _public member_ `bool bFlushShaderCompiler;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (EditCondition = "bOverride_bFlushShaderCompiler"))` — This ensures that any asynchronously compiled shader permutations are completed before rendering the frame. When using On Demand Shader Compilation the editor will skip compiling currently unneeded permutations for the material graph to decrease artist iteration time, but these permutations need to be compiled when rendering. Results are stored in the DDC on subsequent uses.
- L190 _public member_ `bool bFlushGrassStreaming;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (EditCondition = "bOverride_bFlushGrassStreaming"))` — Flushing grass streaming prevents visible pop-in/culling of grass instances, but may come at a high GPU memory cost (depending on rendering feature set), and grass density. Try turning this off if you are low on GPU memory and have dense grass.
- L205 _public member_ `bool bFlushStreamingManagers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (EditCondition = "bOverride_bFlushStreamingManagers"))` — This ensures that we wait on any streaming managers that may have outstanding work to finish their work before we render the frame. Many GPU-based features rely on a feedback loop where a frame is rendered, then results are read back from the GPU to the CPU. These results are analyzed, and additional data is loaded to be used in a subsequent frame. This feature ensures that the data is fully loaded before we render the next frame, but does NOT solve issues related to generating the those feedback requests in the first place. Virtual Textures and Nanite must render the frame to generate the request -- this option cannot solve that; it only helps ensure that the requests that are made are fully processed before the frame is rendered. Configures the following cvars: - r.Streaming.SyncStatesWhenBlocking
- L209 _public member_ `int32 VirtualTextureFeedbackFactor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (EditCondition = "bOverride_VirtualTextureFeedbackFactor"))` — The virtual texture feedback resolution factor. A lower factor will increase virtual texture feedback resolution.
- L217 _public member_ `bool bRebuildLumenSceneBetweenRenderLayers;` — `UE_DEPRECATED(5.8, "Lumen scene rebuild is now automatically applied during layer warm-ups in the deferred renderer. Use Layer Warm Up Frames on the Warm Up Settings or Render Layer nodes instead.")` — `UPROPERTY(BlueprintReadWrite, Category = "Lumen Render Layers (Experimental)", meta = (EditCondition = "bOverride_bRebuildLumenSceneBetweenRenderLayers", DeprecatedProperty, DeprecationMessage = "Lumen scene rebuild is now automatically applied during layer warm-ups in the deferred renderer. Use Layer Warm Up Frames on the Warm Up Settings or Render Layer nodes instead."))` — Deprecated: Lumen scene rebuild is now automatically applied during layer warm-ups in the deferred renderer. Use Layer Warm Up Frames on the Warm Up Settings or Render Layer nodes instead.
- L220 _private member_ `Scalability::FQualityLevels PreviousQualityLevels;`
- L221 _private member_ `int32 PreviousTextureStreaming;`
- L222 _private member_ `int32 PreviousForceLOD;`
- L223 _private member_ `int32 PreviousSkeletalMeshBias;`
- L224 _private member_ `int32 PreviousParticleLODBias;`
- L225 _private member_ `int32 PreviousFoliageDitheredLOD;`
- L226 _private member_ `int32 PreviousFoliageForceLOD;`
- L227 _private member_ `int32 PreviousStreamingManagerSyncState;`
- L228 _private member_ `int32 PreviousLumenRadiosityUpdateFactor;`
- L229 _private member_ `int32 PreviousLumenSurfaceCacheCardCaptureFactor;`
- L230 _private member_ `int32 PreviousLumenSurfaceCacheFeedback;`
- L231 _private member_ `int32 PreviousLumenSurfaceCacheRecaptureEveryFrame;`
- L232 _private member_ `int32 PreviousAnimationUROEnabled;`
- L233 _private member_ `int32 PreviousSkyLightRealTimeReflectionCaptureTimeSlice;`
- L234 _private member_ `int32 PreviousVolumetricRenderTarget;`
- L235 _private member_ `int32 PreviousVolumetricRenderTargetMode;`
- L236 _private member_ `int32 PreviousIgnoreStreamingPerformance;`
- L237 _private member_ `float PreviousChaosImmPhysicsMinStepTime;`
- L238 _private member_ `int32 PreviousSkipRedundantTransformUpdate;`
- L239 _private member_ `int32 PreviousChaosClothUseTimeStepSmoothing;`
- L240 _private member_ `int32 PreviousSkipWaterInfoTextureRenderWhenWorldRenderingDisabled;`
- L241 _private member_ `int32 PreviousNaniteVSMInvalidateOnLODDelta;`
- L242 _private member_ `int32 PreviousAllowSlateThrottling;`
- L243 _private member_ `bool PreviousAlphaOutput;`
- L244 _private member_ `int32 PreviousLUTSize;`
- L247 _private member_ `int32 PreviousGeoCacheStreamerShowNotification;`
- L248 _private member_ `int32 PreviousGeoCacheStreamerBlockTillFinish;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphGlobalOutputSettingNode.h` (Public)


#### struct `FMovieGraphVersioningSettings`  
`struct FMovieGraphVersioningSettings`  
_L16-33_
- reflection: `USTRUCT(BlueprintType)`
- L28 _public member_ `bool bAutoVersioning = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")` — If true, {version} tokens specified in the Output Directory and File Name Format properties will automatically be incremented with each local render. If false, the version specified in Version Number will be used instead. Auto-versioning will search across all render branches and use the highest version found as the basis for the next version used.
- L32 _public member_ `int32 VersionNumber = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning", meta = (UIMin = 1, UIMax = 50, ClampMin = 1))` — The value to use for the version token if versions are not automatically incremented (Auto Version is off).

#### enum `EMovieGraphSequenceRangeType`  
`enum class EMovieGraphSequenceRangeType : uint8`  
_L36-42_
- reflection: `UENUM(BlueprintType)`
- L39 _public enumerator_ `SequenceDefault` — Use the Playback Range value from the Level Sequence (without overriding it.)
- L41 _public enumerator_ `Custom` — Override the Playback Range value from the Level Sequence and instead override it to use a custom Frame Number.

#### struct `FMovieGraphSequencePlaybackRangeBound`  
`struct FMovieGraphSequencePlaybackRangeBound`  
_L45-68_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public function_ `FMovieGraphSequencePlaybackRangeBound() : Type(EMovieGraphSequenceRangeType::Custom) , Value(0)`
- L60 _public member_ `EMovieGraphSequenceRangeType Type;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")` — By default the render will use the Playback Range Start/End frame to determine what to render. Set this to Custom to override the Playback Range bound value, and instead use the Value below as the Start or End frame.
- L67 _public member_ `int32 Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value", meta = (EditCondition = "Type == EMovieGraphSequenceRangeType::Custom"))` — If Type is set to Custom, then this value is used for the Playback Range Start or End frame. Value is considered frames at the original Sequence frame rate (it is applied before Frame Rate Override.)

#### enum `EMovieGraphAspectRatioAdaptBehavior`  
`enum class EMovieGraphAspectRatioAdaptBehavior : uint8`  
_L71-111_
- reflection: `UENUM(BlueprintType)`
- L77 _public enumerator_ `Disabled` — Output resolution will not be modified. If the camera has Constrain Aspect Ratio enabled, then letterboxing may be shown to preserve that aspect ratio within the specified Output Resolution.
- L88 _public enumerator_ `Automatic` — If the camera has Constrain Aspect Ratio enabled, then this should match Disabled, except the letterboxing will be cropped off. No behavior change if Constrain Aspect Ratio is not enabled. The output resolution will be resized to respect the camera aspect ratio, matching either the specified Width, or Height. Which dimension is picked will depend on the aspect ratio (ie: a tall camera aspect ratio will preserve the height of the output, and crop the width, while a wide camera aspect ratio will preserve the width of the output and crop the height.)
- L99 _public enumerator_ `ScaleToWidth` — If the camera has Constrain Aspect Ratio enabled, then the width of the output resolution will be preserved, and the height will automatically be adjusted based on the camera aspect ratio. ie: If you have a 1.77 (16:9) Camera Aspect Ratio and target a 1.0 (1:1) output image, then the output image will have its height adjusted to preserve the 1.77 aspect ratio of the camera, without showing letterboxing. For example, a 1.77 Camera Aspect Ratio and a 1024x1024 output resolution will produce a render that is 1024x576, which preserves the existing aspect ratio and the given width. No behavior change if Constrain Aspect Ratio is not enabled.
- L110 _public enumerator_ `ScaleToHeight` — If the camera has Constrain Aspect Ratio enabled, then the height of the output resolution will be preserved, and the width will automatically be adjusted based on the camera aspect ratio. ie: If you have a 1.77 (16:9) Camera Aspect Ratio and target a 1.0 (1:1) output image, then the output image will have its width adjusted to preserve the 1.77 aspect ratio of the camera, without showing letterboxing. For example, a 1.77 Camera Aspect Ratio and a 1024x1024 output resolution will produce a render that is 1820x1024, which preserves the existing aspect ratio and the given height. No behavior change if Constrain Aspect Ratio is not enabled.

#### class `UMovieGraphGlobalOutputSettingNode`  
`class UMovieGraphGlobalOutputSettingNode : public UMovieGraphSettingNode`  
_L114-285_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- L118 _public prototype_ `UMovieGraphGlobalOutputSettingNode();`
- L121 _public prototype_ `virtual void PostLoad() override;` — UObject Interface
- L125 _public prototype_ `virtual void GetFormatResolveArgs(FMovieGraphResolveArgs& OutMergedFormatArgs, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier) const override;` — UMovieGraphSettingNode Interface
- L126 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L127 _public prototype_ `virtual void PostFlatten() override;`
- L129 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive) const override;`
- L130 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L131 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L132 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L133 _public prototype_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override;`
- L135 _public prototype_ `virtual bool GetCustomPromotionDefaultValue(const FMovieGraphPropertyInfo& InPropertyInfo, FString& OutSerializedValue) const override;`
- L145 _protected prototype_ `virtual void ApplyPostLoadPropertyConversions(bool bEmitWarning);` — This is called from PostLoad and when the UMovieGraphPipeline is initialized to convert any legacy properties. We do it this way to preserve existing code that may be configuring assets after loading them but before rendering them. @param bEmitWarning - If true, a warning will be printed that the conversion took place and the users need to update their scripts.
- L149 _public member_ `uint8 bOverride_OutputDirectory : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L152 _public member_ `uint8 bOverride_OutputResolution : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L155 _public member_ `uint8 bOverride_AdaptResolution : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L158 _public member_ `uint8 bOverride_OutputFrameRate : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L161 _public member_ `uint8 bOverride_bOverwriteExistingOutput : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L164 _public member_ `uint8 bOverride_ZeroPadFrameNumbers : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L167 _public member_ `uint8 bOverride_FrameNumberOffset : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L170 _public member_ `uint8 bOverride_HandleFrameCount : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L174 _public member_ `uint8 bOverride_CustomPlaybackRangeStartFrame : 1;` — `UE_DEPRECATED(5.6, "Use bOverride_CustomPlaybackRangeStart instead.")` — `UPROPERTY(BlueprintReadWrite, Category = Overrides, meta = (DeprecatedProperty, DeprecationMessage = "Use bOverride_CustomPlaybackRangeStart instead."))`
- L178 _public member_ `uint8 bOverride_CustomPlaybackRangeEndFrame : 1;` — `UE_DEPRECATED(5.6, "Use bOverride_CustomPlaybackRangeEnd instead.")` — `UPROPERTY(BlueprintReadWrite, Category = Overrides, meta = (DeprecatedProperty, DeprecationMessage = "Use bOverride_CustomPlaybackRangeEnd instead."))`
- L181 _public member_ `uint8 bOverride_CustomPlaybackRangeStart : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L184 _public member_ `uint8 bOverride_CustomPlaybackRangeEnd : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L187 _public member_ `uint8 bOverride_CustomTimecodeStart : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L190 _public member_ `uint8 bOverride_bDropFrameTimecode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L193 _public member_ `uint8 bOverride_VersioningSettings : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L196 _public member_ `uint8 bOverride_bFlushDiskWritesPerShot : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L200 _public member_ `FDirectoryPath OutputDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output", meta=(EditCondition="bOverride_OutputDirectory", MrgTokenAutocomplete))` — What directory should all of our output files be relative to.
- L204 _public member_ `FMovieGraphNamedResolution OutputResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output", meta = (EditCondition = "bOverride_OutputResolution"))` — What resolution should our output files be exported at?
- L208 _public member_ `EMovieGraphAspectRatioAdaptBehavior AdaptResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output", meta = (EditCondition = "bOverride_AdaptResolution"))` — Should the output resolution be automatically adjusted to match the aspect ratio on cameras with Constrain Aspect Ratio?
- L212 _public member_ `FFrameRate OutputFrameRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output", meta=(EditCondition="bOverride_OutputFrameRate"))` — What frame rate should the output files be exported at? This overrides the Display Rate of the target sequence. If not overwritten, uses the default Sequence Display Rate.
- L216 _public member_ `bool bOverwriteExistingOutput;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output", meta = (EditCondition = "bOverride_bOverwriteExistingOutput"))` — If true, output containers should attempt to override any existing files with the same name.
- L220 _public member_ `int32 ZeroPadFrameNumbers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output", meta = (EditCondition = "bOverride_ZeroPadFrameNumbers", UIMin = "1", UIMax = "5", ClampMin = "1"))` — How many digits should all output frame numbers be padded to? MySequence_1.png -> MySequence_0001.png. Useful for software that struggles to recognize frame ranges when non-padded.
- L227 _public member_ `int32 FrameNumberOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output", meta = (EditCondition = "bOverride_FrameNumberOffset"))` — How many frames should we offset the output frame number by? This is useful when using handle frames on Sequences that start at frame 0, as the output would start in negative numbers. This can be used to offset by a fixed amount to ensure there's no negative numbers.
- L236 _public member_ `int32 HandleFrameCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frames", meta = (UIMin = 0, ClampMin = 0, EditCondition = "bOverride_HandleFrameCount"))` — Top level shot track sections will automatically be expanded by this many frames in both directions, and the resulting additional time will be rendered as part of that shot. The inner sequence should have sections long enough to cover this expanded range, otherwise these tracks will not evaluate during handle frames and may produce unexpected results. This can be used to generate handle frames for traditional non linear editing tools.
- L243 _public member_ `FMovieGraphSequencePlaybackRangeBound CustomPlaybackRangeStart;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frames", meta = (EditCondition = "bOverride_CustomPlaybackRangeStart"))` — If overwritten, and the Type is set to "Custom", then the Value field will override the Sequence's Playback Range Start when rendering. Values are expected to be in the Sequence's original Frame Rate (the custom range is applied before Frame Rate Override).
- L251 _public member_ `FMovieGraphSequencePlaybackRangeBound CustomPlaybackRangeEnd;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frames", meta = (EditCondition = "bOverride_CustomPlaybackRangeEnd"))` — If overwritten, and the Type is set to "Custom", then the Value field will override the Sequence's Playback Range End when rendering. Values are expected to be in the Sequence's original Frame Rate (the custom range is applied before Frame Rate Override).
- L255 _public member_ `FTimecode CustomTimecodeStart;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timecode", meta = (EditCondition = "bOverride_CustomTimecodeStart"))` — Start the timecode at a specific value, rather than the value coming from the Level Sequence. Only applicable to output formats that support timecode.
- L259 _public member_ `bool bDropFrameTimecode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timecode", DisplayName = "Use DF Timecode if 29.97 FPS", meta = (EditCondition = "bOverride_bDropFrameTimecode"))` — Whether the embedded timecode track should be written using drop-frame format. Only applicable to output formats that support timecode, and when the sequence framerate is 29.97.
- L265 _public member_ `FMovieGraphVersioningSettings VersioningSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning", meta = (EditCondition = "bOverride_VersioningSettings"))` — Determines how versioning should be handled (Auto Version, Version Number, etc.).
- L272 _public member_ `bool bFlushDiskWritesPerShot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scripting", meta = (EditCondition = "bOverride_bFlushDiskWritesPerShot"))` — If true, the game thread will stall at the end of each shot to flush the rendering queue, and then flush any outstanding writes to disk, finalizing any outstanding videos and generally completing the work. This is only relevant for scripting where scripts may do post-shot callback work.
- L279 _public member_ `int32 CustomPlaybackRangeStartFrame;` — `UE_DEPRECATED(5.6, "Use CustomPlaybackRangeStart with Type set to Custom and Value set to the desired value instead.")` — `UPROPERTY(BlueprintReadWrite, Category = "Frames", meta = (DeprecatedFunction, DeprecationMessage = "Use CustomPlaybackRangeStart with Type set to Custom and Value set to the desired value instead."))`
- L283 _public member_ `int32 CustomPlaybackRangeEndFrame;` — `UE_DEPRECATED(5.6, "Use CustomPlaybackRangeEnd with Type set to Custom and Value set to the desired value instead.")` — `UPROPERTY(BlueprintReadWrite, Category = "Frames", meta = (DeprecatedFunction, DeprecationMessage = "Use CustomPlaybackRangeEnd with Type set to Custom and Value set to the desired value instead."))`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphInputNode.h` (Public)


#### class `UMovieGraphInputNode`  
`class UMovieGraphInputNode : public UMovieGraphNode`  
_L13-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphNode`
- desc: A graph node which displays all input members available in the graph.
- L18 _public prototype_ `UMovieGraphInputNode();`
- L21 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetOutputPinProperties() const override;`
- L22 _public prototype_ `virtual TArray<UMovieGraphPin*> EvaluatePinsToFollow(FMovieGraphEvaluationContext& InContext) const override;`
- L23 _public prototype_ `virtual FString GetResolvedValueForOutputPin(const FName& InPinName, const FMovieGraphTraversalContext* InContext) const override;`
- L24 _public prototype_ `virtual bool CanBeDisabled() const override;`
- L26 _public function_ `virtual bool CanBeAddedByUser() const override`
- L29 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L30 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L31 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L32 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L37 _private prototype_ `virtual void RegisterDelegates() override;`
- L40 _private prototype_ `void RegisterInputDelegates(UMovieGraphInput* Input);` — Register delegates for the provided input member.
- L43 _private prototype_ `void UpdateExistingPins(UMovieGraphMember* ChangedVariable) const;` — Update data (name, etc) on all existing output pins on this node to reflect the input members on the graph.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphLightModifierNode.h` (Public)


#### enum `EMovieGraphLightModifierIntensityMethod`  
`enum class EMovieGraphLightModifierIntensityMethod : uint8`  
_L20-27_
- reflection: `UENUM(BlueprintType)`
- desc: Controls which intensity properties are used to control lighting intensity in the Light Modifier node.
- L23 _public enumerator_ `PointRectSpot UMETA(DisplayName = "Point, Rect, and Spot Lights")` — Apply the "Intensity" property to Point, Rect, and Spot lights.
- L26 _public enumerator_ `PerLightActor UMETA(DisplayName = "Per Light Actor Type")` — The main "Intensity" property is ignored, and the type-specific "Intensity" properties are used instead.

#### class `UMovieGraphLightModifierNode`  
`class UMovieGraphLightModifierNode final : public UMovieGraphSettingNode, public IMovieGraphModifierNodeInterface`  
_L37-347_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode,IMovieGraphModifierNodeInterface`
- desc: A node which modifies properties on light components within the world. There are several common light properties (eg, Light Color) that can be modified directly. For less common light properties, they can be modified by adding them as "Custom" properties. The common properties apply to all standard light types; custom properties apply only to a specific light type.
- L42 _public prototype_ `UMovieGraphLightModifierNode();`
- L46 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L47 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L48 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L49 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L53 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L58 _public prototype_ `virtual TArray<FPropertyBagPropertyDesc> GetDynamicPropertyDescriptions() const override;`
- L59 _public prototype_ `virtual TArray<FMovieGraphPropertyInfo> GetOverrideablePropertyInfo() const override;`
- L63 _public prototype_ `virtual TArray<UMovieGraphModifierBase*> GetAllModifiers() const override;`
- L64 _public prototype_ `virtual bool SupportsCollections() const override;`
- L65 _public prototype_ `virtual TArray<FName> GetAllCollections() const override;`
- L66 _public prototype_ `virtual void AddCollection(const FName& InCollectionName) override;`
- L67 _public prototype_ `virtual bool RemoveCollection(const FName& InCollectionName) override;`
- L71 _public prototype_ `virtual FString GetNodeInstanceName() const override;`
- L72 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L73 _public prototype_ `virtual void PrepareForFlattening(const UMovieGraphSettingNode* InSourceNode) override;`
- L83 _public prototype_ `bool AddCustomLightProperty(UClass* InLightComponentClass, const FProperty* InLightProperty);` — Adds the property from the specified class to the "Custom" lighting properties. Does nothing if the Custom properties already contains it. Returns true on success, else false. Adding a custom property does not immediately make it take effect. Its override state needs to be set to "true" via UpdateCustomLightPropertyOverrideState().
- L93 _public prototype_ `bool AddCustomLightProperty(UClass* InLightComponentClass, const FName& InPropertyName);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Adds the property from the specified class to the "Custom" lighting properties. Does nothing if the Custom properties already contains it. Returns true on success, else false. Adding a custom property does not immediately make it take effect. Its override state needs to be set to "true" via UpdateCustomLightPropertyOverrideState().
- L99 _public prototype_ `bool RemoveCustomLightProperty(const UClass* InLightComponentClass, const FProperty* InLightProperty);` — Removes the property in the specified class from the "Custom" lighting properties. Does nothing if the Custom properties don't contain the property. Returns true on success, else false.
- L106 _public prototype_ `bool RemoveCustomLightProperty(const UClass* InLightComponentClass, const FName& InPropertyName);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Removes the property in the specified class from the "Custom" lighting properties. Does nothing if the Custom properties don't contain the property. Returns true on success, else false.
- L109 _public prototype_ `bool HasCustomLightProperty(const UClass* InLightComponentClass, const FProperty* InLightProperty) const;` — Determines if the given property exists within the "Custom" lighting properties.
- L113 _public prototype_ `bool HasCustomLightProperty(const UClass* InLightComponentClass, const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Determines if the given property exists within the "Custom" lighting properties.
- L120 _public prototype_ `bool IsCustomLightPropertyOverridden(const UClass* InLightComponentClass, const FName& InPropertyName) const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Determines if the given "Custom" light property has been marked as overridden. A custom property MUST be marked as overridden in order to take effect. The override state is visualized as the checkbox in front of the property name the UI.
- L127 _public prototype_ `bool UpdateCustomLightPropertyOverrideState(const UClass* InLightComponentClass, const FName& InPropertyName, const bool bIsOverridden);` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Updates the override state for a "Custom" light property. A custom property MUST be marked as overridden in order to take effect. Returns true on success, else false.
- L131 _public prototype_ `int32 GetNumCustomLightProperties() const;` — `UFUNCTION(BlueprintCallable, Category = "Properties")` — Gets how many "Custom" lighting properties have been added.
- L136 _public member_ `uint8 bOverride_ModifierName : 1 = 1;` — `UPROPERTY()` — Always merge the modifier name, no need for the user to do this explicitly
- L139 _public member_ `uint8 bOverride_DirectionalLightIntensity : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L142 _public member_ `uint8 bOverride_SkyLightIntensityScale : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L145 _public member_ `uint8 bOverride_IntensityMethod : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L148 _public member_ `uint8 bOverride_Intensity : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L151 _public member_ `uint8 bOverride_PointLightIntensity : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L154 _public member_ `uint8 bOverride_PointLightIntensityUnits : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L157 _public member_ `uint8 bOverride_RectLightIntensity : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L160 _public member_ `uint8 bOverride_RectLightIntensityUnits : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L163 _public member_ `uint8 bOverride_SpotLightIntensity : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L166 _public member_ `uint8 bOverride_SpotLightIntensityUnits : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L169 _public member_ `uint8 bOverride_IntensityUnits : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L172 _public member_ `uint8 bOverride_LightColor : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L175 _public member_ `uint8 bOverride_bAffectsWorld : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L178 _public member_ `uint8 bOverride_CastShadows : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L181 _public member_ `uint8 bOverride_IndirectLightingIntensity : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L184 _public member_ `uint8 bOverride_VolumetricScatteringIntensity : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L187 _public member_ `uint8 bOverride_LightingChannels : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L190 _public member_ `uint8 bOverride_SamplesPerPixel : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L194 _public member_ `FString ModifierName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")` — The name of this modifier.
- L200 _public member_ `float DirectionalLightIntensity = 10.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light|Intensity", meta = (EditCondition = "bOverride_DirectionalLightIntensity", UIMin = "0.0", UIMax = "150.0", SliderExponent = "2.0", Units = "lux"))` — Maximum illumination from the light (in lux).
- L206 _public member_ `float SkyLightIntensityScale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light|Intensity", meta = (EditCondition = "bOverride_SkyLightIntensityScale", UIMin = "0.0", UIMax = "50000.0", SliderExponent = "10.0"))` — Total energy that the sky light emits.
- L212 _public member_ `EMovieGraphLightModifierIntensityMethod IntensityMethod = EMovieGraphLightModifierIntensityMethod::PointRectSpot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light|Intensity", meta = (EditCondition = "bOverride_IntensityMethod"))` — Whether point, rect, and spot lights share the same intensity, or the intensity (and intensity units) are unique for each type.
- L218 _public member_ `float Intensity = 8.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light|Intensity", meta = (EditCondition = "bOverride_Intensity", UIMin = "0.0", UIMax = "20.0", Units = "cd"))` — Total energy that the light emits.
- L224 _public member_ `float PointLightIntensity = 8.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light|Intensity|PointLight", meta = (EditCondition = "bOverride_PointLightIntensity", UIMin = "0.0", UIMax = "20.0"))` — Total energy that the point light emits.
- L232 _public member_ `ELightUnits PointLightIntensityUnits = ELightUnits::Candelas;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light|Intensity|PointLight", meta = (EditCondition = "bOverride_PointLightIntensityUnits"))` — Units used for the point light intensity. The peak luminous intensity is measured in candelas, while the luminous flux is measured in lumens. When the units are set in Nits, the light's power is also determined by the size of the light source (larger sources will emit more light).
- L238 _public member_ `float RectLightIntensity = 8.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light|Intensity|RectLight", meta = (EditCondition = "bOverride_RectLightIntensity", UIMin = "0.0", UIMax = "20.0"))` — Total energy that the rect light emits.
- L246 _public member_ `ELightUnits RectLightIntensityUnits = ELightUnits::Candelas;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light|Intensity|RectLight", meta = (EditCondition = "bOverride_RectLightIntensityUnits"))` — Units used for the rect light intensity. The peak luminous intensity is measured in candelas, while the luminous flux is measured in lumens. When the units are set in Nits, the light's power is also determined by the size of the light source (larger sources will emit more light).
- L252 _public member_ `float SpotLightIntensity = 8.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light|Intensity|SpotLight", meta = (EditCondition = "bOverride_SpotLightIntensity", UIMin = "0.0", UIMax = "20.0"))` — Total energy that the spot light emits.
- L260 _public member_ `ELightUnits SpotLightIntensityUnits = ELightUnits::Candelas;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light|Intensity|SpotLight", meta = (EditCondition = "bOverride_SpotLightIntensityUnits"))` — Units used for the spot light intensity. The peak luminous intensity is measured in candelas, while the luminous flux is measured in lumens. When the units are set in Nits, the light's power is also determined by the size of the light source (larger sources will emit more light).
- L268 _public member_ `ELightUnits IntensityUnits = ELightUnits::Candelas;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light|Intensity", meta = (EditCondition = "bOverride_IntensityUnits"))` — Units used for the intensity. The peak luminous intensity is measured in candelas, while the luminous flux is measured in lumens. When the units are set in Nits, the light's power is also determined by the size of the light source (larger sources will emit more light).
- L275 _public member_ `FColor LightColor = FColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta = (EditCondition = "bOverride_LightColor", HideAlphaChannel))` — Filter color of the light. Note that this can change the light's effective intensity.
- L283 _public member_ `uint32 bAffectsWorld : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta = (EditCondition = "bOverride_bAffectsWorld"))` — Whether the light can affect the world, or whether it is disabled. A disabled light will not contribute to the scene in any way.  This setting cannot be changed at runtime and unbuilds lighting when changed. Setting this to false has the same effect as deleting the light, so it is useful for non-destructive experiments.
- L289 _public member_ `uint32 CastShadows : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta = (EditCondition = "bOverride_CastShadows"))` — Whether the light should cast any shadows.
- L296 _public member_ `float IndirectLightingIntensity = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta = (UIMin = "0.0", UIMax = "6.0", EditCondition = "bOverride_IndirectLightingIntensity"))` — Scales the indirect lighting contribution from this light. A value of 0 disables any GI from this light. Default is 1.
- L300 _public member_ `float VolumetricScatteringIntensity = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta = (UIMin = "0.25", UIMax = "4.0", EditCondition = "bOverride_VolumetricScatteringIntensity"))` — Intensity of the volumetric scattering from this light.  This scales Intensity and LightColor.
- L308 _public member_ `FLightingChannels LightingChannels;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta = (EditCondition = "bOverride_LightingChannels"))` — Channels that this light should affect. These channels only apply to opaque materials, direct lighting, and dynamic lighting and shadowing. Lighting channels are only supported on translucent materials using forward shading (i.e. when not using the translucency lighting volume).
- L312 _public member_ `int SamplesPerPixel = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RayTracing", meta = (EditCondition = "bOverride_SamplesPerPixel"))` — Samples per pixel for ray tracing.
- L316 _private prototype_ `static FName GetLightingPropertyName(const UClass* InLightComponentClass, const FProperty* InLightProperty);` — Gets the property name used for the given property within the DynamicProperties property bag.
- L322 _private prototype_ `static FName GetLightingOverridePropertyName(const FName& InMainPropertyName);` — Gets the bOverride_* property name used for the given property within the DynamicProperties property bag. The "main" property name is the property name returned by GetLightingPropertyName().
- L327 _private member_ `uint8 bOverride_Collections : 1 = 1;` — `UPROPERTY()` — Always merge collection names, no need for the user to do this explicitly
- L331 _private member_ `uint8 bOverride_CustomPropertyInfo : 1 = 1;` — `UPROPERTY()` — Same with the custom property info; always merge it
- L335 _private member_ `TArray<FName> Collections;` — `UPROPERTY(meta = (HideInActiveRenderSettings))` — The collections modified by this node. Only lights will be modified.
- L339 _private member_ `TObjectPtr<UMovieGraphPropertyModifier> Modifier;` — `UPROPERTY(meta = (HideInActiveRenderSettings))` — The light modifier associated with this node.
- L346 _private member_ `TMap<FName, FMovieGraphPropertyReference> CustomPropertyInfo;` — `UPROPERTY(meta = (HideInActiveRenderSettings))` — Stores supplemental information for each "Custom" lighting property. Key is the name of the corresponding non-override property within DynamicProperties.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphMaterialParameterCollectionModifier.h` (Public)


#### class `UMovieGraphMaterialParameterCollectionModifier`  
`class UMovieGraphMaterialParameterCollectionModifier : public UMovieGraphModifierBase`  
_L17-62_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphModifierBase`
- desc: A modifier that allows for changing scalar and vector parameters within a Material Parameter Collection.
- L23 _public prototype_ `virtual void ApplyModifier(const UWorld* World) override;`
- L24 _public prototype_ `virtual void UndoModifier() override;`
- L25 _public prototype_ `virtual FText GetModifierName() override;`
- L30 _public prototype_ `void ClearParameterValues();` — `UFUNCTION(BlueprintCallable, Category = "Modifier")` — Clear the scalar and vector parameter values that have been set on this modifier.
- L35 _public member_ `TSoftObjectPtr<UMaterialParameterCollection> MaterialParameterCollection;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — The Material Parameter Collection that this modifier should update.
- L39 _public member_ `TMap<FName, float> ScalarParameterUpdates;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — The names and values of scalar parameters that this modifier will apply.
- L43 _public member_ `TMap<FName, FLinearColor> VectorParameterUpdates;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — The names and values of vector parameters that this modifier will apply.
- L50 _private prototype_ `void ApplyScalarAndVectorValues(const TMap<FName, float>& InScalarValues, const TMap<FName, FLinearColor>& InVectorValues, const bool bCacheCurrentValues = false);` — Applies the given scalar and vector values to the Material Parameter Collection associated with this modifier. Optionally, the current values can be cached for later restoration.
- L54 _private member_ `TMap<FName, float> PriorScalarValues;` — The cached names/values of scalar parameters before the modifier was applied.
- L57 _private member_ `TMap<FName, FLinearColor> PriorVectorValues;` — The cached names/values of vector parameters before the modifier was applied.
- L61 _private member_ `TWeakObjectPtr<const UWorld> CachedWorld = nullptr;` — `UPROPERTY(Transient)` — The world that the modifier is being applied in.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphMaterialParameterCollectionModifierNode.h` (Public)


#### class `UMovieGraphMaterialParameterCollectionModifierNode`  
`class UMovieGraphMaterialParameterCollectionModifierNode : public UMovieGraphSettingNode, public IMovieGraphModifierNodeInterface`  
_L19-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode,IMovieGraphModifierNodeInterface`
- desc: A node which modifies the scalar and vector parameters of a Material Parameter Collection.
- L24 _public prototype_ `UMovieGraphMaterialParameterCollectionModifierNode();`
- L28 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L29 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L30 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L31 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L35 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L36 _public prototype_ `virtual void PostLoad() override;`
- L41 _public prototype_ `virtual TArray<FPropertyBagPropertyDesc> GetDynamicPropertyDescriptions() const override;`
- L42 _public prototype_ `virtual bool GetDynamicPropertyValue(const FName PropertyName, FString& OutValue) override;`
- L43 _public prototype_ `virtual TArray<FMovieGraphPropertyInfo> GetOverrideablePropertyInfo() const override;`
- L47 _public prototype_ `virtual TArray<UMovieGraphModifierBase*> GetAllModifiers() const override;`
- L48 _public prototype_ `virtual bool SupportsCollections() const override;`
- L52 _public prototype_ `virtual FString GetNodeInstanceName() const override;`
- L53 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L54 _public prototype_ `virtual void PrepareForFlattening(const UMovieGraphSettingNode* InSourceNode) override;`
- L59 _public member_ `uint8 bOverride_MaterialParameterCollection : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L63 _public member_ `TSoftObjectPtr<UMaterialParameterCollection> MaterialParameterCollection;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material Parameter Collection", meta = (EditCondition = "bOverride_MaterialParameterCollection"))` — The Material Parameter Collection that should be modified.
- L66 _private prototype_ `void OnObjectPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);`
- L69 _private member_ `static inline const FName EditConditionMetadataKey = TEXT("Edi` — These should really be defined somewhere outside of MRG, but they don't appear to be.
- L70 _private member_ `static inline const FName CategoryMetadataKey = TEXT("Cat`
- L71 _private member_ `static inline const FName DisplayNameMetadataKey = TEXT("Dis`
- L72 _private member_ `static inline const FName InlineEditConditionToggleMetadataKey = TEXT("Inl`
- L76 _private member_ `TObjectPtr<UMovieGraphMaterialParameterCollectionModifier> Modifier;` — `UPROPERTY()` — The Material Parameter Collection modifier associated with this node.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphModifierNode.h` (Public)


#### class `UMovieGraphMergeableModifierContainer`  
`class UMovieGraphMergeableModifierContainer final : public UObject, public IMovieGraphTraversableObject`  
_L15-31_
- reflection: `UCLASS()`
- inherits: `UObject,IMovieGraphTraversableObject`
- desc: A container which allows an array of modifiers to be merged correctly.
- L21 _public prototype_ `virtual void Merge(const IMovieGraphTraversableObject* InSourceObject) override;` — IMovieGraphTraversableObject interface
- L22 _public prototype_ `virtual TArray<TPair<FString, FString>> GetMergedProperties() const override;`
- L26 _private prototype_ `void MergeProperties(const TObjectPtr<UMovieGraphCollectionModifier>& InDestModifier, const TObjectPtr<UMovieGraphCollectionModifier>& InSourceModifier);`
- L30 _public member_ `TArray<TObjectPtr<UMovieGraphCollectionModifier>> Modifiers;` — `UPROPERTY()`

#### class `UMovieGraphModifierNodeInterface`  
`class UMovieGraphModifierNodeInterface : public UInterface`  
_L34-37_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintable)`
- inherits: `UInterface`

#### class `IMovieGraphModifierNodeInterface`  
`class IMovieGraphModifierNodeInterface : public IInterface`  
_L48-104_
- inherits: `IInterface`
- desc: Provides the interface that nodes must implement if they want to provide modifier behavior. If a modifier node does not support collections, it must specify this explicitly via SupportsCollections(). If it does not support collections, all collection-related methods can remain unimplemented. Note that some of these methods may not be called by MRG yet, but they may be called in the future (eg, in future UIs). To ensure modifier functionality in the future, implement all methods that make sense for the modifier.
- L55 _public function_ `virtual TArray<UMovieGraphModifierBase*> GetAllModifiers() const` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Gets all modifiers that will be applied with this modifier node.
- L62 _public function_ `virtual bool SupportsCollections() const` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Gets whether this modifier node supports/uses collections.
- L69 _public function_ `virtual bool IsCollectionEnabled(const FName& InCollectionName) const` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Gets the enable state (within this modifier) of the collection with the given name.
- L79 _public function_ `virtual void SetCollectionEnabled(const FName& InCollectionName, const bool bIsCollectionEnabled)` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Sets the enable state (within this modifier) of the collection with the given name. Disabled collections will not be modified by this modifier node. Collections that are added to the modifier are enabled by default.
- L86 _public function_ `virtual TArray<FName> GetAllCollections() const` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Gets all collections that will be affected by the modifiers used by this node.
- L93 _public function_ `virtual void AddCollection(const FName& InCollectionName)` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Adds a collection identified by the given name which will be affected by the modifiers on this node.
- L100 _public function_ `virtual bool RemoveCollection(const FName& InCollectionName)` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Removes a collection identified by the given name. Returns true if the collection was found and removed successfully, else false.

#### class `UMovieGraphModifierNode`  
`class UMovieGraphModifierNode : public UMovieGraphSettingNode, public IMovieGraphModifierNodeInterface`  
_L110-201_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode,IMovieGraphModifierNodeInterface`
- desc: A modifier node which allows render properties and materials to be changed.
- L115 _public prototype_ `UMovieGraphModifierNode();`
- L119 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L120 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L121 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L122 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L126 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L131 _public prototype_ `virtual FString GetNodeInstanceName() const override;`
- L132 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L136 _public prototype_ `virtual TArray<UMovieGraphModifierBase*> GetAllModifiers() const override;`
- L137 _public prototype_ `virtual void AddCollection(const FName& InCollectionName) override;`
- L138 _public prototype_ `virtual bool RemoveCollection(const FName& InCollectionName) override;`
- L139 _public prototype_ `virtual TArray<FName> GetAllCollections() const override;`
- L140 _public prototype_ `virtual bool SupportsCollections() const override;`
- L141 _public prototype_ `virtual void SetCollectionEnabled(const FName& InCollectionName, const bool bIsCollectionEnabled) override;`
- L142 _public prototype_ `virtual bool IsCollectionEnabled(const FName& InCollectionName) const override;`
- L147 _public prototype_ `UMovieGraphCollectionModifier* GetModifier(TSubclassOf<UMovieGraphCollectionModifier> ModifierType) const;` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Gets the modifier of the specified type, or nullptr if one does not exist on this node.
- L152 _public prototype_ `const TArray<UMovieGraphCollectionModifier*>& GetModifiers() const;` — `UE_DEPRECATED(5.7, "Use GetAllModifiers() instead.")` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Gets all modifiers currently added to the node.
- L159 _public prototype_ `UMovieGraphCollectionModifier* AddModifier(TSubclassOf<UMovieGraphCollectionModifier> ModifierType);` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Adds a new modifier of the specified type. Returns a pointer to the new modifier, or nullptr if a modifier of the specified type already exists on this node (only one modifier of each type can be added to the node).
- L163 _public prototype_ `bool RemoveModifier(TSubclassOf<UMovieGraphCollectionModifier> ModifierType);` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Removes the modifier of the specified type. Returns true on success, or false if a modifier of the specified type does not exist on the node.
- L168 _public prototype_ `const TArray<FName>& GetCollections() const;` — `UE_DEPRECATED(5.7, "Use GetAllCollections() instead.")` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")` — Gets all collections that will be affected by the modifiers on this node.
- L172 _public member_ `uint8 bOverride_ModifierName : 1 = 1;` — `UPROPERTY()` — Always merge the modifier name, no need for the user to do this explicitly
- L176 _public member_ `FString ModifierName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")` — The name of this modifier.
- L182 _private member_ `uint8 bOverride_Collections : 1 = 1;` — `UPROPERTY()` — These private override properties exist so that the associated non-override properties are merged properly by UMovieGraphMergeableModifierContainer
- L185 _private member_ `uint8 bOverride_ModifiersContainer : 1 = 1;` — `UPROPERTY()`
- L188 _private member_ `uint8 bOverride_DisabledCollections : 1 = 1;` — `UPROPERTY()`
- L192 _private member_ `TArray<FName> Collections;` — `UPROPERTY()` — The names of collections being modified.
- L196 _private member_ `TObjectPtr<UMovieGraphMergeableModifierContainer> ModifiersContainer;` — `UPROPERTY(meta=(DisplayName="Modifiers"))` — The modifiers this node should run.
- L200 _private member_ `TSet<FName> DisabledCollections;` — `UPROPERTY()` — The collections on this node that have been disabled.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphOutputNode.h` (Public)


#### class `UMovieGraphOutputNode`  
`class UMovieGraphOutputNode : public UMovieGraphNode`  
_L13-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphNode`
- desc: A graph node which displays all output members available in the graph.
- L18 _public prototype_ `UMovieGraphOutputNode();`
- L20 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetInputPinProperties() const override;`
- L21 _public prototype_ `virtual bool CanBeDisabled() const override;`
- L23 _public function_ `virtual bool CanBeAddedByUser() const override`
- L26 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L27 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L28 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L29 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L33 _private prototype_ `virtual void RegisterDelegates() override;`
- L36 _private prototype_ `void RegisterOutputDelegates(UMovieGraphOutput* Output);` — Register delegates for the provided output member.
- L39 _private prototype_ `void UpdateExistingPins(UMovieGraphMember* ChangedVariable) const;` — Update data (name, etc) on all existing input pins on this node to reflect the output members on the graph.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphRemoveRenderSettingNode.h` (Public)


#### class `UMovieGraphRemoveRenderSettingNode`  
`class UMovieGraphRemoveRenderSettingNode : public UMovieGraphNode`  
_L14-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphNode`
- desc: A node which can remove other nodes in the graph.
- L19 _public prototype_ `UMovieGraphRemoveRenderSettingNode() = default;`
- L21 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetInputPinProperties() const override;`
- L22 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetOutputPinProperties() const override;`
- L25 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L26 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L27 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L28 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L31 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L38 _public member_ `TSubclassOf<UMovieGraphSettingNode> NodeType;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — The type of node (exact match) that should be removed.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphRenderLayerNode.h` (Public)


#### class `UMovieGraphRenderLayerNode`  
`class UMovieGraphRenderLayerNode : public UMovieGraphSettingNode`  
_L11-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- L15 _public prototype_ `UMovieGraphRenderLayerNode();`
- L17 _public function_ `FString GetRenderLayerName() const`
- L20 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L21 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L26 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L30 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L34 _public member_ `uint8 bOverride_LayerName : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L37 _public member_ `uint8 bOverride_LayerWarmUpFrames : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L40 _public member_ `FString LayerName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "bOverride_LayerName"))`
- L49 _public member_ `int32 LayerWarmUpFrames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bOverride_LayerWarmUpFrames", UIMin=0, ClampMin=0))` — If overridden, the number of warm-up frames to use for this render layer instead of the global value from the Warm Up Settings node. Generally this value should remain untouched unless this layer has specific needs that differ from the other layers. For example, if Lumen needs extra time to converge on this particular layer, then increase the value here.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphRenderPassNode.h` (Public)


#### class `UMovieGraphRenderPassNode`  
`class UMovieGraphRenderPassNode : public UMovieGraphSettingNode`  
_L27-164_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMovieGraphSettingNode`
- desc: The UMovieGraphRenderPassNode node defines a render pass that MRQ may produce. This node can be implemented in the graph multiple times, and the exact settings it should use can be created out of a mixture of nodes. Because of this, when rendering, MRQ will figure out how many layers there are that actually use this CDO and will call the function on the CDO once, providing the information about all instances. This will allow the node to create any number of instances (decoupled from the number of times the node is used in the graph).
- L32 _public function_ `UMovieGraphRenderPassNode()`
- L39 _public function_ `FString GetRendererName() const` — Get the name of this renderer. Deferred, Path Tracer, Panoramic, etc.
- L45 _public function_ `FString GetRendererSubName() const` — Get the sub-name of this renderer, which identifies a specific pass that this renderer generates. Each type of pass that this renderer generates should have a unique sub-name.
- L51 _public function_ `TSharedPtr<FMovieGraphRenderCameraSource> CreateRenderCameraSource(const UMovieGraphPipeline* InPipeline, const UMovieGraphEvaluatedConfig* EvaluatedConfig)` — Create a new camera source for this render node instance, or nullptr if this node uses default sequence cameras. Called on non-CDO instances.
- L57 _public function_ `TSharedPtr<FMovieGraphRenderCameraSource> GetRenderCameraSource() const` — Gets an existing camera source for this render node instance, or nullptr if this node uses default sequence cameras. Called on non-CDO instances.
- L64 _public function_ `void GatherRenderCameraSources(TArray<TSharedRef<FMovieGraphRenderCameraSource>>& InOutSources) const` — Collects custom camera sources from all active pass instances into InOutSources. Called on the CDO. @param InOutSources (in, out) May be non-empty on input; unique sources are appended.
- L67 _public function_ `void Setup(const FMovieGraphRenderPassSetupData& InSetupData)` — Called when this should set up for rendering a new shot. Called on the CDO.
- L70 _public function_ `void Teardown()` — Called when this should do teardown of resources. FlushRenderingCommands() will have already been called by this point. Called on the CDO.
- L73 _public function_ `void Render(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData)` — Called each tick (once per temporal sample). Called on the CDO.
- L81 _public function_ `void GatherOutputPasses(UMovieGraphEvaluatedConfig* InConfig, TArray<FMovieGraphRenderDataIdentifier>& OutExpectedPasses) const` — Called each output frame. Should add a series of FMovieGraphRenderDataIdentifiers to the array, and then when producing frames in Render, the resulting image data should have the matching FMovieGraphRenderDataIdentifiers associated with it. Used by the Output Merger to ensure all of the render data for a given frame has been generated before passing it on to write to disk. Called on the CDO.
- L84 _public function_ `void UpdateRenderPassTelemetry(FMoviePipelineEndShotRenderTelemetryContext& InOutTelemetry) const` — Called by the renderer to gather runtime telemetry from live render pass instances. Called on the CDO.
- L88 _public function_ `int32 GetNumSceneViewsRendered() const` — Gets the number of Scene Views (that is, renders of the 3d scene) that this pass will produce. Can be zero for things like UI Renderers, or more than one for things like panoramic or tiling.
- L95 _public function_ `void GetPreviewBannerMessages(const FMovieGraphRenderDataIdentifier& InIdentifier, TArray<FMovieGraphPreviewBannerMessage>& OutMessages) const` — Called by the renderer when gathering preview data. Implementations should *append* any banner messages contributed by pass instances that produced the preview tile identified by InIdentifier. Default implementation contributes nothing.
- L100 _public function_ `virtual int32 GetCoolingDownFrameCount() const` — Get the cooling down frame count when denoising based on temporal frames are used.
- L106 _public function_ `TArray<FSoftClassPath> GetOutputTypeRestrictions() const` — Gets the type(s) of output nodes that are allowed to process/output the pixel data originating from this node. Typically the return value is an empty array, meaning that all output nodes process the data.
- L108 _public function_ `virtual void ResolveTokenContainingProperties(TFunction<void(FString&)>& ResolveFunc, const FMovieGraphTokenResolveContext& InContext) override`
- L117 _public function_ `virtual FText GetMenuCategory() const override`
- L122 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L127 _public function_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override`
- L137 _protected member_ `uint8 bOverride_RendererName : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L140 _protected member_ `uint8 bOverride_RendererSubName : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L144 _protected member_ `FString RendererName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Naming", meta = (EditCondition="bOverride_RendererName", MrgTokenAutocomplete))` — The value that will be used in the {renderer_name} token.
- L148 _protected member_ `FString RendererSubName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Naming", meta = (EditCondition="bOverride_RendererSubName", MrgTokenAutocomplete))` — The value that will be used in the {renderer_sub_name} token.
- L151 _protected function_ `virtual FString GetRendererNameImpl() const`
- L152 _protected function_ `virtual FString GetRendererSubNameImpl() const`
- L153 _protected function_ `virtual void SetupImpl(const FMovieGraphRenderPassSetupData& InSetupData)`
- L154 _protected function_ `virtual void TeardownImpl()`
- L155 _protected function_ `virtual void RenderImpl(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData)`
- L156 _protected function_ `virtual void GatherOutputPassesImpl(UMovieGraphEvaluatedConfig* InConfig, TArray<FMovieGraphRenderDataIdentifier>& OutExpectedPasses) const`
- L157 _protected function_ `virtual void UpdateRenderPassTelemetryImpl(FMoviePipelineEndShotRenderTelemetryContext& InOutTelemetry) const`
- L158 _protected function_ `virtual int32 GetNumSceneViewsRenderedImpl() const`
- L159 _protected function_ `virtual void GetPreviewBannerMessagesImpl(const FMovieGraphRenderDataIdentifier& InIdentifier, TArray<FMovieGraphPreviewBannerMessage>& OutMessages) const`
- L160 _protected function_ `virtual TArray<FSoftClassPath> GetOutputTypeRestrictionsImpl() const`
- L161 _protected function_ `virtual TSharedPtr<FMovieGraphRenderCameraSource> CreateRenderCameraSourceImpl(const UMovieGraphPipeline* InMovieGraphPipeline, const UMovieGraphEvaluatedConfig* InEvaluatedConfig)`
- L162 _protected function_ `virtual TSharedPtr<FMovieGraphRenderCameraSource> GetRenderCameraSourceImpl() const`
- L163 _protected function_ `virtual void GatherRenderCameraSourcesImpl(TArray<TSharedRef<FMovieGraphRenderCameraSource>>& InOutSources) const`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphRerouteNode.h` (Public)


#### class `UMovieGraphRerouteNode`  
`class UMovieGraphRerouteNode : public UMovieGraphSettingNode`  
_L12-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- desc: A node which is effectively a no-op/passthrough. Allows a connection to be routed untouched through this node to organize the graph.
- L17 _public prototype_ `UMovieGraphRerouteNode();`
- L20 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetInputPinProperties() const override;`
- L21 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetOutputPinProperties() const override;`
- L22 _public prototype_ `virtual bool CanBeDisabled() const override;`
- L24 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L25 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L30 _public prototype_ `virtual UMovieGraphPin* GetPassThroughPin(const UMovieGraphPin* InFromPin) const;` — Gets the pin opposite to the specified InFromPin.
- L34 _public prototype_ `FMovieGraphPinProperties GetPinProperties() const;` — `UFUNCTION(BlueprintPure, Category = "Movie Graph")` — Sets the pin properties for this reroute node. Note that this applies to both the input and output pin.
- L41 _public prototype_ `void SetPinProperties(const FMovieGraphPinProperties& InPinProperties);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Sets the pin properties for this reroute node (both the input and output pin have the same properties). This generally should not be called unless you know what you're doing; normal connection/disconnection should handle setting the properties correctly.
- L46 _private member_ `FMovieGraphPinProperties InputOutputProperties;` — `UPROPERTY()` — Pin properties that are shared with both the input and output pins.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphSamplingMethodNode.h` (Public)


#### class `UMovieGraphSamplingMethodNode`  
`class UMovieGraphSamplingMethodNode : public UMovieGraphSettingNode`  
_L13-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- desc: A node which configures sampling properties for renderers.
- L18 _public prototype_ `UMovieGraphSamplingMethodNode();`
- L20 _public prototype_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override;`
- L21 _public prototype_ `virtual void GetFormatResolveArgs(FMovieGraphResolveArgs& OutMergedFormatArgs, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier) const override;`
- L24 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L25 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L26 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L30 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L34 _public member_ `uint8 bOverride_SamplingMethodClass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))`
- L37 _public member_ `uint8 bOverride_TemporalSampleCount : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))`
- L41 _public member_ `FSoftClassPath SamplingMethodClass;` — `UPROPERTY(NoClear, meta = (EditCondition = "bOverride_SamplingMethodClass", DisplayName = "Sampling Method", MetaClass = "/Script/MovieRenderPipelineCore.MovieGraphTimeStepBase", ShowDisplayNames))` — The type of sampling the render should use. Not currently marked as BlueprintReadWrite/EditAnywhere as there is only one class anyways.
- L45 _public member_ `int32 TemporalSampleCount;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (UIMin = 1, ClampMin = 1, EditCondition = "bOverride_TemporalSampleCount"))` — The number of temporal samples which should be taken on one frame. Applies only to linear sampling.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphSelectNode.h` (Public)


#### class `UMovieGraphSelectNode`  
`class UMovieGraphSelectNode : public UMovieGraphNode`  
_L13-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphNode`
- desc: A node which creates a condition that selects from a set of input branches.
- L18 _public prototype_ `UMovieGraphSelectNode();`
- L20 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetInputPinProperties() const override;`
- L21 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetOutputPinProperties() const override;`
- L22 _public prototype_ `virtual TArray<UMovieGraphPin*> EvaluatePinsToFollow(FMovieGraphEvaluationContext& InContext) const override;`
- L28 _public prototype_ `void SetDataType(const EMovieGraphValueType ValueType, UObject* InValueTypeObject = nullptr);` — Sets the data type for the select options and selected option (note that their data will be reset when this is called). For structs, enums, and objects, the value type object needs to be provided.
- L31 _public prototype_ `EMovieGraphValueType GetValueType() const;` — Gets the data type that the select node is currently using.
- L34 _public prototype_ `const UObject* GetValueTypeObject() const;` — Gets the value type object associated with the value type currently set (if any).
- L37 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L38 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L39 _public prototype_ `virtual FText GetKeywords() const override;`
- L40 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L41 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L44 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L51 _private member_ `TObjectPtr<UMovieGraphValueContainer> SelectOptions;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Options", meta=(ShowInnerProperties, FullyExpand="true"))` — The options that are available on the node.
- L55 _private member_ `TObjectPtr<UMovieGraphValueContainer> SelectedOption;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Options", meta=(ShowInnerProperties, FullyExpand="true"))` — The currently selected option.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphSetCVarValueNode.h` (Public)


#### class `UMovieGraphSetCVarValueNode`  
`class UMovieGraphSetCVarValueNode : public UMovieGraphSettingNode`  
_L13-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- desc: A node which can set a specific console variable's value.
- L17 _public prototype_ `UMovieGraphSetCVarValueNode() = default;`
- L19 _public prototype_ `virtual FString GetNodeInstanceName() const override;`
- L20 _public prototype_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override;`
- L21 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L22 _public prototype_ `virtual TArray<FMovieGraphPropertyInfo> GetOverrideablePropertyInfo() const override;`
- L25 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L26 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L27 _public prototype_ `virtual FText GetKeywords() const override;`
- L28 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L29 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L32 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L38 _public member_ `uint8 bOverride_Name : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L41 _public member_ `uint8 bOverride_Value : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L45 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "bOverride_Name"))` — The name of the CVar having its value set.
- L49 _public member_ `float Value;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "bOverride_Value"))` — The new value of the CVar.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphSetMetadataAttributesNode.h` (Public)


#### struct `FMovieGraphMetadataAttribute`  
`struct FMovieGraphMetadataAttribute`  
_L16-43_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a metadata attribute that can be included in a file.
- L20 _public function_ `FMovieGraphMetadataAttribute(const FString& InName, const FString& InValue, const bool bInIsEnabled = true) : Name(InName) , Value(InValue) , bIsEnabled(bInIsEnabled)`
- L27 _public function_ `FMovieGraphMetadataAttribute() : bIsEnabled(true)`
- L34 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta=(DisplayName="Metadata Name"))` — The name of the metadata attribute.
- L38 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta=(DisplayName="Metadata Value"))` — The value of the metadata attribute.
- L42 _public member_ `bool bIsEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta=(DisplayName="Metadata Enable State"))` — Enable state. If disabled, this metadata attribute won't be added to the file.

#### class `UMovieGraphMetadataAttributeCollection`  
`class UMovieGraphMetadataAttributeCollection : public UObject, public IMovieGraphTraversableObject`  
_L46-61_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IMovieGraphTraversableObject`
- L55 _public member_ `TArray<FMovieGraphMetadataAttribute> MetadataAttributes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metadata", meta=(DisplayName="Metadata Attributes"))` — An array of metadata attributes to be added to output files.
- L58 _public prototype_ `virtual void Merge(const IMovieGraphTraversableObject* InSourceObject) override;` — IMovieGraphTraversableObject interface
- L59 _public prototype_ `virtual TArray<TPair<FString, FString>> GetMergedProperties() const override;`

#### class `UMovieGraphSetMetadataAttributesNode`  
`class UMovieGraphSetMetadataAttributesNode : public UMovieGraphSettingNode`  
_L65-95_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- desc: A node which can set a specific metadata attributes.
- L70 _public prototype_ `UMovieGraphSetMetadataAttributesNode();`
- L72 _public prototype_ `virtual void GetFormatResolveArgs(FMovieGraphResolveArgs& OutMergedFormatArgs, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier) const override;`
- L75 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L76 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L77 _public prototype_ `virtual FText GetKeywords() const override;`
- L78 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L79 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L82 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L88 _public member_ `uint8 bOverride_MetadataAttributeCollection : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L94 _public member_ `TObjectPtr<UMovieGraphMetadataAttributeCollection> MetadataAttributeCollection;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category="Metadata", meta=(DisplayName="Metadata Attribute Collection", EditCondition="bOverride_MetadataAttributeCollection"))` — A container of metadata attributes to be added to the file.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphSetStartEndConsoleCommandsNode.h` (Public)


#### class `UMovieGraphStartEndConsoleCommands`  
`class UMovieGraphStartEndConsoleCommands : public UObject, public IMovieGraphTraversableObject`  
_L14-42_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IMovieGraphTraversableObject`
- desc: Console commands that can execute within the UMovieGraphSetStartEndConsoleCommandsNode.
- L24 _public member_ `TArray<FString> AddStartCommands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Add Commands")` — Console commands to execute when this shot starts rendering. If the command(s) need to be undone after the shot finishes rendering, add a matching entry to Add End Commands.
- L28 _public member_ `TArray<FString> AddEndCommands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Add Commands")` — Console commands to execute when this shot finishes rendering. Used to restore changes made by Add Console Commands.
- L32 _public member_ `TArray<FString> RemoveStartCommands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Remove Commands")` — Start commands that should be removed from upstream nodes. Commands entered here must be an exact match to upstream command(s) in order to be removed.
- L36 _public member_ `TArray<FString> RemoveEndCommands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Remove Commands")` — End commands that should be removed from upstream nodes. Commands entered here must be an exact match to upstream command(s) in order to be removed.
- L39 _public prototype_ `virtual void Merge(const IMovieGraphTraversableObject* InSourceObject) override;` — IMovieGraphTraversableObject interface
- L40 _public prototype_ `virtual TArray<TPair<FString, FString>> GetMergedProperties() const override;`

#### class `UMovieGraphSetStartEndConsoleCommandsNode`  
`class UMovieGraphSetStartEndConsoleCommandsNode : public UMovieGraphSettingNode`  
_L46-76_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- desc: A node which can set console commands to run at the start and end of a render.
- L50 _public prototype_ `UMovieGraphSetStartEndConsoleCommandsNode();`
- L53 _public prototype_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override;`
- L58 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L59 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L60 _public prototype_ `virtual FText GetKeywords() const override;`
- L61 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L62 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L66 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L72 _public member_ `uint8 bOverride_ConsoleCommands : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L75 _public member_ `TObjectPtr<UMovieGraphStartEndConsoleCommands> ConsoleCommands;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category="Settings", meta=(EditCondition="bOverride_ConsoleCommands"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphSubgraphNode.h` (Public)


#### class `UMovieGraphSubgraphNode`  
`class UMovieGraphSubgraphNode : public UMovieGraphNode`  
_L18-58_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphNode`
- desc: A node which represents another graph asset. Inputs/outputs on this subgraph will update if the underlying graph asset's inputs/outputs change.
- L23 _public prototype_ `UMovieGraphSubgraphNode();`
- L26 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetInputPinProperties() const override;`
- L27 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetOutputPinProperties() const override;`
- L28 _public prototype_ `virtual TArray<UMovieGraphPin*> EvaluatePinsToFollow(FMovieGraphEvaluationContext& InContext) const override;`
- L29 _public prototype_ `virtual FString GetResolvedValueForOutputPin(const FName& InPinName, const FMovieGraphTraversalContext* InContext) const override;`
- L32 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L33 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L39 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L45 _public prototype_ `void SetSubGraphAsset(const TSoftObjectPtr<UMovieGraphConfig>& InSubgraphAsset);` — `UFUNCTION(BlueprintCallable, Category="Graph")` — Sets the graph asset this subgraph points to.
- L49 _public prototype_ `UMovieGraphConfig* GetSubgraphAsset() const;` — `UFUNCTION(BlueprintCallable, Category="Graph")` — Gets the graph asset this subgraph points to.
- L53 _private prototype_ `void RefreshOnSubgraphAssetSaved();` — Update the subgraph to reflect the subgraph asset when the subgraph asset is saved.
- L57 _private member_ `TSoftObjectPtr<UMovieGraphConfig> SubgraphAsset;` — `UPROPERTY(EditAnywhere, Category="Graph")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphUIRendererNode.h` (Public)


#### class `UMovieGraphUIRendererNode`  
`class UMovieGraphUIRendererNode : public UMovieGraphWidgetRendererBaseNode`  
_L19-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphWidgetRendererBaseNode`
- desc: A node which renders the viewport's UMG widget to a standalone image, or composited on top of a render layer.
- L24 _public prototype_ `UMovieGraphUIRendererNode();`
- L27 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L28 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L29 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L32 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L36 _public member_ `static const FString RendererName;` — `UE_DEPRECATED(5.7, "RendererName usage is deprecated, please use GetRendererName() instead.")`
- L48 _protected prototype_ `virtual TUniquePtr<FMovieGraphWidgetPass> GeneratePass() override;` — UMovieGraphWidgetRendererBaseNode Interface

#### struct `UMovieGraphUIRendererNode::FMovieGraphUIPass`  
`struct FMovieGraphUIPass final : public FMovieGraphWidgetPass`  
_L40-45_
- inherits: `FMovieGraphWidgetPass`
- desc: A UI pass for a specific render layer. Instances are stored on the UMovieGraphWidgetRendererBaseNode CDO.
- L42 _public prototype_ `virtual void Setup(TWeakObjectPtr<UMovieGraphDefaultRenderer> InRenderer, const FMovieGraphRenderPassLayerData& InLayer) override;`
- L43 _public prototype_ `virtual TSharedPtr<SWidget> GetWidget(UMovieGraphWidgetRendererBaseNode* InNodeThisFrame) override;`
- L44 _public prototype_ `virtual int32 GetCompositingSortOrder() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphVariableNode.h` (Public)


#### class `UMovieGraphVariableNode`  
`class UMovieGraphVariableNode : public UMovieGraphNode`  
_L16-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphNode`
- desc: A node which gets the value of a variable which has been defined on the graph.
- L21 _public prototype_ `UMovieGraphVariableNode() = default;`
- L24 _public prototype_ `virtual void PostEditImport() override;`
- L27 _public prototype_ `virtual TArray<FMovieGraphPinProperties> GetOutputPinProperties() const override;`
- L28 _public prototype_ `virtual FString GetResolvedValueForOutputPin(const FName& InPinName, const FMovieGraphTraversalContext* InContext) const override;`
- L29 _public prototype_ `virtual bool GetResolvedValueForOutputPin(const FName& InPinName, const FMovieGraphTraversalContext* InContext, TObjectPtr<UMovieGraphValueContainer>& OutValueContainer) const override;`
- L33 _public prototype_ `UMovieGraphVariable* GetVariable() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Gets the variable that this node represents.
- L37 _public prototype_ `void SetVariable(UMovieGraphVariable* InVariable);` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Sets the variable that this node represents.
- L41 _public prototype_ `bool IsGlobalVariable() const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Graph")` — Returns true if this node represents a global variable, else false.
- L47 _public prototype_ `static bool GetResolvedVariableValue(const TObjectPtr<UMovieGraphVariable> InGraphVariable, const FMovieGraphTraversalContext* InContext, TObjectPtr<UMovieGraphValueContainer>& OutValueContainer);` — Resolves the provided variable, given a specific traversal context (needed in order to account for job-level overrides). If the variable value could be resolved, returns true and provides the value in OutValueContainer, otherwise returns false.
- L50 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L51 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L52 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L53 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L57 _private prototype_ `virtual void RegisterDelegates() override;`
- L60 _private prototype_ `void UpdateOutputPin(UMovieGraphMember* ChangedVariable) const;` — Updates the output pin on the node to match the provided variable.
- L63 _private prototype_ `static bool ContextHasEnabledAssignmentForVariable(const TObjectPtr<UMovieGraphVariable> InGraphVariable, const FMovieGraphTraversalContext* InContext, TObjectPtr<UMovieJobVariableAssignmentContainer>& OutVariableAssignment);` — Determines if the job in the given context has a valid, enabled variable assignment for the provided variable. Sets OutVariableAssignment if it does.
- L68 _private member_ `TObjectPtr<UMovieGraphVariable> GraphVariable = nullptr;` — `UPROPERTY()` — The underlying graph variable this node represents.
- L72 _private member_ `FMovieGraphPinProperties OutputPin;` — `UPROPERTY(Transient)` — The properties for the output pin on this node.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphVideoOutputNode.h` (Public)


#### struct `MovieRenderGraph::IVideoCodecWriter`  
`struct IVideoCodecWriter`  
_L19-37_
- L26 _public member_ `FString StableFileName;` — The filename without de-duplication numbers, used to match up multiple incoming frames back to the same writer. We use this when looking for existing writers so that we can avoid the de-duplication numbers perpetually increasing due to the file existing on disk after the first frame comes in, and then the next one de-duplicating to one more than that.
- L36 _public member_ `TMap<int32, FLightweightSourceData> LightweightSourceData;`

#### struct `MovieRenderGraph::IVideoCodecWriter::FLightweightSourceData`  
`struct FLightweightSourceData`  
_L32-35_
- desc: This array contains the indexes of each shot that contributed to this writer. This is needed so that after a shot/render, when all we have is the completed blocks of audio samples, we can figure out which blocks go to which video clips. Because of how you can split videos up by either shot, or by the whole sequence, there isn't an obvious mapping, so this array will tell the audio writing system which audio blocks should be sent to the shot.
- L34 _public member_ `int32 SubmittedFrameCount;`

#### class `UMovieGraphVideoOutputNode`  
`class UMovieGraphVideoOutputNode : public UMovieGraphFileOutputNode`  
_L68-140_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UMovieGraphFileOutputNode`
- desc: A base node for nodes that generate video in the Movie Render Graph.
- L73 _public prototype_ `UMovieGraphVideoOutputNode();`
- L89 _protected prototype_ `virtual void OnReceiveImageDataImpl(UMovieGraphPipeline* InPipeline, UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, const TSet<FMovieGraphRenderDataIdentifier>& InMask) override;` — UMovieGraphFileOutputNode Interface
- L90 _protected prototype_ `virtual void OnAllFramesSubmittedImpl(UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph) override;`
- L91 _protected prototype_ `virtual void OnAllFramesFinalizedImpl(UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph) override;`
- L92 _protected prototype_ `virtual void OnAllShotFramesSubmittedImpl(UMovieGraphPipeline* InPipeline, const UMoviePipelineExecutorShot* InShot, TObjectPtr<UMovieGraphEvaluatedConfig>& InShotEvaluatedGraph, const bool bFlushToDisk) override;`
- L93 _protected prototype_ `virtual bool IsFinishedWritingToDiskImpl() const override;`
- L96 _protected prototype_ `virtual TUniquePtr<MovieRenderGraph::IVideoCodecWriter> Initialize_GameThread(const FMovieGraphVideoNodeInitializationContext& InInitializationContext) PURE_VIRTUAL(UMovieGraphVideoOutputNode::Initialize_GameThread, return nullptr; );`
- L97 _protected prototype_ `virtual bool Initialize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) PURE_VIRTUAL(UMovieGraphVideoOutputNode::Initialize_EncodeThread, return true;);`
- L98 _protected prototype_ `virtual void WriteFrame_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter, FImagePixelData* InPixelData, TArray<FMovieGraphPassData>&& InCompositePasses, TObjectPtr<UMovieGraphEvaluatedConfig> InEvaluatedConfig, const FString& InBranchName) PURE_VIRTUAL(UMovieGraphVideoOutputNode::WriteFrame_EncodeThread);`
- L99 _protected prototype_ `virtual void BeginFinalize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) PURE_VIRTUAL(UMovieGraphVideoOutputNode::BeginFinalize_EncodeThread);`
- L100 _protected prototype_ `virtual void Finalize_EncodeThread(MovieRenderGraph::IVideoCodecWriter* InWriter) PURE_VIRTUAL(UMovieGraphVideoOutputNode::Finalize_EncodeThread);`
- L101 _protected prototype_ `virtual const TCHAR* GetFilenameExtension() const PURE_VIRTUAL(UMovieGraphVideoOutputNode::GetFilenameExtension, return TEXT(""););`
- L102 _protected prototype_ `virtual bool IsAudioSupported() const PURE_VIRTUAL(UMovieGraphVideoOutputNode::IsAudioSupported, return false;);`
- L124 _private prototype_ `void GetOutputFilePaths(const UMovieGraphPipeline* InPipeline, const UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, FMovieGraphPassData& InRenderPassData, const TArray<FMovieGraphPassData>& InCompositedPasses, FString& OutFinalFilePath, FString& OutStableFilePath);` — Generates a "stable" and "final" filename for a writer. The stable filename has not been put through a de-duplication procedure (ie, it might reference an existing file on disk). The final filename is what will be written to disk and will not reference an existing filename on disk (unless the user has specified that overwriting existing files is ok).
- L130 _private prototype_ `FMovieGraphCodecWriterWithPromise* GetOrCreateOutputWriter(UMovieGraphPipeline* InPipeline, const UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, FMovieGraphPassData& InRenderPassData, const TArray<FMovieGraphPassData>& InCompositedPasses);` — Generates the writer that is responsible for doing the encoding work. The writer will be added to AllWriters. If there was a problem creating the writer, nullptr will be returned and an error will be sent to the log.
- L136 _private member_ `inline static TArray<FMovieGraphCodecWriterWithPromise> AllWriters;` — All writers that are currently being run. There is one writer per filename. There might be multiple writers due to multiple passes being written out.
- L139 _private member_ `bool bHasError;` — Whether the output encountered any error, like failing to initialize properly.

#### struct `UMovieGraphVideoOutputNode::FMovieGraphVideoNodeInitializationContext`  
`struct FMovieGraphVideoNodeInitializationContext`  
_L77-86_
- desc: The parameters to Initialize_GameThread() have changed a lot -- using a struct as a the only parameter will make future changes easier.
- L79 _public member_ `UMovieGraphPipeline* Pipeline;`
- L80 _public member_ `TObjectPtr<UMovieGraphEvaluatedConfig> EvaluatedConfig;`
- L81 _public member_ `const FMovieGraphTraversalContext* TraversalContext;`
- L82 _public member_ `const FMovieGraphPassData* PassData;`
- L83 _public member_ `FIntPoint Resolution;`
- L84 _public member_ `FString FileName;`
- L85 _public member_ `bool bAllowOCIO;`

#### struct `UMovieGraphVideoOutputNode::FMovieGraphCodecWriterWithPromise`  
`struct FMovieGraphCodecWriterWithPromise`  
_L105-117_
- L107 _public prototype_ `FMovieGraphCodecWriterWithPromise(TUniquePtr<MovieRenderGraph::IVideoCodecWriter>&& InWriter, TPromise<bool>&& InPromise, UClass* InNodeType);`
- L110 _public member_ `TUniquePtr<MovieRenderGraph::IVideoCodecWriter> CodecWriter;` — The codec writer.
- L113 _public member_ `TPromise<bool> Promise;` — The promise that is provided to the pipeline that specifies whether or not the writer has finished.
- L116 _public member_ `UClass* NodeType;` — The type of node associated with this writer.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L15 _namespace_ `namespace MoviePipeline`
- L17 _namespace_ `namespace MovieRenderGraph`
- L39 _namespace_ `namespace Audio` (scope `MovieRenderGraph`)
- L56 _prototype_ `void WriteShotAudioSamples( const MoviePipeline::FAudioState& InAudioData, const TMap<int32, IVideoCodecWriter::FLightweightSourceData>& InLightweightSourceData, const FFrameRate& InOutputFrameRate, TFunctionRef<void(TArrayView<int16>)> InWriteSampleCallback);` (scope `MovieRenderGraph::Audio`) — Resolves per-shot audio recordings from the audio renderer into shot-aligned int16 buffers and invokes InWriteSampleCallback once per shot, in increasing shot-index order. The main submix has ~24 ms of recording latency, so each shot's recording is offset: shot 0 is short by L, and shot N>0's first L samples are actually shot (N-1)'s tail. This helper redistributes samples from shot[N+1]'s head onto shot[N]'s tail until each shot matches its expected length, then truncates each shot to its expected length before passing it to InWriteSampleCallback. The deficit accumulates onto the last shot, which ends ~24 ms early. @param InAudioData              Audio state captured by the audio renderer (provides per-shot FinishedSegments). @param InLightweightSourceData  Per-shot writer source data (provides SubmittedFrameCount). @param InOutputFrameRate        Video frame rate used to size each shot's expected sample count. @param InWriteSampleCallback    Invoked once per shot with the channel-interleaved int16 buffer.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphWarmUpSettingNode.h` (Public)


#### class `UMovieGraphWarmUpSettingNode`  
`class UMovieGraphWarmUpSettingNode : public UMovieGraphSettingNode`  
_L12-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode`
- L16 _public prototype_ `UMovieGraphWarmUpSettingNode();`
- L19 _public prototype_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override;` — UMovieGraphSettingNode Interface
- L20 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L22 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive) const override;`
- L23 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L31 _public member_ `uint8 bOverride_NumWarmUpFrames : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L34 _public member_ `uint8 bOverride_LayerWarmUpFrames : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L37 _public member_ `uint8 bOverride_bEmulateMotionBlur : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L41 _public member_ `int32 NumWarmUpFrames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta=(EditCondition="bOverride_NumWarmUpFrames"))` — At the start of each shot, how many frames should we run the engine (without writing renders to disk) to warm up various systems.
- L52 _public member_ `int32 LayerWarmUpFrames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta=(EditCondition="bOverride_LayerWarmUpFrames", UIMin=0, ClampMin=0))` — The number of warm-up frames to run before each render layer's final render, with that layer's modifiers active. Layer warm-up frames let Lumen's lighting converge to the layer's contents before rendering the frame that's actually written to disk. Contrast with NumWarmUpFrames, which runs at the start of the shot rather than per-layer. Layer warm-ups are helpful when layer contents change substantially in ways that affect lighting.
- L58 _public member_ `bool bEmulateMotionBlur;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bOverride_bEmulateMotionBlur"))` — If true, we will evaluate frame 0, and then wait NumWarmUpFrames frames, rendering each one as we go. Then we will evaluate frame 1, and then frame 0 again. This emulates motion blur on the first frame (which normally needs data before frame 0). If false, we will "walk" towards the first frame of the shot, starting NumWarmUpFrames before the shot normally starts.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Nodes/MovieGraphWidgetRendererBaseNode.h` (Public)


#### class `UMovieGraphWidgetRendererBaseNode`  
`class UMovieGraphWidgetRendererBaseNode : public UMovieGraphRenderPassNode`  
_L23-89_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMovieGraphRenderPassNode`
- desc: Base node containing common logic for nodes that render widgets.
- L29 _public member_ `uint8 bOverride_bCompositeOntoFinalImage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L33 _public member_ `bool bCompositeOntoFinalImage = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bOverride_bCompositeOntoFinalImage"), Category="Widget Settings")` — If true, the pass will be composited onto each render. Does not apply to multi-layer EXR files.
- L60 _protected member_ `TSharedPtr<FWidgetRenderer> WidgetRenderer;` — Widget renderer shared with all FMovieGraphWidgetPass instances.
- L63 _protected member_ `TArray<TUniquePtr<FMovieGraphWidgetPass>> CurrentInstances;` — Render passes generated by GeneratePass() calls on the CDO.
- L67 _protected prototype_ `virtual TUniquePtr<FMovieGraphWidgetPass> GeneratePass() PURE_VIRTUAL(UMovieGraphWidgetRendererBaseNode::GeneratePass, return nullptr;);` — Generate a new pass that the widget renderer will use.
- L70 _protected prototype_ `virtual FString GetFileNameFormatOverride() const;` — Gets the file name that the render will write to if not performing a composite.
- L73 _protected prototype_ `virtual FString GetLayerNameOverride() const;` — Gets the layer name this render will use when writing to multi-layer formats. An empty string means no override, and the default will be used .
- L76 _protected prototype_ `virtual void SetupImpl(const FMovieGraphRenderPassSetupData& InSetupData) override;` — UMovieGraphRenderPassNode Interface
- L77 _protected prototype_ `virtual void TeardownImpl() override;`
- L78 _protected prototype_ `virtual void RenderImpl(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;`
- L79 _protected prototype_ `virtual void GatherOutputPassesImpl(UMovieGraphEvaluatedConfig* InConfig, TArray<FMovieGraphRenderDataIdentifier>& OutExpectedPasses) const override;`
- L84 _private member_ `TMap<const FIntPoint, TSharedPtr<SVirtualWindow>> SharedVirtualWindows;` — Virtual window instances shared with all FMovieGraphWidgetPass instances, keyed by resolution.
- L88 _private prototype_ `TSharedPtr<SVirtualWindow> GetOrCreateVirtualWindow(const FIntPoint& InResolution);` — Gets an existing virtual window with the specified resolution, or creates a new one if one does not exist yet.

#### struct `UMovieGraphWidgetRendererBaseNode::FMovieGraphWidgetPass`  
`struct FMovieGraphWidgetPass`  
_L37-57_
- desc: A render pass for a specific render layer, generated by the UMovieGraphWidgetRendererBaseNode CDO.
- L39 _public prototype_ `virtual ~FMovieGraphWidgetPass() = default;`
- L41 _public prototype_ `virtual void Setup(TWeakObjectPtr<UMovieGraphDefaultRenderer> InRenderer, const FMovieGraphRenderPassLayerData& InLayer);`
- L42 _public prototype_ `virtual void Teardown();`
- L43 _public prototype_ `virtual TSharedPtr<SWidget> GetWidget(UMovieGraphWidgetRendererBaseNode* InNodeThisFrame) = 0;`
- L44 _public prototype_ `virtual void Render(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData);`
- L45 _public prototype_ `virtual void GatherOutputPasses(TArray<FMovieGraphRenderDataIdentifier>& OutExpectedPasses) const;`
- L46 _public prototype_ `virtual int32 GetCompositingSortOrder() const = 0;`
- L47 _public prototype_ `virtual UMovieGraphWidgetRendererBaseNode* GetParentNode(UMovieGraphEvaluatedConfig* InConfig) const;`
- L50 _protected member_ `FMovieGraphRenderPassLayerData LayerData;`
- L53 _protected member_ `FMovieGraphRenderDataIdentifier RenderDataIdentifier;` — Unique identifier passed in GatherOutputPasses and with each render that identifies the data produced by this renderer.
- L56 _protected member_ `TWeakObjectPtr<UMovieGraphDefaultRenderer> Renderer;` — The renderer associated with this pass.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/Renderers/MovieGraphShowFlags.h` (Public)


#### class `UMovieGraphShowFlags`  
`class UMovieGraphShowFlags : public UObject, public IMovieGraphTraversableObject`  
_L20-88_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IMovieGraphTraversableObject`
- desc: Stores show flag enable/disable state, as well as per-flag override state. Here, enable/disable state refers to the actual state of the show flag itself (ie, whether it is turned on or off). This is the value that will be applied to renders. "Override" state is whether the flag has been marked as overridden in the UI (ie, whether it is a value that graph traversal should respect). Flags must be marked as overridden in order for their values to deviate from the default.
- L25 _public prototype_ `UMovieGraphShowFlags();`
- L28 _public prototype_ `FEngineShowFlags GetShowFlags() const;` — Gets a copy of the show flags. If they need to be modified, use one of the Set*() methods.
- L31 _public prototype_ `bool IsShowFlagEnabled(const uint32 ShowFlagIndex) const;` — Gets the enable/disable state for a specific show flag.
- L34 _public prototype_ `void SetShowFlagEnabled(const uint32 ShowFlagIndex, const bool bIsShowFlagEnabled);` — Sets the enable/disable state for a specific show flag. The flag must be marked as overridden for this to have an effect.
- L37 _public prototype_ `bool IsShowFlagOverridden(const uint32 ShowFlagIndex) const;` — Gets the override state for a specific show flag.
- L40 _public prototype_ `void SetShowFlagOverridden(const uint32 ShowFlagIndex, const bool bIsOverridden);` — Sets the override state for a specific show flag.
- L43 _public prototype_ `const TSet<uint32>& GetOverriddenShowFlags() const;` — Gets the indices of all show flags that have been overridden.
- L46 _public prototype_ `bool IsShowFlagSetToDefaultValue(const uint32 ShowFlagIndex) const;` — Determines if the provided show flag is set to a non-default value. The override state does not impact the value returned.
- L49 _public prototype_ `void RevertShowFlagToDefaultValue(const uint32 ShowFlagIndex);` — Reverts the provided show flag to its default value. Does not impact the override state for the flag.
- L56 _public prototype_ `void ApplyDefaultShowFlagValue(const uint32 ShowFlagIndex, const bool bShowFlagState);` — Applies a default value to the show flags. However, the default will not be applied if a user has already specified an override for the flag. This should generally only be called from renderers in order for them to specify defaults that are relevant.
- L59 _public prototype_ `virtual void Merge(const IMovieGraphTraversableObject* InSourceObject) override;` — IMovieGraphTraversableObject interface
- L60 _public prototype_ `virtual TArray<TPair<FString, FString>> GetMergedProperties() const override;`
- L65 _private prototype_ `void CopyOverridesToShowFlags(FEngineShowFlags& InEngineShowFlags) const;` — Copies the overrides from ShowFlagEnableState to InEngineShowFlags.
- L73 _private member_ `TSet<uint32> OverriddenShowFlags;` — `UPROPERTY()` — The show flags which have been marked as overridden in the UI (note this is NOT the enabled/disabled state of the flag itself).
- L80 _private member_ `TMap<uint32, bool> ShowFlagEnableState;` — `UPROPERTY()` — If the flag has been marked as overridden, this stores the enable/disable state of the flag. Key = show flag index, value = enable/disable state of the flag.
- L87 _private member_ `FEngineShowFlags ShowFlags;` — The default show flag state. Since FEngineShowFlags itself cannot be serialized (it is not a USTRUCT), we need to keep track of sparse overrides (ShowFlagEnableState) on top of the base state that these flags are initialized with (ESFIM_Game, plus any additional flags that a specialized renderer specifies).

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MovieJobVariableAssignmentContainer.h` (Public)


#### class `UMovieJobVariableAssignmentContainer`  
`class UMovieJobVariableAssignmentContainer : public UObject`  
_L23-285_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Holds a group of properties which override variable values on the job's associated graph (if any). Overrides are not added manually. Instead, UpdateGraphVariableOverrides() should be called which will update, add, or remove overrides as appropriate. After the update, overrides can have their values retrieved and set.
- L28 _public prototype_ `UMovieJobVariableAssignmentContainer() = default;`
- L34 _public prototype_ `void SetGraphConfig(const TSoftObjectPtr<UMovieGraphConfig>& InGraphConfig);` — `UFUNCTION(BlueprintCallable, Category="Graph")` — Sets the graph config associated with the variable assignments.
- L38 _public prototype_ `TSoftObjectPtr<UMovieGraphConfig> GetGraphConfig() const;` — `UFUNCTION(BlueprintCallable, Category="Graph")` — Gets the graph that is associated with this container.
- L41 _public prototype_ `uint32 GetNumAssignments() const;` — Gets the number of variable assignments present in this container. Assignments that are disabled are counted.
- L45 _public prototype_ `bool GetValueBool(const UMovieGraphVariable* InGraphVariable, bool& bOutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the bool value of the specified property. Returns true on success, else false.
- L49 _public prototype_ `bool GetValueByte(const UMovieGraphVariable* InGraphVariable, uint8& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the byte value of the specified property. Returns true on success, else false.
- L53 _public prototype_ `bool GetValueInt32(const UMovieGraphVariable* InGraphVariable, int32& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the int32 value of the specified property. Returns true on success, else false.
- L57 _public prototype_ `bool GetValueInt64(const UMovieGraphVariable* InGraphVariable, int64& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the int64 value of the specified property. Returns true on success, else false.
- L61 _public prototype_ `bool GetValueFloat(const UMovieGraphVariable* InGraphVariable, float& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the float value of the specified property. Returns true on success, else false.
- L65 _public prototype_ `bool GetValueDouble(const UMovieGraphVariable* InGraphVariable, double& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the double value of the specified property. Returns true on success, else false.
- L69 _public prototype_ `bool GetValueName(const UMovieGraphVariable* InGraphVariable, FName& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the FName value of the specified property. Returns true on success, else false.
- L73 _public prototype_ `bool GetValueString(const UMovieGraphVariable* InGraphVariable, FString& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the FString value of the specified property. Returns true on success, else false.
- L77 _public prototype_ `bool GetValueText(const UMovieGraphVariable* InGraphVariable, FText& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the FText value of the specified property. Returns true on success, else false.
- L81 _public prototype_ `bool GetValueEnum(const UMovieGraphVariable* InGraphVariable, uint8& OutValue, const UEnum* RequestedEnum = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the enum value (for a specific enum) of the specified property. Returns true on success, else false.
- L84 _public prototype_ `bool GetValueStruct(const UMovieGraphVariable* InGraphVariable, FStructView& OutValue, const UScriptStruct* RequestedStruct = nullptr) const;` — Gets the struct value (for a specific struct) of the specified property. Returns true on success, else false.
- L88 _public prototype_ `bool GetValueObject(const UMovieGraphVariable* InGraphVariable, UObject*& OutValue, const UClass* RequestedClass = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the object value (for a specific class) of the specified property. Returns true on success, else false.
- L92 _public prototype_ `bool GetValueClass(const UMovieGraphVariable* InGraphVariable, UClass*& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the UClass value of the specified property. Returns true on success, else false.
- L96 _public prototype_ `FString GetValueSerializedString(const UMovieGraphVariable* InGraphVariable);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the serialized string value of the specified property.
- L100 _public function_ `template <typename T> bool GetValueEnum(const UMovieGraphVariable* InGraphVariable, T& OutValue) const` — Gets the enum value of the specified property. Returns true on success, else false.
- L108 _public function_ `template <typename T> bool GetValueStruct(const UMovieGraphVariable* InGraphVariable, T*& OutValue) const` — Gets the struct value of the specified property. Returns true on success, else false.
- L116 _public function_ `template <typename T> bool GetValueObject(const UMovieGraphVariable* InGraphVariable, T*& OutValue) const` — Gets the object value of the specified property. Returns true on success, else false.
- L124 _public prototype_ `bool SetValueBool(const UMovieGraphVariable* InGraphVariable, const bool bInValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the bool value of the specified property. Returns true on success, else false.
- L128 _public prototype_ `bool SetValueByte(const UMovieGraphVariable* InGraphVariable, const uint8 InValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the byte value of the specified property. Returns true on success, else false.
- L132 _public prototype_ `bool SetValueInt32(const UMovieGraphVariable* InGraphVariable, const int32 InValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the int32 value of the specified property. Returns true on success, else false.
- L136 _public prototype_ `bool SetValueInt64(const UMovieGraphVariable* InGraphVariable, const int64 InValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the int64 value of the specified property. Returns true on success, else false.
- L140 _public prototype_ `bool SetValueFloat(const UMovieGraphVariable* InGraphVariable, const float InValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the float value of the specified property. Returns true on success, else false.
- L144 _public prototype_ `bool SetValueDouble(const UMovieGraphVariable* InGraphVariable, const double InValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the double value of the specified property. Returns true on success, else false.
- L148 _public prototype_ `bool SetValueName(const UMovieGraphVariable* InGraphVariable, const FName InValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the FName value of the specified property. Returns true on success, else false.
- L152 _public prototype_ `bool SetValueString(const UMovieGraphVariable* InGraphVariable, const FString& InValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the FString value of the specified property. Returns true on success, else false.
- L156 _public prototype_ `bool SetValueText(const UMovieGraphVariable* InGraphVariable, const FText& InValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the FText value of the specified property. Returns true on success, else false.
- L160 _public prototype_ `bool SetValueEnum(const UMovieGraphVariable* InGraphVariable, const uint8 InValue, const UEnum* Enum);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the enum value of the specified property. Returns true on success, else false.
- L163 _public prototype_ `bool SetValueStruct(const UMovieGraphVariable* InGraphVariable, FConstStructView InValue);` — Sets the struct value of the specified property. Returns true on success, else false.
- L167 _public prototype_ `bool SetValueObject(const UMovieGraphVariable* InGraphVariable, UObject* InValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the object value of the specified property. Returns true on success, else false.
- L171 _public prototype_ `bool SetValueClass(const UMovieGraphVariable* InGraphVariable, UClass* InValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the class value of the specified property. Returns true on success, else false.
- L175 _public prototype_ `bool SetValueSerializedString(const UMovieGraphVariable* InGraphVariable, const FString& NewValue);` — `UFUNCTION(BlueprintCallable, Category="Value")` — Sets the serialized value of this member. The string should be the serialized representation of the value. Returns true on success, else false.
- L179 _public function_ `template <typename T> bool SetValueEnum(const UMovieGraphVariable* InGraphVariable, const T InValue)` — Sets the enum value of the specified property. Returns true on success, else false.
- L186 _public function_ `template <typename T> bool SetValueStruct(const UMovieGraphVariable* InGraphVariable, const T& InValue)` — Sets the struct value of the specified property. Returns true on success, else false.
- L193 _public function_ `template <typename T> bool SetValueObject(const UMovieGraphVariable* InGraphVariable, T* InValue)` — Sets the object value of the specified property. Returns true on success, else false.
- L200 _public prototype_ `EMovieGraphValueType GetValueType(const UMovieGraphVariable* InGraphVariable) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the type of the value stored in the specified property.
- L204 _public prototype_ `const UObject* GetValueTypeObject(const UMovieGraphVariable* InGraphVariable) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the object that defines the enum, struct, or class stored in the specified property.
- L208 _public prototype_ `EMovieGraphContainerType GetValueContainerType(const UMovieGraphVariable* InGraphVariable) const;` — `UFUNCTION(BlueprintCallable, Category="Value")` — Gets the container type of the stored value in the specified property.
- L214 _public prototype_ `bool GetValueContainer(const UMovieGraphVariable* InGraphVariable, TObjectPtr<UMovieGraphValueContainer>& OutValueContainer);` — Gets a value container object rather than a strongly-typed value. Useful if the type of the value is not known ahead of time. If no property for the specified variable exists, OutValueContainer will not be modified.
- L221 _public prototype_ `bool SetVariableAssignmentEnableState(const UMovieGraphVariable* InGraphVariable, bool bIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Graph")` — Updates an existing variable assignment for the provided graph variable to a new enable state, or adds a new assignment and updates its enable state. Returns true on success, else false.
- L228 _public prototype_ `bool GetVariableAssignmentEnableState(const UMovieGraphVariable* InGraphVariable, bool& bOutIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Graph")` — Gets the enable state of the variable assignment for the provided graph variable. The enable state is provided via bOutIsEnabled. Returns true if an enable state was set on the variable and bOutIsEnabled was changed, else false.
- L238 _public prototype_ `void UpdateGraphVariableOverrides();` — `UFUNCTION(BlueprintCallable, Category = "Graph")` — Updates the stored variable overrides to reflect the graph preset. Existing overrides will be updated to match the graph variable name, value type, object type, and container type. Additionally, stale overrides that have no corresponding graph variable will be removed, and overrides will be created for graph variables which do not have existing overrides.
- L246 _protected prototype_ `bool AddVariableAssignment(const UMovieGraphVariable* InGraphVariable);` — Add a variable assignment for the graph. Returns true if the variable was added or it already exists, else false.
- L252 _protected prototype_ `bool FindOrGenerateVariableOverride(const UMovieGraphVariable* InGraphVariable, FPropertyBagPropertyDesc* OutPropDesc = nullptr, FPropertyBagPropertyDesc* OutEditConditionPropDesc = nullptr, bool bGenerateIfNotExists = true);` — Finds a variable assignment for the provided variable, or adds one if one does not already exist (and bAddIfNotExists is set to true). Returns nullptr if the operation failed.
- L256 _protected prototype_ `bool GenerateVariableOverride(const UMovieGraphVariable* InGraphVariable, FPropertyBagPropertyDesc* OutPropDesc = nullptr, FPropertyBagPropertyDesc* OutEditConditionPropDesc = nullptr);` — Generates a variable override for the provided variable, as well as the associated EditCondition for it.
- L260 _protected prototype_ `FName ConvertVariableToInternalName(const UMovieGraphVariable* InGraphVariable) const;` — Given a graph variable, retrieve the hidden internal name used by our actual property bag.
- L264 _private member_ `static inline FName VariableGuidMetaDataKey = FName(TEXT("Vari` — The metadata key on properties that is associated with a value which identifies a graph variable (by GUID).
- L267 _private member_ `static inline FName ToolTipMetaDataKey = FName(TEXT("Tool` — The metadata key on properties that is associated with a tooltip value.
- L270 _private member_ `static inline FName CategoryMetaDataKey = FName(TEXT("Cate` — The metadata key on properties that is associated with the variable's category.
- L273 _private member_ `static inline FName DisplayNameMetaDataKey = FName(TEXT("Disp` — The metadata key on properties that is associated with the variable's display name.
- L276 _private member_ `static inline FName EnableCategoriesMetaDataKey = FName(TEXT("Enab` — The metadata key on property bag properties that allows them to show up grouped in the details panel.
- L280 _private member_ `FInstancedPropertyBag Value;` — `UPROPERTY(EditAnywhere, meta=(ShowOnlyInnerProperties, FixedLayout), Category = "Value")` — The properties managed by this object.
- L284 _private member_ `TSoftObjectPtr<UMovieGraphConfig> GraphPreset;` — `UPROPERTY()` — The graph preset associated with the variable overrides.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipeline.h` (Public)


#### class `UMoviePipeline`  
`class UMoviePipeline : public UMoviePipelineBase`  
_L43-450_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineBase`
- L48 _public prototype_ `UMoviePipeline();`
- L55 _public prototype_ `void Initialize(UMoviePipelineExecutorJob* InJob);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Initialize the movie pipeline with the specified settings. This kicks off the rendering process. @param InJob	- This contains settings and sequence to render this Movie Pipeline with.
- L58 _public prototype_ `virtual void RequestShutdownImpl(bool bIsError) override;` — UMoviePipelineBase Interface
- L59 _public prototype_ `virtual void ShutdownImpl(bool bError ) override;`
- L60 _public function_ `virtual bool IsShutdownRequestedImpl() const override`
- L61 _public function_ `virtual EMovieRenderPipelineState GetPipelineStateImpl() const override`
- L62 _public function_ `virtual bool IsPostShotCallbackNeeded() const override`
- L69 _public function_ `FDateTime GetInitializationTime() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns the time this movie pipeline was initialized at.
- L77 _public function_ `FTimespan GetInitializationTimeOffset() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — The offset that should be applied to the GetInitializationTime() when generating the {time} related filename tokens. GetInitializationTime() is in UTC so this is either zero (if you called SetInitializationTime) or your offset from UTC.
- L89 _public function_ `void SetInitializationTime(const FDateTime& InDateTime)` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Override the time this movie pipeline was initialized at. This can be used for render farms to ensure that jobs on all machines use the same date/time instead of each calculating it locally. Clears the auto-calculated InitializationTimeOffset, meaning time tokens will be written in UTC. Needs to be called after ::Initialize(...) @param InDateTime - Expected to be in UTC timezone.
- L96 _public prototype_ `UMoviePipelinePrimaryConfig* GetPipelinePrimaryConfig() const;` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Get the Primary Configuration used to render this shot. This contains the global settings for the shot, as well as per-shot configurations which can contain their own settings.
- L99 _public function_ `ULevelSequence* GetTargetSequence() const`
- L102 _public function_ `UTexture* GetPreviewTexture() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L104 _public function_ `void SetPreviewTexture(UTexture* InTexture)`
- L106 _public function_ `const TArray<UMoviePipelineExecutorShot*>& GetActiveShotList() const`
- L108 _public function_ `int32 GetCurrentShotIndex() const`
- L109 _public function_ `const FMoviePipelineFrameOutputState& GetOutputState() const`
- L112 _public function_ `UMoviePipelineExecutorJob* GetCurrentJob() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L114 _public prototype_ `FMoviePipelineOutputData GetOutputDataParams();`
- L116 _public prototype_ `void GetSidecarCameraData(UMoviePipelineExecutorShot* InShot, int32 InCameraIndex, FMinimalViewInfo& OutViewInfo, class UCameraComponent** OutCameraComponent) const;`
- L117 _public prototype_ `bool GetSidecarCameraViewPoints(UMoviePipelineExecutorShot* InShot, TArray<FVector>& OutSidecarViewLocations, TArray<FRotator>& OutSidecarViewRotations) const;`
- L120 _public prototype_ `float GetCachedCameraOverscan(int32 InCameraIndex) const;` — Gets any cached overscan for the specified camera, or 0 if no cached overscan was found
- L123 _public prototype_ `bool HasCachedCameraOverscan(int32 InCameraIndex) const;` — Gets whether there is a cached overscan value for the specified camera
- L126 _public prototype_ `void CacheCameraOverscan(int32 InCameraIndex, float InCameraOverscan);` — Caches the provided overscan value for the specified camera
- L130 _public prototype_ `void WarnAboutAnimatedOverscan(float InInitialOverscan);` — `UE_DEPRECATED(5.6, "WarnAboutAnimatedOverscan is no longer used; animated overscan is supported in 5.6")` — Outputs a warning message regarding animated overscan to the MRQ log if one has not already been output
- L133 _public function_ `const FMovieSceneExportMetadata& GetOutputMetadata() const`
- L138 _public prototype_ `void AddFrameToOutputMetadata(const FString& ClipName, const FString& ImageSequenceFileName, const FMoviePipelineFrameOutputState& FrameOutputState, const FString& Extension, const bool bHasAlpha);`
- L140 _public prototype_ `void AddOutputFuture(TFuture<bool>&& OutputFuture, const MoviePipeline::FMoviePipelineOutputFutureData& InData);`
- L142 _public prototype_ `void ProcessOutstandingFinishedFrames();`
- L143 _public prototype_ `void ProcessOutstandingFutures();`
- L144 _public prototype_ `void OnSampleRendered(TUniquePtr<FImagePixelData>&& OutputSample);`
- L145 _public function_ `const MoviePipeline::FAudioState& GetAudioState() const`
- L146 _public function_ `void SetFlushDiskWritesPerShot(const bool bFlushWrites)`
- L147 _public function_ `bool IsFlushDiskWritesPerShot() const`
- L150 _public function_ `template<typename SettingType> SettingType* FindOrAddSettingForShot(const UMoviePipelineExecutorShot* InShot) const`
- L156 _public function_ `template<typename SettingType> TArray<SettingType*> FindSettingsForShot(const UMoviePipelineExecutorShot* InShot) const`
- L168 _public prototype_ `TArray<UMoviePipelineSetting*> FindSettingsForShot(TSubclassOf<UMoviePipelineSetting> InSetting, const UMoviePipelineExecutorShot* InShot) const;`
- L182 _public prototype_ `void ResolveFilenameFormatArguments(const FString& InFormatString, const TMap<FString, FString>& InFormatOverrides, FString& OutFinalPath, FMoviePipelineFormatArgs& OutFinalFormatArgs, const FMoviePipelineFrameOutputState* InOutputState=nullptr, const int32 InFrameNumberOffset=0) const;` — Resolves the provided InFormatString by converting {format_strings} into settings provided by the primary config. @param	InFormatString		A format string (in the form of "{format_key1}_{format_key2}") to resolve. @param	InFormatOverrides	A series of Key/Value pairs to override particular format keys. Useful for things that change based on the caller such as filename extensions. @return	OutFinalPath			The final filepath based on a combination of the format string, the format overrides, and the current output state. @return	OutFinalFormatArgs	The format arguments that were actually used to fill the format string (including file metadata) @param	InOutputState		(optional) The output state for frame information. @param	InFrameNumberOffset	(optional) Frame offset of the frame we want the filename for, if not the current frame as specified in InOutputState
- L188 _public function_ `void SetViewportInitArgs(const UE::MoviePipeline::FViewportArgs& InArgs)` — Allows initialization of some viewport-related arguments that aren't related to the job. Needs to be called before the Initialize function. Optional.
- L195 _protected prototype_ `virtual void OnMoviePipelineFinishedImpl();` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — This function should be called by the Executor when execution has finished (this should still be called in the event of an error)
- L199 _private prototype_ `void LoadDebugWidget();` — Instantiate our Debug UI Widget and initialize it to ourself.
- L202 _private prototype_ `void OnEngineTickBeginFrame();` — Called before the Engine ticks for the given frame. We use this to calculate delta times that the frame should use.
- L205 _private prototype_ `void OnEngineTickEndFrame();` — Called after the Engine has ticked for a given frame. Everything in the world has been updated by now so we can submit things to render.
- L207 _private prototype_ `void ValidateSequenceAndSettings() const;`
- L211 _private prototype_ `void TickProducingFrames();` — Runs the per-tick logic when doing the ProducingFrames state.
- L213 _private prototype_ `void ProcessEndOfCameraCut(UMoviePipelineExecutorShot* InCameraCut);`
- L217 _private prototype_ `void BeginFinalize();` — Called once when first moving to the Finalize state.
- L219 _private prototype_ `void BeginExport();` — Called once when first moving to the Export state.
- L222 _private prototype_ `void StartUnrealInsightsCapture();` — Attempts to start an Unreal Insights capture to a file on disk adjacent to the movie output.
- L224 _private prototype_ `void StopUnrealInsightsCapture();` — Attempts to stop an already started Unreal Insights capture.
- L231 _private prototype_ `void TickFinalizeOutputContainers(const bool bInForceFinish);` — Runs the per-tick logic when doing the Finalize state. @param bInForceFinish		If true, this function will not return until all Output Containers say they have finalized.
- L238 _private prototype_ `void TickPostFinalizeExport(const bool bInForceFinish);` — Runs the per-tick logic when doing the Export state. This is spread over multiple ticks to allow non-blocking background processes (such as extra encoding). @param bInForceFinish		If true, this function will not return until all exports say they have finished.
- L241 _private prototype_ `bool DebugFrameStepPreTick();` — Return true if we should early out of the TickProducingFrames function. Decrements the remaining number of steps when false.
- L243 _private prototype_ `bool IsDebugFrameStepIdling() const;` — Returns true if we are idling because of debug frame stepping.
- L246 _private prototype_ `void OnSequenceEvaluated(const UMovieSceneSequencePlayer& Player, FFrameTime CurrentTime, FFrameTime PreviousTime);` — Debugging/Information. Don't hinge any logic on this as it will get called multiple times per frame in some cases.
- L249 _private prototype_ `void InitializeShot(UMoviePipelineExecutorShot* InShot);` — Set up per-shot state for the specific shot, tearing down old state (if it exists)
- L250 _private prototype_ `void TeardownShot(UMoviePipelineExecutorShot* InShot);`
- L253 _private prototype_ `void SetupRenderingPipelineForShot(UMoviePipelineExecutorShot* InShot);` — Initialize the rendering pipeline for the given shot. This should not get called if rendering work is still in progress for a previous shot.
- L255 _private prototype_ `void TeardownRenderingPipelineForShot(UMoviePipelineExecutorShot* InShot);` — Deinitialize the rendering pipeline for the given shot.
- L258 _private prototype_ `void FlushAsyncEngineSystems();` — Flush any async resources in the engine that need to be finalized before submitting anything to the GPU, ie: Streaming Levels and Shaders
- L261 _private prototype_ `void PrintVerboseLogForFiles(const TArray<FMoviePipelineShotOutputData>& InOutputData) const;` — If the log verbosity is high enough, prints out the files specified in the shot output data.
- L264 _private prototype_ `void StartAudioRecording();` — Tell our submixes to start capturing the data they are generating. Should only be called once output frames are being produced.
- L266 _private prototype_ `void StopAudioRecording();` — Tell our submixes to stop capturing the data, and then store a copy of it.
- L268 _private prototype_ `void ProcessAudioTick();` — Attempt to process the audio thread work. This is complicated by our non-linear time steps
- L269 _private prototype_ `void SetupAudioRendering();`
- L270 _private prototype_ `void TeardownAudioRendering();`
- L278 _private prototype_ `void RenderFrame();` — Renders the next frame in the Pipeline. This updates/ticks all scene view render states and produces data. This may not result in an output frame due to multiple renders accumulating together to produce an output. frame. Should not be called if we're idling (debug), not initialized yet, or finalizing/exporting.
- L281 _private prototype_ `void ModifySequenceViaExtensions(ULevelSequence* InSequence);` — Allow any Settings to modify the (already duplicated) sequence. This allows inserting automatic pre-roll, etc.
- L286 _private prototype_ `void SetProgressWidgetVisible(bool bVisible);` — Should the Progress UI be visible on the player's screen?
- L289 _private prototype_ `TArray<UMoviePipelineRenderPass*> GetAllRenderPasses(const UMoviePipelineExecutorShot* InShot);` — Returns list of render passes for a given shot
- L294 _private prototype_ `void RestoreTargetSequenceToOriginalState();` — Iterates through the changes we've made to a shot and applies the original settings.
- L297 _private prototype_ `void InitializeLevelSequenceActor();` — Initialize a new Level Sequence Actor to evaluate our target sequence. Disables any existing Level Sequences pointed at our original sequence.
- L300 _private prototype_ `void BuildShotListFromSequence();` — This builds the shot list from the target sequence, and expands Playback Bounds to cover any future evaluation we may need.
- L306 _private prototype_ `void SetSoloShot(UMoviePipelineExecutorShot* InShot);` — Modifies the TargetSequence to ensure that only the specified Shot has it's associated Cinematic Shot Section enabled. This way when Handle Frames are enabled and the sections are expanded, we don't end up evaluating the previous shot.
- L309 _private prototype_ `void ExpandShot(UMoviePipelineExecutorShot* InShot, const int32 InNumHandleFrames, const bool bIsPrePass);` — Expands the specified shot (and contained camera cuts)'s ranges for the given settings.
- L312 _private prototype_ `MoviePipeline::FFrameConstantMetrics CalculateShotFrameMetrics(const UMoviePipelineExecutorShot* InShot) const;` — Calculates lots of useful numbers used in timing based off of the current shot. These are constant for a given shot.
- L315 _private prototype_ `void CalculateFrameNumbersForOutputState(const MoviePipeline::FFrameConstantMetrics& InFrameMetrics, const UMoviePipelineExecutorShot* InCameraCut, FMoviePipelineFrameOutputState& InOutOutputState) const;` — It can be useful to know where the data we're generating was relative to the original Timeline, so this calculates that.
- L318 _private prototype_ `void TransitionToState(const EMovieRenderPipelineState InNewState);` — Handles transitioning between states, preventing reentrancy. Normal state flow should be respected, does not handle arbitrary x to y transitions.
- L322 _private member_ `TObjectPtr<UMoviePipelineCustomTimeStep> CustomTimeStep;` — `UPROPERTY(Transient, Instanced)` — Custom TimeStep used to drive the engine while rendering.
- L325 _private member_ `TSharedPtr<FMoviePipelineTimeController> CustomSequenceTimeController;` — Custom Time Controller for the Sequence Player, used to match Custom TimeStep without any floating point accumulation errors.
- L329 _private member_ `TObjectPtr<UEngineCustomTimeStep> CachedPrevCustomTimeStep;` — `UPROPERTY(Transient)` — Hold a reference to the existing custom time step (if any) so we can restore it after we're done using our custom one.
- L333 _private member_ `TObjectPtr<ULevelSequence> TargetSequence;` — `UPROPERTY(Transient)` — This is our duplicated sequence that we're rendering. This will get modified throughout the rendering process.
- L337 _private member_ `TObjectPtr<ALevelSequenceActor> LevelSequenceActor;` — `UPROPERTY(Transient)` — The Level Sequence Actor we spawned to play our TargetSequence.
- L341 _private member_ `TObjectPtr<UMovieRenderDebugWidget> DebugWidget;` — `UPROPERTY(Transient)` — The Debug UI Widget that is spawned and placed on the player UI
- L344 _private member_ `TObjectPtr<UTexture> PreviewTexture;` — `UPROPERTY(Transient)`
- L347 _private member_ `TArray<UMoviePipelineExecutorShot*> ActiveShotList;` — A list of all of the shots we are going to render out from this sequence.
- L350 _private member_ `EMovieRenderPipelineState PipelineState;` — What state of the overall flow are we in? See enum for specifics.
- L353 _private member_ `int32 CurrentShotIndex;` — What is the index of the shot we are working on. -1 if not initialized, may be greater than ShotList.Num() if we've reached the end.
- L356 _private member_ `FDateTime InitializationTime;` — The time (in UTC) that Initialize was called. Used to track elapsed time.
- L358 _private member_ `FMoviePipelineFrameOutputState CachedOutputState;`
- L361 _private member_ `int32 CurrentShotRenderedFrameCount = 0;` — Number of final output frames rendered for the current shot.
- L363 _private member_ `MoviePipeline::FAudioState AudioState;`
- L366 _private member_ `bool bPrevGScreenMessagesEnabled;` — Cached state of GAreScreenMessagesEnabled. We disable them since some messages are written to the FSceneView directly otherwise.
- L372 _private member_ `bool bHasRunBeginFrameOnce;` — Have we hit the callback for the BeginFrame at least once? This solves an issue where the delegates get registered mid-frame so you end up calling EndFrame before BeginFrame which is undesirable.
- L374 _private member_ `bool bPauseAtEndOfFrame;` — Should we pause the game at the end of the frame? Used to implement frame step debugger.
- L377 _private member_ `bool bFlushDiskWritesPerShot;` — Should we flush outstanding work between each shot, ensuring all files are written to disk before we move on?
- L380 _private member_ `FThreadSafeBool bShutdownRequested;` — True if RequestShutdown() was called. At the start of the next frame we will stop producing frames (if needed) and start shutting down.
- L383 _private member_ `FThreadSafeBool bFatalError;` — True if an error or other event occured which halted frame production prematurely.
- L386 _private member_ `bool bIsTransitioningState;` — True if we're in a TransitionToState call. Used to prevent reentrancy.
- L389 _private member_ `float AccumulatedTickSubFrameDeltas;` — When using temporal sub-frame stepping common counts (such as 3) don't result in whole ticks. We keep track of how many ticks we lose so we can add them the next time there's a chance.
- L392 _private member_ `FTimespan InitializationTimeOffset;` — When we originally initialize we store the offset from UTC (which is what GetInitializationTime() is in), but we clear this if you call SetInitializationTime.
- L398 _private member_ `MoviePipeline::FMoviePipelineFrameInfo FrameInfo;` — We have to apply camera motion vectors manually. So we keep the current and previous frame's camera view and rotation. Then we render a sequence of the same movement, and update after running the game sim.
- L403 _public member_ `TSharedPtr<FMoviePipelineOutputMerger, ESPMode::ThreadSafe> OutputBuilder;` — This gathers all of the produced data for an output frame (which may come in async many frames later) before passing them onto the Output Containers.
- L406 _public member_ `IImageWriteQueue* ImageWriteQueue;` — A debug image sequence writer in the event they want to dump every sample generated on its own.
- L409 _public member_ `bool bHasRenderedFirstViewThisFrame;` — Used to track first-render submissions (for 3d renders) to set the correct flags on the renderer module.
- L414 _private member_ `TObjectPtr<UMoviePipelineExecutorJob> CurrentJob;` — `UPROPERTY(Transient)` — Keep track of which job we're working on. This holds our Configuration + which shots we're supposed to render from it.
- L418 _private member_ `FMovieSceneExportMetadata OutputMetadata;` — Keep track of clips we've exported, for building FCPXML and other project files
- L421 _private member_ `TArray<FMoviePipelineShotOutputData> GeneratedShotOutputData;` — Keeps track of files written for each shot so it can be retrieved later via scripting for post-processing.
- L424 _private member_ `TArray<FMoviePipelineOutputFuture> OutputFutures;` — Files that we've requested be written to disk but have not yet finished writing.
- L426 _private member_ `UE::MoviePipeline::FViewportArgs ViewportInitArgs;`
- L428 _private member_ `TSharedPtr<MoviePipeline::FCameraCutSubSectionHierarchyNode> CachedSequenceHierarchyRoot;`
- L432 _private member_ `TMap<TWeakObjectPtr<UObject>, TArray<MoviePipeline::FClothSimSettingsCache>> ClothSimCache;` — Simulation settings cache per cloth interactor object. Needs one per LOD, hence the array.
- L440 _private member_ `TMap<int32, FRenderTimeStatistics> RenderTimeFrameStatistics;`
- L443 _private member_ `TMap<int32, float> CameraOverscanCache;` — Caches the camera overscan used during setup to ensure that overscan-scaled resolution stays constant for every frame during a render
- L446 _private member_ `bool bHasWarnedAboutAnimatedOverscan = false;` — Indicates if the user has already been warned about animate overscan if it is detected so that logs aren't flooded with warning messages
- L449 _public member_ `static FString DefaultDebugWidgetAsset;`

#### struct `UMoviePipeline::FRenderTimeStatistics`  
`struct FRenderTimeStatistics`  
_L434-438_
- L436 _public member_ `FDateTime StartTime;`
- L437 _public member_ `FDateTime EndTime;`

#### class `UMoviePipelineCustomTimeStep`  
`class UMoviePipelineCustomTimeStep : public UEngineCustomTimeStep`  
_L454-478_
- reflection: `UCLASS()`
- inherits: `UEngineCustomTimeStep`
- L460 _public function_ `virtual bool Initialize(UEngine* InEngine) override` — UEngineCustomTimeStep Interface
- L461 _public function_ `virtual void Shutdown(UEngine* InEngine) override`
- L462 _public prototype_ `virtual bool UpdateTimeStep(UEngine* InEngine) override;`
- L463 _public function_ `virtual ECustomTimeStepSynchronizationState GetSynchronizationState() const override`
- L466 _public prototype_ `void SetCachedFrameTiming(const MoviePipeline::FFrameTimeStepCache& InTimeCache);`
- L469 _public prototype_ `void CacheWorldSettings();` — Cache and Restore some of the World Settings settings, as rendering with MRQ in a runtime world needs to restore any changes made to World Settings.
- L470 _public prototype_ `void RestoreCachedWorldSettings();`
- L473 _private member_ `MoviePipeline::FFrameTimeStepCache TimeCache;` — We don't do any thinking on our own, instead we just spit out the numbers stored in our time cache.
- L476 _private member_ `float PrevMinUndilatedFrameTime;` — Not cached in TimeCache as TimeCache is reset every frame.
- L477 _private member_ `float PrevMaxUndilatedFrameTime;`

#### struct `FMoviePipelineTimeController`  
`struct FMoviePipelineTimeController : public FMovieSceneTimeController`  
_L480-488_
- inherits: `FMovieSceneTimeController`
- L482 _public prototype_ `virtual FFrameTime OnRequestCurrentTime(const FQualifiedFrameTime& InCurrentTime, float InPlayRate) override;`
- L483 _public function_ `void SetCachedFrameTiming(const FQualifiedFrameTime& InTimeCache)`
- L487 _private member_ `FQualifiedFrameTime TimeCache;` — Simply store the number calculated and return it when requested.

#### Free symbols / members of external scopes

- L36 _typedef_ `typedef TTuple<TFuture<bool>, MoviePipeline::FMoviePipelineOutputFutureData> FMoviePipelineOutputFuture;`
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMoviePipelineFinishedNative, UMoviePipeline*, bool);`
- L38 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMoviePipelineFinishedNative, UMoviePipeline*, bool);`
- L40 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMoviePipelineFinished, UMoviePipeline*, MoviePipeline, bool, bFatalError);`
- L40 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMoviePipelineFinished, UMoviePipeline*, MoviePipeline, bool, bFatalError);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineAntiAliasingSetting.h` (Public)


#### class `UMoviePipelineAntiAliasingSetting`  
`class UMoviePipelineAntiAliasingSetting : public UMoviePipelineSetting`  
_L13-116_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineSetting`
- L17 _public function_ `UMoviePipelineAntiAliasingSetting() : SpatialSampleCount(1) , TemporalSampleCount(1) , bOverrideAntiAliasing(false) , AntiAliasingMethod(EAntiAliasingMethod::AAM_None) , RenderWarmUpCount(32) , bUseCameraCutForWarmUp(false) , EngineWarmUpCount(0) , bRenderWarmUpFrames(false) , AccumulationGamma(1.f)`
- L31 _public function_ `virtual FText GetDisplayText() const override`
- L35 _protected function_ `virtual bool IsValidOnShots() const override`
- L36 _protected function_ `virtual bool IsValidOnPrimary() const override`
- L37 _protected prototype_ `virtual void ValidateStateImpl() override;`
- L38 _protected prototype_ `virtual void GetFormatArguments(FMoviePipelineFormatArgs& InOutFormatArgs) const override;`
- L39 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L49 _public member_ `int32 SpatialSampleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 1, ClampMin = 1), Category = "Render Settings")` — How many frames should we accumulate together before contributing to one overall sample. This lets you increase the anti-aliasing quality of an sample, or have high quality anti-aliasing if you don't want any motion blur due to accumulation over time in SampleCount.
- L59 _public member_ `int32 TemporalSampleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 1, ClampMin = 1), Category = "Render Settings")` — The number of frames we should combine together to produce each output frame. This blends the results of this many sub-steps together to produce one output frame. See CameraShutterAngle to control how much time passes between each sub-frame. See SpatialSampleCount to see how many samples we average together to produce a sub-step. (This means rendering complexity is SampleCount * TileCount^2 * SpatialSampleCount * NumPasses).
- L66 _public member_ `bool bOverrideAntiAliasing;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render Settings")` — Should we override the Project's anti-aliasing setting during a movie render? This can be useful to have TAA on during normal work in the editor but force it off for high quality renders /w many spatial samples.
- L72 _public member_ `TEnumAsByte<EAntiAliasingMethod> AntiAliasingMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition="bOverrideAntiAliasing"), Category = "Render Settings")` — If we are overriding the AA method, what do we use? None will turn off anti-aliasing.
- L82 _public member_ `int32 RenderWarmUpCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0, ClampMin = 0), AdvancedDisplay, Category = "Render Settings")` — The number of frames at the start of each shot that the engine will render and then discard. This is useful for ensuring there is history for temporal effects (such as anti-aliasing). It can be set to a lower number if not using temporal effects. This is more expensive than EngineWarmUpCount (which should be used for particle warm-ups, etc.)
- L91 _public member_ `bool bUseCameraCutForWarmUp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render Settings")` — Should we use the excess in the camera cut track to determine engine warmup? When disabled, the sequence is evaluated once at the first frame and then waits there for EngineWarmUpCount many frames. When this is enabled, the number of warmup frames is based on how much excess there is in the camera cut track outside of the playback range AND the sequence is evaluated for each frame which can allow time for skeletal meshes to animate from a bind pose, etc.
- L101 _public member_ `int32 EngineWarmUpCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0, ClampMin = 0, EditCondition = "!bUseCameraCutForWarmUp"), AdvancedDisplay, Category = "Render Settings")` — The number of frames at the start of each shot that the engine will run without rendering. This allows pre-warming systems (such as particle systems, or level loading) which need time to run before you want to start capturing frames. This ticks the game thread but does not submit anything to the GPU to be rendered. This is more cheaper than RenderWarmUpCount and is the preferred way to have time pass at the start of a shot.
- L109 _public member_ `bool bRenderWarmUpFrames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render Settings")` — Should we submit the warm-up frames to the GPU? Generally you want this disabled (as it is more performant), but some systems (such as gpu particles) need to be rendered to actually perform their warm-up. Enabling this will cause any warm up frames to also be submitted to the GPU which resolves this issue.
- L115 _public member_ `float AccumulationGamma;` — For advanced users, the gamma space to apply accumulation in. During accumulation, pow(x,AccumulationGamma) is applied and pow(x,1/AccumulationGamma) is applied after accumulation is finished

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineBase.h` (Public)


#### class `UMoviePipelineBase`  
`class UMoviePipelineBase : public UObject`  
_L12-120_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UObject`
- L28 _public function_ `void RequestShutdown(bool bIsError = false)` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Request the movie pipeline to shut down at the next available time. The pipeline will attempt to abandon the current frame (such as if there are more temporal samples pending) but may be forced into finishing if there are spatial samples already submitted to the GPU. The shutdown flow will be run to ensure already completed work is written to disk. This is a non-blocking operation, use Shutdown() instead if you need to block until it is fully shut down. @param bIsError - Whether this is a request for early shut down due to an error This function is thread safe.
- L43 _public function_ `void Shutdown(bool bIsError = false)` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Abandons any future work on this Movie Pipeline and runs through the shutdown flow to ensure already completed work is written to disk. This is a blocking-operation and will not return until all outstanding work has been completed. @param bIsError - Whether this is an early shut down due to an error This function should only be called from the game thread.
- L52 _public function_ `bool IsShutdownRequested() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Has RequestShutdown() been called?
- L58 _public function_ `EMovieRenderPipelineState GetPipelineState() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L71 _public function_ `FMoviePipelineWorkFinishedNative& OnMoviePipelineWorkFinished()` — Called when we have completely finished this pipeline. This means that all frames have been rendered, all files written to disk, and any post-finalize exports have finished. This Pipeline will call Shutdown() on itself before calling this delegate to ensure we've unregistered from all delegates and are no longer trying to do anything (even if we still exist). The params struct in the return will have metadata about files written to disk for each shot.
- L79 _public function_ `FMoviePipelineWorkFinishedNative& OnMoviePipelineShotWorkFinished()` — Only called if `IsFlushDiskWritesPerShot()` is set! Called after each shot is finished and files have been flushed to disk. The returned data in the params struct will have only the per-shot metadata for the just finished shot. Use OnMoviePipelineFinished() if you need all of the metadata.
- L90 _public member_ `FMoviePipelineWorkFinished OnMoviePipelineWorkFinishedDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Movie Render Pipeline")` — Called when we have completely finished this pipeline. This means that all frames have been rendered, all files written to disk, and any post-finalize exports have finished. This Pipeline will call Shutdown() on itself before calling this delegate to ensure we've unregistered from all delegates and are no longer trying to do anything (even if we still exist). The params struct in the return will have metadata about files written to disk for each shot.
- L104 _public member_ `FMoviePipelineWorkFinished OnMoviePipelineShotWorkFinishedDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Movie Render Pipeline")` — This callback will not be called by default due to performance reasons. You need to opt into this (via scripting in MoviePipeline or in the node in Movie Graph) by setting FlushDiskWritesPerShot to true in the output setting for this job's configuration. Called after each shot is finished and files have been flushed to disk. The returned data in the params struct will have only the per-shot metadata for the just finished shot. Use OnMoviePipelineWorkFinishedDelegate if you need all of the metadata.
- L107 _protected function_ `virtual void RequestShutdownImpl(bool bIsError)`
- L108 _protected function_ `virtual void ShutdownImpl(bool bIsError)`
- L109 _protected function_ `virtual bool IsShutdownRequestedImpl() const`
- L110 _protected function_ `virtual EMovieRenderPipelineState GetPipelineStateImpl() const`
- L111 _protected function_ `virtual FMoviePipelineWorkFinishedNative& OnMoviePipelineWorkFinishedImpl()`
- L112 _protected function_ `virtual FMoviePipelineWorkFinishedNative& OnMoviePipelineShotWorkFinishedImpl()`
- L113 _protected function_ `virtual bool IsPostShotCallbackNeeded() const`
- L116 _protected member_ `FMoviePipelineWorkFinishedNative OnMoviePipelineWorkFinishedDelegateNative;` — Called when we have completely finished. This object will call Shutdown before this and stop ticking.
- L119 _protected member_ `FMoviePipelineWorkFinishedNative OnMoviePipelineShotWorkFinishedDelegateNative;` — Called when each shot has finished work if IsFlushDiskWritesPerShot() is set.

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMoviePipelineWorkFinishedNative, FMoviePipelineOutputData);`
- L8 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMoviePipelineWorkFinishedNative, FMoviePipelineOutputData);`
- L9 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoviePipelineWorkFinished, FMoviePipelineOutputData, Results);`
- L9 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoviePipelineWorkFinished, FMoviePipelineOutputData, Results);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineBasicConfig.h` (Public)


#### enum `EMoviePipelineBasicDenoiserType`  
`enum class EMoviePipelineBasicDenoiserType : uint8`  
_L19-23_
- reflection: `UENUM(BlueprintType)`
- desc: Denoiser type for the Path Traced Renderer in Basic configuration mode.
- L21 _public enumerator_ `Spatial = 0`
- L22 _public enumerator_ `Temporal = 1`

#### class `UMoviePipelineBasicConfig`  
`class UMoviePipelineBasicConfig : public UObject`  
_L32-189_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A simplified configuration for Movie Render Queue jobs. Provides a pared-down set of rendering options that generates a UMovieGraphConfig just-in-time before rendering. This allows most users to configure renders without touching Presets or Graphs, while still using the full graph pipeline under the hood.
- L37 _public prototype_ `UMoviePipelineBasicConfig();`
- L43 _public prototype_ `void MergeOverrides(const UMoviePipelineBasicConfig* InShotOverrides, UMoviePipelineBasicConfig& OutMerged) const;` — Merge a shot's basic config with this config, providing the result in "OutMerged". For each bOverride_* that is true within InShotOverrides, use the shot's value; otherwise, use the value from this config.
- L49 _public prototype_ `static UMovieGraphConfig* GenerateGraph(UMoviePipelineBasicConfig* InConfig, UObject* InOuter);` — Generate a UMovieGraphConfig from this config (or a merged config). Note that EnforceInvariants() will be called on InConfig to ensure the generated graph is valid.
- L54 _public prototype_ `bool HasAnyOverrides() const;` — Returns true if at least one bOverride_* flag is set on this config.
- L61 _public prototype_ `void EnforceInvariants();` — Enforce minimum-valid-state invariants: - At least one renderer (Deferred or Path Traced) must be enabled; if neither is, Deferred is re-enabled. - EnabledOutputTypes must be non-empty; if it is, PNG is restored as the default.
- L64 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L67 _public prototype_ `static void SaveAsDefault(const UMoviePipelineBasicConfig* InConfig);` — Save InConfig as the user's default Basic config (persisted to a local uasset in the project).
- L71 _public prototype_ `static const UMoviePipelineBasicConfig* GetSavedDefault();` — Return the user's saved default Basic config, or nullptr if none exists.
- L77 _public member_ `uint8 bOverride_OutputDirectory : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L80 _public member_ `uint8 bOverride_FileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L83 _public member_ `uint8 bOverride_OutputResolution : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L86 _public member_ `uint8 bOverride_EnabledOutputTypes : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L90 _public member_ `uint8 bOverride_CustomStartFrame : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))` — Whether to override the sequence's playback range start. Playback range overrides are only job-level settings.
- L94 _public member_ `uint8 bOverride_CustomEndFrame : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))` — Whether to override the sequence's playback range end. Playback range overrides are only job-level settings.
- L97 _public member_ `uint8 bOverride_bUseDeferredRenderer : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L100 _public member_ `uint8 bOverride_DeferredSpatialSampleCount : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L104 _public member_ `uint8 bOverride_DeferredAntiAliasingMethod : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))` — Whether to override the project's anti-aliasing method. For shots, this overrides the job's anti-aliasing method.
- L107 _public member_ `uint8 bOverride_bUsePathTracedRenderer : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L110 _public member_ `uint8 bOverride_PathTracedSpatialSampleCount : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L114 _public member_ `uint8 bOverride_PathTracedDenoiserType : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))` — Whether to enable the path traced denoiser. For shots, this overrides the job's denoiser setting.
- L117 _public member_ `uint8 bOverride_NumWarmUpFrames : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L120 _public member_ `uint8 bOverride_TemporalSampleCount : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L123 _public member_ `uint8 bOverride_BurnInClass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L129 _public member_ `FDirectoryPath OutputDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")` — The directory all the output files are relative to.
- L133 _public member_ `FString FileNameFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")` — The format string for file names. Can include folder prefixes, and format string tokens ({shot_name}, etc.)
- L137 _public member_ `FMovieGraphNamedResolution OutputResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")` — The resolution that output files are exported at.
- L141 _public member_ `TArray<TSoftClassPtr<UMovieGraphFileOutputNode>> EnabledOutputTypes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")` — The output types that rendered media should be saved to.
- L145 _public member_ `int32 CustomStartFrame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (EditCondition = "bOverride_CustomStartFrame"))` — A custom start frame, overriding the sequence's playback range start.
- L149 _public member_ `int32 CustomEndFrame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (EditCondition = "bOverride_CustomEndFrame"))` — A custom end frame, overriding the sequence's playback range end.
- L153 _public member_ `bool bUseDeferredRenderer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Whether the deferred renderer should be enabled.
- L157 _public member_ `int32 DeferredSpatialSampleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (DisplayName = "Spatial Sample Count", EditCondition = "bUseDeferredRenderer", UIMin = 1, ClampMin = 1))` — Spatial sample count for the Deferred Renderer.
- L161 _public member_ `TEnumAsByte<EAntiAliasingMethod> DeferredAntiAliasingMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (DisplayName = "Anti Aliasing Method", EditCondition = "bOverride_DeferredAntiAliasingMethod"))` — Anti-aliasing method for the Deferred Renderer.
- L165 _public member_ `bool bUsePathTracedRenderer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Whether the path tracer should be enabled.
- L169 _public member_ `int32 PathTracedSpatialSampleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (DisplayName = "Spatial Sample Count", EditCondition = "bUsePathTracedRenderer", UIMin = 1, ClampMin = 1))` — Spatial sample count for the Path Traced Renderer.
- L173 _public member_ `EMoviePipelineBasicDenoiserType PathTracedDenoiserType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (DisplayName = "Denoiser", EditCondition = "bOverride_PathTracedDenoiserType"))` — If denoising is enabled, this specifies the specific denoiser that path tracer results should be passed to.
- L177 _public member_ `int32 NumWarmUpFrames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (DisplayName = "Num Warm Up Frames", UIMin = 0, ClampMin = 0))` — The number of frames to run (without producing output) at the start of each shot to warm up systems like Niagara, Chaos, etc.
- L181 _public member_ `int32 TemporalSampleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (DisplayName = "Temporal Sample Count", UIMin = 1, ClampMin = 1))` — The number of temporal sub-samples per output frame. Higher values will reduce temporal aliasing.
- L188 _public member_ `FSoftClassPath BurnInClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (EditCondition = "bOverride_BurnInClass", MetaClass = "/Script/MovieRenderPipelineCore.MovieGraphBurnInWidget"))` — The burn-in widget class to use on all output types that support burn-in. Only applies if the burn-in override is enabled. Burn-ins are enabled for all output types that support them, and compositing is enabled for all output types that support burn-in compositing.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineBlueprintLibrary.h` (Public)


#### class `UMoviePipelineBlueprintLibrary`  
`class UMoviePipelineBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L19-204_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "MoviePipelineLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L41 _public prototype_ `static UMovieSceneSequence* DuplicateSequence(UObject* Outer, UMovieSceneSequence* InSequence);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Duplicates the specified sequence using a medium depth copy. Standard duplication will only duplicate the top level Sequence (since shots and sub-sequences are other standalone assets) so this function recursively duplicates the given sequence, shot and subsequence and then fixes up the references to point to newly duplicated sequences. Use at your own risk. Some features may not work when duplicated (complex object binding arrangements, blueprint GetSequenceBinding nodes, etc.) but can be useful when wanting to create a bunch of variations with minor differences (such as swapping out an actor, track, etc.) This does not duplicate any assets that the sequence points to outside of Shots/Subsequences. @param	Outer		- The Outer of the newly duplicated object. Leave null for TransientPackage(); @param	InSequence	- The sequence to recursively duplicate. @return				- The duplicated sequence, or null if no sequence was provided to duplicate.
- L53 _public prototype_ `static void ResolveFilenameFormatArguments(const FString& InFormatString, const FMoviePipelineFilenameResolveParams& InParams, FString& OutFinalPath, FMoviePipelineFormatArgs& OutMergedFormatArgs);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Resolves the provided InFormatString by converting {format_strings} into settings provided by the primary config. @param	InFormatString		A format string (in the form of "{format_key1}_{format_key2}") to resolve. @param	InParams			The parameters to resolve the format string with. See FMoviePipelineFilenameResolveParams properties for details. Expected that you fill out all of the parameters so that they can be used to resolve strings, otherwise default values may be used. @param	OutFinalPath		The final filepath based on a combination of the format string and the Resolve Params. @return	OutMergedFormatArgs	A merged set of Key/Value pairs for both Filename Arguments and Metadata that merges all the sources.
- L66 _public prototype_ `static bool GetEstimatedTimeRemaining(const UMoviePipeline* InPipeline, FTimespan& OutEstimate);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Get the estimated amount of time remaining for the current pipeline. Based on looking at the total amount of samples to render vs. how many have been completed so far. Inaccurate when Time Dilation is used, and gets more accurate over the course of the render. @param	InPipeline	The pipeline to get the time estimate from. @param	OutEstimate	The resulting estimate, or FTimespan() if estimate is not valid. @return				True if a valid estimate can be calculated, or false if it is not ready yet (ie: not enough samples rendered)
- L69 _public prototype_ `static FDateTime GetJobInitializationTime(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L78 _public prototype_ `static EMovieRenderPipelineState GetPipelineState(const UMoviePipeline* InPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Get the current state of the specified Pipeline. See EMovieRenderPipelineState for more detail about each state. @param	InPipeline	The pipeline to get the state for. @return				Current State.
- L81 _public prototype_ `static EMovieRenderShotState GetCurrentSegmentState(UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L84 _public prototype_ `static FText GetJobName(UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L87 _public prototype_ `static FText GetJobAuthor(UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L91 _public prototype_ `static void GetOverallOutputFrames(const UMoviePipeline* InMoviePipeline, int32& OutCurrentIndex, int32& OutTotalCount);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L94 _public prototype_ `static void GetCurrentSegmentName(UMoviePipeline* InMoviePipeline, FText& OutOuterName, FText& OutInnerName);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L97 _public prototype_ `static void GetOverallSegmentCounts(const UMoviePipeline* InMoviePipeline, int32& OutCurrentIndex, int32& OutTotalCount);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L100 _public prototype_ `static FMoviePipelineSegmentWorkMetrics GetCurrentSegmentWorkMetrics(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L104 _public prototype_ `static float GetCompletionPercentage(const UMoviePipeline* InPipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Gets the completion percent of the Pipeline in 0-1
- L107 _public prototype_ `static FTimecode GetRootTimecode(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L110 _public prototype_ `static FFrameNumber GetRootFrameNumber(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L113 _public prototype_ `static FTimecode GetCurrentShotTimecode(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L116 _public prototype_ `static FFrameNumber GetCurrentShotFrameNumber(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L119 _public prototype_ `static float GetCurrentFocusDistance(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L122 _public prototype_ `static float GetCurrentFocalLength(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L125 _public prototype_ `static float GetCurrentAperture(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L129 _public prototype_ `static FString GetMapPackageName(UMoviePipelineExecutorJob* InJob);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Get the package name for the map in this job. The level travel command requires the package path and not the asset path.
- L133 _public prototype_ `static class UMoviePipelineQueue* LoadManifestFileFromString(const FString& InManifestFilePath);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Loads the specified manifest file and converts it into an UMoviePipelineQueue. Use in combination with SaveQueueToManifestFile.
- L137 _public prototype_ `static void UpdateJobShotListFromSequence(ULevelSequence* InSequence, UMoviePipelineExecutorJob* InJob, bool& bShotsChanged);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Scan the provided sequence in the job to see which camera cut sections we would try to render and update the job's shotlist.
- L141 _public prototype_ `static int32 ResolveVersionNumber(FMoviePipelineFilenameResolveParams InParams, bool bGetNextVersion = true);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — If version number is manually specified by the Job, returns that. Otherwise search the Output Directory for the highest version already existing (and increment it by one if bGetNextVersion is true).
- L150 _public prototype_ `static int32 GetCurrentVersionNumber(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Retrieves the cached version number calculated for the current shot, which depends on where the version token was used in the File Name Output ie: If {version} comes before {shot_name} then all shots will use the same version number, but if it comes afterwards then each shot may have a different version (which is the highest number found of that particular shot). This function should retrieve what is used in the filename writing step either way.
- L155 _public prototype_ `static FIntPoint GetEffectiveOutputResolution(UMoviePipelinePrimaryConfig* InPrimaryConfig, UMoviePipelineExecutorShot* InPipelineExecutorShot, float DefaultOverscan = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline", meta=(DeprecatedFunction, DeprecationMessage = "Use GetOverscannedResolution instead"))` — `UE_DEPRECATED(5.6, "GetEffectiveOutputResolution is deprecated, use GetOverscannedResolution to get the overscanned resolution instead")` — In case of Overscan percentage being higher than 0 we render additional pixels. This function returns the resolution with overscan taken into account.
- L163 _public prototype_ `static FIntPoint GetDesiredOutputResolution(const UMoviePipelinePrimaryConfig* InPrimaryConfig);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Gets the desired output resolution for the movie render queue as specified by the user. Does not include overscan, tiling, or aspect ratio constraints, and is the target resolution that the pipeline will generally output (e.g. when cropping overscan in non-EXR formats). Use GetOverscannedResolution or GetBackbufferResolution to get resolutions that factor in overscan and tiling, respectively
- L167 _public prototype_ `static FIntPoint GetOverscannedResolution(const UMoviePipelinePrimaryConfig* InPrimaryConfig, const UMoviePipelineExecutorShot* InPipelineExecutorShot, float InDefaultOverscan = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Gets the overscanned resolution, which is the target output resolution scaled by any configured overscan amount
- L171 _public prototype_ `static FIntPoint GetBackbufferResolution(const UMoviePipelinePrimaryConfig* InPrimaryConfig, const UMoviePipelineExecutorShot* InPipelineExecutorShot, float InDefaultOverscan = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Gets the resolution that will be used by the engine when rendering a frame. Includes overscan and tiling
- L181 _public prototype_ `static FIntRect GetOverscanCropRectangle(const UMoviePipelinePrimaryConfig* InPrimaryConfig, const UMoviePipelineExecutorShot* InPipelineExecutorShot, float DefaultOverscan = 0.0f);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Gets a rectangle that will crop out any overscan applied to the scene. If there is no overscan, the rectangle returned will match the backbuffer rectangle @param InPrimaryConfig			- The pipeline configuration that will provide context for resolving the resolution @param InPipelineExecutorShot	- The shot that is being generated by the pipeline @param DefaultOverscan			- The default overscan to use if there are no camera settings that provide an overscan override value, from 0.0 to 1.0 @return							- The crop rectangle, which will have a resolution matching the requested output resolution
- L185 _public prototype_ `static UMoviePipelineSetting* FindOrGetDefaultSettingForShot(TSubclassOf<UMoviePipelineSetting> InSettingType, const UMoviePipelinePrimaryConfig* InPrimaryConfig, const UMoviePipelineExecutorShot* InShot);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline", meta = (DeterminesOutputType = "InSettingType"))` — Allows access to a setting of provided type for specific shot.
- L188 _public prototype_ `static ULevelSequence* GetCurrentSequence(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L191 _public prototype_ `static UMoviePipelineExecutorShot* GetCurrentExecutorShot(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L195 _public prototype_ `static FText GetMoviePipelineEngineChangelistLabel(const UMoviePipeline* InMoviePipeline);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Get a string to represent the Changelist Number for the burn in. This can be driven by a Modular Feature if you want to permanently replace it with different information.
- L203 _private prototype_ `static UCineCameraComponent* Utility_GetCurrentCineCamera(const UWorld* InWorld);` — Get the current cine camera in use, or nullptr if there is none.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineCameraSetting.h` (Public)


#### class `UMoviePipelineCameraSetting`  
`class UMoviePipelineCameraSetting : public UMoviePipelineSetting`  
_L12-87_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineSetting`
- L16 _public function_ `UMoviePipelineCameraSetting() : ShutterTiming(EMoviePipelineShutterTiming::FrameCenter)`
- L22 _public function_ `virtual FText GetDisplayText() const override`
- L25 _protected function_ `virtual bool IsValidOnShots() const override`
- L26 _protected function_ `virtual bool IsValidOnPrimary() const override`
- L28 _protected prototype_ `virtual void GetFormatArguments(FMoviePipelineFormatArgs& InOutFormatArgs) const override;`
- L29 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L57 _public member_ `EMoviePipelineShutterTiming ShutterTiming;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")` — Shutter Timing allows you to bias the timing of your shutter angle to either be before, during, or after a frame. When set to FrameClose, it means that the motion gathered up to produce frame N comes from before and right up to frame N. When set to FrameCenter, the motion represents half the time before the frame and half the time after the frame. When set to FrameOpen, the motion represents the time from Frame N onwards. As an example, here are 4 temporal subsamples with 180 degree shutter angle (50% motion blur) between frames A & B: FrameClose F-------F-------F ----1234--------- ----AAAA--------- FrameCenter F-------F-------F ------1234------- ------AABB------- FrameOpen F-------F-------F --------1234----- --------BBBB-----
- L64 _public member_ `bool bOverrideCameraOverscan;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings", meta = (InlineEditConditionToggle))` — If true, the camera settings overscan value will override any overscan on the cameras when rendering; otherwise, the overscan value on the cameras will be used.
- L78 _public member_ `float OverscanPercentage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Overscan Percentage Override", UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "bOverrideCameraOverscan"), Category = "Camera Settings")` — Overscan percent enables rendering additional pixels beyond the current target resolution, and can be used in conjunction with the EXR output format to add post-processing effects such as lens distortion. Please note that using this feature may cause the render to appear different in some scenarios (for example, auto-exposure may be impacted due to the increased FoV picking up additional lighting). With EXR outputs, the non-overscanned pixel data is contained in the EXR "display window", and the overscanned pixel data is contained in the "data window". For example, a 1920x1080 render with 0.1 overscan will result in a 2112x1188 render; the display window will be 1920x1080, and the data window will be 2112x1188. For all other formats, the pixels are cropped to the original target resolution (ie, no extra pixel data is included).
- L86 _public member_ `bool bRenderAllCameras;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")` — If true, when a Camera Cut section is found we will also render any other cameras within the same sequence (not parent, nor child sequences though). These cameras are rendered at the same time as the primary camera meaning all cameras capture the same world state. Do note that this multiplies render times and memory requirements!

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineColorSetting.h` (Public)


#### class `UMoviePipelineColorSetting`  
`class UMoviePipelineColorSetting : public UMoviePipelineSetting`  
_L14-37_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineSetting`
- L18 _public prototype_ `UMoviePipelineColorSetting();`
- L21 _public function_ `virtual FText GetDisplayText() const override`
- L22 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L24 _public function_ `virtual bool IsValidOnShots() const override`
- L25 _public function_ `virtual bool IsValidOnPrimary() const override`
- L32 _public member_ `FOpenColorIODisplayConfiguration OCIOConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Misc")` — OCIO config to be passed to OCIO View Extension. If this is enabled the Tone Curve will be disabled.
- L36 _public member_ `bool bDisableToneCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Misc")` — If true the Filmic Tone Curve will not be applied. Disabling this will allow you to export linear data for EXRs. Force Disabled if Open Color IO is enabled.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineCommandLineEncoder.h` (Public)


#### enum `EMoviePipelineEncodeQuality`  
`enum class EMoviePipelineEncodeQuality : uint8`  
_L12-18_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `Low = 0`
- L15 _public enumerator_ `Medium = 1`
- L16 _public enumerator_ `High = 2`
- L17 _public enumerator_ `Epic = 3`

#### class `UMoviePipelineCommandLineEncoder`  
`class UMoviePipelineCommandLineEncoder : public UMoviePipelineSetting`  
_L21-100_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineSetting`
- L32 _public prototype_ `UMoviePipelineCommandLineEncoder();`
- L33 _public prototype_ `void StartEncodingProcess(TArray<FMoviePipelineShotOutputData>& InOutData, const bool bInIsShotEncode);`
- L36 _public function_ `virtual FText GetDisplayText() const override`
- L37 _public function_ `virtual FText GetCategoryText() const override`
- L38 _public function_ `virtual bool CanBeDisabled() const override`
- L40 _public prototype_ `virtual void SetupForPipelineImpl(UMoviePipeline* InPipeline);`
- L41 _public prototype_ `virtual void ValidateStateImpl() override;`
- L42 _public function_ `virtual bool IsValidOnShots() const override`
- L43 _public function_ `virtual bool IsValidOnPrimary() const override`
- L44 _public prototype_ `virtual bool HasFinishedExportingImpl() override;`
- L45 _public prototype_ `virtual void BeginExportImpl() override;`
- L46 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L49 _protected prototype_ `bool NeedsPerShotFlushing() const;`
- L50 _protected prototype_ `void LaunchEncoder(const FEncoderParams& InParams);`
- L51 _protected prototype_ `void OnTick();`
- L52 _protected prototype_ `FString GetQualitySettingString() const;`
- L62 _public member_ `FString FileNameFormatOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command Line Encoder")` — File name format string override. If specified it will override the FileNameFormat from the Output setting. If {shot_name} or {camera_name} is used, encoding will begin after each shot finishes rendering. Can be different from the main one in the Output setting so you can render out frames to individual shot folders but encode to one file.
- L66 _public member_ `EMoviePipelineEncodeQuality Quality;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command Line Encoder")` — What encoding quality to use for this job? Exact command line arguments for each one are specified in Project Settings.
- L70 _public member_ `FString AdditionalCommandLineArgs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command Line Encoder")` — Any additional arguments to pass to the CLI encode for this particular job.
- L74 _public member_ `bool bDeleteSourceFiles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command Line Encoder")` — Should we delete the source files from disk after encoding?
- L78 _public member_ `bool bSkipEncodeOnRenderCanceled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command Line Encoder")` — If a render was canceled (via hitting escape mid render) should we skip trying to encode the files we did produce?
- L82 _public member_ `bool bWriteEachFrameDuration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command Line Encoder")` — Write the duration for each frame into the generated text file. Needed for some input types on some CLI encoding software.
- L99 _private member_ `TArray<FActiveJob> ActiveEncodeJobs;`

#### struct `UMoviePipelineCommandLineEncoder::FEncoderParams`  
`struct FEncoderParams`  
_L23-28_
- L25 _public member_ `FStringFormatNamedArguments NamedArguments;`
- L26 _public member_ `TMap<FString, TArray<FString>> FilesByExtensionType;`
- L27 _public member_ `TWeakObjectPtr<class UMoviePipelineExecutorShot> Shot;`

#### struct `UMoviePipelineCommandLineEncoder::FActiveJob`  
`struct FActiveJob`  
_L85-97_
- L87 _public function_ `FActiveJob() : ReadPipe(nullptr) , WritePipe(nullptr)`
- L92 _public member_ `FProcHandle ProcessHandle;`
- L93 _public member_ `void* ReadPipe;`
- L94 _public member_ `void* WritePipe;`
- L96 _public member_ `TArray<FString> FilesToDelete;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineCommandLineEncoderSettings.h` (Public)


#### class `UMoviePipelineCommandLineEncoderSettings`  
`class UMoviePipelineCommandLineEncoderSettings : public UDeveloperSettings`  
_L8-78_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = Engine, defaultconfig, meta=(DisplayName = "Movie Pipeline CLI Encoder"))`
- inherits: `UDeveloperSettings`
- L13 _public function_ `UMoviePipelineCommandLineEncoderSettings() : Super()`
- L27 _public function_ `virtual FName GetContainerName() const override` — Gets the settings container name for the settings, either Project or Editor
- L29 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L34 _public member_ `FString ExecutablePath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Command Line Encoder")` — Path to the executable (including extension). Can just be "ffmpeg.exe" if it can be located via PATH directories.
- L37 _public member_ `FText CodecHelpText;` — `UPROPERTY(EditAnywhere, Category = "Command Line Encoder")`
- L41 _public member_ `FString VideoCodec;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Command Line Encoder")` — Which video codec should we use? Run 'MovieRenderPipeline.DumpCLIEncoderCodecs' for options.
- L45 _public member_ `FString AudioCodec;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Command Line Encoder")` — Which audio codec should we use? Run 'MovieRenderPipeline.DumpCLIEncoderCodecs' for options.
- L49 _public member_ `FString OutputFileExtension;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Command Line Encoder")` — Extension for the output files. Many encoders use this to determine the container type they are placed in. Should be without dot, ie: "webm".
- L53 _public member_ `FString CommandLineFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Command Line Arguments")` — The format string used when building the final command line argument to launch.
- L57 _public member_ `FString VideoInputStringFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Command Line Arguments")` — Format string used for each video input.
- L61 _public member_ `FString AudioInputStringFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Command Line Arguments")` — Format string used for each audio input.
- L65 _public member_ `FString EncodeSettings_Low;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Command Line Arguments")` — The flags used for low quality encoding.
- L69 _public member_ `FString EncodeSettings_Med;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Command Line Arguments")` — The flags used for medium quality encoding.
- L73 _public member_ `FString EncodeSettings_High;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Command Line Arguments")` — The flags used for high quality encoding.
- L77 _public member_ `FString EncodeSettings_Epic;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Command Line Arguments")` — The flags used for epic quality encoding.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineConfigBase.h` (Public)


#### class `UMoviePipelineConfigBase`  
`class UMoviePipelineConfigBase : public UObject`  
_L13-193_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UObject`
- L18 _public function_ `UMoviePipelineConfigBase()`
- L24 _public function_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override`
- L30 _public function_ `virtual void PostDuplicate(bool bDuplicateForPIE) override`
- L39 _public prototype_ `virtual void RemoveSetting(UMoviePipelineSetting* InSetting);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Removes the specific instance from our Setting list.
- L43 _public prototype_ `virtual void CopyFrom(UMoviePipelineConfigBase* InConfig);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Copy this configuration from another existing configuration.
- L45 _public function_ `int32 GetSettingsSerialNumber() const`
- L49 _public function_ `virtual TArray<UMoviePipelineSetting*> GetUserSettings() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Returns an array of all settings in this config that the user has added via the UI or via Scripting.
- L56 _public function_ `UMoviePipelineConfigBase* GetConfigOrigin() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Gets the config that this config was originally based on (if any). The origin will only be set on transient configs; the origin will be nullptr for non-transient configs because the origin will be this object.
- L62 _public function_ `void SetConfigOrigin(UMoviePipelineConfigBase* InConfig)` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Sets the config that this config originated from (if any). The origin should only be set for transient configs.
- L66 _public function_ `template<typename SettingType> TArray<SettingType*> FindSettings(const bool bIncludeDisabledSettings = false) const`
- L83 _public function_ `template<typename SettingType> SettingType* FindSetting(const bool bIncludeDisabledSettings = false) const`
- L96 _public function_ `TArray<UMoviePipelineSetting*> FindSettingsByClass(TSubclassOf<UMoviePipelineSetting> InClass, const bool bIncludeDisabledSettings = false, const bool bExactMatch = false) const` — `UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = "InClass"), Category = "Movie Render Pipeline")` — Find all settings of a particular type for this config. @param InClass - Class that you wish to find the setting object for. @param bIncludeDisabledSettings - if true, disabled settings will be included in the search @param bExactMatch - if true, only exact matches of the specified class will be found, otherwise subclasses of the specified class will also be found @return An array of instances of this class if it already exists as a setting on this config
- L125 _public function_ `UMoviePipelineSetting* FindSettingByClass(TSubclassOf<UMoviePipelineSetting> InClass, const bool bIncludeDisabledSettings = false, const bool bExactMatch = false) const` — `UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = "InClass"), Category = "Movie Render Pipeline")` — Find a setting of a particular type for this config. @param InClass - Class that you wish to find the setting object for. @param bIncludeDisabledSettings - if true, disabled settings will be included in the search @param bExactMatch - if true, only exact matches of the specified class will be found, otherwise subclasses of the specified class will also be found @return An instance of this class if it already exists as a setting on this config, otherwise null.
- L145 _public function_ `UMoviePipelineSetting* FindOrAddSettingByClass(TSubclassOf<UMoviePipelineSetting> InClass, const bool bIncludeDisabledSettings = false, const bool bExactMatch = false)` — `UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InClass"), Category = "Movie Render Pipeline")` — Finds a setting of a particular type for this pipeline config, adding it if it doesn't already exist. @param InClass - Class you wish to find or create the setting object for. @param bIncludeDisabledSettings - if true, disabled settings will be included in the search @param bExactMatch - if true, only exact matches of the specified class will be found, otherwise subclasses of the specified class will also be found @return An instance of this class as a setting on this config.
- L173 _public prototype_ `virtual bool CanSettingBeAdded(const UMoviePipelineSetting* InSetting) const PURE_VIRTUAL( UMoviePipelineConfigBase::CanSettingBeAdded, return false; );`
- L176 _protected function_ `virtual void OnSettingAdded(UMoviePipelineSetting* InSetting)`
- L177 _protected function_ `virtual void OnSettingRemoved(UMoviePipelineSetting* InSetting)`
- L180 _public member_ `FString DisplayName;` — `UPROPERTY()`
- L185 _protected member_ `TArray<TObjectPtr<UMoviePipelineSetting>> Settings;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Movie Pipeline")` — Array of settings classes that affect various parts of the output pipeline.
- L190 _private member_ `TSoftObjectPtr<UMoviePipelineConfigBase> ConfigOrigin;` — `UPROPERTY()` — The config that this config originated from. Helpful for transient configs.
- L192 _private member_ `int32 SettingsSerialNumber;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineDebugSettings.h` (Public)


#### class `UMoviePipelineDebugSettings`  
`class UMoviePipelineDebugSettings : public UMoviePipelineSetting`  
_L12-51_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineSetting`
- L16 _public prototype_ `UMoviePipelineDebugSettings();`
- L19 _public function_ `virtual FText GetDisplayText() const override`
- L20 _public prototype_ `virtual FText GetFooterText(UMoviePipelineExecutorJob* InJob) const override;`
- L21 _public function_ `virtual bool CanBeDisabled() const override`
- L22 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L24 _public function_ `virtual bool IsValidOnShots() const override`
- L25 _public function_ `virtual bool IsValidOnPrimary() const override`
- L32 _public member_ `bool bWriteAllSamples;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render Settings")` — If true, we will write all samples that get generated to disk individually. This can be useful for debugging or if you need to accumulate render passes differently than provided.
- L35 _public function_ `bool IsRenderDocEnabled() const` — Returns true if both the RenderCapture modular feature is available and the user has enabled capturing with RenderDoc
- L39 _public member_ `bool bCaptureFramesWithRenderDoc;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderDoc")` — If true, automatically trigger RenderDoc to capture rendering information for frames from CaptureStartFrame to CaptureEndFrame, inclusive
- L43 _public member_ `int32 CaptureFrame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderDoc")` — Used when capturing rendering information with RenderDoc. In Display Rate frames.
- L47 _public member_ `bool bCaptureUnrealInsightsTrace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profiling")` — If true, automatically capture an Unreal Insights trace file for the duration of the render.
- L50 _private member_ `bool bIsRenderDebugCaptureAvailable;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineExecutor.h` (Public)


#### class `UMoviePipelineExecutorBase`  
`class UMoviePipelineExecutorBase : public UObject`  
_L46-434_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UObject`
- desc: A Movie Pipeline Executor is responsible for executing an array of Movie Pipelines, and (optionally) reporting progress back for the movie pipelines. The entire array is passed at once to allow the implementations to choose how to split up the work. By default we provide a local execution (UMoviePipelineLocalExecutor) which works on them serially, but you can create an implementation of this class, change the default in the Project Settings and use your own distribution logic. For example, you may want to distribute the work to multiple computers over a network, which may involve running command line options on each machine to sync the latest content from the project before the execution starts.
- L50 _public function_ `UMoviePipelineExecutorBase() : bAnyJobHadFatalError(false) , PostRenderActionType(EMoviePipelinePostRenderActionType::DoNothing) , TargetPipelineClass(nullptr) , ExternalSocket(nullptr) , RecvMessageDataRemaining(0)`
- L78 _public prototype_ `void Execute(UMoviePipelineQueue* InPipelineQueue);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Execute the provided Queue. You are responsible for deciding how to handle each job in the queue and processing them. OnExecutorFinished should be called when all jobs are completed, which can report both success, warning, cancel, or error. For C++ implementations override `virtual void Execute_Implementation() const override` For Python/BP implementations override @unreal.ufunction(override=True) def execute(self): @param InPipelineQueue The queue that this should process all jobs for. This can be null when using certain combination of command line render flags/scripting.
- L92 _public prototype_ `bool IsRendering() const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Report the current state of the executor. This is used to know if we can call Execute again. For C++ implementations override `virtual bool IsRendering_Implementation() const override` For Python/BP implementations override @unreal.ufunction(override=True) def is_rendering(self): return ? @return True if the executor is currently working on a queue to produce a render.
- L105 _public prototype_ `void OnBeginFrame();` — `UFUNCTION(BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Called once at the beginning of each engine frame. For C++ implementations override `virtual bool OnBeginFrame_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def on_begin_frame(self): super().on_begin_frame()
- L121 _public prototype_ `void SetStatusMessage(const FString& InStatus);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Set the status of this Executor. Does nothing in default implementations, but a useful shorthand for implementations to broadcast status updates, ie: You can call SetStatusMessage as your executor changes state, and override the SetStatusMessage function to make it actually do something (such as printing to a log or updating a third party API). For C++ implementations override `virtual bool SetStatusMessage_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def set_status_message(self, inStatus): @param InStatus	The status message you wish the executor to have.
- L133 _public prototype_ `FString GetStatusMessage() const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Get the current status message for this job. May be an empty string. For C++ implementations override `virtual FString GetStatusMessage_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def get_status_message(self): return ?
- L152 _public prototype_ `void SetStatusProgress(const float InProgress);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Set the progress of this Executor. Does nothing in default implementations, but a useful shorthand for implementations to broadcast progress updates, ie: You can call SetStatusProgress as your executor changes progress, and override the SetStatusProgress function to make it actually do something (such as printing to a log or updating a third party API). Does not necessairly reflect the overall progress of the work, it is an arbitrary 0-1 value that can be used to indicate different things (depending on implementation). For C++ implementations override `virtual bool SetStatusProgress_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def set_status_progress(self, inStatus): @param InProgress	The progress (0-1 range) the executor should have.
- L164 _public prototype_ `float GetStatusProgress() const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Get the current progress as last set by SetStatusProgress. 0 by default. For C++ implementations override `virtual float GetStatusProgress_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def get_status_progress(self): return ?
- L170 _public prototype_ `void CancelCurrentJob();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Abort the currently executing job.
- L176 _public prototype_ `void CancelAllJobs();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Abort the currently executing job and skip all other jobs.
- L187 _public prototype_ `void SetPostRenderAction(const EMoviePipelinePostRenderActionType PostRenderAction);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Set the post-render action that will be taken when all the renders in the queue finish. For C++ implementations override `virtual void SetPostRenderAction_Implementation(const EMoviePipelinePostRenderActionType PostRenderAction) override` For Python/BP implementations override @unreal.ufunction(override=True) def set_post_render_action(self, postRenderAction):
- L198 _public prototype_ `EMoviePipelinePostRenderActionType GetPostRenderAction();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Get the post-render action that will be taken when all the renders in the queue finish. For C++ implementations override `virtual EMoviePipelinePostRenderActionType GetPostRenderAction_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def get_post_render_action(self):
- L212 _public prototype_ `bool GetSupportsPostRenderActions();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Get whether this executor supports performing a post-render action. The base executor classes do not implement post-render actions. Executors returning "true" here must implement support for post-render actions themselves. For C++ implementations override `virtual bool GetSupportsPostRenderActions_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def get_supports_post_render_actions(self):
- L218 _public function_ `void SetMoviePipelineClass(UClass* InPipelineClass)` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Specify which MoviePipeline class type should be created by this executor when processing jobs.
- L224 _public function_ `FOnMoviePipelineExecutorFinishedNative& OnExecutorFinished()` — Native C++ event to listen to for when this Executor has finished.
- L229 _public function_ `FOnMoviePipelineExecutorErroredNative& OnExecutorErrored()`
- L236 _protected function_ `virtual void BeginDestroy() override` — UObject Interface
- L255 _protected function_ `virtual void OnExecutorFinishedImpl()` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — This should be called when the Executor has finished executing all of the things it has been asked to execute. This should be called in the event of a failure as well, and passing in false for success to allow the caller to know failure. Errors should be broadcast on the error delegate, so this is just a handy way to know at the end without having to track it yourself. @param bInSuccess	True if the pipeline successfully executed all jobs. False if there was an error.
- L263 _protected function_ `virtual void OnExecutorErroredImpl(UMoviePipeline* ErroredPipeline, bool bFatal, FText ErrorReason)` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")`
- L275 _protected function_ `bool IsAnyJobErrored() const`
- L278 _protected prototype_ `virtual void Execute_Implementation(UMoviePipelineQueue* InPipelineQueue) PURE_VIRTUAL(UMoviePipelineExecutorBase::ExecuteImpl, );` — UMoviePipelineExecutorBase Interface
- L279 _protected prototype_ `virtual bool IsRendering_Implementation() const PURE_VIRTUAL(UMoviePipelineExecutorBase::IsRenderingImpl, return false; );`
- L280 _protected prototype_ `virtual void OnBeginFrame_Implementation();`
- L281 _protected function_ `virtual void SetStatusMessage_Implementation(const FString& InMessage)`
- L282 _protected function_ `virtual void SetStatusProgress_Implementation(const float InProgress)`
- L283 _protected function_ `virtual FString GetStatusMessage_Implementation() const`
- L284 _protected function_ `virtual float GetStatusProgress_Implementation() const`
- L285 _protected prototype_ `virtual void CancelCurrentJob_Implementation() PURE_VIRTUAL(UMoviePipelineExecutorBase::CancelCurrentJobImpl, );`
- L286 _protected prototype_ `virtual void CancelAllJobs_Implementation() PURE_VIRTUAL(UMoviePipelineExecutorBase::CancelAllJobsImpl, );`
- L287 _protected prototype_ `virtual void SetPostRenderAction_Implementation(const EMoviePipelinePostRenderActionType PostRenderAction);`
- L288 _protected function_ `virtual EMoviePipelinePostRenderActionType GetPostRenderAction_Implementation()`
- L289 _protected function_ `virtual bool GetSupportsPostRenderActions_Implementation()`
- L301 _private member_ `FOnMoviePipelineExecutorFinished OnExecutorFinishedDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Movie Render Pipeline")` — Called when the Executor has finished all jobs. Reports success if no jobs had fatal errors. Subscribe to the error delegate for more information about any errors. Exposed for Blueprints/Python. Called at the same time as the native one.
- L304 _private member_ `FOnMoviePipelineExecutorFinishedNative OnExecutorFinishedDelegateNative;` — For native C++ code. Called at the same time as the Blueprint/Python one.
- L313 _private member_ `FOnMoviePipelineExecutorErrored OnExecutorErroredDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Movie Render Pipeline")` — Called when an individual job reports a warning/error. Jobs are considered fatal if the severity was bad enough to abort the job (missing sequence, write failure, etc.) Exposed for Blueprints/Python. Called at the same time as the native one.
- L316 _private member_ `FOnMoviePipelineExecutorErroredNative OnExecutorErroredDelegateNative;` — For native C++ code. Called at the same time as the Blueprint/Python one.
- L319 _private member_ `bool bAnyJobHadFatalError;` — Set automatically when the error delegate gets broadcast (if fatal).
- L322 _private member_ `EMoviePipelinePostRenderActionType PostRenderActionType;` — The type of action that will be taken after all renders in the queue finish.
- L332 _protected prototype_ `bool ConnectSocket(const FString& InHostName, const int32 InPort);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Attempts to connect a socket to the specified host and port. This is a blocking call. @param InHostName	The host name as to connect to such as "127.0.0.1" @param InPort		The port to attempt to connect to the host on. @return True if the socket was succesfully connected to the given host and port.
- L338 _protected prototype_ `void DisconnectSocket();` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Disconnects the socket (if currently connected.)
- L348 _protected prototype_ `bool SendSocketMessage(const FString& InMessage);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Sends a socket message if the socket is currently connected. Messages back will happen in the OnSocketMessageRecieved event. @param InMessage	The message to send. This will be sent over the socket (if connected) with a 4 byte (int32) size prefix on the message so the recieving end knows how much data to recieve before considering it done. This prevents accidentally chopping json strings in half. @return True if the message was sent succesfully.
- L352 _protected prototype_ `bool IsSocketConnected() const;` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns true if the socket is currently connected, false otherwise. Call ConnectSocket to attempt a connection.
- L361 _protected member_ `FMoviePipelineSocketMessageRecieved SocketMessageRecievedDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Movie Render Pipeline")` — If this executor has been configured to connect to a socket, this event will be called each time the socket recieves something. The message response expected from the server should have a 4 byte (int32) size prefix for the string to specify how much data we should expect. This delegate will not get invoked until we recieve that many bytes from the socket connection to avoid broadcasting partial messages.
- L375 _protected prototype_ `int32 SendHTTPRequest(const FString& InURL, const FString& InVerb, const FString& InMessage, const TMap<FString, FString>& InHeaders);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Sends a asynchronous HTTP request. Responses will be returned in the the OnHTTPResponseRecieved event. @param InURL		The URL to send the request to. @param InVerb		The HTTP verb for the request. GET, PUT, POST, etc. @param InMessage	The content of the request. @param InHeaders	Headers that should be set on the request. @return Returns an index for the request. This index will be provided in the OnHTTPResponseRecieved event so you can make multiple HTTP requests at once and tell them apart when you recieve them, even if they come out of order.
- L379 _protected member_ `FMoviePipelineHttpResponseRecieved HTTPResponseRecievedDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Movie Render Pipeline")` — If an HTTP Request has been made and a response returned, the returned response will be broadcast on this event.
- L382 _private prototype_ `bool BlockingSendSocketMessageImpl(const uint8* Data, int32 BytesToSend);`
- L383 _private prototype_ `void OnHttpRequestCompletedImpl(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bWasSuccessful);`
- L384 _private prototype_ `bool ProcessIncomingSocketData();`
- L390 _public member_ `TSubclassOf<UMovieRenderDebugWidget> DebugWidgetClass;` — `UE_DEPRECATED(5.1, "Use SetViewportInitArgs instead.")` — `UPROPERTY(BlueprintReadWrite, Category = "Movie Render Pipeline")` — Optional widget for feedback during render
- L392 _public function_ `void SetViewportInitArgs(const UE::MoviePipeline::FViewportArgs& InArgs)`
- L396 _public member_ `UE::MoviePipeline::FViewportArgs ViewportInitArgs;` — Some global initialization args that get passed to the UMoviePipeline before the call to ::Initialize()
- L403 _public member_ `FString UserData;` — `UPROPERTY(BlueprintReadWrite, Category = "Movie Render Pipeline")` — Arbitrary data that can be associated with the executor. Not used by default implementations, nor read. This can be used to attach third party metadata such as job ids from remote farms.
- L407 _protected member_ `TSubclassOf<UMoviePipeline> TargetPipelineClass;` — `UPROPERTY(BlueprintReadWrite, Category = "Movie Render Pipeline")` — Which Pipeline Class should be created by this Executor. May be null.
- L409 _protected member_ `FString StatusMessage;`
- L410 _protected member_ `float StatusProgress;`
- L414 _private member_ `class FSocket* ExternalSocket;` — The socket connection if we currently have one.
- L417 _private member_ `TSharedPtr<FArrayReader, ESPMode::ThreadSafe> RecvMessageData;` — Message data we're currently in the process of receiving, if any
- L420 _private member_ `int32 RecvMessageDataRemaining;` — The number of bytes of incoming message data we're still waiting on before we have a complete message
- L433 _private member_ `TArray<FOutstandingRequest> OutstandingRequests;`

#### struct `UMoviePipelineExecutorBase::FOutstandingRequest`  
`struct FOutstandingRequest`  
_L422-431_
- L424 _public function_ `FOutstandingRequest() : RequestIndex(-1) , Request(nullptr)`
- L429 _public member_ `int32 RequestIndex;`
- L430 _public member_ `FHttpRequestPtr Request;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineExecutorFinishedNative, UMoviePipelineExecutorBase* , bool );`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineExecutorFinishedNative, UMoviePipelineExecutorBase* , bool );`
- L22 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineExecutorFinished, UMoviePipelineExecutorBase*, PipelineExecutor, bool, bSuccess);`
- L22 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineExecutorFinished, UMoviePipelineExecutorBase*, PipelineExecutor, bool, bSuccess);`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnMoviePipelineExecutorErroredNative, UMoviePipelineExecutorBase* , UMoviePipeline* , bool , FText );`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnMoviePipelineExecutorErroredNative, UMoviePipelineExecutorBase* , UMoviePipeline* , bool , FText );`
- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnMoviePipelineExecutorErrored, UMoviePipelineExecutorBase*, PipelineExecutor, UMoviePipeline*, PipelineWithError, bool, bIsFatal, FText, ErrorText);`
- L25 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnMoviePipelineExecutorErrored, UMoviePipelineExecutorBase*, PipelineExecutor, UMoviePipeline*, PipelineWithError, bool, bIsFatal, FText, ErrorText);`
- L28 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoviePipelineSocketMessageRecieved, const FString&, Message);` — Called when a socket message is recieved. String is UTF8 encoded and has had the length byte stripped from it.
- L28 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoviePipelineSocketMessageRecieved, const FString&, Message);` — Called when a socket message is recieved. String is UTF8 encoded and has had the length byte stripped from it.
- L31 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMoviePipelineHttpResponseRecieved, int32, RequestIndex, int32, ResponseCode, const FString&, Message);` — Called when the response for an HTTP request comes in.
- L31 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMoviePipelineHttpResponseRecieved, int32, RequestIndex, int32, ResponseCode, const FString&, Message);` — Called when the response for an HTTP request comes in.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineFCPXMLExporterSetting.h` (Public)


#### enum `FCPXMLExportDataSource`  
`enum class FCPXMLExportDataSource : uint8`  
_L11-15_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `OutputMetadata`
- L14 _public enumerator_ `SequenceData`

#### class `UMoviePipelineFCPXMLExporter`  
`class UMoviePipelineFCPXMLExporter : public UMoviePipelineOutputBase`  
_L18-51_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineOutputBase`
- L22 _public function_ `UMoviePipelineFCPXMLExporter() : DataSource(FCPXMLExportDataSource::SequenceData) , bHasFinishedExporting(false)`
- L29 _public function_ `virtual FText GetDisplayText() const override`
- L32 _protected function_ `virtual bool HasFinishedExportingImpl()`
- L33 _protected prototype_ `virtual void BeginExportImpl() override;`
- L35 _protected prototype_ `bool EnsureWritableFile();`
- L36 _protected member_ `bool bOverwriteFile;`
- L40 _public member_ `FString FileNameFormatOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output")` — File name format string override. If specified it will override the FileNameFormat from the Output setting. Can include folder prefixes, and format string tags ({sequence_name}, etc.)
- L44 _public member_ `FCPXMLExportDataSource DataSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output")` — Whether to build the FCPXML from sequence data directly (for reimporting) or from actual frame output data (for post processing)
- L48 _protected member_ `FString FilePath;` — The file to write to
- L50 _protected member_ `bool bHasFinishedExporting;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineGameMode.h` (Public)


#### class `AMoviePipelineGameMode`  
`class AMoviePipelineGameMode : public AGameModeBase`  
_L10-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AGameModeBase`
- L14 _public function_ `virtual void BeginPlay() override`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineGameOverrideSetting.h` (Public)


#### enum `EMoviePipelineTextureStreamingMethod`  
`enum class EMoviePipelineTextureStreamingMethod : uint8`  
_L14-22_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `None UMETA(DisplayName="Don't Override" )` — This will not change the texture streaming method / cvars the users has set.
- L19 _public enumerator_ `Disabled UMETA(DisplayName = "Disable Streaming")` — Disable the Texture Streaming system. Requires the highest amount of VRAM, but helps if Fully Load Used Textures still has blurry textures.
- L21 _public enumerator_ `FullyLoad UMETA(DisplayName = "Fully Load Used Textures")` — Fully load used textures instead of progressively streaming them in over multiple frames. Requires less VRAM but can occasionally still results in blurry textures.

#### class `UMoviePipelineGameOverrideSetting`  
`class UMoviePipelineGameOverrideSetting : public UMoviePipelineSetting`  
_L25-194_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineSetting`
- L29 _public function_ `UMoviePipelineGameOverrideSetting() PRAGMA_DISABLE_DEPRECATION_WARNINGS : GameModeOverride(nullptr) PRAGMA_ENABLE_DEPRECATION_WARNINGS , SoftGameModeOverride(AMoviePipelineGameMode::StaticClass()) , bCinematicQualitySettings(true) , TextureStreaming(EMoviePipelineTextureStreamingMethod::Disabled) , bUseLODZero(true) , bDisableHLODs(true) , bUseHighQualityShadows(true) , ShadowDistanceScale(10) , ShadowRadiusThreshold(0.001f) , bOverrideViewDistanceScale(true) , ViewDistanceScale(50) , bFlushGrassStreaming(true) , bOverrideGrassCullDistanceScale(true) , GrassCullDistanceScale(50.0f) , bOverrideGrassDensityScale(false) , GrassDensityScale(1.0f) , bFlushStreamingManagers(true) , bOverrideVirtualTextureFeedbackFactor(true) , VirtualTextureFeedbackFactor(1) , bDisableGPUTimeout(true)`
- L57 _public function_ `virtual FText GetDisplayText() const override`
- L59 _public function_ `virtual bool IsValidOnShots() const override`
- L60 _public function_ `virtual bool IsValidOnPrimary() const override`
- L61 _public prototype_ `virtual void BuildNewProcessCommandLineArgsImpl(TArray<FString>& InOutUnrealURLParams, TArray<FString>& InOutCommandLineArgs, TArray<FString>& InOutDeviceProfileCvars, TArray<FString>& InOutExecCmds) const override;`
- L62 _public prototype_ `virtual void SetupForPipelineImpl(UMoviePipeline* InPipeline) override;`
- L63 _public prototype_ `virtual void TeardownForPipelineImpl(UMoviePipeline* InPipeline) override;`
- L64 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L66 _public function_ `virtual bool IgnoreTransientFilters() const override` — Used to ensure we set the default values even if the user forgets to add it.
- L69 _public prototype_ `virtual void PostLoad() override;`
- L73 _protected prototype_ `void ApplyCVarSettings(const bool bOverrideValues);`
- L79 _public member_ `TSubclassOf<AGameModeBase> GameModeOverride;` — `UE_DEPRECATED(5.5, "Please use the SoftGameModeOverride property instead.")` — `UPROPERTY(BlueprintReadWrite, Category = "Game", meta = (DeprecatedProperty, DeprecationMessage = "Please use the SoftGameModeOverride property instead."))` — Optional Game Mode to override the map's default game mode with. This can be useful if the game's normal mode displays UI elements or loading screens that you don't want captured.
- L83 _public member_ `TSoftClassPtr<AGameModeBase> SoftGameModeOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Game Mode Override", Category = "Game")` — Optional Game Mode to override the map's default game mode with. This can be useful if the game's normal mode displays UI elements or loading screens that you don't want captured.
- L87 _public member_ `bool bCinematicQualitySettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")` — If true, automatically set the engine to the Cinematic Scalability quality settings during render. See the Scalability Reference documentation for information on how to edit cvars to add/change default quality values.
- L91 _public member_ `EMoviePipelineTextureStreamingMethod TextureStreaming;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Defines which If true, when using texture streaming fully load the required textures each frame instead of loading them in over time. This solves objects being blurry after camera cuts.
- L95 _public member_ `bool bUseLODZero;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Should we try to use the highest quality LOD for meshes and particle systems regardless of distance?
- L99 _public member_ `bool bDisableHLODs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta=(ScriptName="DisableHlods;DisableHLODs"))` — Should we disable Hierarchical LODs and instead use their real meshes regardless of distance?
- L103 _public member_ `bool bUseHighQualityShadows;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Should we override shadow-related CVars with some high quality preset settings?
- L107 _public member_ `int32 ShadowDistanceScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta=(EditCondition=bUseHighQualityShadows, ClampMin=0.1, UIMin=0.1, UIMax=10))` — Scalability option to trade shadow distance versus performance for directional lights
- L111 _public member_ `float ShadowRadiusThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (EditCondition = bUseHighQualityShadows, UIMin=0.001, ClampMin=0.001))` — Cull shadow casters if they are too small, value is the minimal screen space bounding sphere radius
- L115 _public member_ `bool bOverrideViewDistanceScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (InlineEditConditionToggle))` — Should we override the View Distance Scale? Can be used in situations where MaxDrawDistance has been set before for in-game performance.
- L119 _public member_ `int32 ViewDistanceScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (EditCondition = bOverrideViewDistanceScale))` — Controls the view distance scale. A primitive's MaxDrawDistance is scaled by this value.
- L123 _public member_ `bool bFlushGrassStreaming;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Flushing grass streaming (combined with override view distance scale) prevents visible pop-in/culling of grass instances.
- L127 _public member_ `bool bOverrideGrassCullDistanceScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (InlineEditConditionToggle))` — Should we override the Landscape Grass Cull Distance Scale? Can be used in situations where grass.CullDistanceScale has been set before for in-game performance.
- L131 _public member_ `float GrassCullDistanceScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (EditCondition = bOverrideGrassCullDistanceScale))` — Controls the grass cull distance scale. See grass.CullDistanceScale
- L135 _public member_ `bool bOverrideGrassDensityScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (InlineEditConditionToggle))` — Should we override the Landscape Grass Density Scale? Can be used in situations where grass.densityScale has been set before for in-game performance.
- L139 _public member_ `float GrassDensityScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (EditCondition = bOverrideGrassDensityScale))` — Controls the grass density scale. See grass.densityScale
- L143 _public member_ `bool bFlushStreamingManagers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Experimental. If true flush the streaming managers (Texture Streaming) each frame. Allows Texture Streaming to not have visible pop-in in final frames.
- L147 _public member_ `bool bOverrideVirtualTextureFeedbackFactor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (InlineEditConditionToggle))` — If true then override the virtual texture feedback resolution factor. Otherwise the value from the project renderer settings will be used.
- L151 _public member_ `int32 VirtualTextureFeedbackFactor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (editcondition = "bOverrideVirtualTextureFeedbackFactor"))` — The virtual texture feedback resolution factor. A lower factor will increase virtual texture feedback resolution.
- L154 _public member_ `bool bDisableGPUTimeout;` — Should we disable the GPU Timeout? Currently only applicable when using D3D12 renderer.
- L158 _private member_ `Scalability::FQualityLevels PreviousQualityLevels;` — To restore previous choices when we modify these at runtime. These will be unset if the user doesn't have the override enabled.
- L159 _private member_ `int32 PreviousFramesForFullUpdate;`
- L160 _private member_ `int32 PreviousFullyLoadUsedTextures;`
- L161 _private member_ `int32 PreviousTextureStreaming;`
- L162 _private member_ `int32 PreviousForceLOD;`
- L163 _private member_ `int32 PreviousSkeletalMeshBias;`
- L164 _private member_ `int32 PreviousParticleLODBias;`
- L165 _private member_ `float PreviousShadowDistanceScale;`
- L166 _private member_ `int32 PreviousShadowQuality;`
- L167 _private member_ `float PreviousShadowRadiusThreshold;`
- L168 _private member_ `float PreviousViewDistanceScale;`
- L169 _private member_ `float PreviousGrassCullDistanceScale;`
- L170 _private member_ `float PreviousGrassDensityScale;`
- L171 _private member_ `int32 PreviousGPUTimeout;`
- L172 _private member_ `int32 PreviousAnimationUROEnabled;`
- L173 _private member_ `int32 PreviousFoliageDitheredLOD;`
- L174 _private member_ `int32 PreviousFoliageForceLOD;`
- L175 _private member_ `int32 PreviousNeverMuteNonRealtimeAudio;`
- L176 _private member_ `bool PreviousNeverDisableSubmixes;`
- L177 _private member_ `int32 PreviousSkyLightRealTimeReflectionCaptureTimeSlice;`
- L178 _private member_ `int32 PreviousVolumetricRenderTarget;`
- L179 _private member_ `int32 PreviousVolumetricRenderTargetMode;`
- L180 _private member_ `int32 PreviousIgnoreStreamingPerformance;`
- L181 _private member_ `int32 PreviousStreamingManagerSyncState;`
- L183 _private member_ `int32 PreviousGeoCacheStreamerShowNotification;`
- L184 _private member_ `int32 PreviousGeoCacheStreamerBlockTillFinish;`
- L186 _private member_ `float PreviousChaosImmPhysicsMinStepTime;`
- L187 _private member_ `int32 PreviousSkipRedundantTransformUpdate;`
- L188 _private member_ `int32 PreviousChaosClothUseTimeStepSmoothing;`
- L189 _private member_ `int32 PreviousSkipWaterInfoTextureRenderWhenWorldRenderingDisabled;`
- L190 _private member_ `int32 PreviousNaniteVSMInvalidateOnLODDelta;`
- L191 _private member_ `int32 PreviousAllowSlateThrottling;`
- L192 _private member_ `bool PreviousAlphaOutput;`
- L193 _private member_ `int32 PreviousLUTSize;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineHighResSetting.h` (Public)


#### class `UMoviePipelineHighResSetting`  
`class UMoviePipelineHighResSetting : public UMoviePipelineSetting`  
_L15-221_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineSetting`
- L19 _public function_ `UMoviePipelineHighResSetting() : TileCount(1) , TextureSharpnessBias(0.f) , OverlapRatio(0.f) , bOverrideSubSurfaceScattering(false) , BurleySampleCount(64) , bAllocateHistoryPerTile(true) , bPageToSystemMemory(false)`
- L30 _public function_ `FIntPoint CalculatePaddedBackbufferSize(const FIntPoint& InTileSize) const`
- L40 _public function_ `virtual FText GetDisplayText() const override`
- L42 _public function_ `virtual bool IsValidOnShots() const override`
- L43 _public function_ `virtual bool IsValidOnPrimary() const override`
- L44 _public function_ `virtual void ValidateStateImpl() override`
- L59 _public function_ `virtual void GetFormatArguments(FMoviePipelineFormatArgs& InOutFormatArgs) const override`
- L69 _public function_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override`
- L75 _public function_ `virtual FText GetFooterText(UMoviePipelineExecutorJob* InJob) const override`
- L151 _public function_ `virtual void SetupForPipelineImpl(UMoviePipeline* InPipeline) override`
- L157 _public function_ `virtual void TeardownForPipelineImpl(UMoviePipeline* InPipeline) override`
- L172 _public member_ `int32 TileCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1", ClampMin = "1", UIMax = "16"), Category = "Render Settings")` — How many tiles should the resulting movie render be broken into? A tile should be no larger than the maximum texture resolution supported by your graphics card (likely 16k), so NumTiles should be ceil(Width/MaxTextureSize). More tiles mean more individual passes over the whole scene at a smaller resolution which may help with gpu timeouts. Requires at least 1 tile. Tiling is applied evenly to both X and Y.
- L181 _public member_ `float TextureSharpnessBias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "-1", UIMax = "0"), Category = "Render Settings")` — This bias encourages the engine to use a higher detail texture when it would normally use a lower detail texture due to the size of the texture on screen. A more negative number means overall sharper images (up to the detail resolution of your texture). Too much sharpness will cause visual grain/noise in the resulting image, but this can be mitigated with more spatial samples.
- L189 _public member_ `float OverlapRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0", ClampMin = "0", UIMax = "0.5", ClampMax = "1"), Category = "Render Settings")` — How much should each tile overlap each other (0-0.5). Decreasing the overlap will result in smaller individual tiles (which means faster renders) but increases the likelyhood of edge-of-screen artifacts showing up which will become visible in the final image as a "grid" of repeated problem areas.
- L196 _public member_ `bool bOverrideSubSurfaceScattering;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render Settings")` — Sub Surface Scattering relies on history which is not available when using tiling. This can be overriden to use more samples to improve the quality.
- L202 _public member_ `int32 BurleySampleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "64", ClampMin = "0", UIMax = "1024", EditCondition="bOverrideSubSurfaceScattering"), Category = "Render Settings")` — How many samples should the Burley Sub Surface Scattering use?
- L209 _public member_ `bool bAllocateHistoryPerTile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render Settings")` — If true, allocate a unique history for each tile. This is needed to make some render features work, including auto-exposure and Lumen, but should be disabled when dealing with extremely large resolutions as you will spend all of your GPU memory on history buffers.
- L215 _public member_ `bool bPageToSystemMemory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render Settings")` — If true, persistent GPU data per high resolution tile is mirrored to system memory, allowing higher resolutions, but increasing render time.
- L220 _private member_ `int32 PrevBurleyOverride;` — What was the Burley CVar before we overrode it?

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineImageQuantization.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MoviePipeline` (scope `UE`)
- L10 _prototype_ `TUniquePtr<FImagePixelData> QuantizeImagePixelDataToBitDepth(const FImagePixelData* InData, const int32 TargetBitDepth, FImagePixelPayloadPtr InPayload = nullptr, bool bConvertToSrgb = true);` (scope `UE::MoviePipeline`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineInProcessExecutor.h` (Public)


#### class `UMoviePipelineInProcessExecutor`  
`class UMoviePipelineInProcessExecutor : public UMoviePipelineLinearExecutorBase`  
_L20-75_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineLinearExecutorBase`
- desc: This executor implementation can process an array of movie pipelines and run them inside the currently running process. This is intended for usage outside of the editor (ie. -game mode) as it will take over the currently running world/game instance instead of launching a new world instance like the editor only PIE.
- L25 _public function_ `UMoviePipelineInProcessExecutor() : UMoviePipelineLinearExecutorBase() , bUseCurrentLevel(false) , RemainingInitializationFrames(-1)`
- L34 _public member_ `bool bUseCurrentLevel;` — `UPROPERTY(BlueprintReadWrite, Category = "Movie Render Pipeline")` — Use current level instead of opening new level
- L36 _public function_ `FMoviePipelineWorkFinishedNative& OnIndividualJobFinished()`
- L42 _protected prototype_ `virtual void Start(const UMoviePipelineExecutorJob* InJob) override;`
- L43 _protected prototype_ `virtual void CancelAllJobs_Implementation() override;`
- L44 _protected prototype_ `virtual void CancelCurrentJob_Implementation() override;`
- L46 _private prototype_ `void OnMapLoadFinished(UWorld* NewWorld);`
- L47 _private prototype_ `void OnMoviePipelineFinished(FMoviePipelineOutputData InOutputData);`
- L48 _private prototype_ `void OnApplicationQuit();`
- L49 _private prototype_ `void OnTick();`
- L51 _private prototype_ `void BackupState();`
- L52 _private prototype_ `void ModifyState(const UMoviePipelineExecutorJob* InJob);`
- L53 _private prototype_ `void RestoreState();`
- L57 _private member_ `int32 RemainingInitializationFrames;` — If using delayed initialization, how many frames are left before we call Initialize. Will be -1 if not actively counting down.
- L73 _private member_ `FSavedState SavedState;`
- L74 _private member_ `FMoviePipelineWorkFinishedNative OnIndividualJobFinishedDelegateNative;`

#### struct `UMoviePipelineInProcessExecutor::FSavedState`  
`struct FSavedState`  
_L59-71_
- L61 _public member_ `bool bBackedUp = false;`
- L64 _public member_ `bool bCinematicMode = false;` — PlayerController
- L65 _public member_ `bool bHidePlayer = false;`
- L67 _public member_ `bool bUseFixedTimeStep = false;`
- L68 _public member_ `double FixedDeltaTime = 1.0;`
- L70 _public member_ `TOptional<FText> WindowTitle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineInProcessExecutorSettings.h` (Public)


#### class `UMoviePipelineInProcessExecutorSettings`  
`class UMoviePipelineInProcessExecutorSettings : public UDeveloperSettings`  
_L13-64_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = Engine, defaultconfig, meta=(DisplayName = "Movie Pipeline New Process"))`
- inherits: `UDeveloperSettings`
- desc: This is the implementation responsible for executing the rendering of multiple movie pipelines after being launched via the command line.
- L18 _public function_ `UMoviePipelineInProcessExecutorSettings() : Super()`
- L40 _public function_ `virtual FName GetContainerName() const override` — Gets the settings container name for the settings, either Project or Editor
- L42 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L46 _public member_ `bool bCloseEditor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Startup")` — If enabled the editor will close itself when a new process is started. This can be used to gain some performance.
- L50 _public member_ `FString AdditionalCommandLineArguments;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Startup")` — A list of additional command line arguments to be appended to the new process startup. In the form of "-foo -bar=baz". Can be useful if your game requires certain arguments to start such as disabling log-in screens.
- L54 _public member_ `FString InheritedCommandLineArguments;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, config, Category = "Startup")` — A list of command line arguments which are inherited from the currently running Editor instance that will be automatically appended to the new process.
- L63 _public member_ `int32 InitialDelayFrameCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, meta = (UIMin = "0", ClampMin = "0", UIMax = "150"), Category = "Startup")` — How long should we wait after being initialized to start doing any work? This can be used to work around situations where the game is not fully loaded by the time the pipeline is automatically started and it is important that the game is fully loaded before we do any work (such as evaluating frames for warm-up).

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineLinearExecutor.h` (Public)


#### class `UMoviePipelineLinearExecutorBase`  
`class UMoviePipelineLinearExecutorBase : public UMoviePipelineExecutorBase`  
_L20-78_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UMoviePipelineExecutorBase`
- desc: This is an abstract base class designed for executing an array of movie pipelines in linear fashion. It is generally the case that you only want to execute one at a time on a local machine and a different executor approach should be taken for a render farm that distributes out jobs to many different machines.
- L25 _public function_ `UMoviePipelineLinearExecutorBase() : UMoviePipelineExecutorBase() , CurrentPipelineIndex(0) , JobsStarted(0) , bIsRendering(false)`
- L35 _protected prototype_ `virtual void Execute_Implementation(UMoviePipelineQueue* InPipelineQueue) override;` — UMoviePipelineExecutorBase Interface
- L36 _protected function_ `virtual bool IsRendering_Implementation() const override`
- L39 _protected prototype_ `virtual void StartPipelineByIndex(int32 InPipelineIndex);`
- L40 _protected function_ `virtual void Start(const UMoviePipelineExecutorJob* InJob)`
- L41 _protected prototype_ `virtual FText GetWindowTitle();`
- L42 _protected prototype_ `virtual float GetCompletionPercentageFromActivePipeline();`
- L45 _public prototype_ `virtual void OnIndividualPipelineFinished(UMoviePipeline* );` — Note: When using a Movie Graph Pipeline this pointer will always be null.
- L46 _public prototype_ `virtual void OnExecutorFinishedImpl();`
- L48 _public prototype_ `virtual void OnPipelineErrored(UMoviePipeline* InPipeline, bool bIsFatal, FText ErrorText);` — Note: When using a Movie Graph Pipeline InPipeline will always be null.
- L50 _public prototype_ `virtual void CancelCurrentJob_Implementation();`
- L51 _public prototype_ `virtual void CancelAllJobs_Implementation();`
- L57 _protected member_ `TObjectPtr<UMoviePipelineQueue> Queue;` — `UPROPERTY(Transient)` — List of Pipeline Configs we've been asked to execute.
- L61 _protected member_ `TObjectPtr<UMoviePipelineBase> ActiveMoviePipeline;` — `UPROPERTY(Transient)` — A Movie Pipeline that has been spawned and is running (if any)
- L64 _protected member_ `int32 CurrentPipelineIndex;` — Which Pipeline Config are we currently working on.
- L67 _protected member_ `int32 JobsStarted;` — The number of jobs started by this executor during this execution.
- L70 _protected member_ `bool bIsRendering;` — Have we actually successfully started a render?
- L73 _protected member_ `bool bIsCanceling;` — Are we in the process of canceling all execution of the queue? Will stop new jobs from being started.
- L77 _private member_ `FDateTime InitializationTime;` — Used to track total processing duration.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineOutputBase.h` (Public)


#### class `UMoviePipelineOutputBase`  
`class UMoviePipelineOutputBase : public UMoviePipelineSetting`  
_L18-82_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UMoviePipelineSetting`
- desc: A base class for different output containers for the data generated by the Movie Pipeline, i.e: image sequences, video containers, etc.
- L27 _public function_ `void OnReceiveImageData(FMoviePipelineMergerOutputFrame* InMergedOutputFrame)` — Called when a frame is ready for output. This will contain all passes the user has requested for the given output frame. It also contains metrics about the output frame (such as frame number).
- L34 _public function_ `void BeginFinalize()` — Called once when all frames have been produced for the pipeline. Use this as an indicator to start flushing to disk. Async processes can be started here and HasFinishedProcessing() will be called each frame until all all containers return true, at which point Finalize will be called.
- L40 _public function_ `bool HasFinishedProcessing()` — Called each frame to check to see if this output container has finished processing. Finalize won't be called until all output containers return true for this.
- L45 _public function_ `void Finalize()` — Called after all output containers have reported that they are done processing.
- L50 _public function_ `void OnShotFinished(const UMoviePipelineExecutorShot* InShot, const bool bFlushToDisk)` — This is called when a shot ends, right after the last frame is rendered.
- L55 _public function_ `void OnPipelineFinished()` — This is called during the Shutdown process of the Pipeline. This is after finalization.
- L60 _public function_ `void OnPostTick()` — Called at the end of the frame, before rendering has happened for that frame.
- L64 _protected function_ `virtual void OnReceiveImageDataImpl(FMoviePipelineMergerOutputFrame* InMergedOutputFrame)` — UMoviePipelineOutputBase Interface
- L65 _protected function_ `virtual void BeginFinalizeImpl()`
- L66 _protected function_ `virtual bool HasFinishedProcessingImpl()`
- L67 _protected function_ `virtual void FinalizeImpl()`
- L68 _protected function_ `virtual void OnShotFinishedImpl(const UMoviePipelineExecutorShot* InShot, const bool bFlushToDisk = false)`
- L69 _protected function_ `virtual void OnPipelineFinishedImpl()`
- L70 _protected function_ `virtual void OnPostTickImpl()`
- L73 _protected function_ `virtual bool ShouldCropOverscanImpl() const` — Returns whether any overscan should be automatically cropped from the image before compositing and output
- L77 _protected function_ `virtual bool IsValidOnShots() const override`
- L78 _protected function_ `virtual bool IsValidOnPrimary() const override`
- L80 _protected function_ `virtual FText GetCategoryText() const override`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineOutputBuilder.h` (Public)


#### class `FMoviePipelineOutputMerger`  
`class FMoviePipelineOutputMerger : public MoviePipeline::IMoviePipelineOutputMerger`  
_L16-42_
- inherits: `MoviePipeline::IMoviePipelineOutputMerger`
- L19 _public function_ `FMoviePipelineOutputMerger(UMoviePipeline* InOwningMoviePipeline) : WeakMoviePipeline(MakeWeakObjectPtr(InOwningMoviePipeline))`
- L25 _public prototype_ `virtual FMoviePipelineMergerOutputFrame& QueueOutputFrame_GameThread(const FMoviePipelineFrameOutputState& CachedOutputState) override;`
- L26 _public prototype_ `virtual void OnCompleteRenderPassDataAvailable_AnyThread(TUniquePtr<FImagePixelData>&& InData) override;`
- L27 _public prototype_ `virtual void OnSingleSampleDataAvailable_AnyThread(TUniquePtr<FImagePixelData>&& InData) override;`
- L28 _public prototype_ `virtual void AbandonOutstandingWork() override;`
- L29 _public function_ `virtual int32 GetNumOutstandingFrames() const override`
- L32 _public member_ `TQueue<FMoviePipelineMergerOutputFrame> FinishedFrames;`
- L35 _private member_ `TWeakObjectPtr<UMoviePipeline> WeakMoviePipeline;` — The Movie Pipeline that owns us.
- L38 _private member_ `TSortedMap<FMoviePipelineFrameOutputState, FMoviePipelineMergerOutputFrame> PendingData;` — Data that is expected but not fully available yet. Sorted by frame number.
- L41 _private member_ `FCriticalSection ActiveDataMutex;` — Mutex that protects adding/updating/removing from ActiveData

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineOutputSetting.h` (Public)


#### class `UMoviePipelineOutputSetting`  
`class UMoviePipelineOutputSetting : public UMoviePipelineSetting`  
_L14-124_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineSetting`
- L18 _public prototype_ `UMoviePipelineOutputSetting();`
- L21 _public function_ `virtual FText GetDisplayText() const override`
- L22 _public prototype_ `virtual FText GetFooterText(UMoviePipelineExecutorJob* InJob) const override;`
- L23 _public function_ `virtual bool CanBeDisabled() const override`
- L25 _public function_ `virtual bool IsValidOnShots() const override`
- L26 _public function_ `virtual bool IsValidOnPrimary() const override`
- L27 _public prototype_ `virtual void GetFormatArguments(FMoviePipelineFormatArgs& InOutFormatArgs) const override;`
- L28 _public prototype_ `virtual void SetupForPipelineImpl(UMoviePipeline* InPipeline) override;`
- L31 _public prototype_ `virtual void PostLoad() override;` — UObject Interface
- L34 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L39 _public member_ `FDirectoryPath OutputDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output")` — What directory should all of our output files be relative to.
- L43 _public member_ `FString FileNameFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output")` — What format string should the final files use? Can include folder prefixes, and format string ({shot_name}, etc.)
- L47 _public member_ `FIntPoint OutputResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output")` — What resolution should our output files be exported at?
- L52 _public member_ `bool bUseCustomFrameRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output")` — Should we use the custom frame rate specified by OutputFrameRate? Otherwise defaults to Sequence frame rate.
- L56 _public member_ `FFrameRate OutputFrameRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition=bUseCustomFrameRate), Category = "File Output")` — What frame rate should the output files be exported at? This overrides the Display Rate of the target sequence.
- L59 _public member_ `int32 DEBUG_OutputFrameStepOffset;` — Experimental way to interleave renders between multiple computers. If FrameStep is 5, and each render is offset by 0-4, they'll render a different subset of frames to add up to all.
- L63 _public member_ `bool bOverrideExistingOutput;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output")` — If true, output containers should attempt to override any existing files with the same name.
- L74 _public member_ `int32 HandleFrameCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0, ClampMin = 0), Category = "Frames")` — Top level shot track sections will automatically be expanded by this many frames in both directions, and the resulting additional time will be rendered as part of that shot. The inner sequence should have sections long enough to cover this expanded range, otherwise these tracks will not evaluate during handle frames and may produce unexpected results. This can be used to generate handle frames for traditional non linear editing tools.
- L78 _public member_ `int32 OutputFrameStep;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1", ClampMin = "1"), Category = "Frames")` — Render every Nth frame. ie: Setting this value to 2 renders every other frame. Game Thread is still evaluated on 'skipped' frames for accuracy between renders of different OutputFrameSteps.
- L82 _public member_ `bool bUseCustomPlaybackRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frames")` — If true, override the Playback Range start/end bounds with the bounds specified below.
- L86 _public member_ `int32 CustomStartFrame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition=bUseCustomPlaybackRange), Category = "Frames")` — Used when overriding the playback range. In Display Rate frames. If bUseCustomPlaybackRange is false range will come from Sequence.
- L90 _public member_ `int32 CustomEndFrame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition=bUseCustomPlaybackRange), Category = "Frames")` — Used when overriding the playback range. In Display Rate frames. If bUseCustomPlaybackRange is false range will come from Sequence.
- L95 _public member_ `int32 VersionNumber;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bAutoVersion", UIMin = 1, UIMax = 10, ClampMin = 1), Category = "Versioning")` — The value to use for the version token if versions are not automatically incremented.
- L99 _public member_ `bool bAutoVersion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")` — If true, version tokens will automatically be incremented with each local render. If false, the custom version number below will be used.
- L103 _public member_ `TArray<TObjectPtr<USoundSubmix>> AdditionalSubmixOutputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output")` — Exports additional .wav file for each submix if .wav output is selected, excludes the device's MasterSubmix.
- L108 _public member_ `int32 ZeroPadFrameNumbers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1", UIMax = "5", ClampMin = "1"), AdvancedDisplay, Category = "File Output")` — How many digits should all output frame numbers be padded to? MySequence_1.png -> MySequence_0001.png. Useful for software that struggles to recognize frame ranges when non-padded.
- L115 _public member_ `int32 FrameNumberOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "File Output")` — How many frames should we offset the output frame number by? This is useful when using handle frames on Sequences that start at frame 0, as the output would start in negative numbers. This can be used to offset by a fixed amount to ensure there's no negative numbers.
- L123 _public member_ `bool bFlushDiskWritesPerShot;` — `UPROPERTY(BlueprintReadWrite, Category = "File Output")` — If true, the game thread will stall at the end of each shot to flush the rendering queue, and then flush any outstanding writes to disk, finalizing any outstanding videos and generally completing the work. This is intentionally not exposed to the user interface as it is only relevant for scripting where scripts may do post-shot callback work.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelinePanoramicBlenderBase.h` (Public)


#### enum `EMoviePipelinePanoramicFilterType`  
`enum class EMoviePipelinePanoramicFilterType : uint8`  
_L14-22_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Bilinear` — 2x2 Bilinear Interpolation. Fastest, nearly the same quality as other options.
- L19 _public enumerator_ `Catmull` — Cubic Catmull-Rom interpolation. Slightly sharper than other results. Uses B=0, C=1/2 in parameterized cubic equation.
- L21 _public enumerator_ `Mitchell` — Cubic Mitchell-Netravali interpolation. More neutral look. Uses B=0.33, C=0.33 in parameterized cubic equation.

#### struct `UE::MoviePipeline::FPanoramicPane`  
`struct FPanoramicPane`  
_L26-109_
- L29 _public member_ `FVector OriginalCameraLocation;` — The camera location as defined by the actual sequence, consistent for all panes.
- L31 _public member_ `FVector PrevOriginalCameraLocation;` — The camera location last frame, used to ensure camera motion vectors are right.
- L33 _public member_ `FRotator OriginalCameraRotation;` — The camera rotation as defined by the actual sequence
- L35 _public member_ `FRotator PrevOriginalCameraRotation;` — The camera rotation last frame, used to ensure camera motion vectors are right.
- L37 _public member_ `float NearClippingPlane;` — The near clip plane distance from the camera.
- L40 _public member_ `float EyeSeparation;` — How far apart are the eyes (total) for stereo?
- L41 _public member_ `float EyeConvergenceDistance;`
- L44 _public member_ `float HorizontalFieldOfView;` — The horizontal field of view this pane was rendered with
- L45 _public member_ `float VerticalFieldOfView;`
- L47 _public member_ `FIntPoint Resolution;`
- L50 _public member_ `FVector CameraLocation;` — The actual rendering location for this pane, offset by the stereo eye if needed.
- L51 _public member_ `FVector PrevCameraLocation;`
- L52 _public member_ `FRotator CameraRotation;`
- L53 _public member_ `FRotator CameraLocalRotation;`
- L54 _public member_ `FRotator PrevCameraRotation;`
- L57 _public member_ `bool bUseLocalRotation;` — If true, uses only the CameraLocalRotation which means that if the camera yaws, so will the resulting blended image.
- L60 _public member_ `int32 NumHorizontalSteps;` — How many horizontal segments are there total.
- L61 _public member_ `int32 NumVerticalSteps;`
- L64 _public member_ `int32 HorizontalStepIndex;` — Which horizontal segment are we?
- L66 _public member_ `int32 VerticalStepIndex;` — Which vertical segment are we?
- L97 _public member_ `EMoviePipelinePanoramicFilterType FilterType = EMoviePipelinePanoramicFilterType::Bilinear;`
- L100 _public function_ `int32 GetAbsoluteIndex() const` — When indexing into arrays of Panes, which index is this?
- L108 _public member_ `int32 EyeIndex;` — -1 if no stereo, 0 left eye, 1 right eye.

#### struct `UE::MoviePipeline::FPanoramicPane::FCubicInterpolationParams`  
`struct FCubicInterpolationParams`  
_L68-95_
- L70 _public member_ `float ParamB;`
- L71 _public member_ `float ParamC;`
- L73 _public function_ `static FCubicInterpolationParams GetParamsForType(const EMoviePipelinePanoramicFilterType InType)`

#### class `UE::MoviePipeline::FMoviePipelinePanoramicBlenderBase`  
`class FMoviePipelinePanoramicBlenderBase`  
_L129-157_
- desc: This class is responsible for blending a together a single Equirectangular Image from a series of individual renders, and can blend multiple samples in a threadsafe way. For each incoming sample the pixel data should contain information about panoramic pane (orientation, index, etc.), and one all samples have been called BlendSample_AnyThread, it is safe for the owner of this instance to fetch the image data, which returns a copy of the output image. You can then call Initialize() on it to reset the output image without reallocating memory, which allows for reusing a given output blender for multiple frames. This implementation works by allocating memory for each incoming sample that is the size of the data once blended. Depending on where in the projection it is, different samples will take up different parts of the output image (with different resolutions) so the pool stores available buffers by resolution. Once a pool is either found or allocated for the sample, the incoming data is read from. Instead of taking each sample in the incoming data and figuring out where it would go in the output image, we instead work backwards, and calculate from each output pixel in the range that the sample would affect, sample the source image with filtering. Once the blending into the temporary buffer is complete, a lock on the output array is taken and the data is added to the output, and the buffer is returned to the pool.
- L132 _public prototype_ `void Initialize(const FIntPoint InOutputResolution);`
- L134 _public prototype_ `void BlendSample_AnyThread(TUniquePtr<FImagePixelData>&& InData, const UE::MoviePipeline::FPanoramicPane& Pane, TUniqueFunction<void(FLinearColor*, FIntPoint)> OnDebugSampleAvailable);`
- L135 _public prototype_ `void FetchFinalPixelDataHalfFloat(TArray64<FFloat16Color>& OutPixelData) const;`
- L136 _public prototype_ `void FetchFinalPixelDataLinearColor(TArray64<FLinearColor>& OutPixelData) const;`
- L138 _public member_ `TUniquePtr<UE::Tasks::FTaskConcurrencyLimiter> TaskConcurrencyLimiter;`
- L150 _private member_ `TArray64<TUniquePtr<FPoolEntry>> TempBufferPool;`
- L151 _private member_ `FCriticalSection PoolAccessMutex;`
- L152 _private member_ `FCriticalSection OutputMapAccessMutex;`
- L154 _private member_ `TArray64<FLinearColor> OutputEquirectangularMap;`
- L155 _private member_ `FIntPoint OutputEquirectangularMapSize;`

#### struct `UE::MoviePipeline::FMoviePipelinePanoramicBlenderBase::FPoolEntry`  
`struct FPoolEntry`  
_L140-148_
- L142 _public member_ `std::atomic<bool> bActive;`
- L143 _public member_ `TArray64<FLinearColor> Data;`
- L145 _public member_ `FIntPoint Resolution;`
- L146 _public member_ `FIntPoint OutputBoundsMin;`
- L147 _public member_ `FIntPoint OutputBoundsMax;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MoviePipeline` (scope `UE`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelinePostRenderSettings.h` (Public)


#### enum `EMovieGraphPlaybackMethod`  
`enum class EMovieGraphPlaybackMethod : uint8`  
_L16-23_
- reflection: `UENUM(BlueprintType)`
- desc: The type of viewer that should be used to play back media.
- L19 _public enumerator_ `OperatingSystem` — Use the operating system's default application for playing back media of the type that's being viewed.
- L22 _public enumerator_ `CustomViewer` — Use a specific application for playing back media.

#### enum `EMovieGraphImageSequencePlaybackRange`  
`enum class EMovieGraphImageSequencePlaybackRange : uint8`  
_L27-34_
- reflection: `UENUM(BlueprintType)`
- desc: The frame range for image sequences that should be used during playback.
- L30 _public enumerator_ `FirstFrameOnly` — Only play back the first frame.
- L33 _public enumerator_ `FullRange` — Play back all available frames.

#### enum `EMovieGraphJobPlaybackRange`  
`enum class EMovieGraphJobPlaybackRange : uint8`  
_L38-45_
- reflection: `UENUM(BlueprintType)`
- desc: Dictates which jobs should be used to get media from for playback if more than one job generated media.
- L41 _public enumerator_ `FirstJobOnly` — Only play back media from the first job that was rendered.
- L44 _public enumerator_ `AllJobs` — Play back media from all of the jobs that were rendered.

#### enum `EMovieGraphRenderLayerPlaybackRange`  
`enum class EMovieGraphRenderLayerPlaybackRange : uint8`  
_L49-56_
- reflection: `UENUM(BlueprintType)`
- desc: Dictates the selection of render layers that should be used in playback if more than one was generated.
- L52 _public enumerator_ `FirstRenderLayerOnly` — Only play back media from the first render layer that was rendered.
- L55 _public enumerator_ `AllRenderLayers` — Play back media from all render layers that were rendered.

#### enum `EMovieGraphFrameRangeNotation`  
`enum class EMovieGraphFrameRangeNotation : uint8`  
_L60-85_
- reflection: `UENUM(BlueprintType)`
- desc: The symbol that should be used to substitute a frame number within image paths.
- L66 _public enumerator_ `HashWithStartEndFrame UMETA(DisplayName = "# with Start/End Frame")` — Hash symbol. Includes the rendered frame range after the file path(s) are given on the command line. For example, "Layer1.#.exr 100-150" for an image sequence that included the frame number in the file name, and a frame range of 100-150 was rendered.
- L72 _public enumerator_ `Hash UMETA(DisplayName = "# without Start/End Frame")` — Hash symbol. Does not include the rendered frame range on the command line. For example, "Layer1.#.exr" for an image sequence that included the frame number in the file name.
- L78 _public enumerator_ `DollarF UMETA(DisplayName = "$F")` — $F. Includes the rendered frame range before the file paths(s) are given on the command line. For example, "-f 100 150 1 Layer1.$F.exr" for an image sequence that included the frame number in the file name, and a frame range of 100-150 was rendered.
- L84 _public enumerator_ `StartFrame` — Use the path for the first rendered frame only. For example, "Layer1.100.exr", if frame 100 was the first frame rendered.

#### enum `EMovieGraphOutputTypePlayback`  
`enum class EMovieGraphOutputTypePlayback : uint8`  
_L89-103_
- reflection: `UENUM(BlueprintType)`
- desc: How media should be selected for playback when more than one type was generated by a render.
- L95 _public enumerator_ `UsePriorityOrder` — Use the priority order when determining the media to play (the media with the extension that has the highest priority is played). The priority order is specified in Editor Preferences.
- L102 _public enumerator_ `PlayAllOutputTypes` — Play all media types that were generated from the render. Note that the highest-priority media dictates the player that will be used. In order for lower-priority media to also be played back, the lower-priority media must be configured to use the same player that the highest-priority is configured to use.

#### enum `EMovieGraphDirectoryOpenBehavior`  
`enum class EMovieGraphDirectoryOpenBehavior : uint8`  
_L107-114_
- reflection: `UENUM(BlueprintType)`
- desc: When opening directories via the Play After Render feature, this dictates how they're opened.
- L110 _public enumerator_ `OpenDirectoryForFirstJob` — Open the output directory for the first job in the queue only.
- L113 _public enumerator_ `OpenDirectoryForAllJobs` — Open the output directory for all jobs in the queue.

#### struct `FMovieGraphPostRenderVideoPlayOptions`  
`struct FMovieGraphPostRenderVideoPlayOptions`  
_L118-143_
- reflection: `USTRUCT(BlueprintType)`
- desc: Options that dictate how videos should be played back after a render completes.
- L122 _public prototype_ `FMovieGraphPostRenderVideoPlayOptions();`
- L126 _public member_ `EMovieGraphPlaybackMethod PlaybackMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Determines which application is used to open rendered media for playback.
- L130 _public member_ `FFilePath PlayerExecutable;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "PlaybackMethod == EMovieGraphPlaybackMethod::CustomViewer", EditConditionHides))` — If using a custom viewer, this is the path to the executable to use.
- L134 _public member_ `FString AdditionalCommandLineArguments;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "PlaybackMethod == EMovieGraphPlaybackMethod::CustomViewer", EditConditionHides))` — If using a custom viewer, these command line arguments are passed along.
- L138 _public member_ `EMovieGraphJobPlaybackRange JobPlayback;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "PlaybackMethod == EMovieGraphPlaybackMethod::CustomViewer"))` — The jobs that should have their media played.
- L142 _public member_ `EMovieGraphRenderLayerPlaybackRange RenderLayerPlayback;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "PlaybackMethod == EMovieGraphPlaybackMethod::CustomViewer"))` — The render layers that should have their media played.

#### struct `FMovieGraphPostRenderImageSequencePlayOptions`  
`struct FMovieGraphPostRenderImageSequencePlayOptions : public FMovieGraphPostRenderVideoPlayOptions`  
_L147-160_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMovieGraphPostRenderVideoPlayOptions`
- desc: Options that dictate how images should be played back after a render completes.
- L151 _public prototype_ `FMovieGraphPostRenderImageSequencePlayOptions();`
- L155 _public member_ `EMovieGraphFrameRangeNotation FrameRangeNotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayAfter = "AdditionalCommandLineArguments", EditCondition = "PlaybackMethod == EMovieGraphPlaybackMethod::CustomViewer", EditConditionHides))` — The symbol that will be used to replace the frame number in image paths when providing those paths to external viewers.
- L159 _public member_ `EMovieGraphImageSequencePlaybackRange PlaybackRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayAfter = "FrameRangeNotation", EditCondition = "PlaybackMethod == EMovieGraphPlaybackMethod::CustomViewer"))` — The range of frames to play back (only applicable to image sequences).

#### struct `FMovieGraphPostRenderSettings`  
`struct FMovieGraphPostRenderSettings`  
_L164-211_
- reflection: `USTRUCT(BlueprintType)`
- desc: Settings that dictate how media is played back after a render finishes.
- L168 _public prototype_ `FMovieGraphPostRenderSettings();`
- L175 _public member_ `TArray<FString> OutputTypePriorityOrder;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Render Output")` — When deciding which media to play, media with extensions ranked higher in this list will play instead of media ranked lower. For example, if EXR is listed above PNG, and both EXRs and PNGs were rendered, the EXRs will play instead of the PNGs.
- L185 _public member_ `EMovieGraphOutputTypePlayback OutputTypePlayback;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Render Output")` — If set to Use Priority Order, the Output Type Priority Order list will be used to determine which media to play (if there were multiple types of images and/or videos generated). If set to Play All Output Types, all media will be opened up in the player if possible. The media that is highest in the Output Type Priority Order will have its player used, and the other media will also be opened if it has been assigned this player as well (ie, two or more players will not be opened). If using the Operating System to open media, this setting is effectively ignored because only the highest-ranked media in Output Type Priority Order will be opened.
- L189 _public member_ `EMovieGraphDirectoryOpenBehavior DirectoryOpenBehavior;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Render Output")` — When opening a directory instead of playing back media, this dictates which directories will be opened.
- L193 _public member_ `FMovieGraphPostRenderImageSequencePlayOptions PostRenderImageSequencePlayOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Render Output", DisplayName = "Image Sequences")` — These options are used to determine how to play the rendered images.
- L197 _public member_ `FMovieGraphPostRenderVideoPlayOptions PostRenderAppleProResPlayOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Render Output", DisplayName = "Apple ProRes Movies")` — These options are used to determine how to play Apple ProRes movies.
- L201 _public member_ `FMovieGraphPostRenderVideoPlayOptions PostRenderAvidDNxHRPlayOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Render Output", DisplayName = "Avid DNxHR Movies")` — These options are used to determine how to play Avid DNxHR movies.
- L205 _public member_ `FMovieGraphPostRenderVideoPlayOptions PostRenderMP4PlayOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Render Output", DisplayName = "H.264 MP4 Movies")` — These options are used to determine how to play H.264 MP4 movies.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelinePrimaryConfig.h` (Public)


#### class `UMoviePipelinePrimaryConfig`  
`class UMoviePipelinePrimaryConfig : public UMoviePipelineConfigBase`  
_L31-96_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineConfigBase`
- desc: This class describes the main configuration for a Movie Render Pipeline. Only settings that apply to the entire output should be stored here, anything that is changed on a per-shot basis should be stored inside of UMovieRenderShotConfig instead. THIS CLASS SHOULD BE IMMUTABLE ONCE PASSED TO THE PIPELINE FOR PROCESSING. (Otherwise you will be modifying the instance that exists in the UI)
- L36 _public prototype_ `UMoviePipelinePrimaryConfig();`
- L39 _public prototype_ `TArray<UMoviePipelineOutputBase*> GetOutputContainers() const;`
- L42 _public prototype_ `virtual TArray<UMoviePipelineSetting*> GetUserSettings() const override;` — UMoviePipelineConfigBase interface
- L43 _public prototype_ `virtual void CopyFrom(UMoviePipelineConfigBase* InConfig) override;`
- L49 _public prototype_ `void InitializeTransientSettings();` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Initializes a single instance of every setting so that even non-user-configured settings have a chance to apply their default values. Does nothing if they're already instanced for this configuration.
- L52 _public function_ `TArray<UMoviePipelineSetting*> GetTransientSettings() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")`
- L55 _public prototype_ `TArray<UMoviePipelineSetting*> GetAllSettings(const bool bIncludeDisabledSettings = false, const bool bIncludeTransientSettings = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")`
- L59 _public prototype_ `UMoviePipelineShotConfig* GetConfigForShot(const FString& ShotName) const;` — Returns a pointer to the config specified for the shot, otherwise the default for this pipeline.
- L61 _public prototype_ `void GetFormatArguments(FMoviePipelineFormatArgs& InOutFormatArgs, const bool bIncludeAllSettings = false) const;`
- L69 _public prototype_ `FFrameRate GetEffectiveFrameRate(const ULevelSequence* InSequence) const;` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Returns the frame rate override from the Primary Configuration (if any) or the Sequence frame rate if no override is specified. This should be treated as the actual output framerate of the overall Pipeline.
- L71 _public prototype_ `TRange<FFrameNumber> GetEffectivePlaybackRange(const ULevelSequence* InSequence) const;`
- L74 _protected function_ `virtual bool CanSettingBeAdded(const UMoviePipelineSetting* InSetting) const override`
- L80 _protected prototype_ `virtual void OnSettingAdded(UMoviePipelineSetting* InSetting) override;`
- L81 _protected prototype_ `virtual void OnSettingRemoved(UMoviePipelineSetting* InSetting) override;`
- L83 _protected prototype_ `void AddTransientSettingByClass(const UClass* InSettingClass);`
- L87 _public member_ `TMap<FString, TObjectPtr<UMoviePipelineShotConfig>> PerShotConfigMapping;` — `UPROPERTY(Instanced)` — A mapping of Shot Name -> Shot Config to use for rendering specific shots with specific configs.
- L91 _private member_ `TObjectPtr<UMoviePipelineOutputSetting> OutputSetting;` — `UPROPERTY(Instanced)`
- L95 _private member_ `TArray<TObjectPtr<UMoviePipelineSetting>> TransientSettings;` — `UPROPERTY(Transient)` — An array of settings that are available in the engine and have not been edited by the user.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelinePythonHostExecutor.h` (Public)


#### class `UMoviePipelinePythonHostExecutor`  
`class UMoviePipelinePythonHostExecutor : public UMoviePipelineExecutorBase`  
_L19-65_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineExecutorBase`
- desc: This is a dummy executor that is designed to host a executor implemented in python. Python defined UClasses are not available when the executor is initialized and not all callbacks are available in Python. By inheriting from this in Python and overriding which UClass to latently spawn, this class can just forward certain events onto Python (by overriding the relevant function).
- L24 _public function_ `UMoviePipelinePythonHostExecutor() : UMoviePipelineExecutorBase()`
- L30 _public prototype_ `virtual void Execute_Implementation(UMoviePipelineQueue* InPipelineQueue) override;` — UMoviePipelineExecutorBase Interface
- L31 _public function_ `virtual bool IsRendering_Implementation() const override`
- L34 _public prototype_ `virtual void CancelAllJobs_Implementation() override;` — You should override this method to implement canceling jobs.
- L36 _public function_ `virtual void CancelCurrentJob_Implementation() override` — You only need to override this methond if your executor supports multiple queued jobs.
- L42 _public prototype_ `void ExecuteDelayed(UMoviePipelineQueue* InPipelineQueue);` — `UFUNCTION(BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Python/Blueprint API
- L43 _public function_ `virtual void ExecuteDelayed_Implementation(UMoviePipelineQueue* InPipelineQueue)`
- L46 _public prototype_ `void OnMapLoad(UWorld* InWorld);` — `UFUNCTION(BlueprintNativeEvent, Category = "Movie Render Pipeline")`
- L47 _public function_ `virtual void OnMapLoad_Implementation(UWorld* InWorld)`
- L51 _public function_ `UWorld* GetLastLoadedWorld() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L53 _private prototype_ `void OnMapLoadFinished(UWorld* NewWorld);`
- L58 _public member_ `TSubclassOf<UMoviePipelinePythonHostExecutor> ExecutorClass;` — `UPROPERTY(BlueprintReadWrite, Category = "Movie Render Pipeline")` — You should override this class type on the CDO of the object with your Python type when Python is initialized.
- L61 _public member_ `TObjectPtr<UMoviePipelineQueue> PipelineQueue;` — `UPROPERTY(BlueprintReadWrite, Transient, Category = "Movie Render Pipeline")`
- L64 _private member_ `TObjectPtr<UWorld> LastLoadedWorld;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineQueue.h` (Public)


#### struct `FMoviePipelineSidecarCamera`  
`struct FMoviePipelineSidecarCamera`  
_L23-41_
- reflection: `USTRUCT(BlueprintType)`
- L28 _public member_ `FGuid BindingId;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Render Pipeline")`
- L37 _public member_ `FMovieSceneSequenceID SequenceId;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Render Pipeline")` — FMovieSceneSequenceID isn't exposed to Blueprints and we need the full support of a FMovieSceneSequenceID so we can't just store a USequence* like the scripting layer does - we need to be able to handle the same sequence being in a sequence multiple times (which scripting does not). This data structure gets regenerated each time a render starts, so the property should be valid when we want to use it, even if it's not exposed to scripting.
- L40 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Render Pipeline")`

#### class `UMoviePipelineQueueProjectSettings`  
`class UMoviePipelineQueueProjectSettings : public UObject`  
_L47-60_
- reflection: `UCLASS(MinimalAPI, Config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Project-based settings for the queue.
- L53 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L59 _public member_ `EMoviePipelinePostRenderActionType PostRenderActionType = EMoviePipelinePostRenderActionType::DoNothing;` — `UPROPERTY(Config, BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — When a queue finishes rendering, this determines the action that should be taken (if any).

#### enum `EMoviePipelineConfigMode`  
`enum class EMoviePipelineConfigMode : uint8`  
_L64-74_
- reflection: `UENUM(BlueprintType)`
- desc: The active configuration mode for a Movie Render Queue job.
- L67 _public enumerator_ `Preset` — Legacy UMoviePipelinePrimaryConfig preset.
- L70 _public enumerator_ `Graph` — Graph-based UMovieGraphConfig configuration.
- L73 _public enumerator_ `Basic` — Simplified UMoviePipelineBasicConfig configuration.

#### class `UMoviePipelineExecutorShot`  
`class UMoviePipelineExecutorShot : public UObject`  
_L83-354_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: This class represents a segment of work within the Executor Job. This should be owned by the UMoviePipelineExecutorJob and can be created before the movie pipeline starts to configure some aspects about the segment (such as disabling it). When the movie pipeline starts, it will use the already existing ones, or generate new ones as needed.
- L87 _public function_ `UMoviePipelineExecutorShot() : bEnabled(true)`
- L107 _public prototype_ `void SetStatusMessage(const FString& InStatus);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Set the status of this shot to the given value. This will be shown on the UI if progress is set to a value less than zero. If progress is > 0 then the progress bar will be shown on the UI instead. Progress and Status Message are cosmetic. For C++ implementations override `virtual void SetStatusMessage_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def set_status_message(self, inStatus): @param InStatus	The status message you wish the executor to have.
- L119 _public prototype_ `FString GetStatusMessage() const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Get the current status message for this shot. May be an empty string. For C++ implementations override `virtual FString GetStatusMessage_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def get_status_message(self): return ?
- L136 _public prototype_ `void SetStatusProgress(const float InProgress);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Set the progress of this shot to the given value. If a positive value is provided the UI will show the progress bar, while a negative value will make the UI show the status message instead. Progress and Status Message are cosmetic and dependent on the executor to update. Similar to the UMoviePipelineExecutor::SetStatusProgress function, but at a per-job level basis instead. For C++ implementations override `virtual void SetStatusProgress_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def set_status_progress(self, inStatus): @param InProgress	The progress (0-1 range) the executor should have.
- L148 _public prototype_ `float GetStatusProgress() const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Get the current progress as last set by SetStatusProgress. 0 by default. For C++ implementations override `virtual float GetStatusProgress_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def get_status_progress(self): return ?
- L151 _public prototype_ `UMoviePipelineShotConfig* AllocateNewShotOverrideConfig(TSubclassOf<UMoviePipelineShotConfig> InConfigType);` — `UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InConfigType"), Category = "Movie Render Pipeline", meta=(InConfigType="/Script/MovieRenderPipelineCore.MoviePipelineShotConfig"))`
- L154 _public prototype_ `void SetShotOverrideConfiguration(UMoviePipelineShotConfig* InPreset);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")`
- L157 _public prototype_ `void SetShotOverridePresetOrigin(UMoviePipelineShotConfig* InPreset);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")`
- L160 _public function_ `UMoviePipelineShotConfig* GetShotOverrideConfiguration() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L166 _public function_ `UMoviePipelineShotConfig* GetShotOverridePresetOrigin() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L175 _public prototype_ `bool IsUsingGraphConfiguration() const;` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns true if this job is using graph-style configuration, else false.
- L183 _public function_ `UMovieGraphConfig* GetGraphPreset() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Gets the graph-style preset that this shot is using. A non-null graph config does not imply the graph config is the config that's in use; reference GetConfigMode() on the job for the config type that's active.
- L196 _public prototype_ `void SetGraphPreset(const UMovieGraphConfig* InGraphPreset, const bool bUpdateVariableAssignments = true);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Sets the graph-style preset that this job will use. Note that this will cause the graph to switch over to using graph-style configuration if it is not already using it. @param InGraphPreset - The graph preset to assign to the shot. @param bUpdateVariableAssignments - Set to false if variable assignments should NOT be automatically updated to reflect the graph preset being used. This is normally not what you want and should be used with caution.
- L220 _public prototype_ `UMovieJobVariableAssignmentContainer* GetOrCreateJobVariableAssignmentsForGraph(const UMovieGraphConfig* InGraph, const bool bIsForPrimaryOverrides = false);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline", DisplayName = "Get or Create Variable Overrides", meta = (ScriptName = "GetOrCreateVariableOverrides"))` — This method will return you the object which contains variable overrides for either the Job's Primary or the Shot's GraphPreset. UMoviePipelineExecutorShot has two separate sets of overrides. You can use the shot to override a variable on the Primary Graph (ie: the one assigned to the whole job), but a graph can also have an entirely separate UMovieGraph config asset to run (though at runtime some variables will only be read from the Primary Graph, ie: Custom Frame Range due to it applying to the entire sequence). If you specify true for bIsForPrimaryOverrides it returns an object that allows this shot to override a variable that comes from the primary graph. If you return false, then it returns an object that allows overriding a variable for this shot's override config (see: GetGraphPreset). See UMoviePipelineExecutorJob's version of this function for more details. @param InGraph - The graph asset to return the config for. If this shot has its own Graph Preset override, you should return GetGraphPreset() or one of it's sub-graph pointers. If this shot is just trying to override the Primary Graph from the parent UMoviePipelineExecutorJob then you should return a pointer to the Job's GetGraphPreset() (or one of it's sub-graphs). Each graph/sub-graph gets its own set of overrides since sub-graphs can have different variables than the parents, so you have to provide the pointer to the one you want to override variables for. @param bIsForPrimaryOverride - Default false. If true, 
- L224 _public prototype_ `bool IsUsingBasicConfiguration() const;` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns true if the parent job is using basic configuration mode.
- L232 _public function_ `UMoviePipelineBasicConfig* GetBasicShotConfig() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Gets the basic shot config overrides. Returns nullptr if no shot overrides are set. A non-null Basic config override does not imply the Basic config is the config that's in use; reference the job's GetConfigMode() for the config type that's active.
- L236 _public prototype_ `UMoviePipelineBasicConfig* SetupBasicShotOverrides();` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Creates and returns basic shot overrides for this shot.
- L240 _public prototype_ `bool CanUseConsoleVariableOverrides() const;` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns true if console variable overrides can be used in the active configuration.
- L244 _public function_ `bool ShouldRender() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns whether this should be rendered.
- L250 _public function_ `FString GetCameraName(int32 InCameraIndex) const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")`
- L260 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;` — UObject Interface
- L261 _public prototype_ `virtual void PostLoad() override;`
- L262 _public prototype_ `virtual void BeginDestroy() override;`
- L272 _public prototype_ `TArray<TObjectPtr<UMovieJobVariableAssignmentContainer>>& GetGraphVariableAssignments(const bool bUpdateAssignments = true);` — Gets overrides on the variables in graph presets associated with this job. A job can have multiple graphs associated with it if the job's assigned graph contains subgraphs. The job's graph and each subgraph will have an entry in the returned array. The assignments are updated before they are returned. To opt-out of this, set bUpdateAssignments to false (generally not recommended unless there is very specific behavior that is needed).
- L280 _public prototype_ `TArray<TObjectPtr<UMovieJobVariableAssignmentContainer>>& GetPrimaryGraphVariableAssignments(const bool bUpdateAssignments = true);` — Gets overrides on the variables in the primary graph (and its subgraphs) associated with this job. The assignments are updated before they are returned. To opt-out of this, set bUpdateAssignments to false (generally not recommended unless there is very specific behavior that is needed).
- L283 _public prototype_ `void RefreshAllVariableAssignments();` — Refreshes the variable assignments associated with this shot, both for the shot's own graph preset and the associated primary graph.
- L287 _protected function_ `virtual void SetStatusMessage_Implementation(const FString& InMessage)` — UMoviePipipelineExecutorShot Interface
- L288 _protected function_ `virtual void SetStatusProgress_Implementation(const float InProgress)`
- L289 _protected function_ `virtual FString GetStatusMessage_Implementation() const`
- L290 _protected function_ `virtual float GetStatusProgress_Implementation() const`
- L293 _protected prototype_ `void OnGraphPreSave(UObject* InObject, FObjectPreSaveContext InObjectPreSaveContext);`
- L299 _public member_ `bool bEnabled;` — `UPROPERTY(BlueprintReadWrite, Category = "Movie Render Pipeline")` — Does the user want to render this shot?
- L303 _public member_ `FString OuterName;` — `UPROPERTY(BlueprintReadWrite, Category = "Movie Render Pipeline")` — The name of the shot section that contains this shot. Can be empty.
- L307 _public member_ `FString InnerName;` — `UPROPERTY(BlueprintReadWrite, Category = "Movie Render Pipeline")` — The name of the camera cut section that this shot represents. Can be empty.
- L311 _public member_ `TArray<FMoviePipelineSidecarCamera> SidecarCameras;` — `UPROPERTY(BlueprintReadWrite, Category = "Movie Render Pipeline")` — List of cameras to render for this shot. Only used if the setting flag is set in the Camera setting.
- L314 _public member_ `FOnMoviePipelineShotGraphPresetChanged OnShotGraphPresetChanged;` — Called when the graph preset assigned to the shot changes.
- L320 _public member_ `TArray<FMoviePipelineConsoleVariableEntry> ConsoleVariableOverrides;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Console Variable Overrides", meta = (DisplayName = "Console Variables", EditCondition="CanUseConsoleVariableOverrides()", EditConditionHides))` — (Optional) Console variable overrides which are applied after cvars set via nodes. Applies to graph-based and Basic configurations.
- L324 _public member_ `FMoviePipelineCameraCutInfo ShotInfo;` — Transient information used by the active Movie Pipeline working on this shot.
- L328 _protected member_ `float Progress;` — `UPROPERTY(Transient)`
- L330 _protected member_ `FString StatusMessage;` — `UPROPERTY(Transient)`
- L334 _private member_ `TObjectPtr<UMoviePipelineShotConfig> ShotOverrideConfig;` — `UPROPERTY()`
- L337 _private member_ `TSoftObjectPtr<UMoviePipelineShotConfig> ShotOverridePresetOrigin;` — `UPROPERTY()`
- L341 _private member_ `TSoftObjectPtr<UMovieGraphConfig> GraphPreset;` — `UPROPERTY()` — The graph-based configuration preset that this shot is using. Can be nullptr.
- L345 _private member_ `TArray<TObjectPtr<UMovieJobVariableAssignmentContainer>> GraphVariableAssignments;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Variable Assignments")` — Overrides on the variables in the graph (and subgraphs) associated with this job.
- L349 _private member_ `TArray<TObjectPtr<UMovieJobVariableAssignmentContainer>> PrimaryGraphVariableAssignments;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Variable Assignments")` — Overrides on the variables in the primary graph (and its subgraphs) associated with this job.
- L353 _private member_ `TObjectPtr<UMoviePipelineBasicConfig> BasicShotConfig;` — `UPROPERTY(Instanced)` — The basic configuration overrides for this shot. Non-null indicates shot-level overrides in Basic configuration mode.

#### class `UMoviePipelineExecutorJob`  
`class UMoviePipelineExecutorJob : public UObject`  
_L363-782_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A particular job within the Queue
- L367 _public function_ `UMoviePipelineExecutorJob()`
- L391 _public prototype_ `void SetStatusMessage(const FString& InStatus);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Set the status of this job to the given value. This will be shown on the UI if progress is set to a value less than zero. If progress is > 0 then the progress bar will be shown on the UI instead. Progress and Status Message are cosmetic and dependent on the executor to update. Similar to the UMoviePipelineExecutor::SetStatusMessage function, but at a per-job level basis instead. For C++ implementations override `virtual void SetStatusMessage_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def set_status_message(self, inStatus): @param InStatus	The status message you wish the executor to have.
- L403 _public prototype_ `FString GetStatusMessage() const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Get the current status message for this job. May be an empty string. For C++ implementations override `virtual FString GetStatusMessage_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def get_status_message(self): return ?
- L420 _public prototype_ `void SetStatusProgress(const float InProgress);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Set the progress of this job to the given value. If a positive value is provided the UI will show the progress bar, while a negative value will make the UI show the status message instead. Progress and Status Message are cosmetic and dependent on the executor to update. Similar to the UMoviePipelineExecutor::SetStatusProgress function, but at a per-job level basis instead. For C++ implementations override `virtual void SetStatusProgress_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def set_status_progress(self, inProgress): @param InProgress	The progress (0-1 range) the executor should have.
- L432 _public prototype_ `float GetStatusProgress() const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Get the current progress as last set by SetStatusProgress. 0 by default. For C++ implementations override `virtual float GetStatusProgress_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def get_status_progress(self): return ?
- L450 _public prototype_ `void SetConsumed(const bool bInConsumed);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Set the job to be consumed. A consumed job is disabled in the UI and should not be submitted for rendering again. This allows jobs to be added to a queue, the queue submitted to a remote farm (consume the jobs) and then more jobs to be added and the second submission to the farm won't re-submit the already in-progress jobs. Jobs can be unconsumed when the render finishes to re-enable editing. For C++ implementations override `virtual void SetConsumed_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def set_consumed(self, isConsumed): @param bInConsumed	True if the job should be consumed and disabled for editing in the UI.
- L464 _public prototype_ `bool IsConsumed() const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Gets whether or not the job has been marked as being consumed. A consumed job is not editable in the UI and should not be submitted for rendering as it is either already finished or already in progress. For C++ implementations override `virtual bool IsConsumed_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def is_consumed(self): return ?
- L478 _public prototype_ `void SetIsEnabled(const bool bInEnabled);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Set the job to be enabled/disabled. This is exposed to the user in the Queue UI so they can disable a job after loading a queue to skip trying to run it. For C++ implementations override `virtual void SetIsEnabled_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def set_is_enabled(self, isEnabled): @param bInEnabled	True if the job should be enabled and rendered.
- L490 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Gets whether or not the job has been marked as being enabled. For C++ implementations override `virtual bool IsEnabled_Implementation() const override` For Python/BP implementations override @unreal.ufunction(override=True) def is_enabled(self): return ?
- L502 _public prototype_ `void OnDuplicated();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movie Render Pipeline")` — Should be called to clear status and user data after duplication so that jobs stay unique and don't pick up ids or other unwanted behavior from the pareant job. For C++ implementations override `virtual bool OnDuplicated_Implementation() override` For Python/BP implementations override @unreal.ufunction(override=True) def on_duplicated(self):
- L505 _public prototype_ `void SetPresetOrigin(UMoviePipelinePrimaryConfig* InPreset);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")`
- L513 _public function_ `UMoviePipelinePrimaryConfig* GetPresetOrigin() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Gets the preset for this job, but only if the preset has not been modified. If it has been modified, or the preset no longer exists, returns nullptr. @see GetConfiguration()
- L529 _public function_ `UMoviePipelinePrimaryConfig* GetConfiguration() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Gets the configuration for the job. This configuration is either standalone (not associated with any preset), or contains a copy of the preset origin plus any modifications made on top of it. If the preset that this configuration was originally based on no longer exists, this configuration will still be valid. Note that a non-null configuration does not imply that this Preset is the active configuration; reference GetConfigMode() for the config type that's active. @see GetPresetOrigin()
- L535 _public prototype_ `void SetConfiguration(UMoviePipelinePrimaryConfig* InPreset);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")`
- L539 _public function_ `EMoviePipelineConfigMode GetConfigMode() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns the active configuration mode for this job.
- L548 _public prototype_ `bool SetConfigMode(EMoviePipelineConfigMode InConfigMode);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Switches the active configuration mode on the job. For Basic mode, lazily initializes the BasicConfig if it doesn't exist yet. For Graph mode, requires a graph preset to already be assigned (returns false otherwise). See SetGraphPreset(). @return true if the mode was switched (or was already the requested mode), false if the switch was not possible.
- L554 _public function_ `bool IsUsingGraphConfiguration() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns true if this job is using graph-style configuration, else false.
- L558 _public function_ `bool IsUsingBasicConfiguration() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns true if this job is using basic configuration mode.
- L566 _public function_ `UMoviePipelineBasicConfig* GetBasicConfig() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Gets the basic configuration object, or nullptr if basic configuration has not been set up. A non-null Basic config does not imply the Basic config is the config that's in use; reference GetConfigMode() for the config type that's active.
- L573 _public prototype_ `UMoviePipelineBasicConfig* SetupBasicConfiguration();` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Sets up basic configuration mode for this job. Note that this will cause the job to switch over to using the Basic configuration. Returns the created basic config object.
- L577 _public prototype_ `bool CanUseConsoleVariableOverrides() const;` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns true if console variable overrides can be used in the active configuration.
- L584 _public function_ `bool HasInitializedLegacyDefaults() const` — Returns true if this job's legacy preset config has been seeded with the project's default settings. Typically used to gate one-time defaults seeding when switching into Preset mode, so settings the user has deliberately removed aren't re-added on subsequent mode switches.
- L593 _public function_ `void MarkLegacyPresetDefaultsAsInitialized()` — Marks this job's legacy preset config as having been seeded with the project's default settings, which disables the one-time defaults seeding that would otherwise run on the next Basic/Graph -> Preset switch. Typically only called by EnsureJobHasDefaultSettings (which manages the flag as part of its idempotency gate), but may be useful in niche cases where external code manages the configuration lifecycle directly and needs to coordinate with that gate.
- L601 _public function_ `UMovieGraphConfig* GetGraphPreset() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Gets the graph-style preset assigned to this job. A non-null graph config does not imply the graph config is the config that's in use; reference GetConfigMode() for the config type that's active.
- L614 _public prototype_ `void SetGraphPreset(const UMovieGraphConfig* InGraphPreset, const bool bUpdateVariableAssignments = true);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Sets the graph-style preset that this job will use. Note that this will cause the graph to switch over to using graph-style configuration if it is not already using it. @param InGraphPreset - The graph preset to assign to the job. @param bUpdateVariableAssignments - Set to false if variable assignments should NOT be automatically updated to reflect the graph preset being used. This is normally not what you want and should be used with caution.
- L617 _public prototype_ `void SetSequence(FSoftObjectPath InSequence);` — `UFUNCTION(BlueprintSetter, Category = "Movie Render Pipeline")`
- L619 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSequenceSet, UMoviePipelineExecutorJob* Job, ULevelSequence* Sequence);`
- L622 _public prototype_ `static FOnSequenceSet& OnSequenceSetEvent();` — Retrieve multicast delegate for when a sequence is set.
- L639 _public prototype_ `UMovieJobVariableAssignmentContainer* GetOrCreateJobVariableAssignmentsForGraph(const UMovieGraphConfig* InGraph);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline", DisplayName = "Get or Create Variable Overrides", meta=(ScriptName ="GetOrCreateVariableOverrides"))` — This method will return you the object which contains variable overrides for the Primary Graph assigned to this job. You need to provide a pointer to the exact graph you want (as the Primary Graph may contain sub-graphs, and those sub-graphs can have their own variables), though this will be the same as GetGraphPreset() if you're not using any sub-graphs, or your variables only exist on the Primary graph. If you want to override a variable on the primary graph but only for a specific shot, you should get the UMoviePipelineExecutorShot and call that classes version of this function, except passing True for the extra boolean.  See comment on that function for more details. @param InGraph - The graph asset to get the Job Override values for. Should be the graph the variables you want to edit are defined on, which can either be the primary graph (GetGraphPreset()) or one of the sub-graphs it points to (as sub-graphs can contain their own variables which are all shown at the top level job in the Editor UI). @return A container object which holds a copy of the variables for the specified Graph Asset that can be used to override their values on jobs without actually editing the default asset.
- L643 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Interface
- L645 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);`
- L647 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L648 _public prototype_ `virtual void PostLoad() override;`
- L649 _public prototype_ `virtual void BeginDestroy() override;`
- L659 _public prototype_ `TArray<TObjectPtr<UMovieJobVariableAssignmentContainer>>& GetGraphVariableAssignments(const bool bUpdateAssignments = true);` — Gets overrides on the variables in graph presets associated with this job. A job can have multiple graphs associated with it if the job's assigned graph contains subgraphs. The job's graph and each subgraph will have an entry in the returned array. The assignments are updated before they are returned. To opt-out of this, set bUpdateAssignments to false (generally not recommended unless there is very specific behavior that is needed).
- L662 _public prototype_ `void RefreshAllVariableAssignments();` — Refreshes the variable assignments associated with this job, both for the jobs's own graph preset and the associated shot graphs.
- L666 _protected function_ `virtual void SetStatusMessage_Implementation(const FString& InMessage)` — UMoviePipelineExecutorJob Interface
- L667 _protected function_ `virtual void SetStatusProgress_Implementation(const float InProgress)`
- L668 _protected function_ `virtual void SetConsumed_Implementation(const bool bInConsumed)`
- L669 _protected function_ `virtual FString GetStatusMessage_Implementation() const`
- L670 _protected function_ `virtual float GetStatusProgress_Implementation() const`
- L671 _protected function_ `virtual bool IsConsumed_Implementation() const`
- L672 _protected prototype_ `virtual void OnDuplicated_Implementation();`
- L673 _protected function_ `virtual void SetIsEnabled_Implementation(const bool bInEnabled)`
- L680 _protected function_ `virtual bool IsEnabled_Implementation() const`
- L683 _protected prototype_ `void OnGraphPreSave(UObject* InObject, FObjectPreSaveContext InObjectPreSaveContext);`
- L688 _public member_ `FString JobName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — (Optional) Name of the job. Shown on the default burn-in.
- L692 _public member_ `FSoftObjectPath Sequence;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintSetter = "SetSequence", Category = "Movie Render Pipeline", meta = (AllowedClasses = "/Script/LevelSequence.LevelSequence", DisplayThumbnail = false))` — Which sequence should this job render?
- L696 _public member_ `FSoftObjectPath Map;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline", meta = (AllowedClasses = "/Script/Engine.World", DisplayThumbnail = false))` — Which map should this job render on
- L700 _public member_ `FString Author;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — (Optional) If left blank, will default to system username. Can be shown in burn in as a first point of contact about the content.
- L704 _public member_ `FString Comment;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline", meta = (MultiLine = true))` — (Optional) If specified, will be shown in the burn in to allow users to keep track of notes about a render.
- L708 _public member_ `TArray<TObjectPtr<UMoviePipelineExecutorShot>> ShotInfo;` — `UPROPERTY(BlueprintReadWrite, Instanced, Category = "Movie Render Pipeline")` — (Optional) Shot specific information. If a shot is missing from this list it will assume to be enabled and will be rendered.
- L716 _public member_ `FString UserData;` — `UPROPERTY(BlueprintReadWrite, Category = "Movie Render Pipeline")` — Arbitrary data that can be associated with the job. Not used by default implementations, nor read. This can be used to attach third party metadata such as job ids from remote farms. Not shown in the user interface.
- L719 _public member_ `FOnMoviePipelineJobGraphPresetChanged OnJobGraphPresetChanged;` — Called when the graph preset assigned to the job changes.
- L722 _public member_ `FOnMoviePipelineJobConfigModeChanged OnJobConfigModeChanged;` — Called when the job's configuration mode changes (Basic, Graph, Preset).
- L728 _public member_ `TArray<FMoviePipelineConsoleVariableEntry> ConsoleVariableOverrides;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Console Variable Overrides", meta = (DisplayName = "Console Variables", EditCondition="CanUseConsoleVariableOverrides()", EditConditionHides))` — (Optional) Console variable overrides which are applied after cvars set via nodes. Applies to graph-based and Basic configurations.
- L732 _private member_ `FString StatusMessage;` — `UPROPERTY(Transient)`
- L735 _private member_ `float StatusProgress;` — `UPROPERTY(Transient)`
- L738 _private member_ `bool bIsConsumed;` — `UPROPERTY(Transient)`
- L743 _private member_ `TObjectPtr<UMoviePipelinePrimaryConfig> Configuration;` — `UPROPERTY(Instanced)`
- L748 _private member_ `TSoftObjectPtr<UMoviePipelinePrimaryConfig> PresetOrigin;` — `UPROPERTY()`
- L752 _private member_ `bool bEnabled;` — `UPROPERTY()` — Whether this job is enabled and should be rendered.
- L760 _private member_ `TSoftObjectPtr<UMovieGraphConfig> GraphPreset;` — `UPROPERTY()` — The graph-based configuration preset that this job is using. Can be nullptr. Typically, this should be set with SetGraphPreset() in order to keep the ConfigMode in sync. May be non-null even when not in Graph mode (it's preserved across mode switches). Check ConfigMode to determine the active configuration.
- L764 _private member_ `TArray<TObjectPtr<UMovieJobVariableAssignmentContainer>> GraphVariableAssignments;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Variable Assignments")` — Overrides on the variables in the graph (and subgraphs) associated with this job.
- L768 _private member_ `TObjectPtr<UMoviePipelineBasicConfig> BasicConfig;` — `UPROPERTY(Instanced)` — The basic configuration for this job. May be non-null even when not in Basic mode (preserved across mode switches).
- L772 _private member_ `EMoviePipelineConfigMode ConfigMode = EMoviePipelineConfigMode::Preset;` — `UPROPERTY()` — The active configuration mode for this job. Determines which config object is in use.
- L781 _private member_ `bool bHasInitializedLegacyPresetDefaults = false;` — `UPROPERTY()` — Tracks whether defaults have been applied to this job's legacy configuration. Set when the defaults are seeded at creation, or on first Basic/Graph -> Preset switch. Prevents re-adding settings the user has removed on subsequent mode switches. By convention this is written via MarkLegacyPresetDefaultsAsInitialized().

#### class `UMoviePipelineQueue`  
`class UMoviePipelineQueue : public UObject`  
_L789-916_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A queue is a list of jobs that have been executed, are executing and are waiting to be executed. These can be saved to specific assets to allow
- L794 _public prototype_ `UMoviePipelineQueue();`
- L804 _public prototype_ `UMoviePipelineExecutorJob* AllocateNewJob(TSubclassOf<UMoviePipelineExecutorJob> InJobType);` — `UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InClass"), Category = "Movie Render Pipeline|Queue", meta=(InJobType="/Script/MovieRenderPipelineCore.MoviePipelineExecutorJob"))` — Allocates a new Job in this Queue. The Queue owns the jobs for memory management purposes, and this will handle that for you. @param InJobType	Specify the specific Job type that should be created. Custom Executors can use custom Job types to allow the user to provide more information. @return	The created Executor job instance.
- L812 _public prototype_ `void DeleteJob(UMoviePipelineExecutorJob* InJob);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Queue")` — Deletes the specified job from the Queue. @param InJob	The job to look for and delete.
- L818 _public prototype_ `void DeleteAllJobs();` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Queue", meta = (Keywords = "Clear Empty"))` — Delete all jobs from the Queue.
- L827 _public prototype_ `UMoviePipelineExecutorJob* DuplicateJob(UMoviePipelineExecutorJob* InJob);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Queue")` — Duplicate the specific job and return the duplicate. Configurations are duplicated and not shared. @param InJob	The job to look for to duplicate. @return The duplicated instance or nullptr if a duplicate could not be made.
- L834 _public function_ `TArray<UMoviePipelineExecutorJob*> GetJobs() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline|Queue")` — Get all of the Jobs contained in this Queue. @return The jobs contained by this queue.
- L844 _public function_ `UMoviePipelineQueue* GetQueueOrigin() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Queue")` — Gets the queue that this queue was originally based on (if any). The origin will only be set on transient queues; the origin will be nullptr for non-transient queues because the origin will be this object.
- L850 _public function_ `void SetQueueOrigin(UMoviePipelineQueue* InConfig)` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Queue")` — Sets the queue that this queue originated from (if any). The origin should only be set for transient queues.
- L857 _public prototype_ `UMoviePipelineQueue* CopyFrom(UMoviePipelineQueue* InQueue);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Queue")` — Replace the contents of this queue with a copy of the contents from another queue. Returns a pointer to this queue if the copy was successful, else nullptr.
- L861 _public prototype_ `void SetJobIndex(UMoviePipelineExecutorJob* InJob, int32 Index);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Queue")` — Set the index of the given job
- L868 _public function_ `bool IsDirty() const` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Queue")` — Gets the dirty state of this queue. Note that dirty state is only tracked when the editor is active.
- L876 _public function_ `void SetIsDirty(const bool bNewDirtyState)` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Queue")` — Sets the dirty state of this queue. Generally the queue will correctly track the dirty state; however, there are situations where a queue may need its dirty state reset (eg, it may be appropriate to reset the dirty state after a call to CopyFrom(), depending on the use case).
- L883 _public function_ `uint32 GetQueueSerialNumber() const` — Retrieve the serial number that is incremented when a job is added or removed from this list. @note: This field is not serialized, and not copied along with UObject duplication.
- L888 _public function_ `void InvalidateSerialNumber()`
- L894 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;` — UObject Interface
- L899 _private prototype_ `void OnAnyObjectModified(UObject* InModifiedObject);`
- L904 _private member_ `TArray<TObjectPtr<UMoviePipelineExecutorJob>> Jobs;` — `UPROPERTY(Instanced)`
- L908 _private member_ `TSoftObjectPtr<UMoviePipelineQueue> QueueOrigin;` — `UPROPERTY()` — The queue that this queue originated from. Helpful for determining the source of the queue when this queue is transient.
- L911 _private member_ `int32 QueueSerialNumber;`
- L915 _private member_ `bool bIsDirty;` — Dirty state is tracked explicitly so transient queues, which are based on a transient package, know when modifications have been made.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineShotGraphPresetChanged, UMoviePipelineExecutorShot*, UMovieGraphConfig*);`
- L43 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineShotGraphPresetChanged, UMoviePipelineExecutorShot*, UMovieGraphConfig*);`
- L356 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineJobGraphPresetChanged, UMoviePipelineExecutorJob*, UMovieGraphConfig*);`
- L356 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineJobGraphPresetChanged, UMoviePipelineExecutorJob*, UMovieGraphConfig*);`
- L357 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineJobConfigModeChanged, UMoviePipelineExecutorJob*, EMoviePipelineConfigMode);`
- L357 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineJobConfigModeChanged, UMoviePipelineExecutorJob*, EMoviePipelineConfigMode);`
- L619 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSequenceSet, UMoviePipelineExecutorJob* Job, ULevelSequence* Sequence);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineQueueEngineSubsystem.h` (Public)


#### class `UMoviePipelineQueueEngineSubsystem`  
`class UMoviePipelineQueueEngineSubsystem : public UEngineSubsystem`  
_L24-159_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta=(DisplayName="MoviePipeline Runtime Subsystem"))`
- inherits: `UEngineSubsystem`
- desc: This subsystem is intended for use when rendering in a shipping game (but can also be used in PIE during development/testing). See UMoviePipelineQueueSubsystem for the Editor-only queue which is bound to the Movie Render Queue UI. To do simple renders at runtime, call AllocateJob(...) with the Level Sequence you want to render, then call FindOrAddSettingByClass on the job to add the settings (such as render pass, output type, and output directory) that you want for the job. Finally, call RenderJob with the job you just configured. Register a delegate to OnRenderFinished to be notified when the render finished. You can optionally call SetConfiguration(...) before RenderJob to configure some advanced options.
- L30 _public function_ `UMoviePipelineQueueEngineSubsystem()`
- L39 _public function_ `UMoviePipelineQueue* GetQueue() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns the queue of Movie Pipelines that need to be rendered.
- L46 _public function_ `UMoviePipelineExecutorBase* GetActiveExecutor() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns the active executor (if there is one). This can be used to subscribe to events on an already in-progress render. May be null.
- L61 _public prototype_ `UMoviePipelineExecutorBase* RenderQueueWithExecutor(TSubclassOf<UMoviePipelineExecutorBase> InExecutorType);` — `UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InExecutorType"), Category = "Movie Render Pipeline|Rendering")` — Starts processing the current queue with the supplied executor class. This starts an async process which may or may not run in a separate process (or on separate machines), determined by the executor implementation. The executor should report progress for jobs depending on the implementation. @param InExecutorType	A subclass of UMoviePipelineExecutorBase. An instance of this class is created and started. @return A pointer to the instance of the class created. This instance will be kept alive by the Queue Subsystem until it has finished (or been canceled). Register for progress reports and various callbacks on this instance.
- L71 _public prototype_ `void RenderQueueWithExecutorInstance(UMoviePipelineExecutorBase* InExecutor);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Rendering")` — Starts processing the current queue with the supplied executor. This starts an async process which may or may not run in a separate process (or on separate machines), determined by the executor implementation. The executor should report progress for jobs depending on the implementation. @param InExecutor	Instance of a subclass of UMoviePipelineExecutorBase.
- L79 _public function_ `bool IsRendering() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline|Rendering")` — Returns true if there is an active executor working on producing a movie. This could be actively rendering frames, or working on post processing (finalizing file writes, etc.). Use GetActiveExecutor() and query it directly for more information, progress updates, etc.
- L99 _public prototype_ `void SetConfiguration(TSubclassOf<UMovieRenderDebugWidget> InProgressWidgetClass = {}, const bool bRenderPlayerViewport = false);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Rendering")` — Sets some advanced configuration options that are used only occasionally to have better control over integrating it into your game/application. This applies to both RenderQueueWithExecutor(Instance) and the simplified RenderJob API. This persists until you call it again with different settings, and needs to be called before the Render* functions. @param ProgressWidget 		- Create a User Widget that inherits from UMovieRenderDebugWidget and it will be created. Passing nullptr will use the default widget, if you wish to hide the widget then create a new widget which inherits from UMovieRenderDebugWidget and put nothing in it. @param bRenderPlayerViewport  - If true, we will render the regular player viewport in addition to the off-screen MRQ render. This is significantly performance heavy (doubles render times) but can be useful in the event that you want to keep rendering the player viewport to better integrate the render into your own application.
- L115 _public prototype_ `UMoviePipelineExecutorJob* AllocateJob(ULevelSequence* InSequence);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Rendering")` — Convenience function for creating a UMoviePipelineExecutorJob out of the given Level Sequence asset. The newly created job will be initialized to render on the current level, and will not have any default settings added to it - instead you will need to call FindOrAddSettingByClass on the job's configuration to add settings such as render passes (UMoviePipelineDeferredPassBase), output types (UMoviePipelineImageSequenceOutput_PNG), and configure the output directory (UMoviePipelineOutputSetting). Once configuration is complete, register a delegate to OnRenderFinished and then call RenderJob. Calling this function will clear the internal queue, see RenderJob for more details. Using this function while IsRendering() returns true will result in an exception being thrown and no attempt being made to create the job.
- L129 _public prototype_ `void RenderJob(UMoviePipelineExecutorJob* InJob);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Rendering")` — Convenience function for rendering the specified job. Calling this will render the specified job (if it was allocated using AllocateJob) and then it will reset the queue once finished. If you need to render multiple jobs (in a queue) then you need to either implement the queue behavior yourself, or use GetQueue()->AllocateJob(...) instead and use the non-convenience functions. Calling this function will clear the queue (after completion). Using this function while IsRendering() returns true will result in an exception being thrown and no attempt being made to render the job.
- L141 _public member_ `FMoviePipelineWorkFinished OnRenderFinished;` — `UPROPERTY(BlueprintAssignable)` — Assign a function to this delegate to get notified when each individual job is finished. THIS WILL ONLY BE CALLED IF USING THE RENDERJOB CONVENIENCE FUNCTION. Because there can only be one job in the queue when using RenderJob, this will be called when the render is complete, and the executor has been released. This allows you to queue up another job immediately as a result of the OnRenderFinished callback.
- L146 _private prototype_ `void OnExecutorFinished(UMoviePipelineExecutorBase* InPipelineExecutor, bool bSuccess);` — Called when the executor is finished so that we can release it and stop reporting IsRendering() == true.
- L147 _private prototype_ `void OnIndividualJobFinished(FMoviePipelineOutputData Results);`
- L151 _private member_ `TObjectPtr<UMoviePipelineExecutorBase> ActiveExecutor;` — `UPROPERTY(Transient)`
- L154 _private member_ `TObjectPtr<UMoviePipelineQueue> CurrentQueue;` — `UPROPERTY(Transient, Instanced)`
- L156 _private member_ `TOptional<FMoviePipelineOutputData> CachedRenderJobResults;`
- L157 _private member_ `TSubclassOf<UMovieRenderDebugWidget> CachedProgressWidgetClass;`
- L158 _private member_ `bool bCachedRenderPlayerViewport;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineRenderPass.h` (Public)


#### class `UMoviePipelineRenderPass`  
`class UMoviePipelineRenderPass : public UMoviePipelineSetting`  
_L11-79_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UMoviePipelineSetting`
- L16 _public function_ `void Setup(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings)`
- L21 _public function_ `void Teardown()`
- L28 _public function_ `void OnFrameStart()` — Called at the start of a new frame to allow the render pass to perform any pre-frame operations
- L34 _public function_ `virtual void OnTileStart(FIntPoint TileIndexes)` — Called at the start and end of tile rendering, allowing per-tile operations
- L38 _public function_ `virtual void OnTileEnd(FIntPoint TileIndexes)`
- L44 _public function_ `void GatherOutputPasses(TArray<FMoviePipelinePassIdentifier>& ExpectedRenderPasses)` — An array of identifiers for the output buffers expected as a result of this render pass.
- L50 _public function_ `void RenderSample_GameThread(const FMoviePipelineRenderPassMetrics& InSampleState)` — This will called for each requested sample.
- L56 _public function_ `bool IsAlphaInTonemapperRequired() const` — `UE_DEPRECATED(5.6, "This function is no longer in use.")`
- L61 _public function_ `virtual bool NeedsFrameThrottle() const`
- L65 _protected function_ `virtual bool IsValidOnShots() const override`
- L66 _protected function_ `virtual bool IsValidOnPrimary() const override`
- L68 _protected function_ `virtual FText GetCategoryText() const override`
- L71 _protected function_ `virtual void SetupImpl(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings)`
- L72 _protected function_ `virtual void WaitUntilTasksComplete()`
- L73 _protected function_ `virtual void TeardownImpl()`
- L74 _protected function_ `virtual void OnFrameStartImpl()`
- L75 _protected function_ `virtual void OnTileStartImpl(FIntPoint TileIndexes)`
- L76 _protected function_ `virtual void OnTileEndImpl(FIntPoint TileIndexes)`
- L77 _protected function_ `virtual void GatherOutputPassesImpl(TArray<FMoviePipelinePassIdentifier>& ExpectedRenderPasses)`
- L78 _protected function_ `virtual void RenderSample_GameThreadImpl(const FMoviePipelineRenderPassMetrics& InSampleState)`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineSetting.h` (Public)


#### enum `EMoviePipelineValidationState`  
`enum class EMoviePipelineValidationState : uint8`  
_L17-22_
- L19 _public enumerator_ `Valid = 0`
- L20 _public enumerator_ `Warnings = 1`
- L21 _public enumerator_ `Errors = 2`

#### class `UMoviePipelineSetting`  
`class UMoviePipelineSetting : public UObject`  
_L28-174_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UObject`
- desc: A base class for all Movie Render Pipeline settings.
- L33 _public prototype_ `UMoviePipelineSetting();`
- L39 _public prototype_ `void OnMoviePipelineInitialized(UMoviePipeline* InPipeline);` — This is called once on a setting when the movie pipeline is first set up. If the setting only exists as part of a shot override, it will be called once when the shot is initialized.
- L46 _public function_ `void OnMoviePipelineShutdown(UMoviePipeline* InPipeline)` — This is called once on a setting when the movie pipeline is shut down. If the setting only exists as part of a shot override, it will be called once the shot is finished. see shot-related callbacks so that they work properly with shot-overrides.
- L53 _public function_ `void OnSetupForShot(UMoviePipelineExecutorShot* InShot)` — Called only on settings that have been added to the Primary Configuration to let you know that a shot is about to be rendered. Useful if your setting needs to know something about the shot to do something correctly, without using a per-shot override.
- L58 _public function_ `void OnTeardownForShot(UMoviePipelineExecutorShot* InShot)` — Called only on settings that have been added to the Primary Configuration to let you know that a shot has finished rendering and is being torn down.
- L67 _public function_ `void BuildNewProcessCommandLineArgs(UPARAM(ref) TArray<FString>& InOutUnrealURLParams, UPARAM(ref) TArray<FString>& InOutCommandLineArgs, UPARAM(ref) TArray<FString>& InOutDeviceProfileCvars, UPARAM(ref) TArray<FString>& InOutExecCmds) const` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — When rendering in a new process some settings may need to provide command line arguments to affect engine settings that need to be set before most of the engine boots up. This function allows a setting to provide these when the user wants to run in a separate process. This won't be used when running in the current process because it is too late to modify the command line.
- L72 _public function_ `void ValidateState()` — Attempt to validate the configuration the user has chosen for this setting. Caches results for fast lookup in UI later.
- L75 _public prototype_ `virtual UWorld* GetWorld() const override;` — UObject Interface
- L79 _public function_ `bool HasFinishedExporting()` — Post Finalize Export
- L80 _public function_ `void BeginExport()`
- L84 _public function_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const` — Updates telemetry data for this setting. Should only be used by settings that ship with Movie Render Queue.
- L87 _protected prototype_ `UMoviePipeline* GetPipeline() const;`
- L89 _protected function_ `virtual void SetupForPipelineImpl(UMoviePipeline* InPipeline)`
- L90 _protected function_ `virtual void TeardownForPipelineImpl(UMoviePipeline* InPipeline)`
- L91 _protected function_ `virtual void OnSetupForShotImpl(UMoviePipelineExecutorShot* InShot)`
- L92 _protected function_ `virtual void OnTeardownForShotImpl(UMoviePipelineExecutorShot* InShot)`
- L96 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L99 _public function_ `virtual FText GetDisplayText() const` — Warning: This gets called on the CDO of the object
- L101 _public function_ `virtual FText GetCategoryText() const` — Warning: This gets called on the CDO of the object
- L104 _public function_ `virtual FText GetFooterText(UMoviePipelineExecutorJob* InJob) const` — Return a string to show in the footer of the details panel. Will be combined with other selected settings.
- L107 _public function_ `virtual bool CanBeDisabled() const` — Can this setting be disabled? UI only.
- L110 _public function_ `const FSlateBrush* GetDisplayIcon()` — What icon should this setting use when displayed in the tree list.
- L113 _public function_ `FText GetDescriptionText()` — What tooltip should be displayed for this setting when hovered in the tree list?
- L116 _public prototype_ `virtual bool IsValidOnShots() const PURE_VIRTUAL(UMoviePipelineSetting::IsValidOnShots, return false; );` — Can this configuration setting be added to shots? If not, it will throw an error when trying to add it to a shot config.
- L118 _public prototype_ `virtual bool IsValidOnPrimary() const PURE_VIRTUAL(UMoviePipelineSetting::IsValidOnPrimary, return false; );` — Can this configuration setting be added to the primary configuration? If not, it will throw an error when trying to add it to the primary configuration.
- L124 _public function_ `virtual bool IgnoreTransientFilters() const` — If true, then this setting will be included when searching for settings even if it was added transiently. This is used for the rare case where a setting needs to be run (to set reasonable default values) even if the user hasn't added it.
- L129 _public function_ `virtual int32 GetPriority() const` — Higher priority settings are run after lower priority settings when setting up shots during rendering. This is run in reverse during teardown!
- L133 _public function_ `virtual EMoviePipelineValidationState GetValidationState() const` — What is the result of the last validation? Only valid if the setting has had ValidateState() called on it.
- L136 _public function_ `virtual void ValidateStateImpl()` — Attempt to validate the configuration the user has chosen for this setting. Caches results for fast lookup in UI later.
- L139 _public prototype_ `virtual TArray<FText> GetValidationResults() const;` — Get a human-readable text describing what validation errors (if any) the call to ValidateState() produced.
- L142 _public function_ `virtual void GetFormatArguments(FMoviePipelineFormatArgs& InOutFormatArgs) const` — Return Key/Value pairs that you wish to be usable in the Output File Name format string or file metadata. This allows settings to add format strings based on their values.
- L145 _public function_ `virtual void BuildNewProcessCommandLineArgsImpl(TArray<FString>& InOutUnrealURLParams, TArray<FString>& InOutCommandLineArgs, TArray<FString>& InOutDeviceProfileCvars, TArray<FString>& InOutExecCmds) const` — Modify the Unreal URL and Command Line Arguments when preparing the setting to be run in a new process.
- L148 _public function_ `virtual bool IsSolo() const` — Can only one of these settings objects be active in a valid pipeline?
- L152 _public function_ `virtual bool IsEnabled() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Is this setting enabled by the user in the UI?
- L154 _public function_ `virtual void SetIsEnabled(bool bInEnabled)` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")`
- L157 _public function_ `virtual bool HasFinishedExportingImpl()` — Has this setting finished any export-related things it needs to do post-finalize?
- L159 _public function_ `virtual void BeginExportImpl()` — Called once when all files have been finalized.
- L163 _private member_ `TWeakObjectPtr<UMoviePipeline> CachedPipeline;` — `UPROPERTY(Transient)`
- L167 _private member_ `bool bEnabled;` — `UPROPERTY()` — Is this setting currently enabled? Disabled settings are like they never existed.
- L170 _protected member_ `EMoviePipelineValidationState ValidationState;` — What was the result of the last call to ValidateState()
- L173 _protected member_ `TArray<FText> ValidationResults;` — If ValidationState isn't valid, what text do we want to show the user to explain to them why?

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineSettingBlueprintBase.h` (Public)


#### class `UMoviePipelineSetting_BlueprintBase`  
`class UMoviePipelineSetting_BlueprintBase : public UMoviePipelineSetting`  
_L18-91_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UMoviePipelineSetting`
- desc: A base class for all Movie Render Pipeline settings which can be implemented in Blueprints. This features a slightly different API than the regular UMoviePipelineSetting to make the Blueprint integration nicer without breaking the C++ API backwards compatibility.
- L23 _public function_ `UMoviePipelineSetting_BlueprintBase()`
- L32 _public function_ `virtual void SetupForPipelineImpl(UMoviePipeline* InPipeline) override` — Setup
- L39 _public prototype_ `void ReceiveSetupForPipelineImpl(UMoviePipeline* InPipeline);` — `UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "SetupForPipeline"))`
- L42 _public function_ `virtual void TeardownForPipelineImpl(UMoviePipeline* InPipeline) override` — Teardown
- L49 _public prototype_ `void ReceiveTeardownForPipelineImpl(UMoviePipeline* InPipeline);` — `UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="TeardownForPipeline"))`
- L52 _public function_ `virtual void GetFormatArguments(FMoviePipelineFormatArgs& InOutFormatArgs) const override` — Format Arguments & EXR Metadata
- L54 _public prototype_ `FMoviePipelineFormatArgs ReceiveGetFormatArguments(UPARAM(ref) FMoviePipelineFormatArgs& InOutFormatArgs) const;` — `UFUNCTION(BlueprintNativeEvent, meta=(DisplayName="GetFormatArgumentsAndMetadata"))`
- L56 _public function_ `FMoviePipelineFormatArgs ReceiveGetFormatArguments_Implementation(FMoviePipelineFormatArgs& InOutFormatArgs) const` — Native Implementation so that if a blueprint class doesn't override this function we still pass on the previous arguments to the rest of the chain.
- L60 _public prototype_ `void OnEngineTickBeginFrame();` — `UFUNCTION(BlueprintImplementableEvent)` — Tick
- L65 _public function_ `virtual FText GetCategoryText() const override` — Warning: This gets called on the CDO of the object
- L68 _public function_ `virtual FText GetFooterText(UMoviePipelineExecutorJob* InJob) const override` — UI Footer Text
- L70 _public prototype_ `FText ReceiveGetFooterText(UMoviePipelineExecutorJob* InJob) const;` — `UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="GetFooterText"))`
- L72 _public function_ `virtual bool CanBeDisabled() const override`
- L74 _public function_ `virtual bool IsValidOnPrimary() const override`
- L75 _public function_ `virtual bool IsValidOnShots() const override`
- L77 _public prototype_ `virtual void PostLoad() override;`
- L81 _protected member_ `FText CategoryText;` — `UPROPERTY(EditDefaultsOnly, Category = "Movie Pipeline")`
- L84 _protected member_ `bool bIsValidOnPrimary;` — `UPROPERTY(EditDefaultsOnly, Category = "Movie Pipeline")`
- L87 _protected member_ `bool bIsValidOnShots;` — `UPROPERTY(EditDefaultsOnly, Category = "Movie Pipeline")`
- L90 _protected member_ `bool bCanBeDisabled;` — `UPROPERTY(EditDefaultsOnly, Category = "Movie Pipeline")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineShotConfig.h` (Public)


#### class `UMoviePipelineShotConfig`  
`class UMoviePipelineShotConfig : public UMoviePipelineConfigBase`  
_L13-30_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineConfigBase`
- L18 _public function_ `UMoviePipelineShotConfig()`
- L24 _protected function_ `virtual bool CanSettingBeAdded(const UMoviePipelineSetting* InSetting) const override`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineSurfaceReader.h` (Public)


#### struct `FMoviePipelineSurfaceReader`  
`struct FMoviePipelineSurfaceReader : public TSharedFromThis<FMoviePipelineSurfaceReader, ESPMode::ThreadSafe>`  
_L21-86_
- inherits: `TSharedFromThis<FMoviePipelineSurfaceReader,ESPMode::ThreadSafe>`
- desc: When the GPU finishes rendering a view we can copy the resulting data back to the CPU. Because the buffer is still in use this requires flushing the RHI and stalling the GPU from doing any additional work while the copy is in progress. To resolve this issue, when the data is returned we schedule a copy to a surface that isn't in use which allows the GPU to resume work. Then when the surface is written to, we can copy it to the CPU without blocking the GPU. This requires ensuring that the surface is available, so this SurfaceReader implements a trigger system to ensure we don't try to access the surface until it has been written to, combined with a round-robin of surfaces to avoid stalls.
- L25 _public prototype_ `FMoviePipelineSurfaceReader(EPixelFormat InPixelFormat, bool bInInvertAlpha);` — Construct a surface reader with the given pixel format and size. This will be the output specification.
- L27 _public prototype_ `~FMoviePipelineSurfaceReader();`
- L30 _public prototype_ `void Initialize();` — Initialize this reader so that it can be waited on.
- L33 _public prototype_ `void BlockUntilAvailable();` — Wait until this surface is available for reuse. Used to stall if we've run out of available surfaces.
- L39 _public prototype_ `void Reset();` — Safely resets the state of the wait event. When doing latent surface reading sometimes we may want to just bail on reading a given frame. Should only be performed after flushing rendering commands.
- L41 _public function_ `bool WasEverQueued() const`
- L42 _public function_ `bool IsAvailable() const`
- L47 _public prototype_ `void ResolveSampleToReadbackTexture_RenderThread(FRHICommandListImmediate& RHICmdList, const FTextureRHIRef& SourceSurfaceSample);` — Issues a command to the GPU to copy the given SourceSurfaceSample to our local ReadbackTexture for this surface.
- L50 _public function_ `void ResolveSampleToReadbackTexture_RenderThread(const FTextureRHIRef& SourceSurfaceSample)` — `UE_DEPRECATED(5.8, "ResolveSampleToReadbackTexture_RenderThread now requires the immediate RHI command list.")`
- L58 _public prototype_ `void CopyReadbackTexture_RenderThread(FRHICommandListImmediate& RHICmdList, TUniqueFunction<void(TUniquePtr<FImagePixelData>&&)>&& InFunctionCallback, TSharedPtr<FImagePixelDataPayload, ESPMode::ThreadSafe> InFramePayload);` — Maps the ReadbackTexture to the CPU (which should have been resolved to before this point) and copies the data over.
- L61 _public function_ `void CopyReadbackTexture_RenderThread(TUniqueFunction<void(TUniquePtr<FImagePixelData>&&)>&& InFunctionCallback, TSharedPtr<FImagePixelDataPayload, ESPMode::ThreadSafe> InFramePayload)` — `UE_DEPRECATED(5.8, "CopyReadbackTexture_RenderThread now requires the immediate RHI command list.")`
- L69 _protected prototype_ `void ResizeImpl(uint32 Width, uint32 Height);` — Set up this surface to the specified width/height
- L73 _protected member_ `FEvent* AvailableEvent;` — Optional event that is triggered when the surface is no longer in use
- L76 _protected member_ `TUniquePtr<FRHIGPUTextureReadback> ReadbackTexture;` — Texture used to store the resolved render target
- L79 _protected member_ `EPixelFormat PixelFormat;` — The desired pixel format of the resolved textures
- L82 _protected member_ `FIntPoint Size;` — The desired size for this texture
- L84 _protected member_ `bool bQueuedForCapture;`
- L85 _protected member_ `bool bInvertAlpha;`

#### struct `FMoviePipelineSurfaceQueue`  
`struct FMoviePipelineSurfaceQueue`  
_L88-142_
- L91 _public prototype_ `FMoviePipelineSurfaceQueue(FIntPoint InSurfaceSize, EPixelFormat InPixelFormat, uint32 InNumSurfaces, bool bInInvertAlpha);`
- L92 _public prototype_ `~FMoviePipelineSurfaceQueue();`
- L95 _public prototype_ `FMoviePipelineSurfaceQueue(FMoviePipelineSurfaceQueue&&) = default;` — Movable
- L96 _public prototype_ `FMoviePipelineSurfaceQueue& operator=(FMoviePipelineSurfaceQueue&&) = default;`
- L99 _public prototype_ `FMoviePipelineSurfaceQueue(const FMoviePipelineSurfaceQueue&) = delete;` — Non Copyable
- L100 _public prototype_ `FMoviePipelineSurfaceQueue& operator=(const FMoviePipelineSurfaceQueue&) = delete;`
- L103 _public prototype_ `void OnRenderTargetReady_RenderThread(const FTextureRHIRef InRenderTarget, TSharedRef<FImagePixelDataPayload, ESPMode::ThreadSafe> InPayload, TUniqueFunction<void(TUniquePtr<FImagePixelData>&&)>&& InFunctionCallback);`
- L105 _public prototype_ `void BlockUntilAnyAvailable();`
- L106 _public prototype_ `void Shutdown();`
- L109 _public prototype_ `void UpdateLastUsedFrame();` — Updates the stored last used frame to be the current frame
- L112 _public prototype_ `bool IsStale() const;` — Returns true if the amount of frames between the current frame and the last used frame is greater than a specific threshold
- L132 _private member_ `int32 CurrentFrameIndex;` — Which surface is the next target to be copied to.
- L135 _private member_ `TArray<FResolveSurface> Surfaces;` — The array of surfaces we can resolve a render target to. More peformant if there's more than one.
- L138 _private member_ `int32 FrameResolveLatency;` — How many frames do we wait before we resolve a frame?
- L141 _private member_ `uint64 LastUsedFrame;` — The last frame this surface was used. Surfaces that haven't been used for a certain number of frames are cleaned up

#### struct `FMoviePipelineSurfaceQueue::FResolveSurface`  
`struct FResolveSurface`  
_L115-129_
- L119 _public function_ `FResolveSurface(const EPixelFormat InPixelFormat, const FIntPoint InSurfaceSize, const bool bInInvertAlpha) : Surface(new FMoviePipelineSurfaceReader(InPixelFormat, bInInvertAlpha))`
- L125 _public member_ `const TSharedRef<FMoviePipelineSurfaceReader, ESPMode::ThreadSafe> Surface;`
- L127 _public member_ `TUniqueFunction<void(TUniquePtr<FImagePixelData>&&)> FunctionCallback;`
- L128 _public member_ `TSharedPtr<FImagePixelDataPayload, ESPMode::ThreadSafe> FunctionPayload;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineTelemetry.h` (Public)


#### struct `FMoviePipelineBeginShotRenderTelemetryContext`  
`struct FMoviePipelineBeginShotRenderTelemetryContext`  
_L17-22_
- desc: Context used to send begin-shot render telemetry.
- L19 _public member_ `UMoviePipelineExecutorShot* Shot = nullptr;`
- L20 _public member_ `UMovieGraphEvaluatedConfig* EvaluatedConfig = nullptr;`
- L21 _public member_ `bool bIsBasicConfig = false;`

#### struct `FMoviePipelineEndShotRenderTelemetryContext`  
`struct FMoviePipelineEndShotRenderTelemetryContext`  
_L25-38_
- desc: Context used to send end-shot render telemetry.
- L28 _public prototype_ `void MergeRenderPassTelemetry(const FMoviePipelineEndShotRenderTelemetryContext& InTelemetry);` — Merges in relevant properties within InTelemetry into this context instance.
- L30 _public member_ `bool bIsGraph = false;`
- L31 _public member_ `bool bIsBasicConfig = false;`
- L32 _public member_ `bool bWasSuccessful = false;`
- L33 _public member_ `bool bWasCanceled = false;`
- L34 _public member_ `int32 TotalRenderedFrameCount = 0;`
- L35 _public member_ `bool bUsesAccumulationDepthOfField = false;`
- L36 _public member_ `int32 AccumulationDepthOfFieldSampleCount = 0;`
- L37 _public member_ `float AccumulationDepthOfFieldSplatSize = 0.f;`

#### struct `FMoviePipelineShotRenderTelemetry`  
`struct FMoviePipelineShotRenderTelemetry`  
_L41-93_
- desc: Telemetry data that is captured when a shot begins rendering. Only for use with settings/nodes shipped with Movie Render Queue/Graph.
- L43 _public member_ `bool bIsGraph = false;`
- L44 _public member_ `bool bIsBasicConfig = false;`
- L45 _public member_ `bool bIsQuickRender = false;`
- L46 _public member_ `bool bUsesDeferred = false;`
- L47 _public member_ `bool bUsesPathTracer = false;`
- L48 _public member_ `bool bUsesPanoramic = false;`
- L49 _public member_ `bool bUsesHighResTiling = false;`
- L50 _public member_ `bool bUsesNDisplay = false;`
- L51 _public member_ `bool bUsesObjectID = false;`
- L52 _public member_ `bool bUsesUIRenderer = false;`
- L53 _public member_ `bool bUsesMultiCamera = false;`
- L54 _public member_ `bool bUsesScripting = false;`
- L55 _public member_ `bool bUsesSubgraphs = false;`
- L56 _public member_ `bool bUsesPPMs = false;`
- L57 _public member_ `bool bUsesAudio = false;`
- L58 _public member_ `bool bMovieEncodesAudio = false;`
- L59 _public member_ `bool bUsesCommandLineEncoder = false;`
- L60 _public member_ `bool bSetsConsoleVariables = false;`
- L61 _public member_ `bool bSetsQueueConsoleVariables = false;`
- L62 _public member_ `bool bUsesConsoleVariablePreset = false;`
- L63 _public member_ `bool bUsesModifier = false;`
- L64 _public member_ `bool bUsesLightModifier = false;`
- L65 _public member_ `bool bUsesMpcModifier = false;`
- L66 _public member_ `bool bUsesAvid = false;`
- L67 _public member_ `bool bUsesProRes = false;`
- L68 _public member_ `bool bUsesMP4 = false;`
- L69 _public member_ `bool bUsesJPG = false;`
- L70 _public member_ `bool bUsesPNG = false;`
- L71 _public member_ `bool bUsesBMP = false;`
- L72 _public member_ `bool bUsesEXR = false;`
- L73 _public member_ `bool bUsesMultiEXR = false;`
- L74 _public member_ `bool bUsesTmvMovie = false;`
- L75 _public member_ `bool bUsesTmvImageSequence = false;`
- L76 _public member_ `bool bUsesMotionDesignRundown = false;`
- L77 _public member_ `int32 ResolutionX = 0;`
- L78 _public member_ `int32 ResolutionY = 0;`
- L79 _public member_ `int32 HandleFrameCount = 0;`
- L80 _public member_ `int32 TemporalSampleCount = 0;`
- L81 _public member_ `int32 SpatialSampleCount = 0;`
- L82 _public member_ `int32 WarmUpFrames = 0;`
- L83 _public member_ `int32 LayerWarmUpFrames = 0;`
- L84 _public member_ `int32 RenderLayerCount = 0;`
- L85 _public member_ `int32 HighResTileCount = 0;`
- L86 _public member_ `float HighResOverlap = 0;`
- L87 _public member_ `bool bUsesPageToSystemMemory = false;`
- L88 _public member_ `FString ScalabilityQualityLevel;`
- L89 _public member_ `FString AntiAliasingType;`

#### class `FMoviePipelineTelemetry`  
`class FMoviePipelineTelemetry`  
_L96-123_
- desc: Responsible for sending out telemetry for Movie Render Queue, Movie Render Graph, and Quick Render.
- L100 _public prototype_ `static void SendRendersRequestedTelemetry(const bool bIsLocal, TArray<UMoviePipelineExecutorJob*>&& InJobs);` — Sends out telemetry that captures queue-level information. Called by either MRQ or MRG, not Quick Render.
- L103 _public prototype_ `static void SendQuickRenderRequestedTelemetry(const EMovieGraphQuickRenderMode QuickRenderMode);` — Sends out telemetry that captures Quick Render information for the provided mode.
- L106 _public prototype_ `static void SendBeginShotRenderTelemetry(const FMoviePipelineBeginShotRenderTelemetryContext& InContext);` — Sends out telemetry that includes information about the shot being rendered (the type of rendering being done, which types of settings/nodes are being used, etc).
- L109 _public prototype_ `static void SendEndShotRenderTelemetry(const FMoviePipelineEndShotRenderTelemetryContext& InContext);` — Sends out telemetry that indicates whether the shot was rendered successfully.
- L113 _private member_ `inline static bool bIsCurrentRenderRequestQuickRender = false;` — Tracks whether the current render request originated from Quick Render. If false, the render originated from a queue in either MRQ or MRG.
- L116 _private prototype_ `static FString GetSessionType();` — Gets the current session type (Editor, DashGame, Shipping).
- L119 _private prototype_ `static FMoviePipelineShotRenderTelemetry GatherShotRenderTelemetryForGraph(const UMoviePipelineExecutorShot* InShot, UMovieGraphEvaluatedConfig* InEvaluatedConfig, const bool bIsBasicConfig);` — Returns a populated telemetry object for the shot and graph that's specified.
- L122 _private prototype_ `static FMoviePipelineShotRenderTelemetry GatherShotRenderTelemetryForLegacy(UMoviePipelineExecutorShot* InShot);` — Returns a populated telemetry object for the shot that's specified. For use with the legacy system, not the graph.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineUtils.h` (Public)


#### Free symbols / members of external scopes

- L24 _namespace_ `namespace MoviePipeline`
- L26 _function_ `static UWorld* FindCurrentWorld()` (scope `MoviePipeline`)
- L50 _prototype_ `void GetPassCompositeData(FMoviePipelineMergerOutputFrame* InMergedOutputFrame, TArray<MoviePipeline::FCompositePassInfo>& OutCompositedPasses);` (scope `MoviePipeline`)
- L54 _macro_ `#define MOVIEPIPELINE_STORE_AND_OVERRIDE_CVAR_BOOL(InOutVariable, CVarName, OverrideValue, bUseOverride) \`
- L72 _macro_ `#define MOVIEPIPELINE_STORE_AND_OVERRIDE_CVAR_INT(InOutVariable, CVarName, OverrideValue, bUseOverride) \`
- L90 _macro_ `#define MOVIEPIPELINE_STORE_AND_OVERRIDE_CVAR_FLOAT(InOutVariable, CVarName, OverrideValue, bUseOverride) \`
- L108 _macro_ `#define MOVIEPIPELINE_STORE_AND_OVERRIDE_CVAR_BOOL_IF_EXIST(InOutVariable, CVarName, OverrideValue, bUseOverride) \`
- L126 _macro_ `#define MOVIEPIPELINE_STORE_AND_OVERRIDE_CVAR_INT_IF_EXIST(InOutVariable, CVarName, OverrideValue, bUseOverride) \`
- L144 _macro_ `#define MOVIEPIPELINE_STORE_AND_OVERRIDE_CVAR_FLOAT_IF_EXIST(InOutVariable, CVarName, OverrideValue, bUseOverride) \`
- L169 _macro_ `#define MRG_LOG_ONCE_PER_RENDER(Identifier, LogCategory, LogVerbosity, LogFormat, ...) \` — Log a message once per render. Note that the arguments to this are the same as for UE_LOG, but also takes an additional `Identifier`. The identifier is what uniquely identifies this specific message within the current SCOPE (identifiers are NOT unique across scopes, so the same log message will be logged more than once per render if it appears in different scopes).
- L189 _namespace_ `namespace UE`
- L191 _namespace_ `namespace MovieRenderPipeline` (scope `UE`)
- L194 _prototype_ `TArray<UClass*> FindMoviePipelineSettingClasses(UClass* InBaseClass, const bool bIncludeBlueprints = true);` (scope `UE::MovieRenderPipeline`) — Finds UMoviePipelineSetting classes declared in the project using the asset registry, potentially including blueprint implemented classes.
- L196 _prototype_ `EAntiAliasingMethod GetEffectiveAntiAliasingMethod(bool bOverride, EAntiAliasingMethod OverrideMethod);` (scope `UE::MovieRenderPipeline`) — Anti-aliasing is defined as a Project Setting, and then MRG can optionally override it. Utility function for getting the project setting and optionally applying the MRQ override to the return value.
- L198 _prototype_ `EAntiAliasingMethod GetEffectiveAntiAliasingMethod(const UMoviePipelineAntiAliasingSetting* InSetting);` (scope `UE::MovieRenderPipeline`) — Anti-aliasing is defined as a Project Setting, and then MRQ can optionally override it. Utility function for getting the project setting and optionally applying the MRQ override to the return value.
- L201 _prototype_ `uint64 GetRendererFrameCount();` (scope `UE::MovieRenderPipeline`) — `UE_DEPRECATED(5.3, "Do not use, this is here as a temporary workaround for another issue.")`
- L208 _prototype_ `void UpdateSceneViewForShowFlags(FSceneView* View);` (scope `UE::MovieRenderPipeline`) — Updates the provided scene view in accordance with the show flags that are currently set (eg, changes the specular override color if the OverrideDiffuseAndSpecular show flag is set). The show flags that are looked at here are usually the ones that are set when the view mode index is changed.
- L211 _namespace_ `namespace MoviePipeline` (scope `UE`)
- L214 _prototype_ `bool GetAlphaOutputOverride();` (scope `UE::MoviePipeline`) — Get the value of the MovieRenderPipeline.AlphaOutputOverride console variable.
- L215 _prototype_ `void ConformOutputFormatStringToken(FString& InOutFilenameFormatString, const FStringView InToken, const FName& InNodeName, const FName& InBranchName);` (scope `UE::MoviePipeline`)
- L216 _prototype_ `void ValidateOutputFormatString(FString& InOutFilenameFormatString, const bool bTestRenderPass, const bool bTestFrameNumber, const bool bIncludeCameraName = false);` (scope `UE::MoviePipeline`)
- L217 _prototype_ `void RemoveFrameNumberFormatStrings(FString& InOutFilenameFormatString, const bool bIncludeShots);` (scope `UE::MoviePipeline`)
- L219 _prototype_ `void DeduplicateNameArray(TArray<FString>& InOutNames);` (scope `UE::MoviePipeline`) — De-duplicates the provided array of strings by appending (1), (2), etc to the end of duplicates.
- L221 _prototype_ `FString GetJobAuthor(const UMoviePipelineExecutorJob* InJob);` (scope `UE::MoviePipeline`)
- L222 _prototype_ `void GetSharedFormatArguments(TMap<FString, FString>& InFilenameArguments, TMap<FString, FString>& InFileMetadata, const FDateTime& InDateTime, const int32 InVersionNumber, const UMoviePipelineExecutorJob* InJob, const FTimespan& InInitializationTimeOffset = FTimespan());` (scope `UE::MoviePipeline`)
- L223 _prototype_ `void GetHardwareUsageMetadata(TMap<FString, FString>& InFileMetadata, const FString& InOutputDir);` (scope `UE::MoviePipeline`)
- L224 _prototype_ `void GetDiagnosticMetadata(TMap<FString, FString>& InFileMetadata, const bool bIsGraph);` (scope `UE::MoviePipeline`)
- L225 _prototype_ `void GetMetadataFromCineCamera(UCineCameraComponent* InComponent, const FString& InPrefix, TMap<FString, FString>& InOutMetadata);` (scope `UE::MoviePipeline`)
- L226 _prototype_ `void GetMetadataFromCineCamera(UCineCameraComponent* InComponent, const FString& InCameraName, const FString& InRenderPassName, TMap<FString, FString>& InOutMetadata);` (scope `UE::MoviePipeline`)
- L227 _prototype_ `void GetMetadataFromCameraLocRot(const FString& InCameraName, const FString& InRenderPassName, const FVector& InCurLoc, const FRotator& InCurRot, const FVector& InPrevLoc, const FRotator& InPrevRot, TMap<FString, FString>& InOutMetadata);` (scope `UE::MoviePipeline`)
- L228 _prototype_ `void GetMetadataFromCameraLocRot(const FVector& InCurLoc, const FRotator& InCurRot, const FVector& InPrevLoc, const FRotator& InPrevRot, const FString& InPrefix, TMap<FString, FString>& InOutMetadata);` (scope `UE::MoviePipeline`)
- L230 _prototype_ `FMoviePipelineRenderPassMetrics GetRenderPassMetrics(UMoviePipelinePrimaryConfig* InPrimaryConfig, UMoviePipelineExecutorShot* InPipelineExecutorShot, const FMoviePipelineRenderPassMetrics& InRenderPassMetrics, const FIntPoint& InEffectiveOutputResolution);` (scope `UE::MoviePipeline`)
- L231 _prototype_ `bool CanWriteToFile(const TCHAR* InFilename, bool bOverwriteExisting);` (scope `UE::MoviePipeline`)
- L232 _prototype_ `FString GetPaddingFormatString(int32 InZeroPadCount, const int32 InFrameNumber);` (scope `UE::MoviePipeline`)
- L233 _prototype_ `void DoPostProcessBlend(const FVector& InViewLocation, const class UWorld* InWorld, const struct FMinimalViewInfo& InViewInfo, class FSceneView* InOutView);` (scope `UE::MoviePipeline`)
- L235 _prototype_ `void SetSkeletalMeshClothSubSteps(const int32 InSubdivisionCount, UWorld* InWorld, TMap<TWeakObjectPtr<UObject>, TArray<::MoviePipeline::FClothSimSettingsCache>>& InClothSimCache);` (scope `UE::MoviePipeline`)
- L236 _prototype_ `void RestoreSkeletalMeshClothSubSteps(const TMap<TWeakObjectPtr<UObject>, TArray<::MoviePipeline::FClothSimSettingsCache>>& InClothSimCache);` (scope `UE::MoviePipeline`)
- L240 _prototype_ `FVector2f GetSubPixelJitter(int32 InFrameIndex, int32 InSamplesPerFrame);` (scope `UE::MoviePipeline`) — When using spatial/temporal samples without anti-aliasing, get the sub-pixel jitter for the given frame index. FrameIndex is modded by InSamplesPerFrame so that the aa jitter pattern repeats every output frame.
- L245 _prototype_ `FIntPoint ScaleResolutionByOverscan(const float OverscanPercentage, const FIntPoint& InOutputResolution);` (scope `UE::MoviePipeline`) — Scales the specified resolution by the specified overscan amount, performing appropriate clamping and rounding.
- L246 _namespace_ `namespace Panoramic` (scope `UE::MoviePipeline`)
- L249 _prototype_ `TArray<float> DistributeValuesInInterval(float InMin, float InMax, int32 InNumDivisions, bool bInInclusiveMax);` (scope `UE::MoviePipeline::Panoramic`) — Returns an array of values distributed throughout the given range, used to calculate which angles the Panoramic renderers should orient the camera to.
- L251 _prototype_ `void GetCameraOrientationForStereo(FVector& OutLocation, FRotator& OutRotation, FRotator& OutLocalRotation, const UE::MoviePipeline::FPanoramicPane& InPane, const int32 InStereoIndex, const bool bInPrevPosition);` (scope `UE::MoviePipeline::Panoramic`) — Given the primary camera rotation and a pane describing the current pane, calculate a new rotation / location for the camera. If stereo was supported, the location would change with the rotation.
- L253 _prototype_ `int32 ComputeAutoExposureCubeCaptureSize(FIntPoint Resolution);` (scope `UE::MoviePipeline::Panoramic`) — Auto-exposure cubemap passes are laid out in a 3x2 arrangement, and rounded down to a multiple of 8 pixels.
- L258 _prototype_ `FString GetMetadataPrefixPath(const FMovieGraphRenderDataIdentifier& Identifier);` (scope `UE::MoviePipeline`) — When using EXR metadata what is the prefix that metadata tokens should go under? This returns "unreal/<layerName>/<rendererName>/<cameraName>" but be aware that the metadata keys will be potentially renamed when actually writing the EXR to disk so that the per-layer data goes into a key that matches the EXR layer names (which makes the lookup in external software much easier).
- L262 _namespace_ `namespace MoviePipeline`
- L264 _prototype_ `void GetOutputStateFormatArgs(TMap<FString, FString>& InFilenameArguments, TMap<FString, FString>& InFileMetadata, const FString FrameNumber, const FString FrameNumberShot, const FString FrameNumberRel, const FString FrameNumberShotRel, const FString CameraName, const FString ShotName);` (scope `MoviePipeline`)
- L270 _prototype_ `FString GetFrameTemplatedFilePath(const FString& InFilePath);` (scope `MoviePipeline`) — Given a non-templated file name/path, returns the "frame-templated" file path. A frame-templated file path is one that has had its {frame_*} token, if any, replaced with the {frame_placeholder} token. Returns the original file path if no modifications were done.
- L276 _prototype_ `TObjectPtr<UMovieJobVariableAssignmentContainer> GetOrCreateJobVariableAssignmentsForGraph(const UMovieGraphConfig* InGraph, TArray<TObjectPtr<UMovieJobVariableAssignmentContainer>>& InVariableAssignments, UObject* InAssignmentsOwner);` (scope `MoviePipeline`) — Gets the job variable assignments for a specific graph. Creates a new variable assignments container if one was not found for the given graph. The owner of the variable assignments must be provided in case a new assignment needs to be created.
- L279 _prototype_ `void RefreshVariableAssignments(UMovieGraphConfig* InRootGraph, TArray<TObjectPtr<UMovieJobVariableAssignmentContainer>>& InVariableAssignments, UObject* InAssignmentsOwner);` (scope `MoviePipeline`) — Refreshes the variable assignments for the given graph and its associated subgraphs.
- L285 _prototype_ `UMovieGraphConfig* DuplicateConfigRecursive(UMovieGraphConfig* InGraphToDuplicate, TMap<TObjectPtr<UMovieGraphConfig>, TObjectPtr<UMovieGraphConfig>>& OutDuplicatedGraphs);` (scope `MoviePipeline`) — Helps duplicate graph configs. Prevents re-duplications, duplicates sub-graphs (updates subgraph nodes accordingly), and potentially more. Returns the duplicated graph.
- L288 _prototype_ `void CacheCompleteSequenceHierarchy(UMovieSceneSequence* InSequence, TSharedPtr<FCameraCutSubSectionHierarchyNode> InRootNode);` (scope `MoviePipeline`) — Iterate root-to-tails and generate a HierarchyNode for each level. Caches the sub-section range, playback range, camera cut range, etc.
- L290 _prototype_ `void RestoreCompleteSequenceHierarchy(UMovieSceneSequence* InSequence, TSharedPtr<FCameraCutSubSectionHierarchyNode> InRootNode);` (scope `MoviePipeline`) — Matching function to Cache. Restores the sequence properties when given the root node.
- L292 _prototype_ `void BuildSectionHierarchyRecursive(const FMovieSceneSequenceHierarchy& InHierarchy, UMovieSceneSequence* InRootSequence, const FMovieSceneSequenceID InSequenceId, const FMovieSceneSequenceID InChildId, TSharedPtr<FCameraCutSubSectionHierarchyNode> OutSubsectionHierarchy);` (scope `MoviePipeline`) — Iterates tail to root building Hierarchy Nodes while correctly keeping track of which sub-section by GUID for correct enabling/disabling later.
- L294 _prototype_ `TTuple<FString, FString> GetNameForShot(const FMovieSceneSequenceHierarchy& InHierarchy, UMovieSceneSequence* InRootSequence, TSharedPtr<FCameraCutSubSectionHierarchyNode> InSubSectionHierarch);` (scope `MoviePipeline`) — Gets the inner and outer names for the shot by resolving camera bindings/shot names, etc. Not neccessairly the final names.
- L296 _prototype_ `void SaveOrRestoreSubSectionHierarchy(TSharedPtr<FCameraCutSubSectionHierarchyNode> InLeaf, const bool bInSave);` (scope `MoviePipeline`) — Given a leaf node, either caches the value of the hierarchy or restores it. Used to save the state before soloing a shot.
- L298 _prototype_ `void SetSubSectionHierarchyActive(TSharedPtr<FCameraCutSubSectionHierarchyNode> InRoot, bool bInActive);` (scope `MoviePipeline`) — Given a leaf node, appropriately sets the IsActive flags for the whole hierarchy chain up to root for soloing a shot.
- L300 _prototype_ `void CheckPartialSectionEvaluationAndWarn(const FFrameNumber& LeftDeltaTicks, TSharedPtr<FCameraCutSubSectionHierarchyNode> Node, UMoviePipelineExecutorShot* InShot, const FFrameRate& InRootDisplayRate);` (scope `MoviePipeline`) — Given a leaf node, searches for sections that will be partially evaluated when using temporal sub-sampling and prints a warning.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineVideoOutputBase.h` (Public)


#### struct `MovieRenderPipeline::IVideoCodecWriter`  
`struct IVideoCodecWriter`  
_L17-41_
- L19 _public function_ `IVideoCodecWriter() : bConvertToSrgb(true)`
- L24 _public member_ `FString FileName;` — The filename to actually write to disk with. This may include "de-duplication" numbers (MyFile (1).ext etc.)
- L28 _public member_ `FString StableFileName;` — The filename without de-duplication numbers, used to match up multiple incoming frames back to the same writer. We use this when looking for existing writers so that we can avoid the de-duplication numbers perpetually increasing due to the file existing on disk after the first frame comes in, and then the next one de-duplicating to one more than that.
- L29 _public member_ `FMoviePipelineFormatArgs FormatArgs;`
- L30 _public member_ `bool bConvertToSrgb;`
- L40 _public member_ `TMap<int32, FLightweightSourceData> LightweightSourceData;`

#### struct `MovieRenderPipeline::IVideoCodecWriter::FLightweightSourceData`  
`struct FLightweightSourceData`  
_L36-39_
- desc: This array contains the indexes of each shot that contributed to this writer. This is needed so that after a shot/render, when all we have is the completed blocks of audio samples, we can figure out which blocks go to which video clips. Because of how you can split videos up by either shot, or by the whole sequence, there isn't an obvious mapping, so this array will tell the audio writing system which audio blocks should be sent to the shot.
- L38 _public member_ `int32 SubmittedFrameCount;`

#### class `FMoviePipelineBackgroundMediaTasks`  
`class FMoviePipelineBackgroundMediaTasks`  
_L44-67_
- L47 _private member_ `FGraphEventRef LastCompletionEvent;`
- L50 _public function_ `FGraphEventRef Execute(TUniqueFunction<void()> InFunctor)`
- L63 _public function_ `inline TStatId GetStatId() const`

#### class `UMoviePipelineVideoOutputBase`  
`class UMoviePipelineVideoOutputBase : public UMoviePipelineOutputBase`  
_L77-111_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UMoviePipelineOutputBase`
- desc: A base class for video codec outputs for the Movie Pipeline system. To simplify encoder implementations this handles multi-threading for you and will call all of the encoding functions on a dedicated thread. This allows an encoder to do more expensive operations (such as image quantization) without implementing threading yourself, nor having to worry about blocking the game thread.
- L82 _public prototype_ `UMoviePipelineVideoOutputBase();`
- L86 _protected prototype_ `virtual void OnReceiveImageDataImpl(FMoviePipelineMergerOutputFrame* InMergedOutputFrame) override;` — UMoviePipelineOutputBase Interface
- L87 _protected prototype_ `virtual bool HasFinishedProcessingImpl() override;`
- L88 _protected prototype_ `virtual void BeginFinalizeImpl() override;`
- L89 _protected prototype_ `virtual void FinalizeImpl() override;`
- L90 _protected prototype_ `virtual void OnShotFinishedImpl(const UMoviePipelineExecutorShot* InShot, const bool bFlushToDisk) override;`
- L92 _protected prototype_ `virtual FText GetFooterText(UMoviePipelineExecutorJob* InJob) const override;`
- L97 _protected prototype_ `virtual TUniquePtr<MovieRenderPipeline::IVideoCodecWriter> Initialize_GameThread(const FString& InFileName, FIntPoint InResolution, EImagePixelType InPixelType, ERGBFormat InPixelFormat, uint8 InBitDepth, uint8 InNumChannels) PURE_VIRTUAL(UMoviePipelineVideoOutputBase::Initialize_GameThread, return nullptr; );` — UMoviePipelineVideoOutputBase Interface
- L98 _protected prototype_ `virtual bool Initialize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter) PURE_VIRTUAL(UMoviePipelineVideoOutputBase::Initialize_EncodeThread, return true;);`
- L99 _protected prototype_ `virtual void WriteFrame_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter, FImagePixelData* InPixelData, TArray<MoviePipeline::FCompositePassInfo>&& InCompositePasses) PURE_VIRTUAL(UMoviePipelineVideoOutputBase::WriteFrame_EncodeThread);`
- L100 _protected prototype_ `virtual void BeginFinalize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter) PURE_VIRTUAL(UMoviePipelineVideoOutputBase::BeginFinalize_EncodeThread);`
- L101 _protected prototype_ `virtual void Finalize_EncodeThread(MovieRenderPipeline::IVideoCodecWriter* InWriter) PURE_VIRTUAL(UMoviePipelineVideoOutputBase::Finalize_EncodeThread);`
- L102 _protected prototype_ `virtual const TCHAR* GetFilenameExtension() const PURE_VIRTUAL(UMoviePipelineVideoOutputBase::GetFilenameExtension, return TEXT(""););`
- L103 _protected prototype_ `virtual bool IsAudioSupported() const PURE_VIRTUAL(UMoviePipelineVideoOutputBase::IsAudioSupported, return false;);`
- L107 _private member_ `TArray<FMoviePipelineCodecWriter> AllWriters;`
- L108 _private member_ `bool bHasError;`
- L110 _private member_ `FGraphEventArray OutstandingTasks;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L15 _namespace_ `namespace MovieRenderPipeline`
- L69 _typedef_ `typedef TTuple<TUniquePtr<MovieRenderPipeline::IVideoCodecWriter>, TPromise<bool>> FMoviePipelineCodecWriter;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineViewFamilySetting.h` (Public)


#### class `UMoviePipelineViewFamilySetting`  
`class UMoviePipelineViewFamilySetting : public UMoviePipelineSetting`  
_L11-20_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UMoviePipelineSetting`
- L15 _public function_ `virtual bool IsValidOnShots() const override`
- L16 _public function_ `virtual bool IsValidOnPrimary() const override`
- L19 _public prototype_ `virtual void SetupViewFamily(FSceneViewFamily& ViewFamily) PURE_VIRTUAL(UMoviePipelineViewFamilySetting::SetupViewFamily, );` — Allows all Output settings to affect the ViewFamily's Render settings before Rendering starts.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MovieRenderDebugWidget.h` (Public)


#### class `UMovieRenderDebugWidget`  
`class UMovieRenderDebugWidget : public UUserWidget`  
_L17-23_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UUserWidget`
- desc: C++ Base Class for the debug widget that is drawn onto the game viewport (but not burned into the output files) that allow us to easily visualize the current state of the pipeline.
- L22 _public prototype_ `void OnInitializedForPipeline(UMoviePipeline* ForPipeline);` — `UFUNCTION(BlueprintImplementableEvent)`

#### class `UMovieGraphRenderPreviewWidget`  
`class UMovieGraphRenderPreviewWidget : public UUserWidget`  
_L31-37_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UUserWidget`
- desc: C++ Base Class for the preview widget that is drawn onto the game viewport (but not burned into the output files) that allow us to easily visualize the current state of the pipeline. Used for Graph Based pipelines.
- L36 _public prototype_ `void OnInitializedForPipeline(UMovieGraphPipeline* InPipeline);` — `UFUNCTION(BlueprintImplementableEvent)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MovieRenderOverlappedImage.h` (Public)


#### struct `FImageOverlappedPlane`  
`struct FImageOverlappedPlane`  
_L19-73_
- desc: Structure for a single overlapped image.
- L25 _public function_ `FImageOverlappedPlane() : Size(0,0)` — Default constructor.
- L35 _public prototype_ `void Init(FIntPoint InSize);` — Initialize the memory. Before using the memory, we also will need a call to ZeroPlane. @param InSize - Size of the tile in pixels.
- L40 _public prototype_ `void ZeroPlane();` — Zeroes the accumulation. Assumes the data is already allocated.
- L45 _public prototype_ `void Reset();` — Frees the memory and resets the sizes
- L61 _public prototype_ `void AccumulateSinglePlane(const TArray64<float>& InRawData, FIntPoint InSize, FIntPoint InOffset, float SubpixelOffsetX, float SubpixelOffsetY, FIntPoint SubRectOffset, FIntPoint SubRectSize, const TArray<float> & WeightDataX, const TArray<float> & WeightDataY);` — Accumulate a single tile to this plane. The raw data will in general be smaller than the full plane. Addtionally, we are only going to be using part of the input plane because the input plane will have unused border areas. The SubRect parameters describe the area inside the source plane. @param InRawData - Raw data to accumulate @param InWeightData - Mask to apply to the raw data for blending the overlapped areas. @param InSize - Size of the tile. Must exactly match. InSize.X @param InOffset - The (x,y) offset to the overlapped image. @param SubpixelOffsetX - Subpixeoffset of the tile (in X), goes from [0,1] with 0.5 meaning it is right in the center. @param SubpixelOffsetY - Subixel offset of the tile (in Y), goes from [0,1] with 0.5 meaning it is right in the center @param SubRectOffset - The offset of the SubRect inside the raw data (InRawData) that actually has a weight > 0.0. @param SubRectSize - The size of the SubRect inside the raw data (InRawData) that actually has a weight > 0.0.
- L69 _public member_ `TArray64<float> ChannelData;` — Actual channel data
- L72 _public member_ `FIntPoint Size;` — Width and Height of the image.

#### struct `FImageOverlappedAccumulator`  
`struct FImageOverlappedAccumulator : MoviePipeline::IMoviePipelineOverlappedAccumulator`  
_L78-223_
- inherits: `MoviePipeline::IMoviePipelineOverlappedAccumulator`
- desc: Contains all the image planes for the tiles.
- L84 _public function_ `FImageOverlappedAccumulator() : PlaneSize(0,0) , NumChannels(0) , AccumulationGamma(1.0f)` — Default constructor.
- L91 _public function_ `static FName GetName()`
- L106 _public prototype_ `void InitMemory(FIntPoint InPlaneSize, int32 InNumChannels);` — Allocates memory. @param InTileSizeX - Horizontal tile size. @param InTileSizeY - Vertical tile size. @param InNumTilesX - Num horizontal tiles. @param InNumTilesY - Num vertical tiles. @param InNumChannels - Num Channels.
- L113 _public prototype_ `void ZeroPlanes();` — Initializes memory. Resets the memory to 0s so that we can start a new frame.
- L120 _public prototype_ `void Reset();` — Resets the PlaneSize and NumChannels but does NOT free the memory because most of the time we're going to just need the same resolution next frame anyways when InitMemory is called again.
- L161 _public prototype_ `void AccumulatePixelData(const FImagePixelData& InPixelData, FIntPoint InTileOffset, FVector2D InSubpixelOffset, const MoviePipeline::FTileWeight1D & WeightX, const MoviePipeline::FTileWeight1D & WeightY);` — Given a rendered tile, accumulate the data to the full size image. @param InPixelData - Raw pixel data. @param InTileOffset - Tile offset in pixels. @param InSubPixelOffset - SubPixel offset, should be in the range [0,1) @param WeightX - 1D Weights in X @param WeightY - 1D Weights in Y
- L171 _public prototype_ `void FetchFinalPixelDataByte(TArray64<FColor>& OutPixelData) const;` — After accumulation is finished, fetch the final image as bytes. In theory we don't need this, because we could just fetch as LinearColor and convert to bytes. But the largest size asked for is 45k x 22.5k, which is 1B pixels. So fetching as LinearColor would create a 16GB intermediary image, so it's worth having an option to fetch straight to FColors. @param OutPixelData - Finished pixel data.
- L178 _public prototype_ `void FetchFinalPixelDataHalfFloat(TArray64<FFloat16Color>& OutPixelData) const;` — After accumulation is finished, fetch the final image as linear colors @param OutPixelData - Finished pixel data.
- L185 _public prototype_ `void FetchFinalPixelDataLinearColor(TArray64<FLinearColor>& OutPixelData) const;` — After accumulation is finished, fetch the final image as linear colors @param OutPixelData - Finished pixel data.
- L195 _public prototype_ `void FetchFullImageValue(float Rgba[4], int32 FullX, int32 FullY) const;` — Grab a single pixel from the full res tile and scale it by the appropriate Scale value. @param Rgba - Found pixel value. @param PlaneScale - The scales of each channel plane. @param FullX - X position of the full res image. @param FullY - Y position of the full res image.
- L199 _public member_ `FIntPoint PlaneSize;` — Width and height of each tile in pixels
- L202 _public member_ `int32 NumChannels;` — Number of channels in the tiles. Typical will be 3 (RGB).
- L205 _public member_ `float AccumulationGamma;` — Gamma for accumulation. Typical values are 1.0 and 2.2.
- L213 _public member_ `TArray64<float> UnpackedDataStorage[4];` — A temporary buffer that is only initialized to the size of a single sample used during RGBA unpacking. We persist it as a member level variable to avoid having to allocate/free it for every sample (which is about a 32mb allocation at 4k) as that is quite slow.
- L218 _public member_ `TArray64<float> WeightChannelStorage;` — A temporary buffer that is only initialized to the size of a single sample used during weight plane accumulation. It is currently filled with 1.0f for all weights, and exists so that we can use the same code as we do for RGBA accumulation.
- L220 _public member_ `TArray64<FImageOverlappedPlane> ChannelPlanes;`
- L222 _public member_ `FImageOverlappedPlane WeightPlane;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MovieRenderPipelineCoreModule.h` (Public)


#### class `UMovieRenderPipelineNamingTokens`  
`class UMovieRenderPipelineNamingTokens final: public UNamingTokens`  
_L30-48_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `UNamingTokens`
- desc: Naming Tokens for Movie Render Pipeline.
- L36 _public member_ `static inline const FString TokenNamespace = TEXT("mrg` — The namespace that all MRG tokens are included under within the Naming Tokens system.
- L38 _public function_ `UMovieRenderPipelineNamingTokens()`
- L45 _public function_ `virtual ~UMovieRenderPipelineNamingTokens() override`

#### struct `FMoviePipelineLightweightTickInfo`  
`struct FMoviePipelineLightweightTickInfo`  
_L54-68_
- desc: Movie pipeline tick information Used by external consumers, like Niagara, to query information
- L56 _public function_ `FMoviePipelineLightweightTickInfo() : bIsActive(false) , TemporalSampleCount(1) , TemporalSampleIndex(0) , SequenceFPS(0.0)`
- L64 _public member_ `bool bIsActive;`
- L65 _public member_ `int32 TemporalSampleCount;`
- L66 _public member_ `int32 TemporalSampleIndex;`
- L67 _public member_ `double SequenceFPS;`

#### class `FMovieRenderPipelineCoreModule`  
`class FMovieRenderPipelineCoreModule : public IModuleInterface`  
_L82-121_
- inherits: `IModuleInterface`
- L85 _public prototype_ `virtual void StartupModule() override;`
- L86 _public prototype_ `virtual void ShutdownModule() override;`
- L88 _public prototype_ `static void SetTickInfo(const FMoviePipelineLightweightTickInfo& InTickInfo);`
- L89 _public function_ `const FMoviePipelineLightweightTickInfo& GetTickInfo() const`
- L92 _private prototype_ `bool IsTryingToRenderMovieFromCommandLine(FString& OutSequenceAssetPath, FString& OutConfigAssetPath, FString& OutExecutorType, FString& OutPipelineType) const;`
- L93 _private prototype_ `void OnMapLoadFinished(class UWorld* InWorld);`
- L94 _private prototype_ `void QueueInitialize(class UWorld* InWorld);`
- L95 _private prototype_ `void InitializeCommandLineMovieRender();`
- L97 _private prototype_ `void OnCommandLineMovieRenderCompleted(UMoviePipelineExecutorBase* InExecutor, bool bSuccess);`
- L98 _private prototype_ `void OnCommandLineMovieRenderErrored(UMoviePipelineExecutorBase* InExecutor, UMoviePipeline* InPipelineWithError, bool bIsFatal, FText ErrorText);`
- L100 _private prototype_ `uint8 ParseMovieRenderData(const FString& InSequenceAssetPath, const FString& InConfigAssetPath, const FString& InExecutorType, const FString& InPipelineType, UMoviePipelineQueue*& OutQueue, UMoviePipelineExecutorBase*& OutExecutor) const;`
- L104 _private prototype_ `void BindToNamingTokenEvents();` — Setup bindings to MRQ Naming Tokens.
- L107 _private prototype_ `void OnMovieRenderPipelineNamingTokensPreEvaluate(const FNamingTokensEvaluationData& InEvaluationData);` — Executes every time Naming Tokens are fetched.
- L111 _private member_ `static FGuid NamingTokensGuid;` — The GUID that the Naming Tokens system has assigned to the MRQ naming tokens.
- L114 _private member_ `static TWeakObjectPtr<UNamingTokens> NamingTokens;` — Naming Tokens object for MRQ.
- L116 _private member_ `FMoviePipelineLightweightTickInfo TickInfo;`
- L117 _private member_ `FString MoviePipelineLocalExecutorClassType;`
- L118 _private member_ `FString MoviePipelineClassType;`
- L119 _private member_ `FString SequenceAssetValue;`
- L120 _private member_ `FString SettingsAssetValue;`

#### class `IMoviePipelineBurnInExtension`  
`class IMoviePipelineBurnInExtension : public IModularFeature`  
_L123-130_
- inherits: `IModularFeature`
- L126 _public prototype_ `virtual ~IMoviePipelineBurnInExtension() = default;`
- L127 _public member_ `static FName ModularFeatureName;`
- L129 _public function_ `virtual FText GetEngineChangelistLabel() const`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L24 _delegate_ `DECLARE_STATS_GROUP(TEXT("MovieRenderPipeline"), STATGROUP_MoviePipeline,` — Declare a stat-group for our performance stats to be counted under, readable in game by "stat MovieRenderPipeline".
- L70 _namespace_ `namespace MoviePipelineErrorCodes`
- L73 _variable_ `constexpr uint8 Success = 0;` (scope `MoviePipelineErrorCodes`) — Everything completed as expected or we (unfortunately) couldn't detect the error.
- L75 _variable_ `constexpr uint8 Critical = 1;` (scope `MoviePipelineErrorCodes`) — Fallback for any generic critical failure. This should be used for "Unreal concepts aren't working as expected" severity errors.
- L77 _variable_ `constexpr uint8 NoAsset = 2;` (scope `MoviePipelineErrorCodes`) — The specified level sequence asset could not be found. Check the logs for details on what it looked for.
- L79 _variable_ `constexpr uint8 NoConfig = 3;` (scope `MoviePipelineErrorCodes`) — The specified pipeline configuration asset could not be found. Check the logs for details on what it looked for.
- L132 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMovieRenderPipeline, Log, All);`
- L133 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMovieRenderPipelineIO, Log, All);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MovieRenderPipelineCoreObjectVersion.h` (Public)


#### struct `FMovieRenderPipelineCoreObjectVersion`  
`struct FMovieRenderPipelineCoreObjectVersion`  
_L11-34_
- desc: Custom serialization version for changes made to Movie Render Pipeline Core objects.
- L31 _public member_ `static const FGuid GUID;`
- L33 _public prototype_ `FMovieRenderPipelineCoreObjectVersion() = delete;`

#### enum `FMovieRenderPipelineCoreObjectVersion::Type`  
`enum Type : int32`  
_L13-29_
- L15 _public enumerator_ `PreVersioning = 0`
- L18 _public enumerator_ `OnlyMatchComponentsAdded` — Added bOnlyMatchComponents to some conditions within graph collections, defaulting to true.
- L21 _public enumerator_ `JobConfigModeAdded` — Added EMoviePipelineConfigMode to UMoviePipelineExecutorJob. Pre-existing assets derive the mode from pointer state in Serialize().
- L24 _public enumerator_ `JobInitializedLegacyDefaultsTrackingAdded` — Added bHasInitializedLegacyPresetDefaults to UMoviePipelineExecutorJob. Pre-existing assets backfill the flag to "true".
- L27 _public enumerator_ `VersionPlusOne` — --- Add new versions above this line ---
- L28 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MovieRenderPipelineDataTypes.h` (Public)


#### enum `EMovieRenderPipelineState`  
`enum class EMovieRenderPipelineState : uint8`  
_L52-64_
- reflection: `UENUM(BlueprintType)`
- desc: What is the current overall state of the Pipeline? States are processed in order from first to last and all states will be hit (though there is no guarantee the state will not be transitioned away from on the same frame it entered it). Used to help track overall progress and validate code flow.
- L55 _public enumerator_ `Uninitialized = 0` — The pipeline has not been initialized yet. Only valid operation is to call Initialize.
- L57 _public enumerator_ `ProducingFrames = 1` — The pipeline has been initialized and is now controlling time and working on producing frames.
- L59 _public enumerator_ `Finalize = 2` — All desired frames have been produced. Audio is already finalized. Outputs have a chance to finish long processing tasks.
- L61 _public enumerator_ `Export = 3` — All outputs have finished writing to disk or otherwise processing. Additional exports that may have needed information about the produced file can now be run.
- L63 _public enumerator_ `Finished = 4` — The pipeline has been shut down. It is an error to shut it down again.

#### enum `EMovieRenderShotState`  
`enum class EMovieRenderShotState : uint8`  
_L72-100_
- reflection: `UENUM(BlueprintType)`
- desc: What is the current state of a shot? States are processed in order from first to last but not all states are required, ie: WarmUp and MotionBlur can be disabled and the shot will never pass through this state.
- L75 _public enumerator_ `Uninitialized = 0` — The shot has not been initialized yet.
- L78 _public enumerator_ `WarmingUp = 1` — The shot is warming up. Engine ticks are passing but no frames are being produced.
- L83 _public enumerator_ `MotionBlur = 2` — The shot is doing additional pre-roll for motion blur. No frames are being produced, but the rendering pipeline is being run to seed histories.
- L88 _public enumerator_ `Rendering = 3` — The shot is working on producing frames and may be currently doing a sub-frame or a whole frame.
- L94 _public enumerator_ `CoolingDown = 4` — The shot is cooling down. Engine ticks are passing and frames are being rendered, but not saved to disk. This is needed because temporal-based denoisers need to look at the future (which would be after a shot) to finish the current frames of the shot.
- L99 _public enumerator_ `Finished = 5` — The shot has produced all frames it will produce. No more evaluation should be done for this shot once it reaches this state.

#### struct `FMoviePipelinePassIdentifier`  
`struct FMoviePipelinePassIdentifier`  
_L103-146_
- reflection: `USTRUCT(BlueprintType)`
- L107 _public function_ `FMoviePipelinePassIdentifier()`
- L111 _public function_ `FMoviePipelinePassIdentifier(const FString& InPassName, const FString& InCameraName = TEXT("camera")) : Name(InPassName) , CameraName(InCameraName)` — Name defaults to "camera" for backwards compatiblity with non-multicam metadata
- L117 _public function_ `bool operator == (const FMoviePipelinePassIdentifier& InRHS) const`
- L122 _public function_ `bool operator != (const FMoviePipelinePassIdentifier& InRHS) const`
- L140 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Pipeline")` — The name of the pass such as "FinalImage" or "ObjectId", etc.
- L145 _public member_ `FString CameraName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Pipeline")` — The name of the camera that this pass is for. Stored here so we can differentiate between multiple cameras within a single pass.

#### struct `FMoviePipelineConsoleVariableEntry`  
`struct FMoviePipelineConsoleVariableEntry`  
_L152-170_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a console variable override that can be enabled/disabled.
- L156 _public prototype_ `FMoviePipelineConsoleVariableEntry(const FString& InName, const float InValue, const bool bInIsEnabled = true);`
- L157 _public prototype_ `FMoviePipelineConsoleVariableEntry();`
- L161 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — The name of the console variable.
- L165 _public member_ `float Value;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — The value of the console variable.
- L169 _public member_ `bool bIsEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — Enable state. If disabled, this cvar entry will be ignored when resolving the final value of the cvar.

#### struct `MoviePipeline::FMoviePipelineFrameInfo`  
`struct FMoviePipelineFrameInfo`  
_L177-204_
- desc: Frame info needed for creating the FSceneView for each tile.
- L180 _public function_ `FMoviePipelineFrameInfo()`
- L181 _public prototype_ `virtual ~FMoviePipelineFrameInfo() = default;`
- L189 _public member_ `FVector CurrViewLocation;` — Current frame camera view location
- L192 _public member_ `FRotator CurrViewRotation;` — Current frame camera view rotation
- L195 _public member_ `FVector PrevViewLocation;` — Previous frame camera view location
- L198 _public member_ `FRotator PrevViewRotation;` — Previous frame camera view rotation
- L200 _public member_ `TArray<FVector> CurrSidecarViewLocations;`
- L201 _public member_ `TArray<FRotator> CurrSidecarViewRotations;`
- L202 _public member_ `TArray<FVector> PrevSidecarViewLocations;`
- L203 _public member_ `TArray<FRotator> PrevSidecarViewRotations;`

#### struct `MoviePipeline::FFrameTimeStepCache`  
`struct FFrameTimeStepCache`  
_L210-221_
- desc: Utility function for the Pipeline to calculate the time metrics for the current frame that can then be used by the custom time step to avoid custom time logic.
- L212 _public function_ `FFrameTimeStepCache() : UndilatedDeltaTime(0.0)`
- L216 _public function_ `FFrameTimeStepCache(double InDeltaTime) : UndilatedDeltaTime(InDeltaTime)`
- L220 _public member_ `double UndilatedDeltaTime;`

#### struct `MoviePipeline::FOutputFrameData`  
`struct FOutputFrameData`  
_L223-230_
- L225 _public member_ `FIntPoint Resolution;`
- L227 _public member_ `TArray<FColor> ColorBuffer;`
- L229 _public member_ `FString PassName;`

#### struct `MoviePipeline::FTileWeight1D`  
`struct FTileWeight1D`  
_L232-297_
- L255 _public function_ `FTileWeight1D()` — Constructor. Sets to invalid values and must be initialized to reasonable values before using.
- L264 _public function_ `void CheckValid() const` — Make sure this map has valid values.
- L273 _public prototype_ `bool operator==(const FTileWeight1D& Rhs) const;` — Is equal operator.
- L287 _public prototype_ `void InitHelper(int32 PadLeft, int32 SizeCenter, int32 PadRight);` — The full tile is of size PadLeft + SizeCenter + PadRight |------PadLeft-------|------------SizeCenter-----------|------PadRight-----| This function puts X0 in the middle of PadLeft, X3 in the middle of PadRight. And X1 is "reflected" around PadLeft, and X2 is "reflected" around PadRight. |------PadLeft-------|------------SizeCenter-----------|------PadRight-----| X0                  X1                  X2              X3 Also note that PadLeft and PadRight are allowed to be zero, but SizeCenter must be > 0;
- L289 _public prototype_ `float CalculateWeight(int32 Pixel) const;`
- L291 _public prototype_ `void CalculateArrayWeight(TArray<float>& WeightData, int Size) const;`
- L293 _public member_ `int32 X0;`
- L294 _public member_ `int32 X1;`
- L295 _public member_ `int32 X2;`
- L296 _public member_ `int32 X3;`

#### struct `MoviePipeline::FFrameConstantMetrics`  
`struct FFrameConstantMetrics`  
_L299-340_
- L302 _public member_ `FFrameRate TickResolution;` — What is the tick resolution of the root sequence
- L304 _public member_ `FFrameRate ShotTickResolution;` — What is the tick resolution of the current shot
- L306 _public member_ `FFrameRate FrameRate;` — What is the effective frame rate of the output
- L308 _public member_ `FFrameTime TicksPerOutputFrame;` — How many ticks per output frame.
- L310 _public member_ `FFrameTime TicksPerSample;` — How many ticks per sub-frame sample.
- L312 _public member_ `FFrameTime TicksWhileShutterClosed;` — How many ticks while the shutter is closed
- L314 _public member_ `FFrameTime TicksWhileShutterOpen;` — How many ticks while the shutter is opened
- L317 _public member_ `double ShutterAnglePercentage;` — Fraction of the output frame that the accumulation frames should cover.
- L320 _public member_ `double ShutterClosedFraction;` — Fraction of the output frame that the shutter is closed (that accumulation frames should NOT cover).
- L326 _public member_ `FFrameTime ShutterOffsetTicks;` — Our time samples are offset by this many ticks. For a given output frame N, we can bias the time N represents to be before, during or after the data stored on time N.
- L332 _public member_ `FFrameTime MotionBlurCenteringOffsetTicks;` — How many ticks do we have to go to center our motion blur? This makes it so the blurred area matches the object position during the time it represents, and not before.
- L334 _public function_ `FFrameTime GetFinalEvalTime(const FFrameNumber InTime) const`

#### struct `MoviePipeline::FCameraCutSubSectionHierarchyNode`  
`struct FCameraCutSubSectionHierarchyNode : TSharedFromThis<FCameraCutSubSectionHierarchyNode>`  
_L342-455_
- inherits: `TSharedFromThis<FCameraCutSubSectionHierarchyNode>`
- L344 _public function_ `FCameraCutSubSectionHierarchyNode() : bOriginalMovieSceneReadOnly(false) , bOriginalMovieScenePlaybackRangeLocked(false) , bOriginalMovieScenePackageDirty(false) , bOriginalShotSectionIsLocked(false) , bOriginalCameraCutIsActive(false) , bOriginalShotSectionIsActive(false) , OriginalSequenceFlags(EMovieSceneSequenceFlags::None) , EvaluationType(EMovieSceneEvaluationType::WithSubFrames) , NodeID(MovieSceneSequenceID::Invalid)`
- L358 _public member_ `TWeakObjectPtr<class UMovieScene> MovieScene;` — The UMovieScene that this node has data for.
- L360 _public member_ `TWeakObjectPtr<class UMovieSceneSubSection> Section;` — The UMovieSceneSubSection within the movie scene (if any)
- L362 _public member_ `TWeakObjectPtr<class UMovieSceneCameraCutSection> CameraCutSection;` — The UMovieSceneCameraCutSection within the movie scene (if any)
- L365 _public member_ `TRange<FFrameNumber> OriginalMovieScenePlaybackRange;` — These are used to restore this node back to its proper shape post render.
- L366 _public member_ `bool bOriginalMovieSceneReadOnly;`
- L367 _public member_ `bool bOriginalMovieScenePlaybackRangeLocked;`
- L368 _public member_ `bool bOriginalMovieScenePackageDirty;`
- L370 _public member_ `bool bOriginalShotSectionIsLocked;`
- L371 _public member_ `TRange<FFrameNumber> OriginalShotSectionRange;`
- L372 _public member_ `TRange<FFrameNumber> OriginalCameraCutSectionRange;`
- L374 _public member_ `bool bOriginalCameraCutIsActive;`
- L375 _public member_ `bool bOriginalShotSectionIsActive;`
- L376 _public member_ `EMovieSceneSequenceFlags OriginalSequenceFlags;`
- L379 _public member_ `TArray<TTuple<UMovieSceneSection*, TRange<FFrameNumber>>> AdditionalSectionsToExpand;` — An array of sections that we should expand, as well as their original range for restoration later.
- L381 _public member_ `EMovieSceneEvaluationType EvaluationType;`
- L382 _public member_ `FMovieSceneSequenceID NodeID;`
- L384 _public function_ `void AddChild(TSharedPtr<FCameraCutSubSectionHierarchyNode> InChild)`
- L395 _public function_ `TArray<TSharedPtr<FCameraCutSubSectionHierarchyNode>> GetChildren() const`
- L400 _public function_ `void SetParent(TSharedPtr<FCameraCutSubSectionHierarchyNode> InParent)`
- L418 _public function_ `bool IsEmpty() const`
- L423 _public function_ `TSharedPtr<FCameraCutSubSectionHierarchyNode> GetParent() const`
- L427 _private member_ `TSharedPtr<FCameraCutSubSectionHierarchyNode> Parent;` — A pointer to the next node in the tree who actually includes us in the hierarchy. Different than outers as each moviescene is outered to its own package.
- L429 _private member_ `TArray<TSharedPtr<FCameraCutSubSectionHierarchyNode>> Children;` — An array of pointers to our children for downwards traversal.
- L431 _private function_ `bool operator == (const FCameraCutSubSectionHierarchyNode& InRHS) const`
- L451 _private function_ `bool operator != (const FCameraCutSubSectionHierarchyNode& InRHS) const`

#### struct `MoviePipeline::FClothSimSettingsCache`  
`struct FClothSimSettingsCache`  
_L457-461_
- L459 _public member_ `int32 NumSubSteps;`
- L460 _public member_ `float DynamicSubstepDeltaTime;`

#### struct `FMoviePipelineSegmentWorkMetrics`  
`struct FMoviePipelineSegmentWorkMetrics`  
_L465-509_
- reflection: `USTRUCT(BlueprintType)`
- L470 _public function_ `FMoviePipelineSegmentWorkMetrics() : SegmentName() , OutputFrameIndex(-1) , TotalOutputFrameCount(-1) , OutputSubSampleIndex(-1) , TotalSubSampleCount(-1) , EngineWarmUpFrameIndex(-1) , TotalEngineWarmUpFrameCount(-1)`
- L484 _public member_ `FString SegmentName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pipeline Segment")` — The name of the segment (if any)
- L488 _public member_ `int32 OutputFrameIndex;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pipeline Segment")` — Index of the output frame we are working on right now.
- L491 _public member_ `int32 TotalOutputFrameCount;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pipeline Segment")` — The number of output frames we expect to make for this segment.
- L496 _public member_ `int32 OutputSubSampleIndex;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pipeline Segment")` — Which temporal/spatial sub sample are we working on right now. This counts temporal, spatial, and tile samples to accurately reflect how much work is needed for this output frame.
- L500 _public member_ `int32 TotalSubSampleCount;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pipeline Segment")` — The total number of samples we will have to build to render this output frame.
- L504 _public member_ `int32 EngineWarmUpFrameIndex;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pipeline Segment")` — The index of the engine warm up frame that we are working on. No rendering samples are produced for these.
- L508 _public member_ `int32 TotalEngineWarmUpFrameCount;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pipeline Segment")` — The total number of engine warm up frames for this segment.

#### enum `EMoviePipelineShutterTiming`  
`enum class EMoviePipelineShutterTiming : uint8`  
_L513-518_
- reflection: `UENUM(BlueprintType)`
- L515 _public enumerator_ `FrameOpen`
- L516 _public enumerator_ `FrameCenter`
- L517 _public enumerator_ `FrameClose`

#### struct `FMoviePipelineCameraCutInfo`  
`struct FMoviePipelineCameraCutInfo`  
_L522-618_
- reflection: `USTRUCT(BlueprintType)`
- desc: ToDo: Rename this to segment.
- L526 _public function_ `FMoviePipelineCameraCutInfo() : bEmulateFirstFrameMotionBlur(true) , NumTemporalSamples(0) , NumSpatialSamples(0) , NumTiles(0, 0) , State(EMovieRenderShotState::Uninitialized) , bHasEvaluatedMotionBlurFrame(false) , NumEngineWarmUpFramesRemaining(0) , NumEngineCoolDownFramesRemaining(0) , bNeedsAudioResetOnRenderStart(false) , VersionNumber(0)`
- L540 _public function_ `bool IsInitialized() const`
- L541 _public prototype_ `void SetNextStateAfter(const EMovieRenderShotState InCurrentState);`
- L542 _public prototype_ `void CalculateWorkMetrics();`
- L545 _private prototype_ `FFrameNumber GetOutputFrameCountEstimate() const;`
- L549 _public member_ `TSharedPtr<MoviePipeline::FCameraCutSubSectionHierarchyNode> SubSectionHierarchy;`
- L556 _public member_ `bool bEmulateFirstFrameMotionBlur;` — Should we evaluate/render an extra frame at the start of this shot to show correct motion blur on the first frame? This emulates motion blur by evaluating forward one frame and then going backwards which is a approximation.
- L559 _public member_ `int32 NumTemporalSamples;` — How many temporal samples is each frame broken up into?
- L562 _public member_ `int32 NumSpatialSamples;` — For each temporal sample, how many spatial samples do we take?
- L565 _public member_ `FIntPoint NumTiles;` — How many image tiles are going to be rendered per temporal frame.
- L568 _public member_ `FFrameRate CachedFrameRate;` — Cached Frame Rate these are being rendered at. Simplifies some APIs.
- L571 _public member_ `FFrameRate CachedTickResolution;` — Cached Tick Resolution our numbers are in. Simplifies some APIs.
- L574 _public member_ `FFrameRate CachedShotTickResolution;` — Cached Tick Resolution the movie scene this range was generated for is in. Can be different than the root due to mixed tick resolutions.
- L577 _public member_ `EMovieRenderShotState State;` — The current state of processing this Shot is in. Not all states will be passed through.
- L580 _public member_ `FFrameNumber CurrentTickInRoot;` — The current tick of this shot that we're on in root space
- L583 _public member_ `FFrameTime CurrentTimeInRoot;` — The current time of this shot that we're on in root space (for the Graph version. Tracks sub-frames too.)
- L586 _public member_ `FFrameTime InitialTimeInRoot;` — The initial time in the root space for this shot when we started evaluating. Only assigned in the Graph version of MRQ. Effectively the same as CurrentTimeInRoot, but is immutable during the shot.
- L588 _public member_ `FFrameTime InitialTimeInShot;` — The initial time in the shot time space for this shot when we started evaluating. Only assigned in the Graph version of MRQ. Effectively the same as CurrentTimeInRoot * OuterToInnerTransform, but is immutable during the shot.
- L591 _public member_ `FMovieSceneSequenceTransform OuterToInnerTransform;` — Converts from the outermost space into the innermost space. Only works with linear transforms.
- L594 _public member_ `TRange<FFrameNumber> TotalOutputRangeRoot;` — The total range of output frames in root space
- L597 _public member_ `TRange<FFrameNumber> WarmupRangeRoot;` — The total range of warmup frames in root space
- L600 _public member_ `FMoviePipelineSegmentWorkMetrics WorkMetrics;` — Metrics - How much work has been done for this particular shot and how much do we estimate we have to do?
- L603 _public member_ `bool bHasEvaluatedMotionBlurFrame;` — Have we evaluated the motion blur frame? Only used if bEvaluateMotionBlurOnFirstFrame is set
- L606 _public member_ `int32 NumEngineWarmUpFramesRemaining;` — How many engine warm up frames are left to process for this shot. May be zero.
- L609 _public member_ `int32 NumEngineCoolDownFramesRemaining;` — How many cool down frames for this shot. May be zero.
- L613 _public member_ `bool bNeedsAudioResetOnRenderStart;` — If true, the first rendering frame will issue a sequencer jump to reset procedural audio generators (e.g. MetaSound) that advanced their internal state during non-emulated warm-up.
- L617 _public member_ `int32 VersionNumber;` — What version number should this shot use when resolving format arguments. This is the highest version number found across all branches.

#### struct `FMoviePipelineFrameOutputState`  
`struct FMoviePipelineFrameOutputState`  
_L626-828_
- desc: The Tick/Render loops are decoupled from the actual desired output. In some cases we may render but not desire an output (such as filling temporal histories) or we may be accumulating the results into a target which does not produce an output. Finally, we may be running the Tick/Render loop but not wanting to do anything!
- L664 _public function_ `FMoviePipelineFrameOutputState() : OutputFrameNumber(-1) , ShotCount(0) , TemporalSampleIndex(-1) , TemporalSampleCount(0)`
- L681 _public function_ `inline bool IsFirstTemporalSample() const` — Is this the first temporal sample for the output frame?
- L682 _public function_ `inline bool IsLastTemporalSample() const`
- L690 _public member_ `int32 OutputFrameNumber;` — The expected output frame count that the render is working towards creating. This number accurately tracks the number of frames we have produced even if the file written to disk uses a different number (due to relative frame numbers or offset frames being added.
- L693 _public member_ `int32 ShotIndex;` — Which shot is this output state for?
- L696 _public member_ `int32 ShotCount;` — How many shots total will we be outputting?
- L699 _public member_ `int32 TemporalSampleIndex;` — Which sub-frame are we on when using Accumulation Frame rendering.
- L702 _public member_ `int32 TemporalSampleCount;` — How many temporal samples do we add together to produce one Output Frame?
- L708 _public member_ `int32 ShotOutputFrameNumber;` — The expected output frame count for this current shot that we're working towards creating. Like OutputFrameNumber but relative to this shot. This should get reset between shots.
- L711 _public member_ `int32 ShotSamplesRendered;` — The total number of samples (including warm ups) that have been sent to the GPU for this shot.
- L714 _public member_ `FTimeData TimeData;` — What time data should this frame use? Can vary between samples when TemporalSampleCount > 1.
- L717 _public member_ `FString CameraName;` — The name of the currently active camera being rendered. May be empty.
- L720 _public member_ `FString CameraNameOverride;` — Name used by the {camera_name} format tag. May be empty
- L723 _public member_ `FString ShotName;` — THe name of the currently active shot. May be empty if there is no shot track.
- L727 _public function_ `void ResetPerFrameData()`
- L742 _public function_ `void ResetPerShotData()`
- L757 _public member_ `bool bSkipRendering;` — If true, then the rendering for this frame should be skipped (ie: nothing submitted to the gpu, and the output merger not told to expect this frame). This is used for rendering every Nth frame for rendering drafts. We still run the game thread logic for the skipped frames (which is relatively cheap) and simply omit rendering them. This increases consistency with non-skipped renders, and will be useful for consistency when rendering on a farm.
- L762 _public member_ `bool bCaptureRendering;` — If true, and a IRenderCaptureProvider is available, trigger a capture of the rendering process of this frame.
- L768 _public member_ `bool bDiscardRenderResult;` — If this is true, then the frame will be rendered but the results discarded and not sent to the accumulator. This is used for render warmup frames or gpu-based feedback loops. Ignored if bSkipRendering is true.
- L772 _public member_ `int32 SourceFrameNumber;` — The closest frame number (in Display Rate) on the Sequence. May be duplicates in the case of different output framerate or Play Rate tracks.
- L775 _public member_ `FTimecode SourceTimeCode;` — The closest time code version of the SourceFrameNumber on the Sequence. May be a duplicate in the case of different output framerate or Play Rate tracks.
- L781 _public member_ `int32 EffectiveFrameNumber;` — The closest frame number (in Display Rate) on the Sequence adjusted for the effective output rate. These numbers will not line up with the frame in the source Sequence if the output frame rate differs from the Sequence display rate. May be a duplicate in the event of Play Rate tracks.
- L784 _public member_ `FTimecode EffectiveTimeCode;` — The closest time code version of the EffectiveFrameNumber. May be a duplicate in the event of Play Rate tracks.
- L787 _public member_ `TMap<FString, FString> FileMetadata;` — Metadata to attach to the output file (if supported by the output container)
- L790 _public member_ `int32 CurrentShotSourceFrameNumber;`
- L792 _public member_ `FTimecode CurrentShotSourceTimeCode;`
- L794 _public member_ `int32 CameraIndex;`
- L797 _public function_ `bool operator == (const FMoviePipelineFrameOutputState& InRHS) const`
- L814 _public function_ `bool operator != (const FMoviePipelineFrameOutputState& InRHS) const`
- L819 _public function_ `bool operator < (const FMoviePipelineFrameOutputState& InRHS) const`

#### struct `FMoviePipelineFrameOutputState::FTimeData`  
`struct FTimeData`  
_L629-662_
- L631 _public function_ `FTimeData() : MotionBlurFraction(0.f) , FrameDeltaTime(0.0) , WorldSeconds(0.0) , TimeDilation(1.f)`
- L640 _public member_ `float MotionBlurFraction;` — A 0-1 fraction of how much motion blur should be applied. This is tied to the shutter angle but more complicated when using sub-sampling
- L643 _public member_ `double FrameDeltaTime;` — The delta time in seconds used for this frame.
- L646 _public member_ `double WorldSeconds;` — The total elapsed time since the pipeline started.
- L652 _public member_ `float TimeDilation;` — Check if there was a non-1.0 Time Dilation in effect when this frame was produced. This indicates that there may be duplicate frame Source/Effective frame numbers as they find the closest ideal time to the current.
- L654 _public function_ `void ResetPerFrameData()`
- L661 _public function_ `inline bool IsTimeDilated() const`

#### struct `FMoviePipelineFormatArgs`  
`struct FMoviePipelineFormatArgs`  
_L831-851_
- reflection: `USTRUCT(BlueprintType)`
- L835 _public function_ `FMoviePipelineFormatArgs() : InJob(nullptr)`
- L842 _public member_ `TMap<FString, FString> FilenameArguments;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — A set of Key/Value pairs for output filename format strings (without {}) and their values.
- L846 _public member_ `TMap<FString, FString> FileMetadata;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — A set of Key/Value pairs for file metadata for file formats that support metadata.
- L850 _public member_ `TObjectPtr<class UMoviePipelineExecutorJob> InJob;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — Which job is this for? Some settings are specific to the level sequence being rendered.

#### struct `FMoviePipelineFilenameResolveParams`  
`struct FMoviePipelineFilenameResolveParams`  
_L854-947_
- reflection: `USTRUCT(BlueprintType)`
- L858 _public function_ `FMoviePipelineFilenameResolveParams() : FrameNumber(0) , FrameNumberShot(0) , FrameNumberRel(0) , FrameNumberShotRel(0) , ZeroPadFrameNumberCount(0) , bForceRelativeFrameNumbers(false) , InitializationTime(0) , InitializationVersion(0) , Job(nullptr) , CameraIndex(-1) , ShotOverride(nullptr) , AdditionalFrameNumberOffset(0)`
- L876 _public member_ `int32 FrameNumber;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — Frame Number for the Root (matching what you see in the Sequencer timeline. ie: If the Sequence PlaybackRange starts on 50, this value would be 50 on the first frame.
- L880 _public member_ `int32 FrameNumberShot;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — Frame Number for the Shot (matching what you would see in Sequencer at the sub-sequence level.
- L884 _public member_ `int32 FrameNumberRel;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — Frame Number for the Root (relative to 0, not what you would see in the Sequencer timeline. ie: If sequence PlaybackRange starts on 50, this value would be 0 on the first frame.
- L888 _public member_ `int32 FrameNumberShotRel;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — Frame Number for the Shot (relative to 0, not what you would see in the Sequencer timeline.
- L892 _public member_ `FString CameraNameOverride;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — Name used by the {camera_name} format tag. If specified, this will override the camera name (which is normally pulled from the ShotOverride object).
- L896 _public member_ `FString ShotNameOverride;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — Name used by the {shot_name} format tag. If specified, this will override the shot name (which is normally pulled from the ShotOverride object)
- L900 _public member_ `int32 ZeroPadFrameNumberCount;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — When converitng frame numbers to strings, how many digits should we pad them up to? ie: 5 => 0005 with a count of 4.
- L904 _public member_ `bool bForceRelativeFrameNumbers;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — If true, force format strings (like {frame_number}) to resolve using the relative version. Used when slow-mo is detected as frame numbers would overlap.
- L908 _public member_ `FString FileNameOverride;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — Optional. If specified this is the filename that will be used instead of automatically building it from the Job's Output Setting.
- L915 _public member_ `TMap<FString, FString> FileNameFormatOverrides;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — A map between "{format}" tokens and their values. These are applied after the auto-generated ones from the system, which allows the caller to override things like {.ext} depending or {render_pass} which have dummy names by default.
- L919 _public member_ `TMap<FString, FString> FileMetadata;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — A key/value pair that maps metadata names to their values. Output is only supported in exr formats at the moment.
- L923 _public member_ `FDateTime InitializationTime;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — The initialization time for this job. Used to resolve time-based format arguments.
- L927 _public member_ `FTimespan InitializationTimeOffset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — What offset should be applied to InitializationTime when generating {time} related filename tokens? Likely your offset from UTC if you want local time.
- L931 _public member_ `int32 InitializationVersion;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — The version for this job. Used to resolve version format arguments.
- L935 _public member_ `TObjectPtr<UMoviePipelineExecutorJob> Job;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — Required. This is the job all of the settings should be pulled from.
- L938 _public member_ `int32 CameraIndex;` — If this shot has multiple cameras in the sidecar array, which camera is this for? -1 will return the InnerName/Main camera for the shot.
- L942 _public member_ `TObjectPtr<UMoviePipelineExecutorShot> ShotOverride;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — Optional. If specified, settings will be pulled from this shot (if overriden by the shot). If null, always use the root configuration in the job.
- L946 _public member_ `int32 AdditionalFrameNumberOffset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Render Pipeline")` — Additional offset added onto the offset provided by the Output Settings in the Job. Required for some internal things (FCPXML).

#### struct `FMoviePipelineRenderPassMetrics`  
`struct FMoviePipelineRenderPassMetrics`  
_L952-1099_
- desc: These parameters define a single sample that a render pass should render with.
- L957 _public prototype_ `FMoviePipelineRenderPassMetrics() = default;` — Manual default constructors to avoid deprecation warnings/errors on EffectiveOutputResolution
- L958 _public prototype_ `~FMoviePipelineRenderPassMetrics() = default;`
- L959 _public prototype_ `FMoviePipelineRenderPassMetrics(const FMoviePipelineRenderPassMetrics&) = default;`
- L960 _public prototype_ `FMoviePipelineRenderPassMetrics(FMoviePipelineRenderPassMetrics&&) = default;`
- L961 _public prototype_ `FMoviePipelineRenderPassMetrics& operator=(const FMoviePipelineRenderPassMetrics&) = default;`
- L962 _public prototype_ `FMoviePipelineRenderPassMetrics& operator=(FMoviePipelineRenderPassMetrics&&) = default;`
- L966 _public member_ `int32 FrameIndex;` — What FrameIndex should the FSceneView use for its internal index. Used to ensure samples have unique TAA/Raytracing/etc. sequences
- L969 _public member_ `bool bWorldIsPaused;` — Is the Scene View frozen so no changes are made as a result of this sample?
- L972 _public member_ `bool bCameraCut;` — Do we pass the camera cut flag to the renderer to clear histories?
- L975 _public member_ `EAntiAliasingMethod AntiAliasingMethod;` — Which anti-aliasing method should this view use?
- L978 _public member_ `ESceneCaptureSource SceneCaptureSource;` — What type of output should the Post Processing output? (HDR /w ToneCurve, HDR w/o ToneCurve)
- L981 _public member_ `FIntPoint OriginalTileCounts;` — How many tiles on X and Y are there total.
- L984 _public member_ `FIntPoint TileCounts;` — How many tiles on X and Y are there total.
- L987 _public member_ `FIntPoint TileIndexes;` — Of the TileCount, which X/Y Tile is this sample for.
- L990 _public member_ `float SpatialShiftX;` — SpatialJitter offset X.
- L993 _public member_ `float SpatialShiftY;` — SpatialJitter offset Y.
- L997 _public function_ `inline int32 GetTileIndex() const` — Get a 0-(TileCount-1) version of TileIndex.
- L1002 _public function_ `inline int32 GetTileCount() const`
- L1008 _public member_ `FIntPoint BackbufferSize;` — How big is the back buffer for this sample? This is the final target size divided by the number of tiles with padding added.
- L1012 _public member_ `FIntPoint EffectiveOutputResolution;` — `UE_DEPRECATED(5.6, "EffectiveOutputResolution is deprecated. Use OverscannedResolution instead")` — Full Output image resolution for this shot.
- L1015 _public member_ `FIntPoint OverscannedResolution;` — The overscanned resolution, computed by scaling the desired output resolution by any configured overscan
- L1018 _public member_ `FIntPoint TileSize;` — How big is an individual tile for this sample? This is the final target size divided by the number of tiles (without padding added)
- L1021 _public member_ `bool bDiscardResult;` — If true, we will discard this sample after rendering. Used to get history set up correctly.
- L1024 _public member_ `bool bWriteSampleToDisk;` — If true, we will write this sample to disk (and also send it to the accumulator.)
- L1027 _public member_ `int32 SpatialSampleCount;` — How many spatial jitters will there be total for this particular temporal accumulation frame?
- L1030 _public member_ `int32 SpatialSampleIndex;` — Of the SpatialSampleCount, which index is this?
- L1033 _public member_ `int32 SeedOffset;` — Offset to apply to random number generator seed.
- L1036 _public member_ `int32 TemporalSampleCount;` — How many temporal jitters will there be total for this particular output frame?
- L1039 _public member_ `int32 TemporalSampleIndex;` — Of the TemporalSampleCount, which index is this?
- L1042 _public member_ `FIntPoint OverlappedPad;` — How many pixels are we overlapping with adjacent tiles (on each side)
- L1045 _public member_ `FIntPoint OverlappedOffset;` — How much is this sample offset, taking padding into account.
- L1048 _public member_ `float OverscanPercentage;` — Use overscan percentage to extend render region beyond the set resolution.
- L1051 _public member_ `bool bOverrideCameraOverscan;` — Whether to override the camera's overscan value when rendering
- L1058 _public member_ `FIntRect CropRectangle;` — The rectangle to use to crop the image prior to compositing and output. Used to crop out overscan from appropriate formats, and will generally have size equal to the originally requested resolution, whereas internal resolutions such as Backbuffer and Accumulator resolutions will be scaled up to include overscan
- L1064 _public member_ `float AccumulationGamma;` — The gamma space to apply accumulation in. During accumulation, pow(x,AccumulationGamma) is applied and pow(x,1/AccumulationGamma) is applied after accumulation is finished. 1.0 means no change."
- L1070 _public member_ `FVector2D ProjectionMatrixJitterAmount;` — The amount of screen-space shift used to replace TAA Projection Jitter, modified for each spatial sample of the render.
- L1075 _public member_ `float TextureSharpnessBias;` — Any additional texture mip map bias that should be added when rendering. Can be used to force extra sharpness. A more negative number means more likely to use a higher quality mip map.
- L1080 _public member_ `float GlobalScreenPercentageFraction;` — What screen percentage should each view be rendered at? 1.0 = standard size. Can gain more detail (at the cost of longer renders, more device timeouts), consider trying to use TextureSharpnessBias if possible instead.
- L1085 _public member_ `bool bAutoExposureCubePass;` — Whether the auto exposure pass is an omnidirectional cube capture pass, useful for panoramic rendering.  Only set for the actual exposure pass!
- L1090 _public member_ `int8 AutoExposureCubeFace;` — Transient value set when generating an autoexposure cube face.
- L1092 _public member_ `FMoviePipelineFrameOutputState OutputState;`
- L1094 _public member_ `FVector2D OverlappedSubpixelShift;`
- L1096 _public member_ `MoviePipeline::FMoviePipelineFrameInfo FrameInfo;`
- L1098 _public member_ `FOpenColorIODisplayConfiguration* OCIOConfiguration;`

#### struct `MoviePipeline::FMoviePipelineRenderPassInitSettings`  
`struct FMoviePipelineRenderPassInitSettings`  
_L1103-1124_
- L1107 _public prototype_ `FMoviePipelineRenderPassInitSettings();` — `UE_DEPRECATED(5.0, "FMoviePipelineRenderPassInitSettings must be constructed with arguments")`
- L1109 _public function_ `FMoviePipelineRenderPassInitSettings(ERHIFeatureLevel::Type InFeatureLevel, const FIntPoint& InBackbufferResolution, const FIntPoint& InTileCount) : BackbufferResolution(InBackbufferResolution) , TileCount(InTileCount) , FeatureLevel(InFeatureLevel)`
- L1118 _public member_ `FIntPoint BackbufferResolution = FIntPoint(0, 0);` — This takes into account any padding needed for tiled rendering overlap. Different than the output resolution of the final image.
- L1121 _public member_ `FIntPoint TileCount = FIntPoint(0, 0);` — How many tiles (in each direction) are we rendering with.
- L1123 _public member_ `ERHIFeatureLevel::Type FeatureLevel;`

#### struct `MoviePipeline::FCompositePassInfo`  
`struct FCompositePassInfo`  
_L1126-1132_
- L1128 _public function_ `FCompositePassInfo()`
- L1130 _public member_ `FMoviePipelinePassIdentifier PassIdentifier;`
- L1131 _public member_ `TUniquePtr<FImagePixelData> PixelData;`

#### struct `FImagePixelDataPayload`  
`struct FImagePixelDataPayload : IImagePixelDataPayload, public TSharedFromThis<FImagePixelDataPayload, ESPMode::ThreadSafe>`  
_L1137-1220_
- inherits: `IImagePixelDataPayload,TSharedFromThis<FImagePixelDataPayload,ESPMode::ThreadSafe>`
- L1139 _public member_ `FMoviePipelineRenderPassMetrics SampleState;`
- L1141 _public member_ `FMoviePipelinePassIdentifier PassIdentifier;`
- L1144 _public member_ `bool bRequireTransparentOutput;` — Does this output data have to be transparent to be useful? Overrides output format to one that supports transparency.
- L1146 _public member_ `int32 SortingOrder;`
- L1147 _public member_ `bool bCompositeToFinalImage;`
- L1150 _public member_ `FString Debug_OverrideFilename;` — If specified, use this as the output filename (not including output directory) when using debug write samples to disk
- L1152 _public function_ `FImagePixelDataPayload() : bRequireTransparentOutput(false) , SortingOrder(TNumericLimits<int32>::Max()) , bCompositeToFinalImage(false)`
- L1158 _public function_ `virtual TSharedRef<FImagePixelDataPayload> Copy() const`
- L1163 _public function_ `virtual FIntPoint GetAccumulatorSize() const`
- L1168 _public function_ `virtual FIntPoint GetOverlappedOffset() const`
- L1173 _public function_ `virtual FVector2D GetOverlappedSubpixelShift() const`
- L1178 _public function_ `virtual void GetWeightFunctionParams(MoviePipeline::FTileWeight1D& WeightFunctionX, MoviePipeline::FTileWeight1D& WeightFunctionY) const`
- L1184 _public function_ `virtual FIntPoint GetOverlapPaddedSize() const`
- L1191 _public function_ `virtual bool GetOverlapPaddedSizeIsValid(const FIntPoint InRawSize) const`
- L1198 _public function_ `inline bool IsFirstTile() const` — Is this the first tile of an image and we should start accumulating?
- L1204 _public function_ `inline bool IsLastTile() const` — Is this the last tile of an image and we should finish accumulating?
- L1211 _public function_ `inline bool IsFirstTemporalSample() const`
- L1216 _public function_ `inline bool IsLastTemporalSample() const`

#### struct `FMoviePipelineMergerOutputFrame`  
`struct FMoviePipelineMergerOutputFrame`  
_L1222-1284_
- L1225 _public function_ `FMoviePipelineMergerOutputFrame()`
- L1226 _public prototype_ `virtual ~FMoviePipelineMergerOutputFrame() = default;`
- L1228 _public function_ `FMoviePipelineMergerOutputFrame& operator=(FMoviePipelineMergerOutputFrame&& InOther)`
- L1236 _public function_ `FMoviePipelineMergerOutputFrame(FMoviePipelineMergerOutputFrame&& InOther) : FrameOutputState(InOther.FrameOutputState) , ExpectedRenderPasses(InOther.ExpectedRenderPasses) , ImageOutputData(MoveTemp(InOther.ImageOutputData))`
- L1243 _public function_ `bool HasDataFromMultipleCameras() const`
- L1256 _public function_ `bool HasDataFromMultipleRenderPasses(const TArray<MoviePipeline::FCompositePassInfo>& InCompositedPasses) const`
- L1279 _public member_ `FMoviePipelineFrameOutputState FrameOutputState;`
- L1281 _public member_ `TArray<FMoviePipelinePassIdentifier> ExpectedRenderPasses;`
- L1283 _public member_ `TMap<FMoviePipelinePassIdentifier, TUniquePtr<FImagePixelData>> ImageOutputData;`

#### struct `MoviePipeline::IMoviePipelineAccumulator`  
`struct IMoviePipelineAccumulator`  
_L1290-1292_
- desc: The interface that all accumulators should derive from.

#### struct `MoviePipeline::IMoviePipelineAccumulationArgs`  
`struct IMoviePipelineAccumulationArgs`  
_L1295-1297_
- desc: The interface that all accumulation args should derive from.

#### struct `MoviePipeline::IMoviePipelineOverlappedAccumulator`  
`struct IMoviePipelineOverlappedAccumulator : IMoviePipelineAccumulator, TSharedFromThis<IMoviePipelineOverlappedAccumulator>`  
_L1299-1301_
- inherits: `IMoviePipelineAccumulator,TSharedFromThis<IMoviePipelineOverlappedAccumulator>`

#### struct `MoviePipeline::IMoviePipelineOutputMerger`  
`struct IMoviePipelineOutputMerger : public TSharedFromThis<IMoviePipelineOutputMerger>`  
_L1303-1312_
- inherits: `TSharedFromThis<IMoviePipelineOutputMerger>`
- L1305 _public prototype_ `virtual FMoviePipelineMergerOutputFrame& QueueOutputFrame_GameThread(const FMoviePipelineFrameOutputState& CachedOutputState) = 0;`
- L1306 _public prototype_ `virtual void OnCompleteRenderPassDataAvailable_AnyThread(TUniquePtr<FImagePixelData>&& InData) = 0;`
- L1307 _public prototype_ `virtual void OnSingleSampleDataAvailable_AnyThread(TUniquePtr<FImagePixelData>&& InData) = 0;`
- L1308 _public prototype_ `virtual void AbandonOutstandingWork() = 0;`
- L1309 _public prototype_ `virtual int32 GetNumOutstandingFrames() const = 0;`
- L1311 _public prototype_ `virtual ~IMoviePipelineOutputMerger() = default;`

#### struct `MoviePipeline::FAudioState`  
`struct FAudioState`  
_L1314-1358_
- L1334 _public function_ `FAudioState() : bIsRecordingAudio(false) , PrevUnfocusedAudioMultiplier(1.f) , PrevRenderEveryTickValue(1) , PrevNeverMuteNRTAudioValue(0) , PrevAudioLatencyCompensationFrames(0) , bPrevAllowBackgroundAudio(false)`
- L1343 _public member_ `bool bIsRecordingAudio;`
- L1345 _public member_ `float PrevUnfocusedAudioMultiplier;`
- L1346 _public member_ `int32 PrevRenderEveryTickValue;`
- L1347 _public member_ `int32 PrevNeverMuteNRTAudioValue;`
- L1348 _public member_ `int32 PrevAudioLatencyCompensationFrames;`
- L1351 _public member_ `bool bPrevAllowBackgroundAudio;` — The previous value of ULevelEditorMiscSettings::bAllowBackgroundAudio.
- L1354 _public member_ `TArray<FAudioSegment> FinishedSegments;` — Float Buffers for Movie Segments we've finished rendering. Stored until shutdown. Fully available during Finalize stage.
- L1357 _public member_ `TArray<TWeakPtr<Audio::FMixerSubmix, ESPMode::ThreadSafe>> ActiveSubmixes;` — An array of active submixes we are recording for this shot. Gets cleared when recording stops on a shot.

#### struct `MoviePipeline::FAudioState::FAudioSegment`  
`struct FAudioSegment`  
_L1316-1332_
- L1318 _public function_ `FAudioSegment()`
- L1323 _public member_ `FGuid Id;`
- L1324 _public member_ `FMoviePipelineFrameOutputState OutputState;`
- L1326 _public member_ `FString SubmixName;`
- L1328 _public member_ `float NumChannels;`
- L1329 _public member_ `float SampleRate;`
- L1331 _public member_ `Audio::AlignedFloatBuffer SegmentData;`

#### struct `FMoviePipelineStringArray`  
`struct FMoviePipelineStringArray`  
_L1363-1369_
- reflection: `USTRUCT(BlueprintType)`
- desc: A simple struct wrapper around a string array so it can be included in a TMap.
- L1368 _public member_ `TArray<FString> Array;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")`

#### struct `FMoviePipelineRenderPassOutputData`  
`struct FMoviePipelineRenderPassOutputData`  
_L1372-1390_
- reflection: `USTRUCT(BlueprintType)`
- L1377 _public member_ `TArray<FString> FilePaths;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")`
- L1385 _public member_ `TArray<FString> FrameTemplatedFilePaths;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")` — The "frame templated" file paths. This groups together a set of output frames by frame number, eg "Seq.Shot.{frame_placeholder}.exr". If the render generated more than one output type (eg, EXR and JPEG), there may be more than one path here, but there should only be one per output type.
- L1389 _public member_ `TMap<FSoftClassPath, FMoviePipelineStringArray> SettingTypeToFilePaths;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")` — Maps a setting type to all of the files that the setting generated.

#### struct `FMoviePipelineShotOutputData`  
`struct FMoviePipelineShotOutputData`  
_L1393-1407_
- reflection: `USTRUCT(BlueprintType)`
- L1399 _public member_ `TWeakObjectPtr<UMoviePipelineExecutorShot> Shot;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Movie Pipeline")` — Which shot was this output data for?
- L1406 _public member_ `TMap<FMoviePipelinePassIdentifier, FMoviePipelineRenderPassOutputData> RenderPassData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")` — A mapping between render passes (such as 'FinalImage') and an array containing the files written for that shot. Will be multiple files if using image sequences.

#### struct `MoviePipeline::FMoviePipelineOutputFutureData`  
`struct FMoviePipelineOutputFutureData`  
_L1411-1427_
- L1413 _public function_ `FMoviePipelineOutputFutureData() : Shot(nullptr) , OriginSettingClass(nullptr)`
- L1418 _public member_ `UMoviePipelineExecutorShot* Shot;`
- L1419 _public member_ `FString FilePath;`
- L1420 _public member_ `FMoviePipelinePassIdentifier PassIdentifier;`
- L1423 _public member_ `FString FrameTemplatedFilePath;` — The "frame templated" filepath. This groups together a set of output frames by frame number, eg "Seq.Shot.{frame_placeholder}.exr".
- L1426 _public member_ `UClass* OriginSettingClass;` — The setting class that this file originated from.

#### struct `UE::MoviePipeline::FViewportArgs`  
`struct FViewportArgs`  
_L1434-1438_
- L1436 _public member_ `TSubclassOf<UMovieRenderDebugWidget> DebugWidgetClass;`
- L1437 _public member_ `bool bRenderViewport = false;`

#### struct `FMoviePipelineOutputData`  
`struct FMoviePipelineOutputData`  
_L1448-1499_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains information about the to-disk output generated by a movie pipeline. This structure is used both for per-shot work finished callbacks and for the final render finished callback. When used as a per-shot callback ShotData will only have one entry (for the shot that was just finished), and for the final render callback it will have data for all shots that managed to render. Can be empty if the job failed to produce any files.
- L1452 _public function_ `FMoviePipelineOutputData() : Pipeline(nullptr) , Job(nullptr) , bSuccess(false)`
- L1465 _public member_ `TObjectPtr<class UMoviePipelineBase> Pipeline;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Movie Pipeline")` — The UMoviePipeline instance that generated this data. This is only provided as an id (in the event you were the one who created the UMoviePipeline instance. DO NOT CALL FUNCTIONS ON THIS (unless you know what you're doing) Provided here for backwards compatibility.
- L1472 _public member_ `TObjectPtr<UMoviePipelineExecutorJob> Job;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Movie Pipeline")` — Job the data is for. Job may still be in progress (if a shot callback) so be careful about modifying properties on it When using the Movie Render Graph this will point to the duplicated job created during execution.
- L1476 _public member_ `bool bSuccess;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")` — Did the job succeed, or was it canceled early due to an error (such as failure to write file to disk)?
- L1487 _public member_ `TArray<FMoviePipelineShotOutputData> ShotData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")` — The file data for each shot that was rendered. If no files were written this will be empty. If this is from the per-shot work finished callback it will only have one entry (for the just finished shot). Will not include shots that did not get rendered due to the pipeline encountering an error. This will be empty when using the Movie Render Graph. If a job is a Movie Render Graph job, use GraphData instead, which has a similar layout but with different data types.
- L1498 _public member_ `TArray<FMovieGraphRenderOutputData> GraphData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")` — The file data for each shot that was rendered. If no files were written this will be empty. If this is from the per-shot work finished callback it will only have one entry (for the just finished shot). Will not include shots that did not get rendered due to the pipeline encountering an error. This will be empty when using the legacy Movie Pipeline Configurations. If a job is a legacy configuration, use ShotData instead, which has a similar layout but with different data types.

#### enum `EMoviePipelinePostRenderActionType`  
`enum class EMoviePipelinePostRenderActionType : uint8`  
_L1503-1513_
- reflection: `UENUM(BlueprintType)`
- desc: The action that should be taken after finishing the render.
- L1506 _public enumerator_ `DoNothing = 0` — Do nothing after the render.
- L1509 _public enumerator_ `PlayRenderOutput = 1 << 0` — Open the media that was generated from the render. The application used for this is defined in Editor Preferences for Movie Render Graph.
- L1512 _public enumerator_ `OpenOutputDirectory = 1 << 1` — Open the directory that contains the files generated by the render.

#### struct `TAsyncCompositeImage`  
`template<> struct TAsyncCompositeImage<FColor>`  
_L1524-1642_
- L1526 _public function_ `TAsyncCompositeImage(TUniquePtr<FImagePixelData>&& InPixelData, FIntPoint InOffset = FIntPoint()) : ImageToComposite(MoveTemp(InPixelData)) , Offset(InOffset)`
- L1531 _public function_ `void operator()(FImagePixelData* PixelData)`
- L1635 _public member_ `TUniquePtr<FImagePixelData> ImageToComposite;`
- L1641 _public member_ `FIntPoint Offset;` — Amount in pixels from the destination's top left to offset the source when compositing onto the destination. Can be negative, in which case a portion of the source's bottom right will be composited onto the destination's top left

#### struct `TAsyncCompositeImage`  
`template<> struct TAsyncCompositeImage<FFloat16Color>`  
_L1645-1710_
- L1526 _public function_ `TAsyncCompositeImage(TUniquePtr<FImagePixelData>&& InPixelData, FIntPoint InOffset = FIntPoint()) : ImageToComposite(MoveTemp(InPixelData)) , Offset(InOffset)`
- L1531 _public function_ `void operator()(FImagePixelData* PixelData)`
- L1635 _public member_ `TUniquePtr<FImagePixelData> ImageToComposite;`
- L1641 _public member_ `FIntPoint Offset;` — Amount in pixels from the destination's top left to offset the source when compositing onto the destination. Can be negative, in which case a portion of the source's bottom right will be composited onto the destination's top left

#### struct `TAsyncCompositeImage`  
`template<> struct TAsyncCompositeImage<FLinearColor>`  
_L1713-1779_
- L1526 _public function_ `TAsyncCompositeImage(TUniquePtr<FImagePixelData>&& InPixelData, FIntPoint InOffset = FIntPoint()) : ImageToComposite(MoveTemp(InPixelData)) , Offset(InOffset)`
- L1531 _public function_ `void operator()(FImagePixelData* PixelData)`
- L1635 _public member_ `TUniquePtr<FImagePixelData> ImageToComposite;`
- L1641 _public member_ `FIntPoint Offset;` — Amount in pixels from the destination's top left to offset the source when compositing onto the destination. Can be negative, in which case a portion of the source's bottom right will be composited onto the destination's top left

#### struct `TAsyncCropImage`  
`template<typename PixelType> struct TAsyncCropImage`  
_L1782-1861_
- L1784 _public function_ `TAsyncCropImage(FImageWriteTask* InParentWriteTask, const FIntRect& InCropRect) : ParentWriteTask(InParentWriteTask) , CropRect(InCropRect)`
- L1789 _public function_ `TAsyncCropImage(const FIntRect& InCropRect) : ParentWriteTask(nullptr) , CropRect(InCropRect)`
- L1794 _public function_ `void operator()(FImagePixelData* PixelData)`
- L1854 _public member_ `FImageWriteTask* ParentWriteTask;` — The parent image write task using this image preprocessor. If not null, the cropped image will be written to the write task's pixel data
- L1857 _public member_ `TUniquePtr<FImagePixelData> OutCroppedImage;` — If the parent write task is null, the cropped image will be written to this pixel data instead
- L1860 _public member_ `FIntRect CropRect;` — the rectangle to crop the source image to

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
- L43 _namespace_ `namespace Audio`
- L127 _function_ `friend uint32 GetTypeHash(FMoviePipelinePassIdentifier OutputState)`
- L132 _function_ `friend FString LexToString(const FMoviePipelinePassIdentifier InIdentifier)`
- L172 _namespace_ `namespace MoviePipeline`
- L824 _function_ `friend uint32 GetTypeHash(FMoviePipelineFrameOutputState OutputState)`
- L1101 _namespace_ `namespace MoviePipeline`
- L1287 _namespace_ `namespace MoviePipeline`
- L1409 _namespace_ `namespace MoviePipeline`
- L1430 _namespace_ `namespace UE`
- L1432 _namespace_ `namespace MoviePipeline` (scope `UE`)
- L1563 _function_ `` (scope `TAsyncCompositeImage::operator ()`)
- L1585 _function_ `` (scope `TAsyncCompositeImage::operator ()::__anon2c858f200102`)
- L1834 _function_ `` (scope `TAsyncCropImage::operator ()`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MovieRenderTileImage.h` (Public)


#### struct `FImageTilePlane`  
`struct FImageTilePlane`  
_L18-73_
- desc: Structure for a single tile.
- L24 _public function_ `FImageTilePlane() : SizeX(0) , SizeY(0) , AccumulationWeight(0.0f)` — Default constructor.
- L37 _public prototype_ `void Init(int32 InSizeX, int32 InSizeY);` — Initialize the memory. Before using the memory, we also will need a call to ZeroPlane. @param InSizeX - Horizontal size of the tile. @param InSizeY - Vertical size of the tile.
- L42 _public prototype_ `void ZeroPlane();` — Zeroes the accumulation. Assumes the data is already allocated.
- L47 _public prototype_ `void Reset();` — Frees the memory and resets the sizes
- L60 _public prototype_ `void AccumulateSinglePlane(const TArray64<float>& InRawData, int32 InSizeX, int32 InSizeY, float InSampleWeight, int InSampleOffsetX, int InSampleOffsetY);` — Accumulate a single tile to this plane. The raw data must be the exact size of the tile. In general, SampleOffsetX/SampleOffsetY will be 0 or 1. In most cases it is zero, but but if a sample has a subpixel offset after the last sample, it will affect the first sample of the next pixel. All accumulating assumes edge clamping. @param InRawData - Raw data to accumulate @param InRawSizeX - Width of the tile. Must exactly match. @param InRawSizeY - Height of the tile. Must exactly match. @param InSampleOffsetX - Pixel offset of the tile (in X) @param InSampleOffsetY - Pixel offset of the tile (in Y)
- L63 _public member_ `TArray64<float> ChannelData;` — Actual channel data
- L66 _public member_ `int32 SizeX;` — Width of the image.
- L69 _public member_ `int32 SizeY;` — Height of the image.
- L72 _public member_ `float AccumulationWeight;` — Accumulation weights, uniform for the whole plane.

#### struct `FImageTileAccumulator`  
`struct FImageTileAccumulator : MoviePipeline::IMoviePipelineAccumulator`  
_L78-253_
- inherits: `MoviePipeline::IMoviePipelineAccumulator`
- desc: Contains all the image planes for the tiles.
- L84 _public function_ `FImageTileAccumulator() : TileSizeX(0) , TileSizeY(0) , NumTilesX(0) , NumTilesY(0) , NumChannels(0) , KernelRadius(1.0f) , AccumulationGamma(1.0f)` — Default constructor.
- L104 _public prototype_ `void InitMemory(int InTileSizeX, int InTileSizeY, int InNumTilesX, int InNumTilesY, int InNumChannels);` — Allocates memory. @param InTileSizeX - Horizontal tile size. @param InTileSizeY - Vertical tile size. @param InNumTilesX - Num horizontal tiles. @param InNumTilesY - Num vertical tiles. @param InNumChannels - Num Channels.
- L111 _public prototype_ `void ZeroPlanes();` — Initializes memory. Resets the memory to 0s so that we can start a new frame.
- L116 _public prototype_ `void Reset();` — Resets the memory.
- L125 _public prototype_ `int32 GetPlaneIndex(int32 InTileX, int32 InTileY, int32 InChannel) const;` — Get the tile index in the ImagePlanes list. @param InTileX - Horizontal tile. @param InTileY - Vertical tile. @param InChannel - Channel index.
- L134 _public prototype_ `FImageTilePlane& AtPlaneData(int32 InTileX, int32 InTileY, int32 InChannel);` — Get the data for the appropriate tile. @param InTileX - Horizontal tile. @param InTileY - Vertical tile. @param InChannel - Channel index.
- L143 _public prototype_ `const FImageTilePlane& AtPlaneData(int32 InTileX, int32 InTileY, int32 InChannel) const;` — Get the data for the appropriate tile. @param InTileX - Horizontal tile. @param InTileY - Vertical tile. @param InChannel - Channel index.
- L157 _public prototype_ `void AccumulateTile(const TArray64<float>& InRawData, int32 InRawSizeX, int32 InRawSizeY, int InRawChannel, FVector2D InSubpixelOffset);` — Given a tile and its subpixel offset, accumulate this tile to all of the image planes. The raw sizes should exactly match the tile size. The SubpixelOffset should be in the range of [0,1). AccumulateTile() then figures out which tiles it touches, and accumulates them. @param InRawData - Tile to add. @param InRawSizeX - Width of the tile. Should exactly match the size of the internal channel planes. @param InRawSizeY - Height of the tile. Should exactly match the size of the internal channel planes. @param InRawChannel - Which channel to accumulate to. @param InSubpixelOffset - The offset, which affects which tiles get accumulated to.
- L164 _public prototype_ `float CalcSampleWeight(float InDistance) const;` — Given the dstance from a sample, calculate the weight. @param InDistance - The distance from the sample to the pixel center.
- L174 _public prototype_ `void AccumulatePixelData(const FImagePixelData& InPixelData, int32 InTileX, int32 InTileY, FVector2D InSubpixelOffset);` — Given a rendered tile, accumulate the data to the full size image. @param InPixelData - Raw pixel data. @param InTileX - Tile index in X. @param InTileY - Tile index in Y. @param InSubPixelOffset - SubPixel offset, should be in the range [0,1)
- L184 _public prototype_ `void FetchFinalPixelDataByte(TArray64<FColor>& OutPixelData) const;` — After accumulation is finished, fetch the final image as bytes. In theory we don't need this, because we could just fetch as LinearColor and convert to bytes. But the largest size asked for is 45k x 22.5k, which is 1B pixels. So fetching as LinearColor would create a 16GB intermediary image, so it's worth having an option to fetch straight to FColors. @param FImagePixelData - Finished pixel data.
- L191 _public prototype_ `void FetchFinalPixelDataLinearColor(TArray64<FLinearColor>& OutPixelData) const;` — After accumulation is finished, fetch the final image as linear colors @param FImagePixelData - Finished pixel data.
- L198 _public prototype_ `void FetchFinalPlaneScale(TArray<float>& PlaneScale) const;` — After accumulation is finished, fetch the final scale of each plane. @param PlaneScale - Final scale for each plane.
- L208 _public prototype_ `void FetchFullImageValue(float Rgba[4], const TArray<float>& PlaneScale, int32 FullX, int32 FullY) const;` — Grab a single pixel from the full res tile and scale it by the appropriate Scale value. @param Rgba - Found pixel value. @param PlaneScale - The scales of each channel plane. @param FullX - X position of the full res image. @param FullY - Y position of the full res image.
- L212 _public member_ `int32 TileSizeX;` — Width of each tile in pixels
- L215 _public member_ `int32 TileSizeY;` — Height of each tile in pixels
- L218 _public member_ `int32 NumTilesX;` — Horizontal tiles.
- L221 _public member_ `int32 NumTilesY;` — Vertical tiles.
- L224 _public member_ `int32 NumChannels;` — Number of channels in the tiles. Typical will be 3 (RGB).
- L227 _public member_ `float KernelRadius;` — Radius of the kernel, in units of the final image. A value of 1.0 means a radius of one pixel.
- L230 _public member_ `float AccumulationGamma;` — When accumulating apply pow(X,AccumulationGamma), and then apply pow(X,1/AccumulationGamma) on output.
- L251 _public member_ `TArray64<FImageTilePlane> ImagePlanes;` — Actual pixel data. Note total number of planes is NumTilesX * NumTilesY * NumChannels; The total image size can be up to 32k x 32k. For an RGBA pass, that is 16GB of data. So in the future we might want to keep a pool of tiles around and share them to avoid allocating/freeing so much memory. The layout of tiles is by subsample. So all tiles are the "width/height" of the full image, but describe different subsamples. So a 4k by 4k with TileSizeX=4 and TileSizeY=3 would have a pixel layout like this. TileIndex: |  0  1  2  3 | 0  1  2  3 | 0  1  2  3 | |  4  5  6  7 | 4  5  6  7 | 4  5  6  7 | |  8  9 10 11 | 8  9 10 11 | 8  9 10 11 | |  0  1  2  3 | 0  1  2  3 | 0  1  2  3 | |  4  5  6  7 | 4  5  6  7 | 4  5  6  7 | |  8  9 10 11 | 8  9 10 11 | 8  9 10 11 |

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINECORE_API`
