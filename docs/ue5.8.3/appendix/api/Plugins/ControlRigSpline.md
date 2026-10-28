# Plugins / ControlRigSpline

- module root: `Plugins/Animation/ControlRigSpline/Source/ControlRigSpline`
- headers: 3; symbols: 219
- symbol kinds: class=4, enum=1, enumerator=3, function=23, macro=2, member=113, prototype=50, struct=23
- PublicDependencyModuleNames: ControlRig, Core, CoreUObject, Engine, RigVM

### `Plugins/Animation/ControlRigSpline/Source/ControlRigSpline/Public/ControlRigSplineModule.h` (Public)


#### class `FControlRigSplineModule`  
`class FControlRigSplineModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L11 _private prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Animation/ControlRigSpline/Source/ControlRigSpline/Public/ControlRigSplineTypes.h` (Public)


#### enum `ESplineType`  
`enum class ESplineType : uint8`  
_L14-26_
- reflection: `UENUM()`
- L18 _public enumerator_ `BSpline` — The smooth curve will pass through the first and last control points
- L22 _public enumerator_ `Hermite` — The curve will pass through the control points
- L25 _public enumerator_ `Max UMETA(Hidden)` — MAX - invalid

#### class `ControlRigBaseSpline`  
`class ControlRigBaseSpline`  
_L38-62_
- L42 _protected member_ `TArray<FVector> ControlPoints;`
- L43 _protected member_ `uint16 Degree;`
- L44 _protected member_ `bool bClosed;`
- L48 _public prototype_ `ControlRigBaseSpline(const TArrayView<const FVector>& InControlPoints, uint16 InDegree, bool bInClosed);`
- L49 _public prototype_ `virtual ~ControlRigBaseSpline()= default;`
- L51 _public prototype_ `virtual FVector GetPointAtParam(float Param) = 0;`
- L53 _public prototype_ `virtual void SetControlPoints(const TArrayView<const FVector>& InControlPoints);`
- L55 _public function_ `virtual TArray<FVector>& GetControlPoints()`
- L57 _public prototype_ `virtual TArray<FVector> GetControlPointsWithoutDuplicates();`
- L59 _public prototype_ `virtual TArray<uint16> GetControlIndicesWithoutDuplicates();`
- L61 _public function_ `uint8 GetDegree() const`

#### class `ControlRigBSpline`  
`class ControlRigBSpline : public ControlRigBaseSpline`  
_L64-73_
- inherits: `ControlRigBaseSpline`
- L66 _private member_ `TArray<float> KnotVector;`
- L69 _public prototype_ `ControlRigBSpline(const TArrayView<const FVector>& InControlPoints, const uint16 InDegree, const bool bInClosed, const bool bInClamped);`
- L71 _public prototype_ `virtual FVector GetPointAtParam(float Param);`

#### class `ControlRigHermite`  
`class ControlRigHermite : public ControlRigBaseSpline`  
_L75-88_
- inherits: `ControlRigBaseSpline`
- L77 _private member_ `TArray<FVector> SegmentPoints;`
- L79 _private member_ `uint16 NumSegments;`
- L82 _public prototype_ `ControlRigHermite(const TArrayView<const FVector>& InControlPoints, const bool bInClosed);`
- L84 _public prototype_ `virtual void SetControlPoints(const TArrayView<const FVector>& InControlPoints) override;`
- L86 _public prototype_ `virtual FVector GetPointAtParam(float Param);`

#### struct `FControlRigSplineImpl`  
`struct FControlRigSplineImpl`  
_L92-153_
- reflection: `USTRUCT()`
- L96 _public function_ `FControlRigSplineImpl()`
- L104 _public prototype_ `virtual ~FControlRigSplineImpl();`
- L107 _public member_ `ESplineType SplineMode;` — Spline type
- L110 _public member_ `TArray<FTransform> ControlTransforms;` — The transforms of the control points
- L113 _public member_ `TArray<float> InitialLengths;` — The initial lengths between samples
- L116 _public member_ `ControlRigBaseSpline* Spline;` — The actual spline
- L119 _public member_ `bool bClosed;` — Wether or not the curve is closed
- L122 _public member_ `int32 SamplesPerSegment;` — Samples per segment, where segment is the portion between two control points
- L125 _public member_ `float Compression;` — The allowed length compression (1.f being do not allow compression`). If 0, no restriction wil be applied.
- L128 _public member_ `float Stretch;` — The allowed length stretch (1.f being do not allow stretch`). If 0, no restriction wil be applied.
- L131 _public member_ `TArray<FTransform> SamplesArray;` — Positions along the "real" curve (no samples in the first and last segments of a hermite spline)
- L134 _public member_ `TArray<float> AccumulatedLenth;` — Accumulated length along the spline given by samples
- L137 _public prototype_ `TArray<FVector>& GetControlPoints();` — Returns a reference to the control points that were used to create this spline
- L140 _public prototype_ `TArray<FTransform>& GetControlTransforms();` — Returns a reference to the control transforms that were used to create this spline
- L143 _public prototype_ `TArray<FVector> GetControlPointsWithoutDuplicates();` — Returns the control points that were used to create this spline, removing the duplicates in case of a closed spline
- L146 _public prototype_ `TArray<FTransform> GetControlTransformsWithoutDuplicates();` — Returns the control transforms that were used to create this spline, removing the duplicates in case of a closed spline
- L149 _public prototype_ `uint8 GetDegree() const;` — Returns the degree of the curve
- L152 _public prototype_ `uint16 NumSamples() const;` — Returns the total number of samples cached

#### struct `FControlRigSpline`  
`struct FControlRigSpline`  
_L156-236_
- reflection: `USTRUCT(BlueprintType)`
- L160 _public function_ `FControlRigSpline()`
- L162 _public prototype_ `virtual ~FControlRigSpline() = default;`
- L164 _public prototype_ `FControlRigSpline(const FControlRigSpline& InOther);`
- L165 _public prototype_ `FControlRigSpline& operator =(const FControlRigSpline& InOther);`
- L167 _public member_ `TSharedPtr<FControlRigSplineImpl> SplineData;`
- L174 _public prototype_ `uint8 GetDegree() const;` — Returns the degree of the spline @return			The degree of the spline.
- L188 _public prototype_ `void SetControlPoints(const TArrayView<const FVector>& InPoints, const ESplineType SplineMode = ESplineType::BSpline, const bool bInClosed = false, const int32 SamplesPerSegment = 16, const float Compression = 1.f, const float Stretch = 1.f);` — Sets the control points in the spline. It will build the spline if needed, or will update the points if building from scratch is not necessary. The type of spline to build will depend on what is set in SplineMode. @param InPoints	The control points to set. @param SplineMode	The type of spline @param bInClosed	If the spline should be closed @param SamplesPerSegment The samples to cache for every segment defined between two control rig @param Compression The allowed length compression (1.f being do not allow compression`). If 0, no restriction wil be applied. @param Stretch The allowed length stretch (1.f being do not allow stretch). If 0, no restriction wil be applied.
- L202 _public prototype_ `void SetControlTransforms(const TArrayView<const FTransform>& InTransforms, const ESplineType SplineMode = ESplineType::BSpline, const bool bInClosed = false, const int32 SamplesPerSegment = 16, const float Compression = 1.f, const float Stretch = 1.f);` — Sets the control transforms in the spline. It will build the spline if needed, or will update the transforms if building from scratch is not necessary. The type of spline to build will depend on what is set in SplineMode. @param InTransforms	The control transforms to set. @param SplineMode	The type of spline @param bInClosed	If the spline should be closed @param SamplesPerSegment The samples to cache for every segment defined between two control rig @param Compression The allowed length compression (1.f being do not allow compression`). If 0, no restriction wil be applied. @param Stretch The allowed length stretch (1.f being do not allow stretch). If 0, no restriction wil be applied.
- L210 _public prototype_ `FVector PositionAtParam(const float InParam) const;` — Given an InParam float in [0, 1], will return the position of the spline at that point. @param InParam	The parameter between [0, 1] to query. @return			The position in the spline.
- L218 _public prototype_ `FTransform TransformAtParam(const float InParam) const;` — Given an InParam float in [0, 1], will return the transform of the spline at that point. @param InParam	The parameter between [0, 1] to query. @return			The transform in the spline.
- L227 _public prototype_ `FVector TangentAtParam(const float InParam) const;` — Given an InParam float in [0, 1], will return the tangent vector of the spline at that point. Note that this vector is not normalized. @param InParam	The parameter between [0, 1] to query. @return			The tangent of the spline at InParam.
- L235 _public prototype_ `float LengthAtParam(const float InParam) const;` — Given an InParam float in [0, 1], will return the length of the spline at that point. @param InParam	The parameter between [0, 1] to query. @return			The length of the spline at InParam.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONTROLRIGSPLINE_API`

### `Plugins/Animation/ControlRigSpline/Source/ControlRigSpline/Public/ControlRigSplineUnits.h` (Public)


#### struct `FRigUnit_ControlRigSplineBase`  
`struct FRigUnit_ControlRigSplineBase : public FRigUnit`  
_L16-19_
- reflection: `USTRUCT(meta = (Abstract, Category = "Splines", Varying, NodeColor = "0.737911 0.099899 0.099899", DocumentationPolicy = "Strict"))`
- inherits: `FRigUnit`
- desc: The base class for all control rig spline nodes

#### struct `FRigUnit_ControlRigSplineBaseMutable`  
`struct FRigUnit_ControlRigSplineBaseMutable : public FRigUnitMutable`  
_L25-28_
- reflection: `USTRUCT(meta = (Abstract, Category = "Splines", Varying, NodeColor = "0.737911 0.099899 0.099899", DocumentationPolicy = "Strict"))`
- inherits: `FRigUnitMutable`
- desc: The base class for all mutable control rig spline nodes

#### struct `FRigUnit_ControlRigSplineFromPoints`  
`struct FRigUnit_ControlRigSplineFromPoints : public FRigUnit_ControlRigSplineBase`  
_L34-78_
- reflection: `USTRUCT(meta = (DisplayName = "Spline From Points", Keywords="Spline From Positions"))`
- inherits: `FRigUnit_ControlRigSplineBase`
- desc: Creates a Spline curve from an array of positions
- L38 _public function_ `FRigUnit_ControlRigSplineFromPoints()`
- L48 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L53 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (Input))` — The input points to form the spline
- L57 _public member_ `ESplineType SplineMode;` — `UPROPERTY(meta = (Input))` — The mode to use for the spline
- L61 _public member_ `bool bClosed;` — `UPROPERTY(meta = (Input))` — If True the spline will be closed
- L65 _public member_ `int32 SamplesPerSegment;` — `UPROPERTY(meta = (Input, ClampMin = "1"))` — Specifies the detail per segment of the spline
- L69 _public member_ `float Compression;` — `UPROPERTY(meta = (Input))` — The amount of compression to apply
- L73 _public member_ `float Stretch;` — `UPROPERTY(meta = (Input))` — The amount of stretch to allow for the spline
- L77 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Output))` — The resulting spline

#### struct `FRigUnit_ControlRigSplineFromTransforms`  
`struct FRigUnit_ControlRigSplineFromTransforms : public FRigUnit_ControlRigSplineBase`  
_L84-128_
- reflection: `USTRUCT(meta = (DisplayName = "Spline From Transforms", Keywords="Spline From Transforms"))`
- inherits: `FRigUnit_ControlRigSplineBase`
- desc: Creates a Spline curve from an array of transforms
- L88 _public function_ `FRigUnit_ControlRigSplineFromTransforms()`
- L98 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L103 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY(meta = (Input))` — The input transforms to build the spline from
- L107 _public member_ `ESplineType SplineMode;` — `UPROPERTY(meta = (Input))` — The mode to use for the spline
- L111 _public member_ `bool bClosed;` — `UPROPERTY(meta = (Input))` — If True the spline will be closed
- L115 _public member_ `int32 SamplesPerSegment;` — `UPROPERTY(meta = (Input))` — Specifies the detail per segment of the spline
- L119 _public member_ `float Compression;` — `UPROPERTY(meta = (Input))` — The amount of compression to apply
- L123 _public member_ `float Stretch;` — `UPROPERTY(meta = (Input))` — The amount of stretch to allow for the spline
- L127 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Output))` — The resulting spline

#### struct `FRigUnit_SetSplinePoints`  
`struct FRigUnit_SetSplinePoints : public FRigUnit_ControlRigSplineBaseMutable`  
_L134-155_
- reflection: `USTRUCT(meta = (DisplayName = "Set Spline Points"))`
- inherits: `FRigUnit_ControlRigSplineBaseMutable`
- desc: Set the points of a spline, given a spline and an array of positions
- L138 _public function_ `FRigUnit_SetSplinePoints()`
- L144 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L150 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (Input))` — The points to set on the spline. The assumption is that the number of points provided matches the points on the spline.
- L154 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input, Output))` — The spline to be updated

#### struct `FRigUnit_SetSplineTransforms`  
`struct FRigUnit_SetSplineTransforms : public FRigUnit_ControlRigSplineBaseMutable`  
_L161-182_
- reflection: `USTRUCT(meta = (DisplayName = "Set Spline Transforms"))`
- inherits: `FRigUnit_ControlRigSplineBaseMutable`
- desc: Set the points of a spline, given a spline and an array of transforms
- L165 _public function_ `FRigUnit_SetSplineTransforms()`
- L171 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L177 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY(meta = (Input))` — The transforms interpreted as positions to set on the spline. The assumption is that the number of transforms provided matches the points on the spline.
- L181 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input, Output))` — The spline to be updated

#### struct `FRigUnit_PositionFromControlRigSpline`  
`struct FRigUnit_PositionFromControlRigSpline : public FRigUnit_ControlRigSplineBase`  
_L188-213_
- reflection: `USTRUCT(meta = (DisplayName = "Position From Spline", Keywords="Point From Spline"))`
- inherits: `FRigUnit_ControlRigSplineBase`
- desc: Retrieves the position from a given Spline and U value
- L192 _public function_ `FRigUnit_PositionFromControlRigSpline()`
- L199 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L204 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The spline to evaluate
- L208 _public member_ `float U;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0"))` — The U value along the spline to evaluate
- L212 _public member_ `FVector Position;` — `UPROPERTY(meta = (Output))` — The resulting position on the spline

#### struct `FRigUnit_TransformFromControlRigSpline`  
`struct FRigUnit_TransformFromControlRigSpline : public FRigUnit_ControlRigSplineBase`  
_L219-254_
- reflection: `USTRUCT(meta = (DisplayName = "Transform From Spline (with UpVector)"))`
- inherits: `FRigUnit_ControlRigSplineBase`
- desc: Retrieves the transform from a given Spline and U value based on the given Up Vector and Roll
- L223 _public function_ `FRigUnit_TransformFromControlRigSpline()`
- L232 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L237 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The spline to evaluate
- L241 _public member_ `FVector UpVector;` — `UPROPERTY(meta = (Input))` — The up-vector to use to build the transform's rotation
- L245 _public member_ `float Roll;` — `UPROPERTY(meta = (Input))` — The roll to apply to the resulting rotation
- L249 _public member_ `float U;` — `UPROPERTY(meta = (Input))` — The U value along the spline to evaluate
- L253 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Output))` — The resulting composed transform

#### struct `FRigUnit_TransformFromControlRigSpline2`  
`struct FRigUnit_TransformFromControlRigSpline2 : public FRigUnit_ControlRigSplineBase`  
_L260-295_
- reflection: `USTRUCT(meta = (DisplayName = "Transform From Spline"))`
- inherits: `FRigUnit_ControlRigSplineBase`
- desc: Retrieves the transform from a given Spline and U value based on the given primary and secondary axis
- L264 _public function_ `FRigUnit_TransformFromControlRigSpline2()`
- L273 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L278 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The spline to evaluate
- L282 _public member_ `float U;` — `UPROPERTY(meta = (Input))` — The U value along the spline to evaluate
- L286 _public member_ `FVector PrimaryAxis;` — `UPROPERTY(meta = (Input))` — The primary axis to use when building the transform
- L290 _public member_ `FVector SecondaryAxis;` — `UPROPERTY(meta = (Input))` — The secondary axis to use when building the transform
- L294 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Output))` — The resulting composed transform

#### struct `FRigUnit_TangentFromControlRigSpline`  
`struct FRigUnit_TangentFromControlRigSpline : public FRigUnit_ControlRigSplineBase`  
_L301-326_
- reflection: `USTRUCT(meta = (DisplayName = "Tangent From Spline"))`
- inherits: `FRigUnit_ControlRigSplineBase`
- desc: Retrieves the tangent from a given Spline and U value
- L305 _public function_ `FRigUnit_TangentFromControlRigSpline()`
- L312 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L317 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The spline to evaluate
- L321 _public member_ `float U;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0"))` — The U value along the spline to evaluate
- L325 _public member_ `FVector Tangent;` — `UPROPERTY(meta = (Output))` — The tangent at the evaluated location on the spline

#### struct `FRigUnit_DrawControlRigSpline`  
`struct FRigUnit_DrawControlRigSpline : public FRigUnit_ControlRigSplineBaseMutable`  
_L332-362_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Spline"))`
- inherits: `FRigUnit_ControlRigSplineBaseMutable`
- desc: Draws the given spline in the viewport
- L336 _public function_ `FRigUnit_DrawControlRigSpline()`
- L344 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L349 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The spline to draw
- L353 _public member_ `FLinearColor Color;` — `UPROPERTY(meta = (Input))` — The color to use for the debug draw
- L357 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input))` — The line thickness to use when drawing the spline
- L361 _public member_ `int32 Detail;` — `UPROPERTY(meta = (Input))` — The detail to use to render the spline

#### struct `FRigUnit_GetLengthControlRigSpline`  
`struct FRigUnit_GetLengthControlRigSpline : public FRigUnit_ControlRigSplineBase`  
_L368-388_
- reflection: `USTRUCT(meta = (DisplayName = "Get Length Of Spline"))`
- inherits: `FRigUnit_ControlRigSplineBase`
- desc: Retrieves the length from a given Spline
- L372 _public function_ `FRigUnit_GetLengthControlRigSpline()`
- L378 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L383 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The spline to evaluate
- L387 _public member_ `float Length;` — `UPROPERTY(meta = (Output))` — The resulting length of the spline

#### struct `FRigUnit_GetLengthAtParamControlRigSpline`  
`struct FRigUnit_GetLengthAtParamControlRigSpline : public FRigUnit_ControlRigSplineBase`  
_L394-419_
- reflection: `USTRUCT(meta = (DisplayName = "Get Length At Param Of Spline"))`
- inherits: `FRigUnit_ControlRigSplineBase`
- desc: Retrieves the length from a given Spline
- L398 _public function_ `FRigUnit_GetLengthAtParamControlRigSpline()`
- L405 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L410 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The spline to evaluate
- L414 _public member_ `float U;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0"))` — The U value along the spline to evaluate
- L418 _public member_ `float Length;` — `UPROPERTY(meta = (Output))` — The resulting length

#### struct `FRigUnit_FitChainToSplineCurve`  
`struct FRigUnit_FitChainToSplineCurve : public FRigUnit_ControlRigSplineBaseMutable`  
_L426-539_
- reflection: `USTRUCT(meta=(DisplayName="Fit Chain on Spline Curve", Category="Hierarchy", Keywords="Fit,Resample,Spline", Deprecated = "5.0"))`
- inherits: `FRigUnit_ControlRigSplineBaseMutable`
- desc: Fits a given chain to a spline curve. Additionally provides rotational control matching the features of the Distribute Rotation node.
- L430 _public function_ `FRigUnit_FitChainToSplineCurve()`
- L445 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L452 _public member_ `FRigElementKeyCollection Items;` — `UPROPERTY(meta = (Input))` — The items to align
- L458 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The curve to align to
- L464 _public member_ `EControlRigCurveAlignment Alignment;` — `UPROPERTY(meta = (Input, Constant))` — Specifies how to align the chain on the curve
- L470 _public member_ `float Minimum;` — `UPROPERTY(meta = (Input, Constant))` — The minimum U value to use on the curve
- L476 _public member_ `float Maximum;` — `UPROPERTY(meta = (Input, Constant))` — The maximum U value to use on the curve
- L482 _public member_ `int32 SamplingPrecision;` — `UPROPERTY(meta = (Input, Constant))` — The number of samples to use on the curve. Clamped at 64.
- L488 _public member_ `FVector PrimaryAxis;` — `UPROPERTY(meta = (Input))` — The major axis being aligned - along the bone
- L495 _public member_ `FVector SecondaryAxis;` — `UPROPERTY(meta = (Input))` — The minor axis being aligned - towards the pole vector. You can use (0.0, 0.0, 0.0) to disable it.
- L502 _public member_ `FVector PoleVectorPosition;` — `UPROPERTY(meta = (Input))` — The position of the pole vector used for aligning the secondary axis. Only has an effect if the secondary axis is set.
- L508 _public member_ `TArray<FRigUnit_FitChainToCurve_Rotation> Rotations;` — `UPROPERTY(meta = (Input))` — The list of rotations to be applied along the curve
- L514 _public member_ `ERigVMAnimEasingType RotationEaseType;` — `UPROPERTY(meta = (Input, Constant))` — The easing to use between to rotations.
- L520 _public member_ `float Weight;` — `UPROPERTY(meta = (Input))` — The weight of the solver - how much the rotation should be applied
- L528 _public member_ `bool bPropagateToChildren;` — `UPROPERTY(meta = (Input, Constant))` — If set to true all of the global transforms of the children of this bone will be recalculated based on their local transforms. Note: This is computationally more expensive than turning it off.
- L532 _public member_ `FRigUnit_FitChainToCurve_DebugSettings DebugSettings;` — `UPROPERTY(meta = (Input, DetailsOnly))` — The debug settings to use
- L535 _public member_ `FRigUnit_FitChainToCurve_WorkData WorkData;` — `UPROPERTY(transient)`
- L537 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigUnit_FitChainToSplineCurveItemArray`  
`struct FRigUnit_FitChainToSplineCurveItemArray : public FRigUnit_ControlRigSplineBaseMutable`  
_L546-656_
- reflection: `USTRUCT(meta=(DisplayName="Fit Chain on Spline Curve", Keywords="Fit,Resample,Spline"))`
- inherits: `FRigUnit_ControlRigSplineBaseMutable`
- desc: Fits a given chain to a spline curve. Additionally provides rotational control matching the features of the Distribute Rotation node.
- L550 _public function_ `FRigUnit_FitChainToSplineCurveItemArray()`
- L565 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L572 _public member_ `TArray<FRigElementKey> Items;` — `UPROPERTY(meta = (Input))` — The items to align
- L578 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The curve to align to
- L584 _public member_ `EControlRigCurveAlignment Alignment;` — `UPROPERTY(meta = (Input, Constant))` — Specifies how to align the chain on the curve
- L590 _public member_ `float Minimum;` — `UPROPERTY(meta = (Input, Constant))` — The minimum U value to use on the curve
- L596 _public member_ `float Maximum;` — `UPROPERTY(meta = (Input, Constant))` — The maximum U value to use on the curve
- L602 _public member_ `int32 SamplingPrecision;` — `UPROPERTY(meta = (Input, Constant))` — The number of samples to use on the curve. Clamped at 64.
- L608 _public member_ `FVector PrimaryAxis;` — `UPROPERTY(meta = (Input))` — The major axis being aligned - along the bone
- L615 _public member_ `FVector SecondaryAxis;` — `UPROPERTY(meta = (Input))` — The minor axis being aligned - towards the pole vector. You can use (0.0, 0.0, 0.0) to disable it.
- L622 _public member_ `FVector PoleVectorPosition;` — `UPROPERTY(meta = (Input))` — The position of the pole vector used for aligning the secondary axis. Only has an effect if the secondary axis is set.
- L628 _public member_ `TArray<FRigUnit_FitChainToCurve_Rotation> Rotations;` — `UPROPERTY(meta = (Input))` — The list of rotations to be applied along the curve
- L634 _public member_ `ERigVMAnimEasingType RotationEaseType;` — `UPROPERTY(meta = (Input, Constant))` — The easing to use between to rotations.
- L640 _public member_ `float Weight;` — `UPROPERTY(meta = (Input))` — The weight of the solver - how much the rotation should be applied
- L648 _public member_ `bool bPropagateToChildren;` — `UPROPERTY(meta = (Input, Constant))` — If set to true all of the global transforms of the children of this bone will be recalculated based on their local transforms. Note: This is computationally more expensive than turning it off.
- L652 _public member_ `FRigUnit_FitChainToCurve_DebugSettings DebugSettings;` — `UPROPERTY(meta = (Input, DetailsOnly))` — The debug settings to use
- L655 _public member_ `FRigUnit_FitChainToCurve_WorkData WorkData;` — `UPROPERTY(transient)`

#### struct `FRigUnit_SplineConstraint_WorkData`  
`struct FRigUnit_SplineConstraint_WorkData`  
_L659-679_
- reflection: `USTRUCT()`
- L663 _public function_ `FRigUnit_SplineConstraint_WorkData()`
- L669 _public member_ `float ChainLength;` — `UPROPERTY()`
- L672 _public member_ `TArray<FTransform> ItemTransforms;` — `UPROPERTY()`
- L675 _public member_ `TArray<float> ItemSegments;` — `UPROPERTY()`
- L678 _public member_ `TArray<FCachedRigElement> CachedItems;` — `UPROPERTY()`

#### struct `FRigUnit_SplineConstraint`  
`struct FRigUnit_SplineConstraint : public FRigUnit_ControlRigSplineBaseMutable`  
_L687-752_
- reflection: `USTRUCT(meta=(DisplayName="Spline Constraint", Keywords="Fit,Resample,Spline"))`
- inherits: `FRigUnit_ControlRigSplineBaseMutable`
- desc: Fits a given chain to a spline curve. Additionally provides rotational control matching the features of the Distribute Rotation node.
- L691 _public function_ `FRigUnit_SplineConstraint()`
- L701 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L708 _public member_ `TArray<FRigElementKey> Items;` — `UPROPERTY(meta = (Input))` — The items to align
- L714 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The curve to align to
- L720 _public member_ `EControlRigCurveAlignment Alignment;` — `UPROPERTY(meta = (Input, Constant))` — Specifies how to align the chain on the curve
- L726 _public member_ `float Minimum;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0"))` — The minimum U value to use on the curve
- L732 _public member_ `float Maximum;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0"))` — The maximum U value to use on the curve
- L736 _public member_ `FVector PrimaryAxis;` — `UPROPERTY(meta = (Input))` — The primary axis to use when building transforms
- L740 _public member_ `FVector SecondaryAxis;` — `UPROPERTY(meta = (Input))` — The secondary axis to use when building transforms
- L748 _public member_ `bool bPropagateToChildren;` — `UPROPERTY(meta = (Input, Constant))` — If set to true all of the global transforms of the children of this bone will be recalculated based on their local transforms. Note: This is computationally more expensive than turning it off.
- L751 _public member_ `FRigUnit_SplineConstraint_WorkData WorkData;` — `UPROPERTY(transient)`

#### struct `FRigUnit_FitSplineCurveToChain`  
`struct FRigUnit_FitSplineCurveToChain : public FRigUnit_ControlRigSplineBaseMutable`  
_L759-785_
- reflection: `USTRUCT(meta=(DisplayName="Fit Spline Curve on Chain", Category="Hierarchy", Keywords="Fit,Resample,Spline", Deprecated = "5.0"))`
- inherits: `FRigUnit_ControlRigSplineBaseMutable`
- desc: Fits a given spline curve to a chain.
- L763 _public function_ `FRigUnit_FitSplineCurveToChain()`
- L768 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L775 _public member_ `FRigElementKeyCollection Items;` — `UPROPERTY(meta = (Input))` — The items to align to
- L781 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input, Output))` — The curve to align
- L783 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### struct `FRigUnit_FitSplineCurveToChainItemArray`  
`struct FRigUnit_FitSplineCurveToChainItemArray : public FRigUnit_ControlRigSplineBaseMutable`  
_L791-814_
- reflection: `USTRUCT(meta=(DisplayName="Fit Spline Curve on Chain", Keywords="Fit,Resample,Spline"))`
- inherits: `FRigUnit_ControlRigSplineBaseMutable`
- desc: Fits a given spline curve to a chain.
- L795 _public function_ `FRigUnit_FitSplineCurveToChainItemArray()`
- L800 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L807 _public member_ `TArray<FRigElementKey> Items;` — `UPROPERTY(meta = (Input))` — The items to align to
- L813 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input, Output))` — The curve to align

#### struct `FRigUnit_ClosestParameterFromControlRigSpline`  
`struct FRigUnit_ClosestParameterFromControlRigSpline : public FRigUnit_ControlRigSplineBase`  
_L820-846_
- reflection: `USTRUCT(meta = (DisplayName = "Closest Parameter From Spline"))`
- inherits: `FRigUnit_ControlRigSplineBase`
- desc: Retrieves the closest U value from a given Spline and a position
- L824 _public function_ `FRigUnit_ClosestParameterFromControlRigSpline()`
- L831 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L836 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The spline to evaluate
- L840 _public member_ `FVector Position;` — `UPROPERTY(meta = (Input))` — The position to evaluate
- L844 _public member_ `float U;` — `UPROPERTY(meta = (Output))` — The U value at the closest location on the spline

#### struct `FRigUnit_ParameterAtPercentage`  
`struct FRigUnit_ParameterAtPercentage : public FRigUnit_ControlRigSplineBase`  
_L852-878_
- reflection: `USTRUCT(meta = (DisplayName = "Parameter At Length Percentage"))`
- inherits: `FRigUnit_ControlRigSplineBase`
- desc: Returns the U parameter of a spline given a length percentage (0.0 - 1.0)
- L856 _public function_ `FRigUnit_ParameterAtPercentage()`
- L863 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L868 _public member_ `FControlRigSpline Spline;` — `UPROPERTY(meta = (Input))` — The spline to evaluate
- L872 _public member_ `float Percentage;` — `UPROPERTY(meta = (Input))` — The percentage (0.0 - 1.0) to evaluate
- L876 _public member_ `float U;` — `UPROPERTY(meta = (Output))` — The U value on the spline for the given percentage

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONTROLRIGSPLINE_API`
