# Plugins / SimpleHMD

- module root: `Plugins/Experimental/SimpleHMD/Source/SimpleHMD`
- headers: 2; symbols: 45
- symbol kinds: class=2, function=7, member=6, prototype=30
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, HeadMountedDisplay, InputCore, RHI, RenderCore, Renderer, XRBase

### `Plugins/Experimental/SimpleHMD/Source/SimpleHMD/Private/SimpleHMD.h` (Private)


#### class `FSimpleHMD`  
`class FSimpleHMD : public FHeadMountedDisplayBase, public FHMDSceneViewExtension`  
_L16-106_
- inherits: `FHeadMountedDisplayBase,FHMDSceneViewExtension`
- desc: Simple Head Mounted Display
- L20 _public function_ `virtual FName GetSystemName() const override` — IXRTrackingSystem interface
- L26 _public function_ `int32 GetXRSystemFlags() const`
- L31 _public prototype_ `virtual bool EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type = EXRTrackedDeviceType::Any) override;`
- L33 _public prototype_ `virtual void SetInterpupillaryDistance(float NewInterpupillaryDistance) override;`
- L34 _public prototype_ `virtual float GetInterpupillaryDistance() const override;`
- L36 _public prototype_ `virtual void ResetOrientationAndPosition(float yaw = 0.f) override;`
- L37 _public prototype_ `virtual void ResetOrientation(float Yaw = 0.f) override;`
- L38 _public prototype_ `virtual void ResetPosition() override;`
- L40 _public prototype_ `virtual bool GetCurrentPose(int32 DeviceId, FQuat& CurrentOrientation, FVector& CurrentPosition) override;`
- L41 _public prototype_ `virtual void SetBaseRotation(const FRotator& BaseRot) override;`
- L42 _public prototype_ `virtual FRotator GetBaseRotation() const override;`
- L44 _public prototype_ `virtual void SetBaseOrientation(const FQuat& BaseOrient) override;`
- L45 _public prototype_ `virtual FQuat GetBaseOrientation() const override;`
- L47 _public function_ `virtual class IHeadMountedDisplay* GetHMDDevice() override`
- L52 _public function_ `virtual class TSharedPtr< class IStereoRendering, ESPMode::ThreadSafe > GetStereoRenderingDevice() override`
- L59 _protected prototype_ `virtual float GetWorldToMetersScale() const override;` — FXRTrackingSystemBase protected interface
- L63 _public function_ `virtual bool IsHMDConnected() override` — IHeadMountedDisplay interface
- L64 _public prototype_ `virtual bool IsHMDEnabled() const override;`
- L65 _public prototype_ `virtual void EnableHMD(bool allow = true) override;`
- L66 _public prototype_ `virtual bool GetHMDMonitorInfo(MonitorInfo&) override;`
- L67 _public prototype_ `virtual void GetFieldOfView(float& OutHFOVInDegrees, float& OutVFOVInDegrees) const override;`
- L68 _public prototype_ `virtual bool IsChromaAbCorrectionEnabled() const override;`
- L69 _public prototype_ `virtual void DrawDistortionMesh_RenderThread(struct FHeadMountedDisplayPassContext& Context, const FIntPoint& TextureSize) override;`
- L72 _public prototype_ `virtual bool IsStereoEnabled() const override;` — IStereoRendering interface
- L73 _public prototype_ `virtual bool EnableStereo(bool stereo = true) override;`
- L74 _public prototype_ `virtual void AdjustViewRect(int32 ViewIndex, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;`
- L75 _public prototype_ `virtual void CalculateStereoViewOffset(const int32 ViewIndex, FRotator& ViewRotation, const float InWorldToMeters, FVector& ViewLocation) override;`
- L77 _public prototype_ `virtual FMatrix GetStereoProjectionMatrix(const int32 ViewIndex) const override;`
- L78 _public prototype_ `virtual void GetEyeRenderParams_RenderThread(const struct FHeadMountedDisplayPassContext& Context, FVector2D& EyeToSrcUVScaleValue, FVector2D& EyeToSrcUVOffsetValue) const override;`
- L81 _public prototype_ `virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;` — ISceneViewExtension interface
- L82 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L86 _public prototype_ `FSimpleHMD(const FAutoRegister&);` — Constructor
- L89 _public prototype_ `virtual ~FSimpleHMD();` — Destructor
- L92 _public prototype_ `bool IsInitialized() const;` — @return	True if the HMD was initialized OK
- L96 _private member_ `FQuat CurHmdOrientation;`
- L97 _private member_ `FQuat LastHmdOrientation;`
- L99 _private member_ `FRotator DeltaControlRotation;` — same as DeltaControlOrientation but as rotator
- L100 _private member_ `FQuat DeltaControlOrientation;` — same as DeltaControlRotation but as quat
- L102 _private member_ `double LastSensorTime;`
- L103 _private member_ `float WorldToMeters;`
- L105 _private prototype_ `void GetHMDOrientation(FQuat& CurrentOrientation);`

### `Plugins/Experimental/SimpleHMD/Source/SimpleHMD/Public/ISimpleHMDPlugin.h` (Public)


#### class `ISimpleHMDPlugin`  
`class ISimpleHMDPlugin : public IHeadMountedDisplayModule`  
_L13-38_
- inherits: `IHeadMountedDisplayModule`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L24 _public function_ `static inline ISimpleHMDPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
