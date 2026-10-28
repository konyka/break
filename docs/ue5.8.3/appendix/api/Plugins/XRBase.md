# Plugins / XRBase

- module root: `Plugins/Runtime/XRBase/Source/XRBase`
- headers: 21; symbols: 504
- symbol kinds: class=23, delegate=7, enum=3, enumerator=11, function=97, macro=14, member=116, prototype=226, struct=6, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, EngineSettings, InputCore, RHI, RenderCore, Renderer, Slate, UnrealEd, VREditor
- PublicDependencyModuleNames: AugmentedReality, HeadMountedDisplay

### `Plugins/Runtime/XRBase/Source/XRBase/Public/DefaultSpectatorScreenController.h` (Public)


#### class `FDefaultSpectatorScreenController`  
`class FDefaultSpectatorScreenController : public ISpectatorScreenController, public TSharedFromThis<FDefaultSpectatorScreenController, ESPMode::ThreadSafe>`  
_L19-79_
- inherits: `ISpectatorScreenController,TSharedFromThis<FDefaultSpectatorScreenController,ESPMode::ThreadSafe>`
- desc: Default implementation of spectator screen controller.
- L22 _public prototype_ `FDefaultSpectatorScreenController(FHeadMountedDisplayBase* InHMDDevice);`
- L25 _public prototype_ `virtual ~FDefaultSpectatorScreenController() = default;`
- L26 _public prototype_ `FDefaultSpectatorScreenController(const FDefaultSpectatorScreenController&) = default;`
- L27 _public prototype_ `FDefaultSpectatorScreenController(FDefaultSpectatorScreenController&&) = default;`
- L28 _public prototype_ `FDefaultSpectatorScreenController& operator=(const FDefaultSpectatorScreenController&) = default;`
- L29 _public prototype_ `FDefaultSpectatorScreenController& operator=(FDefaultSpectatorScreenController&&) = default;`
- L33 _public prototype_ `virtual ESpectatorScreenMode GetSpectatorScreenMode() const override;` — ISpectatorScreenController
- L34 _public prototype_ `virtual void SetSpectatorScreenMode(ESpectatorScreenMode Mode) override;`
- L35 _public prototype_ `virtual void SetSpectatorScreenTexture(UTexture* InTexture) override;`
- L36 _public prototype_ `virtual UTexture* GetSpectatorScreenTexture() const override;`
- L37 _public prototype_ `virtual void SetSpectatorScreenModeTexturePlusEyeLayout(const FSpectatorScreenModeTexturePlusEyeLayout& Layout) override;`
- L40 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& ViewFamily);` — Implementation methods called by HMD
- L42 _public function_ `ESpectatorScreenMode GetSpectatorScreenMode_RenderThread()`
- L47 _public prototype_ `virtual void RenderSpectatorScreen_RenderThread(class FRDGBuilder& GraphBuilder, FRDGTextureRef BackBuffer, FRDGTextureRef SrcTexture, FRDGTextureRef LayersTexture, FVector2f WindowSize);`
- L50 _protected prototype_ `virtual FIntRect GetFullFlatEyeRect_RenderThread(const FRHITextureDesc& EyeTexture);`
- L51 _protected prototype_ `virtual void AddSpectatorModePass(ESpectatorScreenMode SpectatorMode, class FRDGBuilder& GraphBuilder, FRDGTextureRef TargetTexture, FRDGTextureRef EyeTexture, FRDGTextureRef OtherTexture, FVector2f WindowSize);`
- L52 _protected prototype_ `virtual FRDGTextureRef GetFallbackRDGTexture(FRDGBuilder& GraphBuilder) const;`
- L54 _protected member_ `static constexpr ESpectatorScreenMode DefaultSpectatorMode = ESpectatorScreenMode::SingleEyeCroppedToFill;`
- L56 _protected member_ `ESpectatorScreenMode SpectatorScreenMode_GameThread = DefaultSpectatorMode;`
- L57 _protected member_ `TWeakObjectPtr<UTexture> SpectatorScreenTexture;`
- L59 _protected member_ `ESpectatorScreenMode SpectatorScreenMode_RenderThread = DefaultSpectatorMode;`
- L60 _protected member_ `FSpectatorScreenModeTexturePlusEyeLayout SpectatorScreenModeTexturePlusEyeLayout_RenderThread;`
- L61 _protected member_ `FTextureResource* SpectatorScreenTexture_RenderThread = nullptr;`
- L62 _protected member_ `ERHIFeatureLevel::Type FeatureLevel_RenderThread;`
- L63 _protected member_ `EShaderPlatform ShaderPlatform_RenderThread;`
- L73 _private prototype_ `void CopyEmulatedLayers(FRDGBuilder& GraphBuilder, FRDGTextureRef TargetTexture, const FIntRect SrcRect, const FIntRect DstRect);`
- L74 _private prototype_ `void AddSpectatorModePassTexturePlusEye(FRDGBuilder& GraphBuilder, FRDGTextureRef TargetTexture, FRDGTextureRef EyeTexture, FRDGTextureRef OtherTexture);`
- L76 _private member_ `FHeadMountedDisplayBase* HMDDevice;`
- L78 _private member_ `FRDGTextureRef StereoLayersTextureRDG;` — Face locked stereo layers are composited to a single texture which has to be copied over to the spectator screen.

#### class `FDefaultSpectatorScreenController::Helpers`  
`class Helpers`  
_L65-70_
- L68 _public prototype_ `static FIntRect GetEyeCroppedToFitRect(FVector2D EyeCenterPoint, const FIntRect& EyeRect, const FIntRect& TargetRect);`
- L69 _public prototype_ `static FIntRect GetLetterboxedDestRect(const FIntRect& SrcRect, const FIntRect& TargetRect);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API XRBASE_API`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/DefaultStereoLayers.h` (Public)


#### struct `FDefaultStereoLayers_LayerRenderParams`  
`struct FDefaultStereoLayers_LayerRenderParams`  
_L11-15_
- desc: Experimental struct
- L13 _public member_ `FIntRect Viewport;`
- L14 _public member_ `FMatrix RenderMatrices[3];`

#### class `FDefaultStereoLayers`  
`class FDefaultStereoLayers : public FSimpleLayerManager, public FHMDSceneViewExtension`  
_L22-100_
- inherits: `FSimpleLayerManager,FHMDSceneViewExtension`
- desc: Default implementation of stereo layers for platforms that require emulating layer support. FHeadmountedDisplayBase subclasses will use this implementation by default unless overridden.
- L25 _public prototype_ `FDefaultStereoLayers(const FAutoRegister& AutoRegister, FHeadMountedDisplayBase* InHMDDevice);`
- L28 _public prototype_ `virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;` — ISceneViewExtension interface
- L29 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L30 _public prototype_ `virtual void PostRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;`
- L33 _public prototype_ `virtual TArray<FTextureRHIRef, TInlineAllocator<2>> GetDebugLayerTextures_RenderThread() override;` — IStereoLayers interface
- L34 _public prototype_ `TArray<FTextureRHIRef, TInlineAllocator<2>> GetDebugLayerTexturesImpl_RenderThread();`
- L79 _public prototype_ `static void StereoLayerRender(FRHICommandListImmediate& RHICmdList, TArrayView<const FStereoLayerToRender> LayersToRender, const FDefaultStereoLayers_LayerRenderParams& RenderParams);`
- L80 _public prototype_ `static void StereoLayerRender(FRHICommandListImmediate& RHICmdList, const FStereoLayerToRender& Layer, const FDefaultStereoLayers_LayerRenderParams& RenderParams);`
- L87 _protected function_ `void UpdateHmdTransform(const FTransform& InHmdTransform)` — Invoked by FHeadMountedDisplayBase to update the HMD position during the late update.
- L92 _protected member_ `FHeadMountedDisplayBase* HMDDevice;`
- L93 _protected member_ `FTransform HmdTransform;`
- L95 _protected member_ `TArray<FStereoLayerToRender> SortedSceneLayers;`
- L96 _protected member_ `TArray<FStereoLayerToRender> SortedOverlayLayers;`
- L97 _protected member_ `bool bClearLayerBackground = false;`

#### struct `FDefaultStereoLayers::FStereoLayerToRenderTransfer`  
`struct FStereoLayerToRenderTransfer`  
_L37-55_
- desc: Experimental method
- L39 _public member_ `uint32 Id;`
- L40 _public member_ `int32 Priority;`
- L41 _public member_ `uint32 Flags;`
- L42 _public member_ `ELayerType PositionType;`
- L43 _public member_ `FVector2D QuadSize;`
- L44 _public member_ `FBox2D UVRect;`
- L45 _public member_ `FTransform Transform;`
- L46 _public member_ `FTextureResource* Texture;`
- L49 _public member_ `FString Name;`
- L52 _public prototype_ `FStereoLayerToRenderTransfer(const FLayerDesc& Desc);`
- L54 _public prototype_ `FStereoLayerToRenderTransfer(const FStereoLayerToRenderTransfer&) = default;`

#### struct `FDefaultStereoLayers::FStereoLayerToRender`  
`struct FStereoLayerToRender`  
_L57-78_
- L59 _public member_ `uint32 Id;`
- L60 _public member_ `int32 Priority;`
- L61 _public member_ `uint32 Flags;`
- L62 _public member_ `ELayerType PositionType;`
- L63 _public member_ `FVector2D QuadSize;`
- L64 _public member_ `FBox2D UVRect;`
- L65 _public member_ `FTransform Transform;`
- L66 _public member_ `FTextureRHIRef Texture;`
- L69 _public member_ `FString Name;`
- L72 _public prototype_ `FStereoLayerToRender(const FStereoLayerToRenderTransfer& Transfer);`
- L73 _public prototype_ `FStereoLayerToRender(const FStereoLayerToRender&) = default;`
- L74 _public prototype_ `FStereoLayerToRender(FStereoLayerToRender&&) = default;`
- L76 _public prototype_ `[[nodiscard]] bool operator < (const FStereoLayerToRender& Lhs);`
- L77 _public prototype_ `[[nodiscard]] bool operator > (const FStereoLayerToRender& Lhs);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API XRBASE_API`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/DefaultXRCamera.h` (Public)


#### class `FDefaultXRCamera`  
`class FDefaultXRCamera : public IXRCamera, public FHMDSceneViewExtension`  
_L16-100_
- inherits: `IXRCamera,FHMDSceneViewExtension`
- desc: Default base implementation of IXRCamera. Can either be used directly by implementations or extended with platform-specific features.
- L19 _public prototype_ `FDefaultXRCamera(const FAutoRegister&, IXRTrackingSystem* InTrackingSystem, int32 InDeviceId);`
- L21 _public prototype_ `virtual ~FDefaultXRCamera() = default;`
- L25 _public function_ `virtual FName GetSystemName() const override`
- L32 _public function_ `virtual int32 GetSystemDeviceId() const override`
- L43 _public function_ `virtual void UseImplicitHMDPosition(bool bInImplicitHMDPosition) override` — Set the view offset mode to assume an implied HMD position
- L51 _public function_ `virtual bool GetUseImplicitHMDPosition() const override` — Returns current setting controlling whether to assume an implied hmd position
- L61 _public prototype_ `virtual void ApplyHMDRotation(APlayerController* PC, FRotator& ViewRotation) override;` — Optionally called by APlayerController to apply the orientation of the headset to the PC's rotation. If this is not done then the PC will face differently than the camera, which might be good (depending on the game).
- L66 _public prototype_ `virtual bool UpdatePlayerCamera(FQuat& CurrentOrientation, FVector& CurrentPosition, float DeltaTime) override;` — Apply the orientation and position of the headset to the Camera.
- L68 _public prototype_ `virtual void OverrideFOV(float& InOutFOV) override;`
- L71 _public prototype_ `virtual void SetupLateUpdate(const FTransform& ParentToWorld, USceneComponent* Component, bool bSkipLateUpdate) override;` — Setup state for applying the render thread late update
- L73 _public prototype_ `virtual void CalculateStereoCameraOffset(const int32 ViewIndex, FRotator& ViewRotation, FVector& ViewLocation) override;`
- L77 _public prototype_ `virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;`
- L78 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L79 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L80 _public prototype_ `virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;`
- L81 _public prototype_ `virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L84 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;` — FWorldSceneViewExtension interface:
- L88 _protected member_ `IXRTrackingSystem* TrackingSystem;`
- L89 _protected member_ `const int32 DeviceId;`
- L91 _protected member_ `FRotator DeltaControlRotation;`
- L92 _protected member_ `FQuat DeltaControlOrientation;`
- L94 _protected member_ `FRotator SmoothedCameraRotation;`
- L97 _private member_ `FLateUpdateManager LateUpdate;`
- L98 _private member_ `bool bUseImplicitHMDPosition;`
- L99 _private member_ `mutable bool bCurrentFrameIsStereoRendering;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API XRBASE_API`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/DefaultXRLoadingScreen.h` (Public)


#### struct `FSplashData`  
`struct FSplashData`  
_L22-27_
- L23 _public member_ `IXRLoadingScreen::FSplashDesc Desc;`
- L24 _public member_ `uint32 LayerId;`
- L26 _public prototype_ `FSplashData(const IXRLoadingScreen::FSplashDesc& InDesc);`

#### class `FDefaultXRLoadingScreen`  
`class FDefaultXRLoadingScreen : public TXRLoadingScreenBase<FSplashData>, public FGCObject`  
_L29-54_
- inherits: `TXRLoadingScreenBase<FSplashData>,FGCObject`
- L32 _public prototype_ `FDefaultXRLoadingScreen(class IXRTrackingSystem* InTrackingSystem);`
- L35 _public prototype_ `virtual void ShowLoadingScreen() override;` — IXRLoadingScreen interface
- L36 _public prototype_ `virtual void HideLoadingScreen() override;`
- L37 _public prototype_ `virtual bool IsPlayingLoadingMovie() const override;`
- L40 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L41 _public function_ `virtual FString GetReferencerName() const override`
- L45 _private prototype_ `IStereoLayers* GetStereoLayers() const;`
- L48 _protected prototype_ `virtual void DoShowSplash(FSplashData& Splash) override;`
- L49 _protected prototype_ `virtual void DoHideSplash(FSplashData& Splash) override;`
- L50 _protected function_ `virtual void DoAddSplash(FSplashData& Splash) override`
- L51 _protected prototype_ `virtual void DoDeleteSplash(FSplashData& Splash) override;`
- L52 _protected prototype_ `virtual void ApplyDeltaRotation(const FSplashData& Splash) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API XRBASE_API`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/HeadMountedDisplayBase.h` (Public)


#### class `FHeadMountedDisplayBase`  
`class FHeadMountedDisplayBase : public FXRTrackingSystemBase, public IHeadMountedDisplay, public IStereoRendering`  
_L17-106_
- inherits: `FXRTrackingSystemBase,IHeadMountedDisplay,IStereoRendering`
- L21 _public prototype_ `FHeadMountedDisplayBase(IARSystemSupport* InARImplementation);`
- L22 _public prototype_ `virtual ~FHeadMountedDisplayBase() = default;`
- L27 _public function_ `virtual FName GetHMDName() const override` — Retrieves the HMD name, by default this is the same as the system name.
- L32 _public prototype_ `virtual void RecordAnalytics() override;` — Record analytics - To add custom information logged with the analytics, override PopulateAnalyticsAttributes
- L37 _public prototype_ `virtual bool IsHeadTrackingAllowed() const override;` — Default IXRTrackingSystem implementation
- L41 _public prototype_ `virtual bool IsHeadTrackingEnforced() const override;` — Optional IXRTrackingSystem methods.
- L42 _public prototype_ `virtual void SetHeadTrackingEnforced(bool bEnabled) override;`
- L47 _public prototype_ `virtual IStereoLayers* GetStereoLayers() override;` — Default stereo layer implementation
- L49 _public prototype_ `virtual bool GetHMDDistortionEnabled(EShadingPath ShadingPath) const override;`
- L51 _public prototype_ `virtual void OnLateUpdateApplied_RenderThread(FRDGBuilder& GraphBuilder, const FTransform& NewRelativeTransform) override;`
- L53 _public prototype_ `virtual void CalculateStereoViewOffset(const int32 ViewIndex, FRotator& ViewRotation, const float WorldToMeters, FVector& ViewLocation) override;`
- L55 _public prototype_ `virtual bool IsSpectatorScreenActive() const override;`
- L57 _public prototype_ `virtual class ISpectatorScreenController* GetSpectatorScreenController() override;`
- L58 _public prototype_ `virtual class ISpectatorScreenController const* GetSpectatorScreenController() const override;`
- L62 _public prototype_ `virtual FVector2D GetEyeCenterPoint_RenderThread(const int32 ViewIndex) const;` — Spectator Screen Hooks into specific implementations Get the point on the left eye render target which the viewers eye is aimed directly at when looking straight forward. 0,0 is top left.
- L64 _public function_ `virtual FIntRect GetFullFlatEyeRect_RenderThread(const FRHITextureDesc& EyeTexture) const` — Get the rectangle of the HMD rendertarget for the left eye which seems undistorted enough to be cropped and displayed on the spectator screen.
- L72 _protected prototype_ `virtual bool PopulateAnalyticsAttributes(TArray<struct FAnalyticsEventAttribute>& EventAttributes);` — Called by RecordAnalytics when creating the analytics event sent during HMD initialization. Return false to disable recording the analytics event
- L80 _protected function_ `virtual FTextureRHIRef GetOverlayLayerTarget_RenderThread(int32 ViewIndex, FIntRect& InOutViewport)` — Implement this method to provide an alternate render target for head locked stereo layer rendering, when using the default Stereo Layers implementation. Return a FTextureRHIRef pointing to a texture that can be composed on top of each eye without applying reprojection to it. Return nullptr to render head locked stereo layers into the same render target as other layer types, in which case InOutViewport must not be modified.
- L86 _protected function_ `virtual FTextureRHIRef GetSceneLayerTarget_RenderThread(int32 ViewIndex, FIntRect& InOutViewport)` — Implement this method to override the render target for scene based stereo layers. Return nullptr to render stereo layers into the normal render target passed to the stereo layers scene view extension, in which case OutViewport must not be modified.
- L88 _protected member_ `mutable TSharedPtr<class FDefaultStereoLayers, ESPMode::ThreadSafe> DefaultStereoLayers;`
- L92 _protected member_ `TUniquePtr<FDefaultSpectatorScreenController> SpectatorScreenController;`
- L95 _protected member_ `static constexpr float PixelDensityMin = 0.1f;` — Sane pixel density values
- L96 _protected member_ `static constexpr float PixelDensityMax = 2.0f;`
- L101 _protected prototype_ `static void CVarSinkHandler();` — CVar sink for pixel density
- L102 _protected member_ `static FAutoConsoleVariableSink CVarSink;`
- L105 _private member_ `bool bHeadTrackingEnforced;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API XRBASE_API`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/HeadMountedDisplayFunctionLibrary.h` (Public)


#### class `UHeadMountedDisplayFunctionLibrary`  
`class UHeadMountedDisplayFunctionLibrary : public UBlueprintFunctionLibrary`  
_L18-420_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L28 _private prototype_ `static bool IsHeadMountedDisplayEnabled();` — `UFUNCTION(BlueprintPure, Category="Input|HeadMountedDisplay", meta = (KeyWords = "HMD"))` — Returns whether or not we are currently using the head mounted display. @return (Boolean)  status of HMD
- L36 _private prototype_ `static bool IsHeadMountedDisplayConnected();` — `UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay", meta = (KeyWords = "HMD"))` — Returns whether or not the HMD hardware is connected and ready to use.  It may or may not actually be in use. @return (Boolean)  status whether the HMD hardware is connected and ready to use.  It may or may not actually be in use.
- L45 _private prototype_ `static bool EnableHMD(bool bEnable);` — `UFUNCTION(BlueprintCallable, Category="Input|HeadMountedDisplay")` — Switches to/from using HMD and stereo rendering. @param bEnable			(in) 'true' to enable HMD / stereo; 'false' otherwise @return (Boolean)		True, if the request was successful.
- L53 _private prototype_ `static FName GetHMDDeviceName();` — `UFUNCTION(BlueprintPure, Category="Input|HeadMountedDisplay")` — Returns the name of the device, so scripts can modify their behaviour appropriately @return	FName specific to the currently active HMD device type.  "None" implies no device, "Unknown" implies a device with no description.
- L61 _private prototype_ `static int32 GetXRSystemFlags();` — `UFUNCTION(BlueprintPure, Category="Input|HeadMountedDisplay")` — Returns the flags for the device, so scripts can modify their behaviour appropriately @return	IsAR, IsTablet, IsHeadMounted.  Returns false
- L67 _private prototype_ `static FString GetVersionString();` — `UFUNCTION(BlueprintPure, Category = "HeadMountedDisplay")` — Returns name of tracking system specific version string.
- L75 _private prototype_ `static EHMDWornState::Type GetHMDWornState();` — `UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay")` — Returns the worn state of the device. @return	Unknown, Worn, NotWorn.  If the platform does not detect this it will always return Unknown.
- L84 _private prototype_ `static void GetOrientationAndPosition(FRotator& DeviceRotation, FVector& DevicePosition);` — `UFUNCTION(BlueprintPure, Category="Input|HeadMountedDisplay")` — Grabs the current orientation and position for the HMD.  If positional tracking is not available, DevicePosition will be a zero vector @param DeviceRotation	(out) The device's current rotation @param DevicePosition	(out) The device's current position, in its own tracking space
- L90 _private prototype_ `static bool HasValidTrackingPosition();` — `UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay")` — If the HMD supports positional tracking, whether or not we are currently being tracked
- L96 _private prototype_ `static int32 GetNumOfTrackingSensors();` — `UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay")` — If the HMD has multiple positional tracking sensors, return a total number of them currently connected.
- L115 _private prototype_ `static void GetTrackingSensorParameters(FVector& Origin, FRotator& Rotation, float& LeftFOV, float& RightFOV, float& TopFOV, float& BottomFOV, float& Distance, float& NearPlane, float& FarPlane, bool& IsActive, int32 Index = 0);` — `UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay", meta = (AdvancedDisplay = "LeftFOV,RightFOV,TopFOV,BottomFOV,Distance,NearPlane,FarPlane"))` — If the HMD has a positional sensor, this will return the game-world location of it, as well as the parameters for the bounding region of tracking. This allows an in-game representation of the legal positional tracking range.  All values will be zeroed if the sensor is not available or the HMD does not support it. @param Index				(in) Index of the tracking sensor to query @param Origin			(out) Origin, in world-space, of the sensor @param Rotation			(out) Rotation, in world-space, of the sensor @param LeftFOV			(out) Field-of-view, left from center, in degrees, of the valid tracking zone of the sensor @param RightFOV			(out) Field-of-view, right from center, in degrees, of the valid tracking zone of the sensor @param TopFOV			(out) Field-of-view, top from center, in degrees, of the valid tracking zone of the sensor @param BottomFOV			(out) Field-of-view, bottom from center, in degrees, of the valid tracking zone of the sensor @param Distance			(out) Nominal distance to sensor, in world-space @param NearPlane			(out) Near plane distance of the tracking volume, in world-space @param FarPlane			(out) Far plane distance of the tracking volume, in world-space @param IsActive			(out) True, if the query for the specified sensor succeeded.
- L125 _private prototype_ `static void ResetOrientationAndPosition(float Yaw = 0.f, EOrientPositionSelector::Type Options = EOrientPositionSelector::OrientationAndPosition);` — `UFUNCTION(BlueprintCallable, Category="Input|HeadMountedDisplay")` — Resets orientation by setting roll and pitch to 0, assuming that current yaw is forward direction and assuming current position as a 'zero-point' (for positional tracking). @param Yaw				(in) the desired yaw to be set after orientation reset. @param Options			(in) specifies either position, orientation or both should be reset.
- L135 _private prototype_ `static void SetClippingPlanes(float Near, float Far);` — `UFUNCTION(BlueprintCallable, Category="Input|HeadMountedDisplay")` — Sets near and far clipping planes (NCP and FCP) for stereo rendering. Similar to 'stereo ncp= fcp' console command, but NCP and FCP set by this call won't be saved in .ini file. @param Near				(in) Near clipping plane, in centimeters @param Far				(in) Far clipping plane, in centimeters
- L150 _private prototype_ `static float GetXRSecondaryScreenPercentage();` — `UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay", meta = (DisplayName = "Get XR Secondary Screen Percentage"))` — Returns the current XR secondary screen precentage. This sets the final render target size as a percentage of the recommended texture size. Just before the render target is displayed by the HMD, it's distorted by the device's runtime compositor to counteract the distortion a user would normally experience when looking through the device's lenses. The recommended texture size is the size that will result in no undersampling in the most distorted area of the view after this step is performed. @return (float)	The secondary screen percentage to be used in XR mode.
- L167 _private function_ `static float GetPixelDensity()` — `UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay", meta = (DeprecatedFunction, Deprecationmessage = "Replaced with GetHMDSecondaryScreenPercentage for 5.6."))` — Returns the current XR pixel density. This sets the final render target size as a factor of the recommended texture size. Just before the render target is displayed by the HMD, it's distorted by the device's runtime compositor to counteract the distortion a user would normally experience when looking through the device's lenses. The recommended texture size is the size that will result in no undersampling in the most distorted area of the view after this step is performed. This function is deprecated, and will return the HMD secondary screen percentage divided by 100. @return (float)	The pixel density to be used in XR mode.
- L178 _private prototype_ `static void SetWorldToMetersScale(UObject* WorldContext, float NewScale = 100.f);` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay", meta = (WorldContext = "WorldContext"))` — Sets the World to Meters scale, which changes the scale of the world as perceived by the player @param NewScale	Specifies how many Unreal units correspond to one meter in the real world
- L186 _private prototype_ `static float GetWorldToMetersScale(UObject* WorldContext);` — `UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay", meta = (WorldContext = "WorldContext"))` — Returns the World to Meters scale, which corresponds to the scale of the world as perceived by the player @return	How many Unreal units correspond to one meter in the real world
- L192 _private prototype_ `static void SetTrackingOrigin(TEnumAsByte<EHMDTrackingOrigin::Type> Origin);` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay")` — Sets current tracking origin type (eye level or floor level).
- L198 _private prototype_ `static TEnumAsByte<EHMDTrackingOrigin::Type> GetTrackingOrigin();` — `UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay")` — Returns current tracking origin type (eye level or floor level).
- L205 _private prototype_ `static FTransform GetTrackingToWorldTransform(UObject* WorldContext);` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay", meta=(WorldContext="WorldContext"))` — Returns a transform that can be used to convert points from tracking space to world space. Does NOT include the set WorldToMeters scale, as that is added in by the backing XR system to their tracking space poses.
- L217 _private prototype_ `static void CalibrateExternalTrackingToHMD(const FTransform& ExternalTrackingTransform);` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay|ExternalTracking")` — Called to calibrate the offset transform between an external tracking source and the internal tracking source (e.g. mocap tracker to and HMD tracker).  This should be called once per session, or when the physical relationship between the external tracker and internal tracker changes (e.g. it was bumped or reattached).  After calibration, calling UpdateExternalTrackingPosition will try to correct the internal tracker to the calibrated offset to prevent drift between the two systems @param ExternalTrackingTransform		The transform in world-coordinates, of the reference marker of the external tracking system
- L228 _private prototype_ `static void UpdateExternalTrackingHMDPosition(const FTransform& ExternalTrackingTransform);` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay|ExternalTracking")` — Called after calibration to attempt to pull the internal tracker (e.g. HMD tracking) in line with the external tracker (e.g. mocap tracker).  This will set the internal tracker's base offset and rotation to match and realign the two systems. This can be called every tick, or whenever realignment is desired.  Note that this may cause choppy movement if the two systems diverge relative to each other, or a big jump if called infrequently when there has been significant drift @param ExternalTrackingTransform		The transform in world-coordinates, of the reference marker of the external tracking system
- L237 _private prototype_ `static void GetVRFocusState(bool& bUseFocus, bool& bHasFocus);` — `UFUNCTION(BlueprintPure, Category="Input|HeadMountedDisplay", meta=(DisplayName="Get VR Focus State"))` — Returns current state of VR focus. @param bUseFocus		(out) if set to true, then this App does use VR focus. @param bHasFocus		(out) if set to true, then this App currently has VR focus.
- L243 _private prototype_ `static bool IsSpectatorScreenModeControllable();` — `UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay|SpectatorScreen")` — Return true if spectator screen mode control is available.
- L250 _private prototype_ `static void SetSpectatorScreenMode(ESpectatorScreenMode Mode);` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay|SpectatorScreen")` — Sets the social screen mode. @param Mode				(in) The social screen Mode.
- L257 _private prototype_ `static void SetSpectatorScreenTexture(UTexture* InTexture);` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay|SpectatorScreen")` — Change the texture displayed on the social screen @param	InTexture: new Texture2D
- L269 _private prototype_ `static void SetSpectatorScreenModeTexturePlusEyeLayout(FVector2D EyeRectMin, FVector2D EyeRectMax, FVector2D TextureRectMin, FVector2D TextureRectMax, bool bDrawEyeFirst = true, bool bClearBlack = false, bool bUseAlpha = false);` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay|SpectatorScreen")` — Setup the layout for ESpectatorScreenMode::TexturePlusEye. @param	EyeRectMin: min of screen rectangle the eye will be drawn in.  0-1 normalized. @param	EyeRectMax: max of screen rectangle the eye will be drawn in.  0-1 normalized. @param	TextureRectMin: min of screen rectangle the texture will be drawn in.  0-1 normalized. @param	TextureRectMax: max of screen rectangle the texture will be drawn in.  0-1 normalized. @param	bDrawEyeFirst: if true the eye is drawn before the texture, if false the reverse. @param	bClearBlack: if true the render target will be drawn black before either rect is drawn.
- L281 _private prototype_ `static bool SetHMDColorScaleAndBias(FLinearColor ColorScale, FLinearColor ColorBias);` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay")` — Multiply the post-compositor frame by a color and add a bias. LayerColor = LayerColor * ColorScale + ColorBias @param ColorScale		(in) Color to multiply the compositor layer by @param ColorBias			(in) Color to offset the compositor layer by @return  (boolean)		True if successful, false if unsuccessful or unsupported.
- L292 _private prototype_ `static TArray<FXRDeviceId> EnumerateTrackedDevices(const FName SystemId = NAME_None, EXRTrackedDeviceType DeviceType = EXRTrackedDeviceType::Any);` — `UFUNCTION(BlueprintCallable, Category="Input|XRTracking")` — Cross XR-System query that will list all XR devices currently being tracked. @param  SystemId		(Optional) Specifies an explicit system to poll devices from (use if you want only devices belonging to one explicit XR ecosystem, e.g. 'OculusHMD', or 'OpenXR') @param  DeviceType	Specifies the type of device to query for - defaults to 'Any' (meaning 'All'). @return A list of device identifiers matching the query. Use these to query and operate on the device (e.g. through GetDevicePose, AddDeviceVisualizationComponent, etc.)
- L304 _private prototype_ `static void GetDevicePose(const FXRDeviceId& XRDeviceId, bool& bIsTracked, FRotator& Orientation, bool& bHasPositionalTracking, FVector& Position);` — `UFUNCTION(BlueprintCallable, Category="Input|XRTracking")` — Cross XR-System query that returns a specific device's tracked position and orientation (in tracking space). @param  XRDeviceId				Specifies the device you're querying for. @param  bIsTracked				[out] Details if the specified device is tracked (i.e. should the rest of the outputs be used) @param  Orientation				[out] Represents the device's current rotation - NOTE: this value is not late updated and will be behind the render thread @param  bHasPositionalTracking	[out] Details if the specified device has positional tracking (i.e. if the position output should be used) @param  Position					[out] Represents the device's current position - NOTE: this value is not late updated and will be behind the render thread
- L316 _private prototype_ `static void GetDeviceWorldPose(UObject* WorldContext, const FXRDeviceId& XRDeviceId, bool& bIsTracked, FRotator& Orientation, bool& bHasPositionalTracking, FVector& Position);` — `UFUNCTION(BlueprintCallable, Category="Input|XRTracking", meta=(WorldContext="WorldContext"))` — Cross XR-System query that returns a specific device's position and orientation in world space. @param  XRDeviceId				Specifies the device you're querying for. @param  bIsTracked				[out] Details if the specified device is tracked (i.e. should the rest of the outputs be used) @param  Orientation				[out] Represents the device's current rotation - NOTE: this value is not late updated and will be behind the render thread @param  bHasPositionalTracking	[out] Details if the specified device has positional tracking (i.e. if the position output should be used) @param  Position					[out] Represents the device's current position - NOTE: this value is not late updated and will be behind the render thread
- L324 _private prototype_ `static bool IsDeviceTracking(const FXRDeviceId& XRDeviceId);` — `UFUNCTION(BlueprintCallable, Category="Input|XRTracking")` — Cross XR-System query that returns whether the specified device is tracked or not. @param  XRDeviceId	Specifies the device you're querying for.
- L330 _private prototype_ `static void GetHMDData(UObject* WorldContext, FXRHMDData& HMDData);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Cross XR-System query that returns critical information about the HMD display (position, orientation, device name)
- L341 _private prototype_ `static void GetMotionControllerState(UObject* WorldContext, const EXRSpaceType XRSpaceType, const EControllerHand Hand, const EXRControllerPoseType ControllerPoseType, FXRMotionControllerState& MotionControllerState);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Cross XR-System query that returns critical information about the motion controller (position, orientation) @param  WorldContext				Any object in the world (the player pawn would work).  Used in PIE to make sure we get this data from a motioncontroller component that is currently active, rather than one in an editor view world that is never tracked. @param  XRSpaceType				Can switch between unreal world coordinates and tracking space coordinates.  Tracking space may be useful with non-1:1 world scales. @param  Hand						Indicates which hand we want data for. @param  MotionControllerData		[out] Struct filled with information about the motion controller state.
- L352 _private prototype_ `static void GetHandTrackingState(UObject* WorldContext, const EXRSpaceType XRSpaceType, const EControllerHand Hand, FXRHandTrackingState& HandTrackingState);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Cross XR-System query that returns critical information about the motion controller (position, orientation, hand/finger position) @param  WorldContext				Any object in the world (the player pawn would work).  Used in PIE to make sure we get this data from a motioncontroller component that is currently active, rather than one in an editor view world that is never tracked. @param  XRSpaceType				Can switch between unreal world coordinates and tracking space coordinates.  Tracking space may be useful with non-1:1 world scales. @param  Hand						Indicates which hand we want data for. @param  HandTrackingData			[out] Struct filled with information about the hand tracking state.
- L359 _private prototype_ `static bool GetCurrentInteractionProfile(const EControllerHand Hand, FString& InteractionProfile);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking|OpenXR")` — Get the openXR interaction profile name for the given controller. Returns true if the openxr call is successfully made.  The string may be empty if there is no interaction profile associated with the controller.
- L363 _private prototype_ `static EXRDeviceConnectionResult::Type ConnectRemoteXRDevice(const FString& IpAddress, const int32 BitRate);` — `UFUNCTION(BlueprintCallable, Category = "XR|HeadMountedDisplay")` — Connect to a remote device
- L366 _private prototype_ `static void DisconnectRemoteXRDevice();` — `UFUNCTION(BlueprintCallable, Category = "XR|HeadMountedDisplay")` — Disconnect remote AR Device
- L368 _private prototype_ `static void SetXRDisconnectDelegate(const FXRDeviceOnDisconnectDelegate& InDisconnectedDelegate);` — `UFUNCTION(BlueprintCallable, Category = "XR|HeadMountedDisplay")`
- L369 _private member_ `static FXRDeviceOnDisconnectDelegate OnXRDeviceOnDisconnectDelegate;`
- L379 _private prototype_ `static void SetXRTimedInputActionDelegate(const FName& ActionName, const FXRTimedInputActionDelegate& InDelegate);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Hook up a delegate to get an OpenXR action event with action time. For a boolean input the the 'value' parameter of the delegate will be 1.0 for a press and 0.0 for a release.  For an analog input the value's range is action and platform specific. Use in combination with GetControllerTransformForTime2 for potentially improved temporal transform precision and velocity data. "Left Grip" is an example of a valid ActionName. Note: this is likely to be replaced by native support for event times in the core input system at some time in the future.
- L382 _private prototype_ `static void ClearXRTimedInputActionDelegate(const FName& ActionPath);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — /  Clear a delegate to get an OpenXR action event with action time.
- L383 _private member_ `static TMap<FName, FXRTimedInputActionDelegate> OnXRTimedInputActionDelegateMap;`
- L397 _private prototype_ `static bool GetControllerTransformForTime2(UObject* WorldContext, const int32 ControllerIndex, const FName MotionSource, FTimespan Time, bool& bTimeWasUsed, FRotator& Orientation, FVector& Position, bool& bProvidedLinearVelocity, FVector& LinearVelocity, bool& bProvidedAngularVelocity, FRotator& AngularVelocity, bool& bProvidedLinearAcceleration, FVector& LinearAcceleration);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Get the transform and potentially velocity data at a specified time near the current frame in unreal world space. This is intended for use with sub-frame input action timing data from SetXRTimedInputActionDelegate, or future support for timestamps in the core input system. The valid time window is platform dependent, but the intention per OpenXR is to fetch transforms for times from, at most, the previous few frames in the past or future. The OpenXR spec suggests that 50ms in the past should return an accurate result.  There is no guarantee for the future, but the underlying system is likely to have been designed to predict out to about 50ms as well. On some platforms this  will always just return a cached position and rotation, ignoring time.  bTimeWasUsed will be false in that case. AngularVelocity is a Rotator in degrees/second. Be aware that this Rotator may have windings (rotations greater than 360 degrees) and some mathmatical operations (such as conversion to quaternion) will remove the windings. In some cases that is OK becuase the resulting final rotation is the same, but in some cases it would generate incorrect results.
- L403 _private prototype_ `static FVector2D GetPlayAreaBounds(TEnumAsByte<EHMDTrackingOrigin::Type> Origin = EHMDTrackingOrigin::Stage);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Get the bounds of the area where the user can freely move while remaining tracked centered around the specified origin
- L409 _private prototype_ `static bool GetTrackingOriginTransform(TEnumAsByte<EHMDTrackingOrigin::Type> Origin, FTransform& OutTransform);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Get the transform of the specified tracking origin, if available.
- L415 _private prototype_ `static bool GetPlayAreaRect(FTransform& OutTransform, FVector2D& OutRect);` — `UFUNCTION(BlueprintCallable, Category = "Input|XRTracking")` — Get the transform and dimensions of the playable area rectangle.  Returns false if none currently specified/available.
- L419 _private prototype_ `static void BreakKey(FKey InKey, FString& InteractionProfile, EControllerHand& Hand, FName& MotionSource, FString& Indentifier, FString& Component);` — `UFUNCTION(BlueprintPure, Category = "Input|XRTracking", meta = (NativeBreakFunc))` — Breaks an XR key apart into the interaction profile, handedness, motion source, indentifier and component.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API XRBASE_API`
- L14 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FXRDeviceOnDisconnectDelegate, const FString, OutReason);`
- L14 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FXRDeviceOnDisconnectDelegate, const FString, OutReason);`
- L15 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FXRTimedInputActionDelegate, const float, Value, const FTimespan, Time);`
- L15 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FXRTimedInputActionDelegate, const float, Value, const FTimespan, Time);`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/MotionTrackedDeviceFunctionLibrary.h` (Public)


#### class `UMotionTrackedDeviceFunctionLibrary`  
`class UMotionTrackedDeviceFunctionLibrary : public UBlueprintFunctionLibrary`  
_L17-179_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L28 _private prototype_ `static bool IsMotionTrackedDeviceCountManagementNecessary();` — `UFUNCTION(BlueprintPure, Category = "Input|MotionTracking")` — Returns true if it is necessary for the game to manage how many motion tracked devices it is asking to be tracked simultaneously. On some platforms this is unnecessary because all supported devices can be tracked simultaneously. @return (Boolean) true if the game might need to manage which motion tracked devices are actively tracked.
- L36 _private prototype_ `static void SetIsControllerMotionTrackingEnabledByDefault(bool Enable);` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking")` — Set whether motion tracked controllers activate on creation by default, or do not and must be explicitly activated. @param Require					(in) True means controllers are enabled by default.  Enables beyond the controller count limit will fail.
- L44 _private prototype_ `static int32 GetMaximumMotionTrackedControllerCount();` — `UFUNCTION(BlueprintPure, Category = "Input|MotionTracking")` — Get the maximum number of controllers that can be tracked. @return (int) number of controllers that can be tracked, or -1 if there is no limit (IsMotionTrackedDeviceCountManagementNecessary() should return false).
- L52 _private prototype_ `static int32 GetMotionTrackingEnabledControllerCount();` — `UFUNCTION(BlueprintPure, Category = "Input|MotionTracking")` — Get the number of controllers for which tracking is enabled. @return (int) number of controllers tracked now, or -1 if this query is unsupported (IsMotionTrackedDeviceCountManagementNecessary() should return false).
- L63 _private prototype_ `static bool IsMotionTrackingEnabledForDevice(int32 PlayerIndex, EControllerHand Hand);` — `UFUNCTION(BlueprintPure, Category = "Input|MotionTracking", meta = (DeprecatedFunction, DeprecationMessage = "EControllerHand has been deprecated, please use IsMotionTrackingEnabledForSource instead."))` — Returns true if tracking is enabled for the specified device. @param PlayerIndex					(in) The index of the player. @param Hand							(in) The tracked device type. @return (Boolean) true if the specified device is set to be tracked.
- L74 _private prototype_ `static bool IsMotionTrackingEnabledForSource(int32 PlayerIndex, FName SourceName);` — `UFUNCTION(BlueprintPure, Category = "Input|MotionTracking")` — Returns true if tracking is enabled for the specified device. @param PlayerIndex					(in) The index of the player. @param SourceName					(in) The tracked device id. @return (Boolean) true if the specified device is set to be tracked.
- L84 _private prototype_ `static bool IsMotionTrackingEnabledForComponent(const class UMotionControllerComponent* MotionControllerComponent);` — `UFUNCTION(BlueprintPure, Category = "Input|MotionTracking")` — Returns true if tracking is enabled for the specified device. @param MotionControllerComponent		(in) The motion controller component who's associated device is targeted. @return (Boolean) true if the specified device is set to be tracked.
- L95 _private prototype_ `static bool EnableMotionTrackingOfDevice(int32 PlayerIndex, EControllerHand Hand);` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking", meta = (DeprecatedFunction, DeprecationMessage = "EControllerHand has been deprecated, please use EnableMotionTrackingOfSource instead."))` — Enable tracking of the specified controller, by player index and tracked device type. @param PlayerIndex					(in) The index of the player. @param Hand							(in) The device type. @return (Boolean) true if the specified device is now set to be tracked.  This could fail due to tracking limits, or on invalid input.
- L106 _private prototype_ `static bool EnableMotionTrackingOfSource(int32 PlayerIndex, FName SourceName);` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking")` — Enable tracking of the specified controller, by player index and tracked device type. @param PlayerIndex					(in) The index of the player. @param SourceName					(in) The device id. @return (Boolean) true if the specified device is now set to be tracked.  This could fail due to tracking limits, or on invalid input.
- L116 _private prototype_ `static bool EnableMotionTrackingForComponent(class UMotionControllerComponent* MotionControllerComponent);` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking")` — Enable tracking of the specified controller, by player index and tracked device type. @param MotionControllerComponent		(in) The motion controller component who's associated device is targeted. @return (Boolean) true if the specified device is now set to be tracked.  This could fail due to tracking limits, or on invalid input.
- L125 _private prototype_ `static void DisableMotionTrackingOfDevice(int32 PlayerIndex, EControllerHand Hand);` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking", meta = (DeprecatedFunction, DeprecationMessage = "EControllerHand has been deprecated, please use DisableMotionTrackingOfSource instead."))` — Disable tracking of the specified controller, by player index and tracked device type. @param PlayerIndex					(in) The index of the player. @param Hand							(in) The tracked device type.
- L134 _private prototype_ `static void DisableMotionTrackingOfSource(int32 PlayerIndex, FName SourceName);` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking")` — Disable tracking of the specified controller, by player index and tracked device type. @param PlayerIndex					(in) The index of the player. @param SourceName					(in) The tracked device id.
- L142 _private prototype_ `static void DisableMotionTrackingForComponent(const class UMotionControllerComponent* MotionControllerComponent);` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking")` — Disable tracking of the specified controller, by player index and tracked device type. @param MotionControllerComponent		(in) The motion controller component who's associated device is targeted.
- L148 _private prototype_ `static void DisableMotionTrackingOfAllControllers();` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking")` — Disable tracking for all controllers.
- L156 _private prototype_ `static void DisableMotionTrackingOfControllersForPlayer(int32 PlayerIndex);` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking")` — Disable tracking for all controllers associated with the specified player. @param PlayerIndex					(in) The index of the player.
- L163 _private prototype_ `static TArray<FName> EnumerateMotionSources();` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking")` — Returns a list of all available motion sources (FNames associated with discrete tracking data that can be used to drive MotionControllerComponents).
- L170 _private prototype_ `static FName GetActiveTrackingSystemName();` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking")` — Returns the system name used to distinguish the current tracking system. If no XR tracking system is active, then the name 'None' is returned.
- L178 _private prototype_ `static bool IsMotionSourceTracking(int32 PlayerIndex, FName SourceName);` — `UFUNCTION(BlueprintCallable, Category = "Input|MotionTracking")` — Queries the specified source's tracking status and returns true if it has tracking. @return Tracking status of the specified controller.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API XRBASE_API`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/StereoLayerManager.h` (Public)


#### class `FSimpleLayerManager`  
`class FSimpleLayerManager : public IStereoLayers, public FGCObject`  
_L27-300_
- inherits: `IStereoLayers,FGCObject`
- L30 _private member_ `bool bStereoLayersDirty;`
- L40 _private member_ `TArray<FLayerData> LayerStack;`
- L42 _private function_ `FLayerData& LayerState(int Level=0)`
- L43 _private function_ `const FLayerData& LayerState(int Level = 0) const`
- L44 _private function_ `TMap<uint32, FLayerDesc>& StereoLayers(int Level = 0)`
- L45 _private function_ `const TMap<uint32, FLayerDesc>& StereoLayers(int Level = 0) const`
- L46 _private function_ `uint32 MakeLayerId()`
- L48 _private function_ `FLayerDesc* FindLayerById(uint32 LayerId, int32& OutLevel)`
- L70 _protected function_ `virtual void UpdateLayer(FLayerDesc& Layer, uint32 LayerId, bool bIsValid)`
- L73 _protected function_ `bool GetStereoLayersDirty()`
- L81 _protected function_ `void ForEachLayer(TFunction<void(uint32, FLayerDesc&)> Func, bool bMarkClean = true)`
- L98 _public function_ `FSimpleLayerManager() : bStereoLayersDirty(false) , LayerStack`
- L104 _public function_ `virtual ~FSimpleLayerManager()`
- L107 _public prototype_ `FSimpleLayerManager(const FSimpleLayerManager&) = default;`
- L108 _public prototype_ `FSimpleLayerManager(FSimpleLayerManager&&) = default;`
- L109 _public prototype_ `FSimpleLayerManager& operator=(const FSimpleLayerManager&) = default;`
- L110 _public prototype_ `FSimpleLayerManager& operator=(FSimpleLayerManager&&) = default;`
- L113 _public function_ `virtual uint32 CreateLayer(const FLayerDesc& InLayerDesc) override` — IStereoLayers interface
- L126 _public function_ `virtual void DestroyLayer(uint32 LayerId) override`
- L151 _public function_ `virtual void SetLayerDesc(uint32 LayerId, const FLayerDesc& InLayerDesc) override`
- L177 _public function_ `virtual bool GetLayerDesc(uint32 LayerId, FLayerDesc& OutLayerDesc) override`
- L199 _public function_ `virtual const FLayerDesc* FindLayerDesc(uint32 LayerId) const override`
- L204 _public function_ `virtual void MarkTextureForUpdate(uint32 LayerId) override`
- L221 _public function_ `virtual void PushLayerState(bool bPreserve = false) override`
- L248 _public function_ `virtual void PopLayerState() override`
- L281 _public function_ `virtual bool SupportsLayerState() override`
- L283 _public function_ `virtual void HideBackgroundLayer()`
- L284 _public function_ `virtual void ShowBackgroundLayer()`
- L285 _public function_ `virtual bool IsBackgroundLayerVisible() const`
- L288 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override` — FGCObject interface ********************************************************************
- L299 _public function_ `virtual FString GetReferencerName() const override`

#### struct `FSimpleLayerManager::FLayerData`  
`struct FLayerData`  
_L32-39_
- L33 _public member_ `TMap<uint32, FLayerDesc> Layers;`
- L34 _public member_ `uint32 NextLayerId;`
- L35 _public member_ `bool bShowBackground;`
- L37 _public function_ `FLayerData(uint32 InNext, bool bInShowBackground = true) : Layers(), NextLayerId(InNext), bShowBackground(bInShowBackground)`
- L38 _public function_ `FLayerData(const FLayerData& In) : Layers(In.Layers), NextLayerId(In.NextLayerId), bShowBackground(In.bShowBackground)`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/VRNotificationsComponent.h` (Public)


#### class `UVRNotificationsComponent`  
`class UVRNotificationsComponent : public UActorComponent`  
_L21-94_
- reflection: `UCLASS(MinimalAPI, Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = HeadMountedDisplay)`
- inherits: `UActorComponent`
- L25 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVRNotificationsDelegate);`
- L29 _private member_ `FVRNotificationsDelegate HMDTrackingInitializingAndNeedsHMDToBeTrackedDelegate;` — `UE_DEPRECATED(5.8, "Deprecated, no longer used.")` — `UPROPERTY(BlueprintAssignable, meta = (DeprecatedProperty, DeprecationMessage = "Deprecated, no longer used."))`
- L33 _private member_ `FVRNotificationsDelegate HMDTrackingInitializedDelegate;` — `UE_DEPRECATED(5.8, "Deprecated, no longer used.")` — `UPROPERTY(BlueprintAssignable, meta = (DeprecatedProperty, DeprecationMessage = "Deprecated, no longer used."))`
- L40 _private member_ `FVRNotificationsDelegate HMDRecenteredDelegate;` — `UPROPERTY(BlueprintAssignable)` — This will be called when the XR runtime requests a recenter (such as when a system recenter button is pressed). Whether or not the HMD will actually be recentered on the runtime side depends on the runtime, device, and current tracking space (local/stage). By default, we do not automatically recenter on the application side. Recentering on either the runtime side or application side is sufficient to recenter the user, and recentering on both sides at once is acceptable.
- L44 _private member_ `FVRNotificationsDelegate HMDLostDelegate;` — `UPROPERTY(BlueprintAssignable)` — This will be called when connection to HMD is lost.
- L48 _private member_ `FVRNotificationsDelegate HMDReconnectedDelegate;` — `UPROPERTY(BlueprintAssignable)` — This will be called when connection to HMD is restored.
- L52 _private member_ `FVRNotificationsDelegate HMDConnectCanceledDelegate;` — `UPROPERTY(BlueprintAssignable)` — This will be called when the user declines to connect the HMD when prompted to do so by a system dialog. (PS4 Only)
- L56 _private member_ `FVRNotificationsDelegate HMDPutOnHeadDelegate;` — `UPROPERTY(BlueprintAssignable)` — This will be called when the HMD detects that it has been put on by a player.
- L60 _private member_ `FVRNotificationsDelegate HMDRemovedFromHeadDelegate;` — `UPROPERTY(BlueprintAssignable)` — This will be called when the HMD detects that it has been taken off by a player (disconnecting the hmd also causes it to register as taken off).
- L64 _private member_ `FVRNotificationsDelegate VRControllerRecenteredDelegate;` — `UPROPERTY(BlueprintAssignable)` — This will be called when the VR system recenters a controller.
- L68 _private member_ `FVRNotificationsDelegate XRTrackingOriginChangedDelegate;` — `UPROPERTY(BlueprintAssignable)` — This will be called whenever the tracking origin is altered.
- L72 _private member_ `FVRNotificationsDelegate XRPlayAreaChangedDelegate;` — `UPROPERTY(BlueprintAssignable)` — This will be called whenever the play area is altered.
- L76 _private member_ `FVRNotificationsDelegate XRInteractionProfileChangedDelegate;` — `UPROPERTY(BlueprintAssignable)` — This will be called whenever the interaction profile is altered.
- L79 _public prototype_ `void OnRegister() override;`
- L80 _public prototype_ `void OnUnregister() override;`
- L84 _private function_ `void HMDRecenteredDelegate_Handler()` — Native handlers that get registered with the actual FCoreDelegates, and then proceed to broadcast to the delegates above
- L85 _private function_ `void HMDLostDelegate_Handler()`
- L86 _private function_ `void HMDReconnectedDelegate_Handler()`
- L87 _private function_ `void HMDConnectCanceledDelegate_Handler()`
- L88 _private function_ `void HMDPutOnHeadDelegate_Handler()`
- L89 _private function_ `void HMDRemovedFromHeadDelegate_Handler()`
- L90 _private function_ `void VRControllerRecentered_Handler()`
- L91 _private function_ `void XRTrackingOriginChanged_Handler(const IXRTrackingSystem* TrackingSys)`
- L92 _private function_ `void XRPlayAreaChanged_Handler()`
- L93 _private function_ `void XRInteractionProfileChanged_Handler()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API XRBASE_API`
- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVRNotificationsDelegate);`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRAssetFunctionLibrary.h` (Public)


#### class `UXRAssetFunctionLibrary`  
`class UXRAssetFunctionLibrary : public UBlueprintFunctionLibrary`  
_L20-59_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L40 _public prototype_ `static UPrimitiveComponent* AddDeviceVisualizationComponentBlocking(AActor* Target, const FXRDeviceId& XRDeviceId, bool bManualAttachment, const FTransform& RelativeTransform);` — `UFUNCTION(BlueprintCallable, Category = "XR|Devices", meta = (DefaultToSelf = "Target"))` — Spawns a render component for the specified XR device. NOTE: The associated XR system backend has to provide a model for this to work - if one is not available for the specific device, then this will fail and return an invalid (null) object. @param  Target				The intended owner for the component to attach to. @param  XRDeviceId			Specifies the device you're wanting a model for. @param  bManualAttachment	If set, will leave the component unattached (mirror's the same option on the generic AddComponent node). When unset the component will attach to the actor's root. @param  RelativeTransform	Specifies the component initial transform (relative to its attach parent). @return A new component representing the specified device (invalid/null if a model for the device doesn't exist).
- L58 _public prototype_ `static UPrimitiveComponent* AddNamedDeviceVisualizationComponentBlocking(AActor* Target, const FName SystemName, const FName DeviceName, bool bManualAttachment, const FTransform& RelativeTransform, FXRDeviceId& XRDeviceId);` — `UFUNCTION(BlueprintCallable, Category = "XR|Devices", meta = (DefaultToSelf = "Target"))` — Spawns a render component for the specified XR device. NOTE: The associated XR system backend has to provide a model for this to work - if one is not available for the specific device, then this will fail and return an invalid (null) object. @param  Target				The intended owner for the component to attach to. @param  SystemName			(optional) Targets a specific XR system (i.e. 'Oculus', 'OpenXR', etc.). If left as 'None', then the first system found that can render the device will be used. @param  DeviceName			Source name of the specific device - expect the same names that the MotionControllerComponent's "MotionSource" field uses ('Left', 'Right', etc.). @param  bManualAttachment	If set, will leave the component unattached (mirror's the same option on the generic AddComponent node). When unset the component will attach to the actor's root. @param  RelativeTransform	Specifies the component initial transform (relative to its attach parent). @return A new component representing the specified device (invalid/null if a model for the device doesn't exist).

#### class `UAsyncTask_LoadXRDeviceVisComponent`  
`class UAsyncTask_LoadXRDeviceVisComponent : public UBlueprintAsyncActionBase`  
_L67-102_
- reflection: `UCLASS()`
- inherits: `UBlueprintAsyncActionBase`
- L74 _public prototype_ `static UAsyncTask_LoadXRDeviceVisComponent* AddNamedDeviceVisualizationComponentAsync(AActor* Target, const FName SystemName, const FName DeviceName, bool bManualAttachment, const FTransform& RelativeTransform, FXRDeviceId& XRDeviceId, UPrimitiveComponent*& NewComponent);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", DefaultToSelf = "Target"), Category = "XR|Devices")`
- L77 _public prototype_ `static UAsyncTask_LoadXRDeviceVisComponent* AddDeviceVisualizationComponentAsync(AActor* Target, const FXRDeviceId& XRDeviceId, bool bManualAttachment, const FTransform& RelativeTransform, UPrimitiveComponent*& NewComponent);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", DefaultToSelf = "Target"), Category = "XR|Devices")`
- L80 _public member_ `FDeviceModelLoadedDelegate OnModelLoaded;` — `UPROPERTY(BlueprintAssignable)`
- L83 _public member_ `FDeviceModelLoadedDelegate OnLoadFailure;` — `UPROPERTY(BlueprintAssignable)`
- L87 _public prototype_ `virtual void Activate() override;`
- L90 _private prototype_ `void OnLoadComplete(bool bSuccess);`
- L98 _private member_ `ELoadStatus LoadStatus = ELoadStatus::Pending;`
- L101 _private member_ `TObjectPtr<UPrimitiveComponent> SpawnedComponent;` — `UPROPERTY()`

#### enum `UAsyncTask_LoadXRDeviceVisComponent::ELoadStatus`  
`enum class ELoadStatus : uint8`  
_L92-97_
- L94 _public enumerator_ `Pending`
- L95 _public enumerator_ `LoadSuccess`
- L96 _public enumerator_ `LoadFailure`

#### Free symbols / members of external scopes

- L64 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeviceModelLoadedDelegate, const UPrimitiveComponent*, LoadedComponent);`
- L64 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeviceModelLoadedDelegate, const UPrimitiveComponent*, LoadedComponent);`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRCopyTexture.h` (Public)


#### enum `EXRCopyTextureBlendModifier`  
`enum class EXRCopyTextureBlendModifier : uint8`  
_L12-25_
- L15 _public enumerator_ `Opaque` — Copy RGB, clear alpha to 1.0
- L18 _public enumerator_ `TransparentAlphaPassthrough` — Copy RGBA values, overwriting target
- L21 _public enumerator_ `PremultipliedAlphaBlend` — Composite onto target with premultiplied alpha blend factors
- L24 _public enumerator_ `InvertAlpha` — Copy RGB and invert A, overwriting target

#### struct `FXRCopyTextureOptions`  
`struct FXRCopyTextureOptions`  
_L27-60_
- L29 _public member_ `FStaticFeatureLevel FeatureLevel;`
- L30 _public member_ `FStaticShaderPlatform ShaderPlatform;`
- L31 _public member_ `ERenderTargetLoadAction LoadAction = ERenderTargetLoadAction::ELoad;`
- L32 _public member_ `EXRCopyTextureBlendModifier BlendMod = EXRCopyTextureBlendModifier::Opaque;`
- L33 _public member_ `bool bClearBlack = false;`
- L40 _public member_ `bool bOutputMipChain = false;` — If this is set and the dst has mips, those mips will be filled in by the copy. If the source texture has mips, the copy will be repeated for each mip level of the dest texture. If the source texture does not have mips, FGenerateMips will be used on the dest texture after copying.
- L42 _public member_ `bool bNeedsDisplayMapping = false;`
- L43 _public member_ `bool bSrcIsLinear = false;`
- L44 _public member_ `bool bSrcSupportsHDR = false;`
- L45 _public member_ `bool bDstSupportsHDR = false;`
- L46 _public member_ `EDisplayColorGamut SrcColorGamut = EDisplayColorGamut::sRGB_D65;`
- L47 _public member_ `EDisplayColorGamut DstColorGamut = EDisplayColorGamut::sRGB_D65;`
- L48 _public member_ `EDisplayOutputFormat SrcDisplayFormat = EDisplayOutputFormat::SDR_ExplicitGammaMapping;`
- L49 _public member_ `EDisplayOutputFormat DstDisplayFormat = EDisplayOutputFormat::SDR_ExplicitGammaMapping;`
- L51 _public function_ `FXRCopyTextureOptions(FStaticFeatureLevel InFeatureLevel) : FeatureLevel(InFeatureLevel) , ShaderPlatform(GetFeatureLevelShaderPlatform(InFeatureLevel))`
- L55 _public function_ `FXRCopyTextureOptions(FStaticFeatureLevel InFeatureLevel, FStaticShaderPlatform InShaderPlatform) : FeatureLevel(InFeatureLevel) , ShaderPlatform(InShaderPlatform)`
- L59 _public prototype_ `void SetDisplayMappingOptions(class IStereoRenderTargetManager* HDRManager);`

#### Free symbols / members of external scopes

- L62 _prototype_ `void AddXRCopyTexturePass(FRDGBuilder& GraphBuilder, FRDGEventName&& Name, FRDGTextureRef SrcTexture, FIntRect SrcRect, FRDGTextureRef DstTexture, FIntRect DstRect, const FXRCopyTextureOptions& Options);`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRDeviceVisualizationComponent.h` (Public)


#### class `UXRDeviceVisualizationComponent`  
`class UXRDeviceVisualizationComponent : public UStaticMeshComponent`  
_L18-88_
- reflection: `UCLASS(MinimalAPI, Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = MotionController)`
- inherits: `UStaticMeshComponent`
- L24 _private member_ `bool bIsVisualizationActive;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetIsVisualizationActive, Category = "Visualization")` — Whether the visualization offered by this component is being used.
- L27 _private prototype_ `void SetIsVisualizationActive(bool bNewVisualizationState);` — `UFUNCTION(BlueprintSetter)`
- L31 _private member_ `FName DisplayModelSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDisplayModelSource, Category = "Visualization")` — Determines the source of the desired model. By default, the active XR system(s) will be queried and (if available) will provide a model for the associated device. NOTE: this may fail if there's no default model; use 'Custom' to specify your own.
- L33 _private member_ `static FName CustomModelSourceId;`
- L35 _private prototype_ `void SetDisplayModelSource(const FName NewDisplayModelSource);` — `UFUNCTION(BlueprintSetter)`
- L39 _private member_ `TObjectPtr<UStaticMesh> CustomDisplayMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetCustomDisplayMesh, Category = "Visualization")` — A mesh override that'll be displayed attached to this MotionController.
- L42 _private prototype_ `void SetCustomDisplayMesh(UStaticMesh* NewDisplayMesh);` — `UFUNCTION(BlueprintSetter)`
- L46 _private member_ `TArray<TObjectPtr<UMaterialInterface>> DisplayMeshMaterialOverrides;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visualization")` — Material overrides for the specified display mesh.
- L49 _private prototype_ `void OnDisplayModelLoaded(UPrimitiveComponent* DisplayComponent);` — Callback for asynchronous display model loads (to set materials, etc.)
- L52 _private member_ `bool bIsRenderingActive;` — Set by the parent MotionController once tracking kicks in.
- L55 _private prototype_ `bool CanDeviceBeDisplayed();` — Whether this component can be displayed, depending on whether the parent MotionController has activated its rendering.
- L57 _private member_ `FName MotionSource;`
- L66 _private member_ `EModelLoadStatus DisplayModelLoadState = EModelLoadStatus::Unloaded;`
- L68 _private member_ `FXRDeviceId DisplayDeviceId;`
- L70 _private prototype_ `void RefreshMesh();`
- L71 _private prototype_ `UMotionControllerComponent* FindParentMotionController();`
- L72 _private prototype_ `void SetMaterials(int32 MatCount);`
- L73 _private prototype_ `void OnRegister() override;`
- L74 _private prototype_ `void OnUnregister() override;`
- L76 _private prototype_ `void OnCloseVREditor();`
- L82 _public prototype_ `void SetIsRenderingActive(bool bRenderingIsActive);` — `UFUNCTION(BlueprintSetter, Category="MotionController")`
- L85 _private prototype_ `void OnInteractionProfileChanged();`
- L87 _private member_ `bool bInteractionProfilePresent = false;`

#### enum `UXRDeviceVisualizationComponent::EModelLoadStatus`  
`enum class EModelLoadStatus : uint8`  
_L59-65_
- L61 _public enumerator_ `Unloaded`
- L62 _public enumerator_ `Pending`
- L63 _public enumerator_ `InProgress`
- L64 _public enumerator_ `Complete`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API XRBASE_API`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRLoadingScreenBase.h` (Public)


#### class `TXRLoadingScreenBase`  
`template<typename SplashType> class TXRLoadingScreenBase : public IXRLoadingScreen, protected FTickableGameObject`  
_L14-134_
- inherits: `IXRLoadingScreen,FTickableGameObject`
- desc: Base utility class for implementations of the IXRLoadingScreen interface
- L18 _public function_ `TXRLoadingScreenBase(class IXRTrackingSystem* InTrackingSystem) : TrackingSystem(InTrackingSystem) , HMDOrientation(FQuat::Identity) , bShowing(false) , SystemDisplayInterval(1 / 90.0f) , LastTimeInSeconds(FPlatformTime::Seconds())`
- L29 _public function_ `virtual void ClearSplashes() override` — IXRLoadingScreen interface
- L41 _public function_ `virtual void AddSplash(const FSplashDesc& Splash) override`
- L47 _public function_ `virtual void ShowLoadingScreen() override`
- L76 _public function_ `virtual void HideLoadingScreen() override`
- L93 _public function_ `virtual bool IsShown() const override`
- L94 _public prototype_ `virtual bool IsPlayingLoadingMovie() const = 0;`
- L100 _protected function_ `virtual void Tick(float DeltaTime) override` — FTickableGameObject interface
- L115 _protected function_ `virtual TStatId GetStatId() const override`
- L116 _protected function_ `virtual ETickableTickType GetTickableTickType() const override`
- L117 _protected function_ `virtual bool IsTickableWhenPaused() const override`
- L118 _protected function_ `virtual bool IsTickableInEditor() const override`
- L120 _protected prototype_ `virtual void DoShowSplash(SplashType& Splash) = 0;`
- L121 _protected prototype_ `virtual void DoHideSplash(SplashType& Splash) = 0;`
- L122 _protected prototype_ `virtual void DoDeleteSplash(SplashType& Splash) = 0;`
- L123 _protected prototype_ `virtual void DoAddSplash(SplashType& Splash) = 0;`
- L124 _protected prototype_ `virtual void ApplyDeltaRotation(const SplashType& Splash) = 0;`
- L126 _protected member_ `TArray<SplashType> Splashes;`
- L128 _protected member_ `class IXRTrackingSystem* TrackingSystem;`
- L129 _protected member_ `FQuat HMDOrientation;`
- L130 _protected member_ `bool bShowing;`
- L132 _protected member_ `float SystemDisplayInterval;`
- L133 _protected member_ `double LastTimeInSeconds;`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRLoadingScreenFunctionLibrary.h` (Public)


#### class `UXRLoadingScreenFunctionLibrary`  
`class UXRLoadingScreenFunctionLibrary : public UBlueprintFunctionLibrary`  
_L20-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: XR Loading Screen Function Library
- L34 _private prototype_ `static void SetLoadingScreen(class UTexture* Texture, FVector2D Scale = FVector2D(1.0f, 1.0f), FVector Offset = FVector::ZeroVector, bool bShowLoadingMovie = false, bool bShowOnSet = false);` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay|LoadingScreen")` — Sets the loading screen texture for VR displays. @param Texture			(in) A texture asset to be used for the loading screen. @param Scale				(in) Scale of the loading screen texture quad. @param Offset			(in) Offset of the loading screen texture quad relative to the tracking space origin, in meters. @param bShowLoadingMovie	(in) If true, support animated texture assets, such as media textures. @param bShowOnSet		(in) If true, immediately show the loading screen after it's set.
- L37 _private prototype_ `static void ClearLoadingScreenSplashes();` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay|LoadingScreen")`
- L50 _private prototype_ `static void AddLoadingScreenSplash(class UTexture* Texture, FVector Translation, FRotator Rotation, FVector2D Size = FVector2D(1.0f, 1.0f), FRotator DeltaRotation = FRotator::ZeroRotator, bool bClearBeforeAdd = false);` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay|LoadingScreen")` — Adds a splash element to the loading screen. @param Texture			(in) A texture asset to be used for the splash. @param Translation       (in) Initial translation of the center of the splash. @param Rotation			(in) Initial rotation of the splash screen, with the origin at the center of the splash. @param Size      		(in) Size, of the quad with the splash screen. @param DeltaRotation		(in) Incremental rotation, that is added each 2nd frame to the quad transform. The quad is rotated around the center of the quad. @param bClearBeforeAdd	(in) If true, clears splashes before adding a new one.
- L56 _private prototype_ `static void ShowLoadingScreen();` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay|LoadingScreen")` — Show the loading screen and override the VR display
- L62 _private prototype_ `static void HideLoadingScreen();` — `UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay|LoadingScreen")` — Hide the splash screen and return to normal display.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API XRBASE_API`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRMotionControllerBase.h` (Public)


#### class `FXRMotionControllerBase`  
`class FXRMotionControllerBase : public IMotionController`  
_L19-37_
- inherits: `IMotionController`
- desc: Base utility class for implementations of the IMotionController interface
- L22 _public prototype_ `virtual ~FXRMotionControllerBase() = default;`
- L29 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, float WorldToMetersScale) const = 0;` — Note: In this class we are providing a default implementation of GetControllerOrientationAndPosition with velocity, etc parameters and GetControllerOrientationAndPositionForTime that never provide that data and require override of the four param version because this is the most common implementation now. Any child class that does support some of the additional params should override all three functions. See the cpp file for some sample implementations of those overrides.
- L30 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const;`
- L31 _public prototype_ `virtual bool GetControllerOrientationAndPositionForTime(const int32 ControllerIndex, const FName MotionSource, FTimespan Time, bool& OutTimeWasUsed, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const;`
- L32 _public prototype_ `virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const FName MotionSource) const = 0;`
- L33 _public prototype_ `virtual void EnumerateSources(TArray<FMotionControllerSource>& SourcesOut) const;`
- L34 _public function_ `virtual float GetCustomParameterValue(const FName MotionSource, FName ParameterName, bool& bValueFound) const`
- L35 _public function_ `virtual bool GetHandJointPosition(const FName MotionSource, int jointIndex, FVector& OutPosition) const override`

#### class `FXRMotionControllerBaseLegacy`  
`class FXRMotionControllerBaseLegacy : public FXRMotionControllerBase`  
_L41-56_
- inherits: `FXRMotionControllerBase`
- desc: This class adapts deprecated or maintenence only xr plugins which use the old EControllerHand motion sources to the newer FName MotionSource API. If a plugin is still in active development it should refactor and derive from IMotionController or FXRMotionControllerBase rather than derive from this class.
- L47 _private prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, float WorldToMetersScale) const override final;` — These are overridden to call into the backward compatibility functions below.  They are final and private because a legacy vr plugin would not use or implement these functions.
- L48 _private prototype_ `virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const FName MotionSource) const override final;`
- L53 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const EControllerHand DeviceHand, FRotator& OutOrientation, FVector& OutPosition, float WorldToMetersScale) const = 0;` — Original GetControllerOrientationAndPosition signature for backwards compatibility.  They are pure virtual because a legacy plugin must implement them and public because a legacy vr plugin could use them internally.
- L55 _public prototype_ `virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const EControllerHand DeviceHand) const = 0;` — Original GetControllerTrackingStatus signature for backwards compatibility

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API XRBASE_API`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRRenderBridge.h` (Public)


#### class `FXRRenderBridge`  
`class FXRRenderBridge : public FRHICustomPresent`  
_L9-23_
- inherits: `FRHICustomPresent`
- L13 _public function_ `FXRRenderBridge()`
- L17 _public function_ `virtual void OnBackBufferResize() override`
- L19 _public function_ `virtual bool NeedsNativePresent() override`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRRenderTargetManager.h` (Public)


#### class `FXRRenderTargetManager`  
`class FXRRenderTargetManager : public IStereoRenderTargetManager`  
_L13-26_
- inherits: `IStereoRenderTargetManager`
- desc: Common IStereoRenderTargetManager implementation that can be used by HMD implementations in order to get default implementations for most methods.
- L20 _public prototype_ `virtual void CalculateRenderTargetSize(const class FViewport& Viewport, uint32& InOutSizeX, uint32& InOutSizeY) override;` — Calculates dimensions of the render target texture for direct rendering of distortion. This implementation calculates the size based on the current value of xr.SecondaryScreenPercentage.HMDRenderTarget.
- L25 _public prototype_ `virtual bool NeedReAllocateViewportRenderTarget(const class FViewport& Viewport) override;` — Returns true, if render target texture must be re-calculated.

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API XRBASE_API`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRShaders.h` (Public)


#### class `FXRCubemapPS`  
`class FXRCubemapPS : public FGlobalShader`  
_L7-39_
- inherits: `FGlobalShader`
- L12 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L14 _public function_ `FXRCubemapPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)`
- L21 _public function_ `FXRCubemapPS()`
- L23 _public function_ `void SetParameters(FRHIBatchedShaderParameters& BatchedParameters, const FTexture* Texture, const FMatrix44f& FaceToSampleMatrix)`
- L29 _public function_ `void SetParameters(FRHIBatchedShaderParameters& BatchedParameters, FRHISamplerState* SamplerStateRHI, FRHITexture* TextureRHI, const FMatrix44f& FaceToSampleMatrix)`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRSwapChain.h` (Public)


#### class `FXRSwapChain`  
`class FXRSwapChain : public TSharedFromThis<FXRSwapChain, ESPMode::ThreadSafe>`  
_L22-53_
- inherits: `TSharedFromThis<FXRSwapChain,ESPMode::ThreadSafe>`
- L25 _public prototype_ `FXRSwapChain(TArray<FTextureRHIRef>&& InRHITextureSwapChain, const FTextureRHIRef& AliasedTexture);`
- L26 _public prototype_ `virtual ~FXRSwapChain() = default;`
- L28 _public function_ `const FTextureRHIRef& GetTextureRef() const`
- L29 _public function_ `FRHITexture* GetTexture() const`
- L30 _public function_ `FRHITexture* GetTexture2D() const`
- L31 _public function_ `FRHITexture* GetTexture2DArray() const`
- L32 _public function_ `FRHITexture* GetTextureCube() const`
- L33 _public function_ `uint32 GetSwapChainLength() const`
- L34 _public function_ `TArray<FTextureRHIRef> GetSwapChain() const`
- L36 _public function_ `uint32 GetSwapChainIndex_RHIThread()`
- L38 _public prototype_ `virtual void IncrementSwapChainIndex_RHIThread();`
- L40 _public function_ `virtual void WaitCurrentImage_RHIThread(int64 TimeoutNanoseconds = 0)` — Default to no timeout (immediate).
- L41 _public function_ `virtual void ReleaseCurrentImage_RHIThread(IRHICommandContext* RHICmdContext)`
- L43 _public function_ `void SetDebugLabel(FStringView NewLabel)`
- L46 _protected prototype_ `virtual void ReleaseResources_RHIThread();`
- L48 _protected member_ `FTextureRHIRef RHITexture;`
- L49 _protected member_ `TArray<FTextureRHIRef> RHITextureSwapChain;`
- L50 _protected member_ `std::atomic_uint32_t SwapChainIndex_RHIThread;`
- L52 _protected member_ `FString DebugLabel;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API XRBASE_API`
- L55 _typedef_ `typedef TSharedPtr<FXRSwapChain, ESPMode::ThreadSafe> FXRSwapChainPtr;`
- L58 _function_ `template<typename T = FXRSwapChain, typename... Types> FXRSwapChainPtr CreateXRSwapChain(TArray<FTextureRHIRef>&& InRHITextureSwapChain, const FTextureRHIRef& InRHIAliasedTexture, Types... InExtraParameters)`

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRThreadUtils.h` (Public)


#### Free symbols / members of external scopes

- L23 _prototype_ `extern void ExecuteOnRenderThread_DoNotWait(const TFunction<void()>& Function);` — `UE_DEPRECATED(5.7, "Do not use this function. Use ENQUEUE_RENDER_COMMAND directly.")` — Utility function for easily submitting TFunction to be run on the render thread. Must be invoked from the game thread. If rendering does not use a separate thread, the TFunction will be executed immediately, otherwise it will be added to the render thread task queue. @param Function - the Function to be invoked on the render thread. @return true if the function was queued, false if rendering does not use a separate thread, in which case, the function has already been executed.
- L32 _prototype_ `extern void ExecuteOnRenderThread_DoNotWait(const TFunction<void(FRHICommandListImmediate&)>& Function);` — `UE_DEPRECATED(5.7, "Do not use this function. Use ENQUEUE_RENDER_COMMAND directly.")` — Utility function for easily submitting TFunction to be run on the render thread. Must be invoked from the game thread. If rendering does not use a separate thread, the TFunction will be executed immediately, otherwise it will be added to the render thread task queue. @param Function - the Function to be invoked on the render thread. When executed, it will get the current FRHICommandList instance passed in as its sole argument. @return true if the function was queued, false if rendering does not use a separate thread, in which case, the function has already been executed.
- L42 _prototype_ `extern void ExecuteOnRenderThread(const TFunctionRef<void()>& Function);` — `UE_DEPRECATED(5.7, "Do not use this function. Use ENQUEUE_RENDER_COMMAND directly, followed by FlushRenderingCommands() if you need to wait for the function to execute. Ideally systems would be refactored to avoid having to flush though.")` — Utility function for easily running a TFunctionRef on the render thread. Must be invoked from the game thread. If rendering does not use a separate thread, the TFunction will be executed immediately, otherwise it will be added to the render thread task queue. This method will flush rendering commands meaning that the function will be executed before ExecuteOnRenderThread returns. @param Function - the Function to be invoked on the render thread. @return true if the function was queued, false if rendering does not use a separate thread, in which case, the function has already been executed.
- L52 _prototype_ `extern void ExecuteOnRenderThread(const TFunctionRef<void(FRHICommandListImmediate&)>& Function);` — `UE_DEPRECATED(5.7, "Do not use this function. Use ENQUEUE_RENDER_COMMAND directly, followed by FlushRenderingCommands() if you need to wait for the function to execute. Ideally systems would be refactored to avoid having to flush though.")` — Utility function for easily running a TFunctionRef on the render thread. Must be invoked from the game thread. If rendering does not use a separate thread, the TFunction will be executed immediately, otherwise it will be added to the render thread task queue. This method will flush rendering commands meaning that the function will be executed before ExecuteOnRenderThread returns. @param Function - the Function to be invoked on the render thread. When executed, it will get the current FRHICommandList instance passed in as its sole argument. @return true if the function was queued, false if rendering does not use a separate thread, in which case, the function has already been executed.
- L61 _prototype_ `extern bool ExecuteOnRHIThread_DoNotWait(const TFunction<void()>& Function);` — `UE_DEPRECATED(5.7, "Do not use this function. Use EnqueueLambda() on an RHI command list. If you're on the rendering thread, this can be done with the immediate RHI command list: FRHICommandListImmediate::Get().EnqueueLambda(...)")` — Utility function for easily submitting TFunction to be run on the RHI thread. Must be invoked from the render thread. If RHI does not run on a separate thread, the TFunction will be executed immediately, otherwise it will be added to the RHI thread command list. @param Function - the Function to be invoked on the RHI thread. @return true if the function was queued, false if RHI does not use a separate thread, or if it's bypassed, in which case, the function has already been executed.
- L70 _prototype_ `extern bool ExecuteOnRHIThread_DoNotWait(const TFunction<void(FRHICommandListImmediate&)>& Function);` — `UE_DEPRECATED(5.7, "Do not use this function. Use EnqueueLambda() on an RHI command list. If you're on the rendering thread, this can be done with the immediate RHI command list: FRHICommandListImmediate::Get().EnqueueLambda(...)")` — Utility function for easily submitting TFunction to be run on the RHI thread. Must be invoked from the render thread. If RHI does not run on a separate thread, the TFunction will be executed immediately, otherwise it will be added to the RHI thread command list. @param Function - the Function to be invoked on the RHI thread. When executed, it will get the current FRHICommandList instance passed in as its sole argument. @return true if the function was queued, false if RHI does not use a separate thread, or if it's bypassed, in which case, the function has already been executed.
- L81 _prototype_ `extern void ExecuteOnRHIThread(const TFunctionRef<void()>& Function);` — `UE_DEPRECATED(5.7, "Do not use this function. Use EnqueueLambda() on an RHI command list, following by an RHI flush. This can be done with the immediate RHI command list: " "FRHICommandListImmediate& RHICmdList = FRHICommandListImmediate::Get(); RHICmdList.EnqueueLambda(...); RHICmdList.ImmediateFlush(EImmediateFlushType::FlushRHIThread); " "Ideally systems would be refactored to avoid having to flush though.")` — Utility function for easily running a TFunctionRef on the RHI thread. Must be invoked from the render thread. If RHI does not run on a separate thread, the TFunction will be executed on the current thread. This method will flush the RHI command list meaning that the function will be executed before ExecuteOnRHIThread returns. @param Function - the Function to be invoked on the RHI thread.
- L92 _prototype_ `extern void ExecuteOnRHIThread(const TFunctionRef<void(FRHICommandListImmediate&)>& Function);` — `UE_DEPRECATED(5.7, "Do not use this function. Use EnqueueLambda() on an RHI command list, following by an RHI flush. This can be done with the immediate RHI command list: " "FRHICommandListImmediate& RHICmdList = FRHICommandListImmediate::Get(); RHICmdList.EnqueueLambda(...); RHICmdList.ImmediateFlush(EImmediateFlushType::FlushRHIThread); " "Ideally systems would be refactored to avoid having to flush though.")` — Utility function for easily running a TFunctionRef on the RHI thread. Must be invoked from the render thread. If RHI does not run on a separate thread, the TFunction will be executed on the current thread. This method will flush the RHI command list meaning that the function will be executed before ExecuteOnRHIThread returns. @param Function - the Function to be invoked on the RHI thread. When executed, it will get the current FRHICommandList instance passed in as its sole argument.

### `Plugins/Runtime/XRBase/Source/XRBase/Public/XRTrackingSystemBase.h` (Public)


#### class `FXRTrackingSystemDelegates`  
`class FXRTrackingSystemDelegates`  
_L11-22_
- L14 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FXRTrackingOriginChanged, const IXRTrackingSystem* );`
- L15 _public member_ `static FXRTrackingOriginChanged OnXRTrackingOriginChanged;`
- L17 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FXRPlayAreaChanged);`
- L18 _public member_ `static FXRPlayAreaChanged OnXRPlayAreaChanged;`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FXRInteractionProfileChanged);`
- L21 _public member_ `static FXRInteractionProfileChanged OnXRInteractionProfileChanged;`

#### class `FXRTrackingSystemBase`  
`class FXRTrackingSystemBase : public IXRTrackingSystem`  
_L28-230_
- inherits: `IXRTrackingSystem`
- desc: Base utility class for implementations of the IXRTrackingSystem interface Contains helpers and default implementation of most abstract methods, so final implementations only need to override features that they support.
- L31 _public prototype_ `FXRTrackingSystemBase(IARSystemSupport* InARImplementation);`
- L32 _public prototype_ `virtual ~FXRTrackingSystemBase();`
- L38 _public function_ `virtual bool DoesSupportPositionalTracking() const override` — Whether or not the system supports positional tracking (either via sensor or other means). The default implementation always returns false, indicating that only rotational tracking is supported.
- L44 _public function_ `virtual bool HasValidTrackingPosition() override` — If the system currently has valid tracking positions. If not supported at all, returns false. Defaults to calling DoesSupportPositionalTracking();
- L54 _public prototype_ `virtual uint32 CountTrackedDevices(EXRTrackedDeviceType Type = EXRTrackedDeviceType::Any) override;` — Get the count of tracked devices. @param Type Optionally limit the count to a certain type @return the count of matching tracked devices. The default implementation calls EnumerateTrackedDevices and returns the number of elements added to the array.
- L63 _public prototype_ `virtual bool IsTracking(int32 DeviceId) override;` — Check current tracking status of a device. @param DeviceId the device to request status for. @return true if the system currently has valid tracking info for the given device ID. The default implementation returns the result of calling GetCurrentPose(DeviceId, ...), ignoring the returned pose.
- L75 _public function_ `virtual bool GetTrackingSensorProperties(int32 DeviceId, FQuat& OutOrientation, FVector& OutPosition, FXRSensorProperties& OutSensorProperties) override` — If the device id represents a tracking sensor, reports the frustum properties in game-world space of the sensor. @param DeviceId the device to request information for. @param OutOrientation The current orientation of the device. @param OutPosition The current position of the device. @param OutSensorProperties A struct containing the tracking sensor properties. @return true if the device tracking is valid and supports returning tracking sensor properties. The default implementation returns false for all device ids.
- L85 _public function_ `virtual EXRTrackedDeviceType GetTrackedDeviceType(int32 DeviceId) const override` — If the device id represents a tracking sensor, reports the device type. @param DeviceId the device to request information for. @return the device type enum.
- L95 _public function_ `virtual FString GetTrackedDevicePropertySerialNumber(int32 DeviceId) override` — If the device id represents a tracking sensor, reports the serial number as a string if the device supports it. @param DeviceId the device to request information for. @return the serial number of the device if it's available.
- L107 _public prototype_ `virtual TSharedPtr< class IXRCamera, ESPMode::ThreadSafe > GetXRCamera(int32 DeviceId = HMDDeviceId) override;` — Get the IXCamera instance for the given device. @param DeviceId the device the camera should track. @return a shared pointer to an IXRCamera. The default implementation only supports a single IXRCamera for the HMD Device, returning a FDefaultXRCamera instance.
- L112 _public function_ `virtual FString GetVersionString() const` — Returns version string.
- L114 _public prototype_ `virtual bool GetRelativeEyePose(int32 DeviceId, int32 ViewIndex, FQuat& OutOrientation, FVector& OutPosition) override;`
- L121 _public function_ `virtual void SetTrackingOrigin(EHMDTrackingOrigin::Type NewOrigin) override` — Sets tracking origin (either Local, LocalFloor, or Stage.  CustomOpenXR origins are handled automatically, View tracking origins are not allowed.). The default implementations simply ignores the origin value.
- L128 _public function_ `virtual EHMDTrackingOrigin::Type GetTrackingOrigin() const override` — Returns current tracking origin. The default implementation always reports 'local'-level tracking.
- L136 _public prototype_ `virtual FTransform GetTrackingToWorldTransform() const override;` — Returns the system's latest known tracking-to-world transform.
- L142 _public function_ `virtual bool GetFloorToEyeTrackingTransform(FTransform& OutFloorToEye) const override` — Returns a transform for converting from 'Floor' origin space to 'Eye' origin space. The default implementation always returns the identity.
- L147 _public prototype_ `virtual void UpdateTrackingToWorldTransform(const FTransform& TrackingToWorldOverride) override;` — Refreshes the system's known tracking-to-world transform.
- L158 _public prototype_ `virtual void CalibrateExternalTrackingSource(const FTransform& ExternalTrackingTransform) override;` — Called to calibrate the offset transform between an external tracking source and the internal tracking source (e.g. mocap tracker to and HMD tracker).  This should be called once per session, or when the physical relationship between the external tracker and internal tracker changes (e.g. it was bumped or reattached).  After calibration, calling UpdateExternalTrackingPosition will try to correct the internal tracker to the calibrated offset to prevent drift between the two systems @param ExternalTrackingTransform		The transform in world-coordinates, of the reference marker of the external tracking system
- L168 _public prototype_ `virtual void UpdateExternalTrackingPosition(const FTransform& ExternalTrackingTransform) override;` — Called after calibration to attempt to pull the internal tracker (e.g. HMD tracking) in line with the external tracker (e.g. mocap tracker).  This will set the internal tracker's base offset and rotation to match and realign the two systems. This can be called every tick, or whenever realignment is desired.  Note that this may cause choppy movement if the two systems diverge relative to each other, or a big jump if called infrequently when there has been significant drift @param ExternalTrackingTransform		The transform in world-coordinates, of the reference marker of the external tracking system
- L169 _public prototype_ `virtual class IXRLoadingScreen* GetLoadingScreen() override final;`
- L171 _public prototype_ `virtual void GetMotionControllerState(UObject* WorldContext, const EXRSpaceType XRSpaceType, const EControllerHand Hand, const EXRControllerPoseType XRControllerPoseType, FXRMotionControllerState& MotionControllerState) override;`
- L172 _public prototype_ `virtual void GetHandTrackingState(UObject* WorldContext, const EXRSpaceType XRSpaceType, const EControllerHand Hand, FXRHandTrackingState& HandTrackingState) override;`
- L173 _public prototype_ `virtual bool GetCurrentInteractionProfile(const EControllerHand Hand, FString& InteractionProfile) override;`
- L175 _public prototype_ `TSharedPtr<FARSupportInterface , ESPMode::ThreadSafe> GetARCompositionComponent() override;`
- L176 _public prototype_ `const TSharedPtr<const FARSupportInterface , ESPMode::ThreadSafe> GetARCompositionComponent() const override;`
- L182 _protected prototype_ `virtual class IXRLoadingScreen* CreateLoadingScreen();` — Override this method if you need to customize the IXRLoadingScreen implementation. It will be called from GetLoadingScreen() if LoadingScreen is not valid
- L187 _protected function_ `virtual void OnTrackingOriginChanged()` — Meant to be called by sub-classes whenever the tracking origin is altered.
- L192 _protected function_ `virtual void OnPlayAreaChanged()`
- L200 _protected function_ `virtual void OnInteractionProfileChanged()` — Meant to be called by sub-classes whenever the interaction profile is altered.
- L212 _protected prototype_ `FTransform RefreshTrackingToWorldTransform(FWorldContext& WorldContext);` — Computes the project's tracking-to-world transform based off how the user has set up their camera system (assumes the camera is parented to the XR origin, and in turn uses that transform). Intended to be called from OnStartGameFrame()
- L213 _protected prototype_ `FTransform ComputeTrackingToWorldTransform(FWorldContext& WorldContext) const;`
- L215 _protected member_ `TSharedPtr< class FDefaultXRCamera, ESPMode::ThreadSafe > XRCamera;`
- L217 _protected member_ `FTransform CachedTrackingToWorld;`
- L225 _protected member_ `FTransform CalibratedOffset;` — If the tracker is trying to lock itself to an external tracking source for drift control, this stores the calibrated offset between the external tracking system and the internal tracking system (e.g. a location from a mocap system tracker to the HMD's internal IMU).  UpdateExternalTrackingPostion will attempt to normalize the internal tracking system to match this calibration when called.
- L226 _protected member_ `mutable class IXRLoadingScreen* LoadingScreen;`
- L229 _private member_ `TSharedPtr<FARSupportInterface , ESPMode::ThreadSafe> ARCompositionComponent;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API XRBASE_API`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FXRTrackingOriginChanged, const IXRTrackingSystem* );`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE(FXRPlayAreaChanged);`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE(FXRInteractionProfileChanged);`
