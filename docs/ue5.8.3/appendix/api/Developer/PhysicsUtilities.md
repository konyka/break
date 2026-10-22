# Developer / PhysicsUtilities

- module root: `Source/Developer/PhysicsUtilities`
- headers: 5; symbols: 109
- symbol kinds: class=3, enum=2, enumerator=12, function=3, macro=1, member=31, namespace=5, prototype=44, struct=1, typedef=7
- PrivateDependencyModuleNames: GeometryCore, MeshUtilitiesCommon, MeshUtilitiesEngine
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, Engine, PhysicsCore

### `Source/Developer/PhysicsUtilities/Private/LevelSetHelpers.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L15 _namespace_ `namespace LevelSetHelpers`
- L17 _prototype_ `bool CreateLevelSetForBone(UBodySetup* BodySetup, const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, uint32 InResolution);` (scope `LevelSetHelpers`)
- L18 _prototype_ `void CreateDynamicMesh(const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, UE::Geometry::FDynamicMesh3& OutMesh);` (scope `LevelSetHelpers`)
- L19 _prototype_ `bool CreateLevelSetForMesh(const UE::Geometry::FDynamicMesh3& InMesh, int32 InLevelSetGridResolution, FKLevelSetElem& OutElement);` (scope `LevelSetHelpers`)
- L20 _prototype_ `bool CreateLevelSetForMesh(const UE::Geometry::FDynamicMesh3& InMesh, int32 InLevelSetGridResolution, Chaos::FLevelSetPtr& OutElement);` (scope `LevelSetHelpers`)

### `Source/Developer/PhysicsUtilities/Private/SkinnedBoneTriangleCache.h` (Private)


#### class `FSkinnedBoneTriangleCache`  
`class FSkinnedBoneTriangleCache`  
_L30-100_
- desc: To build a convex hull for a bone, DecomposeMeshToHulls() requires an array of vertex positions and an array of indices to these vertices (used to specify the triangles that make up the surface of that bone). In order to provide this information, we need to know which triangles a bone "owns". A bone owns a triangle if at least one vertex used in the triangle is influenced by the bone. Once we know which triangles the bone owns, we can provide the arrays of positions and indices. To find out which triangles a bone owns, we first need to build a set of which vertices are influenced by that bone. Once we have this, we can check each triangle in the mesh to see if the bone owns it; if the bone does own the triangle, the index of that triangle can then be stored in another array. Finally, knowing all the triangles that a bone owns, we can generate an array of all the vertex positions used by these triangles, along with a corresponding local index array.
- L33 _public prototype_ `explicit FSkinnedBoneTriangleCache(const USkeletalMesh& InSkeletalMesh, const FPhysAssetCreateParams& Params);`
- L35 _public prototype_ `void BuildCache();`
- L36 _public prototype_ `void GetVerticesAndIndicesForBone(const int32 BoneIndex, TArray<FVector3f>& OutVertexPositions, TArray<uint32>& OutIndices) const;`
- L38 _public prototype_ `void GetVerticesAndIndicesForBones(const int32 PrimaryBoneIndex, const TArray<int32>& BoneIndices, TArray<FVector3f>& OutVertexPositions, TArray<uint32>& OutIndices, TArray<uint32>& OutLocalToSkinnedVertexIndex) const;` — Vertex positions will be transformed by PrimaryBoneIndex's transform matrix.
- L40 _public function_ `bool IsBuilt() const`
- L43 _private typedef_ `typedef int32 FBoneIndex;`
- L44 _private typedef_ `typedef uint32 FSkinnedVertexIndex;`
- L45 _private typedef_ `typedef uint32 FTriangleIndex;`
- L47 _private typedef_ `typedef TSet<FSkinnedVertexIndex> FInfluencedVerticesSet;`
- L48 _private typedef_ `typedef TMap<FBoneIndex, FInfluencedVerticesSet> FBoneIndexToInfluencedVertices;`
- L50 _private typedef_ `typedef TArray<FTriangleIndex> FTriangleArray;`
- L51 _private typedef_ `typedef TMap<FBoneIndex, FTriangleArray> FBoneIndexToTriangles;`
- L53 _private function_ `inline static uint32 BufferIndexForTri(const FTriangleIndex TriangleIndex, const int32 TriangleVertex = 0)`
- L58 _private prototype_ `FMatrix BoneTransformMatrix(FBoneIndex BoneIndex) const;`
- L66 _private prototype_ `void BuildInfluencedIndexSetForEachBone();` — In order to generate a set of triangles owned by each bone, we need to build up a set of vertices influenced by each bone. This boils down to creating set of vertex indices, which index into the LOD model's vertex array. If a bone's set contains an index, the corresponding vertex is influenced by that bone.
- L69 _private prototype_ `void AddIndexToInfluencerBoneSets(const FSkinnedVertexIndex VertIndex);` — Here we pass in an index to the vertex array, and determine which sets it should be added to.
- L72 _private prototype_ `void BuildOwnedTrianglesSetForEachBone();` — Once the sets of influences vertices have been computed, the sets of owned triangles can be built.
- L75 _private prototype_ `void AddTriangleIndexToOwnerBoneSets(const FTriangleIndex TriangleIndex);` — Here, each triangle index is added to its appropriate sets.
- L77 _private prototype_ `FVector3f VertexPosition(const FSkinnedVertexIndex VertIndex, const FMatrix& ComponentToBoneMatrix) const;`
- L79 _private prototype_ `void GetVerticesAndIndicesForBoneInternal(const int32 TrianglesBoneIndex, const int32 TransformBoneIndex, TArray<FVector3f>& OutVertexPositions, TArray<uint32>& OutIndices, TArray<uint32>& OutLocalToSkinnedVertexIndex) const;`
- L82 _private member_ `const USkeletalMesh& SkeletalMesh;` — Inputs
- L85 _private member_ `const class FSkeletalMeshModel& StaticLODModel;` — Computed from inputs
- L86 _private member_ `const class FSkeletalMeshRenderData& RenderData;`
- L87 _private member_ `const class FPositionVertexBuffer& VertexBuffer;`
- L94 _private member_ `EPhysAssetFitVertWeight InfluenceHeuristic;` — EVW_AnyWeight:		Any vertex influenced by the bone is included in the set. EVW_DominantWeight:	Only vertices where the given bone has the highest influence are included in the set. Note that if two bones tie for the largest influence on a vertex, the vertex is included in both sets.
- L97 _private member_ `FBoneIndexToInfluencedVertices BoneIndexToInfluencedVertices;` — Internal
- L98 _private member_ `FBoneIndexToTriangles BoneIndexToTriangles;`
- L99 _private member_ `TArray<FSkinnedVertexIndex> LODModelIndexBufferInOrder;`

### `Source/Developer/PhysicsUtilities/Private/SkinnedLevelSetBuilder.h` (Private)


#### class `FSkinnedLevelSetBuilder`  
`class FSkinnedLevelSetBuilder : public Chaos::FWeightedLatticeImplicitObjectBuilder`  
_L17-44_
- inherits: `Chaos::FWeightedLatticeImplicitObjectBuilder`
- L21 _public prototype_ `FSkinnedLevelSetBuilder(const USkeletalMesh& InSkeletalMesh, const FSkinnedBoneTriangleCache& InTriangleCache, const int32 InRootBoneIndex);`
- L23 _public prototype_ `bool InitializeSkinnedLevelset(const FPhysAssetCreateParams& Params, const TArray<int32>& BoneIndices, TArray<uint32>& OutOrigIndices);`
- L24 _public prototype_ `void AddBoneInfluence(int32 PrimaryBoneIndex, const TArray<int32>& AllBonesForInfluence);`
- L26 _public prototype_ `FKSkinnedLevelSetElem CreateSkinnedLevelSetElem();`
- L28 _public prototype_ `void GetInfluencingBones(const TArray<uint32>& SkinnedVertexIndices, TSet<int32>& Bones);`
- L32 _private member_ `const USkeletalMesh& SkeletalMesh;` — Input
- L33 _private member_ `const FSkinnedBoneTriangleCache& TriangleCache;`
- L34 _private member_ `const int32 RootBoneIndex;`
- L37 _private member_ `FSkeletalMeshModel* StaticLODModel;` — Computed from Input
- L38 _private member_ `const FSkeletalMeshRenderData* RenderData;`
- L41 _private member_ `Chaos::FLevelSetPtr LevelSet;` — Output
- L43 _private prototype_ `float GetWeightForIndices(const TSet<int32>& BoneIndices, uint32 VertIndex) const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Chaos`

### `Source/Developer/PhysicsUtilities/Public/ConvexDecompTool.h` (Public)


#### class `IDecomposeMeshToHullsAsync`  
`class IDecomposeMeshToHullsAsync`  
_L34-57_
- L38 _public prototype_ `virtual const FString &GetCurrentStatus(void) const = 0;` — Returns the current status message in the decomposition process.  An empty string is returns if the convex decomposition is complete.
- L48 _public prototype_ `virtual bool DecomposeMeshToHullsAsyncBegin(UBodySetup* InBodySetup, TArray<FVector3f>&& InVertices, TArray<uint32>&& InIndices, uint32 InHullCount, int32 InMaxHullVerts, uint32 InResolution = DEFAULT_HACD_VOXEL_RESOLUTION) = 0;` — Utility for turning arbitrary mesh into convex hulls.  This can be called multiple times for multiple UBodySetup results and they will be done processed in sequential order @output		InBodySetup			BodySetup that will have its existing hulls removed and replaced with results of decomposition. @param		InVertices			Array of vertex positions of input mesh, whose ownership is transferred to the async task @param		InIndices			Array of triangle indices for input mesh, whose ownership is transferred to the async task @param		InAccuracy			Value between 0 and 1, controls how accurate hull generation is @param		InMaxHullVerts		Number of verts allowed in a hull
- L51 _public prototype_ `virtual bool IsComplete(void) = 0;` — Returns true if the convex decomposition process has completed and results are ready.
- L54 _public prototype_ `virtual void Release(void) = 0;` — Release the async convex decomposition interface
- L56 _protected prototype_ `virtual ~IDecomposeMeshToHullsAsync(void) = default;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define DEFAULT_HACD_VOXEL_RESOLUTION 100000`
- L32 _prototype_ `void DecomposeMeshToHulls(UBodySetup* InBodySetup, const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, uint32 InHullCount, int32 InMaxHullVerts,uint32 InResolution= DEFAULT_HACD_VOXEL_RESOLUTION);` — Utility for turning arbitrary mesh into convex hulls. @output		InBodySetup			BodySetup that will have its existing hulls removed and replaced with results of decomposition. @param		InVertices			Array of vertex positions of input mesh @param		InIndices			Array of triangle indices for input mesh @param		InAccuracy			Value between 0 and 1, controls how accurate hull generation is @param		InMaxHullVerts		Number of verts allowed in a hull
- L60 _prototype_ `IDecomposeMeshToHullsAsync *CreateIDecomposeMeshToHullAsync(void);` — Creates the interface to the asynchronous convex decomposition tool chain

### `Source/Developer/PhysicsUtilities/Public/PhysicsAssetUtils.h` (Public)


#### enum `EPhysAssetFitGeomType`  
`enum EPhysAssetFitGeomType : int`  
_L17-29_
- reflection: `UENUM()`
- L19 _public enumerator_ `EFG_Box UMETA(DisplayName="Box")`
- L20 _public enumerator_ `EFG_Sphyl UMETA(DisplayName="Capsule")`
- L21 _public enumerator_ `EFG_Sphere UMETA(DisplayName="Sphere")`
- L22 _public enumerator_ `EFG_TaperedCapsule UMETA(DisplayName="Tapered Capsule (Cloth Only)")`
- L23 _public enumerator_ `EFG_SingleConvexHull UMETA(DisplayName="Single Convex Hull")`
- L24 _public enumerator_ `EFG_MultiConvexHull UMETA(DisplayName="Multi Convex Hull")`
- L25 _public enumerator_ `EFG_LevelSet UMETA(DisplayName="Level Set (Experimental, Cloth Only)")`
- L26 _public enumerator_ `EFG_SkinnedLevelSet UMETA(DisplayName="Skinned Level Set (Experimental, Cloth Only)")`
- L27 _public enumerator_ `EFG_MLLevelSet UMETA(Hidden)`
- L28 _public enumerator_ `EFG_SkinnedTriangleMesh UMETA(Hidden)`

#### enum `EPhysAssetFitVertWeight`  
`enum EPhysAssetFitVertWeight : int`  
_L32-36_
- reflection: `UENUM()`
- L34 _public enumerator_ `EVW_AnyWeight UMETA(DisplayName="Any Weight")`
- L35 _public enumerator_ `EVW_DominantWeight UMETA(DisplayName="Dominant Weight")`

#### struct `FPhysAssetCreateParams`  
`struct FPhysAssetCreateParams`  
_L40-140_
- reflection: `USTRUCT()`
- desc: Parameters for PhysicsAsset creation
- L44 _public function_ `FPhysAssetCreateParams()`
- L67 _public member_ `float MinBoneSize;` — `UPROPERTY(EditAnywhere, Category = "Body Creation")` — Bones that are shorter than this value will be ignored for body creation
- L71 _public member_ `float MinWeldSize;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Body Creation")` — Bones that are smaller than this value will be merged together for body creation
- L75 _public member_ `TEnumAsByte<EPhysAssetFitGeomType> GeomType;` — `UPROPERTY(EditAnywhere, Category = "Body Creation", meta=(DisplayName="Primitive Type"))` — The geometry type that should be used when creating bodies
- L79 _public member_ `TEnumAsByte<EPhysAssetFitVertWeight> VertWeight;` — `UPROPERTY(EditAnywhere, Category = "Body Creation", meta=(DisplayName="Vertex Weighting Type"))` — How vertices are mapped to bones when approximating them with bodies
- L86 _public member_ `bool bAlwaysUseVertices;` — `UPROPERTY(EditAnywhere, Category = "Body Creation")` — If true, then mesh vertices are always used to calculate the collision shape, which can be slow. If false then the simpler shapes will not use vertices, which can result in faster processing.
- L93 _public member_ `bool bIncludeChildBones;` — `UPROPERTY(EditAnywhere, Category = "Body Creation")` — If true, then when mesh vertices are used, non-physical bones of the current bone will be included when calculating the collision shapes.
- L97 _public member_ `bool bAutoOrientToBone;` — `UPROPERTY(EditAnywhere, Category = "Body Creation")` — Whether to automatically orient the created bodies to their corresponding bones
- L101 _public member_ `bool bCreateConstraints;` — `UPROPERTY(EditAnywhere, Category = "Constraint Creation")` — Whether to create constraints between adjacent created bodies
- L105 _public member_ `bool bWalkPastSmall;` — `UPROPERTY(EditAnywhere, Category = "Body Creation", meta=(DisplayName="Walk Past Small Bones"))` — Whether to skip small bones entirely (rather than merge them with adjacent bones)
- L109 _public member_ `bool bBodyForAll;` — `UPROPERTY(EditAnywhere, Category = "Body Creation", meta=(DisplayName="Create Body for All Bones"))` — Forces creation of a body for each bone
- L113 _public member_ `bool bDisableCollisionsByDefault;` — `UPROPERTY(EditAnywhere, Category = "Body Creation")` — Whether to disable collision of body with other bodies on creation
- L117 _public member_ `TEnumAsByte<EAngularConstraintMotion> AngularConstraintMode;` — `UPROPERTY(EditAnywhere, Category = "Constraint Creation", meta=(EditCondition="bCreateConstraints"))` — The type of angular constraint to create between bodies
- L121 _public member_ `int32 LodIndex;` — `UPROPERTY(EditAnywhere, Category = "Body Creation")` — The LOD index use to create the physics asset.
- L125 _public member_ `int32 HullCount;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Body Creation", meta = (EditCondition = "GeomType == EPhysAssetFitGeomType::EFG_MultiConvexHull", EditConditionHides))` — When creating multiple convex hulls, the maximum number that will be created.
- L129 _public member_ `int32 MaxHullVerts;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Body Creation", meta = (EditCondition = "GeomType == EPhysAssetFitGeomType::EFG_MultiConvexHull || GeomType == EPhysAssetFitGeomType::EFG_SingleConvexHull", EditConditionHides))` — When creating convex hulls, the maximum verts that should be created
- L134 _public member_ `int32 LevelSetResolution;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Body Creation", meta = (ClampMin = 1, UIMin = 10, UIMax = 100, ClampMax = 500, EditCondition = "GeomType == EPhysAssetFitGeomType::EFG_LevelSet || GeomType == EPhysAssetFitGeomType::EFG_SkinnedLevelSet", EditConditionHides))` — When creating level sets, the grid resolution to use
- L139 _public member_ `int32 LatticeResolution;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Body Creation", meta = (ClampMin = 1, UIMin = 10, UIMax = 100, ClampMax = 500, EditCondition = "GeomType == EPhysAssetFitGeomType::EFG_SkinnedLevelSet", EditConditionHides))` — When creating skinned level sets, the embedding grid resolution to use

#### Free symbols / members of external scopes

- L147 _namespace_ `namespace FPhysicsAssetUtils`
- L159 _prototype_ `bool CreateFromSkeletalMesh(UPhysicsAsset* PhysicsAsset, USkeletalMesh* SkelMesh, const FPhysAssetCreateParams& Params, FText& OutErrorMessage, bool bSetToMesh = true, bool bShowProgress = true);` (scope `FPhysicsAssetUtils`) — Given a USkeletalMesh, construct a new PhysicsAsset automatically, using the vertices weighted to each bone to calculate approximate collision geometry. Ball-and-socket joints will be created for every joint by default. @param	PhysicsAsset		The PhysicsAsset instance to setup @param	SkelMesh			The Skeletal Mesh to create the physics asset from @param	Params				Additional creation parameters @param	OutErrorMessage		Additional error information @param	bSetToMesh			Whether or not to apply the physics asset to SkelMesh immediately
- L177 _prototype_ `bool CreateCollisionFromBone( UBodySetup* BodySetup, USkeletalMesh* SkelMesh, int32 BoneIndex, const FPhysAssetCreateParams& Params, const FBoneVertInfo& Info, const UPhysicsAsset* PhysicsAsset, TConstArrayView<int32> BoneIndicesInCreation = TConstArrayView<int32>());` (scope `FPhysicsAssetUtils`) — Replaces any collision already in the BodySetup with an auto-generated one using the parameters provided. @warning Certain physics geometry types, such as multi-convex hull, must recreate internal caches every time this function is called. If you find you're calling this function repeatedly for different bone indices on the same mesh, CreateFromSkeletalMesh or CreateCollisionsFromBones will provide better performance. @param	BodySetup              BodySetup to create the collision for @param	SkelMesh               The SkeletalMesh we create collision for @param	BoneIndex              Index of the bone the collision is created for @param	Params                 Additional parameters to control the creation @param   Info                   The vertices to create the collision for @param   PhysicsAsset           If set, then this can/will be used to recursively find relevant child bones for collision generation @param   BoneIndicesInCreation  If set, then this can/will be used to identify bones that will be physical (for collision generation) and should not be included in another bone's collision @return  Returns true if successfully created collision from bone
- L192 _prototype_ `bool CreateCollisionFromBones( UBodySetup* BodySetup, USkeletalMesh* SkelMesh, const TArray<int32>& BoneIndices, FPhysAssetCreateParams& Params, const FBoneVertInfo& Info, const UPhysicsAsset* PhysicsAsset );` (scope `FPhysicsAssetUtils`) — Replaces any collision already in the BodySetup with an auto-generated one using the parameters provided. @param	BodySetup					BodySetup to create the collision for @param	SkelMesh			The SkeletalMesh we create collision for @param	BoneIndices			Indices of the bones the collisions are created for @param	Params				Additional parameters to control the creation @param	Info				The vertices to create the collision for @param   PhysicsAsset        If set, then this can/will be used to recursively find relevant child bones for collision generation @return  Returns true if successfully created collision from all specified bones
- L204 _prototype_ `bool CreateCollisionsFromBones(UPhysicsAsset* PhysicsAsset, USkeletalMesh* SkelMesh, const TArray<int32>& BodyIndices, const FPhysAssetCreateParams& Params, const TArray<FBoneVertInfo>& Infos, TArray<int32>& OutSuccessfulBodyIndices);` (scope `FPhysicsAssetUtils`) — Replaces any collision already in the  with an auto-generated ones using the parameters provided. @param	PhysicsAsset		The PhysicsAsset instance to update @param	SkelMesh			The Skeletal Mesh to create the physics asset from @param	BodyIndices			Indices of the existing BodySetups the collisions are created for @param	Params				Additional parameters to control the creation @param	Infos				The vertices to create the collisions for (parallel array to BodyIndices) @param   OutSuccessfulBodyIndices Newly created BodySetup indices. @return  Returns true if successfully created collision from all specified bodies
- L216 _prototype_ `int32 GenerateSkinnedTriangleMesh(UPhysicsAsset* PhysicsAsset, USkeletalMesh* SkelMesh, int32 LODIndex, const FPhysAssetCreateParams& Params, FText& OutErrorMessage, bool bShowProgress = true);` (scope `FPhysicsAssetUtils`) — Given a USkeletalMesh, generate a Skinned Triangle Mesh primitive and add it to the root body (creating a new one if needed). @param	PhysicsAsset		The PhysicsAsset instance to update @param	SkelMesh			The Skeletal Mesh to create the physics asset from @param	LODIndex			SkelMesh LOD index to use. @param	Params				Additional creation parameters @param	OutErrorMessage		Additional error information @return  Index of body under which the new Skinned Triangle Mesh primitive was created (or INDEX_NONE if failure)
- L223 _prototype_ `void WeldBodies(UPhysicsAsset* PhysAsset, int32 BaseBodyIndex, int32 AddBodyIndex, USkeletalMeshComponent* SkelComp);` (scope `FPhysicsAssetUtils`) — Does a few things: - add any collision primitives from body2 into body1 (adjusting the tm of each). - reconnect any constraints between 'add body' to 'base body', destroying any between them. - update collision disable table for any pairs including 'add body'
- L233 _prototype_ `int32 CreateNewConstraint(UPhysicsAsset* PhysAsset, FName InConstraintName, UPhysicsConstraintTemplate* InConstraintSetup = NULL);` (scope `FPhysicsAssetUtils`) — Creates a new constraint @param	PhysAsset			The PhysicsAsset to create the constraint for @param	InConstraintName	Name of the constraint @param	InConstraintSetup	Optional constraint setup @return  Returns the index of the newly created constraint.
- L241 _prototype_ `void DestroyConstraint(UPhysicsAsset* PhysAsset, int32 ConstraintIndex);` (scope `FPhysicsAssetUtils`) — Destroys the specified constraint @param	PhysAsset			The PhysicsAsset for which the constraint should be destroyed @param	ConstraintIndex		The index of the constraint to destroy
- L250 _prototype_ `int32 CreateNewBody(UPhysicsAsset* const PhysAsset, const FName InBodyName, const FPhysAssetCreateParams& Params);` (scope `FPhysicsAssetUtils`) — Create a new BodySetup and default BodyInstance if there is not one for this body already. @param	PhysAsset			The PhysicsAsset to create the body for @param	InBodyName			Name of the new body @return	The Index of the newly created body.
- L258 _prototype_ `void DestroyBody(UPhysicsAsset* const PhysAsset, const int32 BodyIndex);` (scope `FPhysicsAssetUtils`) — Destroys the specified body @param	PhysAsset			The PhysicsAsset for which the body should be destroyed @param	BodyIndex			Index of the body to destroy
- L268 _prototype_ `void RecreateBody(UPhysicsAsset* const PhysAsset, const FName InBodyName, const FPhysAssetCreateParams& Params, const int32 BodyIndex);` (scope `FPhysicsAssetUtils`) — Initialize a new BodySetup at a specified index in the physics asset and create a default BodyInstance if there is not one for this body already. @param	PhysAsset			The PhysicsAsset to create the body for @param	InBodyName			Name of the new body @param	Params				Parameters used when configuring the body @param	BodyIndex			Index of the body to initialize in the Physics Asset
- L273 _prototype_ `bool CanCreateConstraints();` (scope `FPhysicsAssetUtils`) — Whether or not Constraints are allowed to be created (due to asset list filtering)
- L275 _prototype_ `UE_DEPRECATED(5.8, "SanitizeRestrictedContent is no longer used.") void Sanitize` (scope `FPhysicsAssetUtils`)
- L284 _prototype_ `template<typename RealType> FMatrix ComputeViewCovarianceMatrix(TArrayView<const UE::Math::TVector<RealType>, int> PointView);` (scope `FPhysicsAssetUtils`) — Compute a covariance matrix describing the distribution of points in the provided set @param PointView An array view of a vector type to calculate the covariance matrix for @return Calculated covariance matrix
- L285 _prototype_ `FMatrix ComputeCovarianceMatrix(const TArray<FVector3f>& Verts);` (scope `FPhysicsAssetUtils`)
- L296 _prototype_ `FVector ComputeEigenVector(const FMatrix& InMatrix);` (scope `FPhysicsAssetUtils`) — Compute the dominant eigenvector of a provided matrix @param InMatrix Matrix input @return Domininant eigenvector of InMatrix
