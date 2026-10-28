# Plugins / SkeletalMeshReduction

- module root: `Plugins/Experimental/SkeletalReduction/Source`
- headers: 8; symbols: 624
- symbol kinds: class=27, enum=4, enumerator=8, function=294, macro=1, member=100, namespace=10, prototype=95, struct=7, typedef=77, union=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AnimationBlueprintLibrary, ClothingSystemRuntimeCommon, EditorFramework, MeshBoneReduction
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, MaterialUtilities, MeshUtilities, PropertyEditor, QuadricMeshReduction, RHI, RawMesh, RenderCore, SkeletalMeshUtilitiesCommon, Slate, SlateCore, UnrealEd

### `Plugins/Experimental/SkeletalReduction/Source/Private/SkeletalMeshReductionSkinnedMesh.h` (Private)


#### class `SkeletalSimplifier::TSkinnedSkeletalMesh`  
`template <typename SimpVertexType> class TSkinnedSkeletalMesh`  
_L17-230_
- desc: Simple mesh class templated on vertex type that holds an index and vertex buffer. Has the ability to compact and remove unused vertices NB: here 'unused' means vertices that aren't referenced by the index buffer
- L21 _public typedef_ `typedef SimpVertexType VertexType;`
- L23 _public function_ `TSkinnedSkeletalMesh() : IndexBuffer(NULL), VertexBuffer(NULL), NumTris(0), NumVerts(0), TexCoordNum(0)`
- L31 _public function_ `~TSkinnedSkeletalMesh()`
- L39 _public function_ `TSkinnedSkeletalMesh(int32 NumTriangles, int32 NumVertices) : IndexBuffer(NULL), VertexBuffer(NULL), NumTris(0), NumVerts(0), TexCoordNum(0)` — Constructor allocates index and vertex buffer.
- L53 _public function_ `void Resize(int32 NumTriangles, int32 NumVertices)` — Resizes the mesh to new size. NB:  Deletes data already held in mesh.
- L68 _public function_ `void Empty()` — Resizes the mesh to size zero.
- L83 _public function_ `int32 NumIndices() const` — Size of index buffer
- L88 _public function_ `int32 NumVertices() const` — Size of vertex buffer
- L93 _public function_ `int32 TexCoordCount() const` — Number of texture coords on each vertex.
- L95 _public function_ `void SetTexCoordCount(int32 c)`
- L106 _public function_ `void Compact(TArray<int32>* VertexRemap = nullptr)` — Remove vertices that aren't referenced by the index buffer. Also rebuilds the index buffer to account for the removals. Optionally, VertexRemap will map the compact vert index to the original vert index
- L219 _public member_ `uint32* IndexBuffer;`
- L220 _public member_ `SimpVertexType* VertexBuffer;`
- L225 _private prototype_ `TSkinnedSkeletalMesh(const TSkinnedSkeletalMesh&);`
- L227 _private member_ `int32 NumTris;`
- L228 _private member_ `int32 NumVerts;`
- L229 _private member_ `int32 TexCoordNum;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace SkeletalSimplifier`
- L232 _typedef_ `typedef TSkinnedSkeletalMesh<SkeletalSimplifier::MeshVertType> FSkinnedSkeletalMesh;` (scope `SkeletalSimplifier`)

### `Plugins/Experimental/SkeletalReduction/Source/Private/SkeletalSimplifier.h` (Private)


#### class `SkeletalSimplifier::FSimplifierTerminatorBase`  
`class FSimplifierTerminatorBase`  
_L17-41_
- desc: Simple terminator class.  This could be expanded on to include an interrupter to allow the user to halt execution.
- L20 _public function_ `FSimplifierTerminatorBase(int32 MinTri, int32 MinVert, float MaxCost) : MaxFeatureCost(MaxCost) , MinTriNumToRetain(MinTri) , MinVertNumToRetain(MinVert)`
- L27 _public function_ `inline bool operator()(const int32 TriNum, const int32 VertNum, const float SqrError)` — return true if the simplifier should terminate.
- L37 _public member_ `float MaxFeatureCost;`
- L38 _public member_ `int32 MinTriNumToRetain;`
- L39 _public member_ `int32 MinVertNumToRetain;`

#### class `SkeletalSimplifier::FSimplifierTerminator`  
`class FSimplifierTerminator : public FSimplifierTerminatorBase`  
_L46-74_
- inherits: `FSimplifierTerminatorBase`
- desc: Termination criterion for  simplifier
- L49 _public function_ `FSimplifierTerminator(uint32 MinTri, uint32 MaxTri, uint32 MinVert, uint32 MaxVert, float MaxCost, float MaxDist) : FSimplifierTerminatorBase(MinTri, MinVert, MaxCost) , MaxTriNumToRetain(MaxTri) , MaxVertNumToRetain(MaxVert) , MaxDistance(MaxDist)`
- L57 _public function_ `inline bool operator()(const uint32 TriNum, const uint32 VertNum, const float SqrError)` — return true if the simplifier should terminate.
- L70 _public member_ `uint32 MaxTriNumToRetain;`
- L71 _public member_ `uint32 MaxVertNumToRetain;`
- L72 _public member_ `float MaxDistance;`

#### class `SkeletalSimplifier::UniformWeights`  
`class UniformWeights`  
_L79-100_
- desc: Class to allow a single weight value to be applied to all the sparse attributes.
- L82 _public function_ `UniformWeights() : Weight(0.)`
- L84 _public function_ `UniformWeights(double w) : Weight(w)`
- L87 _public function_ `UniformWeights(const UniformWeights& other) : Weight(other.Weight)`
- L89 _public function_ `double GetElement(int32) const`
- L91 _public function_ `UniformWeights& operator=(const UniformWeights& other)`
- L98 _private member_ `double Weight;`

#### class `SkeletalSimplifier::FMeshSimplifier`  
`class FMeshSimplifier`  
_L106-312_
- desc: The core simplifier.  This does all the work
- L108 _private typedef_ `typedef typename SimpVertType::TriIterator TriIterator;`
- L109 _private typedef_ `typedef Quadrics::TFaceQuadric<MeshVertType, UniformWeights> WedgeQuadricType;`
- L110 _private typedef_ `typedef TQuadricCache<WedgeQuadricType> QuadricCacheType;`
- L111 _private typedef_ `typedef typename MeshVertType::BasicAttrContainerType BasicAttrContainerType;`
- L115 _private typedef_ `typedef typename MeshVertType::AttrContainerType AttrContainerType;`
- L117 _private typedef_ `typedef TTuple<SimpVertType*, SimpVertType*, MeshVertType> EdgeUpdateTuple;`
- L118 _private typedef_ `typedef TArray<EdgeUpdateTuple, TInlineAllocator<16> > EdgeUpdateTupleArray;`
- L120 _private typedef_ `typedef TArray<SimpEdgeType*, TInlineAllocator<32> > EdgePtrArray;`
- L121 _private typedef_ `typedef TArray<SimpTriType*, TInlineAllocator<16> > TriPtrArray;`
- L122 _private typedef_ `typedef TArray<SimpVertType*, TInlineAllocator<16> > VertPtrArray;`
- L126 _public typedef_ `typedef typename BasicAttrContainerType::DenseVecDType DenseVecDType;`
- L127 _public typedef_ `typedef typename BasicAttrContainerType::WeightArrayType WeightArrayType;`
- L128 _public typedef_ `typedef typename WedgeQuadricType::SparseWeightContainerType SparseWeightContainerType;`
- L133 _public prototype_ `FMeshSimplifier(const MeshVertType* InSrcVerts, const uint32 InNumSrcVerts, const uint32* InSrcIndexes, const uint32 InNumSrcIndexes, const float CoAlignmentLimit, const float VolumeImportance, const bool bVolumePreservation, const bool bEnforceBoundaries, const bool bMergeCoincidentVertBones, const bool bUseLegacyAttrGradient);`
- L142 _public prototype_ `~FMeshSimplifier();`
- L148 _public prototype_ `void SetBoundaryConstraintWeight(const double Weight);` — Weight used to insure that when a boundary edge collapses, the resulting vertex wont be far from that edge.
- L155 _public prototype_ `void SetAttributeWeights(const DenseVecDType& Weights);` — Set Quadric weights for the standard attributes ( the attributes that are stored in TBasicVertexAttrs<NumTexCoords> ) The order of the weights corresponds to the order of the attributes : Normal (3 weights), Tangent (3 weights ), BiTangent (3 weights), Color (3 weights), TextureCoords( 2 * NumTexCoords weights).
- L160 _public prototype_ `void SetSparseAttributeWeights(const SparseWeightContainerType& SparseWeights);` — Set Quadric weights for sparse attributes
- L165 _public prototype_ `void SetBoundaryLocked();` — Lock mesh boundary edges to prevent simplification by using the vertex tag ESimpElementFlags::SIMP_LOCKED
- L170 _public prototype_ `void SetColorEdgeLocked(float Threshold = 1.e-3);` — Lock edges that connect different colors to prevent simplification by using the vertex tag ESimpElementFlags::SIMP_LOCKED
- L175 _public prototype_ `void SetBoxCornersLocked();` — Lock vertices at corners of very simple 8-vert boxes.
- L187 _public prototype_ `template <typename TerminationCriterionType> float SimplifyMesh(TerminationCriterionType TerminationCriterion);` — Simplify the mesh.  Termination of the simplification is controlled by the TiminationCriterion class The terminator must implement struct Terminator { inline bool operator()(const int32 TriNum, const float SqrError); };
- L192 _public function_ `int GetNumVerts() const` — The number of verts of the mesh once simplified  (or at any stage)
- L197 _public function_ `int GetNumTris() const` — The number of tris in the mesh once simplified (or at any stage)
- L202 _public function_ `float FractionNonManifoldEdges()` — The fraction of non-manifold edges (edges with more than 2 adjacent tris).
- L213 _public prototype_ `void OutputMesh(MeshVertType* Verts, uint32* Indexes, bool bWeldVtxColorAttrs = true, TArray<int32>* LockedVerts = NULL);` — Export a copy of the simplified mesh. @param Verts                 - pointer to an array to populate.  Should be least GetNumVerts() in size @param Indexes               - pointer to index buffer to populate.  Should be at least 3 * GetNumTris() in size @param  bWeldVtxColorAttrs   - Weld verts attributes (colors) that may have been artificially split by the reduction algorithm. note: this could be extended to the other attributes (e.g. normals, uvs ) @param LockedVerts           - optional pointer to array.  On return the array will hold the indices of any locked verts.
- L220 _protected prototype_ `void InitCosts();` — Populate the cost heap by evaluating the collapse cost of each edge. NB: must be called before simplification
- L223 _protected prototype_ `float CalculateNormalShift(const SimpTriType& tri, const SimpVertType* vertToUpdate, const FVector& newPos) const;` — returns the dot product between current face normal and the face normal after vertToUpdate has been moved to newPos
- L225 _protected prototype_ `void ComputeEdgeCollapseVerts(SimpEdgeType* edge, EdgeUpdateTupleArray& newVerts);`
- L226 _protected prototype_ `void ComputeEdgeCollapseVertsAndFixBones(SimpEdgeType* edge, EdgeUpdateTupleArray& newVerts);`
- L229 _protected prototype_ `double ComputeEdgeCollapseVertsAndCost(SimpEdgeType* edge, EdgeUpdateTupleArray& newVerts);`
- L230 _protected prototype_ `FVector ComputeEdgeCollapseVertsPos(SimpEdgeType* edge, EdgeUpdateTupleArray& newVerts, TArray< WedgeQuadricType, TInlineAllocator<16> >& quadrics, Quadrics::FEdgeQuadric& edgeQuadric);`
- L232 _protected prototype_ `void ComputeEdgeCollapseVertsAndQuadrics(SimpEdgeType* edge, EdgeUpdateTupleArray& newVerts, Quadrics::FEdgeQuadric& newEdgeQuadric, TArray< WedgeQuadricType, TInlineAllocator<16> >& newQuadrics);`
- L234 _protected prototype_ `double ComputeEdgeCollapseCost(SimpEdgeType* edge);`
- L237 _protected prototype_ `WedgeQuadricType GetWedgeQuadric(SimpVertType* v);` — Quadric based on attributes and position (see section 4 in Hoppe's "New Quadric Metric for Simplifying Meshes.")
- L241 _protected prototype_ `Quadrics::FEdgeQuadric GetEdgeQuadric(SimpVertType* v);` — Quadric based on sharp edges. (See section 5 in Hoppe's "New Quadric Metric for Simplifying Meshes.") This includes an edge quadric for every single-sided edge that shares this vert
- L243 _protected prototype_ `void DirtyTriQuadricCache(TriPtrArray& DirtyTri);`
- L244 _protected prototype_ `void DirtyVertAndEdgeQuadricsCache(VertPtrArray& DirtyVerts);`
- L248 _protected prototype_ `void UpdateEdgeCollapseCost(EdgePtrArray& DirtyEdges);`
- L250 _protected prototype_ `int32 CountDegenerates() const;` — Included for testing.
- L254 _protected prototype_ `void SnapToClosestSourceVertexColor(EdgeUpdateTuple& UpdateTuple);` — Snap the interpolated vertex color in the third tuple element to the closest of the other two
- L257 _protected prototype_ `const FLinearColor& SnapToClosestColor(const FLinearColor& AColor, const FLinearColor& BColor, const FLinearColor& SampleColor) const;` — Returns the closer (AColor or BColor) from the SampleColor
- L265 _protected member_ `DenseVecDType BasicAttrWeights;` — The weights for the standard attributes
- L268 _protected member_ `SparseWeightContainerType AdditionalAttrWeights;` — The weights for the bones
- L274 _protected member_ `uint32 DegreeLimit = 24;` — prevent high valence verts.
- L275 _protected member_ `double DegreePenalty = 100.0f;`
- L278 _protected member_ `double invalidPenalty = 1.e6;` — prevent edge folding
- L281 _protected member_ `double coAlignmentLimit = .0871557f;` — critical angle by which the normal of a triangle is allowed to changed during a collapse.
- L283 _protected member_ `double VolumeImportance;`
- L285 _protected member_ `bool bPreserveVolume;`
- L286 _protected member_ `bool bCheckBoneBoundaries;`
- L287 _protected member_ `bool bMergeBonesOnCoincidentVerts;`
- L288 _protected member_ `double BoundaryConstraintWeight = 256.;`
- L295 _protected member_ `bool bUseLegacyAttrGrad;` — forces the simplifier to use the old attribute interpolation gradient method.  Needed for backward compatibilty with certain cloth assets
- L299 _protected member_ `FBinaryHeap<double> CollapseCostHeap;` — Heap that maps edges to the cost of collapse
- L303 _protected member_ `QuadricCacheType QuadricCache;` — Manage the quadrics Linear arrays that map quadrics to vertices, faces and edges.
- L306 _protected member_ `FSimplifierMeshManager MeshManager;` — The mesh manager - holds a mesh that supports the topology queries we need and the collapse methods.
- L310 _private prototype_ `FMeshSimplifier();`
- L315 _function_ `FORCEINLINE void FMeshSimplifier::DirtyTriQuadricCache(TriPtrArray& DirtyTriArray)`
- L324 _function_ `FORCEINLINE void FMeshSimplifier::DirtyVertAndEdgeQuadricsCache(VertPtrArray& DirtyVertArray)`
- L336 _function_ `FORCEINLINE FMeshSimplifier::WedgeQuadricType FMeshSimplifier::GetWedgeQuadric(SimpVertType* v)`
- L350 _function_ `FORCEINLINE Quadrics::FEdgeQuadric FMeshSimplifier::GetEdgeQuadric(SimpVertType* v)`
- L365 _function_ `FORCEINLINE void FMeshSimplifier::ComputeEdgeCollapseVertsAndQuadrics(SimpEdgeType* edge, EdgeUpdateTupleArray& EdgeAndNewVertArray, Quadrics::FEdgeQuadric& newEdgeQuadric, TArray< WedgeQuadricType, TInlineAllocator<16> >& newWedgeQuadrics)`
- L391 _function_ `FORCEINLINE const FLinearColor& FMeshSimplifier::SnapToClosestColor(const FLinearColor& AColor, const FLinearColor& BColor, const FLinearColor& SampleColor) const`
- L402 _function_ `FORCEINLINE void FMeshSimplifier::SnapToClosestSourceVertexColor(EdgeUpdateTuple& UpdateTuple)`
- L418 _function_ `FORCEINLINE void FMeshSimplifier::UpdateEdgeCollapseCost(EdgePtrArray& DirtyEdges)`
- L444 _function_ `template< typename TerminationCriterionType> float FMeshSimplifier::SimplifyMesh(TerminationCriterionType TerminationCriterion)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace SkeletalSimplifier`
- L340 _function_ `` (scope `SkeletalSimplifier::FMeshSimplifier::GetWedgeQuadric`)
- L354 _function_ `` (scope `SkeletalSimplifier::FMeshSimplifier::GetEdgeQuadric`)

### `Plugins/Experimental/SkeletalReduction/Source/Private/SkeletalSimplifierLinearAlgebra.h` (Private)


#### class `SkeletalSimplifier::LinearAlgebra::ArrayBase`  
`template <int32 SIZE, typename DerivedType> class ArrayBase`  
_L21-116_
- desc: Base class used in fixed-length linear storage of double precision data
- L25 _public typedef_ `typedef double ScalarType;`
- L27 _public typedef_ `typedef ScalarType DataType;`
- L28 _public typedef_ `typedef ScalarType MyStorageType[SIZE];`
- L30 _public function_ `ArrayBase()`
- L35 _public function_ `void Reset()`
- L41 _public function_ `ScalarType& operator() (const int32 idx)` — Data access
- L48 _public function_ `const ScalarType& operator() (const int32 idx) const`
- L55 _public function_ `ScalarType& operator[] (const int32 idx)` — Direct access
- L56 _public function_ `const ScalarType& operator[] (const int32 idx) const`
- L58 _public function_ `DerivedType& operator=(const DerivedType& other)`
- L66 _public function_ `DerivedType& operator+= (const DerivedType& other)` — Vector addition / subtraction
- L72 _public function_ `DerivedType& operator-= (const DerivedType& other)`
- L78 _public function_ `DerivedType& operator*= (double Scalar)`
- L84 _public function_ `DerivedType operator+(const DerivedType& other) const`
- L92 _public function_ `DerivedType operator-(const DerivedType& other) const`
- L101 _public function_ `int32 Num() const` — The number of elements
- L103 _public function_ `ScalarType L2NormSqr() const`
- L115 _protected member_ `MyStorageType Data;`

#### class `SkeletalSimplifier::LinearAlgebra::Vec3d`  
`class Vec3d : public ArrayBase<3, Vec3d>`  
_L119-193_
- inherits: `ArrayBase<3,Vec3d>`
- L122 _public typedef_ `typedef ArrayBase<3, Vec3d> MyBase;`
- L127 _public function_ `Vec3d()` — Default Construct as zero vector.
- L133 _public function_ `Vec3d(double x, double y, double z)`
- L138 _public function_ `Vec3d(const MyBase& base) : MyBase(base)`
- L142 _public function_ `Vec3d(const FVector3f& fvec)`
- L147 _public function_ `Vec3d(const FVector3d& fvec)`
- L155 _public function_ `void Zero()` — Reset all the values in this vector to zero.
- L163 _public function_ `bool operator==(const Vec3d& other) const` — Strict equality check.
- L171 _public function_ `Vec3d operator*(double Scalar)` — Scale this vector
- L181 _public function_ `double LengthSqrd() const` — The square of the geometric length of the vector.
- L189 _public function_ `double DotProduct(const Vec3d& other) const` — DotProduct of this vector with another.

#### class `SkeletalSimplifier::LinearAlgebra::SymmetricMatrix`  
`class SymmetricMatrix : public ArrayBase<6, SymmetricMatrix>`  
_L244-419_
- inherits: `ArrayBase<6,SymmetricMatrix>`
- desc: Double precision 3x3 symmetric matrix
- L247 _public typedef_ `typedef ArrayBase<6, SymmetricMatrix> MyBase;`
- L248 _public typedef_ `typedef typename MyBase::ScalarType ScalarType;`
- L250 _public function_ `SymmetricMatrix()`
- L259 _public function_ `SymmetricMatrix(double a11, double a12, double a13, double a22, double a23, double a33)` — Constructor: takes the upper triangle part of the symmetric matrix
- L268 _public function_ `SymmetricMatrix(const MyBase& base) : MyBase(base)`
- L278 _public function_ `SymmetricMatrix::ScalarType operator()(int32 i, int32 j) const` — Accesses elements in the matrix using standard M(i,j) notation @param i - the row  in [0,3) @param j - the column in [0, 3)
- L290 _public function_ `SymmetricMatrix::ScalarType& operator()(int32 i, int32 j)` — Accesses elements in the matrix using standard M(i,j) notation @param i - the row  in [0,3) @param j - the column in [0, 3)
- L305 _public function_ `Vec3d operator* (const Vec3d& Vect) const` — Produce a new Vec3d that is the result of SymetricMatrix vector multiplication. NB: this does M*v  not v * M @param Vect  - three dimensional double precision vector @return  Matrix * Vector.
- L324 _public function_ `SymmetricMatrix operator* (const SymmetricMatrix& Other) const` — Produce a new Symetric matrix that is the result of SymetricMatrix times SymetricMatrix NB: ThisMatrix * Other @param Other  - 3x3 symetric matrix @return  ThisMatrix * Other
- L340 _public function_ `SymmetricMatrix operator*(const double Scalar) const` — Produce a new SymetricMatrix that is the result of SymetricMatrix times scalar NB: ThisMatrix * Scalar @param Scalar  - single scale. @return  ThisMatrix * Scalar
- L351 _public function_ `void Zero()` — Update this Matrix to all zero values.
- L359 _public function_ `void Identity()` — Update this Matrix to an identity matrix (1 on diagonal 0 off diagonal).
- L369 _public function_ `SymmetricMatrix::ScalarType Det() const` — Determinant of the matrix.   The matrix may be inverted if this is non-zero.
- L388 _public function_ `SymmetricMatrix Inverse(bool& Success, double Threshold = 1.e-8) const` — Construct the inverse of this matrix. @param  Success   - On return this will be true if the inverse is valid @param  Threshold - Compared against the determinant of the matrix.  If abs(Det()) < Threshold the inverse is said to have failed @return The inverse of 'this' matrix.
- L411 _public function_ `SymmetricMatrix Inverse() const` — Construct the inverse of this matrix. NB: If abs( Det() ) of the matrix is less than 1.e-8 the result will be invalid. @return The inverse of 'this' matrix
- L418 _private member_ `static const int32 Mapping[9];`

#### class `SkeletalSimplifier::LinearAlgebra::DMatrix`  
`class DMatrix : public ArrayBase<9, DMatrix>`  
_L451-628_
- inherits: `ArrayBase<9,DMatrix>`
- desc: Double precision 3x3 matrix class
- L454 _public typedef_ `typedef ArrayBase<9, DMatrix> MyBase;`
- L455 _public typedef_ `typedef typename MyBase::ScalarType ScalarType;`
- L457 _public function_ `DMatrix()`
- L464 _public function_ `DMatrix(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)` — Constructor: Element by element.
- L476 _public function_ `DMatrix(const Vec3d& Row0, const Vec3d& Row1, const Vec3d& Row2)` — Constructor: Row based.
- L491 _public function_ `DMatrix::ScalarType operator()(int32 i, int32 j) const` — Accesses elements in the matrix using standard M(i,j) notation @param i - the row  in [0,3) @param j - the column in [0, 3)
- L497 _public function_ `DMatrix::ScalarType& operator()(int32 i, int32 j)`
- L511 _public function_ `Vec3d operator* (const Vec3d& Vect) const` — Produce a new Vec3d that is the result of Matrix vector multiplication. NB: this does M*v  not v * M @param Vect  - three dimensional double precision vector @return  Matrix * Vect.
- L530 _public function_ `DMatrix operator*(const DMatrix& B) const` — Produce a new 3x3 matrix that is the result of 3x3matrix  times 3x3matridx NB: ThisMatrix * Other @param Other  - 3x3 full matrix @return  ThisMatrix * Other
- L545 _public function_ `void Identity()` — Update this Matrix to an identity matrix (1 on diagonal 0 off diagonal).
- L555 _public function_ `DMatrix::ScalarType Det() const` — Determinant of the matrix.   The matrix may be inverted if this is non-zero.
- L574 _public function_ `DMatrix Inverse(bool& sucess, double threshold = 1.e-8) const` — Construct the inverse of this matrix. @param  Success   - On return this will be true if the inverse is valid @param  Threshold - Compared against the determinant of the matrix.  If abs(Det()) < Threshold the inverse is said to have failed @return The inverse of 'this' matrix.
- L598 _public function_ `DMatrix Inverse() const` — Construct the inverse of this matrix. NB: If abs( Det() ) of the matrix is less than 1.e-8 the result will be invalid. @return The inverse of 'this' matrix
- L607 _public function_ `Vec3d RowSum() const` — Sum of the rows - return as a vector
- L619 _public function_ `Vec3d ColSum() const` — Sum of the column - return as a vector

#### class `SkeletalSimplifier::LinearAlgebra::SparseVecD`  
`class SparseVecD`  
_L670-855_
- desc: Double Precision Sparse Vector: - used with the SparseBMatrix in Quadric calculation
- L674 _public typedef_ `typedef TMap< int32, double> SparseContainer;`
- L677 _public function_ `SparseVecD()`
- L680 _public function_ `SparseVecD(const SparseVecD& Other)`
- L688 _public function_ `bool bIsEmpty() const` — @return true if is the vector is empty
- L696 _public function_ `void Reset()` — Empty this sparse vector
- L704 _public function_ `void SetElement(const int32 j, double Value)` — Add element V[j] = Value
- L713 _public function_ `double GetElement(const int32 j) const` — Return Element V[j].  By default V[j] will be zero if nothing has been stored there.
- L723 _public function_ `SparseVecD& operator=(const SparseVecD& Other)` — Update the values of this vector to match Other
- L732 _public function_ `SparseVecD& operator+=(const SparseVecD& other)` — Add another SparseVector to this one.
- L745 _public function_ `SparseVecD& operator*= (const double Scalar)` — Scale this sparse vector with the scalar
- L758 _public function_ `bool operator==(const SparseVecD& Other) const` — Equality test against another SparseVector
- L777 _public function_ `bool operator!=(const SparseVecD& Other) const`
- L785 _public function_ `double DotProduct(const SparseVecD& Other) const` — Compute Sum(  V[i] * Other[i] )
- L799 _public function_ `double L2NormSqr() const` — Compute the dot product of this sparse vector with itself : Sum(  V[i] * V[i] )
- L815 _public function_ `double SumValues() const` — Sum the non-zero elements in a sparse array. Sum(  V[i]  )
- L830 _public function_ `SparseVecD::SparseContainer& GetData()` — Access to the underlying sparse data structure.
- L831 _public function_ `const SparseVecD::SparseContainer& GetData() const`
- L837 _public function_ `int32 Num() const` — @return the number of non-empty elements in the sparse array.
- L841 _protected function_ `void AddToElement(const int32 j, const double Value)`
- L854 _protected member_ `SparseContainer SparseData;`

#### class `SkeletalSimplifier::LinearAlgebra::TDenseArrayWrapper`  
`template <typename DataType> class TDenseArrayWrapper`  
_L863-948_
- desc: Special double precision vector wrapper. NB:  This does not own the memory. It just grants nicer semantics to some existing memory
- L866 _public typedef_ `typedef DataType Type;`
- L868 _public function_ `TDenseArrayWrapper(DataType* data, int32 size)`
- L874 _public function_ `TDenseArrayWrapper(TArrayView<DataType> InArrayView)`
- L880 _public function_ `int32 Num() const`
- L882 _public function_ `void SetElement(const int32 j, const DataType Value)`
- L883 _public function_ `DataType GetElement(const int32 j) const`
- L885 _public function_ `DataType& operator[] (const int32 j)`
- L886 _public function_ `DataType operator[] (const int32 j) const`
- L887 _public function_ `DataType& operator() (const int32 j)`
- L888 _public function_ `DataType operator() (const int32 j) const`
- L890 _public function_ `TDenseArrayWrapper& operator*= (double Scalar)`
- L897 _public function_ `TDenseArrayWrapper& operator+= (const TDenseArrayWrapper& Other)`
- L908 _public function_ `DataType DotProduct(const TDenseArrayWrapper& Other) const`
- L921 _public function_ `double L2NormSqr() const`
- L926 _public function_ `bool operator==(const TDenseArrayWrapper& Other) const`
- L939 _public function_ `bool operator!=(const TDenseArrayWrapper& Other) const`
- L946 _private member_ `DataType * Data;` — Note: this object doesn't own the data!
- L947 _private member_ `int32 Size;`

#### class `SkeletalSimplifier::LinearAlgebra::TDenseVecD`  
`template <int32 SIZE> class TDenseVecD : public ArrayBase<SIZE, TDenseVecD<SIZE>>`  
_L957-1011_
- inherits: `ArrayBase<SIZE,TDenseVecD<SIZE>>`
- desc: Fixed length double precision vector class with dot product and get/set element methods that are consistent with the sparse double precision vector class SparseVecD
- L961 _public typedef_ `typedef ArrayBase<SIZE, TDenseVecD> MyBase;`
- L962 _public typedef_ `typedef typename MyBase::ScalarType ScalarType;`
- L969 _public function_ `TDenseVecD()`
- L977 _public function_ `TDenseVecD(const TDenseArrayWrapper<float>& FloatArrayWrapper)` — Construct from Wrapped  Array.
- L988 _public prototype_ `TDenseVecD(const TDenseVecD& Other) = default;`
- L989 _public prototype_ `TDenseVecD& operator=(const TDenseVecD& Other) = default;`
- L991 _public function_ `void SetElement(const int32 j, const double Value)`
- L992 _public function_ `ScalarType GetElement(const int32 j) const`
- L1000 _public function_ `double DotProduct(const TDenseVecD& Other) const` — Sum of element-by-element product. Dot Product = Sum( this[i] * Other[i] ) @return sum of element-by-element multiplicaiton.

#### enum `SkeletalSimplifier::LinearAlgebra::TDenseVecD::(anonymous)`  
`enum`  
_L967-967_

#### class `SkeletalSimplifier::LinearAlgebra::SparseBMatrix`  
`class SparseBMatrix`  
_L1021-1137_
- desc: Sparse Matrix class with 3 rows and an unknown number of columns. 3 x M matrix. The sparsity is encoded as the existence / non-existence of a column. a non-filled column is assumed to be all zeros.
- L1025 _public typedef_ `typedef TMap< int32, Vec3d > SparseContainer;`
- L1028 _public function_ `void Reset()` — empty the matrix
- L1039 _public function_ `void SetColumn(const int32 j, const Vec3d& ColumnVec)` — Add a new, or over-write and existing column. @param j          - column index. @param ColumnVec  - the new values for the column.
- L1048 _public function_ `Vec3d GetColumn(const int32 j) const` — Copy of data stored in the column. @param j          - column index.
- L1058 _public function_ `double operator()(int32 i, int32 j) const` — Look up data in matrix with Row, Column address.
- L1068 _public function_ `SparseBMatrix& operator+=(const SparseBMatrix& Other)` — Add another SparseBMatrix to this one Element by element addition. @param Other - the matrix to be added.
- L1083 _public function_ `Vec3d operator*(const SparseVecD& SparseVec) const` — Matrix multiplication with a sparse vector. SparseMatrix * SparseVector  [3 x m] . [m] = 3 vector. @param SparseVec - vector
- L1099 _public function_ `SparseBMatrix& operator*= (const double Scalar)` — Rescale this sparse matrix by *= each element. @param Scalar - Value to scale each element with.
- L1111 _public function_ `const SparseBMatrix::SparseContainer& GetData() const` — Const access to the underlying sparse data structure.
- L1122 _private function_ `void AddToColumn(const int32 j, const Vec3d& ColumnVec)`
- L1135 _private member_ `SparseContainer SparseData;`

#### class `SkeletalSimplifier::LinearAlgebra::TDenseBMatrix`  
`template<int32 NUMCOLS> class TDenseBMatrix`  
_L1148-1264_
- desc: A Dense alternative to the SparseBMatrix NUMCOLS is the number of columns This double precision matrix has 3 rows and NUMCOLS columns.
- L1152 _public typedef_ `typedef Vec3d MyStorageType[NUMCOLS];`
- L1155 _public function_ `TDenseBMatrix()`
- L1161 _public function_ `TDenseBMatrix(const TDenseBMatrix& Other)`
- L1169 _public function_ `void Reset()` — Zero all enteries.
- L1179 _public function_ `void SetColumn(const int32 j, const Vec3d& ColumnVec)` — Replace data in the j-th column with the given column vector @param j - column index @param ColumnVec - the column to insert.
- L1187 _public function_ `Vec3d& GetColumn(const int32 j)` — Access to the j-th column.
- L1193 _public function_ `const Vec3d& GetColumn(const int32 j) const`
- L1202 _public function_ `double operator()(const int32 i, const int32 j) const` — Row-Column access to data in the matrix
- L1209 _public function_ `double& operator()(const int32 i, const int32 j)` — Row-Column access to data in the matrix
- L1217 _public function_ `int32 NumCols() const` — Number of columns that define this matrix.  Known at compile time.
- L1222 _public function_ `TDenseBMatrix& operator=(const TDenseBMatrix& Other)` — Assignment
- L1231 _public function_ `TDenseBMatrix& operator+= (const TDenseBMatrix& Other)` — Element-by-element addition with another matrix.
- L1241 _public function_ `Vec3d operator*(const TDenseVecD<NUMCOLS>& DenseVec) const` — Matrix multiplication with a correctly sized dense vector. DenseBMatrix * DenseVector  [3 x m] . [m] = 3 vector.
- L1253 _public function_ `TDenseBMatrix& operator*= (const double Scalar)` — Rescale this 3xNUMCOLS matrix by *= each element. @param Scalar - Value to scale each element with.
- L1262 _private member_ `MyStorageType Data;` — Array of column vectors defines the matrix

#### class `SkeletalSimplifier::LinearAlgebra::InverseGradientProjection`  
`class InverseGradientProjection`  
_L1419-1524_
- desc: This class generates the interpolation coefficients vector (Vec3d) g  and distance (double) d defined over the face of a triangle.  It does this in one of two ways.  The first constructs a local basis relative to the triangle.  This is preferable. The second is the so-called "legacy method" it uses position vectors for the vertices and will fall back to a crude approximation when the triangle lies on a plane that intersects the origin. * The actual system solved is: <pa | g> + d = s0 <pb | g> + d = s1 <pc | g> + d = s2 <FaceNormal | g> = 0 But we re-write this as <(pc - pa) | g >  = s2 - s0 <(pb - pa) | g >  = s1 - s0 < FaceNormal | g > = 0 d = s0 - <pa | g> The first three equations can be solved for "g", in terms of s, and the result can be used to compute d. The BasisMatrix is defined in terms of the three corners of triangle {pa, pb, pc} and the normal corresponding normal 'FaceNormal' BasisMatrix = ( pc_0 - pa_0 , pc_1 - pa_1 , pc_2 - pa_2 ) ( pb_0 - pa_0 , pb_1 - pa_1 , pb_2 - pa_2) ( FaceNormal_0, FaceNormal_1, FaceNormal_2 ) The rows corresponds to vectors along two sides of the triangle and the face normal Solving for "g" is simply solving BasisMatrix * g = vec(s2-s0, s1-s0, 0) or g  = Invserse(BasisMatrix) * vec(s2-s0, s1-s0, 0) the Inverse(BasisMatrix) is cached as the CoBasisMatrix The computation is broken up do allow for reuse with multiple sets of per-vertex data. Alternately when using the legacy method The Position Matrix is defined in terms of the three corn
- L1422 _public function_ `InverseGradientProjection(const Vec3d& Pos0, const Vec3d& Pos1, const Vec3d& Pos2, const Vec3d& FaceNormal, bool bUseLegacyGradientMethod) : bLegacyGradientMethod(bUseLegacyGradientMethod)`
- L1474 _public function_ `bool IsValid() const`
- L1482 _public function_ `double ComputeGradient(const Vec3d& PerVertexData, Vec3d& OutGradient) const` — @param  PerVertexData - Vertex Data at vertex {0, 1, 2} stored as a Vec3d @param  OutGradient   - on return, the gradient terms @return  Distance
- L1514 _private member_ `bool bIsValid;` — Indicates if the inversions incurred a divide by very-small-number.
- L1516 _private member_ `bool bLegacyGradientMethod = false;`
- L1519 _private member_ `DMatrix CoBasisMatrix;` — used by the standard method
- L1520 _private member_ `Vec3d Origin;` — corresponds to P0
- L1523 _private member_ `Vec3d MInv1;` — used by the legacy version only

#### struct `SkeletalSimplifier::LinearAlgebra::TVectorToMatrixTrait`  
`template <typename SparseVecDOrDenseVecD> struct TVectorToMatrixTrait`  
_L1527-1530_
- L1529 _public typedef_ `typedef SparseBMatrix BMatrixType;`
- L1541 _public typedef_ `typedef TDenseBMatrix<3> BMatrixType;`

#### struct `SkeletalSimplifier::LinearAlgebra::TVectorToMatrixTrait`  
`template <> struct TVectorToMatrixTrait<SparseVecD>`  
_L1533-1536_
- L1529 _public typedef_ `typedef SparseBMatrix BMatrixType;`
- L1541 _public typedef_ `typedef TDenseBMatrix<3> BMatrixType;`

#### struct `SkeletalSimplifier::LinearAlgebra::TVectorToMatrixTrait`  
`template<> struct TVectorToMatrixTrait<TDenseVecD<3>>`  
_L1539-1542_
- L1529 _public typedef_ `typedef SparseBMatrix BMatrixType;`
- L1541 _public typedef_ `typedef TDenseBMatrix<3> BMatrixType;`

#### struct `SkeletalSimplifier::LinearAlgebra::DenseIterMask`  
`template <int32 SIZE> struct DenseIterMask`  
_L1602-1607_
- L1604 _public function_ `int32 operator[](int32 i) const`
- L1606 _public function_ `int32 Num() const`

#### class `SkeletalSimplifier::LinearAlgebra::FAABBox2d`  
`class FAABBox2d`  
_L1620-1747_
- desc: Axis aligned 2d bounding box class used for tracking and clamping UVs.
- L1623 _public typedef_ `typedef float MyStorageType[4];`
- L1626 _public function_ `FAABBox2d()` — default initialized puts the bbox in an invalid state
- L1631 _public function_ `FAABBox2d(const FAABBox2d& Other)`
- L1640 _public function_ `void Reset()` — Set to a default empty state
- L1652 _public function_ `void Union(const FAABBox2d& Other)` — Expand this BBox to include the Other @param Other - another Axis Aligned bbox
- L1664 _public function_ `FAABBox2d& operator+=(const FAABBox2d& Other)` — The += operator is defined to be a union of bboxes.
- L1670 _public function_ `FAABBox2d& operator=(const FAABBox2d& Other)`
- L1682 _public function_ `bool IsValid() const` — @return true only if the min is not greater than the max
- L1691 _public function_ `void ExpandToInclude(const FVector2f& Point)` — Expand this bbox to include the provied point @param Point - point to be included in this Axis aligned bounding box
- L1705 _public function_ `void ClampPoint(FVector2f& Point) const` — Clamp values that exceed the bbox @Param Point - point to be clamped by this bbox
- L1716 _public function_ `void ClampPoint(FVector2f& Point, const float Fraction) const` — Clamp values that exceed the bbox @Param Point - point to be clamped by a padded version of this bbox @Param Fraction - fraction of box width to use for padding.
- L1729 _public function_ `FVector2f Min() const` — Min corner the bbox
- L1738 _public function_ `FVector2f Max() const` — Max corner the bbox
- L1745 _private member_ `MyStorageType MinMax;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace SkeletalSimplifier`
- L14 _namespace_ `namespace LinearAlgebra` (scope `SkeletalSimplifier`)
- L196 _function_ `static Vec3d operator*(double Scalar, Vec3d B)` (scope `SkeletalSimplifier::LinearAlgebra`)
- L210 _function_ `static bool NormalizeVector(Vec3d& Vect)` (scope `SkeletalSimplifier::LinearAlgebra`) — Rescale the vector to have magnitude one. NB: this can fail if the magnitude of the source vector is less than 1.e-8 @return true is the normalization succeeds
- L233 _function_ `static Vec3d CrossProduct(const Vec3d& tmpA, const Vec3d& tmpB)` (scope `SkeletalSimplifier::LinearAlgebra`) — Computes the Cross Product of two vectors Cross = tmpA X tmpB @param tmpA - the first vector @param tmpB - the second vector @return the result
- L429 _function_ `static SymmetricMatrix operator*(double Scalar, SymmetricMatrix Mat)` (scope `SkeletalSimplifier::LinearAlgebra`) — Produce a new SymetricMatrix that is the result of SymetricMatrix times scalar NB: ThisMatrix * Scalar @param Scalar  - single scale. @return  ThisMatrix * Scalar
- L442 _function_ `static Vec3d operator*(const Vec3d& LhsVector, const SymmetricMatrix& SymMatrix)` (scope `SkeletalSimplifier::LinearAlgebra`) — vector * Matrix. NB: This is really vector^Transpose * Matrix and results in a vector^Transpose.   But since we don't distinguish the transpose space, we treat both as vectors. @param LhsVector - vector @param SymMatrix - SymmetricMatrix,
- L633 _function_ `static Vec3d operator*(const Vec3d& VecTranspose, const DMatrix& M)` (scope `SkeletalSimplifier::LinearAlgebra`) — left multiply matrix by vector.    This is really Transpose(vector) * Matrix
- L645 _function_ `static DMatrix operator*(const DMatrix& Dm, const SymmetricMatrix& Sm)` (scope `SkeletalSimplifier::LinearAlgebra`) — Dense3x3 matrix time SymmetricMatrix = results in dense3x3 matrix
- L658 _function_ `static DMatrix operator*(const SymmetricMatrix& Sm, const DMatrix& Dm)` (scope `SkeletalSimplifier::LinearAlgebra`) — SymmetricMatrix X Dense3x3 matrix  = results in dense3x3 matrix
- L967 _enumerator_ `enum { Size = SIZE }; TDenseVecD() { Reset(); } /**` (scope `SkeletalSimplifier::LinearAlgebra::TDenseVecD::__anon326e9ba70103`)
- L1270 _function_ `template <int32 SIZE> TDenseVecD<SIZE> operator*(const Vec3d VecTranspose, const TDenseBMatrix<SIZE>& DenseB)` (scope `SkeletalSimplifier::LinearAlgebra`) — Transpose(Vector) * Matrix.
- L1286 _function_ `inline SparseVecD operator* (const Vec3d VecTranpose, const SparseBMatrix& SparseB)` (scope `SkeletalSimplifier::LinearAlgebra`) — Transpose(Vector) * Matrix.
- L1304 _function_ `static SymmetricMatrix ScaledProjectionOperator(const Vec3d& Vect)` (scope `SkeletalSimplifier::LinearAlgebra`) — Construct the outer product Va . Transpose(Va) This will result in a operator that will give the scaled projection of a vector onto Va.  (scaled by va.lenghtsqrd)
- L1317 _function_ `template<int32 SIZE> SymmetricMatrix OuterProductOperator(const TDenseBMatrix<SIZE>& DenseB)` (scope `SkeletalSimplifier::LinearAlgebra`) — Returns B. Transpose(B)
- L1331 _function_ `inline SymmetricMatrix OuterProductOperator(const SparseBMatrix& SparseB)` (scope `SkeletalSimplifier::LinearAlgebra`) — Returns B. Transpose(B)
- L1553 _function_ `static TArray<int32> GetIterationMask(const SparseVecD& Attr0, const SparseVecD& Attr1, const SparseVecD& Attr2)` (scope `SkeletalSimplifier::LinearAlgebra`) — Create a mask that holds the union of the sparse topology. The resulting array will @return  Array that holds the sparse topology.
- L1610 _function_ `template <int32 SIZE> DenseIterMask<SIZE> GetIterationMask(const TDenseVecD<SIZE>& Attr0, const TDenseVecD<SIZE>& Attr1, const TDenseVecD<SIZE>& Attr2)` (scope `SkeletalSimplifier::LinearAlgebra`)

### `Plugins/Experimental/SkeletalReduction/Source/Private/SkeletalSimplifierMeshManager.h` (Private)


#### class `SkeletalSimplifier::FSimplifierMeshManager`  
`class FSimplifierMeshManager`  
_L55-550_
- desc: Mesh type internal to the simplifier.  This is really an attempt to tease the mesh management code out of the simplifier.  Not intended to be a general mesh. This mesh may be updated by collapsing edges, altering attributes.  In doing so, the mesh does not delete any vertices, just marks them as removed. All attributes are stored in the vertices. Vertices are assumed to be split, so that multiple vertices may coincide at the same physical location. Likewise with edges. As an organizational principle, coincident vertices are held in pointer-based link lists, as are edges. These are often referenced as vertex groups or edge groups, but in practice a group can be infered from a single member.
- L58 _public typedef_ `typedef TArray< SimpEdgeType*, TInlineAllocator<32> > EdgePtrArray;`
- L59 _public typedef_ `typedef TArray< SimpTriType*, TInlineAllocator<16> > TriPtrArray;`
- L60 _public typedef_ `typedef TArray< SimpVertType*, TInlineAllocator<16> > VertPtrArray;`
- L61 _public typedef_ `typedef TArray< uint32, TInlineAllocator<8> > IdxArray;`
- L63 _public typedef_ `typedef typename SimpVertType::TriIterator TriIterator;`
- L65 _public typedef_ `typedef TSharedPtr<FSimplifierMeshManager> Ptr;`
- L67 _public prototype_ `FSimplifierMeshManager(const MeshVertType* InSrcVerts, const uint32 InNumSrcVerts, const uint32* InSrcIndexes, const uint32 InNumSrcIndexes, const bool bMergeBonesIfSamePos);`
- L70 _public prototype_ `~FSimplifierMeshManager() = default;`
- L74 _public prototype_ `void OutputMesh(MeshVertType* verts, uint32* indexes, TArray<int32>* LockedVerts = NULL);` — Extract the currently valid verts / indices from this object.  If LockedVerts != NULL then the indices of verts that had locked state will be passed out too.
- L79 _public prototype_ `void FlagBoundary(const ESimpElementFlags Flag);` — Apply the flag to all verts on the edge of the mesh.
- L82 _public prototype_ `void FlagBoxCorners(const ESimpElementFlags Flag);` — Apply a flag to all verts that are identified as being at the corner of a box.
- L85 _public prototype_ `void FlagEdges(const TFunction<bool(const SimpVertType*, const SimpVertType*)> IsDifferent, const ESimpElementFlags Flag);` — Apply flag to edges when the IsDifferent(AVert, BVert) == true
- L88 _public prototype_ `void VisitEdges(TFunctionRef<void(SimpVertType*, SimpVertType*, int32)> EdgeVisitor);` — Visit each edge group, and call EdgeVisitor(VertexA, VertexB, NumAdjacentFaces)
- L91 _public function_ `void UpdateVertexAttributes(SimpVertType& Vertex, const MeshVertType& AttributeVert)` — Change the attributes on a given simplifier vert.
- L98 _public prototype_ `void UpdateVertexAttriuteIDs(EdgePtrArray& CoincidentEdges);` — copy the element IDs for the correct attributes from v1 to v0 in preparation for collapse.
- L101 _public prototype_ `int32 CountDegeneratesTris() const;` — Count the number of triangles with zero area.
- L104 _public prototype_ `int32 CountDegenerateEdges() const;` — Count the number of edges with zero length.
- L107 _public prototype_ `float FractionNonManifoldEdges(bool bLockNonManifoldEdges = false);` — Fraction (0 to 1) of edge-groups with more than two adjacent tris, optionally lock these edges
- L110 _public function_ `static uint32 HashPoint(const FVector& p)` — Hash location
- L123 _public function_ `int32 TotalNumEdges() const`
- L129 _public function_ `bool IsInvalid(const SimpEdgeType* EdgePtr) const` — Return true if either vertex has no associated faces.
- L135 _public function_ `bool IsCoincident(const SimpVertType* AVertPtr, const SimpVertType* BVertPtr, bool bCompairBones = true) const` — Return true if the AVert and BVert have the same vertex locations.  Optionally require the same bones.
- L141 _public function_ `bool IsRemoved(const SimpEdgeType* EdgePtr) const`
- L146 _public function_ `SimpEdgeType* GetEdgePtr(const uint32 Idx)`
- L152 _public function_ `const SimpEdgeType* GetEdgePtr(const uint32 Idx) const`
- L158 _public function_ `SimpVertType* GetVertPtr(const uint32 Idx)`
- L164 _public function_ `const SimpVertType* GetVertPtr(const uint32 Idx) const`
- L172 _public function_ `uint32 GetVertIndex(const SimpVertType* VertPtr) const` — Convert pointer to array index
- L178 _public function_ `uint32 GetTriIndex(const SimpTriType* TriPtr) const` — Convert pointer to array index
- L184 _public function_ `uint32 GetEdgeIndex(const SimpEdgeType* EdgePtr) const` — Convert pointer to array index
- L194 _public function_ `void MergeGroups(SimpVertType* A, SimpVertType* B)`
- L225 _public function_ `template < ESimpElementFlags FlagToPropagate > void PropagateFlag(SimpVertType& MemberOfGroup)` — If a member of the group has the given flag, propagate that flag to each member
- L244 _public function_ `void GetEdgesInGroup(const SimpEdgeType& seedEdge, EdgePtrArray& InOutEdgeGroup) const` — Gather all the edges implicitly in the edge group defined by the seed edge
- L254 _public function_ `void GetVertsInGroup(const SimpVertType& seedVert, VertPtrArray& InOutVertGroup) const` — Gather all the verts in the group defined by this vert.
- L266 _public function_ `template < ESimpElementFlags FlagValue > void PruneVerts(SimpVertType& seedVert)` — Remove any verts tagged as with FlagValue (e.g. SIMP_REMOVED)  NB: this may unlink the seed vert!
- L292 _public function_ `uint32 GetDegree(const SimpVertType& Vert) const` — Count the adjacent tris to all the split verts that make up this vert.
- L308 _public prototype_ `void GetAdjacentTopology(const SimpVertType* VertPtr, TriPtrArray& AdjacentTris, VertPtrArray& AdjacentVerts, EdgePtrArray& AdjacentEdges);` — Gather all the tri, verts, and edges that will be affected by moving this vert.
- L311 _public prototype_ `void GetAdjacentTopology(const SimpEdgeType& GroupedEdge, TriPtrArray& AdjacentTris, VertPtrArray& AdjacentVerts, EdgePtrArray& AdjacentEdges);`
- L318 _public prototype_ `void GetCoincidentVertGroups(VertPtrArray& CoincidentVertGroups);`
- L331 _public prototype_ `void WeldNonSplitBasicAttributes(EVtxElementWeld WeldType);`
- L334 _public prototype_ `void RebuildEdgeLinkLists(EdgePtrArray& CandidateEdgePtrArray);` — note, this shares a lot of code with GroupEdges - they should be unified..
- L340 _public prototype_ `int32 RemoveEdgeIfInvalid(EdgePtrArray& CandidateEdges, IdxArray& RemovedEdgeIdxArray);` — On return CandidateEdges[i] = NULL for any removed edge and the Edge Idx of all the removed edges are stored in the RemovedEdgeIdArray
- L344 _public prototype_ `uint32 RemoveEdge(const SimpVertType* VertAPtr, const SimpVertType* VertBPtr);` — @return the idx of this edge it if is currently in the VertIdHashMap IF the edge has already been deleted, or doesn't exist, return numeric_limits<uint32>::max()
- L347 _public prototype_ `uint32 RemoveEdge(SimpEdgeType& Edge);` — @return the idx of the edge after removal to allow the caller to clean up any associated data structures (e.g. heap)
- L352 _public prototype_ `uint32 ReplaceVertInEdge(const SimpVertType* VertAPtr, const SimpVertType* VertBPtr, SimpVertType* VertAprimePtr);` — Change the edge VertA-VertB to  VertAprime-VertB @return the Idx of the edge that was changed.
- L357 _public prototype_ `int32 RemoveIfDegenerate(TriPtrArray& CandidateTrisPtrArray);` — @return the number of removed tris. Flags tris as SIMP_REMOVED and removes them from the verts that referenced them
- L359 _public prototype_ `int32 RemoveDegenerateTris();`
- L369 _public prototype_ `bool CollapseEdge(SimpEdgeType* EdgePtr, IdxArray& RemovedEdgeIdxArray);` — Collapse the edge by moving edge-v0 to edge->v1. and record the idx of the edges that are deleted by this action. Note, collapsing a single edge may result in additional edges being removed.  A triangle that shares this edge will be reduced to a single edge e.g. collapse edge 0-1 in the triangle 0-1,  1-2, 2-0 will result in the single edge 1-2 @returns true if the edge collapsed, false if the edge wasn't a true edge.
- L372 _public function_ `uint32 RemoveTri(SimpTriType& Tri)` — Mark a tri as removed, and remove it from vertex adj lists.
- L387 _public function_ `uint32 ReplaceTriVertex(SimpTriType& Tri, SimpVertType& OldVert, SimpVertType& NewVert)` — On @return the index of the tri
- L397 _public prototype_ `int32 RemoveIfDegenerate(VertPtrArray& CandidateVertPtrArray);` — @return the number of removed verts Flags the removed verts link elements as SIMP_REMOVED and removes verts from vert link lists.
- L399 _public prototype_ `int32 RemoveDegenerateVerts();`
- L404 _public prototype_ `int32 RemoveIfDegenerate(EdgePtrArray& CandidateEdges, IdxArray& RemovedEdgeIdxArray);` — On return CandidateEdges[i] = NULL for any removed edge and the Edge Idx of all the removed edges are stored in the RemovedEdgeIdArray
- L408 _public function_ `bool IsLockedGroup(const EdgePtrArray& EdgeGroup) const` — @return true if any of the edges in this edge group is locked.
- L426 _public function_ `bool HasLockedVerts(const SimpEdgeType* Edge) const` — @return true if the either of the verts are locked
- L434 _public function_ `SimpEdgeType* FindEdge(const SimpVertType* u, const SimpVertType* v)` — Find the edge associated with these verts.  Will return NULL if no such edge exists.
- L443 _public member_ `bool bWeldBonesIfSamePos = true;` — Weld Bones if the vertices have the same location
- L446 _public member_ `const int32 NumSrcVerts = 0;` — The number of verts and tris in the initial mesh.
- L447 _public member_ `const int32 NumSrcTris = 0;`
- L449 _public member_ `int32 ReducedNumVerts;`
- L450 _public member_ `int32 ReducedNumTris;`
- L454 _public member_ `TArray<SimpVertType> VertArray;` — Note after these arrays are constructed, they should never be resized. code holds pointers to array elements.
- L455 _public member_ `TArray<SimpTriType> TriArray;`
- L461 _public member_ `FHashTable EdgeVertIdHashMap;`
- L465 _public member_ `TArray< SimpEdgeType > EdgeArray;` — Array of edges Note - this array shouldn't be resized after the mesh is constructed
- L471 _private prototype_ `void GroupVerts(TArray<SimpVertType>& Verts);`
- L472 _private prototype_ `void SetAttributeIDS(TArray<SimpVertType>& Verts);`
- L473 _private prototype_ `void MakeEdges(const TArray<SimpVertType>& Verts, const int32 NumTris, TArray<SimpEdgeType>& Edges);`
- L474 _private prototype_ `void AppendConnectedEdges(const SimpVertType* Vert, TArray<SimpEdgeType>& Edges);`
- L475 _private prototype_ `void GroupEdges(TArray< SimpEdgeType >& Edges);`
- L480 _private function_ `uint32 HashEdge(const SimpVertType* u, const SimpVertType* v) const` — Generate a hash based on the Idxs of the verts. Note this is independent of the order of the verts.
- L488 _private function_ `uint32 HashEdgePosition(const SimpEdgeType& Edge)`
- L493 _private function_ `TPair<uint32, uint32> GetEdgeHashPair(const SimpVertType* u, const SimpVertType* v) const`

#### union `SkeletalSimplifier::FSimplifierMeshManager::HashPoint::(anonymous)`  
`union`  
_L112-112_

#### enum `SkeletalSimplifier::FSimplifierMeshManager::EVtxElementWeld`  
`enum class EVtxElementWeld`  
_L323-330_
- desc: Weld non-split basic attributes on coincident vertices. This should be called prior to output. Note: The simplifier will split a vertex into multiple attribute vertices (with a full copy of all attributes) if only one attribute is split, this insures that the non-split attributes share the same value.
- L325 _public enumerator_ `Normal`
- L326 _public enumerator_ `Tangent`
- L327 _public enumerator_ `BiTangent`
- L328 _public enumerator_ `Color`
- L329 _public enumerator_ `UV`

#### struct `SkeletalSimplifier::FSimplifierMeshManager::FVertAndID`  
`struct FVertAndID`  
_L512-523_
- desc: struct used in sorting and merging coincident verts.
- L514 _public member_ `int32 ID;`
- L515 _public member_ `SimpVertType* SrcVert;`
- L517 _public function_ `FVertAndID()`
- L518 _public function_ `FVertAndID(SimpVertType* SV, int32 InID)`

#### struct `SkeletalSimplifier::FSimplifierMeshManager::FNonManifoldEdgeCounter`  
`struct FNonManifoldEdgeCounter`  
_L526-548_
- desc: struct used with VistEdges when counting nonmanifold edges.
- L528 _public member_ `int32 EdgeCount;`
- L529 _public member_ `int32 NumNonManifoldEdges;`
- L530 _public member_ `bool bLockNonManifoldEdges;`
- L532 _public function_ `void operator()(SimpVertType* v0, SimpVertType* v1, int32 AdjFaceCount)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace SkeletalSimplifier`
- L16 _function_ `template <typename ValueType, typename AllocatorType> void ResizeArray(TArray<ValueType, AllocatorType>& Array, const int32 Size)` (scope `SkeletalSimplifier`)
- L26 _typedef_ `typedef VertexTypes::TBasicVertexAttrs<MAX_TEXCOORDS> BasicAttrArray;` (scope `SkeletalSimplifier`)
- L27 _typedef_ `typedef VertexTypes::DynamicVertexAttrs SparseAttrArray;` (scope `SkeletalSimplifier`)
- L28 _typedef_ `typedef VertexTypes::BoneSparseVertexAttrs BoneAttrArray;` (scope `SkeletalSimplifier`)
- L30 _typedef_ `typedef VertexTypes::TSkeletalSimpVert<BasicAttrArray, SparseAttrArray, BoneAttrArray> MeshVertType;` (scope `SkeletalSimplifier`)
- L33 _typedef_ `typedef TSimpVert< MeshVertType > SimpVertType;` (scope `SkeletalSimplifier`) — Specialized Link-Lists for Verts and Edges
- L34 _typedef_ `typedef TSimpEdge< MeshVertType > SimpEdgeType;` (scope `SkeletalSimplifier`)
- L37 _typedef_ `typedef TSimpTri< MeshVertType > SimpTriType;` (scope `SkeletalSimplifier`) — Definition of a triangle.
- L112 _member_ `union { float f; uint32 i; } x;` (scope `SkeletalSimplifier::FSimplifierMeshManager::HashPoint::__anon0f341206010a`)
- L112 _member_ `union { float f; uint32 i; } x;` (scope `SkeletalSimplifier::FSimplifierMeshManager::HashPoint::__anon0f341206010a`)
- L113 _member_ `union { float f; uint32 i; } y;` (scope `SkeletalSimplifier::FSimplifierMeshManager::HashPoint::__anon0f341206020a`)
- L113 _member_ `union { float f; uint32 i; } y;` (scope `SkeletalSimplifier::FSimplifierMeshManager::HashPoint::__anon0f341206020a`)
- L114 _member_ `union { float f; uint32 i; } z;` (scope `SkeletalSimplifier::FSimplifierMeshManager::HashPoint::__anon0f341206030a`)
- L114 _member_ `union { float f; uint32 i; } z;` (scope `SkeletalSimplifier::FSimplifierMeshManager::HashPoint::__anon0f341206030a`)

### `Plugins/Experimental/SkeletalReduction/Source/Private/SkeletalSimplifierQuadricCache.h` (Private)


#### class `SkeletalSimplifier::TQuadricCache`  
`template <typename WedgeQuadricType> class TQuadricCache`  
_L15-124_
- desc: Cache to manage quadrics for the quadric mesh reduction.
- L18 _public typedef_ `typedef Quadrics::FEdgeQuadric EdgeQuadricType;`
- L20 _public function_ `TQuadricCache()`
- L28 _public function_ `void RegisterMesh(const FSimplifierMeshManager& Mesh)` — Associate the cache with the simplifier mesh This must be done before the cache can be used. @param Mesh  The FSimplifierMesh that this cache will be associated with
- L44 _public prototype_ `template <typename TriQuadricFatoryType> WedgeQuadricType GetWedgeQuadric(SimpVertType* v, const TriQuadricFatoryType& TriQuadricFactory);` — Get the Quadric. If the quadric for the requested SimplifierVert is out of date (dirty) then use the supplied TriQuadricFactor functor to compute a new quadric (and add it to the cache) QuadricType  TriQuadricFactor(SimpTriType& Tri); @param v                  The vert @param TriQuadricFactor   Method to compute new quadric from a triangle
- L58 _public prototype_ `template <typename EdgeQuadricFatoryType> EdgeQuadricType GetEdgeQuadric(SimpVertType* v, const EdgeQuadricFatoryType& EdgeQuadricFatory);` — Get the Edge Quadric. If the edge quadric for the requested SimplifierVert is out of date (dirty) then use the supplied EdgeQuadricFatory functor to compute a new quadric (and add it to the cache) FQuadric  EdgeQuadricFatory(v->GetPos(), vert->GetPos(), face->GetNormal()); @param v                  The vert @param EdgeQuadricFatory   Method to compute new quadric from a triangle
- L64 _public prototype_ `void DirtyVertQuadric(const SimpVertType* v);` — Mark the associated vertex quadric as dirty in the cache.
- L65 _public prototype_ `void DirtyVertQuadric(const uint32 VertIdx);`
- L70 _public prototype_ `void DirtyTriQuadric(const SimpTriType* tri);` — Mark the associated triangle quadric as dirty in the cache.
- L71 _public prototype_ `void DirtyTriQuadric(const uint32 TridIdx);`
- L76 _public prototype_ `void DirtyEdgeQuadric(const SimpVertType* v);` — Mark the associated edge quadric as dirty in the cache.
- L77 _public prototype_ `void DirtyEdgeQuadric(const uint32 VertIdx);`
- L81 _private prototype_ `uint32 GetVertIndex(const SimpVertType* vert) const;`
- L83 _private prototype_ `uint32 GetTriIndex(const SimpTriType* tri) const;`
- L93 _private prototype_ `void RegisterCache(const TArray<SimpVertType>& VertArray, const TArray<SimpTriType>& TriArray);` — Associate the cache with the simplifier vert and triangle arrays. This must be done before the cache can be used. @param VertArray   Array of verts in the source mesh @param TriArray    Array of Tris in the source mesh
- L102 _private prototype_ `void AllocateCacheArrays(const int32 NumVerts, const int32 NumTris);` — Allocate the member arrays with the size required This must be done before the cache can be used. @param NumVerts    Number of Verts in the source mesh @param NumTris     Number of tris in the source mesh
- L107 _private prototype_ `TQuadricCache(const TQuadricCache& other);`
- L111 _private member_ `TBitArray<> VertQuadricsValid;`
- L112 _private member_ `TArray< WedgeQuadricType > VertQuadrics;`
- L114 _private member_ `TBitArray<> TriQuadricsValid;`
- L115 _private member_ `TArray< WedgeQuadricType > TriQuadrics;`
- L117 _private member_ `TBitArray<> EdgeQuadricsValid;`
- L118 _private member_ `TArray< EdgeQuadricType > EdgeQuadrics;`
- L122 _private member_ `const SimpVertType* sVerts = NULL;`
- L123 _private member_ `const SimpTriType* sTris = NULL;`
- L133 _function_ `template <typename WedgeQuadricType > void TQuadricCache< WedgeQuadricType >::AllocateCacheArrays(const int32 NumSVerts, const int32 NumSTris)`
- L148 _function_ `template <typename WedgeQuadricType> void TQuadricCache< WedgeQuadricType>::RegisterCache(const TArray<SimpVertType>& VertArray, const TArray<SimpTriType>& TriArray )`
- L164 _function_ `template <typename WedgeQuadricType> template <typename TriQuadricFatoryType> WedgeQuadricType TQuadricCache< WedgeQuadricType>::GetWedgeQuadric(SimpVertType* v, const TriQuadricFatoryType& TriQuadricFactory)`
- L210 _function_ `template <typename WedgeQuadricType> template <typename EdgeQuadricFatoryType> Quadrics::FEdgeQuadric TQuadricCache< WedgeQuadricType>::GetEdgeQuadric(SimpVertType* v, const EdgeQuadricFatoryType& EdgeQuadricFatory)`
- L269 _function_ `template <typename WedgeQuadricType> FORCEINLINE void TQuadricCache< WedgeQuadricType>::DirtyVertQuadric(const uint32 VertIdx)`
- L275 _function_ `template <typename WedgeQuadricType> FORCEINLINE void TQuadricCache< WedgeQuadricType>::DirtyVertQuadric(const SimpVertType* v)`
- L281 _function_ `template <typename WedgeQuadricType> FORCEINLINE void TQuadricCache< WedgeQuadricType>::DirtyTriQuadric(const uint32 TriIdx)`
- L287 _function_ `template <typename WedgeQuadricType> FORCEINLINE void TQuadricCache< WedgeQuadricType>::DirtyTriQuadric(const SimpTriType* tri)`
- L293 _function_ `template <typename WedgeQuadricType> FORCEINLINE void TQuadricCache< WedgeQuadricType>::DirtyEdgeQuadric(const uint32 VertIdx)`
- L299 _function_ `template <typename WedgeQuadricType> FORCEINLINE void TQuadricCache< WedgeQuadricType>::DirtyEdgeQuadric(const SimpVertType* v)`
- L305 _function_ `template <typename WedgeQuadricType> FORCEINLINE uint32 TQuadricCache< WedgeQuadricType>::GetVertIndex(const SimpVertType* vert) const`
- L312 _function_ `template <typename WedgeQuadricType> FORCEINLINE uint32 TQuadricCache< WedgeQuadricType>::GetTriIndex(const SimpTriType* tri) const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace SkeletalSimplifier`

### `Plugins/Experimental/SkeletalReduction/Source/Private/SkeletalSimplifierQuadrics.h` (Private)


#### class `SkeletalSimplifier::Quadrics::FEdgeQuadric`  
`class FEdgeQuadric`  
_L19-69_
- L23 _public function_ `FEdgeQuadric()`
- L26 _public prototype_ `FEdgeQuadric(const Vec3d& Vert0Pos, const Vec3d& Vert1Pos, const Vec3d& FaceNormal, const double EdgeWeight);`
- L28 _public prototype_ `FEdgeQuadric(const FEdgeQuadric&) = default;`
- L29 _public prototype_ `FEdgeQuadric& operator=(const FEdgeQuadric&) = default;`
- L31 _public prototype_ `double Evaluate(const Vec3d& Pos) const;`
- L34 _public prototype_ `FEdgeQuadric& operator+=(const FEdgeQuadric& Other);`
- L36 _public function_ `void Zero()`
- L57 _private member_ `SymmetricMatrix CMatrix;` — quadric matrix
- L60 _private member_ `Vec3d D0Vector;` — Quadratic vector
- L63 _private member_ `double CScalar = 0.;` — Quadric scalar
- L468 _function_ `inline FEdgeQuadric::FEdgeQuadric(const Vec3d& Vert0Pos, const Vec3d& Vert1Pos, const Vec3d& FaceNormal, const double EdgeWeight)`
- L532 _function_ `inline double FEdgeQuadric::Evaluate(const Vec3d& Pos) const`
- L541 _function_ `inline FEdgeQuadric& FEdgeQuadric::operator+=(const FEdgeQuadric& Other)`

#### class `SkeletalSimplifier::Quadrics::TQuadricBase`  
`template <typename BasicAttrContainerType, typename AdditionalAttrContainerType> class TQuadricBase`  
_L74-148_
- desc: Base class for the more general Quadric that includes two arrays of attributes. The first array is dense, and the second array is optionally sparse.
- L78 _public typedef_ `typedef typename BasicAttrContainerType::DenseBMatrixType B1MatrixType;`
- L79 _public typedef_ `typedef typename TVectorToMatrixTrait<AdditionalAttrContainerType>::BMatrixType B2MatrixType;`
- L80 _public typedef_ `typedef Vec3d D0VectorType;`
- L81 _public typedef_ `typedef typename BasicAttrContainerType::DenseVecDType D1VectorType;`
- L82 _public typedef_ `typedef AdditionalAttrContainerType D2VectorType;`
- L85 _public function_ `TQuadricBase()`
- L88 _public function_ `TQuadricBase(const TQuadricBase& Other) : CMatrix(Other.CMatrix), B1Matrix(Other.B1Matrix), B2Matrix(Other.B2Matrix), Gamma(Other.Gamma), D0Vector(Other.D0Vector), D1Vector(Other.D1Vector), D2Vector(Other.D2Vector), CScalar(Other.CScalar), VolDistConstraint(Other.VolDistConstraint), VolGradConstraint(Other.VolGradConstraint), UVBBox(Other.UVBBox)`
- L103 _public prototype_ `TQuadricBase& operator+=(const TQuadricBase& Other);`
- L105 _public prototype_ `TQuadricBase& operator=(const TQuadricBase& Other);`
- L112 _public prototype_ `double EvaluateQaudric(const D0VectorType& Pos, const D1VectorType& S1, const D2VectorType& S2) const;` — The state vector is broken into three parts:  State = {Pos, S1, S2} This returns double = < State, Quadic_Matrix * State> + 2 <State, Quadric_Vector> + Quadric_Scalar
- L130 _protected member_ `SymmetricMatrix CMatrix;` — quadric matrix
- L131 _protected member_ `B1MatrixType B1Matrix;` — 3xN  - BasicAttr Gradients
- L132 _protected member_ `B2MatrixType B2Matrix;` — 3xM  - (sparse) AddionalAttr Gradients
- L133 _protected member_ `double Gamma = 0.;` — diagonal identity in quadric matrix
- L135 _protected member_ `D0VectorType D0Vector;` — quadric vector
- L136 _protected member_ `D1VectorType D1Vector;` — N
- L137 _protected member_ `D2VectorType D2Vector;` — M (sparse)
- L140 _protected member_ `double CScalar = 0.;` — quadric scalar
- L143 _protected member_ `double VolDistConstraint = 0.;` — volume constraint
- L144 _protected member_ `Vec3d VolGradConstraint;`
- L147 _protected member_ `FAABBox2d UVBBox;` — used to clamp 1st UV
- L384 _function_ `template <typename BasicType, typename AddType> inline double TQuadricBase<BasicType, AddType>::EvaluateQaudric(const D0VectorType& Pos, const D1VectorType& S1, const D2VectorType& S2) const`
- L418 _function_ `template <typename BasicType, typename AddType> inline TQuadricBase<BasicType, AddType>& TQuadricBase<BasicType, AddType>::operator+=(const TQuadricBase<BasicType, AddType>& Other)`
- L442 _function_ `template <typename BasicType, typename AddType> inline TQuadricBase<BasicType, AddType>& TQuadricBase<BasicType, AddType>::operator=(const TQuadricBase<BasicType, AddType>& Other)`

#### class `SkeletalSimplifier::Quadrics::TFaceQuadric`  
`template <typename SimpVertexType_, typename SparseWeightArrayType_> class TFaceQuadric : public TQuadricBase<typename SimpVertexType_::BasicAttrContainerType, typename SimpVertexType_::AttrContainerType>`  
_L154-278_
- inherits: `TQuadricBase<typenameSimpVertexType_::BasicAttrContainerType,typenameSimpVertexType_::AttrContainerType>`
- desc: Wedge type Quadric that contains two arrays of attributes. The first is dense, and the second may be sparse.
- L157 _public typedef_ `typedef TQuadricBase<typename SimpVertexType_::BasicAttrContainerType, typename SimpVertexType_::AttrContainerType> MyBase;`
- L159 _public typedef_ `typedef SimpVertexType_ SimpVertexType;`
- L160 _public typedef_ `typedef typename SimpVertexType::DenseAttrAccessor DenseAttrAccessor;`
- L161 _public typedef_ `typedef typename SimpVertexType::AttrContainerType AttrContainerType;`
- L162 _public typedef_ `typedef typename SimpVertexType::BasicAttrContainerType BasicAttrContainerType;`
- L164 _public typedef_ `typedef SparseWeightArrayType_ SparseWeightContainerType;`
- L166 _public typedef_ `typedef typename MyBase::B1MatrixType B1MatrixType;`
- L167 _public typedef_ `typedef typename MyBase::B2MatrixType B2MatrixType;`
- L168 _public typedef_ `typedef typename MyBase::D0VectorType D0VectorType;`
- L169 _public typedef_ `typedef typename MyBase::D1VectorType D1VectorType;`
- L170 _public typedef_ `typedef typename MyBase::D2VectorType D2VectorType;`
- L193 _public prototype_ `TFaceQuadric(const SimpVertexType& TriVert0, const SimpVertexType& TriVert1, const SimpVertexType& TriVert2, const D1VectorType& BasicWeights, const SparseWeightContainerType& AdditionalWeights, const bool bUseLegacyAttrGrad);` — @param TriVert0  - The three verts that define the triangle face. @param TriVert1  - @param TriVert2  - NB: These have to be some form of TSkeletalSimpVerts @param BasicWeights       - The weights to be applied to the BasicAttributes @param AdditionalWeights  - The weights to be applied to the AdditionalAttributes
- L201 _public prototype_ `TFaceQuadric() = default;`
- L202 _public prototype_ `TFaceQuadric(const TFaceQuadric& Other) = default;`
- L203 _public prototype_ `TFaceQuadric& operator=(const TFaceQuadric& Other) = default;`
- L209 _public prototype_ `double Evaluate(const SimpVertexType& Vert, const D1VectorType& BasicWeights, const SparseWeightContainerType& AdditionalWeights) const;` — Returns the quadric evaluation at this point  (vTr . A . v  + 2 bTr. v + c)  where A = quadric matrix, b = DVector, c = CScalar with bra-ket  <v|A v>  + 2 <b | v> + c
- L218 _public prototype_ `void CalcAttributes(SimpVertexType& Vert, const D1VectorType& BasicWeights, const SparseWeightArrayType_& AdditionalWeights) const;` — @param Vert - Update Vert.BasicAttributes and Vert.AdditionalAttributes to the values interpolated at Vert.Position. NB: assumes Vert.Position is already defined @param BasicWeights       - The weights to be applied to the BasicAttributes @param AdditionalWeights  - The weights to be applied to the AdditionalAttributes
- L220 _public function_ `TFaceQuadric& operator+=(const TFaceQuadric& Other)`
- L226 _public function_ `double TotalArea() const`
- L249 _private prototype_ `template <typename VectorType, typename MatrixType, typename WeightsArrayType> bool EncodeAttrGradient(const InverseGradientProjection& GradientTool, const VectorType& Vert0Attrs, const VectorType& Vert1Attrs, const VectorType& Vert2Attrs, const WeightsArrayType& Weights, MatrixType& GradientMatrix, VectorType& DistanceVector);` — -- Private: Used in the constructor -- Computes the Gradient coefficient for each attribute index and stores them in the ResultMatrix.  The resulting "distances" are stored in the result vector @param GradientTool  - Tool used to solve for the interpolating gradient and distances    (position0^t , 1)  ( g_i[0] )  = (vert0Attr[i]) (position1^t , 1)  ( g_i[1] )    (vert1Attr[i]) (position2^t,  1)  ( g_i[2] )    (vert2Attr[i]) (faceNormal^t, 0)  (  d_i )      (     0      ) @param Vert0Attrs - Attribute containers for each vertex in the triangle @param Vert1Attrs @param Vert2Attrs @param Weights    - Weights to scale the attributes with. @param GradientMatrix  - Matrix with columns that are the "-gradient"  (-g_i) of attributes @param DistanceVector  - The "-distances"  (-d_i) for each attribute. @return 'false' if the gradient encoding failed and the Gradient Matrix is empty.  In either event, the Distance Vector holds useful stuff.
- L262 _private prototype_ `void WeightByArea(double Area);` — -- Private: Used in the constructor -- Weight the quadric values by an area.
- L272 _private prototype_ `static void ComputeAttrs(const double Area, const B1MatrixType& GradientMatrix, const D1VectorType& DistVector, const Vec3d& Pos, const D1VectorType& Weights, DenseAttrAccessor& Attrs);`
- L273 _private prototype_ `static void ComputeAttrs(const double Area, const SparseBMatrix& GradientMatrix, const SparseVecD& DistVector, const Vec3d& Pos, const SparseWeightContainerType& Weights, SparseVecD& Attrs);`
- L275 _private prototype_ `static void SumOuterProducts(const B1MatrixType& GradientArray, const D1VectorType& DistArray, SymmetricMatrix& OuterProductSum, Vec3d& DistGradientSum);`
- L276 _private prototype_ `static void SumOuterProducts(const SparseBMatrix& GradientArray, const SparseVecD& DistArray, SymmetricMatrix& OuterProductSum, Vec3d& DistGradientSum);`
- L553 _function_ `template <typename SimpVertexType, typename SparseWeightArrayType> TFaceQuadric<SimpVertexType, SparseWeightArrayType>::TFaceQuadric(const SimpVertexType& TriVert0, const SimpVertexType& TriVert1, const SimpVertexType& TriVert2, const D1VectorType& BasicWeights, const SparseWeightContainerType& AdditionalWeights, const bool bUseLegacyAttrGrad)`
- L674 _function_ `template <typename SimpVertexType, typename SparseWeightArrayType> template <typename VectorType, typename MatrixType, typename WeightsArrayType> bool TFaceQuadric<SimpVertexType, SparseWeightArrayType>::EncodeAttrGradient( const InverseGradientProjection& GradientTool, const VectorType& Vert0Attrs, const VectorType& Vert1Attrs, const VectorType& Vert2Attrs, const WeightsArrayType& Weights, MatrixType& GradientMatrix, VectorType& DistanceVector)`
- L760 _function_ `template <typename SimpVertexType, typename SparseWeightArrayType> void TFaceQuadric<SimpVertexType, SparseWeightArrayType>::WeightByArea(double Area)`
- L779 _function_ `template <typename SimpVertexType, typename SparseWeightArrayType> inline void TFaceQuadric<SimpVertexType, SparseWeightArrayType>::ComputeAttrs(const double Area, const B1MatrixType& GradientMatrix, const D1VectorType& DistVector, const Vec3d& Pos, const D1VectorType& Weights, DenseAttrAccessor& Attrs)`
- L799 _function_ `template <typename SimpVertexType, typename SparseWeightArrayType> inline void TFaceQuadric<SimpVertexType, SparseWeightArrayType>::ComputeAttrs(const double Area, const SparseBMatrix& GradientMatrix, const SparseVecD& DistVector, const Vec3d& Pos, const SparseWeightContainerType& Weights, SparseVecD& Attrs)`
- L819 _function_ `template <typename SimpVertexType, typename SparseWeightArrayType> inline void TFaceQuadric<SimpVertexType, SparseWeightArrayType>::CalcAttributes(SimpVertexType& Vert, const D1VectorType& BasicWeights, const SparseWeightArrayType& AdditionalWeights) const`
- L842 _function_ `template <typename SimpVertexType, typename SparseWeightArrayType> inline double TFaceQuadric<SimpVertexType, SparseWeightArrayType>::Evaluate(const SimpVertexType& Vert, const D1VectorType& BasicWeights, const SparseWeightArrayType& AdditionalWeights) const`
- L880 _function_ `template <typename SimpVertexType, typename SparseWeightArrayType> inline void TFaceQuadric<SimpVertexType, SparseWeightArrayType>::SumOuterProducts(const B1MatrixType& GradientArray, const D1VectorType& DistArray, SymmetricMatrix& OuterProductSum, Vec3d& DistGradientSum)`
- L899 _function_ `template <typename SimpVertexType, typename SparseWeightArrayType> inline void TFaceQuadric<SimpVertexType, SparseWeightArrayType>::SumOuterProducts(const SparseBMatrix& GradientArray, const SparseVecD& DistArray, SymmetricMatrix& OuterProductSum, Vec3d& DistGradientSum)`

#### class `SkeletalSimplifier::Quadrics::TQuadricOptimizer`  
`template <typename FaceQuadricType> class TQuadricOptimizer : public TQuadricBase<typename FaceQuadricType::BasicAttrContainerType, typename FaceQuadricType::AttrContainerType>`  
_L285-333_
- inherits: `TQuadricBase<typenameFaceQuadricType::BasicAttrContainerType,typenameFaceQuadricType::AttrContainerType>`
- L288 _public typedef_ `typedef typename FaceQuadricType::SimpVertexType SimpVertexType;`
- L289 _public typedef_ `typedef typename FaceQuadricType::AttrContainerType AttrContainerType;`
- L290 _public typedef_ `typedef typename FaceQuadricType::BasicAttrContainerType BaseAttrContainerType;`
- L291 _public typedef_ `typedef TQuadricBase<BaseAttrContainerType, AttrContainerType> MyBase;`
- L292 _public typedef_ `typedef FaceQuadricType FFaceQuadric;`
- L306 _public function_ `TQuadricOptimizer() : MyBase()`
- L310 _public function_ `void AddFaceQuadric(const FFaceQuadric& FaceQuadric)`
- L315 _public function_ `void AddEdgeQuadric(const FEdgeQuadric& EdgeQuadric)`
- L330 _public prototype_ `bool Optimize(Vec3d& OptimalPosition, const bool bPreserveVolume, const double VolumeImportance) const;` — @param OptimalPosition  - Result of optimizing the quadric @param bPreserveVolume  - Controls the use of the volume conservation fixup. @param VolumeImportance - Artificial scalar between 0, 1 that scales the amount of conservation fixup actually used. the value 0 corresponds to no fixup, and 1 to full fixup
- L918 _function_ `template <typename FaceQuadricType> inline bool TQuadricOptimizer<FaceQuadricType>::Optimize(Vec3d& OutPosition, const bool bPreserveVolume, const double VolumeImportance) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace SkeletalSimplifier`
- L10 _namespace_ `namespace Quadrics` (scope `SkeletalSimplifier`)
- L341 _function_ `static void InitializeBMatrix(const TArray<int32>& IterMask, SparseBMatrix& Matrix)` (scope `SkeletalSimplifier::Quadrics`)
- L353 _function_ `template <int32 SIZE> static void InitializeBMatrix(const DenseIterMask<SIZE>& IterMask, TDenseBMatrix<SIZE>& Matrix)` (scope `SkeletalSimplifier::Quadrics`)
- L360 _function_ `static void InitializeBVector(const TArray<int32>& IterMask, SparseVecD& Vec)` (scope `SkeletalSimplifier::Quadrics`)
- L373 _function_ `template <int32 SIZE> static void InitializeBVector(const DenseIterMask<SIZE>& IterMask, TDenseVecD<SIZE>& Vec)` (scope `SkeletalSimplifier::Quadrics`)

### `Plugins/Experimental/SkeletalReduction/Source/Private/SkeletalSimplifierVertex.h` (Private)


#### class `SkeletalSimplifier::VertexTypes::TBasicVertexAttrs`  
`template <int32 NumTexCoords> class TBasicVertexAttrs`  
_L22-257_
- desc: Class that holds the dense vertex attributes. Normal, Tangent, BiTangent, Color, TextureCoords NB: this can be extended with additional float-type attributes.
- L28 _public typedef_ `typedef TDenseVecD<13 + 2 * NumTexCoords> DenseVecDType;` — NB: if you update the number of float-equivalent attributes, the '13' will have to be updated.
- L30 _public typedef_ `typedef DenseVecDType WeightArrayType;`
- L31 _public typedef_ `typedef TDenseBMatrix<13 + 2 * NumTexCoords> DenseBMatrixType;`
- L36 _public member_ `FVector3f Normal;` — 0, 1, 2
- L37 _public member_ `FVector3f Tangent;` — 3, 4, 5
- L38 _public member_ `FVector3f BiTangent;` — 6, 7, 8
- L39 _public member_ `FLinearColor Color;` — 9, 10, 11, 12
- L40 _public member_ `FVector2f TexCoords[NumTexCoords];` — 13, .. 13 + NumTexCoords * 2 - 1
- L138 _public member_ `FElementIDs ElementIDs;`
- L142 _public typedef_ `typedef TDenseArrayWrapper<float> DenseAttrAccessor;` — vector semantic wrapper for raw array
- L148 _public function_ `TBasicVertexAttrs() : Normal(ForceInitToZero), Tangent(ForceInitToZero), BiTangent(ForceInitToZero), Color(ForceInitToZero)` — default construct to zero values
- L163 _public function_ `TBasicVertexAttrs(const TBasicVertexAttrs& Other) : Normal(Other.Normal), Tangent(Other.Tangent), BiTangent(Other.BiTangent), Color(Other.Color), ElementIDs(Other.ElementIDs)` — copy construct
- L179 _public function_ `static int32 Size()` — Number of float equivalents.
- L184 _public function_ `DenseAttrAccessor AsDenseAttrAccessor()` — Get access to the data as a generic linear array of floats.
- L185 _public function_ `const DenseAttrAccessor AsDenseAttrAccessor() const`
- L190 _public function_ `TBasicVertexAttrs& operator=(const TBasicVertexAttrs& Other)` — Assignment operator.
- L208 _public function_ `void Correct()` — Method to insure that the attribute values are valid by correcting any invalid ones.
- L222 _public function_ `bool operator==(const TBasicVertexAttrs& Other)` — Strict equality test.
- L241 _public function_ `bool IsApproxEquals(const TBasicVertexAttrs& Other) const` — Approx equality test.

#### enum `SkeletalSimplifier::VertexTypes::TBasicVertexAttrs::(anonymous)`  
`enum`  
_L25-25_

#### struct `SkeletalSimplifier::VertexTypes::TBasicVertexAttrs::FElementIDs`  
`struct FElementIDs`  
_L45-136_
- desc: used to manage identity of split/non-split vertex attributes. note, could have external storage for the above attributes and just use these to point to those values.
- L47 _public member_ `int32 NormalID;`
- L48 _public member_ `int32 TangentID;`
- L49 _public member_ `int32 BiTangentID;`
- L50 _public member_ `int32 ColorID;`
- L51 _public member_ `int32 TexCoordsID[NumTexCoords];`
- L56 _public function_ `FElementIDs()` — construct with invalid ID values.
- L68 _public function_ `FElementIDs(const FElementIDs& other)`
- L81 _public function_ `FElementIDs operator-(const FElementIDs& other) const` — Subtract other ID struct from this one.
- L96 _public function_ `void MaskedCopy(const FElementIDs& IDMask, const FElementIDs& other)` — copy other ID if the mask value is zero
- L109 _public function_ `void MaskedCopy(const FElementIDs& IDMask, const FElementIDs& InverseIDMask, const FElementIDs& BIDs)` — copy IDs values over to this for elemenets where IDMask == 0 and InverseIDMask != 0

#### enum `SkeletalSimplifier::VertexTypes::TBasicVertexAttrs::FElementIDs::(anonymous)`  
`enum`  
_L53-53_

#### class `SkeletalSimplifier::VertexTypes::DynamicVertexAttrs`  
`class DynamicVertexAttrs : public SparseVecD`  
_L262-269_
- inherits: `SparseVecD`
- desc: Dynamic vertex attributes. Distinguished from the BoneSparseVertexAttrs. Based on SparseVecD, rather than using dense vector wrappers, because of requirements by the simplifier.
- L265 _public function_ `static void Correct()`

#### class `SkeletalSimplifier::VertexTypes::BoneSparseVertexAttrs`  
`class BoneSparseVertexAttrs : public SparseVecD`  
_L275-395_
- inherits: `SparseVecD`
- desc: Sparse attributes. Used to hold bone weights where the bone ID is the attribute key.
- L285 _public function_ `void Correct( int32 MaxBoneNumber = 8)` — Deletes smallest bones if currently more than MaxBoneNumber, and maintain the normalization of weight (all sum to 1). keeping the bones sorted internally by weight (largest to smallest).
- L320 _public function_ `void Normalize()` — Note: the norm here is the sum of weights (not L2 or L1 norm)
- L338 _public function_ `void DeleteSmallBones()` — Removes bones with very small weights. This may not be appropriate for all models.
- L351 _public function_ `void Empty()` — Remove all bones.
- L360 _public function_ `bool IsApproxEquals(const BoneSparseVertexAttrs& Other, double Tolerance = (double)KINDA_SMALL_NUMBER) const` — Compare two sparse arrays.  A small bone weight will be equivalent to no bone weight.

#### class `SkeletalSimplifier::VertexTypes::TSkeletalSimpVert`  
`template< typename BasicAttrContainerType_, typename AttrContainerType_ , typename BoneContainerType_> class TSkeletalSimpVert`  
_L406-625_
- L408 _private typedef_ `typedef TSkeletalSimpVert< BasicAttrContainerType_, AttrContainerType_, BoneContainerType_ > VertType;`
- L412 _public typedef_ `typedef BoneContainerType_ BoneContainer;`
- L413 _public typedef_ `typedef AttrContainerType_ AttrContainerType;`
- L414 _public typedef_ `typedef BasicAttrContainerType_ BasicAttrContainerType;`
- L415 _public typedef_ `typedef typename BasicAttrContainerType::DenseVecDType DenseVecDType;`
- L421 _public member_ `int32 ClosestSrcVertIndex;`
- L424 _public member_ `uint32 MaterialIndex;` — The Vertex Point
- L425 _public member_ `FVector3f Position;`
- L429 _public member_ `float SpecializedWeight;`
- L437 _public member_ `BasicAttrContainerType BasicAttributes;` — - Base Attributes: Normal, Tangent, BiTangent, Color, TexCoords: size = 13 + 2 * NumTexCoord
- L440 _public member_ `AttrContainerType AdditionalAttributes;` — - Additional Attributes : size not determined at compile time
- L443 _public member_ `BoneContainer SparseBones;` — - Sparse Bones : size not determined at compile time
- L447 _public typedef_ `typedef typename BasicAttrContainerType::DenseAttrAccessor DenseAttrAccessor;`
- L450 _public function_ `TSkeletalSimpVert() : ClosestSrcVertIndex(-1), MaterialIndex(0), Position(ForceInitToZero), SpecializedWeight(0.f), BasicAttributes(), AdditionalAttributes(), SparseBones()`
- L462 _public function_ `TSkeletalSimpVert(const TSkeletalSimpVert& Other) : ClosestSrcVertIndex(Other.ClosestSrcVertIndex), MaterialIndex(Other.MaterialIndex), Position(Other.Position), SpecializedWeight(Other.SpecializedWeight), BasicAttributes(Other.BasicAttributes), AdditionalAttributes(Other.AdditionalAttributes), SparseBones(Other.SparseBones)` — copy constructor
- L474 _public function_ `uint32 GetMaterialIndex() const`
- L475 _public function_ `FVector3f& GetPos()`
- L476 _public function_ `const FVector3f& GetPos() const`
- L481 _public function_ `static int32 NumBaseAttributes()`
- L482 _public function_ `DenseAttrAccessor GetBasicAttrAccessor()`
- L483 _public function_ `const DenseAttrAccessor GetBasicAttrAccessor() const`
- L487 _public function_ `AttrContainerType& GetAdditionalAttrContainer()`
- L488 _public function_ `const AttrContainerType& GetAdditionalAttrContainer() const`
- L493 _public function_ `BoneContainer& GetSparseBones()`
- L494 _public function_ `const BoneContainer& GetSparseBones() const`
- L499 _public function_ `void Correct()`
- L511 _public function_ `TSkeletalSimpVert& operator=(const TSkeletalSimpVert& Other)`
- L528 _public function_ `bool Equals(const VertType& Other) const` — Tests approximate equality using specialized comparison functions. NB: This functionality exists to help in welding verts prior to simplification, but is not used in the simplifier itself.
- L551 _public function_ `bool operator==(const VertType& Other) const`
- L567 _public function_ `VertType operator+(const VertType& Other) const`
- L585 _public function_ `VertType operator-(const VertType& Other) const`
- L603 _public function_ `VertType operator*(const float Scalar) const`
- L620 _public function_ `VertType operator/(const float Scalar) const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace SkeletalSimplifier`
- L11 _namespace_ `namespace VertexTypes` (scope `SkeletalSimplifier`)
- L25 _enumerator_ `enum { NumUVs = NumTexCoords}; typedef TDenseVecD<13 + 2 * NumTexCoords> DenseVecDType; typedef DenseVecDType WeightArrayType; typedef TDenseBMatrix<13 + 2 * NumTexCoords> DenseBMatrixType;` (scope `SkeletalSimplifier::VertexTypes::TBasicVertexAttrs::__anon540ac15c0103`)
- L53 _enumerator_ `enum { InvalidID = -1 }; FElementIDs() { NormalID = InvalidID; TangentID = InvalidID; BiTangentID = InvalidID;` (scope `SkeletalSimplifier::VertexTypes::TBasicVertexAttrs::FElementIDs::__anon540ac15c0203`)
- L279 _macro_ `#define SmallBoneSize 1.e-12`
- L297 _function_ `SparseData.ValueSort([](double A, double B)->bool { return B < A; });` (scope `SkeletalSimplifier::VertexTypes::BoneSparseVertexAttrs::Correct`) — sort by value from large to small
- L365 _function_ `` (scope `SkeletalSimplifier::VertexTypes::BoneSparseVertexAttrs::IsApproxEquals`)

### `Plugins/Experimental/SkeletalReduction/Source/Public/ISkeletalMeshReduction.h` (Public)


#### class `ISkeletalMeshReduction`  
`class ISkeletalMeshReduction : public IMeshReductionModule`  
_L16-46_
- inherits: `IMeshReductionModule`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L27 _public function_ `static inline ISkeletalMeshReduction& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L42 _public function_ `virtual FString GetName() override`
