# Plugins / OpenCVLensCalibration

- module root: `Plugins/Compositing/OpenCVLensDistortion/Source/OpenCVLensCalibration`
- headers: 2; symbols: 22
- symbol kinds: class=2, delegate=1, function=3, macro=1, member=8, prototype=7
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, OpenCV, OpenCVHelper, OpenCVLensDistortion

### `Plugins/Compositing/OpenCVLensDistortion/Source/OpenCVLensCalibration/Private/OpenCVLensCalibrator.h` (Private)


#### class `UOpenCVLensCalibrator`  
`class UOpenCVLensCalibrator : public UObject`  
_L24-119_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent))`
- inherits: `UObject`
- L32 _private function_ `UOpenCVLensCalibrator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : UObject(ObjectInitializer)` — Default constructor for an OpenCV lens calibration object.
- L44 _public prototype_ `static UOpenCVLensCalibrator* CreateCalibrator(int32 BoardWidth = 7, int32 BoardHeight = 5, float SquareSize = 3.f, bool bUseFisheyeModel = false);` — `UFUNCTION(BlueprintCallable, Category = "LensDistortion|OpenCV|Calibration")` — @param BoardWidth The width of the checkerboard used to calibrate the camera counted as number of inner edges. @param BoardHeight The height of the checkerboard used to calibrate the camera counted as number of inner edges. @param SquareSize The width of each square in (potentially arbitrary) world units. @param bUseFisheyeModel Specifies if the calibrator is to use the fisheye camera model from OpenCV
- L52 _public prototype_ `void Reset(int32 InBoardWidth, int32 InBoardHeight, float InSquareSize = 3.f, bool bInUseFisheyeModel = false);` — @param InBoardWidth The width of the checkerboard used to calibrate the camera counted as number of inner edges. @param InBoardHeight The height of the checkerboard used to calibrate the camera counted as number of inner edges. @param InSquareSize The width of each square in (potentially arbitrary) world units. @param bInUseFisheyeModel Specifies if the calibrator is to use the fisheye camera model from OpenCV
- L60 _public prototype_ `bool FeedRenderTarget(UTextureRenderTarget2D* TextureRenderTarget);` — `UFUNCTION(BlueprintCallable, Category = "LensDistortion|OpenCV|Calibration")` — Feeds a render target to the calibration. It must contain a checkerboard somewhere in the image. The images fed in should come from the same camera. @return true if the calibrator found a checkerboard in the image.
- L68 _public prototype_ `bool FeedImage(const FString& FilePath);` — `UFUNCTION(BlueprintCallable, Category = "LensDistortion|OpenCV|Calibration")` — Feeds an image to the calibration. It must contain a checkerboard somewhere in the image. The images fed in should come from the same camera. @return true if the calibrator found a checkerboard in the image.
- L77 _public prototype_ `bool CalculateLensParameters(FOpenCVLensDistortionParameters& LensDistortionParameters, float& MarginOfError, FOpenCVCameraViewInfo& CameraViewInfo);` — `UFUNCTION(BlueprintCallable, Category = "LensDistortion|OpenCV|Calibration")` — @param LensDistortionParameters the calculated distortion data from the images passed into the calibrator. @param MarginOfError returned reprojection error of the calibration @param CameraViewInfo returned information about the camera view obtained from calibration parameters @return true if there was enough data to calculate the distortion
- L86 _private prototype_ `bool Feed(const cv::Mat& InImage);`
- L92 _public member_ `FVector2D MinimumCornerCoordinates;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Calibration")` — Smallest coordinates of a grid corner that was found. For best result, try to cover full resolution of the input.
- L96 _public member_ `FVector2D MaximumCornerCoordinates;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Calibration")` — Biggest coordinates of a grid corner that was found. For best result, try to cover full resolution of the input.
- L102 _private member_ `std::vector<std::vector<cv::Point2f>> ImagePoints;` — Size of a square in the grid. Potentially useless.
- L105 _private member_ `std::vector<cv::Point3f> BoardPoints;` — Size of a square in the grid. Potentially useless.
- L108 _private member_ `cv::Size ImageSize;` — Size of input image used for calibration in pixels.
- L111 _private member_ `cv::Size BoardSize;` — Size of the checkerboard in number of squares.
- L115 _private member_ `float SquareSize;` — Size of a square in the grid. Potentially useless.
- L118 _private member_ `bool bUseFisheyeModel;` — Specifies if Fisheye camera model is to be used.

### `Plugins/Compositing/OpenCVLensDistortion/Source/OpenCVLensCalibration/Public/IOpenCVLensCalibrationModule.h` (Public)


#### class `IOpenCVLensCalibrationModule`  
`class IOpenCVLensCalibrationModule : public IModuleInterface`  
_L17-42_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L28 _public function_ `static inline IOpenCVLensCalibrationModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L38 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L10 _macro_ `#define OPENCV_LENSCALIBRATION_MODULE_NAME TEXT("OpenCVLensCalibration")`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenCVLensCalibration, Verbose, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenCVLensCalibration, Verbose, All);`
