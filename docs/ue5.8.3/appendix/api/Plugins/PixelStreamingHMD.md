# Plugins / PixelStreamingHMD

- module root: `Plugins/Media/PixelStreaming/Source/PixelStreamingHMD`
- headers: 5; symbols: 99
- symbol kinds: class=3, delegate=1, enum=1, enumerator=3, externvar=9, function=22, member=22, namespace=5, prototype=33
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, HeadMountedDisplay, InputCore, RHI, RenderCore, Renderer, SlateCore, XRBase

### `Plugins/Media/PixelStreaming/Source/PixelStreamingHMD/Private/PixelStreamingHMDModule.h` (Private)


#### class `UE::PixelStreamingHMD::FPixelStreamingHMDModule`  
`class FPixelStreamingHMDModule : public IPixelStreamingHMDModule`  
_L15-36_
- inherits: `IPixelStreamingHMDModule`
- desc: This module allows HMD input to be used with pixel streaming
- L18 _public prototype_ `FPixelStreamingHMD* GetPixelStreamingHMD() const;`
- L19 _public function_ `EPixelStreamingXRSystem GetActiveXRSystem()`
- L20 _public function_ `void SetActiveXRSystem(EPixelStreamingXRSystem System)`
- L24 _private prototype_ `void StartupModule() override;` — IModuleInterface implementation
- L25 _private prototype_ `void ShutdownModule() override;`
- L29 _private prototype_ `virtual TSharedPtr<IXRTrackingSystem, ESPMode::ThreadSafe> CreateTrackingSystem() override;` — IHeadMountedDisplayModule implementation
- L30 _private function_ `FString GetModuleKeyName() const override`
- L31 _private function_ `bool IsHMDConnected() override`
- L34 _private member_ `TSharedPtr<FPixelStreamingHMD, ESPMode::ThreadSafe> HMD;`
- L35 _private member_ `EPixelStreamingXRSystem ActiveXRSystem;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreamingHMD` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingHMD/Private/Settings.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PixelStreamingHMD` (scope `UE`)
- L9 _namespace_ `namespace Settings` (scope `UE::PixelStreamingHMD`)
- L11 _prototype_ `extern void InitialiseSettings();` (scope `UE::PixelStreamingHMD::Settings`)
- L12 _prototype_ `extern void CommandLineParseOption();` (scope `UE::PixelStreamingHMD::Settings`)
- L15 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingEnableHMD;` (scope `UE::PixelStreamingHMD::Settings`)
- L16 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingHMDMatchAspectRatio;` (scope `UE::PixelStreamingHMD::Settings`)
- L17 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingHMDApplyEyePosition;` (scope `UE::PixelStreamingHMD::Settings`)
- L18 _externvar_ `extern TAutoConsoleVariable<bool> CVarPixelStreamingHMDApplyEyeRotation;` (scope `UE::PixelStreamingHMD::Settings`)
- L19 _externvar_ `extern TAutoConsoleVariable<float> CVarPixelStreamingHMDHFOV;` (scope `UE::PixelStreamingHMD::Settings`)
- L20 _externvar_ `extern TAutoConsoleVariable<float> CVarPixelStreamingHMDVFOV;` (scope `UE::PixelStreamingHMD::Settings`)
- L21 _externvar_ `extern TAutoConsoleVariable<float> CVarPixelStreamingHMDIPD;` (scope `UE::PixelStreamingHMD::Settings`)
- L22 _externvar_ `extern TAutoConsoleVariable<float> CVarPixelStreamingHMDProjectionOffsetX;` (scope `UE::PixelStreamingHMD::Settings`)
- L23 _externvar_ `extern TAutoConsoleVariable<float> CVarPixelStreamingHMDProjectionOffsetY;` (scope `UE::PixelStreamingHMD::Settings`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingHMD/Public/IPixelStreamingHMDModule.h` (Public)


#### class `IPixelStreamingHMDModule`  
`class IPixelStreamingHMDModule : public IHeadMountedDisplayModule`  
_L14-50_
- inherits: `IHeadMountedDisplayModule`
- desc: The public interface of the Pixel Streaming HMD module.
- L23 _public function_ `static inline IPixelStreamingHMDModule& Get()` — Singleton-like access to this module's interface. Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded. @return True if the module is loaded.
- L40 _public prototype_ `virtual FPixelStreamingHMD* GetPixelStreamingHMD() const = 0;` — @brief Get the Pixel Streaming HMD object @return FPixelStreamingHMD*
- L47 _public prototype_ `virtual EPixelStreamingXRSystem GetActiveXRSystem() = 0;` — @brief Get the Active XR System @return EPixelStreamingXRSystem
- L49 _public prototype_ `virtual void SetActiveXRSystem(EPixelStreamingXRSystem System) = 0;`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingHMD/Public/PixelStreamingHMD.h` (Public)


#### class `FPixelStreamingHMD`  
`class FPixelStreamingHMD : public FHeadMountedDisplayBase, public FHMDSceneViewExtension`  
_L20-122_
- inherits: `FHeadMountedDisplayBase,FHMDSceneViewExtension`
- desc: Pixel Streamed Head Mounted Display
- L24 _public function_ `virtual FName GetSystemName() const override` — IXRTrackingSystem interface
- L30 _public function_ `int32 GetXRSystemFlags() const`
- L31 _public prototype_ `virtual bool GetRelativeEyePose(int32 DeviceId, int32 ViewIndex, FQuat& OutOrientation, FVector& OutPosition) override;`
- L32 _public function_ `virtual void SetBasePosition(const FVector& InBasePosition) override`
- L33 _public function_ `virtual FVector GetBasePosition() const override`
- L35 _public prototype_ `virtual bool EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type = EXRTrackedDeviceType::Any) override;`
- L37 _public prototype_ `virtual void SetInterpupillaryDistance(float NewInterpupillaryDistance) override;`
- L38 _public prototype_ `virtual float GetInterpupillaryDistance() const override;`
- L40 _public prototype_ `virtual void ResetOrientationAndPosition(float yaw = 0.f) override;`
- L41 _public function_ `virtual void ResetOrientation(float Yaw = 0.f) override`
- L42 _public function_ `virtual void ResetPosition() override`
- L44 _public prototype_ `virtual bool GetCurrentPose(int32 DeviceId, FQuat& CurrentOrientation, FVector& CurrentPosition) override;`
- L45 _public function_ `virtual void SetBaseRotation(const FRotator& BaseRot) override`
- L46 _public function_ `virtual FRotator GetBaseRotation() const override`
- L48 _public function_ `virtual void SetBaseOrientation(const FQuat& BaseOrient) override`
- L49 _public function_ `virtual FQuat GetBaseOrientation() const override`
- L51 _public function_ `virtual class IHeadMountedDisplay* GetHMDDevice() override`
- L53 _public function_ `virtual class TSharedPtr<class IStereoRendering, ESPMode::ThreadSafe> GetStereoRenderingDevice() override`
- L60 _protected prototype_ `virtual float GetWorldToMetersScale() const override;` — FXRTrackingSystemBase protected interface
- L64 _public function_ `virtual bool IsHMDConnected() override` — IHeadMountedDisplay interface
- L65 _public prototype_ `virtual bool IsHMDEnabled() const override;`
- L66 _public prototype_ `virtual void EnableHMD(bool allow = true) override;`
- L67 _public prototype_ `virtual bool GetHMDMonitorInfo(MonitorInfo&) override;`
- L68 _public prototype_ `virtual void GetFieldOfView(float& OutHFOVInDegrees, float& OutVFOVInDegrees) const override;`
- L69 _public prototype_ `virtual bool IsChromaAbCorrectionEnabled() const override;`
- L70 _public function_ `virtual bool GetHMDDistortionEnabled(EShadingPath ShadingPath) const override`
- L71 _public prototype_ `virtual void DrawDistortionMesh_RenderThread(struct FHeadMountedDisplayPassContext& Context, const FIntPoint& TextureSize) override;`
- L74 _public prototype_ `virtual bool IsStereoEnabled() const override;` — IStereoRendering interface
- L75 _public prototype_ `virtual bool EnableStereo(bool stereo = true) override;`
- L76 _public prototype_ `virtual void AdjustViewRect(int32 ViewIndex, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;`
- L77 _public prototype_ `virtual void CalculateStereoViewOffset(const int32 ViewIndex, FRotator& ViewRotation, const float InWorldToMeters, FVector& ViewLocation) override;`
- L81 _public prototype_ `virtual FMatrix GetStereoProjectionMatrix(const int32 ViewIndex) const override;`
- L82 _public prototype_ `virtual void GetEyeRenderParams_RenderThread(const struct FHeadMountedDisplayPassContext& Context, FVector2D& EyeToSrcUVScaleValue, FVector2D& EyeToSrcUVOffsetValue) const override;`
- L87 _public prototype_ `virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;` — ISceneViewExtension interface
- L90 _public prototype_ `FPixelStreamingHMD(const FAutoRegister&);` — Constructor
- L93 _public prototype_ `virtual ~FPixelStreamingHMD();` — Destructor
- L96 _public function_ `bool IsInitialized() const` — @return	True if the HMD was initialized OK
- L98 _public function_ `void SetTransform(FTransform Transform)`
- L99 _public prototype_ `void SetEyeViews(FTransform Left, FMatrix LeftProj, FTransform Right, FMatrix RightProj, FTransform HMD);`
- L102 _private member_ `FVector BasePosition = FVector::ZeroVector;`
- L103 _private member_ `FTransform CurHmdTransform;`
- L104 _private member_ `FVector LeftEyePosOffset;`
- L105 _private member_ `FVector RightEyePosOffset;`
- L106 _private member_ `FQuat LeftEyeRotOffset;`
- L107 _private member_ `FQuat RightEyeRotOffset;`
- L108 _private member_ `float WorldToMeters;`
- L109 _private member_ `float InterpupillaryDistance;`
- L110 _private member_ `float HFoVRads = FMath::DegreesToRadians(90.0f);`
- L111 _private member_ `float VFoVRads = FMath::DegreesToRadians(90.0f);`
- L112 _private member_ `float CurLeftEyeProjOffsetX = 0.0f;`
- L113 _private member_ `float CurLeftEyeProjOffsetY = 0.0f;`
- L114 _private member_ `float CurRightEyeProjOffsetX = 0.0f;`
- L115 _private member_ `float CurRightEyeProjOffsetY = 0.0f;`
- L116 _private member_ `float TargetAspectRatio = 9.0f/16.0f;`
- L117 _private member_ `float NearClip = 10.0f;`
- L118 _private member_ `float FarClip = 10000.0f;`
- L119 _private member_ `bool bStereoEnabled;`
- L120 _private member_ `bool bReceivedTransforms = false;`
- L121 _private member_ `double LastResChangeSeconds = 0.0f;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreamingHMD, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreamingHMD, Log, All);`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingHMD/Public/PixelStreamingHMDEnums.h` (Public)


#### enum `EPixelStreamingXRSystem`  
`enum class EPixelStreamingXRSystem : uint8`  
_L7-12_
- L9 _public enumerator_ `Unknown`
- L10 _public enumerator_ `HTCVive`
- L11 _public enumerator_ `Quest`
