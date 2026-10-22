# Plugins / MetaHumanCalibrationLib

- module root: `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib`
- headers: 220; symbols: 3566
- symbol kinds: class=150, enum=28, enumerator=93, function=1202, macro=76, member=600, namespace=37, prototype=1204, struct=77, typedef=99
- PrivateDependencyModuleNames: CaptureDataCore, Core, Eigen, ImageCore, OpenCV, OpenCVHelper, RigLogicLib, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/SetCamerasHelper.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Wrappers` (scope `UE`)
- L20 _prototype_ `void SetCamerasHelper(const TArray<FCameraCalibration>& InCalibrations, std::map<std::string, TITAN_API_NAMESPACE::OpenCVCameraD>& OutCameras);` (scope `UE::Wrappers`) — Convert the array of camera calibrations into the form required to pass to the titan API @param[in] InCalibration An array of camera calibrations. @param[out] OutCameras The cameras in the form required by the titan API
- L27 _prototype_ `void GetCalibrationsHelper(const std::map<std::string, TITAN_API_NAMESPACE::OpenCVCameraD>& InCameras, TArray<FCameraCalibration>& OutCalibrations);` (scope `UE::Wrappers`) — Convert a map of the titan API cameras to an array of camera calibrations @param[in] InCameras A map of the cameras in form given by the titan API @param[out] OutCalibrations An array of camera calibrations

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/TitanVersion.h` (Private)


#### Free symbols / members of external scopes

- L3 _macro_ `#define MHCALIB_TITAN_MAJOR_VERSION 9`
- L4 _macro_ `#define MHCALIB_TITAN_MINOR_VERSION 0`
- L5 _macro_ `#define MHCALIB_TITAN_PATCH_VERSION 9`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/api/CameraUndistortion.h` (Private)


#### class `TITAN_API_NAMESPACE::CameraUndistortion`  
`class CameraUndistortion`  
_L12-54_
- L15 _public prototype_ `CameraUndistortion();`
- L16 _public prototype_ `~CameraUndistortion();`
- L17 _public prototype_ `CameraUndistortion(CameraUndistortion&&) = delete;`
- L18 _public prototype_ `CameraUndistortion(const CameraUndistortion&) = delete;`
- L19 _public prototype_ `CameraUndistortion& operator=(CameraUndistortion&&) = delete;`
- L20 _public prototype_ `CameraUndistortion& operator=(const CameraUndistortion&) = delete;`
- L26 _public prototype_ `bool Init();` — Initialize camera undistortion. @returns True if initialization is successful, False otherwise.
- L31 _public prototype_ `void Reset();` — Remove all cameras.
- L36 _public prototype_ `void AddCamera(const char* InCameraName, const OpenCVCamera& InCameraParameters);` — Add a camera with name @p InCameraName and camera parameters @p InCameraParameters
- L43 _public prototype_ `bool UndistortImage(const char* InCameraName, const unsigned char* InImageData, unsigned char* OutImageData);` — Undistorts the image @p InImageData using the parameters of camera @p InCameraName and saves it to @p OutImageData. The images need have format RGBA uint8, though each channel is interpolated independently including the alpha channel. @returns True if image was undistorted, False if @p InCameraName was not added via AddCamera().
- L49 _public prototype_ `bool UndistortPoints(const char* InCameraName, int32_t InNumPoints, const float* InPointsData, float* OutPointsData) const;` — Undistort the @p InNumPoints number of points @p InPointsData using the parameters of camera @p InCameraName and outputs it to @p OutPointsData @returns True if the points were undistorted, False if @p InCameraName was not added via AddCamera().
- L53 _private member_ `Private* m;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/api/Common.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define TITAN_RESET_ERROR if (!sc::StatusProvider::isOk()) sc::StatusProvider::set({ 0, "" })`
- L10 _macro_ `#define TITAN_SET_ERROR(errorCode, message) sc::StatusProvider::set({ errorCode, message })`
- L12 _macro_ `#define TITAN_CHECK_OR_RETURN(condition, returnValue, ...) if (!(condition)) { \`
- L17 _macro_ `#define TITAN_HANDLE_EXCEPTION(...) { \`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/api/Defs.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define TITAN_NAMESPACE epic::nls`
- L14 _macro_ `#define TITAN_API_NAMESPACE titan::api`
- L18 _macro_ `#define TITAN_API`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/api/FBBundleAdjustment.h` (Private)


#### struct `TITAN_API_NAMESPACE::FBBundleAdjustmentParameters`  
`struct FBBundleAdjustmentParameters`  
_L15-29_
- L17 _public member_ `size_t Iterations = 50;`
- L18 _public member_ `size_t NumberOfFrames = 0;`
- L20 _public member_ `std::vector<int> FixedIntrinsicIndices = {};`
- L21 _public member_ `std::vector<int> FixedDistortionIndices = {};`
- L23 _public member_ `bool bFixedScale = false;`
- L26 _public member_ `std::vector<std::vector<std::vector<double>>> ReferencePoints;` — Two 2d points per camera for every frame Two 2d points are packed in vector [Point1.X, Point1.Y, Point2.X, Point2.Y]
- L28 _public member_ `double ReferenceDistance;`

#### struct `TITAN_API_NAMESPACE::FBFullBundleAdjustmentParameters`  
`struct FBFullBundleAdjustmentParameters : public FBBundleAdjustmentParameters`  
_L31-37_
- inherits: `FBBundleAdjustmentParameters`
- L34 _public member_ `bool bOptimizeIntrinsics = false;`
- L35 _public member_ `bool bOptimizeDistortion = false;`
- L36 _public member_ `bool bOptimizePoints = false;`

#### class `TITAN_API_NAMESPACE::FeatureBasedBundleAdjustment`  
`class FeatureBasedBundleAdjustment`  
_L39-98_
- L42 _public prototype_ `FeatureBasedBundleAdjustment();`
- L43 _public prototype_ `~FeatureBasedBundleAdjustment();`
- L45 _public prototype_ `FeatureBasedBundleAdjustment(FeatureBasedBundleAdjustment&& InOther) noexcept;`
- L46 _public prototype_ `FeatureBasedBundleAdjustment& operator=(FeatureBasedBundleAdjustment&& InOther) noexcept;`
- L48 _public prototype_ `FeatureBasedBundleAdjustment(const FeatureBasedBundleAdjustment&) = delete;`
- L49 _public prototype_ `FeatureBasedBundleAdjustment& operator=(const FeatureBasedBundleAdjustment&) = delete;`
- L56 _public prototype_ `bool Init(const std::map<std::string, OpenCVCameraD>& InCalibrationInformation);` — Initializes Feature Based Bundle Adjustment using calibration information from each camera @param[in] InCalibrationInformation A map of calibration information for each camera @returns True if initialization is successful, False otherwise.
- L67 _public prototype_ `bool BundleAdjustment(const std::map<size_t, std::vector<double>>& InPoints3d, const std::map<size_t, std::vector<std::vector<double>>>& InCameraPoints, const std::map<size_t, std::vector<std::vector<bool>>>& InVisibility, const FBFullBundleAdjustmentParameters& InParams, double& OutMse);` — Runs the bundle adjustment process using the detected features (check RobustFeatureMatcher) @param[in] InPoints3d 3D points per frame @param[in] InCameraPoints Camera points per frame @param[in] InVisibility Visibility of camera points per frame @param[in] InParams FeatureBased Bundle Adjustment parameters with flexibility of specifying what to optimize @param[out] OutMse MSE calculated after bundle adjustment process @returns True if initialization is successful, False otherwise.
- L82 _public prototype_ `bool RunPipeline(const std::map<size_t, std::vector<double>>& InPoints3d, const std::map<size_t, std::vector<std::vector<double>>>& InCameraPoints, const std::map<size_t, std::vector<std::vector<bool>>>& InVisibility, const FBBundleAdjustmentParameters& InParams, double& OutMse);` — Runs the 3 stage pipeline process using the detected features (check RobustFeatureMatcher) @param[in] InPoints3d 3D points per frame @param[in] InCameraPoints Camera points per frame @param[in] InVisibility Visibility of camera points per frame @param[in] InParams FeatureBased Bundle Adjustment parameters @param[out] OutMse MSE calculated after bundle adjustment process @returns True if initialization is successful, False otherwise.
- L93 _public prototype_ `bool GetCalibrationInfo(std::map<std::string, OpenCVCameraD>& OutCalibrationInformation);` — Provides the current map of calibration information for each camera @param[out] OutCalibrationInformation A map of calibration information for each camera @returns True if initialization is successful, False otherwise.
- L97 _private member_ `Private* pImpl;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/api/Internals/OpenCVCamera2MetaShapeCamera.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TITAN_API_NAMESPACE`
- L14 _function_ `template <class T, class C = float> TITAN_NAMESPACE::MetaShapeCamera<T> OpenCVCamera2MetaShapeCamera(const char* InCameraName, const OpenCVCameraTemplate<C>& InCameraParameters)` (scope `TITAN_API_NAMESPACE`)
- L36 _function_ `template <class T, class C = float> static std::pair<std::string, OpenCVCameraTemplate<C>> MetaShape2OpenCVCamera(const TITAN_NAMESPACE::MetaShapeCamera<T>& InCamera)` (scope `TITAN_API_NAMESPACE`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/api/MultiCameraCalibration.h` (Private)


#### class `TITAN_API_NAMESPACE::MultiCameraCalibration`  
`class MultiCameraCalibration`  
_L16-87_
- L19 _public prototype_ `MultiCameraCalibration();`
- L20 _public prototype_ `~MultiCameraCalibration();`
- L21 _public prototype_ `MultiCameraCalibration(MultiCameraCalibration&&) = delete;`
- L22 _public prototype_ `MultiCameraCalibration(const MultiCameraCalibration&) = delete;`
- L23 _public prototype_ `MultiCameraCalibration& operator=(MultiCameraCalibration&&) = delete;`
- L24 _public prototype_ `MultiCameraCalibration& operator=(const MultiCameraCalibration&) = delete;`
- L33 _public prototype_ `bool Init(size_t InPatternWidth, size_t InPatternHeight, double InPatternSquareSize);` — Initialize multi camera calibration. @param[in] InPatternWidth The number of inner corners on the chessboard pattern wide @param[in] InPatternHeight The number of inner corners on the chessboard pattern high @param[in] InPatternSquareSize The size of the square on the chessboard pattern in cm @returns True if initialization is successful, False otherwise.
- L42 _public prototype_ `bool AddCamera(const std::string& InCameraName, int32_t InWidth, int32_t InHeight);` — Adds a camera view used for calibration @param[in] InCameraName The name of the camera view @param[in] InWidth The width of the camera image in pixels @param[in] InHeight The height of the camera image in pixels @returns True if successful, false upon any error.
- L52 _public prototype_ `bool DetectPattern(const std::string& InCameraName, const unsigned char* InImage, std::vector<double>& OutPoints, double& OutChessboardSharpness) const;` — Detects the corner points in the image of a chessboard pattern. Calculates an average sharpness of the corner points in the image @param[in] InCameraName The name of the camera view @param[in] InImage The image of the chessboard pattern @param[out] OutPoints The corner points detected in the image @param[out] OutChessboardSharpness The estimated sharpness of the corner points in the image points detected in the image @returns True if successful, false if chessboard pattern is not detected.
- L61 _public prototype_ `bool Calibrate(const std::vector<std::map<std::string, std::vector<double>>>& InCornerPointsPerCameraPerFrame, std::map<std::string, OpenCVCameraD>& OutCalibrations, double& OutMSE);` — Calibrates the intrinsics and extrinsics of the added cameras @param[in] InCornerPointsPerCameraPerFrame The detected corner points per camera per frame @param[out] OutCalibrations The calibrated cameras @param[out] OutMSE The reprojection error from the calibration @returns True if successful, false upon any error.
- L72 _public prototype_ `bool Calibrate(const std::vector<std::map<std::string, const unsigned char*>>& InImagePerCameraPerFrame, std::map<std::string, OpenCVCameraD>& OutCalibrations, double& OutMSE);` — Calibrates the intrinsics and extrinsics of the added cameras @param[in] InImagePerCameraPerFrame The images per camera per frame @param[out] OutCalibrations The calibrated cameras @param[out] OutMSE The reprojection error from the calibration @returns True if successful, false upon any error.
- L82 _public prototype_ `bool ExportCalibrations(const std::map<std::string, OpenCVCameraD>& InCalibrations, const std::string& InExportFilepath) const;` — Exports the results of Calibrate to a json file @param[in] InCalibrations The camera calibrations to be exported @param[in] InExportFilepath The filepath the calibration json will be written to @returns True if successful, false upon any error.
- L86 _private member_ `Private* m;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/api/OpenCVCamera.h` (Private)


#### struct `TITAN_API_NAMESPACE::OpenCVCameraTemplate`  
`template<typename T> struct OpenCVCameraTemplate`  
_L12-27_
- L14 _public member_ `int32_t width;`
- L15 _public member_ `int32_t height;`
- L16 _public member_ `T fx;`
- L17 _public member_ `T fy;`
- L18 _public member_ `T cx;`
- L19 _public member_ `T cy;`
- L20 _public member_ `T k1;`
- L21 _public member_ `T k2;`
- L22 _public member_ `T k3;`
- L23 _public member_ `T p1;`
- L24 _public member_ `T p2;`
- L26 _public member_ `T Extrinsics[16];` — Transform from world coordinates to camera coordinates in column-major format.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TITAN_API_NAMESPACE`
- L29 _typedef_ `using OpenCVCameraD = OpenCVCameraTemplate<double>;` (scope `TITAN_API_NAMESPACE`)
- L30 _typedef_ `using OpenCVCamera = OpenCVCameraTemplate<float>;` (scope `TITAN_API_NAMESPACE`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/api/RobustFeatureMatcher.h` (Private)


#### enum `TITAN_API_NAMESPACE::FeatureDetectorType`  
`enum class FeatureDetectorType`  
_L21-25_
- desc: Feature detector and matcher type. SlowPrecise: SIFT with BRUTEFORCE (L2 distance) - more accurate, slower. FastLessPrecise: AKAZE with BRUTEFORCE_HAMMING - faster, less accurate.
- L23 _public enumerator_ `SlowPrecise`
- L24 _public enumerator_ `FastLessPrecise`

#### class `TITAN_API_NAMESPACE::RobustFeatureMatcher`  
`class RobustFeatureMatcher`  
_L27-123_
- L30 _public prototype_ `RobustFeatureMatcher();`
- L31 _public prototype_ `~RobustFeatureMatcher();`
- L33 _public prototype_ `RobustFeatureMatcher(RobustFeatureMatcher&& InOther) noexcept;`
- L34 _public prototype_ `RobustFeatureMatcher& operator=(RobustFeatureMatcher&& InOther) noexcept;`
- L36 _public prototype_ `RobustFeatureMatcher(const RobustFeatureMatcher&) = delete;`
- L37 _public prototype_ `RobustFeatureMatcher& operator=(const RobustFeatureMatcher&) = delete;`
- L47 _public prototype_ `bool Init(const std::string& InCalibrationFilePath, double InReprojectionThreshold, double InRatioThreshold, FeatureDetectorType InFeatureDetectorType = FeatureDetectorType::SlowPrecise);` — Initializes Robust Feature Matcher using calibration json file path @param[in] InCalibrationFilePath Absolute path to the calibration json file @param[in] InReprojectionThreshold Reprojection threshold @param[in] InRatioThreshold Ratio threshold @param[in] InFeatureDetectorType SlowPrecise (SIFT) or FastLessPrecise (AKAZE) @returns True if initialization is successful, False otherwise.
- L60 _public prototype_ `bool Init(const std::map<std::string, OpenCVCameraD>& InCalibrationInformation, double InReprojectionThreshold, double InRatioThreshold, FeatureDetectorType InFeatureDetectorType = FeatureDetectorType::SlowPrecise);` — Initializes Robust Feature Matcher using calibration information from each camera @param[in] InCalibrationInformation A map of calibration information for each camera @param[in] InReprojectionThreshold Reprojection threshold @param[in] InRatioThreshold Ratio threshold @param[in] InFeatureDetectorType SlowPrecise (SIFT) or FastLessPrecise (AKAZE) @returns True if initialization is successful, False otherwise.
- L72 _public prototype_ `bool AddCamera(const std::string& InCameraName, int32_t InWidth, int32_t InHeight);` — Adds camera information @param[in] InCameraName Camera name/label/user id @param[in] InWidth Image width @param[in] InHeight Image height @returns True if successful, False otherwise
- L83 _public prototype_ `bool GetDetectedFeatures(size_t InFrame, std::vector<double>& OutPoints3d, std::vector<std::vector<double>>& OutCameraPoints, std::vector<std::vector<double>>& OutPoints3dReprojected, std::vector<std::vector<bool>>& OutVisibility);` — Provides the detected feature for a specific frame @param[in] InFrame Frame Id @param[out] OutPoints3d 3D points @param[out] OutCameraPoints Camera points @param[out] OutPoints3dReprojected Reprojected camera points @param[out] OutVisibility Visibility of camera points @returns True if successful, False otherwise
- L98 _public prototype_ `bool GetDetectedFeatures(const std::vector<size_t>& InFrames, std::map<size_t, std::vector<double>>& OutPoints3d, std::map<size_t, std::vector<std::vector<double>>>& OutCameraPoints, std::map<size_t, std::vector<std::vector<double>>>& OutPoints3dReprojected, std::map<size_t, std::vector<std::vector<bool>>>& OutVisibility);` — Provides the detected feature for an array of frames @param[in] InFrames Frames @param[out] OutPoints3d 3D points @param[out] OutCameraPoints Camera points @param[out] OutPoints3dReprojected Reprojected camera points @param[out] OutVisibility Visibility of camera points @returns True if successful, False otherwise
- L110 _public prototype_ `bool DetectFeatures(size_t InFrame, const std::vector<const unsigned char*>& InImages);` — Detects the matching features for a single frame @param[in] InFrame Frame Id @param[in] InImages An array of stereo pair frame data @returns True if successful, False otherwise
- L118 _public prototype_ `bool DetectFeatures(const std::map<size_t, std::vector<const unsigned char*>>& InImages);` — Detects the matching features an array of stereo pair frames @param[in] InImages Map containing all the frame Ids and stereo pair frame data @returns True if successful, False otherwise
- L122 _private member_ `Private* pImpl;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TITAN_API_NAMESPACE`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/AfterOpenCvHeaders.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define UE_DIRECT_HEADER_COMPILING_AFTER_OPENCV_HEADERS UE_DIRECT_HEADER_COMPILING(AfterOpenCvHeaders)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/BeforeOpenCvHeaders.h` (Private)


#### Free symbols / members of external scopes

- L4 _macro_ `#define OPENCV_HEADERS_GUARD`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/BundleAdjustmentPerformer.h` (Private)


#### class `BundleAdjustmentPerformer`  
`class BundleAdjustmentPerformer`  
_L28-54_
- L53 _public prototype_ `static std::optional<real_t> bundleAdjustScene(Object* object, std::vector<Camera*>& cameras, BAParams& params) noexcept;` — @brief Bundle adjust scene Perform bundle adjust algorithm on created scene in order to reduce reprojection error between the observed and predicted image points. @param object Pointer to calibration Object object existing on the scene. @param params BAParams object - Set of bundle adjustment params that are leading the optimization process. @param cameras Array of Camera objects existing on the scene. @return Reprojection error after optimization (in pixels).

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/CalibContext.h` (Private)


#### enum `ImageLoadType`  
`enum ImageLoadType`  
_L15-19_
- L17 _public enumerator_ `LOAD_RAW`
- L18 _public enumerator_ `LOAD_PROXY`

#### class `CalibContext`  
`class CalibContext`  
_L28-247_
- L31 _public prototype_ `virtual ~CalibContext() = default;`
- L44 _public prototype_ `virtual std::vector<CameraModel*> getCameraModels() const noexcept = 0;`
- L53 _public prototype_ `virtual std::vector<Camera*> getCameras() const noexcept = 0;`
- L62 _public prototype_ `virtual std::vector<Image*> getImages() const noexcept = 0;`
- L71 _public prototype_ `virtual Object* getObject() const noexcept = 0;`
- L80 _public prototype_ `virtual void setPatternDetectorType(PatternDetect type) noexcept = 0;`
- L89 _public prototype_ `virtual void setCalibrationType(SceneCalibrationType type) noexcept = 0;`
- L105 _public prototype_ `virtual bool calibrateScene() noexcept = 0;`
- L114 _public prototype_ `virtual void setBundleAdjustOptimParams(const BAParams& params) noexcept = 0;`
- L123 _public prototype_ `virtual real_t getMse() const noexcept = 0;`
- L147 _public prototype_ `virtual std::optional<CameraModel*> addCameraModel(const char* camModelTag, size_t imgW, size_t imgH, const std::vector<ObjectPlaneProjection*>& projections = std::vector<ObjectPlaneProjection*>(), const Eigen::Matrix3<real_t>& initK = Eigen::Matrix3<real_t>::Identity()) noexcept = 0;`
- L154 _public prototype_ `virtual void addCameraModel(CameraModel* model) noexcept = 0;`
- L174 _public prototype_ `virtual std::optional<Camera*> addCamera(const char* camTag, size_t modelIndex, const Eigen::Matrix4<real_t>& position = Eigen::Matrix4<real_t>::Identity()) noexcept = 0;`
- L177 _public prototype_ `virtual void addCamera(Camera* camera) noexcept = 0;`
- L195 _public prototype_ `virtual std::optional<Image*> addImage(const char* path, const char* modelTag, const char* camTag, int frameId, ImageLoadType loadType) noexcept = 0;`
- L197 _public prototype_ `virtual void addImage(Image* image) noexcept = 0;`
- L212 _public prototype_ `virtual std::optional<ObjectPlane*> addObjectPlane(size_t pWidth, size_t pHeight, real_t squareSize) noexcept = 0;`
- L214 _public prototype_ `virtual void addObjectPlane(ObjectPlane* plane) noexcept = 0;`
- L216 _public prototype_ `virtual void setObject(Object* object) noexcept = 0;`
- L218 _public prototype_ `virtual void setMetricUnit(const char* metricUnit) noexcept = 0;`
- L220 _public prototype_ `virtual const char* getMetricUnit() const noexcept = 0;`
- L230 _public prototype_ `static std::optional<CalibContext*> create() noexcept;`

#### struct `CalibContext::destructor`  
`struct destructor`  
_L243-246_
- L245 _public prototype_ `void operator()(CalibContext* scene) noexcept;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/Calibration.h` (Private)


#### enum `PatternDetect`  
`enum PatternDetect`  
_L28-45_
- L36 _public enumerator_ `DETECT_FAST = 0`
- L44 _public enumerator_ `DETECT_DEEP = 1`

#### enum `ImageReliability`  
`enum ImageReliability`  
_L52-57_
- L54 _public enumerator_ `NO_GRID_DETECTED = 0`
- L55 _public enumerator_ `BLURRY_GRID = 1`
- L56 _public enumerator_ `IMAGE_RELIABLE = 2`

#### enum `IntrinsicEstimation`  
`enum IntrinsicEstimation`  
_L65-93_
- L72 _public enumerator_ `K_MATRIX = 0`
- L79 _public enumerator_ `D_PARAMETERS = 1`
- L86 _public enumerator_ `D_PARAMETERS_FULL = 2`
- L92 _public enumerator_ `K_AND_D = 3`

#### class `PatternNotFound`  
`class PatternNotFound`  
_L100-101_

#### enum `SceneCalibrationType`  
`enum SceneCalibrationType`  
_L113-118_
- L115 _public enumerator_ `FULL_CALIBRATION = 0`
- L116 _public enumerator_ `FIXED_INTRINSICS = 1`
- L117 _public enumerator_ `FIXED_PROJECTIONS = 2`

#### struct `BAParams`  
`struct BAParams`  
_L120-129_
- L122 _public member_ `std::size_t iterations { 50 };`
- L123 _public member_ `std::size_t frameNum { 1 };`
- L124 _public member_ `bool optimizeIntrinsics { false };`
- L125 _public member_ `bool optimizeDistortion { false };`
- L126 _public member_ `bool optimizePoints { false };`
- L127 _public member_ `std::vector<int> fixedIntrinsicIndices {};`
- L128 _public member_ `std::vector<int> fixedDistortionIndices {};`

#### struct `FBBAParams`  
`struct FBBAParams : public BAParams`  
_L131-139_
- inherits: `BAParams`
- L133 _public member_ `bool fixedScale { true };`
- L136 _public member_ `std::vector<std::vector<std::vector<Eigen::Vector2<real_t>>>> referencePoints;` — Two points per camera for every frame (using vector instead of pair)
- L138 _public member_ `real_t referenceDistance = 0.0;`

#### Free symbols / members of external scopes

- L142 _prototype_ `checkFrameReliability(const Eigen::MatrixX<real_t>& image, int patternWidth, int patternHeight, double sharpnessThreshold);`
- L144 _prototype_ `std::optional<Eigen::MatrixX<real_t>> loadImage(const char* path);`
- L175 _prototype_ `std::optional<Eigen::MatrixX<real_t>> detectPattern(const Eigen::MatrixX<real_t>& image, std::size_t p_w, std::size_t p_h, real_t sq_size, PatternDetect type);`
- L204 _prototype_ `std::vector<Eigen::MatrixX<real_t>> detectMultiplePatterns(const Eigen::MatrixX<real_t>& image, const std::vector<std::size_t>& p_w, const std::vector<std::size_t>& p_h, const std::vector<real_t>& sq_size, PatternDetect type);`
- L253 _prototype_ `calibrateIntrinsics(const std::vector<Eigen::MatrixX<real_t>>& points2d, const std::vector<Eigen::MatrixX<real_t>>& points3d, Eigen::Matrix3<real_t>& intrinsics, Eigen::VectorX<real_t>& distortion, std::size_t im_w, std::size_t im_h, IntrinsicEstimation type);`
- L305 _prototype_ `calibrateIntrinsics(const std::vector<Eigen::MatrixX<real_t>>& points2d, const Eigen::MatrixX<real_t>& points3d, Eigen::Matrix3<real_t>& intrinsics, Eigen::VectorX<real_t>& distortion, std::size_t im_w, std::size_t im_h);`
- L347 _prototype_ `calibrateIntrinsics(const std::vector<Eigen::MatrixX<real_t>>& points2d, const std::vector<Eigen::MatrixX<real_t>>& points3d, const Eigen::VectorX<std::size_t>& p_idx, Eigen::Matrix3<real_t>& intrinsics, Eigen::VectorX<real_t>& distortion, std::size_t im_w, std::size_t im_h);`
- L393 _prototype_ `calibrateExtrinsics(const Eigen::MatrixX<real_t>& points2d, const Eigen::MatrixX<real_t>& points3d, const Eigen::Matrix3<real_t>& intrinsics, const Eigen::VectorX<real_t>& distortion, Eigen::Matrix4<real_t>& T);`
- L446 _prototype_ `calibrateStereoExtrinsics(const std::vector<Eigen::MatrixX<real_t>>& points2d_1, const std::vector<Eigen::MatrixX<real_t>>& points2d_2, const std::vector<Eigen::MatrixX<real_t>>& points3d, const Eigen::Matrix3<real_t>& intrinsics, const Eigen::VectorX<real_t>& distortion, Eigen::Matrix4<real_t>& T, std::size_t im_w, std::size_t im_h);`
- L544 _prototype_ `generate3dPatternPoints(std::size_t p_w, std::size_t p_h, real_t sq_size);`
- L583 _prototype_ `estimateRelativePatternTransform(const Eigen::MatrixX<real_t>& p1_points_2d, const Eigen::MatrixX<real_t>& p1_points_3d, const Eigen::MatrixX<real_t>& p2_points_2d, const Eigen::MatrixX<real_t>& p2_points_3d, const Eigen::Matrix3<real_t>& intrinsics, const Eigen::VectorX<real_t>& distortion, Eigen::Matrix4<real_t>& T);`
- L613 _prototype_ `projectPointOnImagePlane(const Eigen::VectorX<real_t>& point3d, const Eigen::Matrix3<real_t>& intrinsics, const Eigen::VectorX<real_t>& distortion, const Eigen::Matrix4<real_t>& T);`
- L641 _prototype_ `void projectPointsOnImagePlane( const Eigen::MatrixX<real_t>& points3d, const Eigen::Matrix3<real_t>& intrinsics, const Eigen::VectorX<real_t>& distortion, const Eigen::Matrix4<real_t>& T, Eigen::MatrixX<real_t>& outPoints2d);`
- L679 _prototype_ `bundleAdjustment(const Eigen::MatrixX<real_t>& points, std::vector<Eigen::Matrix4<real_t>>& objTransform, const std::vector<std::vector<Eigen::MatrixX<real_t>>>& imagePoints, const std::vector<std::vector<bool>>& visibility, std::vector<Eigen::Matrix3<real_t>>& cameraMatrix, std::vector<Eigen::Matrix4<real_t>>& cameraTransform, std::vector<Eigen::VectorX<real_t>>& distCoeffs, const BAParams& params);`
- L688 _prototype_ `Eigen::MatrixX<real_t> triangulatePointsForFrame(const std::vector<std::vector<Eigen::Vector2<real_t>>>& referencePoints, const std::vector<Eigen::Matrix3<real_t>>& cameraMatrix, const std::vector<Eigen::Matrix4<real_t>>& cameraTransform);`
- L723 _prototype_ `std::optional<real_t> featureBundleAdjustment(std::vector<Eigen::MatrixX<real_t>>& points, const std::vector<std::vector<Eigen::MatrixX<real_t>>>& imagePoints, const std::vector<std::vector<std::vector<bool>>>& visibility, std::vector<Eigen::Matrix3<real_t>>& cameraMatrix, std::vector<Eigen::Matrix4<real_t>>& cameraTransform, std::vector<Eigen::VectorX<real_t>>& distCoeffs, const FBBAParams& params);` — CALIB_API TODO this is the core module which is a static library, external APIs should be done separately. Is this correct?

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/CameraManager.h` (Private)


#### class `CameraManager`  
`class CameraManager`  
_L22-45_
- L44 _public prototype_ `static std::vector<Camera*> groupCamerasByPattern(ObjectPlane* plane, const std::vector<Camera*>& input_cameras) noexcept;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/CameraModel.h` (Private)


#### class `CameraModel`  
`class CameraModel`  
_L44-213_
- L47 _public prototype_ `virtual ~CameraModel() = default;`
- L60 _public prototype_ `virtual std::optional<real_t> calibrateIntrinsics() = 0;`
- L68 _public prototype_ `virtual const Eigen::Matrix3<real_t>& getIntrinsicMatrix() const = 0;`
- L76 _public prototype_ `virtual const Eigen::VectorX<real_t>& getDistortionParams() const = 0;`
- L91 _public prototype_ `virtual void setProjectionData(const std::vector<ObjectPlaneProjection*>& projections) = 0;`
- L106 _public prototype_ `virtual void setIntrinsicMatrix(const Eigen::Matrix3<real_t>& K) = 0;`
- L121 _public prototype_ `virtual void setDistortionParams(const Eigen::VectorX<real_t>& D) = 0;`
- L133 _public prototype_ `virtual const std::vector<ObjectPlaneProjection*>& getProjectionData() const = 0;`
- L142 _public prototype_ `virtual const char* getTag() const = 0;`
- L151 _public prototype_ `virtual size_t getFrameWidth() const = 0;`
- L160 _public prototype_ `virtual size_t getFrameHeight() const = 0;`
- L192 _public prototype_ `static std::optional<CameraModel*> create(const char* camModelTag, size_t imgW, size_t imgH, const std::vector<ObjectPlaneProjection*>& projections = std::vector<ObjectPlaneProjection*>(), const Eigen::Matrix3<real_t>& initK = Eigen::Matrix3<real_t>::Identity());`

#### struct `CameraModel::destructor`  
`struct destructor`  
_L209-212_
- L211 _public prototype_ `void operator()(CameraModel* model);`

#### class `Camera`  
`class Camera`  
_L216-369_
- L219 _public prototype_ `virtual ~Camera() = default;`
- L235 _public prototype_ `virtual CameraModel* getCameraModel() const = 0;`
- L244 _public prototype_ `virtual const char* getTag() const = 0;`
- L253 _public prototype_ `virtual bool calibrateExtrinsics() = 0;`
- L268 _public prototype_ `virtual Eigen::Matrix4<real_t> calibrateExtrinsicsStereo(Camera* other) = 0;`
- L270 _public prototype_ `virtual void setCameraModel(CameraModel& model) = 0;`
- L284 _public prototype_ `virtual void setWorldPosition(const Eigen::Matrix4<real_t>& transform) = 0;`
- L298 _public prototype_ `virtual int isPlaneVisible(ObjectPlane& plane) const = 0;`
- L299 _public prototype_ `virtual int isPlaneVisibleOnFrame(ObjectPlane& plane, size_t frame) const = 0;`
- L309 _public prototype_ `virtual const Eigen::Matrix4<real_t>& getWorldPosition() const = 0;`
- L321 _public prototype_ `virtual const std::vector<ObjectPlaneProjection*>& getProjectionData() const = 0;`

#### struct `Camera::destructor`  
`struct destructor`  
_L365-368_
- L367 _public prototype_ `void operator()(Camera* camera);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/CoordinateSystemAligner.h` (Private)


#### class `CoordinateSystemAligner`  
`class CoordinateSystemAligner`  
_L24-83_
- L27 _public prototype_ `virtual ~CoordinateSystemAligner() = default;`
- L49 _public prototype_ `static void alignCoordinateSystems(ObjectPlane* ref, ObjectPlane* al, std::vector<Camera*>& cameras) noexcept;`
- L67 _public prototype_ `static bool neighborhoodCheck(ObjectPlane* ref, ObjectPlane* al, std::vector<Camera*>& cameras) noexcept;`
- L82 _public prototype_ `static void transformCamerasGlobal(ObjectPlane* plane, std::vector<Camera*>& cameras) noexcept;`

#### Free symbols / members of external scopes

- L86 _prototype_ `Eigen::Matrix4<real_t> estimatePatternTransform(Camera* referent, ObjectPlane* plane, size_t refFrame, size_t alFrame);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/DHInputOutput.h` (Private)


#### Free symbols / members of external scopes

- L10 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::calib) template <class T> std::vector<Camera*> loadCamerasJson(const std::string& path);`
- L16 _prototype_ `template <class T> std::vector<Camera*> loadCamerasXml(const std::string& path);`
- L19 _prototype_ `template <class T> void writeCamerasJson(const std::string& path, const std::vector<Camera*>& cameras, bool setOriginInFirstCamera);`
- L22 _prototype_ `template <class T> void writeCamerasXml(const std::string& path, const std::vector<Camera*>& cameras, bool setOriginInFirstCamera);`
- L25 _prototype_ `template <class T> void writeCamerasRealityCapture(const std::string& path, const std::vector<TITAN_NAMESPACE::MetaShapeCamera<T>>& cameras, int type);`
- L28 _prototype_ `template <class T> void writeCameraRealityCapture(const std::string& path, const TITAN_NAMESPACE::MetaShapeCamera<T>& camera, int type);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/Defs.h` (Private)


#### Free symbols / members of external scopes

- L13 _macro_ `#define CALIB_STRINGIZE(Token) #Token`
- L17 _macro_ `#define CALIB_PUSH_MACRO(name) _Pragma(CALIB_STRINGIZE(push_macro(name)))`
- L18 _macro_ `#define CALIB_POP_MACRO(name) _Pragma(CALIB_STRINGIZE(pop_macro(name)))`
- L22 _macro_ `#define CALIB_PUSH_MACRO(name) __pragma(push_macro(name))`
- L23 _macro_ `#define CALIB_POP_MACRO(name) __pragma(pop_macro(name))`
- L32 _macro_ `#define CALIB_API`
- L49 _namespace_ `namespace mvg`
- L52 _macro_ `#define real_t double`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/Error.h` (Private)


#### enum `(anonymous)`  
``  
_L6-12_

#### Free symbols / members of external scopes

- L7 _enumerator_ `CALIB_OK = 0` (scope `__anon48cd83490103`)
- L8 _enumerator_ `CALIB_ERROR = -1` (scope `__anon48cd83490103`)
- L9 _enumerator_ `CALIB_INVALID_ARGUMENT = 1` (scope `__anon48cd83490103`)
- L10 _enumerator_ `CALIB_INVALID_HANDLE = 2` (scope `__anon48cd83490103`)
- L11 _enumerator_ `CALIB_DETECT_PATTERN_FAILED = 3` (scope `__anon48cd83490103`)
- L12 _typedef_ `} CalibStatus;`
- L14 _prototype_ `void calibPrintLastError(const char* message);`
- L16 _prototype_ `const char* calibGetLastErrorMessage();`
- L18 _prototype_ `CalibStatus calibGetLastErrorCode();`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/Image.h` (Private)


#### class `Image`  
`class Image`  
_L33-146_
- L36 _public prototype_ `virtual ~Image() = default;`
- L55 _public prototype_ `virtual std::optional<Eigen::MatrixX<real_t>> getPixels() = 0;`
- L64 _public prototype_ `virtual const char* getModelTag() const = 0;`
- L73 _public prototype_ `virtual const char* getCameraTag() const = 0;`
- L82 _public prototype_ `virtual size_t getFrameId() const = 0;`
- L107 _public prototype_ `static std::optional<Image*> loadRaw(const char* path, const char* modelTag, const char* camTag, size_t frameId);`
- L129 _public prototype_ `static std::optional<Image*> loadProxy(const char* path, const char* modelTag, const char* camTag, size_t frameId);`

#### struct `Image::destructor`  
`struct destructor`  
_L142-145_
- L144 _public prototype_ `void operator()(Image* image);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/Object.h` (Private)


#### class `ObjectPlane`  
`class ObjectPlane`  
_L28-174_
- L31 _public prototype_ `virtual ~ObjectPlane() = default;`
- L48 _public prototype_ `virtual Eigen::Vector2i getPatternShape() const = 0;`
- L61 _public prototype_ `virtual const Eigen::MatrixX<real_t>& getLocalPoints() const = 0;`
- L74 _public prototype_ `virtual bool hasProjections() const = 0;`
- L86 _public prototype_ `virtual Eigen::MatrixX<real_t> getGlobalPoints(size_t atFrame = 0) const = 0;` — @brief Get global points. Get 3D points of a pattern in global coordinate system. @return nitro::Matrix (number of points, 3) where each matrix row represents one 3D point. Point coordinates are stored in collumns as (x, y, z).
- L97 _public prototype_ `virtual real_t getSquareSize() const = 0;`
- L111 _public prototype_ `virtual void setTransform(const Eigen::Matrix4<real_t>& transform, size_t atFrame = 0) = 0;`
- L113 _public prototype_ `virtual void setNumberOfFrames(size_t numberOfFrames) = 0;`
- L124 _public prototype_ `virtual const Eigen::Matrix4<real_t>& getTransform(size_t atFrame = 0) const = 0;`
- L135 _public function_ `virtual bool isInternalType() const`
- L157 _public prototype_ `std::optional<ObjectPlane*> create(size_t pWidth, size_t pHeight, real_t squareSize);`

#### struct `ObjectPlane::destructor`  
`struct destructor`  
_L170-173_
- L172 _public prototype_ `void operator()(ObjectPlane* objectPlane);`

#### class `Object`  
`class Object`  
_L177-270_
- L180 _public prototype_ `virtual ~Object() = default;`
- L195 _public prototype_ `virtual size_t getPlaneCount() const = 0;`
- L209 _public prototype_ `virtual void addObjectPlane(ObjectPlane* plane) = 0;`
- L223 _public prototype_ `virtual ObjectPlane* getObjectPlane(size_t planeId) const = 0;`
- L237 _public prototype_ `virtual void sortPlanes() = 0;`
- L253 _public prototype_ `Object* create(const Eigen::Matrix4<real_t>& transform = Eigen::Matrix4<real_t>::Identity());`

#### struct `Object::destructor`  
`struct destructor`  
_L266-269_
- L268 _public prototype_ `void operator()(Object* object);`

#### class `ObjectPlaneProjection`  
`class ObjectPlaneProjection`  
_L273-409_
- L276 _public prototype_ `virtual ~ObjectPlaneProjection() = default;`
- L292 _public prototype_ `virtual ObjectPlane* getObjectPlane() const = 0;`
- L307 _public prototype_ `virtual void setProjectionPoints(const Eigen::MatrixX<real_t>& points) = 0;`
- L319 _public prototype_ `virtual const Eigen::MatrixX<real_t>& getProjectionPoints() const = 0;`
- L333 _public prototype_ `virtual void setImage(Image* image) = 0;`
- L345 _public prototype_ `virtual Image* getImage() const = 0;`
- L356 _public prototype_ `virtual const Eigen::Matrix4<real_t> getTransform() const = 0;`
- L367 _public prototype_ `virtual void setTransform(const Eigen::Matrix4<real_t>& transform) = 0;`
- L391 _public prototype_ `static ObjectPlaneProjection* create(ObjectPlane* plane, Image* image = nullptr, const Eigen::MatrixX<real_t>& points = Eigen::Matrix2<real_t>::Zero());`

#### struct `ObjectPlaneProjection::destructor`  
`struct destructor`  
_L405-408_
- L407 _public prototype_ `void operator()(ObjectPlaneProjection* objectPlaneProj);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/ObjectDetector.h` (Private)


#### class `ObjectDetector`  
`class ObjectDetector`  
_L38-122_
- L41 _public prototype_ `virtual ~ObjectDetector() = default;`
- L63 _public prototype_ `virtual std::optional<std::vector<ObjectPlaneProjection*>> tryDetect() = 0;`
- L86 _public prototype_ `static ObjectDetector* create(Image* image, Object* object, PatternDetect type);`
- L105 _public prototype_ `static ObjectDetector* create(const std::vector<Image*>& images, Object* object, PatternDetect type);`

#### struct `ObjectDetector::destructor`  
`struct destructor`  
_L118-121_
- L120 _public prototype_ `void operator()(ObjectDetector* detector);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/include/calib/Utilities.h` (Private)


#### Free symbols / members of external scopes

- L15 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::calib) void splitRotationAndTranslation(const Eigen::Matrix4<real_t>& transformation, Eigen::Matrix3<real_t>& rotation, Eigen::Vector3<real_t>& translation);`
- L47 _prototype_ `void inverseGeometricTransform( Eigen::Matrix4<real_t>& transformation);`
- L64 _prototype_ `bool pointFromRow3dHomogenious( const Eigen::MatrixX<real_t>& matrix, size_t row, Eigen::Vector4<real_t>& point);`
- L83 _prototype_ `void pointFromRow3d( const Eigen::MatrixX<real_t>& matrix, size_t row, Eigen::Vector3<real_t>& point);`
- L102 _prototype_ `void rowFromPoint3d( Eigen::MatrixX<real_t>& matrix, size_t row, const Eigen::VectorX<real_t>& point);`
- L121 _prototype_ `void pointFromRow2dHomogenious( const Eigen::MatrixX<real_t>& matrix, size_t row, Eigen::Vector3<real_t>& point);`
- L140 _prototype_ `void pointFromRow2d( const Eigen::MatrixX<real_t>& matrix, size_t row, Eigen::Vector2<real_t>& point);`
- L159 _prototype_ `void rowFromPoint2d( Eigen::MatrixX<real_t>& matrix, size_t row, const Eigen::VectorX<real_t>& point);`
- L179 _prototype_ `makeTransformationMatrix(const Eigen::Matrix3<real_t>& rotation, const Eigen::Vector3<real_t>& translation);`
- L192 _prototype_ `rotationMatrixToQuaternion(const Eigen::Matrix3<real_t>& rotation);`
- L205 _prototype_ `quaternionToRotationMatrix(const Eigen::Vector4<real_t>& quaternion);`
- L218 _prototype_ `quaternionToNormQuat(const Eigen::Vector4<real_t>& quat);`
- L231 _prototype_ `normQuatToQuaternion(const Eigen::Vector3<real_t>& normQuat);`
- L244 _prototype_ `vectorToQuaternion(const Eigen::Vector3<real_t>& vec);`
- L257 _prototype_ `averageTransformationMatrices(const std::vector<Eigen::Matrix4<real_t>>& transformations);`
- L273 _prototype_ `quaternionMultFast(const Eigen::Vector4<real_t>& q1, const Eigen::Vector4<real_t>& q2);`
- L300 _prototype_ `std::optional<Eigen::MatrixX<real_t>> triangulatePoint(const Eigen::Vector2<real_t>& p2d1, const Eigen::Vector2<real_t>& p2d2, const Eigen::Matrix3<real_t>& K1, const Eigen::Matrix3<real_t>& K2, const Eigen::Matrix4<real_t>& T1, const Eigen::Matrix4<real_t>& T2);`
- L327 _prototype_ `std::optional<Eigen::MatrixX<real_t>> triangulatePoints(const Eigen::MatrixX<real_t>& p2d1, const Eigen::MatrixX<real_t>& p2d2, const Eigen::Matrix3<real_t>& K1, const Eigen::Matrix3<real_t>& K2, const Eigen::Matrix4<real_t>& T1, const Eigen::Matrix4<real_t>& T2);`
- L341 _prototype_ `calculateMeanSquaredError(const Eigen::MatrixX<real_t>& lhs, const Eigen::MatrixX<real_t>& rhs);`
- L343 _prototype_ `void transformPoints( Eigen::MatrixX<real_t>& points, const Eigen::Matrix4<real_t>& transform);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/src/ErrorInternal.h` (Private)


#### Free symbols / members of external scopes

- L14 _macro_ `#define CV_CALL_CATCH(call, ExceptionType) \`
- L22 _macro_ `#define CALIB_ASSERT(cond, message, errorCode) \`
- L28 _macro_ `#define REPORT_ERROR(message, errorCode) \`
- L32 _macro_ `#define CALIB_CHECK_INVALID_HANDLE(handle) CALIB_ASSERT(handle != nullptr, \`
- L35 _macro_ `#define CALIB_CHECK_INVALID_ARGUMENT(cond) CALIB_ASSERT(cond, \`
- L38 _macro_ `#define CALIB_EXPECT_VALID(expected, error) \`
- L41 _prototype_ `void calibSetLastError(const std::string& errorMessage, CalibStatus error);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/calib/src/ObjectImpl.h` (Private)


#### struct `ObjectPlaneInternal`  
`struct ObjectPlaneInternal : ObjectPlane`  
_L10-15_
- inherits: `ObjectPlane`
- L12 _public prototype_ `virtual void setProjectionFlag(bool) = 0;`
- L14 _public function_ `virtual bool isInternalType() const override`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/Algorithm.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L29 _function_ `template <class T> bool ConcatenateVectorsWithMatchingEndPointsAndUnknownDirection(const std::vector<T>& vector1, const std::vector<T>& vector2, std::vector<T>& mergedVector)` — Concatenates two vectors with undown direction along one matching end point (removing the duplicate). Fails if there is no matching end point or if either vector is empty.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/Common.h` (Private)


#### struct `always_false`  
`template <class T> struct always_false : std::false_type`  
_L13-13_
- inherits: `std::false_type`

#### Free symbols / members of external scopes

- L8 _macro_ `#define CARBON_SUPPRESS_UNUSED(x) (void)(x)`
- L19 _function_ `inline std::string from_u8string(const std::string &s)` — @brief support converting u8string to string as of C++20 based on https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1423r2.html: "Use explicit conversion functions"
- L24 _function_ `inline std::string from_u8string(std::string &&s)`
- L30 _function_ `inline std::string from_u8string(const std::u8string &s)`
- L36 _macro_ `#define FROM_U8STRING(x) TITAN_NAMESPACE::from_u8string(x).c_str()`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/Math.h` (Private)
_(no declarations extracted)_

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/common/Common.h` (Private)
_(no declarations extracted)_

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/common/Defs.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define CARBON_NAMESPACE_BEGIN(name) namespace name {`
- L6 _macro_ `#define CARBON_NAMESPACE_END(name) }`
- L9 _macro_ `#define TITAN_NAMESPACE epic::nls`
- L13 _macro_ `#define CARBON_SUPRESS_MS_WARNING(Warning)`
- L14 _macro_ `#define CARBON_REENABLE_MS_WARNING`
- L18 _macro_ `#define CARBON_DISABLE_EIGEN_WARNINGS THIRD_PARTY_INCLUDES_START // use UE warning suppression if we can`
- L19 _macro_ `#define CARBON_RENABLE_WARNINGS THIRD_PARTY_INCLUDES_END`
- L21 _macro_ `#define CARBON_DISABLE_EIGEN_WARNINGS \`
- L25 _macro_ `#define CARBON_RENABLE_WARNINGS \`
- L34 _macro_ `#define CARBON_RENABLE_WARNINGS __pragma(warning(pop))`
- L35 _macro_ `#define CARBON_SUPRESS_MS_WARNING(Warning) \`
- L38 _macro_ `#define CARBON_REENABLE_MS_WARNING CARBON_RENABLE_WARNINGS`
- L44 _macro_ `#define CARBON_RENABLE_WARNINGS _Pragma("GCC diagnostic pop")`
- L48 _macro_ `#define CARBON_DISABLE_EIGEN_WARNINGS`
- L49 _macro_ `#define CARBON_RENABLE_WARNINGS`
- L58 _macro_ `#define DEBUG_PRECONDITION(condition, message) (void)(condition)`
- L60 _macro_ `#define DEBUG_PRECONDITION(condition, message) if (!(condition)) throw std::runtime_error(message)`
- L66 _macro_ `#define EPIC_CARBON_API` — API symbol export import preprocessor defines. Currently Carbon is forced to be a static library, so no need for export/import defines
- L82 _macro_ `#define CARBON_PI 3.14159265358979323846 // pi` — CONSTANTS
- L84 _macro_ `#define CARBON_CRITICAL(...) { \`
- L92 _macro_ `#define CARBON_PRECONDITION(condition, ...) if (!(condition)) { \`
- L98 _macro_ `#define CARBON_POSTCONDITION(condition, ...) if (!(condition)) { \`
- L104 _macro_ `#define CARBON_ASSERT(condition, ...) if (!(condition)) { \`
- L111 _macro_ `#define CARBON_PRECONDITION(condition, ...) (void)(condition)`
- L112 _macro_ `#define CARBON_POSTCONDITION(condition, ...) (void)(condition)`
- L113 _macro_ `#define CARBON_ASSERT(condition, ...) (void)(condition)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/common/EigenDenseBackwardsCompatible.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Eigen`
- L15 _typedef_ `template <typename T> using Matrix2 = Matrix<T, 2, 2>;` (scope `Eigen`)
- L18 _typedef_ `template <typename T> using Matrix2X = Matrix<T, 2, Dynamic>;` (scope `Eigen`)
- L21 _typedef_ `template <typename T> using Matrix3 = Matrix<T, 3, 3>;` (scope `Eigen`)
- L24 _typedef_ `template <typename T> using Matrix3X = Matrix<T, 3, Dynamic>;` (scope `Eigen`)
- L27 _typedef_ `template <typename T> using Matrix4 = Matrix<T, 4, 4>;` (scope `Eigen`)
- L30 _typedef_ `template <typename T> using Matrix4X = Matrix<T, 4, Dynamic>;` (scope `Eigen`)
- L33 _typedef_ `template <typename T> using MatrixX = Matrix<T, Dynamic, Dynamic>;` (scope `Eigen`)
- L36 _typedef_ `template <typename T> using MatrixX2 = Matrix<T, Dynamic, 2>;` (scope `Eigen`)
- L39 _typedef_ `template <typename T> using MatrixX3 = Matrix<T, Dynamic, 3>;` (scope `Eigen`)
- L42 _typedef_ `template <typename T> using MatrixX4 = Matrix<T, Dynamic, 4>;` (scope `Eigen`)
- L45 _typedef_ `template <typename T, int Size> using RowVector = Matrix<T, 1, Size>;` (scope `Eigen`)
- L48 _typedef_ `template <typename T> using RowVector2 = RowVector<T, 2>;` (scope `Eigen`)
- L51 _typedef_ `template <typename T> using RowVector3 = RowVector<T, 3>;` (scope `Eigen`)
- L54 _typedef_ `template <typename T> using RowVector4 = RowVector<T, 4>;` (scope `Eigen`)
- L57 _typedef_ `template <typename T> using RowVectorX = RowVector<T, Dynamic>;` (scope `Eigen`)
- L60 _typedef_ `template <typename T, int Size> using Vector = Matrix<T, Size, 1>;` (scope `Eigen`)
- L63 _typedef_ `template <typename T> using Vector2 = Vector<T, 2>;` (scope `Eigen`)
- L66 _typedef_ `template <typename T> using Vector3 = Vector<T, 3>;` (scope `Eigen`)
- L69 _typedef_ `template <typename T> using Vector4 = Vector<T, 4>;` (scope `Eigen`)
- L72 _typedef_ `template <typename T> using VectorX = Vector<T, Dynamic>;` (scope `Eigen`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/common/External.h` (Private)
_(no declarations extracted)_

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/common/Format.h` (Private)


#### Free symbols / members of external scopes

- L22 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::fmt)`
- L41 _function_ `template<> inline std::string to_string<bool>(const bool& value)` — ! Specialization for bool type
- L48 _function_ `template<typename ... Types> std::string format(Types&& ... args)`
- L53 _function_ `template<typename ... Types> void print(Types&& ... args)`
- L60 _function_ `template<typename ... Types> std::string BasicFormat(const std::string& str, Types&& ... args)`
- L88 _function_ `inline std::string format()`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/common/Integration.h` (Private)


#### struct `Integration`  
`struct Integration`  
_L13-17_
- desc: @Brief Integration structure wraps objects that implements core functionalities from the external client.
- L15 _public member_ `Logger logger{};`
- L16 _public member_ `pma::MemoryResource* memoryResource{};`

#### Free symbols / members of external scopes

- L24 _prototype_ `Integration& GetIntegrationParams();` — @Brief Gets/Sets Integration struct to be used in the core tech lib @returns Integraton parameters - singleton instance.
- L29 _macro_ `#define LOGGER TITAN_NAMESPACE::GetIntegrationParams().logger` — Singletone instances - recommended usage is providing object through DI
- L30 _macro_ `#define MEM_RESOURCE TITAN_NAMESPACE::GetIntegrationParams().memoryResource`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/common/Log.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L26 _macro_ `#define LOG_INTERNAL(LogLevel,...) LOGGER.Log(LogLevel, "(%s, l%d): %s\n\0", TITAN_NAMESPACE::ConstexprBasename(__FILE__), static_cast<int>(__LINE__),\`
- L29 _macro_ `#define LOG_CONDITION(format,condition,args) LOGGER.Log(TITAN_NAMESPACE::LogLevel::ERR, format, condition, TITAN_NAMESPACE::ConstexprBasename(__FILE__), static_cast<int>(__LINE__),args)`
- L31 _macro_ `#define LOG_INFO(...) LOGGER.Log(TITAN_NAMESPACE::LogLevel::INFO, "%s\n\0", TITAN_NAMESPACE::fmt::format(__VA_ARGS__).c_str())`
- L33 _macro_ `#define LOG_WARNING(...) LOG_INTERNAL(TITAN_NAMESPACE::LogLevel::WARNING, __VA_ARGS__)`
- L35 _macro_ `#define LOG_ERROR(...) LOG_INTERNAL(TITAN_NAMESPACE::LogLevel::ERR, __VA_ARGS__)`
- L37 _macro_ `#define LOG_CRITICAL(...) LOG_INTERNAL(TITAN_NAMESPACE::LogLevel::CRITICAL, __VA_ARGS__);`
- L39 _macro_ `#define LOG_VERBOSE(...) LOG_INTERNAL(TITAN_NAMESPACE::LogLevel::VERBOSE, __VA_ARGS__)`
- L41 _macro_ `#define LOG_FATAL(...) LOG_INTERNAL(TITAN_NAMESPACE::LogLevel::FATAL, __VA_ARGS__)`
- L43 _macro_ `#define LOG_PRECONDITION(failedPrecondition, ...) LOG_CONDITION("FAILED PRECONDITION - %s in (%s, l%d): %s\n\0", TITAN_NAMESPACE::fmt::to_string(failedPrecondition).c_str(), TITAN_NAMESPACE::fmt::format(__VA_ARGS__).c_str());`
- L45 _macro_ `#define LOG_POSTCONDITION(failedPostcondition, ...) LOG_CONDITION("FAILED POSTCONDITION - %s in (%s, l%d): %s\n\0", TITAN_NAMESPACE::fmt::to_string(failedPostcondition).c_str(), TITAN_NAMESPACE::fmt::format(__VA_ARGS__).c_str());`
- L47 _macro_ `#define LOG_ASSERT(failedAssert, ...) LOG_CONDITION("FAILED ASSERT - %s in (%s, l%d): %s\n\0", TITAN_NAMESPACE::fmt::to_string(failedAssert).c_str(), TITAN_NAMESPACE::fmt::format(__VA_ARGS__).c_str());`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/common/Logger.h` (Private)


#### enum `LogLevel`  
`enum class LogLevel`  
_L9-18_
- L11 _public enumerator_ `VERBOSE = 0`
- L12 _public enumerator_ `WARNING = 1`
- L13 _public enumerator_ `INFO = 2`
- L14 _public enumerator_ `DEBUG = 3`
- L15 _public enumerator_ `ERR = 4`
- L16 _public enumerator_ `CRITICAL = 5`
- L17 _public enumerator_ `FATAL = 6`

#### class `Logger`  
`class Logger final`  
_L27-77_
- desc: @Brief Logger class is simple logging functionality wrapper. Its main purpose is integration of logging functionality from external system (for example UE)
- L34 _public prototype_ `Logger() noexcept;` — Default Constructor.
- L42 _public prototype_ `Logger(LogFunction logFunction_) noexcept;` — Constructor. @param[in] logFunction_ logging function provided from the external system. Initially set to DefaultLogger.
- L47 _public prototype_ `~Logger() noexcept;` — Destructor.
- L61 _public function_ `template<typename ...ARGS> void Log(LogLevel logLevel, const char* format, ARGS&& ...params)` — Send message to log system. @param[in] logLevel Log level of message. @param[in] format format string. @param[in] params multiple parameters to be embeded in the format string. @note C style formatting syntax needs to be applied
- L70 _public function_ `void SetVerbose(bool enable)` — Set whether to log verbose output
- L73 _private prototype_ `static void DefaultLogger(LogLevel logLevel, const char* format, ...);`
- L75 _private member_ `LogFunction m_logFunction{ DefaultLogger };`
- L76 _private member_ `bool m_logVerbose{true};`

#### Free symbols / members of external scopes

- L20 _typedef_ `using LogFunction = void(*)(LogLevel , const char* , ...);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/common/Pimpl.h` (Private)


#### class `Pimpl`  
`template <class T, class Deleter = std::default_delete<T>> class Pimpl`  
_L21-41_
- desc: Most basic const-forwarding pointer wrapper for use with the Pimpl programming technique. https://en.cppreference.com/w/cpp/language/pimpl. Use a custom delete Deleter = void(*)(T*) when the class does not have a destructor. E.g. in the cpp class use Pimpl(std::unique_ptr<T, void(*)(T*)>(new T, [](T* ptr) {std::default_delete<T>()(ptr);})) @warning does not work with class that have a DLL interface.
- L24 _public function_ `Pimpl(std::unique_ptr<T, Deleter>&& obj) : m_ptr(std::move(obj))`
- L25 _public function_ `Pimpl(T* ptr) : m_ptr(ptr)`
- L26 _public prototype_ `~Pimpl() = default;`
- L27 _public prototype_ `Pimpl(Pimpl&&) = default;`
- L28 _public prototype_ `Pimpl(const Pimpl&) = delete;`
- L29 _public prototype_ `Pimpl& operator=(Pimpl&&) = default;`
- L30 _public prototype_ `Pimpl& operator=(const Pimpl&) = delete;`
- L32 _public function_ `constexpr T* operator->()`
- L33 _public function_ `constexpr const T* operator->() const`
- L34 _public function_ `constexpr T& operator*()`
- L35 _public function_ `constexpr const T& operator*() const`
- L36 _public function_ `constexpr T* Get()`
- L37 _public function_ `constexpr const T* Get() const`
- L40 _private member_ `std::unique_ptr<T, Deleter> m_ptr;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/data/CameraModelOpenCV.h` (Private)


#### class `CameraModelOpenCV`  
`template<class T> class CameraModelOpenCV : public CameraModelPinhole<T>`  
_L30-79_
- inherits: `CameraModelPinhole<T>`
- L46 _public prototype_ `CameraModelOpenCV() noexcept;`
- L56 _public prototype_ `virtual ~CameraModelOpenCV() noexcept;`
- L65 _public prototype_ `const Eigen::Vector<T, 5>& GetDistortionParams() const noexcept;`
- L74 _public prototype_ `void SetDistortionParams(const Eigen::Vector<T, 5>& distortion) noexcept;`
- L78 _private member_ `Eigen::Vector<T, 5> m_distortion;` — OpenCV format distortion parameters (k1, k2, p1, p2, k3)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/data/CameraModelPinhole.h` (Private)


#### class `CameraModelPinhole`  
`template<class T> class CameraModelPinhole`  
_L35-192_
- L50 _public prototype_ `CameraModelPinhole() noexcept;`
- L60 _public prototype_ `virtual ~CameraModelPinhole() noexcept;`
- L68 _public prototype_ `const Eigen::Matrix<T, 3, 3, Eigen::DontAlign>& GetIntrinsics() const noexcept;`
- L79 _public prototype_ `void SetIntrinsics(const Eigen::Matrix<T, 3, 3, Eigen::DontAlign>& intrinsics);`
- L90 _public prototype_ `const Eigen::Matrix<T, 3, 4, Eigen::DontAlign>& GetExtrinsics() const noexcept;`
- L101 _public prototype_ `void SetExtrinsics(const Eigen::Matrix<T, 3, 4, Eigen::DontAlign>& extrinsics);`
- L110 _public prototype_ `int GetWidth() const noexcept;`
- L119 _public prototype_ `void SetWidth(const int width) noexcept;`
- L128 _public prototype_ `int GetHeight() const noexcept;`
- L137 _public prototype_ `void SetHeight(const int height) noexcept;`
- L147 _public prototype_ `std::string GetLabel() const noexcept;`
- L156 _public prototype_ `void SetLabel(std::string label) noexcept;`
- L165 _public prototype_ `std::string GetModel() const noexcept;`
- L174 _public prototype_ `void SetModel(std::string model) noexcept;`
- L178 _protected member_ `Eigen::Matrix<T, 3, 3, Eigen::DontAlign> m_intrinsics;` — Intrinsics matrix
- L181 _protected member_ `Eigen::Matrix<T, 3, 4, Eigen::DontAlign> m_extrinsics;` — Extrinsics matrix [R|t]
- L184 _protected member_ `int m_width;` — Image dimensions
- L185 _protected member_ `int m_height;`
- L188 _protected member_ `std::string m_label;` — Label of the camera
- L191 _protected member_ `std::string m_model;` — Camera model

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/geometry/AABBTree.h` (Private)


#### struct `AABBTreeDefaultEPS`  
`template <typename scalar_t> struct AABBTreeDefaultEPS`  
_L19-22_
- L21 _public member_ `static constexpr scalar_t eps = std::numeric_limits<scalar_t>::epsilon() * scalar_t(10);`

#### struct `AABBTreeZeroEPS`  
`struct AABBTreeZeroEPS`  
_L24-27_
- L26 _public member_ `static constexpr double eps = 0;`

#### class `AABBTree`  
`template <typename scalar_t, size_t leafSize = 8, typename AABBTreeEPS = AABBTreeDefaultEPS<scalar_t>, typename compatibility_t = NoCompatibility<scalar_t>> class AABBTree`  
_L31-954_
- L34 _public typedef_ `using point_data_t = Eigen::Matrix<scalar_t, Eigen::Dynamic, 3, Eigen::RowMajor>;`
- L35 _public typedef_ `using primitive_data_t = Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::RowMajor>;`
- L36 _public typedef_ `using point_t = Eigen::RowVector<scalar_t, 3>;`
- L37 _public typedef_ `using point2_t = Eigen::RowVector<scalar_t, 2>;`
- L38 _public typedef_ `using primitive_t = Eigen::RowVector<int, 3>;`
- L39 _public typedef_ `using leaf_data_t = std::array<point_t, leafSize>;`
- L40 _public typedef_ `using bbox_t = std::pair<point_t, point_t>;`
- L41 _public member_ `static constexpr size_t invalid = std::numeric_limits<size_t>::max();`
- L42 _public member_ `static constexpr scalar_t eps = AABBTreeEPS::eps;`
- L68 _private member_ `Eigen::Map<const point_data_t> points{nullptr};` — members for storing the data
- L69 _private member_ `Eigen::Map<const primitive_data_t> primitives{nullptr};`
- L70 _private member_ `std::vector<helper_data_t> meta;`
- L73 _private member_ `std::vector<int> indices;` — tree structure data
- L74 _private member_ `std::vector<node_t> nodes;`
- L76 _private member_ `compatibility_t comp;`
- L80 _public function_ `template <typename ... Types> AABBTree(const scalar_t* pointsData_, int numPoints_, const int* primitivesData_, int numPrimitives_, Types&& ... args) : points(Eigen::Map<const point_data_t>(pointsData_, numPoints_, 3)), primitives(Eigen::Map<const primitive_data_t>(primitivesData_, numPrimitives_, 3)), comp(args ...)`
- L116 _public function_ `template <typename ... Types> AABBTree(const Eigen::Ref<const point_data_t>& points_, const Eigen::Ref<const primitive_data_t>& primitives_, Types&& ... args) : AABBTree(points_.data(), (int)points_.rows(), primitives_.data(), (int)primitives_.rows(), args ...)`
- L122 _public function_ `template <typename... Types> std::vector<std::tuple<int64_t, point_t, scalar_t>> getAllPointsWithinDistance(const Eigen::Ref<const point_t>& point, const scalar_t& distance, Types&&... args) const` — Computes all points <= the specified distance from the supplied point
- L205 _public function_ `void Update(TaskThreadPool* threadPool = nullptr)` — Update the current AABB tree with updated points. This assumes that the referenced points (see constructor) have been updated.
- L233 _public function_ `void Update(const scalar_t* pointsData_, TaskThreadPool* threadPool = nullptr)` — Update the current AABB tree with updated points. This assumes that the referenced points (see constructor) have been updated.
- L241 _public function_ `template <typename ... Types> std::tuple<int64_t, point_t, scalar_t> getClosestPoint(const Eigen::Ref<const point_t>& point, const scalar_t& distance, Types&& ... args) const`
- L323 _public function_ `std::tuple<int, point_t, scalar_t> intersectRay(const Eigen::Ref<const point_t>& origin, const Eigen::Ref<const point_t>& direction) const`
- L466 _public function_ `std::tuple<int, point_t, scalar_t> intersectRayBidirectional(const Eigen::Ref<const point_t>& origin, const Eigen::Ref<const point_t>& direction) const` — Finds the closest intersection of the ray with the AABB tree in both the positive and the negative direction. @return Tuple containing the triangle index (-1 if there is no intersection), the barycentric coordinates of the intersection, and the absolute distance from the origin to the intersection point.
- L607 _private function_ `std::tuple<scalar_t, point_t> getClosestPointToPrimitive(const Eigen::Ref<const point_t>& point, const size_t index) const` — --- point-primitive distance + helper functions ---
- L742 _private function_ `inline void getMinEdge02(const scalar_t& a11, const scalar_t& b1, point2_t& p) const`
- L759 _private function_ `inline void getMinEdge12(const scalar_t& a01, const scalar_t& a11, const scalar_t& b1, const scalar_t& f10, const scalar_t& f01, point2_t& p) const`
- L781 _private function_ `inline void getMinInterior(const point2_t& p0, const scalar_t& h0, const point2_t& p1, const scalar_t& h1, point2_t& p) const`
- L788 _private function_ `std::tuple<bool, point_t, scalar_t> intersectRayPrimitive(const Eigen::Ref<const point_t>& origin, const Eigen::Ref<const point_t>& direction, const size_t& index) const` — --- ray-primitive intersection function ---
- L824 _private function_ `void splitNode(size_t index)` — --- hierarchy construction function and helpers ---
- L887 _private function_ `void updateNode(size_t index, int level, TaskThreadPool* threadPool)` — the split and bounding box of the nodes
- L920 _private function_ `inline bbox_t centroidBoundingBox(const size_t start, const size_t end) const`
- L936 _private function_ `inline bbox_t primitiveBoundingBox(const size_t start, const size_t end) const`

#### struct `AABBTree::node_t`  
`struct node_t`  
_L45-56_
- L47 _public member_ `std::pair<size_t, size_t> children = { invalid, invalid };`
- L48 _public member_ `std::pair<size_t, size_t> range;`
- L49 _public member_ `bbox_t bbox;`
- L50 _public member_ `size_t dim = invalid;`
- L51 _public member_ `scalar_t split = 0.0f;`
- L53 _public function_ `node_t(size_t start, size_t end) : range({ start, end })`

#### struct `AABBTree::helper_data_t`  
`struct helper_data_t`  
_L58-65_
- L60 _public member_ `point_t edge0;`
- L61 _public member_ `point_t edge1;`
- L62 _public member_ `point_t normal;`
- L63 _public member_ `point_t centroid;`
- L64 _public member_ `point_t a;`

#### Free symbols / members of external scopes

- L209 _function_ `` (scope `AABBTree::Update`)
- L858 _function_ `` (scope `AABBTree::splitNode`)
- L902 _function_ `futures.Add(threadPool->AddTask([&]() { updateNode(node.children.first, level + 1, threadPool); }));` (scope `AABBTree::updateNode`)
- L903 _function_ `futures.Add(threadPool->AddTask([&]() { updateNode(node.children.second, level + 1, threadPool); }));` (scope `AABBTree::updateNode`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/geometry/KdTree.h` (Private)


#### struct `NoCompatibility`  
`template <typename scalar_t> struct NoCompatibility`  
_L19-28_
- desc: some basic compatibility structures that might be useful empty compatibility structure
- L21 _public function_ `NoCompatibility()`
- L24 _public function_ `inline bool isCompatible(const size_t) const`

#### struct `NormalCompatiblityFunction`  
`template <typename scalar_t, size_t dimension = 3> struct NormalCompatiblityFunction`  
_L33-47_
- desc: compatibility function checking if the normal is pointing in a similar direction
- L35 _public typedef_ `using data_t = Eigen::Matrix<scalar_t, Eigen::Dynamic, dimension, Eigen::RowMajor>;`
- L36 _public typedef_ `using value_t = Eigen::RowVector<scalar_t, dimension>;`
- L38 _public member_ `const Eigen::Ref<const data_t> normals;`
- L40 _public function_ `NormalCompatiblityFunction(const Eigen::Ref<const data_t>& normals_) : normals(normals_)`
- L43 _public function_ `inline bool isCompatible(const size_t index, const Eigen::Ref<const value_t>& normal, const scalar_t threshold) const`

#### class `KdTree`  
`template <typename scalar_t, typename compatibility_t = NoCompatibility<scalar_t>, size_t dimension = 3, size_t leafSize = 32> class KdTree`  
_L52-386_
- desc: kd-tree class supporting compatibility structures
- L55 _public typedef_ `using data_t = Eigen::Matrix<scalar_t, Eigen::Dynamic, dimension, Eigen::RowMajor>;`
- L56 _public typedef_ `using vector_t = Eigen::RowVector<scalar_t, dimension>;`
- L57 _public typedef_ `using leaf_data_t = std::array<vector_t, leafSize>;`
- L58 _public typedef_ `using bbox_t = std::pair<vector_t, vector_t>;`
- L59 _public member_ `static constexpr size_t invalid = std::numeric_limits<size_t>::max();`
- L78 _private member_ `const Eigen::Ref<const data_t> points;` — members for storing the data
- L79 _private member_ `const size_t numPoints;`
- L80 _private member_ `compatibility_t comp;`
- L83 _private member_ `std::vector<size_t> indices;` — tree structure data
- L84 _private member_ `std::vector<node_t> nodes;`
- L88 _public function_ `template <typename ... Types> KdTree(const Eigen::Ref<const data_t>& points_, Types&& ... args) : points(points_), numPoints(points.rows()), comp(args ...)`
- L105 _public function_ `vector_t getReferencePoint(const size_t index) const`
- L111 _public function_ `template <typename ... Types> std::pair<int64_t, scalar_t> getClosestPoint(const Eigen::Ref<const vector_t>& point, const scalar_t& distance, Types&& ... args) const`
- L201 _public function_ `template <typename ... Types> std::pair<std::vector<int64_t>, std::vector<scalar_t>> getPointsInRadius(const Eigen::Ref<const vector_t>& point, const scalar_t& distance, Types&& ... args) const`
- L291 _public function_ `void Search(const scalar_t* qrs, int numPts, int* resultIndices, scalar_t* distances = nullptr, const scalar_t maxDistance = std::numeric_limits<scalar_t>::max()) const`
- L309 _public function_ `Eigen::VectorXi Search(const scalar_t* qrs, int numPts, const scalar_t maxDistance = std::numeric_limits<scalar_t>::max()) const`
- L317 _private function_ `bbox_t boundingBox(const size_t start, const size_t end) const`
- L333 _private function_ `void splitNode(size_t index)`

#### struct `KdTree::node_t`  
`struct node_t`  
_L62-74_
- L64 _public member_ `std::pair<size_t, size_t> children = { invalid, invalid };`
- L65 _public member_ `std::pair<size_t, size_t> range;`
- L66 _public member_ `bbox_t bbox;`
- L67 _public member_ `size_t dim = invalid;`
- L68 _public member_ `scalar_t split = 0.0f;`
- L69 _public member_ `leaf_data_t data;`
- L71 _public function_ `node_t(size_t start, size_t end) : range({ start, end })`

#### Free symbols / members of external scopes

- L363 _function_ `` (scope `KdTree::splitNode`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/io/CameraIO.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template<class T> std::vector<CameraModelOpenCV<T> > ReadOpenCvModelJson(const std::string& filename);`
- L31 _prototype_ `template<class T> std::vector<CameraModelPinhole<T> > ReadPinholeModelJson(const std::string& filename);` — @brief Read Digital Humans Json camera file. Read Digital Humans Json camera file format with no distortion model - pinhole cameras (in the case of working with undistorted images, for example). @param filename String with file path.
- L41 _prototype_ `template<class T> void WriteOpenCvModelJson(const std::string& filename, const std::vector<CameraModelOpenCV<T> >& cameras);` — @brief Write Digital Humans Json camera file. Write Digital Humans Json camera file format with OpenCV distortion as distortion model (k1, k2, p1, p2, k3). @param cameras Vector of cameras with OpenCV distortion model.
- L50 _prototype_ `template<class T> void WritePinholeModelJson(const std::string& filename, const std::vector<CameraModelPinhole<T> >& cameras);` — @brief Write Digital Humans Json camera file. Write Digital Humans Json camera file format with pinhole camera model. @param cameras Vector of cameras with pinhole camera model.
- L60 _prototype_ `template<class T> std::vector<CameraModelOpenCV<T> > ReadOpenCvModelXml(const std::string& filename);` — @brief Read Agisoft Metashape xml camera file. Read Agisoft Metashape xml camera file format with OpenCV distortion as distortion model (k1, k2, p1, p2, k3). @param filename String with file path.
- L69 _prototype_ `template<class T> std::vector<CameraModelPinhole<T> > ReadPinholeModelXml(const std::string& filename);` — @brief Read Agisoft Metashape xml camera file. Read Agisoft Metashape xml camera file format with as Pinhole camera model. @param filename String with file path.
- L82 _prototype_ `template<class T> void WriteOpenCvModelXml(const std::string& filename, const std::vector<CameraModelOpenCV<T> >& cameras);`
- L94 _prototype_ `template<class T> void WritePinholeModelXml(const std::string& filename, const std::vector<CameraModelPinhole<T> >& cameras);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/io/JsonIO.h` (Private)


#### class `JsonElement`  
`class JsonElement`  
_L20-376_
- desc: JSON elements as defined in http://ietf.org/rfc/rfc4627.txt
- L39 _public function_ `JsonElement() : m_type(JsonType::Null), m_container()`
- L42 _public function_ `explicit JsonElement(JsonType type) : m_type(type)`
- L51 _public function_ `explicit JsonElement(int value) : m_type(JsonType::Int), m_container(static_cast<int64_t>(value))`
- L54 _public function_ `explicit JsonElement(int64_t value) : m_type(JsonType::Int), m_container(value)`
- L57 _public function_ `explicit JsonElement(double value) : m_type(JsonType::Double), m_container(value)`
- L60 _public function_ `explicit JsonElement(const std::string& str) : m_type(JsonType::String), m_container(str)`
- L63 _public function_ `explicit JsonElement(const char* str) : m_type(JsonType::String), m_container(str)`
- L66 _public function_ `explicit JsonElement(std::vector<JsonElement>&& array) : m_type(JsonType::Array), m_container(std::move(array))`
- L69 _public function_ `explicit JsonElement(std::map<std::string, JsonElement>&& object) : m_type(JsonType::Object), m_container(std::move( object))`
- L73 _public function_ `static JsonElement Obj()`
- L74 _public function_ `static JsonElement Arr()`
- L77 _public function_ `template<typename T> JsonElement& Set(const std::string& key, T value) &`
- L82 _public function_ `template<typename T> JsonElement&& Set(const std::string& key, T value) &&`
- L87 _public function_ `JsonElement& Set(const std::string& key, JsonElement element) &`
- L91 _public function_ `JsonElement&& Set(const std::string& key, JsonElement element) &&`
- L97 _public function_ `template<typename T> JsonElement& Add(T value) &`
- L102 _public function_ `template<typename T> JsonElement&& Add(T value) &&`
- L107 _public function_ `JsonElement& Add(JsonElement element) &`
- L111 _public function_ `JsonElement&& Add(JsonElement element) &&`
- L116 _public function_ `explicit JsonElement(bool value) : m_type(value ? JsonType::True : JsonType::False)`
- L120 _public function_ `template<typename T> explicit JsonElement(const std::pair<T, T>& pair) : m_type(JsonType::Array)`
- L127 _public function_ `template<typename ... Types> explicit JsonElement(const std::tuple<Types ...>& tuple) : m_type(JsonType::Array)`
- L135 _public function_ `template<typename T> explicit JsonElement(const std::vector<T>& vec) : m_type(JsonType::Array)`
- L143 _public function_ `template<typename T> explicit JsonElement(const std::map<std::string, T>& map) : m_type(JsonType::Object)`
- L150 _public prototype_ `JsonElement(const JsonElement&) = delete;`
- L151 _public prototype_ `JsonElement& operator=(const JsonElement&) = delete;`
- L153 _public function_ `JsonElement(JsonElement&& other) : m_type(other.m_type), m_container(std::move(other.m_container))`
- L157 _public function_ `JsonElement& operator=(JsonElement&& other)`
- L166 _public function_ `JsonType Type() const`
- L170 _public function_ `bool IsNull() const`
- L174 _public function_ `bool IsTrue() const`
- L178 _public function_ `bool IsFalse() const`
- L182 _public function_ `bool IsInt() const`
- L186 _public function_ `bool IsDouble() const`
- L190 _public function_ `bool IsNumber() const`
- L194 _public function_ `bool IsString() const`
- L198 _public function_ `bool IsArray() const`
- L202 _public function_ `bool IsObject() const`
- L207 _public function_ `template<class T, typename DISCARD = typename std::enable_if<std::is_arithmetic<T>::value>::type> T Value() const`
- L211 _public function_ `std::string& String()`
- L212 _public function_ `const std::string& String() const`
- L214 _public function_ `std::vector<JsonElement>& Array()`
- L215 _public function_ `const std::vector<JsonElement>& Array() const`
- L217 _public function_ `std::map<std::string, JsonElement>& Object()`
- L218 _public function_ `const std::map<std::string, JsonElement>& Object() const`
- L220 _public function_ `bool Boolean() const`
- L231 _public function_ `template<class T> T Get() const` — ! Generic get function which calls the specializations using typeHelper.
- L235 _public function_ `size_t Size() const`
- L245 _public function_ `JsonElement& operator[](size_t index)`
- L255 _public function_ `const JsonElement& operator[](size_t index) const`
- L265 _public function_ `void Append(JsonElement&& element)`
- L272 _public function_ `bool Contains(const std::string& key) const`
- L276 _public function_ `const JsonElement& operator[](const std::string& key) const`
- L288 _public function_ `JsonElement& operator[](const std::string& key)`
- L300 _public function_ `const std::map<std::string, JsonElement>& Map() const`
- L304 _public function_ `void Insert(const std::string& key, JsonElement&& element)`
- L314 _private prototype_ `template<typename T> T Get(typeHelper<T>) const;` — ! Generic Get function. B
- L318 _private function_ `template<typename S, typename T> std::pair<S, T> Get(typeHelper<std::pair<S, T> >) const` — ! Partial specialization for std::pair.
- L330 _private function_ `template<typename ... Types> std::tuple<Types ...> Get(typeHelper<std::tuple<Types ...> >) const` — ! Partial specialization for std::tuple.
- L348 _private function_ `template<typename S> std::vector<S> Get(typeHelper<std::vector<S> >) const` — ! Partial specialization for std::vector.
- L362 _private function_ `template<typename S> std::map<std::string, S> Get(typeHelper<std::map<std::string, S> >) const` — ! Partial specialization for std::map.
- L374 _private member_ `JsonType m_type;`
- L375 _private member_ `std::variant<int64_t, double, std::string, std::vector<JsonElement>, std::map<std::string, JsonElement> > m_container;`
- L379 _function_ `template<> inline int JsonElement::Get<int>(typeHelper<int>) const` — ! Get spezializations
- L384 _function_ `template<> inline int64_t JsonElement::Get<int64_t>(typeHelper<int64_t>) const` — ! Get spezializations
- L388 _function_ `template<> inline size_t JsonElement::Get<size_t>(typeHelper<size_t>) const`
- L392 _function_ `template<> inline float JsonElement::Get<float>(typeHelper<float>) const`
- L396 _function_ `template<> inline double JsonElement::Get<double>(typeHelper<double>) const`
- L400 _function_ `template<> inline std::string JsonElement::Get<std::string>(typeHelper<std::string>) const`

#### struct `JsonElement::typeHelper`  
`template<typename T> struct typeHelper`  
_L24-24_
- desc: ! helper struct to implement partial specialization

#### enum `JsonElement::JsonType`  
`enum class JsonType`  
_L28-37_
- desc: ! allowed types
- L29 _public enumerator_ `False`
- L30 _public enumerator_ `Null`
- L31 _public enumerator_ `True`
- L32 _public enumerator_ `Object`
- L33 _public enumerator_ `Array`
- L34 _public enumerator_ `Int`
- L35 _public enumerator_ `Double`
- L36 _public enumerator_ `String`

#### Free symbols / members of external scopes

- L129 _function_ `std::apply([&](auto&&... arg) { (Append(JsonElement(arg)), ...); }, tuple);` (scope `JsonElement::JsonElement`)
- L339 _function_ `std::apply([&](auto&&... arg) { size_t i(0); ((arg = Array()[i++].Get<typename std::remove_reference<decltype(arg)>::type>()), ...); }, tupleOut);` (scope `JsonElement::Get`)
- L404 _prototype_ `JsonElement ReadJson(const std::string& jsonString);`
- L407 _prototype_ `std::string WriteJson(const JsonElement& json, int tabs = -1);` — ! Write @p json to string. Set @p tabs to 0 or positive to pretty print with tabs and newlines.
- L410 _prototype_ `void WriteJson(std::ostream& stream, const JsonElement& element, int tabs = -1);` — ! Write @p json to @p stream. Set @p tabs to 0 or positive to pretty print with tabs and newlines.
- L412 _function_ `inline JsonElement DeepCopy(const JsonElement& src)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/io/NpyFileFormat.h` (Private)


#### struct `NPYHeader`  
`struct NPYHeader`  
_L23-32_
- L25 _public member_ `std::string m_dataType;` — supported: "<i4" (32-bit int), "<f4" (32-bit float), "<f8" (64-bit double)
- L26 _public member_ `std::vector<int> m_shape;`
- L27 _public member_ `bool m_fortranOrder;`
- L29 _public prototype_ `int DataTypeSize() const;`
- L31 _public function_ `template <typename T> bool IsType()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define CARBON_NPY_NAMESPACE TITAN_NAMESPACE::npy`
- L19 _prototype_ `CARBON_NAMESPACE_BEGIN(CARBON_NPY_NAMESPACE) template <typename T> std::string NpyTypeName();`
- L34 _prototype_ `void SaveNPYRaw(std::ostream& out, const NPYHeader& header, const uint8_t* data, size_t dataSize);`
- L36 _function_ `template <class T> void SaveNPY(std::ostream& out, const NPYHeader& header, const std::vector<T>& data)`
- L40 _function_ `template <class T> void SaveNPY(const std::string& filename, const NPYHeader& header, const std::vector<T>& data)`
- L47 _function_ `template <class T, int R, int C, int MatrixOrder> void SaveMatrixAsNpy(std::ostream& out, const Eigen::Matrix<T, R, C, MatrixOrder>& matrix)`
- L57 _function_ `template <class T, int R, int C, int MatrixOrder> void SaveMatrixAsNpy(const std::string& filename, const Eigen::Matrix<T, R, C, MatrixOrder>& matrix)`
- L69 _prototype_ `void LoadNPYRawHeader(const std::vector<char>& htxt, NPYHeader& header);`
- L70 _prototype_ `void LoadNPYRawHeader(std::istream& in, NPYHeader& header);`
- L71 _prototype_ `void LoadNPYRawData(std::istream& in, const NPYHeader& header, std::vector<uint8_t>& data);`
- L72 _prototype_ `void LoadNPYRaw(std::istream& in, NPYHeader& header, std::vector<uint8_t>& data);`
- L74 _prototype_ `void LoadNPYRawHeader(FILE* pFile, NPYHeader& header);`
- L75 _prototype_ `void LoadNPYRawData(FILE* pFile, const NPYHeader& header, std::vector<uint8_t>& data);`
- L78 _function_ `template <class T, std::enable_if_t<!std::is_same_v<T, uint8_t>, bool> = true> void LoadNPY(std::istream& in, NPYHeader& header, std::vector<T>& data)`
- L91 _function_ `template <class T, std::enable_if_t<!std::is_same_v<T, uint8_t>, bool> = true> void LoadNPY(const std::string& filename, NPYHeader& header, std::vector<T>& data)`
- L98 _function_ `template <class T, int R, int C, int MatrixOrder> void LoadMatrixFromNpy(std::istream& in, Eigen::Matrix<T, R, C, MatrixOrder>& matrix)`
- L153 _function_ `template <class T, int R, int C, int MatrixOrder> void LoadMatrixFromNpy(FILE* pFile, Eigen::Matrix<T, R, C, MatrixOrder>& matrix)`
- L206 _function_ `template <class T, int R, int C, int MatrixOrder> void LoadMatrixFromNpy(const std::string& filename, Eigen::Matrix<T, R, C, MatrixOrder>& matrix)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/io/Utils.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) FILE* OpenUtf8File(const std::string& utf8Path, const char* mode);`
- L23 _prototype_ `std::string ReadFile(const std::string& filename);` — @brief Reads all data in @p filename and returns it as std::string. @return std::string with all data in the file. @throw std::runtime_error if the file cannot be opened.
- L30 _prototype_ `bool FileExists(const std::string& filename);` — @brief Check if the @p filename exists. @return bool indicating if the file exists. False if filename is greater than max filename length. @throw std::filesystem::filesystem_error upon error.
- L36 _prototype_ `void WriteFile(const std::string& filename, const std::string& data);` — @brief Writes @p data to file @p filename. @throw std::runtime_error if the file could not be written.
- L42 _prototype_ `void ThrowReadFileErrorWithInfo(const std::string& filename);` — @brief Throw file reading error with troubleshooting information if the file reading fails @throw std::runtime_error if the file cannot be opened.
- L47 _prototype_ `std::string GetUsername();` — @return The username as read from the environment.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/io/XmlIO.h` (Private)


#### class `XMLElement`  
`class XMLElement`  
_L19-99_
- desc: XML element with name, attributes, text, and xml element children.
- L22 _public function_ `XMLElement(const std::string& name) : m_name(name)` — ! Creates an XMLElement with name @p name
- L26 _public function_ `XMLElement& AddChild(const std::string& childName)` — ! Add a child element and return reference to it.
- L31 _public function_ `const std::string& Name() const`
- L35 _public function_ `void SetText(const std::string& text)`
- L39 _public function_ `const std::string& Text() const`
- L43 _public function_ `void AddAttribute(const std::string& attributeName, const std::string& attributeValue)`
- L47 _public function_ `const std::string& Attribute(const std::string& attributeName) const`
- L56 _public function_ `const std::map<std::string, std::string>& Attributes() const`
- L60 _public function_ `const std::vector<std::unique_ptr<XMLElement> >& Children() const`
- L65 _public function_ `std::vector<XMLElement*> ChildrenWithName(const std::string& childName)` — ! @returns all children with element name @p childName
- L81 _public function_ `template<bool failIfNotUnique = true> XMLElement* UniqueChild(const std::string& childName)` — @returns a unique child element @p childName. @param[in] childName   The name of the child. @param[in] failIfNotUnique  If True then the method throws an exception is there is no child or multiple children with the name, otherwise it will return a nullptr.
- L94 _private member_ `std::string m_name;`
- L95 _private member_ `std::map<std::string, std::string> m_attributes;`
- L96 _private member_ `std::string m_text;`
- L98 _private member_ `std::vector<std::unique_ptr<XMLElement> > m_children;` — ! Store children as unique_ptr to handle any potential vector resizing which would break the references

#### Free symbols / members of external scopes

- L102 _prototype_ `void WriteXML(std::ostream& out, const XMLElement& element);` — ! Writes the XML element to @p output
- L105 _prototype_ `std::string WriteXML(const XMLElement& element);` — ! Writes the XML element to std::string.
- L108 _prototype_ `XMLElement ReadXML(const std::string& xmlData);` — ! Reads XML data from @p xmlData and @returns it as XMLElemen.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/simd/Simd.h` (Private)


#### struct `SimdTypeBase`  
`template <typename T, int C> struct SimdTypeBase`  
_L14-19_
- L16 _public function_ `inline static constexpr int Alignment()`
- L17 _public function_ `inline static constexpr int Size()`
- L18 _public function_ `inline static int Pad(int n)`

#### struct `_SimdType`  
`template <> struct _SimdType<bool, 1> : public SimdTypeBase<int, 1>`  
_L30-36_
- inherits: `SimdTypeBase<int,1>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<int, 1> : public SimdTypeBase<int, 1>`  
_L38-69_
- inherits: `SimdTypeBase<int,1>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<float, 1> : public SimdTypeBase<float, 1>`  
_L72-110_
- inherits: `SimdTypeBase<float,1>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<bool, 4> : public SimdTypeBase<int, 4>`  
_L155-161_
- inherits: `SimdTypeBase<int,4>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<int, 4> : public SimdTypeBase<int, 4>`  
_L164-196_
- inherits: `SimdTypeBase<int,4>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<float, 4> : public SimdTypeBase<float, 4>`  
_L199-236_
- inherits: `SimdTypeBase<float,4>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<bool, 8> : public SimdTypeBase<int, 8>`  
_L295-301_
- inherits: `SimdTypeBase<int,8>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<int, 8> : public SimdTypeBase<int, 8>`  
_L304-336_
- inherits: `SimdTypeBase<int,8>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### struct `_SimdType`  
`template <> struct _SimdType<float, 8> : public SimdTypeBase<float, 8>`  
_L339-376_
- inherits: `SimdTypeBase<float,8>`
- L32 _public member_ `bool vec;`
- L33 _public function_ `_SimdType(bool value) : vec(value)`
- L34 _public function_ `inline void StoreAligned(int* ptr) const`
- L35 _public function_ `inline bool Any() const`
- L40 _public member_ `int vec;`
- L42 _public prototype_ `_SimdType() = default;`
- L43 _public function_ `explicit _SimdType(int value) : vec(value)`
- L44 _public prototype_ `_SimdType(const _SimdType& other) = default;`
- L45 _public prototype_ `_SimdType& operator=(const _SimdType& other) = default;`
- L46 _public prototype_ `_SimdType(_SimdType&& vec) = default;`
- L47 _public prototype_ `_SimdType& operator=(_SimdType&& other) = default;`
- L48 _public prototype_ `~_SimdType() = default;`
- L50 _public function_ `inline static _SimdType Zero()`
- L51 _public function_ `inline void SetZero()`
- L52 _public function_ `inline void Set(int value)`
- L53 _public function_ `inline void LoadAligned(const int* ptr)`
- L55 _public function_ `inline _SimdType operator+(const _SimdType& other) const`
- L56 _public function_ `inline _SimdType operator-(const _SimdType& other) const`
- L57 _public function_ `inline _SimdType operator*(const _SimdType& other) const`
- L58 _public function_ `inline _SimdType operator/(const _SimdType& other) const`
- L59 _public function_ `inline _SimdType& operator+=(const _SimdType& other)`
- L60 _public function_ `inline _SimdType& operator-=(const _SimdType& other)`
- L61 _public function_ `inline _SimdType& operator*=(const _SimdType& other)`
- L62 _public function_ `inline _SimdType& operator/=(const _SimdType& other)`
- L65 _public prototype_ `template <typename S> inline _SimdType<S, 1> ValueCast() const;`
- L68 _public prototype_ `template <typename S> inline _SimdType<S, 1> BitwiseCast() const;`
- L74 _public member_ `float vec;`
- L77 _public function_ `explicit _SimdType(float value) : vec(value)`
- L86 _public function_ `inline void Set(float value)`
- L87 _public function_ `inline void LoadAligned(const float* ptr)`
- L88 _public function_ `inline void StoreAligned(float* ptr) const`
- L97 _public function_ `inline _SimdType Reciprocal() const`
- L98 _public function_ `inline float HorizontalSum() const`
- L99 _public function_ `inline _SimdType Square() const`
- L100 _public function_ `inline _SimdType<float, 1> ConditionalMove(const _SimdType<bool, 1>& mask) const`
- L112 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::ValueCast<float>() const`
- L119 _function_ `template <> inline _SimdType<float, 1> _SimdType<int, 1>::BitwiseCast<float>() const`
- L157 _public member_ `simde__m128i vec;`
- L158 _public function_ `_SimdType(simde__m128i&& vec) : vec(vec)`
- L170 _public function_ `explicit _SimdType(int value) : vec(simde_mm_set1_epi32(value))`
- L192 _public prototype_ `template <typename S> inline _SimdType<S, 4> ValueCast() const;`
- L195 _public prototype_ `template <typename S> inline _SimdType<S, 4> BitwiseCast() const;`
- L201 _public member_ `simde__m128 vec;`
- L204 _public function_ `_SimdType(simde__m128&& vec) : vec(vec)`
- L205 _public function_ `explicit _SimdType(float value) : vec(simde_mm_set1_ps(value))`
- L228 _public function_ `inline _SimdType<float, 4> ConditionalMove(const _SimdType<bool, 4>& mask) const`
- L229 _public function_ `inline _SimdType<float, 4> Abs() const`
- L239 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::ValueCast<float>() const`
- L246 _function_ `template <> inline _SimdType<float, 4> _SimdType<int, 4>::BitwiseCast<float>() const`
- L297 _public member_ `simde__m256i vec;`
- L298 _public function_ `_SimdType(simde__m256i&& vec) : vec(vec)`
- L310 _public function_ `explicit _SimdType(int value) : vec(simde_mm256_set1_epi32(value))`
- L332 _public prototype_ `template <typename S> inline _SimdType<S, 8> ValueCast() const;`
- L335 _public prototype_ `template <typename S> inline _SimdType<S, 8> BitwiseCast() const;`
- L341 _public member_ `simde__m256 vec;`
- L344 _public function_ `_SimdType(simde__m256&& vec) : vec(vec)`
- L345 _public function_ `explicit _SimdType(float value) : vec(simde_mm256_set1_ps(value))`
- L368 _public function_ `inline _SimdType<float, 8> ConditionalMove(const _SimdType<bool, 8>& mask) const`
- L369 _public function_ `inline _SimdType<float, 8> Abs() const`
- L378 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::ValueCast<float>() const`
- L385 _function_ `template <> inline _SimdType<float, 8> _SimdType<int, 8>::BitwiseCast<float>() const`

#### Free symbols / members of external scopes

- L24 _prototype_ `template <class T, int C> inline _SimdType<T, C> Abs(const _SimdType<T, C>& value);`
- L25 _prototype_ `template <class T, int C> inline _SimdType<T, C> Abs(const _SimdType<T, C>& value);`
- L26 _prototype_ `template <class T, int C> inline _SimdType<T, C> Abs(const _SimdType<T, C>& value);`
- L27 _prototype_ `template <class T, int C> inline _SimdType<T, C> Abs(const _SimdType<T, C>& value);`
- L125 _function_ `inline _SimdType<bool, 1> operator&&(const _SimdType<bool, 1>& a, const _SimdType<bool, 1>& b)`
- L126 _function_ `inline _SimdType<bool, 1> operator||(const _SimdType<bool, 1>& a, const _SimdType<bool, 1>& b)`
- L128 _function_ `template <typename T> inline _SimdType<bool, 1> operator==(const _SimdType<T, 1>& a, const _SimdType<T, 1>& b)`
- L129 _function_ `template <typename T> inline _SimdType<bool, 1> operator==(const _SimdType<T, 1>& a, const _SimdType<T, 1>& b)`
- L130 _function_ `template <typename T> inline _SimdType<bool, 1> operator==(const _SimdType<T, 1>& a, const _SimdType<T, 1>& b)`
- L131 _function_ `template <typename T> inline _SimdType<bool, 1> operator==(const _SimdType<T, 1>& a, const _SimdType<T, 1>& b)`
- L132 _function_ `template <typename T> inline _SimdType<bool, 1> operator!=(const _SimdType<T, 1>& a, const _SimdType<T, 1>& b)`
- L134 _function_ `template <> inline _SimdType<float, 1> Abs(const _SimdType<float, 1>& value)`
- L135 _function_ `template <> inline _SimdType<float, 1> Abs(const _SimdType<float, 1>& value)`
- L142 _function_ `template <> inline _SimdType<float, 1> Max(const _SimdType<float, 1>& value1, const _SimdType<float, 1>& value2)`
- L149 _function_ `template <> inline _SimdType<float, 1> Sqrt(const _SimdType<float, 1>& value)`
- L249 _function_ `inline _SimdType<bool, 4> operator&&(const _SimdType<bool, 4>& a, const _SimdType<bool, 4>& b)`
- L250 _function_ `inline _SimdType<bool, 4> operator||(const _SimdType<bool, 4>& a, const _SimdType<bool, 4>& b)`
- L252 _function_ `inline _SimdType<bool, 4> operator==(const _SimdType<int, 4>& a, const _SimdType<int, 4>& b)`
- L253 _function_ `inline _SimdType<bool, 4> operator>(const _SimdType<int, 4>& a, const _SimdType<int, 4>& b)`
- L254 _function_ `inline _SimdType<bool, 4> operator<=(const _SimdType<int, 4>& a, const _SimdType<int, 4>& b)`
- L255 _function_ `inline _SimdType<bool, 4> operator<(const _SimdType<int, 4>& a, const _SimdType<int, 4>& b)`
- L257 _function_ `inline _SimdType<bool, 4> operator==(const _SimdType<float, 4>& a, const _SimdType<float, 4>& b)`
- L260 _function_ `inline _SimdType<bool, 4> operator!=(const _SimdType<float, 4>& a, const _SimdType<float, 4>& b)`
- L263 _function_ `inline _SimdType<bool, 4> operator<=(const _SimdType<float, 4>& a, const _SimdType<float, 4>& b)`
- L266 _function_ `inline _SimdType<bool, 4> operator<(const _SimdType<float, 4>& a, const _SimdType<float, 4>& b)`
- L269 _function_ `inline _SimdType<bool, 4> operator>(const _SimdType<float, 4>& a, const _SimdType<float, 4>& b)`
- L273 _function_ `template <> inline _SimdType<float, 4> Abs(const _SimdType<float, 4>& value)`
- L274 _function_ `template <> inline _SimdType<float, 4> Abs(const _SimdType<float, 4>& value)`
- L281 _function_ `template <> inline _SimdType<float, 4> Max(const _SimdType<float, 4>& value1, const _SimdType<float, 4>& value2)`
- L288 _function_ `template <> inline _SimdType<float, 4> Sqrt(const _SimdType<float, 4>& value)`
- L388 _function_ `inline _SimdType<bool, 8> operator&&(const _SimdType<bool, 8>& a, const _SimdType<bool, 8>& b)`
- L389 _function_ `inline _SimdType<bool, 8> operator||(const _SimdType<bool, 8>& a, const _SimdType<bool, 8>& b)`
- L391 _function_ `inline _SimdType<bool, 8> operator==(const _SimdType<int, 8>& a, const _SimdType<int, 8>& b)`
- L392 _function_ `inline _SimdType<bool, 8> operator>(const _SimdType<int, 8>& a, const _SimdType<int, 8>& b)`
- L393 _function_ `inline _SimdType<bool, 8> operator<=(const _SimdType<int, 8>& a, const _SimdType<int, 8>& b)`
- L394 _function_ `inline _SimdType<bool, 8> operator<(const _SimdType<int, 8>& a, const _SimdType<int, 8>& b)`
- L396 _function_ `inline _SimdType<bool, 8> operator==(const _SimdType<float, 8>& a, const _SimdType<float, 8>& b)`
- L399 _function_ `inline _SimdType<bool, 8> operator!=(const _SimdType<float, 8>& a, const _SimdType<float, 8>& b)`
- L402 _function_ `inline _SimdType<bool, 8> operator<=(const _SimdType<float, 8>& a, const _SimdType<float, 8>& b)`
- L405 _function_ `inline _SimdType<bool, 8> operator<(const _SimdType<float, 8>& a, const _SimdType<float, 8>& b)`
- L408 _function_ `inline _SimdType<bool, 8> operator>(const _SimdType<float, 8>& a, const _SimdType<float, 8>& b)`
- L412 _function_ `template <> inline _SimdType<float, 8> Abs(const _SimdType<float, 8>& value)`
- L413 _function_ `template <> inline _SimdType<float, 8> Abs(const _SimdType<float, 8>& value)`
- L420 _function_ `template <> inline _SimdType<float, 8> Max(const _SimdType<float, 8>& value1, const _SimdType<float, 8>& value2)`
- L427 _function_ `template <> inline _SimdType<float, 8> Sqrt(const _SimdType<float, 8>& value)`
- L433 _typedef_ `typedef _SimdType<float, 8> SimdType;`
- L434 _typedef_ `typedef _SimdType<int, 8> SimdTypei;`
- L435 _typedef_ `typedef _SimdType<bool, 8> SimdTypeb;`
- L437 _typedef_ `typedef _SimdType<float, 4> SimdType;`
- L438 _typedef_ `typedef _SimdType<int, 4> SimdTypei;`
- L439 _typedef_ `typedef _SimdType<bool, 4> SimdTypeb;`
- L441 _typedef_ `typedef _SimdType<float, 1> SimdType;`
- L442 _typedef_ `typedef _SimdType<int, 1> SimdTypei;`
- L443 _typedef_ `typedef _SimdType<bool, 1> SimdTypeb;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/simd/SimdeWarnings.h` (Private)


#### Free symbols / members of external scopes

- L6 _macro_ `#define CARBON_DISABLE_SIMDE_WARNINGS`
- L7 _macro_ `#define CARBON_REENABLE_SIMDE_WARNINGS`
- L11 _macro_ `#define CARBON_DISABLE_SIMDE_WARNINGS \` — disable warning: sse.h(3979) : warning C6001: Using uninitialized memory 'r_'.: Lines: 3971, 3979
- L14 _macro_ `#define CARBON_REENABLE_SIMDE_WARNINGS __pragma(warning(pop))`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/simd/Utils.h` (Private)


#### Free symbols / members of external scopes

- L19 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) #if defined CARBON_ENABLE_SSE && CARBON_ENABLE_SSE`
- L32 _function_ `inline simde__m128i mul_epi32_sse2(const simde__m128i& a, const simde__m128i& b)`
- L47 _function_ `inline float HorizontalSum(simde__m256 value)` — \return value[0] + value[1] + ... + value[7]

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/simd/VertexUnpack.h` (Private)


#### struct `VertexPack128`  
`struct VertexPack128`  
_L12-17_
- L14 _public member_ `simde__m128 v0;`
- L15 _public member_ `simde__m128 v1;`
- L16 _public member_ `simde__m128 v2;`

#### struct `VertexPack256`  
`struct VertexPack256`  
_L55-60_
- L57 _public member_ `simde__m256 v0;`
- L58 _public member_ `simde__m256 v1;`
- L59 _public member_ `simde__m256 v2;`

#### Free symbols / members of external scopes

- L27 _function_ `static inline VertexPack128 VertexUnpack(const simde__m128& v0, const simde__m128& v1, const simde__m128& v2)` — @brief Converts ArrayOfStructures into StructuresOfArray for 4 vectors with 3 elements each. [x1, y1, z1, x2], [y2, z2, x3, y3] [z3, x4, y4, z4] => [x1, x2, x3, x4], [y1, y2, y3, y4] [z1, z2, z3, z4] This is useful to extract consecutive vertex data and unpack each vertex dimension.
- L70 _function_ `static inline VertexPack256 VertexUnpack(const simde__m256& v0, const simde__m256& v1, const simde__m256& v2)` — @brief Converts ArrayOfStructures into StructuresOfArray for 4 vectors with 3 elements each. [x1, y1, z1, x2], [y2, z2, x3, y3] [z3, x4, y4, z4] => [x1, x2, x3, x4], [y1, y2, y3, y4] [z1, z2, z3, z4] This is useful to extract consecutive vertex data and unpack each vertex dimension.
- L102 _function_ `template <typename T, int C> std::tuple<_SimdType<T, C>, _SimdType<T, C>, _SimdType<T, C>> VertexUnpack(const _SimdType<T, C>& v0, const _SimdType<T, C>& v1, const _SimdType<T, C>& v2)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/Base64.h` (Private)


#### Free symbols / members of external scopes

- L10 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) std::string Base64Encode(const unsigned char* data, size_t length); bool Base64Decode(std::string const& encodedString, std::vector<unsigned char>& decodedData); std::string Base64Decode(std::string const& encodedString);`
- L26 _prototype_ `bool Base64Decode(std::string const& encodedString, std::vector<unsigned char>& decodedData);` — Perform base64 decoding of string to return binary data using base64 alphabet defined in RFC 4648 ( https://en.wikipedia.org/wiki/Base64 ) @param[in] encodedString: the base64 encoded string (length must be a multiple of 4). @param[out] decodedData: the base64 decoded data @returns true if decoded successfully, false otherwise (ie encoded string is not valid base64 data)
- L34 _prototype_ `std::string Base64Decode(std::string const& encodedString);` — Perform base64 decoding of string to return binary data using base64 alphabet defined in RFC 4648 ( https://en.wikipedia.org/wiki/Base64 ) @param[in] encodedString: the base64 encoded string (length must be a multiple of 4). @returns The decoded binary string @throws exception if string cannot be decoded (ie encoded string is not valid base64 data).
- L37 _prototype_ `bool IsBase64Data(const std::string& encodedString);` — @return True if string is base64 data

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/Env.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/FlattenJson.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) JsonElement FlattenJson(const JsonElement& jsonIn, const std::string& baseDir);`
- L25 _prototype_ `JsonElement FlattenJson(const std::string& fileName);` — Load the selected file as Json and flatten it, ie for any strings in the Json file, if they exist as a file, if the file extension is .json they will be loaded as json, and if not, they will be loaded as binary and converted to a Base64 string and embedded in the output json @param[in] fileName: the filename of the Json file to flatten @returns the flattened Json

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/ObjectPool.h` (Private)


#### class `ObjectPool`  
`template <typename T> class ObjectPool`  
_L21-90_
- desc: Class to keep a pool of objects. Aquire() returns a shared_ptr to an object of the pool, or it creates a new one if the pool is empty. Upon release of the shared_ptr, the object is returned to the pool via Release(). The class is intended to be used to keep large allocated data structures in the pool and therefore prevent constant mallocs and frees. @warning neither constructor or destructor are called on the objects upon Aquire() and Release(). The caller is responsible to fill all members of the returned object.
- L24 _public function_ `ObjectPool() : m_selfPtr(std::make_shared<ObjectPool<T>*>(this))`
- L26 _public function_ `std::shared_ptr<T> Aquire()`
- L54 _public function_ `size_t Size() const`
- L61 _public function_ `void Clear()` — Clears all objects from the pool that are currently within the pool. Does not remove the ones that have been aquired.
- L72 _public function_ `size_t TotalSize() const` — @returns the total number of objects belonging to the pool, both currently in the pool and the ones that have been aquired.
- L79 _private function_ `void Release(std::unique_ptr<T>&& obj)`
- L86 _private member_ `mutable std::mutex m_mutex;`
- L87 _private member_ `std::stack<std::unique_ptr<T>> m_objects;`
- L88 _private member_ `std::shared_ptr<ObjectPool<T>*> m_selfPtr;`
- L89 _private member_ `size_t m_totalCreatedObjects = 0;`

#### Free symbols / members of external scopes

- L41 _function_ `auto releaseFunctor = [poolWeakPtr](T* ptr)` (scope `ObjectPool::Aquire`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/ProgressReporter.h` (Private)


#### class `AbstractProgressReporter`  
`class AbstractProgressReporter`  
_L22-44_
- desc: Abstract class to represent progress reporting implementation. Simple utility that can be implemented to act as a CLI progress reporter, or maybe part of a more complex GUI application.
- L24 _public prototype_ `virtual ~AbstractProgressReporter() = default;`
- L31 _public prototype_ `virtual void StartProgress(const char* message) = 0;` — Start tracking progress for a particular process. @param message Message that should describe the process.
- L38 _public prototype_ `virtual void SetProgress(float progress) = 0;` — Set the progress to the current state. @param progress New progress value between [0, 1].
- L43 _public prototype_ `virtual void EndProgress() = 0;` — Mark the ending of a progress.

#### class `CLIProgressReporter`  
`class CLIProgressReporter : public AbstractProgressReporter`  
_L56-97_
- inherits: `AbstractProgressReporter`
- desc: A simple command-line interface progress reporter implementation. An example of a fully printed out CMD progress line: Reading images   |==================================================| 100%, done in 44.3064 seconds. It includes a single line progress update (equal signs '=' in the example above though the character can be changed), estimated time printout while progress is running, and elapsed time took to finish the process once it is done.
- L66 _public prototype_ `CLIProgressReporter(unsigned int barLength = 50, unsigned int barStart = 40, char barPin = '=');` — Default Constructor. @param barLength How many character will there be to represent the 100% process. @param barStart The offset character count, acting as a TAB character to denote the offset between the message and progress bar. @param barPin Character that is used to represent a single pin inside the progress bar.
- L68 _public prototype_ `virtual ~CLIProgressReporter();`
- L71 _public prototype_ `void Silence();` — Silence the reporter output (ignore it's update to the stream)
- L74 _public prototype_ `void Unsilence();` — Continue pushing printouts to the stream.
- L85 _public prototype_ `void SetStream(std::ostream* stream);` — Set custom output stream to which the utility prints progress. By default, constructor sets this field to std::cout. @warning Stream instance must live as long as it is the lifetime of this instance. CLIProgressReporter does not take ownership of the stream instance.
- L87 _public prototype_ `virtual void StartProgress(const char* message) override final;`
- L88 _public prototype_ `virtual void SetProgress(float progress) final override;`
- L89 _public prototype_ `virtual void EndProgress() final override;`
- L93 _private member_ `Pimpl<Impl> m_pimpl;`
- L95 _private prototype_ `void PrintProgress();`
- L96 _private prototype_ `void PrintProgressEnd();`

#### class `IncrementingProgressReporter`  
`class IncrementingProgressReporter`  
_L104-150_
- desc: @brief Utility counting progress reporter that can be used to wrap a an AbstractProgressReporter to count progress in increments.
- L106 _public function_ `IncrementingProgressReporter(AbstractProgressReporter* progressReporter) : m_progressReporter(progressReporter) , m_numSteps(1) , m_count(0)`
- L121 _public function_ `void StartProgress(const char* message, int numSteps)` — Start tracking progress for a particular process. @param message Message that should describe the process. @param numSteps Defines how many steps / iterations this progress will contain. @note Based on numSteps update method calculates how much to advance the progress counters.
- L128 _public function_ `void Update()`
- L139 _public function_ `void EndProgress()` — Mark the ending of a progress.
- L147 _private member_ `AbstractProgressReporter* m_progressReporter;`
- L148 _private member_ `std::atomic<int> m_numSteps;`
- L149 _private member_ `std::atomic<int> m_count;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/Stopwatch.h` (Private)


#### class `Stopwatch`  
`template<class Timer = std::chrono::steady_clock> class Stopwatch`  
_L18-76_
- desc: Simple, header-only utility for measuring time based on std::chrono.
- L20 _public function_ `Stopwatch() : m_tick(Timer::now())`
- L23 _public function_ `~Stopwatch()`
- L31 _public function_ `std::chrono::duration<double> Tick()` — Tick the stopwatch - start counting anew. @return Last counted time segment, before the tick.
- L44 _public function_ `void Reset()` — Reset all so far collected times.
- L50 _public function_ `std::chrono::duration<double> LastTime()` — Get what is the last measured time.
- L55 _public function_ `std::chrono::duration<double> ElapsedTime()` — Get what is currently elapsed time since the last tick.
- L63 _public function_ `std::chrono::duration<double> TotalTime()` — Get what is the total elapsed time since the first tick of the stopwatch instance.
- L69 _public function_ `const std::vector<std::chrono::duration<double> >& AllTimes() const` — Get list of all times that is collected in this stopwatch instance.
- L74 _private member_ `std::chrono::time_point<Timer> m_tick;`
- L75 _private member_ `std::vector<std::chrono::duration<double> > m_allTimes;`

#### Free symbols / members of external scopes

- L79 _function_ `inline Stopwatch<std::chrono::steady_clock> SteadyStopwatch()` — Create a stopwatch instance based on std::chrono::steady_clock.
- L84 _function_ `inline Stopwatch<std::chrono::high_resolution_clock> HighResolutionStopwatch()` — Create a stopwatch instance based on std::chrono::high_resolution_clock.
- L89 _function_ `inline Stopwatch<std::chrono::system_clock> SystemStopwatch()` — Create a stopwatch instance based on std::chrono::system_clock.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/StringFormat.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <typename ... Args> std::string StringFormat(const std::string& format, Args ... args)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/StringReplace.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) inline std::string ReplaceSubstring(const std::string& input, const std::string& pattern, const std::string& replacement)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/StringUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) inline bool StringEndsWith(const std::string& input, const std::string& suffix)`
- L19 _function_ `inline bool StringStartsWith(const std::string& input, const std::string& prefix)`
- L25 _function_ `inline std::string StringToLower(const std::string& input)`
- L28 _function_ `std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return static_cast<unsigned char>(std::tolower(c)); });` (scope `StringToLower`)
- L34 _function_ `inline std::vector<std::string> Split(const std::string& str, const std::string& delim)`
- L60 _function_ `inline std::string Trim(const std::string& s)`
- L77 _function_ `inline std::filesystem::path Utf8Path(const std::string& utf8)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/TaskThreadPool.h` (Private)


#### Free symbols / members of external scopes

- L15 _typedef_ `using TaskFuture = TaskFutureUE;`
- L16 _typedef_ `using TaskFutures = TaskFuturesUE;`
- L17 _typedef_ `using TaskThreadPool = TaskThreadPoolUE;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/TaskThreadPoolStd.h` (Private)


#### class `TaskThreadPoolStd`  
`class TaskThreadPoolStd`  
_L23-54_
- L26 _public prototype_ `static std::shared_ptr<TaskThreadPoolStd> GlobalInstance(bool createIfNotAvailable, int numThreads = MaxNumThreads());`
- L27 _public prototype_ `static void ParallelFor(int number, std::function<void(int)>&& Body);`
- L29 _public prototype_ `TaskThreadPoolStd(int numThreads);`
- L30 _public prototype_ `~TaskThreadPoolStd();`
- L32 _public prototype_ `void Stop();`
- L34 _public function_ `size_t NumThreads() const`
- L35 _public prototype_ `void SetNumThreads(int numThreads);`
- L36 _public prototype_ `static size_t MaxNumThreads();`
- L38 _public prototype_ `TaskFutureStd AddTask(std::function<void()>&& task);`
- L40 _public prototype_ `void AddTaskRangeAndWait(int numTasks, const std::function<void(int, int)>& processFunction, int numThreadsToUseHint = -1);`
- L43 _public prototype_ `void RunTask();` — explicitly run a task
- L46 _private prototype_ `void RunWorkerThread();`
- L49 _private member_ `std::atomic<bool> m_stop;`
- L50 _private member_ `std::mutex m_mutex;`
- L51 _private member_ `std::condition_variable m_conditionVariable;`
- L52 _private member_ `std::deque<std::packaged_task<void()>> m_tasks;`
- L53 _private member_ `std::vector<std::thread> m_workerThreads;`

#### class `TaskFutureStd`  
`class TaskFutureStd`  
_L56-73_
- L59 _public function_ `TaskFutureStd() : m_future(), m_pool(nullptr)`
- L60 _public function_ `TaskFutureStd(std::future<void>&& future, TaskThreadPoolStd* pool) : m_future(std::move(future)), m_pool(pool)`
- L61 _public prototype_ `TaskFutureStd(TaskFutureStd&&) = default;`
- L62 _public prototype_ `TaskFutureStd(const TaskFutureStd&) = delete;`
- L63 _public prototype_ `TaskFutureStd& operator=(TaskFutureStd&&) = default;`
- L64 _public prototype_ `TaskFutureStd& operator=(const TaskFutureStd&) = delete;`
- L66 _public prototype_ `bool Valid() const;`
- L67 _public prototype_ `bool Ready() const;`
- L68 _public prototype_ `void Wait();`
- L71 _private member_ `std::future<void> m_future;`
- L72 _private member_ `TaskThreadPoolStd* m_pool;`

#### class `TaskFuturesStd`  
`class TaskFuturesStd`  
_L75-88_
- L78 _public prototype_ `TaskFuturesStd() = default;`
- L79 _public prototype_ `~TaskFuturesStd();`
- L81 _public function_ `void Reserve(size_t size)`
- L83 _public prototype_ `void Add(TaskFutureStd&& future);`
- L84 _public prototype_ `void Wait();`
- L87 _private member_ `std::vector<TaskFutureStd> m_futures;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/TaskThreadPoolUE.h` (Private)


#### class `TaskThreadPoolUE`  
`class TaskThreadPoolUE`  
_L22-43_
- L25 _public prototype_ `static std::shared_ptr<TaskThreadPoolUE> GlobalInstance(bool createIfNotAvailable, int numThreads = MaxNumThreads());`
- L26 _public prototype_ `static void ParallelFor(int number, std::function<void(int)>&& Body);`
- L28 _public prototype_ `TaskThreadPoolUE();`
- L29 _public prototype_ `TaskThreadPoolUE(int numThreads);`
- L30 _public prototype_ `~TaskThreadPoolUE();`
- L32 _public prototype_ `static size_t MaxNumThreads();`
- L34 _public prototype_ `void Stop();`
- L35 _public prototype_ `size_t NumThreads() const;`
- L36 _public prototype_ `void SetNumThreads(int numThreads);`
- L37 _public prototype_ `TaskFutureUE AddTask(std::function<void()>&& InFunction);`
- L38 _public prototype_ `void AddTaskRangeAndWait(int numTasks, const std::function<void(int, int)>& processFunction, int numThreadsToUseHint = -1);`
- L39 _public prototype_ `void RunTask();`
- L42 _private member_ `std::atomic<int> m_numThreads{};`

#### class `TaskFutureUE`  
`class TaskFutureUE`  
_L45-65_
- L48 _public prototype_ `TaskFutureUE();`
- L49 _public prototype_ `~TaskFutureUE();`
- L51 _public prototype_ `TaskFutureUE(FGraphEventRef Task);`
- L53 _public prototype_ `TaskFutureUE(TaskFutureUE&&);`
- L54 _public prototype_ `TaskFutureUE(const TaskFutureUE&) = delete;`
- L55 _public prototype_ `TaskFutureUE& operator=(TaskFutureUE&&);`
- L56 _public prototype_ `TaskFutureUE& operator=(const TaskFutureUE&) = delete;`
- L58 _public prototype_ `bool Valid() const;`
- L60 _public prototype_ `void Wait();` — bool Ready() const;
- L64 _private member_ `std::unique_ptr<Data> m_data;`

#### class `TaskFuturesUE`  
`class TaskFuturesUE`  
_L67-80_
- L70 _public prototype_ `TaskFuturesUE() = default;`
- L71 _public prototype_ `~TaskFuturesUE();`
- L73 _public function_ `void Reserve(size_t size)`
- L75 _public prototype_ `void Add(TaskFutureUE&& future);`
- L76 _public prototype_ `void Wait();`
- L79 _private member_ `std::vector<TaskFutureUE> m_futures;`

#### Free symbols / members of external scopes

- L15 _typedef_ `using FGraphEvent = class FBaseGraphTask;`
- L16 _typedef_ `using FGraphEventRef = TRefCountPtr<class FBaseGraphTask>;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/TaskThreadPoolUtils.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace TaskThreadPoolUtils`
- L33 _prototype_ `void RunTaskRangeAndWait(std::shared_ptr<TaskThreadPool> threadPool, int range, const std::function<void(int, int)> &processFunction, int numThreadsToUseHint = -1);` (scope `TaskThreadPoolUtils`) — @brief Run the tasks range with the provided thread pool. If the thread pool is not available, run all tasks in one call to processing function Thread pool will call the processing function (which takes the start and end indices) in parallel until the whole range of tasks is processed. If the thread pool is not available, the processing function will be called for the whole range in the thread that called this function @note It is assumed that the first tasks starts with index 0 and that the last is at index (range - 1) @param[in] threadPool            - thread pool to use @param[in] range                 - range of tasks @param[in] processingFunction    - function that takes start and end index for the tasks to be processed @param[in] numThreadsToUseHint   - optional, hint on how many threads to use at once (default is -1 which means use max available)
- L52 _prototype_ `void RunTaskRangeAndWait(int range, const std::function<void(int, int)> &processFunction, int numThreadsToUseHint = -1, bool createThreadPoolIfNotAvailable = true);` (scope `TaskThreadPoolUtils`) — @brief Create thread pool (optional) and run the tasks range. If the thread pool is not available, run all tasks in one call to processing function Thread pool will call the processing function (which takes the start and end indices) in parallel until the whole range of tasks is processed. If the thread pool is not available (not created or cant be created), the processing function will be called for the whole range in the thread that called this function @note It is assumed that the first tasks starts with index 0 and that the last is at index (range - 1) @param[in] range                             - range of tasks @param[in] processingFunction                - function that takes start and end index for the tasks to be processed @param[in] createThreadPoolIfNotAvailable    - optional, indicates should the thread pool be created if not already available (default is true) @param[in] numThreadsToUseHint               - optional, hint on how many threads to use at once (default is -1 which means use max available)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/Timecode.h` (Private)


#### class `Timecode`  
`class Timecode`  
_L16-70_
- desc: Class to calculate Timecode
- L18 _public prototype_ `Timecode() = default;`
- L20 _public function_ `Timecode(int hours, int minutes, int seconds, int frames, double fps) : m_hours(hours) , m_minutes(minutes) , m_seconds(seconds) , m_frames(frames) , m_fps(fps)`
- L30 _public function_ `void AddSeconds(double seconds)`
- L36 _public function_ `void Round()`
- L42 _public function_ `void MakeCanonical()`
- L55 _public function_ `std::string to_string() const`
- L62 _public function_ `double GetFps() const`
- L65 _private member_ `int m_hours;`
- L66 _private member_ `int m_minutes;`
- L67 _private member_ `int m_seconds;`
- L68 _private member_ `double m_frames;`
- L69 _private member_ `double m_fps;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/include/carbon/utils/Timer.h` (Private)


#### class `Timer`  
`class Timer`  
_L11-29_
- L14 _public function_ `Timer()`
- L19 _public function_ `void Restart()`
- L21 _public function_ `double Current()`
- L28 _private member_ `std::chrono::high_resolution_clock::time_point m_start;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/carbon/src/io/Utils.h` (Private)


#### Free symbols / members of external scopes

- L14 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) JsonElement WriteFileinfo();`
- L18 _prototype_ `void ReadCameraMetadataJson(const JsonElement& json, std::string& label, std::string& model, int& width, int& height);`
- L19 _prototype_ `void ReadSensorMetadataXml(XMLElement* xmlSensor, int& width, int& height, int& id);`
- L21 _prototype_ `void WriteCameraMetadataJson(JsonElement& json, int width, int height, const std::string& label, const std::string& model);`
- L22 _prototype_ `void WriteSensorMetadataXml(XMLElement& xmlSensor, int width, int height, int id);`
- L23 _prototype_ `void WriteCameraMetadataXml(XMLElement& xmlCamera, const std::string& label, int id);`
- L26 _prototype_ `template<class T> void WriteIntrinsicsJson(JsonElement& json, const Eigen::Matrix3<T>& intrinsics);`
- L29 _prototype_ `template<class T> void WriteIntrinsicsXml(XMLElement& xmlCalibration, const Eigen::Matrix3<T>& intrinsics, int width, int height);`
- L32 _prototype_ `template<class T> void ReadIntrinsicsJson(const JsonElement& json, Eigen::Matrix3<T>& intrinsics);`
- L35 _prototype_ `template<class T> void ReadIntrinsicsXml(XMLElement* xmlCalibration, Eigen::Matrix3<T>& intrinsics, int width, int height);`
- L38 _prototype_ `template<class T> JsonElement WriteExtrinsicsJson(const Eigen::Matrix<T, 3, 4>& transform);`
- L41 _prototype_ `template<class T> void WriteExtrinsicsXml(XMLElement& xmlCamera, const Eigen::Matrix<T, 3, 4>& transform);`
- L44 _prototype_ `template<class T> void ReadExtrinsicsJson(const JsonElement& json, Eigen::Matrix<T, 3, 4>& transform);`
- L47 _prototype_ `template<class T> void ReadGlobalTransformXml(XMLElement* xmlChunk, Eigen::Matrix4d& transform, T& scale);`
- L50 _prototype_ `template<class T> void ReadExtrinsicsXml(XMLElement* xmlCamera, const Eigen::Matrix4d& globalTransform, Eigen::Matrix<T, 3, 4>& cameraExtrinsics, T scale);`
- L56 _prototype_ `template<class T> void WriteDistortionOpenCVJson(JsonElement& json, const Eigen::Vector<T, 5>& distortion);`
- L59 _prototype_ `template<class T> void WriteDistortionOpenCVXml(XMLElement& json, const Eigen::Vector<T, 5>& distortion);`
- L62 _prototype_ `template<class T> void ReadDistortionOpenCVJson(const JsonElement& json, Eigen::Vector<T, 5>& distortion);`
- L65 _prototype_ `template<class T> void ReadDistortionOpenCvXml(XMLElement* xmlCalibration, Eigen::Vector<T, 5>& distortion);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/BlockJacobian.h` (Private)


#### class `BlockJacobian`  
`template <class T> class BlockJacobian`  
_L18-101_
- desc: Jacobian class using block layout with each block being either a sparse or dense matrix.
- L21 _public typedef_ `using DenseMatrixType = Eigen::Matrix<T, -1, -1, Eigen::RowMajor>;`
- L22 _public typedef_ `using SparseMatrixType = Eigen::SparseMatrix<T, Eigen::RowMajor>;`
- L25 _public prototype_ `BlockJacobian() = default;`
- L31 _public prototype_ `BlockJacobian(const std::shared_ptr<const SparseMatrixType>& sparseMatrix, int startCol);` — @brief Create a block jacobian with a sparse matrix of size [rows, cols]. The block jacobian then has size [rows, cols]. @p startCol should be the first non-zero column of the sparse matrix.
- L33 _public prototype_ `BlockJacobian(const std::shared_ptr<const DenseMatrixType>& denseMatrix, int startCol);` — Create a block jacobian with a dense matrix of size [rows, cols]. The block jacobian then has size [rows, startCol + cols]
- L34 _public prototype_ `~BlockJacobian() = default;`
- L35 _public prototype_ `BlockJacobian(BlockJacobian&&) = default;`
- L36 _public prototype_ `BlockJacobian(const BlockJacobian&) = default;`
- L37 _public prototype_ `BlockJacobian& operator=(BlockJacobian&&) = default;`
- L38 _public prototype_ `BlockJacobian& operator=(const BlockJacobian&) = default;`
- L41 _public prototype_ `[[nodiscard]] int Rows() const;` — @returns the number of rows of the Jacobian matrix
- L44 _public prototype_ `[[nodiscard]] int Cols() const;` — @returns the number of columns of the Jacobian matrix
- L47 _public prototype_ `[[nodiscard]] int StartCol() const;` — @returns the first non-zero column of the Jacobian matrix
- L50 _public prototype_ `[[nodiscard]] int NonZeros() const;` — @returns the total number of non zeros
- L53 _public prototype_ `[[nodiscard]] int NonZeros(int r) const;` — @returns the number of non zeros for row @p r
- L56 _public prototype_ `[[nodiscard]] std::shared_ptr<const SparseMatrixType> AsSparseMatrix() const;` — @returns the block jacobian as a sparse matrix of size [Rows(), Cols()]
- L59 _public prototype_ `void CopyToDenseMatrix(Eigen::Ref<DenseMatrixType> dense) const;` — Copies the block jacobian to dense matrix @p dense (of size [Rows(), Cols() - StartCol()])
- L61 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Premultiply(const SparseMatrixType& sparseMat) const;`
- L63 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Add(const BlockJacobian<T>& other) const;`
- L64 _public function_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Add(const std::shared_ptr<const BlockJacobian<T>>& other) const`
- L66 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Subtract(const BlockJacobian<T>& other) const;`
- L67 _public function_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Subtract(const std::shared_ptr<const BlockJacobian<T>>& other) const`
- L69 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Scale(T scale) const;`
- L71 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> RowGather(const Eigen::VectorX<int>& blockIndices, int blockSize) const;`
- L73 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> RowScatter(int outputSize, const Eigen::VectorX<int>& blockIndices, int blockSize) const;`
- L75 _public prototype_ `[[nodiscard]] std::shared_ptr<const BlockJacobian> Repeat(int N) const;`
- L77 _public prototype_ `[[nodiscard]] Eigen::SparseVector<T> Row(int row) const;`
- L80 _public prototype_ `void AddJx(Eigen::Ref<Eigen::VectorX<T>> result, const Eigen::Ref<const Eigen::VectorX<T>>& x, const T scale) const;` — result += scale * Jacobian() * vec
- L83 _public prototype_ `void AddJtx(Eigen::Ref<Eigen::VectorX<T>> result, const Eigen::Ref<const Eigen::VectorX<T>>& x, const T scale) const;` — result += scale * Jacobian().transpose() * vec
- L86 _public prototype_ `void AddSparseJtJLower(std::vector<Eigen::Triplet<T>>& JtJ, const T scale) const;` — JtJ += scale * Jacobian().transpose() * Jacobian()
- L89 _public prototype_ `void AddDenseJtJLower(Eigen::Ref<Eigen::Matrix<T, -1, -1>> JtJ, const T scale, TaskThreadPool* threadPool) const;` — JtJ += scale * Jacobian().transpose() * Jacobian()
- L100 _private member_ `std::vector<Block> m_blocks;`

#### struct `BlockJacobian::Block`  
`struct Block`  
_L92-99_
- L94 _public member_ `std::shared_ptr<const SparseMatrixType> sparseMatrix;`
- L95 _public member_ `std::shared_ptr<const DenseMatrixType> denseMatrix;`
- L96 _public member_ `int startCol;`
- L97 _public member_ `int endCol;`
- L98 _public member_ `T scale;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/BoundedVectorVariable.h` (Private)


#### class `BoundedVectorVariable`  
`template <class T> class BoundedVectorVariable : public VectorVariable<T>`  
_L16-118_
- inherits: `VectorVariable<T>`
- desc: BoundedVectorVariable is a VectorVariable where each dimenion is bounded by some user defined bounds. Note that the Jacobian is correct in the sense that clamping due to the bounds is not taken into account i.e. the Jacobian is the same as VectorVariable.
- L19 _public function_ `BoundedVectorVariable(int size) : VectorVariable<T>(size), m_enforceBounds(true)`
- L25 _public function_ `BoundedVectorVariable(const Vector<T>& vector) : VectorVariable<T>(vector), m_enforceBounds(true)`
- L31 _public prototype_ `BoundedVectorVariable(BoundedVectorVariable&& other) = default;`
- L32 _public prototype_ `BoundedVectorVariable(const BoundedVectorVariable& other) = default;`
- L33 _public prototype_ `BoundedVectorVariable& operator=(BoundedVectorVariable&& other) = default;`
- L34 _public prototype_ `BoundedVectorVariable& operator=(const BoundedVectorVariable& other) = default;`
- L39 _public function_ `void EnforceBounds(bool enforce)` — Change whether the bounds are enforced or not. If the bounds are not enforced then the variable behaves the same as a VectorVariable.
- L50 _public function_ `bool BoundsAreEnforced() const` — @return True if the bounds are enforced when setting/updating the value
- L52 _public function_ `const Eigen::Matrix<T, 2, -1> Bounds() const`
- L54 _public function_ `void SetBounds(const Eigen::Matrix<T, 2, -1>& bounds)`
- L68 _public function_ `void SetBounds(int index, T minValue, T maxValue)`
- L82 _public function_ `void SetRegularizationScaling(const Eigen::VectorX<T>& regularizationScaling)`
- L91 _public function_ `const Eigen::VectorX<T>& RegularizationScaling() const`
- L95 _private function_ `virtual void ProjectToManifold(Vector<T>& value) override final` — Project the variables to the bounds
- L107 _private function_ `void SetUnbounded()` — Set the internal bounds to unbounded i.e. the range is to the minimum and maximum value
- L115 _private member_ `bool m_enforceBounds;`
- L116 _private member_ `Eigen::Matrix<T, 2, -1> m_bounds;`
- L117 _private member_ `Eigen::VectorX<T> m_regularizationScaling;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/Context.h` (Private)


#### class `Context`  
`template <class T> class Context`  
_L29-215_
- desc: The Context class provides the variable context when creating nonlinear optimization problems. In particular a Variable registers its local Jacobian with the Context and retrieves a modified Jacobian where the variable placement (the column indices) has been modified so that multiple Variables can coexist. The functions Value(), Set(), and Update() work similarly to the Variable implementation, but in this case these methods update all Variables that have been registered by the Context. Once a variable has registered a local jacobian it is expeced to remain the same until Next() is being called on the Context. This indicates that the variables have changed and therefore the Jacobians may also change. Note that Update() and Set() wil automatically call Next().
- L48 _public function_ `Context() : m_valueSize(0), m_updateSize(0), m_variableMap()`
- L50 _public function_ `void Clear()`
- L57 _public function_ `void Next()`
- L65 _public function_ `JacobianConstPtr<T> Map(Variable<T>* var, const SparseMatrixConstPtr<T>& localJacobian)`
- L110 _public function_ `void Set(const Vector<T>& x)`
- L129 _public function_ `Vector<T> Value()` — @returns the current variable vector defined by the mapping in this context
- L144 _public function_ `void Update(const Vector<T>& dx)`
- L162 _public function_ `std::vector<Variable<T>*> Variables()`
- L173 _public function_ `int ValueSize() const`
- L174 _public function_ `int UpdateSize() const`
- L177 _public function_ `const VariableInfo& GetVariableInfo(const Variable<T>* var) const` — @returns the column index and size of the variable in the jacobian
- L191 _private function_ `JacobianConstPtr<T> LocalToGlobalJacobian(const SparseMatrixConstPtr<T>& localJacobian, int columnIndex)`
- L211 _private member_ `int m_valueSize;`
- L212 _private member_ `int m_updateSize;`
- L214 _private member_ `std::map<Variable<T>*, VariableInfo> m_variableMap;`

#### struct `Context::VariableInfo`  
`struct VariableInfo`  
_L32-45_
- L35 _public member_ `SparseMatrixConstPtr<T> localJacobian;` — local jacobian of size rows x cols
- L38 _public member_ `JacobianConstPtr<T> globalJacobian;` — global jacobian which is the jacobian shifted by colOffset, total size rows x m_updateSize (when the global Jacobian was last constructed)
- L40 _public member_ `int rows;` — variable output dimension
- L41 _public member_ `int cols;` — variable update dimension
- L42 _public member_ `int rowOffset;` — offset into global value dimension
- L43 _public member_ `int colOffset;` — offset into global update dimension
- L44 _public member_ `int queries;` — how often the variable has been queries since the last call to Next()

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/Cost.h` (Private)


#### class `Cost`  
`template <class T> class Cost`  
_L17-108_
- desc: Cost
- L20 _public prototype_ `Cost() = default;`
- L21 _public prototype_ `~Cost() = default;`
- L22 _public prototype_ `Cost(Cost&&) = default;`
- L23 _public prototype_ `Cost(const Cost&) = delete;`
- L24 _public prototype_ `Cost& operator=(Cost&&) = default;`
- L25 _public prototype_ `Cost& operator=(const Cost&) = delete;`
- L35 _public function_ `void Add(DiffData<T>&& fx, T weight, const std::string& name = std::string(), bool average = false)` — @brief Add a least squares cost term: weight * || f(x) ||^2 @param fx       The f(x) value (with or without Jacobian). @param weight   The weight for the cost term. @param name     An optional name for the cost term. @param average  If True, then the cost term is calculating the average: weight * || f(x) ||^2 / size(f(x)).
- L51 _public function_ `void Add(Cost&& other, T weight = T(1), bool average = false)` — @brief Add another cost term to this cost term: weight * cost(x) @param other    The other cost term. @param weight   A weighting of the other cost term. @param average  If True, then the cost term is added as an average: weight * cost(x) / size(f(x))
- L63 _public prototype_ `Eigen::VectorX<T> Value() const;`
- L65 _public prototype_ `DiffData<T> CostToDiffData() const;`
- L67 _public function_ `int NumTerms() const`
- L69 _public function_ `int Size() const`
- L79 _public function_ `int Rows() const`
- L82 _public prototype_ `int Cols() const;` — @returns the number of columns of the Jacobian. @pre HasJacobian() is True.
- L85 _public prototype_ `void AddJx(Eigen::Ref<Eigen::VectorX<T>> result, const Eigen::Ref<const Eigen::VectorX<T>>& x, const T scale) const;` — result += scale * cost.Jacobian() * vec
- L88 _public prototype_ `void AddJtx(Eigen::Ref<Eigen::VectorX<T>> result, const Eigen::Ref<const Eigen::VectorX<T>>& x, const T scale) const;` — result += scale * cost.Jacobian().transpose() * vec
- L91 _public prototype_ `void AddDenseJtJLower(Eigen::Ref<Eigen::Matrix<T, -1, -1>> JtJ, const T scale, TaskThreadPool* threadPool) const;` — Calculates JtJ of the cost term and accumulates it into JtJ with additional scaling @p scale.
- L94 _public prototype_ `void AddSparseJtJLower(std::vector<Eigen::Triplet<T>>& JtJ, const T scale) const;` — Calculates sparse JtJ of the cost term and accumulates it as triplets with additional scaling @p scale.
- L97 _public prototype_ `bool HasJacobian() const;` — @returns True if all cost terms have a Jacobian.
- L107 _private member_ `std::vector<CostTerm> m_costTerms;`

#### struct `Cost::CostTerm`  
`struct CostTerm`  
_L100-105_
- L102 _public member_ `T weight;`
- L103 _public member_ `DiffData<T> diffdata;`
- L104 _public member_ `std::string name;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/DiffData.h` (Private)


#### class `DiffData`  
`template <class T> class DiffData`  
_L17-90_
- desc: Base data representation required for differentiable data with a vector of values and a Jacobian values: f(x) jacobian: df/dx
- L20 _public function_ `DiffData(Vector<T>&& value, JacobianConstPtr<T>&& jacobian) : m_value(std::move(value)), m_jacobian(std::move(jacobian))`
- L25 _public function_ `DiffData(Vector<T>&& value, const JacobianConstPtr<T>& jacobian) : m_value(std::move(value)), m_jacobian(jacobian)`
- L30 _public function_ `DiffData(Vector<T>&& value) : DiffData(std::move(value), JacobianConstPtr<T>())`
- L32 _public function_ `DiffData(const Vector<T>& value, const JacobianConstPtr<T>& jacobian) : m_value(value), m_jacobian(jacobian)`
- L37 _public function_ `DiffData(const Vector<T>& value) : DiffData(value, JacobianConstPtr<T>())`
- L40 _public function_ `DiffData(const T* values, int size) : DiffData(Eigen::Map<const Vector<T>>(values, size))` — constructor that explicitly copies the data
- L41 _public function_ `DiffData(const T* values, int size, const JacobianConstPtr<T>& jacobian) : DiffData(Eigen::Map<const Vector<T>>(values, size), jacobian)`
- L45 _public function_ `template <class S, int R, int C, typename DISCARD = typename std::enable_if<std::is_same<S, T>::value, void>::type> DiffData(const Eigen::Matrix<S, R, C>& mat) : DiffData((const T*)mat.data(), (int)mat.size())` — constructor that explicitly copies the data
- L49 _public function_ `template <class S, int R, int C, typename DISCARD = typename std::enable_if<std::is_same<S, T>::value, void>::type> DiffData(const Eigen::Matrix<S, R, C>& mat, const JacobianConstPtr<T>& jacobian) : DiffData((const T*)mat.data(), (int)mat.size(), jacobian)` — constructor that explicitly copies the data
- L51 _public prototype_ `DiffData(const DiffData&) = delete;`
- L52 _public prototype_ `DiffData& operator=(const DiffData&) = delete;`
- L53 _public prototype_ `DiffData(DiffData&&) = default;`
- L54 _public prototype_ `DiffData& operator=(DiffData&&) = default;`
- L56 _public function_ `void SanityCheck() const`
- L65 _public function_ `DiffData<T> Clone() const` — explicitly clone the diff data object as copy constructor is disabled (implementation may change in the future)
- L67 _public function_ `int Size() const`
- L68 _public function_ `const Vector<T>& Value() const`
- L70 _public function_ `bool HasJacobian() const`
- L71 _public function_ `const JacobianConstPtr<T>& JacobianPtr() const`
- L72 _public function_ `const TITAN_NAMESPACE::Jacobian<T>& Jacobian() const`
- L74 _public function_ `void SetJacobianPtr(const JacobianConstPtr<T>& jacobian)`
- L80 _public function_ `Vector<T>& MutableValue()` — Convenience function returning a reference to the value. @warning Use with care as any copy of DiffData will have its value modified as well.
- L85 _public function_ `JacobianConstPtr<T>& MutableJacobianPtr()` — Convenience function returning a reference to the jacobian ptr.
- L88 _private member_ `Vector<T> m_value;`
- L89 _private member_ `JacobianConstPtr<T> m_jacobian;`

#### Free symbols / members of external scopes

- L94 _function_ `template <class T> DiffData<T> operator*(const SparseMatrix<T>& A, const DiffData<T>& x)` — Sparse multiplication (linear map) of input @p x.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/DiffDataMatrix.h` (Private)


#### class `DiffDataMatrix`  
`template <class T, int R = -1, int C = -1> class DiffDataMatrix : public DiffData<T>`  
_L17-86_
- inherits: `DiffData<T>`
- desc: Differentiable data but with f(x) being a matrix and not a vector. @see DiffData
- L21 _public function_ `template <bool TMP = true> DiffDataMatrix(DiffData<T>&& o, typename std::enable_if<TMP && ((R >= 0) && (C >= 0))>::type* = 0) : DiffData<T>(std::move(o)) , m_rows(R) , m_cols(C)`
- L31 _public function_ `DiffDataMatrix(int rows, int cols, DiffData<T>&& o) : DiffData<T>(std::move(o)) , m_rows(rows) , m_cols(cols)`
- L42 _public function_ `template <bool TMP = true> DiffDataMatrix(const Eigen::Matrix<T, R, C>& mat, const JacobianConstPtr<T>& jacobian = nullptr, typename std::enable_if<TMP && ((R >= 0) && (C >= 0))>::type* = 0) : DiffDataMatrix(DiffData<T>(mat.data(), int(mat.size()), jacobian))`
- L48 _public function_ `template <bool TMP = true> DiffDataMatrix(const Eigen::Matrix<T, R, C>& mat, const JacobianConstPtr<T>& jacobian = nullptr, typename std::enable_if<TMP && !((R >= 0) && (C >= 0))>::type* = 0) : DiffDataMatrix(int(mat.rows()), int(mat.cols()), DiffData<T>(mat.data(), int(mat.size()), jacobian))`
- L53 _public function_ `int Rows() const`
- L54 _public function_ `int Cols() const`
- L57 _public function_ `Eigen::Map<const Eigen::Matrix<T, R, C>> Matrix() const` — Convenience function returning the value data as a matrix
- L66 _public function_ `Eigen::Map<Eigen::Matrix<T, R, C>> MutableMatrix()` — Convenience function returning the value data as a matrix. @warning Use with care as any copy of DiffDataMatrix will have its value modified as well.
- L70 _public function_ `template <int C2> DiffDataMatrix<T, R, C2> Multiply(const DiffDataMatrix<T, C, C2>& B) const` — Multiplies two matrices C = A * B
- L77 _public function_ `DiffData<T> Multiply(const DiffData<T>& b) const` — Multiplies a matrix and a vector c = A * b
- L84 _private member_ `int m_rows;`
- L85 _private member_ `int m_cols;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/DiffDataSparseMatrix.h` (Private)


#### class `DiffDataSparseMatrix`  
`template <class T, int R = -1, int C = -1> class DiffDataSparseMatrix : public DiffData<T>`  
_L20-134_
- inherits: `DiffData<T>`
- desc: Differentiable data but with f(x) being a sparse matrix and not a vector. Values of the underlying data vector are the dense nonzero entries and will always be in the sparse matrix's storage order. @see DiffData
- L27 _public function_ `template <bool TMP = true> DiffDataSparseMatrix(DiffData<T>&& o, const Eigen::VectorX<int>& outerIndices, const Eigen::VectorX<int>& innerIndices, typename std::enable_if<TMP && ((R >= 0) && (C >= 0))>::type* = 0) : DiffData<T>(std::move(o)) , m_rows(R) , m_cols(C) , m_outerIndices(outerIndices) , m_innerIndices(innerIndices)` — @warning Index arrays follow Eigen's CSC sparse format. len(outerIndices) = R + 1 and len(innerIndices) = o.Size()
- L43 _public function_ `DiffDataSparseMatrix(int rows, int cols, DiffData<T>&& o, const Eigen::VectorX<int>& outerIndices, const Eigen::VectorX<int>& innerIndices) : DiffData<T>(std::move(o)) , m_rows(rows) , m_cols(cols) , m_outerIndices(outerIndices) , m_innerIndices(innerIndices)`
- L62 _public function_ `template <bool TMP = true> DiffDataSparseMatrix(DiffData<T>&& o, const SparseMatrix<T>& mat, typename std::enable_if<TMP && ((R >= 0) && (C >= 0))>::type* = 0) : DiffDataSparseMatrix(std::move(o), Eigen::Map<const Eigen::VectorX<int>>(mat.outerIndexPtr(), mat.outerSize() + 1), Eigen::Map<const Eigen::VectorX<int>>(mat.innerIndexPtr(), mat.nonZeros()))` — @warning This constructor uses 'mat' ONLY for the sparsity structure for convenience. The nonzero data and jacobian comes from DiffData input
- L73 _public function_ `template <bool TMP = true> DiffDataSparseMatrix(DiffData<T>&& o, const SparseMatrix<T>& mat, typename std::enable_if<TMP && !((R >= 0) && (C >= 0))>::type* = 0) : DiffDataSparseMatrix(int(mat.rows()), int(mat.cols()), std::move(o), Eigen::Map<const Eigen::VectorX<int>>(mat.outerIndexPtr(), mat.outerSize() + 1), Eigen::Map<const Eigen::VectorX<int>>(mat.innerIndexPtr(), mat.nonZeros()))` — @warning This constructor uses 'mat' ONLY for the sparsity structure for convenience. The nonzero data and jacobian comes from DiffData input
- L83 _public function_ `template <bool TMP = true> DiffDataSparseMatrix(const SparseMatrix<T>& mat, const JacobianConstPtr<T>& jacobian = nullptr, typename std::enable_if<TMP && ((R >= 0) && (C >= 0))>::type* = 0) : DiffDataSparseMatrix(DiffData<T>(mat.valuePtr(), int(mat.nonZeros()), jacobian), Eigen::Map<const Eigen::VectorX<int>>(mat.outerIndexPtr(), mat.outerSize() + 1), Eigen::Map<const Eigen::VectorX<int>>(mat.innerIndexPtr(), mat.nonZeros()))`
- L91 _public function_ `template <bool TMP = true> DiffDataSparseMatrix(const SparseMatrix<T>& mat, const JacobianConstPtr<T>& jacobian = nullptr, typename std::enable_if<TMP && !((R >= 0) && (C >= 0))>::type* = 0) : DiffDataSparseMatrix(int(mat.rows()), int(mat.cols()), DiffData<T>(mat.valuePtr(),int(mat.nonZeros()), jacobian), Eigen::Map<const Eigen::VectorX<int>>(mat.outerIndexPtr(), mat.outerSize() + 1), Eigen::Map<const Eigen::VectorX<int>>(mat.innerIndexPtr(), mat.nonZeros()))`
- L101 _public function_ `int Rows() const`
- L102 _public function_ `int Cols() const`
- L104 _public function_ `const Eigen::VectorX<int>& OuterIndices() const`
- L105 _public function_ `const Eigen::VectorX<int>& InnerIndices() const`
- L108 _public function_ `Eigen::Map<const SparseMatrix<T>> Matrix() const` — Convenience function returning the value data as a sparse matrix
- L117 _public function_ `Eigen::Map<SparseMatrix<T>> MutableMatrix()` — Convenience function returning the value data as a sparse matrix. @warning Use with care as any copy of DiffDataSparseMatrix will have its value modified as well.
- L123 _public function_ `DiffData<T> Multiply(const DiffData<T>& b) const` — Multiplies a matrix and a vector c = A * b
- L130 _private member_ `int m_rows;`
- L131 _private member_ `int m_cols;`
- L132 _private member_ `Eigen::VectorX<int> m_outerIndices;`
- L133 _private member_ `Eigen::VectorX<int> m_innerIndices;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/DiffScalar.h` (Private)


#### class `DiffScalar`  
`template <typename T> class DiffScalar`  
_L21-37_
- desc: Base data representation representing a scalar and a Jacobian as a sparse vector value: f(x) jacobian: df/dx
- L24 _public function_ `DiffScalar(const T value, const Eigen::SparseVector<T>& jacobian) : m_value(value), m_jacobian(jacobian)`
- L27 _public function_ `explicit DiffScalar(const T value) : m_value(value), m_jacobian()`
- L29 _public function_ `const T Value() const`
- L31 _public function_ `bool HasJacobian() const`
- L32 _public function_ `const Eigen::SparseVector<T>& Jacobian() const`
- L35 _private member_ `T m_value;`
- L36 _private member_ `Eigen::SparseVector<T> m_jacobian;`

#### Free symbols / members of external scopes

- L41 _function_ `template <typename T> DiffScalar<T> ExtractScalar(const DiffData<T>& diffData, int index)` — Extract the @p index row from @p diffData.
- L53 _function_ `template <typename T> DiffData<T> AssembleDiffData(const std::vector<DiffScalar<T>>& diffScalars)` — Assemble all DiffScalar into on DiffData
- L100 _function_ `template <typename T> inline DiffScalar<T> operator+(const DiffScalar<T>& f)` — Unary +
- L106 _function_ `template <typename T> inline DiffScalar<T> operator-(const DiffScalar<T>& f)` — Unary -
- L111 _function_ `template <class T> Eigen::SparseVector<T> AutoResizeAdd(const Eigen::SparseVector<T>& a, const Eigen::SparseVector<T>& b)`
- L146 _function_ `template <typename T> inline DiffScalar<T> operator+(const DiffScalar<T>& f, const DiffScalar<T>& g)` — Binary +
- L152 _function_ `template <typename T> inline DiffScalar<T> operator+(const DiffScalar<T>& f, T s)` — Binary + with scalar f + s
- L158 _function_ `template <typename T> inline DiffScalar<T> operator+(T s, const DiffScalar<T>& f)` — Binary + with scalar s + f
- L164 _function_ `template <typename T> inline DiffScalar<T> operator-(const DiffScalar<T>& f, const DiffScalar<T>& g)` — Binary -
- L170 _function_ `template <typename T> inline DiffScalar<T> operator-(const DiffScalar<T>& f, T s)` — Binary - with scalar f - s
- L176 _function_ `template <typename T> inline DiffScalar<T> operator-(T s, const DiffScalar<T>& f)` — Binary - with scalar s - f
- L182 _function_ `template <typename T> inline DiffScalar<T> operator*(const DiffScalar<T>& f, const DiffScalar<T>& g)` — Binary *
- L188 _function_ `template <typename T> inline DiffScalar<T> operator*(const DiffScalar<T>& f, T s)` — Binary * with scalar f * s
- L194 _function_ `template <typename T> inline DiffScalar<T> operator*(T s, const DiffScalar<T>& f)` — Binary * with scalar s * f
- L200 _function_ `template <typename T> inline DiffScalar<T> operator/(const DiffScalar<T>& f, const DiffScalar<T>& g)` — Binary /
- L208 _function_ `template <typename T> inline DiffScalar<T> operator/(const DiffScalar<T>& f, T s)` — Binary / with scalar f / s
- L215 _function_ `template <typename T> inline DiffScalar<T> operator/(T s, const DiffScalar<T>& f)` — Binary / with scalar s / f
- L222 _function_ `template <typename T> inline DiffScalar<T> max(const DiffScalar<T> f, const DiffScalar<T>& g)` — maximum (the Jacobian is not well defined when both values are equal, so in this case we return the average Jacobian)
- L233 _function_ `template <typename T> inline DiffScalar<T> max(T s, const DiffScalar<T>& f)`
- L242 _function_ `template <typename T> inline DiffScalar<T> max(const DiffScalar<T>& f, T s)`
- L246 _function_ `template <typename T> inline DiffScalar<T> min(const DiffScalar<T> f, const DiffScalar<T>& g)` — minimum (the Jacobian is not well defined when both values are equal, so in this case we return the average Jacobian)
- L257 _function_ `template <typename T> inline DiffScalar<T> min(T s, const DiffScalar<T>& f)`
- L266 _function_ `template <typename T> inline DiffScalar<T> min(const DiffScalar<T>& f, T s)`
- L270 _function_ `template <typename T> inline DiffScalar<T> clamp(const DiffScalar<T>& f, T a, T b)` — clamp

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/Jacobian.h` (Private)


#### Free symbols / members of external scopes

- L14 _macro_ `#define USE_BLOCK_JACOBIAN 0`
- L18 _typedef_ `template <class T> using JacobianPtr = std::shared_ptr<BlockJacobian<T>>;`
- L21 _typedef_ `template <class T> using JacobianConstPtr = std::shared_ptr<const BlockJacobian<T>>;`
- L24 _typedef_ `template <class T> using Jacobian = BlockJacobian<T>;`
- L27 _typedef_ `template <class T> using DenseJacobian = BlockJacobian<T>;`
- L29 _typedef_ `template <class T> using SparseJacobian = BlockJacobian<T>;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/MatrixVariable.h` (Private)


#### class `MatrixVariable`  
`template <class T, int R = -1, int C = -1, typename DISCARD = typename std::enable_if<(R >= -1 && C >= -1), void>::type> class MatrixVariable : public VectorVariable<T>`  
_L21-84_
- inherits: `VectorVariable<T>`
- L24 _public member_ `static constexpr int ROWS = R;`
- L25 _public member_ `static constexpr int COLS = C;`
- L30 _public function_ `template <typename U = T> MatrixVariable(typename std::enable_if<std::is_same<U, T>::value && ((R >= 0) && (C >= 0))>::type* = 0) : MatrixVariable( R* C)` — constructor for fixed size matrices (calls the protected version further below with the correct updateDimension)
- L35 _public function_ `template <typename U = T> MatrixVariable(int rows, int cols, typename std::enable_if<std::is_same<U, T>::value && !((R >= 0) && (C >= 0))>::type* = 0) : MatrixVariable(rows, cols, rows* cols)` — constructor for dynamic size matrices (calls the protected version further below with the correct updateDimension)
- L38 _public function_ `int Rows() const`
- L39 _public function_ `int Cols() const`
- L42 _public function_ `void SetMatrix(const Eigen::Matrix<T, R, C>& M)` — Sets the matrix and projects it to the manifold.
- L48 _public function_ `Eigen::Map<const Eigen::Matrix<T, R, C>> Matrix() const` — Convenience function returning the variable data as a matrix.
- L54 _public function_ `DiffDataMatrix<T, R, C> EvaluateMatrix(Context<T>* context = nullptr)` — Convenience function returning a matrix with Jacobian (DiffDataMatrix) instead of just a vector
- L57 _public function_ `void SetIdentity()` — convenience function to set the identity matrix
- L60 _public function_ `void SetRandom()` — convenience function to set a random matrix
- L65 _protected function_ `template <typename U = T> MatrixVariable(int updateDimension, typename std::enable_if<std::is_same<U, T>::value && ((R >= 0) && (C >= 0))>::type* = 0) : VectorVariable<T>(R * C, updateDimension), dimInfo(R, C)` — Only subclasses can call this constructor to set up a matrix variable with an underlying manifold representation e.g. quaternion.
- L70 _protected function_ `template <typename U = T> MatrixVariable(int rows, int cols, int updateDimension, typename std::enable_if<std::is_same<U, T>::value && !((R >= 0) && (C >= 0))>::type* = 0) : VectorVariable<T>(rows * cols, updateDimension), dimInfo(rows, cols)` — Only subclasses can call this constructor to set up a matrix variable with an underlying manifold representation e.g. quaternion.
- L77 _protected function_ `void SetMatrix(const Eigen::Matrix<T, R, C>& M, bool projectToManifold)` — Sets the matrix and optionally projects it to the manifold. Note that the caller needs to ensure that the matrix is already on the manifold if projectToManifold=false.
- L80 _protected function_ `void SetMatrix(const Eigen::Map<const Eigen::Matrix<T, R, C>>& M, bool projectToManifold)` — @see SetMatrix above
- L83 _private member_ `internal::DimInfo<R, C> dimInfo;`

#### class `internal::DimInfo`  
`template <int R, int C> class DimInfo`  
_L92-98_
- desc: helper class to have fixed and dynamic size dimensions
- L95 _public function_ `DimInfo(int, int)`
- L96 _public function_ `static constexpr int Rows()`
- L97 _public function_ `static constexpr int Cols()`
- L104 _public function_ `DimInfo(int rows, int cols) : cols(cols)`
- L110 _public function_ `int Rows() const`
- L111 _public function_ `int Cols() const`
- L114 _private member_ `int cols;`
- L121 _public function_ `DimInfo(int rows, int cols) : rows(rows)`
- L131 _private member_ `int rows;`
- L138 _public function_ `DimInfo(int rows, int cols) : rows(rows), cols(cols)`

#### class `internal::DimInfo`  
`template <int R> class DimInfo<R, -1>`  
_L101-115_
- L95 _public function_ `DimInfo(int, int)`
- L96 _public function_ `static constexpr int Rows()`
- L97 _public function_ `static constexpr int Cols()`
- L104 _public function_ `DimInfo(int rows, int cols) : cols(cols)`
- L110 _public function_ `int Rows() const`
- L111 _public function_ `int Cols() const`
- L114 _private member_ `int cols;`
- L121 _public function_ `DimInfo(int rows, int cols) : rows(rows)`
- L131 _private member_ `int rows;`
- L138 _public function_ `DimInfo(int rows, int cols) : rows(rows), cols(cols)`

#### class `internal::DimInfo`  
`template <int C> class DimInfo<-1, C>`  
_L118-132_
- L95 _public function_ `DimInfo(int, int)`
- L96 _public function_ `static constexpr int Rows()`
- L97 _public function_ `static constexpr int Cols()`
- L104 _public function_ `DimInfo(int rows, int cols) : cols(cols)`
- L110 _public function_ `int Rows() const`
- L111 _public function_ `int Cols() const`
- L114 _private member_ `int cols;`
- L121 _public function_ `DimInfo(int rows, int cols) : rows(rows)`
- L131 _private member_ `int rows;`
- L138 _public function_ `DimInfo(int rows, int cols) : rows(rows), cols(cols)`

#### class `internal::DimInfo`  
`template <> class DimInfo<-1, -1>`  
_L135-149_
- L95 _public function_ `DimInfo(int, int)`
- L96 _public function_ `static constexpr int Rows()`
- L97 _public function_ `static constexpr int Cols()`
- L104 _public function_ `DimInfo(int rows, int cols) : cols(cols)`
- L110 _public function_ `int Rows() const`
- L111 _public function_ `int Cols() const`
- L114 _private member_ `int cols;`
- L121 _public function_ `DimInfo(int rows, int cols) : rows(rows)`
- L131 _private member_ `int rows;`
- L138 _public function_ `DimInfo(int rows, int cols) : rows(rows), cols(cols)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace internal`
- L87 _namespace_ `namespace internal`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/PatternCheck.h` (Private)


#### class `PatternCheck`  
`template <class T> class PatternCheck`  
_L14-50_
- desc: Helper class to check whether the sparsity pattern of a matrix has changed.
- L18 _public function_ `template <int Options> bool checkAndUpdatePattern(const Eigen::SparseMatrix<T, Options>& mat)`
- L45 _private member_ `Eigen::VectorXi jtjPattern;`
- L46 _private member_ `int options = 0;`
- L47 _private member_ `int64_t rows = 0;`
- L48 _private member_ `int64_t cols = 0;`
- L49 _private member_ `int64_t numNonZeros = 0;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/RobustLoss.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> void makeDiag(SparseMatrix<T>* sparseMat, const Vector<T>& diagValues)`
- L80 _function_ `template <class T> DiffData<T> smoothL1(const DiffData<T>& diffData, T beta, bool calcSqrt = true)` — @brief Compute a smooth L1 loss. A smooth L1 penalty variant is implemented by this function. It behaves like an L2 around zero and like an L1 far away from it. The option to return the square root, rather than just the loss value, facilitates the application in the context of Gauss-Newton optimization.
- L163 _function_ `template <class T> DiffData<T> generalizedCharbonnier(const DiffData<T>& diffData, T alpha, T eps, bool calcSqrt = true, bool zeroMin = true, T smallEps = T(1e-07))` — @brief Compute the generalized Charbonnier loss. This function establishes a generalized Charbonnier loss. It is a robust loss which can provide edge-preserving smoothing regularization for rig inverse problems. The square root of the loss can be optionally computed.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/Variable.h` (Private)


#### class `Variable`  
`template <class T> class Variable`  
_L13-189_
- L16 _public typedef_ `using value_type = T;`
- L19 _public function_ `Variable(const Vector<T>& vector) : m_outputDimension(int(vector.size())) , m_updateDimension(int(vector.size())) , m_constant(false) , m_value(vector) , m_cachedLocalJacobian()`
- L27 _public function_ `Variable(int outputDimension, int updateDimension) : m_outputDimension(outputDimension) , m_updateDimension(updateDimension) , m_constant(false) , m_value(Vector<T>::Zero(m_outputDimension)) , m_cachedLocalJacobian()`
- L35 _public function_ `Variable(int outputDimension) : Variable(outputDimension, outputDimension)`
- L39 _public prototype_ `virtual ~Variable() = default;`
- L42 _public prototype_ `Variable(Variable&&) = default;` — accept copy and move constructor as we are not duplicating the objects this way
- L43 _public prototype_ `Variable& operator=(Variable&&) = default;`
- L45 _public function_ `int OutputDimension() const`
- L46 _public function_ `int UpdateDimension() const`
- L47 _public function_ `int Size() const`
- L49 _public function_ `void MakeConstant()`
- L51 _public function_ `virtual void MakeMutable()`
- L53 _public function_ `bool IsConstant() const`
- L55 _public function_ `const Vector<T>& Value() const`
- L57 _public function_ `DiffData<T> Evaluate(Context<T>* context = nullptr)`
- L75 _public prototype_ `virtual void Set(const Vector<T>& value) = 0;` — Sets the variable \p value. The dimension of \p value needs to be OutputDimension(). A variable may have its internal valid manifold, and the function will project the value to the corresponding manifold. This means that calling Value() will return a value that may be different from the one passed to Set().
- L78 _public prototype_ `virtual void Update(const Vector<T>& dx) = 0;` — Updates the variable values by an offset dx. The dimension of dx needs to be UpdateDimension()
- L81 _public prototype_ `virtual bool RealJacobian() = 0;` — Method indicating with the Jacobian is the real Jacobian or some simplification (e.g. the Jacobian may not include the projection to the manifold).
- L84 _protected function_ `void SetValue(const VectorConstPtr<T>& valuePtr, bool projectToManifold)`
- L98 _protected function_ `void SetValue(const T* data, int64_t size, bool projectToManifold)`
- L110 _protected function_ `void InvalidateCachedJacobian()`
- L112 _protected function_ `Variable(const Variable& other) : m_outputDimension(other.m_outputDimension) , m_updateDimension(other.m_updateDimension) , m_constant(other.m_constant) , m_value(other.m_value) , m_cachedLocalJacobian()`
- L120 _protected function_ `Variable& operator=(const Variable& other)`
- L134 _private function_ `JacobianConstPtr<T> GlobalJacobianMatrixPtr(Context<T>* context)`
- L154 _private function_ `void SetValue(Vector<T>&& value)`
- L161 _private function_ `void SetValue(const Vector<T>& value)`
- L168 _private function_ `SparseMatrixConstPtr<T> LocalJacobianMatrixPtr()`
- L178 _private prototype_ `virtual SparseMatrixConstPtr<T> CalculateLocalJacobianMatrix() = 0;`
- L181 _private prototype_ `virtual void ProjectToManifold(Vector<T>& value) = 0;` — Projects the variable to the valid manifold of the underlying representation.
- L184 _private member_ `int m_outputDimension;`
- L185 _private member_ `int m_updateDimension;`
- L186 _private member_ `bool m_constant = false;`
- L187 _private member_ `Vector<T> m_value;`
- L188 _private member_ `SparseMatrixConstPtr<T> m_cachedLocalJacobian;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/VectorVariable.h` (Private)


#### class `VectorVariable`  
`template <class T> class VectorVariable : public Variable<T>`  
_L12-107_
- inherits: `Variable<T>`
- L15 _public function_ `VectorVariable(int size) : Variable<T>(size)`
- L16 _public function_ `VectorVariable(const Vector<T>& vector) : Variable<T>(vector)`
- L17 _public prototype_ `VectorVariable(VectorVariable&& other) = default;`
- L18 _public prototype_ `VectorVariable& operator=(VectorVariable&& other) = default;`
- L20 _public function_ `void SetZero()`
- L22 _public function_ `virtual void Set(const Vector<T>& value) override`
- L29 _public function_ `virtual void Update(const Vector<T>& dx) override`
- L35 _public function_ `virtual bool RealJacobian() override`
- L41 _public function_ `virtual void MakeMutable() override` — Specialization of MakeMutable() to also clear any constant indices
- L48 _public function_ `void MakeIndividualIndicesConstant(const std::vector<int>& constantIndices)` — Make invidual values of the variable constant
- L62 _public function_ `const std::vector<int>& ConstantIndices() const` — @return which indices are constant
- L66 _protected function_ `VectorVariable(int size, int updateDimension) : Variable<T>(size, updateDimension)` — Only subclasses can call this constructor to set up a vector variable with a different update dimension
- L68 _protected prototype_ `VectorVariable(const VectorVariable& other) = default;`
- L69 _protected prototype_ `VectorVariable& operator=(const VectorVariable&) = default;`
- L72 _private function_ `virtual SparseMatrixConstPtr<T> CalculateLocalJacobianMatrix() override`
- L103 _private function_ `virtual void ProjectToManifold(Vector<T>& ) override` — Nothing to do for a generic vector variable.
- L106 _private member_ `std::vector<int> m_constantIndices;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/VertexOptimization.h` (Private)


#### struct `VertexOptimization`  
`template <class T> struct VertexOptimization`  
_L60-402_
- desc: Class supporting vertex optimization problems
- L62 _public typedef_ `using ScalarType = T;`
- L64 _public member_ `int numVertices;`
- L67 _public member_ `Eigen::SparseMatrix<T, Eigen::RowMajor> baseLtL;` — Base Laplacian
- L69 _public member_ `Eigen::SparseMatrix<T, Eigen::RowMajor> tmpLtL;` — Temporary laplacian with removed "fixed" rows
- L71 _public member_ `Eigen::SparseMatrix<T, Eigen::RowMajor> LtL;` — Final laplacian with removed "fixed" rows and columns
- L73 _public member_ `std::vector<Eigen::Matrix<T, 3, 3>> diagonalBlocks;`
- L74 _public member_ `std::vector<bool> validDiagonal;`
- L75 _public member_ `std::vector<int> vertexMap;`
- L77 _public member_ `std::vector<Eigen::Matrix<T, 3, 3>> offDiagonalBlocks;`
- L78 _public member_ `std::vector<std::pair<int, int>> offDiagonalIndices;`
- L80 _public member_ `Eigen::VectorX<T> Jtb;`
- L82 _public member_ `std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool> threadPool;`
- L84 _public function_ `int NumUnknowns() const`
- L85 _public function_ `int NumVariableVertices() const`
- L86 _public function_ `int NumVertices() const`
- L87 _public function_ `bool HasFixedVertices() const`
- L89 _public function_ `void SetTopology(const Mesh<T>& mesh)`
- L109 _public function_ `void Clear(const std::vector<int>& fixVertices = {})`
- L153 _public function_ `void Setup(const Eigen::Matrix<T, 3, -1>& vertexOffsets, T laplacianRegularization, T offsetRegularization, T updateRegularization)`
- L272 _public function_ `template <int ResidualSize, int NumConstraintVertices> void AddConstraints(const VertexConstraints<T, ResidualSize, NumConstraintVertices>& vertexConstraints)`
- L313 _public function_ `const Eigen::VectorX<T>& Rhs() const`
- L315 _public function_ `Eigen::VectorX<T> DiagonalPreconditioner() const`
- L350 _public function_ `int NumSegments() const`
- L352 _public function_ `void MatrixMultiply(Eigen::Ref<Eigen::VectorX<T>> out, int segmentId, Eigen::Ref<const Eigen::VectorX<T>> x) const`
- L378 _public function_ `Eigen::Matrix<T, 3, -1> Solve(int cgIterations) const`

#### Free symbols / members of external scopes

- L18 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L32 _function_ `auto func = [&](int start, int end)` (scope `CARBON_NAMESPACE_BEGIN`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/AddFunction.h` (Private)


#### class `AddFunction`  
`template <class T> class AddFunction`  
_L16-49_
- desc: Function to add two value vectors: f(x) = a(x) + b(x)
- L19 _public function_ `AddFunction()`
- L21 _public function_ `DiffData<T> Evaluate(const DiffData<T>& a, const DiffData<T>& b) const`
- L43 _public function_ `template <int R, int C> DiffDataMatrix<T, R, C> Evaluate(const DiffDataMatrix<T, R, C>& a, const DiffDataMatrix<T, R, C>& b) const`

#### Free symbols / members of external scopes

- L52 _function_ `template <class T> DiffData<T> operator+(const DiffData<T>& a, const DiffData<T>& b)`
- L55 _function_ `template <class T, int R, int C> DiffDataMatrix<T, R, C> operator+(const DiffDataMatrix<T, R, C>& a, const DiffDataMatrix<T, R, C>& b)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/AxisConstraintFunction.h` (Private)


#### class `AxisConstraintFunction`  
`template <class T> class AxisConstraintFunction`  
_L12-48_
- L18 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, 3, -1>& v, const int axis, const int minIndex, const int maxIndex, const T targetLength, const T weight)` — Function to calculate a length constraint measured along an axis (i.e. max(v) - min(v) = l)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/BarycentricCoordinatesFunction.h` (Private)


#### class `BarycentricCoordinatesFunction`  
`template <class T, int R, int C = 3> class BarycentricCoordinatesFunction`  
_L18-104_
- desc: Function to add gather values from diff data
- L26 _public function_ `static DiffDataMatrix<T, R, -1> Evaluate(const DiffDataMatrix<T, R, -1>& vertices, const std::vector<BarycentricCoordinates<T, C>>& barycentricCoordinates)` — Evaluates the barycentric coordinates on the input vertices
- L66 _public function_ `static DiffDataMatrix<T, R, -1> Evaluate(const DiffDataMatrix<T, R, -1>& vertices, const std::vector<BarycentricCoordinatesExt<T, C>>& barycentricCoordinates)`

#### class `BarycentricCoordinatesFunctionExt`  
`template <class T> class BarycentricCoordinatesFunctionExt`  
_L111-156_
- desc: Function to add gather values from diff data
- L118 _public function_ `static DiffDataMatrix<T, 3, -1> Evaluate(const DiffDataMatrix<T, 2, -1>& barycentricUVNew, const Eigen::Matrix<T, 3, -1>& vertices, const std::vector<BarycentricCoordinatesExt<T, 3>>& barycentricCoordinatesOld)` — Evaluates the barycentric coordinates on the input vertices

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/BarycentricPointPointConstraintFunction.h` (Private)


#### class `BarycentricPointPointConstraintFunction`  
`template <class T, int C, typename DISCARD = typename std::enable_if<(C == 2 || C ==3), void>::type> class BarycentricPointPointConstraintFunction`  
_L13-67_
- L20 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const std::vector<BarycentricCoordinates<T, 3> >& barycentricCoordinates, const Eigen::Matrix<T, C, -1>& targets, const Vector<T>& weights, const T wPoint2Point)` — Function to calculate the an point-point constraint from vertices given as barycentric coordinates: residual(x) = sqrt(wPoint2Point) * w * (v(x) - target)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/ColwiseAddFunction.h` (Private)


#### class `ColwiseAddFunction`  
`template <class T> class ColwiseAddFunction`  
_L15-49_
- desc: Function to add a vector to a matrix colwise f(x).colwise() += t(x)
- L18 _public function_ `ColwiseAddFunction()`
- L21 _public function_ `template <int R, int C> DiffDataMatrix<T, R, C> colwiseAddFunction(const DiffDataMatrix<T, R, C>& matA, const DiffDataMatrix<T, R, 1>& vecB) const`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/DualQuaternionFunctions.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> SparseMatrix<T> DualQuaternionNormalizationJacobian(const DiffData<T>& dq)`
- L103 _function_ `template <class T> DiffData<T> DualQuaternionNormalizeDiff(const DiffData<T>& dq)`
- L140 _function_ `template <class T> DiffData<T> DualQuaternionVectorTransformDiff(const DiffData<T>& dq, const Eigen::Vector3<T>& v)`
- L166 _function_ `template <class T> DiffData<T> DualQuaternionVectorTransformDiff_2(const DiffData<T>& dq, const Eigen::Vector3<T>& v)`
- L224 _function_ `template <class T> DiffDataMatrix<T, 3, -1> DualQuaternionShapeTransformDiff(const DiffData<T>& dq, const Eigen::Matrix<T, 3, -1>& v)`
- L293 _function_ `template <class T> DiffData<T> DualQuaternionQuatConjugateDiff(const DiffData<T>& dq)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/GatherFunction.h` (Private)


#### class `GatherFunction`  
`template <class T> class GatherFunction`  
_L18-63_
- desc: Function to add gather values from diff data
- L21 _public function_ `GatherFunction()`
- L23 _public function_ `static DiffData<T> Gather(const DiffData<T>& a, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)`
- L49 _public function_ `template <int R, int C1, int C2> static DiffDataMatrix<T, R, C1> GatherColumns(const DiffDataMatrix<T, R, C2>& a, const Eigen::VectorX<int>& colIndices)`
- L59 _public function_ `template <int R, int C1, int C2> static DiffDataMatrix<T, R, C1> GatherColumns(const DiffDataMatrix<T, R, C2>& a, const std::vector<int>& colIndices)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/LengthConstraintFunction.h` (Private)


#### class `LengthConstraintFunction`  
`template <class T, int C, typename DISCARD = typename std::enable_if<(C == 3), void>::type> class LengthConstraintFunction`  
_L13-141_
- L20 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const std::vector<std::vector<int>>& lines, const Vector<T>& target_lengths, const T wLength)` — Function to calculate a length constraint measuremed along a vertex line given by indices i_0...i_n: residual(x) = sqrt(wLength) * (sum(norm(i_{j+1} - i_{j})) - target_length)
- L85 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const std::vector<std::vector<BarycentricCoordinates<T, C>>>& lines, const Vector<T>& target_lengths, const T wLength)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/MatrixMultiplyFunction.h` (Private)


#### class `MatrixMultiplyFunction`  
`template <class T> class MatrixMultiplyFunction`  
_L17-162_
- desc: Function to multiply two matrices: f(x) = A(x) * B(x)
- L20 _public function_ `MatrixMultiplyFunction()`
- L23 _public function_ `template <int R1, int C1, int R2, int C2> static DiffDataMatrix<T, R1, C2> DenseMatrixMatrixMultiply(const DiffDataMatrix<T, R1, C1>& matA, const DiffDataMatrix<T, R2, C2>& matB)`
- L96 _public function_ `template <int R, int C> static DiffData<T> DenseMatrixVectorMultiply(const DiffDataMatrix<T, R, C>& mat, const DiffData<T>& vec)`
- L108 _public function_ `template <int R, int C> static DiffData<T> SparseMatrixVectorMultiply(const DiffDataSparseMatrix<T, R, C>& mat, const DiffData<T>& vec)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/PointPointConstraintFunction.h` (Private)


#### class `PointPointConstraintFunction`  
`template <class T, int C, typename DISCARD = typename std::enable_if<(C == 2 || C == 3), void>::type> class PointPointConstraintFunction`  
_L12-117_
- L19 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const Eigen::Matrix<T, C, -1>& targets, const Vector<T>& weights, const T wPoint2Point)` — Function to calculate the an point-point constraint: residual(x) = sqrt(wPoint2Point) * w * (v(x) - target)
- L69 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const Eigen::VectorXi& indices, const Eigen::Matrix<T, C, -1>& targets, const Vector<T>& weights, const T wPoint2Point)` — Function to calculate the an point-point constraint: residual(x) = sqrt(wPoint2Point) * w * (v(x) - target) Additional indices vector specifying on which vertices to evaluate the constraints. In this case the targets and weights need to have the samme number of points as the size of the indices vector.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/PointSurfaceConstraintFunction.h` (Private)


#### class `PointSurfaceConstraintFunction`  
`template <class T, int C> class PointSurfaceConstraintFunction`  
_L15-130_
- desc: Function to calculate the point surface constraint: residual(x) = sqrt(wNormal) * w * normal.dot(v(x) - target)
- L18 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const Eigen::Vector<T, C>* targets, const Eigen::Vector<T, C>* normals, const T* weights, const T wNormal)`
- L55 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const Eigen::Matrix<T, C, -1>& targets, const Eigen::Matrix<T, C, -1>& normals, const Vector<T>& weights, const T wNormal)`
- L74 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const int* indices, const Eigen::Vector<T, C>* targets, const Eigen::Vector<T, C>* normals, const T* weights, const int numConstraints, const T wNormal)`
- L111 _public function_ `static DiffData<T> Evaluate(const DiffDataMatrix<T, C, -1>& v, const Eigen::VectorXi& indices, const Eigen::Matrix<T, C, -1>& targets, const Eigen::Matrix<T, C, -1>& normals, const Vector<T>& weights, const T wNormal)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/ProjectionConstraintFunction.h` (Private)


#### class `ProjectionConstraintFunction`  
`template <class T> class ProjectionConstraintFunction`  
_L12-59_
- L18 _public function_ `static DiffData<T> Evaluate( const DiffData<T>& inputVector, const std::vector<Vector<T>>& projectionVectors, const Vector<T>& targetValues, const T weight)` — Function to a soft error based on the limits of the riglogic class

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/RigidityConstraintFunction.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int R, int C> DiffData<T> RigidityConstraintFunction(const DiffDataMatrix<T, R, C>& mat, T weight)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/ScaleFunction.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> DiffData<T> operator*(const DiffData<T>& a, const T scale)`
- L26 _function_ `template <class T> DiffData<T> operator*(const T scale, const DiffData<T>& a)`
- L29 _function_ `template <class T, int R, int C> DiffDataMatrix<T, R, C> operator*(const DiffDataMatrix<T, R, C>& a, const T scale)`
- L35 _function_ `template <class T, int R, int C> DiffDataMatrix<T, R, C> operator*(const T scale, const DiffDataMatrix<T, R, C>& a)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/ScatterFunction.h` (Private)


#### class `ScatterFunction`  
`template <class T> class ScatterFunction`  
_L16-54_
- desc: Function to add scatter values from diff data
- L19 _public function_ `ScatterFunction()`
- L21 _public function_ `static DiffData<T> Scatter(const DiffData<T>& a, int outputSize, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)`
- L46 _public function_ `template <int R, int C1, int C2> static DiffDataMatrix<T, R, C1> ScatterColumns(const DiffDataMatrix<T, R, C2>& a, int outputCols, const Eigen::VectorX<int>& colIndices)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/SubtractFunction.h` (Private)


#### class `SubtractFunction`  
`template <class T> class SubtractFunction`  
_L16-50_
- desc: Function to subtract two value vectors: f(x) = a(x) - b(x)
- L19 _public function_ `SubtractFunction()`
- L21 _public function_ `DiffData<T> Evaluate(const DiffData<T>& a, const DiffData<T>& b) const`
- L44 _public function_ `template <int R, int C> DiffDataMatrix<T, R, C> Evaluate(const DiffDataMatrix<T, R, C>& a, const DiffDataMatrix<T, R, C>& b) const`

#### Free symbols / members of external scopes

- L54 _function_ `template <class T> DiffData<T> operator-(const DiffData<T>& a, const DiffData<T>& b)`
- L57 _function_ `template <class T, int R, int C> DiffDataMatrix<T, R, C> operator-(const DiffDataMatrix<T, R, C>& a, const DiffDataMatrix<T, R, C>& b)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/VertexConstraintsFunction.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int ResidualSize, int NumConstraintVertices> DiffData<T> ApplyVertexConstraints(const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& baseVertices, const VertexConstraints<T, ResidualSize, NumConstraintVertices>& vertexConstraints)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/functions/WeightedSumFunction.h` (Private)


#### class `WeightedSumFunction`  
`template <class T> class WeightedSumFunction`  
_L15-82_
- desc: Function to calculated the weighted sum of multiple vectors: f(x) = w1 f1(x) + w2 f2(x) + ...
- L18 _public function_ `WeightedSumFunction()`
- L20 _public function_ `DiffData<T> Evaluate(const std::vector<std::reference_wrapper<const DiffData<T>>>& inputs, const std::vector<T>& weights) const`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/Affine.h` (Private)


#### class `Affine`  
`template <class T, int R, int C, typename DISCARD = typename std::enable_if<(R > 0 && C > 0), void>::type> class Affine`  
_L30-126_
- desc: An affine transformation maps y = Mx + b where M is the linear transformation and b a translation https://en.wikipedia.org/wiki/Affine_transformation The matrix is stored as a homogenous matrix i.e. A =  |M b| |0 1| Hence, |y| = A * |x| |1|		 |1| Dimensions: R: row dimension of M and b C: column dimension of M Dimensions of the internal matrix: (R+1),(C+1). This is consitent with Eigen::Transform.
- L33 _public typedef_ `using ScalarType = T;`
- L34 _public typedef_ `using MatrixType = Eigen::Matrix<T, R + 1, C + 1>;`
- L37 _public function_ `Affine()`
- L42 _public function_ `Affine(const Eigen::Matrix<T, R + 1, C + 1>& mat) : m_affineMatrix(mat)`
- L45 _public function_ `Affine& operator=(const Eigen::Matrix<T, R + 1, C + 1>& mat)`
- L51 _public function_ `void SetLinear(const Eigen::Matrix<T, R, C>& linear)`
- L52 _public function_ `Eigen::Matrix<T, R, C> Linear() const`
- L54 _public function_ `void SetTranslation(const Eigen::Vector<T, R>& translation)`
- L55 _public function_ `Eigen::Vector<T, R> Translation() const`
- L57 _public function_ `const Eigen::Matrix<T, R + 1, C + 1>& Matrix() const`
- L59 _public function_ `void SetMatrix(const Eigen::Matrix<T, R + 1, C + 1>& mat)`
- L61 _public function_ `static Affine FromTranslation(const Eigen::Vector<T, R>& translation)`
- L68 _public function_ `static Affine FromLinear(const Eigen::Matrix<T, R, C>& linear)`
- L75 _public function_ `static inline Affine FromEulerXYZ(const Eigen::Vector3f& eulerXYZ, const Eigen::Vector3f& translation, bool radians = true)`
- L90 _public function_ `Eigen::Matrix<T, R, -1> Transform(const Eigen::Matrix<T, C, -1>& vertices) const`
- L102 _public function_ `Affine operator*(const Affine& aff) const`
- L107 _public function_ `void SetIdentity()`
- L109 _public function_ `Affine Inverse() const`
- L119 _public function_ `bool HasScaling(const T eps = T(1e-4)) const` — @returns True if the linear component of the affine transformation contains scale
- L125 _private member_ `Eigen::Matrix<T, R + 1, C + 1> m_affineMatrix;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/AffineVariable.h` (Private)


#### class `AffineVariable`  
`template <class LinearTransformationVariable> class AffineVariable`  
_L19-96_
- desc: An AffineTransformationVariable represents an affine transformation of a set of vertices.
- L22 _public typedef_ `typedef typename LinearTransformationVariable::value_type T;`
- L23 _public member_ `static constexpr int R = LinearTransformationVariable::ROWS;`
- L24 _public member_ `static constexpr int C = LinearTransformationVariable::COLS;`
- L27 _public function_ `AffineVariable()`
- L33 _public function_ `DiffDataAffine<T, R, C> EvaluateAffine(Context<T>* context)`
- L41 _public function_ `void SetAffine(const ::TITAN_NAMESPACE::Affine<T, R, C>& A)`
- L47 _public function_ `TITAN_NAMESPACE::Affine<T, R, C> Affine() const`
- L59 _public function_ `static ::TITAN_NAMESPACE::Affine<T, R, C> Random()` — Creates a valid affine transformation matrix. Valid means the linear part of the transformation is on the manifold of the underlying LinearTransformationVariable.
- L69 _public function_ `void MakeConstant(bool makeLinearConstant, bool makeTranslationConstant)`
- L90 _public function_ `LinearTransformationVariable& LinearVariable()`
- L91 _public function_ `MatrixVariable<T, R, 1>& TranslationVariable()`
- L94 _private member_ `LinearTransformationVariable m_linearTransformationVariable;`
- L95 _private member_ `MatrixVariable<T, R, 1> m_translationVariable;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/BarycentricCoordinates.h` (Private)


#### class `BarycentricCoordinates`  
`template <class T, int C = 3> class BarycentricCoordinates`  
_L20-111_
- desc: Representation of barycentric coordinates of a point in a triangle (C=3) or tetrahedron (C=4). Note: negative barycentric coordinates are supported and enable extrapolation outside of the tri/tet.
- L25 _public function_ `BarycentricCoordinates()`
- L31 _public function_ `BarycentricCoordinates(const Eigen::Vector<int, C>& indices, const Eigen::Vector<T, C>& weights) : m_indices(indices) , m_weights(weights)`
- L37 _public function_ `template <int R> Eigen::Vector<T, R> Evaluate(const Eigen::Ref<const Eigen::Matrix<T, R, -1>>& vertices) const`
- L47 _public function_ `int Index(int i) const`
- L52 _public function_ `T Weight(int i) const`
- L57 _public function_ `const Eigen::Vector<int, C>& Indices() const`
- L62 _public function_ `const Eigen::Vector<T, C>& Weights() const`
- L67 _public function_ `static BarycentricCoordinates SingleVertex(int vID)`
- L81 _public function_ `bool operator==(const BarycentricCoordinates& other) const`
- L87 _public prototype_ `static Eigen::Vector<T, C> ComputeBarycentricCoordinates(const Eigen::Vector<T, 3>& p, const Eigen::Vector<int, C>& indices, const Eigen::Matrix<T, 3, -1>& vertices);` — Computes barycentric coordinates of point 'p' w.r.t. a triangle/tet:
- L91 _public function_ `bool Nonnegative() const`
- L108 _private member_ `static constexpr int32_t m_version = 1;`
- L109 _private member_ `Eigen::Vector<int, C> m_indices;`
- L110 _private member_ `Eigen::Vector<T, C> m_weights;`

#### class `BarycentricCoordinatesExt`  
`template <class T, int C = 3> class BarycentricCoordinatesExt : public BarycentricCoordinates<T, C>`  
_L114-133_
- inherits: `BarycentricCoordinates<T,C>`
- L117 _public function_ `BarycentricCoordinatesExt() : BarycentricCoordinates<T, C>()`
- L122 _public function_ `BarycentricCoordinatesExt(const Eigen::Vector<int, C>& indices, const Eigen::Vector<T, C>& weights, const int triangle) : BarycentricCoordinates<T, C>(indices, weights)`
- L127 _public function_ `int Triangle() const`
- L132 _private member_ `int m_triangle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace trio`
- L137 _function_ `template <typename T, int C = 3> bool ToBinaryFile(FILE* pFile, const BarycentricCoordinates<T, C>& bcs)`
- L147 _function_ `template <typename T, int C = 3> bool FromBinaryFile(FILE* pFile, BarycentricCoordinates<T, C>& bcs)`
- L165 _function_ `template <typename T, int C = 3> bool FromBinaryFile(trio::BoundedIOStream* stream, BarycentricCoordinates<T, C>& bcs)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/BarycentricEmbedding.h` (Private)


#### class `BarycentricEmbedding`  
`template <class T> class BarycentricEmbedding`  
_L22-68_
- desc: Class representing barycentric embedding of a list of points w.r.t. a tetmesh Note: the points do not have to be inside the tetmesh; if outside, negative barycentrics will be used Note 2: the current method to compute barycentric embedding is slow, hence serialization and deserialization is supported
- L25 _public prototype_ `BarycentricEmbedding() = default;`
- L26 _public prototype_ `BarycentricEmbedding(const BarycentricEmbedding& o) = default;`
- L27 _public prototype_ `BarycentricEmbedding& operator=(const BarycentricEmbedding& o) = default;`
- L29 _public function_ `const std::vector<BarycentricCoordinates<T, 4>>& GetBarycentricCoordinates() const`
- L35 _public prototype_ `void SetBarycentricEmbedding(const Eigen::Matrix<T, 3, -1>& points, const TetMesh<T>& tetMesh);` — Computes and sets embedding of 'points' in a 'tetMesh':
- L38 _public prototype_ `void Serialize(std::string fname) const;` — Saves m_barycentricCoordinates to a file:
- L39 _public prototype_ `void Serialize(JsonElement& json) const;`
- L42 _public prototype_ `void Deserialize(std::string fname);` — Sets m_barycentricCoordinates loaded from a file:
- L43 _public prototype_ `void Deserialize(const JsonElement& json);`
- L46 _public function_ `bool allAffine() const` — Checks if all barycentric coordinates are affine (i.e. sum to 1; they may be negative but always must sum to 1):
- L55 _public function_ `T minimalBarycentricCoordinate() const`
- L67 _private member_ `std::vector<BarycentricCoordinates<T, 4>> m_barycentricCoordinates;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/Camera.h` (Private)


#### class `Camera`  
`template <class T> class Camera`  
_L34-281_
- desc: A simple pinhole Camera with the following projection equation: @code px = K * [R|t] * Pw @code where K is a 3x3 triangular camera intrinsic matrix, R is a 3x3 3D rotation matrix, t is a 3x1 translation vector, Pw is a 3D point in world coordinates, and px is the projected point on the image plane (in pixels). K =  | fx  a  cx | |  0  fy cy | |  0  0  1  | Subclasses of the camera may also provide additional distortion parameters. Important: the camera model assumes the origin of the image is the corner of the top left pixel. so the center of the top-left pixel has coordinates (0.5, 0.5). This is different to opencv where the origin is at the center of the top-left pixel.
- L37 _public function_ `Camera() : m_intrinsics(Eigen::Matrix<T, 3, 3>::Identity()) , m_extrinsics() , m_width(0) , m_height(0)`
- L44 _public prototype_ `virtual ~Camera() = default;`
- L46 _public function_ `int Width() const`
- L47 _public function_ `void SetWidth(int width)`
- L49 _public function_ `int Height() const`
- L50 _public function_ `void SetHeight(int height)`
- L52 _public function_ `const std::string& Label() const`
- L53 _public function_ `void SetLabel(const std::string& label)`
- L55 _public function_ `const Eigen::Matrix<T, 3, 3>& Intrinsics() const`
- L56 _public function_ `void SetIntrinsics(const Eigen::Matrix<T, 3, 3>& intrinsics)`
- L65 _public function_ `const Affine<T, 3, 3>& Extrinsics() const`
- L66 _public function_ `void SetExtrinsics(const Affine<T, 3, 3>& extrinsics)`
- L69 _public function_ `const Eigen::Vector3<T> Origin() const` — @return the camera origin in world coordinates
- L72 _public function_ `Eigen::Vector2<T> Project(const Eigen::Vector3<T>& pt, bool withExtrinsics) const` — Projects a 3d point into the image
- L91 _public function_ `Eigen::Vector3<T> ToImagePlane(const Eigen::Vector2<T>& pix) const` — @return the image plane position for pixel @pix
- L99 _public function_ `Eigen::Vector3<T> Unproject(const Eigen::Vector2<T>& pix, T depth, bool withExtrinsics) const` — Unprojects a 2d point into 3D
- L113 _public function_ `void Scale(const T scale)` — Scales the camera parameters which is equivalent to scaling images associated with the camera.
- L147 _public function_ `Eigen::Matrix<T, 4, 4> RenderingProjectionMatrix(const T depthNear, const T depthFar) const` — Calculates a rendering projection matrix without extrinsics. x is mapped between [-1, 1] y is mapped between [-1, 1] z is mapped between [1, 0] where 1=depthNear, and 0=depthFar Calculation to pixel coordinates: [0, width], [0, height] x' = fx X/Z + skew Y/Z + cx y' = fy X/Z + cy Calculation to normalized coordinates: [-1, 1], [-1, 1]: x'' = 2 * x' / width - 1 y'' = 2 * y' / height - 1 Depth: depthNear maps to 1, depthFar maps to 0 a/depthNear + b = 1 a/depthFar + b = 0 => a = depthNear * depthFar / (depthFar - depthNear) => b = - depthNear / (depthFar - depthNear) Important notes: 1) depthNear maps to 1, depthFar maps to 0 (as opposed to the common depthNear=0 and depthFar=1) 2) -1 is the top of the image, not the bottom 3) the camera is looking in positive z direction
- L168 _public function_ `template <bool withExtrinsics> DiffDataMatrix<T, 2, -1> Project(const DiffDataMatrix<T, 3, -1>& pts) const` — Projects the input points into the image and also calculates the Jacobian px = (K(0,0) * p[0] + K(0, 1) * p[1] + K(0,2)) / p[2] py = (K(1,1) * p[1] + K(1,2)) / p[2]
- L220 _public function_ `DiffDataMatrix<T, 2, -1> Project(const DiffDataMatrix<T, 3, -1>& pts, bool withExtrinsics) const`
- L232 _public function_ `std::vector<T> serialize() const`
- L244 _public function_ `bool deserialize(const T* data)`
- L258 _public function_ `bool deserialize(const std::vector<T>& data)`
- L270 _private member_ `Eigen::Matrix<T, 3, 3> m_intrinsics;` — The intrinsics K
- L273 _private member_ `Affine<T, 3, 3> m_extrinsics;` — The camera extrinsics [R|t]
- L276 _private member_ `int m_width;` — The image dimensions
- L277 _private member_ `int m_height;`
- L280 _private member_ `std::string m_label;` — Label of the camera (optional)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/CameraHelpers.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> Camera<T> CameraFromVerticalFOV(const T angleInRadians, int width, int height)`
- L37 _function_ `template <class T> Camera<T> CameraFromHorizontalFOV(const T angleInRadians, int width, int height)` — Calculates the intrinsic camera parameters from a camera resolution and the horizontal field of view.
- L59 _function_ `template <class T> Affine<T, 3, 3> LookAt(const Eigen::Vector3<T>& eye, const Eigen::Vector3<T>& center, const Eigen::Vector3<T>& down)` — Calculates the extrinsics for a camera using a modified version of "lookat". In this version the caller needs to define the down vector which corresponds to the positive y direction in the camera which is pointing downwards in the camera image.
- L83 _function_ `template <class T> Mesh<T> CreateImagePlane(const Camera<T>& camera, const T distance, bool withExtrinsics)` — Creates an image backplane for \p camera at \p distance. @param [in] camera          The camera for which the image plane is created. @param [in] distance        The distance at which the image plane is created. @param [in] withExtrinsics  Whether to create the image plane in world coordinates (true) or in camera coordinates (false). @return A quad mesh with a single quad with the vertices and the texture coordinates so that a camera image can be assigned as texture.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/CatmullRom.h` (Private)


#### class `CatmullRom`  
`template <class T, int D> class CatmullRom`  
_L14-40_
- L17 _public prototype_ `CatmullRom() = default;`
- L18 _public function_ `CatmullRom(const Eigen::Matrix<T, D, -1>& controlPoints, int pointsPerSegment, bool closed)`
- L24 _public prototype_ `void Set(const Eigen::Matrix<T, D, -1>& controlPoints, int pointsPerSegment, bool closed);` — Sets the control points of the catmull rom curve.
- L26 _public function_ `const Polyline<T, D>& ControlPoints() const`
- L27 _public function_ `const Polyline<T, D>& SampledPoints() const`
- L30 _public prototype_ `Eigen::Vector<T, -1> LinearResampling(const Eigen::Vector<T, -1>& values) const;` — Method to resample values at the sample points linearly based on the values at the control points.
- L32 _public function_ `bool IsClosed() const`
- L33 _public function_ `int PointsPerSegment() const`
- L36 _private member_ `Polyline<T, D> m_controlPoints;`
- L37 _private member_ `int m_pointsPerSegment = 1;`
- L38 _private member_ `bool m_closed;`
- L39 _private member_ `Polyline<T, D> m_sampledPoints;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/ClosestPointData.h` (Private)


#### struct `ClosestPointData`  
`template <class T> struct ClosestPointData`  
_L17-35_
- desc: A way of storing data to represent the closest point on a mesh in terms of BaryCentric coordinates for a triangle, and delta Vector from the triangle in terms of its local reference frame (which allows the mesh to be rotated and still obtain a sensible offset)
- L19 _public function_ `ClosestPointData()`
- L21 _public member_ `static constexpr int32_t version = 1;`
- L22 _public member_ `BarycentricCoordinates<T> bcs;`
- L23 _public member_ `T weight;`
- L24 _public member_ `Eigen::Vector<T, 3> deltaInLocalCoordSystem;` — x = delta.dot(Tangent vector), y = delta.dot(Bitangent vector), z = delta.dot(normal vector)
- L27 _public prototype_ `Eigen::Vector<T, 3> CalculateTransformedPoint(const Eigen::Matrix<T, 3, -1>& inTransformedMeshVertices, T normalOffset = 0) const;` — calculate the transformed point in the local coordinate frame; also allows an offset along the normal if we want to offset the results
- L29 _public prototype_ `ClosestPointData(const Eigen::Matrix<T, 3, -1>& inMeshVertices, const Eigen::Vector<T, 3>& inPoint, const BarycentricCoordinates<T>& inBcs, const T& inWeight);`
- L33 _private prototype_ `void CalculateLocalCoordSystem(const Eigen::Matrix<T, 3, -1>& inMeshVertices, Eigen::Vector<T, 3>& outTangent, Eigen::Vector<T, 3>& outBitangent, Eigen::Vector<T, 3>& outNormal) const;`

#### Free symbols / members of external scopes

- L38 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const ClosestPointData<T>& closestPointData);`
- L41 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, ClosestPointData<T>& closestPointData);`
- L44 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, ClosestPointData<T>& closestPointData);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/DepthmapData.h` (Private)


#### struct `DepthmapData`  
`template <class T> struct DepthmapData`  
_L13-22_
- L15 _public member_ `Camera<T> camera;`
- L16 _public member_ `Eigen::Matrix<T, 4, -1> depthAndNormals;`
- L18 _public prototype_ `void Create(const Camera<T>& cam);`
- L19 _public prototype_ `void Create(const Camera<T>& cam, const T* depthPtr, TaskThreadPool* taskThreadPool = nullptr);`
- L21 _public prototype_ `void ApplyScale(T scale, TaskThreadPool* taskThreadPool = nullptr);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/DiffDataAffine.h` (Private)


#### class `DiffDataAffine`  
`template <class T, int R, int C, typename DISCARD = typename std::enable_if<(R > 0 && C > 0), void>::type> class DiffDataAffine`  
_L17-126_
- desc: Convenience function for differentiable affine transformation Ax + b
- L20 _public typedef_ `using ScalarType = T;`
- L21 _public typedef_ `using MatrixType = Eigen::Matrix<T, R + 1, C + 1>;`
- L24 _public function_ `DiffDataAffine() : m_A(Eigen::Matrix<T, R, C>::Identity()) , m_b(Eigen::Vector<T, R>::Zero())`
- L29 _public function_ `DiffDataAffine(const Eigen::Matrix<T, R + 1, C + 1>& mat) : m_A(mat.template topLeftCorner<R, C>()) , m_b(mat.template topRightCorner<R, 1>())`
- L34 _public function_ `DiffDataAffine(const DiffDataMatrix<T, R, C>& A, const DiffDataMatrix<T, R, 1>& b) : m_A(A) , m_b(b)`
- L39 _public function_ `DiffDataAffine(DiffDataMatrix<T, R, C>&& A, DiffDataMatrix<T, R, 1>&& b) : m_A(std::move(A)) , m_b(std::move(b))`
- L44 _public function_ `DiffDataAffine(const Affine<T, R, C>& aff) : DiffDataAffine(aff.Matrix())`
- L48 _public prototype_ `DiffDataAffine(const DiffDataAffine& aff) = delete;`
- L49 _public prototype_ `DiffDataAffine(DiffDataAffine&& aff) = default;`
- L50 _public prototype_ `DiffDataAffine& operator=(const DiffDataAffine& aff) = delete;`
- L51 _public prototype_ `DiffDataAffine& operator=(DiffDataAffine&& aff) = default;`
- L54 _public function_ `DiffDataAffine Clone() const` — explicitly clone the diff data affine object as copy constructor is disabled (implementation may change in the future)
- L58 _public function_ `DiffDataAffine Multiply(const DiffDataAffine& other) const` — Multiplies two affine transformations A1 (A2 x + b2) + b1 = (A1 A2) x + (A1 b2 + b2)
- L69 _public function_ `DiffDataAffine operator*(const DiffDataAffine& aff) const`
- L74 _public function_ `static DiffDataAffine FromTranslation(const DiffDataMatrix<T, R, 1>& translation)`
- L83 _public function_ `DiffDataMatrix<T, R, -1> Transform(const DiffDataMatrix<T, C, -1>& matX) const` — Applies the affine transformation to some input data y = Ax + b
- L94 _public function_ `Eigen::Matrix<T, R + 1, C + 1> Matrix() const` — Returns the full "homogeneous" matrix
- L104 _public function_ `TITAN_NAMESPACE::Affine<T, R, C> Affine() const`
- L113 _public function_ `bool HasJacobian() const`
- L118 _public function_ `const DiffDataMatrix<T, R, C>& Linear() const`
- L119 _public function_ `DiffDataMatrix<T, R, C>& Linear()`
- L120 _public function_ `const DiffDataMatrix<T, R, 1>& Translation() const`
- L121 _public function_ `DiffDataMatrix<T, R, 1>& Translation()`
- L124 _private member_ `DiffDataMatrix<T, R, C> m_A;`
- L125 _private member_ `DiffDataMatrix<T, R, 1> m_b;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/DualQuaternion.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) #if !defined(NDEBUG) || (defined(CARBON_ENABLE_ASSERTS) && CARBON_ENABLE_ASSERTS) #define ASSERT_VALID_DQ_RESULT(dq, result) \ Eigen::Vector2<T> norm = DualQuaternionNorm(dq);`
- L12 _macro_ `#define ASSERT_VALID_DQ_RESULT(dq, result) \`
- L44 _function_ `template <class T> Vector<T> IdentityDq()`
- L53 _function_ `template <class T> Eigen::Matrix4<T> MatrixOfQuaternionPreMultiplication(const Eigen::Vector4<T>& q)`
- L64 _function_ `template <class T> Eigen::Matrix4<T> MatrixOfQuaternionPostMultiplication(const Eigen::Vector4<T>& q)`
- L75 _function_ `template <class T> Eigen::Matrix<T, 8, 8> MatrixOfDualQuaternionPreMultiplication(const Vector<T>& dq)`
- L91 _function_ `template <class T> Eigen::Matrix<T, 8, 8> MatrixOfDualQuaternionPostMultiplication(const Vector<T>& dq)`
- L107 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix3<T> DualQuaternionToRotationMatrix(const Vector<T>& dq)`
- L123 _function_ `template <class T, bool NORMALIZE> Eigen::Vector3<T> DualQuaternionToTranslationVector(const Vector<T>& dq)`
- L145 _function_ `template <class T> Vector<T> RotationMatrixTranslationVectorToDualQuaternion(const Eigen::Matrix3<T>& R, const Eigen::Vector3<T>& t)`
- L157 _function_ `template <class T> Vector<T> TranslationVectorToDualQuaternion(const Eigen::Vector3<T>& t)`
- L164 _function_ `template <class T> Eigen::Vector2<T> DualQuaternionNorm(const Vector<T>& dq)`
- L185 _function_ `template <class T> Vector<T> DualQuaternionNormalize(const Vector<T>& dq)` — Calculates the normalized dual quaternion
- L217 _function_ `template <class T, bool NORMALIZE> Vector<T> DualQuaternionQuatConjugate(const Vector<T>& dq)`
- L233 _function_ `template <class T, bool NORMALIZE> Vector<T> DualQuaternionDualQuatConjugate(const Vector<T>& dq)`
- L249 _function_ `template <class T, bool NORMALIZE> Vector<T> DualQuaternionMultiplication(const Vector<T>& dq1, const Vector<T>& dq2)`
- L281 _function_ `template <class T, bool NORMALIZE> Eigen::Vector3<T> DualQuaternionVectorTransform(const Eigen::Vector3<T>& p, const Vector<T>& dq)`
- L305 _function_ `template <class T> Eigen::Matrix<T, 3, -1> DualQuaternionShapeTransform(const Eigen::Matrix<T, 3, -1>& shape, const Vector<T>& dq)`
- L319 _function_ `template <class T> Eigen::Matrix<T, 4, 4> DualQuaternionToAffineMatrix(const Vector<T>& dq)`
- L332 _function_ `template <class T> Vector<T> AffineMatrixToDualQuaternion(const Eigen::Matrix<T, 4, 4>& m)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/DualQuaternionVariable.h` (Private)


#### class `DualQuaternionVariable`  
`template <class T> class DualQuaternionVariable : public VectorVariable<T>`  
_L21-67_
- inherits: `VectorVariable<T>`
- L24 _public function_ `DualQuaternionVariable() : VectorVariable<T>( 8)`
- L28 _public function_ `DualQuaternionVariable(const Vector<T>& value) : VectorVariable<T>( 8)`
- L35 _public function_ `virtual bool RealJacobian() override`
- L40 _public function_ `void SetIdentity()`
- L48 _private function_ `virtual SparseMatrixConstPtr<T> CalculateLocalJacobianMatrix() override`
- L63 _private function_ `virtual void ProjectToManifold(Vector<T>& value) override`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/EulerAngles.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> Eigen::Matrix<T, 3, 3> EulerX(const T angleInRadians)`
- L30 _function_ `template <class T> Eigen::Matrix<T, 3, 3> EulerY(const T angleInRadians)`
- L48 _function_ `template <class T> Eigen::Matrix<T, 3, 3> EulerZ(const T angleInRadians)`
- L67 _function_ `template <typename T> Eigen::Vector3<T> RotationMatrixToEulerXYZ(const Eigen::Matrix<T, 3, 3>& R)` — Calculates the Euler angles given the rotation matrix assuming the XYZ order of Maya i.e. in post-multiply this is EulerZ() * EulerY() * EulerX()
- L71 _function_ `auto wrapToPi = [](T angle)` (scope `RotationMatrixToEulerXYZ`)
- L96 _function_ `template <class T> Eigen::Matrix<T, 3, 3> EulerXYZ(const T rx, const T ry, const T rz)` — Calculates the Euler rotation using the XYZ order of Maya i.e. in post-multiply this is EulerZ() * EulerY() * EulerX() Expects the angles in radians.
- L123 _function_ `template <class T> Eigen::Matrix<T, 3, 3> EulerXYZ(const Eigen::Vector3<T>& angles)`
- L131 _function_ `template <class T> SparseMatrix<T> EulerXYZJacobian(const T rx, const T ry, const T rz)` — Calculates the Jacobian of EulerXYZ
- L185 _function_ `template <class T> Eigen::Matrix<T, 9, 3, Eigen::RowMajor> EulerXYZJacobianDense(const T rx, const T ry, const T rz)` — Calculates the Jacobian of EulerXYZ
- L241 _function_ `template <class T> Eigen::Matrix<T, 3, 3> EulerXYZAndScale(const T rx, const T ry, const T rz, const T sx, const T sy, const T sz)`
- L269 _function_ `template <class T> SparseMatrix<T> EulerXYZAndScaleJacobian(const T rx, const T ry, const T rz, const T sx, const T sy, const T sz)` — Calculates the Jacobian of EulerXYZAndScale
- L335 _function_ `template <class T> Eigen::Matrix<T, 9, 6, Eigen::RowMajor> EulerXYZAndScaleJacobianDense(const T rx, const T ry, const T rz, const T sx, const T sy, const T sz)` — Calculates the Jacobian of EulerXYZAndScale

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/GeometryHelpers.h` (Private)


#### Free symbols / members of external scopes

- L12 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::geoutils) std::vector<std::vector<int>> VertexAdjacency(const Eigen::Matrix<int, 3, -1>& Triangles);`
- L30 _prototype_ `void TriangleAdjacency( const Eigen::Matrix<int, 3, -1>& triangles, Eigen::Matrix<int, 3, -1>& adjacency, Eigen::Matrix<int, 3, -1>& outerTriangleEdges);` — Find the neighboring triangles of each mesh triangle. @param triangles is the input topology @param adjacency (result) contains the neighbors ordered ordered according to the i-th traingle edges. Edge 0: {triangles(0, i), triangles(1, i)}; edge 1: {triangles(1, i), triangles(2, i)}; edge 2: {triangles(2, i), triangles(0, i)}; @param outerTriangleEdges (result) contains for each i-th triangle the id of the edge of the j-th triangle that is shared by (i, j).
- L47 _prototype_ `void QuadAdjacency( const Eigen::Matrix<int, 4, -1>& quads, Eigen::Matrix<int, 4, -1>& adjacency, Eigen::Matrix<int, 4, -1>& outerQuadEdges);` — Find the neighboring quads of each mesh triangle. @param quads is the input topology @param adjacency (result) contains the neighbors ordered ordered according to the i-th traingle edges. Edge 0: {quads(0, i), quads(1, i)}; edge 1: {quads(1, i), quads(2, i)}; edge 2: {quads(2, i), quads(3, i)}; edge 3: {quads(3, i), quads(0, i)}; @param outerTriangleEdges (result) contains for each i-th quad the id of the edge of the j-th quad that is shared by (i, j).
- L55 _prototype_ `std::vector<std::vector<int>> VertexAdjacency(const Eigen::Matrix<int, 4, -1>& Tets);` — Calculate vertex adjacency for a given tet mesh
- L61 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreatePyramid(const Eigen::Matrix<T, 3, 1>& origin, const Eigen::Matrix<T, 3, 1>& node, T baseDistance)` — Creates a pyramid using origin as a center of the base and node for the apex
- L104 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreateCylinder( const T radius, const T height, const int numSamplesCircle, const int numSamplesHeight)` — Creates a cylinder by stacking circles from the plane x = 0 y = 0
- L192 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreateTorus( const Eigen::Vector<T, 2>& radiuses, const Eigen::Vector2i& numSamplesPhiTheta, bool triangulate = false)` — Creates torus by stacking circles around the origin.
- L332 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreateSphere(int subdivLevels)` — Creates a sphere by subdividing a diamond shape base shape and projecting the subdivision verices to the unit sphere.
- L354 _function_ `auto makeEdge = [](int vID0, int vID1)` (scope `CreateSphere`)
- L409 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreateGrid(const T extentX, const T extentY, const int subdivX, const int subdivY)` — Creates a grid with a given size and number of subdivisions
- L453 _function_ `template <class T> static const Mesh<T> ConstructMeshFromDepthStream(const Camera<T>& camera, const T* depthPtr, T distThresh)`
- L515 _function_ `template <class T> static const Mesh<T> ConstructMeshFromMeshStream(const int numTriangles, const int* trianglesPtr, const int numVertices, const T* verticesPtr)`
- L564 _function_ `template <class T> static const Eigen::VectorX<T> CalculateMaskBasedOnMeshTopology(const Mesh<T>& inputMesh, bool &bInvalidMeshTopology, T edgeRatioThreshold = T(10))`
- L623 _function_ `template <class T> static Eigen::VectorX<T> ComputeTemplateCoverageMask( const Mesh<T>& templateMesh, const Mesh<T>& scanMesh, const Eigen::VectorX<T>& scanQualityMask, T maxCoverageDistance)`
- L666 _function_ `template <class T> Eigen::VectorX<T> FitEllipse(const Eigen::Matrix2X<T>& points2d)`
- L695 _function_ `template <class T, int D> static Eigen::Matrix<T, D, -1> CombinePoints(const std::vector<Eigen::Matrix<T, D, -1>>& vertices)`
- L715 _function_ `template <class T, int D> static Eigen::Matrix<T, D, -1> CombineRows(const std::vector<Eigen::Matrix<T, D, -1>>& vertices)`
- L735 _function_ `template <class T> static Eigen::VectorX<T> CombinePoints(const std::vector<Eigen::VectorX<T>>& input)`
- L755 _function_ `template <class T> static std::pair<std::vector<int>, Mesh<T>> CombineMeshes(const std::vector<Mesh<T>>& meshes)`
- L782 _function_ `template <class T, int D = 3> static std::vector<Eigen::Matrix<T, D, -1>> SplitVertices(const Eigen::Matrix<T, D, -1>& combined, const std::vector<int>& offsets)`
- L795 _function_ `template <class T> static TITAN_NAMESPACE::Mesh<T> CreateTrapezoidalPrism(T start, T end, T startSize, T endSize)`
- L851 _function_ `template <class T> static std::vector<std::vector<int>> ExtractBoundaryLoops(const Mesh<T>& mesh)` — Extract ordered boundary loops from a mesh. Boundary edges belong to exactly one triangle. Each loop is a closed sequence of vertex indices ordered along the boundary.
- L928 _function_ `template <class T> static std::vector<std::pair<int, int>> FindAlignedBoundaryLoops( const Mesh<T>& meshA, const Mesh<T>& meshB, T tolerance = T(0.01), bool allowDiffCount = false)` — Find pairs of boundary loops from two meshes that are spatially aligned. Returns pairs of (loopIndexA, loopIndexB). @param tolerance      Maximum per-vertex distance to consider aligned (default 0.01) @param allowDiffCount If false (default), only match loops with identical vertex counts
- L986 _function_ `template <class T> static Mesh<T> MergeMeshesAlongBoundary( const Mesh<T>& meshA, const Mesh<T>& meshB, const std::vector<int>& loopA, const std::vector<int>& loopB)` — Merge two meshes along aligned boundary loops by welding matching vertices. loopA and loopB are ordered vertex index sequences from meshA and meshB respectively. Matched boundary vertices from meshB are remapped to use meshA's vertices. @returns Combined mesh with welded boundary

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/HalfEdgeMesh.h` (Private)


#### struct `HalfEdgeMesh`  
`template <class T> struct HalfEdgeMesh`  
_L19-50_
- desc: Half edge mesh class representing meshes with polygonal faces
- L32 _public member_ `Eigen::Matrix<T, 3, -1> vertices;`
- L35 _public member_ `std::vector<HalfEdge> halfEdges;` — list of half edges
- L38 _public member_ `std::vector<int> vertexEdge;` — map from vertex id to one of the half-edges originating at that vertex
- L40 _public member_ `std::vector<int> faces;` — map from face index to one of the half-edges part of that face
- L43 _public prototype_ `HalfEdgeMesh() = default;`
- L44 _public prototype_ `HalfEdgeMesh(const HalfEdgeMesh& o) = default;`
- L45 _public prototype_ `HalfEdgeMesh& operator=(const HalfEdgeMesh& o) = default;`
- L47 _public prototype_ `HalfEdgeMesh(const Mesh<T>& m);`
- L49 _public prototype_ `std::vector<int> GetTopologicalSymmetry(const int referenceEdge) const;`

#### struct `HalfEdgeMesh::HalfEdge`  
`struct HalfEdge`  
_L22-30_
- desc: main half edge data structure
- L24 _public member_ `int v0;` — source vertex index for half-edge
- L25 _public member_ `int v1;` — target vertex index for half-edge
- L26 _public member_ `int next;` — next edge in loop
- L27 _public member_ `int prev;` — previous edge in loop
- L28 _public member_ `int dual;` — dual edge in neighboring face, might be -1 if edge
- L29 _public member_ `int face;` — face index for halfedge

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/ImageHelpers.h` (Private)


#### Free symbols / members of external scopes

- L8 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> T srgb2linear(T srgb)`
- L25 _function_ `template <class T> T linear2srgb(T linear)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/ImageView.h` (Private)


#### enum `PixelDepth`  
`enum class PixelDepth`  
_L10-15_
- L12 _public enumerator_ `UINT8`
- L13 _public enumerator_ `UINT16`
- L14 _public enumerator_ `FLOAT`

#### class `ImageView`  
`class ImageView`  
_L28-53_
- L31 _public function_ `ImageView(void* imageData, int width, int height, PixelFormat pixelFormat, PixelDepth pixelDepth) : m_imageData(imageData) , m_width(width) , m_height(height) , m_pixelFormat(pixelFormat) , m_pixelDepth(pixelDepth)`
- L39 _public function_ `void* Data()`
- L40 _public function_ `const void* Data() const`
- L41 _public function_ `int Width() const`
- L42 _public function_ `int Height() const`
- L43 _public function_ `PixelFormat GetPixelFormat() const`
- L44 _public function_ `PixelDepth GetPixelDepth() const`
- L45 _public function_ `int GetSizeInBytes() const`
- L48 _private member_ `void* m_imageData;`
- L49 _private member_ `int m_width;`
- L50 _private member_ `int m_height;`
- L51 _private member_ `PixelFormat m_pixelFormat;`
- L52 _private member_ `PixelDepth m_pixelDepth;`

#### class `ConstImageView`  
`class ConstImageView`  
_L55-87_
- L58 _public function_ `ConstImageView(const void* imageData, int width, int height, PixelFormat pixelFormat, PixelDepth pixelDepth) : m_imageData(imageData) , m_width(width) , m_height(height) , m_pixelFormat(pixelFormat) , m_pixelDepth(pixelDepth)`
- L66 _public function_ `ConstImageView(const ImageView& other) : m_imageData(other.Data()) , m_width(other.Width()) , m_height(other.Height()) , m_pixelFormat(other.GetPixelFormat()) , m_pixelDepth(other.GetPixelDepth())`
- L74 _public function_ `const void* Data() const`
- L75 _public function_ `int Width() const`
- L76 _public function_ `int Height() const`
- L77 _public function_ `PixelFormat GetPixelFormat() const`
- L78 _public function_ `PixelDepth GetPixelDepth() const`
- L79 _public function_ `int GetSizeInBytes() const`
- L82 _private member_ `const void* m_imageData;`
- L83 _private member_ `int m_width;`
- L84 _private member_ `int m_height;`
- L85 _private member_ `PixelFormat m_pixelFormat;`
- L86 _private member_ `PixelDepth m_pixelDepth;`

#### Free symbols / members of external scopes

- L17 _function_ `inline int BytesForPixelDepth(PixelDepth pixelDepth)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/IncrementalPCA.h` (Private)


#### enum `DataOrder`  
`enum class DataOrder`  
_L20-24_
- L22 _public enumerator_ `RowsAreExamples`
- L23 _public enumerator_ `ColsAreExamples`

#### class `IncrementalPCA`  
`template <typename T> class IncrementalPCA`  
_L34-391_
- desc: @brief Class for training a PCA model incrementally (after an initial training batch) @details Uses the method of Ross et al in: "Incremental Learning for Robust Visual Tracking" https://www.cs.toronto.edu/~dross/ivt/RossLimLinYang_ijcv.pdf @tparam T must be a floating point type such as float, double, etc.
- L63 _public function_ `void AddTrainingData(const Eigen::Matrix<T, -1, -1>& dataMatrix, T forgetFactor, int maxModes, T maxVariance, DataOrder order)` — @brief Add a set of training examples to the model @details If this block is the first set of examples a normal PCA is computed, otherwise the existing model is updated. In the second case, the data must have the same number of dimensions as the original data used to train the model. @param dataMatrix A matrix of training data, where each row or column is a training example according to the order flag @param forgetFactor Typically set to 1.0 this controls how much weight to give to the existing model versus the new data. A forgot factor of 0.0 gives all the weight to the new data essentially completely forgetting all the previous training. @param maxModes The maximum number of modes to retain in the model. @param maxVariance The maximum variance to retain. @param order Flag to specify whether the data is column-wise or row-wise @pre dataMatrix.cols() > 0 @pre dataMatrix.rows() > 0 @pre 0<= forgetFactor <= 1 @pre if IsTrained() then (order==DataOrder::ColsAreExamples && dataMatrix.rows()==NumVariables()) || (order==DataOrder::RowsreExamples && dataMatrix.cols()==NumVariables())
- L86 _public function_ `bool IsTrained()` — @brief Check if the model is trained
- L92 _public function_ `void Reset()` — @brief Reset the model so that the next set of data passed to it is treated as the first set of data.
- L108 _public function_ `Eigen::Matrix<T, -1, -1> Parameterize(const Eigen::Matrix<T, -1, -1>& dataMatrix, DataOrder order)` — @brief Given a set of data examples, return their parameterizations @param dataMatrix A matrix of training data, where each row or column is a training example according to the order flag @param order Flag to specify whether the data is column-wise or row-wise @return A matrix of parameters where each column corresponds to each column of the input data. @pre (IsTrained() && (order==DataOrder::ColsAreExamples && dataMatrix.rows()==NumVariables()) || (order==DataOrder::RowsAreExamples && dataMatrix.cols()==NumVariables()))
- L135 _public function_ `Eigen::Matrix<T, -1, -1> Reconstruct(const Eigen::Matrix<T, -1, -1>& parameterMatrix, DataOrder order)` — @brief Given a set of parameterizations, return their reconstructions @param parameterMatrix A matrix of parameters, where each row or column is an example according to the order flag. @param order Flag to specify whether the data is column-wise or row-wise @return A matrix of reconstructions where each column corresponds to each column of the input data. @pre (IsTrained() && (order==DataOrder::ColsAreExamples && parameterMatrix.rows()==NumParams()) || (order==DataOrder::RowsAreExamples && parameterMatrix.cols()==NumParams()))
- L163 _public function_ `Eigen::Matrix<T, -1, -1> BestFit(const Eigen::Matrix<T, -1, -1>& dataMatrix, DataOrder order)` — @brief Given a set of data, parameterize, the reconstruct their approximations @param dataMatrix A matrix of training data, where each row or column is a training example according to the order flag @param order Flag to specify whether the data is column-wise or row-wise @return A matrix of reconstructions where each column corresponds to each column of the input data. @pre (IsTrained() && (order==DataOrder::ColsAreExamples && dataMatrix.rows()==NumVariables()) || (order==DataOrder::RowsAreExamples && dataMatrix.cols()==NumVariables()))
- L176 _public function_ `int NumModes()` — @brief Return the number of modes in the model. @return The number of modes.
- L182 _public function_ `int NumVariables()` — @brief Return the number of variables in the data the model encodes. @return The number of variables.
- L188 _public function_ `const Eigen::Vector<T, -1>& StandardDeviations()` — @brief Return a vector giving the standard deviations of the modes. @return Vector of standard deviations.
- L194 _public function_ `const Eigen::Matrix<T, -1, -1>& U()` — @brief Return the matrix of modes. @return The modes.
- L200 _public function_ `const Eigen::VectorX<T>& Mean()` — @brief Return the mean. @return The mean.
- L203 _private member_ `bool m_isTrained = false;`
- L204 _private member_ `Eigen::VectorX<T> m_mean;`
- L205 _private member_ `Eigen::Matrix<T, -1, -1> m_U;`
- L206 _private member_ `Eigen::Vector<T, -1> m_singularValues;`
- L207 _private member_ `Eigen::Vector<T, -1> m_stds;`
- L208 _private member_ `T m_n = 0.f;`
- L211 _private function_ `void Train(const Eigen::Matrix<T, -1, -1>& dataMatrix, int maxModes, T maxVariance, DataOrder order)`
- L280 _private function_ `void Update(const Eigen::Matrix<T, -1, -1>& dataMatrix, T forgetFactor, int maxModes, T maxVariance, DataOrder order)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/Interpolation.h` (Private)


#### enum `InterpolationMethod`  
`enum class InterpolationMethod`  
_L12-17_
- L14 _public enumerator_ `NEAREST`
- L15 _public enumerator_ `LINEAR`
- L16 _public enumerator_ `CUBIC`

#### Free symbols / members of external scopes

- L21 _function_ `template <typename TYPE> inline TYPE nearestInterpolate(const TYPE* texture, float x, float y, int maxX, int maxY)` — nearest texture interpolation
- L32 _function_ `template <typename TYPE> inline TYPE bilinearInterpolate(const TYPE* texture, float x, float y, int maxX, int maxY)` — bilinear texture interpolation
- L52 _function_ `template <typename TYPE> inline TYPE cubicValue(float t, TYPE fm, TYPE f0, TYPE f1, TYPE f2)` — cubic interpolation based on implementation in OpenCV
- L64 _function_ `template <typename TYPE> inline TYPE cubicInterpolate(const TYPE* texture, float x, float y, int maxX, int maxY)` — cubic texture interpolation

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/Jacobians.h` (Private)


#### Free symbols / members of external scopes

- L8 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int R, int K, int C> SparseMatrix<T> JacobianOfPremultipliedMatrix(const Eigen::Matrix<T, R, K>& M)`
- L40 _function_ `template <class T, int R, int K, int C> Eigen::Matrix<T, R* C, K* C, Eigen::RowMajor> JacobianOfPremultipliedMatrixDense(const Eigen::Matrix<T, R, K>& M)`
- L65 _function_ `template <class T, int R, int K, int C> SparseMatrix<T> JacobianOfPostmultipliedMatrix(const Eigen::Matrix<T, K, C>& M)` — Calculates the Jacobian of the product A = X M A: R x C X: R x K M: K x C @returns dA/dX
- L108 _function_ `template <class T> SparseMatrix<T> JacobianOfCrossProductMatrix(const T SCALE = T(1.0))` — Calculates the Jacobian of the cross product matrix L with an optional scaling: SL = s * |  0  -z   y  | |  z   0  -x  | | -y   x   0  | and X = [x y z]^T @returns dSL/dX dSL/dx = | 0  0  0 | | 0  0 -s | | 0  s  0 | dSL/dy = | 0  0  s | | 0  0  0 | |-s  0  0 | dSL/dz = | 0 -s  0 | | s  0  0 | | 0  0  0 |
- L206 _function_ `template <class T, int C> SparseMatrix<T> JacobianOfCrossProductMatrixPostMultipliedByMatrix(Eigen::Map<const Eigen::Matrix<T, 3, C>> M, const T SCALE = T(1.0))` — Calculates the Jacobian of the product A = L M with L being the cross product matrix and optional scaling: L = |  0  -z   y  | |  z   0  -x  | | -y   x   0  | and X = [x y z]^T @returns dA/dX dL/dx = | 0  0  0 | | 0  0 -1 | | 0  1  0 | dL/dy = | 0  0  1 | | 0  0  0 | |-1  0  0 | dL/dz = | 0 -1  0 | | 1  0  0 | | 0  0  0 | M =  | row(0) | | row(1) | | row(2) | dA/dx =  |  0		| | -2 row(2)	| |  2 row(1)	| dA/dy =  |  2 row(2) | |  0        | | -2 row(0) | dA/dz =  | -2 row(1) | |  2 row(0) | |  0        |
- L296 _function_ `template <class T, int R> SparseMatrix<T> JacobianOfCrossProductMatrixPreMultipliedByMatrix(Eigen::Map<const Eigen::Matrix<T, R, 3>> M, const T SCALE = T(1.0))` — Calculates the Jacobian of the product A = M L with L being the cross product matrix and optional scaling: L = |  0  -z   y  | |  z   0  -x  | | -y   x   0  | and X = [x y z]^T @returns dA/dX dL/dx = | 0  0  0 | | 0  0 -1 | | 0  1  0 | dL/dy = | 0  0  1 | | 0  0  0 | |-1  0  0 | dL/dz = | 0 -1  0 | | 1  0  0 | | 0  0  0 | M =          |    col(0)     col(1)      col(2) | dA/dx =  |  0          2 col(2)   -2 col(1) | dA/dy =  | -2 col(2)   0           2 col(0) | dA/dz =  |  2 col(1)  -2col(0)     0        |

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/LodGeneration.h` (Private)


#### class `LodGenerationConfiguration`  
`template <class T> class LodGenerationConfiguration`  
_L26-62_
- desc: Representation of a configuration representing how Lod Generation is performed
- L45 _public prototype_ `LodGenerationConfiguration() = default;`
- L48 _public prototype_ `bool Load(const std::string& filenameOrData);` — Load data from either file or the data directly.
- L50 _public function_ `const std::map<std::string, LodGenerationData>& RigPartLodGenerationData() const`
- L58 _private prototype_ `bool LoadJson(const std::string& jsonString, const std::string& baseDir, bool isFileBased);`
- L61 _private member_ `std::map<std::string, LodGenerationData> m_rigPartLodGenerationData;` — a map of part name to lod generation data for each rig part

#### struct `LodGenerationConfiguration::LodData`  
`struct LodData`  
_L29-36_
- L31 _public member_ `std::string meshName;`
- L32 _public member_ `std::string driverMesh;`
- L33 _public member_ `std::shared_ptr<const Mesh<T>> mesh;`
- L34 _public member_ `SnapConfig<T> snapConfig;`
- L35 _public prototype_ `bool ReadJson(const JsonElement& element, const std::string& baseDir, bool isFileBased = true);`

#### struct `LodGenerationConfiguration::LodGenerationData`  
`struct LodGenerationData`  
_L38-43_
- L40 _public member_ `std::vector<LodData> lodData;`
- L41 _public member_ `WrapDeformerParams<T> params;`
- L42 _public prototype_ `bool ReadJson(const JsonElement& element, const std::string& baseDir, bool isFileBased = true);`

#### class `LodGeneration`  
`template <class T> class LodGeneration`  
_L68-105_
- desc: Representation of a class for performing Lod generation using wrap deformers
- L71 _public prototype_ `LodGeneration();`
- L74 _public prototype_ `void SetThreadPool(const std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool>& taskThreadPool);` — Set a threadpool for parallelization of lod generation tasks (if not set, the default global threadpool will be used)
- L77 _public prototype_ `bool Init(const LodGenerationConfiguration<T>& config);` — initialize the lod generation object from a config
- L80 _public prototype_ `bool Apply(std::map<std::string, Eigen::Matrix<T, 3, -1>>& lod0MeshVertices, std::map<std::string, Eigen::Matrix<T, 3, -1>>& higherLodMeshVertices, bool bAllowMissingMeshes = false) const;` — apply lod generation to a map of mesh name to vertices, once the object has been initialized, and return the results for the higher lods as a map of mesh name to vertices
- L83 _public prototype_ `void GetDriverMeshClosestPointBarycentricCoordinates(std::map<std::string, std::vector<BarycentricCoordinates<T>>>& driverMeshClosestPointBarycentricCoordinates) const;` — once the object has been initialized, for each higher lod mesh, get the barycentric coordinates for the closest vertices on the driver mesh, returning the results as a map of mesh names to vector of barycemtric coordinates
- L86 _public prototype_ `bool LoadModelBinary(const std::string& lodGenerationModelFile);` — load from a binary lod generation model filename
- L89 _public prototype_ `bool SaveModelBinary(const std::string& lodGenerationModelFile) const;` — save to a binary lod generation model filename
- L91 _public function_ `const std::vector<std::string>& Lod0MeshNames() const`
- L92 _public prototype_ `std::vector<std::string> HigherLodMeshNames() const;`
- L93 _public prototype_ `int LodForMesh(const std::string& meshName) const;`
- L96 _private member_ `static constexpr int32_t m_version = 2;`
- L97 _private member_ `std::vector<std::string> m_baseMeshes;`
- L98 _private member_ `std::map<std::string, std::string> m_driverMeshNames;`
- L99 _private member_ `std::map<std::string, WrapDeformer<T>> m_wrapDeformers;`
- L100 _private member_ `std::map<std::string, SnapConfig<T>> m_snapConfigs;`
- L101 _private member_ `std::map<std::string, int> m_meshLods;`
- L102 _private member_ `std::map<std::string, std::shared_ptr<const Mesh<T>>> m_allMeshes;`
- L104 _private member_ `std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool> m_taskThreadPool;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/Mesh.h` (Private)


#### enum `VertexNormalComputationType`  
`enum class VertexNormalComputationType`  
_L36-41_
- L38 _public enumerator_ `AreaWeighted`
- L39 _public enumerator_ `VoronoiAreaWeighted`
- L40 _public enumerator_ `AngleWeighted`

#### class `Mesh`  
`template <class T> class Mesh`  
_L52-243_
- desc: Mesh class representing quad and triangle meshes. Important note: Texture coordinates are stored with the origin being at the top left corner. Any import/export of meshes, e.g. when writing OBJs, needs to take this into account and flip the y coordinate accordingly. The reason to store texture coordinates with the top left corner is so that this is consistent with image, windows, and normalized coordinates (Vulkan).
- L55 _public prototype_ `Mesh() = default;`
- L56 _public prototype_ `Mesh(const Mesh& o) = default;`
- L57 _public prototype_ `Mesh& operator=(const Mesh& o) = default;`
- L59 _public function_ `int NumVertices() const`
- L60 _public function_ `int NumTriangles() const`
- L61 _public function_ `int NumQuads() const`
- L63 _public function_ `const Eigen::Matrix<T, 3, -1>& Vertices() const`
- L65 _public function_ `void SetVertices(Eigen::Matrix<T, 3, -1>&& vertices)` — Sets the vertices and clears the normals
- L66 _public function_ `void SetVertices(const Eigen::Matrix<T, 3, -1>& vertices)`
- L68 _public function_ `const Eigen::Matrix<int, 3, -1>& Triangles() const`
- L70 _public function_ `void SetTriangles(Eigen::Matrix<int, 3, -1>&& tris)` — Sets the triangles and clears the normals
- L71 _public function_ `void SetTriangles(const Eigen::Matrix<int, 3, -1>& tris)`
- L73 _public function_ `const Eigen::Matrix<int, 4, -1>& Quads() const`
- L75 _public function_ `void SetQuads(Eigen::Matrix<int, 4, -1>&& quads)` — Sets the quads and clears the normals
- L76 _public function_ `void SetQuads(const Eigen::Matrix<int, 4, -1>& quads)`
- L84 _public prototype_ `void SetTopology(const Eigen::VectorXi& topology, const Eigen::VectorXi& vIDs);` — Set the topology using the polygon format (as used in Maya). @pre There should not be any prior tris and quads assigned to the mesh. @param polygons      The number of vertices per polygons (only 3 for tris and 4 for quads are supported) @param vIDs          The vertex IDs for the \p polygons (concatenated)
- L90 _public prototype_ `bool Validate(bool checkVertexUsage) const;` — Validates that all indices are correct (in bound) @checkVertexUsage  Checks whether all vertices are being used
- L100 _public prototype_ `std::vector<std::pair<int, bool>> Triangulate(TriangulationMethod triangulationMethod = TriangulationMethod::Quality, TaskThreadPool* taskThreadPool = nullptr);`
- L103 _public prototype_ `Eigen::Vector<T, -1> TriangleAreas() const;` — Calculates the triangle areas. (only works for pure triangle meshes)
- L109 _public prototype_ `Eigen::Vector<T, -1> VertexAreas() const;` — Calculates the vertex areas (only works for pure triangle meshes) using the mixed area term as described in Fig. 4 Meyer et al, "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds")
- L116 _public prototype_ `Eigen::Matrix<T, 3, -1> VertexMeanCurvatureNormals() const;` — Calculates the vertex mean curvature normal based on Meyer et al, "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds"). The mean curvature value is half the magnitude.
- L119 _public function_ `bool HasVertexNormals() const` — @returns True if the mesh has vertex normals
- L122 _public function_ `void ClearVertexNormals()` — Clears the current normals
- L129 _public prototype_ `const Eigen::Matrix<T, 3, -1>& CalculateVertexNormals(bool recompute = false, VertexNormalComputationType vertexNormalComputationType = VertexNormalComputationType::VoronoiAreaWeighted, bool stableNormalize = true, TaskThreadPool* taskThreadPool = nullptr);` — Calculates the vertex normals weighted by the mixed area term as described in Fig. 4 Meyer et al, "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds") @param recompute  If false then the normals are only calculated if they are not already there, if True then calculation is forced
- L139 _public prototype_ `void CalculateVertexNormals(const Eigen::Matrix<T, 3, -1>& vertices, Eigen::Matrix<T, 3, -1>& normals, VertexNormalComputationType vertexNormalComputationType, bool stableNormalize, TaskThreadPool* taskThreadPool = nullptr) const;` — Calculates the vertex normals using the topology of this mesh and the vertices of @p vertices. Stores the result in @p normals. @param[in] accurate  If True, it uses the mixed area term (see above), otherwise it uses a faster version by weighing using the triangle area.
- L150 _public prototype_ `void CalculateVertexNormalsRef(Eigen::Ref<const Eigen::Matrix<T, 3, -1>> vertices, Eigen::Ref<Eigen::Matrix<T, 3, -1>> normals, VertexNormalComputationType vertexNormalComputationType, bool stableNormalize, TaskThreadPool* taskThreadPool = nullptr) const;` — Calculates the vertex normals using the topology of this mesh and the vertices of @p vertices. Stores the result in @p normals. @param[in] accurate  If True, it uses the mixed area term (see above), otherwise it uses a faster version by weighing using the triangle area.
- L157 _public function_ `const Eigen::Matrix<T, 3, -1>& VertexNormals() const` — @returns the vertex normals
- L160 _public function_ `void SetVertexNormals(Eigen::Matrix<T, 3, -1>&& vertexNormals)` — Sets the vertex normals.
- L161 _public function_ `void SetVertexNormals(const Eigen::Matrix<T, 3, -1>& vertexNormals)`
- L164 _public prototype_ `std::vector<int> CalculateBorderVertices() const;` — @returns the border vertices of the mesh
- L167 _public function_ `bool HasTexcoords() const` — @returns True if the mesh has UV coordinates
- L169 _public function_ `int NumTexcoords() const`
- L170 _public function_ `int NumTexTriangles() const`
- L171 _public function_ `int NumTexQuads() const`
- L174 _public function_ `void SetTexcoords(Eigen::Matrix<T, 2, -1>&& texcoords)` — Sets the texture coordinates. Note that the origin of texture coordinates is at the top left corner (as opposed to how it is stored in OBJs)
- L175 _public function_ `void SetTexcoords(const Eigen::Matrix<T, 2, -1>& texcoords)`
- L177 _public function_ `const Eigen::Matrix<T, 2, -1>& Texcoords() const` — @returns the texture coordinates. Note that the origin of texture coordinates is at the top left corner (as opposed to how it is stored in OBJs)
- L179 _public function_ `const Eigen::Matrix<int, 3, -1>& TexTriangles() const`
- L180 _public function_ `void SetTexTriangles(Eigen::Matrix<int, 3, -1>&& tris)`
- L181 _public function_ `void SetTexTriangles(const Eigen::Matrix<int, 3, -1>& tris)`
- L183 _public function_ `const Eigen::Matrix<int, 4, -1>& TexQuads() const`
- L184 _public function_ `void SetTexQuads(Eigen::Matrix<int, 4, -1>&& quads)`
- L185 _public function_ `void SetTexQuads(const Eigen::Matrix<int, 4, -1>& quads)`
- L188 _public prototype_ `std::vector<std::pair<int, int>> GetEdges(const std::vector<int>& vIDs) const;` — @returns all the edges of the mesh. If vIDs.size() > 0 then only edges which are part of vIDs are returned.
- L191 _public function_ `template <class S> Mesh<S> Cast() const`
- L209 _public prototype_ `void Resample(const std::vector<int>& newToOldMap);` — @brief Resample the mesh such that new vertex i will correspond to previous vertex newToOldMap[i]. In the current implementation texture coordinates and texture faces are discarded. @pre newToOldMap Each new vertex needs to point to an existing vertex, and it needs to be unique.
- L212 _public prototype_ `Eigen::Matrix<T, 3, -1> CalculateTriangleNormals() const;` — Calculate and return the triangle normals
- L215 _public prototype_ `void Mask(const Eigen::VectorX<T>& mask);` — Remove all triangles and quads where any vertex is mask[vID] = 0.
- L218 _public prototype_ `void Mask(const std::vector<int>& vIDs);` — Keep only triangles and quads that contain vIDs
- L230 _private member_ `static constexpr int32_t m_version = 1;`
- L232 _private member_ `Eigen::Matrix<T, 3, -1> m_vertices;`
- L233 _private member_ `Eigen::Matrix<int, 3, -1> m_tris;`
- L234 _private member_ `Eigen::Matrix<int, 4, -1> m_quads;`
- L237 _private member_ `Eigen::Matrix<T, 3, -1> m_normals;` — the normals of the mesh (one normal per vertex)
- L240 _private member_ `Eigen::Matrix<T, 2, -1> m_texcoords;` — UVs of the mesh (may be more than one normal per vertex)
- L241 _private member_ `Eigen::Matrix<int, 3, -1> m_tex_tris;`
- L242 _private member_ `Eigen::Matrix<int, 4, -1> m_tex_quads;`

#### enum `Mesh::TriangulationMethod`  
`enum class TriangulationMethod`  
_L96-99_
- desc: Triangulates the Mesh. Quads will be empty afterwards. @returns for each triangle, the index of the quad (bool = true) from which it was triangulated or the triangle id (bool = false)
- L97 _public enumerator_ `Simple`
- L98 _public enumerator_ `Quality`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace trio`
- L20 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::io) template <typename T> bool ToBinaryFile(FILE* pFile, const Mesh<T>& mesh);`
- L26 _prototype_ `template <typename T> bool FromBinaryFile(FILE* pFile, Mesh<T>& mesh);`
- L29 _prototype_ `template <class U> bool FromBinaryFile(trio::BoundedIOStream* stream, Mesh<U>& mesh);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/MeshCorrespondenceSearch.h` (Private)


#### class `MeshCorrespondenceSearch`  
`template <class T> class MeshCorrespondenceSearch`  
_L14-59_
- L26 _public prototype_ `MeshCorrespondenceSearch();`
- L27 _public prototype_ `~MeshCorrespondenceSearch();`
- L28 _public prototype_ `MeshCorrespondenceSearch(MeshCorrespondenceSearch&& o);`
- L29 _public prototype_ `MeshCorrespondenceSearch(const MeshCorrespondenceSearch& o) = delete;`
- L30 _public prototype_ `MeshCorrespondenceSearch& operator=(MeshCorrespondenceSearch&& o);`
- L31 _public prototype_ `MeshCorrespondenceSearch& operator=(const MeshCorrespondenceSearch& o) = delete;`
- L33 _public prototype_ `void Init(const Mesh<T>& targetMesh);`
- L36 _public prototype_ `const Eigen::Vector<T, -1>& TargetWeights() const;` — @returns the target vertex weights, by default border vertices are zero, all others are one.
- L42 _public prototype_ `void SetTargetWeights(const Eigen::Vector<T, -1>& targetWeights);` — Set custom target vertex weights. @pre @p targetWeights need to have the size of the number of vertices of the target mesh
- L44 _public prototype_ `void Search(const Mesh<T>& srcMesh, Result& result, const Eigen::VectorX<T>* weights = nullptr, T normalIncompatibilityThreshold = T(0.5)) const;`
- L45 _public prototype_ `void Search(const Eigen::Matrix<T, 3, -1>& srcVertices, const Eigen::Matrix<T, 3, -1>& srcNormals, Result& result, const Eigen::VectorX<T>* weights = nullptr, T normalIncompatibilityThreshold = T(0.5)) const;`
- L54 _public prototype_ `BarycentricCoordinates<T, 3> Search(const Eigen::Vector3<T>& pt) const;` — Search for the closest point on the target mesh and return them as barycentric coordinates.
- L58 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### struct `MeshCorrespondenceSearch::Result`  
`struct Result`  
_L17-23_
- L19 _public member_ `Eigen::VectorXi srcIndices;`
- L20 _public member_ `Eigen::Matrix<T, 3, -1> targetVertices;`
- L21 _public member_ `Eigen::Matrix<T, 3, -1> targetNormals;`
- L22 _public member_ `Eigen::Vector<T, -1> weights;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/MeshSmoothing.h` (Private)


#### class `MeshSmoothing`  
`template <typename T> class MeshSmoothing`  
_L12-23_
- L15 _public prototype_ `void SetTopology(const Mesh<T>& mesh, T identityWeight = T(0.44), T step = T(0.5));`
- L16 _public function_ `void SetWeights(const Eigen::VectorX<T>& weights)`
- L18 _public prototype_ `void Apply(Eigen::Matrix<T, 3, -1>& vertices, int iterations);`
- L21 _private member_ `Eigen::SparseMatrix<T, Eigen::RowMajor> m_smoothingMatrix;`
- L22 _private member_ `Eigen::VectorX<T> m_weights;`
- L26 _function_ `template <typename T> void MeshSmoothing<T>::SetTopology(const Mesh<T>& mesh, T identityWeight, T step)`
- L56 _function_ `template <typename T> void MeshSmoothing<T>::Apply(Eigen::Matrix<T, 3, -1>& vertices, int iterations)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/MeshTools.h` (Private)


#### struct `FaceCoord`  
`struct FaceCoord`  
_L130-196_
- L138 _public member_ `std::vector<int> indices;`
- L139 _public member_ `std::vector<float> weights;`
- L140 _public member_ `bool fixed{};`
- L142 _public prototype_ `FaceCoord() = default;`
- L143 _public function_ `FaceCoord(int vID) : indices(1, vID), weights(1, 1.0f), fixed(false)`
- L145 _public function_ `bool operator!=(const FaceCoord& other) const`
- L152 _public function_ `bool operator==(const FaceCoord& other) const`
- L157 _public function_ `bool IsSamePosition(const FaceCoord& other) const`
- L163 _public function_ `bool IsValid() const`
- L164 _public function_ `bool IsVertex() const`
- L165 _public function_ `bool IsEdge() const`
- L166 _public function_ `bool IsTriangle() const`
- L167 _public function_ `bool IsQuad() const`
- L169 _public function_ `Eigen::Vector3f Evaluate(const Eigen::Matrix<float, 3, -1>& vertices) const`
- L180 _public function_ `int ClosestVertex(const Eigen::Matrix<float, 3, -1>& vertices) const`

#### enum `FaceCoord::Type`  
`enum class Type`  
_L132-136_
- L133 _public enumerator_ `Vertex`
- L134 _public enumerator_ `Edge`
- L135 _public enumerator_ `Face`

#### struct `ContourCorrespondence`  
`struct ContourCorrespondence`  
_L201-207_
- desc: Correspondence to a contour, where it is assumed a contour is a vector of FaceCoord
- L202 _public member_ `int segment{-1};`
- L203 _public member_ `float t{};`
- L204 _public member_ `float geodesicDistance{};`
- L205 _public member_ `float euclideanDistance{};`
- L206 _public function_ `bool IsValid() const`

#### class `MeshTools`  
`class MeshTools`  
_L210-274_
- L221 _public prototype_ `MeshTools();`
- L222 _public prototype_ `~MeshTools();`
- L225 _public prototype_ `std::pair<int, FaceCoord> Select(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const Eigen::Vector3f& query, FaceCoord::Type type, float threshold = 1e-1f);` — Get the mesh selection (vertex, edge, face) based on a query point @p query
- L232 _public prototype_ `std::vector<FaceCoord> ShortestPath(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, FaceCoord startCoord, FaceCoord endCoord);` — Calculate the shortest path between @p startVertexID and @p endVertexID
- L235 _public prototype_ `std::vector<std::pair<float, int>> GeodesicDistance(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const FaceCoord& rootCoord, float radius);` — Calculate the approximate geodesic distance for all mesh vertices from @p rootCoord up to @p radius
- L238 _public prototype_ `std::vector<std::pair<float, int>> EuclideanDistance(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const Eigen::Vector3f& query, float radius);` — Calculate the approximate euclidean distance for all mesh vertices from @p rootCoord up to @p radius
- L241 _public prototype_ `FaceCoord ClosestFaceCoord(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const Eigen::Vector3f& query, const FaceCoord& initCoord, std::vector<FaceCoord>* path = nullptr);` — Find closest facecoord on the mesh to a target position using a walk over the mesh faces
- L244 _public prototype_ `std::vector<float> CalculateLineLength(const std::shared_ptr<const Mesh<float>>& mesh, const std::vector<FaceCoord>& coords) const;` — Calculate the length of the line
- L247 _public prototype_ `std::vector<ContourCorrespondence> CalculateClosestCorrespondences(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const std::vector<FaceCoord>& coords, float maxRadius);` — calculate for every vertex of @p mesh the closest correspondence to the contour defined by @p coords
- L250 _public prototype_ `Contour RefineContour(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const Contour& contour, const ContourRefinementOptions& options);` — Refine contour
- L253 _public prototype_ `std::vector<int> TopologicalSymmetry(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh, const FaceCoord& coord);` — Get topologyical symmetry based on a selected edge
- L256 _private prototype_ `void Prepare(const std::shared_ptr<const Mesh<float>>& topology, const std::shared_ptr<const Mesh<float>>& mesh);`
- L257 _private prototype_ `void PrepareHalfEdgeTopology();`
- L258 _private prototype_ `void PrepareKdTree();`
- L259 _private prototype_ `void PrepareAabbTree();`
- L260 _private prototype_ `void PrepareEdgesMap(bool withDiagonals);`
- L263 _private member_ `std::shared_ptr<const Mesh<float>> m_topology;`
- L264 _private member_ `std::shared_ptr<const Mesh<float>> m_triTopology;`
- L265 _private member_ `std::shared_ptr<const HalfEdgeMesh<float>> m_halfEdgeTopology;`
- L266 _private member_ `std::vector<std::pair<int, bool>> m_triToQuadMapping;`
- L267 _private member_ `std::shared_ptr<const Mesh<float>> m_mesh;`
- L268 _private member_ `std::shared_ptr<AABBTree<float>> m_aabbTree;`
- L269 _private member_ `std::shared_ptr<KdTree<float>> m_kdTree;`
- L270 _private member_ `bool m_requiresEdgesMapNoDiagonalsUpdate{};`
- L271 _private member_ `std::vector<std::vector<std::pair<int, float>>> m_edgesMapNoDiagonals;`
- L272 _private member_ `bool m_requiresEdgesMapIncludingDiagonalsUpdate{};`
- L273 _private member_ `std::vector<std::vector<std::pair<int, float>>> m_edgesMapIncludingDiagonals;`

#### struct `MeshTools::ContourRefinementOptions`  
`struct ContourRefinementOptions`  
_L213-218_
- L215 _public member_ `int segments = 5;`
- L216 _public member_ `bool edgesOnly = true;`
- L217 _public member_ `bool useSpline = true;`

#### Free symbols / members of external scopes

- L14 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L35 _function_ `template <class T, int C> Eigen::Vector<T, C> MeanValueCoordinates(const Eigen::Vector3f& query, const Eigen::Matrix<T, 3, C>& vertices)` — Calculates the mean value coordinates of point @p query in the polygon spanned by @p vertices
- L37 _function_ `auto safeTanHalf = [] (T cosAngle)` (scope `MeanValueCoordinates`)
- L80 _function_ `template <class T> std::vector<T> MeanValueCoordinates(const Eigen::Vector3f& query, const std::vector<int>& indices, const Eigen::Matrix<T, 3, -1>& vertices)` — Calculates the mean value coordinates of point @p query in the polygon spanned by @p indices and index @p vertices
- L198 _typedef_ `typedef std::vector<FaceCoord> Contour;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/MetaShapeCamera.h` (Private)


#### class `MetaShapeCamera`  
`template <class T> class MetaShapeCamera : public Camera<T>`  
_L36-144_
- inherits: `Camera<T>`
- desc: The camera model as used in Agisoft PhotoScan/MetaShape. @see (https://www.agisoft.com/pdf/metashape-pro_1_6_en.pdf, https://www.agisoft.com/pdf/metashape-pro_1_5_en.pdf) We use the more generic version of tangential distortion parameters as used in version 1.5. x = X/Z y = Y/Z r = sqrt(x^2 + y^2) x' = x (1 + K1 r^2 + K2 r^4 + K3 r^6 + K4 r^8) + (P1 (r^2 + 2x^2) + 2 P2 x y) (1 + P3 r^2 + P4 r^4) y' = y (1 + K1 r^2 + K2 r^4 + K3 r^6 + K4 r^8) + (P2 (r^2 + 2y^2) + 2 P1 x y) (1 + P3 r^2 + P4 r^4) px = width * 0.5 + cx + x' f + x' B1 + y' B2 py = height * 0.5 + cy + y' f Thereoretically B2 is the skew parameter "a" in the intrinsics, and B1 can be added to the focal length fx = f + B1 K =  |  fx a  cx' | |  0  fy cy' | |  0  0  1   | However, in Agisoft photoscan undistortion also removes B1 and B2, and therefore we do not map the skew parameters into the intrinsics either. Important note: the tangential distortion parameters are swapped relative to the opencv model. Also the OpenCV does not support the K4 parameter. https://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html
- L39 _public function_ `MetaShapeCamera() : Camera<T>() , m_radialDistortion(0, 0, 0, 0) , m_tangentialDistortion(0, 0, 0, 0) , m_skew(0, 0) , m_sensorID(-1) , m_cameraID(-1)`
- L47 _public prototype_ `virtual ~MetaShapeCamera() = default;`
- L49 _public function_ `const Eigen::Vector<T, 4>& RadialDistortion() const`
- L50 _public function_ `void SetRadialDistortion(const Eigen::Vector<T, 4>& radialDistortion)`
- L52 _public function_ `const Eigen::Vector<T, 4>& TangentialDistortion() const`
- L53 _public function_ `void SetTangentialDistortion(const Eigen::Vector<T, 4>& tangentialDistortion)`
- L55 _public function_ `const Eigen::Vector<T, 2>& Skew() const`
- L56 _public function_ `void SetSkew(const Eigen::Vector<T, 2>& skew)`
- L58 _public function_ `int SensorID() const`
- L59 _public function_ `void SetSensorID(int id)`
- L61 _public function_ `int CameraID() const`
- L62 _public function_ `void SetCameraID(int id)`
- L65 _public function_ `Eigen::Vector2<T> Distort(const Eigen::Vector2<T>& pix) const` — @return the location of the distorted pixel
- L93 _public function_ `Eigen::Vector2<T> Undistort(const Eigen::Vector2<T>& pix, T eps = T(1e-6), int maxIter = 100) const` — @return the location of the undistorted pixel
- L131 _private member_ `Eigen::Vector<T, 4> m_radialDistortion;` — The radial distortion parameters (K1, K2, K3, K4)
- L134 _private member_ `Eigen::Vector<T, 4> m_tangentialDistortion;` — The tangential distortion parameters (P1, P2, P3, P4)
- L137 _private member_ `Eigen::Vector<T, 2> m_skew;` — The skew parameters (B1, B2)
- L140 _private member_ `int m_sensorID;` — Sensor ID
- L143 _private member_ `int m_cameraID;` — Camera ID

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/MultiCameraSetup.h` (Private)


#### class `MultiCameraSetup`  
`template <class T> class MultiCameraSetup`  
_L16-126_
- desc: Class that contains a full camera setup including depth ranges.
- L19 _public prototype_ `MultiCameraSetup() = default;`
- L21 _public function_ `void Init(const std::vector<MetaShapeCamera<float>>& cameras)`
- L32 _public function_ `void SetCameraRanges(const std::map<std::string, std::pair<T, T>>& cameraRanges)`
- L40 _public function_ `void SetCameraRange(const std::string& cameraName, const std::pair<T, T>& cameraRange)`
- L49 _public function_ `const std::vector<std::string>& GetCameraNames() const`
- L54 _public function_ `std::vector<MetaShapeCamera<T>> GetCamerasAsVector() const`
- L64 _public function_ `bool HasCamera(const std::string& name) const`
- L66 _public function_ `const MetaShapeCamera<T>& GetCamera(const std::string& name) const`
- L79 _public function_ `const std::map<std::string, MetaShapeCamera<T>>& GetCameras() const`
- L81 _public function_ `bool HasCameraRange(const std::string& name) const`
- L83 _public function_ `const std::pair<T, T>& GetCameraRange(const std::string& name) const`
- L96 _public function_ `const std::map<std::string, std::pair<T, T>>& GetCameraRanges() const`
- L98 _public function_ `void ScaleCameras(T scale)`
- L118 _public function_ `T GetScale() const`
- L121 _private member_ `std::vector<std::string> m_cameraNames;`
- L122 _private member_ `std::map<std::string, MetaShapeCamera<T>> m_cameraMap;`
- L123 _private member_ `std::map<std::string, std::pair<T, T>> m_cameraRanges;`
- L125 _private member_ `T m_originalCamerasToCurrentCamerasScale = T(1);` — any scaling that was applied to the cameras after setting up the the camera setup

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/MultiCameraTriangulation.h` (Private)


#### class `MultiCameraTriangulation`  
`template <class T> class MultiCameraTriangulation`  
_L23-91_
- desc: Class to do mutli camera triangulation. Requires at least two points. Supports triangulation via DLT as well as the more accurate nonlinear variant (which should be initialized by the linear version)
- L26 _public function_ `void SetCameras(const std::vector<Camera<T>>& cameras)`
- L40 _public function_ `Eigen::Vector3<T> Triangulate(const std::vector<Eigen::Vector2<T>>& pixels) const`
- L60 _public function_ `Eigen::Vector3<T> TriangulateNonlinear(const Eigen::Vector3<T>& initial, const std::vector<Eigen::Vector2<T>>& pixels, const std::vector<T>& confidences) const`
- L89 _private member_ `std::vector<Camera<T>> m_cameras;`
- L90 _private member_ `std::vector<Eigen::Matrix<T, 3, 4>> m_Ps;`

#### Free symbols / members of external scopes

- L70 _function_ `std::function<DiffData<T>(Context<T>*)> evaluationFunction = [&](Context<T>* context)` (scope `MultiCameraTriangulation::TriangulateNonlinear`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/PCA.h` (Private)


#### struct `EigPCA`  
`template <class T, int MatOrder> struct EigPCA`  
_L121-186_
- L123 _public typedef_ `using scalar_t = T;`
- L125 _public member_ `Eigen::VectorX<T> mean;` — mean of pca
- L127 _public member_ `Eigen::Matrix<T, -1, -1, MatOrder> modes;` — modes of PCA as columns scaled by standard deviation of the mode
- L130 _public function_ `template <int MatOrderInput> void Create(const Eigen::Matrix<T, -1, -1, MatOrderInput>& dataMatrix, const DataOrder& dataOrder, const T varianceToKeep, const int maxModes = 0, bool verbose = false)`

#### struct `SvdPCA`  
`template <class T, int MatOrder> struct SvdPCA`  
_L190-227_
- L192 _public typedef_ `using scalar_t = T;`
- L194 _public member_ `Eigen::VectorX<T> mean;` — mean of pca
- L196 _public member_ `Eigen::Matrix<T, -1, -1, MatOrder> modes;` — modes of PCA as columns scaled by standard deviation of the mode
- L199 _public function_ `template <int MatOrderInput> void Create(const Eigen::Matrix<T, -1, -1, MatOrderInput>& dataMatrix, const DataOrder& dataOrder, const T varianceToKeep, const int maxModes = 0, bool verbose = false)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PCAHelper`
- L27 _function_ `template <class T> int NumberOfModes(const Eigen::VectorX<T>& stds, const T maxVariance, const int maxModes, bool verbose = false)` (scope `PCAHelper`) — @brief Calculates the number of modes to keep for a vector of standard deviations, either limited by the maximum variance or the maximum modes. @tparam T                float or double @param stds              The vector of standard deviations which are assumed to be ordered in decreasing order and >= 0. @param maxVariance      The maximum variance to keep. @param maxModes          The maximum number of modes to be kept. @param verbose           Whether to print verbose output of the variances. @return int              The number of modes.
- L71 _function_ `template <class T, int MatOrder> int NumSamples(const Eigen::Matrix<T, -1, -1, MatOrder>& dataMatrix, const DataOrder dataOrder)` (scope `PCAHelper`) — return the number of samples
- L85 _function_ `template <class T, int MatOrder> std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1, MatOrder>> MeanCenterData(const Eigen::Matrix<T, -1, -1, MatOrder>& dataMatrix, const DataOrder dataOrder)` (scope `PCAHelper`) — mean center the data
- L104 _function_ `template <class T, int MatOrder> void MakeModesDeterministic(Eigen::Matrix<T, -1, -1, MatOrder>& modes)` (scope `PCAHelper`) — flip modes to ensure deterministic output
- L235 _function_ `template <class T> Eigen::Matrix<T, -1, -1> CreatePCAWithMeanCenteredData(const Eigen::Matrix<T, -1, -1>& meanCenteredDataMatrix, const T varianceToKeep, const int maxModes = 0)` — @brief Calculates PCA on the mean centered data matrix @p meanCenteredDataMatrix and returns the modes that keep @p varianceToKeep of the variance. @p meanCenteredDataMatrix  Rows are the data samples, columns the dimensions of the data.
- L255 _function_ `template <class T> std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1>> CreatePCA(const Eigen::Matrix<T, -1, -1>& dataMatrix, const T varianceToKeep, const int maxModes = 0)` — @brief Calculates PCA on data matrix @p dataMatrix and returns the modes that keep @p varianceToKeep of the variance. @p dataMatrix  Rows are the data samples, columns the dimensions of the data.
- L273 _function_ `template <class T, int D> std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1>> PrepareRegionPCAData(const std::vector<Eigen::Matrix<T, D, -1>>& meshes, const std::vector<std::pair<int, T>>& vertexWeights, const bool premultiplyWeight)` — @brief Helper function for PCA calculation. Input data is vectorized and put as rows into the output matrix. Matrix is zero centered and premultiplied with weights, if stated so. @param[in] meshes - The meshes on which PCA is calculated. @param[in] vertexWeights - The vertices for which PCA is calculated together with a weight per vertex. @param[in] premultiplyWeight   Whether the data is weighted before calculating PCA or after calculating PCA for the region. @returns std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1>> where the vector is the mean, and matrix is the data
- L320 _function_ `template <class T, int D> Eigen::Matrix<T, -1, -1> PrepareRegionPCAData(const std::vector<Eigen::Matrix<T, D, -1>>& meshes, const Eigen::Matrix<T, D, -1>& mean, const std::vector<std::pair<int, T>>& vertexWeights, const bool premultiplyWeight)`
- L381 _function_ `template <class T, int D> std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1>> CreatePCA(const std::vector<Eigen::Matrix<T, D, -1>>& meshes, const std::vector<std::pair<int, T>>& vertexWeights, const T varianceToKeep, const bool premultiplyWeight, const int maxModes = 0)` — @brief Applies PCA for meshes @p meshes and the region as defined by @p vertexWeights. @param[in] meshes - The meshes on which PCA is calculated. @param[in] vertexWeights - The vertices for which PCA is calculated together with a weight per vertex. @param[in] varianceToKeep - The variance to keep for PCA. @param[in] premultiplyWeight - Whether the data is multiplied by weights before calculating PCA or not @param[in] maxModes - The maximum number of modes to keep. If <= 0 then it will calculate it based on @p varianceToKeep @return std::pair<Eigen::VectorX<T>, Eigen::Matrix<T, -1, -1>>  Returns mean and modes of PCA for just the region. The modes are multiplied by the standard deviation.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/PixelFormat.h` (Private)


#### enum `PixelFormat`  
`enum class PixelFormat`  
_L12-19_
- desc: Pixel formats that are accepted by VulkanAllInOneTexture
- L14 _public enumerator_ `MONOCHROME`
- L15 _public enumerator_ `BGR`
- L16 _public enumerator_ `RGB`
- L17 _public enumerator_ `BGRA`
- L18 _public enumerator_ `RGBA`

#### Free symbols / members of external scopes

- L21 _function_ `inline std::string PixelFormatName(PixelFormat pixelFormat)`
- L34 _function_ `inline int NumChannels(PixelFormat pixelFormat)`
- L51 _prototype_ `template <class T> constexpr T SaturatedValue();`
- L52 _function_ `template <class T> constexpr T SaturatedValue();`
- L57 _function_ `template <class T> void Convert(const T* src, T* target, int width, int height, PixelFormat srcPixelFormat, PixelFormat targetPixelFormat)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/Polyline.h` (Private)


#### class `Polyline`  
`template <class T, int D> class Polyline`  
_L17-256_
- desc: Polyline represents a curve as a set of points. When setting the control points, Polyine automtically removes all invalid i.e. zero-length line segments.
- L20 _public prototype_ `Polyline() = default;`
- L21 _public function_ `Polyline(Eigen::Matrix<T, D, -1>&& controlPoints)`
- L26 _public function_ `Polyline(const Eigen::Matrix<T, D, -1>& controlPoints)`
- L32 _public function_ `void Set(Eigen::Matrix<T, D, -1>&& controlPoints)` — Sets the control points of the polyline. Removes all empty segments.
- L38 _public function_ `void Set(const Eigen::Matrix<T, D, -1>& controlPoints)`
- L44 _public function_ `void RemoveEmptySegments()`
- L62 _public function_ `const Eigen::Matrix<T, D, -1>& ControlPoints() const`
- L64 _public function_ `int NumControlPoints() const`
- L67 _public function_ `bool Valid() const` — a polyline is only valid if it has at least two control points.
- L69 _public function_ `Eigen::Vector<T, D> EvaluatePoint(int segment, T lambda) const`
- L82 _public function_ `T ClosestPoint(const Eigen::Vector<T, D>& query, int& closestSegment, T& closestLambda) const` — Finds the closest point by going through all line segments and finding the closest point. @param [in]  query    The query position. @param [out] segment  The segment on which the closest point lies. @param [out] lambda   The lambda value between [0, 1] on the segment. @return the distance to the line
- L135 _public function_ `T ClosestPointAndDirection(const Eigen::Vector<T, D>& query, Eigen::Vector<T, D>& closest, Eigen::Vector<T, D>& direction, T& confidence, const Eigen::Vector<T, -1>* confidences = nullptr) const` — Finds the closest point by going through all line segments and finding the closest point. @param [in]  query      The query position. @param [out] closest    The closest point. @param [out] direction  The direction of the polyline at the closest point (defined by the line segment). @return the distance to the line
- L176 _public function_ `template <typename U = T> T ClosestPointAndNormal(const Eigen::Vector<T, 2>& query, Eigen::Vector<T, 2>& closest, Eigen::Vector<T, 2>& normal, T& confidence, const Eigen::Vector<T, -1>* confidences = nullptr, typename std::enable_if<std::is_same<U, T>::value && D == 2>::type* = 0) const` — Finds the closest point by going through all line segments and finding the closest point. @param [in]  query    The query position. @param [out] closest  The closest point. @param [out] normal   The normal of the polyline at the closest point (defined by the line segment). @return the distance to the line
- L200 _public function_ `template <typename U = T> T ClosestPointAndNormal(const Eigen::Vector<T, 3>& query, Eigen::Vector<T, 3>& closest, Eigen::Vector<T, 3>& normal, Eigen::Vector<T, 3>& direction, T& confidence, typename std::enable_if<std::is_same<U, T>::value && D == 3>::type* = 0) const` — Finds the closest point by going through all line segments and finding the closest point. @param [in]  query     The query position. @param [out] closest   The closest point. @param [out] normal    The random normal of the polyline. @param [out] direction The direction of the line segment. @return the distance to the line
- L227 _public function_ `template <typename U = T> std::vector<std::pair<T, int>> FindIntersections(const Eigen::Vector2<T>& A, const Eigen::Vector2<T>& B, typename std::enable_if<std::is_same<U, T>::value&& D == 2>::type* = 0) const` — Finds all intersection points of the line [A, B] with the polyline. @returns the intersection points as pairs, which contain alpha and control point index below, where alpha values define the intersection point: (1 - alpha) A + alpha B
- L255 _private member_ `Eigen::Matrix<T, D, -1> m_controlPoints;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/Procrustes.h` (Private)


#### class `Procrustes`  
`template <class T, int C> class Procrustes`  
_L16-131_
- desc: Procrustes Analsysis see https://en.wikipedia.org/wiki/Procrustes_analysis, https://en.wikipedia.org/wiki/Orthogonal_Procrustes_problem
- L22 _public function_ `static Affine<T, C, C> AlignRigid(const Eigen::Matrix<T, C, -1>& src, const Eigen::Matrix<T, C, -1>& target, bool withRotation = true)` — Calculate optimal rigid transformation to align src and target: min_affine || target - affine * src ||
- L56 _public function_ `static Affine<T, C, C> AlignRigidWeighted(const Eigen::Matrix<T, C, -1>& src, const Eigen::Matrix<T, C, -1>& target, const Eigen::VectorX<T>& weights, bool withRotation = true)` — Calculate optimal rigid transformation to align src and target: min_affine || (target - affine * src) * weight ||
- L92 _public function_ `static std::pair<T, Affine<T, C, C>> AlignRigidAndScale(const Eigen::Matrix<T, C, -1>& src, const Eigen::Matrix<T, C, -1>& target, bool withRotation = true)` — Calculate optimal rigid transformation and scale to align src and target: min_affine || target - affine * scale * src ||

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/QRigidMotion.h` (Private)


#### struct `QRigidMotion`  
`template <class T> struct QRigidMotion`  
_L30-68_
- desc: Rigid transform using Quaternion rotation.
- L32 _public member_ `Eigen::Quaternion<T> q;`
- L33 _public member_ `Eigen::Vector3<T> t;`
- L35 _public function_ `QRigidMotion() : q(Eigen::Quaternion<T>::Identity()), t(Eigen::Vector3<T>::Zero())`
- L36 _public function_ `QRigidMotion(const Eigen::Quaternion<T>& q, const Eigen::Vector3<T>& t) : q(q), t(t)`
- L37 _public function_ `QRigidMotion(const Eigen::Matrix<T, 4, 4>& mat) : q(mat.template block<3, 3>(0, 0)), t(mat.template block<3, 1>(0, 3))`
- L38 _public function_ `QRigidMotion(const Eigen::Matrix<T, 3, 3>& rot, const Eigen::Vector<T, 3>& t) : q(rot), t(t)`
- L41 _public function_ `Eigen::Transform<T, 3, Eigen::Affine> ToEigenTransform() const`
- L49 _public function_ `void ToEigenTransform(Eigen::Transform<T, 3, Eigen::Affine>& transform) const`
- L55 _public function_ `QRigidMotion operator*(const QRigidMotion& other) const`
- L62 _public function_ `QRigidMotion Inverse() const`

#### Free symbols / members of external scopes

- L8 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/Quaternion.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, bool NORMALIZE> Eigen::Matrix<T, 3, 3> QuaternionToRotationMatrix(const Vector<T>& quaternion)`
- L58 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix<T, 4, 1> QuaternionInverse(const Eigen::Matrix<T, 4, 1>& q)` — Calculates the inverse of the quaternion.
- L71 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix<T, 4, 1> QuaternionMultiplication(const Eigen::Matrix<T, 4, 1>& q1, const Eigen::Matrix<T, 4, 1>& q2)`
- L95 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix<T, 3, 1> QuaternionVectorMultiplication(const Eigen::Matrix<T, 4, 1>& q, const Eigen::Matrix<T, 3, 1>& p)` — Rotates vector \p p using the quaterion \p q. If NORMALIZE is false then it assumes that the quaternion is normalized, otherwise the return vector will be scaled by the squaredNorm of q.
- L117 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix<T, 9, 4> JacobianOfQuaternionToRotationMatrix(const Eigen::Vector4<T>& quaternion)` — Calculates the Jacobian dR/dq i.e of the rotation matrix R with respect to a Quaternion q. To get consistent Jacobians the normalization flag for JacobianOfQuaternionToRotationMatrix and QuaternionToRotationMatrix need to match.
- L219 _function_ `template <class T, bool NORMALIZE> Eigen::Matrix<T, 9, 4> JacobianOfIdentityQuaternionToRotationMatrix()` — Implements the special case of the Jacobian dR/dq of the rotation matrix R with respect to the identity quaternion q i.e. q = [0,0,0,1]. (i.e. apply these numbers to JacobianOfQuaternionToRotationMatrix()) In case of the calculating Jacobians for normalized quaternions the values for the w coordinate cancel completely out, and therefore that dimension can be dropped in an optimization. (see Iterative Estimation of Rotation and Translation using the Quaternion, by Mark Wheeler, 1995)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/QuaternionAverage.h` (Private)


#### Free symbols / members of external scopes

- L14 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/QuaternionVariable.h` (Private)


#### class `QuaternionVariable`  
`template <class T, bool PREMULTIPLY = true> class QuaternionVariable : public MatrixVariable<T, 3, 3>`  
_L29-103_
- inherits: `MatrixVariable<T,3,3>`
- desc: A Rotation variable using a quaternion as the underlying representation. Quaternion updates are handled "incrementally" as described in "Iterative Estimation of Rotation and Translation using the Quaternion", by Mark Wheeler, 1995 https://www.ri.cmu.edu/publications/iterative-estimation-of-rotation-and-translation-using-the-quaternion/. The advantage is that there are only 3 unknowns instead of the general case of 4 variables per quaternion. There are two options: PREMULTIPLY=true: R' = R * dR PREMULTIPLY=false: R' = dR * R
- L32 _public function_ `QuaternionVariable() : MatrixVariable<T, 3, 3>( 3)`
- L34 _public function_ `virtual void Update(const Vector<T>& dx) override`
- L50 _public function_ `virtual bool RealJacobian() override`
- L59 _private function_ `virtual SparseMatrixConstPtr<T> CalculateLocalJacobianMatrix() override` — @return dR/dq i.e. Jacobian of 3x3 rotation matrix with respect to a normalized quaternion
- L90 _private function_ `virtual void ProjectToManifold(Vector<T>& value) override`
- L102 _private member_ `Eigen::Quaternion<T> m_quaternion;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/RayTriangleIntersection.h` (Private)


#### Free symbols / members of external scopes

- L8 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> bool RayTriangleIntersection(const Eigen::Vector3<T>& rayOrigin, const Eigen::Vector3<T>& rayVector, const Eigen::Vector3<T>& vertex0, const Eigen::Vector3<T>& vertex1, const Eigen::Vector3<T>& vertex2, T* outT, Eigen::Vector3<T>* outIntersection)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/RigidICP.h` (Private)


#### Free symbols / members of external scopes

- L12 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) QRigidMotion<float> RigidICP(const Eigen::Matrix<float, 3, -1>& srcPts, const Eigen::Matrix<float, 3, -1>& srcNormals, const std::vector<int>& srcIndices, const Camera<float>& targetCamera, const Eigen::Matrix<float, 4, -1>& targetDepthAndNormals, const QRigidMotion<float>& inputRigidMotion, const int numIterations);`
- L22 _prototype_ `QRigidMotion<float> RigidICPFast(const Eigen::Matrix<float, 3, -1>& srcPts, const Eigen::Matrix<float, 3, -1>& srcNormals, const std::vector<int>& srcIndices, const Camera<float>& targetCamera, const Eigen::Matrix<float, 4, -1>& targetDepthAndNormals, const QRigidMotion<float>& inputRigidMotion, const int numIterations);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/RigidSolve.h` (Private)


#### Free symbols / members of external scopes

- L10 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) /** * Solves the rigid transformation minimizing the point to surface error i.e. sum(weight * targetNormal.dot(R * src + t - targetPt)) with * R = dR * initR * t = dT * initT * It only runs a single iteration of the linearization, and it optimizes from input transformation @p inputRigidMotion. * @param[in] outputDeltaTransform If True, outputs`
- L33 _prototype_ `template <class T> QRigidMotion<T> SolveRigid(const Eigen::Matrix<T, 3, -1>& srcPts, const Eigen::Matrix<T, 3, -1>& targetPts, const Eigen::Matrix<T, 3, -1>& targetNormals, const Eigen::Vector<T, -1>& weights, const Eigen::Vector<bool, 6>& dimensionsToOptimize);` — Solves the rigid transformation minimizing the point to surface error i.e. sum(weight * targetNormal.dot(R * src + t - targetPt)) with It only runs a single iteration of the linearization @param[in] dimensionsToOptimize  Which dimensions of the rotation and translation to optimize [rx, ry, rz, tx, ty, tz]
- L48 _prototype_ `QRigidMotion<float> SolveRigid(const SimdType* srcPtsX, const SimdType* srcPtsY, const SimdType* srcPtsZ, const SimdType* targetPtsX, const SimdType* targetPtsY, const SimdType* targetPtsZ, const SimdType* targetNormalsX, const SimdType* targetNormalsY, const SimdType* targetNormalsZ, const SimdType* weights, const int numSimdElements, const QRigidMotion<float>& inputRigidMotion, bool outputDeltaTransform = false);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/Rotation2DVariable.h` (Private)


#### class `Rotation2DVariable`  
`template <class T> class Rotation2DVariable : public MatrixVariable<T, 2, 2>`  
_L23-94_
- inherits: `MatrixVariable<T,2,2>`
- desc: A 2D Rotation variable using a an angle as underlying representation. https://en.wikipedia.org/wiki/Rotation_matrix
- L26 _public function_ `Rotation2DVariable() : MatrixVariable<T, 2, 2>( 1)`
- L29 _public function_ `void SetAngle(const T& angle)`
- L35 _public function_ `T Angle() const`
- L40 _public function_ `virtual void Update(const Vector<T>& dx) override`
- L47 _public function_ `virtual bool RealJacobian() override`
- L53 _private function_ `Eigen::Matrix<T, 4, 1> CalculateDenseJacobianMatrix()`
- L64 _private function_ `virtual SparseMatrixConstPtr<T> CalculateLocalJacobianMatrix() override` — @return dR/dq i.e. Jacobian of 2D rotation matrix with respect to the rotation angle
- L83 _private function_ `virtual void ProjectToManifold(Vector<T>& value) override`
- L93 _private member_ `Eigen::Rotation2D<T> m_rotation;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/RotationManifold.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int SIZE> Eigen::Matrix<T, SIZE, SIZE> ProjectToClosestRotationMatrix(const Eigen::Matrix<T, SIZE, SIZE>& M);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/SnapConfig.h` (Private)


#### struct `SnapConfig`  
`template <class T> struct SnapConfig`  
_L18-39_
- desc: Representation of a simple configuration for snapping vertices on one mesh to corresponding vertices on another mesh
- L20 _public member_ `static constexpr int32_t version = 1;`
- L21 _public member_ `std::string sourceMesh;`
- L22 _public member_ `std::vector<int> sourceVertexIndices;`
- L23 _public member_ `std::vector<int> targetVertexIndices;`
- L26 _public prototype_ `bool ReadJson(const JsonElement& element);` — read the snap config from a json element and return true if successful, false otherwise
- L32 _public prototype_ `void Apply(const Eigen::Matrix<T, 3, -1>& sourceVertices, Eigen::Matrix<T, 3, -1>& targetVertices) const;` — Apply the snap config to 'snap' the target vertices to the same positions as the source vertices @pre indices in the SnapConfig must be in range for the source and target vertices
- L35 _public prototype_ `bool IsValid(const Eigen::Matrix<T, 3, -1>& sourceVertices, const Eigen::Matrix<T, 3, -1>& targetVertices) const;` — is the SnapConfig valid to apply for the supplied source and target vertices ie source and target vertex indices in range
- L38 _public prototype_ `void WriteJson(JsonElement& json) const;` — Write the SnapConfig to Json

#### Free symbols / members of external scopes

- L43 _function_ `template <class T> bool ToBinaryFile(FILE* pFile, const SnapConfig<T>& snapConfig)`
- L54 _function_ `template <class T> bool FromBinaryFile(FILE* pFile, SnapConfig<T>& snapConfig)`
- L73 _function_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, SnapConfig<T>& snapConfig)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/SubdivisionMesh.h` (Private)


#### class `SubdivisionMesh`  
`template <class T> class SubdivisionMesh`  
_L17-37_
- desc: SubdivisionMesh provides functionality to resample a mesh based on subdivision stencil weights.
- L20 _public prototype_ `void Create(const Mesh<T>& subdivisionTopology, const std::vector<std::tuple<int, int, T>>& stencilWeights);`
- L22 _public prototype_ `void SetBaseMesh(const Mesh<T>& mesh);`
- L23 _public prototype_ `void SetBaseVertices(const Eigen::Matrix<T, 3, -1>& vertices);`
- L25 _public prototype_ `Mesh<T> EvaluateMesh(Eigen::VectorX<T> vertexDisplacements = Eigen::VectorX<T>()) const;`
- L27 _public prototype_ `Eigen::VectorX<T> EvaluateWeights(const Eigen::VectorX<T>& baseWeights) const;`
- L29 _public function_ `int NumVertices() const`
- L31 _public function_ `const Mesh<T>& GetSubdivisionMesh() const`
- L34 _private member_ `std::vector<std::tuple<int, int, T>> m_stencilWeights;`
- L35 _private member_ `Mesh<T> m_subdivisionMesh;`
- L36 _private member_ `Mesh<T> m_triangulatedSubdivisionMesh;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/TetConstraints.h` (Private)


#### class `TetConstraints`  
`template <class T> class TetConstraints`  
_L23-181_
- desc: Various tetrahedral contraints including strain hyperelasticity, volume preservation, and the deformation gradient.
- L31 _public prototype_ `TetConstraints() = default;`
- L32 _public prototype_ `TetConstraints(const TetConstraints& o) = delete;`
- L33 _public prototype_ `TetConstraints& operator=(const TetConstraints& o) = delete;`
- L36 _public function_ `void SetTopology(const Eigen::Matrix<int, 4, -1>& tets)` — Sets the topology of the tetrahedral mesh.
- L39 _public prototype_ `void SetRestPose(const Eigen::Matrix<T, 3, -1>& vertices, bool allowInvertedTets = false);` — Set the rest pose of the tetrahedral mesh.
- L47 _public prototype_ `void SetTetsMask(const Eigen::Vector<int, -1>& mask);` — Set mask for the tets. it is different from fixing vertices in a MatrixVariable as boundary primitives would still be evaluated. (mask > 0) -> the tet is not optimized (mask <= 0) -> the tet is optimized
- L50 _public function_ `void ClearTetsMask()` — Delete the mask for the tets. All the tets will be optimized.
- L56 _public function_ `int NumTets() const` — @returns the number of tetraheda.
- L58 _public function_ `const std::vector<Eigen::Matrix<T, 3, 3>>& InvRestFrame() const`
- L59 _public function_ `const std::vector<T>& SqrtRestVolume() const`
- L67 _public prototype_ `DiffData<T> EvaluateStrain(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight, ElasticityModel elModel = Corotated) const;` — Tetrahedral strain hyperelasticity. Evaluates residual function r(x) and its Jacobian, e.g. - corotated: r(x) = F(x) - R(F(x)) - Neo Hookean: r(x) = sqrt(trace(F^T * F)) - sqrt(3)
- L71 _public prototype_ `void SetupStrain(const Eigen::Matrix<T, 3, -1>& vertices, const T strainWeight, VertexConstraintsExt<T, 9, 4>& vertexConstraints) const;` — Setup strain constraints in @p vertexConstraints. It is not compatible with pre-stretch
- L79 _public prototype_ `DiffData<T> EvaluateStrainLinearProjective( const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight, ElasticityModel elModel = Corotated, T minRange = T(1), T maxRange = T(1)) const;` — Tetrahedral strain hyperelasticity. Evaluates residual function r(x) and its Jacobian, e.g. - linear elasticity: r(x) = F(x) - I - corotated: r(x) = F(x) - R (where R is fixed to the rotation closest to F).
- L90 _public prototype_ `DiffData<T> EvaluateVolumeLoss( const DiffDataMatrix<T, 3, -1>& vertices, T volumeWeight) const;` — Tetrahedral volume loss. Evaluates residual function r(x) and its Jacobian, e.g. r(x) = det(F(x)) - 1
- L98 _public prototype_ `DiffData<T> EvaluateVolumeLossProjective( const DiffDataMatrix<T, 3, -1>& vertices, T volumeWeight, T minRange = T(1), T maxRange = T(1)) const;` — Tetrahedral volume loss. Evaluates residual function r(x) and its Jacobian, e.g. r(x) = F(x) - F' (where F' is fixed to the volume preserving deformation closest to F)
- L105 _public prototype_ `DiffDataMatrix<T, 9, -1> EvaluateDeformationGradient(const DiffDataMatrix<T, 3, -1>& vertices, bool volumeWeighted = true, const std::vector<T>& perTetWeight = std::vector<T>()) const;` — @returns F(x)
- L114 _public prototype_ `DiffData<T> EvaluateStrainActivation( const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 9, -1>& activations, const T strainWeight) const;` — Tetrahedral strain hyperelasticity evaluated in terms of activation. Evaluates residual function r(x) and its Jacobian, e.g. - r(x) = F(x) - R(x) * A
- L123 _public prototype_ `DiffDataMatrix<T, 9, -1> EvaluateDeformationGradientLossProjective( const DiffDataMatrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 9, -1>& targetGradients, bool volumeWeighted) const;` — Evaluate residual and Jacobian between deformation gradient and desired gradient value.
- L135 _public prototype_ `DiffData<T> EvaluateGravityPotential( const DiffDataMatrix<T, 3, -1>& vertices, const T acceleration, const T density, const int hAxis = 1) const;` — Evaluate gravity potential per-vertex R(x) = mass * acceleration * location[hAxis] The constraint is undefined for points below the zero plane. In the current implementation, points under the zero plane are given zero potential
- L149 _public prototype_ `Eigen::VectorX<T> EvaluateCauchyGreenStrainTensor( const DiffDataMatrix<T, 3, -1>& vertices) const;` — Evaluates the Cauchy-Green tensor, e.g. r(x) = 0.5 * (F^T * F - I) It is useful for color coding the strain over a mesh. The current implementation does not provide the Jacobian.
- L159 _private prototype_ `DiffData<T> EvaluateStrainCorotated(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight) const;` — Tetrahedral strain hyperelasticity. Evaluates residual function r(x) and its Jacobian, e.g. - corotated: r(x) = F(x) - R(F(x))
- L166 _private prototype_ `DiffData<T> EvaluateStrainNH(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight) const;` — Tetrahedral strain hyperelasticity. Evaluates residual function r(x) and its Jacobian, e.g. - Neo Hookean: r(x) = sqrt(trace(F^T * F)) - sqrt(3)
- L173 _private prototype_ `Eigen::Matrix<T, 3, 3> EvaluateDeformationGradient(const DiffDataMatrix<T, 3, -1>& vertices, const int* v, const int t) const;` — Evaluate elastic deformation gradient for one tet. F_elastic = F_geometry * F_rest^-1 The elastic deformation gradient is employed in the elastic strain evaluation
- L175 _private member_ `int m_numVertices;`
- L176 _private member_ `Eigen::Matrix<int, 4, -1> m_tets;`
- L177 _private member_ `std::vector<Eigen::Matrix<T, 3, 3>> m_invRestFrame;`
- L178 _private member_ `std::vector<T> m_sqrtRestVolume;`
- L179 _private member_ `std::unordered_set<ElasticityModel> validElModels = {Linear, Corotated, NeoHookean};`
- L180 _private member_ `Eigen::Vector<int, -1> m_mask;`

#### enum `TetConstraints::ElasticityModel`  
`enum ElasticityModel`  
_L26-29_
- L28 _public enumerator_ `Linear = 0`
- L28 _public enumerator_ `Linear = 0`
- L28 _public enumerator_ `Linear = 0`

#### Free symbols / members of external scopes

- L13 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/TetMesh.h` (Private)


#### class `TetMesh`  
`template <class T> class TetMesh`  
_L17-63_
- desc: Class representing tetrahedral meshes.
- L20 _public prototype_ `TetMesh() = default;`
- L21 _public prototype_ `TetMesh(const TetMesh& o) = default;`
- L22 _public prototype_ `TetMesh& operator=(const TetMesh& o) = default;`
- L24 _public function_ `int NumVertices() const`
- L25 _public function_ `int NumTets() const`
- L27 _public function_ `const Eigen::Matrix<T, 3, -1>& Vertices() const`
- L28 _public function_ `void SetVertices(const Eigen::Matrix<T, 3, -1>& vertices)`
- L30 _public function_ `const Eigen::Matrix<int, 4, -1>& Tets() const`
- L31 _public function_ `void SetTets(const Eigen::Matrix<int, 4, -1>& tets)`
- L34 _public prototype_ `void LoadFromNPY(std::string vertices_fname, std::string tets_fname);` — Loads m_vertices and m_tets from NPY files
- L37 _public prototype_ `void SaveToNPY(std::string vertices_fname, std::string tets_fname) const;` — Saves m_vertices and m_tets to NPY files
- L39 _public prototype_ `void BoundingBox(Eigen::Vector3<T>& bbmin, Eigen::Vector3<T>& bbmax) const;`
- L42 _public prototype_ `void CropByPlane(std::vector<bool>& tetMask, const Eigen::Vector<T, 3>& normal, T offset) const;` — Sets to false the tetMask tets which have at least one vertex below a plane specified by normal and offset
- L45 _public prototype_ `void FullVisualizationMesh(Eigen::Matrix<T, 3, -1>& visVertices, Eigen::Matrix<int, 3, -1>& visTriangles) const;` — Sets a full visualization mesh: 12 triangles per tetrahedron
- L48 _public prototype_ `void BoundaryMesh(Eigen::Matrix<T, 3, -1>& visVertices, Eigen::Matrix<int, 3, -1>& visTriangles, std::vector<bool>* tetPresent = nullptr) const;` — Sets a boundary visualization mesh: one triangle per boundary face. tetPresent can flag tets to be ignored.
- L51 _public prototype_ `void BoundaryMesh(Eigen::Matrix<int, 3, -1>& visTriangles, std::vector<bool>* tetPresent = nullptr) const;` — Sets the boundary visualization mesh: one triangle per boundary face. tetPresent can flag tets to be ignored. Vertex indices are the same as for tets.
- L54 _public prototype_ `std::vector<int> BoundaryTets() const;` — @return all boundary tets
- L56 _public prototype_ `void TetVolumeStatistics(T& minVol, T& avgVol, T& maxVol, bool absValue = false) const;`
- L58 _public prototype_ `Eigen::VectorX<T> TetVolumes() const;`
- L61 _private member_ `Eigen::Matrix<T, 3, -1> m_vertices;`
- L62 _private member_ `Eigen::Matrix<int, 4, -1> m_tets;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/Triangle.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> T TriangleQuality(const Eigen::Vector3<T>& v1, const Eigen::Vector3<T>& v2, const Eigen::Vector3<T>& v3)`
- L44 _function_ `template <class T> inline Eigen::Vector3<T> ClosestPtPointTriangle(Eigen::Vector3<T> p, Eigen::Vector3<T> a, Eigen::Vector3<T> b, Eigen::Vector3<T> c)` — Closest point calculation as described in "Real-Time Collision Detection" by Christer Ericson @returns the barycentric coordinates

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/TriangleBending.h` (Private)


#### class `TriangleBending`  
`template <class T> class TriangleBending`  
_L33-115_
- desc: Triangle bending model. The triangle bending model creates bending constraints for each pair of triangles that share an edge. The goal is to keep the dihedral angle for the rest and deformed position consistent. The class implements two different models based on a quadratic bending energy as well as measuring the dihedral error directly. See EvaluateQuadratic() and EvaluateDihedral(). The bending model is rotation and translation invariant. EvaluateQuadratic() is scale invariant in the sense that the energy is the same no matter how you scale the rest and deformed vertices, but the scale needs to be consistent for both meshes. EvaluateDihedral() is scale invariant in the sense that both rest vertices and deformed vertices can have completely different scales. Note regarding scale invariance: you need to be careful when integrating the bending constraint with other constraints that may not be scale invariant (e.g. point to point constraint) or otherwise an energy minimization will result in different results depending on the global scale of the data. You can anchieve this by globally modify the bending energy by passing in a global bending weight. Note that testing on spherical triangle meshes has shown that the bending energy is not equal to the integrated squared mean curvature. TODO: figure out why this is not the case. Implemented for T=float and T=double.
- L36 _public prototype_ `TriangleBending() = default;`
- L37 _public prototype_ `TriangleBending(const TriangleBending& o) = delete;`
- L38 _public prototype_ `TriangleBending& operator=(const TriangleBending& o) = delete;`
- L43 _public prototype_ `void SetTopology(const Eigen::Matrix<int, 3, -1>& triangles);` — Sets the triangles/topology for which to calculate the bending terms.
- L47 _public function_ `int NumBendingTerms() const` — @returns the number of bending constraints i.e. the number of neighbouring triangles that share an edge.
- L53 _public prototype_ `void SetRestPose(const Eigen::Matrix<T, 3, -1>& vertices);` — Initializes the rest position for the bending constraints. Sets up the base data for both Quadratic and Dihedral bending constraints.
- L70 _public prototype_ `DiffData<T> EvaluateQuadratic(const DiffDataMatrix<T, 3, -1>& vertices, const T bendingWeight) const;` — Quadratic bending energy (energy = ||K x||_2^2) as described in Bergou et al, "A Quadratic Bending Model for Inextensible Surfaces", see Implementation Details as well as  Wardetzky et al, "Discrete Quadratic Curvature Energies", where Equation (7) is equivalent to the cotan formulation. The latter shows the relationship to the Dihedral error. The main issue of the quadratic bending model is that it is only accurate for inextensible surface i.e. surfaces that cannot strain which is why the model is not scale invariant for different rest and deformed scales. Also the model cannot differentiate between convex and concave curvature. The advantage of the implementation is that the Jacobian is constant, though the Jacobian is also not fully correct as it does not take the normalization of the target vector into account. (see implementation for details) @param vertices       The current deformed vertex configuration. @param bendingWeight  A global weighting factor: energy = bendingWeight ||K x||_2^2
- L82 _public prototype_ `DiffData<T> EvaluateDihedral(const DiffDataMatrix<T, 3, -1>& vertices, const T bendingWeight) const;` — Dihedral bending energy (energy = (theta - theta_rest)^2 Le^2/Ae) as described in Fröhlich and Botsch, "Example-Driven Deformations Based on Discrete Shells" and Grinspun et al, "Discrete Shells", in each case Equation (2). The advantage over the quadratic model is that it optimizes the dihedral angle of neighbouring triangles directly and it is not influenced by any other in-plane deformation of the triangles. However, the cost is that @param vertices       The current deformed vertex configuration. @param bendingWeight  A global weighting factor.
- L85 _public prototype_ `Eigen::VectorX<T> EvaluateAngles(const Eigen::Matrix<T, 3, -1>& vertices) const;` — Calculates the dihedral angle for all neighbouring triangle pairs. Output size is NumBendingTerms().
- L88 _public function_ `const Eigen::VectorX<T>& RestBendingEnergy() const` — @returns The rest bending energy as calculated using th quadratic bending model
- L90 _public function_ `const Eigen::VectorX<T>& RestEdgeAreaSqrt() const`
- L91 _public function_ `const Eigen::VectorX<T>& RestAngle() const`
- L92 _public function_ `const Eigen::VectorX<T>& RestEdgeLength() const`
- L94 _public function_ `const Eigen::Matrix<int, 4, -1> TrianglePairs() const`
- L97 _public prototype_ `Eigen::VectorX<T> EvaluateQuadraticPerVertex(const DiffDataMatrix<T, 3, -1>& vertices) const;` — Evaluate the quadratic bending per edgepair, and then assign for each vertex the maximum bending value
- L100 _public prototype_ `Eigen::VectorX<T> EvaluateDihedralPerVertex(const DiffDataMatrix<T, 3, -1>& vertices) const;` — Evaluate the diahedral bending per edgepair, and then assign for each vertex the maximum bending value
- L103 _private member_ `int m_numVertices;`
- L105 _private member_ `Eigen::Matrix<int, 3, -1> m_triangles;`
- L106 _private member_ `Eigen::Matrix<int, 4, -1> m_trianglePairs;`
- L108 _private member_ `Eigen::Matrix<T, 4, -1> m_K;`
- L109 _private member_ `Eigen::VectorX<T> m_restBendingEnergy;`
- L111 _private member_ `Eigen::VectorX<T> m_restAngle;`
- L112 _private member_ `Eigen::VectorX<T> m_restEdgeAreaSqrt;`
- L113 _private member_ `Eigen::VectorX<T> m_restOneOverEdgeAreaSqrt;`
- L114 _private member_ `Eigen::VectorX<T> m_restEdgeLength;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/TriangleDeformationGradient.h` (Private)


#### class `TriangleDeformationGradient`  
`template <class T> class TriangleDeformationGradient`  
_L29-63_
- desc: Triangle deformation gradient for deformation transfer as described in "Deformation Transfer for Detail-Preserving Surface Editing" by Botsch et al. (however it currently does not include weighting based on the triangle area) The class can be used for deformation transfer in the following way: Input: undeformedA, undeformedB, deformedA Output: deformedB SetTopology(undeformedA.Triangles()) SetRestPose(undeformedA.Vertices()) G = DeformationGradient(deformedA.Vertices()) SetRestPose(undeformedB.Vertices()) minimize(G - DeformationGradient(deformedB)) // using DiffDataMatrix version
- L32 _public prototype_ `TriangleDeformationGradient() = default;`
- L33 _public prototype_ `TriangleDeformationGradient(const TriangleDeformationGradient& o) = delete;`
- L34 _public prototype_ `TriangleDeformationGradient& operator=(const TriangleDeformationGradient& o) = delete;`
- L37 _public prototype_ `void SetTopology(const Eigen::Matrix<int, 3, -1>& triangles);` — Set the mesh topology
- L40 _public prototype_ `void SetRestPose(const Eigen::Matrix<T, 3, -1>& vertices);` — Set the rest pose
- L43 _public function_ `int NumTriangles() const` — Returns the number of triangles
- L48 _public prototype_ `Eigen::Matrix<T, 9, -1> DeformationGradient3D(const Eigen::Matrix<T, 3, -1>& vertices) const;` — Calculate the 3D deformation gradient from the rest pose (@see SetRestPose()) to @p vertices
- L56 _public prototype_ `DiffDataMatrix<T, 9, -1> DeformationGradient3D(const DiffDataMatrix<T, 3, -1>& vertices) const;` — Calculate the 3D deformation gradient from the rest pose (@see SetRestPose()) to @p vertices. As described in "Deformation Transfer for Detail-Preserving Surface Editing", by Botsch et al the Gradient Matrix G does not need the normal, but instead is set to be zero. The Jacobian output accordingly does not need the normal.
- L59 _private member_ `Eigen::Matrix<int, 3, -1> m_triangles;`
- L62 _private member_ `std::vector<Eigen::Matrix<T, 3, 3>> m_invRestFrame3D;` — inv(RestFrame3D) per triangle - (extended by normal)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/TriangleStrain.h` (Private)


#### class `TriangleStrain`  
`template <class T> class TriangleStrain`  
_L35-131_
- desc: Triangle strain using projections as described in Bouaziz et al, "Projective Dynamics: Fusing Constraint Projections for Fast Simulation" see also https://www.shapeop.org. The deformation gradient from the rest triangle to the current triangle should only have a rotation component but no stretching i.e. you can rotate the triangle but not stretch it. Define a Frame (local coordinate system) as [v1 - v0, v2 - v0] Then we get the following deformation gradient: F = CurrFrame * inv(RestFrame) G should only be a rotation, so the closest valid deformation gradient F' = svd(G).U * svd(F).V.t() The stretch energy is therefore || F - F' ||_2^2 For a triangle the deformation gradient has rank 2, and therefore we can simply project the 3D coordinates to 2D: RestFrame = (Proj2D * RestFrame3D) CurrFrame = CurrFrame3D Then F' is a 3x2 matrix. The stretch energy is then || CurrFrame3D * inv(Proj2D * RestFrame3D) - F' ||_2^2 The stretch energy is scale invariant, so typically you would weight the stretch energy scaled by the triangle area: Stretch Energy = triangleArea  * || CurrFrame3D * inv(Proj2D * RestFrame3D) - F' ||_2^2
- L38 _public prototype_ `TriangleStrain() = default;`
- L39 _public prototype_ `TriangleStrain(const TriangleStrain& o) = delete;`
- L40 _public prototype_ `TriangleStrain& operator=(const TriangleStrain& o) = delete;`
- L42 _public prototype_ `void SetTopology(const Eigen::Matrix<int, 3, -1>& triangles);`
- L44 _public prototype_ `void SetRestPose(const Eigen::Matrix<T, 3, -1>& vertices, bool areaWeighs = false);`
- L46 _public function_ `const std::vector<T>& SqrtRestArea() const`
- L64 _public prototype_ `DiffData<T> EvaluateProjectiveStrain(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight, const Eigen::Vector<T, -1>& inversionCheck, const T minLambda = T(1), const T maxLambda = T(1)) const;` — Triangle projective strain Evaluates residual function r(x) and its Jacobian, e.g. r(x) = F(x) - F' (where F' is the closest feasible deformation gradient) Triangle inversions are handled according to inversionCheck. (inversionCheckinversionCheck[i] < 0) -> the triangle is flipped and the eigenvalue of the deformation gradient is reflected (maxLambda > 1) and (minLambda < 1) define the maximum allowed stretch and compression
- L72 _public function_ `DiffData<T> EvaluateProjectiveStrain(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight, const T minLambda = T(1), const T maxLambda = T(1)) const` — Triangle projective strain Evaluates residual function r(x) and its Jacobian, e.g. r(x) = F(x) - F' (where F' is the closest feasible deformation gradient) (maxLambda > 1) and (minLambda < 1) define the maximum allowed stretch and compression
- L77 _public prototype_ `DiffData<T> EvaluateGreenStrain(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight) const;`
- L84 _public prototype_ `DiffData<T> EvaluateNHStrain(const DiffDataMatrix<T, 3, -1>& vertices, const T strainWeight) const;` — Triangular strain hyperelasticity. Evaluates residual function r(x) and its Jacobian, e.g. - Neo Hookean: r(x) = sqrt(trace(F^T * F)) - sqrt(2)
- L86 _public function_ `const Eigen::Matrix<int, 3, -1>& Triangles() const`
- L89 _public prototype_ `Eigen::VectorX<T> EvaluateProjectiveStrainPerVertex(const DiffDataMatrix<T, 3, -1>& vertices) const;` — Evaluate the projective strain per triangle, and then assign for each vertex the maximum strain value
- L92 _public prototype_ `Eigen::VectorX<T> EvaluateGreenStrainPerVertex(const DiffDataMatrix<T, 3, -1>& vertices) const;` — Evaluate the green strain per triangle, and then assign for each vertex the maximum strain value
- L98 _public prototype_ `DiffData<T> EvaluateAreaLoss(const DiffDataMatrix<T, 3, -1>& vertices, T areaWeight) const;` — Triangle area loss. Evaluates residual function r(x) and its Jacobian, e.g. r(x) = sqrt(det(F(x).T * F)) - 1
- L109 _public prototype_ `DiffData<T> EvaluateAreaLossProjective(const DiffDataMatrix<T, 3, -1>& vertices, const T areaWeight, const Eigen::Vector<T, -1>& inversionCheck, const T minLambda = T(1), const T maxLambda = T(1)) const;` — Triangle projective area loss Evaluates residual function r(x) and its Jacobian, e.g. r(x) = F(x) - F' (where F' is fixed to the area preserving deformation closest to F) Triangle inversions are handled according to inversionCheck. (inversionCheckinversionCheck[i] < 0) -> the triangle is flipped and the eigenvalue of the deformation gradient is reflected (maxLambda > 1) and (minLambda < 1) define the maximum allowed stretch and compression
- L117 _public function_ `DiffData<T> EvaluateAreaLossProjective(const DiffDataMatrix<T, 3, -1>& vertices, const T areaWeight, const T minLambda = T(1), const T maxLambda = T(1)) const` — Triangle projective area loss Evaluates residual function r(x) and its Jacobian, e.g. r(x) = F(x) - F' (where F' is fixed to the area preserving deformation closest to F) (maxLambda > 1) and (minLambda < 1) define the maximum allowed stretch and compression
- L123 _private member_ `int m_numVertices;`
- L125 _private member_ `Eigen::Matrix<int, 3, -1> m_triangles;`
- L128 _private member_ `std::vector<Eigen::Matrix<T, 2, 2>> m_invRestFrame2D;` — inv(Proj2D * RestFrame3D) per triangle
- L130 _private member_ `std::vector<T> m_sqrtRestArea;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/VertexConstraints.h` (Private)


#### class `VertexConstraints`  
`template <class T, int ResidualSize, int NumConstraintVertices> class VertexConstraints`  
_L25-226_
- desc: @brief Class encapsulating a set of linearized vertex constraints. @tparam T                      Scalar type, typically float or double. @tparam ResidualSize           Number of constraints per vertex. @tparam NumConstraintVertices  Number of involved vertices per constraint. The jacobian dCdV (i.e. constraint to vertex) is the same for each involved vertex multiplied with the barycentric weights. i.e. dCdV = w1 * dCdV1 + w2 * dCdV2 in case two vertices are involved in a constraint. For individual jacobian per vertex see VertexConstraintsExt
- L28 _public function_ `int64_t NumberOfConstraints() const`
- L30 _public function_ `int64_t NumberOfReservedConstraints() const`
- L32 _public function_ `void Clear(bool clearMemory = false)`
- L45 _public function_ `void ResizeToFitAdditionalConstraints(int64_t numAdditionalConstraints)`
- L58 _public function_ `void AddConstraint(const Eigen::Vector<int, NumConstraintVertices>& vIDs, const Eigen::Vector<T, NumConstraintVertices>& weightsPerVertex, const Eigen::Vector<T, ResidualSize>& residual, const Eigen::Matrix<T, ResidualSize, 3>& jacobian)`
- L71 _public function_ `void AddConstraint(int vID, const T residual, const Eigen::Matrix<T, ResidualSize, 3>& jacobian)`
- L83 _public function_ `void AddConstraint(int vID, const T residual, Eigen::Matrix<T, ResidualSize, 3>&& jacobian)`
- L95 _public function_ `void AddConstraint(int vID, const Eigen::Vector<T, ResidualSize>& residual, const Eigen::Matrix<T, ResidualSize, 3>& jacobian)`
- L106 _public function_ `void AddConstraint(int vID, const Eigen::Vector<T, ResidualSize>& residual, Eigen::Matrix<T, ResidualSize, 3>&& jacobian)`
- L117 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> Residual() const`
- L122 _public function_ `Eigen::VectorX<T> EvaluateResidual(const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& baseVertices) const`
- L139 _public function_ `Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> EvaluateJacobian(const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>& denseVertexJacobian, Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& denseVertexConstraintJacobian, TITAN_NAMESPACE::TaskThreadPool* taskThreadPool = nullptr) const`
- L186 _public function_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> EvaluateJacobian(const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>& denseVertexJacobian) const`
- L193 _public function_ `SparseMatrix<T> SparseJacobian(int numVertices) const`
- L215 _public function_ `const std::vector<Eigen::Matrix<T, ResidualSize, 3>>& Jacobians() const`
- L216 _public function_ `const std::vector<Eigen::Vector<int, NumConstraintVertices>>& VertexIDs() const`
- L217 _public function_ `const std::vector<Eigen::Vector<T, NumConstraintVertices>>& WeightsPerVertex() const`
- L220 _private member_ `std::vector<Eigen::Vector<int, NumConstraintVertices>> m_vIDs;`
- L221 _private member_ `std::vector<Eigen::Vector<T, NumConstraintVertices>> m_weightsPerVertex;`
- L222 _private member_ `std::vector<Eigen::Vector<T, ResidualSize>> m_residuals;`
- L223 _private member_ `std::vector<Eigen::Matrix<T, ResidualSize, 3>> m_jacobians;`
- L224 _private member_ `int64_t m_numConstraints = 0;`
- L225 _private member_ `int64_t m_reservedConstraints = 0;`

#### class `VertexConstraintsExt`  
`template <class T, int ResidualSize, int NumConstraintVertices> class VertexConstraintsExt`  
_L239-433_
- desc: @brief Class encapsulating a set of linearized vertex constraints. @tparam T                      Scalar type, typically float or double. @tparam ResidualSize           Number of constraints per vertex. @tparam NumConstraintVertices  Number of involved vertices per constraint. The jacobian dCdV (i.e. constraint to vertex) is different for each vertex.
- L242 _public function_ `int64_t NumberOfConstraints() const`
- L244 _public function_ `int64_t NumberOfReservedConstraints() const`
- L246 _public function_ `void Clear(bool clearMemory = false)`
- L258 _public function_ `void ResizeToFitAdditionalConstraints(int64_t numAdditionalConstraints)`
- L270 _public function_ `void AddConstraint(const Eigen::Vector<int, NumConstraintVertices>& vIDs, const Eigen::Vector<T, ResidualSize>& residual, const Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>& jacobian)`
- L283 _public function_ `void AddConstraint(int vID, const T residual, const Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>& jacobian)`
- L294 _public function_ `void AddConstraint(int vID, const T residual, Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>&& jacobian)`
- L305 _public function_ `void AddConstraint(int vID, const Eigen::Vector<T, ResidualSize>& residual, const Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>& jacobian)`
- L315 _public function_ `void AddConstraint(int vID, const Eigen::Vector<T, ResidualSize>& residual, Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>&& jacobian)`
- L325 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> Residual() const`
- L330 _public function_ `Eigen::VectorX<T> EvaluateResidual(const Eigen::Matrix<T, 3, -1>& vertices, const Eigen::Matrix<T, 3, -1>& baseVertices) const`
- L347 _public function_ `Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> EvaluateJacobian(const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>& denseVertexJacobian, Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& denseVertexConstraintJacobian, TITAN_NAMESPACE::TaskThreadPool* taskThreadPool = nullptr) const`
- L394 _public function_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> EvaluateJacobian(const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>& denseVertexJacobian) const`
- L401 _public function_ `SparseMatrix<T> SparseJacobian(int numVertices) const`
- L423 _public function_ `const std::vector<Eigen::Vector<T, ResidualSize>>& Residuals() const`
- L424 _public function_ `const std::vector<Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>>& Jacobians() const`
- L425 _public function_ `const std::vector<Eigen::Vector<int, NumConstraintVertices>>& VertexIDs() const`
- L428 _private member_ `std::vector<Eigen::Vector<int, NumConstraintVertices>> m_vIDs;`
- L429 _private member_ `std::vector<Eigen::Vector<T, ResidualSize>> m_residuals;`
- L430 _private member_ `std::vector<Eigen::Matrix<T, ResidualSize, 3 * NumConstraintVertices>> m_jacobians;`
- L431 _private member_ `int64_t m_numConstraints = 0;`
- L432 _private member_ `int64_t m_reservedConstraints = 0;`

#### Free symbols / members of external scopes

- L150 _function_ `auto process = [&](int start, int end)` (scope `VertexConstraints::EvaluateJacobian`)
- L358 _function_ `auto process = [&](int start, int end)` (scope `VertexConstraintsExt::EvaluateJacobian`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/VertexLaplacian.h` (Private)


#### class `VertexLaplacian`  
`template <class T> class VertexLaplacian`  
_L19-57_
- desc: Class to evaluate the classic cotan Laplacian on the vertices of a triangle mesh i.e. E = || Lx - Lx0 ||_2^2. Implemented for T=float and T=double.
- L30 _public prototype_ `VertexLaplacian() = default;`
- L31 _public prototype_ `VertexLaplacian(const VertexLaplacian& o) = delete;`
- L32 _public prototype_ `VertexLaplacian& operator=(const VertexLaplacian& o) = delete;`
- L39 _public prototype_ `void SetRestPose(const Mesh<T>& mesh, Type type = Type::COTAN);` — Sets the rest pose i.e. defines the Laplacian matrix with weights depending on @p type For all types, the resulting Laplacian weights are normalized and divided by the squared root of the vertex area. This means that the resulting vertex laplacian is scale invariant.
- L46 _public prototype_ `DiffDataMatrix<T, 3, -1> EvaluateLaplacianOnOffsets(const DiffDataMatrix<T, 3, -1>& vertexOffsets, const T laplacianWeight) const;` — Evaluate Ldx (instead of Lx - Lx0) @param vertexOffset   The current deformed vertex configuration. @param laplacianWeight  A global weighting factor: energy = laplacianWeight ||L dx||_2^2
- L53 _public prototype_ `static SparseMatrix<T> LaplacianMatrix(const Mesh<T>& mesh, Type type = Type::COTAN, int dim = 1);` — @brief Calculates the laplacian matrix @param dim Set the output dimension i.e. 3 if we use a laplacian per vertex
- L56 _private member_ `SparseMatrix<T> m_laplacianMatrix;`

#### enum `VertexLaplacian::Type`  
`enum class Type`  
_L22-27_
- L24 _public enumerator_ `UNIFORM` — uniform laplacian
- L25 _public enumerator_ `COTAN` — laplacian using cotangent weights
- L26 _public enumerator_ `MEANVALUE`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/geometry/WrapDeformer.h` (Private)


#### struct `WrapDeformerParams`  
`template <class T> struct WrapDeformerParams`  
_L23-41_
- desc: Parameters for a wrap deformer (see below)
- L31 _public member_ `static constexpr int32_t version = 2;`
- L32 _public member_ `bool bExclusiveBind = true;`
- L33 _public member_ `FalloffType falloffType = FalloffType::Volume;`
- L34 _public member_ `T maxDistance = std::numeric_limits<T>::max();`
- L35 _public member_ `T weightThreshold = 0;`
- L36 _public member_ `bool bAutoWeightThreshold = true;`
- L37 _public member_ `T normalOffset = 0;` — optional parameter; if non-zero, wrapping results will be displaced by the normalOffset along the local reference frame normals, allowing a wrapped result to be displaced slightly from its driver mesh
- L38 _public member_ `Eigen::VectorXi wrappedMeshVertexIndicesToApplyTo;` — optional parameter; if empty, the wrap deformer will be applied to all mesh indices; if contains values, it will only be applied to the specified mesh vertices
- L40 _public prototype_ `bool ReadJson(const JsonElement& element);`

#### enum `WrapDeformerParams::FalloffType`  
`enum class FalloffType`  
_L25-29_
- L27 _public enumerator_ `Volume`
- L28 _public enumerator_ `Surface` — TODO Surface falloff is not currently implemented; not sure what surface distance means; perhaps geodesic distance from closest point?

#### class `WrapDeformer`  
`template <class T> class WrapDeformer`  
_L51-97_
- desc: An implementation of a 'wrap-deformer'. A method for deforming one 'wrapped' mesh to follow the deformations of another 'driver' mesh using local nearest point to surface geometry, defined in the local coordinate space of the mesh. This is similar to the Maya Wrap Deformer in concept and results, although we don't know exactly how that is implemented. There are a couple of minor additions to the vanilla Maya implementation: i) you can offset the wrapped mesh along the driver mesh normals, ii) you can specify a subset of wrapped mesh vertices to apply the wrapping to.
- L54 _public function_ `WrapDeformer()`
- L60 _public prototype_ `void SetMeshes(const std::shared_ptr<const Mesh<T>>& driverMesh, const std::shared_ptr<const Mesh<T>>& wrappedMesh);` — set the driver and wrapped meshes without initializing. Note that the driver mesh must contain triangles only. Note that this does NOT re-initialize the other internals of the class and can be used as a means to (re)set the meshes if they have been stored separately from the class
- L63 _public prototype_ `void Init(const WrapDeformerParams<T>& params);` — initialize the deformer from parameters. The driver and wrapped meshes must have been set already.
- L66 _public prototype_ `void Init(const std::shared_ptr<const Mesh<T>>& driverMesh, const std::shared_ptr<const Mesh<T>>& wrappedMesh, const WrapDeformerParams<T>& params);` — initialize the deformer from the driver mesh, the wrapped mesh, and parameters. Note that the driver mesh must contain triangles only, and if specified, wrappedMeshIndicesToApplyTo must be in range
- L73 _public prototype_ `void Deform(const Eigen::Matrix<T, 3, -1>& deformedDriverMeshVertices, Eigen::Matrix<T, 3, -1>& deformedWrappedMeshVertices) const;` — apply the deformer to the driver mesh vertices to give deformedWrappedMeshVertices as a result; deformedDriverMeshVertices must contain the correct number of vertices. Note that if you have specified wrappedMeshIndicesToApplyTo, if the input deformedWrappedMeshVertices contains vertices and is of the correct size, any vertices not specified in wrappedMeshIndicesToApplyTo will be set to the values of those in deformedWrappedMeshVertices
- L78 _public prototype_ `void GetDriverMeshClosestPointBarycentricCoordinates(std::vector<BarycentricCoordinates<T>>& driverMeshClosestPointBarycentricCoordinates) const;` — once initialized, get the barycentric coordinates of the closest point on the driver mesh to each point on the wrapped mesh ie the highest weighted in the wrap deformer
- L80 _public prototype_ `const WrapDeformerParams<T>& Params() const;`
- L92 _private member_ `static constexpr int32_t m_version = 2;`
- L93 _private member_ `std::shared_ptr<const Mesh<T>> m_driverMesh;`
- L94 _private member_ `std::shared_ptr<const Mesh<T>> m_wrappedMesh;`
- L95 _private member_ `std::vector<std::vector<ClosestPointData<T>>> m_driverMeshCorrespondenceClosestPointData;`
- L96 _private member_ `WrapDeformerParams<T> m_wrappingParams;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace trio`
- L100 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const WrapDeformerParams<T>& params);`
- L103 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, WrapDeformerParams<T>& params);`
- L106 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const WrapDeformer<T>& wrapDeformer);`
- L109 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, WrapDeformer<T>& wrapDeformer);`
- L112 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, WrapDeformerParams<T>& params);`
- L115 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, WrapDeformer<T>& wrapDeformer);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/math/MKLWrapper.h` (Private)


#### Free symbols / members of external scopes

- L13 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::mkl)`
- L23 _prototype_ `template <class T, int Options> void CreateEigenSparseMatrix(sparse_matrix_t mklA, Eigen::SparseMatrix<T, Options>& A);` — Creates an Eigen Sparse matrix from an MKL sparse matrix.
- L27 _prototype_ `template <class T, int Options> void ComputeAtA(const Eigen::SparseMatrix<T, Options>& A, Eigen::SparseMatrix<T, Options>& AtA);` — Calculates AAt = A * A.transpose().
- L32 _prototype_ `template <class T, int Options> void ComputeAAt(const Eigen::SparseMatrix<T, Options>& A, Eigen::SparseMatrix<T, Options>& AAt);` — Calculates AAt = A * A.transpose().
- L39 _prototype_ `template <class T> void ComputeAAt_UpperOnly(const Eigen::SparseMatrix<T, Eigen::RowMajor>& A, Eigen::SparseMatrix<T, Eigen::RowMajor>& AAt);` — Calculates AAt for the upper triangular matrix only. Note that this is currently slower than ComputeAAt above, so for now this should be used.
- L46 _prototype_ `template <class T> void ComputeAtA_UpperOnly(const Eigen::SparseMatrix<T, Eigen::RowMajor>& A, Eigen::SparseMatrix<T, Eigen::RowMajor>& AtA);` — Calculates AtA for the upper triangular matrix only. Note that this is currently slower than ComputeAAt above, so for now this should be used.
- L50 _function_ `template <class T, int Options> void SparseMatrixMultiply(const Eigen::SparseMatrix<T, Options>& A, bool transposeA, const Eigen::SparseMatrix<T, Options>& B, bool transposeB, Eigen::SparseMatrix<T, Options>& C)` — Calculates the C = op(A) * op(B) where op() is transpose or none
- L97 _function_ `template <class T, int Options> void SparseMatrixReorder(Eigen::SparseMatrix<T, Options>& A)` — Reorders the inner dimension of the matrix so that the inner indices are in order

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/math/Math.h` (Private)


#### Free symbols / members of external scopes

- L13 _typedef_ `template <class T> using Vector = Eigen::Matrix<T, Eigen::Dynamic, 1>;`
- L16 _typedef_ `template <class T> using VectorPtr = std::shared_ptr<Vector<T>>;`
- L19 _typedef_ `template <class T> using VectorConstPtr = std::shared_ptr<const Vector<T>>;`
- L22 _typedef_ `template <class T> using SparseMatrix = Eigen::SparseMatrix<T, Eigen::RowMajor>;`
- L25 _typedef_ `template <class T> using SparseMatrixPtr = std::shared_ptr<SparseMatrix<T>>;`
- L28 _typedef_ `template <class T> using SparseMatrixConstPtr = std::shared_ptr<const SparseMatrix<T>>;`
- L32 _function_ `template <typename T> inline T random()` — basic implementation of a uniform random variable between 0 and 1
- L35 _function_ `template <typename T> inline T clamp(T value, T minValue, T maxValue)` — clamp value
- L43 _function_ `template <typename T> inline T clamped_acos(T value)` — acos ensuring that input is clamped to -1
- L61 _function_ `template <typename T> T cotangent(const Eigen::Vector3<T>& a, const Eigen::Vector3<T>& b)` — cotangent between vector a and b
- L69 _function_ `template <typename T> constexpr T rad2degreeScale()`
- L73 _function_ `template <typename T> T rad2degree(T deg)` — convert from radian to degree
- L77 _function_ `template <typename T> constexpr T degree2radScale()` — convert from degree to radian
- L80 _function_ `template <typename T> T degree2rad(T rad)`
- L82 _function_ `inline int RoundUp(int value, int multiple)`
- L88 _function_ `inline int RoundDown(int value, int multiple)`
- L92 _function_ `template <class T> static bool isIdentityMatrix(const SparseMatrix<T>& mat)` — @returns True if the sparse matrix is an identity matrix.
- L111 _function_ `template <class T> Eigen::Matrix<T, 3, 3> CrossProductMatrix(const Eigen::Vector<T, 3>& vec)` — Calculates the cross product matrix such that for the cross product c = a x b, we have c = CrossProductMatrix(a) * b CrossProductMatrix([x y z]^T) = |  0  -z   y  | |  z   0  -x  | | -y   x   0  |
- L135 _function_ `template <class T> SparseMatrix<T> AddSparseMatricesAndPadColumns(const SparseMatrix<T>& A, const SparseMatrix<T>& B, bool squeeze)` — Adds two compressed sparse CRS matrices. Both matrices need to have the same number of rows, but the columns may differ. In this case the output matrix will have the larger of the two column dimensions and the smaller of the two matrices is considered to be filled with zeros. A: (rows, cols_a) B: (rows, cols_b) output: (rows, max(cols_a, cols_b))
- L249 _function_ `template <class T> void RepeatRowsOfSparseMatrix(const SparseMatrix<T>& A, SparseMatrix<T>& output, int n)` — Create a new sparse matrix by repeating the rows of the input matrix @p n times output =  | A | | A | | ... | | A |
- L317 _function_ `template <class T> void ConcatenateSparseMatricesAlongRowDimension(const std::vector<std::reference_wrapper<const SparseMatrix<T>>>& inputs, SparseMatrix<T>& output)` — Concatenates a set of sparse matrices along the row dimension. Input matrices may be compressed or uncompressed, the output is always a compressed sparse matrix. Precondition: all input matrices need to be valid (no nullptr) and have the same number of cols.
- L404 _function_ `template <class T> SparseMatrix<T> RowGather(const SparseMatrix<T>& inSparse, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)` — Gathers rows from the sparse matrix. @param blockIndices  The indices indicate which rows to select from the sparse matrix. rowIndex = blockIdx * blockSize @param blockSize		The size of each row block i.e. for blockSize = 1, the blockIndices are equivalent to rowIndices.
- L462 _function_ `template <class T> SparseMatrix<T> RowScatter(const SparseMatrix<T>& inSparse, const int outputRows, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)` — Scatters rows from the sparse matrix. @param blockIndices  The indices indicate where each row of the input matrix is placed in the output matrix. @param blockSize		The size of each row block i.e. for blockSize = 1, the blockIndices are equivalent to rowIndices.
- L514 _function_ `template <class T> SparseMatrix<T> ColGather(const SparseMatrix<T>& inSparse, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)` — Gathers columns from the sparse matrix. @param blockIndices  The indices indicate which rows to select from the sparse matrix. rowIndex = blockIdx * blockSize @param blockSize		The size of each row block i.e. for blockSize = 1, the blockIndices are equivalent to rowIndices.
- L531 _function_ `template <class T> SparseMatrix<T> ColScatter(const SparseMatrix<T>& inSparse, const int outputCols, const Eigen::VectorX<int>& blockIndices, int blockSize = 1)` — Scatters rows from the sparse matrix. @param blockIndices  The indices indicate which rows to select from the sparse matrix. rowIndex = blockIdx * blockSize @param blockSize		The size of each row block i.e. for blockSize = 1, the blockIndices are equivalent to rowIndices.
- L547 _function_ `template <typename _Scalar, int _Options, typename _StorageIndex> void DiscardEmptyInnerDimensions(Eigen::SparseMatrix<_Scalar, _Options, _StorageIndex>& sparse, Eigen::Matrix<int, -1, 1>& indices)` — Removes the empty inner dimensions of a sparse matrix (removes empty rows for row major, and empty columns for column major), and outputs the indices of the old rows/columns to the new rows/columns.
- L605 _function_ `template <class T> void Dense2Sparse(const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& dense, SparseMatrix<T>& sparse, int rowOffset, int colOffset)` — Convert a dense matrix to a sparse matrix. As opposed to dense.sparseView() it keeps zero values in the matrix. @param colOffset  Offsets the dense matrix keeping the first colOffset colums of the sparse matrix empty
- L626 _function_ `template <class T> inline int NumNonzerosForRow(const SparseMatrix<T>& smat, int row)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/math/PCG.h` (Private)


#### class `PCG`  
`template <typename MatrixType> class PCG`  
_L16-116_
- desc: Preconditioned Conjugate Gradient that uses multi-threading for matrix vector multiplication. Only supports row-major matrices (both dense and sparse).
- L17 _private typedef_ `using T = typename MatrixType::Scalar;`
- L20 _public function_ `PCG(int size = 0, const std::shared_ptr<TaskThreadPool>& threadPool = TaskThreadPool::GlobalInstance(false)) : m_xrpqzc(size, 6) , m_threadPool(threadPool)`
- L27 _public function_ `Eigen::Ref<Eigen::VectorX<T>> Solve(int iterations, const MatrixType& A, const Eigen::VectorX<T>& rhs, const Eigen::VectorX<T>& xInit)` — Solve Ax = b
- L91 _public function_ `Eigen::Ref<Eigen::VectorX<T>> x()`
- L92 _public function_ `Eigen::Ref<Eigen::VectorX<T>> r()`
- L93 _public function_ `Eigen::Ref<Eigen::VectorX<T>> p()`
- L94 _public function_ `Eigen::Ref<Eigen::VectorX<T>> q()`
- L95 _public function_ `Eigen::Ref<Eigen::VectorX<T>> z()`
- L96 _public function_ `Eigen::Ref<Eigen::VectorX<T>> c()`
- L98 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> x() const`
- L99 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> r() const`
- L100 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> p() const`
- L101 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> q() const`
- L102 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> z() const`
- L103 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> c() const`
- L105 _public function_ `const T TolError() const`
- L106 _public function_ `const T ResError() const`
- L107 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> Result() const`
- L110 _private member_ `Eigen::Matrix<T, -1, 6> m_xrpqzc;`
- L112 _private member_ `T m_tolError{};`
- L113 _private member_ `T m_resError{};`
- L115 _private member_ `std::shared_ptr<TaskThreadPool> m_threadPool;`

#### class `ParallelPCG`  
`template <typename CGProblem> class ParallelPCG`  
_L131-259_
- desc: Class to solve a ConjugateGradient Problem where the matrix multiplication residual = rhs - A * x is calculated in multiple segments by a user provide CGProblem type i.e. residual = rhs - sum_i A[i] * x. As opposed @tparam CGProblem  Needs to define all functions to solve the conjugate gradient problem including - Rhs(); which returns the right-hand side of the problem residual = Rhs() - A x() - DiagonalPreconditioner(): the diagonal preconditioner for matrix A - NumSegments(): the number partial matrix multiplications - MatrixMultiply(): the partial multiplication A(i) * x, where A * x = sum_i A(i) x
- L132 _private typedef_ `using T = typename CGProblem::ScalarType;`
- L134 _public function_ `ParallelPCG(const std::shared_ptr<TaskThreadPool>& threadPool) : m_threadPool(threadPool)`
- L142 _public function_ `Eigen::Ref<Eigen::VectorX<T>> Solve(int iterations, const CGProblem& problem, const Eigen::VectorX<T>& xInit = Eigen::VectorX<T>())` — Solve Ax = b
- L233 _public function_ `Eigen::Ref<Eigen::VectorX<T>> x()`
- L234 _public function_ `Eigen::Ref<Eigen::VectorX<T>> r()`
- L235 _public function_ `Eigen::Ref<Eigen::VectorX<T>> p()`
- L236 _public function_ `Eigen::Ref<Eigen::VectorX<T>> z()`
- L237 _public function_ `Eigen::Ref<Eigen::VectorX<T>> c()`
- L239 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> x() const`
- L240 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> r() const`
- L241 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> p() const`
- L242 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> z() const`
- L243 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> c() const`
- L245 _public function_ `Eigen::Ref<Eigen::VectorX<T>> q(int i)`
- L246 _public function_ `Eigen::Ref<const Eigen::VectorX<T>> q(int i) const`
- L248 _public function_ `T TolError() const`
- L249 _public function_ `T ResidualError() const`
- L252 _private member_ `Eigen::Matrix<T, -1, 5> m_xrpzc;`
- L253 _private member_ `Eigen::Matrix<T, -1, -1> m_qs;`
- L255 _private member_ `T m_tolError;`
- L256 _private member_ `T m_resError;`
- L258 _private member_ `std::shared_ptr<TaskThreadPool> m_threadPool;`

#### Free symbols / members of external scopes

- L162 _function_ `taskFutures.Add(m_threadPool->AddTask(std::bind([&](int segmentId) { problem.MatrixMultiply(q(segmentId), segmentId, x()); }, i)));` (scope `ParallelPCG::Solve`)
- L203 _function_ `taskFutures.Add(m_threadPool->AddTask(std::bind([&](int segmentId) { problem.MatrixMultiply(q(segmentId), segmentId, p()); }, i)));` (scope `ParallelPCG::Solve`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/math/ParallelBLAS.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L19 _prototype_ `template <class T> void ParallelNoAliasGEMV(Eigen::Ref<Eigen::Matrix<T, -1, 1>, 0, Eigen::InnerStride<1>> out, const Eigen::SparseMatrix<T, Eigen::RowMajor>& A, const Eigen::Ref<const Eigen::Matrix<T, -1, 1>, 0, Eigen::InnerStride<1>>& x, TaskThreadPool* taskThreadPool);` — Method to calculate out = A * x for a sparse matrix with explicit multi-threading.
- L29 _prototype_ `template <class T> void ParallelNoAliasGEMV(Eigen::Ref<Eigen::Matrix<T, -1, 1>, 0, Eigen::InnerStride<1>> out, const Eigen::Ref<const Eigen::Matrix<T, -1, 1>, 0, Eigen::InnerStride<1>>& b, const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>, 0, Eigen::OuterStride<-1>>& A, const Eigen::Ref<const Eigen::Matrix<T, -1, 1>, 0, Eigen::InnerStride<1>>& x, TaskThreadPool* taskThreadPool);` — Method to calculate out = A * x + b with explicit multi-threading. It is only used in case MKL is not available, as MKL will perform multi-threading for matrix multiplication.
- L41 _prototype_ `template <class T> void ParallelAtALowerAdd(Eigen::Ref<Eigen::Matrix<T, -1, -1>> AtA, const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>, 0, Eigen::OuterStride<-1>>& A, TaskThreadPool* taskThreadPool);` — Method to calculate the lower triangular matrix of AtA with multi-threading. It is only used in case MKL is not available, as MKL will perform multi-threading for matrix multiplication. AtA.triangularView<Eigen::Lower>() += A.transpose() * A
- L51 _prototype_ `template <class T> void ParallelAtALowerAdd(Eigen::Ref<Eigen::Matrix<T, -1, -1>> AtA, const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>, 0, Eigen::OuterStride<-1>>& A, T scale, TaskThreadPool* taskThreadPool);` — Method to calculate the lower triangular matrix of scaled AtA with multi-threading. It is only used in case MKL is not available, as MKL will perform multi-threading for matrix multiplication. AtA.triangularView<Eigen::Lower>() += scale * A.transpose() * A
- L62 _prototype_ `template <class T> void ParallelAtALower(Eigen::Ref<Eigen::Matrix<T, -1, -1>> AtA, const Eigen::Ref<const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>, 0, Eigen::OuterStride<-1>>& A, TaskThreadPool* taskThreadPool);` — Method to calculate the lower triangular matrix of AtA with multi-threading. It is only used in case MKL is not available, as MKL will perform multi-threading for matrix multiplication. AtA.triangularView<Eigen::Lower>() = A.transpose() * A

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/math/SparseMatrixBuilder.h` (Private)


#### class `SparseMatrixInnerBuilder`  
`template <class T> class SparseMatrixInnerBuilder`  
_L17-78_
- desc: The SparseMatrixInnerBuilder class is used to incrementally build a sparse inner (row or column) vector by keeping track of the indexed data in an remapping vector and a separate row index and value vector. TODO: it might be faster to use a memset to clear the data once a certain fill factor has been reached
- L20 _public function_ `SparseMatrixInnerBuilder()`
- L24 _public function_ `void Init(int innerSize)` — Create an empty sparse inner vector of size @p innerSize
- L33 _public function_ `void Add(int innerIndex, T value)` — Add @p value at index @p innerIndex
- L51 _public function_ `int Size() const` — @return the number of elements in the sparse vector
- L57 _public function_ `void Clear()` — Clears the remapping by going though all current indices and setting them to -1
- L68 _public function_ `typename Eigen::VectorXi::ConstSegmentReturnType InnerIndices() const` — @return the inner indices
- L71 _public function_ `typename Eigen::VectorX<T>::ConstSegmentReturnType Values() const` — @return the values
- L74 _private member_ `int m_currentCounter = 0;`
- L75 _private member_ `Eigen::VectorXi m_indexMapping;`
- L76 _private member_ `Eigen::VectorXi m_innerIndices;`
- L77 _private member_ `Eigen::VectorX<T> m_values;`

#### class `SparseMatrixBuilder`  
`template <class T, int BLOCK_SIZE> class SparseMatrixBuilder`  
_L104-224_
- desc: The SparseMatrixBuilder class is used to incrementally build a sparse (row or column-major) matrix by filling @p BLOCK_SIZE rows or columns at a time. In the following we sparse inner vector to represent the block of rows or columns that are being filled. The builder can be used for either row or column major matrices, but the caller needs to make sure to use the corresponding outerIndex and innerIndex. Use it in the following way: SparseMatrixBuilder builder(M, N) for (int b = 0; b < M; b += BLOCK_SIZE) { StartBlock(b); // add arbitrary number of values using // Add(outerIndex, innerIndex, value)    where outerIndex needs to be b <= outerIndex < b + BLOCK_SIZE // ... FinalizeBlock(); } SparseMatrix<T> sMat; builder.Build(sMat); Note that the functionality is similar to Eigen::SparseMatrix::startVec(), ::insertBackByOuterInnerUnordered(), and ::finalize() but supports multiple rows at a time.
- L107 _public function_ `SparseMatrixBuilder(int outerSize, int innerSize, T allocationRatio = T(0.1))`
- L127 _public function_ `void StartBlock(int outerIndex)` — Start the next block of sparse inner vectors
- L140 _public function_ `void Add(int outerIndex, int innerIndex, T value)` — Add items to the current block of sparse vectors @pre m_currentOuterIndexStart <= outerIndex < m_currentOuterIndexStart + BLOCK_SIZE
- L157 _public function_ `void FinalizeBlock()` — Finalizes the current block of sparse inner vectors and copies the data to internal arrays.
- L190 _public function_ `template <int Options> void Build(Eigen::SparseMatrix<T, Options>& m)` — Builds an Eigen::SparseMatrix from the assembled sparse vector data.
- L210 _private member_ `int m_outerSize = 0;`
- L211 _private member_ `int m_innerSize = 0;`
- L212 _private member_ `int m_currentOuterIndexStart = 0;`
- L213 _private member_ `SparseMatrixInnerBuilder<T> m_innerBuilders[BLOCK_SIZE];`
- L215 _private member_ `bool m_blockInProgress = false;`
- L218 _private member_ `int m_allocationIncrement = 1;` — data for assembled matrix
- L219 _private member_ `int m_allocatedSize = 0;`
- L220 _private member_ `int m_currentSize = 0;`
- L221 _private member_ `Eigen::VectorXi m_outerIndices;`
- L222 _private member_ `Eigen::VectorXi m_innerIndices;`
- L223 _private member_ `Eigen::VectorX<T> m_values;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/math/SparseMatrixMultiply.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int Options> void SparseMatrixMultiply(const Eigen::SparseMatrix<T, Options>& A, bool transposeA, const Eigen::SparseMatrix<T, Options>& B, bool transposeB, Eigen::SparseMatrix<T, Options>& C)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/math/SparseMatrixReorder.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T, int Options> void SparseMatrixReorder(Eigen::SparseMatrix<T, Options>& A)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/rendering/Rasterizer.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> T OrientedArea2(const Eigen::Vector2<T> a, const Eigen::Vector2<T> b, const Eigen::Vector2<T> c)`
- L28 _function_ `template <class T> void RasterizeTriangleInsideOut(const Eigen::Matrix<T, 3, 3>& vertices, const Eigen::Matrix<T, 4, 3>& barycentricCoordinates, int width, int height, const std::function<void(int x, int y, T depth, const Eigen::Vector3<T>& bc)>& drawFunction)` — Rasterizes a triangle by traversing the bounding box and testing each pixel using an inside-out test. It assumes that (0,0) is the pixel-center of the top left corner. The reason is that triangle rasterization then works directly with integer coordinates. Depth and homogenous barycentric coordinates are interpolated linearly. Points that have depth outside the range (0, 1] are clipped.
- L108 _function_ `template <class T> void cullAndRasterizeTriangle(const Eigen::Matrix<T, 4, 3>& vertices, const int width, const int height, const std::function<void(int x, int y, T depth, const Eigen::Vector3<T>& bc)>& drawFunction)` — Rasterizes a triangle, but culls triangles that fall outside the view volume. The view volume is defined by x: [-1, 1] y: [-1, 1] z: [1, 0]  // reverse with 0 being the furthest depth @param vertices      The homogeneous vertex matrix (vertices are the columns of the matrix) @param width         The width of the output image @param height        The height of the output image @param drawFunction  For every rasterized pixel the drawFunction() is called with the pixel position (origin is center of top left pixel), the depth of the vertex [1, 0] and the perspectively correct interpolated barycentric coordinates.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/serialization/AffineSerialization.h` (Private)


#### Free symbols / members of external scopes

- L13 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L20 _function_ `template <class T, int R, int C> JsonElement ToJson(const std::vector<Affine<T, R, C>>& aff)`
- L32 _function_ `template <class T, int R, int C> void FromJson(const JsonElement& j, Affine<T, R, C>& aff)` — deserializes an affine matrix from json format
- L38 _function_ `template <class T, int R, int C> void FromJson(const JsonElement& j, std::vector<Affine<T, R, C>>& aff)`
- L51 _function_ `template <class T, int R, int C> bool ToBinaryFile(FILE* pFile, const Affine<T, R, C>& mat)` — Serializes an affine matrix to binary format
- L63 _function_ `template <class T, int R, int C> bool FromBinaryFile(FILE* pFile, Affine<T, R, C>& mat)` — Deserializes an affine matrix from binary format
- L83 _function_ `template <class T, int R, int C> bool FromBinaryFile(trio::BoundedIOStream* stream, Affine<T, R, C>& mat)` — Deserializes an affine matrix from binary format

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/serialization/BinarySerialization.h` (Private)


#### Free symbols / members of external scopes

- L16 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::io) template <class T> bool ToBinaryFile(FILE* pFile, const Eigen::SparseMatrix<T>& mat)`
- L45 _function_ `template <typename T> inline bool ToBinaryFile(FILE* pFile, const T& value, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0)`
- L51 _function_ `template <typename T> inline bool ToBinaryFile(FILE* pFile, const T& str, typename std::enable_if<std::is_same<T, std::string>::value, int>::type = 0)`
- L61 _function_ `template <class T, int R, int C> bool ToBinaryFile(FILE* pFile, const Eigen::Matrix<T, R, C>& mat)` — Serializes a column-major matrix to binary format
- L76 _prototype_ `template <typename S, typename T> inline bool ToBinaryFile(FILE* pFile, const std::map<S,T>& values);`
- L79 _prototype_ `template <typename T> bool ToBinaryFile(FILE* pFile, const Mesh<T>& mesh);`
- L82 _prototype_ `template <typename T> bool FromBinaryFile(FILE* pFile, Mesh<T>& mesh);`
- L85 _prototype_ `template <class T> inline bool ToBinaryFile(FILE* pFile, const std::shared_ptr<const Mesh<T>>& mesh);`
- L88 _prototype_ `template <class T> inline bool FromBinaryFile(FILE* pFile, std::shared_ptr<Mesh<T>>& mesh);`
- L91 _function_ `template <typename T> inline bool ToBinaryFile(FILE* pFile, const std::vector<T>& values, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0)`
- L99 _function_ `template <typename T> bool ToBinaryFile(FILE* pFile, const std::vector<T>& values, typename std::enable_if<!std::is_arithmetic<T>::value, int>::type = 0)`
- L110 _function_ `template <typename S, typename T> inline bool ToBinaryFile(FILE* pFile, const std::map<S,T>& values)`
- L123 _function_ `template <typename S, typename T> inline bool ToBinaryFile(FILE* pFile, const std::pair<S, T>& pair)`
- L135 _function_ `template <typename T> inline bool FromBinaryFile(FILE* pFile, T& value, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0)`
- L141 _function_ `template <typename T> bool FromBinaryFile(FILE* pFile, T& str, typename std::enable_if<std::is_same<T, std::string>::value, int>::type = 0)`
- L150 _function_ `template <class T> bool FromBinaryFile(FILE* pFile, Eigen::SparseMatrix<T>& mat)`
- L197 _function_ `template <class T, int R, int C> bool FromBinaryFile(FILE* pFile, Eigen::Matrix<T, R, C>& mat)` — Deserializes a column-major matrix from binary format
- L231 _prototype_ `template <typename S, typename T> inline bool FromBinaryFile(FILE* pFile, std::map<S,T>& values);`
- L234 _function_ `template <typename T> inline bool FromBinaryFile(FILE* pFile, std::vector<T>& values, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0)`
- L243 _function_ `template <typename T> bool FromBinaryFile(FILE* pFile, std::vector<T>& values, typename std::enable_if<!std::is_arithmetic<T>::value, int>::type = 0)`
- L256 _function_ `template <typename S, typename T> inline bool FromBinaryFile(FILE* pFile, std::map<S,T>& values)`
- L273 _function_ `template <typename S, typename T> inline bool FromBinaryFile(FILE* pFile, std::pair<S, T>& pair)`
- L289 _function_ `template <typename T> inline bool ReadAndCheckOrRevertFromBinaryFile(FILE* pFile, const T& expected)` — utility to read and check for a value, and revert in case the value is not valid
- L307 _function_ `template <typename T> bool ToBinaryFile(FILE* pFile, const Mesh<T>& mesh)`
- L322 _function_ `template <typename T> bool FromBinaryFile(FILE* pFile, Mesh<T>& mesh)`
- L347 _function_ `template <class T> inline bool ToBinaryFile(FILE* pFile, const std::shared_ptr<const Mesh<T>>& mesh)` — template specializations for serializing and deserializing shared ptrs to meshes
- L364 _function_ `template <class T> inline bool FromBinaryFile(FILE* pFile, std::shared_ptr<Mesh<T>>& mesh)`
- L391 _prototype_ `template <typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, T& value, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0);`
- L394 _prototype_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, T& str, typename std::enable_if<std::is_same<T, std::string>::value, int>::type = 0);`
- L397 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, Eigen::SparseMatrix<T>& mat);`
- L400 _prototype_ `template <class T, int R, int C> bool FromBinaryFile(trio::BoundedIOStream* stream, Eigen::Matrix<T, R, C>& mat);`
- L403 _prototype_ `template <typename S, typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::map<S, T>& values);`
- L406 _prototype_ `template <typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::vector<T>& values, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0);`
- L409 _prototype_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, std::vector<T>& values, typename std::enable_if<!std::is_arithmetic<T>::value, int>::type = 0);`
- L412 _prototype_ `template <typename S, typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::pair<S, T>& pair);`
- L415 _prototype_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, Mesh<T>& mesh);`
- L418 _prototype_ `template <class T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::shared_ptr<Mesh<T>>& mesh);`
- L421 _function_ `template <typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, T& value, typename std::enable_if<std::is_arithmetic<T>::value, int>::type)`
- L428 _function_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, T& str, typename std::enable_if<std::is_same<T, std::string>::value, int>::type)`
- L455 _function_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, Eigen::SparseMatrix<T>& mat)`
- L492 _function_ `template <class T, int R, int C> bool FromBinaryFile(trio::BoundedIOStream* stream, Eigen::Matrix<T, R, C>& mat)`
- L540 _function_ `template <typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::vector<T>& values, typename std::enable_if<std::is_arithmetic<T>::value, int>::type)`
- L567 _function_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, std::vector<T>& values, typename std::enable_if<!std::is_arithmetic<T>::value, int>::type)`
- L593 _function_ `template <typename S, typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::map<S, T>& values)`
- L627 _function_ `template <typename S, typename T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::pair<S, T>& pair)`
- L650 _function_ `template <typename T> bool FromBinaryFile(trio::BoundedIOStream* stream, Mesh<T>& mesh)`
- L675 _function_ `template <class T> inline bool FromBinaryFile(trio::BoundedIOStream* stream, std::shared_ptr<Mesh<T>>& mesh)`
- L705 _function_ `template <typename T> inline bool ReadAndCheckOrRevertFromBoundedIOStream(trio::BoundedIOStream* stream, const T& expected)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/serialization/CSVReader.h` (Private)


#### Free symbols / members of external scopes

- L14 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/serialization/CameraSerialization.h` (Private)


#### struct `RealityCaptureCamera`  
`template<class T> struct RealityCaptureCamera`  
_L32-41_
- desc: Reality Capture camera parameters as stored in XMP sidecar files.
- L33 _public member_ `Eigen::Matrix3<T> rotation;`
- L34 _public member_ `Eigen::Vector3<T> position;`
- L35 _public member_ `Eigen::VectorX<T> distortion;`
- L36 _public member_ `T focalLength35mm = T(0.0);`
- L37 _public member_ `T skew = T(0.0);`
- L38 _public member_ `T aspectRatio = T(0.0);`
- L39 _public member_ `T principalPointU = T(0.0);`
- L40 _public member_ `T principalPointV = T(0.0);`

#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> bool ReadMetaShapeCamerasFromJsonFile(const std::string& filename, std::vector<MetaShapeCamera<T>>& cameras);`
- L20 _prototype_ `template <class T> bool WriteMetaShapeCamerasToJsonFile(const std::string& filename, const std::vector<MetaShapeCamera<T>>& cameras);` — Writes camera calibration information into our own camera json format.
- L26 _prototype_ `template<class T> bool WriteMetaShapeCamerasToXmpFolder(const std::string& folderPath, const std::vector<MetaShapeCamera<T>>& cameras, int type);` — Writes camera calibration information into xmp format.
- L47 _prototype_ `template <class T> RealityCaptureCamera<T> ParseRealityCaptureXmp(const std::string& path);` — Parses a Reality Capture XMP sidecar file into a RealityCaptureCamera.
- L53 _prototype_ `template<typename T> MetaShapeCamera<T> RealityCaptureToMetashapeCamera(T width, T height, const RealityCaptureCamera<T>& rc);` — Converts a RealityCaptureCamera to a MetaShapeCamera given the image dimensions.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/serialization/EigenSerialization.h` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::io) /** * Serializes an Eigen matrix mat to json format in column major format. * Vectors are serialized to an array [values...] * Matrices are serialized to`
- L55 _function_ `template <class T, int R, int C> void FromJson(const JsonElement& j, Eigen::Matrix<T, R, C>& mat)` — deserializes a matrix from json format (see @ToJson)
- L110 _function_ `template <class MatrixType> MatrixType FromJson(const JsonElement& j)` — Serializes a matrix to json format.

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/serialization/GeometrySerialization.h` (Private)


#### Free symbols / members of external scopes

- L9 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) /** * Serializes vertices to a json dictionary`
- L25 _function_ `template <class T> void GeometryFromJson(const JsonElement& j, Eigen::Matrix<T, 3, Eigen::Dynamic>& vertices)` — Deserializes vertices from a json dictionary { “vertices” : 3xN matrix }
- L39 _function_ `template <class T> void MultiGeometryFromJson(const JsonElement& j, std::map<std::string, Eigen::Matrix<T, 3, Eigen::Dynamic>>& geometryMap)` — Deserializes multiple geometries { “geometry” : { “name of geometry” : { “vertices” : 3xN matrix }, ... } }
- L51 _function_ `template <class T> void MultiGeometryFromJson(const JsonElement& j, std::vector<Eigen::Matrix<T, 3, Eigen::Dynamic>>& geometryMap)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/serialization/MeshSerialization.h` (Private)


#### Free symbols / members of external scopes

- L14 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) /** * Serializes a mesh into a json dictionary`
- L90 _function_ `template <class T> void MeshFromJson(const JsonElement& j, Mesh<T>& mesh)` — Deserializes a mesh from a json dictionary. @see MeshToJson

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/serialization/MetaShapeSerialization.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> bool ReadMetaShapeCameras(const std::string& filename, std::vector<MetaShapeCamera<T>>& cameras, const Affine<T, 3, 3>& metashapeToWorldTransform, const T metashapeToWorldScale);`
- L26 _prototype_ `template <class T> bool WriteMetaShapeCameras(const std::string& filename, const std::vector<MetaShapeCamera<T>>& cameras);` — Writes the metashape cameras to a cameras.xml file in Agisoft Metashape format. Writes out one sensor per camera even if two or more cameras have the same intrinsics and distortion parameters.
- L35 _prototype_ `template <class T> bool ReadStabilizationFile(const std::string& filename, Affine<T, 3, 3>& transform, T& scale);` — Reads our custom formst stabilization file that describes the transformation from metashape to world coordinates. The stabilisation file has the info as tx, ty, tz, rx, ry, rz, sx, sy, sz in Maya convention (rotations in degrees, xyz order, scale should be uniform). The transformation from metashape to world is therefore: P_world = EulerZ(rx) * EulerY(ry) * EulerX(rx) * sx * P_metashape + (tx, ty, tz)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/serialization/ObjFileFormat.h` (Private)


#### class `ObjFileReader`  
`template <class T> class ObjFileReader`  
_L22-38_
- L25 _public prototype_ `static bool readObj(const std::string& fileName, Mesh<T>& mesh, const std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool>& taskThreadPool = TITAN_NAMESPACE::TaskThreadPool::GlobalInstance( false));`
- L28 _public prototype_ `static bool readObjFromString(const std::string& data, Mesh<T>& mesh, const std::shared_ptr<TITAN_NAMESPACE::TaskThreadPool>& taskThreadPool = TITAN_NAMESPACE::TaskThreadPool::GlobalInstance( false));`
- L37 _public prototype_ `static const char* ErrorTypeToString(ErrorType errorType);`

#### enum `ObjFileReader::ErrorType`  
`enum class ErrorType`  
_L32-35_
- L34 _public enumerator_ `NONE`
- L34 _public enumerator_ `NONE`
- L34 _public enumerator_ `NONE`
- L34 _public enumerator_ `NONE`
- L34 _public enumerator_ `NONE`
- L34 _public enumerator_ `NONE`

#### class `ObjFileWriter`  
`template <class T> class ObjFileWriter`  
_L42-46_
- L45 _public prototype_ `static void writeObj(const Mesh<T>& mesh, const std::string& filename, bool withTexture = true, bool withNormals = false);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/serialization/QsaSerialization.h` (Private)


#### Free symbols / members of external scopes

- L17 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> inline bool LoadQsa(const std::string& filename, std::map<int, std::map<std::string, T>>& valuesPerFrameAndControl)`
- L56 _function_ `template <class T> inline bool WriteQsa(const std::string& filename, const std::vector<std::string>& guiControlNames, const std::vector<Eigen::VectorX<T>>& guiControls, const std::vector<int>& frameNumbers, bool exportControlsThatAreAlwaysZero = true)`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/solver/BoundedCoordinateDescentSolver.h` (Private)


#### struct `BoundedCoordinateDescentSolverSettings`  
`template <class T> struct BoundedCoordinateDescentSolverSettings`  
_L15-23_
- L17 _public member_ `int iterations = 10;`
- L18 _public member_ `int coordinateDescentIterations = 100;`
- L19 _public member_ `int maxLineSearchIterations = 10;`
- L20 _public member_ `T l1reg = 0;`
- L21 _public member_ `bool useSaturatedL1 = false;`
- L22 _public member_ `T saturatedL1_m = 2;`

#### class `BoundedCoordinateDescentSolver`  
`template <class T> class BoundedCoordinateDescentSolver`  
_L34-73_
- desc: Special coordinate descent solver with bounds and L1 regularization i.e. LASSO with box constraints. see also https://www.stat.cmu.edu/~ryantibs/convexopt-S15/lectures/22-coord-desc.pdf. https://www.jstatsoft.org/article/view/v033i01/v33i01.pdf Used to solve the function: min 1/2 || evaluationFunction() ||_2^2 + sum_i | l1Reg boundedVectorVariable_i |_1 (optionally using saturated L1)
- L44 _public prototype_ `static bool SolveCostFunction(const std::function<Cost<T>(Context<T>*)>& costFunction, Context<T>& context, const std::vector<BoundedVectorVariable<T>*>& boundedVectorVariables, const BoundedCoordinateDescentSolverSettings<T>& settings, TaskThreadPool* threadPool);` — Run the solve on the cost function with additional L1 regularization. @param costFunction            The least squares evaluation function. @param context                             The context that maps variables to the columns of the Jacobian of the evaluation function @param boundedVectorVariables  A set of vector variable for which the bounds are applied. The costFunction needs to use these bounded variables. @param settings				  The settings for the solver.
- L51 _public prototype_ `static T EvaluateCostFunction(const std::function<Cost<T>(Context<T>*)>& costFunction, const std::vector<BoundedVectorVariable<T>*>& boundedVectorVariables, const BoundedCoordinateDescentSolverSettings<T>& settings);` — Evaluate the total energy for the function: 1/2 || costFunction() ||_2^2 + sum_i | l1Reg boundedVectorVariable_i |_1 (optionally using saturated L1)
- L62 _public prototype_ `static bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, Context<T>& context, const std::vector<BoundedVectorVariable<T>*>& boundedVectorVariables, const BoundedCoordinateDescentSolverSettings<T>& settings, TaskThreadPool* threadPool);` — Run the solve on the evaluation function with additional L1 regularization. @param evaluationFunction      The least squares evaluation function. @param context                             The context that maps variables to the columns of the Jacobian of the evaluation function @param boundedVectorVariables  A set of vector variable for which the bounds are applied. The evaluationFunction needs to use these bounded variables. @param settings				  The settings for the solver.
- L70 _public prototype_ `static T Evaluate(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, const std::vector<BoundedVectorVariable<T>*>& boundedVectorVariables, const BoundedCoordinateDescentSolverSettings<T>& settings);` — Evaluate the total energy for the function: 1/2 || evaluationFunction() ||_2^2 + sum_i | l1Reg boundedVectorVariable_i |_1 (optionally using saturated L1)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/solver/GaussNewtonSolver.h` (Private)


#### class `GaussNewtonSolver`  
`template <class T> class GaussNewtonSolver`  
_L17-81_
- L32 _public prototype_ `GaussNewtonSolver() = default;`
- L34 _public function_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, int iterations = 1, T reg = DiagonalRegularization<T>()) const`
- L40 _public function_ `bool Solve(const std::function<DiffData<T>(Context<T> *)> &evaluationFunction, const Settings &settings) const`
- L46 _public function_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, Context<T>& context, int iterations = 1, T reg = DiagonalRegularization<T>()) const`
- L55 _public prototype_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, Context<T>& context, const Settings& settings) const;`
- L57 _public function_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& evaluationFunction, int iterations = 1, T reg = DiagonalRegularization<T>()) const`
- L63 _public function_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& evaluationFunction, const Settings& settings) const`
- L69 _public function_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& evaluationFunction, Context<T>& context, int iterations = 1, T reg = DiagonalRegularization<T>()) const`
- L78 _public prototype_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& evaluationFunction, Context<T>& context, const Settings& settings) const;`

#### struct `GaussNewtonSolver::Settings`  
`struct Settings`  
_L20-30_
- L22 _public member_ `int iterations = 1;`
- L23 _public member_ `T reg = DiagonalRegularization<T>();`
- L24 _public member_ `int cgIterations = 200;` — the number of cg iterations (if pcg is used)
- L25 _public member_ `int maxLineSearchIterations = 10;`
- L26 _public member_ `T residualErrorStoppingCriterion = ResidualErrorStoppingCriterion<T>();`
- L27 _public member_ `T predictionReductionStoppingCriterion = PredictionReductionErrorStoppingCriterion<T>();`
- L28 _public member_ `bool optimizeForRectangularDenseJacobian = false;`
- L29 _public member_ `bool useDenseJtJAccumulation = true;`

#### Free symbols / members of external scopes

- L10 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> T DiagonalRegularization();`
- L13 _prototype_ `template <class T> T DiagonalRegularization();`
- L14 _prototype_ `template <class T> T DiagonalRegularization();`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/solver/LBFGSSolver.h` (Private)


#### class `LBFGSSolver`  
`template <class T> class LBFGSSolver`  
_L12-60_
- L15 _public function_ `LBFGSSolver()`
- L24 _public function_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, int iterations = 1) const`
- L31 _public prototype_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, Context<T>& context, int iterations = 1) const;`
- L36 _public function_ `void SetResidualErrorStoppingCriterion(T value)` — Setter methods for stopping criteria
- L37 _public function_ `void SetPredictionReductionStoppingCriterion(T value)`
- L38 _public function_ `void SetAbsDeltaStoppingCriterion(T value)`
- L39 _public function_ `void SetAbsDeltaStoppingWindow(int value)`
- L42 _public function_ `T GetResidualErrorStoppingCriterion() const` — Getter methods for stopping criteria
- L43 _public function_ `T GetPredictionReductionStoppingCriterion() const`
- L44 _public function_ `T GetAbsDeltaStoppingCriterion() const`
- L45 _public function_ `int GetAbsDeltaStoppingWindow() const`
- L49 _private member_ `int historySize = 50;` — LBFGS storage
- L50 _private member_ `mutable std::vector<Vector<T>> s;`
- L51 _private member_ `mutable std::vector<Vector<T>> y;`
- L52 _private member_ `mutable Vector<T> p;`
- L53 _private member_ `mutable Vector<T> a;`
- L56 _private member_ `T residualErrorStoppingCriterion = T(1e-8);` — Stopping criteria
- L57 _private member_ `T predictionReductionStoppingCriterion = T(1e-6);`
- L58 _private member_ `T absDeltaStoppingCriterion = T(0);` — disabled by default
- L59 _private member_ `int absDeltaStoppingWindow = 1;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/solver/LMSolver.h` (Private)


#### class `LMSolver`  
`template <class T> class LMSolver`  
_L12-33_
- L15 _public prototype_ `LMSolver() = default;`
- L19 _public function_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, int iterations = 1, const T epsilon1 = T(1e-8), const T epsilon2 = T(1e-8)) const` — epsilon1: stopping criterion for gradient norm epsilon2: stopping criterion for step size
- L28 _public prototype_ `bool Solve(const std::function<DiffData<T>(Context<T>*)>& evaluationFunction, Context<T>& context, const int iterations = 1, const T epsilon1 = T(1e-8), const T epsilon2 = T(1e-8)) const;` — epsilon1: stopping criterion for gradient norm epsilon2: stopping criterion for step size

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/solver/SimpleGaussNewtonSolver.h` (Private)


#### class `SimpleGaussNewtonSolver`  
`template <class T> class SimpleGaussNewtonSolver`  
_L13-40_
- L16 _public prototype_ `SimpleGaussNewtonSolver() = default;`
- L20 _public function_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& costFunction, int iterations, const T regularization,` — epsilon1: stopping criterion for gradient norm epsilon2: stopping criterion for step size
- L33 _public prototype_ `bool Solve(const std::function<Cost<T>(Context<T>*)>& costFunction, Context<T>& context, const int iterations, const T regularization,` — epsilon1: stopping criterion for gradient norm epsilon2: stopping criterion for step size

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/utils/BilateralFilter.h` (Private)


#### class `BilateralFilter`  
`class BilateralFilter`  
_L9-22_
- L12 _public prototype_ `BilateralFilter() = delete;`
- L13 _public prototype_ `static std::vector<Eigen::VectorXf> CorrelatedFilter(const std::vector<Eigen::VectorXf>& InUnfilteredControls, const float& InDomainStdDev, const float& InRangeStdDev);`
- L16 _public prototype_ `static std::vector<Eigen::VectorXf> IndependentFilter(const std::vector<Eigen::VectorXf>& InUnfilteredControls, const float& InDomainStdDev, const float& InRangeStdDev);`
- L21 _private prototype_ `static std::vector<float> CreateGaussianFilter(const long long& half_width, const float& InDomainStdDev);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/utils/Configuration.h` (Private)


#### class `Configuration`  
`class Configuration`  
_L16-63_
- L18 _public prototype_ `Configuration(const std::string& configName, const std::vector<std::pair<std::string, ConfigurationParameter> >& configParameters);`
- L21 _public prototype_ `void Set(const Configuration& other, bool ignoreUnknownKeys = false);`
- L23 _public prototype_ `std::map<std::string, std::string> StringConfiguration() const;`
- L24 _public prototype_ `void SetStringConfiguration(const std::map<std::string, std::string>& config, bool ignoreUnknownKeys = false);`
- L26 _public prototype_ `bool HasParameter(const std::string& name) const;`
- L28 _public prototype_ `const ConfigurationParameter& operator[](const std::string& name) const;`
- L29 _public prototype_ `ConfigurationParameter& operator[](const std::string& name);`
- L31 _public prototype_ `const std::map<std::string, ConfigurationParameter>& Parameters() const;`
- L32 _public prototype_ `std::map<std::string, ConfigurationParameter>& Parameters();`
- L34 _public prototype_ `const std::string& Name() const;`
- L36 _public prototype_ `void AddParameter(const std::string& key, ConfigurationParameter&& value);`
- L37 _public prototype_ `void AddConfiguration(const std::string& key, const Configuration& config);`
- L38 _public prototype_ `void AddConfiguration(const Configuration& config);`
- L39 _public prototype_ `void AddConfigurations(const std::vector<Configuration>& configs);`
- L41 _public prototype_ `JsonElement ToJson() const;`
- L43 _public prototype_ `void FromJson(const JsonElement& json, std::vector<std::string>& unspecifiedKeys, std::vector<std::string>& unknownKeys);`
- L48 _public function_ `const std::vector<std::string>& ParameterOrder()` — @returns the order in which the parameters were added to the configuration
- L53 _private prototype_ `void FromJson(const JsonElement& json, std::vector<std::string>& unspecifiedKeys, std::vector<std::string>& unknownKeys, const std::string& prefix);`
- L59 _private member_ `std::string m_configName;`
- L60 _private member_ `std::map<std::string, ConfigurationParameter> m_configParameters;`
- L62 _private member_ `std::vector<std::string> m_paramOrder;` — keep the order of the keys as they have been added

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/nls/include/nls/utils/ConfigurationParameter.h` (Private)


#### class `ConfigurationParameter`  
`class ConfigurationParameter`  
_L81-255_
- L88 _public function_ `ConfigurationParameter() : m_value(int(0)), m_rangeStart(int(0)), m_rangeEnd(int(0))`
- L96 _public function_ `explicit ConfigurationParameter(bool value) : m_value(value), m_rangeStart(int(0)), m_rangeEnd(int(0))`
- L99 _public function_ `explicit ConfigurationParameter(int value, int rangeStart = 0, int rangeEnd = 1) : m_value(value), m_rangeStart(rangeStart), m_rangeEnd(rangeEnd)`
- L102 _public function_ `explicit ConfigurationParameter(float value, float rangeStart = 0.0f, float rangeEnd = 1.0f) : m_value(value), m_rangeStart(rangeStart), m_rangeEnd(rangeEnd)`
- L106 _public function_ `explicit ConfigurationParameter(double value, double rangeStart = 0.0, double rangeEnd = 1.0) : m_value(value), m_rangeStart(rangeStart), m_rangeEnd( rangeEnd)`
- L110 _public function_ `explicit ConfigurationParameter(const std::string& value) : m_value(value), m_rangeStart(int(0)), m_rangeEnd(int(0))`
- L113 _public function_ `explicit ConfigurationParameter(const char* value) : ConfigurationParameter(std::string(value))`
- L116 _public function_ `explicit ConfigurationParameter(Configuration value) : m_value(value), m_rangeStart(int(0)), m_rangeEnd(int(0))`
- L119 _public function_ `void Set(const std::string& value)`
- L161 _public function_ `void Set(float value)`
- L168 _public function_ `void Set(double value)`
- L175 _public function_ `void Set(int value)`
- L181 _public function_ `void Set(bool value)`
- L188 _public function_ `template <class T> const T& Value() const`
- L194 _public function_ `template <class T> T& Value()`
- L210 _public function_ `template <class T> ConfigurationParameter& operator=(const T& v)`
- L213 _public function_ `std::string AsString() const` — @returns String representation of the underlying value. It does not support the Configuration type.
- L216 _public function_ `template <class T> std::pair<T, T> Range() const`
- L219 _public function_ `template <class T> bool IsType() const`
- L221 _public function_ `ConfigurationParameter& operator[](const std::string& name)`
- L227 _public function_ `const ConfigurationParameter& operator[](const std::string& name) const`
- L233 _public function_ `ConfigurationParameter& operator[](const char* name)`
- L239 _public function_ `const ConfigurationParameter& operator[](const char* name) const`
- L247 _private member_ `std::string m_name;` — the parameter name
- L250 _private member_ `detail::ConfigurationParameterVariant m_value;` — the parameter value
- L253 _private member_ `std::variant<int, float, double> m_rangeStart;` — the range of the parameter value in [m_rangeStart, m_rangeEnd]. Note that the end of the range is included.
- L254 _private member_ `std::variant<int, float, double> m_rangeEnd;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace detail`
- L18 _typedef_ `typedef std::variant<bool, int, float, double, std::string, Configuration> ConfigurationParameterVariant;` (scope `detail`)
- L20 _function_ `template <typename T> inline bool IsType(const ConfigurationParameterVariant& value)` (scope `detail`)
- L22 _function_ `template <typename T> inline T& Value(ConfigurationParameterVariant& value)` (scope `detail`)
- L32 _function_ `template <typename T> inline const T& Value(const ConfigurationParameterVariant& value)` (scope `detail`)
- L42 _function_ `inline std::string AsString(const ConfigurationParameterVariant& value)` (scope `detail`)
- L44 _function_ `return std::visit([](auto&& arg) { using T = std::decay_t<decltype(arg)>; if constexpr (std::is_same_v<T, int> ) { return std::to_string(arg); } else if constexpr (std::is_same_v<T, float> ) { return std::to_string(arg); } else if constexpr (std::is_same_v<T, double> ) { return std::to_string(arg); } else if constexpr (std::is_same_v<T, bool> ) { return std::string(arg ? "True" : "False"); } else if constexpr (std::is_same_v<T, std::string> ) { return arg; } else if constexpr (std::is_same_v<T, Configuration> ) { static_assert("cannot retrieve sub configuration as string"); return std::string(); } else { static_assert(TITAN_NAMESPACE::always_false<T>::value, "non-exhaustive visitor!"); return std::string(); } }, value);` (scope `detail::AsString`)
- L45 _typedef_ `using T = std::decay_t<decltype(arg)>;` (scope `detail::AsString::__anon36d32cfc0102`)
- L190 _typedef_ `using base_type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;` (scope `ConfigurationParameter::Value`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/resourceloader/include/resourceloader/IMetaHumanFileResourceLoader.h` (Private)


#### class `IMetaHumanFileResourceLoader`  
`class IMetaHumanFileResourceLoader`  
_L11-33_
- L14 _public prototype_ `virtual ~IMetaHumanFileResourceLoader() = default;`
- L17 _public prototype_ `virtual bool Exists(const char* InPathUtf8) const = 0;` — Check if a path (UTF-8) exists.
- L20 _public prototype_ `virtual bool ReadAllText(const char* InPathUtf8, char*& OutData, std::size_t& OutSize) const = 0;` — Read text file as raw UTF-8 bytes. Allocates a buffer that has to be freed
- L23 _public prototype_ `virtual bool ReadAllBytes(const char* InPathUtf8, void*& OutData, std::size_t& OutSize) const = 0;` — /  Read binary file as raw bytes. Allocates a buffer that has to be freed
- L26 _public prototype_ `virtual void Free(const void* InPtr) const = 0;` — Release any pointer previously returned via Read / Resolve functions
- L31 _public prototype_ `virtual bool ResolveDataLoadingPath(const char* InBasePathUtf8, const std::size_t& InBaseSize, const char* InAppendPathUtf8, std::size_t& InAppendSize, char*& OutPathUtf8, std::size_t& OutSize) const = 0;` — Constructs a valid path for data that could be loaded based on the resource loader type. Allocates a buffer that has to be freed. Expects a null terminated base and appended input

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/resourceloader/include/resourceloader/MetaHumanFileResourceLoader.h` (Private)


#### class `FMetaHumanFileResourceLoader`  
`class FMetaHumanFileResourceLoader : public IMetaHumanFileResourceLoader`  
_L16-59_
- inherits: `IMetaHumanFileResourceLoader`
- L20 _public prototype_ `virtual bool Exists(const char* InPathUtf8) const override;` — IMetaHumanFileResourceLoader
- L21 _public prototype_ `virtual bool ReadAllText(const char* InPathUtf8, char*& OutData, std::size_t& OutSize) const override;`
- L22 _public prototype_ `virtual bool ReadAllBytes(const char* InPathUtf8, void*& OutData, std::size_t& OutSize) const override;`
- L23 _public prototype_ `virtual void Free(const void* InPtr) const override;`
- L24 _public prototype_ `virtual bool ResolveDataLoadingPath(const char* InBasePathUtf8, const std::size_t& InBaseSize, const char* InAppendPathUtf8, std::size_t& InAppendSize, char*& OutPathUtf8, std::size_t& OutSize) const override;`
- L28 _public prototype_ `static TITAN_NAMESPACE::JsonElement GetJsonElementForFile(const std::string& InFilePath);` — Reads the json data based on static IResourceLoader implementation of ReadAllText override and returns json element
- L31 _public prototype_ `static std::string GetResolvedPathForFile(const std::string& InBasePathUtf8, const std::string& InAppendPathUtf8);` — Appends the paths based on the corresponding implementation of static IResourceLoader
- L34 _public prototype_ `static bool ResourceExists(const std::string& InResourcePathUtf8);` — A convenience function that wraps around the overriden Exists function for static IResourceLoader
- L50 _public typedef_ `using BoundedStreamPtr = pma::ScopedPtr<::trio::BoundedIOStream, BoundedDestroy>;` — Unified smart pointer type that contains deleter
- L53 _public prototype_ `static BoundedStreamPtr GetBoundedIOStreamFromFile(const std::string& InFilePath, bool bForceMemoryStream = false);` — A convenience function that returns File or Memory based IO stream for input binary file. Or nullptr if failed
- L58 _private prototype_ `static std::string ToStdString(const char* InData, std::size_t InSize);` — Copies raw UTF-8 (InData/InSize) into std::string.

#### struct `FMetaHumanFileResourceLoader::BoundedDestroy`  
`struct BoundedDestroy`  
_L37-47_
- desc: Type-erased deleter that can call either FileStream::destroy or MemoryStream::destroy
- L39 _public typedef_ `using Fn = void (*)(trio::BoundedIOStream*);`
- L40 _public member_ `Fn fn { nullptr };`
- L42 _public function_ `void operator()(trio::BoundedIOStream* p)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace trio`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/resourceloader/include/resourceloader/MetaHumanResourceLoaderHub.h` (Private)


#### class `FMetaHumanResourceLoaderHub`  
`class FMetaHumanResourceLoaderHub`  
_L9-26_
- L13 _public prototype_ `static void Install(IMetaHumanFileResourceLoader* InResourceLoader);` — Install a process-wide loader for the singleton
- L16 _public prototype_ `static IMetaHumanFileResourceLoader& GetResourceLoader();` — Access the active loader. Never null.
- L19 _private prototype_ `FMetaHumanResourceLoaderHub() = default;`
- L20 _private prototype_ `FMetaHumanResourceLoaderHub(const FMetaHumanResourceLoaderHub&) = delete;`
- L21 _private prototype_ `FMetaHumanResourceLoaderHub& operator=(const FMetaHumanResourceLoaderHub&) = delete;`
- L23 _private prototype_ `static IMetaHumanFileResourceLoader& FallbackFileLoader();`
- L25 _private member_ `static IMetaHumanFileResourceLoader* ResourceLoader;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/BarycentricCoordinatesForOddLods.h` (Private)


#### class `BarycentricCoordinatesForOddLods`  
`template <class T> class BarycentricCoordinatesForOddLods`  
_L17-51_
- desc: Simple class for representing the barycentric coordinates for the head mesh for odd lods which are calculated relative to the previous lod head mesh
- L20 _public prototype_ `BarycentricCoordinatesForOddLods() = default;`
- L26 _public prototype_ `void Init(const RigGeometry<T>& headRigGeometry);` — initialise the class from the supplied (head) rigGeometry. @param[in] rigGeometry: the rig geometry for the head rig.
- L29 _public prototype_ `bool ReadJson(const JsonElement& json);` — Read data from json element
- L32 _public prototype_ `void WriteJson(JsonElement& json) const;` — Write the BarycentricCoordinatesForOddLods to Json
- L39 _public prototype_ `bool IsValidForRig(const RigGeometry<T>& faceRigGeometry) const;` — Check if the confifg is valid for the supplied face rig. Returns true if it is valid, false if not. Checks that a set of barycentric coordinates is available for each odd lod, and that there are the correct number of barycentric coordinates for the current lod head mesh, and that the vertex indices for the bcs are in range for the previous lod head mesh
- L46 _public prototype_ `const std::map<int, std::vector<std::pair<bool, BarycentricCoordinates<T>>>>& GetBarycentricCoordinatesForOddLods() const;` — Get the map of mesh seam snap configs for each head mesh from combined body mesh to head mesh for each lod. Returns a map of (head) lod to a corresponding vector of pairs of boolean and BaryCentric coordinates, for each vertex in the current lod head mesh, how it maps onto the vertices of the previous lod, with the bool set to true to indicate a valid mapping and false to indicate an invalid mapping
- L50 _private member_ `std::map<int, std::vector<std::pair<bool, BarycentricCoordinates<T>>>> m_barycentricCoordinatesForOddLods;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/BindPoseJointsCalculation.h` (Private)


#### class `BindPoseJointsCalculation`  
`class BindPoseJointsCalculation`  
_L12-48_
- L15 _public prototype_ `BindPoseJointsCalculation();`
- L16 _public prototype_ `~BindPoseJointsCalculation();`
- L17 _public prototype_ `BindPoseJointsCalculation(BindPoseJointsCalculation&& o);`
- L18 _public prototype_ `BindPoseJointsCalculation(const BindPoseJointsCalculation& o) = delete;`
- L19 _public prototype_ `BindPoseJointsCalculation& operator=(BindPoseJointsCalculation&& o);`
- L20 _public prototype_ `BindPoseJointsCalculation& operator=(const BindPoseJointsCalculation& o) = delete;`
- L22 _public prototype_ `bool LoadVolumetricConfig(const std::string& filepath);`
- L23 _public prototype_ `bool LoadVolumetricJointsJson(const JsonElement& json);`
- L25 _public prototype_ `bool LoadSurfaceConfig(const std::string& filepath);`
- L26 _public prototype_ `bool LoadSurfaceJointsMapFromJson(const JsonElement& jsonData);`
- L28 _public prototype_ `bool Load(const std::string& surfaceJointsConfig, const std::string& volumetricJointsConfig);`
- L30 _public prototype_ `void UpdateVolumetric(Eigen::Matrix<float, 3, -1>& vertices, const std::map<std::string, std::pair<int, int>>& meshMapping, const std::map<std::string, int>& jointNameToId) const;`
- L34 _public prototype_ `void UpdateSurface(Eigen::Matrix<float, 3, -1>& vertices, const int jointOffset, const std::map<std::string, int>& jointNameToId) const;`
- L36 _public prototype_ `void Update(Eigen::Matrix<float, 3, -1>& vertices, const int jointOffset, const std::map<std::string, std::pair<int, int>>& meshMapping, const std::map<std::string, int>& jointNameToId) const;`
- L39 _public prototype_ `bool VolumetricDataLoaded() const;`
- L41 _public prototype_ `bool SurfaceDataLoaded() const;`
- L43 _public prototype_ `std::vector<std::string> SurfaceJointsList() const;`
- L47 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/BodyGeometry.h` (Private)


#### class `BodyGeometry`  
`template <class T> class BodyGeometry`  
_L20-149_
- desc: BodyGeometry implements the rig geometry evaluation based on rig logic inputs.
- L26 _public prototype_ `explicit BodyGeometry(const std::shared_ptr<TaskThreadPool>& taskThreadPool);`
- L27 _public prototype_ `explicit BodyGeometry(bool useMultithreading = true);`
- L28 _public prototype_ `BodyGeometry(int numLods, bool useMultithreading = true);`
- L29 _public prototype_ `~BodyGeometry() = default;`
- L30 _public prototype_ `BodyGeometry(BodyGeometry&&) = default;`
- L31 _public prototype_ `BodyGeometry(BodyGeometry&) = default;`
- L32 _public prototype_ `BodyGeometry& operator=(BodyGeometry&&) = default;`
- L33 _public prototype_ `BodyGeometry& operator=(const BodyGeometry&) = default;`
- L35 _public prototype_ `void SetThreadPool(const std::shared_ptr<TaskThreadPool>& taskThreadPool);`
- L37 _public prototype_ `std::shared_ptr<BodyGeometry> Clone() const;`
- L39 _public prototype_ `void SetNumLODs(const int l);`
- L40 _public prototype_ `int GetNumLODs() const;`
- L43 _public prototype_ `bool Init(const dna::Reader* reader, bool computeMeshNormals = false);` — Initializes BodyGeometry with the data from the dna::BinaryStreamReader
- L45 _public prototype_ `static Mesh<T> ReadMesh(const dna::Reader* reader, int meshIndex);` — Assembles the mesh at index @p meshIndex stored within dna::BinaryStreamReader
- L48 _public prototype_ `State EvaluateBodyGeometry(const int lod, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L51 _public prototype_ `State& EvaluateBodyGeometry(const int lod, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd, State& state) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L52 _public prototype_ `State& EvaluateIndexedBodyGeometry(const int lod, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd, const std::vector<int>& indices, State& state) const;`
- L53 _public prototype_ `State& EvaluateBodyGeometryWithOffset(const int lod, const DiffDataMatrix<T, 3, -1>& offset, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd, State& state) const;`
- L56 _public function_ `const Mesh<T>& GetMesh(const int lod) const` — @return the mesh
- L57 _public function_ `Mesh<T>& GetMesh(const int lod)`
- L60 _public function_ `int NumJoints() const` — get num components
- L61 _public function_ `int NumBlendshapes(int lod) const`
- L64 _public function_ `const std::vector<std::string>& GetJointNames() const` — get joint names
- L65 _public function_ `std::vector<std::string>& GetJointNames()`
- L68 _public prototype_ `int GetJointIndex(const std::string& jointName) const;` — get joint index by name
- L71 _public function_ `const Eigen::VectorXi& GetBlendshapeMap(const int lod) const` — get blendshape data
- L72 _public function_ `Eigen::VectorXi& GetBlendshapeMap(const int lod)`
- L73 _public function_ `const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& GetBlendshapeMatrix(const int lod) const`
- L74 _public function_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& GetBlendshapeMatrix(const int lod)`
- L77 _public function_ `const std::vector<int>& GetJointParentIndices() const` — get joint parent indices
- L78 _public function_ `std::vector<int>& GetJointParentIndices()`
- L79 _public prototype_ `int GetParentIndex(int jointIndex) const;`
- L82 _public function_ `const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& GetBindMatrices() const` — @return the current bind matrix of the joint rig.
- L84 _public function_ `const Eigen::Matrix3X<T>& GetJointRestPoses() const`
- L85 _public function_ `Eigen::Matrix3X<T>& GetJointRestPoses()`
- L87 _public function_ `const std::vector<Eigen::Matrix<T, 3, 3>>& GetJointRestOrientation() const`
- L88 _public function_ `std::vector<Eigen::Matrix<T, 3, 3>>& GetJointRestOrientation()`
- L90 _public function_ `const SparseMatrix<T>& GetVertexInfluenceWeights(const int lod) const`
- L91 _public function_ `SparseMatrix<T>& GetVertexInfluenceWeights(const int lod)`
- L93 _public prototype_ `void UpdateBindPoses();`
- L96 _public prototype_ `void EvaluateJointDeltas(const DiffData<T>& diffJoints, State& state, bool evaluateSkinningMatrices = true) const;` — Evaluates the joint deltas and stores it in @p state.
- L98 _public prototype_ `const Eigen::Matrix3X<T> EvaluateInverseSkinning(const int lod, const State& state, const Eigen::Matrix3X<T>& vertices);` — perform inverse skinning for a given state plus optional mesh
- L102 _private prototype_ `void EvaluateJointDeltasWithoutJacobians(const DiffData<T>& diffJoints, State& state) const;` — Evaluates the joint deltas and stores it in @p state.
- L105 _private prototype_ `const std::pair<Eigen::Matrix<T, 3, -1>, std::vector<Eigen::Matrix<T, 3, 3>>> EvaluateInverseJointDeltas(const DiffData<T>& diffJoints, const State& state) const;` — Get original joint rest poses from state and pose
- L114 _private prototype_ `void EvaluateBlendshapes(const int lod, const DiffData<T>& diffPsd, State& state) const;` — Evaluates the mesh vertices of for LOD @p lod and mesh index @p meshIndex. @param diffPsd          The psd coefficients. Typically the output from RigLogic::EvaluatePsd() @param lod              The lod for which to evalute the vertices. @param meshIndex        Which mesh to evaluate. @return the evaluated deformed mesh vertices. The output contains Jacobians if either the internal rig has the jacobians set, or if @diffBlendshapes contains the Jacobian.
- L115 _private prototype_ `void EvaluateIndexedBlendshapes(const int lod, const DiffData<T>& diffPsd, State& state, const std::vector<int>& indices) const;`
- L118 _private prototype_ `void EvaluateSkinningWithoutJacobians(const int lod, State& state) const;` — evaluates the skinning for geometry @p geometryName with state as input (evaluated blendshape vertices) and output (final vertices).
- L119 _private prototype_ `void EvaluateSkinningWithJacobians(const int lod, State& state) const;`
- L123 _private prototype_ `void EvaluateIndexedSkinningWithoutJacobians(const int lod, State& state, const std::vector<int>& indices) const;` — evaluates the skinning only for the given vertex indices for geometry @p geometryName with state as input (evaluated blendshape vertices) and output (final vertices).
- L124 _private prototype_ `void EvaluateIndexedSkinningWithJacobians(const int lod, State& state, const std::vector<int>& indices) const;`
- L128 _private member_ `std::vector<Mesh<T>> mesh;` — the mesh topology
- L131 _private member_ `std::vector<Eigen::VectorXi> blendshapeControlsToMeshBlendshapeControls;` — selection of which blendshapes are used by this mesh
- L132 _private member_ `std::vector<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> blendshapeMatrixDense;`
- L135 _private member_ `std::vector<SparseMatrix<T>> vertexInfluenceWeights;` — skinning data
- L138 _private member_ `std::vector<std::string> jointNames;` — joint data
- L139 _private member_ `std::vector<int> jointParentIndices;`
- L141 _private member_ `Eigen::Matrix<T, 3, -1> jointRestPose;`
- L142 _private member_ `std::vector<Eigen::Matrix<T, 3, 3>> jointRestOrientation;`
- L145 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> jointBindPoses;` — bind pose
- L146 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> jointInverseBindPoses;`
- L148 _private member_ `std::shared_ptr<TaskThreadPool> taskThreadPool{};`

#### class `BodyGeometry::State`  
`template <class T> class BodyGeometry<T>::State`  
_L154-235_
- desc: Rig geometry state containing results of a specific evaluation
- L157 _public function_ `State()`
- L158 _public prototype_ `~State() = default;`
- L159 _public prototype_ `State(State&&) = default;`
- L160 _public prototype_ `State& operator=(State&&) = default;`
- L161 _public prototype_ `State(const State&) = default;`
- L162 _public prototype_ `State& operator=(const State&) = default;`
- L170 _public function_ `const DiffDataMatrix<T, 3, -1>& Vertices() const` — @return const std::vector<DiffDataMatrix<T, 3, -1>>&  the evaluated vertices. See BodyGeometry<T>::EvaluateBodyGeometry @warning The returned DiffDataMatrices are only valid as long as the State has not been updated by another call to BodyGeometry<T>::EvaluateBodyGeometry with the same state. Explanation: the dense matrix of the Jacobian is resized in BodyGeometry<T>::EvaluateBodyGeometry and therefore the DiffDataMatrix Jacobian will map to an invalidated dense matrix.
- L173 _public function_ `const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& GetWorldMatrices() const` — @return the current world matrix of the joint rig.
- L175 _public function_ `const Eigen::Matrix<T, -1, -1, Eigen::RowMajor>& GetWorldMatricesJacobian() const`
- L178 _public function_ `const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& GetLocalMatrices() const` — @return the current local matrix of the joint rig.
- L181 _public function_ `const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& GetSkinningMatrices() const` — @return the current skinning matrix of the joint rig.
- L184 _public function_ `const Vector<T>& GetBlendshapeCoefficients() const` — @return the blendshape coefficients
- L187 _public function_ `const Eigen::Matrix3X<T>& GetBlendshapeVertices() const` — @return the blendshape mesh of index i
- L190 _public function_ `const std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>& GetBlendshapeJacobian() const` — @return the blendshape mesh jacobian
- L194 _private member_ `DiffDataMatrix<T, 3, -1> vertices = DiffDataMatrix<T, 3, -1>(Eigen::Matrix<T, 3, -1>());` — the evaluated vertices
- L196 _private member_ `DiffDataMatrix<T, 3, -1> jointWorldTranslations = DiffDataMatrix<T, 3, -1>(Eigen::Matrix<T, 3, -1>());`
- L199 _private member_ `bool withJacobians = false;` — flag specifying whether the state has been set including Jacobians
- L202 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> localMatrices;` — the evaluated local transformations for each joint
- L205 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> worldMatrices;` — the evaluated world transformations for each joint
- L208 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> skinningMatrices;` — the evaluated skinning transformations for each joint
- L211 _private member_ `DiffData<T> diffMeshBlendshapes = DiffData<T>(Eigen::VectorX<T>());` — the evaluated blendshape weights
- L214 _private member_ `int jointJacobianColOffset = -1;` — local caching of the jacobians for the joints
- L215 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> jointDeltasJacobian;`
- L216 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> localMatricesJacobian;`
- L217 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> worldMatricesJacobian;`
- L218 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> skinningMatricesJacobian;`
- L221 _private member_ `Eigen::Matrix<T, 3, -1> blendshapeVertices;` — blendshapes as they were evaluated
- L222 _private member_ `std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> blendshapeJacobianRM = std::make_shared<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>();`
- L223 _private member_ `int blendshapeJacobianColOffset = -1;`
- L226 _private member_ `int offsetJacobianColOffset = -1;` — offset Jacobian info (for differentiable offset in EvaluateBodyGeometryWithOffset)
- L227 _private member_ `std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> offsetJacobianRM = std::make_shared<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>();`
- L230 _private member_ `Eigen::Matrix<T, 3, -1> finalVertices;` — final vertices after applying the joint evaluation
- L231 _private member_ `std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> finalJacobianRM = std::make_shared<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>();`
- L232 _private member_ `int finalJacobianColOffset = -1;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/BodyLogic.h` (Private)


#### class `BodyLogic`  
`template <class T> class BodyLogic`  
_L23-128_
- desc: BodyLogic implements rig logic including Jacobian for parametric body models This is quite more open than the face rig version, as we need to have easy acces to edit/change the values of things
- L37 _public prototype_ `BodyLogic();`
- L38 _public prototype_ `BodyLogic(int _numLods);`
- L39 _public prototype_ `~BodyLogic() = default;`
- L40 _public prototype_ `BodyLogic(BodyLogic&&) = default;`
- L41 _public prototype_ `BodyLogic(BodyLogic&) = default;`
- L42 _public prototype_ `BodyLogic& operator=(BodyLogic&&) = default;`
- L43 _public prototype_ `BodyLogic& operator=(const BodyLogic&) = default;`
- L45 _public prototype_ `std::shared_ptr<BodyLogic> Clone() const;`
- L48 _public prototype_ `bool Init(const dna::Reader* reader);` — Initializes BodyLogic with the data from the dna::BinaryStreamReader
- L50 _public prototype_ `bool InitRBFJointMatrix(const dna::Reader* reader);`
- L53 _public function_ `int NumGUIControls() const` — @return the number of gui controls of the rig
- L56 _public function_ `int NumRawControls() const` — @return the number of raw controls of the rig
- L59 _public function_ `int NumLODs() const` — @return the number of lods
- L60 _public prototype_ `void SetNumLODs(const int l);`
- L66 _public prototype_ `DiffData<T> EvaluateRawControls(const DiffData<T>& guiControls) const;` — Evaluate the raw controls given the input gui controls. Throws an expection is the size is incorrect. There is no clamping involved, any gui controls exceeding their range will extrapolate the values.
- L72 _public prototype_ `DiffData<T> EvaluateJoints(const int lod, const DiffData<T>& rawControls) const;` — Evaluate the joint values from the raw values. Throws an expection is the size is incorrect. You would typically call it with the output from EvaluateRawControls().
- L73 _public prototype_ `DiffData<T> EvaluateRbfJoints(const int lod, const DiffData<T>& rbfControls) const;`
- L78 _public function_ `const std::vector<std::string>& GuiControlNames() const` — @return the names of the GUI controls.
- L79 _public function_ `std::vector<std::string>& GuiControlNames()`
- L84 _public function_ `const std::vector<std::string>& RawControlNames() const` — @return the names of the raw controls.
- L85 _public function_ `std::vector<std::string>& RawControlNames()`
- L90 _public function_ `const std::vector<GuiToRawInfo>& GuiToRawMapping() const` — @return the gui control mapping
- L91 _public function_ `std::vector<GuiToRawInfo>& GuiToRawMapping()`
- L96 _public function_ `const Eigen::Matrix<T, 2, -1>& GuiControlRanges() const` — @return the gui control ranges
- L97 _public function_ `Eigen::Matrix<T, 2, -1>& GuiControlRanges()`
- L102 _public function_ `const SparseMatrix<T>& GetJointMatrix(const int lod) const` — @return the joint matrix mapping raw controls to joint maps for the given lod
- L103 _public function_ `SparseMatrix<T>& GetJointMatrix(const int lod)`
- L105 _public function_ `const SparseMatrix<T>& GetRbfJointMatrix(const int lod) const`
- L106 _public function_ `SparseMatrix<T>& GetRbfJointMatrix(const int lod)`
- L109 _private prototype_ `void SortGuiControlMapping();`
- L112 _private member_ `int numLODs;`
- L114 _private member_ `std::vector<std::string> guiControlNames;`
- L115 _private member_ `std::vector<std::string> rawControlNames;`
- L118 _private member_ `std::vector<GuiToRawInfo> guiToRawMapping;` — ### GUI to Raw mapping ###
- L121 _private member_ `Eigen::Matrix<T, 2, -1> guiControlRanges;` — the ranges for each gui control
- L124 _private member_ `std::vector<SparseMatrix<T>> jointMatrix;` — joint mapping
- L127 _private member_ `std::vector<SparseMatrix<T>> rbfJointMatrix;` — rbf joint matrix

#### struct `BodyLogic::GuiToRawInfo`  
`struct GuiToRawInfo`  
_L26-34_
- L28 _public member_ `int inputIndex;` — gui control (col index)
- L29 _public member_ `int outputIndex;` — raw control (row index)
- L30 _public member_ `T from;`
- L31 _public member_ `T to;`
- L32 _public member_ `T slope;`
- L33 _public member_ `T cut;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/CombinedBodyJointLodMapping.h` (Private)


#### class `CombinedBodyJointLodMapping`  
`template <class T> class CombinedBodyJointLodMapping`  
_L21-62_
- desc: A class for calculating a simple mapping for how skinning weights for joints should be propagated from LOD0 to higher LODs. This is intended for a rig where joints for higher lods are represented by a simple parent child relationship ie no new joints are introduced at intermediate lods. The approach first works out which joints are active for each lod, and for each joint in a higher lod, if that joint is not active, it pushes it up to the first active parent. The user can also specify options joints for which joints can be propagated to a combination of the first active parent joint, and the closest active sibling joint. The user can decide the split in influence between the parent joint (giving stability) and the sibling joint (giving more specific localized behaviour), and can also apply an optional inverse distance weighting ie if the parent joint is further away it gives less influence (and vice versa). Sibling joint propagation works well for joint clusters like fingers (and possibly toes) where some of the digits may be removed at higher lod(s).
- L24 _public function_ `CombinedBodyJointLodMapping()`
- L27 _public prototype_ `void CalculateMapping(const RigGeometry<T>& rigGeometry);` — | Calculate the joint mapping from RigGeometry as above
- L31 _public prototype_ `const std::vector<std::map<std::string, std::map<std::string, T>>>& GetJointMapping() const;` — Get the joint mapping for all Lods. For each lod, this returns a mapping for each lod which defines how to take each joint influence for that joint from lod 0 and spread it onto joint(s) in the current lod as a weighted sum of values from lod0
- L34 _public prototype_ `JsonElement ToJson() const;` — save the mapping to json
- L37 _public prototype_ `bool ReadJson(const JsonElement& jointPropagationMapJson);` — read the mapping from json
- L40 _public prototype_ `bool UseDistanceWeightingForSiblingPropagation() const;` — get whether or not we use distance weighting for sibling propagation
- L43 _public prototype_ `void SetUseDistanceWeightingForSiblingPropagation(bool bUseDistanceWeighting);` — set whether we use distance weighting for sibling propagation
- L46 _public prototype_ `T ParentWeightForSiblingPropagation() const;` — get the parent weighting for sibling propagation
- L49 _public prototype_ `void SetParentWeightForSiblingPropagation(const T& parentWeighting);` — set the parent weighting for sibling propagation
- L52 _public prototype_ `const std::vector<std::string>& JointsToIncludeSiblingsInPropagation() const;` — get the list of (parent) joints to include in sibling propagation ie all child joints below this joint will use sibling propagation
- L55 _public prototype_ `void SetJointsToIncludeSiblingsInPropagation(const std::vector<std::string>& jointsToIncludeInSiblingPropagation);` — set the list of (parent) joints to include in sibling propagation ie all child joints below this joint will use sibling propagation
- L58 _private member_ `std::vector<std::map<std::string, std::map<std::string, T>>> m_combinedBodyJointLodMapping;`
- L59 _private member_ `std::vector<std::string> m_jointsToIncludeSiblingsInPropagation = { "hand_r",`
- L60 _private member_ `T m_parentWeightForSiblingPropagation = T(0.25f);`
- L61 _private member_ `bool m_bUseDistanceWeightingForSiblingPropagation = true;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/DriverJointControls.h` (Private)


#### class `DriverJointControls`  
`class DriverJointControls`  
_L23-72_
- L43 _public prototype_ `DriverJointControls();`
- L44 _public prototype_ `~DriverJointControls();`
- L45 _public prototype_ `DriverJointControls(DriverJointControls&& other) noexcept;`
- L46 _public prototype_ `DriverJointControls& operator=(DriverJointControls&& other) noexcept;`
- L47 _public prototype_ `DriverJointControls(const DriverJointControls& other);`
- L48 _public prototype_ `DriverJointControls& operator=(const DriverJointControls& other);`
- L51 _public prototype_ `template <class T> DiffData<T> EvaluateRawControlsFromEuler(const DiffData<T>& eulerControls) const;`
- L54 _public prototype_ `template <class T> DiffData<T> EvaluateRawControlsFromJoints(const DiffData<T>& jointDiff) const;`
- L57 _public prototype_ `const std::vector<std::string>& EulerControlNames() const;`
- L58 _public prototype_ `const std::vector<std::uint16_t>& RawControlIndices() const;`
- L60 _public prototype_ `const std::map<int, Mapping>& Mappings() const;`
- L62 _public prototype_ `int JointIndexFromEulerControl(std::uint16_t control) const;`
- L63 _public prototype_ `int JointIndexFromRawControl(std::uint16_t control) const;`
- L65 _public prototype_ `void Init(const dna::Reader* reader);`
- L66 _public prototype_ `void RemoveJoints(const std::vector<int>& newToOldJointMapping);`
- L70 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### struct `DriverJointControls::Mapping`  
`struct Mapping`  
_L26-41_
- L28 _public member_ `std::string jointName;`
- L30 _public member_ `std::uint16_t eulerX;`
- L31 _public member_ `std::uint16_t eulerY;`
- L32 _public member_ `std::uint16_t eulerZ;`
- L34 _public member_ `std::uint16_t rawX;`
- L35 _public member_ `std::uint16_t rawY;`
- L36 _public member_ `std::uint16_t rawZ;`
- L37 _public member_ `std::uint16_t rawW;`
- L38 _public prototype_ `static std::map<int, Mapping> Generate(const dna::Reader* reader);`
- L39 _public prototype_ `static std::vector<std::string> GetEulerControlNames(const std::map<int, Mapping>& mappings);`
- L40 _public prototype_ `static std::vector<std::uint16_t> GetRawControlIndices(const std::map<int, Mapping>& mappings);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/EyelashConnectedVertices.h` (Private)


#### struct `EyelashConnectedVertices`  
`template <class T> struct EyelashConnectedVertices`  
_L17-36_
- desc: a little struct to represent eyelash connected vertices and how they should be transformed relative to the head mesh
- L19 _public member_ `static constexpr int32_t version = 1;`
- L21 _public member_ `bool valid = false;`
- L22 _public member_ `std::vector<int> indices;`
- L23 _public member_ `Affine<T, 3, 3> affine;`
- L24 _public member_ `std::vector<int> headvIDs;`
- L27 _public prototype_ `static bool InitializeEyelashMapping(const Mesh<T>& headMesh, const Mesh<T>& eyelashesMesh, const std::vector<std::pair<int, T>>& eyelashRoots, std::vector<std::shared_ptr<EyelashConnectedVertices<T>>>& eyelashConnectedVertices);` — initialize the eyelash mapping between the eyelashes mesh and head mesh, returning the mapping as a vector of eyelash connected vertices. Returns true if initialized successfully, false otherwise (eg if eyelashRoots indices are out of range)
- L31 _public prototype_ `static void ApplyEyelashMapping(const Mesh<T>& srcHeadMesh, const Eigen::Matrix<T, 3, -1>& targetHeadMeshVertices, const Mesh<T>& srcEyelashesMesh, const std::vector<std::shared_ptr<EyelashConnectedVertices<T>>>& eyelashConnectedVertices, Eigen::Matrix<T, 3, -1>& updatedEyelashVertices);` — apply the eyelash mapping using the supplied head and eyelash meshes and eyelash connected vertices, returning the results in updatedEyelashVertices. Will fail with a CARBON_CRITICAL if the head meshes do not contain a consistent number of verticesm or the eyelash mesh and eyelashConnectedVertices are inconsistent with each other or with the head mesh
- L35 _public prototype_ `static void Reduce(std::vector<std::shared_ptr<EyelashConnectedVertices<T>>>& eyelashConnectedVertices);` — reduce the number of eyelashes to segments

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace trio`
- L40 _prototype_ `template <class T> bool ToBinaryFile(FILE* pFile, const EyelashConnectedVertices<T>& eyelashConnectedVertices);`
- L43 _prototype_ `template <class T> bool FromBinaryFile(FILE* pFile, EyelashConnectedVertices<T>& eyelashConnectedVertices);`
- L46 _prototype_ `template <class T> bool FromBinaryFile(trio::BoundedIOStream* stream, EyelashConnectedVertices<T>& eyelashConnectedVertices);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/Joint.h` (Private)


#### struct `JointHelper`  
`template <class T> struct JointHelper`  
_L19-19_
- L24 _public typedef_ `using SCALAR = T;`

#### struct `JointHelper`  
`template <class T, int R, int C> struct JointHelper<Eigen::Matrix<T, R, C>>`  
_L22-25_
- L24 _public typedef_ `using SCALAR = T;`

#### struct `JointHelper`  
`template <class T, int R, int C> struct JointHelper<DiffDataAffine<T, R, C>>`  
_L28-31_
- L24 _public typedef_ `using SCALAR = T;`

#### struct `JointHelper`  
`template <class T, int R, int C> struct JointHelper<Affine<T, R, C>>`  
_L33-36_
- L24 _public typedef_ `using SCALAR = T;`

#### class `Joint`  
`template <class AffineType> class Joint`  
_L42-232_
- desc: A Joint represents a local transformation
- L44 _private typedef_ `using T = typename JointHelper<AffineType>::SCALAR;`
- L47 _public function_ `Joint(const std::string& name = "") : m_name(name), m_parent(nullptr)`
- L49 _public function_ `const std::string& Name() const`
- L51 _public function_ `bool HasParent() const`
- L53 _public function_ `bool IsRoot() const`
- L55 _public function_ `const Joint* Parent() const`
- L57 _public function_ `bool SetParent(Joint* parent)`
- L80 _public function_ `void AddChild(Joint* child)`
- L89 _public function_ `void RemoveChild(Joint* child)`
- L94 _public function_ `int NumChildren() const`
- L97 _public function_ `bool HasChild(Joint* j, bool recursive) const` — @returns whether joint @p j is a child of this joint. Use @p recursive to check recursively.
- L117 _public function_ `const AffineType& LocalMatrix()`
- L119 _public function_ `void SetLocalMatrix(const AffineType& localMatrix)`
- L125 _public function_ `void SetLocalMatrix(AffineType&& localMatrix)`
- L131 _public function_ `const Affine<T, 3, 3>& BindMatrix() const`
- L136 _public function_ `void SetBindMatrix(const Affine<T, 3, 3>& bindMatrix)`
- L143 _public function_ `const AffineType& WorldMatrix()`
- L159 _public function_ `const AffineType& SkinningMatrix()`
- L170 _private function_ `void RemoveChild(Joint* child, bool updateChild)`
- L184 _private function_ `void InvalidateWorldMatrix()` — Set the world matrix as invalid, and therefore all children are also invalid
- L201 _private member_ `std::string m_name;` — name of this joint
- L204 _private member_ `Joint<AffineType>* m_parent;` — parent
- L207 _private member_ `std::vector<Joint<AffineType>*> m_children;` — children
- L210 _private member_ `AffineType m_localMatrix;` — local transformation matrix
- L213 _private member_ `Affine<T, 3, 3> m_bindMatrix;` — bind matrix
- L216 _private member_ `Affine<T, 3, 3> m_bindMatrixInverse;` — inverse of the bind matrix
- L224 _private member_ `std::optional<AffineType> m_worldMatrix;` — world transformation matrix
- L227 _private member_ `std::optional<AffineType> m_skinningMatrix;` — skinning matrix (m_worldMatrix * m_bindMatrixInverse)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/JointRig.h` (Private)


#### struct `InfluenceWeights`  
`template <class T> struct InfluenceWeights`  
_L13-20_
- L17 _public member_ `Eigen::VectorX<int> indices;` — vertex indices
- L19 _public member_ `Eigen::VectorX<T> weights;` — vertex weights

#### class `JointRig`  
`template <class AffineType> class JointRig`  
_L28-307_
- desc: A JointRig represents a hierarchy of joints and the set of influence weights on how each joint influences geometry. The deformed geometry can be evaluated with or without Jacobians.
- L31 _public typedef_ `using T = typename JointHelper<AffineType>::SCALAR;`
- L32 _public typedef_ `using JointPtr = std::shared_ptr<Joint<AffineType>>;`
- L35 _public function_ `JointRig()`
- L36 _public prototype_ `virtual ~JointRig() = default;`
- L38 _public prototype_ `JointRig(JointRig&) = delete;`
- L39 _public prototype_ `JointRig& operator=(const JointRig&) = delete;`
- L41 _public function_ `virtual void Clear()`
- L49 _public function_ `void AddJoint(const JointPtr& joint)` — Adds a new joint to the rig
- L63 _public function_ `JointPtr GetJoint(const std::string& name) const`
- L76 _public function_ `const std::map<std::string, JointPtr>& GetJoints() const`
- L78 _public function_ `std::vector<std::string> GetJointNames() const`
- L92 _public function_ `void AddInfluenceWeights(const std::string& geometryName, const std::map<std::string, InfluenceWeights<T>>& jointInfluenceWeights, int numVertices = -1)` — Add all joint influence weights for geometry @p geometryName. @param[in] numVertices  If numVertices < 0 then the number of vertices are infered from the vertex indices in @p jointInfluenceWeights.
- L167 _public function_ `InfluenceWeights<T> GetInfluenceWeights(const std::string& jointName, const std::string& geometryName) const`
- L214 _public function_ `std::vector<std::string> GetGeometryNames() const`
- L225 _public function_ `std::map<std::string, Affine<T, 3, 3>> GetState() const` — Returns the current state (local matrices) of all the joints
- L236 _public function_ `virtual void SetState(const std::map<std::string, Affine<T, 3, 3>>& state)` — Set the state of the joints
- L253 _public prototype_ `Eigen::Matrix<T, 3, -1> EvaluateGeometry(const std::string& geometryName, const Eigen::Matrix<T, 3, -1>& restVertices) const;` — Basic geometry evaluation. This does not calculate any Jacobian. Instantiated for float and double versions of Affine<T, 3, 3> and DiffDataAffine<T, 3, 3>
- L261 _public prototype_ `DiffDataMatrix<T, 3, -1> EvaluateGeometry(const std::string& geometryName, const DiffDataMatrix<T, 3, -1>& restVertices) const;` — Geometry evaluation with Jacobian. Instantiated for float and double versions of DiffDataAffine<T, 3, 3>
- L268 _public prototype_ `DiffData<T> EvaluateRegularization(const T rotationWeight, const T translationWeight, const std::map<std::string, Affine<T, 3, 3>>& restStates, const bool regularizeRoot = false) const;` — Calculates a regularization residual of the affine transformations of the rig against the save state Instantiated for float and double versions of DiffDataAffine<T, 3, 3>
- L275 _public function_ `void CheckValidity()` — Sanity checks for the rig
- L278 _public function_ `void CheckSingleRoot()` — JointRig only supports rigs with a single root joint
- L300 _private member_ `std::map<std::string, JointPtr> m_joints;` — map of joint name to joint
- L303 _private member_ `std::vector<JointPtr> m_jointsVector;` — vector of joints
- L306 _private member_ `std::map<std::string, SparseMatrix<T>> m_vertexInfluenceWeights;` — map of geometry name to map of vertex index to list of joint indices (@see m_jointsVector) and weight

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/JointRig2.h` (Private)


#### class `JointRig2`  
`template <class T> class JointRig2`  
_L16-134_
- desc: A JointRig represents a hierarchy of joints and the set of influence weights on how each joint influences geometry.
- L27 _public prototype_ `JointRig2() = default;`
- L28 _public prototype_ `~JointRig2() = default;`
- L29 _public prototype_ `JointRig2(JointRig2&&) = default;`
- L30 _public prototype_ `JointRig2& operator=(JointRig2&&) = default;`
- L31 _public prototype_ `JointRig2(JointRig2&) = default;`
- L32 _public prototype_ `JointRig2& operator=(const JointRig2&) = default;`
- L34 _public prototype_ `void Clear();`
- L36 _public function_ `int NumJoints() const`
- L42 _public prototype_ `void AddJoint(const std::string& newJointName);` — Adds a new joint to the rig
- L44 _public function_ `const std::vector<std::string>& GetJointNames() const`
- L49 _public prototype_ `int GetJointIndex(const std::string& jointName) const;`
- L51 _public function_ `int GetParentIndex(int jointIndex) const`
- L57 _public prototype_ `void AttachJointToParent(const std::string& childJointName, const std::string& parentJointName);` — Sets a joint to be the parent of another joint
- L60 _public prototype_ `bool IsChildOf(const std::string& jointName, const std::string& parentJointName) const;` — Checks if @p jointName is child of parentJointName
- L63 _public prototype_ `int HierarchyLevel(const std::string& jointName) const;` — @return the hierarchy level of the joint. 0 is a root joint, 1 is a joint one below the root, ...
- L64 _public prototype_ `int HierarchyLevel(int jointIndex) const;`
- L67 _public prototype_ `std::vector<std::vector<int>> GetJointsPerHierarchyLevel() const;` — @return vector of which joints indices are at what level
- L73 _public prototype_ `void SetSkinningWeights(const std::string& geometryName, const std::map<std::string, InfluenceWeights<T>>& jointInfluenceWeights, int numVertices = -1, bool normalizeWeights = true, bool allowNegativeWeights = false, ErrorInfo* errorInfo = nullptr);` — Add all joint influence weights for geometry @p geometryName. @param[in] numVertices  If numVertices < 0 then the number of vertices are infered from the vertex indices in @p jointInfluenceWeights.
- L84 _public prototype_ `Eigen::VectorX<T> GetSkinningWeights(const std::string& jointName, const std::string& geometryName, bool includingChildren = false) const;` — @returns the skinning weights for joint @p jointName on geometry @p geometryName. If @p inclduingChildren is True, then it will add the skinning weights of child joints.
- L87 _public prototype_ `InfluenceWeights<T> GetSkinningWeightsAsStruct(const std::string& jointName, const std::string& geometryName) const;` — Temporary method which returns JointRig API skinning weights
- L89 _public prototype_ `std::vector<std::string> GetGeometryNames() const;`
- L92 _public prototype_ `void CheckValidity();` — Sanity checks for the rig
- L95 _public prototype_ `void CheckSingleRoot();` — JointRig only supports rigs with a single root joint
- L98 _public prototype_ `const SparseMatrix<T>& GetSkinningWeights(const std::string& geometryName) const;` — @return the skin weights matrix for geometry @p geometryName
- L101 _public prototype_ `void SetSkinningWeights(const std::string& geometryName, const SparseMatrix<T>& smat);` — Explicity set the joint matrix for geometry @p geometryName
- L104 _public prototype_ `void RemoveSkinningWeights(const std::string& geometryName);` — Remove skin weights for a geometry @p geometryName
- L107 _public prototype_ `bool HasSkinningWeights(const std::string& geometryName) const;` — Check if skinning weights exist for geometry @p geometryName
- L112 _public prototype_ `void Resample(const std::string& geometryName, const std::vector<int>& newToOldMap);` — Resample the vertex influence weights for geometry @p geometryName, where influence for the new vertex i will have the old weights of vertex newToOldMap[i].
- L119 _public prototype_ `std::vector<int> RemoveUnusedJoints();` — @brief Remove all unused joints. @return Maps new joint indices to previous joint indices.
- L123 _public prototype_ `std::vector<int> GetSymmetricJointIndices() const;` — @returns vector of indices pointing to the symmetric joint. Symmetric joints are determined by looking at the joint names and searching for _R or _L in the name.
- L127 _private member_ `std::vector<std::string> m_jointNames;` — names of the joints
- L130 _private member_ `std::vector<int> m_jointParentIndices;` — maps a joint to its parent (via indices)
- L133 _private member_ `std::map<std::string, SparseMatrix<T>> m_skinningWeights;` — map of geometry name to sparse matrix with rows: vertices, columns: joint index, values: skin weight

#### struct `JointRig2::ErrorInfo`  
`struct ErrorInfo`  
_L19-24_
- L21 _public member_ `std::vector<int> unskinnedVertices;`
- L22 _public member_ `std::vector<int> unnormalizedVertices;`
- L23 _public member_ `std::vector<int> negativeWeightsVertices;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/JointRigVariable.h` (Private)


#### class `JointRigVariable`  
`template <class T> class JointRigVariable : public JointRig<DiffDataAffine<T, 3, 3>>`  
_L20-91_
- inherits: `JointRig<DiffDataAffine<T,3,3>>`
- desc: A 3D JointRig with variable local matrices that can be optimized
- L22 _private typedef_ `using JointPtr = typename JointRig<DiffDataAffine<T, 3, 3>>::JointPtr;`
- L25 _public prototype_ `virtual ~JointRigVariable() = default;`
- L27 _public function_ `virtual void Clear() override`
- L34 _public function_ `void CreateVariables()` — Create all variables associated to the joints
- L48 _public function_ `void EvaluateVariables(Context<T>* context)` — Evaluates the joint variables and sets the local affine transformation matrix of the rig including the Jacobians.
- L59 _public function_ `virtual void SetState(const std::map<std::string, Affine<T, 3, 3>>& state) override` — Set the joint state and update the variables
- L78 _public function_ `void SetDegreesOfFreedom(const std::string& jointName, bool rotation, bool translation)` — Sets the degrees of freedom of a joint @param rotation     Whether rotation is a degree of freedom (3 DOFs really) @param translation  Whether translation is a degree of freedom (3 DOFs really)
- L90 _private member_ `std::map<std::string, std::shared_ptr<AffineVariable<QuaternionVariable<T>>>> m_variables;` — the variables associated with the joints

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/LimitConstraintFunction.h` (Private)


#### class `LimitConstraintFunction`  
`template <class T> class LimitConstraintFunction`  
_L13-82_
- L18 _public function_ `static DiffData<T> Evaluate( const DiffData<T>& guiControls, const BodyLogic<T>& rig, const T weight)` — Function to a soft error based on the limits of the riglogic class

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/RBFLogic.h` (Private)


#### class `RBFLogic`  
`template <class T> class RBFLogic`  
_L28-70_
- L31 _public typedef_ `using SolverPtr = pma::ScopedPtr<rbfs::RBFSolver>;`
- L33 _public prototype_ `RBFLogic();`
- L34 _public prototype_ `~RBFLogic();`
- L36 _public prototype_ `RBFLogic(RBFLogic&&);`
- L37 _public prototype_ `RBFLogic& operator=(RBFLogic&&);`
- L39 _public prototype_ `RBFLogic(const RBFLogic&);`
- L40 _public prototype_ `RBFLogic& operator=(const RBFLogic&);`
- L42 _public prototype_ `DiffData<T> EvaluatePoseControlsFromRawControls(const DiffData<T>& rawControls) const;`
- L43 _public prototype_ `DiffData<T> EvaluatePoseControlsFromJoints(const DiffData<T>& joints, bool withJointScaling = false) const;`
- L45 _public prototype_ `bool Init(const dna::Reader* reader);`
- L46 _public prototype_ `void Write(dna::Writer* writer);`
- L48 _public prototype_ `const SolverPtr& GetSolver(int solverIndex) const;`
- L49 _public prototype_ `const std::vector<SolverPtr>& RBFSolvers() const;`
- L50 _public prototype_ `std::vector<std::uint16_t> SolverRawControlIndices(int solverIndex) const;`
- L51 _public prototype_ `const std::vector<float>& SolverRawTargetValues(int solverIndex) const;`
- L52 _public prototype_ `const std::vector<std::string>& SolverNames() const;`
- L53 _public prototype_ `const std::vector<std::uint16_t>& SolverPoseIndices(int solverIndex) const;`
- L54 _public prototype_ `const std::vector<std::uint16_t>& PoseOutputControlIndices(int poseIndex) const;`
- L55 _public prototype_ `const std::string& PoseOutputControlName(int poseOutputControlIndex) const;`
- L56 _public prototype_ `std::uint16_t PoseControlCount() const;`
- L57 _public prototype_ `std::uint16_t PoseControlOffset() const;`
- L58 _public prototype_ `const std::vector<std::string>& PoseNames() const;`
- L59 _public prototype_ `const std::vector<std::string>& PoseControlNames() const;`
- L60 _public prototype_ `bool SolverAutomaticRadius(int solverIndex) const;`
- L61 _public prototype_ `const DriverJointControls& GetDriverJointControls() const;`
- L63 _public prototype_ `void SetSolver(int solverIndex, const std::string& solverName, const std::vector<std::uint16_t>& poseIndices, rbfs::RBFSolverRecipe recipe);`
- L65 _public prototype_ `void RemoveJoints(const std::vector<int>& newToOldJointMapping);`
- L69 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/Rig.h` (Private)


#### class `Rig`  
`template <class T> class Rig`  
_L17-125_
- desc: Class combining RigLogic, RigGeometry, and the default values.
- L20 _public prototype_ `Rig();`
- L21 _public prototype_ `~Rig();`
- L23 _public prototype_ `Rig(const std::shared_ptr<const RigLogic<T>>& rigLogic, const std::shared_ptr<const RigGeometry<T>>& rigGeometry);`
- L33 _public prototype_ `bool LoadRig(const std::string& DNAFilename, bool withJointScaling = false, std::map<std::string, typename RigGeometry<T>::ErrorInfo>* errorInfo = nullptr);` — @brief Loads the rig from @p DNAFilename. @param DNAFilename The name of the DNA file. @param withJointScaling If False, then any joint scaling that is part of the DNA is discarded. Currently only pupils have scaling information. @return true   If DNA file could be read. @return false  If any error occurred during reading.
- L43 _public prototype_ `bool LoadRig(const dna::Reader* DNAStream, bool withJointScaling = false, std::map<std::string, typename RigGeometry<T>::ErrorInfo>* errorInfo = nullptr);` — @brief Loads the rig from @p DNAStream. @param DNAStream The DNA stream. @param withJointScaling If False, then any joint scaling that is part of the DNA is discarded. Currently only pupils have scaling information. @return true   If DNA file could be read. @return false  If any error occurred during reading.
- L46 _public prototype_ `bool VerifyTopology(const Mesh<T>& topology) const;` — Tests whether the rig adheres to \p topology
- L48 _public function_ `const std::shared_ptr<const RigLogic<T>>& GetRigLogic() const`
- L49 _public function_ `const std::shared_ptr<const RigGeometry<T>>& GetRigGeometry() const`
- L50 _public prototype_ `const std::vector<std::string>& GetGuiControlNames() const;`
- L51 _public prototype_ `const std::vector<std::string>& GetRawControlNames() const;`
- L53 _public function_ `const Mesh<T>& GetBaseMesh() const`
- L54 _public function_ `const Mesh<T>& GetBaseMeshTriangulated() const`
- L57 _public prototype_ `void UpdateBaseMeshTriangulation(const Mesh<T>& triangulatedMesh);` — Update the base mesh triangulation using @p triangulatedMesh
- L66 _public prototype_ `std::vector<Eigen::Matrix<T, 3, -1>> EvaluateVertices(const Eigen::VectorX<T>& controls, int lod, const std::vector<int>& meshIndices, ControlsType controlsType = ControlsType::GuiControls) const;` — Evaluates the vertices of multiple meshes
- L72 _public prototype_ `void EvaluateVertices(const Eigen::VectorX<T>& controls, int lod, const std::vector<int>& meshIndices, typename RigGeometry<T>::State& state, ControlsType controlsType = ControlsType::GuiControls) const;` — Evaluates the vertices of multiple meshes
- L79 _public prototype_ `void MakeBlendshapeOnly();` — Convert joint-based shapes into blendshape-only shapes. Does not create blendshapes for the eye geometry.
- L82 _public prototype_ `void ReduceToLOD0Only();` — Only keep the highest resolution mesh
- L88 _public prototype_ `void ReduceToMeshes(const std::vector<int>& meshIndices);` — @brief Reduce the rig to only contain the meshes @p meshIndices Removes unused joints in the rig.
- L91 _public prototype_ `void RemoveBlendshapes(const std::vector<int>& meshIndices);` — Remove the blendshapes for meshes @p meshIndices
- L94 _public prototype_ `void ReduceToGuiControls(const std::vector<int>& guiControls);` — Simplify the rig to only support @p guiControls. All other gui controls will be ignored even if the are non-zero.
- L97 _public prototype_ `void Resample(const std::map<int, std::vector<int>>& vertexIndicesMap);` — Resample the rig such that for each mesh, a new vertex i will correspond to previous vertex vertexIndices[i].
- L100 _public prototype_ `void SetMesh(int meshIndex, const Eigen::Matrix<T, 3, -1>& vertices);` — Update the @p meshIndex 'th mesh vertices
- L102 _public prototype_ `void Translate(const Eigen::Vector3<T>& translation);`
- L105 _public prototype_ `void Mirror(const std::map<std::string, std::vector<int>>& symmetries, const std::map<std::string, std::vector<std::pair<int, T>>>& meshRoots);` — Mirror the rig horizontally
- L108 _public prototype_ `void UpdateRestOrientationEuler(const Eigen::Matrix<T, 3, -1>& restOrientationEuler);` — Update the rest orientation and also update the joint deltas due to change of the rest orientation
- L111 _public prototype_ `void UpdateRestPose(const Eigen::Matrix<T, 3, -1>& restPose, CoordinateSystem coordinateSystem);` — Update the rest pose
- L114 _public prototype_ `void CreateSubdivision(const Mesh<T>& subdivisionTopology, const std::vector<std::tuple<int, int, T>>& stencilWeights, int meshIndex);` — Create a subdivision version of mesh @p meshIndex
- L117 _private member_ `std::shared_ptr<const RigLogic<T>> m_rigLogic;`
- L118 _private member_ `std::shared_ptr<const RigGeometry<T>> m_rigGeometry;`
- L121 _private member_ `Mesh<T> m_baseMesh;` — The base mesh (quads)
- L124 _private member_ `Mesh<T> m_baseMeshTriangulated;` — the base mesh (triangulated)

#### enum `Rig::ControlsType`  
`enum class ControlsType`  
_L59-63_
- L61 _public enumerator_ `GuiControls`
- L62 _public enumerator_ `RawControls`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/RigGeometry.h` (Private)


#### enum `CoordinateSystem`  
`enum class CoordinateSystem`  
_L28-32_
- desc: An enum to define whether coordinate system is Local or World
- L30 _public enumerator_ `Local`
- L31 _public enumerator_ `World`

#### class `RigGeometry`  
`template <class T> class RigGeometry`  
_L36-291_
- desc: RigGeometry implements the rig geometry evaluation based on rig logic inputs.
- L51 _public prototype_ `explicit RigGeometry(bool useMultithreading = true);`
- L52 _public prototype_ `~RigGeometry();`
- L53 _public prototype_ `RigGeometry(RigGeometry&&);`
- L54 _public prototype_ `RigGeometry(RigGeometry&) = delete;`
- L55 _public prototype_ `RigGeometry& operator=(RigGeometry&&);`
- L56 _public prototype_ `RigGeometry& operator=(const RigGeometry&) = delete;`
- L58 _public prototype_ `std::shared_ptr<RigGeometry> Clone() const;`
- L61 _public prototype_ `bool Init(const dna::Reader* reader, bool withJointScaling = false, std::map<std::string, ErrorInfo>* errorInfo = nullptr);` — Initializes RigGeometry with the data from the dna::Reader
- L64 _public prototype_ `State EvaluateRigGeometry(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd, const std::vector<int>& meshIndices) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L68 _public prototype_ `State& EvaluateRigGeometry(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, const DiffData<T>& diffPsd, const std::vector<int>& meshIndices, State& state) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L72 _public prototype_ `State& EvaluateWithPerMeshBlendshapes(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, const std::vector<DiffDataMatrix<T, 3, -1>>& diffBlendshapes, const std::vector<int>& meshIndices, const std::vector<Eigen::Ref<const Eigen::Matrix<T, 3, -1>>>& meshNeutrals, State& state) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L80 _public prototype_ `State& EvaluateWithPerMeshBlendshapes(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, const std::vector<DiffDataMatrix<T, 3, -1>>& diffBlendshapes, const std::vector<int>& meshIndices, State& state) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L87 _public prototype_ `State EvaluateWithPerMeshBlendshapes(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, const std::vector<DiffDataMatrix<T, 3, -1>>& diffBlendshapes, const std::vector<int>& meshIndices) const;` — Sets the joints and evaluates the mesh vertices for LOD @p lod and mesh indices @p meshIndices.
- L93 _public prototype_ `const Mesh<T>& GetMesh(int meshIndex) const;` — @return the @p meshIndex 'th mesh
- L96 _public prototype_ `const Mesh<T>& GetMesh(const std::string& meshName) const;` — @return the mesh @p meshName
- L99 _public prototype_ `const std::string& GetMeshName(int meshIndex) const;` — @return the name of the @p meshIndex 'th mesh
- L102 _public prototype_ `int GetMeshIndex(const std::string& meshName) const;` — @return the index of the mesh with name @p meshName
- L105 _public prototype_ `bool IsValid(int meshIndex) const;` — @return True if there is valid data for mesh @p meshIndex
- L108 _public prototype_ `int NumMeshes() const;` — @return the number of meshes
- L111 _public prototype_ `const std::vector<int>& GetMeshIndicesForLOD(int lod) const;` — @return all mesh indices that are part of @p lod
- L114 _public prototype_ `const std::vector<int>& GetBlendshapeMeshIndices() const;` — @return all mesh indices that contains blendshape targets
- L117 _public prototype_ `const std::vector<int>& JointIndicesForLOD(int lod) const;` — @return the joint indices that are used on LOD @p lod
- L120 _public prototype_ `const JointRig2<T>& GetJointRig() const;` — @return the underlying joint rig
- L123 _public prototype_ `Eigen::Matrix<T, 4, 4> GetBindMatrix(int jointIndex) const;` — @return the current bind matrix of the joint rig.
- L126 _public prototype_ `Eigen::Matrix<T, 4, 4> GetRestMatrix(int jointIndex) const;` — @return the current rest matrix of the joint rig.
- L129 _public prototype_ `const Eigen::Matrix<T, 3, -1>& GetRestOrientationEuler() const;` — @return the current rest orientation of all joints in euler angles.
- L132 _public prototype_ `const Eigen::Matrix<T, 3, -1>& GetRestPose() const;` — @return the current rest pose of all joints in euler angles.
- L138 _public prototype_ `void SetRestPose(Eigen::Matrix<T, 3, -1> restPose, CoordinateSystem coordSystem = CoordinateSystem::Local);` — @brief Set the rest pose. @param coordSystem: the coordinate system that the rest pose is provided in. This may be Local (the default) or World
- L145 _public prototype_ `void SetRestOrientationEuler(Eigen::Matrix<T, 3, -1> restOrientationEuler, CoordinateSystem coordSystem = CoordinateSystem::Local, bool bUpdateJointPositionsToPreviousValues = false);` — @brief Set the rest orientation (does not update joint deltas, see @p UpdateRestOrientationEuler ) @param coordSystem: the coordinate system that the rest orientation is provided in. This may be Local (the default) or World @param bUpdateJointPositionsToPreviousValues: if set to false, then the rest pose is not changed; if set to true then the rest pose is updated so that joint positions are the same as before
- L148 _public prototype_ `void UpdateRestOrientationEuler(const Eigen::Matrix<T, 3, -1>& restOrientationEuler, RigLogic<T>& rigLogic);` — Update the rest orientation and also update the joint deltas due to change of the rest orientation
- L153 _public prototype_ `void MakeBlendshapeOnly(const RigLogic<T>& rigLogic);` — @brief Makes a blendshape only rig. However, it keeps the eyes as joints.
- L156 _public prototype_ `void RemoveUnusedJoints(RigLogic<T>& rigLogic);` — Removes all unused joints from both RigGeometry and RigLogic.
- L159 _public prototype_ `void ReduceToLOD0Only();` — Remove all LODs besides the highest.
- L162 _public prototype_ `void ReduceToMeshes(const std::vector<int>& meshIndices);` — Only keep the mesh indices in the the rig. Keeps the removed meshes as empty meshes.
- L165 _public prototype_ `void RemoveBlendshapes(const std::vector<int>& meshIndices);` — Remove the blendshapes for meshes @p meshIndices
- L168 _public prototype_ `void SetMesh(int meshIndex, const Eigen::Matrix<T, 3, -1>& vertices);` — Update the @p meshIndex 'th mesh vertices
- L171 _public prototype_ `static Mesh<T> ReadMesh(const dna::Reader* reader, int meshIndex, bool triangulate = false);` — Assembles the mesh at index @p meshIndex stored within dna::Reader
- L174 _public prototype_ `void Resample(int meshIndex, const std::vector<int>& newToOldMap);` — Resample the rig geometry such that new vertex i will correspond to previous vertex newToOldMap[i].
- L177 _public prototype_ `std::string HeadMeshName(int lod) const;` — @return the name of the head mesh
- L180 _public prototype_ `std::string TeethMeshName(int lod) const;` — @return the name of the teeth mesh
- L183 _public prototype_ `std::string EyeLeftMeshName(int lod) const;` — @return the name of the left eye mesh
- L186 _public prototype_ `std::string EyeRightMeshName(int lod) const;` — @return the name of the right eye mesh
- L189 _public prototype_ `int HeadMeshIndex(int lod) const;` — @return the index of the head mesh
- L192 _public prototype_ `int TeethMeshIndex(int lod) const;` — @return the index of the teeth mesh
- L195 _public prototype_ `int EyeLeftMeshIndex(int lod) const;` — @return the index of the left eye mesh
- L198 _public prototype_ `int EyeRightMeshIndex(int lod) const;` — @return the index of the right eye mesh
- L202 _public prototype_ `int CorrespondingMeshIndexAtLod(int meshIndex, int lod) const;` — @return for mesh index @p meshIndex, returns the corresponding mesh index at LOD @p lod. -1 if the mesh does not exist.
- L206 _public prototype_ `SparseMatrix<T> VertexInfluenceWeights(const std::string& meshName) const;` — Returns vertex influence weights as a sparse matrix. Matrix is row major, rows correspond to vertices, and columns to joints
- L209 _public prototype_ `void Translate(const Eigen::Vector3<T>& translation);` — Update the rig by translating all elements
- L212 _public prototype_ `Eigen::Vector3<T> EyesMidpoint() const;` — @return the eye midpoint position
- L223 _public prototype_ `void Mirror(const std::map<std::string, std::vector<int>>& symmetries, const std::map<std::string, std::vector<std::pair<int, T>>>& meshRoots, RigLogic<T>& rigLogic);` — @brief Mirror the rig. @param symmetries  The symmetry mapping for meshes that are symmetric. Eyes are handled explicitly. @param meshRoots   The roots of meshes that are used to apply an as-rigid-as-possible deformation based on the head mesh. Used to mirror eyelashes as they are not symmetric, hence an acceptable deformation to the new symmetric head mesh is required. Roots are defined indices with a weight above 1. @param rigLogic    The riglogic component that also needs to be mirrored.
- L228 _public prototype_ `std::string GetSymmetricMeshName(const std::string& meshName) const;` — @returns the symmetric mesh for @p meshName. All meshes are self symmetric besides eyeLeft and eyeRight.
- L231 _public prototype_ `void CreateSubdivision(const Mesh<T>& subdivisionTopology, const std::vector<std::tuple<int, int, T>>& stencilWeights, int meshIndex);` — Cfreate a subdivision version of mesh @p meshIndex replacing the current version of the mesh.
- L234 _public prototype_ `void Transfer(int meshIndex, const RigGeometry<T>& otherRig, int otherMeshIndex);` — Copy the mesh of @p otherRig to mesh @p meshIndex of this rig using the blendshapes of this mesh.
- L237 _public prototype_ `void SaveBindPoseToDna(dna::Writer* writer) const;` — Save the rig bind pose to the dna binary stream
- L240 _public prototype_ `void SaveDna(dna::Writer* writer, int meshIndex) const;` — Save a specific mesh index to the binary stream
- L243 _public prototype_ `void SaveBlendshapeMappingToDna(dna::Writer* writer) const;` — Save the blendshape mapping to the dna binary stream
- L246 _public prototype_ `Eigen::Transform<T, 3, Eigen::Affine> GetRestPose(int jointIndex) const;` — Get joint rest pose
- L248 _public prototype_ `const Eigen::Matrix<T, -1, -1>& GetBlendshapeMatrix(int meshIndex) const;`
- L251 _public prototype_ `const Eigen::VectorXi GetBlendshapePsdControls(int meshIndex) const;` — get for each blendshape by which control it is being driven
- L254 _public prototype_ `std::uint16_t NumLODs() const;` — the number of LODs
- L256 _public prototype_ `void CalculateLocalJointTransformsFromWorldTransforms(const std::vector<Affine<T, 3, 3>>& jointWorldTransforms, Eigen::Matrix<T, 3, -1>& restPose, Eigen::Matrix<T, 3, -1>& restOrientationEulers) const;`
- L261 _private prototype_ `void EvaluateJointDeltas(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, State& state) const;` — Evaluates the joint deltas and stores it in @p state.
- L264 _private prototype_ `void EvaluateJointDeltasWithoutJacobians(const DiffDataAffine<T, 3, 3>& diffRigid, const DiffData<T>& diffJoints, State& state) const;` — Evaluates the joint deltas and stores it in @p state.
- L273 _private prototype_ `void EvaluateBlendshapes(const DiffData<T>& diffPsd, int meshIndex, State& state) const;` — Evaluates the mesh vertices of for LOD @p lod and mesh index @p meshIndex. @param diffPsd          The psd coefficients. Typically the output from RigLogic::EvaluatePsd() @param meshIndex        Which mesh to evaluate. @return the evaluated deformed mesh vertices. The output contains Jacobians if either the internal rig has the jacobians set, or if @diffBlendshapes contains the Jacobian.
- L277 _private prototype_ `void EvaluateSkinningWithoutJacobians(int meshIndex, State& state) const;` — evaluates the skinning for geometry @p geometryName with state as input (evaluated blendshape vertices) and output (final vertices).
- L279 _private prototype_ `void EvaluateSkinningWithJacobians(int meshIndex, State& state) const;`
- L281 _private prototype_ `void UpdateBindPoses();`
- L283 _private prototype_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> GetPreviousBindPose(const Eigen::Matrix<T, 3, -1>& restOrientationEuler) const;`
- L285 _private prototype_ `void UpdateRestPose(const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& prevBindPoses);`
- L290 _private member_ `std::unique_ptr<Private> m;` — TITAN_NAMESPACE::Pimpl<Private> m;

#### struct `RigGeometry::ErrorInfo`  
`struct ErrorInfo`  
_L43-48_
- L45 _public member_ `std::vector<std::pair<std::string, std::vector<int>>> duplicateBlendshapes;`
- L46 _public member_ `std::vector<std::pair<std::string, std::vector<int>>> zeroBlendshapes;`
- L47 _public member_ `typename JointRig2<T>::ErrorInfo skinningWeightsErrors;`

#### class `RigGeometry::State`  
`template <class T> class RigGeometry<T>::State`  
_L296-395_
- desc: Rig geometry state containing results of a specific evaluation
- L299 _public prototype_ `State();`
- L300 _public prototype_ `~State();`
- L301 _public prototype_ `State(State&&);`
- L302 _public prototype_ `State& operator=(State&&);`
- L303 _public prototype_ `State(const State&) = delete;`
- L304 _public prototype_ `State& operator=(const State&) = delete;`
- L314 _public prototype_ `const std::vector<DiffDataMatrix<T, 3, -1>>& Vertices() const;` — @return const std::vector<DiffDataMatrix<T, 3, -1>>&  the evaluated vertices. See RigGeometry<T>::EvaluateRigGeometry @warning The returned DiffDataMatrices are only valid as long as the State has not been updated by another call to RigGeometry<T>::EvaluateRigGeometry with the same state. Explanation: the dense matrix of the Jacobian is resized in RigGeometry<T>::EvaluateRigGeometry and therefore the DiffDataMatrix Jacobian will map to an invalidated dense matrix.
- L317 _public prototype_ `const Eigen::Matrix<T, 3, -1>& BlendshapeVertices(int meshId) const;` — @return blendshape deltas in bind pose space
- L320 _public prototype_ `const std::vector<int>& MeshIndices() const;` — @return the mesh indices that were passed to RigGeometry<T>::EvaluateRigGeometry for evalution
- L323 _public function_ `const std::vector<Eigen::Transform<T, 3, Eigen::Affine>>& GetWorldMatrices() const` — @return all world matrices
- L326 _public prototype_ `Eigen::Matrix<T, 4, 4> GetWorldMatrix(int jointIndex) const;` — @return the current world matrix of the joint rig.
- L329 _public prototype_ `Eigen::Matrix<T, 4, 4> GetLocalMatrix(int jointIndex) const;` — @return the current local matrix of the joint rig.
- L332 _public prototype_ `void SetLocalMatrix(int jointIndex, const Eigen::Matrix<T, 4, 4>& jointTransform);` — Set the current local matrix of the joint rig.
- L335 _public prototype_ `Eigen::Matrix<T, 4, 4> GetSkinningMatrix(int jointIndex) const;` — @return the current skinning matrix of the joint rig
- L338 _public prototype_ `std::vector<Eigen::Matrix<T, 4, 4>> GetAllSkinningMatrices() const;` — @return the current skinning matrices for all joints
- L341 _public prototype_ `std::vector<DiffDataMatrix<T, 3, -1>> MoveVertices();` — std::move the vertices from the state
- L345 _private prototype_ `void SetupForMesh(int meshIndex);` — setup the state to support adding data for mesh @p meshIndex
- L349 _private member_ `std::vector<DiffDataMatrix<T, 3, -1>> m_vertices;` — the evaluated vertices
- L352 _private member_ `std::vector<int> m_meshIndices;` — vector containing mapping mesh indices to the evaluated vertices
- L355 _private member_ `bool m_withJacobians = false;` — flag specifying whether the state has been set including Jacobians
- L358 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> m_localMatrices;` — the evaluated local transformations for each joint
- L361 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> m_worldMatrices;` — the evaluated world transformations for each joint
- L364 _private member_ `std::vector<Eigen::Transform<T, 3, Eigen::Affine>> m_skinningMatrices;` — the evaluated skinning transformations for each joint
- L367 _private member_ `int m_jointJacobianColOffset = -1;` — local caching of the jacobians for the joints
- L368 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> m_jointDeltasJacobian;`
- L369 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> m_localMatricesJacobian;`
- L370 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> m_worldMatricesJacobian;`
- L371 _private member_ `Eigen::Matrix<T, -1, -1, Eigen::RowMajor> m_skinningMatricesJacobian;`
- L392 _private member_ `std::vector<JacobianData> m_meshJacobianData;` — structure containing temporary data for jacobian calculations of the blendshapes

#### struct `RigGeometry::State::JacobianData`  
`struct JacobianData`  
_L373-389_
- L376 _public member_ `Eigen::Matrix<T, 3, -1> blendshapeVertices;` — blendshapes as they were evaluated
- L377 _public member_ `std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> blendshapeJacobianRM = std::make_shared<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>();`
- L381 _public member_ `int blendshapeJacobianColOffset = -1;`
- L384 _public member_ `Eigen::Matrix<T, 3, -1> finalVertices;` — final vertices after applying the joint evaluation
- L385 _public member_ `std::shared_ptr<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>> finalJacobianRM = std::make_shared<Eigen::Matrix<T, -1, -1, Eigen::RowMajor>>();`
- L388 _public member_ `int finalJacobianColOffset = -1;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/RigLogic.h` (Private)


#### class `RigLogic`  
`template <class T> class RigLogic`  
_L37-270_
- desc: RigLogic implements rig logic including Jacobian. Opens: - TODO: animated map clamping needs to be fixed, once clamping in RigLogic has been fixed - TODO: the clamping scheme needs to be investigated: when using clamps the Jacobians would become 0, which would hurt any optimization. currently Jacobians are not supported when clamping is enabled
- L40 _public prototype_ `RigLogic();`
- L41 _public prototype_ `~RigLogic();`
- L42 _public prototype_ `RigLogic(RigLogic&&);`
- L43 _public prototype_ `RigLogic(RigLogic&) = delete;`
- L44 _public prototype_ `RigLogic& operator=(RigLogic&&);`
- L45 _public prototype_ `RigLogic& operator=(const RigLogic&) = delete;`
- L47 _public prototype_ `std::shared_ptr<RigLogic> Clone() const;`
- L50 _public prototype_ `bool Init(const dna::Reader* reader, bool withJointScaling = false);` — Initializes RigLogic with the data from the dna::Reader
- L53 _public prototype_ `int NumGUIControls() const;` — @return the number of gui controls of the rig
- L56 _public prototype_ `int NumRawControls() const;` — @return the number of raw controls of the rig
- L59 _public prototype_ `int NumPsdControls() const;` — @return the number of psd controls of the rig
- L62 _public prototype_ `int NumMLControls() const;` — @return the number of ML controls of the rig
- L65 _public prototype_ `int NumRBFControls() const;` — @return the number of RBF controls of the rig
- L68 _public prototype_ `int NumTotalControls() const;` — @return the number of total output controls of the rig i.e. sum of raw, psd, and ml controls, and the side of the data that is output of EvaluatePSD()
- L71 _public prototype_ `int NumNeuralNetworks() const;` — @return the number of neural networks
- L77 _public prototype_ `DiffData<T> EvaluateRawControls(const DiffData<T>& guiControls) const;` — Evaluate the raw controls given the input gui controls. Throws an expection is the size is incorrect. There is no clamping involved, any gui controls exceeding their range will extrapolate the values.
- L87 _public prototype_ `DiffData<T> EvaluatePSD(const DiffData<T>& rawControls, const Eigen::VectorX<T>& maskWeights = Eigen::VectorX<T>()) const;` — Evaluates the full controls from raw controls. Throws an expection is the size is incorrect. Full controls contains [raw_controls, psd_controls, ml_controls] You would typically call it with the output from EvaluateRawControls(). @param rawControls  The raw control values. @see EvaluateRawControls() @param maskWeights  Neural networks are weighted by a mask weight. An empty vector is equivalent to weight=1. @note we may want to rename EvaluatePSD() to EvaluateControls() to be clear that it does not only refer to PSD controls.
- L99 _public prototype_ `DiffData<T> EvaluateJoints(const DiffData<T>& psdControls, int lod) const;` — Evaluate the joint values from the psd values. Throws an expection if the size is incorrect. You would typically call it with the output from EvaluatePSD().
- L106 _public prototype_ `DiffData<T> EvaluateJoints(const DiffData<T>& psdControls, const DiffDataSparseMatrix<T>& jointMatrix) const;` — Evaluate the joint values from the psd values and additionaly a specified joint matrix. Throws an expection if the size is incorrect. You would typically call it with the output from EvaluatePSD().
- L112 _public prototype_ `DiffData<T> EvaluateAnimatedMaps(const DiffData<T>& psdControls, int lod) const;` — Evaluate the animated map coefficients from the psd values. Throws an expection is the size is incorrect. You would typically call it with the output from EvaluatePSD().
- L117 _public prototype_ `const std::vector<std::string>& GuiControlNames() const;` — @return the names of the GUI controls.
- L122 _public prototype_ `const std::vector<std::string>& RawControlNames() const;` — @return the names of the raw controls.
- L127 _public prototype_ `const DriverJointControls& GetDriverJointControls() const;` — @return DriverJointControls used for evaluating directly
- L132 _public prototype_ `const std::vector<std::string>& MLControlNames() const;` — @return the names of the ML controls.
- L137 _public prototype_ `const std::vector<std::string>& RBFPoseNames() const;` — @return the names of the RBF poses.
- L142 _public prototype_ `const std::vector<std::string>& RBFPoseControlNames() const;` — @return the names of the RBF pose controls.
- L145 _public prototype_ `const std::vector<std::string>& MLNetworkNames() const;` — @return the name of neural networks
- L148 _public prototype_ `const std::vector<std::string>& GetAllControlNames() const;` — @return the name of neural networks
- L153 _public prototype_ `const Eigen::Matrix<T, 2, -1>& GuiControlRanges() const;` — @return the range of the GUI controls
- L158 _public prototype_ `int NumLODs() const;` — @return the number of LODs in the rig.
- L163 _public prototype_ `int NumJoints() const;` — @return the number of joints in the rig.
- L169 _public prototype_ `const SparseMatrix<T>& PsdToRawMap() const;` — @return the matrix mapping psd controls to raw controls i.e psd = PsdToRawMap() * rawControls. (output size NumTotalControls()) @note the first NumRawControls() rows map raw controls to itself.
- L175 _public prototype_ `const SparseMatrix<T>& JointMatrix(int lod) const;` — @return the matrix mapping psd controls to joint deltas i.e. jointDeltas = jointMatrix * psdControls Matrix size is therefore (dofPerJoint * numJoints, totalControlCount) == (jointRowCount, jointColumnCount)
- L178 _public prototype_ `void SetJointMatrix(int lod, const SparseMatrix<T>& mat);` — Set the joint matrix @p mat for lod @p load.
- L181 _public prototype_ `void ReduceToLOD0Only();` — Remove all LODs besides the highest.
- L184 _public prototype_ `bool WithJointScaling() const;` — @return whether joint scaling is output by RigLogic
- L192 _public prototype_ `std::vector<std::tuple<int, int, Eigen::VectorX<T>>> GetAllExpressions() const;` — The PSD values for all expressions (raw controls, and each corretive expression) of the rig sorted by the number of raw controls that affect the expression. @return vector with tuples containing the number of raw controls affecting the expression, the index into the PSD output (EvaluatePSD()) for the expression, and the psd control activations.
- L197 _public prototype_ `void RemoveJoints(const std::vector<int>& newToOldJointMapping);` — @brief Remove joints from RigLogic. This is being together with simplification in RigGeometry.
- L200 _public prototype_ `void ReduceToGuiControls(const std::vector<int>& guiControls);` — @brief Reduce internal PSD logic to only support @p guiControls. All other gui controls will be ignored even if the are non-zero.
- L208 _public prototype_ `Eigen::VectorX<T> GuiControlsFromRawControls(const Eigen::VectorX<T>& rawControls, std::vector<int>& inconsistentGuiControls) const;` — @brief Calculates the inverse of EvaluateRawControls i.e. gets the gui controls based on the raw controls. @param[out] inconsistentGuiControls  It is possible that the raw controls lead to inconsistent gui controls. the gui controls that are not well defined are set here. @returns the GUI controls that map to raw controls.
- L211 _public prototype_ `std::vector<int> UnusedGuiControls() const;` — @returns all gui controls that do not affect any raw control.
- L214 _public prototype_ `std::vector<int> UnusedRawControls() const;` — @returns all raw controls that are not affected by gui controls.
- L217 _public prototype_ `std::vector<int> UnmappedJoints() const;` — @returns which joints are unmapped by riglogic
- L220 _public prototype_ `int GuiControlIndex(const char* name) const;` — @returns the index for gui control @p name
- L223 _public prototype_ `int RawControlIndex(const char* name) const;` — @returns the index for raw control @p name
- L226 _public prototype_ `void MirrorJoints(const std::vector<int>& symmetricJointIndices);` — Mirror the riglogic joint activations.
- L235 _public prototype_ `std::vector<std::pair<int, T>> GetSymmetricGuiControlIndices() const;` — Get the symmetric gui control indices. Entries point to the symmetric index. The multiplier needs to be applied to the symmetric controls. This is used for controls such as CTRL_jaw.tx as it has a [-1, 1] mapping as well as the symmetric CTRL_L_eye.tx and CTRL_R_eye.tx.
- L238 _public prototype_ `std::vector<std::vector<int>> GetUsedRawControls() const;` — Get the used raw controls for a gui control
- L241 _public prototype_ `std::vector<int> GetSymmetricRawControlIndices() const;` — Get the symmetric raw control indices
- L244 _public prototype_ `std::vector<int> GetSymmetricPsdIndices() const;` — Get the symmetric psd indices
- L247 _public prototype_ `const std::vector<int>& GetJointGroupIndices() const;` — Get the joint group indices per joint
- L250 _public prototype_ `const std::vector<Eigen::VectorX<std::uint16_t>>& GetJointGroupJointIndices() const;` — Get the joint group joint indices
- L253 _public prototype_ `const std::vector<Eigen::VectorX<std::uint16_t>>& GetJointGroupInputIndices() const;` — Get the joint group input indices
- L256 _public prototype_ `const std::vector<Eigen::VectorX<std::uint16_t>>& GetJointGroupOutputIndices() const;` — Get the joint group output indices
- L259 _public prototype_ `const std::vector<Eigen::VectorX<std::uint16_t>>& GetJointGroupLODs() const;` — Get the joint group LODs
- L262 _public prototype_ `void SaveJointDeltas(dna::Writer* writer) const;` — Save joint deltas to the dna binary stream
- L265 _private prototype_ `void SortGuiControlMapping();`
- L269 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/RigLogicDNAResource.h` (Private)


#### class `RigLogicDNAResource`  
`class RigLogicDNAResource`  
_L22-46_
- desc: Wrapper to load RigLogic DNA resources.
- L25 _public prototype_ `RigLogicDNAResource();`
- L26 _public prototype_ `~RigLogicDNAResource();`
- L27 _public prototype_ `RigLogicDNAResource(RigLogicDNAResource&&);`
- L28 _public prototype_ `RigLogicDNAResource(const RigLogicDNAResource&) = delete;`
- L29 _public prototype_ `RigLogicDNAResource& operator=(RigLogicDNAResource&&);`
- L30 _public prototype_ `RigLogicDNAResource& operator=(const RigLogicDNAResource&) = delete;`
- L36 _public prototype_ `static std::shared_ptr<const RigLogicDNAResource> LoadDNA(const std::string& dnaFile, bool retain);` — Read the DNA file from \p dnaFile. @param [in] retain  Cache the resource in memory for subsequent accesses. Only necessary if the same DNA file is being loaded multiple times.
- L41 _public prototype_ `dna::Reader* Stream() const;` — Returns the pointer to the underlying RL4 BinaryStreamReader. Only valid as long as the instance is alive.
- L45 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/RigLogicSolveControls.h` (Private)


#### class `RigLogicSolveControls`  
`template <class T> class RigLogicSolveControls`  
_L17-69_
- desc: Higher level solve controls that map to GUI controls of RigLogic.
- L20 _public prototype_ `RigLogicSolveControls();`
- L21 _public prototype_ `~RigLogicSolveControls();`
- L22 _public prototype_ `RigLogicSolveControls(RigLogicSolveControls&&);`
- L23 _public prototype_ `RigLogicSolveControls(RigLogicSolveControls&) = delete;`
- L24 _public prototype_ `RigLogicSolveControls& operator=(RigLogicSolveControls&&);`
- L25 _public prototype_ `RigLogicSolveControls& operator=(const RigLogicSolveControls&) = delete;`
- L28 _public prototype_ `bool Init(const RigLogic<T>& rigLogicReference, const JsonElement& rigLogicSolveControlJson);` — Initializes RigLogicSolveControls with the rig logic reference and a json description of the solve controls
- L31 _public prototype_ `const std::string& Name() const;` — @returns the name of the riglogic solve control set
- L34 _public prototype_ `int NumSolveControls() const;` — @returns the number of solve controls of the rig
- L39 _public prototype_ `DiffData<T> EvaluateGuiControls(const DiffData<T>& solveControls) const;` — Evaluate the GUI controls given the solve controls.
- L44 _public prototype_ `const std::vector<std::string>& SolveControlNames() const;` — @returns the names of the Solve controls.
- L49 _public prototype_ `const Eigen::Matrix<T, 2, -1>& SolveControlRanges() const;` — @returns the range of the Solve controls
- L52 _public prototype_ `const Eigen::VectorX<T>& SolveControlRegularizationScaling() const;` — @returns the regularization scaling of the solve controls
- L58 _public prototype_ `Eigen::VectorX<T> SolveControlsFromGuiControls(const Eigen::VectorX<T>& guiControls, std::vector<int>& inconsistentSolveControls) const;` — Calculate solve controls from Gui Controls. @param[out] inconsistentSolveControls  Marks all solve controls that are not consistent in the mapping.
- L61 _public prototype_ `const std::vector<int>& UsedGuiControls() const;` — @returns all gui controls that are triggered by the solve controls
- L64 _public prototype_ `std::vector<std::vector<int>> UsedGuiControlsPerSolveControl() const;` — @returns per solve control which gui control is affected
- L68 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/RigUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::rigutils) template <class T> std::map<std::string, int> JointNameToIndexMap(const RigGeometry<T>& rigGeometry);`
- L17 _prototype_ `std::map<std::string, int> JointNameToIndexMap(const dna::Reader* reader);`
- L21 _prototype_ `template <class T> std::vector<Affine<T, 3, 3>> JointWorldTransforms(const RigGeometry<T>& rigGeometry);` — returns per joint rotation and translation as affine transform.
- L26 _prototype_ `template <class T> std::pair<Eigen::Matrix<T, 3, -1>, Eigen::Matrix<T, 3, -1>> CalculateLocalJointRotationAndTranslation(const RigGeometry<T>& rigGeometry, const std::vector<Affine<T, 3, 3>>& worldTransforms);` — returns per joint rotation and translation as separate data streams. Rotation is stored as Euler angles, and both rotation and translation are in local space.
- L30 _prototype_ `template <class T> std::vector<Affine<T, 3, 3>> WorldToLocalJointDeltas(const RigGeometry<T>& rigGeometry, const std::vector<Affine<T, 3, 3>>& worldJointDeltas);`
- L33 _prototype_ `void AddRBFLayerToDnaStream(dna::Reader* reader, dna::Reader* rbfReader, dna::Writer* writer);`
- L35 _prototype_ `std::vector<int> GetJointsWithVariableSkinning(const dna::Reader* reader, const std::string& regionName);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/SkinningWeightUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::skinningweightutils) template <class T> void SnapNeckSeamSkinningWeightsToBodySkinningWeights(const SparseMatrix<T>& skinningWeightsCombinedBody, const std::vector<std::pair<int, bool>>& faceBodyJointMapping, const SnapConfig<T>& snapConfig, Eigen::Matrix<T, -1, -1>& updatedHeadSkinningWeightsDense);`
- L38 _prototype_ `template <class T> std::map<int, std::vector<int>> GetJointChildrenRecursive(const JointRig2<T>& jointRig, const std::string& mustContainStr = {});` — For each joint in a joint rig, return a vector of all descendant joint indices. Optionally mass in a string (mustContainStr) which the joint name must contain to be considered for recursion (for example if you just want to consider FACIAL joints). @param[in] jointRig: the rig which we are analyzing @param[in] mustContainStr: an optional string which allows us to only consider joints which contain the supplied string (for example if we just want to consider FACIAL joints) @returns a map of joint index to a vector containing the joint indices of all the descendants of that joint
- L48 _prototype_ `template <class T> std::vector<std::pair<int, bool>> CalculateBodyFaceJointMapping(const JointRig2<T>& faceJointRig, const JointRig2<T>& bodyJointRig);` — Calculate the mapping for each body rig joint to corresponding face rig joint. If there is a match, result will contain the matching joint index and true; if not, it will be - 1 and false @param[in]: faceJointRig the face joint rig @param[in]: bodyJointRig the body joint rig @returns a vector containing for each body joint index, a pair which contains either the matching face joint index and true, or -1 and false if no match
- L58 _prototype_ `template <class T> std::vector<std::pair<int, bool>> CalculateFaceBodyJointMapping(const JointRig2<T>& faceJointRig, const JointRig2<T>& bodyJointRig);` — Calculate the mapping for each face rig joint to corresponding body rig joint. If there is a match, result will contain the matching joint index and true; if not, it will contain the facial parent joint which matches the body and false @param[in]: faceJointRig the face joint rig @param[in]: bodyJointRig the body joint rig @returns a vector containing for each face joint index, a pair which contains either the matching body joint index and true, or the corresponding body rig parent joint and false
- L73 _prototype_ `template <class T> void CalculateSkinningWeightsForBarycentricCoordinates(const std::vector<BarycentricCoordinates<T>>& barycentricCoordinates, const Eigen::Matrix<T, 3, -1>& vertices, const SparseMatrix<T>& skinningWeights, SparseMatrix<T>& outputSkinningWeights);` — Take a vector of barycentric coordinates, a corresponding matrix of vertex positions, and skinning weights for those vertices. Evaluate the barycentric coordinates and return a matrix of skinning weights for each joint, for each element of the vector of barycentric coordinates. No pruning or re-normalization is performed by this function currently, so output skinning weights will not necessarily be normalize to sum to 1 per vertex, or have the right number of influences per vertex. @param[in] barycentricCoordinates: the barycentric coordinates for each vertex for which we want to create skinning weights; for each vertex, this is the closest point on the mesh of vertices contained in vertices (typically a lower lod) @param[in] vertices: a 3 x n vertices matrix containing the coordinates of the vertices at the lower lod; this would typically be lod 0 @param[in] skinningWeights: a n vertices x n joints sparse matrix containing the skinning weights at the lower lod (typically lod 0) @param[out] outputSkinningWeights: on output will contain a matrix of barycentricCoordinates.size() x skinningWeights.cols() skinning weights which are generated by calculating a weighted sum of the source skinningWeights for each set of barycentric coordinates. The output weights are not normalized or pruned. @pre skinningWeights must contain the same number of rows as the number of columns in vertices @pre barycentric coordinates indices must be consistent with the vertices ie all indices in the ran
- L96 _prototype_ `template <class T, class R> void PropagateSkinningWeightsToHigherLOD(const std::vector<BarycentricCoordinates<T>>& higherLodBarycentricCoordinates, const Eigen::Matrix<T, 3, -1>& lowerLodVertices, const SparseMatrix<T>& lowerLodSkinningWeights, const std::map<std::string, std::map<std::string, T>>& jointMappingFromLod0, const SnapConfig<T>& lowerLodSnapConfig, const R& jointRig, int maxNumWeightsForLod, SparseMatrix<T>& outputHighLodSkinningWeights);` — Take an input sparse matrix of skinning weights which have been generated, and a 'template' matrix of skinning weights for the archetype at a (higher) required lod level, plus a corresponding joint rig, and modify the input skinning weights so that any joint influences not present in the archetype are . Finally, sort, prune and re-normalize the weights for each vertex to the required maximum number per vertex for the lod. This function assumes that the joints in different lods follow a simple parent child relationship ie at each level joint influences can simply be summed up and pushed up to their parents (as required). The function is templated on the scalar type T and also on the rig type R. This is so that it can work with both a JointRig2 and and a BodyGeometry type (which supports the required functionality) @param[in] higherLodBarycentricCoordinates: the barycentric coordinates for each vertex in the higher lod which we want to create skinning weights; for each higher lod vertex, this is the closest point on the lower lod mesh @param[in] lowerLodVertices: a 3 x n vertices matrix containing the coordinates of the vertices at the lower lod; this would typically be lod 0 @param[in] lowerLodSkinningWeights: a n vertices x n joints sparse matrix containing the skinning weights at the lower lod (typically lod 0) @params[in] jointMappingFromLod0: a map which for each joint in the rig used in lod0 defines how joint influences should be redistributed to joints in the higher lod 
- L106 _prototype_ `template <class T> void SortPruneAndRenormalizeSkinningWeights(SparseMatrix<T>& skin, int maxSkinWeights);` — sort, prune and renormalize the weights in the skinning weight matrix, limiting the influence for each vertex to maxSkinWeights joints. skin is n vertices rows x n joints columns matrix @param[out] skin: the input skinning weight matrix (n vertices rows x n joints columns) which on output will be pruned and normalized such that the joint weights for each vertex sum to 1 and no more than maxSkinWeights are > 0 @param[in] maxSkinWeights: the maximum number of joint weights for each vertex which may have a non-zero value

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/SymmetricControls.h` (Private)


#### class `SymmetricControls`  
`template <class T> class SymmetricControls`  
_L15-50_
- desc: Creates a symmetric control layer on top of the exisitng riglogic gui controls
- L18 _public prototype_ `SymmetricControls(const BodyLogic<T>& bodyLogicReference);`
- L19 _public prototype_ `~SymmetricControls();`
- L20 _public prototype_ `SymmetricControls(SymmetricControls&&);`
- L21 _public prototype_ `SymmetricControls(SymmetricControls&) = delete;`
- L22 _public prototype_ `SymmetricControls& operator=(SymmetricControls&&);`
- L23 _public prototype_ `SymmetricControls& operator=(const SymmetricControls&) = delete;`
- L26 _public prototype_ `int NumSolveControls() const;` — @returns the number of solve controls of the rig
- L31 _public prototype_ `DiffData<T> EvaluateSymmetricControls(const DiffData<T>& solveControls) const;` — Evaluate the GUI controls given the solve controls.
- L33 _public prototype_ `const Vector<T> GuiToSymmetricControls(const Vector<T>& guiControls) const;`
- L34 _public prototype_ `const Vector<T> SymmetricToGuiControls(const Vector<T>& symmetricControls) const;`
- L36 _public prototype_ `const std::vector<int> GetSymmetryMapping() const;`
- L37 _public prototype_ `const std::vector<std::string>& GetControlNames() const;`
- L39 _public prototype_ `std::vector<int> GuiIndicesToSymmetricIndices(const std::vector<int>& guiIndices) const;`
- L41 _public prototype_ `std::vector<int> GetSymmetricGuiIndices() const;`
- L43 _public prototype_ `std::vector<int> GetNonSymmetricGuiIndices() const;`
- L45 _public prototype_ `const Eigen::SparseMatrix<T, Eigen::RowMajor>& SymmetricToGuiControlsMatrix() const;`
- L49 _private member_ `TITAN_NAMESPACE::Pimpl<Private> m;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/TwistSwingLogic.h` (Private)


#### class `TwistSwingLogic`  
`template <class T> class TwistSwingLogic`  
_L20-44_
- L24 _public prototype_ `TwistSwingLogic();`
- L25 _public prototype_ `~TwistSwingLogic();`
- L27 _public prototype_ `TwistSwingLogic(TwistSwingLogic&&);`
- L28 _public prototype_ `TwistSwingLogic& operator=(TwistSwingLogic&&);`
- L30 _public prototype_ `TwistSwingLogic(const TwistSwingLogic&);`
- L31 _public prototype_ `TwistSwingLogic& operator=(const TwistSwingLogic&);`
- L33 _public prototype_ `DiffData<T> EvaluateJointsFromJoints(const DiffData<T>& jointDiff) const;`
- L34 _public prototype_ `DiffData<T> EvaluateJointsFromRawControls(const DiffData<T>& rawControls) const;`
- L36 _public prototype_ `void RemoveJoints(const std::vector<int>& newToOldJointMapping);`
- L38 _public prototype_ `bool Init(const dna::Reader* reader, bool withJointScaling = false);`
- L39 _public prototype_ `void Write(dna::Writer* writer);`
- L43 _private member_ `Pimpl<Private> m;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace dna`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/rbfs/AdditiveRBFSolver.h` (Private)


#### class `AdditiveRBFSolver`  
`class AdditiveRBFSolver : public RBFSolverBase`  
_L10-19_
- inherits: `RBFSolverBase`
- L12 _public prototype_ `explicit AdditiveRBFSolver(pma::MemoryResource* memRes);`
- L13 _public prototype_ `AdditiveRBFSolver(const RBFSolverRecipe& recipe, pma::MemoryResource* memRes);`
- L14 _public prototype_ `explicit AdditiveRBFSolver(const RBFSolverBase* other);`
- L17 _public prototype_ `RBFSolverType getSolverType() const override;`
- L18 _public prototype_ `void solve(dna::ArrayView<float> input, dna::ArrayView<float> intermediateWeights, dna::ArrayView<float> outputWeights) const override;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/rbfs/InterpolativeRBFSolver.h` (Private)


#### class `InterpolativeRBFSolver`  
`class InterpolativeRBFSolver : public RBFSolverBase`  
_L10-24_
- inherits: `RBFSolverBase`
- L12 _public prototype_ `InterpolativeRBFSolver(const RBFSolverRecipe& recipe, pma::MemoryResource* memRes);`
- L13 _public prototype_ `explicit InterpolativeRBFSolver(InterpolativeRBFSolver* other);`
- L14 _public prototype_ `explicit InterpolativeRBFSolver(pma::MemoryResource* memRes);`
- L17 _public prototype_ `RBFSolverType getSolverType() const override;`
- L18 _public prototype_ `void solve(dna::ArrayView<float> input, dna::ArrayView<float> intermediateWeights, dna::ArrayView<float> outputWeights) const override;`
- L20 _public prototype_ `const Matrix<float>& getCoefficients() const;`
- L23 _private member_ `Matrix<float> coefficients;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/rbfs/RBFSolver.h` (Private)


#### enum `RBFSolverType`  
`enum class RBFSolverType`  
_L20-34_
- L25 _public enumerator_ `Additive` — The additive solver sums up contributions from each target. It's faster but may require more targets for a good coverage, and requires the normalization step to be performed for smooth results.
- L33 _public enumerator_ `Interpolative` — The interpolative solver interpolates the values from each target based on distance. As long as the input values are within the area bounded by the targets, the interpolation is well-behaved and returns weight values within the 0% - 100% limit with no normalization required. Interpolation also gives smoother results, with fewer targets than additive solver, but at a higher computational cost.

#### enum `RBFFunctionType`  
`enum class RBFFunctionType`  
_L36-42_
- L37 _public enumerator_ `Gaussian`
- L38 _public enumerator_ `Exponential`
- L39 _public enumerator_ `Linear`
- L40 _public enumerator_ `Cubic`
- L41 _public enumerator_ `Quintic`

#### enum `RBFDistanceMethod`  
`enum class RBFDistanceMethod`  
_L44-53_
- L46 _public enumerator_ `Euclidean` — Standard n-dimensional distance measure
- L48 _public enumerator_ `Quaternion` — Treat inputs as quaternion
- L50 _public enumerator_ `SwingAngle` — Treat inputs as quaternion, and find distance between rotated TwistAxis direction
- L52 _public enumerator_ `TwistAngle` — Treat inputs as half quaternion, and find distance between rotations around the TwistAxis direction

#### enum `RBFNormalizeMethod`  
`enum class RBFNormalizeMethod`  
_L55-58_
- L56 _public enumerator_ `OnlyNormalizeAboveOne`
- L57 _public enumerator_ `AlwaysNormalize`

#### enum `AutomaticRadius`  
`enum class AutomaticRadius`  
_L60-63_
- L61 _public enumerator_ `On`
- L62 _public enumerator_ `Off`

#### enum `TwistAxis`  
`enum class TwistAxis`  
_L65-69_
- L66 _public enumerator_ `X`
- L67 _public enumerator_ `Y`
- L68 _public enumerator_ `Z`

#### struct `RBFSolverRecipe`  
`struct RBFSolverRecipe`  
_L71-83_
- L72 _public member_ `RBFSolverType solverType;`
- L73 _public member_ `RBFDistanceMethod distanceMethod;`
- L74 _public member_ `RBFFunctionType weightFunction;`
- L75 _public member_ `RBFNormalizeMethod normalizeMethod;`
- L76 _public member_ `TwistAxis twistAxis;`
- L77 _public member_ `bool isAutomaticRadius;`
- L78 _public member_ `float radius;`
- L79 _public member_ `float weightThreshold;`
- L80 _public member_ `std::uint16_t rawControlCount;`
- L81 _public member_ `dna::ConstArrayView<float> targetValues;`
- L82 _public member_ `dna::ConstArrayView<float> targetScales;`

#### class `RBFSolver`  
`class RBFSolver`  
_L85-110_
- L87 _public prototype_ `static RBFSolver* create(RBFSolverRecipe recipe, pma::MemoryResource* memRes = nullptr);`
- L88 _public prototype_ `static RBFSolver* create(pma::MemoryResource* memRes = nullptr);`
- L89 _public prototype_ `static RBFSolver* create(RBFSolver* other);`
- L91 _public prototype_ `static void destroy(RBFSolver* instance);`
- L94 _public prototype_ `virtual ~RBFSolver();`
- L96 _public prototype_ `virtual RBFSolverType getSolverType() const = 0;`
- L97 _public prototype_ `virtual void solve(dna::ArrayView<float> input, dna::ArrayView<float> intermediateWeights, dna::ArrayView<float> outputWeights) const = 0;`
- L100 _public prototype_ `virtual dna::ConstArrayView<float> getTarget(std::uint16_t targetIndex) const = 0;`
- L101 _public prototype_ `virtual std::uint16_t getTargetCount() const = 0;`
- L103 _public prototype_ `virtual dna::ConstArrayView<float> getTargetScales() const = 0;`
- L104 _public prototype_ `virtual float getRadius() const = 0;`
- L105 _public prototype_ `virtual float getWeightThreshold() const = 0;`
- L106 _public prototype_ `virtual RBFDistanceMethod getDistanceMethod() const = 0;`
- L107 _public prototype_ `virtual RBFFunctionType getWeightFunction() const = 0;`
- L108 _public prototype_ `virtual RBFNormalizeMethod getNormalizeMethod() const = 0;`
- L109 _public prototype_ `virtual TwistAxis getTwistAxis() const = 0;`

#### struct `pma::DefaultInstanceCreator`  
`template<> struct DefaultInstanceCreator<TITAN_NAMESPACE::rbfs::RBFSolver>`  
_L117-119_
- L118 _public typedef_ `using type = FactoryCreate<TITAN_NAMESPACE::rbfs::RBFSolver>;`

#### struct `pma::DefaultInstanceDestroyer`  
`template<> struct DefaultInstanceDestroyer<TITAN_NAMESPACE::rbfs::RBFSolver>`  
_L122-124_
- L123 _public typedef_ `using type = FactoryDestroy<TITAN_NAMESPACE::rbfs::RBFSolver>;`

#### Free symbols / members of external scopes

- L114 _namespace_ `namespace pma`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/rbfs/RBFSolverBase.h` (Private)


#### class `RBFSolverBase`  
`class RBFSolverBase : public RBFSolver`  
_L37-81_
- inherits: `RBFSolver`
- L40 _public typedef_ `using DistanceWeightFun = std::function<void (dna::ConstArrayView<AlignedVector<float> >, dna::ConstArrayView<float>, dna::ArrayView<float>, float)>;`
- L43 _public typedef_ `using InputConvertFun = std::function<void (dna::ArrayView<float>)>;`
- L45 _public prototype_ `explicit RBFSolverBase(dna::MemoryResource* memRes);`
- L46 _public prototype_ `RBFSolverBase(const RBFSolverRecipe& recipe, dna::MemoryResource* memRes);`
- L48 _public prototype_ `virtual ~RBFSolverBase() = 0;`
- L50 _public prototype_ `RBFSolverBase& operator=(const RBFSolverBase&) = default;`
- L51 _public prototype_ `RBFSolverBase(const RBFSolverBase&) = default;`
- L54 _public prototype_ `dna::MemoryResource* getMemoryResource() const;`
- L56 _public prototype_ `dna::ConstArrayView<float> getTarget(std::uint16_t targetIndex) const override;`
- L57 _public prototype_ `std::uint16_t getTargetCount() const override;`
- L59 _public prototype_ `dna::ConstArrayView<float> getTargetScales() const override;`
- L60 _public prototype_ `float getRadius() const override;`
- L61 _public prototype_ `float getWeightThreshold() const override;`
- L62 _public prototype_ `RBFDistanceMethod getDistanceMethod() const override;`
- L63 _public prototype_ `RBFFunctionType getWeightFunction() const override;`
- L64 _public prototype_ `RBFNormalizeMethod getNormalizeMethod() const override;`
- L65 _public prototype_ `TwistAxis getTwistAxis() const override;`
- L68 _protected prototype_ `void normalizeAndCutOff(dna::ArrayView<float> outputWeights) const;`
- L71 _protected member_ `dna::Vector<AlignedVector<float> > targets;`
- L72 _protected member_ `dna::Vector<float> targetScale;`
- L73 _protected member_ `DistanceWeightFun getDistanceWeight;`
- L74 _protected member_ `InputConvertFun convertInput;`
- L75 _protected member_ `float radius;`
- L76 _protected member_ `float weightThreshold;`
- L77 _protected member_ `RBFDistanceMethod distanceMethod;`
- L78 _protected member_ `RBFFunctionType weightFunction;`
- L79 _protected member_ `RBFNormalizeMethod normalizeMethod;`
- L80 _protected member_ `TwistAxis twistAxis;`

#### Free symbols / members of external scopes

- L23 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE::rbfs) static constexpr std::size_t cacheLineAlignment = 64ul;`
- L28 _typedef_ `template<typename T> using AlignedAllocator = pma::PolyAllocator<T, cacheLineAlignment, pma::AlignedMemoryResource>;`
- L31 _typedef_ `template<typename T> using AlignedVector = pma::Vector<T, AlignedAllocator<T>>;`
- L34 _typedef_ `template<typename T, typename Allocator = pma::PolyAllocator<pma::Vector<T> > > using Matrix = pma::Vector<pma::Vector<T>, Allocator>;`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/rbfs/TDMQuaternionJacobian.h` (Private)


#### struct `SlerpJacobian`  
`template <class T> struct SlerpJacobian`  
_L151-156_
- L152 _public member_ `Eigen::Matrix<T,4,4> dqdq1;` — derivative of q wrt q1
- L153 _public member_ `Eigen::Matrix<T,4,4> dqdq2;` — derivative of q wrt q2
- L154 _public member_ `Eigen::Matrix<T,4,1> dqdt;` — derivative of q wrt t
- L155 _public member_ `tdm::quat<T> q;` — slerp result (x,y,z,w)

#### Free symbols / members of external scopes

- L18 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) template <class T> Eigen::Matrix<T, 3, 4> QuaternionToEulerXYZJacobian(const tdm::quat<T>& q)`
- L96 _function_ `template <typename T> Eigen::Matrix<T, 4, 4> QuaternionNormalizationJacobian(const tdm::quat<T>& quat)`
- L106 _function_ `template <class T> Eigen::Matrix<T, 4, 3> EulerXYZToQuaternionJacobian(const tdm::rad3<T>& rot)`
- L159 _function_ `template <class T> inline SlerpJacobian<T> SlerpJacobianAll(const tdm::quat<T>& q1, const tdm::quat<T>& q2, T t)`
- L174 _function_ `auto asEigen = [](const tdm::quat<T> q)` (scope `SlerpJacobianAll`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/serialization/DirectoryMeshReader.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE)`
- L19 _prototype_ `template <class T> Mesh<T> ReadMeshFromObjOrDNA(const std::string& filename, int meshId);` — meshId used only when loading DNA files (0 - head, 1 - teeth, 3 - left eye, 4 - right eye)
- L21 _prototype_ `std::vector<std::string> GetObjsOrDNAsFromDirectory(const std::string& dir, bool objOnly = false);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/rig/include/rig/serialization/JointRigSerialization.h` (Private)


#### Free symbols / members of external scopes

- L12 _function_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) /** * Deserializes the joint rig from json format. * * TODO: open questions: how to handle the case when the root node itself has a parent with * a global transformation. For now we ignore the case and throw an exception if the local and bind pose of the root node do not match. * * Format for joints: * joints`
- L43 _typedef_ `using T = typename JointHelper<AffineType>::SCALAR;` (scope `CARBON_NAMESPACE_BEGIN`)
- L44 _typedef_ `using Joint = TITAN_NAMESPACE::Joint<AffineType>;` (scope `CARBON_NAMESPACE_BEGIN`)
- L45 _typedef_ `using JointPtr = std::shared_ptr<Joint>;` (scope `CARBON_NAMESPACE_BEGIN`)
- L139 _function_ `template <class AffineType> void JointRigStateFromJson(const JsonElement& j, JointRig<AffineType>& jointRig)` — Deserializes the joint state from json format i.e. it only reads the local transformation matrix per joint Format for joint states (note that any other entries in the dictionaries are ignored) joints { “name of joint” : { “local”: 4x4 matrix (column major, pre multiply - should be possible to calculate it from the parent) }, ... (next joint) }
- L143 _typedef_ `using T = typename JointHelper<AffineType>::SCALAR;` (scope `JointRigStateFromJson`)
- L159 _function_ `template <class AffineType> JsonElement JointRigStateToJson(const JointRig<AffineType>& jointRig)` — Serializes the joint state to json format i.e. it only writes the local transformation matrix per joint. @see JointRigStateFromJson
- L161 _typedef_ `using T = typename JointHelper<AffineType>::SCALAR;` (scope `JointRigStateToJson`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/robustfeaturematcher/include/robustfeaturematcher/Features.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) void computeImageFeatures(const std::vector<Eigen::MatrixX<real_t>>& images, RobustFeatureMatcherParams appData, std::vector<Eigen::MatrixX<real_t>>& kptsMatrices, std::vector<Eigen::MatrixX<real_t>>& descriptors, size_t ptsNumThreshold = 100000);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/robustfeaturematcher/include/robustfeaturematcher/ImageFeatures.h` (Private)


#### struct `calib::rfm::Match`  
`struct Match`  
_L17-23_
- L18 _public member_ `Eigen::Vector2<real_t> keypointLeft;`
- L19 _public member_ `Eigen::Vector2<real_t> keypointRight;`
- L20 _public member_ `size_t matchId;`
- L21 _public member_ `MetaShapeCamera<real_t> refCamera;`
- L22 _public member_ `MetaShapeCamera<real_t> pairCamera;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace calib`
- L16 _namespace_ `namespace rfm` (scope `calib`)
- L25 _prototype_ `std::vector<Match> featureMatching(const Eigen::MatrixX<real_t>& descriptor1, const Eigen::MatrixX<real_t>& descriptor2, const Eigen::MatrixX<real_t>& keypoints1, const Eigen::MatrixX<real_t>& keypoints2, const MetaShapeCamera<real_t>& refCamera, const MetaShapeCamera<real_t>& pairCamera, real_t ratioThreshold, int& currMaxId, int offset, int featureDetectorType = 0);` (scope `calib::rfm`)
- L35 _prototype_ `void featureDetection(const Eigen::MatrixX<real_t>& img, Eigen::MatrixX<real_t>& kptsMatrix, Eigen::MatrixX<real_t>& desc, size_t ptsNumThreshold = 200000, int featureDetectorType = 0);` (scope `calib::rfm`)
- L40 _prototype_ `Eigen::Vector3<real_t> triangulateMatch(const MetaShapeCamera<real_t>& leftCamera, const MetaShapeCamera<real_t>& rightCamera, const Eigen::MatrixX<real_t>& leftPt, const Eigen::MatrixX<real_t>& rightPt);` (scope `calib::rfm`)
- L44 _prototype_ `void createMultiViewScene(const std::vector<calib::rfm::Match>& matches, const std::vector<MetaShapeCamera<real_t>>& cameras, std::vector<Eigen::MatrixX<real_t>>& cameraPoints, Eigen::MatrixX<real_t>& pts3d, std::vector<Eigen::MatrixX<real_t>>& pts3dReprojected, std::vector<std::vector<bool>>& vis, real_t reprojFilterThresh);` (scope `calib::rfm`)
- L51 _prototype_ `Eigen::MatrixX<real_t>applyClahe(const Eigen::MatrixX<real_t>& image, int limit);` (scope `calib::rfm`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/robustfeaturematcher/include/robustfeaturematcher/Matches.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `CARBON_NAMESPACE_BEGIN(TITAN_NAMESPACE) void computeMatches(const std::vector<Eigen::MatrixX<real_t>>& kptsMatrices, const std::vector<Eigen::MatrixX<real_t>>& descriptors, const std::vector<MetaShapeCamera<real_t>>& cameras, const RobustFeatureMatcherParams& appData, std::vector<calib::rfm::Match>& matches);`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/robustfeaturematcher/include/robustfeaturematcher/RobustFeatureMatcherContext.h` (Private)


#### class `RobustFeatureMatcherContext`  
`class RobustFeatureMatcherContext`  
_L26-125_
- desc: @brief RobustFeatureMatcherContext is high-level API class which unifies objects and functionalities and makes it easy to create a scene for bundle adjustment.
- L29 _public prototype_ `RobustFeatureMatcherContext() = default;`
- L30 _public prototype_ `~RobustFeatureMatcherContext() = default;`
- L41 _public prototype_ `void setParams(const RobustFeatureMatcherParams& parameters);` — @brief Sets the data description object, which contains all neccessary data: cameras, calibration and images. @param parameters Object representing data description
- L49 _public prototype_ `std::vector<TITAN_NAMESPACE::MetaShapeCamera<real_t> >& getCameras();` — @brief Get all camera models @return Array of CameraModel objects.
- L51 _public prototype_ `size_t getFeatureNumThreshold();`
- L53 _public prototype_ `void setFeatureNumThreshold(size_t threshold);`
- L61 _public prototype_ `void computeFeaturesAndMatches(size_t frame, const std::vector<const unsigned char*>& images);` — @brief Compute matches between stereo pair images. @return Vector of matches.
- L69 _public prototype_ `void computeFeaturesAndMatches(const std::map<size_t, std::vector<const unsigned char*>>& images);` — @brief Compute matches between list of stereo pair images. @return Vector of matches.
- L77 _public prototype_ `std::map<size_t,std::vector<calib::rfm::Match>> getMatches() const;` — @brief Get matches between images computed in computeFeaturesAndMatches() method. @return Vector of matches.
- L85 _public prototype_ `std::vector<calib::rfm::Match> getMatches(size_t frame) const;` — @brief Get matches between images computed in computeFeaturesAndMatches(size_t frame) method. @return Vector of matches.
- L90 _public prototype_ `void createScene(size_t frame);` — @brief Create multi-view scene for a frame (image points, 3d points and visibility information)
- L95 _public prototype_ `void createScene();` — @brief Create multi-view scene for all the matched frames (image points, 3d points and visibility information)
- L100 _public prototype_ `void getScene(size_t frame, Eigen::MatrixX<real_t>& outPts3d, std::vector<std::vector<bool>>& outVisibility, std::vector<Eigen::MatrixX<real_t>>& outCameraPoints, std::vector<Eigen::MatrixX<real_t>>& outPts3dReprojected) const;` — @brief get the scene of specified frame: image points, 3d reconstructions, reprojectd reconstructions and visibility
- L109 _public prototype_ `void getScene(std::map<size_t, Eigen::MatrixX<real_t>>& outPts3d, std::map<size_t, std::vector<std::vector<bool>>>& outVisibility, std::map<size_t, std::vector<Eigen::MatrixX<real_t>>>& outCameraPoints, std::map<size_t, std::vector<Eigen::MatrixX<real_t>>>& outPts3dReprojected) const;` — @brief get the scene of all matched frames: image points, 3d reconstructions, reprojectd reconstructions and visibility
- L115 _private member_ `RobustFeatureMatcherParams params;`
- L116 _private member_ `std::vector<TITAN_NAMESPACE::MetaShapeCamera<real_t>> cameras;`
- L117 _private member_ `std::map<size_t, std::vector<Eigen::MatrixX<real_t>>> kptsMatrices;`
- L118 _private member_ `std::map<size_t, std::vector<Eigen::MatrixX<real_t>>> descriptors;`
- L119 _private member_ `std::map<size_t, std::vector<calib::rfm::Match>> matches;`
- L120 _private member_ `std::map<size_t, Eigen::MatrixX<real_t>> pts3d;`
- L121 _private member_ `std::map<size_t, std::vector<std::vector<bool>>> visibility;`
- L122 _private member_ `std::map<size_t, std::vector<Eigen::MatrixX<real_t>>> cameraPoints;`
- L123 _private member_ `std::map<size_t, std::vector<Eigen::MatrixX<real_t>>> pts3dReprojected;`
- L124 _private member_ `size_t ptsNumThreshold{ 200000 };`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/robustfeaturematcher/include/robustfeaturematcher/RobustFeatureMatcherParams.h` (Private)


#### class `RobustFeatureMatcherParams`  
`class RobustFeatureMatcherParams`  
_L14-100_
- L17 _public prototype_ `RobustFeatureMatcherParams() = default;`
- L26 _public function_ `std::vector<std::string> getCameraLabels() const`
- L35 _public function_ `std::vector<Camera> getCameras() const`
- L39 _public function_ `void addCamera(const Camera& camera)`
- L43 _public function_ `std::optional<Camera> getCamera(const std::string& cameraLabel)`
- L56 _public function_ `const std::vector<MetaShapeCamera<real_t>>& getMetaShapeCameras() const`
- L60 _public function_ `void setMetaShapeCameras(const std::vector<MetaShapeCamera<real_t>>& calibs)`
- L64 _public function_ `void setMetaShapeCamerasFromFile(const std::string& inputFilePath)`
- L68 _public function_ `real_t getReprojectionThreshold() const`
- L72 _public function_ `void setReprojectionThreshold(real_t reprojectionThresh)`
- L76 _public function_ `real_t getRatioThreshold() const`
- L80 _public function_ `void setRatioThreshold(real_t ratioThresh)`
- L85 _public function_ `int getFeatureDetectorType() const` — 0 = SlowPrecise (SIFT/BRUTEFORCE), 1 = FastLessPrecise (AKAZE/BRUTEFORCE_HAMMING)
- L89 _public function_ `void setFeatureDetectorType(int detectorType)`
- L94 _private member_ `std::vector<Camera> cameras;`
- L95 _private member_ `std::vector<MetaShapeCamera<real_t>> calibrations;`
- L97 _private member_ `real_t reprojectionThreshold = 0.0;`
- L98 _private member_ `real_t ratioThreshold = 0.0;`
- L99 _private member_ `int featureDetectorType = 0;` — 0 = SlowPrecise (SIFT), 1 = FastLessPrecise (AKAZE)

#### struct `RobustFeatureMatcherParams::Camera`  
`struct Camera`  
_L19-24_
- L21 _public member_ `std::string name;`
- L22 _public member_ `int32_t width;`
- L23 _public member_ `int32_t height;`

#### Free symbols / members of external scopes

- L28 _function_ `std::transform(cameras.begin(), cameras.end(), std::back_inserter(cameraLabels), [](const Camera& camera) { return camera.name; });` (scope `RobustFeatureMatcherParams::getCameraLabels`)
- L45 _function_ `std::find_if(cameras.begin(), cameras.end(), [&cameraLabel](const Camera& camera) { return camera.name == cameraLabel; });` (scope `RobustFeatureMatcherParams::getCamera`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Private/robustfeaturematcher/include/robustfeaturematcher/UtilsCamera.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace calib`
- L15 _namespace_ `namespace rfm` (scope `calib`)
- L17 _prototype_ `void adjustNlsCamera(const MetaShapeCamera<real_t>& camera, Eigen::Matrix3<real_t>& K, Eigen::VectorX<real_t>& D);` (scope `calib::rfm`)
- L18 _prototype_ `real_t computeEuclidDistance(Eigen::Vector3<real_t> point1, Eigen::Vector3<real_t> point2);` (scope `calib::rfm`)
- L19 _prototype_ `std::vector<std::vector<size_t>> getCameraPairs(const std::vector<Camera*>& cameras);` (scope `calib::rfm`)
- L20 _prototype_ `MetaShapeCamera<real_t> findCameraByLabel(std::vector<MetaShapeCamera<real_t>> cameras, std::string cameraLabel, int& id);` (scope `calib::rfm`)
- L23 _prototype_ `bool compareCalibrations(std::vector<MetaShapeCamera<real_t>> cameras, std::vector<MetaShapeCamera<real_t>> priorCameras, const real_t angleThreshold, const real_t distanceThreshold);` (scope `calib::rfm`)
- L27 _prototype_ `std::map<std::string, size_t> tagToId(const std::vector<MetaShapeCamera<real_t>>& cameras);` (scope `calib::rfm`)
- L28 _prototype_ `void writePly(const Eigen::MatrixX<real_t>& points3d);` (scope `calib::rfm`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Public/MetaHumanCalibrationLib.h` (Public)


#### class `FMetaHumanCalibrationLibModule`  
`class FMetaHumanCalibrationLibModule : public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- L14 _public prototype_ `static FString GetVersion();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANCALIBRATIONLIB_API`

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Public/MetaHumanRobustFeatureMatcher.h` (Public)


#### class `UE::Wrappers::FMetaHumanRobustFeatureMatcher`  
`class FMetaHumanRobustFeatureMatcher`  
_L16-78_
- L20 _public prototype_ `FMetaHumanRobustFeatureMatcher();`
- L29 _public prototype_ `bool Init(const TArray<FCameraCalibration>& InCameraCalibrations, double InReprojectionThreshold = 5.0, double InRatioThreshold = 0.75);` — Initialize robust feature matcher. @param[in] InCameraCalibrations An array of camera calibrations @param[in] InReprojectionThreshold Max allowed reprojection error (in pixels) to consider a 3D-2D correspondence @param[in] InRatioThreshold Ratio used for comparing best match distance to second-best; keeps match if sufficiently better @returns True if initialization is successful, False otherwise.
- L40 _public prototype_ `UE_INTERNAL bool Init(const FString& InCameraCalibrationFile, double InReprojectionThreshold = 5.0, double InRatioThreshold = 0.75);` — Initialize robust feature matcher. @param[in] InCameraCalibrationFile Camera Calibration file @param[in] InReprojectionThreshold Max allowed reprojection error (in pixels) to consider a 3D-2D correspondence @param[in] InRatioThreshold Ratio used for comparing best match distance to second-best; keeps match if sufficiently better @returns True if initialization is successful, False otherwise.
- L51 _public prototype_ `bool AddCamera(const FString& InCameraName, int32 InWidth, int32 InHeight);` — Adds a footage information for the camera. @param[in] InCameraName Name of the camera used for calibration @param[in] InWidth Image width @param[in] InHeight Image height @returns True if adding is successful, False otherwise.
- L59 _public prototype_ `bool DetectFeatures(int64 InFrame, const TArray<const unsigned char*>& InImages);` — Detects the matching features for the cameras. @param[in] InFrame Frame index @param[in] InImages Image data for all cameras for a specified frame @returns True if matching is successful, False otherwise.
- L69 _public prototype_ `bool GetFeatures(int64 InFrame, TArray<FVector>& OutPoints3d, TArray<TArray<FVector2D>>& OutCameraPoints, TArray<TArray<FVector2D>>& OutPoints3dReprojected);` — Provides the matching features for the cameras. @param[in] InFrame Frame index @param[out] OutPoints3d Triangulated 3D coordinates of calibration target points in stereo camera frame @param[out] OutCameraPoints 2D detected points in each image @param[out] OutPoints3dReprojected 2D points obtained by projecting Points3D back into the image using camera calibration @returns True if matching is successful, False otherwise.
- L77 _private member_ `TPimplPtr<FPrivate> ImplPtr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCALIBRATIONLIB_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Wrappers` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationLib/Public/MetaHumanStereoCalibrator.h` (Public)


#### class `UE::Wrappers::FMetaHumanStereoCalibrator`  
`class FMetaHumanStereoCalibrator`  
_L15-68_
- L18 _public prototype_ `FMetaHumanStereoCalibrator();`
- L27 _public prototype_ `bool Init(uint32 PatternWidth, uint32 PatternHeight, float SquareSize);` — Initialize multi camera calibration. @param[in] InPatternWidth The number of inner corners on the chessboard pattern wide @param[in] InPatternHeight The number of inner corners on the chessboard pattern high @param[in] InPatternSquareSize The size of the square on the chessboard pattern in cm @returns True if initialization is successful, False otherwise.
- L36 _public prototype_ `bool AddCamera(const FString& InCameraName, uint32 InWidth, uint32 InHeight);` — Adds a camera view used for calibration @param[in] InCameraName The name of the camera view @param[in] InWidth The width of the camera image in pixels @param[in] InHeight The height of the camera image in pixels @returns True if successful, false upon any error.
- L46 _public prototype_ `bool DetectPattern(const FString& InCameraName, const unsigned char* InImage, TArray<FVector2D>& OutCornerPoints, double& OutChessboardSharpness);` — Detects the corner points in the image of a chessboard pattern. Calculates an average sharpness of the corner points in the image @param[in] InCameraName The name of the camera view @param[in] InImage The image of the chessboard pattern @param[out] OutPoints The corner points detected in the image @param[out] OutChessboardSharpness The estimated sharpness of the corner points in the image points detected in the image @returns True if successful, false if chessboard pattern is not detected.
- L55 _public prototype_ `bool Calibrate(const TArray<TMap<FString, TArray<FVector2D>>>& InPointsPerCameraPerFrame, TArray<FCameraCalibration>& OutCalibrations, double& OutMse);` — Calibrates the intrinsics and extrinsics of the added cameras @param[in] InCornerPointsPerCameraPerFrame The detected corner points per camera per frame @param[out] OutCalibrations A array of the calibrated cameras @param[out] OutMSE The reprojection error from the calibration @returns True if successful, false upon any error.
- L63 _public prototype_ `bool ExportCalibrations(const TArray<FCameraCalibration>& InCalibrations, const FString& ExportFilepath);` — Exports the results of Calibrate to a json file @param[in] InCalibrations A array of the calibrated cameras @param[in] InExportFilepath The filepath the calibration json will be written to @returns True if successful, false upon any error.
- L67 _private member_ `TPimplPtr<Private> Impl;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCALIBRATIONLIB_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Wrappers` (scope `UE`)
