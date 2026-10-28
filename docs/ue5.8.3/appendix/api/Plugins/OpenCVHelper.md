# Plugins / OpenCVHelper

- module root: `Plugins/Runtime/OpenCV/Source/OpenCVHelper`
- headers: 6; symbols: 118
- symbol kinds: class=3, delegate=1, enum=4, enumerator=33, function=7, macro=4, member=25, namespace=2, prototype=30, struct=5, typedef=4
- PrivateDependencyModuleNames: OpenCV, Projects
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/OpenCV/Source/OpenCVHelper/Public/IOpenCVHelperModule.h` (Public)


#### class `IOpenCVHelperModule`  
`class IOpenCVHelperModule : public IModuleInterface`  
_L11-16_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual ~IOpenCVHelperModule() = default;` — Virtual destructor.

### `Plugins/Runtime/OpenCV/Source/OpenCVHelper/Public/OpenCVBlueprintFunctionLibrary.h` (Public)


#### enum `EOpenCVArucoDictionary`  
`enum class EOpenCVArucoDictionary : uint8`  
_L19-26_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `Dict4x4 UMETA(DisplayName = "4x4")`
- L22 _public enumerator_ `Dict5x5 UMETA(DisplayName = "5x5")`
- L23 _public enumerator_ `Dict6x6 UMETA(DisplayName = "6x6")`
- L24 _public enumerator_ `Dict7x7 UMETA(DisplayName = "7x7")`
- L25 _public enumerator_ `DictOriginal UMETA(DisplayName = "Original")`

#### enum `EOpenCVArucoDictionarySize`  
`enum class EOpenCVArucoDictionarySize : uint8`  
_L29-35_
- reflection: `UENUM(BlueprintType)`
- L31 _public enumerator_ `DictSize50 UMETA(DisplayName = "50")`
- L32 _public enumerator_ `DictSize100 UMETA(DisplayName = "100")`
- L33 _public enumerator_ `DictSize250 UMETA(DisplayName = "250")`
- L34 _public enumerator_ `DictSize1000 UMETA(DisplayName = "1000")`

#### struct `FOpenCVArucoDetectedMarker`  
`struct FOpenCVArucoDetectedMarker`  
_L38-55_
- reflection: `USTRUCT(BlueprintType)`
- L42 _public function_ `FOpenCVArucoDetectedMarker() : Id(-1)`
- L48 _public member_ `int32 Id;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenCV | ArUco")`
- L51 _public member_ `TArray<FVector2D> Corners;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenCV | ArUco")`
- L54 _public member_ `FTransform Pose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenCV | ArUco")`

#### class `UOpenCVBlueprintFunctionLibrary`  
`class UOpenCVBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L58-92_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- L74 _public prototype_ `static int32 OpenCVChessboardDetectCorners(const UTextureRenderTarget2D* InRenderTarget, const FIntPoint InPatternSize, const bool bDebugDrawCorners, UTexture2D*& OutDebugTexture, TArray<FVector2D>& OutDetectedCorners);` — `UFUNCTION(BlueprintCallable, Category = "OpenCV", Meta = (DisplayName = "OpenCV Chessboard Detect Corners"))` — Detects a camera calibration chessboard in the supplied image @param InRenderTarget Input image in which to search for a chessboard @param InPatternSize Number of interior corners on the physical chessboard (rows, columns) @param bDebugDrawCorners If true, output a Texture2D showing the detected corner debug info overlaid on the input image @param OutDebugTexture Output debug image (required if bDebugDrawCorners is True) @param OutDetectedCorners Output array of corners detected in the input image @return Total number of corners detected in the input image
- L91 _public prototype_ `static int32 OpenCVArucoDetectMarkers(const UTextureRenderTarget2D* InRenderTarget, const EOpenCVArucoDictionary InDictionary, const EOpenCVArucoDictionarySize InDictionarySize, const bool bDebugDrawMarkers, const bool bEstimatePose, const float InMarkerLengthInMeters, const FOpenCVLensDistortionParametersBase& InLensDistortionParameters, UTexture2D*& OutDebugTexture, TArray<FOpenCVArucoDetectedMarker>& OutDetectedMarkers);` — `UFUNCTION(BlueprintCallable, Category = "OpenCV | ArUco", Meta = (DisplayName = "OpenCV ArUco Detect Markers"))` — Detects all ArUco markers in the supplied image @param InRenderTarget Input image in which to search for markers @param InDictionary Which ArUco marker dictionary to use for detection @param InDictionarySize The size of the ArUco marker dictionary @param bDebugDrawMarkers If true, output a Texture2D showing the detected marker debug info overlaid on the input image @param bEstimatePose If true, return the 3D pose for each marker relative to the camera position @param InMarkerLengthInMeters Length in meters of one side of the physical marker (required if bEstimatePose is True) @param InCameraCalibrationParameters Lens distortion parameters for the incoming image (required if bEstimatePose is True) @param OutDebugTexture Output debug image (required if bDebugDrawMarkers is True) @param OutDetectedMarkers Output array of markers detected in the input image @return Total number of markers detected in the input image

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OPENCVHELPER_API`
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenCVBlueprintFunctionLibrary, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenCVBlueprintFunctionLibrary, Log, All);`

### `Plugins/Runtime/OpenCV/Source/OpenCVHelper/Public/OpenCVHelper.h` (Public)


#### enum `EArucoDictionary`  
`enum class EArucoDictionary : uint8`  
_L49-69_
- reflection: `UENUM(BlueprintType)`
- L51 _public enumerator_ `None UMETA(DisplayName = "None")`
- L52 _public enumerator_ `DICT_4X4_50 UMETA(DisplayName = "DICT_4X4_50")`
- L53 _public enumerator_ `DICT_4X4_100 UMETA(DisplayName = "DICT_4X4_100")`
- L54 _public enumerator_ `DICT_4X4_250 UMETA(DisplayName = "DICT_4X4_250")`
- L55 _public enumerator_ `DICT_4X4_1000 UMETA(DisplayName = "DICT_4X4_1000")`
- L56 _public enumerator_ `DICT_5X5_50 UMETA(DisplayName = "DICT_5X5_50")`
- L57 _public enumerator_ `DICT_5X5_100 UMETA(DisplayName = "DICT_5X5_100")`
- L58 _public enumerator_ `DICT_5X5_250 UMETA(DisplayName = "DICT_5X5_250")`
- L59 _public enumerator_ `DICT_5X5_1000 UMETA(DisplayName = "DICT_5X5_1000")`
- L60 _public enumerator_ `DICT_6X6_50 UMETA(DisplayName = "DICT_6X6_50")`
- L61 _public enumerator_ `DICT_6X6_100 UMETA(DisplayName = "DICT_6X6_100")`
- L62 _public enumerator_ `DICT_6X6_250 UMETA(DisplayName = "DICT_6X6_250")`
- L63 _public enumerator_ `DICT_6X6_1000 UMETA(DisplayName = "DICT_6X6_1000")`
- L64 _public enumerator_ `DICT_7X7_50 UMETA(DisplayName = "DICT_7X7_50")`
- L65 _public enumerator_ `DICT_7X7_100 UMETA(DisplayName = "DICT_7X7_100")`
- L66 _public enumerator_ `DICT_7X7_250 UMETA(DisplayName = "DICT_7X7_250")`
- L67 _public enumerator_ `DICT_7X7_1000 UMETA(DisplayName = "DICT_7X7_1000")`
- L68 _public enumerator_ `DICT_ARUCO_ORIGINAL UMETA(DisplayName = "DICT_ARUCO_ORIGINAL")`

#### struct `FArucoMarker`  
`struct FArucoMarker`  
_L72-76_
- L74 _public member_ `int32 MarkerID = 0;`
- L75 _public member_ `FVector2f Corners[4];`

#### struct `FCharucoBoardConfig`  
`struct FCharucoBoardConfig`  
_L80-96_
- desc: Structure representing a Charuco board configuration
- L83 _public member_ `int32 SquaresX = 5;` — Number of chessboard squares in X direction
- L86 _public member_ `int32 SquaresY = 7;` — Number of chessboard squares in Y direction
- L89 _public member_ `float SquareSize = 4.0f;` — Size of each square in the board (in cm)
- L92 _public member_ `float MarkerSize = 3.0f;` — Size of the ArUco markers (in cm)
- L95 _public member_ `EArucoDictionary Dictionary = EArucoDictionary::DICT_4X4_50;` — ArUco dictionary to use for the markers. Smaller dictionaries tend to be easier to parse

#### struct `FCharucoCorners`  
`struct FCharucoCorners`  
_L100-110_
- desc: Structure representing detected Charuco corners
- L103 _public member_ `TArray<FVector2f> Corners;` — 2D image coordinates of detected corners
- L106 _public member_ `TArray<int32> CornerIds;` — IDs of the detected corners (based on board layout)
- L109 _public member_ `TArray<FArucoMarker> Markers;` — Detected ArUco markers in the Charuco board

#### class `FOpenCVHelper`  
`class FOpenCVHelper`  
_L113-229_
- L124 _public member_ `inline static const TArray<FVector> UnitVectors = { { 1, 0, 0 },` — These axes must match the order in which they are declared in EAxis
- L134 _public function_ `static const FVector& UnitVectorFromAxisEnum(const EAxis Axis)`
- L140 _public prototype_ `static void ConvertCoordinateSystem(FTransform& Transform, const EAxis DstXInSrcAxis, const EAxis DstYInSrcAxis, const EAxis DstZInSrcAxis);` — Converts in-place the coordinate system of the given FTransform by specifying the source axes in terms of the destination axes
- L143 _public prototype_ `static void ConvertUnrealToOpenCV(FTransform& Transform);` — Converts in-place an FTransform in Unreal coordinates to OpenCV coordinates
- L146 _public prototype_ `static void ConvertOpenCVToUnreal(FTransform& Transform);` — Converts in-place an FTransform in OpenCV coordinates to Unreal coordinates
- L149 _public prototype_ `static FVector ConvertUnrealToOpenCV(const FVector& Transform);` — Converts an FVector in Unreal coordinates to OpenCV coordinates
- L152 _public prototype_ `static FVector ConvertOpenCVToUnreal(const FVector& Transform);` — Converts an FTransform in OpenCV coordinates to Unreal coordinates
- L165 _public prototype_ `static UTexture2D* TextureFromCvMat(cv::Mat& Mat, const FString* PackagePath = nullptr, const FName* TextureName = nullptr);` — Creates a Texture from the given Mat, if its properties (e.g. pixel format) are supported. @param Mat The OpenCV Mat to convert. @param PackagePath Optional path to a package to create the texture in. @param TextureName Optional name for the texture. Required if PackagePath is not nullptr. @return Texture created out of the given OpenCV Mat.
- L166 _public prototype_ `static UTexture2D* TextureFromCvMat(cv::Mat& Mat, UTexture2D* InTexture);`
- L173 _public prototype_ `static void MakeCameraPoseFromObjectVectors(const cv::Mat& InRotation, const cv::Mat& InTranslation, FTransform& OutTransform);` — Takes a rotation vector (in rodrigues form) and translation vector that represent a change of basis from object space to camera space (in OpenCV's coordinate system), inverts them to generate a camera pose, and converts it to an FTransform in UE's coordinate system. The input rotation and translation vectors are expected to match the form of an "rvec" and "tvec" that are generated functions like cv::calibrateCamera() and cv::solvePnP()
- L180 _public prototype_ `static void MakeObjectVectorsFromCameraPose(const FTransform& InTransform, cv::Mat& OutRotation, cv::Mat& OutTranslation);` — Takes a camera pose transform in UE's coordinate system, converts it to a rotation vector (in rodrigues form) and translation vector (in OpenCV's coordinate system), and inverts them to generate vectors that represent a change of basis from object space to camera space. The output rotation and translation vectors are expected to match the form of an "rvec" and "tvec" that are consumed by functions like cv::calibrateCamera() and cv::solvePnP()
- L184 _public prototype_ `static bool IdentifyArucoMarkers(TArray<FColor>& Image, FIntPoint ImageSize, EArucoDictionary DictionaryName, TArray<FArucoMarker>& OutMarkers);` — Identify a set of aruco markers in the input image that belong to the input aruco dictionary, and output the marker IDs and the 2D coordinates of the 4 corners of each marker
- L187 _public prototype_ `static bool DrawArucoMarkers(const TArray<FArucoMarker>& Markers, UTexture2D* DebugTexture);` — Draw a debug view of the input aruco markers on top of the input texture
- L190 _public prototype_ `static bool IdentifyCheckerboard(TArray<FColor>& Image, FIntPoint ImageSize, FIntPoint CheckerboardDimensions, TArray<FVector2f>& OutCorners);` — Identify a checkerboard pattern in the input image with the given checkerboard dimensions (columns x rows), and output the 2D coordinates of the intersections between each checkerboard square
- L193 _public prototype_ `static bool IdentifyCheckerboard(TArray<FColor>& Image, FIntPoint ImageSize, FIntRect RegionOfInterest, FIntPoint CheckerboardDimensions, TArray<FVector2f>& OutCorners);` — Identify a checkerboard pattern in a region of interest of the input image with the given checkerboard dimensions (columns x rows), and output the 2D coordinates of the intersections between each checkerboard square
- L196 _public prototype_ `static bool DrawCheckerboardCorners(const TArray<FVector2f>& Corners, FIntPoint CheckerboardDimensions, UTexture2D* DebugTexture);` — Draw a debug view of the input checkerboard corners on top of the input texture
- L199 _public prototype_ `static bool DrawCheckerboardCorners(const TArray<FVector2D>& Corners, FIntPoint CheckerboardDimensions, UTexture2D* DebugTexture);` — Draw a debug view of the input checkerboard corners on top of the input texture
- L202 _public prototype_ `static bool SolvePnP(const TArray<FVector>& ObjectPoints, const TArray<FVector2f>& ImagePoints, const FVector2D& FocalLength, const FVector2D& ImageCenter, const TArray<float>& DistortionParameters, FTransform& OutCameraPose);` — Compute the camera pose that minimizes the reprojection error of the input object points and image points
- L205 _public prototype_ `static bool ProjectPoints(const TArray<FVector>& ObjectPoints, const FVector2D& FocalLength, const FVector2D& ImageCenter, const TArray<float>& DistortionParameters, const FTransform& CameraPose, TArray<FVector2f>& OutImagePoints);` — Project the input object points to the 2D image plane defined by the input camera intrinsics and camera pose
- L208 _public prototype_ `static bool ProjectPoints(const TArray<FVector>& ObjectPoints, const FVector2D& FocalLength, const FVector2D& ImageCenter, const TArray<float>& DistortionParameters, const FTransform& CameraPose, TArray<FVector2D>& OutImagePoints);` — Project the input object points to the 2D image plane defined by the input camera intrinsics and camera pose
- L211 _public prototype_ `static bool FitLine3D(const TArray<FVector>& InPoints, FVector& OutLine, FVector& OutPointOnLine);` — Find a 3D fit line that passes through the input points, as well as a point on that line
- L215 _public prototype_ `static double ComputeReprojectionError(const FTransform& CameraPose, const cv::Mat& CameraIntrinsicMatrix, const std::vector<cv::Point3f>& Points3d, const std::vector<cv::Point2f>& Points2d);` — `UE_DEPRECATED(5.4, "The version of ComputeReprojectionError takes OpenCV types as input parameters is deprecated. Please use the version that takes all UE types.")`
- L219 _public prototype_ `static double ComputeReprojectionError(const TArray<FVector>& ObjectPoints, const TArray<FVector2f>& ImagePoints, const FVector2D& FocalLength, const FVector2D& ImageCenter, const FTransform& CameraPose);` — Project the 3D objects points to the 2D image plane represented by the input camera intrinsics and pose, and compute the reprojection error (euclidean distance) between the input image points and the reprojected points
- L222 _public prototype_ `static bool IdentifyCharucoCorners(TArray<FColor>& Image, FIntPoint ImageSize, const FCharucoBoardConfig& BoardConfig, FCharucoCorners& OutCorners, const FIntRect& ROI = FIntRect());` — Identify Charuco corners in the input image with the given board configuration, and output the detected corners and their IDs
- L225 _public prototype_ `static bool DrawCharucoCorners(const FCharucoCorners& Corners, UTexture2D* DebugTexture);` — Draw a debug view of the input Charuco corners on top of the input texture
- L228 _public prototype_ `static UTexture2D* GenerateCharucoBoard(const FCharucoBoardConfig& BoardConfig, FIntPoint ImageSize, int32 MarginSize = 10);` — Generate a Charuco board image with the given configuration for display or printing

#### enum `FOpenCVHelper::EAxis`  
`enum class EAxis`  
_L117-121_
- desc: Enumeration to specify any cartesian axis in positive or negative directions
- L119 _public enumerator_ `X`
- L119 _public enumerator_ `X`
- L119 _public enumerator_ `X`
- L120 _public enumerator_ `Xn`
- L120 _public enumerator_ `Xn`
- L120 _public enumerator_ `Xn`

#### struct `FOpenCVLensDistortionParametersBase`  
`struct FOpenCVLensDistortionParametersBase`  
_L240-356_
- reflection: `USTRUCT(BlueprintType)`
- desc: Mathematic camera model for lens distortion/undistortion. Camera matrix = | F.X  0  C.x | |  0  F.Y C.Y | |  0   0   1  | where F and C are normalized.
- L245 _public function_ `FOpenCVLensDistortionParametersBase() : K1(0.f) , K2(0.f) , P1(0.f) , P2(0.f) , K3(0.f) , K4(0.f) , K5(0.f) , K6(0.f) , F(FVector2D(1.f, 1.f)) , C(FVector2D(0.5f, 0.5f)) , bUseFisheyeModel(false)`
- L263 _public prototype_ `cv::Mat ConvertToOpenCVDistortionCoefficients() const;` — Convert internal coefficients to OpenCV matrix representation
- L266 _public prototype_ `cv::Mat CreateOpenCVCameraMatrix(const FVector2D& InImageSize) const;` — Convert internal normalized camera matrix to OpenCV pixel scaled matrix representation.
- L271 _public function_ `bool operator == (const FOpenCVLensDistortionParametersBase& Other) const` — Compare two lens distortion models and return whether they are equal.
- L287 _public function_ `bool operator != (const FOpenCVLensDistortionParametersBase& Other) const` — Compare two lens distortion models and return whether they are different.
- L293 _public function_ `bool IsIdentity() const` — Returns true if lens distortion parameters are for identity lens (or default parameters)
- L307 _public function_ `bool IsSet() const`
- L315 _public member_ `float K1;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Parameters")` — Radial parameter #1.
- L319 _public member_ `float K2;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Parameters")` — Radial parameter #2.
- L323 _public member_ `float P1;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Parameters")` — Tangential parameter #1.
- L327 _public member_ `float P2;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Parameters")` — Tangential parameter #2.
- L331 _public member_ `float K3;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Parameters")` — Radial parameter #3.
- L335 _public member_ `float K4;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Parameters")` — Radial parameter #4.
- L339 _public member_ `float K5;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Parameters")` — Radial parameter #5.
- L343 _public member_ `float K6;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Parameters")` — Radial parameter #6.
- L347 _public member_ `FVector2D F;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Parameters")` — Camera matrix's normalized Fx and Fy.
- L351 _public member_ `FVector2D C;` — `UPROPERTY(Interp, EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Parameters")` — Camera matrix's normalized Cx and Cy.
- L355 _public member_ `bool bUseFisheyeModel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lens Distortion|Parameters")` — Camera lens needs Fisheye camera model.

#### Free symbols / members of external scopes

- L25 _macro_ `#define OPENCV_INCLUDES_START static_assert(false, "Include PreOpenCVHeaders.h instead of using this macro.");`
- L27 _macro_ `#define OPENCV_INCLUDES_END static_assert(false, "Include PostOpenCVHeaders.h instead of using this macro");`
- L35 _namespace_ `namespace cv`
- L41 _typedef_ `typedef Point_<float> Point2f;` (scope `cv`)
- L42 _typedef_ `typedef Point3_<float> Point3f;` (scope `cv`)

### `Plugins/Runtime/OpenCV/Source/OpenCVHelper/Public/OpenCVUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace OpenCVUtils`
- L11 _typedef_ `using UEInt64 = FPlatformTypes::int64;` (scope `OpenCVUtils`) — Keep track of UE's int64 and uint64 typedefs to be able to restore it after including CV headers
- L12 _typedef_ `using UEUInt64 = FPlatformTypes::uint64;` (scope `OpenCVUtils`)

### `Plugins/Runtime/OpenCV/Source/OpenCVHelper/Public/PostOpenCVHeaders.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/OpenCV/Source/OpenCVHelper/Public/PreOpenCVHeaders.h` (Public)


#### Free symbols / members of external scopes

- L4 _macro_ `#define OPENCV_HEADERS_TYPES_GUARD`
