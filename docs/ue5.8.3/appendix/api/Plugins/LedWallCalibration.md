# Plugins / LedWallCalibration

- module root: `Plugins/Experimental/VirtualProduction/LedWallCalibration/Source/LedWallCalibration`
- headers: 3; symbols: 14
- symbol kinds: class=1, delegate=1, function=2, member=5, namespace=1, prototype=3, struct=1
- PrivateDependencyModuleNames: CameraCalibrationCore, Core, CoreUObject, Engine, MeshDescription, OpenCV, OpenCVHelper, StaticMeshDescription

### `Plugins/Experimental/VirtualProduction/LedWallCalibration/Source/LedWallCalibration/Private/LedWallCalibrationLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLedWallCalibration, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLedWallCalibration, Log, All);`

### `Plugins/Experimental/VirtualProduction/LedWallCalibration/Source/LedWallCalibration/Public/LedWallArucoGenerationOptions.h` (Public)


#### struct `FLedWallArucoGenerationOptions`  
`struct FLedWallArucoGenerationOptions`  
_L14-61_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure that can be passed to the Aruco generation function
- L22 _public member_ `int32 TextureWidth = 3840;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aruco")` — Width of the texture that will contain the Aruco markers
- L26 _public member_ `int32 TextureHeight = 2160;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aruco")` — Height of the texture that will contain the Aruco markers
- L30 _public member_ `EArucoDictionary ArucoDictionary = EArucoDictionary::DICT_6X6_1000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aruco")` — Aruco dictionary to use when generating the markers
- L34 _public member_ `int32 MarkerId = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aruco")` — Starting marker Id. Arucos will be generated with consecutive Marker Ids, starting from this one
- L41 _public member_ `int32 PlaceModulus = 2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aruco")` — Used to avoid using up the symbols in the dictionary as quickly. Will place the next marker id when [(row + column) mod PlaceModulus] is zero.
- L50 _public function_ `FString ArucoDictionaryAsString() const` — Returns name of selected Aruco dictionary @return Name of selected Aruco dictionary

### `Plugins/Experimental/VirtualProduction/LedWallCalibration/Source/LedWallCalibration/Public/LedWallCalibration.h` (Public)


#### class `FLedWallCalibration`  
`class FLedWallCalibration`  
_L18-64_
- L35 _public prototype_ `static bool GenerateArucosForCalibrationPoint( UCalibrationPointComponent* CalibrationPoint, const FLedWallArucoGenerationOptions& Options, int32& OutNextMarkerId, cv::Mat& OutMat);` — Populates calibration points and generates a texture with Aruco markers. It finds the CalibrationPointComponent's parent, which is expected to be a StaticMeshComponent, and finds the led panels in it (it expects its triangles to have 3 corners of any given panel. It then generates an Aruco marker for each detected panel and populates its named calibration point corners. @param InCalibrationPoint The calibration point that will be populated. @param InOptions The options for Aruco generation. @param OutNextMarkerId If you re-run this function for another mesh, use OutNextMarkerId in the input options. @param OutMat The generated OpenCV Mat with the Aruco markers. @return True if successful
- L50 _public prototype_ `static USceneComponent* GetTypedParentComponent(const USceneComponent* InComponent, const UClass* InParentClass);` — Finds the parent component of the given component. @param InComponent Component that we are looking the parent for. @param ParentClass Parent class to search for. @return The found component that InComponent is parented to.
- L60 _public function_ `template <class T> static T* GetTypedParentComponent(const USceneComponent* InComponent)` — Finds the parent component of the given calibration point component @param InComponent Component that we are looking the parent for. @return The found component that InComponent is parented to.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace cv`
