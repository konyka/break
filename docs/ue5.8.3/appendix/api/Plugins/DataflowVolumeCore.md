# Plugins / DataflowVolumeCore

- module root: `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore`
- headers: 16; symbols: 432
- symbol kinds: class=10, enum=19, enumerator=84, function=77, macro=5, member=30, namespace=36, prototype=144, struct=10, typedef=17
- PrivateDependencyModuleNames: Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DataflowEnginePlugin, DynamicMesh, Engine, GeometryCollectionEngine, GeometryCore, GeometryFramework, MeshConversion, MeshDescription, PlanarCut, StaticMeshDescription, Voronoi
- PublicDependencyModuleNames: 

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Internal/Dataflow/DataflowBoolVolume.h` (Internal)


#### struct `FDataflowBoolVolume`  
`struct FDataflowBoolVolume : public FDataflowVolume`  
_L19-36_
- reflection: `USTRUCT()`
- inherits: `FDataflowVolume`
- L21 _public member_ `inline static const FName TypeName = "Bo`
- L26 _public function_ `FDataflowBoolVolume()`
- L27 _public function_ `virtual ~FDataflowBoolVolume()`
- L29 _public prototype_ `TSharedPtr<const UE::DataflowVolume::Private::FDataflowBoolVolumeImpl> GetBoolVolumeImpl() const;`
- L30 _public prototype_ `TSharedPtr<UE::DataflowVolume::Private::FDataflowBoolVolumeImpl> GetBoolVolumeImpl();`
- L32 _public prototype_ `FVector GetVoxelSize() const;`
- L35 _private prototype_ `FDataflowBoolVolume(TSharedPtr<UE::DataflowVolume::Private::FDataflowBoolVolumeImpl> InBoolVolume);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DataflowVolume` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::DataflowVolume`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Internal/Dataflow/DataflowFloatVectorVolume.h` (Internal)


#### struct `FDataflowFloatVectorVolume`  
`struct FDataflowFloatVectorVolume : public FDataflowVolume`  
_L23-50_
- reflection: `USTRUCT()`
- inherits: `FDataflowVolume`
- L25 _public member_ `inline static const FName TypeName = "Fl`
- L32 _public function_ `FDataflowFloatVectorVolume()`
- L33 _public function_ `virtual ~FDataflowFloatVectorVolume()`
- L35 _public prototype_ `TSharedPtr<const UE::DataflowVolume::Private::FDataflowFloatVectorVolumeImpl> GetFloatVectorVolumeImpl() const;`
- L36 _public prototype_ `TSharedPtr<UE::DataflowVolume::Private::FDataflowFloatVectorVolumeImpl> GetFloatVectorVolumeImpl();`
- L38 _public prototype_ `FVector GetVoxelSize() const;`
- L39 _public prototype_ `FString GetVectorType() const;`
- L41 _public prototype_ `void VolumeSample(const TArray<FVector>& InPoints, TArray<FVector>& OutValues) const;`
- L43 _public prototype_ `FDataflowFloatVolume ComputeDivergence(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, const FDataflowBoolVolume* MaskVolume = nullptr) const;`
- L44 _public prototype_ `FDataflowFloatVolume ComputeMagnitude(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, const FDataflowBoolVolume* MaskVolume = nullptr) const;`
- L45 _public prototype_ `FDataflowFloatVectorVolume ComputeCurl(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, const FDataflowBoolVolume* MaskVolume = nullptr) const;`
- L46 _public prototype_ `FDataflowFloatVectorVolume ComputeNormalize(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, const FDataflowBoolVolume* MaskVolume = nullptr) const;`
- L49 _private prototype_ `FDataflowFloatVectorVolume(TSharedPtr<UE::DataflowVolume::Private::FDataflowFloatVectorVolumeImpl> InFloatVectorVolume);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DataflowVolume` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::DataflowVolume`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Internal/Dataflow/DataflowFloatVolume.h` (Internal)


#### struct `FDataflowFloatVolume`  
`struct FDataflowFloatVolume : public FDataflowVolume`  
_L24-184_
- reflection: `USTRUCT()`
- inherits: `FDataflowVolume`
- L26 _public member_ `inline static const FName TypeName = "Fl`
- L31 _public function_ `FDataflowFloatVolume()`
- L32 _public function_ `virtual ~FDataflowFloatVolume()`
- L34 _public prototype_ `TSharedPtr<const UE::DataflowVolume::Private::FDataflowFloatVolumeImpl> GetFloatVolumeImpl() const;`
- L35 _public prototype_ `TSharedPtr<UE::DataflowVolume::Private::FDataflowFloatVolumeImpl> GetFloatVolumeImpl();`
- L37 _public prototype_ `FVector GetVoxelSize() const;`
- L40 _public prototype_ `static FDataflowFloatVolume CreateSphereSDF(const float InVoxelSize, const float InRadius, const FVector& InCenter);` — Create a sphere SDF
- L43 _public prototype_ `static FDataflowFloatVolume CreateCubeSDF(const float InScale, const FVector& InCenter, const float InVoxelSize);` — Create a cube SDF
- L46 _public prototype_ `static FDataflowFloatVolume CreatePlatonicSolidSDF(const int32 InFaceCount, const float InScale, const FVector& InCenter, const float InVoxelSize);` — Create different types of solid SDF
- L49 _public prototype_ `static FDataflowFloatVolume CreateVolumeFromMeshDescription( const FMeshDescription& InMeshDescription, const FTransform& InTransform, const float InVoxelSize, const FDataflowVolume& InReferenceGrid, const EDataflowVolumeOutputType InOutputType, const FString& InGridName, const bool InUseWorldSpaceUnits, const float InExteriorBand, const float InInteriorBand, const int32 InExteriorBandVoxels, const int32 InInteriorBandVoxels, const bool bFillInterior, const bool bPreserveHoles, const float InIsoValue, FDataflowIntVolume& OutFaceIndexVolume);` — Create a volume from MeshDescription
- L67 _public prototype_ `void VolumeToSpheres( const int32 InMinSphereCount, const int32 InMaxSphereCount, const bool InOverlapping, const float InMinRadius, const float InMaxRadius, const float InIsoValue, const int32 InInstanceCount, TArray<FVector>& OutSphereCenters, TArray<float>& OutSphereRadii) const;` — Compute sphere packing in an SDF volume using original algorithm
- L79 _public prototype_ `void VolumeToSpheresImproved( const int32 InMinSphereCount, const int32 InMaxSphereCount, const bool InOverlapping, const float InMinRadius, const float InMaxRadius, const float InIsoValue, const int32 InInstanceCount, const int32 InRandomSeed, const EDataflowVolumeScatterType InScatterType, const float InSpread, const float InMinNumberOfPointsPerVoxel, const float InMaxNumberOfPointsPerVoxel, TArray<FVector>& OutSphereCenters, TArray<float>& OutSphereRadii) const;` — Compute sphere packing in an SDF volume using improved algorithm
- L96 _public prototype_ `FDataflowFloatVolume CovertSDFToFogVolume(const bool InPruneTolerance, const float InTolerance, const bool InFloodFillOutput, const bool InActivateInteriror) const;` — Convert SDF to Fog Volume
- L99 _public prototype_ `FDataflowFloatVolume CovertFogVolumeToSDF( const float InFogIsoValue, const bool InPruneTolerance, const float InTolerance, const bool InFloodFillOutput, const bool InActivateInteriror) const;` — Convert SDF to Fog Volume
- L107 _public prototype_ `void ConvertVolumeToMeshDescription(const float InIsoValue, const float InAdaptivity, FMeshDescription& OutMeshDescription) const;` — Convert volume to MeshDescription
- L110 _public prototype_ `void UniformVolumeScatter( const int32 InMinNumberOfPoints, const int32 InMaxNumberOfPoints, const int32 InRandomSeed, const float InIsoValue, const float InSpread, TArray<FVector>& OutPoints) const;` — Compute uniform point scatter in an SDF volume
- L119 _public prototype_ `void DenseUniformVolumeScatter( const float InMinNumberOfPointsPerVoxel, const float InMaxNumberOfPointsPerVoxel, const int32 InRandomSeed, const float InIsoValue, const float InSpread, TArray<FVector>& OutPoints) const;` — Compute dense uniform point scatter in an SDF volume
- L128 _public prototype_ `void NonUniformVolumeScatter( const float InMinNumberOfPointsPerVoxel, const float InMaxNumberOfPointsPerVoxel, const int32 InRandomSeed, const float InIsoValue, const float InSpread, TArray<FVector>& OutPoints) const;` — Compute a non uniform point scatter in an SDF volume
- L137 _public prototype_ `void VolumeSample(const TArray<FVector>& InPoints, TArray<float>& OutValues) const;` — Sample a volume
- L140 _public prototype_ `FDataflowFloatVectorVolume ComputeGradient(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, const FDataflowBoolVolume* MaskVolume = nullptr) const;` — Compute gradient
- L143 _public prototype_ `FDataflowFloatVolume ComputeCurvature(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, const FDataflowBoolVolume* MaskVolume = nullptr) const;` — Compute curvature
- L146 _public prototype_ `FDataflowFloatVolume ComputeLaplacian(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, const FDataflowBoolVolume* MaskVolume = nullptr) const;` — Compute Laplacian
- L149 _public prototype_ `FDataflowFloatVectorVolume ComputeClosestPoint(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, const FDataflowBoolVolume* MaskVolume = nullptr) const;` — Compute ClosestPoint
- L152 _public prototype_ `FDataflowFloatVolume VolumeCombine( const FDataflowFloatVolume& InVolumeB, const EDataflowVolumeSDFCombineOperation InOperation, const float InMultiplierA, const float InMultiplierB, const EDataflowVolumeSDFCombineResample InResample, const EDataflowVolumeSDFCombineInterpolation InInterpolation, const bool InPruneDegenerateTiles, const float InPruneTol) const;` — Combine SDF volumes
- L163 _public prototype_ `void VolumeToSpheresWithRelaxation( const int32 InPointCount, const int32 InScatterRandomSeed, const float InMinRadius, const float InMaxRadius, const int32 InRandomSeed, const float InIsoValue, const float InSpread, const bool InRemoveSpheres, const bool InApplyRelaxation, const int32 InSteps, const float InStepScalar, const bool InCorrectAgainstSurface, const float InDistanceThreshold, TArray<FSphere>& OutSpheres) const;` — Compute sphere packing in an SDF volume with relaxation
- L183 _private prototype_ `FDataflowFloatVolume(TSharedPtr<UE::DataflowVolume::Private::FDataflowFloatVolumeImpl> InFloatVolume);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DataflowVolume` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::DataflowVolume`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Internal/Dataflow/DataflowIntVolume.h` (Internal)


#### struct `FDataflowIntVolume`  
`struct FDataflowIntVolume : public FDataflowVolume`  
_L19-43_
- reflection: `USTRUCT()`
- inherits: `FDataflowVolume`
- L21 _public member_ `inline static const FName TypeName = "In`
- L26 _public function_ `FDataflowIntVolume()`
- L27 _public function_ `virtual ~FDataflowIntVolume()`
- L29 _public prototype_ `TSharedPtr<const UE::DataflowVolume::Private::FDataflowIntVolumeImpl> GetIntVolumeImpl() const;`
- L30 _public prototype_ `TSharedPtr<UE::DataflowVolume::Private::FDataflowIntVolumeImpl> GetIntVolumeImpl();`
- L32 _public prototype_ `FVector GetVoxelSize() const;`
- L35 _public prototype_ `void VolumeSample(const TArray<FVector>& InPoints, TArray<int32>& OutValues) const;` — Sample a volume
- L40 _private prototype_ `FDataflowIntVolume(TSharedPtr<UE::DataflowVolume::Private::FDataflowIntVolumeImpl> InIntVolume);`
- L42 _private prototype_ `void SetIntVolume(TSharedPtr<UE::DataflowVolume::Private::FDataflowIntVolumeImpl> InIntVolume);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DataflowVolume` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::DataflowVolume`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Internal/Dataflow/DataflowVolume.h` (Internal)


#### struct `FDataflowVolume`  
`struct FDataflowVolume`  
_L18-98_
- reflection: `USTRUCT()`
- L23 _public function_ `FDataflowVolume()`
- L24 _public function_ `virtual ~FDataflowVolume()`
- L26 _public prototype_ `int32 GetNumActiveVoxels(const float InIsovalue, bool bInteriorMaskOnly = false) const;`
- L27 _public prototype_ `void GetActiveVoxels(const float InIsovalue, TArray<FBox>& OutActiveVoxels, bool bInteriorMaskOnly = false) const;`
- L28 _public prototype_ `FBox GetVolumeBoundingBox() const;`
- L30 _public prototype_ `bool CreateVolumeTexture(UVolumeTexture* InVolumeTexture) const;`
- L33 _public prototype_ `FString VolumeInfo() const;` — Prints Volume info into string
- L34 _public function_ `FName GetType() const`
- L62 _public function_ `template<typename T> T* Cast()`
- L76 _public function_ `template<typename T> const T* Cast() const`
- L89 _public function_ `TSharedPtr<const UE::DataflowVolume::Private::FDataflowVolumeImpl> GetVolume() const`
- L92 _protected prototype_ `FDataflowVolume(TSharedPtr<UE::DataflowVolume::Private::FDataflowVolumeImpl> InVolume, const FName InType);`
- L94 _protected member_ `TSharedPtr<UE::DataflowVolume::Private::FDataflowVolumeImpl> Volume;`
- L97 _private member_ `FName Type;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DataflowVolume` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::DataflowVolume`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Internal/Dataflow/DataflowVolumeAnyType.h` (Internal)


#### struct `FDataflowVolumeTypePolicy`  
`struct FDataflowVolumeTypePolicy : public TDataflowMultiTypePolicy<FDataflowFloatVolume, FDataflowIntVolume, FDataflowFloatVectorVolume>`  
_L19-22_
- inherits: `TDataflowMultiTypePolicy<FDataflowFloatVolume,FDataflowIntVolume,FDataflowFloatVectorVolume>`

#### struct `FDataflowVolumeTypes`  
`struct FDataflowVolumeTypes : public FDataflowAnyType`  
_L25-34_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- L27 _public typedef_ `using FPolicyType = FDataflowVolumeTypePolicy;`
- L28 _public typedef_ `using FStorageType = FDataflowVolume;`
- L33 _public member_ `FDataflowVolume Value;` — `UPROPERTY()`

#### struct `FDataflowConverter`  
`template <> struct FDataflowConverter<FDataflowVolume>`  
_L37-53_
- L40 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowVolume& To)`
- L46 _public function_ `template <typename TToType> static void To(const FDataflowVolume& From, TToType& To)`

#### Free symbols / members of external scopes

- L55 _namespace_ `namespace UE`
- L55 _namespace_ `namespace Dataflow` (scope `UE`)
- L57 _prototype_ `void RegisterVolumeAnyTypes();` (scope `UE::Dataflow`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Internal/Dataflow/DataflowVolumeNodeEnums.h` (Internal)


#### enum `EDataflowVolumeOutputType`  
`enum class EDataflowVolumeOutputType : uint8`  
_L8-13_
- reflection: `UENUM(BlueprintType)`
- L10 _public enumerator_ `SDF UMETA(DisplayName = "Signed Distance Field")`
- L11 _public enumerator_ `USDF UMETA(DisplayName = "Unsigned Distance Field")`
- L12 _public enumerator_ `FogVolume UMETA(DisplayName = "Fog Volume")`

#### enum `EDataflowVolumeSDFCombineOperation`  
`enum class EDataflowVolumeSDFCombineOperation : uint8`  
_L16-36_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `CopyA UMETA(DisplayName = "Copy A")`
- L19 _public enumerator_ `CopyB UMETA(DisplayName = "Copy B")`
- L20 _public enumerator_ `InvertA UMETA(DisplayName = "Invert A")`
- L21 _public enumerator_ `Add UMETA(DisplayName = "Add")`
- L22 _public enumerator_ `Subtract UMETA(DisplayName = "Subtract")`
- L23 _public enumerator_ `Multiply UMETA(DisplayName = "Multiply")`
- L24 _public enumerator_ `Divide UMETA(DisplayName = "Divide")`
- L25 _public enumerator_ `Minimum UMETA(DisplayName = "Minimum")`
- L26 _public enumerator_ `Maximum UMETA(DisplayName = "Maximum")`
- L27 _public enumerator_ `CompATimesB UMETA(DisplayName = "(1 - A) * B")`
- L28 _public enumerator_ `APlusCompATimesB UMETA(DisplayName = "A + (1 - A) * B")`
- L29 _public enumerator_ `SDFUnion UMETA(DisplayName = "SDF Union")`
- L30 _public enumerator_ `SDFIntersect UMETA(DisplayName = "SDF Intersection")`
- L31 _public enumerator_ `SDFDifference UMETA(DisplayName = "SDF Difference")`
- L32 _public enumerator_ `ReplaceWithActive UMETA(DisplayName = "Replace A with Active B")`
- L33 _public enumerator_ `ActivityUnion UMETA(DisplayName = "Activity Union")`
- L34 _public enumerator_ `ActivityIntersect UMETA(DisplayName = "Activity Intersection")`
- L35 _public enumerator_ `ActivityDifference UMETA(DisplayName = "Activity Difference")`

#### enum `EDataflowVolumeSDFCombineResample`  
`enum class EDataflowVolumeSDFCombineResample : uint8`  
_L39-46_
- reflection: `UENUM(BlueprintType)`
- L41 _public enumerator_ `Off UMETA(DisplayName = "Off")`
- L42 _public enumerator_ `BMatchA UMETA(DisplayName = "B to Match A")`
- L43 _public enumerator_ `AMatchB UMETA(DisplayName = "A to Match B")`
- L44 _public enumerator_ `HiresMatchLores UMETA(DisplayName = "Higher-res to Match Lower-res")`
- L45 _public enumerator_ `LoresMatchHires UMETA(DisplayName = "Lower-res to Match Higher-res")`

#### enum `EDataflowVolumeSDFCombineInterpolation`  
`enum class EDataflowVolumeSDFCombineInterpolation : uint8`  
_L49-54_
- reflection: `UENUM(BlueprintType)`
- L51 _public enumerator_ `Nearest UMETA(DisplayName = "Nearest")`
- L52 _public enumerator_ `Linear UMETA(DisplayName = "Linear")`
- L53 _public enumerator_ `Quadratic UMETA(DisplayName = "Quadratic")`

#### enum `EDataflowVolumeConvertSDFTo`  
`enum class EDataflowVolumeConvertSDFTo : uint8`  
_L57-61_
- reflection: `UENUM(BlueprintType)`
- L59 _public enumerator_ `Volume UMETA(DisplayName = "Volume")`
- L60 _public enumerator_ `Collection UMETA(DisplayName = "Collection")`

#### enum `EDataflowVolumeConvertSDFGridClass`  
`enum class EDataflowVolumeConvertSDFGridClass : uint8`  
_L64-69_
- reflection: `UENUM(BlueprintType)`
- L66 _public enumerator_ `NoChange UMETA(DisplayName = "No Change")`
- L67 _public enumerator_ `SDFToFog UMETA(DisplayName = "SDF -> Fog Volume")`
- L68 _public enumerator_ `FogToSDF UMETA(DisplayName = "Fog Volume -> SDF")`

#### enum `EDataflowVolumeConvertSDFGridType`  
`enum class EDataflowVolumeConvertSDFGridType : uint8`  
_L72-80_
- reflection: `UENUM(BlueprintType)`
- L74 _public enumerator_ `NoChange UMETA(DisplayName = "No Change")`
- L75 _public enumerator_ `Float UMETA(DisplayName = "Float")`
- L76 _public enumerator_ `Int UMETA(DisplayName = "Int")`
- L77 _public enumerator_ `Bool UMETA(DisplayName = "Bool")`
- L78 _public enumerator_ `VectorFloat UMETA(DisplayName = "Vector Float")`
- L79 _public enumerator_ `VectorInt UMETA(DisplayName = "Vector Int")`

#### enum `EDataflowVolumeActiveVoxelsDisplayType`  
`enum class EDataflowVolumeActiveVoxelsDisplayType : uint8`  
_L83-88_
- reflection: `UENUM(BlueprintType)`
- L85 _public enumerator_ `Points UMETA(DisplayName = "Points")`
- L86 _public enumerator_ `WwireframeBoxes UMETA(DisplayName = "Wireframe Boxes")`
- L87 _public enumerator_ `SolidBoxes UMETA(DisplayName = "Solid Boxes")`

#### enum `EDataflowVolumePlatonicSolidType`  
`enum class EDataflowVolumePlatonicSolidType : uint8`  
_L91-98_
- reflection: `UENUM(BlueprintType)`
- L93 _public enumerator_ `Tetrahedron UMETA(DisplayName = "Tetrahedron")`
- L94 _public enumerator_ `Cube UMETA(DisplayName = "Cube")`
- L95 _public enumerator_ `Octahedron UMETA(DisplayName = "Octahedron")`
- L96 _public enumerator_ `Dodecahedron UMETA(DisplayName = "Dodecahedron")`
- L97 _public enumerator_ `Icosahedron UMETA(DisplayName = "Icosahedron")`

#### enum `EDataflowVolumeSampleAttribute`  
`enum class EDataflowVolumeSampleAttribute : uint8`  
_L101-111_
- reflection: `UENUM(BlueprintType)`
- L103 _public enumerator_ `Phi UMETA(DisplayName = "Vertex/Phi")`
- L104 _public enumerator_ `Gradient UMETA(DisplayName = "Vertex/Gradient")`
- L105 _public enumerator_ `VertexColor UMETA(DisplayName = "Vertex/Color")`
- L106 _public enumerator_ `VertexClosestFaceID UMETA(DisplayName = "Vertex/ClosestFaceID")`
- L107 _public enumerator_ `VertexUV UMETA(DisplayName = "Vertex/UV")`
- L108 _public enumerator_ `FaceMaterialID UMETA(DisplayName = "Face/MaterialID")`
- L109 _public enumerator_ `VertexCustomAttribute UMETA(DisplayName = "Vertex/Custom Attribute")`
- L110 _public enumerator_ `FaceCustomAttribute UMETA(DisplayName = "Face/Custom Attribute")`

#### enum `EDataflowVolumeSampleType`  
`enum class EDataflowVolumeSampleType : uint8`  
_L114-119_
- reflection: `UENUM(BlueprintType)`
- L116 _public enumerator_ `Float UMETA(DisplayName = "Float")`
- L117 _public enumerator_ `Int UMETA(DisplayName = "Int")`
- L118 _public enumerator_ `FloatVector UMETA(DisplayName = "FloatVector")`

#### enum `EDataflowVolumeSampleLocation`  
`enum class EDataflowVolumeSampleLocation : uint8`  
_L122-126_
- reflection: `UENUM(BlueprintType)`
- L124 _public enumerator_ `Vertices UMETA(DisplayName = "Vertices")`
- L125 _public enumerator_ `FaceCenters UMETA(DisplayName = "Face Centers")`

#### enum `EDataflowVolumeSliceMethod`  
`enum class EDataflowVolumeSliceMethod : uint8`  
_L129-132_
- reflection: `UENUM(BlueprintType)`
- L131 _public enumerator_ `Points UMETA(DisplayName = "Points")`

#### enum `EDataflowVolumeSlicePlane`  
`enum class EDataflowVolumeSlicePlane : uint8`  
_L135-140_
- reflection: `UENUM(BlueprintType)`
- L137 _public enumerator_ `XYPlane UMETA(DisplayName = "XY Plane")`
- L138 _public enumerator_ `YZPlane UMETA(DisplayName = "YZ Plane")`
- L139 _public enumerator_ `ZXPlane UMETA(DisplayName = "ZX Plane")`

#### enum `EDataflowVolumeSliceRamp`  
`enum class EDataflowVolumeSliceRamp : uint8`  
_L143-150_
- reflection: `UENUM(BlueprintType)`
- L145 _public enumerator_ `InfraRed UMETA(DisplayName = "Infra-Red")`
- L146 _public enumerator_ `WhiteToRed UMETA(DisplayName = "White to Red")`
- L147 _public enumerator_ `Grayscale UMETA(DisplayName = "Grayscale")`
- L148 _public enumerator_ `BlackBody UMETA(DisplayName = "Blackbody")`
- L149 _public enumerator_ `Custom UMETA(DisplayName = "Custom")`

#### enum `EDataflowVolumeAnalysisOperator`  
`enum class EDataflowVolumeAnalysisOperator : uint8`  
_L153-163_
- reflection: `UENUM(BlueprintType)`
- L155 _public enumerator_ `Gradient UMETA(DisplayName = "Gradient (Scalar->Vector)")`
- L156 _public enumerator_ `Curvature UMETA(DisplayName = "Curvature (Scalar->Scalar)")`
- L157 _public enumerator_ `Laplacian UMETA(DisplayName = "Laplacian (Scalar->Scalar)")`
- L158 _public enumerator_ `ClosestPoint UMETA(DisplayName = "Closest Point (Scalar->Vector)")`
- L159 _public enumerator_ `Divergence UMETA(DisplayName = "Divergence (Vector->Scalar)")`
- L160 _public enumerator_ `Curl UMETA(DisplayName = "Curl (Vector->Vector)")`
- L161 _public enumerator_ `Magnitude UMETA(DisplayName = "Magnitude (Vector->Scalar)")`
- L162 _public enumerator_ `Normalize UMETA(DisplayName = "Normalize (Vector->Vector)")`

#### enum `EDataflowVolumeAnalysisOutputName`  
`enum class EDataflowVolumeAnalysisOutputName : uint8`  
_L166-170_
- reflection: `UENUM(BlueprintType)`
- L168 _public enumerator_ `AppendOperationName UMETA(DisplayName = "Append Operation Name")`
- L169 _public enumerator_ `CustomName UMETA(DisplayName = "Custom Name")`

#### enum `EDataflowVolumeScatterType`  
`enum class EDataflowVolumeScatterType : uint8`  
_L173-178_
- reflection: `UENUM(BlueprintType)`
- L175 _public enumerator_ `Uniform UMETA(DisplayName = "Uniform")`
- L176 _public enumerator_ `DenseUniform UMETA(DisplayName = "Dense Uniform")`
- L177 _public enumerator_ `NonUniform UMETA(DisplayName = "Non Uniform")`

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Private/Dataflow/DataflowBoolVolumeImpl.h` (Private)


#### class `UE::DataflowVolume::Private::FDataflowBoolVolumeImpl`  
`class FDataflowBoolVolumeImpl : public FDataflowVolumeImpl`  
_L13-29_
- inherits: `FDataflowVolumeImpl`
- L16 _private member_ `openvdb::BoolGrid::Ptr BoolGrid = nullptr;`
- L20 _public prototype_ `virtual void GetActiveVoxels(const float InIsovalue, TArray<FBox>& OutActiveVoxels, bool bInteriorMaskOnly = false) const override;` — Virtual functions
- L21 _public prototype_ `virtual FBox GetVolumeBoundingBox() const override;`
- L22 _public prototype_ `virtual bool CreateVolumeTexture(UVolumeTexture* InVolumeTexture) const override;`
- L24 _public prototype_ `openvdb::BoolGrid::Ptr GetGrid() const;`
- L25 _public prototype_ `void SetGrid(const openvdb::BoolGrid::Ptr& InBoolGrid, const FString& InGridName = "");`
- L26 _public prototype_ `FString GetGridType() const;`
- L27 _public prototype_ `FString VolumeInfo() const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DataflowVolume` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::DataflowVolume`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Private/Dataflow/DataflowFloatVectorVolumeImpl.h` (Private)


#### class `UE::DataflowVolume::Private::FDataflowFloatVectorVolumeImpl`  
`class FDataflowFloatVectorVolumeImpl : public FDataflowVolumeImpl`  
_L19-46_
- inherits: `FDataflowVolumeImpl`
- L22 _private member_ `openvdb::VectorGrid::Ptr FloatVectorGrid = nullptr;`
- L26 _public prototype_ `void GetActiveVoxels(const float InIsovalue, TArray<FBox>& OutActiveVoxels, bool bInteriorMaskOnly = false) const;` — Virtual functions
- L27 _public prototype_ `virtual FBox GetVolumeBoundingBox() const override;`
- L28 _public prototype_ `virtual bool CreateVolumeTexture(UVolumeTexture* InVolumeTexture) const override;`
- L30 _public prototype_ `void SetGrid(const openvdb::VectorGrid::Ptr& InFloatVectorGrid, const openvdb::VecType InVecType, const FString& InGridName = "Gra`
- L32 _public prototype_ `openvdb::VectorGrid::Ptr GetGrid() const;`
- L34 _public prototype_ `FString GetGridType() const;`
- L36 _public prototype_ `FString GetVectorType() const;`
- L38 _public prototype_ `FString VolumeInfo() const;`
- L40 _public prototype_ `void VolumeSample(const TArray<FVector>& InPoints, TArray<FVector>& OutValues) const;`
- L42 _public prototype_ `TSharedPtr<FDataflowFloatVolumeImpl> ComputeDivergence(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, TSharedPtr<const FDataflowBoolVolumeImpl> InMaskVolumeImpl) const;`
- L43 _public prototype_ `TSharedPtr<FDataflowFloatVolumeImpl> ComputeMagnitude(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, TSharedPtr<const FDataflowBoolVolumeImpl> InMaskVolumeImpl) const;`
- L44 _public prototype_ `TSharedPtr<FDataflowFloatVectorVolumeImpl> ComputeCurl(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, TSharedPtr<const FDataflowBoolVolumeImpl> InMaskVolumeImpl) const;`
- L45 _public prototype_ `TSharedPtr<FDataflowFloatVectorVolumeImpl> ComputeNormalize(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, TSharedPtr<const FDataflowBoolVolumeImpl> InMaskVolumeImpl) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DataflowVolume` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DataflowVolume`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Private/Dataflow/DataflowFloatVolumeImpl.h` (Private)


#### class `UE::DataflowVolume::Private::FDataflowFloatVolumeImpl`  
`class FDataflowFloatVolumeImpl : public FDataflowVolumeImpl`  
_L25-176_
- inherits: `FDataflowVolumeImpl`
- L28 _private member_ `openvdb::FloatGrid::Ptr FloatGrid = nullptr;`
- L32 _public prototype_ `virtual FString VolumeInfo() const override;` — Virtual functions
- L33 _public prototype_ `virtual void GetActiveVoxels(const float InIsovalue, TArray<FBox>& OutActiveVoxels, bool bInteriorMaskOnly = false) const override;`
- L34 _public prototype_ `virtual FBox GetVolumeBoundingBox() const override;`
- L35 _public prototype_ `virtual bool CreateVolumeTexture(UVolumeTexture* InVolumeTexture) const override;`
- L37 _public prototype_ `openvdb::FloatGrid::Ptr GetGrid() const;`
- L39 _public prototype_ `void SetGrid(const openvdb::FloatGrid::Ptr& InFloatGrid, const openvdb::GridClass InGridClass, const FString& InGridName = TEXT("Leve`
- L41 _public prototype_ `FString GetGridType() const;`
- L43 _public prototype_ `FString GetGridClass() const;`
- L45 _public prototype_ `static TSharedPtr<FDataflowFloatVolumeImpl> CreateSphereSDF( const float InVoxelSize, const float InRadius, const FVector& InCenter);`
- L50 _public prototype_ `static TSharedPtr<FDataflowFloatVolumeImpl> CreateCubeSDF( const float InScale, const FVector& InCenter, const float InVoxelSize);`
- L55 _public prototype_ `static TSharedPtr<FDataflowFloatVolumeImpl> CreatePlatonicSolidSDF( const int32 InFaceCount, const float InScale, const FVector& InCenter, const float InVoxelSize);`
- L61 _public prototype_ `static TSharedPtr<FDataflowFloatVolumeImpl> CreateVolumeFromMeshDescription( const FMeshDescription& InMeshDescription, const FTransform& InTransform, const float InVoxelSize, const TSharedPtr<const FDataflowVolumeImpl>& InReferenceVolumeImpl, const EDataflowVolumeOutputType InOutputType, const FString& InGridName, const bool InUseWorldSpaceUnits, const float InExteriorBand, const float InInteriorBand, const int32 InExteriorBandVoxels, const int32 InInteriorBandVoxels, const bool bFillInterior, const bool bPreserveHoles, const float InIsoValue, TSharedPtr<FDataflowIntVolumeImpl>& OutFaceIndexVolume);`
- L78 _public prototype_ `void VolumeToSpheres(const int32 InMinSphereCount, const int32 InMaxSphereCount, const bool InOverlapping, const float InMinRadius, float InMaxRadius, const float InIsoValue, const int32 InInstanceCount, TArray<FVector>& OutSphereCenters, TArray<float>& OutSphereRadii) const;`
- L88 _public prototype_ `void VolumeToSpheresImproved(const int32 InMinSphereCount, const int32 InMaxSphereCount, const bool InOverlapping, const float InMinRadius, float InMaxRadius, const float InIsoValue, const int32 InInstanceCount, const int32 InRandomSeed, const EDataflowVolumeScatterType InScatterType, const float InSpread, const float InMinNumberOfPointsPerVoxel, const float InMaxNumberOfPointsPerVoxel, TArray<FVector>& OutSphereCenters, TArray<float>& OutSphereRadii) const;`
- L103 _public prototype_ `TSharedPtr<FDataflowFloatVolumeImpl> CovertSDFToFogVolume( const bool InPruneTolerance, const float InTolerance, const bool InFloodFillOutput, const bool InActivateInteriror) const;`
- L109 _public prototype_ `TSharedPtr<FDataflowFloatVolumeImpl> CovertFogVolumeToSDF( const float InFogIsoValue, const bool InPruneTolerance, const float InTolerance, const bool InFloodFillOutput, const bool InActivateInteriror) const;`
- L116 _public prototype_ `void CovertSDFToCollection(const float InIsoValue, const float InAdaptivity, FManagedArrayCollection& OutCollection) const;`
- L118 _public prototype_ `void ConvertVolumeToMeshDescription(const float InIsoValue, const float InAdaptivity, FMeshDescription& OutMeshDescription) const;`
- L120 _public prototype_ `void UniformVolumeScatter( const int32 InMinNumberOfPoints, const int32 InMaxNumberOfPoints, const int32 InRandomSeed, const float InIsoValue, const float InSpread, TArray<FVector>& OutPoints) const;`
- L128 _public prototype_ `void DenseUniformVolumeScatter( const float InMinNumberOfPointsPerVoxel, const float InMaxNumberOfPointsPerVoxel, const int32 InRandomSeed, const float InIsoValue, const float InSpread, TArray<FVector>& OutPoints) const;`
- L136 _public prototype_ `void NonUniformVolumeScatter( const float InMinNumberOfPointsPerVoxel, const float InMaxNumberOfPointsPerVoxel, const int32 InRandomSeed, const float InIsoValue, const float InSpread, TArray<FVector>& OutPoints) const;`
- L144 _public prototype_ `void VolumeSample(const TArray<FVector>& InPoints, TArray<float>& OutValues) const;`
- L146 _public prototype_ `TSharedPtr<FDataflowFloatVectorVolumeImpl> ComputeGradient(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, TSharedPtr<const FDataflowBoolVolumeImpl> InMaskVolumeImpl) const;`
- L147 _public prototype_ `TSharedPtr<FDataflowFloatVolumeImpl> ComputeCurvature(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, TSharedPtr<const FDataflowBoolVolumeImpl> InMaskVolumeImpl) const;`
- L148 _public prototype_ `TSharedPtr<FDataflowFloatVolumeImpl> ComputeLaplacian(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, TSharedPtr<const FDataflowBoolVolumeImpl> InMaskVolumeImpl) const;`
- L149 _public prototype_ `TSharedPtr<FDataflowFloatVectorVolumeImpl> ComputeClosestPoint(const EDataflowVolumeAnalysisOutputName OutputName, const FString& CustomName, TSharedPtr<const FDataflowBoolVolumeImpl> InMaskVolumeImpl) const;`
- L151 _public prototype_ `TSharedPtr<FDataflowFloatVolumeImpl> VolumeCombine( TSharedPtr<const FDataflowFloatVolumeImpl> InVolumeBImpl, const EDataflowVolumeSDFCombineOperation InOperation, const float InMultiplierA, const float InMultiplierB, const EDataflowVolumeSDFCombineResample InResample, const EDataflowVolumeSDFCombineInterpolation InInterpolation, const bool InPruneDegenerateTiles, const float InPruneTol) const;`
- L161 _public prototype_ `void VolumeToSpheresWithRelaxation( const int32 InPointCount, const int32 InScatterRandomSeed, const float InMinRadius, const float InMaxRadius, const int32 InRandomSeed, const float InIsoValue, const float InSpread, const bool InRemoveSpheres, const bool InApplyRelaxation, const int32 InSteps, const float InStepScalar, const bool InCorrectAgainstSurface, const float InDistanceThreshold, TArray<FSphere>& OutSpheres) const;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DataflowVolume` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::DataflowVolume`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Private/Dataflow/DataflowIntVolumeImpl.h` (Private)


#### class `UE::DataflowVolume::Private::FDataflowIntVolumeImpl`  
`class FDataflowIntVolumeImpl : public FDataflowVolumeImpl`  
_L14-34_
- inherits: `FDataflowVolumeImpl`
- L17 _private member_ `openvdb::Int32Grid::Ptr IntGrid = nullptr;`
- L21 _public prototype_ `virtual FString VolumeInfo() const override;` — Virtual functions
- L22 _public prototype_ `void GetActiveVoxels(const float InIsovalue, TArray<FBox>& OutActiveVoxels, bool bInteriorMaskOnly = false) const;`
- L23 _public prototype_ `virtual FBox GetVolumeBoundingBox() const override;`
- L24 _public prototype_ `virtual bool CreateVolumeTexture(UVolumeTexture* InVolumeTexture) const override;`
- L26 _public prototype_ `openvdb::Int32Grid::Ptr GetGrid() const;`
- L28 _public prototype_ `void SetGrid(const openvdb::Int32Grid::Ptr& InIntGrid, const FString& InGridName = "");`
- L30 _public prototype_ `FString GetGridType() const;`
- L32 _public prototype_ `void VolumeSample(const TArray<FVector>& InPoints, TArray<int32>& OutValues) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DataflowVolume` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::DataflowVolume`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Private/Dataflow/DataflowVolumeAlgo.h` (Private)


#### Free symbols / members of external scopes

- L37 _function_ `template<typename GridT, typename InterrupterT = openvdb::util::NullInterrupter> void FillWithSpheres( const GridT& grid, std::vector<openvdb::Vec4s>& spheres, const openvdb::Vec2i& sphereCount, bool overlapping, float minRadius, float maxRadius, float isovalue, int instanceCount, int32 InRandomSeed, EDataflowVolumeScatterType InScatterType, float InSpread, float InMinNumberOfPointsPerVoxel, float InMaxNumberOfPointsPerVoxel, InterrupterT* interrupter = nullptr)`
- L109 _typedef_ `using TreeT = typename GridT::TreeType;` (scope `FillWithSpheres`)
- L110 _typedef_ `using BoolTreeT = typename TreeT::template ValueConverter<bool>::Type;` (scope `FillWithSpheres`)
- L111 _typedef_ `using Int16TreeT = typename TreeT::template ValueConverter<openvdb::Int16>::Type;` (scope `FillWithSpheres`)
- L113 _typedef_ `using RandGen = std::mersenne_twister_engine<uint32_t, 32, 351, 175, 19, 0xccab8ee7, 11, 0xffffffff, 7, 0x31b6ab00, 15, 0xffe50000, 17, 1812433253>;` (scope `FillWithSpheres`)
- L263 _namespace_ `namespace DataflowVolumeToSpheres`
- L263 _namespace_ `namespace Private` (scope `DataflowVolumeToSpheres`)
- L265 _function_ `static FVector ToVector(const openvdb::Vec3R& InPoint)` (scope `DataflowVolumeToSpheres::Private`)
- L270 _function_ `static openvdb::Vec3R ToPoint(const FVector& InVector)` (scope `DataflowVolumeToSpheres::Private`)
- L275 _function_ `static bool IsSphereContainedInSphere(const FVector& InCenterA, const FVector& InCenterB, const float InRadiusA, const float InRadiusB)` (scope `DataflowVolumeToSpheres::Private`)
- L293 _function_ `static void ComputeDisplacement(const FVector& InCenterA, const FVector& InCenterB, const float InRadiusA, const float InRadiusB, const float InStepScalar, FVector& OutDisplacementA, FVector& OutDisplacementB)` (scope `DataflowVolumeToSpheres::Private`)
- L321 _function_ `static bool ComputeDisplacementAgainsSurface(const FVector& InCenter, const float InRadius, const float InDistanceThreshold, const auto& InCsp, const openvdb::FloatGrid::ConstAccessor& InAccessor, const auto& InTransform, FVector& OutDisplacement)` (scope `DataflowVolumeToSpheres::Private`)
- L385 _function_ `template<typename GridT, typename InterrupterT = openvdb::util::NullInterrupter> void VolumeToSpheresWithRelaxationProc( const GridT& InGrid, std::vector<openvdb::Vec4s>& OutSpheres, int32 InPointCount, const int32 InScatterRandomSeed, const float InMinRadius, const float InMaxRadius, const int32 InRandomSeed, float InIsovalue, float InSpread, bool InRemoveSpheres, bool InApplyRelaxation, int32 InSteps, float InStepScalar, bool InCorrectAgainstSurface, float InDistanceThreshold, InterrupterT* InInterrupter = nullptr)`
- L452 _typedef_ `using TreeT = typename GridT::TreeType;` (scope `VolumeToSpheresWithRelaxationProc`)
- L453 _typedef_ `using BoolTreeT = typename TreeT::template ValueConverter<bool>::Type;` (scope `VolumeToSpheresWithRelaxationProc`)
- L454 _typedef_ `using Int16TreeT = typename TreeT::template ValueConverter<openvdb::Int16>::Type;` (scope `VolumeToSpheresWithRelaxationProc`)
- L456 _typedef_ `using RandGen = std::mersenne_twister_engine<uint32_t, 32, 351, 175, 19, 0xccab8ee7, 11, 0xffffffff, 7, 0x31b6ab00, 15, 0xffe50000, 17, 1812433253>;` (scope `VolumeToSpheresWithRelaxationProc`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Private/Dataflow/DataflowVolumeCoreModule.h` (Private)


#### class `IDataflowVolumeCoreModule`  
`class IDataflowVolumeCoreModule : public IModuleInterface`  
_L14-30_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public function_ `virtual bool SupportsDynamicReloading() override`

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Private/Dataflow/DataflowVolumeImpl.h` (Private)


#### class `UE::DataflowVolume::Private::FDataflowVolumeImpl`  
`class FDataflowVolumeImpl`  
_L16-48_
- L19 _private member_ `openvdb::GridBase::Ptr BaseGrid;`
- L22 _public prototype_ `bool IsGridEmpty() const;`
- L24 _public prototype_ `FVector GetVoxelSize() const;`
- L26 _public prototype_ `FString GetGridName() const;`
- L28 _public prototype_ `int32 GetActiveVoxelCount() const;`
- L30 _public prototype_ `virtual void GetActiveVoxels(const float InIsovalue, TArray<FBox>& OutActiveVoxels, bool bInteriorMaskOnly = false) const = 0;`
- L32 _public prototype_ `virtual FBox GetVolumeBoundingBox() const = 0;`
- L34 _public prototype_ `FIntVector3 GetActiveVoxelDim() const;`
- L36 _public prototype_ `FBox GetActiveVoxelBoundingBox() const;`
- L38 _public prototype_ `FTransform GetGridTransform() const;`
- L40 _public prototype_ `virtual FString VolumeInfo() const;`
- L42 _public function_ `virtual ~FDataflowVolumeImpl()`
- L44 _public prototype_ `virtual bool CreateVolumeTexture(UVolumeTexture* InVolumeTexture) const = 0;`
- L47 _protected prototype_ `void SetGrid(const openvdb::GridBase::Ptr& InGrid, const FString& InGridName);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DataflowVolume` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DataflowVolume`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Private/Dataflow/DataflowVolumeUtils.h` (Private)


#### class `UE::DataflowVolumeUtils::FPlacedMesh`  
`class FPlacedMesh`  
_L33-58_
- L36 _public function_ `FPlacedMesh() : Mesh(nullptr)`
- L40 _public function_ `explicit FPlacedMesh(const FMeshDescription* MeshIn, const FTransform& TransformIn = FTransform::Identity) : Mesh(MeshIn), Transform(TransformIn)`
- L44 _public function_ `FPlacedMesh(const FPlacedMesh& other) : Mesh(other.Mesh) , Transform(other.Transform)`
- L49 _public function_ `FPlacedMesh& operator=(const FPlacedMesh& other)`
- L56 _public member_ `const FMeshDescription* Mesh;`
- L57 _public member_ `FTransform Transform;`

#### struct `UE::DataflowVolumeUtils::FInterrupter`  
`struct FInterrupter`  
_L61-69_
- desc: the interrupter interface.
- L63 _public prototype_ `FInterrupter() = default;`
- L64 _public prototype_ `virtual ~FInterrupter() = default;`
- L66 _public function_ `virtual void start(const char* name = nullptr)` — templated openvdb code requires these functions.
- L67 _public function_ `virtual void end()`
- L68 _public function_ `virtual bool wasInterrupted(int percent = -1)`

#### class `UE::DataflowVolumeUtils::FMeshDescriptionAdapter`  
`class FMeshDescriptionAdapter`  
_L75-123_
- desc: Mesh adapter class that implements the needed API for the methods in openvdb that convert polygonal mesh to a signed distance field.
- L81 _public prototype_ `FMeshDescriptionAdapter(const FMeshDescription& InRawMesh, const openvdb::math::Transform& InTransform);` — Constructor
- L82 _public prototype_ `FMeshDescriptionAdapter(const FMeshDescriptionAdapter& other);`
- L85 _public prototype_ `size_t polygonCount() const;` — Total number of polygons
- L88 _public prototype_ `size_t pointCount() const;` — Total number of points (vertex locations)
- L91 _public function_ `size_t vertexCount(size_t n) const` — Vertex count for polygon n: currently FMeshDescription is just triangles.
- L94 _public prototype_ `void getIndexSpacePoint(size_t FaceNumber, size_t CornerNumber, openvdb::Vec3d& pos) const;` — Return position pos in local grid index space for polygon n and vertex v
- L99 _public function_ `const openvdb::math::Transform& GetTransform() const` — The transform used to map between the physical space of the mesh and the voxel space.
- L107 _private member_ `const FMeshDescription* RawMesh;` — Pointer to the raw mesh we are wrapping
- L113 _private prototype_ `void InitializeCacheData();` — Cache data
- L114 _private member_ `uint32 TriangleCount;`
- L115 _private member_ `TVertexAttributesConstRef<FVector3f> VertexPositions;`
- L117 _private member_ `TArray<FVertexInstanceID> IndexBuffer;` — Local version of the index array.  The FMeshDescription doesn't really have one.
- L122 _private member_ `const openvdb::math::Transform Transform;` — Transform used to convert the mesh space into the index space used by voxelization

#### struct `UE::DataflowVolumeUtils::FMixedPolyMesh`  
`struct FMixedPolyMesh`  
_L133-197_
- desc: Mesh type that holds minimal required data for openvdb iso-surface extraction interface. Implements the openvdb MeshDataAdapter interface. NB: std::vector required by the openvdb interface.
- L135 _public member_ `std::vector<openvdb::Vec3s> Points;`
- L136 _public member_ `std::vector<openvdb::Vec4I> Quads;`
- L137 _public member_ `std::vector<openvdb::Vec3I> Triangles;`
- L138 _public member_ `openvdb::math::Transform Transform;`
- L144 _public function_ `size_t polygonCount() const` — Total number of polygons
- L150 _public function_ `size_t pointCount() const` — Total number of points (vertex locations)
- L156 _public function_ `size_t vertexCount(size_t n) const` — Vertex count for polygon n
- L162 _public function_ `void getIndexSpacePoint(size_t n, size_t v, openvdb::Vec3d& pos) const` — Return position pos in local grid index space for polygon n and vertex v
- L178 _private function_ `bool PolygonIsQuad(size_t n) const`
- L183 _private function_ `bool PolygonIsTriangle(size_t n) const`
- L188 _private function_ `size_t GetQuadIndex(size_t n) const`
- L193 _private function_ `size_t GetTriangleIndex(size_t n) const`

#### class `UE::DataflowVolumeUtils::FPositionNormalVertex`  
`class FPositionNormalVertex`  
_L206-296_
- desc: Simplifier vertex type that stores position and normal. Implements the interface needed by templated simplifier code.
- L208 _private typedef_ `typedef FPositionNormalVertex VertType;`
- L210 _public function_ `FPositionNormalVertex()`
- L214 _public member_ `uint32 MaterialIndex = 0;`
- L215 _public member_ `FVector3f Position;`
- L218 _public member_ `FVector3f Normal;` — ---- Attributes -------- currently just the components of the normal.
- L222 _public function_ `static uint32 NumAttributes()` — Attributes are all assumed to be floats.
- L229 _public function_ `uint32 GetMaterialIndex() const` — Methods needed by the simplifier.
- L230 _public function_ `FVector3f& GetPos()`
- L231 _public function_ `const FVector3f& GetPos() const`
- L232 _public function_ `float* GetAttributes()`
- L233 _public function_ `const float* GetAttributes() const`
- L236 _public function_ `void Correct()`
- L239 _public function_ `bool operator==(const VertType& OtherVert) const` — Note this uses exact float compares..
- L251 _public function_ `bool operator!=(const VertType& OtherVert)`
- L259 _public function_ `VertType operator+(const VertType& OtherVert) const` — NB: Addition isn't commutative since the MaterialIndex.. maybe Result.MaterialIndex = min(this->MaterialIndex, Other.MaterialIndex) would be better.
- L270 _public function_ `VertType operator-(const VertType& OtherVert) const` — NB: A-B != -(B-A) because of the material index.
- L281 _public function_ `VertType operator*(const float Scalar) const` — NB: The normal isn't unit length after this..
- L291 _public function_ `VertType operator/(const float Scalar) const`

#### enum `UE::DataflowVolumeUtils::FPositionNormalVertex::(anonymous)`  
`enum`  
_L212-212_

#### class `UE::DataflowVolumeUtils::TAOSMesh`  
`template <typename SimplifierVertexType> class TAOSMesh`  
_L304-353_
- desc: A Triangle Mesh Array Of Structs (AOS) for the vertex data.  This should work with the simplification code.
- L308 _public typedef_ `typedef SimplifierVertexType VertexType;`
- L310 _public prototype_ `TAOSMesh();`
- L311 _public prototype_ `TAOSMesh(int32 VertCount, int32 FaceCount);`
- L313 _public prototype_ `~TAOSMesh();`
- L316 _public prototype_ `void Empty();` — reset the mesh to size zero, deleting content.
- L319 _public prototype_ `void Resize(int32 VertCount, int32 FaceCount);` — resize the mesh, deleting the current content.
- L322 _public prototype_ `void SetVertexAndIndexCount(uint32 VertCount, uint32 IndexCount);` — set the real vertex & index count after duplicate removal
- L325 _public prototype_ `void Swap(TAOSMesh& other);` — Swap content with an existing mesh of the same type.
- L329 _public prototype_ `openvdb::Vec3I GetFace(int32 FaceNumber) const;` — Get the indices that correspond to this face.
- L332 _public prototype_ `void GetPosArray(std::vector<FVector3f>& PosArray) const;` — Get an array of positions only.
- L336 _public prototype_ `int32 ComputeDegenerateTriCount() const;` — This method is for testing only.  Not designed for perf.
- L339 _public function_ `bool IsEmpty() const`
- L340 _public function_ `uint32 GetNumVertexes() const`
- L341 _public function_ `uint32 GetNumIndexes() const`
- L344 _public member_ `VertexType* Vertexes;` — unfettered public access.
- L345 _public member_ `uint32* Indexes;`
- L349 _private member_ `uint32 NumVertexes;`
- L350 _private member_ `uint32 NumIndexes;`
- L352 _private prototype_ `TAOSMesh(const TAOSMesh& other);`
- L392 _function_ `template <typename SimplifierVertexType> TAOSMesh<SimplifierVertexType>::TAOSMesh() : Vertexes(NULL), Indexes(NULL), NumVertexes(0), NumIndexes(0)`
- L400 _function_ `template <typename SimplifierVertexType> TAOSMesh<SimplifierVertexType>::TAOSMesh(int32 VertCount, int32 FaceCount) : Vertexes(NULL), Indexes(NULL), NumVertexes(0), NumIndexes(0)`
- L410 _function_ `template <typename SimplifierVertexType> TAOSMesh<SimplifierVertexType>::~TAOSMesh()`
- L416 _function_ `template <typename SimplifierVertexType> void TAOSMesh<SimplifierVertexType>::Empty()`
- L428 _function_ `template <typename SimplifierVertexType> void TAOSMesh<SimplifierVertexType>::Resize(int32 VertCount, int32 FaceCount)`
- L446 _function_ `template <typename SimplifierVertexType> void TAOSMesh<SimplifierVertexType>::SetVertexAndIndexCount(uint32 VertCount, uint32 IndexCount)`
- L456 _function_ `template <typename SimplifierVertexType> void TAOSMesh<SimplifierVertexType>::Swap(TAOSMesh& other)`
- L486 _function_ `template <typename SimplifierVertexType> openvdb::Vec3I TAOSMesh<SimplifierVertexType>::GetFace(int32 FaceNumber) const`
- L495 _function_ `template <typename SimplifierVertexType> void TAOSMesh<SimplifierVertexType>::GetPosArray(std::vector<FVector3f>& PosArray) const`
- L515 _function_ `template <typename SimplifierVertexType> int32 TAOSMesh<SimplifierVertexType>::ComputeDegenerateTriCount() const`

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace DataflowVolumeUtils` (scope `UE`)
- L212 _enumerator_ `enum { NumAttributesValue = 3 }; uint32 MaterialIndex = 0; FVector3f Position; FVector3f Normal;` (scope `UE::DataflowVolumeUtils::FPositionNormalVertex::__anon4797809f0103`)
- L360 _typedef_ `typedef TAOSMesh<FPositionNormalVertex> FAOSMesh;` (scope `UE::DataflowVolumeUtils`) — Array of structs mesh composed of vertices that are compatible with the simplifier.
- L363 _typedef_ `typedef tbb::blocked_range<int32> FIntRange;` (scope `UE::DataflowVolumeUtils`) — Threaded wrappers
- L364 _typedef_ `typedef tbb::blocked_range<uint32> FUIntRange;` (scope `UE::DataflowVolumeUtils`)
- L365 _typedef_ `typedef tbb::blocked_range2d<int32> FIntRange2d;` (scope `UE::DataflowVolumeUtils`)
- L368 _function_ `template <typename RangeType, typename FunctorType> void Parallel_For(const RangeType& Range, const FunctorType& Functor, const bool bParallel = true)` (scope `UE::DataflowVolumeUtils`)
- L376 _function_ `` (scope `UE::DataflowVolumeUtils::Parallel_For`)
- L502 _function_ `` (scope `UE::DataflowVolumeUtils::TAOSMesh::GetPosArray`)
- L550 _prototype_ `template <typename T> void MixedPolyMeshToAOSMesh(const FMixedPolyMesh& InMesh, TAOSMesh<T>& OutMesh, const bool bClockWise = true);` (scope `UE::DataflowVolumeUtils`) — Convert a mixed triangle and quad mesh to a triangle mesh type by splitting quads. No new vertices are created. NB: This does not attempt to add any additional attributes to the result.  Will need to separately compute vertex normals if desired. @param InMesh   Mesh with a mixture of quads and triangles. @param OutMesh  Triangle Mesh. @param bClockWise how to order the verts in a triangle
- L554 _function_ `template <typename T> void MixedPolyMeshToAOSMesh(const FMixedPolyMesh& MixedPolyMesh, TAOSMesh<T>& DstAOSMesh, bool bClockWise)` (scope `UE::DataflowVolumeUtils`) — Convert MixedPolyMesh to AOS Mesh.  This requires splitting quads to produce triangles.
- L578 _function_ `` (scope `UE::DataflowVolumeUtils::MixedPolyMeshToAOSMesh`)
- L670 _prototype_ `void ConvertMesh(const FAOSMesh& InMesh, FMeshDescription& OutMesh);` (scope `UE::DataflowVolumeUtils`) — Common interface to convert between various triangle-based mesh types. The conversions will maintain geometry and connectivity, but different mesh types support different attribute types and possibly different frequenceies even when the same attribute types exist on both mesh types ( e.g. FMeshDescription has per-wedge data while FVertexDataMesh has per-vertex attributes). @param InMesh   Source Mesh to convert. @param OutMesh  The result of the mesh conversion.  Any data already stored in OutMesh will be lost.
- L685 _prototype_ `void AOSMeshToRawMesh(const FAOSMesh& InMesh, FMeshDescription& OutMesh);` (scope `UE::DataflowVolumeUtils`) — Convert the simplifier-friendly array-of-structs mesh to a struct of arrays FMeshDescription. NB: This copies the AOSVertex normal to the wedge FMeshDescription::Tangentz. But additional FMeshDescription attributes, including tangent/bitangent are given default values. @param InMesh   Source Mesh to convert. @param OutMesh  The result of the mesh conversion.  Any data already stored in OutMesh will be lost.
- L690 _prototype_ `FMatrix CreateMatrixFromTransformAndVoxelSize( const FVector InTranslation, const FVector InRotation, const FVector InScale, const float InVoxelSize);` (scope `UE::DataflowVolumeUtils`) — Create a world-to-index-space transform matrix from transform and voxelSize
- L699 _prototype_ `openvdb::Mat4R ConvertMatrixToVDBMatrix(FMatrix& InMatrix);` (scope `UE::DataflowVolumeUtils`) — Convert a FMatrix to openvdb::Mat4R
- L702 _function_ `template <typename GridType> void GetActiveVoxels(const typename GridType::Ptr& InGridPtr, TArray<FBox>& OutActiveVoxels)` (scope `UE::DataflowVolumeUtils`)
- L704 _typedef_ `using IterT = typename GridType::ValueOnCIter;` (scope `UE::DataflowVolumeUtils::GetActiveVoxels`)
- L736 _function_ `template <typename GridType> void GetActiveVoxels(const typename GridType::Ptr& InGridPtr, const float InIsovalue, TArray<FBox>& OutActiveVoxels, bool bInteriorMaskOnly = false)` (scope `UE::DataflowVolumeUtils`) — Get active voxels of a volume of any type
- L744 _function_ `` (scope `UE::DataflowVolumeUtils::GetActiveVoxels`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeCore/Private/Dataflow/OpenVDB.h` (Private)


#### Free symbols / members of external scopes

- L24 _macro_ `#define M_PI 3.14159265358979323846`
- L25 _macro_ `#define LOCAL_M_PI 1`
- L29 _macro_ `#define M_PI_2 1.57079632679489661923 // pi/2`
- L30 _macro_ `#define LOCAL_M_PI_2 1`
- L33 _macro_ `#define BOOST_ALLOW_DEPRECATED_HEADERS`
