# Plugins / OpenXRHMD

- module root: `Plugins/Runtime/OpenXR/Source/OpenXRHMD`
- headers: 18; symbols: 802
- symbol kinds: class=21, delegate=1, enum=5, enumerator=19, function=173, macro=21, member=247, namespace=2, prototype=289, struct=15, typedef=6, union=1, variable=2
- PrivateDependencyModuleNames: AugmentedReality, BuildSettings, Core, CoreUObject, DeveloperSettings, EditorFramework, Engine, EngineSettings, InputCore, RHI, RenderCore, Renderer, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: D3D11RHI, D3D12RHI, DX11, DX12, HeadMountedDisplay, OpenGL, OpenGLDrv, Vulkan, VulkanRHI, XRBase
- PublicIncludePathModuleNames: OpenXR

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Internal/Epic_openxr.h` (Internal)


#### enum `XrStructureTypeEPIC`  
`typedef enum XrStructureTypeEPIC`  
_L15-19_
- L16 _public enumerator_ `XR_TYPE_SPACE_ACCELERATION_EPIC = XR_TYPE_EPIC`
- L17 _public enumerator_ `XR_TYPE_RHI_CONTEXT_EPIC`
- L18 _public enumerator_ `XR_STRUCTURE_TYPE_EPIC_MAX_ENUM = 0x7FFFFFFF`

#### struct `XrSpaceAccelerationEPIC`  
`typedef struct XrSpaceAccelerationEPIC`  
_L34-40_
- L35 _public member_ `XrStructureType type;`
- L36 _public member_ `void* XR_MAY_ALIAS next;`
- L37 _public member_ `XrSpaceAccelerationFlagsEPIC accelerationFlags;`
- L38 _public member_ `XrVector3f linearAcceleration;` — m/s^2
- L39 _public member_ `XrVector3f angularAcceleration;` — rad/s^2

#### struct `XrRHIContextEPIC`  
`typedef struct XrRHIContextEPIC`  
_L42-46_
- L43 _public member_ `XrStructureType type;`
- L44 _public member_ `void* XR_MAY_ALIAS next;`
- L45 _public member_ `class IRHICommandContext* RHIContext;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define XR_TYPE_EPIC 1000059050` — This number is in a block that is unused by openxr, and that seemed unlikely to be used soon based on the patterns of usage. But if it ever was used by openxr we would have to change it. See openxr.h for the list.  This is XR_TYPE_VIEW_CONFIGURATION_VIEW_FOV_EPIC + 50.  This is inside the reserved range for the XR_EPIC_view_configuration_fov extension.
- L19 _typedef_ `} XrStructureTypeEPIC;`
- L24 _macro_ `#define XR_EPIC_space_acceleration 1`
- L25 _macro_ `#define XR_EPIC_space_acceleration_SPEC_VERSION 1`
- L26 _macro_ `#define XR_EPIC_SPACE_ACCELERATION_NAME "XR_EPIC_space_acceleration"`
- L28 _typedef_ `typedef XrFlags64 XrSpaceAccelerationFlagsEPIC;`
- L31 _variable_ `static const XrSpaceAccelerationFlagsEPIC XR_SPACE_ACCELERATION_LINEAR_VALID_BIT_EPIC = 0x00000001;` — Flag bits for XrSpaceAccelerationFlagsEPIC
- L32 _variable_ `static const XrSpaceAccelerationFlagsEPIC XR_SPACE_ACCELERATION_ANGULAR_VALID_BIT_EPIC = 0x00000002;`
- L40 _typedef_ `} XrSpaceAccelerationEPIC;`
- L46 _typedef_ `} XrRHIContextEPIC;`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Internal/OpenXRHMD_RenderBridge.h` (Internal)


#### class `FOpenXRRenderBridge`  
`class FOpenXRRenderBridge : public FXRRenderBridge`  
_L16-81_
- inherits: `FXRRenderBridge`
- L19 _public function_ `FOpenXRRenderBridge(XrInstance InInstance) : Instance(InInstance) , OpenXRHMD(nullptr)`
- L24 _public function_ `void SetOpenXRHMD(FOpenXRHMD* InHMD)`
- L25 _public function_ `virtual uint64 GetGraphicsAdapterLuid(XrSystemId InSystem)`
- L26 _public prototype_ `virtual void* GetGraphicsBinding(XrSystemId InSystem) = 0;`
- L27 _public prototype_ `virtual FXRSwapChainPtr CreateSwapchain(XrSession InSession, uint8 Format, uint8& OutActualFormat, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, ETextureDimension Dimension, ETextureCreateFlags CreateFlags, const FClearValueBinding& ClearValueBinding, ETextureCreateFlags AuxiliaryCreateFlags = ETextureCreateFlags::None) = 0;`
- L28 _public function_ `FXRSwapChainPtr CreateSwapchain(XrSession InSession, FRHITexture* Template, ETextureCreateFlags CreateFlags)`
- L57 _public function_ `virtual void RunOnRHISubmissionThread(TFunction<void()>&& CodeToRun)` — Used to wrap OpenXR calls which can submit directly to the graphics queue (xrBeginFrame, xrEndFrame, xrAcquireSwapchainImage, xrReleaseSwapchainImage) and their surrounding logic. When a submission thread is in use, only that thread is permitted to submit to the graphics queue. Implmentations for RHIs using a submission thread should override this function to run the provided code on the submission thread via RHIRunOnQueue. Note: This is not necessary for calls in Present/HMDOnFinishRendering_RHIThread because FD3D12Viewport::Present and FVulkanViewport::Present both flush the submission thread before calling FRHICustomPresent::Present.
- L64 _public prototype_ `virtual bool Present(FRHIViewport* Viewport, IRHICommandContext& RHICmdContext, int32& InOutSyncInterval) override;` — FRHICustomPresent
- L65 _public prototype_ `virtual bool PresentOnSubmissionThread(int32& InOutSyncInterval) override;`
- L67 _public function_ `virtual bool Support10BitSwapchain() const`
- L69 _public function_ `virtual bool HDRGetMetaDataForStereo(EDisplayOutputFormat& OutDisplayOutputFormat, EDisplayColorGamut& OutDisplayColorGamut, bool& OutbHDRSupported)`
- L71 _public function_ `virtual void SetSkipRate(uint32 SkipRate)`
- L73 _public prototype_ `virtual void HMDOnFinishRendering_RHIThread(IRHICommandContext& RHICmdContext);`
- L74 _public prototype_ `virtual void HMDOnFinishRendering_SubmissionThread();`
- L77 _protected member_ `XrInstance Instance;`
- L78 _protected member_ `FOpenXRHMD* OpenXRHMD;`

#### Free symbols / members of external scopes

- L84 _prototype_ `FOpenXRRenderBridge* CreateRenderBridge_D3D11(XrInstance InInstance);`
- L87 _prototype_ `FOpenXRRenderBridge* CreateRenderBridge_D3D12(XrInstance InInstance);`
- L90 _prototype_ `FOpenXRRenderBridge* CreateRenderBridge_OpenGLES(XrInstance InInstance);`
- L93 _prototype_ `FOpenXRRenderBridge* CreateRenderBridge_OpenGL(XrInstance InInstance);`
- L96 _prototype_ `FOpenXRRenderBridge* CreateRenderBridge_Vulkan(XrInstance InInstance);`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Internal/OpenXRHMD_Swapchain.h` (Internal)


#### class `FOpenXRSwapchain`  
`class FOpenXRSwapchain : public FXRSwapChain`  
_L12-35_
- inherits: `FXRSwapChain`
- L15 _public prototype_ `FOpenXRSwapchain(TArray<FTextureRHIRef>&& InRHITextureSwapChain, const FTextureRHIRef & InRHITexture, XrSwapchain InHandle);`
- L16 _public prototype_ `virtual ~FOpenXRSwapchain();`
- L18 _public prototype_ `virtual void IncrementSwapChainIndex_RHIThread() override final;`
- L19 _public prototype_ `virtual void WaitCurrentImage_RHIThread(int64 Timeout) override final;`
- L20 _public prototype_ `virtual void ReleaseCurrentImage_RHIThread(IRHICommandContext* RHICmdContext) override final;`
- L22 _public function_ `XrSwapchain GetHandle()`
- L23 _public prototype_ `static XrSwapchain CreateSwapchain(XrSession InSession, uint32 PlatformFormat, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, ETextureDimension Dimension, ETextureCreateFlags CreateFlags, void* Next = nullptr);`
- L24 _public prototype_ `static uint8 GetNearestSupportedSwapchainFormat(XrSession InSession, uint8 RequestedFormat, TFunction<uint32(uint8)> ToPlatformFormat = nullptr);`
- L25 _public prototype_ `void GetFragmentDensityMaps(TArray<FTextureRHIRef>& OutTextureChain, const bool bIsMobileMultiViewEnabled);`
- L28 _protected member_ `XrSwapchain Handle;`
- L31 _protected member_ `std::atomic<bool> ImageAcquired;` — Whether the image associated with the swapchain has been acquired.
- L34 _protected member_ `std::atomic<bool> ImageReady;` — Whether the image associated with the swapchain is ready for being written to.

#### Free symbols / members of external scopes

- L38 _prototype_ `FXRSwapChainPtr CreateSwapchain_D3D11(XrSession InSession, uint8 Format, uint8& OutActualFormat, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, ETextureDimension Dimension, ETextureCreateFlags CreateFlags, const FClearValueBinding& ClearValueBinding, ETextureCreateFlags AuxiliaryCreateFlags = ETextureCreateFlags::None);`
- L41 _prototype_ `FXRSwapChainPtr CreateSwapchain_D3D12(XrSession InSession, uint8 Format, uint8& OutActualFormat, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, ETextureDimension Dimension, ETextureCreateFlags CreateFlags, const FClearValueBinding& ClearValueBinding, ETextureCreateFlags AuxiliaryCreateFlags = ETextureCreateFlags::None);`
- L44 _prototype_ `FXRSwapChainPtr CreateSwapchain_OpenGL(XrSession InSession, uint8 Format, uint8& OutActualFormat, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, ETextureDimension Dimension, ETextureCreateFlags CreateFlags, const FClearValueBinding& ClearValueBinding, ETextureCreateFlags AuxiliaryCreateFlags = ETextureCreateFlags::None);`
- L47 _prototype_ `FXRSwapChainPtr CreateSwapchain_OpenGLES(XrSession InSession, uint8 Format, uint8& OutActualFormat, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, ETextureDimension Dimension, ETextureCreateFlags CreateFlags, const FClearValueBinding& ClearValueBinding, ETextureCreateFlags AuxiliaryCreateFlags = ETextureCreateFlags::None);`
- L50 _prototype_ `FXRSwapChainPtr CreateSwapchain_Vulkan(XrSession InSession, uint8 Format, uint8& OutActualFormat, uint32 SizeX, uint32 SizeY, uint32 ArraySize, uint32 NumMips, uint32 NumSamples, ETextureDimension Dimension, ETextureCreateFlags CreateFlags, const FClearValueBinding& ClearValueBinding, ETextureCreateFlags AuxiliaryCreateFlags = ETextureCreateFlags::None);`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Private/FBFoveationImageGenerator.h` (Private)


#### class `FFBFoveationImageGenerator`  
`class FFBFoveationImageGenerator : public IVariableRateShadingImageGenerator`  
_L13-51_
- inherits: `IVariableRateShadingImageGenerator`
- L16 _public prototype_ `FFBFoveationImageGenerator(bool bIsFoveationExtensionSupported, XrInstance InInstance, FOpenXRHMD* HMD, bool bMobileMultiViewEnabled);`
- L17 _public function_ `virtual ~FFBFoveationImageGenerator() override`
- L19 _public function_ `bool IsFoveationExtensionEnabled()`
- L21 _public prototype_ `void UpdateFoveationImages(bool bReallocatedSwapchain = false);` — bReallocatedSwapchain forces foveation images to update even if the foveation params haven't changed.
- L22 _public prototype_ `void SetCurrentFrameSwapchainIndex(int32 CurrentFrameSwapchainIndex);`
- L25 _public prototype_ `virtual FRDGTextureRef GetImage(FRDGBuilder& GraphBuilder, const FViewInfo& ViewInfo, FVariableRateShadingImageManager::EVRSImageType ImageType, bool bGetSoftwareImage = false) override;` — IVariableRateShadingImageGenerator interface
- L26 _public prototype_ `virtual void PrepareImages(FRDGBuilder& GraphBuilder, const FSceneViewFamily& ViewFamily, const FMinimalSceneTextures& SceneTextures, bool bPrepareHardwareImages, bool bPrepareSoftwareImages) override;`
- L27 _public prototype_ `virtual bool IsEnabled() const override;`
- L28 _public prototype_ `virtual bool IsSupportedByView(const FSceneView& View) const override;`
- L29 _public prototype_ `virtual FRDGTextureRef GetDebugImage(FRDGBuilder& GraphBuilder, const FViewInfo& ViewInfo, FVariableRateShadingImageManager::EVRSImageType ImageType, bool bGetSoftwareImage = false) override;`
- L30 _public function_ `virtual FVariableRateShadingImageManager::EVRSSourceType GetType() const override`
- L38 _private member_ `FOpenXRHMD* OpenXRHMD;`
- L39 _private member_ `bool bIsMobileMultiViewEnabled;`
- L40 _private member_ `int32 CurrentFrameSwapchainIndex;`
- L43 _private member_ `bool bFoveationExtensionSupported;` — XR_FB_foveation
- L44 _private member_ `XrFoveationLevelFB FoveationLevel;`
- L45 _private member_ `float VerticalOffset;`
- L46 _private member_ `XrFoveationDynamicFB FoveationDynamic;`
- L47 _private member_ `TArray<FTextureRHIRef> FoveationImages;`
- L48 _private member_ `PFN_xrCreateFoveationProfileFB xrCreateFoveationProfileFB;`
- L49 _private member_ `PFN_xrUpdateSwapchainFB xrUpdateSwapchainFB;`
- L50 _private member_ `PFN_xrDestroyFoveationProfileFB xrDestroyFoveationProfileFB;`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Private/OpenXRAssetManager.h` (Private)


#### class `FOpenXRAssetManager`  
`class FOpenXRAssetManager : public IXRSystemAssets`  
_L15-38_
- inherits: `IXRSystemAssets`
- L18 _public prototype_ `FOpenXRAssetManager(XrInstance Instance, FOpenXRHMD* InHMD);`
- L19 _public prototype_ `virtual ~FOpenXRAssetManager();`
- L24 _public prototype_ `virtual bool EnumerateRenderableDevices(TArray<int32>& DeviceListOut) override;`
- L25 _public prototype_ `virtual int32 GetDeviceId(EControllerHand ControllerHand) override;`
- L26 _public prototype_ `virtual UPrimitiveComponent* CreateRenderComponent(const int32 DeviceId, AActor* Owner, EObjectFlags Flags, const bool bForceSynchronous, const FXRComponentLoadComplete& OnLoadComplete) override;`
- L29 _private member_ `FOpenXRHMD* OpenXRHMD;`
- L31 _private member_ `XrPath LeftHand;`
- L32 _private member_ `XrPath RightHand;`
- L33 _private member_ `TMap<TPair<XrPath, XrPath>, FSoftObjectPath> DeviceMeshes;`
- L36 _private member_ `FName Quest1, Quest2;` — Oculus Quest platforms use different Touch controllers, but share the same interaction profile
- L36 _private member_ `FName Quest1, Quest2;` — Oculus Quest platforms use different Touch controllers, but share the same interaction profile
- L37 _private member_ `TMap<XrPath, FSoftObjectPath> Quest1Meshes, Quest2Meshes;`
- L37 _private member_ `TMap<XrPath, FSoftObjectPath> Quest1Meshes, Quest2Meshes;`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Private/OpenXRHMD.h` (Private)


#### class `FOpenXRHMD`  
`class FOpenXRHMD : public FHeadMountedDisplayBase , public FXRRenderTargetManager , public FHMDSceneViewExtension , public FOpenXRAssetManager , public FSimpleLayerManager , public IOpenXRExtensionPluginDelegates , public IOpenXRHMD`  
_L40-640_
- inherits: `FHeadMountedDisplayBase,FXRRenderTargetManager,FHMDSceneViewExtension,FOpenXRAssetManager,FSimpleLayerManager,IOpenXRExtensionPluginDelegates,IOpenXRHMD`
- desc: Simple Head Mounted Display
- L203 _public prototype_ `FRIEND_ENUM_CLASS_FLAGS(EOpenXRLayerStateFlags);`
- L254 _public function_ `virtual FName GetSystemName() const override` — IXRTrackingSystem interface
- L262 _public function_ `int32 GetXRSystemFlags() const override`
- L279 _public prototype_ `virtual bool EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type = EXRTrackedDeviceType::Any) override;`
- L281 _public prototype_ `virtual void SetInterpupillaryDistance(float NewInterpupillaryDistance) override;`
- L282 _public prototype_ `virtual float GetInterpupillaryDistance() const override;`
- L283 _public prototype_ `virtual bool GetRelativeEyePose(int32 InDeviceId, int32 InViewIndex, FQuat& OutOrientation, FVector& OutPosition) override;`
- L285 _public prototype_ `virtual void ResetOrientationAndPosition(float Yaw = 0.f) override;`
- L286 _public prototype_ `virtual void ResetOrientation(float Yaw = 0.f) override;`
- L287 _public prototype_ `virtual void ResetPosition() override;`
- L288 _public prototype_ `virtual void Recenter(EOrientPositionSelector::Type Selector, float Yaw = 0.f);`
- L290 _public prototype_ `virtual bool GetIsTracked(int32 DeviceId) override;`
- L291 _public prototype_ `virtual bool GetCurrentPose(int32 DeviceId, FQuat& CurrentOrientation, FVector& CurrentPosition) override;`
- L292 _public prototype_ `virtual bool GetPoseForTime(int32 DeviceId, FTimespan Timespan, bool& OutTimeWasUsed, FQuat& CurrentOrientation, FVector& CurrentPosition, bool& bProvidedLinearVelocity, FVector& LinearVelocity, bool& bProvidedAngularVelocity, FVector& AngularVelocityAsAxisAndLength, bool& bProvidedLinearAcceleration, FVector& LinearAcceleration, float WorldToMetersScale) override;`
- L293 _public prototype_ `virtual bool GetCurrentInteractionProfile(const EControllerHand Hand, FString& InteractionProfile) override;`
- L295 _public prototype_ `virtual void SetBaseRotation(const FRotator& InBaseRotation) override;`
- L296 _public prototype_ `virtual FRotator GetBaseRotation() const override;`
- L298 _public prototype_ `virtual void SetBaseOrientation(const FQuat& InBaseOrientation) override;`
- L299 _public prototype_ `virtual FQuat GetBaseOrientation() const override;`
- L301 _public prototype_ `virtual void SetBasePosition(const FVector& InBasePosition) override;`
- L302 _public prototype_ `virtual FVector GetBasePosition() const override;`
- L304 _public prototype_ `virtual void SetTrackingOrigin(EHMDTrackingOrigin::Type NewOrigin) override;`
- L305 _public prototype_ `virtual EHMDTrackingOrigin::Type GetTrackingOrigin() const override;`
- L307 _public function_ `virtual class IHeadMountedDisplay* GetHMDDevice() override`
- L311 _public function_ `virtual class TSharedPtr< class IStereoRendering, ESPMode::ThreadSafe > GetStereoRenderingDevice() override`
- L316 _public function_ `virtual class IStereoLayers* GetStereoLayers() override`
- L321 _public prototype_ `virtual void GetMotionControllerState(UObject* WorldContext, const EXRSpaceType XRSpaceType, const EControllerHand Hand, const EXRControllerPoseType XRControllerPoseType, FXRMotionControllerState& MotionControllerState) override;`
- L322 _public prototype_ `virtual void GetHandTrackingState(UObject* WorldContext, const EXRSpaceType XRSpaceType, const EControllerHand Hand, FXRHandTrackingState& HandTrackingState) override;`
- L324 _public prototype_ `virtual float GetWorldToMetersScale() const override;`
- L326 _public prototype_ `virtual FVector2D GetPlayAreaBounds(EHMDTrackingOrigin::Type Origin) const override;`
- L327 _public prototype_ `virtual bool GetPlayAreaRect(FTransform& OutTransform, FVector2D& OutExtent) const override;`
- L328 _public prototype_ `virtual bool GetTrackingOriginTransform(TEnumAsByte<EHMDTrackingOrigin::Type> Origin, FTransform& OutTransform) const override;`
- L330 _public prototype_ `virtual bool HDRGetMetaDataForStereo(EDisplayOutputFormat& OutDisplayOutputFormat, EDisplayColorGamut& OutDisplayColorGamut, bool& OutbHDRSupported) override;`
- L333 _protected prototype_ `bool StartSession();`
- L334 _protected prototype_ `bool StopSession();`
- L335 _protected prototype_ `bool OnStereoStartup();`
- L336 _protected prototype_ `bool OnStereoTeardown();`
- L337 _protected prototype_ `bool ReadNextEvent(XrEventDataBuffer* buffer);`
- L338 _protected prototype_ `void DestroySession();`
- L340 _protected prototype_ `void RequestExitApp();`
- L342 _protected prototype_ `void BuildOcclusionMeshes();`
- L343 _protected prototype_ `bool BuildOcclusionMesh(XrVisibilityMaskTypeKHR Type, int View, FHMDViewMesh& Mesh);`
- L345 _protected prototype_ `FPipelinedFrameStateAccessorReadOnly GetPipelinedFrameStateForThread() const;`
- L346 _protected prototype_ `FPipelinedFrameStateAccessorReadWrite GetPipelinedFrameStateForThread();`
- L348 _protected prototype_ `void UpdateDeviceLocations(bool bUpdateOpenXRExtensionPlugins);`
- L349 _protected prototype_ `void EnumerateViews(FPipelinedFrameState& PipelineState);`
- L350 _protected prototype_ `void LocateViews(FPipelinedFrameState& PipelinedState, bool ResizeViewsArray = false);`
- L352 _protected prototype_ `void AllocateDepthTextureInternal(uint32 SizeX, uint32 SizeY, uint32 NumSamples, uint32 ArraySize);`
- L354 _protected prototype_ `void SetupFrameLayers_GameThread();`
- L355 _protected prototype_ `void SetupFrameLayers_RenderThread(FRDGBuilder& GraphBuilder);`
- L356 _protected prototype_ `void DrawEmulatedLayers_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& InView);`
- L357 _protected prototype_ `void DrawBackgroundCompositedEmulatedLayers_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& InView);`
- L358 _protected prototype_ `void DrawEmulatedFaceLockedLayers_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& InView);`
- L359 _protected prototype_ `void DrawAllEmulatedLayers_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& InView);`
- L362 _protected prototype_ `virtual void MarkTextureForUpdate(uint32 LayerId) override;` — TStereoLayerManager<FLayerDesc>
- L363 _protected prototype_ `virtual uint32 CreateLayer(const FLayerDesc& InLayerDesc) override;`
- L364 _protected prototype_ `virtual void DestroyLayer(uint32 LayerId) override;`
- L365 _protected prototype_ `virtual void SetLayerDesc(uint32 LayerId, const FLayerDesc& InLayerDesc) override;`
- L367 _protected prototype_ `virtual bool PopulateAnalyticsAttributes(TArray<struct FAnalyticsEventAttribute>& EventAttributes) override;`
- L370 _protected prototype_ `bool AcquireSystemIdAndProperties();` — Populates System, SystemProperties and related fields. Can get called before OnStereoStartup.
- L372 _protected prototype_ `[[nodiscard]] int32 GetNumHeaders() const;`
- L376 _public function_ `virtual bool DoesSupportLateProjectionUpdate() const override` — IXRTrackingSystem interface
- L377 _public prototype_ `virtual FString GetVersionString() const override;`
- L378 _public prototype_ `virtual bool IsTracking(int32 DeviceId) override;`
- L379 _public prototype_ `virtual bool HasValidTrackingPosition() override;`
- L380 _public function_ `virtual IOpenXRHMD* GetIOpenXRHMD()`
- L383 _public prototype_ `virtual bool IsHMDConnected() override;` — IHeadMountedDisplay interface
- L384 _public function_ `virtual bool DoesSupportPositionalTracking() const override`
- L385 _public prototype_ `virtual bool IsHMDEnabled() const override;`
- L386 _public prototype_ `virtual void EnableHMD(bool allow = true) override;`
- L387 _public prototype_ `virtual FName GetHMDName() const override;`
- L388 _public prototype_ `virtual bool GetHMDMonitorInfo(MonitorInfo&) override;`
- L389 _public prototype_ `virtual void GetFieldOfView(float& OutHFOVInDegrees, float& OutVFOVInDegrees) const override;`
- L390 _public prototype_ `virtual bool IsChromaAbCorrectionEnabled() const override;`
- L391 _public prototype_ `virtual float GetPixelDenity() const override;`
- L392 _public prototype_ `virtual void SetPixelDensity(const float NewDensity) override;`
- L393 _public prototype_ `virtual FIntPoint GetIdealRenderTargetSize() const override;`
- L394 _public function_ `virtual bool GetHMDDistortionEnabled(EShadingPath ShadingPath) const override`
- L395 _public prototype_ `virtual FIntRect GetFullFlatEyeRect_RenderThread(const FRHITextureDesc& EyeTexture) const override;`
- L396 _public prototype_ `virtual bool HasHiddenAreaMesh() const override final;`
- L397 _public prototype_ `virtual bool HasVisibleAreaMesh() const override final;`
- L398 _public prototype_ `virtual void DrawHiddenAreaMesh(class FRHICommandList& RHICmdList, int32 ViewIndex) const override final;`
- L399 _public prototype_ `virtual void DrawVisibleAreaMesh(class FRHICommandList& RHICmdList, int32 ViewIndex) const override final;`
- L400 _public prototype_ `virtual void DrawHiddenAreaMesh(class FRHICommandList& RHICmdList, int32 ViewIndex, int32 InstanceCount) const override final;`
- L401 _public prototype_ `virtual void DrawVisibleAreaMesh(class FRHICommandList& RHICmdList, int32 ViewIndex, int32 InstanceCount) const override final;`
- L402 _public prototype_ `virtual void OnBeginRendering_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& ViewFamily) override;`
- L403 _public prototype_ `virtual void OnBeginRendering_GameThread(FSceneViewFamily& SceneViewFamily) override;`
- L404 _public prototype_ `virtual void OnLateUpdateApplied_RenderThread(FRDGBuilder& GraphBuilder, const FTransform& NewRelativeTransform) override;`
- L405 _public prototype_ `virtual bool OnStartGameFrame(FWorldContext& WorldContext) override;`
- L406 _public function_ `virtual EHMDWornState::Type GetHMDWornState() override`
- L407 _public prototype_ `virtual bool SetColorScaleAndBias(FLinearColor ColorScale, FLinearColor ColorBias);`
- L410 _public prototype_ `virtual bool IsStereoEnabled() const override;` — IStereoRendering interface
- L411 _public prototype_ `virtual bool EnableStereo(bool stereo = true) override;`
- L412 _public prototype_ `virtual void AdjustViewRect(int32 ViewIndex, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;`
- L413 _public prototype_ `virtual void SetFinalViewRect(FRHICommandListImmediate& RHICmdList, const int32 StereoViewIndex, const FIntRect& FinalViewRect) override;`
- L414 _public prototype_ `virtual int32 GetDesiredNumberOfViews(bool bStereoRequested) const override;`
- L415 _public prototype_ `virtual EStereoscopicPass GetViewPassForIndex(bool bStereoRequested, int32 ViewIndex) const override;`
- L416 _public prototype_ `virtual uint32 GetLODViewIndex() const override;`
- L417 _public function_ `virtual bool IsStandaloneStereoOnlyDevice() const override`
- L419 _public prototype_ `virtual FMatrix GetStereoProjectionMatrix(const int32 StereoViewIndex) const override;`
- L420 _public prototype_ `virtual void GetEyeRenderParams_RenderThread(const struct FHeadMountedDisplayPassContext& Context, FVector2D& EyeToSrcUVScaleValue, FVector2D& EyeToSrcUVOffsetValue) const override;`
- L421 _public prototype_ `virtual IStereoRenderTargetManager* GetRenderTargetManager() override;`
- L423 _public prototype_ `virtual void RenderTexture_RenderThread(class FRDGBuilder& GraphBuilder, FRDGTextureRef BackBuffer, FRDGTextureRef SrcTexture, FVector2f WindowSize) const override;`
- L426 _public prototype_ `virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;` — ISceneViewExtension interface
- L427 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L428 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L429 _public prototype_ `virtual void PostRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;` — for non-face locked compositing
- L430 _public prototype_ `virtual void PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L433 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;` — FHMDSceneViewExtension interface
- L436 _public function_ `virtual bool ShouldUseSeparateRenderTarget() const override` — IStereoRenderTargetManager
- L437 _public prototype_ `virtual void CalculateRenderTargetSize(const FViewport& Viewport, uint32& InOutSizeX, uint32& InOutSizeY) override;`
- L438 _public prototype_ `virtual bool AllocateRenderTargetTextures(FRHICommandListBase& RHICmdList, uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumLayers, ETextureCreateFlags Flags, ETextureCreateFlags TargetableTextureFlags, TArray<FTextureRHIRef>& OutTargetableTextures, TArray<FTextureRHIRef>& OutShaderResourceTextures, uint32 NumSamples = 1) override;`
- L439 _public prototype_ `virtual int32 AcquireColorTexture() override final;`
- L440 _public prototype_ `virtual int32 AcquireDepthTexture() override final;`
- L441 _public prototype_ `virtual bool AllocateDepthTexture(uint32 Index, uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, ETextureCreateFlags InTexFlags, ETextureCreateFlags TargetableTextureFlags, FTextureRHIRef& OutTargetableTexture, FTextureRHIRef& OutShaderResourceTexture, uint32 NumSamples = 1) override final;`
- L442 _public prototype_ `virtual bool GetRecommendedMotionVectorTextureSize(FIntPoint& OutTextureSize) override;`
- L443 _public prototype_ `virtual bool GetMotionVectorTexture(uint32 Index, const FIntPoint& Size, uint8 Format, uint32 NumMips, ETextureCreateFlags Flags, FTextureRHIRef& OutTexture, uint32 NumSamples = 1) override;`
- L444 _public prototype_ `virtual bool GetMotionVectorDepthTexture(uint32 Index, const FIntPoint& Size, uint8 Format, uint32 NumMips, ETextureCreateFlags Flags, FTextureRHIRef& OutTexture, uint32 NumSamples = 1) override;`
- L445 _public prototype_ `virtual bool ReconfigureForShaderPlatform(EShaderPlatform NewShaderPlatform) override;`
- L446 _public function_ `virtual EPixelFormat GetActualColorSwapchainFormat() const override`
- L449 _public prototype_ `virtual void OnBeginPlay(FWorldContext& InWorldContext) override;` — IXRTrackingSystem
- L452 _public prototype_ `virtual TArray<FTextureRHIRef, TInlineAllocator<2>> GetDebugLayerTextures_RenderThread() override;` — IStereoLayers
- L456 _public function_ `virtual FApplyHapticFeedbackAddChainStructsDelegate& GetApplyHapticFeedbackAddChainStructsDelegate() override`
- L458 _private member_ `FApplyHapticFeedbackAddChainStructsDelegate ApplyHapticFeedbackAddChainStructsDelegate;`
- L462 _public prototype_ `FOpenXRHMD(const FAutoRegister&, XrInstance InInstance, TRefCountPtr<FOpenXRRenderBridge>& InRenderBridge, TArray<const char*> InEnabledExtensions, TArray<class IOpenXRExtensionPlugin*> InExtensionPlugins, IARSystemSupport* ARSystemSupport, EOpenXRAPIVersion InOpenXRAPIVersion);` — Constructor
- L466 _public prototype_ `virtual ~FOpenXRHMD();` — Destructor
- L468 _public prototype_ `void OnBeginSimulation_GameThread();`
- L469 _public prototype_ `void OnBeginRendering_RHIThread(IRHICommandContext& RHICmdContext, const FPipelinedFrameState& InFrameState, FXRSwapChainPtr ColorSwapchain, FXRSwapChainPtr DepthSwapchain, FXRSwapChainPtr MotionVectorSwapchain, FXRSwapChainPtr MotionVectorDepthSwapchain, FXRSwapChainPtr EmulationSwapchain);`
- L470 _public prototype_ `void OnFinishRendering(IRHICommandContext* RHICmdContext);`
- L471 _public prototype_ `void OnBackBufferReadyToPresent(class SWindow& Window, ISlateViewportProvider& ViewportProvider);`
- L474 _public function_ `void SetInputModule(IOpenXRInputModule* InInputModule) override` — IOpenXRHMD
- L479 _public prototype_ `bool IsInitialized() const override;` — @return	True if the HMD was initialized OK
- L480 _public prototype_ `bool IsRunning() const override;`
- L481 _public prototype_ `bool IsFocused() const override;`
- L482 _public prototype_ `int32 AddTrackedDevice(XrAction Action, XrPath Path) override;`
- L483 _public prototype_ `int32 AddTrackedDevice(XrAction Action, XrPath Path, XrPath SubActionPath) override;`
- L484 _public prototype_ `void ResetTrackedDevices() override;`
- L485 _public prototype_ `XrPath GetTrackedDevicePath(const int32 DeviceId) override;`
- L486 _public prototype_ `XrSpace GetTrackedDeviceSpace(const int32 DeviceId) override;`
- L487 _public function_ `bool IsExtensionEnabled(const FString& Name) const override`
- L488 _public function_ `bool IsOpenXRAPIVersionMet(EOpenXRAPIVersion RequiredVersion) const override`
- L490 _public function_ `XrInstance GetInstance() override`
- L491 _public function_ `XrSystemId GetSystem() override`
- L492 _public function_ `XrSession GetSession() override`
- L493 _public prototype_ `XrTime GetDisplayTime() const override;`
- L494 _public prototype_ `XrSpace GetTrackingSpace() const override;`
- L495 _public function_ `IOpenXRExtensionPluginDelegates& GetIOpenXRExtensionPluginDelegates() override`
- L496 _public function_ `TArray<IOpenXRExtensionPlugin*>& GetExtensionPlugins() override`
- L498 _public prototype_ `void SetEnvironmentBlendMode(XrEnvironmentBlendMode NewBlendMode) override;`
- L499 _public function_ `XrEnvironmentBlendMode GetEnvironmentBlendMode() override`
- L500 _public prototype_ `TArray<XrEnvironmentBlendMode> GetSupportedEnvironmentBlendModes() const override;`
- L503 _public prototype_ `void GetFullFOVInformation(TArray<XrFovf>& FovInfos) const override;` — Provides the full asymmetric FOV information for the view, which allows proper centering of screen-based techniques based on forward eye gaze
- L505 _public prototype_ `virtual bool AllocateSwapchainTextures_RenderThread(const FOpenXRSwapchainProperties& InSwapchainProperies, FXRSwapChainPtr& InOutSwapchain, uint8& OutActualFormat) override;`
- L508 _public function_ `EShaderPlatform GetConfiguredShaderPlatform() const` — Returns shader platform the plugin is currently configured for, in the editor it can change due to preview platforms.
- L509 _public prototype_ `FOpenXRSwapchain* GetColorSwapchain_RenderThread();`
- L511 _public function_ `bool RuntimeRequiresRHIContext() const`
- L514 _private prototype_ `FDefaultStereoLayers_LayerRenderParams CalculateEmulatedLayerRenderParams(const FSceneView& InView);`
- L516 _private prototype_ `class FEmulatedLayersPass* SetupEmulatedLayersRenderPass( FRDGBuilder& GraphBuilder, const FSceneView& InView, TArray<FDefaultStereoLayers::FStereoLayerToRender>& Layers, FRDGTextureRef RenderTarget, FDefaultStereoLayers_LayerRenderParams& OutRenderParams);`
- L523 _private prototype_ `[[nodiscard]] FEmulatedLayersPass* SetupEmulatedLayerRenderPass( FRDGBuilder& GraphBuilder, const FSceneView& InView, const FDefaultStereoLayers::FStereoLayerToRender& Layer, FRDGTextureRef RenderTarget, FRDGTextureRef DepthTarget, FDefaultStereoLayers_LayerRenderParams& OutRenderParams);`
- L531 _private prototype_ `bool IsEmulatingStereoLayers();`
- L532 _private prototype_ `void CopySwapchainTexture_RenderThread(FRDGBuilder& GraphBuilder, FRDGTextureRef SrcTexture, FIntRect SrcRect, const FXRSwapChainPtr& DstSwapChain, FIntRect DstRect, bool bClearBlack, EXRCopyTextureBlendModifier SrcTextureCopyModifier, FStaticFeatureLevel FeatureLevel, FStaticShaderPlatform ShaderPlatform) const;`
- L535 _private prototype_ `void UpdateLayerSwapchainTexture(FOpenXRLayer& Layer, FRDGBuilder& GraphBuilder);`
- L536 _private prototype_ `void ConfigureLayerSwapchains(const struct FLayerToUpdateSwapchain& Update, FOpenXRLayer& Layer);`
- L539 _private prototype_ `static XrPath GetUserPathForControllerHand(EControllerHand Hand);` — Gets the user path corresponding to the input EControllerHand value
- L541 _private member_ `bool bStereoEnabled;`
- L542 _private member_ `TAtomic<bool> bIsRunning;`
- L543 _private member_ `TAtomic<bool> bIsReady;`
- L544 _private member_ `TAtomic<bool> bIsRendering;`
- L545 _private member_ `TAtomic<bool> bIsSynchronized;`
- L546 _private member_ `bool bShouldWait;`
- L547 _private member_ `bool bIsExitingSessionByxrRequestExitSession;`
- L548 _private member_ `bool bDepthExtensionSupported;`
- L549 _private member_ `bool bHiddenAreaMaskSupported;`
- L550 _private member_ `bool bViewConfigurationFovSupported;`
- L551 _private member_ `bool bNeedReBuildOcclusionMesh;`
- L552 _private member_ `bool bIsMobileMultiViewEnabled;`
- L553 _private member_ `bool bSupportsHandTracking;`
- L554 _private member_ `bool bSpaceAccelerationSupported;`
- L555 _private member_ `bool bProjectionLayerAlphaEnabled;`
- L556 _private member_ `bool bIsStandaloneStereoOnlyDevice;`
- L557 _private member_ `bool bRuntimeRequiresRHIContext;`
- L558 _private member_ `bool bIsTrackingOnlySession;`
- L559 _private member_ `bool bIsAcquireOnAnyThreadSupported;`
- L560 _private member_ `bool bUseWaitCountToAvoidExtraXrBeginFrameCalls;`
- L561 _private member_ `bool bEquirectLayersSupported;`
- L562 _private member_ `bool bCylinderLayersSupported;`
- L563 _private member_ `bool bCubemapLayersSupported;`
- L564 _private member_ `float WorldToMetersScale = 100.0f;`
- L565 _private member_ `float RuntimePixelDensityMax = FHeadMountedDisplayBase::PixelDensityMax;`
- L566 _private member_ `EShaderPlatform ConfiguredShaderPlatform = EShaderPlatform::SP_NumPlatforms;`
- L568 _private member_ `XrSessionState CurrentSessionState;`
- L569 _private member_ `FRWLock SessionHandleMutex;`
- L571 _private member_ `TArray<const char*> EnabledExtensions;`
- L572 _private member_ `IOpenXRInputModule* InputModule;`
- L573 _private member_ `TArray<class IOpenXRExtensionPlugin*> ExtensionPlugins;`
- L574 _private member_ `XrInstance Instance;`
- L575 _private member_ `EOpenXRAPIVersion OpenXRAPIVersion;`
- L576 _private member_ `XrSystemId System;`
- L577 _private member_ `XrSession Session;`
- L578 _private member_ `XrSpace LocalSpace;`
- L579 _private member_ `XrSpace LocalFloorSpace;`
- L580 _private member_ `XrSpace StageSpace;`
- L581 _private member_ `XrSpace CustomSpace;`
- L582 _private member_ `XrReferenceSpaceType TrackingSpaceType;`
- L583 _private member_ `XrViewConfigurationType SelectedViewConfigurationType;`
- L584 _private member_ `XrEnvironmentBlendMode SelectedEnvironmentBlendMode;`
- L585 _private member_ `XrInstanceProperties InstanceProperties;`
- L586 _private member_ `XrSystemProperties SystemProperties;`
- L588 _private member_ `FPipelinedFrameState PipelinedFrameStateGame;`
- L589 _private member_ `FPipelinedFrameState PipelinedFrameStateRendering;`
- L590 _private member_ `FPipelinedFrameState PipelinedFrameStateRHI;`
- L593 _private member_ `FRWLock PipelinedFrameStateGameAccessGuard;` — Arbitrates access to PipelinedFrameStateGame from code on task threads
- L595 _private member_ `FRWLock PipelinedFrameStateRenderingAccessGuard;` — Arbitrates access to PipelinedFrameStateRendering from code on task threads
- L598 _private member_ `FPipelinedLayerState PipelinedLayerStateRendering;`
- L599 _private member_ `FPipelinedLayerState PipelinedLayerStateRHI;`
- L601 _private member_ `mutable FRWLock DeviceMutex;`
- L602 _private member_ `TArray<FDeviceSpace> DeviceSpaces;`
- L604 _private member_ `TRefCountPtr<FOpenXRRenderBridge> RenderBridge;`
- L605 _private member_ `IRendererModule* RendererModule;`
- L607 _private member_ `uint8 LastRequestedColorSwapchainFormat;`
- L608 _private member_ `uint8 LastActualColorSwapchainFormat;`
- L609 _private member_ `uint8 LastRequestedDepthSwapchainFormat;`
- L611 _private member_ `TArray<FHMDViewMesh> HiddenAreaMeshes;`
- L612 _private member_ `TArray<FHMDViewMesh> VisibleAreaMeshes;`
- L614 _private member_ `bool bTrackingSpaceInvalid;`
- L615 _private member_ `bool bUseCustomReferenceSpace;`
- L616 _private member_ `FQuat BaseOrientation;`
- L617 _private member_ `FVector BasePosition;`
- L619 _private member_ `bool bLayerSupportOpenXRCompliant;`
- L620 _private member_ `bool bOpenXRForceStereoLayersEmulationCVarCachedValue;`
- L621 _private member_ `TArray<uint32> VisibleLayerIds;`
- L622 _private member_ `TArray<FDefaultStereoLayers::FStereoLayerToRender> BackgroundCompositedEmulatedLayers;`
- L623 _private member_ `TArray<FDefaultStereoLayers::FStereoLayerToRender> EmulatedFaceLockedLayers;`
- L624 _private member_ `TArray<FDefaultStereoLayers::FStereoLayerToRender> EmulatedLayers;`
- L625 _private member_ `TArray<FOpenXRLayer> NativeLayers;`
- L627 _private member_ `TUniquePtr<FFBFoveationImageGenerator> FBFoveationImageGenerator;`
- L628 _private member_ `bool bFoveationExtensionSupported;`
- L629 _private member_ `bool bRuntimeFoveationSupported;`
- L630 _private member_ `bool bLocalFloorSpaceSupported;`
- L631 _private member_ `bool bUserPresenceSupported;`
- L633 _private member_ `XrColor4f LayerColorScale;`
- L634 _private member_ `XrColor4f LayerColorBias;`
- L635 _private member_ `bool bCompositionLayerColorScaleBiasSupported;`
- L636 _private member_ `bool bxrGetSystemPropertiesSuccessful;`
- L638 _private member_ `FTransform FrameSynthesisLastTrackingToWorld;`
- L639 _private member_ `FIntPoint RecommendedMotionVectorTextureSize;`

#### class `FOpenXRHMD::FDeviceSpace`  
`class FDeviceSpace`  
_L52-66_
- L55 _public prototype_ `FDeviceSpace(XrAction InAction, XrPath InPath);`
- L56 _public prototype_ `FDeviceSpace(XrAction InAction, XrPath InPath, XrPath InSubactionPath);`
- L57 _public prototype_ `~FDeviceSpace();`
- L59 _public prototype_ `bool CreateSpace(XrSession InSession);`
- L60 _public prototype_ `void DestroySpace();`
- L62 _public member_ `XrAction Action;`
- L63 _public member_ `XrSpace Space;`
- L64 _public member_ `XrPath Path;`
- L65 _public member_ `XrPath SubactionPath;`

#### class `FOpenXRHMD::FTrackingSpace`  
`class FTrackingSpace`  
_L68-81_
- L71 _public prototype_ `FTrackingSpace(XrReferenceSpaceType InType);`
- L72 _public prototype_ `FTrackingSpace(XrReferenceSpaceType InType, XrPosef InBasePose);`
- L73 _public prototype_ `~FTrackingSpace();`
- L75 _public prototype_ `bool CreateSpace(XrSession InSession);`
- L76 _public prototype_ `void DestroySpace();`
- L78 _public member_ `XrReferenceSpaceType Type;`
- L79 _public member_ `XrSpace Handle;`
- L80 _public member_ `XrPosef BasePose;`

#### struct `FOpenXRHMD::FPipelinedFrameState`  
`struct FPipelinedFrameState`  
_L85-99_
- desc: The game and render threads each have a separate copy of these structures so that they don't stomp on each other or cause tearing when the game thread progresses to the next frame while the render thread is still working on the previous frame.
- L87 _public member_ `XrFrameState FrameState{XR_TYPE_FRAME_STATE};`
- L88 _public member_ `XrViewState ViewState{XR_TYPE_VIEW_STATE};`
- L89 _public member_ `TArray<XrView> Views;`
- L90 _public member_ `TArray<XrViewConfigurationView> ViewConfigs;`
- L91 _public member_ `TArray<XrSpaceLocation> DeviceLocations;`
- L92 _public member_ `TSharedPtr<FTrackingSpace> TrackingSpace;`
- L93 _public member_ `float WorldToMetersScale = 100.0f;`
- L94 _public member_ `float PixelDensity = 1.0f;`
- L95 _public member_ `int WaitCount = 0;`
- L96 _public member_ `int BeginCount = 0;`
- L97 _public member_ `int EndCount = 0;`
- L98 _public member_ `bool bXrFrameStateUpdated = false;`

#### struct `FOpenXRHMD::FPipelinedFrameStateAccessorReadOnly`  
`struct FPipelinedFrameStateAccessorReadOnly`  
_L101-127_
- L103 _public function_ `FPipelinedFrameStateAccessorReadOnly(FPipelinedFrameState const& InPipelinedFrameState, FRWLock const& InAccessGuard) : PipelinedFrameState(InPipelinedFrameState), AccessGuard(const_cast<FRWLock&>(InAccessGuard))`
- L110 _public function_ `~FPipelinedFrameStateAccessorReadOnly()` — not virtual because we aren't going to delete via a base pointer
- L115 _public function_ `FPipelinedFrameState const& GetFrameState() const`
- L123 _private member_ `FPipelinedFrameState const& PipelinedFrameState;` — The frame state we're guarding the access to.
- L126 _private member_ `FRWLock& AccessGuard;` — Reference to the guarding lock.

#### struct `FOpenXRHMD::FPipelinedFrameStateAccessorReadWrite`  
`struct FPipelinedFrameStateAccessorReadWrite`  
_L129-155_
- L131 _public function_ `FPipelinedFrameStateAccessorReadWrite(FPipelinedFrameState& InPipelinedFrameState, FRWLock& InAccessGuard) : PipelinedFrameState(InPipelinedFrameState), AccessGuard(InAccessGuard)`
- L138 _public function_ `~FPipelinedFrameStateAccessorReadWrite()` — not virtual because we aren't going to delete via a base pointer
- L143 _public function_ `FPipelinedFrameState& GetFrameState()`
- L151 _private member_ `FPipelinedFrameState& PipelinedFrameState;` — The frame state we're guarding the access to.
- L154 _private member_ `FRWLock& AccessGuard;` — Reference to the guarding lock.

#### struct `FOpenXRHMD::FEmulatedLayerState`  
`struct FEmulatedLayerState`  
_L157-165_
- L161 _public member_ `TArray<XrCompositionLayerProjectionView> CompositedProjectionLayers;` — These layers are used as a target to composite all the emulated face locked layers into and be sent to the compositor with VIEW tracking space to avoid reprojection.
- L162 _public member_ `TArray<XrSwapchainSubImage> EmulationImages;`
- L164 _public member_ `FXRSwapChainPtr EmulationSwapchain;` — This swapchain is where the emulated face locked layers are rendered into.

#### struct `FOpenXRHMD::FBasePassLayerBlendParameters`  
`struct FBasePassLayerBlendParameters`  
_L167-184_
- L172 _public function_ `FBasePassLayerBlendParameters()` — Default constructor inverts the alpha for color blending to make up for the fact that UE uses alpha = 0 for opaque and alpha = 1 for transparent while OpenXR does the opposite. Alpha blending passes through the destination alpha instead.
- L180 _public member_ `XrBlendFactorFB srcFactorColor;`
- L181 _public member_ `XrBlendFactorFB dstFactorColor;`
- L182 _public member_ `XrBlendFactorFB srcFactorAlpha;`
- L183 _public member_ `XrBlendFactorFB dstFactorAlpha;`

#### struct `FOpenXRHMD::FLayerColorScaleAndBias`  
`struct FLayerColorScaleAndBias`  
_L186-192_
- L190 _public member_ `XrColor4f ColorScale;` — Used by XR_KHR_composition_layer_color_scale_bias to apply a color multiplier and offset to the background layer and set via UHeadMountedDisplayFunctionLibrary::SetHMDColorScaleAndBias() --> OpenXRHMD::SetColorScaleAndBias()
- L191 _public member_ `XrColor4f ColorBias;`

#### enum `FOpenXRHMD::EOpenXRLayerStateFlags`  
`enum class EOpenXRLayerStateFlags : uint32`  
_L194-202_
- L196 _public enumerator_ `None = 0u`
- L197 _public enumerator_ `BackgroundLayerVisible = (1u << 0)`
- L198 _public enumerator_ `SubmitBackgroundLayer = (1u << 1)`
- L199 _public enumerator_ `SubmitDepthLayer = (1u << 2)`
- L200 _public enumerator_ `SubmitEmulatedFaceLockedLayer = (1u << 3)`
- L201 _public enumerator_ `SubmitMotionVectorLayer = (1u << 4)`

#### struct `FOpenXRHMD::FPipelinedLayerState`  
`struct FPipelinedLayerState`  
_L205-233_
- L207 _public member_ `TArray<FXrCompositionLayerUnion> NativeOverlays;`
- L208 _public member_ `TArray<FXrCompositionLayerUnion> NativeUnderlays;` — Underlays will be rendered below the projection layers
- L209 _public member_ `TArray<XrCompositionLayerProjectionView> ProjectionLayers;`
- L210 _public member_ `TArray<XrCompositionLayerDepthInfoKHR> DepthLayers;`
- L211 _public member_ `TArray<XrCompositionLayerDepthTestFB> CompositionDepthTestLayers;`
- L213 _public member_ `TArray<XrFrameSynthesisInfoEXT> FrameSynthesisLayers;`
- L214 _public member_ `TArray<XrCompositionLayerSpaceWarpInfoFB> SpaceWarpLayers;`
- L216 _public member_ `TArray<XrSwapchainSubImage> ColorImages;`
- L217 _public member_ `TArray<XrSwapchainSubImage> DepthImages;`
- L219 _public member_ `TArray<XrSwapchainSubImage> MotionVectorImages;`
- L220 _public member_ `TArray<XrSwapchainSubImage> MotionVectorDepthImages;`
- L222 _public member_ `FXRSwapChainPtr ColorSwapchain;`
- L223 _public member_ `FXRSwapChainPtr DepthSwapchain;`
- L224 _public member_ `FXRSwapChainPtr MotionVectorSwapchain;`
- L225 _public member_ `FXRSwapChainPtr MotionVectorDepthSwapchain;`
- L226 _public member_ `TArray<FXRSwapChainPtr> NativeLayerSwapchains;` — This is currently only used as a reference to keep the swapchains from being destroyed
- L228 _public member_ `FEmulatedLayerState EmulatedLayerState;`
- L230 _public member_ `EOpenXRLayerStateFlags LayerStateFlags = EOpenXRLayerStateFlags::None;`
- L231 _public member_ `FBasePassLayerBlendParameters BasePassLayerBlendParams;`
- L232 _public member_ `FLayerColorScaleAndBias LayerColorScaleAndBias;`

#### class `FOpenXRHMD::FVulkanExtensions`  
`class FVulkanExtensions : public IHeadMountedDisplayVulkanExtensions`  
_L235-251_
- inherits: `IHeadMountedDisplayVulkanExtensions`
- L238 _public function_ `FVulkanExtensions(XrInstance InInstance, XrSystemId InSystem) : Instance(InInstance), System(InSystem)`
- L239 _public function_ `virtual ~FVulkanExtensions()`
- L242 _public prototype_ `virtual bool GetVulkanInstanceExtensionsRequired(TArray<const ANSICHAR*>& Out) override;` — IHeadMountedDisplayVulkanExtensions
- L243 _public prototype_ `virtual bool GetVulkanDeviceExtensionsRequired(VkPhysicalDevice_T *pPhysicalDevice, TArray<const ANSICHAR*>& Out) override;`
- L246 _private member_ `XrInstance Instance;`
- L247 _private member_ `XrSystemId System;`
- L249 _private member_ `TArray<char> Extensions;`
- L250 _private member_ `TArray<char> DeviceExtensions;`

#### Free symbols / members of external scopes

- L642 _prototype_ `ENUM_CLASS_FLAGS(FOpenXRHMD::EOpenXRLayerStateFlags);`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Private/OpenXRHMDModule.h` (Private)


#### class `FOpenXRHMDModule`  
`class FOpenXRHMDModule : public IOpenXRHMDModule`  
_L13-84_
- inherits: `IOpenXRHMDModule`
- L16 _public prototype_ `FOpenXRHMDModule();`
- L17 _public prototype_ `~FOpenXRHMDModule();`
- L20 _public prototype_ `virtual TSharedPtr< class IXRTrackingSystem, ESPMode::ThreadSafe > CreateTrackingSystem() override;` — IHeadMountedDisplayModule implementation
- L21 _public prototype_ `virtual TSharedPtr< class IHeadMountedDisplayVulkanExtensions, ESPMode::ThreadSafe > GetVulkanExtensions() override;`
- L22 _public prototype_ `virtual uint64 GetGraphicsAdapterLuid() override;`
- L23 _public prototype_ `virtual FString GetAudioInputDevice() override;`
- L24 _public prototype_ `virtual FString GetAudioOutputDevice() override;`
- L26 _public function_ `FString GetModuleKeyName() const override`
- L31 _public function_ `void GetModuleAliases(TArray<FString>& AliasesOut) const override`
- L36 _public prototype_ `virtual bool PreInit() override;`
- L37 _public prototype_ `virtual void StartupModule() override;`
- L38 _public prototype_ `virtual void ShutdownModule() override;`
- L40 _public function_ `virtual bool IsHMDConnected() override`
- L41 _public prototype_ `virtual FString GetDeviceSystemName() override;`
- L42 _public prototype_ `virtual bool IsStandaloneStereoOnlyDevice() override;`
- L45 _public function_ `virtual bool IsExtensionAvailable(const FString& Name) const override` — IOpenXRHMDModule implementation
- L46 _public function_ `virtual bool IsExtensionEnabled(const FString& Name) const override`
- L47 _public function_ `virtual bool IsLayerAvailable(const FString& Name) const override`
- L48 _public function_ `virtual bool IsLayerEnabled(const FString& Name) const override`
- L49 _public function_ `virtual XrInstance GetInstance() const override`
- L50 _public prototype_ `virtual XrSystemId GetSystemId() const override;`
- L52 _public prototype_ `virtual FName ResolvePathToName(XrPath Path) override;`
- L53 _public prototype_ `virtual XrPath ResolveNameToPath(FName Name) override;`
- L56 _private member_ `void* LoaderHandle;`
- L57 _private member_ `XrInstance Instance;`
- L58 _private member_ `EOpenXRAPIVersion InstanceOpenXRAPIVersion;`
- L59 _private member_ `TSet<FString> AvailableExtensions;`
- L60 _private member_ `TSet<FString> AvailableLayers;`
- L61 _private member_ `TArray<const char*> EnabledExtensions;`
- L62 _private member_ `TArray<const char*> EnabledLayers;`
- L63 _private member_ `TArray<class IOpenXRExtensionPlugin*> ExtensionPlugins;`
- L64 _private member_ `TRefCountPtr<class FOpenXRRenderBridge> RenderBridge;`
- L65 _private member_ `TSharedPtr< IHeadMountedDisplayVulkanExtensions, ESPMode::ThreadSafe > VulkanExtensions;`
- L68 _private member_ `FRWLock NameMutex;` — We cache all attempts to convert between XrPath and FName to avoid costly resolves
- L69 _private member_ `TSortedMap<XrPath, FName> PathToName;`
- L70 _private member_ `TSortedMap<FName, XrPath, FDefaultAllocator, FNameFastLess> NameToPath;`
- L73 _private member_ `FString OculusAudioInputDevice;` — Cache off Oculus Audio devices on PreInit so that the XrInstance can be released before Initialize
- L74 _private member_ `FString OculusAudioOutputDevice;`
- L76 _private prototype_ `bool EnumerateExtensions();`
- L77 _private prototype_ `bool EnumerateLayers();`
- L78 _private prototype_ `bool InitRenderBridge();`
- L79 _private prototype_ `bool InitInstance();`
- L80 _private prototype_ `bool TryCreateInstance(XrInstanceCreateInfo& Info);`
- L81 _private prototype_ `PFN_xrGetInstanceProcAddr GetDefaultLoader();`
- L82 _private prototype_ `bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions);`
- L83 _private prototype_ `bool GetOptionalExtensions(TArray<const ANSICHAR*>& OutExtensions);`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Private/OpenXRHMD_Layer.h` (Private)


#### struct `FOpenXRLayer`  
`struct FOpenXRLayer`  
_L12-57_
- L26 _public member_ `IStereoLayers::FLayerDesc Desc;`
- L29 _public member_ `FPerEyeTextureData RightEye;` — Texture tracking data for the right eye.
- L32 _public member_ `FPerEyeTextureData LeftEye;` — Texture tracking data for the left eye, may not be present.
- L34 _public function_ `FOpenXRLayer(const IStereoLayers::FLayerDesc& InLayerDesc) : Desc(InLayerDesc)`
- L38 _public prototype_ `FIntRect GetRightViewportSize() const;`
- L39 _public prototype_ `FVector2D GetRightQuadSize() const;`
- L41 _public prototype_ `FIntRect GetLeftViewportSize() const;`
- L42 _public prototype_ `FVector2D GetLeftQuadSize() const;`
- L44 _public prototype_ `TArray<FXrCompositionLayerUnion> CreateOpenXRLayer(FTransform InvTrackingToWorld, float WorldToMeters, XrSpace Space, EOpenXRLayerCreationFlags CreationFlags) const;`
- L46 _public prototype_ `void ApplyCompositionDepthTestLayer(TArray<FXrCompositionLayerUnion>& Headers, EOpenXRLayerCreationFlags CreationFlags, TArray<XrCompositionLayerDepthTestFB>& InCompositionDepthTestLayers) const;`
- L48 _public prototype_ `[[nodiscard]] int32 GetNumHeaders() const;`
- L51 _private prototype_ `void CreateOpenXRQuadLayer(bool bIsStereo, bool bNoAlpha, FTransform PositionTransform, float WorldToMeters, XrSpace Space, TArray<FXrCompositionLayerUnion>& Headers) const;`
- L52 _private prototype_ `void CreateOpenXRCylinderLayer(bool bIsStereo, bool bNoAlpha, FTransform PositionTransform, float WorldToMeters, XrSpace Space, TArray<FXrCompositionLayerUnion>& Headers) const;`
- L53 _private prototype_ `void CreateOpenXREquirectLayer(bool bIsStereo, bool bNoAlpha, FTransform PositionTransform, float WorldToMeters, XrSpace Space, TArray<FXrCompositionLayerUnion>& Headers) const;`
- L54 _private prototype_ `void CreateOpenXREquirect2Layer(bool bIsStereo, bool bNoAlpha, FTransform PositionTransform, float WorldToMeters, XrSpace Space, TArray<FXrCompositionLayerUnion>& Headers) const;`
- L55 _private prototype_ `void SetupEquirect2(FVector2D Scale, FVector2D Bias, FVector2D Position, FVector2D Size, FTransform PositionTransform, float WorldToMeters, XrCompositionLayerEquirect2KHR& Equirect2) const;`
- L56 _private prototype_ `void CreateOpenXRCubemapLayer(bool bIsStereo, bool bNoAlpha, FTransform PositionTransform, float WorldToMeters, XrSpace Space, TArray<FXrCompositionLayerUnion>& Headers) const;`

#### struct `FOpenXRLayer::FPerEyeTextureData`  
`struct FPerEyeTextureData`  
_L14-24_
- L16 _public member_ `FTextureRHIRef Texture = nullptr;`
- L17 _public member_ `FXRSwapChainPtr Swapchain = nullptr;`
- L18 _public member_ `FVector2D SwapchainSize{};`
- L19 _public member_ `ETextureDimension SwapchainDimension = ETextureDimension::Texture2D;`
- L20 _public member_ `bool bStaticSwapchain = false;`
- L21 _public member_ `bool bUpdateTexture = false;`
- L23 _public prototype_ `void ConfigureSwapchain(XrSession Session, class FOpenXRRenderBridge* RenderBridge, FTextureRHIRef Texture, bool bStaticSwapchain);`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Public/IOpenXRARModule.h` (Public)


#### class `IOpenXRARModule`  
`class IOpenXRARModule : public IModuleInterface, public IModularFeature`  
_L10-41_
- inherits: `IModuleInterface,IModularFeature`
- L14 _public prototype_ `virtual class IARSystemSupport* CreateARSystem() = 0;` — Used to init our AR system
- L15 _public prototype_ `virtual void SetTrackingSystem(class IXRTrackingSystem& InTrackingSystem) = 0;`
- L16 _public prototype_ `virtual bool GetExtensions(TArray<const ANSICHAR*>& OutExtensions) = 0;`
- L18 _public prototype_ `virtual class IOpenXRARTrackedMeshHolder * GetTrackedMeshHolder() = 0;`
- L26 _public function_ `static inline IOpenXRARModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Public/IOpenXRExtensionPlugin.h` (Public)


#### class `IOpenXRCustomAnchorSupport`  
`class IOpenXRCustomAnchorSupport`  
_L17-62_
- L23 _public prototype_ `virtual bool OnPinComponent(class UARPin* Pin, XrSession InSession, XrSpace TrackingSpace, XrTime DisplayTime, float worldToMeterScale) = 0;` — Method to add an anchor on tracking space
- L28 _public prototype_ `virtual void OnRemovePin(class UARPin* Pin) = 0;` — Method to remove an anchor from tracking space
- L30 _public prototype_ `virtual void OnUpdatePin(class UARPin* Pin, XrSession InSession, XrSpace TrackingSpace, XrTime DisplayTime, float worldToMeterScale) = 0;`
- L36 _public function_ `virtual bool IsLocalPinSaveSupported() const`
- L41 _public function_ `virtual bool ArePinsReadyToLoad()`
- L46 _public function_ `virtual void LoadARPins(XrSession InSession, TFunction<UARPin*(FName)> OnCreatePin)`
- L50 _public function_ `virtual bool SaveARPin(XrSession InSession, FName InName, UARPin* InPin)`
- L55 _public function_ `virtual void RemoveSavedARPin(XrSession InSession, FName InName)`
- L59 _public function_ `virtual void RemoveAllSavedARPins(XrSession InSession)`

#### class `IOpenXRCustomCaptureSupport`  
`class IOpenXRCustomCaptureSupport`  
_L64-103_
- L68 _public function_ `virtual bool OnGetCameraIntrinsics(struct FARCameraIntrinsics& OutCameraIntrinsics) const`
- L74 _public function_ `virtual class UARTexture* OnGetARTexture(EARTextureType TextureType) const` — @return the AR texture for the specified type
- L79 _public function_ `virtual bool OnToggleARCapture(const bool bOnOff)`
- L84 _public function_ `virtual FTransform GetCameraTransform() const`
- L89 _public function_ `virtual FVector GetWorldSpaceRayFromCameraPoint(FVector2D pixelCoordinate) const`
- L94 _public function_ `virtual bool IsEnabled() const`
- L99 _public function_ `virtual TArray<FARTraceResult> OnLineTraceTrackedObjects(const TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> ARCompositionComponent, const FVector Start, const FVector End, const EARLineTraceChannels TraceChannels)`

#### class `IOpenXRInputModule`  
`class IOpenXRInputModule`  
_L106-113_
- desc: Note: We may refactor to put OpenXRInput into the OpenXRHMD module so we can get rid of this interface.
- L109 _public function_ `virtual ~IOpenXRInputModule()`
- L111 _public prototype_ `virtual void OnBeginSession() = 0;`
- L112 _public prototype_ `virtual void OnDestroySession() = 0;`

#### struct `FInputKeyOpenXRProperties`  
`struct FInputKeyOpenXRProperties`  
_L115-120_
- L117 _public member_ `FString InputKey;`
- L118 _public member_ `FString InteractionProfile;`
- L119 _public member_ `FString OpenXRPath;`

#### class `IOpenXRExtensionPlugin`  
`class IOpenXRExtensionPlugin : public IModularFeature`  
_L122-531_
- inherits: `IModularFeature`
- L125 _public function_ `virtual ~IOpenXRExtensionPlugin()`
- L127 _public function_ `static FName GetModularFeatureName()`
- L138 _public function_ `void RegisterOpenXRExtensionModularFeature()` — Register module as an extension on startup. It is common to do this in StartupModule of your IModuleInterface class (which may also be the class that implements this interface). The module's LoadingPhase must be PostConfigInit or earlier because OpenXRHMD will look for these after it is loaded in that phase.
- L143 _public function_ `void UnregisterOpenXRExtensionModularFeature()`
- L148 _public function_ `virtual FString GetDisplayName()`
- L156 _public function_ `virtual bool GetCustomLoader(PFN_xrGetInstanceProcAddr* OutGetProcAddr)` — Optionally use a custom loader (via GetInstanceProcAddr) for the OpenXR plugin.
- L166 _public function_ `virtual bool InsertOpenXRAPILayer(PFN_xrGetInstanceProcAddr& InOutGetProcAddr)` — Experimental: Optionally hand off the loader/plugin GetInstanceProcAddr to an extension plugin to support API layering. Returns true if plugin is wrapping API. Layers can chain by using received GetProcAddr to hand off API calls.
- L175 _public function_ `virtual bool IsStandaloneStereoOnlyDevice()` — Indicates that the device we're currently running does not support a spectator view. This will only be called once at initialization and should only return a result based for the current device the engine is running on.
- L184 _public function_ `virtual class FOpenXRRenderBridge* GetCustomRenderBridge(XrInstance InInstance)` — Optionally provide a custom render bridge for the OpenXR plugin. Note: this returns a pointer to a new instance allocated with "new".  Calling code is responsible for eventually deleting it.
- L192 _public function_ `virtual bool RequiresRHIContext() const` — If true pass the rhi context into some xr functions via XrRHIContextEpic.  Intended to be used where an unreal plugin wraps a XR platform api in the OpenXR api.
- L202 _public function_ `virtual bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions)` — Fill the array with extensions required by the plugin If false is returned the plugin and its extensions will be ignored
- L211 _public function_ `virtual bool GetOptionalExtensions(TArray<const ANSICHAR*>& OutExtensions)` — Fill the array with extensions optionally supported by the plugin If false is returned the plugin and its extensions will be ignored
- L228 _public function_ `virtual bool GetBlockedOptionalExtensions(TArray<const ANSICHAR*>& OutExtensions)` — Fill the array with optional extensions blocked by this plugin. This can be used to disable optional extension usage by the UE OpenXR core and by other ExtensionPlugins. Required extensions either from UE OpenXR core or from ExtensionPlugins are NOT blocked.  In the latter case disabling plugins may have the same effect.  Otherwise code changes will be needed. In general blocking optional extensions used by UE's OpenXR core should be ok because it is designed to run correctly without those extensions and it seems likely the blocking plugin is replacing that functionality somehow. Blocking optional extensions added by plugins is potentially more complicated and ExtensionPlugins that do this may make themselves harder to use along with other ExtensionPlugins.  They are optional, so it should work, but feature use may become complex. Plugin settings to explicitly disable extension use or splitting plugins up so that features can be individually enabled/disable should be considered. If false is returned the returned extension list will be ignored.
- L236 _public function_ `virtual bool GetInteractionProfiles(XrInstance InInstance, TArray<FString>& OutKeyPrefixes, TArray<XrPath>& OutPaths, TArray<bool>& OutHasHaptics)` — Set the output parameters to add multiple interaction profiles to OpenXR Input
- L246 _public function_ `virtual bool GetSuggestedBindings(XrPath InInteractionProfile, TArray<XrActionSuggestedBinding>& OutBindings)` — Set the output parameter to add suggested bindings to the given interaction profile. This function gets called once for each interaction profile. If false is returned the bindings will be ignored.
- L256 _public function_ `virtual bool GetInputKeyOverrides(TArray<FInputKeyOpenXRProperties>& OutOverrides)` — Set the output parameter to explicitly define an interaction profile and path for the given key. The same key can contain multiple entries if the key is relevant to multiple interaction profiles. If false is returned the overrides will be ignored.
- L270 _public function_ `virtual bool GetControllerModel(XrInstance InInstance, XrPath InInteractionProfile, XrPath InDevicePath, FSoftObjectPath& OutPath)` — Set the output parameters to provide a path to an asset in the plugin content folder that visualizes the controller in the hand represented by the user path. While it's possible to provide controller models for other interaction profiles, you should only provide controller models for the interaction profile provided by the plugin. NOTE: All models that can be returned also need to be returned in GetControllerModels() so they're included when cooking a project. If this is skipped the controllers won't show up in packaged projects
- L278 _public function_ `virtual void GetControllerModelsForCooking(TArray<FSoftObjectPath>& OutPaths)` — Add all asset paths that need to be packaged for cooking.
- L287 _public function_ `virtual bool GetSpectatorScreenController(FHeadMountedDisplayBase* InHMDBase, TUniquePtr<FDefaultSpectatorScreenController>& OutSpectatorScreenController)` — Set a spectator screen controller specific to the platform If true is returned and OutSpectatorScreenController is nullptr, spectator screen will be disabled If false is returned a default spectator screen controller will be created
- L296 _public function_ `virtual void AttachActionSets(TSet<XrActionSet>& OutActionSets)` — Add any action sets provided by the plugin to be attached as active to the session This allows a plugin to manage a custom actionset that will be active in xrSyncActions
- L303 _public function_ `virtual void GetActiveActionSetsForSync(TArray<XrActiveActionSet>& OutActiveSets)` — Specify action sets to be included in XrActionsSyncInfo::activeActionSets.
- L310 _public function_ `virtual void OnEvent(XrSession InSession, const XrEventDataBaseHeader* InHeader)` — Use this callback to handle events that the OpenXR plugin doesn't handle itself
- L315 _public function_ `virtual IOpenXRCustomAnchorSupport* GetCustomAnchorSupport()` — Get custom anchor interface if provided by this extension.
- L318 _public function_ `virtual IOpenXRCustomCaptureSupport* GetCustomCaptureSupport(const EARCaptureType CaptureType)` — Get custom capture interface if provided by this extension.
- L320 _public function_ `virtual void* OnEnumerateViewConfigurationViews(XrInstance InInstance, XrSystemId InSystem, XrViewConfigurationType InViewConfigurationType, uint32_t InViewIndex, void* InNext)`
- L325 _public function_ `virtual const void* OnLocateViews(XrSession InSession, XrTime InDisplayTime, const void* InNext)`
- L335 _public function_ `virtual const void* OnCreateInstance(class IOpenXRHMDModule* InModule, const void* InNext)`
- L340 _public function_ `virtual void PostCreateInstance(XrInstance InInstance)`
- L344 _public function_ `virtual void BindExtensionPluginDelegates(class IOpenXRExtensionPluginDelegates& OpenXRHMD)`
- L348 _public function_ `virtual const void* OnGetSystem(XrInstance InInstance, const void* InNext)`
- L353 _public function_ `virtual void PostGetSystem(XrInstance InInstance, XrSystemId InSystem)`
- L357 _public function_ `virtual const void* OnCreateSession(XrInstance InInstance, XrSystemId InSystem, const void* InNext)`
- L362 _public function_ `virtual void PostCreateSession(XrSession InSession)`
- L366 _public function_ `virtual const void* OnBeginSession(XrSession InSession, const void* InNext)`
- L371 _public function_ `virtual void OnDestroySession(XrSession InSession)`
- L376 _public function_ `virtual void* OnWaitFrame(XrSession InSession, void* InNext)` — OpenXRHMD::OnBeginSimulation_GameThread
- L381 _public function_ `virtual void OnBeginRendering_GameThread(XrSession InSession, FSceneViewFamily& InViewFamily, TArrayView<const uint32> VisibleLayers)`
- L385 _public function_ `virtual void OnBeginRendering_RenderThread_PreDeviceLocationUpdate(XrSession InSession, FRDGBuilder& GraphBuilder)`
- L389 _public function_ `virtual void OnBeginRendering_RenderThread(XrSession InSession, FRDGBuilder& GraphBuilder)`
- L393 _public function_ `virtual void PostBeginFrame_RHIThread(XrTime PredictedDisplayTime)`
- L401 _public function_ `virtual const uint8 GetPreferredSwapchainFormat(uint8 RequestedFormat)` — Called during AllocateRenderTargetTextures (render thread) to allow the plugin to override the color swapchain pixel format. Return PF_Unknown (0) to indicate no preference and use the engine's default format selection.
- L407 _public function_ `virtual const void* OnBeginFrame_RHIThread(XrSession InSession, XrTime DisplayTime, const void* InNext)` — OpenXRHMD::OnBeginRendering_RHIThread
- L412 _public function_ `virtual const void* OnBeginProjectionView(XrSession InSession, int32 InLayerIndex, int32 InViewIndex, const void* InNext)`
- L417 _public function_ `virtual const void* OnBeginDepthInfo(XrSession InSession, int32 InLayerIndex, int32 InViewIndex, const void* InNext)`
- L423 _public function_ `virtual void OnCreateLayer(uint32 LayerId)` — FOpenXRHMD::CreateLayer
- L428 _public function_ `virtual void OnDestroyLayer(uint32 LayerId)` — FOpenXRHMD::DestroyLayer
- L433 _public function_ `virtual void OnSetLayerDesc(uint32 LayerId)` — FOpenXRHMD::SetLayerDesc
- L437 _public function_ `virtual void UpdateCompositionLayers_RHIThread(XrSession InSession, TArray<XrCompositionLayerBaseHeader*>& Headers)`
- L442 _public function_ `virtual const void* OnEndProjectionLayer_RHIThread(XrSession InSession, int32 InLayerIndex, const void* InNext, XrCompositionLayerFlags& OutFlags)` — FOpenXRHMD::OnFinishRendering_RHIThread
- L448 _public function_ `virtual const void* OnSuggestBindings(XrPath InteractionProfile, const void* InNext)` — FOpenXRInputPlugin::FOpenXRInput::BuildActions
- L454 _public function_ `virtual const void* OnEndFrame(XrSession InSession, XrTime DisplayTime, const void* InNext)` — FOpenXRRenderBridge::Present, RHI thread
- L460 _public function_ `virtual const void* OnCreateActionSet(XrActionSetCreateInfo InCreateInfo, const void* InNext)` — FOpenXRInputPlugin::FOpenXRActionSet::FOpenXRActionSet
- L466 _public function_ `void PostCreateActionSet(XrActionSet InActionSet)` — FOpenXRInputPlugin::FOpenXRActionSet::FOpenXRActionSet
- L471 _public function_ `virtual const void* OnCreateAction(XrActionCreateInfo InCreateInfo, const void* InNext)` — FOpenXRInputPlugin::FOpenXRAction::FOpenXRAction
- L477 _public function_ `void PostCreateAction(XrAction InAction)` — FOpenXRInputPlugin::FOpenXRAction::FOpenXRAction
- L482 _public function_ `virtual const void* OnActionSetAttach(XrSessionActionSetsAttachInfo InAttachInfo, const void* InNext)` — FOpenXRInputPlugin::FOpenXRInput::BuildActions
- L488 _public function_ `virtual const void* OnSyncActions(XrSession InSession, const void* InNext)` — FOpenXRInput::Tick, game thread, setting up for xrSyncActions.  This happens near the start of the game frame.
- L494 _public function_ `virtual void UpdateDeviceLocations(XrSession InSession, XrTime DisplayTime, XrSpace TrackingSpace)` — OpenXRHMD::OnStartGameFrame
- L499 _public function_ `virtual void PostSyncActions(XrSession InSession)` — FOpenXRInput::Tick, game thread, after xrSyncActions
- L504 _public function_ `virtual void OnSetDeviceProperty(XrSession InSession, int32 ControllerId, const FInputDeviceProperty* Property)`
- L509 _public function_ `virtual bool UseCustomReferenceSpaceType(XrReferenceSpaceType& OutReferenceSpaceType)` — Update OpenXRHMD to use reference space types other than view, local, and stage.
- L521 _public function_ `virtual void OnStartARSession(class UARSessionConfig* SessionConfig)` — Start the AR system. @param SessionType The type of AR session to create @return true if the system was successfully started
- L524 _public function_ `virtual void OnPauseARSession()` — Stop the AR system but leave its internal state intact.
- L527 _public function_ `virtual void OnStopARSession()` — Stop the AR system and reset its internal state; this task must succeed.
- L529 _public function_ `virtual const void* OnCreateHandTracker(const void* InNext)`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Public/IOpenXRExtensionPluginDelegates.h` (Public)


#### struct `FOpenXRExtensionChainStruct`  
`struct FOpenXRExtensionChainStruct`  
_L31-34_
- L33 _public function_ `virtual ~FOpenXRExtensionChainStruct()`

#### struct `TOpenXRExtensionChainStruct`  
`template <typename ChainStructType> struct TOpenXRExtensionChainStruct : public FOpenXRExtensionChainStruct`  
_L38-49_
- inherits: `FOpenXRExtensionChainStruct`
- L40 _public function_ `TOpenXRExtensionChainStruct(void* Head, XrStructureType XRType)`
- L47 _public function_ `virtual ~TOpenXRExtensionChainStruct()`
- L48 _public member_ `ChainStructType Data;`

#### class `IOpenXRExtensionPluginDelegates`  
`class IOpenXRExtensionPluginDelegates`  
_L54-58_
- L57 _public prototype_ `virtual FApplyHapticFeedbackAddChainStructsDelegate& GetApplyHapticFeedbackAddChainStructsDelegate() = 0;`

#### Free symbols / members of external scopes

- L35 _typedef_ `typedef TSharedPtr<FOpenXRExtensionChainStruct> FOpenXRExtensionChainStructPtr;`
- L36 _typedef_ `typedef TArray<FOpenXRExtensionChainStructPtr> FOpenXRExtensionChainStructPtrs;`
- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FApplyHapticFeedbackAddChainStructsDelegate, XrHapticVibration*, FOpenXRExtensionChainStructPtrs&, struct FHapticFeedbackBuffer*);` — Delegates
- L52 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FApplyHapticFeedbackAddChainStructsDelegate, XrHapticVibration*, FOpenXRExtensionChainStructPtrs&, struct FHapticFeedbackBuffer*);` — Delegates

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Public/IOpenXRHMD.h` (Public)


#### struct `FOpenXRSwapchainProperties`  
`struct FOpenXRSwapchainProperties`  
_L13-27_
- L15 _public member_ `const FStringView DebugName;`
- L16 _public member_ `uint8 Format;`
- L17 _public member_ `ETextureDimension Dimension;`
- L18 _public member_ `uint32 SizeX;`
- L19 _public member_ `uint32 SizeY;`
- L20 _public member_ `uint32 ArraySize;`
- L21 _public member_ `uint32 NumMips;`
- L22 _public member_ `uint32 NumSamples;`
- L24 _public member_ `ETextureCreateFlags CreateFlags;`
- L25 _public member_ `const FClearValueBinding& ClearValueBinding;`
- L26 _public member_ `ETextureCreateFlags AuxiliaryCreateFlags = ETextureCreateFlags::None;`

#### class `IOpenXRHMD`  
`class IOpenXRHMD`  
_L31-68_
- L34 _public prototype_ `virtual void SetInputModule(class IOpenXRInputModule* InInputModule) = 0;`
- L36 _public prototype_ `virtual bool IsInitialized() const = 0;`
- L37 _public prototype_ `virtual bool IsRunning() const = 0;`
- L38 _public prototype_ `virtual bool IsFocused() const = 0;`
- L40 _public prototype_ `virtual int32 AddTrackedDevice(XrAction Action, XrPath Path) = 0;`
- L41 _public prototype_ `virtual int32 AddTrackedDevice(XrAction Action, XrPath Path, XrPath SubactionPath) = 0;`
- L42 _public prototype_ `virtual void ResetTrackedDevices() = 0;`
- L43 _public prototype_ `virtual XrPath GetTrackedDevicePath(const int32 DeviceId) = 0;`
- L44 _public prototype_ `virtual XrSpace GetTrackedDeviceSpace(const int32 DeviceId) = 0;`
- L46 _public prototype_ `virtual bool IsExtensionEnabled(const FString& Name) const = 0;`
- L47 _public prototype_ `virtual bool IsOpenXRAPIVersionMet(EOpenXRAPIVersion Version) const = 0;`
- L48 _public prototype_ `virtual XrInstance GetInstance() = 0;`
- L49 _public prototype_ `virtual XrSystemId GetSystem() = 0;`
- L50 _public prototype_ `virtual XrSession GetSession() = 0;`
- L51 _public prototype_ `virtual XrTime GetDisplayTime() const = 0;`
- L52 _public prototype_ `virtual XrSpace GetTrackingSpace() const = 0;`
- L54 _public prototype_ `virtual class IOpenXRExtensionPluginDelegates& GetIOpenXRExtensionPluginDelegates() = 0;`
- L56 _public prototype_ `virtual bool GetIsTracked(int32 DeviceId) = 0;`
- L57 _public prototype_ `virtual bool GetPoseForTime(int32 DeviceId, FTimespan Timespan, bool& OutTimeWasUsed, FQuat& CurrentOrientation, FVector& CurrentPosition, bool& bProvidedLinearVelocity, FVector& LinearVelocity, bool& bProvidedAngularVelocity, FVector& AngularVelocityAsAxisAndLength, bool& bProvidedLinearAcceleration, FVector& LinearAcceleration, float WorldToMetersScale) = 0;`
- L59 _public prototype_ `virtual TArray<class IOpenXRExtensionPlugin*>& GetExtensionPlugins() = 0;`
- L61 _public prototype_ `virtual void SetEnvironmentBlendMode(XrEnvironmentBlendMode NewBlendMode) = 0;`
- L62 _public prototype_ `virtual XrEnvironmentBlendMode GetEnvironmentBlendMode() = 0;`
- L63 _public prototype_ `virtual TArray<XrEnvironmentBlendMode> GetSupportedEnvironmentBlendModes() const = 0;`
- L65 _public prototype_ `virtual void GetFullFOVInformation(TArray<XrFovf>& FovInfos) const = 0;`
- L67 _public prototype_ `virtual bool AllocateSwapchainTextures_RenderThread(const FOpenXRSwapchainProperties& InSwapchainProperies, FXRSwapChainPtr& InOutSwapchain, uint8& OutActualFormat) = 0;`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Public/IOpenXRHMDModule.h` (Public)


#### class `IOpenXRHMDModule`  
`class IOpenXRHMDModule : public IHeadMountedDisplayModule`  
_L15-52_
- inherits: `IHeadMountedDisplayModule`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L26 _public function_ `static inline IOpenXRHMDModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L41 _public prototype_ `virtual bool IsExtensionAvailable(const FString& Name) const = 0;`
- L42 _public prototype_ `virtual bool IsExtensionEnabled(const FString& Name) const = 0;`
- L44 _public prototype_ `virtual bool IsLayerAvailable(const FString& Name) const = 0;`
- L45 _public prototype_ `virtual bool IsLayerEnabled(const FString& Name) const = 0;`
- L47 _public prototype_ `virtual XrInstance GetInstance() const = 0;`
- L48 _public prototype_ `virtual XrSystemId GetSystemId() const = 0;`
- L50 _public prototype_ `virtual FName ResolvePathToName(XrPath Path) = 0;`
- L51 _public prototype_ `virtual XrPath ResolveNameToPath(FName Name) = 0;`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Public/OpenXRAssetDirectory.h` (Public)


#### class `FOpenXRAssetDirectory`  
`class FOpenXRAssetDirectory`  
_L8-39_
- L12 _public prototype_ `static void LoadForCook();`
- L13 _public prototype_ `static void ReleaseAll();`
- L16 _public member_ `static FSoftObjectPath HPMixedRealityLeft;`
- L17 _public member_ `static FSoftObjectPath HPMixedRealityRight;`
- L18 _public member_ `static FSoftObjectPath HTCVive;`
- L19 _public member_ `static FSoftObjectPath HTCViveCosmosLeft;`
- L20 _public member_ `static FSoftObjectPath HTCViveCosmosRight;`
- L21 _public member_ `static FSoftObjectPath HTCViveFocus;`
- L22 _public member_ `static FSoftObjectPath HTCViveFocusPlus;`
- L23 _public member_ `static FSoftObjectPath MicrosoftMixedRealityLeft;`
- L24 _public member_ `static FSoftObjectPath MicrosoftMixedRealityRight;`
- L25 _public member_ `static FSoftObjectPath OculusGo;`
- L26 _public member_ `static FSoftObjectPath OculusTouchLeft;`
- L27 _public member_ `static FSoftObjectPath OculusTouchRight;`
- L28 _public member_ `static FSoftObjectPath OculusTouchV2Left;`
- L29 _public member_ `static FSoftObjectPath OculusTouchV2Right;`
- L30 _public member_ `static FSoftObjectPath OculusTouchV3Left;`
- L31 _public member_ `static FSoftObjectPath OculusTouchV3Right;`
- L32 _public member_ `static FSoftObjectPath PicoNeo3Left;`
- L33 _public member_ `static FSoftObjectPath PicoNeo3Right;`
- L34 _public member_ `static FSoftObjectPath SamsungGearVR;`
- L35 _public member_ `static FSoftObjectPath SamsungOdysseyLeft;`
- L36 _public member_ `static FSoftObjectPath SamsungOdysseyRight;`
- L37 _public member_ `static FSoftObjectPath ValveIndexLeft;`
- L38 _public member_ `static FSoftObjectPath ValveIndexRight;`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Public/OpenXRBlueprintFunctionLibrary.h` (Public)


#### enum `EOpenXREnvironmentBlendMode`  
`enum class EOpenXREnvironmentBlendMode : uint8`  
_L13-19_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `None = 0`
- L16 _public enumerator_ `Opaque = XR_ENVIRONMENT_BLEND_MODE_OPAQUE`
- L17 _public enumerator_ `Additive = XR_ENVIRONMENT_BLEND_MODE_ADDITIVE`
- L18 _public enumerator_ `AlphaBlend = XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND`

#### class `UOpenXRBlueprintFunctionLibrary`  
`class UOpenXRBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L22-55_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L32 _private prototype_ `static void SetEnvironmentBlendMode(EOpenXREnvironmentBlendMode NewBlendMode);` — `UFUNCTION(BlueprintCallable, Category="OpenXR|Passthrough")` — Sets the OpenXR environment blend mode. @param NewBlendMode		The new blend mode to be set, if supported.
- L38 _private prototype_ `static EOpenXREnvironmentBlendMode GetEnvironmentBlendMode();` — `UFUNCTION(BlueprintCallable, Category="OpenXR|Passthrough")` — Gets the OpenXR environment blend mode that is currently in use.
- L44 _private prototype_ `static TArray<EOpenXREnvironmentBlendMode> GetSupportedEnvironmentBlendModes();` — `UFUNCTION(BlueprintCallable, Category="OpenXR|Passthrough")` — Gets the OpenXR runtime's supported environment blend modes, sorted in order from highest to lowest runtime preference.
- L50 _private prototype_ `static bool IsCompositionLayerInvertedAlphaEnabled();` — `UFUNCTION(BlueprintCallable, Category="OpenXR|Passthrough")` — Returns true if OpenXR composition layer inverted alpha is enabled.
- L54 _private prototype_ `static FOpenXRHMD* GetOpenXRHMD();`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Public/OpenXRCore.h` (Public)


#### union `FXrCompositionLayerUnion`  
`union FXrCompositionLayerUnion`  
_L163-171_
- L165 _public member_ `XrCompositionLayerBaseHeader Header;`
- L166 _public member_ `XrCompositionLayerQuad Quad;`
- L167 _public member_ `XrCompositionLayerCylinderKHR Cylinder;`
- L168 _public member_ `XrCompositionLayerEquirectKHR Equirect;`
- L169 _public member_ `XrCompositionLayerEquirect2KHR Equirect2;`
- L170 _public member_ `XrCompositionLayerCubeKHR Cube;`

#### enum `EOpenXRLayerCreationFlags`  
`enum class EOpenXRLayerCreationFlags : uint32`  
_L173-178_
- L175 _public enumerator_ `None = 0u`
- L176 _public enumerator_ `EquirectLayer2Supported = (1u << 0)`
- L177 _public enumerator_ `DepthTestSupported = (1u << 1)`

#### enum `EOpenXRAPIVersion`  
`enum class EOpenXRAPIVersion : uint32`  
_L182-187_
- L184 _public enumerator_ `V_INVALID`
- L185 _public enumerator_ `V_1_0`
- L186 _public enumerator_ `V_1_1`

#### class `FOpenXRPath`  
`class FOpenXRPath`  
_L192-243_
- desc: XrPath wrapper with convenience functions
- L195 _public prototype_ `FOpenXRPath(XrPath InPath);`
- L200 _public prototype_ `FOpenXRPath(FName InName);` — Efficiently converts an FName to an XrPath
- L205 _public prototype_ `FOpenXRPath(const char* PathString);` — Converts a string to an XrPath
- L206 _public prototype_ `FOpenXRPath(const FString& PathString);`
- L213 _public prototype_ `FString ToString() const;` — Converts an XrPath to a readable format @return String representation of the path
- L218 _public prototype_ `uint32 GetStringLength() const;` — Get the number of characters, excluding null-terminator, that ToString() would yield
- L225 _public prototype_ `FName ToName() const;` — Efficiently converts an XrPath to an FName @return FName representing the path
- L227 _public function_ `XrPath ToXRPath() const`
- L229 _public function_ `operator bool() const`
- L230 _public function_ `operator XrPath() const`
- L231 _public function_ `operator FString() const`
- L232 _public function_ `operator FName() const`
- L237 _public function_ `FOpenXRPath operator/(const char* Suffix) const` — Operators to append another path ensuring the / character is used between them
- L238 _public function_ `FOpenXRPath operator/(FString Suffix) const`
- L239 _public function_ `FOpenXRPath operator/(FOpenXRPath Suffix) const`
- L242 _private member_ `XrPath Path;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define XR_ENUM_CASE_STR(name, val) case name: return TEXT(#name);`
- L11 _function_ `constexpr const TCHAR* OpenXRResultToString(XrResult e)`
- L20 _macro_ `#define XR_SESSION_STATE_STR(name, val) case name: return TEXT(#name);`
- L21 _function_ `constexpr const TCHAR* OpenXRSessionStateToString(XrSessionState e)`
- L30 _macro_ `#define XR_REFERENCE_SPACE_TYPE_STR(name, val) case name: return TEXT(#name);`
- L31 _function_ `constexpr const TCHAR* OpenXRReferenceSpaceTypeToString(XrReferenceSpaceType e)`
- L52 _macro_ `#define XR_ENSURE(xrCall) \`
- L59 _macro_ `#define XR_ENSURE(xrCall) XR_SUCCEEDED(xrCall)`
- L65 _macro_ `#define XR_ENSURE_WITH_CALLINFO(xrCall, xrCallInfoText) [] (XrResult Result) \`
- L70 _macro_ `#define XR_ENSURE_WITH_CALLINFO(xrCall, xrCallInfoText) XR_SUCCEEDED(xrCall)`
- L73 _function_ `inline FQuat ToFQuat(XrQuaternionf Quat)`
- L78 _function_ `inline XrQuaternionf ToXrQuat(FQuat Quat)`
- L83 _function_ `inline FVector ToFVector(XrVector3f Vector, float Scale = 1.0f)`
- L88 _function_ `inline FVector3f ToFVector3f(XrVector3f Vector, float Scale = 1.0f)`
- L93 _function_ `inline XrVector3f ToXrVector(FVector Vector, float Scale = 1.0f)`
- L101 _function_ `inline FTransform ToFTransform(XrPosef Transform, float Scale = 1.0f)`
- L106 _function_ `inline XrPosef ToXrPose(FTransform Transform, float Scale = 1.0f)`
- L111 _function_ `inline FTimespan ToFTimespan(XrTime Time)`
- L118 _function_ `inline XrTime ToXrTime(FTimespan Time)`
- L123 _function_ `inline FIntRect ToFIntRect(XrRect2Di Rect)`
- L128 _function_ `inline XrRect2Di ToXrRect(FIntRect Rect)`
- L133 _function_ `inline FVector2D ToFVector2D(XrVector2f Vector, float Scale = 1.0f)`
- L138 _function_ `inline XrVector2f ToXrVector2f(FVector2D Vector, float Scale = 1.0f)`
- L143 _function_ `inline FVector2D ToFVector2D(XrExtent2Df Extent, float Scale = 1.0f)`
- L148 _function_ `inline XrExtent2Df ToXrExtent2D(FVector2D Vector, float Scale = 1.0f)`
- L156 _function_ `inline uint32 ToXrPriority(int32 Priority)`
- L180 _prototype_ `ENUM_CLASS_FLAGS(EOpenXRLayerCreationFlags);`
- L246 _macro_ `#define ENUM_XR_ENTRYPOINTS_GLOBAL(EnumMacro) \` — List all OpenXR global entry points used by Unreal.
- L252 _macro_ `#define ENUM_XR_ENTRYPOINTS(EnumMacro) \` — List all OpenXR instance entry points used by Unreal.
- L306 _macro_ `#define DECLARE_XR_ENTRYPOINTS(Type,Func) extern Type OPENXRHMD_API Func;` — Declare all XR functions in a namespace to avoid conflicts with the loader exported symbols.
- L307 _namespace_ `namespace OpenXRDynamicAPI`
- L309 _prototype_ `ENUM_XR_ENTRYPOINTS_GLOBAL(DECLARE_XR_ENTRYPOINTS);` (scope `OpenXRDynamicAPI`)
- L310 _prototype_ `ENUM_XR_ENTRYPOINTS(DECLARE_XR_ENTRYPOINTS);` (scope `OpenXRDynamicAPI`)
- L319 _prototype_ `bool PreInitOpenXRCore(PFN_xrGetInstanceProcAddr InGetProcAddr);` — Initialize essential OpenXR functions. @returns true if initialization was successful.
- L325 _prototype_ `bool InitOpenXRCore(XrInstance Instance);` — Initialize core OpenXR functions. @returns true if initialization was successful.
- L327 _prototype_ `void EnumerateOpenXRApiLayers(TArray<XrApiLayerProperties>& OutProperties);`
- L329 _function_ `inline void FilterActionName(const char* InActionName, char* OutActionName)`
- L343 _namespace_ `namespace OpenXR`
- L346 _function_ `template<typename T> T* FindChainedStructByType(void* Head, XrStructureType XRType)` (scope `OpenXR`)
- L364 _function_ `template<typename T> const T* FindChainedStructByType(const void* Head, XrStructureType XRType)` (scope `OpenXR`)
- L381 _function_ `inline void AppendChainStruct(void*& Tail, void* NewTail)` (scope `OpenXR`)

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Public/OpenXRHMDSettings.h` (Public)


#### class `UOpenXRHMDSettings`  
`class UOpenXRHMDSettings : public UDeveloperSettingsBackedByCVars`  
_L13-65_
- reflection: `UCLASS(config=Engine, defaultconfig, meta = (DisplayName = "OpenXR"))`
- inherits: `UDeveloperSettingsBackedByCVars`
- desc: Implements the settings for the OpenXR plugin.
- L22 _public member_ `bool bIsFBFoveationEnabled = false;` — `UPROPERTY(config, EditAnywhere, Category = "Foveation", meta = ( ToolTip = "Enables foveation provided by the XR_FB_foveation OpenXR extension. Requires support for hardware variable rate shading.", DisplayName = "Enable XR_FB_foveation extension"))` — Enables foveation provided by the XR_FB_foveation OpenXR extension.
- L29 _public member_ `bool bOpenXRInvertAlpha = false;` — `UPROPERTY(config, EditAnywhere, Category = "Passthrough", meta = ( ConsoleVariable = "xr.OpenXRInvertAlpha", ToolTip = "Enables alpha inversion of the background layer if the XR_EXT_composition_layer_inverted_alpha extension or XR_FB_composition_layer_alpha_blend is supported.", DisplayName = "Invert scene alpha for passthrough"))` — Enables alpha inversion of the background layer.
- L35 _public member_ `bool bIsOpenXR1_0Enabled = true;` — `UPROPERTY(config, EditAnywhere, Category = "OpenXR Versions", meta = ( ToolTip = "Enable support for OpenXR 1.0. If multiple versions are supported by the current OpenXR Runtime the latest version will be used.", DisplayName = "Enable OpenXR 1.0"))` — Enable support for OpenXR 1.0.
- L41 _public member_ `bool bIsOpenXR1_1Enabled = true;` — `UPROPERTY(config, EditAnywhere, Category = "OpenXR Versions", meta = ( ToolTip = "Enable support for OpenXR 1.1. If multiple versions are supported by the current OpenXR Runtime the latest version will be used.", DisplayName = "Enable OpenXR 1.1"))` — Enable support for OpenXR 1.1.
- L47 _public member_ `TArray<FString> BlockedExtensions;` — `UPROPERTY(config, EditAnywhere, Category = "OpenXR", meta = ( ToolTip = "List of OpenXR extension names that will be blocked and not used.\n The names must exactly match those provided in openxr_platform.h (eg \"XR_KHR_vulkan_enable\" from #define XR_KHR_VULKAN_ENABLE_EXTENSION_NAME \"XR_KHR_vulkan_enable\")\nIf a UE Core optional extension is blocked UE's OpenXR support should continue to function, but functionality or performance may be degraded.\nIf a UE Core required extension is blocked UE's OpenXR support will be disabled.\nIf a OpenXRExtensionPlugin optional extension is blocked the plugin should continue to function, but functionality or performance may be degraded.\nIf a OpenXRExtensionPlugin required extension is blocked that plugin will be disabled.\nAnticipated use cases:\n Facilitation of testing without certain extensions\n Working around runtime bugs where an extension is malfunctioning (Note that if the runtime is later fixed your project will still not use it!).\n You will need to restart the editor after changing this setting to have it effect PIE.", DisplayName = "Blocked Extensions"))` — Extension Blocking
- L54 _public member_ `int32 Priority = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Stereo Layers", meta = ( ConsoleVariable = "xr.OpenXRProjectionLayerPriority", ToolTip = "Render priority for the projection layer (main UE environment).\nStereo layers with priorities greater than or equal to this value will render above the projection layer. Layers with priorities less than this value will render below the projection layer.\nNote that some OpenXR runtimes will ignore this setting and always render the projection layer below all stereo layers.", DisplayName = "Projection Layer Priority"))` — Projection Layer Priority
- L61 _public member_ `bool bSortFaceLockedLayersAboveOtherLayers = false;` — `UPROPERTY(config, EditAnywhere, Category = "Stereo Layers", meta = ( ConsoleVariable = "xr.OpenXRSortFaceLockedLayersAboveOtherLayers", ToolTip = "Sort face locked stereo layers above all other layers, including the projection layer, even if the face locked layer has a lower priority.", DisplayName = "Sort Face Locked Layers Above Other Layers"))` — Sort face-locked layers above all other layers
- L64 _public function_ `virtual FName GetCategoryName() const override`

### `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Public/OpenXRPlatformRHI.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define XR_USE_PLATFORM_WIN32 1`
- L12 _macro_ `#define XR_USE_GRAPHICS_API_D3D11 1`
- L16 _macro_ `#define XR_USE_GRAPHICS_API_D3D12 1`
- L20 _macro_ `#define XR_USE_GRAPHICS_API_OPENGL 1`
- L24 _macro_ `#define XR_USE_PLATFORM_ANDROID 1`
- L28 _macro_ `#define XR_USE_GRAPHICS_API_OPENGL_ES 1`
- L32 _macro_ `#define XR_USE_GRAPHICS_API_VULKAN 1`
