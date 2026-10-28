# Plugins / LensDistortion

- module root: `Plugins/Compositing/LensDistortion/Source/LensDistortion`
- headers: 3; symbols: 22
- symbol kinds: class=2, function=7, member=7, prototype=5, struct=1
- PrivateDependencyModuleNames: Projects
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RHI, RenderCore

### `Plugins/Compositing/LensDistortion/Source/LensDistortion/Classes/LensDistortionAPI.h` (Public)


#### struct `FLensDistortionCameraModel`  
`struct FLensDistortionCameraModel`  
_L18-107_
- reflection: `UE_DEPRECATED(5.0, "The LensDistortion plugin is deprecated. Please update your project to use the features of the CameraCalibration plugin.")`
- reflection: `USTRUCT(BlueprintType)`
- desc: Mathematic camera model for lens distortion/undistortion. Camera matrix = | F.X  0  C.x | |  0  F.Y C.Y | |  0   0   1  |
- L21 _public function_ `FLensDistortionCameraModel()`
- L31 _public member_ `float K1;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Camera Model")` — Radial parameter #1.
- L35 _public member_ `float K2;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Camera Model")` — Radial parameter #2.
- L39 _public member_ `float K3;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Camera Model")` — Radial parameter #3.
- L43 _public member_ `float P1;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Camera Model")` — Tangential parameter #1.
- L47 _public member_ `float P2;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Camera Model")` — Tangential parameter #2.
- L51 _public member_ `FVector2D F;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Camera Model")` — Camera matrix's Fx and Fy.
- L55 _public member_ `FVector2D C;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Camera Model")` — Camera matrix's Cx and Cy.
- L59 _public prototype_ `FVector2D UndistortNormalizedViewPosition(FVector2D V) const;` — Undistorts 3d vector (x, y, z=1.f) in the view space and returns (x', y', z'=1.f).
- L63 _public prototype_ `float GetUndistortOverscanFactor( float DistortedHorizontalFOV, float DistortedAspectRatio) const;` — Returns the overscan factor required for the undistort rendering to avoid unrendered distorted pixels.
- L79 _public prototype_ `void DrawUVDisplacementToRenderTarget( class UWorld* World, float DistortedHorizontalFOV, float DistortedAspectRatio, float UndistortOverscanFactor, class UTextureRenderTarget2D* OutputRenderTarget, float OutputMultiply, float OutputAdd) const;` — Draws UV displacement map within the output render target. - Red & green channels hold the distortion displacement; - Blue & alpha channels hold the undistortion displacement. @param World Current world to get the rendering settings from (such as feature level). @param DistortedHorizontalFOV The desired horizontal FOV in the distorted render. @param DistortedAspectRatio The desired aspect ratio of the distorted render. @param UndistortOverscanFactor The factor of the overscan for the undistorted render. @param OutputRenderTarget The render target to draw to. Don't necessarily need to have same resolution or aspect ratio as distorted render. @param OutputMultiply The multiplication factor applied on the displacement. @param OutputAdd Value added to the multiplied displacement before storing into the output render target.
- L90 _public function_ `bool operator == (const FLensDistortionCameraModel& Other) const` — Compare two lens distortion models and return whether they are equal.
- L103 _public function_ `bool operator != (const FLensDistortionCameraModel& Other) const` — Compare two lens distortion models and return whether they are different.

### `Plugins/Compositing/LensDistortion/Source/LensDistortion/Classes/LensDistortionBlueprintLibrary.h` (Public)


#### class `ULensDistortionBlueprintLibrary`  
`class ULensDistortionBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L14-69_
- reflection: `UE_DEPRECATED(5.0, "The LensDistortion plugin is deprecated. Please update your project to use the features of the CameraCalibration plugin.")`
- reflection: `UCLASS(MinimalAPI, meta=(DeprecationMessage = "The LensDistortion plugin is deprecated. Please update your project to use the features of the CameraCalibration plugin.", ScriptName="LensDistortionLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L22 _private prototype_ `static void GetUndistortOverscanFactor( const FLensDistortionCameraModel& CameraModel, float DistortedHorizontalFOV, float DistortedAspectRatio, float& UndistortOverscanFactor);` — `UFUNCTION(BlueprintPure, Category = "Lens Distortion", meta = (DeprecatedFunction, DeprecationMessage = "The LensDistortion plugin is deprecated. Please update your project to use the features of the CameraCalibration plugin."))` — Returns the overscan factor required for the undistort rendering to avoid unrendered distorted pixels.
- L39 _private prototype_ `static void DrawUVDisplacementToRenderTarget( const UObject* WorldContextObject, const FLensDistortionCameraModel& CameraModel, float DistortedHorizontalFOV, float DistortedAspectRatio, float UndistortOverscanFactor, class UTextureRenderTarget2D* OutputRenderTarget, float OutputMultiply = 0.5, float OutputAdd = 0.5 );` — `UFUNCTION(BlueprintCallable, Category = "Lens Distortion", meta = (DeprecatedFunction, DeprecationMessage = "The LensDistortion plugin is deprecated. Please update your project to use the features of the CameraCalibration plugin.", WorldContext = "WorldContextObject"))` — Draws UV displacement map within the output render target. - Red & green channels hold the distortion displacement; - Blue & alpha channels hold the undistortion displacement. @param DistortedHorizontalFOV The desired horizontal FOV in the distorted render. @param DistortedAspectRatio The desired aspect ratio of the distorted render. @param UndistortOverscanFactor The factor of the overscan for the undistorted render. @param OutputRenderTarget The render target to draw to. Don't necessarily need to have same resolution or aspect ratio as distorted render. @param OutputMultiply The multiplication factor applied on the displacement. @param OutputAdd Value added to the multiplied displacement before storing into the output render target.
- L52 _private function_ `static bool EqualEqual_CompareLensDistortionModels( const FLensDistortionCameraModel& A, const FLensDistortionCameraModel& B)` — `UFUNCTION(BlueprintPure, meta=(DeprecatedFunction, DeprecationMessage = "The LensDistortion plugin is deprecated. Please update your project to use the features of the CameraCalibration plugin.", DisplayName = "Equal (LensDistortionCameraModel)", CompactNodeTitle = "==", Keywords = "== equal"), Category = "Lens Distortion")` — Returns true if A is equal to B (A == B)
- L61 _private function_ `static bool NotEqual_CompareLensDistortionModels( const FLensDistortionCameraModel& A, const FLensDistortionCameraModel& B)` — `UFUNCTION(BlueprintPure, meta = (DeprecatedFunction, DeprecationMessage = "The LensDistortion plugin is deprecated. Please update your project to use the features of the CameraCalibration plugin.", DisplayName = "NotEqual (LensDistortionCameraModel)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category = "Lens Distortion")` — Returns true if A is not equal to B (A != B)

### `Plugins/Compositing/LensDistortion/Source/LensDistortion/Public/ILensDistortion.h` (Public)


#### class `ILensDistortion`  
`class ILensDistortion : public IModuleInterface`  
_L14-41_
- reflection: `UE_DEPRECATED(5.0, "The LensDistortion plugin is deprecated. Please update your project to use the features of the CameraCalibration plugin.")`
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L26 _public function_ `static inline ILensDistortion& Get()` — `UE_DEPRECATED(5.0, "The LensDistortion plugin is deprecated. Please update your project to use the features of the CameraCalibration plugin.")` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — `UE_DEPRECATED(5.0, "The LensDistortion plugin is deprecated. Please update your project to use the features of the CameraCalibration plugin.")` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
