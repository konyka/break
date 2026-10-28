# Runtime / HeadMountedDisplay

- module root: `Source/Runtime/HeadMountedDisplay`
- headers: 18; symbols: 543
- symbol kinds: class=21, delegate=2, enum=13, enumerator=74, function=131, member=111, namespace=5, prototype=170, struct=13, variable=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, EngineSettings, InputCore, RHI, RenderCore, Renderer

### `Source/Runtime/HeadMountedDisplay/Public/HeadMountedDisplay.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/HeadMountedDisplay/Public/HeadMountedDisplayTypes.h` (Public)


#### class `FHMDViewMesh`  
`class FHMDViewMesh`  
_L33-59_
- L43 _public prototype_ `FHMDViewMesh();`
- L44 _public prototype_ `~FHMDViewMesh();`
- L46 _public function_ `bool IsValid() const`
- L51 _public prototype_ `void BuildMesh(const FVector2D Positions[], uint32 VertexCount, EHMDMeshType MeshType);`
- L53 _public member_ `FBufferRHIRef VertexBufferRHI;`
- L54 _public member_ `FBufferRHIRef IndexBufferRHI;`
- L56 _public member_ `unsigned NumVertices;`
- L57 _public member_ `unsigned NumIndices;`
- L58 _public member_ `unsigned NumTriangles;`

#### enum `FHMDViewMesh::EHMDMeshType`  
`enum EHMDMeshType`  
_L37-41_
- L39 _public enumerator_ `MT_HiddenArea`
- L40 _public enumerator_ `MT_VisibleArea`

#### enum `EOrientPositionSelector::Type`  
`enum Type : int`  
_L67-72_
- L69 _public enumerator_ `Orientation UMETA(DisplayName = "Orientation")`
- L70 _public enumerator_ `Position UMETA(DisplayName = "Position")`
- L71 _public enumerator_ `OrientationAndPosition UMETA(DisplayName = "Orientation and Position")`

#### enum `EHMDTrackingOrigin::Type`  
`enum Type : int`  
_L81-88_
- L83 _public enumerator_ `View UMETA(ToolTip = "Previously sometimes used Eye space to query for the view transform, this space is fixed to the HMD, meaning that as the hmd moves this space moves relative to other spaces. This isn't used as a tracking origin.")`
- L84 _public enumerator_ ``
- L85 _public enumerator_ ``
- L86 _public enumerator_ ``
- L87 _public enumerator_ ``

#### enum `EHMDWornState::Type`  
`enum Type : int`  
_L97-102_
- L99 _public enumerator_ `Unknown UMETA(DisplayName = "Unknown")`
- L100 _public enumerator_ `Worn UMETA(DisplayName = "Worn")`
- L101 _public enumerator_ `NotWorn UMETA(DisplayName = "Not Worn")`

#### enum `EXRDeviceConnectionResult::Type`  
`enum Type : int`  
_L112-119_
- L114 _public enumerator_ `NoTrackingSystem`
- L115 _public enumerator_ `FeatureNotSupported`
- L116 _public enumerator_ `NoValidViewport`
- L117 _public enumerator_ `MiscFailure`
- L118 _public enumerator_ `Success`

#### enum `EXRSystemFlags::Type`  
`enum Type : int`  
_L128-135_
- L130 _public enumerator_ `NoFlags = 0x00 UMETA(Hidden)`
- L131 _public enumerator_ `IsAR = 0x01`
- L132 _public enumerator_ `IsTablet = 0x02`
- L133 _public enumerator_ `IsHeadMounted = 0x04`
- L134 _public enumerator_ `SupportsHandTracking = 0x08`

#### enum `ESpectatorScreenMode`  
`enum class ESpectatorScreenMode : uint8`  
_L143-153_
- reflection: `UENUM()`
- desc: The Spectator Screen Mode controls what the non-vr video device displays on platforms that support one. Not all modes are universal. Modes SingleEyeCroppedToFill, Texture, and MirrorPlusTexture are supported on all.
- L145 _public enumerator_ `Disabled UMETA(DisplayName = "Disabled")`
- L146 _public enumerator_ `SingleEyeLetterboxed UMETA(DisplayName = "SingleEyeLetterboxed")`
- L147 _public enumerator_ `Undistorted UMETA(DisplayName = "Undistorted")`
- L148 _public enumerator_ `Distorted UMETA(DisplayName = "Distorted")`
- L149 _public enumerator_ `SingleEye UMETA(DisplayName = "SingleEye")`
- L150 _public enumerator_ `SingleEyeCroppedToFill UMETA(DisplayName = "SingleEyeCroppedToFill")`
- L151 _public enumerator_ `Texture UMETA(DisplayName = "Texture")`
- L152 _public enumerator_ `TexturePlusEye UMETA(DisplayName = "TexturePlusEye")`

#### struct `FSpectatorScreenModeTexturePlusEyeLayout`  
`struct FSpectatorScreenModeTexturePlusEyeLayout`  
_L157-231_
- L159 _public function_ `FSpectatorScreenModeTexturePlusEyeLayout() : EyeRectMin(0.0f, 0.0f) , EyeRectMax(1.0f, 1.0f) , TextureRectMin(0.125f, 0.125f) , TextureRectMax(0.25f, 0.25f) , bDrawEyeFirst(true) , bUseAlpha(false) , bClearBlack(false)`
- L169 _public function_ `FSpectatorScreenModeTexturePlusEyeLayout(FVector2D InEyeRectMin, FVector2D InEyeRectMax, FVector2D InTextureRectMin, FVector2D InTextureRectMax, bool InbDrawEyeFirst, bool InbClearBlack, bool InbUseAlpha) : EyeRectMin(InEyeRectMin) , EyeRectMax(InEyeRectMax) , TextureRectMin(InTextureRectMin) , TextureRectMax(InTextureRectMax) , bDrawEyeFirst(InbDrawEyeFirst) , bUseAlpha(InbUseAlpha) , bClearBlack(InbClearBlack)`
- L179 _public function_ `bool IsValid() const`
- L214 _public function_ `FIntRect GetScaledEyeRect(int SizeX, int SizeY) const`
- L219 _public function_ `FIntRect GetScaledTextureRect(int SizeX, int SizeY) const`
- L224 _public member_ `FVector2D EyeRectMin;`
- L225 _public member_ `FVector2D EyeRectMax;`
- L226 _public member_ `FVector2D TextureRectMin;`
- L227 _public member_ `FVector2D TextureRectMax;`
- L228 _public member_ `bool bDrawEyeFirst;`
- L229 _public member_ `bool bUseAlpha;`
- L230 _public member_ `bool bClearBlack;`

#### enum `EXRTrackedDeviceType`  
`enum class EXRTrackedDeviceType : uint8`  
_L234-250_
- reflection: `UENUM(BlueprintType)`
- L237 _public enumerator_ `HeadMountedDisplay` — Represents a head mounted display
- L239 _public enumerator_ `Controller` — Represents a controller
- L241 _public enumerator_ `TrackingReference` — Represents a static tracking reference device, such as a Lighthouse or tracking camera
- L243 _public enumerator_ `Tracker` — Represents trackers, such as a Vive tracker
- L245 _public enumerator_ `Other` — Misc. device types, for future expansion
- L247 _public enumerator_ `Invalid = (uint8)-2 UMETA(Hidden)` — DeviceId is invalid
- L249 _public enumerator_ `Any = (uint8)-1` — Pass to EnumerateTrackedDevices to get all devices regardless of type

#### enum `EHandKeypoint`  
`enum class EHandKeypoint : uint8`  
_L259-287_
- reflection: `UENUM(BlueprintType)`
- desc: Transforms that are tracked on the hand. Matches the enums from WMR to make it a direct mapping
- L261 _public enumerator_ `Palm`
- L262 _public enumerator_ `Wrist`
- L263 _public enumerator_ `ThumbMetacarpal`
- L264 _public enumerator_ `ThumbProximal`
- L265 _public enumerator_ `ThumbDistal`
- L266 _public enumerator_ `ThumbTip`
- L267 _public enumerator_ `IndexMetacarpal`
- L268 _public enumerator_ `IndexProximal`
- L269 _public enumerator_ `IndexIntermediate`
- L270 _public enumerator_ `IndexDistal`
- L271 _public enumerator_ `IndexTip`
- L272 _public enumerator_ `MiddleMetacarpal`
- L273 _public enumerator_ `MiddleProximal`
- L274 _public enumerator_ `MiddleIntermediate`
- L275 _public enumerator_ `MiddleDistal`
- L276 _public enumerator_ `MiddleTip`
- L277 _public enumerator_ `RingMetacarpal`
- L278 _public enumerator_ `RingProximal`
- L279 _public enumerator_ `RingIntermediate`
- L280 _public enumerator_ `RingDistal`
- L281 _public enumerator_ `RingTip`
- L282 _public enumerator_ `LittleMetacarpal`
- L283 _public enumerator_ `LittleProximal`
- L284 _public enumerator_ `LittleIntermediate`
- L285 _public enumerator_ `LittleDistal`
- L286 _public enumerator_ `LittleTip`

#### class `UHandKeypointConversion`  
`class UHandKeypointConversion : public UBlueprintFunctionLibrary`  
_L292-303_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L299 _public function_ `static int32 Conv_HandKeypointToInt32(EHandKeypoint input)` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (CompactNodeTitle = "->", BlueprintAutocast))` — Interpret a HandKeypoint as an int input, useful for indexing into arrays of hand keypoint data.

#### enum `EXRVisualType`  
`enum class EXRVisualType : uint8`  
_L306-310_
- reflection: `UENUM(BlueprintType)`
- L308 _public enumerator_ `Controller`
- L309 _public enumerator_ `Hand`

#### enum `EXRSpaceType`  
`enum class EXRSpaceType : uint8`  
_L318-324_
- reflection: `UENUM(BlueprintType)`
- desc: Used to get unreal world space or tracking space positions in XR. Working only with unreal world space coordinates is almost always simpler and should be generally preferred. There are specific cases where raw XRTrackingSpace coordinates may be useful, particularly in apps where world scale is not 1:1 or where it changes.
- L321 _public enumerator_ `UnrealWorldSpace` — The unreal coordinate system.  Affected by world scaling and the TrackingToWorldTransform.
- L323 _public enumerator_ `XRTrackingSpace` — The coordinate system the XR Device is tracking itself in.  Should be fixed relative to the real world over short timescales, not affected by world scaling or the TrackingToWorldTransoform.  May change relationship to the physical world through recentering or similar events.

#### enum `EXRControllerPoseType`  
`enum class EXRControllerPoseType : uint8`  
_L330-338_
- reflection: `UENUM(BlueprintType)`
- desc: Controllers, due to their various shapes, might have different natural usages.
- L333 _public enumerator_ `Aim` — A pose meant to represent pointing.
- L335 _public enumerator_ `Grip` — A poose meant to represent holding a stick.
- L337 _public enumerator_ `Palm` — A pose meant to represent holding an item in the palm of the hand.

#### struct `FXRHMDData`  
`struct FXRHMDData`  
_L341-359_
- reflection: `USTRUCT(BlueprintType)`
- L346 _public member_ `bool bValid = false;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L348 _public member_ `FName DeviceName;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L350 _public member_ `FGuid ApplicationInstanceID;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L353 _public member_ `ETrackingStatus TrackingStatus = ETrackingStatus::NotTracked;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L356 _public member_ `FVector Position = FVector(0.0f);` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L358 _public member_ `FQuat Rotation = FQuat(EForceInit::ForceInitToZero);` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`

#### struct `FXRMotionControllerState`  
`struct FXRMotionControllerState`  
_L362-398_
- reflection: `USTRUCT(BlueprintType)`
- L368 _public member_ `bool bValid = false;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")` — The state is valid if a pose has ever been provided.
- L370 _public member_ `FName DeviceName;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L372 _public member_ `FGuid ApplicationInstanceID;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L375 _public member_ `EXRSpaceType XRSpaceType = EXRSpaceType::UnrealWorldSpace;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L378 _public member_ `EControllerHand Hand = EControllerHand::Left;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L382 _public member_ `ETrackingStatus TrackingStatus = ETrackingStatus::NotTracked;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")` — If a controller pose has been provided this frame the TrackingStatus will be Tracked.
- L385 _public member_ `EXRControllerPoseType XRControllerPoseType = EXRControllerPoseType::Grip;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L388 _public member_ `FVector ControllerLocation = FVector(0.0f);` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L391 _public member_ `FQuat ControllerRotation = FQuat(EForceInit::ForceInitToZero);` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L395 _public member_ `FVector GripUnrealSpaceLocation = FVector(0.0f);` — `UPROPERTY()` — These are used by the XRVisualizationFunctionLibrary, and are not exposed to blueprint.
- L397 _public member_ `FQuat GripUnrealSpaceRotation = FQuat(EForceInit::ForceInitToZero);` — `UPROPERTY()`

#### struct `FXRHandTrackingState`  
`struct FXRHandTrackingState`  
_L401-433_
- reflection: `USTRUCT(BlueprintType)`
- L407 _public member_ `bool bValid = false;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")` — The state is valid if poses have ever been provided.
- L409 _public member_ `FName DeviceName;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L411 _public member_ `FGuid ApplicationInstanceID;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L414 _public member_ `EXRSpaceType XRSpaceType = EXRSpaceType::UnrealWorldSpace;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L417 _public member_ `EControllerHand Hand = EControllerHand::Left;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L420 _public member_ `ETrackingStatus TrackingStatus = ETrackingStatus::NotTracked;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")`
- L424 _public member_ `TArray<FVector> HandKeyLocations;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")` — The indices of this array are the values of EHandKeypoint (Palm, Wrist, ThumbMetacarpal, etc).
- L428 _public member_ `TArray<FQuat> HandKeyRotations;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")` — The indices of this array are the values of EHandKeypoint (Palm, Wrist, ThumbMetacarpal, etc).
- L432 _public member_ `TArray<float> HandKeyRadii;` — `UPROPERTY(BlueprintReadOnly, Category = "XR")` — The indices of this array are the values of EHandKeypoint (Palm, Wrist, ThumbMetacarpal, etc).

#### Free symbols / members of external scopes

- L61 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHMD, Log, All);`
- L62 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLoadingSplash, Log, All);`
- L65 _namespace_ `namespace EOrientPositionSelector`
- L79 _namespace_ `namespace EHMDTrackingOrigin`
- L95 _namespace_ `namespace EHMDWornState`
- L110 _namespace_ `namespace EXRDeviceConnectionResult`
- L126 _namespace_ `namespace EXRSystemFlags`
- L154 _variable_ `const uint8 ESpectatorScreenModeFirst = (uint8)ESpectatorScreenMode::Disabled;`
- L155 _variable_ `const uint8 ESpectatorScreenModeLast = (uint8)ESpectatorScreenMode::TexturePlusEye;`
- L289 _variable_ `const int32 EHandKeypointCount = static_cast<int32>(EHandKeypoint::LittleTip) + 1;`

### `Source/Runtime/HeadMountedDisplay/Public/IHandTracker.h` (Public)


#### class `IHandTracker`  
`class IHandTracker : public IModularFeature`  
_L19-61_
- inherits: `IModularFeature`
- L22 _public function_ `static FName GetModularFeatureName()`
- L33 _public prototype_ `virtual FName GetHandTrackerDeviceTypeName() const = 0;` — Returns the device type of the controller. @return	Device type of the controller.
- L41 _public prototype_ `virtual bool IsHandTrackingStateValid() const = 0;` — Returns true if hand tracking is available and tracking. @return			true/false
- L48 _public prototype_ `virtual bool GetKeypointState(EControllerHand Hand, EHandKeypoint Keypoint, FTransform& OutTransform, float& OutRadius) const = 0;` — Get the transform and radius (or 0 if radius is not available on this platform) for the given hand keypoint. @return			true if data was fetched
- L50 _public prototype_ `virtual bool GetAllKeypointStates(EControllerHand Hand, TArray<FVector>& OutPositions, TArray<FQuat>& OutRotations, TArray<float>& OutRadii, bool& OutIsTracked) const = 0;`
- L52 _public function_ `virtual bool HasHandMeshData() const`
- L57 _public function_ `virtual bool GetHandMeshData(EControllerHand Hand, TArray<FVector>& OutVertices, TArray<FVector>& OutNormals, TArray<int32>& OutIndices, FTransform& OutHandMeshTransform) const`

### `Source/Runtime/HeadMountedDisplay/Public/IHeadMountedDisplay.h` (Public)


#### struct `FHeadMountedDisplayPassContext`  
`struct FHeadMountedDisplayPassContext`  
_L22-31_
- L24 _public function_ `FHeadMountedDisplayPassContext(FRHICommandListImmediate& InRHICmdList, const FSceneView& InView) : RHICmdList(InRHICmdList) , View(InView)`
- L29 _public member_ `FRHICommandListImmediate& RHICmdList;`
- L30 _public member_ `const FSceneView& View;`

#### class `IHeadMountedDisplay`  
`class IHeadMountedDisplay : public IModuleInterface`  
_L37-274_
- inherits: `IModuleInterface`
- L41 _public prototype_ `IHeadMountedDisplay();`
- L46 _public prototype_ `virtual bool IsHMDConnected() = 0;` — Returns true if HMD is currently connected.  It may or may not be in use.
- L51 _public prototype_ `virtual bool IsHMDEnabled() const = 0;` — Whether or not switching to stereo is enabled; if it is false, then EnableStereo(true) will do nothing.
- L56 _public function_ `virtual EHMDWornState::Type GetHMDWornState()` — Returns EHMDWornState::Worn if we detect that the user is wearing the HMD, EHMDWornState::NotWorn if we detect the user is not wearing the HMD, and EHMDWornState::Unknown if we cannot detect the state.
- L61 _public prototype_ `virtual void EnableHMD(bool bEnable = true) = 0;` — Enables or disables switching to stereo.
- L66 _public prototype_ `virtual FName GetHMDName() const = 0;` — Retrieves the HMD name.
- L93 _public prototype_ `virtual bool GetHMDMonitorInfo(MonitorInfo&) = 0;` — Get the name or id of the display to output for this HMD.
- L98 _public prototype_ `virtual void GetFieldOfView(float& InOutHFOVInDegrees, float& InOutVFOVInDegrees) const = 0;` — Calculates the FOV, based on the screen dimensions of the device. Original FOV is passed as params.
- L106 _public function_ `virtual void SetClippingPlanes(float NCP, float FCP)` — Sets near and far clipping planes (NCP and FCP) for the HMD. @param NCP				(in) Near clipping plane, in centimeters @param FCP				(in) Far clipping plane, in centimeters
- L111 _public function_ `virtual void GetEyeRenderParams_RenderThread(const struct FHeadMountedDisplayPassContext& Context, FVector2D& EyeToSrcUVScaleValue, FVector2D& EyeToSrcUVOffsetValue) const` — Returns eye render params, used from PostProcessHMD, RenderThread.
- L116 _public prototype_ `virtual void SetInterpupillaryDistance(float NewInterpupillaryDistance) = 0;` — Accessors to modify the interpupillary distance (meters)
- L117 _public prototype_ `virtual float GetInterpupillaryDistance() const = 0;`
- L122 _public prototype_ `virtual bool GetHMDDistortionEnabled(EShadingPath ShadingPath) const = 0;` — Whether HMDDistortion post processing is enabled or not
- L125 _public function_ `virtual bool IsSpectatorScreenActive() const` — Are we outputting so a Spectator Screen now.
- L131 _public function_ `virtual class ISpectatorScreenController* GetSpectatorScreenController()` — Return a pointer to the SpectatorScreenController for the HMD if supported, else null. The controller is owned by the HMD, and will be destroyed when the HMD is destroyed.
- L132 _public function_ `virtual class ISpectatorScreenController const* GetSpectatorScreenController() const`
- L137 _public function_ `virtual void CreateHMDPostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const struct FHMDDistortionInputs& Inputs, struct FScreenPassTexture& OutPass) const` — When implemented, creates a new post process node to provide platform-specific HMD distortion.
- L144 _public function_ `virtual float GetPixelDenity() const` — Gets the current pixel density setting.
- L149 _public function_ `virtual void SetPixelDensity(const float NewDensity)` — Sets the pixel density. This may cause render target resizing.
- L154 _public function_ `virtual FIntPoint GetIdealRenderTargetSize() const` — Gets the ideal render target size for the device. See xr.SecondaryScreenPercentage.HMDRenderTarget description.
- L159 _public function_ `virtual FIntPoint GetIdealDebugCanvasRenderTargetSize() const` — Gets the ideal render target size for the debug canvas on the device.
- L164 _public function_ `virtual float GetDistortionScalingFactor() const` — Gets the scaling factor, applied to the post process warping effect
- L169 _public function_ `virtual float GetLensCenterOffset() const` — Gets the offset (in clip coordinates) from the center of the screen for the lens position
- L174 _public function_ `virtual void GetDistortionWarpValues(FVector4& K) const` — Gets the barrel distortion shader warp values for the device
- L179 _public prototype_ `virtual bool IsChromaAbCorrectionEnabled() const = 0;` — Returns 'false' if chromatic aberration correction is off.
- L185 _public function_ `virtual bool GetChromaAbCorrectionValues(FVector4& K) const` — Gets the chromatic aberration correction shader values for the device. Returns 'false' if chromatic aberration correction is off.
- L190 _public function_ `virtual bool HasHiddenAreaMesh() const` — @return true if a hidden area mesh is available for the device.
- L195 _public function_ `virtual bool HasVisibleAreaMesh() const` — @return true if a visible area mesh is available for the device.
- L201 _public function_ `virtual void DrawHiddenAreaMesh(class FRHICommandList& RHICmdList, int32 ViewIndex) const` — Optional method to draw a view's hidden area mesh where supported. This can be used to avoid rendering pixels which are not included as input into the final distortion pass.
- L208 _public function_ `virtual void DrawHiddenAreaMesh(class FRHICommandList& RHICmdList, int32 ViewIndex, int32 InstanceCount) const` — Optional method to draw a view's hidden area mesh where supported. This can be used to avoid rendering pixels which are not included as input into the final distortion pass. Supports instanced rendering.
- L214 _public function_ `virtual void DrawVisibleAreaMesh(class FRHICommandList& RHICmdList, int32 ViewIndex) const` — Optional method to draw a view's visible area mesh where supported. This can be used instead of a full screen quad to avoid rendering pixels which are not included as input into the final distortion pass.
- L221 _public function_ `virtual void DrawVisibleAreaMesh(class FRHICommandList& RHICmdList, int32 ViewIndex, int32 InstanceCount) const` — Optional method to draw a view's visible area mesh where supported. This can be used instead of a full screen quad to avoid rendering pixels which are not included as input into the final distortion pass. Supports instanced rendering.
- L223 _public function_ `virtual void DrawDistortionMesh_RenderThread(struct FHeadMountedDisplayPassContext& Context, const FIntPoint& TextureSize)`
- L230 _public function_ `virtual void UpdateScreenSettings(const class FViewport* InViewport)` — This method is able to change screen settings right before any drawing occurs. It is called at the beginning of UGameViewportClient::Draw() method. We might remove this one as UpdatePostProcessSettings should be able to capture all needed cases
- L236 _public function_ `virtual FTexture* GetDistortionTextureLeft() const` — Additional optional distortion rendering parameters @todo:  Once we can move shaders into plugins, remove these!
- L237 _public function_ `virtual FTexture* GetDistortionTextureRight() const`
- L238 _public function_ `virtual FVector2D GetTextureOffsetLeft() const`
- L239 _public function_ `virtual FVector2D GetTextureOffsetRight() const`
- L240 _public function_ `virtual FVector2D GetTextureScaleLeft() const`
- L241 _public function_ `virtual FVector2D GetTextureScaleRight() const`
- L242 _public function_ `virtual const float* GetRedDistortionParameters() const`
- L243 _public function_ `virtual const float* GetGreenDistortionParameters() const`
- L244 _public function_ `virtual const float* GetBlueDistortionParameters() const`
- L246 _public function_ `virtual bool NeedsUpscalePostProcessPass()`
- L251 _public function_ `virtual void RecordAnalytics()` — Record analytics
- L258 _public prototype_ `virtual bool DoesAppUseVRFocus() const;` — Returns true, if the App is using VR focus. This means that the app may handle lifecycle events differently from the regular desktop apps. In this case, FCoreDelegates::ApplicationWillEnterBackgroundDelegate and FCoreDelegates::ApplicationHasEnteredForegroundDelegate reflect the state of VR focus (either the app should be rendered in HMD or not).
- L263 _public prototype_ `virtual bool DoesAppHaveVRFocus() const;` — Returns true, if the app has VR focus, meaning if it is rendered in the HMD.
- L268 _public function_ `virtual bool IsRenderingPaused() const` — If true, scene rendering should be skipped.
- L273 _public function_ `virtual bool SetColorScaleAndBias(FLinearColor ColorScale, FLinearColor ColorBias)` — Set the multiply and offset colors for composited images in the HMD

#### struct `IHeadMountedDisplay::MonitorInfo`  
`struct MonitorInfo`  
_L68-88_
- L70 _public member_ `FString MonitorName;`
- L71 _public member_ `size_t MonitorId;`
- L72 _public member_ `int DesktopX, DesktopY;`
- L72 _public member_ `int DesktopX, DesktopY;`
- L73 _public member_ `int ResolutionX, ResolutionY;`
- L73 _public member_ `int ResolutionX, ResolutionY;`
- L74 _public member_ `int WindowSizeX, WindowSizeY;`
- L74 _public member_ `int WindowSizeX, WindowSizeY;`
- L75 _public member_ `bool bShouldTestResolution;`
- L77 _public function_ `MonitorInfo() : MonitorId(0) , DesktopX(0) , DesktopY(0) , ResolutionX(0) , ResolutionY(0) , WindowSizeX(0) , WindowSizeY(0) , bShouldTestResolution(false)`

### `Source/Runtime/HeadMountedDisplay/Public/IHeadMountedDisplayModule.h` (Public)


#### class `IHeadMountedDisplayModule`  
`class IHeadMountedDisplayModule : public IModuleInterface, public IModularFeature`  
_L18-162_
- inherits: `IModuleInterface,IModularFeature`
- desc: The public interface of the HeadmountedDisplay Module
- L21 _public function_ `static FName GetModularFeatureName()`
- L28 _public prototype_ `virtual FString GetModuleKeyName() const = 0;` — Returns the key into the HMDPluginPriority section of the config file for this module
- L30 _public function_ `virtual void GetModuleAliases(TArray<FString>& AliasesOut) const` — Returns an array of alternative ini/config names for this module (helpful if the module's name changes, so we can have back-compat)
- L33 _public function_ `float GetModulePriority() const` — Returns the priority of this module from INI file configuration
- L75 _public function_ `static inline IHeadMountedDisplayModule& Get()` — Singleton-like access to IHeadMountedDisplayModule @return Returns reference to the highest priority IHeadMountedDisplayModule module
- L88 _public function_ `static inline bool IsAvailable()` — Checks to see if there exists a module registered as an HMD.  It is only valid to call Get() if IsAvailable() returns true. @return True if there exists a module registered as an HMD.
- L97 _public function_ `virtual void StartupModule() override` — Register module as an HMD on startup.
- L105 _public function_ `virtual bool PreInit()` — Optionally pre-initialize the HMD module.  Return false on failure.
- L110 _public function_ `virtual bool IsHMDConnected()` — Test to see whether HMD is connected.  Used to guide which plug-in to select.
- L120 _public function_ `virtual uint64 GetGraphicsAdapterLuid()` — Get LUID of graphics adapter where the HMD was last connected. @TODO  currently, for mac, GetGraphicsAdapterLuid() is used to return a device index (how the function "GetGraphicsAdapter" used to work), not a ID... eventually we want the HMD module to return the MTLDevice's registryID, but we cannot fully handle that until we drop support for 10.12 NOTE: this is why we  use -1 as a sentinel value representing "no device" (instead of 0, which is used in the LUID case)
- L132 _public function_ `virtual FString GetAudioInputDevice()` — Get name of audio input device where the HMD was last connected
- L137 _public function_ `virtual FString GetAudioOutputDevice()` — Get name of audio output device where the HMD was last connected
- L142 _public function_ `virtual FString GetDeviceSystemName()` — Get XR system name
- L149 _public prototype_ `virtual TSharedPtr< class IXRTrackingSystem, ESPMode::ThreadSafe > CreateTrackingSystem() = 0;` — Attempts to create a new head tracking device interface @return	Interface to the new head tracking device, if we were able to successfully create one
- L155 _public function_ `virtual TSharedPtr< IHeadMountedDisplayVulkanExtensions, ESPMode::ThreadSafe > GetVulkanExtensions()` — Extensions: If the HMD supports the various extensions listed below, it should return a valid pointer to an implementation contained within it.
- L161 _public function_ `virtual bool IsStandaloneStereoOnlyDevice()` — Indicates that the device we're currently running does not support a spectator view. This will only be called once at initialization and should only return a result based for the current device the engine is running on.

#### struct `IHeadMountedDisplayModule::FCompareModulePriority`  
`struct FCompareModulePriority`  
_L62-68_
- desc: Sorting method for which plug-in should be given priority
- L64 _public function_ `bool operator()(IHeadMountedDisplayModule& A, IHeadMountedDisplayModule& B) const`

### `Source/Runtime/HeadMountedDisplay/Public/IHeadMountedDisplayVulkanExtensions.h` (Public)


#### class `IHeadMountedDisplayVulkanExtensions`  
`class IHeadMountedDisplayVulkanExtensions`  
_L12-23_
- desc: Query Vulkan extensions required by the HMD. Knowledge of these extensions is required during Vulkan RHI initialization.
- L15 _public prototype_ `virtual bool GetVulkanInstanceExtensionsRequired(TArray<const ANSICHAR*>& Out) = 0;`
- L16 _public prototype_ `virtual bool GetVulkanDeviceExtensionsRequired(struct VkPhysicalDevice_T *pPhysicalDevice, TArray<const ANSICHAR*>& Out) = 0;`
- L22 _public prototype_ `virtual bool ShouldDisableVulkanVSync() const;` — If true and VK_PRESENT_MODE_MAILBOX_KHR is not available, VK_PRESENT_MODE_IMMEDIATE_KHR will be preferred over VK_PRESENT_MODE_FIFO_KHR when creating the swap chain for the spectator window.

### `Source/Runtime/HeadMountedDisplay/Public/IIdentifiableXRDevice.h` (Public)


#### class `IXRSystemIdentifier`  
`class IXRSystemIdentifier`  
_L13-23_
- L22 _public prototype_ `virtual FName GetSystemName() const = 0;` — Returns a unique identifier that's supposed to represent the third party system that this object is part of (Vive, Oculus, etc.). @return  A name unique to the system which this object belongs to.

#### class `IIdentifiableXRDevice`  
`class IIdentifiableXRDevice : public IXRSystemIdentifier`  
_L36-54_
- inherits: `IXRSystemIdentifier`
- desc: Generic device identifier interface This class is meant to provide a way to identify and distinguish XR devices across various XR systems in a platform-agnostic way. Additionally, it can be used to tie various IModularFeature device interfaces together. For example, if you have separate IXRTrackingSystem and IXRSystemAssets interfaces which both reference the same devices, then this base class gives you a way to communicate between the two.
- L45 _public prototype_ `virtual int32 GetSystemDeviceId() const = 0;` — Returns a unique identifier that can be used to reference this device within the system is belongs to. @return  A numerical identifier, unique to this device (not guaranteed to be unique outside of the system this belongs to).

#### struct `FXRDeviceId`  
`struct FXRDeviceId`  
_L57-84_
- reflection: `USTRUCT(BlueprintType)`
- L62 _public prototype_ `FXRDeviceId();`
- L63 _public prototype_ `FXRDeviceId(IIdentifiableXRDevice* DeviceId);`
- L64 _public prototype_ `FXRDeviceId(IXRSystemIdentifier* OwningSystem, const int32 DeviceId);`
- L66 _public prototype_ `bool IsOwnedBy(IXRSystemIdentifier* XRSystem) const;`
- L67 _public prototype_ `void Clear();`
- L69 _public function_ `bool IsSet() const`
- L76 _public prototype_ `bool operator==(const FXRDeviceId& Rhs) const;`
- L77 _public prototype_ `bool operator==(const IIdentifiableXRDevice* Rhs) const;`
- L81 _public member_ `FName SystemName;` — `UPROPERTY(BlueprintReadOnly, Category="XRDevice")`
- L83 _public member_ `int32 DeviceId;` — `UPROPERTY(BlueprintReadOnly, Category="XRDevice")`

#### Free symbols / members of external scopes

- L48 _function_ `friend uint32 GetTypeHash(const IIdentifiableXRDevice& XRDevice)` — Combines the different aspects of IIdentifiableXRDevice to produce a unique identifier across all XR systems

### `Source/Runtime/HeadMountedDisplay/Public/IMotionController.h` (Public)


#### enum `ETrackingStatus`  
`enum class ETrackingStatus : uint8`  
_L15-20_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `NotTracked`
- L18 _public enumerator_ `InertialOnly` — Note This value of the enum is deprecated and only used by legacy platforms.  Please do not introduce new usages of it.
- L19 _public enumerator_ `Tracked`

#### struct `FMotionControllerSource`  
`struct FMotionControllerSource`  
_L27-37_
- desc: Motion Controller Source Named Motion Controller source. Used for UI display
- L29 _public member_ `FName SourceName;`
- L31 _public member_ `FName EditorCategory;`
- L34 _public function_ `FMotionControllerSource(FName InSourceName = NAME_None) : SourceName(InSourceName)`

#### class `IMotionController`  
`class IMotionController : public IModularFeature`  
_L47-181_
- inherits: `IModularFeature`
- L50 _public prototype_ `virtual ~IMotionController() = default;`
- L52 _public member_ `static inline FName FeatureName = FName("Mot`
- L53 _public function_ `static FName GetModularFeatureName()`
- L63 _public prototype_ `virtual FName GetMotionControllerDeviceTypeName() const = 0;` — Returns the device type of the controller. @return	Device type of the controller.
- L76 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, float WorldToMetersScale) const = 0;` — Returns the calibration-space orientation of the requested controller's hand. @param ControllerIndex	The Unreal controller (player) index of the controller set @param MotionSource		Which source, within the motion controller to get the orientation and position for @param OutOrientation	(out) If tracked, the orientation (in calibrated-space) of the controller in the specified hand @param OutPosition		(out) If tracked, the position (in calibrated-space) of the controller in the specified hand @param WorldToMetersScale The world scaling factor. @return					True if the device requested is valid and tracked, false otherwise
- L95 _public prototype_ `virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const FName MotionSource, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const = 0;` — Returns the calibration-space orientation of the requested controller's hand. @param ControllerIndex	The Unreal controller (player) index of the controller set @param MotionSource		Which source, within the motion controller to get the orientation and position for @param OutOrientation	(out) If tracked, the orientation (in calibrated-space) of the controller in the specified hand @param OutPosition		(out) If tracked, the position (in calibrated-space) of the controller in the specified hand @param OutbProvidedLinearVelocity     (out) True if linear velocity was provided. @param OutLinearVelocity              (out) The Linear velocity of the controller. @param OutbProvidedAngularVelocity    (out) True if angular velocity was provided. @param OutAngularVelocityAsAxisAndLength    (out) The angular velocity of the controller represented as an axis of rotation who's magnitude is the velocity in radians per second.  See UHeadMountedDisplayFunctionLibrary::GetControllerTransformForTime2 for an example of how this can be turned into an FRotator without losing rotation speed beyond 180 degrees/second. @param OutbProvidedLinearAcceleration (out) True if linear acceleration was provided. @param OutLinearAcceleration          (out) The Linear acceleration of the controller. @param WorldToMetersScale The world scaling factor. @return					True if the device requested is valid and tracked, false otherwise
- L117 _public prototype_ `virtual bool GetControllerOrientationAndPositionForTime(const int32 ControllerIndex, const FName MotionSource, FTimespan Time, bool& OutTimeWasUsed, FRotator& OutOrientation, FVector& OutPosition, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale) const = 0;` — Returns the calibration-space orientation of the requested controller's hand at the specified time for potentially improved temporal precision, particularly fetching the controller transform when a button was pressed on a platform that provides sub-frame timing for button presses.  This is only intended to work with times very near the current frame.  In general it should be called immediatly after receiving the button press. On many platforms this functionality is not supported and this function will set OutTimeWasUsed to false and then call GetControllerOrientationAndPosition, ignoring Time. @param ControllerIndex                The Unreal controller (player) index of the controller set @param MotionSource                   Which source, within the motion controller to get the orientation and position for @param Time                           The time at which we would like to query the orientation. @param OutTimeWasUsed                 (out) If true the time was used somehow to give a more temporally relevant orientation.  If false the time was ignored and a cached value returned. @param OutOrientation                 (out) If tracked, the orientation (in calibrated-space) of the controller in the specified hand @param OutPosition                    (out) If tracked, the position (in calibrated-space) of the controller in the specified hand @param OutbProvidedLinearVelocity     (out) True if linear velocity was provided. @param OutLinearVelocity              (out) The Line
- L119 _public function_ `static inline FRotator AngularVelocityAsAxisAndLengthToRotator(const FVector AngularVelocityAsAxisAndLength)`
- L132 _public prototype_ `virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const FName MotionSource) const = 0;` — Returns the tracking status (e.g. not tracked, intertial-only, fully tracked) of the specified controller @return	Tracking status of the specified controller, or ETrackingStatus::NotTracked if the device is not found
- L139 _public prototype_ `virtual void EnumerateSources(TArray<FMotionControllerSource>& SourcesOut) const = 0;` — Called to request the motion sources that this IMotionController provides @param Sources	A motion source enumerator object that IMotionControllers can add source names to
- L150 _public prototype_ `virtual float GetCustomParameterValue(const FName MotionSource, FName ParameterName, bool& bOutValueFound) const = 0;` — Returns a custom names parameter value @param MotionSource		The name of the motion source we want parameters for @param ParameterName		The specific value we are looking for @param bOutValueFound	(out) Whether the parameter could be found @return			The value of the parameter
- L152 _public prototype_ `virtual bool GetHandJointPosition(const FName MotionSource, int jointIndex, FVector& OutPosition) const = 0;`
- L162 _public function_ `virtual bool SetEnhancedInputUserSettings(TObjectPtr<class UEnhancedInputUserSettings> InputSettings = nullptr)` — Add a set of enhanced input user settings to the motion controller. This allows the motion controller to support Enhanced Input actions. @param InputConfig		The path to the enhanced user input settings asset @return			False if the input config can't be attached to the session, true otherwise
- L172 _public function_ `virtual bool AttachInputMappingContexts(const TSet<TObjectPtr<class UInputMappingContext>>& InputMappingContexts)` — Add input mapping contexts to the motion controller. This allows the motion controller to support Enhanced Input actions. @param MappingContexts		The set of input mapping contexts used with motion controllers @return			False if the input mapping contexts can't be attached to the session, true otherwise
- L175 _public member_ `static FName LeftHandSourceId;` — explicit source names
- L176 _public member_ `static FName RightHandSourceId;`
- L177 _public member_ `static FName HMDSourceId;`
- L178 _public member_ `static FName HeadSourceId;` — Note Head and HMD are interchangable.  HMD is the legacy term.
- L180 _public prototype_ `static bool GetHandEnumForSourceName(const FName Source, EControllerHand& OutHand);`

### `Source/Runtime/HeadMountedDisplay/Public/IMotionTrackingSystemManagement.h` (Public)


#### class `IMotionTrackingSystemManagement`  
`class IMotionTrackingSystemManagement : public IModularFeature`  
_L17-86_
- inherits: `IModularFeature`
- L20 _public function_ `static FName GetModularFeatureName()`
- L31 _public prototype_ `virtual void SetIsControllerMotionTrackingEnabledByDefault(bool Enable) = 0;` — Set whether controller tracking is enabled by default or whether controllers must be specifically enabled. @param Enable						(in) True to enable by default.
- L38 _public prototype_ `virtual int32 GetMaximumMotionTrackedControllerCount() const = 0;` — Get the maximum number of controllers that can be tracked. @return (int) number of controllers that can be tracked.
- L45 _public prototype_ `virtual int32 GetMotionTrackingEnabledControllerCount() const = 0;` — Get the number of controllers for which motion tracking is enabled. @return (int) number of controllers tracked now.
- L55 _public prototype_ `virtual bool IsMotionTrackingEnabledForDevice(const int32 ControllerIndex, const EControllerHand DeviceHand) const = 0;` — Returns true if the specified device is supposed to be tracked @param PlayerIndex				(in) The index of the player. @param Hand						(in) The tracked device type. @return (Boolean) true if the specified device is set to be tracked.
- L65 _public prototype_ `virtual bool EnableMotionTrackingOfDevice(const int32 ControllerIndex, const EControllerHand DeviceHand) = 0;` — Enaable tracking of the specified controller, by player index and tracked device type. @param PlayerIndex				(in) The index of the player. @param Hand						(in) The device type. @return (Boolean) true if the specified device is now set to be tracked.  This could fail due to tracking limits, or on invalid input.
- L73 _public prototype_ `virtual void DisableMotionTrackingOfDevice(const int32 ControllerIndex, const EControllerHand DeviceHand) = 0;` — Disable tracking of the specified controller, by player index and tracked device type. @param PlayerIndex				(in) The index of the player. @param Hand						(in) The tracked device type.
- L78 _public prototype_ `virtual void DisableMotionTrackingOfAllControllers() = 0;` — Disable tracking for all controllers.
- L85 _public prototype_ `virtual void DisableMotionTrackingOfControllersForPlayer(int32 PlayerIndex) = 0;` — Disable tracking for all controllers of a certain player. @param PlayerIndex				(in) The index of the player.

### `Source/Runtime/HeadMountedDisplay/Public/ISpectatorScreenController.h` (Public)


#### class `ISpectatorScreenController`  
`class ISpectatorScreenController : public IModularFeature`  
_L19-59_
- inherits: `IModularFeature`
- L22 _public prototype_ `virtual ~ISpectatorScreenController() = default;`
- L24 _public function_ `static FName GetModularFeatureName()`
- L34 _public prototype_ `virtual void SetSpectatorScreenMode(ESpectatorScreenMode Mode) = 0;` — Sets the social screen mode. @param Mode				(in) The social screen Mode.
- L36 _public prototype_ `virtual ESpectatorScreenMode GetSpectatorScreenMode() const = 0;`
- L42 _public prototype_ `virtual void SetSpectatorScreenTexture(UTexture* InTexture) = 0;` — Change the texture displayed on the social screen @param	InTexture: new Texture2D
- L47 _public function_ `virtual UTexture* GetSpectatorScreenTexture() const` — Get the texture that would currently be displayed on the social screen (if in a mode that does that)
- L58 _public prototype_ `virtual void SetSpectatorScreenModeTexturePlusEyeLayout(const FSpectatorScreenModeTexturePlusEyeLayout& Layout) = 0;` — Setup the layout for ESpectatorScreenMode::TexturePlusEye. @param	EyeRectMin: min of screen rectangle the eye will be drawn in.  0-1 normalized. @param	EyeRectMax: max of screen rectangle the eye will be drawn in.  0-1 normalized. @param	TextureRectMin: min of screen rectangle the texture will be drawn in.  0-1 normalized. @param	TextureRectMax: max of screen rectangle the texture will be drawn in.  0-1 normalized. @param	bDrawEyeFirst: if true the eye is drawn before the texture, if false the reverse. @param	bClearBlack: if true the render target will be drawn black before either rect is drawn.

### `Source/Runtime/HeadMountedDisplay/Public/IXRCamera.h` (Public)


#### class `IXRCamera`  
`class IXRCamera : public IIdentifiableXRDevice`  
_L21-70_
- inherits: `IIdentifiableXRDevice`
- desc: Interface used by the camera component to figure out the final position of a motion tracked camera. To reduce duplicated code, implementations should use the FXRCameraBase instead of implementing this interface directly.
- L24 _public function_ `IXRCamera()`
- L29 _public prototype_ `virtual void UseImplicitHMDPosition(bool bInImplicitHMDPosition) = 0;` — Set the view offset mode to assume an implied HMD position
- L34 _public prototype_ `virtual bool GetUseImplicitHMDPosition() const = 0;` — Gets the view offset mode to assume an implied HMD position
- L41 _public prototype_ `virtual void ApplyHMDRotation(APlayerController* PC, FRotator& ViewRotation) = 0;` — Optionally called by APlayerController to apply the orientation of the headset to the PC's rotation. If this is not done then the PC will face differently than the camera, which might be good (depending on the game).
- L46 _public prototype_ `virtual bool UpdatePlayerCamera(FQuat& CurrentOrientation, FVector& CurrentPosition, float DeltaTime) = 0;` — Apply the orientation and position of the headset to the Camera.
- L51 _public prototype_ `virtual void OverrideFOV(float& InOutFOV) = 0;` — Override the Field of View for the player camera component.
- L54 _public prototype_ `virtual void SetupLateUpdate(const FTransform& ParentToWorld, USceneComponent* Component, bool bSkipLateUpdate) = 0;` — Setup state for applying the render thread late update
- L60 _public prototype_ `virtual void CalculateStereoCameraOffset(const int32 ViewIndex, FRotator& ViewRotation, FVector& ViewLocation) = 0;` — Calculates the offset for the camera position, given the specified eye pass, position and rotation. An XR plugin implementing stereo rendering should forward all calls of CalculateStereoViewOffset to this method.
- L69 _public function_ `virtual bool GetPassthroughCameraUVs_RenderThread(TArray<FVector2D>& OutUVs)` — Fetches the UV coordinates of an AR passthrough camera relative to the screen. Takes into account cropping, orientation and difference between camera and screen aspect ratios. Returns false if the UVs are not available or if the feature is not supported or implemented by the current platform. If the result is true, OutUVs will contain the four corner UVs of the passthrough camera rectangle. This method should only be called from the render thread.

### `Source/Runtime/HeadMountedDisplay/Public/IXRLoadingScreen.h` (Public)


#### class `IXRLoadingScreen`  
`class IXRLoadingScreen`  
_L17-98_
- desc: Interface used to register and show loading splash screen layers. A loading screen consists of one or more splash layers shown instead of the current scene during level load. To reduce duplicated code, implementations should use the FXRLoadingScreenBase of FDefaultXRLoadingScreen instead of implementing this interface directly.
- L21 _public prototype_ `virtual ~IXRLoadingScreen() = default;`
- L69 _public prototype_ `virtual void ClearSplashes() = 0;` — Removes all splashes. Use this to replace the existing splashes before calling AddSplash.
- L76 _public prototype_ `virtual void AddSplash(const FSplashDesc& Splash) = 0;` — Registers a splash to be shown while the loading screen is active. @param Splash	The settings for the new splash.
- L82 _public prototype_ `virtual void ShowLoadingScreen() = 0;` — Activates the loading screen. If called while the loading screen is active, this will reinitialize the positions of all splashes according to the current HMD pose.
- L87 _public prototype_ `virtual void HideLoadingScreen() = 0;` — Hides the loading screen.
- L92 _public prototype_ `virtual bool IsShown() const = 0;` — Returns whether the loading screen is currently active or not.
- L97 _public prototype_ `virtual bool IsPlayingLoadingMovie() const = 0;` — Returns whether a loading movie is playing or not.

#### struct `IXRLoadingScreen::FSplashDesc`  
`struct FSplashDesc`  
_L29-64_
- desc: Structure describing the visual appearance of a single loading splash. Splashes are shown in a tracker-relative space with the orientation reset to the direction the player is facing when brought up.
- L31 _public prototype_ `FSplashDesc() = default;`
- L32 _public prototype_ `FSplashDesc(const FSplashDesc&) = default;`
- L33 _public prototype_ `FSplashDesc(FSplashDesc&&) = default;`
- L34 _public prototype_ `FSplashDesc& operator=(const FSplashDesc&) = default;`
- L35 _public prototype_ `FSplashDesc& operator=(FSplashDesc&&) = default;`
- L38 _public member_ `FTransform Transform = FTransform::Identity;` — Transform of the splash relative to the HMD orientation and location at the time of showing the loading screen.
- L40 _public member_ `FVector2D QuadSize = FVector2D(1.0f, 1.0f);` — Size of rendered quad in UE units
- L42 _public member_ `FBox2D UVRect = FBox2D(FVector2D(0.0f, 0.0f), FVector2D(1.0f, 1.0f));` — UVs of the rendered texture
- L45 _public member_ `FQuat DeltaRotation = FQuat::Identity;` — Simple animation. Rotation that will be applied to the splash every other frame.
- L48 _public member_ `bool bIgnoreAlpha = false;` — If set, the splash texture will be rendered opaque regardless of the alpha channel. Not supported by all platforms.
- L51 _public member_ `bool bIsDynamic = false;` — Set to true to tell that the texture is dynamically generated and may update each frame.
- L54 _public member_ `bool bIsExternal = false;` — Set this to true if the assigned texture is an external texture, for instance if using the media framework.
- L58 _public member_ `TWeakObjectPtr<UTexture> TextureObj = nullptr;` — The texture shown. Can be set to a 2D or a Cube texture. (Cube textures may not be supported by all platforms.) Implementations of IXRLoadingScreen will prevent GC of these pointers for any stored splashes.
- L63 _public member_ `TWeakObjectPtr<UTexture> LeftTextureObj = nullptr;` — If set, overrides the texture shown for the left eye. If null, both eyes will show the same texture. Useful for stereo texture cubes. Implementations of IXRLoadingScreen will prevent GC of these pointers for any stored splashes.

### `Source/Runtime/HeadMountedDisplay/Public/IXRSystemAssets.h` (Public)


#### class `IXRSystemAssets`  
`class IXRSystemAssets : public IModularFeature, public IXRSystemIdentifier`  
_L16-78_
- inherits: `IModularFeature,IXRSystemIdentifier`
- L19 _public function_ `static FName GetModularFeatureName()`
- L38 _public prototype_ `virtual bool EnumerateRenderableDevices(TArray<int32>& DeviceListOut) = 0;` — Fills out a device list with unique identifiers that can be used to reference system specific devices. These IDs are intended to be used with certain methods to reference a specific device (like with CreateRenderComponent(), etc.). NOTE: that these IDs are NOT interoperable across XR systems (vive vs. oculus, etc.). Using an ID from one system with another will have undefined results. @param  DeviceListOut	A list of @return True if the DeviceList was successfully updated, otherwise false.
- L58 _public prototype_ `virtual int32 GetDeviceId(EControllerHand ControllerHand) = 0;` — Provides a mapping for MotionControllers, so we can identify the device ID used for a specific hand (which in turn can be used in other functions, like CreateRenderComponent, etc.). NOTE: Some systems will not have an explicit mapping until the device is on and registered. In that case, this function will return an invalid device ID. NOTE: Not all XR systems support every EControllerHand value. If that's the case, then this will return an invalid device ID, though that specific value is undetermined and up to each XRSystem for interpretation. @param  ControllerHand	The UE specific hand identifier you want a system specific device ID for. @return A device ID that is specific to this XRSystem (can only be interpreted by other members belonging to the same IXRSystemIdentifier)
- L77 _public prototype_ `virtual UPrimitiveComponent* CreateRenderComponent(const int32 DeviceId, AActor* Owner, EObjectFlags Flags, const bool bForceSynchronous = false, const FXRComponentLoadComplete& OnLoadComplete = FXRComponentLoadComplete()) = 0;` — Attempts to spawn a renderable component for the specified device. Returns a component that needs to be attached and registered by the caller. NOTE: Resource loads for this component may be asynchronous. The component can be attached and registered immediately, but there may be a delay before it renders properly. To make the operation synchronous use the bForceSynchronous param. @param  DeviceId				Uniquely identifies the XR device you want to render. @param  Owner				The actor which this component will be attached to. @param  Flags				Object creation flags to spawn the component with. @param  bForceSynchronous	Forces the any associated resource loads to complete before returning. @param  OnLoadComplete		Model load callback, useful for when the load is asynchronous - should be triggered for synchronous loads as well. @return A valid component pointer if the method succeeded, otherwise null.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FXRComponentLoadComplete, UPrimitiveComponent*);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FXRComponentLoadComplete, UPrimitiveComponent*);`

### `Source/Runtime/HeadMountedDisplay/Public/IXRTrackingSystem.h` (Public)


#### struct `FXRSensorProperties`  
`struct FXRSensorProperties`  
_L22-39_
- desc: Struct representing the properties of an external tracking sensor.
- L25 _public member_ `float LeftFOV;` — The field of view of the sensor to the left in degrees
- L27 _public member_ `float RightFOV;` — The field of view of the sensor to the right in degrees
- L29 _public member_ `float TopFOV;` — The upwards field of view of the sensor in degrees
- L31 _public member_ `float BottomFOV;` — The downwards field of view of the sensor in degrees
- L33 _public member_ `float NearPlane;` — The near plane of the sensor's effective tracking area
- L35 _public member_ `float FarPlane;` — The far plane of the sensor's effective tracking area
- L38 _public member_ `float CameraDistance;` — The focal distance of the camera. Can be zero if this does not make sense for the type of tracking sensor.

#### class `IXRTrackingSystem`  
`class IXRTrackingSystem : public IModularFeature, public IXRSystemIdentifier`  
_L46-441_
- inherits: `IModularFeature,IXRSystemIdentifier`
- desc: Main access point to an XR tracking system. Use it to enumerate devices and query their poses.
- L49 _public function_ `static FName GetModularFeatureName()`
- L58 _public prototype_ `virtual FString GetVersionString() const = 0;` — Returns version string.
- L63 _public prototype_ `virtual int32 GetXRSystemFlags() const = 0;` — Returns device specific flags.
- L70 _public member_ `static constexpr int32 HMDDeviceId = 0;` — Device id 0 is reserved for an HMD. This should represent the HMD or the first HMD in case multiple HMDs are supported. Other devices can have arbitrary ids defined by each system. If a tracking system does not support tracking HMDs, device ID zero should be treated as invalid.
- L75 _public prototype_ `virtual bool DoesSupportPositionalTracking() const = 0;` — Whether or not the system supports positional tracking (either via sensor or other means)
- L84 _public function_ `virtual bool DoesSupportLateUpdate() const` — Return true if the default camera implementation should query the current pose at the start of the render frame and apply late update. In order to support late update, the plugin should refresh the current pose just before rendering starts. A good point to insert the update is in OnBeginRendering_GameThread or OnBeginRendering_RenderThread. Note that for backwards compatibility with plugins written before 4.19, this method defaults to returning 'true'
- L93 _public function_ `virtual bool DoesSupportLateProjectionUpdate() const` — Return true if the default camera implementation should query the current projection matrix at the start of the render frame and apply late update. In order to support late update, the plugin should refresh the current projection matrix just before rendering starts. A good point to insert the update is in OnBeginRendering_GameThread or OnBeginRendering_RenderThread. Note that late projection update isn't compatible with all XR implementations because of projection matrix fetch restrictions.
- L98 _public prototype_ `virtual bool HasValidTrackingPosition() = 0;` — If the system currently has valid tracking positions. If not supported at all, returns false.
- L106 _public prototype_ `virtual bool EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type = EXRTrackedDeviceType::Any) = 0;` — Reports all devices currently available to the system, optionally limiting the result to a given class of devices. @param OutDevices The device ids of available devices will be appended to this array. @param Type Optionally limit the list of devices to a certain type.
- L113 _public prototype_ `virtual uint32 CountTrackedDevices(EXRTrackedDeviceType Type = EXRTrackedDeviceType::Any) = 0;` — Get the count of tracked devices @param Type Optionally limit the count to a certain type @return the count of matching tracked devices
- L120 _public prototype_ `virtual bool IsTracking(int32 DeviceId) = 0;` — Check current tracking status of a device. @param DeviceId the device to request status for. @return true if the system currently has valid tracking info for the given device ID.
- L132 _public prototype_ `virtual bool GetCurrentPose(int32 DeviceId, FQuat& OutOrientation, FVector& OutPosition) = 0;` — Get the current pose for a device. This method must be callable both on the render thread and the game thread. For devices that don't support positional tracking, OutPosition will be at the base position. @param DeviceId the device to request the pose for. @param OutOrientation The current orientation of the device @param OutPosition The current position of the device @return true if the pose is valid or not.
- L144 _public prototype_ `virtual bool GetRelativeEyePose(int32 DeviceId, int32 ViewIndex, FQuat& OutOrientation, FVector& OutPosition) = 0;` — If the device id represents a head mounted display, fetches the relative position of the given eye relative to the eye. If the device is does not represent a stereoscopic tracked camera, orientation and position should be identity and zero and the return value should be false. @param DeviceId the device to request the eye pose for. @param ViewIndex the view the pose should be requested for, if passing in INDEX_NONE, the method should return a zero offset. @param OutOrientation The orientation of the eye relative to the device orientation. @param OutPosition The position of the eye relative to the tracked device @return true if the pose is valid or not. If the device is not a stereoscopic device, return false.
- L154 _public prototype_ `virtual bool GetTrackingSensorProperties(int32 DeviceId, FQuat& OutOrientation, FVector& OutPosition, FXRSensorProperties& OutSensorProperties) = 0;` — If the device id represents a tracking sensor, reports the frustum properties in game-world space of the sensor. @param DeviceId the device to request information for. @param OutOrientation The current orientation of the device. @param OutPosition The current position of the device. @param OutSensorProperties A struct containing the tracking sensor properties. @return true if the device tracking is valid and supports returning tracking sensor properties.
- L161 _public prototype_ `virtual EXRTrackedDeviceType GetTrackedDeviceType(int32 DeviceId) const = 0;` — If the device id represents a tracking sensor, reports the device type. @param DeviceId the device to request information for. @return the device type enum.
- L168 _public prototype_ `virtual FString GetTrackedDevicePropertySerialNumber(int32 DeviceId) = 0;` — If the device id represents a tracking sensor, reports the serial number as a string if the device supports it. @param DeviceId the device to request information for. @return the serial number of the device if it's available.
- L173 _public prototype_ `virtual void SetTrackingOrigin(EHMDTrackingOrigin::Type NewOrigin) = 0;` — Sets tracking origin (either 'eye'-level or 'floor'-level).
- L178 _public prototype_ `virtual EHMDTrackingOrigin::Type GetTrackingOrigin() const = 0;` — Returns current tracking origin.
- L184 _public prototype_ `virtual FTransform GetTrackingToWorldTransform() const = 0;` — Returns the system's latest known tracking-to-world transform. Useful for translating poses from GetCurrentPose() into unreal world space.
- L191 _public prototype_ `virtual float GetWorldToMetersScale() const = 0;` — This method should return the world to meters scale for the current frame. Should be callable on both the render and the game threads. @return the current world to meter scale.
- L201 _public prototype_ `virtual bool GetFloorToEyeTrackingTransform(FTransform& OutFloorToEye) const = 0;` — Computes a transform to convert from 'Floor' origin space to 'Eye' origin space. Useful when changing between the two different TrackingOrigin spaces. Invert the transform to get the opposite. @param  OutFloorToEye	[out] The returned floor-to-eye transform. @return True if the transform was successfully constructed.
- L208 _public prototype_ `virtual void UpdateTrackingToWorldTransform(const FTransform& TrackingToWorldOverride) = 0;` — Refreshes the system's known tracking-to-world transform. Helpful for clients if they change the world's representation of the XR origin, or if they want to override the system calculated transform - calling this will update the known transform returned by GetTrackingToWorldTransform().
- L215 _public function_ `virtual FVector GetAudioListenerOffset(int32 DeviceId = HMDDeviceId) const` — Get the offset, in device space, of the reported device (screen / eye) position to the center of the head. @return a vector containing the offset coordinates, ZeroVector if not supported.
- L223 _public prototype_ `virtual void ResetOrientationAndPosition(float Yaw = 0.f) = 0;` — Resets orientation by setting roll and pitch to 0, assuming that current yaw is forward direction and assuming current position as a 'zero-point' (for positional tracking). @param Yaw				(in) the desired yaw to be set after orientation reset.
- L230 _public function_ `virtual void ResetOrientation(float Yaw = 0.f)` — Resets orientation by setting roll and pitch to 0, assuming that current yaw is forward direction. Position is not changed. @param Yaw				(in) the desired yaw to be set after orientation reset.
- L235 _public function_ `virtual void ResetPosition()` — Resets position, assuming current position as a 'zero-point'.
- L243 _public function_ `virtual void SetBaseRotation(const FRotator& BaseRot)` — Sets base orientation by setting yaw, pitch, roll, assuming that this is forward direction. Position is not changed. @param BaseRot			(in) the desired orientation to be treated as a base orientation.
- L248 _public function_ `virtual FRotator GetBaseRotation() const` — Returns current base orientation of HMD as yaw-pitch-roll combination.
- L256 _public function_ `virtual void SetBaseOrientation(const FQuat& BaseOrient)` — Sets base orientation, assuming that this is forward direction. Position is not changed. @param BaseOrient		(in) the desired orientation to be treated as a base orientation.
- L261 _public function_ `virtual FQuat GetBaseOrientation() const` — Returns current base orientation of HMD as a quaternion.
- L268 _public function_ `virtual void SetBasePosition(const FVector& BasePosition)` — Sets base position of the HMD. @param BasePosition		(in) the desired offset to be treated as a base position.
- L273 _public function_ `virtual FVector GetBasePosition() const` — Returns current base position of HMD.
- L284 _public function_ `virtual void CalibrateExternalTrackingSource(const FTransform& ExternalTrackingTransform)` — Called to calibrate the offset transform between an external tracking source and the internal tracking source (e.g. mocap tracker to and HMD tracker).  This should be called once per session, or when the physical relationship between the external tracker and internal tracker changes (e.g. it was bumped or reattached).  After calibration, calling UpdateExternalTrackingPosition will try to correct the internal tracker to the calibrated offset to prevent drift between the two systems @param ExternalTrackingTransform		(in) The transform in world-coordinates, of the reference marker of the external tracking system
- L294 _public function_ `virtual void UpdateExternalTrackingPosition(const FTransform& ExternalTrackingTransform)` — Called after calibration to attempt to pull the internal tracker (e.g. HMD tracking) in line with the external tracker (e.g. mocap tracker).  This will set the internal tracker's base offset and rotation to match and realign the two systems. This can be called every tick, or whenever realignment is desired.  Note that this may cause choppy movement if the two systems diverge relative to each other, or a big jump if called infrequently when there has been significant drift @param ExternalTrackingTransform		(in) The transform in world-coordinates, of the reference marker of the external tracking system
- L302 _public prototype_ `virtual class TSharedPtr< class IXRCamera, ESPMode::ThreadSafe > GetXRCamera(int32 DeviceId = HMDDeviceId) = 0;` — Get the IXCamera instance for the given device. @param DeviceId the device the camera should track. @return a shared pointer to an IXRCamera.
- L309 _public function_ `virtual class IHeadMountedDisplay* GetHMDDevice()` — Access HMD rendering-related features. @return a IHeadmountedDisplay pointer or a nullptr if this tracking system does not support head mounted displays.
- L317 _public function_ `virtual class TSharedPtr< class IStereoRendering, ESPMode::ThreadSafe > GetStereoRenderingDevice()` — Access Stereo rendering device associated with this XR system. If GetHMDDevice() returns non-null, this method should also return a vaild instance. @return a IStereoRendering pointer or a nullptr if this tracking system does not support stereo rendering.
- L327 _public function_ `virtual TSharedPtr<FARSupportInterface, ESPMode::ThreadSafe> GetARCompositionComponent()` — Access optionsal ARCompositionComponent
- L328 _public function_ `virtual const TSharedPtr<const FARSupportInterface, ESPMode::ThreadSafe> GetARCompositionComponent() const`
- L336 _public function_ `virtual class IXRLoadingScreen* GetLoadingScreen()` — Access the loading screen interface associated with this tracking system, if any. @return an IXRLoadingScreen pointer or a nullptr if this tracking system does not support loading screens.
- L344 _public prototype_ `virtual bool IsHeadTrackingAllowed() const = 0;` — Returns true, if head tracking is allowed. Most common case: it returns true when GEngine->IsStereoscopic3D() is true, but some overrides are possible.
- L349 _public prototype_ `virtual bool IsHeadTrackingAllowedForWorld(UWorld & World) const;` — Same as IsHeadTrackingAllowed, but returns false if the World is not using VR (such as with the non-VR PIE instances when using VR Preview)
- L356 _public function_ `virtual bool IsHeadTrackingEnforced() const` — Can be used to enforce tracking even when stereo rendering is disabled. The default implementation does not allow enforcing tracking and always returns false. This method is called both from the game and render threads.
- L362 _public function_ `virtual void SetHeadTrackingEnforced(bool bEnabled)` — Can be used to enforce tracking even when stereo rendering is disabled. The default implementation does not allow enforcing tracking and ignores the argument.
- L368 _public function_ `virtual void OnBeginPlay(FWorldContext& InWorldContext)` — This method is called when playing begins. Useful to reset all runtime values stored in the plugin.
- L373 _public function_ `virtual void OnEndPlay(FWorldContext& InWorldContext)` — This method is called when playing ends. Useful to reset all runtime values stored in the plugin.
- L378 _public function_ `virtual bool OnStartGameFrame(FWorldContext& WorldContext)` — This method is called when new game frame begins (called on a game thread).
- L383 _public function_ `virtual bool OnEndGameFrame(FWorldContext& WorldContext)` — This method is called when game frame ends (called on a game thread).
- L392 _public prototype_ `virtual void OnBeginRendering_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& ViewFamily);` — Called just before rendering the current frame on the render thread. Invoked before applying late update, so plugins that want to refresh poses on the render thread prior to late update. Use this to perform any initializations prior to rendering.
- L397 _public function_ `virtual void OnBeginRendering_GameThread(FSceneViewFamily& InViewFamily)` — Called just before rendering the current frame on the game frame.
- L402 _public prototype_ `virtual void OnLateUpdateApplied_RenderThread(FRDGBuilder& GraphBuilder, const FTransform& NewRelativeTransform);` — Called just after the late update on the render thread passing back the current relative transform.
- L407 _public prototype_ `virtual void GetHMDData(UObject* WorldContext, FXRHMDData& HMDData);` — Platform Agnostic Query about HMD details
- L412 _public prototype_ `virtual void GetMotionControllerState(UObject* WorldContext, const EXRSpaceType XRSpaceType, const EControllerHand Hand, const EXRControllerPoseType XRControllerPoseType, FXRMotionControllerState& MotionControllerState) = 0;` — Platform Agnostic Query about MotionControllers details
- L413 _public prototype_ `virtual void GetHandTrackingState(UObject* WorldContext, const EXRSpaceType XRSpaceType, const EControllerHand Hand, FXRHandTrackingState& HandTrackingState) = 0;`
- L414 _public prototype_ `virtual bool GetCurrentInteractionProfile(const EControllerHand Hand, FString& InteractionProfile) = 0;`
- L416 _public function_ `virtual EXRDeviceConnectionResult::Type ConnectRemoteXRDevice(const FString& IpAddress, const int32 BitRate)`
- L420 _public function_ `virtual void DisconnectRemoteXRDevice()`
- L425 _public function_ `virtual FVector2D GetPlayAreaBounds(EHMDTrackingOrigin::Type Origin) const` — Get the bounds of the area where the user can freely move while remaining tracked centered around the specified origin
- L430 _public function_ `virtual bool GetTrackingOriginTransform(TEnumAsByte<EHMDTrackingOrigin::Type> Origin, FTransform& OutTransform) const` — Get the transform of the specified tracking origin, if available.
- L435 _public function_ `virtual bool GetPlayAreaRect(FTransform& OutTransform, FVector2D& OutRect) const` — Get the transform and dimensions of the area where the user can freely move while remaining tracked centered around the specified origin transform
- L440 _public function_ `virtual IOpenXRHMD* GetIOpenXRHMD()` — Get the IOpenXRHMD interface, if there is one.

### `Source/Runtime/HeadMountedDisplay/Public/LateUpdateManager.h` (Public)


#### class `FLateUpdateManager`  
`class FLateUpdateManager`  
_L13-52_
- desc: Utility class for applying an offset to a hierarchy of components in the renderer thread.
- L16 _public function_ `FLateUpdateManager()`
- L17 _public prototype_ `virtual ~FLateUpdateManager() = default;`
- L20 _public prototype_ `void Setup(const FTransform& ParentToWorld, USceneComponent* Component, bool bSkipLateUpdate);` — Setup state for applying the render thread late update
- L23 _public function_ `bool GetSkipLateUpdate_RenderThread() const` — Returns true if the LateUpdateSetup data is stale.
- L26 _public prototype_ `void Apply_RenderThread(FSceneInterface* Scene, const FTransform& OldRelativeTransform, const FTransform& NewRelativeTransform);` — Apply the late update delta to the cached components
- L31 _private prototype_ `void GatherLateUpdatePrimitives(USceneComponent* ParentComponent);` — A utility method that calls CacheSceneInfo on ParentComponent and all of its descendants
- L33 _private prototype_ `void CacheSceneInfo(USceneComponent* Component);` — Generates a LateUpdatePrimitiveInfo for the given component if it has a SceneProxy and appends it to the current LateUpdatePrimitives array
- L50 _private member_ `FLateUpdateState PipelinedUpdateStatesGame;`
- L51 _private member_ `FLateUpdateState PipelinedUpdateStatesRendering;`

#### struct `FLateUpdateManager::FLateUpdateState`  
`struct FLateUpdateState`  
_L35-48_
- L37 _public function_ `FLateUpdateState() : ParentToWorld(FTransform::Identity) , bSkip(false)`
- L43 _public member_ `FTransform ParentToWorld;` — Parent world transform used to reconstruct new world transforms for late update scene proxies
- L45 _public member_ `TMap<FPrimitiveSceneInfo*, int32> Primitives;` — Primitives that need late update before rendering
- L47 _public member_ `bool bSkip;` — Late Update Info Stale, if this is found true do not late update

### `Source/Runtime/HeadMountedDisplay/Public/MotionControllerComponent.h` (Public)


#### class `UMotionControllerComponent`  
`class UMotionControllerComponent : public UPrimitiveComponent`  
_L18-161_
- reflection: `UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = MotionController, MinimalAPI)`
- inherits: `UPrimitiveComponent`
- L24 _private member_ `int32 PlayerIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetAssociatedPlayerIndex, Category = "MotionController")` — Which player index this motion controller should automatically follow
- L28 _private member_ `FName MotionSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTrackingMotionSource, Category = "MotionController")` — Defines which pose this component should receive from the OpenXR Runtime. Left/Right MotionSource is the same as LeftGrip/RightGrip. See OpenXR specification for details on poses.
- L32 _private member_ `uint32 bDisableLowLatencyUpdate : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotionController")` — If false, render transforms within the motion controller hierarchy will be updated a second time immediately before rendering.
- L36 _private member_ `ETrackingStatus CurrentTrackingStatus;` — `UPROPERTY(BlueprintReadOnly, Category = "MotionController")` — The tracking status for the device (e.g. full tracking, inertial tracking only, no tracking)
- L40 _private function_ `bool IsTracked() const` — `UFUNCTION(BlueprintPure, Category = "MotionController")` — Whether or not this component had a valid tracked device this frame
- L46 _private prototype_ `void SetTrackingSource(const EControllerHand NewSource);` — `UFUNCTION(BlueprintSetter, meta = (DeprecatedFunction, DeprecationMessage = "Please use the Motion Source property instead of Hand"))`
- L49 _private prototype_ `EControllerHand GetTrackingSource() const;` — `UFUNCTION(BlueprintGetter, meta = (DeprecatedFunction, DeprecationMessage = "Please use the Motion Source property instead of Hand"))`
- L52 _private prototype_ `void SetTrackingMotionSource(const FName NewSource);` — `UFUNCTION(BlueprintSetter)`
- L54 _private prototype_ `FName GetTrackingMotionSource();`
- L57 _private prototype_ `void SetAssociatedPlayerIndex(const int32 NewPlayer);` — `UFUNCTION(BlueprintSetter)`
- L59 _private prototype_ `void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L60 _private prototype_ `void BeginDestroy() override;`
- L64 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L67 _public prototype_ `virtual void InitializeComponent() override;`
- L70 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FActivateVisualizationComponent, bool);` — Delegate for activation of XRDeviceVisualizationComponent
- L71 _public member_ `static FActivateVisualizationComponent OnActivateVisualizationComponent;`
- L75 _protected prototype_ `virtual void CreateRenderState_Concurrent(FRegisterComponentContext* Context) override;`
- L76 _protected prototype_ `virtual void SendRenderTransform_Concurrent() override;`
- L80 _protected member_ `IMotionController* InUseMotionController;` — Cached Motion Controller that can be read by GetParameterValue. Only valid for the duration of OnMotionControllerUpdated
- L84 _protected prototype_ `void OnMotionControllerUpdated();` — `UFUNCTION(BlueprintImplementableEvent, Category = "Motion Controller Update")` — Blueprint Implementable function for responding to updated data from a motion controller (so we can use custom parameter values from it)
- L88 _protected prototype_ `float GetParameterValue(FName InName, bool& bValueFound);` — `UFUNCTION(BlueprintCallable, Category = "Motion Controller Update")` — Returns the value of a custom parameter on the current in use Motion Controller (see member InUseMotionController). Only valid for the duration of OnMotionControllerUpdated
- L91 _protected prototype_ `FVector GetHandJointPosition(int jointIndex, bool& bValueFound);` — `UFUNCTION(BlueprintCallable, Category = "Motion Controller Update")`
- L95 _protected prototype_ `bool GetLinearVelocity(FVector &OutLinearVelocity) const;` — `UFUNCTION(BlueprintPure, Category = "Motion Controller Update")` — If the motion tracking system provides linear velocity at this time the vector will be that velocity in cm/s in unreal world space and the function will return true.  If velocity is unavailable it will return false.
- L99 _protected prototype_ `bool GetAngularVelocity(FRotator& OutAngularVelocity) const;` — `UFUNCTION(BlueprintPure, Category = "Motion Controller Update")` — If the motion tracking system provides angular velocity at this time OutAngularVelocity will be that velocity in deg/s in unreal world space and the function will return true. Note that it is not difficult to rotate a controller at more than 0.5 or 1 rotation per second briefly and some mathmatical operations(such as conversion to quaternion) lose rotations beyond 180 degrees or 360 degrees..  In some cases that is OK becuase the resulting final rotation is the same, but in some cases it would generate incorrect results.   If angular velocity is unavailable it will return false.
- L103 _protected prototype_ `bool GetLinearAcceleration(FVector& OutLinearAcceleration) const;` — `UFUNCTION(BlueprintPure, Category = "Motion Controller Update")` — If the motion tracking system provides linear acceleration at this time the vector will be that acceleration in cm/(s^2) in unreal world space and the function will return true.  If acceleration is unavailable it will return false.
- L109 _protected member_ `bool bTracked;` — Whether or not this component had a valid tracked controller associated with it this frame
- L112 _protected member_ `bool bHasAuthority;` — Whether or not this component has authority within the frame
- L115 _protected member_ `bool bProvidedLinearVelocity;` — Velocity and acceleration data for the motion controller, if available.
- L116 _protected member_ `bool bProvidedAngularVelocity;`
- L117 _protected member_ `bool bProvidedLinearAcceleration;`
- L121 _protected member_ `FVector LinearVelocity;` — Note: these values are in tracking space, which is also the space relative to the parent of the motioncontroller component, and still need to be converted to unreal space by the TrackingToWorldTransform for use. They are in the unreal coordinate system and world scaled. Also we do not late-update these values.
- L122 _protected member_ `FVector AngularVelocityAsAxisAndLength;` — This vector represents an axis of rotation and its length is the magnitude of the rotation in radians per second.  Be careful turning it into a quaternion because those cannot represent more than 0.5 revolution per second. See UHeadMountedDisplayFunctionLibrary::GetControllerTransformForTime2 for an
- L123 _protected member_ `FVector LinearAcceleration;`
- L126 _protected prototype_ `bool PollControllerState_GameThread(FVector& Position, FRotator& Orientation, bool& OutbProvidedLinearVelocity, FVector& OutLinearVelocity, bool& OutbProvidedAngularVelocity, FVector& OutAngularVelocityAsAxisAndLength, bool& OutbProvidedLinearAcceleration, FVector& OutLinearAcceleration, float WorldToMetersScale);` — If true, the Position and Orientation args will contain the most recent controller state
- L127 _protected prototype_ `bool PollControllerState_RenderThread(FVector& Position, FRotator& Orientation, float WorldToMetersScale);`
- L129 _protected prototype_ `void OnModularFeatureUnregistered(const FName& Type, class IModularFeature* ModularFeature);`
- L130 _protected member_ `IMotionController* PolledMotionController_GameThread;`
- L131 _protected member_ `IMotionController* PolledMotionController_RenderThread;`
- L132 _protected member_ `bool bPolledHMD_GameThread;`
- L133 _protected member_ `bool bPolledHMD_RenderThread;`
- L134 _protected member_ `FCriticalSection PolledMotionControllerMutex;` — Used to protect PolledMotionController_GameThread and bPolledHMD_GameThread which are written on the game thread and copied on the render thread.
- L137 _protected member_ `FTransform RenderThreadRelativeTransform;`
- L138 _protected member_ `FVector RenderThreadComponentScale;`
- L160 _protected member_ `TSharedPtr< FViewExtension, ESPMode::ThreadSafe > ViewExtension;`

#### class `UMotionControllerComponent::FViewExtension`  
`class FViewExtension : public FSceneViewExtensionBase`  
_L141-159_
- inherits: `FSceneViewExtensionBase`
- desc: View extension object that can persist on the render thread without the motion controller component
- L144 _public prototype_ `FViewExtension(const FAutoRegister& AutoRegister, UMotionControllerComponent* InMotionControllerComponent);`
- L145 _public prototype_ `virtual ~FViewExtension() = default;`
- L148 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;` — ISceneViewExtension interface
- L149 _public prototype_ `virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L150 _public function_ `virtual int32 GetPriority() const override`
- L151 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const;`
- L157 _protected member_ `UMotionControllerComponent* MotionControllerComponent;` — Motion controller component associated with this view extension
- L158 _protected member_ `FLateUpdateManager LateUpdate;`

#### Free symbols / members of external scopes

- L70 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FActivateVisualizationComponent, bool);` — Delegate for activation of XRDeviceVisualizationComponent

### `Source/Runtime/HeadMountedDisplay/Public/MotionDelayBuffer.h` (Public)


#### class `FMotionDelayService`  
`class FMotionDelayService`  
_L22-28_
- L25 _public prototype_ `static void SetEnabled(bool bEnable);`
- L26 _public prototype_ `static bool RegisterDelayTarget(USceneComponent* MotionControlledComponent, const int32 PlayerIndex, const FName SourceId);`
- L27 _public prototype_ `static void RegisterDelayClient(TSharedRef<FMotionDelayClient, ESPMode::ThreadSafe> DelayClient);`

#### class `FMotionDelayClient`  
`class FMotionDelayClient : public FSceneViewExtensionBase`  
_L33-62_
- inherits: `FSceneViewExtensionBase`
- L36 _public prototype_ `FMotionDelayClient(const FAutoRegister& AutoRegister);`
- L38 _public prototype_ `virtual uint32 GetDesiredDelay() const = 0;`
- L39 _public function_ `virtual void GetExemptTargets(TArray<USceneComponent*>& ExemptTargets) const`
- L41 _public prototype_ `void Apply_RenderThread(FSceneInterface* Scene);`
- L42 _public prototype_ `void Restore_RenderThread(FSceneInterface* Scene);`
- L46 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;` — ISceneViewExtension interface
- L47 _public prototype_ `virtual void PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L48 _public prototype_ `virtual int32 GetPriority() const override;`
- L49 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L52 _protected prototype_ `bool FindDelayTransform(USceneComponent* Target, uint32 Delay, FTransform& TransformOut);`
- L61 _private member_ `TArray<FTargetTransform> TargetTransforms_RenderThread;`

#### struct `FMotionDelayClient::FTargetTransform`  
`struct FTargetTransform`  
_L55-60_
- L57 _public member_ `TSharedPtr<FMotionDelayTarget, ESPMode::ThreadSafe> DelayTarget;`
- L58 _public member_ `FTransform DelayTransform;`
- L59 _public member_ `FTransform RestoreTransform;`

#### class `TCircularHistoryBuffer`  
`template<typename ElementType> class TCircularHistoryBuffer`  
_L72-115_
- desc: Modeled after TCircularBuffer/Queue, but resizable with it's own stack-style way of indexing (0 = most recent value added)
- L75 _public prototype_ `TCircularHistoryBuffer(uint32 InitialCapacity = 0);`
- L77 _public prototype_ `ElementType& Add(const ElementType& Element);`
- L78 _public prototype_ `void Resize(uint32 NewCapacity);`
- L86 _public prototype_ `ElementType& operator[](uint32 Index);` — NOTE: Will clamp to the oldest value available if the buffer isn't full and the index is larger than the number of values buffered. @param  Index	Stack-esque indexing: 0 => the most recent value added, 1+n => Older entries, 1+n back from the newest.
- L87 _public prototype_ `const ElementType& operator[](uint32 Index) const;`
- L89 _public prototype_ `void InsertAt(uint32 Index, const ElementType& Element);`
- L91 _public prototype_ `uint32 Capacity() const;`
- L92 _public prototype_ `int32 Num() const;`
- L94 _public prototype_ `void Empty();`
- L96 _public prototype_ `bool IsEmpty() const;`
- L97 _public prototype_ `bool IsFull() const;`
- L100 _private prototype_ `void RangeCheck(const uint32 Index, bool bCheckIfUnderfilled = false) const;`
- L101 _private prototype_ `uint32 AsInternalIndex(uint32 Index) const;`
- L102 _private prototype_ `uint32 GetNextIndex(uint32 CurrentIndex) const;`
- L104 _private prototype_ `void ResizeGrow(uint32 AddedSlack);`
- L105 _private prototype_ `void Realign();`
- L106 _private prototype_ `void ResizeShrink(uint32 ShrinkAmount);`
- L110 _private member_ `TArray<ElementType> Elements;` — Holds the buffer's elements.
- L112 _private member_ `uint32 Head;` — Index to the next slot to be filled. NOTE: The last element added is at Head-1.
- L114 _private member_ `bool bIsFull;` — Allows us to recognize the difference between an empty buffer and one where Head has looped back to the start.

### `Source/Runtime/HeadMountedDisplay/Public/MotionDelayBuffer.inl` (Public)


#### Free symbols / members of external scopes

- L5 _function_ `template<typename ElementType> TCircularHistoryBuffer<ElementType>::TCircularHistoryBuffer(uint32 InitialCapacity) : Head(0) , bIsFull(false)` (scope `TCircularHistoryBuffer`)
- L16 _function_ `template<typename ElementType> ElementType& TCircularHistoryBuffer<ElementType>::Add(const ElementType& Element)` (scope `TCircularHistoryBuffer`)
- L28 _function_ `template<typename ElementType> void TCircularHistoryBuffer<ElementType>::Resize(uint32 NewCapacity)` (scope `TCircularHistoryBuffer`)
- L44 _function_ `template<typename ElementType> inline ElementType& TCircularHistoryBuffer<ElementType>::operator[](uint32 Index)` (scope `TCircularHistoryBuffer`)
- L51 _function_ `template<typename ElementType> inline const ElementType& TCircularHistoryBuffer<ElementType>::operator[](uint32 Index) const` (scope `TCircularHistoryBuffer`)
- L58 _function_ `template<typename ElementType> void TCircularHistoryBuffer<ElementType>::InsertAt(uint32 Index, const ElementType& Element)` (scope `TCircularHistoryBuffer`)
- L96 _function_ `template<typename ElementType> inline uint32 TCircularHistoryBuffer<ElementType>::Capacity() const` (scope `TCircularHistoryBuffer`)
- L102 _function_ `template<typename ElementType> inline int32 TCircularHistoryBuffer<ElementType>::Num() const` (scope `TCircularHistoryBuffer`)
- L115 _function_ `template<typename ElementType> inline void TCircularHistoryBuffer<ElementType>::Empty()` (scope `TCircularHistoryBuffer`)
- L122 _function_ `template<typename ElementType> inline bool TCircularHistoryBuffer<ElementType>::IsEmpty() const` (scope `TCircularHistoryBuffer`)
- L128 _function_ `template<typename ElementType> inline bool TCircularHistoryBuffer<ElementType>::IsFull() const` (scope `TCircularHistoryBuffer`)
- L134 _function_ `template<typename ElementType> inline void TCircularHistoryBuffer<ElementType>::RangeCheck(const uint32 Index, bool bCheckIfUnderfilled) const` (scope `TCircularHistoryBuffer`)
- L142 _function_ `template<typename ElementType> inline uint32 TCircularHistoryBuffer<ElementType>::AsInternalIndex(uint32 Index) const` (scope `TCircularHistoryBuffer`)
- L151 _function_ `template<typename ElementType> inline uint32 TCircularHistoryBuffer<ElementType>::GetNextIndex(uint32 CurrentIndex) const` (scope `TCircularHistoryBuffer`)
- L157 _function_ `template<typename ElementType> void TCircularHistoryBuffer<ElementType>::ResizeGrow(uint32 AddedSlack)` (scope `TCircularHistoryBuffer`)
- L173 _function_ `template<typename ElementType> void TCircularHistoryBuffer<ElementType>::Realign()` (scope `TCircularHistoryBuffer`)
- L200 _function_ `template<typename ElementType> void TCircularHistoryBuffer<ElementType>::ResizeShrink(uint32 ShrinkAmount)` (scope `TCircularHistoryBuffer`)
