# Plugins / GeometryScriptingCore

- module root: `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore`
- headers: 44; symbols: 2002
- symbol kinds: class=47, enum=97, enumerator=292, function=44, macro=43, member=658, namespace=6, prototype=650, struct=165
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Chaos, CoreUObject, EditorFramework, Engine, GeometryAlgorithms, GeometryCollectionEngine, MeshConversion, MeshConversionEngineTypes, MeshDescription, MeshReductionInterface, ModelingComponents, ModelingOperators, ModelingOperatorsEditorOnly, PlanarCut, SkeletalMeshDescription, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryCore, GeometryFramework, PhysicsCore, RenderCore

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/CollisionFunctions.h` (Public)


#### enum `EGeometryScriptCollisionGenerationMethod`  
`enum class EGeometryScriptCollisionGenerationMethod : uint8`  
_L17-27_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `AlignedBoxes = 0`
- L20 _public enumerator_ `OrientedBoxes = 1`
- L21 _public enumerator_ `MinimalSpheres = 2`
- L22 _public enumerator_ `Capsules = 3`
- L23 _public enumerator_ `ConvexHulls = 4`
- L24 _public enumerator_ `SweptHulls = 5`
- L25 _public enumerator_ `MinVolumeShapes = 6`
- L26 _public enumerator_ `LevelSets = 7`

#### enum `EGeometryScriptSweptHullAxis`  
`enum class EGeometryScriptSweptHullAxis : uint8`  
_L31-40_
- reflection: `UENUM(BlueprintType)`
- L33 _public enumerator_ `X = 0`
- L34 _public enumerator_ `Y = 1`
- L35 _public enumerator_ `Z = 2`
- L37 _public enumerator_ `SmallestBoxDimension = 3` — Use X/Y/Z axis with smallest axis-aligned-bounding-box dimension
- L39 _public enumerator_ `SmallestVolume = 4` — Compute projected hull for each of X/Y/Z axes and use the one that has the smallest volume

#### struct `FGeometryScriptCollisionFromMeshOptions`  
`struct FGeometryScriptCollisionFromMeshOptions`  
_L44-99_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public member_ `bool bEmitTransaction = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L52 _public member_ `EGeometryScriptCollisionGenerationMethod Method = EGeometryScriptCollisionGenerationMethod::MinVolumeShapes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L55 _public member_ `bool bAutoDetectSpheres = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L58 _public member_ `bool bAutoDetectBoxes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L61 _public member_ `bool bAutoDetectCapsules = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L64 _public member_ `float MinThickness = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L67 _public member_ `bool bSimplifyHulls = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L70 _public member_ `int ConvexHullTargetFaceCount = 25;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L73 _public member_ `float ConvexHullGeometricTolerance = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L76 _public member_ `int MaxConvexHullsPerMesh = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L79 _public member_ `float ConvexDecompositionSearchFactor = .5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L82 _public member_ `float ConvexDecompositionErrorTolerance = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L85 _public member_ `float ConvexDecompositionMinPartThickness = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L88 _public member_ `float SweptHullSimplifyTolerance = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L91 _public member_ `EGeometryScriptSweptHullAxis SweptHullAxis = EGeometryScriptSweptHullAxis::Z;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L95 _public member_ `bool bRemoveFullyContainedShapes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L98 _public member_ `int MaxShapeCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptSetSimpleCollisionOptions`  
`struct FGeometryScriptSetSimpleCollisionOptions`  
_L103-109_
- reflection: `USTRUCT(BlueprintType)`
- L108 _public member_ `bool bEmitTransaction = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptSetStaticMeshCollisionOptions`  
`struct FGeometryScriptSetStaticMeshCollisionOptions`  
_L113-121_
- reflection: `USTRUCT(BlueprintType)`
- L120 _public member_ `bool bMarkAsCustomized = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to mark the static mesh collision as customized when it is set, so that it will not be overwritten on next import. If false, Static Mesh collision will not be un-marked as Customized; its state will just be left unchanged.

#### enum `ENegativeSpaceSampleMethod`  
`enum class ENegativeSpaceSampleMethod : uint8`  
_L126-134_
- reflection: `UENUM(BlueprintType)`
- desc: Method to distribute sampling spheres, used by FComputeNegativeSpaceOptions
- L129 _public enumerator_ `Uniform` — Place sample spheres in a uniform grid pattern
- L131 _public enumerator_ `VoxelSearch` — Use voxel-based subtraction and offsetting methods to specifically target concavities
- L133 _public enumerator_ `NavigableVoxelSearch` — A more-principled version of VoxelSearch that attempts to target specifically the space that is reachable by characters at least as large as a MinRadius sphere

#### struct `FNegativeSpaceDirectionalToleranceScale`  
`struct FNegativeSpaceDirectionalToleranceScale`  
_L139-154_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines direction-specific custom scaling to apply to the FComputeNegativeSpaceOptions::NegativeSpaceTolerance value, based on the direction to the surface For example, this can be used to more closely fit collision shapes on ground surfaces
- L145 _public member_ `FVector Direction = FVector(0,0,-1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Direction to apply custom tolerance scale
- L149 _public member_ `double AngleRange = 45.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (ClampMin = 0, ClampMax = 180, Units = deg))` — Angle range around direction within which the scale will be applied, in degrees
- L153 _public member_ `double ScaleFactor = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (ClampMin = .1, ClampMax = 1, UIMin = .25))` — Scale factor to apply to tolerance. Should be in the (0, 1] range

#### struct `FComputeNegativeSpaceOptions`  
`struct FComputeNegativeSpaceOptions`  
_L158-197_
- reflection: `USTRUCT(BlueprintType)`
- desc: Options controlling how to sample the negative space of shapes, e.g. to define a region that must be avoided when merging collision shapes
- L164 _public member_ `ENegativeSpaceSampleMethod SampleMethod = ENegativeSpaceSampleMethod::Uniform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace)` — Method to use to find and sample negative space
- L168 _public member_ `bool bRequireSearchSampleCoverage = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace, meta = (EditCondition = "SampleMethod == EGeometryScriptNegativeSpaceSampleMethod::VoxelSearch", EditConditionHides))` — Whether to require that all candidate locations identified by Voxel Search are covered by negative space samples, up to the specified Min Sample Spacing. Only applies to Voxel Search.
- L172 _public member_ `bool bOnlyConnectedToHull = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace, meta = (EditCondition = "SampleMethod == EGeometryScriptNegativeSpaceSampleMethod::VoxelSearch", EditConditionHides))` — When performing Voxel Search, only look for negative space that is connected out to the convex hull. This removes inaccessable internal negative space from consideration. Only applies to Voxel Search.
- L176 _public member_ `int32 MaxVoxelsPerDim = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace, meta = (ClampMin = 4, ClampMax = 1290))` — When performing Voxel Search, maximum number of voxels to use along each dimension
- L180 _public member_ `int32 TargetNumSamples = 50;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace, meta = (ClampMin = 1))` — Approximate number of spheres to consider when covering negative space
- L184 _public member_ `double MinSampleSpacing = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace, meta = (ClampMin = 0, Units = cm))` — Minimum desired spacing between sphere centers; if > 0, will attempt not to place sphere centers closer than this
- L188 _public member_ `double NegativeSpaceTolerance = 2.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace, meta = (ClampMin = .01, UIMin = .1, Units = cm))` — Amount of space to leave between convex hulls and protected negative space
- L192 _public member_ `TArray<FNegativeSpaceDirectionalToleranceScale> ToleranceDirectionalScales;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace, AdvancedDisplay)` — Optionally scale the negative space tolerances in custom directions
- L196 _public member_ `double MinRadius = 10.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace, meta = (ClampMin = 0, Units = cm))` — Spheres smaller than this are not included in the negative space

#### struct `FNavigableConvexDecompositionOptions`  
`struct FNavigableConvexDecompositionOptions`  
_L206-234_
- reflection: `USTRUCT(BlueprintType)`
- desc: Settings to define the important regions for a convex decomposition to preserve for a given input shape. Note: this is similar to FComputeNegativeSpaceOptions, but with better default behavior and more intuitive parameters.
- L212 _public member_ `double MinRadius = 100;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Minimum radius of characters/manipulators that should be able to navigate an input shape
- L216 _public member_ `double Tolerance = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Tolerance distance: convex decomposition should be no further than this from an input shape, in the navigable regions
- L220 _public member_ `bool bIgnoreUnreachableInternalSpace = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to only consider navigable space that is accessible from outside the shape. (Note this parameter is called bOnlyConnectedToHull elsewhere.)
- L224 _public member_ `TArray<FVector> CustomNavigablePositions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Optional list of locations that we expect to be navigable
- L229 _public member_ `TArray<FPlane> UnreachablePlanes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Optional list of planes defining unreachable space (on their negative side) Use this for example to specify a ground plane, if a mesh will always be placed on ground and need not be navigable from below.
- L233 _public member_ `TArray<FNegativeSpaceDirectionalToleranceScale> ToleranceDirectionalScales;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace, AdvancedDisplay)` — Optionally scale the tolerance in custom directions

#### struct `FGeometryScriptMergeSimpleCollisionOptions`  
`struct FGeometryScriptMergeSimpleCollisionOptions`  
_L239-283_
- reflection: `USTRUCT(BlueprintType)`
- desc: Options controlling how collision shapes can be merged together
- L248 _public member_ `int MaxShapeCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If > 0, merge down to at most this many simple shapes. (If <= 0, this value is ignored.)
- L255 _public member_ `double ErrorTolerance = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = "0", UIMax = "100.", Units = cm))` — Error tolerance to use to decide to convex hulls together, in cm. If merging two hulls would increase the volume by more than this ErrorTolerance cubed, the merge is not accepted.
- L262 _public member_ `double MinThicknessTolerance = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = "0", UIMax = "100.", Units = cm))` — Always attempt to merge parts thicker than this, ignoring ErrorTolerance and MaxShapeCount. Note: Negative space, if set, will still prevent merges.
- L266 _public member_ `bool bConsiderAllPossibleMerges = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to consider merges between every shape. If false, will only merge shapes that have overlapping or nearby bounding boxes.
- L270 _public member_ `FGeometryScriptSphereCovering PrecomputedNegativeSpace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace)` — Negative space that must be preserved during merging
- L274 _public member_ `bool bComputeNegativeSpace = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace)` — Whether to compute a new sphere covering representing the negative space of the input shapes
- L278 _public member_ `FComputeNegativeSpaceOptions ComputeNegativeSpaceOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NegativeSpace)` — Options controlling how the negative space is computed, if ComputeNegativeSpace is true
- L282 _public member_ `FGeometryScriptSimpleCollisionTriangulationOptions ShapeToHullTriangulation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConvexHulls)` — Controls for how smooth shapes can be triangulated when/if converted to a convex hull for a merge

#### enum `EGeometryScriptConvexHullSimplifyMethod`  
`enum class EGeometryScriptConvexHullSimplifyMethod : uint8`  
_L287-293_
- reflection: `UENUM(BlueprintType)`
- desc: Methods to simplify convex hulls, used by FGeometryScriptConvexHullSimplificationOptions
- L290 _public enumerator_ `MeshQSlim` — Simplify convex hulls using a general mesh-based simplifier, and taking the convex hull of the simplified mesh
- L292 _public enumerator_ `AngleTolerance` — Simplify convex hulls by merging hull faces that have similar normals

#### struct `FGeometryScriptConvexHullSimplificationOptions`  
`struct FGeometryScriptConvexHullSimplificationOptions`  
_L296-319_
- reflection: `USTRUCT(BlueprintType)`
- L303 _public member_ `EGeometryScriptConvexHullSimplifyMethod SimplificationMethod = EGeometryScriptConvexHullSimplifyMethod::MeshQSlim;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Method to use to simplify convex hulls
- L307 _public member_ `float SimplificationDistanceThreshold = 10.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Simplified hull should stay within this distance of the initial convex hull. Used by the MeshQSlim simplification method.
- L311 _public member_ `float SimplificationAngleThreshold = 10.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Simplified hull should preserve angles larger than this (in degrees). Used by the AngleTolerance simplification method.
- L318 _public member_ `int32 MinTargetFaceCount = 12;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (ClampMin = 4))` — The minimum number of faces to use for the convex hull. Note that for the MeshQSlim method all faces are triangles, while the AngleTolerance method can consider more general polygons.

#### struct `FGeometryScriptConvexHullApproximationOptions`  
`struct FGeometryScriptConvexHullApproximationOptions`  
_L322-346_
- reflection: `USTRUCT(BlueprintType)`
- L329 _public member_ `bool bFitSpheres = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to attempt to replace convex hulls with spheres
- L333 _public member_ `bool bFitBoxes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to attempt to replace convex hulls with boxes
- L337 _public member_ `bool bFitCapsules = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to attempt to replace convex hulls with capsules
- L341 _public member_ `float DistanceThreshold = 5.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Approximating shape should be at least this close to the original shape
- L345 _public member_ `float VolumeDiffThreshold_Fraction = .15f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Acceptable difference between approximating shape volume and convex hull volume, as a fraction of convex hull volume

#### struct `FGeometryScriptTransformCollisionOptions`  
`struct FGeometryScriptTransformCollisionOptions`  
_L349-367_
- reflection: `USTRUCT(BlueprintType)`
- L356 _public member_ `bool bWarnOnInvalidTransforms = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to log a warning when a requested transform is not compatible with the simple collision shapes
- L366 _public member_ `bool bCenterTransformPivotPerShape = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true, we apply the Transform to each collision shape separately, and pivot the Transform around the local center of each shape. Otherwise, we apply the Transform to all shapes in the same space, with the pivot at the origin of the origin of that space. For example, if we apply a uniform 2x scale to a sphere w/ center (1,1,1), with this enabled, the center will not move and only the radius will scale. If this setting is not enabled, the 2x scale will move the sphere center to (2,2,2)

#### class `UGeometryScriptLibrary_CollisionFunctions`  
`class UGeometryScriptLibrary_CollisionFunctions : public UBlueprintFunctionLibrary`  
_L370-628_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_Collision"))`
- inherits: `UBlueprintFunctionLibrary`
- L382 _public prototype_ `static bool SetStaticMeshCustomComplexCollision( UStaticMesh* StaticMeshAsset, UStaticMesh* StaticMeshCollisionAsset, bool bEmitTransaction, bool bMarkCollisionAsCustomized = true, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (HidePin = "Debug"))` — Set a static mesh as the custom collision for another static mesh to use. Note: Only works if editor-only data is available. @return true on success.
- L394 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* SetStaticMeshCollisionFromMesh( UDynamicMesh* FromDynamicMesh, UStaticMesh* ToStaticMeshAsset, FGeometryScriptCollisionFromMeshOptions Options, FGeometryScriptSetStaticMeshCollisionOptions StaticMeshCollisionOptions = FGeometryScriptSetStaticMeshCollisionOptions(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (HidePin = "Debug"))` — Generates Simple Collision shapes for a Static Mesh Asset based on the input Dynamic Mesh.
- L407 _public prototype_ `SetStaticMeshCollisionFromComponent( UStaticMesh* StaticMeshAsset, UPrimitiveComponent* SourceComponent, FGeometryScriptSetSimpleCollisionOptions Options = FGeometryScriptSetSimpleCollisionOptions(), FGeometryScriptSetStaticMeshCollisionOptions StaticMeshCollisionOptions = FGeometryScriptSetStaticMeshCollisionOptions(), UGeometryScriptDebug* Debug = nullptr);`
- L418 _public prototype_ `static UPARAM(DisplayName = "IsCustomized") bool StaticMeshHasCustomizedCollision(UStaticMesh* Stati` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision")` — @returns true if the static mesh has customized collision. If no editor data is available, returns false.
- L424 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* SetDynamicMeshCollisionFromMesh( UDynamicMesh* FromDynamicMesh, UDynamicMeshComponent* ToDynamicMeshComponent, FGeometryScriptCollisionFromMeshOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (HidePin = "Debug"))` — Generate Simple Collision shapes for a Dynamic Mesh Component based on the input Dynamic Mesh.
- L436 _public prototype_ `ResetDynamicMeshCollision( UDynamicMeshComponent* Component, bool bEmitTransaction = false, UGeometryScriptDebug* Debug = nullptr);`
- L445 _public prototype_ `static void ResetSimpleCollision(UPARAM(ref) FGeometryScriptSimpleCollision& SimpleCollision);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision")` — Clears the Simple Collision shapes
- L451 _public prototype_ `static UPARAM(DisplayName = "Simple Collision") FGeometryScriptSimpleCollision GetSimpleCollisionFromComponent( UPrimitiveComponent* Component, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (HidePin = "Debug"))` — Get the simple collision from a Primitive Component
- L461 _public prototype_ `SetSimpleCollisionOfDynamicMeshComponent( const FGeometryScriptSimpleCollision& SimpleCollision, UDynamicMeshComponent* DynamicMeshComponent, FGeometryScriptSetSimpleCollisionOptions Options, UGeometryScriptDebug* Debug = nullptr);`
- L471 _public prototype_ `static UPARAM(DisplayName = "Simple Collision") FGeometryScriptSimpleCollision GetSimpleCollisionFromStaticMesh(UStaticMesh* StaticMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (HidePin = "Debug"))` — Get the simple collision from a Static Mesh
- L479 _public prototype_ `SetSimpleCollisionOfStaticMesh( const FGeometryScriptSimpleCollision& SimpleCollision, UStaticMesh* StaticMesh, FGeometryScriptSetSimpleCollisionOptions Options, FGeometryScriptSetStaticMeshCollisionOptions StaticMeshCollisionOptions = FGeometryScriptSetStaticMeshCollisionOptions(), UGeometryScriptDebug* Debug = nullptr);`
- L490 _public prototype_ `static UPARAM(DisplayName = "Simple Collision") FGeometryScriptSimpleCollision GenerateCollisionFromMesh( UDynamicMesh* FromDynamicMesh, FGeometryScriptCollisionFromMeshOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (HidePin = "Debug"))` — Generate Simple Collision shapes for an input Dynamic Mesh shape
- L500 _public function_ `static int32 GetSimpleCollisionShapeCount(const FGeometryScriptSimpleCollision& SimpleCollision)` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (ScriptMethod))` — Count of number of simple collision shapes
- L510 _public prototype_ `static UPARAM(DisplayName = "Transformed Collision") FGeometryScriptSimpleCollision TransformSimpleCollisionShapes( const FGeometryScriptSimpleCollision& SimpleCollision, FTransform Transform, const FGeometryScriptTransformCollisionOptions& TransformOptions, bool& bSuccess, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (HidePin = "Debug", AutoCreateRefTerm = "TransformOptions"))` — Transform simple collision shapes @param bSuccess	Indicates whether all collision shapes were accurately transformed. On failure, shapes will still be copied over and a best-effort transform will still be applied.
- L522 _public prototype_ `static void CombineSimpleCollision( UPARAM(ref) FGeometryScriptSimpleCollision& CollisionToUpdate, const FGeometryScriptSimpleCollision& AppendCollision, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (ScriptMethod, HidePin = "Debug"))` — Add simple collision shapes from AppendCollision to CollisionToUpdate
- L532 _public prototype_ `static void CombineSimpleCollisionArray( const TArray<FGeometryScriptSimpleCollision>& SimpleCollisionArray, FGeometryScriptSimpleCollision& SimpleCollision, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (HidePin = "Debug"))` — Combine the SimpleCollisionArray collision shapes into a single SimpleCollision
- L546 _public prototype_ `static void SimplifyConvexHulls( UPARAM(ref) FGeometryScriptSimpleCollision& SimpleCollision, const FGeometryScriptConvexHullSimplificationOptions& SimplifyOptions, bool& bHasSimplified, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (ScriptMethod, HidePin = "Debug", AutoCreateRefTerm = "SimplifyOptions"))` — Simplify any convex hulls in the given simple collision representation. Updates the passed-in Simple Collision. @param SimpleCollision		The collision in which to attempt to simplify the convex hulls @param ConvexSimplifyOptions	Options controlling how convex hulls are simplified @param bHasSimplified		Indicates whether any convex hulls were modified
- L562 _public prototype_ `static void ApproximateConvexHullsWithSimplerCollisionShapes( UPARAM(ref) FGeometryScriptSimpleCollision& SimpleCollision, const FGeometryScriptConvexHullApproximationOptions& ApproximateOptions, bool& bHasApproximated, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (ScriptMethod, HidePin = "Debug", AutoCreateRefTerm = "ApproximateOptions"))` — Attempt to approximate any convex hulls in the given simple collision representation. Updates the passed-in Simple Collision. Convex hulls that aren't well approximated (to tolerances set in ApproximateOptions) will remain as convex hulls. @param SimpleCollision		The collision in which to attempt to approximate the convex hulls @param ConvexSimplifyOptions	Options controlling how convex hulls are approximated @param bHasApproximated		Indicates whether any convex hulls were replaced with simpler approximations
- L578 _public prototype_ `static UPARAM(DisplayName = "Merged Simple Collision") FGeometryScriptSimpleCollision MergeSimpleCollisionShapes( const FGeometryScriptSimpleCollision& SimpleCollision, const FGeometryScriptMergeSimpleCollisionOptions& MergeOptions, bool& bHasMerged, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (HidePin = "Debug", AutoCreateRefTerm = "MergeOptions"))` — Attempt to merge collision shapes to create a representation with fewer overall shapes. @param SimpleCollision		The collision to attempt to simplify by merging shapes @param MergeOptions			Options controlling how shapes can be merged @param bHasMerged			Indicates whether any shapes have been merged @return						Simple Collision with collision shapes merged, as allowed by settings
- L593 _public prototype_ `static UPARAM(DisplayName = "Negative Space") FGeometryScriptSphereCovering ComputeNegativeSpace( const FGeometryScriptDynamicMeshBVH& MeshBVH, const FComputeNegativeSpaceOptions& NegativeSpaceOptions, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (HidePin = "Debug", AutoCreateRefTerm = "NegativeSpaceOptions"))` — Compute the negative space of an input mesh surface that should be protected when merging simple collision shapes @param MeshBVH				A Dynamic Mesh BVH structure of the surface for which we will compute negative space @param NegativeSpaceOptions	Options controlling how the negative space is generated @return						A set of spheres that cover the negative space of the input shape
- L608 _public prototype_ `static UPARAM(DisplayName = "Convex Decomposition") FGeometryScriptSimpleCollision ComputeNavigableConvexDecomposition( const UDynamicMesh* TargetMesh, const FNavigableConvexDecompositionOptions& Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Collision", meta = (HidePin = "Debug", AutoCreateRefTerm = "Options"))` — Compute the 'navigable' convex decomposition of an input mesh surface, i.e. a convex decomposition appropriate for a character of (or larger than) a given size @param TargetMesh	Mesh to decompose to convex hulls @param Options		Options controlling the convex decomposition @return				The resulting convex hulls as simple collision shapes
- L619 _public prototype_ `static TArray<FSphere> Conv_GeometryScriptSphereCoveringToSphereArray(const FGeometryScriptSphereCovering& SphereCovering);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "SphereCovering To Array Of Spheres", CompactNodeTitle = "->", BlueprintAutocast), Category = "GeometryScript|Collision")` — @return An array of the spheres in the given Sphere Covering
- L625 _public prototype_ `static FGeometryScriptSphereCovering Conv_SphereArrayToGeometryScriptSphereCovering(const TArray<FSphere>& Spheres);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Array Of Spheres To SphereCovering", CompactNodeTitle = "->", BlueprintAutocast), Category = "GeometryScript|Collision")` — @return A sphere covering containing the spheres in the given Spheres array

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/ContainmentFunctions.h` (Public)


#### struct `FGeometryScriptConvexHullOptions`  
`struct FGeometryScriptConvexHullOptions`  
_L17-34_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `bool bPrefilterVertices = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L25 _public member_ `int PrefilterGridResolution = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L29 _public member_ `int SimplifyToFaceCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Try to simplify each convex hull to this triangle count. If 0, no simplification
- L33 _public member_ `float GeometricToleranceAfterTarget = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — After SimplifyToFaceCount is applied, further simplify within this tolerance. If SimplifyToFaceCount <= 0, or this tolerance is <= 0, does not apply.

#### struct `FGeometryScriptSweptHullOptions`  
`struct FGeometryScriptSweptHullOptions`  
_L39-61_
- reflection: `USTRUCT(BlueprintType)`
- L44 _public member_ `bool bPrefilterVertices = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L47 _public member_ `int PrefilterGridResolution = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L50 _public member_ `float MinThickness = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L54 _public member_ `bool bSimplify = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L57 _public member_ `float MinEdgeLength = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L60 _public member_ `float SimplifyTolerance = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptConvexDecompositionOptions`  
`struct FGeometryScriptConvexDecompositionOptions`  
_L66-89_
- reflection: `USTRUCT(BlueprintType)`
- L72 _public member_ `int NumHulls = 2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DecompositionOptions)` — How many convex pieces to target per mesh when creating convex decompositions.  If ErrorTolerance is set, can create fewer pieces.
- L76 _public member_ `double SearchFactor = .5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DecompositionOptions)` — How much additional decomposition decomposition + merging to do, as a fraction of max pieces.  Larger values can help better-cover small features, while smaller values create a cleaner decomposition with less overlap between hulls.
- L80 _public member_ `double ErrorTolerance = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DecompositionOptions)` — Error tolerance to guide convex decomposition (in cm); we stop adding new parts if the volume error is below the threshold.  For volumetric errors, value will be cubed.
- L84 _public member_ `double MinPartThickness = .1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DecompositionOptions)` — Minimum part thickness for convex decomposition (in cm); hulls thinner than this will be merged into adjacent hulls, if possible.
- L88 _public member_ `int SimplifyToFaceCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConvexHullOptions)` — Try to simplify each convex hull to this triangle count. If 0, no simplification

#### enum `FGeometryScriptFitOrientedBoxMethod`  
`enum class FGeometryScriptFitOrientedBoxMethod : uint8`  
_L92-98_
- reflection: `UENUM()`
- L95 _public enumerator_ `FastIterative` — Use an iterative method to fit the oriented box, starting from a fast initial guess and locally refining
- L97 _public enumerator_ `Precise` — Use a precise method to fit the oriented box, testing a potentially large space of options for the best fit

#### struct `FGeometryScriptFitOrientedBoxOptions`  
`struct FGeometryScriptFitOrientedBoxOptions`  
_L101-113_
- reflection: `USTRUCT(BlueprintType)`
- L107 _public member_ `double MinBoxDimension = .01;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta=(ClampMin=0))` — Minimum length of the resulting bounding box along any of its principal directions
- L111 _public member_ `FGeometryScriptFitOrientedBoxMethod FitMethod = FGeometryScriptFitOrientedBoxMethod::FastIterative;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Method to use for fitting the bounding box

#### class `UGeometryScriptLibrary_ContainmentFunctions`  
`class UGeometryScriptLibrary_ContainmentFunctions : public UBlueprintFunctionLibrary`  
_L117-186_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_Containment"))`
- inherits: `UBlueprintFunctionLibrary`
- L129 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputeMeshConvexHull( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "Hull Mesh", ref) UDynamicMesh* CopyToMesh, UPARAM(DisplayName = "Hull Mesh") UDynamicMesh*& CopyToMeshOut, FGeometryScriptMeshSelection Selection, FGeometryScriptConvexHullOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Containment", meta=(ScriptMethod))` — Compute the Convex Hull of a given Target Mesh, or part of the mesh if an optional Selection is provided, and put the result in Hull Mesh @param CopyToMesh	The Dynamic Mesh to store the convex hull geometry. @param CopyToMeshOut	The resulting convex hull. @param Selection	Selection of mesh faces/vertices to contain in the convex hull. If not provided, entire mesh is used.
- L145 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputeMeshSweptHull( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "Hull Mesh", ref) UDynamicMesh* CopyToMesh, UPARAM(DisplayName = "Hull Mesh") UDynamicMesh*& CopyToMeshOut, FTransform ProjectionFrame, FGeometryScriptSweptHullOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Containment", meta=(ScriptMethod))` — Compute the Swept Hull of a given Target Mesh for a given 3D Plane defined by ProjectionFrame, and put the result in Hull Mesh The Swept Hull is a linear sweep of the 2D convex hull of the mesh vertices projected onto the plane (the sweep precisely contains the mesh extents along the plane normal) @param CopyToMesh	The Dynamic Mesh to store the swept hull geometry. @param CopyToMeshOut	The resulting swept hull.
- L164 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputeMeshConvexDecomposition( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "Hull Mesh", ref) UDynamicMesh* CopyToMesh, UPARAM(DisplayName = "Hull Mesh") UDynamicMesh*& CopyToMeshOut, FGeometryScriptConvexDecompositionOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Containment|Experimental", meta=(ScriptMethod))` — Compute a Convex Hull Decomposition of the given TargetMesh. Assuming more than one hull is requested, multiple hulls will be returned that attempt to approximate the mesh. If simplification settings are enabled, there is no guarantee that the entire mesh is contained in the hulls. @warning this function can be quite expensive, and the results are expected to change in the future as the Convex Decomposition algorithm is improved @param CopyToMesh The Dynamic Mesh to store the convex hulls as a single, combined mesh. Note: SplitMeshByComponents can separate this result into its convex parts. @param CopyToMeshOut A combined mesh of the convex hulls. Note: SplitMeshByComponents can separate this result into its convex parts.
- L178 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputeMeshOrientedBox( UDynamicMesh* TargetMesh, FOrientedBox& OrientedBoxOut, FGeometryScriptMeshSelection Selection, FGeometryScriptFitOrientedBoxOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Containment", meta = (ScriptMethod, KeyWords = "Fit Bounding OBB"))` — Compute an oriented box fitting a given Target Mesh, or optionally a selection of the mesh @param Selection	Selection of mesh faces/vertices to contain in the oriented box. If not provided, entire mesh is used.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/GeometryScriptSelectionTypes.h` (Public)


#### enum `EGeometryScriptMeshSelectionType`  
`enum class EGeometryScriptMeshSelectionType : uint8`  
_L20-26_
- reflection: `UENUM(BlueprintType)`
- desc: Type of index stored in a FGeometryScriptMeshSelection
- L22 _public enumerator_ `Vertices = 0`
- L23 _public enumerator_ `Edges = 3`
- L24 _public enumerator_ `Triangles = 1`
- L25 _public enumerator_ `Polygroups = 2 UMETA(DisplayName = "PolyGroups")`

#### enum `EGeometryScriptMeshSelectionConversionType`  
`EGeometryScriptMeshSelectionConversionType : uint8`  
_L34-40_
- reflection: `UENUM(BlueprintType)`
- reflection: `UE_DEPRECATED(5.5, "This enum is unused, and may be removed in the future. To convert selection types, we use EGeometryScriptMeshSelectionType to specify the desired result type.")`
- L36 _public enumerator_ `NoConversion = 0`
- L37 _public enumerator_ `ToVertices = 1`
- L38 _public enumerator_ `ToTriangles = 2`
- L39 _public enumerator_ `ToPolygroups = 3 UMETA(DisplayName = "To PolyGroups")`

#### enum `EGeometryScriptCombineSelectionMode`  
`enum class EGeometryScriptCombineSelectionMode : uint8`  
_L46-51_
- reflection: `UENUM(BlueprintType)`
- desc: Type of Combine operation to use when combining multiple FGeometryScriptMeshSelection
- L48 _public enumerator_ `Add`
- L49 _public enumerator_ `Subtract`
- L50 _public enumerator_ `Intersection`

#### enum `EGeometryScriptEmptySelectionBehavior`  
`enum class EGeometryScriptEmptySelectionBehavior : uint8`  
_L57-61_
- reflection: `UENUM(BlueprintType)`
- desc: Behavior of operations when a MeshSelection is empty
- L59 _public enumerator_ `FullMeshSelection = 0`
- L60 _public enumerator_ `EmptySelection = 1`

#### struct `FGeometryScriptMeshSelection`  
`struct FGeometryScriptMeshSelection`  
_L77-175_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Mesh Selection"))`
- desc: FGeometryScriptMeshSelection is a container for a Mesh Selection used in Geometry Script. The actual selection representation is not exposed to BP, use functions in MeshSelectionFunctions/etc to manipulate the selection. Internally the selection is stored as a SharedPtr to a FGeometrySelection, which stores a TSet (so unique add and remove are efficient, but the selection cannot be directly indexed without converting to an Array). Note that the Selection storage is not a UProperty, and is not serialized. FGeometryScriptMeshSelection instances *cannot* be serialized, they are only transient data structures, that can be created and used Blueprint instances.
- L81 _public prototype_ `FGeometryScriptMeshSelection();`
- L83 _public prototype_ `void SetSelection(const FGeometryScriptMeshSelection& Selection);`
- L84 _public prototype_ `void SetSelection(const UE::Geometry::FGeometrySelection& Selection);`
- L85 _public prototype_ `void SetSelection(UE::Geometry::FGeometrySelection&& Selection);`
- L86 _public prototype_ `void ClearSelection();`
- L88 _public prototype_ `bool IsEmpty() const;`
- L90 _public prototype_ `EGeometryScriptMeshSelectionType GetSelectionType() const;`
- L95 _public prototype_ `int32 GetNumSelected() const;` — Note that for edge selections, this can return more elements than expected because both can be redundantly represented i.e. an edge can be in the selection once per 'half edge', since it is represented by triangle/index-in-triangle pair. Call GetNumUniqueValidSelected(Mesh) to get the number of unique elements in the selection
- L97 _public prototype_ `int32 GetNumUniqueSelected(const UE::Geometry::FDynamicMesh3& Mesh) const;` — Return the number of valid, unique elements in the selection; e.g., with no double-counting of selected edges
- L98 _public prototype_ `void DebugPrint() const;`
- L100 _public function_ `static bool ConvertIndexTypeToSelectionType(EGeometryScriptIndexType IndexType, EGeometryScriptMeshSelectionType& OutSelectionType)`
- L123 _public prototype_ `void CombineSelectionInPlace(const FGeometryScriptMeshSelection& SelectionB, EGeometryScriptCombineSelectionMode CombineMode);` — Combine SelectionB with current selection, updating current selection, using CombineMode to control how combining happens
- L131 _public prototype_ `EGeometryScriptIndexType ConvertToMeshIndexArray(const UE::Geometry::FDynamicMesh3& Mesh, TArray<int32>& IndexListOut, EGeometryScriptIndexType ConvertToType = EGeometryScriptIndexType::Any) const;` — Convert the current selection to a TArray, optionally converting to ConvertToType. For (Tri|Group)=>Vtx, all triangle vertices (in triangles or PolyGroups) are included. For Vtx=>Tri, all one-ring vertices are included. For Group=>Tri, all Triangles are found via enumerating over mesh. (Tri|Vtx)=>Group, all GroupIDs of all triangles/one-ring triangles are included
- L138 _public prototype_ `void ProcessByTriangleID(const UE::Geometry::FDynamicMesh3& Mesh, TFunctionRef<void(int32)> PerTriangleFunc, bool bProcessAllTrisIfSelectionEmpty = false) const;` — Call PerTriangleFunc for each TriangleID in the Selection. For Vertex Selections, Vertex one-rings are enumerated and accumulated in a TSet. For PolyGroup Selections, a full mesh iteration is used to find all Triangles in the groups.
- L147 _public prototype_ `void ProcessByVertexID(const UE::Geometry::FDynamicMesh3& Mesh, TFunctionRef<void(int32)> PerVertexFunc, bool bProcessAllVertsIfSelectionEmpty = false) const;` — Call PerVertexFunc for each VertexID in the Selection. For Triangle Selections, Triangles Vertex tuples are enumerated and accumulated in a TSet. For PolyGroup Selections, a full mesh iteration is used to find all Triangle Vertices in the groups (accumulated in a TSet)
- L157 _public prototype_ `void ProcessByEdgeID(const UE::Geometry::FDynamicMesh3& Mesh, TFunctionRef<void(int32)> PerEdgeFunc, bool bProcessAllVertsIfSelectionEmpty = false) const;` — Call PerEdgeFunc for each EdgeID in the Selection. For Vertex Selections, Vertex Edge one-rings are enumerated and accumulated in a TSet. For Triangle Selections, Triangle Edges are enumerated and accumulated in a TSet. For PolyGroup Selections, a full mesh iteration is used to find all Triangle Edges in the groups (accumulated in a TSet)
- L163 _public function_ `bool operator==(const FGeometryScriptMeshSelection& Other) const` — Required by TStructOpsTypeTraits interface
- L167 _public function_ `bool operator!=(const FGeometryScriptMeshSelection& Other) const`
- L174 _private member_ `TSharedPtr<UE::Geometry::FGeometrySelection> GeoSelection;` — keeping this private for now in case it needs to be revised in 5.2+

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptMeshSelection> : public TStructOpsTypeTraitsBase2<FGeometryScriptMeshSelection>`  
_L179-185_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptMeshSelection>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L182-184_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)
- L183 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonc73573cf0103`)

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/GeometryScriptTypes.h` (Public)


#### enum `EGeometryScriptOutcomePins`  
`enum class EGeometryScriptOutcomePins : uint8`  
_L22-26_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `Failure`
- L25 _public enumerator_ `Success`

#### enum `EGeometryScriptSearchOutcomePins`  
`enum class EGeometryScriptSearchOutcomePins : uint8`  
_L29-33_
- reflection: `UENUM(BlueprintType)`
- L31 _public enumerator_ `Found`
- L32 _public enumerator_ `NotFound`

#### enum `EGeometryScriptContainmentOutcomePins`  
`enum class EGeometryScriptContainmentOutcomePins : uint8`  
_L36-40_
- reflection: `UENUM(BlueprintType)`
- L38 _public enumerator_ `Inside`
- L39 _public enumerator_ `Outside`

#### enum `EGeometryScriptLODType`  
`enum class EGeometryScriptLODType : uint8`  
_L47-65_
- reflection: `UENUM(BlueprintType)`
- desc: The Type of LOD in a Mesh Asset (ie a StaticMesh Asset)
- L50 _public enumerator_ `MaxAvailable` — The Maximum-quality available SourceModel LOD (HiResSourceModel if it is available, otherwise SourceModel LOD0)
- L52 _public enumerator_ `HiResSourceModel` — The HiRes SourceModel. LOD Index is ignored. HiResSourceModel is not available at Runtime.
- L57 _public enumerator_ `SourceModel` — The SourceModel mesh at a given LOD Index. Note that a StaticMesh Asset with Auto-Generated LODs may not have a valid SourceModel for every LOD Index SourceModel meshes are not available at Runtime.
- L64 _public enumerator_ `RenderData` — The Render mesh at at given LOD Index. A StaticMesh Asset derives its RenderData LODs from it's SourceModel LODs. RenderData LODs always exist for every valid LOD Index. However the RenderData LODs are not identical to SourceModel LODs, in particular they will be split at UV seams, Hard Normal creases, etc. RenderData LODs in a StaticMesh Asset are only available at Runtime if the bAllowCPUAccess flag was enabled on the Asset at Cook time.

#### enum `EGeometryScriptAxis`  
`enum class EGeometryScriptAxis : uint8`  
_L69-74_
- reflection: `UENUM(BlueprintType)`
- L71 _public enumerator_ `X = 0`
- L72 _public enumerator_ `Y = 1`
- L73 _public enumerator_ `Z = 2`

#### enum `EGeometryScriptCoordinateSpace`  
`enum class EGeometryScriptCoordinateSpace : uint8`  
_L78-82_
- reflection: `UENUM(BlueprintType)`
- L80 _public enumerator_ `Local = 0`
- L81 _public enumerator_ `World = 1`

#### struct `FGeometryScriptMeshReadLOD`  
`struct FGeometryScriptMeshReadLOD`  
_L86-95_
- reflection: `USTRUCT(BlueprintType)`
- L91 _public member_ `EGeometryScriptLODType LODType = EGeometryScriptLODType::MaxAvailable;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LOD)`
- L94 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LOD)`

#### struct `FGeometryScriptMeshWriteLOD`  
`struct FGeometryScriptMeshWriteLOD`  
_L99-108_
- reflection: `USTRUCT(BlueprintType)`
- L104 _public member_ `bool bWriteHiResSource = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LOD)`
- L107 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LOD)`

#### struct `FGeometryScriptSimpleCollision`  
`struct FGeometryScriptSimpleCollision`  
_L118-126_
- reflection: `USTRUCT(BlueprintType)`
- desc: Holds simple shapes that can be used for collision
- L124 _public member_ `FKAggregateGeom AggGeom;` — `UPROPERTY()`

#### struct `FGeometryScriptSphereCovering`  
`struct FGeometryScriptSphereCovering`  
_L130-147_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Sphere Covering"))`
- desc: A set of spheres used to represent a volume
- L134 _public member_ `TSharedPtr<UE::Geometry::FSphereCovering> Spheres;`
- L136 _public prototype_ `void Reset();`
- L139 _public function_ `bool operator==(const FGeometryScriptSphereCovering& Other) const` — Required by TStructOpsTypeTraits interface
- L143 _public function_ `bool operator!=(const FGeometryScriptSphereCovering& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptSphereCovering> : public TStructOpsTypeTraitsBase2<FGeometryScriptSphereCovering>`  
_L150-156_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptSphereCovering>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L153-155_

#### struct `FGeometryScriptSimpleCollisionTriangulationOptions`  
`struct FGeometryScriptSimpleCollisionTriangulationOptions`  
_L162-183_
- reflection: `USTRUCT(BlueprintType)`
- desc: Settings to control the triangulation of simple collision primitives -- used for conversion to mesh or convex hull geometry
- L169 _public member_ `int32 SphereStepsPerSide = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — When triangulating a sphere by deforming a cube to the sphere, number of vertices to use along each edge of the cube
- L173 _public member_ `int32 CapsuleHemisphereSteps = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — When triangulating a capsule's spherical endcaps, number of vertices to use on the arcs across the endcaps.
- L177 _public member_ `int32 CapsuleCircleSteps = 8;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — When triangulating a capsule, number of vertices to use for the circular cross-sections
- L181 _public member_ `bool bApproximateLevelSetsWithCubes = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to cheaply approximate level sets with cubes. Otherwise, will use marching cubes.

#### struct `FGeometryScriptTriangle`  
`struct FGeometryScriptTriangle`  
_L191-203_
- reflection: `USTRUCT(BlueprintType)`
- L196 _public member_ `FVector Vector0 = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L199 _public member_ `FVector Vector1 = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L202 _public member_ `FVector Vector2 = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptTrianglePoint`  
`struct FGeometryScriptTrianglePoint`  
_L207-222_
- reflection: `USTRUCT(BlueprintType)`
- L212 _public member_ `bool bValid = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L215 _public member_ `int TriangleID = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L218 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L221 _public member_ `FVector BaryCoords = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptUVTriangle`  
`struct FGeometryScriptUVTriangle`  
_L226-238_
- reflection: `USTRUCT(BlueprintType)`
- L231 _public member_ `FVector2D UV0 = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L234 _public member_ `FVector2D UV1 = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L237 _public member_ `FVector2D UV2 = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptColorFlags`  
`struct FGeometryScriptColorFlags`  
_L248-265_
- reflection: `USTRUCT(BlueprintType)`
- L253 _public member_ `bool bRed = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Color)`
- L256 _public member_ `bool bGreen = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Color)`
- L259 _public member_ `bool bBlue = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Color)`
- L262 _public member_ `bool bAlpha = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Color)`
- L264 _public function_ `bool AllSet() const`

#### struct `FGeometryScriptGroupLayer`  
`struct FGeometryScriptGroupLayer`  
_L278-289_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGeometryScriptGroupLayer identifies a PolyGroup Layer of a Mesh. The Default Layer always exists, Extended layers may or may not exist.
- L284 _public member_ `bool bDefaultLayer = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LOD)` — If true,the default/standard PolyGroup Layer is used
- L288 _public member_ `int ExtendedLayerIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LOD)` — Index of an extended PolyGroup Layer (which may or may not exist on any given Mesh)

#### struct `FGeometryScriptWeightMapHandle`  
`struct FGeometryScriptWeightMapHandle`  
_L297-310_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Weight Map Handle"))`
- L303 _public function_ `bool IsValid() const`
- L309 _public member_ `int WeightMapAttributeLayerIndex = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handle")`

#### enum `EGeometryScriptIndexType`  
`enum class EGeometryScriptIndexType : uint8`  
_L325-334_
- reflection: `UENUM(BlueprintType)`
- L328 _public enumerator_ `Any` — Index lists of Any type are compatible with any other index list type
- L329 _public enumerator_ `Triangle`
- L330 _public enumerator_ `Edge`
- L331 _public enumerator_ `Vertex`
- L332 _public enumerator_ `MaterialID`
- L333 _public enumerator_ `PolygroupID UMETA(DisplayName = "PolyGroup ID")`

#### struct `FGeometryScriptIndexList`  
`struct FGeometryScriptIndexList`  
_L337-370_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Index List"))`
- L342 _public member_ `EGeometryScriptIndexType IndexType = EGeometryScriptIndexType::Any;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IndexList)`
- L344 _public member_ `TSharedPtr<TArray<int>> List;`
- L346 _public function_ `void Reset(EGeometryScriptIndexType TargetIndexType, int32 Num = 0)`
- L356 _public function_ `bool IsCompatibleWith(EGeometryScriptIndexType OtherType) const`
- L362 _public function_ `bool operator==(const FGeometryScriptIndexList& Other) const` — Required by TStructOpsTypeTraits interface
- L366 _public function_ `bool operator!=(const FGeometryScriptIndexList& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptIndexList> : public TStructOpsTypeTraitsBase2<FGeometryScriptIndexList>`  
_L373-379_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptIndexList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L376-378_

#### struct `FGeometryScriptTriangleList`  
`struct FGeometryScriptTriangleList`  
_L383-407_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Triangle List"))`
- L387 _public member_ `TSharedPtr<TArray<FIntVector>> List;`
- L389 _public function_ `void Reset(int32 Num = 0)`
- L399 _public function_ `bool operator==(const FGeometryScriptTriangleList& Other) const` — Required by TStructOpsTypeTraits interface
- L403 _public function_ `bool operator!=(const FGeometryScriptTriangleList& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptTriangleList> : public TStructOpsTypeTraitsBase2<FGeometryScriptTriangleList>`  
_L410-416_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptTriangleList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L413-415_

#### struct `FGeometryScriptScalarList`  
`struct FGeometryScriptScalarList`  
_L420-444_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Scalar List"))`
- L424 _public member_ `TSharedPtr<TArray<double>> List;`
- L426 _public function_ `void Reset(int32 Num = 0)`
- L436 _public function_ `bool operator==(const FGeometryScriptScalarList& Other) const` — Required by TStructOpsTypeTraits interface
- L440 _public function_ `bool operator!=(const FGeometryScriptScalarList& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptScalarList> : public TStructOpsTypeTraitsBase2<FGeometryScriptScalarList>`  
_L447-453_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptScalarList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L450-452_

#### struct `FGeometryScriptVectorList`  
`struct FGeometryScriptVectorList`  
_L458-482_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Vector List"))`
- L462 _public member_ `TSharedPtr<TArray<FVector>> List;`
- L464 _public function_ `void Reset(int32 Num = 0)`
- L474 _public function_ `bool operator==(const FGeometryScriptVectorList& Other) const` — Required by TStructOpsTypeTraits interface
- L478 _public function_ `bool operator!=(const FGeometryScriptVectorList& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptVectorList> : public TStructOpsTypeTraitsBase2<FGeometryScriptVectorList>`  
_L485-491_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptVectorList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L488-490_

#### struct `FGeometryScriptUVList`  
`struct FGeometryScriptUVList`  
_L495-519_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "UV List"))`
- L499 _public member_ `TSharedPtr<TArray<FVector2D>> List;`
- L501 _public function_ `void Reset(int32 Num = 0)`
- L511 _public function_ `bool operator==(const FGeometryScriptUVList& Other) const` — Required by TStructOpsTypeTraits interface
- L515 _public function_ `bool operator!=(const FGeometryScriptUVList& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptUVList> : public TStructOpsTypeTraitsBase2<FGeometryScriptUVList>`  
_L522-528_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptUVList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L525-527_

#### struct `FGeometryScriptColorList`  
`struct FGeometryScriptColorList`  
_L533-557_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Color List"))`
- L537 _public member_ `TSharedPtr<TArray<FLinearColor>> List;`
- L539 _public function_ `void Reset(int32 Num = 0)`
- L549 _public function_ `bool operator==(const FGeometryScriptColorList& Other) const` — Required by TStructOpsTypeTraits interface
- L553 _public function_ `bool operator!=(const FGeometryScriptColorList& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptColorList> : public TStructOpsTypeTraitsBase2<FGeometryScriptColorList>`  
_L560-566_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptColorList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L563-565_

#### struct `FGeometryScriptPolyPath`  
`struct FGeometryScriptPolyPath`  
_L570-597_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "PolyPath"))`
- L574 _public member_ `TSharedPtr<TArray<FVector>> Path;`
- L577 _public member_ `bool bClosedLoop = false;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L579 _public function_ `void Reset(int32 Num = 0)`
- L589 _public function_ `bool operator==(const FGeometryScriptPolyPath& Other) const` — Required by TStructOpsTypeTraits interface
- L593 _public function_ `bool operator!=(const FGeometryScriptPolyPath& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptPolyPath> : public TStructOpsTypeTraitsBase2<FGeometryScriptPolyPath>`  
_L600-606_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptPolyPath>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L603-605_

#### struct `FGeometryScriptSimplePolygon`  
`struct FGeometryScriptSimplePolygon`  
_L610-634_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Simple Polygon"))`
- desc: A simple 2D Polygon with no holes
- L614 _public member_ `TSharedPtr<TArray<FVector2D>> Vertices;`
- L616 _public function_ `void Reset(int32 Num = 0)`
- L626 _public function_ `bool operator==(const FGeometryScriptSimplePolygon& Other) const` — Required by TStructOpsTypeTraits interface
- L630 _public function_ `bool operator!=(const FGeometryScriptSimplePolygon& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptSimplePolygon> : public TStructOpsTypeTraitsBase2<FGeometryScriptSimplePolygon>`  
_L637-643_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptSimplePolygon>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L640-642_

#### struct `FGeometryScriptGeneralPolygonList`  
`struct FGeometryScriptGeneralPolygonList`  
_L649-666_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "PolygonList"))`
- desc: A list of general polygons, which may have holes.
- L653 _public member_ `TSharedPtr<TArray<UE::Geometry::FGeneralPolygon2d>> Polygons;`
- L655 _public prototype_ `void Reset(int32 Num = 0);`
- L658 _public function_ `bool operator==(const FGeometryScriptGeneralPolygonList& Other) const` — Required by TStructOpsTypeTraits interface
- L662 _public function_ `bool operator!=(const FGeometryScriptGeneralPolygonList& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptGeneralPolygonList> : public TStructOpsTypeTraitsBase2<FGeometryScriptGeneralPolygonList>`  
_L669-675_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptGeneralPolygonList>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L672-674_

#### struct `FGeometryScriptDynamicMeshBVH`  
`struct FGeometryScriptDynamicMeshBVH`  
_L686-703_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "DynamicMesh BVH Cache"))`
- L691 _public member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> Spatial;`
- L692 _public member_ `TSharedPtr<UE::Geometry::TFastWindingTree<UE::Geometry::FDynamicMesh3>> FWNTree;`
- L695 _public function_ `bool operator==(const FGeometryScriptDynamicMeshBVH& Other) const` — Required by TStructOpsTypeTraits interface
- L699 _public function_ `bool operator!=(const FGeometryScriptDynamicMeshBVH& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryScriptDynamicMeshBVH> : public TStructOpsTypeTraitsBase2<FGeometryScriptDynamicMeshBVH>`  
_L706-712_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryScriptDynamicMeshBVH>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L709-711_

#### struct `FGeometryScriptRenderCaptureCamera`  
`struct FGeometryScriptRenderCaptureCamera`  
_L724-743_
- reflection: `USTRUCT(BlueprintType)`
- L730 _public member_ `int Resolution = 256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The pixel resolution of render capture photo set, this value is used for width and height
- L733 _public member_ `double FieldOfViewDegrees = 45.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L736 _public member_ `FVector ViewPosition = FVector::Zero();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L739 _public member_ `FVector ViewDirection = FVector::UnitX();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L742 _public member_ `double NearPlaneDist = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptRenderCaptureCamerasForBoxOptions`  
`struct FGeometryScriptRenderCaptureCamerasForBoxOptions`  
_L748-786_
- reflection: `USTRUCT(BlueprintType)`
- L754 _public member_ `int Resolution = 256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The pixel resolution of render capture photos, this value is used for width and height
- L757 _public member_ `double FieldOfViewDegrees = 45.;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L761 _public member_ `bool bViewFromBoxFaces = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Enable 6 directions corresponding to views from box face centers to the box center
- L765 _public member_ `bool bViewFromUpperCorners = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Enable 4 directions corresponding to views from box upper corners to the box center
- L769 _public member_ `bool bViewFromLowerCorners = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Enable 4 directions corresponding to views from box lower corners to the box center
- L773 _public member_ `bool bViewFromUpperEdges = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Enable 4 directions corresponding to views from box upper edges centers to the box center
- L777 _public member_ `bool bViewFromLowerEdges = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Enable 4 directions corresponding to views from box lower edges centers to the box center
- L781 _public member_ `bool bViewFromSideEdges = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Enable 4 directions corresponding to views from box side edges centers to the box center
- L785 _public member_ `TArray<FVector> ExtraViewFromPositions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Extra positions from which to deduce view directions on the box center (located at (0,0,0))

#### enum `EGeometryScriptDebugMessageType`  
`enum class EGeometryScriptDebugMessageType : uint8`  
_L799-803_
- reflection: `UENUM(BlueprintType)`
- L801 _public enumerator_ `ErrorMessage`
- L802 _public enumerator_ `WarningMessage`

#### enum `EGeometryScriptErrorType`  
`enum class EGeometryScriptErrorType : uint8`  
_L807-814_
- reflection: `UENUM(BlueprintType)`
- L810 _public enumerator_ `NoError` — warning: must only append members!
- L811 _public enumerator_ `UnknownError`
- L812 _public enumerator_ `InvalidInputs`
- L813 _public enumerator_ `OperationFailed`

#### struct `FGeometryScriptDebugMessage`  
`struct FGeometryScriptDebugMessage`  
_L818-830_
- reflection: `USTRUCT(BlueprintType)`
- L823 _public member_ `EGeometryScriptDebugMessageType MessageType = EGeometryScriptDebugMessageType::ErrorMessage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L826 _public member_ `EGeometryScriptErrorType ErrorType = EGeometryScriptErrorType::UnknownError;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L829 _public member_ `FText Message = FText();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### class `UGeometryScriptDebug`  
`class UGeometryScriptDebug : public UObject`  
_L834-846_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (TestMetadata))`
- inherits: `UObject`
- L839 _public member_ `TArray<FGeometryScriptDebugMessage> Messages;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Messages)`
- L842 _public function_ `void Append(const FGeometryScriptDebugMessage& MessageIn)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`
- L12 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L13 _prototype_ `PREDECLARE_GEOMETRY(template<typename MeshType> class TMeshAABBTree3);`
- L14 _prototype_ `PREDECLARE_GEOMETRY(template<typename MeshType> class TFastWindingTree);`
- L15 _prototype_ `PREDECLARE_GEOMETRY(typedef TMeshAABBTree3<FDynamicMesh3> FDynamicMeshAABBTree3);`
- L16 _prototype_ `PREDECLARE_GEOMETRY(template<typename RealType> class TGeneralPolygon2);`
- L17 _prototype_ `PREDECLARE_GEOMETRY(typedef TGeneralPolygon2<double> FGeneralPolygon2d);`
- L18 _prototype_ `PREDECLARE_GEOMETRY(class FSphereCovering);`
- L154 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncce478890103`)
- L377 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncce478890203`)
- L414 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncce478890303`)
- L451 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncce478890403`)
- L489 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncce478890503`)
- L526 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncce478890603`)
- L564 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncce478890703`)
- L604 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncce478890803`)
- L641 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncce478890903`)
- L673 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncce478890a03`)
- L710 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anoncce478890b03`)
- L850 _namespace_ `namespace UE`
- L852 _namespace_ `namespace Geometry` (scope `UE`)
- L854 _prototype_ `FGeometryScriptDebugMessage MakeScriptError(EGeometryScriptErrorType ErrorTypeIn, const FText& MessageIn);` (scope `UE::Geometry`)
- L855 _prototype_ `FGeometryScriptDebugMessage MakeScriptWarning(EGeometryScriptErrorType WarningTypeIn, const FText& MessageIn);` (scope `UE::Geometry`)
- L858 _prototype_ `void AppendError(UGeometryScriptDebug* Debug, EGeometryScriptErrorType ErrorTypeIn, const FText& MessageIn);` (scope `UE::Geometry`)
- L859 _prototype_ `void AppendWarning(UGeometryScriptDebug* Debug, EGeometryScriptErrorType WarningTypeIn, const FText& MessageIn);` (scope `UE::Geometry`)
- L866 _prototype_ `void AppendError(TArray<FGeometryScriptDebugMessage>* DebugMessages, EGeometryScriptErrorType ErrorTypeIn, const FText& MessageIn);` (scope `UE::Geometry`) — These variants of AppendError/Warning are for direct write to a debug message array. This may be useful in cases where a function is async and needs to accumulate debug messages for later collation on a game thread.
- L867 _prototype_ `void AppendWarning(TArray<FGeometryScriptDebugMessage>* DebugMessages, EGeometryScriptErrorType WarningTypeIn, const FText& MessageIn);` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/ListUtilityFunctions.h` (Public)


#### class `UGeometryScriptLibrary_ListUtilityFunctions`  
`class UGeometryScriptLibrary_ListUtilityFunctions : public UBlueprintFunctionLibrary`  
_L16-375_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_List"))`
- inherits: `UBlueprintFunctionLibrary`
- L24 _public prototype_ `static int GetIndexListLength(FGeometryScriptIndexList IndexList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the number of Items in Index List.
- L31 _public prototype_ `static int GetIndexListLastIndex(FGeometryScriptIndexList IndexList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the index of the last element in the Index List. Note, the value -1 will be returned if the list is empty or invalid.
- L38 _public prototype_ `static int GetIndexListItem(FGeometryScriptIndexList IndexList, int Index, bool& bIsValidIndex);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the item associated with Index in the Index List. If Index is not valid for this Index List the value -1 will be returned and bIsValidIndex will be set to false.
- L45 _public prototype_ `static void SetIndexListItem(UPARAM(ref) FGeometryScriptIndexList& IndexList, int Index, int NewValue, bool& bIsValidIndex);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Updates the value associated with Index in the Index List. If the Index is invalid, the operation will fail and in this case bValidIndex will be set to false on return.
- L51 _public prototype_ `static void ConvertIndexListToArray(FGeometryScriptIndexList IndexList, TArray<int>& IndexArray);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Populates Index Array with the integer values stored in the Index List.
- L57 _public prototype_ `static void ConvertArrayToIndexList(const TArray<int>& IndexArray, FGeometryScriptIndexList& IndexList, EGeometryScriptIndexType IndexType = EGeometryScriptIndexType::Any);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils")` — Populates Index List of the specified Index Type from the integer values stored in the Index Array.
- L63 _public prototype_ `static void DuplicateIndexList(FGeometryScriptIndexList IndexList, FGeometryScriptIndexList& DuplicateList);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Updates Duplicate List to be identical to Index List.
- L69 _public prototype_ `static void ClearIndexList(UPARAM(ref) FGeometryScriptIndexList& IndexList, int ClearValue = 0);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Set each value in Index List to the given Clear Value.
- L75 _public prototype_ `static int GetTriangleListLength(FGeometryScriptTriangleList TriangleList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the number of Triangles in the  Triangle list.
- L82 _public prototype_ `static int GetTriangleListLastTriangle(FGeometryScriptTriangleList TriangleList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the index of the last element in the Triangle List. If the Triangle List is empty or invalid, the value 0 will be returned.
- L89 _public prototype_ `static FIntVector GetTriangleListItem(FGeometryScriptTriangleList TriangleList, int Triangle, bool& bIsValidTriangle);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the integer triplet associated with the index Triangle in the Triangle  List. If Triangle is not valid for this Triangle List, the triplet (-1, -1, -1) will be returned and bIsValidIndex set to false.
- L101 _public prototype_ `static void ConvertArrayToTriangleList(UPARAM(DisplayName = "Triangle Tuple Array") const TArray<FIntVector>& TriangleArray, FGeometryScriptTriangle` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils")` — Converts a Triangle Array of integer triplets to a Triangle List.
- L108 _public prototype_ `static int GetScalarListLength(FGeometryScriptScalarList ScalarList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the number of items in the Scalar List.
- L115 _public prototype_ `static int GetScalarListLastIndex(FGeometryScriptScalarList ScalarList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the index of the last Scalar in Scalar List. If Scalar List is empty or invalid, the value -1 will be returned
- L122 _public prototype_ `static double GetScalarListItem(FGeometryScriptScalarList ScalarList, int Index, bool& bIsValidIndex);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the Scalar value associated with Index in Scalar List. If the Index is not valid for this Scalar List, the value 0.0 will be returned and bIsValidIndex set to false.
- L129 _public prototype_ `static void SetScalarListItem(UPARAM(ref) FGeometryScriptScalarList& ScalarList, int Index, double NewValue, bool& bIsValidIndex);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Updates the value associated with Index in the Scalar List. If the Index is invalid, the operation will fail and bValidIndex will be set to false.
- L135 _public prototype_ `static void ConvertScalarListToArray(FGeometryScriptScalarList ScalarList, TArray<double>& ScalarArray);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Converts a Scalar List to an Scalar Array (an array of doubles).
- L141 _public prototype_ `static void ConvertArrayToScalarList(UPARAM(DisplayName = "Scalar Array") const TArray<double>& VectorArray, FGeometryScriptScalarList&` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils")` — Converts an array of doubles (Scalar Array) to Scalar List.
- L147 _public prototype_ `static void DuplicateScalarList(FGeometryScriptScalarList ScalarList, FGeometryScriptScalarList& DuplicateList);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Copies the contents of Scalar List into Duplicate List.
- L153 _public prototype_ `static void ClearScalarList(UPARAM(ref) FGeometryScriptScalarList& ScalarList, double ClearValue = 0.0);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Resets all the items in the Scalar List to the Clear Value.
- L161 _public prototype_ `static int GetVectorListLength(FGeometryScriptVectorList VectorList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the number of items in the Vector List.
- L168 _public prototype_ `static int GetVectorListLastIndex(FGeometryScriptVectorList VectorList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the index of the last item in the Vector List. If Vector List is empty or invalid, the value -1 will be returned.
- L175 _public prototype_ `static FVector GetVectorListItem(FGeometryScriptVectorList VectorList, int Index, bool& bIsValidIndex);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the FVector stored in the VectorList at the specified location. if the Index is not valid for this Vector List, the Zero Vector will be returned and bIsValidIndex set to false.
- L182 _public prototype_ `static void SetVectorListItem(UPARAM(ref) FGeometryScriptVectorList& VectorList, int Index, FVector NewValue, bool& bIsValidIndex);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Updates the value of the FVector stored in the Vector List at the specified location. If the Index is invalid, the operation will fail and bValidIndex will be set to false.
- L188 _public prototype_ `static void ConvertVectorListToArray(FGeometryScriptVectorList VectorList, TArray<FVector>& VectorArray);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Converts Vector List to an array of FVectors (Vector Array).
- L194 _public prototype_ `static void ConvertArrayToVectorList(const TArray<FVector>& VectorArray, FGeometryScriptVectorList& VectorList);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils")` — Converts an Array of FVectors (Vector Array) to Vector List.
- L200 _public prototype_ `static void DuplicateVectorList(FGeometryScriptVectorList VectorList, FGeometryScriptVectorList& DuplicateList);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Copies the contents of Vector List into Duplicate Vector List.
- L206 _public prototype_ `static void ClearVectorList(UPARAM(ref) FGeometryScriptVectorList& VectorList, FVector ClearValue = FVector::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Resets all the items in the Vector List to the Clear Value.
- L214 _public prototype_ `static int GetUVListLength(FGeometryScriptUVList UVList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the number of items in the UV List.
- L221 _public prototype_ `static int GetUVListLastIndex(FGeometryScriptUVList UVList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the index of the last item in the UV List. If UV List is empty or invalid, the value -1 will be returned.
- L228 _public prototype_ `static FVector2D GetUVListItem(FGeometryScriptUVList UVList, int Index, bool& bIsValidIndex);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the FVector2D stored in the UV List at the specified location. If the Index is not valid for this UV List, the Zero Vector will be returned and bIsValidIndex set to false.
- L235 _public prototype_ `static void SetUVListItem(UPARAM(ref) FGeometryScriptUVList& UVList, int Index, FVector2D NewUV, bool& bIsValidIndex);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Updates the value of the FVector2D stored in the UV List at the specified location. If the Index is invalid, the operation will fail and bValidIndex will be set to false on return.
- L241 _public prototype_ `static void ConvertUVListToArray(FGeometryScriptUVList UVList, TArray<FVector2D>& UVArray);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Converts a UV List to an array of FVector2Ds (UV Array).
- L247 _public prototype_ `static void ConvertArrayToUVList(const TArray<FVector2D>& UVArray, FGeometryScriptUVList& UVList);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils")` — Converts an array of FVector2D (UV Array) to UV List.
- L253 _public prototype_ `static void DuplicateUVList(FGeometryScriptUVList UVList, FGeometryScriptUVList& DuplicateList);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Duplicates the contents of UV List into Duplicate List.
- L259 _public prototype_ `static void ClearUVList(UPARAM(ref) FGeometryScriptUVList& UVList, FVector2D ClearUV);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Resets all the items in the Vector List to the given Clear UV value.
- L266 _public prototype_ `static int GetColorListLength(FGeometryScriptColorList ColorList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the number of items in the Color List.
- L273 _public prototype_ `static int GetColorListLastIndex(FGeometryScriptColorList ColorList);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the index of the last item in the Color List. If Color List is empty or invalid, the value -1 will be returned.
- L280 _public prototype_ `static FLinearColor GetColorListItem(FGeometryScriptColorList ColorList, int Index, bool& bIsValidIndex);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Returns the FLinearColor stored in the Color List at the specified location. If the Index is not valid for this Color List, FLinearColor::White will be returned and bIsValidIndex set to false.
- L287 _public prototype_ `static void SetColorListItem(UPARAM(ref) FGeometryScriptColorList& ColorList, int Index, FLinearColor NewColor, bool& bIsValidIndex);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Updates the value of the FLinearColor stored in the Color List at the specified location. If the Index is invalid, the operation will fail and bValidIndex will be set to false.
- L293 _public prototype_ `static void ConvertColorListToArray(FGeometryScriptColorList ColorList, TArray<FLinearColor>& ColorArray);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Converts the Color List to an array of FLinearColor (Color Array).
- L299 _public prototype_ `static void ConvertArrayToColorList(const TArray<FLinearColor>& ColorArray, FGeometryScriptColorList& ColorList);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils")` — Converts an array of FLinearColor (Color Array) to a Color List.
- L305 _public prototype_ `static void DuplicateColorList(FGeometryScriptColorList ColorList, FGeometryScriptColorList& DuplicateList);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Duplicates the contents of Color List into Duplicate List.
- L311 _public prototype_ `static void ClearColorList(UPARAM(ref) FGeometryScriptColorList& ColorList, FLinearColor ClearColor);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Resets all the items in the Color List to the specified Clear Color.
- L317 _public prototype_ `static void ExtractColorListChannel(FGeometryScriptColorList ColorList, FGeometryScriptScalarList& ScalarList, int32 ChannelIndex = 0);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Populates a Scalar List with values that correspond to the 0, 1, 2, or 3 channel of a Color List.
- L323 _public prototype_ `static void ExtractColorListChannels(FGeometryScriptColorList ColorList, FGeometryScriptVectorList& VectorList, int32 XChannelIndex = 0, int32 YChannelIndex = 1, int32 ZChannelIndex = 2);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta=(ScriptMethod))` — Populates a Vector List from a Color List. The channels in the Color List are mapped to vector components by means of X Channel Index, Y Channel Index, and Z Channel Index.
- L329 _public prototype_ `static void ExtractUVListComponent(FGeometryScriptUVList UVList, FGeometryScriptScalarList& ScalarList, int32 ComponentIndex = 0);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta = (ScriptMethod))` — Populates a Scalar List with values that correspond to the U or V component of a UV List.
- L335 _public prototype_ `static void ExtractVectorListComponent(FGeometryScriptVectorList VectorList, FGeometryScriptScalarList& ScalarList, int32 ComponentIndex = 0);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta = (ScriptMethod))` — Populates a Scalar List with values that correspond to the X Y or Z component of a Vector List.
- L341 _public prototype_ `static void ExtractVectorListComponentsAsUVs(FGeometryScriptVectorList VectorList, FGeometryScriptUVList& UVList, int32 UComponentIndex = 0, int32 VComponentIndex = 1);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta = (ScriptMethod, DisplayName = "Extract Vector List Components As UVs"))` — Populates a UV List with values that correspond to the X Y or Z components of a Vector List.
- L346 _public prototype_ `static void SetColorListChannelFromScalars(UPARAM(ref) FGeometryScriptColorList& ColorList, FGeometryScriptScalarList ScalarList, int32 ColorChannel = 0, FLinearColor DefaultColor = FLinearColor::Black);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta = (ScriptMethod))` — Sets the specified Color Channel of the Color List from the corresponding values in the Scalar List, resizing Color List as needed
- L351 _public prototype_ `static void SetColorListChannelsFromUVs(UPARAM(ref) FGeometryScriptColorList& ColorList, FGeometryScriptUVList UVList, int32 UToChannelIndex = 0, int32 VToChannelIndex = 1, FLinearColor DefaultColor = FLinearColor::Black);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta = (ScriptMethod, DisplayName = "Set Color List Channels From UVs"))` — Sets the specified Color Channels of the Color List from the corresponding values in the UV List, resizing Color List as needed
- L356 _public prototype_ `static void SetColorListChannelsFromVectors(UPARAM(ref) FGeometryScriptColorList& ColorList, FGeometryScriptVectorList VectorList, int32 XToChannelIndex = 0, int32 YToChannelIndex = 1, int32 ZToChannelIndex = 2, FLinearColor DefaultColor = FLinearColor::Black);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta = (ScriptMethod))` — Sets the specified Color Channels of the Color List from the corresponding values in the Vector List, resizing Color List as needed
- L361 _public prototype_ `static void SetUVListComponentFromScalars(UPARAM(ref) FGeometryScriptUVList& UVList, FGeometryScriptScalarList ScalarList, int32 UVComponent = 0, FVector2D DefaultUV = FVector2D::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta = (ScriptMethod))` — Sets the specified Component of the UV List from the corresponding values in the Scalar List, resizing UV List as needed
- L366 _public prototype_ `static void SetVectorListComponentFromScalars(UPARAM(ref) FGeometryScriptVectorList& VectorList, FGeometryScriptScalarList ScalarList, int32 VectorComponent = 0, FVector DefaultVector = FVector::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta = (ScriptMethod))` — Sets the specified Component of the Vector List from the corresponding values in the Scalar List, resizing Vector List as needed
- L371 _public prototype_ `static void SetVectorListComponentsFromUVs(UPARAM(ref) FGeometryScriptVectorList& VectorList, FGeometryScriptUVList UVList, int32 UToVectorComponent = 0, int32 VToVectorComponent = 1, FVector DefaultVector = FVector::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|ListUtils", meta = (ScriptMethod, DisplayName = "Set Vector List Components From UVs"))` — Sets the specified Components of the Vector List from the corresponding values in the UV List, resizing Vector List as needed

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshAssetFunctions.h` (Public)


#### enum `EGeometryScriptBoneHierarchyMismatchHandling`  
`enum class EGeometryScriptBoneHierarchyMismatchHandling : uint8`  
_L21-40_
- reflection: `UENUM(BlueprintType)`
- desc: A set of options on how to handle the situation where the bone hierarchy on a skeletal geometry does not match the reference skeleton on the skeletal asset being copied to. Does not apply when copying geometry to static meshes.
- L25 _public enumerator_ `DoNothing = 0` — Do nothing to fix the mismatch. This is dangerous and should not be used lightly. The reference skeleton and the geometry's bone hierarchy may not match, resulting in visual glitches during rendering.
- L30 _public enumerator_ `RemapGeometryToReferenceSkeleton = 1` — Remap the bone bindings and bone hierarchy on the geometry to match the reference skeleton. If no bone information is present then all vertices are mapped to the root bone.
- L39 _public enumerator_ `CreateNewReferenceSkeleton = 2` — Generate a new reference skeleton on the skeletal mesh asset that matches the bone hierarchy of the geometry being copied in. Note that virtual bones are not retained from the old reference skeleton. If no bone information is present, then a ref skeleton is created, with a single root bone at the origin, and all vertices bound to that root bone. No attempt is made to ensure that this reference skeleton is compatible with the skeleton object. If this is a requirement, then it is the user's responsibility to ensure they are.

#### enum `EGeometryScriptGenerateLightmapUVOptions`  
`enum class EGeometryScriptGenerateLightmapUVOptions : uint8`  
_L44-52_
- reflection: `UENUM(BlueprintType)`
- desc: Options to control whether lightmap UVs are generated
- L47 _public enumerator_ `MatchTargetLODSetting UMETA(DisplayName = "Match Target LOD Setting")` — Match the lightmap UV generation setting of the target LOD, if it exists. For a new LOD, match LOD 0.
- L49 _public enumerator_ `GenerateLightmapUVs UMETA(DisplayName = "Generate Lightmap UVs")` — Generate lightmap UVs
- L51 _public enumerator_ `DoNotGenerateLightmapUVs UMETA(DisplayName = "Do Not Generate Lightmap UVs")` — Do not generate lightmap UVs

#### struct `FGeometryScriptCopyMeshFromAssetOptions`  
`struct FGeometryScriptCopyMeshFromAssetOptions`  
_L56-75_
- reflection: `USTRUCT(BlueprintType)`
- L62 _public member_ `bool bApplyBuildSettings = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to apply Build Settings during the mesh copy.
- L66 _public member_ `bool bRequestTangents = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to request tangents on the copied mesh. If tangents are not requested, tangent-related build settings will also be ignored.
- L70 _public member_ `bool bIgnoreRemoveDegenerates = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to ignore the 'remove degenerates' option from Build Settings. Note: Only applies if 'Apply Build Settings' is enabled.
- L74 _public member_ `bool bUseBuildScale = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to scale the copied mesh by the Build Setting's 'Build Scale'. Note: This is considered separately from the 'Apply Build Settings' option.

#### struct `FGeometryScriptNaniteOptions`  
`struct FGeometryScriptNaniteOptions`  
_L81-96_
- reflection: `USTRUCT(BlueprintType)`
- desc: Configuration settings for Nanite Rendering on StaticMesh Assets
- L87 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Set Nanite to Enabled/Disabled
- L91 _public member_ `float FallbackPercentTriangles = 100.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Percentage of triangles to maintain in Fallback Mesh used when Nanite is unavailable
- L95 _public member_ `float FallbackRelativeError = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Relative Error to maintain in Fallback Mesh used when Nanite is unavailable. Overrides FallbackPercentTriangles. Set to 0 to only use FallbackPercentTriangles (default).

#### enum `ECopyMeshToAssetUseNewMaterialsOptions`  
`enum class ECopyMeshToAssetUseNewMaterialsOptions : uint8`  
_L100-106_
- reflection: `UENUM(BlueprintType)`
- desc: Options for how to use the NewMaterials array when copying materials to a mesh asset
- L103 _public enumerator_ `ReplaceAssetMaterials = 0` — Fully replace asset materials list with the provided set
- L105 _public enumerator_ `SetLODMaterials = 1 UMETA(DisplayName = "Set LOD Materials")` — Use the provided new materials as the material for the newly-set LOD, only adding asset materials as-needed

#### struct `FGeometryScriptCopyMeshToAssetOptions`  
`struct FGeometryScriptCopyMeshToAssetOptions`  
_L111-186_
- reflection: `USTRUCT(BlueprintType)`
- L116 _public member_ `bool bEnableRecomputeNormals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L119 _public member_ `bool bEnableRecomputeTangents = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L122 _public member_ `bool bEnableRemoveDegenerates = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L128 _public member_ `EGeometryScriptBoneHierarchyMismatchHandling BoneHierarchyMismatchHandling = EGeometryScriptBoneHierarchyMismatchHandling::DoNothing;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — An option that specifies, for skeletal mesh assets, how mismatches between the existing reference skeleton on the asset, and the bone hierarchy stored on the geometry are handled. By default, no attempt is made to resolve this mismatch.
- L134 _public member_ `bool bRemapBoneIndicesToMatchAsset = false;` — `UE_DEPRECATED(5.6, "Deprecated. Use BoneHierarchyMismatchHandling instead.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = Deprecated)` — Deprecated. Use BoneHierarchyMismatchHandling instead.
- L139 _public member_ `bool bUseOriginalVertexOrder = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Use the original vertex order found in the source data. This is useful if the inbound mesh was originally non-manifold, and needs to keep the non-manifold structure when re-created.
- L143 _public member_ `bool bUseBuildScale = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to use the build scale on the target asset. If enabled, the inverse scale will be applied when saving to the asset, and the BuildScale will be preserved. Otherwise, BuildScale will be set to 1.0 on the asset BuildSettings.
- L147 _public member_ `bool bReplaceMaterials = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta=(DisplayName = "Use New Materials"))` — Whether to update the materials on the asset with those in the New Materials array
- L151 _public member_ `ECopyMeshToAssetUseNewMaterialsOptions NewMaterialUsage = ECopyMeshToAssetUseNewMaterialsOptions::ReplaceAssetMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If using New Materials, whether to use them as a full replacement of all asset materials, or just to update the target LOD
- L155 _public member_ `TArray<TObjectPtr<UMaterialInterface>> NewMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — New materials to set if Replace Materials is enabled. Ignored otherwise.
- L159 _public member_ `TArray<FName> NewMaterialSlotNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Optional slot names for the New Materials. Ignored if not the same length as the New Materials array.
- L163 _public member_ `bool bCleanAssignedMaterials = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to apply a cleanup pass to assigned materials -- fixing invalid material assignments
- L167 _public member_ `EGeometryScriptGenerateLightmapUVOptions GenerateLightmapUVs = EGeometryScriptGenerateLightmapUVOptions::MatchTargetLODSetting;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to generate lightmap UVs
- L171 _public member_ `bool bApplyNaniteSettings = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If enabled, NaniteSettings will be applied to the target Asset if possible
- L175 _public member_ `FGeometryScriptNaniteOptions NaniteSettings = FGeometryScriptNaniteOptions();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Deprecated, AdvancedDisplay, meta=(DisplayName = "DEPRECATED NANITE SETTING"))` — Replaced FGeometryScriptNaniteOptions with usage of Engine FMeshNaniteSettings
- L179 _public member_ `FMeshNaniteSettings NewNaniteSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (DisplayName = "Nanite Settings"))` — Nanite Settings applied to the target Asset, if bApplyNaniteSettings = true
- L182 _public member_ `bool bEmitTransaction = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L185 _public member_ `bool bDeferMeshPostEditChange = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptCopyMorphTargetToAssetOptions`  
`struct FGeometryScriptCopyMorphTargetToAssetOptions`  
_L189-206_
- reflection: `USTRUCT(BlueprintType)`
- L196 _public member_ `bool bOverwriteExistingTarget = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true and the morph target with the given name exists, it will be overwritten. If false, will abort and print a console error.
- L199 _public member_ `bool bEmitTransaction = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L202 _public member_ `bool bDeferMeshPostEditChange = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L205 _public member_ `bool bCopyNormals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptCopySkinWeightProfileToAssetOptions`  
`struct FGeometryScriptCopySkinWeightProfileToAssetOptions`  
_L210-224_
- reflection: `USTRUCT(BlueprintType)`
- L217 _public member_ `bool bOverwriteExistingProfile = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true and a skin weight profile with the given name exists, it will be overwritten. If false, will abort and print a console error.
- L220 _public member_ `bool bEmitTransaction = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L223 _public member_ `bool bDeferMeshPostEditChange = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### class `UGeometryScriptLibrary_StaticMeshFunctions`  
`class UGeometryScriptLibrary_StaticMeshFunctions : public UBlueprintFunctionLibrary`  
_L231-469_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_AssetUtils"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Although the class name indicates StaticMeshFunctions, that was a naming mistake that is difficult to correct. This class is intended to serve as a generic asset utils function library. The naming issue is only visible at the C++ level. It is not visible in Python or BP.
- L242 _public prototype_ `CheckStaticMeshHasAvailableLOD( UStaticMesh* StaticMeshAsset, FGeometryScriptMeshReadLOD RequestedLOD, EGeometryScriptSearchOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);`
- L253 _public prototype_ `GetNumStaticMeshLODsOfType( UStaticMesh* StaticMeshAsset, EGeometryScriptLODType LODType = EGeometryScriptLODType::SourceModel);`
- L266 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* CopyMeshFromStaticMeshV2( UStaticMesh* FromStaticMeshAsset, UDynamicMesh* ToDynamicMesh, FGeometryScriptCopyMeshFromAssetOptions AssetOptions, FGeometryScriptMeshReadLOD RequestedLOD, EGeometryScriptOutcomePins& Outcome, bool bUseSectionMaterials = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|StaticMesh", meta = (HidePin = "Debug", DisplayName = "Copy Mesh From Static Mesh", ExpandEnumAsExecs = "Outcome"))`
- L282 _public function_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* CopyMeshFromStaticMesh( UStaticMesh* FromStaticMeshAsset, UDynamicMesh* ToDynamicMesh, FGeometryScriptCopyMeshFromAssetOptions AssetOptions, FGeometryScriptMeshReadLOD RequestedLOD, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr)` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|StaticMesh", meta = (HidePin = "Debug", DisplayName = "Copy Mesh From Static Mesh with Section Materials", ExpandEnumAsExecs = "Outcome"))` — Extracts a Dynamic Mesh from a Static Mesh Asset, using section indices for the material IDs -- use GetSectionMaterialListFromStaticMesh to get the corresponding materials. Note that the LOD Index in RequestedLOD will be silently clamped to the available number of LODs (SourceModel or RenderData)
- L300 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* CopyMeshToStaticMesh( UDynamicMesh* FromDynamicMesh, UStaticMesh* ToStaticMeshAsset, FGeometryScriptCopyMeshToAssetOptions Options, FGeometryScriptMeshWriteLOD TargetLOD, EGeometryScriptOutcomePins& Outcome, bool bUseSectionMaterials = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|StaticMesh", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Updates a Static Mesh Asset with new geometry converted from a Dynamic Mesh @param bUseSectionMaterials Whether to assume Dynamic Mesh material IDs are section indices in the target Static Mesh. Should match the value passed to CopyMeshFromStaticMesh. Has no effect if replacing the asset materials.
- L312 _public function_ `static UDynamicMesh* CopyMeshToStaticMesh( UDynamicMesh* FromDynamicMesh, UStaticMesh* ToStaticMeshAsset, FGeometryScriptCopyMeshToAssetOptions Options, FGeometryScriptMeshWriteLOD TargetLOD, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug)` — `UE_DEPRECATED(5.5, "Use the version of this function with a bUseSectionMaterials parameter")`
- L337 _public prototype_ `GetSectionMaterialListFromStaticMesh( UStaticMesh* FromStaticMeshAsset, FGeometryScriptMeshReadLOD RequestedLOD, TArray<UMaterialInterface*>& MaterialList, TArray<int32>& MaterialIndex, TArray<FName>& MaterialSlotNames, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);`
- L357 _public prototype_ `GetLODMaterialListFromSkeletalMesh( USkeletalMesh* FromSkeletalMeshAsset, FGeometryScriptMeshReadLOD RequestedLOD, TArray<UMaterialInterface*>& MaterialList, TArray<int32>& MaterialIndex, TArray<FName>& MaterialSlotNames, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);`
- L372 _public prototype_ `GetMaterialListFromStaticMesh(const UStaticMesh* FromStaticMeshAsset, TArray<UMaterialInterface*>& MaterialList, TArray<FName>& MaterialSlotNames, UGeometryScriptDebug* Debug = nullptr);`
- L383 _public prototype_ `GetMaterialListFromSkeletalMesh(const USkeletalMesh* FromSkeletalMeshAsset, TArray<UMaterialInterface*>& MaterialList, TArray<FName>& MaterialSlotNames, UGeometryScriptDebug* Debug = nullptr);`
- L392 _public prototype_ `static void ConvertMaterialMapToMaterialList(const TMap<FName, UMaterialInterface*>& MaterialMap, TArray<UMaterialInterface*>& MaterialList, TArray<FName>& MaterialSlotNames);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials")` — Converts material map to a material list and a slot names list. Null materials will be kept in the list, and the list will have the same number of elements as the map.
- L402 _public prototype_ `static UPARAM(DisplayName = "Material Map") TMap<FName, UMaterialInterface*> ConvertMaterialListToMaterialMap(const TArray<UMaterialInterface*>& MaterialList, const TArray<FName>& MaterialSlotNames);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials")` — Converts material list and slot names list to material map, which is the format expected by CreateNewSkeletalMeshAssetFromMesh. Material List and Material Slot Names should have the same length. However, if there are fewer slot names than materials, slot names will be auto-generated (as '[Name of material]_[Index]', or 'Material_[Index]' for null materials)
- L409 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* CopyMeshFromSkeletalMesh( USkeletalMesh* FromSkeletalMeshAsset, UDynamicMesh* ToDynamicMesh, FGeometryScriptCopyMeshFromAssetOptions AssetOptions, FGeometryScriptMeshReadLOD RequestedLOD, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SkeletalMesh", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Extracts a Dynamic Mesh from a Skeletal Mesh Asset.
- L422 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* CopyMeshToSkeletalMesh( UDynamicMesh* FromDynamicMesh, USkeletalMesh* ToSkeletalMeshAsset, FGeometryScriptCopyMeshToAssetOptions Options, FGeometryScriptMeshWriteLOD TargetLOD, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SkeletalMesh", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Updates a Skeletal Mesh Asset with new geometry and bone weights data from a Dynamic Mesh.
- L440 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* CopyMorphTargetToSkeletalMesh( UDynamicMesh* FromMorphTarget, USkeletalMesh* ToSkeletalMeshAsset, FName MorphTargetName, FGeometryScriptCopyMorphTargetToAssetOptions Options, FGeometryScriptMeshWriteLOD TargetLOD, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SkeletalMesh", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Add a Dynamic Mesh morph target to a Skeletal Mesh Asset. @param FromMorphTarget the dynamic mesh representing the geometry of the morph target @param ToSkeletalMeshAsset the asset we are writing the morph target into @param MorphTargetName the name of the morph target as it will appear in the UI
- L459 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* CopySkinWeightProfileToSkeletalMesh( UDynamicMesh* FromDynamicMesh, USkeletalMesh* ToSkeletalMeshAsset, FName TargetProfileName, FName SourceProfileName, FGeometryScriptCopySkinWeightProfileToAssetOptions Options, FGeometryScriptMeshWriteLOD TargetLOD, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SkeletalMesh", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Add a Dynamic Mesh skin weight profile to a Skeletal Mesh Asset. @param FromDynamicMesh the dynamic mesh representing the geometry of the morph target @param ToSkeletalMeshAsset the asset we are writing the morph target into @param TargetProfileName the name of the skin weight profile as it will appear in the UI. Leave blank for the default profile. @param SourceProfileName The name of the skin weight profile to copy from the dynamic mesh. Leave blank for the default profile.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshBakeFunctions.h` (Public)


#### enum `EGeometryScriptBakeResolution`  
`enum class EGeometryScriptBakeResolution : uint8`  
_L15-27_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Resolution16 UMETA(DisplayName = "16 x 16")`
- L18 _public enumerator_ `Resolution32 UMETA(DisplayName = "32 x 32")`
- L19 _public enumerator_ `Resolution64 UMETA(DisplayName = "64 x 64")`
- L20 _public enumerator_ `Resolution128 UMETA(DisplayName = "128 x 128")`
- L21 _public enumerator_ `Resolution256 UMETA(DisplayName = "256 x 256")`
- L22 _public enumerator_ `Resolution512 UMETA(DisplayName = "512 x 512")`
- L23 _public enumerator_ `Resolution1024 UMETA(DisplayName = "1024 x 1024")`
- L24 _public enumerator_ `Resolution2048 UMETA(DisplayName = "2048 x 2048")`
- L25 _public enumerator_ `Resolution4096 UMETA(DisplayName = "4096 x 4096")`
- L26 _public enumerator_ `Resolution8192 UMETA(DisplayName = "8192 x 8192")`

#### enum `EGeometryScriptBakeBitDepth`  
`enum class EGeometryScriptBakeBitDepth : uint8`  
_L30-34_
- reflection: `UENUM(BlueprintType)`
- L32 _public enumerator_ `ChannelBits8 UMETA(DisplayName = "8 bits/channel")`
- L33 _public enumerator_ `ChannelBits16 UMETA(DisplayName = "16 bits/channel")`

#### enum `EGeometryScriptBakeSamplesPerPixel`  
`enum class EGeometryScriptBakeSamplesPerPixel : uint8`  
_L37-44_
- reflection: `UENUM(BlueprintType)`
- L39 _public enumerator_ `Sample1 UMETA(DisplayName = "1")`
- L40 _public enumerator_ `Sample4 UMETA(DisplayName = "4")`
- L41 _public enumerator_ `Sample16 UMETA(DisplayName = "16")`
- L42 _public enumerator_ `Sample64 UMETA(DisplayName = "64")`
- L43 _public enumerator_ `Samples256 UMETA(DisplayName = "256")`

#### enum `EGeometryScriptBakeFilteringType`  
`enum class EGeometryScriptBakeFilteringType : uint8`  
_L47-51_
- reflection: `UENUM(BlueprintType)`
- L49 _public enumerator_ `BSpline UMETA(DisplayName = "B-Spline")`
- L50 _public enumerator_ `Box UMETA(DisplayName = "Box")`

#### enum `EGeometryScriptBakeTypes`  
`enum class EGeometryScriptBakeTypes : uint8`  
_L54-85_
- reflection: `UENUM(BlueprintType)`
- L56 _public enumerator_ `None`
- L58 _public enumerator_ `TangentSpaceNormal UMETA(DisplayName = "Tangent Normal")` — Normals in tangent space
- L60 _public enumerator_ `ObjectSpaceNormal UMETA(DisplayName = "Object Normal")` — Interpolated normals in object space
- L62 _public enumerator_ `FaceNormal` — Geometric face normals in object space
- L64 _public enumerator_ `BentNormal` — Normals skewed towards the least occluded direction
- L66 _public enumerator_ `Position` — Positions in object space
- L68 _public enumerator_ `Curvature` — Local curvature of the mesh surface
- L70 _public enumerator_ `AmbientOcclusion` — Ambient occlusion sampled across the hemisphere
- L72 _public enumerator_ `Texture` — Transfer a given texture
- L74 _public enumerator_ `MultiTexture` — Transfer a texture per material ID
- L76 _public enumerator_ `VertexColor` — Interpolated vertex colors
- L78 _public enumerator_ `MaterialID UMETA(DisplayName = "Material ID")` — Material IDs as unique colors
- L80 _public enumerator_ `Constant` — Constant value
- L82 _public enumerator_ `UVShell UMETA(DisplayName = "UV Shell")` — UV Shell
- L84 _public enumerator_ `Height` — Height

#### enum `EGeometryScriptBakeOutputMode`  
`enum class EGeometryScriptBakeOutputMode : uint8`  
_L88-92_
- reflection: `UENUM(BlueprintType)`
- L90 _public enumerator_ `RGBA`
- L91 _public enumerator_ `PerChannel`

#### enum `EGeometryScriptBakeNormalSpace`  
`enum class EGeometryScriptBakeNormalSpace : uint8`  
_L95-101_
- reflection: `UENUM(BlueprintType)`
- L98 _public enumerator_ `Tangent` — Tangent space
- L100 _public enumerator_ `Object` — Object space

#### enum `EGeometryScriptBakeVertexTopology`  
`enum class EGeometryScriptBakeVertexTopology : uint8`  
_L104-110_
- reflection: `UENUM(BlueprintType)`
- L107 _public enumerator_ `CreateNew` — Create new vertex color topology
- L109 _public enumerator_ `UseExisting` — Use existing vertex color topology

#### struct `FGeometryScriptBakeTypes`  
`struct FGeometryScriptBakeTypes`  
_L112-114_

#### struct `FGeometryScriptBakeType_Occlusion`  
`struct FGeometryScriptBakeType_Occlusion : public FGeometryScriptBakeTypes`  
_L116-132_
- inherits: `FGeometryScriptBakeTypes`
- L119 _public member_ `int32 OcclusionRays = 16;` — Number of occlusion rays per sample
- L122 _public member_ `float MaxDistance = 0.0f;` — Maximum distance for occlusion rays to test for intersections; a value of 0 means infinity
- L125 _public member_ `float SpreadAngle = 180.0f;` — Maximum spread angle in degrees for occlusion rays; for example, 180 degrees will cover the entire hemisphere whereas 90 degrees will only cover the center of the hemisphere down to 45 degrees from the horizon.
- L128 _public member_ `float BiasAngle = 15.0f;` — Angle in degrees from the horizon for occlusion rays for which the contribution is attenuated to reduce faceting artifacts.
- L131 _public member_ `EGeometryScriptBakeNormalSpace NormalSpace = EGeometryScriptBakeNormalSpace::Tangent;` — Normal space for Bent Normals.

#### enum `EGeometryScriptBakeCurvatureTypeMode`  
`enum class EGeometryScriptBakeCurvatureTypeMode : uint8`  
_L135-145_
- reflection: `UENUM(BlueprintType)`
- L138 _public enumerator_ `Mean` — Average of the minimum and maximum principal curvatures
- L140 _public enumerator_ `Max` — Maximum principal curvature
- L142 _public enumerator_ `Min` — Minimum principal curvature
- L144 _public enumerator_ `Gaussian` — Product of the minimum and maximum principal curvatures

#### enum `EGeometryScriptBakeCurvatureColorMode`  
`enum class EGeometryScriptBakeCurvatureColorMode : uint8`  
_L148-156_
- reflection: `UENUM(BlueprintType)`
- L151 _public enumerator_ `Grayscale` — Map curvature values to grayscale such that black is negative, grey is zero, and white is positive
- L153 _public enumerator_ `RedBlue` — Map curvature values to red and blue such that red is negative, black is zero, and blue is positive
- L155 _public enumerator_ `RedGreenBlue` — Map curvature values to red, green, blue such that red is negative, green is zero, and blue is positive

#### enum `EGeometryScriptBakeCurvatureClampMode`  
`enum class EGeometryScriptBakeCurvatureClampMode : uint8`  
_L159-167_
- reflection: `UENUM(BlueprintType)`
- L162 _public enumerator_ `None` — Include both negative and positive curvatures
- L164 _public enumerator_ `OnlyPositive` — Clamp negative curvatures to zero
- L166 _public enumerator_ `OnlyNegative` — Clamp positive curvatures to zero

#### struct `FGeometryScriptBakeType_Curvature`  
`struct FGeometryScriptBakeType_Curvature : public FGeometryScriptBakeTypes`  
_L169-185_
- inherits: `FGeometryScriptBakeTypes`
- L172 _public member_ `EGeometryScriptBakeCurvatureTypeMode CurvatureType = EGeometryScriptBakeCurvatureTypeMode::Mean;` — Type of curvature
- L175 _public member_ `EGeometryScriptBakeCurvatureColorMode ColorMapping = EGeometryScriptBakeCurvatureColorMode::Grayscale;` — How to map calculated curvature values to colors
- L178 _public member_ `float ColorRangeMultiplier = 1.0f;` — Multiplier for how the curvature values fill the available range in the selected Color Mapping; a larger value means that higher curvature is required to achieve the maximum color value.
- L181 _public member_ `float MinRangeMultiplier = 0.0f;` — Minimum for the curvature values to not be clamped to zero relative to the curvature for the maximum color value; a larger value means that higher curvature is required to not be considered as no curvature.
- L184 _public member_ `EGeometryScriptBakeCurvatureClampMode Clamping = EGeometryScriptBakeCurvatureClampMode::None;` — Clamping applied to curvature values before color mapping

#### enum `EGeometryScriptBakeHeightRangeMode`  
`enum class EGeometryScriptBakeHeightRangeMode : uint8`  
_L188-194_
- reflection: `UENUM(BlueprintType)`
- L191 _public enumerator_ `Absolute` — Height range defined in absolute units in object space
- L193 _public enumerator_ `RelativeBounds` — Height range defined as a ratio of the maximal bounding box axis

#### struct `FGeometryScriptBakeType_Height`  
`struct FGeometryScriptBakeType_Height : public FGeometryScriptBakeTypes`  
_L196-209_
- inherits: `FGeometryScriptBakeTypes`
- L202 _public member_ `EGeometryScriptBakeHeightRangeMode HeightRangeMode = EGeometryScriptBakeHeightRangeMode::Absolute;` — When set to Absolute, Inner/Outer distance are interpreted as an absolute distance range in object space. When set to RelativeBounds, Inner/Outer distance are interpreted as a ratio of the maximal bounding box axis.
- L205 _public member_ `float InnerDistance = -1.0f;` — The absolute or relative inner distance from the target mesh, in object space units.
- L208 _public member_ `float OuterDistance = 1.0f;` — The absolute or relative outer distance from the target mesh, in object space units.

#### struct `FGeometryScriptBakeType_UVShell`  
`struct FGeometryScriptBakeType_UVShell : public FGeometryScriptBakeTypes`  
_L211-227_
- inherits: `FGeometryScriptBakeTypes`
- L214 _public member_ `int SourceUVLayer = 0;` — The source UV layer to sample.
- L217 _public member_ `float WireframeThickness = 1.0f;` — The pixel thickness of the wireframes.
- L220 _public member_ `FLinearColor WireframeColor = FLinearColor::Blue;` — The color for wireframe samples.
- L223 _public member_ `FLinearColor ShellColor = FLinearColor::Gray;` — The color for UV shell triangle fill samples.
- L226 _public member_ `FLinearColor BackgroundColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);` — The color for samples external to UV shells.

#### struct `FGeometryScriptBakeType_Texture`  
`struct FGeometryScriptBakeType_Texture : public FGeometryScriptBakeTypes`  
_L229-236_
- inherits: `FGeometryScriptBakeTypes`
- L232 _public member_ `TObjectPtr<UTexture2D> SourceTexture = nullptr;` — Source mesh texture that is to be resampled into a new texture
- L235 _public member_ `int SourceUVLayer = 0;` — UV channel to use for the source mesh texture

#### struct `FGeometryScriptBakeType_MultiTexture`  
`struct FGeometryScriptBakeType_MultiTexture : public FGeometryScriptBakeTypes`  
_L238-245_
- inherits: `FGeometryScriptBakeTypes`
- L241 _public member_ `TArray<TObjectPtr<UTexture2D>> MaterialIDSourceTextures;` — For each material ID, the source texture that will be resampled in that material's region
- L244 _public member_ `int SourceUVLayer = 0;` — UV channel to use for the source mesh texture

#### struct `FGeometryScriptBakeType_Constant`  
`struct FGeometryScriptBakeType_Constant : public FGeometryScriptBakeTypes`  
_L247-251_
- inherits: `FGeometryScriptBakeTypes`
- L250 _public member_ `float Value = 0.0f;` — Constant value to set

#### struct `FGeometryScriptBakeTypeOptions`  
`struct FGeometryScriptBakeTypeOptions`  
_L257-266_
- reflection: `USTRUCT(BlueprintType)`
- desc: Opaque struct for storing bake type options.
- L263 _public member_ `EGeometryScriptBakeTypes BakeType = EGeometryScriptBakeTypes::None;` — `UPROPERTY(BlueprintReadOnly, Category = Type)` — The bake output type to generate
- L265 _public member_ `TSharedPtr<FGeometryScriptBakeTypes> Options;`

#### struct `FGeometryScriptBakeTextureOptions`  
`struct FGeometryScriptBakeTextureOptions`  
_L269-306_
- reflection: `USTRUCT(BlueprintType)`
- L275 _public member_ `EGeometryScriptBakeResolution Resolution = EGeometryScriptBakeResolution::Resolution256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The pixel resolution of the generated textures
- L279 _public member_ `EGeometryScriptBakeBitDepth BitDepth = EGeometryScriptBakeBitDepth::ChannelBits8;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The bit depth for each channel of the generated textures
- L283 _public member_ `int32 GutterSize = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta=(ClampMin=0))` — The pixel distance to pad baked content past the UV borders.
- L287 _public member_ `EGeometryScriptBakeSamplesPerPixel SamplesPerPixel = EGeometryScriptBakeSamplesPerPixel::Sample1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Number of samples per pixel
- L291 _public member_ `TObjectPtr<UTexture2D> SampleFilterMask = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Mask texture for filtering out samples/pixels from the output texture
- L295 _public member_ `EGeometryScriptBakeFilteringType FilteringType = EGeometryScriptBakeFilteringType::BSpline;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Filtering Type to perform on samples
- L300 _public member_ `float ProjectionDistance = 3.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Maximum allowed distance for the projection from target mesh to source mesh for the sample to be considered valid. This is only relevant if a separate source mesh is provided.
- L305 _public member_ `bool bProjectionInWorldSpace = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true, uses the world space positions for the projection from target mesh to source mesh, otherwise it uses their object space positions. This is only relevant if a separate source mesh is provided.

#### struct `FGeometryScriptBakeVertexOptions`  
`struct FGeometryScriptBakeVertexOptions`  
_L309-334_
- reflection: `USTRUCT(BlueprintType)`
- L315 _public member_ `EGeometryScriptBakeVertexTopology TopologyMode = EGeometryScriptBakeVertexTopology::CreateNew;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Option to generate new vertex color topology or reuse existing vertex color topology.
- L319 _public member_ `bool bSplitAtNormalSeams = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true, compute a separate vertex color for each unique normal on a vertex
- L323 _public member_ `bool bSplitAtUVSeams = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta=(DisplayName = "Split at UV Seams"))` — If true, compute a separate vertex color for each unique UV on a vertex.
- L328 _public member_ `float ProjectionDistance = 3.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Maximum allowed distance for the projection from target mesh to source mesh for the sample to be considered valid. This is only relevant if a separate source mesh is provided.
- L333 _public member_ `bool bProjectionInWorldSpace = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true, uses the world space positions for the projection from target mesh to source mesh, otherwise it uses their object space positions. This is only relevant if a separate source mesh is provided.

#### struct `FGeometryScriptBakeOutputType`  
`struct FGeometryScriptBakeOutputType`  
_L337-359_
- reflection: `USTRUCT(BlueprintType)`
- L343 _public member_ `EGeometryScriptBakeOutputMode OutputMode = EGeometryScriptBakeOutputMode::RGBA;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The bake output mode
- L346 _public member_ `FGeometryScriptBakeTypeOptions RGBA;` — `UPROPERTY(BlueprintReadWrite, Category = Output)`
- L349 _public member_ `FGeometryScriptBakeTypeOptions R;` — `UPROPERTY(BlueprintReadWrite, Category = Output)`
- L352 _public member_ `FGeometryScriptBakeTypeOptions G;` — `UPROPERTY(BlueprintReadWrite, Category = Output)`
- L355 _public member_ `FGeometryScriptBakeTypeOptions B;` — `UPROPERTY(BlueprintReadWrite, Category = Output)`
- L358 _public member_ `FGeometryScriptBakeTypeOptions A;` — `UPROPERTY(BlueprintReadWrite, Category = Output)`

#### struct `FGeometryScriptBakeTargetMeshOptions`  
`struct FGeometryScriptBakeTargetMeshOptions`  
_L362-368_
- reflection: `USTRUCT(BlueprintType)`
- L367 _public member_ `int TargetUVLayer = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (DisplayName="Target UV Channel"))`

#### struct `FGeometryScriptBakeSourceMeshOptions`  
`struct FGeometryScriptBakeSourceMeshOptions`  
_L371-383_
- reflection: `USTRUCT(BlueprintType)`
- L376 _public member_ `TObjectPtr<UTexture2D> SourceNormalMap = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L379 _public member_ `int SourceNormalUVLayer = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (DisplayName="Source Normal UV Channel"))`
- L382 _public member_ `EGeometryScriptBakeNormalSpace SourceNormalSpace = EGeometryScriptBakeNormalSpace::Tangent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptBakeRenderCaptureOptions`  
`struct FGeometryScriptBakeRenderCaptureOptions`  
_L386-484_
- reflection: `USTRUCT(BlueprintType)`
- L400 _public member_ `TArray<FGeometryScriptRenderCaptureCamera> Cameras;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If not empty the given Render Capture Cameras are used to create the photos from which to Bake textures If empty then a default set of Render Capture Cameras with frustums containing the SourceActors bounding box is used Note: Providing a value is highly recommended, the default camera set is intended only to support legacy blueprints
- L407 _public member_ `EGeometryScriptBakeResolution RenderCaptureResolution = EGeometryScriptBakeResolution::Resolution256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta=(DisplayName="Default Capture Resolution"))` — The pixel resolution of the default render capture camera photo sets. Only used if Cameras is empty
- L414 _public member_ `double FieldOfViewDegrees = 45.0;` — `UPROPERTY()` — Default field of view of the default render capture cameras. Only used if Cameras is empty
- L421 _public member_ `double NearPlaneDist = 1.0;` — `UPROPERTY()` — Default near plane distance for the viewing frustums of the default render capture cameras. Only used if Cameras is empty
- L431 _public member_ `EGeometryScriptBakeResolution Resolution = EGeometryScriptBakeResolution::Resolution256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The pixel resolution of the generated textures
- L435 _public member_ `EGeometryScriptBakeSamplesPerPixel SamplesPerPixel = EGeometryScriptBakeSamplesPerPixel::Sample1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Number of samples per pixel
- L439 _public member_ `bool bRenderCaptureAntiAliasing = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, DisplayName="Render Capture Anti-aliasing")` — Whether to use anti-aliasing in the render captures, this may introduce artefacts if pixels at different scene depths get blended
- L454 _public member_ `float CleanupTolerance = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — This threshold is used to detect occlusion artefacts (e.g., silhouettes/blotches in the base color) so that texels exhibiting them can be cleaned up i.e., rejected and filled in using the values of nearby valid texels instead. If the threshold is zero, the cleanup step is skipped. If the threshold is too large, texels with artefacts won't be detected and the cleanup step is effectively skipped. If the threshold is too small, texels without artefacts get detected and results will be bad because there won't be enough nearby valid texels from which to infill values. A good starting point is to choose a threshold around the size of the distance (in world space) between the target and source meshes; if the target was generated by VoxWrap then the voxel size estimates this distance.
- L457 _public member_ `bool bBaseColorMap = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L461 _public member_ `bool bNormalMap = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — World space normal map
- L465 _public member_ `bool bPackedMRSMap = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, DisplayName="Packed MRS Map")` — Packed Metallic/Roughness/Specular Map. If this is true the separated channel booleans are ignored
- L468 _public member_ `bool bMetallicMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L471 _public member_ `bool bRoughnessMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L474 _public member_ `bool bSpecularMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L477 _public member_ `bool bEmissiveMap = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L480 _public member_ `bool bOpacityMap = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L483 _public member_ `bool bSubsurfaceColorMap = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptRenderCaptureTextures`  
`struct FGeometryScriptRenderCaptureTextures`  
_L487-544_
- reflection: `USTRUCT(BlueprintType)`
- L492 _public member_ `TObjectPtr<UTexture2D> BaseColorMap = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L495 _public member_ `bool bHasBaseColorMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L498 _public member_ `TObjectPtr<UTexture2D> NormalMap = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L501 _public member_ `bool bHasNormalMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L504 _public member_ `TObjectPtr<UTexture2D> PackedMRSMap = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, DisplayName="Packed MRS Map")`
- L507 _public member_ `bool bHasPackedMRSMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, DisplayName="Has Packed MRS Map")`
- L510 _public member_ `TObjectPtr<UTexture2D> MetallicMap = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L513 _public member_ `bool bHasMetallicMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L516 _public member_ `TObjectPtr<UTexture2D> RoughnessMap = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L519 _public member_ `bool bHasRoughnessMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L522 _public member_ `TObjectPtr<UTexture2D> SpecularMap = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L525 _public member_ `bool bHasSpecularMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L528 _public member_ `TObjectPtr<UTexture2D> EmissiveMap = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L531 _public member_ `bool bHasEmissiveMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L534 _public member_ `TObjectPtr<UTexture2D> OpacityMap = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L537 _public member_ `bool bHasOpacityMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L540 _public member_ `TObjectPtr<UTexture2D> SubsurfaceColorMap = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L543 _public member_ `bool bHasSubsurfaceColorMap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### class `UGeometryScriptLibrary_MeshBakeFunctions`  
`class UGeometryScriptLibrary_MeshBakeFunctions : public UBlueprintFunctionLibrary`  
_L547-656_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_Bake"))`
- inherits: `UBlueprintFunctionLibrary`
- L553 _public prototype_ `static UPARAM(DisplayName="Resolution Out") int ConvertBakeResolutionToInt(EGeometryScriptBakeResolution Ba` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake", meta=(CompactNodeTitle = "->", BlueprintAutocast))`
- L556 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTypeTan` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L559 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTypeOb` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L562 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeType` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L565 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTypeBentNormal( int OcclusionRays = 16, float MaxDistance = 0.0f, float SpreadAngle = 180.0f, EGeometryScriptBakeNormalSpace NormalSpace = EGeometryScriptBakeNormalSpace::Tangent);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L572 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTy` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L575 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTypeCurvature( EGeometryScriptBakeCurvatureTypeMode CurvatureType = EGeometryScriptBakeCurvatureTypeMode::Mean, EGeometryScriptBakeCurvatureColorMode ColorMapping = EGeometryScriptBakeCurvatureColorMode::Grayscale, float ColorRangeMultiplier = 1.0f, float MinRangeMultiplier = 0.0f, EGeometryScriptBakeCurvatureClampMode Clamping = EGeometryScriptBakeCurvatureClampMode::None);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L583 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTypeAmbientOcclusion( int OcclusionRays = 16, float MaxDistance = 0.0f, float SpreadAngle = 180.0f, float BiasAngle = 15.0f);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L590 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTypeTexture( UTexture2D* SourceTexture = nullptr, int SourceUVLayer = 0);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L595 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTypeMultiTexture( const TArray<UTexture2D*>& MaterialIDSourceTextures, UPARAM(DisplayName="Source UV Channel") int So` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L600 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTypeV` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L606 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTypeUVShell( int SourceUVLayer = 0, float WireframeThickness = 1.0f, FLinearColor WireframeColor = FLinearColor::Blue, FLinearColor ShellColor = FLinearColor::Gray, FLinearColor BackgroundColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L614 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTypeHeight( EGeometryScriptBakeHeightRangeMode RangeMode = EGeometryScriptBakeHeightRangeMode::Absolute, float InnerDistance = -1.0f, float OuterDistance = 1.0f);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L620 _public prototype_ `static UPARAM(DisplayName="Bake Type Out") FGeometryScriptBakeTypeOptions MakeBakeTypeConstant( float Value = 0.0f);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Bake")`
- L624 _public prototype_ `static UPARAM(DisplayName="Textures Out") TArray<UTexture2D*> BakeTexture( UDynamicMesh* TargetMesh, FTransform TargetTransform, FGeometryScriptBakeTargetMeshOptions TargetOptions, UDynamicMesh* SourceMesh, FTransform SourceTransform, FGeometryScriptBakeSourceMeshOptions SourceOptions, const TArray<FGeometryScriptBakeTypeOptions>& BakeTypes, FGeometryScriptBakeTextureOptions BakeOptions, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Bake", meta = (HidePin = "Debug"))`
- L636 _public prototype_ `static UPARAM(DisplayName="Target Mesh") UDynamicMesh* BakeVertex( UDynamicMesh* TargetMesh, FTransform TargetTransform, FGeometryScriptBakeTargetMeshOptions TargetOptions, UDynamicMesh* SourceMesh, FTransform SourceTransform, FGeometryScriptBakeSourceMeshOptions SourceOptions, FGeometryScriptBakeOutputType BakeTypes, FGeometryScriptBakeVertexOptions BakeOptions, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Bake", meta = (HidePin = "Debug"))`
- L648 _public prototype_ `static UPARAM(DisplayName="Textures Out") FGeometryScriptRenderCaptureTextures BakeTextureFromRenderCaptures( UDynamicMesh* TargetMesh, FTransform TargetLocalToWorld, FGeometryScriptBakeTargetMeshOptions TargetOptions, const TArray<AActor*> SourceActors, FGeometryScriptBakeRenderCaptureOptions BakeOptions, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Bake", meta = (HidePin = "Debug"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshBasicEditFunctions.h` (Public)


#### struct `FGeometryScriptSimpleMeshBuffers`  
`struct FGeometryScriptSimpleMeshBuffers`  
_L22-58_
- reflection: `USTRUCT(BlueprintType)`
- L27 _public member_ `TArray<FVector> Vertices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L30 _public member_ `TArray<FVector> Normals;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L33 _public member_ `TArray<FVector2D> UV0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L35 _public member_ `TArray<FVector2D> UV1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L37 _public member_ `TArray<FVector2D> UV2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L39 _public member_ `TArray<FVector2D> UV3;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L41 _public member_ `TArray<FVector2D> UV4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L43 _public member_ `TArray<FVector2D> UV5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L45 _public member_ `TArray<FVector2D> UV6;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L47 _public member_ `TArray<FVector2D> UV7;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L50 _public member_ `TArray<FLinearColor> VertexColors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L54 _public member_ `TArray<FIntVector> Triangles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L57 _public member_ `TArray<int> TriGroupIDs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### enum `EGeometryScriptCombineAttributesMode`  
`enum class EGeometryScriptCombineAttributesMode : uint8`  
_L63-71_
- reflection: `UENUM(BlueprintType)`
- desc: Options for how attributes from a source and target mesh are combined into the target mesh
- L66 _public enumerator_ `EnableAllMatching` — Include attributes enabled on either the source or target mesh
- L68 _public enumerator_ `UseTarget` — Only include attributes that are already enabled on the target mesh
- L70 _public enumerator_ `UseSource` — Make the target mesh have only the attributes that are enabled on the source mesh

#### struct `FGeometryScriptAppendMeshOptions`  
`struct FGeometryScriptAppendMeshOptions`  
_L78-89_
- reflection: `USTRUCT(BlueprintType)`
- desc: Control how details like mesh attributes are handled when one mesh is appended to another
- L85 _public member_ `EGeometryScriptCombineAttributesMode CombineMode = EGeometryScriptCombineAttributesMode::EnableAllMatching;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — How attributes from each mesh are combined into the result
- L88 _public prototype_ `void UpdateAttributesForCombineMode(UE::Geometry::FDynamicMesh3& Target, const UE::Geometry::FDynamicMesh3& Source);`

#### struct `FGeometryScriptMergeVertexOptions`  
`struct FGeometryScriptMergeVertexOptions`  
_L95-108_
- reflection: `USTRUCT(BlueprintType)`
- desc: Options for merging vertex pairs
- L102 _public member_ `bool bOnlyBoundary = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to restrict merges to boundary vertices
- L106 _public member_ `bool bAllowNonBoundaryBowties = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to allow the merge to introduce a non-boundary bowtie vertex (has no effect if bOnlyBoundary is true)

#### class `UGeometryScriptLibrary_MeshBasicEditFunctions`  
`class UGeometryScriptLibrary_MeshBasicEditFunctions : public UBlueprintFunctionLibrary`  
_L113-438_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshEdits"))`
- inherits: `UBlueprintFunctionLibrary`
- L119 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* DiscardMeshAttributes( UDynamicMesh* TargetMesh, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod))`
- L127 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetVertexPosition( UDynamicMesh* TargetMesh, int VertexID, FVector NewPosition, bool& bIsValidVertex, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod))`
- L140 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetAllMeshVertexPositions( UDynamicMesh* TargetMesh, FGeometryScriptVectorList PositionList, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod, HidePin = "Debug"))` — Set all vertex positions in the TargetMesh to the specified Positions. @param PositionList new vertex Positions. Size must be less than or equal to the MaxVertexID of TargetMesh  (ie gaps are supported).
- L150 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AddVertexToMesh( UDynamicMesh* TargetMesh, FVector NewPosition, int& NewVertexIndex, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod))` — Adds a new vertex to the mesh and returns a new Vertex ID (NewVertexIndex).
- L161 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AddVerticesToMesh( UDynamicMesh* TargetMesh, FGeometryScriptVectorList NewPositionsList, FGeometryScriptIndexList& NewIndicesList, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod))` — Adds a list of vertices to the mesh, and populates the NewIndicesList with the corresponding new Vertex IDs.
- L173 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* DeleteVertexFromMesh( UDynamicMesh* TargetMesh, int VertexID, bool& bWasVertexDeleted, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod))` — Removes a vertex from the mesh as indicated by the VertexID. Should the delete fail, e.g. if the specified vertex was not a mesh element, the flag bWasVertexDeleted will be set to false.
- L185 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* DeleteVerticesFromMesh( UDynamicMesh* TargetMesh, FGeometryScriptIndexList VertexList, int& NumDeleted, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod))` — Removes a list of vertices from the mesh. On return, NumDeleted will contain the actual number of vertices removed.
- L196 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AddTriangleToMesh( UDynamicMesh* TargetMesh, FIntVector NewTriangle, int& NewTriangleIndex, int NewTriangleGroupID = 0, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod, HidePin = "Debug"))` — Adds a triangle (Vertex ID triplet) to the mesh and updates New Triangle Index with the resulting Triangle ID.
- L209 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AddTrianglesToMesh( UDynamicMesh* TargetMesh, FGeometryScriptTriangleList NewTrianglesList, FGeometryScriptIndexList& NewIndicesList, int NewTriangleGroupID = 0, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod, HidePin = "Debug"))` — Adds a list of triangles to the mesh and populates the New Indices List with the corresponding new Triangle IDs.
- L223 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* DeleteTriangleFromMesh( UDynamicMesh* TargetMesh, int TriangleID, bool& bWasTriangleDeleted, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod))` — Removes a triangle from the mesh as indicated by the Triangle ID. Should the delete fail, e.g. if the specified triangle was not a mesh element, the flag bWasTriangleDelete will be set to false.
- L235 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* DeleteTrianglesFromMesh( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "Triangle ID List") FGeometryScriptIndexList TriangleList, int& NumDeleted, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod))` — Removes a list of triangles from the mesh. On return, NumDeleted will contain the actual number of triangles removed.
- L247 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* DeleteSelectedTrianglesFromMesh( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, int& NumDeleted, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod))` — Removes specified triangles, identified by mesh selection, from the mesh. On return, NumDeleted will contain the actual number of triangles removed.
- L267 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* MergeMeshVertexPair( UDynamicMesh* TargetMesh, int32 VertexKeep, int32 VertexDiscard, FGeometryScriptMergeVertexOptions Options, bool& bSuccess, double InterpParam = .5, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta = (ScriptMethod, HidePin = "Debug"))` — Attempt to merge together two vertices, and report whether they were merged. Note that some merges may be prevented because they would create non-manifold edges in the mesh, which are not supported. @param TargetMesh Mesh in which to merge vertices @param VertexKeep Vertex to keep after merge @param VertexDiscard Vertex to discard after merge @param Options Options for merge, controlling which merges should be permitted @param bSuccess Flag indicating whether the merge succeeded @param InterpParam The kept vertex is moved to interpolated position Lerp(VertexKeep Position, VertexDiscard Position, InterpParam) @param bDeferChangeNotifications Whether to defer change notifications after this operation
- L293 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* MergeMeshVerticesInSelections( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection SelectionKeep, FGeometryScriptMeshSelection SelectionDiscard, FGeometryScriptMergeVertexOptions Options, int& NumMerged, double InterpParam = .5, double DistanceThreshold = 1, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta = (ScriptMethod, HidePin = "Debug"))` — Attempt to merge together vertices in one selection to their closest vertices in the second selection, within a distance threshold. Note that some merges may be prevented because they would create non-manifold edges in the mesh, which are not supported. @param TargetMesh Mesh in which to merge vertices @param SelectionKeep Selection of vertices to be merged with SelectionDiscard, treated as 'kept' vertices for purposes of interpolation. @param SelectionDiscard Selection of vertices to be merged with SelectionKeep. Note: If a vertex is in both selections, it will be treated as if it were only in SelectionKeep. @param Options Options for merge, controlling which merges should be permitted @param NumMerged Number of vertices merged @param InterpParam The kept vertex is moved to interpolated position Lerp(VertexKeep Position, VertexDiscard Position, InterpParam) @param DistanceThreshold Vertices further apart than this threshold will not be merged @param bDeferChangeNotifications Whether to defer change notifications after this operation
- L313 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendMesh( UDynamicMesh* TargetMesh, UDynamicMesh* AppendMesh, FTransform AppendTransform, bool bDeferChangeNotifications = false, FGeometryScriptAppendMeshOptions AppendOptions = FGeometryScriptAppendMeshOptions(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod, HidePin = "Debug"))` — Apply Append Transform to Append Mesh and then add its geometry to the Target Mesh. @param AppendOptions Control how details like mesh attributes are handled when one mesh is appended to another.
- L328 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendMeshWithMaterials( UDynamicMesh* TargetMesh, const TArray<UMaterialInterface*>& TargetMeshMaterialList, UDynamicMesh* AppendMesh, const TArray<UMaterialInterface*>& AppendMeshMaterialList, TArray<UMaterialInterface*>& ResultMeshMaterialList, FTransform AppendTransform, bool bDeferChangeNotifications = false, FGeometryScriptAppendMeshOptions AppendOptions = FGeometryScriptAppendMeshOptions(), bool bCompactAppendedMaterials = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta = (ScriptMethod, HidePin = "Debug"))` — Apply Append Transform to Append Mesh and then add its geometry to the Target Mesh. Also combines materials lists of the Target and Append meshes, and updates the output mesh materials to reference the combined list. @param AppendOptions Control how details like mesh attributes are handled when one mesh is appended to another.
- L348 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendMeshTransformed( UDynamicMesh* TargetMesh, UDynamicMesh* AppendMesh, const TArray<FTransform>& AppendTransforms, FTransform ConstantTransform, bool bConstantTransformIsRelative = true, bool bDeferChangeNotifications = false, FGeometryScriptAppendMeshOptions AppendOptions = FGeometryScriptAppendMeshOptions(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod, HidePin = "Debug"))` — For each transform in AppendTransforms, apply the transform to AppendMesh and then add its geometry to the TargetMesh. @param ConstantTransform the Constant transform will be applied after each Append transform @param bConstantTransformIsRelative if true, the Constant transform is applied "in the frame" of the Append Transform, otherwise it is applied as a second transform in local coordinates (ie rotate around the AppendTransform X axis, vs around the local X axis) @param AppendOptions Control how details like mesh attributes are handled when one mesh is appended to another
- L368 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendMeshTransformedWithMaterials( UDynamicMesh* TargetMesh, const TArray<UMaterialInterface*>& TargetMeshMaterialList, UDynamicMesh* AppendMesh, const TArray<UMaterialInterface*>& AppendMeshMaterialList, TArray<UMaterialInterface*>& ResultMeshMaterialList, const TArray<FTransform>& AppendTransforms, FTransform ConstantTransform, bool bConstantTransformIsRelative = true, bool bDeferChangeNotifications = false, FGeometryScriptAppendMeshOptions AppendOptions = FGeometryScriptAppendMeshOptions(), bool bCompactAppendedMaterials = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod, HidePin = "Debug"))` — For each transform in AppendTransforms, apply the transform to AppendMesh and then add its geometry to the TargetMesh. Also combines materials lists of the Target and Append meshes, and updates the output mesh materials to reference the combined list. @param ConstantTransform the Constant transform will be applied after each Append transform @param bConstantTransformIsRelative if true, the Constant transform is applied "in the frame" of the Append Transform, otherwise it is applied as a second transform in local coordinates (ie rotate around the AppendTransform X axis, vs around the local X axis) @param AppendOptions Control how details like mesh attributes are handled when one mesh is appended to another
- L390 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendMeshRepeated( UDynamicMesh* TargetMesh, UDynamicMesh* AppendMesh, FTransform AppendTransform, int RepeatCount = 1, bool bApplyTransformToFirstInstance = true, bool bDeferChangeNotifications = false, FGeometryScriptAppendMeshOptions AppendOptions = FGeometryScriptAppendMeshOptions(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod, HidePin = "Debug"))` — Repeatedly apply AppendTransform to the AppendMesh, each time adding the geometry to TargetMesh. @param RepeatCount number of times to repeat the transform-append cycle @param bApplyTransformToFirstInstance if true, the AppendTransform is applied before the first mesh append, otherwise it is applied after @param AppendOptions Control how details like mesh attributes are handled when one mesh is appended to another
- L409 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendMeshRepeatedWithMaterials( UDynamicMesh* TargetMesh, const TArray<UMaterialInterface*>& TargetMeshMaterialList, UDynamicMesh* AppendMesh, const TArray<UMaterialInterface*>& AppendMeshMaterialList, TArray<UMaterialInterface*>& ResultMeshMaterialList, FTransform AppendTransform, int RepeatCount = 1, bool bApplyTransformToFirstInstance = true, bool bDeferChangeNotifications = false, FGeometryScriptAppendMeshOptions AppendOptions = FGeometryScriptAppendMeshOptions(), bool bCompactAppendedMaterials = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod, HidePin = "Debug"))` — Repeatedly apply AppendTransform to the AppendMesh, each time adding the geometry to TargetMesh. Also combines materials lists of the Target and Append meshes, and updates the output mesh materials to reference the combined list. @param RepeatCount number of times to repeat the transform-append cycle @param bApplyTransformToFirstInstance if true, the AppendTransform is applied before the first mesh append, otherwise it is applied after @param AppendOptions Control how details like mesh attributes are handled when one mesh is appended to another
- L429 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendBuffersToMesh( UDynamicMesh* TargetMesh, const FGeometryScriptSimpleMeshBuffers& Buffers, FGeometryScriptIndexList& NewTriangleIndicesList, int MaterialID = 0, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod, HidePin = "Debug"))` — Adds a set of vertices/triangles to the mesh, with Normals, UVs, and Colors; returning the new triangles indices

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshBoneWeightFunctions.h` (Public)


#### struct `FGeometryScriptBoneWeight`  
`struct FGeometryScriptBoneWeight`  
_L19-34_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Bone Weights"))`
- L23 _public prototype_ `FGeometryScriptBoneWeight() = default;`
- L24 _public function_ `FGeometryScriptBoneWeight(int32 InBoneIndex, float InWeight) : BoneIndex(InBoneIndex), Weight(InWeight)`
- L30 _public member_ `int32 BoneIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoneWeights)`
- L33 _public member_ `float Weight = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoneWeights)`

#### struct `FGeometryScriptBoneWeightProfile`  
`struct FGeometryScriptBoneWeightProfile`  
_L38-46_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Bone Weights Profile"))`
- L43 _public member_ `FName ProfileName = FSkeletalMeshAttributes::DefaultSkinWeightProfileName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoneWeights)`
- L45 _public function_ `FName GetProfileName() const`

#### enum `EGeometryScriptPruneBoneWeightsAssignmentType`  
`enum class EGeometryScriptPruneBoneWeightsAssignmentType : uint8`  
_L49-53_
- reflection: `UENUM(BlueprintType)`
- L51 _public enumerator_ `RenormalizeRemaining = 0`
- L52 _public enumerator_ `ReassignToParent = 1` — RenormalizeRemaining = 0,	  Remove the bone from the bone weights and renormalize the remaining weights.

#### struct `FGeometryScriptPruneBoneWeightsOptions`  
`struct FGeometryScriptPruneBoneWeightsOptions`  
_L56-67_
- reflection: `USTRUCT(BlueprintType)`
- L62 _public member_ `EGeometryScriptPruneBoneWeightsAssignmentType ReassignmentType = EGeometryScriptPruneBoneWeightsAssignmentType::RenormalizeRemaining;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Specifies how the weight of the removed bone from a vertex's bone weights list gets reassigned.
- L66 _public member_ `bool bIgnoredInvalidBones = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Ignore invalid bones. Otherwise, if invalid bones are given, the operation terminates with an error

#### enum `EGeometryScriptSmoothBoneWeightsType`  
`enum class EGeometryScriptSmoothBoneWeightsType : uint8`  
_L70-74_
- reflection: `UENUM(BlueprintType)`
- L72 _public enumerator_ `DirectDistance = 0`
- L73 _public enumerator_ `GeodesicVoxel = 1` — DirectDistance = 0,		  Compute weighting by using Euclidean distance from bone to vertex

#### struct `FGeometryScriptSmoothBoneWeightsOptions`  
`struct FGeometryScriptSmoothBoneWeightsOptions`  
_L78-104_
- reflection: `USTRUCT(BlueprintType)`
- L84 _public member_ `EGeometryScriptSmoothBoneWeightsType DistanceWeighingType = EGeometryScriptSmoothBoneWeightsType::DirectDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The type of algorithm to use for computing the bone weight for each vertex
- L90 _public member_ `float Stiffness = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — How rigid the binding should be. Higher values result in a more rigid binding (greater influence by bones closer to the vertex than those further away).
- L96 _public member_ `int32 MaxInfluences = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Maximum number of bones that contribute to each weight. Set to 1 for a completely rigid binding. Higher values to have more distant bones make additional contributions to the deformation at each vertex.
- L103 _public member_ `int32 VoxelResolution = 256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta=(EditCondition="DistanceWeighingType==EGeometryScriptSmoothBoneWeightsType::GeodesicVoxel"))` — The resolution to build the voxelized representation of the mesh, for computing geodesic distance. Higher values result in greater fidelity and less chance of disconnected parts contributing, but slower rate of computation and more memory usage.

#### enum `ETransferBoneWeightsMethod`  
`enum class ETransferBoneWeightsMethod : uint8`  
_L107-122_
- reflection: `UENUM(BlueprintType)`
- L113 _public enumerator_ `ClosestPointOnSurface = 0` — For every vertex on the TargetMesh, find the closest point on the surface of the SourceMesh and transfer bone weights from it. This is usually a point on the SourceMesh triangle where the bone weights are computed via interpolation of the bone weights at the vertices of the triangle via barycentric coordinates.
- L121 _public enumerator_ `InpaintWeights = 1` — For every vertex on the target mesh, find the closest point on the surface of the source mesh. If that point is within the search radius (controlled via SearchPercentage), and their normals differ by less than the NormalThreshold, then we directly copy the weights from the source point to the target mesh vertex (same as the ClosestPointOnSurface method). For all the vertices we didn't copy the weights directly, automatically compute the smooth weights.

#### enum `EOutputTargetMeshBones`  
`enum class EOutputTargetMeshBones : uint8`  
_L125-139_
- reflection: `UENUM(BlueprintType)`
- L130 _public enumerator_ `SourceBones = 0` — When transferring weights, the SourceMesh bone attriubtes will be copied over to the TargetMesh, replacing any existing one, and transferred weights will be indexing the copied bone attributes.
- L138 _public enumerator_ `TargetBones = 1` — When transferring weights, if the TargetMesh has bone attributes, then the transferred SourceMesh weights will be reindexed with respect to the TargetMesh bones. In cases where a transferred SourceMesh weight refers to a bone not present in the TargetMesh bone attributes, then that weight is simply skipped, and an error message with information about the bone will be printed to the Output Log. For best results, the TargetMesh bone attributes should be a superset of all the bones that are indexed by the transferred weights.

#### struct `FGeometryScriptTransferBoneWeightsOptions`  
`struct FGeometryScriptTransferBoneWeightsOptions`  
_L142-189_
- reflection: `USTRUCT(BlueprintType)`
- L148 _public member_ `ETransferBoneWeightsMethod TransferMethod = ETransferBoneWeightsMethod::ClosestPointOnSurface;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The type of algorithm to use for transferring the bone weights.
- L152 _public member_ `EOutputTargetMeshBones OutputTargetMeshBones = EOutputTargetMeshBones::SourceBones;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Chooses which bone attributes to use for transferring weights to the TargetMesh.
- L156 _public member_ `FGeometryScriptBoneWeightProfile SourceProfile = FGeometryScriptBoneWeightProfile();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The identifier for the source bone/skin weight profile used to transfer the weights from.
- L160 _public member_ `FGeometryScriptBoneWeightProfile TargetProfile = FGeometryScriptBoneWeightProfile();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The identifier for the source bone/skin weight profile used to transfer the weights to.
- L165 _public member_ `double RadiusPercentage = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, Meta = (UIMin = -1, UIMax = 2, ClampMin = -1, ClampMax = 2, EditCondition = "TransferMethod == ETransferBoneWeightsMethod::InpaintWeights"))` — Defines the search radius as the RadiusPercentage * (input mesh bounding box diagonal). All points not within the search radius will be ignored. If negative, all points are considered. Only used in the InpaintWeights algorithm.
- L170 _public member_ `double NormalThreshold = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, Meta = (UIMin = -1, UIMax = 180, ClampMin = -1, ClampMax = 180, EditCondition="TransferMethod == ETransferBoneWeightsMethod::InpaintWeights"))` — Maximum angle (in degrees) difference between the target and the source point normals to be considred a match. If negative, normals are ignored. Only used in the InpaintWeights algorithm.
- L176 _public member_ `bool LayeredMeshSupport = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, Meta = (EditCondition = "TransferMethod == ETransferBoneWeightsMethod::InpaintWeights"))` — If true, when the closest point doesn't pass the normal threshold test, will try again with a flipped normal. This helps with layered meshes where the "inner" and "outer" layers are close to each other but whose normals are pointing in the opposite directions.
- L180 _public member_ `int32 NumSmoothingIterations = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = 0, UIMax = 100, ClampMin = 0, ClampMax = 100, EditCondition = "TransferMethod == ETransferBoneWeightsMethod::InpaintWeights"))` — The number of optional post-processing smoothing iterations applied to the vertices without the match.
- L184 _public member_ `float SmoothingStrength = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = 0, UIMax = 1, ClampMin = 0, ClampMax = 1, EditCondition = "TransferMethod == ETransferBoneWeightsMethod::InpaintWeights"))` — The strength of each post-processing smoothing iteration.
- L188 _public member_ `FName InpaintMask;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (EditCondition = "TransferMethod == ETransferBoneWeightsMethod::InpaintWeights"))` — Optional weight attribute name where a non-zero value indicates that we want the skinning weights for the vertex to be computed automatically instead of it being copied over from the source mesh.

#### struct `FGeometryScriptBoneInfo`  
`struct FGeometryScriptBoneInfo`  
_L192-219_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Bone Info"))`
- L198 _public member_ `int Index = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bone)` — Index of the bone in the skeletal hierarchy.
- L202 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bone)` — Bone name.
- L206 _public member_ `int ParentIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bone)` — Parent bone index.
- L210 _public member_ `FTransform LocalTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bone)` — Local/bone space reference transform.
- L214 _public member_ `FTransform WorldTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bone)` — Global/world space reference transform.
- L218 _public member_ `FLinearColor Color = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bone)` — Bone color.

#### enum `EBonesToCopyFromSource`  
`enum class EBonesToCopyFromSource : uint8`  
_L223-235_
- reflection: `UENUM(BlueprintType)`
- L227 _public enumerator_ `AllBones = 0` — Copy all bones from the source mesh to the target, regardless of whether they're bound or not.
- L230 _public enumerator_ `OnlyBoundAndParents = 1` — Keep only bones that are actually bound to the target mesh, including all parent bones up to the root.
- L234 _public enumerator_ `OnlyBoundAndRoot = 2` — Keep only bones that are actually bound to the target mesh and the root bone. Any existing bones between the two will not be copied. Bound bones will have their parent as either the root bone or another bound bone.

#### struct `FGeometryScriptCopyBonesFromMeshOptions`  
`struct FGeometryScriptCopyBonesFromMeshOptions`  
_L239-251_
- reflection: `USTRUCT(BlueprintType)`
- L246 _public member_ `bool ReindexWeights = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If the target Dynamic mesh has bone weights and a skeleton, re-index (re-bind) target weight indices from the target skeleton to the source skeleton.
- L250 _public member_ `EBonesToCopyFromSource BonesToCopyFromSource = EBonesToCopyFromSource::AllBones;` — `UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Options)` — Specify which bones are copied from the source mesh to the target.

#### class `UGeometryScriptLibrary_MeshBoneWeightFunctions`  
`class UGeometryScriptLibrary_MeshBoneWeightFunctions : public UBlueprintFunctionLibrary`  
_L254-572_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_BoneWeights"))`
- inherits: `UBlueprintFunctionLibrary`
- L265 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* MeshHasBoneWeights( UDynamicMesh* TargetMesh, bool& bHasBoneWeights, FGeometryScriptBoneWeightProfile Profile = FGeometryScriptBoneWeightProfile() );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod))` — Check whether the TargetMesh has a per-vertex Bone/Skin Weight Attribute set @param bHasBoneWeights will be returned true if the requested bone weight profile exists @param Profile identifier for the bone/skin weight profile
- L279 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* MeshCreateBoneWeights( UDynamicMesh* TargetMesh, bool& bProfileExisted, bool bReplaceExistingProfile = false, FGeometryScriptBoneWeightProfile Profile = FGeometryScriptBoneWeightProfile() );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod))` — Create a new BoneWeights attribute on the TargetMesh, if it does not already exist. If it does exist, and bReplaceExistingProfile is passed as true, the attribute will be removed and re-added, to reset it. @param bProfileExisted will be returned true if the requested bone weight profile already existed @param bReplaceExistingProfile if true, if the Profile already exists, it is reset @param Profile identifier for the bone/skin weight profile
- L295 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* MeshCopyBoneWeights( UDynamicMesh* TargetMesh, bool& bProfileExisted, FGeometryScriptBoneWeightProfile TargetProfile, FGeometryScriptBoneWeightProfile SourceProfile = FGeometryScriptBoneWeightProfile() );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod))` — Copies all bone weights from a source profile onto a target profile, on the same mesh, replacing all weights that existed on the target profile. If either the source or the target profile didn't exist, then bProfileExisted will be set to false and no weights are copied. @param bProfileExisted will be returned true if both of the requested bone weight profiles exist @param TargetProfile The skin weight profile to copy to. @param SourceProfile The skin weight profile to copy from.
- L310 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMaxBoneWeightIndex( UDynamicMesh* TargetMesh, bool& bHasBoneWeights, int& MaxBoneIndex, FGeometryScriptBoneWeightProfile Profile = FGeometryScriptBoneWeightProfile() );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod))` — Determine the largest bone weight index that exists on the Mesh @param bHasBoneWeights will be returned true if the requested bone weight profile exists @param MaxBoneIndex maximum bone index will be returned here, or -1 if no bone indices exist @param Profile identifier for the bone/skin weight profile
- L325 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetVertexBoneWeights( UDynamicMesh* TargetMesh, int VertexID, TArray<FGeometryScriptBoneWeight>& BoneWeights, bool& bHasValidBoneWeights, FGeometryScriptBoneWeightProfile Profile = FGeometryScriptBoneWeightProfile() );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod))` — Return an array of Bone/Skin Weights at a given vertex of TargetMesh @param VertexID requested vertex @param BoneWeights output array of bone index/weight pairs for the given Vertex @param bHasValidBoneWeights will be returned as true if the vertex has bone weights in the given profile, ie BoneWeights is valid @param Profile identifier for the bone/skin weight profile
- L341 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetLargestVertexBoneWeight( UDynamicMesh* TargetMesh, int VertexID, FGeometryScriptBoneWeight& BoneWeight, bool& bHasValidBoneWeights, FGeometryScriptBoneWeightProfile Profile = FGeometryScriptBoneWeightProfile() );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod))` — Return the Bone/Skin Weight with the maximum weight at a given vertex of TargetMesh @param VertexID requested vertex @param BoneWeight the bone index and weight that was found to have the maximum weight @param bHasValidBoneWeights will be returned as true if the vertex has bone weights in the given profile and a largest weight was found @param Profile identifier for the bone/skin weight profile
- L357 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetVertexBoneWeights( UDynamicMesh* TargetMesh, int VertexID, const TArray<FGeometryScriptBoneWeight>& BoneWeights, bool& bIsValidVertexID, FGeometryScriptBoneWeightProfile Profile = FGeometryScriptBoneWeightProfile(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Set the Bone/Skin Weights at a given vertex of TargetMesh @param VertexID vertex to update @param BoneWeights input array of bone index/weight pairs for the Vertex @param bIsValidVertexID will be returned as true if the vertex ID is valid @param Profile identifier for the bone/skin weight profile
- L379 _public prototype_ `BlendBoneWeights( const TArray<FGeometryScriptBoneWeight>& BoneWeightsA, const TArray<FGeometryScriptBoneWeight>& BoneWeightsB, float Alpha, TArray<FGeometryScriptBoneWeight>& Result, UGeometryScriptDebug* Debug = nullptr );`
- L393 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetAllVertexBoneWeights( UDynamicMesh* TargetMesh, const TArray<FGeometryScriptBoneWeight>& BoneWeights, FGeometryScriptBoneWeightProfile Profile = FGeometryScriptBoneWeightProfile(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Set all vertices of the TargetMesh to the given Bone/Skin Weights @param BoneWeights input array of bone index/weight pairs for the Vertex @param Profile identifier for the bone/skin weight profile
- L413 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* PruneBoneWeights( UDynamicMesh* TargetMesh, const TArray<FName>& BonesToPrune, FGeometryScriptPruneBoneWeightsOptions Options, FGeometryScriptBoneWeightProfile Profile = FGeometryScriptBoneWeightProfile(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Prunes the given bones from any bone weight assignment on the given profile. The bone weights are re-assigned based on the type of re-assignment specified in the options, although in the case where the bone(s) being pruned are the sole bone weight on a vertex, then the parent bone will be assigned as the sole bone weight for that vertex. Bones are pruned iteratively from leaf to root, to ensure that weighs are progressively re-assigned in case multiple bones along the same branch are being pruned. @param BonesToPrune The list of bones to remove. @param Options The options to set for the pruning algorithm. @param Profile The skin weight profile to prune the bones from.
- L429 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputeSmoothBoneWeights( UDynamicMesh* TargetMesh, USkeleton* Skeleton, FGeometryScriptSmoothBoneWeightsOptions Options, FGeometryScriptBoneWeightProfile Profile = FGeometryScriptBoneWeightProfile(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Computes a smooth skin binding for the given mesh to the skeleton provided. @param Skeleton The skeleton to compute binding for the skin weights. @param Options The options to set for the binding algorithm. @param Profile The skin weight profile to update with the smooth binding.
- L448 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* TransferBoneWeightsFromMesh( UDynamicMesh* SourceMesh, UDynamicMesh* TargetMesh, FGeometryScriptTransferBoneWeightsOptions Options = FGeometryScriptTransferBoneWeightsOptions(), FGeometryScriptMeshSelection Selection = FGeometryScriptMeshSelection(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta = (ScriptMethod, HidePin = "Debug"))` — Transfer the bone weights from the SourceMesh to the TargetMesh. Assumes that the meshes are aligned. Otherwise, use the TransformMesh geometry script function to align them. @param SourceMesh The mesh we are transferring the weights from. @param TargetMesh The mesh we are transferring the weights to. @param Options The options to set for the transfer weight algorithm. @param Selection Optional subset of target mesh vertices to transfer weights to. If left empty, skin weights will be transferred to all target mesh vertices.
- L463 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* CopyBonesFromMesh( UDynamicMesh* SourceMesh, UDynamicMesh* TargetMesh, FGeometryScriptCopyBonesFromMeshOptions Options = FGeometryScriptCopyBonesFromMeshOptions(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Copy the bone attributes (skeleton) from the SourceMesh to the TargetMesh. @param SourceMesh Mesh we are copying the bone attributes from. @param TargetMesh Mesh we are copying the bone attributes to. @param Options An option object to control how the copying is performed.
- L477 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* CopyBonesFromSkeleton( USkeleton* SourceSkeleton, UDynamicMesh* TargetMesh, FGeometryScriptCopyBonesFromMeshOptions Options = FGeometryScriptCopyBonesFromMeshOptions(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Copy the bone attributes (skeleton) from the SourceSkeleton to the TargetMesh. @param SourceSkeleton The skeleton asset we are copying the bone attributes from. @param TargetMesh Mesh we are copying the bone attributes to. @param Options An option object to control how the copying is performed.
- L489 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* DiscardBonesFromMesh( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Discard the bone attributes (skeleton) from the TargetMesh. @param TargetMesh Mesh we are discarding bone attributes from.
- L503 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetBoneIndex( UDynamicMesh* TargetMesh, FName BoneName, bool& bIsValidBoneName, int& BoneIndex, UGeometryScriptDebug* Debug = nullptr);` — `UE_DEPRECATED(5.3, "Use GetBoneInfo instead.")` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Get the index of the bone with the given name. @param TargetMesh Mesh containing the bone attributes. @param BoneName The name of the bone whose index we are getting. @param bIsValidBoneName Set to true if the TargetMesh contains a bone with the given name, false otherwise. @param BoneIndex The index of the bone with the given name. Will be set to -1 if bIsValidBoneName is false.
- L518 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetRootBoneName( UDynamicMesh* TargetMesh, FName& BoneName, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Get the name of the root bone. @param TargetMesh Mesh containing the bone attributes. @param BoneName The name of the root bone.
- L534 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetBoneChildren( UDynamicMesh* TargetMesh, FName BoneName, bool bRecursive, bool& bIsValidBoneName, TArray<FGeometryScriptBoneInfo>& ChildrenInfo, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Get the information about the children of the bone. @param TargetMesh Mesh containing the bone attributes. @param BoneName The name of bone. @param bRecursive If set to true, grandchildren will also be added recursively @param bIsValidBoneName Set to true if the TargetMesh contains a bone with the given name, false otherwise. @param ChildrenInfo The informattion of the children.
- L552 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetBoneInfo( UDynamicMesh* TargetMesh, FName BoneName, bool& bIsValidBoneName, FGeometryScriptBoneInfo& BoneInfo, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Get the bone information. @param TargetMesh Mesh containing the bone attributes. @param BoneName The name of bone. @param bIsValidBoneName Set to true if the TargetMesh contains a bone with the given name, false otherwise. @param BoneInfo The information about the bone.
- L567 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetAllBonesInfo( UDynamicMesh* TargetMesh, TArray<FGeometryScriptBoneInfo>& BonesInfo, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries|BoneWeights", meta=(ScriptMethod, HidePin = "Debug"))` — Get an array of bones representing the skeleton. Each entry contains information about the bone. @param TargetMesh Mesh containing the bone attributes. @param BonesInfo Skeleton information.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshBooleanFunctions.h` (Public)


#### enum `EGeometryScriptBooleanOperation`  
`enum class EGeometryScriptBooleanOperation : uint8`  
_L15-24_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Union`
- L18 _public enumerator_ `Intersection`
- L19 _public enumerator_ `Subtract`
- L20 _public enumerator_ `TrimInside`
- L21 _public enumerator_ `TrimOutside`
- L22 _public enumerator_ `NewPolyGroupInside UMETA(DisplayName = "New PolyGroup Inside")`
- L23 _public enumerator_ `NewPolyGroupOutside UMETA(DisplayName = "New PolyGroup Outside")`

#### enum `EGeometryScriptBooleanOutputSpace`  
`enum class EGeometryScriptBooleanOutputSpace : uint8`  
_L29-37_
- reflection: `UENUM(BlueprintType)`
- desc: Options for the output coordinate space for the mesh boolean result
- L32 _public enumerator_ `TargetTransformSpace` — Transform the boolean result into the local space of the target mesh
- L34 _public enumerator_ `ToolTransformSpace` — Transform the boolean result into the local space of the tool mesh
- L36 _public enumerator_ `SharedTransformSpace` — Keep the boolean result in the shared space where the boolean was computed

#### struct `FGeometryScriptMeshBooleanOptions`  
`struct FGeometryScriptMeshBooleanOptions`  
_L40-60_
- reflection: `USTRUCT(BlueprintType)`
- L45 _public member_ `bool bFillHoles = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L48 _public member_ `bool bSimplifyOutput = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L51 _public member_ `float SimplifyPlanarTolerance = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L55 _public member_ `bool bAllowEmptyResult = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to allow the Mesh Boolean operation to generate an empty mesh as its result
- L59 _public member_ `EGeometryScriptBooleanOutputSpace OutputTransformSpace = EGeometryScriptBooleanOutputSpace::TargetTransformSpace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The coordinate space to use for the result mesh

#### struct `FGeometryScriptMeshSelfUnionOptions`  
`struct FGeometryScriptMeshSelfUnionOptions`  
_L64-82_
- reflection: `USTRUCT(BlueprintType)`
- L69 _public member_ `bool bFillHoles = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L72 _public member_ `bool bTrimFlaps = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L75 _public member_ `bool bSimplifyOutput = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L78 _public member_ `float SimplifyPlanarTolerance = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L81 _public member_ `float WindingThreshold = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptMeshPlaneCutOptions`  
`struct FGeometryScriptMeshPlaneCutOptions`  
_L87-106_
- reflection: `USTRUCT(BlueprintType)`
- L92 _public member_ `bool bFillHoles = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L96 _public member_ `int32 HoleFillMaterialID = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If non-negative and bFillHoles is true, specify the material ID to set on hole fill triangles
- L99 _public member_ `bool bFillSpans = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L102 _public member_ `bool bFlipCutSide = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L105 _public member_ `float UVWorldDimension = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptMeshPlaneSliceOptions`  
`struct FGeometryScriptMeshPlaneSliceOptions`  
_L110-129_
- reflection: `USTRUCT(BlueprintType)`
- L115 _public member_ `bool bFillHoles = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L119 _public member_ `int32 HoleFillMaterialID = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If non-negative and bFillHoles is true, specify the material ID to set on hole fill triangles
- L122 _public member_ `bool bFillSpans = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L125 _public member_ `float GapWidth = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L128 _public member_ `float UVWorldDimension = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptMeshMirrorOptions`  
`struct FGeometryScriptMeshMirrorOptions`  
_L133-145_
- reflection: `USTRUCT(BlueprintType)`
- L138 _public member_ `bool bApplyPlaneCut = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L141 _public member_ `bool bFlipCutSide = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L144 _public member_ `bool bWeldAlongPlane = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptMeshIsoCurveOptions`  
`struct FGeometryScriptMeshIsoCurveOptions`  
_L148-159_
- reflection: `USTRUCT(BlueprintType)`
- L154 _public member_ `float CurveIsoValueSnapTolerance = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L157 _public member_ `float SnapToExistingVertexTolerance = UE_KINDA_SMALL_NUMBER;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (Units = "cm"))`

#### class `UGeometryScriptLibrary_MeshBooleanFunctions`  
`class UGeometryScriptLibrary_MeshBooleanFunctions : public UBlueprintFunctionLibrary`  
_L162-257_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshBooleans"))`
- inherits: `UBlueprintFunctionLibrary`
- L177 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshBoolean( UDynamicMesh* TargetMesh, FTransform TargetTransform, UDynamicMesh* ToolMesh, FTransform ToolTransform, EGeometryScriptBooleanOperation Operation, FGeometryScriptMeshBooleanOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Booleans", meta=(ScriptMethod, HidePin = "Debug"))` — Applies a Boolean operation (such as, Union, Intersect, and Subtract) to the Target Dynamic Mesh based on a Tool Dynamic Mesh. @param TargetMesh  Dynamic Mesh to be acted upon @param TargetTransform  used to position the TargetMesh @param ToolMesh  Dynamic Mesh that acts as the cutting tool @param ToolTransform used to position the ToolMesh @param Operation selects the specific boolean operation @param Options selects additional options that are applied to the result
- L191 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshSelfUnion( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelfUnionOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Booleans", meta=(ScriptMethod, HidePin = "Debug"))` — Mesh-Boolean-Union an object with itself to repair self-intersections, remove floating geometry, etc.
- L205 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshPlaneCut( UDynamicMesh* TargetMesh, FTransform CutFrame, FGeometryScriptMeshPlaneCutOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Booleans", meta=(ScriptMethod, HidePin = "Debug"))` — Applies a plane cut to a mesh, optionally filling any holes created. @param TargetMesh Dynamic Mesh to updated with the cut @param CutFrame defines the plane used to cut the TargetMesh @param Options selects additional clean-up operations performed after the cut.
- L219 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshPlaneSlice( UDynamicMesh* TargetMesh, FTransform CutFrame, FGeometryScriptMeshPlaneSliceOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Booleans", meta=(ScriptMethod, HidePin = "Debug"))` — Slices a mesh into two halves, with optional hole filling. @param TargetMesh Dynamic Mesh to be updated by the slice. @param CutFrame defines the plane used to slice the TargetMesh. @param Options selects additional clean-up operations performed after the cut.
- L233 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshMirror( UDynamicMesh* TargetMesh, FTransform MirrorFrame, FGeometryScriptMeshMirrorOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Booleans", meta=(ScriptMethod, HidePin = "Debug"))` — Mirrors a mesh across a plane, with optional cutting and welding of triangles. @param TargetMesh Dynamic Mesh to be updated by the mirror operation. @param MirrorFrame defines the plane used to mirror the TargetMesh. @param Options selects  additional clean-up operations performed after the mirror.
- L249 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshIsoCurves( UDynamicMesh* TargetMesh, FGeometryScriptMeshIsoCurveOptions Options, const FGeometryScriptScalarList& PerVertexValue, float IsoValue = .5, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Booleans", meta = (ScriptMethod, HidePin = "Debug"))` — Insert edges along the curve where the interpolated per-vertex values match a given isovalue @param TargetMesh Dynamic Mesh to be updated. @param Options Settings for processing to perform after inserting the curve edges @param PerVertexValue Values to interpolate, must be one per vertex @param IsoValue Value at which to insert the new curve

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshComparisonFunctions.h` (Public)


#### struct `FGeometryScriptIsSameMeshOptions`  
`struct FGeometryScriptIsSameMeshOptions`  
_L16-43_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `bool bCheckConnectivity = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L24 _public member_ `bool bCheckEdgeIDs = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L27 _public member_ `bool bCheckNormals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L30 _public member_ `bool bCheckColors = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L33 _public member_ `bool bCheckUVs = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L36 _public member_ `bool bCheckGroups = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L39 _public member_ `bool bCheckAttributes = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L42 _public member_ `float Epsilon = 1e-06f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptMeasureMeshDistanceOptions`  
`struct FGeometryScriptMeasureMeshDistanceOptions`  
_L48-54_
- reflection: `USTRUCT(BlueprintType)`
- L53 _public member_ `bool bSymmetric = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### enum `EGeometryScriptMeshDifferenceReason`  
`enum class EGeometryScriptMeshDifferenceReason : uint8`  
_L57-72_
- reflection: `UENUM(BlueprintType)`
- L59 _public enumerator_ `Unknown = 0`
- L60 _public enumerator_ `VertexCount`
- L61 _public enumerator_ `TriangleCount`
- L62 _public enumerator_ `EdgeCount`
- L63 _public enumerator_ `Vertex`
- L64 _public enumerator_ `Triangle`
- L65 _public enumerator_ `Edge`
- L66 _public enumerator_ `Connectivity`
- L67 _public enumerator_ `Normal`
- L68 _public enumerator_ `Color`
- L69 _public enumerator_ `UV`
- L70 _public enumerator_ `Group`
- L71 _public enumerator_ `Attribute`

#### struct `FGeometryScriptMeshDifferenceInfo`  
`struct FGeometryScriptMeshDifferenceInfo`  
_L75-95_
- reflection: `USTRUCT(BlueprintType)`
- L80 _public member_ `EGeometryScriptMeshDifferenceReason Reason = EGeometryScriptMeshDifferenceReason::Unknown;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Difference)`
- L84 _public member_ `FString Detail;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Difference)` — String that may contain additional detail on the difference
- L87 _public member_ `int32 TargetMeshElementID = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Difference)`
- L90 _public member_ `int32 OtherMeshElementID = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Difference)`
- L94 _public member_ `EGeometryScriptIndexType ElementIDType = EGeometryScriptIndexType::Any;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Difference)` — Indicates the type of element that TargetMeshElementID and OtherMeshElementID reference

#### class `UGeometryScriptLibrary_MeshComparisonFunctions`  
`class UGeometryScriptLibrary_MeshComparisonFunctions : public UBlueprintFunctionLibrary`  
_L98-154_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshComparison"))`
- inherits: `UBlueprintFunctionLibrary`
- L108 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* IsSameMeshAs( UDynamicMesh* TargetMesh, UDynamicMesh* OtherMesh, FGeometryScriptIsSameMeshOptions Options, bool &bIsSameMesh, FGeometryScriptMeshDifferenceInfo& DifferenceInfo, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Comparison", meta = (ScriptMethod, HidePin = "Debug"))` — Returns true if the two input meshes are equivalent under the comparisons defined by the input options. If false, DifferenceInfo provides info on the first difference found. @param DifferenceInfo If the meshes are different, provides info on the first difference found.
- L118 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* IsSameMeshAs( UDynamicMesh* TargetMesh, UDynamicMesh* OtherMesh, FGeometryScriptIsSameMeshOptions Options, bool& bIsSameMesh, UGeometryScriptDebug* Debug = nullptr);` — Non-blueprint overload of IsSameMeshAs, without DifferenceInfo, for C++ API backwards compatibilty
- L130 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* MeasureDistancesBetweenMeshes( UDynamicMesh* TargetMesh, UDynamicMesh* OtherMesh, FGeometryScriptMeasureMeshDistanceOptions Options, double& MaxDistance, double& MinDistance, double& AverageDistance, double& RootMeanSqrDeviation, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Comparison", meta = (ScriptMethod, HidePin = "Debug"))` — Measures the min/max and average closest-point distances between two meshes.
- L145 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* IsIntersectingMesh( UDynamicMesh* TargetMesh, FTransform TargetTransform, UDynamicMesh* OtherMesh, FTransform OtherTransform, bool &bIsIntersecting, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Comparison", meta = (ScriptMethod, HidePin = "Debug"))` — Returns true if the two input meshes (with optional transforms) are geometrically intersecting.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshDecompositionFunctions.h` (Public)


#### class `UGeometryScriptLibrary_MeshDecompositionFunctions`  
`class UGeometryScriptLibrary_MeshDecompositionFunctions : public UBlueprintFunctionLibrary`  
_L18-187_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshDecomposition"))`
- inherits: `UBlueprintFunctionLibrary`
- L31 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SplitMeshByComponents( UDynamicMesh* TargetMesh, TArray<UDynamicMesh*>& ComponentMeshes, UDynamicMeshPool* MeshPool, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Decomposition", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Split Mesh by Connected Islands", Keywords = "Connected Components Parts"))` — Create a new Mesh for each Connected Island (Component) of TargetMesh. New meshes are drawn from MeshPool if it is provided, otherwise new UDynamicMesh instances are allocated @param ComponentMeshes New List of meshes is returned here @param MeshPool New meshes in ComponentMeshes output list are allocated from this pool if it is provided (highly recommended!!)
- L46 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SplitMeshByVertexOverlap( UDynamicMesh* TargetMesh, TArray<UDynamicMesh*>& ComponentMeshes, UDynamicMeshPool* MeshPool, double ConnectVerticesThreshold = .001, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Decomposition", meta = (ScriptMethod, HidePin = "Debug", Keywords = "Islands Connected Components Parts"))` — Create a new Mesh for each vertex-connected or vertex-overlapping part of TargetMesh. New meshes are drawn from MeshPool if it is provided, otherwise new UDynamicMesh instances are allocated @param ComponentMeshes New List of meshes is returned here @param MeshPool New meshes in ComponentMeshes output list are allocated from this pool if it is provided (highly recommended!!) @param ConnectVerticesThreshold Vertices closer than this distance will be classified as part of the same component, even if they aren't connected by the mesh triangulation
- L62 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SplitMeshByMaterialIDs( UDynamicMesh* TargetMesh, TArray<UDynamicMesh*>& ComponentMeshes, TArray<int>& ComponentMaterialIDs, UDynamicMeshPool* MeshPool, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Decomposition", meta=(ScriptMethod, HidePin = "Debug"))` — Create a new Mesh for each MaterialID of TargetMesh. New meshes are drawn from MeshPool if it is provided, otherwise new UDynamicMesh instances are allocated @param ComponentMeshes New List of meshes is returned here @param ComponentMaterialIDs MaterialID for each Mesh in ComponentMeshes is returned here @param MeshPool New meshes in ComponentMeshes output list are allocated from this pool if it is provided (highly recommended!!)
- L78 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SplitMeshByPolygroups( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, TArray<UDynamicMesh*>& ComponentMeshes, TArray<int>& ComponentPolygroups, UDynamicMeshPool* MeshPool, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Decomposition", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Split Mesh By PolyGroups"))` — Create a new Mesh for each Polygroup of TargetMesh. Note that this may be a *large* number of meshes! New meshes are drawn from MeshPool if it is provided, otherwise new UDynamicMesh instances are allocated @param ComponentMeshes New List of meshes is returned here @param ComponentPolygroups Original Polygroup for each Mesh in ComponentMeshes is returned here @param MeshPool New meshes in ComponentMeshes output list are allocated from this pool if it is provided (highly recommended!!)
- L98 _public prototype_ `SortMeshesByVolume( UPARAM(Ref) TArray<UDynamicMesh*>& Meshes, bool bStableSort = false, EArraySortOrder SortOrder = EArraySortOrder::Ascending);`
- L112 _public prototype_ `SortMeshesByArea( UPARAM(Ref) TArray<UDynamicMesh*>& Meshes, bool bStableSort = false, EArraySortOrder SortOrder = EArraySortOrder::Ascending);`
- L126 _public prototype_ `SortMeshesByBoundsVolume( UPARAM(Ref) TArray<UDynamicMesh*>& Meshes, bool bStableSort = false, EArraySortOrder SortOrder = EArraySortOrder::Ascending);`
- L142 _public prototype_ `SortMeshesByCustomValues( UPARAM(Ref) TArray<UDynamicMesh*>& Meshes, const TArray<float>& ValuesToSortBy, bool bStableSort = false, EArraySortOrder SortOrder = EArraySortOrder::Ascending);`
- L152 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetSubMeshFromMesh( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "Copy To Submesh", ref) UDynamicMesh* StoreToSubmesh, UPARAM(DisplayName = "Triangle ID List") FGeometryScriptIndexList TriangleList, UPARAM(DisplayName = "Copy To Submesh") UDynamicMesh*& StoreToSubmeshOut, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Decomposition", meta=(ScriptMethod, HidePin = "Debug"))` — CopyMeshSelectionToMesh should be used instead of this function
- L166 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* CopyMeshSelectionToMesh( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "Copy To Submesh", ref) UDynamicMesh* StoreToSubmesh, FGeometryScriptMeshSelection Selection, UPARAM(DisplayName = "Copy To Submesh") UDynamicMesh*& StoreToSubmeshOut, bool bAppendToExisting = false, bool bPreserveGroupIDs = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Decomposition", meta=(ScriptMethod, HidePin = "Debug"))` — Extract the triangles identified by Selection from TargetMesh and copy/add them to StoreToSubmesh @param bAppendToExisting if false (default), StoreToSubmesh is cleared, otherwise selected triangles are appended @param bPreserveGroupIDs if true, GroupIDs of triangles on TargetMesh are preserved in StoreToSubmesh. Otherwise new GroupIDs are allocated.
- L180 _public prototype_ `static UPARAM(DisplayName = "Copy From Mesh") UDynamicMesh* CopyMeshToMesh( UDynamicMesh* CopyFromMesh, UPARAM(DisplayName = "Copy To Mesh", ref) UDynamicMesh* CopyToMesh, UPARAM(DisplayName = "Copy To Mesh") UDynamicMesh*& CopyToMeshOut, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Decomposition", meta=(ScriptMethod, HidePin = "Debug"))` — Set CopyToMesh to be the same mesh as CopyFromMesh

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshDeformFunctions.h` (Public)


#### struct `FGeometryScriptBendWarpOptions`  
`struct FGeometryScriptBendWarpOptions`  
_L17-32_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `bool bSymmetricExtents = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Symmetric extents are [-BendExtent,BendExtent], if disabled, then [-LowerExtent,BendExtent] is used
- L27 _public member_ `float LowerExtent = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (EditCondition = "bSymmetricExtents == false"))` — Lower extent used when bSymmetricExtents = false
- L31 _public member_ `bool bBidirectional = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true, the Bend is "centered" at the Origin, ie the regions on either side of the extents are rigidly transformed. If false, the Bend begins at the start of the Lower Extents, and the "lower" region is not affected.

#### struct `FGeometryScriptTwistWarpOptions`  
`struct FGeometryScriptTwistWarpOptions`  
_L37-52_
- reflection: `USTRUCT(BlueprintType)`
- L43 _public member_ `bool bSymmetricExtents = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Symmetric extents are [-BendExtent,BendExtent], if disabled, then [-LowerExtent,BendExtent] is used
- L47 _public member_ `float LowerExtent = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (EditCondition = "bSymmetricExtents == false"))` — Lower extent used when bSymmetricExtents = false
- L51 _public member_ `bool bBidirectional = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true, the Twist is "centered" at the Origin, ie the regions on either side of the extents are rigidly transformed. If false, the Twist begins at the start of the Lower Extents, and the "lower" region is not affected.

#### enum `EGeometryScriptFlareType`  
`enum class EGeometryScriptFlareType : uint8`  
_L55-65_
- reflection: `UENUM(BlueprintType)`
- L58 _public enumerator_ `SinMode = 0` — Displaced by sin(pi x) with x in 0 to 1
- L61 _public enumerator_ `SinSquaredMode = 1` — Displaced by sin(pi x)*sin(pi x) with x in 0 to 1. This provides a smooth normal transition.
- L64 _public enumerator_ `TriangleMode = 2` — Displaced by piecewise-linear trianglular mode

#### struct `FGeometryScriptFlareWarpOptions`  
`struct FGeometryScriptFlareWarpOptions`  
_L68-83_
- reflection: `USTRUCT(BlueprintType)`
- L74 _public member_ `bool bSymmetricExtents = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Symmetric extents are [-BendExtent,BendExtent], if disabled, then [-LowerExtent,BendExtent] is used
- L78 _public member_ `float LowerExtent = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (EditCondition = "bSymmetricExtents == false"))` — Lower extent used when bSymmetricExtents = false
- L82 _public member_ `EGeometryScriptFlareType FlareType = EGeometryScriptFlareType::SinMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Determines the profile used as a displacement

#### struct `FGeometryScriptPerlinNoiseLayerOptions`  
`struct FGeometryScriptPerlinNoiseLayerOptions`  
_L88-103_
- reflection: `USTRUCT(BlueprintType)`
- L93 _public member_ `float Magnitude = 5.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L96 _public member_ `float Frequency = 0.25;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L99 _public member_ `FVector FrequencyShift = FVector::Zero();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L102 _public member_ `int RandomSeed = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### enum `EGeometryScriptMathWarpType`  
`enum class EGeometryScriptMathWarpType : uint8`  
_L108-113_
- reflection: `UENUM(BlueprintType)`
- L110 _public enumerator_ `SinWave1D = 0`
- L111 _public enumerator_ `SinWave2D = 1`
- L112 _public enumerator_ `SinWave3D = 2`

#### struct `FGeometryScriptMathWarpOptions`  
`struct FGeometryScriptMathWarpOptions`  
_L117-129_
- reflection: `USTRUCT(BlueprintType)`
- L122 _public member_ `float Magnitude = 5.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L125 _public member_ `float Frequency = 0.25f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L128 _public member_ `float FrequencyShift = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### enum `EGeometryScriptPerVertexNormalSource`  
`enum class EGeometryScriptPerVertexNormalSource : uint8`  
_L133-139_
- reflection: `UENUM(BlueprintType)`
- L136 _public enumerator_ `Computed` — Compute new per-vertex normals from the mesh geometry
- L138 _public enumerator_ `AverageFromOverlay` — Average existing overlay normals to compute per-vertex normals

#### struct `FGeometryScriptPerlinNoiseOptions`  
`struct FGeometryScriptPerlinNoiseOptions`  
_L143-159_
- reflection: `USTRUCT(BlueprintType)`
- L148 _public member_ `FGeometryScriptPerlinNoiseLayerOptions BaseLayer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L151 _public member_ `bool bApplyAlongNormal = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L154 _public member_ `EGeometryScriptPerVertexNormalSource NormalSource = EGeometryScriptPerVertexNormalSource::Computed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta=(EditCondition="bApplyAlongNormal"))`
- L158 _public member_ `EGeometryScriptEmptySelectionBehavior EmptyBehavior = EGeometryScriptEmptySelectionBehavior::FullMeshSelection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — EmptyBehavior Defines how an empty input selection should be interpreted

#### struct `FGeometryScriptIterativeMeshSmoothingOptions`  
`struct FGeometryScriptIterativeMeshSmoothingOptions`  
_L163-176_
- reflection: `USTRUCT(BlueprintType)`
- L168 _public member_ `int NumIterations = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L171 _public member_ `float Alpha = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L175 _public member_ `EGeometryScriptEmptySelectionBehavior EmptyBehavior = EGeometryScriptEmptySelectionBehavior::FullMeshSelection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — EmptyBehavior Defines how an empty input selection should be interpreted

#### struct `FGeometryScriptDisplaceFromTextureOptions`  
`struct FGeometryScriptDisplaceFromTextureOptions`  
_L182-204_
- reflection: `USTRUCT(BlueprintType)`
- L187 _public member_ `float Magnitude = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L190 _public member_ `FVector2D UVScale = FVector2D(1,1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L193 _public member_ `FVector2D UVOffset = FVector2D(0,0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L196 _public member_ `float Center = 0.5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L199 _public member_ `int ImageChannel = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L203 _public member_ `EGeometryScriptEmptySelectionBehavior EmptyBehavior = EGeometryScriptEmptySelectionBehavior::FullMeshSelection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — EmptyBehavior Defines how an empty input selection should be interpreted

#### enum `EGeometryScriptTessellationErrorMode`  
`enum class EGeometryScriptTessellationErrorMode : uint8`  
_L207-218_
- reflection: `UENUM(BlueprintType)`
- L212 _public enumerator_ `Absolute` — Target error specified in scene-units.
- L217 _public enumerator_ `Relative` — Scale-invariant tessellation detail, relative to object bounds.

#### struct `FGeometryScriptAdaptiveTessellationOptions`  
`struct FGeometryScriptAdaptiveTessellationOptions`  
_L221-259_
- reflection: `USTRUCT(BlueprintType)`
- L228 _public member_ `bool bEnableTessellation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L234 _public member_ `float ErrorTolerance = 5.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Primary parameter to controlling tessellation detail when using adaptive tessellation (lower values produce finer meshes). When mode is absolute, correspond to world units error.
- L240 _public member_ `EGeometryScriptTessellationErrorMode ErrorMode = EGeometryScriptTessellationErrorMode::Relative;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Control whether error criterion is related to world units (absolute) or object bounds (relative).
- L246 _public member_ `float FeatureSensitivity = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Value between 0 and 1 to control the amount of curvature sensitive refinement for approximation of high-frequency details.
- L252 _public member_ `bool bMeshOptimization = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to apply some mesh regularization as a post-process, to counter stretching or skinny triangles.
- L258 _public member_ `float Coplanarity = 0.8f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Value between 0 and 1 to control how coplanar faces adjacent to an edge need to be to allow edge flips. This should rarely need to be modified.

#### class `UGeometryScriptLibrary_MeshDeformFunctions`  
`class UGeometryScriptLibrary_MeshDeformFunctions : public UBlueprintFunctionLibrary`  
_L263-414_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshDeformers"))`
- inherits: `UBlueprintFunctionLibrary`
- L273 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyBendWarpToMesh( UDynamicMesh* TargetMesh, FGeometryScriptBendWarpOptions Options, FTransform BendOrientation, float BendAngle = 45, float BendExtent = 50, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta=(ScriptMethod, HidePin = "Debug"))` — Applies a Bend Warp around an axis defined by the Bend Orientation transform. The extents of the affected region can be controlled by the Options.
- L287 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyTwistWarpToMesh( UDynamicMesh* TargetMesh, FGeometryScriptTwistWarpOptions Options, FTransform TwistOrientation, float TwistAngle = 45, float TwistExtent = 50, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta=(ScriptMethod, HidePin = "Debug"))` — Applies a twist warp around an axis defined by the Twist Orientation transform. The extents of the affected region can be controlled by the Options.
- L302 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyFlareWarpToMesh( UDynamicMesh* TargetMesh, FGeometryScriptFlareWarpOptions Options, FTransform FlareOrientation, float FlarePercentX = 0, float FlarePercentY = 0, float FlareExtent = 50, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta=(ScriptMethod, HidePin = "Debug"))` — Applies a Flare/Bulge warp around an axis defined by the Flare Orientation transform. The amount of flare in the perpendicular directions can be controlled by FlarePercentX and FlarePercentY and the extents of the affected region can be controlled by the Options.
- L318 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMathWarpToMesh( UDynamicMesh* TargetMesh, FTransform WarpOrientation, EGeometryScriptMathWarpType WarpType, FGeometryScriptMathWarpOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta=(ScriptMethod, HidePin = "Debug"))` — Applies various simple math-function-based warps around an axis defined by the Warp Orientation transform, currently a 1D or 2D sine-wave with arbitrary orientation may be selected by WarpType.
- L332 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyPerlinNoiseToMesh2( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FGeometryScriptPerlinNoiseOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta = (ScriptMethod, DisplayName = "Apply Perlin Noise to Mesh", HidePin = "Debug"))` — Applies 3D Perlin noise displacement to the Target Mesh. @param Selection if non-empty, only the vertices identified by the selection will be displaced, otherwise the Options' EmptyBehavior will be followed.
- L343 _public prototype_ `static UPARAM(DisplayName = "Noise Values") FGeometryScriptScalarList ComputePerlinNoise(FGeometryScriptVectorList Positions, FGeometryScriptPerlinNoiseOptions Options);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta = (ScriptMethod))` — Compute Perlin Noise at the requested positions
- L352 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyIterativeSmoothingToMesh( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FGeometryScriptIterativeMeshSmoothingOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta=(ScriptMethod, HidePin = "Debug"))` — Applies a number of iterations of mesh smoothing to a Dynamic Mesh. @param Selection if non-empty, only the vertices identified by the selection will be subject to smoothing,  otherwise the Options' EmptyBehavior will be followed.
- L365 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyDisplaceFromTextureMap( UDynamicMesh* TargetMesh, UTexture2D* Texture, FGeometryScriptMeshSelection Selection, FGeometryScriptDisplaceFromTextureOptions Options, FGeometryScriptAdaptiveTessellationOptions TessellationOptions, UPARAM(DisplayName = "UV Channel") int32 UVLayer = 0, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta=(ScriptMethod, HidePin = "Debug"))` — Applies a displacement to a Dynamic Mesh based on a Texture2D and a UV Channel. @param Selection if non-empty, only the vertices identified by the selection will be subject to displacement,  otherwise the Options' EmptyBehavior will be followed.
- L381 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyDisplaceFromPerVertexVectors( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, const FGeometryScriptVectorList& VectorList, float Magnitude = 5.0, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta=(ScriptMethod, HidePin = "Debug"))` — Add the vectors in VectorList, scaled by Magnitude, to the vertex positions in Target Mesh. VectorList Length must be >= the MaxVertexID of the Target Mesh. @param Selection if non-empty, only the vertices identified by the selection will be displaced. The VectorList must still be the same size as the whole mesh, this is just a filter on which vertices are updated.
- L406 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyPerlinNoiseToMesh( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FGeometryScriptPerlinNoiseOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UE_DEPRECATED(5.7, "Use 'ApplyPerlinNoiseToMesh2' instead. This method is deprecated because it incorrectly squared the frequency parameter.")` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Compatibility", meta = (ScriptMethod, DeprecatedFunction, HidePin = "Debug", DeprecationMessage = "Use 'Apply Perlin Noise to Mesh' instead. This node is deprecated because it incorrectly squared the frequency parameter.", DisplayName="Apply Perlin Noise to Mesh Compatibility 5.6 (Deprecated)"))` — Applies 3D Perlin noise displacement to the Target Mesh, with Frequency parameter incorrectly squared. @param Selection if non-empty, only the vertices identified by the selection will be displaced, otherwise the Options' EmptyBehavior will be followed. @warning It is strongly recommended that callers of this function update to the current ApplyPerlinNoiseToMesh function!

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshGeodesicFunctions.h` (Public)


#### class `UGeometryScriptLibrary_MeshGeodesicFunctions`  
`class UGeometryScriptLibrary_MeshGeodesicFunctions : public UBlueprintFunctionLibrary`  
_L16-93_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshGeodesic"))`
- inherits: `UBlueprintFunctionLibrary`
- L33 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetShortestVertexPath( UDynamicMesh* TargetMesh, int32 StartVertexID, int32 EndVertexID, FGeometryScriptIndexList& VertexIDList, bool& bFoundErrors, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshGeodesic", meta=(ScriptMethod, HidePin = "Debug"))` — Computes a vertex list that represents the shortest path constrained to travel along mesh triangle edges between the prescribed start and end vertex. This can fail if the Start and End points are within separate connected components of the mesh. @param TargetMesh defines the surface where the path is computed. @param StartVertexID  indicates ID of mesh vertex that defines the starting point of the path. @param EndVertexID  indicates ID of the mesh vertex that defined the end point of the path. @param VertexIDList, if found this will hold on return a list of mesh vertex IDs that define the path from StartVertexID to EndVertexID. @param bFoundErrors will be false on success.
- L56 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetShortestSurfacePath( UDynamicMesh* TargetMesh, int32 StartTriangleID, FVector StartBaryCoords, int32 EndTriangleID, FVector EndBaryCoords, FGeometryScriptPolyPath& ShortestPath, bool& bFoundErrors, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshGeodesic", meta=(ScriptMethod, HidePin = "Debug"))` — Computes a PolyPath that represents the shortest mesh surface path between two prescribed points on the provided mesh. This can fail if the Start and End points are within separate connected components of the mesh. @param TargetMesh defines the surface where the path is computed. @param StartTriangleID the ID of mesh Triangle that contains the start point of the path. @param StartBaryCoords indicates the location of start point within the start triangle, in terms of barycentric coordinates. @param EndTriangleID the ID of mesh Triangle that contains the end point of the path. @param EndBaryCoords indicates the location of the end point within the end triangle, in terms of barycentric coordinates. @param ShortestPath, if found this will hold on return a PolyPath that defines the shortest path along the mesh surface connecting the start and end points. @param bFoundErrors, will be false on success. Note, Barycentric coordinates are of the form (a,b,c) where each entry is positive and a + b + c = 1. If the provided coordinates are invalid, the value (1/3, 1/3, 1/3) will be used.
- L82 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* CreateSurfacePath( UDynamicMesh* TargetMesh, FVector Direction, int32 StartTriangleID, FVector StartBaryCoords, float MaxPathLength, FGeometryScriptPolyPath& SurfacePath, bool& bFoundErrors, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshGeodesic", meta=(ScriptMethod, HidePin = "Debug"))` — Computes a PolyPath that represents a "straight" surface path starting at the prescribed point on the mesh, and continuing in the indicated direction until reaching the requested path length or encountering a mesh boundary, whichever comes first. @param TargetMesh defines the surface where the path is computed. @param Direction is a three-dimensional vector that is projected onto the mesh surface to determine the path direction. @param StartTriangleID the ID of mesh Triangle that contains the start point of the path. @param StartBaryCoords indicates the location of start point within the start triangle, in terms of barycentric coordinates. @param MaxPathLength sets the maximal length of the path, but the actual path may be shorter as it automatically terminates when encountering a mesh boundary edge. @param SurfacePath holds on return a PolyPath that forms a "straight" path along the mesh surface from the start position. @param bFoundErrors, will be false on success. Note, Barycentric coordinates are of the form (a,b,c) where each entry is positive and a + b + c = 1. If the provided coordinate is invalid, the value (1/3, 1/3, 1/3) will be used. Also, if the direction vector is nearly zero, the up-vector will be used.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshMaterialFunctions.h` (Public)


#### class `UGeometryScriptLibrary_MeshMaterialFunctions`  
`class UGeometryScriptLibrary_MeshMaterialFunctions : public UBlueprintFunctionLibrary`  
_L17-242_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_Materials"))`
- inherits: `UBlueprintFunctionLibrary`
- L23 _public prototype_ `static UPARAM(DisplayName = "Max ID") int GetMaxMaterialID( UDynamicMesh* TargetMesh, bool& bHasMaterial` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))`
- L30 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* EnableMaterialIDs( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta=(ScriptMethod, HidePin = "Debug"))` — Enables per-triangle Material IDs on a mesh and initializes the values to 0. If Target Mesh already has Material IDs, this function will do nothing.
- L38 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ClearMaterialIDs( UDynamicMesh* TargetMesh, int ClearValue = 0, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta=(ScriptMethod, HidePin = "Debug"))` — Resets all Material IDs on a mesh to the given ClearValue, or 0 if no ClearValue is provided. If Material IDs are not already enabled on the Target Mesh, this function will first enable them and then set the value.
- L45 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RemapMaterialIDs( UDynamicMesh* TargetMesh, int FromMaterialID, int ToMaterialID, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta=(ScriptMethod, HidePin = "Debug"))` — For all triangles with a Material ID matching the given value (From Material ID), update the Material ID to the new value (To Material ID).
- L62 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RemapToNewMaterialIDsByMaterial( UDynamicMesh* TargetMesh, const TArray<UMaterialInterface*>& FromMaterialList, const TArray<UMaterialInterface*>& ToMaterialList, int MissingMaterialID = -1, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta=(ScriptMethod, HidePin = "Debug"))` — Remap the Material IDs of the TargetMesh to a new set of Material IDs based on a 'From'/Current Material List, and a New Material List. For each triangle, the current Material is determined as FromMaterialList[MaterialID], and then the first index of this Material is found in the ToMaterialList, and this index is used as the new MaterialID If a Material cannot be found in ToMaterialList, a warning will be printed and the MaterialID left unmodified, unless MissingMaterialID is set to a value >= 0, in which case MissingMaterialID will be assigned
- L86 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RemapAndCombineMaterials( UDynamicMesh* TargetMesh, const TArray<UMaterialInterface*>& TargetMeshMaterials, const TArray<UMaterialInterface*>& RequiredMaterials, TArray<UMaterialInterface*>& CombinedMaterials, int RemapInvalidMaterialID = -1, bool bCompactDuplicateMaterials = true, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta = (ScriptMethod, HidePin = "Debug"))` — Remap material IDs to be consistent with a Required Materials list. The Target Mesh material IDs will be remapped to reference the Combined Materials list, which will always start with the Required Materials. If a Material cannot be found in CurrentMeshMaterials, a warning will be printed and the MaterialID left unmodified, unless RemapInvalidMaterialID is set to a value >= 0, in which case RemapInvalidMaterialID will be assigned @param TargetMesh Mesh to update @param TargetMeshMaterials Initial materials used by the TargetMesh @param RequiredMaterials Materials that must be used, unchanged, in the output @param CombinedMaterials Final materials used by the TargetMesh after remapping. Always starts with the RequiredMaterials. @param RemapInvalidMaterialID If >= 0, automatically remap invalid input material IDs to this value @param bCompactDuplicateMaterials If true, materials from TargetMeshMaterials will only be added if they are not already in RequiredMaterials. If false, all TargetMeshMaterials are appended.
- L102 _public prototype_ `static UPARAM(DisplayName = "Material ID") int32 GetTriangleMaterialID( UDynamicMesh* TargetMesh, int TriangleID, bool& bIsValidTriangle );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Materials", meta=(ScriptMethod, DisplayName="Get Material ID Of Triangle"))` — Returns the current Material ID for a Triangle. If the mesh does not have Material IDs enabled or if the Triangle ID is not an element of the mesh, the value 0 will be returned and bIsValidTriangle will be false.
- L111 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMaterialIDsOfTriangles( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "Triangle ID List") FGeometryScriptIndexList TriangleIDList, UPARAM(DisplayName = "Material ID List") FGeometryScriptIndexList& MaterialIDList, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Materials", meta=(ScriptMethod, HidePin = "Debug"))` — This populates the MaterialIDList with Material IDs for each triangle in the TriangleIDList. If a triangle is not present in the Target Mesh the number -1 will be used for the corresponding Material ID. If Material IDs are not enabled on the TargetMesh no Material IDs will be added to the result list.
- L124 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetAllTriangleMaterialIDs( UDynamicMesh* TargetMesh, FGeometryScriptIndexList& MaterialIDList, bool& bHasMaterialIDs );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Materials", meta=(ScriptMethod, DisplayName="Get Material IDs Of All Triangles"))` — Returns an Index List of all triangle Material IDs, constructed with one entry for each consecutive Triangle ID. If Material IDs are not enabled on the mesh, bHasMaterialsIDs will be set to false on return and nothing will be added to the Material ID List. @warning if the mesh is not Triangle-Compact (eg GetHasTriangleIDGaps == false) then the returned list will also have the same gaps where the number -1 will be recorded for any missing Triangle IDs.
- L131 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetTrianglesByMaterialID( UDynamicMesh* TargetMesh, int MaterialID, UPARAM(DisplayName = "Triangle ID List") FGeometryScriptIndexList& TriangleIDList, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Selection", meta=(ScriptMethod, HidePin = "Debug"))` — Populates Triangle ID List with the Triangle IDs of triangles that share the specified Material ID in the Target Mesh.
- L143 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetTriangleMaterialID( UDynamicMesh* TargetMesh, int TriangleID, int MaterialID, bool& bIsValidTriangle, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta=(ScriptMethod, DisplayName="Set Material ID On Triangle"))` — Assigns the specified triangle the given Material ID. If the Target Mesh does not have Material IDs enabled, or if the Triangle ID is not an element of the Target Mesh then bIsValidTriangle will be set to false.
- L157 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetAllTriangleMaterialIDs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "Triangle Material ID List") FGeometryScriptIndexList TriangleMaterialIDList, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta=(ScriptMethod, HidePin = "Debug", DisplayName="Set Material IDs On All Triangles"))` — Sets the Material ID of all triangles in a mesh to the values in an input Index List. @param TriangleMateralIDList the list of Material IDs, the length of this list should be the same as the Max Triangle ID for this mesh. @param bDeferChangeNotifications if true, the UDynamicMesh does not emit a change event/signal for this modification.
- L171 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMaterialIDOnTriangles( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "Triangle ID List") FGeometryScriptIndexList TriangleIDList, int MaterialID, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta=(ScriptMethod, HidePin = "Debug", DisplayName="Set Material ID On Triangles"))` — Assigns the Material ID to all the triangles specified by the Triangle ID List. @param TriangleIDList the triangles in the target mesh that will be updated with the new Material ID @param MaterialID the ID to be assigned to each triangle in the input list. @param bDeferChangeNotifications if true, the UDynamicMesh does not emit a change event/signal for this modification.
- L185 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMaterialIDForMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, int MaterialID, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta=(ScriptMethod, HidePin = "Debug", DisplayName="Set Material ID For Mesh Selection"))` — Set a new MaterialID on all the triangles of the given Selection. @param MaterialID new Material ID to set @param bDeferChangeNotifications if true, the UDynamicMesh does not emit a change event/signal for this modification
- L201 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetPolygroupMaterialID( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, UPARAM(DisplayName = "PolyGroup ID") int PolygroupID, int MaterialID, UPARAM(DisplayName = "Is Valid PolyGroup ID") bool& bIsValidPolygroupID, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta=(ScriptMethod, HidePin = "Debug", DisplayName = "Set PolyGroup Material ID"))` — Set a new MaterialID on all the triangles of TargetMesh with the given PolyGroup. @param GroupLayer PolyGroup Layer to use as basis for PolyGroups @param PolyGroupID PolyGroup ID that specifies Triangles to set to new MaterialID @param MaterialID explicit new MaterialID to set @param bDeferChangeNotifications if true, the UDynamicMesh does not emit a change event/signal for this modification
- L216 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* DeleteTrianglesByMaterialID( UDynamicMesh* TargetMesh, int MaterialID, int& NumDeleted, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta=(ScriptMethod, HidePin = "Debug"))` — Delete all triangles in TargetMesh with the given MaterialID @param NumDeleted number of deleted triangles is returned here
- L232 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* CompactMaterialIDs( UDynamicMesh* TargetMesh, TArray<UMaterialInterface*> SourceMaterialList, TArray<UMaterialInterface*>& CompactedMaterialList, bool bRemoveDuplicateMaterials = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Materials", meta=(ScriptMethod, HidePin = "Debug"))` — Compact the MaterialIDs of the TargetMesh, ie remove any un-used MaterialIDs and remap the remaining N in-use MaterialIDs to the range [0,N-1]. Optionally compute a Compacted list of Materials. @param SourceMaterialList Input Material list, assumption is that SourceMaterialList.Num() == number of MaterialIDs on mesh at input @param CompactedMaterialList new Compacted Material list, one-to-one with new compacted MaterialIDs @param bRemoveDuplicateMaterials Whether to also remove duplicate materials from the compacted list

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshModelingFunctions.h` (Public)


#### enum `EGeometryScriptMeshEditPolygroupMode`  
`enum class EGeometryScriptMeshEditPolygroupMode : uint8`  
_L16-21_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `PreserveExisting = 0`
- L19 _public enumerator_ `AutoGenerateNew = 1`
- L20 _public enumerator_ `SetConstant = 2`

#### struct `FGeometryScriptMeshEditPolygroupOptions`  
`struct FGeometryScriptMeshEditPolygroupOptions`  
_L24-33_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `EGeometryScriptMeshEditPolygroupMode GroupMode = EGeometryScriptMeshEditPolygroupMode::PreserveExisting;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L32 _public member_ `int ConstantGroup = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptMeshOffsetOptions`  
`struct FGeometryScriptMeshOffsetOptions`  
_L37-59_
- reflection: `USTRUCT(BlueprintType)`
- L42 _public member_ `float OffsetDistance = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L45 _public member_ `bool bFixedBoundary = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L48 _public member_ `int SolveSteps = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L51 _public member_ `float SmoothAlpha = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L54 _public member_ `bool bReprojectDuringSmoothing = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L58 _public member_ `float BoundaryAlpha = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — should not be > 0.9

#### enum `EGeometryScriptPolyOperationArea`  
`enum class EGeometryScriptPolyOperationArea : uint8`  
_L63-68_
- reflection: `UENUM(BlueprintType)`
- L65 _public enumerator_ `EntireSelection = 0`
- L66 _public enumerator_ `PerPolygroup = 1 UMETA(DisplayName = "Per PolyGroup")`
- L67 _public enumerator_ `PerTriangle = 2`

#### struct `FGeometryScriptMeshExtrudeOptions`  
`struct FGeometryScriptMeshExtrudeOptions`  
_L72-87_
- reflection: `USTRUCT(BlueprintType)`
- L77 _public member_ `float ExtrudeDistance = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L80 _public member_ `FVector ExtrudeDirection = FVector(0,0,1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L83 _public member_ `float UVScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L86 _public member_ `bool bSolidsToShells = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### enum `EGeometryScriptLinearExtrudeDirection`  
`enum class EGeometryScriptLinearExtrudeDirection : uint8`  
_L91-95_
- reflection: `UENUM(BlueprintType)`
- L93 _public enumerator_ `FixedDirection = 0`
- L94 _public enumerator_ `AverageFaceNormal = 1`

#### struct `FGeometryScriptMeshLinearExtrudeOptions`  
`struct FGeometryScriptMeshLinearExtrudeOptions`  
_L99-123_
- reflection: `USTRUCT(BlueprintType)`
- L104 _public member_ `float Distance = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L107 _public member_ `EGeometryScriptLinearExtrudeDirection DirectionMode = EGeometryScriptLinearExtrudeDirection::FixedDirection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L110 _public member_ `FVector Direction = FVector(0,0,1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L113 _public member_ `EGeometryScriptPolyOperationArea AreaMode = EGeometryScriptPolyOperationArea::EntireSelection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L116 _public member_ `FGeometryScriptMeshEditPolygroupOptions GroupOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L119 _public member_ `float UVScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L122 _public member_ `bool bSolidsToShells = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### enum `EGeometryScriptOffsetFacesType`  
`enum class EGeometryScriptOffsetFacesType : uint8`  
_L127-132_
- reflection: `UENUM(BlueprintType)`
- L129 _public enumerator_ `VertexNormal = 0`
- L130 _public enumerator_ `FaceNormal = 1`
- L131 _public enumerator_ `ParallelFaceOffset = 2`

#### struct `FGeometryScriptMeshOffsetFacesOptions`  
`struct FGeometryScriptMeshOffsetFacesOptions`  
_L135-156_
- reflection: `USTRUCT(BlueprintType)`
- L140 _public member_ `float Distance = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L143 _public member_ `EGeometryScriptOffsetFacesType OffsetType = EGeometryScriptOffsetFacesType::ParallelFaceOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L146 _public member_ `EGeometryScriptPolyOperationArea AreaMode = EGeometryScriptPolyOperationArea::EntireSelection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L149 _public member_ `FGeometryScriptMeshEditPolygroupOptions GroupOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L152 _public member_ `float UVScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L155 _public member_ `bool bSolidsToShells = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptMeshInsetOutsetFacesOptions`  
`struct FGeometryScriptMeshInsetOutsetFacesOptions`  
_L162-189_
- reflection: `USTRUCT(BlueprintType)`
- L167 _public member_ `float Distance = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L170 _public member_ `bool bReproject = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L173 _public member_ `bool bBoundaryOnly = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L176 _public member_ `float Softness = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L179 _public member_ `float AreaScale = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L182 _public member_ `EGeometryScriptPolyOperationArea AreaMode = EGeometryScriptPolyOperationArea::EntireSelection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L185 _public member_ `FGeometryScriptMeshEditPolygroupOptions GroupOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L188 _public member_ `float UVScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptMeshBevelOptions`  
`struct FGeometryScriptMeshBevelOptions`  
_L194-243_
- reflection: `USTRUCT(BlueprintType)`
- L200 _public member_ `float BevelDistance = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Distance that each beveled mesh edge is inset from it's initial position
- L204 _public member_ `bool bInferMaterialID = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true, when faces on either side of a beveled mesh edges have the same Material ID, beveled edge will be set to that Material ID. Otherwise SetMaterialID is used.
- L208 _public member_ `int SetMaterialID = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Material ID to set on the new faces introduced by bevel operation, unless bInferMaterialID=true and non-ambiguous MaterialID can be inferred from adjacent faces
- L212 _public member_ `int Subdivisions = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Number of edge loops added along the bevel faces
- L216 _public member_ `float RoundWeight = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Roundness of the bevel. Ignored if Subdivisions = 0.
- L223 _public member_ `bool bApplyFilterBox = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilterShape, AdvancedDisplay)` — If true the set of beveled PolyGroup edges is limited to those that are fully or partially contained within the (transformed) FilterBox
- L229 _public member_ `FBox FilterBox = FBox(EForceInit::ForceInit);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilterShape, AdvancedDisplay)` — Bounding Box used for edge filtering
- L235 _public member_ `FTransform FilterBoxTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilterShape, AdvancedDisplay)` — Transform applied to the FilterBox
- L242 _public member_ `bool bFullyContained = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilterShape, AdvancedDisplay)` — If true, then only PolyGroup edges that are fully contained within the filter box will be beveled, otherwise the edge will be beveled if any vertex is within the filter box.

#### enum `EGeometryScriptMeshBevelSelectionMode`  
`enum class EGeometryScriptMeshBevelSelectionMode : uint8`  
_L251-261_
- reflection: `UENUM(BlueprintType)`
- desc: Mode passed to ApplyMeshBevelSelection to control how the input Selection should be interpreted as selecting an area of the mesh to Bevel
- L254 _public enumerator_ `TriangleArea = 0` — Convert the selection to Triangles and bevel the boundary edge loops of the triangle set
- L256 _public enumerator_ `AllPolygroupEdges = 1 UMETA(DisplayName = "All PolyGroup Edges")` — Convert the selection to PolyGroups and bevel all the PolyGroup Edges of the selected PolyGroups
- L258 _public enumerator_ `SharedPolygroupEdges = 2 UMETA(DisplayName = "Shared PolyGroup Edges")` — Convert the selection to PolyGroups and bevel all the PolyGroup Edges that are between selected PolyGroups
- L260 _public enumerator_ `SelectedEdges = 3` — Convert the selection to Edges (if needed) and bevel them

#### struct `FGeometryScriptMeshBevelSelectionOptions`  
`struct FGeometryScriptMeshBevelSelectionOptions`  
_L265-288_
- reflection: `USTRUCT(BlueprintType)`
- L271 _public member_ `float BevelDistance = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Distance that each beveled mesh edge is inset from it's initial position
- L275 _public member_ `bool bInferMaterialID = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true, when faces on either side of a beveled mesh edges have the same Material ID, beveled edge will be set to that Material ID. Otherwise SetMaterialID is used.
- L279 _public member_ `int SetMaterialID = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Material ID to set on the new faces introduced by bevel operation, unless bInferMaterialID=true and non-ambiguous MaterialID can be inferred from adjacent faces
- L283 _public member_ `int Subdivisions = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Number of edge loops added along the bevel faces
- L287 _public member_ `float RoundWeight = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Roundness of the bevel. Ignored if Subdivisions = 0.

#### class `UGeometryScriptLibrary_MeshModelingFunctions`  
`class UGeometryScriptLibrary_MeshModelingFunctions : public UBlueprintFunctionLibrary`  
_L293-459_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshModeling"))`
- inherits: `UBlueprintFunctionLibrary`
- L304 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshDisconnectFaces( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, bool bAllowBowtiesInOutput = true, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Modeling", meta=(ScriptMethod, HidePin = "Debug"))` — Disconnect the triangles of TargetMesh identified by the Selection. The input Selection will still identify the same geometric elements after Disconnecting. @param bAllowBowtiesInOutput if false, any bowtie vertices created by the operation will be automatically split
- L319 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshDisconnectFacesAlongEdges( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Modeling", meta = (ScriptMethod, HidePin = "Debug"))` — Disconnect triangles of TargetMesh along the edges of the Selection. The input Selection will still identify the same geometric elements after Disconnecting. @param TargetMesh Mesh to operate on @param Selection Which edges to operate on. Non-edge selections will be interpreted as edge selections -- i.e., all selected triangles' edges, or all selected vertices' one-ring edges.
- L331 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshDuplicateFaces( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FGeometryScriptMeshSelection& NewTriangles, FGeometryScriptMeshEditPolygroupOptions GroupOptions = FGeometryScriptMeshEditPolygroupOptions(), UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Modeling", meta=(ScriptMethod, HidePin = "Debug"))` — Duplicate the triangles of TargetMesh identified by the Selection @param NewTriangles a Mesh Selection of the duplicate triangles is returned here (with type Triangles) @param bAllowBowtiesInOutput if false, any bowtie vertices resulting created in the Duplicate area will be disconnected into unique vertices
- L345 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshOffset( UDynamicMesh* TargetMesh, FGeometryScriptMeshOffsetOptions Options, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Modeling", meta=(ScriptMethod, HidePin = "Debug"))` — Offset the vertices of TargetMesh from their initial positions based on averaged vertex normals. This function is intended for high-res meshes, for polymodeling-style offsets, ApplyMeshOffsetFaces will produce better results.
- L356 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshShell( UDynamicMesh* TargetMesh, FGeometryScriptMeshOffsetOptions Options, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Modeling", meta=(ScriptMethod, HidePin = "Debug"))` — Create a thickened shell from TargetMesh by offsetting the vertex positions along averaged vertex normals, inwards or outwards. Similar to ApplyMeshOffset but also includes the initial mesh (possibly flipped, if the offset is positive)
- L368 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshLinearExtrudeFaces( UDynamicMesh* TargetMesh, FGeometryScriptMeshLinearExtrudeOptions Options, FGeometryScriptMeshSelection Selection, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Modeling", meta=(ScriptMethod, HidePin = "Debug"))` — Apply Linear Extrusion (ie extrusion in a single direction) to the triangles of TargetMesh identified by the Selection. The input Selection will still identify the same geometric elements after the Extrusion
- L380 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshOffsetFaces( UDynamicMesh* TargetMesh, FGeometryScriptMeshOffsetFacesOptions Options, FGeometryScriptMeshSelection Selection, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Modeling", meta=(ScriptMethod, HidePin = "Debug"))` — Apply an Offset to the faces of TargetMesh identified by the Selection, or all faces if the Selection is empty. The Offset direction at each vertex can be derived from the averaged vertex normals or per-triangle normals.
- L391 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshInsetOutsetFaces( UDynamicMesh* TargetMesh, FGeometryScriptMeshInsetOutsetFacesOptions Options, FGeometryScriptMeshSelection Selection, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Modeling", meta=(ScriptMethod, HidePin = "Debug"))` — Apply an Inset or Outset to the faces of TargetMesh identified by the Selection, or all faces if the Selection is empty.
- L404 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshBevelEdgeSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FGeometryScriptMeshBevelSelectionOptions BevelOptions, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Modeling", meta = (ScriptMethod, HidePin = "Debug"))` — Apply a Mesh Bevel operation to parts of TargetMesh using the BevelOptions settings. @param Selection specifies which mesh edges to Bevel @param BevelOptions settings for the Bevel Operation
- L418 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshBevelSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, EGeometryScriptMeshBevelSelectionMode BevelMode, FGeometryScriptMeshBevelSelectionOptions BevelOptions, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Modeling", meta=(ScriptMethod, HidePin = "Debug", DisplayName = "Apply Mesh Bevel Region Selection"))` — Apply a Mesh Bevel operation to parts of TargetMesh using the BevelOptions settings, with additional options to handle region selections @param Selection specifies which mesh edges to Bevel @param BevelMode specifies whether Selection should be optionally converted to a Triangle Region or set of PolyGroup Edges @param BevelOptions settings for the Bevel Operation
- L431 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshPolygroupBevel( UDynamicMesh* TargetMesh, FGeometryScriptMeshBevelOptions Options, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Modeling", meta=(ScriptMethod, HidePin = "Debug", DisplayName = "Apply Mesh PolyGroup Bevel"))` — Apply a Mesh Bevel operation to all PolyGroup Edges.
- L453 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshExtrude_Compatibility_5p0( UDynamicMesh* TargetMesh, FGeometryScriptMeshExtrudeOptions Options, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Compatibility", meta=(ScriptMethod, HidePin = "Debug"))`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshNormalsFunctions.h` (Public)


#### struct `FGeometryScriptCalculateNormalsOptions`  
`struct FGeometryScriptCalculateNormalsOptions`  
_L16-25_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `bool bAngleWeighted = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L24 _public member_ `bool bAreaWeighted = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptSplitNormalsOptions`  
`struct FGeometryScriptSplitNormalsOptions`  
_L30-45_
- reflection: `USTRUCT(BlueprintType)`
- L35 _public member_ `bool bSplitByOpeningAngle = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L38 _public member_ `float OpeningAngleDeg = 15.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L41 _public member_ `bool bSplitByFaceGroup = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L44 _public member_ `FGeometryScriptGroupLayer GroupLayer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### enum `EGeometryScriptTangentTypes`  
`enum class EGeometryScriptTangentTypes : uint8`  
_L49-55_
- reflection: `UENUM(BlueprintType)`
- L51 _public enumerator_ `FastMikkT = 0`
- L52 _public enumerator_ `PerTriangle = 1`
- L54 _public enumerator_ `StandardMikkT` — Standard MikkT-algorithm tangents. Available for windows/mac/linux platforms; will fall back to FastMikkT if unavailable.

#### struct `FGeometryScriptTangentsOptions`  
`struct FGeometryScriptTangentsOptions`  
_L59-68_
- reflection: `USTRUCT(BlueprintType)`
- L64 _public member_ `EGeometryScriptTangentTypes Type = EGeometryScriptTangentTypes::FastMikkT;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L67 _public member_ `int UVLayer = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### class `UGeometryScriptLibrary_MeshNormalsFunctions`  
`class UGeometryScriptLibrary_MeshNormalsFunctions : public UBlueprintFunctionLibrary`  
_L73-342_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_Normals"))`
- inherits: `UBlueprintFunctionLibrary`
- L82 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* FlipNormals( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug"))` — Flip/Invert the normal vectors of TargetMesh by multiplying them by -1, as well as reversing the mesh triangle orientations, ie triangle (a,b,c) becomes (b,a,c)
- L94 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* FlipTriangleSelectionNormals( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, bool bFlipTriangleOrientation = true, bool bFlipNormalDirection = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta = (ScriptMethod, HidePin = "Debug"))` — Flip/Invert the normal vectors of the triangles in a given selection of TargetMesh. For edge or vertex selections, normals for the triangles touching the selected edges or vertices will be flipped. @param bFlipTriangleOrientation If true, triangles are flipped by reversing the mesh triangle orientations, ie triangle (a,b,c) becomes (b,a,c) @param bFlipNormalDirection If true, normals of vertices on the selected triangles are flipped by multiplying them by -1
- L110 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AutoRepairNormals( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug"))` — Attempt to repair inconsistent normals in TargetMesh. Currently this is done in two passes. In the first pass, triangles with reversed orientation from their neighours are incrementally flipped until each connected component has a consistent orientation, if this is possible (note that this is not always globally possible, eg for a mobius-strip topology there is no consistent orientation). In the second pass, the "global" orientation is detected by casting rays from outside the mesh. This may produce incorrect results for meshes that are not closed.
- L120 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetPerVertexNormals( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug", DisplayName="Set Mesh To Per Vertex Normals (Computed)"))` — Recompute the normals of TargetMesh by averaging the triangle/face normals around each vertex, using combined area and angle weighting. Each vertex will have a single normal, ie there will be no hard edges.
- L130 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetPerFaceNormals( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug", DisplayName = "Set Mesh To Facet Normals"))` — Recompute the normals of TargetMesh by setting the normals of each triangle vertex to the triangle/face normal. Each vertex will have a unique normal in each triangle, ie there will be hard edges / split normals at every mesh edge
- L141 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RecomputeNormals( UDynamicMesh* TargetMesh, FGeometryScriptCalculateNormalsOptions CalculateOptions, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug"))` — Recompute the normals of TargetMesh using the given CalculateOptions. This method will preserve any existing hard edges, ie each shared triangle-vertex normal is recomputed by averaging the face normals of triangles that reference that shared triangle-vertex normal
- L154 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RecomputeNormalsForMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FGeometryScriptCalculateNormalsOptions CalculateOptions, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug"))` — Recompute the normals of TargetMesh on all the triangles/vertices of the given Selection using the given CalculateOptions. This method will preserve any existing hard edges, ie each shared triangle-vertex normal is recomputed by averaging the face normals of triangles that reference that shared triangle-vertex normal
- L168 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputeSplitNormals( UDynamicMesh* TargetMesh, FGeometryScriptSplitNormalsOptions SplitOptions, FGeometryScriptCalculateNormalsOptions CalculateOptions, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug"))` — Recompute hard edges / split-normals for TargetMesh based on the provided SplitOptions, and then recompute the new shared triangle-vertex normals using the given CalculateOptions. The normal recomputation is identical to calling RecomputeNormals.
- L185 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetSplitNormalsAlongSelectedEdges( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, bool bSplit = true, bool bRecalculateNormals = true, FGeometryScriptCalculateNormalsOptions CalculateOptions = FGeometryScriptCalculateNormalsOptions(), bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta = (ScriptMethod, HidePin = "Debug"))` — Set or remove split normals (aka sharp normals) for all edges in the Selection @param TargetMesh The mesh to update @param Selection Which edges to operate on @param bSplit Whether to split normals along the selected edges; if false, they will be merged instead @param bRecalculateNormals Whether to recalculate normals along edges where they were split/merged @param CalculateOptions Options for computing the normals, if bRecalculateNormals is true @param bDeferChangeNotifications If true, no mesh change notification will be sent. Set to true if performing many changes in a loop.
- L203 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshTriangleNormals( UDynamicMesh* TargetMesh, int TriangleID, FGeometryScriptTriangle Normals, bool& bIsValidTriangle, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod))` — Set the triangle-vertex normals for the given TriangleID on the TargetMesh. This will create unique triangle-vertex normals, ie it will create hard edges / split normals in the normal overlay for each edge of the triangle. @param bIsValidTriangle will be returned as false if TriangleID does not refer to a valid triangle @param bDeferChangeNotifications if true, no mesh change notification will be sent. Set to true if changing many normals in a loop.
- L216 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshPerVertexNormals( UDynamicMesh* TargetMesh, FGeometryScriptVectorList VertexNormalList, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug", DisplayName="Set Mesh To Per Vertex Normals (From List)"))` — Set all normals in the TargetMesh Normals Overlay to the specified per-vertex normals @param VertexNormalList per-vertex normals. Size must be equal to the MaxVertexID of TargetMesh  (ie non-compact TargetMesh is supported)
- L233 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMeshPerVertexNormals( UDynamicMesh* TargetMesh, FGeometryScriptVectorList& NormalList, bool& bIsValidNormalSet, bool& bHasVertexIDGaps, bool bAverageSplitVertexValues = true);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod))` — Get a list of single normal vectors for each mesh vertex in the TargetMesh, derived from the Normals Overlay. The Normals Overlay may store multiple normals for a single vertex (ie split normals) In such cases the normals can either be averaged, or the last normal seen will be used, depending on the bAverageSplitVertexValues parameter. @param NormalList output normal list will be stored here. Size will be equal to the MaxVertexID of TargetMesh  (not the VertexCount!) @param bIsValidNormalSet will be set to true if the Normal Overlay was valid @param bHasVertexIDGaps will be set to true if some vertex indices in TargetMesh were invalid, ie MaxVertexID > VertexCount @param bAverageSplitVertexValues control how multiple normals at the same vertex should be interpreted
- L247 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMeshHasTangents( UDynamicMesh* TargetMesh, bool& bHasTangents, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug"))` — Check if the TargetMesh has a Tangents Attribute Layer enabled
- L257 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* DiscardTangents( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug"))` — Remove any existing Tangents Attribute Layer from the TargetMesh
- L267 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputeTangents( UDynamicMesh* TargetMesh, FGeometryScriptTangentsOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug"))` — Recompute Tangents for the TargetMesh, using the method and settings specified by FGeometryScriptTangentsOptions @note If recomputing Tangents for use with a DynamicMeshComponent, it is also necessary to set the Tangents Type on the Component to "Externally Provided"
- L281 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshPerVertexTangents( UDynamicMesh* TargetMesh, FGeometryScriptVectorList TangentXList, FGeometryScriptVectorList TangentYList, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod, HidePin = "Debug"))` — Set all tangents in the TargetMesh Tangents Overlays to the specified per-vertex tangents @param TangentXList per-vertex tangent vectors. Size must be equal to the MaxVertexID of TargetMesh  (ie non-compact TargetMesh is supported) @param TangentYList per-vertex bitangent/binormal vectors. Size must be equal to TangentXList @note If setting Tangents for use with a DynamicMeshComponent, it is also necessary to set the Tangents Type on the Component to "Externally Provided"
- L299 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMeshPerVertexTangents( UDynamicMesh* TargetMesh, FGeometryScriptVectorList& TangentXList, FGeometryScriptVectorList& TangentYList, bool& bIsValidTangentSet, bool& bHasVertexIDGaps, bool bAverageSplitVertexValues = true);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Normals", meta=(ScriptMethod))` — Get a list of single tangent vectors for each mesh vertex in the TargetMesh, derived from the Tangents Overlays. The Tangents Overlay may store multiple tangents for a single vertex (ie split tangents) In such cases the tangents can either be averaged, or the last tangent seen will be used, depending on the bAverageSplitVertexValues parameter. @param TangentXList output Tangent "X" vectors list will be stored here. Size will be equal to the MaxVertexID of TargetMesh  (not the VertexCount!) @param TangentYList output Tangent "Y" vectors (Binormal/Bitangent) list will be stored here. Size will be equal to TangentXList @param bIsValidTangentSet will be set to true if the Tangent Overlay was valid @param bHasVertexIDGaps will be set to true if some vertex indices in TargetMesh were invalid, ie MaxVertexID > VertexCount @param bAverageSplitVertexValues control how multiple tangents at the same vertex should be interpreted
- L329 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* UpdateVertexNormal( UDynamicMesh* TargetMesh, int VertexID, bool bUpdateNormal, FVector NewNormal, bool bUpdateTangents, FVector NewTangentX, FVector NewTangentY, bool& bIsValidVertex, bool bMergeSplitValues, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod, bUpdateNormal="true"))` — Update the Normals and/or Tangents at VertexID of TargetMesh. Note that the specified vertex may have "split normals" or "split tangents", ie in the case of hard/crease normals, UV seams, and so on. In these situations, by default each of the unique normals/tangents at the vertex will be updated, but they will not be "merged", ie they will remain split. However if bMergeSplitValues=true, then the vertex will be "un-split", ie after the function call the vertex will have a single unique shared normal and/or tangents. Note that this function requires that some normals/tangents already exist on the TargetMesh. If this is not the case, functions like SetPerVertexNormals and ComputeTangents can be used to initialize the normals/tangents first. @param bUpdateNormal if true (default) then the normals overlay is updated @param NewNormal the new normal vector. This vector will not be normalized, it must be normalized by the calling code. @param bUpdateTangents if true then the tangents overlay will be updated. If the tangents overlay does not exist, this function returns an error. @param NewTangentX the new tangent vector. This vector will not be normalized, it must be normalized by the calling code. @param NewTangentY the new bitangent/binormal vector. This vector will not be normalized, it must be normalized by the calling code. @param bIsValidVertex will be set to true on return if the VertexID was valid, ie had valid normals and tangents @param bMergeSplitValues if true, any split

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshPolygroupFunctions.h` (Public)


#### class `UGeometryScriptLibrary_MeshPolygroupFunctions`  
`class UGeometryScriptLibrary_MeshPolygroupFunctions : public UBlueprintFunctionLibrary`  
_L17-284_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_PolyGroups"))`
- inherits: `UBlueprintFunctionLibrary`
- L25 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* EnablePolygroups( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Enable PolyGroups"))` — Enables the standard PolyGroup Layer on the Target Mesh.
- L32 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetNumExtendedPolygroupLayers( UDynamicMesh* TargetMesh, int NumLayers, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Set Num Extended PolyGroup Layers"))` — Sets the number of extended PolyGroup Layers on a Mesh.
- L47 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AddNamedPolygroupLayer( UDynamicMesh* TargetMesh, FName LayerName, FGeometryScriptGroupLayer& GroupLayer, bool& bAlreadyExisted, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Add Named PolyGroup Layer"))` — Add an extended polygroup layer with the given name. If a layer with that name is already on the mesh, that existing layer will be returned and no new layer will be added. @param TargetMesh Mesh to update @param LayerName Name of the PolyGroup layer @param GroupLayer PolyGroup layer with the requested name @param bAlreadyExisted If true, the layer already existed and did not need to be added (and the output GroupLayer will refer to that existing layer)
- L64 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") const UDynamicMesh* FindExtendedPolygroupLayerByName( const UDynamicMesh* TargetMesh, FName LayerName, FGeometryScriptGroupLayer &GroupLayer, EGeometryScriptSearchOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Find Extended PolyGroup Layer By Name", ExpandEnumAsExecs = "Outcome"))` — Find an extended PolyGroup layer by its name. If there are multiple layers with the same name, returns the first such layer. @param TargetMesh Mesh to search @param LayerName Name of the PolyGroup layer to find @param GroupLayer PolyGroup layer with the requested name (if Outcome is Success) @param Outcome Whether the requested layer was found
- L79 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ClearPolygroups( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, int ClearValue = 0, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Clear PolyGroups"))` — Resets the triangle PolyGroup assignments within a PolyGroup Layer to the given Clear Value (or 0 if no Clear Value is specified). Note, this will have no effect if PolyGroups have not been enabled on the mesh, or if the requested Group Layer does not exist.
- L91 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* CopyPolygroupsLayer( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer FromGroupLayer, FGeometryScriptGroupLayer ToGroupLayer, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Copy PolyGroups Layer"))` — Copies the triangle PolyGroup assignments from one layer on the Target Mesh to another. Note, this will have no effect if PolyGroups have not been enabled on the mesh, or if one of the requested Group Layers does not exist.
- L105 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ConvertUVIslandsToPolygroups( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, int UVLayer = 0, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Convert UV Islands To PolyGroups"))` — Creates and assigns a new PolyGroup for each disconnected UV island of a Mesh. Note, this will have no effect if either the requested UV Layer or Group Layer does not exist. @param GroupLayer indicates PolyGroup Layer that will be populated with unique values for each UV island. @param UVLayer specifies the UV Layer used to construct the PolyGroups.
- L118 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ConvertComponentsToPolygroups( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, HidePin = "Debug", KeyWords = "Components", DisplayName = "Convert Connected Islands To PolyGroups"))` — Creates and assigns a new PolyGroup for each disconnected island (component) of a Mesh. Regions of a mesh are disconnected they do not have a triangle in common. Note, this will have no effect if the Group Layer does not exist.
- L132 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputePolygroupsFromAngleThreshold( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, float CreaseAngle = 15, int MinGroupSize = 2, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Compute PolyGroups From Angle Threshold"))` — Sets PolyGroups by partitioning the mesh based on an edge crease/opening-angle. Note, this will have no effect if the Group Layer does not exist. @param GroupLayer indicates the PolyGroup Layer that will be populated. @param CreaseAngle measured in degrees and used when comparing adjacent faces. @param MinGroupSize the minimum number of triangles in each PolyGroup.
- L144 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputePolygroupsFromPolygonDetection( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, bool bRespectUVSeams = true, bool bRespectHardNormals = false, double QuadAdjacencyWeight = 1.0, double QuadMetricClamp = 1.0, int MaxSearchRounds = 1, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Compute PolyGroups From Polygon Detection"))` — Sets PolyGroups by identifying adjacent triangles that form reasonable quads. Note any triangles that do not neatly pair to form quads will receive their own PolyGroup.
- L163 _public prototype_ `static UPARAM(DisplayName = "PolyGroup ID") int32 GetTrianglePolygroupID( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, int TriangleID, bool& bIsValidTriangle );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, DisplayName = "Get Triangle PolyGroup ID"))` — Gets the PolyGroup ID associated with the specified Triangle ID and stored in the Group Layer. If the Group Layer or the Triangle does not exist, the value 0 will be returned and bIsValidTriangle set to false. @param GroupLayer indicates the layer on the Target Mesh to query. @param TriangleID identifies a triangle in the Target Mesh. @param bIsValidTriangle will be populated on return with false if either the Group Layer or the Triangle does not exist.
- L177 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* DeleteTrianglesInPolygroup( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, UPARAM(DisplayName = "PolyGroup ID") int PolygroupID, int& NumDeleted, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Delete Triangles In PolyGroup"))` — Deletes all triangles from the Target Mesh that have a particular PolyGroup ID, in the specific Group Layer. @param GroupLayer specifies the PolyGroup Layer to query. @param PolyGroup ID identifies the triangles in the Target Mesh to delete. @param NumDeleted on return will contain the number of triangles deleted from the Target Mesh.
- L191 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetAllTrianglePolygroupIDs( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, UPARAM(ref, DisplayName="PolyGroup IDs Out") FGeometryScriptIndexList& P` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, DisplayName = "Get All Triangle PolyGroup IDs"))` — Create list of per-triangle PolyGroup IDs for the PolyGroup in the Mesh @warning if the mesh is not Triangle-Compact (eg GetHasTriangleIDGaps == false) then the returned list will also have the same gaps
- L201 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetPolygroupIDsInMesh( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, UPARAM(ref, DisplayName="PolyGroup IDs Out") FGeometryScriptIndexList& P` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, DisplayName = "Get PolyGroup IDs In Mesh"))` — Create list of all unique PolyGroup IDs that exist in the PolyGroup Layer in the Mesh
- L215 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") const UDynamicMesh* GetPolyGroupBoundingBox(const UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, int32 GroupID, FBox& Bounds);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, DisplayName = "Get PolyGroup Bounding Box"))` — Compute the bounds of a PolyGroup @param GroupLayer The PolyGroup layer to query @param GroupID The PolyGroup to query @param Bounds The bounds of the PolyGroups's triangles. Can be invalid if the PolyGroup was not found.
- L230 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") const UDynamicMesh* GetPolyGroupUVBoundingBox(const UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, int32 GroupID, UPARAM(DisplayName = "UV Channel") int32 UVChannel, UPARAM(DisplayName = "UV Bounds") FBox2D& U` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, DisplayName = "Get PolyGroup UV Bounding Box"))` — Compute the UV bounds of a PolyGroup @param GroupLayer The PolyGroup layer to query @param GroupID The PolyGroup to query @param UVChannel The UV channel to query @param UVBounds The bounds of the PolyGroups's UV triangles. Can be invalid if the PolyGroup was not found or did not have UVs in the requested channel.
- L247 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") const UDynamicMesh* GetPolyGroupUVCentroid(const UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, int32 GroupID, UPARAM(DisplayName = "UV Channel") int32 UVChannel, FVector2D& Centroid, bool& bIsValid);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, DisplayName = "Get PolyGroup UV Centroid"))` — Compute the UV centroid of a PolyGroup @param GroupLayer The PolyGroup layer to query @param GroupID The PolyGroup to query @param UVChannel The UV channel to query @param Centroid The centroid of the polygroup's UV triangles @param bIsValid True if a valid centroid was found, false otherwise. Can be false if the PolyGroup was not found or did not have UVs in the requested channel.
- L259 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetTrianglesInPolygroup( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, UPARAM(DisplayName = "PolyGroup ID") int PolygroupID, UPARAM(ref, DisplayName="Triangle IDs Out") FGeometryScriptIndexList& T` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, DisplayName = "Get Triangles In PolyGroup"))` — Create list of all triangles with the given PolyGroup ID in the given GroupLayer (not necessarily a single connected-component / island)
- L275 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetPolygroupForMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, FGeometryScriptMeshSelection Selection, UPARAM(DisplayName = "Set PolyGroup ID Out") int& SetPolygroupIDOut, UPARAM(DisplayName = "Set PolyGroup ID") int SetPolygroupID = 0, UPARAM(DisplayName = " Generate New PolyGroup") bool bGenerateNewPolygroup = false, bool bDeferChangeNotifications = false);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, DisplayName = "Set PolyGroup For Mesh Selection"))` — Set a new PolyGroup on all the triangles of the given Selection, for the given GroupLayer. @param SetPolygroupID explicit new PolyGroupID to set @param bGenerateNewPolygroup if true, SetPolyGroupID is ignored and a new unique PolyGroupID is generated @param SetPolygroupIDOut the PolyGroupID that was set on the triangles is returned here (whether explicit or auto-generated) @param bDeferChangeNotifications if true, the UDynamicMesh does not emit a change event/signal for this modification

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshPoolFunctions.h` (Public)


#### class `UGeometryScriptLibrary_MeshPoolFunctions`  
`class UGeometryScriptLibrary_MeshPoolFunctions : public UBlueprintFunctionLibrary`  
_L15-28_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshPoolUtility"))`
- inherits: `UBlueprintFunctionLibrary`
- L22 _public prototype_ `static UPARAM(DisplayName = "Mesh Pool") UDynamicMeshPool* GetGlobalMeshPool();` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshPool")` — Access a global compute mesh pool (created on first access)
- L27 _public prototype_ `static void DiscardGlobalMeshPool();` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshPool")` — Fully clear/destroy the current global mesh pool, allowing it and all its meshes to be garbage collected

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshPrimitiveFunctions.h` (Public)


#### enum `EGeometryScriptPrimitivePolygroupMode`  
`enum class EGeometryScriptPrimitivePolygroupMode : uint8`  
_L14-19_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `SingleGroup = 0`
- L17 _public enumerator_ `PerFace = 1`
- L18 _public enumerator_ `PerQuad = 2`

#### enum `EGeometryScriptPrimitiveOriginMode`  
`enum class EGeometryScriptPrimitiveOriginMode : uint8`  
_L22-26_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `Center = 0`
- L25 _public enumerator_ `Base = 1`

#### enum `EGeometryScriptPrimitiveUVMode`  
`enum class EGeometryScriptPrimitiveUVMode : uint8`  
_L29-33_
- reflection: `UENUM(BlueprintType)`
- L31 _public enumerator_ `Uniform = 0`
- L32 _public enumerator_ `ScaleToFill = 1`

#### enum `EGeometryScriptPolygonFillMode`  
`enum class EGeometryScriptPolygonFillMode : uint8`  
_L36-50_
- reflection: `UENUM(BlueprintType)`
- L39 _public enumerator_ `All = 0` — Keep all triangles, regardless of whether they were enclosed by constrained edges
- L41 _public enumerator_ `Solid = 1` — Fill everything inside the outer boundaries of constrained edges, ignoring edge orientation and any internal holes
- L43 _public enumerator_ `PositiveWinding = 2` — Fill where the 'winding number' is positive
- L45 _public enumerator_ `NonZeroWinding = 3` — Fill where the 'winding number' is not zero
- L47 _public enumerator_ `NegativeWinding = 4` — Fill where the 'winding number' is negative
- L49 _public enumerator_ `OddWinding = 5` — Fill where the 'winding number' is an odd number

#### struct `FGeometryScriptPrimitiveOptions`  
`struct FGeometryScriptPrimitiveOptions`  
_L54-70_
- reflection: `USTRUCT(BlueprintType)`
- L59 _public member_ `EGeometryScriptPrimitivePolygroupMode PolygroupMode = EGeometryScriptPrimitivePolygroupMode::PerFace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (DisplayName = "PolyGroup Mode"))`
- L62 _public member_ `bool bFlipOrientation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L65 _public member_ `EGeometryScriptPrimitiveUVMode UVMode = EGeometryScriptPrimitiveUVMode::Uniform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L69 _public member_ `int32 MaterialID = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Material ID to set on primitive mesh triangles

#### struct `FGeometryScriptRevolveOptions`  
`struct FGeometryScriptRevolveOptions`  
_L74-98_
- reflection: `USTRUCT(BlueprintType)`
- L79 _public member_ `float RevolveDegrees = 360.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L82 _public member_ `float DegreeOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L85 _public member_ `bool bReverseDirection = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L88 _public member_ `bool bHardNormals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L91 _public member_ `float HardNormalAngle = 30.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L94 _public member_ `bool bProfileAtMidpoint = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L97 _public member_ `bool bFillPartialRevolveEndcaps = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptVoronoiOptions`  
`struct FGeometryScriptVoronoiOptions`  
_L101-118_
- reflection: `USTRUCT(BlueprintType)`
- L106 _public member_ `float BoundsExpand = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L109 _public member_ `FBox Bounds = FBox(EForceInit::ForceInit);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L113 _public member_ `TArray<int32> CreateCells;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Optional list of cells to create meshes for.  If empty, create all cells.
- L117 _public member_ `bool bIncludeBoundary = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to include the bordering Voronoi cells (which extend 'infinitely' to any boundary)

#### struct `FGeometryScriptConstrainedDelaunayTriangulationOptions`  
`struct FGeometryScriptConstrainedDelaunayTriangulationOptions`  
_L122-141_
- reflection: `USTRUCT(BlueprintType)`
- L128 _public member_ `EGeometryScriptPolygonFillMode ConstrainedEdgesFillMode = EGeometryScriptPolygonFillMode::All;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — How to decide which parts of the shape defined by constrained edges should be filled with triangles
- L135 _public member_ `bool bValidateEdgesInResult = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether the triangulation should be considered a failure if it doesn't include the requested Constrained Edges. (Edges may be missing e.g. due to intersecting edges in the input.)
- L139 _public member_ `bool bRemoveDuplicateVertices = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to remove duplicate vertices from the output.  If false, duplicate vertices will not be used in any triangles, but will remain in the output mesh.

#### struct `FGeometryScriptPolygonsTriangulationOptions`  
`struct FGeometryScriptPolygonsTriangulationOptions`  
_L145-154_
- reflection: `USTRUCT(BlueprintType)`
- L152 _public member_ `bool bStillAppendOnTriangulationError = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to still append the triangulation in error cases -- typically, cases where the input contained intersecting edges. Resulting triangulation likely will appear correct except at the intersecting edges.

#### class `UGeometryScriptLibrary_MeshPrimitiveFunctions`  
`class UGeometryScriptLibrary_MeshPrimitiveFunctions : public UBlueprintFunctionLibrary`  
_L158-851_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_Primitives"))`
- inherits: `UBlueprintFunctionLibrary`
- L167 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendBox( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float DimensionX = 100, float DimensionY = 100, float DimensionZ = 100, int32 StepsX = 0, int32 StepsY = 0, int32 StepsZ = 0, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Base, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a 3D box to the Target Mesh.
- L186 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendBoxWithCollision( UDynamicMesh* TargetMesh, FGeometryScriptSimpleCollision &SimpleCollision, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float DimensionX = 100, float DimensionY = 100, float DimensionZ = 100, int32 StepsX = 0, int32 StepsY = 0, int32 StepsZ = 0, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Base, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta = (ScriptMethod, HidePin = "Debug"))` — Appends a 3D box to the Target Mesh Also creates matching simple collision
- L205 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendBoundingBox( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, FBox Box, int32 StepsX = 0, int32 StepsY = 0, int32 StepsZ = 0, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a 3D box to the Target Mesh with dimensions and origin taken from the input Box
- L220 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendOrientedBox( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, FOrientedBox Box, int32 StepsX = 0, int32 StepsY = 0, int32 StepsZ = 0, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta = (ScriptMethod, HidePin = "Debug"))` — Appends a 3D oriented box to the Target Mesh
- L236 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendOrientedBoxWithCollision( UDynamicMesh* TargetMesh, FGeometryScriptSimpleCollision& SimpleCollision, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, FOrientedBox Box, int32 StepsX = 0, int32 StepsY = 0, int32 StepsZ = 0, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta = (ScriptMethod, HidePin = "Debug"))` — Appends a 3D oriented box to the Target Mesh Also creates matching simple collision
- L253 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendBoundingBoxWithCollision( UDynamicMesh* TargetMesh, FGeometryScriptSimpleCollision& SimpleCollision, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, FBox Box, int32 StepsX = 0, int32 StepsY = 0, int32 StepsZ = 0, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a 3D box to the Target Mesh with dimensions and origin taken from the input Box Also creates matching simple collision
- L270 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendSphereLatLong( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float Radius = 50, int32 StepsPhi = 10, int32 StepsTheta = 16, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Center, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a 3D Sphere triangulated using latitude/longitude topology to the Target Mesh.
- L287 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendSphereLatLongWithCollision( UDynamicMesh* TargetMesh, FGeometryScriptSimpleCollision& SimpleCollision, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float Radius = 50, int32 StepsPhi = 10, int32 StepsTheta = 16, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Center, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a 3D Sphere triangulated using latitude/longitude topology to the Target Mesh. Also creates matching simple collision. Note: If transform has non-uniform scale, collision shape will be a uniform-scale approximation matching the behavior of the physics system -- specifically, it will scale the sphere radius by the smallest axis scale.
- L303 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendSphereBox( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float Radius = 50, int32 StepsX = 6, int32 StepsY = 6, int32 StepsZ = 6, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Center, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a 3D sphere triangulated using box topology to the Target Mesh.
- L321 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendSphereBoxWithCollision( UDynamicMesh* TargetMesh, FGeometryScriptSimpleCollision& SimpleCollision, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float Radius = 50, int32 StepsX = 6, int32 StepsY = 6, int32 StepsZ = 6, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Center, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta = (ScriptMethod, HidePin = "Debug"))` — Appends a 3D sphere triangulated using box topology to the Target Mesh. Also creates matching simple collision. Note: If transform has non-uniform scale, collision shape will be a uniform-scale approximation matching the behavior of the physics system -- specifically, it will scale the sphere radius by the smallest axis scale.
- L338 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendCapsule( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float Radius = 30, float LineLength = 75, int32 HemisphereSteps = 5, int32 CircleSteps = 8, int32 SegmentSteps = 0, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Base, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a 3D Capsule to the Target Mesh.
- L357 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendCapsuleWithCollision( UDynamicMesh* TargetMesh, FGeometryScriptSimpleCollision& SimpleCollision, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float Radius = 30, float LineLength = 75, int32 HemisphereSteps = 5, int32 CircleSteps = 8, int32 SegmentSteps = 0, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Base, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a 3D Capsule to the Target Mesh. Also creates matching simple collision. Note: If transform has non-uniform scale, collision shape will be a uniform-scale approximation matching the behavior of the physics system -- specifically, it will scale the radius by the larger of the X, Y axis scales, and the length by the Z axis scale
- L373 _public function_ `static UDynamicMesh* AppendCapsule( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float Radius = 30, float LineLength = 75, int32 HemisphereSteps = 5, int32 CircleSteps = 8, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Base, UGeometryScriptDebug* Debug = nullptr)` — `UE_DEPRECATED(5.5, "Use AppendCapsule with the SegmentSteps parameter, instead")` — Version of append capsule without SegmentSteps parameter
- L391 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendCylinder( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float Radius = 50, float Height = 100, int32 RadialSteps = 12, int32 HeightSteps = 0, bool bCapped = true, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Base, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a 3D Cylinder (with optional end caps) to the Target Mesh.
- L408 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendCone( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float BaseRadius = 50, float TopRadius = 5, float Height = 100, int32 RadialSteps = 12, int32 HeightSteps = 4, bool bCapped = true, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Base, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a 3D cone to the Target Mesh.
- L426 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendTorus( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, FGeometryScriptRevolveOptions RevolveOptions, float MajorRadius = 50, float MinorRadius = 25, int32 MajorSteps = 16, int32 MinorSteps = 8, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Base, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a 3D torus (donut) or partial torus to the Target Mesh.
- L445 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendRevolvePolygon( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const TArray<FVector2D>& PolygonVertices, FGeometryScriptRevolveOptions RevolveOptions, float Radius = 100, int32 Steps = 8, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — In the coordinate system of the revolve polygon, +X is towards the "outside" of the revolve donut, and +Y is "up" (ie +Z in local space) Polygon should be oriented counter-clockwise to produce a correctly-oriented shape, otherwise it will be inside-out Polygon endpoint is not repeated.
- L460 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendSpiralRevolvePolygon( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const TArray<FVector2D>& PolygonVertices, FGeometryScriptRevolveOptions RevolveOptions, float Radius = 100, int Steps = 18, float RisePerRevolution = 50, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta = (ScriptMethod, HidePin = "Debug"))` — Revolves a 2D polygon on a helical path, like one used to create a vertical spiral, appending the result to the Target Mesh.
- L476 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendRevolvePath( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const TArray<FVector2D>& PathVertices, FGeometryScriptRevolveOptions RevolveOptions, int32 Steps = 8, bool bCapped = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Revolves an open 2D path, with optional top and bottom end caps, appending the result to the Target Mesh.
- L502 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendSweepPolyline( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const TArray<FVector2D>& PolylineVertices, const TArray<FTransform>& SweepPath, const TArray<float>& PolylineTexParamU, const TArray<float>& SweepPathTexParamV, bool bLoop = false, float StartScale = 1.0f, float EndScale = 1.0f, float RotationAngleDeg = 0.0f, float MiterLimit = 1.0f, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug", AutoCreateRefTerm="PolylineTexParamU, SweepPathTexParamV"))` — Sweep the given 2D PolylineVertices along the SweepPath specified as a set of FTransforms If the 2D vertices are (U,V), then in the coordinate space of the FTransform, X points "along" the path, Y points "right" (U) and Z points "up" (V). @param PolylineVertices vertices of the open 2D path that will be swept along the SweepPath @param SweepPath defines the 3D sweep path curve as a 3D poly-path, with rotation and scaling at each polypath vertex taken from the Transform @param PolylineTexParamU defines U coordinate value for each element in PolylineVertices. Must be same length as PolylineVertices (ignored if length=0). @param SweepPathTexParamV defines V coordinate value for each element in SweepPath. Must be same length as SweepPath if bLoop=false, length+1 if bLoop=true, and ignored if length=0. @param bLoop if true, SweepPath is considered to be a Loop and a section connecting the end and start of the path is added (bCapped is ignored) @param StartScale uniform scaling applied to the 2D polygon at the start of the path. Interpolated via arc length to EndScale at the end of the path. @param EndScale uniform scaling applied to the 2D polygon at the end of the path @param RotationAngleDeg Rotation applied to the 2D Polygon. Positive rotation rotates clockwise, ie Up/+Z/+V towards Right/+Y/+U. This Rotation is applied before any rotation in the SweepPath Transforms. @param MiterLimit If > 1, maximum scaling to apply at sharp turns in the curve path to keep the apparent swept p
- L523 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendSimpleExtrudePolygon( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const TArray<FVector2D>& PolygonVertices, float Height = 100, int32 HeightSteps = 0, bool bCapped = true, EGeometryScriptPrimitiveOriginMode Origin = EGeometryScriptPrimitiveOriginMode::Base, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Polygon should be oriented counter-clockwise to produce a correctly-oriented shape, otherwise it will be inside-out Polygon endpoint is not repeated.
- L547 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendSimpleSweptPolygon( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const TArray<FVector2D>& PolygonVertices, const TArray<FVector>& SweepPath, bool bLoop = false, bool bCapped = true, float StartScale = 1.0f, float EndScale = 1.0f, float RotationAngleDeg = 0.0f, float MiterLimit = 1.0f, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Sweeps a 2D polygon along an arbitrary 3D path, appending the result to the Target Mesh. @param PolygonVertices vertices of the closed 2D polyon that will be swept along the SweepPath @param SweepPath defines the 3D sweep path curve @param bLoop if true, SweepPath is considered to be a Loop and a section connecting the end and start of the path is added (bCapped is ignored) @param bCapped if true the open ends of the swept generalized cylinder are triangulated @param StartScale uniform scaling applied to the 2D polygon at the start of the path. Interpolated via arc length to EndScale at the end of the path. @param EndScale uniform scaling applied to the 2D polygon at the end of the path @param RotationAngleDeg Rotation applied to the 2D Polygon. Positive rotation rotates clockwise, ie Up/+Z/+V towards Right/+Y/+U @param MiterLimit If > 1, maximum scaling to apply at sharp turns in the curve path to keep the apparent swept profile from shrinking
- L576 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendSweepPolygon( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const TArray<FVector2D>& PolygonVertices, const TArray<FTransform>& SweepPath, bool bLoop = false, bool bCapped = true, float StartScale = 1.0f, float EndScale = 1.0f, float RotationAngleDeg = 0.0f, float MiterLimit = 1.0f, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Sweep the given 2D PolygonVertices along the SweepPath specified as a set of FTransforms If the 2D vertices are (U,V), then in the coordinate space of the FTransform, X points "along" the path, Y points "right" (U) and Z points "up" (V). @param PolygonVertices vertices of the closed 2D polyon that will be swept along the SweepPath @param SweepPath defines the 3D sweep path curve as a 3D poly-path, with rotation and scaling at each polypath vertex taken from the Transform @param bLoop if true, SweepPath is considered to be a Loop and a section connecting the end and start of the path is added (bCapped is ignored) @param bCapped if true the open ends of the swept generalized cylinder are triangulated @param StartScale uniform scaling applied to the 2D polygon at the start of the path. Interpolated via arc length to EndScale at the end of the path. @param EndScale uniform scaling applied to the 2D polygon at the end of the path @param RotationAngleDeg Rotation applied to the 2D Polygon. Positive rotation rotates clockwise, ie Up/+Z/+V towards Right/+Y/+U. This Rotation is applied before any rotation in the SweepPath Transforms. @param MiterLimit If > 1, maximum scaling to apply at sharp turns in the curve path to keep the apparent swept profile from shrinking, and sweep path frames will be aligned to the path direction
- L596 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendRectangleXY( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float DimensionX = 100, float DimensionY = 100, int32 StepsWidth = 0, int32 StepsHeight = 0, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a planar Rectangle to a Dynamic Mesh.
- L611 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendRoundRectangleXY( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float DimensionX = 100, float DimensionY = 100, float CornerRadius = 5, int32 StepsWidth = 0, int32 StepsHeight = 0, int32 StepsRound = 4, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a planar Rectangle with Rounded Corners (RoundRect) to the Target Mesh.
- L628 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendDisc( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float Radius = 50, int32 AngleSteps = 16, int32 SpokeSteps = 0, float StartAngle = 0, float EndAngle = 360, float HoleRadius = 0, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a planar disc to the Target Mesh.
- L647 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendTriangulatedPolygon( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const TArray<FVector2D>& PolygonVertices, bool bAllowSelfIntersections = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a Triangulated Polygon to the Target Mesh. Polygon should be oriented counter-clockwise to produce a correctly-oriented shape, otherwise it will be inside-out Polygon endpoint is not repeated.
- L663 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendTriangulatedPolygon3D( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const TArray<FVector>& PolygonVertices3D, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta = (ScriptMethod, HidePin = "Debug"))` — Appends a Triangulated Polygon (with vertices specified in 3D) to the Target Mesh. Uses Ear Clipping-based triangulation. Output vertices will always be 1:1 with input vertices. Polygon endpoint is not repeated.
- L675 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendLinearStairs( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float StepWidth = 100.0f, float StepHeight = 20.0f, float StepDepth = 30.0f, int NumSteps = 8, bool bFloating = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a linear staircase to the Target Mesh.
- L691 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendCurvedStairs( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float StepWidth = 100.0f, float StepHeight = 20.0f, float InnerRadius = 150.0f, float CurveAngle = 90.0f, int NumSteps = 8, bool bFloating = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta=(ScriptMethod, HidePin = "Debug"))` — Appends a rising circular staircase to the Target Mesh.
- L708 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendVoronoiDiagram2D( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const TArray<FVector2D>& VoronoiSites, FGeometryScriptVoronoiOptions VoronoiOptions, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta = (ScriptMethod, HidePin = "Debug"))` — Generates triangulated Voronoi Cells from the provided Voronoi Sites, identifying each with PolyGroups, and appends to the Target Mesh.
- L724 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendDelaunayTriangulation2D( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const TArray<FVector2D>& VertexPositions, const TArray<FIntPoint>& ConstrainedEdges, FGeometryScriptConstrainedDelaunayTriangulationOptions TriangulationOptions, TArray<int32>& PositionsToVertexIDs, bool& bHasDuplicateVertices, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta = (ScriptMethod, HidePin = "Debug", AutoCreateRefTerm = "ConstrainedEdges"))` — Generates a Delaunay Triangulation of the provided vertices, and appends it to the Target Mesh. If optional Constrained Edges are provided, will generate a Constrained Delaunay Triangulation which connects the specified vertices with edges. On success, all vertices are always appended to the output mesh, though duplicate vertices will not be used in any triangles and may optionally be removed. Use PositionsToVertexIDs to map indices in the input VertexPositions array to vertex IDs in the Dynamic Mesh.
- L742 _public prototype_ `static TArray<FIntPoint> CreateConstrainedEdgesLoop(int32 NumVertices, int32 Start = 0);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives")` — Intended for use with AppendDelaunayTriangulation2D: Create a loop of edges through sequential vertices e.g., a Loop(3,0) will construct edges (2,0), (0,1) and (1,2)
- L750 _public prototype_ `static TArray<FIntPoint> CreateConstrainedEdgesChain(int32 NumVertices, int32 Start = 0);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives")` — Intended for use with AppendDelaunayTriangulation2D: Create a chain of edges through sequential vertices e.g., a Chain(3,0) will construct edges (0,1) and (1,2)
- L759 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendPolygonListTriangulation( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, FGeometryScriptGeneralPolygonList PolygonList, FGeometryScriptPolygonsTriangulationOptions TriangulationOptions, bool& bTriangulationError, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta = (HidePin = "Debug"))` — Generates a Delaunay Triangulation of the provided Polygon List, and appends it to the Target Mesh. @param bTriangulationError Reports whether the triangulation contains errors, typically due to intersecting edges in the input. Consider pre-processing the PolygonsList with PolygonsUnion to resolve intersections and prevent this error. @param bStillAppendOnError Whether to still append a best-effort triangulation in error cases. Often this will be a triangulation that does not quite match the polygon shape near intersecting edges in the input, but otherwise is as-expected.
- L775 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendSimpleCollisionShapes( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const FGeometryScriptSimpleCollision& SimpleCollision, FGeometryScriptSimpleCollisionTriangulationOptions TriangulationOptions, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, DisplayName = "Append Simple Collision Shapes to Mesh", Category = "GeometryScript|Primitives", meta = (HidePin = "Debug"))` — Appends Simple Collision shapes to the Target Mesh, triangulated as specified by Triangulation Options @param Transform Transform to be applied to simple collision shapes, following the method by which simple collision shapes are transformed -- so, e.g., spheres will not be non-uniformly scaled
- L789 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendSphereCovering( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, const FGeometryScriptSphereCovering& SphereCovering, int32 StepsX = 6, int32 StepsY = 6, int32 StepsZ = 6, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Primitives", meta = (HidePin = "Debug"))` — Appends the spheres in the Sphere Covering to the Target Mesh
- L820 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendRectangle_Compatibility_5_0( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float DimensionX = 100, float DimensionY = 100, int32 StepsWidth = 0, int32 StepsHeight = 0, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Compatibility", meta=(ScriptMethod, HidePin = "Debug"))` — 5.0 Preview 1 Compatibility version of AppendRectangleXY. Incorrectly interprets the input dimensions. Incorrectly divides the input DimensionX and DimensionY by 2. @warning It is strongly recommended that callers of this function update to the current AppendRectangleXY function!
- L838 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendRoundRectangle_Compatibility_5_0( UDynamicMesh* TargetMesh, FGeometryScriptPrimitiveOptions PrimitiveOptions, FTransform Transform, float DimensionX = 100, float DimensionY = 100, float CornerRadius = 5, int32 StepsWidth = 0, int32 StepsHeight = 0, int32 StepsRound = 4, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Compatibility", meta=(ScriptMethod, HidePin = "Debug"))` — 5.0 Preview 1 Compatibility version of AppendRoundRectangleXY. Incorrectly divides the input DimensionX and DimensionY by 2. @warning It is strongly recommended that callers of this function update to the current AppendRoundRectangleXY function!

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshQueryFunctions.h` (Public)


#### class `UGeometryScriptLibrary_MeshQueryFunctions`  
`class UGeometryScriptLibrary_MeshQueryFunctions : public UBlueprintFunctionLibrary`  
_L16-488_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshQueries"))`
- inherits: `UBlueprintFunctionLibrary`
- L25 _public prototype_ `static FString GetMeshInfoString( UDynamicMesh* TargetMesh );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns information about the Target Mesh, such as the vertex and triangle count as well as some attribute information.
- L32 _public prototype_ `static bool GetIsDenseMesh( UDynamicMesh* TargetMesh );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns true if the mesh is dense. For example, no gaps in Vertex IDs or Triangle IDs. Note if a mesh is not dense, the Compact Mesh node can be used to removed the gaps.
- L38 _public prototype_ `static bool GetMeshHasAttributeSet( UDynamicMesh* TargetMesh );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns true if the Target Mesh has attributes enabled.
- L44 _public prototype_ `static UPARAM(DisplayName = "Bounding Box") FBox GetMeshBoundingBox( UDynamicMesh* T` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Computes the bounding box of the mesh vertices in the local space of the mesh.
- L50 _public prototype_ `static void GetMeshVolumeArea( UDynamicMesh* TargetMesh, float& SurfaceArea, float& Volume );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Computes the volume and area of the mesh.
- L56 _public prototype_ `static void GetMeshVolumeAreaCenter(UDynamicMesh* TargetMesh, float& SurfaceArea, float& Volume, FVector& CenterOfMass);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod))` — Computes the volume, area and center-of-mass of the mesh.
- L62 _public prototype_ `static bool GetIsClosedMesh( UDynamicMesh* TargetMesh );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns true if the mesh is closed, such as no topological boundary edges.
- L68 _public prototype_ `static UPARAM(DisplayName = "Num Loops") int32 GetNumOpenBorderLoops( UDynamicMesh* TargetMesh, bool& bAmbiguousTopolog` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns the number of open border loops, such as "holes" in the mesh.
- L74 _public prototype_ `static UPARAM(DisplayName = "Num Edges") int32 GetNumOpenBorderEdges( UDynamicMesh* Targ` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns the number of topological boundary edges in the mesh, i.e counts edges that only have one adjacent triangle.
- L80 _public prototype_ `static UPARAM(DisplayName = "Num Islands") int32 GetNumConnectedComponents( UDynamicMesh* Ta` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod, DisplayName = "Get Num Connected Islands", KeyWords = "Components Parts"))` — Returns the number of separate connected islands (components) in the mesh, such as "triangle patches" internally connected by shared edges.
- L90 _public prototype_ `static UPARAM(DisplayName = "Num Triangle IDs") int32 GetNumTriangleIDs( UDynamicMes` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Gets the number of Triangle IDs in the mesh. This may be larger than the Triangle Count if the mesh is not dense, even after deleting triangles.
- L96 _public prototype_ `static bool GetHasTriangleIDGaps( UDynamicMesh* TargetMesh );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns true if there are gaps in the Triangle ID list, such that Get Num Triangle IDs is greater than Get Triangle Count.
- L102 _public prototype_ `static bool IsValidTriangleID( UDynamicMesh* TargetMesh, int32 TriangleID );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns true if Triangle ID refers to a valid Triangle in the Target Mesh.
- L109 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetAllTriangleIDs( UDynamicMesh* TargetMesh, FGeometryScriptIndexList& TriangleIDList, bool& bHasTriangleIDGaps );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns an Index List of all Triangle IDs in a mesh. @param bHasTriangleIDGaps will be true on return if there are breaks in the sequential numeration of Triangle IDs, as would happen after deleting triangles.
- L118 _public prototype_ `static UPARAM(DisplayName = "Indices") FIntVector GetTriangleIndices( UDynamicMesh* TargetMesh, int32 TriangleID, bool& bIsValidTria` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns the Vertex ID triplet for the specified Triangle. @param TriangleID indicates the triangle to query on the Target Mesh. @param bIsValidTriangle will be false on return if the Triangle ID does not exist in the Target Mesh, in that case the returned vertex triplet will be (-1, -1, -1).
- L126 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetAllTriangleIndices( UDynamicMesh* TargetMesh, FGeometryScriptTriangleList& TriangleList, bool bSkipGaps, bool& bHasTriangleIDGaps);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns a TriangleList of all Triangle Vertex ID triplets in a mesh. @param bSkipGaps if false there will be a one-to-one correspondence between Triangle ID and entries in the triangle list and invalid triplets of (-1,-1,-1) will correspond to Triangle IDs not found in the Target Mesh. @param bHasTriangleIDGaps will be false on return if the mesh had no gaps in Triangle IDs or if bSkipGaps was set to true.
- L134 _public prototype_ `static void GetTrianglePositions( UDynamicMesh* TargetMesh, int32 TriangleID, bool& bIsValidTriangle, FVector& Vertex1, FVector& Vertex2, FVector& Vertex3 );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns the 3D positions (in the mesh local space) of the three vertices of the requested triangle. If the Triangle ID is not an element of the Target Mesh, all three vertices will be returned as (0, 0, 0) and bIsValidTriangle will be set to false.
- L142 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetInterpolatedTrianglePosition( UDynamicMesh* TargetMesh, int32 TriangleID, FVector BarycentricCoords, bool& bIsValidTriangle, FVector& InterpolatedPosition );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Compute the interpolated Position (A*Vertex1 + B*Vertex2 + C*Vertex3), where (A,B,C)=BarycentricCoords and the Vertex positions are taken from the specified TriangleID of the TargetMesh. @param bIsValidTriangle will be returned true if TriangleID exists in TargetMesh, and otherwise will be returned false
- L152 _public prototype_ `static UPARAM(DisplayName = "Normal") FVector GetTriangleFaceNormal( UDynamicMesh* TargetMesh, int32 TriangleID, bool& bIsValidTrian` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))`
- L163 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputeTriangleBarycentricCoords( UDynamicMesh* TargetMesh, int32 TriangleID, bool& bIsValidTriangle, FVector Point, FVector& Vertex1, FVector& Vertex2, FVector& Vertex3, FVector& BarycentricCoords );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Compute the barycentric coordinates (A,B,C) of the Point relative to the specified TriangleID of the TargetMesh. The properties of barycentric coordinates are such that A,B,C are all positive, A+B+C=1.0, and A*Vertex1 + B*Vertex2 + C*Vertex3 = Point. So, the barycentric coordinates can be used to smoothly interpolate/blend any other per-triangle-vertex quantities. The Point must lie in the plane of the Triangle, otherwise the coordinates are somewhat meaningless (but clamped to 0-1 range to avoid catastrophic errors) The Positions of the Triangle Vertices are also returned for convenience (similar to GetTrianglePositions) @param bIsValidTriangle will be returned true if TriangleID exists in TargetMesh, and otherwise will be returned false
- L179 _public prototype_ `static UPARAM(DisplayName = "Vertex Count") int32 GetVertexCount( UDynamicMesh* T` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Gets the number of vertices in the mesh. Note this may be less than the number of Vertex IDs used as some vertices may have been deleted.
- L185 _public prototype_ `static UPARAM(DisplayName = "Num Vertex IDs") int32 GetNumVertexIDs( UDynamicMesh*` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Gets the number of Vertex IDs in the mesh, which may be larger than the Vertex Count, if the mesh is not dense (e.g.  after deleting vertices).
- L191 _public prototype_ `static bool GetHasVertexIDGaps( UDynamicMesh* TargetMesh );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns true if there are gaps in the Vertex ID list. For example, Get Number of Vertex IDs is greater than Get Vertex Count.
- L197 _public prototype_ `static bool IsValidVertexID( UDynamicMesh* TargetMesh, int32 VertexID );` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns true if Vertex ID refers to a valid vertex in the Target Mesh.
- L203 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetAllVertexIDs( UDynamicMesh* TargetMesh, FGeometryScriptIndexList& VertexIDList, bool& bHasVertexIDGaps );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns an IndexList of all Vertex IDs in mesh.
- L210 _public prototype_ `static UPARAM(DisplayName = "Position") FVector GetVertexPosition( UDynamicMesh* TargetMesh, int32 VertexID, bool& bIsValidV` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Gets the 3D position of a mesh vertex in the mesh local space, by Vertex ID.
- L219 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetAllVertexPositions( UDynamicMesh* TargetMesh, FGeometryScriptVectorList& PositionList, bool bSkipGaps, bool& bHasVertexIDGaps );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns a Vector List of all the mesh vertex 3D positions (possibly large!). @param bSkipGaps if false there will be a one-to-one correspondence between Vertex ID and entries in the Position List where a zero vector (0,0,0) will correspond to Vertex IDs not found in the Target Mesh. @param bHasVertexIDGaps will be false if the mesh had no gaps in Vertex IDs or if bSkipGaps was set to true.
- L232 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetAllVertexPositionsAtEdges( UDynamicMesh* TargetMesh, const FGeometryScriptIndexList& EdgeIDs, FGeometryScriptVectorList& Start, FGeometryScriptVectorList& End);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns the vertex positions for each edge in the given index list. @param TargetMesh The mesh to query @param EdgeIDs The edge IDs to query @param Start The output list of start vertex positions @param End The output list of end vertex positions @return The target mesh that was queried
- L239 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetVertexConnectedTriangles( UDynamicMesh* TargetMesh, int32 VertexID, TArray<int32>& Triangles);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Return array of Triangle IDs connected to the given VertexID, ie the triangle one-ring
- L246 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetVertexConnectedVertices( UDynamicMesh* TargetMesh, int32 VertexID, TArray<int32>& Vertices);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Return array of Vertex IDs connected via a mesh edge to the given VertexID, ie the vertex one-ring
- L257 _public prototype_ `static UPARAM(DisplayName = "Num UV Channels") int32 GetNumUVSets( UDynamicMesh` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod), DisplayName = "Get Num UV Channels")` — Gets the number of UV Channels on the Target Mesh.
- L263 _public prototype_ `static UPARAM(DisplayName = "Bounding Box") FBox2D GetUVSetBoundingBox( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, UPARAM(DisplayName = "Is Valid UV Channel") bool& bIsValidUVSet, UPARAM(DisplayName = "UV Channel Is Empty") boo` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Gets the 2D bounding box of all UVs in the UV Channel.  If the UV Channel does not exist, or if the UV Channel is empty, the resulting box will be invalid.
- L277 _public prototype_ `static UPARAM(DisplayName = "UV Area") double GetMeshUVArea(UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVChannel, UPARAM(DisplayName = "Is Valid UV Channel") bool&` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod), DisplayName = "Get Mesh UV Area")` — Gets the area of triangles in UV space for the given UV Channel. @param TargetMesh The mesh to query. @param UVChannel The UV channel to query @param bIsValidUVChannel True, if the mesh has UVs for the given UVSetIndex. @return The number of UV islands
- L294 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetAllSplitUVsAtVertex( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int32 UVSetIndex, int32 VertexID, TArray<int32>& ElementIDs, TArray<FVector2D>& ElementUVs, bool& bHave` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns the unique UV element IDs and values associated with the mesh vertex, in the specified UV Channel. If the Vertex or UV channel does not exist, the arrays will be empty and bHaveValidUVs will be set to false.
- L303 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetInterpolatedTriangleUV( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int32 UVSetIndex, int32 TriangleID, FVector BarycentricCoords, bool& bTriHasValidUVs, FVector2D& InterpolatedUV );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Compute the interpolated UV (A*UV1+ B*UV2+ C*UV3), where (A,B,C)=BarycentricCoords and the UV positions are taken from the specified TriangleID in the specified UVSet of the TargetMesh. @param bIsValidTriangle bTriHasValidUVs be returned true if TriangleID exists in TargetMesh and is set to valid UVs in the UV Set, and otherwise will be returned false
- L323 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetAllUVSeamEdges( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int32 UVSetIndex, bool& bHaveValidUVs, FGeometryScriptIndexList& El` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns all edge element IDs that are UV seam edges for a given UV channel. @param TargetMesh The mesh to query. @param UVSetIndex The UV channel to query @param bHaveValidUVs True, if the mesh has UVs for the given UVSetIndex. @param ElementIDs The returned edge element IDs @return The target mesh that was queried.
- L335 _public prototype_ `static UPARAM(DisplayName = "Num UV Islands") int32 GetNumUVIslands( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int32 UVChannel, UPARAM(DisplayName = "Is Valid UV Channel") bool&` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod), DisplayName = "Get Num UV Islands")` — Returns the number of UV islands in a given UV channel. @param TargetMesh The mesh to query. @param UVChannel The UV channel to query @param bIsValidUVChannel True, if the mesh has UVs for the given UVSetIndex. @return The number of UV islands
- L349 _public prototype_ `static UPARAM(DisplayName = "Enabled") bool GetHasTriangleNormals( UDynamicMesh* Target` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — @return true if the TargetMesh has the Normals Attribute enabled (which allows for storing split normals)
- L357 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetTriangleNormals( UDynamicMesh* TargetMesh, int32 TriangleID, FVector& Normal1, FVector& Normal2, FVector& Normal3, bool& bTriHasValidNormals );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — For the specified TriangleID of the Target Mesh, get the Normal vectors at each vertex of the Triangle. These Normals will be taken from the Normal Overlay, i.e. they will potentially be split-normals. @param bTriHasValidNormals will be returned true if TriangleID exists in TargetMesh and has Normals set.
- L372 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetInterpolatedTriangleNormal( UDynamicMesh* TargetMesh, int32 TriangleID, FVector BarycentricCoords, bool& bTriHasValidNormals, FVector& InterpolatedNormal );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Compute the interpolated Normal (A*Normal1 + B*Normal2 + C*Normal3), where (A,B,C)=BarycentricCoords and the Normals are taken from the specified TriangleID in the Normal layer of the TargetMesh. @param bTriHasValidNormals will be returned true if TriangleID exists in TargetMesh and has Normals set, and otherwise will be returned false.
- L386 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetTriangleNormalTangents( UDynamicMesh* TargetMesh, int32 TriangleID, bool& bTriHasValidElements, FGeometryScriptTriangle& Normals, FGeometryScriptTriangle& Tangents, FGeometryScriptTriangle& BiTangents);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — For the specified Triangle ID of the TargetMesh, get the Normal and Tangent vectors at each vertex of the Triangle. These Normals/Tangents will be taken from the Normal and Tangents Overlays, i.e. they will potentially be split-normals. @param bTriHasValidElements will be returned true if TriangleID exists in TargetMesh and has Normals and Tangents set.
- L400 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetInterpolatedTriangleNormalTangents( UDynamicMesh* TargetMesh, int32 TriangleID, FVector BarycentricCoords, bool& bTriHasValidElements, FVector& InterpolatedNormal, FVector& InterpolatedTangent, FVector& InterpolatedBiTangent);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Compute the interpolated Normal and Tangents for the specified specified TriangleID in the Normal and Tangent attributes of the TargetMesh. @param bTriHasValidElements will be returned true if TriangleID exists in TargetMesh and has Normals and Tangents set, and otherwise will be returned false
- L420 _public prototype_ `static UPARAM(DisplayName = "Enabled") bool GetHasVertexColors( UDynamicMesh* Target` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — @return true if the TargetMesh has the Vertex Colors attribute enabled
- L428 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetTriangleVertexColors( UDynamicMesh* TargetMesh, int32 TriangleID, FLinearColor& Color1, FLinearColor& Color2, FLinearColor& Color3, bool& bTriHasValidVertexColors );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — For the specified TriangleID of the TargetMesh, get the Vertex Colors at each vertex of the Triangle. These Colors will be taken from the Vertex Color Attribute, ie they will potentially be split-colors. @param bTriHasValidVertexColors will be returned true if TriangleID exists in TargetMesh and has Vertex Colors set
- L443 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetInterpolatedTriangleVertexColor( UDynamicMesh* TargetMesh, int32 TriangleID, FVector BarycentricCoords, FLinearColor DefaultColor, bool& bTriHasValidVertexColors, FLinearColor& InterpolatedColor );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Compute the interpolated Vertex Color (A*Color1 + B*Color2 + C*Color3), where (A,B,C)=BarycentricCoords and the Colors are taken from the specified TriangleID in the Vertex Color layer of the TargetMesh. @param bTriHasValidVertexColors will be returned true if TriangleID exists in TargetMesh and has Colors set, and otherwise will be returned false
- L461 _public prototype_ `static UPARAM(DisplayName = "Enabled") bool GetHasMaterialIDs( UDynamicMesh* Target` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod))` — Returns true if the mesh has Material IDs available/enabled.
- L472 _public prototype_ `static UPARAM(DisplayName = "Enabled") bool GetHasPolygroups( UDynamicMesh* Target` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod, DisplayName = "Get Has PolyGroups"))` — Returns true if the mesh has a standard PolyGroup Layer.
- L478 _public prototype_ `static UPARAM(DisplayName = "Num Layers") int GetNumExtendedPolygroupLayers( UDynamicMesh* Tar` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta=(ScriptMethod, DisplayName = "Get Num Extended PolyGroup Layers"))` — Returns the count of extended PolyGroup Layers.
- L486 _public prototype_ `static UPARAM(DisplayName = "Weight Map Handle") FGeometryScriptWeightMapHandle GetWeightMapHandle(UDynamicMesh* TargetMesh, FName Name, EGeometryScriptSearchOutcomePin` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod, DisplayName = "Get Weight Map Handle By Name", ExpandEnumAsExecs = "FoundWeights"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshRemeshFunctions.h` (Public)


#### enum `EGeometryScriptUniformRemeshTargetType`  
`enum class EGeometryScriptUniformRemeshTargetType : uint8`  
_L17-23_
- reflection: `UENUM(BlueprintType)`
- desc: Goal types for Uniform Remeshing
- L20 _public enumerator_ `TriangleCount = 0` — Approximate Desired Triangle Count. This is used to compute a Target Edge Length, and is not an explicit target
- L22 _public enumerator_ `TargetEdgeLength = 1` — Attempt to Remesh such that all edges have approximately this length

#### enum `EGeometryScriptRemeshEdgeConstraintType`  
`enum class EGeometryScriptRemeshEdgeConstraintType : uint8`  
_L27-37_
- reflection: `UENUM(BlueprintType)`
- desc: Types of edge constraints, specified for different mesh attributes
- L30 _public enumerator_ `Fixed = 0` — Constrained edges cannot be flipped, split or collapsed, and vertices will not move
- L32 _public enumerator_ `Refine = 1` — Constrained edges can be split, but not flipped or collapsed. Vertices will not move.
- L34 _public enumerator_ `Free = 2` — Constrained edges cannot be flipped, but otherwise are free to move
- L36 _public enumerator_ `Ignore = 3` — Edges are not constrained, ie the Attribute used to derive the Constraints will not be considered

#### enum `EGeometryScriptRemeshSmoothingType`  
`enum class EGeometryScriptRemeshSmoothingType : uint8`  
_L41-49_
- reflection: `UENUM(BlueprintType)`
- desc: The Vertex Smoothing strategy used in a Remeshing operation
- L44 _public enumerator_ `Uniform = 0` — Vertices move towards their 3D one-ring centroids, UVs are ignored. This produces the most regular mesh possible.
- L46 _public enumerator_ `UVPreserving = 1` — Vertices move towards the projection of their one-ring centroids onto their normal vectors, preserving UVs
- L48 _public enumerator_ `Mixed = 2` — Similar to UV Preserving, but allows some tangential drift (causing UV distortion) when vertices would otherwise be "stuck"

#### struct `FGeometryScriptRemeshOptions`  
`struct FGeometryScriptRemeshOptions`  
_L56-120_
- reflection: `USTRUCT(Blueprintable)`
- desc: Standard Remeshing Options
- L63 _public member_ `bool bDiscardAttributes = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — When enabled, all mesh attributes are discarded, so UV and Normal Seams can be ignored. New per-vertex normals are computed.
- L67 _public member_ `bool bReprojectToInputMesh = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — When enabled, mesh vertices are projected back onto the input mesh surface during Remeshing, preserving the shape
- L71 _public member_ `EGeometryScriptRemeshSmoothingType SmoothingType = EGeometryScriptRemeshSmoothingType::Mixed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Type of 3D Mesh Smoothing to apply during Remeshing. Disable by setting SmoothingRate = 0
- L75 _public member_ `float SmoothingRate = 0.25f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = 0, UIMax = 1, ClampMin = 0, ClampMax = 1))` — Smoothing Rate/Speed. Faster Smoothing results in a more regular mesh, but also more potential for undesirable 3D shape change and UV distortion
- L79 _public member_ `EGeometryScriptRemeshEdgeConstraintType MeshBoundaryConstraint = EGeometryScriptRemeshEdgeConstraintType::Free;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Constraints on the open mesh boundary/border edges
- L83 _public member_ `EGeometryScriptRemeshEdgeConstraintType GroupBoundaryConstraint = EGeometryScriptRemeshEdgeConstraintType::Free;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Constraints on the mesh boundary/border edges between different PolyGroups of the Mesh
- L87 _public member_ `EGeometryScriptRemeshEdgeConstraintType MaterialBoundaryConstraint = EGeometryScriptRemeshEdgeConstraintType::Free;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Constraints on the mesh boundary/border edges between different Material Results of the Mesh
- L91 _public member_ `bool bAllowFlips = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Enable/Disable Edge Flips during Remeshing. Disabling flips will significantly reduce the output mesh quality
- L95 _public member_ `bool bAllowSplits = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Enable/Disable Edge Splits during Remeshing. Disabling Splits will prevent the mesh density from increasing.
- L99 _public member_ `bool bAllowCollapses = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Enable/Disable Edge Collapses during Remeshing. Disabling Collapses will prevent the mesh density from decreasing.
- L103 _public member_ `bool bPreventNormalFlips = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — When Enabled, Flips and Collapses will be skipped if they would flip any triangle face normals
- L107 _public member_ `bool bPreventTinyTriangles = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — When Enabled, Flips and Collapses will be skipped if they would create tiny degenerate triangles
- L111 _public member_ `bool bUseFullRemeshPasses = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — By default, remeshing is accelerated by tracking a queue of edges that need to be processed. This is signficantly faster but can produce a lower quality output. Enable this option to use a more expensive strategy that guarantees maximum quality.
- L115 _public member_ `int32 RemeshIterations = 20;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = 0, ClampMin = 0))` — Maximum Number of iterations of the Remeshing Strategy to apply to the Mesh. More iterations are generally more expensive (much moreso with bUseFullRemeshPasses = true)
- L119 _public member_ `bool bAutoCompact = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If enabled, the output mesh is automatically compacted to remove gaps in the index space. This is expensive and can be disabled by advanced users.

#### struct `FGeometryScriptUniformRemeshOptions`  
`struct FGeometryScriptUniformRemeshOptions`  
_L127-142_
- reflection: `USTRUCT(Blueprintable)`
- desc: Uniform Remeshing Options
- L133 _public member_ `EGeometryScriptUniformRemeshTargetType TargetType = EGeometryScriptUniformRemeshTargetType::TriangleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Method used to define target/goal of Uniform Remeshing
- L137 _public member_ `int32 TargetTriangleCount = 5000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = 0, ClampMin = 0, EditCondition = "TargetType == EGeometryScriptUniformRemeshTargetType::TriangleCount"))` — Approximate Target Triangle Count, combined with mesh surface area to derive a TargetEdgeLength
- L141 _public member_ `float TargetEdgeLength = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = 0, ClampMin = 0, EditCondition = "TargetType == EGeometryScriptUniformRemeshTargetType::TargetEdgeLength"))` — Explicit Target Edge Length that is desired in the output uniform mesh

#### struct `FGeometryScriptAdaptiveRemeshOptions`  
`struct FGeometryScriptAdaptiveRemeshOptions`  
_L148-167_
- reflection: `USTRUCT(Blueprintable)`
- desc: Adaptive Remeshing Options
- L154 _public member_ `EGeometryScriptUniformRemeshTargetType TargetType = EGeometryScriptUniformRemeshTargetType::TriangleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Method used to define target/goal of Adaptive Remeshing
- L158 _public member_ `int32 TargetTriangleCount = 5000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = 0, ClampMin = 0, EditCondition = "TargetType == EGeometryScriptUniformRemeshTargetType::TriangleCount"))` — Approximate Target Triangle Count, combined with mesh surface area to derive a TargetEdgeLength
- L162 _public member_ `float TargetEdgeLength = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = 0, ClampMin = 0, EditCondition = "TargetType == EGeometryScriptUniformRemeshTargetType::TargetEdgeLength"))` — Explicit Target Edge Length that is desired in the output uniform mesh
- L166 _public member_ `float RelativeDensity = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = "-2.0", UIMax = "2.0"))` — Amount to adjust density in regions where the vertex weight map is greater than zero. A positive value here results in a denser mesh, a negative value results in a coarser one

#### class `UGeometryScriptLibrary_RemeshingFunctions`  
`class UGeometryScriptLibrary_RemeshingFunctions : public UBlueprintFunctionLibrary`  
_L171-197_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_Remeshing"))`
- inherits: `UBlueprintFunctionLibrary`
- L181 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyUniformRemesh( UDynamicMesh* TargetMesh, FGeometryScriptRemeshOptions RemeshOptions, FGeometryScriptUniformRemeshOptions UniformOptions, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Simplification", meta=(ScriptMethod, HidePin = "Debug"))` — Apply Uniform Remeshing to the TargetMesh. @warning this function can be quite expensive. The results may be non-deterministic, and are expected to change in future versions.
- L189 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyAdaptiveRemesh( UDynamicMesh* TargetMesh, FGeometryScriptRemeshOptions RemeshOptions, FGeometryScriptAdaptiveRemeshOptions AdaptiveOptions, FGeometryScriptWeightMapHandle WeightMapHandle, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Simplification", meta = (ScriptMethod, HidePin = "Debug"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshRepairFunctions.h` (Public)


#### struct `FGeometryScriptWeldEdgesOptions`  
`struct FGeometryScriptWeldEdgesOptions`  
_L16-27_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `float Tolerance = 1e-06f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Edges are coincident if both pairs of endpoint vertices, and their midpoint, are closer than this distance
- L26 _public member_ `bool bOnlyUniquePairs = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Only merge unambiguous pairs that have unique duplicate-edge matches

#### struct `FGeometryScriptResolveTJunctionOptions`  
`struct FGeometryScriptResolveTJunctionOptions`  
_L32-39_
- reflection: `USTRUCT(BlueprintType)`
- L38 _public member_ `float Tolerance = 1e-03f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptSnapBoundariesOptions`  
`struct FGeometryScriptSnapBoundariesOptions`  
_L42-57_
- reflection: `USTRUCT(BlueprintType)`
- L48 _public member_ `float Tolerance = 1e-03f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Snapping tolerance
- L52 _public member_ `bool bSnapToEdges = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to snap vertices to open edges. If false, will only snap together vertices
- L56 _public member_ `int MaxIterations = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Maximum number of iterations of boundary snapping to apply. Will stop earlier if an iteration applies no snapping.

#### enum `EGeometryScriptFillHolesMethod`  
`enum class EGeometryScriptFillHolesMethod : uint8`  
_L60-67_
- reflection: `UENUM(BlueprintType)`
- L62 _public enumerator_ `Automatic = 0`
- L63 _public enumerator_ `MinimalFill = 1`
- L64 _public enumerator_ `PolygonTriangulation = 2`
- L65 _public enumerator_ `TriangleFan = 3`
- L66 _public enumerator_ `PlanarProjection = 4`

#### struct `FGeometryScriptFillHolesOptions`  
`struct FGeometryScriptFillHolesOptions`  
_L70-80_
- reflection: `USTRUCT(BlueprintType)`
- L75 _public member_ `EGeometryScriptFillHolesMethod FillMethod = EGeometryScriptFillHolesMethod::Automatic;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L79 _public member_ `bool bDeleteIsolatedTriangles = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Delete floating, disconnected triangles, as they produce a "hole" that cannot be filled

#### struct `FGeometryScriptRemoveSmallComponentOptions`  
`struct FGeometryScriptRemoveSmallComponentOptions`  
_L85-99_
- reflection: `USTRUCT(BlueprintType)`
- L91 _public member_ `float MinVolume = 0.0001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L95 _public member_ `float MinArea = 0.0001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L98 _public member_ `int MinTriangleCount = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### enum `EGeometryScriptRemoveHiddenTrianglesMethod`  
`enum class EGeometryScriptRemoveHiddenTrianglesMethod : uint8`  
_L105-109_
- reflection: `UENUM(BlueprintType)`
- L107 _public enumerator_ `FastWindingNumber = 0`
- L108 _public enumerator_ `RaycastOcclusionTest = 1`

#### struct `FGeometryScriptRemoveHiddenTrianglesOptions`  
`struct FGeometryScriptRemoveHiddenTrianglesOptions`  
_L113-145_
- reflection: `USTRUCT(BlueprintType)`
- L119 _public member_ `EGeometryScriptRemoveHiddenTrianglesMethod Method = EGeometryScriptRemoveHiddenTrianglesMethod::FastWindingNumber;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L123 _public member_ `int SamplesPerTriangle = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — add triangle samples per triangle (in addition to TriangleSamplingMethod)
- L127 _public member_ `int ShrinkSelection = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — once triangles to remove are identified, do iterations of boundary erosion, ie contract selection by boundary vertex one-rings
- L131 _public member_ `float WindingIsoValue = 0.5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — use this as winding isovalue for WindingNumber mode
- L135 _public member_ `int RaysPerSample = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — random rays to add beyond +/- major axes, for raycast sampling
- L140 _public member_ `float NormalOffset = 1e-6f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Nudge sample points out by this amount to try to counteract numerical issues
- L144 _public member_ `bool bCompactResult = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to compact the resulting mesh after triangles are deleted

#### struct `FGeometryScriptSelectHiddenTrianglesFromOutsideOptions`  
`struct FGeometryScriptSelectHiddenTrianglesFromOutsideOptions`  
_L148-178_
- reflection: `USTRUCT(BlueprintType)`
- L156 _public member_ `double SampleSpacing = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Approximate spacing between samples on triangle faces used for determining visibility Set a smaller value to increase the number of visibility samples per triangle, which can give more accurate visibility results
- L160 _public member_ `bool bDoubleSided = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to treat faces as double-sided when determining visibility
- L164 _public member_ `int32 NumSearchDirections = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Number of directions to test for visibility. Note: RestrictToViewDirections will filter the view directions after they are sampled from a full sphere, so the actual number of sampled directions will be smaller if restricted.
- L168 _public member_ `bool bPerPolyGroup = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to decide visibility on a per-polygroup basis, rather than per-triangle
- L173 _public member_ `TArray<FVector> RestrictToViewDirections;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If not empty, only allow views along these directions (or a direction within the ViewDirectionAngleRange cone of these directions) To be specific: A mesh sample P is visible from given direction D if a ray starting at P-D*(Mesh Diameter), cast in direction D, reaches P
- L177 _public member_ `double ViewDirectionAngleRange = 45;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Field of view to use for the RestrictViewDirections (if any), in degrees

#### enum `EGeometryScriptRepairMeshMode`  
`enum class EGeometryScriptRepairMeshMode : uint8`  
_L182-187_
- reflection: `UENUM(BlueprintType)`
- L184 _public enumerator_ `DeleteOnly = 0`
- L185 _public enumerator_ `RepairOrDelete = 1`
- L186 _public enumerator_ `RepairOrSkip = 2`

#### struct `FGeometryScriptDegenerateTriangleOptions`  
`struct FGeometryScriptDegenerateTriangleOptions`  
_L192-210_
- reflection: `USTRUCT(BlueprintType)`
- L198 _public member_ `EGeometryScriptRepairMeshMode Mode = EGeometryScriptRepairMeshMode::RepairOrDelete;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L202 _public member_ `double MinTriangleArea = 0.001;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L206 _public member_ `double MinEdgeLength = 0.0001;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L209 _public member_ `bool bCompactOnCompletion = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### class `UGeometryScriptLibrary_MeshRepairFunctions`  
`class UGeometryScriptLibrary_MeshRepairFunctions : public UBlueprintFunctionLibrary`  
_L215-345_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshRepair"))`
- inherits: `UBlueprintFunctionLibrary`
- L224 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* CompactMesh( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Repair", meta=(ScriptMethod, HidePin = "Debug"))` — Compacts the mesh's vertices and triangles to remove any "holes" in the Vertex ID or Triangle ID lists.
- L233 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RemoveUnusedVertices( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Repair", meta = (ScriptMethod, HidePin = "Debug"))` — Remove vertices that are not used by any triangles. Note: Does not update the IDs of any remaining vertices; use CompactMesh to do so.
- L243 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SnapMeshOpenBoundaries( UDynamicMesh* TargetMesh, FGeometryScriptSnapBoundariesOptions SnapOptions, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Repair", meta = (ScriptMethod, HidePin = "Debug"))` — Snap vertices on open edges to the closest compatible open boundary, if found within the tolerance distance Unlike ResolveMeshTJunctions, does not introduce new vertices to the mesh
- L254 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ResolveMeshTJunctions( UDynamicMesh* TargetMesh, FGeometryScriptResolveTJunctionOptions ResolveOptions, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Repair", meta=(ScriptMethod, HidePin = "Debug"))` — Attempts to resolve T-Junctions in the mesh by addition of vertices and welding.
- L264 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* WeldMeshEdges( UDynamicMesh* TargetMesh, FGeometryScriptWeldEdgesOptions WeldOptions, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Repair", meta=(ScriptMethod, HidePin = "Debug"))` — Welds any open boundary edges of the mesh together if possible in order to remove "cracks."
- L277 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* FillAllMeshHoles( UDynamicMesh* TargetMesh, FGeometryScriptFillHolesOptions FillOptions, int32& NumFilledHoles, int32& NumFailedHoleFills, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Repair", meta=(ScriptMethod, HidePin = "Debug"))` — Tries to fill all open boundary loops (such as holes in the geometry surface) of a mesh. @param FillOptions specifies the method used to fill the holes. @param NumFilledHoles reports the number of holes filled by the function. @param NumFailedHolesFills reports the detected holes that were unable to be filled.
- L290 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RemoveSmallComponents( UDynamicMesh* TargetMesh, FGeometryScriptRemoveSmallComponentOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Repair", meta=(ScriptMethod, HidePin = "Debug", DisplayName = "Remove Small Connected Islands", KeyWords = "Delete Components Parts"))` — Removes connected islands (components) of the mesh that have a volume, area, or triangle count below a threshold as specified by the Options.
- L301 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RemoveHiddenTriangles( UDynamicMesh* TargetMesh, FGeometryScriptRemoveHiddenTrianglesOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Repair", meta=(ScriptMethod, HidePin = "Debug", KeyWords = "Jacket Occluded"))` — Removes any triangles in the mesh that are not visible from the exterior view, under various definitions of "visible" and "outside" as specified by the Options.
- L315 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectHiddenTrianglesFromOutside( UDynamicMesh* TargetMesh, FGeometryScriptSelectHiddenTrianglesFromOutsideOptions Options, FGeometryScriptMeshSelection IgnoreSelection, FGeometryScriptMeshSelection TransparentSelection, FGeometryScriptMeshSelection& ResultSelection, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Repair", meta = (ScriptMethod, HidePin = "Debug", KeyWords = "Remove Jacket Occluded"))` — Select mesh triangles hidden from outside views, with optional filtering on view directions @param IgnoreSelection Optionally indicate parts of the mesh that should not be included in the ResultSelection, so do not need to be tested for occlusion @param TransparentSelection Optionally indicate parts of the mesh that should not be considered occluding, e.g. transparent triangles @param ResultSelection The fully occluded triangles of the target mesh (based on the options / transparencies, and excluding any IgnoreSelection triangles)
- L329 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SplitMeshBowties( UDynamicMesh* TargetMesh, bool bMeshBowties = true, bool bAttributeBowties = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Repair", meta=(ScriptMethod, HidePin = "Debug"))` — Splits Bowties in the mesh and/or the attributes.  A Bowtie is formed when a single vertex is connected to more than two boundary edges, and splitting duplicates the shared vertex so each triangle will have a unique copy.
- L340 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RepairMeshDegenerateGeometry( UDynamicMesh* TargetMesh, FGeometryScriptDegenerateTriangleOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Repair", meta=(ScriptMethod, HidePin = "Debug"))` — Removes triangles that have area or edge length below specified amounts depending on the Options requested.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshSamplingFunctions.h` (Public)


#### struct `FGeometryScriptMeshPointSamplingOptions`  
`struct FGeometryScriptMeshPointSamplingOptions`  
_L16-46_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `float SamplingRadius = 10.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Desired "radius" of sample points. Spacing between samples is at least 2x this value.
- L26 _public member_ `int MaxNumSamples = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Maximum number of samples requested. If 0 or default value, mesh will be maximally sampled
- L30 _public member_ `int RandomSeed = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Random Seed used to initialize sampling strategies
- L34 _public member_ `double SubSampleDensity = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Density of subsampling used in Poisson strategy. Larger numbers mean "more accurate" (but slower) results.
- L45 _public member_ `int SamplingMethodVersion = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, AdvancedDisplay)` — If < 0, the latest, recommended sampling methods will be used. Otherwise, requests a specific sampling method version. Set this for more consistent results across UE versions, at the risk of worse performance or quality. Valid versions are: Method 0: UE 5.5 and earlier sampling method. Slower initial (dense) point sampling, less robust to degenerate triangles. Method 1: Point downsampling is performed in a fixed order regardless of seed, which gives overly-similar sample patterns across multiple runs Method 2: Currently the default method.

#### enum `EGeometryScriptSamplingWeightMode`  
`enum class EGeometryScriptSamplingWeightMode : uint8`  
_L50-67_
- reflection: `UENUM(BlueprintType)`
- desc: Control how active Weights are used to affect point radius
- L56 _public enumerator_ `WeightToRadius = 0` — Weights are clamped to [0,1] and used to interpolate Min/Max Radius. This is a "hard constraint", ie if the weight at a point is 1, only a "max radius" sample may be placed there, otherwise no samples at all (so no "filling in" smaller samples between large ones)
- L61 _public enumerator_ `FilledWeightToRadius = 1` — Weights are clamped to [0,1] and used to interpolate Min/Max Radius, with decay, so that smaller-radius samples will infill between large ones. So areas with large weight may still end up with some variable-radius samples, but areas with 0 weight will only ever have min-radius samples.
- L66 _public enumerator_ `WeightedRandom = 2` — Weight is used to create nonuniform random sampling, ie it nudges the random sample-radius distribution but does not directly control it. So samples with any radius can still appear at any location, but if weight=1 then max-radius samples are more likely, etc.

#### enum `EGeometryScriptSamplingDistributionMode`  
`enum class EGeometryScriptSamplingDistributionMode : uint8`  
_L71-79_
- reflection: `UENUM(BlueprintType)`
- desc: Controls the distribution of sample radii
- L74 _public enumerator_ `Uniform = 0` — Uniform distribution of sizes, ie all equally likely
- L76 _public enumerator_ `Smaller = 1` — Distribution is weighted towards smaller points
- L78 _public enumerator_ `Larger = 2` — Distribution is weighted towards larger points

#### struct `FGeometryScriptNonUniformPointSamplingOptions`  
`struct FGeometryScriptNonUniformPointSamplingOptions`  
_L83-106_
- reflection: `USTRUCT(BlueprintType)`
- L89 _public member_ `float MaxSamplingRadius = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If MaxSampleRadius > SampleRadius, then output sample radius will be in range [SampleRadius, MaxSampleRadius]
- L93 _public member_ `EGeometryScriptSamplingDistributionMode SizeDistribution = EGeometryScriptSamplingDistributionMode::Uniform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — SizeDistribution setting controls the distribution of sample radii
- L97 _public member_ `double SizeDistributionPower = 2.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, Meta = (UIMin=1, UIMax=10, EditCondition ="(SizeDistribution != EGeometryScriptSamplingDistributionMode::Uniform)" ))` — SizeDistributionPower is used to control how extreme the Size Distribution shift is. Valid range is [1,10]
- L101 _public member_ `EGeometryScriptSamplingWeightMode WeightMode = EGeometryScriptSamplingWeightMode::WeightedRandom;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — WeightMode controls how any active Weight scheme is used to affect sample radius
- L105 _public member_ `bool bInvertWeights = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true, weight values are inverted

#### class `UGeometryScriptLibrary_MeshSamplingFunctions`  
`class UGeometryScriptLibrary_MeshSamplingFunctions : public UBlueprintFunctionLibrary`  
_L110-204_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshSampling"))`
- inherits: `UBlueprintFunctionLibrary`
- L119 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") const UDynamicMesh* ComputeUniformRandomPointSampling( const UDynamicMesh* TargetMesh, int32 NumSamples, TArray<FTransform>& Samples, FGeometryScriptIndexList& TriangleIDs, int RandomSeed = 0, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSampling", meta = (ScriptMethod, HidePin = "Debug"))` — Compute a 'uniform random' (not 'uniform spacing') point sampling over the mesh surface
- L136 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputePointSampling( UDynamicMesh* TargetMesh, FGeometryScriptMeshPointSamplingOptions Options, TArray<FTransform>& Samples, FGeometryScriptIndexList& TriangleIDs, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSampling", meta=(ScriptMethod, HidePin = "Debug"))` — Compute a set of sample points lying on the surface of TargetMesh based on the provided sampling Options. Samples are approximately uniformly distributed, and non-overlapping relative to the provided Options.SamplingRadius, ie the distance between any pair of samples if >= 2*SamplingRadius. @param Samples output list of sample points. Transform Location is sample position, Rotation orients Z with the triangle normal @param TriangleIDs TriangleID that contains each sample point. Length is the same as Samples array.
- L150 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputeNonUniformPointSampling( UDynamicMesh* TargetMesh, FGeometryScriptMeshPointSamplingOptions Options, FGeometryScriptNonUniformPointSamplingOptions NonUniformOptions, TArray<FTransform>& Samples, TArray<double>& SampleRadii, FGeometryScriptIndexList& TriangleIDs, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSampling", meta=(ScriptMethod, HidePin = "Debug"))` — Compute a set of sample points lying on the surface of TargetMesh based on the provided sampling Options and NonUniformOptions. The sample points have radii in the range [Options.SamplingRadius, NonUniformOptions.MaxSamplingRadius], and are non-overlapping, ie the distance between two points is always larger than the sum of their respective radii.
- L167 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputeVertexWeightedPointSampling( UDynamicMesh* TargetMesh, FGeometryScriptMeshPointSamplingOptions Options, FGeometryScriptNonUniformPointSamplingOptions NonUniformOptions, FGeometryScriptScalarList VertexWeights, TArray<FTransform>& Samples, TArray<double>& SampleRadii, FGeometryScriptIndexList& TriangleIDs, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSampling", meta=(ScriptMethod, HidePin = "Debug"))` — Compute a set of sample points lying on the surface of TargetMesh based on the provided sampling Options and NonUniformOptions. The sample points have radii in the range [Options.SamplingRadius, NonUniformOptions.MaxSamplingRadius], and are non-overlapping, ie the distance between two points is always larger than the sum of their respective radii. @param VertexWeights defines a per-vertex weight in range [0,1], these are interpolated to create a scalar field over the mesh triangles which is used to weight the sampling radii
- L186 _public prototype_ `ComputeRenderCaptureCamerasForBox( TArray<FGeometryScriptRenderCaptureCamera>& Cameras, FBox Box, const FGeometryScriptRenderCaptureCamerasForBoxOptions& Options, UGeometryScriptDebug* Debug = nullptr);`
- L198 _public prototype_ `ComputeRenderCapturePointSampling( TArray<FTransform>& Samples, const TArray<AActor*>& Actors, const TArray<FGeometryScriptRenderCaptureCamera>& Cameras, UGeometryScriptDebug* Debug = nullptr);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshSculptLayersFunctions.h` (Public)


#### struct `FGeometryScriptSculptLayerUpdateOptions`  
`struct FGeometryScriptSculptLayerUpdateOptions`  
_L16-23_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `bool bRecomputeNormals = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to recompute normals when changes to sculpt layers may have changed the mesh vertex positions

#### class `UGeometryScriptLibrary_MeshSculptLayersFunctions`  
`class UGeometryScriptLibrary_MeshSculptLayersFunctions : public UBlueprintFunctionLibrary`  
_L27-104_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshSculptLayers"))`
- inherits: `UBlueprintFunctionLibrary`
- L35 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* EnableSculptLayers( UDynamicMesh* TargetMesh, int32 NumLayers, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SculptLayers", meta = (ScriptMethod, HidePin = "Debug"))` — Enable Sculpt Layers on the Target Mesh, if not already enabled, with at least the requested number of layers. Note: Will never decrease the number of enabled layers. @param NumLayers The amount of layers that must be enabled on the mesh. Note: If this many layers (or more) are already enabled, the mesh will not be changed.
- L43 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetActiveSculptLayer( UDynamicMesh* TargetMesh, int32 LayerIndex, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SculptLayers", meta = (ScriptMethod, HidePin = "Debug"))` — Set the requested LayerIndex as the current active sculpt layer, if possible.
- L51 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetSculptLayerWeight( UDynamicMesh* TargetMesh, int32 LayerIndex, double Weight, FGeometryScriptSculptLayerUpdateOptions Options = FGeometryScriptSculptLayerUpdateOptions(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SculptLayers", meta = (ScriptMethod, HidePin = "Debug"))` — Set the weight of the layer at LayerIndex to the requested Weight
- L62 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetSculptLayerWeightsArray( UDynamicMesh* TargetMesh, TArray<double> Weights, FGeometryScriptSculptLayerUpdateOptions Options = FGeometryScriptSculptLayerUpdateOptions(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SculptLayers", meta = (ScriptMethod, HidePin = "Debug"))` — Set the weights of multiple layers to match the given Weights array. Note: If the Weights array length is larger than the number of layers, will just set the weights of the existing layers. Will not add or remove layers.
- L71 _public prototype_ `static UPARAM(DisplayName = "Weights") TArray<double> GetSculptLayerWeightsArray(UDynamicMesh* TargetMesh);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SculptLayers", meta = (ScriptMethod))` — Get the weights of all sculpt layers on the mesh
- L76 _public prototype_ `static UPARAM(DisplayName = "Num Layers") int32 GetNumSculptLayers(const UDynamicMesh* Ta` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|SculptLayers")` — Get the number of sculpting layers active on the mesh
- L80 _public prototype_ `static UPARAM(DisplayName = "Layer Index") int32 GetActiveSculptLayer(const UDynamicMesh* T` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|SculptLayers")` — Get the current sculpting layers active on the mesh, or -1 if the mesh does not have sculpting layers
- L84 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* DiscardSculptLayers( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SculptLayers", meta = (ScriptMethod, HidePin = "Debug", Keywords="Delete Remove"))` — Discard all sculpt layer data, leaving current vertex positions unchanged
- L95 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* MergeSculptLayers( UDynamicMesh* TargetMesh, int32& OutActiveLayer, int32 MergeLayerStart, int32 MergeLayerNum, bool bUseWeights = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SculptLayers", meta = (ScriptMethod, HidePin = "Debug", Keywords = "Combine"))` — Merge a range of sculpt layers together. May change the Active Sculpt Layer. @param OutActiveLayer The active layer after layers have been merged. @param MergeLayerStart The first layer to merge @param MergeLayerNum The number of layers to merge. Note: If larger than the number of existing layers after MergeLayerStart, will be clamped as needed. @param bUseWeights If true, layers will be merged based on their current weights -- keeping the mesh shape unchanged. Otherwise, layers will be merged with weight 1, which may change the shape of the mesh.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshSelectionFunctions.h` (Public)


#### enum `EGeometryScriptTopologyConnectionType`  
`enum class EGeometryScriptTopologyConnectionType : uint8`  
_L18-23_
- reflection: `UENUM(BlueprintType)`
- desc: Types of connection between adjacent Mesh Elements (vertices/triangles/polygoups)
- L20 _public enumerator_ `Geometric`
- L21 _public enumerator_ `Polygroup UMETA(DisplayName = "PolyGroup")`
- L22 _public enumerator_ `MaterialID`

#### class `UGeometryScriptLibrary_MeshSelectionFunctions`  
`class UGeometryScriptLibrary_MeshSelectionFunctions : public UBlueprintFunctionLibrary`  
_L29-410_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshSelection"))`
- inherits: `UBlueprintFunctionLibrary`
- L41 _public prototype_ `GetMeshSelectionInfo( FGeometryScriptMeshSelection Selection, EGeometryScriptMeshSelectionType& SelectionType, int& NumSelected);`
- L51 _public prototype_ `GetMeshUniqueSelectionInfo( const UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, EGeometryScriptMeshSelectionType& SelectionType, int& NumSelected);`
- L63 _public prototype_ `DebugPrintMeshSelection( FGeometryScriptMeshSelection Selection, bool bDisable = false);`
- L71 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* CreateSelectAllMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection& Selection, EGeometryScriptMeshSelectionType SelectionType = EGeometryScriptMeshSelectionType::Triangles );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Create a Selection of the given SelectionType that contains all the mesh elements of TargetMesh
- L81 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshElementsByMaterialID( UDynamicMesh* TargetMesh, int MaterialID, FGeometryScriptMeshSelection& Selection, EGeometryScriptMeshSelectionType SelectionType = EGeometryScriptMeshSelectionType::Triangles );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Create a Selection of the SelectionType that contains all mesh elements referencing triangles with the given Material ID
- L92 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshElementsByPolygroup( UDynamicMesh* TargetMesh, FGeometryScriptGroupLayer GroupLayer, UPARAM(DisplayName = "PolyGroup ID") int PolygroupID, FGeometryScriptMeshSelection& Selection, EGeometryScriptMeshSelectionType SelectionType = EGeometryScriptMeshSelectionType::Triangles );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Create a Selection of the SelectionType that contains all mesh elements referencing triangles with the given PolyGroup ID in the given GroupLayer
- L112 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ConvertMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection FromSelection, FGeometryScriptMeshSelection& ToSelection, EGeometryScriptMeshSelectionType NewType = EGeometryScriptMeshSelectionType::Triangles, bool bAllowPartialInclusion = true );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Convert a Mesh Selection to a different Type (eg Vertices to Triangles, etc) By default, Vertices map to Triangle one-rings, and Triangles to all contained vertices. If bAllowPartialInclusion is disabled, then more restrictive conversions are performed, as follows: For To-Vertices, only include vertices where all one-ring triangles or edges are included in FromSelection. For To-Edges, only include edges where all adjacent triangles or vertices are included in FromSelection For To-Triangles, only include triangles where all tri vertices or edges are included in FromSelection. For To-PolyGroups, only include groups where all group triangles are touched by FromSelection (Note: The To-PolyGroups rule allows vertex and edge selections that miss some vertices or edges, as long as they touch all the polygroup triangles.) @param bAllowPartialInclusion if false, perform more limited selection conversion as described above
- L127 _public prototype_ `CombineMeshSelections( FGeometryScriptMeshSelection SelectionA, FGeometryScriptMeshSelection SelectionB, FGeometryScriptMeshSelection& ResultSelection, EGeometryScriptCombineSelectionMode CombineMode = EGeometryScriptCombineSelectionMode::Add );`
- L139 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ConvertIndexArrayToMeshSelection( UDynamicMesh* TargetMesh, const TArray<int32>& IndexArray, EGeometryScriptMeshSelectionType SelectionType, FGeometryScriptMeshSelection& Selection);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Create a Mesh Selection from the IndexArray. @param SelectionType type of indices specified in the selection
- L151 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ConvertIndexSetToMeshSelection( UDynamicMesh* TargetMesh, const TSet<int32>& IndexSet, EGeometryScriptMeshSelectionType SelectionType, FGeometryScriptMeshSelection& Selection);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Create a Mesh Selection from the IndexSet. @param SelectionType type of indices specified in the selection
- L163 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ConvertMeshSelectionToIndexArray( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, TArray<int32>& IndexArray, EGeometryScriptMeshSelectionType& SelectionType);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Convert a Mesh Selection to an Index Array @param ConvertToType optional parameter specifying the type of Index List to convert to. If Set to Any, no conversion will be performed.
- L176 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ConvertIndexListToMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptIndexList IndexList, EGeometryScriptMeshSelectionType SelectionType, FGeometryScriptMeshSelection& Selection);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Create a Mesh Selection from the Index List. For cases where the IndexList Type does not match the SelectionType, ConvertMeshSelection with bAllowPartialInclusion=true is used to convert. @param SelectionType type of indices desired in the Output selection
- L188 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ConvertMeshSelectionToIndexList( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FGeometryScriptIndexList& IndexList, EGeometryScriptIndexType& ResultListType, EGeometryScriptIndexType ConvertToType = EGeometryScriptIndexType::Any);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Convert a Mesh Selection to an Index List @param ConvertToType optional parameter specifying the type of Index List to convert to. If Set to Any, no conversion will be performed.
- L203 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshElementsInBox( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection& Selection, FBox Box, EGeometryScriptMeshSelectionType SelectionType = EGeometryScriptMeshSelectionType::Triangles, bool bInvert = false, UPARAM(DisplayName = "Min Element Vertices") int MinNum` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod, AdvancedDisplay="MinNumTrianglePoints"))` — Create a new Mesh Selection of the SelectionType for the TargetMesh by finding all elements contained in the Box. @param bInvert return a selection of all elements not in the Box @param MinElementVertices number of vertices of a triangle or edge that must be in the box for it to be selected (clamped to 1-3 for tri; 1-2 for edge)
- L220 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshElementsInSphere( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection& Selection, FVector SphereOrigin = FVector::ZeroVector, double SphereRadius = 100.0, EGeometryScriptMeshSelectionType SelectionType = EGeometryScriptMeshSelectionType::Triangles, bool bInvert = false, UPARAM(DisplayName = "Min Element Vertices") int MinNum` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod, AdvancedDisplay="MinNumTrianglePoints"))` — Create a new Mesh Selection of the SelectionType for the TargetMesh by finding all elements contained in the Sphere. @param SphereOrigin center point of the Sphere @param SphereRadius radius of the Sphere @param bInvert return a selection of all elements not in the Sphere @param MinElementVertices number of vertices of a triangle or edge that must be in the Sphere for it to be selected (clamped to 1-3 for tri; 1-2 for edge)
- L238 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshElementsWithPlane( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection& Selection, FVector PlaneOrigin = FVector::ZeroVector, FVector PlaneNormal = FVector::UpVector, EGeometryScriptMeshSelectionType SelectionType = EGeometryScriptMeshSelectionType::Triangles, bool bInvert = false, UPARAM(DisplayName = "Min Element Vertices") int MinNum` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod, AdvancedDisplay="MinNumTrianglePoints"))` — Create a new Mesh Selection of the SelectionType for the TargetMesh by finding all elements on the "positive" side of a Plane @param PlaneOrigin center point of the Plane @param PlaneNormal normal vector for the Plane @param bInvert return a selection of all elements on the other (negative) side of the Plane @param MinElementVertices number of vertices of a triangle or edge that must be on the positive Plane side to be selected (clamped to 1-3 for tri; 1-2 for edge)
- L258 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshElementsByNormalAngle( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection& Selection, FVector Normal = FVector::UpVector, double MaxAngleDeg = 1.0, EGeometryScriptMeshSelectionType SelectionType = EGeometryScriptMeshSelectionType::Triangles, bool bInvert = false, UPARAM(DisplayName = "Min Element Vertices") int MinNum` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod, AdvancedDisplay="MinNumTrianglePoints"))` — Create a new Mesh Selection of the SelectionType for the TargetMesh by finding all elements that have a normal vector that is within an angular deviation threshold from the given Normal. For Triangle and PolyGroup selections the triangle facet normal is used, for Vertex selections the per-vertex averaged normal is used. @param Normal normal/direction vector to measure against @param MaxAngleDeg maximum angular deviation from Normal, in degrees @param bInvert return a selection of all elements not within the given deviation @param MinElementVertices number of vertices of a triangle or edge that must be within the angular deviation for it to be selected  (clamped to 1-3 for tri; 1-2 for edge)
- L272 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshSharpEdges( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection& Selection, double MinAngleDeg = 20.0 );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta = (ScriptMethod))` — Create a new Selection, for the TargetMesh, of all 'sharp' edges where the edge's adjacent triangle normals differ by at least MinAngleDeg
- L283 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshSplitNormalEdges( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection& Selection );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta = (ScriptMethod))` — Create a new Selection, for the TargetMesh, of all edges seams in the mesh normal topology -- i.e., where normals can be different across the edge
- L293 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshBoundaryEdges( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection& Selection );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta = (ScriptMethod))` — Create a new Selection, for the TargetMesh, of all mesh boundary edges
- L304 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectSelectionBoundaryEdges( UDynamicMesh* TargetMesh, const FGeometryScriptMeshSelection& Selection, FGeometryScriptMeshSelection& BoundarySelection, bool bExcludeMeshBoundaryEdges = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta = (ScriptMethod))` — Create a new BoundarySelection, for the TargetMesh, of the edges on the boundary of another Selection @param bExcludeMeshBoundaryEdges If true, do not include Selection boundary edges if they are also mesh boundary edges
- L320 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshUVSeamEdges( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection& Selection, UPARAM(DisplayName = "UV Channel") int32 UVChannel, bool& bHaveValidUVs, bool bExcludeMeshBoundaryEdges = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta = (ScriptMethod, DisplayName = "Select Mesh UV Seam Edges"))` — Create a new Mesh Selection of UV seam edges for the TargetMesh @param UVChannel Seams will be found with respect to this UV Channel @param bHaveValidUVs If false, the requested UV Channel was not present on the TargetMesh @param bExcludeMeshBoundaryEdges If true, do not include mesh boundary edges in the selection; otherwise, they will be included.
- L333 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshPolyGroupBoundaryEdges( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection& Selection, FGeometryScriptGroupLayer GroupLayer, bool bExcludeMeshBoundaryEdges = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta = (ScriptMethod, DisplayName = "Select Mesh PolyGroup Boundary Edges"))` — Create a new Mesh Selection of PolyGroup boundary edges for the TargetMesh @param GroupLayer PolyGroup layer to reference @param bExcludeMeshBoundaryEdges If true, do not include mesh boundary edges in the selection; otherwise, they will be included.
- L351 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshElementsInsideMesh( UDynamicMesh* TargetMesh, UDynamicMesh* SelectionMesh, FGeometryScriptMeshSelection& Selection, FTransform SelectionMeshTransform, EGeometryScriptMeshSelectionType SelectionType = EGeometryScriptMeshSelectionType::Triangles, bool bInvert = false, double ShellDistance = 0.0, double WindingThreshold = 0.5, UPARAM(DisplayName = "Min Element Vertices") int MinNum` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod, AdvancedDisplay="MinNumTrianglePoints"))` — Create a new Mesh Selection of the SelectionType for the TargetMesh by finding all elements inside a second SelectionMesh For Triangle and PolyGroup selections the triangle facet normal is used, for Vertex selections the per-vertex averaged normal is used. @param SelectionMeshTransform Transform applied to SelectionMesh for inside/outside testing @param bInvert return a selection of all elements not within the given deviation @param ShellDistance If > 0, points within this distance from SelectionMesh will also be considered "inside" @param WindingThreshold Threshold used for Fast Mesh Winding Number inside/outside test (range is [0,1], with 1 being "inside") @param MinElementVertices number of vertices of a triangle or edge that must be within the selection mesh for it to be selected  (clamped to 1-3 for tri; 1-2 for edge)
- L369 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* InvertMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FGeometryScriptMeshSelection& NewSelection, bool bOnlyToConnected = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Invert the Selection on the TargetMesh, ie select what is not currently selected @param bOnlyToConnected if true, the inverse is limited to mesh areas geometrically connected to the Selection, instead of the entire mesh
- L382 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ExpandMeshSelectionToConnected( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FGeometryScriptMeshSelection& NewSelection, EGeometryScriptTopologyConnectionType ConnectionType = EGeometryScriptTopologyConnectionType::Geometric );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Expand the Selection on the TargetMesh to connected regions and return the NewSelection @param ConnectionType defines what "connected" means, ie purely geometric connection, or some additional constraint like same MaterialIDs/etc
- L400 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ExpandContractMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FGeometryScriptMeshSelection& NewSelection, int32 Iterations = 1, bool bContract = false, bool bOnlyExpandToFaceNeighbours = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshSelection", meta=(ScriptMethod))` — Grow or Shrink the Selection on the TargetMesh to connected neighbours. For Vertex selections, Expand includes vertices in one-ring of selected vertices, and Contract removes any vertices with a one-ring neighbour that is not selected For Triangle selections, Add/Remove Triangles connected to selected Triangles For PolyGroup selections, Add/Remove PolyGroups connected to selected PolyGroups @param Iterations number of times to Expand/Contract the Selection. Valid range is [0,100] where 0 is a no-op. @param bContract if true selection contracts instead of growing @param bOnlyExpandToFaceNeighbours if true, only adjacent Triangles/PolyGroups directly connected by an edge are added, vs connected to any selected vertex

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshSelectionQueryFunctions.h` (Public)


#### class `UGeometryScriptLibrary_MeshSelectionQueryFunctions`  
`class UGeometryScriptLibrary_MeshSelectionQueryFunctions : public UBlueprintFunctionLibrary`  
_L14-51_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshSelectionQueries"))`
- inherits: `UBlueprintFunctionLibrary`
- L24 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMeshSelectionBoundingBox( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FBox& SelectionBounds, bool& bIsEmpty, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SelectionQueries", meta=(ScriptMethod, HidePin = "Debug"))` — Get the 3D Bounding Box of a Mesh Selection, ie bounding box of vertices contained in the Selection @param bIsEmpty will return as true if the selection was empty (the box will be initialized to 0 in this case)
- L42 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMeshSelectionBoundaryLoops( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, TArray<FGeometryScriptIndexList>& IndexLoops, TArray<FGeometryScriptPolyPath>& PathLoops, int& NumLoops, bool& bFoundErrors, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SelectionQueries", meta=(ScriptMethod, HidePin = "Debug"))` — Compute the set of Vertex Loops bordering a Mesh Selection. Both the 3D polylines and lists of vertex indices are returned for each Loop. Note that for a Vertex selection this will function return the border loops around the set of vertex triangle one-rings. @param IndexLoops for each discovered Loop, the IndexList of mesh vertex indices around the loop is returned here @param PathLoops for each discovered Loop, the PolyPath of mesh vertex positions around the loop is returned here. The ordering for each loop is the same as IndexLoops. @param NumLoops number of loops found is returned here @param bFoundErrors true is returned here if topological errors were found during loop computation. In this case the Loop set may be incomplete.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshSimplifyFunctions.h` (Public)


#### struct `FGeometryScriptPlanarSimplifyOptions`  
`struct FGeometryScriptPlanarSimplifyOptions`  
_L15-26_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `float AngleThreshold = 0.001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L25 _public member_ `bool bAutoCompact = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If enabled, the simplified mesh is automatically compacted to remove gaps in the index space. This is expensive and can be disabled by advanced users.

#### struct `FGeometryScriptPolygroupSimplifyOptions`  
`struct FGeometryScriptPolygroupSimplifyOptions`  
_L29-40_
- reflection: `USTRUCT(BlueprintType)`
- L35 _public member_ `float AngleThreshold = 0.001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L39 _public member_ `bool bAutoCompact = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If enabled, the simplified mesh is automatically compacted to remove gaps in the index space. This is expensive and can be disabled by advanced users.

#### enum `EGeometryScriptRemoveMeshSimplificationType`  
`enum class EGeometryScriptRemoveMeshSimplificationType : uint8`  
_L44-57_
- reflection: `UENUM(BlueprintType)`
- L47 _public enumerator_ `StandardQEM = 0 UMETA(DisplayName = "Standard QEM")` — classic quadric error metric without volume preservation
- L50 _public enumerator_ `VolumePreserving = 1 UMETA(DisplayName = "Volume Preserving")` — classic quadric error metric with volume preservation
- L53 _public enumerator_ `AttributeAware = 2 UMETA(DisplayName = "Normals Aware, Volume Preserving")` — QEM with volume preservation, account for vertex normals in optimization. This used to be called Attribute Aware prior to 5.8.
- L56 _public enumerator_ `AttributeAwareV2 = 3 UMETA(DisplayName = "Attribute Aware, Volume Preserving")` — QEM with volume preservation, accounting for normals/tangents/bitangents/color/texture coordinates and weight channels with attribute seams.

#### enum `EGeometryScriptMeshSimplificationQuadricVariant`  
`enum class EGeometryScriptMeshSimplificationQuadricVariant : uint8`  
_L60-64_
- reflection: `UENUM(BlueprintType)`
- L62 _public enumerator_ `PlaneQuadric = 0`
- L63 _public enumerator_ `TriangleQuadric = 1`

#### struct `FGeometryScriptWeightMapDensity`  
`struct FGeometryScriptWeightMapDensity`  
_L68-83_
- reflection: `USTRUCT(BlueprintType)`
- desc: Specify a weight map for controlling relative density of a mesh
- L75 _public member_ `FGeometryScriptWeightMapHandle Handle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The weight map to reference
- L82 _public member_ `float RelativeDensity = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = "-3.0", UIMax = "3.0"))` — Controls the effect of the weight map: Positive values increase local mesh density for larger weights, negative values decrease density, and zero gives no effect

#### struct `FGeometryScriptSimplifyMeshOptions`  
`struct FGeometryScriptSimplifyMeshOptions`  
_L86-156_
- reflection: `USTRUCT(Blueprintable)`
- L92 _public member_ `EGeometryScriptRemoveMeshSimplificationType Method = EGeometryScriptRemoveMeshSimplificationType::AttributeAware;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L95 _public member_ `bool bAllowSeamCollapse = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L98 _public member_ `bool bAllowSeamSmoothing = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L101 _public member_ `bool bAllowSeamSplits = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L104 _public member_ `bool bPreserveVertexPositions = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L107 _public member_ `bool bRetainQuadricMemory = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L111 _public member_ `FGeometryScriptWeightMapDensity EdgeLengthWeightMap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Optional weight map to scale measured edge lengths
- L115 _public member_ `FGeometryScriptWeightMapDensity GeometricToleranceWeightMap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Optional weight map to scale measured geometric errors
- L119 _public member_ `FGeometryScriptWeightMapDensity QuadricErrorWeightMap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Optional weight map to scale measured quadric error
- L123 _public member_ `float RegularizeWeight = 0.000001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (ClampMin = "0.0", ClampMax = "10.0", UIMax = ".01"))` — Setting a very small RegularizeWeight value (e.g., 0.000001) can improve triangle quality and the effect of the QuadricErrorWeightMap in flat regions
- L127 _public member_ `bool bAutoCompact = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If enabled, the simplified mesh is automatically compacted to remove gaps in the index space. This is expensive and can be disabled by advanced users.
- L130 _public member_ `EGeometryScriptMeshSimplificationQuadricVariant QuadricVariant = EGeometryScriptMeshSimplificationQuadricVariant::PlaneQuadric;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L134 _public member_ `float NormalAttributeWeight = 16.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Control the influence of the normals to the simplification metric (for attribute-aware quadrics)
- L138 _public member_ `float TangentAttributeWeight = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Control the influence of tangents and bitangents to the simplification metric (for attribute-aware quadrics)
- L142 _public member_ `float ColorAttributeWeight = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Control the influence of color channels to the simplification metric. alpha is ignored but preserved. (for attribute-aware quadrics)
- L146 _public member_ `float TexCoordAttributeWeight = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Control the influence of texture coordinates the simplification metric (all available channels). (for attribute-aware quadrics)
- L154 _public member_ `float ScaleCorrection = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The behavior of the simplifier is not scale invariant: scaling an object by X will impact the geometry terms X^2 times more than it will impact the attributes and change the relative impact. To facilitate rebalancing, while working with the same attribute weights, this setting can be used. Its meaning corresponds to the scale of the object relative to the scale at which the attribute weights were initially calibrated for. This means, setting this value to X results in the same behavior as if the object was scaled down by a factor of X and rescaled back up after simplification. Only supported for attribute aware method.

#### enum `EGeometryScriptClusterSimplifyConstraintLevel`  
`enum class EGeometryScriptClusterSimplifyConstraintLevel : uint8`  
_L159-168_
- reflection: `UENUM(BlueprintType)`
- L162 _public enumerator_ `Fixed` — Edge will be kept as-is in final output
- L165 _public enumerator_ `Constrained` — Attempt to preserve 'paths' of constrained edges, but may simplify along the path Vertices where paths converge will be kept in final output
- L167 _public enumerator_ `Free` — Edge can be simplified without constraint

#### struct `FGeometryScriptClusterSimplifyEdgeConstraintOptions`  
`struct FGeometryScriptClusterSimplifyEdgeConstraintOptions`  
_L171-193_
- reflection: `USTRUCT(BlueprintType)`
- L177 _public member_ `EGeometryScriptClusterSimplifyConstraintLevel MeshBoundary = EGeometryScriptClusterSimplifyConstraintLevel::Constrained;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConstraintOptions)`
- L180 _public member_ `EGeometryScriptClusterSimplifyConstraintLevel GroupBoundary = EGeometryScriptClusterSimplifyConstraintLevel::Constrained;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConstraintOptions)`
- L183 _public member_ `EGeometryScriptClusterSimplifyConstraintLevel MaterialBoundary = EGeometryScriptClusterSimplifyConstraintLevel::Constrained;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConstraintOptions)`
- L186 _public member_ `EGeometryScriptClusterSimplifyConstraintLevel UVSeam = EGeometryScriptClusterSimplifyConstraintLevel::Constrained;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConstraintOptions)`
- L189 _public member_ `EGeometryScriptClusterSimplifyConstraintLevel ColorSeam = EGeometryScriptClusterSimplifyConstraintLevel::Constrained;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConstraintOptions)`
- L192 _public member_ `EGeometryScriptClusterSimplifyConstraintLevel NormalSeam = EGeometryScriptClusterSimplifyConstraintLevel::Constrained;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConstraintOptions)`

#### struct `FGeometryScriptClusterSimplifyMeshOptions`  
`struct FGeometryScriptClusterSimplifyMeshOptions`  
_L196-222_
- reflection: `USTRUCT(BlueprintType)`
- L204 _public member_ `bool bDiscardAttributes = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to discard attributes (materials, UV/normal/tangent/color attributes) Note that attribute seam edges will not be constrained if attributes are discarded
- L208 _public member_ `double FixBoundaryAngleTolerance = 45;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If > 0, boundary vertices w/ incident boundary edge angle greater than this (in degrees) will be kept in the output
- L212 _public member_ `FGeometryScriptClusterSimplifyEdgeConstraintOptions EdgeConstraints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Options to constrain simplification of different mesh edge types, to optionally help preserve mesh boundaries and seams
- L216 _public member_ `FGeometryScriptWeightMapHandle WeightMapHandle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Optional weight map to control simplification error tolerances and/or edge lengths
- L220 _public member_ `float RelativeDensity = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = "-2.0", UIMax = "2.0"))` — Amount to adjust density in regions where the vertex weight map is greater than zero. A positive value results in less simplification in weighted regions, while a negative value results in more

#### class `UGeometryScriptLibrary_MeshSimplifyFunctions`  
`class UGeometryScriptLibrary_MeshSimplifyFunctions : public UBlueprintFunctionLibrary`  
_L227-333_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshSimplification"))`
- inherits: `UBlueprintFunctionLibrary`
- L237 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplySimplifyToPlanar( UDynamicMesh* TargetMesh, FGeometryScriptPlanarSimplifyOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Simplification", meta=(ScriptMethod, HidePin = "Debug"))` — Simplifies planar areas of the mesh that have more triangles than necessary. Note that it does not change the 3D shape of the mesh. Planar regions are identified by comparison of face normals using a Angle Threshold in the Options.
- L248 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplySimplifyToPolygroupTopology( UDynamicMesh* TargetMesh, FGeometryScriptPolygroupSimplifyOptions Options, FGeometryScriptGroupLayer GroupLayer, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Simplification", meta=(ScriptMethod, HidePin = "Debug", DisplayName = "Apply Simplify To PolyGroup Topology"))` — Simplifies the mesh down to the PolyGroup Topology. For example, the high-level faces of the mesh PolyGroups. Another example would be on a default Box-Sphere where simplifying to PolyGroup topology produces a box.
- L259 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplySimplifyToTriangleCount( UDynamicMesh* TargetMesh, int32 TriangleCount, FGeometryScriptSimplifyMeshOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Simplification", meta=(ScriptMethod, HidePin = "Debug"))` — Simplifies the mesh until a target triangle count is reached. Behavior can be additionally controlled with the Options.
- L270 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplySimplifyToVertexCount( UDynamicMesh* TargetMesh, int32 VertexCount, FGeometryScriptSimplifyMeshOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Simplification", meta=(ScriptMethod, HidePin = "Debug"))` — Simplifies the mesh until a target vertex count is reached. Behavior can be additionally controlled with the Options.
- L281 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyEditorSimplifyToTriangleCount( UDynamicMesh* TargetMesh, int32 TriangleCount, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Simplification", meta = (ScriptMethod, HidePin = "Debug"))` — Simplifies the mesh until a target triangle count is reached, using the UE Editor's standard mesh simplifier. Editor only.
- L291 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyEditorSimplifyToVertexCount( UDynamicMesh* TargetMesh, int32 VertexCount, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Simplification", meta=(ScriptMethod, HidePin = "Debug"))` — Simplifies the mesh until a target vertex count is reached, using the UE Editor's standard mesh simplifier. Editor only.
- L302 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplySimplifyToTolerance( UDynamicMesh* TargetMesh, float Tolerance, FGeometryScriptSimplifyMeshOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Simplification", meta=(ScriptMethod, HidePin = "Debug"))` — Simplifies the mesh to a target geometric tolerance. Stops when any further simplification would result in a deviation from the input mesh larger than the tolerance. Behavior can be additionally controlled with the Options.
- L314 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplySimplifyToEdgeLength( UDynamicMesh* TargetMesh, double EdgeLength, FGeometryScriptSimplifyMeshOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Simplification", meta=(ScriptMethod, HidePin = "Debug"))` — Simplifies the mesh to a target edge length, using error-based edge collapse. Note: Not intended to create uniform edge lengths. Result may have edge lengths much larger than the target value.
- L326 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyClusterSimplifyToEdgeLength( UDynamicMesh* TargetMesh, double EdgeLength, FGeometryScriptClusterSimplifyMeshOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Simplification", meta = (ScriptMethod, HidePin = "Debug"))` — Simplifies the mesh to a target edge length, using a fast cluster-based method (not error-based). Note: Lengths are approximated via 'graph distance' on the original mesh; will not exactly match the target.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshSpatialFunctions.h` (Public)


#### struct `FGeometryScriptSpatialQueryOptions`  
`struct FGeometryScriptSpatialQueryOptions`  
_L17-30_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "BVH Query Options"))`
- L22 _public member_ `float MaxDistance = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L26 _public member_ `bool bAllowUnsafeModifiedQueries = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — When true, allows the provided BHV to be used even if the mesh has been updated
- L29 _public member_ `float WindingIsoThreshold = 0.5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptRayHitResult`  
`struct FGeometryScriptRayHitResult`  
_L37-55_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Ray Hit Result"))`
- L42 _public member_ `bool bHit = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L45 _public member_ `float RayParameter = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L48 _public member_ `int HitTriangleID = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L51 _public member_ `FVector HitPosition = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L54 _public member_ `FVector HitBaryCoords = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### class `UGeometryScriptLibrary_MeshSpatial`  
`class UGeometryScriptLibrary_MeshSpatial : public UBlueprintFunctionLibrary`  
_L60-180_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshSpatial"))`
- inherits: `UBlueprintFunctionLibrary`
- L69 _public prototype_ `static void ResetBVH(UPARAM(ref) FGeometryScriptDynamicMeshBVH& ResetBVH);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Spatial", meta = (ScriptMethod))` — Reset the Bounding Volume Hierarchy (BVH) by clearing all the internal data.
- L75 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* BuildBVHForMesh( UDynamicMesh* TargetMesh, FGeometryScriptDynamicMeshBVH& OutputBVH, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Spatial", meta=(ScriptMethod, HidePin = "Debug", DisplayName="Build BVH For Mesh"))` — Builds a Bounding Volume Hierarchy (BVH) object for a mesh that can be used with multiple spatial queries.
- L85 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* IsBVHValidForMesh( UDynamicMesh* TargetMesh, UPARAM(ref) const FGeometryScriptDynamicMeshBVH& TestBVH, bool& bIsValid, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Spatial", meta=(ScriptMethod, HidePin = "Debug", DisplayName="Is BVH Valid For Mesh"))` — Checks if the provided Bounding Volume Hierarchy (BVH) can still be used with the Mesh — it generally returns false if the mesh has been changed.
- L96 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RebuildBVHForMesh( UDynamicMesh* TargetMesh, UPARAM(ref) FGeometryScriptDynamicMeshBVH& UpdateBVH, bool bOnlyIfInvalid = true, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Spatial", meta=(ScriptMethod, HidePin = "Debug", DisplayName="Rebuild BVH For Mesh"))` — Rebuilds the Bounding Volume Hierarchy (BVH) for the mesh in-place, which can reduce memory allocations, compared to building a new BVH.
- L112 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* FindNearestPointOnMesh( UDynamicMesh* TargetMesh, UPARAM(ref) const FGeometryScriptDynamicMeshBVH& QueryBVH, FVector QueryPoint, FGeometryScriptSpatialQueryOptions Options, FGeometryScriptTrianglePoint& NearestResult, EGeometryScriptSearchOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Spatial", meta=(ScriptMethod, HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Finds the nearest point (Nearest Result) on the Target Mesh to a given 3D point (Query Point) by using the Query BVH. @param QueryBVH a BVH associated with the Target Mesh @param QueryPoint a 3D location relative to the local space of the mesh @param NearestResult on return, holds the nearest point on the mesh to the QueryPoint @param Outcome will be either Found or Not Found depending on the success of the query. Note NearestResult.bValid will be false if the query failed.
- L128 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* FindNearestRayIntersectionWithMesh( UDynamicMesh* TargetMesh, UPARAM(ref) const FGeometryScriptDynamicMeshBVH& QueryBVH, FVector RayOrigin, FVector RayDirection, FGeometryScriptSpatialQueryOptions Options, FGeometryScriptRayHitResult& HitResult, EGeometryScriptSearchOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Spatial", meta=(ScriptMethod, HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Finds the nearest intersection of a 3D ray with the mesh by using the Query BVH. Note, depending on the Ray Origin and Ray Direction, there is the possibility that the ray might not intersect with the Target Mesh. Should the ray miss, the HitResult.bHit will be false and the Outcome  will be Not Found.
- L146 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* IsPointInsideMesh( UDynamicMesh* TargetMesh, UPARAM(ref) const FGeometryScriptDynamicMeshBVH& QueryBVH, FVector QueryPoint, FGeometryScriptSpatialQueryOptions Options, bool& bIsInside, EGeometryScriptContainmentOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Spatial", meta=(ScriptMethod, HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Tests if a point is inside the mesh using the Fast Winding Number query and data stored in the BVH. @param QueryBVH is an acceleration structure previously built with this mesh. @param QueryPoint the point in the mesh's 3D local space. @param Options control the fast winding number threshold
- L169 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SelectMeshElementsInBoxWithBVH( UDynamicMesh* TargetMesh, UPARAM(ref) const FGeometryScriptDynamicMeshBVH& QueryBVH, FBox QueryBox, FGeometryScriptSpatialQueryOptions Options, FGeometryScriptMeshSelection& Selection, EGeometryScriptMeshSelectionType SelectionType = EGeometryScriptMeshSelectionType::Vertices, UPARAM(DisplayName = "Min Element Vertices") int MinNumTrianglePoints = 3, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Spatial", meta=(ScriptMethod, HidePin = "Debug", AdvancedDisplay = "MinNumTrianglePoints"))` — Create Mesh Selection of mesh elements in TargetMesh contained by QueryBox, using QueryBVH to accellerate the computation. Triangles and Edges are selected if Min Element Vertices (clamped to a 1-3 or 1-2 range, for triangles or edges respectively) or more are inside the box. PolyGroups are selected if any of their triangles are inside the box Note that this method cannot select mesh elements that cut through the query box without having any vertices in the query box. @param QueryBVH is an acceleration structure previously built with TargetMesh. @param QueryPoint the point in the mesh's 3D local space. @param Options control the fast winding number threshold

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshSubdivideFunctions.h` (Public)


#### struct `FGeometryScriptPNTessellateOptions`  
`struct FGeometryScriptPNTessellateOptions`  
_L19-25_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "PN Tessellate Options"))`
- desc: PN Tessellate options
- L24 _public member_ `bool bRecomputeNormals = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### enum `ESelectiveTessellatePatternType`  
`enum class ESelectiveTessellatePatternType : uint8`  
_L32-35_
- reflection: `UENUM(BlueprintType)`
- desc: Selective Tessellate options
- L34 _public enumerator_ `ConcentricRings = 0`

#### struct `FGeometryScriptSelectiveTessellateOptions`  
`struct FGeometryScriptSelectiveTessellateOptions`  
_L39-49_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Selective Tessellate Options"))`
- L44 _public member_ `bool bEnableMultithreading = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L48 _public member_ `EGeometryScriptEmptySelectionBehavior EmptyBehavior = EGeometryScriptEmptySelectionBehavior::FullMeshSelection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — EmptyBehavior Defines how an empty input selection should be interpreted

#### class `UGeometryScriptLibrary_MeshSubdivideFunctions`  
`class UGeometryScriptLibrary_MeshSubdivideFunctions : public UBlueprintFunctionLibrary`  
_L53-98_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshSubdivide"))`
- inherits: `UBlueprintFunctionLibrary`
- L64 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyPNTessellation( UDynamicMesh* TargetMesh, FGeometryScriptPNTessellateOptions Options, int TessellationLevel = 3, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Subdivide", meta=(ScriptMethod, HidePin = "Debug", DisplayName = "Apply PN Tessellation"))` — Apply PN Tessellation to the Target Mesh as controlled by the Tessellation Level and the Options.
- L75 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyUniformTessellation( UDynamicMesh* TargetMesh, int TessellationLevel = 3, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Subdivide", meta=(ScriptMethod, HidePin = "Debug"))` — Apply Uniform Tessellation to the Target Mesh as controlled by the Tessellation Level and the Options.
- L89 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplySelectiveTessellation( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FGeometryScriptSelectiveTessellateOptions Options, int TessellationLevel = 1, ESelectiveTessellatePatternType PatternType = ESelectiveTessellatePatternType::ConcentricRings, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Subdivide", meta=(ScriptMethod, HidePin = "Debug"))` — Selectively Tessellate a Selection of the Target Mesh or possibly the entire mesh as controlled by the Options. @param Selection selects the triangles of the mesh to be tessellated. @param Options controls the behavior of the tessellation if the Selection is empty. @param TessellationLevel determines the amount of tessellation

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshTransformFunctions.h` (Public)


#### class `UGeometryScriptLibrary_MeshTransformFunctions`  
`class UGeometryScriptLibrary_MeshTransformFunctions : public UBlueprintFunctionLibrary`  
_L17-153_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshTransforms"))`
- inherits: `UBlueprintFunctionLibrary`
- L26 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* TransformMesh( UDynamicMesh* TargetMesh, FTransform Transform, bool bFixOrientationForNegativeScale = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Transforms", meta=(ScriptMethod, HidePin = "Debug", AdvancedDisplay = "bFixOrientationForNegativeScale"))` — Applies the provided Transform to the vertices of a Mesh.
- L37 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* InverseTransformMesh( UDynamicMesh* TargetMesh, FTransform Transform, bool bFixOrientationForNegativeScale = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Transforms", meta = (ScriptMethod, HidePin = "Debug", AdvancedDisplay = "bFixOrientationForNegativeScale"))` — Applies the inverse of the provided Transform to the TargetMesh
- L48 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* TranslateMesh( UDynamicMesh* TargetMesh, FVector Translation, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Transforms", meta=(ScriptMethod, HidePin = "Debug"))` — Applies the provided Translation to the vertices of a Mesh.
- L58 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RotateMesh( UDynamicMesh* TargetMesh, FRotator Rotation, FVector RotationOrigin = FVector(0,0,0), UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Transforms", meta=(ScriptMethod, HidePin = "Debug"))` — Rotates the mesh relative to the specified Rotation Origin.
- L69 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ScaleMesh( UDynamicMesh* TargetMesh, FVector Scale = FVector(1,1,1), FVector ScaleOrigin = FVector(0,0,0), bool bFixOrientationForNegativeScale = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Transforms", meta=(ScriptMethod, HidePin = "Debug", AdvancedDisplay = "bFixOrientationForNegativeScale"))` — Applies the provided Scale transformation relative to the Scale Origin to the vertices of a Mesh.
- L83 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* TransformMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FTransform Transform, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Transforms", meta=(ScriptMethod, HidePin = "Debug", AdvancedDisplay = "bFixOrientationForNegativeScale"))` — Applies the given Transform to the vertices identified by the Selection of the mesh.
- L94 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* InverseTransformMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FTransform Transform, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Transforms", meta=(ScriptMethod, HidePin = "Debug", AdvancedDisplay = "bFixOrientationForNegativeScale"))` — Applies the inverse of the given Transform to the vertices identified by the Selection of the TargetMesh.
- L105 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* TranslateMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FVector Translation, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Transforms", meta=(ScriptMethod, HidePin = "Debug"))` — Applies the given Translation to the vertices identified by the Selection of the mesh.
- L116 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RotateMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FRotator Rotation, FVector RotationOrigin = FVector(0,0,0), UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Transforms", meta=(ScriptMethod, HidePin = "Debug"))` — Rotates the selected part of the mesh relative to the specified Rotation Origin.
- L128 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ScaleMeshSelection( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FVector Scale = FVector(1,1,1), FVector ScaleOrigin = FVector(0,0,0), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Transforms", meta=(ScriptMethod, HidePin = "Debug", AdvancedDisplay = "bFixOrientationForNegativeScale"))` — Applies the given Scale transform relative to the Scale Origin to the selection part of the mesh.
- L142 _public function_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* TranslatePivotToLocation( UDynamicMesh* TargetMesh, FVector PivotLocation, UGeometryScriptDebug* Debug = nullptr)` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Transforms", meta=(ScriptMethod, HidePin = "Debug"))` — Set the Pivot Location for the Mesh. Since the Pivot of a Mesh object is always the point at (0,0,0), this function simply translates the mesh by -PivotLocation.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshUVFunctions.h` (Public)


#### struct `FGeometryScriptRepackUVsOptions`  
`struct FGeometryScriptRepackUVsOptions`  
_L17-26_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `int TargetImageWidth = 512;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L25 _public member_ `bool bOptimizeIslandRotation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### enum `EGeometryScriptUVLayoutType`  
`enum class EGeometryScriptUVLayoutType : uint8`  
_L29-39_
- reflection: `UENUM(BlueprintType)`
- L32 _public enumerator_ `Transform` — Apply Scale and Translation properties to all UV values
- L34 _public enumerator_ `Stack` — Uniformly scale and translate each UV island individually to pack it into the unit square, i.e. fit between 0 and 1 with overlap
- L36 _public enumerator_ `Repack` — Uniformly scale and translate UV islands collectively to pack them into the unit square, i.e. fit between 0 and 1 with no overlap
- L38 _public enumerator_ `Normalize` — Scale and translate UV islands to normalize the UV islands' area to match an average texel density.

#### struct `FGeometryScriptLayoutUVsOptions`  
`struct FGeometryScriptLayoutUVsOptions`  
_L42-80_
- reflection: `USTRUCT(BlueprintType)`
- L48 _public member_ `EGeometryScriptUVLayoutType LayoutType = EGeometryScriptUVLayoutType::Repack;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Type of layout applied to input UVs
- L52 _public member_ `int TextureResolution = 1024;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Expected resolution of the output textures; this controls spacing left between UV islands to avoid interpolation artifacts
- L56 _public member_ `float Scale = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Uniform scale applied to UVs after packing
- L60 _public member_ `FVector2D Translation = FVector2D(0, 0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Translation applied to UVs after packing, and after scaling
- L64 _public member_ `bool bPreserveScale = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Force the Repack layout type to preserve existing scaling of UV islands. Note, this might lead to the packing not fitting within a unit square, and therefore is disabled by default.
- L68 _public member_ `bool bPreserveRotation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Force the Repack layout type to preserve existing rotation of UV islands. Note, this might lead to the packing not being as space efficient as possible, and therefore is disabled by default.
- L72 _public member_ `bool bAllowFlips = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Allow the Repack layout type to flip the orientation when rotating UV islands to save space. Note that this may cause problems for downstream operations, and therefore is disabled by default.
- L76 _public member_ `bool bEnableUDIMLayout = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Enable UDIM aware layout and keep islands within their originating UDIM tiles when laying out.
- L79 _public member_ `TMap<int32, int32> UDIMResolutions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (DisplayName = "Per UDIM Texture Resolution"))`

#### enum `EGeometryScriptUVFlattenMethod`  
`enum class EGeometryScriptUVFlattenMethod : uint8`  
_L83-88_
- reflection: `UENUM(BlueprintType)`
- L85 _public enumerator_ `ExpMap = 0`
- L86 _public enumerator_ `Conformal = 1`
- L87 _public enumerator_ `SpectralConformal = 2`

#### enum `EGeometryScriptUVIslandSource`  
`enum class EGeometryScriptUVIslandSource : uint8`  
_L91-95_
- reflection: `UENUM(BlueprintType)`
- L93 _public enumerator_ `PolyGroups = 0`
- L94 _public enumerator_ `UVIslands = 1`

#### struct `FGeometryScriptExpMapUVOptions`  
`struct FGeometryScriptExpMapUVOptions`  
_L99-108_
- reflection: `USTRUCT(BlueprintType)`
- L104 _public member_ `int NormalSmoothingRounds = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L107 _public member_ `float NormalSmoothingAlpha = 0.25f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptSpectralConformalUVOptions`  
`struct FGeometryScriptSpectralConformalUVOptions`  
_L111-117_
- reflection: `USTRUCT(BlueprintType)`
- L116 _public member_ `bool bPreserveIrregularity = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptRecomputeUVsOptions`  
`struct FGeometryScriptRecomputeUVsOptions`  
_L121-142_
- reflection: `USTRUCT(BlueprintType)`
- L126 _public member_ `EGeometryScriptUVFlattenMethod Method = EGeometryScriptUVFlattenMethod::SpectralConformal;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L129 _public member_ `EGeometryScriptUVIslandSource IslandSource = EGeometryScriptUVIslandSource::UVIslands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L132 _public member_ `FGeometryScriptExpMapUVOptions ExpMapOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L135 _public member_ `FGeometryScriptSpectralConformalUVOptions SpectralConformalOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L138 _public member_ `FGeometryScriptGroupLayer GroupLayer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L141 _public member_ `bool bAutoAlignIslandsWithAxes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptPatchBuilderOptions`  
`struct FGeometryScriptPatchBuilderOptions`  
_L149-183_
- reflection: `USTRUCT(BlueprintType)`
- L154 _public member_ `int InitialPatchCount = 100;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L157 _public member_ `int MinPatchSize = 2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L160 _public member_ `float PatchCurvatureAlignmentWeight = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L163 _public member_ `float PatchMergingMetricThresh = 1.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L166 _public member_ `float PatchMergingAngleThresh = 45.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L169 _public member_ `FGeometryScriptExpMapUVOptions ExpMapOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L172 _public member_ `bool bRespectInputGroups = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L175 _public member_ `FGeometryScriptGroupLayer GroupLayer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L179 _public member_ `bool bAutoPack = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L182 _public member_ `FGeometryScriptRepackUVsOptions PackingOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptXAtlasOptions`  
`struct FGeometryScriptXAtlasOptions`  
_L189-195_
- reflection: `USTRUCT(BlueprintType)`
- L194 _public member_ `int MaxIterations = 2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### enum `EGeometryScriptTexelDensityMode`  
`enum class EGeometryScriptTexelDensityMode : uint8`  
_L200-205_
- reflection: `UENUM(BlueprintType)`
- L202 _public enumerator_ `ApplyToIslands`
- L203 _public enumerator_ `ApplyToWhole`
- L204 _public enumerator_ `Normalize`

#### struct `FGeometryScriptUVTexelDensityOptions`  
`struct FGeometryScriptUVTexelDensityOptions`  
_L208-230_
- reflection: `USTRUCT(Blueprintable)`
- L214 _public member_ `EGeometryScriptTexelDensityMode TexelDensityMode = EGeometryScriptTexelDensityMode::ApplyToIslands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L217 _public member_ `float TargetWorldUnits = 100;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L220 _public member_ `float TargetPixelCount = 1024;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L223 _public member_ `float TextureResolution = 1024;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L226 _public member_ `bool bEnableUDIMLayout = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L229 _public member_ `TMap<int32, int32> UDIMResolutions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (DisplayName = "Per UDIM Texture Resolution"))`

#### struct `FGeometryScriptMeshProjectionSettings`  
`struct FGeometryScriptMeshProjectionSettings`  
_L233-254_
- reflection: `USTRUCT(BlueprintType)`
- L240 _public member_ `bool bProcessAllIfEmptySelection = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If selection contains no triangles, project all triangles (for both source and target)
- L244 _public member_ `float ProjectionRangeMax = UE_LARGE_WORLD_MAX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Maximum projection distance
- L248 _public member_ `float ProjectionRangeMin = -UE_LARGE_WORLD_MAX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Minimum projection distance. If negative, will also consider projection backwards, and take the closest result.
- L252 _public member_ `bool bResetUVsForUnmatched = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to reset UVs for triangles where projection failed. Otherwise UVs are left as-is where projection failed.

#### class `UGeometryScriptLibrary_MeshUVFunctions`  
`class UGeometryScriptLibrary_MeshUVFunctions : public UBlueprintFunctionLibrary`  
_L258-724_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_UVs"))`
- inherits: `UBlueprintFunctionLibrary`
- L267 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetNumUVSets( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "Num UV Channels") int NumUVSets, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"), DisplayName = "Set Num UV Channels")` — Set the number of UV Channels on the Target Mesh. If not already enabled, this will enable the mesh attributes.
- L274 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ClearUVChannel( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVChannel, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta = (ScriptMethod, HidePin = "Debug"), DisplayName = "Clear UV Channel")`
- L284 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* CopyUVSet( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "From UV Channel") int FromUVSet, UPARAM(DisplayName = "To UV Channel") int ToUVSet, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"), DisplayName = "Copy UV Channel")` — Copy the data in one UV Channel to another UV Channel on the same Target Mesh.
- L297 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshTriangleUVs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, int TriangleID, FGeometryScriptUVTriangle UVs, bool& bIsValidTriangle, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod))` — Sets the UVs of a mesh triangle in the given UV Channel. This function will create new UV elements for each vertex of the triangle, meaning that the triangle will become an isolated UV island.
- L311 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AddUVElementToMesh( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int32 UVSetIndex, FVector2D NewUVPosition, UPARAM(DisplayName = "New UV Element ID") int& NewUVElementID, bool& bIsValidUVSet, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdits", meta=(ScriptMethod))` — Adds a new UV Element to the specified UV Channel of the Mesh and returns a new UV Element ID.
- L329 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshTriangleUVElementIDs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, int TriangleID, FIntVector TriangleUVElements, bool& bIsValidTriangle, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod))` — Sets the UV Element IDs for a given Triangle in the specified UV Channel, ie the "UV Triangle" indices. This function does not create new UVs, the provided UV Elements must already. The UV Triangle can only be set if the resulting topology would be valid, ie the Elements cannot be shared between different base Mesh Vertices, so they must either be unused by any other triangles, or already associated with the same mesh vertex in other UV triangles. If any conditions are not met, bIsValidTriangle will be returned as false.
- L344 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMeshTriangleUVElementIDs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int32 UVSetIndex, int32 TriangleID, FIntVector& TriangleUVElements, bool& bHaveValidUVs);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta = (ScriptMethod))` — Returns the UV Element IDs associated with the three vertices of the triangle in the specified UV Channel. If the Triangle does not exist in the mesh or if no UVs are set in the specified UV Channel for the triangle, bHaveValidUVs will be returned as false.
- L362 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetUVSeamsAlongSelectedEdges( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVChannel, FGeometryScriptMeshSelection Selection, bool bInsertSeams = true, bool bDeferChangeNotifications = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta = (ScriptMethod, HidePin = "Debug", DisplayName = "Set UV Seams Along Selected Edges"))` — Convert Selection to an Edge selection, and set or remove UV seams along all of the selected edges @param TargetMesh The mesh to update @param UVChannel The UV Channel to update @param Selection Which edges to operate on @param bInsertSeams Whether to insert new seams. If false, removes existing seams instead. @param bDeferChangeNotifications If true, no mesh change notification will be sent. Set to true if performing many changes in a loop.
- L376 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMeshUVElementPosition( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int32 UVSetIndex, int32 ElementID, FVector2D& UVPosition, bool& bIsValidElementID);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta = (ScriptMethod))` — Returns the UV Position for a given UV Element ID in the specified UV Channel. If the UV Set or Element ID does not exist, bIsValidElementID will be returned as false.
- L389 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshUVElementPosition( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, int ElementID, FVector2D NewUVPosition, bool& bIsValidElementID, bool bDeferChangeNotifications = false );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod))` — Sets the UV position of a specific ElementID in the given UV Set/Channel If the UV Set or Element ID does not exist, bIsValidElementID will be returned as false.
- L403 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* TranslateMeshUVs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FVector2D Translation, FGeometryScriptMeshSelection Selection, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Update all selected UV values in the specified UV Channel by adding the Translation value to each. If the provided Selection is empty, the Translation is applied to the entire UV Channel.
- L416 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ScaleMeshUVs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FVector2D Scale, FVector2D ScaleOrigin, FGeometryScriptMeshSelection Selection, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Update all selected UV values in the specified UV Channel by Scale, mathematically the new value is given by (UV - ScaleOrigin) * Scale + ScaleOrigin If the provided Selection is empty, the update is applied to the entire UV Channel.
- L430 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RotateMeshUVs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, float RotationAngle, FVector2D RotationOrigin, FGeometryScriptMeshSelection Selection, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Update all the selected UV values in the specified UV Channel by a rotation of Rotation Angle (in degrees) relative to the Rotation Origin. If the provided Selection is empty, the update is applied to the entire UV Channel.
- L444 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshUVsFromPlanarProjection( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FTransform PlaneTransform, FGeometryScriptMeshSelection Selection, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Scale of PlaneTransform defines world-space dimension that maps to 1 UV dimension
- L457 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshUVsFromBoxProjection( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FTransform BoxTransform, FGeometryScriptMeshSelection Selection, int MinIslandTriCount = 2, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Using Box Projection, update the UVs in the UV Channel for an entire mesh or a subset defined by a non-empty Selection.
- L470 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshUVsFromCylinderProjection( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FTransform CylinderTransform, FGeometryScriptMeshSelection Selection, float SplitAngle = 45.0, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Using Cylinder Projection, update the UVs in the UV Channel for an entire mesh or a subset defined by a non-empty Selection.
- L499 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* TransferMeshUVsByProjection( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "Target UV Channel") int TargetUVChannel, FGeometryScriptMeshSelection TargetSelection, FTransform TargetTransform, const UDynamicMesh* SourceMesh, FGeometryScriptDynamicMeshBVH SourceMeshOptionalBVH, UPARAM(DisplayName = "Source UV Channel") int SourceUVChannel, FGeometryScriptMeshSelection SourceSelection, FTransform SourceTransform, FGeometryScriptMeshProjectionSettings Settings, FVector ProjectionDirection = FVector(0,0,-1), double ProjectionOffset = 0, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta = (ScriptMethod, HidePin = "Debug", Keywords = "Set From Mesh"))` — Copy UVs from one mesh to another, by projecting along the requested direction. Note: This does not transfer UV seams; it assigns a single UV coordinate per vertex in the target mesh selection. By default, also searches in -ProjectionDirection and picks the closest source mesh position to copy from -- set ProjectionRangeMin in Settings to a value >= 0 to only search in +ProjectionDirection. @param TargetMesh Mesh to assign new UVs @param TargetUVChannel UV channel to update on target mesh @param TargetSelection Triangles to update on the target mesh @param TargetTransform Transform of target mesh @param SourceMesh Mesh to transfer UVs from @param SourceMeshOptionalBVH Optional BVH for the source mesh @param SourceUVChannel UV channel to read from on the source mesh @param SourceSelection Triangles to read from on the source mesh @param SourceTransform Transform of the source mesh @param Settings Additional settings @param ProjectionDirection Direction to project (in the space where TargetMesh is transformed by TargetTransform, and SourceMesh is transformed by SourceTransform) @param ProjectionOffset Projection will start offset by this amount from the TargetMesh vertices
- L521 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyTexelDensityUVScaling( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FGeometryScriptUVTexelDensityOptions Options, FGeometryScriptMeshSelection Selection, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug", AdvancedDisplay = "UDIMResolutions"))` — Rescales UVs in the UV Channel for a Mesh to match a specified texel density, described by the options passed in. Supports processing on a subset of UVs via a non-empty Selection.
- L534 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RecomputeMeshUVs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FGeometryScriptRecomputeUVsOptions Options, FGeometryScriptMeshSelection Selection, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Recomputes UVs in the UV Channel for a Mesh based on different types of well-defined UV islands, such as existing UV islands, PolyGroups, or a subset of the mesh based on a non-empty Selection.
- L546 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RepackMeshUVs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FGeometryScriptRepackUVsOptions RepackOptions, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Packs the existing UV islands in the specified UV Channel into standard UV space based on the Repack Options.
- L557 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* LayoutMeshUVs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FGeometryScriptLayoutUVsOptions LayoutOptions, FGeometryScriptMeshSelection Selection, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta = (ScriptMethod, HidePin = "Debug"))` — Packs the existing UV islands in the specified UV Channel into standard UV space based on the Repack Options.
- L569 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AutoGeneratePatchBuilderMeshUVs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FGeometryScriptPatchBuilderOptions Options, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Computes new UVs for the specified UV Channel using PatchBuilder method in the Options, and optionally packs.
- L580 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AutoGenerateXAtlasMeshUVs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FGeometryScriptXAtlasOptions Options, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Computes new UVs for the specified UV Channel using XAtlas, and optionally packs.
- L600 _public prototype_ `static UPARAM(DisplayName = "Copy From Mesh") UDynamicMesh* GetMeshUVSizeInfo( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FGeometryScriptMeshSelection Selection, double& MeshArea, double& UVArea, FBox& MeshBounds, FBox2D& UVBounds, bool& bIsValidUVSet, bool& bFoundUnsetUVs, bool bOnlyIncludeValidUVTris = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Compute information about dimensions and areas for a UV Set of a Mesh, with an optional Mesh Selection @param UVSetIndex index of UV Channel to query @param Selection subset of triangles to process, whole mesh is used if selection is not provided @param MeshArea output 3D area of queried triangles @param UVArea output 2D UV-space area of queried triangles @param MeshBounds output 3D bounding box of queried triangles @param UVBounds output 2D UV-space bounding box of queried triangles @param bIsValidUVSet output flag set to false if UV Channel does not exist on the target mesh. In this case Areas and Bounds are not initialized. @param bFoundUnsetUVs output flag set to true if any of the queried triangles do not have valid UVs set @param bOnlyIncludeValidUVTris if true, only triangles with valid UVs are included in 3D Mesh Area/Bounds
- L626 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMeshPerVertexUVs( UDynamicMesh* TargetMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, FGeometryScriptUVList& UVList, bool& bIsValidUVSet, bool& bHasVertexIDGaps, bool& bHasSplitUVs, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"))` — Get a list of single vertex UVs for each mesh vertex in the TargetMesh, derived from the specified UV Channel. The UV Channel may store multiple UVs for a single vertex (along UV seams) In such cases an arbitrary UV will be stored for that vertex, and bHasSplitUVs will be returned as true @param UVSetIndex index of UV Channel to read @param UVList output UV list will be stored here. Size will be equal to the MaxVertexID of TargetMesh  (not the VertexCount!) @param bIsValidUVSet will be set to true if the UV Channel was valid @param bHasVertexIDGaps will be set to true if some vertex indices in TargetMesh were invalid, ie MaxVertexID > VertexCount @param bHasSplitUVs will be set to true if there were split UVs in the UV Channel
- L651 _public prototype_ `static UPARAM(DisplayName = "Copy From Mesh") UDynamicMesh* CopyMeshUVLayerToMesh( UDynamicMesh* CopyFromMesh, UPARAM(DisplayName = "UV Channel") int UVSetIndex, UPARAM(DisplayName = "Copy To UV Mesh", ref) UDynamicMesh* CopyToUVMesh, UPARAM(DisplayName = "Copy To UV Mesh") UDynamicMesh*& CopyToUVMeshOut, bool& bInvalidTopology, bool& bIsValidUVSet, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"), DisplayName="Copy Mesh UV Channel To Mesh")` — Copy the 2D UVs from the given UV Channel in CopyFromMesh to the 3D vertex positions in CopyToUVMesh, with the triangle mesh topology defined by the UV Channel. Generally this "UV Mesh" topology will not be the same as the 3D mesh topology. PolyGroup IDs and Material IDs are preserved in the UVMesh. 2D UV Positions are copied to 3D as (X, Y, 0) CopyMeshToMeshUVChannel will copy the 3D UV Mesh back to the UV Channel. This pair of functions can then be used to implement UV generation/editing via other mesh functions. @param bInvalidTopology will be returned true if any topological issues were found @param bIsValidUVSet will be returned false if UVSetIndex is not available
- L674 _public prototype_ `static UPARAM(DisplayName = "Copy From Mesh") UDynamicMesh* CopyMeshToMeshUVLayer( UDynamicMesh* CopyFromUVMesh, UPARAM(DisplayName = "To UV Channel") int ToUVSetIndex, UPARAM(DisplayName = "Copy To Mesh", ref) UDynamicMesh* CopyToMesh, UPARAM(DisplayName = "Copy To Mesh") UDynamicMesh*& CopyToMeshOut, bool& bFoundTopologyErrors, UPARAM(DisplayName = "Is Valid UV Channel") bool& bIsValidUVSet, bool bOnlyUVPositions = true, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug"), DisplayName="Copy Mesh To Mesh UV Channel")` — Transfer the 3D vertex positions and triangles of CopyFromUVMesh to the given UV Channel identified by ToUVChannel of CopyToMesh. 3D positions (X,Y,Z) will be copied as UV positions (X,Y), ie Z is ignored. bOnlyUVPositions controls whether only UV positions will be updated, or if the UV topology will be fully replaced. When false, CopyFromUVMesh must currently have a MaxVertexID <= that of the UV Channel MaxElementID When true, CopyFromUVMesh must currently have a MaxTriangleID <= that of CopyToMesh @param bInvalidTopology will be returned true if any topological inconsistencies are found (but the operation will generally continue) @param bIsValidUVSet will be returned false if To UV Channel is not available @param bOnlyUVPositions if true, only (valid, matching) UV positions are updated, a full new UV topology is created
- L699 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ComputeMeshLocalUVParam( UDynamicMesh* TargetMesh, FVector CenterPoint, int32 CenterPointTriangleID, TArray<int>& VertexIDs, TArray<FVector2D>& VertexUVs, double Radius = 1, bool bUseInterpolatedNormal = false, FVector TangentYDirection = FVector(0,0,0), double UVRotationDeg = 0.0, UGeometryScriptDebug* Debug = nullptr );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|UVs", meta=(ScriptMethod, HidePin = "Debug", AdvancedDisplay = "bUseInterpolatedNormal, TangentYDirection"))` — Compute local UV parameterization on TargetMesh vertices around the given CenterPoint / Triangle. This method uses a Discrete Exponential Map parameterization, which unwraps the mesh locally based on geodesic distances and angles. The CenterPoint will have UV value (0,0), and the computed vertex UVs will be such that Length(UV) == geodesic distance. @param CenterPoint the center point of the parameterization. This point must lie on the triangle specified by CenterPointTriangleID @param CenterPointTriangleID the ID of the Triangle that contains CenterPoint @param Radius the parameterization will be computed out to this geodesic radius @param bUseInterpolatedNormal if true (default false), the normal frame used for the parameterization will be taken from the normal overlay, otherwise the CenterPointTriangleID normal will be used @param VertexIDs output list of VertexIDs that UVs have been computed for, ie are within geodesic distance Radius from the CenterPoint @param VertexUVs output list of Vertex UVs that corresponds to VertexIDs
- L721 _public prototype_ `static bool IntersectsUVBox2D(FBox2D A, FBox2D B, bool bWrappedToUnitRange = false);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|UVs", meta = (DisplayName = "Intersects (UV Box2D)"))` — Test two Box2D bounds for intersection, with optional support for working in a wrapped space @param A First box @param B Second box @param bWrappedCoordinates Whether to test the boxes for intersection in a space wrapped to unit range of [0, 1] @return Whether the boxes intersect

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshVertexColorFunctions.h` (Public)


#### enum `EGeometryScriptBlurColorMode`  
`enum class EGeometryScriptBlurColorMode : uint8`  
_L17-25_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `Uniform = 0` — Blur the attributes where each neighbor is weighted equally.
- L22 _public enumerator_ `EdgeLength = 1` — Blur the attributes where each neighbor is weighted proportionally to the shared edge length.
- L24 _public enumerator_ `CotanWeights = 2` — Blur the attributes where each neighbor is weighted proportionally to the cotangent weight of the shared edge.

#### struct `FGeometryScriptBlurMeshVertexColorsOptions`  
`struct FGeometryScriptBlurMeshVertexColorsOptions`  
_L28-47_
- reflection: `USTRUCT(BlueprintType)`
- L34 _public member_ `bool Red = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Blur red channel.
- L38 _public member_ `bool Green = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Blur green channel.
- L42 _public member_ `bool Blue = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Blur blue channel.
- L46 _public member_ `bool Alpha = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Blur alpha channel.

#### enum `ETransferVertexColorMethod`  
`enum class ETransferVertexColorMethod : uint8`  
_L50-65_
- reflection: `UENUM(BlueprintType)`
- L56 _public enumerator_ `ClosestPointOnSurface = 0` — For every vertex on the TargetMesh, find the closest point on the surface of the SourceMesh and transfer colors from it. This is usually a point on the SourceMesh triangle where the colors are computed via interpolation of the colors at the vertices of the triangle via barycentric coordinates.
- L64 _public enumerator_ `Inpaint = 1` — For every vertex on the target mesh, find the closest point on the surface of the source mesh. If that point is within the search radius (controlled via SearchPercentage), and their normals differ by less than the NormalThreshold, then we directly copy the colors from the source point to the target mesh vertex (same as the ClosestPointOnSurface method). For all the vertices we didn't copy the colors directly, automatically compute the smooth colors.

#### struct `FGeometryScriptTransferMeshVertexColorsOptions`  
`struct FGeometryScriptTransferMeshVertexColorsOptions`  
_L68-107_
- reflection: `USTRUCT(BlueprintType)`
- L74 _public member_ `ETransferVertexColorMethod TransferMethod = ETransferVertexColorMethod::ClosestPointOnSurface;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The type of algorithm to use for transferring the colors.
- L79 _public member_ `double RadiusPercentage = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, Meta = (UIMin = -1, UIMax = 2, ClampMin = -1, ClampMax = 2, EditCondition = "TransferMethod == ETransferVertexColorMethod::Inpaint"))` — Defines the search radius as the RadiusPercentage * (input mesh bounding box diagonal). All points not within the search radius will be ignored. If negative, all points are considered. Only used in the Inpaint algorithm.
- L84 _public member_ `double NormalThreshold = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, Meta = (UIMin = -1, UIMax = 180, ClampMin = -1, ClampMax = 180, EditCondition="TransferMethod == ETransferVertexColorMethod::Inpaint"))` — Maximum angle (in degrees) difference between the target and the source point normals to be considered a match. If negative, normals are ignored. Only used in the Inpaint algorithm.
- L90 _public member_ `bool LayeredMeshSupport = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, Meta = (EditCondition = "TransferMethod == ETransferVertexColorMethod::Inpaint"))` — If true, when the closest point doesn't pass the normal threshold test, will try again with a flipped normal. This helps with layered meshes where the "inner" and "outer" layers are close to each other but whose normals are pointing in the opposite directions.
- L94 _public member_ `int32 NumSmoothingIterations = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = 0, UIMax = 100, ClampMin = 0, ClampMax = 100, EditCondition = "TransferMethod == ETransferVertexColorMethod::Inpaint"))` — The number of optional post-processing smoothing iterations applied to the vertices without the match.
- L98 _public member_ `float SmoothingStrength = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = 0, UIMax = 1, ClampMin = 0, ClampMax = 1, EditCondition = "TransferMethod == ETransferVertexColorMethod::Inpaint"))` — The strength of each post-processing smoothing iteration.
- L102 _public member_ `bool bHardEdges = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Creates vertex instances per triangle to be able to have per-face vertex colors.
- L106 _public member_ `float BiasRatio = UE_KINDA_SMALL_NUMBER;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (UIMin = 0, UIMax = 1, ClampMin = 0, ClampMax = 1))` — Ratio used to blend a vertex between its position and the center of the face (0 = vertex position, 1 = face centroid)

#### class `UGeometryScriptLibrary_MeshVertexColorFunctions`  
`class UGeometryScriptLibrary_MeshVertexColorFunctions : public UBlueprintFunctionLibrary`  
_L111-238_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_VertexColors"))`
- inherits: `UBlueprintFunctionLibrary`
- L122 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshConstantVertexColor( UDynamicMesh* TargetMesh, FLinearColor Color, FGeometryScriptColorFlags Flags, bool bClearExisting = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|VertexColor", meta=(ScriptMethod, HidePin = "Debug"))` — Set all vertex colors (optionally specific channels) in the TargetMesh VertexColor Overlay to a constant value @param Color the constant color to set @param Flags specify which RGBA channels to set (default all channels)
- L140 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshSelectionVertexColor( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, FLinearColor Color, FGeometryScriptColorFlags Flags, bool bCreateColorSeam = false, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|VertexColor", meta=(ScriptMethod, HidePin = "Debug"))` — Set the colors in the TargetMesh VertexColor Overlay identified by the Selection to a constant value. For a Vertex Selection, each existing VertexColor Overlay Element for the vertex is updated. For a Triangle or PolyGroup Selection, all Overlay Elements in the identified Triangles are updated. @param Color the constant color to set @param Flags specify which RGBA channels to set (default all channels) @param bCreateColorSeam if true, a "hard edge" in the vertex colors is created, by creating new Elements for all the triangles in the selection. If enabled, Vertex selections are converted to Triangle selections, and Flags is ignored.
- L155 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshPerVertexColors( UDynamicMesh* TargetMesh, FGeometryScriptColorList VertexColorList, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|VertexColor", meta=(ScriptMethod, HidePin = "Debug"))` — Set all vertex colors in the TargetMesh VertexColor Overlay to the specified per-vertex colors @param VertexColorList per-vertex colors. Size must be less than or equal to the MaxVertexID of TargetMesh  (ie gaps are supported)
- L171 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMeshPerVertexColors( UDynamicMesh* TargetMesh, FGeometryScriptColorList& ColorList, bool& bIsValidColorSet, bool& bHasVertexIDGaps, bool bBlendSplitVertexValues = true);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|VertexColor", meta=(ScriptMethod))` — Get a list of single vertex colors for each mesh vertex in the TargetMesh, derived from the VertexColor Overlay. The VertexColor Overlay may store multiple colors for a single vertex (ie different colors for that vertex on different triangles) In such cases the colors can either be averaged, or the last color seen will be used, depending on the bBlendSplitVertexValues parameter. @param ColorList output color list will be stored here. Size will be equal to the MaxVertexID of TargetMesh  (not the VertexCount!) @param bIsValidColorSet will be set to true if the VertexColor Overlay was valid @param bHasVertexIDGaps will be set to true if some vertex indices in TargetMesh were invalid, ie MaxVertexID > VertexCount @param bBlendSplitVertexValues control how multiple colors at the same vertex should be interpreted
- L184 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ConvertMeshVertexColorsSRGBToLinear( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|VertexColor", meta=(ScriptMethod, HidePin = "Debug"))` — Apply a SRGB to Linear color transformation on all vertex colors on the mesh.
- L194 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ConvertMeshVertexColorsLinearToSRGB( UDynamicMesh* TargetMesh, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|VertexColor", meta=(ScriptMethod, HidePin = "Debug"))` — Apply a Linear to SRGB color transformation on all vertex colors on the mesh.
- L210 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* BlurMeshVertexColors( UDynamicMesh* TargetMesh, FGeometryScriptMeshSelection Selection, int NumIterations = 1, double Strength = 0.5, EGeometryScriptBlurColorMode BlurMode = EGeometryScriptBlurColorMode::Uniform, FGeometryScriptBlurMeshVertexColorsOptions Options = FGeometryScriptBlurMeshVertexColorsOptions(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|VertexColor", meta=(ScriptMethod, HidePin = "Debug"))` — Blur the color attribute of the mesh. If the mesh has no color attribute, the function returns the mesh unchanged. @param TargetMesh The mesh containing the color attribute. @param Selection Only vertices in the selection will have their color attribute blurred. @param NumIterations The number of blur iterations. @param Strength Each iteration, we will blur between the vertex of the color at the previous iteration and its neighbors' average by Strength amount (expected to be in the zero to one range). @param BlurMode Determines how neighbors are weighted when computing their average.
- L231 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* TransferVertexColorsFromMesh( UDynamicMesh* SourceMesh, UDynamicMesh* TargetMesh, FGeometryScriptTransferMeshVertexColorsOptions Options = FGeometryScriptTransferMeshVertexColorsOptions(), FGeometryScriptMeshSelection Selection = FGeometryScriptMeshSelection(), UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|VertexColor", meta = (ScriptMethod, HidePin = "Debug"))` — Transfer the vertex colors from the SourceMesh to the TargetMesh. Assumes that the meshes are aligned. Otherwise, use the TransformMesh geometry script function to align them. @param SourceMesh The mesh we are transferring the colors from. @param TargetMesh The mesh we are transferring the colors to. @param Options The options to set for the transfer colors algorithm. @param Selection Optional subset of target mesh vertices to transfer weights to. If left empty, colors will be transferred to all target mesh vertices.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshVoxelFunctions.h` (Public)


#### enum `EGeometryScriptGridSizingMethod`  
`enum class EGeometryScriptGridSizingMethod : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `GridCellSize = 0`
- L18 _public enumerator_ `GridResolution = 1`

#### struct `FGeometryScript3DGridParameters`  
`struct FGeometryScript3DGridParameters`  
_L26-41_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters for 3D grids, eg grids used for sampling, SDFs, voxelization, etc
- L32 _public member_ `EGeometryScriptGridSizingMethod SizeMethod = EGeometryScriptGridSizingMethod::GridResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — SizeMethod determines how the parameters below will be interpreted to define the size of a 3D sampling/voxel grid
- L36 _public member_ `float GridCellSize = 0.5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (EditCondition = "SizeMethod == EGeometryScriptGridSizingMethod::GridCellSize"))` — Use a specific grid cell size, and construct a grid with dimensions large enough to contain the target object
- L40 _public member_ `int GridResolution = 64;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (EditCondition = "SizeMethod == EGeometryScriptGridSizingMethod::GridResolution"))` — Use a specific grid resolution, with the grid cell size derived form the target object bounds such that this is the number of cells along the longest box dimension

#### struct `FGeometryScriptSolidifyOptions`  
`struct FGeometryScriptSolidifyOptions`  
_L45-81_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public member_ `FGeometryScript3DGridParameters GridParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L55 _public member_ `FBox CustomBounds = FBox(EForceInit::ForceInit);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If valid, will be used to define the region of space to operate on. Otherwise, standard bounds based on the input mesh will be computed.
- L59 _public member_ `float WindingThreshold = 0.5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Space with generalized winding number higher than this threshold is considered to be inside the input surface.
- L63 _public member_ `bool bSolidAtBoundaries = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If the solid surface extends beyond the bounds provided, whether to close off the surface at that boundary or leave it open
- L67 _public member_ `float ExtendBounds = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (DisplayName = "Extend Mesh Bounds"))` — Amount to extend bounds, applied to both min and max extents. Only applied to default input-mesh-based bounds, *not* Custom Bounds.
- L71 _public member_ `int SurfaceSearchSteps = 3;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Number of search steps to take when finding the marching cubes surface vertex positions.
- L75 _public member_ `bool bThickenShells = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — When enabled, regions of the input mesh that have open boundaries (ie "shells") are thickened by extruding them into closed solids. This may be expensive on large meshes.
- L79 _public member_ `double ShellThickness = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Open Shells are Thickened by offsetting vertices along their averaged vertex normals by this amount. Dimension is but clamped to twice the grid cell size.

#### enum `EGeometryScriptMorphologicalOpType`  
`enum class EGeometryScriptMorphologicalOpType : uint8`  
_L85-97_
- reflection: `UENUM(BlueprintType)`
- L88 _public enumerator_ `Dilate = 0` — Expand the shapes outward
- L90 _public enumerator_ `Contract = 1` — Shrink the shapes inward
- L92 _public enumerator_ `Close = 2` — Dilate and then contract, to delete small negative features (sharp inner corners, small holes)
- L94 _public enumerator_ `Open = 3` — Contract and then dilate, to delete small positive features (sharp outer corners, small isolated pieces)

#### struct `FGeometryScriptMorphologyOptions`  
`struct FGeometryScriptMorphologyOptions`  
_L103-127_
- reflection: `USTRUCT(BlueprintType)`
- L108 _public member_ `FGeometryScript3DGridParameters SDFGridParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L111 _public member_ `bool bUseSeparateMeshGrid = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L114 _public member_ `FGeometryScript3DGridParameters MeshGridParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L119 _public member_ `FBox CustomBounds = FBox(EForceInit::ForceInit);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If valid, will be used to define the region of space to operate on. Otherwise, standard bounds based on the input mesh will be computed.
- L122 _public member_ `EGeometryScriptMorphologicalOpType Operation = EGeometryScriptMorphologicalOpType::Dilate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L125 _public member_ `float Distance = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### class `UGeometryScriptLibrary_MeshVoxelFunctions`  
`class UGeometryScriptLibrary_MeshVoxelFunctions : public UBlueprintFunctionLibrary`  
_L133-158_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_MeshVoxelProcessing"))`
- inherits: `UBlueprintFunctionLibrary`
- L142 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshSolidify( UDynamicMesh* TargetMesh, FGeometryScriptSolidifyOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Voxel", meta = (ScriptMethod, HidePin = "Debug", Keywords = "Vox Wrap", DisplayName = "Apply Mesh Solidify (Voxel Wrap)"))` — Replaces the mesh with a voxelized-and-meshed approximation (VoxWrap operation).
- L152 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyMeshMorphology( UDynamicMesh* TargetMesh, FGeometryScriptMorphologyOptions Options, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Voxel", meta=(ScriptMethod, HidePin = "Debug", Keywords="Vox Offset Dilate Contract", DisplayName = "Apply Mesh Morphology (Voxel Offset)"))` — Replaces the mesh with an SDF-based offset mesh approximation (VoxOffset operation).

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/MeshWeightMapFunctions.h` (Public)


#### class `UGeometryScriptLibrary_MeshWeightMapFunctions`  
`class UGeometryScriptLibrary_MeshWeightMapFunctions : public UBlueprintFunctionLibrary`  
_L15-85_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_WeightMaps"))`
- inherits: `UBlueprintFunctionLibrary`
- L24 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* FindOrAddMeshWeightMap( UDynamicMesh* TargetMesh, FName Name, FGeometryScriptWeightMapHandle& WeightMapHandle, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod, HidePin = "Debug"))` — Find or add a weight layer with the requested name.
- L32 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* RemoveMeshWeightMap(UDynamicMesh* TargetMesh, FGeometryScriptWeightMapHandle WeightMapHandle, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod, HidePin = "Debug"))` — Remove the requested weight layer, if present.
- L43 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetMeshWeightMapValues(UDynamicMesh* TargetMesh, FGeometryScriptScalarList& WeightValues, FGeometryScriptWeightMapHandle WeightMapHandle, bool bSkipGaps, bool& bHasVertexIDGaps, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod, HidePin = "Debug"))` — Get the values of a given mesh weight map as a scalar list @param WeightValues The weights of each vertex in the Target Mesh @param bSkipGaps Whether to skip invalid vertex IDs in a non-compact mesh. @param bHasVertexIDGaps Whether any values in the list correspond to 'skipped' vertices. Will only be true if SkipGaps is false, and the Target Mesh is non-compact.
- L54 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshWeightMapValues(UDynamicMesh* TargetMesh, FGeometryScriptScalarList WeightValues, FGeometryScriptWeightMapHandle WeightMapHandle, bool bSkipGaps, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod, HidePin = "Debug"))` — Set the values of a given mesh weight map from a scalar list. @param WeightValues The weights to set on each vertex in the Target Mesh. Length must be the same as Target Mesh's Max Vertex ID, or the Vertex Count if Skip Gaps is true. @param bSkipGaps Whether to skip invalid vertex IDs in a non-compact mesh
- L63 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshConstantWeightMapValue( UDynamicMesh* TargetMesh, FGeometryScriptWeightMapHandle WeightMapHandle, float Weight, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|VertexColor", meta=(ScriptMethod, HidePin = "Debug"))` — Set all weights in the given layer to a constant value @param Weight The constant value to set
- L76 _public prototype_ `static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetMeshSelectionWeightMapValue( UDynamicMesh* TargetMesh, FGeometryScriptWeightMapHandle WeightMapHandle, FGeometryScriptMeshSelection Selection, float Weight, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|VertexColor", meta=(ScriptMethod, HidePin = "Debug"))` — Set the weights on selected vertices to a constant value. @param Weight The constant weight to set

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/PointSetFunctions.h` (Public)


#### enum `EGeometryScriptInitKMeansMethod`  
`enum class EGeometryScriptInitKMeansMethod : uint8`  
_L14-18_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Random`
- L17 _public enumerator_ `UniformSpacing`

#### struct `FGeometryScriptPointClusteringOptions`  
`struct FGeometryScriptPointClusteringOptions`  
_L21-45_
- reflection: `USTRUCT(BlueprintType)`
- L28 _public member_ `TArray<FVector> InitialClusterCenters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If not empty, will be used instead of Target Num Clusters. Specifies the initial cluster centers to use.
- L32 _public member_ `int TargetNumClusters = 3;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Number of clusters requested, if Initial Cluster Centers is empty. Actual clusters generated may be smaller, e.g. if there are fewer points
- L36 _public member_ `EGeometryScriptInitKMeansMethod InitializeMethod = EGeometryScriptInitKMeansMethod::UniformSpacing;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Method to initialize the cluster centers, if Initial Cluster Centers is empty
- L40 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (EditCondition="InitializeMethod == EGeometryScriptInitKMeansMethod::Random"))` — Random Seed used to initialize clustering, if the Random cluster initialization is chosen
- L44 _public member_ `int32 MaxIterations = 500;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (ClampMin = "1"))` — Maximum iterations to run the clustering process. Will stop earlier if/when clustering converges.

#### struct `FGeometryScriptPointPriorityOptions`  
`struct FGeometryScriptPointPriorityOptions`  
_L48-61_
- reflection: `USTRUCT(BlueprintType)`
- L55 _public member_ `TArray<float> OptionalPriorityWeights;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If not empty, will be used to order the points so that higher-priority points are kept.
- L59 _public member_ `bool bUniformSpacing = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to ensure the kept points are approximately uniformly spaced

#### struct `FGeometryScriptPointFlatteningOptions`  
`struct FGeometryScriptPointFlatteningOptions`  
_L65-77_
- reflection: `USTRUCT(BlueprintType)`
- L72 _public member_ `FTransform Frame = FTransform::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Relative transform to use as a frame of reference. When flattening, the inverse transform will be applied to bring the points into the local space of the frame.
- L76 _public member_ `EGeometryScriptAxis DropAxis = EGeometryScriptAxis::Z;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Which axis to drop when flattening

#### class `UGeometryScriptLibrary_PointSetSamplingFunctions`  
`class UGeometryScriptLibrary_PointSetSamplingFunctions : public UBlueprintFunctionLibrary`  
_L82-182_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_PointSetSampling"))`
- inherits: `UBlueprintFunctionLibrary`
- L92 _public prototype_ `static void KMeansClusterToIDs( const TArray<FVector>& Points, const FGeometryScriptPointClusteringOptions& Options, TArray<int32>& PointClusterIndices);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PointSet", meta = (AutoCreateRefTerm = "Options"))` — Use K-Means clustering to cluster the given points into a target number of clusters, and return an array with a cluster index per point.
- L102 _public prototype_ `static void KMeansClusterToArrays( const TArray<FVector>& Points, const FGeometryScriptPointClusteringOptions& Options, TArray<FGeometryScriptIndexList>& ClusterIDToLists);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PointSet", meta = (AutoCreateRefTerm = "Options"))` — Use K-Means clustering to cluster the given points into a target number of clusters, and return the clusters as an array of lists of point indices.
- L116 _public prototype_ `static void DownsamplePoints( const TArray<FVector>& Points, const FGeometryScriptPointPriorityOptions& Options, FGeometryScriptIndexList& DownsampledIndices, int32 KeepNumPoints = 100, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PointSet", meta = (HidePin = "Debug", AutoCreateRefTerm = "Options"))` — Find a subset of the given Points of a specified size. Can optionally specify a priorty weighting and/or request uniform spacing for the downsampled points. Note: Ordering of the result will balance: (1) if weights are provided, higher weight points come earlier and (2) if uniform spacing is requested, points will be ordered to have an octree-style coverage -- so the first 8 points will cover the 8 octants (where samples are available) and the subsequent points will progressively fill in the space
- L127 _public prototype_ `static void TransformsToPoints( const TArray<FTransform>& Transforms, TArray<FVector>& Points );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PointSet")` — Create an array of the positions of the input Transforms
- L137 _public prototype_ `static void OffsetTransforms( UPARAM(ref) TArray<FTransform>& Transforms, double Offset, FVector Direction = FVector::UpVector, EGeometryScriptCoordinateSpace Space = EGeometryScriptCoordinateSpace::Local );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PointSet")` — Offset the location of all Transforms by Offset in the given Direction, either locally in the space of the transform or in world space. For example, this can offset mesh surface samples along the surface normal direction.
- L149 _public prototype_ `static void FlattenPoints( const TArray<FVector>& PointsIn3D, TArray<FVector2D>& PointsIn2D, const FGeometryScriptPointFlatteningOptions& Options );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PointSet", meta = (AutoCreateRefTerm = "Options"))` — Convert an array of points from 3D to 2D, by transforming into the given ReferenceFrame and taking the X,Y coordinates Note that to transform into the ReferenceFrame, we apply the inverse of the ReferenceFrame's transform.
- L159 _public prototype_ `static void UnflattenPoints( const TArray<FVector2D>& PointsIn2D, TArray<FVector>& PointsIn3D, const FGeometryScriptPointFlatteningOptions& Options, double Height = 0.0 );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PointSet", meta = (AutoCreateRefTerm = "Options"))` — Convert an array of points from 2D to 3D, by transforming out of the given ReferenceFrame, with the given Height for the non-flat axis (default Z).
- L170 _public prototype_ `static UPARAM(DisplayName = "Bounding Box") FBox MakeBoundingBoxFromPoints(const TArray<FVector>& Points, double Expa` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PointSet")` — Make a Axis Aligned Bounding Box that bounds the given Points, optionally expanded by some additional amount on each side
- L176 _public prototype_ `static void GetPointsFromIndexList( const TArray<FVector>& AllPoints, const FGeometryScriptIndexList& Indices, TArray<FVector>& SelectedPoints );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PointSet")` — Create an array of the subset of AllPoints indicated by the Indices list

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/PolyPathFunctions.h` (Public)


#### enum `EGeometryScriptSampleSpacing`  
`enum class EGeometryScriptSampleSpacing : uint8`  
_L15-20_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `UniformDistance`
- L18 _public enumerator_ `UniformTime`
- L19 _public enumerator_ `ErrorTolerance`

#### enum `EGeometryScriptEvaluateSplineRange`  
`enum class EGeometryScriptEvaluateSplineRange : uint8`  
_L23-33_
- reflection: `UENUM(BlueprintType)`
- L26 _public enumerator_ `FullSpline` — Evaluate the full spline, ignoring any specified range
- L28 _public enumerator_ `DistanceRange` — Evaluate a range specified by distances along the spline
- L30 _public enumerator_ `TimeRange_ConstantSpeed` — Evaluate a range specified by times, based on travelling at constant speed along the spline
- L32 _public enumerator_ `TimeRange_VariableSpeed` — Evaluate a range specified by times, based on travelling at a constant rate of spline segments/second

#### struct `FGeometryScriptSplineSamplingOptions`  
`struct FGeometryScriptSplineSamplingOptions`  
_L36-64_
- reflection: `USTRUCT(BlueprintType)`
- L41 _public member_ `int32 NumSamples = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (EditCondition = "SampleSpacing != EGeometryScriptSampleSpacing::ErrorTolerance"))`
- L44 _public member_ `float ErrorTolerance = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (EditCondition = "SampleSpacing == EGeometryScriptSampleSpacing::ErrorTolerance"))`
- L47 _public member_ `EGeometryScriptSampleSpacing SampleSpacing = EGeometryScriptSampleSpacing::UniformDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L50 _public member_ `TEnumAsByte<ESplineCoordinateSpace::Type> CoordinateSpace = ESplineCoordinateSpace::Type::Local;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L54 _public member_ `EGeometryScriptEvaluateSplineRange RangeMethod = EGeometryScriptEvaluateSplineRange::FullSpline;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — How the RangeStart and RangeEnd parameters will be interpreted
- L58 _public member_ `float RangeStart = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (EditCondition = "EvaluateRange != EGeometryScriptEvaluateSplineRange::FullSpline"))` — If not evaluating the full spline, where to start sampling. Expressed in units based on the EvaluateRange value.
- L62 _public member_ `float RangeEnd = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (EditCondition = "EvaluateRange != EGeometryScriptEvaluateSplineRange::FullSpline"))` — If not evaluating the full spline, where to stop sampling. Expressed in units based on the EvaluateRange value.

#### class `UGeometryScriptLibrary_PolyPathFunctions`  
`class UGeometryScriptLibrary_PolyPathFunctions : public UBlueprintFunctionLibrary`  
_L68-216_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_PolyPath"))`
- inherits: `UBlueprintFunctionLibrary`
- L77 _public prototype_ `static int GetPolyPathNumVertices(FGeometryScriptPolyPath PolyPath);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|PolyPath", meta=(ScriptMethod))` — Returns the number of vertices in the the PolyPath.
- L83 _public prototype_ `static int GetPolyPathLastIndex(FGeometryScriptPolyPath PolyPath);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|PolyPath", meta=(ScriptMethod))` — Returns the index of the last vertex in the PolyPath.
- L92 _public prototype_ `static FVector GetPolyPathVertex(FGeometryScriptPolyPath PolyPath, int Index, bool& bIsValidIndex);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|PolyPath", meta=(ScriptMethod))` — Returns the 3D position of the requested vertex in the PolyPath. If the Index does not correspond to a vertex in the PolyPath, a Zero Vector (0,0,0) will be returned. @param Index specifies a vertex in the PolyPath. @param bIsValidIndex will be false on return if the Index is not included in the PolyPath.
- L101 _public prototype_ `static FVector GetPolyPathTangent(FGeometryScriptPolyPath PolyPath, int Index, bool& bIsValidIndex);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|PolyPath", meta = (ScriptMethod))` — Returns the local tangent vector of the PolyPath at the specified vertex index. If the Index does not correspond to a vertex in the PolyPath, a Zero Vector (0,0,0) will be returned. @param Index specifies a vertex in the PolyPath @param bIsValidIndex will be false on return if the Index is not included in the PolyPath
- L107 _public prototype_ `static double GetPolyPathArcLength(FGeometryScriptPolyPath PolyPath);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath", meta = (ScriptMethod))` — Returns the length of the PolyPath.
- L111 _public prototype_ `static int32 GetNearestVertexIndex(FGeometryScriptPolyPath PolyPath, FVector Point);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath", meta = (ScriptMethod))` — Find the index of the vertex closest to a given point.  Returns -1 if the PolyPath has no vertices.
- L115 _public prototype_ `static UPARAM(DisplayName = "Poly Path") FGeometryScriptPolyPath FlattenTo2DOnAxis(FGeometryScriptPolyPath PolyPath, EGeometryScriptAxis DropAxis = EGeometryScript` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath", meta = (ScriptMethod, DisplayName = "Flatten To 2D On Axis"))` — Create a 2D, flattened copy of the path by dropping the given axis, and using the other two coordinates as the new X, Y coordinates.
- L122 _public prototype_ `static UPARAM(DisplayName = "Poly Path") FGeometryScriptPolyPath CreateCirclePath3D(FTransform Transform, float Radius = 10, int NumPoin` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath")` — Create a closed circle around the origin on the XY plane, then transformed by Transform. By our convention for closed paths, the end vertex is *not* a duplicate of the start vertex.
- L129 _public prototype_ `static UPARAM(DisplayName = "Poly Path") FGeometryScriptPolyPath CreateArcPath3D(FTransform Transform, float Radius = 10, int NumPoints = 10, float StartAngle = 0, float EndAng` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath")` — Create an open arc around the origin on the XY plane, then transformed by Transform. As it is an open path, the end vertex exactly hits the target EndAngle (so will be positioned on the start vertex if the end aligns to the start)
- L136 _public prototype_ `static UPARAM(DisplayName = "Poly Path") FGeometryScriptPolyPath CreateCirclePath2D(FVector2D Center = FVector2D(0, 0), float Radius = 10, int NumPoin` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath")` — Create a closed circle on the XY plane around the given Center. By our convention for closed paths, the end vertex is *not* a duplicate of the start vertex.
- L143 _public prototype_ `static UPARAM(DisplayName = "Poly Path") FGeometryScriptPolyPath CreateArcPath2D(FVector2D Center = FVector2D(0, 0), float Radius = 10, int NumPoints = 10, float StartAngle = 0, float EndAng` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath")` — Create an open arc on the XY plane around the given Center. As it is an open path, the end vertex exactly hits the target EndAngle (so will be positioned on the start vertex if the end aligns to the start)
- L149 _public prototype_ `static void ConvertSplineToPolyPath(const USplineComponent* Spline, FGeometryScriptPolyPath& PolyPath, FGeometryScriptSplineSamplingOptions SamplingOptions);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath")` — Sample positions from a USplineComponent into a PolyPath, based on the given SamplingOptions
- L160 _public prototype_ `static UPARAM(DisplayName = "Times Use Constant Velocity") bool SampleSplineToTransforms( const USplineComponent* Spline, TArray<FTransform>& Frames, TArray<double>& FrameTimes, FGeometryScriptSplineSamplingOptions SamplingOptions, FTransform RelativeTransform, bool bIncludeScale = true);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath")` — Sample a USplineComponent into a list of FTransforms, based on the given SamplingOptions. @param Frames Transforms are returned here, with X axis oriented along spline Tangent and Z as the 'Up' vector. @param FrameTimes the spline Time value used for each Frame. Note the Times Use Constant Velocity output indicates whether these times are w.r.t. to a constant-speed parameterization of the spline. @param RelativeTransform a constant Transform applied to each sample Transform in its local frame of reference. So, eg, an X Rotation will rotate each frame around the local spline Tangent vector @param bIncludeScale if true, the Scale of each FTransform is taken from the Spline, otherwise the Transforms have unit scale @return whether the FrameTimes are w.r.t. a 'constant speed' traversal of the spline
- L173 _public prototype_ `static void ConvertPolyPathToArray(FGeometryScriptPolyPath PolyPath, TArray<FVector>& VertexArray);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath", meta=(ScriptMethod))` — Populates an array of 3D vectors with the PolyPath vertex locations.
- L179 _public prototype_ `static void ConvertArrayToPolyPath(const TArray<FVector>& VertexArray, FGeometryScriptPolyPath& PolyPath);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath")` — Creates a PolyPath from an array of 3D position vectors.
- L185 _public prototype_ `static void ConvertPolyPathToArrayOfVector2D(FGeometryScriptPolyPath PolyPath, TArray<FVector2D>& VertexArray);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath", meta = (ScriptMethod))` — Creates an array of 2D Vectors with the PolyPath vertex locations projected onto the XY plane.
- L191 _public prototype_ `static void ConvertArrayOfVector2DToPolyPath(const TArray<FVector2D>& VertexArray, FGeometryScriptPolyPath& PolyPath);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyPath")` — Creates a PolyPath from an array of 2D position vectors. The Z-coordinate of the corresponding PolyPath vertices will be zero.
- L197 _public prototype_ `static TArray<FVector> Conv_GeometryScriptPolyPathToArray(FGeometryScriptPolyPath PolyPath);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "PolyPath To Array Of Vector", CompactNodeTitle = "->", BlueprintAutocast), Category = "GeometryScript|PolyPath")` — Returns an array of 3D vectors with the PolyPath vertex locations.
- L203 _public prototype_ `static TArray<FVector2D> Conv_GeometryScriptPolyPathToArrayOfVector2D(FGeometryScriptPolyPath PolyPath);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "PolyPath To Array Of Vector2D", CompactNodeTitle = "->", BlueprintAutocast), Category = "GeometryScript|PolyPath")` — Returns an array of 2D Vectors with the PolyPath vertex locations projected onto the XY plane.
- L209 _public prototype_ `static FGeometryScriptPolyPath Conv_ArrayToGeometryScriptPolyPath(const TArray<FVector>& PathVertices);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Array Of Vector To PolyPath", CompactNodeTitle = "->", BlueprintAutocast), Category = "GeometryScript|PolyPath")` — Returns a PolyPath created from an array of 3D position vectors.
- L215 _public prototype_ `static FGeometryScriptPolyPath Conv_ArrayOfVector2DToGeometryScriptPolyPath(const TArray<FVector2D>& PathVertices);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Array Of Vector2D To PolyPath", CompactNodeTitle = "->", BlueprintAutocast), Category = "GeometryScript|PolyPath")` — Returns a PolyPath created from an array of 2D position vectors. The Z-coordinate of the corresponding PolyPath vertices will be zero.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/PolygonFunctions.h` (Public)


#### enum `EGeometryScriptPolyOffsetJoinType`  
`enum class EGeometryScriptPolyOffsetJoinType : uint8`  
_L16-24_
- reflection: `UENUM(BlueprintType)`
- desc: Join types to define the shape of corners between polygon and polypath edges
- L19 _public enumerator_ `Square` — Uniform squaring on all convex edge joins.
- L21 _public enumerator_ `Round` — Arcs on all convex edge joins.
- L23 _public enumerator_ `Miter` — Squaring of convex edge joins with acute angles ("spikes"). Use in combination with MiterLimit.

#### enum `EGeometryScriptPathOffsetEndType`  
`enum class EGeometryScriptPathOffsetEndType : uint8`  
_L28-36_
- reflection: `UENUM(BlueprintType)`
- L31 _public enumerator_ `Butt` — Offsets both sides of a path, with square blunt ends
- L33 _public enumerator_ `Square` — Offsets both sides of a path, with square extended ends
- L35 _public enumerator_ `Round` — Offsets both sides of a path, with round extended ends

#### struct `FGeometryScriptPolygonOffsetOptions`  
`struct FGeometryScriptPolygonOffsetOptions`  
_L39-63_
- reflection: `USTRUCT(BlueprintType)`
- L46 _public member_ `EGeometryScriptPolyOffsetJoinType JoinType = EGeometryScriptPolyOffsetJoinType::Square;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — How to join / extend corners between two edges
- L50 _public member_ `double MiterLimit = 2.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — if JoinType is Miter, limits how far the miter can extend
- L54 _public member_ `bool bOffsetBothSides = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to apply the offset to both sides of the polygon, i.e. adding an inner hole to any polygon. If false, the offset is only applied to one side.
- L58 _public member_ `double StepsPerRadianScale = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (ClampMin = "0"))` — Scales the default number of vertices (per radian) used for round joins.
- L62 _public member_ `double MaximumStepsPerRadian = 10.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (ClampMin = "-1"))` — Maximum vertices per radian for round joins. Only applied if > 0.

#### struct `FGeometryScriptOpenPathOffsetOptions`  
`struct FGeometryScriptOpenPathOffsetOptions`  
_L67-92_
- reflection: `USTRUCT(BlueprintType)`
- L74 _public member_ `EGeometryScriptPolyOffsetJoinType JoinType = EGeometryScriptPolyOffsetJoinType::Square;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — How to join / extend corners between two edges
- L78 _public member_ `double MiterLimit = 2.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — if JoinType is Miter, limits how far the miter can extend
- L82 _public member_ `EGeometryScriptPathOffsetEndType EndType = EGeometryScriptPathOffsetEndType::Square;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — How the ends of a path should be closed off
- L86 _public member_ `double StepsPerRadianScale = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (ClampMin = "0"))` — Scales the default number of vertices (per radian) used for round joins and ends.
- L90 _public member_ `double MaximumStepsPerRadian = 10.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options, meta = (ClampMin = "-1"))` — Maximum vertices per radian for round joins and ends. Only applied if > 0.

#### class `UGeometryScriptLibrary_SimplePolygonFunctions`  
`class UGeometryScriptLibrary_SimplePolygonFunctions : public UBlueprintFunctionLibrary`  
_L95-180_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_SimplePolygon"))`
- inherits: `UBlueprintFunctionLibrary`
- L104 _public prototype_ `static int32 GetPolygonVertexCount(FGeometryScriptSimplePolygon Polygon);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SimplePolygon", meta = (ScriptMethod))` — Returns the number of vertices in a Simple Polygon
- L111 _public prototype_ `static FVector2D GetPolygonVertex(FGeometryScriptSimplePolygon Polygon, int32 VertexIndex, bool& bPolygonIsEmpty);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SimplePolygon", meta = (ScriptMethod))` — Returns the specified vertex of a Simple Polygon. VertexIndex loops around, so e.g., -1 gives the last vertex in the polygon. If Polygon has no vertices, returns the zero vector.
- L118 _public prototype_ `static void SetPolygonVertex(UPARAM(ref) FGeometryScriptSimplePolygon Polygon, int32 VertexIndex, FVector2D Position, bool& bPolygonIsEmpty);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SimplePolygon", meta = (ScriptMethod))` — Set the specified vertex of a Simple Polygon. VertexIndex loops around, so e.g., -1 gives the last vertex in the polygon. Does nothing if Polygon has no vertices.
- L124 _public prototype_ `static UPARAM(DisplayName = "Vertex Index") int32 AddPolygonVertex(UPARAM(ref) FGeometryScriptSimplePolygon& Polygon, FVector2` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SimplePolygon", meta = (ScriptMethod))` — Set the specified vertex of a Simple Polygon. Returns the index of the added vertex.
- L131 _public prototype_ `static FVector2D GetPolygonTangent(FGeometryScriptSimplePolygon Polygon, int32 VertexIndex, bool& bPolygonIsEmpty);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SimplePolygon", meta = (ScriptMethod))` — Returns a vertex's tangent of a Simple Polygon. VertexIndex loops around, so e.g., -1 gives the tangent of the last vertex in the polygon. If Polygon has no vertices, returns the zero vector.
- L137 _public prototype_ `static double GetPolygonArcLength(FGeometryScriptSimplePolygon Polygon);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SimplePolygon", meta = (ScriptMethod))` — Returns the arc length of a Simple Polygon
- L143 _public prototype_ `static double GetPolygonArea(FGeometryScriptSimplePolygon Polygon);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SimplePolygon", meta = (ScriptMethod, DisplayName = "Get Simple Polygon Area"))` — Returns the area enclosed by a Simple Polygon
- L149 _public prototype_ `static FBox2D GetPolygonBounds(FGeometryScriptSimplePolygon Polygon);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SimplePolygon", meta = (ScriptMethod))` — Returns the bounding box of a Simple Polygon
- L155 _public prototype_ `static void ConvertSplineToPolygon(const USplineComponent* Spline, FGeometryScriptSimplePolygon& Polygon, FGeometryScriptSplineSamplingOptions SamplingOptions, EGeometryScriptAxis DropAxis = EGeometryScriptAxis::Z);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|SimplePolygon")` — Sample positions from a USplineComponent into a Simple Polyon, based on the given SamplingOptions
- L161 _public prototype_ `static TArray<FVector> Conv_GeometryScriptSimplePolygonToArray(FGeometryScriptSimplePolygon Polygon);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Simple Polygon To Array Of Vector", CompactNodeTitle = "->", BlueprintAutocast), Category = "GeometryScript|SimplePolygon")` — Returns an array of 3D vectors with the Polygon vertex locations, with Z coordinate set to zero.
- L167 _public prototype_ `static TArray<FVector2D> Conv_GeometryScriptSimplePolygonToArrayOfVector2D(FGeometryScriptSimplePolygon Polygon);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Simple Polygon To Array Of Vector2D", CompactNodeTitle = "->", BlueprintAutocast), Category = "GeometryScript|SimplePolygon")` — Returns an array of 2D Vectors with the Polygon vertex locations.
- L173 _public prototype_ `static FGeometryScriptSimplePolygon Conv_ArrayToGeometryScriptSimplePolygon(const TArray<FVector>& PathVertices);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Array Of Vector To Simple Polygon", CompactNodeTitle = "->", BlueprintAutocast), Category = "GeometryScript|SimplePolygon")` — Returns a Polygon created from an array of 3D position vectors, ignoring the Z coordinate.
- L179 _public prototype_ `static FGeometryScriptSimplePolygon Conv_ArrayOfVector2DToGeometryScriptSimplePolygon(const TArray<FVector2D>& PathVertices);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Array Of Vector2D To Simple Polygon", CompactNodeTitle = "->", BlueprintAutocast), Category = "GeometryScript|SimplePolygon")` — Returns a Polygon created from an array of 2D position vectors.

#### class `UGeometryScriptLibrary_PolygonListFunctions`  
`class UGeometryScriptLibrary_PolygonListFunctions : public UBlueprintFunctionLibrary`  
_L184-323_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_PolygonList"))`
- inherits: `UBlueprintFunctionLibrary`
- L193 _public prototype_ `static int32 GetPolygonCount(FGeometryScriptGeneralPolygonList PolygonList);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Returns the number of polygons in the Polygon List
- L199 _public prototype_ `static int32 GetPolygonHoleCount(FGeometryScriptGeneralPolygonList PolygonList, bool& bValidIndex, int32 PolygonIndex);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Returns the number of holes in a Polygon. Returns zero for an invalid PolygonIndex.
- L206 _public prototype_ `static int32 GetPolygonVertexCount(FGeometryScriptGeneralPolygonList PolygonList, bool& bValidIndices, int32 PolygonIndex, int32 HoleIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta=(ScriptMethod))` — Returns the number of vertices in a Polygon's outer shape, if HoleIndex is -1, or in the specified inner hole. Returns 0 for invalid Polygon or Hole indices.
- L213 _public prototype_ `static void GetPolygonVertices(FGeometryScriptGeneralPolygonList PolygonList, TArray<FVector2D>& OutVertices, bool& bValidIndices, int32 PolygonIndex, int32 HoleIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Returns the vertices of a Polygon -- either of the outer polygon, if HoleIndex is -1, or specified inner hole. OutVertices will be empty for invalid Polygon or Hole indices.
- L220 _public prototype_ `static FGeometryScriptSimplePolygon GetSimplePolygon(FGeometryScriptGeneralPolygonList PolygonList, bool& bValidIndices, int32 PolygonIndex, int32 HoleIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Returns a specified Simple Polygon from a Polygon List -- either the outer polygon, if HoleIndex is -1, or specified inner hole. Polygon will be empty for invalid Polygon or Hole indices.
- L227 _public prototype_ `static FVector2D GetPolygonVertex(FGeometryScriptGeneralPolygonList PolygonList, bool& bIsValidVertex, int32 VertexIndex, int32 PolygonIndex, int32 HoleIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Returns the specified vertex of a Polygon -- either of the outer polygon, if HoleIndex is -1, or specified inner hole. Vertex will be the zero vector for invalid Polygon or Hole indices, or if the polygon is empty. VertexIndex will loop.
- L233 _public prototype_ `static double GetPolygonArea(FGeometryScriptGeneralPolygonList PolygonList, bool& bValidIndex, int32 PolygonIndex);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod, DisplayName = "Get Area of Polygon in List"))` — Returns the area enclosed by a specified Polygon in a Polygon List. Returns zero for an invalid PolygonIndex.
- L239 _public prototype_ `static FBox2D GetPolygonBounds(FGeometryScriptGeneralPolygonList PolygonList, bool& bValidIndex, int32 PolygonIndex);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Returns the bounding box of a Polygon. Returns an empty, invalid box for an invalid PolygonIndex.
- L245 _public prototype_ `static double GetPolygonListArea(FGeometryScriptGeneralPolygonList PolygonList);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Returns the area enclosed by a Polygon List
- L251 _public prototype_ `static FBox2D GetPolygonListBounds(FGeometryScriptGeneralPolygonList PolygonList);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Returns the bounding box of a Polygon List
- L257 _public prototype_ `static UPARAM(DisplayName = "Polygon List") FGeometryScriptGeneralPolygonList CreatePolygonListFromSinglePolygon(FGeometryScriptSimplePolygon OuterPolygon, const TArray<FGeometryScriptSimplePolygon>& HolePolygons, bool bFixHoleOrientati` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod, AutoCreateRefTerm = "HolePolygons"))` — Create a Polygon List of a single Polygon, with optional holes
- L263 _public prototype_ `static UPARAM(DisplayName = "Polygon Index") int32 AddPolygonToList(UPARAM(ref) FGeometryScriptGeneralPolygonList& PolygonList, FGeometryScriptSimplePolygon OuterPolygon, const TArray<FGeometryScriptSimplePolygon>& HolePolygons, bool bFixHoleOrientat` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod, AutoCreateRefTerm = "HolePolygons"))` — Add Polygon to a Polygon List, with optional holes. Returns index of the added polygon.
- L269 _public prototype_ `static UPARAM(DisplayName = "Polygon List") FGeometryScriptGeneralPolygonList CreatePolygonListFromSimplePolygons(const TArray<FGeometryScriptSimplePolygon>& Out` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList")` — Create a Polygon List from an array of Simple Polygons
- L275 _public prototype_ `static void AppendPolygonList(UPARAM(ref) FGeometryScriptGeneralPolygonList& PolygonList, FGeometryScriptGeneralPolygonList PolygonsToAppend);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Append the polygons in 'Polygons to Append' to Polygon List
- L279 _public prototype_ `static FGeometryScriptGeneralPolygonList PolygonsUnion(FGeometryScriptGeneralPolygonList PolygonList, bool bCopyInputOnFailure = true);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Compute union of all polygons in Polygon List. Also resolves self-intersections within each polygon.
- L283 _public prototype_ `static FGeometryScriptGeneralPolygonList PolygonsDifference(FGeometryScriptGeneralPolygonList PolygonList, FGeometryScriptGeneralPolygonList PolygonsToSubtract);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Compute difference of Polygon List and Polygons to Subtract
- L287 _public prototype_ `static FGeometryScriptGeneralPolygonList PolygonsIntersection(FGeometryScriptGeneralPolygonList PolygonList, FGeometryScriptGeneralPolygonList PolygonsToIntersect);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Compute intersection of Polygon List and Polygons to Intersect
- L291 _public prototype_ `static FGeometryScriptGeneralPolygonList PolygonsExclusiveOr(FGeometryScriptGeneralPolygonList PolygonList, FGeometryScriptGeneralPolygonList PolygonsToExclusiveOr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Compute exclusive or of Polygon List and Polygons to Exclusive Or
- L295 _public prototype_ `static FGeometryScriptGeneralPolygonList PolygonsOffset(FGeometryScriptGeneralPolygonList PolygonList, FGeometryScriptPolygonOffsetOptions OffsetOptions, double Offset, bool& bOperationSuccess, bool bCopyInputOnFailure = true);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Apply a single offset to a list of closed polygons
- L300 _public prototype_ `static FGeometryScriptGeneralPolygonList PolygonsOffsets(FGeometryScriptGeneralPolygonList PolygonList, FGeometryScriptPolygonOffsetOptions OffsetOptions, double FirstOffset, double SecondOffset, bool& bOperationSuccess, bool bCopyInputOnFailure = true);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Apply two offsets in sequence to a list of closed polygons
- L305 _public prototype_ `static FGeometryScriptGeneralPolygonList PolygonsMorphologyOpen(FGeometryScriptGeneralPolygonList PolygonList, FGeometryScriptPolygonOffsetOptions OffsetOptions, double Offset, bool& bOperationSuccess, bool bCopyInputOnFailure = true);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Apply a morphological "open" operator to a list of closed polygons -- first offsetting by -Offset, then by +Offset. If Offset is negative, this will instead function as a 'Close' operation
- L310 _public prototype_ `static FGeometryScriptGeneralPolygonList PolygonsMorphologyClose(FGeometryScriptGeneralPolygonList PolygonList, FGeometryScriptPolygonOffsetOptions OffsetOptions, double Offset, bool& bOperationSuccess, bool bCopyInputOnFailure = true);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList", meta = (ScriptMethod))` — Apply a morphological "close" operator to a list of closed polygons -- first offsetting by +Offset, then by -Offset. If Offset is negative, this will instead function as an 'Open' operation
- L315 _public prototype_ `static FGeometryScriptGeneralPolygonList CreatePolygonsFromPathOffset(TArray<FVector2D> Path, FGeometryScriptOpenPathOffsetOptions OffsetOptions, double Offset, bool& bOperationSuccess, bool bCopyInputOnFailure = true);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList")` — Apply an offset to a single open 2D path, generating closed polygons as a result
- L320 _public prototype_ `static FGeometryScriptGeneralPolygonList CreatePolygonsFromOpenPolyPathsOffset(TArray<FGeometryScriptPolyPath> PolyPaths, FGeometryScriptOpenPathOffsetOptions OffsetOptions, double Offset, bool& bOperationSuccess, bool bCopyInputOnFailure = true);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolygonList")` — Apply an offset to a set of open 2D PolyPaths, generating closed polygons as a result

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/SceneUtilityFunctions.h` (Public)


#### struct `FGeometryScriptCopyMeshFromComponentOptions`  
`struct FGeometryScriptCopyMeshFromComponentOptions`  
_L18-34_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `bool bWantNormals = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L26 _public member_ `bool bWantTangents = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L30 _public member_ `bool bWantInstanceColors = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to request per-instance vertex colors (where applicable; applies to RenderData LODs of Static Mesh components)
- L33 _public member_ `FGeometryScriptMeshReadLOD RequestedLOD = FGeometryScriptMeshReadLOD();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FGeometryScriptDetermineMeshOcclusionOptions`  
`struct FGeometryScriptDetermineMeshOcclusionOptions`  
_L37-53_
- reflection: `USTRUCT(BlueprintType)`
- L44 _public member_ `double SamplingDensity = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Approximate spacing between samples on triangle faces used for determining visibility
- L48 _public member_ `bool bDoubleSided = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to treat faces as double-sided when determining visibility
- L52 _public member_ `int32 NumSearchDirections = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Number of directions to test for visibility

#### class `UGeometryScriptLibrary_SceneUtilityFunctions`  
`class UGeometryScriptLibrary_SceneUtilityFunctions : public UBlueprintFunctionLibrary`  
_L57-151_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_SceneUtils"))`
- inherits: `UBlueprintFunctionLibrary`
- L67 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh Pool") UDynamicMeshPool* CreateDynamicMeshPool();` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Utility")` — Create a new UDynamicMeshPool object. Caller needs to create a UProperty reference to the returned object, or it will be garbage-collected.
- L81 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* CopyMeshFromComponent( USceneComponent* Component, UDynamicMesh* ToDynamicMesh, FGeometryScriptCopyMeshFromComponentOptions Options, bool bTransformToWorld, FTransform& LocalToWorld, EGeometryScriptOutcomePins& Outcome, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Scene", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Copy the mesh from a given Component to a Dynamic Mesh. Supported Component types are: StaticMeshComponent, SkinnedMeshComponent, SplineMeshComponent, DynamicMeshComponent, GeometryCacheComponent, GeometryCollectionComponent, and BrushComponent This function offers minimal control over the copying. If more control is needed for Static Meshes, use CopyMeshFromStaticMesh. @param bTransformToWorld if true, output mesh is in World space @param LocalToWorld local-to-world transform is returned here (whether mesh is in local or world space)
- L98 _public prototype_ `SetComponentMaterialList( UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& MaterialList, UGeometryScriptDebug* Debug = nullptr);`
- L114 _public prototype_ `static UPARAM(DisplayName = "Dynamic Mesh") UDynamicMesh* CopyCollisionMeshesFromObject( UObject* FromObject, UDynamicMesh* ToDynamicMesh, bool bTransformToWorld, FTransform& LocalToWorld, EGeometryScriptOutcomePins& Outcome, bool bUseComplexCollision = false, int SphereResolution = 16, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Scene", meta = (HidePin = "Debug", ExpandEnumAsExecs = "Outcome"))` — Extract the Collision Geometry from FromObject and copy/approximate it with meshes stored in ToDynamicMesh. For Simple Collision, FromObject can be a StaticMesh Asset or any PrimitiveComponent For Complex Collision, FromObject can be a Static/Skeletal Mesh Asset/Component, Dynamic Mesh Component, or other Component w/ complex collision support @param bTransformToWorld if true, output mesh is in World space @param LocalToWorld local-to-world transform is returned here (whether mesh is in local or world space) @param bUseComplexCollision if true, complex collision is extracted, otherwise Simple collision shapes are meshed @param SphereResolution determines tessellation density of sphere and capsule shapes
- L140 _public prototype_ `static void DetermineMeshOcclusion( const TArray<UDynamicMesh*>& SourceMeshes, const TArray<FTransform>& SourceMeshTransforms, TArray<bool>& OutMeshIsHidden, const TArray<UDynamicMesh*>& TransparentMeshes, const TArray<FTransform>& TransparentMeshTransforms, TArray<bool>& OutTransparentMeshIsHidden, const TArray<UDynamicMesh*>& OccludeMeshes, const TArray<FTransform>& OccludeMeshTransforms, const FGeometryScriptDetermineMeshOcclusionOptions& OcclusionOptions, UGeometryScriptDebug* Debug = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|Scene", meta = (HidePin = "Debug", AutoCreateRefTerm = "SourceMeshes, SourceMeshTransforms, TransparentMeshes, TransparentMeshTransforms, OccludeMeshes, OccludeMeshTransforms, OcclusionOptions"))` — Determine which meshes are entirely hidden by other meshes in the set, when viewed from outside. @param SourceMeshes			Meshes to test for occlusion. Note: The same mesh may appear multiple times in this array, if it is instanced with different transforms. @param SourceMeshTransforms	A transform for each source mesh. Array must have the same length as SourceMeshes. @param OutMeshIsHidden		Array will be filled with a bool per source mesh, indicating whether that mesh is hidden (true) or visible (false) @param TransparentMeshes		Transparent source meshes, to test for occlusion but which do not occlude. @param TransparentMeshTransforms		Array of transforms for each transparent mesh @param OutTransparentMeshIsHidden	Array will be filled with a bool per transparent mesh, indicating whether that mesh is hidden (true) or visible (false) @param OccludeMeshes			Array of optional meshes which can occlude SourceMeshes, but for which we will not test occlusion. @param OccludeMeshTransforms	Array of transforms for each occlude mesh. Array must have the same length as OccludeMeshes. @param Options				Settings to control how occlusion is tested

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/ShapeFunctions.h` (Public)


#### class `UGeometryScriptLibrary_TransformFunctions`  
`class UGeometryScriptLibrary_TransformFunctions : public UBlueprintFunctionLibrary`  
_L16-61_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_Transform"))`
- inherits: `UBlueprintFunctionLibrary`
- L25 _public prototype_ `static UPARAM(DisplayName="Transform") FTransform MakeTransformFromZAxis(FVector Location, FVector ZAxis);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Transform")` — Create a Transform at the given Location, with the ZAxis vector as the Z axis of the Transform.
- L34 _public prototype_ `static UPARAM(DisplayName="Transform") FTransform MakeTransformFromAxes(FVector Location, FVector ZAxis, FVector TangentAxis, bool bTangentIsX = true);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Transform")` — Create a Transform at the given Location, with the ZAxis vector as the Z axis of the Transform, and the X or Y axis oriented to the Tangent vector, based on the bTangentIsX parameter.
- L42 _public prototype_ `static UPARAM(DisplayName="Direction") FVector GetTransformAxisVector(FTransform Transform, EGeometryScriptAxis Axis = EGeometryScriptAxis::X);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Transform")` — Get the Vector for the direction of the X/Y/Z axis of the Transform, ie the Vector resulting from transforming the unit direction vectors (1,0,0) / etc
- L50 _public prototype_ `static UPARAM(DisplayName="Ray") FRay GetTransformAxisRay(FTransform Transform, EGeometryScriptAxis Axis = EGeometryScriptAxis::X);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Transform")` — Get the Ray at the Transform Location aligned with the direction of the X/Y/Z axis of the Transform, ie the Direction Vector resulting from transforming the unit direction vectors (1,0,0) / etc
- L58 _public prototype_ `static UPARAM(DisplayName="Ray") FPlane GetTransformAxisPlane(FTransform Transform, EGeometryScriptAxis Axis = EGeometryScriptAxis::X);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Transform")` — Get the Plane at the Transform Location with the Plane Normal aligned with the direction of the X/Y/Z axis of the Transform, ie the Direction Vector resulting from transforming the unit direction vectors (1,0,0) / etc

#### class `UGeometryScriptLibrary_RayFunctions`  
`class UGeometryScriptLibrary_RayFunctions : public UBlueprintFunctionLibrary`  
_L65-185_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_Ray"))`
- inherits: `UBlueprintFunctionLibrary`
- L74 _public prototype_ `static UPARAM(DisplayName="Ray") FRay MakeRayFromPoints(FVector A, FVector B);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray")` — Create a Ray from two points, placing the Origin at A and the Direction as Normalize(B-A)
- L81 _public prototype_ `static UPARAM(DisplayName="Ray") FRay MakeRayFromPointDirection(FVector Origin, FVector Direction, bool bDirectionIsNormalized = true);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray")` — Create a Ray from an Origin and Direction, with optionally non-normalized Direction
- L88 _public prototype_ `static UPARAM(DisplayName="Transformed Ray") FRay GetTransformedRay(FRay Ray, FTransform Transform, bool bInvert = false);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray", meta=(ScriptMethod))` — Apply the given Transform to the given Ray, or optionally the Transform Inverse, and return the new transformed Ray
- L95 _public prototype_ `static UPARAM(DisplayName="Point") FVector GetRayPoint(FRay Ray, double Distance);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray", meta=(ScriptMethod))` — Get a Point at the given Distance along the Ray (Origin + Distance*Direction)
- L105 _public prototype_ `GetRayStartEnd(FRay Ray, double StartDistance, double EndDistance, FVector& StartPoint, FVector& EndPoint);`
- L111 _public prototype_ `static UPARAM(DisplayName="Ray Paramater") double GetRayParameter(FRay Ray, FVector Point);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray", meta=(ScriptMethod))` — Project the given Point onto the closest point along the Ray, and return the Ray Parameter/Distance at that Point
- L118 _public prototype_ `static UPARAM(DisplayName="Distance") double GetRayPointDistance(FRay Ray, FVector Point);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray", meta=(ScriptMethod))` — Get the distance from Point to the closest point on the Ray
- L125 _public prototype_ `static UPARAM(DisplayName="Closest Point") FVector GetRayClosestPoint(FRay Ray, FVector Point);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray", meta=(ScriptMethod))` — Get the closest point on the Ray to the given Point
- L139 _public prototype_ `static UPARAM(DisplayName="Intersects") bool GetRaySphereIntersection(FRay Ray, FVector SphereCenter, double SphereRadius, double& Distance1, double& Distance2);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray", meta=(ScriptMethod))` — Check if the Ray intersects a Sphere defined by the SphereCenter and SphereRadius. This function returns two intersection distances (ray parameters). If the ray grazes the sphere, both distances will be the same, and if it misses, they will be MAX_FLOAT. Use the function GetRayPoint to convert the distances to points on the ray/sphere. @param Distance1 Distance along ray (Ray Parameter) to first/closer intersection point with sphere @param Distance2 Distance along ray (Ray Parameter) to second/further intersection point with sphere @return true if ray intersects sphere
- L148 _public prototype_ `static UPARAM(DisplayName="Intersects") bool GetRayBoxIntersection(FRay Ray, FBox Box, double& HitDistance);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray", meta=(ScriptMethod))` — Find the intersection of a Ray and a Box @param HitDistance Distance along the ray (Ray Parameter) to first intersection point with the Box @return true if the ray hits the box, and false otherwise
- L157 _public prototype_ `static UPARAM(DisplayName="Intersects") bool GetRayPlaneIntersection(FRay Ray, FPlane Plane, double& HitDistance);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray", meta=(ScriptMethod))` — Find the intersection of a Ray and a Plane @param HitDistance the returned Distance along the ray (Ray Parameter) to intersection point with the Plane @return true if the ray hits the plane (only false if ray is parallel with plane)
- L170 _public prototype_ `static UPARAM(DisplayName="Distance") double GetRayLineClosestPoint(FRay Ray, FVector LineOrigin, FVector LineDirection, double& RayParameter, FVector& RayPoint, double& LineParameter, FVector& LinePoint);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray", meta=(ScriptMethod))` — Compute the pair of closest points on a 3D Ray and Line. The Line is defined by an Origin and Direction (ie same as a Ray) but extends infinitely in both directions. @param RayParameter the Ray Parameter of the closest point on the Ray (range 0, inf) @param RayPoint the point on the Ray corresponding to RayParameter @param LineParameter the Line parameter of the closest point on the Line (range -inf, inf) @param LinePoint the point on the Line corresponding to LineParameter @return the minimum distance between the Ray and Line, ie between RayPoint and LinePoint
- L182 _public prototype_ `static UPARAM(DisplayName="Distance") double GetRaySegmentClosestPoint(FRay Ray, FVector SegStartPoint, FVector SegEndPoint, double& RayParameter, FVector& RayPoint, FVector& SegPoint);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Ray", meta=(ScriptMethod))` — Compute the pair of closest points on a 3D Ray and Line Segment The Line Segment is defined by its two Endpoints. @param RayParameter the Ray Parameter of the closest point on the Ray (range 0, inf) @param RayPoint the point on the Ray corresponding to RayParameter @param SegPoint the point on the Segment @return the minimum distance between the Ray and Segment, ie between RayPoint and SegPoint

#### class `UGeometryScriptLibrary_BoxFunctions`  
`class UGeometryScriptLibrary_BoxFunctions : public UBlueprintFunctionLibrary`  
_L189-307_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_Box"))`
- inherits: `UBlueprintFunctionLibrary`
- L198 _public prototype_ `static UPARAM(DisplayName="Box") FBox MakeBoxFromCenterSize(FVector Center, FVector Dimensions);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box")` — Create a Box from a Center point and X/Y/Z Dimensions (*not* Extents, which are half-dimensions)
- L205 _public prototype_ `static UPARAM(DisplayName="Box") FBox MakeBoxFromCenterExtents(FVector Center, FVector Extents);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box")` — Create a Box from a Center point and X/Y/Z Extents (Extents are half-dimensions)
- L212 _public prototype_ `static void GetBoxCenterSize(FBox Box, FVector& Center, FVector& Dimensions);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Get the Center point and X/Y/Z Dimensions of a Box (full dimensions, not Extents)
- L221 _public prototype_ `static UPARAM(DisplayName="Corner Point") FVector GetBoxCorner(FBox Box, int CornerIndex);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Get the position of a corner of the Box. Corners are indexed from 0 to 7, using an ordering where 0 is the Min corner, 1/2/3 are +Z/+Y/+X from the Min corner, 7 is the Max corner, and 4/5/6 are -Z/-Y/-X from the Max corner.
- L230 _public prototype_ `static UPARAM(DisplayName="Center Point") FVector GetBoxFaceCenter(FBox Box, int FaceIndex, FVector& FaceNormal);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Get the position of the center of a face of the Box. Faces are indexed from 0 to 5, using an ordering where 0/1 are the MinZ/MaxZ faces, 2/3 are MinY/MaxY, and 4/5 are MinX/MaxX @param FaceNormal returned Normal vector of the identified face
- L237 _public prototype_ `static void GetBoxVolumeArea(FBox Box, double& Volume, double& SurfaceArea);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Get the Volume and Surface Area of a Box
- L244 _public prototype_ `static UPARAM(DisplayName="Expanded Box") FBox GetExpandedBox(FBox Box, FVector ExpandBy);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Get the input Box expanded by adding the ExpandBy parameter to both the Min and Max. Dimensions will be clamped to the center point if any of ExpandBy are larger than half the box size
- L251 _public prototype_ `static UPARAM(DisplayName="Transformed Box") FBox GetTransformedBox(FBox Box, FTransform Transform);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Apply the input Transform to the corners of the input Box, and return the new Box containing those points
- L258 _public prototype_ `static UPARAM(DisplayName="Intersects") bool TestBoxBoxIntersection(FBox Box1, FBox Box2);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Test if Box1 and Box2 intersect
- L266 _public prototype_ `static UPARAM(DisplayName="Intersection Box") FBox FindBoxBoxIntersection(FBox Box1, FBox Box2, bool& bIsIntersecting);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Find the Box formed by the intersection of Box1 and Box2 @param bIsIntersecting if the boxes do not intersect, this will be returned as false, otherwise true
- L273 _public prototype_ `static UPARAM(DisplayName="Distance") double GetBoxBoxDistance(FBox Box1, FBox Box2);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Calculate the minimum distance between Box1 and Box2
- L281 _public prototype_ `static UPARAM(DisplayName="Is Inside") bool TestPointInsideBox(FBox Box, FVector Point, bool bConsiderOnBoxAsInside = true);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Test if a Point is inside the Box, returning true if so, otherwise false @param bConsiderOnBoxAsInside if true, a point lying on the box face is considered "inside", otherwise it is considered "outside"
- L290 _public prototype_ `static UPARAM(DisplayName="Closest Point") FVector FindClosestPointOnBox(FBox Box, FVector Point, bool& bIsInside);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Find the point on the faces of the Box that is closest to the input Point. If the Point is inside the Box, it is returned, ie points Inside do not project to the Box Faces @param bIsInside if the Point is inside the Box, this will return as true, otherwise false
- L297 _public prototype_ `static UPARAM(DisplayName="Distance") double GetBoxPointDistance(FBox Box, FVector Point);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Calculate the minimum distance between the Box and the Point
- L304 _public prototype_ `static UPARAM(DisplayName="Intersects") bool TestBoxSphereIntersection(FBox Box, FVector SphereCenter, double SphereRadius);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|Box", meta=(ScriptMethod))` — Check if the Box intersects a Sphere defined by the SphereCenter and SphereRadius

#### class `UGeometryScriptLibrary_OrientedBoxFunctions`  
`class UGeometryScriptLibrary_OrientedBoxFunctions : public UBlueprintFunctionLibrary`  
_L311-404_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_OrientedBox"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Oriented Box methods
- L320 _public prototype_ `static UPARAM(DisplayName="OrientedBox") FOrientedBox MakeOrientedBoxFromBox(FBox Box, FTransform Transform);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta = (KeyWords = "Transform"))` — Create an Oriented Box from a Box and a Transform
- L327 _public prototype_ `static UPARAM(DisplayName = "Orientation") FRotator GetOrientedBoxOrientation(FOrient` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta=(ScriptMethod, KeyWords = "Rotation"))` — Get the orientation of an Oriented Box
- L335 _public prototype_ `static UPARAM(DisplayName="Corner Point") FVector GetOrientedBoxCorner(FOrientedBox Box, int CornerIndex);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta=(ScriptMethod))` — Get the position of a corner of the Oriented Box. Corners are indexed from 0 to 7: Corner 0 is in the negative direction along each axis, 1/2/3 are along +Z/+Y/+X from the corner 0, 7 is the all-positive direction corner, and 4/5/6 are along -Z/-Y/-X from the corner 7.
- L344 _public prototype_ `static UPARAM(DisplayName="Center Point") FVector GetOrientedBoxFaceCenter(FOrientedBox Box, int FaceIndex, FVector& FaceNormal);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta=(ScriptMethod))` — Get the position of the center of a face of the Oriented Box. Faces are indexed from 0 to 5, using an ordering where 0/1 are the negative then positive Z-axis faces, 2/3 are Y-axis faces, and 4/5 are X-axis faces @param FaceNormal returned Normal vector of the identified face
- L351 _public prototype_ `static void GetOrientedBoxVolumeArea(FOrientedBox Box, double& Volume, double& SurfaceArea);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta=(ScriptMethod))` — Get the Volume and Surface Area of an Oriented Box
- L358 _public prototype_ `static UPARAM(DisplayName="Expanded Oriented Box") FOrientedBox GetExpandedOrientedBox(FOrientedBox OrientedBox, FVector ExpandBy, double MinExtent = 0);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta=(ScriptMethod, KeyWords = "Shrink"))` — Get the Oriented Box with extents expanded by the ExpandBy vector Can also shrink the box if negative ExpandBy values are provided, but will clamp to Max(0, MinExtent)
- L365 _public prototype_ `static UPARAM(DisplayName="Transformed Box") FOrientedBox GetTransformedOrientedBox(FOrientedBox OrientedBox, FTransform Transform);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta=(ScriptMethod))` — Apply the Transform to the Oriented Box
- L372 _public prototype_ `static UPARAM(DisplayName="Bounding Box") FBox ConvertOrientedBoxToAxisAlignedBox(FOrientedBox Box);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta=(ScriptMethod, KeyWords = "Bounding"))` — Find the bounding Box enclosing the input Oriented Box.
- L379 _public prototype_ `static UPARAM(DisplayName = "Is Inside") bool TestPointInsideOrOnOrientedBox(FOrientedBox Box, FVector Point);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta = (ScriptMethod))` — Test if a Point is inside or on the Box, returning true if so, otherwise false
- L388 _public prototype_ `static UPARAM(DisplayName = "Closest Point") FVector FindClosestPointOnOrientedBox(FOrientedBox Box, FVector Point, bool& bIsInsideOrOn);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta = (ScriptMethod, KeyWords = "Project"))` — Find the point on the faces of the Box that is closest to the input Point. If the Point is inside the Box, it is returned, ie points Inside do not project to the Box Faces @param bIsInsideOrOn if the Point is inside or on the Box, this will return as true, otherwise false
- L395 _public prototype_ `static UPARAM(DisplayName = "Intersects") bool TestOrientedBoxOrientedBoxIntersection(FOrientedBox Box1, FOrientedBox Box2);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta = (ScriptMethod, KeyWords = "Overlaps"))` — Test if two oriented boxes intersect
- L402 _public prototype_ `static UPARAM(DisplayName = "Intersects") bool TestBoxOrientedBoxIntersection(FBox Box, FOrientedBox OrientedBox);` — `UFUNCTION(BlueprintPure, Category = "GeometryScript|Shapes|OrientedBox", meta = (ScriptMethod, KeyWords = "Overlaps"))` — Test if an axis-aligned box intersects an oriented box

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/TextureMapFunctions.h` (Public)


#### enum `EGeometryScriptPixelSamplingMethod`  
`enum class EGeometryScriptPixelSamplingMethod : uint8`  
_L14-18_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Bilinear = 0`
- L17 _public enumerator_ `Nearest = 1`

#### struct `FGeometryScriptSampleTextureOptions`  
`struct FGeometryScriptSampleTextureOptions`  
_L24-39_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `EGeometryScriptPixelSamplingMethod SamplingMethod = EGeometryScriptPixelSamplingMethod::Bilinear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L32 _public member_ `bool bWrap = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L35 _public member_ `FVector2D UVScale = FVector2D(1,1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
- L38 _public member_ `FVector2D UVOffset = FVector2D(0,0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### class `UGeometryScriptLibrary_TextureMapFunctions`  
`class UGeometryScriptLibrary_TextureMapFunctions : public UBlueprintFunctionLibrary`  
_L45-76_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_TextureUtils"))`
- inherits: `UBlueprintFunctionLibrary`
- L55 _public prototype_ `SampleTexture2DAtUVPositions( FGeometryScriptUVList UVList, UTexture2D* Texture, FGeometryScriptSampleTextureOptions SampleOptions, FGeometryScriptColorList& ColorList, UGeometryScriptDebug* Debug = nullptr);`
- L68 _public prototype_ `SampleTextureRenderTarget2DAtUVPositions( FGeometryScriptUVList UVList, UTextureRenderTarget2D* Texture, FGeometryScriptSampleTextureOptions SampleOptions, FGeometryScriptColorList& ColorList, UGeometryScriptDebug* Debug = nullptr);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/VectorMathFunctions.h` (Public)


#### class `UGeometryScriptLibrary_VectorMathFunctions`  
`class UGeometryScriptLibrary_VectorMathFunctions : public UBlueprintFunctionLibrary`  
_L16-198_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_VectorMath"))`
- inherits: `UBlueprintFunctionLibrary`
- L27 _public prototype_ `VectorLength(FGeometryScriptVectorList VectorList);`
- L34 _public prototype_ `VectorDot(FGeometryScriptVectorList VectorListA, FGeometryScriptVectorList VectorListB);`
- L41 _public prototype_ `VectorCross(FGeometryScriptVectorList VectorListA, FGeometryScriptVectorList VectorListB);`
- L49 _public prototype_ `VectorNormalizeInPlace(UPARAM(ref) FGeometryScriptVectorList& VectorList, FVector SetOnFailure = FVector::ZeroVector);`
- L57 _public prototype_ `VectorTransformInPlace(UPARAM(ref) FGeometryScriptVectorList& VectorList, FTransform Transform, bool bAsPosition = true);`
- L65 _public prototype_ `VectorInverseTransformInPlace(UPARAM(ref) FGeometryScriptVectorList& VectorList, FTransform Transform, bool bAsPosition = true);`
- L72 _public prototype_ `VectorPlaneProjectInPlace(UPARAM(ref) FGeometryScriptVectorList& VectorList, FPlane Plane);`
- L81 _public prototype_ `VectorBlend(FGeometryScriptVectorList VectorListA, FGeometryScriptVectorList VectorListB, double ConstantA = 1.0, double ConstantB = 1.0);`
- L90 _public prototype_ `VectorBlendInPlace(FGeometryScriptVectorList VectorListA, UPARAM(ref) FGeometryScriptVectorList& VectorListB, double ConstantA = 1.0, double ConstantB = 1.0);`
- L97 _public prototype_ `ScalarVectorMultiply(FGeometryScriptScalarList ScalarList, FGeometryScriptVectorList VectorList, double ScalarMultiplier = 1.0);`
- L104 _public prototype_ `ScalarVectorMultiplyInPlace(FGeometryScriptScalarList ScalarList, UPARAM(ref) FGeometryScriptVectorList& VectorList, double ScalarMultiplier = 1.0);`
- L111 _public prototype_ `ConstantVectorMultiply(double Constant, FGeometryScriptVectorList VectorList);`
- L118 _public prototype_ `ConstantVectorMultiplyInPlace(double Constant, UPARAM(ref) FGeometryScriptVectorList& VectorList);`
- L127 _public prototype_ `VectorToScalar(FGeometryScriptVectorList VectorList, double ConstantX = 1.0, double ConstantY = 0.0, double ConstantZ = 0.0);`
- L137 _public prototype_ `ScalarInvert(FGeometryScriptScalarList ScalarList, double Numerator = 1.0, double SetOnFailure = 0.0, double Epsilon = 0.0);`
- L145 _public prototype_ `ScalarInvertInPlace(UPARAM(ref) FGeometryScriptScalarList& ScalarList, double Numerator = 1.0, double SetOnFailure = 0.0, double Epsilon = 0.0);`
- L154 _public prototype_ `ScalarBlend(FGeometryScriptScalarList ScalarListA, FGeometryScriptScalarList ScalarListB, double ConstantA = 1.0, double ConstantB = 1.0);`
- L163 _public prototype_ `ScalarBlendInPlace(FGeometryScriptScalarList ScalarListA, UPARAM(ref) FGeometryScriptScalarList& ScalarListB, double ConstantA = 1.0, double ConstantB = 1.0);`
- L172 _public prototype_ `ScalarMultiply(FGeometryScriptScalarList ScalarListA, FGeometryScriptScalarList ScalarListB, double ConstantMultiplier = 1.0);`
- L181 _public prototype_ `ScalarMultiplyInPlace(FGeometryScriptScalarList ScalarListA, UPARAM(ref) FGeometryScriptScalarList& ScalarListB, double ConstantMultiplier = 1.0);`
- L189 _public prototype_ `ConstantScalarMultiply(double Constant, FGeometryScriptScalarList ScalarList);`
- L196 _public prototype_ `ConstantScalarMultiplyInPlace(double Constant, UPARAM(ref) FGeometryScriptScalarList& ScalarList);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScript/VolumeTextureBakeFunctions.h` (Public)


#### enum `EDistanceFieldComputeMode`  
`enum class EDistanceFieldComputeMode : uint8`  
_L16-22_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `NarrowBand` — Compute distances in a narrow band around the input. Outside of this band, field will have large, correctly-signed values.
- L21 _public enumerator_ `FullGrid` — Compute distances in the full grid

#### enum `EDistanceFieldUnits`  
`enum class EDistanceFieldUnits : uint8`  
_L25-31_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `NumberOfVoxels` — Express distance as a number of voxels
- L30 _public enumerator_ `Distance` — Directly specify distances

#### struct `FComputeDistanceFieldSettings`  
`struct FComputeDistanceFieldSettings`  
_L35-61_
- reflection: `USTRUCT(BlueprintType)`
- desc: Settings for computing distance fields
- L44 _public member_ `EDistanceFieldComputeMode ComputeMode = EDistanceFieldComputeMode::NarrowBand;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to compute distances only in a band around the surface (faster) or compute the full grid Note: If full grid is computed, the distances will still be more accurately computed in the narrow band In narrow band mode, values outside the band will have a large magnitude with the correct sign
- L48 _public member_ `float NarrowBandWidth = 2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Width of the narrow band where distances are computed accurately
- L52 _public member_ `EDistanceFieldUnits NarrowBandUnits = EDistanceFieldUnits::NumberOfVoxels;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether Narrow Band Width is expressed as a number of voxels (rounded up to nearest int) or a distance
- L56 _public member_ `FIntVector VoxelsPerDimensions = FIntVector(32,32,32);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Number of voxels to use along each axis
- L60 _public member_ `bool bRequirePower2 = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Whether to round voxel count on each dimension up to the nearest power of two

#### struct `FDistanceFieldToTextureSettings`  
`struct FDistanceFieldToTextureSettings`  
_L64-76_
- reflection: `USTRUCT(BlueprintType)`
- L71 _public member_ `float Scale = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Scale values by this amount before writing them to the texture
- L75 _public member_ `float Offset = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Offset values by this amount before writing them to the texture (after applying Scale)

#### class `UGeometryScriptLibrary_VolumeTextureBakeFunctions`  
`class UGeometryScriptLibrary_VolumeTextureBakeFunctions : public UBlueprintFunctionLibrary`  
_L80-94_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryScript_VolumeBake"))`
- inherits: `UBlueprintFunctionLibrary`
- L87 _public prototype_ `static UPARAM(DisplayName = "Success") bool BakeSignedDistanceToVolumeTexture( const UDynamicMesh* TargetMesh, UVolumeTexture* VolumeTexture, FComputeDistanceFieldSettings DistanceSettings, FDistanceFieldToTextureSettings TextureSettings );` — `UFUNCTION(BlueprintCallable, Category = "GeometryScript|VolumeBake")` — Write a distance field to the given existing volume texture

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYSCRIPTINGCORE_API`

### `Plugins/Runtime/GeometryScripting/Source/GeometryScriptingCore/Public/GeometryScriptingCoreModule.h` (Public)


#### class `FGeometryScriptingCoreModule`  
`class FGeometryScriptingCoreModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
