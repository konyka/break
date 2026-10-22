# Plugins / DisplayClusterMedia

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia`
- headers: 29; symbols: 293
- symbol kinds: class=30, delegate=2, enum=2, enumerator=5, externvar=1, function=19, member=63, namespace=2, prototype=161, struct=5, typedef=3
- PrivateDependencyModuleNames: Core, CoreUObject, D3D12RHI, DisplayCluster, DisplayClusterShaders, Engine, OpenColorIO, RHI, RenderCore, Renderer, UnrealEd
- PublicDependencyModuleNames: DisplayClusterConfiguration, Media, MediaAssets, MediaIOCore

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Capture/DisplayClusterMediaCaptureBase.h` (Private)


#### class `FDisplayClusterMediaCaptureBase`  
`class FDisplayClusterMediaCaptureBase : public FDisplayClusterMediaBase , public FGCObject`  
_L22-131_
- inherits: `FDisplayClusterMediaBase,FGCObject`
- desc: Base media capture adapter class
- L28 _public prototype_ `FDisplayClusterMediaCaptureBase( const FString& MediaId, const FString& ClusterNodeId, UMediaOutput* MediaOutput, UDisplayClusterMediaOutputSynchronizationPolicy* SyncPolicy );`
- L35 _public prototype_ `virtual ~FDisplayClusterMediaCaptureBase();`
- L40 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L41 _public function_ `virtual FString GetReferencerName() const override`
- L50 _public prototype_ `virtual bool StartCapture();` — Start capturing
- L53 _public prototype_ `virtual void StopCapture();` — Stop capturing
- L56 _public function_ `UMediaCapture* GetMediaCapture() const` — Returns current media capture device
- L76 _protected prototype_ `void OnPostClusterTick();` — PostClusterTick event handler. It's used to restart capturing if needed
- L79 _protected prototype_ `bool StartMediaCapture();` — Re-starts media capturing after failure
- L82 _protected prototype_ `void ExportMediaData_RenderThread(FRDGBuilder& GraphBuilder, const FMediaOutputTextureInfo& TextureInfo);` — Passes capture data request to the capture device
- L85 _protected prototype_ `virtual FIntPoint GetCaptureSize() const = 0;` — Returns capture size (main thread)
- L90 _private prototype_ `bool IsValidRequestData(const FMediaOutputTextureInfo& TextureInfo) const;` — Validate if capture request data is valid
- L112 _private member_ `TObjectPtr<UMediaOutput> MediaOutput;`
- L113 _private member_ `TObjectPtr<UMediaCapture> MediaCapture;`
- L114 _private member_ `TObjectPtr<UDisplayClusterMediaOutputSynchronizationPolicy> SyncPolicy;`
- L118 _private member_ `FIntPoint CustomResolution = FIntPoint::ZeroValue;` — Custom resolution to use on capture side
- L121 _private member_ `bool bWasCaptureStarted = false;` — Used to restart media capture in the case it falls in error
- L124 _private member_ `double LastRestartTimestamp = 0;` — Used to control the rate at which we try to restart the capture
- L127 _private member_ `std::atomic<FIntSize> LastSrcRegionSize { FIntSize(0,0) };` — Last region size of the texture being exported.Used to restart the capture when in error.
- L130 _private member_ `TSharedPtr<IDisplayClusterMediaOutputSynchronizationPolicyHandler> SyncPolicyHandler;` — Sync policy handler to deal with synchronization logic

#### struct `FDisplayClusterMediaCaptureBase::FMediaOutputTextureInfo`  
`struct FMediaOutputTextureInfo`  
_L64-71_
- desc: Media capture data
- L67 _public member_ `FRDGTextureRef Texture = nullptr;` — Texture to capture by a media capture device
- L70 _public member_ `FIntRect Region = { FIntPoint::ZeroValue, FIntPoint::ZeroValue };` — Subregion to capture

#### struct `FDisplayClusterMediaCaptureBase::FIntSize`  
`struct FIntSize`  
_L95-107_
- desc: Trivial version of FIntPoint so that it can be std::atomic
- L97 _public member_ `int32 X = 0;`
- L98 _public member_ `int32 Y = 0;`
- L100 _public function_ `FIntSize(int32 InX, int32 InY) : X(InX), Y(InY)`
- L101 _public function_ `FIntSize(const FIntPoint& IntPoint) : X(IntPoint.X), Y(IntPoint.Y)`
- L103 _public function_ `FIntPoint ToIntPoint()`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Capture/DisplayClusterMediaCaptureCameraBase.h` (Private)


#### class `FDisplayClusterMediaCaptureCameraBase`  
`class FDisplayClusterMediaCaptureCameraBase : public FDisplayClusterMediaCaptureViewportBase , public FDisplayClusterMediaCameraCommon`  
_L12-34_
- inherits: `FDisplayClusterMediaCaptureViewportBase,FDisplayClusterMediaCameraCommon`
- desc: Base camera capture adapter
- L18 _public prototype_ `FDisplayClusterMediaCaptureCameraBase( const FString& MediaId, const FString& ClusterNodeId, const FString& CameraId, const FString& CameraViewportId, UMediaOutput* MediaOutput, UDisplayClusterMediaOutputSynchronizationPolicy* SyncPolicy );`
- L30 _protected prototype_ `virtual void UpdateLateOCIOState(const IDisplayClusterViewport* Viewport) override;` — Updates late OCIO state
- L33 _protected prototype_ `virtual void UpdateMediaPassthrough(const IDisplayClusterViewport* Viewport) override;` — Checks whether current frame should use media passthrough

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Capture/DisplayClusterMediaCaptureCameraFull.h` (Private)


#### class `FDisplayClusterMediaCaptureCameraFull`  
`class FDisplayClusterMediaCaptureCameraFull : public FDisplayClusterMediaCaptureCameraBase`  
_L11-29_
- inherits: `FDisplayClusterMediaCaptureCameraBase`
- desc: Camera capture adapter (full frame)
- L16 _public prototype_ `FDisplayClusterMediaCaptureCameraFull( const FString& MediaId, const FString& ClusterNodeId, const FString& CameraId, UMediaOutput* MediaOutput, UDisplayClusterMediaOutputSynchronizationPolicy* SyncPolicy );`
- L27 _public prototype_ `virtual bool GetCaptureSizeFromConfig(FIntPoint& OutSize) const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Capture/DisplayClusterMediaCaptureCameraTile.h` (Private)


#### class `FDisplayClusterMediaCaptureCameraTile`  
`class FDisplayClusterMediaCaptureCameraTile : public FDisplayClusterMediaCaptureCameraBase`  
_L11-30_
- inherits: `FDisplayClusterMediaCaptureCameraBase`
- desc: Camera capture adapter (tile)
- L16 _public prototype_ `FDisplayClusterMediaCaptureCameraTile( const FString& MediaId, const FString& ClusterNodeId, const FString& CameraId, const FIntPoint& TilePosition, UMediaOutput* MediaOutput, UDisplayClusterMediaOutputSynchronizationPolicy* SyncPolicy );`
- L28 _protected prototype_ `virtual bool GetCaptureSizeFromConfig(FIntPoint& OutSize) const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Capture/DisplayClusterMediaCaptureNodeBase.h` (Private)


#### class `FDisplayClusterMediaCaptureNodeBase`  
`class FDisplayClusterMediaCaptureNodeBase : public FDisplayClusterMediaCaptureBase`  
_L16-46_
- inherits: `FDisplayClusterMediaCaptureBase`
- desc: Node backbuffer media capture base class
- L22 _public prototype_ `FDisplayClusterMediaCaptureNodeBase( const FString& MediaId, const FString& ClusterNodeId, UMediaOutput* MediaOutput, UDisplayClusterMediaOutputSynchronizationPolicy* SyncPolicy );` — Constructor
- L32 _public prototype_ `virtual bool StartCapture() override;` — Start backbuffer capture
- L35 _public prototype_ `virtual void StopCapture() override;` — Stop backbuffer capture
- L40 _protected prototype_ `virtual void ProcessPostBackbufferUpdated_RenderThread(FRHICommandListImmediate& RHICmdList, FViewport* Viewport) = 0;` — PostBackbufferUpdated implementation on the children side
- L45 _private prototype_ `void OnPostBackbufferUpdated_RenderThread(FRHICommandListImmediate& RHICmdList, FViewport* Viewport);` — Main PostBackbufferUpdated event handler. It's passed as virtual ProcessPostBackbufferUpdated_RenderThread call to the children.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Capture/DisplayClusterMediaCaptureNodeFull.h` (Private)


#### class `FDisplayClusterMediaCaptureNodeFull`  
`class FDisplayClusterMediaCaptureNodeFull : public FDisplayClusterMediaCaptureNodeBase`  
_L16-36_
- inherits: `FDisplayClusterMediaCaptureNodeBase`
- desc: Node backbuffer media capture (whole buffer)
- L22 _public prototype_ `FDisplayClusterMediaCaptureNodeFull( const FString& MediaId, const FString& ClusterNodeId, UMediaOutput* MediaOutput, UDisplayClusterMediaOutputSynchronizationPolicy* SyncPolicy = nullptr );` — Constructor
- L32 _protected prototype_ `virtual FIntPoint GetCaptureSize() const override;` — Returns backbuffer size
- L35 _protected prototype_ `virtual void ProcessPostBackbufferUpdated_RenderThread(FRHICommandListImmediate& RHICmdList, FViewport* Viewport) override;` — PostBackbufferUpdated handler

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Capture/DisplayClusterMediaCaptureNodeTile.h` (Private)


#### class `FDisplayClusterMediaCaptureNodeTile`  
`class FDisplayClusterMediaCaptureNodeTile : public FDisplayClusterMediaCaptureNodeBase`  
_L16-68_
- inherits: `FDisplayClusterMediaCaptureNodeBase`
- desc: Node backbuffer media capture (tile)
- L22 _public function_ `static const FIntPoint GetMaxTileLayout()` — Returns maximum layout allowed for backbuffer capture
- L30 _public prototype_ `FDisplayClusterMediaCaptureNodeTile( const FString& MediaId, const FString& ClusterNodeId, const FIntPoint& TileLayout, const FIntPoint& TilePosition, UMediaOutput* MediaOutput, UDisplayClusterMediaOutputSynchronizationPolicy* SyncPolicy = nullptr );` — Constructor
- L42 _public prototype_ `virtual bool StartCapture() override;` — Start backbuffer capture
- L47 _protected prototype_ `virtual FIntPoint GetCaptureSize() const override;` — Returns tile size
- L50 _protected prototype_ `virtual void ProcessPostBackbufferUpdated_RenderThread(FRHICommandListImmediate& RHICmdList, FViewport* Viewport) override;` — PostBackbufferUpdated handler
- L55 _private member_ `const bool bValidTileSettings;` — Pre-computed optimization flag to avoid repetitive tile settings validation
- L58 _private member_ `const bool bEndingX;` — Pre-computed optimization flag to know if it's the last tile in a raw
- L61 _private member_ `const bool bEndingY;` — Pre-computed optimization flag to know if it's the last tile in a column
- L64 _private member_ `const FIntPoint TileLayout;` — Output tile layout
- L67 _private member_ `const FIntPoint TilePosition;` — This tile XY coordinate

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Capture/DisplayClusterMediaCaptureViewportBase.h` (Private)


#### class `FDisplayClusterMediaCaptureViewportBase`  
`class FDisplayClusterMediaCaptureViewportBase : public FDisplayClusterMediaCaptureBase`  
_L21-97_
- inherits: `FDisplayClusterMediaCaptureBase`
- desc: Base viewport capture adapter
- L26 _public prototype_ `FDisplayClusterMediaCaptureViewportBase( const FString& MediaId, const FString& ClusterNodeId, const FString& ViewportId, UMediaOutput* MediaOutput, UDisplayClusterMediaOutputSynchronizationPolicy* SyncPolicy );`
- L37 _public prototype_ `virtual bool StartCapture() override;` — Start capturing
- L40 _public prototype_ `virtual void StopCapture() override;` — Stop capturing
- L43 _public function_ `const FString& GetViewportId() const` — Returns viewport ID that is configured for capture
- L49 _public prototype_ `virtual FIntPoint GetCaptureSize() const override;` — Returns texture size of a viewport assigned to capture (main thread)
- L52 _public prototype_ `virtual bool GetCaptureSizeFromConfig(FIntPoint& OutSize) const = 0;` — Ask children about capture size based on the configuration data
- L55 _public prototype_ `bool GetCaptureSizeFromGameProxy(FIntPoint& OutSize) const;` — Provides texture size from a game proxy (if available)
- L60 _protected prototype_ `virtual void UpdateLateOCIOState(const IDisplayClusterViewport* Viewport);` — Updates late OCIO state
- L63 _protected prototype_ `virtual void HandleLateOCIOChanged(const FLateOCIOData& NewLateOCIOConfiguration) override;` — Process late OCIO state updates
- L66 _protected prototype_ `virtual void UpdateMediaPassthrough(const IDisplayClusterViewport* Viewport);` — Checks whether current frame should use media passthrough
- L71 _private prototype_ `void OnUpdateViewportMediaState(IDisplayClusterViewport* InViewport, EDisplayClusterViewportMediaState& InOutMediaState);` — UpdateViewportMediaState callback to configure media state for a viewoprt
- L74 _private prototype_ `void OnPostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, const FSceneViewFamily& ViewFamily, const IDisplayClusterViewportProxy* ViewportProxy);` — PostRenderViewFamily callback handler where data is captured (no late OCIO)
- L77 _private prototype_ `void OnPostTonemapPass_RenderThread(FRDGBuilder& GraphBuilder, const IDisplayClusterViewportProxy* ViewportProxy, const FSceneView& View, const FPostProcessMaterialInputs& Inputs, const uint32 ContextNum);` — PostTonemapPass callback handler (late OCIO)
- L80 _private prototype_ `void OnPassthroughMediaCapture_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* ViewportManagerProxy);` — PassthroughMediaCapture callback handler is used to capture in the passthrough scenarios
- L83 _private prototype_ `void OnPostResolveOverridden_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* ViewportProxy);` — PostResolveOverridden callback for the viewports that grab textures from somewhere and don't emit PostRender events
- L88 _private prototype_ `virtual FIntPoint GetViewportSize() const;` — Returns size of the viewport bound to this media
- L93 _private member_ `const FString ReferencedViewportId;` — Viewport ID assigned to capture
- L96 _private member_ `bool bUseMediaPassthrough_RT = false;` — Whether passthrough capture is needed

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Capture/DisplayClusterMediaCaptureViewportFull.h` (Private)


#### class `FDisplayClusterMediaCaptureViewportFull`  
`class FDisplayClusterMediaCaptureViewportFull : public FDisplayClusterMediaCaptureViewportBase`  
_L11-28_
- inherits: `FDisplayClusterMediaCaptureViewportBase`
- desc: Viewport capture adapter (full frame)
- L16 _public prototype_ `FDisplayClusterMediaCaptureViewportFull( const FString& MediaId, const FString& ClusterNodeId, const FString& ViewportId, UMediaOutput* MediaOutput, UDisplayClusterMediaOutputSynchronizationPolicy* SyncPolicy );`
- L27 _public prototype_ `virtual bool GetCaptureSizeFromConfig(FIntPoint& OutSize) const;` — Provides default capture size from config

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Capture/DisplayClusterMediaCaptureViewportTile.h` (Private)


#### class `FDisplayClusterMediaCaptureViewportTile`  
`class FDisplayClusterMediaCaptureViewportTile : public FDisplayClusterMediaCaptureViewportBase`  
_L11-30_
- inherits: `FDisplayClusterMediaCaptureViewportBase`
- desc: Viewport capture adapter (tile)
- L16 _public prototype_ `FDisplayClusterMediaCaptureViewportTile( const FString& MediaId, const FString& ClusterNodeId, const FString& ViewportId, const FIntPoint& TilePosition, UMediaOutput* MediaOutput, UDisplayClusterMediaOutputSynchronizationPolicy* SyncPolicy );`
- L28 _protected prototype_ `virtual bool GetCaptureSizeFromConfig(FIntPoint& OutSize) const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Common/DisplayClusterMediaBase.h` (Private)


#### class `FDisplayClusterMediaBase`  
`class FDisplayClusterMediaBase : public TSharedFromThis<FDisplayClusterMediaBase>`  
_L12-93_
- inherits: `TSharedFromThis<FDisplayClusterMediaBase>`
- desc: Base media adapter class
- L17 _public function_ `FDisplayClusterMediaBase(const FString& InMediaId, const FString& InClusterNodeId) : MediaId(InMediaId) , ClusterNodeId(InClusterNodeId)`
- L22 _public prototype_ `virtual ~FDisplayClusterMediaBase() = default;`
- L27 _public function_ `const FString& GetMediaId() const` — Returns ID of this media adapter
- L33 _public function_ `const FString& GetClusterNodeId() const` — Returns current cluster node ID
- L39 _public prototype_ `bool IsLateOCIO() const;` — Whether late OCIO is active on current frame
- L46 _public prototype_ `bool IsTransferPQ(bool bConsideringLateOCIOState = true) const;` — Is PQ transfer required? @param bConsideringLateOCIOState - Should the OCIO on/off state be logically AND-ed with the PQ on/off state
- L72 _protected prototype_ `void SetLateOCIO(const FLateOCIOData& NewLateOCIOConfiguration);` — Set late OCIO configuration by children
- L75 _protected function_ `virtual void HandleLateOCIOChanged(const FLateOCIOData& NewLateOCIOConfiguration)` — Let children handle the OCIO changes
- L81 _private member_ `const FString MediaId;` — ID of this media adapter
- L84 _private member_ `const FString ClusterNodeId;` — Cluster node ID we're running on
- L89 _private member_ `FLateOCIOData LateOCIOConfiguration;` — Late OCIO configuration on current frame
- L92 _private member_ `FLateOCIOData LateOCIOConfiguration_RT;` — Late OCIO configuration on current frame (render thread)

#### struct `FDisplayClusterMediaBase::FLateOCIOData`  
`struct FLateOCIOData`  
_L51-69_
- desc: Auxiliary structure to keep late OCIO parameters
- L54 _public member_ `bool bLateOCIO = false;` — Late OCIO enabled/disabled flag
- L57 _public member_ `bool bTransferPQ = false;` — PQ transfer enabled/disabled
- L60 _public function_ `bool operator==(const FLateOCIOData& Other)` — Comparison operator

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Common/DisplayClusterMediaCameraCommon.h` (Private)


#### class `FDisplayClusterMediaCameraCommon`  
`class FDisplayClusterMediaCameraCommon`  
_L13-37_
- desc: Common camera logic for media
- L17 _public prototype_ `FDisplayClusterMediaCameraCommon(const FString& CameraId);`
- L18 _public prototype_ `virtual ~FDisplayClusterMediaCameraCommon() = default;`
- L23 _protected prototype_ `UDisplayClusterICVFXCameraComponent* GetCameraComponent() const;` — Finds an ICVFX camera component by name, otherwise nullptr
- L26 _protected prototype_ `void GetLateOCIOParameters(bool& bOutLateOCIOEnabled, bool& bOutTransferPQ) const;` — Returns late OCIO parameters of the current camera
- L31 _private prototype_ `bool HasAnyValidPerNodeOCIOConfiguration() const;` — Checks whether any valid per-node OCIO configuration is set
- L36 _private member_ `const FString CameraId;` — Holds ICVFX camera component name associated with this media adapter

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/DisplayClusterMediaCVars.h` (Private)


#### Free symbols / members of external scopes

- L12 _externvar_ `extern TAutoConsoleVariable<bool> CVarMediaEnabled;` — Enable/disable media. May be useful if media needs to be disabled without doing any changes to the nDisplay configuration asset.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/DisplayClusterMediaHelpers.h` (Private)


#### enum `DisplayClusterMediaHelpers::MediaId::EMediaDeviceType`  
`enum class EMediaDeviceType : uint8`  
_L16-20_
- desc: Helper for media ID generation
- L18 _public enumerator_ `Input`
- L19 _public enumerator_ `Output`

#### enum `DisplayClusterMediaHelpers::MediaId::EMediaOwnerType`  
`enum class EMediaOwnerType : uint8`  
_L23-28_
- desc: Helper for media ID generation
- L25 _public enumerator_ `Backbuffer`
- L26 _public enumerator_ `Viewport`
- L27 _public enumerator_ `ICVFXCamera`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DisplayClusterMediaHelpers`
- L13 _namespace_ `namespace MediaId` (scope `DisplayClusterMediaHelpers`)
- L31 _prototype_ `FString GenerateMediaId(EMediaDeviceType DeviceType, EMediaOwnerType OwnerType, const FString& NodeId, const FString& DCRAName, const FString& OwnerName, uint8 Index, const FIntPoint* InTilePos = nullptr);` (scope `DisplayClusterMediaHelpers::MediaId`) — Generate media ID for a specific entity
- L35 _prototype_ `FString GenerateICVFXViewportName(const FString& ClusterNodeId, const FString& ICVFXCameraName);` (scope `DisplayClusterMediaHelpers`) — Generates internal ICVFX viewport IDs
- L38 _prototype_ `FString GenerateTileViewportName(const FString& InViewportId, const FIntPoint& InTilePos);` (scope `DisplayClusterMediaHelpers`) — Generates viewport tile IDs
- L41 _prototype_ `FString GenerateICVFXTileViewportName(const FString& ClusterNodeId, const FString& ICVFXCameraName, const FIntPoint& InTilePos);` (scope `DisplayClusterMediaHelpers`) — Generates viewport tile IDs for an ICVFX camera
- L44 _prototype_ `void ResampleTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FRHITexture* SrcTexture, FRHITexture* DstTexture, const FIntRect& SrcRect, const FIntRect& DstRect);` (scope `DisplayClusterMediaHelpers`) — Copy and resize an RHI texture
- L47 _prototype_ `bool IsValidLayout(const FIntPoint& TileLayout, const FIntPoint& MaxLayout);` (scope `DisplayClusterMediaHelpers`) — Checks whether a tile layout is valid
- L50 _prototype_ `bool IsValidTileCoordinate(const FIntPoint& TilePosition, const FIntPoint& TileLayout);` (scope `DisplayClusterMediaHelpers`) — Checks the correctness of the coordinates of the tile in the given layout

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/DisplayClusterMediaLog.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMedia, Log, All);` — Module-wide log categories
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMedia, Log, All);` — Module-wide log categories
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMediaSync, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMediaSync, Log, All);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/DisplayClusterMediaModule.h` (Private)


#### class `FDisplayClusterMediaModule`  
`class FDisplayClusterMediaModule : public IModuleInterface`  
_L21-102_
- inherits: `IModuleInterface`
- desc: Media module
- L26 _public prototype_ `FDisplayClusterMediaModule();`
- L27 _public prototype_ `~FDisplayClusterMediaModule() = default;`
- L32 _public prototype_ `virtual void StartupModule() override;`
- L33 _public prototype_ `virtual void ShutdownModule() override;`
- L39 _protected prototype_ `void InitializeMedia();` — Initialize all media internals (from instance)
- L42 _protected prototype_ `void ReleaseMedia();` — Release all media internals
- L45 _protected prototype_ `void StartCapture();` — Start media capture (all sources)
- L48 _protected prototype_ `void StopCapture();` — Stop media capture (all sources)
- L51 _protected prototype_ `void PlayMedia();` — Start playing media (all inputs)
- L54 _protected prototype_ `void StopMedia();` — Stop playing media (all inputs)
- L59 _private prototype_ `void InitializeBackbufferFullFrameOutput(const UDisplayClusterConfigurationClusterNode* ClusterNode, const FString& RootActorName, const FString& ClusterNodeId);` — Backbuffer output initializer (full frame)
- L62 _private prototype_ `void InitializeBackbufferUniformTilesOutput(const UDisplayClusterConfigurationClusterNode* ClusterNode, const FString& RootActorName, const FString& ClusterNodeId);` — Backbuffer output initializer (uniform tiles)
- L65 _private prototype_ `void InitializeViewportInput(const UDisplayClusterConfigurationViewport* Viewport, const FString& ViewportId, const FString& RootActorName, const FString& ClusterNodeId);` — Viewport input initializer
- L68 _private prototype_ `void InitializeViewportOutput(const UDisplayClusterConfigurationViewport* Viewport, const FString& ViewportId, const FString& RootActorName, const FString& ClusterNodeId);` — Viewport output initializer
- L71 _private prototype_ `void InitializeICVFXCameraFullFrameInput(const UDisplayClusterICVFXCameraComponent* ICVFXCameraComponent, const FString& RootActorName, const FString& ClusterNodeId);` — ICVFX camera input initializer (full frame)
- L74 _private prototype_ `void InitializeICVFXCameraFullFrameOutput(const UDisplayClusterICVFXCameraComponent* ICVFXCameraComponent, const FString& RootActorName, const FString& ClusterNodeId);` — ICVFX camera output initializer (full frame)
- L77 _private prototype_ `void InitializeICVFXCameraUniformTilesInput(const UDisplayClusterICVFXCameraComponent* ICVFXCameraComponent, const FString& RootActorName, const FString& ClusterNodeId);` — ICVFX camera input initializer (uniform tiles)
- L80 _private prototype_ `void InitializeICVFXCameraUniformTilesOutput(const UDisplayClusterICVFXCameraComponent* ICVFXCameraComponent, const FString& RootActorName, const FString& ClusterNodeId);` — ICVFX camera output initializer (uniform tiles)
- L85 _private prototype_ `void OnPreSubmitViewFamilies(TArray<FSceneViewFamilyContext*>&);` — PreSubmitViewFamilies event handler. It's used to initialize media on start.
- L88 _private prototype_ `void OnEnginePreExit();` — EnginePreExit event handler
- L93 _private member_ `TMap<FString, TSharedPtr<FDisplayClusterMediaCaptureBase>> CaptureDevices;` — Active media capture devices
- L96 _private member_ `TMap<FString, TSharedPtr<FDisplayClusterMediaInputBase>> InputDevices;` — Active media input devices
- L101 _private member_ `TSharedRef<FDisplayClusterFrameQueue> FrameQueue;` — Latency queue

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Input/DisplayClusterMediaInputBase.h` (Private)


#### class `FDisplayClusterMediaInputBase`  
`class FDisplayClusterMediaInputBase : public FDisplayClusterMediaBase , public FGCObject`  
_L24-132_
- inherits: `FDisplayClusterMediaBase,FGCObject`
- desc: Base media input adapter class
- L30 _public prototype_ `FDisplayClusterMediaInputBase( const FString& MediaId, const FString& ClusterNodeId, UMediaSource* MediaSource );`
- L39 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L40 _public function_ `virtual FString GetReferencerName() const override`
- L49 _public prototype_ `virtual bool Play();` — Start playback
- L52 _public prototype_ `virtual void Stop();` — Stop playback
- L57 _public function_ `UMediaSource* GetMediaSource() const` — Returns current media source
- L63 _public function_ `UMediaPlayer* GetMediaPlayer() const` — Returns current media player
- L69 _public function_ `UMediaTexture* GetMediaTexture() const` — Returns current media texture
- L92 _protected prototype_ `void ImportMediaData_RenderThread(FRHICommandListImmediate& RHICmdList, const FMediaInputTextureInfo& TextureInfo);` — Imports texture from a media source
- L97 _private prototype_ `void ImportMediaDataDirect_RenderThread(FRHICommandListImmediate& RHICmdList, FRHITexture* SrcTexture, const FIntRect& SrcRect, FRHITexture* DstTexture, const FIntRect& DstRect);` — Import implementation for non-OCIO path
- L100 _private prototype_ `void ImportMediaDataOCIO_RenderThread(FRHICommandListImmediate& RHICmdList, FRHITexture* SrcTexture, const FIntRect& SrcRect, FRHITexture* DstTexture, const FIntRect& DstRect, const FOpenColorIORenderPassResources& OCIOResources);` — Import implementation for OCIO path
- L105 _private prototype_ `void OnMediaEvent(EMediaEvent MediaEvent);` — Media events root handler
- L108 _private prototype_ `bool StartPlayer();` — Start playback. Used to restart playback after failure
- L111 _private prototype_ `void OnPlayerClosed();` — Media event handler. Called when media source is closed.
- L114 _private prototype_ `void OverrideTextureRegions_RenderThread(FIntRect& InOutSrcRect, FIntRect& InOutDstRect) const;` — [TEMP] A temporary workaround to cut off extra pixels for Rivermax input streams
- L119 _private member_ `TObjectPtr<UMediaSource> MediaSource;`
- L120 _private member_ `TObjectPtr<UMediaPlayer> MediaPlayer;`
- L121 _private member_ `TObjectPtr<UMediaTexture> MediaTexture;`
- L125 _private member_ `bool bWasPlayerStarted = false;` — Used to restart media player in the case it falls in error
- L128 _private member_ `double LastRestartTimestamp = 0;` — Used to control the rate at which we try to restart the player
- L131 _private member_ `bool bRunningRivermaxMedia = false;` — [Temp workaround] Whether current media is Rivermax

#### struct `FDisplayClusterMediaInputBase::FMediaInputTextureInfo`  
`struct FMediaInputTextureInfo`  
_L77-87_
- desc: Media playback data
- L80 _public member_ `FRHITexture* Texture = nullptr;` — Target texture for media input
- L83 _public member_ `FIntRect Region = { FIntPoint::ZeroValue, FIntPoint::ZeroValue };` — Target subregion
- L86 _public member_ `FOpenColorIORenderPassResources OCIOPassResources;` — OpenColorIO render pass parameters

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Input/DisplayClusterMediaInputCameraBase.h` (Private)


#### class `FDisplayClusterMediaInputCameraBase`  
`class FDisplayClusterMediaInputCameraBase : public FDisplayClusterMediaInputViewportBase , public FDisplayClusterMediaCameraCommon`  
_L14-32_
- inherits: `FDisplayClusterMediaInputViewportBase,FDisplayClusterMediaCameraCommon`
- desc: Base camera input adapter
- L20 _public prototype_ `FDisplayClusterMediaInputCameraBase( const FString& MediaId, const FString& ClusterNodeId, const FString& CameraId, const FString& CameraViewportId, UMediaSource* MediaSource );`
- L31 _protected prototype_ `virtual void UpdateLateOCIOState(const IDisplayClusterViewport* Viewport) override;` — Updates late OCIO state

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Input/DisplayClusterMediaInputCameraFull.h` (Private)


#### class `FDisplayClusterMediaInputCameraFull`  
`class FDisplayClusterMediaInputCameraFull : public FDisplayClusterMediaInputCameraBase`  
_L11-22_
- inherits: `FDisplayClusterMediaInputCameraBase`
- desc: Camera input adapter (full frame)
- L16 _public prototype_ `FDisplayClusterMediaInputCameraFull( const FString& MediaId, const FString& ClusterNodeId, const FString& CameraId, UMediaSource* MediaSource );`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Input/DisplayClusterMediaInputCameraTile.h` (Private)


#### class `FDisplayClusterMediaInputCameraTile`  
`class FDisplayClusterMediaInputCameraTile : public FDisplayClusterMediaInputCameraBase`  
_L11-23_
- inherits: `FDisplayClusterMediaInputCameraBase`
- desc: Camera input adapter (tile)
- L16 _public prototype_ `FDisplayClusterMediaInputCameraTile( const FString& MediaId, const FString& InClusterNodeId, const FString& CameraId, const FIntPoint& TilePosition, UMediaSource* MediaSource );`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Input/DisplayClusterMediaInputViewportBase.h` (Private)


#### class `FDisplayClusterMediaInputViewportBase`  
`class FDisplayClusterMediaInputViewportBase : public FDisplayClusterMediaInputBase`  
_L20-70_
- inherits: `FDisplayClusterMediaInputBase`
- desc: Base viewport input adapter
- L24 _public prototype_ `FDisplayClusterMediaInputViewportBase( const FString& MediaId, const FString& ClusterNodeId, const FString& ViewportId, UMediaSource* MediaSource );`
- L33 _public prototype_ `virtual bool Play() override;` — Start playback
- L36 _public prototype_ `virtual void Stop() override;` — Stop playback
- L39 _public function_ `const FString& GetViewportId() const` — Returns viewport ID bound for playback
- L47 _protected prototype_ `virtual void UpdateLateOCIOState(const IDisplayClusterViewport* Viewport);` — Updates late OCIO state
- L50 _protected prototype_ `virtual void HandleLateOCIOChanged(const FLateOCIOData& NewLateOCIOConfiguration) override;` — Process late OCIO state updates
- L55 _private prototype_ `void OnPreSubmitViewFamilies(TArray<FSceneViewFamilyContext*>&);` — PreSubmitViewFamilies event handler. It's used to initialize media on start.
- L58 _private prototype_ `void OnPostCrossGpuTransfer_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* ViewportManagerProxy, FViewport* Viewport);` — PostCrossGpuTransfer callback handler where media data is pushed into nDisplay internal buffers
- L61 _private prototype_ `void OnUpdateViewportMediaState(IDisplayClusterViewport* InViewport, EDisplayClusterViewportMediaState& InOutMediaState);` — UpdateViewportMediaState callback to configure media state for a viewoprt
- L66 _private member_ `const FString ViewportId;` — Viewport ID assigned for this media input
- L69 _private member_ `FOpenColorIORenderPassResources OCIOPassResources_RT;` — OCIO conversion pass resources (render thread data)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Input/DisplayClusterMediaInputViewportFull.h` (Private)


#### class `FDisplayClusterMediaInputViewportFull`  
`class FDisplayClusterMediaInputViewportFull : public FDisplayClusterMediaInputViewportBase`  
_L11-21_
- inherits: `FDisplayClusterMediaInputViewportBase`
- desc: Viewport input adapter (full frame)
- L15 _public prototype_ `FDisplayClusterMediaInputViewportFull( const FString& MediaId, const FString& ClusterNodeId, const FString& ViewportId, UMediaSource* MediaSource );`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Input/DisplayClusterMediaInputViewportTile.h` (Private)


#### class `FDisplayClusterMediaInputViewportTile`  
`class FDisplayClusterMediaInputViewportTile : public FDisplayClusterMediaInputViewportBase`  
_L11-22_
- inherits: `FDisplayClusterMediaInputViewportBase`
- desc: Viewport input adapter (tile)
- L15 _public prototype_ `FDisplayClusterMediaInputViewportTile( const FString& MediaId, const FString& ClusterNodeId, const FString& ViewportId, const FIntPoint& TilePosition, UMediaSource* MediaSource );`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Synchronization/LatencyQueue/DisplayClusterFrameQueue.h` (Private)


#### class `FDisplayClusterFrameQueue`  
`class FDisplayClusterFrameQueue : public TSharedFromThis<FDisplayClusterFrameQueue>`  
_L28-77_
- inherits: `TSharedFromThis<FDisplayClusterFrameQueue>`
- desc: Latency queue class Implements artificial latency feature. It's responsible for caching visual and shaders data to be used later. All the data that comes out of the rendering pipeline for current frame is cached to the HEAD of the queue. The final output is built from the TAIL view data. Every queue item contains all necessary information for every nD viewport. Note: this queue needs to be an intermediate part of the nD rendering pipeline. It should be moved there at some point during refactoring.
- L33 _public prototype_ `void Init();` — Initializes latency feature
- L35 _public prototype_ `void Release();` — Releases latency feature
- L39 _private prototype_ `void HandleBeginDraw();` — Handles BeginDraw event
- L41 _private prototype_ `void HandleEndDraw();` — Handles EndDraw event
- L43 _private prototype_ `void HandleProcessLatency_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportManagerProxy* ViewportManagerProxy, FViewport* Viewport);` — Handles latency processing event
- L45 _private prototype_ `void HandlePreProcessIcvfx_RenderThread(FRHICommandListImmediate& RHICmdList, const IDisplayClusterViewportProxy* ViewportProxy, FDisplayClusterShaderParameters_WarpBlend& WarpBlendParameters, FDisplayClusterShaderParameters_ICVFX& ICVFXParameters);` — Handles ICVFX pre-processing event
- L49 _private prototype_ `void SetLatency_RenderThread(int32 NewLatency);` — Changes current latency
- L51 _private prototype_ `void ProcessAddingPendingFrames_RenderThread();` — Auxiliary method to process queue resize
- L53 _private prototype_ `void AddToQueue_RenderThread(int32 FramesAmount);` — Auxiliary method to increase queue length by amount of frames
- L55 _private prototype_ `void RemoveFromQueue_RenderThread(int32 FramesAmout);` — Auxiliary method to decrease queue length by amount of frames
- L57 _private prototype_ `void CleanQueue_RenderThread();` — Cleans the queue container
- L59 _private prototype_ `void StepQueueIndices_RenderThread();` — Updates head and tail indices every frame
- L63 _private member_ `TArray<FDisplayClusterFrameQueueItem> Frames;` — Frames buffer
- L66 _private member_ `int32 LastRequestedLatency = 0;` — Latency value requested last time
- L69 _private member_ `int32 FramesPendingToAdd = 0;` — Amount of frames pending to add to the latency queue
- L71 _private member_ `int32 FramesAdded = 0;` — Amount of frames that were added at current frame
- L74 _private member_ `int32 IdxHead = 0;` — Head queue index
- L76 _private member_ `int32 IdxTail = 0;` — Tail queue index

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Private/Synchronization/LatencyQueue/DisplayClusterFrameQueueItem.h` (Private)


#### struct `FDisplayClusterFrameQueueItemView`  
`struct FDisplayClusterFrameQueueItemView`  
_L17-27_
- desc: Viewport data cache to be used in the latency queue
- L20 _public member_ `FTextureRHIRef Texture = nullptr;` — Cached view texture of a viewoprt
- L23 _public member_ `FDisplayClusterShaderParameters_WarpBlend WarpBlendData;` — Cached warp/blend shader data
- L26 _public member_ `FDisplayClusterShaderParameters_ICVFX IcvfxData;` — Cached ICVFX shader data

#### class `FDisplayClusterFrameQueueItem`  
`class FDisplayClusterFrameQueueItem`  
_L37-64_
- desc: Latency queue item class It's responsible for caching all required data for single frame. Note: this one is render thread only. It's never used on the main thread or any other thread.
- L40 _public prototype_ `FDisplayClusterFrameQueueItem() = default;`
- L41 _public prototype_ `FDisplayClusterFrameQueueItem(const FDisplayClusterFrameQueueItem& Other);`
- L42 _public prototype_ `FDisplayClusterFrameQueueItem(FDisplayClusterFrameQueueItem&& Other) = default;`
- L44 _public prototype_ `~FDisplayClusterFrameQueueItem() = default;`
- L48 _public prototype_ `void SaveView(FRHICommandListImmediate& RHICmdList, const FString& ViewportId, FRHITexture* Texture);` — Save texture of a viewport
- L50 _public prototype_ `void LoadView(FRHICommandListImmediate& RHICmdList, const FString& ViewportId, FRHITexture* Texture);` — Load texture of a viewport
- L53 _public prototype_ `void SaveData(FRHICommandListImmediate& RHICmdList, const FString& ViewportId, FDisplayClusterShaderParameters_WarpBlend& WarpBlendParameters, FDisplayClusterShaderParameters_ICVFX& ICVFXParameters);` — Save shader data of a viewport
- L55 _public prototype_ `void LoadData(FRHICommandListImmediate& RHICmdList, const FString& ViewportId, FDisplayClusterShaderParameters_WarpBlend& WarpBlendParameters, FDisplayClusterShaderParameters_ICVFX& ICVFXParameters);` — Load shader data of a viewport
- L59 _private prototype_ `FTextureRHIRef CreateTexture(FRHICommandListBase& RHICmdList, FRHITexture* ReferenceTexture);` — Auxiliary function that creates a new texture based on the reference (same format, size)
- L63 _private member_ `TMap<FString, FDisplayClusterFrameQueueItemView> Views;` — Available views (viewports)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Public/Synchronization/DisplayClusterMediaOutputSynchronizationPolicyEthernetBarrier.h` (Public)


#### class `FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierHandler`  
`class FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierHandler : public FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler`  
_L12-29_
- inherits: `FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler`
- desc: Synchronization logic handler class for UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrier.
- L15 _private typedef_ `using Super = FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler;`
- L19 _public prototype_ `FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierHandler(UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrier* InPolicyObject);`
- L22 _public prototype_ `virtual TSubclassOf<UDisplayClusterMediaOutputSynchronizationPolicy> GetPolicyClass() const override;`
- L27 _protected prototype_ `virtual void Synchronize() override;`

#### class `UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrier`  
`class UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrier : public UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBase`  
_L35-45_
- reflection: `UCLASS(editinlinenew, Blueprintable, meta = (DisplayName = "Ethernet Barrier"))`
- inherits: `UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBase`
- desc: EthernetBarrier media synchronization policy implementation
- L41 _protected prototype_ `virtual TSharedPtr<IDisplayClusterMediaOutputSynchronizationPolicyHandler> GetHandler() override;`
- L44 _protected member_ `TSharedPtr<IDisplayClusterMediaOutputSynchronizationPolicyHandler> Handler;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Public/Synchronization/DisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBase.h` (Public)


#### class `FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler`  
`class FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler : public IDisplayClusterMediaOutputSynchronizationPolicyHandler`  
_L15-107_
- inherits: `IDisplayClusterMediaOutputSynchronizationPolicyHandler`
- desc: Synchronization logic handler class for UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBase.
- L20 _public prototype_ `FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler(UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBase* InPolicyObject);`
- L25 _public prototype_ `virtual bool StartSynchronization(UMediaCapture* MediaCapture, const FString& MediaId) override;`
- L26 _public prototype_ `virtual void StopSynchronization() override;`
- L27 _public prototype_ `virtual bool IsRunning() override final;`
- L28 _public prototype_ `virtual bool IsCaptureTypeSupported(UMediaCapture* MediaCapture) const override;`
- L34 _public prototype_ `virtual void Synchronize() = 0;` — Children implement their own sync approaches.
- L39 _protected prototype_ `virtual bool InitializeBarrier(const FString& SyncInstanceId);` — Initializes dynamic barrier on the primary node.
- L42 _protected prototype_ `void SyncThreadOnBarrier();` — Synchronizes calling thread at the barrier.
- L45 _protected prototype_ `FString GetMediaDeviceId() const;` — Returns media device ID being synchronized
- L49 _protected function_ `IDisplayClusterGenericBarriersClient* const GetBarrierClient() const` — `UE_DEPRECATED(5.6, "This method has been deprecated. Please use another 'GetBarrierClient' that returns TSharedPtr.")` — Returns barrier client created for this sync policy
- L55 _protected prototype_ `TSharedPtr<IDisplayClusterGenericBarriersClient> GetBarrierClient();` — Returns barrier client created for this sync policy
- L58 _protected prototype_ `const FString& GetBarrierId() const;` — Get Barrier ID for this sync policy
- L61 _protected prototype_ `const FString& GetThreadMarker() const;` — Get thread marker for this sync policy
- L66 _private prototype_ `void ReleaseBarrier();` — Releases dynamic barrier on the primary node.
- L69 _private prototype_ `FString GenerateBarrierName() const;` — Generates name of the dynamic barrier.
- L72 _private prototype_ `void GenerateSyncCallersMapping(TMap<FString, TSet<FString>>& OutMarkers) const;` — Generates per-node sync callers mapping.
- L75 _private prototype_ `void LogSyncCallersMapping(const TMap<FString, TSet<FString>>& OutNodeToSyncCallers) const;` — Auxiliary function to log custom barrier callers mapping.
- L78 _private function_ `void GenerateListOfThreadMarkers(TArray<FString>& OutMarkers) const` — `UE_DEPRECATED(5.6, "This method has been deprecated. Please use 'GenerateSyncCallersMapping'.")`
- L82 _private prototype_ `void ProcessMediaSynchronizationCallback();` — Handles media capture sync callbacks.
- L87 _protected member_ `TObjectPtr<UMediaCapture> CapturingDevice;` — Capture device being used.
- L90 _protected member_ `int32 BarrierTimeoutMs = 3000;` — Barrier timeout (ms)
- L94 _private member_ `bool bIsRunning = false;` — Is synchronization currently active.
- L97 _private member_ `FString MediaDeviceId;` — ID of media device being synchronized.
- L100 _private member_ `FString BarrierId;` — Unique barrier name to use.
- L103 _private member_ `FString ThreadMarker;` — Unique thread (caller) marker to be used on the barrier.
- L106 _private member_ `TSharedPtr<IDisplayClusterGenericBarriersClient> EthernetBarrierClient;` — Generic barriers API.

#### class `UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBase`  
`class UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBase : public UDisplayClusterMediaOutputSynchronizationPolicy`  
_L115-125_
- reflection: `UCLASS(Abstract, editinlinenew, BlueprintType, hidecategories = (Object))`
- inherits: `UDisplayClusterMediaOutputSynchronizationPolicy`
- desc: Base class for Ethernet barrier based media synchronization policies. It encapsulates network barriers related settings.
- L124 _public member_ `int32 BarrierTimeoutMs = 3000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Barrier Timeout (ms)", ClampMin = "1", ClampMax = "10000", UIMin = "1", UIMax = "10000"))` — Barrier timeout (ms)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Public/Synchronization/DisplayClusterMediaOutputSynchronizationPolicyThresholdBase.h` (Public)


#### class `FDisplayClusterMediaOutputSynchronizationPolicyThresholdBaseHandler`  
`class FDisplayClusterMediaOutputSynchronizationPolicyThresholdBaseHandler : public FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler`  
_L12-32_
- inherits: `FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler`
- desc: Synchronization logic handler class for UDisplayClusterMediaOutputSynchronizationPolicyThresholdBase.
- L15 _private typedef_ `using Super = FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler;`
- L18 _public prototype_ `FDisplayClusterMediaOutputSynchronizationPolicyThresholdBaseHandler(UDisplayClusterMediaOutputSynchronizationPolicyThresholdBase* InPolicyObject);`
- L22 _protected prototype_ `virtual void Synchronize() override;`
- L27 _protected prototype_ `virtual double GetTimeBeforeNextSyncPoint() = 0;` — Returns amount of time before next synchronization point.
- L31 _protected member_ `int32 MarginMs = 5;` — Synchronization margin (ms)

#### class `UDisplayClusterMediaOutputSynchronizationPolicyThresholdBase`  
`class UDisplayClusterMediaOutputSynchronizationPolicyThresholdBase : public UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBase`  
_L40-49_
- reflection: `UCLASS(Abstract, editinlinenew, BlueprintType, hidecategories = (Object))`
- inherits: `UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBase`
- desc: Base class for threshold based media synchronization policies. Basically it uses the same approach that we use in 'Ethernet' sync policy where v-blanks are used as the timepoints.
- L48 _public member_ `int32 MarginMs = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Margin (ms)", ClampMin = "1", ClampMax = "20", UIMin = "1", UIMax = "20"))` — Synchronization margin (ms)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMedia/Public/Synchronization/DisplayClusterMediaOutputSynchronizationPolicyVblank.h` (Public)


#### class `FDisplayClusterMediaOutputSynchronizationPolicyVblankHandler`  
`class FDisplayClusterMediaOutputSynchronizationPolicyVblankHandler : public FDisplayClusterMediaOutputSynchronizationPolicyThresholdBaseHandler`  
_L14-35_
- inherits: `FDisplayClusterMediaOutputSynchronizationPolicyThresholdBaseHandler`
- desc: Synchronization logic handler class for UDisplayClusterMediaOutputSynchronizationPolicyVblank.
- L17 _private typedef_ `using Super = FDisplayClusterMediaOutputSynchronizationPolicyThresholdBaseHandler;`
- L21 _public prototype_ `FDisplayClusterMediaOutputSynchronizationPolicyVblankHandler(UDisplayClusterMediaOutputSynchronizationPolicyVblank* InPolicyObject);`
- L24 _public prototype_ `virtual TSubclassOf<UDisplayClusterMediaOutputSynchronizationPolicy> GetPolicyClass() const override;`
- L25 _public prototype_ `virtual bool StartSynchronization(UMediaCapture* MediaCapture, const FString& MediaId) override;`
- L30 _protected prototype_ `virtual double GetTimeBeforeNextSyncPoint() override;` — Returns amount of time before next synchronization point.
- L34 _private member_ `TSharedPtr<IDisplayClusterVblankMonitor> VblankMonitor;` — V-blank monitor

#### class `UDisplayClusterMediaOutputSynchronizationPolicyVblank`  
`class UDisplayClusterMediaOutputSynchronizationPolicyVblank : public UDisplayClusterMediaOutputSynchronizationPolicyThresholdBase`  
_L41-51_
- reflection: `UCLASS(editinlinenew, Blueprintable, meta = (DisplayName = "V-blank"))`
- inherits: `UDisplayClusterMediaOutputSynchronizationPolicyThresholdBase`
- desc: Vblank media synchronization policy config
- L47 _public prototype_ `virtual TSharedPtr<IDisplayClusterMediaOutputSynchronizationPolicyHandler> GetHandler() override;`
- L50 _protected member_ `TSharedPtr<IDisplayClusterMediaOutputSynchronizationPolicyHandler> Handler;`
