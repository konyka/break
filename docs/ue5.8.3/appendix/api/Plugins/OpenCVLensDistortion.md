# Plugins / OpenCVLensDistortion

- module root: `Plugins/Compositing/OpenCVLensDistortion/Source/OpenCVLensDistortion`
- headers: 3; symbols: 20
- symbol kinds: class=2, delegate=1, function=5, macro=1, member=3, prototype=6, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Projects, RHI, RenderCore
- PublicDependencyModuleNames: OpenCV, OpenCVHelper

### `Plugins/Compositing/OpenCVLensDistortion/Source/OpenCVLensDistortion/Public/IOpenCVLensDistortionModule.h` (Public)


#### class `IOpenCVLensDistortionModule`  
`class IOpenCVLensDistortionModule : public IModuleInterface`  
_L17-45_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L31 _public function_ `static inline IOpenCVLensDistortionModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L41 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L10 _macro_ `#define OPENCV_LENSDISTORTION_MODULE_NAME TEXT("OpenCVLensDistortion")`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenCVLensDistortion, Verbose, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenCVLensDistortion, Verbose, All);`

### `Plugins/Compositing/OpenCVLensDistortion/Source/OpenCVLensDistortion/Public/OpenCVLensDistortionBlueprintLibrary.h` (Public)


#### class `UOpenCVLensDistortionBlueprintLibrary`  
`class UOpenCVLensDistortionBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L18-62_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="OpenCVLensDistortionLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L31 _private prototype_ `static void DrawDisplacementMapToRenderTarget(const UObject* WorldContextObject, UTextureRenderTarget2D* OutputRenderTarget, UTexture2D* PreComputedUndistortDisplacementMap);` — `UFUNCTION(BlueprintCallable, Category = "Lens Distortion | OpenCV", meta = (WorldContext = "WorldContextObject"))` — Draws UV displacement map within the output render target. - Red & green channels hold the distort to undistort displacement; - Blue & alpha channels hold the undistort to distort displacement. @param WorldContextObject Current world to get the rendering settings from (such as feature level). @param OutputRenderTarget The render target to draw to. Don't necessarily need to have same resolution or aspect ratio as distorted render. @param PreComputedUndistortDisplacementMap Distort to undistort displacement pre computed using OpenCV in engine or externally.
- L43 _private prototype_ `static UTexture2D* CreateUndistortUVDisplacementMap(const FOpenCVLensDistortionParameters& LensParameters, const FIntPoint& ImageSize, const float CroppingFactor, FOpenCVCameraViewInfo& CameraViewInfo);` — `UFUNCTION(BlueprintCallable, Category = "Lens Distortion | OpenCV", meta = (WorldContext = "WorldContextObject"))` — Creates a texture containing a DisplacementMap in the Red and the Green channel for undistorting a camera image. This call can take quite some time to process depending on the resolution. @param LensParameters The Lens distortion parameters with which to compute the UV displacement map. @param ImageSize The size of the camera image to be undistorted in pixels. Scaled down resolution will have an impact. @param CroppingFactor One means OpenCV will attempt to crop out all empty pixels resulting from the process (essentially zooming the image). Zero will keep all pixels. @param CameraViewInfo Information computed by OpenCV about the undistorted space. Can be used with SceneCapture to adjust FOV. @return Texture2D containing the distort to undistort space displacement map.
- L47 _private function_ `static bool EqualEqual_CompareLensDistortionModels( const FOpenCVLensDistortionParameters& A, const FOpenCVLensDistortionParameters& B)` — `UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal (LensDistortionParameters)", CompactNodeTitle = "==", Keywords = "== equal", ScriptOperator = "=="), Category = "Lens Distortion")` — Returns true if A is equal to B (A == B)
- L56 _private function_ `static bool NotEqual_CompareLensDistortionModels( const FOpenCVLensDistortionParameters& A, const FOpenCVLensDistortionParameters& B)` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "NotEqual (LensDistortionParameters)", CompactNodeTitle = "!=", Keywords = "!= not equal", ScriptOperator = "!="), Category = "Lens Distortion")` — Returns true if A is not equal to B (A != B)

### `Plugins/Compositing/OpenCVLensDistortion/Source/OpenCVLensDistortion/Public/OpenCVLensDistortionParameters.h` (Public)


#### struct `FOpenCVCameraViewInfo`  
`struct FOpenCVCameraViewInfo`  
_L19-40_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public function_ `FOpenCVCameraViewInfo() : HorizontalFOV(0.0f) , VerticalFOV(0.0f) , FocalLengthRatio(0.0f)`
- L31 _public member_ `float HorizontalFOV;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Info")` — Horizontal Field Of View in degrees
- L35 _public member_ `float VerticalFOV;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Info")` — Vertical Field Of View in degrees
- L39 _public member_ `float FocalLengthRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Info")` — Focal length aspect ratio -> Fy / Fx

#### struct `FOpenCVLensDistortionParameters`  
`struct FOpenCVLensDistortionParameters : public FOpenCVLensDistortionParametersBase`  
_L51-73_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FOpenCVLensDistortionParametersBase`
- desc: Mathematic camera model for lens distortion/undistortion. Camera matrix = | F.X  0  C.x | |  0  F.Y C.Y | |  0   0   1  | where F and C are normalized.
- L63 _public prototype_ `static void DrawDisplacementMapToRenderTarget(UWorld* InWorld, UTextureRenderTarget2D* InOutputRenderTarget, UTexture2D* InPreComputedUndistortDisplacementMap);` — Draws UV displacement map within the output render target. - Red & green channels hold the distort to undistort displacement; - Blue & alpha channels hold the undistort to distort displacement. @param InWorld Current world to get the rendering settings from (such as feature level). @param InOutputRenderTarget The render target to draw to. Don't necessarily need to have same resolution or aspect ratio as distorted render. @param InPreComputedUndistortDisplacementMap Distort to undistort displacement pre computed using OpenCV in engine or externally.
- L72 _public prototype_ `UTexture2D* CreateUndistortUVDisplacementMap(const FIntPoint& InImageSize, const float InCroppingFactor, FOpenCVCameraViewInfo& OutCameraViewInfo) const;` — Creates a texture containing a DisplacementMap in the Red and the Green channel for undistorting a camera image. This call can take quite some time to process depending on the resolution. @param InImageSize The size of the camera image to be undistorted in pixels. Scaled down resolution will have an impact. @param InCroppingFactor One means OpenCV will attempt to crop out all empty pixels resulting from the process (essentially zooming the image). Zero will keep all pixels. @param OutCameraViewInfo Information computed by OpenCV about the undistorted space. Can be used with SceneCapture to adjust FOV.
