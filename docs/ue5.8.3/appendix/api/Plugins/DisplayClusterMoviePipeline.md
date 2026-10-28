# Plugins / DisplayClusterMoviePipeline

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline`
- headers: 11; symbols: 259
- symbol kinds: class=9, enum=6, enumerator=21, function=34, member=92, namespace=10, prototype=76, struct=11
- PrivateDependencyModuleNames: Core, CoreUObject, DisplayCluster, Engine, Imath, Json, UEOpenExr, UEOpenExrRTTI
- PublicDependencyModuleNames: ActorLayerUtilities, CinematicCamera, DisplayCluster, DisplayClusterConfiguration, ImageWriteQueue, LevelSequence, MovieRenderPipelineCore, MovieRenderPipelineRenderPasses, MovieScene, OpenColorIO, RHI, RenderCore

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline/Private/DisplayClusterMoviePipelineRenderSettings.h` (Private)


#### struct `UE::DisplayClusterMoviePipeline::FRenderSettings`  
`struct FRenderSettings`  
_L13-54_
- desc: Settings captured from the render pass node during Initialize().
- L16 _public member_ `EDisplayClusterRenderFrameMode RenderMode = EDisplayClusterRenderFrameMode::Unknown;` — Render frame mode (mono or stereo) captured from the render pass node during Initialize().
- L19 _public member_ `EDisplayClusterMoviePipelineOverscanMode OverscanMode = EDisplayClusterMoviePipelineOverscanMode::Default;` — Whether overscan comes from MRP (Default) or from each nDisplay viewport's own overscan setting.
- L22 _public member_ `float RenderResolutionScale = 1.f;` — Uniform scale applied to the render resolution of all viewports [0..1].
- L25 _public member_ `FIntPoint OutputResolutionOverride = FIntPoint::ZeroValue;` — When non-zero, overrides the viewport output resolution.
- L28 _public member_ `bool bIsMultiLayerEXROutput = false;` — True when the output node is a multi-layer EXR.
- L47 _public member_ `FExternalOverscan ExternalOverscan;` — External overscan state captured from the render pass node during Initialize().
- L50 _public member_ `EDisplayClusterMoviePipelineWarpBlendMode WarpBlendMode = EDisplayClusterMoviePipelineWarpBlendMode::WarpBlend;` — Controls how warp-blend is applied and composited for this pass.
- L53 _public member_ `mutable bool bEnabledWarpBlendErrorMsgShowOnce = false;` — Ensures the warp-blend unavailability warning is logged only once per initialization.

#### struct `UE::DisplayClusterMoviePipeline::FRenderSettings::FExternalOverscan`  
`struct FExternalOverscan`  
_L37-44_
- desc: Controls whether external overscan is applied and what fraction to pass to SetExternalOverscan(). - Default mode: bActive is true. If UMovieGraphCameraSettingNode overrides OverscanPercentage, that value is normalized to [0..1] and stored in Fraction; otherwise Fraction is unset and the viewport manager falls back to FMinimalViewInfo.GetOverscan() from the MRP camera. - Viewport mode: nDisplay's own per-viewport overscan settings apply; bActive is false.
- L40 _public member_ `bool bActive = false;` — When false, external overscan is disabled and nDisplay's per-viewport overscan applies instead.
- L43 _public member_ `TOptional<float> Fraction;` — Overscan fraction [0..1] to forward; unset means fall back to FMinimalViewInfo.GetOverscan().

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DisplayClusterMoviePipeline` (scope `UE`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline/Private/DisplayClusterMoviePipelineViewportCameraInfo.h` (Private)


#### enum `UE::DisplayClusterMoviePipeline::EClusterTopology`  
`enum class EClusterTopology : uint8`  
_L16-26_
- desc: Classifies the nDisplay cluster topology by the arrangement of viewports across nodes.
- L19 _public enumerator_ `None = 0` — One node, one viewport.
- L22 _public enumerator_ `PerViewport` — One node, multiple viewports.
- L25 _public enumerator_ `PerNode` — Multiple nodes, multiple viewports.

#### struct `UE::DisplayClusterMoviePipeline::FClusterInfo`  
`struct FClusterInfo`  
_L29-39_
- desc: General information about the nDisplay cluster. Captured during Initialize().
- L32 _public member_ `FString RootActorName;` — Root actor name.
- L35 _public member_ `FString RootActorClassName;` — Root actor class name.
- L38 _public member_ `EClusterTopology ClusterTopology = EClusterTopology::None;` — nDisplay cluster topology.

#### struct `UE::DisplayClusterMoviePipeline::FClusterNodeInfo`  
`struct FClusterNodeInfo`  
_L42-49_
- desc: Information about the cluster node that owns a viewport. Captured during Initialize().
- L45 _public member_ `FString Id;` — Cluster node ID.
- L48 _public member_ `FString Host;` — Cluster node host address.

#### struct `UE::DisplayClusterMoviePipeline::FViewportCameraInfo`  
`struct FViewportCameraInfo`  
_L55-113_
- desc: Maps a MRG camera index to a specific nDisplay viewport and stereo context. One entry is created per viewport context (mono = 1, stereo = 2 per viewport).
- L57 _public prototype_ `FViewportCameraInfo() = default;`
- L60 _public function_ `FViewportCameraInfo(const FViewportCameraInfo& In) : ClusterInfo(In.ClusterInfo) , ClusterNodeInfo(In.ClusterNodeInfo) , CameraName(In.CameraName) , ViewportId(In.ViewportId) , ContextNum(In.ContextNum) , bStereoRendering(In.bStereoRendering)` — Explicit copy constructor required because all members are const.
- L76 _public prototype_ `FViewportCameraInfo( const FRenderSettings& InRenderSettings, const FClusterInfo& InClusterInfo, const TSharedRef<IDisplayClusterViewport, ESPMode::ThreadSafe>& InViewport, const int32 InContextNum);` — Constructs a camera entry from an nDisplay viewport. @param InRenderSettings  Render settings captured from the render pass node during Initialize(). @param InClusterInfo     Cluster-level info (ID, root actor name). @param InViewport        nDisplay viewport to derive camera name, viewport ID, and cluster node from. @param InContextNum      Stereo context index (0 = mono/left eye, 1 = right eye).
- L83 _public prototype_ `const FString GetStereoEyeName() const;` — Return stereo eye name.
- L86 _public function_ `const bool IsActive() const` — returns true, if this camera can be used for rendering.
- L93 _public member_ `const FClusterInfo ClusterInfo;` — Cluster info.
- L96 _public member_ `const FClusterNodeInfo ClusterNodeInfo;` — Cluster node info.
- L103 _public member_ `const FString CameraName;` — Unique camera name used by MRG to identify this viewport. This camera name should be unique within the (viewport base ID + optional stereo suffix).
- L106 _public member_ `const FString ViewportId;` — Unique runtime ID of the nDisplay viewport.
- L109 _public member_ `const int32 ContextNum = 0;` — Stereo context index: 0 = mono or left eye, 1 = right eye.
- L112 _public member_ `const bool bStereoRendering = false;` — True if this viewport use stereo rendering.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DisplayClusterMoviePipeline` (scope `UE`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline/Private/DisplayClusterMoviePipelineViewportManager.h` (Private)


#### struct `FDisplayClusterMoviePipelineViewportManager`  
`struct FDisplayClusterMoviePipelineViewportManager`  
_L15-92_
- desc: Manages the viewport manager and render frame for a single cluster node during Movie Pipeline rendering. Each cluster node gets its own instance so nodes render independently of each other and of the DCRA's own viewport manager.
- L24 _public prototype_ `FDisplayClusterMoviePipelineViewportManager(const FString& InClusterNodeId, ADisplayClusterRootActor* InRootActor);` — Creates a viewport manager for the given cluster node and binds it to InRootActor. @param InClusterNodeId The cluster node this instance is responsible for rendering. @param InRootActor     The DCRA that owns the cluster configuration.
- L27 _public prototype_ `~FDisplayClusterMoviePipelineViewportManager();` — Releases the viewport manager.
- L36 _public prototype_ `bool BeginNewFrame( const UE::DisplayClusterMoviePipeline::FRenderSettings& InRenderSettings, UWorld* InWorld = nullptr, const uint32* InFrameNumberOverride = nullptr);` — Updates viewport configuration and builds the render frame for this cluster node. @param InWorld               World to use for rendering. If null, uses the world from the root actor. @param InFrameNumberOverride Optional frame number override passed to the viewport configuration update. @return True if the render frame was built successfully; false if the root actor or world is unavailable.
- L58 _public prototype_ `static ADisplayClusterRootActor* ResolveRootActor( class UMovieSceneSequencePlayer* InSequencePlayer, const TSoftObjectPtr<ADisplayClusterRootActor> InRootActor, const TSoftClassPtr<ADisplayClusterRootActor> InRootActorClass);` — Resolves the ADisplayClusterRootActor to render, respecting the provided override references. Search order: 1. Sequence bindings — preferred because the sequence explicitly owns the actor. 2. World actor list — fallback when the actor is in the world but not bound in the sequence. Within each source, the match priority is: a. Exact name + class match b. Class match only c. Any DCRA @param InSequencePlayer      Sequence player used to access the sequence bindings and the world. @param InRootActor           Soft reference to a specific actor to prefer; use a null soft pointer to skip. @param InRootActorClass      Soft reference to a subclass to prefer when no exact actor match is found; use a null soft pointer to skip. @return                      The best-matching DCRA, or nullptr if none could be found.
- L76 _public prototype_ `void ApplyWarpBlend_RenderThread( FRHICommandListImmediate& RHICmdList, class IDisplayClusterViewportProxy* InViewportProxy, const uint32 ContextNum, const FTextureRHIRef& InOutRTT) const;` — Apply viewport WarpBlend to the InOutRTT nDisplay WarpBlend PP does : RTT > copy > TempIn > WarpShader > TempOut > copy back > RTT + Transition for MRP RTT     = InOutRTT TempIn  = EDisplayClusterViewportResourceType::InputShaderResource TempOut = EDisplayClusterViewportResourceType::AdditionalTargetableResource Note: After the final copy-back, the RTT must be in the state OnRenderTargetReady_RenderThread expects
- L84 _public member_ `const FString ClusterNodeId;` — The cluster node ID this context is responsible for.
- L87 _public member_ `const TSharedRef<IDisplayClusterViewportManager, ESPMode::ThreadSafe> ViewportManagerRef;` — Viewport manager for this cluster node. Created in the constructor, released in the destructor.
- L91 _private member_ `FDisplayClusterRenderFrame RenderFrame;` — Current render frame data.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline/Private/Graph/DisplayClusterMovieGraphRenderCameraSource.h` (Private)


#### struct `FDisplayClusterMovieGraphRenderCameraSource`  
`struct FDisplayClusterMovieGraphRenderCameraSource : public FMovieGraphRenderCameraSource`  
_L28-169_
- inherits: `FMovieGraphRenderCameraSource`
- desc: nDisplay implementation of FMovieGraphRenderCameraSource. Replaces the default MRP cameras with the nDisplay viewports defined by a render pass node. During Initialize(), it resolves the root actor, enumerates viewports across all cluster nodes, and creates one FDisplayClusterMoviePipelineViewportManager per node so that multiple nDisplay instances in the same graph can render independently.
- L31 _public prototype_ `virtual ~FDisplayClusterMovieGraphRenderCameraSource() = default;`
- L35 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FMovieGraphRenderCameraSource Interface
- L36 _public prototype_ `virtual void OnBeginFrame(const UMovieGraphPipeline* InMoviePipeline, const FMovieGraphTimeStepData* InTimeData) override;`
- L38 _public function_ `virtual int32 GetNumCameras() const override`
- L40 _public prototype_ `virtual bool GetCameraName(const int32 InCameraIndex, FString& OutCameraName) const override;`
- L41 _public prototype_ `virtual bool GetCameraViewActor(const int32 InCameraIndex, AActor*& OutCameraActor) const override;`
- L42 _public prototype_ `virtual bool GetCameraOverscan(const int32 InCameraIndex, float& OutCameraOverscan) const override;`
- L44 _public prototype_ `virtual bool GetCameraViewInfo(const int32 InCameraIndex, FMinimalViewInfo& OutViewInfo) const override;`
- L45 _public prototype_ `virtual void SetupCameraViewProjectionData(const int32 InCameraIndex, FSceneViewProjectionData& InOutProjectionData) const override;`
- L47 _public prototype_ `virtual bool GetCameraOverscannedResolution(const int32 InCameraIndex, FIntPoint& InOutOverscannedResolution, FIntRect& InOutOverscanCropRectangle, float& InOutOverscanFraction) const override;`
- L61 _public prototype_ `template<typename TDisplayClusterRenderPassNode> bool Initialize( const TDisplayClusterRenderPassNode& InRenderPassNode, const UMovieGraphPipeline* InMovieGraphPipeline, const UMovieGraphEvaluatedConfig* InEvaluatedConfig);` — Resolves the root actor and viewports, creates per-cluster-node viewport managers, and populates this source with the resulting render pass layer data. Returns false if the root actor could not be resolved or no viewports are available. @param InRenderPassNode      Render pass node providing configuration (output method, viewports, etc.). @param InMovieGraphPipeline  Active pipeline, used to resolve the sequence player and world. @param InEvaluatedConfig     Evaluated graph config for the current shot.
- L75 _public prototype_ `bool ModifyProjectionMatrixForTiling( const int32 InCameraIndex, const UE::MovieGraph::DefaultRenderer::FMovieGraphTilingParams& InTilingParams, const bool bInOrthographic, FMatrix& InOutProjectionMatrix, float& OutDoFSensorScale) const;` — Implements FMovieGraphImagePassBase::ModifyProjectionMatrixForTiling() for nDisplay. @param InCameraIndex          Index into the camera viewport list. @param InTilingParams        Tiling configuration for the current sample. @param bInOrthographic       Whether the camera uses an orthographic projection. @param InOutProjectionMatrix Projection matrix to adjust for the current tile. @param OutDoFSensorScale     Receives the sensor scale factor used for depth-of-field calculations.
- L88 _public prototype_ `static void GetFormatResolveArgs(const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier, FMovieGraphResolveArgs& OutMergedFormatArgs);` — Returns the set of nDisplay filename tokens for the UI. Uses dummy instances because no DCRA or live viewports are present in that context. @param InRenderDataIdentifier  Identifier used to derive the metadata path prefix. @param OutMergedFormatArgs     Receives the nDisplay filename and metadata token entries.
- L97 _public prototype_ `void ApplyCameraOverridesToSampleState( const int32 InCameraIndex, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier, UE::MovieGraph::FMovieGraphSampleState& InOutSampleState) const;` — Applies nDisplay-specific overrides (e.g. layer name) to the sample state for the given camera. @param InCameraIndex          Index into the camera viewport list. @param InRenderDataIdentifier Identifier for the current render data, used to derive per-viewport overrides. @param InOutSampleState       Sample state to modify in place.
- L111 _public prototype_ `void PostRendererSubmission(const int32 InCameraIndex, const UE::MovieGraph::FMovieGraphSampleState& InSampleState, const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InRenderTargetInitParams, FCanvas& InCanvas, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const;` — Called after the renderer submits a frame; applies warp-blend to the canvas render target for the given camera. @param InCameraIndex             Index into the camera viewport list. @param InSampleState             Sample state for the current frame. @param InRenderTargetInitParams  Parameters used to initialize the render target. @param InCanvas                  Canvas whose render target receives the warp-blend result. @param InCameraInfo              Camera and tiling parameters for the current sample.
- L124 _public function_ `inline IDisplayClusterViewport* FindViewport(const int32 CameraIndex, int32& OutContextNum) const` — Returns the viewport for the given camera index, or nullptr if out of range. @param CameraIndex    Index into the camera viewport list. @param OutContextNum  Receives the view context index (0 = mono/left, 1 = right). @return               The viewport, or nullptr if CameraIndex is out of range.
- L143 _public function_ `inline IDisplayClusterViewport* FindViewport(const UE::DisplayClusterMoviePipeline::FViewportCameraInfo& InCamera) const` — Returns the viewport for the given camera entry, or nullptr if the cluster node or viewport is not found. @param InCamera  Camera entry identifying the cluster node and viewport to look up. @return          The viewport, or nullptr if the cluster node or viewport ID is not registered.
- L155 _private member_ `UE::DisplayClusterMoviePipeline::FRenderSettings RenderSettings;` — Cached render settings.
- L158 _private member_ `UE::DisplayClusterMoviePipeline::FClusterInfo ClusterInfo;` — Root actor info, populated by Initialize().
- L161 _private member_ `TArray<UE::DisplayClusterMoviePipeline::FViewportCameraInfo> CameraViewports;` — Viewports selected for rendering this shot, populated by Initialize().
- L168 _private member_ `TMap<FString, TSharedRef<FDisplayClusterMoviePipelineViewportManager, ESPMode::ThreadSafe>> ClusterNodes;` — One viewport manager per cluster node (keyed by node ID). Each node gets its own manager instead of sharing the DCRA's manager, so multiple nDisplay nodes in the same graph can render independently.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline/Public/DisplayClusterMoviePipelineEnums.h` (Public)


#### enum `EDisplayClusterMoviePipelineOutputMethod`  
`enum class EDisplayClusterMoviePipelineOutputMethod : uint8`  
_L15-34_
- reflection: `UENUM(BlueprintType)`
- desc: Defines how nDisplay is rendered for Movie Pipeline.
- L18 _public enumerator_ `PerViewportOutput = 0 UMETA(DisplayName = "Per-Viewport Output")` — Renders each viewport to a separate texture.
- L21 _public enumerator_ `PerNodeOutputMapping UMETA(DisplayName = "Per-Node Output Mapping")` — Renders cluster nodes to a texture using the DCRA output mapping layout.
- L24 _public enumerator_ `FullClusterOutputMapping UMETA(DisplayName = "Full Cluster Output Mapping")` — Renders the full cluster to a texture using the DCRA output mapping layout.
- L27 _public enumerator_ `FrontProjection UMETA(DisplayName = "180 Equirectangular Output")` — Renders the full cluster to a texture using the front-facing 180-degree equirectangular projection and DefaultViewPoint as the eye origin.
- L30 _public enumerator_ `FullProjection UMETA(DisplayName = "360 Equirectangular Output")` — Renders the full cluster to a texture using the full 360-degree equirectangular projection and DefaultViewPoint as the eye origin.
- L33 _public enumerator_ `CustomMeshProjection UMETA(DisplayName = "Custom Mesh Projection Output")` — Renders the full cluster to a texture using a custom mesh as the UV projection surface and DefaultViewPoint as the eye origin.

#### enum `EDisplayClusterMoviePipelineStereoMode`  
`enum class EDisplayClusterMoviePipelineStereoMode : uint8`  
_L40-53_
- reflection: `UENUM(BlueprintType)`
- desc: Stereo rendering mode for nDisplay Movie Pipeline.
- L43 _public enumerator_ `None = 0 UMETA(DisplayName = "None")` — No stereo — renders a single mono (center) view.
- L46 _public enumerator_ `Stereo UMETA(DisplayName = "Stereo")` — Renders both left and right eye views.
- L49 _public enumerator_ `LeftEye UMETA(DisplayName = "Left Eye")` — Renders the left eye view only.
- L52 _public enumerator_ `RightEye UMETA(DisplayName = "Right Eye")` — Renders the right eye view only.

#### enum `EDisplayClusterMoviePipelineWarpBlendMode`  
`enum class EDisplayClusterMoviePipelineWarpBlendMode : uint8`  
_L59-66_
- reflection: `UENUM(BlueprintType)`
- desc: Controls how nDisplay warp-blend is composited during Movie Pipeline rendering.
- L62 _public enumerator_ `None = 0 UMETA(DisplayName = "None")` — Warp-blend is disabled; the raw render target is passed through unchanged.
- L65 _public enumerator_ `WarpBlend UMETA(DisplayName = "Warp Blend")` — Apply warp-blend.

#### enum `EDisplayClusterMoviePipelineOverscanMode`  
`enum class EDisplayClusterMoviePipelineOverscanMode : uint8`  
_L72-79_
- reflection: `UENUM(BlueprintType)`
- desc: Selects the overscan source for nDisplay Movie Pipeline.
- L75 _public enumerator_ `Default = 0 UMETA(DisplayName = "Default")` — Use the overscan configured in MRP (default behavior).
- L78 _public enumerator_ `Viewport UMETA(DisplayName = "nDisplay Viewport")` — Use the overscan configured on each nDisplay viewport.

#### enum `EDisplayClusterMoviePipelineEXRLayerGrouping`  
`enum class EDisplayClusterMoviePipelineEXRLayerGrouping : uint8`  
_L86-108_
- reflection: `UENUM(BlueprintType)`
- desc: Controls how nDisplay viewports are grouped into multi-layer EXR files. Only applies when the Movie Graph output node supports multi-layer output.
- L89 _public enumerator_ `None = 0 UMETA(DisplayName = "None")` — Each viewport is written to a separate file. No multi-layer grouping.
- L95 _public enumerator_ `Viewport UMETA(DisplayName = "Viewport")` — Each viewport (and its stereo eye contexts) is written as one or two layers in a shared EXR file. Mono produces one layer per viewport; stereo produces two (left + right).
- L101 _public enumerator_ `Node UMETA(DisplayName = "Node")` — All viewports belonging to the same cluster node are grouped into a single EXR file, one layer per viewport.
- L107 _public enumerator_ `Cluster UMETA(DisplayName = "Cluster")` — All viewports across all cluster nodes are grouped into a single EXR file, one layer per viewport.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline/Public/DisplayClusterMoviePipelineSettings.h` (Public)


#### struct `FDisplayClusterMoviePipelineConfiguration`  
`struct FDisplayClusterMoviePipelineConfiguration`  
_L11-36_
- reflection: `USTRUCT(Blueprintable)`
- L18 _public member_ `TSoftObjectPtr<ADisplayClusterRootActor> DCRootActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "DC Root Actor"))` — Reference to Display Cluster Root Actor If not set, the first available in the scene will be set.
- L23 _public member_ `TSoftClassPtr<ADisplayClusterRootActor> DCRootActorClass;` — `UPROPERTY()` — Container with DCRA instance class: for using multiple instances of DCRA of the same class in multiple scenes.
- L27 _public member_ `bool bUseViewportResolutions = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay")` — Render with nDisplay viewport resolutions.
- L31 _public member_ `bool bRenderAllViewports = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay")` — Render all viewports
- L35 _public member_ `TArray<FString> AllowedViewportNamesList;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Allowed Viewport Names List", EditCondition = "!bRenderAllViewports && DCRootActor != nullptr"))` — Render only viewports from this list.

#### class `UDisplayClusterMoviePipelineSettings`  
`class UDisplayClusterMoviePipelineSettings : public UMoviePipelineSetting`  
_L42-80_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UMoviePipelineSetting`
- desc: nDisplay settings for MoviePipeline
- L50 _public prototype_ `ADisplayClusterRootActor* GetRootActor(const UWorld* InWorld) const;` — return a pointer to the specified DCRA from the current world
- L61 _public prototype_ `bool GetViewports(const UWorld* InWorld, TArray<FString>& OutViewports, TArray<FIntPoint>& OutViewportResolutions) const;` — Collect viewport names for rendering @param InWorld       - World for render @param OutViewports  - [Out] list of viewports to render in MoviewPipeline @param OutViewportResolutions - [Out] list of viewports dimensions return true if is whether it populated 1 or more viewports in the given array.
- L64 _public function_ `virtual FText GetDisplayText() const override`
- L67 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L72 _protected function_ `virtual bool IsValidOnShots() const override`
- L73 _protected function_ `virtual bool IsValidOnPrimary() const override`
- L79 _public member_ `FDisplayClusterMoviePipelineConfiguration Configuration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "nDisplay"))` — Reference to Display Cluster Root Actor If not set, the first available in the scene will be set.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline/Public/DisplayClusterMoviePipelineViewportPass.h` (Public)


#### class `UDisplayClusterMoviePipelineViewportPassBase`  
`class UDisplayClusterMoviePipelineViewportPassBase : public UMoviePipelineDeferredPassBase`  
_L14-94_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMoviePipelineDeferredPassBase`
- desc: nDisplay viewport render pass (Lit)
- L27 _public prototype_ `UDisplayClusterMoviePipelineViewportPassBase(const FString& InRenderPassName);`
- L28 _public function_ `UDisplayClusterMoviePipelineViewportPassBase() : UDisplayClusterMoviePipelineViewportPassBase(TEXT("nDis`
- L32 _public prototype_ `virtual void SetupImpl(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings) override;` — UMoviePipelineDeferredPassBase
- L33 _public prototype_ `virtual void TeardownImpl() override;`
- L35 _public prototype_ `virtual FSceneView* GetSceneViewForSampleState(FSceneViewFamily* ViewFamily, FMoviePipelineRenderPassMetrics& InOutSampleState, IViewCalcPayload* OptPayload) override;`
- L36 _public prototype_ `virtual void ModifyProjectionMatrixForTiling(const FMoviePipelineRenderPassMetrics& InSampleState, const bool bInOrthographic, FMatrix& InOutProjectionMatrix, float& OutDoFSensorScale) const override;`
- L37 _public prototype_ `virtual void PostRendererSubmission(const FMoviePipelineRenderPassMetrics& InSampleState, const FMoviePipelinePassIdentifier InPassIdentifier, const int32 InSortingOrder, FCanvas& InCanvas) override;`
- L39 _public prototype_ `virtual int32 GetNumCamerasToRender() const override;`
- L40 _public prototype_ `virtual int32 GetCameraIndexForRenderPass(const int32 InCameraIndex) const override;`
- L41 _public prototype_ `virtual FString GetCameraName(const int32 InCameraIndex) const override;`
- L42 _public prototype_ `virtual FString GetCameraNameOverride(const int32 InCameraIndex) const override;`
- L44 _public prototype_ `virtual UE::MoviePipeline::FImagePassCameraViewData GetCameraInfo(FMoviePipelineRenderPassMetrics& InOutSampleState, IViewCalcPayload* OptPayload = nullptr) const override;`
- L45 _public prototype_ `virtual void BlendPostProcessSettings(FSceneView* InView, FMoviePipelineRenderPassMetrics& InOutSampleState, IViewCalcPayload* OptPayload = nullptr) override;`
- L47 _public prototype_ `virtual FIntPoint GetOverscannedResolutionForCamera(const int32 InCameraIndex) const override;`
- L51 _public function_ `virtual FText GetDisplayText() const override`
- L54 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`
- L55 _public function_ `virtual bool bIsEnabledWarpBlend() const`
- L57 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L60 _protected prototype_ `bool GetViewportId(int32 InViewportIndex, FString& OutViewportId) const;`
- L62 _protected prototype_ `class IDisplayClusterViewport* GetAndCalculateDisplayClusterViewport(const FMoviePipelineRenderPassMetrics& InSampleState, const FString& InViewportId, const FIntPoint& InDestSize, const uint32 InContextNum, FDisplayClusterViewInfo& OutView);`
- L64 _protected prototype_ `bool InitializeDisplayCluster();`
- L65 _protected prototype_ `void ReleaseDisplayCluster();`
- L67 _protected prototype_ `void GetViewportCutOffset(const FMoviePipelineRenderPassMetrics& InSampleState, FIntPoint& OutOffsetMin, FIntPoint& OutOffsetMax) const;`
- L70 _protected prototype_ `ADisplayClusterRootActor* GetRootActor() const;` — Return current DCRA.
- L75 _public member_ `bool bEnabledWarpBlend = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay")` — Allow warp blend for this pass
- L79 _private member_ `const FString RenderPassName;` — Render pass name
- L82 _private member_ `TWeakObjectPtr<ADisplayClusterRootActor> RootActorWeakPtr;` — Scene DCRA.
- L85 _private member_ `TArray<FString> DisplayClusterViewports;` — Names of viewports to render in the current shot
- L86 _private member_ `TArray<FIntPoint> DisplayClusterViewportSizes;`
- L89 _private member_ `TMap<int32, FDisplayClusterViewInfo> DCViews;` — Cache view info for viewports
- L90 _private member_ `TMap<int32, FDisplayClusterViewInfo> DCPrevViews;`
- L93 _private member_ `uint8 bFrameWarpBlend : 1 = 0;` — Runtime flags

#### struct `UDisplayClusterMoviePipelineViewportPassBase::FDisplayClusterViewInfo`  
`struct FDisplayClusterViewInfo`  
_L19-24_
- L21 _public member_ `FVector ViewLocation;`
- L22 _public member_ `FRotator ViewRotation;`
- L23 _public member_ `FMatrix ProjectionMatrix;`

#### class `UDisplayClusterMoviePipelineViewportPass_Unlit`  
`class UDisplayClusterMoviePipelineViewportPass_Unlit : public UDisplayClusterMoviePipelineViewportPassBase`  
_L100-117_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDisplayClusterMoviePipelineViewportPassBase`
- desc: nDisplay viewport render pass (Unlit)
- L106 _public function_ `UDisplayClusterMoviePipelineViewportPass_Unlit() : UDisplayClusterMoviePipelineViewportPassBase(TEXT("nDisplayUnlit"))`
- L109 _public function_ `virtual FText GetDisplayText() const override`
- L112 _public function_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override`

#### class `UDisplayClusterMoviePipelineViewportPass_DetailLighting`  
`class UDisplayClusterMoviePipelineViewportPass_DetailLighting : public UDisplayClusterMoviePipelineViewportPassBase`  
_L123-141_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDisplayClusterMoviePipelineViewportPassBase`
- desc: nDisplay viewport render pass (DetailLightingOnly)
- L129 _public function_ `UDisplayClusterMoviePipelineViewportPass_DetailLighting() : UDisplayClusterMoviePipelineViewportPassBase(TEXT("nDisplayDetailLightingOnly"))`
- L132 _public function_ `virtual FText GetDisplayText() const override`
- L134 _public function_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override`
- L140 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`

#### class `UDisplayClusterMoviePipelineViewportPass_LightingOnly`  
`class UDisplayClusterMoviePipelineViewportPass_LightingOnly : public UDisplayClusterMoviePipelineViewportPassBase`  
_L147-165_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDisplayClusterMoviePipelineViewportPassBase`
- desc: nDisplay viewport render pass (LightingOnly)
- L153 _public function_ `UDisplayClusterMoviePipelineViewportPass_LightingOnly() : UDisplayClusterMoviePipelineViewportPassBase(TEXT("nDisplayLightingOnly"))`
- L156 _public function_ `virtual FText GetDisplayText() const override`
- L158 _public function_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override`
- L164 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`

#### class `UDisplayClusterMoviePipelineViewportPass_ReflectionsOnly`  
`class UDisplayClusterMoviePipelineViewportPass_ReflectionsOnly : public UDisplayClusterMoviePipelineViewportPassBase`  
_L171-189_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDisplayClusterMoviePipelineViewportPassBase`
- desc: nDisplay viewport render pass (ReflectionsOnly)
- L177 _public function_ `UDisplayClusterMoviePipelineViewportPass_ReflectionsOnly() : UDisplayClusterMoviePipelineViewportPassBase(TEXT("nDisplayReflectionsOnly"))`
- L180 _public function_ `virtual FText GetDisplayText() const override`
- L182 _public function_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override`
- L188 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`

#### class `UDisplayClusterMoviePipelineViewportPass_PathTracer`  
`class UDisplayClusterMoviePipelineViewportPass_PathTracer : public UDisplayClusterMoviePipelineViewportPassBase`  
_L195-225_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDisplayClusterMoviePipelineViewportPassBase`
- desc: nDisplay viewport render pass (PathTracer)
- L200 _public function_ `UDisplayClusterMoviePipelineViewportPass_PathTracer() : UDisplayClusterMoviePipelineViewportPassBase(TEXT("nDisplayPathTracer"))`
- L203 _public function_ `virtual FText GetDisplayText() const override`
- L204 _public prototype_ `virtual FText GetFooterText(UMoviePipelineExecutorJob* InJob) const override;`
- L206 _public function_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override`
- L213 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`
- L215 _public function_ `virtual bool IsAntiAliasingSupported() const`
- L216 _public prototype_ `virtual void ValidateStateImpl() override;`
- L217 _public prototype_ `virtual void SetupImpl(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings) override;`
- L224 _public member_ `bool bReferenceMotionBlur;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference Motion Blur")` — When enabled, the path tracer will blend all spatial and temporal samples prior to the denoising and will disable post-processed motion blur. In this mode it is possible to use higher temporal sample counts to improve the motion blur quality. When this option is disabled, the path tracer will accumulate spatial samples, but denoise them prior to accumulation of temporal samples.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline/Public/Graph/Nodes/DisplayClusterMovieGraphDeferredPassNode.h` (Public)


#### class `UDisplayClusterMovieGraphDeferredRenderPassNode`  
`class UDisplayClusterMovieGraphDeferredRenderPassNode : public UMovieGraphDeferredRenderPassNode`  
_L14-129_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieGraphDeferredRenderPassNode`
- desc: Movie Graph deferred render pass node for nDisplay.
- L19 _public prototype_ `UDisplayClusterMovieGraphDeferredRenderPassNode();`
- L20 _public prototype_ `~UDisplayClusterMovieGraphDeferredRenderPassNode();`
- L23 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L26 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _public member_ `uint8 bOverride_OutputMethod : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L35 _public member_ `uint8 bOverride_ResolutionScale : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L38 _public member_ `uint8 bOverride_OutputResolution : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L41 _public member_ `uint8 bOverride_WarpBlendMode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L44 _public member_ `uint8 bOverride_RootActorRef : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L47 _public member_ `uint8 bOverride_AllowedViewportNamesList : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L50 _public member_ `uint8 bOverride_AllowedNodeNamesList : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L53 _public member_ `uint8 bOverride_StereoMode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L56 _public member_ `uint8 bOverride_OverscanMode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L59 _public member_ `uint8 bOverride_EXRLayerGrouping : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L64 _public member_ `EDisplayClusterMoviePipelineOutputMethod OutputMethod = EDisplayClusterMoviePipelineOutputMethod::PerViewportOutput;` — `UPROPERTY(BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "nDisplay Output Method", EditCondition = "bOverride_OutputMethod"))` — Determines how nDisplay renders output: per-viewport, via output mapping layout, or via projection policy.
- L68 _public member_ `EDisplayClusterMoviePipelineEXRLayerGrouping EXRLayerGrouping = EDisplayClusterMoviePipelineEXRLayerGrouping::None;` — `UPROPERTY(BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "EXR Layer Grouping", EditCondition = "bOverride_EXRLayerGrouping"))` — Controls how nDisplay viewports are grouped into multi-layer EXR files.
- L72 _public member_ `float ResolutionScale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Resolution Scale", ClampMin = "0.01", UIMin = "0.1", UIMax = "1.0", EditCondition = "bOverride_ResolutionScale"))` — Uniform scale applied to the viewport resolution before rendering.
- L76 _public member_ `FIntPoint OutputResolution = FIntPoint::ZeroValue;` — `UPROPERTY(BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Override Output Resolution", EditCondition = "bOverride_OutputResolution"))` — Overrides the output resolution.
- L80 _public member_ `EDisplayClusterMoviePipelineStereoMode StereoMode = EDisplayClusterMoviePipelineStereoMode::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Stereo Mode", EditCondition = "bOverride_StereoMode"))` — Stereo rendering mode for this pass.
- L84 _public member_ `EDisplayClusterMoviePipelineOverscanMode OverscanMode = EDisplayClusterMoviePipelineOverscanMode::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Overscan Mode", EditCondition = "bOverride_OverscanMode"))` — Selects the overscan source: MRP default or nDisplay viewport overscan.
- L88 _public member_ `EDisplayClusterMoviePipelineWarpBlendMode WarpBlendMode = EDisplayClusterMoviePipelineWarpBlendMode::WarpBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Warp Blend Mode", EditCondition = "bOverride_WarpBlendMode"))` — Controls how warp-blend is applied and composited for this pass.
- L95 _public member_ `TSoftObjectPtr<ADisplayClusterRootActor> RootActorRef;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Override nDisplay Actor", EditCondition = "bOverride_RootActorRef"))` — Reference to the DisplayCluster Root Actor to use for this render. If not set, the first available ADisplayClusterRootActor in the scene is used.
- L99 _public member_ `TSoftClassPtr<ADisplayClusterRootActor> RootActorClassRef;` — `UPROPERTY()` — Container with DCRA instance class: for using multiple instances of DCRA of the same class in multiple scenes.
- L103 _public member_ `TArray<FString> AllowedViewportNamesList;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Render Selected Viewports Only", EditCondition = "bOverride_AllowedViewportNamesList"))` — Render only viewports from this list.
- L107 _public member_ `TArray<FString> AllowedNodeNamesList;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Render Selected Nodes Only", EditCondition = "bOverride_AllowedNodeNamesList"))` — Render only nodes from this list.
- L111 _protected prototype_ `virtual void SetupImpl(const FMovieGraphRenderPassSetupData& InSetupData) override;`
- L112 _protected prototype_ `virtual void TeardownImpl() override;`
- L113 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L114 _protected prototype_ `virtual void GetFormatResolveArgs(FMovieGraphResolveArgs& OutMergedFormatArgs, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier) const override;`
- L115 _protected prototype_ `virtual TSharedPtr<FMovieGraphRenderCameraSource> CreateRenderCameraSourceImpl(const UMovieGraphPipeline* InMovieGraphPipeline, const UMovieGraphEvaluatedConfig* InEvaluatedConfig) override;`
- L116 _protected function_ `virtual TSharedPtr<FMovieGraphRenderCameraSource> GetRenderCameraSourceImpl() const override`
- L120 _protected prototype_ `virtual TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase> CreateInstance() const override;`
- L125 _private member_ `TSharedPtr<FMovieGraphRenderCameraSource> RenderCameraSource;` — Non-CDO only; null on the CDO and valid for the lifetime of the active shot pipeline.
- L128 _private member_ `bool bRenderCameraSourceInitialized = false;` — Guards CreateRenderCameraSourceImpl() so it runs exactly once per shot.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline/Public/Graph/Nodes/DisplayClusterMovieGraphPathTracerPassNode.h` (Public)


#### class `UDisplayClusterMovieGraphPathTracerRenderPassNode`  
`class UDisplayClusterMovieGraphPathTracerRenderPassNode : public UMovieGraphPathTracerRenderPassNode`  
_L14-129_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieGraphPathTracerRenderPassNode`
- desc: Movie Graph PathTracer render pass node for nDisplay.
- L19 _public prototype_ `UDisplayClusterMovieGraphPathTracerRenderPassNode();`
- L20 _public prototype_ `~UDisplayClusterMovieGraphPathTracerRenderPassNode();`
- L23 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L26 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _public member_ `uint8 bOverride_OutputMethod : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L35 _public member_ `uint8 bOverride_ResolutionScale : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L38 _public member_ `uint8 bOverride_OutputResolution : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L41 _public member_ `uint8 bOverride_WarpBlendMode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L44 _public member_ `uint8 bOverride_RootActorRef : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L47 _public member_ `uint8 bOverride_AllowedViewportNamesList : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L50 _public member_ `uint8 bOverride_AllowedNodeNamesList : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L53 _public member_ `uint8 bOverride_StereoMode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L56 _public member_ `uint8 bOverride_OverscanMode : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L59 _public member_ `uint8 bOverride_EXRLayerGrouping : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L64 _public member_ `EDisplayClusterMoviePipelineOutputMethod OutputMethod = EDisplayClusterMoviePipelineOutputMethod::PerViewportOutput;` — `UPROPERTY(BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "nDisplay Output Method", EditCondition = "bOverride_OutputMethod"))` — Determines how nDisplay renders output: per-viewport, via output mapping layout, or via projection policy.
- L68 _public member_ `EDisplayClusterMoviePipelineEXRLayerGrouping EXRLayerGrouping = EDisplayClusterMoviePipelineEXRLayerGrouping::None;` — `UPROPERTY(BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "EXR Layer Grouping", EditCondition = "bOverride_EXRLayerGrouping"))` — Controls how nDisplay viewports are grouped into multi-layer EXR files.
- L72 _public member_ `float ResolutionScale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Resolution Scale", ClampMin = "0.01", UIMin = "0.1", UIMax = "1.0", EditCondition = "bOverride_ResolutionScale"))` — Uniform scale applied to the viewport resolution before rendering.
- L76 _public member_ `FIntPoint OutputResolution = FIntPoint::ZeroValue;` — `UPROPERTY(BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Override Output Resolution", EditCondition = "bOverride_OutputResolution"))` — Overrides the output resolution.
- L80 _public member_ `EDisplayClusterMoviePipelineStereoMode StereoMode = EDisplayClusterMoviePipelineStereoMode::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Stereo Mode", EditCondition = "bOverride_StereoMode"))` — Stereo rendering mode for this pass.
- L84 _public member_ `EDisplayClusterMoviePipelineOverscanMode OverscanMode = EDisplayClusterMoviePipelineOverscanMode::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Overscan Mode", EditCondition = "bOverride_OverscanMode"))` — Selects the overscan source: MRP default or nDisplay viewport overscan.
- L88 _public member_ `EDisplayClusterMoviePipelineWarpBlendMode WarpBlendMode = EDisplayClusterMoviePipelineWarpBlendMode::WarpBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Warp Blend Mode", EditCondition = "bOverride_WarpBlendMode"))` — Controls how warp-blend is applied and composited for this pass.
- L95 _public member_ `TSoftObjectPtr<ADisplayClusterRootActor> RootActorRef;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Override nDisplay Actor", EditCondition = "bOverride_RootActorRef"))` — Reference to the DisplayCluster Root Actor to use for this render. If not set, the first available ADisplayClusterRootActor in the scene is used.
- L99 _public member_ `TSoftClassPtr<ADisplayClusterRootActor> RootActorClassRef;` — `UPROPERTY()` — Container with DCRA instance class: for using multiple instances of DCRA of the same class in multiple scenes.
- L103 _public member_ `TArray<FString> AllowedViewportNamesList;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Render Selected Viewports Only", EditCondition = "bOverride_AllowedViewportNamesList"))` — Render only viewports from this list.
- L107 _public member_ `TArray<FString> AllowedNodeNamesList;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay", meta = (DisplayName = "Render Selected Nodes Only", EditCondition = "bOverride_AllowedNodeNamesList"))` — Render only nodes from this list.
- L111 _protected prototype_ `virtual void SetupImpl(const FMovieGraphRenderPassSetupData& InSetupData) override;`
- L112 _protected prototype_ `virtual void TeardownImpl() override;`
- L113 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L114 _protected prototype_ `virtual void GetFormatResolveArgs(FMovieGraphResolveArgs& OutMergedFormatArgs, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier) const override;`
- L115 _protected prototype_ `virtual TSharedPtr<FMovieGraphRenderCameraSource> CreateRenderCameraSourceImpl(const UMovieGraphPipeline* InMovieGraphPipeline, const UMovieGraphEvaluatedConfig* InEvaluatedConfig) override;`
- L116 _protected function_ `virtual TSharedPtr<FMovieGraphRenderCameraSource> GetRenderCameraSourceImpl() const override`
- L120 _protected prototype_ `virtual TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase> CreateInstance() const override;`
- L125 _private member_ `TSharedPtr<FMovieGraphRenderCameraSource> RenderCameraSource;` — Non-CDO only; null on the CDO and valid for the lifetime of the active shot pipeline.
- L128 _private member_ `bool bRenderCameraSourceInitialized = false;` — Guards CreateRenderCameraSourceImpl() so it runs exactly once per shot.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline/Public/Graph/Renderers/DisplayClusterMovieGraphDeferredPass.h` (Public)


#### struct `UE::MovieGraph::Rendering::FDisplayClusterMovieGraphDeferredPass`  
`struct FDisplayClusterMovieGraphDeferredPass : public FMovieGraphDeferredPass`  
_L12-29_
- inherits: `FMovieGraphDeferredPass`
- desc: nDisplay override of FMovieGraphDeferredPass.
- L15 _public prototype_ `virtual UMovieGraphImagePassBaseNode* GetParentNode(UMovieGraphEvaluatedConfig* InConfig) const override;`
- L17 _public prototype_ `virtual void ModifyProjectionMatrixForTiling( const UE::MovieGraph::DefaultRenderer::FMovieGraphTilingParams& InTilingParams, const bool bInOrthographic, FMatrix& InOutProjectionMatrix, float& OutDoFSensorScale) const override;`
- L21 _public prototype_ `virtual void PostRendererSubmission( const UE::MovieGraph::FMovieGraphSampleState& InSampleState, const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InRenderTargetInitParams, FCanvas& InCanvas, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const override;`
- L27 _public prototype_ `virtual void ApplyMovieGraphOverridesToSampleState(FMovieGraphSampleState& SampleState) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MovieGraph` (scope `UE`)
- L7 _namespace_ `namespace Rendering` (scope `UE::MovieGraph`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipeline/Public/Graph/Renderers/DisplayClusterMovieGraphPathTracerPass.h` (Public)


#### struct `UE::MovieGraph::Rendering::FDisplayClusterMovieGraphPathTracerPass`  
`struct FDisplayClusterMovieGraphPathTracerPass : public FMovieGraphPathTracerPass`  
_L12-29_
- inherits: `FMovieGraphPathTracerPass`
- desc: nDisplay override of FMovieGraphPathTracerPass.
- L15 _public prototype_ `virtual UMovieGraphImagePassBaseNode* GetParentNode(UMovieGraphEvaluatedConfig* InConfig) const override;`
- L17 _public prototype_ `virtual void ModifyProjectionMatrixForTiling( const UE::MovieGraph::DefaultRenderer::FMovieGraphTilingParams& InTilingParams, const bool bInOrthographic, FMatrix& InOutProjectionMatrix, float& OutDoFSensorScale) const override;`
- L21 _public prototype_ `virtual void PostRendererSubmission( const UE::MovieGraph::FMovieGraphSampleState& InSampleState, const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InRenderTargetInitParams, FCanvas& InCanvas, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const override;`
- L27 _public prototype_ `virtual void ApplyMovieGraphOverridesToSampleState(FMovieGraphSampleState& SampleState) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MovieGraph` (scope `UE`)
- L7 _namespace_ `namespace Rendering` (scope `UE::MovieGraph`)
