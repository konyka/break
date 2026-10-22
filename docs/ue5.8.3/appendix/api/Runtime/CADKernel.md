# Runtime / CADKernel

- module root: `Source/Runtime/Datasmith/CADKernel/Base`
- headers: 116; symbols: 3937
- symbol kinds: class=120, delegate=2, enum=31, enumerator=233, externvar=8, function=1617, macro=11, member=693, namespace=251, prototype=871, struct=45, typedef=20, variable=35
- PublicDependencyModuleNames: Core, GeometryCore

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Core/Factory.h` (Private)


#### class `UE::CADKernel::TFactory`  
`template<class ElementType> class TFactory`  
_L14-72_
- L16 _private member_ `static const int32 MaxSize = 256;`
- L19 _protected member_ `TDoubleLinkedList<TArray<ElementType>> StackOfEntitySet;`
- L20 _protected member_ `TArray<ElementType*> FreeEntityStack;`
- L22 _protected member_ `int32 AllocatedElementNum = 0;`
- L23 _protected member_ `int32 UsedElementNum = 0;`
- L24 _protected member_ `int32 AvailableElementNum = 0;`
- L28 _private function_ `void FillFreeEntityStack()`
- L43 _public function_ `TFactory()`
- L48 _public function_ `void DeleteEntity(ElementType* Entity)`
- L58 _public function_ `ElementType& New()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Core/Group.h` (Private)


#### enum `UE::CADKernel::EGroupOrigin`  
`enum class EGroupOrigin : uint8`  
_L9-15_
- L11 _public enumerator_ `Unknown`
- L12 _public enumerator_ `CADGroup`
- L13 _public enumerator_ `CADLayer`
- L14 _public enumerator_ `CADColor`

#### class `UE::CADKernel::FGroup`  
`class FGroup : public FEntity`  
_L19-137_
- inherits: `FEntity`
- L24 _protected member_ `EGroupOrigin Origin;`
- L25 _protected member_ `FString GroupName;`
- L26 _protected member_ `TArray<TSharedPtr<FEntity>> Entities;`
- L28 _protected function_ `FGroup() : Origin(EGroupOrigin::Unknown)`
- L33 _protected function_ `FGroup(TArray<TSharedPtr<FEntity>>& InEntities) : Origin(EGroupOrigin::Unknown)`
- L41 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L49 _public function_ `virtual void SpawnIdent(FDatabase& Database) override`
- L59 _public function_ `virtual void ResetMarkersRecursively() const override`
- L66 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L69 _public function_ `virtual EEntity GetEntityType() const override`
- L74 _public prototype_ `void SetName(const FString& Name);`
- L76 _public function_ `const FString& GetName() const`
- L81 _public function_ `void AddEntity(TSharedPtr<FEntity> Entity)`
- L86 _public function_ `void Empty()`
- L91 _public function_ `void RemoveEntity(TSharedPtr<FEntity> Entity)`
- L96 _public function_ `bool Contains(TSharedPtr<FEntity> Entity)`
- L101 _public function_ `EGroupOrigin GetOrigin() const`
- L106 _public function_ `void SetOrigin(EGroupOrigin InOrigin)`
- L111 _public prototype_ `EEntity GetGroupType() const;`
- L113 _public function_ `void GetValidEntities(TArray<TSharedPtr<FEntity>>& OutEntities) const`
- L124 _public function_ `const TArray<TSharedPtr<FEntity>>& GetEntities() const`
- L129 _public function_ `bool IsEmpty()`
- L134 _public prototype_ `void ReplaceEntitiesWithMap(const TMap<TSharedPtr<FEntity>, TSharedPtr<FEntity>>& Map);`
- L136 _public prototype_ `void RemoveNonTopologicalEntities();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)
- L17 _externvar_ `extern const TCHAR* GroupOriginNames[];` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Curves/BezierCurve.h` (Private)


#### class `UE::CADKernel::FBezierCurve`  
`class FBezierCurve : public FCurve`  
_L10-104_
- inherits: `FCurve`
- L15 _protected member_ `bool bIsRational = false;`
- L17 _protected member_ `int32 Degree = 0;`
- L18 _protected member_ `TArray<double> NodalVector;`
- L19 _protected member_ `int32 NumSegments = 0;`
- L21 _protected member_ `TArray<FVector> Poles;`
- L22 _protected member_ `TArray<double> Weights;`
- L24 _protected function_ `FBezierCurve(const TArray<FVector>& InPoles) : Poles`
- L38 _protected prototype_ `FBezierCurve(const FNurbsCurveData& NurbsCurveData);`
- L40 _protected prototype_ `FBezierCurve() = default;`
- L44 _public prototype_ `static bool IsBezier(const FNurbsCurveData& NurbsCurveData);`
- L46 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L59 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L62 _public function_ `virtual ECurve GetCurveType() const override`
- L67 _public function_ `int32 GetDegre() const`
- L72 _public function_ `const TArray<FVector>& GetPoles() const`
- L77 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L78 _public prototype_ `virtual void Offset(const FVector& OffsetDirection) override;`
- L80 _public prototype_ `virtual void EvaluatePoint(double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder = 0) const override;`
- L81 _public function_ `virtual void Evaluate2DPoint(double Coordinate, FCurvePoint2D& OutPoint, int32 DerivativeOrder = 0) const override`
- L101 _public prototype_ `virtual void ExtendTo(const FVector& Point) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Curves/BoundedCurve.h` (Private)


#### class `UE::CADKernel::FBoundedCurve`  
`class FBoundedCurve : public FCurve`  
_L9-72_
- inherits: `FCurve`
- L15 _protected member_ `TSharedPtr<FCurve> Curve;`
- L17 _protected function_ `FBoundedCurve(TSharedRef<FCurve> InCurve, const FLinearBoundary& InBoundary, int8 InDimension) : FCurve(InBoundary, InDimension) , Curve(InCurve)`
- L23 _protected prototype_ `FBoundedCurve() = default;`
- L27 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L33 _public function_ `virtual void SpawnIdent(FDatabase& Database) override`
- L43 _public function_ `virtual void ResetMarkersRecursively() const override`
- L50 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L53 _public function_ `virtual ECurve GetCurveType() const override`
- L58 _public function_ `TSharedRef<const FCurve> GetBaseCurve()`
- L63 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L64 _public prototype_ `virtual void Offset(const FVector& OffsetDirection) override;`
- L66 _public prototype_ `virtual void EvaluatePoint(double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder = 0) const override;`
- L67 _public prototype_ `virtual void Evaluate2DPoint(double Coordinate, FCurvePoint2D& OutPoint, int32 DerivativeOrder = 0) const override;`
- L69 _public prototype_ `virtual void FindNotDerivableCoordinates(const FLinearBoundary& InBoundary, int32 DerivativeOrder, TArray<double>& OutNotDerivableCoordinates) const override;`
- L71 _public prototype_ `virtual TSharedPtr<FCurve> MakeBoundedCurve(const FLinearBoundary& InBoundary) override;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Curves/CompositeCurve.h` (Private)


#### class `UE::CADKernel::FOrientedCurve`  
`class FOrientedCurve : public TOrientedEntity<FCurve>`  
_L11-23_
- inherits: `TOrientedEntity<FCurve>`
- L14 _public function_ `FOrientedCurve(TSharedPtr<FCurve>& InEntity, EOrientation InDirection) : TOrientedEntity(InEntity, InDirection)`
- L19 _public function_ `FOrientedCurve() : TOrientedEntity()`

#### class `UE::CADKernel::FCompositeCurve`  
`class FCompositeCurve : public FCurve`  
_L25-86_
- inherits: `FCurve`
- L30 _protected member_ `TArray<FOrientedCurve> Curves;`
- L31 _protected member_ `TArray<double> Coordinates;`
- L33 _protected prototype_ `FCompositeCurve(const TArray<TSharedPtr<FCurve>>& Curves, bool bDoInversions = false);`
- L35 _protected prototype_ `FCompositeCurve() = default;`
- L39 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L46 _public function_ `virtual void SpawnIdent(FDatabase& Database) override`
- L56 _public function_ `virtual void ResetMarkersRecursively() const override`
- L63 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L66 _public function_ `virtual ECurve GetCurveType() const override`
- L71 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L72 _public prototype_ `virtual void Offset(const FVector& OffsetDirection) override;`
- L74 _public function_ `virtual TSharedPtr<FCurve> GetCurve(int32 Index) const`
- L79 _public prototype_ `virtual void EvaluatePoint(double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder = 0) const override;`
- L80 _public prototype_ `virtual void Evaluate2DPoint(double Coordinate, FCurvePoint2D& OutPoint, int32 DerivativeOrder = 0) const override;`
- L82 _public prototype_ `virtual void FindNotDerivableCoordinates(const FLinearBoundary& InBoundary, int32 DerivativeOrder, TArray<double>& OutNotDerivableCoordinates) const override;`
- L84 _public prototype_ `double LocalToGlobalCoordinate(int32 CurveIndex, double LocalCoordinate) const;`
- L85 _public prototype_ `double GlobalToLocalCoordinate(int32 CurveIndex, double GlobalCoordinate) const;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Curves/EllipseCurve.h` (Private)


#### class `UE::CADKernel::FEllipseCurve`  
`class FEllipseCurve : public FCurve`  
_L11-113_
- inherits: `FCurve`
- L16 _protected member_ `FMatrixH Matrix;`
- L17 _protected member_ `double RadiusU;`
- L18 _protected member_ `double RadiusV;`
- L20 _protected function_ `FEllipseCurve(const FMatrixH& InMatrix, double InRadiusU, double InRadiusV, int8 InDimension = 3) : FCurve(FLinearBoundary(0, PI * 2.), InDimension) , Matrix(InMatrix) , RadiusU(InRadiusU) , RadiusV(InRadiusV)`
- L28 _protected function_ `FEllipseCurve(const FMatrixH& InMatrix, double InRadiusU, double InRadiusV, const FLinearBoundary& InBounds, int8 InDimension = 3) : FCurve(InBounds, InDimension) , Matrix(InMatrix) , RadiusU(InRadiusU) , RadiusV(InRadiusV)`
- L36 _protected prototype_ `FEllipseCurve() = default;`
- L40 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L49 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L52 _public function_ `virtual ECurve GetCurveType() const override`
- L57 _public function_ `const FMatrixH& GetMatrix() const`
- L62 _public function_ `bool IsCircular() const`
- L67 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L68 _public prototype_ `virtual void Offset(const FVector& OffsetDirection) override;`
- L70 _public function_ `virtual void EvaluatePoint(double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder = 0) const override`
- L92 _public function_ `virtual void Evaluate2DPoint(double Coordinate, FCurvePoint2D& OutPoint, int32 DerivativeOrder = 0) const override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Curves/HyperbolaCurve.h` (Private)


#### class `UE::CADKernel::FHyperbolaCurve`  
`class FHyperbolaCurve : public FCurve`  
_L9-101_
- inherits: `FCurve`
- L16 _protected member_ `FMatrixH Matrix;`
- L17 _protected member_ `double SemiMajorAxis;`
- L18 _protected member_ `double SemiImaginaryAxis;`
- L20 _protected function_ `FHyperbolaCurve(const FMatrixH& InMatrix, double InSemiAxis, double InSemiImagAxis, const FLinearBoundary& InBounds, int8 InDimension = 3) : FCurve(InBounds, InDimension) , Matrix(InMatrix) , SemiMajorAxis(InSemiAxis) , SemiImaginaryAxis(InSemiImagAxis)`
- L28 _protected prototype_ `FHyperbolaCurve() = default;`
- L32 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L41 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L44 _public function_ `virtual ECurve GetCurveType() const override`
- L49 _public function_ `FMatrixH& GetMatrix()`
- L54 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L55 _public prototype_ `virtual void Offset(const FVector& OffsetDirection) override;`
- L58 _public function_ `virtual void EvaluatePoint(double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder = 0) const override`
- L80 _public function_ `virtual void Evaluate2DPoint(double Coordinate, FCurvePoint2D& OutPoint, int32 DerivativeOrder = 0) const override`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Curves/NURBSCurve.h` (Private)


#### struct `UE::CADKernel::FNurbsCurveData`  
`struct FNurbsCurveData`  
_L9-19_
- L11 _public member_ `bool bIsRational = false;`
- L12 _public member_ `int32 Dimension = 0;`
- L14 _public member_ `int32 Degree = 0;`
- L15 _public member_ `TArray<double> NodalVector;`
- L17 _public member_ `TArray<double> Weights;`
- L18 _public member_ `TArray<FVector> Poles;`

#### class `UE::CADKernel::FNURBSCurve`  
`class FNURBSCurve : public FCurve`  
_L21-138_
- inherits: `FCurve`
- L27 _protected member_ `int32 Degree;`
- L29 _protected member_ `TArray<double> NodalVector;`
- L30 _protected member_ `TArray<double> Weights;`
- L32 _protected member_ `TArray<FVector> Poles;`
- L34 _protected member_ `bool bIsRational;`
- L39 _protected member_ `TArray<double> HomogeneousPoles;` — Data generated at initialization which are not serialized
- L40 _protected member_ `int32 PoleDimension;`
- L42 _protected prototype_ `FNURBSCurve(int32 InDegree, const TArray<double>& InNodalVector, const TArray<FVector>& InPoles, const TArray<double>& InWeights, int8 InDimension = 3);`
- L43 _protected prototype_ `FNURBSCurve(FNurbsCurveData& NurbsCurveData);`
- L45 _protected prototype_ `FNURBSCurve() = default;`
- L49 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L65 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L68 _public function_ `virtual ECurve GetCurveType() const override`
- L73 _public function_ `int32 GetDegree() const`
- L78 _public function_ `const int32 GetPoleCount() const`
- L83 _public function_ `const TArray<FVector>& GetPoles() const`
- L88 _public function_ `const TArray<double>& GetWeights() const`
- L93 _public function_ `const TArray<double>& GetHPoles() const`
- L98 _public function_ `const TArray<double>& GetNodalVector() const`
- L103 _public function_ `bool IsRational() const`
- L108 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L109 _public prototype_ `virtual void Offset(const FVector& OffsetDirection) override;`
- L111 _public function_ `virtual void EvaluatePoint(double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder = 0) const override`
- L116 _public function_ `virtual void Evaluate2DPoint(double Coordinate, FCurvePoint2D& OutPoint, int32 DerivativeOrder = 0) const override`
- L121 _public function_ `virtual void FindNotDerivableCoordinates(const FLinearBoundary& InBoundary, int32 DerivativeOrder, TArray<double>& OutNotDerivableCoordinates) const override`
- L126 _public prototype_ `virtual void ExtendTo(const FVector& DesiredPosition) override;`
- L128 _public prototype_ `void Invert();`
- L129 _public prototype_ `void SetStartNodalCoordinate(double NewStartBoundary);`
- L136 _private prototype_ `void Finalize();` — Fill homogeneous points and set bounds

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Curves/ParabolaCurve.h` (Private)


#### class `UE::CADKernel::FParabolaCurve`  
`class FParabolaCurve : public FCurve`  
_L9-90_
- inherits: `FCurve`
- L15 _protected member_ `FMatrixH Matrix;`
- L16 _protected member_ `double FocalDistance;`
- L18 _protected function_ `FParabolaCurve(const FMatrixH& InMatrix, double InFocalDistance, const FLinearBoundary& InBounds, int8 InDimension = 3) : FCurve(InBounds, InDimension) , Matrix(InMatrix) , FocalDistance(InFocalDistance)`
- L25 _protected prototype_ `FParabolaCurve() = default;`
- L29 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L37 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L40 _public function_ `virtual ECurve GetCurveType() const override`
- L45 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L46 _public prototype_ `virtual void Offset(const FVector& OffsetDirection) override;`
- L48 _public function_ `virtual void ExtendTo(const FVector& Point) override`
- L53 _public function_ `virtual void EvaluatePoint(double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder = 0) const override`
- L72 _public function_ `virtual void Evaluate2DPoint(double Coordinate, FCurvePoint2D& OutPoint, int32 DerivativeOrder = 0) const override`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Curves/PolylineCurve.h` (Private)


#### class `UE::CADKernel::TPolylineCurve`  
`template<class PointType, class PointCurveType> class TPolylineCurve : public FCurve, public TPolyline<PointType>`  
_L14-142_
- inherits: `FCurve,TPolyline<PointType>`
- L21 _protected member_ `TPolylineApproximator<PointType> Approximator;`
- L23 _protected function_ `TPolylineCurve(const TArray<PointType>& InPoints, const TArray<double>& InCoordinates, int8 InDimension) : FCurve(InDimension) , Approximator(this->Coordinates, this->Points)`
- L33 _protected function_ `TPolylineCurve(const TArray<PointType>& InPoints, int8 InDimension) : FCurve(InDimension) , TPolyline<PointType>(InPoints) , Approximator(this->Coordinates, this->Points)`
- L51 _protected function_ `TPolylineCurve() : Approximator(this->Coordinates, this->Points)`
- L58 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L64 _public function_ `virtual void EvaluateCurvesPoint(double InCoordinate, PointCurveType& OutPoint, int32 InDerivativeOrder = 0) const`
- L69 _public function_ `PointType EvaluatePointAt(double InCoordinate) const`
- L74 _public function_ `virtual void EvaluateCurvesPoints(const TArray<double>& InCoordinates, TArray<PointCurveType>& OutPoints, int32 InDerivativeOrder = 0) const`
- L79 _public function_ `virtual double ComputeSubLength(const FLinearBoundary& InBoundary) const`
- L84 _public function_ `const TArray<PointType>& GetPolylinePoints() const`
- L89 _public function_ `const TArray<double>& GetPolylineParameters() const`
- L94 _public function_ `virtual void FindNotDerivableCoordinates(const FLinearBoundary& InBoundary, int32 DerivativeOrder, TArray<double>& OutNotDerivableCoordinates) const override`
- L110 _public function_ `void SetPoints(const TArray<PointType>& InPoints)`
- L117 _public function_ `template<class PolylineType> TSharedPtr<FEntityGeom> ApplyMatrixImpl(const FMatrixH& InMatrix) const`
- L130 _public function_ `virtual void Offset(const FVector& OffsetDirection) override`
- L138 _public function_ `virtual void ExtendTo(const FVector& DesiredPoint) override`

#### class `UE::CADKernel::FPolylineCurve`  
`class FPolylineCurve : public TPolylineCurve<FVector, FCurvePoint>`  
_L144-182_
- inherits: `TPolylineCurve<FVector,FCurvePoint>`
- L149 _protected function_ `FPolylineCurve(const TArray<FVector>& InPoints, const TArray<double>& InCoordinates) : TPolylineCurve<FVector, FCurvePoint>(InPoints, InCoordinates, 3)`
- L154 _protected function_ `FPolylineCurve(const TArray<FVector>& InPoints) : TPolylineCurve<FVector, FCurvePoint>(InPoints, 3)`
- L159 _protected prototype_ `FPolylineCurve() = default;`
- L163 _public function_ `virtual ECurve GetCurveType() const override`
- L168 _public function_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override`
- L173 _public function_ `virtual FVector EvaluatePoint(double InCoordinate) const override`
- L179 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity& Info) const override;`

#### class `UE::CADKernel::FPolyline2DCurve`  
`class FPolyline2DCurve : public TPolylineCurve<FVector2d, FCurvePoint2D>`  
_L184-232_
- inherits: `TPolylineCurve<FVector2d,FCurvePoint2D>`
- L189 _protected function_ `FPolyline2DCurve(const TArray<FVector2d>& InPoints, const TArray<double>& InCoordinates) : TPolylineCurve<FVector2d, FCurvePoint2D>(InPoints, InCoordinates, 2)`
- L194 _protected function_ `FPolyline2DCurve(const TArray<FVector2d>& InPoints) : TPolylineCurve<FVector2d, FCurvePoint2D>(InPoints, 2)`
- L199 _protected prototype_ `FPolyline2DCurve() = default;`
- L203 _public function_ `virtual ECurve GetCurveType() const override`
- L208 _public function_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override`
- L213 _public function_ `virtual void Evaluate2DPoint(double InCoordinate, FCurvePoint2D& OutPoint, int32 InDerivativeOrder = 0) const override`
- L218 _public function_ `virtual FVector2d Evaluate2DPoint(double InCoordinate) const override`
- L223 _public function_ `virtual void Evaluate2DPoints(const TArray<double>& InCoordinates, TArray<FCurvePoint2D>& OutPoints, int32 InDerivativeOrder = 0) const override`
- L229 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity& Info) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Curves/SegmentCurve.h` (Private)


#### class `UE::CADKernel::FSegmentCurve`  
`class FSegmentCurve : public FCurve`  
_L10-118_
- inherits: `FCurve`
- L15 _protected member_ `FVector StartPoint;`
- L16 _protected member_ `FVector EndPoint;`
- L18 _protected function_ `FSegmentCurve(const FVector& InStartPoint, const FVector& InEndPoint, int8 InDimension = 3) : FCurve(InDimension) , StartPoint(InStartPoint) , EndPoint(InEndPoint)`
- L25 _protected function_ `FSegmentCurve(const FVector2d& InStartPoint, const FVector2d& InEndPoint, int8 InDimension = 3) : FCurve(InDimension) , StartPoint(InStartPoint, 0.) , EndPoint(InEndPoint, 0.)`
- L32 _protected prototype_ `FSegmentCurve() = default;`
- L36 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L44 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L47 _public function_ `virtual ECurve GetCurveType() const override`
- L52 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L53 _public prototype_ `virtual void Offset(const FVector& OffsetDirection) override;`
- L55 _public function_ `virtual void EvaluatePoint(double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder = 0) const override`
- L61 _public function_ `virtual void Evaluate2DPoint(double Coordinate, FCurvePoint2D& OutPoint, int32 DerivativeOrder = 0) const override`
- L67 _public function_ `const FVector& GetStartPoint() const`
- L72 _public function_ `const FVector& GetEndPoint() const`
- L77 _public function_ `virtual void ExtendTo(const FVector& DesiredPosition) override`
- L92 _private function_ `void GetTangent(FVector& Tangent) const`
- L97 _private function_ `void GetTangent(FVector2d& Tangent) const`
- L103 _private function_ `template <typename CurvePointType, typename PointType> void Evaluate(double Coordinate, CurvePointType& OutPoint, int32 DerivativeOrder) const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Curves/SplineCurve.h` (Private)


#### class `UE::CADKernel::FSplineCurve`  
`class FSplineCurve : public FCurve`  
_L15-113_
- inherits: `FCurve`
- L21 _protected member_ `FInterpCurveFVector Position;`
- L30 _protected member_ `FInterpCurveDouble ReparamTable;` — Input: distance along curve, output: parameter that puts you there.
- L36 _protected member_ `bool bClosedLoop;` — Whether the spline is to be considered as a closed loop. Use SetClosedLoop() to set this property, and IsClosedLoop() to read it.
- L41 _protected function_ `FSplineCurve(const TArray<FVector>& InPoles)`
- L46 _protected function_ `FSplineCurve(const TArray<FVector>& InPoles, const TArray<FVector>& InTangents)`
- L51 _protected function_ `FSplineCurve(const TArray<FVector>& InPoles, const TArray<FVector>& InArriveTangents, const TArray<FVector>& InLeaveTangents)`
- L56 _protected prototype_ `FSplineCurve() = default;`
- L59 _protected prototype_ `FVector GetLocationAtSplineInputKey(double InCoordinate) const;` — Get location along spline at the provided input coordinate value
- L62 _protected prototype_ `FVector GetTangentAtSplineInputKey(double InCoordinate) const;` — Get tangent along spline at the provided input coordinate value
- L65 _protected prototype_ `FVector GetDirectionAtSplineInputKey(double InCoordinate) const;` — Get unit direction (normalized tangent) along spline at the provided input coordinate value
- L69 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L78 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L81 _public function_ `virtual ECurve GetCurveType() const override`
- L86 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L87 _public prototype_ `virtual void Offset(const FVector& OffsetDirection) override;`
- L89 _public prototype_ `virtual void EvaluatePoint(double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder = 0) const override;`
- L91 _public prototype_ `virtual void ExtendTo(const FVector& Point) override;`
- L99 _public prototype_ `void UpdateSpline(bool bClosedLoop = false, bool bStationaryEndpoints = false, int32 ReparamStepsPerSegment = 10);` — Update the spline's internal data according to the passed-in params @param	bClosedLoop				Whether the spline is to be considered as a closed loop. @param	bStationaryEndpoints	Whether the endpoints of the spline are considered stationary when traversing the spline at non-constant velocity.  Essentially this sets the endpoints' tangents to zero vectors. @param	ReparamStepsPerSegment	Number of steps per spline segment to place in the re parameterization table
- L102 _public prototype_ `double GetSegmentLength(const int32 Index, const double Param, bool bClosedLoop = false) const;` — Returns the length of the specified spline segment up to the parametric value given
- L105 _public prototype_ `double GetSplineLength() const;` — Returns total length along this spline
- L108 _public prototype_ `void SetSplinePoints(const TArray<FVector>& InPoints);` — Sets the spline to an array of points
- L109 _public prototype_ `void SetSplinePoints(const TArray<FVector>& InPoints, const TArray<FVector>& InTangents);`
- L110 _public prototype_ `void SetSplinePoints(const TArray<FVector>& InPoints, const TArray<FVector>& InArriveTangents, const TArray<FVector>& InLeaveTangents);`
- L112 _public function_ `const FInterpCurveFVector& GetSplinePointsPosition() const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Sampler/SamplerAbstract.h` (Private)


#### class `UE::CADKernel::TCurveSamplerAbstract`  
`template<typename PolylineType, typename PointType> class TCurveSamplerAbstract`  
_L19-509_
- L51 _public function_ `TCurveSamplerAbstract(const FLinearBoundary& InBoundary, PolylineType& OutPolyline, double InDesiredChordError) : Boundary(InBoundary) , Sampling(OutPolyline) , TmpPolylineCoordinates(CandidatePoints.GetCoordinates()) , SamplingCoordinates(Sampling.GetCoordinates()) , EndStudySegment(OutPolyline) , DesiredChordError(InDesiredChordError)`
- L61 _public prototype_ `virtual ~TCurveSamplerAbstract() = default;`
- L66 _public function_ `virtual void Sample()` — Method to call to generate the curve sampling
- L75 _protected prototype_ `virtual void EvaluatesNewCandidatePoints() = 0;` — Evaluate the new candidate points corresponding to the NextCoordinates
- L81 _protected prototype_ `virtual int32 CheckSamplingError(int32 FirstIndex, int32 EndIndex) = 0;` — This function check the sub-polyline to verify if its respect the attended quality e.g. Curve sampler implementation of this method check the chord error
- L86 _protected function_ `virtual void GetNotDerivableCoordinates(TArray<double>& OutNotDerivableCoordinates)` — OutNotDerivableCoordinates must not include the boundaries of the curve. They are added after
- L93 _protected function_ `virtual void SamplingInitializing()` — Method to call to generate the curve sampling
- L143 _protected function_ `void RunSampling()` — Method to call to generate the curve sampling
- L251 _protected function_ `bool AddIntermediateCoordinates(double UMin, double UMax, int32 PointNum)` — Adds coordinates of the next candidate points in NextCoordinates array
- L276 _protected function_ `void CompletesPolyline(int32 NeededPointNumber, int32 IntermediateIndex)` — Completes Polyline and add new candidate coordinates for the next step. @param NeededPointCount estimated number of needed points to respect the sampling error. NeededPointNumber = 1: only the last point is needed NeededPointNumber = 2: the intermediate point and last point is needed NeededPointNumber > 2: the both points are not enought. Candidate points are added on each side of the intermediate point @param IntermediateIndex
- L315 _protected function_ `int32 GetFirstNeighbor(int32 NeighborIndex, const double StartCoordinate, const PolylineType& Points, const int32 Increment, double& NeighborCoordinate)`
- L326 _protected function_ `int32 CountOfNeededPointsToRespectChordError(const PointType& PointA, const PointType& PointB, double ChordError)`
- L334 _protected function_ `int32 CheckTangentError(const PointType& APoint, double ACoordinate, const PointType& BPoint, double BCoordinate, int32 FirstIndex, int32 EndIndex, int32 InStartSamplingSegmentIndex)`
- L381 _protected member_ `FLinearBoundary Boundary;`
- L384 _protected member_ `PolylineType& Sampling;` — Final sampling of the curve. This polyline will be completed at each iteration
- L386 _protected member_ `PolylineType CandidatePoints;`
- L388 _protected member_ `const TArray<double>& TmpPolylineCoordinates;`
- L389 _protected member_ `const TArray<double>& SamplingCoordinates;`
- L392 _protected member_ `TArray<char> IsOptimalSegments;` — Array to indicated if the segment at Index defined by Sampling[Index] and Sampling[Index + 1] respects the desired criteria
- L397 _protected member_ `int32 StartSamplingSegmentIndex;` — StartSamplingPointIndex and EndSamplingPointIndex defined the extremity of the segment that is currently enriched with candidate points if needed
- L402 _protected member_ `int32 EndSamplingSegmentIndex;` — EndSamplingPointIndex changes (+1) each time a candidate point is inserted in the sampling
- L409 _protected member_ `TSamplingPoint EndStudySegment;` — The study segment starting at StartSamplingPoint and ending at EndStudySegment that is either a point of Sampling or a point of CandidatePoints The sampling error is compute between the intermediate candidate points (candidate points localized between StartSamplingPoint and EndStudySegment) and this segment. FirstCandidateIndex and (LastCandidateIndex - 1) are the index of the first and the last intermediate points
- L412 _protected member_ `TArray<double> NextCoordinates;` — Coordinates of the new candidate points for the next iteration
- L414 _protected member_ `double DesiredChordError;`
- L418 _public member_ `int32 CurveIndex = 0;`
- L419 _public member_ `int32 CurveToDisplay = 1;`
- L421 _public function_ `void DisplaySampling(bool bDisplay, int32 Step)`
- L459 _public function_ `void CheckResult()`

#### struct `UE::CADKernel::TCurveSamplerAbstract::TSamplingPoint`  
`struct TSamplingPoint`  
_L23-49_
- L25 _public member_ `const PolylineType* Sampling;`
- L26 _public member_ `const PolylineType* Polyline;`
- L27 _public member_ `int32 Index;`
- L29 _public function_ `TSamplingPoint(const PolylineType& InSampling) : Sampling(&InSampling)`
- L34 _public function_ `void Set(const PolylineType& InPolyline, int32 InIndex)`
- L40 _public function_ `constexpr bool IsCandidatePoint()`
- L45 _public function_ `constexpr bool IsSamplingPoint()`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Sampler/SamplerOnChord.h` (Private)


#### class `UE::CADKernel::TSamplerBasedOnChordError`  
`template<class PointType> class TSamplerBasedOnChordError : public TCurveSamplerAbstract<TPolyline<PointType>, PointType>`  
_L21-127_
- inherits: `TCurveSamplerAbstract<TPolyline<PointType>,PointType>`
- L24 _public function_ `TSamplerBasedOnChordError(const FLinearBoundary& InBoundary, double InMaxAllowedError, TPolyline<PointType>& OutPolyline) : TCurveSamplerAbstract<TPolyline<PointType>, PointType>(InBoundary, OutPolyline, InMaxAllowedError)`
- L49 _protected function_ `virtual int32 CheckSamplingError(int32 FirstIndex, int32 EndIndex) override` — Check the chord error of the AB segment for each point of TmpPoints between FirstIndex and EndIndex If the MaxChord is biggest to the DesiredChordError, an estimation of the needed point number to insert is done. This estimation is bases on the approximation of local curve radius (R) : R = square(L) / 8Sag L2 = sqrt(square(L1) * S2 / S1) S2 = S1 * square(L2 / L1) Sag & Angle criterion.pdf https://docs.google.com/presentation/d/1bUnrRFWCW3sDn9ngb9ftfQS-2JxNJaUZlh783hZMMEw/edit?usp=sharing @return the number of point to add after PointA to PointB to respect the chord error. if PointNum = 0, PointB is not necessary if PointNum = 1, PointB has to be add to respect the chord error and the segment AB is respecting the chord error if PointNum = 2, Point at FirstIndex and PointB have to be add to respect the chord error and both segments are respecting the chord error In this case, a complementary check is done at each extremity to verify that the curve do not have a fast modification if PointNum > 2, Point at FirstIndex and PointB have to be add but at least (PointNum - 2) points have to be added in both segments to respect the chord error
- L125 _protected member_ `bool bDisplay = true;`

#### class `UE::CADKernel::FCurveSamplerOnChord`  
`class FCurveSamplerOnChord : public TSamplerBasedOnChordError<FVector>`  
_L132-155_
- inherits: `TSamplerBasedOnChordError<FVector>`
- desc: Sampler of curve based on parametrization and chord error control
- L135 _public function_ `FCurveSamplerOnChord(const FCurve& InCurve, const FLinearBoundary& InBoundary, double InMaxAllowedError, FPolyline3D& OutPolyline) : TSamplerBasedOnChordError<FVector>(InBoundary, InMaxAllowedError, OutPolyline) , Curve(InCurve)`
- L143 _protected member_ `const FCurve& Curve;`
- L145 _protected function_ `virtual void EvaluatesNewCandidatePoints() override`
- L150 _protected function_ `virtual void GetNotDerivableCoordinates(TArray<double>& OutNotDerivableCoordinates) override`

#### class `UE::CADKernel::FCurve2DSamplerOnChord`  
`class FCurve2DSamplerOnChord : public TSamplerBasedOnChordError<FVector2d>`  
_L157-180_
- inherits: `TSamplerBasedOnChordError<FVector2d>`
- L160 _public function_ `FCurve2DSamplerOnChord(const FCurve& InCurve, const FLinearBoundary& InBoundary, double InMaxAllowedError, FPolyline2D& OutPolyline) : TSamplerBasedOnChordError<FVector2d>(InBoundary, InMaxAllowedError, OutPolyline) , Curve(InCurve)`
- L168 _protected member_ `const FCurve& Curve;`
- L170 _protected function_ `virtual void EvaluatesNewCandidatePoints() override`
- L175 _protected function_ `virtual void GetNotDerivableCoordinates(TArray<double>& OutNotDerivableCoordinates) override`

#### class `UE::CADKernel::FIsoCurve3DSamplerOnChord`  
`class FIsoCurve3DSamplerOnChord : public TSamplerBasedOnChordError<FVector>`  
_L182-253_
- inherits: `TSamplerBasedOnChordError<FVector>`
- L185 _public function_ `FIsoCurve3DSamplerOnChord(const FSurface& InSurface, double InMaxAllowedError, FPolyline3D& OutPolyline) : TSamplerBasedOnChordError<FVector>(FLinearBoundary(), InMaxAllowedError, OutPolyline) , Surface(InSurface)`
- L191 _public function_ `void Set(EIso InIsoType, double InIsoCoordinate, const FLinearBoundary& CurveBounds)`
- L201 _protected member_ `const FSurface& Surface;`
- L202 _protected member_ `FCoordinateGrid NotDerivableCoordinates;`
- L203 _protected member_ `bool bNotDerivableFound = false;`
- L205 _protected member_ `mutable TArray<double> IsoCoordinate;`
- L206 _protected member_ `EIso IsoType;`
- L208 _protected function_ `virtual void GetNotDerivableCoordinates(TArray<double>& OutNotDerivableCoordinates) override`
- L222 _protected function_ `virtual void EvaluatesNewCandidatePoints() override`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace CADKernel` (scope `UE`)
- L225 _function_ `` (scope `UE::CADKernel::FIsoCurve3DSamplerOnChord::EvaluatesNewCandidatePoints`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Sampler/SamplerOnParam.h` (Private)


#### class `UE::CADKernel::TSamplerBasedOnParametrizationAndChordError`  
`template<typename PolylineType, typename PointType> class TSamplerBasedOnParametrizationAndChordError : public TCurveSamplerAbstract<PolylineType, PointType>`  
_L21-128_
- inherits: `TCurveSamplerAbstract<PolylineType,PointType>`
- L24 _public function_ `TSamplerBasedOnParametrizationAndChordError(const FLinearBoundary& InBoundary, double InMaxChordError, double InMaxParameterizationError, PolylineType& OutPolyline) : TCurveSamplerAbstract<PolylineType, PointType>(InBoundary, OutPolyline, InMaxChordError) , DesiredParameterizationError(InMaxParameterizationError)`
- L32 _protected member_ `double DesiredParameterizationError;`
- L59 _protected function_ `virtual int32 CheckSamplingError(int32 FirstIndex, int32 EndIndex) override`

#### class `UE::CADKernel::FSurfacicCurveSamplerOnParam`  
`class FSurfacicCurveSamplerOnParam : public TSamplerBasedOnParametrizationAndChordError<FSurfacicPolyline, FVector>`  
_L133-179_
- inherits: `TSamplerBasedOnParametrizationAndChordError<FSurfacicPolyline,FVector>`
- desc: Sampler of surfacic curve based on parametrization and chord error control
- L136 _public function_ `FSurfacicCurveSamplerOnParam(const FRestrictionCurve& InCurve, const FLinearBoundary& InBoundary, double InMaxSagError, double InMaxParameterizationError, FSurfacicPolyline& OutPolyline) : TSamplerBasedOnParametrizationAndChordError<FSurfacicPolyline, FVector>(InBoundary, InMaxSagError, InMaxParameterizationError, OutPolyline) , Surface(*InCurve.GetCarrierSurface()) , Curve(*InCurve.Get2DCurve())`
- L143 _public function_ `FSurfacicCurveSamplerOnParam(const FSurface& InSurface, const FCurve& InCurve, const FLinearBoundary& InBoundary, double InMaxSagError, double InMaxParameterizationError, FSurfacicPolyline& OutPolyline) : TSamplerBasedOnParametrizationAndChordError<FSurfacicPolyline, FVector>(InBoundary, InMaxSagError, InMaxParameterizationError, OutPolyline) , Surface(InSurface) , Curve(InCurve)`
- L152 _protected member_ `const FSurface& Surface;`
- L153 _protected member_ `const FCurve& Curve;`
- L154 _protected member_ `double MaxParameterizationError;`
- L156 _protected function_ `virtual void EvaluatesNewCandidatePoints() override`
- L174 _protected function_ `virtual void GetNotDerivableCoordinates(TArray<double>& OutNotDerivableCoordinates) override`

#### class `UE::CADKernel::FCurveSamplerOnParam`  
`class FCurveSamplerOnParam : public TSamplerBasedOnParametrizationAndChordError<FPolyline3D, FVector>`  
_L184-207_
- inherits: `TSamplerBasedOnParametrizationAndChordError<FPolyline3D,FVector>`
- desc: Sampler of curve based on parametrization and chord error control
- L187 _public function_ `FCurveSamplerOnParam(const FCurve& InCurve, const FLinearBoundary& InBoundary, double InMaxSagError, double InMaxParameterizationError, FPolyline3D& OutPolyline) : TSamplerBasedOnParametrizationAndChordError<FPolyline3D, FVector>(InBoundary, InMaxSagError, InMaxParameterizationError, OutPolyline) , Curve(InCurve)`
- L195 _protected member_ `const FCurve& Curve;`
- L196 _protected member_ `double MaxParameterizationError;`
- L198 _protected function_ `virtual void EvaluatesNewCandidatePoints() override`
- L203 _protected function_ `virtual void GetNotDerivableCoordinates(TArray<double>& OutNotDerivableCoordinates) override`

#### class `UE::CADKernel::FSurfaceSamplerOnParam`  
`class FSurfaceSamplerOnParam : public TSamplerBasedOnParametrizationAndChordError<FPolyline3D, FVector>`  
_L212-386_
- inherits: `TSamplerBasedOnParametrizationAndChordError<FPolyline3D,FVector>`
- desc: Sampler of surface based on parametrization and chord error control
- L216 _public function_ `FSurfaceSamplerOnParam(const FSurface& InSurface, const FSurfacicBoundary& InBoundary, double InMaxSagError, double InMaxParameterizationError, FPolyline3D& TemporaryPolyline, FCoordinateGrid& OutSampling) : TSamplerBasedOnParametrizationAndChordError<FPolyline3D, FVector>(FLinearBoundary(), InMaxSagError, InMaxParameterizationError, TemporaryPolyline) , Surface(InSurface) , SurfaceBoundary(InBoundary) , SurfaceSampling(OutSampling)`
- L224 _public function_ `void Set(EIso InIsoType, double InIsoCoordinate, const FLinearBoundary& CurveBounds)`
- L232 _public function_ `virtual void Sample() override`
- L238 _public function_ `void Sample(EIso InIsoType)`
- L288 _public function_ `virtual void SamplingInitializing() override`
- L338 _protected member_ `const FSurface& Surface;`
- L339 _protected member_ `const FSurfacicBoundary& SurfaceBoundary;`
- L341 _protected member_ `FCoordinateGrid& SurfaceSampling;`
- L343 _protected member_ `FCoordinateGrid NotDerivableCoordinates;`
- L345 _protected member_ `bool bNotDerivableFound = false;`
- L347 _protected member_ `TArray<double> IsoCoordinate;`
- L348 _protected member_ `EIso IsoType;`
- L350 _protected function_ `virtual void GetNotDerivableCoordinates(TArray<double>& OutNotDerivableCoordinates) override`
- L364 _protected function_ `virtual void EvaluatesNewCandidatePoints() override`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Sampling/SurfacicSampling.h` (Private)


#### struct `UE::CADKernel::FSurfacicSampling`  
`struct FSurfacicSampling`  
_L13-64_
- L15 _public member_ `bool bWithNormals = false;`
- L16 _public member_ `TArray<FVector2d> Points2D;`
- L17 _public member_ `TArray<FVector> Points3D;`
- L18 _public member_ `TArray<FVector3f> Normals;`
- L20 _public function_ `int32 Count()`
- L25 _public function_ `void SetNum(int32 Number)`
- L35 _public function_ `void Reserve(int32 Number)`
- L45 _public function_ `void NormalizeNormals()`
- L53 _public function_ `void Set2DCoordinates(const FCoordinateGrid& Coordinates)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/BezierSurface.h` (Private)


#### class `UE::CADKernel::FBezierSurface`  
`class FBezierSurface : public FSurface`  
_L10-79_
- inherits: `FSurface`
- L16 _protected member_ `int32 UDegre;`
- L17 _protected member_ `int32 VDegre;`
- L19 _protected member_ `int32 UPoleNum;`
- L20 _protected member_ `int32 VPoleNum;`
- L22 _protected member_ `TArray<FVector> Poles;`
- L24 _protected function_ `FBezierSurface(const double InToleranceGeometric, int32 InUDegre, int32 InVDegre, const TArray<FVector>& InPoles) : FSurface(InToleranceGeometric) , UDegre(InUDegre) , VDegre(InVDegre) , UPoleNum(InUDegre + 1) , VPoleNum(InVDegre + 1) , Poles(InPoles)`
- L36 _protected prototype_ `FBezierSurface() = default;`
- L40 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L50 _public function_ `ESurface GetSurfaceType() const`
- L55 _public function_ `int32 GetUDegree() const`
- L60 _public function_ `int32 GetVDegree() const`
- L65 _public function_ `virtual const TArray<FVector>& GetPoles() const`
- L70 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L72 _public prototype_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override;`
- L74 _public prototype_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates) override;`
- L77 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/CompositeSurface.h` (Private)


#### class `UE::CADKernel::FCompositeSurface`  
`class FCompositeSurface : public FSurface`  
_L10-87_
- inherits: `FSurface`
- L19 _protected member_ `TArray<double> GlobalCoordinates[2];` — U & V Coordinates of the composite surface's parametric space at each change of elementary surface
- L24 _protected member_ `TArray<TSharedPtr<FSurface>> Surfaces;` — Elementary surfaces
- L29 _protected member_ `TArray<FSurfacicBoundary> NativeUVBoundaries;` — Native UV Loops of each surface composing the composite surface
- L31 _protected prototype_ `FCompositeSurface(const double InToleranceGeometric, int32 USurfaceNum, int32 VSurfaceNum, const TArray<double>& UCoordinates, const TArray<double>& VCoordinates, const TArray<TSharedPtr<FSurface>>& Surfaces);`
- L33 _protected prototype_ `FCompositeSurface() = default;`
- L37 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L46 _public function_ `virtual void SpawnIdent(FDatabase& Database) override`
- L56 _public function_ `virtual void ResetMarkersRecursively() const override`
- L62 _public function_ `ESurface GetSurfaceType() const`
- L68 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L71 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L73 _public function_ `int32 GetSurfNum(EIso Iso) const`
- L78 _public prototype_ `virtual void InitBoundary() override;`
- L80 _public prototype_ `virtual void LinesNotDerivables(const FSurfacicBoundary& Bounds, int32 InDerivativeOrder, FCoordinateGrid& OutNotDerivableCoordinates) const override;`
- L82 _public prototype_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override;`
- L84 _public prototype_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates) override;`
- L86 _public prototype_ `double LocalToGlobalCoordinate(int32 SurfaceIndex, double CoordinateU, EIso Iso) const;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/ConeSurface.h` (Private)


#### class `UE::CADKernel::FConeSurface`  
`class FConeSurface : public FSurface`  
_L8-116_
- inherits: `FSurface`
- L13 _protected member_ `FMatrixH Matrix;`
- L14 _protected member_ `double StartRadius;`
- L15 _protected member_ `double ConeAngle;`
- L27 _protected function_ `FConeSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, double InStartRadius, double InConeAngle, double InStartRuleLength = -HUGE_VALUE, double InEndRuleLength = HUGE_VALUE, double InStartAngle = 0.0, double InEndAngle = DOUBLE_TWO_PI) : FConeSurface(InToleranceGeometric, InMatrix, InStartRadius, InConeAngle, FSurfacicBoundary(InStartAngle, InEndAngle, InStartRuleLength, InEndRuleLength))` — A Cone surface is defined by a point on the axis of the cone, the direction of the axis of the cone, the radius of the cone at the axis point and the cone semi-angle. The local coordinate system is defined with the origin at the axis point and the Z axis in the axis direction, The equation of the surface in this system is x2 + y2 – (StartRadius + z*tan(ConeAngle) )2 = 0 where ConeAngle is the cone semi-angle and StartRadius is the given cone radius. The cone is placed at its final position and orientation by the Matrix
- L48 _protected function_ `FConeSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, double InStartRadius, double InConeAngle, const FSurfacicBoundary& InBoundary) : FSurface(InToleranceGeometric, InBoundary) , Matrix(InMatrix) , StartRadius(InStartRadius) , ConeAngle(InConeAngle)` — A Cone surface is defined by a point on the axis of the cone, the direction of the axis of the cone, the radius of the cone at the axis point and the cone semi-angle. The local coordinate system is defined with the origin at the axis point and the Z axis in the axis direction, The equation of the surface in this system is x2 + y2 – (StartRadius + z*tan(ConeAngle) )2 = 0 where ConeAngle is the cone semi-angle and StartRadius is the given cone radius. The cone is placed at its final position and orientation by the Matrix The bounds of the cone are defined as follow: Bounds[EIso::IsoU].Min = StartRuleLength; Bounds[EIso::IsoU].Max = EndRuleLength; Bounds[EIso::IsoV].Min = StartAngle; Bounds[EIso::IsoV].Max = EndAngle;
- L57 _protected prototype_ `FConeSurface() = default;`
- L59 _protected function_ `void ComputeMinToleranceIso()`
- L83 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L92 _public function_ `ESurface GetSurfaceType() const`
- L98 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L101 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L103 _public prototype_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override;`
- L104 _public prototype_ `virtual void EvaluatePointGrid(const FCoordinateGrid& Coordinates, FSurfacicSampling& OutPoints, bool bComputeNormals = false) const override;`
- L106 _public function_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates) override`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/CoonsSurface.h` (Private)


#### class `UE::CADKernel::FCoonsSurface`  
`class FCoonsSurface : public FSurface`  
_L12-51_
- inherits: `FSurface`
- L17 _protected member_ `TSharedPtr<FCurve> Curves[4];`
- L18 _protected member_ `TArray<FVector> Corners;`
- L20 _protected prototype_ `FCoonsSurface(const double InToleranceGeometric, TSharedPtr<FCurve> InCurve1, TSharedPtr<FCurve> InCurve2, TSharedPtr<FCurve> InCurve3, TSharedPtr<FCurve> InCurve4);`
- L21 _protected prototype_ `FCoonsSurface(const double InToleranceGeometric, TSharedPtr<FCurve> InCurves[4]);`
- L22 _protected prototype_ `FCoonsSurface() = default;`
- L26 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L38 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L41 _public function_ `virtual ESurface GetSurfaceType() const override`
- L46 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L48 _public prototype_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override;`
- L50 _public prototype_ `virtual void LinesNotDerivables(const FSurfacicBoundary& Bounds, int32 InDerivativeOrder, FCoordinateGrid& OutNotDerivableCoordinates) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/CylinderSurface.h` (Private)


#### class `UE::CADKernel::FCylinderSurface`  
`class FCylinderSurface : public FSurface`  
_L10-85_
- inherits: `FSurface`
- L15 _protected member_ `FMatrixH Matrix;`
- L16 _protected member_ `double Radius;`
- L30 _protected prototype_ `FCylinderSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, double InRadius, double InStartLength = -HUGE_VALUE, double InEndLength = HUGE_VALUE, double InStartAngle = 0.0, double InEndAngle = DOUBLE_TWO_PI);` — The Cylinder surface is a right circular cylinder surface starting at the axis origin and with z axis as the axis direction. It is defined by its Radius and its bounds (StartAngle, EndAngle, StartLength, EndLength) The surface is placed at its final position and orientation by the Matrix The bounds of the cylinder are defined as follow: Bounds[EIso::IsoU].Min = StartAngle; Bounds[EIso::IsoU].Max = EndAngle; Bounds[EIso::IsoV].Min = StartLength; Bounds[EIso::IsoV].Max = EndLength;
- L31 _protected prototype_ `FCylinderSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, const double InRadius, const FSurfacicBoundary& Boundary);`
- L33 _protected prototype_ `FCylinderSurface() = default;`
- L35 _protected function_ `void ComputeMinToleranceIso()`
- L53 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L60 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L63 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L66 _public function_ `ESurface GetSurfaceType() const`
- L71 _public prototype_ `virtual void InitBoundary() override;`
- L73 _public prototype_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override;`
- L75 _public function_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates) override`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/NURBSSurface.h` (Private)


#### class `UE::CADKernel::FNURBSSurface`  
`class FNURBSSurface : public FSurface`  
_L10-255_
- inherits: `FSurface`
- L15 _protected member_ `int32 PoleUCount;`
- L16 _protected member_ `int32 PoleVCount;`
- L18 _protected member_ `int32 UDegree;`
- L19 _protected member_ `int32 VDegree;`
- L21 _protected member_ `TArray<double> UNodalVector;`
- L22 _protected member_ `TArray<double> VNodalVector;`
- L24 _protected member_ `TArray<double> Weights;`
- L26 _protected member_ `TArray<FVector> Poles;`
- L28 _protected member_ `bool bIsRational;`
- L33 _protected member_ `TArray<double> HomogeneousPoles;` — Data generated at initialization which are not serialized
- L40 _protected function_ `FNURBSSurface(const double InToleranceGeometric, int32 InPoleUCount, int32 InPoleVCount, int32 InDegreU, int32 InDegreV, const TArray<double>& InNodalVectorU, const TArray<double>& InNodalVectorV, const TArray<FVector>& InPoles) : FSurface(InToleranceGeometric) , PoleUCount(InPoleUCount) , PoleVCount(InPoleVCount) , UDegree(InDegreU) , VDegree(InDegreV) , UNodalVector(InNodalVectorU) , VNodalVector(InNodalVectorV) , Poles(InPoles) , bIsRational(false)` — Build a Non uniform B-Spline surface @param NodalVectorU Its size is the number of poles in U + the surface degree in U + 1 (PoleUNum + UDegre + 1) @param NodalVectorV Its size is the number of poles in V + the surface degree in V + 1 (PoleVNum + VDegre + 1)
- L80 _protected function_ `FNURBSSurface(const double InToleranceGeometric, FNurbsSurfaceData NurbsData) : FSurface(InToleranceGeometric) , PoleUCount(NurbsData.PoleUCount) , PoleVCount(NurbsData.PoleVCount) , UDegree(NurbsData.UDegree) , VDegree(NurbsData.VDegree) , UNodalVector(NurbsData.UNodalVector) , VNodalVector(NurbsData.VNodalVector) , Weights(NurbsData.Weights) , Poles(NurbsData.Poles) , bIsRational(true)` — Build a Non uniform B-Spline surface @param NodalVectorU Its size is the number of poles in U + the surface degree in U + 1 (PoleUNum + UDegre + 1) @param NodalVectorV Its size is the number of poles in V + the surface degree in V + 1 (PoleVNum + VDegre + 1)
- L101 _protected function_ `FNURBSSurface(const double InToleranceGeometric, FNurbsSurfaceHomogeneousData NurbsData) : FSurface(InToleranceGeometric)` — Build a Non uniform B-Spline surface @param NodalVectorU Its size is the number of poles in U + the surface degree in U + 1 (PoleUNum + UDegre + 1) @param NodalVectorV Its size is the number of poles in V + the surface degree in V + 1 (PoleVNum + VDegre + 1)
- L107 _protected prototype_ `FNURBSSurface() = default;`
- L112 _public function_ `virtual void ValidateUVPoints(TArray<FVector2d>& UVPoints) const`
- L148 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L167 _public function_ `ESurface GetSurfaceType() const`
- L173 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L176 _public function_ `constexpr const int32 GetDegree(EIso Iso) const`
- L188 _public function_ `constexpr const int32 GetPoleCount(EIso Iso) const`
- L200 _public function_ `const TArray<FVector>& GetPoles() const`
- L205 _public function_ `const TArray<double>& GetWeights() const`
- L210 _public function_ `const TArray<double>& GetHPoles() const`
- L215 _public function_ `constexpr const TArray<double>& GetNodalVector(EIso Iso) const`
- L227 _public function_ `bool IsRational() const`
- L233 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L235 _public function_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override`
- L240 _public function_ `void EvaluatePointGrid(const FCoordinateGrid& InSurfacicCoordinates, FSurfacicSampling& OutPoints, bool bComputeNormals) const override`
- L245 _public function_ `virtual void LinesNotDerivables(const FSurfacicBoundary& InBoundary, int32 InDerivativeOrder, FCoordinateGrid& OutNotDerivableCoordinates) const override`
- L250 _public prototype_ `void ComputeMinToleranceIso();`
- L253 _private prototype_ `void Finalize();`
- L254 _private prototype_ `void FillNurbs(FNurbsSurfaceHomogeneousData& NurbsData);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)
- L118 _function_ `` (scope `UE::CADKernel::FNURBSSurface::ValidateUVPoints`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/OffsetSurface.h` (Private)


#### class `UE::CADKernel::FOffsetSurface`  
`class FOffsetSurface : public FSurface`  
_L9-91_
- inherits: `FSurface`
- L15 _protected member_ `TSharedPtr<FSurface> BaseSurface;`
- L16 _protected member_ `double Offset;`
- L18 _protected function_ `FOffsetSurface(const double InToleranceGeometric, TSharedRef<FSurface> InBaseSurface, double InOffset) : FSurface(InToleranceGeometric) , BaseSurface(InBaseSurface) , Offset(InOffset)`
- L26 _protected prototype_ `FOffsetSurface() = default;`
- L28 _protected function_ `void ComputeMinToleranceIso()`
- L35 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L42 _public function_ `virtual void SpawnIdent(FDatabase& Database) override`
- L52 _public function_ `virtual void ResetMarkersRecursively() const override`
- L58 _public function_ `ESurface GetSurfaceType() const`
- L63 _public function_ `const double GetOffset() const`
- L68 _public function_ `TSharedPtr<FSurface> GetBaseSurface() const`
- L73 _public prototype_ `virtual void InitBoundary() override;`
- L76 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L79 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L81 _public prototype_ `virtual void LinesNotDerivables(const FSurfacicBoundary& Bounds, int32 InDerivativeOrder, FCoordinateGrid& OutNotDerivableCoordinates) const override;`
- L86 _public prototype_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override;` — The Gradient and Laplacian are approximated by their value on the carrier surface.
- L87 _public prototype_ `virtual void EvaluatePoints(const TArray<FVector2d>& InSurfacicCoordinates, TArray<FSurfacicPoint>& OutPoint3D, int32 InDerivativeOrder = 0) const override;`
- L88 _public prototype_ `virtual void EvaluatePointGrid(const FCoordinateGrid& Coordinates, FSurfacicSampling& OutPoints, bool bComputeNormals = false) const override;`
- L90 _public prototype_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates) override;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/PlaneSurface.h` (Private)


#### class `UE::CADKernel::FPlaneSurface`  
`class FPlaneSurface : public FSurface`  
_L8-108_
- inherits: `FSurface`
- L14 _protected member_ `FMatrixH Matrix;`
- L15 _protected member_ `FMatrixH InverseMatrix;`
- L21 _protected prototype_ `FPlaneSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, const FSurfacicBoundary& InBoundary);` — The plane surface is the plane XY. The surface is placed at its final position and orientation by the Matrix
- L28 _protected function_ `FPlaneSurface(const double InToleranceGeometric, double InDistanceFromOrigin, FVector InNormal, const FSurfacicBoundary& InBoundary) : FPlaneSurface(InToleranceGeometric, InNormal* InDistanceFromOrigin, InNormal, InBoundary)` — The plane surface is the plane XY. The surface is placed at its final position and orientation by the Matrix, The matrix is calculated from the normal plane at its final position and its distance from the origin along the normal.
- L38 _protected prototype_ `FPlaneSurface(const double InToleranceGeometric, const FVector& Position, FVector Normal, const FSurfacicBoundary& InBoundary);` — The plane surface is the plane XY. The surface is placed at its final position and orientation by the Matrix The matrix is calculated from the plan origin at its final position and its final normal
- L40 _protected prototype_ `FPlaneSurface() = default;`
- L42 _protected function_ `void ComputeMinToleranceIso()`
- L57 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L64 _public function_ `ESurface GetSurfaceType() const`
- L69 _public function_ `const FMatrixH& GetMatrix() const`
- L74 _public prototype_ `FPlane GetPlane() const;`
- L77 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L80 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L82 _public prototype_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override;`
- L83 _public prototype_ `virtual void EvaluatePoints(const TArray<FVector2d>& InSurfacicCoordinates, TArray<FSurfacicPoint>& OutPoint3D, int32 InDerivativeOrder = 0) const override;`
- L84 _public prototype_ `virtual void EvaluatePointGrid(const FCoordinateGrid& Coordinates, FSurfacicSampling& OutPoints, bool bComputeNormals = false) const override;`
- L86 _public prototype_ `virtual FVector ProjectPoint(const FVector& InPoint, FVector* OutProjectedPoint = nullptr) const;` — override;
- L87 _public prototype_ `virtual void ProjectPoints(const TArray<FVector>& InPoints, TArray<FVector>* OutProjectedPointCoordinates, TArray<FVector>* OutProjectedPoints = nullptr) const;` — override;
- L89 _public function_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates) override`
- L102 _public function_ `virtual void IsSurfaceClosed(bool& bOutClosedAlongU, bool& bOutClosedAlongV) const override`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/RevolutionSurface.h` (Private)


#### class `UE::CADKernel::FRevolutionSurface`  
`class FRevolutionSurface : public FSurface`  
_L11-78_
- inherits: `FSurface`
- L17 _protected member_ `TSharedPtr<FSegmentCurve> Axis;`
- L18 _protected member_ `TSharedPtr<FCurve> Generatrix;`
- L20 _protected member_ `FVector RotationAxis;`
- L33 _protected prototype_ `FRevolutionSurface(const double InToleranceGeometric, TSharedRef<FSegmentCurve> Axe, TSharedRef<FCurve> Generatrix, double MinAngle, double MaxAngle);` — A surface of revolution is defined by an axis of rotation (Axis) and a generatrix. The start and terminate rotation angles can limited the surface. The surface is created by rotating the generatrix about the axis of rotation through the start and terminating angles. The bounds of the surface of revolution are defined as follow: Bounds[EIso::IsoU].Min = Start rotation angle; Bounds[EIso::IsoU].Max = Terminate rotation angle; Bounds[EIso::IsoV].Min = Min Generatrix bounds; Bounds[EIso::IsoV].Max = Max Generatrix bounds;
- L35 _protected prototype_ `FRevolutionSurface() = default;`
- L39 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L47 _public prototype_ `virtual void SpawnIdent(FDatabase& Database) override;`
- L48 _public prototype_ `virtual void ResetMarkersRecursively() const override;`
- L50 _public function_ `ESurface GetSurfaceType() const`
- L55 _public function_ `TSharedPtr<FCurve> GetGeneratrix() const`
- L60 _public function_ `virtual TSharedPtr<FSegmentCurve> GetAxe() const`
- L66 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L69 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L71 _public prototype_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override;`
- L72 _public prototype_ `virtual void EvaluatePointGrid(const FCoordinateGrid& Coordinates, FSurfacicSampling& OutPoints, bool bComputeNormals = false) const override;`
- L74 _public prototype_ `virtual void LinesNotDerivables(const FSurfacicBoundary& Bounds, int32 InDerivativeOrder, FCoordinateGrid& OutCoordinates) const override;`
- L76 _public prototype_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates) override;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/RuledSurface.h` (Private)


#### class `UE::CADKernel::FRuledSurface`  
`class FRuledSurface : public FSurface`  
_L11-63_
- inherits: `FSurface`
- L16 _protected member_ `TSharedPtr<FCurve> Curves[2];`
- L18 _protected function_ `FRuledSurface(const double InToleranceGeometric, TSharedPtr<FCurve> InCurveU, TSharedPtr<FCurve> InCurveV) : FSurface(InToleranceGeometric, 0., 1., 0., 1.)`
- L26 _protected prototype_ `FRuledSurface() = default;`
- L30 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L37 _public prototype_ `virtual void SpawnIdent(FDatabase& Database) override;`
- L38 _public prototype_ `virtual void ResetMarkersRecursively() const override;`
- L40 _public function_ `ESurface GetSurfaceType() const`
- L45 _public function_ `const TSharedPtr<FCurve>& GetCurve(EIso Iso) const`
- L51 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L54 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L56 _public prototype_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override;`
- L57 _public prototype_ `virtual void EvaluatePointGrid(const FCoordinateGrid& Coordinates, FSurfacicSampling& OutPoints, bool bComputeNormals = false) const override;`
- L59 _public prototype_ `virtual void LinesNotDerivables(const FSurfacicBoundary& Bounds, int32 InDerivativeOrder, FCoordinateGrid& OutCoordinates) const override;`
- L61 _public prototype_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates) override;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/SphericalSurface.h` (Private)


#### class `UE::CADKernel::FSphericalSurface`  
`class FSphericalSurface : public FSurface`  
_L8-139_
- inherits: `FSurface`
- L13 _protected member_ `FMatrixH Matrix;`
- L14 _protected member_ `double Radius;`
- L23 _protected function_ `FSphericalSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, double InRadius, double InParallelStartAngle = 0.0, double InParallelEndAngle = DOUBLE_TWO_PI, double InMeridianStartAngle = -DOUBLE_HALF_PI, double InMeridianEndAngle = DOUBLE_HALF_PI) : FSphericalSurface(InToleranceGeometric, InMatrix, InRadius, FSurfacicBoundary(InParallelStartAngle, InParallelEndAngle, InMeridianStartAngle, InMeridianEndAngle))` — The spherical surface is defined its radius. It's defined as the rotation around Z axis of an semicircle defined in the plan XY centered at the origin. The spherical surface is placed at its final position and orientation by the Matrix
- L41 _protected function_ `FSphericalSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, double InRadius, const FSurfacicBoundary& Boundary) : FSurface(InToleranceGeometric, Boundary) , Matrix(InMatrix) , Radius(InRadius)` — The spherical surface is defined its radius. It's defined as the rotation around Z axis of an semicircle defined in the plan XY centered at the origin. The spherical surface is placed at its final position and orientation by the Matrix The bounds of the spherical surface are defined as follow: Bounds[EIso::IsoU].Min = MeridianStartAngle Bounds[EIso::IsoU].Max = MeridianEndAngle Bounds[EIso::IsoV].Min = ParallelStartAngle Bounds[EIso::IsoV].Max = ParallelEndAngle
- L49 _protected prototype_ `FSphericalSurface() = default;`
- L51 _protected function_ `void ComputeMinToleranceIso()`
- L68 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L75 _public function_ `ESurface GetSurfaceType() const`
- L81 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L84 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L86 _public function_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override`
- L119 _public prototype_ `virtual void EvaluatePointGrid(const FCoordinateGrid& Coordinates, FSurfacicSampling& OutPoints, bool bComputeNormals = false) const override;`
- L121 _public function_ `virtual FVector2d EvaluatePointInCylindricalSpace(const FVector2d& InSurfacicCoordinate) const override`
- L132 _public prototype_ `virtual void EvaluatePointGridInCylindricalSpace(const FCoordinateGrid& Coordinates, TArray<FVector2d>&) const override;`
- L134 _public function_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates) override`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/TabulatedCylinderSurface.h` (Private)


#### class `UE::CADKernel::FTabulatedCylinderSurface`  
`class FTabulatedCylinderSurface : public FSurface`  
_L11-78_
- inherits: `FSurface`
- L16 _protected member_ `TSharedPtr<FCurve> GuideCurve;`
- L17 _protected member_ `FVector DirectorVector;`
- L28 _protected function_ `FTabulatedCylinderSurface(const double InToleranceGeometric, TSharedPtr<FCurve> InGuideCurve, const FVector& InDirectorVector, double InVMin = 0., double InVMax = 1.) : FSurface(InToleranceGeometric, 0.0, 1.0, InVMin, InVMax) , GuideCurve(InGuideCurve) , DirectorVector(InDirectorVector)` — A tabulated cylinder is a surface formed by moving a curve segment called GuideCurve parallel to itself along a vector called DirectorVector. The bounds of the cylinder are defined as follow: Bounds[EIso::IsoU] = GuideCurve bounds; Bounds[EIso::IsoV].Min = InVMin; Bounds[EIso::IsoV].Max = InVMax;
- L36 _protected prototype_ `FTabulatedCylinderSurface() = default;`
- L40 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L47 _public prototype_ `virtual void SpawnIdent(FDatabase& Database) override;`
- L48 _public prototype_ `virtual void ResetMarkersRecursively() const override;`
- L50 _public function_ `ESurface GetSurfaceType() const`
- L55 _public function_ `TSharedPtr<FCurve> GetGuideCurve() const`
- L60 _public function_ `FVector GetDirectorVector() const`
- L65 _public prototype_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override;`
- L66 _public prototype_ `virtual void EvaluatePointGrid(const FCoordinateGrid& Coordinates, FSurfacicSampling& OutPoints, bool bComputeNormals = false) const override;`
- L68 _public prototype_ `virtual void LinesNotDerivables(const FSurfacicBoundary& Bounds, int32 InDerivativeOrder, FCoordinateGrid& OutNotDerivables) const override;`
- L70 _public prototype_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates) override;`
- L72 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L75 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Geo/Surfaces/TorusSurface.h` (Private)


#### class `UE::CADKernel::FTorusSurface`  
`class FTorusSurface : public FSurface`  
_L8-151_
- inherits: `FSurface`
- L13 _protected member_ `FMatrixH Matrix;`
- L14 _protected member_ `double MajorRadius;`
- L15 _protected member_ `double MinorRadius;`
- L25 _protected function_ `FTorusSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, double InMajorRadius, double InMinorRadius, double InMajorStartAngle = 0.0, double InMajorEndAngle = DOUBLE_TWO_PI, double InMinorStartAngle = 0.0, double InMinorEndAngle = DOUBLE_TWO_PI) : FTorusSurface(InToleranceGeometric, InMatrix, InMajorRadius, InMinorRadius, FSurfacicBoundary(InMajorStartAngle, InMajorEndAngle, InMinorStartAngle, InMinorEndAngle))` — A torus is the solid formed by revolving a circular disc about a specified coplanar axis. MajorRadius is the distance from the axis to the center of the defining disc, and MinorRadius is the radius of the defining disc, where MajorRadius > MinorRadius > 0.0. The torus computed at the origin with Z axis. It is placed at its final position and orientation by the Matrix
- L44 _protected function_ `FTorusSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, double InMajorRadius, double InMinorRadius, const FSurfacicBoundary& InBoundary) : FSurface(InToleranceGeometric, InBoundary) , Matrix(InMatrix) , MajorRadius(InMajorRadius) , MinorRadius(InMinorRadius)` — A torus is the solid formed by revolving a circular disc about a specified coplanar axis. MajorRadius is the distance from the axis to the center of the defining disc, and MinorRadius is the radius of the defining disc, where MajorRadius > MinorRadius > 0.0. The torus computed at the origin with Z axis. It is placed at its final position and orientation by the Matrix The bounds of the cone are defined as follow: Bounds[EIso::IsoU].Min = MajorStartAngle Bounds[EIso::IsoU].Max = MajorEndAngle Bounds[EIso::IsoV].Min = MinorStartAngle Bounds[EIso::IsoV].Max = MinorEndAngle
- L53 _protected prototype_ `FTorusSurface() = default;`
- L55 _protected function_ `void ComputeMinToleranceIso()`
- L73 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L81 _public function_ `ESurface GetSurfaceType() const`
- L87 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L90 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L92 _public function_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const override`
- L127 _public prototype_ `virtual void EvaluatePointGrid(const FCoordinateGrid& Coordinates, FSurfacicSampling& OutPoints, bool bComputeNormals = false) const override;`
- L129 _public prototype_ `virtual void EvaluatePointGridInCylindricalSpace(const FCoordinateGrid& Coordinates, TArray<FVector2d>&) const override;`
- L131 _public function_ `virtual FVector2d EvaluatePointInCylindricalSpace(const FVector2d& InSurfacicCoordinate) const override`
- L145 _public function_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates) override`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Criteria/AngleCriterion.h` (Private)


#### class `UE::CADKernel::FAngleCriterion`  
`class FAngleCriterion : public FCriterion`  
_L14-73_
- inherits: `FCriterion`
- L19 _protected member_ `double AngleCriterionValue;`
- L20 _protected member_ `double SinMaxAngle;`
- L25 _protected function_ `FAngleCriterion(double DegreeAngle)` — @param DegreeAngle the max allowed angle between tow elements in degree
- L31 _protected prototype_ `FAngleCriterion() = default;`
- L35 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L42 _public function_ `virtual double Value() const override`
- L47 _public function_ `static double DefaultValue()`
- L52 _public function_ `virtual bool IsAppliedBetweenBreaks() const override`
- L57 _public function_ `virtual ECriterion GetCriterionType() const override`
- L69 _protected function_ `virtual double ComputeDeltaU(double ChordLength, double DeltaU, double Sag) const override` — Sag & Angle criterion.pdf https://docs.google.com/presentation/d/1bUnrRFWCW3sDn9ngb9ftfQS-2JxNJaUZlh783hZMMEw/edit?usp=sharing

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Criteria/CriteriaGrid.h` (Private)


#### class `UE::CADKernel::FCriteriaGrid`  
`class FCriteriaGrid : public FGridBase`  
_L14-102_
- inherits: `FGridBase`
- L22 _private member_ `FCoordinateGrid CoordinateGrid;` — Cutting coordinates of the face respecting the meshing criteria
- L24 _private member_ `FSurfacicBoundary FaceMinMax;`
- L28 _protected function_ `virtual const FCoordinateGrid& GetCoordinateGrid() const override`
- L33 _protected function_ `int32 GetIndex(int32 UIndex, int32 VIndex, bool bIsInternalU, bool bIsInternalV) const`
- L48 _protected function_ `const FVector& GetPoint(int32 UIndex, int32 VIndex, bool bIsInternalU, bool bIsInternalV) const`
- L55 _protected prototype_ `void Init();`
- L57 _protected function_ `double GetCoordinate(EIso Iso, int32 ind) const`
- L64 _public prototype_ `FCriteriaGrid(FTopologicalFace& InFace);`
- L67 _public function_ `const FVector& GetPoint(int32 iU, int32 iV) const`
- L72 _public function_ `const FVector& GetIntermediateU(int32 iU, int32 iV) const`
- L77 _public function_ `const FVector& GetIntermediateV(int32 iU, int32 iV) const`
- L82 _public function_ `const FVector& GetIntermediateUV(int32 iU, int32 iV) const`
- L87 _public prototype_ `void ComputeFaceMinMaxThicknessAlongIso();`
- L89 _public function_ `double GetCharacteristicThicknessOfFace() const`
- L97 _public prototype_ `bool CheckIfIsDegenerate();` — @return true if all the iso lines are smaller than geometric tolerance
- L100 _public prototype_ `void Display() const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Criteria/CurvatureCriterion.h` (Private)


#### class `UE::CADKernel::FCurvatureCriterion`  
`class FCurvatureCriterion : public FCriterion`  
_L11-78_
- inherits: `FCriterion`
- L17 _protected prototype_ `FCurvatureCriterion() = default;`
- L21 _public function_ `void Serialize(FCADKernelArchive& Ar)`
- L30 _public function_ `virtual void UpdateDelta(double InDeltaU, double InUSag, double InDiagonalSag, double InVSag, double ChordLength, double DiagonalLength, double& OutSagDeltaUMax, double& OutSagDeltaUMin, FIsoCurvature& IsoCurvature) const override` — Sag & Angle criterion.pdf https://docs.google.com/presentation/d/1bUnrRFWCW3sDn9ngb9ftfQS-2JxNJaUZlh783hZMMEw/edit?usp=sharing
- L46 _public function_ `virtual double Value() const override`
- L51 _public function_ `virtual void ApplyOnEdgeParameters(FTopologicalEdge& Edge, const TArray<double>& Coordinates, const TArray<FCurvePoint>& Points) const override`
- L56 _public function_ `virtual ECriterion GetCriterionType() const override`
- L68 _protected function_ `virtual bool IsAppliedBetweenBreaks() const override` — Sag & Angle criterion.pdf https://docs.google.com/presentation/d/1bUnrRFWCW3sDn9ngb9ftfQS-2JxNJaUZlh783hZMMEw/edit?usp=sharing
- L73 _protected function_ `virtual double ComputeDeltaU(double ChordLength, double DeltaU, double Sag) const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Criteria/SagCriterion.h` (Private)


#### class `UE::CADKernel::FSagCriterion`  
`class FSagCriterion : public FCriterion`  
_L9-60_
- inherits: `FCriterion`
- L14 _protected member_ `double MaxSag;`
- L16 _protected function_ `FSagCriterion(double InSag = 0.2) : MaxSag(InSag)`
- L23 _public function_ `void Serialize(FCADKernelArchive& Ar)`
- L29 _public function_ `virtual double Value() const override`
- L34 _public function_ `static double DefaultValue()`
- L39 _public function_ `virtual ECriterion GetCriterionType() const override`
- L51 _protected function_ `virtual double ComputeDeltaU(double ChordLength, double DeltaU, double Sag) const override` — Sag & Angle criterion.pdf https://docs.google.com/presentation/d/1bUnrRFWCW3sDn9ngb9ftfQS-2JxNJaUZlh783hZMMEw/edit?usp=sharing
- L56 _protected function_ `virtual bool IsAppliedBetweenBreaks() const override`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Criteria/SizeCriterion.h` (Private)


#### class `UE::CADKernel::FSizeCriterion`  
`class FSizeCriterion : public FCriterion`  
_L15-58_
- inherits: `FCriterion`
- L20 _protected member_ `double Size;`
- L22 _protected function_ `FSizeCriterion(double InSize = 1.) : Size(InSize)`
- L27 _protected function_ `double ComputeSizeCriterionValue(double InDeltaU, double ChordLength) const`
- L34 _public function_ `void Serialize(FCADKernelArchive& Ar)`
- L40 _public function_ `double Value() const override`
- L45 _public function_ `static double DefaultValue(ECriterion Type)`
- L57 _public prototype_ `void ApplyOnParameters(const TArray<double>& Coordinates, const TArray<FCurvePoint>& Points, TArray<double>& DeltaUMax, TArray<double>& DeltaUMins, TFunction<void(double, double&, double&)> UpdateDeltaU) const;`

#### class `UE::CADKernel::FMinSizeCriterion`  
`class FMinSizeCriterion : public FSizeCriterion`  
_L60-83_
- inherits: `FSizeCriterion`
- L64 _protected function_ `FMinSizeCriterion(double InSize = 0.05) : FSizeCriterion(InSize)`
- L71 _public function_ `virtual ECriterion GetCriterionType() const override`
- L76 _public prototype_ `virtual void ApplyOnEdgeParameters(FTopologicalEdge& Edge, const TArray<double>& Coordinates, const TArray<FCurvePoint>& Points) const override;`
- L82 _public prototype_ `virtual void UpdateDelta(double InDeltaU, double InUSag, double InDiagonalSag, double InVSag, double ChordLength, double DiagonalLength, double& OutSagDeltaUMax, double& OutSagDeltaUMin, FIsoCurvature& SurfaceCurvature) const override;` — MinSizeCrtierion sets DeltaUMin. @see FCriterion::UpdateWithUMinValue

#### class `UE::CADKernel::FMaxSizeCriterion`  
`class FMaxSizeCriterion : public FSizeCriterion`  
_L85-107_
- inherits: `FSizeCriterion`
- L89 _protected function_ `FMaxSizeCriterion(double InSize = 10000.) : FSizeCriterion(InSize)`
- L95 _public function_ `virtual ECriterion GetCriterionType() const override`
- L100 _public prototype_ `virtual void ApplyOnEdgeParameters(FTopologicalEdge& Edge, const TArray<double>& Coordinates, const TArray<FCurvePoint>& Points) const override;`
- L106 _public prototype_ `virtual void UpdateDelta(double InDeltaU, double InUSag, double InDiagonalSag, double InVSag, double ChordLength, double DiagonalLength, double& OutSagDeltaUMax, double& OutSagDeltaUMin, FIsoCurvature& SurfaceCurvature) const override;` — MaxSizeCriterion sets DeltaUMax. @see FCriterion::UpdateWithUMaxValue

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/BowyerWatsonTriangulator.h` (Private)


#### class `UE::CADKernel::FBowyerWatsonTriangulator`  
`class FBowyerWatsonTriangulator`  
_L11-660_
- L43 _public function_ `FBowyerWatsonTriangulator(TArray<TPair<int32, FVector2d>>& InVertices, TArray<int32>& OutEdgeVertices) : VerticesCount(InVertices.Num()) , Vertices(InVertices) , EdgeVertexIndices(OutEdgeVertices)` — @param Vertices the 2d point cloud to mesh @param OutEdgeVertices, the edges of the mesh. An edge is defined by the indices of its vertices So the ith edge is defined by the vertices EdgeVertexIndices[2 * ith] and EdgeVertexIndices[2 * ith + 1]
- L51 _public function_ `void Triangulate()`
- L358 _public function_ `int32 OuterEdgeCount() const`
- L374 _public function_ `void GetOuterEdges(TArray<int32>& OuterEdgeIndices) const` — Return the edge connected to 0 or 1 triangle
- L392 _public function_ `void GetOuterVertices(TSet<int32>& OuterVertexIndices) const`
- L410 _public function_ `TArray<int32> GetOuterVertices() const`
- L417 _public function_ `void GetMesh(TArray<int32>& Triangles)`
- L427 _public member_ `static bool bDisplay;`
- L431 _private member_ `int32 VerticesCount;`
- L433 _private member_ `TArray<TPair<int32, FVector2d>>& Vertices;`
- L439 _private member_ `TArray<int32>& EdgeVertexIndices;` — An edge is defined by the indices of its vertices So the ith edge is defined by the vertices EdgeVertexIndices[2 * ith] and EdgeVertexIndices[2 * ith + 1]
- L441 _private member_ `TArray<FTriangle> TriangleSet;`
- L444 _private member_ `TArray<int32> SelectedTriangleIndices;` — It's use to mark all triangles whose circumcircles contain the next vertex
- L445 _private member_ `TArray<int32> AdditionalTriangleIndices;`
- L451 _private member_ `TArray<int32> EdgeInstanceCount;` — Use to determine if the edge is a border edge of inner edge If EdgeInstanceCount[ith] = 2, the edge is a inner edge
- L453 _private function_ `void MakeBoundingMesh()`
- L474 _private function_ `void Init()`
- L491 _private function_ `void FindBoundaryEdgesOfSelectedTriangles(TArray<int32>& BoundaryEdgeVertexIndices)` — Find the boundary edges of the selected triangles: For all selected triangles, For each triangle edges if the edge is not in EdgeVertexIndices: Add the edge i.e. add its vertex indices else (the edge is in EdgeVertexIndices), remove the edge of EdgeVertexIndices As the triangles are oriented, the edge AB of a triangle is the edge BA of the adjacent triangle
- L521 _private function_ `bool DoSelectedTrianglesFormSinglePartition()`
- L572 _private function_ `bool DoesTriangleContainingNewVertex(const FVector2d& NewVertex, int32 CandiadateTriangle)`
- L587 _private function_ `void AddTrianglesContainingNewVertexToSelectedTriangles(const FVector2d& NewVertex, TArray<int32>& CandiadateTriangles)`
- L599 _private function_ `void AddConnectedTrianglesToSelection(TArray<int32>& CandiadateTriangles)`

#### struct `UE::CADKernel::FBowyerWatsonTriangulator::FTriangle`  
`struct FTriangle`  
_L14-33_
- L16 _public member_ `int32 VertexIndices[3];`
- L17 _public member_ `double SquareRadius;`
- L18 _public member_ `FVector Center;`
- L20 _public function_ `FTriangle(const int32& Index0, const int32& Index1, const int32& Index2, const TArray<TPair<int32, FVector2d>>& InVertices)`
- L25 _public function_ `void Set(const int32& Index0, const int32& Index1, const int32& Index2, const TArray<TPair<int32, FVector2d>>& InVertices)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)
- L53 _function_ `Vertices.Sort([](const TPair<int32, FVector2d>& Vertex1, const TPair<int32, FVector2d>& Vertex2) {return (Vertex1.Value.X + Vertex1.Value.Y) > (Vertex2.Value.X + Vertex2.Value.Y); });` (scope `UE::CADKernel::FBowyerWatsonTriangulator::Triangulate`)
- L192 _function_ `BoundaryVertexToSlope.Sort([](const TPair<int32, double>& Vertex1, const TPair<int32, double>& Vertex2) {return Vertex1.Value < Vertex2.Value; });` (scope `UE::CADKernel::FBowyerWatsonTriangulator::Triangulate`) — Sort the vertex to make the boundary polygon

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/CycleTriangulator.h` (Private)


#### struct `UE::CADKernel::FCandidateNode`  
`struct FCandidateNode`  
_L22-38_
- L24 _public member_ `FIsoNode* Node;`
- L25 _public member_ `double SlopeAtStartNode;`
- L26 _public member_ `double SlopeAtEndNode;`
- L27 _public member_ `int32 Index;`
- L28 _public member_ `bool bIsValid;`
- L30 _public prototype_ `FCandidateNode() = default;`
- L31 _public function_ `FCandidateNode(FIsoNode* InNode, double InSlopeAtStartNode, double InSlopeAtEndNode, int32 InIndex) :Node(InNode) , SlopeAtStartNode(InSlopeAtStartNode) , SlopeAtEndNode(InSlopeAtEndNode) , Index(InIndex) , bIsValid(false)`

#### struct `UE::CADKernel::FAdditionalIso`  
`struct FAdditionalIso`  
_L40-107_
- L42 _public member_ `int32 StartIndex = 0;`
- L43 _public member_ `FIsoNode* StartNode = nullptr;`
- L45 _public member_ `int32 EndIndex = 0;`
- L46 _public member_ `FIsoNode* EndNode = nullptr;`
- L48 _public member_ `int32 NodeIndices[2] = { -1, -1 };`
- L49 _public member_ `FIsoNode* Nodes[2] = { nullptr , nullptr };`
- L51 _public member_ `double EquilateralCriteria[2] = { Slope::TwoPiSlope, Slope::TwoPiSlope };`
- L53 _public member_ `bool bForceNodes = false;`
- L55 _public function_ `FAdditionalIso(int32 InStartIndex, int32 InEndIndex, FIsoNode* InStartNode, FIsoNode* InEndNode) : StartIndex(InStartIndex) , StartNode(InStartNode) , EndIndex(InEndIndex) , EndNode(InEndNode)`
- L62 _public function_ `int32 CandidateNodeCount()`
- L67 _public function_ `void AddTo(TArray<FIsoNode*>& PolygonNodes)`
- L78 _public function_ `void RemoveCandidate(int32 Index)`
- L85 _public function_ `void Reset()`
- L96 _public function_ `void RemoveCandidateIfPresent(FIsoNode* ForbiddenNode)`

#### class `UE::CADKernel::FCycleTriangulator`  
`class FCycleTriangulator`  
_L111-284_
- L114 _private member_ `const FGrid& Grid;`
- L116 _private member_ `int32 NodeCount = 0;`
- L117 _private member_ `const TArray<FIsoSegment*>& Cycle;`
- L118 _private member_ `const TArray<bool>& CycleOrientation;`
- L120 _private member_ `const EGridSpace Space = EGridSpace::UniformScaled;`
- L121 _private member_ `const FIntersectionIsoSegmentTool& InnerToOuterIsoSegmentsIntersectionTool;`
- L122 _private member_ `FFaceMesh& Mesh;`
- L123 _private member_ `TFactory<FIsoSegment>& IsoSegmentFactory;`
- L125 _private member_ `FIntersectionSegmentTool CycleIntersectionTool;`
- L127 _private member_ `TArray<FIsoSegment*> SegmentStack;`
- L130 _private member_ `TArray<FIsoSegment*> UnmeshedSegment;` — Array of segments that failed to mesh
- L132 _private member_ `bool bFirstRun = true;`
- L135 _private member_ `int32 SubCycleNodeCount = 0;` — Sub cycle data
- L136 _private member_ `TArray<FIsoNode*> SubCycleNodes;`
- L138 _private member_ `TArray<TPair<int32, double>> VertexIndexToSlopes;`
- L139 _private member_ `double MeanSquareLength = 0;`
- L140 _private member_ `bool bAcuteTriangle = false;`
- L142 _private member_ `int32 IntersectionCountAllowed = 0;`
- L143 _private member_ `int32 MaxIntersectionCounted = 0;`
- L145 _private member_ `int32 FirstSideStartIndex = -1;`
- L146 _private member_ `int32 FirstSideEndIndex = -1;`
- L147 _private member_ `int32 TriangleThirdIndex = -1;`
- L148 _private member_ `FIsoNode* FirstSideStartNode;`
- L149 _private member_ `FIsoNode* FirstSideEndNode;`
- L150 _private member_ `FIsoNode* TriangleThirdNode;`
- L153 _private member_ `TArray<FCandidateNode> CandidateNodes;` — Candidates nodes for FindCandidateNodes
- L154 _private member_ `FCandidateNode* ExtremityCandidateNodes[2] = { nullptr, nullptr };`
- L155 _private member_ `TArray<FNodeIntersectionCount> NodeToIntersection;`
- L158 _private member_ `TArray<FIsoNode*> PolygonNodes;` — Final polygon nodes
- L161 _private member_ `bool bNeedIntersectionToolUpdate = true;`
- L163 _private member_ `const SlopeMethod GetSlopeAtStartNode = CounterClockwiseSlope;`
- L164 _private member_ `const SlopeMethod GetSlopeAtEndNode = ClockwiseSlope;`
- L167 _public prototype_ `FCycleTriangulator(FIsoTriangulator& IsoTriangulator, const TArray<FIsoSegment*>& InCycle, const TArray<bool>& InCycleOrientation);`
- L169 _public prototype_ `bool MeshCycle();`
- L172 _private prototype_ `bool CanCycleBeMeshed();`
- L173 _private prototype_ `FIsoSegment* FindNextSegment(const FIsoSegment* StartSegment, const FIsoNode* StartNode, SlopeMethod GetSlope) const;`
- L175 _private prototype_ `void InitializeArrays();`
- L176 _private prototype_ `void CleanContext();`
- L177 _private prototype_ `void InitializeCycleForMeshing();`
- L178 _private prototype_ `void FillSegmentStack();`
- L180 _private prototype_ `bool BuildTheBestPolygon(FIsoSegment* SegmentToMesh, bool bOrientation);`
- L182 _private function_ `int32 NextIndex(int32 Index)`
- L187 _private function_ `int32 PreviousIndex(int32 Index)`
- L196 _private prototype_ `bool FindTheCycleToMesh(FIsoSegment* Segment, bool bOrientation, int32& StartIndexForMinLength);` — Find all potential candidate nodes Find the node with the smallest slope between its adjacent segments
- L198 _private prototype_ `bool FindTheBestAcuteTriangle();`
- L204 _private prototype_ `bool FindCandidateNodes(int32 StartIndex);` — Find all potential candidate nodes i.e. Nodes that can be linked with the Segment to build a valid triangle without intersection with other segments The candidates are saved in PotentialCandidateNodes
- L206 _private prototype_ `bool FindTheBestCandidateNode();`
- L208 _private prototype_ `bool BuildTheBestPolygonFromTheSelectedTriangle();`
- L210 _private prototype_ `void FindComplementaryNodes(FAdditionalIso& Side);`
- L211 _private prototype_ `void ValidateAddNodesAccordingSlopeWithSide(FAdditionalIso& Side);`
- L215 _private prototype_ `void ValidateComplementaryNodesWithInsideAndIntersectionsCriteria(FAdditionalIso& Side);` — Valid additional nodes i.e. check if they can be added in The Side Of Selected Triangle
- L216 _private prototype_ `bool ValidComplementaryNodeOrDeleteIt(FAdditionalIso& Side, int32 Index);`
- L217 _private prototype_ `bool IsInnerSideSegmentInsideCycle(FAdditionalIso& Side);`
- L219 _private prototype_ `void SelectFinalNodes(FAdditionalIso& Side1, FAdditionalIso& Side2);`
- L220 _private prototype_ `void ComputeSideCandidateEquilateralCriteria(FAdditionalIso& Side);`
- L222 _private prototype_ `bool BuildTriangle(TArray<FIsoNode*>& CandidatNodes);`
- L224 _private prototype_ `bool BuildQuadrilateral(TArray<FIsoNode*>& CandidatNodes);`
- L225 _private prototype_ `bool BuildPentagon(TArray<FIsoNode*>& CandidatNodes);`
- L227 _private prototype_ `bool BuildSmallPolygon(TArray<FIsoNode*>& CandidatNodes, bool bCheckIntersectionWithIso);`
- L230 _private prototype_ `bool BuildSegmentIfNeeded(TArray<FIsoNode*>& CandidatNodes);`
- L231 _private prototype_ `bool BuildSegmentIfNeeded(FIsoNode* NodeA, FIsoNode* NodeB);`
- L232 _private prototype_ `bool BuildSegmentIfNeeded(FIsoNode* NodeA, FIsoNode* NodeB, FIsoSegment* ABSegment);`
- L234 _private prototype_ `void SortCycleIntersectionToolIfNeeded();`
- L236 _private function_ `int32 IsIntersectingIso(const TArray<FIsoNode*>& Nodes)`
- L251 _private function_ `int32 CountIntersectionWithIso()`
- L283 _private prototype_ `bool ConfirmIntersection(const FIsoNode* Start, const FIsoNode* End, const FIsoNode* Candidate, const FIsoSegment* IntersectedSegment) const;` — In case of intersection with the loop, confirm that it was a real intersection and not a nearly parallel segment

#### enum `UE::CADKernel::Polygon::ETriangleOfPentagon`  
`enum ETriangleOfPentagon : uint8`  
_L289-302_
- L291 _public enumerator_ `Triangle012 = 0`
- L292 _public enumerator_ `Triangle013`
- L293 _public enumerator_ `Triangle014`
- L294 _public enumerator_ `Triangle023`
- L295 _public enumerator_ `Triangle024`
- L296 _public enumerator_ `Triangle034`
- L297 _public enumerator_ `Triangle123`
- L298 _public enumerator_ `Triangle124`
- L299 _public enumerator_ `Triangle134`
- L300 _public enumerator_ `Triangle234`
- L301 _public enumerator_ `NoTriangle`

#### enum `UE::CADKernel::Polygon::EPentagon`  
`enum class EPentagon : uint8`  
_L308-322_
- desc: Triangles of pentagon or pair of pentagon Triangles
- L310 _public enumerator_ `None = 0x00u`
- L311 _public enumerator_ `P012_023_034 = 0x01u`
- L312 _public enumerator_ `P012_024_234 = 0x02u`
- L313 _public enumerator_ `P012_023_034_or_P012_024_234 = 0x03u`
- L314 _public enumerator_ `P013_034_123 = 0x04u`
- L315 _public enumerator_ `P012_023_034_or_P013_034_123 = 0x05u`
- L316 _public enumerator_ `P014_123_134 = 0x08u`
- L317 _public enumerator_ `P013_034_123_or_P014_123_134 = 0x0Cu`
- L318 _public enumerator_ `P014_124_234 = 0x10u`
- L319 _public enumerator_ `P012_024_234_or_P014_124_234 = 0x12u`
- L320 _public enumerator_ `P014_123_134_or_P014_124_234 = 0x18u`
- L321 _public enumerator_ `All = 0x1Fu`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CADKernel` (scope `UE`)
- L19 _typedef_ `typedef TFunction<double(const FVector2d&, const FVector2d&, double)> SlopeMethod;` (scope `UE::CADKernel`)
- L20 _typedef_ `typedef TFunction<int32(int32)> NextIndexMethod;` (scope `UE::CADKernel`)
- L109 _typedef_ `using FNodeIntersectionCount = TPair<FCandidateNode*, int32>;` (scope `UE::CADKernel`)
- L286 _namespace_ `namespace Polygon` (scope `UE::CADKernel`)
- L305 _variable_ `constexpr uint8 TrianglesOfPentagon[10][3] = { { 0, 1, 2 }, { 0, 1, 3 }, { 0, 1, 4 }, { 0, 2, 3 }, { 0, 2, 4 }, { 0, 3, 4 }, { 1, 2, 3 }, { 1, 2, 4 }, { 1, 3, 4 }, { 2, 3, 4 } };` (scope `UE::CADKernel::Polygon`) — Triangle to vertex indices (cf ETriangle)
- L323 _prototype_ `ENUM_CLASS_FLAGS(EPentagon);` (scope `UE::CADKernel::Polygon`)
- L326 _variable_ `constexpr EPentagon TriangleToPentagon[10] = { EPentagon::P012_023_034_or_P012_024_234,` (scope `UE::CADKernel::Polygon`) — pentagon (or pair) containing the triangle (cf ETriangle)
- L339 _prototype_ `void MeshTriangle(const FGrid& Grid, FIsoNode** Nodes, FFaceMesh& Mesh);` (scope `UE::CADKernel::Polygon`)
- L340 _prototype_ `void MeshQuadrilateral(const FGrid& Grid, FIsoNode** Nodes, FFaceMesh& Mesh);` (scope `UE::CADKernel::Polygon`)
- L341 _prototype_ `void MeshPentagon(const FGrid& Grid, FIsoNode** Nodes, FFaceMesh& Mesh);` (scope `UE::CADKernel::Polygon`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/IsoTriangulator.h` (Private)


#### class `UE::CADKernel::FIsoTriangulator`  
`class FIsoTriangulator`  
_L26-295_
- L35 _protected member_ `FGrid& Grid;`
- L36 _protected member_ `FFaceMesh& Mesh;`
- L38 _protected member_ `TArray<int32> LoopStartIndex;`
- L39 _protected member_ `TArray<FLoopNode> LoopNodes;`
- L40 _protected member_ `int32 LoopNodeCount = 0;`
- L41 _protected member_ `TArray<FLoopNode*> SortedLoopNodes;`
- L46 _protected member_ `TArray<FIsoInnerNode*> GlobalIndexToIsoInnerNodes;` — GlobalIndexToIsoInnerNodes contains only inner nodes of the grid, if GlobalIndexToIsoInnerNodes[Index] == null, the point is outside the domain
- L51 _protected member_ `TArray<FIsoInnerNode> InnerNodes;` — Static array of InnerNodes. Only used for allocation needs
- L52 _protected member_ `int32 InnerNodeCount = 0;`
- L54 _protected member_ `TFactory<FIsoSegment> IsoSegmentFactory;`
- L56 _protected member_ `TArray<FIsoSegment*> LoopSegments;`
- L57 _protected member_ `TArray<FIsoSegment*> ThinZoneSegments;`
- L58 _protected member_ `TArray<FIsoSegment*> FinalInnerSegments;`
- L59 _protected member_ `TArray<FIsoSegment*> InnerToOuterSegments;`
- L65 _protected member_ `TArray<FIsoSegment*> InnerToLoopCandidateSegments;` — Waiting list for SelectSegmentsToLinkInnerToLoop Segments are identified in each cell but not directly processed
- L72 _protected member_ `FIntersectionSegmentTool LoopSegmentsIntersectionTool;` — Tool to check if a segment intersect or not existing segments. To be optimal, depending on the segment, only a subset of segment is used. Checks intersection with loop.
- L75 _protected member_ `FIntersectionSegmentTool InnerSegmentsIntersectionTool;` — Boundary of the inner grid
- L78 _protected member_ `FIntersectionIsoSegmentTool InnerToOuterIsoSegmentsIntersectionTool;` — To check if the candidate segment intersect a iso line
- L81 _protected member_ `FIntersectionSegmentTool ThinZoneIntersectionTool;` — To check if a candidate segment intersect a thin zone that is already meshed
- L88 _protected member_ `TArray<int32> IndexOfLowerLeftInnerNodeSurroundingALoop;` — Define all the lower left index of grid node that the upper cell is surrounding a loop This is set in FindSegmentIsoUVSurroundingSmallLoop and use in TriangulateInnerNodes to don't generate the both cell triangles
- L95 _protected member_ `TArray<FIsoSegment*> FinalToLoops;` — Segments to link inner to boundary and boundary to boundary From FindIsoSegmentToLinkInnerToBoundary SelectSegmentInCandidateSegments
- L100 _protected member_ `TArray<FIsoSegment*> CandidateSegments;`
- L102 _protected member_ `bool bDisplay = false;`
- L104 _protected member_ `bool bNeedCheckOrientation = false;`
- L107 _public member_ `const FMeshingTolerances& Tolerances;`
- L111 _public prototype_ `FIsoTriangulator(FGrid& InGrid, FFaceMesh& OutMesh, const FMeshingTolerances& InTolerance);`
- L117 _public prototype_ `bool Triangulate();` — Main method @return false if the tessellation failed
- L119 _public prototype_ `void BuildNodes();`
- L125 _public prototype_ `void BuildLoopSegments();` — Build the segments of the loops and check if each loop is self intersecting. @return false if the loop is self intersecting
- L127 _public prototype_ `void BuildInnerSegments();`
- L133 _public prototype_ `void GetThinZonesMesh();` — Add temporary loops defining thin zones to avoid the tessellation of these zone. These zones are tessellated in a specific process
- L134 _public prototype_ `void GetThinZoneMesh(const TMap<int32, FLoopNode*>& IndexToNode, const FThinZone2D& ThinZone);`
- L139 _public prototype_ `void FillMeshNodes();` — Fill mesh node data (Position, normal, UV, Index) of the FFaceMesh object
- L149 _public prototype_ `void BuildInnerSegmentsIntersectionTool();` — Build the Inner Segments Intersection Tool used to check if a candidate segment crosses the inner mesh The minimal set of segments of the intersection tool is the boundaries of the inner triangulation. https://docs.google.com/presentation/d/1qUVOH-2kU_QXBVKyRUcdDy1Y6WGkcaJCiaS8wGjSZ6M/edit?usp=sharing Slide "Boundary Segments Of Inner Triangulation"
- L165 _public prototype_ `void FindInnerGridCellSurroundingSmallLoop();` — The purpose of the method is to add surrounding segments (boundary of an unitary inner grid cell) to the small loop to intersection tool to prevent traversing inner segments A loop is inside inner segments |			 | |	 XXX	 | |	XXXXX	 | |	 XXX	 | |			 | https://docs.google.com/presentation/d/1qUVOH-2kU_QXBVKyRUcdDy1Y6WGkcaJCiaS8wGjSZ6M/edit?usp=sharing Slide "Find Inner Grid Cell Surrounding Small Loop" This method finalizes BuildInnerSegmentsIntersectionTool
- L167 _public prototype_ `void ConnectCellLoops();`
- L168 _public prototype_ `void FindCellContainingBoundaryNodes(TArray<FCell>& Cells);`
- L170 _public prototype_ `void FindCandidateToConnectCellCornerToLoops(FCell& Cell);`
- L172 _public prototype_ `void SelectSegmentsToLinkInnerToLoop();`
- L174 _public prototype_ `void InitCellCorners(FCell& Cell);`
- L181 _public prototype_ `void TriangulateOverCycle(const EGridSpace Space);` — Finalize the tessellation between inner grid boundary and loops. The final set of segments define a network Each minimal cycle is tessellated independently
- L187 _public prototype_ `bool FindCycle(FIsoSegment* StartSegment, bool bLeftSide, TArray<FIsoSegment*>& Cycle, TArray<bool>& CycleOrientation);` — Find in the network a minimal cycle stating from a segment @return false if the new cycle crosses a segment already used
- L193 _public prototype_ `void MeshCycle(const TArray<FIsoSegment*>& Cycle, const TArray<bool>& CycleOrientation);` — Generate the "Delaunay" tessellation of the cycle. The algorithm is based on frontal process
- L194 _public prototype_ `void MeshLargeCycle(const TArray<FIsoSegment*>& Cycle, const TArray<bool>& CycleOrientation);`
- L197 _public function_ `template <uint32 Dim> void MeshCycleOf(const TArray<FIsoSegment*>& Cycle, const TArray<bool>& CycleOrientation, FMeshPolygonFunc MeshPolygonFunc)`
- L209 _public prototype_ `bool CanCycleBeMeshed(const TArray<FIsoSegment*>& Cycle, FIntersectionSegmentTool& CycleIntersectionTool);`
- L214 _public prototype_ `void TriangulateInnerNodes();` — Finalization of the mesh by the tessellation of the inner grid
- L219 _public function_ `void SortLoopNodes()` — Sorted loop node array used to have efficient loop proximity node research
- L235 _public function_ `const FGrid& GetGrid() const`
- L242 _private prototype_ `FIsoSegment* FindNextSegment(EGridSpace Space, const FIsoSegment* StartSegment, const FIsoNode* StartNode, SlopeMethod GetSlop) const;`
- L248 _private prototype_ `void TryToConnectTwoLoopsWithIsocelesTriangle(FCell& Cell, const TArray<FLoopNode*>& SubLoopA, const TArray<FLoopNode*>& SubLoopB);`
- L258 _private prototype_ `void TryToConnectTwoSubLoopsWithTheMostIsoSegment(FCell& Cell, const TArray<FLoopNode*>& SubLoopA, const TArray<FLoopNode*>& SubLoopB);` — --X------X-----X--  <-- SubLoopA I I    <- The most isoSegment I ----X----X--------  <-- SubLoopB
- L268 _private prototype_ `void TryToConnectVertexSubLoopWithTheMostIsoSegment(FCell& Cell, const TArray<FLoopNode*>& SubLoop);` — X--X------X-----X--  <-- SubLoop |         I |         I   <- The most isoSegment |         I X----X----X--------
- L269 _private prototype_ `FIsoSegment* GetOrTryToCreateSegment(FCell& Cell, FLoopNode* NodeA, const FVector2d& ACoordinates, FIsoNode* NodeB, const FVector2d& BCoordinates, const double FlatAngle);`
- L273 _public member_ `FIsoTriangulatorChronos Chronos;`
- L277 _public prototype_ `void DisplayPixels(TArray<uint8>& Pixel) const;`
- L279 _public prototype_ `void DisplayPixel(const int32 Index) const;`
- L280 _public prototype_ `void DisplayPixel(const int32 IndexU, const int32 IndexV) const;`
- L282 _public prototype_ `void DisplayIsoNodes(EGridSpace Space) const;`
- L284 _public prototype_ `void DisplayLoops(const TCHAR* Message, bool bOneNode = true, bool bSplitBySegment = false) const;`
- L285 _public prototype_ `void DisplayLoopsByNextAndPrevious(const TCHAR* Message) const;`
- L287 _public prototype_ `void DisplayCells(const TArray<FCell>& Cells) const;`
- L288 _public prototype_ `void DisplayCell(const FCell& Cell) const;`
- L289 _public prototype_ `void DrawCellBoundary(int32 Index, EVisuProperty Property) const;`
- L291 _public prototype_ `void DisplayCellConnexion(const FCellConnexion& LoopConnexion, EVisuProperty Property) const;`
- L292 _public prototype_ `void DisplayCellConnexions(const FString& Message, const TArray<FCellConnexion>& LoopConnexions, EVisuProperty Property) const;`

#### struct `UE::CADKernel::IsoTriangulatorImpl::FPairOfDouble`  
`struct FPairOfDouble`  
_L353-357_
- L355 _public member_ `double Value1;`
- L356 _public member_ `double Value2;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CADKernel` (scope `UE`)
- L22 _typedef_ `using FMeshPolygonFunc = TFunction<void(const FGrid&, FIsoNode*[], FFaceMesh&)>;` (scope `UE::CADKernel`)
- L228 _function_ `` (scope `UE::CADKernel::FIsoTriangulator::SortLoopNodes`)
- L297 _namespace_ `namespace IsoTriangulatorImpl` (scope `UE::CADKernel`)
- L305 _function_ `inline double CotangentCriteria(const FVector& APoint, const FVector& BPoint, const FVector& PPoint, FVector& OutNormal)` (scope `UE::CADKernel::IsoTriangulatorImpl`) — Criteria to find the optimal "Delaunay" triangle starting from the segment AB to a set of point P A "Delaunay" triangle is an equilateral triangle The optimal value is the smallest value.
- L329 _function_ `inline double CotangentCriteria(const FVector2d& APoint, const FVector2d& BPoint, const FVector2d& PPoint)` (scope `UE::CADKernel::IsoTriangulatorImpl`)
- L359 _function_ `inline FPairOfDouble IsoscelesCriteria(const FVector2d& APoint, const FVector2d& BPoint, const FVector2d& CPoint)` (scope `UE::CADKernel::IsoTriangulatorImpl`)
- L369 _function_ `inline double IsoscelesCriteriaMax(const FVector2d& APoint, const FVector2d& BPoint, const FVector2d& CPoint)` (scope `UE::CADKernel::IsoTriangulatorImpl`)
- L375 _function_ `inline double IsoscelesCriteriaMin(const FVector2d& APoint, const FVector2d& BPoint, const FVector2d& CPoint)` (scope `UE::CADKernel::IsoTriangulatorImpl`)
- L381 _function_ `inline double EquilateralSlopeCriteria(const FVector2d& APoint, const FVector2d& BPoint, const FVector2d& CPoint)` (scope `UE::CADKernel::IsoTriangulatorImpl`)
- L398 _function_ `template<class PointType> inline double EquilateralCriteria(const PointType& SegmentA, const PointType& SegmentB, const PointType& Point)` (scope `UE::CADKernel::IsoTriangulatorImpl`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/IsoTriangulator/IntersectionIsoSegmentTool.h` (Private)


#### class `UE::CADKernel::IntersectionIsoSegmentTool::FIntersectionIsoSegment`  
`class FIntersectionIsoSegment`  
_L16-72_
- L19 _private member_ `const FVector2d& Point0;`
- L20 _private member_ `const FVector2d& Point1;`
- L21 _private member_ `double IsoCoordinate;`
- L22 _private member_ `double MinCoordinate;`
- L23 _private member_ `double MaxCoordinate;`
- L27 _public function_ `FIntersectionIsoSegment(const FVector2d& StartPoint, const FVector2d& EndPoint, const double InIsoCoordinate, const double InStartCoordinate, const double InEndCoordinate) : Point0(StartPoint) , Point1(EndPoint) , IsoCoordinate(InIsoCoordinate) , MinCoordinate(FMath::Min(InStartCoordinate, InEndCoordinate)) , MaxCoordinate(FMath::Max(InStartCoordinate, InEndCoordinate))`
- L35 _public function_ `virtual ~FIntersectionIsoSegment()`
- L38 _public prototype_ `virtual FVector2d GetMinPoint() const = 0;`
- L39 _public prototype_ `virtual FVector2d GetMaxPoint() const = 0;`
- L41 _public function_ `double GetIsoCoordinate() const`
- L46 _public function_ `double GetMinCoordinate() const`
- L51 _public function_ `double GetMaxCoordinate() const`
- L56 _public function_ `FSegment2D GetSegment2D() const`

#### class `UE::CADKernel::IntersectionIsoSegmentTool::FIsoUSegment`  
`class FIsoUSegment : public FIntersectionIsoSegment`  
_L74-89_
- inherits: `FIntersectionIsoSegment`
- L77 _public function_ `FIsoUSegment(const FVector2d& StartPoint, const FVector2d& EndPoint) : FIntersectionIsoSegment(StartPoint, EndPoint, StartPoint.X, StartPoint.Y, EndPoint.Y)`
- L81 _public function_ `virtual FVector2d GetMinPoint() const override`
- L85 _public function_ `virtual FVector2d GetMaxPoint() const override`

#### class `UE::CADKernel::IntersectionIsoSegmentTool::FIsoVSegment`  
`class FIsoVSegment : public FIntersectionIsoSegment`  
_L91-108_
- inherits: `FIntersectionIsoSegment`
- L94 _public function_ `FIsoVSegment(const FVector2d& StartPoint, const FVector2d& EndPoint) : FIntersectionIsoSegment(StartPoint, EndPoint, StartPoint.Y, StartPoint.X, EndPoint.X)`
- L98 _public function_ `virtual FVector2d GetMinPoint() const override`
- L103 _public function_ `virtual FVector2d GetMaxPoint() const override`

#### class `UE::CADKernel::FIntersectionIsoSegmentTool`  
`class FIntersectionIsoSegmentTool`  
_L112-143_
- L115 _private member_ `const FGrid& Grid;`
- L117 _private member_ `TArray<TPair<double, int32>> CoordToIndex[2];`
- L119 _private member_ `TArray<IntersectionIsoSegmentTool::FIsoUSegment> USegments;`
- L120 _private member_ `TArray<IntersectionIsoSegmentTool::FIsoVSegment> VSegments;`
- L122 _private member_ `bool bIsSorted = false;`
- L125 _public prototype_ `FIntersectionIsoSegmentTool(const FGrid& InGrid, const double Tolerance);`
- L127 _public prototype_ `void AddIsoSegment(const FVector2d& StartPoint, const FVector2d& EndPoint, const ESegmentType InType);`
- L129 _public prototype_ `bool DoesIntersect(const FIsoNode& StartNode, const FIsoNode& EndNode) const;`
- L131 _public prototype_ `int32 CountIntersections(const FIsoNode& StartNode, const FIsoNode& EndNode) const;`
- L133 _public prototype_ `void Sort();`
- L136 _private prototype_ `int32 GetStartIndex(EIso Iso, double Min) const;`
- L137 _private prototype_ `int32 GetStartIndex(EIso Iso, const FSurfacicBoundary& Boundary) const;`
- L141 _public prototype_ `void Display(bool bDisplay, const TCHAR* Message, EVisuProperty Property = EVisuProperty::BlueCurve) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)
- L13 _namespace_ `namespace IntersectionIsoSegmentTool` (scope `UE::CADKernel`)
- L61 _function_ `friend bool operator<(const FIntersectionIsoSegment& A, const FIntersectionIsoSegment& B)` (scope `UE::CADKernel::IntersectionIsoSegmentTool`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/IsoTriangulator/IntersectionSegmentTool.h` (Private)


#### enum `UE::CADKernel::EConnectionType`  
`enum class EConnectionType : uint8`  
_L15-21_
- L17 _public enumerator_ `DoesntStartFrom = 0`
- L18 _public enumerator_ `StartFrom`
- L19 _public enumerator_ `SuperimposedByOrOn`
- L20 _public enumerator_ `SameSegment`

#### struct `UE::CADKernel::IntersectionToolBase::FSegment`  
`struct FSegment`  
_L25-172_
- L27 _public member_ `const FSegment2D Segment2D;`
- L32 _public member_ `const FSurfacicBoundary Boundary;` — Segment's axis aligned bounding box
- L38 _public member_ `double AxisMin;` — Uses as criterion to sort segments to optimize AxisMin = Boundary[EIso::IsoU].Min + Boundary[EIso::IsoV].Min
- L39 _public member_ `double AxisMax;`
- L44 _public function_ `FSegment(const double Tolerance, const FVector2d& StartPoint, const FVector2d& EndPoint) : Segment2D(StartPoint, EndPoint) , Boundary(StartPoint, EndPoint, Tolerance)` — WARNING StartPoint, EndPoint must be defined in EGridSpace::UniformScaled
- L52 _public prototype_ `virtual ~FSegment() = default;`
- L54 _public prototype_ `virtual bool IsValid() const = 0;`
- L56 _public prototype_ `virtual const FIsoNode* GetFirstNode() const = 0;`
- L57 _public prototype_ `virtual const FIsoNode* GetSecondNode() const = 0;`
- L59 _public function_ `virtual const FIsoSegment* GetIsoSegment() const`
- L64 _public function_ `static EConnectionType IsSuperimposed(const FSegment2D& SegmentAB, const FSegment2D& SegmentCD, bool bSameOrientation)`
- L80 _public function_ `EConnectionType DoesItStartFromAndSuperimposed(const FIsoNode* StartNode, const FVector2d* EndPoint, const FSegment2D& InSegment) const`
- L96 _public function_ `EConnectionType DoesItStartFromAndSuperimposed(const FVector2d* StartPoint, const FVector2d* EndPoint, const FSegment2D& InSegment) const`
- L101 _public function_ `EConnectionType DoesItStartFromAndSuperimposed(const FIsoNode* StartNode, const FIsoNode* EndNode, const FSegment2D& InSegment) const`
- L134 _public function_ `bool IsFullyBefore(const FSegment& Segment) const`
- L139 _public function_ `bool IsFullyAfter(const FSegment& Segment) const`
- L144 _public function_ `bool CouldItIntersect(const FSurfacicBoundary& SegmentBoundary) const`
- L158 _public function_ `virtual bool DoesItIntersect(const FSegment& Segment) const`
- L168 _public function_ `bool IsParallelWith(const FSegment& Segment) const`

#### struct `UE::CADKernel::IntersectionSegmentTool::FSegment`  
`struct FSegment : public IntersectionToolBase::FSegment`  
_L178-201_
- inherits: `IntersectionToolBase::FSegment`
- L180 _public member_ `const FIsoSegment* IsoSegment;`
- L182 _public prototype_ `FSegment(const FGrid& Grid, const double Tolerance, const FIsoSegment& InSegment);`
- L183 _public prototype_ `FSegment(const FGrid& Grid, const double Tolerance, const FIsoNode& StartNode, const FIsoNode& EndNode);`
- L184 _public prototype_ `FSegment(const FGrid& Grid, const double Tolerance, const FIsoNode& StartNode, const FVector2d& EndPoint);`
- L185 _public function_ `FSegment(const FGrid& Grid, const double Tolerance, const FVector2d& StartPoint, const FVector2d& EndPoint) : IntersectionToolBase::FSegment(Tolerance, StartPoint, EndPoint) , IsoSegment(nullptr)`
- L191 _public prototype_ `virtual bool IsValid() const override;`
- L193 _public prototype_ `virtual const FIsoNode* GetFirstNode() const override;`
- L194 _public prototype_ `virtual const FIsoNode* GetSecondNode() const override;`
- L196 _public function_ `virtual const FIsoSegment* GetIsoSegment() const override`

#### class `UE::CADKernel::TIntersectionSegmentTool`  
`template<typename SegmentType> class TIntersectionSegmentTool`  
_L206-391_
- L209 _protected member_ `const FGrid& Grid;`
- L211 _protected member_ `TArray<SegmentType> Segments;`
- L212 _protected member_ `bool bSegmentsAreSorted;`
- L214 _protected member_ `const double Tolerance;`
- L217 _public function_ `TIntersectionSegmentTool(const FGrid& InGrid, const double InTolerance) : Grid(InGrid) , bSegmentsAreSorted(false) , Tolerance(InTolerance)`
- L224 _public prototype_ `virtual ~TIntersectionSegmentTool() = default;`
- L226 _public function_ `void Empty(int32 InMaxNum)`
- L232 _public function_ `void Reserve(int32 InMaxNum)`
- L237 _public function_ `void RemoveLast()`
- L244 _public function_ `void SetCount(int32 NewCount)`
- L250 _public function_ `int32 Count()`
- L258 _public function_ `void Sort()` — segments are sorted by DMin increasing
- L265 _public function_ `template<typename ExtremityType1, typename ExtremityType2> const SegmentType* FindIntersectingSegment(const ExtremityType1* StartExtremity, const ExtremityType2* EndExtremity) const`
- L312 _public function_ `template<typename ExtremityType1, typename ExtremityType2> int32 FindIntersectingSegments(const ExtremityType1* StartExtremity, const ExtremityType2* EndExtremity, TArray<const FIsoSegment*>* OutIntersectedSegments) const`
- L374 _public function_ `virtual void Display(bool bDisplay, const TCHAR* Message, EVisuProperty Property = EVisuProperty::BlueCurve) const`

#### class `UE::CADKernel::FIntersectionSegmentTool`  
`class FIntersectionSegmentTool : public TIntersectionSegmentTool<IntersectionSegmentTool::FSegment>`  
_L393-541_
- inherits: `TIntersectionSegmentTool<IntersectionSegmentTool::FSegment>`
- L396 _public function_ `FIntersectionSegmentTool(const FGrid& InGrid, const double Tolerance) : TIntersectionSegmentTool<IntersectionSegmentTool::FSegment>(InGrid, Tolerance)`
- L401 _public function_ `bool Update(const FIsoSegment* Segment)`
- L418 _public function_ `void AddSegments(FIsoSegment** InNewSegments, int32 Count)`
- L429 _public function_ `void AddSegments(const TArray<FIsoSegment*>& InNewSegments)`
- L439 _public function_ `void AddSegment(const FIsoSegment& Segment)`
- L445 _public function_ `void AddSegment(const FVector2d& StartPoint, const FVector2d& EndPoint)`
- L454 _public function_ `bool Remove(const FIsoSegment* Segment)` — @return true if the segment is found and removed
- L469 _public prototype_ `const FIsoSegment* FindIntersectingSegment(const FIsoSegment& Segment) const;`
- L470 _public prototype_ `FIsoSegment* FindIntersectingSegment(const FIsoSegment& Segment);`
- L472 _public function_ `bool DoesIntersect(const FIsoSegment& Segment) const`
- L480 _public function_ `bool DoesIntersect(const FVector2d& StartPoint, const FVector2d& EndPoint) const` — WARNING StartPoint, EndPoint must be defined in EGridSpace::UniformScaled
- L489 _public function_ `bool DoesIntersect(const FIsoNode& StartNode, const FVector2d& EndPoint) const` — Allow StartNode to be connected to one segment WARNING EndPoint must be defined in EGridSpace::UniformScaled
- L494 _public function_ `bool DoesIntersect(const FIsoNode* StartNode, const FIsoNode* EndNode) const`
- L499 _public function_ `bool DoesIntersect(const FIsoNode& StartNode, const FIsoNode& EndNode) const`
- L507 _public function_ `const FIsoSegment* FindIntersectingSegment(const FIsoNode& StartNode, const FIsoNode& EndNode) const` — Allow StartNode and EndNode to be connected to one segment
- L517 _public function_ `const FIsoSegment* FindIntersectingSegment(const FIsoNode* StartNode, const FIsoNode* EndNode) const`
- L527 _public function_ `bool FindIntersectingSegments(const FIsoNode* StartNode, const FIsoNode* EndNode, TArray<const FIsoSegment*>& OutIntersections) const`
- L532 _public function_ `bool FindIntersectingSegments(const FIsoNode& StartNode, const FIsoNode& EndNode, TArray<const FIsoSegment*>& OutIntersections) const`
- L537 _public function_ `int32 CountIntersections(const FIsoNode* StartNode, const FIsoNode* EndNode) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)
- L23 _namespace_ `namespace IntersectionToolBase` (scope `UE::CADKernel`)
- L175 _namespace_ `namespace IntersectionSegmentTool` (scope `UE::CADKernel`)
- L260 _function_ `Algo::Sort(Segments, [](const SegmentType& Segment1, const SegmentType& Segment2) { return Segment1.AxisMin < Segment2.AxisMin; });` (scope `UE::CADKernel::TIntersectionSegmentTool::Sort`)
- L404 _function_ `` (scope `UE::CADKernel::FIntersectionSegmentTool::Update`)
- L457 _function_ `` (scope `UE::CADKernel::FIntersectionSegmentTool::Remove`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/IsoTriangulator/IsoCell.h` (Private)


#### struct `UE::CADKernel::FCellLoop`  
`struct FCellLoop`  
_L20-61_
- L22 _public member_ `int32 Id;`
- L23 _public member_ `FVector2d Barycenter;`
- L24 _public member_ `TArray<FLoopNode*> Nodes;`
- L25 _public member_ `TArray<FCellConnexion*> Connexions;`
- L26 _public member_ `bool bIsOuterLoop = false;`
- L27 _public member_ `bool bIsConnected = false;`
- L29 _public function_ `FCellLoop(const int32 InIndex, TArray<FLoopNode*>& InNodes, const FGrid& Grid) : Id(InIndex) , Barycenter(FVector2d::ZeroVector) , Nodes(InNodes) , bIsOuterLoop(Nodes[0]->GetLoopIndex() == 0)`
- L42 _public function_ `FCellLoop(const int32 InIndex) : Id(InIndex) , Barycenter(FVector::ZeroVector)`
- L48 _public prototype_ `virtual ~FCellLoop() = default;`
- L50 _public function_ `virtual bool IsCellCorner() const`
- L55 _public function_ `virtual bool IsCellCornerOrOuterLoop() const`
- L60 _public prototype_ `void PropagateAsConnected();`

#### struct `UE::CADKernel::FCellCorner`  
`struct FCellCorner : public FCellLoop`  
_L63-84_
- inherits: `FCellLoop`
- L65 _public member_ `FIsoInnerNode& CornerNode;`
- L67 _public function_ `FCellCorner(const int32 InIndex, FIsoInnerNode& InNode, const FGrid& Grid) : FCellLoop(InIndex) , CornerNode(InNode)`
- L74 _public function_ `virtual bool IsCellCorner() const override`
- L79 _public function_ `virtual bool IsCellCornerOrOuterLoop() const`

#### struct `UE::CADKernel::FCellConnexion`  
`struct FCellConnexion`  
_L86-328_
- L88 _public member_ `bool bIsConnexionWithOuter = false;`
- L89 _public member_ `FCellLoop& Loop1;`
- L90 _public member_ `FCellLoop& Loop2;`
- L92 _public member_ `double MinDistance = HUGE_VALUE_SQUARE;`
- L94 _public member_ `FLoopNode* NodeA = nullptr;`
- L95 _public member_ `FIsoNode* NodeB = nullptr;`
- L97 _public member_ `FIsoSegment* Segment = nullptr;`
- L99 _public function_ `FCellConnexion(FCellLoop& InLoop1, FCellLoop& InLoop2) : Loop1(InLoop1) , Loop2(InLoop2)`
- L108 _public function_ `const FCellLoop* GetOtherLoop(const FCellLoop* Loop) const`
- L113 _public function_ `FCellLoop* GetOtherLoop(const FCellLoop* Loop)`
- L118 _public function_ `bool IsShortestPath(const int32 MaxLoopCount)`
- L187 _public function_ `bool IsShortestPathToOuterLoop(const int32 MaxLoopCount)`
- L258 _public function_ `bool IsShortestPathToCorner(const int32 MaxLoopCount)`

#### struct `UE::CADKernel::FCellPath`  
`struct FCellPath`  
_L330-335_
- L332 _public member_ `double Length = 0;`
- L333 _public member_ `FCellLoop* CurrentLoop;`
- L334 _public member_ `TArray<FCellLoop> Path;`

#### struct `UE::CADKernel::FCell`  
`struct FCell`  
_L337-506_
- L339 _public member_ `FIsoTriangulator& Triangulator;`
- L340 _public member_ `const FGrid& Grid;`
- L341 _public member_ `int32 Id;`
- L343 _public member_ `int32 InnerLoopCount = 0;`
- L344 _public member_ `int32 OuterLoopCount = 0;`
- L346 _public member_ `TArray<FIsoSegment*> CandidateSegments;`
- L347 _public member_ `TArray<FIsoSegment*> FinalSegments;`
- L349 _public member_ `FIntersectionSegmentTool IntersectionTool;`
- L351 _public member_ `TArray<FCellLoop> CellLoops;`
- L352 _public member_ `TArray<FCellCorner> CellCorners;`
- L353 _public member_ `TArray<FCellConnexion> LoopConnexions;`
- L354 _public member_ `TArray<int32> LoopCellBorderIndices;`
- L356 _public function_ `FCell(const int32 InLoopIndex, TArray<FLoopNode*>& InNodes, FIsoTriangulator& InTriangulator) : Triangulator(InTriangulator) , Grid(Triangulator.GetGrid()) , Id(InLoopIndex) , IntersectionTool(Triangulator.GetGrid(), Triangulator.Tolerances.GeometricTolerance)`
- L466 _public prototype_ `void InitLoopConnexions();`
- L468 _public function_ `TArray<TPair<int32, FVector2d>> GetLoopBarycenters()`
- L482 _public prototype_ `void FindCandidateToConnectLoopsByNeighborhood();`
- L483 _public prototype_ `void FindCandidateToConnectCellCornerToLoops();`
- L485 _public prototype_ `void SelectSegmentToConnectLoops(TFactory<FIsoSegment>& SegmentFactory);`
- L486 _public prototype_ `void SelectSegmentToConnectLoopToCorner(TFactory<FIsoSegment>& SegmentFactory);`
- L487 _public prototype_ `void CheckAllLoopsConnectedTogetherAndConnect();`
- L503 _public prototype_ `void TryToConnectTwoSubLoopsWithShortestSegment(FCellConnexion& LoopConnexion);` — SubLoopA                  SubLoopB --X---X             X-----X-- \           / \         / X=======X /         \ /           \ --X---X             X-----X-- ======= ShortestSegment
- L505 _public prototype_ `void TryToCreateSegment(FCellConnexion& LoopConnexion);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CADKernel` (scope `UE`)
- L367 _function_ `` (scope `UE::CADKernel::FCell::FCell`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/IsoTriangulator/IsoNode.h` (Private)


#### enum `UE::CADKernel::EIsoLink`  
`enum class EIsoLink : uint8`  
_L14-20_
- L16 _public enumerator_ `IsoUNext = 0`
- L17 _public enumerator_ `IsoVNext = 1`
- L18 _public enumerator_ `IsoUPrevious = 2`
- L19 _public enumerator_ `IsoVPrevious = 3`

#### enum `UE::CADKernel::EIsoNodeStates`  
`enum class EIsoNodeStates : uint16`  
_L22-51_
- L24 _public enumerator_ `None = 0x0000u` — No flags.
- L26 _public enumerator_ `LinkedToPreviousU = 0x0001u`
- L27 _public enumerator_ `LinkedToNextU = 0x0002u`
- L28 _public enumerator_ `LinkedToPreviousV = 0x0004u`
- L29 _public enumerator_ `LinkedToNextV = 0x0008u`
- L31 _public enumerator_ `NodeComplete = 0x000Fu`
- L33 _public enumerator_ `LinkedToLoop = 0x0010u`
- L34 _public enumerator_ `InnerMeshLoop = 0x0020u`
- L35 _public enumerator_ `ThinZoneNode = 0x0040u`
- L37 _public enumerator_ `Delete = 0x0080u`
- L39 _public enumerator_ `FirstQuarter = 0x0100u`
- L40 _public enumerator_ `SecondQuarter = 0x0200u`
- L41 _public enumerator_ `ThirdQuarter = 0x0400u`
- L42 _public enumerator_ `FourthQuarter = 0x0800u`
- L44 _public enumerator_ `NearlyIsoU = 0x1000u` — Loop nodes
- L45 _public enumerator_ `NearlyIsoV = 0x2000u` — Loop nodes
- L47 _public enumerator_ `HasMarker1 = 0x4000u`
- L48 _public enumerator_ `HasMarker2 = 0x8000u`
- L50 _public enumerator_ `All = 0xFFFFu`

#### class `UE::CADKernel::FIsoNode`  
`class FIsoNode`  
_L61-279_
- desc: Inner Node of the TopologicalFace, these nodes are IsoNodes as they are build according to the TopologicalFace iso cutting coordinates UV
- L64 _protected member_ `TArray<FIsoSegment*> ConnectedSegments;`
- L65 _protected member_ `EIsoNodeStates States;`
- L67 _protected member_ `int32 LocalIndex;` — Index of the node either in loop nodes either in inner nodes
- L68 _protected member_ `int32 GlobalIndex;` — Index of the node in the face
- L69 _protected member_ `int32 NodeId;` — Id of the node in the mesh
- L72 _public function_ `FIsoNode(int32 InNodeIndex, int32 InFaceIndex, int32 InNodeId) : ConnectedSegments() , States(EIsoNodeStates::None) , LocalIndex(InNodeIndex) , GlobalIndex(InFaceIndex) , NodeId(InNodeId)`
- L82 _public prototype_ `virtual ~FIsoNode() = default;`
- L84 _public function_ `virtual void Delete()`
- L92 _public function_ `bool IsDelete() const`
- L97 _public function_ `const int32 GetIndex() const`
- L102 _public function_ `const int32 GetGlobalIndex() const`
- L107 _public function_ `const int32 GetNodeId() const`
- L112 _public function_ `const TArray<FIsoSegment*>& GetConnectedSegments() const`
- L117 _public prototype_ `FIsoSegment* GetSegmentConnectedTo(const FIsoNode* Node) const;`
- L119 _public function_ `void ConnectSegment(FIsoSegment& Segment)`
- L124 _public function_ `void DisconnectSegment(FIsoSegment& Segment)`
- L129 _public prototype_ `const virtual bool IsALoopNode() const = 0;`
- L131 _public function_ `void SetThinZoneNodeMarker()`
- L136 _public function_ `bool IsThinZoneNode() const`
- L141 _public function_ `bool IsDeleteOrThinNode() const`
- L147 _public function_ `void SetLinkedToLoopMarker()`
- L152 _public function_ `void SetLinkedToLoopInQuarter(int32 Quarter)`
- L167 _public function_ `bool IsLinkedToLoopInNearlyIso(int32 Iso) const`
- L186 _public function_ `void SetLinkedToIso(EIsoLink Iso)` — [3Pi/2 2Pi]
- L204 _public function_ `void SetLinkedToIso(int32 Iso)` — [3Pi/2 2Pi]
- L226 _public function_ `bool HasMarker1() const`
- L231 _public function_ `bool HasMarker2() const`
- L236 _public function_ `bool IsDeleteOrHasMarker2() const`
- L242 _public function_ `bool HasMarker1NotMarker2() const`
- L248 _public function_ `void SetMarker1()`
- L253 _public function_ `void SetMarker2()`
- L258 _public function_ `void ResetMarkers()`
- L267 _public prototype_ `virtual const FVector2d& Get2DPoint(EGridSpace Space, const FGrid& Grid) const = 0;` — Return the 2d coordinate of the node according to the space
- L268 _public prototype_ `virtual void Set2DPoint(EGridSpace Space, FGrid& Grid, const FVector2d& NewCoordinate) = 0;`
- L270 _public prototype_ `virtual const FVector& Get3DPoint(const FGrid& Grid) const = 0;`
- L271 _public prototype_ `virtual const FVector3f& GetNormal(const FGrid& Grid) const = 0;`
- L273 _public prototype_ `virtual bool operator==(const FIsoNode& OtherNode) const = 0;`
- L274 _public prototype_ `virtual bool IsEqualTo(const FLoopNode& OtherNode) const = 0;`
- L275 _public prototype_ `virtual bool IsEqualTo(const FIsoInnerNode& OtherNode) const = 0;`
- L277 _public prototype_ `virtual uint32 GetTypeHash() const = 0;`

#### class `UE::CADKernel::FLoopNode`  
`class FLoopNode : public FIsoNode`  
_L284-434_
- inherits: `FIsoNode`
- desc: Node of the loop of the TopologicalFace
- L287 _protected member_ `int32 LoopIndex;`
- L288 _protected member_ `FLoopNode* ConnectedLoopNodes[2];`
- L291 _public function_ `FLoopNode(int32 InLoopIndex, int32 InNodeLoopIndex, int32 InNodeFaceIndex, int32 NodeId) : FIsoNode(InNodeLoopIndex, InNodeFaceIndex, NodeId) , LoopIndex(InLoopIndex) , ConnectedLoopNodes`
- L298 _public function_ `virtual void Delete() override`
- L307 _public function_ `virtual bool IsEqualTo(const FLoopNode& OtherNode) const`
- L312 _public function_ `virtual bool IsEqualTo(const FIsoInnerNode& OtherNode) const`
- L317 _public function_ `bool operator==(const FIsoNode& OtherNode) const`
- L322 _public function_ `virtual const bool IsALoopNode() const override`
- L327 _public function_ `const int32 GetLoopIndex() const`
- L332 _public function_ `void SetNextConnectedNode(FLoopNode* NextNode)`
- L336 _public function_ `void SetPreviousConnectedNode(FLoopNode* PreviousNode)`
- L341 _public function_ `FLoopNode& GetPreviousNode() const`
- L346 _public function_ `FLoopNode& GetNextNode() const`
- L351 _public function_ `FIsoSegment& GetPreviousSegment() const`
- L356 _public function_ `FIsoSegment& GetNextSegment() const`
- L364 _public function_ `virtual const FVector2d& Get2DPoint(EGridSpace Space, const FGrid& Grid) const override` — Return the 2d coordinate of the node according to the space
- L369 _public function_ `virtual void Set2DPoint(EGridSpace Space, FGrid& Grid, const FVector2d& NewCoordinate) override`
- L374 _public function_ `virtual const FVector& Get3DPoint(const FGrid& Grid) const override`
- L379 _public function_ `virtual const FVector3f& GetNormal(const FGrid& Grid) const override`
- L425 _public function_ `bool IsSegmentBeInsideFace(const FVector2d& EndSegmentCoordinate, const FGrid& Grid, const double FlatAngle) const` — Check if the segment starting from this loop node (S) to EndSegmentCoordinate (E) is inside the face Warning, inner loops (loop index > 0) are not in the same orientation than outer loop Inside e.g.: X---------------X----------------X        X------------------X-----------X |                                |        |                              | |         X-----------------X    |        |            X-------------X   | |         |                 |    |        |            |             |   | X   E-----S                 |    |    or  S---------E  |             |   | |         |                 |    |        |            |             |   | |         X-----------------X    |        |            X-------------X   | |                                |        |                              | X---------------X----------------X        X------------------X-----------X Outside e.g.: X---------------X----------------X        X------------------X-----------X |                                |        |                              | |         X-----------------X    |        |            X-------------X   | |         |                 |    |        |            |             |   | |         S------E          |    |    or  |            |             |   S------E |         |                 |    |        |            |             |   | |         X-----------------X    |        |            X-------------X   | |                                |        |                              | X---
- L430 _public function_ `virtual uint32 GetTypeHash() const override`

#### class `UE::CADKernel::FIsoInnerNode`  
`class FIsoInnerNode : public FIsoNode`  
_L441-549_
- inherits: `FIsoNode`
- L444 _public function_ `FIsoInnerNode(int32 NodeIndex, int32 FaceIndex, int32 NodeId) : FIsoNode(NodeIndex, FaceIndex, NodeId)`
- L449 _public function_ `virtual bool IsEqualTo(const FLoopNode& OtherNode) const`
- L454 _public function_ `virtual bool IsEqualTo(const FIsoInnerNode& OtherNode) const`
- L459 _public function_ `bool operator==(const FIsoNode& OtherNode) const`
- L464 _public function_ `const bool IsIsolated() const`
- L469 _public function_ `virtual const bool IsALoopNode() const override`
- L474 _public function_ `bool IsLinkedToPreviousU() const`
- L479 _public function_ `bool IsLinkedToNextU() const`
- L484 _public function_ `bool IsLinkedToPreviousV() const`
- L489 _public function_ `bool IsLinkedToNextV() const`
- L495 _public function_ `bool IsComplete() const` — the node is connected in its 4 directions
- L500 _public function_ `bool IsLinkedToBoundary() const`
- L505 _public function_ `virtual const FVector2d& Get2DPoint(EGridSpace Space, const FGrid& Grid) const override`
- L510 _public function_ `virtual void Set2DPoint(EGridSpace Space, FGrid& Grid, const FVector2d& NewCoordinate) override`
- L515 _public function_ `virtual const FVector& Get3DPoint(const FGrid& Grid) const override`
- L520 _public function_ `virtual const FVector3f& GetNormal(const FGrid& Grid) const override`
- L540 _public function_ `void OffsetId(int32 StartId)`
- L545 _public function_ `virtual uint32 GetTypeHash() const override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)
- L53 _prototype_ `ENUM_CLASS_FLAGS(EIsoNodeStates);` (scope `UE::CADKernel`)
- L436 _function_ `inline uint32 GetTypeHash(const FIsoNode& Node)` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/IsoTriangulator/IsoSegment.h` (Private)


#### enum `UE::CADKernel::ESegmentType`  
`enum class ESegmentType : uint8`  
_L10-22_
- L12 _public enumerator_ `Unknown = 0`
- L13 _public enumerator_ `Loop = 1`
- L14 _public enumerator_ `ThinZone = 2`
- L15 _public enumerator_ `IsoU`
- L16 _public enumerator_ `IsoV`
- L17 _public enumerator_ `LoopToLoop` — IsBoundaryToInner use that xxxToBoundary are bigger than BoundaryToBoundary
- L18 _public enumerator_ `IsoLoopToLoop`
- L19 _public enumerator_ `InnerToLoopU`
- L20 _public enumerator_ `InnerToLoopV`
- L21 _public enumerator_ `InnerToLoop`

#### enum `UE::CADKernel::EIsoSegmentStates`  
`enum class EIsoSegmentStates : uint8`  
_L24-43_
- L26 _public enumerator_ `None = 0x00u` — No flags.
- L28 _public enumerator_ `Candidate = 0x01u`
- L30 _public enumerator_ `LeftCycle = 0x02u`
- L31 _public enumerator_ `RightCycle = 0x04u`
- L33 _public enumerator_ `Degenerate = 0x08u`
- L35 _public enumerator_ `LeftTriangle = 0x10u`
- L36 _public enumerator_ `RightTriangle = 0x20u`
- L37 _public enumerator_ `SegmentComplete = 0x30u`
- L39 _public enumerator_ `Final = 0x40u`
- L40 _public enumerator_ `Delete = 0x80u`
- L42 _public enumerator_ `All = 0xFFu`

#### class `UE::CADKernel::FIsoSegment`  
`class FIsoSegment`  
_L50-344_
- L53 _protected member_ `FIsoNode* FirstNode;`
- L54 _protected member_ `FIsoNode* SecondNode;`
- L55 _protected member_ `ESegmentType Type;`
- L56 _protected member_ `EIsoSegmentStates States;`
- L60 _public function_ `FIsoSegment() : FirstNode(nullptr) , SecondNode(nullptr) , Type(ESegmentType::Unknown) , States(EIsoSegmentStates::None)`
- L68 _public function_ `void Init(FIsoNode& InFirstNode, FIsoNode& InSecondNode, const ESegmentType InType)`
- L88 _public function_ `bool ConnectToNode()`
- L100 _public function_ `static bool IsItAlreadyDefined(const FIsoNode* StartNode, const FIsoNode* EndNode)`
- L113 _public function_ `void Clean()`
- L128 _public function_ `bool IsDelete() const`
- L133 _public function_ `void SetSelected()`
- L138 _public function_ `void SetCandidate()`
- L143 _public function_ `bool IsACandidate() const`
- L148 _public function_ `void SetFinalMarker()`
- L153 _public function_ `bool IsAFinalSegment() const`
- L158 _public function_ `bool HasCycleOnLeft()`
- L163 _public function_ `void SetHaveCycleOnLeft()`
- L168 _public function_ `bool HasCycleOnRight()`
- L173 _public function_ `void SetHaveCycleOnRight()`
- L178 _public function_ `bool HasTriangleOn(EIsoSegmentStates Side)`
- L183 _public function_ `bool HasTriangleOnLeft()`
- L188 _public function_ `bool HasTriangleOnRight()`
- L193 _public function_ `bool HasntTriangle()`
- L199 _public function_ `bool HasTriangleOnRightAndLeft()`
- L205 _public function_ `void SetHasTriangleOn(EIsoSegmentStates Side)`
- L210 _public function_ `void SetHasTriangleOnLeft()`
- L215 _public function_ `void SetHasTriangleOnRight()`
- L220 _public function_ `void SetHasInnerTriangle(bool bOrientation)`
- L232 _public function_ `void ResetHasTriangle()`
- L237 _public function_ `void SetAsDegenerated()`
- L242 _public function_ `void ResetDegenerated()`
- L247 _public function_ `bool IsDegenerated() const`
- L252 _public function_ `bool IsFirstNode(const FIsoNode* Node) const`
- L257 _public function_ `const FIsoNode& GetFirstNode() const`
- L262 _public function_ `FIsoNode& GetFirstNode()`
- L267 _public function_ `const FIsoNode& GetSecondNode() const`
- L272 _public function_ `FIsoNode& GetSecondNode()`
- L277 _public function_ `void SetFirstNode(FIsoNode& NewNode)`
- L285 _public function_ `void SetSecondNode(FIsoNode& NewNode)`
- L293 _public function_ `void ReplaceNode(FIsoNode& OldNode, FIsoNode& NewNode)`
- L306 _public function_ `void SwapOrientation()`
- L316 _public function_ `const FIsoNode& GetOtherNode(const FIsoNode* Node) const`
- L321 _public function_ `FIsoNode& GetOtherNode(const FIsoNode* Node)`
- L326 _public function_ `const ESegmentType GetType() const`
- L331 _public function_ `double Get2DLengthSquare(EGridSpace Space, const FGrid& Grid) const`
- L338 _public function_ `double Get3DLengthSquare(const FGrid& Grid) const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)
- L45 _prototype_ `ENUM_CLASS_FLAGS(EIsoSegmentStates);` (scope `UE::CADKernel`)
- L346 _function_ `inline uint32 GetTypeHash(const FIsoSegment& Segment)` (scope `UE::CADKernel`)
- L360 _function_ `inline uint32 GetTypeHash(const FIsoSegment& Segment0, const FIsoSegment& Segment1)` (scope `UE::CADKernel`)
- L375 _function_ `inline FIsoSegment* FIsoNode::GetSegmentConnectedTo(const FIsoNode* Node) const` (scope `UE::CADKernel::FIsoNode`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/MesherTools.h` (Private)


#### class `UE::CADKernel::FMesherTools`  
`class FMesherTools`  
_L15-70_
- L34 _public prototype_ `static void ComputeFinalCuttingPointsWithPreferredCuttingPoints(const TArray<double>& CrossingUs, TArray<double> DeltaUs, const TArray<FCuttingPoint>& PreferredCuttingPoints, const FLinearBoundary& Boundary, TArray<double>& OutCuttingPoints);` — The purpose of this method is to compute the cutting of a face or an edge by preferring as soon as possible the suggested cuttings. In input a set of coordinate (CrossingUs) and the DeltaU between each coordinate (DeltaUs) which makes it possible to respect the mesh criteria. By analogy with a travel: - the target time between each cutting points is one - the speed of the travel at a point p(u) is DeltaUs(u) Step 1: Compute the number of mesh nodes i.e. compute the time of the travel between Boundary.Min and Boundary.Max with the initial speeds DeltaUs Step 2: Define the number of step (each step lasts one) as it must be an integer bigger than 1 Step 3: Adjust the speeds than the travel respect the count of step Step 4: Define the steps (if a preferred step is near the next step, the preferred step is used) Mandatory: PreferredCuttingPoints.Last() == UMax,
- L51 _public prototype_ `static void ComputeFinalCuttingPointsWithImposedCuttingPoints(const TArray<double>& CrossingUs, const TArray<double>& DeltaUs, const TArray<FCuttingPoint>& ImposedCuttingPoints, TArray<double>& OutCuttingPoints);` — The purpose of this method is to compute the cutting of a face or an edge by using the imposed cuttings. In input a set of coordinate (CrossingUs) and the DeltaU between each coordinate (DeltaUs) which makes it possible to respect the mesh criteria. By analogy with a travel: - the target time between each cutting points is one - the speed of the travel at a point p(u) is DeltaUs(u) Between each imposed cutting points Step 1: Define the number of step (each step lasts one) as it must be an integer bigger than 1 Step 2: Adjust the speeds than the travel respect the count of step Step 3: Compute the steps until the next imposed point Mandatory: ImposedCuttingPoints[0] == UMin && ImposedCuttingPoints.Last() == UMax,
- L56 _public function_ `static void FillCuttingPointCoordinates(const FLinearBoundary& Boundary, int32 PointCount, TArray<double>& OutCuttingPointCoordinates)` — Fill an array of CuttingPointCoordinates with "PointCount" coordinates evenly divided between the extremities of the boundary
- L69 _public prototype_ `static void FillImposedIsoCuttingPoints(TArray<double>& UEdgeSetOfIntersectionWithIso, ECoordinateType CoordinateType, double EdgeToleranceGeo, const FTopologicalEdge& Edge, TArray<FCuttingPoint>& OutImposedIsoVertexSet);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/ParametricFaceMesher.h` (Private)


#### struct `UE::CADKernel::ParametricMesherTool::FCrossZoneElement`  
`struct FCrossZoneElement`  
_L21-67_
- L23 _public member_ `const int32 VertexId;`
- L24 _public member_ `FVector2d VertexPoint2D;`
- L25 _public member_ `const double Tolerance3D;`
- L26 _public member_ `const FEdgeSegment* Segment;`
- L27 _public member_ `FPairOfIndex OppositeVertexIndices;`
- L29 _public member_ `FVector2d OppositePoint2D;`
- L30 _public member_ `FEdgeSegment* OppositeSegment;`
- L31 _public member_ `double OppositePointCoordinate = -1.;`
- L33 _public member_ `double SquareThickness;`
- L35 _public member_ `bool bIsSelected = false;`
- L37 _public function_ `FCrossZoneElement(const int32 InVertexId, const FVector2d InPoint2D, const double InTolerance3D, const FEdgeSegment* InSegment, const FPairOfIndex& InOppositeVertexIndices) : VertexId(InVertexId) , VertexPoint2D(InPoint2D) , Tolerance3D(InTolerance3D) , Segment(InSegment) , OppositeVertexIndices(InOppositeVertexIndices) , OppositePoint2D(FVector2d::ZeroVector) , OppositeSegment(nullptr) , OppositePointCoordinate(-1.) , SquareThickness(-1.)`
- L50 _public function_ `FCrossZoneElement() : VertexId(-1) , VertexPoint2D(FVector2d::ZeroVector) , Tolerance3D(-1.) , Segment(nullptr) , OppositeVertexIndices(FPairOfIndex::Undefined) , OppositePoint2D(FVector2d::ZeroVector) , OppositeSegment(nullptr) , OppositePointCoordinate(-1.) , SquareThickness(-1.)`
- L63 _public function_ `void Add(const FPairOfIndex& VertexIndices)`

#### class `UE::CADKernel::ParametricMesherTool::FIntersectionTool`  
`class FIntersectionTool`  
_L70-130_
- L73 _private member_ `const TArray<FEdgeSegment>& Side1Segments;`
- L74 _private member_ `const TArray<FEdgeSegment>& Side2Segments;`
- L75 _private member_ `TArray<FCrossZoneElement*> SelectedCrossZoneElement;`
- L79 _public function_ `FIntersectionTool(const TArray<FEdgeSegment>& InSide1Segments, const TArray<FEdgeSegment>& InSide2Segments, int32 MaxCrossZoneElementCount) : Side1Segments(InSide1Segments) , Side2Segments(InSide2Segments)`
- L86 _public function_ `bool IsIntersectSides(const FCrossZoneElement& CrossZoneElement)`
- L96 _public function_ `void AddCrossZoneElement(FCrossZoneElement& Element)`
- L103 _private function_ `bool IsIntersectSide(const TArray<FEdgeSegment>& Segments, const FSegment2D& CrossZoneSegment)`
- L117 _private function_ `bool IsIntersectCrossZoneElement(const FSegment2D& CrossZoneSegment)`

#### class `UE::CADKernel::FParametricFaceMesher`  
`class FParametricFaceMesher`  
_L134-197_
- L137 _protected member_ `FTopologicalFace& Face;`
- L138 _protected member_ `FModelMesh& MeshModel;`
- L140 _protected member_ `const FMeshingTolerances& Tolerances;`
- L141 _protected member_ `bool bThinZoneMeshing = false;`
- L143 _protected member_ `FGrid Grid;`
- L147 _public prototype_ `FParametricFaceMesher(FTopologicalFace& Face, FModelMesh& InMeshModel, const FMeshingTolerances& InTolerances, bool bActivateThinZoneMeshing);`
- L149 _public prototype_ `void Mesh();`
- L153 _private prototype_ `void Mesh(FTopologicalEdge& InEdge, bool bFinalMeshing = true);`
- L154 _private prototype_ `void Mesh(FTopologicalVertex& Vertex);`
- L155 _private prototype_ `void MeshVerticesOfFace(FTopologicalFace& Face);`
- L156 _private prototype_ `bool MeshPlanarFace();`
- L158 _private prototype_ `void MeshFaceLoops();`
- L161 _private prototype_ `void ApplyEdgeCriteria(FTopologicalEdge& Edge);`
- L166 _private prototype_ `bool GenerateCloud();` — @return false if the process fails i.e. the grid is degenerated or else.
- L169 _private member_ `TArray<FThinZone2D*> WaitingThinZones;` — Thin zone meshing data / context  =================================================================
- L171 _private member_ `TArray<FTopologicalEdge*> ZoneAEdges;`
- L172 _private member_ `TArray<FTopologicalEdge*> ZoneBEdges;`
- L178 _private prototype_ `void MeshThinZones();` — Main methode
- L179 _private prototype_ `void MeshThinZones(TArray<FThinZone2D*>& ThinZones);`
- L185 _private prototype_ `void SortThinZoneSides(TArray<FThinZone2D*>& ThinZones);` — Check that in one edge with further thin zones, the edge is for all zone in the same side otherwise, fix it Zone with conflicts will be saved in a waiting list
- L187 _private prototype_ `void MeshThinZones(TArray<FTopologicalEdge*>& EdgesToMesh, const bool bFinalMeshing);`
- L189 _private prototype_ `void MeshThinZoneSide(FThinZoneSide& Side, bool bFinalMeshing);`
- L190 _private prototype_ `void DefineImposedCuttingPointsBasedOnOtherSideMesh(FThinZoneSide& SideToConstrain);`
- L193 _private prototype_ `void DisplayMeshOfFaceLoop();`
- L194 _private prototype_ `void DisplayThinZoneEdges(const TCHAR* Text, TArray<FTopologicalEdge*>& Edges, EVisuProperty Color, EVisuProperty Color2);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)
- L18 _namespace_ `namespace ParametricMesherTool` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/ParametricMesher.h` (Private)


#### struct `UE::CADKernel::ParametricMesherTool::FCostToFace`  
`struct FCostToFace`  
_L23-33_
- L25 _public member_ `double Cost;`
- L26 _public member_ `FTopologicalFace* Face;`
- L28 _public function_ `FCostToFace(double NewCost, FTopologicalFace* NewFace) : Cost(NewCost) , Face(NewFace)`

#### class `UE::CADKernel::FParametricMesher`  
`class FParametricMesher`  
_L40-110_
- L44 _protected member_ `FMeshingTolerances Tolerances;`
- L45 _protected member_ `bool bThinZoneMeshing = false;`
- L47 _protected member_ `FModelMesh& MeshModel;`
- L49 _protected member_ `TArray<FTopologicalFace*> Faces;`
- L52 _protected member_ `bool bDisplay = false;`
- L57 _public prototype_ `FParametricMesher(FModelMesh& InMeshModel, double GeometricTolerance, bool bActivateThinZoneMeshing);`
- L59 _public function_ `const FModelMesh& GetMeshModel() const`
- L64 _public function_ `FModelMesh& GetMeshModel()`
- L69 _public prototype_ `void MeshEntities(TArray<FTopologicalShapeEntity*>& InEntities);`
- L71 _public function_ `void MeshEntity(FTopologicalShapeEntity& InEntity)`
- L78 _public prototype_ `void Mesh(FTopologicalFace& Face);`
- L99 _protected prototype_ `void PreMeshingTasks();` — ApplyFaceCriteria, ComputeSurfaceSideProperties
- L100 _protected prototype_ `void MeshEntities();`
- L103 _protected prototype_ `void IsolateQuadFace(TArray<ParametricMesherTool::FCostToFace>& QuadSurfaces, TArray<FTopologicalFace*>& OtherSurfaces) const;`
- L105 _protected prototype_ `void LinkQuadSurfaceForMesh(TArray<ParametricMesherTool::FCostToFace>& QuadTrimmedSurfaceSet, TArray<TArray<FTopologicalFace*>>& OutStrips);`
- L106 _protected prototype_ `void MeshSurfaceByFront(TArray<ParametricMesherTool::FCostToFace>& QuadTrimmedSurfaceSet);`
- L108 _protected prototype_ `void ApplyEdgeCriteria(FTopologicalEdge& Edge);`
- L109 _protected prototype_ `static void ApplyFaceCriteria(FTopologicalFace& Face, const TArray<TSharedPtr<FCriterion>>& Criteria, const double, bool);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)
- L20 _namespace_ `namespace ParametricMesherTool` (scope `UE::CADKernel`)
- L37 _variable_ `constexpr double ConstMinCurvature = 0.001;` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Meshers/ParametricMesherConstantes.h` (Private)


#### class `UE::CADKernel::FMeshingTolerances`  
`class FMeshingTolerances`  
_L16-35_
- L19 _public member_ `const double GeometricTolerance;`
- L20 _public member_ `const double GeometricToleranceSqrt2;`
- L21 _public member_ `const double SquareGeometricTolerance;`
- L22 _public member_ `const double SquareGeometricTolerance2;`
- L23 _public member_ `const double MeshingTolerance;`
- L24 _public member_ `const double SquareMeshingTolerance;`
- L26 _public function_ `FMeshingTolerances(double InGeometricTolerance3D) : GeometricTolerance(InGeometricTolerance3D) , GeometricToleranceSqrt2(InGeometricTolerance3D * UE_DOUBLE_SQRT_2) , SquareGeometricTolerance(FMath::Square(GeometricTolerance)) , SquareGeometricTolerance2(2. * SquareGeometricTolerance) , MeshingTolerance(GeometricTolerance * MeshConst::GeometricToMeshingToleranceFactor) , SquareMeshingTolerance(FMath::Square(MeshingTolerance))`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)
- L8 _namespace_ `namespace MeshConst` (scope `UE::CADKernel`)
- L10 _variable_ `constexpr double MinCurvature = 0.001;` (scope `UE::CADKernel::MeshConst`)
- L11 _variable_ `constexpr double GeometricToMeshingToleranceFactor = 10.;` (scope `UE::CADKernel::MeshConst`)
- L12 _variable_ `constexpr double ElementRatioVsThickness = 20.;` (scope `UE::CADKernel::MeshConst`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Structure/Grid.h` (Private)


#### enum `UE::CADKernel::ENodeMarker`  
`enum class ENodeMarker : uint8`  
_L27-36_
- L29 _public enumerator_ `None = 0x00u` — No flags.
- L31 _public enumerator_ `IsInside = 0x01u`
- L32 _public enumerator_ `IsInsideButTooCloseToLoop = 0x02u` — node inside the loop but too close to the loop to be include in the mesh
- L33 _public enumerator_ `IsCloseToLoop = 0x04u`
- L35 _public enumerator_ `All = 0xFFu`

#### class `UE::CADKernel::FGrid`  
`class FGrid : public FGridBase`  
_L40-418_
- inherits: `FGridBase`
- L47 _protected member_ `FCoordinateGrid& CoordinateGrid;` — Cutting coordinates of the face respecting the meshing criteria
- L49 _protected function_ `virtual const FCoordinateGrid& GetCoordinateGrid() const override`
- L54 _protected member_ `const FSurfacicTolerance FaceTolerance;`
- L55 _protected member_ `const double MinimumElementSize;`
- L57 _protected member_ `FModelMesh& MeshModel;`
- L63 _protected member_ `TArray<TArray<FVector2d>> FaceLoops2D[EGridSpace::EndGridSpace];` — 2D Coordinate of Loop's nodes in each space
- L68 _protected member_ `TArray<TArray<FVector>> FaceLoops3D;` — 3D Coordinate of Loop nodes in each space
- L73 _protected member_ `TArray<TArray<FVector3f>> NormalsOfFaceLoops;` — Surface Normal at each boundary nodes
- L75 _protected member_ `TArray<TArray<int32>> NodeIdsOfFaceLoops;`
- L80 _protected member_ `int32 CountOfInnerNodes = 0;` — count of node inside the face i.e. node inside the external loop and outer the inner loops
- L82 _protected member_ `double MinOfMaxElementSize = 0;`
- L88 _protected member_ `TArray<ENodeMarker> NodeMarkers;` — Array to flag each points as inside, close, ... the face @see IsNode...,
- L92 _public member_ `FGridChronos Chronos;`
- L95 _public prototype_ `FGrid(FTopologicalFace& InFace, FModelMesh& InShellMesh);`
- L98 _public function_ `virtual ~FGrid()`
- L103 _public prototype_ `virtual ~FGrid() = default;`
- L114 _public prototype_ `void DefineCuttingParameters();` — Defines the cutting coordinate of the grid according to mesh criteria and the existing mesh of bordering edges (loop's edges) @see GetPreferredUVCoordinatesFromNeighbours
- L115 _public prototype_ `void DefineCuttingParameters(EIso Iso, FCuttingGrid& Neighbors);`
- L122 _public prototype_ `bool GeneratePointCloud();` — Computes the 2d Points, 3D points and Normals of the grid. call of DefineCuttingParameters is mandatory called before @return false if the grid is degenerated
- L129 _public prototype_ `void ProcessPointCloud();` — Process the generated point cloud to compute the scaled parametric spaces and to identify outer points of the face @see IsNodeInsideFace @see Points2D
- L138 _protected prototype_ `void ScaleLoops();` — Projects loop's points in the scaled parametric spaces @see FaceLoops2D @see ProcessPointClound (called in ProcessPointClound)
- L143 _protected prototype_ `void FindInnerFacePoints();` — @see ProcessPointClound (called in ProcessPointClound)
- L155 _protected prototype_ `void FindPointsCloseToLoop();` — Define if an inner node is close to a loop i.e. if the loop cross the cell [[IndexU - 1, IndexU], [IndexV - 1, IndexV]], each corner node of the cell is close to the loop This algorithm is inspired of Bresenham's line algorithm The loop is traversed segment by segment For each segment, according to the slop of the segment, each cell intersecting the segment is selected (FindIntersectionsCaseSlope_) i.e. each corner node of the cell is flagged IsCloseToLoop (SetCellCloseToLoop) @see SlopeUtils @see IsNodeCloseToLoop @see ProcessPointCloud (called in ProcessPointClound)
- L166 _protected prototype_ `void RemovePointsCloseToLoop();` — Find all node close to the boundary. For each node, the 3d distance to the boundary is estimated If this distance is bigger than the Tolerance, the node is remove Removing a node can make its neighbor removable, Each removed node make its direct neighbor removable, the process is recursive as long as it is possible to remove a node @see ProcessPointClound (called in ProcessPointClound)
- L172 _protected prototype_ `void GetPreferredUVCuttingParametersFromLoops(FCuttingGrid& CuttingFromLoops);` — Gets the cutting coordinates of the existing mesh of bordering edges (loop's edges) @see DefineCuttingParameters (called in DefineCuttingParameters)
- L177 _protected prototype_ `bool GetMeshOfLoops();` — @ return false if the mesh of the loop is degenerated
- L178 _protected prototype_ `void GetMeshOfLoop(const FTopologicalLoop& Loop);`
- L179 _protected prototype_ `void GetMeshOfThinZone(const FThinZone2D& ThinZone);`
- L187 _protected prototype_ `bool CheckIfExternalLoopIsDegenerate() const;` — @return true if the grid is not consistent to build a mesh as composed of only two border nodes.
- L192 _protected prototype_ `bool CheckIf2DGridIsDegenerate() const;` — @return true if along an Iso, all (U(i+1) - U(i)) < FaceTolerance
- L200 _public function_ `constexpr const int32 GetCuttingCount(EIso Iso) const`
- L208 _public function_ `const int32 GetTotalCuttingCount() const` — Return the number of points (inner and outer points) of the grid (i.e. CuttingCount[IsoU] x CuttingCount[IsoV]).
- L213 _public function_ `const double GetTolerance(EIso Iso) const`
- L221 _public function_ `const bool IsNodeInsideAndMeshable(int32 Index) const` — @return true if the node is inner the external loop and outer the inner loops and not too close
- L226 _public function_ `const bool IsNodeInsideButTooCloseToLoop(int32 Index) const`
- L234 _public function_ `const bool IsNodeFarFromFace(int32 Index) const` — @return true if the bits EPointMarker::IsInside, EPointMarker::IsInsideButTooCloseToLoop and EPointMarker::IsCloseToLoop are alls equal to 0
- L243 _public function_ `const bool IsNodeOutsideFace(int32 Index) const` — @return true if the bits EPointMarker::IsInside, EPointMarker::IsInsideButTooCloseToLoop and EPointMarker::IsCloseToLoop are alls equal to 0
- L249 _public function_ `const bool IsNodeInsideAndCloseToLoop(int32 Index) const`
- L258 _public function_ `const bool IsNodeOusideFaceButClose(int32 Index) const` — @return true if the bits EPointMarker::IsInside and EPointMarker::IsInsideButTooCloseToLoop are booth equal to 0 and EPointMarker::IsCloseToLoop  is equal to 1
- L264 _public function_ `void SetNodeInside(int32 Index)`
- L272 _public function_ `const int32 InnerNodesCount() const` — @return the count of inner nodes
- L280 _public function_ `const bool IsNodeCloseToLoop(int32 Index) const` — @return true if the node is close to a loop i.e. the loop cross the space [[IndexU - 1, IndexU + 1], [IndexV - 1, IndexV + 1]]
- L285 _public function_ `const bool IsNodeTooCloseToLoop(int32 Index) const`
- L290 _public function_ `void SetCloseToLoop(int32 Index)`
- L295 _public function_ `void SetTooCloseToLoop(int32 Index)`
- L301 _public function_ `void ResetInsideLoop(int32 Index)`
- L306 _public function_ `void SetInner2DPoint(EGridSpace Space, int32 Index, const FVector2d& NewCoordinate)`
- L314 _public function_ `const FVector3f& GetPointNormal(int32 IndexU, int32 IndexV) const` — @return the normal of the surface at the point at the Index of the grid
- L322 _public function_ `const FVector3f& GetPointNormal(int32 Index) const` — @return the normal of the surface at the point at the Index of the grid
- L327 _public function_ `const TArray<double>& GetCuttingCoordinatesAlongIso(EIso Iso) const`
- L332 _public function_ `const FCoordinateGrid& GetCuttingCoordinates() const`
- L340 _public function_ `TArray<FVector3f>& GetNormals()` — @return the array of normal of the points of the grid
- L345 _public function_ `const TArray<TArray<int32>>& GetNodeIdsOfFaceLoops() const`
- L350 _public function_ `const FVector2d& GetLoop2DPoint(EGridSpace Space, int32 LoopIndex, int32 Index) const`
- L355 _public function_ `void SetLoop2DPoint(EGridSpace Space, int32 LoopIndex, int32 Index, const FVector2d& NewCoordinate)`
- L360 _public function_ `const FVector& GetLoop3DPoint(int32 LoopIndex, int32 Index) const`
- L365 _public function_ `const int32 GetLoopCount() const`
- L373 _public function_ `const TArray<TArray<FVector2d>>& GetLoops2D(EGridSpace Space) const` — @return the array of array of 2d points of the loops according to the defined grid space
- L381 _public function_ `TArray<TArray<FVector>>& GetLoops3D()` — @return the array of array of 3d points of the loops
- L389 _public function_ `const TArray<TArray<FVector>>& GetLoops3D() const` — @return the array of array of 3d points of the loops
- L397 _public function_ `const TArray<TArray<FVector3f>>& GetLoopNormals() const` — @return the array of array of normal of the points of the loops
- L405 _public function_ `void UVIndexFromGlobalIndex(int32 GLobalIndex, int32& OutIndexU, int32& OutIndexV) const` — @return the Index of the position in the arrays of a point [IndexU, IndexV] of the grid
- L414 _public function_ `double GetMinElementSize() const` — @return the minimal size of the mesh elements according to 3d geometric tolerance

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CADKernel` (scope `UE`)
- L37 _prototype_ `ENUM_CLASS_FLAGS(ENodeMarker);` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Structure/GridBase.h` (Private)


#### class `UE::CADKernel::FGridBase`  
`class FGridBase : public FHaveStates`  
_L25-211_
- inherits: `FHaveStates`
- L30 _protected member_ `FTopologicalFace& Face;`
- L31 _protected member_ `const double Tolerance3D;`
- L36 _protected member_ `int32 CuttingCount[2] = { 0 , 0 };` — grid point cloud size
- L37 _protected member_ `int32 CuttingSize = 0;`
- L39 _protected member_ `FCoordinateGrid UniformCuttingCoordinates;`
- L44 _protected member_ `TArray<FVector2d> Points2D[EGridSpace::EndGridSpace];` — 2D Coordinate of grid nodes in each space
- L49 _protected member_ `TArray<FVector> Points3D;` — 3D Coordinate of inner nodes
- L54 _protected member_ `TArray<FVector3f> Normals;` — Surface Normal at each inner nodes
- L57 _public prototype_ `FGridBase(FTopologicalFace& InFace);`
- L59 _public function_ `virtual ~FGridBase()`
- L70 _public prototype_ `void TransformPoints(EGridSpace DestinationSpace, const TArray<FVector2d>& InPointsToScale, TArray<FVector2d>& OutScaledPoints) const;` — Convert an array of points of "DefaultParametric" space into a scaled parametric space @see FThinZone2DFinder::BuildBoundarySegments()
- L78 _public prototype_ `bool ScaleGrid();` — Builds the scaled parametric spaces @see Points2D @see GeneratePointCloud (ended GeneratePointCloud process) @return false if the scaled grid is degenerated
- L80 _public function_ `double GetTolerance() const`
- L87 _protected prototype_ `virtual const FCoordinateGrid& GetCoordinateGrid() const = 0;`
- L89 _protected prototype_ `void EvaluatePointGrid(const FCoordinateGrid& CoordinateGrid, bool bWithNormals);`
- L95 _protected function_ `void ComputeNewCoordinate(const TArray<FVector2d>& NewGrid, int32 IndexU, int32 IndexV, const FVector2d& InPoint, FVector2d& OutNewScaledPoint) const` — Convert Coordinate of "DefaultParametric" space into a scaled parametric space @see ScaleLoops
- L123 _public function_ `const FVector2d& GetInner2DPoint(EGridSpace Space, int32 Index) const` — @return the FVector2d (parametric coordinates) of the point at the Index of the grid in the defined grid space @see EGridSpace @see Points2D
- L131 _public function_ `const FVector2d& GetInner2DPoint(EGridSpace Space, int32 IndexU, int32 IndexV) const` — @return the FVector2d (parametric coordinates) of the point at the Index of the grid in the defined grid space @see EGridSpace
- L139 _public function_ `const FVector& GetInner3DPoint(int32 Index) const` — @return the FVector (3D coordinates) of the point at the Index of the grid
- L144 _public function_ `constexpr const TArray<double>& GetUniformCuttingCoordinatesAlongIso(EIso Iso) const`
- L149 _public function_ `const FCoordinateGrid& GetUniformCuttingCoordinates() const`
- L157 _public function_ `TArray<FVector>& GetInner3DPoints()` — @return the array of 3d points of the grid
- L165 _public function_ `const TArray<FVector>& GetInner3DPoints() const` — @return the array of 3d points of the grid
- L173 _public function_ `const TArray<FVector2d>& GetInner2DPoints(EGridSpace Space) const` — @return the array of 2d points of the grid in the defined space
- L178 _public function_ `const FTopologicalFace& GetFace() const`
- L183 _public function_ `FTopologicalFace& GetFace()`
- L191 _public function_ `int32 GobalIndex(int32 IndexU, int32 IndexV) const` — @return the Index of the position in the arrays of a point [IndexU, IndexV] of the grid
- L201 _public member_ `mutable bool bDisplay = true;`
- L203 _public prototype_ `void DisplayIsoNode(EGridSpace Space, const int32 PointIndex, FIdent Ident = 0, EVisuProperty Property = EVisuProperty::BluePoint) const;`
- L204 _public prototype_ `virtual void DisplayGridPoints(EGridSpace DisplaySpace) const;`
- L205 _public prototype_ `void DisplayInnerPoints(TCHAR* Message, EGridSpace DisplaySpace) const;`
- L209 _public prototype_ `void PrintTimeElapse() const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Structure/LoopCleaner.h` (Private)


#### struct `UE::CADKernel::LoopCleanerImpl::FPinchIntersectionContext`  
`struct FPinchIntersectionContext`  
_L30-40_
- L32 _public member_ `const TPair<double, double>& Intersection;`
- L33 _public member_ `FLoopNode* Nodes[2][3];`
- L34 _public member_ `TArray<const FVector2d*> Points[2];`
- L36 _public function_ `FPinchIntersectionContext(const TPair<double, double>& InIntersection) : Intersection(InIntersection)`

#### class `UE::CADKernel::FLoopCleaner`  
`class FLoopCleaner`  
_L93-439_
- L96 _private member_ `FGrid& Grid;`
- L97 _private member_ `const FMeshingTolerances& Tolerances;`
- L99 _private member_ `TArray<FLoopNode>& LoopNodes;`
- L100 _private member_ `TArray<FIsoSegment*>& LoopSegments;`
- L101 _private member_ `TFactory<FIsoSegment>& IsoSegmentFactory;`
- L103 _private member_ `bool bDisplay;`
- L105 _private member_ `TArray<FLoopNode*> BestStartNodeOfLoops;`
- L109 _private member_ `int32 LoopIndex;` — Index of the processing loop
- L115 _private member_ `TArray<FLoopNode*> NodesOfLoop;` — Array of the processed loop's nodes Warning: some nodes can be deleted -> check with Node.IsDelete
- L121 _private member_ `int32 NodesOfLoopCount;` — This value doesn't need to be updated because the count of nodes doesn't change Deleted nodes are not removed of NodesOfLoop array
- L124 _private member_ `int32 StartSegmentIndex;` — Index of first segment of the processing loop
- L125 _private member_ `int32 SegmentCount;`
- L133 _private member_ `int32 NextLoopFirstSegmentIndex;` — Index of first segment of the next loop Warning, this index need to be updated with the deletion of a segment Use RemoveSegmentOfLoops to delete a segment and use UpdateNextLoopFirstSegmentIndex in case of doubt
- L135 _private member_ `bool bLoopOrientation;`
- L136 _private member_ `TArray<TPair<double, double>> Intersections;`
- L137 _private member_ `FIntersectionSegmentTool LoopSegmentsIntersectionTool;`
- L139 _private member_ `LoopCleanerImpl::GetNextNodeMethod GetNext;`
- L140 _private member_ `LoopCleanerImpl::GetNextNodeMethod GetPrevious;`
- L141 _private member_ `LoopCleanerImpl::GetSegmentToNodeMethod GetFirst;`
- L142 _private member_ `LoopCleanerImpl::GetSegmentToNodeMethod GetSecond;`
- L146 _public prototype_ `FLoopCleaner(FIsoTriangulator& Triangulator);`
- L148 _public prototype_ `bool Run();`
- L152 _private prototype_ `bool CleanLoops();`
- L153 _private prototype_ `bool UncrossLoops(bool bAddProcessedLoop);`
- L159 _private prototype_ `void FindBestLoopExtremity();` — For each loop, find the best starting node i.e. a node well oriented All extremity nodes have to be identified, then one of the four nodes is chosen
- L168 _private prototype_ `bool RemoveLoopPicks();` — @return false if the process failed => the surface cannot be meshed
- L169 _private prototype_ `bool RemoveLoopPicks(TArray<FIsoSegment*>& Loop);`
- L171 _private prototype_ `bool RemovePickRecursively(FLoopNode* Node0, FLoopNode* Node1);`
- L172 _private prototype_ `bool FindAndRemoveCoincidence(FLoopNode*& StartNode);`
- L177 _private function_ `bool CheckAndRemovePick(const FVector2d& PreviousPoint, const FVector2d& NodeToRemovePoint, const FVector2d& NextPoint, FLoopNode& NodeToRemove)` — @return true if the node has been deleted
- L202 _private function_ `bool CheckAndRemoveCoincidence(const FVector2d& Point0, const FVector2d& Point1, FLoopNode& NodeToRemove)` — @return true if the node has been deleted
- L215 _private prototype_ `bool RemoveNodeOfLoop(FLoopNode& NodeToRemove);` — @return true if the node has been deleted
- L217 _private prototype_ `void FindLoopIntersections();`
- L222 _private prototype_ `bool RemoveSelfIntersectionsOfLoop();` — @return false if the process failed => the surface cannot be meshed
- L224 _private prototype_ `bool RemoveIntersection(TPair<double, double>& Intersection);`
- L225 _private prototype_ `bool RemoveOutgoingLoop(const TPair<double, double>& Intersection, const TPair<double, double>& NextIntersection);`
- L226 _private prototype_ `bool RemoveIntersectionsOfSubLoop(int32 IntersectionIndex, int32 IntersectionCount);`
- L227 _private prototype_ `bool RemoveOuterNode(const TPair<double, double>& Intersection);`
- L228 _private prototype_ `bool SwapNodes(const TPair<double, double>& Intersection);`
- L233 _private prototype_ `bool RemovePickOrCoincidenceBetween(FLoopNode* StartNode, FLoopNode* StopNode);` — @return false if the process failed => the surface cannot be meshed
- L246 _private prototype_ `bool TryToSwapSegmentsOrRemoveLoop(const TPair<double, double>& Intersection);` — Two cases: - the segments of the intersection a closed parallel and in same orientation. in this case, the sub-loop is a long pick. The sub-Loop is delete - the loop is an inner loop closed to the border: _____________                _____________ |  /             \			  |__/             \ \/               |     =>                     | /\               |		   __               | |  \_____________/			  |  \_____________/
- L247 _private prototype_ `void SwapSubLoopOrientation(int32 FirstSegmentIndex, int32 LastSegmentIndex);`
- L248 _private prototype_ `bool RemoveSubLoop(FLoopNode* StartNode, FLoopNode* EndNode);`
- L250 _private prototype_ `bool MoveIntersectingSectionBehindOppositeSection(LoopCleanerImpl::FLoopSection IntersectingSection, LoopCleanerImpl::FLoopSection OppositeSection);`
- L251 _private prototype_ `void MoveNodeBehindSegment(const FIsoSegment& IntersectingSegment, FLoopNode& NodeToMove);`
- L252 _private prototype_ `void MoveNode(FLoopNode& NodeToMove, FVector2d& NewPosition);`
- L254 _private prototype_ `void FixLoopOrientation();`
- L255 _private prototype_ `EOrientation GetLoopOrientation(const FLoopNode* StartNode);`
- L265 _private prototype_ `bool TryToRemoveIntersectionOfTwoConsecutiveIntersectingSegments(const FIsoSegment& IntersectingSegment, FIsoSegment& Segment);` — Segment and the segment next (or before Segment) are intersecting IntersectingSegment The common node is moved
- L266 _private prototype_ `void RemoveIntersectionByMovingOutsideSegmentNodeInside(const FIsoSegment& IntersectingSegment, const FIsoSegment& Segment, bool bIsSameInnerLoop);`
- L271 _private prototype_ `void OffsetSegment(FIsoSegment& Segment, FSegment2D& Segment2D, FSegment2D& IntersectingSegment2D);`
- L272 _private prototype_ `void OffsetNode(FLoopNode& Node, FSegment2D& IntersectingSegment2D);`
- L279 _private prototype_ `void SwapSegments(FIsoSegment& Segment0, FIsoSegment& Segment1);`
- L281 _private prototype_ `bool IsAPinch(const LoopCleanerImpl::FPinchIntersectionContext& Contex) const;`
- L292 _private prototype_ `bool DisconnectCoincidentNodes(const LoopCleanerImpl::FPinchIntersectionContext& Contex);` — OppositeCase: __________        ___________ |__     ___|      |__      ___| \   /             \    / o o        =>     o  o __/   \___		__/    \___
- L304 _private prototype_ `bool DisconnectCrossingSegments(LoopCleanerImpl::FPinchIntersectionContext& Context);` — CrossingCase: --<-    ->--       --<-    --<- |   \  /   |       |   \  /   | |    oo    |   =>  |    o     | |   /  \   |       |          | -->-    -<--       |     o    | |   /  \   | -->-    ->--
- L312 _private prototype_ `bool MovePickBehind(const TPair<double, double>& Intersection, bool bKeyIsExtremity);` — Case:  o_________o          o_________o o         => __/ \___		        o __/ \___
- L319 _private prototype_ `bool CheckMainLoopConsistency();`
- L321 _private function_ `FLoopNode* GetNodeAt(int32 Index)`
- L340 _private function_ `int32 NextSegmentIndex(int32 StartIndex)`
- L346 _private function_ `int32 NextIndex(int32 StartIndex)`
- L352 _private function_ `int32 FitNodeIndex(int32 Index)`
- L361 _private function_ `int32 FitSegmentIndex(int32 Index)`
- L370 _private prototype_ `bool Fill(LoopCleanerImpl::FPinchIntersectionContext& Context);`
- L372 _private function_ `void GetLoopNodeStartingFrom(FLoopNode* StartNode, TArray<FLoopNode*>& Loop)`
- L383 _private function_ `bool UpdateNodesOfLoop()`
- L397 _private function_ `void UpdateNextLoopFirstSegmentIndex(int32 NewLoopIndex)` — Update NextLoopFirstSegmentIndex i.e. the Index of the first segment of the next loop (for iteration purpose)
- L409 _private function_ `void RemoveSegmentOfLoops(FIsoSegment* Segment)`
- L417 _private function_ `void DisplayIntersection(const TPair<double, double>& Intersection)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CADKernel` (scope `UE`)
- L22 _namespace_ `namespace LoopCleanerImpl` (scope `UE::CADKernel`)
- L24 _typedef_ `typedef TFunction<double(const FVector2d&, const FVector2d&, double)> GetSlopeMethod;` (scope `UE::CADKernel::LoopCleanerImpl`)
- L25 _typedef_ `typedef TFunction<FLoopNode* (FLoopNode*)> GetNextNodeMethod;` (scope `UE::CADKernel::LoopCleanerImpl`)
- L26 _typedef_ `typedef TFunction<const FLoopNode* (const FLoopNode*)> GetNextConstNodeMethod;` (scope `UE::CADKernel::LoopCleanerImpl`)
- L27 _typedef_ `typedef TFunction<const FLoopNode* (const FIsoSegment*)> GetSegmentToNodeMethod;` (scope `UE::CADKernel::LoopCleanerImpl`)
- L28 _typedef_ `typedef TPair<FLoopNode*, FLoopNode*> FLoopSection;` (scope `UE::CADKernel::LoopCleanerImpl`)
- L42 _function_ `inline FLoopNode* GetNextNodeImpl(FLoopNode* Node)` (scope `UE::CADKernel::LoopCleanerImpl`)
- L47 _function_ `inline FLoopNode* GetPreviousNodeImpl(FLoopNode* Node)` (scope `UE::CADKernel::LoopCleanerImpl`)
- L52 _function_ `inline const FLoopNode* GetNextConstNodeImpl(const FLoopNode* Node)` (scope `UE::CADKernel::LoopCleanerImpl`)
- L57 _function_ `inline const FLoopNode* GetPreviousConstNodeImpl(const FLoopNode* Node)` (scope `UE::CADKernel::LoopCleanerImpl`)
- L62 _function_ `inline const FLoopNode* GetFirstNode(const FIsoSegment* Segment)` (scope `UE::CADKernel::LoopCleanerImpl`)
- L67 _function_ `inline const FLoopNode* GetSecondNode(const FIsoSegment* Segment)` (scope `UE::CADKernel::LoopCleanerImpl`)
- L72 _function_ `inline void RemoveDeletedNodes(TArray<FLoopNode*>& NodesOfLoop)` (scope `UE::CADKernel::LoopCleanerImpl`)
- L74 _function_ `int32 Index = NodesOfLoop.IndexOfByPredicate([](FLoopNode* Node) { return Node->IsDelete(); });` (scope `UE::CADKernel::LoopCleanerImpl::RemoveDeletedNodes`)
- L399 _function_ `NextLoopFirstSegmentIndex = LoopSegments.IndexOfByPredicate([&](FIsoSegment* Segment) { return ((FLoopNode&)Segment->GetFirstNode()).GetLoopIndex() > NewLoopIndex; });` (scope `UE::CADKernel::FLoopCleaner::UpdateNextLoopFirstSegmentIndex`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Structure/ModelMeshAnalyzer.h` (Private)


#### struct `UE::CADKernel::Analyzer::FTriangle`  
`struct FTriangle`  
_L20-46_
- L22 _public member_ `uint32 Vertices[3];`
- L23 _public member_ `FVector3f Normals[3];`
- L24 _public member_ `FEdge* Edges[3];`
- L25 _public member_ `const FFaceMesh* FaceMesh;`
- L28 _public function_ `FTriangle(uint32* InVertices, FEdge** InEdges, FVector3f* InNormals, const FFaceMesh* InFaceMesh) : FaceMesh(InFaceMesh)`
- L45 _public prototype_ `FVector ComputeNormal(const TArray<FVector>& NodeCoordinates) const;`

#### struct `UE::CADKernel::Analyzer::FEdge`  
`struct FEdge : public FHaveStates`  
_L48-74_
- inherits: `FHaveStates`
- L50 _public member_ `static const int32 MaxTraingleStoredCount = 2;`
- L51 _public member_ `uint32 VertexIndices[2];`
- L52 _public member_ `FTriangle* Triangles[MaxTraingleStoredCount];` — n first adjacent triangles
- L53 _public member_ `uint32 TriangleCount = 0;`
- L55 _public function_ `FEdge(uint32 Index0, uint32 Index1)`
- L61 _public function_ `void AddTriangle(FTriangle& Triangle)`
- L70 _public function_ `uint32 OtherVertexIndex(uint32 Index) const`

#### class `UE::CADKernel::FModelMeshAnalyzer`  
`class FModelMeshAnalyzer`  
_L78-99_
- L80 _private member_ `const FModelMesh& ModelMesh;`
- L82 _private member_ `TArray<FVector> NodeCoordinates;`
- L83 _private member_ `TArray<Analyzer::FEdge> Edges;`
- L84 _private member_ `TArray<Analyzer::FTriangle> Triangles;`
- L85 _private member_ `TArray<TArray<Analyzer::FEdge*>> VertexToEdges;` — Vertex to border or non manifold edges
- L88 _public function_ `FModelMeshAnalyzer(const FModelMesh& InModelMesh) : ModelMesh(InModelMesh)`
- L93 _public prototype_ `void BuildMesh();`
- L95 _public prototype_ `void ComputeBorderCount(int32& OutBorderCount, int32& OutNonManifoldCount) const;`
- L96 _public prototype_ `void ComputeMeshGapCount(int32& OutCycleCount, int32& OutChainCount) const;`
- L97 _public prototype_ `double ComputeMaxAngle() const;`
- L98 _public prototype_ `bool CheckOrientation() const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)
- L15 _namespace_ `namespace Analyzer` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Mesh/Structure/ThinZone2DFinder.h` (Private)


#### class `UE::CADKernel::FThinZone2DFinder`  
`class FThinZone2DFinder`  
_L22-141_
- L27 _protected member_ `const FGridBase& Grid;`
- L28 _protected member_ `const FTopologicalFace& Face;`
- L30 _protected member_ `double FinderTolerance;`
- L31 _protected member_ `double SquareFinderTolerance;`
- L33 _protected member_ `TArray<FThinZone2D> ThinZones;`
- L35 _protected member_ `TArray<FEdgeSegment*> LoopSegments;`
- L36 _protected member_ `TArray<TArray<FEdgeSegment*>> ThinZoneSides;`
- L38 _protected member_ `double ExternalLoopLength = 0.0;`
- L40 _protected member_ `TFactory<FEdgeSegment> SegmentFatory;`
- L44 _public function_ `FThinZone2DFinder(const FGridBase& InGrid, const FTopologicalFace& InFace) : Grid(InGrid) , Face(InFace) , SegmentFatory()`
- L54 _public prototype_ `bool SearchThinZones(double InFinderTolerance);`
- L56 _public function_ `TArray<FThinZone2D>& GetThinZones()`
- L64 _private function_ `void SetTolerance(double InFinderTolerance)`
- L73 _private prototype_ `bool BuildLoopSegments();` — @return false if the main loop is empty
- L75 _private prototype_ `void FindCloseSegments();`
- L80 _private prototype_ `void FindCloseSegments(const TArray<FEdgeSegment*>& Segments, const TArray<const TArray<FEdgeSegment*>*>& OppositeSides);` — For Segment with Marker1 in Segments, find in OppositeSides the closest segment in the respect of the criteria
- L86 _private prototype_ `void LinkCloseSegments();` — Fill ThinZoneSides (TArray<TArray<FEdgeSegment*>>) Each TArray<FEdgeSegment*> is an array of connected segment defining a side of one (or more) thin zone
- L99 _private prototype_ `void ImproveThinSide();` — Two adjacent sides can be separated by a small chain of segments slightly too far to another side be considered as thin side. If this kind of chain is find, the three chains are merged. E.g. Side(n-1) and Side(n) are close from Side(k) _ / \ <-- a small chain of segments slightly too far                          / \ /   \												                       /   \ #-------------------#     #-----------------#              ====>		      #-------------------/     \-----------------# Side(n-1)                  Side(n)									                      Side(n) #-------------------------------------------#								  #-------------------------------------------# Side(k)                                                                       Side(k)
- L112 _private prototype_ `bool CheckIfCloseSideOfThinSideIsNotDegenerated(TArray<FEdgeSegment*>& Side);` — Check that the thin side is not opposite to a unique point #-----------------------#  a Side / The opposite unique point @return false if the opposite is degenerated
- L113 _private prototype_ `void CheckIfCloseSideOfThinSidesAreNotDegenerated();`
- L126 _private prototype_ `void SplitThinSide();` — SplitThinSide splits chain in front of many other chain eg. Side A is close to Side B then Side C Side A has to be split in two Side A #-----------------# #--------------------# Side B               Side C
- L128 _private prototype_ `void BuildThinZone();`
- L129 _private prototype_ `void BuildThinZone(const TArray<FEdgeSegment*>& FirstSide, const TArray<FEdgeSegment*>& SecondSide);`
- L130 _private prototype_ `static void GetThinZoneSideConnectionsLength(const TArray<FEdgeSegment*>& FirstSide, const TArray<FEdgeSegment*>& SecondSide, double InMaxLength, double* OutLengthBetweenExtremities, TArray<const FTopologicalEdge*>* OutPeakEdges);`
- L136 _private member_ `bool bDisplay = false;`
- L137 _private prototype_ `void DisplayCloseSegments();`
- L138 _private prototype_ `void DisplayLoopSegments();`
- L139 _private prototype_ `void DisplaySegmentsOfThinZone();`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CADKernel` (scope `UE`)
- L144 _namespace_ `namespace ThinZone` (scope `UE::CADKernel`)
- L146 _variable_ `static bool bDisplay = false;` (scope `UE::CADKernel::ThinZone`)
- L147 _prototype_ `void DisplayEdgeSegmentAndProjection(const FEdgeSegment* Segment, EVisuProperty SegColor, EVisuProperty OppositeColor, EVisuProperty ProjectionColor);` (scope `UE::CADKernel::ThinZone`)
- L148 _prototype_ `void DisplayEdgeSegmentAndProjection(const FEdgeSegment* Segment, const FEdgeSegment* Opposite, EVisuProperty SegColor, EVisuProperty OppositeColor, EVisuProperty ProjectionColor);` (scope `UE::CADKernel::ThinZone`)
- L149 _prototype_ `void DisplayEdgeSegment(const FEdgeSegment* EdgeSegment, EVisuProperty Color);` (scope `UE::CADKernel::ThinZone`)
- L150 _prototype_ `void DisplayEdgeSegment(const FEdgeSegment* EdgeSegment, EVisuProperty Color, int32 Index);` (scope `UE::CADKernel::ThinZone`)
- L151 _prototype_ `void DisplayThinZoneSidesAndCloses(const TArray<TArray<FEdgeSegment*>>& ThinZoneSides);` (scope `UE::CADKernel::ThinZone`)
- L152 _prototype_ `void DisplayThinZoneSides(const TArray<TArray<FEdgeSegment*>>& ThinZoneSides);` (scope `UE::CADKernel::ThinZone`)
- L153 _prototype_ `void DisplayThinZoneSides2(const TArray<TArray<FEdgeSegment*>>& ThinZoneSides);` (scope `UE::CADKernel::ThinZone`)
- L154 _prototype_ `void DisplayThinZoneSide2(const TArray<FEdgeSegment*>& Side, int32 Index, bool bSplitBySide = false, bool bSplitBySegment = false);` (scope `UE::CADKernel::ThinZone`)
- L155 _prototype_ `void DisplayThinZoneSide(const TArray<FEdgeSegment*>& Side, int32 Index, EVisuProperty Color, bool bSplitBySegment = false);` (scope `UE::CADKernel::ThinZone`)
- L156 _prototype_ `void DisplayThinZoneSideAndClose(const TArray<FEdgeSegment*>& Side, int32 Index, bool bSplitBySegment = false);` (scope `UE::CADKernel::ThinZone`)
- L157 _prototype_ `void DisplayThinZoneSide(const FThinZoneSide& Side, int32 Index, EVisuProperty Color, bool bSplitBySegment = false);` (scope `UE::CADKernel::ThinZone`)
- L158 _prototype_ `void DisplayThinZones(const TArray<FThinZone2D>& ThinZones);` (scope `UE::CADKernel::ThinZone`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Topo/FaceAnalyzer.h` (Private)


#### class `UE::CADKernel::Topo::FEdgeSegment`  
`class FEdgeSegment : public FHaveStates`  
_L25-150_
- inherits: `FHaveStates`
- L28 _private member_ `const FTopologicalEdge* Edge = nullptr;`
- L29 _private member_ `double Coordinates[2] = {0. ,0.};`
- L30 _private member_ `FVector Points[2];`
- L31 _private member_ `FVector Middle;`
- L32 _private member_ `FVector Vector;`
- L34 _private member_ `FEdgeSegment* ClosedSegment = nullptr;`
- L36 _private member_ `double MiddleAxis = 0.;`
- L37 _private member_ `double SquareDistanceToClosedSegment = 0.;`
- L39 _private member_ `double Length;`
- L41 _private member_ `bool bIsThinZone = false;`
- L44 _private member_ `FIdent Id;`
- L45 _private member_ `static FIdent LastId;`
- L49 _public prototype_ `FEdgeSegment() = default;`
- L51 _public prototype_ `virtual ~FEdgeSegment() = default;`
- L53 _public function_ `void SetBoundarySegment(const FTopologicalEdge* InEdge, double InStartU, double InEndU, const FVector& InStartPoint, const FVector& InEndPoint)`
- L75 _public function_ `const FVector GetVector() const`
- L81 _public function_ `FIdent GetId() const`
- L87 _public function_ `const FTopologicalEdge* GetEdge() const`
- L92 _public function_ `double GetLength() const`
- L97 _public function_ `FVector GetMiddle() const`
- L102 _public function_ `constexpr const FVector& GetExtemity(const ELimit Limit) const`
- L107 _public function_ `constexpr double GetCoordinate(const ELimit Limit) const`
- L115 _public function_ `double ComputeCosAngleOf(const FEdgeSegment* Segment)` — Compute the slope of the input Segment according to this.
- L120 _public function_ `FEdgeSegment* GetClosedSegment() const`
- L125 _public function_ `void SetClosedSegment(FEdgeSegment* InSegmentA, double InSquareDistance)`
- L131 _public function_ `double GetClosedSquareDistance() const`
- L136 _public function_ `FVector ProjectPoint(const FVector& PointToProject, double& SegmentU) const`
- L141 _public function_ `bool IsThinZone()`
- L146 _public function_ `void SetAsThinZone()`

#### struct `UE::CADKernel::Topo::FThinFaceContext`  
`struct FThinFaceContext`  
_L152-171_
- L154 _public member_ `const FTopologicalLoop& Loop;`
- L156 _public member_ `TArray<Topo::FEdgeSegment*> LoopSegments;`
- L157 _public member_ `double ExternalLoopLength = 0.0;`
- L158 _public member_ `TFactory<Topo::FEdgeSegment> SegmentFatory;`
- L160 _public member_ `TArray<double> EdgeSquareDistance;`
- L161 _public member_ `TArray<double> EdgeMaxSquareDistance;`
- L163 _public member_ `double MaxSquareDistance = 0;`
- L164 _public member_ `double ThinSideEdgeLength = 0;`
- L165 _public member_ `double OppositSideEdgeLength = 0;`
- L167 _public function_ `FThinFaceContext(const FTopologicalLoop& InLoop) : Loop(InLoop)`

#### class `UE::CADKernel::FFaceAnalyzer`  
`class FFaceAnalyzer`  
_L175-207_
- L179 _protected member_ `const double Tolerance;`
- L180 _protected member_ `const double SquareTolerance;`
- L181 _protected member_ `const double MaxOppositSideLength;`
- L183 _protected member_ `FTopologicalFace& Face;`
- L187 _public function_ `FFaceAnalyzer(FTopologicalFace& InFace, double InTol) : Tolerance(InTol) , SquareTolerance(FMath::Square(InTol)) , MaxOppositSideLength(4. * InTol) , Face(InFace)`
- L195 _public prototype_ `bool IsThinFace(double& OutGapSize);`
- L199 _private prototype_ `void BuildLoopSegments(Topo::FThinFaceContext& Context);`
- L200 _private prototype_ `void FindClosedSegments(Topo::FThinFaceContext& Context);`
- L201 _private prototype_ `void Analyze(Topo::FThinFaceContext& Context);`
- L204 _private prototype_ `void DisplayCloseSegments(Topo::FThinFaceContext& Context);`
- L205 _private prototype_ `void DisplayLoopSegments(Topo::FThinFaceContext& Context);`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace CADKernel` (scope `UE`)
- L22 _namespace_ `namespace Topo` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Private/UI/Message.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCADKernelBase, Error, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCADKernelBase, Error, All);`

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Utils/ArrayUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)
- L11 _namespace_ `namespace ArrayUtils` (scope `UE::CADKernel`)
- L19 _function_ `inline void InsertInside(TArray<double>& InitialArray, const TArray<double>& ValuesToInsert, double Epsilon)` (scope `UE::CADKernel::ArrayUtils`) — Merge two array of sorted values and keep the resulting array sorted. The value to insert is inserted if and only if it is not nearly equal to an existent value and if it is inside the boundary of the InitialArray ([InitialArray[0], InitialArray.Last()]) The values of the existing array are always kept.
- L66 _function_ `inline void Complete(TArray<double>& InitialArray, TArray<double>& ValuesToInsert, double Epsilon)` (scope `UE::CADKernel::ArrayUtils`) — Merge two array of sorted values and keep the resulting array sorted. The value to insert is inserted if and only if it is not nearly equal to an existent value except for the first and last value of ValuesToInsert if they are outside initial array boundary
- L130 _function_ `inline void RemoveDuplicates(TArray<double>& ArrayToProcess, double Epsilon)` (scope `UE::CADKernel::ArrayUtils`)
- L154 _function_ `inline void SubArrayWithoutBoundary(const TArray<double>& InitialArray, const FLinearBoundary& Boundary, double Tolerance, TArray<double>& OutArray)` (scope `UE::CADKernel::ArrayUtils`)
- L219 _function_ `inline void FindCoordinateIndex(const TArray<double>& InCoordinates, double Coordinate, int32& OutIndex)` (scope `UE::CADKernel::ArrayUtils`) — Find the index of the segment containing the coordinate i.e. Coordinate is in [InCoordinates[OutIndex], InCoordinates[OutIndex+1]] This method is very fast if initial value of Index is near the solution. This is very useful to process linked set of coordinate like loop point coordinates.

### `Source/Runtime/Datasmith/CADKernel/Base/Private/Utils/Util.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)
- L11 _namespace_ `namespace Utils` (scope `UE::CADKernel`)
- L14 _function_ `template<typename SRC, typename DST> inline void TSharedPtrArrayConversion(const TArray<TSharedPtr<SRC>>& Source, TArray<TSharedPtr<DST>>& Destination)` (scope `UE::CADKernel::Utils`)
- L24 _function_ `template<typename SRC, typename DST> inline void TSharedPtrArrayConversionChecked(const TArray<TSharedPtr<SRC>>& Source, TArray<TSharedPtr<DST>>& Destination)` (scope `UE::CADKernel::Utils`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/CADKernel.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmith, Log, All);`

### `Source/Runtime/Datasmith/CADKernel/Base/Public/CADKernelLog.h` (Public)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCADKernel, Log, All)`

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Core/CADEntity.h` (Public)


#### enum `UE::CADKernel::EEntity`  
`enum class EEntity : uint8`  
_L17-47_
- L19 _public enumerator_ `None = 0`
- L21 _public enumerator_ `Curve`
- L22 _public enumerator_ `Surface`
- L24 _public enumerator_ `EdgeLink`
- L25 _public enumerator_ `VertexLink`
- L27 _public enumerator_ `TopologicalEdge`
- L28 _public enumerator_ `TopologicalFace`
- L30 _public enumerator_ `TopologicalLink`
- L31 _public enumerator_ `TopologicalLoop`
- L33 _public enumerator_ `TopologicalVertex`
- L35 _public enumerator_ `Shell`
- L36 _public enumerator_ `Body`
- L37 _public enumerator_ `Model`
- L39 _public enumerator_ `MeshModel`
- L40 _public enumerator_ `Mesh`
- L42 _public enumerator_ `Group`
- L43 _public enumerator_ `Criterion`
- L44 _public enumerator_ `Property`
- L46 _public enumerator_ `EntityTypeEnd`

#### class `UE::CADKernel::FEntity`  
`class FEntity : public TSharedFromThis<FEntity>, public FHaveStates`  
_L55-303_
- inherits: `TSharedFromThis<FEntity>,FHaveStates`
- L60 _protected member_ `static const TCHAR* TypesNames[];`
- L61 _protected member_ `FIdent Id = 0;`
- L64 _public prototype_ `virtual ~FEntity();`
- L66 _public function_ `virtual void Delete()`
- L72 _public function_ `virtual void Empty()`
- L78 _public function_ `template<typename OtherEntity, typename... InArgTypes> static TSharedRef<OtherEntity> MakeShared(InArgTypes&&... Args)`
- L90 _public function_ `template<typename OtherEntity> static TSharedRef<OtherEntity> MakeShared(FCADKernelArchive& Archive)`
- L104 _public prototype_ `static void SerializeIdent(FCADKernelArchive& Ar, TSharedPtr<FEntity>& Entity, bool bSaveSelection = true);` — To Serialize a TSharedPtr<FEntity>, the Id of the FEntity is saved in the archive (ArchiveId). At the deserialization of the archive, a map is build linking ArchiveId to the TSharedPtr of the deserialized entities. At the deserialization of a TSharedPtr<FEntity>, the ArchiveId of the TSharedPtr<FEntity> is get. The map return the associated TSharedPtr. If the Entity is not yet deserialized, the TSharedPtr is add to a waiting list to be set as soon as the associated Entity is deserialized See FDatabase for more details
- L105 _public prototype_ `static void SerializeIdent(FCADKernelArchive& Ar, TWeakPtr<FEntity>& Entity, bool bSaveSelection = true);`
- L106 _public prototype_ `static void SerializeIdent(FCADKernelArchive& Ar, FEntity** Entity, bool bSaveSelection = true);`
- L109 _public function_ `template<typename EntityType> static void SerializeIdent(FCADKernelArchive& Ar, EntityType** Entity, bool bSaveSelection = true)`
- L115 _public function_ `template<typename EntityType> static void SerializeIdent(FCADKernelArchive& Ar, TSharedPtr<EntityType>& Entity, bool bSaveSelection = true)`
- L121 _public function_ `template<typename EntityType> static void SerializeIdent(FCADKernelArchive& Ar, TWeakPtr<EntityType>& Entity, bool bSaveSelection = true)`
- L129 _public prototype_ `static void SerializeIdents(FCADKernelArchive& Ar, TArray<FEntity*>& Array, bool bSaveSelection = true);` — SerializeIdent of each TSharedPtr<FEntity> of the array
- L130 _public prototype_ `static void SerializeIdents(FCADKernelArchive& Ar, TArray<TWeakPtr<FEntity>>& Array, bool bSaveSelection = true);`
- L131 _public prototype_ `static void SerializeIdents(FCADKernelArchive& Ar, TArray<TSharedPtr<FEntity>>& Array, bool bSaveSelection = true);`
- L132 _public prototype_ `static void SerializeIdents(FCADKernelArchive& Ar, TArray<TOrientedEntity<FEntity>>& Array);`
- L135 _public function_ `template<typename EntityType> static void SerializeIdents(FCADKernelArchive& Ar, TArray<EntityType*>& Array, bool bSaveSelection = true)`
- L141 _public function_ `template<typename EntityType> static void SerializeIdents(FCADKernelArchive& Ar, TArray<TWeakPtr<EntityType>>& Array, bool bSaveSelection = true)`
- L147 _public function_ `template<typename EntityType> static void SerializeIdents(FCADKernelArchive& Ar, TArray<TSharedPtr<EntityType>>& Array, bool bSaveSelection = true)`
- L155 _public function_ `static void SpawnIdentOnEntities(TArray<FEntity*>& Array, FDatabase& Database)` — Spawn Ident on each FEntity* of the array
- L166 _public function_ `static void SpawnIdentOnEntities(TArray<TSharedPtr<FEntity>>& Array, FDatabase& Database)` — Spawn Ident on each TSharedPtr<FEntity> of the array
- L174 _public function_ `static void SpawnIdentOnEntities(TArray<TOrientedEntity<FEntity>>& Array, FDatabase& Database)`
- L183 _public function_ `template<typename EntityType> static void SpawnIdentOnEntities(TArray<TSharedPtr<EntityType>>& Array, FDatabase& Database)`
- L191 _public function_ `static void ResetMarkersRecursivelyOnEntities(const TArray<FEntity*>& Array)` — Reset Processed flags Recursively on each TSharedPtr<FEntity> of the array
- L199 _public function_ `static void ResetMarkersRecursivelyOnEntities(const TArray<TWeakPtr<FEntity>>& Array)`
- L207 _public function_ `static void ResetMarkersRecursivelyOnEntities(const TArray<TSharedPtr<FEntity>>& Array)`
- L215 _public function_ `static void ResetMarkersRecursivelyOnEntities(const TArray<TOrientedEntity<FEntity>>& Array)`
- L224 _public function_ `template<typename EntityType> static void ResetMarkersRecursivelyOnEntities(const TArray<TSharedPtr<EntityType>>& Array)`
- L241 _public function_ `virtual void Serialize(FCADKernelArchive& Ar)` — Serialization of a FEntity. Each class derived from FEntity has to override this method (and call the direct base class override method first) E.g. class FEntityXXX : public FEntityXX { virtual void Serialize(FCADKernelArchive& Ar) override { FEntityXX::Serialize(Ar); ... } }
- L250 _public prototype_ `static TSharedPtr<FEntity> Deserialize(FCADKernelArchive& Ar);` — Deserialize the next entity in the archive.
- L252 _public prototype_ `static const TCHAR* GetTypeName(EEntity Type);`
- L254 _public prototype_ `virtual EEntity GetEntityType() const = 0;`
- L256 _public function_ `bool IsTopologicalEntity() const`
- L261 _public function_ `bool IsTopologicalShapeEntity() const`
- L266 _public function_ `bool IsGeometricalEntity()`
- L271 _public function_ `const TCHAR* GetTypeName() const`
- L276 _public function_ `const FIdent& GetId() const`
- L282 _public prototype_ `void InfoEntity() const;`
- L283 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity& EntityInfo) const;`
- L284 _public prototype_ `static void AddEntityInDatabase(TSharedRef<FEntity> Entity);`
- L287 _public function_ `virtual void SpawnIdent(FDatabase& Database)`
- L295 _public function_ `virtual void ResetMarkersRecursively() const`
- L302 _protected prototype_ `bool SetId(FDatabase& Database);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Core/CADKernelArchive.h` (Public)


#### class `UE::CADKernel::FCADKernelArchive`  
`class FCADKernelArchive`  
_L17-168_
- L20 _public member_ `TUniquePtr<FMemoryReader> MemoryReader;`
- L21 _public member_ `TUniquePtr<FMemoryArchive> MemoryArchive;`
- L22 _public member_ `TSharedPtr<FArchive> ArchivePtr;`
- L23 _public member_ `FArchive& Archive;`
- L24 _public member_ `FSession& Session;`
- L25 _public member_ `FModel* ArchiveModel = nullptr;`
- L27 _public function_ `FCADKernelArchive(FSession& InSession, FArchive& InArchive) : Archive(InArchive) , Session(InSession)`
- L36 _public function_ `FCADKernelArchive(FSession& InSession, const TArray<uint8>& InRawData) : MemoryArchive(MakeUnique<FMemoryReader>(InRawData, true)) , Archive(*MemoryArchive) , Session(InSession)` — Archive reader constructor
- L43 _public function_ `FCADKernelArchive(FSession& InSession, TArray<uint8>& InRawData) : MemoryArchive(MakeUnique<FMemoryWriter>(InRawData, true)) , Archive(*MemoryArchive) , Session(InSession)`
- L50 _public function_ `FCADKernelArchive(FSession& InSession, FArchive* InArchive) : ArchivePtr(MakeShareable<FArchive>(InArchive)) , Archive(*InArchive) , Session(InSession)`
- L57 _public function_ `static TSharedPtr<FCADKernelArchive> CreateArchiveWriter(FSession& InSession, const TCHAR* FileName)`
- L67 _public function_ `static TSharedPtr<FCADKernelArchive> CreateArchiveReader(FSession& InSession, const TCHAR* FileName)`
- L77 _public function_ `static TSharedPtr<FCADKernelArchive> CreateArchiveWriter(FSession& InSession, TArray<uint8>& InRawData)`
- L87 _public function_ `static TSharedPtr<FCADKernelArchive> CreateArchiveReader(FSession& InSession, const TArray<uint8>& InRawData)`
- L98 _public function_ `template<typename EntityType> void operator<<(EntityType& Entity)`
- L103 _public function_ `bool IsLoading() const`
- L108 _public function_ `bool IsSaving() const`
- L113 _public function_ `void Serialize(void* Value, int64 Length)`
- L119 _public function_ `template<typename EntityType> void Serialize(TArray<EntityType>& EntityArray)`
- L136 _public function_ `template<typename EntityType> void Serialize(EntityType& EntityArray)`
- L141 _public prototype_ `void SetReferencedEntityOrAddToWaitingList(FIdent ArchiveId, FEntity** Entity);`
- L142 _public prototype_ `void SetReferencedEntityOrAddToWaitingList(FIdent ArchiveId, TWeakPtr<FEntity>& Entity);`
- L143 _public prototype_ `void SetReferencedEntityOrAddToWaitingList(FIdent ArchiveId, TSharedPtr<FEntity>& Entity);`
- L145 _public prototype_ `void AddEntityToSave(FIdent Id);`
- L146 _public prototype_ `void AddEntityFromArchive(TSharedPtr<FEntity>& Entity);`
- L149 _public function_ `template<typename EntityType> void AddEntityFromArchive(TSharedPtr<EntityType>& Entity)`
- L154 _public function_ `int64 TotalSize()`
- L159 _public function_ `int64 Tell()`
- L164 _public function_ `void Close()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Core/Chrono.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Core/Database.h` (Public)


#### class `UE::CADKernel::FDatabase`  
`class FDatabase`  
_L16-313_
- L28 _protected member_ `TSharedPtr<FModel> Model;` — Root Geometry Entity node
- L34 _protected member_ `TArray<TSharedPtr<FEntity>> DatabaseEntities;` — Array (use as a Map<FIdent, TSharedPtr<FEntity>>) of all the entities create during the session Each Entity.Id is the index of the entity in the array
- L39 _protected member_ `TArray<FIdent> AvailableIdents;` — Recycling of the Id to avoid fragmented idents
- L45 _protected member_ `TArray<TSharedPtr<FEntity>> ArchiveEntities;` — Array (use as a Map<FIdent, TSharedPtr<FEntity>>) of all the entities of an archive Each Entity is at the index of AchiveId in the array
- L60 _protected member_ `TArray<TArray<TSharedPtr<FEntity>*>> ArchiveIdToWaitingSharedPointers;` — Array (use as a Map<FIdent, TArray<TSharedPtr<FEntity>*>>) Some Entity reference an other Entities (with a TSharedPtr). If at the deserialization of the Entity, the referenced entity is not yet created, the pointer of the TSharedPtr of the referenced entity is added in the array associated to the ArchiveId of the referenced entity. E.g. Edge |- ArchiveId = 5 |- Vertex1 (ArchiveId = 6) IdToWaitingPointers[ArchiveId].Add(&Edge.Vertex)
- L61 _protected member_ `TArray<TArray<TWeakPtr<FEntity>*>> ArchiveIdToWaitingWeakPointers;`
- L62 _protected member_ `TArray<TArray<FEntity**>> ArchiveIdToWaitingPointers;`
- L67 _protected member_ `TSet<FIdent> EntitiesToBeSerialized;` — Dedicated to SerializeSelection. Set of entity Ids needed to be saved
- L72 _protected member_ `TQueue<FIdent> NotYetSerialized;` — Dedicated to SerializeSelection. Queue of entity Ids waiting to be saved
- L74 _protected member_ `mutable bool bForceSpawning = false;`
- L75 _protected member_ `bool bIsRecursiveSerialization = false;`
- L76 _protected member_ `uint32 EntityCount;`
- L80 _public prototype_ `FDatabase();`
- L82 _public function_ `FModel& GetModel()`
- L83 _public prototype_ `TSharedPtr<FModel> GetModelAsShared();`
- L88 _public prototype_ `void RemoveEntity(FIdent idEntity);` — Remove from database
- L89 _public prototype_ `void RemoveEntity(FEntity& Entity);`
- L96 _public prototype_ `void SerializeSelection(FCADKernelArchive& Ar, const TArray<FIdent>& SelectionIds);` — Recursive serialization of a selection. The selection and all the dependencies are serialized. All entities that need to be saved (added in EntitiesToBeSerialized set) for the completeness of the archive are added to the queue of entities to Serialized (NotYetSerialized).
- L101 _public prototype_ `void Serialize(FCADKernelArchive& Ar);` — All entities of the session are saved in the archive
- L103 _public prototype_ `void Deserialize(FCADKernelArchive& Ar);`
- L108 _public prototype_ `void CleanArchiveEntities();` — Method to clean entity descriptions i.e. removing invalid references (like unsaved linked edges of an edge because the neighbor topological face is not saved)
- L113 _public prototype_ `void Empty();` — Delete all the entities of the session
- L119 _public function_ `void AddEntity(TSharedPtr<FEntity> Entity)` — All Entities are saved in the session map that allows to retrieve them according to their Id This process is automatically done during the entity creation (FEntity::MakeShared)
- L141 _public function_ `void AddEntityFromArchive(TSharedPtr<FEntity>Entity)` — During the load of an FArchive: All Entities are saved in the session map (like Entity created in runtime) that allows to retrieve them according to their Id. Archive's entities are also saved in a temporary map for the load purpose (c.f. FEntity::Serialize) This process is automatically done during the entity creation (FEntity::MakeShared)
- L196 _public function_ `void SetReferencedEntityOrAddToWaitingList(FIdent ArchiveId, TSharedPtr<FEntity>& Entity)` — Find TSharedPtr<FEntity> associate to an Archive Id If the Entity is not yet created, add the entity in the waiting list
- L219 _public function_ `void SetReferencedEntityOrAddToWaitingList(FIdent ArchiveId, TWeakPtr<FEntity>& Entity)` — Find TWeakPtr<FEntity> associate to an Archive Id If the Entity is not yet created, add the entity in the waiting list
- L242 _public function_ `void SetReferencedEntityOrAddToWaitingList(FIdent ArchiveId, FEntity** Entity)` — Find FEntity* associate to an Archive Id If the Entity is not yet created, add the entity in the waiting list
- L261 _public prototype_ `uint32 SpawnEntityIdents(const TArray<TSharedPtr<FEntity>>& SelectedEntities, bool bForceSpawning = false);`
- L262 _public prototype_ `uint32 SpawnEntityIdents(const TArray<FEntity*>& SelectedEntities, bool bForceSpawning = false);`
- L263 _public prototype_ `uint32 SpawnEntityIdent(FEntity& SelectedEntity, bool bForceSpawning = false);`
- L269 _protected function_ `void AddEntityToSave(FIdent EntityId)` — Dedicated method for SerializeSelection
- L279 _private prototype_ `FIdent CreateId();`
- L295 _public prototype_ `TSharedPtr<FEntity> GetEntity(FIdent id) const;`
- L296 _public prototype_ `void GetEntities(const TArray<FIdent>& ids, TArray<TSharedPtr<FEntity>>& Entities) const;`
- L297 _public prototype_ `void GetEntities(const TArray<FIdent>& ids, TArray<FEntity*>& Entities) const;`
- L298 _public prototype_ `void GetTopologicalEntities(const TArray<FIdent>& ids, TArray<FTopologicalEntity*>& Entities) const;`
- L299 _public prototype_ `void GetTopologicalShapeEntities(const TArray<FIdent>& ids, TArray<FTopologicalShapeEntity*>& Entities) const;`
- L301 _public prototype_ `void GetEntitiesOfType(EEntity Type, TArray<TSharedPtr<FEntity>>& OutEntities) const;`
- L302 _public prototype_ `void GetEntitiesOfTypes(const TSet<EEntity>& Types, TArray<TSharedPtr<FEntity>>& OutEntities) const;`
- L304 _public prototype_ `void ExpandSelection(TSharedPtr<FEntity> Entities, const TSet<EEntity>& Filter, TSet<TSharedPtr<FEntity>>& OutSelection) const;`
- L305 _public prototype_ `void ExpandSelection(const TArray<TSharedPtr<FEntity>>& Entities, const TSet<EEntity>& Filter, TSet<TSharedPtr<FEntity>>& OutSelection) const;`
- L306 _public prototype_ `void ExpandSelection(const TArray<TSharedPtr<FEntity>>& Entities, const TSet<EEntity>& Filter, TArray<TSharedPtr<FEntity>>& OutSelection) const;`
- L308 _public prototype_ `void TopologicalEntitiesSelection(const TArray<TSharedPtr<FEntity>>& Entities, TArray<TSharedPtr<FTopologicalEntity>>& OutTopoEntities, bool bFindSurfaces, bool bFindEdges, bool bFindVertices) const;`
- L309 _public prototype_ `void CadEntitiesSelection(const TArray<TSharedPtr<FEntity>>& Entities, TArray<TSharedPtr<FEntity>>& OutCadEntities) const;`
- L310 _public prototype_ `void MeshEntitiesSelection(const TArray<TSharedPtr<FEntity>>& Entities, TArray<TSharedPtr<FEntity>>& OutMeshEntities) const;`
- L312 _public prototype_ `TSharedPtr<FEntity> GetFirstEntityOfType(EEntity Type) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Core/EntityGeom.h` (Public)


#### class `UE::CADKernel::FEntityGeom`  
`class FEntityGeom : public FEntity`  
_L14-44_
- inherits: `FEntity`
- L19 _protected member_ `FIdent CtKioId = 0;`
- L23 _public prototype_ `FEntityGeom() = default;`
- L25 _public function_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const`
- L30 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L36 _public function_ `FIdent GetKioId() const`
- L42 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity& Info) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Core/HaveStates.h` (Public)


#### enum `EHaveStates`  
`enum class EHaveStates : uint16`  
_L7-41_
- L9 _public enumerator_ `None = 0x0000u` — No flags.
- L11 _public enumerator_ `IsApplyCriteria = 0x0001u` — used for FTopologicalFace, FEdge
- L12 _public enumerator_ `IsMeshed = 0x0002u` — used for FTopologicalFace, FEdge
- L13 _public enumerator_ `IsPreMeshed = 0x0004u` — used for FTopologicalFace, FEdge
- L15 _public enumerator_ `ThinZone = 0x0008u` — used for FTopologicalFace, FEdge, FEdgeSegment
- L17 _public enumerator_ `Degenerated = 0x0010u` — used for FEdge, FGrid
- L19 _public enumerator_ `IsDeleted = 0x0020u` — used for all class
- L21 _public enumerator_ `IsVirtuallyMeshed = 0x0040u` — used for FEdge
- L23 _public enumerator_ `ThinPeak = 0x0080u` — used for FEdge
- L25 _public enumerator_ `IsBackOriented = 0x0100u` — used for FTopologicalFace
- L26 _public enumerator_ `IsInner = 0x0100u` — used for FEdgeSegment, FShell,
- L28 _public enumerator_ `FirstSideClosed = 0x0200u` — used for FThinZone2D
- L29 _public enumerator_ `SecondSideClosed = 0x0400u` — used for FThinZone2D
- L31 _public enumerator_ `HasMarker1 = 0x0800u` — used for all class
- L32 _public enumerator_ `HasMarker2 = 0x1000u` — used for all class
- L34 _public enumerator_ `ToProcess = 0x2000u` — used for all class
- L35 _public enumerator_ `IsWaiting = 0x4000u` — used for all class
- L36 _public enumerator_ `IsProcessed = 0x8000u` — used for all class
- L38 _public enumerator_ `AllMarkers = 0xF800u` — used for all class
- L40 _public enumerator_ `All = 0xFFFFu`

#### class `UE::CADKernel::FHaveStates`  
`class FHaveStates`  
_L47-219_
- L50 _protected member_ `mutable EHaveStates States;`
- L54 _public function_ `FHaveStates() : States(EHaveStates::None)`
- L58 _public function_ `void Serialize(FCADKernelArchive& Ar)`
- L63 _public function_ `void ResetElementStatus()`
- L68 _public function_ `bool HasMarker1() const`
- L73 _public function_ `bool HasMarker2() const`
- L83 _public function_ `bool HasMarker1And2() const`
- L89 _public function_ `bool HasMarker1Or2() const`
- L95 _public function_ `void SetMarker1() const`
- L100 _public function_ `void SetMarker2() const`
- L105 _public function_ `void ResetMarker1() const`
- L110 _public function_ `void ResetMarker2() const`
- L115 _public function_ `void ResetMarkers() const`
- L120 _public function_ `bool IsDeleted() const`
- L125 _public function_ `void SetDeletedMarker() const`
- L130 _public function_ `void ResetDeleted() const`
- L135 _public function_ `virtual bool IsDeletedOrDegenerated() const`
- L141 _public function_ `virtual bool IsDegenerated() const`
- L146 _public function_ `virtual void SetAsDegenerated() const`
- L151 _public function_ `virtual void ResetDegenerated() const`
- L156 _public function_ `void SetWaitingMarker() const`
- L161 _public function_ `void ResetWaitingMarker() const`
- L166 _public function_ `virtual bool IsWaiting() const`
- L171 _public function_ `void SetProcessedMarker() const`
- L176 _public function_ `void ResetProcessedMarker() const`
- L181 _public function_ `virtual bool IsProcessed() const`
- L186 _public function_ `virtual bool IsProcessedDeletedOrDegenerated() const`
- L193 _public function_ `void SetToProcessMarker() const`
- L198 _public function_ `void ResetToProcessMarker() const`
- L203 _public function_ `virtual bool IsToProcess() const`
- L208 _public function_ `virtual bool IsNotToProcess() const`
- L213 _public function_ `virtual bool IsNotToOrAlreadyProcess() const`

#### Free symbols / members of external scopes

- L43 _prototype_ `ENUM_CLASS_FLAGS(EHaveStates);`
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Core/MetadataDictionary.h` (Public)


#### class `UE::CADKernel::FMetadataDictionary`  
`class FMetadataDictionary`  
_L11-154_
- L14 _private member_ `FString Name;`
- L15 _private member_ `int32 HostId = 0;`
- L16 _private member_ `int32 PatchId = 0;`
- L17 _private member_ `uint32 ColorId = 0;`
- L18 _private member_ `uint32 MaterialId = 0;`
- L19 _private member_ `int32 LayerId = -1;`
- L22 _public prototype_ `FMetadataDictionary() = default;`
- L24 _public function_ `void Serialize(FCADKernelArchive& Ar)`
- L34 _public function_ `void CompleteDictionary(const FMetadataDictionary& MetaData)`
- L62 _public function_ `void ExtractMetaData(TMap<FString, FString>& OutMetaData) const`
- L90 _public function_ `void SetHostId(const int32 InHostId)`
- L95 _public function_ `const int32 GetHostId() const`
- L100 _public function_ `void SetLayer(const int32 InLayerId)`
- L105 _public function_ `int32 GetLayer() const`
- L110 _public function_ `void SetName(const FString& InName)`
- L115 _public function_ `bool HasName() const`
- L120 _public function_ `const TCHAR* GetName() const`
- L125 _public function_ `void SetColorId(const uint32& InColorId)`
- L130 _public function_ `uint32 GetColorId() const`
- L135 _public function_ `void SetMaterialId(const uint32& InMaterialId)`
- L140 _public function_ `uint32 GetMaterialId() const`
- L145 _public function_ `void SetPatchId(int32 InPatchId)`
- L150 _public function_ `int32 GetPatchId() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Core/OrientedEntity.h` (Public)


#### class `UE::CADKernel::TOrientedEntity`  
`template <typename KeyType> class TOrientedEntity`  
_L10-27_
- L13 _public member_ `TSharedPtr<KeyType> Entity;`
- L14 _public member_ `EOrientation Direction;`
- L16 _public function_ `TOrientedEntity(TSharedPtr<KeyType> InEntity, EOrientation InDirection) : Entity(InEntity) , Direction(InDirection)`
- L22 _public prototype_ `TOrientedEntity() = default;`
- L23 _public prototype_ `TOrientedEntity(TOrientedEntity&&) = default;`
- L24 _public prototype_ `TOrientedEntity(const TOrientedEntity&) = default;`
- L25 _public prototype_ `TOrientedEntity& operator=(TOrientedEntity&&) = default;`
- L26 _public prototype_ `TOrientedEntity& operator=(const TOrientedEntity&) = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Core/Session.h` (Public)


#### class `UE::CADKernel::FSession`  
`class FSession`  
_L17-167_
- L25 _protected member_ `double GeometricTolerance;`
- L26 _protected member_ `FDatabase Database;`
- L27 _protected member_ `int32 LastHostId;`
- L31 _public member_ `static FSession Session;`
- L34 _public function_ `FSession(double InGeometricTolerance) : GeometricTolerance(InGeometricTolerance)`
- L40 _public function_ `FModel& GetModel()`
- L41 _public prototype_ `TSharedPtr<FModel> GetModelAsShared();`
- L43 _public function_ `void Serialize(FCADKernelArchive& Ar)`
- L49 _public function_ `FDatabase& GetDatabase()`
- L57 _public prototype_ `void SetGeometricTolerance(double NewTolerance);` — Tolerance must not be modified as soon as a geometric entity has been build.
- L59 _public function_ `double GetGeometricTolerance() const`
- L69 _public prototype_ `bool SaveDatabase(const TCHAR* FilePath);` — Save the database as a FAchive in a file Mandatory: all entity have to have a defined ID Use SpawnEntityIdent if needed
- L76 _public prototype_ `void SaveDatabase(const TCHAR* FileName, const TArray<TSharedPtr<FEntity>>& Entities);` — Save a selection and all the dependencies as a FAchive in a file Mandatory: all entity have to have a defined ID Use SpawnEntityIdent if needed
- L83 _public prototype_ `void SaveDatabase(const TCHAR* FileName, const TArray<FEntity*>& Entities);` — Save a selection and all the dependencies as a FAchive in a file Mandatory: all entity have to have a defined ID Use SpawnEntityIdent if needed
- L90 _public function_ `void SaveDatabase(const TCHAR* FileName, FEntity& Entity)` — Save a selection and all the dependencies as a FAchive in a file Mandatory: all entity have to have a defined ID Use SpawnEntityIdent if needed
- L102 _public function_ `void SaveDatabase(const TCHAR* FileName, const TSharedPtr<FEntity> Entity)` — Save a selection and all the dependencies as a FAchive in a file Mandatory: all entity have to have a defined ID Use SpawnEntityIdent if needed
- L113 _public prototype_ `bool LoadDatabase(const TCHAR* FilePath);` — Load and add a database in the current session database Entity ID is set for all loaded entities
- L115 _public prototype_ `bool SaveDatabase(TArray<uint8>& Bytes);`
- L116 _public prototype_ `bool LoadDatabase(const TArray<uint8>& Bytes);`
- L122 _public prototype_ `void AddDatabase(const TArray<uint8>& InRawData);` — Add a database defined by a RawData in the current session database Entity ID is set for all loaded entities
- L124 _public function_ `void Clear()`
- L134 _public function_ `uint32 SpawnEntityIdent(FEntity& SelectedEntity, bool bForceSpawning = false)` — To be consistent,  all entity to save have to had an Id. This method browses all sub entities and set their Id if needed @param bForceSpawning If false, the process does not iterate through the children of entities with a defined ID
- L139 _public function_ `uint32 SpawnEntityIdents(const TArray<TSharedPtr<FEntity>>& SelectedEntities, bool bForceSpawning = false)`
- L144 _public function_ `uint32 SpawnEntityIdents(const TArray<FEntity*>& SelectedEntities, bool bForceSpawning = false)`
- L149 _public function_ `int32 GetLastHostId() const`
- L154 _public function_ `int32 NewHostId()`
- L163 _public function_ `void SetFirstNewHostId(int32 StartHostId)` — For stitching purpose, stitching can generate new body needing a host id. To avoid duplicate, the first generated host id can be set.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Core/Types.h` (Public)


#### struct `UE::CADKernel::FPairOfIndex`  
`struct FPairOfIndex`  
_L32-81_
- L34 _public member_ `int32 Value0;`
- L35 _public member_ `int32 Value1;`
- L37 _public function_ `FPairOfIndex(int32 InValue1, int32 InValue2) : Value0(InValue1) , Value1(InValue2)`
- L43 _public function_ `FPairOfIndex(int32 InValue1) : Value0(InValue1) , Value1(-1)`
- L49 _public function_ `int32& operator[](const int32 Index)`
- L54 _public function_ `const int32& operator[](const int32 Index) const`
- L59 _public function_ `void Add(const int32 Value)`
- L74 _public function_ `void Add(const FPairOfIndex Values)`
- L80 _public member_ `static const FPairOfIndex Undefined;`

#### enum `UE::CADKernel::EValue`  
`enum class EValue : uint8`  
_L88-101_
- L90 _public enumerator_ `Entity`
- L91 _public enumerator_ `OrientedEntity`
- L92 _public enumerator_ `Point`
- L93 _public enumerator_ `Matrix`
- L94 _public enumerator_ `Integer`
- L95 _public enumerator_ `Double`
- L96 _public enumerator_ `String`
- L97 _public enumerator_ `Boolean`
- L98 _public enumerator_ `Tuple`
- L99 _public enumerator_ `List`
- L100 _public enumerator_ `Array`

#### enum `UE::CADKernel::EVerboseLevel`  
`enum EVerboseLevel : uint8`  
_L103-109_
- L105 _public enumerator_ `NoVerbose = 0`
- L106 _public enumerator_ `Spy`
- L107 _public enumerator_ `Log`
- L108 _public enumerator_ `Debug`

#### Free symbols / members of external scopes

- L10 _macro_ `#define SMALL_NUMBER_SQUARE (1.e-16)`
- L11 _macro_ `#define DOUBLE_SMALL_NUMBER_SQUARE (1.e-16)`
- L13 _macro_ `#define KINDA_SMALL_NUMBER_SQUARE (1.e-8)`
- L14 _macro_ `#define DOUBLE_KINDA_SMALL_NUMBER_SQUARE (1.e-8)`
- L16 _macro_ `#define HUGE_VALUE (1e8)`
- L17 _macro_ `#define DOUBLE_HUGE_VALUE (1e8)`
- L19 _macro_ `#define HUGE_VALUE_SQUARE (1e16)`
- L20 _macro_ `#define DOUBLE_HUGE_VALUE_SQUARE (1e16)`
- L22 _variable_ `constexpr double AThird = 1. / 3.;`
- L23 _variable_ `constexpr double AQuarter = 0.25;`
- L24 _variable_ `constexpr double ASixth = 1. / 6.;`
- L25 _variable_ `constexpr double AEighth = 0.125;`
- L27 _typedef_ `typedef uint32 FIdent;`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace CADKernel` (scope `UE`)
- L83 _namespace_ `namespace Ident` (scope `UE::CADKernel`)
- L85 _variable_ `static const FIdent Undefined = (FIdent)-1;` (scope `UE::CADKernel::Ident`)
- L113 _macro_ `#define ensureCADKernel(InExpression) ensure(InExpression)`
- L115 _macro_ `#define ensureCADKernel(InExpression) (LIKELY(!!(InExpression)))`

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/Curves/Curve.h` (Public)


#### class `UE::CADKernel::FCurve`  
`class FCurve : public FEntityGeom`  
_L20-242_
- inherits: `FEntityGeom`
- L26 _protected member_ `mutable TCache<double> GlobalLength;`
- L27 _protected member_ `FLinearBoundary Boundary;`
- L29 _protected member_ `int8 Dimension;`
- L31 _protected function_ `FCurve(int8 InDimension = 3) : FEntityGeom() , Boundary() , Dimension(InDimension)`
- L38 _protected function_ `FCurve(const FLinearBoundary& InBounds, int8 InDimension = 3) : FEntityGeom() , Boundary(InBounds) , Dimension(InDimension)`
- L47 _public prototype_ `static TSharedPtr<FCurve> MakeNurbsCurve(FNurbsCurveData& InNurbsData);`
- L48 _public prototype_ `static TSharedPtr<FCurve> MakeBezierCurve(const TArray<FVector>& InPoles);`
- L49 _public prototype_ `static TSharedPtr<FCurve> MakeSplineCurve(const TArray<FVector>& InPoles);`
- L50 _public prototype_ `static TSharedPtr<FCurve> MakeSplineCurve(const TArray<FVector>& InPoles, const TArray<FVector>& Tangents);`
- L51 _public prototype_ `static TSharedPtr<FCurve> MakeSplineCurve(const TArray<FVector>& InPoles, const TArray<FVector>& ArriveTangents, const TArray<FVector>& LeaveTangents);`
- L60 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L76 _public prototype_ `static TSharedPtr<FEntity> Deserialize(FCADKernelArchive& Archive);` — Specific method for curve family to instantiate the correct derived class of FCurve
- L79 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L82 _public function_ `int32 GetDimension() const`
- L87 _public function_ `virtual EEntity GetEntityType() const override`
- L92 _public prototype_ `virtual ECurve GetCurveType() const = 0;`
- L94 _public function_ `double GetUMin() const`
- L99 _public function_ `double GetUMax() const`
- L104 _public function_ `const FLinearBoundary& GetBoundary() const`
- L109 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override = 0;`
- L110 _public prototype_ `virtual void Offset(const FVector& OffsetDirection) = 0;`
- L112 _public prototype_ `virtual double GetLength(double Tolerance) const;`
- L118 _public function_ `virtual void EvaluatePoint(double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder = 0) const` — Evaluate exact 3D point of the curve at the input Coordinate The function can only be used with 3D curve (Dimension == 3)
- L127 _public function_ `virtual FVector EvaluatePoint(double Coordinate) const` — Evaluate exact 3D point of the curve at the input Coordinate The function can only be used with 3D curve (Dimension == 3)
- L138 _public function_ `virtual void Evaluate2DPoint(double Coordinate, FCurvePoint2D& OutPoint, int32 DerivativeOrder = 0) const` — Evaluate exact 2D point of the curve at the input Coordinate The function can only be used with 2D curve (Dimension == 2)
- L147 _public function_ `virtual FVector2d Evaluate2DPoint(double Coordinate) const` — Evaluate exact 3D point of the curve at the input Coordinate The function can only be used with 3D curve (Dimension == 3)
- L158 _public function_ `virtual void Evaluate2DPoint(double Coordinate, FVector2d& OutPoint) const` — Evaluate exact 2D point of the curve at the input Coordinate The function can only be used with 2D curve (Dimension == 2)
- L170 _public prototype_ `virtual void EvaluatePoints(const TArray<double>& Coordinates, TArray<FCurvePoint>& OutPoints, int32 DerivativeOrder = 0) const;` — Evaluate exact 3D points of the curve at the input Coordinates The function can only be used with 3D curve (Dimension == 3)
- L176 _public prototype_ `virtual void EvaluatePoints(const TArray<double>& Coordinates, TArray<FVector>& OutPoints) const;` — Evaluate exact 3D points of the curve at the input Coordinates The function can only be used with 3D curve (Dimension == 3)
- L182 _public prototype_ `virtual void Evaluate2DPoints(const TArray<double>& Coordinates, TArray<FVector2d>& OutPoints) const;` — Evaluate exact 2D points of the curve at the input Coordinates The function can only be used with 2D curve (Dimension == 2)
- L188 _public prototype_ `virtual void Evaluate2DPoints(const TArray<double>& Coordinates, TArray<FCurvePoint2D>& OutPoints, int32 DerivativeOrder = 0) const;` — Evaluate exact 2D points of the curve at the input Coordinates The function can only be used with 2D curve (Dimension == 2)
- L190 _public function_ `void FindNotDerivableCoordinates(int32 DerivativeOrder, TArray<double>& OutNotDerivableCoordinates) const`
- L194 _public prototype_ `virtual void FindNotDerivableCoordinates(const FLinearBoundary& InBoundary, int32 DerivativeOrder, TArray<double>& OutNotDerivableCoordinates) const;`
- L201 _public function_ `void Presample(TArray<double>& OutSampling, double Tolerance) const` — Generate a pre-sampling of the curve saved in OutCoordinates. This sampling is light enough to allow a fast computation, precise enough to compute accurately meshing criteria
- L206 _public prototype_ `virtual void Presample(const FLinearBoundary& InBoundary, double Tolerance, TArray<double>& OutSampling) const;`
- L212 _public prototype_ `virtual TSharedPtr<FCurve> MakeBoundedCurve(const FLinearBoundary& InBoundary);` — Make a new curve based on the new bounds. If the new bound is nearly equal to the initial bound, no curve is made (return TSharedPtr<FCurve>())
- L217 _public prototype_ `virtual TSharedPtr<FCurve> Rebound(const FLinearBoundary& InBoundary);` — Rebound the curve, if not possible make a new curve based on the new bounds.
- L222 _public function_ `virtual void ExtendTo(const FVector& DesiredPosition)` — Linear deformation of the curve along the axis [Start point, End point] so that the nearest extremity is at the desired position and the other is not modified
- L231 _public function_ `virtual void ExtendTo(const FVector2d& DesiredPosition)` — Linear deformation of the curve along the axis [Start point, End point] so that the nearest extremity is at the desired position and the other is not modified
- L240 _protected prototype_ `virtual double ComputeLength(const FLinearBoundary& InBoundary, double Tolerance) const;`
- L241 _protected prototype_ `virtual double ComputeLength2D(const FLinearBoundary& InBoundary, double Tolerance) const;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/Curves/CurveUtilities.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)
- L13 _namespace_ `namespace CurveUtilities` (scope `UE::CADKernel`)
- L15 _prototype_ `int32 GetPoleCount(const UE::CADKernel::FCurve& Curve);` (scope `UE::CADKernel::CurveUtilities`)
- L16 _prototype_ `int32 GetPoleCount(const UE::CADKernel::FRestrictionCurve& Curve);` (scope `UE::CADKernel::CurveUtilities`)
- L18 _prototype_ `TArray<FVector> GetPoles(const UE::CADKernel::FCurve& Curve);` (scope `UE::CADKernel::CurveUtilities`)
- L19 _prototype_ `TArray<FVector2d> GetPoles(const UE::CADKernel::FRestrictionCurve& Curve);` (scope `UE::CADKernel::CurveUtilities`)
- L20 _prototype_ `TArray<FVector2d> Get2DPolyline(const UE::CADKernel::FRestrictionCurve& Curve);` (scope `UE::CADKernel::CurveUtilities`)
- L21 _prototype_ `TArray<FVector> Get3DPolyline(const UE::CADKernel::FRestrictionCurve& Curve);` (scope `UE::CADKernel::CurveUtilities`)
- L23 _prototype_ `int32 GetDegree(const UE::CADKernel::FCurve& Curve);` (scope `UE::CADKernel::CurveUtilities`)
- L24 _prototype_ `int32 GetDegree(const UE::CADKernel::FRestrictionCurve& Curve);` (scope `UE::CADKernel::CurveUtilities`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/Curves/NURBSCurveData.h` (Public)


#### struct `UE::CADKernel::FNurbsCurveData`  
`struct FNurbsCurveData`  
_L9-19_
- L11 _public member_ `bool bIsRational;`
- L12 _public member_ `int32 Dimension = 0;`
- L14 _public member_ `int32 Degree = 0;`
- L15 _public member_ `TArray<double> NodalVector;`
- L17 _public member_ `TArray<double> Weights;`
- L18 _public member_ `TArray<FVector> Poles;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/Curves/RestrictionCurve.h` (Public)


#### class `UE::CADKernel::FRestrictionCurve`  
`class FRestrictionCurve : public FSurfacicCurve`  
_L32-280_
- inherits: `FSurfacicCurve`
- desc: A restriction curve is the curve carrying an edge It's defined by - A surfacic curve defined by a 2D curve (@see Curve2D) and the carrier surface (@see CarrierSurface) of the TopologicalFace containing the edge: - A linear approximation of the surfacic curve (@see Polyline) respecting the System Geometrical Tolerance (@see FKernelParameters::GeometricalTolerance) The linear approximation is: - an array of increasing coordinates (@see Polyline::Coordinates) - an array of 2D Points relating to coordinates: points of curve in the parametric space of the carrier surface (@see Polyline::Points2D) - an array of 3D Points relating to coordinates: 3D points of curve (@see Polyline::Points3D) - an array of Normal relating to coordinates: Surface's normal (@see Polyline::Normal)
- L39 _protected member_ `FSurfacicPolyline Polyline;`
- L40 _protected member_ `double MinLinearTolerance;`
- L42 _protected function_ `FRestrictionCurve(TSharedRef<FSurface> InCarrierSurface, TSharedRef<FCurve> InCurve2D) : FSurfacicCurve(InCurve2D, InCarrierSurface) , Polyline(InCarrierSurface, InCurve2D)`
- L49 _protected prototype_ `FRestrictionCurve() = default;`
- L53 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L64 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L67 _public function_ `virtual ECurve GetCurveType() const override`
- L72 _public function_ `const FSurfacicPolyline& GetPolyline() const`
- L77 _public function_ `const TSharedRef<FCurve> Get2DCurve() const`
- L82 _public function_ `double GetMinLinearTolerance() const`
- L87 _public function_ `TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override`
- L97 _public function_ `FVector2d Approximate2DPoint(double InCoordinate) const` — Fast computation of the point in the parametric space of the carrier surface. This approximation is based on FSurfacicPolyline::Polyline
- L106 _public function_ `FVector Approximate3DPoint(double InCoordinate) const` — Fast computation of the point in the parametric space of the carrier surface. This approximation is based on FSurfacicPolyline::Polyline
- L111 _public function_ `FVector GetTangentAt(double InCoordinate) const`
- L116 _public function_ `FVector2d GetTangent2DAt(double InCoordinate) const`
- L125 _public function_ `void Approximate2DPoints(const TArray<double>& InCoordinates, TArray<FVector2d>& OutPoints) const` — Fast computation of the point in the parametric space of the carrier surface. This approximation is based on FSurfacicPolyline::Polyline
- L134 _public function_ `void Approximate3DPoints(const TArray<double>& InCoordinates, TArray<FVector>& OutPoints) const` — Fast computation of the 3D point of the curve. This approximation is based on FSurfacicPolyline::Polyline
- L142 _public function_ `void ApproximatePolyline(FSurfacicPolyline& OutPolyline) const` — Approximation of surfacic polyline (points 2d, 3d, normals, tangents) defined by its coordinates compute with carrier surface polyline
- L148 _public function_ `template<class PointType> double GetCoordinateOfProjectedPoint(const FLinearBoundary& InBoundary, const PointType& PointOnEdge, PointType& ProjectedPoint) const`
- L154 _public function_ `template<class PointType> void ProjectPoints(const FLinearBoundary& InBoundary, const TArray<PointType>& InPointsToProject, TArray<double>& ProjectedPointCoordinates, TArray<PointType>& ProjectedPoints) const`
- L163 _public function_ `void ProjectTwinCurvePoints(const FLinearBoundary& InBoundary, const TArray<FVector>& InPointsToProject, bool bSameOrientation, TArray<double>& OutProjectedPointCoords, double ToleranceOfProjection) const` — Project a set of points of a twin curve on the 3D polyline and return the coordinate of the projected point @param ToleranceOfProjection: Max error between the both curve to stop the search of projection of a point
- L168 _public function_ `void ComputeIntersectionsWithIsos(const FLinearBoundary& InBoundary, const TArray<double>& InIsoCoordinates, const EIso InTypeIso, const FSurfacicTolerance& ToleranceIso, TArray<double>& OutIntersection) const`
- L180 _public function_ `void CheckIfDegenerated(const FLinearBoundary& InBoundary, bool& bDegeneration2D, bool& bDegeneration3D, double& Length3D) const` — A check is done to verify that: - the curve is degenerated in the parametric space of the carrier surface i.e. the 2D length of the curve is not nearly equal to zero - the curve is degenerated in 3D i.e. the 3D length of the curve is not nearly equal to zero A curve can be degenerated in 3D and not in 2D in the case of locally degenerated carrier surface.
- L194 _public function_ `void GetExtremities(const FLinearBoundary& InBoundary, FSurfacicCurveExtremities& Extremities) const`
- L201 _public function_ `double GetToleranceAt(const double InCoordinate)`
- L210 _public function_ `FVector2d GetExtremityTolerances(const FLinearBoundary& InBoundary)`
- L227 _public function_ `int32 GetPolylineSize()` — @return the size of the polyline i.e. the count of points.
- L236 _public function_ `template<class PointType> void GetDiscretizationPoints(const FLinearBoundary& InBoundary, EOrientation Orientation, TArray<PointType>& OutPoints) const` — Get the sub polyline bounded by the input InBoundary in the orientation of the input InOrientation and append it to the output OutPoints
- L245 _public function_ `template<class PointType> void GetDiscretizationPoints(const FLinearBoundary& InBoundary, TArray<double>& OutCoordinates, TArray<PointType>& OutPoints) const` — Get the sub polyline bounded by the input InBoundary in the orientation of the input InOrientation and append it to the output OutPoints
- L253 _public function_ `void Sample(const FLinearBoundary& InBoundary, const double DesiredSegmentLength, TArray<double>& OutCoordinates) const` — Samples the sub curve limited by the boundary respecting the input Desired segment length
- L258 _public function_ `double ApproximateLength(const FLinearBoundary& InBoundary) const`
- L263 _public prototype_ `void ExtendTo(const FVector2d& Point) override;`
- L265 _public function_ `bool IsIso(EIso Iso, double ErrorTolerance = DOUBLE_SMALL_NUMBER) const`
- L270 _public prototype_ `void Offset2D(const FVector2d& OffsetDirection);`
- L275 _public function_ `virtual void Offset(const FVector& OffsetDirection) override` — must not be call

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/Curves/SurfacicCurve.h` (Public)


#### class `UE::CADKernel::FSurfacicCurve`  
`class FSurfacicCurve : public FCurve`  
_L21-146_
- inherits: `FCurve`
- L27 _protected member_ `TSharedPtr<FCurve> Curve2D;`
- L28 _protected member_ `TSharedPtr<FSurface> CarrierSurface;`
- L30 _protected function_ `FSurfacicCurve(TSharedRef<FCurve> InCurve2D, TSharedRef<FSurface> InSurface) : FCurve(InCurve2D->GetBoundary()) , Curve2D(InCurve2D) , CarrierSurface(InSurface)`
- L38 _protected prototype_ `FSurfacicCurve() = default;`
- L42 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L49 _public function_ `virtual void SpawnIdent(FDatabase& Database) override`
- L60 _public function_ `virtual void ResetMarkersRecursively() const override`
- L68 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L71 _public function_ `virtual ECurve GetCurveType() const override`
- L76 _public function_ `const TSharedPtr<FCurve>& Get2DCurve() const`
- L81 _public function_ `TSharedPtr<FCurve>& Get2DCurve()`
- L86 _public function_ `const TSharedRef<FSurface> GetCarrierSurface() const`
- L91 _public function_ `void Set2DCurve(TSharedPtr<FCurve>& NewCurve2D)`
- L97 _public function_ `const TSharedPtr<FSurface>& GetSurface() const`
- L102 _public function_ `TSharedPtr<FSurface>& GetSurface()`
- L107 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const override;`
- L112 _public function_ `virtual void Offset(const FVector& OffsetDirection) override` — Must not be call
- L117 _public prototype_ `virtual void EvaluatePoint(double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder = 0) const override;`
- L119 _public function_ `virtual void Evaluate2DPoint(double Coordinate, FCurvePoint2D& OutPoint, int32 DerivativeOrder = 0) const override`
- L124 _public function_ `virtual void Evaluate2DPoint(double Coordinate, FVector2d& OutPoint) const override`
- L129 _public prototype_ `virtual void EvaluatePoints(const TArray<double>& Coordinates, TArray<FCurvePoint>& OutPoints, int32 DerivativeOrder = 0) const override;`
- L131 _public prototype_ `void EvaluateSurfacicPolyline(FSurfacicPolyline& OutPolyline) const;`
- L133 _public function_ `virtual void Evaluate2DPoints(const TArray<double>& Coordinates, TArray<FVector2d>& OutPoints) const override`
- L138 _public function_ `virtual void Evaluate2DPoints(const TArray<double>& Coordinates, TArray<FCurvePoint2D>& OutPoints, int32 DerivativeOrder = 0) const override`
- L143 _public prototype_ `virtual void FindNotDerivableCoordinates(const FLinearBoundary& InBoundary, int32 DerivativeOrder, TArray<double>& OutNotDerivableCoordinates) const override;`
- L145 _private prototype_ `void EvaluateSurfacicPolylineWithNormalAndTangent(FSurfacicPolyline& OutPolyline) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/GeoEnum.h` (Public)


#### enum `UE::CADKernel::ECurve`  
`enum class ECurve : uint8`  
_L9-27_
- L11 _public enumerator_ `Bezier = 0`
- L12 _public enumerator_ `BoundedCurve`
- L13 _public enumerator_ `Composite`
- L14 _public enumerator_ `Ellipse`
- L15 _public enumerator_ `Hyperbola`
- L16 _public enumerator_ `Nurbs`
- L17 _public enumerator_ `Offset`
- L18 _public enumerator_ `Parabola`
- L19 _public enumerator_ `Polyline3D`
- L20 _public enumerator_ `Polyline2D`
- L21 _public enumerator_ `Restriction`
- L22 _public enumerator_ `Segment`
- L23 _public enumerator_ `Surfacic`
- L24 _public enumerator_ `SurfacicPolyline`
- L25 _public enumerator_ `Spline`
- L26 _public enumerator_ `None`

#### enum `UE::CADKernel::ESurface`  
`enum class ESurface : uint8`  
_L33-52_
- L35 _public enumerator_ `Bezier = 0`
- L36 _public enumerator_ `Blend01`
- L37 _public enumerator_ `Blend02`
- L38 _public enumerator_ `Blend03`
- L39 _public enumerator_ `Composite`
- L40 _public enumerator_ `Cone`
- L41 _public enumerator_ `Coons`
- L42 _public enumerator_ `Cylinder`
- L43 _public enumerator_ `Nurbs`
- L44 _public enumerator_ `Offset`
- L45 _public enumerator_ `Plane`
- L46 _public enumerator_ `Revolution`
- L47 _public enumerator_ `Ruled`
- L48 _public enumerator_ `Sphere`
- L49 _public enumerator_ `TabulatedCylinder`
- L50 _public enumerator_ `Torus`
- L51 _public enumerator_ `None`

#### enum `UE::CADKernel::ERupture`  
`enum class ERupture : uint8`  
_L58-63_
- L60 _public enumerator_ `Continuity = 0` — Positional rupture i.e. points of the curve that are not G0
- L61 _public enumerator_ `Tangency` — Tangency rupture i.e. points of the curve that are not G1 (or G0)
- L62 _public enumerator_ `Curvature` — Curvature rupture i.e. points of the curve that are not G2 (or G1, G0)

#### enum `UE::CADKernel::EIso`  
`enum EIso : uint8`  
_L65-70_
- L67 _public enumerator_ `IsoU = 0`
- L68 _public enumerator_ `IsoV = 1`
- L69 _public enumerator_ `UndefinedIso`

#### enum `UE::CADKernel::EOrientation`  
`enum EOrientation : uint8`  
_L81-85_
- L83 _public enumerator_ `Back = 0`
- L84 _public enumerator_ `Front = 1`

#### enum `UE::CADKernel::ESituation`  
`enum ESituation : uint8`  
_L87-92_
- L89 _public enumerator_ `Undefined = 0`
- L90 _public enumerator_ `Inside`
- L91 _public enumerator_ `Outside`

#### enum `UE::CADKernel::ELimit`  
`enum ELimit : uint8`  
_L98-102_
- L100 _public enumerator_ `Start = 0`
- L101 _public enumerator_ `End = 1`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)
- L30 _externvar_ `extern const TCHAR* CurvesTypesNames[];` (scope `UE::CADKernel`)
- L55 _externvar_ `extern const TCHAR* SurfacesTypesNames[];` (scope `UE::CADKernel`)
- L73 _externvar_ `extern const TCHAR* IsoNames[];` (scope `UE::CADKernel`)
- L76 _function_ `constexpr EIso Other(const EIso Iso)` (scope `UE::CADKernel`)
- L95 _externvar_ `extern const TCHAR* OrientationNames[];` (scope `UE::CADKernel`)
- L104 _function_ `inline EOrientation SameOrientation(bool bIsSameOrientation)` (scope `UE::CADKernel`)
- L116 _function_ `inline EOrientation GetReverseOrientation(EOrientation Orientation)` (scope `UE::CADKernel`)
- L128 _function_ `inline void SwapOrientation(EOrientation& Orientation)` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/GeoPoint.h` (Public)


#### struct `UE::CADKernel::FCurvePoint2D`  
`struct FCurvePoint2D`  
_L10-16_
- L12 _public member_ `int32 DerivativeOrder = -1;`
- L13 _public member_ `FVector2d Point = FVector2d::ZeroVector;`
- L14 _public member_ `FVector2d Gradient = FVector2d::ZeroVector;`
- L15 _public member_ `FVector2d Laplacian = FVector2d::ZeroVector;`

#### struct `UE::CADKernel::FSurfacicPoint`  
`struct FSurfacicPoint`  
_L18-27_
- L20 _public member_ `int32 DerivativeOrder = -1;`
- L21 _public member_ `FVector Point = FVector::ZeroVector;`
- L22 _public member_ `FVector GradientU = FVector::ZeroVector;`
- L23 _public member_ `FVector GradientV = FVector::ZeroVector;`
- L24 _public member_ `FVector LaplacianU = FVector::ZeroVector;`
- L25 _public member_ `FVector LaplacianV = FVector::ZeroVector;`
- L26 _public member_ `FVector LaplacianUV = FVector::ZeroVector;`

#### struct `UE::CADKernel::FSurfacicCurvePoint`  
`struct FSurfacicCurvePoint`  
_L29-38_
- L31 _public member_ `bool bWithNormals;`
- L32 _public member_ `bool bWithTangent;`
- L34 _public member_ `FVector2d Point2D = FVector2d::ZeroVector;`
- L35 _public member_ `FVector Point = FVector::ZeroVector;`
- L36 _public member_ `FVector Normal = FVector::ZeroVector;`
- L37 _public member_ `FVector Tangent = FVector::ZeroVector;`

#### struct `UE::CADKernel::FSurfacicCurvePointWithTolerance`  
`struct FSurfacicCurvePointWithTolerance`  
_L40-45_
- L42 _public member_ `FVector2d Point2D = FVector2d::ZeroVector;`
- L43 _public member_ `FVector Point = FVector::ZeroVector;`
- L44 _public member_ `FSurfacicTolerance Tolerance = FVectorUtil::FarawayPoint2D;`

#### struct `UE::CADKernel::FCurvePoint`  
`struct FCurvePoint`  
_L49-100_
- L51 _public member_ `int32 DerivativeOrder = -1;`
- L52 _public member_ `FVector Point = FVector::ZeroVector;`
- L53 _public member_ `FVector Gradient = FVector::ZeroVector;`
- L54 _public member_ `FVector Laplacian = FVector::ZeroVector;`
- L56 _public prototype_ `FCurvePoint() = default;`
- L58 _public function_ `FCurvePoint(FVector InPoint) : Point(InPoint)`
- L65 _public function_ `void Init()`
- L76 _public function_ `void Combine(const FCurvePoint2D& Point2D, const FSurfacicPoint& SurfacicPoint)` — Compute the 3D surface curve point property (3D Coordinate, Gradient, Laplacian) according to its 2D curve point property and the 3D surface point property

#### struct `UE::CADKernel::FCoordinateGrid`  
`struct FCoordinateGrid`  
_L102-155_
- L104 _public member_ `TArray<double> Coordinates[2];`
- L106 _public function_ `FCoordinateGrid()`
- L110 _public function_ `FCoordinateGrid(const TArray<double>& InUCoordinates, const TArray<double>& InVCoordinates)`
- L116 _public function_ `void Swap(TArray<double>& InUCoordinates, TArray<double>& InVCoordinates)`
- L122 _public function_ `int32 Count() const`
- L127 _public function_ `int32 IsoCount(EIso Iso) const`
- L132 _public function_ `void SetNum(int32 UNumber, int32 VNumber)`
- L138 _public function_ `void Empty(int32 UNumber = 0, int32 VNumber = 0)`
- L144 _public function_ `constexpr TArray<double>& operator[](EIso Iso)`
- L150 _public function_ `constexpr const TArray<double>& operator[](EIso Iso) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)
- L47 _typedef_ `typedef FSurfacicCurvePointWithTolerance FSurfacicCurveExtremities[2];` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/Sampling/Polyline.h` (Public)


#### class `UE::CADKernel::TPolyline`  
`template<class PointType> class TPolyline`  
_L15-198_
- L19 _public member_ `TArray<double> Coordinates;`
- L20 _public member_ `TArray<PointType> Points;`
- L21 _public member_ `TArray<PointType> Tangent;`
- L22 _public member_ `TPolylineApproximator<PointType> Approximator;`
- L23 _public member_ `bool bWithTangent = false;`
- L26 _public function_ `TPolyline(const TArray<PointType>& InPoints, const TArray<double>& InCoordinates) : Coordinates(InCoordinates) , Points(InPoints) , Approximator(Coordinates, Points)`
- L33 _public function_ `TPolyline(const TArray<PointType>& InPoints) : Points(InPoints) , Approximator(Coordinates, Points)`
- L39 _public function_ `TPolyline() : Approximator(Coordinates, Points)`
- L44 _public function_ `void Serialize(FCADKernelArchive& Ar)`
- L50 _public function_ `PointType ApproximatePoint(double InCoordinate) const`
- L55 _public function_ `void ApproximatePoints(const TArray<double>& InCoordinates, TArray<PointType>& OutPoints) const`
- L60 _public function_ `void GetSubPolyline(const FLinearBoundary& InBoundary, const EOrientation InOrientation, TArray<PointType>& OutPoints) const`
- L68 _public function_ `void UpdateSubPolylineBBox(const FLinearBoundary& InBoundary, FPolylineBBox& OutBBox) const` — The FPolylineBBox is updated by adding all the points of the polyline included in the boundary
- L73 _public function_ `void Sample(const FLinearBoundary& Boundary, const double DesiredSegmentLength, TArray<double>& OutCoordinates) const`
- L78 _public function_ `double GetCoordinateOfProjectedPoint(const FLinearBoundary& Boundary, const PointType& PointOnEdge, PointType& ProjectedPoint) const`
- L83 _public function_ `void ProjectPoints(const FLinearBoundary& InBoundary, const TArray<PointType>& InPointsToProject, TArray<double>& ProjectedPointCoordinates, TArray<PointType>& ProjectedPoints) const`
- L88 _public function_ `const PointType& GetPointAt(int32 Index) const`
- L93 _public function_ `const TArray<PointType>& GetPoints() const`
- L98 _public function_ `const TArray<double>& GetCoordinates() const`
- L103 _public function_ `TArray<double>& GetCoordinates()`
- L108 _public function_ `void SwapCoordinates(TArray<double>& NewCoordinates)`
- L118 _public function_ `void GetAt(int32 Index, double& Coordinate, PointType& Point)`
- L128 _public function_ `int32 Size() const` — @return the size of the polyline i.e. the count of points.
- L138 _public function_ `void Reserve(int32 Number)` — Reserves memory such that the polyline can contain at least Number elements. @param Number The number of elements that the polyline should be able to contain after allocation.
- L149 _public function_ `void Empty(int32 Slack = 0)` — Empties the polyline. @param Slack (Optional) The expected usage size after empty operation. Default is 0.
- L155 _public function_ `void EmplaceAt(int32 Index, TPolyline<PointType>& Polyline, int32 PointIndex)`
- L162 _public function_ `void RemoveComplementaryPoints(int32 Offset)`
- L188 _public function_ `void Pop()`
- L194 _public function_ `double GetLength(const FLinearBoundary& InBoundary) const`

#### class `UE::CADKernel::FPolyline2D`  
`class FPolyline2D : public TPolyline<FVector2d>`  
_L202-240_
- inherits: `TPolyline<FVector2d>`
- L209 _public function_ `void FindIntersectionsWithIso(const EIso Iso, double IsoParameter, TArray<double>& OutIntersections)` — Add to OutIntersection the curve coordinate of the intersection with the Iso curve

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CADKernel` (scope `UE`)
- L200 _typedef_ `typedef TPolyline<FVector> FPolyline3D;` (scope `UE::CADKernel`)
- L217 _function_ `` (scope `UE::CADKernel::FPolyline2D::FindIntersectionsWithIso`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/Sampling/PolylineTools.h` (Public)


#### struct `UE::CADKernel::FPolylineBBox`  
`struct FPolylineBBox`  
_L19-58_
- L21 _public member_ `FVector Max;`
- L22 _public member_ `FVector Min;`
- L23 _public member_ `FVector MaxPoints[3];`
- L24 _public member_ `FVector MinPoints[3];`
- L25 _public member_ `double CoordinateOfMaxPoint[3] = { -HUGE_VALUE, -HUGE_VALUE, -HUGE_VALUE };`
- L26 _public member_ `double CoordinateOfMinPoint[3] = { HUGE_VALUE, HUGE_VALUE, HUGE_VALUE };`
- L28 _public function_ `FPolylineBBox() : Max(-HUGE_VALUE, -HUGE_VALUE, -HUGE_VALUE) , Min(HUGE_VALUE, HUGE_VALUE, HUGE_VALUE)`
- L34 _public function_ `void Update(const double Coordinate, const FVector& Point)`
- L54 _public function_ `void Update(const double Coordinate, const FVector2d& Point2D)`

#### class `UE::CADKernel::TPolylineApproximator`  
`template<class PointType> class TPolylineApproximator`  
_L193-830_
- L196 _protected member_ `const TArray<double>& PolylineCoordinates;`
- L197 _protected member_ `const TArray<PointType>& PolylinePoints;`
- L200 _public function_ `TPolylineApproximator(const TArray<double>& InPolylineCoordinates, const TArray<PointType>& InPolylinePoints) : PolylineCoordinates(InPolylineCoordinates) , PolylinePoints(InPolylinePoints)`
- L208 _protected function_ `double ComputeCurvilinearCoordinatesOfPolyline(const FLinearBoundary& InBoundary, TArray<double>& OutCurvilinearCoordinates, int32 BoundaryIndices[2]) const`
- L256 _protected function_ `PointType ComputePoint(const int32 Index, const double PointCoordinate) const`
- L271 _protected function_ `double ProjectPointToPolyline(int32 BoundaryIndices[2], const PointType& InPointToProject, PointType& OutProjectedPoint) const` — Project a Set of points on a restricted polyline (StartIndex & EndIndex define the polyline boundary) the points are projected on all segments of the polyline, the closest are selected
- L308 _public function_ `void GetStartEndIndex(const FLinearBoundary& InBoundary, int32 BoundaryIndices[2]) const`
- L319 _public function_ `PointType ApproximatePoint(const double InCoordinate) const` — Evaluate the point of the polyline at the input InCoordinate If the input coordinate is outside the boundary of the polyline, the coordinate of the nearest boundary is used.
- L331 _public function_ `template<class CurvePointType> void ApproximatePoint(double InCoordinate, CurvePointType& OutPoint, int32 InDerivativeOrder) const` — Evaluate the point of the polyline at the input Coordinate If the input coordinate is outside the boundary of the polyline, the coordinate of the nearest boundary is used.
- L360 _public function_ `template<class CurvePointType> void ApproximatePoints(const TArray<double>& InCoordinates, TArray<CurvePointType>& OutPoints, int32 InDerivativeOrder = 0) const`
- L423 _public function_ `void ApproximatePoints(const TArray<double>& InCoordinates, TArray<PointType>& OutPoints) const` — Evaluate the points of the polyline associated to the increasing array of input Coordinates If the input coordinate is outside the boundary of the polyline, the coordinate of the nearest boundary is used.
- L459 _public function_ `void SamplePolyline(const FLinearBoundary& InBoundary, const double DesiredSegmentLength, TArray<double>& OutCoordinates) const`
- L526 _public function_ `double ProjectPointToPolyline(const FLinearBoundary& InBoundary, const PointType& PointOnEdge, PointType& OutProjectedPoint) const` — Project a Set of points on a restricted polyline (StartIndex & EndIndex define the polyline boundary) the points are projected on all segments of the polyline, the closest are selected
- L552 _public function_ `void ProjectPointsToPolyline(const FLinearBoundary& InBoundary, const TArray<PointType>& InPointsToProject, TArray<double>& OutProjectedPointCoords, TArray<PointType>& OutProjectedPoints) const` — Project a Set of points on a restricted polyline (StartIndex & EndIndex define the polyline boundary) Each points are projected on all segments of the restricted polyline, the closest are selected
- L575 _public function_ `void ProjectCoincidentalPolyline(const FLinearBoundary& InBoundary, const TArray<PointType>& InPointsToProject, bool bSameOrientation, TArray<double>& OutProjectedPointCoords, const double ToleranceOfProjection) const` — Project each point of a coincidental polyline on the Polyline. @param ToleranceOfProjection: Max error between the both curve to stop the search of projection if ToleranceOfProjection < 0, it's compute with ComputeSquareToleranceForProjection
- L673 _public function_ `void GetSubPolyline(const FLinearBoundary& InBoundary, const EOrientation Orientation, TArray<PointType>& OutPoints) const` — Append to the OutPoints array the sub polyline bounded by InBoundary according to the orientation
- L716 _public function_ `void GetSubPolyline(const FLinearBoundary& InBoundary, TArray<double>& OutCoordinates, TArray<PointType>& OutPoints) const` — Get the subset of point defining the sub polyline bounded by InBoundary OutCoordinates and OutPoints are emptied before the process
- L748 _public function_ `void UpdateSubPolylineBBox(const FLinearBoundary& InBoundary, FPolylineBBox& OutBBox) const` — Update the Curve bounding box with this subset of polyline
- L774 _public function_ `double ComputeLength() const`
- L779 _public function_ `double ComputeLengthOfSubPolyline(const int BoundaryIndex[2], const FLinearBoundary& InBoundary) const`
- L806 _public function_ `double ComputeLengthOfSubPolyline(const FLinearBoundary& InBoundary) const`
- L814 _public function_ `template<int Dimension = 3> void ComputeBoundingBox(const int BoundaryIndex[2], const FLinearBoundary& InBoundary, TAABB<PointType, Dimension>& Aabb)`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace CADKernel` (scope `UE`)
- L60 _namespace_ `namespace PolylineTools` (scope `UE::CADKernel`)
- L63 _function_ `inline bool IsDichotomyToBePreferred(int32 InPolylineSize, int32 ResultSize)` (scope `UE::CADKernel::PolylineTools`)
- L76 _function_ `template<typename PointType> inline PointType LinearInterpolation(const TArray<PointType>& Array, const int32 Index, const double Coordinate)` (scope `UE::CADKernel::PolylineTools`)
- L82 _function_ `inline double SectionCoordinate(const TArray<double>& Array, const int32 Index, const double Coordinate)` (scope `UE::CADKernel::PolylineTools`)
- L94 _function_ `template<typename PointType> double ComputeLength(const TArray<PointType>& Polyline)` (scope `UE::CADKernel::PolylineTools`)
- L105 _function_ `template<typename PointType> double ComputeSquareToleranceForProjection(const TArray<PointType>& Polyline)` (scope `UE::CADKernel::PolylineTools`)
- L112 _function_ `template<typename PointType> TArray<double> ComputePolylineSegmentLengths(const PointType& StartPoint, const TArray<PointType>& InnerPolyline, const PointType& EndPoint)` (scope `UE::CADKernel::PolylineTools`)
- L147 _function_ `template<typename PointType> void ExtendTo(TArray<PointType>& Polyline, const PointType& DesiredEnd)` (scope `UE::CADKernel::PolylineTools`) — Progressively deforms a polyline (or a control polygon) so that its end is in the desired position
- L179 _function_ `template<class PointType> PointType ComputePoint(const TArray<double>& PolylineCoordinates, const TArray<PointType>& PolylinePoints, const int32 Index, const double PointCoordinate)` (scope `UE::CADKernel::PolylineTools`)
- L369 _function_ `` (scope `UE::CADKernel::TPolylineApproximator::ApproximatePoints`)
- L487 _function_ `` (scope `UE::CADKernel::TPolylineApproximator::SamplePolyline`)
- L604 _function_ `` (scope `UE::CADKernel::TPolylineApproximator::ProjectCoincidentalPolyline`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/Sampling/SurfacicPolyline.h` (Public)


#### class `UE::CADKernel::FSurfacicPolyline`  
`class FSurfacicPolyline`  
_L28-500_
- L33 _public member_ `TArray<double> Coordinates;`
- L34 _public member_ `TArray<FVector2d> Points2D;`
- L35 _public member_ `TArray<FVector> Points3D;`
- L36 _public member_ `TArray<FVector3f> Normals;`
- L37 _public member_ `TArray<FVector> Tangents;`
- L39 _public member_ `FSurfacicBoundary BoundingBox;`
- L41 _public member_ `bool bWithNormals;`
- L42 _public member_ `bool bWithTangent;`
- L44 _public prototype_ `FSurfacicPolyline(TSharedRef<FSurface> InCarrierSurface, TSharedRef<FCurve> InCurve2D);`
- L46 _public prototype_ `FSurfacicPolyline(TSharedRef<FSurface> InCarrierSurface, TSharedRef<FCurve> InCurve2D, const double Tolerance);`
- L48 _public prototype_ `FSurfacicPolyline(TSharedRef<FSurface> InCarrierSurface, TSharedRef<FCurve> InCurve2D, const double ChordTolerance, const double ParamTolerance, bool bInWithNormals , bool bWithTangent );`
- L50 _public function_ `FSurfacicPolyline(bool bInWithNormals = false, bool bInWithTangent = false) : bWithNormals(bInWithNormals) , bWithTangent(bInWithTangent)`
- L56 _public function_ `void Serialize(FCADKernelArchive& Ar)`
- L67 _public prototype_ `FInfoEntity& GetInfo(FInfoEntity&) const;`
- L69 _public prototype_ `TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH&) const;`
- L71 _public prototype_ `void CheckIfDegenerated(const double Tolerance3D, const FSurfacicTolerance& Tolerances2D, const FLinearBoundary& Boudary, bool& bDegeneration2D, bool& bDegeneration3D, double& Length3D) const;`
- L73 _public prototype_ `void GetExtremities(const FLinearBoundary& InBoundary, const double Tolerance3D, const FSurfacicTolerance& Tolerances2D, FSurfacicCurveExtremities& Extremities) const;`
- L75 _public function_ `FVector Approximate3DPoint(double InCoordinate) const`
- L81 _public function_ `void Approximate3DPoints(const TArray<double>& InCoordinates, TArray<FVector>& OutPoints) const`
- L87 _public function_ `FVector2d Approximate2DPoint(double InCoordinate) const`
- L93 _public function_ `FVector GetTangentAt(double InCoordinate) const`
- L100 _public function_ `FVector2d GetTangent2DAt(double InCoordinate) const`
- L107 _public function_ `FSurfacicTolerance ComputeTolerance(const double Tolerance3D, const FSurfacicTolerance& MinToleranceIso, const int32 Index) const`
- L121 _public function_ `double ComputeLinearToleranceAt(const double Tolerance3D, const double MinLinearTolerance, const int32 Index) const`
- L135 _public function_ `void Approximate2DPoints(const TArray<double>& InCoordinates, TArray<FVector2d>& OutPoints) const`
- L141 _public function_ `void ApproximatePolyline(FSurfacicPolyline& OutPolyline) const`
- L227 _public function_ `void Sample(const FLinearBoundary& Boundary, const double DesiredSegmentLength, TArray<double>& OutCoordinates) const`
- L233 _public function_ `double GetCoordinateOfProjectedPoint(const FLinearBoundary& Boundary, const FVector& PointOnEdge, FVector& ProjectedPoint) const`
- L239 _public function_ `double GetCoordinateOfProjectedPoint(const FLinearBoundary& Boundary, const FVector2d& PointOnEdge, FVector2d& ProjectedPoint) const`
- L245 _public function_ `void ProjectPoints(const FLinearBoundary& InBoundary, const TArray<FVector>& InPointsToProject, TArray<double>& ProjectedPointCoordinates, TArray<FVector>& ProjectedPoints) const`
- L251 _public function_ `void ProjectPoints(const FLinearBoundary& InBoundary, const TArray<FVector2d>& InPointsToProject, TArray<double>& ProjectedPointCoordinates, TArray<FVector2d>& ProjectedPoints) const`
- L261 _public function_ `void ProjectCoincidentalPolyline(const FLinearBoundary& InBoundary, const TArray<FVector>& InPointsToProject, bool bSameOrientation, TArray<double>& OutProjectedPointCoordinates, double ToleranceOfProjection) const` — Project each point of a coincidental polyline on the Polyline. @param ToleranceOfProjection: Max error between the both curve to stop the search of projection
- L270 _public prototype_ `void ComputeIntersectionsWithIsos(const FLinearBoundary& InBoundary, const TArray<double>& InIsoCoordinates, const EIso InTypeIso, const FSurfacicTolerance& ToleranceIso, TArray<double>& OutIntersection) const;` — The main idea of this algorithm is to process starting for the beginning of the curve to the end of the curve.
- L272 _public function_ `const TArray<double>& GetCoordinates() const`
- L277 _public function_ `const TArray<FVector2d>& Get2DPoints() const`
- L282 _public function_ `const FVector& GetPointAt(int32 Index) const`
- L287 _public function_ `const TArray<FVector>& GetPoints() const`
- L292 _public function_ `const TArray<FVector3f>& GetNormals() const`
- L297 _public function_ `const TArray<FVector>& GetTangents() const`
- L302 _public function_ `void SwapCoordinates(TArray<double>& NewCoordinates)`
- L320 _public function_ `int32 Size() const` — @return the size of the polyline i.e. the count of points.
- L328 _public function_ `void GetSubPolyline(const FLinearBoundary& InBoundary, const EOrientation InOrientation, TArray<FVector2d>& OutPoints) const` — Get the sub 2d polyline bounded by the input InBoundary in the orientation of the input InOrientation and append it to the output OutPoints
- L337 _public function_ `void GetSubPolyline(const FLinearBoundary& InBoundary, TArray<double>& OutCoordinates, TArray<FVector2d>& OutPoints) const` — Get the sub polyline bounded by the input InBoundary in the orientation of the input InOrientation and append it to the output OutPoints
- L346 _public function_ `void GetSubPolyline(const FLinearBoundary& InBoundary, const EOrientation InOrientation, TArray<FVector>& OutPoints) const` — Get the sub polyline bounded by the input InBoundary in the orientation of the input InOrientation and append it to the output OutPoints
- L355 _public function_ `void GetSubPolyline(const FLinearBoundary& InBoundary, TArray<double>& OutCoordinates, TArray<FVector>& OutPoints) const` — Get the sub polyline bounded by the input InBoundary in the orientation of the input InOrientation and append it to the output OutPoints
- L366 _public function_ `void Reserve(int32 Number)` — Reserves memory such that the polyline can contain at least Number elements. @param Number The number of elements that the polyline should be able to contain after allocation.
- L382 _public function_ `void Empty(int32 Slack = 0)` — Empties the polyline. @param Slack (Optional) The expected usage size after empty operation. Default is 0.
- L390 _public function_ `void EmplaceAt(int32 Index, FSurfacicPolyline& Polyline, int32 PointIndex)`
- L406 _public function_ `void RemoveComplementaryPoints(int32 Offset)`
- L450 _public function_ `void Pop()`
- L465 _public function_ `void Reverse()`
- L480 _public function_ `double GetLength(const FLinearBoundary& InBoundary) const`
- L486 _public function_ `double Get2DLength(const FLinearBoundary& InBoundary) const`
- L492 _public function_ `bool IsIso(EIso Iso, double ErrorTolerance = DOUBLE_SMALL_NUMBER) const`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace CADKernel` (scope `UE`)
- L149 _function_ `` (scope `UE::CADKernel::FSurfacicPolyline::ApproximatePolyline`)
- L495 _function_ `return Algo::AllOf(Points2D, [&](const FVector2d& Point) { return FMath::IsNearlyEqual(Point[Iso], StartPoint[Iso], ErrorTolerance); });` (scope `UE::CADKernel::FSurfacicPolyline::IsIso`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/Surfaces/NurbsSurfaceData.h` (Public)


#### struct `UE::CADKernel::FNurbsSurfaceHomogeneousData`  
`struct FNurbsSurfaceHomogeneousData`  
_L10-24_
- L12 _public member_ `bool bSwapUV;`
- L13 _public member_ `int32 PoleUCount;`
- L14 _public member_ `int32 PoleVCount;`
- L16 _public member_ `int32 UDegree;`
- L17 _public member_ `int32 VDegree;`
- L19 _public member_ `TArray<double> UNodalVector;`
- L20 _public member_ `TArray<double> VNodalVector;`
- L22 _public member_ `bool bIsRational;`
- L23 _public member_ `TArray<double> HomogeneousPoles;`

#### struct `UE::CADKernel::FNurbsSurfaceData`  
`struct FNurbsSurfaceData`  
_L26-41_
- L28 _public member_ `bool bSwapUV;`
- L29 _public member_ `int32 PoleUCount;`
- L30 _public member_ `int32 PoleVCount;`
- L32 _public member_ `int32 UDegree;`
- L33 _public member_ `int32 VDegree;`
- L35 _public member_ `TArray<double> UNodalVector;`
- L36 _public member_ `TArray<double> VNodalVector;`
- L39 _public member_ `TArray<double> Weights;` — if Weights.Num() == 0  => bIsRational = false
- L40 _public member_ `TArray<FVector> Poles;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/Surfaces/Surface.h` (Public)


#### class `UE::CADKernel::FSurface`  
`class FSurface : public FEntityGeom`  
_L26-294_
- inherits: `FEntityGeom`
- L32 _protected member_ `FSurfacicBoundary Boundary;`
- L33 _protected member_ `double Tolerance3D;`
- L42 _protected member_ `TCache<FSurfacicTolerance> MinToleranceIso;` — Tolerance along Iso U/V is very costly to compute and not accurate. A first approximation is based on the surface boundary along U and along V Indeed, defining a Tolerance2D has no sense has the boundary length along an Iso could be very very huge compare to the boundary length along the other Iso like [[0, 1000] [0, 1]] The tolerance along an iso is the length of the boundary along this iso divided by 100 000: if the curve length in 3d is 10m, the tolerance is 0.01mm In the used, a local tolerance has to be estimated
- L46 _private function_ `virtual void InitBoundary()`
- L53 _protected prototype_ `FSurface() = default;`
- L55 _protected function_ `FSurface(double InToleranceGeometric) : FEntityGeom() , Tolerance3D(InToleranceGeometric)`
- L62 _protected function_ `FSurface(double InToleranceGeometric, const FSurfacicBoundary& InBoundary) : FEntityGeom() , Boundary(InBoundary) , Tolerance3D(InToleranceGeometric)`
- L70 _protected function_ `FSurface(double InToleranceGeometric, double UMin, double UMax, double VMin, double VMax) : FEntityGeom() , Tolerance3D(InToleranceGeometric)`
- L77 _protected function_ `void ComputeDefaultMinToleranceIso()`
- L84 _public prototype_ `static TSharedPtr<FSurface> MakeBezierSurface(const double InToleranceGeometric, int32 InUDegre, int32 InVDegre, const TArray<FVector>& InPoles);`
- L85 _public prototype_ `static TSharedPtr<FSurface> MakeConeSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, double InStartRadius, double InConeAngle, const FSurfacicBoundary& InBoundary);`
- L86 _public prototype_ `static TSharedPtr<FSurface> MakeCylinderSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, const double InRadius, const FSurfacicBoundary& InBoundary);`
- L87 _public prototype_ `static TSharedPtr<FSurface> MakeNurbsSurface(const double InToleranceGeometric, const FNurbsSurfaceData& NurbsData);`
- L88 _public prototype_ `static TSharedPtr<FSurface> MakeNurbsSurface(const double InToleranceGeometric, const FNurbsSurfaceHomogeneousData& NurbsData);`
- L89 _public prototype_ `static TSharedPtr<FSurface> MakePlaneSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, const FSurfacicBoundary& InBoundary);`
- L90 _public prototype_ `static TSharedPtr<FSurface> MakeSphericalSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, double InRadius, const FSurfacicBoundary& InBoundary);`
- L91 _public prototype_ `static TSharedPtr<FSurface> MakeTorusSurface(const double InToleranceGeometric, const FMatrixH& InMatrix, double InMajorRadius, double InMinorRadius, const FSurfacicBoundary& InBoundary);`
- L93 _public function_ `virtual void ValidateUVPoints(TArray<FVector2d>& UVPoints) const`
- L95 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L113 _public prototype_ `static TSharedPtr<FSurface> Deserialize(FCADKernelArchive& Archive);` — Specific method for surface family to instantiate the correct derived class of FCurve
- L115 _public prototype_ `virtual ~FSurface() = default;`
- L118 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L121 _public function_ `virtual EEntity GetEntityType() const override`
- L126 _public prototype_ `virtual ESurface GetSurfaceType() const = 0;`
- L128 _public function_ `const FSurfacicBoundary& GetBoundary() const`
- L134 _public function_ `void TrimBoundaryTo(const FSurfacicBoundary NewLimit)`
- L139 _public function_ `void ExtendBoundaryTo(const FSurfacicBoundary MaxLimit)`
- L144 _public prototype_ `virtual TSharedPtr<FEntityGeom> ApplyMatrix(const FMatrixH& InMatrix) const = 0;`
- L153 _public function_ `const FSurfacicTolerance& GetIsoTolerances() const` — Tolerance along Iso U/V is very costly to compute and not accurate. A first approximation is based on the surface parametric space length along U and along V Indeed, defining a Tolerance2D has no sense has the boundary length along an Iso could be very very huge compare to the boundary length along the other Iso like [[0, 1000] [0, 1]] @see FBoundary::ComputeMinimalTolerance In the used, a local tolerance has to be estimated
- L164 _public function_ `double GetIsoTolerance(EIso Iso) const` — Return the minimum tolerance in the parametric space of the surface along the specified axis With Tolerance3D = FSysteme.GeometricalTolerance @see FBoundary::ComputeMinimalTolerance
- L170 _public function_ `double Get3DTolerance() const`
- L176 _public prototype_ `virtual void EvaluatePoint(const FVector2d& InSurfacicCoordinate, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder = 0) const = 0;`
- L178 _public prototype_ `virtual void EvaluatePoints(const TArray<FVector2d>& InSurfacicCoordinates, TArray<FSurfacicPoint>& OutPoint3D, int32 InDerivativeOrder = 0) const;`
- L179 _public prototype_ `virtual void EvaluatePoints(const TArray<FCurvePoint2D>& InSurfacicCoordinates, TArray<FSurfacicPoint>& OutPoint3D, int32 InDerivativeOrder = 0) const;`
- L180 _public prototype_ `virtual void EvaluatePoints(const TArray<FCurvePoint2D>& InSurfacicCoordinates, TArray<FCurvePoint>& OutPoint3D, int32 InDerivativeOrder = 0) const;`
- L181 _public prototype_ `virtual void EvaluatePoints(FSurfacicPolyline& Polyline) const;`
- L182 _public prototype_ `virtual void EvaluatePoints(const TArray<FCurvePoint2D>& Points2D, FSurfacicPolyline& Polyline) const;`
- L195 _public function_ `virtual FVector2d EvaluatePointInCylindricalSpace(const FVector2d& InSurfacicCoordinate) const` — X = Rho cos(Alpha) Y = Rho sin(Alpha) Z = Z YZ => cylindrical projection XY => Plan projection along rotation axis For Normal(u,v) parallel Rotation Axis -> use Plan projection For Normal(u,v) perpendicular to Rotation Axis -> use cylindrical projection
- L196 _public function_ `virtual void EvaluatePointGridInCylindricalSpace(const FCoordinateGrid& Coordinates, TArray<FVector2d>&) const`
- L198 _public prototype_ `virtual void EvaluatePointGrid(const FCoordinateGrid& Coordinates, FSurfacicSampling& OutPoints, bool bComputeNormals = false) const;`
- L199 _public prototype_ `void EvaluateGrid(FGrid& Grid) const;`
- L201 _public prototype_ `virtual void EvaluateNormals(const TArray<FVector2d>& Points2D, TArray<FVector3f>& Normals) const;`
- L203 _public function_ `virtual void EvaluatePointAndNormal(const FVector2d& InPoint2D, FVector& Point, FVector3f& Normal) const`
- L215 _public function_ `virtual FVector EvaluateNormal(const FVector2d& InPoint2D) const`
- L229 _public prototype_ `void Sample(const FSurfacicBoundary& Bounds, int32 NumberOfSubdivisions[2], FSurfacicSampling& OutPointSampling) const;` — Divide the parametric space in the desired number of regular subdivisions and compute the associated PointGrid
- L234 _public prototype_ `void Sample(const FSurfacicBoundary& Boundary, int32 NumberOfSubdivisions[2], FCoordinateGrid& OutCoordinateSampling) const;` — Divide the parametric space in the desired number of regular subdivisions and compute the associated CoordinateGrid
- L240 _public prototype_ `virtual void Presample(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& OutCoordinates);` — Generate a pre-sampling of the surface saved in OutCoordinates. This sampling is light enough to allow a fast computation of the grid, precise enough to compute accurately meshing criteria
- L242 _public function_ `virtual void LinesNotDerivables(const FSurfacicBoundary& Bounds, int32 InDerivativeOrder, FCoordinateGrid& OutNotDerivableCoordinates) const`
- L247 _public function_ `void LinesNotDerivables(int32 InDerivativeOrder, FCoordinateGrid& OutNotDerivableCoordinates) const`
- L257 _public function_ `virtual void IsSurfaceClosed(bool& bOutClosedAlongU, bool& bOutClosedAlongV) const` — A surface is closed along an iso axis if it's connected to itself e.g. the edge carried by the iso curve U = UMin is linked to the edge carried by the iso curve U = UMax A complete sphere, torus are example of surface closed along U and V A cylinder with circle section or a cone are example of surface closed along an iso
- L263 _public function_ `void PresampleIsoCircle(const FSurfacicBoundary& InBoundaries, FCoordinateGrid& Coordinates, EIso Iso)`
- L286 _public function_ `static double ComputeScaleAlongAxis(const FVector& InAxis, const FMatrixH& InMatrix, const FVector& InOrigin)` — This function return the scale of the input Axis. This function is useful to estimate tolerance when scales are defined in the Matrix @param InAxis a vetor of length 1 @param InMatrix @param InOrigin = InMatrix*FVector::ZeroVector

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Geo/Surfaces/SurfaceUtilities.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)
- L10 _namespace_ `namespace SurfaceUtilities` (scope `UE::CADKernel`)
- L12 _prototype_ `TArray<TArray<FVector3f>> GetPoles(const UE::CADKernel::FSurface& Surface);` (scope `UE::CADKernel::SurfaceUtilities`)
- L13 _prototype_ `bool IsPlanar(const UE::CADKernel::FSurface& Surface);` (scope `UE::CADKernel::SurfaceUtilities`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Math/Aabb.h` (Public)


#### enum `EAABBBoundary`  
`enum EAABBBoundary : uint32`  
_L7-15_
- L9 _public enumerator_ `XMax = 0x00000000u`
- L10 _public enumerator_ `YMax = 0x00000000u`
- L11 _public enumerator_ `ZMax = 0x00000000u`
- L12 _public enumerator_ `XMin = 0x00000001u`
- L13 _public enumerator_ `YMin = 0x00000002u`
- L14 _public enumerator_ `ZMin = 0x00000004u`

#### class `UE::CADKernel::TAABB`  
`template<class PointType, int Dimension = 3> class TAABB`  
_L22-206_
- L26 _protected member_ `PointType MinCorner;`
- L27 _protected member_ `PointType MaxCorner;`
- L30 _public function_ `TAABB()`
- L34 _public function_ `TAABB(const PointType& InMinCorner, const PointType& InMaxCorner) : MinCorner(InMinCorner) , MaxCorner(InMaxCorner)`
- L47 _public function_ `bool IsValid() const`
- L59 _public function_ `void Empty()`
- L63 _public function_ `bool Contains(const PointType& Point) const`
- L75 _public function_ `void SetMinSize(double MinSize)`
- L89 _public function_ `double GetMaxSize() const`
- L103 _public function_ `double GetSize(int32 Axis) const`
- L108 _public function_ `double DiagonalLength() const`
- L113 _public function_ `PointType Diagonal() const`
- L118 _public function_ `bool Contains(const TAABB& Aabb) const`
- L123 _public function_ `const PointType& GetMin() const`
- L128 _public function_ `const PointType& GetMax() const`
- L133 _public function_ `TAABB& operator+= (const double* Point)`
- L149 _public function_ `TAABB& operator+= (const PointType& Point)`
- L166 _public function_ `TAABB& operator+= (const TArray<PointType>& Points)`
- L176 _public function_ `void Offset(double Offset)`
- L185 _public function_ `TAABB& operator+= (const TAABB& aabb)`
- L192 _public function_ `TAABB operator+ (const PointType& Point) const`
- L200 _public function_ `TAABB operator+ (const TAABB& Aabb) const`
- L209 _function_ `template<> inline TAABB<FVector2d, 2>::TAABB() : MinCorner(FVectorUtil::FarawayPoint2D) , MaxCorner(-FVectorUtil::FarawayPoint2D)`
- L216 _function_ `template<> inline TAABB<FVector, 3>::TAABB() : MinCorner(FVectorUtil::FarawayPoint3D) , MaxCorner(-FVectorUtil::FarawayPoint3D)`
- L223 _function_ `template<> inline void TAABB<FVector2d, 2>::Empty()`
- L230 _function_ `template<> inline void TAABB<FVector, 3>::Empty()`

#### class `UE::CADKernel::FAABB`  
`class FAABB : public TAABB<FVector>`  
_L237-259_
- inherits: `TAABB<FVector>`
- L241 _public function_ `FAABB() : TAABB<FVector>()`
- L246 _public function_ `FAABB(const FVector& InMinCorner, const FVector& InMaxCorner) : TAABB<FVector>(InMinCorner, InMaxCorner)`
- L251 _public function_ `FVector GetCorner(int32 Corner) const`

#### class `UE::CADKernel::FAABB2D`  
`class FAABB2D : public TAABB<FVector2d, 2>`  
_L261-282_
- inherits: `TAABB<FVector2d,2>`
- L264 _public function_ `FAABB2D() : TAABB<FVector2d, 2>()`
- L269 _public function_ `FAABB2D(const FVector& InMinCorner, const FVector& InMaxCorner) : TAABB<FVector2d, 2>(FVector2d(InMinCorner.X, InMinCorner.Y), FVector2d(InMaxCorner.X, InMaxCorner.Y))`
- L274 _public function_ `FVector2d GetCorner(int32 CornerIndex) const`

#### Free symbols / members of external scopes

- L17 _prototype_ `ENUM_CLASS_FLAGS(EAABBBoundary);`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace CADKernel` (scope `UE`)
- L40 _function_ `friend FArchive& operator<<(FArchive& Ar, TAABB& AABB)` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Math/BSpline.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)
- L22 _namespace_ `namespace BSpline` (scope `UE::CADKernel`)
- L27 _prototype_ `void Bernstein(int32 Degree, double InCoordinateU, double* BernsteinValuesAtU, double* BernsteinGradientsAtU, double* BernsteinLaplaciansAtU);` (scope `UE::CADKernel::BSpline`) — Compute the values of Bernstein polynomial
- L29 _prototype_ `void FindNotDerivableParameters(const FNURBSCurve&, int32 InDerivativeOrder, const FLinearBoundary& Boundary, TArray<double>& OutNotDerivableParameters);` (scope `UE::CADKernel::BSpline`)
- L30 _prototype_ `void FindNotDerivableParameters(const FNURBSSurface&, int32 InDerivativeOrder, const FSurfacicBoundary& Boundary, FCoordinateGrid& OutNotDerivableParameters);` (scope `UE::CADKernel::BSpline`)
- L32 _prototype_ `void Evaluate2DPoint(const FNURBSCurve&, double Coordinate, FCurvePoint2D& OutPoint, int32 DerivativeOrder);` (scope `UE::CADKernel::BSpline`)
- L33 _prototype_ `void EvaluatePoint(const FNURBSCurve&, double Coordinate, FCurvePoint& OutPoint, int32 DerivativeOrder);` (scope `UE::CADKernel::BSpline`)
- L35 _prototype_ `void EvaluatePoint(const FNURBSSurface&, const FVector2d& InPoint2D, FSurfacicPoint& OutPoint3D, int32 InDerivativeOrder);` (scope `UE::CADKernel::BSpline`)
- L36 _prototype_ `void EvaluatePointGrid(const FNURBSSurface&, const FCoordinateGrid& Coords, FSurfacicSampling& OutPoints, bool bComputeNormals);` (scope `UE::CADKernel::BSpline`)
- L38 _prototype_ `TSharedPtr<FNURBSCurve> DuplicateNurbsCurveWithHigherDegree(int32 degre, const FNURBSCurve& InCurve);` (scope `UE::CADKernel::BSpline`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Math/Boundary.h` (Public)


#### struct `UE::CADKernel::FLinearBoundary`  
`struct FLinearBoundary`  
_L17-245_
- L21 _public member_ `static const FLinearBoundary DefaultBoundary;` — A default boundary (0., 1.)
- L23 _public member_ `double Min;`
- L24 _public member_ `double Max;`
- L26 _public function_ `FLinearBoundary()`
- L32 _public function_ `FLinearBoundary(const FLinearBoundary& Boundary) : Min(Boundary.Min) , Max(Boundary.Max)`
- L38 _public function_ `FLinearBoundary(const double UMin, const double UMax)`
- L43 _public function_ `FLinearBoundary(const FLinearBoundary& Boundary, const double OffsetTolerance) : Min(Boundary.Min - OffsetTolerance) , Max(Boundary.Max + OffsetTolerance)`
- L49 _public function_ `FLinearBoundary(const double UMin, const double UMax, const double OffsetTolerance)`
- L61 _public function_ `constexpr double GetMin() const`
- L66 _public function_ `constexpr double GetMax() const`
- L71 _public function_ `constexpr double GetAt(const double Coordinate) const`
- L76 _public function_ `constexpr double GetMiddle() const`
- L81 _public function_ `double Size() const`
- L83 _public function_ `void SetMin(const double Coordinates)`
- L88 _public function_ `void SetMax(const double Coordinates)`
- L93 _public function_ `void Set(const double InUMin = 0., const double InUMax = 1.)`
- L101 _public function_ `void Set(const TArray<double>& Coordinates)` — Set the boundary with the min and max of the array
- L111 _public function_ `bool IsValid() const`
- L116 _public function_ `bool Contains(const double Coordinate) const`
- L121 _public function_ `double Length() const`
- L129 _public function_ `bool IsDegenerated() const` — Return true if the parametric domain is to small
- L141 _public function_ `double ComputeMinimalTolerance() const` — Compute the minimal tolerance of the parametric domain i.e. ToleranceMin = Boundary.Length() * MINIMAL_UNIT_LINEAR_TOLERANCE e.g. for a curve of 1m with a parametric space define between [0, 1], the parametric tolerance is 0.01 This is a minimal value that has to be replace with a more accurate value when its possible
- L149 _public function_ `void MoveInsideIfNot(double& Coordinate, const double Tolerance = DOUBLE_SMALL_NUMBER) const` — If a coordinate is outside the bounds, set the coordinate at the closed limit
- L161 _public function_ `void Offset(const double Tolerance = DOUBLE_SMALL_NUMBER)`
- L170 _public function_ `void Init()` — Uses to initiate a boundary computation with ExtendTo
- L176 _public function_ `void ExtendTo(double MinCoordinate, double MaxCoordinate)`
- L183 _public function_ `void TrimAt(const FLinearBoundary& MaxBound)`
- L195 _public function_ `void ExtendTo(const FLinearBoundary& MaxBound)`
- L201 _public function_ `void ExtendTo(const double Coordinate)`
- L214 _public function_ `void RestrictTo(const FLinearBoundary& MaxBound)`
- L229 _public function_ `void WidenIfDegenerated()` — If the boundary width is near or equal to zero, it's widened by +/- DOUBLE_SMALL_NUMBER
- L238 _public function_ `FLinearBoundary& operator=(const FLinearBoundary& InBounds)`

#### class `UE::CADKernel::FSurfacicBoundary`  
`class FSurfacicBoundary`  
_L247-462_
- L250 _private member_ `FLinearBoundary UVBoundaries[2];`
- L254 _public member_ `static const FSurfacicBoundary DefaultBoundary;` — A default boundary (0., 1., 0., 1.)
- L256 _public prototype_ `FSurfacicBoundary() = default;`
- L258 _public function_ `FSurfacicBoundary(const double InUMin, const double InUMax, const double InVMin, const double InVMax)`
- L264 _public function_ `FSurfacicBoundary(const double InUMin, const double InUMax, const double InVMin, const double InVMax, const double OffsetTolerance)`
- L271 _public function_ `FSurfacicBoundary(const FVector2d& Point1, const FVector2d& Point2)`
- L276 _public function_ `FSurfacicBoundary(const FVector2d& Point1, const FVector2d& Point2, const double OffsetTolerance)`
- L282 _public function_ `void Set(const FVector2d& Point1, const FVector2d& Point2)`
- L295 _public function_ `void Set(const FLinearBoundary& BoundU, const FLinearBoundary& BoundV)`
- L301 _public function_ `void Set(const double InUMin, const double InUMax, const double InVMin, const double InVMax)`
- L307 _public function_ `void Set()`
- L316 _public function_ `void Set(const TArray<FVector2d>& Points)` — Set the boundary with the min and max of this array
- L325 _public function_ `const FLinearBoundary& Get(EIso Type) const`
- L330 _public function_ `bool IsValid() const`
- L338 _public function_ `bool IsDegenerated() const` — Return true if the parametric domain is to small
- L343 _public function_ `ESituation IsInside(const FSurfacicBoundary& OtherBoundary, const FSurfacicTolerance& Tolerance2D)`
- L378 _public function_ `void Init()` — Uses to initiate a boundary computation with ExtendTo
- L384 _public function_ `void TrimAt(const FSurfacicBoundary& MaxLimit)`
- L390 _public function_ `void ExtendTo(const FSurfacicBoundary& MaxLimit)`
- L396 _public function_ `void ExtendTo(const FVector2d& Point)`
- L402 _public function_ `void ExtendTo(const FVector& Point)`
- L408 _public function_ `void RestrictTo(const FSurfacicBoundary& MaxBound)`
- L417 _public function_ `void WidenIfDegenerated()` — If Along each axis, the bound width is near equal to zero, it's widened by +/- DOUBLE_SMALL_NUMBER
- L426 _public function_ `void MoveInsideIfNot(FVector& Point, const double Tolerance = DOUBLE_SMALL_NUMBER) const` — If a point is outside the bounds, set the coordinate to insert the point inside the bounds
- L435 _public function_ `void MoveInsideIfNot(FVector2d& Point, const double Tolerance = DOUBLE_SMALL_NUMBER) const` — If a point is outside the bounds, set the coordinate to insert the point inside the bounds
- L441 _public function_ `double Length(const EIso& Iso) const`
- L446 _public function_ `constexpr const FLinearBoundary& operator[](const EIso& Iso) const`
- L451 _public function_ `constexpr FLinearBoundary& operator[](const EIso& Iso)`
- L456 _public function_ `void Offset(const double Tolerance = DOUBLE_SMALL_NUMBER)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)
- L15 _macro_ `#define MINIMAL_UNIT_LINEAR_TOLERANCE 1e-5` — MINIMAL_UNIT_LINEAR_TOLERANCE allows to define the minimal tolerance value of a parametric space @see FLinearBoundary::ComputeMinimalTolerance
- L55 _function_ `friend FArchive& operator<<(FArchive& Ar, FLinearBoundary& Boundary)` (scope `UE::CADKernel`)
- L288 _function_ `friend FArchive& operator<<(FArchive& Ar, FSurfacicBoundary& Boundary)` (scope `UE::CADKernel`)
- L348 _function_ `` (scope `UE::CADKernel::FSurfacicBoundary::IsInside`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Math/Curvature.h` (Public)


#### struct `UE::CADKernel::FIsoCurvature`  
`struct FIsoCurvature`  
_L9-13_
- L11 _public member_ `double Min = HUGE_VALUE;`
- L12 _public member_ `double Max = 0;`

#### struct `UE::CADKernel::FSurfaceCurvature`  
`struct FSurfaceCurvature`  
_L15-28_
- L17 _public member_ `FIsoCurvature Curvatures[2];`
- L19 _public function_ `constexpr const FIsoCurvature& operator[](const EIso& Iso) const`
- L24 _public function_ `constexpr FIsoCurvature& operator[](const EIso& Iso)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Math/Geometry.h` (Public)


#### enum `UE::CADKernel::EPolygonSide`  
`enum EPolygonSide : uint8`  
_L13-20_
- L15 _public enumerator_ `Side01 = 0`
- L16 _public enumerator_ `Side12`
- L17 _public enumerator_ `Side20`
- L18 _public enumerator_ `Side23`
- L19 _public enumerator_ `Side30`

#### struct `UE::CADKernel::TSegment`  
`template<class PointType> struct TSegment`  
_L249-284_
- L251 _public member_ `const PointType& Point0;`
- L252 _public member_ `const PointType& Point1;`
- L253 _public member_ `const PointType Dummy = PointType::ZeroVector;`
- L255 _public function_ `TSegment(const PointType& InPoint0, const PointType& InPoint1) : Point0(InPoint0) , Point1(InPoint1)`
- L261 _public function_ `constexpr const PointType& operator[](int32 Index) const`
- L275 _public function_ `double SquaredLength() const`
- L280 _public function_ `PointType GetVector() const`

#### struct `UE::CADKernel::TTriangle`  
`template<class PointType> struct TTriangle`  
_L290-410_
- L292 _public member_ `const PointType& Point0;`
- L293 _public member_ `const PointType& Point1;`
- L294 _public member_ `const PointType& Point2;`
- L296 _public function_ `TTriangle(const PointType& InPoint0, const PointType& InPoint1, const PointType& InPoint2) : Point0(InPoint0) , Point1(InPoint1) , Point2(InPoint2)`
- L303 _public function_ `constexpr const PointType& operator[](int32 Index) const`
- L319 _public function_ `virtual inline PointType ProjectPoint(const PointType& InPoint, FVector2d& OutCoordinate)`
- L406 _public function_ `virtual PointType CircumCircleCenter() const`

#### struct `UE::CADKernel::FTriangle`  
`struct FTriangle : public TTriangle<FVector>`  
_L412-425_
- inherits: `TTriangle<FVector>`
- L414 _public function_ `FTriangle(const FVector& InPoint0, const FVector& InPoint1, const FVector& InPoint2) : TTriangle<FVector>(InPoint0, InPoint1, InPoint2)`
- L419 _public function_ `virtual FVector ComputeNormal() const`

#### struct `UE::CADKernel::FTriangle2D`  
`struct FTriangle2D : public TTriangle<FVector2d>`  
_L427-438_
- inherits: `TTriangle<FVector2d>`
- L429 _public function_ `FTriangle2D(const FVector2d& InPoint0, const FVector2d& InPoint1, const FVector2d& InPoint2) : TTriangle<FVector2d>(InPoint0, InPoint1, InPoint2)`
- L434 _public function_ `FVector2d CircumCircleCenterWithSquareRadius(double& SquareRadius) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CADKernel` (scope `UE`)
- L22 _namespace_ `namespace IntersectionTool` (scope `UE::CADKernel`)
- L24 _prototype_ `void SetTolerance(const double Tolerance);` (scope `UE::CADKernel::IntersectionTool`)
- L32 _function_ `inline FVector2d ComputeCircumCircleCenter(const FVector2d& InPoint0, const FVector2d& InPoint1, const FVector2d& InPoint2)` (scope `UE::CADKernel`) — https://en.wikipedia.org/wiki/Circumscribed_circle#Cartesian_coordinates_2 With A = (0, 0)
- L54 _function_ `inline FVector ComputeCircumCircleCenter(const FVector& Point0, const FVector& Point1, const FVector& Point2)` (scope `UE::CADKernel`)
- L88 _function_ `inline FVector2d ComputeCircumCircleCenterAndSquareRadius(const FVector2d& InPoint0, const FVector2d& InPoint1, const FVector2d& InPoint2, double& OutSquareRadius)` (scope `UE::CADKernel`)
- L116 _function_ `template<class PointType> inline PointType ProjectPointOnSegment(const PointType& Point, const PointType& InSegmentA, const PointType& InSegmentB, double& OutCoordinate, bool bRestrictCoodinateToInside = true)` (scope `UE::CADKernel`) — @param OutCoordinate: the coordinate of the projected point in the segment AB (coodinate of A = 0 and of B = 1) @return Projected point
- L153 _function_ `inline FVector ProjectPointOnPlane(const FVector& Point, const FVector& Origin, const FVector& InNormal, double& OutDistance)` (scope `UE::CADKernel`)
- L169 _function_ `template<class PointType> inline PointType PointOnSegment(const PointType& InSegmentA, const PointType& InSegmentB, double InCoordinate)` (scope `UE::CADKernel`) — @return InSegmentA + (InSegmentB - InSegmentA) | InCoordinate
- L180 _function_ `template<class PointType> inline double DistanceOfPointToSegment(const PointType& Point, const PointType& SegmentPoint1, const PointType& SegmentPoint2)` (scope `UE::CADKernel`) — @return the distance between the point and the segment. If the projection of the point on the segment is not inside it, return the distance of the point to nearest the segment extremity
- L191 _function_ `template<class PointType> inline double SquareDistanceOfPointToSegment(const PointType& Point, const PointType& SegmentPoint1, const PointType& SegmentPoint2)` (scope `UE::CADKernel`) — @return the distance between the point and the segment. If the projection of the point on the segment is not inside it, return the distance of the point to nearest the segment extremity
- L201 _function_ `template<class PointType> inline double DistanceOfPointToLine(const PointType& Point, const PointType& LinePoint1, const PointType& LineDirection)` (scope `UE::CADKernel`) — @return the distance between the point and the line i.e. the distance between the point and its projection on the line
- L207 _prototype_ `double ComputeCurvature(const FVector& Gradient, const FVector& Laplacian);` (scope `UE::CADKernel`)
- L208 _prototype_ `double ComputeCurvature(const FVector& normal, const FVector& Gradient, const FVector& Laplacian);` (scope `UE::CADKernel`)
- L214 _function_ `template<class PointType> inline double CoordinateOfProjectedPointOnSegment(const PointType& Point, const PointType& InSegmentA, const PointType& InSegmentB, bool bRestrictCoodinateToInside = true)` (scope `UE::CADKernel`) — @return Coordinate of the projected point in the segment AB (coordinate of A = 0 and of B = 1)
- L246 _prototype_ `void FindLoopIntersectionsWithIso(const EIso Iso, const double IsoParameter, const TArray<TArray<FVector2d>>& Loops, TArray<double>& OutIntersections);` (scope `UE::CADKernel`)
- L286 _typedef_ `using FSegment2D = TSegment<FVector2d>;` (scope `UE::CADKernel`)
- L287 _typedef_ `using FSegment3D = TSegment<FVector>;` (scope `UE::CADKernel`)
- L443 _function_ `inline FVector2d FindIntersectionOfSegments2D(const FSegment2D& SegmentAB, const FSegment2D& SegmentCD, double& OutABIntersectionCoordinate)` (scope `UE::CADKernel`) — The segments must intersect because no check is done
- L492 _function_ `inline FVector2d FindIntersectionOfSegments2D(const FSegment2D& SegmentAB, const FSegment2D& SegmentCD)` (scope `UE::CADKernel`) — The segments must intersect because no check is done
- L501 _function_ `inline bool FindIntersectionOfLines2D(const FSegment2D& LineAB, const FSegment2D& LineCD, FVector2d& OutIntersectionPoint)` (scope `UE::CADKernel`) — @return false if the lines are parallel
- L525 _prototype_ `bool DoIntersect(const FSegment2D& SegmentAB, const FSegment2D& SegmentCD);` (scope `UE::CADKernel`) — Similar as FastDoIntersect but check intersection if both segment are carried by the same line. This method is 50% slower than FastIntersectSegments2D even if the segments tested are never carried by the same line
- L526 _prototype_ `bool DoIntersectInside(const FSegment2D& SegmentAB, const FSegment2D& SegmentCD);` (scope `UE::CADKernel`)
- L528 _function_ `inline bool AreParallel(const FSegment2D& SegmentAB, const FSegment2D& SegmentCD)` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Math/MathConst.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)
- L12 _function_ `template<typename ValueType> const void GetMinMax(const ValueType& ValueA, const ValueType& ValueB, ValueType& OutMin, ValueType& OutMax)` (scope `UE::CADKernel`) — Sort input A & B values into OutMin & OutMax
- L21 _function_ `template<typename ValueType> const void GetMinMax(ValueType& Min, ValueType& Max)` (scope `UE::CADKernel`) — Sort input values to be Min and Max
- L27 _function_ `template<typename ValueType> bool IsWithinExclusive(const ValueType& TestValue, const ValueType& MinValue, const ValueType& MaxValue)` (scope `UE::CADKernel`) — Checks if value is within a range, exclusive on MinValue and MaxValue)
- L32 _function_ `inline int32 RealCompare(const double Value1, const double Value2, const double Tolerance = DOUBLE_SMALL_NUMBER)` (scope `UE::CADKernel`)
- L47 _function_ `template< class T > static T Cubic(const T A)` (scope `UE::CADKernel`)
- L53 _function_ `template< class T > uint8 ToUInt8(T Value)` (scope `UE::CADKernel`)
- L65 _function_ `inline double WrapTo(double Slope, const double StartOfPeriod, const double EndOfPeriod, const double PeriodLength)` (scope `UE::CADKernel`) — Wraps a periodic value into a prime period defined by its StartOfPeriod value and its EndOfPeriod value Mandatory EndOfPeriod - StartOfPeriod = PeriodSize Fast FMath::Fmod or FMath::Floor for the special case of Slope functions since most of the time the input value doesn't need to be change @see SlopeUtils.h

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Math/MatrixH.h` (Public)


#### class `UE::CADKernel::FMatrixH`  
`class FMatrixH`  
_L13-282_
- desc: Should be unified with the math utilities implemented by the Geometry team.
- L16 _private member_ `double Matrix[16];`
- L20 _public member_ `static const FMatrixH Identity;`
- L22 _public function_ `FMatrixH()`
- L27 _public function_ `FMatrixH(const double* const InMatrix16)`
- L35 _public function_ `FMatrixH(const double InMatrix44[][4])`
- L46 _public function_ `FMatrixH(const FVector& Origin, const FVector& Ox, const FVector& Oy, const FVector& Oz)`
- L57 _public function_ `void SetIdentity()`
- L68 _public prototype_ `void FromAxisOrigin(const FVector& Axis, const FVector& Origin);`
- L77 _public prototype_ `void BuildChangeOfCoordinateSystemMatrix(const FVector& Xaxis, const FVector& Yaxis, const FVector& Zaxis, const FVector& Origin);` — @param Xaxis the vector X of the old coordinate system in the new coordinate system @param Yaxis the vector Y of the old coordinate system in the new coordinate system @param Zaxis the vector Z of the old coordinate system in the new coordinate system @param Origin Origin of the old coordinate system in the new coordinate system @return the transform matrix
- L79 _public function_ `FVector Multiply(const FVector& InPoint) const`
- L88 _public function_ `FVector Multiply(const FVector2d& Point2D) const`
- L93 _public function_ `FVector2d Multiply2D(const FVector2d& Point2D) const`
- L99 _public function_ `FVector MultiplyVector(const FVector& InVector) const`
- L108 _public function_ `FVector MultiplyVector(const FVector2d& Point2D) const`
- L113 _public function_ `FVector2d MultiplyVector2D(const FVector2d& Point2D) const`
- L119 _public function_ `FVector3f MultiplyVector(const FVector3f& InVector) const`
- L128 _public prototype_ `static FMatrixH MakeRotationMatrix(double InAngle, const FVector InAxe);`
- L130 _public prototype_ `static FMatrixH MakeTranslationMatrix(const FVector& InPoint);`
- L132 _public prototype_ `static FMatrixH MakeScaleMatrix(FVector& Scale);`
- L133 _public prototype_ `static FMatrixH MakeScaleMatrix(double ScaleX, double ScaleY, double ScaleZ);`
- L138 _public function_ `FVector PointRotation(const FVector& PointToRotate, const FVector& Origin) const` — Apply the rotation centered in origin to PointToRotate
- L151 _public function_ `FVector2d PointRotation(const FVector2d& PointToRotate, const FVector2d& Origin) const`
- L164 _public prototype_ `void Inverse();`
- L166 _public function_ `FMatrixH GetInverse() const`
- L173 _public function_ `void Transpose()`
- L185 _public function_ `double& Get(int32 Row, int32 Column)`
- L190 _public function_ `double Get(int32 Row, int32 Column) const`
- L195 _public function_ `double& operator()(int32 Row, int32 Column)`
- L200 _public function_ `double operator()(int32 Row, int32 Column) const`
- L205 _public function_ `double& operator[](int32 Index)`
- L210 _public function_ `FMatrixH operator*(const FMatrixH& InMatrix) const`
- L228 _public function_ `void operator*=(const FMatrixH& InMatrix)`
- L234 _public function_ `FVector operator*(const FVector& Point) const`
- L239 _public function_ `FMatrixH operator+(const FMatrixH& InMatrix) const`
- L249 _public function_ `void GetMatrixDouble(double* OutMatrix) const`
- L254 _public function_ `FVector Column(int32 Index) const`
- L259 _public function_ `FVector Row(int32 Index) const`
- L264 _public function_ `bool IsId() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)
- L51 _function_ `friend FArchive& operator<<(FArchive& Ar, FMatrixH& InMatrix)` (scope `UE::CADKernel`)
- L284 _prototype_ `void InverseMatrixN(double* Matrix, int32 n);` (scope `UE::CADKernel`)
- L286 _prototype_ `void MatrixProduct(int32 ARowNum, int32 AColumnNum, int32 ResultRank, const double* InMatrixA, const double* InMatrixB, double* OutMatrix);` (scope `UE::CADKernel`)
- L288 _prototype_ `void TransposeMatrix(int32 RowNum, int32 ColumnNum, const double* InMatrix, double* OutMatrix);` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Math/Point.h` (Public)


#### class `UE::CADKernel::FVectorUtil`  
`class FVectorUtil`  
_L12-62_
- L15 _public member_ `static const FVector FarawayPoint3D;`
- L16 _public member_ `static const FVector2d FarawayPoint2D;`
- L18 _public function_ `static FVector2d FromVector(const FVector& Src)`
- L24 _public function_ `template<typename VectorType> static double ComputeCosinus(const VectorType& Vec1, const VectorType& Vec2)`
- L38 _public function_ `template<typename VectorType> static double ComputeAngle(const VectorType& Vec1, const VectorType& Vec2)`
- L53 _public function_ `static double DiagonalAxisCoordinate(const FVector& Vec)` — Return the projection of the point on the diagonal axis (of vector (1,1,1)) i.e. return X + Y + Z
- L58 _public function_ `static double DiagonalAxisCoordinate(const FVector2d& Vec)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)
- L10 _typedef_ `typedef FVector2d FSurfacicTolerance;` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Math/SlopeUtils.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)
- L51 _namespace_ `namespace Slope` (scope `UE::CADKernel`)
- L54 _variable_ `constexpr double NullSlope = 0.;` (scope `UE::CADKernel::Slope`)
- L59 _variable_ `constexpr double RightSlope = 2.;` (scope `UE::CADKernel::Slope`) — RightSlope i.e. Right angle i.e Pi / 2
- L60 _variable_ `constexpr double HalfPiSlope = 2.;` (scope `UE::CADKernel::Slope`)
- L61 _variable_ `constexpr double NinetySlope = 2.;` (scope `UE::CADKernel::Slope`)
- L66 _variable_ `constexpr double ThreeRightSlope = 6.;` (scope `UE::CADKernel::Slope`) — ThreeRightSlope i.e. 3Pi / 2
- L71 _variable_ `constexpr double MinusRightSlope = -2.;` (scope `UE::CADKernel::Slope`) — MinusRightSlope i.e. -Pi / 2
- L76 _variable_ `constexpr double PiSlope = 4.;` (scope `UE::CADKernel::Slope`) — PiSlope i.e. Pi angle
- L81 _variable_ `constexpr double TwoPiSlope = 8.;` (scope `UE::CADKernel::Slope`) — PiSlope i.e. Pi angle
- L86 _variable_ `constexpr double ThirdPiSlope = 1.422649730810374235490851219498;` (scope `UE::CADKernel::Slope`) — ThirdPiSlope i.e. Pi/3 angle (60 deg)
- L87 _variable_ `constexpr double SixtySlope = 1.422649730810374235490851219498;` (scope `UE::CADKernel::Slope`)
- L92 _variable_ `constexpr double QuaterPiSlope = 1;` (scope `UE::CADKernel::Slope`) — ThirdPiSlope i.e. Pi/4 angle (45 deg)
- L93 _variable_ `constexpr double FortyFiveSlope = 0.57735026918962576450914878050196;` (scope `UE::CADKernel::Slope`)
- L98 _variable_ `constexpr double SixthPiSlope = 0.57735026918962576450914878050196;` (scope `UE::CADKernel::Slope`) — ThirdPiSlope i.e. Pi/6 angle (30 deg)
- L99 _variable_ `constexpr double ThirtySlope = 0.57735026918962576450914878050196;` (scope `UE::CADKernel::Slope`)
- L104 _variable_ `constexpr double ThreeQuaterPiSlope = 3;` (scope `UE::CADKernel::Slope`) — ThreeQuaterPiSlope i.e. 3Pi/4 angle (135 deg)
- L106 _variable_ `constexpr double OneDegree = 0.01745506492821758576512889521973;` (scope `UE::CADKernel::Slope`)
- L107 _variable_ `constexpr double TwoDegree = 0.03492076949174773050040262577373;` (scope `UE::CADKernel::Slope`)
- L108 _variable_ `constexpr double FiveDegree = 0.08748866352592400522201866943496;` (scope `UE::CADKernel::Slope`)
- L109 _variable_ `constexpr double TenDegree = 0.17632698070846497347109038686862;` (scope `UE::CADKernel::Slope`)
- L110 _variable_ `constexpr double FifteenDegree = 0.26794919243112270647255365849413;` (scope `UE::CADKernel::Slope`)
- L111 _variable_ `constexpr double TwentyDegree = 0.36397023426620236135104788277683;` (scope `UE::CADKernel::Slope`)
- L112 _variable_ `constexpr double TwentyFiveDegree = 0.46630765815499859283000619479956;` (scope `UE::CADKernel::Slope`)
- L114 _variable_ `constexpr double Epsilon = 0.001;` (scope `UE::CADKernel::Slope`)
- L118 _typedef_ `typedef TFunction<double(const FVector2d&, const FVector2d&, double)> SlopeMethod;` (scope `UE::CADKernel`)
- L124 _function_ `inline double TransformIntoOrientedSlope(double Slope)` (scope `UE::CADKernel`) — Transform a positive slope into an oriented slope [-4, 4] i.e. an equivalent angle between [-Pi, Pi] @return a slope between [-4, 4]
- L129 _function_ `inline double TransformIntoClockwiseSlope(double Slope)` (scope `UE::CADKernel`)
- L138 _function_ `inline double TransformIntoUnorientedSlope(double Slope)` (scope `UE::CADKernel`) — Transform a positive slope into an unoriented slope [0, 4] i.e. an equivalent angle between [0, Pi] @return a slope between [0, 4]
- L147 _function_ `inline double TransformIntoPositiveSlope(double Slope)` (scope `UE::CADKernel`) — Transform a slope into a positive slope [0, *] i.e. an equivalent angle between [0, 2.Pi] @return a slope between [0, 8]
- L157 _function_ `inline double TransformIntoSlopeRelativeToReferenceAxis(double Slope)` (scope `UE::CADKernel`) — return a slope between [0, 2] relative to reference Axis i.e. ComputeUnorientedSlope => 0.5 return 0.5 ComputeUnorientedSlope => 2.3 return 1.7
- L174 _function_ `inline double SwapSlopeOrientation(double Slope)` (scope `UE::CADKernel`) — Swap a slope i.e Slope + PiSlope i.e. angle + Pi @return a slope between [0, 8]
- L180 _function_ `inline double ComputeSlope(const FVector2d& StartPoint, const FVector2d& EndPoint)` (scope `UE::CADKernel`)
- L268 _function_ `inline double ComputeSlope(const FVector2d& StartPoint, const FVector2d& EndPoint, double ReferenceSlope)` (scope `UE::CADKernel`) — Compute the slope of a segment according to a reference slope return the slope
- L278 _function_ `inline double ComputeSlope(const FVector2d& StartPoint, const FVector2d& EndPoint1, const FVector2d& EndPoint2)` (scope `UE::CADKernel`) — Compute the slope between the segments [StartPoint, EndPoint1] and [StartPoint, EndPoint2] @return a slope i.e. an equivalent angle
- L290 _function_ `inline double ComputePositiveSlope(const FVector2d& StartPoint, const FVector2d& EndPoint, double ReferenceSlope)` (scope `UE::CADKernel`) — Compute the oriented slope of a segment according to a reference slope This method is used to compute an approximation of the angle between two segments in 2D. return a slope between [0, 8] i.e. an equivalent angle between [0, 2Pi]
- L300 _function_ `inline double ComputePositiveSlope(const FVector2d& StartPoint, const FVector2d& EndPoint1, const FVector2d& EndPoint2)` (scope `UE::CADKernel`) — Compute the positive slope between the segments [StartPoint, EndPoint1] and [StartPoint, EndPoint2] @return a slope between [0, 8] i.e. an equivalent angle between [0, 2Pi]
- L306 _function_ `inline double ClockwiseSlope(const FVector2d& StartPoint, const FVector2d& EndPoint, double ReferenceSlope)` (scope `UE::CADKernel`)
- L311 _function_ `inline double CounterClockwiseSlope(const FVector2d& StartPoint, const FVector2d& EndPoint, double ReferenceSlope)` (scope `UE::CADKernel`)
- L320 _function_ `inline double ComputeOrientedSlope(const FVector2d& StartPoint, const FVector2d& EndPoint, double ReferenceSlope)` (scope `UE::CADKernel`) — Compute the oriented slope of a segment according to a reference slope @return a slope between [-4, 4] i.e. an equivalent angle between [-Pi, Pi]
- L329 _function_ `inline double ComputeOrientedSlope(const FVector2d& StartPoint, const FVector2d& EndPoint1, const FVector2d& EndPoint2)` (scope `UE::CADKernel`) — Compute the positive slope between the segments [StartPoint, EndPoint1] and [StartPoint, EndPoint2] @return a slope between [-4, 4] i.e. an equivalent angle between [-Pi, Pi]
- L337 _function_ `inline double ComputeUnorientedSlope(const FVector2d& StartPoint, const FVector2d& EndPoint, double ReferenceSlope)` (scope `UE::CADKernel`) — return a slope between [0, 4] i.e. an angle between [0, Pi]
- L349 _function_ `inline double ComputeSlopeRelativeToNearestAxis(const FVector2d& StartPoint, const FVector2d& EndPoint)` (scope `UE::CADKernel`) — return a slope between [0, 1] relative to the nearest axis between horizontal or vertical axis i.e. ComputeUnorientedSlope => 0.5 return 0.5 ComputeUnorientedSlope => 2.3 return 0.3 ComputeUnorientedSlope => 3.6 return 0.4
- L373 _function_ `inline double ComputeSlopeRelativeToReferenceAxis(const FVector2d& StartPoint, const FVector2d& EndPoint, double ReferenceAxisSlope)` (scope `UE::CADKernel`) — return a slope between [0, 2] relative to reference Axis i.e. ComputeUnorientedSlope => 0.5 return 0.5 ComputeUnorientedSlope => 2.3 return 1.7
- L382 _function_ `inline double ComputeUnorientedSlope(const FVector2d& StartPoint, const FVector2d& EndPoint1, const FVector2d& EndPoint2)` (scope `UE::CADKernel`) — return a slope between [0, 4] i.e. an angle between [0, Pi]
- L401 _function_ `inline bool IsPointPInsideSectorABC(const FVector2d& PointA, const FVector2d& PointB, const FVector2d& PointC, const FVector2d& PointP, const double FlatAngle)` (scope `UE::CADKernel`) — P1 inside        / /   inside / A -------------- B --------------- C \ Outside     \  Outside \ P2 Return true if the segment BP is inside the sector defined the half-lines [BA) and [BC) in the counterclockwise. Return false if ABP angle or PBC angle is too flat (smaller than FlatAngle)
- L426 _function_ `inline bool ArePointsInsideSectorABC(const FVector2d& PointA, const FVector2d& PointB, const FVector2d& PointC, const TArray<const FVector2d*>& Points, const double FlatAngle = -DOUBLE_SMALL_NUMBER)` (scope `UE::CADKernel`) — P1 inside        / /   inside / A -------------- B --------------- C \ Outside     \  Outside \ P2 Return true if all of the segment BPi is inside the sector defined the half-lines [BA) and [BC) in the counterclockwise.
- L432 _function_ `` (scope `UE::CADKernel::ArePointsInsideSectorABC`)
- L450 _function_ `inline FVector2d SlopeToVector(const double Slope)` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Mesh/Criteria/Criterion.h` (Public)


#### class `UE::CADKernel::FCriterion`  
`class FCriterion : public FEntity`  
_L23-180_
- inherits: `FEntity`
- L29 _protected prototype_ `FCriterion() = default;`
- L33 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L47 _public prototype_ `static TSharedPtr<FCriterion> Deserialize(FCADKernelArchive& Archive);` — Specific method for curve family to instantiate the correct derived class of FCurve
- L49 _public prototype_ `static TSharedPtr<FCriterion> CreateCriterion(ECriterion type, double value = 0.);`
- L52 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L55 _public function_ `virtual EEntity GetEntityType() const override`
- L64 _public prototype_ `virtual void ApplyOnEdgeParameters(FTopologicalEdge& Edge, const TArray<double>& Coordinates, const TArray<FCurvePoint>& Points) const;` — Sag & Angle criterion.pdf https://docs.google.com/presentation/d/1bUnrRFWCW3sDn9ngb9ftfQS-2JxNJaUZlh783hZMMEw/edit?usp=sharing
- L66 _public prototype_ `virtual ECriterion GetCriterionType() const = 0;`
- L68 _public function_ `FString GetCriterionName()`
- L73 _public prototype_ `virtual double Value() const = 0;`
- L75 _public function_ `static double EvaluateSag(const FVector& PointPoint, const FVector& PointNext, const FVector& PointMiddle, double& Length)`
- L102 _public function_ `virtual bool IsAppliedBetweenBreaks() const`
- L107 _public function_ `static FString GetCriterionName(ECriterion CriterionType)`
- L113 _public prototype_ `static double DefaultValue(ECriterion type);`
- L125 _public function_ `virtual void UpdateDelta(double InDeltaU, double InUSag, double InDiagonalSag, double InVSag, double ChordLength, double DiagonalLength, double& OutDeltaUMax, double& OutDeltaUMin, FIsoCurvature& SurfaceCurvature) const` — According to the criterion, either DeltaUMin or DeltaUMax is set e.g MinSizeCrtierion sets DeltaUMin when MaxSizeCriterion sets DeltaUMax. The implicit rule is that DeltaUMin is predominant over DeltaUMax i.e.: UpdateWithUMaxValue: DeltaUMax = Max(DeltaUMin, Min(DeltaUMax, NewDeltaUMax)) UpdateWithUMinValue: DeltaUMin = Max(DeltaUMin, NewDeltaUMin) DeltaUMax = Max(DeltaUMax, NewDeltaUMin)
- L140 _protected function_ `virtual double ComputeDeltaU(double ChordLength, double DeltaU, double Sag) const`
- L149 _protected function_ `void UpdateWithUMaxValue(double NewMaxValue, double& OutDeltaUMax, const double& OutDeltaUMin) const` — DeltaUMax = Max(DeltaUMin, Min(DeltaUMax, NewDeltaUMax))
- L169 _protected function_ `void UpdateWithUMinValue(double NewMinValue, double& OutDeltaUMax, double& OutDeltaUMin) const` — DeltaUMin = Max(DeltaUMin, NewDeltaUMin) DeltaUMin cannot be smaller than DeltaUMax, so: DeltaUMax = Max(DeltaUMax, NewDeltaUMin)

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CADKernel` (scope `UE`)
- L13 _externvar_ `extern const TCHAR* CriterionTypeNames[];` (scope `UE::CADKernel`)
- L16 _externvar_ `extern const char* CriterionTypeConstNames[];` (scope `UE::CADKernel`) — Defined for Python purpose
- L17 _externvar_ `extern const char* CriterionTypeConstDescHelp[];` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Mesh/Criteria/CriterionType.h` (Public)


#### enum `UE::CADKernel::ECriterion`  
`enum class ECriterion : uint8`  
_L8-17_
- L10 _public enumerator_ `Size = 0`
- L11 _public enumerator_ `MaxSize = 1`
- L12 _public enumerator_ `MinSize = 2`
- L13 _public enumerator_ `Angle = 3`
- L14 _public enumerator_ `Sag = 4`
- L15 _public enumerator_ `CADCurvature = 5`
- L16 _public enumerator_ `None = 255`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Mesh/MeshEnum.h` (Public)


#### enum `UE::CADKernel::EGridSpace`  
`enum EGridSpace : uint8`  
_L16-22_
- desc: 3 parametric spaces are defined : -EGridSpace::Default2D the natural parametric space of the carrier surface i.e. for a Bezier surface the boundary of the space is [[0, 1], [0, 1]] and for a spherical surface [[0, 2Pi], [-Pi / 2, Pi / 2]] -EGridSpace::UniformScaled.The average curvilinear length of the iso curves is calculated in each axis.The parametric space is then scaled in each axis such that the average curvilinear length between two points P(A, V) and P(B, V) = B - A.For a spherical surface [[0, 2Pi.R / 2], [-Pi.R / 2, Pi.R / 2]] with R the radius of the sphere -EGridSpace::Scaled.The UnifomeScaled space is rescaled in its most disturbe axis e.g. if V is the most disturbe axis, whatever V, length of[P(A, V), P(B, V)] = (B - A). This parametric space is closed to a good flattening of the surface.
- L18 _public enumerator_ `Default2D = 0` — do not modified enum value as it is used for a static array
- L19 _public enumerator_ `Scaled = 1`
- L20 _public enumerator_ `UniformScaled = 2`
- L21 _public enumerator_ `EndGridSpace`

#### enum `UE::CADKernel::EMeshingState`  
`enum EMeshingState : uint8`  
_L24-29_
- L26 _public enumerator_ `NotMeshed = 0`
- L27 _public enumerator_ `PartiallyMeshed`
- L28 _public enumerator_ `FullyMeshed`

#### enum `UE::CADKernel::ECoordinateType`  
`enum ECoordinateType : uint8`  
_L31-39_
- L33 _public enumerator_ `VertexCoordinate`
- L34 _public enumerator_ `ImposedCoordinate` — imposted cutting point by thin zone meshing process
- L35 _public enumerator_ `IsoUCoordinate`
- L36 _public enumerator_ `IsoVCoordinate`
- L37 _public enumerator_ `IsoUVCoordinate`
- L38 _public enumerator_ `OtherCoordinate`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)
- L40 _namespace_ `namespace GridSpace` (scope `UE::CADKernel`)
- L43 _function_ `inline FString ToString(EGridSpace Space)` (scope `UE::CADKernel::GridSpace`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Mesh/Meshers/Mesher.h` (Public)


#### class `UE::CADKernel::FMesher`  
`class FMesher`  
_L12-33_
- L16 _protected member_ `double GeometricTolerance;`
- L17 _protected member_ `bool bThinZoneMeshing = false;`
- L19 _protected member_ `FModelMesh& MeshModel;`
- L23 _public prototype_ `FMesher(FModelMesh& InMeshModel, double GeometricTolerance, bool bActivateThinZoneMeshing);`
- L25 _public prototype_ `void MeshEntities(TArray<FTopologicalShapeEntity*>& InEntities);`
- L27 _public function_ `void MeshEntity(FTopologicalShapeEntity& InEntity)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Mesh/Structure/EdgeMesh.h` (Public)


#### class `UE::CADKernel::FEdgeMesh`  
`class FEdgeMesh : public FMesh`  
_L11-44_
- inherits: `FMesh`
- desc: Define the mesh of an edge. This mesh is polygon
- L20 _public member_ `TArray<int32> EdgeVerticesIndex;` — Index of the vertices of the mesh of the TopologicalEdge in the MeshModel vertex array i.e. EdgeVerticesIndex = {5,10,11,12,13,14,3} defines Edge(Vertices[5],Vertices[10]), Edge(Vertices[10],Vertices[11]) etc of the mesh (Edge is side of mesh's triangle). "Vertices" is the mesh model vertices array
- L22 _public function_ `FEdgeMesh(FModelMesh& Model, FTopologicalEntity& TopologicalEntity) : FMesh(Model, TopologicalEntity)`
- L27 _public function_ `void Mesh(int32 StartVertexNodeIndex, int32 EndVertexNodeIndex)`
- L38 _public function_ `int32 GetNodeCount() const`
- L43 _public prototype_ `TArray<double> GetElementLengths() const;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Mesh/Structure/EdgeSegment.h` (Public)


#### class `UE::CADKernel::FEdgeSegment`  
`class FEdgeSegment : public FHaveStates`  
_L21-292_
- inherits: `FHaveStates`
- L24 _private member_ `FTopologicalEdge* Edge;`
- L25 _private member_ `double Coordinates[2];`
- L26 _private member_ `FVector2d USSPoints[2];` — in Uniform Scaled space
- L28 _private member_ `FEdgeSegment* NextSegment;`
- L29 _private member_ `FEdgeSegment* PreviousSegment;`
- L31 _private member_ `FEdgeSegment* ClosedSegment;`
- L33 _private member_ `FSurfacicBoundary Boundary;`
- L34 _private member_ `double AxisMin;`
- L36 _private member_ `double SquareDistanceToClosedSegment;`
- L37 _private member_ `double Length;`
- L39 _private member_ `FIdent ChainIndex;`
- L41 _private member_ `FIdent Id;`
- L42 _private member_ `static FIdent LastId;`
- L45 _public function_ `FEdgeSegment() : Edge(nullptr) , NextSegment(nullptr) , PreviousSegment(nullptr) , ClosedSegment(nullptr) , AxisMin(0.) , SquareDistanceToClosedSegment(HUGE_VALUE) , Length(-1.) , ChainIndex(Ident::Undefined) , Id(0)`
- L58 _public prototype_ `FEdgeSegment(const FEdgeSegment& Segment) = default;`
- L60 _public prototype_ `virtual ~FEdgeSegment() = default;`
- L62 _public function_ `void SetBoundarySegment(bool bInIsInnerLoop, FTopologicalEdge* InEdge, double InStartU, double InEndU, const FVector2d& InStartPoint, const FVector2d& InEndPoint)`
- L89 _public function_ `void UpdateReferences(TMap<int32, FEdgeSegment*>& Map)`
- L112 _public function_ `double GetAxeMin() const`
- L117 _public function_ `FIdent GetChainIndex() const`
- L122 _public function_ `void SetChainIndex(FIdent index)`
- L127 _public function_ `bool IsInner() const`
- L132 _public function_ `void SetInner()`
- L137 _public function_ `FIdent GetId() const`
- L142 _public function_ `FTopologicalEdge* GetEdge() const`
- L147 _public function_ `double GetLength() const`
- L155 _public function_ `FVector2d GetCenter() const` — @return Center of the segment in uniform scaled space
- L163 _public function_ `FVector2d ComputeEdgePoint(double EdgeParamU) const` — @return Point a parameter U of the segment in uniform scaled space
- L172 _public function_ `const FVector2d& GetExtemity(const ELimit Limit) const` — @return the extremity Point of the segment in uniform scaled space
- L177 _public function_ `double GetCoordinate(const ELimit Limit) const`
- L182 _public function_ `bool IsForward() const`
- L190 _public function_ `double ComputeUnorientedSlopeOf(const FEdgeSegment* Segment) const` — Compute the slope of the input Segment according to this.
- L199 _public function_ `double ComputeOrientedSlopeOf(const FEdgeSegment* Segment) const` — Compute the slope of the input Segment according to this.
- L208 _public function_ `double ComputeUnorientedSlopeOf(const FVector2d& Middle, const FVector2d& Projection) const` — Compute the slope of the Segment defined by the two input points according to this.
- L217 _public function_ `double ComputeOrientedSlopeOf(const FVector2d& Middle, const FVector2d& Projection) const` — Compute the slope of the Segment defined by the two input points according to this.
- L223 _public function_ `FEdgeSegment* GetNext() const`
- L228 _public function_ `FEdgeSegment* GetPrevious() const`
- L233 _public function_ `FEdgeSegment* GetCloseSegment() const`
- L238 _public function_ `void ResetCloseData()`
- L248 _public function_ `void SetCloseSegment(FEdgeSegment* InSegmentA, double InDistance)`
- L260 _public function_ `double GetCloseSquareDistance() const`
- L265 _public function_ `void SetNext(FEdgeSegment* Segment)`
- L271 _public function_ `double ComputeEdgeCoordinate(const double SegmentU) const`
- L277 _public function_ `double ComputeDeltaU(const double DeltaLength) const` — Compute the delta U corresponding to a delta length in the 2d space
- L282 _public function_ `FVector2d ProjectPoint(const FVector2d& PointToProject, double& SegmentU) const`
- L288 _private function_ `void SetPrevious(FEdgeSegment* Segment)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CADKernel` (scope `UE`)
- L92 _function_ `` (scope `UE::CADKernel::FEdgeSegment::UpdateReferences`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Mesh/Structure/FaceMesh.h` (Public)


#### class `UE::CADKernel::FFaceMesh`  
`class FFaceMesh : public FMesh`  
_L15-62_
- inherits: `FMesh`
- desc: Define the mesh of a topological face. This mesh is an array of triangle
- L20 _public member_ `TArray<int32> TrianglesVerticesIndex;` — Index of the 3 vertices of each triangle in the local VertexIndices i.e. Triangle(a,b,c) use VertexIndices[a], VertexIndices[b], VertexIndices[c]
- L23 _public member_ `TArray<int32> VerticesGlobalIndex;` — Index of the surface mesh vertices in the MeshModel vertex set
- L26 _public member_ `TArray<FVector3f> Normals;` — Normals of the surface mesh vertices
- L29 _public member_ `TArray<FVector2f> UVMap;` — UV coordinates of the surface mesh vertices
- L32 _public function_ `FFaceMesh(FModelMesh& InMeshModel, FTopologicalEntity& InTopologicalEntity) : FMesh(InMeshModel, InTopologicalEntity)`
- L37 _public function_ `void Init(int32 TriangleNum, int32 VertexNum)`
- L46 _public function_ `void AddTriangle(int32 IndexA, int32 IndexB, int32 IndexC)`
- L58 _public prototype_ `void InverseOrientation();`
- L60 _public prototype_ `void GetNodeIdToCoordinates(TMap<int32, const FVector*>& NodeIdToCoordinates) const;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Mesh/Structure/Mesh.h` (Public)


#### class `UE::CADKernel::FMesh`  
`class FMesh : public FEntityGeom`  
_L15-96_
- inherits: `FEntityGeom`
- L18 _protected member_ `FModelMesh& ModelMesh;`
- L19 _protected member_ `FTopologicalEntity& TopologicalEntity;`
- L21 _protected member_ `int32 StartNodeId;`
- L22 _protected member_ `int32 LastNodeIndex;`
- L24 _protected member_ `TArray<FVector> NodeCoordinates;`
- L25 _protected member_ `int32 MeshModelIndex;`
- L29 _public function_ `FMesh(FModelMesh& InMeshModel, FTopologicalEntity& InTopologicalEntity) : FEntityGeom() , ModelMesh(InMeshModel) , TopologicalEntity(InTopologicalEntity) , StartNodeId(0) , LastNodeIndex(0) , MeshModelIndex(0)`
- L39 _public prototype_ `virtual ~FMesh() = default;`
- L42 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L45 _public function_ `virtual EEntity GetEntityType() const override`
- L50 _public function_ `TArray<FVector>& GetNodeCoordinates()`
- L55 _public function_ `const TArray<FVector>& GetNodeCoordinates() const`
- L60 _public prototype_ `int32 RegisterCoordinates();`
- L62 _public function_ `const int32 GetStartVertexId() const`
- L67 _public function_ `const int32 GetLastVertexIndex() const`
- L72 _public function_ `const int32 GetIndexInMeshModel() const`
- L77 _public function_ `FModelMesh& GetMeshModel()`
- L82 _public function_ `const FModelMesh& GetMeshModel() const`
- L87 _public function_ `const FTopologicalEntity& GetGeometricEntity() const`
- L92 _public function_ `FTopologicalEntity& GetGeometricEntity()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Mesh/Structure/ModelMesh.h` (Public)


#### class `UE::CADKernel::FModelMesh`  
`class FModelMesh : public FEntityGeom`  
_L20-162_
- inherits: `FEntityGeom`
- L24 _private member_ `TArray<TSharedPtr<FCriterion>> Criteria;`
- L26 _private member_ `TArray<TArray<FVector>*> GlobalPointCloud;`
- L27 _private member_ `FIdent LastIdUsed;`
- L29 _private member_ `TArray<FVertexMesh*> VertexMeshes;`
- L30 _private member_ `TArray<FEdgeMesh*> EdgeMeshes;`
- L31 _private member_ `TArray<FFaceMesh*> FaceMeshes;`
- L33 _private member_ `bool QuadAnalyse = false;`
- L34 _private member_ `double MinSize = DOUBLE_SMALL_NUMBER;`
- L35 _private member_ `double MaxSize = HUGE_VALUE;`
- L36 _private member_ `double MaxAngle = DOUBLE_PI;`
- L37 _private member_ `double Sag = HUGE_VALUE;`
- L39 _private function_ `FModelMesh() : FEntityGeom() , LastIdUsed(0)`
- L47 _public function_ `const TArray<TArray<FVector>*>& GetGlobalPointCloud() const`
- L49 _public function_ `int32 GetFaceCount() const`
- L54 _public function_ `int32 GetVertexCount() const`
- L59 _public prototype_ `int32 GetTriangleCount() const;`
- L61 _public function_ `virtual void SpawnIdent(FDatabase& Database) override`
- L73 _public function_ `virtual void ResetMarkersRecursively() const override`
- L82 _public function_ `virtual EEntity GetEntityType() const override`
- L87 _public function_ `const TArray<TSharedPtr<FCriterion>>& GetCriteria() const`
- L92 _public prototype_ `void AddCriterion(TSharedPtr<FCriterion>& Criterion);`
- L94 _public function_ `double GetGeometricTolerance() const`
- L99 _public function_ `double GetMinSize() const`
- L104 _public function_ `double GetMaxSize() const`
- L109 _public function_ `double GetAngleCriteria()`
- L114 _public function_ `double GetSag() const`
- L119 _public function_ `void AddMesh(FVertexMesh& Mesh)`
- L124 _public function_ `void AddMesh(FEdgeMesh& Mesh)`
- L129 _public function_ `void AddMesh(FFaceMesh& Mesh)`
- L134 _public function_ `void RegisterCoordinates(TArray<FVector>& Coordinates, int32& OutStartVertexId, int32& OutIndex)`
- L147 _public prototype_ `const FVertexMesh* GetMeshOfVertexNodeId(const int32 Id) const;`
- L149 _public prototype_ `void GetNodeCoordinates(TArray<FVector>& NodeCoordinates) const;`
- L150 _public prototype_ `void GetNodeCoordinates(TArray<FVector3f>& NodeCoordinates) const;`
- L152 _public prototype_ `const TArray<FMesh*>& GetMeshes() const;`
- L154 _public function_ `const TArray<FFaceMesh*>& GetFaceMeshes() const`
- L160 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Mesh/Structure/ThinZone2D.h` (Public)


#### enum `UE::CADKernel::EThinZone2DType`  
`enum class EThinZone2DType : uint8`  
_L14-23_
- L16 _public enumerator_ `Undefined = 0`
- L17 _public enumerator_ `Global` — a Surface globally thin
- L18 _public enumerator_ `PeakStart` — an extremity of a Surface that is fine
- L19 _public enumerator_ `PeakEnd` — an extremity of a Surface that is fine
- L20 _public enumerator_ `Butterfly` — the outer loop that is like a bow tie (Butterfly)
- L21 _public enumerator_ `BetweenLoops` — a bow tie between two different loops
- L22 _public enumerator_ `TooSmall` — -> to delete

#### enum `UE::CADKernel::ESide`  
`enum class ESide : uint8`  
_L25-30_
- L27 _public enumerator_ `First = 0`
- L28 _public enumerator_ `Second`
- L29 _public enumerator_ `None`

#### class `UE::CADKernel::FThinZoneSide`  
`class FThinZoneSide : public FHaveStates`  
_L39-154_
- inherits: `FHaveStates`
- L44 _private member_ `TArray<FEdgeSegment> Segments;`
- L45 _private member_ `FThinZoneSide& FrontSide;`
- L47 _private member_ `TArray<FTopologicalEdge*> Edges;`
- L49 _private member_ `double SideLength;`
- L50 _private member_ `double MediumThickness;`
- L51 _private member_ `double MaxThickness;`
- L55 _public prototype_ `FThinZoneSide(FThinZoneSide* InFrontSide, const TArray<FEdgeSegment*>& InSegments);`
- L57 _public prototype_ `virtual ~FThinZoneSide() = default;`
- L59 _public function_ `void Empty()`
- L64 _public function_ `const FEdgeSegment& GetFirst() const`
- L69 _public function_ `const FEdgeSegment& GetLast() const`
- L78 _public prototype_ `void GetEdges(TArray<FTopologicalEdge*>& OutEdges) const;` — Use Marker1 flag to selected edges once Edge Marker1 has to be reset after.
- L80 _public function_ `const TArray<FTopologicalEdge*>& GetEdges() const`
- L85 _public function_ `TArray<FTopologicalEdge*>& GetEdges()`
- L90 _public prototype_ `void AddToEdge();`
- L92 _public prototype_ `void CleanMesh();`
- L94 _public function_ `const TArray<FEdgeSegment>& GetSegments() const`
- L99 _public function_ `TArray<FEdgeSegment>& GetSegments()`
- L104 _public prototype_ `EMeshingState GetMeshingState() const;`
- L106 _public function_ `double Length() const`
- L111 _public function_ `double GetThickness() const`
- L116 _public function_ `double GetMaxThickness() const`
- L121 _public function_ `bool IsInner() const`
- L130 _public function_ `bool IsClosed() const`
- L139 _public function_ `FThinZoneSide& GetFrontThinZoneSide()`
- L144 _public prototype_ `void CheckEdgesZoneSide();`
- L145 _public prototype_ `void SetEdgesZoneSide(ESide Side);`
- L147 _public prototype_ `int32 GetImposedPointCount();`
- L149 _public prototype_ `void GetExistingMeshNodes(const FTopologicalFace& Face, FModelMesh& MeshModel, FReserveContainerFunc& Reserve, FAddMeshNodeFunc& AddMeshNode, const bool bWithTolerance) const;`
- L152 _private prototype_ `void ComputeThicknessAndLength();`

#### class `UE::CADKernel::FThinZone2D`  
`class FThinZone2D : public FHaveStates`  
_L156-312_
- inherits: `FHaveStates`
- L160 _private member_ `FThinZoneSide SideA;`
- L161 _private member_ `FThinZoneSide SideB;`
- L163 _private member_ `EThinZone2DType Category;`
- L165 _private member_ `double Thickness;`
- L166 _private member_ `double MaxThickness;`
- L168 _private member_ `bool bIsSwap = false;`
- L176 _public function_ `FThinZone2D(const TArray<FEdgeSegment*>& InFirstSideSegments, const TArray<FEdgeSegment*>& InSecondSideSegments) : SideA(&SideB, InFirstSideSegments) , SideB(&SideA, InSecondSideSegments) , Category(EThinZone2DType::Undefined)` — FThinZone2D::FThinZoneSides are maded with a copy of TArray<FEdgeSegment*> into TArray<FEdgeSegment> to break the link with TFactory<FEdgeSegment> of FThinZone2DFinder So FThinZone2D can be transfered into the FTopologicalFace
- L184 _public prototype_ `virtual ~FThinZone2D() = default;`
- L186 _public function_ `void Empty()`
- L193 _public function_ `double GetThickness() const`
- L198 _public function_ `double GetMaxThickness() const`
- L203 _public function_ `const FThinZoneSide& GetSide(ESide Side) const`
- L208 _public function_ `FThinZoneSide& GetSide(ESide Side)`
- L213 _public function_ `FThinZoneSide& GetFirstSide()`
- L218 _public function_ `FThinZoneSide& GetSecondSide()`
- L223 _public function_ `const FThinZoneSide& GetFirstSide() const`
- L228 _public function_ `const FThinZoneSide& GetSecondSide() const`
- L233 _public function_ `EThinZone2DType GetCategory() const`
- L238 _public prototype_ `static void SetPeakEdgesMarker(const TArray<const FTopologicalEdge*>&);`
- L240 _public function_ `double Length() const`
- L245 _public function_ `double GetMaxSideLength() const`
- L250 _public function_ `void SetCategory(EThinZone2DType InType)`
- L259 _public function_ `void GetEdges(TArray<FTopologicalEdge*>& OutSideAEdges, TArray<FTopologicalEdge*>& OutSideBEdges) const` — Use Marker 3 flag to count edge once Edge Marker 3 has to be reset after.
- L269 _public function_ `void CheckEdgesZoneSide()` — Use Marker 1 and 2 flags they have to be reset after.
- L278 _public function_ `void SetEdgesZoneSide()` — For each edge of the zone, set Marker1 flag if edge is in first zone, and Marker2 if edge is in second zone
- L284 _public prototype_ `void AddToEdge();`
- L286 _public function_ `void Swap()`
- L307 _public prototype_ `void Display(const FString& Title, EVisuProperty VisuProperty) const;`
- L311 _private prototype_ `void Finalize();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CADKernel` (scope `UE`)
- L36 _typedef_ `using FReserveContainerFunc = TFunction<void(int32)>;` (scope `UE::CADKernel`)
- L37 _typedef_ `using FAddMeshNodeFunc = TFunction<void(const int32, const FVector2d&, const double, const FEdgeSegment&, const FPairOfIndex&)>;` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Mesh/Structure/VertexMesh.h` (Public)


#### class `UE::CADKernel::FVertexMesh`  
`class FVertexMesh : public FMesh`  
_L10-24_
- inherits: `FMesh`
- L15 _public function_ `FVertexMesh(FModelMesh& Model, FTopologicalEntity& TopologicalEntity) : FMesh(Model, TopologicalEntity)`
- L20 _public function_ `int32 GetMesh() const`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/Body.h` (Public)


#### class `UE::CADKernel::FBody`  
`class FBody : public FTopologicalShapeEntity`  
_L21-157_
- inherits: `FTopologicalShapeEntity`
- L26 _private member_ `TArray<TSharedPtr<FShell>> Shells;`
- L28 _private prototype_ `FBody() = default;`
- L30 _private function_ `FBody(const TArray<TSharedPtr<FShell>>& InShells)`
- L43 _public function_ `virtual ~FBody() override`
- L48 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L55 _public function_ `virtual void SpawnIdent(FDatabase& Database) override`
- L65 _public function_ `virtual void ResetMarkersRecursively() const override`
- L72 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L75 _public function_ `virtual EEntity GetEntityType() const override`
- L80 _public prototype_ `void AddShell(TSharedRef<FShell> Shell);`
- L82 _public prototype_ `void RemoveEmptyShell();`
- L84 _public prototype_ `virtual void Remove(const FTopologicalShapeEntity* ShellToRemove) override;`
- L86 _public function_ `virtual void Empty() override`
- L95 _public function_ `const TArray<TSharedPtr<FShell>>& GetShells() const`
- L100 _public function_ `int32 ShellCount() const`
- L105 _public function_ `bool IsEmpty() const`
- L110 _public function_ `virtual int32 FaceCount() const override`
- L120 _public function_ `virtual void GetFaces(TArray<FTopologicalFace*>& Faces) override`
- L128 _public function_ `virtual void CompleteMetaData() override`
- L137 _public function_ `virtual void PropagateBodyOrientation() override`
- L145 _public function_ `void Orient()`
- L154 _public prototype_ `virtual void FillTopologyReport(FTopologyReport& Report) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/Linkable.h` (Public)


#### class `UE::CADKernel::TLinkable`  
`template<typename EntityType, typename LinkType> class TLinkable : public FTopologicalEntity`  
_L14-201_
- inherits: `FTopologicalEntity`
- L17 _protected member_ `mutable TSharedPtr<LinkType> TopologicalLink;`
- L20 _public prototype_ `TLinkable() = default;`
- L22 _public function_ `virtual ~TLinkable() override`
- L27 _public function_ `void Finalize()`
- L33 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L39 _public function_ `virtual void Empty() override`
- L44 _public function_ `const TSharedRef<const EntityType> GetLinkActiveEntity() const`
- L51 _public function_ `TSharedRef<EntityType> GetLinkActiveEntity()`
- L58 _public function_ `bool IsActiveEntity() const`
- L70 _public function_ `void Activate()`
- L76 _public function_ `virtual TSharedPtr<LinkType> GetLink() const`
- L82 _public function_ `virtual TSharedPtr<LinkType> GetLink()`
- L88 _public function_ `void ResetTopologicalLink()`
- L94 _public function_ `bool IsLinkedTo(const TSharedRef<EntityType>& Entity) const`
- L103 _public function_ `bool IsLinkedTo(const EntityType& Entity) const`
- L112 _public function_ `int32 GetTwinEntityCount() const`
- L118 _public function_ `bool HasTwin() const`
- L123 _public function_ `const TArray<EntityType*>& GetTwinEntities() const`
- L129 _public function_ `virtual void RemoveFromLink()`
- L139 _public function_ `void UnlinkTwinEntities()` — Unlink all twin entities
- L148 _public function_ `const bool IsThinZone() const`
- L153 _public function_ `virtual void SetThinZoneMarker()`
- L158 _public function_ `virtual void ResetThinZone()`
- L163 _public function_ `virtual void ResetMarkersRecursively() const override`
- L171 _protected function_ `void MakeLink(EntityType& Twin)`
- L197 _protected function_ `void SetTopologicalLink(TSharedPtr<LinkType> Link)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/Model.h` (Public)


#### class `UE::CADKernel::FModel`  
`class FModel : public FTopologicalShapeEntity`  
_L21-183_
- inherits: `FTopologicalShapeEntity`
- L27 _protected member_ `TArray<TSharedPtr<FBody>> Bodies;`
- L29 _protected function_ `FModel()`
- L36 _public function_ `virtual ~FModel() override`
- L41 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L56 _public function_ `virtual void SpawnIdent(FDatabase& Database) override`
- L66 _public function_ `virtual void ResetMarkersRecursively() const override`
- L73 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L76 _public function_ `virtual EEntity GetEntityType() const override`
- L81 _public prototype_ `void AddEntity(TSharedRef<FTopologicalEntity> InEntity);`
- L83 _public function_ `void Append(TArray<TSharedPtr<FBody>>& InNewBody)`
- L88 _public function_ `void Add(const TSharedPtr<FBody>& InBody)`
- L93 _public function_ `virtual void Empty() override`
- L99 _public function_ `virtual void Remove(const FTopologicalShapeEntity* InBody) override`
- L113 _public prototype_ `void RemoveEmptyBodies();`
- L115 _public prototype_ `bool Contains(TSharedPtr<FTopologicalEntity> InEntity);`
- L120 _public function_ `void Copy(const TSharedPtr<FModel>& OtherModel)` — Copy the body and face arrays of other model
- L128 _public function_ `void Copy(const FModel& OtherModel)` — Copy the body and face arrays of other model
- L137 _public function_ `void Merge(FModel& OtherModel)` — Copy the body and face arrays of other model Empty other model arrays
- L143 _public function_ `int32 EntityCount() const`
- L148 _public function_ `int32 BodyCount() const`
- L153 _public function_ `bool IsEmpty() const`
- L158 _public prototype_ `virtual void GetFaces(TArray<FTopologicalFace*>& OutFaces) override;`
- L160 _public prototype_ `virtual int32 FaceCount() const override;`
- L162 _public function_ `const TArray<TSharedPtr<FBody>>& GetBodies() const`
- L167 _public prototype_ `virtual void PropagateBodyOrientation() override;`
- L169 _public prototype_ `virtual void CompleteMetaData() override;`
- L176 _public prototype_ `void CheckTopology();` — Check topology of each body
- L179 _public prototype_ `virtual void FillTopologyReport(FTopologyReport& Report) const override;`
- L182 _public prototype_ `void Orient();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CADKernel` (scope `UE`)
- L106 _function_ `int32 Index = Bodies.IndexOfByPredicate([&](const TSharedPtr<FBody>& Body) { return (InBody == (FTopologicalShapeEntity*) Body.Get()); });` (scope `UE::CADKernel::FModel::Remove`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/Shell.h` (Public)


#### class `UE::CADKernel::FOrientedFace`  
`class FOrientedFace : public TOrientedEntity<FTopologicalFace>`  
_L29-41_
- inherits: `TOrientedEntity<FTopologicalFace>`
- L32 _public function_ `FOrientedFace(TSharedPtr<FTopologicalFace>& InEntity, EOrientation InOrientation) : TOrientedEntity(InEntity, InOrientation)`
- L37 _public function_ `FOrientedFace() : TOrientedEntity()`

#### class `UE::CADKernel::FShell`  
`class FShell : public FTopologicalShapeEntity`  
_L43-197_
- inherits: `FTopologicalShapeEntity`
- L48 _private member_ `TArray<FOrientedFace> TopologicalFaces;`
- L50 _private prototype_ `FShell() = default;`
- L52 _private function_ `FShell(const TArray<FOrientedFace> InTopologicalFaces, bool bIsInnerShell = false) : FTopologicalShapeEntity() , TopologicalFaces(InTopologicalFaces)`
- L62 _private prototype_ `FShell(const TArray<TSharedPtr<FTopologicalFace>>& InTopologicalFaces, bool bIsInnerShell = true);`
- L64 _private prototype_ `FShell(const TArray<TSharedPtr<FTopologicalFace>>& InTopologicalFaces, const TArray<EOrientation>& InOrientations, bool bIsInnerShell = true);`
- L69 _public function_ `virtual ~FShell() override`
- L74 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L80 _public function_ `virtual void SpawnIdent(FDatabase& Database) override`
- L90 _public function_ `virtual void ResetMarkersRecursively() const override`
- L96 _public prototype_ `void RemoveFaces();`
- L98 _public prototype_ `void RemoveDeletedOrDegeneratedFaces();`
- L100 _public prototype_ `virtual void Empty() override;`
- L102 _public prototype_ `void Add(TSharedRef<FTopologicalFace> InTopologicalFace, EOrientation InOrientation);`
- L103 _public prototype_ `void Add(TArray<FTopologicalFace*>& Faces);`
- L106 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L109 _public function_ `virtual EEntity GetEntityType() const override`
- L114 _public function_ `virtual int32 FaceCount() const override`
- L119 _public function_ `void ReplaceFaces(TArray<FOrientedFace>& NewFaces)`
- L125 _public function_ `const TArray<FOrientedFace>& GetFaces() const`
- L130 _public function_ `TArray<FOrientedFace>& GetFaces()`
- L135 _public prototype_ `virtual void GetFaces(TArray<FTopologicalFace*>& OutFaces) override;`
- L137 _public prototype_ `virtual void Merge(TSharedPtr<FShell>& Shell);`
- L139 _public prototype_ `virtual void PropagateBodyOrientation() override;`
- L141 _public prototype_ `virtual void CompleteMetaData() override;`
- L146 _public prototype_ `virtual void UpdateShellOrientation();` — Update each FOrientedFace::Direction according to FOrientedFace::Entity->IsBackOriented() flag
- L148 _public prototype_ `void CheckTopology(TArray<FFaceSubset>& Subshells);`
- L150 _public function_ `void UnlinkFromOther(TArray<FTopologicalVertex*>& OutVerticesToLink)`
- L158 _public prototype_ `virtual void FillTopologyReport(FTopologyReport& Report) const override;`
- L164 _public prototype_ `bool IsOpenShell();` — @return true if the shell has at least one border edge
- L166 _public function_ `bool IsInner() const`
- L171 _public function_ `bool IsOuter() const`
- L176 _public function_ `void SetInner()`
- L181 _public function_ `void SetOuter()`
- L193 _public prototype_ `int32 Orient();` — Orient each connected sub-shell: each connected face will have the same orientation Each connected subset of faces will be oriented: - towards the outside if it's a closed subset (without border edge) - according to its main/average orientation if it's an open shell @return SwapFaceCount for report purpose
- L195 _public prototype_ `virtual void Remove(const FTopologicalShapeEntity*) override;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CADKernel` (scope `UE`)
- L24 _namespace_ `namespace ShellTools` (scope `UE::CADKernel`)
- L26 _prototype_ `void UnlinkFromOther(TArray<FTopologicalFace*>& Faces, TArray<FTopologicalVertex*>& VerticesToLink);` (scope `UE::CADKernel::ShellTools`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/TopologicalEdge.h` (Public)


#### struct `UE::CADKernel::FImposedCuttingPoint`  
`struct FImposedCuttingPoint`  
_L26-45_
- desc: Cutting point used for thin zone purpose
- L31 _public member_ `const double Coordinate = 0;` — coordinate of the edge's mesh nodes
- L32 _public member_ `const int32 OppositNodeIndex = -1;`
- L33 _public member_ `double DeltaU = 0;`
- L35 _public function_ `FImposedCuttingPoint()`
- L39 _public function_ `FImposedCuttingPoint(const double InCoordinate, const int32 NodeIndex1, const double InDeltaU = 0.) : Coordinate(InCoordinate) , OppositNodeIndex(NodeIndex1) , DeltaU(InDeltaU)`

#### class `UE::CADKernel::FTopologicalEdge`  
`class FTopologicalEdge : public TLinkable<FTopologicalEdge, FEdgeLink>`  
_L62-886_
- inherits: `TLinkable<FTopologicalEdge,FEdgeLink>`
- L69 _private member_ `const double FactorToComputeMaxTol = 0.1;`
- L73 _protected member_ `TSharedPtr<FTopologicalVertex> StartVertex;`
- L74 _protected member_ `TSharedPtr<FTopologicalVertex> EndVertex;`
- L79 _protected member_ `FLinearBoundary Boundary;` — The edge is oriented in the curve orientation i.e. StartCoordinate < EndCoordinate
- L81 _protected member_ `TSharedPtr<FRestrictionCurve> Curve;`
- L82 _protected member_ `mutable double Length3D = -1.;`
- L85 _protected member_ `mutable double Max2DTolerance = -1;` — To avoid huge tolerance in case of degenerated edge, the max tol is defined as Length3D / 10.
- L87 _protected member_ `FTopologicalLoop* Loop = nullptr;`
- L89 _protected member_ `TSharedPtr<FEdgeMesh> Mesh;`
- L94 _protected member_ `TArray<FCuttingPoint> CuttingPointUs;` — Final U coordinates of the edge's mesh nodes
- L99 _protected member_ `TArray<FImposedCuttingPoint> ImposedCuttingPointUs;` — U coordinates of the edge's mesh nodes for thin zone purpose
- L101 _protected member_ `TArray<FThinZoneSide*> ThinZoneSides;`
- L102 _protected member_ `TArray<FLinearBoundary> ThinZoneBounds;`
- L107 _protected member_ `TArray<double> CrossingPointUs;` — Temporary discretization of the edge used to compute the mesh of the edge
- L112 _protected member_ `TArray<double> CrossingPointDeltaUMins;` — Min delta U at the crossing points to respect meshing criteria
- L117 _protected member_ `TArray<double> CrossingPointDeltaUMaxs;` — Max delta U at the crossing points to respect meshing criteria
- L125 _private prototype_ `FTopologicalEdge(const TSharedRef<FRestrictionCurve>& InCurve, const TSharedRef<FTopologicalVertex>& InVertex1, const TSharedRef<FTopologicalVertex>& InVertex2, const FLinearBoundary& InBoundary);` — MANDATORY Constructors of FEdge cannot be used directly, use FEdge::Make to create an FEdge object.
- L126 _private prototype_ `FTopologicalEdge(const TSharedRef<FRestrictionCurve>& InCurve, const TSharedRef<FTopologicalVertex>& InVertex1, const TSharedRef<FTopologicalVertex>& InVertex2);`
- L127 _private prototype_ `FTopologicalEdge(const TSharedRef<FRestrictionCurve>& InCurve, const FLinearBoundary& InBoundary);`
- L128 _private prototype_ `FTopologicalEdge(const TSharedRef<FSurface>& InSurface, const FVector2d& InCoordinateVertex1, const TSharedRef<FTopologicalVertex>& InVertex1, const FVector2d& InCoordinateVertex2, const TSharedRef<FTopologicalVertex>& InVertex2);`
- L130 _private prototype_ `FTopologicalEdge() = default;`
- L132 _private function_ `void SetLoop(FTopologicalLoop& NewBoundary)`
- L137 _private function_ `void RemoveLoop()`
- L148 _private prototype_ `bool CheckVertices();` — Used by FEdge::Make Sort vertex coordinate to ensure that start coordinate < end coordinate Swap vertices if needed i.e. to ensure that 3D point at start (and end) coordinate is near to start (and end) vertex 3d coordinates @return false if one vertex is too far to the associated curve 3d point
- L152 _public prototype_ `static TSharedPtr<FTopologicalEdge> Make(const TSharedRef<FRestrictionCurve>& InCurve, const TSharedRef<FTopologicalVertex>& InVertex1, const TSharedRef<FTopologicalVertex>& InVertex2, const FLinearBoundary& InBoundary);`
- L153 _public prototype_ `static TSharedPtr<FTopologicalEdge> Make(const TSharedRef<FRestrictionCurve>& InCurve, const TSharedRef<FTopologicalVertex>& InVertex1, const TSharedRef<FTopologicalVertex>& InVertex2);`
- L154 _public prototype_ `static TSharedPtr<FTopologicalEdge> Make(const TSharedRef<FRestrictionCurve>& InCurve, const FLinearBoundary& InBoundary);`
- L155 _public prototype_ `static TSharedPtr<FTopologicalEdge> Make(const TSharedRef<FRestrictionCurve>& InCurve);`
- L160 _public prototype_ `static TSharedPtr<FTopologicalEdge> Make(const TSharedRef<FSurface>& InSurface, const FVector2d& InCoordinateVertex1, const TSharedRef<FTopologicalVertex>& InVertex1, const FVector2d& InCoordinateVertex2, const TSharedRef<FTopologicalVertex>& InVertex2);` — Build an edge to connect two vertices carried by a 2d segment
- L165 _public prototype_ `static TSharedPtr<FTopologicalEdge> ReturnIfValid(TSharedRef<FTopologicalEdge>& InEdge, bool bCheckVertices);` — To check the build edge before returning it or return TSharedPtr<FTopologicalEdge>() if the edge is not valid
- L167 _public function_ `virtual ~FTopologicalEdge() override`
- L172 _public prototype_ `virtual void Empty() override;`
- L174 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L186 _public prototype_ `virtual void SpawnIdent(FDatabase& Database) override;`
- L188 _public function_ `virtual void ResetMarkersRecursively() const override`
- L198 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L201 _public function_ `double GetTolerance3D() const`
- L206 _public function_ `double GetTolerance2DAt(double Coordinate) const`
- L211 _public function_ `virtual EEntity GetEntityType() const override`
- L218 _public prototype_ `void LinkVertex();`
- L224 _public prototype_ `bool CheckIfDegenerated() const;` — Checks if the carrier curve is degenerated i.e. the 2d length of the curve is nearly zero If the 3d length is nearly zero, the edge is flag as degenerated
- L231 _public prototype_ `bool IsLinkableTo(const FTopologicalEdge& Edge, double EdgeLengthTolerance) const;` — It can be linked to the edge if : - they have the same length (5% or +/- EdgeLengthTolerance) - they are ~tangent at their extremities i.e @see IsTangentAtExtremitiesWith
- L241 _public prototype_ `void LinkIfCoincident(FTopologicalEdge& OtherEdge, double EdgeLengthTolerance, double SquareJoiningTolerance);` — Link two edges. Two edges can be linked if : - Their extremities coincide following SquareJoiningTolerance's criteria, - They are linkable (@see IsLinkableTo) This step must be done when the loop is finalize because in some case edges can be delete, split, extend... to avoid problems
- L248 _public prototype_ `void Link(FTopologicalEdge& OtherEdge);` — Link with the other edge. No check is performed except check if degenerated ot deleted. If checks are needed, use LinkIfCoincident
- L254 _public prototype_ `void Disjoin();` — Remove the edge and the extremity vertices of the linked entity vs UnlinkTwinEntities delete only the edge link
- L260 _public function_ `void Unlink()` — Remove the edge and the extremity vertices of the linked entity vs UnlinkTwinEntities delete only the edge link
- L266 _public function_ `TSharedRef<const FTopologicalEdge> GetLinkActiveEdge() const`
- L271 _public function_ `TSharedRef<FTopologicalEdge> GetLinkActiveEdge()`
- L276 _public function_ `FTopologicalEdge* GetFirstTwinEdge() const`
- L292 _public function_ `FTopologicalEdge* GetTwinEdge() const`
- L305 _public prototype_ `bool IsSameDirection(const FTopologicalEdge& Edge) const;` — @return true if the twin edge is in the same direction as this
- L310 _public prototype_ `bool IsTangentAtExtremitiesWith(const FTopologicalEdge & Edge) const;` — @return true if it is ~tangent with the edge at their extremities i.e Cos(tangents) > cos(30 deg)
- L315 _public function_ `bool IsClosed() const` — @return true if the edge is self connected at its extremities
- L338 _public prototype_ `void ReplaceEdgeVertex(bool bIsStartVertex, TSharedRef<FTopologicalVertex>& NewVertex);` — This function is used to : - sew exactly two edges of the same loop - prepare to disconnect two edges connected by the same vertex OldVertex = bStartVertex ? StartVertex : EndVertex OldVertex can be an extremity of other edges OldVertex can be link to other vertices (TopologicalLink can be valid or not) NewVertex can be an extremity of other edges NewVertex can be linked to other vertices (TopologicalLink can be valid or not) NewVertex can be not linked to OldVertex After the process: OldVertex is no more connected to this edge but stay connected to its other linked edges If OldVertex is isolated (not connected to any edge), OldVertex is deleted otherwise OldVertex is linked to NewVertex
- L343 _public function_ `const FTopologicalLoop* GetLoop() const` — @return the containing boundary
- L351 _public function_ `FTopologicalLoop* GetLoop()` — @return the containing boundary
- L359 _public prototype_ `FTopologicalFace* GetFace() const;` — @return the carrier topological face
- L363 _public function_ `const TSharedRef<FTopologicalVertex> GetStartVertex(EOrientation Forward) const`
- L368 _public function_ `const TSharedRef<FTopologicalVertex> GetEndVertex(EOrientation Forward) const`
- L373 _public function_ `const TSharedRef<FTopologicalVertex> GetStartVertex(bool Forward) const`
- L378 _public function_ `const TSharedRef<FTopologicalVertex> GetEndVertex(bool Forward) const`
- L383 _public function_ `const TSharedRef<FTopologicalVertex> GetStartVertex() const`
- L388 _public function_ `const TSharedRef< FTopologicalVertex> GetEndVertex() const`
- L393 _public function_ `TSharedRef<FTopologicalVertex> GetStartVertex()`
- L398 _public function_ `TSharedRef<FTopologicalVertex> GetEndVertex()`
- L403 _public function_ `TSharedPtr<FTopologicalVertex> GetOtherVertex(const TSharedRef<FTopologicalVertex>& Vertex)`
- L408 _public function_ `FTopologicalVertex* GetOtherVertex(FTopologicalVertex& Vertex)`
- L413 _public function_ `const FTopologicalVertex* GetOtherVertex(const FTopologicalVertex& Vertex) const`
- L418 _public function_ `const TSharedPtr<FTopologicalVertex> GetOtherVertex(const TSharedRef<FTopologicalVertex>& Vertex) const`
- L423 _public prototype_ `void SetStartVertex(const double NewCoordinate);`
- L424 _public prototype_ `void SetEndVertex(const double NewCoordinate);`
- L426 _public prototype_ `void SetStartVertex(const double NewCoordinate, const FVector& NewPoint3D);`
- L427 _public prototype_ `void SetEndVertex(const double NewCoordinate, const FVector& NewPoint3D);`
- L431 _public function_ `const FLinearBoundary& GetBoundary() const`
- L436 _public function_ `double GetStartCurvilinearCoordinates() const`
- L441 _public function_ `double GetEndCurvilinearCoordinates() const`
- L449 _public function_ `FVector GetStartBarycenter()` — @return the 3d coordinate of the start vertex (the barycenter of the twin vertices)
- L457 _public function_ `FVector GetEndBarycenter()` — @return the 3d coordinate of the end vertex (the barycenter of the twin vertices)
- L465 _public function_ `FVector GetStartCoordinate()` — @return the 3d coordinate of the start vertex (prefer GetStartBarycenter)
- L473 _public function_ `FVector GetEndCoordinate()` — @return the 3d coordinate of the end vertex (prefer GetEndBarycenter)
- L478 _public prototype_ `void GetTangentsAtExtremities(FVector& StartTangent, FVector& EndTangent, bool bForward) const;`
- L479 _public function_ `void GetTangentsAtExtremities(FVector& StartTangent, FVector& EndTangent, EOrientation Orientation) const`
- L486 _public function_ `const FEdgeMesh* GetMesh() const`
- L499 _public prototype_ `FEdgeMesh& GetOrCreateMesh(FModelMesh& MeshModel);`
- L505 _public prototype_ `void RemovePreMesh();` — If the mesh of the edge is not built, Empty the CuttingPoints This allows to recompute a new discretization of the mesh based among other things on a new imposed cutting points (mesh of thin zone process)
- L507 _public prototype_ `const FTopologicalEdge* GetPreMeshedTwin() const;`
- L508 _public function_ `FTopologicalEdge* GetPreMeshedTwin()`
- L518 _public prototype_ `void ComputeCrossingPointCoordinates();` — Generate a sampling of the curve. This sampling is used by apply meshing criteria function to defined the optimal mesh of the edge. This sampling is saved in CrossingPointUs TArray.
- L520 _public prototype_ `int32 EvaluateCuttingPointNum();`
- L522 _public function_ `void InitDeltaUs()`
- L531 _public function_ `const TArray<double>& GetCrossingPointUs() const`
- L536 _public function_ `TArray<double>& GetCrossingPointUs()`
- L541 _public function_ `TArray<double>& GetDeltaUMins()`
- L546 _public function_ `TArray<double>& GetDeltaUMaxs()`
- L551 _public function_ `const TArray<double>& GetDeltaUMaxs() const`
- L556 _public function_ `double GetDeltaUFor(double Coordinate, int32& Index) const`
- L576 _public function_ `TArray<FCuttingPoint>& GetCuttingPoints()`
- L581 _public function_ `const TArray<FCuttingPoint>& GetCuttingPoints() const`
- L586 _public prototype_ `TArray<double> GetCuttingPointCoordinates() const;`
- L588 _public prototype_ `void TransferCuttingPointFromMeshedEdge(bool bOnlyWithOppositeNode, FAddCuttingPointFunc AddCuttingPoint);`
- L593 _public prototype_ `TArray<double> GetPreElementLengths() const;` — Compute the lengths of each pre-elements of the edge i.e the elements based of the cutting points of the edges.
- L596 _public prototype_ `void SortImposedCuttingPoints();` — For thin zone purpose
- L598 _public function_ `const TArray<FImposedCuttingPoint>& GetImposedCuttingPoints() const`
- L603 _public function_ `void AddThinZone(FThinZoneSide* InThinZoneSide, const FLinearBoundary& InThinZoneBounds)`
- L612 _public function_ `int32 GetThinZoneCount() const`
- L617 _public function_ `const TArray<FThinZoneSide*>& GetThinZoneSides() const`
- L622 _public function_ `const TArray<FLinearBoundary>& GetThinZoneBounds() const`
- L627 _public prototype_ `void AddImposedCuttingPointU(const double ImposedCuttingPointU, const int32 OppositeNodeIndex, const double DeltaU);`
- L628 _public prototype_ `void AddTwinsCuttingPoint(const double Coord, const double DeltaU);`
- L630 _public prototype_ `void GenerateMeshElements(FModelMesh& MeshModel);`
- L634 _public function_ `TSharedRef<FRestrictionCurve> GetCurve() const`
- L639 _public function_ `TSharedRef<FRestrictionCurve> GetCurve()`
- L644 _public prototype_ `void ComputeLength();`
- L645 _public prototype_ `double Length() const;`
- L650 _public prototype_ `void Sample(const double DesiredSegmentLength, TArray<double>& OutCoordinates) const;` — Samples the curve with segments of a desired length
- L656 _public function_ `void EvaluatePoint(double InCoordinate, int32 Derivative, FCurvePoint& Point) const` — Exact evaluation of point on the 3D curve According to derivativeOrder Gradient of the point (DerivativeOrder = 1) and Laplacian (DerivativeOrder = 1) can also be return
- L665 _public function_ `void EvaluatePoints(const TArray<double>& InCoordinates, int32 DerivativeOrder, TArray<FCurvePoint>& OutPoints) const` — Exact evaluation of points on the 3D curve According to derivativeOrder Gradient of the point (DerivativeOrder = 1) and Laplacian (DerivativeOrder = 1) can also be return
- L673 _public function_ `void ApproximatePoints(const TArray<double>& InCoordinates, TArray<FVector>& OutPoints) const` — Approximation of 3D points compute with carrier surface 3D polyline
- L681 _public function_ `FVector2d Approximate2DPoint(const double InCoordinate) const` — Approximation of 2D point defined by its coordinate compute with carrier surface 2D polyline
- L689 _public function_ `void Approximate2DPoints(const TArray<double>& InCoordinates, TArray<FVector2d>& OutPoints) const` — Approximation of 2D points defined by its coordinates compute with carrier surface 2D polyline
- L697 _public function_ `void ApproximatePolyline(FSurfacicPolyline& Polyline) const` — Approximation of surfacic polyline (points 2d, 3d, normals, tangents) defined by its coordinates compute with carrier surface polyline
- L702 _public function_ `FVector GetTangentAt(const double InCoordinate) const`
- L707 _public function_ `FVector2d GetTangent2DAt(const double InCoordinate) const`
- L715 _public prototype_ `FVector GetTangentAt(const FTopologicalVertex& InVertex);` — Return the tangent at the input vertex
- L716 _public prototype_ `FVector2d GetTangent2DAt(const FTopologicalVertex& InVertex);`
- L722 _public function_ `template<class PointType> double ProjectPoint(const PointType& InPointToProject, PointType& OutProjectedPoint) const` — Project Point (2D or 3D) on the polyline (2D or 3D) and return the coordinate of the projected point
- L730 _public function_ `void ProjectPoints(const TArray<FVector>& InPointsToProject, TArray<double>& OutProjectedPointCoords, TArray<FVector>& OutProjectedPoints) const` — Project a set of points on the 3D polyline and return the coordinate of the projected point
- L738 _public function_ `void ProjectTwinEdgePoints(const TArray<FVector>& InPointsToProject, bool bSameOrientation, TArray<double>& OutProjectedPointCoords) const` — Project a set of points of a twin edge on the 3D polyline and return the coordinate of the projected point
- L747 _public prototype_ `void ProjectTwinEdgePointsOn2DCurve(const TSharedRef<FTopologicalEdge>& InTwinEdge, const TArray<double>& InTwinEdgePointCoords, TArray<FVector2d>& OutPoints2D);` — Compute 2D points of the edge coincident the points of the twin edge defined by their coordinates
- L749 _public function_ `void ComputeIntersectionsWithIsos(const TArray<double>& InIsoCoordinates, const EIso InTypeIso, const FSurfacicTolerance& ToleranceIso, TArray<double>& OutIntersection) const`
- L758 _public function_ `template<class PointType> void GetDiscretization2DPoints(EOrientation Orientation, TArray<PointType>& OutPoints) const` — Get the discretization points of the edge and add them to the outpoints TArray
- L763 _public prototype_ `double TransformLocalCoordinateToActiveEdgeCoordinate(const double LocalCoordinate) const;`
- L764 _public prototype_ `double TransformActiveEdgeCoordinateToLocalCoordinate(const double ActiveEdgeCoordinate) const;`
- L765 _public prototype_ `double TransformTwinEdgeCoordinateToLocalCoordinate(const FTopologicalEdge& TwinEdge, const double InTwinCoordinate) const;`
- L767 _public prototype_ `void TransformTwinEdgeCoordinatesToLocalCoordinates(const FTopologicalEdge& TwinEdge, const TArray<double>& InActiveEdgeCoordinate, TArray<double>& OutLocalCoordinate) const;`
- L768 _public prototype_ `void TransformActiveEdgeCoordinatesToLocalCoordinates(const TArray<double>& InActiveEdgeCoordinate, TArray<double>& OutLocalCoordinate) const;`
- L769 _public prototype_ `void TransformLocalCoordinatesToActiveEdgeCoordinates(const TArray<double>& InLocalCoordinate, TArray<double>& OutActiveEdgeCoordinate) const;`
- L774 _public prototype_ `void ComputeEdge2DProperties(FEdge2DProperties& SlopeCharacteristics);` — Compute the edge 2D properties i.e. the mean and standard deviation of the slop of the edge in the parametric space of the carrier surface
- L776 _public function_ `void GetExtremities(FSurfacicCurveExtremities& Extremities) const`
- L781 _public prototype_ `void Offset2D(const FVector2d& OffsetDirection);`
- L792 _public prototype_ `FTopologicalVertex* SplitAt(double SplittingCoordinate, const FVector& NewVertexCoordinate, bool bKeepStartVertexConnectivity, TSharedPtr<FTopologicalEdge>& OutNewEdge);` — Split the edge at input coordinate. The initial edge will be used for the first edge, the second edge will be return. @param SplittingCoordinate @param NewVertexCoordinate @param bKeepStartVertexConnectivity: if true the new edge is connected to endVertex, otherwise the new edge is connected to start vertex @param OutNewEdge, the second edge
- L798 _public prototype_ `bool ExtendTo(bool bStartExtremity, const FVector2d& NewExtremityCoordinate, TSharedRef<FTopologicalVertex>& NewVertex);` — Extend the Edge to the NewVertex. NewVertex become the new extremity of the edge. The old vertex is unconnected of the edge.
- L800 _public prototype_ `bool IsSharpEdge() const;`
- L803 _public prototype_ `bool HasSameLengthAs(const FTopologicalEdge& Edge, double EdgeLengthTolerance) const;` — @return true if they have the same length +/- 5 % or +/- EdgeLengthTolerance
- L811 _public function_ `virtual bool IsDegenerated() const override` — Important note: A Degenerated Edge is used to close 2D boundary in case of degenerated surface to ensureCADKernel a closed boundary Specific process is done for the mesh of this kind of surface
- L829 _public function_ `bool IsThinPeak() const` — An edge is a thin peak means that this edge is a small edge at the extremity of a peak thin zone So this edge must not be meshed (except at its extremities) ThinSide 0 / /  <- Thin peak edge / ThinSide 1
- L834 _public function_ `virtual void SetThinPeakMarker() const`
- L839 _public function_ `virtual void ResetThinPeakMarker() const`
- L844 _public function_ `bool IsVirtuallyMeshed() const`
- L849 _public function_ `virtual void SetVirtuallyMeshedMarker() const`
- L854 _public function_ `virtual void ResetVirtuallyMeshedMarker() const`
- L862 _public function_ `bool IsBorder() const` — @return true if the edge is adjacent to only one surface (its carrier surface)
- L870 _public function_ `bool IsSurfacic() const` — @return true if the edge is adjacent to only two surfaces
- L875 _public prototype_ `bool IsConnectedTo(const FTopologicalFace* Face) const;`
- L877 _public prototype_ `TArray<FTopologicalFace*> GetLinkedFaces() const;`
- L885 _public prototype_ `static TSharedPtr<FTopologicalEdge> CreateEdgeByMergingEdges(const double SmallEdgeTolerance, TArray<FOrientedEdge>& Edges, const TSharedRef<FTopologicalVertex>& StartVertex, const TSharedRef<FTopologicalVertex>& EndVertex);` — Merge successive edges of a face in a single edge. Edges must not be topological linked to other faces i.e. edges must be border edges The merged edges are deleted @return TSharedPtr<FTopologicalEdge>() if failed

#### struct `UE::CADKernel::FEdge2DProperties`  
`struct FEdge2DProperties`  
_L888-958_
- L890 _public member_ `double StandardDeviation = 0;`
- L891 _public member_ `double MediumSlope = 0;`
- L892 _public member_ `double Length3D = 0;`
- L893 _public member_ `EIso IsoType = EIso::UndefinedIso;`
- L894 _public member_ `bool bIsMesh = false;`
- L895 _public member_ `double MeshedLength = 0;`
- L897 _public function_ `void Add(double InSlope, double InLength)`
- L907 _public function_ `void Add2(FEdge2DProperties& Property)` — Finalize has been done on each Property
- L920 _public function_ `void Add(FEdge2DProperties& Property)` — Finalize has not been done on each Property
- L927 _public function_ `void Finalize()`

#### struct `UE::CADKernel::FCuttingPoint`  
`struct FCuttingPoint`  
_L963-1004_
- desc: Cutting point used for meshing purpose
- L968 _public member_ `double Coordinate;` — coordinate of the edge's mesh nodes
- L969 _public member_ `ECoordinateType Type;`
- L970 _public member_ `FPairOfIndex OppositNodeIndices;`
- L971 _public member_ `double IsoDeltaU = 0;`
- L973 _public function_ `FCuttingPoint() : Coordinate(0) , Type(ECoordinateType::OtherCoordinate) , OppositNodeIndices(FPairOfIndex::Undefined) , IsoDeltaU(HUGE_VAL)`
- L981 _public function_ `FCuttingPoint(double InCoordinate, ECoordinateType InType) : Coordinate(InCoordinate) , Type(InType) , OppositNodeIndices(FPairOfIndex::Undefined) , IsoDeltaU(HUGE_VAL)`
- L989 _public function_ `FCuttingPoint(double InCoordinate, ECoordinateType InType, FPairOfIndex InOppositNodeIndices, double DeltaU) : Coordinate(InCoordinate) , Type(InType) , OppositNodeIndices(InOppositNodeIndices) , IsoDeltaU(DeltaU)`
- L997 _public function_ `FCuttingPoint(double InCoordinate, ECoordinateType InType, int32 InOppositeNodeId, double DeltaU) : Coordinate(InCoordinate) , Type(InType) , OppositNodeIndices(InOppositeNodeId) , IsoDeltaU(DeltaU)`

#### struct `UE::CADKernel::FCuttingGrid`  
`struct FCuttingGrid`  
_L1006-1021_
- L1008 _public member_ `TArray<FCuttingPoint> Coordinates[2];`
- L1010 _public function_ `constexpr TArray<FCuttingPoint>& operator[](EIso Iso)`
- L1016 _public function_ `constexpr const TArray<FCuttingPoint>& operator[](EIso Iso) const`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CADKernel` (scope `UE`)
- L17 _typedef_ `typedef TTopologicalLink<FTopologicalEdge> FEdgeLink;` (scope `UE::CADKernel`)
- L48 _prototype_ `template<typename FCuttingPointType> void GetCuttingPointCoordinates(const TArray<FCuttingPointType>& CuttingPoints, TArray<double>& CuttingPointCoordinates);` (scope `UE::CADKernel`)
- L50 _typedef_ `using FAddCuttingPointFunc = TFunction<void(const double, const ECoordinateType, const FPairOfIndex, const double)>;` (scope `UE::CADKernel`)
- L1025 _function_ `template<typename FCuttingPointType> void GetCuttingPointCoordinates(const TArray<FCuttingPointType>& CuttingPoints, TArray<double>& CuttingPointCoordinates)` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/TopologicalEntity.h` (Public)


#### class `UE::CADKernel::FTopologicalEntity`  
`class FTopologicalEntity : public FEntity`  
_L15-96_
- inherits: `FEntity`
- L20 _protected member_ `FIdent CtKioId = 0;`
- L24 _public function_ `FIdent GetKioId() const`
- L29 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L36 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L39 _public function_ `const bool IsApplyCriteria() const`
- L44 _public function_ `virtual void SetApplyCriteriaMarker() const`
- L49 _public function_ `virtual void ResetApplyCriteria()`
- L54 _public function_ `bool IsNotMeshable() const`
- L60 _public function_ `bool IsMeshable() const`
- L70 _public function_ `bool IsPreMeshed() const` — An edge is premesh if the cutting points of the mesh have been defined but the mesh is not build This is used during thin zone meshing i.e. due to the process, an edge can be premeshed but not finalized
- L76 _public function_ `bool IsMeshed() const`
- L81 _public function_ `virtual void SetPreMeshedMarker()`
- L86 _public function_ `virtual void SetMeshedMarker()`
- L92 _public function_ `virtual void ResetPreMeshed()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/TopologicalFace.h` (Public)


#### enum `UE::CADKernel::EStatut`  
`enum class EStatut : uint8`  
_L35-40_
- L37 _public enumerator_ `Interior = 0`
- L38 _public enumerator_ `Exterior`
- L39 _public enumerator_ `Border`

#### enum `UE::CADKernel::EQuadType`  
`enum class EQuadType : uint8`  
_L42-48_
- L44 _public enumerator_ `Unset = 0`
- L45 _public enumerator_ `Quadrangular`
- L46 _public enumerator_ `Triangular`
- L47 _public enumerator_ `Other`

#### class `UE::CADKernel::FTopologicalFace`  
`class FTopologicalFace : public FTopologicalShapeEntity`  
_L52-663_
- inherits: `FTopologicalShapeEntity`
- L58 _protected member_ `TSharedPtr<FSurface> CarrierSurface;`
- L59 _protected member_ `TArray<TSharedPtr<FTopologicalLoop>> Loops;`
- L61 _protected member_ `mutable TCache<FSurfacicBoundary> Boundary;`
- L63 _protected member_ `TSharedPtr<FFaceMesh> Mesh;`
- L68 _protected member_ `FCoordinateGrid MeshCuttingCoordinates;` — Final U&V coordinates of the surface's mesh grid
- L73 _protected member_ `FCoordinateGrid CrossingCoordinates;` — Temporary discretization of the surface used to compute the mesh of the edge
- L78 _protected member_ `FCoordinateGrid CrossingPointDeltaMins;` — Min delta U at the crossing u coordinate to respect meshing criteria
- L83 _protected member_ `FCoordinateGrid CrossingPointDeltaMaxs;` — Max delta U at the crossing u coordinate to respect meshing criteria
- L85 _protected member_ `double EstimatedMinimalElementLength = DOUBLE_BIG_NUMBER;`
- L91 _protected function_ `FTopologicalFace(const TSharedPtr<FSurface>& InCarrierSurface) : FTopologicalShapeEntity() , CarrierSurface(InCarrierSurface) , Mesh(TSharedPtr<FFaceMesh>())` — Build a non-trimmed trimmed surface This constructor has to be completed with one of the three "AddBoundaries" methods to be finalized.
- L99 _protected prototype_ `FTopologicalFace() = default;`
- L104 _protected prototype_ `void ComputeBoundary() const;` — Compute the bounds of the topological surface according to the Loops
- L108 _public function_ `virtual ~FTopologicalFace() override`
- L113 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L120 _public prototype_ `virtual void SpawnIdent(FDatabase& Database) override;`
- L122 _public function_ `virtual void ResetMarkersRecursively() const override`
- L130 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L133 _public function_ `virtual EEntity GetEntityType() const override`
- L138 _public function_ `const FSurfacicTolerance& GetIsoTolerances() const`
- L143 _public function_ `double GetIsoTolerance(EIso Iso) const`
- L148 _public function_ `const FSurfacicBoundary& GetBoundary() const`
- L157 _public function_ `virtual int32 FaceCount() const override`
- L162 _public function_ `virtual void GetFaces(TArray<FTopologicalFace*>& OutFaces) override`
- L171 _public function_ `virtual void CompleteMetaData() override`
- L176 _public function_ `virtual void PropagateBodyOrientation() override`
- L182 _public prototype_ `void RemoveLoop(const TSharedPtr<FTopologicalLoop>& Loop);`
- L183 _public function_ `void AddLoop(const TSharedPtr<FTopologicalLoop>& Loop)`
- L195 _public prototype_ `void AddLoops(const TArray<TSharedPtr<FTopologicalLoop>>& Loops, int32& DoubtfulLoopOrientationCount);` — Trimmed the face with an outer boundary (first boundary of the array) and inners boundaries
- L200 _public prototype_ `void AddLoops(const TArray<TSharedPtr<FCurve>>& Restrictions);` — Trimmed the face with curves i.e. Edges will be build from the cures to make boundaries.
- L206 _public prototype_ `void ApplyNaturalLoops();` — Trimmed the face with its natural limit curves (Iso UMin,  ...). This function is called to trim untrimmed topological face. This function should not be called if the topological face already has a loop.
- L212 _public prototype_ `void ApplyNaturalLoops(const FSurfacicBoundary& Boundaries);` — Trimmed the face with the boundary limit curves (Iso UMin,  ...). This function is called to trim untrimmed topological face. This function should not be called if the topological face already has a loop.
- L214 _public function_ `int32 LoopCount() const`
- L219 _public function_ `const TArray<TSharedPtr<FTopologicalLoop>>& GetLoops() const`
- L224 _public prototype_ `const TSharedPtr<FTopologicalLoop> GetExternalLoop() const;`
- L230 _public prototype_ `const void Get2DLoopSampling(TArray<TArray<FVector2d>>& OutLoopSamplings) const;` — Get a sampling of each loop of the face @param OutLoopSamplings an array of 2d points
- L237 _public prototype_ `const FTopologicalEdge* GetLinkedEdge(const FTopologicalEdge& LinkedEdge) const;` — @return the twin edge of linked edge belonging this topological face
- L245 _public prototype_ `void GetEdgeIndex(const FTopologicalEdge& Edge, int32& OutBoundaryIndex, int32& OutEdgeIndex) const;` — Finds the boundary containing the twin edge of Edge @param Edge @param OutBoundaryIndex: the index of the boundary containing the twin edge @param OutEdgeIndex: the index in the boundary of the twin edge
- L250 _public function_ `void EdgeCount(int32& EdgeCount) const` — Count the edges.
- L262 _public function_ `void GetActiveEdges(TArray<TSharedPtr<FTopologicalEdge>>& OutEdges) const` — Add active Edge that has not marker 1 in the edge array. Marker 1 has to be reset at the end.
- L270 _public function_ `int32 EdgeCount() const`
- L282 _public function_ `TSharedRef<FSurface> GetCarrierSurface() const`
- L289 _public function_ `void EvaluatePointGrid(const FCoordinateGrid& Coordinates, FSurfacicSampling& OutPoints, bool bComputeNormals = false) const`
- L294 _public prototype_ `void EvaluateGrid(FGrid& Grid) const;`
- L300 _public prototype_ `void UpdateBBox(int32 IsoCount, const double ApproximationFactor, FBBoxWithNormal& BBox);` — Update the bounding box with an approximation of the surface based of n iso curves @param ApproximationFactor: the factor apply to the geometric tolerance to defined the SAG error of the ISO
- L307 _public function_ `void Remove(TArray<FTopologicalEdge*>* NewBorderEdges = nullptr)` — Delete a face i.e. disjoin the face to all its linked elements before setting it as deleted
- L313 _public function_ `virtual void Empty() override`
- L343 _public prototype_ `bool IsANonManifoldFace() const;` — Has at least one non manifold edge
- L346 _public prototype_ `bool IsABorderFace() const;` — Has at least one border edge
- L349 _public prototype_ `bool IsAFullyNonManifoldFace() const;` — All its edges are non manifold
- L352 _public prototype_ `bool IsADuplicatedFace() const;` — one adjacent face shares the same loops
- L357 _public prototype_ `bool HasSameBoundariesAs(const FTopologicalFace* OtherFace) const;` — Checks if the face and the other face have the same boundaries i.e. each non degenerated edge is linked to an edge of the other face
- L363 _public prototype_ `void Disjoin(TArray<FTopologicalEdge*>* NewBorderEdges = nullptr);` — Disconnects the face of its neighbors i.e. remove topological edge and vertex link with its neighbors @param OutNewBorderEdges the neighbors edges
- L369 _public prototype_ `void DeleteNonmanifoldLink();` — Delete only nonmanifold edge link
- L373 _public prototype_ `virtual void FillTopologyReport(FTopologyReport& Report) const override;`
- L378 _public prototype_ `FFaceMesh& GetOrCreateMesh(FModelMesh& ModelMesh);`
- L380 _public function_ `const bool HasTesselation() const`
- L385 _public function_ `FFaceMesh* GetMesh() const`
- L394 _public prototype_ `void InitDeltaUs();`
- L396 _public function_ `const TArray<double>& GetCuttingCoordinatesAlongIso(EIso Iso) const`
- L401 _public function_ `TArray<double>& GetCuttingCoordinatesAlongIso(EIso Iso)`
- L406 _public function_ `const FCoordinateGrid& GetCuttingPointCoordinates() const`
- L411 _public function_ `FCoordinateGrid& GetCuttingPointCoordinates()`
- L416 _public function_ `const FCoordinateGrid& GetCrossingPointCoordinates() const`
- L421 _public function_ `const TArray<double>& GetCrossingPointCoordinates(EIso Iso) const`
- L426 _public function_ `TArray<double>& GetCrossingPointCoordinates(EIso Iso)`
- L436 _public prototype_ `bool ComputeCriteriaGridSampling();` — Generate a pre-sampling of the surface saved in CrossingCoordinate. This sampling is light enough to allow a fast computation of the grid, precise enough to compute accurately meshing criteria @return false if the face is considered as degenerate and so removed
- L441 _public prototype_ `void ApplyCriteria(const TArray<TSharedPtr<FCriterion>>& Criteria, const FCriteriaGrid& Grid);` — Compute CrossingPointDeltaMins and CrossingPointDeltaMaxs respecting the meshing criteria
- L443 _public function_ `const TArray<double>& GetCrossingPointDeltaMins(EIso Iso) const`
- L448 _public function_ `const TArray<double>& GetCrossingPointDeltaMaxs(EIso Iso) const`
- L455 _public function_ `const EQuadType GetQuadType() const`
- L460 _public function_ `const bool HasThinZone() const`
- L465 _public function_ `void SetHasThinZoneMarker()`
- L470 _public function_ `void ResetHasThinSurface()`
- L475 _public function_ `bool IsBackOriented() const`
- L480 _public function_ `void SwapOrientation() const`
- L492 _public function_ `void SetBackOriented() const`
- L497 _public function_ `void ResetBackOriented() const`
- L502 _public function_ `virtual void Remove(const FTopologicalShapeEntity*) override`
- L510 _private member_ `TArray<FThinZone2D> ThinZones;`
- L513 _public function_ `void MoveThinZones(TArray<FThinZone2D>& InThinZones)`
- L518 _public function_ `const TArray<FThinZone2D>& GetThinZones() const`
- L523 _public function_ `TArray<FThinZone2D>& GetThinZones()`
- L532 _private member_ `TArray<TSharedPtr<FTopologicalVertex>> SurfaceCorners;`
- L533 _private member_ `TArray<int32> StartSideIndices;`
- L534 _private member_ `TArray<FEdge2DProperties> SideProperties;`
- L535 _private member_ `int32 NumOfMeshedSide = 0;`
- L536 _private member_ `double LoopLength = -1.;`
- L537 _private member_ `double LengthOfMeshedSide = 0;`
- L538 _private member_ `double QuadCriteria = 0;`
- L539 _private member_ `FSurfaceCurvature Curvatures;`
- L540 _private member_ `EQuadType QuadType = EQuadType::Unset;`
- L543 _public prototype_ `void ComputeQuadCriteria();`
- L544 _public prototype_ `double GetQuadCriteria();`
- L546 _public function_ `const FSurfaceCurvature& GetCurvatures() const`
- L551 _public function_ `FSurfaceCurvature& GetCurvatures()`
- L556 _public function_ `const FIsoCurvature& GetCurvature(EIso Iso) const`
- L561 _public prototype_ `void ComputeSurfaceSideProperties();`
- L566 _public prototype_ `void DefineSurfaceType();` — Defines if the surface is either EQuadType::QUAD, either EQuadType::TRIANGULAR or EQuadType::OTHER
- L568 _public function_ `const TArray<FEdge2DProperties>& GetSideProperties() const`
- L573 _public function_ `FEdge2DProperties& GetSideProperty(int32 Index)`
- L578 _public function_ `const FEdge2DProperties& GetSideProperty(int32 Index) const`
- L583 _public function_ `int32& MeshedSideNum()`
- L588 _public function_ `const int32& MeshedSideNum() const`
- L593 _public function_ `void AddMeshedLength(double Length)`
- L598 _public function_ `double MeshedSideRatio() const`
- L603 _public function_ `int32 GetStartEdgeIndexOfSide(int32 Index) const`
- L608 _public function_ `const TArray<int32>& GetStartSideIndices() const`
- L613 _public function_ `int32 GetSideIndex(FTopologicalEdge& Edge) const`
- L623 _public function_ `int32 GetSideIndex(int32 EdgeIndex) const`
- L647 _public function_ `void SetEstimatedMinimalElementLength(double Value)`
- L658 _public function_ `double GetEstimatedMinimalElementLength() const` — @return the minimal size of the mesh elements according to meshing criteria

#### struct `UE::CADKernel::FFaceSubset`  
`struct FFaceSubset`  
_L665-681_
- L667 _public member_ `TArray<FTopologicalFace*> Faces;`
- L668 _public member_ `int32 BorderEdgeCount = 0;`
- L669 _public member_ `int32 NonManifoldEdgeCount = 0;`
- L670 _public member_ `FTopologicalShapeEntity* MainShell;`
- L671 _public member_ `FTopologicalShapeEntity* MainBody;`
- L672 _public member_ `FString MainName;`
- L673 _public member_ `uint32 MainColor;`
- L674 _public member_ `uint32 MainMaterial;`
- L676 _public prototype_ `void SetMainShell(TMap<FTopologicalShapeEntity*, int32>& ShellToFaceCount);`
- L677 _public prototype_ `void SetMainBody(TMap<FTopologicalShapeEntity*, int32>& BodyToFaceCount);`
- L678 _public prototype_ `void SetMainName(TMap<FString, int32>& NameToFaceCount);`
- L679 _public prototype_ `void SetMainColor(TMap<uint32, int32>& ColorToFaceCount);`
- L680 _public prototype_ `void SetMainMaterial(TMap<uint32, int32>& MaterialToFaceCount);`

#### struct `UE::CADKernel::FBBoxWithNormal`  
`struct FBBoxWithNormal`  
_L683-822_
- L685 _public member_ `FVector Max;`
- L686 _public member_ `FVector Min;`
- L687 _public member_ `FVector MaxPoints[3];`
- L688 _public member_ `FVector MinPoints[3];`
- L689 _public member_ `FVector2d MaxCoordinates[3];`
- L690 _public member_ `FVector2d MinCoordinates[3];`
- L691 _public member_ `FVector MaxPointNormals[3];`
- L692 _public member_ `FVector MinPointNormals[3];`
- L693 _public member_ `bool MaxNormalNeedUpdate[3] = {true, true, true};`
- L694 _public member_ `bool MinNormalNeedUpdate[3] = {true, true, true};`
- L696 _public function_ `FBBoxWithNormal() : Max(-HUGE_VALUE, -HUGE_VALUE, -HUGE_VALUE) , Min(HUGE_VALUE, HUGE_VALUE, HUGE_VALUE)`
- L705 _public function_ `double Length()` — BBox Length is the sum of the length of the 3 sides
- L716 _public function_ `bool CheckOrientation(bool bHasWrongOrientation)` — Return false if the process failed
- L750 _public function_ `void Update(const FPolylineBBox& PolylineBBox, const EIso IsoType, double IsoCoordinate)`
- L772 _public function_ `void Update(const FVector& Point, const FVector2d InPoint2D)`
- L794 _public function_ `void UpdateNormal(const FTopologicalFace& Face)`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/TopologicalFaceUtilities.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)
- L13 _namespace_ `namespace TopologicalFaceUtilities` (scope `UE::CADKernel`)
- L15 _prototype_ `bool IsPlanar(const UE::CADKernel::FTopologicalFace& Face);` (scope `UE::CADKernel::TopologicalFaceUtilities`)
- L16 _prototype_ `TArray<FVector2d> Get2DPolyline(const UE::CADKernel::FTopologicalEdge& Edge);` (scope `UE::CADKernel::TopologicalFaceUtilities`)
- L17 _prototype_ `TArray<FVector2d> Get2DPolyline(const UE::CADKernel::FOrientedEdge& Edge);` (scope `UE::CADKernel::TopologicalFaceUtilities`)
- L18 _prototype_ `TArray<FVector2d> Get2DPolyline(const UE::CADKernel::FTopologicalLoop& Loop);` (scope `UE::CADKernel::TopologicalFaceUtilities`)
- L19 _prototype_ `TArray<FVector> Get3DPolyline(const UE::CADKernel::FTopologicalEdge& Edge);` (scope `UE::CADKernel::TopologicalFaceUtilities`)
- L20 _prototype_ `TArray<FVector> Get3DPolyline(const UE::CADKernel::FOrientedEdge& Edge);` (scope `UE::CADKernel::TopologicalFaceUtilities`)
- L21 _prototype_ `TArray<FVector> Get3DPolyline(const UE::CADKernel::FTopologicalLoop& Loop);` (scope `UE::CADKernel::TopologicalFaceUtilities`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/TopologicalLink.h` (Public)


#### class `UE::CADKernel::TTopologicalLink`  
`template<typename EntityType> class TTopologicalLink : public FTopologicalEntity`  
_L16-202_
- inherits: `FTopologicalEntity`
- L22 _protected member_ `EntityType* ActiveEntity;`
- L24 _protected member_ `TArray<EntityType*> TwinEntities;`
- L26 _protected function_ `TTopologicalLink() : ActiveEntity(nullptr)`
- L31 _protected function_ `TTopologicalLink(EntityType& Entity) : ActiveEntity(&Entity)`
- L39 _public function_ `virtual ~TTopologicalLink() override`
- L44 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L58 _public function_ `virtual void Empty() override`
- L64 _public function_ `const EntityType* GetActiveEntity() const`
- L70 _public function_ `EntityType* GetActiveEntity()`
- L76 _public function_ `int32 GetTwinEntityNum() const`
- L81 _public function_ `const TArray<EntityType*>& GetTwinEntities() const`
- L86 _public function_ `void ActivateEntity(const EntityType& NewActiveEntity)`
- L104 _public function_ `void RemoveEntity(TSharedPtr<EntityType>& Entity)`
- L110 _public function_ `void RemoveEntity(EntityType& Entity)`
- L135 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity& Info) const override;`
- L138 _public function_ `virtual EEntity GetEntityType() const override`
- L143 _public function_ `void AddEntity(EntityType* Entity)`
- L148 _public function_ `void AddEntity(EntityType& Entity)`
- L154 _public function_ `template <typename LinkableType> void AddEntity(const LinkableType* Entity)`
- L160 _public function_ `template <typename ArrayType> void AddEntities(const ArrayType& Entities)`
- L168 _public function_ `virtual bool CleanLink()` — @return true if the Twin entity count link is modified
- L192 _public function_ `void ResetMarkersRecursively() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)
- L88 _function_ `TFunction<bool()> CheckEntityIsATwin = [&]()` (scope `UE::CADKernel::TTopologicalLink::ActivateEntity`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/TopologicalLoop.h` (Public)


#### class `UE::CADKernel::FOrientedEdge`  
`class FOrientedEdge : public TOrientedEntity<FTopologicalEdge>`  
_L20-57_
- inherits: `TOrientedEntity<FTopologicalEdge>`
- L23 _public function_ `FOrientedEdge(TSharedPtr<FTopologicalEdge>& InEntity, EOrientation InDirection) : TOrientedEntity(InEntity, InDirection)`
- L28 _public function_ `FOrientedEdge() : TOrientedEntity()`
- L33 _public function_ `bool operator==(const FOrientedEdge& Edge) const`
- L38 _public function_ `TSharedRef<FTopologicalVertex> GetStartVertex()`
- L43 _public function_ `TSharedRef<FTopologicalVertex> GetEndVertex()`
- L48 _public function_ `double GetStartCoordinate()`
- L53 _public function_ `double GetEndCoordinate()`

#### class `UE::CADKernel::FTopologicalLoop`  
`class FTopologicalLoop : public FTopologicalEntity`  
_L59-279_
- inherits: `FTopologicalEntity`
- L67 _public member_ `FSurfacicBoundary Boundary;`
- L70 _protected member_ `TArray<FOrientedEdge> Edges;`
- L72 _protected member_ `FTopologicalFace* Face;`
- L73 _protected member_ `bool bIsExternal;`
- L75 _protected prototype_ `FTopologicalLoop(const TArray<TSharedPtr<FTopologicalEdge>>& Edges, const TArray<EOrientation>& EdgeDirections, const bool bIsEternalLoop);`
- L77 _protected prototype_ `FTopologicalLoop() = default;`
- L81 _private function_ `void SetSurface(FTopologicalFace* HostedFace)`
- L86 _private function_ `void ResetSurface()`
- L93 _public function_ `virtual ~FTopologicalLoop() override`
- L98 _public function_ `virtual void Empty() override`
- L108 _public prototype_ `static TSharedPtr<FTopologicalLoop> Make(const TArray<TSharedPtr<FTopologicalEdge>>& EdgeList, const TArray<EOrientation>& EdgeDirections, const bool bIsExternalLoop, const double GeometricTolerance);`
- L110 _public prototype_ `void DeleteLoopEdges();`
- L112 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L120 _public function_ `virtual void SpawnIdent(FDatabase& Database) override`
- L130 _public function_ `virtual void ResetMarkersRecursively() const override`
- L137 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L140 _public function_ `virtual EEntity GetEntityType() const override`
- L145 _public prototype_ `double Length() const;`
- L147 _public function_ `const int32 EdgeCount() const`
- L152 _public function_ `const TArray<FOrientedEdge>& GetEdges() const`
- L157 _public function_ `TArray<FOrientedEdge>& GetEdges()`
- L162 _public function_ `const FOrientedEdge* GetOrientedEdge(const FTopologicalEdge* InEdge) const`
- L178 _public function_ `void GetActiveEdges(TArray<TSharedPtr<FTopologicalEdge>>& OutEdges) const` — Add active Edge that has not marker 1 in the edge array. Marker 1 has to be reset at the end.
- L191 _public function_ `FTopologicalFace* GetFace() const`
- L196 _public function_ `bool IsExternal() const`
- L201 _public function_ `void SetExternal()`
- L206 _public function_ `void SetInternal()`
- L214 _public prototype_ `bool Orient();` — @return false if the orientation is doubtful
- L215 _public prototype_ `void SwapOrientation();`
- L217 _public prototype_ `void ReplaceEdge(TSharedPtr<FTopologicalEdge>& OldEdge, TSharedPtr<FTopologicalEdge>& NewEdge);`
- L218 _public prototype_ `void ReplaceEdge(TSharedPtr<FTopologicalEdge>& Edge, TArray<TSharedPtr<FTopologicalEdge>>& NewEdges);`
- L219 _public prototype_ `void ReplaceEdges(TArray<FOrientedEdge>& Candidates, TSharedPtr<FTopologicalEdge>& NewEdge);`
- L226 _public prototype_ `void SplitEdge(FTopologicalEdge& Edge, TSharedPtr<FTopologicalEdge> NewEdge, bool bNewEdgeIsFirst);` — The Edge is split in two edges : Edge + NewEdge @param bNewEdgeIsFirst == true => StartVertex Connected to Edge, EndVertexConnected to NewEdge According to the direction of Edge, if bNewEdgeIsFirst == true, NewEdge is added in the loop after (EOrientation::Front) or before (EOrientation::Back)
- L228 _public prototype_ `void RemoveEdge(TSharedPtr<FTopologicalEdge>& Edge);`
- L231 _public prototype_ `EOrientation GetDirection(TSharedPtr<FTopologicalEdge>& Edge, bool bAllowLinkedEdge = false) const;`
- L233 _public function_ `EOrientation GetDirection(int32 Index) const`
- L238 _public function_ `const TSharedPtr<FTopologicalEdge>& GetEdge(int32 Index) const`
- L243 _public function_ `int32 GetEdgeIndex(const FTopologicalEdge& Edge) const`
- L255 _public prototype_ `void Get2DSampling(TArray<FVector2d>& LoopSampling) const;`
- L264 _public prototype_ `bool Get2DSamplingWithoutDegeneratedEdges(TArray<FVector2d>& LoopSampling) const;` — The idea is to remove degenerated edges of the loop i.e. where the surface is degenerated - so where projections on these area are hazardous - so where 2d curve computation based on hazardous projection is hazardous... - so where the sampling could be in self-intersecting @return false if the loop is degenerated
- L266 _public prototype_ `void FindSurfaceCorners(TArray<TSharedPtr<FTopologicalVertex>>& OutCorners, TArray<int32>& OutStartSideIndex) const;`
- L267 _public prototype_ `void FindBreaks(TArray<TSharedPtr<FTopologicalVertex>>& Ruptures, TArray<int32>& OutStartSideIndex, TArray<double>& RuptureValues) const;`
- L269 _public prototype_ `void ComputeBoundaryProperties(const TArray<int32>& StartSideIndex, TArray<FEdge2DProperties>& OutSideProperties) const;`
- L271 _public prototype_ `void EnsureLogicalClosing(const double GeometricTolerance);`
- L273 _public prototype_ `void CheckEdgesOrientation();`
- L274 _public prototype_ `void CheckLoopWithTwoEdgesOrientation();`
- L275 _public prototype_ `void RemoveDegeneratedEdges();`
- L277 _public prototype_ `bool IsInside(const FTopologicalLoop& Other) const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/TopologicalShapeEntity.h` (Public)


#### class `UE::CADKernel::FTopologicalShapeEntity`  
`class FTopologicalShapeEntity : public FTopologicalEntity`  
_L13-180_
- inherits: `FTopologicalEntity`
- L20 _private member_ `FTopologicalShapeEntity* HostedBy = nullptr;`
- L21 _private member_ `FMetadataDictionary Dictionary;`
- L25 _public function_ `virtual ~FTopologicalShapeEntity() override`
- L30 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L37 _public function_ `virtual void Empty() override`
- L43 _public function_ `const FMetadataDictionary& GetMetaDataDictionary() const`
- L48 _public function_ `void ExtractMetaData(TMap<FString, FString>& OutMetaData) const`
- L53 _public prototype_ `virtual void CompleteMetaData() = 0;`
- L54 _public prototype_ `void CompleteMetaDataWithHostMetaData();`
- L56 _public prototype_ `virtual int32 FaceCount() const = 0;`
- L57 _public prototype_ `virtual void GetFaces(TArray<FTopologicalFace*>& OutFaces) = 0;`
- L63 _public prototype_ `virtual void PropagateBodyOrientation() = 0;` — Each face of model is set by its orientation. This allow to make oriented mesh and to keep the face orientation in topological function. Marker2 of propagate face is set. It must be reset after the process
- L66 _public prototype_ `virtual void FillTopologyReport(FTopologyReport& Report) const = 0;`
- L69 _public function_ `FTopologicalShapeEntity* GetHost()`
- L74 _public function_ `const FTopologicalShapeEntity* GetHost() const`
- L79 _public function_ `void SetHost(FTopologicalShapeEntity* Body)`
- L88 _public prototype_ `virtual void Remove(const FTopologicalShapeEntity*) = 0;`
- L90 _public function_ `void SetHostId(const int32 InHostId)`
- L95 _public function_ `int32 GetHostId() const`
- L100 _public function_ `void SetLayer(const int32 InLayerId)`
- L105 _public function_ `void SetName(const FString& InName)`
- L110 _public function_ `bool HasName() const`
- L115 _public function_ `const TCHAR* GetName() const`
- L120 _public function_ `void SetColorId(const uint32& InColorId)`
- L125 _public function_ `uint32 GetColorId() const`
- L130 _public function_ `void SetMaterialId(const uint32& InMaterialId)`
- L135 _public function_ `uint32 GetMaterialId() const`
- L140 _public function_ `void SetDisplayData(const uint32& InColorId, const uint32& InMaterialId)`
- L152 _public function_ `void SetDisplayData(const FTopologicalShapeEntity& DisplayData)`
- L157 _public function_ `void SetPatchId(int32 InPatchId)`
- L162 _public function_ `int32 GetPatchId() const`
- L168 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L175 _protected function_ `void ResetHost()` — Mandatory: The host must have remove this from his array

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/TopologicalVertex.h` (Public)


#### class `UE::CADKernel::FVertexLink`  
`class FVertexLink : public TTopologicalLink<FTopologicalVertex>`  
_L23-80_
- inherits: `TTopologicalLink<FTopologicalVertex>`
- desc: TTopologicalLink overload dedicated to FVertex to manage the barycenter of twin vertices
- L28 _protected member_ `FVector Barycenter;`
- L30 _protected function_ `void SetBarycenter(const FVector& Point)`
- L36 _public function_ `FVertexLink() : Barycenter(FVector::ZeroVector)`
- L41 _public function_ `FVertexLink(FTopologicalVertex& Entity) : TTopologicalLink<FTopologicalVertex>(Entity) , Barycenter(FVector::ZeroVector)`
- L47 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L54 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity& Info) const override;`
- L57 _public function_ `const FVector& GetBarycenter() const`
- L62 _public function_ `virtual bool CleanLink() override`
- L73 _public function_ `virtual EEntity GetEntityType() const override`
- L78 _public prototype_ `void ComputeBarycenter();`
- L79 _public prototype_ `void DefineActiveEntity();`

#### class `UE::CADKernel::FTopologicalVertex`  
`class FTopologicalVertex : public TLinkable<FTopologicalVertex, FVertexLink>`  
_L82-307_
- inherits: `TLinkable<FTopologicalVertex,FVertexLink>`
- L89 _protected member_ `TArray<FTopologicalEdge*> ConnectedEdges;`
- L90 _protected member_ `FVector Coordinates;`
- L91 _protected member_ `TSharedPtr<FVertexMesh> Mesh;`
- L93 _protected function_ `FTopologicalVertex(const FVector& InCoordinates) : Coordinates(InCoordinates)`
- L98 _protected prototype_ `FTopologicalVertex() = default;`
- L102 _public function_ `virtual ~FTopologicalVertex() override`
- L107 _public function_ `static TSharedRef<FTopologicalVertex> Make(const FVector& InCoordinate)`
- L114 _public function_ `virtual void Serialize(FCADKernelArchive& Ar) override`
- L126 _public prototype_ `virtual void SpawnIdent(FDatabase& Database) override;`
- L129 _public prototype_ `virtual FInfoEntity& GetInfo(FInfoEntity&) const override;`
- L132 _public function_ `virtual EEntity GetEntityType() const override`
- L140 _public function_ `inline const FVector& GetBarycenter() const` — @return the 3d coordinate of the barycenter of the twin vertices
- L152 _public function_ `const FVector& GetCoordinates() const` — @return the 3d coordinates of the vertex (prefere GetBarycenter())
- L157 _public function_ `void SetCoordinates(const FVector& NewCoordinates)`
- L175 _public function_ `double Distance(const FTopologicalVertex& OtherVertex) const`
- L180 _public function_ `double SquareDistance(const FTopologicalVertex& OtherVertex) const`
- L185 _public function_ `double SquareDistanceBetweenBarycenters(const FTopologicalVertex& OtherVertex) const`
- L190 _public function_ `double SquareDistance(const FVector& Point) const`
- L195 _public prototype_ `FVertexMesh& GetOrCreateMesh(FModelMesh& MeshModel);`
- L197 _public function_ `const FVertexMesh* GetMesh() const`
- L210 _public prototype_ `void Link(FTopologicalVertex& InEntity);`
- L212 _public prototype_ `void UnlinkTo(FTopologicalVertex& Entity);`
- L214 _public function_ `virtual void RemoveFromLink() override`
- L224 _public function_ `void DeleteIfIsolated()`
- L241 _public function_ `virtual void Empty() override`
- L248 _public prototype_ `bool IsBorderVertex() const;`
- L250 _public prototype_ `void AddConnectedEdge(FTopologicalEdge& Edge);`
- L251 _public prototype_ `void RemoveConnectedEdge(FTopologicalEdge& Edge);`
- L263 _public function_ `const TArray<FTopologicalEdge*>& GetDirectConnectedEdges() const` — Mandatory: to browse all the connected edges, you have to browse the connected edges of all the twin vertices for (TWeakPtr<FTopologicalVertex> TwinVertex : Vertex->GetTwinsEntities()) { for (TWeakPtr<FTopologicalEdge> ConnectedEdge : TwinVertex.Pin()->GetDirectConnectedEdges()) { ... } }
- L268 _public prototype_ `const FTopologicalFace* GetFace() const;`
- L270 _public function_ `void GetConnectedEdges(TArray<FTopologicalEdge*>& OutConnectedEdges) const`
- L286 _public function_ `const int32 ConnectedEdgeCount()`
- L306 _public prototype_ `void GetConnectedEdges(const FTopologicalVertex& OtherVertex, TArray<FTopologicalEdge*>& Edges) const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Topo/Topomaker.h` (Public)


#### enum `UE::CADKernel::ESewOption`  
`enum class ESewOption : uint8`  
_L20-29_
- L22 _public enumerator_ `None = 0x00u` — No flags.
- L24 _public enumerator_ `ForceJoining = 0x01u`
- L25 _public enumerator_ `RemoveThinFaces = 0x02u`
- L26 _public enumerator_ `RemoveDuplicatedFaces = 0x04u`
- L28 _public enumerator_ `All = 0x07u`

#### struct `UE::CADKernel::FTopomakerOptions`  
`struct FTopomakerOptions`  
_L71-82_
- L73 _public member_ `ESewOption SewOptions;`
- L74 _public member_ `double Tolerance;`
- L75 _public member_ `double ForceJoinFactor;`
- L77 _public function_ `FTopomakerOptions(ESewOption InSewOptions, double InTolerance, double InForceJoinFactor) : SewOptions(InSewOptions) , Tolerance(InTolerance) , ForceJoinFactor(InForceJoinFactor)`

#### class `UE::CADKernel::FTopomaker`  
`class FTopomaker`  
_L85-231_
- L90 _protected member_ `FSession& Session;`
- L92 _protected member_ `TArray<FShell*> Shells;`
- L93 _protected member_ `TArray<TSharedPtr<FTopologicalFace>> Faces;`
- L96 _protected member_ `FTopomakerReport Report;`
- L101 _public prototype_ `FTopomaker(FSession& InSession, const FTopomakerOptions& InOptions);`
- L102 _public prototype_ `FTopomaker(FSession& InSession, const TArray<TSharedPtr<FShell>>& Shells, const FTopomakerOptions& InOptions);`
- L103 _public prototype_ `FTopomaker(FSession& InSession, const TArray<TSharedPtr<FTopologicalFace>>& Faces, const FTopomakerOptions& InOptions);`
- L105 _public function_ `void SetTolerance(const FTopomakerOptions Options)`
- L127 _public prototype_ `void Sew();`
- L132 _public prototype_ `void SplitIntoConnectedShells();` — Split into connected shell and put each shell into the appropriate body
- L134 _public prototype_ `void OrientShells();`
- L139 _public prototype_ `void UnlinkNonManifoldVertex();` — Unlink Non-Manifold Vertex i.e. Vertex belong to tow or more shell
- L144 _public prototype_ `void UnlinkFromOther();` — Mandatory: UnlinkNonManifoldVertex has to be call before
- L146 _public prototype_ `void RemoveThinFaces();`
- L152 _public prototype_ `void DeleteNonmanifoldLink();` — Mandatory: UnlinkNonManifoldVertex has to be call after
- L155 _public function_ `void PrintSewReport()`
- L160 _public function_ `void PrintRemoveThinFacesReport()`
- L172 _private prototype_ `void InitFaces();` — Call by constructor. For each shell, add their faces into Faces array, complete the metadata and set the states for the joining process
- L174 _private prototype_ `void EmptyShells();`
- L176 _private prototype_ `void RemoveEmptyShells();`
- L178 _private prototype_ `void RemoveDuplicatedFaces();`
- L183 _private prototype_ `void GetVertices(TArray<FTopologicalVertex*>& Vertices);` — Return an array of active vertices.
- L188 _private prototype_ `void GetBorderVertices(TArray<FTopologicalVertex*>& BorderVertices);` — Return an array of active border vertices.
- L190 _private prototype_ `void CheckSelfConnectedEdge(double MaxLengthOfDegeneratedEdge, TArray<FTopologicalVertex*>& OutBorderVertices);`
- L191 _private prototype_ `void RemoveIsolatedEdges();` — Useful ???
- L193 _private prototype_ `void SetSelfConnectedEdgeDegenerated(TArray<FTopologicalVertex*>& Vertices);`
- L212 _private prototype_ `void MergeUnconnectedSuccessiveEdges();` — For each loop of each surface, check if successive edges are unconnected and if their common vertices are connected only to them (UV vs CV: vertex connected to many faces ). These edges must be tangent together. These edges are merged into one edge. E.g. : Face A has 3 successive unconnected edges. If these 3 edges are merged to give only one edge, the new edge could be linked to its parallel edge of Face B CV: Connected vertex i.e. linked to different faces \                          Face A                                   |    Face C \                                                                  | Face E     CV ------------------ UV -------------------- UV ---------------- CV -------------------- CV -------------------------------------------------------------- CV -------------------- /                         Face B                                   |    Face D /                                                                   |
- L214 _private prototype_ `void SetToProcessMarkerOfFaces();`
- L215 _private prototype_ `void ResetMarkersOfFaces();`
- L219 _private member_ `ESewOption SewOptions;`
- L221 _private member_ `double Tolerance;`
- L222 _private member_ `double ForceJoinFactor;`
- L224 _private member_ `double SewTolerance;`
- L225 _private member_ `double SewToleranceToForceJoin;` — SewTolerance x ForceJoinFactor;
- L227 _private member_ `double EdgeLengthTolerance;` — 2x SewTolerance
- L228 _private member_ `double LargeEdgeLengthTolerance;` — 2x SewToleranceToForceJoin
- L230 _private member_ `double ThinFaceWidth;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CADKernel` (scope `UE`)
- L31 _prototype_ `ENUM_CLASS_FLAGS(ESewOption);` (scope `UE::CADKernel`)
- L33 _namespace_ `namespace SewOption` (scope `UE::CADKernel`)
- L36 _function_ `static ESewOption GetFromOptions(bool bGStitchingForceSew, bool bGStitchingRemoveThinFaces, bool bGStitchingRemoveDuplicatedFaces)` (scope `UE::CADKernel::SewOption`)
- L60 _namespace_ `namespace TopomakerTools` (scope `UE::CADKernel`)
- L67 _prototype_ `void MergeCoincidentVertices(TArray<FTopologicalVertex*>& VerticesToMerge, double Tolerance);` (scope `UE::CADKernel::TopomakerTools`) — Merge Border Vertices with other vertices. @param Vertices: the initial array of active vertices to process, this array is updated at the end of the process

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Utils/Cache.h` (Public)


#### class `UE::CADKernel::TCache`  
`template<class ObjectType> class TCache`  
_L11-92_
- L14 _protected member_ `ObjectType Value;`
- L15 _protected member_ `bool bReady;`
- L18 _public function_ `TCache() : Value() , bReady(false)`
- L25 _public function_ `template<typename... InArgTypes> TCache(InArgTypes&&... Args) : Value(Forward<InArgTypes>(Args)...) , bReady(true)`
- L38 _public function_ `void Set(const ObjectType& NewValue)`
- L45 _public function_ `template<typename... InArgTypes> void Set(InArgTypes&&... Args)`
- L51 _public function_ `void operator=(const ObjectType& NewValue)`
- L57 _public function_ `void operator+=(const ObjectType& NewValue)`
- L63 _public function_ `ObjectType* operator->()`
- L68 _public function_ `operator ObjectType& ()`
- L73 _public function_ `const ObjectType& operator*() const`
- L78 _public function_ `void SetReady()`
- L83 _public function_ `bool IsValid() const`
- L88 _public function_ `void Empty()`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CADKernel` (scope `UE`)
- L31 _function_ `friend FArchive& operator<<(FArchive& Ar, TCache<ObjectType>& Cache)` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Utils/IndexOfCoordinateFinder.h` (Public)


#### class `UE::CADKernel::FIndexOfCoordinateFinder`  
`class FIndexOfCoordinateFinder`  
_L19-30_
- desc: Finder of the index of the segment of the polyline coordinates containing the input coordinate This abstract class return the lower index of the segment i.e. InPolylineCoordinates[OutIndex] <= InCoordinate <= InPolylineCoordinates[OutIndex + 1] As input coordinates are increasing, the algorithme is optimize by restarting form the last coordinate found. Class derived from it allows to optimized polyline functions needing the index of the segment containing the input coordinate (@see ApproximatePoint). @see FLinearFinder to optimize the search when the next points to search is nearest the previous. @see FFinderByDichotomy to optimize the search when there is no simple rule, so a dichotomy algorithm is used. This class is dedicated for a unique or mess up set of input coordinates
- L22 _protected member_ `const TArray<double>& Coordinates;`
- L24 _public function_ `FIndexOfCoordinateFinder(const TArray<double>& InPolylineCoordinates) : Coordinates(InPolylineCoordinates)`
- L29 _public prototype_ `virtual int32 Find(const double InCoordinate) = 0;`

#### class `UE::CADKernel::FLinearFinder`  
`class FLinearFinder : public FIndexOfCoordinateFinder`  
_L32-82_
- inherits: `FIndexOfCoordinateFinder`
- L34 _private member_ `int32& Index;`
- L37 _public function_ `FLinearFinder(const TArray<double>& InPolylineCoordinates, int32& InOutIndex) : FIndexOfCoordinateFinder(InPolylineCoordinates) , Index(InOutIndex)`
- L43 _public function_ `virtual int32 Find(const double InCoordinate) override`

#### class `UE::CADKernel::FDichotomyFinder`  
`class FDichotomyFinder : public FIndexOfCoordinateFinder`  
_L84-145_
- inherits: `FIndexOfCoordinateFinder`
- L88 _public function_ `FDichotomyFinder(const TArray<double>& InPolylineCoordinates) : FIndexOfCoordinateFinder(InPolylineCoordinates) , StartLower(0) , StartUpper(InPolylineCoordinates.Num() - 2)`
- L95 _public function_ `FDichotomyFinder(const TArray<double>& InPolylineCoordinates, int32 InStartLowerBound, int32 InStartUpperBound) : FIndexOfCoordinateFinder(InPolylineCoordinates) , StartLower(InStartLowerBound) , StartUpper(InStartUpperBound)`
- L102 _public member_ `int32 StartLower;`
- L103 _public member_ `int32 StartUpper;`
- L105 _public function_ `virtual int32 Find(const double InCoordinate) override`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Base/Public/Utils/StringUtil.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace CADKernel` (scope `UE`)
- L17 _namespace_ `namespace Utils` (scope `UE::CADKernel`)
- L20 _function_ `inline std::string ToString(const TCHAR* WideString)` (scope `UE::CADKernel::Utils`)
- L26 _function_ `template<typename ValueType> inline std::string ToString(const ValueType& v)` (scope `UE::CADKernel::Utils`)
- L33 _function_ `inline std::string ToString(const FVector& p)` (scope `UE::CADKernel::Utils`)
- L40 _function_ `inline FString ToFString(const char* Text)` (scope `UE::CADKernel::Utils`)
- L45 _function_ `inline FString ToFString(const double& Value)` (scope `UE::CADKernel::Utils`)
- L50 _function_ `inline FString ToFString(const int32& Value)` (scope `UE::CADKernel::Utils`)
- L55 _function_ `inline FString ToFString(const uint32& Value)` (scope `UE::CADKernel::Utils`)
- L60 _function_ `inline FString ToFString(const bool& Value)` (scope `UE::CADKernel::Utils`)
- L65 _function_ `inline FString ToFString(const FVector& p)` (scope `UE::CADKernel::Utils`)
- L70 _prototype_ `void Explode(const FString& FullString, const TCHAR* Separator, TArray<FString>& StringArray);` (scope `UE::CADKernel::Utils`)
- L72 _function_ `inline FString EscapeBackSlashes(const FString& InputString)` (scope `UE::CADKernel::Utils`)
- L86 _function_ `inline void RemoveUnwantedChar(FString& String, const TCHAR UnwantedChar)` (scope `UE::CADKernel::Utils`)
