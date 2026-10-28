# Plugins / MetaHumanCore

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore`
- headers: 20; symbols: 333
- symbol kinds: class=12, delegate=4, enum=10, enumerator=36, function=17, macro=18, member=82, namespace=9, prototype=130, struct=14, typedef=1
- PrivateDependencyModuleNames: CameraCalibrationCore, ImgMedia, Json, JsonUtilities, Projects, RHI, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: CaptureDataCore, Core, CoreUObject, Engine, MetaHumanCoreTech, RigLogicLib, RigLogicModule

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Private/MetaHumanCoreLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCore, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCore, Log, All);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Private/ShapeAnnotation.h` (Private)


#### enum `ShapeAnnotation::EVertexStyle`  
`enum class EVertexStyle`  
_L9-13_
- L11 _public enumerator_ `Smooth`
- L12 _public enumerator_ `Sharp`

#### enum `ShapeAnnotation::ECurveConnectionDirection`  
`enum class ECurveConnectionDirection`  
_L15-19_
- L17 _public enumerator_ `ToStartOfOtherCurve`
- L18 _public enumerator_ `ToEndOfOtherCurve`

#### struct `ShapeAnnotation::FPoint2D`  
`struct FPoint2D`  
_L21-61_
- L23 _public function_ `FPoint2D() : X(0.0) , Y(0.0)`
- L29 _public function_ `FPoint2D(double InX, double InY) : X(InX) , Y(InY)`
- L35 _public function_ `double Length() const`
- L36 _public function_ `double LengthSquared() const`
- L37 _public member_ `double X;`
- L38 _public member_ `double Y;`
- L40 _public function_ `FPoint2D operator+(const FPoint2D& InOther) const`
- L45 _public function_ `FPoint2D operator-(const FPoint2D& InOther) const`
- L50 _public function_ `FPoint2D operator*(double InScalar) const`
- L55 _public function_ `FPoint2D operator/(double InScalar) const`

#### struct `ShapeAnnotation::FKeypoint`  
`struct FKeypoint`  
_L68-73_
- L70 _public member_ `FPoint2D Pos{0., 0.};`
- L71 _public member_ `EVertexStyle Style = EVertexStyle::Sharp;`
- L72 _public member_ `bool bVisible = false;`

#### struct `ShapeAnnotation::FKeypointCurve`  
`struct FKeypointCurve`  
_L75-80_
- L77 _public member_ `FString StarKeypointName;`
- L78 _public member_ `FString EndKeypointName;`
- L79 _public member_ `TArray<FPoint2D> InternalPoints;`

#### struct `ShapeAnnotation::FCurveConnection`  
`struct FCurveConnection`  
_L82-86_
- L84 _public member_ `FString OtherCurveName;`
- L85 _public member_ `ECurveConnectionDirection Direction;`

#### class `ShapeAnnotation::FShapeAnnotation`  
`class FShapeAnnotation`  
_L88-123_
- L92 _public prototype_ `void Initialize(const TMap<FString, FKeypoint>& InKeyPoints, const TMap<FString, FKeypointCurve>& InKeypointCurves);`
- L93 _public prototype_ `void InsertInternalPoint(const FString& InName, int32 InsertBefore, const FPoint2D InPoint);`
- L94 _public prototype_ `void RemoveInternalPoint(const FString& InName, int32 InIndex);`
- L96 _public prototype_ `TMap<FString, TArray<FPoint2D>> GetDrawingSplines(const TMap<FString, int32>& InPointsPerSpline) const;`
- L97 _public prototype_ `const TMap<FString, FKeypoint>& GetKeypoints() const;`
- L98 _public prototype_ `const TMap<FString, FKeypointCurve>& GetKeypointCurves() const;`
- L100 _public prototype_ `TMap<FString, FKeypoint>& GetKeypointsRef();`
- L101 _public prototype_ `TMap<FString, FKeypointCurve>& GetKeypointCurvesRef();`
- L105 _private prototype_ `TArray<FPoint2D> GetDensePoints(const int32 InImageWidth, const int32 InImageHeight, TArray<TArray<int32>>& OutInboundLinks, TArray<TArray<int32>> &OutOutboundLinks, TMap<FString, TArray<int32>>& OutCurveLookup, TMap<FString, int32>& OutKeypointLookup, const TMap<FString, int32>& InInternalDensities) const;`
- L108 _private prototype_ `FPoint2D FirstPointBeforeEnd(const FString& InCurveName) const;`
- L109 _private prototype_ `FPoint2D FirstPointAfterStart(const FString& InCurveName) const;`
- L110 _private prototype_ `FPoint2D DummyFirstPoint(const FString& InCurveName) const;`
- L111 _private prototype_ `FPoint2D DummyLastPoint(const FString& InCurveName) const;`
- L113 _private prototype_ `FCurveConnection IncomingConnection(const FString& InCurveName) const;`
- L114 _private prototype_ `FCurveConnection OutgoingConnection(const FString& InCurveName) const;`
- L116 _private prototype_ `TArray<FPoint2D> ApproximateOpenCatmullromSpline(const TArray<FPoint2D>& InExtendedPoints, int32 InNumOutPoints, int32 InResolution) const;`
- L117 _private prototype_ `FPoint2D CatmullromPointOnCurve(FPoint2D InA, FPoint2D InB, FPoint2D InC, FPoint2D InD, double InT, double InAlpha = 0.5) const;`
- L118 _private prototype_ `TArray<double> LinearRange(double InA, double InB, int32 InN) const;`
- L119 _private prototype_ `TArray<FPoint2D> SpreadPointsEvenly(const TArray<FPoint2D>& InPoints, int32 InNOutPoints) const;`
- L121 _private member_ `TMap<FString, FKeypoint> Keypoints;`
- L122 _private member_ `TMap<FString, FKeypointCurve> KeypointCurves;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ShapeAnnotation`
- L63 _function_ `inline FPoint2D operator*(double InScalar, const FPoint2D& InPoint)` (scope `ShapeAnnotation`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/DNAUtilities.h` (Public)


#### enum `EDNARigCompatiblityFlags`  
`enum class EDNARigCompatiblityFlags`  
_L9-18_
- L11 _public enumerator_ `None = 0`
- L13 _public enumerator_ `Joint = 1 << 0`
- L14 _public enumerator_ `Mesh = 1 << 1`
- L15 _public enumerator_ `LOD = 1 << 2`
- L17 _public enumerator_ `All = Joint | Mesh | LOD`

#### class `FDNAUtilities`  
`class FDNAUtilities`  
_L24-32_
- L28 _public prototype_ `static bool CheckCompatibility(IDNAReader* InDnaReaderA, IDNAReader* InDnaReaderB, EDNARigCompatiblityFlags InCompareFlags = EDNARigCompatiblityFlags::All);` — Checks if provided DNA readers share the same rig definition
- L31 _public prototype_ `static bool CheckCompatibility(IDNAReader* InDnaReaderA, IDNAReader* InDnaReaderB, EDNARigCompatiblityFlags InCompareFlags, FString& OutCompatibilityMsg);` — Checks if provided DNA readers share the same rig definition. Also outputs compatibility message

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCORE_API`
- L20 _prototype_ `ENUM_CLASS_FLAGS(EDNARigCompatiblityFlags);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/Defs.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define DLL_EXPORT __attribute__((dllexport))`
- L8 _macro_ `#define DLL_IMPORT __attribute__((dllimport))`
- L10 _macro_ `#define DLL_EXPORT __declspec(dllexport)`
- L11 _macro_ `#define DLL_IMPORT __declspec(dllimport)`
- L14 _macro_ `#define DLL_EXPORT __attribute__((visibility("default")))`
- L15 _macro_ `#define DLL_IMPORT DLL_EXPORT`
- L20 _macro_ `#define COREAPI DLL_EXPORT` — Build shared library
- L23 _macro_ `#define COREAPI DLL_IMPORT` — Use shared library
- L26 _macro_ `#define COREAPI` — Build or use static library

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/Integration.h` (Public)


#### struct `epic::core::Integration`  
`struct Integration`  
_L16-20_
- desc: @Brief Integration structure wraps objects that implements core functionalities from the external client.
- L18 _public member_ `Logger logger{};`
- L19 _public member_ `pma::MemoryResource* memoryResource{};`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace epic`
- L10 _namespace_ `namespace core` (scope `epic`)
- L27 _prototype_ `COREAPI Integration& GetIntegrationParams();` (scope `epic::core`) — @Brief Gets/Sets Integration struct to be used in the core tech lib @returns Integration parameters - singleton instance.

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/LoadLiveLinkFaceCameraCalibration.h` (Public)


#### struct `FDimensions`  
`struct FDimensions`  
_L10-22_
- reflection: `USTRUCT()`
- desc: simple structs allowing us to use FJsonObjectConverter::JsonObjectStringToUStruct to load in a camera calibration json file
- L17 _public member_ `int32 Width = 0;` — `UPROPERTY()`
- L20 _public member_ `int32 Height = 0;` — `UPROPERTY()`

#### struct `FLiveLinkFaceCalibrationData`  
`struct FLiveLinkFaceCalibrationData`  
_L25-60_
- reflection: `USTRUCT()`
- L32 _public member_ `FString Version;` — `UPROPERTY()`
- L35 _public member_ `FString DeviceModel;` — `UPROPERTY()`
- L38 _public member_ `FDimensions VideoDimensions;` — `UPROPERTY()`
- L41 _public member_ `FDimensions DepthDimensions;` — `UPROPERTY()`
- L44 _public member_ `FVector2D LensDistortionCenter = FVector2D::ZeroVector;` — `UPROPERTY()`
- L47 _public member_ `TArray<double> IntrinsicMatrix;` — `UPROPERTY()`
- L50 _public member_ `TArray<double> LensDistortionLookupTable;` — `UPROPERTY()`
- L53 _public member_ `TArray<double> InverseLensDistortionLookupTable;` — `UPROPERTY()`
- L56 _public member_ `double PixelSize = 0.0;` — `UPROPERTY()`
- L59 _public member_ `FDimensions IntrinsicMatrixReferenceDimensions;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L62 _prototype_ `class UCameraCalibration* LoadLiveLinkFaceCameraCalibration(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, const FString& InFilenameOrString, bool bIsFile = true);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/Logger.h` (Public)


#### class `epic::core::Logger`  
`class COREAPI Logger final`  
_L18-61_
- desc: @Brief Logger class is simple logging functionality wrapper. Its main purpose is integration of logging functionality from external system (for example UE)
- L25 _public prototype_ `Logger() noexcept;` — Default Constructor.
- L33 _public prototype_ `Logger(LogFunction logFunction_) noexcept;` — Constructor. @param[in] logFunction_ logging function provided from the external system. Initially set to DefaultLogger.
- L38 _public prototype_ `~Logger() noexcept;` — Destructor.
- L52 _public function_ `template<typename ...ARGS> void Log(LogLevel logLevel, const char* format, ARGS&& ...params)` — Send message to log system. @param[in] logLevel Log level of message. @param[in] format format string. @param[in] params multiple parameters to be embedded in the format string. @note C style formatting syntax needs to be applied
- L58 _private prototype_ `static void DefaultLogger(epic::core::LogLevel logLevel, const char* format, ...);`
- L60 _private member_ `LogFunction m_logFunction{ DefaultLogger };`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace epic`
- L10 _namespace_ `namespace core` (scope `epic`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/MetaHumanAuthoringObjects.h` (Public)


#### class `FMetaHumanAuthoringObjects`  
`class FMetaHumanAuthoringObjects`  
_L12-42_
- L16 _public prototype_ `static bool ArePresent();`
- L18 _public prototype_ `static bool FindObject(FString& InOutObjectPath);`
- L19 _public prototype_ `static bool FindObject(FString& InOutObjectPath, bool& bOutWasFound, bool& bOutHasMoved);`
- L22 _public function_ `template<class T> static bool FindObject(TSoftObjectPtr<T>& InSoftObjectPtr)`
- L30 _public function_ `template<class T> static bool FindObject(TSoftObjectPtr<T>& InSoftObjectPtr, bool& bOutWasFound, bool& bOutHasMoved)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANCORE_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/MetaHumanContourData.h` (Public)


#### struct `FControlVertex`  
`struct FControlVertex`  
_L12-30_
- reflection: `USTRUCT()`
- L17 _public member_ `FVector2D PointPosition = FVector2D::ZeroVector;` — `UPROPERTY()`
- L20 _public member_ `TArray<FVector2D> LinePoints;` — `UPROPERTY()`
- L23 _public member_ `TArray<FString> CurveNames;` — `UPROPERTY()`
- L26 _public member_ `int32 PointId = INDEX_NONE;` — `UPROPERTY()`
- L29 _public member_ `bool bIsSinglePointCurve = false;` — `UPROPERTY()`

#### struct `FReducedContour`  
`struct FReducedContour`  
_L33-39_
- reflection: `USTRUCT()`
- L38 _public member_ `TArray<FControlVertex> ControlVertices;` — `UPROPERTY()`

#### class `UMetaHumanContourData`  
`class UMetaHumanContourData : public UObject`  
_L42-104_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L48 _public prototype_ `void SetContourDataForDrawing(const TMap<FString, TArray<FVector2D>>& InContoursDrawData);`
- L49 _public prototype_ `void SetFullCurveContourDataForDrawing(const TMap<FString, TArray<FVector2D>>& InFullContoursForDraw);`
- L52 _public prototype_ `void ClearGeneratedDrawData();` — Removes generated curve draw data and control vertices
- L55 _public prototype_ `bool ControlVertexIsVisible(const FControlVertex& InVertex) const;` — Returns true if any of the curves (this control vertex is on) is visible
- L58 _public prototype_ `bool ContourIsVisible(const FString& InCurveName) const;` — Returns true if the curve is visible
- L60 _public prototype_ `const TMap<FString, TArray<FVector2D>>& GetReducedDataForDrawing();`
- L61 _public prototype_ `const TMap<FString, TArray<FVector2D>>& GetTrackingContourDataForDrawing();`
- L64 _public prototype_ `FControlVertex* GetControlVertexFromPointId(const int32 InPointId);` — Returns a reference to a control vertex for a specified point id
- L67 _public prototype_ `TArray<FControlVertex> GetControlVerticesForCurve(const FString& InCurveName);` — Returns a copy of control vertices from reduced contour. End points NOT included
- L70 _public prototype_ `TArray<FVector2D> GetControlVertexPositions(const FString& InCurveName);` — Returns positions of control vertices for the curve. End points NOT included
- L73 _public prototype_ `TArray<int32> GetPointIdsWithEndpointsForCurve(const FString& InCurveName) const;` — Returns the list of point IDs for a curve INCLUDING the end points
- L76 _public prototype_ `TSet<FString> GetSelectedCurves() const;` — Returns a list of curves that have selected status set to true
- L79 _public prototype_ `TPair<FString, FString> GetStartEndNamesForCurve(const FString& InCurveName) const;` — returns a pair of start and end point names for a given curve
- L82 _public member_ `FFrameTrackingContourData FrameTrackingContourData;` — `UPROPERTY()`
- L85 _public member_ `TMap<FString, FReducedContour> ReducedContourData;` — `UPROPERTY()`
- L89 _public member_ `TSet<FString> ManuallyModifiedCurves;` — `UPROPERTY()` — A list of curves that the user has manually adjusted
- L92 _public member_ `FString ContourDataConfigVersion = "";` — `UPROPERTY()`
- L97 _private prototype_ `const TArray<int32> GetPointIdsForCurve(const FString& InCurveName) const;` — Returns the list of point IDs for a curve. End points NOT included
- L100 _private member_ `TMap<FString, TArray<FVector2D>> CurveDrawDataFromReducedContours;` — A draw data for curves, generated from control vertices
- L103 _private member_ `TMap<FString, TArray<FVector2D>> CurveDrawDataFromTrackingContours;` — A draw data for curves, generated from all points produced by contour tracker

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCORE_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/MetaHumanContourDataVersion.h` (Public)


#### struct `FMetaHumanContourDataVersion`  
`struct FMetaHumanContourDataVersion`  
_L9-27_
- desc: Version for the contour data internal functionality (not necessarily matching UE version)
- L20 _public prototype_ `static FString GetContourDataVersionString();` — Returns the Mesh Tracker module version on an FEngineVersion struct
- L23 _public prototype_ `static bool CheckVersionCompatibility(const TArray<FString>& InVersionStringList, ECompatibilityResult& OutResult);` — Check for compatibility for a list of versions, returning the most severe upgrade requirement as OutResult
- L26 _public member_ `const static FString ConfigFileName;` — Config file name for contour data

#### enum `FMetaHumanContourDataVersion::ECompatibilityResult`  
`enum class ECompatibilityResult : uint8`  
_L11-17_
- L13 _public enumerator_ `NoUpgrade = 0` — Nothing to change
- L14 _public enumerator_ `NeedsUpgrade` — Not expected to be compatible
- L15 _public enumerator_ `RecommendUpgrade` — Compatible but upgrade is recommended
- L16 _public enumerator_ `AutoUpgrade` — Minor change that could be automatically resolved

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API METAHUMANCORE_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/MetaHumanCoreStyle.h` (Public)


#### class `FMetaHumanCoreStyle`  
`class FMetaHumanCoreStyle : public FSlateStyleSet`  
_L9-26_
- inherits: `FSlateStyleSet`
- desc: A Style set for MetaHuman Core module
- L13 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L14 _public prototype_ `static const FMetaHumanCoreStyle& Get();`
- L16 _public prototype_ `static void ReloadTextures();`
- L18 _public prototype_ `static void Register();`
- L19 _public prototype_ `static void Unregister();`
- L23 _private prototype_ `FMetaHumanCoreStyle();`
- L25 _private member_ `static FName StyleName;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/MetaHumanCurveDataController.h` (Public)


#### class `FMetaHumanCurveDataController`  
`class FMetaHumanCurveDataController`  
_L15-109_
- L19 _public prototype_ `FMetaHumanCurveDataController(TObjectPtr<UMetaHumanContourData> InCurveData, ECurveDisplayMode InMode = ECurveDisplayMode::Editing);`
- L22 _public prototype_ `void InitializeContoursFromConfig(const FFrameTrackingContourData& InDefaultContourData, const FString& InConfigVersion);` — Sets up the curve list from config along with default data to be displayed
- L25 _public prototype_ `void UpdateFromContourData(const FFrameTrackingContourData& InTrackingData, const bool bUpdateVisibility);` — Updates the tracking contour data present in config & relevant data to display those curves
- L28 _public prototype_ `void UpdateIndividualCurves(const FFrameTrackingContourData& InTrackingData);` — Updates individual curves, keeping reduced data of other curves intact
- L31 _public prototype_ `void ClearContourData();` — Removes all contour data, invalidating the initialization from config
- L34 _public prototype_ `void OffsetSelectedPoints(const TSet<int32>& InSelectedPoints, const FVector2D& InOffset);` — Moves selected points by a provided offset
- L37 _public prototype_ `void MoveSelectedPoint(const FVector2D& InNewPosition, const int32 InPointId);` — Moves a single point to a mouse cursor in image space
- L40 _public prototype_ `void UpdateDensePointsAfterDragging(const TSet<int32>& InDraggedIds);` — Update the original dense points data to represent the modified curve
- L43 _public prototype_ `void SetCurveSelection(const TSet<FString>& InSelectedCurves, bool bClearPointSelection);` — Updates the selection of contour data & emits the signal for relevant updates
- L46 _public prototype_ `void ResolveCurveSelectionFromSelectedPoints(const TSet<int32>& InSelectedPoints);` — Updates the selection of contour data based of individually selected points
- L49 _public prototype_ `void HandleUndoOperation();` — Triggers relevant updates to draw data after the undo operation
- L52 _public prototype_ `void ClearDrawData();` — Clears displayed data but keeps controller initialization with whatever last data was set
- L55 _public prototype_ `void ResolvePointSelectionOnCurveVisibilityChanged(const TArray<FString>& InCurveNames, bool bInSingleCurve, bool bInIsHiding);` — Resolves end point selection when these points belong to multiple curves
- L58 _public prototype_ `TPair<bool, bool> GetCurveSelectedAndActiveStatus(const FString& InCurve);` — Checks if the curve is selected or active
- L60 _public prototype_ `void GenerateCurvesFromControlVertices();`
- L61 _public prototype_ `void GenerateDrawDataForDensePoints();`
- L64 _public prototype_ `bool AddRemoveKey(const FVector2D& InPointPosition, const FString& InCurveName, bool bInAdd);` — Scoped operation for adding or removing the key
- L66 _public prototype_ `TArray<FString> GetCurveNamesForPointId(const int32 InPointId);`
- L67 _public prototype_ `TArray<int32> GetPointIdsWithEndPointsForCurve(const FString& InCurveName) const;`
- L68 _public prototype_ `TMap<FString, TArray<FVector2D>> GetDensePointsForVisibleCurves() const;`
- L69 _public prototype_ `TMap<FString, TArray<FVector2D>> GetFullSplineDataForVisibleCurves() const;`
- L70 _public prototype_ `TArray<FControlVertex> GetAllVisibleControlVertices();`
- L72 _public function_ `FSimpleMulticastDelegate& TriggerContourUpdate()`
- L73 _public function_ `FOnCurvesSelectedDelegate& GetCurvesSelectedDelegate()`
- L74 _public function_ `FOnGetViewportPointSelectionDelegate& ViewportPointSelectionRetrieverDelegate()`
- L76 _public function_ `const TObjectPtr<UMetaHumanContourData> GetContourData()`
- L80 _private prototype_ `void CreateControlVertices();`
- L81 _private prototype_ `void RecreateControlVertexIds();`
- L82 _private prototype_ `void RecreateCurvesFromReducedData();`
- L83 _private prototype_ `void ClearCurveSelection();`
- L84 _private prototype_ `void GenerateCurveDataPostTrackingDataChange();`
- L85 _private prototype_ `void ModifyViewportEndPointSelectionForCurveVisibility(const FString& InCurveName, const FString& InEndPointName);`
- L87 _private prototype_ `bool CurveIsVisible(const FString& InCurveName) const;`
- L88 _private prototype_ `int32 GetCurveInsertionIndex(const FVector2D& InInsertionPos, const FString& InCurveName);`
- L89 _private prototype_ `float GetDistanceToNearestVertex(const FVector2D& InPosition, const FString& InCurveName, int32& outIndex);`
- L91 _private prototype_ `TArray<FString> GetCurveNamesForEndPoints(const FString& InEndPointName) const;`
- L92 _private prototype_ `TArray<FVector2D> GetPointAtPosition(const FVector2D& InScreenPosition) const;`
- L93 _private prototype_ `TMap<FString, TArray<FVector2D>> GetCurveDisplayDataForEditing() const;`
- L94 _private prototype_ `TMap<FString, TArray<FVector2D>> GetCurveDisplayDataForVisualization() const;`
- L95 _private prototype_ `FReducedContour GetReducedContourForTrackingContour(const TPair<FString, FTrackingContour>& InContour);`
- L97 _private member_ `TObjectPtr<UMetaHumanContourData> ContourData;`
- L98 _private member_ `FShapeAnnotationWrapper ShapeAnnotationWrapper;`
- L100 _private member_ `static constexpr int32 LinesPerCircle = 33;`
- L101 _private member_ `static constexpr int32 PointSize = 5;`
- L102 _private member_ `static constexpr float CurveAddRemoveThreshold = 2.5f;`
- L103 _private member_ `static constexpr float SelectionCaptureRange = 40.0f;`
- L105 _private member_ `const ECurveDisplayMode DisplayMode;`
- L106 _private member_ `FSimpleMulticastDelegate UpdateContourDelegate;`
- L107 _private member_ `FOnCurvesSelectedDelegate OnCurvesSelectedDelegate;`
- L108 _private member_ `FOnGetViewportPointSelectionDelegate OnGetViewportPointSelection;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCORE_API`
- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurvesSelectedDelegate, bool bClearPointSelection) DECLARE_DELEGATE_RetVal(TSet<int32>&, FOnGetViewportPointSelectionDelegate) class FMetaHumanCurveDataController { public: FMetaHumanCurveDataController(TObjectPtr<UMetaHumanContourData> InCurveData, ECurveDisplayMode InMode = ECurveDisplayMode::Editing); void InitializeContoursFromConfig(const FFrameTrackingContourData& InDefaultContourData, const FString& InConfigVersion); void UpdateFromContourData(const FFrameTrackingContourData& InTrackingData, const bool bUpdateVisibility); void UpdateIndividualCurves(const FFrameTrackingContourData& InTrackingData); void ClearContourData(); void OffsetSelectedPoints(const TSet<int32>& InSelectedPoints, const FVector2D& InOffset); void MoveSelectedPoint(const FVector2D& InNewPosition, const int32 InPointId); void UpdateDensePointsAfterDragging(const TSet<int32>& InDraggedIds); void SetCurveSelection(const TSet<FString>& InSelectedCurves, bool bClearPointSelection); void ResolveCurveSelectionFromSelectedPoints(const TSet<int32>& InSelectedPoints); void HandleUndoOperation();`
- L13 _delegate_ `DECLARE_DELEGATE_RetVal(TSet<int32>&, FOnGetViewportPointSelectionDelegate) class FMetaHumanCurveDataController { public: FMetaHumanCurveDataController(TObjectPtr<UMetaHumanContourData> InCurveData, ECurveDisplayMode InMode = ECurveDisplayMode::Editing); void InitializeContoursFromConfig(const FFrameTrackingContourData& InDefaultContourData, const FString& InConfigVersion); void UpdateFromContourData(const FFrameTrackingContourData& InTrackingData, const bool bUpdateVisibility); void UpdateIndividualCurves(const FFrameTrackingContourData& InTrackingData); void ClearContourData(); void OffsetSelectedPoints(const TSet<int32>& InSelectedPoints, const FVector2D& InOffset); void MoveSelectedPoint(const FVector2D& InNewPosition, const int32 InPointId); void UpdateDensePointsAfterDragging(const TSet<int32>& InDraggedIds); void SetCurveSelection(const TSet<FString>& InSelectedCurves, bool bClearPointSelection); void ResolveCurveSelectionFromSelectedPoints(const TSet<int32>& InSelectedPoints); void HandleUndoOperation(); void ClearDrawData();`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/MetaHumanIdentityCustomVersion.h` (Public)


#### struct `FMetaHumanIdentityCustomVersion`  
`struct FMetaHumanIdentityCustomVersion`  
_L10-26_
- L21 _public member_ `static const FGuid GUID;`
- L25 _private prototype_ `FMetaHumanIdentityCustomVersion() = default;`

#### enum `FMetaHumanIdentityCustomVersion::Type`  
`enum Type : int32`  
_L12-19_
- L15 _public enumerator_ `EditorBulkDataUpdate = 0` — MetaHuman Identity was updated to use EditorBulkData
- L17 _public enumerator_ `VersionPlusOne`
- L18 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANCORE_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/MetaHumanProcessingAsset.h` (Public)


#### class `UMetaHumanProcessingAsset`  
`class UMetaHumanProcessingAsset : public UObject`  
_L10-17_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UObject`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/MetaHumanSupportedRHI.h` (Public)


#### class `FMetaHumanSupportedRHI`  
`class FMetaHumanSupportedRHI`  
_L11-23_
- L15 _public prototype_ `static bool IsSupported();`
- L16 _public prototype_ `static FText GetSupportedRHINames();`
- L17 _public prototype_ `static void Reset();`
- L21 _private member_ `static bool bIsInitialized;`
- L22 _private member_ `static bool bIsSupported;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCORE_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/MetaHumanViewportModes.h` (Public)


#### enum `EABImageViewMode`  
`enum class EABImageViewMode`  
_L8-20_
- reflection: `UENUM()`
- L12 _public enumerator_ `A = 0` — Single view modes
- L13 _public enumerator_ `B`
- L15 _public enumerator_ `ABSplit` — Multi view modes
- L16 _public enumerator_ `ABSide`
- L18 _public enumerator_ `Current` — Special modes for querying per-view parameter state
- L19 _public enumerator_ `Any`

#### enum `EABImageNavigationMode`  
`enum class EABImageNavigationMode`  
_L23-27_
- reflection: `UENUM()`
- L25 _public enumerator_ `ThreeD = 0`
- L26 _public enumerator_ `TwoD`

#### enum `EABImageMouseSide`  
`enum class EABImageMouseSide`  
_L30-35_
- reflection: `UENUM()`
- L32 _public enumerator_ `NotApplicable = 0`
- L33 _public enumerator_ `A`
- L34 _public enumerator_ `B`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/MetaHumanViewportSettings.h` (Public)


#### struct `FMetaHumanViewportState`  
`struct FMetaHumanViewportState`  
_L15-51_
- reflection: `USTRUCT()`
- L19 _public function_ `FMetaHumanViewportState() : bShowCurves(true) , bShowControlVertices(true) , bShowSkeletalMesh(false) , bShowFootage(false) , bShowDepthMesh(false) , bShowUndistorted(false)`
- L29 _public member_ `uint8 bShowCurves : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L32 _public member_ `uint8 bShowControlVertices : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L35 _public member_ `uint8 bShowSkeletalMesh : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L38 _public member_ `uint8 bShowFootage : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L41 _public member_ `uint8 bShowDepthMesh : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L44 _public member_ `uint8 bShowUndistorted : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L47 _public member_ `TEnumAsByte<EViewModeIndex> ViewModeIndex = VMI_Lit;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L50 _public member_ `float FixedEV100 = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`

#### struct `FMetaHumanViewportCameraState`  
`struct FMetaHumanViewportCameraState`  
_L54-88_
- reflection: `USTRUCT()`
- L60 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category = "Camera")` — The current camera location for this Promoted Frame
- L64 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(VisibleAnywhere, Category = "Camera")` — The current camera rotation for this Promoted Frame
- L68 _public member_ `FVector LookAt = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category = "Camera")` — The current camera LookAt position for this Promoted Frame
- L72 _public member_ `float ViewFOV = 45.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Camera")` — The Camera FoV from when the view was promoted
- L75 _public member_ `float CameraSpeed = 0.33f;` — `UPROPERTY(VisibleAnywhere, Category = "Camera")`
- L78 _public member_ `float MinCameraSpeed = 0.033f;` — `UPROPERTY(VisibleAnywhere, Category = "Camera")`
- L81 _public member_ `float MaxCameraSpeed = 4.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Camera")`
- L84 _public member_ `int32 SpeedSetting_DEPRECATED = 2;` — `UPROPERTY()`
- L87 _public member_ `float SpeedScalar_DEPRECATED = 1.0f;` — `UPROPERTY()`

#### class `UMetaHumanViewportSettings`  
`class UMetaHumanViewportSettings : public UObject`  
_L91-188_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L98 _public prototype_ `UMetaHumanViewportSettings();`
- L102 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L107 _public prototype_ `static bool IsExtendDefaultLuminanceRangeEnabled();` — Returns true if the luminance range variable is enabled
- L110 _public prototype_ `static float GetDefaultViewportBrightness();` — Returns 0 if using ExtendDefaultLuminanceRange and 1 otherwise
- L113 _public prototype_ `void NotifySettingsChanged();` — Calls OnSettingsChangedDelegate to notify that something changed
- L116 _public prototype_ `EViewModeIndex GetViewModeIndex(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L119 _public prototype_ `float GetEV100(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L122 _public prototype_ `void SetEV100(EABImageViewMode InView, float InValue, bool bInNotify);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L125 _public prototype_ `void SetViewModeIndex(EABImageViewMode InView, EViewModeIndex InViewModeIndex, bool bInNotify);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L128 _public prototype_ `bool IsShowingSingleView() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L131 _public prototype_ `void ToggleShowCurves(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L134 _public prototype_ `bool IsShowingCurves(EABImageViewMode InView) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L137 _public prototype_ `void ToggleShowControlVertices(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L140 _public prototype_ `bool IsShowingControlVertices(EABImageViewMode InView) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L143 _public prototype_ `void ToggleSkeletalMeshVisibility(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L146 _public prototype_ `bool IsSkeletalMeshVisible(EABImageViewMode InView) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L149 _public prototype_ `void ToggleFootageVisibility(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L152 _public prototype_ `bool IsFootageVisible(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L155 _public prototype_ `void ToggleDepthMeshVisibility(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L158 _public prototype_ `bool IsDepthMeshVisible(EABImageViewMode InView) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L161 _public prototype_ `void ToggleDistortion(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L164 _public prototype_ `bool IsShowingUndistorted(EABImageViewMode InView) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L166 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMetaHumanViewportSettingsChanged);`
- L167 _public member_ `FOnMetaHumanViewportSettingsChanged OnSettingsChangedDelegate;`
- L172 _public member_ `EABImageViewMode CurrentViewMode;` — `UPROPERTY(VisibleAnywhere, Category = "Viewport Settings")`
- L175 _public member_ `float DepthNear;` — `UPROPERTY(VisibleAnywhere, Category = "Viewport Settings")`
- L178 _public member_ `float DepthFar;` — `UPROPERTY(VisibleAnywhere, Category = "Viewport Settings")`
- L181 _public member_ `FMetaHumanViewportCameraState CameraState;` — `UPROPERTY(VisibleAnywhere, Category = "Viewport Settings")`
- L186 _protected member_ `TMap<EABImageViewMode, FMetaHumanViewportState> ViewportState;` — `UPROPERTY(VisibleAnywhere, Category = "Viewport Settings")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCORE_API`
- L166 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMetaHumanViewportSettingsChanged);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/ScopedTimer.h` (Public)


#### class `epic::core::ScopedTimer`  
`class COREAPI ScopedTimer`  
_L17-52_
- desc: @Brief ScopedTimer is rudimentary profiler that leverages std::chrono timers.
- L29 _public prototype_ `ScopedTimer(const char* functionName_, const Logger& logger_) noexcept;` — Constructor. @param[in] functionName_ name of the profiled function. Function name can be obtained through __func__ macro. @param[in] logger logging wrapper.
- L34 _public prototype_ `~ScopedTimer() noexcept;` — Destructor.
- L37 _private prototype_ `ScopedTimer(ScopedTimer const&) = delete;`
- L38 _private prototype_ `ScopedTimer(ScopedTimer&&) = delete;`
- L39 _private prototype_ `auto operator=(ScopedTimer const&)->ScopedTimer & = delete;`
- L40 _private prototype_ `auto operator=(ScopedTimer &&)->ScopedTimer = delete;`
- L41 _private prototype_ `auto operator new(std::size_t)->void* = delete;`
- L42 _private prototype_ `auto operator delete(void*, std::size_t)->void = delete;`
- L45 _private member_ `const char* m_function{};`
- L46 _private member_ `Logger m_logger{ };`
- L51 _private member_ `pimpl m_pimpl{};`

#### struct `epic::core::ScopedTimer::pimpl`  
`struct pimpl`  
_L47-50_
- L49 _public member_ `const std::chrono::steady_clock::time_point m_start{};`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace epic`
- L11 _namespace_ `namespace core` (scope `epic`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/ShapeAnnotationWrapper.h` (Public)


#### enum `ECurveDisplayMode`  
`enum class ECurveDisplayMode : uint8`  
_L13-17_
- L15 _public enumerator_ `Visualization`
- L16 _public enumerator_ `Editing`

#### class `FShapeAnnotationWrapper`  
`class FShapeAnnotationWrapper`  
_L19-38_
- L22 _public prototype_ `FShapeAnnotationWrapper();`
- L23 _public prototype_ `~FShapeAnnotationWrapper();`
- L26 _public prototype_ `TArray<FVector2D> GetControlVerticesForCurve(const TArray<FVector2D>& InLandmarkData, const FString& InCurveName, ECurveDisplayMode InDisplayMode) const;` — Returns a list of control vertices for a curve. Start and end points are not included
- L29 _public prototype_ `TMap<FString, TArray<FVector2D>> GetDrawingSplinesFromContourData(const TObjectPtr<class UMetaHumanContourData> InContourData);` — Returns point data that represents a Catmull-Rom spline, generated from contour data
- L34 _private prototype_ `void InitializeShapeAnnotation(const TObjectPtr<class UMetaHumanContourData> InContourData, bool bUseDensePoints);` — Initializes keypoints and keypoint curves in the form that rlibv::shapeAnnotation requires to generate curves
- L37 _private member_ `TPimplPtr<FImpl> Impl;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANCORE_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCore/Public/types.h` (Public)


#### enum `epic::core::LogLevel`  
`enum class LogLevel`  
_L8-17_
- L10 _public enumerator_ `VERBOSE = 0`
- L11 _public enumerator_ `WARNING = 1`
- L12 _public enumerator_ `INFO = 2`
- L13 _public enumerator_ `DEBUG = 3`
- L14 _public enumerator_ `ERR = 4`
- L15 _public enumerator_ `CRITICAL = 5`
- L16 _public enumerator_ `FATAL = 6`

#### Free symbols / members of external scopes

- L3 _namespace_ `namespace epic`
- L5 _namespace_ `namespace core` (scope `epic`)
- L19 _typedef_ `using LogFunction = void(*)(LogLevel , const char* , ...);` (scope `epic::core`)
