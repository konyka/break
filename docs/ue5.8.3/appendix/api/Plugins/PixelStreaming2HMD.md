# Plugins / PixelStreaming2HMD

- module root: `Plugins/Media/PixelStreaming2/Source/PixelStreaming2HMD`
- headers: 6; symbols: 89
- symbol kinds: class=4, delegate=1, enum=1, enumerator=3, function=22, macro=1, member=22, namespace=2, prototype=33
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, HeadMountedDisplay, InputCore, PixelStreaming2Settings, RHI, RenderCore, Renderer, SlateCore, XRBase
- PublicDependencyModuleNames: Core

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2HMD/Private/Logging.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2HMD, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2HMD, Log, All);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2HMD/Private/PixelStreaming2HMD.h` (Private)


#### class `FPixelStreaming2HMD`  
`class FPixelStreaming2HMD : public IPixelStreaming2HMD, public FHeadMountedDisplayBase, public FHMDSceneViewExtension`  
_L19-121_
- inherits: `IPixelStreaming2HMD,FHeadMountedDisplayBase,FHMDSceneViewExtension`
- desc: Pixel Streamed Head Mounted Display
- L23 _public function_ `virtual FName GetSystemName() const override`
- L29 _public function_ `int32 GetXRSystemFlags() const`
- L30 _public prototype_ `virtual bool GetRelativeEyePose(int32 DeviceId, int32 ViewIndex, FQuat& OutOrientation, FVector& OutPosition) override;`
- L31 _public function_ `virtual void SetBasePosition(const FVector& InBasePosition) override`
- L32 _public function_ `virtual FVector GetBasePosition() const override`
- L34 _public prototype_ `virtual bool EnumerateTrackedDevices(TArray<int32>& OutDevices, EXRTrackedDeviceType Type = EXRTrackedDeviceType::Any) override;`
- L36 _public prototype_ `virtual void SetInterpupillaryDistance(float NewInterpupillaryDistance) override;`
- L37 _public prototype_ `virtual float GetInterpupillaryDistance() const override;`
- L39 _public prototype_ `virtual void ResetOrientationAndPosition(float yaw = 0.f) override;`
- L40 _public function_ `virtual void ResetOrientation(float Yaw = 0.f) override`
- L41 _public function_ `virtual void ResetPosition() override`
- L43 _public prototype_ `virtual bool GetCurrentPose(int32 DeviceId, FQuat& CurrentOrientation, FVector& CurrentPosition) override;`
- L44 _public function_ `virtual void SetBaseRotation(const FRotator& BaseRot) override`
- L45 _public function_ `virtual FRotator GetBaseRotation() const override`
- L47 _public function_ `virtual void SetBaseOrientation(const FQuat& BaseOrient) override`
- L48 _public function_ `virtual FQuat GetBaseOrientation() const override`
- L50 _public function_ `virtual class IHeadMountedDisplay* GetHMDDevice() override`
- L52 _public function_ `virtual class TSharedPtr<class IStereoRendering, ESPMode::ThreadSafe> GetStereoRenderingDevice() override`
- L60 _protected prototype_ `virtual float GetWorldToMetersScale() const override;`
- L65 _public function_ `virtual bool IsHMDConnected() override`
- L66 _public prototype_ `virtual bool IsHMDEnabled() const override;`
- L67 _public prototype_ `virtual void EnableHMD(bool allow = true) override;`
- L68 _public prototype_ `virtual bool GetHMDMonitorInfo(MonitorInfo&) override;`
- L69 _public prototype_ `virtual void GetFieldOfView(float& OutHFOVInDegrees, float& OutVFOVInDegrees) const override;`
- L70 _public prototype_ `virtual bool IsChromaAbCorrectionEnabled() const override;`
- L71 _public function_ `virtual bool GetHMDDistortionEnabled(EShadingPath ShadingPath) const override`
- L72 _public prototype_ `virtual void DrawDistortionMesh_RenderThread(struct FHeadMountedDisplayPassContext& Context, const FIntPoint& TextureSize) override;`
- L76 _public prototype_ `virtual bool IsStereoEnabled() const override;`
- L77 _public prototype_ `virtual bool EnableStereo(bool stereo = true) override;`
- L78 _public prototype_ `virtual void AdjustViewRect(int32 ViewIndex, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;`
- L79 _public prototype_ `virtual void CalculateStereoViewOffset(const int32 ViewIndex, FRotator& ViewRotation, const float InWorldToMeters, FVector& ViewLocation) override;`
- L80 _public prototype_ `virtual FMatrix GetStereoProjectionMatrix(const int32 ViewIndex) const override;`
- L81 _public prototype_ `virtual void GetEyeRenderParams_RenderThread(const struct FHeadMountedDisplayPassContext& Context, FVector2D& EyeToSrcUVScaleValue, FVector2D& EyeToSrcUVOffsetValue) const override;`
- L85 _public prototype_ `virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;`
- L88 _public prototype_ `FPixelStreaming2HMD(const FAutoRegister&);`
- L90 _public prototype_ `virtual ~FPixelStreaming2HMD();`
- L95 _public function_ `bool IsInitialized() const` — @return	True if the HMD was initialized OK
- L97 _public function_ `virtual void SetTransform(FTransform Transform) override`
- L98 _public prototype_ `virtual void SetEyeViews(FTransform Left, FMatrix LeftProj, FTransform Right, FMatrix RightProj, FTransform HMD) override;`
- L101 _private member_ `FVector BasePosition = FVector::ZeroVector;`
- L102 _private member_ `FTransform CurHmdTransform;`
- L103 _private member_ `FVector LeftEyePosOffset;`
- L104 _private member_ `FVector RightEyePosOffset;`
- L105 _private member_ `FQuat LeftEyeRotOffset;`
- L106 _private member_ `FQuat RightEyeRotOffset;`
- L107 _private member_ `float WorldToMeters;`
- L108 _private member_ `float InterpupillaryDistance;`
- L109 _private member_ `float HFoVRads = FMath::DegreesToRadians(90.0f);`
- L110 _private member_ `float VFoVRads = FMath::DegreesToRadians(90.0f);`
- L111 _private member_ `float CurLeftEyeProjOffsetX = 0.0f;`
- L112 _private member_ `float CurLeftEyeProjOffsetY = 0.0f;`
- L113 _private member_ `float CurRightEyeProjOffsetX = 0.0f;`
- L114 _private member_ `float CurRightEyeProjOffsetY = 0.0f;`
- L115 _private member_ `float TargetAspectRatio = 9.0f / 16.0f;`
- L116 _private member_ `float NearClip = 10.0f;`
- L117 _private member_ `float FarClip = 10000.0f;`
- L118 _private member_ `bool bStereoEnabled;`
- L119 _private member_ `bool bReceivedTransforms = false;`
- L120 _private member_ `double LastResChangeSeconds = 0.0f;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELSTREAMING2HMD_API`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2HMD/Private/PixelStreaming2HMDModule.h` (Private)


#### class `UE::PixelStreaming2HMD::FPixelStreaming2HMDModule`  
`class FPixelStreaming2HMDModule : public IPixelStreaming2HMDModule`  
_L15-36_
- inherits: `IPixelStreaming2HMDModule`
- desc: This module allows HMD input to be used with pixel streaming
- L18 _public prototype_ `FPixelStreaming2HMD* GetPixelStreaming2HMD() const;`
- L19 _public function_ `EPixelStreaming2XRSystem GetActiveXRSystem()`
- L20 _public function_ `void SetActiveXRSystem(EPixelStreaming2XRSystem System)`
- L24 _private prototype_ `void StartupModule() override;`
- L25 _private prototype_ `void ShutdownModule() override;`
- L29 _private prototype_ `virtual TSharedPtr<IXRTrackingSystem, ESPMode::ThreadSafe> CreateTrackingSystem() override;`
- L30 _private function_ `FString GetModuleKeyName() const override`
- L31 _private function_ `bool IsHMDConnected() override`
- L34 _private member_ `TSharedPtr<FPixelStreaming2HMD, ESPMode::ThreadSafe> HMD;`
- L35 _private member_ `EPixelStreaming2XRSystem ActiveXRSystem;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PixelStreaming2HMD` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2HMD/Public/IPixelStreaming2HMD.h` (Public)


#### class `IPixelStreaming2HMD`  
`class IPixelStreaming2HMD`  
_L11-29_
- desc: Interface class that allows for setting the transform data for a Head Mounted Display (HMD). The transform and projection matrix for each eye can be individually set.
- L18 _public prototype_ `virtual void SetTransform(FTransform Transform) = 0;` — @brief Set the transform for the HMD. @param Transform The transform for the HMD to set.
- L28 _public prototype_ `virtual void SetEyeViews(FTransform Left, FMatrix LeftProj, FTransform Right, FMatrix RightProj, FTransform HMD) = 0;` — @brief Set the eye views, including the eye positions and their respective projection matrices @param Left The transform of the left eye relative to the HMD transform. @param LeftProj The Projection matrix of the left eye. @param Right The transform of the right eye relative to the HMD transform. @param RightProj The Projection matrix of the right eye. @param HMD The transform for the HMD to set.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2HMD/Public/IPixelStreaming2HMDModule.h` (Public)


#### class `IPixelStreaming2HMDModule`  
`class IPixelStreaming2HMDModule : public IHeadMountedDisplayModule`  
_L13-50_
- inherits: `IHeadMountedDisplayModule`
- desc: The public interface provides functionality for interacting with Pixel Streaming and Head Mounted Display (HMD) systems.
- L22 _public function_ `static inline IPixelStreaming2HMDModule& Get()` — Singleton-like access to this module's interface. Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded. @return True if the module is loaded.
- L37 _public prototype_ `virtual IPixelStreaming2HMD* GetPixelStreaming2HMD() const = 0;` — @brief Get the Pixel Streaming HMD object. @return Pointer to the Pixel Streaming HMD.
- L43 _public prototype_ `virtual EPixelStreaming2XRSystem GetActiveXRSystem() = 0;` — @brief Get the Active XR System. @return The Active XR System.
- L49 _public prototype_ `virtual void SetActiveXRSystem(EPixelStreaming2XRSystem System) = 0;` — @brief Set the Active XR System. @param System The Active XR System to set.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2HMD/Public/PixelStreaming2HMDEnums.h` (Public)


#### enum `EPixelStreaming2XRSystem`  
`enum class EPixelStreaming2XRSystem : uint8`  
_L10-18_
- desc: Enums for different XR (Extended Reality) Systems that can be used with Pixel Streaming.
- L13 _public enumerator_ `Unknown` — The XR system is unknown or not specified.
- L15 _public enumerator_ `HTCVive` — HTC Vive XR system.
- L17 _public enumerator_ `Quest` — Oculus Quest XR system.
