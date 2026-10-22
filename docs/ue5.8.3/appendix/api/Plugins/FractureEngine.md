# Plugins / FractureEngine

- module root: `Plugins/Experimental/Fracture/Source/FractureEngine`
- headers: 10; symbols: 217
- symbol kinds: class=10, enum=12, enumerator=36, function=6, macro=6, member=43, namespace=10, prototype=91, struct=3
- PublicDependencyModuleNames: Core, CoreUObject, DataflowCore, DynamicMesh, GeometryCore, MeshUtilitiesCommon, PlanarCut, Voronoi

### `Plugins/Experimental/Fracture/Source/FractureEngine/Public/FractureEngineClustering.h` (Public)


#### class `FVoronoiPartitioner`  
`class FVoronoiPartitioner`  
_L13-73_
- L16 _public prototype_ `FVoronoiPartitioner(const FGeometryCollection* GeometryCollection, int32 ClusterIndex);`
- L24 _public prototype_ `void KMeansPartition(int32 InPartitionCount, int32 MaxIterations = 500, TArrayView<const FVector> InitialCenters = TArrayView<const FVector>());` — Cluster bodies into k partitions using K-Means. Connectivity is ignored: only spatial proximity is considered. @param InPartitionCount	Number of partitions to target, if InitialCenters is not provided @param MaxIterations		Maximum iterations of refinement of partitions. In many cases, K-Means will converge and stop early if MaxIterations is large. @param InitialCenters	If non-empty, these positions will be used to initialize the partition locations. The target partition count will then be the length of this array.
- L27 _public prototype_ `void SplitDisconnectedPartitions(FGeometryCollection* GeometryCollection);` — Split any partition islands into their own partition. This will possbily increase number of partitions to exceed desired count.
- L30 _public prototype_ `void MergeSingleElementPartitions(FGeometryCollection* GeometryCollection);` — Merge any partitions w/ only 1 body into a connected, neighboring partition (if any).  This can decrease the number of partitions below the desired count.
- L33 _public prototype_ `void MergeSmallPartitions(FGeometryCollection* GeometryCollection, float PartitionSizeThreshold);` — Merge any too-small partitions into a connected, neighboring partition (if any).  This can decrease the number of partitions below the desired count.
- L35 _public function_ `int32 GetPartitionCount() const`
- L37 _public function_ `int32 GetNonEmptyPartitionCount() const`
- L42 _public function_ `int32 GetIsolatedPartitionCount() const`
- L48 _public prototype_ `TArray<int32> GetPartition(int32 PartitionIndex) const;` — return the GeometryCollection TranformIndices within the partition.
- L50 _public prototype_ `static FBox GenerateBounds(const FGeometryCollection* GeometryCollection, int32 TransformIndex);`
- L53 _private prototype_ `void GenerateConnectivity(const FGeometryCollection* GeometryCollection);`
- L54 _private prototype_ `void CollectConnections(const FGeometryCollection* GeometryCollection, int32 Index, int32 OperatingLevel, TSet<int32>& OutConnections) const;`
- L55 _private prototype_ `void GenerateCentroids(const FGeometryCollection* GeometryCollection);`
- L56 _private prototype_ `FVector GenerateCentroid(const FGeometryCollection* GeometryCollection, int32 TransformIndex) const;`
- L57 _private prototype_ `void InitializePartitions(TArrayView<const FVector> InitialCenters = TArrayView<const FVector>());`
- L58 _private prototype_ `bool Refine();`
- L59 _private prototype_ `int32 FindClosestPartitionCenter(const FVector& Location) const;`
- L60 _private prototype_ `void MarkVisited(int32 Index, int32 PartitionIndex);`
- L63 _private member_ `TArray<int32> TransformIndices;`
- L64 _private member_ `TArray<FVector> Centroids;`
- L66 _private member_ `TArray<int32> Partitions;` — mapping from index into TransformIndices to partition number
- L67 _private member_ `int32 PartitionCount;`
- L68 _private member_ `TArray<int32> PartitionSize;`
- L69 _private member_ `TArray<FVector> PartitionCenters;`
- L71 _private member_ `TArray<TSet<int32>> Connectivity;` — mapping from index into TransformIndices to the set of connected transforms (also via their index in TransformIndices)
- L72 _private member_ `TArray<bool> Visited;`

#### enum `EFractureEngineClusterSizeMethod`  
`enum class EFractureEngineClusterSizeMethod : uint8`  
_L75-85_
- L78 _public enumerator_ `ByNumber` — Cluster by specifying an absolute number of clusters
- L80 _public enumerator_ `ByFractionOfInput` — Cluster by specifying a fraction of the number of input bones
- L82 _public enumerator_ `BySize` — Cluster by specifying the density of the input bones
- L84 _public enumerator_ `ByGrid` — Cluster by a regular grid distribution

#### class `FFractureEngineClustering`  
`class FFractureEngineClustering`  
_L87-168_
- L91 _public prototype_ `static void AutoCluster(FGeometryCollection& GeometryCollection, const TArray<int32>& BoneIndices, const EFractureEngineClusterSizeMethod ClusterSizeMethod, const uint32 SiteCount, const float SiteCountFraction, const float SiteSize, const bool bEnforceConnectivity, const bool bAvoidIsolated, const bool bEnforceSiteParameters, const int32 GridX = 2, const int32 GridY = 2, const int32 GridZ = 2, const float MinimumClusterSize = 0, const int32 KMeansIterations = 500, const bool bPreferConvexity = false, const float ConcavityErrorTolerance = 0);`
- L108 _public prototype_ `static void AutoCluster(FGeometryCollection& GeometryCollection, const int32 ClusterIndex, const EFractureEngineClusterSizeMethod ClusterSizeMethod, const uint32 SiteCount, const float SiteCountFraction, const float SiteSize, const bool bEnforceConnectivity, const bool bAvoidIsolated, const bool bEnforceSiteParameters, const int32 GridX = 2, const int32 GridY = 2, const int32 GridZ = 2, const float MinimumClusterSize = 0, const int32 KMeansIterations = 500, const bool bPreferConvexity = false, const float ConcavityErrorTolerance = 0);`
- L126 _public prototype_ `static void ConvexityBasedCluster(FGeometryCollection& GeometryCollection, int32 ClusterIndex, uint32 SiteCount, bool bEnforceConnectivity, bool bAvoidIsolated, float ConcavityErrorTolerance);` — Autoclustering that favors convex-shaped clusters
- L133 _public prototype_ `static TArray<FVector> GenerateGridSites( const FGeometryCollection& GeometryCollection, const TArray<int32>& BoneIndices, const int32 GridX, const int32 GridY, const int32 GridZ);`
- L140 _public prototype_ `static TArray<FVector> GenerateGridSites( const FGeometryCollection& GeometryCollection, const int32 ClusterIndex, const int32 GridX, const int32 GridY, const int32 GridZ, FBox* OutBounds = nullptr);`
- L150 _public prototype_ `static bool ClusterSelected( FGeometryCollection& GeometryCollection, TArray<int32>& InOutSelection );` — Cluster the chosen transform indices (and update the selection array to remove any that were not clustered, i.e. invalid or root transforms) @return true if the GeometryCollection was updated
- L157 _public prototype_ `static bool MergeSelectedClusters( FGeometryCollection& GeometryCollection, TArray<int32>& InOutSelection );` — Merge selected clusters. Non-clusters in the selection are converted to the closest (parent) clusters. On success, returns true and InOutSelection holds the index of the cluster to which the selection was merged.
- L163 _public prototype_ `static bool ClusterMagnet( FGeometryCollection& GeometryCollection, TArray<int32>& InOutSelection, int32 Iterations );` — Merge neighbors, and neighbors of neighbors (out to the Iterations number) to the selected clusters.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API FRACTUREENGINE_API`

### `Plugins/Experimental/Fracture/Source/FractureEngine/Public/FractureEngineConvex.h` (Public)


#### enum `EConvexHullSimplifyMethod`  
`enum class EConvexHullSimplifyMethod`  
_L15-19_
- reflection: `UENUM()`
- L17 _public enumerator_ `MeshQSlim`
- L18 _public enumerator_ `AngleTolerance`

#### struct `UE::FractureEngine::Convex::FSimplifyHullSettings`  
`struct FSimplifyHullSettings`  
_L24-38_
- desc: Options to control the simplification of an existing convex hull
- L26 _public member_ `EConvexHullSimplifyMethod SimplifyMethod = EConvexHullSimplifyMethod::MeshQSlim;`
- L28 _public member_ `double AngleThreshold = 0;` — used for AngleTolerance simplification
- L29 _public member_ `double SmallAreaThreshold = .1;` — optionally used for AngleTolerance to ignore very small faces
- L31 _public member_ `bool bUseGeometricTolerance = true;`
- L32 _public member_ `double ErrorTolerance = 5;`
- L34 _public member_ `bool bUseTargetTriangleCount = false;`
- L35 _public member_ `int32 TargetTriangleCount = 20;`
- L37 _public member_ `bool bUseExistingVertexPositions = true;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace FractureEngine` (scope `UE`)
- L21 _namespace_ `namespace Convex` (scope `UE::FractureEngine`)
- L44 _prototype_ `bool GetConvexHullsAsDynamicMesh(const FManagedArrayCollection& Collection, UE::Geometry::FDynamicMesh3& UpdateMesh, bool bRestrictToSelection = false, const TArrayView<const int32> TransformSelection = TArrayView<const int32>(), bool bRecomputeHulls = false);` (scope `UE::FractureEngine::Convex`) — Get the convex hulls on the given Collection as a Dynamic Mesh. Optionally only include the hulls on the transforms in TransformSelection. @return true if the collection has convex hulls, the bone selection (if present) was valid, and all requested convex hulls were included in the mesh
- L50 _prototype_ `bool GetConvexHullsAsDynamicMeshes(const FManagedArrayCollection& Collection, TArray<UE::Geometry::FDynamicMesh3>& UpdateMeshes, bool bRestrictToSelection = false, const TArrayView<const int32> TransformSelection = TArrayView<const int32>(), bool bRecomputeHulls = false);` (scope `UE::FractureEngine::Convex`) — Get the convex hulls on the given Collection as an array of dynamic meshes. Optionally only include the hulls on the transforms in TransformSelection. @return true if the collection has convex hulls, the bone selection (if present) was valid, and all requested convex hulls were included in the mesh array
- L56 _prototype_ `bool SimplifyConvexHulls(FManagedArrayCollection& Collection, const FSimplifyHullSettings& Settings, bool bRestrictToSelection = false, const TArrayView<const int32> TransformSelection = TArrayView<const int32>());` (scope `UE::FractureEngine::Convex`) — Simplify the convex hulls on the given Collection. Optionally only simplify the hulls on the transforms in TransformSelection. @return true if the collection has convex hulls and the hulls were either simplified or did not need to be
- L62 _prototype_ `bool SimplifyConvexHull(const ::Chaos::FConvex* InConvexHull, ::Chaos::FConvex* OutConvexHull, const FSimplifyHullSettings& Settings);` (scope `UE::FractureEngine::Convex`) — Simplify a convex hull using the given Settings.OutConvexHull can optionally be the same pointer as InConvexHull. @return true if the hull had valid data and either was simplified or did not need to be (e.g. already had few enough triangles)
- L68 _prototype_ `bool ComputeConvexHullsNegativeSpace(FManagedArrayCollection& Collection, UE::Geometry::FSphereCovering& OutNegativeSpace, const UE::Geometry::FNegativeSpaceSampleSettings& Settings, bool bRestrictToSelection = false, const TArrayView<const int32> TransformSelection = TArrayView<const int32>(), bool bFromRigidTransforms = true);` (scope `UE::FractureEngine::Convex`) — Compute negative space for the convex hulls on a geometry collection @return true if any negative space was found

### `Plugins/Experimental/Fracture/Source/FractureEngine/Public/FractureEngineEdit.h` (Public)


#### class `FFractureEngineEdit`  
`class FFractureEngineEdit`  
_L12-24_
- L16 _public prototype_ `static void DeleteBranch(FGeometryCollection& GeometryCollection, const TArray<int32>& InBoneSelection);`
- L18 _public prototype_ `static void SetVisibilityInCollectionFromTransformSelection(FManagedArrayCollection& InCollection, const TArray<int32>& InTransformSelection, bool bVisible);`
- L20 _public prototype_ `static void SetVisibilityInCollectionFromFaceSelection(FManagedArrayCollection& InCollection, const TArray<int32>& InFaceSelection, bool bVisible);`
- L22 _public prototype_ `static void Merge(FGeometryCollection& GeometryCollection, const TArray<int32>& InBoneSelection);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API FRACTUREENGINE_API`

### `Plugins/Experimental/Fracture/Source/FractureEngine/Public/FractureEngineEmbed.h` (Public)


#### class `FFractureEngineEmbed`  
`class FFractureEngineEmbed`  
_L8-12_

### `Plugins/Experimental/Fracture/Source/FractureEngine/Public/FractureEngineFracturing.h` (Public)


#### enum `EFractureBrickBondEnum`  
`enum class EFractureBrickBondEnum : uint8`  
_L19-26_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `Dataflow_FractureBrickBond_Stretcher UMETA(DisplayName = "Stretcher")`
- L22 _public enumerator_ `Dataflow_FractureBrickBond_Stack UMETA(DisplayName = "Stack")`
- L23 _public enumerator_ `Dataflow_FractureBrickBond_English UMETA(DisplayName = "English")`
- L24 _public enumerator_ `Dataflow_FractureBrickBond_Header UMETA(DisplayName = "Header")`
- L25 _public enumerator_ `Dataflow_FractureBrickBond_Flemish UMETA(DisplayName = "Flemish")`

#### enum `EMeshCutterCutDistribution`  
`enum class EMeshCutterCutDistribution : uint8`  
_L29-37_
- reflection: `UENUM(BlueprintType)`
- L32 _public enumerator_ `SingleCut UMETA(DisplayName = "Single Cut")` — Cut only once, at the cutting mesh's current location in the level
- L34 _public enumerator_ `UniformRandom UMETA(DisplayName = "Uniform Random")` — Scatter the cutting mesh in a uniform random distribution around the geometry bounding box
- L36 _public enumerator_ `Grid UMETA(DisplayName = "Grid")` — Arrange the cutting mesh in a regular grid pattern

#### enum `EMeshCutterPerCutMeshSelection`  
`enum class EMeshCutterPerCutMeshSelection : uint8`  
_L40-48_
- reflection: `UENUM(BlueprintType)`
- L43 _public enumerator_ `All` — Use all cut meshes for every cut
- L45 _public enumerator_ `Random` — Choose which cut mesh to use from the mesh array randomly, per cut
- L47 _public enumerator_ `Sequential` — Choose which cut mesh to use from the mesh array sequentially, starting with the first mesh and cycling through, per cut

#### struct `FUniformFractureSettings`  
`struct FUniformFractureSettings`  
_L50-66_
- L52 _public member_ `FTransform Transform;`
- L53 _public member_ `int32 MinVoronoiSites;`
- L54 _public member_ `int32 MaxVoronoiSites;`
- L55 _public member_ `int32 InternalMaterialID;`
- L56 _public member_ `int32 RandomSeed;`
- L57 _public member_ `float ChanceToFracture;`
- L58 _public member_ `bool GroupFracture;`
- L59 _public member_ `bool SplitIslands;`
- L60 _public member_ `double CloseVertexDistance = 1e-3;`
- L61 _public member_ `double VertexToSurfaceBridgeDistance = 0;`
- L62 _public member_ `float Grout;`
- L63 _public member_ `FNoiseSettings NoiseSettings;`
- L64 _public member_ `bool AddSamplesForCollision;`
- L65 _public member_ `float CollisionSampleSpacing;`

#### struct `FUniformFractureProcSettings`  
`struct FUniformFractureProcSettings`  
_L68-83_
- L70 _public member_ `FBox BBox;`
- L71 _public member_ `FTransform Transform;`
- L72 _public member_ `int32 MinVoronoiSites;`
- L73 _public member_ `int32 MaxVoronoiSites;`
- L74 _public member_ `int32 InternalMaterialID;`
- L75 _public member_ `int32 RandomSeed;`
- L76 _public member_ `bool SplitIslands;`
- L77 _public member_ `double CloseVertexDistance = 1e-3;`
- L78 _public member_ `double VertexToSurfaceBridgeDistance = 0;`
- L79 _public member_ `float Grout;`
- L80 _public member_ `FNoiseSettings NoiseSettings;`
- L81 _public member_ `bool AddSamplesForCollision;`
- L82 _public member_ `float CollisionSampleSpacing;`

#### class `FFractureEngineFracturing`  
`class FFractureEngineFracturing`  
_L85-284_
- L88 _public prototype_ `static void GenerateExplodedViewAttribute( FManagedArrayCollection& InOutCollection, const FVector& InScale, const float InUniformScale, const int32 InViewFractureLevel = -1, const int32 InMaxFractureLevel = -1);`
- L95 _public prototype_ `static int32 VoronoiFracture(FManagedArrayCollection& InOutCollection, FDataflowTransformSelection InTransformSelection, TArray<FVector> InSites, const FTransform& InTransform, int32 InRandomSeed, float InChanceToFracture, FIslandSplitSettings IslandSplitSettings, float InGrout, float InAmplitude, float InFrequency, float InPersistence, float InLacunarity, int32 InOctaveNumber, float InPointSpacing, bool InAddSamplesForCollision, float InCollisionSampleSpacing);`
- L112 _public prototype_ `static void GenerateSliceTransforms( const FBox& InBoundingBox, const int32 InRandomSeed, const int32 InNumPlanes, TArray<FTransform>& OutCuttingPlaneTransforms);`
- L118 _public prototype_ `static int32 PlaneCutter(FManagedArrayCollection& InOutCollection, FDataflowTransformSelection InTransformSelection, const FBox& InBoundingBox, const FTransform& InTransform, int32 InNumPlanes, int32 InRandomSeed, float InChanceToFracture, FIslandSplitSettings IslandSplitSettings, float InGrout, float InAmplitude, float InFrequency, float InPersistence, float InLacunarity, int32 InOctaveNumber, float InPointSpacing, bool InAddSamplesForCollision, float InCollisionSampleSpacing, TConstArrayView<FTransform> InCutPlaneTransforms = TConstArrayView<FTransform>());`
- L137 _public prototype_ `static void GenerateSliceTransforms(TArray<FTransform>& InOutCuttingPlaneTransforms, const FBox& InBoundingBox, int32 InSlicesX, int32 InSlicesY, int32 InSlicesZ, int32 InRandomSeed, float InSliceAngleVariation, float InSliceOffsetVariation);`
- L146 _public prototype_ `static int32 SliceCutter(FManagedArrayCollection& InOutCollection, FDataflowTransformSelection InTransformSelection, const FBox& InBoundingBox, int32 InSlicesX, int32 InSlicesY, int32 InSlicesZ, float InSliceAngleVariation, float InSliceOffsetVariation, int32 InRandomSeed, float InChanceToFracture, FIslandSplitSettings IslandSplitSettings, float InGrout, float InAmplitude, float InFrequency, float InPersistence, float InLacunarity, int32 InOctaveNumber, float InPointSpacing, bool InAddSamplesForCollision, float InCollisionSampleSpacing);`
- L167 _public prototype_ `static void AddBoxEdges(TArray<TTuple<FVector, FVector>>& InOutEdges, const FVector& InMin, const FVector& InMax);`
- L171 _public prototype_ `static void GenerateBrickTransforms(const FBox& InBounds, TArray<FTransform>& InOutBrickTransforms, const EFractureBrickBondEnum InBond, const float InBrickLength, const float InBrickHeight, const float InBrickDepth, TArray<TTuple<FVector, FVector>>& InOutEdges);`
- L179 _public prototype_ `static int32 BrickCutter(FManagedArrayCollection& InOutCollection, FDataflowTransformSelection InTransformSelection, const FBox& InBoundingBox, const FTransform& InTransform, EFractureBrickBondEnum InBond, float InBrickLength, float InBrickHeight, float InBrickDepth, int32 InRandomSeed, float InChanceToFracture, FIslandSplitSettings IslandSplitSettings, float InGrout, float InAmplitude, float InFrequency, float InPersistence, float InLacunarity, int32 InOctaveNumber, float InPointSpacing, bool InAddSamplesForCollision, float InCollisionSampleSpacing);`
- L200 _public prototype_ `static void GenerateMeshTransforms(TArray<FTransform>& MeshTransforms, const FBox& InBoundingBox, const int32 InRandomSeed, const EMeshCutterCutDistribution InCutDistribution, const int32 InNumberToScatter, const int32 InGridX, const int32 InGridY, const int32 InGridZ, const float InVariability, const float InMinScaleFactor, const float InMaxScaleFactor, const bool InRandomOrientation, const float InRollRange, const float InPitchRange, const float InYawRange);`
- L216 _public prototype_ `static int32 MeshCutter(TArray<FTransform>& MeshTransforms, FManagedArrayCollection& InOutCollection, const FDataflowTransformSelection& InTransformSelection, const UE::Geometry::FDynamicMesh3& InDynCuttingMesh, const int32 InRandomSeed, const float InChanceToFracture, const FIslandSplitSettings IslandSplitSettings, const float InCollisionSampleSpacing);`
- L225 _public prototype_ `static int32 MeshArrayCutter(TArray<FTransform>& MeshTransforms, FManagedArrayCollection& InOutCollection, const FDataflowTransformSelection& InTransformSelection, TArrayView<const UE::Geometry::FDynamicMesh3*> InDynCuttingMeshes, const EMeshCutterPerCutMeshSelection PerCutMeshSelection, const int32 InRandomSeed, const float InChanceToFracture, const FIslandSplitSettings IslandSplitSettings, const float InCollisionSampleSpacing);`
- L235 _public prototype_ `static int32 UniformFracture( FManagedArrayCollection& InOutCollection, FDataflowTransformSelection InTransformSelection, const FUniformFractureSettings& InUniformFractureSettings);`
- L240 _public prototype_ `static void InitColors(FManagedArrayCollection& InCollection);`
- L242 _public prototype_ `static void TransferBoneColorToVertexColor(FManagedArrayCollection& InCollection);`
- L244 _public prototype_ `static void SetBoneColorByParent( FManagedArrayCollection& InCollection, const FRandomStream& InRandomStream, int32 InLevel, const int32 InColorRangeMin = 40, const int32 InColorRangeMax = 190);`
- L251 _public prototype_ `static void SetBoneColorByLevel( FManagedArrayCollection& InCollection, int32 InLevel);`
- L255 _public prototype_ `static void SetBoneColorByCluster( FManagedArrayCollection& InCollection, const FRandomStream& InRandomStream, int32 InLevel, const int32 InColorRangeMin, const int32 InColorRangeMax);`
- L262 _public prototype_ `static void SetBoneColorByLeafLevel( FManagedArrayCollection& InCollection, int32 InLevel);`
- L266 _public prototype_ `static void SetBoneColorByLeaf( FManagedArrayCollection& InCollection, const FRandomStream& InRandomStream, int32 InLevel, const int32 InColorRangeMin, const int32 InColorRangeMax);`
- L273 _public prototype_ `static void SetBoneColorByAttr( FManagedArrayCollection& InCollection, const FString InAttribute, const float InMinAttrValue, float InMaxAttrValue, const FLinearColor InMinColor, const FLinearColor InMaxColor);`
- L281 _public prototype_ `static void SetBoneColorRandom( FManagedArrayCollection& InCollection, const FRandomStream& InRandomStream);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API FRACTUREENGINE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/Fracture/Source/FractureEngine/Public/FractureEngineMaterials.h` (Public)


#### class `FFractureEngineMaterials`  
`class FFractureEngineMaterials`  
_L12-32_
- L23 _public prototype_ `static void SetMaterial(FManagedArrayCollection& InCollection, const TArray<int32>& InBoneSelection, ETargetFaces TargetFaces, int32 MaterialID);`
- L25 _public prototype_ `static void SetMaterialOnGeometryAfter(FManagedArrayCollection& InCollection, int32 FirstGeometryIndex, ETargetFaces TargetFaces, int32 MaterialID);`
- L27 _public function_ `static void SetMaterialOnAllGeometry(FManagedArrayCollection& InCollection, ETargetFaces TargetFaces, int32 MaterialID)`

#### enum `FFractureEngineMaterials::ETargetFaces`  
`enum class ETargetFaces`  
_L16-21_
- L18 _public enumerator_ `InternalFaces`
- L19 _public enumerator_ `ExternalFaces`
- L20 _public enumerator_ `AllFaces`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API FRACTUREENGINE_API`

### `Plugins/Experimental/Fracture/Source/FractureEngine/Public/FractureEnginePlugin.h` (Public)


#### class `IFractureEnginePlugin`  
`class IFractureEnginePlugin : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public function_ `static inline IFractureEnginePlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Experimental/Fracture/Source/FractureEngine/Public/FractureEngineSampling.h` (Public)


#### enum `ENonUniformSamplingDistributionMode`  
`enum class ENonUniformSamplingDistributionMode : uint8`  
_L16-24_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `ENonUniformSamplingDistributionMode_Uniform UMETA(DisplayName = "Uniform")` — Uniform distribution of sizes, ie all equally likely
- L21 _public enumerator_ `ENonUniformSamplingDistributionMode_Smaller UMETA(DisplayName = "Smaller")` — Distribution is weighted towards smaller points
- L23 _public enumerator_ `ENonUniformSamplingDistributionMode_Larger UMETA(DisplayName = "Larger")` — Distribution is weighted towards larger points

#### enum `ENonUniformSamplingWeightMode`  
`enum class ENonUniformSamplingWeightMode : uint8`  
_L27-44_
- reflection: `UENUM(BlueprintType)`
- L33 _public enumerator_ `ENonUniformSamplingWeightMode_WeightToRadius UMETA(DisplayName = "Weight To Radius")` — Weights are clamped to [0,1] and used to interpolate Min/Max Radius. This is a "hard constraint", ie if the weight at a point is 1, only a "max radius" sample may be placed there, otherwise no samples at all (so no "filling in" smaller samples between large ones)
- L38 _public enumerator_ `ENonUniformSamplingWeightMode_FilledWeightToRadius UMETA(DisplayName = "Filled Weight To Radius")` — Weights are clamped to [0,1] and used to interpolate Min/Max Radius, with decay, so that smaller-radius samples will infill between large ones. So areas with large weight may still end up with some variable-radius samples, but areas with 0 weight will only ever have min-radius samples.
- L43 _public enumerator_ `ENonUniformSamplingWeightMode_WeightedRandom UMETA(DisplayName = "Weighted Random")` — Weight is used to create nonuniform random sampling, ie it nudges the random sample-radius distribution but does not directly control it. So samples with any radius can still appear at any location, but if weight=1 then max-radius samples are more likely, etc.

#### class `FFractureEngineSampling`  
`class FFractureEngineSampling`  
_L46-95_
- L52 _public prototype_ `static void ComputeUniformPointSampling(const UE::Geometry::FDynamicMesh3& InMesh, const float InSamplingRadius, const int32 InMaxNumSamples, const float InSubSampleDensity, const int32 InRandomSeed, TArray<FTransform>& OutSamples, TArray<int32>& OutTriangleIDs, TArray<FVector>& OutBarycentricCoords);` — Computes a Poisson sampling on the InMesh
- L64 _public prototype_ `static void ComputeNonUniformPointSampling(const UE::Geometry::FDynamicMesh3& InMesh, const float InSamplingRadius, const int32 InMaxNumSamples, const float InSubSampleDensity, const int32 InRandomSeed, const float InMaxSamplingRadius, const ENonUniformSamplingDistributionMode InSizeDistribution, const float InSizeDistributionPower, TArray<FTransform>& OutSamples, TArray<float>& OutSampleRadii, TArray<int32>& OutTriangleIDs, TArray<FVector>& OutBarycentricCoords);` — Computes a NonUniform sampling on the InMesh
- L80 _public prototype_ `static void ComputeVertexWeightedPointSampling(const UE::Geometry::FDynamicMesh3& InMesh, const TArray<float>& InVertexWeights, const float InSamplingRadius, const int32 InMaxNumSamples, const float InSubSampleDensity, const int32 InRandomSeed, const float InMaxSamplingRadius, const ENonUniformSamplingDistributionMode InSizeDistribution, const float InSizeDistributionPower, const ENonUniformSamplingWeightMode InWeightMode, const bool InInvertWeights, TArray<FTransform>& OutSamples, TArray<float>& OutSampleRadii, TArray<int32>& OutTriangleIDs, TArray<FVector>& OutBarycentricCoords);` — Computes a vertex weighted sampling on the InMesh

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/Fracture/Source/FractureEngine/Public/FractureEngineSelection.h` (Public)


#### class `FFractureEngineSelection`  
`class FFractureEngineSelection`  
_L14-52_
- L17 _public prototype_ `static void GetRootBones(const FManagedArrayCollection& Collection, TArray<int32>& RootBonesOut);`
- L18 _public prototype_ `static void GetRootBones(const FManagedArrayCollection& Collection, FDataflowTransformSelection& TransformSelection);`
- L20 _public prototype_ `static void SelectParent(const FManagedArrayCollection& Collection, TArray<int32>& SelectedBones);`
- L21 _public prototype_ `static void SelectParent(const FManagedArrayCollection& Collection, FDataflowTransformSelection& TransformSelection);`
- L23 _public prototype_ `static void SelectChildren(const FManagedArrayCollection& Collection, TArray<int32>& SelectedBones);`
- L24 _public prototype_ `static void SelectChildren(const FManagedArrayCollection& Collection, FDataflowTransformSelection& TransformSelection);`
- L26 _public prototype_ `static void SelectSiblings(const FManagedArrayCollection& Collection, TArray<int32>& SelectedBones);`
- L27 _public prototype_ `static void SelectSiblings(const FManagedArrayCollection& Collection, FDataflowTransformSelection& TransformSelection);`
- L29 _public prototype_ `static void SelectLevel(const FManagedArrayCollection& Collection, TArray<int32>& SelectedBones);`
- L30 _public prototype_ `static void SelectLevel(const FManagedArrayCollection& Collection, FDataflowTransformSelection& TransformSelection);`
- L32 _public prototype_ `static void SelectContact(FGeometryCollection& GeometryCollection, TArray<int32>& SelectedBones);`
- L33 _public prototype_ `static void SelectContact(FGeometryCollection& GeometryCollection, FDataflowTransformSelection& TransformSelection);`
- L35 _public prototype_ `static void SelectLeaf(const FGeometryCollection& GeometryCollection, TArray<int32>& SelectedBones);`
- L36 _public prototype_ `static void SelectLeaf(const FGeometryCollection& GeometryCollection, FDataflowTransformSelection& TransformSelection);`
- L38 _public prototype_ `static void SelectCluster(const FGeometryCollection& GeometryCollection, TArray<int32>& SelectedBones);`
- L39 _public prototype_ `static void SelectCluster(const FGeometryCollection& GeometryCollection, FDataflowTransformSelection& TransformSelection);`
- L41 _public prototype_ `static void SelectByPercentage(TArray<int32>& SelectedBones, const int32 Percentage, const bool Deterministic, const float RandomSeed);`
- L42 _public prototype_ `static void SelectByPercentage(FDataflowTransformSelection& TransformSelection, const int32 Percentage, const bool Deterministic, const float RandomSeed);`
- L44 _public prototype_ `static void SelectBySize(FGeometryCollection& GeometryCollection, TArray<int32>& SelectedBones, const float SizeMin, const float SizeMax);`
- L45 _public prototype_ `static void SelectBySize(FGeometryCollection& GeometryCollection, FDataflowTransformSelection& TransformSelection, const float SizeMin, const float SizeMax);`
- L47 _public prototype_ `static void SelectByVolume(FGeometryCollection& GeometryCollection, TArray<int32>& SelectedBones, const float VolumeMin, const float VolumeMax);`
- L48 _public prototype_ `static void SelectByVolume(FGeometryCollection& GeometryCollection, FDataflowTransformSelection& TransformSelection, const float VolumeMin, const float VolumeMax);`
- L50 _public prototype_ `static bool IsBoneSelectionValid(const FManagedArrayCollection& Collection, const TArray<int32>& SelectedBones);`
- L51 _public prototype_ `static bool IsSelectionValid(const FManagedArrayCollection& Collection, const TArray<int32>& SelectedItems, const FName ItemGroup);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API FRACTUREENGINE_API`

### `Plugins/Experimental/Fracture/Source/FractureEngine/Public/FractureEngineUtility.h` (Public)


#### enum `EFixTinyGeoMergeType`  
`enum class EFixTinyGeoMergeType : uint8`  
_L17-21_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `MergeGeometry UMETA(DisplayName = "Merge Geometry")`
- L20 _public enumerator_ `MergeClusters UMETA(DisplayName = "Merge Clusters")`

#### enum `EFixTinyGeoNeighborSelectionMethod`  
`enum class EFixTinyGeoNeighborSelectionMethod : uint8`  
_L24-32_
- reflection: `UENUM(BlueprintType)`
- L27 _public enumerator_ `LargestNeighbor UMETA(DisplayName = "Largest Neighbor")` — Merge to the neighbor with the largest volume
- L29 _public enumerator_ `NearestCenter UMETA(DisplayName = "Nearest Center")` — Merge to the neighbor with the closest center
- L31 _public enumerator_ `LargestContactArea` — Merge to the neighbor with the largest contact surface area

#### enum `EFixTinyGeoUseBoneSelection`  
`enum class EFixTinyGeoUseBoneSelection : uint8`  
_L35-40_
- reflection: `UENUM(BlueprintType)`
- L37 _public enumerator_ `NoEffect UMETA(DisplayName = "No Effect")`
- L38 _public enumerator_ `AlsoMergeSelected UMETA(DisplayName = "Also Merge Selected")`
- L39 _public enumerator_ `OnlyMergeSelected UMETA(DisplayName = "Only Merge Selected")`

#### enum `EFixTinyGeoGeometrySelectionMethod`  
`enum class EFixTinyGeoGeometrySelectionMethod : uint8`  
_L43-49_
- reflection: `UENUM(BlueprintType)`
- L46 _public enumerator_ `VolumeCubeRoot UMETA(DisplayName = "Size")` — Select by cube root of volume
- L48 _public enumerator_ `RelativeVolume UMETA(DisplayName = "Relative Volume")` — Select by cube root of volume relative to the overall shape's cube root of volume

#### class `FFractureEngineUtility`  
`class FFractureEngineUtility`  
_L51-104_
- L57 _public prototype_ `static void ConvertBoxToVertexAndTriangleData(const FBox& InBox, TArray<FVector3f>& OutVertices, TArray<FIntVector>& OutTriangles);` — Outputs the vertex and triangle data of a FBox into OutVertices and OutTriangles
- L62 _public prototype_ `static void ConstructMesh(UE::Geometry::FDynamicMesh3& OutMesh, const TArray<FVector3f>& InVertices, const TArray<FIntVector>& InTriangles);` — Creates a mesh from vertex and triangle data
- L67 _public prototype_ `static void DeconstructMesh(const UE::Geometry::FDynamicMesh3& InMesh, TArray<FVector3f>& OutVertices, TArray<FIntVector>& OutTriangles);` — Outputs the vertex and triangle data of a mesh into OutVertices and OutTriangles
- L69 _public prototype_ `static void FixTinyGeo(FManagedArrayCollection& InOutCollection, FDataflowTransformSelection InTransformSelection, const EFixTinyGeoMergeType InMergeType, const bool InOnFractureLevel, const EFixTinyGeoGeometrySelectionMethod InSelectionMethod, const float InMinVolumeCubeRoot, const float InRelativeVolume, const EFixTinyGeoUseBoneSelection InUseBoneSelection, const bool InOnlyClusters, const EFixTinyGeoNeighborSelectionMethod InNeighborSelection, const bool InOnlyToConnected, const bool InOnlySameParent, const bool bUseCollectionProximity = true);`
- L83 _public prototype_ `static void RecomputeNormalsInGeometryCollection(FManagedArrayCollection& InOutCollection, FDataflowTransformSelection InTransformSelection, const bool InOnlyTangents, const bool InRecomputeSharpEdges, const float InSharpEdgeAngleThreshold, const bool InOnlyInternalSurfaces);`
- L90 _public prototype_ `static int32 ResampleGeometryCollection(FManagedArrayCollection& InOutCollection, FDataflowTransformSelection InTransformSelection, const float InCollisionSampleSpacing);`
- L94 _public prototype_ `static void ValidateGeometryCollection(FManagedArrayCollection& InOutCollection, const bool InRemoveUnreferencedGeometry, const bool InRemoveClustersOfOne, const bool InRemoveDanglingClusters);`
- L99 _public prototype_ `static void SplitIslands(FManagedArrayCollection& InOutCollection, FDataflowTransformSelection InTransformSelection, const float InCloseVertexDistance, const float InVertexToSurfaceBridgeDistance);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API FRACTUREENGINE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)
