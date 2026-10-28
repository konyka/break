# Plugins / DynamicMesh

- module root: `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh`
- headers: 137; symbols: 4520
- symbol kinds: class=163, enum=81, enumerator=289, function=813, macro=84, member=1350, namespace=297, prototype=1204, struct=119, typedef=119, union=1
- PrivateDependencyModuleNames: Eigen, MeshConversion
- PublicDependencyModuleNames: Core, GeometryAlgorithms, GeometryCore

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Operations/RedGreenTessellation.h` (Private)


#### class `UE::Geometry::FRedGreenTessellationPattern`  
`class FRedGreenTessellationPattern : public FTessellationPattern`  
_L22-40_
- inherits: `FTessellationPattern`
- L26 _public prototype_ `FRedGreenTessellationPattern(const FDynamicMesh3* InMesh, const TArray<int>& InTriangleTessLevels);`
- L27 _public prototype_ `virtual ~FRedGreenTessellationPattern() = default;`
- L29 _public member_ `TArray<int32> TriangleLevels;`
- L34 _private prototype_ `virtual EOperationValidationResult Validate() const override;` — FTessellationPattern  overrides
- L35 _private prototype_ `virtual int GetNumberOfNewVerticesForEdgePatch(const int InEdgeID) const override;`
- L36 _private prototype_ `virtual int GetNumberOfNewVerticesForTrianglePatch(const int InTriangleID) const override;`
- L37 _private prototype_ `virtual int GetNumberOfPatchTriangles(const int InTriangleID) const override;`
- L38 _private prototype_ `virtual void TessellateEdgePatch(EdgePatch& EdgePatch) const override;`
- L39 _private prototype_ `virtual void TessellateTriPatch(TrianglePatch& TriPatch) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DYNAMICMESH_API`
- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/ConstrainedMeshDeformationSolver.h` (Private)


#### class `UE::Geometry::FConstrainedMeshDeformationSolver`  
`class FConstrainedMeshDeformationSolver : public UE::Solvers::IConstrainedMeshSolver`  
_L34-187_
- inherits: `UE::Solvers::IConstrainedMeshSolver`
- desc: FConstrainedMeshDeformationSolver is an implmentation of IConstrainedMeshSolver that solves Mesh Deformation problems by using quadratic energy functions based on the vertex-graph Laplacians. All constraints are "soft", ie they are included in the system as weighted quadratic energies rather than had constraints. Both the Laplacian weighting scheme/type and The Sparse Matrix Solver type are configurable.
- L37 _public typedef_ `typedef UE::Solvers::FPositionConstraint FConstraintPosition;`
- L39 _public prototype_ `FConstrainedMeshDeformationSolver(const FDynamicMesh3& DynamicMesh, const ELaplacianWeightScheme Scheme, const EMatrixSolverType MatrixSolverType);`
- L40 _public prototype_ `virtual ~FConstrainedMeshDeformationSolver();`
- L44 _public prototype_ `template<typename MeshType> FConstrainedMeshDeformationSolver(const MeshType& Mesh, const EMatrixSolverType MatrixSolverType);` — Create the solver using a generic mesh type. Assume uniform weight scheme.
- L47 _public prototype_ `void AddConstraint(const int32 VtxId, const double Weight, const FVector3d& Pos, const bool bPostFix) override;` — Add constraint associated with given vertex id.  Boundary vertices will be ignored
- L50 _public prototype_ `bool UpdateConstraintPosition(const int32 VtxId, const FVector3d& Position, const bool bPostFix) override;` — Update the position of an existing constraint.  Bool return if a corresponding constraint weight exists. Boundary vertices will be ignored (and return false).
- L53 _public prototype_ `bool UpdateConstraintWeight(const int32 VtxId, const double Weight) override;` — The underlying solver will have to refactor the matrix if this is done. Bool return if a corresponding constraint position exists. Boundary vertices will be ignored (and return false).
- L56 _public function_ `void ClearConstraints() override` — Clear all constraints associated with this smoother
- L58 _public function_ `void ClearConstraintWeights() override`
- L60 _public function_ `void ClearConstraintPositions() override`
- L64 _public prototype_ `bool IsConstrained(const int32 VtxId) const override;` — Test if for constraint associated with given vertex id. Will return false for any boundary vert.
- L66 _public function_ `virtual bool Deform(TArray<FVector3d>& PositionBuffer) override`
- L70 _public prototype_ `void UpdateSolverConstraints();` — Sync constraints with internal solver.  If in the process any internal matrix factoring is dirty, it will be rebuilt. Note: this is called from within the Deform() method.   Only call this method if you want to trigger the matrix refactor yourself.
- L77 _public prototype_ `bool SetMaxIterations(int32 MaxIterations);`
- L78 _public prototype_ `bool SetTolerance(double Tol);`
- L85 _protected function_ `template<typename MeshType> void Init(const MeshType& Mesh, const ELaplacianWeightScheme Scheme, const EMatrixSolverType MatrixSolverType, const FSparseMatrixD& LaplacianInternal, const FSparseMatrixD& LaplacianBoundary)` — Call this from constructors after building matrices
- L131 _protected function_ `template<typename MeshType> void ExtractInteriorVertexPositions(const MeshType& Mesh, FSOAPositions& VertexPositions) const`
- L148 _protected prototype_ `void UpdateWithPostFixConstraints(FSOAPositions& PositionalVector) const;` — void UpdateMeshWithConstraints(); Respect any bPostFix constraints by moving those vertices to position defined by said constraint.
- L154 _protected prototype_ `bool CopyInternalPositions(const FSOAPositions& PositionalVector, TArray<FVector3d>& LinearArray) const;` — converts the positionalvector to a TArray<FVector3d> where the offset in the array is implicitly the VtxId in the mesh, and not ness the matrix row id NB: the resulting array is treated as sparse and may have un-initialized elements.
- L156 _protected prototype_ `bool CopyBoundaryPositions(TArray<FVector3d>& LinearArray) const;`
- L163 _protected member_ `TMap<int32, FConstraintPosition> ConstraintPositionMap;` — The Key (int32) here is the vertex index not vertex ID making it the same as the matrix row
- L164 _protected member_ `TMap<int32, double> ConstraintWeightMap;`
- L166 _protected member_ `bool bConstraintPositionsDirty = true;`
- L167 _protected member_ `bool bConstraintWeightsDirty = true;`
- L170 _protected member_ `int32 VertexCount;` — Cache the vertex count. boundary + internal
- L173 _protected member_ `int32 InternalVertexCount;` — Cache the number of internal vertices
- L176 _protected member_ `FVertexLinearization VtxLinearization;` — Used to map between VtxId and vertex Index in linear vector..
- L179 _protected member_ `FSOAPositions BoundaryPositions;` — Boundary points, split into 3 arrays (x,y,z).
- L183 _protected member_ `TUniquePtr<FConstrainedSolver> ConstrainedSolver;` — Actual solver that manages the various linear algebra bits.
- L186 _protected member_ `FSparseMatrixD BoundaryOperator;` — Sparse Matrix that holds L^T * B where B has the boundary terms.
- L192 _function_ `template<typename MeshType> FConstrainedMeshDeformationSolver::FConstrainedMeshDeformationSolver(const MeshType& Mesh, const EMatrixSolverType MatrixSolverType) : VertexCount(Mesh.VertexCount())`

#### class `UE::Geometry::FSoftMeshDeformationSolver`  
`class FSoftMeshDeformationSolver : public UE::Solvers::IConstrainedLaplacianMeshSolver`  
_L215-283_
- inherits: `UE::Solvers::IConstrainedLaplacianMeshSolver`
- desc: FSoftMeshDeformationSolver is an implmentation of IConstrainedLaplacianMeshSolver that solves Mesh Deformation problems by using quadratic energy functions based on the vertex-graph Laplacians. The primary difference with FConstrainedMeshDeformationSolver is that boundary vertices do not receive special treatment, they are included in the system and solved in the same way. As a result it is generally necessary to add constraints for boundary vertices. All constraints are "soft", ie they are included in the system as weighted quadratic energies rather than had constraints. Voronoi-Area Clamped Cotangent weights are used for the Laplacian, and an LU Sover
- L218 _public typedef_ `typedef UE::Solvers::FPositionConstraint FPositionConstraint;`
- L220 _public prototype_ `FSoftMeshDeformationSolver(const FDynamicMesh3& DynamicMesh);`
- L221 _public prototype_ `virtual ~FSoftMeshDeformationSolver();`
- L228 _public prototype_ `void AddConstraint(const int32 VtxId, const double Weight, const FVector3d& Position, const bool bPostFix) override;` — Add constraint associated with given vertex id.  Boundary vertices will be ignored
- L231 _public prototype_ `bool UpdateConstraintPosition(const int32 VtxId, const FVector3d& Position, const bool bPostFix) override;` — Update the position of an existing constraint.  Bool return if a corresponding constraint weight exists. Boundary vertices will be ignored (and return false).
- L234 _public prototype_ `bool UpdateConstraintWeight(const int32 VtxId, const double Weight) override;` — The underlying solver will have to refactor the matrix if this is done. Bool return if a corresponding constraint position exists. Boundary vertices will be ignored (and return false).
- L237 _public prototype_ `void ClearConstraints() override;` — Clear all constraints associated with this smoother
- L240 _public function_ `void ClearConstraintWeights() override` — do not support these
- L241 _public function_ `void ClearConstraintPositions() override`
- L244 _public prototype_ `bool IsConstrained(const int32 VtxId) const override;` — Test if for constraint associated with given vertex id. Will return false for any boundary vert.
- L246 _public function_ `virtual bool Deform(TArray<FVector3d>& PositionBuffer) override`
- L255 _public prototype_ `virtual void UpdateLaplacianScale(double UniformScale);` — Update global scale applied to Laplacian vectors before solve.
- L262 _public prototype_ `void UpdateSolverConstraints();` — Sync constraints with internal solver.  If in the process any internal matrix factoring is dirty, it will be rebuilt. Note: this is called from within the Deform() method.   Only call this method if you want to trigger the matrix refactor yourself.
- L269 _protected member_ `TMap<int32, FPositionConstraint> ConstraintMap;` — The Key (int32) here is the vertex index not vertex ID making it the same as the matrix row
- L271 _protected member_ `bool bConstraintPositionsDirty = true;`
- L272 _protected member_ `bool bConstraintWeightsDirty = true;`
- L275 _protected member_ `FVertexLinearization VtxLinearization;` — Used to map between VtxId and vertex Index in linear vector..
- L278 _protected member_ `TUniquePtr<FConstrainedSolver> ConstrainedSolver;` — Actual solver that manages the various linear algebra bits.
- L280 _protected member_ `double LaplacianScale = 1.0;`
- L281 _protected prototype_ `bool HasLaplacianScale() const;`
- L282 _protected prototype_ `double GetLaplacianScale(int32 LinearVtxIndex) const;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DYNAMICMESH_API`
- L19 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/ConstrainedMeshDeformers.h` (Private)


#### class `UE::Geometry::FConstrainedMeshDeformer`  
`class FConstrainedMeshDeformer : public FConstrainedMeshDeformationSolver`  
_L24-40_
- inherits: `FConstrainedMeshDeformationSolver`
- desc: FConstrainedMeshDeformer solves detail-preserving mesh deformation problems with arbitrary position constraints. The initial Mesh Laplacians are defined as Biharmonic * VtxPositions A direct solver is used, currently LU decomposition. Boundary vertices are fixed to their input positions.
- L27 _public prototype_ `FConstrainedMeshDeformer(const FDynamicMesh3& DynamicMesh, const ELaplacianWeightScheme LaplacianType);`
- L28 _public prototype_ `~FConstrainedMeshDeformer() override = default;`
- L32 _public prototype_ `template<typename MeshT> FConstrainedMeshDeformer(const MeshT& Mesh);` — Generic mesh type, assume uniform weight scheme
- L34 _public prototype_ `bool Deform(TArray<FVector3d>& PositionBuffer) override;`
- L38 _private member_ `FSOAPositions LaplacianVectors;`
- L39 _private member_ `FSOAPositions OriginalInteriorPositions;`
- L44 _function_ `template<typename MeshT> FConstrainedMeshDeformer::FConstrainedMeshDeformer(const MeshT& Mesh) : FConstrainedMeshDeformationSolver(Mesh, EMatrixSolverType::LU), LaplacianVectors(FConstrainedMeshDeformationSolver::InternalVertexCount)` — Generic mesh type, assume uniform weight scheme

#### class `UE::Geometry::FSoftMeshDeformer`  
`class FSoftMeshDeformer : public FSoftMeshDeformationSolver`  
_L78-90_
- inherits: `FSoftMeshDeformationSolver`
- desc: FSoftMeshDeformer solves detail-preserving mesh deformation problems with arbitrary position constraints. The initial Mesh Laplacians are defined as Biharmonic * VtxPositions A direct solver is used, currently LU decomposition. Clamped Cotangent weights with Voronoi area are used. Boundary Vertices are *not* fixed, they are included in the system and so should have soft constraints set similar to any other vertex
- L81 _public prototype_ `FSoftMeshDeformer(const FDynamicMesh3& DynamicMesh);`
- L82 _public prototype_ `~FSoftMeshDeformer() override = default;`
- L84 _public prototype_ `bool Deform(TArray<FVector3d>& PositionBuffer) override;`
- L88 _private member_ `FSOAPositions LaplacianVectors;`
- L89 _private member_ `FSOAPositions OriginalPositions;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/ConstrainedMeshSmoothers.h` (Private)


#### class `UE::Geometry::FBiHarmonicMeshSmoother`  
`class FBiHarmonicMeshSmoother : public FConstrainedMeshDeformationSolver`  
_L23-40_
- inherits: `FConstrainedMeshDeformationSolver`
- desc: FConstrainedMeshDeformer solves implicit mesh smoothing problems with arbitrary position constraints. A direct solver is used, currently LU decomposition. Boundary vertices are fixed to their input positions.
- L26 _public typedef_ `typedef FConstrainedMeshDeformationSolver MyBaseType;`
- L28 _public function_ `FBiHarmonicMeshSmoother(const FDynamicMesh3& DynamicMesh, const ELaplacianWeightScheme Scheme) : MyBaseType(DynamicMesh, Scheme, EMatrixSolverType::LU)`
- L32 _public function_ `bool Deform(TArray<FVector3d>& UpdatedPositions) override`
- L38 _public prototype_ `bool ComputeSmoothedMeshPositions(TArray<FVector3d>& UpdatedPositions);` — (Direct) Solve the constrained system and populate the UpdatedPositions with the result

#### class `UE::Geometry::FCGBiHarmonicMeshSmoother`  
`class FCGBiHarmonicMeshSmoother : public FConstrainedMeshDeformationSolver`  
_L52-69_
- inherits: `FConstrainedMeshDeformationSolver`
- desc: FConstrainedMeshDeformer solves implicit mesh smoothing problems with arbitrary position constraints. An iterative Conjugate Gradient solver is used to compute the solution. Boundary vertices are fixed to their input positions.
- L55 _public typedef_ `typedef FConstrainedMeshDeformationSolver MyBaseType;`
- L57 _public function_ `FCGBiHarmonicMeshSmoother(const FDynamicMesh3& DynamicMesh, const ELaplacianWeightScheme Scheme) : MyBaseType(DynamicMesh, Scheme, EMatrixSolverType::BICGSTAB)`
- L61 _public function_ `bool Deform(TArray<FVector3d>& UpdatedPositions) override`
- L67 _public prototype_ `bool ComputeSmoothedMeshPositions(TArray<FVector3d>& UpdatedPositions);` — (Iterative) Solve the constrained system and populate the UpdatedPositions with the result

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/ConstrainedPoissonSolver.h` (Private)


#### class `UE::Geometry::FConstrainedSolver`  
`class FConstrainedSolver`  
_L42-394_
- L46 _public typedef_ `typedef typename FSparseMatrixD::Scalar ScalarType;`
- L47 _public typedef_ `typedef typename FSOAPositions::VectorType VectorType;`
- L56 _public typedef_ `typedef FDummyTimeLogger FConstrainedSolverTimeLogger;` — Change this to enable time logging for testing. typedef FScopedDurationTimeLogger FConstrainedSolverTimeLogger;
- L59 _public function_ `FConstrainedSolver(TUniquePtr<FSparseMatrixD>& SymmatrixMatrixOperator, const EMatrixSolverType MatrixSolverType) : ConstraintPositions((int32)SymmatrixMatrixOperator->cols())`
- L71 _public function_ `void SetConstraintWeights(const TMap<int32, double>& WeightMap)` — Updates the diagonal weights matrix.
- L106 _public function_ `void SetConstraintWeights(const TMap<int32, UE::Solvers::FPositionConstraint>& ConstraintMap)` — Updates the diagonal weights matrix.
- L141 _public function_ `void SetContraintPositions(const TMap<int32, UE::Solvers::FPositionConstraint>& PositionMap)` — Updates the positional source term
- L161 _public function_ `ScalarType GetWeightSqrd(int32 VtxIndex) const`
- L169 _public function_ `IMatrixSolverBase* GetMatrixSolverBase()` — Access to the underlying solver
- L171 _public function_ `const IMatrixSolverBase* GetMatrixSolverBase() const`
- L176 _public function_ `IIterativeMatrixSolverBase* GetMatrixSolverIterativeBase()` — Access to the underlying solver in iterative form - will return null if the solver is not iterative.
- L185 _public function_ `const IIterativeMatrixSolverBase* GetMatrixSolverIterativeBase() const`
- L199 _public function_ `bool Solve(const FSOAPositions& SourceVector, FSOAPositions& SolutionVector) const` — @param SourceVector   - Required that each component vector has size equal to the the number of columns in the laplacian @param SolutionVector - the resulting solution to the least squares problem
- L230 _public function_ `bool Solve(FSOAPositions& SolutionVector) const` — Special case when the source vector is identically zero. NB: this is used for region smoothing.
- L260 _public function_ `bool SolveWithGuess(const FSOAPositions& Guess, FSOAPositions& SolutionVector) const` — For use with iterative solvers. Reverts to Solve(SolutionVector); if the matrix solver type is direct.
- L294 _public function_ `bool SolveWithGuess(const FSOAPositions& Guess, const FSOAPositions& SourceVector, FSOAPositions& SolutionVector) const` — For use with iterative solvers. Reverts to Solve(SourceVector, SolutionVector); if the matrix solver type is direct
- L325 _public function_ `const FSparseMatrixD& Biharmonic() const`
- L331 _protected function_ `void ClearConstraints()` — Zero the diagonal matrix that holds constraints
- L337 _protected function_ `void ClearConstraintPositions()`
- L345 _protected function_ `void ClearWeights()`
- L356 _protected function_ `void UpdateSolverWithContraints()` — Note: If constraints haven't been set, or if constraints have been cleared, this must be called prior to solve.
- L383 _private member_ `FSOAPositions ConstraintPositions;` — Positional Constraint Arrays
- L385 _private member_ `TUniquePtr<FSparseMatrixD> SymmetricMatrixPtr;` — Transpose(Laplacian) * Laplacain
- L386 _private member_ `FSparseMatrixD WeightsSqrdMatrix;` — Weights Squared Diagonal Matrix.
- L388 _private member_ `FSparseMatrixD LHSMatrix;`
- L390 _private member_ `bool bMatrixSolverDirty;`
- L391 _private member_ `TUniquePtr<IMatrixSolverBase> MatrixSolver;`

#### struct `UE::Geometry::FConstrainedSolver::FDummyTimeLogger`  
`struct FDummyTimeLogger`  
_L49-52_
- L51 _public function_ `FDummyTimeLogger(FString InMsg = TEXT("Scoped action"), FOutputDevice* InDe`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)
- L73 _typedef_ `typedef FSparseMatrixD::Scalar ScalarT;` (scope `UE::Geometry::FConstrainedSolver::SetConstraintWeights`)
- L74 _typedef_ `typedef Eigen::Triplet<ScalarT> MatrixTripletT;` (scope `UE::Geometry::FConstrainedSolver::SetConstraintWeights`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/DenseMatrix.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define EIGEN_MPL2_ONLY`
- L42 _namespace_ `namespace UE`
- L44 _namespace_ `namespace Geometry` (scope `UE`)
- L49 _typedef_ `template <typename ScalarType, int RowsAtCompileTime, int ColsAtCompileTime> using TDenseMatrix = Eigen::Matrix<ScalarType, RowsAtCompileTime, ColsAtCompileTime>;` (scope `UE::Geometry`) — Template wrapper around Eigen's Dense Matrix class
- L53 _typedef_ `template <typename ScalarType> using TDenseMatrixX = TDenseMatrix<ScalarType, Eigen::Dynamic, Eigen::Dynamic>;` (scope `UE::Geometry`) — Dense matrix of arbitrary dimensions
- L54 _typedef_ `using FDenseMatrixD = TDenseMatrixX<double>;` (scope `UE::Geometry`)
- L55 _typedef_ `using FDenseMatrixF = TDenseMatrixX<float>;` (scope `UE::Geometry`)
- L56 _typedef_ `using FDenseMatrixI = TDenseMatrixX<int32>;` (scope `UE::Geometry`)
- L60 _typedef_ `template <class ScalarType> using TColumnVector = TDenseMatrix<ScalarType, Eigen::Dynamic, 1>;` (scope `UE::Geometry`) — Dense matrix representing a column vector
- L61 _typedef_ `using FColumnVectorD = TColumnVector<double>;` (scope `UE::Geometry`)
- L62 _typedef_ `using FColumnVectorF = TColumnVector<float>;` (scope `UE::Geometry`)
- L63 _typedef_ `using FColumnVectorI = TColumnVector<int32>;` (scope `UE::Geometry`)
- L74 _prototype_ `template <typename ScalarType, int RowsAtCompileTime, int ColsAtCompileTime> void RandomDenseMatrix(TDenseMatrix<ScalarType, RowsAtCompileTime, ColsAtCompileTime>& OutMatrix, const int32 InRowsAtRunTime, const int32 InColsAtRunTime, const FRandomStream& InRandomStream);` (scope `UE::Geometry`) — Initialize a Dense Matrix with random values from the stream. @param OutMatrix        Matrix will be resized and populated with the random values from the stream. @param InRowsAtRunTime  Number of rows in the output matrix. @param InColsAtRunTime  Number of columns in the output matrix. @param InRandomStream   Random stream used for fetching random values.
- L90 _prototype_ `template <typename ScalarType, int RowsAtCompileTime, int ColsAtCompileTime> bool SliceDenseMatrix(const TDenseMatrix<ScalarType, RowsAtCompileTime,ColsAtCompileTime>& InMatrix, const TArray<int>& InRowsToSlice, const TArray<int>& InColsToSlice, TDenseMatrixX<ScalarType>& OutSlicedMatrix);` (scope `UE::Geometry`) — Slice the matrix such that OutSlicedMatrix = InMatrix[InRowsToSlice, InColsToSlice]. @param InMatrix The matrix we are slicing. @param InRowsToSlice Rows slice mask. If empty all rows will be used. @param InColsToSlice Columns slice mask. If empty all columns will be used. @param OutSlicedMatrix The sliced matrix. @return true if slicing succeeds, false otherwise. Slicing can fail if one of the input parameters is invalid.
- L105 _prototype_ `template <typename ScalarType, int RowsAtCompileTime, int ColsAtCompileTime> bool SliceDenseMatrix(const TDenseMatrix<ScalarType, RowsAtCompileTime, ColsAtCompileTime>& InMatrix, const TArray<int>& InRowsToSlice, TDenseMatrixX<ScalarType>& OutSlicedMatrix);` (scope `UE::Geometry`) — Slice the matrix only along the rows such that OutSlicedMatrix = InMatrix[InRowsToSlice, :]. @param InMatrix The matrix we are slicing. @param InRowsToSlice Rows slice mask. If empty all rows will be used. @param OutSlicedMatrix The sliced matrix. @return true if slicing succeeds, false otherwise. Slicing can fail if one of the input parameters is invalid.

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/LaplacianOperators.h` (Private)


#### Free symbols / members of external scopes

- L30 _prototype_ `void ConstructLaplacian(const ELaplacianWeightScheme Scheme, const FDynamicMesh3& DynamicMesh, FVertexLinearization& VertexMap, FSparseMatrixD& LaplacianInterior, FSparseMatrixD& LaplacianBoundary);` — Construct a sparse matrix representation of the requested "Laplacian" type operator. The mesh itself is assumed to have N interior vertices, and M boundary vertices. @param Scheme             Selects the actual type of "laplacian" constructed. @param DynamicMesh        The triangle mesh @param VertexMap          On return, Additional arrays used to map between vertexID and offset in a linear array (i.e. the row). The vertices are ordered so that last M ( = VertexMap.NumBoundaryVerts() )  correspond to those on the boundary. @param LaplacianInterior  On return, the laplacian operator that acts on the interior vertices: sparse  N x N matrix @param LaplacianBoundary  On return, the portion of the operator that acts on the boundary vertices: sparse  N x M matrix LaplacianInterior * Vector_InteriorVerts + LaplacianBoundary * Vector_BoundaryVerts = Full Laplacian applied to interior vertices.
- L46 _prototype_ `void ConstructCotangentLaplacian( const FDynamicMesh3& DynamicMesh, FVertexLinearization& VertexMap, FSparseMatrixD& LaplacianInterior, FSparseMatrixD& LaplacianBoundary, const bool bClampWeights);`
- L53 _prototype_ `TUniquePtr<FSparseMatrixD> ConstructLaplacian(const ELaplacianWeightScheme Scheme, const FDynamicMesh3& DynamicMesh, FVertexLinearization& VertexMap, TArray<int32>* BoundaryVerts = NULL);`
- L58 _prototype_ `TUniquePtr<FSparseMatrixD> ConstructUmbrellaLaplacian(const FDynamicMesh3& DynamicMesh, FVertexLinearization& VertexMap, TArray<int32>* BoundaryVerts = NULL);`
- L62 _prototype_ `TUniquePtr<FSparseMatrixD> ConstructValenceWeightedLaplacian(const FDynamicMesh3& DynamicMesh3, FVertexLinearization& VertexMap, TArray<int32>* BoundaryVerts = NULL);`
- L66 _prototype_ `TUniquePtr<FSparseMatrixD> ConstructCotangentLaplacian(const FDynamicMesh3& DynamicMesh, FVertexLinearization& VertexMap, const bool bClampWeights = false, TArray<int32>* BoundaryVerts = NULL);`
- L71 _prototype_ `TUniquePtr<FSparseMatrixD> ConstructIDTCotangentLaplacian(const FDynamicMesh3& DynamicMesh, FVertexLinearization& VertexMap, const bool bClampWeights = false, TArray<int32>* BoundaryVerts = NULL);`
- L76 _prototype_ `TUniquePtr<FSparseMatrixD> ConstructCotangentLaplacian(const FDynamicMesh3& DynamicMesh, FVertexLinearization& VertexMap, FSparseMatrixD& AreaMatrix, TArray<int32>* BoundaryVerts = NULL);`
- L81 _prototype_ `TUniquePtr<FSparseMatrixD> ConstructMeanValueWeightLaplacian(const FDynamicMesh3& DynamicMesh, FVertexLinearization& VertexMap, TArray<int32>* BoundaryVerts = NULL);`
- L85 _prototype_ `void ExtractBoundaryVerts(const FVertexLinearization& VertexMap, TArray<int32>& BoundaryVerts);`
- L89 _function_ `template<typename MeshType> void ConstructUniformLaplacian(const MeshType& Mesh, FVertexLinearization& VertexMap, FSparseMatrixD& LaplacianInterior, FSparseMatrixD& LaplacianBoundary)`
- L105 _function_ `template<typename MeshType> TUniquePtr<FSparseMatrixD> ConstructUniformLaplacian(const MeshType& Mesh, FVertexLinearization& VertexMap, TArray<int32>* BoundaryVerts)`

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/MatrixBase.h` (Private)


#### enum `UE::Geometry::EMatrixSolverType`  
`enum class EMatrixSolverType`  
_L12-22_
- L14 _public enumerator_ `LU`
- L15 _public enumerator_ `QR`
- L16 _public enumerator_ `BICGSTAB`
- L17 _public enumerator_ `PCG`
- L19 _public enumerator_ `LDLT`
- L21 _public enumerator_ `FastestPSD`

#### class `UE::Geometry::FMatrixSolverSettings`  
`class FMatrixSolverSettings`  
_L56-64_
- L59 _public member_ `EMatrixSolverType MatrixSolverType;`
- L62 _public member_ `int32 MaxIterations = 600;` — Used by iterative solvers
- L63 _public member_ `double Tolerance = 1e-4;`

#### class `UE::Geometry::IMatrixSolverBase`  
`class IMatrixSolverBase`  
_L69-87_
- desc: Pure Virtual Base Class used to wrap Eigen Solvers.
- L72 _public typedef_ `typedef typename FSparseMatrixD::Scalar ScalarType;`
- L73 _public typedef_ `typedef typename FSOAPositions::VectorType VectorType;`
- L74 _public typedef_ `typedef typename Eigen::Matrix<ScalarType, Eigen::Dynamic, 1> RealVectorType;`
- L76 _public function_ `IMatrixSolverBase()`
- L77 _public prototype_ `virtual ~IMatrixSolverBase() = 0;`
- L78 _public prototype_ `virtual bool bIsIterative() const = 0;`
- L79 _public prototype_ `virtual void Solve(const RealVectorType& BVector, RealVectorType& SolVector) const = 0;`
- L80 _public prototype_ `virtual void Solve(const VectorType& BVector, VectorType& SolVector) const = 0;`
- L81 _public prototype_ `virtual void Solve(const FSOAPositions& BVectors, FSOAPositions& SolVectors) const = 0;`
- L83 _public prototype_ `virtual void SetUp(const FSparseMatrixD& Matrix, bool bIsSymmetric) = 0;`
- L85 _public prototype_ `virtual void Reset() = 0;` — virtual void SetIterations(int32 MaxIterations) = 0;
- L86 _public prototype_ `virtual bool bSucceeded() const = 0;`

#### class `UE::Geometry::IIterativeMatrixSolverBase`  
`class IIterativeMatrixSolverBase : public IMatrixSolverBase`  
_L90-102_
- inherits: `IMatrixSolverBase`
- desc: Additional methods particular to the iterative solvers
- L93 _public function_ `IIterativeMatrixSolverBase()`
- L95 _public prototype_ `virtual ~IIterativeMatrixSolverBase() = 0;`
- L96 _public prototype_ `virtual void SetIterations(int32 MaxIterations) = 0;`
- L97 _public prototype_ `virtual void SetTolerance(double Tol) = 0;`
- L98 _public prototype_ `virtual void SolveWithGuess(const RealVectorType& GuessVector, const RealVectorType& BVector, RealVectorType& SolVector) const = 0;`
- L99 _public prototype_ `virtual void SolveWithGuess(const VectorType& GuessVector, const VectorType& BVector, VectorType& SolVector) const = 0;`
- L100 _public prototype_ `virtual void SolveWithGuess(const FSOAPositions& GuessVector, const FSOAPositions& BVector, FSOAPositions& SolVector) const = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)
- L24 _function_ `static FString MatrixSolverName(const EMatrixSolverType SolverType)` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/MatrixSolver.h` (Private)


#### class `UE::Geometry::TMatrixSolver`  
`template <typename DirectSolverType> class TMatrixSolver : public IMatrixSolverBase`  
_L44-127_
- inherits: `IMatrixSolverBase`
- L47 _public typedef_ `typedef DirectSolverType SolverType;`
- L48 _public function_ `TMatrixSolver()`
- L49 _public function_ `~TMatrixSolver() override`
- L51 _public function_ `bool bIsIterative() const override`
- L53 _public function_ `void Solve(const RealVectorType& BVector, RealVectorType& SolVector) const override`
- L61 _public function_ `void Solve(const VectorType& BVector, VectorType& SolVector) const override`
- L69 _public function_ `void Solve(const FSOAPositions& BVectors, FSOAPositions& SolVectors) const override`
- L79 _public function_ `void SetUp(const FSparseMatrixD& SparseMatrix, bool bIsSymmetric) override`
- L85 _public prototype_ `void SetSymmetry(bool bIsSymmetric);`
- L89 _public function_ `void Reset() override`
- L95 _public function_ `bool bSucceeded() const override`
- L105 _private function_ `void SetUp(const FSparseMatrixD& SparseMatrix)`
- L125 _private member_ `bool bSetup = false;`
- L126 _private member_ `DirectSolverType MatrixSolver;`

#### class `UE::Geometry::TIterativeMatrixSolver`  
`template <typename IterativeMatrixSolverType> class TIterativeMatrixSolver : public IIterativeMatrixSolverBase`  
_L165-264_
- inherits: `IIterativeMatrixSolverBase`
- L168 _public typedef_ `typedef IterativeMatrixSolverType SolverType;`
- L170 _public function_ `TIterativeMatrixSolver()`
- L171 _public function_ `~TIterativeMatrixSolver() override`
- L173 _public function_ `bool bIsIterative() const override`
- L175 _public function_ `void Solve(const RealVectorType& BVector, RealVectorType& SolVector) const override`
- L183 _public function_ `void Solve(const VectorType& BVector, VectorType& SolVector) const override`
- L191 _public function_ `void Solve(const FSOAPositions& BVectors, FSOAPositions& SolVectors) const override`
- L201 _public function_ `void SolveWithGuess(const RealVectorType& GuessVector, const RealVectorType& BVector, RealVectorType& SolVector) const override`
- L210 _public function_ `void SolveWithGuess(const VectorType& GuessVector, const VectorType& BVector, VectorType& SolVector) const override`
- L219 _public function_ `void SolveWithGuess(const FSOAPositions& GuessVectors, const FSOAPositions& BVectors, FSOAPositions& SolVectors) const override`
- L228 _public function_ `void SetUp(const FSparseMatrixD& SparseMatrix, bool bIsSymmetric) override`
- L233 _public function_ `void SetIterations(int32 MaxIterations) override`
- L234 _public function_ `void SetTolerance(double Tol) override`
- L236 _public function_ `void Reset() override`
- L242 _public function_ `bool bSucceeded() const override`
- L250 _private function_ `void SetUp(const FSparseMatrixD& SparseMatrix)`
- L261 _private member_ `bool bSetup = false;`
- L263 _private member_ `IterativeMatrixSolverType MatrixSolver;`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace UE`
- L38 _namespace_ `namespace Geometry` (scope `UE`)
- L41 _prototype_ `TUniquePtr<IMatrixSolverBase> ConstructMatrixSolver(const EMatrixSolverType& MatrixSolverType);` (scope `UE::Geometry`) — Matrix Solver Factory
- L75 _function_ `` (scope `UE::Geometry::TMatrixSolver::Solve`)
- L138 _typedef_ `typedef TMatrixSolver<Eigen::SparseLU <FSparseMatrixD, Eigen::COLAMDOrdering<int>>> FLUMatrixSolver;` (scope `UE::Geometry`) — Timing Tests: 7k Tri  3.6k Verts.  10 sets of 3 backsolves  0.17s 29k tri  14.5k Verts                           1.3s 100k tri  51.5k Verts                           5.39s 127k tri  63.4k Verts                           3.0s
- L139 _typedef_ `typedef TMatrixSolver<Eigen::SparseQR<FSparseMatrixD, Eigen::COLAMDOrdering<int>>> FQRMatrixSolver;` (scope `UE::Geometry`)
- L153 _typedef_ `template<> void TMatrixSolver<typename FLUMatrixSolver::SolverType>::SetSymmetry(bool bIsSymmetric) { check(bIsSymmetric); };` (scope `UE::Geometry`)
- L158 _function_ `template<> inline void TMatrixSolver<typename FLUMatrixSolver::SolverType>::SetSymmetry(bool bIsSymmetric)` (scope `UE::Geometry::TMatrixSolver::SolverType`)
- L161 _function_ `template<> inline void TMatrixSolver<typename FQRMatrixSolver::SolverType>::SetSymmetry(bool bIsSymmetric)` (scope `UE::Geometry::TMatrixSolver::SolverType`)
- L197 _function_ `` (scope `UE::Geometry::TIterativeMatrixSolver::Solve`)
- L225 _function_ `` (scope `UE::Geometry::TIterativeMatrixSolver::SolveWithGuess`)
- L270 _typedef_ `typedef TIterativeMatrixSolver<Eigen::ConjugateGradient<FSparseMatrixD, Eigen::Lower | Eigen::Upper>> FPCGMatrixSolver;` (scope `UE::Geometry`) — typedef Eigen::IncompleteCholesky< double, Eigen::Lower | Eigen::Upper>  FICPreConditioner;
- L271 _typedef_ `typedef TIterativeMatrixSolver<Eigen::BiCGSTAB<FSparseMatrixD, Eigen::IncompleteLUT<FSparseMatrixD::Scalar, int> >> FBiCGMatrixSolver;` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/MeshDiffusionIntegrator.h` (Private)


#### class `UE::Geometry::FMeshDiffusionIntegrator`  
`class FMeshDiffusionIntegrator`  
_L24-81_
- desc: FMeshDiffusionIntegrator solves diffusion problems over vertices of a 3D triangle mesh. Note: if canceled using the optional FProgressCancel, the results may be in an unusable state. (Could likely be generalized to other graph diffusion problems)
- L28 _public prototype_ `FMeshDiffusionIntegrator(const FDynamicMesh3& DynamicMesh, const ELaplacianWeightScheme Scheme, FProgressCancel* Progress = nullptr);`
- L29 _public prototype_ `virtual ~FMeshDiffusionIntegrator() = default;`
- L31 _public prototype_ `void Integrate_ForwardEuler(const int32 NumSteps, const double Speed);`
- L34 _public prototype_ `void Integrate_BackwardEuler(const EMatrixSolverType MatrixSolverType, const int32 NumSteps, const double TimeStepSize);` — Note:
- L36 _public prototype_ `void GetPositions(TArray<FVector3d>& PositionArray) const;`
- L43 _protected prototype_ `virtual void ConstructOperators(const ELaplacianWeightScheme Scheme, const FDynamicMesh3& Mesh, bool& bIsOperatorSymmetric, FVertexLinearization& Linearization, FSparseMatrixD& DiffusionOp, FSparseMatrixD& BoundaryOp) = 0;` — The derived class has to implement this. responsible for constructing the Diffusion Operator, the Boundary Operator etc
- L50 _protected prototype_ `void Initialize(const FDynamicMesh3& DynamicMesh, const ELaplacianWeightScheme Scheme);`
- L55 _protected prototype_ `bool CopyInternalPositions(const FSOAPositions& PositionalVector, TArray<FVector3d>& LinearArray) const;` — Copy the
- L57 _protected prototype_ `bool CopyBoundaryPositions(TArray<FVector3d>& LinearArray) const;`
- L60 _protected member_ `int32 VertexCount;` — Cache the vertex count.
- L63 _protected member_ `int32 InternalVertexCount;` — Cache the number of internal vertices
- L66 _protected member_ `FVertexLinearization VtxLinearization;` — Used to map between VtxId and vertex Index in linear vector..
- L69 _protected member_ `bool bIsSymmetric;` — I don't know if we want to keep this after the constructor
- L70 _protected member_ `FSparseMatrixD DiffusionOperator;`
- L71 _protected member_ `FSparseMatrixD BoundaryOperator;`
- L72 _protected member_ `TArray<int32> EdgeVerts;`
- L73 _protected member_ `FSparseMatrixD::Scalar MinDiagonalValue;`
- L75 _protected member_ `FSOAPositions BoundaryPositions;`
- L77 _protected member_ `FSOAPositions Tmp[2];`
- L78 _protected member_ `int32 Id;` — double buffer id
- L80 _protected member_ `FProgressCancel* ProgressCancel;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/MeshDiffusionSmoothing.h` (Private)


#### class `UE::Geometry::FLaplacianDiffusionMeshSmoother`  
`class FLaplacianDiffusionMeshSmoother : public FMeshDiffusionIntegrator`  
_L17-39_
- inherits: `FMeshDiffusionIntegrator`
- desc: Solve mesh diffusion using Laplacian matrix of various types Note: if canceled using the optional FProgressCancel, the results may be in an unusable state.
- L21 _public function_ `FLaplacianDiffusionMeshSmoother(const FDynamicMesh3& DynamicMesh, const ELaplacianWeightScheme Scheme, FProgressCancel* Progress = nullptr) : FMeshDiffusionIntegrator(DynamicMesh, Scheme, Progress)`
- L29 _protected function_ `void ConstructOperators(const ELaplacianWeightScheme Scheme, const FDynamicMesh3& Mesh, bool& bIsOperatorSymmetric, FVertexLinearization& Linearization, FSparseMatrixD& DiffusionOp, FSparseMatrixD& BoundaryOp) override`

#### class `UE::Geometry::FBiHarmonicDiffusionMeshSmoother`  
`class FBiHarmonicDiffusionMeshSmoother : public FMeshDiffusionIntegrator`  
_L47-95_
- inherits: `FMeshDiffusionIntegrator`
- desc: Solve mesh diffusion using Biharmonic (ie squared Laplacian) matrix of various types Note: if canceled using the optional FProgressCancel, the results may be in an unusable state.
- L51 _public function_ `FBiHarmonicDiffusionMeshSmoother(const FDynamicMesh3& DynamicMesh, const ELaplacianWeightScheme Scheme, FProgressCancel* Progress = nullptr) : FMeshDiffusionIntegrator(DynamicMesh, Scheme, Progress)`
- L59 _protected function_ `void ConstructOperators(const ELaplacianWeightScheme Scheme, const FDynamicMesh3& Mesh, bool& bIsOperatorSymmetric, FVertexLinearization& Linearization, FSparseMatrixD& DiffusionOp, FSparseMatrixD& BoundaryOp) override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/MeshUVSolver.h` (Private)


#### class `UE::Geometry::FConstrainedMeshUVSolver`  
`class FConstrainedMeshUVSolver : public UE::Solvers::IConstrainedMeshUVSolver`  
_L25-64_
- inherits: `UE::Solvers::IConstrainedMeshUVSolver`
- desc: FConstrainedMeshUVSolver is an abstract class that implements methods for setting vertex constraints and their weights.
- L28 _public typedef_ `typedef UE::Solvers::FUVConstraint FUVConstraint;`
- L30 _public prototype_ `FConstrainedMeshUVSolver(const FDynamicMesh3& DynamicMesh);`
- L32 _public prototype_ `virtual ~FConstrainedMeshUVSolver() = default;`
- L35 _public prototype_ `void AddConstraint(const int32 VtxId, const double Weight, const FVector2d& Pos, const bool bPostFix) override;` — Add constraint associated with given vertex id.
- L38 _public prototype_ `bool UpdateConstraintPosition(const int32 VtxId, const FVector2d& Position, const bool bPostFix) override;` — Update the position of an existing constraint. Bool return if a corresponding constraint weight exists.
- L41 _public prototype_ `bool UpdateConstraintWeight(const int32 VtxId, const double Weight) override;` — The underlying solver will have to refactor the matrix if this is done. Bool return if a corresponding constraint position exists.
- L44 _public prototype_ `void ClearConstraints() override;` — Clear all constraints associated with this uv solver.
- L47 _public prototype_ `bool IsConstrained(const int32 VtxId) const override;` — Test if for constraint associated with given vertex id.
- L53 _protected member_ `TMap<int32, FUVConstraint> ConstraintMap;` — The Key (int32) here is the vertex index not vertex ID making it the same as the matrix row
- L56 _protected member_ `bool bConstraintPositionsDirty = true;` — currently unused
- L57 _protected member_ `bool bConstraintWeightsDirty = true;`
- L60 _protected member_ `FVertexLinearization VtxLinearization;` — Used to map between VtxId and vertex Index in linear vector.
- L63 _protected member_ `const FDynamicMesh3& Mesh;` — The Mesh for which we are computing the UV mapping

#### class `UE::Geometry::FConformalMeshUVSolver`  
`class FConformalMeshUVSolver : public FConstrainedMeshUVSolver`  
_L70-143_
- inherits: `FConstrainedMeshUVSolver`
- desc: FConformalMeshUVSolver is an abstract class that implements shared methods for the constrained conformal UV solvers.
- L74 _public function_ `FConformalMeshUVSolver(const FDynamicMesh3& InMesh) : FConstrainedMeshUVSolver(InMesh)`
- L80 _public prototype_ `virtual ~FConformalMeshUVSolver() = default;`
- L95 _public prototype_ `void ConstructConformalEnergyMatrix(FSparseMatrixD& OutConfromalEnergy, const bool bInAreaWeighted = false, const double InSmallTriangleArea = SMALL_NUMBER, FSparseMatrixD* OutCotangentMatrix = nullptr, FSparseMatrixD* OutAreaMatrix = nullptr);` — Construct the 2Vx2V (V is the number of vertices) conformal energy matrix C = L - A, which is equal to the difference between the (possibly area-weighted) cotangent Laplacian (L) and the vector area matrices (A). @param OutConfromalEnergy 	Conformal energy matrix. @param bInAreaWeighted  		Should the entries of the cotangent Laplacian and the vector area matrices be weighted by the areas of the triangles, they are computed on. @param InSmallTriangleArea   The "floor" for the triangle area. Triangles with areas below this value are considered to be triangles with SmallTriangleArea area. Optional and only used if bAreaWeighted == true. @param OutCotangentMatrix 	(optional) If not nullptr, then store the cotangent Laplacian matrix. @param OutAreaMatrix 		(optional) If not nullptr, then store the vector area matrix.
- L117 _protected prototype_ `void ConstructVectorAreaMatrix(FSparseMatrixD& OutAreaMatrix);` — Construct the 2Vx2V (V is the number of vertices) symmetric vector area matrix A. Given the vector X = [u;v] of the stacked UV coordinates, we can compute the signed 2D area of the parameterization using the quadratic form (1/4)*X'*A*X. The area is computed using only the coordinates of the boundary vertices as the contributions from internal edges cancel out. Given a border edge ij: A_{Ui,Vj} =  1, where Ui is the u index (into X) of vert_i and Vj is the v index of vert_j. A_{Vi,Uj} = -1, where Vi is the v index of vert_i and Uj is the u index of vert_j. To ensure the symmetry of A, we additionally set A_{Vj,Ui} = 1 and A_{Uj,Vi} = -1 since the area matrix A will be used as a quadratic coefficients matrix. @param OutAreaMatrix The signed vector area matrix.
- L138 _protected prototype_ `void ConstructWeightedVectorAreaMatrix(FSparseMatrixD& OutAreaMatrix, double& OutMaxArea, const double InSmallTriangleArea = SMALL_NUMBER);` — Construct the 2Vx2V (V is the number of vertices) symmetric weighted area matrix A. This is similar to ConstructVectorAreaMatrix() method but the matrix coefficients are now scaled by the areas of the triangle on which they are computed. This formulation is used to enforce insensitivity to sampling irregularity of the meshes. Because of area scaling, we no longer can only use border edges, but all the directed edges will need to be considered. Given the directed edge ij of a triangle t: A_{Ui,Vj} = 1/Area(t), where Ui is the u index (into X) of vert_i and Vj is the v index of vert_j. A_{Vi,Uj} = -1/Area(t), where Vi is the v index of vert_i and Uj is the u index of vert_j. To ensure the symmetry of A, we additionally set A_{Vj,Ui} = 1/Area(t) and A_{Uj,Vi} = -1/Area(t) since the area matrix A will be used as a quadratic coefficients matrix. @param OutAreaMatrix  	   The signed weighted vector area matrix. @param OutMaxArea		   The maximum area among all mesh triangles @param InSmallTriangleArea  The "floor" for the triangle area. Triangles with areas below this value are considered to be triangles with SmallTriangleArea area.

#### class `UE::Geometry::FLeastSquaresConformalMeshUVSolver`  
`class FLeastSquaresConformalMeshUVSolver : public FConformalMeshUVSolver`  
_L151-188_
- inherits: `FConformalMeshUVSolver`
- desc: FLeastSquaresConformalMeshUVSolver computes the conformal UV map using the Least squares conformal maps for automatic texture atlas generation [Levy 2002] method. It's equivalent to Intrinsic parameterizations of surface meshes [Desburn 2002]. However, the energy is constructed using the formulation presented in the Spectral Conformal parameterization [Mullen 2008].
- L155 _public function_ `FLeastSquaresConformalMeshUVSolver(const FDynamicMesh3& InMesh) : FConformalMeshUVSolver(InMesh)`
- L161 _public prototype_ `virtual ~FLeastSquaresConformalMeshUVSolver() = default;`
- L163 _public prototype_ `virtual bool SolveUVs(const FDynamicMesh3* InMesh, TArray<FVector2d>& OutUVBuffer) override;`
- L172 _protected prototype_ `void ConstructSystemMatrices(FSparseMatrixD& OutSystemMatrix);` — Create the "left-hand side" system matrix used in our linear solve. The matrix is equal to the conformal energy matrix (created with ConstructConformalEnergyMatrix()) but with the rows corresponding to the constraints (defined by ConstraintMap) to only have one non-zero value along the diagonal (set to one).
- L185 _protected prototype_ `bool SolveParameterization(const FSparseMatrixD& InSystemMatrix, const EMatrixSolverType InMatrixSolverType, FColumnVectorD& OutSolution);` — Solve the natural/free-boundary conformal parameterization problem defined by the given system matrix (likely generated by ConstructSystemMatrices() above) using the specified linear solver. Requires that FixedIndices/Positions pairs define at least two constraint points for the solution to be well-defined. Assumes that these rows are also constrained in the System Matrix. @param OutSolution Array of UV coordinates if parameterization succeeded. Empty if the solve failed. @return true if the solve succeded, false otherwise.

#### class `UE::Geometry::FSpectralConformalMeshUVSolver`  
`class FSpectralConformalMeshUVSolver : public FConformalMeshUVSolver`  
_L195-272_
- inherits: `FConformalMeshUVSolver`
- desc: FConformalMeshUVSolver computes the conformal UV map using the Spectral Conformal Parameterization [Mullen 2008] method including enforcing insensitivity to sampling irregularity extension.
- L199 _public function_ `FSpectralConformalMeshUVSolver(const FDynamicMesh3& InMesh, const bool bInPreserveIrregularity = false) : FConformalMeshUVSolver(InMesh), bPreserveIrregularity(bInPreserveIrregularity)`
- L205 _public prototype_ `virtual ~FSpectralConformalMeshUVSolver() = default;`
- L207 _public prototype_ `virtual bool SolveUVs(const FDynamicMesh3* InMesh, TArray<FVector2d>& OutUVBuffer) override;`
- L228 _public prototype_ `void SetInitialSolution(const TArray<FVector2d>& InInitialUVs);` — Spectral conformal solver uses an iterative method to compute the final UVs. As most iterative methods it requires the initial guess of the solution. By default, we randomly set UV values between [-1, 1] and then converge to the correct solution. However, the solution is rotation invariant and it can be different given different initial guesses. Hence, to help make this method more deterministic, you can manually specify the initial per-vertex UVs. Same initial values will always produce the same solution. @param InInitialUVs vector of UV coordinates for every vertex in the mesh. @note resets RandomStream optional variable to avoid confusion as to which one to use.
- L236 _public prototype_ `void SetInitialSolution(const FRandomStream& InRandomStream);` — @param InRandomStream  The stream will be used to sample random values for the initial UV solution. You can set the desired seed value in the stream. @note resets InitialUVs optional variable to avoid confusion as to which one to use.
- L250 _protected prototype_ `void ConstructSystemMatrices(FSparseMatrixD& OutConformalEnergy, FSparseMatrixD& OutMatrixB, FSparseMatrixD& OutMatrixE);` — Construct the matrices needed for solving the general eigenvalue problem. @param OutConformalEnergy Conformal energy matrix (created using ConstructConformalEnergyMatrix() method). @param OutMatrixB 		 2V×2V diagonal matrix with 1 at each diagonal element corresponding to the boundary vertices (not including any of the internal boundaries) and 0 everywhere else. @param OutMatrixE 		 2V×2V matrix such that E(i,1) (resp., E(i,2)) is 1/sqrt(V_b) for each u-coordinate (resp.,v-coordinate) of the boundary vertices (not including any of the internal boundaries) and 0 otherwise. V_b is the number of the boundary vertices.
- L258 _protected prototype_ `bool SolveParameterization(const FSparseMatrixD& InConformalEnergy, const FSparseMatrixD& InMatrixB, const FSparseMatrixD& InMatrixE, FColumnVectorD& OutSolution);` — Solve the general eigenvalue problem to compute the UV mapping using the matrices computed in ConstructSystemMatrices().
- L267 _protected member_ `bool bPreserveIrregularity = false;` — The mesh can contain triangles of variable sizes. By default this difference in size is not considered during the UV solve. Enabling this allows to preserve the triangle size irregularity in the resulting parameterization.
- L270 _protected member_ `TOptional<TArray<FVector2d>> InitialUVs;` — Optional debug varibles used for setting the initial UV values.
- L271 _protected member_ `TOptional<FRandomStream> RandomStream;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API DYNAMICMESH_API`
- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/PowerMethodSolver.h` (Private)


#### class `UE::Geometry::FPowerMethod`  
`class FPowerMethod`  
_L27-156_
- desc: Power iteration solver for computing the largest or smallest eigenvalue/eigenvector pair of a generalized eigenvalue problem A*x = lambda*B*x. A, B are real square matrices. B is optional. If the matrices A and B are not symmetric, this power method might fail due to the fact that the target eigenvalue could be complex. Additionally, with symmetric matrices, the method may still fail to converge in the case that the largest/smallest eigenvalue is not distinct. For sparse matrices see FSparsePowerMethod.
- L30 _public typedef_ `using ScalarType = typename IMatrixSolverBase::ScalarType;`
- L31 _public typedef_ `using RealVectorType = typename IMatrixSolverBase::RealVectorType;`
- L73 _public function_ `FPowerMethod(const Parameters& InParms) : Parms(InParms)`
- L79 _public function_ `FPowerMethod(const MatrixOperator& InMatrixA, const Parameters& InParms) : OpMatrixA(InMatrixA), Parms(InParms)`
- L85 _public function_ `FPowerMethod(const MatrixOperator& InMatrixA, const MatrixOperator& InMatrixB, const Parameters& InParms) : OpMatrixA(InMatrixA), OpMatrixB(InMatrixB), Parms(InParms)`
- L91 _public prototype_ `virtual ~FPowerMethod() = default;`
- L100 _public prototype_ `virtual ESolveStatus Solve(ScalarType& OutEigenValue, RealVectorType& OutEigenVector, bool bComputeLargest = false);` — Compute the eigen pair corresponding to the largest (smallest) eigenvalue. @param OutEigenValue Computed largest (smallest) eigenvalue. @param OutEigenVector Computed eigenvector corresponding to the largest (smallest) eigen value. @param bComputeLargest If true (false) will compute the eigen pair corresponding to the largest (smallest) eigenvalue.
- L103 _public function_ `inline ScalarType GetConvergedTolerance()` — The tolerance value upon reaching convergence or upon hitting the max iteration.
- L109 _public function_ `inline int32 GetConvergedIterations()` — How many iterations did it take for the solver to converge.
- L116 _protected prototype_ `virtual bool Converged(ScalarType Lambda, const RealVectorType& EVector);` — Checks if we reached the convergence condition ||A*x - lambda*B*x||_Inf < Tolerance
- L119 _protected prototype_ `virtual ScalarType RayleighQuotient(const RealVectorType& NormalizedEVector) const;` — Compute the eigenvalue corresponding to the given eigenvector using the Rayleigh Quotient: lambda = x'*A*x/x'*B*x
- L122 _protected function_ `virtual void Normalize(RealVectorType& EVector) const` — Normalize the input vector. Default is L2 normalization.
- L128 _protected prototype_ `virtual bool Iteration(RealVectorType& EVector, bool bComputeLargest);` — Single power iteration that computes the next approximation for the eigenvector.
- L134 _protected prototype_ `virtual bool SetupSolver(bool bComputeLargest);` — In some cases we need to solve a linear system on every iteration. This method is called outside of the loop to pre-factorize any matrices used in the solve.
- L137 _protected prototype_ `virtual bool VerifyUserParameters(bool bComputeLargest) const;` — Check that the input user parameters are valid and matrix operators are set
- L140 _protected function_ `inline bool IsGeneralProblem() const` — Is matrix B not an identity matrix
- L146 _public member_ `MatrixOperator OpMatrixA;` — The A matrix in the A*x = lambda*B*x formula
- L147 _public member_ `TOptional<MatrixOperator> OpMatrixB;` — The optional B matrix in the A*x = lambda*B*x formula
- L150 _protected member_ `TUniquePtr<IMatrixSolverBase> Solver;` — Will either contain pre-factorization of A or B
- L152 _protected member_ `Parameters Parms;` — User specified parameters
- L154 _protected member_ `ScalarType IterationTol = 0.0;` — Current iteration tolerance
- L155 _protected member_ `int32 IterationNum = -1;` — Current iteration number

#### struct `UE::Geometry::FPowerMethod::Parameters`  
`struct Parameters`  
_L34-39_
- desc: User-specified parameters
- L36 _public member_ `ScalarType Tolerance = 1e-6;` — Convergence parameter, see Converged()
- L37 _public member_ `int32 MaxIterations = 1000;` — Maximum number of times the power iteration is run
- L38 _public member_ `TOptional<RealVectorType> InitialSolution;` — Optionally specify the starting vector for the first iteration.

#### enum `UE::Geometry::FPowerMethod::ESolveStatus`  
`enum class ESolveStatus`  
_L42-54_
- desc: The result of the solve
- L44 _public enumerator_ `Success` — Solve was successful and converged within the maximum number of allowed iterations.
- L46 _public enumerator_ `NotConverged` — Solve was successful but did not converge to the user-specified tolerance within the
- L50 _public enumerator_ `NumericalIssue` — Encountered a numerical issues. Most likely causes are a failed linear solve
- L53 _public enumerator_ `InvalidParameters` — User specified parameters are invalid or the matrix operators are not properly set.

#### struct `UE::Geometry::FPowerMethod::MatrixOperator`  
`struct MatrixOperator`  
_L57-71_
- desc: Instead of providing matrices we specify matrix operations via function handles
- L60 _public member_ `TFunction<void(const RealVectorType& VecIn, RealVectorType& VecOut)> Product;` — Matrix vector product
- L67 _public member_ `TFunction<TUniquePtr<IMatrixSolverBase>()> Factorize;` — Creates the IMatrixSolverBase instance and calls SetUp to prefactorize the matrix which is used to compute the matrix inverse vector product. This is optional and is only needed when the problem requires it: Matrix A needs this when computing the smallest eigenpair. Matrix B needs this when computing the largest eigenpair.
- L70 _public member_ `TFunction<int32()> Rows;` — The number of matrix rows. Can omit for B.

#### class `UE::Geometry::FSparsePowerMethod`  
`class FSparsePowerMethod : public FPowerMethod`  
_L185-243_
- inherits: `FPowerMethod`
- desc: Convenience class that handles the power iteration solver where A and B are sparse matrices. Allows passing FSparseMatrixD matrices which are used to construct the corresponding matrix operators with correct solvers. Example usage: FSparseMatrixD L = ... // setup PSD laplacian matrix // Make sure we use the best solver for the job FMatrixHints LHints; LHints.IsPSD = true; FSparsePowerMethod Solver(L, LHints); RealVectorType OutVector; ScalarType OutValue; ESolveStatus Status = Solver.Solve(OutValue, OutVector, true); // compute the largest eigenvalue pair if (Status == ESolveStatus::Success) { // OutValue, OutVector is a valid eigenpair } @note The MatrixOperator TFunctions capture the passed-in matrices by reference, so the lifetime of these matrices must extend through the use of the FSparsePowerMethod class methods (specifically the Solve() method).
- L209 _public function_ `FSparsePowerMethod(const FSparseMatrixD& InMatrixA, const FMatrixHints& InHintsA = FMatrixHints(), const Parameters& InParms = Parameters()) : FPowerMethod(InParms)`
- L218 _public function_ `FSparsePowerMethod(const FSparseMatrixD& InMatrixA, const FSparseMatrixD& InMatrixB, const FMatrixHints& InHintsA = FMatrixHints(), const FMatrixHints& InHintsB = FMatrixHints(), const Parameters& InParms = Parameters()) : FPowerMethod(InParms)`
- L232 _public prototype_ `virtual ~FSparsePowerMethod() = default;`
- L240 _public prototype_ `static void CreateSparseMatrixOperator(const FSparseMatrixD& InMatrix, const FMatrixHints& InHints, MatrixOperator& OutMatrixOp);` — Convenience method to set up the Product(), Factorize() and Rows() TFunctions for the MatrixOperator. @note InMatrix is captured by reference by all TFunctions and hence we assume that the lifetime of the referenced matrix extends past the use of the OutMatrixOp.

#### struct `UE::Geometry::FSparsePowerMethod::FMatrixHints`  
`struct FMatrixHints`  
_L190-207_
- desc: Hints to help choose the best solver for the problem
- L192 _public function_ `FMatrixHints()`
- L195 _public function_ `FMatrixHints(bool bSetAll) : bIsSymmetric(bSetAll), bIsPSD(bSetAll)`
- L200 _public function_ `FMatrixHints(bool bIsSymmetric, bool bIsPSD) : bIsSymmetric(bIsSymmetric), bIsPSD(bIsPSD)`
- L205 _public member_ `bool bIsSymmetric = false;`
- L206 _public member_ `bool bIsPSD = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/QuadraticProgramming.h` (Private)


#### class `UE::Geometry::FQuadraticProgramming`  
`class FQuadraticProgramming`  
_L66-137_
- L70 _public prototype_ `FQuadraticProgramming(const FSparseMatrixD* InMatrixQ, const FColumnVectorD* InVectorF = nullptr);`
- L73 _public prototype_ `void SetEnableParallelization(const bool bEnable);` — If true, will solve for each column x \in X in parallel. By default, parallelization is enabled.
- L76 _public prototype_ `bool SetFixedConstraints(const TArray<int>* InFixedRowIndices, const FSparseMatrixD* InFixedValues);` — Set the fixed constraints either via a sparse or a dense matrix. Calls are mutually exclusive.
- L77 _public prototype_ `bool SetFixedConstraints(const TArray<int>* InFixedRowIndices, const FDenseMatrixD* InFixedValues);`
- L80 _public prototype_ `bool PreFactorize();` — Pre-factorizes the matrices and sets up the solver.
- L86 _public prototype_ `bool Solve(FDenseMatrixD& Solution, const bool bVariablesOnly = false);` — @param Solution The result of the solve as a dense matrix. @param bVariablesOnly If true, the Solution matrix only contains the rows for non-fixed (variable) rows (set via SetFixedConstraints function).
- L93 _public prototype_ `bool Solve(FSparseMatrixD& Solution, const bool bVariablesOnly = false, const double Tolerance = SMALL_NUMBER);` — @param Solution The result of the solve as a sparse matrix. @param bVariablesOnly If true, the Solution matrix only contains the rows for non-fixed (variable) rows (set via SetFixedConstraints function). @param Tolerance Convert dense solution to sparse by pruning any values with their absolute value below the Tolerance.
- L100 _public prototype_ `static bool SolveWithFixedConstraints(const FSparseMatrixD& MatrixQ, const FColumnVectorD* VectorF, const TArray<int>& FixedRowIndices, const FSparseMatrixD& FixedValues, FDenseMatrixD& Solution, const bool bVariablesOnly = false, TArray<int>* VariableRowIndices = nullptr);`
- L101 _public prototype_ `static bool SolveWithFixedConstraints(const FSparseMatrixD& MatrixQ, const FColumnVectorD* VectorF, const TArray<int>& FixedRowIndices, const FSparseMatrixD& FixedValues, FSparseMatrixD& Solution, const bool bVariablesOnly = false, const double Tolerance = SMALL_NUMBER, TArray<int>* VariableRowIndices = nullptr);`
- L109 _public prototype_ `double GetSolveTimeElapsedInSec() const;` — How long did the last call to Solve() take in seconds.
- L112 _public prototype_ `TArray<int> GetVariableRowIndices() const;` — Array of row indices into MatrixQ representing variables (non-fixed).
- L116 _protected member_ `const FSparseMatrixD* MatrixQ = nullptr;` — Matrix of quadratic coefficient
- L117 _protected member_ `const FColumnVectorD* VectorF = nullptr;` — Column vector of linear coefficients
- L120 _protected member_ `bool bFixedConstraintsSet = false;` — Fixed constraints
- L121 _protected member_ `const TArray<int>* FixedRowIndices = nullptr;` — row indices of the fixed parameters, set by the user when calling SetFixedConstraints
- L122 _protected member_ `const FSparseMatrixD* FixedValuesSparse = nullptr;` — matrix of fixed values, set by the user when calling SetFixedConstraints
- L123 _protected member_ `const FDenseMatrixD* FixedValuesDense = nullptr;` — matrix of fixed values, set by the user when calling SetFixedConstraints
- L125 _protected member_ `TArray<int> VariableRowIndices;` — row indices of the variable parameters, computed internally by the call to PreFactorize()
- L127 _protected member_ `TUniquePtr<IMatrixSolverBase> Solver = nullptr;` — PreFactorize() method pre-factorizes the matrices and setups the solver
- L129 _protected member_ `bool bUseParallel = true;` — if true when solving for X, will solve for each column x \in X in parallel
- L136 _protected member_ `double SolveTimeElapsedInSec = 0.0;` — Set every time Solve() is called

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Private/Solvers/Internal/SparseMatrix.h` (Private)


#### class `UE::Geometry::FEigenSparseMatrixAssembler`  
`class FEigenSparseMatrixAssembler : public UE::Solvers::TSparseMatrixAssembler<double>`  
_L63-102_
- inherits: `UE::Solvers::TSparseMatrixAssembler<double>`
- desc: Extension of TSparseMatrixAssembler suitable for eigen sparse matrix
- L66 _public typedef_ `typedef FSparseMatrixD::Scalar ScalarT;`
- L67 _public typedef_ `typedef Eigen::Triplet<ScalarT> MatrixTripletT;`
- L69 _public member_ `TUniquePtr<FSparseMatrixD> Matrix;`
- L70 _public member_ `std::vector<MatrixTripletT> EntryTriplets;`
- L72 _public function_ `FEigenSparseMatrixAssembler(int32 RowsI, int32 ColsJ)`
- L95 _public function_ `void ExtractResult(FSparseMatrixD& Result)`

#### class `UE::Geometry::FSOAPositions`  
`class FSOAPositions : public UE::Geometry::TVector3Arrays<double>`  
_L110-135_
- inherits: `UE::Geometry::TVector3Arrays<double>`
- desc: A struct of arrays representation used to hold vertex positions in three vectors that can interface with the eigen library
- L113 _public typedef_ `typedef typename FSparseMatrixD::Scalar ScalarType;`
- L114 _public typedef_ `typedef Eigen::Matrix<ScalarType, Eigen::Dynamic, 1> RealVectorType;`
- L115 _public typedef_ `typedef Eigen::Map<RealVectorType> VectorType;`
- L116 _public typedef_ `typedef Eigen::Map<const RealVectorType> ConstVectorType;`
- L118 _public function_ `FSOAPositions(int32 Size) : UE::Geometry::TVector3Arrays<double>(Size)`
- L121 _public function_ `FSOAPositions()`
- L124 _public function_ `VectorType Array(int32 i)`
- L129 _public function_ `ConstVectorType Array(int32 i) const`

#### Free symbols / members of external scopes

- L15 _macro_ `#define EIGEN_MPL2_ONLY`
- L46 _namespace_ `namespace UE`
- L48 _namespace_ `namespace Geometry` (scope `UE`)
- L55 _typedef_ `typedef Eigen::SparseMatrix<double, Eigen::ColMajor> FSparseMatrixD;` (scope `UE::Geometry`)
- L77 _function_ `` (scope `UE::Geometry::FEigenSparseMatrixAssembler::FEigenSparseMatrixAssembler`)
- L147 _prototype_ `bool SliceSparseMatrix(const FSparseMatrixD& InMatrix, const TArray<int>& InRowsToSlice, const TArray<int>& InColsToSlice, FSparseMatrixD& OutSlicedMatrix);` (scope `UE::Geometry`) — Slice the matrix such that OutSlicedMatrix = InMatrix[InRowsToSlice, InColsToSlice]. @param InMatrix The matrix we are slicing. @param InRowsToSlice Rows slice mask. If empty all rows will be used. @param InColsToSlice Columns slice mask. If empty all columns will be used. @param OutSlicedMatrix The sliced matrix. @return true if slicing succeeds, false otherwise. Slicing can fail if one of the input parameters is invalid.

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/DynamicMeshModule.h` (Public)


#### class `FDynamicMeshModule`  
`class FDynamicMeshModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/FaceGroupUtil.h` (Public)


#### class `UE::Geometry::FGroupVisualizationCache`  
`class FGroupVisualizationCache`  
_L100-157_
- desc: FGroupVisualizationCache is intended to be used as a cache for per-group information that would be used to visualize PolyGroups, in particular drawing the Polygroup ID for each group.
- L116 _public member_ `bool bStorePerGroupTriangleIDs = false;` — if enabled, each FGroupInfo keeps track of the TriangleIDs that belong to it. Can have significant memory overhead.
- L121 _public member_ `TArray<FGroupInfo> GroupInfo;` — Computed Per-Group Info, for each group found during the Update functions below
- L131 _public prototype_ `void UpdateGroupInfo_ConnectedComponents( const FDynamicMesh3& SourceMesh, const FPolygroupSet& GroupSet, bool bParallel = true);` — Update the GroupInfo array by finding group-connected components. Note that this may result in multiple GroupInfo items with the same GroupID, if they are not connected-components. Computing connected components is somewhat expensive. In addition, for each component, if it is more than 2 triangles it will be "eroded" down a single triangle to determine the group "center", also somewhat expensive. This step can be computed in parallel if bParallel is true.
- L143 _public prototype_ `void UpdateGroupInfo_ConnectedComponents( const FDynamicMesh3& SourceMesh, const ITriangleGroupSetAdapter& Adapter, bool bParallel = true);` — Update the GroupInfo array by finding group-connected components. Note that this may result in multiple GroupInfo items with the same GroupID, if they are not connected-components. Computing connected components is somewhat expensive. In addition, for each component, if it is more than 2 triangles it will be "eroded" down a single triangle to determine the group "center", also somewhat expensive. This step can be computed in parallel if bParallel is true.
- L153 _public function_ `auto begin()` — DO NOT USE DIRECTLY STL-like iterators to enable ranged-based for loop support
- L154 _public function_ `auto begin() const`
- L155 _public function_ `auto end()`
- L156 _public function_ `auto end() const`

#### struct `UE::Geometry::FGroupVisualizationCache::FGroupInfo`  
`struct FGroupInfo`  
_L104-113_
- L106 _public member_ `int32 GroupID;`
- L107 _public member_ `FAxisAlignedBox3d Bounds;` — bounding box of the triangles in the group
- L109 _public member_ `FVector3d Center;` — "center point" of the group - may or may not actually be on the mesh surface
- L110 _public member_ `FIndex2i CenterTris;` — "center triangles" of the group - one or two triangles, may be invalid
- L112 _public member_ `TArray<int32> TriangleIDs;` — list of triangles in the group, only initialized if bStorePerGroupTriangleIDs is true

#### Free symbols / members of external scopes

- L11 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(ITriangleGroupSetAdapter);`
- L13 _macro_ `#define UE_API DYNAMICMESH_API`
- L18 _namespace_ `namespace FaceGroupUtil`
- L25 _prototype_ `void SetGroupID(FDynamicMesh3& Mesh, int32 to);` (scope `FaceGroupUtil`) — Set group ID of all triangles in Mesh
- L30 _prototype_ `void SetGroupID(FDynamicMesh3& Mesh, const TArrayView<const int32>& triangles, int32 to);` (scope `FaceGroupUtil`) — Set group id of subset of triangles in Mesh
- L35 _prototype_ `void SetGroupToGroup(FDynamicMesh3& Mesh, int32 from, int32 to);` (scope `FaceGroupUtil`) — replace group id in Mesh
- L40 _prototype_ `bool HasMultipleGroups(const FDynamicMesh3& Mesh);` (scope `FaceGroupUtil`) — @return true if mesh has multiple face groups
- L45 _prototype_ `void FindAllGroups(const FDynamicMesh3& Mesh, TSet<int32>& GroupsOut);` (scope `FaceGroupUtil`) — find the set of group ids used in Mesh
- L50 _prototype_ `void CountAllGroups(const FDynamicMesh3& Mesh, TArray<int32>& GroupCountsOut);` (scope `FaceGroupUtil`) — count number of tris in each group in Mesh; TODO: does this need sparse storage?
- L56 _prototype_ `void FindTriangleSetsByGroup(const FDynamicMesh3& Mesh, TArray<TArray<int32>>& GroupTrisOut, int32 IgnoreGID = -1);` (scope `FaceGroupUtil`) — collect triangles by group id. Returns array of triangle lists (stored as arrays). This requires 2 passes over Mesh, but each pass is linear
- L61 _prototype_ `bool FindTrianglesByGroup(FDynamicMesh3& Mesh, int32 FindGroupID, TArray<int32>& TrianglesOut);` (scope `FaceGroupUtil`) — find list of triangles in Mesh with specific group id
- L68 _prototype_ `void SeparateMeshByGroups(FDynamicMesh3& Mesh, TArray<FDynamicMesh3>& SplitMeshes);` (scope `FaceGroupUtil`) — `UE_DEPRECATED(5.8, "Use TArray<TUniquePtr<FDynamicMesh3>> version")` — split input Mesh into submeshes based on group ID **does not** separate disconnected components w/ same group ID
- L73 _prototype_ `void SeparateMeshByGroups(FDynamicMesh3& Mesh, TArray<TUniquePtr<FDynamicMesh3>>& SplitMeshes);` (scope `FaceGroupUtil`) — split input Mesh into submeshes based on group ID **does not** separate disconnected components w/ same group ID
- L80 _prototype_ `void SeparateMeshByGroups(FDynamicMesh3& Mesh, TArray<FDynamicMesh3>& SplitMeshes, TArray<int32>& GroupIDs);` (scope `FaceGroupUtil`) — `UE_DEPRECATED(5.8, "Use TArray<TUniquePtr<FDynamicMesh3>> version")` — split input Mesh into submeshes based on group ID **does not** separate disconnected components w/ same group ID
- L85 _prototype_ `void SeparateMeshByGroups(FDynamicMesh3& Mesh, TArray<TUniquePtr<FDynamicMesh3>>& SplitMeshes, TArray<int32>& GroupIDs);` (scope `FaceGroupUtil`) — split input Mesh into submeshes based on group ID **does not** separate disconnected components w/ same group ID
- L90 _namespace_ `namespace UE`
- L92 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/GroupTopology.h` (Public)


#### struct `UE::Geometry::FGroupTopologySelection`  
`struct FGroupTopologySelection`  
_L23-130_
- desc: FGroupTopologySelection represents a set of selected elements of a FGroupTopology
- L25 _public member_ `TSet<int32> SelectedGroupIDs;`
- L26 _public member_ `TSet<int32> SelectedCornerIDs;`
- L27 _public member_ `TSet<int32> SelectedEdgeIDs;`
- L35 _public function_ `int32 GetASelectedGroupID() const` — These are helper methods to get out a value when you know you only have one, or you don't care which one of the existing ones you grab. They only exist because TSet doesn't have a clean way to grab one arbitrary element besides *TSet<int32>::TConstIterator(MySet). The hope is that these are slightly cleaner.
- L39 _public function_ `int32 GetASelectedCornerID() const`
- L43 _public function_ `int32 GetASelectedEdgeID() const`
- L48 _public function_ `FGroupTopologySelection()`
- L50 _public function_ `void Clear()`
- L57 _public function_ `bool IsEmpty() const`
- L62 _public function_ `void Append(const FGroupTopologySelection& Selection)`
- L70 _public function_ `void Remove(const FGroupTopologySelection& Selection)`
- L81 _public function_ `void Toggle(const FGroupTopologySelection& Selection)`
- L98 _public function_ `bool Contains(const FGroupTopologySelection& Selection) const` — Returns true if this selection contains every element in the passed in selection
- L105 _public function_ `bool operator==(const FGroupTopologySelection& Selection) const`
- L114 _public function_ `bool operator!=(const FGroupTopologySelection& Selection) const`
- L119 _public prototype_ `inline bool IsSelectedTriangle(const FDynamicMesh3* Mesh, const FGroupTopology* Topology, int32 TriangleID) const;`
- L123 _private function_ `void ToggleItem(TSet<int32>& Set, int32 Item)`
- L536 _function_ `bool FGroupTopologySelection::IsSelectedTriangle(const FDynamicMesh3* Mesh, const FGroupTopology* Topology, int32 TriangleID) const` — Defined here instead of the class declaration because it requires FGroupTopology to be defined.

#### class `UE::Geometry::FGroupTopology`  
`class FGroupTopology`  
_L151-512_
- desc: Given a per-triangle integer ("group"), FGroupTopology extracts a group-level topological graph from an input Mesh. The graph consists of three elements: Corners: there is a corner at each vertex where 3 or more groups meet (ie 3 or more groups in one-ring) Edges: a group edge is a list of one or more connected edges that have the same pair of different groups on either side Group: a group is a set of connected faces with the same GroupID By default, the triangle group attribute of the input Mesh is used. You can override GetGroupID to provide your own grouping. Various query functions are provided to allow group topology to be interrogated. Note that when functions refer to "CornerID", and "GroupEdgeID", these are simply indices into the internal Corners and Edges arrays. However references to "GroupID" refer to the actual group IDs in FDynamicMesh (not an index into Groups).
- L154 _public function_ `FGroupTopology()`
- L155 _public prototype_ `FGroupTopology(const FDynamicMesh3* Mesh, bool bAutoBuild);`
- L156 _public prototype_ `FGroupTopology(const FDynamicMesh3* Mesh, const FDynamicMeshPolygroupAttribute* GroupLayer, bool bAutoBuild);`
- L161 _public prototype_ `FGroupTopology(const FGroupTopology&) = default;`
- L162 _public prototype_ `FGroupTopology& operator=(const FGroupTopology&) = default;`
- L163 _public prototype_ `virtual ~FGroupTopology() = default;`
- L171 _public prototype_ `void RetargetOnClonedMesh(const FDynamicMesh3* Mesh);` — Keeps the structures of topology in place but points the mesh pointers to a new cloned mesh. If the given mesh is not cloned, the topology will no longer be consistent.
- L173 _public function_ `const FDynamicMesh3* GetMesh() const`
- L182 _public prototype_ `virtual bool RebuildTopology();` — Build the group topology graph. @return true on success, false if there was an error
- L191 _public member_ `TFunction<bool(const FGroupTopology& GroupTopology, int32 Vid, const FIndex2i& AttachedGroupEdgeEids)> ShouldAddExtraCornerAtVert = nullptr;` — Optional function that will add extra corners (in addition to the ones that are always placed at junctures of three or more group edges) during RebuildTopology whenever the function returns true for a vertex that is part of a group edge. For instance, this allows corners to be placed at sharp group edge bends even if the given vertex doesn't connect 3 or more group edges.
- L197 _public function_ `const TSet<int32>& GetCurrentExtraCornerVids() const` — @return Set of vertex ID's that are currently considered corners despite not originally having 3 or more attached group edges (due to the effects of ShouldAddExtraCornerAtVert or RebuildTopologyWithSpecificExtraCorners).
- L205 _public prototype_ `virtual bool RebuildTopologyWithSpecificExtraCorners(const TSet<int32>& ExtraCornerVids);` — Rebuilds the topology graph while ignoring ShouldAddExtraCornerAtVert and only determining whether an extra corner should be forced by seeing whether the vertex is in the provided set. This is used to rebuild the topology with a particular group of extra corners during client undo/redo operations where the behavior of ShouldAddExtraCornerAtVert may have changed in the interim.
- L213 _public function_ `virtual int GetGroupID(int TriangleID) const` — Adjacency of Per-Triangle integers are what define the triangle groups. Override this function to provide an alternate group definition. Note: By convention, group IDs should not be negative @return group id integer for given TriangleID
- L231 _public member_ `TArray<FCorner> Corners;` — List of Corners in the topology graph (ie these are the nodes/vertices of the graph)
- L259 _public member_ `TArray<FGroup> Groups;` — List of Groups in the topology graph (ie faces)
- L290 _public member_ `TArray<FGroupEdge> Edges;` — List of Edges in the topology graph (each edge connects two corners/nodes)
- L295 _public prototype_ `int GetCornerVertexID(int CornerID) const;` — @return the mesh vertex ID for the given Corner ID
- L298 _public prototype_ `int32 GetCornerIDFromVertexID(int32 VertexID) const;` — @return the Group ID for a given Vertex ID, or InvalidID if vertex is not a group corner
- L301 _public prototype_ `const FGroup* FindGroupByID(int GroupID) const;` — @return the FGroup for the given GroupID, or nullptr if not found
- L303 _public function_ `const TArray<int>& GetGroupFaces(int GroupID) const` — @return the list of triangles in the given GroupID, or empty list if not found
- L305 _public prototype_ `const TArray<int>& GetGroupTriangles(int GroupID) const;` — @return the list of triangles in the given GroupID, or empty list if not found
- L307 _public prototype_ `const TArray<int>& GetGroupNbrGroups(int GroupID) const;` — @return the list of neighbour GroupIDs for the given GroupID, or empty list if not found
- L310 _public prototype_ `bool IsGroupEdge(FMeshTriEdgeID TriEdgeID, bool bIncludeMeshBoundary = false) const;` — @return true if the mesh edge identified by FMeshTriEdgeID is a group boundary edge
- L312 _public prototype_ `int FindGroupEdgeID(int MeshEdgeID) const;` — @return the ID of the FGroupEdge that contains the given Mesh Edge ID
- L314 _public prototype_ `int FindGroupEdgeID(FMeshTriEdgeID FMeshTriEdgeID) const;` — @return the ID of the FGroupEdge that contains the given Mesh Edge ID
- L316 _public prototype_ `const TArray<int>& GetGroupEdgeVertices(int GroupEdgeID) const;` — @return the list of vertices of a FGroupEdge identified by the GroupEdgeID
- L318 _public prototype_ `const TArray<int>& GetGroupEdgeEdges(int GroupEdgeID) const;` — @return the list of edges of a FGroupEdge identified by the GroupEdgeID
- L321 _public prototype_ `void FindEdgeNbrGroups(int GroupEdgeID, TArray<int>& GroupsOut) const;` — Add the groups connected to the given GroupEdgeID to the GroupsOut list. This is not the either-side pair, but the set of groups on the one-ring of each connected corner.
- L323 _public prototype_ `void FindEdgeNbrGroups(const TArray<int>& GroupEdgeIDs, TArray<int>& GroupsOut) const;` — Add the groups connected to all the GroupEdgeIDs to the GroupsOut list. This is not the either-side pair, but the set of groups on the one-ring of each connected corner.
- L326 _public prototype_ `void FindEdgeNbrEdges(int GroupEdgeID, TArray<int>& EdgesOut) const;` — Add the edges connected to the given GroupEdgeID to the EdgesOut list. This is somewhat expensive.
- L329 _public prototype_ `bool IsBoundaryEdge(int32 GroupEdgeID) const;` — @return true if the FGroupEdge identified by the GroupEdgeID is on the mesh boundary
- L331 _public prototype_ `bool IsSimpleGroupEdge(int32 GroupEdgeID) const;` — @return true if group edge is a "simple" edge, meaning it only has one mesh edge
- L334 _public prototype_ `bool IsIsolatedLoop(int32 GroupEdgeID) const;` — @return true if the FGroupEdge identified by the GroupEdgeID is an isolated loop (ie not connected to any other edges)
- L337 _public prototype_ `double GetEdgeArcLength(int32 GroupEdgeID, TArray<double>* PerVertexLengthsOut = nullptr) const;` — @return arc length of edge, and optionally accumulated arclength distances for each edge vertex
- L340 _public prototype_ `FVector3d GetEdgeMidpoint(int32 GroupEdgeID, double* ArcLengthOut = nullptr, TArray<double>* PerVertexLengthsOut = nullptr) const;` — @return arclength midpoint of edge, and optionally arclength info
- L343 _public prototype_ `FVector3d GetEdgeAveragePosition(int32 GroupEdgeID) const;` — @return average position of edge (may not be on edge for curved edges)
- L346 _public prototype_ `void FindCornerNbrGroups(int CornerID, TArray<int>& GroupsOut) const;` — Add all the groups connected to the given Corner to the GroupsOut list
- L348 _public prototype_ `void FindCornerNbrGroups(const TArray<int>& CornerIDs, TArray<int>& GroupsOut) const;` — Add all the groups connected to the given Corners to the GroupsOut list
- L355 _public prototype_ `void ForCornerNbrEdges(int CornerID, TFunctionRef<bool(int32 EdgeID)> ReturnTrueToContinue) const;` — Helper that iterates over the group edges neighboring a particular corner. @param ReturnTrueToContinue Function to call on all the group edges, which should return true if it wants iteration to continue, and false if it wants to exit early.
- L358 _public prototype_ `void FindCornerNbrEdges(int CornerID, TArray<int>& EdgesOut) const;` — Add all the Edges connected to the given Corner to the EdgesOut list. This is somewhat expensive as there is no connection from Corners to Edges, must iterate over adjacent faces
- L360 _public prototype_ `void FindCornerNbrCorners(int CornerID, TArray<int>& CornersOut) const;` — Add all the Corners connected to the given Corner to the EdgesOut list. This is somewhat expensive as there is no connection from Corners to Corners, must iterate over adjacent faces/edges
- L363 _public prototype_ `void FindVertexNbrGroups(int VertexID, TArray<int>& GroupsOut ) const;` — Add all the groups connected to the given Mesh Vertex to the GroupsOut list
- L365 _public prototype_ `void FindVertexNbrGroups(const TArray<int>& VertexIDs, TArray<int>& GroupsOut) const;` — Add all the groups connected to the given Mesh Vertices to the GroupsOut list
- L373 _public function_ `template <typename FuncTakingFGroupEdgeAndInt> void ForGroupEdges(int GroupID, const FuncTakingFGroupEdgeAndInt& EdgeFunc) const` — Call EdgeFunc for each boundary edge of the given Group  (no order defined). Templated so it works with both lambdas or TFunctions. Defined here to avoid dll explicit instantiation woes.
- L395 _public function_ `template <typename IntIterableContainerType, typename FuncTakingFGroupEdgeAndInt> void ForGroupSetEdges(const IntIterableContainerType& GroupIDs, const FuncTakingFGroupEdgeAndInt& EdgeFunc) const` — Call EdgeFunc for each boundary edge of each of the given Groups (no order defined). Templated so that it can be used with either sets (such as selections) or lists, and works with both lambdas or TFunctions. Defined here to avoid dll explicit instantiation woes.
- L422 _public prototype_ `void CollectGroupVertices(int GroupID, TSet<int>& Vertices) const;` — Add all the vertices of the given GroupID to the Vertices set
- L424 _public prototype_ `void CollectGroupBoundaryVertices(int GroupID, TSet<int>& Vertices) const;` — Add all the group boundary vertices of the given GroupID to the Vertices set
- L430 _public prototype_ `bool GetGroupEdgeTangent(int GroupEdgeID, FVector3d& TangentOut) const;` — Calculate tangent of group edge, as direction from start to end endpoints @return false if edge is degenerate or start == end
- L435 _public prototype_ `FFrame3d GetGroupFrame(int32 GroupID) const;` — @return a 3D frame for the given group. Based on centroid of triangle centroids, so does not necessarily lie on group surface.
- L440 _public prototype_ `FFrame3d GetSelectionFrame(const FGroupTopologySelection& Selection, FFrame3d* InitialLocalFrame = nullptr) const;` — @return a 3D frame for the given selection
- L445 _public prototype_ `FAxisAlignedBox3d GetSelectionBounds(const FGroupTopologySelection& Selection, TFunctionRef<FVector3d(const FVector3d&)> TransformFunc) const;` — @return A Bounding Box for the vertices of the current selection, with TransformFunc applied
- L451 _public prototype_ `void GetSelectedTriangles(const FGroupTopologySelection& Selection, TArray<int32>& Triangles) const;` — Get the set of selected triangles for a given GroupTopologySelection
- L461 _public prototype_ `static bool IsEdgeAngleSharp(const FDynamicMesh3* Mesh, int32 SharedVid, const FIndex2i& AttachedGroupEdgeEids, double DotThreshold);` — Helper function for use with ShouldAddExtraCornerAtVert. Checks that the dot product of the two mesh edge unit vectors starting from shared vertex is greater than or equal to the given threshold. Assumes that SharedVid actually is shared by the two edges, and returns false if either edge is degenerate. @param DotThreshold Threshold usually set equal to FMathd::Cos(ThresholdDegrees * FMathd::DegToRad). The parameter is not degrees just to avoid that calculation on each invocation.
- L464 _protected member_ `const FDynamicMesh3* Mesh = nullptr;`
- L465 _protected member_ `const FDynamicMeshPolygroupAttribute* GroupLayer = nullptr;`
- L467 _protected member_ `TArray<int> GroupIDToGroupIndexMap;` — allow fast lookup of index in .Groups, given GroupID
- L470 _protected member_ `TBitArray<> CornerVerticesFlags;` — `UE_DEPRECATED(5.1, "Use VertexIDToCornerIDMap instead.")` — bit array of corners for fast testing in ExtractGroupEdges  (redundant w/ VertexIDToCornerIDMap?)
- L472 _protected member_ `TArray<int> EmptyArray;`
- L473 _protected member_ `TMap<int32, int32> VertexIDToCornerIDMap;`
- L475 _protected member_ `TSet<int32> CurrentExtraCornerVids;`
- L482 _protected prototype_ `virtual bool IsCornerVertex(int VertexID) const;` — `UE_DEPRECATED(5.1, "Use ShouldVertBeCorner instead.")` — @return true if given mesh vertex should be a Corner vertex. This looks at the actual mesh- it doesn't use the topology structures.
- L491 _protected prototype_ `virtual bool ShouldVertBeCorner(int VertexID, bool* bIsExtraCornerOut = nullptr) const;` — Return true if the given vertex should be a corner based on the number of adjoining group edges or based on ShouldAddExtraCornerAtVert, if provided. @param bIsExtraCornerOut Set to true if the vertex didn't have 3 or more group adjoining edges, but was forced to be a corner by ShouldAddExtraCornerAtVert.
- L495 _protected function_ `bool ExtractGroupEdges(FGroup& Group)` — `UE_DEPRECATED(5.1, "Use GenerateBoundaryAndGroupEdges instead.")` — Return false if we had a problem finding group boundaries
- L498 _protected prototype_ `bool GenerateBoundaryAndGroupEdges(FGroup& Group, TMap<int32, int32>& GroupEdgeMinEidToGroupEdgeID, TBitArray<>& VertCheckedForCorner);` — Generates group edges and boundary structs for given group. Returns false if failed to find group boundaries.
- L501 _protected function_ `inline FIndex2i MakeEdgeID(int MeshEdgeID) const` — `UE_DEPRECATED(5.1, "Use MakeEdgeGroupsPair instead. The returned pair cannot uniquely identify a group edge.")`
- L503 _protected function_ `inline FIndex2i MakeEdgeID(int Group1, int Group2) const` — `UE_DEPRECATED(5.1, "Use MakeEdgeGroupsPair instead. The returned pair cannot uniquely identify a group edge.")`
- L505 _protected prototype_ `inline FIndex2i MakeEdgeGroupsPair(int MeshEdgeID) const;`
- L506 _protected prototype_ `inline FIndex2i MakeEdgeGroupsPair(int Group1, int Group2) const;`
- L509 _protected function_ `int FindExistingGroupEdge(int GroupID, int OtherGroupID, int FirstVertexID, int SecondVertexID)` — `UE_DEPRECATED(5.1, "Group edges cannot be uniquely identified by a group pair.")`
- L511 _protected prototype_ `void GetAllVertexGroups(int32 VertexID, TArray<int32>& GroupsOut) const;`
- L514 _function_ `FIndex2i FGroupTopology::MakeEdgeGroupsPair(int MeshEdgeID) const`
- L528 _function_ `FIndex2i FGroupTopology::MakeEdgeGroupsPair(int Group1, int Group2) const`

#### struct `UE::Geometry::FGroupTopology::FCorner`  
`struct FCorner`  
_L222-228_
- desc: FCorner is a "corner" in the group topology, IE a vertex where 3+ groups meet.
- L225 _public member_ `int VertexID;` — Mesh Vertex ID
- L227 _public member_ `TArray<int> NeighbourGroupIDs;` — List of IDs of groups connected to this Corner

#### struct `UE::Geometry::FGroupTopology::FGroupBoundary`  
`struct FGroupBoundary`  
_L234-242_
- desc: A Group is bounded by closed loops of FGroupEdge elements. A FGroupBoundary is one such loop.
- L237 _public member_ `TArray<int> GroupEdges;` — Ordered list of edges forming this boundary
- L239 _public member_ `TArray<int> NeighbourGroupIDs;` — List of IDs of groups on the "other side" of this boundary (this GroupBoundary is owned by a particular FGroup)
- L241 _public member_ `bool bIsOnBoundary;` — true if one or more edges in GroupEdges is on the mesh boundary

#### struct `UE::Geometry::FGroupTopology::FGroup`  
`struct FGroup`  
_L245-256_
- desc: FGroup is a set of connected triangles with the same GroupID
- L248 _public member_ `int GroupID;` — GroupID for this group
- L250 _public member_ `TArray<int> Triangles;` — List of triangles forming this group
- L253 _public member_ `TArray<FGroupBoundary> Boundaries;` — List of boundaries of this group (may be empty, eg on a closed component with only one group)
- L255 _public member_ `TArray<int> NeighbourGroupIDs;` — List of groups that are adjacent to this group

#### struct `UE::Geometry::FGroupTopology::FGroupEdge`  
`struct FGroupEdge`  
_L268-287_
- desc: FGroupEdge is a sequence of group-boundary-edges where the two groups on either side of each edge are the same. The sequence is stored an FEdgeSpan. FGroupEdge instances are *shared* between the two FGroups on either side, via FGroupBoundary.
- L271 _public member_ `FIndex2i Groups;` — Groups adjoinging this edge, sorted by increasing value if both present, otherwise the second element may be InvalidID (if boundary edge).
- L273 _public member_ `FEdgeSpan Span;` — Edge span for this edge
- L276 _public member_ `FIndex2i EndpointCorners;` — Index of corners at either end of span, if they exist, otherwise both InvalidID
- L279 _public function_ `int OtherGroupID(int GroupID) const` — @return the member of .Groups that is not GroupID
- L286 _public prototype_ `bool IsConnectedToVertices(const TSet<int>& Vertices) const;` — @return true if any vertex in the Span is in the Vertices set

#### class `UE::Geometry::FTriangleGroupTopology`  
`class FTriangleGroupTopology : public FGroupTopology`  
_L550-562_
- inherits: `FGroupTopology`
- desc: FTriangleGroupTopology is a simplification of FGroupTopology that just represents a normal mesh. This allows algorithms to be written against FGroupTopology that will also work per-triangle. (However, there is enormous overhead to doing it this way!)
- L553 _public function_ `FTriangleGroupTopology()`
- L554 _public prototype_ `FTriangleGroupTopology(const FDynamicMesh3* Mesh, bool bAutoBuild);`
- L556 _public prototype_ `virtual bool RebuildTopology() override;`
- L558 _public function_ `virtual int GetGroupID(int TriangleID) const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/MeshConstraints.h` (Public)


#### enum `UE::Geometry::EEdgeRefineFlags`  
`enum class EEdgeRefineFlags`  
_L18-38_
- desc: EEdgeRefineFlags indicate constraints on triangle mesh edges
- L21 _public enumerator_ `NoConstraint = 0` — Edge is unconstrained
- L23 _public enumerator_ `NoFlip = 1` — Edge cannot be flipped
- L25 _public enumerator_ `NoSplit = 2` — Edge cannot be split
- L27 _public enumerator_ `NoCollapse = 4` — Edge cannot be collapsed
- L29 _public enumerator_ `NoTopologyMerge = 8` — Topology of constraints should not be changed, i.e. disconnected constraint edges should not be connected via an adjacent edge collapse
- L31 _public enumerator_ `FullyConstrained = NoFlip | NoSplit | NoCollapse | NoTopologyMerge` — Edge cannot be flipped, split, collapsed, or topologically-merged
- L33 _public enumerator_ `SplitsOnly = NoFlip | NoCollapse` — Edge can only be split
- L35 _public enumerator_ `FlipOnly = NoSplit | NoCollapse` — Edge can only flip
- L37 _public enumerator_ `CollapseOnly = NoFlip | NoSplit` — Edge can only collapse

#### struct `UE::Geometry::FEdgeConstraint`  
`struct FEdgeConstraint`  
_L44-155_
- desc: FEdgeConstraint is a constraint on a triangle mesh edge
- L48 _public member_ `EEdgeRefineFlags RefineFlags;` — Constraint flags on this edge
- L50 _public member_ `IProjectionTarget * Target;` — Edge is associated with this projection target.
- L53 _public member_ `int TrackingSetID;` — This ID is not a constraint, but can be used to find descendants of a constrained input edge after splits
- L56 _public member_ `float DistanceToleranceSq = -1.f;` — Squared tolerance distance: if positive, edge should not move farther than this distance from Target (if set, and feature is enabled; see TMeshSimplification::bLimitConstrainedSeamMovement)
- L58 _public function_ `FEdgeConstraint()`
- L66 _public function_ `explicit FEdgeConstraint(EEdgeRefineFlags ConstraintFlags)`
- L73 _public function_ `explicit FEdgeConstraint(EEdgeRefineFlags ConstraintFlags, IProjectionTarget* TargetIn)`
- L81 _public function_ `bool CanFlip() const` — @return true if edge can be flipped
- L87 _public function_ `bool CanSplit() const` — @return true if edge can be split
- L93 _public function_ `bool CanCollapse() const` — @return true if edge can be collapsed
- L98 _public function_ `bool CanMergeTopology() const`
- L104 _public function_ `bool NoModifications() const` — @return true if edge cannot be modified at all
- L110 _public function_ `bool IsUnconstrained() const` — @return true if edge is unconstrained
- L116 _public function_ `static FEdgeConstraint Unconstrained()` — @return an unconstrained edge constraint (ie not constrained at all)
- L119 _public function_ `static FEdgeConstraint NoFlips()` — @return a no-flip edge constraint
- L122 _public function_ `static FEdgeConstraint SplitsOnly()` — @return a splits-only edge constraint
- L125 _public function_ `static FEdgeConstraint FullyConstrained()` — @return a fully constrained edge constraint
- L128 _public function_ `static inline bool CanFlip(const EEdgeRefineFlags Flags)` — @return true if flags permit flip
- L134 _public function_ `static inline bool CanSplit(const EEdgeRefineFlags Flags)` — @return true if flags permit split
- L140 _public function_ `static inline bool CanCollapse(const EEdgeRefineFlags Flags)` — @return true if flags permit collapsed
- L145 _public function_ `static inline bool CanMergeTopology(const EEdgeRefineFlags Flags)`
- L151 _public function_ `static inline bool NoModifications(const EEdgeRefineFlags Flags)` — @return true if flags permit no edge modification

#### struct `UE::Geometry::FVertexConstraint`  
`struct FVertexConstraint`  
_L162-226_
- desc: FVertexConstraint is a constraint on a triangle mesh vertex
- L167 _public member_ `bool bCannotDelete;` — Is this vertex permanent (i.e. cannot be removed by topology-change operations).
- L170 _public member_ `bool bCanMove;` — Can this vertex be moved
- L173 _public member_ `int FixedSetID;` — Vertices marked as "CannotDelete" but sharing the same FixedSetID can optionally be collapsed together (ie in Remesher)
- L176 _public member_ `static constexpr int InvalidSetID = -1;` — value for FixedSetID that is treated as not-a-fixed-set-ID by various functions (ie don't use this value yourself)
- L179 _public member_ `IProjectionTarget* Target;` — Vertex is associated with this ProjectionTarget, and should be projected onto it (ie in Remesher)
- L181 _public function_ `FVertexConstraint() : bCannotDelete(false), bCanMove(false), FixedSetID(InvalidSetID), Target(nullptr)`
- L188 _public function_ `explicit FVertexConstraint(bool bCannotDelete, bool bCanMove, int FixedSetID = InvalidSetID) : bCannotDelete(bCannotDelete), bCanMove(bCanMove), FixedSetID(FixedSetID), Target(nullptr)`
- L195 _public function_ `explicit FVertexConstraint(IProjectionTarget* Target, int FixedSetID = InvalidSetID) : bCannotDelete(false), bCanMove(true), FixedSetID(FixedSetID), Target(Target)`
- L202 _public function_ `bool IsUnconstrained() const`
- L208 _public function_ `static FVertexConstraint Unconstrained()` — @return an unconstrained vertex constraint (ie not constrained at all)
- L211 _public function_ `static FVertexConstraint FullyConstrained()` — @return a fully constrained vertex: can't delete and can't move
- L214 _public function_ `static FVertexConstraint PermanentMovable()` — @return a movable but not "delete-able" vertex constraint
- L218 _public function_ `void CombineConstraint(const FVertexConstraint& OtherConstraint)` — Combine the incoming constraint with this constraint. The combination cannot be less restrictive than the existing constraint.

#### class `UE::Geometry::FMeshConstraintCurve`  
`class FMeshConstraintCurve : public FPolyline3d, public IProjectionTarget`  
_L229-248_
- inherits: `FPolyline3d,IProjectionTarget`
- L233 _public function_ `virtual FVector3d Project(const FVector3d& Point, int ) override`

#### struct `UE::Geometry::FConstraintProjectionData`  
`struct FConstraintProjectionData`  
_L250-253_
- L252 _public member_ `TArray<TSharedPtr<FMeshConstraintCurve>> ProjectionCurves;`

#### class `UE::Geometry::FMeshConstraints`  
`class FMeshConstraints`  
_L259-433_
- desc: FMeshConstraints is a set of Edge and Vertex constraints for a Triangle Mesh
- L264 _protected member_ `TMap<int, FEdgeConstraint> Edges;` — Map of mesh edge IDs to active EdgeConstraints
- L267 _protected member_ `TMap<int, FVertexConstraint> Vertices;` — Map of mesh vertex IDs to active VertexConstraints
- L270 _protected member_ `int FixedSetIDCounter;` — internal counter used to allocate new FixedSetIDs
- L275 _public member_ `FConstraintProjectionData ProjectionData;` — Additional data for constraint curve projection
- L278 _public function_ `FMeshConstraints()`
- L284 _public function_ `int AllocateSetID()` — @return an unused Fixed Set ID
- L290 _public function_ `const TMap<int, FEdgeConstraint>& GetEdgeConstraints() const` — @return map of active edge constraints
- L296 _public function_ `const TMap<int, FVertexConstraint>& GetVertexConstraints() const` — @return map of active vertex constraints
- L303 _public function_ `bool HasConstraints() const` — @return true if any edges or vertices are constrained
- L311 _public function_ `bool HasEdgeConstraint(int EdgeID) const` — @return true if given EdgeID has active constraint
- L317 _public function_ `FEdgeConstraint GetEdgeConstraint(int EdgeID) const` — @return EdgeConstraint for give EdgeID, may be Unconstrained
- L331 _public function_ `bool GetEdgeConstraint(int EdgeID, FEdgeConstraint& ConstraintOut) const` — @return true if EdgeID is constrained and ConstraintOut is filled
- L346 _public function_ `void SetOrUpdateEdgeConstraint(int EdgeID, const FEdgeConstraint& ec)` — Set the constraint on the given EdgeID
- L352 _public function_ `void ClearEdgeConstraint(int EdgeID)` — Clear the constraint on the given EdgeID
- L359 _public function_ `void FindConstrainedEdgesBySetID(int SetID, TArray<int>& FoundListOut) const` — Find all constraint edges for the given SetID, and return via FoundListOut
- L373 _public function_ `bool HasVertexConstraint(int VertexID) const` — @return true if given VertexID has active constraint
- L380 _public function_ `FVertexConstraint GetVertexConstraint(int VertexID) const` — @return VertexConstraint for give VertexID, may be Unconstrained
- L394 _public function_ `bool GetVertexConstraint(int VertexID, FVertexConstraint& ConstraintOut)const` — @return true if VetexID  is constrained and ConstraintOut is filled
- L409 _public function_ `void SetOrUpdateVertexConstraint(int VertexID, const FVertexConstraint& vc)` — Set the constraint on the given VertexID
- L414 _public function_ `void SetOrCombineVertexConstraint(int VertexID, const FVertexConstraint& vc)`
- L428 _public function_ `void ClearVertexConstraint(int VertexID)` — Clear the constraint on the given VertexID

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/MeshConstraintsUtil.h` (Public)


#### class `UE::Geometry::FMeshConstraintsUtil`  
`class FMeshConstraintsUtil`  
_L22-205_
- desc: Utility functions for configuring a FMeshConstraints instance
- L35 _public prototype_ `static void ConstrainAllSeams(FMeshConstraints& Constraints, const FDynamicMesh3& Mesh, bool bAllowSplits, bool bAllowSmoothing, bool bParallel = true);` — Constrain all attribute seams for all overlays of a mesh @param Constraints the set of constraints to add to @param Mesh the mesh to constrain @param bAllowSplits should we allow constrained edges to be split @param bAllowSmoothing should we allow constrained vertices to be smoothed @param bParallel should we run the algo in parallel
- L49 _public prototype_ `static void ConstrainAllBoundariesAndSeams(FMeshConstraints& Constraints, const FDynamicMesh3& Mesh, EEdgeRefineFlags MeshBoundaryConstraint, EEdgeRefineFlags GroupBoundaryConstraint, EEdgeRefineFlags MaterialBoundaryConstraint, bool bAllowSeamSplits, bool bAllowSeamSmoothing, bool bAllowSeamCollpase = false, bool bParallel = true);` — Constrain all attribute seams for all overlays of a mesh and different types of boundaries on the mesh @param Constraints the set of constraints to add to @param Mesh the mesh to constrain @param MeshBoundaryConstraint the constraints to place on Mesh boundaries @param GroupBoundaryConstraint the constraints to place on boundaries between polygon groups @param MaterialBoundaryConstraint the constraints to place on boundaries between different materials @param bAllowSplits should we allow constrained edges to be split @param bAllowSmoothing should we allow constrained vertices to be smoothed @param bAllowSeamCollapse should we allow seam edges to collapse @param bParallel should we run the algo in parallel
- L66 _public prototype_ `static void ConstrainSeamsInEdgeROI(FMeshConstraints& Constraints, const FDynamicMesh3& Mesh, const TArray<int>& EdgeROI, bool bAllowSplits, bool bAllowSmoothing, bool bParallel = true);` — Constrain all attribute seams for all overlays of a mesh, for edges in the edge array. This includes edges in s	 * EdgeROI that are seams, as well as vertices incident to edges in EdgeROI that are on seams. @param Constraints the set of constraints to add to @param Mesh the mesh to constrain @param EdgeROI list of edges to try to constrain @param bAllowSplits should we allow constrained edges to be split @param bAllowSmoothing should we allow constrained vertices to be smoothed
- L78 _public prototype_ `static void ConstrainROIBoundariesInEdgeROI(FMeshConstraints& Constraints, const FDynamicMesh3& Mesh, const TSet<int>& EdgeROI, const TSet<int>& TriangleROI, bool bAllowSplits, bool bAllowSmoothing);` — Constrain each edge in the EdgeROI set that is incident on exactly one triangle in the TriangleROI set @param Constraints the set of constraints to add to @param Mesh the mesh to constrain @param EdgeROI set of edges to try to constrain @param TriangleROI set of triangles that determine whether an edge is a "boundary" @param bAllowSplits should we allow constrained edges to be split @param bAllowSmoothing should we allow constrained vertices to be smoothed
- L92 _public function_ `template<typename RealType, int ElementSize> static void ConstrainSeams(FMeshConstraints& Constraints, const FDynamicMesh3& Mesh, const TDynamicMeshOverlay<RealType, ElementSize>& Overlay)` — Constrain attribute seams of the given overlay @param Constraints the set of constraints to add to @param Mesh the mesh to constrain @param Overlay the attribute overlay to find seams in
- L114 _public function_ `template<typename iter> static void FullyConstrainEdges(FMeshConstraints& Constraints, const FDynamicMesh3& Mesh, iter BeginEdges, iter EndEdges)` — For all edges, disable flip/split/collapse. For all vertices, pin in current position. @param Constraints the set of constraints to add to @param Mesh the mesh to constrain
- L138 _public function_ `template<typename EnumerableType> static void FullyConstrainEdges(FMeshConstraints& Constraints, const FDynamicMesh3& Mesh, EnumerableType Enumerable)` — For all edges, disable flip/split/collapse. For all vertices, pin in current position. @param Constraints the set of constraints to add to @param Mesh the mesh to constrain @param Enumerable object that can be passed to a range-based for loop
- L166 _public prototype_ `static bool ConstrainEdgeBoundariesAndSeams(const int EdgeID, const FDynamicMesh3& Mesh, const EEdgeRefineFlags MeshBoundaryConstraint, const EEdgeRefineFlags GroupBoundaryConstraint, const EEdgeRefineFlags MaterialBoundaryConstraint, const EEdgeRefineFlags SeamEdgeConstraint, const bool bAllowSeamSmoothing, FEdgeConstraint& EdgeConstraint, FVertexConstraint& VertexConstraintA, FVertexConstraint& VertexConstraintB);` — Constrain all attribute seams for all overlays of a mesh and different types of boundaries on the mesh @param EdgeID the edge in Mesh to constrain @param Mesh the mesh to constrain @param MeshBoundaryConstraint the constraint policy for Mesh boundaries @param GroupBoundaryConstraint the constraint policy for boundaries between polygon groups @param MaterialBoundaryConstraint the constraint policy for boundaries between different materials @param SeamEdgeConstraint  the constraint policy for attribute (e.g. uv, normals ) seams @param bAllowSmoothing should we allow constrained vertices to be smoothed @param EdgeConstraint [out] edge constraint to be updated @param VertexConstraintA [out] vertex constraint to be updated on return @param VertexConstraintB [out] vertex constraint to be updated on return @return false if no constraint is needed for this edge
- L194 _public prototype_ `static void SetBoundaryConstraintsWithProjection( FMeshConstraints& Constraints, const EBoundaryType BoundaryToConstrain, const FDynamicMesh3& Mesh, double CornerAngleThreshold = 45.0, float CurveConstraintToleranceDistance = -1.f);` — Create polycurve projection targets at group boundaries. Vertices on multiple boundaries are fixed, as well as vertices at boundary "corners" (where the angle formed between adjacent boundary edges is above a given threshold.) @param Constraints (out) constraint data to add new constraints to @param Mesh the mesh to constrain @param CornerAngleThreshold angle threshold (in degrees) above which adjacent edges are considered a corner @param CurveConstraintToleranceDistance threshold distance used to limit how far edges should be allowed to deviate from their constraint curves
- L202 _private prototype_ `FMeshConstraintsUtil() = delete;` — this class is not constructible

#### enum `UE::Geometry::FMeshConstraintsUtil::EBoundaryType`  
`enum class EBoundaryType`  
_L177-182_
- L179 _public enumerator_ `Mesh = 0`
- L180 _public enumerator_ `Group = 1`
- L181 _public enumerator_ `MaterialID = 2`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/MeshCurvature.h` (Public)


#### class `UE::Geometry::FMeshVertexCurvatureCache`  
`class FMeshVertexCurvatureCache`  
_L64-87_
- desc: FMeshVertexCurvatureCache calculates and stores various per-vertex Curvature types for a Mesh, as well as some statistics for those values.
- L76 _public member_ `TArray<FVertexCurvature> Curvatures;`
- L78 _public member_ `FSampleSetStatisticsd MeanStats;`
- L79 _public member_ `FSampleSetStatisticsd GaussianStats;`
- L80 _public member_ `FSampleSetStatisticsd MaxPrincipalStats;`
- L81 _public member_ `FSampleSetStatisticsd MinPrincipalStats;`
- L83 _public function_ `int32 Num() const`
- L84 _public function_ `const FVertexCurvature& operator[](int32 Index) const`
- L86 _public prototype_ `void BuildAll(const FDynamicMesh3& Mesh);`

#### struct `UE::Geometry::FMeshVertexCurvatureCache::FVertexCurvature`  
`struct FVertexCurvature`  
_L68-74_
- L70 _public member_ `double Mean = 0;`
- L71 _public member_ `double Gaussian = 0;`
- L72 _public member_ `double MaxPrincipal = 0;`
- L73 _public member_ `double MinPrincipal = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L10 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshCurvature` (scope `UE`)
- L24 _prototype_ `FVector3d MeanCurvatureNormal(const FDynamicMesh3& Mesh, int32 VertexIndex);` (scope `UE::MeshCurvature`) — Calculate the Discrete Mean-Curvature Normal at a vertex as defined by discrete differential geometry. Based on Eq 8 from "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds", Meyer et al 2002 The Discrete Mean-Curvature Normal is (2.0 * MeanCurvature * SurfaceNormal)    ((unclear why it has the 2.0))
- L33 _prototype_ `FVector3d MeanCurvatureNormal(const FDynamicMesh3& Mesh, int32 VertexIndex, TFunctionRef<FVector3d(int32)> VertexPositionFunc);` (scope `UE::MeshCurvature`) — Calculate the Discrete Mean-Curvature Normal at a vertex as defined by discrete differential geometry. Based on Eq 8 from "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds", Meyer et al 2002 The Discrete Mean-Curvature Normal is (2.0 * MeanCurvature * SurfaceNormal)    ((unclear why it has the 2.0)) @param VertexPositionFunc use positions returned by this function instead of mesh positions
- L41 _prototype_ `double GaussianCurvature(const FDynamicMesh3& Mesh, int32 VertexIndex);` (scope `UE::MeshCurvature`) — Calculate the Discrete Gaussian Curvature at a vertex as defined by discrete differential geometry Based on Eq 9 from "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds", Meyer et al 2002
- L48 _prototype_ `double GaussianCurvature(const FDynamicMesh3& Mesh, int32 VertexIndex, TFunctionRef<FVector3d(int32)> VertexPositionFunc);` (scope `UE::MeshCurvature`) — Calculate the Discrete Gaussian Curvature at a vertex as defined by discrete differential geometry Based on Eq 9 from "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds", Meyer et al 2002 @param VertexPositionFunc use positions returned by this function instead of mesh positions
- L54 _namespace_ `namespace UE`
- L56 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/MeshDerivatives.h` (Public)


#### class `UE::Geometry::FMeshDerivatives`  
`class FMeshDerivatives`  
_L17-52_
- desc: First derivatives of some mesh quantities with respect to particular vertex positions
- L30 _public prototype_ `static FVector3d InteriorAngleGradient(const FDynamicMesh3& Mesh, int32 TriangleIndex, int32 VertexIndex, int32 WRTVertexIndex);` — Gradient of the interior angle of a vertex within a triangle @param Mesh			 Surface mesh to consider @param TriangleIndex  The triangle whose interior angle is considered @param VertexIndex	 The vertex whose interior angle gradient is computed (note this a global mesh vertex index, not [0,1,2]) @param WRTVertexIndex The gradient is computed with respect to this vertex's position @return 3x1 gradient of interior angle with respect to the specified vertex position
- L40 _public prototype_ `static FMatrix3d TriangleNormalGradient(const FDynamicMesh3& Mesh, int32 TriangleIndex, int32 WRTVertexIndex);` — Gradient of the unit-length triangle normal @param Mesh			 Surface mesh to consider @param TriangleIndex  Which triangle to compute the normal gradient for @param WRTVertexIndex The gradient is computed with respect to this vertex's position @return 3x3 Jacobian of the the triangle normal with respect to the specified vertex position
- L50 _public prototype_ `static FMatrix3d TriangleAreaScaledNormalGradient(const FDynamicMesh3& Mesh, int32 TriangleIndex, int32 WRTVertexIndex);` — Gradient of the triangle normal scaled by triangle area @param Mesh           Surface mesh to consider @param TriangleIndex  Triangle for which to compute the gradient of the area-scaled normal @param WRTVertexIndex The gradient is computed with respect to this vertex's position @return 3x3 Jacobian of the the area-scaled triangle normal with respect to the specified vertex position

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/MeshPaths.h` (Public)


#### class `UE::Geometry::FMeshPaths`  
`class FMeshPaths`  
_L20-52_
- desc: Given a mesh and a set of edges, walk connected edges to form a set of paths. We do not distinguish betweens spans and loops -- if the input set of edges forms a loop, it will create an FEdgeSpan with those edges. If the input edges do not form loops, then paths will begin/end at vertices incident on 1 or >2 of the given edges (e.g. "dead ends" or "intersections" of paths.)
- L24 _public function_ `FMeshPaths(const FDynamicMesh3* Mesh, const TSet<int>& Edges ) : Mesh(Mesh), Edges(Edges)`
- L30 _public member_ `const FDynamicMesh3* Mesh = nullptr;` — Inputs
- L31 _public member_ `const TSet<int> Edges;`
- L34 _public member_ `TArray<FEdgeSpan> Spans;` — Outputs
- L37 _public prototype_ `bool Compute();` — Find connected simple paths made up of edges in the input Edges structure
- L41 _private member_ `TSet<int> UnvisitedEdges;`
- L50 _private prototype_ `int GetNextEdge(int CurrentEdge, int FromVertex, int& CrossedVertex) const;` — Find an edge adjacent to CurrentEdge which is in both the Edges and UnvisitedEdges set. Consider only edges incident on CrossedVertex, which is the vertex belonging to CurrentEdge that is not FromVertex. Do not consider an adjacent edge if CrossedVertex is incident on more than 2 input Edges (i.e. we've hit a corner).

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/MeshRefinerBase.h` (Public)


#### class `UE::Geometry::FMeshRefinerBaseFixLayout`  
`class FMeshRefinerBaseFixLayout`  
_L19-23_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L22 _public prototype_ `virtual ~FMeshRefinerBaseFixLayout() = default;`

#### class `UE::Geometry::FMeshRefinerBase`  
`class FMeshRefinerBase : public FMeshRefinerBaseFixLayout`  
_L29-310_
- inherits: `FMeshRefinerBaseFixLayout`
- desc: This is a base class that implements common functionality for various triangle mesh resampling strategies (ie FRemesher and FReducer). You probably should not use this class directly.
- L33 _protected member_ `FDynamicMesh3* Mesh = nullptr;` — Mesh that will be refined
- L36 _protected member_ `TOptional<FMeshConstraints> Constraints;` — Constraints are used to control how certain edges and vertices can be modified
- L39 _protected member_ `IProjectionTarget* ProjTarget = nullptr;` — Vertices can be projected onto this surface when they are modified
- L41 _protected member_ `FDynamicMeshChangeTracker* ActiveChangeTracker = nullptr;`
- L43 _protected function_ `FMeshRefinerBase(FDynamicMesh3* MeshIn)`
- L48 _protected function_ `FMeshRefinerBase()`
- L66 _public member_ `TFunction<EVertexControl(int)> VertexControlF = nullptr;` — This function allows client to specify fine-grained control over what happens to specific vertices. Somewhat redundant w/ FVertexConstraints, but simpler to code and has the option to be dynamic during remesh pass.
- L69 _public member_ `FProgressCancel* Progress = nullptr;` — Set this to be able to cancel running Remesher/Reducer
- L72 _public member_ `TArray<int> DebugEdges;` — This is a debugging aid, will break to debugger if these edges are touched, in debug builds
- L85 _public member_ `ETargetProjectionMode ProjectionMode = ETargetProjectionMode::NoProjection;` — Method to use to project vertices onto target surface. Default is no projection.
- L92 _public member_ `bool AllowCollapseFixedVertsWithSameSetID = true;` — If true, then when two Fixed vertices have the same non-invalid SetID, we treat them as not fixed and allow collapse
- L95 _public member_ `bool ENABLE_PROFILING = false;` — Set to true to profile various passes @todo re-enable this!
- L98 _public member_ `int DEBUG_CHECK_LEVEL = 0;` — 0 = no checking, 1 = check constraints each pass, 2 = and check validity each pass, 3 = and check validity after every mesh change (v slow but best for debugging)
- L102 _public prototype_ `FMeshRefinerBase(const FMeshRefinerBase&) = delete;`
- L103 _public prototype_ `FMeshRefinerBase(FMeshRefinerBase&&) = delete;`
- L104 _public prototype_ `FMeshRefinerBase& operator=(const FMeshRefinerBase&) = delete;`
- L105 _public prototype_ `FMeshRefinerBase& operator=(FMeshRefinerBase&&) = delete;`
- L106 _public prototype_ `virtual ~FMeshRefinerBase() = default;`
- L109 _public function_ `FDynamicMesh3* GetMesh()` — Get the current mesh we are operating on
- L112 _public function_ `const TOptional<FMeshConstraints>& GetConstraints()` — Get the current mesh constraints
- L118 _public function_ `void SetExternalConstraints(TOptional<FMeshConstraints> ConstraintsIn)` — Set external constraints. Note that this object will be updated during computation.
- L122 _public function_ `IProjectionTarget* ProjectionTarget()` — Get the current Projection Target
- L125 _public function_ `void SetProjectionTarget(IProjectionTarget* TargetIn)` — Set a Projection Target
- L132 _public function_ `double GetEdgeFlipTolerance()` — @return edge flip tolerance
- L135 _public function_ `void SetEdgeFlipTolerance(double NewTolerance)` — Set edge flip tolerance. Value is clamped to range [-1,1]
- L142 _public function_ `virtual bool Cancelled()` — If this returns true, abort computation.
- L152 _protected member_ `double EdgeFlipTolerance = 0.0f;` — If normals dot product is less than this, we consider it a normal flip. default = 0
- L157 _protected function_ `inline double ComputeEdgeFlipMetric(const FVector3d& Direction0, const FVector3d& Direction1) const` — @return edge-flip dotproduct metric in range [-1,1] measured between two possibly-not-normalized normal directions. if EdgeFlipTolerance is 0, only the sign of the returned value is valid
- L181 _protected prototype_ `bool CheckIfCollapseCreatesFlipOrInvalid(int vid, int vother, const FVector3d& newv, int tc, int td) const;` — Check if edge collapse will create a face-normal flip. Also checks if collapse would violate link condition, since we are iterating over one-ring anyway. This only checks one-ring of vid, so you have to call it twice, with vid and vother reversed, to check both one-rings @param vid first vertex of edge @param vother other vertex of edge @param newv new vertex position after collapse @param tc triangle on one side of edge @param td triangle on other side of edge
- L188 _protected member_ `double TinyTriangleThreshold = SMALL_NUMBER;` — Avoid creation of triangles smaller than this value. We compare the triangle cross product's norm squared to this value since it's cheaper to compute than the triangle area. So the actual area threshold is sqrt(TinyTriangleThreshold)/2. Default is based on the threshold for creating triangles in a simulation mesh
- L199 _protected prototype_ `bool CheckIfCollapseCreatesTinyTriangle(int vid, int vother, const FVector3d& newv, int tc, int td) const;` — Check if edge collapse will create a triangle with small area (either all vertices are close together, or in a sliver configuration) This only checks one-ring of vid, so you have to call it twice, with vid and vother reversed, to check both one-rings @param vid first vertex of edge @param vother other vertex of edge @param newv new vertex position after collapse @param tc triangle on one side of edge @param td triangle on other side of edge
- L210 _protected prototype_ `bool CheckIfFlipInvertsNormals(int a, int b, int c, int d, int t0) const;` — Check if edge flip might reverse normal direction. Not entirely clear on how to best implement this test. Currently checking if any normal-pairs are reversed. @param a first vertex of edge @param b second vertex of edge @param c opposing vertex 1 @param d opposing vertex 2 @param t0 index of triangle containing [a,b,c]
- L220 _protected prototype_ `bool CheckIfFlipCreatesTinyTriangle(int OriginalEdgeVertexA, int OriginalEdgeVertexB, int OppositeEdgeVertexC, int OppositeEdgeVertexD, int OriginalTriangleIndex) const;` — Check if edge flip might create a triangle with small area (either all vertices are close together, or in a sliver configuration) @param a first vertex of edge @param b second vertex of edge @param c opposing vertex 1 @param d opposing vertex 2 @param t0 index of triangle containing [a,b,c]
- L236 _protected prototype_ `bool CanCollapseEdge(int eid, int a, int b, int c, int d, int tc, int td, int& collapse_to) const;` — Figure out if we can collapse edge eid=[a,b] under current constraint set. First we resolve vertex constraints using CanCollapseVertex(). However this does not catch some topological cases at the edge-constraint level, which which we will only be able to detect once we know if we are losing a or b. See comments on CanCollapseVertex() for what collapse_to is for. @param a first vertex of edge @param b second vertex of edge @param c opposing vertex 1 @param d opposing vertex 2 @param tc index of triangle [a,b,c] @param td index of triangle [a,b,d] @param collapse_to either a or b if we should collapse to one of those, or -1 if either is acceptable
- L249 _protected prototype_ `bool CanCollapseVertex(int eid, int a, int b, int& collapse_to) const;` — Resolve vertex constraints for collapsing edge eid=[a,b]. Generally we would collapse a to b, and set the new position as 0.5*(v_a+v_b). However if a *or* b are constrained, then we want to keep that vertex and collapse to its position. This vertex (a or b) will be returned in collapse_to, which is -1 otherwise. If a *and* b are constrained, then things are complicated (and documented below). @param eid edge ID @param a first vertex of edge @param b second vertex of edge* @param collapse_to either a or b if we should collapse to one of those, or -1 if either is acceptable
- L255 _protected function_ `inline bool IsVertexPositionConstrained(int VertexID)` — @return true if given vertex can't move, or has a projection target
- L268 _protected function_ `inline FVertexConstraint GetVertexConstraint(int VertexID)` — @return constraint for given vertex
- L280 _protected function_ `inline bool GetVertexConstraint(int VertexID, FVertexConstraint& OutConstraint)` — @return true if vertex has constraint
- L293 _public prototype_ `void SetMeshChangeTracker(FDynamicMeshChangeTracker* Tracker);`
- L296 _protected prototype_ `virtual void SaveTriangleBeforeModify(int32 TriangleID);`
- L297 _protected prototype_ `virtual void SaveEdgeBeforeModify(int32 EdgeID);`
- L298 _protected prototype_ `virtual void SaveVertexTrianglesBeforeModify(int32 VertexID);`
- L305 _protected prototype_ `void RuntimeDebugCheck(int EdgeID);` — testing/debug/profiling stuff
- L306 _protected prototype_ `virtual void DoDebugChecks(bool bEndOfPass = false);`
- L307 _protected prototype_ `void DebugCheckUVSeamConstraints();`
- L308 _protected prototype_ `void DebugCheckVertexConstraints();`

#### enum `UE::Geometry::FMeshRefinerBase::EVertexControl`  
`enum class EVertexControl : uint8`  
_L55-61_
- L57 _public enumerator_ `AllowAll = 0`
- L58 _public enumerator_ `NoSmooth = 1`
- L59 _public enumerator_ `NoProject = 2`
- L60 _public enumerator_ `NoMovement = NoSmooth | NoProject`

#### enum `UE::Geometry::FMeshRefinerBase::ETargetProjectionMode`  
`enum class ETargetProjectionMode : uint8`  
_L75-82_
- desc: Options for projecting vertices onto target surface
- L77 _public enumerator_ `NoProjection = 0` — disable projection
- L78 _public enumerator_ `AfterRefinement = 1` — do all projection after the refine/smooth pass
- L79 _public enumerator_ `Inline = 2` — project after each vertex update. Better results but more

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/MeshSimplification.h` (Public)


#### enum `UE::Geometry::ESimplificationResult`  
`enum class ESimplificationResult`  
_L18-32_
- L20 _public enumerator_ `Ok_Collapsed = 0`
- L21 _public enumerator_ `Ignored_CannotCollapse = 1`
- L22 _public enumerator_ `Ignored_EdgeIsFullyConstrained = 2`
- L23 _public enumerator_ `Ignored_EdgeTooLong = 3`
- L24 _public enumerator_ `Ignored_Constrained = 4`
- L25 _public enumerator_ `Ignored_CreatesFlip = 5`
- L26 _public enumerator_ `Failed_OpNotSuccessful = 6`
- L27 _public enumerator_ `Failed_NotAnEdge = 7`
- L28 _public enumerator_ `Failed_IsolatedTriangle = 8`
- L29 _public enumerator_ `Failed_GeometricDeviation = 9`
- L30 _public enumerator_ `Ignored_CreatesTinyTriangle = 10`
- L31 _public enumerator_ `Failed_ConstraintDeviation = 11`

#### enum `UE::Geometry::ERegularizeSimplificationMethod`  
`enum class ERegularizeSimplificationMethod`  
_L34-42_
- L38 _public enumerator_ `Position` — Regularize with a distance-from-original-vertex-position term Simplest / fastest method, stable even for very large weights
- L41 _public enumerator_ `NormalLine` — Regularize with a distance-from-line-through-vertex-along-normal term. Tends to give slightly better results for small weights; can be less stable for very large weights

#### struct `UE::Geometry::TQuadricOptionsHelper`  
`template <typename T, typename = void> struct TQuadricOptionsHelper`  
_L46-49_
- L55 _public typedef_ `using FOptions = typename T::FOptions;`

#### struct `UE::Geometry::TQuadricOptionsHelper::FOptions`  
`struct FOptions`  
_L48-48_

#### struct `UE::Geometry::TQuadricOptionsHelper`  
`template <typename T> struct TQuadricOptionsHelper<T, std::void_t<typename T::FOptions>>`  
_L53-56_
- desc: Partial specialization (kicks in when T::FOptions exists)
- L55 _public typedef_ `using FOptions = typename T::FOptions;`

#### class `UE::Geometry::TMeshSimplification`  
`template <typename QuadricErrorType> class TMeshSimplification : public FMeshRefinerBase`  
_L62-537_
- inherits: `FMeshRefinerBase`
- desc: Implementation of Garland & Heckbert Quadric Error Metric (QEM) Triangle Mesh Simplification
- L66 _public typedef_ `typedef QuadricErrorType FQuadricErrorType;`
- L67 _public typedef_ `typedef typename FQuadricErrorType::ScalarType RealType;`
- L68 _public typedef_ `typedef TQuadricError<RealType> FSeamQuadricType;`
- L70 _public typedef_ `using FQuadricOptions = TQuadricOptionsHelper<QuadricErrorType>::FOptions;`
- L92 _public member_ `ESimplificationCollapseModes CollapseMode = ESimplificationCollapseModes::MinimalQuadricPositionError;` — Controls the method used when selecting the position the results from an edge collapse. Note some of the simpler methods (such as average) may be significantly slower as they result in many more points that are rejected because the would cause a triangle flip. MinimalQuadricPositionError  Try to find position for collapsed vertices that minimizes quadric error. If false we just use midpoints, which is actually significantly slower, because it results in many more points that would cause a triangle flip, which are then rejected. MinimalExistingVertexError   Use one of the existing vertex position with smallest error for the collapse point. AverageVertexPosition        Use the midpoint of the two vertex positions.
- L95 _public member_ `bool bRetainQuadricMemory = false;` — if false, face and vertex quadrics are recomputed in the neighborhood of each collapse, definitely slower but maybe higher quality
- L100 _public member_ `bool bPreserveBoundaryShape = true;` — if true, we try to keep boundary vertices on boundary. You probably want this if you aren't using seam quadrics.
- L103 _public member_ `bool bAllowSeamCollapse = true;` — if true, we allow UV and Normal seams to collapse during simplification.
- L108 _public member_ `bool bPreventTinyTriangles = false;` — Controls whether we disallow creation of triangles with small areas inside edge operations. This is moderately expensive and in some cases can result in lower-quality meshes. Disabled by default.
- L113 _public member_ `bool bLimitConstrainedSeamMovement = false;` — If true, we prevent collapses that would move edge midpoints away from their constraint target by more than the edge constraint's threshold distance (if any)
- L119 _public member_ `double RegularizeWeight = 0.;` — If greater than 0, we will add a regularization term with this weight. This can help give a better triangulation for example in flat regions where the error metric is under-determined
- L122 _public member_ `ERegularizeSimplificationMethod RegularizeMethod = ERegularizeSimplificationMethod::NormalLine;` — Method to use to regularize, if RegularizeWeight > 0
- L125 _public member_ `EEdgeRefineFlags MeshBoundaryConstraint, GroupBoundaryConstraint, MaterialBoundaryConstraint;` — When using the constraint system, these options will apply to the appropriate boundaries.
- L125 _public member_ `EEdgeRefineFlags MeshBoundaryConstraint, GroupBoundaryConstraint, MaterialBoundaryConstraint;` — When using the constraint system, these options will apply to the appropriate boundaries.
- L125 _public member_ `EEdgeRefineFlags MeshBoundaryConstraint, GroupBoundaryConstraint, MaterialBoundaryConstraint;` — When using the constraint system, these options will apply to the appropriate boundaries.
- L138 _public member_ `EGeometricErrorCriteria GeometricErrorConstraint = EGeometricErrorCriteria::None;` — Geometric error measurement/check to perform before allowing an edge collapse
- L141 _public member_ `double GeometricErrorTolerance = 0.0;` — Tolerance to use in geometric error checking
- L154 _public member_ `int32 MaxResultTriangleCount = 0;` — If > 0, this is an absolute upper bound on the result triangle count: while the mesh has more triangles than this, the simplifier bypasses its stopping criteria (geometric error tolerance, edge-too-long rejection in SimplifyToEdgeLength, and the SimplifyToMaxError loop break) and keeps collapsing. Once the count drops to this value or below, the configured stopping criteria resume. Default 0 = stopping criteria always apply (unchanged behavior). Useful in combination with SimplifyToTriangleCount + GeometricErrorTolerance: simplification will always reach this ceiling, then continue toward the SimplifyToTriangleCount target only while collapses stay within tolerance.
- L156 _public member_ `FQuadricOptions QuadricOptions;`
- L159 _public member_ `TFunction<double(const FDynamicMesh3&, int VertexA, int VertexB)> CustomGeometricErrorScaleF;` — Custom scales to apply to *measured* errors and edge lengths. Note this is in effect the inverse of scaling the tolerances / target lengths.
- L160 _public member_ `TFunction<double(const FDynamicMesh3&, int VertexA, int VertexB)> CustomEdgeLengthScaleF;`
- L162 _public member_ `TFunction<double(const FDynamicMesh3&, int Vertex)> CustomQuadricErrorScaleF;` — Custom per-vertex quadric error scaling. Values should be greater than zero.
- L164 _public function_ `TMeshSimplification(FDynamicMesh3* m) : FMeshRefinerBase(m)`
- L181 _public prototype_ `virtual void SimplifyToTriangleCount(int TriangleCount);` — Simplify mesh until we reach a specific triangle count, unless geometric error criterion stops the decimation earlier. Note that because triangles are removed in pairs, the resulting count may be TriangleCount-1. @param TriangleCount the target triangle count
- L187 _public prototype_ `virtual void SimplifyToVertexCount(int VertexCount);` — Simplify mesh until it has a specific vertex count @param VertexCount the target vertex count
- L193 _public prototype_ `virtual void SimplifyToEdgeLength(double MinEdgeLength);` — Simplify mesh until no edges smaller than min length remain. This is not a great criteria. @param MinEdgeLength collapse any edge longer than this
- L199 _public prototype_ `virtual void SimplifyToMaxError(double MaxError);` — Simplify mesh until the quadric error of an edge collapse exceeds the specified criteria. @param MaxError collapse an edge if the corresponding quadric error exceeds this
- L207 _public prototype_ `virtual void SimplifyToMinimalPlanar( double CoplanarAngleTolDeg = 0.001, TFunctionRef<bool(int32 EdgeID)> EdgeFilterPredicate = [](int32) { return true; } );` — Maximally collapse mesh in a way that does not change shape at all. This process does not involve quadric error at all. @param AngleTolDeg two triangles are considered coplanar if their normals are within this angle tolerance @param EdgeFilterPredicate only edges that pass this predicate will be considered for collapse. Default all true.
- L209 _public function_ `double CoplanarAngleTolDeg = 0.001, TFunctionRef<bool(int32 EdgeID)> EdgeFilterPredicate = [](int32)`
- L221 _public prototype_ `virtual void FastCollapsePass(double MinEdgeLength, int Rounds = 1, bool bMeshIsClosedHint = false, uint32 MinTriangleCount = 0);` — Does N rounds of collapsing edges longer than fMinEdgeLength. Does not use Quadrics or priority queue. This is a quick way to get triangle count down on huge meshes (eg like marching cubes output). @param MinEdgeLength collapse any edge longer than this @param Rounds number of collapse rounds @param MeshIsClosedHint if you know the mesh is closed, this pass this true to avoid some precomputes @param MinTriangleCount halt fast collapse if mesh falls below this triangle count
- L227 _protected function_ `TMeshSimplification()` — for subclasses that extend our behavior
- L232 _protected function_ `bool EnableInlineProjection() const` — this just lets us write more concise code
- L237 _protected function_ `bool ShouldIgnoreStoppingCriteria() const` — Returns true while the mesh is still above MaxResultTriangleCount and we should therefore override stopping criteria (geometric error, edge-too-long, max-error loop break) to keep collapsing. When MaxResultTriangleCount is 0 (default) this is always false.
- L242 _protected member_ `float MaxErrorAllowed = FLT_MAX;`
- L243 _protected member_ `double MinEdgeLength = FMathd::MaxReal;`
- L244 _protected member_ `int TargetCount = INT_MAX;`
- L252 _protected member_ `ETargetModes SimplifyMode = ETargetModes::TriangleCount;`
- L257 _protected prototype_ `virtual void DoSimplify();` — Top-level function that does the simplification
- L266 _protected member_ `uint64 MaxEdgeID = 0;` — We are using a modulo-index loop to break symmetry/pathological conditions.
- L267 _protected function_ `virtual int StartEdges()`
- L273 _protected function_ `virtual int GetNextEdge(int CurEdgeID, bool& bDoneOut)`
- L283 _protected member_ `double SeamEdgeWeight = 256.;`
- L285 _protected member_ `TArray<FQuadricErrorType> vertQuadrics;`
- L286 _protected prototype_ `virtual void InitializeVertexQuadrics();`
- L288 _protected member_ `TMap<int, FSeamQuadricType> seamQuadrics;`
- L289 _protected prototype_ `virtual void InitializeSeamQuadrics();`
- L291 _protected member_ `TArray<double> triAreas;`
- L292 _protected member_ `TArray<FVector3d> triNormals;` — this array is only populate if needed; i.e. if RegularizeUsesNormals() returns true
- L293 _protected member_ `TArray<FQuadricErrorType> triQuadrics;`
- L294 _protected member_ `TArray<double> AppliedVertexQuadricScales;` — needed to properly update scaled vertex quadrics in the memoryless update case
- L295 _protected prototype_ `virtual void InitializeTriQuadrics();`
- L297 _protected function_ `bool RegularizeUsesNormals() const`
- L302 _protected member_ `FDynamicMeshNormalOverlay* NormalOverlay;`
- L304 _protected prototype_ `FQuadricErrorType ComputeFaceQuadric(const int tid, FVector3d& nface, FVector3d& c, double& Area) const;`
- L307 _protected prototype_ `FQuadricErrorType AssembleEdgeQuadric(const FDynamicMesh3::FEdge& edge) const;` — uses pre-computed vertex, face and seam quadrics to construct the edge quadric.
- L309 _protected prototype_ `FQuadricErrorType MergeVertexQuadricsToEdgeQuadric(const FDynamicMesh3::FEdge& edge) const;`
- L311 _protected prototype_ `void UpdateVertexAttributes(int edgeID, int va, int vb );`
- L330 _protected member_ `TArray<QEdge> EdgeQuadrics;`
- L331 _protected member_ `FIndexPriorityQueue EdgeQueue;`
- L343 _protected prototype_ `virtual void InitializeQueue();`
- L346 _protected prototype_ `FVector3d OptimalPoint(int eid, const FQuadricErrorType& q, int ea, int eb);` — return point that minimizes quadric error for edge [ea,eb]
- L348 _protected function_ `FVector3d GetProjectedPoint(const FVector3d& pos)`
- L359 _protected prototype_ `virtual void UpdateNeighborhood(const FDynamicMesh3::FEdgeCollapseInfo& collapseInfo);` — update queue weight for each edge in vertex one-ring and rebuild and quadrics necessary
- L362 _protected function_ `virtual void Reproject()`
- L377 _protected member_ `bool bHaveBoundary;`
- L378 _protected member_ `TArray<bool> IsBoundaryVtxCache;`
- L379 _protected prototype_ `void Precompute(bool bMeshIsClosed = false);`
- L381 _protected function_ `inline bool IsBoundaryVertex(int vid) const`
- L404 _protected prototype_ `bool CanCollapseEdge(int edgeID, int a, int b, int c, int d, int t0, int t1, int& collapse_to, FCollapseInfo* OutCollapseInfo = nullptr) const;` — Figure out if we can collapse edge eid=[a,b] under current constraint set Similar to the base class FMeshRefinerBase::CanCollapseEdge, but with simplifier-specific modifications (some more flexibility and restrictions depending on CollapseMode) @param OutCollapseInfo If non-null, we can allow more edge collapses that require some additional post-collapse updates See the similar base class for description of the other parameters.
- L411 _protected prototype_ `ESimplificationResult CollapseEdge(int edgeID, FVector3d vNewPos, FDynamicMesh3::FEdgeCollapseInfo& collapseInfo, int32 RequireKeepVert = -1);` — Collapse given edge. @param RequireCollapseToVert if >= 0 and after constraints/etc the vertex we will collapse "to" cannot be this vertex, do not collapse
- L417 _protected prototype_ `bool RemoveIsolatedTriangle(int tID);` — Remove an isolated triangle. @return false if the triangle shares a vertex with another triangle
- L421 _protected prototype_ `virtual void OnEdgeCollapse(int edgeID, int va, int vb, const FDynamicMesh3::FEdgeCollapseInfo& collapseInfo);` — subclasses can override this to implement custom behavior...
- L424 _protected prototype_ `virtual void OnRemoveIsolatedTriangle(int tId);` — subclasses can override this to implement custom behavior...
- L427 _protected prototype_ `virtual void FullProjectionPass();` — Project vertices onto projection target.
- L429 _protected prototype_ `virtual void ProjectVertex(int vID, IProjectionTarget* targetIn);`
- L432 _protected prototype_ `virtual FVector3d GetProjectedCollapsePosition(int vid, const FVector3d& vNewPos);` — used by collapse-edge to get projected position for new vertex
- L434 _protected prototype_ `virtual void ApplyToProjectVertices(const TFunction<void(int)>& apply_f);`
- L445 _protected prototype_ `bool CheckIfCollapseWithinGeometricTolerance(int vid, int vother, const FVector3d& newv, int tc, int td);` — Check if edge collapse would violate geometric error criteria @param vid first vertex of edge @param vother other vertex of edge @param newv new vertex position after collapse @param tc triangle on one side of edge @param td triangle on other side of edge
- L455 _protected prototype_ `bool CheckIfCollapseWithinEdgeConstraintsTolerance(int VKeep, int VRemove, const FVector3d& NewPosition, int TC);` — Check if edge collapse would violate edge constraint tolerance @param VKeep First edge vertex @param VRemove Other edge vertex @param NewPosition New vertex position after collapse @param TC triangle on one side of edge @return true if collapsing the edge won't move constrained edge midpoints too far from their projection targets
- L468 _protected member_ `int COUNT_COLLAPSES;` — profiling functions, turn on ENABLE_PROFILING to see output in console
- L469 _protected member_ `int COUNT_ITERATIONS;`
- L472 _protected function_ `virtual void ProfileBeginPass()`
- L485 _protected function_ `virtual void ProfileEndPass()`
- L498 _protected function_ `virtual void ProfileBeginOps()`
- L502 _protected function_ `virtual void ProfileEndOps()`
- L506 _protected function_ `virtual void ProfileBeginSetup()`
- L510 _protected function_ `virtual void ProfileEndSetup()`
- L515 _protected function_ `virtual void ProfileBeginProject()`
- L519 _protected function_ `virtual void ProfileEndProject()`
- L524 _protected function_ `virtual void ProfileBeginCollapse()`
- L528 _protected function_ `virtual void ProfileEndCollapse()`
- L535 _private prototype_ `void ApplyScalingAndRegularizationToVertexQuadric(FQuadricErrorType& Q, int32 VID, double AreaSum, FVector3d Normal);`

#### enum `UE::Geometry::TMeshSimplification::ESimplificationCollapseModes`  
`enum class ESimplificationCollapseModes`  
_L72-77_
- L74 _public enumerator_ `MinimalQuadricPositionError = 0`
- L75 _public enumerator_ `MinimalExistingVertexError = 1`
- L76 _public enumerator_ `AverageVertexPosition = 2`

#### enum `UE::Geometry::TMeshSimplification::EGeometricErrorCriteria`  
`enum class EGeometricErrorCriteria`  
_L129-135_
- desc: Ways to measure geometric error
- L132 _public enumerator_ `None = 0` — No geometric error checking
- L134 _public enumerator_ `PredictedPointToProjectionTarget = 1` — Fixed envelope around projection target

#### enum `UE::Geometry::TMeshSimplification::ETargetModes`  
`enum class ETargetModes`  
_L245-251_
- L247 _public enumerator_ `TriangleCount = 0`
- L248 _public enumerator_ `VertexCount = 1`
- L249 _public enumerator_ `MinEdgeLength = 2`
- L250 _public enumerator_ `MaxError = 3`

#### struct `UE::Geometry::TMeshSimplification::QEdge`  
`struct QEdge`  
_L314-328_
- desc: internal class for priority queue
- L316 _public member_ `int eid;`
- L317 _public member_ `FQuadricErrorType q;`
- L318 _public member_ `FVector3d collapse_pt;`
- L320 _public function_ `QEdge()`
- L322 _public function_ `QEdge(int edge_id, const FQuadricErrorType& qin, const FVector3d& pt)`

#### struct `UE::Geometry::TMeshSimplification::FEdgeError`  
`struct FEdgeError`  
_L333-341_
- L335 _public member_ `float error;`
- L336 _public member_ `int eid;`
- L337 _public function_ `bool operator<(const FEdgeError& e2) const`

#### struct `UE::Geometry::TMeshSimplification::FCollapseInfo`  
`struct FCollapseInfo`  
_L390-394_
- desc: Optional additional info to support edge collapses in more configurations i.e. for tri ABC, if edge AB is not constrained, but AC and BC are, it is *sometimes* safe to collapse AB *if* we also remove constraints from vertex B and edges B(AC) after the collapse. (As long as B is not otherwise constrained)
- L392 _public member_ `TArray<int32, TInlineAllocator<2>> UnconstrainVIDs;`
- L393 _public member_ `TArray<int32, TInlineAllocator<2>> UnconstrainEIDs;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L540 _typedef_ `typedef TMeshSimplification< FAttrBasedQuadricErrord > FAttrMeshSimplification;` (scope `UE::Geometry`) — The simplifier
- L541 _typedef_ `typedef TMeshSimplification< FVolPresQuadricErrord > FVolPresMeshSimplification;` (scope `UE::Geometry`)
- L542 _typedef_ `typedef TMeshSimplification< FQuadricErrord > FQEMSimplification;` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/MeshSimplificationQuadrics.h` (Public)


#### struct `UE::Geometry::TQuadricAttributeData`  
`template <typename RealType> struct TQuadricAttributeData`  
_L24-73_
- desc: Corresponds to the additional, attribute-related terms added to the main quadrics (A, b, c) Tracking this allows computing the geometry quadric separately from the attribute quadric.
- L26 _public member_ `RealType Axx{0}, Axy{0}, Axz{0}, Ayy{0}, Ayz{0}, Azz{0};`
- L26 _public member_ `RealType Axx{0}, Axy{0}, Axz{0}, Ayy{0}, Ayz{0}, Azz{0};`
- L26 _public member_ `RealType Axx{0}, Axy{0}, Axz{0}, Ayy{0}, Ayz{0}, Azz{0};`
- L26 _public member_ `RealType Axx{0}, Axy{0}, Axz{0}, Ayy{0}, Ayz{0}, Azz{0};`
- L26 _public member_ `RealType Axx{0}, Axy{0}, Axz{0}, Ayy{0}, Ayz{0}, Azz{0};`
- L26 _public member_ `RealType Axx{0}, Axy{0}, Axz{0}, Ayy{0}, Ayz{0}, Azz{0};`
- L27 _public member_ `RealType bx{0}, by{0}, bz{0};`
- L27 _public member_ `RealType bx{0}, by{0}, bz{0};`
- L27 _public member_ `RealType bx{0}, by{0}, bz{0};`
- L28 _public member_ `RealType c{0};`
- L30 _public function_ `void Add(RealType Weight, const TQuadricAttributeData& Other)`
- L45 _public function_ `void AccumulateFromWedge(RealType AreaTerm, const TVector<RealType>& G, RealType D)` — Accumulate from wedge data during position quadric construction
- L60 _public function_ `RealType ComputeCorrection(const TVector<RealType>& P) const` — Compute the debug quadric correction term (to be subtracted from base evaluation)

#### struct `UE::Geometry::TQuadricNoAttributeData`  
`template <typename RealType> struct TQuadricNoAttributeData`  
_L77-87_
- desc: Empty policy for release builds - all operations compile away to nothing
- L79 _public function_ `void Add(RealType, const TQuadricNoAttributeData&)`
- L80 _public function_ `void AccumulateFromWedge(RealType, const TVector<RealType>&, RealType)`
- L82 _public function_ `RealType ComputeCorrection(const TVector<RealType>&) const`

#### class `UE::Geometry::TAttrBasedQuadricErrorV2`  
`template<typename RealType> class TAttrBasedQuadricErrorV2 : public TQuadricError<RealType>`  
_L105-544_
- inherits: `TQuadricError<RealType>`
- desc: Configurable attributes with separate topology (wedges) Volume preservation Plane (Garland/Heckbert) and triangle quadrics (Lindstrom/Turk), including probabilistic versions (Trettner/Kobbelt)
- L108 _protected typedef_ `using BaseStruct = TQuadricError<RealType>;`
- L110 _protected member_ `TQuadricAttributePolicy<RealType> AttributeData;` — compiles away if UE_GEOMETRY_QEM_EXTRA_ATTRIBUTE_DATA isn't defined
- L185 _protected member_ `constexpr static uint32 InlineAttrElements = 6;`
- L188 _protected member_ `TArray<FAttrWedgeQuadricData, TInlineAllocator<InlineAttrElements>> AttrWedgeQuadricDatas;` — 6 enough to hold Normals, Tangents (2x), VertexColor, 2 x UV
- L189 _protected member_ `TArray<int, TInlineAllocator<InlineAttrElements>> WedgeCount;`
- L193 _public typedef_ `using FAttrArray = TArray<TVector<RealType>, TInlineAllocator<InlineAttrElements>>;`
- L321 _public function_ `TAttrBasedQuadricErrorV2() : BaseStruct()` — empty quadric
- L327 _public function_ `TAttrBasedQuadricErrorV2(const TVector<RealType>& P0, const TVector<RealType>& P1, const TVector<RealType>& P2, const FOptions& Options) : BaseStruct()` — initialize a face quadric
- L351 _public function_ `TAttrBasedQuadricErrorV2(const TAttrBasedQuadricErrorV2& Q0, const TAttrBasedQuadricErrorV2& Q1) : BaseStruct(Q0, Q1)` — this should never be called. addition of vertex quadrics is not supported because it doesn't work for attribute wedges
- L366 _public function_ `TAttrBasedQuadricErrorV2(const TAttrBasedQuadricErrorV2& VertexQuadric0, const TAttrBasedQuadricErrorV2& VertexQuadric1, const TAttrBasedQuadricErrorV2* TriangleQuadricA, const TAttrBasedQuadricErrorV2* TriangleQuadricB, const int LocalEdgeIndexA, const int LocalEdgeIndexB, const RealType RemoveScale) : BaseStruct(VertexQuadric0, VertexQuadric1)` — initialize to an edge quadric given the two vertex quadrics at the end points of the edge and (up to two) face quadrics corresponding to the overlap of both the local edge indices correspond to the local edge index [0..3) of the shared edge within A and B respectively.
- L390 _public function_ `inline static TAttrBasedQuadricErrorV2 Zero()`
- L395 _public prototype_ `void AccumulateFaceQuadric(const int CornerIdx, RealType TriArea, RealType Weight, const TAttrBasedQuadricErrorV2& FaceQuadric);` — If this is a vertex, accumulate a face quadric on to it. \param CornerIdx local vertex index [0..3) of the center vertex within the triangle of the face quadric
- L400 _public prototype_ `void RemoveFaceQuadric(const int CornerIdx, RealType TriArea, RealType RemoveScale, const TAttrBasedQuadricErrorV2& FaceQuadric);` — If this is a vertex, remove a face quadric from it (undoing accumulate face quadric) \param CornerIdx local vertex index [0..3) of the center vertex within the triangle of the face quadric
- L402 _public function_ `void Scale(RealType Wt)`
- L415 _public prototype_ `bool OptimalPoint(UE::Math::TVector<RealType>& OutResult, RealType MinThresh = 1000.0*TMathUtil<RealType>::Epsilon) const;` — The optimal point minimizing the quadric error with respect to a volume conserving constraint
- L418 _public prototype_ `FAttrArray ComputeAttributes(const TVector<RealType>& P) const;` — Scale-correct attributes
- L421 _public function_ `RealType Evaluate(const TVector<RealType>& P) const` — combination of geometry and attribute quadrics
- L428 _public prototype_ `RealType EvaluateGeometryOnly(const TVector<RealType>& P) const;` — geometry quadrics only
- L431 _public prototype_ `bool ValidateArea() const;` — For each attribute, checks whether the area of all wedges adds up to the total area of the quadric.
- L434 _public function_ `RealType GetArea() const` — actual area, not the scaling term
- L440 _public function_ `bool CanCollapse() const` — is this a valid edge-collapse quadric?
- L442 _public function_ `int GetAttributeCount() const`
- L447 _public function_ `int GetWedgeCount(int AttributeIndex) const`
- L452 _public function_ `bool IsWedgeActive(int WedgeIndex) const`
- L457 _public function_ `const FIndex3i& GetWedgeAttributeIndex(int WedgeIndex) const`
- L465 _protected prototype_ `template <typename SolverType> bool OptimalPointImpl(TVector<RealType>& OutResult) const;`
- L467 _protected prototype_ `FAttrArray ComputeScaledAttributes(const TVector<RealType>& P) const;`
- L469 _protected prototype_ `RealType Evaluate(const TVector<RealType>& P, const FAttrArray& ScaledWedgeAttrs) const;`
- L471 _protected prototype_ `bool MergeVertexQuadricsToEdgeQuadric(const TAttrBasedQuadricErrorV2& VertexQuadric0, const TAttrBasedQuadricErrorV2& VertexQuadric1, const TAttrBasedQuadricErrorV2* TriangleQuadricA, const TAttrBasedQuadricErrorV2* TriangleQuadricB, const int LocalEdgeIndexA, const int LocalEdgeIndexB, const RealType RemoveScale);`
- L480 _protected function_ `void AAddOuterProduct(const TVector<RealType>& V)` — Set A to rank-1 matrix V \otimes V = V V^T
- L490 _protected function_ `void AAddCrossProductSquaredTranspose(const TVector<RealType>& V)`
- L505 _protected function_ `void AScale(const RealType Alpha)`
- L516 _protected prototype_ `void MakeProbabilisticPlaneQuadric( const TVector<RealType>& P0, const TVector<RealType>& P1, const TVector<RealType>& P2, const RealType SigmaN);`
- L522 _protected prototype_ `void MakeTriangleQuadric( const TVector<RealType>& P0, const TVector<RealType>& P1, const TVector<RealType>& P2);`
- L527 _protected prototype_ `void MakeProbabilisticTriangleQuadric( const TVector<RealType>& P0, const TVector<RealType>& P1, const TVector<RealType>& P2, const RealType SigmaN);`
- L539 _protected member_ `TVector<RealType> GVol { 0. };` — See: http://hhoppe.com/newqem.pdf or https://www.cc.gatech.edu/~turk/my_papers/memless_vis98.pdf volume constraint: dot(g_vol,x) = DVol The volume of the tetrahedron spanned by the base triangle (v0, v1, v2) and x is 1/6 * det(v1-v0 v2-v0 x-v0) = 1/6 dot((v1-v0) ^ (v2-v0), x-v0) Summed over all triangles and setting to 0: dot(sum_t N, x) = sum(dot(N, v0)) with N the scaled normal (v1-v0) ^ (v2-v0)
- L540 _protected member_ `RealType DVol { 0. };`
- L541 _protected member_ `RealType Area { 0. };` — accumulated area, this is always used for scaling the volume constraint.
- L542 _protected member_ `RealType TotalAreaTerm { 0. };` — accumulated area or area^2, depending on which variant is used. This is used for scaling the quadric.
- L543 _protected member_ `bool bCanCollapse { false };`
- L547 _function_ `template <typename RealType> inline bool TAttrBasedQuadricErrorV2<RealType>::MergeVertexQuadricsToEdgeQuadric( const TAttrBasedQuadricErrorV2& VertexQuadric0, const TAttrBasedQuadricErrorV2& VertexQuadric1, const TAttrBasedQuadricErrorV2* TriangleQuadricA, const TAttrBasedQuadricErrorV2* TriangleQuadricB, const int LocalEdgeIndexA, const int LocalEdgeIndexB, const RealType RemoveScale)`
- L681 _function_ `template <typename RealType> inline void TAttrBasedQuadricErrorV2<RealType>::AccumulateFaceQuadric( const int CornerIdx, RealType TriArea, RealType Weight, const TAttrBasedQuadricErrorV2& FaceQuadric)`
- L777 _function_ `template <typename RealType> inline void TAttrBasedQuadricErrorV2<RealType>::RemoveFaceQuadric( const int CornerIdx, RealType TriArea, RealType RemoveScale, const TAttrBasedQuadricErrorV2& FaceQuadric)`
- L836 _function_ `template <typename RealType> inline void TAttrBasedQuadricErrorV2<RealType>::MakeProbabilisticPlaneQuadric( const TVector<RealType>& P0, const TVector<RealType>& P1, const TVector<RealType>& P2, const RealType SigmaN)`
- L878 _function_ `template <typename RealType> inline void TAttrBasedQuadricErrorV2<RealType>::MakeTriangleQuadric( const TVector<RealType>& P0, const TVector<RealType>& P1, const TVector<RealType>& P2)`
- L902 _function_ `template <typename RealType> inline void TAttrBasedQuadricErrorV2<RealType>::MakeProbabilisticTriangleQuadric( const TVector<RealType>& P0, const TVector<RealType>& P1, const TVector<RealType>& P2, const RealType Sigma)`
- L953 _function_ `template <typename RealType> inline TAttrBasedQuadricErrorV2<RealType>::FAttrArray TAttrBasedQuadricErrorV2<RealType>::ComputeScaledAttributes( const TVector<RealType>& P) const`
- L979 _function_ `template <typename RealType> inline TAttrBasedQuadricErrorV2<RealType>::FAttrArray TAttrBasedQuadricErrorV2<RealType>::ComputeAttributes(const TVector<RealType>& P) const`
- L991 _function_ `template <typename RealType> inline RealType TAttrBasedQuadricErrorV2<RealType>::Evaluate( const TVector<RealType>& P, const FAttrArray& ScaledWedgeAttrs) const`
- L1048 _function_ `template <typename RealType> inline RealType TAttrBasedQuadricErrorV2<RealType>::EvaluateGeometryOnly( const TVector<RealType>& P) const`
- L1064 _function_ `template <typename RealType> inline bool TAttrBasedQuadricErrorV2<RealType>::ValidateArea() const`

#### struct `UE::Geometry::TAttrBasedQuadricErrorV2::FAttrWedgeQuadricData`  
`struct FAttrWedgeQuadricData`  
_L112-183_
- L117 _public member_ `TVector<RealType> G[3];` — g and d terms, as described in http://hhoppe.com/newqem.pdf NOTE: they are scaled by the area term for face quadrics and accumulated accordingly for vertex and edge quadrics.
- L118 _public member_ `TVector<RealType> D;`
- L120 _public member_ `FIndex3i AttrTri;` — attribute layer topology
- L121 _public member_ `RealType TotalAreaTerm { 0. };` — sum of triangles contributing to wedge, or sum squared
- L122 _public member_ `RealType AttrWeight { 0. };`
- L124 _public function_ `void Scale(const RealType Wt)`
- L132 _public function_ `void AccumulateQuadricData(const FAttrWedgeQuadricData& FaceQuadricData)`
- L144 _public function_ `void RemoveQuadricData(const FAttrWedgeQuadricData& FaceQuadricData)`
- L156 _public function_ `void AccumulateToPositionQuadric(TAttrBasedQuadricErrorV2& FaceQuadric) const`

#### enum `UE::Geometry::TAttrBasedQuadricErrorV2::EQuadricVariant`  
`enum class EQuadricVariant`  
_L195-199_
- L197 _public enumerator_ `PlaneQuadric` — classic Garland-Heckbert squared distance to plane
- L198 _public enumerator_ `TriangleQuadric` — Lindstrom-Turk volumetric error

#### class `UE::Geometry::TAttrBasedQuadricErrorV2::FScopedAttributeDataBuilder`  
`class FScopedAttributeDataBuilder`  
_L202-288_
- desc: Helper class to register attributes to the quadric on construction
- L205 _private function_ `void CalcGandD(const FVector3f& W0, const FVector3f& W1, const FVector3f& W2, TVector<RealType> G[3], TVector<RealType>& D) const`
- L228 _public function_ `FScopedAttributeDataBuilder( TAttrBasedQuadricErrorV2& InQuadric, const TVector<RealType>& InP0, const TVector<RealType>& InP1, const TVector<RealType>& InP2, const TVector<RealType>& InN, const RealType ScaleCorrection) : Quadric(InQuadric), P0(InP0)`
- L252 _public function_ `void AddWedgeAttribute(const FIndex3i& AttrTri, const FVector3f& W0, const FVector3f& W1, const FVector3f& W2, const RealType AttrWeight)`
- L277 _public function_ `void AddMissingWedgeAttribute()`
- L283 _private member_ `TAttrBasedQuadricErrorV2& Quadric;` — face quadric
- L284 _private member_ `const TVector<RealType>& P0;`
- L285 _private member_ `FMatrix3d CoBasisMatrix;`
- L286 _private member_ `bool IsValid { false };`
- L287 _private member_ `RealType AttributeScaling { 1. };`

#### struct `UE::Geometry::TAttrBasedQuadricErrorV2::FOptions`  
`struct FOptions`  
_L290-318_
- L292 _public member_ `EQuadricVariant QuadricVariant { EQuadricVariant::PlaneQuadric };`
- L297 _public member_ `RealType SigmaN { 0. };` — When positive, will trigger the probabilistic quadrics, leading to regularized results that are less sensitive to local noise and improve behavior in flat regions.
- L309 _public member_ `RealType ScaleCorrection { 1. };` — Used to rebalance the optimization weight for geometry and attributes when scaling objects. The behavior of the simplifier is not scale invariant. Scaling an object by X will impact the geometry terms X^2 times more than it will impact the attributes. Setting this value to X, should then give the same behavior as if the the object was scaled down by a factor of X and rescaled back up after simplification. It is also applied to edge quadric scaling which is weighted by edge-length instead of area.
- L313 _public member_ `RealType NormalAttributeWeight { 16.0 };` — currently mimicking FQuadricSimplifierMeshReduction, see ReduceMeshDescription.
- L314 _public member_ `RealType TangentAttributeWeight { 0.1 };`
- L315 _public member_ `RealType ColorAttributeWeight { 0.1 };`
- L316 _public member_ `RealType TexCoordAttributeWeight { 0.5 };`
- L317 _public member_ `RealType WeightLayerWeight { 0.0 };`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L94 _typedef_ `template<typename RealType> using TQuadricAttributePolicy = TQuadricAttributeData<RealType>;` (scope `UE::Geometry`)
- L97 _typedef_ `template<typename RealType> using TQuadricAttributePolicy = TQuadricNoAttributeData<RealType>;` (scope `UE::Geometry`)
- L1092 _typedef_ `using FAttrBasedQuadricErrorV2d = TAttrBasedQuadricErrorV2<double>;` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/MeshWeights.h` (Public)


#### class `UE::Geometry::FMeshWeights`  
`class FMeshWeights`  
_L20-114_
- desc: FMeshWeights implements various techniques for computing local weights of a mesh, for example one-ring weights like Cotangent or Mean-Value.
- L28 _public prototype_ `static FVector3d UniformCentroid(const FDynamicMesh3& Mesh, int32 VertexIndex);` — Compute uniform centroid of a vertex one-ring. These weights are strictly positive and all equal to 1 / valence
- L34 _public prototype_ `static FVector3d UniformCentroid(const FDynamicMesh3& Mesh, int32 VertexIndex, TFunctionRef<FVector3d(int32)> VertexPositionFunc );` — Compute uniform centroid of a vertex one-ring. These weights are strictly positive and all equal to 1 / valence
- L40 _public prototype_ `static FVector3d FilteredUniformCentroid(const FDynamicMesh3& Mesh, int32 VertexIndex, TFunctionRef<FVector3d(int32)> VertexPositionFunc, TFunctionRef<bool(int32)> VertexFilterFunc);` — Compute uniform centroid of a subset of vertex one-ring (eg boundary vertices) These weights are strictly positive and all equal to 1 / valence
- L46 _public prototype_ `static FVector3d MeanValueCentroid(const FDynamicMesh3& Mesh, int32 VertexIndex, double WeightClamp = FMathf::MaxReal);` — Compute mean-value centroid of a vertex one-ring. These weights are strictly positive.
- L52 _public prototype_ `static FVector3d MeanValueCentroid(const FDynamicMesh3& Mesh, int32 VertexIndex, TFunctionRef<FVector3d(int32)> VertexPositionFunc, double WeightClamp = FMathf::MaxReal);` — Compute mean-value centroid of a vertex one-ring. These weights are strictly positive.
- L59 _public prototype_ `static FVector3d CotanCentroid(const FDynamicMesh3& Mesh, int32 VertexIndex);` — Compute cotan-weighted centroid of a vertex one-ring. These weights are numerically unstable if any of the triangles are degenerate. We catch these problems and return input vertex as centroid
- L66 _public prototype_ `static FVector3d CotanCentroid(const FDynamicMesh3& Mesh, int32 VertexIndex, TFunctionRef<FVector3d(int32)> VertexPositionFunc);` — Compute cotan-weighted centroid of a vertex one-ring. These weights are numerically unstable if any of the triangles are degenerate. We catch these problems and return input vertex as centroid
- L76 _public prototype_ `static FVector3d CotanCentroidSafe(const FDynamicMesh3& Mesh, int32 VertexIndex, double DegenerateTol = 100.0, bool* bFailedToUniform = nullptr);` — Compute cotan-weighted centroid of a vertex one-ring, with some weight analysis/clamping to avoid vertices getting "stuck" in explicit integration/iterations. If failure is detected, Uniform centroid is returned, which does cause some tangential flow @param DegenerateTol if any weights are larger than this value, return uniform weights instead. Should be > 1. @param bFailedToUniform will be set to true if non-null and result was clamped
- L84 _public prototype_ `static FVector3d CotanCentroidSafe(const FDynamicMesh3& Mesh, int32 VertexIndex, TFunctionRef<FVector3d(int32)> VertexPositionFunc, double DegenerateTol = 100.0, bool* bFailedToUniform = nullptr);` — Compute cotan-weighted centroid of a vertex one-ring, with some weight analysis/clamping to avoid vertices getting "stuck" in explicit integration/iterations. If failure is detected, Uniform centroid is returned, which does cause some tangential flow @param DegenerateTol if any weights are larger than this value, return uniform weights instead. Should be > 1. @param bFailedToUniform will be set to true if non-null and result was clamped
- L95 _public prototype_ `static void CotanWeightsBlendSafe(const FDynamicMesh3& Mesh, int32 VertexIndex, TFunctionRef<void(int32,double)> BlendingFunc, double DegenerateTol = 100.0, bool* bFailedToUniform = nullptr);` — Compute cotan-weighted blend for a vertex one-ring, with some weight analysis/clamping to avoid vertices getting "stuck" in explicit integration/iterations. If failure is detected, Uniform centroid is returned, which does cause some tangential flow. Equivalent to CotanCentroidSafe() if the weights are used to blend vertex positions, but can be used to weight other properties. @param BlendingFunc BlendingFunc(NbrVertexID, Weight) will be called for every one-ring neighbour vertex @param DegenerateTol if any weights are larger than this value, return uniform weights instead. Should be > 1. @param bFailedToUniform will be set to true if non-null and result was clamped
- L103 _public prototype_ `static double VoronoiArea(const FDynamicMesh3& Mesh, int32 VertexIndex);` — Compute the Mixed Voronoi Area associated with a vertex. Based on Fig 4 from "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds", Meyer et al 2002,
- L109 _public prototype_ `static double VoronoiArea(const FDynamicMesh3& Mesh, int32 VertexIndex, TFunctionRef<FVector3d(int32)> VertexPositionFunc);` — Compute the Mixed Voronoi Area associated with a vertex. Based on Fig 4 from "Discrete Differential-Geometry Operators for Triangulated 2-Manifolds", Meyer et al 2002,
- L113 _protected prototype_ `FMeshWeights() = delete;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/NormalFlowRemesher.h` (Public)


#### class `UE::Geometry::FNormalFlowRemesher`  
`class FNormalFlowRemesher : public FQueueRemesher`  
_L20-143_
- inherits: `FQueueRemesher`
- desc: Remeshing with "face aligned projection". This approach to projection attempts to preserve sharp features in the mesh by aligning triangle normals with normals from the original mesh during the projection pass. This class also performs a pass of edge flips aimed at further aligning triangle normals to their originals. This can be helpful in fixing the occasional single "bad edge" along a sequence of feature edges.
- L24 _public function_ `FNormalFlowRemesher(FDynamicMesh3* MeshIn) : FQueueRemesher(MeshIn)`
- L27 _public member_ `int FaceProjectionPassesPerRemeshIteration = 1;` — During each call to RemeshIteration, do this many passes of face-aligned projection
- L30 _public member_ `int NumExtraProjectionIterations = 5;` — Additional projection iterations after the usual remesh step
- L33 _public member_ `double SurfaceProjectionSpeed = 0.2;` — drag on surface projection
- L36 _public member_ `double NormalAlignmentSpeed = 0.2;` — drag on normal alignment
- L40 _public member_ `bool bSmoothInFillAreas = true;` — Control whether or not we want to apply mesh smoothing in "free" areas that have not projected to target surface. This smoothing is on applied in the ExtraProjections Iterations
- L43 _public member_ `float FillAreaDistanceMultiplier = 0.25;` — This is used as a multiplier on MaxEdgeLength to determine when we identify points as being in "free" areas
- L46 _public member_ `float FillAreaSmoothMultiplier = 0.25;` — This is used as a multiplier on the Remesher smoothing rate, applied to points identified as being in "free" areas
- L49 _public member_ `int MaxTriangleCount = 0;` — cap on triangle count, to prevent runaway mesh messes. Ignored if zero.
- L52 _public function_ `void BasicRemeshPass() override` — "Outer loop" for all remeshing operations
- L58 _public member_ `bool bEnableParallelEdgeFlipPass = true;` — Gather candidates for edge flipping in parallel, then do the actual flips sequentially
- L65 _protected prototype_ `void RemeshWithFaceProjection();` — Do remeshing with face-aligned projection. During the Projection step of RemeshIteration, perform N passes of face-aligned projection (N = FaceProjectionPassesPerRemeshIteration). Additionally, do M passes of face-aligned projection after remeshing has finished (M = NumExtraProjectionIterations).
- L68 _protected prototype_ `void TrackedFaceProjectionPass(double& MaxDistanceMoved, bool bIsTuningIteration);` — Perform face-aligned projection onto the target mesh. Queue edges whose lengths change because of it.
- L69 _protected prototype_ `void TrackedFaceProjectionPass_Serial(double& MaxDistanceMoved, bool bIsTuningIteration);`
- L72 _protected function_ `void TrackedFullProjectionPass(bool bParallel) override` — This is called during RemeshIteration
- L90 _protected member_ `TArray<double> TempWeightBuffer;`
- L93 _protected member_ `TArray<double> ProjectionWeightBuffer;` — Per triangle-vertex weights for face projection pass. (Size >= 3 * MaxTriangleID)
- L96 _protected member_ `TArray<FVector3d> ProjectionVertexBuffer;` — Per triangle-vertex projection positions for face projection pass. (Size >= 3 * MaxTriangleID)
- L100 _protected function_ `void InitializeVertexBufferForFacePass()` — Similar to InitializeVertexBufferForPass, but also initialize the additional per-vertex weight buffer
- L139 _protected prototype_ `bool EdgeFlipWouldReduceNormalError(int EdgeID, double BadEdgeErrorThreshold = 0.01, double ImprovementRatioThreshold = 0.75) const;` — Test to see if flipping an edge would improve "normal error". Normal error for a triangle is: 0.5 * (1.0 - TriangleNormal \cdot ProjectedNormal), where ProjectedNormal is the normal of the triangle returned by finding the closest point on ProjTarget. The normal error for an edge is the sum of errors for the edge's incident triangles. @param EdgeID Edge to consider. @param BadEdgeErrorThreshold Only edges with this error or greater are candidates for flipping. @param ImprovementRatioThreshold New edge must have error less than old edge error times this ratio. @return True iff (CurrentEdgeError > BadEdgeErrorThreshold) and (NewEdgeError < ImprovementRatioThreshold * CurrentEdgeError)
- L142 _protected prototype_ `void TrackedEdgeFlipPass();` — Flip all edges for which EdgeFlipWouldReduceNormalError returns true

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DYNAMICMESH_API`
- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/AverageOverlayToVertices.h` (Public)


#### class `UE::Geometry::FAverageOverlayToVertices`  
`class FAverageOverlayToVertices`  
_L26-75_
- desc: Compute the per-vertex values which are the weighted average of all vertex element values stored in the overlay.
- L35 _public member_ `bool bUseParallel = true;` — Enable/disable multi-threading.
- L38 _public member_ `TArray<int32> Selection;` — Array of vertex IDs whose vertices will be affected.
- L48 _public member_ `ETriangleWeight TriangleWeight = ETriangleWeight::AngleArea;`
- L52 _protected member_ `const FDynamicMesh3* Mesh;`
- L56 _public prototype_ `FAverageOverlayToVertices(const FDynamicMesh3& InMesh);`
- L58 _public prototype_ `virtual ~FAverageOverlayToVertices() = default;`
- L72 _public prototype_ `template<typename RealType, int ElementSize> bool AverageOverlay(const TDynamicMeshOverlay<RealType, ElementSize>* Overlay, TArray<RealType>& VertexValues, TArray<bool>& HasElements);` — Compute the per-vertex values which are the weighted average of all vertex element values stored in the overlay. @param Overlay      Overlay containing the element values to be averaged. @param VertexValues Array of per-vertex averaged element values. The size is either equal to the ElementSize*Mesh.MaxVertexID() or ElementSize*Selection.Num() if Selection is not empty. @param HasElements  Array of per-vertex flags, indicating if the vertex had at least one element set in the overlay and contains correct averaged value. @return true on success, false otherwise

#### enum `UE::Geometry::FAverageOverlayToVertices::ETriangleWeight`  
`enum class ETriangleWeight : uint8`  
_L41-47_
- desc: The type of weight used for each element.
- L43 _public enumerator_ `Uniform` — all elements are weighted equally
- L44 _public enumerator_ `Angle = 0` — use the angle between the edges that share the element
- L45 _public enumerator_ `Area = 1` — use the area of the triangle containing the element
- L46 _public enumerator_ `AngleArea = 2` — use the angle weighted by the area

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/DetectExteriorVisibility.h` (Public)


#### struct `UE::Geometry::FExteriorVisibilitySampling`  
`struct FExteriorVisibilitySampling`  
_L15-63_
- desc: Parameters controlling how exterior visiblity is tested
- L19 _public member_ `double SamplingDensity = 1.0;` — Approximate spacing between triangle samples used for visibility tests Set a smaller value to increase the number of visibility samples per triangle, which can give more accurate visibility results
- L22 _public member_ `bool bDoubleSided = false;` — Whether to treat faces as double-sided
- L25 _public member_ `int32 NumSearchDirections = 128;` — Number of directions to test for visibility
- L28 _public member_ `bool bMarkDegenerateAsVisible = true;` — Whether to mark degenerate tris as visible. If bPerPolyGroup is true, this setting controls the classification of PolyGroups that *only* have degenerate tris.
- L35 _public prototype_ `static void ComputePerTriangleOcclusion(const FDynamicMesh3& Mesh, TArray<bool>& OutTriOccluded, bool bPerPolyGroup, const FExteriorVisibilitySampling& SamplingParameters, TArrayView<const bool> SkipTris = TArrayView<const bool>());` — Compute per-triangle visibility array for a triangle mesh @param OutTriOccluded		For each valid triangle ID, OutTriOccluded[ID] will be true if that triangle is hidden, false if it is visible @param bPerPolyGroup			If true, visiblity will be determined on a per group basis: If any triangle in a group is visible, the whole group will be marked as not-occluded @param SamplingParameters	Parameters controlling how exterior visiblity is tested @param SkipTris				True for triangles do not need visibility testing (will be marked as not occluded). If empty, no triangles will be skipped.
- L44 _public prototype_ `static void ComputePerTriangleOcclusion(const FDynamicMesh3& Mesh, TFunctionRef<bool(int32)> IsTriTransparent, TArray<bool>& OutTriOccluded, bool bPerPolyGroup, const FExteriorVisibilitySampling& SamplingParameters, TArrayView<const bool> SkipTris = TArrayView<const bool>());` — Compute per-triangle visibility array for a triangle mesh, with support for transparent (non-occluding) triangles @param IsTriTransparent		Indicator function returns true if a triangle is 'transparent' (should not occlude, but can still be occluded) @param OutTriOccluded		For each valid triangle ID, OutTriOccluded[ID] will be true if that triangle is hidden, false if it is visible @param bPerPolyGroup			If true, visiblity will be determined on a per group basis: If any triangle in a group is visible, the whole group will be marked as not-occluded @param SamplingParameters	Parameters controlling how exterior visiblity is tested @param SkipTris				True for triangles do not need visibility testing (will be marked as not occluded). If empty, no triangles will be skipped.
- L57 _public prototype_ `static void ComputePerTriangleOcclusionFromDirections(const FDynamicMesh3& Mesh, TFunctionRef<bool(int32)> IsTriTransparent, TArray<bool>& OutTriOccluded, bool bPerPolyGroup, TConstArrayView<FVector3d> InitialTestDirections, TConstArrayView<FVector3d> FullTestDirections, bool bAlsoSampleTriangleNormalDirections, const FExteriorVisibilitySampling& SamplingParameters, TArrayView<const bool> SkipTris = TArrayView<const bool>());` — Compute per-triangle visibility array for a triangle mesh, with support for transparent (non-occluding) triangles, and with custom sampling directions (ignoring the NumSearchDirections parameter) @param IsTriTransparent		Indicator function returns true if a triangle is 'transparent' (should not occlude, but can still be occluded) @param OutTriOccluded		For each valid triangle ID, OutTriOccluded[ID] will be true if that triangle is hidden, false if it is visible @param InitialViewTestDirections Initial directions to test for triangle visibility/occlusion. Note: directions are from mesh surface toward outside. Use this to specify a small set of directions (e.g., cardinal directions) to test per triangle before using the full set, which can help improve the algorithm performance. @param FullViewTestDirections Full set of directions to test for triangle visibility/occlusion. Note: directions are from mesh surface toward outside @param bAlsoSampleTriangleNormalDirections Whether to also sample in the normal direction for each triangle. Can be disabled for greater control over the sampling directions. @param bPerPolyGroup			If true, visiblity will be determined on a per group basis: If any triangle in a group is visible, the whole group will be marked as not-occluded @param SamplingParameters	Parameters controlling how exterior visiblity is tested @param SkipTris				True for triangles do not need visibility testing (will be marked as not occluded). If empty, no triangles will be sk
- L62 _public prototype_ `static TArray<FVector3d> GetRestrictedViewDirections(TConstArrayView<FVector3d> RestrictViewDirections, double RestrictViewAngle, int32 NumSphereSamples);`

#### class `UE::Geometry::FDetectPerDynamicMeshExteriorVisibility`  
`class FDetectPerDynamicMeshExteriorVisibility`  
_L66-102_
- desc: Determine which meshes are visible from exterior views of a list of meshes
- L86 _public member_ `TArray<FDynamicMeshInstance> Instances;` — Instances for which we need to determine visibility
- L89 _public member_ `TArray<FDynamicMeshInstance> OccludeInstances;` — Instances which occlude visibility, but for which we don't need to determine visibility
- L92 _public member_ `TArray<FDynamicMeshInstance> TransparentInstances;` — Instances which do not occlude visibility, but for which we do need to determine visibility
- L95 _public member_ `FExteriorVisibilitySampling SamplingParameters;` — Parameters controlling how the triangles are sampled for visibility
- L100 _public prototype_ `void ComputeHidden(TArray<bool>& OutIsOccluded, TArray<bool>* OutTransparentIsOccluded = nullptr);` — Compute which source meshes are hidden @param OutIsOccluded				Indicate if each mesh in Instances is hidden (true) or visible (false) @param OutTransparentIsOccluded	If provided, indicate if each mesh in TransparentInstances is hidden (true) or visible (false). If not provided, TransparentInstances are not tested.

#### struct `UE::Geometry::FDetectPerDynamicMeshExteriorVisibility::FDynamicMeshInstance`  
`struct FDynamicMeshInstance`  
_L70-79_
- L72 _public member_ `const FDynamicMesh3* SourceMesh;`
- L73 _public member_ `FTransformSequence3d Transforms;`
- L74 _public prototype_ `FDynamicMeshInstance() = default;`
- L75 _public function_ `FDynamicMeshInstance(FDynamicMesh3* Mesh, const FTransform& InTransform) : SourceMesh(Mesh)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/DisplaceMesh.h` (Public)


#### class `UE::Geometry::FDisplaceMesh`  
`class FDisplaceMesh`  
_L16-48_
- L21 _public function_ `inline static void DisplaceMeshWithVertexWeights(FDynamicMesh3& Mesh, const FMeshNormals& Normals, const TArray<float>& VertexWeights, float Intensity)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)
- L32 _function_ `` (scope `UE::Geometry::FDisplaceMesh::DisplaceMeshWithVertexWeights`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/ExtrudeBoundaryEdges.h` (Public)


#### class `UE::Geometry::FExtrudeBoundaryEdgesFixLayout`  
`class FExtrudeBoundaryEdgesFixLayout`  
_L21-25_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L24 _public prototype_ `virtual ~FExtrudeBoundaryEdgesFixLayout() = default;`

#### class `UE::Geometry::FExtrudeBoundaryEdges`  
`class FExtrudeBoundaryEdges : public FExtrudeBoundaryEdgesFixLayout`  
_L27-145_
- inherits: `FExtrudeBoundaryEdgesFixLayout`
- L30 _public typedef_ `using FFrame3d = UE::Geometry::FFrame3d;`
- L73 _public member_ `FDynamicMesh3* Mesh;` — The mesh that we are modifying
- L76 _public member_ `TArray<int32> InputEids;` — The edges we're extruding
- L79 _public member_ `bool bUsePerVertexExtrudeFrames = true;` — Whether to calculate local extrude frames and supply them to OffsetPositionFunc
- L82 _public member_ `bool bAssignAnyBoundaryNeighborToUnmatched = false;` — When generating extrude frames, whether to use unselected neighbors for setting the frame.
- L89 _public member_ `TFunction<FVector3d(const FVector3d& Position, const FExtrudeFrame& ExtrudeFrame, int32 SourceVid)> OffsetPositionFunc = [this](const FVector3d& Position, const FExtrudeFrame& ExtrudeFrame, int32 SourceVid) { return ExtrudeFrame.FromFramePoint(FVector3d(this->DefaultOffsetDistance, 0, 0)); };` — Function queried for new vertex positions. ExtrudeFrame origin is Position, unless it is not initialized due to bUsePerVertexExtrudeFrames being false. The default given here assumes that bUsePerVertexExtrudeFrames is true, and extrudes along the X axis of the extrude frame.
- L91 _public function_ ``
- L99 _public member_ `double ScalingAdjustmentLimit = 1.0;` — If greater than 1, maximal amount by which a vertex can be moved in an attempt to keep edges parallel to original edges while extruding. This "movement" is done by scaling the X axis of the extrude frame.
- L105 _public member_ `TOptional<TArray<int32>> GroupsToSetPerEid;` — Optional mapping, 1:1 with Eids, that gives the group id to use for each generated quad. Otherwise all generated triangles will be given the same new group id.
- L108 _public member_ `double DefaultOffsetDistance = 1.0;` — Used in the default OffsetPositionFunc.
- L112 _public member_ `TArray<int32> NewTids;` — Outputs:
- L113 _public member_ `TArray<int32> NewExtrudedEids;`
- L116 _public prototype_ `FExtrudeBoundaryEdges(FDynamicMesh3* mesh);`
- L118 _public prototype_ `virtual ~FExtrudeBoundaryEdges() = default;`
- L124 _public prototype_ `virtual bool Apply(FProgressCancel* Progress);` — Apply the operation to the input mesh. @return true if the algorithm succeeds
- L132 _public prototype_ `static bool GetInputEdgePairings( const FDynamicMesh3& Mesh, TArray<int32>& InputEids, bool bAssignAnyBoundaryNeighborToUnmatched, TArray<FNewVertSourceData>& NewVertDataOut, TMap<int32, FIndex2i>& EidToIndicesIntoNewVertsOut);` — Pairs up edges across vertices to help in extrusion frame calculation. Public because it is used by the extrude edges activity to find an operational space for the gizmos used to set extrude distance. @return false if there is an error.
- L142 _public prototype_ `static bool GetExtrudeFrame(const FDynamicMesh3& Mesh, int32 Vid, int32 IncomingEid, int32 OutgoingEid, FExtrudeFrame& ExtrudeFrameOut, double ScalingLimit);` — Gets an extrude frame given a vert and its neighboring boundary edges. Like GetInputEdgePairings, public because it is used to set up UX for setting extrude distance. @return false if there is an error.

#### struct `UE::Geometry::FExtrudeBoundaryEdges::FExtrudeFrame`  
`struct FExtrudeFrame`  
_L36-60_
- desc: Represents a frame where the axes might not be unit scaled (but are still orthogonal). Allows vertices to adjust the extrusion distance along one of their extrusion frame axes when trying to keep edges parallel. When using extrusion frames, vertices will be moved in the XZ plane, usually along X.
- L38 _public function_ `FExtrudeFrame()`
- L40 _public function_ `FExtrudeFrame(const FFrame3d& FrameIn) : Frame(FrameIn)`
- L43 _public function_ `FExtrudeFrame(const FFrame3d& FrameIn, const FVector3d& InFrameScaleDirection, double ScalingIn) : Frame(FrameIn) , InFrameScaleDirection(InFrameScaleDirection) , Scaling(ScalingIn)`
- L49 _public prototype_ `FVector3d FromFramePoint(FVector3d FramePoint) const;`
- L51 _public prototype_ `FVector3d ToFramePoint(FVector3d WorldPoint) const;`
- L53 _public member_ `FFrame3d Frame;`
- L58 _public member_ `TOptional<FVector3d> InFrameScaleDirection;` — Extra scaling direction used to support adjusting extruded vertices when trying to keep edges parallel. The input is scaled along this axis in frame space. See comment inside ExtrudeBoundaryEdgesLocals::GetExtrudeFrameAtVertex.
- L59 _public member_ `double Scaling = 1.0;`

#### struct `UE::Geometry::FExtrudeBoundaryEdges::FNewVertSourceData`  
`struct FNewVertSourceData`  
_L63-68_
- desc: Data needed to create a new vert and its extrude frame
- L65 _public member_ `int32 SourceVid = IndexConstants::InvalidID;`
- L67 _public member_ `FIndex2i SourceEidPair = FIndex2i::Invalid();` — Neighboring edges, ordered by (incoming, outgoing)

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/ExtrudeMesh.h` (Public)


#### class `UE::Geometry::FExtrudeMeshFixLayout`  
`class FExtrudeMeshFixLayout`  
_L24-28_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L27 _public prototype_ `virtual ~FExtrudeMeshFixLayout() = default;`

#### class `UE::Geometry::FExtrudeMesh`  
`class FExtrudeMesh : public FExtrudeMeshFixLayout`  
_L41-133_
- inherits: `FExtrudeMeshFixLayout`
- desc: Note: FExtrudeMesh might someday be removed. Consider using FOffsetMeshRegion instead, which can extrude all or part of a mesh. FExtrudeMesh implements a full-mesh extrusion of a mesh. This happens in two stages: 1) all triangles of input mesh are duplicated and offset 2) base and offset border loops are stitched together with triangulated quads Step 2 does not occur if there are no boundary loops (ie for a closed input mesh) Each quad of the border loop is assigned it's own normal and UVs (ie each is a separate UV-island)
- L50 _public member_ `FDynamicMesh3* Mesh;` — The mesh that we are modifying
- L53 _public member_ `TFunction<FVector3d (const FVector3d&, const FVector3f&, int)> ExtrudedPositionFunc;` — This function is called to generate the offset vertex position. Default returns (Position + DefaultExtrudeDistance * Normal)
- L56 _public member_ `double DefaultExtrudeDistance = 1.0;` — If no Extrude function is set, we will displace by DefaultExtrudeDistance*Normal
- L59 _public member_ `bool IsPositiveOffset = true;` — if Extrusion is "negative" (ie negative distance, inset, etc) then this value must be set to false or the output will have incorrect winding orientation
- L62 _public member_ `bool bSkipClosedComponents = false;` — If true, skip closed components
- L65 _public member_ `float UVScaleFactor = 1.0f;` — quads on the stitch loop are planar-projected and scaled by this amount
- L101 _public member_ `TArray<FExtrusionInfo> Extrusions;` — List of extrusion regions, one per connected component of input
- L104 _public prototype_ `FExtrudeMesh(FDynamicMesh3* mesh);`
- L106 _public prototype_ `virtual ~FExtrudeMesh() = default;`
- L112 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot
- L126 _public prototype_ `virtual bool Apply();` — Apply the Extrude operation to the input mesh. @return true if the algorithm succeeds
- L132 _protected prototype_ `bool ApplyExtrude(FExtrusionInfo& Region, FMeshNormals* UseNormals = nullptr);`

#### struct `UE::Geometry::FExtrudeMesh::FExtrusionInfo`  
`struct FExtrusionInfo`  
_L75-96_
- desc: FExtrusionInfo stores info about extrusion for a single mesh connected component. Note that this may involve multiple boundary loops (eg if a region has holes)
- L78 _public member_ `FMeshRegionBoundaryLoops InitialLoops;` — Initial boundary loops on the mesh (may be empty)
- L80 _public member_ `TArray<int> InitialTriangles;` — set of triangles that were extruded
- L82 _public member_ `TArray<int> InitialVertices;` — set of vertices that were extruded
- L84 _public member_ `TMap<int, int> InitialToOffsetMapV;` — Map from initial vertices to new offset vertices
- L86 _public member_ `TArray<int> OffsetTriangles;` — list of triangles on offset surface, in correspondence with InitialTriangles (note: can get vertices via InitialToOffsetMapV(InitialVertices)
- L88 _public member_ `TArray<int> OffsetTriGroups;` — list of new groups of triangles on offset surface
- L91 _public member_ `TArray<FEdgeLoop> NewLoops;` — New edge loops on borders of offset patches (1-1 correspondence w/ InitialLoops.Loops)
- L93 _public member_ `TArray<TArray<int>> StitchTriangles;` — Lists of triangle-strip "tubes" that connect each loop-pair
- L95 _public member_ `TArray<TArray<int>> StitchPolygonIDs;` — List of group ids / polygon ids on each triangle-strip "tube"

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DYNAMICMESH_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/FFDLattice.h` (Public)


#### enum `UE::Geometry::ELatticeInterpolation`  
`enum class ELatticeInterpolation : uint8`  
_L22-26_
- L24 _public enumerator_ `Linear = 0`
- L25 _public enumerator_ `Cubic = 1`

#### struct `UE::Geometry::FLatticeExecutionInfo`  
`struct FLatticeExecutionInfo`  
_L28-32_
- L30 _public member_ `bool bParallel = true;`
- L31 _public member_ `int CancelCheckSize = 100000;` — Number of vertices to process before checking for cancel

#### class `UE::Geometry::FFFDLattice`  
`class FFFDLattice`  
_L38-165_
- desc: Free-form deformation lattice. Initialize it with a mesh and desired resolution, get the initial lattice points out. Then pass in deformed lattice points and it will compute deformed mesh vertex positions.
- L51 _public prototype_ `FFFDLattice(const FVector3i& InDims, const FDynamicMesh3& InMesh, float Padding);` — Create a lattice that fits the given mesh and has the given resolution along each dimension. Also precompute the weight of each mesh vertex inside the appropriate lattice cell.
- L55 _public prototype_ `FFFDLattice(const FVector3i& InDims, const FDynamicMesh3* Mesh, float Padding, const FAxisAlignedBox3d& InInitialBounds, const FTransformSRT3d& LatticeTransform = FTransformSRT3d::Identity());` — Create a lattice that fits the oriented box defined by the AABB and Transform, and has the given resolution along each dimension. Also precompute the weight of each mesh vertex inside the appropriate lattice cell. Mesh vertices outside of the oriented bounding box should have a LatticeCell value of {-1, -1, -1}.
- L58 _public prototype_ `bool VertexHasValidEmbedding(int32 VertexIndex) const;` — Whether the given vertex has a valid embedding, i.e. whether the original vertex location was inside a lattice cell and it would be affected by lattice deformation
- L62 _public prototype_ `void GetDeformedMeshVertexPositions(const TArray<FVector3d>& LatticeControlPoints, TArray<FVector3d>& OutVertexPositions, ELatticeInterpolation Interpolation = ELatticeInterpolation::Linear, FLatticeExecutionInfo ExecutionInfo = FLatticeExecutionInfo(), FProgressCancel* Progress = nullptr) const;` — Using the Lattice's current control point positions and the original embedding information, compute the deformed mesh vertex positions.
- L70 _public prototype_ `void GetRotatedOverlayNormals(const TArray<FVector3d>& LatticeControlPoints, const FDynamicMeshNormalOverlay* NormalOverlay, TArray<FVector3f>& OutNormals, ELatticeInterpolation Interpolation = ELatticeInterpolation::Linear, FLatticeExecutionInfo ExecutionInfo = FLatticeExecutionInfo(), FProgressCancel* Progress = nullptr) const;` — Using the Lattice's current control point positions, the original embedding information, and the original normals contained in an overlay, compute the new rotated normals
- L79 _public prototype_ `void GetRotatedMeshVertexNormals(const TArray<FVector3d>& LatticeControlPoints, const TArray<FVector3f>& OriginalNormals, TArray<FVector3f>& OutNormals, ELatticeInterpolation Interpolation, FLatticeExecutionInfo ExecutionInfo, FProgressCancel* Progress) const;` — Using the Lattice's current control point positions, the original embedding information, and the original normals, compute the new rotated normals
- L87 _public prototype_ `void GenerateInitialLatticePositions(TArray<FVector3d>& OutLatticePositions) const;` — Return the set of lattice corner positions in undeformed state
- L90 _public prototype_ `void GenerateLatticeEdges(TArray<FVector2i>& OutLatticeEdges) const;` — Return the lattice edges by index. The indices refer to the array of lattice positions returned by GenerateInitialLatticePositions
- L93 _public function_ `const FVector3i& GetDimensions() const` — Number of lattice points in each dimension
- L99 _public function_ `const FVector3d& GetCellSize() const` — 3D size of a lattice cell
- L105 _public function_ `const FAxisAlignedBox3d& GetInitialBounds() const` — Extents of the lattice before it is deformed
- L111 _public function_ `int ControlPointIndexFromCoordinates(int i, int j, int k) const` — Get the index into the flat TArray of positions given the (i,j,k) coordinates in the lattice
- L118 _public function_ `int ControlPointIndexFromCoordinates(const FVector3i& Index) const` — Get the index into the flat TArray of positions given the (i,j,k) coordinates in the lattice
- L126 _protected member_ `FTransformSRT3d Transform;` — Lattice transform
- L129 _protected member_ `FVector3i Dimensions;` — Number of lattice points in each dimension
- L132 _protected member_ `FAxisAlignedBox3d InitialBounds;` — Extents of the lattice before it is deformed
- L135 _protected member_ `FVector3d CellSize;` — 3D size of a lattice cell
- L138 _protected member_ `TArray<FEmbedding> VertexEmbeddings;` — Interpolation weights and cell indices per vertex of the input FDynamicMesh3
- L141 _protected prototype_ `void InitLattice(float Padding);` — Ccnstructor helper function for setting up lattice data
- L144 _protected prototype_ `void ComputeInitialEmbedding(const FDynamicMesh3& Mesh, FLatticeExecutionInfo ExecutionInfo = FLatticeExecutionInfo());` — For each vertex in Mesh, compute the lattice cell it resides in and its weighting
- L147 _protected prototype_ `FVector3d ComputeTrilinearWeights(const FVector3d& Pt, FVector3i& GridCoordinates) const;` — Compute cell index and linear interpolation weights for a given point
- L150 _protected prototype_ `void GetValuePair(int I, int J, int K, FVector3d& A, FVector3d& B, const TArray<FVector3d>& LatticeControlPoints) const;` — Helper for linear interpolation. Returns lattice points at (I,J,K) and (I+1,J,K).
- L153 _protected prototype_ `FVector3d InterpolatedPosition(const FEmbedding& VertexEmbedding, const TArray<FVector3d>& LatticeControlPoints) const;` — Use the given cell index and weights to compute the interpolated position
- L154 _protected prototype_ `FVector3d InterpolatedPositionCubic(const FEmbedding& VertexEmbedding, const TArray<FVector3d>& LatticeControlPoints) const;`
- L156 _protected prototype_ `FMatrix3d LinearInterpolationJacobian(const FEmbedding& VertexEmbedding, const TArray<FVector3d>& LatticeControlPoints) const;`
- L157 _protected prototype_ `FMatrix3d CubicInterpolationJacobian(const FEmbedding& VertexEmbedding, const TArray<FVector3d>& LatticeControlPoints) const;`
- L160 _protected prototype_ `FVector3d ClosestLatticePosition(const FVector3i& VirtualControlPointIndex, const TArray<FVector3d>& LatticeControlPoints) const;` — Clamp the given index to [0, Dims] and return the current lattice point position at the clamped index
- L163 _protected prototype_ `FVector3d ExtrapolatedLatticePosition(const FVector3i& VirtualPointIndex, const TArray<FVector3d>& LatticeControlPoints) const;` — Compute the extrapolated position for a "virtual" lattice control point outside of the actual lattice

#### struct `UE::Geometry::FFFDLattice::FEmbedding`  
`struct FEmbedding`  
_L43-47_
- desc: Linear interpolation information. There should be one of these per mesh vertex.
- L45 _public member_ `FVector3i LatticeCell = { -1, -1, -1 };` — Original point is in the hexahedron whose Min corner is LatticeCell
- L46 _public member_ `FVector3d CellWeighting = { 0,0,0 };` — Original linear interpolation weights of the point in the cell

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/GeodesicPath.h` (Public)


#### class `UE::Geometry::FEdgePath`  
`class FEdgePath`  
_L35-93_
- desc: FEdgePath is is little more than a double link-list that exposes IDs instead of node pointers. The ID of a removed segment may be reused for a subsequently appended or inserted segment. When used in conjunction with a mesh, it represents a directed, edge-aligned path. Note: this exists primarily for use with FDeformableEdgePath and no checking is done to ensure the path is continuous, in fact it could be used to represent multiple disconnected paths.
- L40 _public member_ `constexpr static int InvalidID = IndexConstants::InvalidID;`
- L47 _public prototype_ `FEdgePath() = default;`
- L48 _public prototype_ `FEdgePath(const FEdgePath&) = delete;`
- L51 _public prototype_ `inline int32 NumSegments() const;` — @return number of segments in path
- L54 _public prototype_ `inline int32 MaxSegmentID() const;` — @return upper bound on the segment ID used in path.  i.e. all segment IDs < MaxSegmentID
- L57 _public prototype_ `inline bool IsSegment(int32 SID) const;` — @return true if the specified segment ID corresponds to a valid segment in path
- L60 _public prototype_ `FDirectedSegment GetSegment(int32 SID) const;` — @return requested segment if it is part of the path, otherwise return invalid segment (with EID = InvalidID)
- L63 _public prototype_ `int32 GetHeadSegmentID() const;` — @return the segment ID of the {first, last} segment in the path, or InvalidID if the path is empty
- L64 _public prototype_ `int32 GetTailSegmentID() const;`
- L67 _public prototype_ `int32 GetPrevSegmentID(int32 SID) const;` — @return segment ID of {previous, next} segment in the path, or InvalidID if if no {previous, next} exists or if SID itself is not in the path
- L68 _public prototype_ `int32 GetNextSegmentID(int32 SID) const;`
- L71 _public prototype_ `int32 AppendSegment(const FDirectedSegment& Segment);` — @return segment ID of a new segment appended to the tail of the path
- L74 _public prototype_ `int32 InsertSegmentBefore(const FDirectedSegment& DirectedSegment, int32 SegmentIDToInsertBefore = InvalidID);` — @return segment ID of a new segment inserted before the specified existing segment. If SegmentIDToInsertBefore is InvalidID, then insert at head
- L77 _public prototype_ `void RemoveSegment(int32 SID);` — remove specified segment from path. Note SID is added to an internal free list and maybe reused
- L87 _protected typedef_ `typedef typename TDoubleLinkedList<FSegmentAndSID>::TDoubleLinkedListNode NodeType;`
- L89 _protected member_ `TDoubleLinkedList<FSegmentAndSID> PathLinkList;` — The path is represented by Segments in a double link list.
- L91 _protected member_ `TDynamicVector<NodeType*> SIDtoNode;` — Nodes per segment indexed by SegmentID (SID)
- L92 _protected member_ `FRefCountVector DirectedSegmentRefCounts{};` — SID list.
- L314 _function_ `int FEdgePath::NumSegments() const`
- L319 _function_ `int32 FEdgePath::MaxSegmentID() const`
- L324 _function_ `bool FEdgePath::IsSegment(int32 SID) const`

#### struct `UE::Geometry::FEdgePath::FDirectedSegment`  
`struct FDirectedSegment`  
_L41-45_
- L43 _public member_ `int32 EID = InvalidID;` — expected to be a mesh edge ID
- L44 _public member_ `int32 HeadIndex = InvalidID;` — 0 or 1.  GetEdgeV()[HeadIndex] is the 'to' vertex,  GetEdgeV()[1-HeadIndex] is the 'from' vertex

#### struct `UE::Geometry::FEdgePath::FSegmentAndSID`  
`struct FSegmentAndSID : FDirectedSegment`  
_L82-85_
- inherits: `FDirectedSegment`
- L84 _public member_ `int32 SID = InvalidID;` — segment id

#### class `UE::Geometry::FDeformableEdgePath`  
`class FDeformableEdgePath`  
_L110-276_
- desc: Given a single path initially defined by edges on a FDynamicMesh (the SurfaceMesh), this class uses an intrinsic mesh with the same vertex set to minimize the length of the path on the surface mesh.  This is done iteratively by a succession of local path deformations comprised of (local) intrisic edge flips and path re-routing, each deformation locally reduces the path length. The resulting path is comprised of intrinsic mesh edges. This is an implementation of the ideas in "You Can Find Geodesic Paths in Triangle Meshes by Just Flipping Edges" by Nicholas Sharp and Keenan Crane ACM Trans. Graph. Vol. 39, No. 6, 2020 The original path is constructed as a sequence of mesh edges relative to the  SurfaceMesh ( the FDynamicMesh3 ), these edges are encoded with path direction as FDirectedSegments. Note: The current implementation does not support closed paths or multiple paths.
- L114 _public member_ `constexpr static int InvalidID = IndexConstants::InvalidID;`
- L116 _public typedef_ `typedef FIntrinsicEdgeFlipMesh IntrinsicMeshType;`
- L121 _public prototype_ `FDeformableEdgePath(const FDynamicMesh3& SurfaceMeshIn, const TArray<FEdgePath::FDirectedSegment>& OriginalPathAsDirectedSegments);` — Constructor assumes the directed segments are ordered from tail (at index 0) to head
- L123 _public prototype_ `virtual ~FDeformableEdgePath()= default;`
- L126 _public prototype_ `FDeformableEdgePath() = delete;` — only allow construction from a path and mesh.
- L127 _public prototype_ `FDeformableEdgePath(const FDeformableEdgePath& ) = delete;`
- L145 _public prototype_ `virtual void Minimize(FEdgePathDeformationInfo& DeformedPathInfo, const int32 MaxNumIterations = TMathUtilConstants<int32>::MaxReal);` — Minimize the deformable edge path with respect to the total path length. This minimization finds a local minimum in path length but may not find the shortest over all distance between to points. In this sense the operation can be thought of as a path-straightening. @param DeformedPathInfo  - on return this info struct is populated @param MaxNumIterations  - the maximum number of two-edge joints that may be replaced by shorter paths.
- L150 _public prototype_ `inline const FEdgePath& GetEdgePath() const;` — @return a const reference to the edge path.
- L155 _public prototype_ `inline double GetPathLength() const;` — @return Length of the path.
- L160 _public prototype_ `inline const FIntrinsicEdgeFlipMesh& GetIntrinsicMesh() const;` — @return const reference to the intrinsic mesh on which the EdgePath is defined.
- L165 _public typedef_ `using FSurfacePoint = IntrinsicCorrespondenceUtils::FSurfacePoint;` — struct that references a point on a mesh, by vertex, by edge-crossing, or barycentric coords
- L177 _public prototype_ `TArray<FSurfacePoint> AsSurfacePoints(double CoalesceThreshold = 0.) const;` — @return an array of surface points relative to the SurfaceMesh that define this path. Note the first and last surfacepoints correspond to the start and end vertex, but all other surface points may be either edge crossings or vertex points. @param CoalesceThreshold - In barycentric units [0,1], edge-crossings within this threshold are snapped to the nearest vertex and any resulting repitition of vertex surface points are replaced with a single vertex surface point. Due to numerical precision issues, a path that 'should' intersect a surface mesh vertex may appear as a sequence of vertex adjacent edge-crossings very close to the vertex.. the threshold is applied in a post-process coalesce those crossings into a single vertex crossing.
- L195 _protected prototype_ `void DeformJoint(FPathJoint& PathJoint);` — Replace the specified two connected edge segments (FPathJoint) in the main path with a new sub-path that connects the same end points. This new path is formed by flipping the adjacent edges to the left (or right) of the joint vertex and may have one, two, or more segments
- L207 _protected prototype_ `bool DeformJoint( const int32 IncomingEID, const int32 OutgoingEID, int32 JointVID, TArray<FEdgePath::FDirectedSegment>& DeformedPath, const bool bClockwise );` — Edge flip the adjacent edges to the JointVID and collect the DeformedPath that can be used to replace the local incoming and outgoing edge path @param IncomingEID  - ID of incoming edge of joint @param OutgoingEID  - ID of outgoing edge of joint @param JointVID     - ID of Vertex where incoming and outgoing edges meet @param DeformedPath - On return, holds directed segments that can be used to replace the joint @param bClockwise   - When true, the deformation and new path are on the "left" of the original path, otherwise on the "right" where the path is locally viewed as traveling from bottom to top
- L213 _protected prototype_ `inline int32 SegmentHeadVID(int32 SID) const;` — @return the ID of the vertex at the "head" of the specified segment
- L218 _protected prototype_ `inline int32 SegmentTailVID(int32 SID) const;` — @return the ID of the vertex at the "tail" of the specified segment
- L223 _protected prototype_ `bool IsJointFlexible(const FPathJoint& PathJoint) const;` — @return true if no part of the global path lies in the wedge (partial one-ring) on PathJoint.Interior side
- L229 _protected prototype_ `void UpdateJointAndQueue(int32 OutgoingSegmentID);` — Compute data associated with the joint formed by the specified segment (outgoing), and the preceding segment (incoming) in the path. Also update the JointAngleQueue that tracks straightness of each joint.
- L236 _protected prototype_ `void RemoveSegment(int32 SID);` — remove specified segment from the linked-list path and clean up joint-related data for the joint that ends with this segment. note: the joint data (e.g. joint angle queue) for the joint that started with this segment will be dirty.
- L241 _protected prototype_ `void ReplaceJointWithPath(const FPathJoint PathJoint, const TArray<FEdgePath::FDirectedSegment>& PathAsDirectedEdges);` — Splice in a path to replace the joint and update the joint angle queue.
- L253 _protected prototype_ `bool OuterArcFlipEdges(int32 StartEID, int32 EndEID, int32 CenterVID, bool bClockwise = false);` — Traveling either CCW or CW around vertex CenterVID, from edge StartEID to edge EndEID, flip edges adjacent to CVID. return true on success, and false if one of the edges was a boundary edge. It is assumed the specified edges do in fact have vertex CVID in common, but this is not checked. Note: in the false case, some of the edges may have been flipped before encountering the boundary edge - no attempt is made to restore the mesh.
- L261 _protected prototype_ `void ComputeWedgeAngles(int32 IncomingEID, int32 OutgoingEID, int32 CenterVID, double& LeftSideAngle, double& RightSideAngle) const ;` — Compute the two angles formed at the vertex CenterVID by the two wedges formed by splitting the local one-ring by local path specified as incoming and outgoing edges. It is assumed the specified edges do in fact have vertex CVID in common, but this is not checked.
- L266 _protected member_ `IntrinsicMeshType EdgeFlipMesh;` — Intrinsic mesh with the same vertices as the original surface mesh. The geodesic path is comprised of edges in this mesh.
- L268 _protected member_ `double PathLength;` — Total length of the path
- L269 _protected member_ `int32 NumFlips;` — Count of the number of edge flips performed in shortening the path.
- L271 _protected member_ `FEdgePath EdgePath;` — Path defined relative to the edges in the EdgeFlipMesh.
- L272 _protected member_ `TMap<int32, TArray<int32>> EIDToSIDsMap;` — Map mesh edge ID to array of path segments.  A path could traverse the same mesh edge multiple times.
- L273 _protected member_ `TDynamicVector<FPathJoint> PathJoints;` — List of directed segment joints in the path, indexed by SID of Outgoing segment.
- L274 _protected member_ `FBinaryHeap<double> JointAngleQueue;` — Priority queue that can automatically resize if needed.  Priority based on the smaller angle between the two edges in a joint
- L285 _function_ `const FEdgePath& FDeformableEdgePath::GetEdgePath() const`
- L290 _function_ `double FDeformableEdgePath::GetPathLength() const`
- L295 _function_ `const FIntrinsicEdgeFlipMesh& FDeformableEdgePath::GetIntrinsicMesh() const`
- L300 _function_ `int32 FDeformableEdgePath::SegmentHeadVID(int32 SID) const`
- L306 _function_ `int32 FDeformableEdgePath::SegmentTailVID(int32 SID) const`

#### struct `UE::Geometry::FDeformableEdgePath::FEdgePathDeformationInfo`  
`struct FEdgePathDeformationInfo`  
_L130-136_
- desc: information gathered during minimization
- L132 _public member_ `int32 NumIterations = 0;` — number of two-edge joints that were replaced by shorter paths (but perhaps more segments)
- L133 _public member_ `int32 NumEdgeFlips = 0;` — number of edge flips performed in minimizing the path
- L134 _public member_ `double OriginalLength = 0.;` — path length prior to minimization
- L135 _public member_ `double FinalLength = 0.;` — path length after minimization

#### enum `UE::Geometry::FDeformableEdgePath::ESide`  
`enum class ESide`  
_L181-181_
- desc: indicates which wedge (Left or Right) has the smaller internal angle, where in 2d the path travels "up"
- L181 _public enumerator_ `enum class ESide { Left, Right }; struct FPathJoint { int32 OutgoingSID = InvalidID; ESide InteriorSide; int32 VID = InvalidID; };` — indicates which wedge (Left or Right) has the smaller internal angle, where in 2d the path travels "up"
- L181 _public enumerator_ `enum class ESide { Left, Right }; struct FPathJoint { int32 OutgoingSID = InvalidID; ESide InteriorSide; int32 VID = InvalidID; };` — indicates which wedge (Left or Right) has the smaller internal angle, where in 2d the path travels "up"

#### struct `UE::Geometry::FDeformableEdgePath::FPathJoint`  
`struct FPathJoint`  
_L182-187_
- L184 _public member_ `int32 OutgoingSID = InvalidID;` — Outgoing segment.  EdgePath.GetPrevSegmentID(OutgoingSID) returns incoming segment
- L185 _public member_ `ESide InteriorSide;` — Side of the one-ring with the smaller angle.
- L186 _public member_ `int32 VID = InvalidID;` — incoming and Outgoing edges meet at this vertex

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API DYNAMICMESH_API`
- L21 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Geometry` (scope `UE`)
- L282 _prototype_ `double SumPathLength(const FDeformableEdgePath& DeformableEdgePath);` (scope `UE::Geometry`) — @return the length of the path, computed by suming the path segment lengths.  Primarily for testing as the result should match FDeformableEdgePath::GetPathLength()

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/GroupEdgeInserter.h` (Public)


#### class `UE::Geometry::FGroupEdgeInserter`  
`class FGroupEdgeInserter`  
_L24-162_
- desc: Used to insert group edges and group edge loops.
- L102 _public prototype_ `bool InsertEdgeLoops(const FEdgeLoopInsertionParams& Params, FOptionalOutputParams OptionalOut = FOptionalOutputParams(), FProgressCancel* Progress = nullptr);`
- L160 _public prototype_ `bool InsertGroupEdge(FGroupEdgeInsertionParams& Params, FOptionalOutputParams OptionalOut = FOptionalOutputParams(), FProgressCancel* Progress = nullptr);`

#### enum `UE::Geometry::FGroupEdgeInserter::EInsertionMode`  
`enum class EInsertionMode`  
_L28-32_
- L30 _public enumerator_ `Retriangulate`
- L31 _public enumerator_ `PlaneCut`

#### struct `UE::Geometry::FGroupEdgeInserter::FEdgeLoopInsertionParams`  
`struct FEdgeLoopInsertionParams`  
_L35-76_
- desc: Parameters for an InsertEdgeLoops() call.
- L38 _public member_ `FDynamicMesh3* Mesh = nullptr;` — Both of these get updated in the operation
- L39 _public member_ `FGroupTopology* Topology = nullptr;`
- L42 _public member_ `int32 GroupEdgeID = FDynamicMesh3::InvalidID;` — Edge loops will be inserted perpendicular to this group edge
- L48 _public member_ `const TArray<double>* SortedInputLengths = nullptr;` — Inputs can be proportions in the range (0,1), or absolute lengths. As the name suggests, they must already be sorted.
- L49 _public member_ `bool bInputsAreProportions = true;`
- L55 _public member_ `int32 StartCornerID = FDynamicMesh3::InvalidID;` — One of the endpoints of the group edge, from which the arc lengths or proportions should be measured
- L61 _public member_ `double VertexTolerance = KINDA_SMALL_NUMBER * 10;` — When inserting edges, this is the distance that a desired new point can be to use a nearby vertex rather than splitting an edge to create a new one.
- L68 _public member_ `bool bSimplifyAlongPath = true;` — When inserting edges, we can locally simplify to improve mesh quality along the edge path. Only does so when it should not change mesh shape, UVs, triangle groups, etc, and only applies when Insertion Mode is "Plane Cut"
- L75 _public member_ `EInsertionMode Mode = EInsertionMode::Retriangulate;` — Determines how the edge is inserted: by using a cutting plane to cut existing triangles along the path, or deleting triangles and retriangulating. Retriangulation will keep geometry nice but currently loses the UV's, and it obviously breaks for non-planar groups.

#### struct `UE::Geometry::FGroupEdgeInserter::FOptionalOutputParams`  
`struct FOptionalOutputParams`  
_L78-100_
- L82 _public function_ `FOptionalOutputParams()` — Some compilers (clang, at least) have issues with using a nested class with default initializers and a default constructor as default argument in a function, hence this constructor.
- L87 _public member_ `TSet<int32>* NewEidsOut = nullptr;` — Edge IDs of the edges composing the newly inserted group edges.
- L93 _public member_ `TSet<int32>* ChangedTidsOut = nullptr;` — Any triangle IDs whose triangles were deleted or changed by the operation (but not newly created tids). Useful for setting up undo.
- L99 _public member_ `TSet<int32>* ProblemGroupEdgeIDsOut = nullptr;` — In loop insertion, the group edge IDs in the original topology that surround non-quad-like groups that stopped the loop.

#### struct `UE::Geometry::FGroupEdgeInserter::FGroupEdgeSplitPoint`  
`struct FGroupEdgeSplitPoint`  
_L106-126_
- desc: Point along a group edge that is used as a start/endpoint for an inserted group edge.
- L109 _public member_ `int32 ElementID;` — Either vertex ID or edge ID of the point.
- L112 _public member_ `bool bIsVertex;` — Whether the point is an edge or vertex.
- L119 _public member_ `FVector3d Tangent;` — When using a cutting plane, tangent that is used to help position the plane. For edges, it is just an edge vector, but for vertices, it is the average of the adjacent edge vectors of the group boundary.
- L125 _public member_ `double EdgeTValue;` — Only relevant for edges. The range (0,1) parameter that determines where the edge should be split (the order of endpoints is given by the mesh structure).

#### struct `UE::Geometry::FGroupEdgeInserter::FGroupEdgeInsertionParams`  
`struct FGroupEdgeInsertionParams`  
_L129-158_
- desc: Parameters for an InsertGroupEdge() call
- L132 _public member_ `FDynamicMesh3* Mesh = nullptr;` — These are both modified in the operation
- L133 _public member_ `FGroupTopology* Topology = nullptr;`
- L136 _public member_ `int32 GroupID = FDynamicMesh3::InvalidID;` — Group across which the cut is inserted.
- L138 _public member_ `int32 GroupBoundaryIndex = 0;` — Index into the group's Boundary array that holds the boundary that the start and end points share.
- L140 _public member_ `FGroupEdgeSplitPoint StartPoint;`
- L141 _public member_ `FGroupEdgeSplitPoint EndPoint;`
- L148 _public member_ `double VertexTolerance = KINDA_SMALL_NUMBER * 10;` — When inserting edges, this is the distance that a desired new point can be to use a nearby vertex rather than splitting an edge to create a new one (used when inserting using plane cut).
- L155 _public member_ `bool bSimplifyAlongPath = true;` — When inserting edges, we can locally simplify to improve mesh quality along the edge path. Only does so when it should not change mesh shape, UVs, triangle groups, etc, and only applies when Insertion Mode is "Plane Cut"
- L157 _public member_ `EInsertionMode Mode = EInsertionMode::Retriangulate;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/GroupTopologyDeformer.h` (Public)


#### class `UE::Geometry::FVertexPositionCache`  
`class FVertexPositionCache`  
_L24-52_
- desc: Basic cache of vertex positions.
- L27 _public member_ `TArray<int> Vertices;`
- L28 _public member_ `TArray<FVector3d> Positions;`
- L30 _public function_ `void Reset()`
- L37 _public function_ `void AddVertex(const FDynamicMesh3* Mesh, int VertexID)` — Save this vertex. Does not check that VertexID hasn't already been added.
- L44 _public function_ `void SetPositions(FDynamicMesh3* Mesh) const` — Apply saved positions to Mesh

#### class `UE::Geometry::FGroupTopologyDeformer`  
`class FGroupTopologyDeformer`  
_L71-228_
- desc: FGroupTopologyDeformer supports deforming a Mesh based on an overlaid FGroupTopology. First the client defines a set of "Handle" elements (Faces/Corners/Edges) using SetActiveHandleX(). The client will provide new vertex positions for the vertices of these elements via the HandleVertexDeformFunc argument to UpdateSolution(). Once the Handle vertices have been updated, the deformer solves for updated vertex positions in the GroupTopology Faces that are adjacent to the handles. This region is referred to as the "ROI" (Region-of-Interest) The default deformation is to first solve for the updated edges, and then solve for updated faces. This is done via linear encoding of the edge and face vertices relative to their boundaries (edge boundary is endpoint corners, face boundary is edges). Various functions can be overrided to customize behavior.
- L74 _public prototype_ `virtual ~FGroupTopologyDeformer() = default;`
- L77 _public prototype_ `void Initialize(const FDynamicMesh3* Mesh, const FGroupTopology* Topology);` — Set the Mesh and Topology to use for the deformation
- L79 _public function_ `const FDynamicMesh3* GetMesh() const`
- L80 _public function_ `const FGroupTopology* GetTopology() const`
- L89 _public prototype_ `virtual void SetActiveHandleFaces(const TArray<int>& FaceGroupIDs);` — Set the active handle to the given Faces
- L94 _public prototype_ `virtual void SetActiveHandleCorners(const TArray<int>& TopologyCornerIDs);` — Set the active handle to the given Corners
- L99 _public prototype_ `virtual void SetActiveHandleEdges(const TArray<int>& TopologyEdgeIDs);` — Set the active handle to the given Edges
- L105 _public prototype_ `virtual void SetActiveHandleFromSelection(const FGeometrySelection& Selection);` — Set the active handle from GeometrySelection
- L111 _public prototype_ `virtual void SetActiveHandle(const TArray<int>& FaceGroupIDs, const TArray<int>& TopologyEdgeIDs, const TArray<int>& TopologyCornerIDs);` — Set the active handle to the given Faces, Edges, Corners
- L121 _public prototype_ `virtual void UpdateSolution(FDynamicMesh3* TargetMesh, const TFunction<FVector3d(FDynamicMesh3* Mesh, int)>& HandleVertexDeformFunc);` — Update TargetMesh by first calling HandleVertexDeformFunc() to get new handle vertex positions, then solving for new ROI vertex positions.
- L126 _public prototype_ `virtual void ClearSolution(FDynamicMesh3* TargetMesh);` — Restore the Handle and ROI vertex positions to their initial state
- L131 _public function_ `const TSet<int>& GetHandleVertices() const` — @return the set of handle vertices
- L133 _public function_ `const TSet<int>& GetModifiedVertices() const` — @return the set of all vertices whose positions will be modified by the deformation
- L135 _public function_ `const TSet<int>& GetModifiedOverlayNormals() const` — @return the set of all overlay normals that will be modified by the deformation
- L138 _public function_ `void EnumerateROIEdges(TFunctionRef<void(const FEdgeSpan& EdgeSpan)> EdgeSpanFunc) const` — Call EdgeSpanFunc for every group FEdgeSpan in the modified-area ROI that will be modified by the solver (does not include edges that are encompassed by the Handle)
- L152 _protected prototype_ `virtual void Reset();` — reset all internal data structures, eg when changing handle
- L158 _protected prototype_ `virtual void CalculateROI(const TArray<int>& HandleGroups, const TArray<int>& ROIGroups);` — Populate the internal ROI data structures based on the given HandleGroups and ROIGroups. HandleGroups will be empty if the Handle is a set of Vertices or Edges.
- L163 _protected prototype_ `virtual void SaveInitialPositions();` — Save the positions of all vertices that will be modified
- L168 _protected prototype_ `virtual void ComputeEncoding();` — Precompute the representation of the ROI vertices at the initial positions.
- L171 _protected member_ `const FDynamicMesh3* Mesh = nullptr;`
- L172 _protected member_ `const FGroupTopology* Topology = nullptr;`
- L174 _protected member_ `FVertexPositionCache InitialPositions;`
- L175 _protected member_ `TSet<int> ModifiedVertices;`
- L176 _protected member_ `TSet<int> HandleVertices;`
- L177 _protected member_ `TSet<int> HandleBoundaryVertices;`
- L178 _protected member_ `TSet<int> FixedBoundaryVertices;`
- L179 _protected member_ `TSet<int> ROIEdgeVertices;`
- L180 _protected member_ `TSet<int> FaceVertsTemp;`
- L181 _protected member_ `TSet<int> FaceBoundaryVertsTemp;`
- L182 _protected member_ `TSet<int> ModifiedOverlayNormals;`
- L189 _protected member_ `TArray<FROIEdge> ROIEdges;`
- L196 _protected member_ `TArray<FROIFace> ROIFaces;`
- L213 _protected member_ `TArray<FEdgeEncoding> EdgeEncodings;`
- L226 _protected member_ `TArray<FFaceEncoding> FaceEncodings;`

#### struct `UE::Geometry::FGroupTopologyDeformer::FROIEdge`  
`struct FROIEdge`  
_L184-188_
- L186 _public member_ `int EdgeIndex;`
- L187 _public member_ `FEdgeSpan Span;`

#### struct `UE::Geometry::FGroupTopologyDeformer::FROIFace`  
`struct FROIFace`  
_L191-195_
- L193 _public member_ `TArray<int> BoundaryVerts;`
- L194 _public member_ `TArray<int> InteriorVerts;`

#### struct `UE::Geometry::FGroupTopologyDeformer::FEdgeVertexEncoding`  
`struct FEdgeVertexEncoding`  
_L203-208_
- L205 _public member_ `double T;`
- L206 _public member_ `FVector3d Delta;`
- L207 _public function_ `FEdgeVertexEncoding()`

#### struct `UE::Geometry::FGroupTopologyDeformer::FEdgeEncoding`  
`struct FEdgeEncoding`  
_L209-212_
- L211 _public member_ `TArray<FEdgeVertexEncoding> Vertices;`

#### struct `UE::Geometry::FGroupTopologyDeformer::FFaceVertexEncoding`  
`struct FFaceVertexEncoding`  
_L217-221_
- L219 _public member_ `TArray<double> Weights;`
- L220 _public member_ `TArray<FVector3d> Deltas;`

#### struct `UE::Geometry::FGroupTopologyDeformer::FFaceEncoding`  
`struct FFaceEncoding`  
_L222-225_
- L224 _public member_ `TArray<FFaceVertexEncoding> Vertices;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DYNAMICMESH_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/HoleFillUtil.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)
- L18 _namespace_ `namespace HoleFillUtil` (scope `UE::Geometry`)
- L32 _function_ `template<typename OverlayType, typename EdgeEnumerateFn> void FillOverlayElements(const FDynamicMesh3& Mesh, OverlayType* Overlay, EdgeEnumerateFn PerEdgeIDFn, TConstArrayView<int32> NewTriangles, int32 NewVertex = IndexConstants::InvalidID)` (scope `UE::Geometry::HoleFillUtil`) — Fill in overlay elements on new triangles, by copying values from provided edges. Used to fill in overlay values after a hole fill. Only supports fills where at most one new vertex is added inside the hole (e.g., does not support smooth hole fill) @param Mesh Mesh holding the Overlay @param Overlay The dynamic mesh overlay to update @param PerEdgeIDFn Enumerator function, which will call a passed-in method per Edge ID on the hole border @param NewTriangles Triangles that fill the hole @param NewVertex If not invalid, the at-most one vertex created when filling the hole.
- L39 _function_ `` (scope `UE::Geometry::HoleFillUtil::FillOverlayElements`)
- L109 _function_ `inline void FillColorOverlay(FDynamicMesh3& Mesh, TConstArrayView<int32> HoleEdges, TConstArrayView<int32> NewTriangles, int32 NewVertex = IndexConstants::InvalidID)` (scope `UE::Geometry::HoleFillUtil`) — Fill in color overlay elements on new triangles, by copying values from provided edges. If mesh doesn't have a color overlay, does nothing. Used to fill in overlay values after a hole fill. Only supports fills where at most one new vertex is added inside the hole (e.g., does not support smooth hole fill) @param Mesh The mesh to update @param HoleEdges The edges at the boundary of the hole @param NewTriangles Triangles that fill the hole @param NewVertex If not invalid, the at-most one vertex created when filling the hole.
- L115 _function_ `` (scope `UE::Geometry::HoleFillUtil::FillColorOverlay`)
- L138 _function_ `inline void FillColorOverlay(FDynamicMesh3& Mesh, const TArray<TArray<int32>>& HoleVertexLoops, TConstArrayView<int32> NewTriangles, int32 NewVertex = IndexConstants::InvalidID)` (scope `UE::Geometry::HoleFillUtil`) — Fill in color overlay elements on new triangles, by copying values from edges along the provided vertex loops. If mesh doesn't have a color overlay, does nothing. Used to fill in overlay values after a hole fill. Only supports fills where at most one new vertex is added inside the hole (e.g., does not support smooth hole fill) @param Mesh The mesh to update @param HoleVertexLoops Vertex loops at the boundary of the hole @param NewTriangles Triangles that fill the hole @param NewVertex If not invalid, the at-most one vertex created when filling the hole.

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/HoleFiller.h` (Public)


#### class `UE::Geometry::IHoleFiller`  
`class IHoleFiller`  
_L13-21_
- L16 _public member_ `TArray<int32> NewTriangles;`
- L18 _public prototype_ `virtual ~IHoleFiller() = default;`
- L20 _public prototype_ `virtual bool Fill(int32 GroupID = -1) = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/InsetMeshRegion.h` (Public)


#### class `UE::Geometry::FInsetMeshRegion`  
`class FInsetMeshRegion`  
_L34-141_
- desc: FInsetMeshRegion implements local inset of a mesh region. The selected triangles are separated and then stitched back together, creating an new strip of triangles around their border (s). The boundary loop vertices are inset by creating an offset line for each boundary loop edge, and then finding closest-points between the sequential edge pairs. Complex input regions are handled, eg it can be multiple disconnected components, donut-shaped, etc Each quad of the border loop is assigned it's own normal and UVs (ie each is a separate UV-island)
- L43 _public member_ `FDynamicMesh3* Mesh;` — The mesh that we are modifying
- L46 _public member_ `TArray<int32> Triangles;` — The triangle region we are modifying
- L49 _public member_ `double InsetDistance = 1.0;` — Inset by this distance
- L52 _public member_ `float UVScaleFactor = 1.0f;` — quads on the stitch loop are planar-projected and scaled by this amount
- L55 _public member_ `bool bReproject = true;` — reproject positions onto input surface
- L59 _public member_ `bool bSolveRegionInteriors = true;` — update positions of any non-boundary vertices in inset regions (via laplacian solve)
- L62 _public member_ `float Softness = 0.0;` — determines how strongly laplacian solve constraints are enforced. 0 means hard constraint. Valid range [0,1]
- L65 _public member_ `float AreaCorrection = 1.0;` — Linear attenuation of area correction factor, valid range [0,1], 0 means ignore area correction entirely
- L68 _public member_ `FMeshProjectionTarget* ProjectionTarget;` — projection target
- L71 _public member_ `TUniquePtr<FDynamicMeshChangeTracker> ChangeTracker;` — If set, change tracker will be updated based on edit
- L104 _public member_ `TArray<FInsetInfo> InsetRegions;` — List of Inset regions/components
- L109 _public member_ `TArray<int32> AllModifiedTriangles;` — List of all triangles created/modified by this operation
- L113 _public prototype_ `FInsetMeshRegion(FDynamicMesh3* mesh);`
- L115 _public prototype_ `virtual ~FInsetMeshRegion();`
- L121 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot
- L135 _public prototype_ `virtual bool Apply();` — Apply the Inset operation to the input mesh. @return true if the algorithm succeeds
- L140 _protected prototype_ `virtual bool ApplyInset(FInsetInfo& Region, FMeshNormals* UseNormals = nullptr);`

#### struct `UE::Geometry::FInsetMeshRegion::FInsetInfo`  
`struct FInsetInfo`  
_L80-99_
- desc: Inset information for a single connected component
- L83 _public member_ `TArray<int32> InitialTriangles;` — Set of triangles for this region
- L85 _public member_ `TArray<FEdgeLoop> BaseLoops;` — Initial loops on the mesh
- L93 _public member_ `TArray<FEdgeLoop> InsetLoops;` — Inset loops on the mesh. If the region had bowtie vertices (in terms of selection, not even necessarily in terms of original mesh topology), then the number of loops here may no longer match number of loops in BaseLoops, StitchTriangles, etc (for example, imagine a circular hole tangent inside a circular region; when the tangent bowtie is split, this becomes one C-shaped loop instead of two nested ones)
- L96 _public member_ `TArray<TArray<int>> StitchTriangles;` — Lists of triangle-strip "tubes" that connect each loop-pair
- L98 _public member_ `TArray<TArray<int>> StitchPolygonIDs;` — List of group ids / polygon ids on each triangle-strip "tube"

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/IntrinsicCorrespondenceUtils.h` (Public)


#### struct `UE::Geometry::IntrinsicCorrespondenceUtils::FSurfacePoint`  
`struct FSurfacePoint`  
_L24-63_
- desc: Location on an extrinsic (surface) mesh stored as a union.
- L34 _public prototype_ `FSurfacePoint();` — constructors respect the correct position type
- L35 _public prototype_ `FSurfacePoint(const int32 VID);`
- L36 _public prototype_ `FSurfacePoint(const int32 EdgeID, const double Alpha);`
- L37 _public prototype_ `FSurfacePoint(const int32 TriID, const FVector3d& BaryCentrics);`
- L61 _public member_ `EPositionType PositionType;` — Position type, needed to correctly interpret the Position union
- L62 _public member_ `FSurfacePositionUnion Position;` — Position relative to vertex, edge, or triangle.

#### enum `UE::Geometry::IntrinsicCorrespondenceUtils::FSurfacePoint::EPositionType`  
`enum class EPositionType`  
_L26-31_
- L28 _public enumerator_ `Vertex`
- L29 _public enumerator_ `Edge`
- L30 _public enumerator_ `Triangle`

#### struct `UE::Geometry::IntrinsicCorrespondenceUtils::FSurfacePoint::FVertexPosition`  
`struct FVertexPosition`  
_L39-42_
- L41 _public member_ `int32 VID;` — Reference (extrinsic) vertex

#### struct `UE::Geometry::IntrinsicCorrespondenceUtils::FSurfacePoint::FEdgePosition`  
`struct FEdgePosition`  
_L43-47_
- L45 _public member_ `int32 EdgeID;` — Reference (extrinsic) edge
- L46 _public member_ `double Alpha;` — Lerp coordinate along referenced edge as Pos(Edge.A) (Alpha) + (1-Alpha) Pos(Edge.B)

#### struct `UE::Geometry::IntrinsicCorrespondenceUtils::FSurfacePoint::FTrianglePosition`  
`struct FTrianglePosition`  
_L48-52_
- L50 _public member_ `int32 TriID;` — Reference (extrinsic) triangle
- L51 _public member_ `FVector3d BarycentricCoords;` — Barycentric coordinates within referenced triangle

#### union `UE::Geometry::IntrinsicCorrespondenceUtils::FSurfacePoint::FSurfacePositionUnion`  
`union FSurfacePositionUnion`  
_L53-59_
- L55 _public function_ `FSurfacePositionUnion()`
- L56 _public member_ `FVertexPosition VertexPosition;`
- L57 _public member_ `FEdgePosition EdgePosition;`
- L58 _public member_ `FTrianglePosition TriPosition;`

#### struct `UE::Geometry::IntrinsicCorrespondenceUtils::FMeshConnection`  
`struct FMeshConnection`  
_L99-118_
- desc: A Connection stores the information needed to define a local reference direction for each vertex and triangle.
- L101 _public function_ `FMeshConnection() : SurfaceMesh(nullptr)`
- L103 _public prototype_ `FMeshConnection(const FDynamicMesh3& SurfMesh);`
- L106 _public prototype_ `void Reset(const FDynamicMesh3& SurfMesh);` — Reset the connection to the given (not owned) surface mesh
- L109 _public prototype_ `void Reset(TUniquePtr<FDynamicMesh3>& SurfMesh);` — Reset the connection to used a internally owned surface mesh
- L114 _public member_ `const FDynamicMesh3* SurfaceMesh;` — Pointer back the surface mesh used by the connection.  Will agree with OwnedSurfaceMesh if that is not null
- L115 _public member_ `TUniquePtr<FDynamicMesh3> OwnedSurfaceMesh;` — Optional, the connection can own a surface mesh.
- L116 _public member_ `TArray<int32> VIDToReferenceEID;` — Reference (original mesh) Edge per (original mesh) Vertex, defines local zero angle on tangent plane
- L117 _public member_ `TArray<int32> TIDToReferenceEID;` — Reference (original mesh) Edge per (original mesh) Triangle, defines local zero angle on tangent plane

#### struct `UE::Geometry::IntrinsicCorrespondenceUtils::FNormalCoordinates`  
`struct FNormalCoordinates : public FMeshConnection`  
_L125-204_
- inherits: `FMeshConnection`
- desc: Normal Coordinates as defined by "Discrete Conformal Equivalence of Polyhedral Surfaces" - Gillespi, Springborn, Crane, TOG V40 No4, 2021 This structure assumes that the surface mesh is fixed, and the intrinsic mesh shares the same vertex set as the surface mesh and is initialized with the same connectivity as the surface mesh. Note, it is assumed that the surface mesh has no bow-ties.
- L127 _public typedef_ `typedef FMeshConnection MyBase;`
- L129 _public function_ `FNormalCoordinates(): MyBase()`
- L131 _public prototype_ `FNormalCoordinates(const FDynamicMesh3& SurfMesh);`
- L134 _public prototype_ `void Reset(const FDynamicMesh3& SurfMesh);` — Reset the connection to the given (not owned) surface mesh
- L137 _public prototype_ `void Reset(TUniquePtr<FDynamicMesh3>& SurfMesh);` — Reset the connection to used an internally owned surface mesh
- L152 _public prototype_ `inline int32 NumEdgeCrossing(const int32 IntrinsicEID) const;` — @return the number of surface edges that cross this intrinsic edge. Note: it is the responsibility of the caller to ensure IntrinsicEID is a valid edge on the intrinsic mesh.
- L160 _public prototype_ `inline bool IsSurfaceEdgeSegment(const int32 IntrinsicEID) const;` — @return true if the specified intrinsic edge ( indicated by IntrinsicEID) is a segment of a surface edge. Note: By construction the initial intrinsic edges will have the same ID as the corresponding surface mesh edges, but edge splits will disrupt this. Also note: it is the responsibility of the caller to ensure IntrinsicEID is a valid edge on the intrinsic mesh.
- L167 _public prototype_ `inline int32 NumCornerEmanatingRefEdges(const FIndex3i& IntrinsicTriEIDs, const int32 TriCornerIndex) const;` — @return number of surface edges within the specified intrinsic triangle that are adjacent to the specified triangle corner. This excludes any surface edges that are along the intrinsic triangle boundary edges. note it is assumed that IntrinsicTriEIDs are edge ID of an intrinsic triangle, but no checking is done.
- L173 _public prototype_ `inline int32 NumCornerCrossingRefEdges(const FIndex3i& IntrinsicTriEIDs, const int32 TriCornerIndex) const;` — @return number of surface edges that cross corner the specified corner of the intrinsic triangle defined by the given edges. note, it is assumed that IntrinsicTriEIDs are edge ID of an intrinsic triangle, but no checking is done.
- L180 _public prototype_ `bool OnFlipEdge(const int32 T0ID, const FIndex3i& BeforeT0EIDs, const int32 T0OppVID, const int32 T1ID, const FIndex3i& BeforeT1EIDs, const int32 T1OppVID, const int32 FlippedEID);` — Update the NormalCoords and RoundaboutOrder after an intrinsic mesh edge flip. TriAEID, and TriBEID are the triangle edges of the two affected triangles prior (!) to flipping the specified edge. @return false if something failed
- L187 _public prototype_ `int32 GetNthEdgeID(const int32 VID, const int32 N) const;` — @return the edgeID of the N-th out-going edge in the SurfaceMesh (counting CCW from the reference edge for this vertex).
- L193 _public prototype_ `int32 GetEdgeOrder(const int32 VID, const int32 SurfaceEID) const;` — @return the Order of the edge EID about VID (counting CCW from the surface reference edge for this vertex). Note: this assumes that edge EID is adjacent to vertex VID - otherwise -1 is returned.
- L195 _public member_ `TDynamicVector<int32> NormalCoord;` — Per intrinsic edge: number of times src mesh edge crosses. By convention NormalCoord[EID] = -1 iff same as edge on surface mesh
- L196 _public member_ `TDynamicVector<FIndex3i> RoundaboutOrder;` — Per intrinsic Triangle, per (directed) edge: indicates the closest (when traveling ccw) reference mesh edge
- L198 _public member_ `TArray<int32> RefVertDegree;` — Per vertex in ref mesh, caches the result of counting the edges in RefMesh.VtxEdgeIter().
- L199 _public member_ `TArray<FIndex3i> EdgeOrder;` — Per surface triangle, per directed edge: number of edges past reference edge traveling ccw.
- L203 _protected prototype_ `void RebuildNormalCoordinates(const FDynamicMesh3& SurfMesh);` — rebuild the normal coordinate data in this connection. Assumes the base connection data is consistent with this surface mesh
- L245 _function_ `int32 FNormalCoordinates::NumEdgeCrossing(const int32 IntrinsicEID) const`
- L250 _function_ `bool FNormalCoordinates::IsSurfaceEdgeSegment(const int32 IntrinsicEID) const`
- L257 _function_ `int32 FNormalCoordinates::NumCornerEmanatingRefEdges(const FIndex3i& IntrinsicTriEIDs, const int32 TriCornerIndex) const`
- L277 _function_ `int32 FNormalCoordinates::NumCornerCrossingRefEdges(const FIndex3i& IntrinsicTriEIDs, const int32 TriCornerIndex) const`

#### struct `UE::Geometry::IntrinsicCorrespondenceUtils::FNormalCoordinates::FEdgeAndCrossingIdx`  
`struct FEdgeAndCrossingIdx`  
_L141-146_
- L143 _public member_ `int32 TID;` — triangle traversed
- L144 _public member_ `int32 EID;` — edge crossed.  This will be one of the three edges in GetTriEdges(TID)
- L145 _public member_ `int32 CIdx;` — index of curve relative to the edge crossed

#### struct `UE::Geometry::IntrinsicCorrespondenceUtils::FSignpost`  
`struct FSignpost : public FMeshConnection`  
_L212-243_
- inherits: `FMeshConnection`
- desc: Signpost Coordinates inspired by "Navigating Intrinsic Triangulations" Sharp, Soliman and Crane [2019, ACM Transactions on Graphics] This structure assumes that the surface mesh is fixed, but allows the intrinsic mesh to support operations like edge splits and triangle pokes. is initialized with the same connectivity as the surface mesh.  Note, it is assumed that the surface mesh has no bow-ties.
- L214 _public typedef_ `typedef FMeshConnection MyBase;`
- L215 _public prototype_ `FSignpost(const FDynamicMesh3& SurfaceMesh);`
- L226 _public prototype_ `void OnFlipEdge(const int32 EID, const FIndex2i AdjTris, const FIndex2i OpposingVerts, const FIndex2i PreFlipIndexOf, const double Opp0NewInternalAngle, const double Opp1NewInternalAngle);` — Update the signpost after an edge flip.  This requires information about the both the pre and post flip state. @param EID                  - edge that was flipped @param AdjTris              - IDs of the tris adjacent to flipped edge @param OpposingVerts        - verts opposite the edge, pre-flip.  i.e. EdgeFlipInfo.OpposingVerts @param PreFlipIndexOf       - edge index in the EID in the pre-fliped tris. i.e. {GetTriEdges(Tris[0]).IndexOf(EID), GetTriEdges(Tris[1]).IndexOf(EID)}; @param Opp0NewInternalAngle - internal angle of opposing vert 0 after the flip. i.e. InternalAngles[Tris[1]][1] @param Opp1NewInternalAngle - internal angle of opposing vert 1 after the flip. i.e  InternalAngles[Tris[0]][1];
- L240 _public member_ `TDynamicVector<FVector3d> IntrinsicEdgeAngles;` — Per-intrinsic Triangle - polar angles of each edge relative to the vertex it exits (i.e. edge 0 relative to vertex 0)
- L241 _public member_ `TDynamicVector<FSurfacePoint> IntrinsicVertexPositions;` — Per-intrinsic Vertex - Locates intrinsic mesh vertices relative to the surface defined by extrinsic mesh.
- L242 _public member_ `TDynamicVector<FGeometricInfo> GeometricVertexInfo;` — Per-intrinsic Vertex - Simple geometric information about the extrinsic surface in the neighborhood of intrinsic vert

#### struct `UE::Geometry::IntrinsicCorrespondenceUtils::FSignpost::FSurfaceTraceResult`  
`struct FSurfaceTraceResult`  
_L229-233_
- L231 _public member_ `FSurfacePoint SurfacePoint;` — point on the surface mesh
- L232 _public member_ `double Angle;` — polar angle relative to reference edge (on surface mesh) in the neighborhood of the surface point.

#### struct `UE::Geometry::IntrinsicCorrespondenceUtils::FSignpost::FGeometricInfo`  
`struct FGeometricInfo`  
_L235-239_
- L237 _public member_ `double ToRadians = 1.;` — 2pi / sum of angles at this vertex.  Will be 1 if the Gaussian curvature is 0
- L238 _public member_ `bool bIsInterior = false;` — false if on boundary or at a bow-tie.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DYNAMICMESH_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)
- L20 _namespace_ `namespace IntrinsicCorrespondenceUtils` (scope `UE::Geometry`)
- L74 _prototype_ `FVector3d AsR3Position(const FSurfacePoint& SurfacePoint, const FDynamicMesh3& Mesh, bool& bValidPoint);` (scope `UE::Geometry::IntrinsicCorrespondenceUtils`) — @return the R3 position of this surface point as applied to the input Mesh on return bValidPoint will be false if the edge / vertex / triangle ID referenced by this surface point is not an element of the mesh in question @param SurfacePoint - Position defined relative to the Mesh @param Mesh         - Dynamic mesh that defines a surface @param bValidPoint  - will be false if the vert, edge or tri that defines the surface point is not a member of Mesh
- L79 _function_ `static inline bool IsVertexPoint(const FSurfacePoint& SurfacePoint)` (scope `UE::Geometry::IntrinsicCorrespondenceUtils`) — @return true if the SurfacePoint corresponds to a vertex
- L86 _function_ `static inline bool IsEdgePoint(const FSurfacePoint& SurfacePoint)` (scope `UE::Geometry::IntrinsicCorrespondenceUtils`) — @return true if the SurfacePoint corresponds to an edge
- L93 _function_ `static inline bool IsFacePoint(const FSurfacePoint& SurfacePoint)` (scope `UE::Geometry::IntrinsicCorrespondenceUtils`) — @return true if the SurfacePoint corresponds to a face
- L306 _function_ `template <typename MeshType, typename FunctorType> bool VisitVertexAdjacentElements(const MeshType& Mesh, const int32 VID, const int32 StartEID, FunctorType& Functor)` (scope `UE::Geometry::IntrinsicCorrespondenceUtils`) — Utility to walk around a vertex (VID) visiting the adjacent edges and triangles. Note: this isn't appropriate for bow-ties as it will terminate upon encountering a mesh edge. If the vertex is on the mesh boundary, StartEID should correspond to the first boundary edge allowing for a ccw traversal of the vertex-adjacent faces.
- L316 _function_ `` (scope `UE::Geometry::IntrinsicCorrespondenceUtils::VisitVertexAdjacentElements`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/IntrinsicTriangulationMesh.h` (Public)


#### class `UE::Geometry::FSimpleIntrinsicEdgeFlipMesh`  
`class FSimpleIntrinsicEdgeFlipMesh`  
_L65-439_
- desc: The FSimpleIntrinsicEdgeFlipMesh is designed to work with the function FlipToDelaunay() to make an Intrinsic Delaunay Triangulation (IDT) of the same surface as a given FDynamicMesh, allowing for more robust cotangent-Laplacians (see LaplacianMatrixAssembly.h) The vertices in this FSimpleIntrinsicEdgeFlipMesh are exactly those found in the surface mesh since it supports edge flips, but no other operations that change the mesh connectivity, and no operations that affect the vertices. This mesh alone does not support computing the intersections of intrinsic edges with the surface mesh edges and as a result it can not be used to easily extract the path of an intrinsic edge. To do such computations FIntrinsicEdgeFlipMesh, FIntrinsicMesh or FIntrinsicTriangulation should be used. The API of FIntrinsicEdgeFlipMesh is similar to FDynamicMesh3, but only has a minimal subset of methods and some such as ::FlipEdge() and ::GetEdgeOpposingV() have very different implementations. In addition to managing vertices, triangles and edges this class also tracks edge lengths (as measured on the surface mesh) and for convenience the internal angles for each triangle.
- L69 _public typedef_ `using FEdge = FDynamicMesh3::FEdge;`
- L78 _public member_ `constexpr static int InvalidID = IndexConstants::InvalidID;` — InvalidID indicates that a vertex/edge/triangle ID is invalid
- L80 _public function_ `FSimpleIntrinsicEdgeFlipMesh()`
- L83 _public prototype_ `FSimpleIntrinsicEdgeFlipMesh(const FDynamicMesh3& SrcMesh);` — Constructor does ID-matching deep copy the basic mesh topology (but no attributes or groups)
- L85 _public prototype_ `FSimpleIntrinsicEdgeFlipMesh(const FSimpleIntrinsicEdgeFlipMesh&) = delete;`
- L88 _public prototype_ `void Clear();` — Discard all data
- L91 _public prototype_ `void Reset(const FDynamicMesh3& SrcMesh);` — Reset the mesh to an ID-matching deep copy the basic mesh topology (but no attributes or groups)
- L102 _public prototype_ `EMeshResult FlipEdge(int32 EID, FEdgeFlipInfo& EdgeFlipInfo);` — Flip a single edge in the Intrinsic Mesh. Note: After a successful flip, both triangles will share the same orientation (matching that of the pre-flip Edge.Tri.A) even if they had different orientations (e.g. cw & ccw) prior to flipping. @param EID indicates the edge to flip. @param EdgeFlipInfo [out] populated on return. @return a success or failure info.
- L106 _public function_ `double GetEdgeLength(int32 EID) const` — @return the intrinsic edge length of specified edge
- L116 _public function_ `FVector3d GetTriEdgeLengths(const int32 TID) const` — @return the intrinsic edge lengths for specified tri ordered to match the edges returned by ::GetEdges(TID)
- L128 _public function_ `double GetTriInternalAngleR(const int32 TID, const int32 IndexOf) const` — @return the interior angle of specified triangle corner @param TID             - ID of containing triangle @param IndexOf         - Index (i.e 0, 1, 2) of specified wedge of the triangle
- L144 _public prototype_ `FVector2d EdgeOpposingAngles(int32 EID) const;` — return FVector2( alpha_{ij} , beta_{ij} ) where alpha_{ij} and beta_{ij} are the two interior angles opposite the specified edge, EID. Expected angles are in the [0,2pi) range Note: if EID is a mesh boundary beta_{ij} is replaced by -MAX_DOUBLE
- L154 _public prototype_ `double EdgeCotanWeight(int32 EID) const;` — return 1/2 ( cot(alpha_{ij}) + cot(beta_{ij}) ) where alpha_{ij} and beta_{ij} are the to interior angles opposite the specified edge, EID. Note: if EID is a mesh boundary, cot(alpha_ij) is returned
- L160 _public function_ `FRefCountVector::IndexEnumerable EdgeIndicesItr() const` — @return enumerable object for valid edge indices suitable for use with range-based for, ie for ( int i : EdgeIndicesItr() )
- L166 _public function_ `FSmallListSet::ValueEnumerable VtxEdgesItr(int32 VID) const` — @return enumerable object for one-ring edges of a vertex, suitable for use with range-based for, ie for ( int i : VtxEdgesItr(VertexID) )
- L173 _public function_ `int32 GetVtxEdgeCount(int32 VID) const` — @return the valence of a vertex (the number of connected edges)
- L179 _public function_ `int32 TriangleCount() const` — @return number of triangles in the intrinsic mesh
- L185 _public function_ `int32 EdgeCount() const` — @return number of edges in the intrinsic mesh
- L191 _public function_ `int32 MaxEdgeID() const` — @return upper bound on the edge ID used in the mesh.  i.e. all edge IDs < MaxEdgeID
- L197 _public function_ `inline bool IsEdge(int32 EdgeID) const` — @return true if intrinsic mesh contains specified edge
- L203 _public function_ `inline bool IsBoundaryEdge(int32 EdgeID) const` — @return true if specified edge is on the boundary of intrinsic mesh
- L210 _public function_ `inline FEdge GetEdge(int32 EdgeID) const` — @return specified edge
- L217 _public function_ `inline FIndex2i GetEdgeV(int32 EdgeID) const` — @return the vertex IDs that define the given edge in intrinsic mesh
- L224 _public function_ `inline FIndex2i GetEdgeT(int32 EdgeID) const` — @return the triangle pair for an edge. The second triangle may be InvalidID
- L231 _public prototype_ `FIndex2i GetEdgeOpposingV(int32 EID) const;` — @return the vertex pair opposite specified edge. The second vertex may be InvalidID
- L234 _public function_ `inline bool IsVertex(int32 VertexID) const` — @return true if intrinsic mesh contains specified vertex
- L240 _public function_ `inline bool IsBoundaryVertex(int32 VertexID) const` — @return true if the specified vertex is adjacent to a boundary edge
- L256 _public function_ `inline FVector3d GetVertex(int32 VertexID) const` — @return the r3 position of the specified vertex
- L263 _public function_ `int32 MaxVertexID() const` — @return upper bound on the vertex ID used in the mesh.  i.e. all edge IDs < MaxVertexID
- L269 _public function_ `int32 MaxTriangleID() const` — @return upper bound on the triangle ID used in the mesh.  i.e. all triangle IDs < MaxTriangleID
- L275 _public function_ `FRefCountVector::IndexEnumerable TriangleIndicesItr() const` — @return enumerable object for valid triangle indices suitable for use with range-based for, ie for ( int i : TriangleIndicesItr() )
- L281 _public function_ `inline bool IsTriangle(int32 TriangleID) const` — @return true if intrinsic mesh contains specified triangle
- L287 _public function_ `inline FIndex3i GetTriangle(int32 TriangleID) const` — @return vertex ids for the three corners of the triangle (e.g. a, b, c)
- L294 _public function_ `inline const FIndex3i& GetTriangleRef(int TriangleID) const` — @return  reference to vertex ids for the three corners of the triangle (e.g. a, b, c)
- L301 _public function_ `inline FIndex3i GetTriEdges(int32 TriangleID) const` — @return edge ids for the three sides of the triangle (e.g. ab, bc, ca)
- L312 _public function_ `template <typename Vector3Type> Vector3Type Permute(int32 Index, const Vector3Type& Src) const` — cyclic permutation of the src vector such that the 'Index' entry in the src is the first entry in the result NB: Index must be 0, 1, or 2.
- L324 _public function_ `bool AreSameOrientation(int32 EID) const` — @return false if the two triangles adjacent to the indicated edge have the different orientation (eg counter-clockwise and clockwise), otherwise return true. Note: by convention this will return true for boundary edges ( or invalid edges ).
- L347 _protected function_ `FVector3d GetEdgeLengthTriple(const FIndex3i& EIDs) const` — @return three requested edge lengths
- L358 _protected prototype_ `FVector3d ComputeTriInternalAnglesR(const int32 TID) const;` — computes the angles based on the edge lengths, so must have valid EdgeLengths for this tri before calling. the order of the angles matches the order of the vertices that define the triangle, e.g. if (a, b, c) = GetTriangle() the (angle at a, angle at b, angle at c) = ComputeTriInternalAnglesR
- L364 _protected prototype_ `double GetOpposingVerticesDistance(int32 EID) const;` — @return the intrinsic distance between the two vertices opposite the specified edge NB: Will fail if EID is a boundary edge.
- L373 _protected prototype_ `EMeshResult FlipEdgeTopology(int32 eab, FEdgeFlipInfo& FlipInfo);` — update the mesh topology (e.g. triangles and edges) by doing an edge flip, but does not update the intrinsic edge lengths or angles. Note: this requires precomputed FlipInfo.bHadSameOrientation.
- L376 _protected function_ `void SetEdgeVerticesInternal(int32 EdgeID, int32 a, int32 b)` — update the existing edge to reference vertices 'a' and 'b'.
- L386 _protected function_ `inline void SetEdgeTrianglesInternal(int32 EdgeID, int32 t0, int32 t1)` — update the existing edge to reference triangles t0 and t1
- L392 _protected prototype_ `int32 ReplaceEdgeTriangle(int32 eID, int32 tOld, int32 tNew);` — replace tOld with tNew in an existing edge
- L394 _protected function_ `inline int32 ReplaceTriangleEdge(int32 tID, int32 eOld, int32 eNew)` — replace eOld with eNew in and existing triangle
- L413 _protected prototype_ `FIndex2i GetOrientedEdgeV(int32 EID, int32 TID) const;` — @return vertex pair in specified edge, oriented by the given triangle. note: the vertices may be the same. note: assumes EID is an edge in Triangle TID
- L416 _protected member_ `const int32 AddOneModThree[3] = { 1, 2, 0 };`
- L417 _protected member_ `const int32 AddTwoModThree[3] = { 2, 0, 1 };`
- L421 _protected member_ `TDynamicVector<FVector3d> Vertices{};` — list of vertex positions
- L422 _protected member_ `FRefCountVector VertexRefCounts{};` — Reference counts of vertex indices. For vertices that exist, the count is 1 + num_triangle_using_vertex. Iterate over this to find out which vertex indices are valid.
- L423 _protected member_ `FSmallListSet VertexEdgeLists;` — List of per-vertex edge one-rings
- L425 _protected member_ `TDynamicVector<FIndex3i> Triangles;` — List of triangle vertex - index triplets[Vert0 Vert1 Vert2]
- L426 _protected member_ `FRefCountVector TriangleRefCounts{};` — Reference counts of triangle indices. Ref count is always 1 if the triangle exists. Iterate over this to find out which triangle indices are valid.
- L427 _protected member_ `TDynamicVector<FIndex3i> TriangleEdges;` — List of triangle edge triplets [Edge0 Edge1 Edge2], note these correspond to [Vert0-Vert1, Vert1-Vert2, Vert2-Vert0] for a given triangle.
- L429 _protected member_ `TDynamicVector<FEdge> Edges;` — List of edge elements. An edge is four elements [VertA, VertB, Tri0, Tri1], where VertA < VertB, and Tri1 may be InvalidID (if the edge is a boundary edge)
- L430 _protected member_ `FRefCountVector EdgeRefCounts{};` — Reference counts of edge indices. Ref count is always 1 if the edge exists. Iterate over this to find out which edge indices are valid.
- L436 _protected member_ `TDynamicVector<double> EdgeLengths;` — Length of each intrinsic edge in the Mesh: note these may differ from (Vert0 - Vert1).Lenght().
- L437 _protected member_ `TDynamicVector<FVector3d> InternalAngles;` — Interior Angles for each triangle: note may differ from FDynamicMesh::GetTriInternalAnglesR(TID) as they are computed from intrinsic edge lengths

#### struct `UE::Geometry::FSimpleIntrinsicEdgeFlipMesh::FEdgeFlipInfo`  
`struct FEdgeFlipInfo : DynamicMeshInfo::FEdgeFlipInfo`  
_L72-75_
- inherits: `DynamicMeshInfo::FEdgeFlipInfo`
- desc: information collected when flipping an edge.
- L74 _public member_ `bool bHadSameOrientations = true;` — will be false if the original triangles had different orientations.

#### class `UE::Geometry::FSimpleIntrinsicMesh`  
`class FSimpleIntrinsicMesh : public FSimpleIntrinsicEdgeFlipMesh`  
_L454-558_
- inherits: `FSimpleIntrinsicEdgeFlipMesh`
- desc: FSimpleIntrinsicMesh extends FSimpleIntrinsicEdgeFlipMesh to support edge splits and triangle pokes in addition to edge flips. The surface mesh vertices will be a subset of the intrinsic mesh vertex set. This is intended as a base class for more sophisticated intrinsic mesh classes, as it does not explicitly track the topology changes relative to the original surface mesh.  For example it does not record the locations on the surface mesh of any new intrinsic vertices or the locations of intrinsic mesh edge intersections with the surface mesh edges. FIntrinsicMesh and FIntrinsicTriangulation are derived from this class and each maintain their own connection with the surface mesh ( "normal coordinates" or "signpost data") that can track these surface mesh locations and can be used to reconstruct paths (e.g. intrinsic edges) on the surface mesh.
- L457 _public typedef_ `typedef FSimpleIntrinsicEdgeFlipMesh MyBase;`
- L458 _public typedef_ `using FEdge = FSimpleIntrinsicEdgeFlipMesh::FEdge;`
- L459 _public typedef_ `using FEdgeFlipInfo = FSimpleIntrinsicEdgeFlipMesh::FEdgeFlipInfo;`
- L460 _public typedef_ `using FPokeTriangleInfo = DynamicMeshInfo::FPokeTriangleInfo;`
- L461 _public typedef_ `using FEdgeSplitInfo = DynamicMeshInfo::FEdgeSplitInfo;`
- L464 _public member_ `constexpr static int InvalidID = IndexConstants::InvalidID;` — InvalidID indicates that a vertex/edge/triangle ID is invalid
- L466 _public function_ `FSimpleIntrinsicMesh()`
- L469 _public function_ `FSimpleIntrinsicMesh(const FDynamicMesh3& SrcMesh) : MyBase(SrcMesh)` — Constructor does ID-matching deep copy the basic mesh topology (but no attributes or groups)
- L473 _public prototype_ `FSimpleIntrinsicMesh(const FSimpleIntrinsicMesh&) = delete;`
- L484 _public prototype_ `EMeshResult PokeTriangle(int32 TID, const FVector3d& BaryCoordinates, FPokeTriangleInfo& PokeInfo);` — Insert a new vertex inside an intrinsic triangle, ie do a 1 to 3 triangle split @param TID             - index of triangle to poke @param BaryCoordinates - barycentric coordinates of poke position @param PokeInfo        - returned information about new and modified mesh elements @return Ok on success, or enum value indicates why operation cannot be applied. Mesh remains unmodified on error.
- L499 _public prototype_ `EMeshResult SplitEdge(int32 EdgeAB, FEdgeSplitInfo& SplitInfo, double SplitParameterT = 0.5);` — Split an intrinsic edge of the mesh by inserting a vertex. This creates a new triangle on either side of the edge (ie a 2-4 split). If the original edge had vertices [a,b], with triangles t0=[a,b,c] and t1=[b,a,d],  then the split inserts new vertex f. After the split t0=[a,f,c] and t1=[f,a,d], and we have t2=[f,b,c] and t3=[f,d,b]  (it's best to draw it out on paper...) SplitInfo.OriginalTriangles = {t0, t1} and SplitInfo.NewTriangles = {t2, t3} @param EdgeAB          - index of the edge to be split @param SplitInfo       - returned information about new and modified mesh elements @param SplitParameterT - defines the position along the edge that we split at, must be between 0 and 1, and is assumed to be based on the order of vertices in t0 @return Ok on success, or enum value indicates why operation cannot be applied. Mesh remains unmodified on error.
- L507 _protected prototype_ `EMeshResult PokeTriangleTopology(int32 TID, FPokeTriangleInfo& PokeInfo);` — Updates the mesh connectivity by adding a new vertex at the vertex-averaged location. Note: this does not update any of the intrinsic lengths, positions, angles, etc. those quantities must be updated after.  See ::PokeTriangle()
- L513 _protected prototype_ `EMeshResult SplitEdgeTopology(int32 EdgeAB, FEdgeSplitInfo& SplitInfo);` — Updates the mesh connectivity by adding a new vertex at the vertex-averaged location. Note: this does not update any of the intrinsic lengths, positions, angles, etc. those quantities must be updated after.  See ::SplitEdge()
- L516 _protected function_ `inline void AllocateEdgesList(int32 VertexID)` — allocate, or clear existing edge list for specified vertex
- L526 _protected function_ `inline int32 AppendVertex(const FVector3d& vPos)` — add new vertex to the mesh topology, does not update any of the intrinsic quantities
- L535 _protected function_ `inline int32 AddEdgeInternal(int32 vA, int32 vB, int32 tA, int32 tB = InvalidID)` — add new edge to the mesh topology, does not update any of the intrinsic quantities
- L551 _protected function_ `inline int32 AddTriangleInternal(int32 a, int32 b, int32 c, int32 e0, int32 e1, int32 e2)` — add new triangle to the mesh topology, does not update any of the intrinsic quantities

#### struct `UE::Geometry::TEdgeCorrespondence`  
`template <typename IntrinsicMeshType> struct TEdgeCorrespondence`  
_L575-603_
- desc: TEdgeCorrespondence allows intrinsic edges to be traced across the underlying surface mesh. When computing a large number intrinsic edge traces, this is to be preferred over the TraceEdge() intrinsic mesh methods because it avoids redundant computations.  But when tracing a small number of intrinsic edges the large up-front cost of computing information the entire mesh will make use of this class sub-optimal. During construction a list of surface mesh edges crossed by each intrinsic edge is stored. The Trace operation for an intrinsic edge uses this information to unfold the crossed surface triangles into a 2d triangle strip upon which the actual trace takes place. This is only for use with intrinsic mesh implementations that support  'normal coordinates' when doing flips/splits and pokes. such as the FIntrinsicMesh and FIntrinsicEdgeFlipMesh.
- L578 _public typedef_ `using FEdgeAndCrossingIdx = IntrinsicCorrespondenceUtils::FNormalCoordinates::FEdgeAndCrossingIdx;`
- L579 _public typedef_ `using FSurfacePoint = IntrinsicCorrespondenceUtils::FSurfacePoint;`
- L582 _public function_ `TEdgeCorrespondence(const IntrinsicMeshType& IntrinsicMesh)`
- L587 _public prototype_ `void Setup(const IntrinsicMeshType& IntrinsicMesh);`
- L597 _public prototype_ `TArray<UE::Geometry::IntrinsicCorrespondenceUtils::FSurfacePoint> TraceEdge(int32 IntrinsicEID, double CoalesceThreshold = 0., bool bReverse = false) const;` — @return Array of FSurfacePoints relative to the ExtrinsicMesh that represent the specified intrinsic mesh edge. This is directed relative to traversal of the first adjacent triangle (GetEdgeT().[0]), unless bReverse is true @param IntrinsicEID      - ID of the intrinsic mesh edge to be traced. @param CoalesceThreshold - in barycentric units [0,1], edge crossings within this threshold are snapped to the nearest vertex. and any resulting repetitions of vertex surface points are replaced with a single vertex surface point. @param bReverse          - if true, trace edge direction is reversed
- L600 _public member_ `const IntrinsicMeshType* IntrinsicMesh;` — the intrinsic mesh
- L601 _public member_ `const FDynamicMesh3* SurfaceMesh;` — the surface mesh
- L602 _public member_ `TArray<TArray<int32>> SurfaceEdgesCrossed;` — array of surface edge crossings per intrinsic edge.

#### class `UE::Geometry::FIntrinsicEdgeFlipMesh`  
`class FIntrinsicEdgeFlipMesh : public FSimpleIntrinsicEdgeFlipMesh`  
_L643-742_
- inherits: `FSimpleIntrinsicEdgeFlipMesh`
- desc: FIntrinsicEdgeFlipMesh augments the base class FSimpleIntrinsicEdgeFlipMesh with the addition of a 'normal coordinate' based correspondence with the surface mesh. This class supports both the trace of intrinsic mesh edges across the surface mesh, and the trace of surface mesh edges across the intrinsic mesh. Note, because only edge flips are supported (no edge split or triangle pokes), the vertex set of the intrinsic mesh and the surface (i.e. extrinsic) mesh will be the same. The expected use // generate the implicit mesh from a surface mesh FIntrinsicEdgeFlipMesh  ImplicitMesh( DynamicMesh ); .. do some edge flips .. perhaps FlipToDelaunay( ImplicitMesh, ..) // if only a small percentage of the intrinsic edges are to be traced, this can be done directly as auto TracedIntrinsicEdge  =  ImplicitMesh.TraceEdge(IntrinsicEdgeID); // alternately if a large number of edges will be traced, a correspondence will be more efficient. // create a correspondence that allows the edges of the implicit mesh to be traced on the surface mesh FIntrinsicEdgeFlipMesh::FEdgeCorrespondence  Correspondence = ImplicitMesh.ComputeEdgeCorrespondence(); for (.. doing multiple traces..  ) { // trace desired edge across the surface mesh int32 IntrinsicEdgeID = auto TracedIntrinsicEdge  =  Correspondence.TraceEdge(IntrinsicEdgeID); } NB: The lifetime of this structure should not exceed that of the original FDynamicMesh as this class holds a pointer to that mesh to reference locations on its surface. Also,
- L646 _public typedef_ `typedef FSimpleIntrinsicEdgeFlipMesh MyBase;`
- L647 _public typedef_ `using FEdge = FSimpleIntrinsicEdgeFlipMesh::FEdge;`
- L648 _public typedef_ `using FEdgeFlipInfo = FSimpleIntrinsicEdgeFlipMesh::FEdgeFlipInfo;`
- L649 _public typedef_ `using FSurfacePoint = IntrinsicCorrespondenceUtils::FSurfacePoint;`
- L650 _public typedef_ `using FEdgeAndCrossingIdx = IntrinsicCorrespondenceUtils::FNormalCoordinates::FEdgeAndCrossingIdx;`
- L652 _public prototype_ `FIntrinsicEdgeFlipMesh(const FDynamicMesh3& SurfaceMesh);`
- L654 _public prototype_ `FIntrinsicEdgeFlipMesh() = delete;`
- L655 _public prototype_ `FIntrinsicEdgeFlipMesh(const FIntrinsicEdgeFlipMesh&) = delete;`
- L658 _public function_ `const FDynamicMesh3* GetExtrinsicMesh() const` — @return pointer the reference mesh, note the FIntrinsicTriangulation does not manage the lifetime of this mesh
- L674 _public prototype_ `TArray<FSurfacePoint> TraceEdge(int32 IntrinsicEID, double CoalesceThreshold = 0., bool bReverse = false) const;` — @return Array of FSurfacePoints relative to the surface mesh that represent the specified intrinsic mesh edge. This is directed relative to traversal of the first adjacent triangle (GetEdgeT().[0]), unless bReverse is true @param CoalesceThreshold - in barycentric units [0,1], edge crossings with in this threshold are snapped to the nearest vertex. and any resulting repetitions of vertex surface points are replaced with a single vertex surface point. @param bReverse          - if true, trace edge direction is reversed Note: when tracing few edges, this method is preferred to using the FEdgeCorrespondence based tracing (see FEdgeCorrespondence below). But when tracing a large percentage of the mesh edges the FEdgeCorrespondence will be faster as it reuses intermediate results.
- L683 _public prototype_ `EMeshResult FlipEdge(int32 EID, FEdgeFlipInfo& EdgeFlipInfo);` — Flip a single edge in the Intrinsic Mesh. @param EdgeFlipInfo [out] populated on return. @return a success or failure info.
- L686 _public typedef_ `typedef TEdgeCorrespondence< FIntrinsicEdgeFlipMesh > FEdgeCorrespondence;`
- L688 _public function_ `FEdgeCorrespondence ComputeEdgeCorrespondence() const`
- L696 _public function_ `const IntrinsicCorrespondenceUtils::FNormalCoordinates& GetNormalCoordinates() const` — @return NormalCoordinate data structure that counts the number of regular surface (extrinsic) mesh edge-crossings for each intrinsic mesh edge.
- L709 _public prototype_ `TArray<FEdgeAndCrossingIdx> GetImplicitEdgeCrossings(const int32 SurfaceEID, const bool bReverse = false) const;` — Trace the specified surface (extrinsic) mesh edge across the intrinsic mesh.  By default this traces from vertex EdgeV.A to vertex EdgeV.B where EdgeV = SurfaceMesh.GetEdgeV(SurfaceEID). @param SurfaceEID   - the surface edge to be traced @param bReverse     - reverses the direction of the trace giving EdgeV.B -> EdgeV.A @return array of intrinsic edges crossed between the specified vertices.  This can be used to compute the actual MeshPoints on the surface if desired.
- L719 _public prototype_ `TArray<FSurfacePoint> TraceSurfaceEdge(int32 SurfaceEID, double CoalesceThreshold, bool bReverse = false) const;` — Trace the specified surface (extrinsic) mesh edge across the intrinsic mesh.  By default this traces from vertex EdgeV.A to vertex EdgeV.B where EdgeV = SurfaceMesh.GetEdgeV(SurfaceEID). @param SurfaceEID   - the surface edge to be traced @param bReverse     - reverses the direction of the trace giving EdgeV.B -> EdgeV.A @return array of surface points defined relative to the intrinsic mesh.  In particular, the array will be a vertex followed by a sequence of (intrinsic) edge crossings.
- L724 _public function_ `bool IsSurfaceVertex(int VID) const` — @return true if the intrinsic vertex corresponds to a surface vertex.
- L732 _public function_ `FSurfacePoint GetVertexSurfacePoint(int32 VID) const` — @return the position of the intrinsic vertex relative to the underlying surface mesh
- L740 _protected typedef_ `using FNormalCoordinates = IntrinsicCorrespondenceUtils::FNormalCoordinates;`
- L741 _protected member_ `FNormalCoordinates NormalCoordinates;` — connection and integer-based coordinates used in reconstructing {intrinsic, surface} edges on the {surface, intrinsic} mesh

#### class `UE::Geometry::FIntrinsicMesh`  
`class FIntrinsicMesh : public FSimpleIntrinsicMesh`  
_L766-895_
- inherits: `FSimpleIntrinsicMesh`
- L769 _public typedef_ `typedef FSimpleIntrinsicMesh MyBase;`
- L771 _public typedef_ `using FEdge = FSimpleIntrinsicMesh::FEdge;`
- L772 _public typedef_ `using FEdgeFlipInfo = FSimpleIntrinsicMesh::FEdgeFlipInfo;`
- L773 _public typedef_ `using FSurfacePoint = IntrinsicCorrespondenceUtils::FSurfacePoint;`
- L774 _public typedef_ `using FEdgeAndCrossingIdx = IntrinsicCorrespondenceUtils::FNormalCoordinates::FEdgeAndCrossingIdx;`
- L775 _public typedef_ `using FPokeTriangleInfo = DynamicMeshInfo::FPokeTriangleInfo;`
- L776 _public typedef_ `using FEdgeSplitInfo = DynamicMeshInfo::FEdgeSplitInfo;`
- L778 _public prototype_ `FIntrinsicMesh() = delete;`
- L779 _public prototype_ `FIntrinsicMesh(const FIntrinsicMesh&) = delete;`
- L781 _public prototype_ `FIntrinsicMesh(const FDynamicMesh3& SurfaceMesh);`
- L784 _public function_ `const FDynamicMesh3* GetExtrinsicMesh() const` — @return pointer the reference mesh, note the FIntrinsicTriangulation does not manage the lifetime of this mesh
- L796 _public prototype_ `EMeshResult FlipEdge(int32 EID, FEdgeFlipInfo& EdgeFlipInfo);` — Flip a single edge in the Intrinsic Mesh. @param EdgeFlipInfo [out] populated on return. @return a success or failure info.
- L806 _public prototype_ `EMeshResult PokeTriangle(int32 TID, const FVector3d& BaryCoordinates, FPokeTriangleInfo& PokeInfo);` — Insert a new vertex inside an intrinsic triangle, ie do a 1 to 3 triangle split @param TID             - index of triangle to poke @param BaryCoordinates - barycentric coordinates of poke position @param PokeInfo        - returned information about new and modified mesh elements @return Ok on success, or enum value indicates why operation cannot be applied. Mesh remains unmodified on error.
- L820 _public prototype_ `EMeshResult SplitEdge(int32 EdgeAB, FEdgeSplitInfo& SplitInfo, double SplitParameterT = 0.5);` — Split an intrinsic edge of the mesh by inserting a vertex. This creates a new triangle on either side of the edge (ie a 2-4 split). If the original edge had vertices [a,b], with triangles t0=[a,b,c] and t1=[b,a,d],  then the split inserts new vertex f. After the split t0=[a,f,c] and t1=[f,a,d], and we have t2=[f,b,c] and t3=[f,d,b]  (it's best to draw it out on paper...) SplitInfo.OriginalTriangles = {t0, t1} and SplitInfo.NewTriangles = {t2, t3} @param EdgeAB          - index of the edge to be split @param SplitInfo       - returned information about new and modified mesh elements @param SplitParameterT - defines the position along the edge that we split at, must be between 0 and 1, and is assumed to be based on the order of vertices in t0 @return Ok on success, or enum value indicates why operation cannot be applied. Mesh remains unmodified on error.
- L826 _public function_ `const IntrinsicCorrespondenceUtils::FNormalCoordinates& GetNormalCoordinates() const` — @return NormalCoordinate data structure that counts regular surface (extrinsic) mesh edge-crossing for each intrinsic mesh edge.
- L842 _public prototype_ `TArray<FSurfacePoint> TraceEdge(int32 IntrinsicEID, double CoalesceThreshold = 0., bool bReverse = false) const;` — @return Array of FSurfacePoints relative to the surface mesh that represent the specified intrinsic mesh edge. This is directed relative to traversal of the first adjacent triangle (GetEdgeT()[0]), unless bReverse is true @param CoalesceThreshold - in barycentric units [0,1], edge crossings with in this threshold are snapped to the nearest vertex. and any resulting repetitions of vertex surface points are replaced with a single vertex surface point. @param bReverse          - if true, trace edge direction is reversed Note: when tracing few edges, this method is preferred to using the FEdgeCorrespondence based tracing (see FEdgeCorrespondence below). But when tracing a large percentage of the mesh edges the FEdgeCorrespondence will be faster as it reuses intermediate results.
- L852 _public prototype_ `TArray<FEdgeAndCrossingIdx> GetImplicitEdgeCrossings(const int32 SurfaceEID, const bool bReverse = false) const;` — Trace the specified surface (extrinsic) mesh edge across the intrinsic mesh.  By default this traces from vertex EdgeV.A to vertex EdgeV.B where EdgeV = SurfaceMesh.GetEdgeV(SurfaceEID). @param SurfaceEID   - the surface edge to be traced @param bReverse     - reverses the direction of the trace giving EdgeV.B -> EdgeV.A @return array of intrinsic edges crossed between the specified vertices.  This can be used to compute the actual MeshPoints on the surface if desired.
- L862 _public prototype_ `TArray<FSurfacePoint> TraceSurfaceEdge(int32 SurfaceEID, double CoalesceThreshold, bool bReverse = false) const;` — Trace the specified surface (extrinsic) mesh edge across the intrinsic mesh.  By default this traces from vertex EdgeV.A to vertex EdgeV.B where EdgeV = SurfaceMesh.GetEdgeV(SurfaceEID). @param SurfaceEID   - the surface edge to be traced @param bReverse     - reverses the direction of the trace giving EdgeV.B -> EdgeV.A @return array of surface points defined relative to the intrinsic mesh.  In particular, the array will be a vertex followed by a sequence of (intrinsic) edge crossings.
- L865 _public typedef_ `typedef TEdgeCorrespondence< FIntrinsicMesh > FEdgeCorrespondence;`
- L867 _public function_ `FEdgeCorrespondence ComputeEdgeCorrespondence() const`
- L876 _public function_ `FVector3d GetVertexPosition(int32 VID) const` — @return position in r3 of an intrinsic vertex.
- L884 _public function_ `FSurfacePoint GetVertexSurfacePoint(int32 VID) const` — @return the position of the intrinsic vertex relative to the underlying surface mesh
- L891 _protected typedef_ `using FNormalCoordinates = IntrinsicCorrespondenceUtils::FNormalCoordinates;`
- L892 _protected member_ `FNormalCoordinates NormalCoordinates;` — connection and integer-based coordinates used in reconstructing {intrinsic, surface} edges on the {surface, intrinsic} mesh
- L894 _protected member_ `TDynamicVector<FSurfacePoint> IntrinsicVertexPositions;` — Per-intrinsic Vertex - Locates intrinsic mesh vertices relative to the surface defined by extrinsic mesh.

#### class `UE::Geometry::FIntrinsicTriangulation`  
`class FIntrinsicTriangulation : public FSimpleIntrinsicMesh`  
_L916-1026_
- inherits: `FSimpleIntrinsicMesh`
- desc: Class that manages the intrinsic triangulation of a given FDynamicMesh. This supports mesh operations that: SplitEdge, PokeTriangle, FlipEdge. Both SplitEdge and PokeTriangle will generate new vertices and triangles in the intrinsic triangulation.  These vertices will live on the surface of the original mesh and their location (in R3 and relative to the original surface ) is computed by tracing a path on the original mesh. NB: The lifetime of this structure should not exceed that of the original FDynamicMesh as this class holds a pointer to that mesh to reference locations on its surface. Also, this class isn't currently expected to work with surface meshes that have bow-ties. Note:  This assumes but does not check that the FDynamicMesh3 "Surface Mesh" has consistent orientation of all triangles.
- L921 _public typedef_ `typedef FSimpleIntrinsicMesh MyBase;`
- L923 _public typedef_ `using FEdgeFlipInfo = FSimpleIntrinsicMesh::FEdgeFlipInfo;`
- L924 _public typedef_ `using FEdgeSplitInfo = FSimpleIntrinsicMesh::FEdgeSplitInfo;`
- L925 _public typedef_ `using FPokeTriangleInfo = FSimpleIntrinsicMesh::FPokeTriangleInfo;`
- L926 _public typedef_ `using FSurfacePoint = IntrinsicCorrespondenceUtils::FSurfacePoint;`
- L928 _public prototype_ `FIntrinsicTriangulation(const FDynamicMesh3& SrcMesh);`
- L930 _public prototype_ `FIntrinsicTriangulation() = delete;`
- L931 _public prototype_ `FIntrinsicTriangulation(const FIntrinsicTriangulation&) = delete;`
- L935 _public function_ `const FDynamicMesh3* GetExtrinsicMesh() const` — @return pointer the reference mesh, note the FIntrinsicTriangulation does not manage the lifetime of this mesh
- L949 _public prototype_ `TArray<FIntrinsicTriangulation::FSurfacePoint> TraceEdge(int32 EID, double CoalesceThreshold = 0., bool bReverse = false) const;` — @return Array of FSurfacePoints relative to the ExtrinsicMesh that represent the specified intrinsic mesh edge. This is directed from vertex EdgeV.A to vertex EdgeV.B unless bReverse is true @param CoalesceThreshold - in barycentric units [0,1], edge crossings with in this threshold are snapped to the nearest vertex. and any resulting repetitions of vertex surface points are replaced with a single vertex surface point. @param bReverse          - if true, trace edge from EdgeV.B to EdgeV.A
- L954 _public function_ `const FIntrinsicTriangulation::FSurfacePoint& GetVertexSurfacePoint(int32 VID) const` — @return FSurfacePoint for the specified intrinsic vertex.
- L963 _public function_ `FVector3d GetVertexPosition(int32 VID) const` — @return position in r3 of an intrinsic vertex.
- L974 _public prototype_ `EMeshResult FlipEdge(int32 EID, FEdgeFlipInfo& EdgeFlipInfo);` — Flip a single edge in the Intrinsic Mesh. @param EdgeFlipInfo [out] populated on return. @return a success or failure info.
- L985 _public prototype_ `EMeshResult PokeTriangle(int32 TID, const FVector3d& BaryCoordinates, FPokeTriangleInfo& PokeInfo);` — Insert a new vertex inside an intrinsic triangle, ie do a 1 to 3 triangle split @param TID             - index of triangle to poke @param BaryCoordinates - barycentric coordinates of poke position @param PokeInfo        - returned information about new and modified mesh elements @return Ok on success, or enum value indicates why operation cannot be applied. Mesh remains unmodified on error.
- L1000 _public prototype_ `EMeshResult SplitEdge(int32 EdgeAB, FEdgeSplitInfo& SplitInfo, double SplitParameterT = 0.5);` — Split an intrinsic edge of the mesh by inserting a vertex. This creates a new triangle on either side of the edge (ie a 2-4 split). If the original edge had vertices [a,b], with triangles t0=[a,b,c] and t1=[b,a,d],  then the split inserts new vertex f. After the split t0=[a,f,c] and t1=[f,a,d], and we have t2=[f,b,c] and t3=[f,d,b]  (it's best to draw it out on paper...) SplitInfo.OriginalTriangles = {t0, t1} and SplitInfo.NewTriangles = {t2, t3} @param EdgeAB          - index of the edge to be split @param SplitInfo       - returned information about new and modified mesh elements @param SplitParameterT - defines the position along the edge that we split at, must be between 0 and 1, and is assumed to be based on the order of vertices in t0 @return Ok on success, or enum value indicates why operation cannot be applied. Mesh remains unmodified on error.
- L1019 _protected prototype_ `double UpdateVertexByEdgeTrace(const int32 UpdateVID, const int32 StartVID, const double TracePolarDir, const double TraceDistance);` — Given edge EID connects UpdateVID and StartVID, this update the SurfacePosition of the vertex UpdateVID by tracing the edge EID a distance TraceDistance from StartVID. @return               - the polar angle of the tracing edge incident to VID ( relative to the local reference edge. ) @param UpdateVID      - ID of intrinsic vertex who's surface position is updated by this trace @param StartVID       - ID of intrinsic vertex where the trace starts @param TracePolarDir  - Local direction of the trace. @param TraceDistance  - Distance, measured on the extrinsic mesh surface to trace.
- L1023 _protected typedef_ `using FSignpost = IntrinsicCorrespondenceUtils::FSignpost;`
- L1024 _protected member_ `FSignpost SignpostData;` — connection and directional-based coordinates used in reconstructing {intrinsic, surface} edges on the {surface, intrinsic} mesh vert

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DYNAMICMESH_API`
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Geometry` (scope `UE`)
- L1037 _prototype_ `int32 FlipToDelaunay(FSimpleIntrinsicEdgeFlipMesh& IntrinsicMesh, TSet<int>& Uncorrected, const int32 MaxFlipCount = TMathUtilConstants<int>::MaxReal);` (scope `UE::Geometry`) — Perform edge flips on intrinsic mesh until either the MaxFlipCount is reached or the mesh is fully Delaunay @param IntrinsicMesh - The mesh to be operated on. @param Uncorrected   - contains on return, all the edges that could not be flipped (e.g. edge shared by non-convex pair of triangles) @return  the number of flips.
- L1038 _prototype_ `int32 FlipToDelaunay(FIntrinsicEdgeFlipMesh& IntrinsicMesh, TSet<int>& Uncorrected, const int32 MaxFlipCount = TMathUtilConstants<int>::MaxReal);` (scope `UE::Geometry`)
- L1039 _prototype_ `int32 FlipToDelaunay(FSimpleIntrinsicMesh& IntrinsicMesh, TSet<int>& Uncorrected, const int32 MaxFlipCount = TMathUtilConstants<int>::MaxReal);` (scope `UE::Geometry`)
- L1040 _prototype_ `int32 FlipToDelaunay(FIntrinsicMesh& IntrinsicMesh, TSet<int>& Uncorrected, const int32 MaxFlipCount = TMathUtilConstants<int>::MaxReal);` (scope `UE::Geometry`)
- L1041 _prototype_ `int32 FlipToDelaunay(FIntrinsicTriangulation& IntrinsicMesh, TSet<int>& Uncorrected, const int32 MaxFlipCount = TMathUtilConstants<int>::MaxReal);` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/JoinMeshLoops.h` (Public)


#### class `UE::Geometry::FJoinMeshLoops`  
`class FJoinMeshLoops`  
_L31-95_
- desc: FJoinMeshLoops connects two open loops of a mesh with a quad-strip. A 1-1 match between the loop vertices is assumed. The fill strip currently is configured so that: - entire strip is assigned a new face group - the entire strip becomes a separate "normal island", ie hard normals at border with existing mesh - the strip is unwrapped into a UV rectangle starting at vertex 0 and ending back at 0 again
- L40 _public member_ `FDynamicMesh3* Mesh;` — The mesh that we are modifying
- L43 _public member_ `float UVScaleFactor = 1.0f;` — quads on the stitch loop are scaled by this amount
- L46 _public member_ `TArray<int32> LoopA;` — first loop
- L49 _public member_ `TArray<int32> LoopB;` — second loop
- L57 _public member_ `TArray<FIndex2i> JoinQuads;` — quads along the join strip, in order of loops. Each quad is two triangle indices
- L59 _public member_ `TArray<int32> JoinTriangles;` — triangles of the quads flattend out (convenient), ie size = 2*NumQuads
- L62 _public member_ `TArray<int32> NewGroups;` — groups created by the operation (currently 1)
- L64 _public member_ `TArray<int32> QuadGroups;` — group for each quad, ie size = NumQuads   (currently all have same value)
- L67 _public prototype_ `FJoinMeshLoops(FDynamicMesh3* Mesh);`
- L68 _public prototype_ `FJoinMeshLoops(FDynamicMesh3* Mesh, const TArray<int32>& LoopA, const TArray<int32>& LoopB);`
- L70 _public prototype_ `virtual ~FJoinMeshLoops() = default;`
- L76 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot
- L89 _public prototype_ `virtual bool Apply();` — Apply the Extrude operation to the input mesh. @return true if the algorithm succeeds

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DYNAMICMESH_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MedialSkeletonSkinBinding.h` (Public)


#### struct `UE::Geometry::SkinBinding::FBindMedialSkeletonSettings`  
`struct FBindMedialSkeletonSettings`  
_L13-24_
- L17 _public member_ `int32 ClusterNeighborSearchRange = 1;` — Search range in local medial skeleton to use when binding vertices -- i.e. a value of 1 will restrict vertices to bind to clusters within the 1-ring of their best-fit cluster
- L20 _public member_ `FBindSettings BindSettings;` — General skin weight binding settings
- L23 _public member_ `MedialAxis::FMedialSkeletonToTreeSkeletonOptions AnimationSkeletonOptions;` — Options controlling conversion to an animation skeleton

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L10 _namespace_ `namespace SkinBinding` (scope `UE::Geometry`)
- L39 _prototype_ `bool CreateSkinWeightsFromMedialSkeleton( const MedialAxis::FMedialSkeleton& InMedialSkeleton, FDynamicMesh3& TargetMesh, bool& bOutMeshWasCompatible, FName WeightProfileName, const FBindMedialSkeletonSettings& Settings, int32 RootIndex = INDEX_NONE);` (scope `UE::Geometry::SkinBinding`) — Convert a medial skeleton + mesh to a skinned mesh, using the medial skeleton clusters to both define the animation skeleton and to help guide the skinning -- binding vertices to bones within the local graph neighborhood of their corresponding medial skeleton cluster/medial sphere @param InMedialSkeleton Source medial skeleton @param TargetMesh Mesh to receive skeleton attributes and skin weights @param bOutMeshWasCompatible Reports whether the mesh was compatible with the medial skeleton (had a valid vertex->cluster mapping). If not, mesh can still be bound but will not respect some options. @param WeightProfileName Skin weight profile name to use @param Settings Options controlling the weight binding and skeleton conversion @param RootIndex Specify the medial skeleton cluster to prefer as the animation skeleton's root bone. If INDEX_NONE, a default root will be selected automatically. @return true on success, false if could not be bound (e.g. if medial skeleton was empty)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MeshAttributeTransfer.h` (Public)


#### enum `UE::Geometry::EMeshAttributeTransferType`  
`enum class EMeshAttributeTransferType`  
_L18-21_
- L20 _public enumerator_ `MaterialID`

#### enum `UE::Geometry::EMeshAttributeTransferError`  
`enum class EMeshAttributeTransferError`  
_L23-30_
- L25 _public enumerator_ `InvalidSource`
- L26 _public enumerator_ `InvalidTarget`
- L27 _public enumerator_ `SourceMissingAttribute`
- L28 _public enumerator_ `TargetMissingAttribute`
- L29 _public enumerator_ `InvalidOperationForInputs`

#### class `UE::Geometry::FMeshAttributeTransfer`  
`class FMeshAttributeTransfer`  
_L35-67_
- desc: FMeshAttributeTransfer transfers attributes from a SourceMesh to a TargetMesh
- L39 _public member_ `const FDynamicMesh3* SourceMesh;` — The mesh that we are transferring from
- L42 _public member_ `FDynamicMesh3* TargetMesh;` — The mesh that we are transferring to
- L45 _public member_ `EMeshAttributeTransferType TransferType = EMeshAttributeTransferType::MaterialID;` — What is being transferred
- L48 _public member_ `TArray<EMeshAttributeTransferError> Errors;`
- L51 _public prototype_ `FMeshAttributeTransfer(const FDynamicMesh3* SourceMeshIn, FDynamicMesh3* TargetMeshIn);`
- L53 _public prototype_ `virtual ~FMeshAttributeTransfer() = default;`
- L59 _public prototype_ `virtual bool Apply();` — Run the operation and modify .Mesh @return true if the algorithm succeeds
- L63 _protected member_ `TUniquePtr<FDynamicMeshAABBTree3> SourceSpatial;`
- L66 _protected prototype_ `bool Apply_MaterialID();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MeshBevel.h` (Public)


#### class `UE::Geometry::FMeshBevel`  
`class FMeshBevel`  
_L49-371_
- desc: FMeshBevel applies a "Bevel" operation to edges of a FDynamicMesh3. Bevel is not strictly well-defined, there are a wide range of possible cases to handle and currently only some are supported. See this website for a discussion of many interesting cases (most are not currently supported): https://wiki.blender.org/wiki/User:Howardt/Bevel The bevel operation is applied in-place to the input mesh. The bevel is mesh-topological, ie implemented by un-stitching mesh edges and inserting new triangles, rather than via booleans/etc. Currently supports: - Bevel an isolated closed loop of edges, that edge-loop becomes a quad-strip (simplest case) - Bevel a set of open edge spans that may meet a T-junctions - if incoming-span-valence at a vertex is >= 3, vertex is replaced by a polygon - if incoming-span-valence at a vertex is 1, bevel is "terminated" by expanding the vertex into an edge (this is the messiest case) - vertex-on-boundary is a special case that is simpler - edge spans are replaced by quad-strips Currently does not support: - Beveling an isolated vertex - partial bevels of a GroupTopology Edge - multiple-segment bevel (eg to do rounds/etc) - ??? Generally this FMeshBevel is intended to be applied to group-boundary "edges" in a FGroupTopology. However the FGroupTopology is currently only used in the initial setup, so other methods could be used to construct the bevel topology. Currently "updating" the bevel shape, once the topology is known, is not supported, but could be imp
- L58 _public member_ `double InsetDistance = 5.0;` — Distance that bevel edges/vertices are inset from their initial position. Not guaranteed to hold for all vertices, though.
- L61 _public member_ `int32 NumSubdivisions = 0;` — Number of subdivisions inserted in each bevel strip
- L67 _public member_ `double RoundWeight = 1.0;` — "Roundness" of the bevel profile. Ignored if Subdivisions = 0. Default=1 means try to be circular-ish. Higher values pull towards a sharper crease. 0 is flat (ie no profile, a linear chamfer). If negative, bevel profile will be an inverted-arc
- L77 _public member_ `EMaterialIDMode MaterialIDMode = EMaterialIDMode::ConstantMaterialID;` — Which MaterialID assignment mode to use
- L79 _public member_ `int32 SetConstantMaterialID = 0;` — Constant MaterialID used for various MaterialIDMode settings
- L82 _public member_ `FProgressCancel* Progress = nullptr;` — Set this member to support progress/cancel in the computations below
- L90 _public member_ `TArray<int32> NewTriangles;` — list of all new triangles created by the operation
- L93 _public member_ `FGeometryResult ResultInfo = FGeometryResult(EGeometryResultType::InProgress);` — status of the operation, warnings/errors may be returned here
- L99 _public prototype_ `void InitializeFromGroupTopology(const FDynamicMesh3& Mesh, const FGroupTopology& Topology);` — Initialize the bevel with all edges of the given GroupTopology
- L104 _public prototype_ `void InitializeFromGroupTopologyEdges(const FDynamicMesh3& Mesh, const FGroupTopology& Topology, const TArray<int32>& GroupEdges);` — Initialize the bevel with the specified edges of a GroupTopology
- L110 _public prototype_ `void InitializeFromTriangleEdges(const FDynamicMesh3& Mesh, TConstArrayView<int32> TriangleEdges, TFunctionRef<bool(int32)> IsCornerVertex);` — Initialize the bevel with the specified mesh triangle edges @param IsCornerVertex Function to determine whether a vertex should be treated as a corner when beveling. Only affects vertices with exactly two adjacent TriangleEdges; otherwise corners will be automatically detected.
- L115 _public function_ `void InitializeFromTriangleEdges(const FDynamicMesh3& Mesh, TConstArrayView<int32> TriangleEdges)` — Initialize the bevel with the specified mesh triangle edges
- L124 _public prototype_ `bool InitializeFromGroupTopologyFaces(const FDynamicMesh3& Mesh, const FGroupTopology& Topology, const TArray<int32>& GroupFaces);` — Initialize the bevel with the specified faces of a GroupTopology @return false if any selection-bowtie vertices were found, in this case we cannot compute the bevel
- L130 _public prototype_ `bool InitializeFromTriangleSet(const FDynamicMesh3& Mesh, const TArray<int32>& Triangles);` — Initialize the bevel with border loops of the selected triangles. @return false if any selection-bowtie vertices were found, in this case we cannot compute the bevel
- L135 _public prototype_ `bool Apply(FDynamicMesh3& Mesh, FDynamicMeshChangeTracker* ChangeTracker);` — Apply the bevel operation to the mesh, and optionally track changes
- L292 _protected member_ `TMap<int32, int32> VertexIDToIndexMap;` — map of mesh-vertex-IDs to indices into Vertices list
- L293 _protected member_ `TArray<FBevelVertex> Vertices;` — list of FBevelVertex data structures for mesh vertices that need beveling
- L295 _protected member_ `TArray<FBevelEdge> Edges;` — list of FBevelEdge data structures for mesh edge-spans that need beveling
- L296 _protected member_ `TArray<FBevelLoop> Loops;` — list of FBevelLoop data structures for mesh edge-loops that need beveling
- L298 _protected member_ `TMap<int32, int32> MeshEdgePairs;` — Many edges of the input mesh will be split into edge pairs, which are then stitched together with quads.
- L305 _protected prototype_ `FBevelVertex* GetBevelVertexFromVertexID(int32 VertexID, int32* IndexOut = nullptr);`
- L311 _protected prototype_ `void AddBevelGroupEdge(const FDynamicMesh3& Mesh, const FGroupTopology& Topology, int32 GroupEdgeID);`
- L312 _protected prototype_ `void AddBevelEdgeLoop(const FDynamicMesh3& Mesh, const FEdgeLoop& Loop);`
- L313 _protected prototype_ `void BuildVertexSets(const FDynamicMesh3& Mesh);`
- L314 _protected prototype_ `void BuildJunctionVertex(FBevelVertex& Vertex, const FDynamicMesh3& Mesh);`
- L315 _protected prototype_ `void BuildTerminatorVertex(FBevelVertex& Vertex, const FDynamicMesh3& Mesh);`
- L320 _protected prototype_ `void UnlinkEdges( FDynamicMesh3& Mesh, FDynamicMeshChangeTracker* ChangeTracker);`
- L321 _protected prototype_ `void UnlinkBevelEdgeInterior( FDynamicMesh3& Mesh, FBevelEdge& BevelEdge, FDynamicMeshChangeTracker* ChangeTracker);`
- L323 _protected prototype_ `void UnlinkLoops( FDynamicMesh3& Mesh, FDynamicMeshChangeTracker* ChangeTracker);`
- L324 _protected prototype_ `void UnlinkBevelLoop( FDynamicMesh3& Mesh, FBevelLoop& BevelLoop, FDynamicMeshChangeTracker* ChangeTracker);`
- L326 _protected prototype_ `void UnlinkVertices( FDynamicMesh3& Mesh, FDynamicMeshChangeTracker* ChangeTracker);`
- L327 _protected prototype_ `void UnlinkJunctionVertex(FDynamicMesh3& Mesh, FBevelVertex& BevelVertex, FDynamicMeshChangeTracker* ChangeTracker);`
- L328 _protected prototype_ `void UnlinkTerminatorVertex(FDynamicMesh3& Mesh, FBevelVertex& BevelVertex, FDynamicMeshChangeTracker* ChangeTracker);`
- L330 _protected prototype_ `void FixUpUnlinkedBevelEdges(FDynamicMesh3& Mesh);`
- L334 _protected prototype_ `void DisplaceVertices(FDynamicMesh3& Mesh, double Distance);`
- L340 _protected prototype_ `void CreateBevelMeshing(FDynamicMesh3& Mesh);` — Meshing functions for chamfer bevel, ie no subdivisions
- L341 _protected prototype_ `void AppendJunctionVertexPolygon(FDynamicMesh3& Mesh, FBevelVertex& Vertex);`
- L342 _protected prototype_ `void AppendTerminatorVertexTriangle(FDynamicMesh3& Mesh, FBevelVertex& Vertex);`
- L343 _protected prototype_ `void AppendTerminatorVertexPairQuad(FDynamicMesh3& Mesh, FBevelVertex& Vertex0, FBevelVertex& Vertex1);`
- L344 _protected prototype_ `void AppendEdgeQuads(FDynamicMesh3& Mesh, FBevelEdge& Edge);`
- L345 _protected prototype_ `void AppendLoopQuads(FDynamicMesh3& Mesh, FBevelLoop& Loop);`
- L348 _protected prototype_ `void CreateBevelMeshing_Multi(FDynamicMesh3& Mesh);` — Meshing functions for multi-segment bevel with optional round profile
- L349 _protected prototype_ `void AppendEdgeQuads_Multi(FDynamicMesh3& Mesh, FBevelEdge& Edge);`
- L350 _protected prototype_ `void AppendLoopQuads_Multi(FDynamicMesh3& Mesh, FBevelLoop& Loop);`
- L351 _protected prototype_ `void AppendJunctionVertexPolygon_Multi(FDynamicMesh3& Mesh, FBevelVertex& Vertex);`
- L352 _protected prototype_ `void AppendTerminatorVertexTriangles_Multi(FDynamicMesh3& Mesh, FBevelVertex& Vertex);`
- L353 _protected prototype_ `void AppendTerminatorVertexPairQuad_Multi(FDynamicMesh3& Mesh, FBevelVertex& Vertex0, FBevelVertex& Vertex1);`
- L354 _protected prototype_ `void ApplyProfileShape_Round(FDynamicMesh3& Mesh);`
- L355 _protected prototype_ `FInterpCurveVector MakeArcSplineCurve(const FVector3d& PosA, FVector3d& NormalA, const FVector3d& PosB, FVector3d& NormalB) const;`
- L360 _protected prototype_ `void ComputeNormals(FDynamicMesh3& Mesh);`
- L361 _protected prototype_ `void ComputeUVs(FDynamicMesh3& Mesh);`
- L362 _protected prototype_ `void ComputeMaterialIDs(FDynamicMesh3& Mesh);`
- L367 _private prototype_ `void FixBowties(FDynamicMesh3& Mesh, FDynamicMeshChangeTracker* ChangeTracker);` — Detect and fix any bowtie vertices in the bevel operation set Called by "Apply" (because the setup methods all operate on a const Mesh) before the actual bevel operation
- L369 _private prototype_ `void InitVertexSet(const FDynamicMesh3& Mesh, FBevelVertex& Vertex);`
- L370 _private prototype_ `void FinalizeTerminatorVertex(const FDynamicMesh3& Mesh, FBevelVertex& Vertex);`

#### enum `UE::Geometry::FMeshBevel::EMaterialIDMode`  
`enum class EMaterialIDMode`  
_L70-75_
- desc: Options for MaterialID assignment on the new triangles generated for the bevel
- L72 _public enumerator_ `ConstantMaterialID`
- L73 _public enumerator_ `InferMaterialID`
- L74 _public enumerator_ `InferMaterialID_ConstantIfAmbiguous`

#### struct `UE::Geometry::FMeshBevel::FBevelLoop`  
`struct FBevelLoop`  
_L158-179_
- desc: FBevelLoop is the accumulated data for a closed loop of mesh-edges, with no T-junctions w/ other bevel-edges. This is the easiest case as each mesh-edge of the loop expands out into a quad, with no complex vertex-polygons/etc
- L161 _public member_ `TArray<int32> MeshVertices;` — initial topological information that defines what happens in unlink/displace/mesh steps
- L162 _public member_ `TArray<int32> MeshEdges;` — sequential list of mesh edge IDs along edge loop
- L163 _public member_ `TArray<FIndex2i> MeshEdgeTris;` — the one or two triangles associated w/ each MeshEdges element in the input mesh
- L164 _public member_ `TArray<FVector3d> InitialPositions;` — initial vertex positions
- L167 _public member_ `TArray<int32> NewMeshVertices;` — new mesh topology computed during unlink step
- L168 _public member_ `TArray<int32> NewMeshEdges;` — list of new edges on "other" side of unlinked edge, 1-1 with MeshEdges
- L171 _public member_ `TArray<FVector3d> NewPositions0;` — buffers for new vertex positions computed during displace step
- L172 _public member_ `TArray<FVector3d> NewPositions1;` — new positions for NewMeshVertices list
- L175 _public member_ `TArray<int32> NewGroupIDs;` — new geometry computed during mesh step
- L176 _public member_ `TArray<FIndex2i> StripQuads;` — triangle-ID-pairs for each new quad added along edge, 1-1 with MeshEdges
- L177 _public member_ `FQuadGridPatch StripQuadPatch;` — only initialized in multi-segment bevel
- L178 _public member_ `TArray<FVector3d> NormalsA, NormalsB;` — normals at NewPositions0 and NewPositions1, before internal meshing is added (ie the tangent-boundary condition)
- L178 _public member_ `TArray<FVector3d> NormalsA, NormalsB;` — normals at NewPositions0 and NewPositions1, before internal meshing is added (ie the tangent-boundary condition)

#### struct `UE::Geometry::FMeshBevel::FBevelEdge`  
`struct FBevelEdge`  
_L183-217_
- desc: FBevelEdge is the accumulated data for an open span of mesh-edges, which possibly meets up with other bevel-edges at the vertices on either end of the span. Each mesh-edge of the bevel-edge will become a quad
- L186 _public prototype_ `FBevelEdge() = default;`
- L187 _public prototype_ `FBevelEdge(const FBevelEdge&) = default;`
- L188 _public prototype_ `FBevelEdge(FBevelEdge&&) = default;`
- L192 _public member_ `int32 EdgeIndex;` — initial topological information that defines what happens in unlink/displace/mesh steps
- L193 _public member_ `TArray<int32> MeshVertices;` — sequential list of mesh vertex IDs along edge
- L194 _public member_ `TArray<int32> MeshEdges;` — sequential list of mesh edge IDs along edge
- L195 _public member_ `TArray<FIndex2i> MeshEdgeTris;` — the one or two triangles associated w/ each MeshEdges element in the input mesh
- L197 _public member_ `int32 GroupEdgeID;` — `UE_DEPRECATED(5.5, "Mapping back to source topology is not used.")` — ID of this edge in external topology (eg FGroupTopology)
- L199 _public member_ `FIndex2i GroupIDs;` — `UE_DEPRECATED(5.5, "Mapping back to source topology is not used.")` — topological IDs of groups on either side of topological edge
- L200 _public member_ `bool bEndpointBoundaryFlag[2];` — flag defining whether vertex at start/end of MeshVertices was a boundary vertex
- L201 _public member_ `TArray<FVector3d> InitialPositions;` — initial vertex positions
- L202 _public member_ `FIndex2i BevelVertices;` — indices of Bevel Vertices at either end of Bevel Edge
- L205 _public member_ `TArray<int32> NewMeshVertices;` — new mesh topology computed during unlink step
- L206 _public member_ `TArray<int32> NewMeshEdges;` — list of new edges on "other" side of unlinked edge, 1-1 with MeshEdges
- L209 _public member_ `TArray<FVector3d> NewPositions0;` — buffers for new vertex positions computed during displace step
- L210 _public member_ `TArray<FVector3d> NewPositions1;` — new positions for NewMeshVertices list
- L213 _public member_ `int32 NewGroupID;` — new geometry computed during mesh step
- L214 _public member_ `TArray<FIndex2i> StripQuads;` — triangle-ID-pairs for each new quad added along edge, 1-1 with MeshEdges
- L215 _public member_ `FQuadGridPatch StripQuadPatch;` — only initialized in multi-segment bevel
- L216 _public member_ `TArray<FVector3d> NormalsA, NormalsB;` — normals at NewPositions0 and NewPositions1, before internal meshing is added (ie the tangent-boundary condition)
- L216 _public member_ `TArray<FVector3d> NormalsA, NormalsB;` — normals at NewPositions0 and NewPositions1, before internal meshing is added (ie the tangent-boundary condition)

#### struct `UE::Geometry::FMeshBevel::FOneRingWedge`  
`struct FOneRingWedge`  
_L222-232_
- desc: A FOneRingWedge represents a sequential set of connected triangles around a vertex, ie a subset of an ordered triangle one-ring. Used to represent the desired bevel topology in FBevelVertex
- L224 _public member_ `TArray<int32> Triangles;` — list of sequential triangles in this wedge
- L225 _public member_ `FIndex2i BorderEdges;` — "first" and "last" Edges of sequential triangles in Triangles list (connected to central Vertex)
- L226 _public member_ `FIndex2i BorderEdgeTriEdgeIndices;` — index 0/1/2 of BorderEdges[j] in start/ed Triangles
- L228 _public member_ `int32 WedgeVertex;` — central vertex of this wedge (updated by unlink functions)
- L230 _public member_ `FVector3d NewPosition;` — new calculated position for vertex of this wedge
- L231 _public member_ `bool bHaveNewPosition = false;` — flag indicating if NewPosition is valid

#### enum `UE::Geometry::FMeshBevel::EBevelVertexType`  
`enum class EBevelVertexType`  
_L235-247_
- desc: a FBevelVertex can have various types, depending on the topology of the bevel edge graph and input mesh
- L239 _public enumerator_ `JunctionVertex` — A JunctionVertex is a vertex at which 2 or more FBevelEdges meet (ie is an endpoint of 2 or more of those vertex-spans) If N>=3 or more edges meet at a JunctionVertex, it will become a polygon with N vertices, one for each "wedge"
- L242 _public enumerator_ `TerminatorVertex` — A TerminatorVertex is a vertex at which a single FBevelEdge terminates, ie the N=1 case. This requires different handling because we essentially want to turn that vertex into an edge, which means inserting a triangle into the adjacent one-ring
- L244 _public enumerator_ `BoundaryVertex` — a BoundaryVertex is a junction/terminator on the mesh boundary
- L246 _public enumerator_ `Unknown` — An Unknown vertex is one at which we don't know what to do, or some error occurred while processing as a Junction/Terminator.

#### struct `UE::Geometry::FMeshBevel::FBevelVertex_InteriorVertex`  
`struct FBevelVertex_InteriorVertex`  
_L249-253_
- L251 _public member_ `int32 VertexID = -1;`
- L252 _public member_ `TArray<FVector3d> BorderFrameWeight;`

#### struct `UE::Geometry::FMeshBevel::FBevelVertex`  
`struct FBevelVertex`  
_L257-287_
- desc: A FBevelVertex repesents/stores the accumulated data at a "bevel vertex", which is the mesh vertex at the end of a FBevelEdge. A FBevelVertex may be expanded out into a polygon or just an edge, depending on its Type
- L260 _public prototype_ `FBevelVertex() = default;`
- L261 _public prototype_ `FBevelVertex(const FBevelVertex&) = default;`
- L262 _public prototype_ `FBevelVertex(FBevelVertex&&) = default;`
- L265 _public member_ `int32 VertexID;` — Initial Mesh Vertex ID for the Bevel Vertex
- L267 _public member_ `int32 CornerID;` — `UE_DEPRECATED(5.5, "Mapping back to source topology is not used.")` — Initial Group Topology Corner ID for the Bevel Vertex (if exists)
- L268 _public member_ `EBevelVertexType VertexType = EBevelVertexType::Unknown;` — Type of the Bevel Vertex
- L270 _public member_ `TArray<int32> IncomingBevelMeshEdges;` — Set of (unsorted) Mesh Edges that are destined to be Beveled, coming into the vertex
- L272 _public member_ `TArray<int32> IncomingBevelTopoEdges;` — `UE_DEPRECATED(5.5, "Mapping back to source topology is not used.")` — Set of (unsorted) Group Topology Edges that are to be Beveled, coming into the vertex
- L273 _public member_ `TArray<int32> IncomingBevelEdgeIndices;` — Set of (unsorted) indices of FBevelEdge, coming into the vertex
- L275 _public member_ `TArray<int32> SortedTriangles;` — ordered triangle one-ring around VertexID
- L276 _public member_ `TArray<FOneRingWedge> Wedges;` — ordered decomposition of one-ring into "wedges" between incoming bevel edges (no correspondence w/ IncomingBevelMeshEdges list)
- L278 _public member_ `int32 NewGroupID;` — new polygroup allocated for the beveled polygon generated by this vertex (if NumEdges > 2)
- L279 _public member_ `TArray<int32> NewTriangles;` — new triangles that make up the beveled polygon for this vertex (if NumEdges > 2)
- L281 _public member_ `FIndex2i TerminatorInfo;` — for TerminatorVertex type, store [EdgeID, FarVertexID] in one-ring, used to unlink/fill (see usage)
- L282 _public member_ `int32 ConnectedBevelVertex = -1;` — If set to another FBevelVertex index, then the TerminatorInfo.EdgeID directly connects to that vertex and special handling is needed
- L285 _public member_ `TArray<FBevelVertex_InteriorVertex> InteriorVertices;` — these arrays are used for multi-segment bevels, and are initialized in different ways depending on the vertex valence - see cpp comments
- L286 _public member_ `TArray<int32> InteriorBorderLoop;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)
- L117 _function_ `InitializeFromTriangleEdges(Mesh, TriangleEdges, [](int32) {return false;});` (scope `UE::Geometry::FMeshBevel::InitializeFromTriangleEdges`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MeshClusterSimplifier.h` (Public)


#### struct `UE::Geometry::MeshClusterSimplify::FSimplifyOptions`  
`struct FSimplifyOptions`  
_L20-89_
- L23 _public member_ `double TargetEdgeLength = 1;` — Vertices within this distance are allowed to be replaced with a single vertex
- L27 _public member_ `TFunction<double(int32)> OptionalTargetEdgeLengthScale = nullptr;` — Optionally locally scales the simplifier's TargetEdgeLength on a per-vertex basis If provided, the target edge length at a vertex VID will be TargetEdgeLength * OptionalTargetEdgeLengthScale(VID)
- L35 _public member_ `int32 MaxPreserveCollapsedClusterPasses = 3;` — If > 0, number of passes to attempt to make sure the simplification does not fully delete islands of the mesh. In areas that would be deleted (because the region is smaller than the TargetEdgeLength), the target edge length will instead be locally reduced to half the local max in-cluster distance, and clustering will be re-run. This does not guarantee all clusters will be preserved: Use a higher number of passes to reducing the likelihood of losing mesh components/connectivity, for additional cost & more vertices in the result.
- L38 _public member_ `double FixBoundaryAngleTolerance = 45;` — If > 0, boundary vertices w/ incident boundary edge angle greater than this (in degrees) will be kept in the output
- L80 _public member_ `FPreserveFeatures PreserveEdges{};` — Manage which feature edge types we try to retain in the simplified result
- L83 _public member_ `bool bTransferAttributes = true;` — Whether to attempt to transfer attributes to the result mesh
- L86 _public member_ `bool bTransferGroups = true;` — Whether to attempt to transfer triangle groups (PolyGroups) to the result mesh

#### enum `UE::Geometry::MeshClusterSimplify::FSimplifyOptions::EConstraintLevel`  
`enum class EConstraintLevel : uint8`  
_L42-53_
- desc: Constraint levels control what simplifications are allowed Ordered from most-constrained to least-constrained
- L45 _public enumerator_ `Fixed` — Fixed vertices/edges will generally be preserved in the output, as they will each be given their own cluster
- L48 _public enumerator_ `Constrained` — Constrained vertices/edges may be simplified, but the edge flow should be preserved A vertex at an intersection of more than two constrained edges will be automatically preserved as 'Fixed'
- L50 _public enumerator_ `Free` — No constraints / ok to simplify as much as possible
- L52 _public enumerator_ `MAX` — The count of total constraint levels, used for iterating over the levels. (Not itself a valid constraint level)

#### struct `UE::Geometry::MeshClusterSimplify::FSimplifyOptions::FPreserveFeatures`  
`struct FPreserveFeatures`  
_L55-77_
- L58 _public member_ `EConstraintLevel Boundary = EConstraintLevel::Constrained;` — Mesh boundaries
- L60 _public member_ `EConstraintLevel UVSeam = EConstraintLevel::Constrained;` — Seam types
- L61 _public member_ `EConstraintLevel NormalSeam = EConstraintLevel::Constrained;`
- L62 _public member_ `EConstraintLevel TangentSeam = EConstraintLevel::Free;`
- L63 _public member_ `EConstraintLevel ColorSeam = EConstraintLevel::Constrained;`
- L65 _public member_ `EConstraintLevel Material = EConstraintLevel::Constrained;` — Material ID boundaries
- L67 _public member_ `EConstraintLevel PolyGroup = EConstraintLevel::Constrained;` — PolyGroup ID boundaries
- L70 _public function_ `void SetSeamConstraints(EConstraintLevel Level)` — Helper to set all seam types to the same constraint level

#### struct `UE::Geometry::MeshClusterSimplify::FResultMeshAdapter`  
`struct FResultMeshAdapter`  
_L116-165_
- desc: Adapter for producing an output simplified triangle mesh in any target triangle mesh structure
- L119 _public member_ `TFunction<int32(FVector3d)> AppendVertex;` — Add a vertex to the result mesh, and return its ID
- L124 _public member_ `TFunction<int32(FIndex3i)> AppendTriangle;` — Add a triangle to the result mesh, and return its ID Note this method should follow the same error conventions as FDynamicMesh3, so if it refuses to add a non-manifold triangle, it should return FDynamicMesh3::NonManifoldID
- L127 _public member_ `TFunction<void()> Clear;` — Clear the current mesh from the results
- L130 _public member_ `TFunction<FVector3d(int32)> GetVertex;` — Accessor for vertices
- L132 _public member_ `TFunction<FIndex3i(int32)> GetTriangle;` — Accessor for triangles
- L137 _public function_ `template<typename MeshType> void Init(MeshType* Mesh)` — Initialize the adapter from a mesh type that has the same basic interface Note that for attributes to transfer, the optional attribute transfer methods must be implemented separately
- L162 _public member_ `TFunction<void(TConstArrayView<int32> ResultToSourceVertexID)> TransferPerVertexAttributes;` — Attribute transfer methods; if not provided, attributes will not be transferred
- L163 _public member_ `TFunction<void(TConstArrayView<int32> ResultToSourceTriangleID)> TransferPerTriangleAttributes;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)
- L17 _namespace_ `namespace MeshClusterSimplify` (scope `UE::Geometry`)
- L111 _prototype_ `bool Simplify(const FDynamicMesh3& InMesh, FDynamicMesh3& OutSimplifiedMesh, const FSimplifyOptions& SimplifyOptions);` (scope `UE::Geometry::MeshClusterSimplify`) — Makes a simplified copy of the input mesh This cluster simplify method first clusters vertices locally by distance (calculated along mesh edges), and creates new triangles from the connectivity of the clusters. i.e., it is a triangulation of the dual of the graph voronoi diagram over mesh edges. To preserve feature edges: (1) constrained / feature-edge vertices are prioritized as cluster 'seeds,' and (2) clusters are grown along feature edges first, then free edges after -- and growth over 'free' edges cannot claim 'constrained' vertices. This locks in clusters along 'constrained' feature edges. Note that mesh features can be lost if the clusters are large enough that the graph becomes degenerate -- e.g., if a mesh island has so few clusters that the graph connectivity does not contain triangles. @param InMesh The mesh to simplify @param OutSimplifiedMesh This mesh will store the simplified result mesh @param SimplifyOptions Options controlling simplification @return true on success
- L140 _function_ `` (scope `UE::Geometry::MeshClusterSimplify::FResultMeshAdapter::Init`)
- L169 _prototype_ `bool Simplify(const FTriangleMeshAdapterd& InMesh, FResultMeshAdapter& OutSimplifiedMesh, const FSimplifyOptions& SimplifyOptions);` (scope `UE::Geometry::MeshClusterSimplify`) — Simplify an input mesh provided by the general triangle mesh adapter, placing the result in an output mesh via a similar adapter interface Note: The output mesh must not be aliased with input mesh data

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MeshConvexHull.h` (Public)


#### class `UE::Geometry::FMeshConvexHull`  
`class FMeshConvexHull`  
_L23-108_
- desc: Calculate Convex Hull of a Mesh
- L27 _public member_ `const FDynamicMesh3* Mesh;` — Input Mesh
- L30 _public member_ `TArray<int32> VertexSet;` — If set, hull will be computed on subset of vertices
- L33 _public member_ `bool bPostSimplify = false;` — If true, output convex hull is simplified down based on the SimplifyOptions
- L44 _public member_ `FSimplifyOptions SimplifyOptions;` — IF bPostSimplify, options controlling the simplification
- L47 _public member_ `int32 MaxTargetFaceCount = 0;` — `UE_DEPRECATED(5.8, "Use SimplifyOptions.MaxTargetFaceCount instead")`
- L50 _public member_ `double MinDimension = 0;` — Minimum extent along the shortest dimension; if greater than zero, the hull may be expanded if it would be too thin
- L53 _public member_ `FDynamicMesh3 ConvexHull;` — Output convex hull
- L64 _public prototype_ `static void GridSample(const FDynamicMesh3& Mesh, int GridResolutionMaxAxis, TArray<int32>& OutSamples);` — Choose a more or less evenly-spaced subset of mesh vertices. Conceptually, this function creates a uniform grid with given cell size. (Cell size is given roughly as a percentage of the total mesh bounding box.) Each grid cell can hold up to one vertex. Return the set of representative vertices, maximum one per cell. @param Mesh							Surface mesh whose vertices we want to sample @param CellSizeAsPercentOfBounds	Grid cell size expressed as a percentage of the mesh bounding box size @param OutSamples					Indices of chosen vertices
- L69 _public prototype_ `static FVector3i DebugGetCellIndex(const FDynamicMesh3& Mesh, int GridResolutionMaxAxis, int VertexIndex);` — Used for testing/debugging
- L75 _public function_ `FMeshConvexHull(const FDynamicMesh3* MeshIn)`
- L84 _public prototype_ `bool Compute(FProgressCancel* Progress = nullptr);` — Calculate output ConvexHull mesh for vertices of input Mesh @return true on success
- L90 _public function_ `static bool SimplifyHull(FDynamicMesh3& HullMesh, int32 MaxTargetFaceCount, FProgressCancel* Progress = nullptr)` — Simplify the output convex hull. Assumes ConvexHull is already computed. @return true on success
- L101 _public prototype_ `static bool SimplifyHull(FDynamicMesh3& HullMesh, FSimplifyOptions SimplifyOptions, FProgressCancel* Progress = nullptr);` — Simplify the output convex hull. Assumes ConvexHull is already computed. @return true on success
- L104 _protected prototype_ `bool Compute_FullMesh(FProgressCancel* Progress);`
- L105 _protected prototype_ `bool Compute_VertexSubset(FProgressCancel* Progress);`
- L107 _private prototype_ `bool Compute_Helper(FProgressCancel* Progress, int32 MaxVertexIndex, TFunctionRef<FVector3d(int32)> GetVertex, TFunctionRef<bool(int32)> IsVertex, bool bTestMinDimension = true);`

#### struct `UE::Geometry::FMeshConvexHull::FSimplifyOptions`  
`struct FSimplifyOptions`  
_L35-41_
- L38 _public member_ `int32 MaxTargetFaceCount = 0;` — Target triangle count of the simplified output Convex Hull; hull will be simplified to at most this triangle count if possible
- L40 _public member_ `double GeometricToleranceAfterTarget = 0.;` — If greater than zero, hull will be futher simplified below target face count where doing so remains within this error tolerance

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MeshGeodesicSurfaceTracer.h` (Public)


#### enum `UE::Geometry::GeodesicSingleTriangleUtils::ETraceClassification`  
`enum class ETraceClassification`  
_L43-50_
- desc: Classification for a trace result (i.e. for a points recorded along the path).
- L45 _public enumerator_ `Start` — corresponds to initial location when starting a trace
- L46 _public enumerator_ `Continuing` — non-terminated result computed when crossing a single triangle
- L47 _public enumerator_ `DistanceTerminated` — result terminated by reaching prescribed max distance
- L48 _public enumerator_ `BoundaryTerminated` — result terminated by reaching mesh boundary
- L49 _public enumerator_ `Failed` — failed trace, generally a sign that you started a trace with a ray origin outside the triangle.

#### class `UE::Geometry::GeodesicSingleTriangleUtils::FTangentTri2`  
`class GeodesicSingleTriangleUtils::FTangentTri2`  
_L148-191_
- L151 _public prototype_ `FTangentTri2() = default;`
- L154 _public prototype_ `FTangentTri2(const FDynamicMesh3& Mesh, int32 TriID, int32 PrimaryEdgeID);` — The PrimaryEdge will be aligned with the x-axis in 2d ( and must be one of the edges of the triangle indicated by TriID)
- L157 _public prototype_ `void Reset();` — Reset just invalidates Tri3ID
- L160 _public prototype_ `double DistanceToEdge(int EdgeIndex, const FVector2d& Point) const;` — EdgeIndex = 0, 1, 2
- L163 _public prototype_ `double ProjectOnEdge(int EdgeIndex, const FVector2d& Point) const;` — Closest Point on the edge, given in terms of 0,1 parameter measured along the edge (EdgeIndex = 0, 1, 2)
- L166 _public prototype_ `FVector2d ChangeBasis(const FVector2d& Vec, int32 EdgeIndex) const;` — Express the vector in terms of a basis that is aligned with the EdgeIndex edge of the triangle
- L170 _public prototype_ `template <typename Vector3Type> Vector3Type ReorderVertexDataForSrcTri3d(const Vector3Type& DataOrderedForTri2d) const;` — Convert vertex data ordered for this FTangentTri2 into vertex data ordered for the source 3d triangle
- L173 _public prototype_ `FVector3d GetBarycentricCoords(const FVector2d& PoinInTri2) const;` — Barycentric coords for this point in the tri2d
- L176 _public prototype_ `FVector3d GetBarycentricCoordsInSrcTri(const FVector2d& PoinInTri2) const;` — Convert a point on this tri, to Barycentric coords in the un-rotated source triangle.
- L180 _public member_ `int32 Tri3ID = IndexConstants::InvalidID;` — TriID in the DynamicMesh3 that defined the triangle in R3
- L182 _public member_ `FIndex3i PermutedTriVIDs;` — Map verts to original triangle
- L183 _public member_ `FIndex3i PermutedTriEIDs;` — Map edges to original triangle
- L184 _public member_ `FIndex3i PermutedIndices;` — Maps R2 triangle index order to original R3 triangle index order
- L186 _public member_ `FIndex3i EdgeOrientationSign;` — Per-edge information: +1 if Mesh.GetEdgeV() orientation agrees with ccw traversal of this triangle. -1 if reversed
- L187 _public member_ `FTriangle2d Tri2d;` — The triangle in R2
- L189 _public member_ `FVector2d Tri2dEdges[3];` — cached R2 triangle edge vectors
- L190 _public member_ `FVector3d Tri2dLengths;` — cached R2 triangle edge lengths
- L348 _function_ `template <typename Vector3Type> Vector3Type GeodesicSingleTriangleUtils::FTangentTri2::ReorderVertexDataForSrcTri3d(const Vector3Type& DataOrderdForTri2d) const`

#### class `UE::Geometry::FMeshGeodesicSurfaceTracer`  
`class FMeshGeodesicSurfaceTracer`  
_L202-294_
- desc: Class that, given a starting location and direction, traces a geodesic path along a mesh. As the path enters a triangle, it is unfolded a two-dimensional triangle and the path is transformed into the local frame of the triangle. At each point where the path crosses into a new triangle, this class records the point and direction in terms of barycentric coordinates, triangle references and local path direction relative to a local frame (in the form of one of the edges of the triangle).
- L206 _public typedef_ `using FMeshSurfaceDirection = GeodesicSingleTriangleUtils::FMeshSurfaceDirection;`
- L207 _public typedef_ `using FMeshTangentDirection = GeodesicSingleTriangleUtils::FMeshTangentDirection;`
- L208 _public typedef_ `using ETraceClassification = GeodesicSingleTriangleUtils::ETraceClassification;`
- L209 _public typedef_ `using FTraceResult = GeodesicSingleTriangleUtils::FTraceResult;`
- L210 _public typedef_ `using FTangentTri2 = GeodesicSingleTriangleUtils::FTangentTri2;`
- L213 _public prototype_ `FMeshGeodesicSurfaceTracer() = default;` — will need to associate a mesh to actually use..
- L215 _public function_ `FMeshGeodesicSurfaceTracer(const FDynamicMesh3& MeshIn) : Mesh(&MeshIn)`
- L219 _public function_ `void Reset(const FDynamicMesh3& MeshIn)`
- L239 _public prototype_ `double TraceMeshFromBaryPoint(const int32 TriID, const FVector3d& BaryPoint, const FVector3d& RayDir3, double MaxDistance = TMathUtilConstants<double>::MaxReal);` — Populate internal SurfaceTrace array of FTraceResults while following a "straight" path on the surface of a mesh. The starting location and direction are given in terms of a local parameterization of the initial triangle. @param TriID     - FDynamicMesh3 TriangleID that indicated that triangle where the trace originates @param BaryPoint - Barycentric coordinates of ray origin relative to the specified triangle. See NB below. @param RayDir3   - Initial Direction given in R3.  This will be projected on the face of the specified Triangle (TriID) @param MaxDist   - Max distance the path is allowed to travel for this triangle trace. @return total distance of the trace, this may be less than the MaxDist (e.g. in the event the trace encounters a mesh edge) NB: the BaryPoint must be a valid point within or on the boundary of the triangle.
- L255 _public prototype_ `double TraceMeshFromBaryPoint(const int32 TriID, const FVector3d& BaryPoint, const FMeshSurfaceDirection& Direction, double MaxDistance = TMathUtilConstants<double>::MaxReal);` — Populate internal SurfaceTrace array of FTraceResults while following a "straight" path on the surface of a mesh. The starting location and direction are given in terms of a local parameterization of the initial triangle. @param TriID     - FDynamicMesh3 TriangleID that indicated that triangle where the trace originates @param BaryPoint - Barycentric coordinates of ray origin relative to the specified triangle. See NB below. @param Direction - Surface direction of trace @param MaxDist   - Max distance the path is allowed to travel for this triangle trace. @return total distance of the trace, this may be less than the MaxDist (e.g. in the event the trace encounters a mesh edge) NB: the BaryPoint must be a valid point within or on the boundary of the triangle. NB: it is assumed the edge Direction.EdgeID is part of the triangle TriID.  ( otherwise the result will be unexpected)
- L268 _public prototype_ `double TraceMeshFromVertex( const FMeshTangentDirection& Direction, double MaxDistance);` — Populate internal SurfaceTrace array of FTraceResults while following a "straight" path on the surface of a mesh. The starting location and direction are given in terms of a local parameterization of the initial triangle. @param Direction - Tangent plane direction of trace, defines the origin (VID) and the zero radian direction (EID.A to EID.B) along with a polar angle @param MaxDist   - Max distance the path is allowed to travel for this triangle trace. @return total distance of the trace, this may be less than the MaxDist (e.g. in the event the trace encounters a mesh edge) NB: it is assumed the edge Direction.EdgeID is adjacent to VID.  ( otherwise the result will be unexpected)
- L271 _public function_ `const FTangentTri2& GetLastTri()` — Access to the last tri traced in 2d form.
- L277 _public function_ `TArray<FTraceResult>& GetTraceResults()` — Access to the trace results
- L282 _public function_ `const TArray<FTraceResult>& GetTraceResults() const` — Access to the trace results
- L290 _protected member_ `const FDynamicMesh3* Mesh = nullptr;` — Pointer to the Mesh to be traced.
- L291 _protected member_ `TArray<FTraceResult> SurfaceTrace;` — Vector of points along the computed trace
- L292 _protected member_ `FTangentTri2 ScratchTri2;` — 2d representation of the last triangle traversed.  Used as scratch during computations

#### struct `UE::Geometry::GeodesicSingleTriangleUtils::FMeshSurfaceDirection`  
`struct GeodesicSingleTriangleUtils::FMeshSurfaceDirection`  
_L298-315_
- L300 _public function_ `FMeshSurfaceDirection() :EdgeID(IndexConstants::InvalidID), Dir(0., 0.)`
- L302 _public function_ `FMeshSurfaceDirection(int EID, const FVector2d& DirIn) : EdgeID(EID) , Dir(DirIn)`
- L307 _public function_ `FMeshSurfaceDirection(int EID, const double PolarAngle) : EdgeID(EID) , Dir(FVector2d(FMath::Cos(PolarAngle), FMath::Sin(PolarAngle)))`
- L313 _public member_ `int32 EdgeID;` — Mesh Edge, has implicit order (from Edge.A to Edge.B)
- L314 _public member_ `FVector2d Dir;` — Normalized direction relative to the frame defined by the mesh edge EdgeID aligned with the x-axis

#### struct `UE::Geometry::GeodesicSingleTriangleUtils::FMeshTangentDirection`  
`struct GeodesicSingleTriangleUtils::FMeshTangentDirection`  
_L317-322_
- L319 _public member_ `int32 VID;` — Tangent space centered on VID vertex
- L320 _public member_ `int32 EdgeID;` — Mesh Edge (adjacent to VID), the vector Edge.A to Edge.B defines the zero radians direction (Edge.B to Edge.A is pi radians)
- L321 _public member_ `double PolarAngle;` — Angle measured between [0, 2pi)

#### struct `UE::Geometry::GeodesicSingleTriangleUtils::FTraceResult`  
`struct GeodesicSingleTriangleUtils::FTraceResult`  
_L324-337_
- L326 _public member_ `ETraceClassification Classification = ETraceClassification::Start;`
- L328 _public member_ `double TraceDist = -1.;` — Distance traveled in this tri before either meeting and edge or the max distance.
- L329 _public member_ `int32 TriID = IndexConstants::InvalidID;` — Triangle traversed
- L330 _public member_ `FMeshSurfaceDirection SurfaceDirection;` — Tangent vector.
- L333 _public member_ `FVector3d Barycentric;` — -- Information about the surface point --//
- L334 _public member_ `bool bIsEdgePoint;` — Duplicate description of the surface point in the case of edge termination
- L335 _public member_ `int32 EdgeID = IndexConstants::InvalidID;` — In the case of Edge termination, SurfaceDirection.EdgeID = EdgeID
- L336 _public member_ `double EdgeAlpha = -1.;` — When edge point: locates position between the vertices as (1-Alpha) Edge.A + Alpha Edge.B

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DYNAMICMESH_API`
- L16 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)
- L27 _namespace_ `namespace GeodesicSingleTriangleUtils` (scope `UE::Geometry`)
- L65 _prototype_ `static bool IsTerminated(const FTraceResult& Result);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`)
- L81 _prototype_ `FTraceResult TraceTangentTriangle(const FTangentTri2& TangentTri2, const FVector2d& RayOrigin, const FVector2d& RayDir, double MaxDistance);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`) — Trace FTangentTri2 using a local coordinate system defined by aligning the first edge of the triangle with the positive x-direction and the opposing vertex with positive y-coordinate. @param TangentTri2    - Triangle to trace, expressed in 2d @param RayOrigin - ray origin @param Direction - direction of trace, normalized @param MaxDist   - Max distance the path is allowed to travel for this triangle trace. @return Trace Result.
- L96 _prototype_ `FTraceResult TraceTriangleFromBaryPoint(const FDynamicMesh3& Mesh, const int32 TriID, const FVector3d& BaryPoint, const FMeshSurfaceDirection& Direction, double MaxDistance = TMathUtilConstants<double>::MaxReal);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`) — Trace From an Edge crossing into the triangle TriID @param TriID     - FDynamicMesh3 TriangleID that indicated that triangle we trace across @param BaryPoint - Barycentric coordinates of ray origin. @param Direction - Surface direction of trace @param MaxDist   - Max distance the path is allowed to travel for this triangle trace. @return Trace Result. NB: it is assumed the edge EID is part of the triangle TriID.  ( otherwise the result will be unexpected) NB: it is assumed the BaryPoint is a valid point in the triangle ( otherwise the results will be unexpected)
- L97 _prototype_ `FTraceResult TraceTriangleFromBaryPoint(const FDynamicMesh3& Mesh, const int32 TriID, const FVector3d& BaryPoint, const FMeshSurfaceDirection& Direction, FTangentTri2& ScratchTangentTri2, double MaxDistance = TMathUtilConstants<double>::MaxReal);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`)
- L106 _prototype_ `FTraceResult TraceFromVertex(const FDynamicMesh3& Mesh, const FMeshTangentDirection& Direction, double MaxDistance = TMathUtilConstants<double>::MaxReal);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`) — Trace from  a Vertex Crossing. @param TangentDirection   - Direction in the local tangent space ( also defines the frame by center VID and zero angle EID) @param MaxDistance        - Maximal distance this trace can travel. @return Trace Result.
- L107 _prototype_ `FTraceResult TraceFromVertex(const FDynamicMesh3& Mesh, const FMeshTangentDirection& Direction, FTangentTri2& ScratchTangentTri2, double MaxDistance = TMathUtilConstants<double>::MaxReal);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`)
- L119 _prototype_ `FTraceResult TraceFromVertex(const FDynamicMesh3& Mesh, int32 VID, const FMeshSurfaceDirection& Direction, double MaxDistance = TMathUtilConstants<double>::MaxReal);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`) — Trace from  a Vertex Crossing. @param VID         - Vertex ID (per the FDynamicMesh3) where the trace starts @param Direction   - Surface direction of trace. @param MaxDistance - Maximal distance this trace can travel. @return Trace Result. NB: the direction vector is defined on the surface, not the tangent plane.   This means, it must lie in a triangle adjacent to Direction.EdgeID
- L120 _prototype_ `FTraceResult TraceFromVertex(const FDynamicMesh3& Mesh, int32 VID, const FMeshSurfaceDirection& Direction, FTangentTri2& ScratchTangentTri2, double MaxDistance = TMathUtilConstants<double>::MaxReal);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`)
- L132 _prototype_ `FTraceResult TraceTriangleFromEdge(const FDynamicMesh3& Mesh, const int32 TriID, double EdgeAlpha, const FMeshSurfaceDirection& Direction, double MaxDistance = TMathUtilConstants<double>::MaxReal);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`) — Trace From an Edge crossing into the triangle TriID @param TriID     - FDynamicMesh3 TriangleID that indicated that triangle we trace across @param EdgeAlpha - [0,1] parameter that determines the location on the Direction edge where the trace originates (measured from Edge.A to Edge.B as ordered in mesh) @param Direction - Surface direction of trace @return Trace Result. NB: it is assumed that the edge EID is part of the triangle TriID.  (otherwise the result will be unexpected)
- L133 _prototype_ `FTraceResult TraceTriangleFromEdge(const FDynamicMesh3& Mesh, const int32 TriID, double EdgeAlpha, const FMeshSurfaceDirection& Direction, FTangentTri2& ScratchTangentTri2, double MaxDistance = TMathUtilConstants<double>::MaxReal);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`)
- L143 _prototype_ `FTraceResult TraceNextTriangle(const FDynamicMesh3& Mesh, const FTraceResult& LastTrace, double MaxDistance = TMathUtilConstants<double>::MaxReal);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`) — Trace, starting with the result of an earlier trace. @param LastTrace   - Struct that hold previous trace.  Note StartTrace.TriID will be the triangle last visited. Will trace across the other edge adjacent tri @param MaxDistance - Maximal distance this trace can travel. @return Trace Result.
- L144 _prototype_ `FTraceResult TraceNextTriangle(const FDynamicMesh3& Mesh, const FTraceResult& LastTrace, FTangentTri2& ScratchTangentTri2, double MaxDistance = TMathUtilConstants<double>::MaxReal);` (scope `UE::Geometry::GeodesicSingleTriangleUtils`)
- L339 _function_ `bool GeodesicSingleTriangleUtils::IsTerminated(const FTraceResult& Result)` (scope `UE::Geometry::GeodesicSingleTriangleUtils`)
- L366 _function_ `static double AsZeroToTwoPi(double AngleR)` (scope `UE::Geometry`) — return AngleR in [0,2pi) range. The same polar point (r, AngleR) can be described by an infinite number of alternative angles, each offset by some multiple of 2pi,  i.e. (r, AngleR + n * 2Pi). This selects the unique angle that falls in the [0,2pi) range.

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MeshIsoCurves.h` (Public)


#### struct `UE::Geometry::MeshIsoCurve::FMeshUpdateAdapter`  
`struct FMeshUpdateAdapter`  
_L25-35_
- desc: Adapter methods to support updating a mesh with a cut. All triangles will either be labelled via LabelTriangle, or replaced w/ labelled triangles via ReplaceTriangle.
- L28 _public member_ `TFunction<int32(int32 VID0, int32 VID1, double T)> AddInterpolatedEdgeVertex;` — Add a vertex interpolating the two input vertices (but not yet connected to any triangles)
- L30 _public member_ `TFunction<int32(FIndex3i Tri, const FVector3d& BaryCoords)> AddInterpolatedTriangleVertex;` — Add a vertex interpolating the three input vertices (but not yet connected to any triangles)
- L32 _public member_ `TFunction<void(int32 ReplaceTriID, TConstArrayView<FIndex3i> NewTris, TConstArrayView<int32> NewTriLabels)> ReplaceTriangle;` — Replace a triangle with the given new triangles, with the specified new per-triangle labels
- L34 _public member_ `TFunction<void(int32 TID, int32 Label)> LabelTriangle;` — Set label on a triangle

#### struct `UE::Geometry::MeshIsoCurve::FMultiLabelIsoCurveAdapter`  
`struct FMultiLabelIsoCurveAdapter`  
_L39-59_
- desc: Adapter methods to help define the iso-curves where a triangle mesh changes between multiple discrete labels where the labels are expressed as a weight per vertex, and the highest weight should be chosen
- L42 _public member_ `TFunction<int32(int32 VID, float& OutLabelWeight)> LabelVertex;` — This function should return the 'class' index with the highest weight for the given vertex, and also return that weight by reference
- L44 _public member_ `TFunction<float(int32 VID, int32 Label)> GetVertexLabelWeight;` — This function should return the weight for a given vertex and class index
- L47 _public member_ `TFunction<double(FIndex2i EdgeV, FIndex2i EdgeLabels, FVector2f EdgeWeights)> FindEdgeCutParam;` — Find the cut parameter along a given edge where the label should change
- L50 _public member_ `TFunction<FVector3d(FIndex3i TriV, FIndex3i TriLabels, FVector3f TriWeights)> FindTriCutBaryCoords;` — For a triangle with different labels on each vertex, find the barycentric coordinates where those labels should meet Note: This method is allowed to return a coordinate outside of the triangle (should be handled gracefully by the cutting method)
- L53 _public prototype_ `void SetDefaultFindCutFunctions(const TFunction<float(int32 VID, int32 Label)>& InGetVertexLabelWeight);` — Set default implementations for FindEdgeCutParam and FindTriCutBaryCoords
- L58 _public member_ `TFunction<bool(int32 Vert0Label, int32 Vert1Label)> ShouldCutEdge;` — Return true if an edge with these two vertex labels should be cut. Note: Will not be called if the labels are the same. If not set, edges with different labels will always be cut.

#### struct `UE::Geometry::MeshIsoCurve::FMultiLabelCutSettings`  
`struct FMultiLabelCutSettings`  
_L61-68_
- L64 _public member_ `double SnapToExistingTolerance = UE_DOUBLE_KINDA_SMALL_NUMBER;` — Distance tolerance at which a cut vertex is too close to an existing vertex (or, for an on-face insertion, an existing edge) and should not be inserted
- L67 _public member_ `bool bNeverCut = false;` — Option to never cut triangles and only label triangles; equivalent to setting the snap tolerance high enough to always snap

#### struct `UE::Geometry::FMeshIsoCurveSettings`  
`struct FMeshIsoCurveSettings`  
_L84-97_
- desc: Dynamic Mesh IsoCurve Settings
- L87 _public member_ `bool bCollapseDegenerateEdgesOnCut = true;` — Whether to collapse any degenerate edges created by the curve insertion
- L90 _public member_ `double DegenerateEdgeTol = FMathd::ZeroTolerance;` — New edges shorter than this will be considered degenerate, and collapsed if bCollapseDegenerateEdgesOnCut is true
- L93 _public member_ `double SnapToExistingVertexTol = UE_DOUBLE_KINDA_SMALL_NUMBER;` — Distance at which to snap curve vertices to nearby existing vertices
- L96 _public member_ `float CurveIsoValueSnapTolerance = 0.f;` — Tolerance distance (in function domain) to an existing vertex to be 'on curve'

#### class `UE::Geometry::FMeshIsoCurves`  
`class FMeshIsoCurves`  
_L103-142_
- desc: Insert edges on a dynamic mesh along the isocurve where some scalar value function over the mesh surface crosses a specified value
- L109 _public member_ `FMeshIsoCurveSettings Settings;`
- L119 _public prototype_ `void Cut(FDynamicMesh3& Mesh, TFunctionRef<float(int32)> VertexFn, TFunctionRef<float(int32 VertA, int32 VertB, float ValueA, float ValueB)> EdgeCutFn, float IsoValue = 0);` — Insert new edges on the given mesh along the curve where a function over the mesh surface crosses a given isovalue @param Mesh The mesh to cut @param VertexFn Function from vertex ID to values @param EdgeCutFn Given the vertices of an edge and their values, return the parameter where the edge should be cut. Only called if IsoValue is crossed between ValueA and ValueB. @param IsoValue Value at which to insert a new curve on the mesh
- L128 _public function_ `void Cut(FDynamicMesh3& Mesh, TFunctionRef<float(int32)> VertexFn, float IsoValue = 0)` — Insert new edges on the given mesh along the curve where a function over the mesh vertices, and linearly interpolated over edges, crosses a given isovalue @param Mesh The mesh to cut @param VertexFn Function from vertex ID to values @param IsoValue Value at which to insert a new curve on the mesh
- L139 _private prototype_ `void SplitCrossingEdges(FDynamicMesh3& Mesh, const TArray<float>& VertexValues, TSet<int32>& OnCutEdges, TFunctionRef<float(int32 VIDMin, int32 VIDMax, float ValMin, float ValMax)> EdgeCutFn, float IsoValue);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L21 _namespace_ `namespace MeshIsoCurve` (scope `UE::Geometry`)
- L80 _prototype_ `void MultiLabelCut(const FTriangleMeshAdapterd& InMesh, const FMultiLabelIsoCurveAdapter& IsoCurveAdapter, const FMeshUpdateAdapter& UpdateAdapter, const FMultiLabelCutSettings& Settings);` (scope `UE::Geometry::MeshIsoCurve`) — Algorithm to cut a mesh's triangles based on per-vertex labels, and transfer those labels to the mesh triangles. Note this will not introduce new boundaries along the cuts; the resulting mesh will just have new edges along the boundaries. @param InMesh The mesh to cut. Note only original mesh vertices will be queried via this adapter -- never added vertices and triangles. @param IsoCurveAdapter An adapter defining how vertices should be labelled, which edges should be cut, and the desired cut positions @param UpdateAdapter An adapter that update the mesh (or a new target mesh) with newly cut/labelled triangles @param Settings Additional settings controlling how the cuts are made
- L131 _function_ `` (scope `UE::Geometry::FMeshIsoCurves::Cut`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MeshMirror.h` (Public)


#### enum `UE::Geometry::EMeshMirrorNormalMode`  
`enum class EMeshMirrorNormalMode`  
_L14-20_
- L17 _public enumerator_ `MirrorNormals = 0` — Normals are split and mirrored across the mirror plane.
- L19 _public enumerator_ `AverageMirrorNormals = 1` — Normals are averaged with their mirrored normal across the mirror plane.

#### class `UE::Geometry::FMeshMirror`  
`class FMeshMirror`  
_L22-66_
- L26 _public function_ `FMeshMirror(FDynamicMesh3* Mesh, FVector3d Origin, FVector3d Normal) : Mesh(Mesh) , PlaneOrigin(Origin) , PlaneNormal(Normal)`
- L32 _public prototype_ `virtual ~FMeshMirror() = default;`
- L34 _public member_ `FDynamicMesh3* Mesh;`
- L35 _public member_ `FVector3d PlaneOrigin;`
- L36 _public member_ `FVector3d PlaneNormal;`
- L39 _public member_ `double PlaneTolerance = FMathf::ZeroTolerance * 10.0;` — Tolerance distance for considering a vertex to be "on the plane".
- L42 _public member_ `bool bWeldAlongPlane = true;` — Whether, when using MirrorAndAppend, vertices on the mirror plane should be welded.
- L45 _public member_ `EMeshMirrorNormalMode WeldNormalMode = EMeshMirrorNormalMode::MirrorNormals;` — The normal compute method for welded vertices along the mirror plane.
- L51 _public member_ `bool bAllowBowtieVertexCreation = false;` — Whether, when welding, the creation of new bowtie vertices should be allowed (if a point lies in the mirror plane without an edge in the plane).
- L58 _public prototype_ `void Mirror(FProgressCancel *Progress = nullptr);` — Alters the existing mesh to be mirrored across the mirror plane. @param Progress Object used to cancel the operation early. This leaves the mesh in an undefined state.
- L65 _public prototype_ `void MirrorAndAppend(FProgressCancel* Progress = nullptr);` — Appends a mirrored copy of the mesh to the mesh. @param Progress Object used to cancel the operation early. This leaves the mesh in an undefined state.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DYNAMICMESH_API`
- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MeshPlaneCut.h` (Public)


#### class `UE::Geometry::FMeshPlaneCutFixLayout`  
`class FMeshPlaneCutFixLayout`  
_L27-31_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L30 _public prototype_ `virtual ~FMeshPlaneCutFixLayout() = default;`

#### class `UE::Geometry::FMeshPlaneCut`  
`class FMeshPlaneCut : public FMeshPlaneCutFixLayout`  
_L50-224_
- inherits: `FMeshPlaneCutFixLayout`
- desc: Cut the Mesh with the Plane. The *positive* side, ie (p-o).n > 0, is removed. If possible, returns boundary loop(s) along cut (this will fail if cut intersected with holes in mesh). Also FillHoles() for a topological fill. Or use CutLoops and fill yourself. Algorithm is: 1) find all edge crossings 2) optionally discard any triangles with all vertex distances < epsilon. 3) Do edge splits at crossings 4 option a) (optionally) delete all vertices on positive side 4 option b) (OR optionally) disconnect all triangles w/ vertices on positive side (if keeping both sides) 4 option c) do nothing (if keeping both sides and not disconnecting them) 5) (optionally) collapse any degenerate boundary edges 6) (optionally) change an attribute tag for all triangles on positive side 7) find loops through valid boundary edges (ie connected to splits, or on-plane edges) (if second half was kept, do this separately for each separate mesh ID label)
- L57 _public member_ `FDynamicMesh3 *Mesh;` — Inputs
- L58 _public member_ `FVector3d PlaneOrigin, PlaneNormal;`
- L58 _public member_ `FVector3d PlaneOrigin, PlaneNormal;`
- L63 _public member_ `TUniqueFunction<bool(int32)> EdgeFilterFunc = nullptr;` — If set, only edges that pass this filter will be split
- L66 _public member_ `bool bSimplifyAlongNewEdges = false;` — Control whether we attempt to auto-simplify the small planar triangles that the plane cut operation tends to generate
- L68 _public member_ `bool bCollapseDegenerateEdgesOnCut = true;`
- L71 _public member_ `float UVScaleFactor = 1.0f;` — UVs on any hole fill surfaces are scaled by this amount
- L73 _public member_ `double DegenerateEdgeTol = FMathd::ZeroTolerance;`
- L76 _public member_ `double PlaneTolerance = FMathf::ZeroTolerance * 10.0;` — Tolerance distance for considering a vertex to be 'on plane'
- L79 _public member_ `FLocalPlanarSimplify SimplifySettings;` — Settings to apply if bSimplifyAlongNewEdges == true
- L99 _public member_ `TArray<FOpenBoundary> OpenBoundaries;` — note: loops and spans within a single FOpenBoundary could be part of the same hole-fill triangulation separate open boundary structs will be considered separately and will not share hole fill triangles
- L102 _public member_ `TArray<TArray<int>> HoleFillTriangles;` — Triangle IDs of hole fill triangles.  Outer array is 1:1 with the OpenBoundaries array
- L110 _public member_ `TArray<FCutResultRegion> ResultRegions;` — List of output cut regions (eg that have separate GroupIDs). Currently only calculated by SplitEdgesOnly() path
- L116 _public member_ `TArray<int32> ResultSeedTriangles;` — `UE_DEPRECATED(5.3, "To preserve a triangle selection when using SplitEdgesOnly(), instead pass the selection as a pointer to that function.")` — List of output cut triangles representing the seed triangles along the cut. Currently only calculated by SplitEdgesOnly() path
- L124 _public function_ `FMeshPlaneCut(FDynamicMesh3* Mesh, FVector3d Origin, FVector3d Normal) : Mesh(Mesh), PlaneOrigin(Origin), PlaneNormal(Normal)` — Cut mesh with plane. Assumption is that plane normal is Z value.
- L130 _public prototype_ `virtual ~FMeshPlaneCut() = default;` — Note: deprecation warnings disabled on destructor due to deprecated member variables
- L136 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot
- L147 _public prototype_ `virtual bool Cut();` — Compute the plane cut by splitting mesh edges that cross the cut plane, and then deleting any triangles on the positive side of the cutting plane. @return true if operation succeeds
- L159 _public prototype_ `virtual bool CutWithoutDelete(bool bSplitVerticesAtPlane, float OffsetSeparatedPortion = 0.0f, TDynamicMeshScalarTriangleAttribute<int>* TriLabels = nullptr, int NewLabelStartID = 0, bool bAddBoundariesFirstHalf = true, bool bAddBoundariesSecondHalf = true);` — Compute the plane cut by splitting mesh edges that cross the cut plane, but not deleting triangles on positive side. @param bSplitVerticesAtPlane if true, vertices on cutting plane are split into multiple vertices @param OffsetSeparatedPortion positive side of cut mesh is offset by this distance along plane normal @param TriLabels optional per-triangle integer labels @param NewLabelStartID starting new label value @param bAddBoundariesFirstHalf add open boundaries on "first" half to OpenBoundaries list (default true) @param bAddBoundariesSecondHalf add open boundaries on "second" half to OpenBoundaries list (default true) @return true if operation succeeds
- L169 _public function_ `virtual bool SplitEdgesOnly(bool bAssignNewGroups, TSet<int32>* OptionalTriangleSelection)` — Compute the plane cut by splitting mesh edges that cross the cut plane, and then optionally update groups @param bAssignNewGroups if true, update group IDs such that each group-connected-component on either side of the cut plane is assigned a new unique group ID @param OptionalTriangleSelection if non-null, a set of triangle IDs that must be updated along with any triangle splits or deletions in the edge split process @return true if operation succeeds
- L175 _public function_ `virtual bool SplitEdgesOnly(bool bAssignNewGroups)` — `UE_DEPRECATED(5.3, "Instead use the two-parameter version of SplitEdgesOnly, which has direction selection tracking and does not populate the deprecated ResultSeedTriangles")`
- L183 _public prototype_ `virtual bool SimpleHoleFill(int ConstantGroupID = -1);` — Fill cut loops with FSimpleHoleFiller
- L185 _public prototype_ `virtual bool MinimalHoleFill(int ConstantGroupID = -1);`
- L190 _public prototype_ `virtual bool HoleFill(TFunction<TArray<FIndex3i>(const FGeneralPolygon2d&)> PlanarTriangulationFunc, bool bFillSpans, int ConstantGroupID = -1, int MaterialID = -1);` — Fill cut loops with FPlanarHoleFiller, using a caller-provided triangulation function
- L193 _public prototype_ `virtual void TransferTriangleLabelsToHoleFillTriangles(TDynamicMeshScalarTriangleAttribute<int>* TriLabels);`
- L198 _protected prototype_ `void CollapseDegenerateEdges(const TSet<int>& OnCutEdges, const TSet<int>& ZeroEdges);` — `UE_DEPRECATED(5.3, "Use the single-set CollapseDegenerateEdges instead")`
- L205 _protected prototype_ `void CollapseDegenerateEdges(TSet<int>& Edges, bool bRemoveAllDegenerateFromInputSet, TSet<int>* TriangleSelection = nullptr);` — Collapse degenerate edges @param Edges									Edges to consider for collapse; will updated by removing edges at they are collapsed @param bRemoveAllDegenerateFromInputSet			Whether we should also check whether the neighbor edges removed by collapse were also in the set (typically this is not needed, and has additional cost) @param TriangleSelection						Optional set tracking an active selection. Any triangles removed by collapse will also be removed from the set.
- L207 _protected prototype_ `void SplitCrossingEdges(TArray<double>& Signs, TSet<int>& ZeroEdges, TSet<int>& OnCutEdges, bool bDeleteTrisOnPlane = true);`
- L208 _protected prototype_ `void SplitCrossingEdges(TArray<double>& Signs, TSet<int>& ZeroEdges, TSet<int>& OnCutEdges, TSet<int>& OnSplitEdges, bool bDeleteTrisOnPlane = true);`
- L209 _protected prototype_ `void SplitCrossingEdges(bool bDeleteTrisOnPlane, TArray<double>& Signs, TSet<int>& AlreadyOnPlaneEdges, TSet<int32>& CutPlaneEdges, TSet<int>* SplitEdges = nullptr, TSet<int>* OnPlaneVertices = nullptr, TSet<int>* TriangleSelection = nullptr);`
- L212 _protected prototype_ `bool ExtractBoundaryLoops(const TSet<int>& OnCutEdges, const TSet<int>& ZeroEdges, FMeshPlaneCut::FOpenBoundary& Boundary);`
- L216 _protected member_ `TSet<int32> OnCutVertices;` — `UE_DEPRECATED(5.3, "If needed, explicitly request the vertices on the cut plane the the OnPlaneVertices argument of SplitCrossingEdges")` — set of vertices lying on plane after calling SplitCrossingEdges
- L221 _private prototype_ `void ComputeVertexSignedDistances(TArray<double>& Signs, double InvalidDist);` — Helper to compute signed distances from the cutting plane for all vertices of the mesh.  Value at Invalid Vertex IDs will be set to InvalidDist.
- L223 _private prototype_ `bool SplitEdgesOnlyHelper(bool bAssignNewGroups, TSet<int32>* OptionalTriangleSelection, bool bAddDeprecatedResultSeedTriangles);`

#### struct `UE::Geometry::FMeshPlaneCut::FOpenBoundary`  
`struct FOpenBoundary`  
_L88-96_
- desc: Outputs
- L90 _public member_ `int Label;` — optional ID, used to transfer label to new hole-fill triangles
- L91 _public member_ `float NormalSign = 1;` — -1 for the open boundary on the other side of the cut (for the CutWithoutDelete path)
- L92 _public member_ `TArray<FEdgeLoop> CutLoops;`
- L93 _public member_ `TArray<FEdgeSpan> CutSpans;`
- L94 _public member_ `bool CutLoopsFailed = false;` — set to true if we could not compute cut loops/spans
- L95 _public member_ `bool FoundOpenSpans = false;` — set to true if we found open spans in cut

#### struct `UE::Geometry::FMeshPlaneCut::FCutResultRegion`  
`struct FCutResultRegion`  
_L104-108_
- L106 _public member_ `int32 GroupID;`
- L107 _public member_ `TArray<int32> Triangles;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API DYNAMICMESH_API`
- L18 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MeshProjectionHull.h` (Public)


#### class `UE::Geometry::FMeshProjectionHull`  
`class FMeshProjectionHull`  
_L22-82_
- desc: Calculate a Convex Hull for a Mesh by first Projecting all vertices to a plane, computing a 2D convex polygon that contains them, and then sweeping that 2D hull to create an extruded 3D volume.
- L26 _public member_ `const FDynamicMesh3* Mesh;` — Input Mesh
- L29 _public member_ `FFrame3d ProjectionFrame;` — Input 3D Frame/Plane
- L32 _public member_ `bool bSimplifyPolygon = false;` — If true, 2D convex hull is simplified using MinEdgeLength and DeviationTolerance
- L34 _public member_ `double MinEdgeLength = 0.01;` — Minimum Edge Length of the simplified 2D Convex Hull
- L36 _public member_ `double DeviationTolerance = 0.1;` — Deviation Tolerance of the simplified 2D Convex Hull
- L39 _public member_ `double MinThickness = 0.0;` — Minimum thickness of extrusion. If extrusion length is smaller than this amount, box is expanded symmetrically
- L43 _public member_ `FPolygon2d ConvexHull2D;` — Calculated convex hull polygon
- L46 _public member_ `FPolygon2d SimplifiedHull2D;` — Simplified convex hull polygon. Not initialized if bSimplifyPolygon == false
- L49 _public member_ `FDynamicMesh3 ConvexHull3D;` — Output swept-polygon convex hull
- L63 _public member_ `EKeep3DHullSide Keep3DHullSide = EKeep3DHullSide::None;` — Whether to conform to the 3D convex hull surface on the front or back side of the sweep, or to use a flat surface on both sides of the swept hull
- L66 _public function_ `FMeshProjectionHull(const FDynamicMesh3* MeshIn)`
- L75 _public prototype_ `bool Compute();` — Calculate output 2D Convex Polygon and Swept-Polygon 3D Mesh for vertices of input Mesh @return true on success
- L80 _private prototype_ `bool ComputeWith3DHullSide(FFrame3d CenterFrame, double ExtrudeLength);` — Helper to compute the 3D hull when Keep3DHullSide is not None; called by Compute after the 2D projection hull is computed

#### enum `UE::Geometry::FMeshProjectionHull::EKeep3DHullSide`  
`enum class EKeep3DHullSide : uint8`  
_L51-60_
- L54 _public enumerator_ `None` — Both sides of the projection hull will be flat
- L56 _public enumerator_ `Front` — The front of the projection hull will follow the 3D convex hull, and the back will be flat
- L58 _public enumerator_ `Back` — The back of the projection hull will follow the 3D convex hull, and the front will be flat

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MeshRegionOperator.h` (Public)


#### class `UE::Geometry::FMeshRegionOperator`  
`class FMeshRegionOperator`  
_L31-256_
- desc: This class automatically extracts a submesh from a mesh, and can re-insert it after you have edited it, as long as you have not messed up the boundary [TODO] Should this share any code w/ RegionRemesher? [TODO] ReinsertSubToBaseMapT is not returned by the FDynamicMeshEditor.ReinsertSubmesh, instead we are trying to guess it here, by making some assumptions about what happens. It works for now, but it would better if FDynamicMeshEditor returned this information.
- L34 _public member_ `FDynamicMesh3* BaseMesh;`
- L35 _public member_ `FDynamicSubmesh3 Region;`
- L38 _public member_ `FOptionallySparseIndexMap ReinsertSubToBaseMapV;` — this is only valid after BackPropagate() call!! maps submeshverts to base mesh
- L41 _public member_ `FOptionallySparseIndexMap ReinsertSubToBaseMapT;` — Note computation of this is kind of a hack right now; see TODO in class comment above
- L44 _public member_ `FDynamicMeshEditor::EDuplicateTriBehavior ReinsertDuplicateTriBehavior = FDynamicMeshEditor::EDuplicateTriBehavior::EnsureContinue;` — handle a tricky problem...see comments for EDuplicateTriBehavior enum
- L47 _public member_ `TArray<int> CurrentBaseTris;` — IDs of triangles in the base mesh that correspond to the submesh at time of last Compute or BackPropagate
- L49 _public function_ `FMeshRegionOperator(FDynamicMesh3* Base, const TArrayView<const int>& RegionTris, TFunctionRef<void(FDynamicSubmesh3&)> ConfigSubmeshFunc) : BaseMesh(Base)`
- L58 _public function_ `FMeshRegionOperator(FDynamicMesh3* Base, const TArrayView<const int>& RegionTris) : BaseMesh(Base)`
- L69 _public function_ `const TArray<int>& CurrentBaseTriangles() const` — @return the array of sub-region triangles. This is either the input regionTris or the submesh triangles after they are re-inserted.
- L77 _public function_ `TSet<int> CurrentBaseInteriorVertices() const` — @return base mesh interior vertices of region (does not include region boundary vertices)
- L114 _public function_ `void RepairPossibleNonManifoldEdges()` — After remeshing we may create an internal edge between two boundary vertices [a,b]. Those vertices will be merged with vertices c and d in the base mesh. If the edge [c,d] already exists in the base mesh, then after the merge we would have at least 3 triangles at this edge. Dang. A common example is a 'fin' triangle that would duplicate a 'fin' on the border of the base mesh after removing the submesh, but this situation can arise anywhere (eg think about one-triangle-wide strips). This is very hard to remove, but we can at least avoid creating non-manifold edges (which with the current DMesh3 will be prevented, hence leaving a hole) by splitting the internal edge in the submesh (which presumably we were remeshing anyway, so changes are ok).
- L163 _public function_ `void SetSubmeshGroupID(int GID)` — @param gid New group ID to set for entire submesh
- L178 _public function_ `bool BackPropropagate(bool bAllowSubmeshRepairs = true)` — Remove the original submesh region and merge in the remeshed version. You can call this multiple times as the base-triangle-set is updated. @param bAllowSubmeshRepairs if true, we allow the submesh to be modified to prevent creation of non-manifold edges. You can disable this, however then some of the submesh triangles may be discarded. @return false if there were errors in insertion, ie if some triangles failed to insert. Does not revert changes that were successful.
- L232 _public function_ `bool BackPropropagateVertices(bool bRecomputeBoundaryNormals = false)` — Transfer vertex positions in submesh back to base mesh; for use when the vertices in submesh still directly correspond back @return true on success

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Geometry` (scope `UE`)
- L217 _function_ `new_tris.SetNum(Algo::RemoveIf(new_tris, [](int id) { return id == -2; }));` (scope `UE::Geometry::FMeshRegionOperator::BackPropropagate`)
- L221 _function_ `checkSlow(IndexUtil::ArrayCheck(new_tris, [this](int TID) {return BaseMesh->IsTriangle(TID); }));` (scope `UE::Geometry::FMeshRegionOperator::BackPropropagate`) — assert that new triangles are all valid (goes wrong sometimes??)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MeshResolveTJunctions.h` (Public)


#### class `UE::Geometry::FMeshResolveTJunctions`  
`class FMeshResolveTJunctions`  
_L44-74_
- desc: FMeshResolveTJunctions splits edges to create matching vertices at T-Junctions in the mesh. T-Junctions are edge configurations where a border vertex lies on an opposing border edge. This frequently occurs in (eg) CAD meshes where the tessellator had bugs or simply did not bother to ensure that tessellations match on adjacent spline patches. The simplest case would be, one side has two collinear edges [A,B] and [B,C], and the other side has edge [F,G] such that F/A and G/C are coincident. The implementation works by adding a matching vertex to [F,G], via an edge split at the projected location of B, to create a new vertex X that could be welded with B. F  A                         F  A So basically it    |  |                         |  | turns this         |  B         into this one   X  B configuration      |  |                         |  | G  C                         G  C If everything is within-tolerance, then after resolving all the T-Junctions, a FMergeCoincidentMeshEdges would successfully weld the new set of border edges back together (note: caller must do this, FMeshResolveTJunctions only splits, it does not weld!) Caller can provide a subset of edges via BoundaryEdges, otherwise all boundary edges in Mesh will be used. Current implementation is O(N*M) in the number of boundary edges (N) and boundary vertices (M). Could be improved with a spatial data structure.
- L48 _public member_ `static const double DEFAULT_TOLERANCE;` — default tolerance is float ZeroTolerance
- L51 _public member_ `FDynamicMesh3* Mesh;` — The mesh that we are modifying
- L54 _public member_ `TSet<int32> BoundaryEdges;` — Subset of mesh boundary edges (otherwise all boundary edges are processed)
- L57 _public member_ `double DistanceTolerance = DEFAULT_TOLERANCE;` — Distance threshold used for various checks (eg is vertex on edge, end endpoint tolerance, etc)
- L60 _public member_ `int32 NumSplitEdges = 0;` — Number of edges that were split to resolve T-junctions
- L64 _public function_ `FMeshResolveTJunctions(FDynamicMesh3* MeshIn) : Mesh(MeshIn)`
- L72 _public prototype_ `bool Apply();` — Run the resolve operation and modify .Mesh @return true if the algorithm succeeds

#### class `UE::Geometry::FMeshSnapOpenBoundaries`  
`class FMeshSnapOpenBoundaries`  
_L80-122_
- desc: Similar to FMeshResolveTJunctions, but does not add any vertices to the mesh. Supports running multiple snapping iterations, because snapped-to edges may move in subsequent snaps.
- L84 _public member_ `static const double DEFAULT_TOLERANCE;` — default tolerance is float ZeroTolerance
- L87 _public member_ `FDynamicMesh3* Mesh;` — The mesh that we are modifying
- L90 _public member_ `TSet<int32> BoundaryEdges;` — Subset of mesh boundary edges (otherwise all boundary edges are processed)
- L93 _public member_ `double DistanceTolerance = DEFAULT_TOLERANCE;` — Distance threshold used for various checks (eg is vertex on edge, end endpoint tolerance, etc)
- L96 _public member_ `double VertexSnapToleranceFactor = 1.0;` — Scalar multiple of DistanceTolerance at which we snap a vertex directly to another vertex, rather than an edge
- L99 _public member_ `int32 NumVertexSnaps = 0;` — Number of vertex snaps performed (cumulative over iterations)
- L102 _public member_ `int32 MaxIterations = 1;` — Maximum number of snapping iterations to perform
- L105 _public member_ `bool bSnapToEdges = true;` — Whether vertices can be snapped to edges; otherwise, vertices are only snapped to other vertices
- L108 _public member_ `bool bPreventFlips = true;` — Whether to avoid snapping in cases where doing so would locally flip a triangle
- L112 _public function_ `FMeshSnapOpenBoundaries(FDynamicMesh3* MeshIn) : Mesh(MeshIn)`
- L120 _public prototype_ `bool Apply();` — Run the resolve operation and modify .Mesh @return true if the algorithm succeeds

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/MinimalHoleFiller.h` (Public)


#### class `UE::Geometry::FMinimalHoleFiller`  
`class FMinimalHoleFiller : public IHoleFiller`  
_L29-77_
- inherits: `IHoleFiller`
- L33 _public function_ `FMinimalHoleFiller(FDynamicMesh3* InMesh, FEdgeLoop InFillLoop) : Mesh(InMesh), FillLoop(InFillLoop), FillMesh(nullptr)`
- L39 _public prototype_ `bool Fill(int32 GroupID = -1) override;`
- L42 _public member_ `bool bIgnoreBoundaryTriangles = false;` — Settings
- L43 _public member_ `bool bOptimizeDevelopability = true;`
- L44 _public member_ `bool bOptimizeTriangles = true;`
- L45 _public member_ `double DevelopabilityTolerance = 0.0001;`
- L47 _public member_ `bool bAutoFillPrimaryColors = true;` — whether to automatically fill in PrimaryColors on new hole fill triangles
- L52 _private member_ `FDynamicMesh3* Mesh;` — Inputs
- L53 _private member_ `FEdgeLoop FillLoop;`
- L55 _private member_ `TUniquePtr<FMeshRegionOperator> RegionOp;`
- L56 _private member_ `FDynamicMesh3* FillMesh;`
- L57 _private member_ `TSet<int> BoundaryVertices;`
- L58 _private member_ `TMap<int, double> ExteriorAngleSums;`
- L59 _private member_ `TArray<double> Curvatures;`
- L61 _private prototype_ `void AddAllEdges(int EdgeID, TSet<int>& EdgeSet);`
- L63 _private prototype_ `double AspectMetric(int eid);`
- L64 _private prototype_ `static double GetTriAspect(const FDynamicMesh3& mesh, FIndex3i& tri);`
- L66 _private prototype_ `void UpdateCurvature(int vid);`
- L67 _private prototype_ `double CurvatureMetricCached(int a, int b, int c, int d);`
- L68 _private prototype_ `double CurvatureMetricEval(int a, int b, int c, int d);`
- L69 _private prototype_ `double ComputeGaussCurvature(int vid);`
- L72 _private prototype_ `void CollapseToMinimal();` — Steps in Fill:
- L73 _private prototype_ `void RemoveRemainingInteriorVerts();`
- L74 _private prototype_ `void FlipToFlatter();`
- L75 _private prototype_ `void FlipToMinimizeCurvature();`
- L76 _private prototype_ `void FlipToImproveAspectRatios();`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API DYNAMICMESH_API`
- L20 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/OffsetMeshRegion.h` (Public)


#### class `UE::Geometry::FOffsetMeshRegionFixLayout`  
`class FOffsetMeshRegionFixLayout`  
_L24-28_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L27 _public prototype_ `virtual ~FOffsetMeshRegionFixLayout() = default;`

#### class `UE::Geometry::FOffsetMeshRegion`  
`class FOffsetMeshRegion : public FOffsetMeshRegionFixLayout`  
_L40-260_
- inherits: `FOffsetMeshRegionFixLayout`
- desc: FOffsetMeshRegion implements local extrusion/offset of a mesh region. The selected triangles are separated and then stitched back together, creating an new strip of triangles around their border (s). The offset region is then transformed using the OffsetPositionFunc. Complex input regions are handled, eg it can be multiple disconnected components, donut-shaped, etc Each quad of the border loop is assigned it's own normal and UVs (ie each is a separate UV-island)
- L67 _public member_ `FDynamicMesh3* Mesh;` — The mesh that we are modifying
- L70 _public member_ `TArray<int32> Triangles;` — The triangle region we are modifying
- L73 _public member_ `TFunction<FVector3d(const FVector3d& Position, const FVector3d& VertexVector, int Vid)> OffsetPositionFunc = [this](const FVector3d& Position, const FVector3d& VertexVector, int Vid) { return Position + this->DefaultOffsetDistance * (FVector3d)VertexVector; };` — OffsetPositionFunc function is called to generate the offset vertex position.
- L75 _public function_ ``
- L80 _public member_ `double DefaultOffsetDistance = 1.0;` — Used in the default OffsetPositionFunc.
- L83 _public member_ `EVertexExtrusionVectorType ExtrusionVectorType = EVertexExtrusionVectorType::Zero;` — Determines the type of vector passed in per-vertex to OffsetPositionFunc
- L92 _public member_ `TFunction<bool(int32 Eid1, int32 Eid2)> LoopEdgesShouldHaveSameGroup = [this](int32 Eid1, int32 Eid2) { return EdgesSeparateSameGroupsAndAreColinearAtBorder(Mesh, Eid1, Eid2, true); };` — When stitching the extruded portion to the source loop, this determines the grouping of the side quads by passing in successive Eids in the original loop. For instance, always returning true will result in one group for the stitched portion, and always returning true will result in a separate group for every edge quad. By default, the same group is given to adjacent edges that separate the same two groups, or to border edges that are colinear.
- L93 _public function_ `[this](int32 Eid1, int32 Eid2)`
- L96 _public member_ `float UVScaleFactor = 1.0f;` — quads on the stitch loop are planar-projected and scaled by this amount
- L99 _public member_ `bool bOffsetFullComponentsAsSolids = true;` — If a sub-region of Triangles is a full connected component, offset into a solid instead of leaving a shell
- L106 _public member_ `bool bIsPositiveOffset = true;` — When bOffsetFullComponentsAsSolids is true and the extrusion applied by OffsetPositionFunc is negative, then fully-connected components need to be turned inside-out. Thus, in this circumstance we need to be notified whether the OffsetPositionFunc is applying a positive or negative offset.
- L109 _public member_ `double MaxScaleForAdjustingTriNormalsOffset = 4.0;` — When using SelectionTriNormalsAngleWeightedAdjusted to keep triangles parallel, clamp the offset scale to at most this factor
- L115 _public member_ `int32 NumSubdivisions = 0;` — Number of subdivisions along the length of the "tubes" used to stitch the offset regions. This parameter is only supported in EVersion::Version1 and later
- L121 _public member_ `bool bSingleGroupPerArea = true;` — If true, each extruded area gets a single new group, instead of remapping the input groups This parameter is only supported in EVersion::Version1 and later
- L127 _public member_ `bool bGroupPerSubdivision = true;` — If true, each subdivision level gets a new group This parameter is only supported in EVersion::Version1 and later
- L134 _public member_ `bool bUVIslandPerGroup = true;` — if true, new UV island is assigned for each group in stitch region. This parameter is only supported in EVersion::Version1 and later This parameter is only supported in EVersion::Version1 and later
- L140 _public member_ `bool bInferMaterialID = true;` — If true, Material IDs around the border of the extrude area are propagated "down" the extrusion tube This parameter is only supported in EVersion::Version1 and later
- L149 _public member_ `double CreaseAngleThresholdDeg = 180.0;` — Split the extrude "tube" into separate groups based on the opening angle between quads. This split is done relative to the above group options, so even if the tube would only have a single group, but the extrude area is a square, it will be split into groups based on the corners. This parameter is only supported in EVersion::Version1 and later
- L156 _public member_ `int SetMaterialID = 0;` — Constant Material ID to set along the extrusion tubes This parameter is only supported in EVersion::Version1 and later
- L173 _public member_ `EVersion UseVersion = EVersion::Current;` — Version of Offset operation being used. Defaults to Current, ie most recent version
- L219 _public member_ `TArray<FOffsetInfo> OffsetRegions;` — List of offset regions/components
- L224 _public member_ `TArray<int32> AllModifiedAndNewTriangles;` — List of all triangles created/modified by this operation
- L227 _public prototype_ `FOffsetMeshRegion(FDynamicMesh3* mesh);`
- L229 _public prototype_ `virtual ~FOffsetMeshRegion() = default;`
- L235 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot
- L249 _public prototype_ `virtual bool Apply();` — Apply the Offset operation to the input mesh. @return true if the algorithm succeeds
- L252 _public prototype_ `static bool EdgesSeparateSameGroupsAndAreColinearAtBorder(FDynamicMesh3* Mesh, int32 Eid1, int32 Eid2, bool bCheckColinearityAtBorder);` — The default function used for LoopEdgesShouldHaveSameGroup.
- L256 _protected prototype_ `virtual bool ApplyOffset(FOffsetInfo& Region);`
- L258 _protected prototype_ `virtual bool ApplyOffset_Legacy(FOffsetInfo& Region);`
- L259 _protected prototype_ `virtual bool ApplyOffset_Version1(FOffsetInfo& Region);`

#### enum `UE::Geometry::FOffsetMeshRegion::EVertexExtrusionVectorType`  
`enum class EVertexExtrusionVectorType`  
_L47-60_
- desc: Method used to determine the per-vertex offset direction vector
- L50 _public enumerator_ `Zero` — No geometric offset vector, client must define offset via custom OffsetPositionFunc
- L52 _public enumerator_ `VertexNormal` — Offset vector is per-vertex normal, either provided by FDynamicMesh3 Per-Vertex Normals if defined, or computed by averaging one-ring face normals
- L54 _public enumerator_ `SelectionTriNormalsAngleWeightedAverage` — Angle weighted average of the triangles in the selection that contain this vertex(unit length)
- L59 _public enumerator_ `SelectionTriNormalsAngleWeightedAdjusted` — Like SelectionTriNormalsAngleWeightedAverage, but with the vertex length adjusted to try to keep the selection triangles parallel to their original location.

#### enum `UE::Geometry::FOffsetMeshRegion::EVersion`  
`enum class EVersion`  
_L162-170_
- desc: Support for different versions of the OffsetMeshRegion geometric operation. We default to the latest version.
- L165 _public enumerator_ `Current = 0` — always use most recent version
- L167 _public enumerator_ `Legacy = 1` — initial implementation, various limitations and issues, maintained for back-compat
- L169 _public enumerator_ `Version1 = 2` — support NumSubdivisions, UVs and Normals computed by polygroup

#### struct `UE::Geometry::FOffsetMeshRegion::FOffsetInfo`  
`struct FOffsetInfo`  
_L183-214_
- desc: Offset information for a single connected component
- L189 _public member_ `TArray<int32> OffsetTids;` — Set of triangles for this region. These will be the same Tids that were originally in the region.
- L194 _public member_ `TArray<int32> OffsetGroups;` — Groups on offset faces. These IDs will be the same as the original groups in the region.
- L197 _public member_ `TArray<FEdgeLoop> BaseLoops;` — Initial loops on the mesh
- L205 _public member_ `TArray<FEdgeLoop> OffsetLoops;` — Offset loops on the mesh. If the region had bowtie vertices (in terms of selection, not even necessarily in terms of original mesh topology), then the number of loops here may no longer match number of loops in BaseLoops, StitchTriangles, etc (for example, imagine a circular hole tangent inside a circular region; when the tangent bowtie is split, this becomes one C-shaped loop instead of two nested ones)
- L208 _public member_ `TArray<TArray<int>> StitchTriangles;` — Lists of triangle-strip "tubes" that connect each loop-pair
- L210 _public member_ `TArray<TArray<int>> StitchPolygonIDs;` — List of group ids / polygon ids on each triangle-strip "tube"
- L213 _public member_ `bool bIsSolid = false;` — If true, full region was thickened into a solid

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/PNTriangles.h` (Public)


#### class `UE::Geometry::FPNTriangles`  
`class FPNTriangles`  
_L25-78_
- L34 _public member_ `FDynamicMesh3* Mesh = nullptr;` — The mesh that we are modifying. If the operator fails or is canceled by the user, the mesh will not be changed.
- L41 _public member_ `FProgressCancel* Progress = nullptr;` — Set this to be able to cancel running operation.
- L44 _public member_ `int32 TessellationLevel = 1;` — How many times we are recursively subdividing triangles (loop style subdivision).
- L51 _public member_ `bool bRecalculateNormals = false;` — If true and the mesh has the normal overlay then recalculate it. If true and the normal overlay doesn't exists, compute per-vertex normals (if they are enabled in the mesh). If false, only perform the displacement.
- L54 _public function_ `FPNTriangles(FDynamicMesh3* Mesh) : Mesh(Mesh)`
- L58 _public prototype_ `virtual ~FPNTriangles() = default;`
- L63 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot.
- L77 _public prototype_ `virtual bool Compute();` — Generate PN Triangles geometry and optionally compute quadratically varying normals. @return true if the algorithm succeeds, false if it failed or was canceled by the user.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/PlanarFlipsOptimization.h` (Public)


#### class `UE::Geometry::FPlanarFlipsOptimization`  
`class FPlanarFlipsOptimization`  
_L22-45_
- desc: If both triangles on an edge are coplanar, we can arbitrarily flip the interior edge to improve triangle quality. Similarly if one triangle on an edge is degenerate, we can flip the edge without affecting the shape to try to remove it. This code does one or more passes of such an optimization.
- L26 _public function_ `explicit FPlanarFlipsOptimization(FDynamicMesh3* MeshIn, int32 NumPassesIn = 1, double PlanarDotThreshIn = 0.99) : Mesh(MeshIn) , NumPasses(NumPassesIn) , PlanarDotThresh(PlanarDotThreshIn)`
- L33 _public member_ `FDynamicMesh3* Mesh;`
- L34 _public member_ `int32 NumPasses;`
- L35 _public member_ `double PlanarDotThresh;`
- L36 _public member_ `bool bRespectGroupBoundaries = true;`
- L41 _public prototype_ `void Apply();` — Apply the operation to the mesh.
- L44 _protected prototype_ `void ApplySinglePass();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DYNAMICMESH_API`
- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/PlanarHoleFiller.h` (Public)


#### class `UE::Geometry::FPlanarHoleFiller`  
`class FPlanarHoleFiller : public IHoleFiller`  
_L29-68_
- inherits: `IHoleFiller`
- desc: Fill a set of boundary loops with planar surfaces.  User must provide the triangulation function.
- L35 _public member_ `FDynamicMesh3* Mesh;` — Inputs
- L36 _public member_ `const TArray<TArray<int>> *VertexLoops;`
- L38 _public member_ `TFunction<TArray<FIndex3i>(const FGeneralPolygon2d&)> PlanarTriangulationFunc;`
- L40 _public member_ `FVector3d PlaneOrigin;`
- L41 _public member_ `FVector3d PlaneNormal;`
- L44 _public member_ `bool bAutoFillPrimaryColors = true;` — whether to automatically fill in PrimaryColors on new hole fill triangles
- L50 _public function_ `FPlanarHoleFiller(FDynamicMesh3* Mesh, const TArray<TArray<int>> *VertexLoops, TFunction<TArray<FIndex3i>(const FGeneralPolygon2d&)> PlanarTriangulationFunc, FVector3d PlaneOrigin, FVector3d PlaneNormal) : Mesh(Mesh), VertexLoops(VertexLoops), PlanarTriangulationFunc(PlanarTriangulationFunc), PlaneOrigin(PlaneOrigin), PlaneNormal(PlaneNormal)` — Construct planar hole filler (projects the hole edges to a plane and fills the hole w/ a general 2D polygon triangulation)
- L54 _public prototype_ `virtual ~FPlanarHoleFiller() = default;`
- L60 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot
- L67 _public prototype_ `bool Fill(int GroupID = -1) override;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DYNAMICMESH_API`
- L19 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/PolyEditingEdgeUtil.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L25 _prototype_ `void ComputeInsetLineSegmentsFromEdges( const FDynamicMesh3& Mesh, const TArray<int32>& EdgeList, double InsetDistance, TArray<FLine3d>& InsetLinesOut );` (scope `UE::Geometry`) — For each edge in EdgeList, compute a line segment offset from the original edge by distance InsetDistance. Assumes that each Edge is a boundary edge and so Triangle0 of that edge defines "inside" direction.
- L38 _prototype_ `void SolveInsetVertexPositionsFromInsetLines( const FDynamicMesh3& Mesh, const TArray<FLine3d>& InsetEdgeLines, const TArray<int32>& VertexIDs, TArray<FVector3d>& VertexPositionsOut, bool bIsLoop);` (scope `UE::Geometry`) — For each vertex in VertexIDs, compute inset position based on list of precomputed inset lines and store in VertexPositionsOut. Assumption is that each vertex position was at the intersection point of the pre-inset lines, ie sequential edge-line-pairs determine each sequential vertex position @param bIsLoop if true, vertex list is treated as a loop, otherwise as an open span
- L51 _prototype_ `FVector3d SolveInsetVertexPositionFromLinePair( const FVector3d& Position, const FLine3d& InsetEdgeLine1, const FLine3d& InsetEdgeLine2);` (scope `UE::Geometry`) — Solve for a new inset position by finding the intersection point a pair of inset-lines (or handle parallel-lines case). Assumption is that Position is the location of the initial vertex on the pre-inset edge-line-pair, ie at their intersection point.
- L70 _prototype_ `void ComputeNewGroupIDsAlongEdgeLoop( FDynamicMesh3& Mesh, const TArray<int32>& LoopEdgeIDs, TArray<int32>& NewLoopEdgeGroupIDsOut, TArray<int32>& NewGroupIDsOut, TFunctionRef<bool(int32 Eid1, int32 Eid2)> EdgesShouldHaveSameGroupFunc);` (scope `UE::Geometry`) — Compute a new set of GroupIDs along an edge loop under the assumption that the edge loop is about to be split and new geometry introduced. The decision is based on a provided EdgesShouldHaveSameGroupFunc function which is called with sequential pairs of edges. For example if this function returns true when the GroupIDs are the same on both edges, then this function will create a new GroupID for each sequential span of non-matching GroupIDs (ie often the "expected" behavior). @param LoopEdgeIDs the EdgeIDs of the loop @param NewLoopEdgeGroupIDsOut returned with new GroupID for each input EdgeID, same length as LoopEdgeIDs @param NewGroupIDsOut list of newly-allocated GroupIDs @param EdgesShouldHaveSameGroupFunc predicate that determines where new GroupIDs will be allocated

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/PolyEditingUVUtil.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L26 _prototype_ `void ComputeArbitraryTrianglePatchUVs( FDynamicMesh3& Mesh, FDynamicMeshUVOverlay& UVOverlay, const TArray<int32>& TriangleSet );` (scope `UE::Geometry`) — Create a new single UV island for the provided TriangleSet in the given Mesh/UVOverlay, by computing an ExpMap parameterization based on an automatically-detected midpoint of the triangle patch. The UV scale is determined automatically based on the UV/3D area ratio of triangles adjacent to the TriangleSet (using a ratio of 1 if the triangles have no neighbours). @param TriangleSet a list of triangles, must be a single connected component
- L43 _prototype_ `double ComputeAverageUVScaleRatioAlongVertexPath( const FDynamicMesh3& Mesh, const FDynamicMeshUVOverlay& UVOverlay, const TArray<int32>& VertexPath, double* PathLengthOut = nullptr, double* UVPathLengthOut = nullptr );` (scope `UE::Geometry`) — Compute the total UVLength/MeshLength ratio along the given VertexPath. Other 3D lengths can then be scaled to comparable UV-space lengths by multiplying by this value. Edges must exist between the vertices along the path, and loops are not considered. Each UV edge for a 3D edge is considered, ie if a 3D edge corresponds to 2 UV edges, both are counted, and if the 3D edge has no UV edges, it is skipped. @param VertexPath list of vertices which are connected by edges @param PathLengthOut optional output param for sum of 3D edge lengths along path (arc length) @param UVPathLengthOut optional output param for sum of UV edge lengths along path @return UVPathLength / PathLength, or 1.0 if no valid UV edges along the path existed

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/PolyModeling/PolyModelingFaceUtil.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)
- L28 _prototype_ `FFrame3d ComputeFaceSelectionFrame( const FDynamicMesh3& Mesh, const TArray<int32>& Triangles, bool bIsDefinitelySingleComponent = false);` (scope `UE::Geometry`) — Try to compute a good "Frame" for the selected Triangles of the Mesh. Only the largest triangle-connected-component of Triangles is considered. The Frame Z is aligned with the area-weighted average normal of the connected triangles. Initially the Frame is placed at the area-weighted centroid of the connected triangles. Rays are cast along Z in both directions, if either hits, the Frame is translated to the nearer hit. @param bIsDefinitelySingleComponent if this is known, passing as true will speed up the computation

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/PolyModeling/PolyModelingMaterialUtil.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)
- L21 _prototype_ `bool ComputeMaterialIDRange( const FDynamicMesh3& Mesh, FInterval1i& MaterialIDRange );` (scope `UE::Geometry`) — Compute inclusive range [0...N] of MaterialID values currently in use on Mesh (ie range always includes 0) @return true if MaterialIDs attribute exists (if false, Range is returned as [0,0])
- L35 _prototype_ `bool ComputeMaterialIDsForVertexPath( const FDynamicMesh3& Mesh, const TArray<int32>& VertexPath, bool bIsLoop, TArray<int32>& EdgeMaterialIDsOut, int32 FallbackMaterialID = 0);` (scope `UE::Geometry`) — Compute a MaterialID for each edge along the VertexPath based on the MaterialID of adjacent triangles. Currently, for each Edge, EdgeTriangle.A is used. @param VertexPath list of sequential vertices that are connected by mesh edges @param bIsLoop is the path a loop? @param EdgeMaterialIDsOut returned list of per-edge Material ID. Length is VertexPath.Num-1 for open paths and VertexPath.Num for loops @param FallbackMaterialID default MaterialID to use if no Material attribute exists or no edge is found @return true if MaterialIDs attribute exists

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/PolygroupRemesh.h` (Public)


#### class `UE::Geometry::FPolygroupRemeshFixLayout`  
`class FPolygroupRemeshFixLayout`  
_L29-33_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L32 _public prototype_ `virtual ~FPolygroupRemeshFixLayout() = default;`

#### class `UE::Geometry::FPolygroupRemesh`  
`class FPolygroupRemesh : public FPolygroupRemeshFixLayout`  
_L39-96_
- inherits: `FPolygroupRemeshFixLayout`
- desc: PolygroupRemesh -- remesh only considering polygroup features (topological corners and bends on polygroup edges) This can help clean up low poly meshes that have extra vertices along straight edges e.g. after mesh Boolean operations
- L48 _public member_ `FDynamicMesh3* Mesh;` — The mesh to remesh -- will be updated in place
- L51 _public member_ `const FGroupTopology* Topology;` — Topology of polygroups in the mesh, before the remesh has been computed
- L54 _public member_ `TFunction<TArray<FIndex3i>(const FGeneralPolygon2d&)> PlanarTriangulationFunc;` — Planar triangulation function (e.g. ConstrainedDelaunayTriangulate<double> in GeometryAlgorithms)
- L57 _public member_ `double SimplificationAngleTolerance = .1;` — Units are degrees.  The angle change in boundary edge directions at a group-boundary vertex beyond which we need to keep the vertex in our remesh
- L60 _public member_ `FProgressCancel* Progress = nullptr;` — Set this to be able to cancel running operation
- L65 _public function_ `FPolygroupRemesh(FDynamicMesh3* Mesh, const FGroupTopology* Topology, TFunction<TArray<FIndex3i>(const FGeneralPolygon2d&)> PlanarTriangulationFunc) : Mesh`
- L71 _public prototype_ `virtual ~FPolygroupRemesh() = default;`
- L76 _public function_ `EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot
- L87 _public prototype_ `bool Compute();` — Compute the plane cut by splitting mesh edges that cross the cut plane, and then deleting any triangles on the positive side of the cutting plane. @return true if operation succeeds
- L91 _protected function_ `virtual bool Cancelled()` — If this returns true, abort computation.

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API DYNAMICMESH_API`
- L23 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/QuadGridPatchUtil.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L17 _prototype_ `void ComputeNormalsForQuadPatch( FDynamicMesh3& Mesh, const FQuadGridPatch& QuadPatch );` (scope `UE::Geometry`) — Create a new Normals "island" (ie surrounded by hard edges) for the QuadPatch of the Mesh,
- L25 _prototype_ `bool ComputeUVIslandForQuadPatch( FDynamicMesh3& Mesh, const FQuadGridPatch& QuadPatch, double UVScaleFactor = 1.0, int UVOverlayIndex = 0);` (scope `UE::Geometry`) — Create a new UV Island for the QuadPatch triangles of the Mesh, and then assign UVs based on the grid layout.

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/RemoveOccludedTriangles.h` (Public)


#### enum `UE::Geometry::EOcclusionTriangleSampling`  
`enum class EOcclusionTriangleSampling`  
_L30-35_
- L32 _public enumerator_ `Centroids = 0`
- L33 _public enumerator_ `Vertices = 1`
- L34 _public enumerator_ `VerticesAndCentroids = 2`

#### enum `UE::Geometry::EOcclusionCalculationMode`  
`enum class EOcclusionCalculationMode`  
_L37-41_
- L39 _public enumerator_ `FastWindingNumber = 0`
- L40 _public enumerator_ `SimpleOcclusionTest = 1`

#### class `UE::Geometry::TRemoveOccludedTriangles`  
`template<typename OccluderTriangleMeshType> class TRemoveOccludedTriangles`  
_L85-624_
- desc: Remove "occluded" triangles, i.e. triangles on the "inside" of the mesh(es). This is a fuzzy definition, current implementation has a couple of options including a winding number-based version and an ambient-occlusion-ish version, where if face is occluded for all test rays, then we classify it as inside and remove it. Note this class always removes triangles from an FDynamicMesh3, but can use any mesh type to define the occluding geometry (as long as the mesh type implements the TTriangleMeshAdapter fns)
- L89 _public member_ `FDynamicMesh3* Mesh;`
- L91 _public function_ `TRemoveOccludedTriangles(FDynamicMesh3* Mesh) : Mesh(Mesh)`
- L94 _public prototype_ `virtual ~TRemoveOccludedTriangles() = default;`
- L109 _public function_ `virtual bool Select(const TArrayView<const FTransformSRT3d> MeshLocalToOccluderSpaces, const TArrayView<TMeshAABBTree3<OccluderTriangleMeshType>*> Spatials, const TArrayView<TFastWindingTree<OccluderTriangleMeshType>*> FastWindingTrees, const TArrayView<const FTransformSRT3d> SpatialTransforms = TArrayView<const FTransformSRT3d>(), bool bTestOccludedByAny = false)` — Select the occluded triangles, considering the given occluder AABB trees (which may represent more geometry than a single mesh) See simpler invocations below for the single instance case or the case where you'd like the spatial data structures built for you Selection will be stored in the RemovedT array, but no triangles will be removed. @param MeshLocalToOccluderSpaces Transforms to take instances of the local mesh into the space of the occluders @param Spatials AABB trees for all occluders @param FastWindingTrees Precomputed fast winding trees for occluders @param SpatialTransforms Transforms AABB/winding tree to shared occluder space (if empty, Identity is used) @param bTestOccludedByAny If true, a triangle is occluded if it is fully occluded by *any* occluder. Otherwise, we test if it's occluded by the combination of all occluders. @return true on success
- L435 _public function_ `virtual bool RemoveSelected()` — Remove triangles that were selected (the triangle IDs in the RemoveT array)
- L464 _public function_ `virtual bool Apply(const TArrayView<const FTransformSRT3d> MeshLocalToOccluderSpaces, const TArrayView<TMeshAABBTree3<OccluderTriangleMeshType>*> Spatials, const TArrayView<TFastWindingTree<OccluderTriangleMeshType>*> FastWindingTrees, const TArrayView<const FTransformSRT3d> SpatialTransforms = TArrayView<const FTransformSRT3d>(), bool bTestOccludedByAny = false)` — Remove the occluded triangles, considering the given occluder AABB trees (which may represent more geometry than a single mesh) See simpler invocations below for the single instance case or the case where you'd like the spatial data structures built for you @param MeshLocalToOccluderSpaces Transforms to take instances of the local mesh into the space of the occluders @param Spatials AABB trees for all occluders @param FastWindingTrees Precomputed fast winding trees for occluders @param SpatialTransforms Transforms AABB/winding tree to shared occluder space (if empty, Identity is used) @param bTestOccludedByAny If true, a triangle is occluded if it is fully occluded by *any* occluder. Otherwise, we test if it's occluded by the combination of all occluders. @return true on success
- L486 _public function_ `virtual bool Select(const TArrayView<const FTransformSRT3d> MeshLocalToOccluderSpaces, TMeshAABBTree3<OccluderTriangleMeshType>* Spatial, TFastWindingTree<OccluderTriangleMeshType>* FastWindingTree)` — Select the occluded triangles, considering the given occluder AABB tree (which may represent more geometry than a single mesh) See simpler invocations below for the single instance case or the case where you'd like the spatial data structures built for you @param MeshLocalToOccluderSpaces Transforms to take instances of the local mesh into the space of the occluders @param Spatials AABB trees for all occluders @param FastWindingTrees Precomputed fast winding trees for occluders @return true on success
- L504 _public function_ `virtual bool Apply(const TArrayView<const FTransformSRT3d> MeshLocalToOccluderSpaces, TMeshAABBTree3<OccluderTriangleMeshType>* Spatial, TFastWindingTree<OccluderTriangleMeshType>* FastWindingTree)` — Remove the occluded triangles, considering the given occluder AABB tree (which may represent more geometry than a single mesh) See simpler invocations below for the single instance case or the case where you'd like the spatial data structures built for you @param MeshLocalToOccluderSpaces Transforms to take instances of the local mesh into the space of the occluders @param Spatials AABB trees for all occluders @param FastWindingTrees Precomputed fast winding trees for occluders @return true on success
- L519 _public function_ `virtual bool Select(const FTransformSRT3d& MeshLocalToOccluderSpace, TMeshAABBTree3<OccluderTriangleMeshType>* Spatial, TFastWindingTree<OccluderTriangleMeshType>* FastWindingTree)` — Select the occluded triangles -- single instance case @param LocalToWorld Transform to take the local mesh into the space of the occluder geometry @param Occluder AABB tree of occluding geometry @return true on success
- L533 _public function_ `virtual bool Apply(const FTransformSRT3d& MeshLocalToOccluderSpace, TMeshAABBTree3<OccluderTriangleMeshType>* Spatial, TFastWindingTree<OccluderTriangleMeshType>* FastWindingTree)` — Remove the occluded triangles -- single instance case @param LocalToWorld Transform to take the local mesh into the space of the occluder geometry @param Occluder AABB tree of occluding geometry @return true on success
- L547 _public function_ `virtual bool Select(const FTransformSRT3d& MeshLocalToOccluderSpace, TMeshAABBTree3<OccluderTriangleMeshType>* Occluder)` — Select the occluded triangles -- single instance case w/out precomputed winding tree @param LocalToWorld Transform to take the local mesh into the space of the occluder geometry @param Occluder AABB tree of occluding geometry @return true on success
- L561 _public function_ `virtual bool Apply(const FTransformSRT3d& MeshLocalToOccluderSpace, TMeshAABBTree3<OccluderTriangleMeshType>* Occluder)` — Remove the occluded triangles -- single instance case w/out precomputed winding tree @param LocalToWorld Transform to take the local mesh into the space of the occluder geometry @param Occluder AABB tree of occluding geometry @return true on success
- L570 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot
- L582 _public member_ `EOcclusionTriangleSampling TriangleSamplingMethod = EOcclusionTriangleSampling::Vertices;`
- L585 _public member_ `double NormalOffset = FMathd::ZeroTolerance;` — we nudge points out by this amount to try to counteract numerical issues
- L588 _public member_ `double WindingIsoValue = 0.5;` — use this as winding isovalue for WindingNumber mode
- L590 _public member_ `EOcclusionCalculationMode InsideMode = EOcclusionCalculationMode::FastWindingNumber;`
- L593 _public member_ `int AddRandomRays = 0;` — Number of additional ray directions to add to raycast-based occlusion checks, beyond the default +/- major axis directions
- L596 _public member_ `int AddTriangleSamples = 0;` — Number of additional samples to add per triangle
- L601 _public member_ `FProgressCancel* Progress = nullptr;` — Set this to be able to cancel running operation
- L609 _public member_ `TArray<int> RemovedT;` — indices of removed triangles. will be empty if nothing removed
- L612 _public member_ `bool bRemoveFailed = false;` — true if it wanted to remove triangles but the actual remove operation failed
- L619 _protected function_ `virtual bool Cancelled()` — if this returns true, abort computation.

#### struct `UE::Geometry::TRemoveOccludedTriangles::Select::FTransformWithInv`  
`struct FTransformWithInv`  
_L150-214_
- desc: Helper struct to track both the transform and its inverse
- L152 _public member_ `FTransformSRT3d Transform;`
- L153 _public member_ `FQuaterniond InvRot;`
- L154 _public member_ `FVector3d InvScale;`
- L156 _public function_ `FTransformWithInv() : Transform(FTransformSRT3d::Identity()), InvRot(FQuaterniond::Identity()), InvScale(FVector3d::One())`
- L159 _public function_ `FTransformWithInv(const FTransformSRT3d& Transform) : Transform(Transform)`
- L164 _public function_ `void ComputeInv()`
- L183 _public function_ `inline FVector3d InverseTransformPosition(const FVector3d& P) const`
- L188 _public function_ `inline FVector3d InverseTransformVector(const FVector3d& V) const`
- L194 _public function_ `inline bool IsSameTransform(const FTransformSRT3d& Other) const` — checks if the transform is an exact match
- L203 _public function_ `inline FVector3d InverseTransformUnlessMatch(const FVector3d& Pt, const FVector3d& OriginalPt, const FTransformSRT3d& OriginalXF) const` — apply the inverse transform unless the point was originally transformed by this same transform; then just return the original point use to avoid floating point error shoving a sample into the surface that it came from

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Geometry` (scope `UE`)
- L48 _namespace_ `namespace UE`
- L50 _namespace_ `namespace MeshAutoRepair` (scope `UE`)
- L63 _prototype_ `bool RemoveInternalTriangles(FDynamicMesh3& Mesh, bool bTestPerComponent = false, EOcclusionTriangleSampling SamplingMethod = EOcclusionTriangleSampling::Centroids, EOcclusionCalculationMode OcclusionMode = EOcclusionCalculationMode::FastWindingNumber, int RandomSamplesPerTri = 0, double WindingNumberThreshold = .5, bool bTestOccludedByAny = false);` (scope `UE::MeshAutoRepair`) — Remove any triangles that are internal to the input mesh @param Mesh Input mesh to analyze and remove triangles from @param bTestPerComponent Remove if inside *any* connected component of the input mesh, instead of testing the whole mesh at once. Note in FastWindingNumber mode, this can remove internal pockets that otherwise would be missed @param SamplingMethod Whether to sample centroids, vertices or both @param RandomSamplesPerTri Number of additional random samples to check before deciding if a triangle is occluded @param WindingNumberThreshold Threshold to decide whether a triangle is inside or outside (only used if OcclusionMode is WindingNumber)
- L70 _namespace_ `namespace UE`
- L72 _namespace_ `namespace Geometry` (scope `UE`)
- L217 _typedef_ `typedef TFunction<bool(const TArrayView<TMeshAABBTree3<OccluderTriangleMeshType>*> Spatials, const TArrayView<TFastWindingTree<OccluderTriangleMeshType>*> FastWindingTrees, const FVector3d& Pt, const FVector3d& OriginalPt, const FTransformSRT3d& OriginalXF, const TArray<FTransformWithInv>& SpatialTransforms)> FIsOccludedFn;` (scope `UE::Geometry::TRemoveOccludedTriangles::Select`)
- L223 _function_ `` (scope `UE::Geometry::TRemoveOccludedTriangles::Select`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/RepairOrientation.h` (Public)


#### class `UE::Geometry::FMeshRepairOrientation`  
`class FMeshRepairOrientation`  
_L22-64_
- desc: Invert triangles as needed to a consistent ~"outward" orientation
- L28 _public member_ `FDynamicMesh3* Mesh;` — Inputs
- L30 _public function_ `FMeshRepairOrientation(FDynamicMesh3* Mesh) : Mesh(Mesh)`
- L33 _public prototype_ `virtual ~FMeshRepairOrientation() = default;`
- L39 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot
- L47 _public prototype_ `void OrientComponents();` — locally orient connected components
- L50 _public prototype_ `void SolveGlobalOrientation(FDynamicMeshAABBTree3* Tree);` — globally orient -- to be called after OrientComponents if a more globally consistent result is desired
- L60 _protected member_ `TArray<Component> Components;`
- L62 _protected prototype_ `void ComputeStatistics(FDynamicMeshAABBTree3* Tree);`
- L63 _protected prototype_ `void ComputeComponentStatistics(FDynamicMeshAABBTree3* Tree, Component& c);`

#### struct `UE::Geometry::FMeshRepairOrientation::Component`  
`struct Component`  
_L54-59_
- L56 _public member_ `TArray<int> Triangles;`
- L57 _public member_ `double OutFacing;`
- L58 _public member_ `double InFacing;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DYNAMICMESH_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/SelectiveTessellate.h` (Public)


#### class `UE::Geometry::FTessellationPattern`  
`class FTessellationPattern`  
_L53-195_
- desc: An abstract class for writing tessellation patterns. You can subclass it and implement its virtual methods to specify a custom tessellation behavior. Original mesh edges and triangles are referred to as edge patches and triangle patches. The edge patch handles all the vertices we are adding along the edge. The triangle patch handles all the vertices we are adding inside of the patch (excluding the edges) and the new triangles we are splitting the patch into. Patterns describe how individual patches are tessellated. Although you can access mesh data during the tessellation, the patches do not generate actual vertex coordinates or other attribute data. Instead, new vertices are generated in terms of linear or barycentric coefficients with respect to the edge or triangle vertices. The coefficient data can later be used to interpolate the actual mesh data (vertex positions, colors, normals, etc). Patterns do not need to worry about generating the vertex IDs as those will be provided for each patch during the tessellation and need to simply be referred to when generating triangles. The job of the tessellation pattern is: - Provide the number of new vertices introduced for an edge or a triangle patch. - Provide the number of new triangles introduced for a triangle patch. - Given a single edge patch with vertices [v1,v2], provide coordinates of the new vertices [a_i, a_(i+1), ...] inserted along the edge via a linear coeffcient [t_i, t_(i+1), ...] such that a_i = v1 + t_i*(v2-v1). -
- L57 _public member_ `constexpr static int InvalidIndex = -1;`
- L61 _protected member_ `const FDynamicMesh3* Mesh;`
- L110 _public function_ `FTessellationPattern(const FDynamicMesh3* InMesh) : Mesh(InMesh)`
- L116 _public prototype_ `virtual ~FTessellationPattern() = default;`
- L121 _public prototype_ `virtual EOperationValidationResult Validate() const = 0;` — @return EOperationValidationResult::Ok if we can perform tessellation on the given mesh with this pattern
- L127 _public prototype_ `virtual int GetNumberOfNewVerticesForEdgePatch(const int InEdgeID) const = 0;` — @return the number of new vertices added along the edge patch. If InEdgeID is not valid then return FTessellationPattern::InvalidIndex.
- L133 _public prototype_ `virtual int GetNumberOfNewVerticesForTrianglePatch(const int InTriangleID) const = 0;` — @return the number of new vertices added inside the triangle patch (i.e. exclude vertices added along edges). If InTriangleID is not valid then return FTessellationPattern::InvalidIndex.
- L139 _public prototype_ `virtual int GetNumberOfPatchTriangles(const int InTriangleID) const = 0;` — @return the number of triangles that will be generated after tessellating the patch. If InTriangleID is not valid then return FTessellationPattern::InvalidIndex.
- L148 _public prototype_ `virtual void TessellateEdgePatch(EdgePatch& EdgePatch) const = 0;` — Tessellate the edge patch by generating linear interpolation coefficients for each new vertex and storing the result in the EdgePatch.LinearCoord. @param EdgePatch Edge patch has EdgePatch.EdgeID and EdgePatch.VIDs fields set. The order of IDs is along the edge from one corner to another. The edge direction is same as the direction stored by the FDynamicMesh3 class.
- L160 _public prototype_ `virtual void TessellateTriPatch(TrianglePatch& TriPatch) const = 0;` — Tessellate the triangle patch by generating new vertices inside the triangle. Compute the barycentric coordinates of the new vertices and store them in the TriPatch.BaryCoord. Using the vertices generated in the edge patches and inside the triangle patch, generate new triangles and store the result in the TriPatch.Triangles. @param TriPatch Has all the fields set except the values in the TriPatch.BaryCoord and TriPatch.Triangles which should be set by this method. Both arrays are already sized correctly to be able to hold all the data needed as specified by the GetNumberOfNewVerticesForTrianglePatch() and GetNumberOfPatchTriangles().
- L188 _protected prototype_ `void ComputeInnerConcentricTriangle(const FVector3d& U, const FVector3d& V, const FVector3d& W, const int EdgeTessellationLevel, FVector3d& InnerU, FVector3d& InnerV, FVector3d& InnerW) const;` — Takes a triangle defined by three vertices and a TessellationLevel value. For each corner of the outer triangle, an inner triangle corner is produced at the intersection of two lines extended perpendicular to the corner's two adjacent edges running through the vertex of the subdivided outer edge nearest to that corner. U O / \            O - triangle corner /   \           x - closest vertex to the corner inserted along the edge during tessellation /     \          + - inner vertex resulting from intersection of two lines extened perpendicular to the edges x       x /  .   .  \ /     +     \ /   innerU    \ @note Vertices should be passed in CW order.

#### struct `UE::Geometry::FTessellationPattern::EdgePatch`  
`struct EdgePatch`  
_L72-80_
- desc: Represents an abstract edge as a parameterized line segment with two endpoints [v1,v2]. Contains information about the linear interpolation parameter of the new vertices added along the edge and their vertex IDs. O----x----x----x----O           x  -  New vertices added. We only store their lerp coefficients (t1,t2,t3) v1     a1   a2   a3    v2               with respect to the end points, s.t. a_i = vi + t_i*(v2-v1).
- L74 _public member_ `int EdgeID = IndexConstants::InvalidID;`
- L75 _public member_ `TArrayView<int> VIDs;` — Vertex IDs of the new vertices added.
- L76 _public member_ `TArrayView<double> LinearCoord;` — Lerp cooeficients of the new vertices added.
- L77 _public member_ `bool bIsReversed = false;` — If true, we need to traverse BaryCoord and VIDs in reverse order.

#### struct `UE::Geometry::FTessellationPattern::TrianglePatch`  
`struct TrianglePatch`  
_L87-108_
- desc: Represents an abstract triangle patch with corners [u,v,w], s.t. u = (1,0,0), v = (0,1,0), w = (0,0,1). Contains information about the barycentric coordinates and IDs of the new vertices and the new triangles generated during the tessellation.
- L90 _public member_ `int TriangleID = IndexConstants::InvalidID;` — ID of the triangle in the original mesh this patch represents
- L93 _public member_ `FIndex3i UVWCorners = FIndex3i::Invalid();` — Vertex IDs of the 3 corners of the patch. These are the triangle vertex IDs in the original mesh.
- L96 _public member_ `EdgePatch UVEdge;` — Edge patches
- L97 _public member_ `EdgePatch VWEdge;`
- L98 _public member_ `EdgePatch UWEdge;`
- L101 _public member_ `TArrayView<int> VIDs;` — Vertex IDs of the inner vertices added inside the triangle.
- L104 _public member_ `TArrayView<FVector3d> BaryCoord;` — Barycentric coordinates of the inner vertices.
- L107 _public member_ `TArrayView<FIndex3i> Triangles;` — Triangles the patch is split into

#### class `UE::Geometry::FSelectiveTessellate`  
`class FSelectiveTessellate`  
_L209-518_
- desc: Given an input mesh and a tessellation pattern, this operator generates a new tessellated mesh where the triangles affected are subtriangulated according to the rules specified by the pattern. Per-vertex normals, UVs, colors, and extended per-vertex attributes are linearly interpolated to the new vertices. Per-triangle group identifiers/materials and extended triangle attributes for the new triangles are inherited from the corresponding input mesh triangles they replaced. @note Currently does not support interpolation of the GenericAttributes besides Skin Weights.
- L222 _public member_ `FProgressCancel* Progress = nullptr;` — Set this to be able to cancel running operation. @note currently not implemented
- L225 _public member_ `bool bUseParallel = true;` — Should tessellation be multi-threaded.
- L228 _public member_ `FTessellationPattern* Pattern = nullptr;` — Tessellation pattern determines how we tessellate edges and triangles.
- L235 _public member_ `FDynamicMesh3* ResultMesh = nullptr;` — The tessellated mesh.
- L259 _public member_ `FTessellationInformation TessInfo;`
- L267 _protected member_ `const FDynamicMesh3* Mesh = nullptr;` — Points to either the input mesh to be used to generate the new tessellated mesh or will point to a copy of the mesh we are tessellating inplace.
- L273 _protected member_ `bool bInPlace = false;` — If true, the mesh to tessellate is contained in the ResultMesh and will be overwritten with the tessellation result.
- L283 _public function_ `FSelectiveTessellate(FDynamicMesh3* OutMesh) : ResultMesh(OutMesh), bInPlace(true)` — Tessellate the mesh inplace. If the tessellation fails or the user cancelled the operation, OutMesh will not be changed. //TODO: Add an option to turn off making the backup copy of the input mesh in case the computation fails.
- L292 _public function_ `FSelectiveTessellate(const FDynamicMesh3* Mesh, FDynamicMesh3* OutMesh) : ResultMesh(OutMesh), Mesh(Mesh), bInPlace(false)` — Tessellate the mesh and write the result into another mesh. This will overwrite any data stored in the OutMesh.
- L298 _public prototype_ `virtual ~FSelectiveTessellate() = default;`
- L303 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot.
- L323 _public function_ `inline void SetPattern(FTessellationPattern* InPattern)`
- L332 _public prototype_ `virtual bool Compute();` — Generate tessellated geometry. @return true if the algorithm succeeds, false if it failed or was cancelled by the user.
- L381 _public prototype_ `static TUniquePtr<FTessellationPattern> CreateConcentricRingsTessellationPattern(const FDynamicMesh3* InMesh, const TArray<int>& InEdgeTessLevels, const TArray<int>& InInnerTessLevels);` — Pattern where the inner area is tessellated using the style of the OpenGL tessellation shader. The inner area of each tessellated triangle consists of multiple "rings". Areas between the rings are tessellated with the new triangles. You can specify per-edge and per-triangle tessellation levels. Per-edge tessellation level determines how many new vertices are inserted along the new edge. Per-triangle tessellation level determines the number of new vertices along each of the edges of the first inner ring. Each subsequent ring will have 2 fewer vertices. Triangles with a zero inner tessellation level but with a non-zero edge tessellation level (common for those triangles adjacent to the triangles marked for tessellation) will have a single vertex inserted in the middle and connected to all edge vertices (triangle fan). O / \ O. .O /  O  \ O. / \ .O /  O. .O  \ /  /  O  \  \ /  /  / \  \  \ O. /  /   \  \ .O /  O. /     \ .O  \ /  /  O-------O  \  \ O. /   .       .   \ .O /  O----O-------O----O  \ /   .    .       .    .   \ O----O----O-------O----O----O @param InMesh Mesh we are tessellating. @param InEdgeTessLevels Array of InMesh->MaxEdgeID() size, where InEdgeTessLevels[EdgeID] is the number of new vertices inserted along an EdgeID edge. @param InInnerTessLevels Array of InMesh->MaxTriangleID() size, where InInnerTessLevels[TriangleID] is the number of new vertices along each of the edges of the first inner ring.
- L388 _public prototype_ `static TUniquePtr<FTessellationPattern> CreateConcentricRingsTessellationPattern(const FDynamicMesh3* InMesh, const int InTessellationLevel);` — Tessellate the whole mesh such that all the edge and inner tessellation levels are equal to InTessellationLevel.
- L395 _public prototype_ `static TUniquePtr<FTessellationPattern> CreateConcentricRingsTessellationPattern(const FDynamicMesh3* InMesh, const int InTessellationLevel, const TArray<int>& InTriangleList);` — Tessellate only selected triangles such that the edge and inner tessellation levels of those triangles are set to InTessellationLevel.
- L406 _public prototype_ `static TUniquePtr<FTessellationPattern> CreateConcentricRingsTessellationPattern(const TFunctionRef<int(const int EdgeID)> InEdgeFunc, const TFunctionRef<int(const int TriangleID)> InTriFunc);` — InEdgeFunc and InTriFunc functions will be evaluated on all edges and triangles respectively to determine their desired tessellation levels. This can be helpful when the tessellation levels depend on some condition. For example, how close/far the edge/triangle is from some point in space. @note not yet implemented
- L414 _public prototype_ `static TUniquePtr<FTessellationPattern> CreateConcentricRingsPatternFromTriangleGroup(const FDynamicMesh3* InMesh, const int InTessellationLevel, const int InPolygroupID);` — Tessellate only triangles that belong to a given triangle group id. Triangle groups are defined by the FDynamicMesh3::GetTriangleGroup().
- L425 _public prototype_ `static TUniquePtr<FTessellationPattern> CreateConcentricRingsPatternFromPolyGroup(const FDynamicMesh3* InMesh, const int InTessellationLevel, const FString& InLayerName, const int InPolygroupID);` — Tessellate only triangles that belong to a given polygroup id within the polygroup layer attribute (FDynamicMeshPolygroupAttribute) specified by its name. @return nullptr if InMesh has no attributes or if no polygroup layer attribute with the given name or id exists.
- L436 _public prototype_ `static TUniquePtr<FTessellationPattern> CreateConcentricRingsPatternFromMaterial(const FDynamicMesh3* InMesh, const int InTessellationLevel, const int MaterialID);` — Tessellate only triangles that belong to a given material (FDynamicMeshMaterialAttribute). @return nullptr if InMesh has no attributes, no material attribute or if no material attribute with the given id exists.
- L446 _public prototype_ `static TUniquePtr<FTessellationPattern> CreateConcentricRingsPatternFromSelectionAndMaterial(const FDynamicMesh3* InMesh, const int InTessellationLevel, const int MaterialID, const TArray<int>& SelectedTriangles);` — Tessellate only triangles that are selected AND which belong to a given material (FDynamicMeshMaterialAttribute). @return nullptr if InMesh has no attributes, no material attribute, if no material attribute with the given id exists, or if selection is invalid
- L476 _public prototype_ `static TUniquePtr<FTessellationPattern> CreateInnerUnifromTessellationPattern(const FDynamicMesh3* InMesh, const TArray<int>& InEdgeTessLevels, const TArray<int>& InInnerTessLevels);`
- L506 _public prototype_ `static TUniquePtr<FTessellationPattern> CreateUniformTessellationPattern(const FDynamicMesh3* InMesh, const int InTessellationLevel, const TArray<int>& InTriangleList);`
- L510 _public prototype_ `static TUniquePtr<FTessellationPattern> CreateRedGreenTessellationPattern(const FDynamicMesh3* InMesh, const TArray<int>& InTriangleTessLevels);`
- L517 _protected prototype_ `virtual bool Cancelled();` — @return true if we need to abort the computation.

#### struct `UE::Geometry::FSelectiveTessellate::FTessellationInformation`  
`struct FTessellationInformation`  
_L248-257_
- desc: Stores any additional tessellation information that was requested by the caller. The caller should set the pointers to request the information to be computed. @note The caller is responsible for managing the memmory the pointers are pointing to. The operator simply populates the data structures if they are not null.
- L254 _public member_ `TArray<int32>* SelectedVertices = nullptr;` — If not null, construction of tessellated mesh will append a list of all the vertices that belong to triangles affected by the tessellation.
- L256 _public member_ `TMap<int32, TArray<int32>>* TriangleIDToNewTriangleIDs = nullptr;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/SimpleHoleFiller.h` (Public)


#### class `UE::Geometry::FSimpleHoleFiller`  
`class FSimpleHoleFiller : public IHoleFiller`  
_L26-113_
- inherits: `IHoleFiller`
- desc: Fill an EdgeLoop hole with triangles. Supports two fill modes, either a fan connected to a new central vertex, or a triangulation of the boundary polygon
- L38 _public member_ `FDynamicMesh3 *Mesh;` — Inputs
- L39 _public member_ `FEdgeLoop Loop;`
- L40 _public member_ `EFillType FillType = EFillType::TriangleFan;`
- L43 _public member_ `bool bAutoFillPrimaryColors = true;` — whether to automatically fill in PrimaryColors on new hole fill triangles
- L48 _public member_ `int32 NewVertex = IndexConstants::InvalidID;` — Outputs
- L54 _public function_ `FSimpleHoleFiller(FDynamicMesh3* Mesh, FEdgeLoop Loop, EFillType InFillType = EFillType::TriangleFan) : Mesh(Mesh), Loop(Loop), FillType(InFillType)` — Construct simple hole filler (just adds a central vertex and a triangle fan)
- L61 _public prototype_ `virtual ~FSimpleHoleFiller() = default;`
- L67 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot
- L83 _public prototype_ `bool Fill(int32 GroupID = -1) override;`
- L103 _public prototype_ `bool UpdateAttributes(TArray<FMeshRegionBoundaryLoops::VidOverlayMap<FVector2f>>& VidUVMaps);` — Updates the normals and UV's of NewTriangles. UV's are taken from VidUVMaps, which is an array of maps (1:1 with UV layers) that map vid's of vertices on the boundary to their UV elements and values. If an entry for NewVertex is not provided, it is set to be the average of the boundary UV's. For other UV's, an entry must exist, though the UV element ID can be InvalidID if an element does not exist for that UV value. The function will update the element ID in the map to point to the new element once it inserts it. Normals are shared among NewTriangles but not with the surrounding portions of the mesh. @param VidsToUVsMap A map from vertex ID's of the boundary vertices to UV element ID's and/or their values. When the element ID is invalid, a new element is generated using the value, and the map is updated accordingly. @returns false if there is an error, usually if VidsToUVsMap did not have an entry for a needed vertex ID.
- L107 _protected prototype_ `bool Fill_Fan(int32 NewGroupID);`
- L108 _protected prototype_ `bool Fill_EarClip(int32 NewGroupID);`
- L112 _private prototype_ `void FillColors();` — Fill colors on triangles added by the fill, by copying boundary colors

#### enum `UE::Geometry::FSimpleHoleFiller::EFillType`  
`enum class EFillType`  
_L29-33_
- L31 _public enumerator_ `TriangleFan`
- L32 _public enumerator_ `PolygonEarClipping`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DYNAMICMESH_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/SkinWeightBinding.h` (Public)


#### enum `UE::Geometry::ESkinBindingType`  
`enum class ESkinBindingType : uint8`  
_L20-30_
- L25 _public enumerator_ `DirectDistance = 0` — Computes the binding strength by computing the Euclidean distance to the closest set of bones, where the strength of binding is proportional to the inverse distance. May cause bones to affects parts of geometry that, although close in space, may be topologically distant.
- L29 _public enumerator_ `GeodesicVoxel = 1` — Computes the binding by computing the geodesic distance from each set of bones. This is slower than the direct distance.

#### struct `UE::Geometry::SkinBinding::FBonePoseInfo`  
`struct FBonePoseInfo`  
_L36-41_
- L38 _public member_ `FTransform LocalTransform;`
- L39 _public member_ `FName Name;`
- L40 _public member_ `int32 ParentIndex;`

#### struct `UE::Geometry::SkinBinding::FBindSettings`  
`struct FBindSettings`  
_L43-49_
- L45 _public member_ `float Stiffness = 0.2f;`
- L46 _public member_ `int32 MaxInfluences = 5;`
- L47 _public member_ `int32 VoxelResolution = 256;`
- L48 _public member_ `ESkinBindingType BindType = ESkinBindingType::DirectDistance;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)
- L17 _typedef_ `using FDynamicMeshVertexSkinWeightsAttribute = TDynamicVertexSkinWeightsAttribute<FDynamicMesh3>;` (scope `UE::Geometry`)
- L33 _namespace_ `namespace SkinBinding` (scope `UE::Geometry`)
- L52 _prototype_ `void CreateSkinWeights(FDynamicMesh3& InMesh, TConstArrayView<FBonePoseInfo> TransformHierarchy, FName ProfileName, const FBindSettings& Settings);` (scope `UE::Geometry::SkinBinding`) — Create skin weights from the input bone hierarchy, and set them on the dynamic mesh
- L56 _prototype_ `void CreateConstrainedSkinWeights(FDynamicMesh3& InMesh, TConstArrayView<FBonePoseInfo> TransformHierarchy, FName ProfileName, const FBindSettings& Settings, TConstArrayView<TArray<int32, TInlineAllocator<16>>> BoneGroups, TConstArrayView<int32> VIDtoGroupIndex);` (scope `UE::Geometry::SkinBinding`) — Create skin weights from the input bone hierarchy, with vertices constrained to only allow weights on specific subsets of bones. @param VIDtoGroupIndex Mapping from vertex ID to BoneGroups index, or INDEX_NONE if the vertex has no assigned group (will use unconstrained weights in this case)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/SmoothBoneWeights.h` (Public)


#### enum `UE::Geometry::ESmoothBoneWeightsEdgeWeightMethod`  
`enum class ESmoothBoneWeightsEdgeWeightMethod : uint8`  
_L29-35_
- desc: Method used to compute edge weights during bone weight smoothing.
- L32 _public enumerator_ `Uniform = 0` — Each neighbor contributes equally (existing behavior).
- L34 _public enumerator_ `CotanWeights = 1` — Neighbors weighted by cotangent of opposite angles on shared edge.

#### class `UE::Geometry::TBoneWeightsDataSource`  
`template <typename BoneIndexType, typename BoneWeightType> class TBoneWeightsDataSource`  
_L42-58_
- desc: Interface for getting the bone weights data. Should be subclassed and implemented if the bone weights data is not stored using the FDynamicMeshVertexSkinWeightsAttribute.
- L45 _public prototype_ `virtual ~TBoneWeightsDataSource() = default;`
- L48 _public prototype_ `virtual int32 GetBoneNum(const int32 InVertexIDs) = 0;` — Number of bones at a vertex.
- L51 _public prototype_ `virtual BoneIndexType GetBoneIndex(const int32 InVertexIDs, const int32 Index) = 0;` — Bone ID of the bone stored at an index Index, where Index is between 0 and GetBoneNum(InVertexIDs).
- L54 _public prototype_ `virtual BoneWeightType GetBoneWeight(const int32 InVertexIDs, const int32 Index) = 0;` — Bone weight of the bone stored at an index Index, where Index is between 0 and GetBoneNum(InVertexIDs).
- L57 _public prototype_ `virtual BoneWeightType GetWeightOfBoneOnVertex(const int32 InVertexIDs, const BoneIndexType BoneIndex) = 0;` — Bone weight of the bone with Bone ID at a vertex. Must return 0 if bone has no influence.

#### class `UE::Geometry::TSmoothBoneWeights`  
`template <typename BoneIndexType, typename BoneWeightType> class TSmoothBoneWeights`  
_L96-170_
- desc: Collection of algorithms for smoothing bone weights. Bone weight data is fetched using the TBoneWeightsDataSource which is implemented by the caller to match their custom data storage of bone weights. Example usage: // Mesh whose bone weights we are smoothing FDynamicMesh SourceMesh = ... ; // The caller should create a subclass of TBoneWeightsDataSource that implements its interface TUniquePtr<TBoneWeightsDataSource> DataSource = ... ; // Setup the smoothing operator TSmoothBoneWeights SmoothBoneWeights(&SourceMesh, DataSource.Get()); // Array of vertex IDs to apply smoothing to TArray<int32> VerticesToSmooth = ... ; // Run the operator const float SmoothStrength = 0.2; if (SmoothBoneWeights.Validate() == EOperationValidationResult::Ok) { for (const int32 VertexID : VerticesToSmooth) { TMap<BoneIndexType, BoneWeightType> FinalWeights; SmoothBoneWeights.SmoothWeightsAtVertex(VertexID, SmoothStrength, FinalWeights); // Use FinalWeights to modify your weights } }
- L105 _public member_ `FProgressCancel* Progress = nullptr;` — Set this to be able to cancel the running operation.
- L108 _public member_ `BoneWeightType MinimumWeightThreshold = (BoneWeightType) 0.0f;` — Only consider the weights above the threshold.
- L111 _public member_ `ESmoothBoneWeightsEdgeWeightMethod EdgeWeightMethod = ESmoothBoneWeightsEdgeWeightMethod::Uniform;` — The edge weighting method used during smoothing.
- L115 _protected member_ `const FDynamicMesh3* SourceMesh;`
- L118 _protected member_ `TBoneWeightsDataSource<BoneIndexType, BoneWeightType>* DataSource = nullptr;` — Data source supplied by the caller.
- L121 _protected member_ `TArray<double> CotangentEdgeWeights;` — Pre-computed cotangent edge weights indexed by EdgeID. Populated lazily when CotanWeights is selected.
- L124 _protected prototype_ `void ComputeEdgeWeightsIfNeeded();` — Pre-compute edge weights if needed based on EdgeWeightMethod.
- L132 _public prototype_ `TSmoothBoneWeights(const FDynamicMesh3* InSourceMesh, TBoneWeightsDataSource<BoneIndexType, BoneWeightType>* InDataSource = nullptr);` — @param InSourceMesh The mesh whose vertices contain bone weights data. @param InDataSource The bone weights data.
- L134 _public prototype_ `virtual ~TSmoothBoneWeights() = default;`
- L137 _public prototype_ `virtual EOperationValidationResult Validate();` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot.
- L148 _public prototype_ `virtual bool SmoothWeightsAtVertex(const int32 VertexID, const BoneWeightType VertexFalloff, TMap<BoneIndexType, BoneWeightType>& OutFinalWeights);` — Compute smoothed weights at a vertex and return the result. @param VertexID		  The vertex whose weights we are smoothing. @param VertexFalloff   The lerp value between the old and the new weight. @param OutFinalWeights The smoothed weights. @return true if the algorithm succeeds, false if it failed or was canceled by the user.
- L162 _public prototype_ `virtual bool SmoothWeightsAtVertex(const int32 VertexID, const BoneWeightType VertexFalloff, const TSet<BoneIndexType>& LockedBones, TMap<BoneIndexType, BoneWeightType>& OutFinalWeights);` — Compute smoothed weights at a vertex and return the result. @param VertexID		  The vertex whose weights we are smoothing. @param VertexFalloff   The lerp value between the old and the new weight. @param LockedBones	  The bones to exclude from the smooth op @param OutFinalWeights The smoothed weights. @return true if the algorithm succeeds, false if it failed or was canceled by the user.
- L169 _protected prototype_ `virtual bool Cancelled();` — @return if true, abort the computation.

#### class `UE::Geometry::FSmoothDynamicMeshVertexSkinWeights`  
`class FSmoothDynamicMeshVertexSkinWeights : public TSmoothBoneWeights<FBoneIndexType, float>`  
_L201-260_
- inherits: `TSmoothBoneWeights<FBoneIndexType,float>`
- desc: Subclass of TSmoothBoneWeights for dealing with smoothing of bone weights stored in the FDynamicMeshVertexSkinWeightsAttribute. Example usage: // Mesh whose bone weights we are smoothing FDynamicMesh SourceMesh = ... ; // Setup the smoothing operator FSmoothDynamicMeshVertexSkinWeights SmoothBoneWeights(&SourceMesh, FSkeletalMeshAttributes::DefaultSkinWeightProfileName); // Array of vertex IDs to apply smoothing to TArray<int32> VerticesToSmooth = ... ; // Run the operator const float SmoothStrength = 0.2; if (SmoothBoneWeights.Validate() == EOperationValidationResult::Ok) { for (const int32 VertexID : VerticesToSmooth) { SmoothBoneWeights.SmoothWeightsAtVertex(VertexID, SmoothStrength); } }
- L212 _public member_ `int32 MaxNumInfluences = UE::AnimationCore::MaxInlineBoneWeightCount;` — During the smoothing, only use this number of influences per vertex. Prune the excess with the smallest influences and re-normalize.
- L218 _public prototype_ `FSmoothDynamicMeshVertexSkinWeights(const FDynamicMesh3* InSourceMesh, const FName InProfile);` — @param InSourceMesh The mesh whose vertices contain bone weights data. @param InProfile    The name of the skin weights profile containing the bone weights data.
- L224 _public prototype_ `FSmoothDynamicMeshVertexSkinWeights(const FDynamicMesh3* InSourceMesh, FDynamicMeshVertexSkinWeightsAttribute* InAttribute);` — @param InSourceMesh The mesh whose vertices contain bone weights data. @param InAttribute  The skin weight attribute containing the bone data.
- L226 _public prototype_ `virtual ~FSmoothDynamicMeshVertexSkinWeights() = default;`
- L229 _public prototype_ `virtual EOperationValidationResult Validate() override;` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot.
- L240 _public prototype_ `bool SmoothWeightsAtVertex(const int32 VertexID, const float VertexFalloff);` — Compute smoothed weights at a vertex and write the result into FDynamicMeshVertexSkinWeightsAttribute passed upon construction. @param VertexID		  The vertex whose weights we are smoothing. @param VertexFalloff   The lerp value between the old and the new weight. @return true if the algorithm succeeds, false if it failed or was canceled by the user.
- L254 _public prototype_ `bool SmoothWeightsAtVerticesWithinDistance(const TArray<int32>& Vertices, const float Strength, const double FloodFillUpToDistance, const int32 NumIterations);` — Compute smoothed weights at vertices and neighbors within distance and write the result into FDynamicMeshVertexSkinWeightsAttribute passed upon construction. @param Vertices		  		Array of vertex IDs we are smoothing weights for. @param Strength 				The lerp value between the old and the new weight. @param FloodFillUpToDistance	For every vertex in Vertices, find vertices that are within FloodFillUpToDistance geodesic distance away and smooth them as well. @param NumIterations			Number of times the smoothing will be run @return true if the algorithm succeeds, false if it failed or was canceled by the user.
- L257 _protected member_ `TUniquePtr<TBoneWeightsDataSource<FBoneIndexType, float>> SkinWeightsAttributeDataSource = nullptr;`
- L258 _protected member_ `FDynamicMeshVertexSkinWeightsAttribute* Attribute = nullptr;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L19 _typedef_ `template<typename ParentType> class TDynamicVertexSkinWeightsAttribute;` (scope `UE::Geometry`)
- L23 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/SmoothDynamicMeshAttributes.h` (Public)


#### class `UE::Geometry::FSmoothDynamicMeshAttributes`  
`class FSmoothDynamicMeshAttributes`  
_L68-159_
- desc: Smooth scalar data of any dimension that is stored via TDynamicMeshOverlay. The operator doesn't know anything about constraints that are associated with the actual overlay type. For example, if the overlay contains unit length normals, the resulting "smoothed" normals might not have unit length. The smoothing happens in stages: - First, we average the overlay element values at each vertex to obtain the per-vertex values. - For each vertex, we compute the weighted average of its connected neighbors using the EdgeWeightMethod weights. The smoothed value equals the (1-Strength)*PerVertexValue + (Strength)*NeighborAverage. Strength is expected to be in the zero to one range, otherwise the operation can turn from smoothing to more of an unsharp filter. We repeat this NumIterations times. - Finally, the smoothed per-vertex values are written back to the overlay by either overwriting the content of all per-vertex elements (SplitVertexModel == ESplitVertexModel::SetAllToSmoothed) or blending on per-element basis using the BlendWithSmoothedStrength blend value. The calling code could use FSplitAttributeWelder to weld split-attributes that happen to have identical values after this smoothing (happens when the SplitVertexModel == ESplitVertexModel::SetAllToSmoothed). Example Usage: // Smoothing the color FDynamicMesh3 Mesh = ... FDynamicMeshColorOverlay* Colors = Mesh.Attributes()->PrimaryColors(); FSmoothDynamicMeshAttributes BlurOp(&Mesh); // Setup the parameters BlurOp.bUseParallel 
- L77 _public member_ `FProgressCancel* Progress = nullptr;` — Set this to be able to cancel the running operation.
- L80 _public member_ `bool bUseParallel = true;` — Enable/disable multi-threading.
- L83 _public member_ `TArray<int32> Selection;` — Subset of points to smooth.
- L94 _public member_ `EEdgeWeights EdgeWeightMethod = EEdgeWeights::CotanWeights;`
- L104 _public member_ `ESplitVertexModel SplitVertexModel = ESplitVertexModel::SetAllToSmoothed;`
- L107 _public member_ `int32 NumIterations = 0;` — The number of smoothing iterations.
- L110 _public member_ `double Strength = 0.0;` — The strength of each smoothing iteration.
- L116 _public member_ `double BlendWithSmoothedStrength = 0.0;` — Control the amount of blending between the final smoothed value and the original element value. Only used when the SplitVertexModel==ESplitVertexModel::BlendWithSmoothed
- L120 _protected member_ `const FDynamicMesh3* Mesh;`
- L122 _protected member_ `TArray<double> CotangentEdgeWeights;`
- L124 _protected member_ `TArray<double> EdgeLengthWeights;`
- L127 _protected member_ `TArray<int32> ExpandedSelection;` — If Selection array is not empty, will contain all vertices in Selection plus one-ring neighbors for each vertex
- L130 _protected member_ `TMap<int32, int32> VIDToExpandedSelectionIdx;` — Maps mesh Vertex ID to ExpandedSelection index
- L132 _protected member_ `double EdgeLengthThreshold = 1.0;`
- L136 _public prototype_ `FSmoothDynamicMeshAttributes(const FDynamicMesh3& InMesh);`
- L138 _public prototype_ `virtual ~FSmoothDynamicMeshAttributes() = default;`
- L147 _public prototype_ `template<typename RealType, int ElementSize> bool SmoothOverlay(TDynamicMeshOverlay<RealType, ElementSize>* InOverlay, const TArray<bool>& DimensionsToSmooth = TArray<bool>());` — @param InOverlay Overlay to smooth @param DimensionsToSmooth ElementSize array, where DimensionsToSmooth[Idx] is true if we want smooth the dimension Idx. If empty, we smooth all dimensions. @return true if the algorithm succeeds, false if it failed or was canceled by the user.
- L152 _protected prototype_ `virtual bool Cancelled();` — @return if true, abort the computation.
- L155 _protected function_ `inline int32 MeshVIDToSelectionIdx(int32 VertexID) const` — @return the index of the vertex into ExpandedSelection array if Selection is not empty, otherwise returns VertexID.

#### enum `UE::Geometry::FSmoothDynamicMeshAttributes::EEdgeWeights`  
`enum class EEdgeWeights : uint8`  
_L85-93_
- L88 _public enumerator_ `Uniform = 0` — Smooth the attributes where each neighbor is weighted equally.
- L90 _public enumerator_ `EdgeLength = 1` — Smooth the attributes where each neighbor is weighted proportionally to the shared edge length.
- L92 _public enumerator_ `CotanWeights = 2` — Smooth the attributes where each neighbor is weighted proportionally to the cotangent weight of the shared edge.

#### enum `UE::Geometry::FSmoothDynamicMeshAttributes::ESplitVertexModel`  
`enum class ESplitVertexModel : uint8`  
_L97-103_
- desc: How to deal with the split vertices.
- L100 _public enumerator_ `SetAllToSmoothed` — Each element will be assigned the same value.
- L102 _public enumerator_ `BlendWithSmoothed` — Each element will be blended with he smoothed value. Set BlendWithSmoothedStrength to control the amount of blend.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MeshDeformation` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/SmoothHoleFiller.h` (Public)


#### struct `UE::Geometry::FSmoothFillOptions`  
`struct FSmoothFillOptions`  
_L29-69_
- desc: Fill parameters
- L34 _public member_ `bool bConstrainToHoleInterior = true;` — If this is true, we don't modify any triangles outside hole (often results in lower-quality fill)
- L41 _public member_ `double InteriorSmoothness = 0.2;` — Controls the trade off between smoothness in the fill region vs faithfulness to the original fill surface. This value is inversely proportional to the vertex constraint weight in Laplacian smoothing, for vertices in the fill interior far away from the boundary.
- L47 _public member_ `int RemeshingExteriorRegionWidth = 2;` — If we are not constraining remeshing to the fill interior, how many one-rings outside of the fill should we include in remeshing.
- L52 _public member_ `int SmoothingExteriorRegionWidth = 2;` — Number of one-rings to include when smoothing the fill region. Use this to control smoothness across the boundary.
- L57 _public member_ `int SmoothingInteriorRegionWidth = 2;` — Smoothing constraint falloff region from border into the interior
- L63 _public member_ `double FillDensityScalar = 1.0;` — Controls the target edge length during remeshing. The target edge length is set to the average length of the input loop edges divided by this value.
- L68 _public member_ `bool bProjectDuringRemesh = false;` — Whether to use projection in the post-smooth remeshing

#### class `UE::Geometry::FSmoothHoleFiller`  
`class FSmoothHoleFiller : public IHoleFiller`  
_L75-103_
- inherits: `IHoleFiller`
- desc: This fills a hole in a mesh by doing a trivial fill, then doing a remesh, then a laplacian smooth, then a second remesh.
- L78 _public prototype_ `FSmoothHoleFiller(FDynamicMesh3& Mesh, const FEdgeLoop& FillLoop);`
- L80 _public member_ `FSmoothFillOptions FillOptions;`
- L82 _public prototype_ `bool Fill(int32 GroupID) override;`
- L87 _protected member_ `FDynamicMesh3& Mesh;` — Mesh to operate on
- L90 _protected member_ `const FEdgeLoop& FillLoop;` — Loop to fill
- L93 _protected member_ `double RemeshingTargetEdgeLength;` — initialized to the average edge length of FillLoop / FillDensityScalar
- L95 _protected prototype_ `void SmoothAndRemeshPreserveRegion(FMeshFaceSelection& tris, bool bFinal);`
- L97 _protected prototype_ `void SmoothAndRemesh(FMeshFaceSelection& tris);`
- L99 _protected prototype_ `void ConstrainSubregionSeams(FSubRegionRemesher& Remesher, bool bConstrainROIBoundary);`
- L101 _protected prototype_ `void DefaultConfigureRemesher(FSubRegionRemesher& Remesher, bool bConstrainROIBoundary);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DYNAMICMESH_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/TransferBoneWeights.h` (Public)


#### class `UE::Geometry::FTransferBoneWeights`  
`class FTransferBoneWeights`  
_L90-298_
- L111 _public member_ `FProgressCancel* Progress = nullptr;` — Set this to be able to cancel the running operation.
- L114 _public member_ `bool bUseParallel = true;` — Enable/disable multi-threading.
- L117 _public member_ `ETransferBoneWeightsMethod TransferMethod = ETransferBoneWeightsMethod::ClosestPointOnSurface;` — The transfer method to compute the bone weights.
- L120 _public member_ `FTransformSRT3d TargetToWorld = FTransformSRT3d::Identity();` — Transform applied to the input target mesh or target point before transfer.
- L126 _public member_ `bool bIgnoreBoneAttributes = false;` — Completely ignore the source and target mesh bone attributes when transferring weights from one dynamic mesh to another. This skips re-indexing and simply copies skin weights over. Use with caution.
- L133 _public member_ `double SearchRadius = -1;` — Radius for searching the closest point. If negative, all points are considered.
- L139 _public member_ `double NormalThreshold = -1;` — Maximum angle (in radians) difference between target and source point normals to be considred a match. If negative, normals are ignored.
- L146 _public member_ `bool LayeredMeshSupport = false;` — If true, when the closest point doesn't pass the normal threshold test, will try again with a flipped normal. This helps with layered meshes where the "inner" and "outer" layers are close to each other but whose normals are pointing in the opposite directions.
- L149 _public member_ `int32 NumSmoothingIterations = 0;` — The number of optional post-processing smoothing iterations applied to the vertices without the match.
- L152 _public member_ `float SmoothingStrength = 0.0f;` — The strength of each post-processing smoothing iteration.
- L155 _public member_ `bool bUseIntrinsicLaplacian = false;` — If true, will use the intrinsic Delaunay mesh to construct sparse Cotangent Laplacian matrix.
- L161 _public member_ `int32 MaxNumInfluences = UE::AnimationCore::MaxInlineBoneWeightCount;` — During the transfer, only use this number of influences per vertex. Prune the excess with the smallest influences and re-normalize.
- L170 _public member_ `TArray<float> ForceInpaint;` — Optional mask where if ForceInpaint[VertexID] != 0 we want to force the weights for the vertex to be computed automatically. @note Only used when TransferMethod == ETransferBoneWeightsMethod::InpaintWeights. The size must be equal to the InTargetMesh.MaxVertexID(), otherwise the mask is ignored.
- L176 _public member_ `FName ForceInpaintWeightMapName = NAME_None;` — Alternatively, if the mask is stored as a target mesh weight map attribute, specify its name. Will be ignored if the ForceInpaint array is not empty and valid.
- L182 _public member_ `TArray<int32> TargetVerticesSubset;` — Optional subset of target mesh vertices to transfer weights to. If left empty, skin weights will be transferred to all target mesh vertices.
- L189 _public member_ `TArray<bool> MatchedVertices;` — MatchedVertices[VertexID] is set to true for a target mesh vertex ID with a match found, false otherwise.
- L194 _protected member_ `const FDynamicMesh3* SourceMesh;` — Source mesh we are transfering weights from.
- L197 _protected member_ `FName SourceProfileName;` — The name of the source mesh skinning profile name.
- L203 _protected member_ `const FDynamicMeshAABBTree3* SourceBVH = nullptr;` — The caller can optionally specify the source mesh BVH in case this operator is run on multiple target meshes while the source mesh remains the same. Otherwise BVH tree will be computed.
- L206 _protected member_ `TUniquePtr<FDynamicMeshAABBTree3> InternalSourceBVH;` — If the caller doesn't pass BVH for the source mesh then we compute one.
- L209 _protected member_ `TUniquePtr<FMeshNormals> InternalSourceMeshNormals;` — If the source mesh doesn't have per-vertex normals then compute them
- L221 _public prototype_ `FTransferBoneWeights(const FDynamicMesh3* InSourceMesh, const FName& InSourceProfileName, const FDynamicMeshAABBTree3* SourceBVH = nullptr);` — @param InSourceMesh The mesh we are transferring weights from @param InSourceProfileName The profile name of the skin weight attribute we are transferring weights from. @param SourceBVH Optional source mesh BVH. If not provided, one will be computed internally. @note Assumes that the InSourceMesh has bone attributes, use bIgnoreBoneAttributes flag to ignore the bone attributes and skip re-indexing.
- L225 _public prototype_ `virtual ~FTransferBoneWeights();`
- L230 _public prototype_ `virtual EOperationValidationResult Validate();` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot.
- L245 _public prototype_ `virtual bool TransferWeightsToMesh(FDynamicMesh3& InOutTargetMesh, const FName& InTargetProfileName);` — Transfer the bone weights from the source mesh to the given target mesh and store the result in the skin weight attribute with the given profile name. @param InOutTargetMesh	  Target mesh we are transfering weights into @param InTargetProfileName Skin weight profile name we are writing into. If the profile with that name exists, then the data will be overwritten, otherwise a new attribute will be created. @return true if the algorithm succeeds, false if it failed or was canceled by the user. @note Assumes that the InOutTargetMesh has bone attributes, use bIgnoreBoneAttributes flag to ignore the bone attributes and skip re-indexing.
- L259 _public prototype_ `virtual bool TransferWeightsToPoint(UE::AnimationCore::FBoneWeights& OutWeights, const FVector3d& InPoint, const TMap<FName, uint16>* TargetBoneToIndex = nullptr, const FVector3f& InNormal = FVector3f::Zero());` — Compute the bone weights for a given point using the ETransferBoneWeightsMethod::ClosestPointOnSurface algorithm. @param OutWeights 		Bone weight computed for the input transformed point. @param InPoint			Point for which we are computing the bone weight. @param TargetBoneToIndex Optional map from the bone names to the bone indices of the target skeleton. If null, the bone indices of the skinning weights will not be re-indexed after the transfer. @param InNormal			Normal at the input point. Should be set if NormalThreshold >= 0. @return true if the algorithm succeeds, false if it failed to find the matching point or was canceled by the user.
- L280 _public prototype_ `template<typename BoneIndexType, typename BoneFloatWeightType, typename PosVectorType, typename NormalVectorType = float> bool TransferWeightsToPoint(TArray<BoneIndexType>& OutBones, TArray<BoneFloatWeightType>& OutWeights, const UE::Math::TVector<PosVectorType>& InPoint, const TMap<FName, uint16>* TargetBoneToIndex = nullptr, const UE::Math::TVector<NormalVectorType>& InNormal = UE::Math::TVector<NormalVectorType>::Zero());` — Compute the bone weights for a given point using the ETransferBoneWeightsMethod::ClosestPointOnSurface algorithm. @param OutBones			Array of bone indices. Array size is equal to the number of bone influences. @param OutWeights		Array of bone weights. Array size is equal to the number of bone influences. @param InPoint			Point for which we are computing the bone weight. @param TargetBoneToIndex Optional map from the bone names to the bone indices of the target skeleton. If null, the bone indices of the skinning weights will not be re-indexed after the transfer. @param InNormal			Normal at the input point. Should be set if NormalThreshold >= 0. @return true if the algorithm succeeds, false if it failed to find the matching point or was canceled by the user. @note Add specialization in the source file for template types you want to use. Currently supporting int for BoneIndexType and float for BoneFloatWeightType, PosVectorType, NormalVectorType
- L288 _protected prototype_ `virtual bool Cancelled();` — @return if true, abort the computation.
- L296 _protected prototype_ `bool FindClosestPointOnSourceSurface(const FVector3d& InPoint, const FTransformSRT3d& InToWorld, int32& OutTriID, FVector3d& OutBary);` — Find the closest point on the surface of the source mesh and return the ID of the triangle containing it and its barycentric coordinates. @return true if point is found, false otherwise

#### enum `UE::Geometry::FTransferBoneWeights::ETransferBoneWeightsMethod`  
`enum class ETransferBoneWeightsMethod : uint8`  
_L94-104_
- L99 _public enumerator_ `ClosestPointOnSurface = 0` — For every vertex on the target mesh, find the closest point on the surface of the source mesh. If that point is within the SearchRadius, and their normals differ by less than the NormalThreshold, then we directly copy the weights from the source point to the target mesh vertex.
- L103 _public enumerator_ `InpaintWeights = 1` — Same as the ClosestPointOnSurface but for all the vertices we didn't copy the weights directly, automatically compute the smooth weights.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DYNAMICMESH_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)
- L20 _typedef_ `template<typename MeshType> class TMeshAABBTree3;` (scope `UE::Geometry`)
- L25 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/TransferDynamicMeshAttributes.h` (Public)


#### class `UE::Geometry::FTransferVertexColorAttribute`  
`class FTransferVertexColorAttribute`  
_L32-194_
- L53 _public member_ `FProgressCancel* Progress = nullptr;` — Set this to be able to cancel the running operation.
- L56 _public member_ `bool bUseParallel = true;` — Enable/disable multi-threading.
- L59 _public member_ `ETransferMethod TransferMethod = ETransferMethod::ClosestPointOnSurface;` — The transfer method to compute the bone weights.
- L62 _public member_ `FTransformSRT3d TargetToWorld = FTransformSRT3d::Identity();` — Transform applied to the input target mesh or target point before transfer.
- L69 _public member_ `double SearchRadius = -1;` — Radius for searching the closest point. If negative, all points are considered.
- L75 _public member_ `double NormalThreshold = -1;` — Maximum angle (in radians) difference between target and source point normals to be considered a match. If negative, normals are ignored.
- L82 _public member_ `bool LayeredMeshSupport = false;` — If true, when the closest point doesn't pass the normal threshold test, will try again with a flipped normal. This helps with layered meshes where the "inner" and "outer" layers are close to each other but whose normals are pointing in the opposite directions.
- L85 _public member_ `int32 NumSmoothingIterations = 0;` — The number of optional post-processing smoothing iterations applied to the vertices without the match.
- L88 _public member_ `float SmoothingStrength = 0.0f;` — The strength of each post-processing smoothing iteration.
- L91 _public member_ `bool bUseIntrinsicLaplacian = false;` — If true, will use the intrinsic Delaunay mesh to construct sparse Cotangent Laplacian matrix.
- L100 _public member_ `TArray<float> ForceInpaint;` — Optional mask where if ForceInpaint[VertexID] != 0 we want to force the colors for the vertex to be computed automatically. @note Only used when TransferMethod == ETransferMethod::Inpaint. The size must be equal to the InTargetMesh.MaxVertexID(), otherwise the mask is ignored.
- L106 _public member_ `TArray<int32> TargetVerticesSubset;` — Optional subset of target mesh vertices to transfer weights to. If left empty, skin weights will be transferred to all target mesh vertices.
- L113 _public member_ `TArray<bool> MatchedVertices;` — MatchedVertices[VertexID] is set to true for a target mesh vertex ID with a match found, false otherwise.
- L116 _public member_ `bool bHardEdges = false;` — Creates vertex instances per triangle to be able to have per-face vertex colors.
- L119 _public member_ `float BiasRatio = UE_KINDA_SMALL_NUMBER;` — Ratio used to blend a vertex between its position and the center of the face (0 = vertex position, 1 = face centroid)
- L124 _protected member_ `const FDynamicMesh3* SourceMesh = nullptr;` — Source mesh we are transferring colors from.
- L130 _protected member_ `const FDynamicMeshAABBTree3* SourceBVH = nullptr;` — The caller can optionally specify the source mesh BVH in case this operator is run on multiple target meshes while the source mesh remains the same. Otherwise BVH tree will be computed.
- L133 _protected member_ `TUniquePtr<FDynamicMeshAABBTree3> InternalSourceBVH;` — If the caller doesn't pass BVH for the source mesh then we compute one.
- L136 _protected member_ `TUniquePtr<FMeshNormals> InternalSourceMeshNormals;` — If the source mesh doesn't have per-vertex normals then compute them
- L146 _public prototype_ `FTransferVertexColorAttribute(const FDynamicMesh3* InSourceMesh, const FDynamicMeshAABBTree3* SourceBVH = nullptr);` — @param InSourceMesh The mesh we are transferring colors from @param SourceBVH Optional source mesh BVH. If not provided, one will be computed internally. @note Assumes that the InSourceMesh has a primary colors attribute.
- L148 _public prototype_ `virtual ~FTransferVertexColorAttribute();`
- L153 _public prototype_ `virtual EOperationValidationResult Validate();` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot.
- L162 _public prototype_ `virtual bool TransferColorsToMesh(FDynamicMesh3& InOutTargetMesh);` — Transfer the colors from the source mesh to the given target mesh and store the result in the primary colors attribute. @param InOutTargetMesh	  Target mesh we are transferring colors into @return true if the algorithm succeeds, false if it failed or was canceled by the user.
- L174 _public prototype_ `bool TransferColorToPoint(FVector4f& OutColor, const FVector3d& InPoint, const FVector3f& InNormal = FVector3f::Zero()) const;` — Compute the color for a given point using the ETransferMethod::ClosestPointOnSurface algorithm. @param OutColor 		Color computed for the input transformed point. @param InPoint		Point for which we are computing the color. @param InNormal		Normal at the input point. Should be set if NormalThreshold >= 0. @return true if the algorithm succeeds, false if it failed to find the matching point or was canceled by the user.
- L179 _protected prototype_ `virtual bool Cancelled();` — @return if true, abort the computation.
- L187 _protected prototype_ `bool FindClosestPointOnSourceSurface(const FVector3d& InPoint, const FTransformSRT3d& InToWorld, int32& OutTriID, FVector3d& OutBary) const;` — Find the closest point on the surface of the source mesh and return the ID of the triangle containing it and its barycentric coordinates. @return true if point is found, false otherwise
- L193 _protected prototype_ `int32 TransferUsingClosestPoint(FDynamicMesh3& InOutTargetMesh, const TUniquePtr<FMeshNormals>& InTargetMeshNormals);` — Transfer the colors from the source mesh to the given target mesh using the closest point algorithm. @return the number of matching vertices / elements

#### enum `UE::Geometry::FTransferVertexColorAttribute::ETransferMethod`  
`enum class ETransferMethod : uint8`  
_L36-46_
- L41 _public enumerator_ `ClosestPointOnSurface = 0` — For every vertex on the target mesh, find the closest point on the surface of the source mesh. If that point is within the SearchRadius, and their normals differ by less than the NormalThreshold, then we directly copy the weights from the source point to the target mesh vertex.
- L45 _public enumerator_ `Inpaint = 1` — Same as the ClosestPointOnSurface but for all the vertices we didn't copy the weights directly, automatically compute the smooth weights.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)
- L18 _typedef_ `template<typename MeshType> class TMeshAABBTree3;` (scope `UE::Geometry`)
- L23 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/UniformTessellate.h` (Public)


#### class `UE::Geometry::FUniformTessellate`  
`class FUniformTessellate`  
_L40-155_
- L48 _public member_ `FProgressCancel* Progress = nullptr;` — Set this to be able to cancel running operation.
- L51 _public member_ `int TessellationNum = 0;` — Determines the number of triangles we generate.
- L54 _public member_ `bool bUseParallel = true;` — Should multi-threading be enabled.
- L57 _public member_ `bool bComputeMappings = false;` — If true, populate VertexMap, VertexEdgeMap, VertexTriangleMap.
- L64 _public member_ `FDynamicMesh3* ResultMesh = nullptr;` — The tessellated mesh.
- L74 _public member_ `TArray<int32> VertexMap;` — Map the vertex ID in the input mesh to the corresponding vertex ID in the output mesh. If the vertex ID is Invalid in the input mesh, then it is mapped to InvalidID.
- L80 _public member_ `TMap<int32, FIndex2i> VertexEdgeMap;` — Map the ID of the vertex inserted along the input mesh edge to the input mesh triangle IDs (t1,t2) that share that edge. If its a boundary edge then t2 is InvalidID.
- L83 _public member_ `TMap<int32, int32> VertexTriangleMap;` — Map the ID of the vertex inserted inside the input mesh triangle to the triangle's ID.
- L91 _protected member_ `const FDynamicMesh3* Mesh = nullptr;` — Points to either the input mesh to be used to generate the new tessellated mesh or will point to a copy of the mesh we are tessellating inplace.
- L97 _protected member_ `bool bInPlace = false;` — If true, the mesh to tessellate is contained in the ResultMesh and will be overwritten with the tessellation result.
- L105 _public function_ `FUniformTessellate(FDynamicMesh3* OutMesh) : ResultMesh(OutMesh), bInPlace(true)` — Tessellate the mesh inplace. If the tessellation fails or the user cancelled the operation, OutMesh will not be changed.
- L114 _public function_ `FUniformTessellate(const FDynamicMesh3* Mesh, FDynamicMesh3* OutMesh) : ResultMesh(OutMesh), Mesh(Mesh), bInPlace(false)` — Tessellate the mesh and write the result into another mesh. This will overwrite any data stored in the OutMesh.
- L120 _public prototype_ `virtual ~FUniformTessellate() = default;`
- L123 _public prototype_ `static int32 ExpectedNumVertices(const FDynamicMesh3& Mesh, const int32 TessellationNum);` — @return The number of vertices after the tessellation.
- L126 _public prototype_ `static int32 ExpectedNumTriangles(const FDynamicMesh3& Mesh, const int32 TessellationNum);` — @return The number of triangles after the tessellation.
- L131 _public function_ `virtual EOperationValidationResult Validate()` — @return EOperationValidationResult::Ok if we can apply operation, or error code if we cannot.
- L149 _public prototype_ `virtual bool Compute();` — Generate tessellated geometry. @return true if the algorithm succeeds, false if it failed or was cancelled by the user.
- L154 _protected prototype_ `virtual bool Cancelled();` — If this returns true, abort computation.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/WeldEdgeSequence.h` (Public)


#### class `UE::Geometry::FWeldEdgeSequence`  
`class FWeldEdgeSequence`  
_L25-114_
- L45 _public member_ `FDynamicMesh3* Mesh;` — Inputs/Outputs
- L46 _public member_ `FEdgeSpan EdgeSpanToDiscard;` — This data is junk once Weld() is called
- L47 _public member_ `FEdgeSpan EdgeSpanToKeep;` — This is the updated edge span which can be used once Weld() is called
- L50 _public member_ `bool bAllowIntermediateTriangleDeletion = false;` — Whether triangle deletion is allowed in order to merge edges which are connected by a different edge
- L54 _public member_ `bool bAllowFailedMerge = false;` — When true, failed calls to MergeEdges() will be handled by moving the edges without merging such that the final result appears to be welded but has invisible seam(s) instead of just failing.
- L57 _public member_ `double InterpolationT = 0;` — When vertices are welded, each kept vertex will be placed at Lerp(KeepPos, RemovePos, InterpolationT)
- L61 _public member_ `TArray<TPair<int, int>> UnmergedEdgePairsOut;` — This is populated with pairs of eids which were not able to be merged. Only valid when bAllowFailedMerge is true
- L64 _public function_ `FWeldEdgeSequence(FDynamicMesh3* Mesh, FEdgeSpan SpanDiscard, FEdgeSpan SpanKeep) : Mesh(Mesh) , EdgeSpanToDiscard(SpanDiscard) , EdgeSpanToKeep(SpanKeep)`
- L70 _public prototype_ `virtual ~FWeldEdgeSequence() = default;`
- L79 _public prototype_ `EWeldResult Weld();` — Alters the existing mesh by welding two edge sequences, preserving sequence A. Conditions the mesh by splitting edges and optionally deleting triangles. @return EWeldResult::OK on success
- L86 _public prototype_ `static EWeldResult SplitEdgesToEqualizeSpanLengths(FDynamicMesh3& Mesh, FEdgeSpan& Span1, FEdgeSpan& Span2);` — Helper that splits the edges in the shorter span until the spans have the same number of edges. Weld() will automatically do this, but this is public in case the user wants to equalize spans that get concatenated together before all being welded at once.
- L94 _protected prototype_ `EWeldResult CheckInput();` — Verifies validity of input edges by ensuring they are correctly-oriented boundary edges @return EWeldResult::OK on success
- L102 _protected prototype_ `EWeldResult SplitSmallerSpan();` — Splits largest edges of the span with fewest vertices so that both input spans have an equal number of vertices and edges after @return EWeldResult::OK on success
- L106 _protected prototype_ `EWeldResult CheckForAndCollapseSideTriangles();` — `UE_DEPRECATED(5.5, "Side triangles are handled appropriately in WeldEdgeSequence")`
- L113 _protected prototype_ `EWeldResult WeldEdgeSequence();` — Welds edge sequence together @return EWeldResult::OK on success

#### enum `UE::Geometry::FWeldEdgeSequence::EWeldResult`  
`enum class EWeldResult`  
_L28-39_
- L30 _public enumerator_ `Ok = 0`
- L32 _public enumerator_ `Failed_EdgesNotBoundaryEdges = 10` — Occurs when any edge in either input span isn't a boundary edge.
- L34 _public enumerator_ `Failed_CannotSplitEdge = 21` — Occurs when SplitEdge() fails, haven't encountered this and I'm not sure what would cause it
- L35 _public enumerator_ `Failed_TriangleDeletionDisabled = 22` — Occurs when bAllowIntermediateTriangleDeletion is false and edge spans are connected by an edge
- L36 _public enumerator_ `Failed_CannotDeleteTriangle = 23` — Occurs when bAllowIntermediateTriangleDeletion is true, edge spans are connected, but edge deletion fails
- L38 _public enumerator_ `Failed_Other = 100` — Catch all for general failure

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API DYNAMICMESH_API`
- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Operations/WrapMesh.h` (Public)


#### struct `UE::Geometry::FWrapMeshCorrespondence`  
`struct FWrapMeshCorrespondence`  
_L21-25_
- L23 _public member_ `int32 SourceVertexIndex = IndexConstants::InvalidID;`
- L24 _public member_ `int32 TargetVertexIndex = IndexConstants::InvalidID;`

#### class `UE::Geometry::FWrapMesh`  
`class FWrapMesh final`  
_L30-80_
- desc: Wrap a source mesh's topology to a target mesh's shape. Users can supply vertex correspondences for landmarks to aid the mesh wrap process.
- L34 _public prototype_ `explicit FWrapMesh(const FDynamicMesh3* InSourceMesh);`
- L36 _public prototype_ `~FWrapMesh();`
- L48 _public member_ `int32 MaxNumOuterIterations = 10;` — Mesh Wrap is calculated with an inner and outer loop. This is the maximum number of outer loops. Each outer loop increases the Projection Stiffness by ProjectionStiffnessMultiplier.
- L50 _public member_ `int32 NumInnerIterations = 10;` — Mesh Wrap is calculated with an inner and outer loop. This is the number of inner loops run before increasing the Projection Stiffness in the outer loop.
- L52 _public member_ `double ProjectionTolerance = 1e-4;` — Mesh Wrap will terminate early if the Projection tolerance is within this threshold.
- L55 _public member_ `bool bWeldSourceMesh = true;` — Weld source mesh vertices with matching positions during mesh wrap. Final WrappedMesh topology will match original Source Mesh, not the welded one. Without welding, dynamic meshes with duplicate vertices may split at the seams.
- L57 _public member_ `double SourceMeshWeldingThreshold = UE_THRESH_POINTS_ARE_SAME;` — Threshold for welding positions
- L59 _public member_ `double LaplacianStiffness = 1.;` — Weight of mesh wrap to retain Source Topology mesh features. Metric is defined by Laplacian Type.
- L61 _public member_ `double InitialProjectionStiffness = 0.1;` — Initial weight of mesh wrap to match projected Target Shape. Each outer loop will multiply this stiffness by ProjectionStiffnessMultiplier.
- L63 _public member_ `double ProjectionStiffnessMuliplier = 10.;` — Each outer loop will multiply InitialProjectionStiffness by this to improve Target Shape match.
- L65 _public member_ `double CorrespondenceStiffness = 0.1;` — Weight of mesh wrap to match Landmark correspondences.
- L67 _public member_ `ELaplacianType LaplacianType = ELaplacianType::AffineInvariant;` — Laplacian type.
- L69 _public prototype_ `void SetMesh(const FDynamicMesh3* InSourceMesh);`
- L71 _public prototype_ `void WrapToTargetShape(const FDynamicMesh3& TargetShape, const TArray<FWrapMeshCorrespondence>& SourceTargetVertexCorrespondences, FDynamicMesh3& WrappedMesh) const;`
- L74 _private prototype_ `void Initialize();`
- L76 _private member_ `const FDynamicMesh3* SourceMesh;`
- L79 _private member_ `TPimplPtr<FImpl> Impl;`

#### enum `UE::Geometry::FWrapMesh::ELaplacianType`  
`enum struct ELaplacianType : uint8`  
_L38-43_
- L40 _public enumerator_ `CotangentNoArea`
- L41 _public enumerator_ `CotangentAreaWeighted`
- L42 _public enumerator_ `AffineInvariant`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Parameterization/DynamicMeshUVEditor.h` (Public)


#### struct `UE::Geometry::FUVEditResult`  
`struct FUVEditResult`  
_L17-21_
- L19 _public member_ `TArray<int32> NewUVElements;`

#### class `UE::Geometry::FDynamicMeshUVEditor`  
`class FDynamicMeshUVEditor`  
_L27-376_
- desc: FDynamicMeshUVEditor implements various UV overlay editing operations.
- L31 _private member_ `FDynamicMesh3* Mesh = nullptr;` — The mesh we will be editing
- L33 _private member_ `FDynamicMeshUVOverlay* UVOverlay = nullptr;` — The UV Overlay we will be editing
- L35 _private member_ `int32 UVOverlayIndex = -1;` — The index of the UV Overlay we will be editing
- L43 _public prototype_ `explicit FDynamicMeshUVEditor(FDynamicMesh3* MeshIn, int32 UVLayerIndex, bool bCreateIfMissing);` — Construct UV Editor for a UV Overlay of the given Mesh. @param UVLayerIndex index of target UV layer @param bCreateIfMissing if true, target UV layers up to UVLayerIndex will be created if it is not there. Otherwise UVOverlay will be nullptr and class is incomplete.
- L48 _public prototype_ `explicit FDynamicMeshUVEditor(FDynamicMesh3* MeshIn, FDynamicMeshUVOverlay* UVOverlayIn);` — Construct UV Editor for a UV Overlay of the given Mesh.
- L51 _public function_ `FDynamicMesh3* GetMesh()`
- L52 _public function_ `const FDynamicMesh3* GetMesh() const`
- L54 _public function_ `FDynamicMeshUVOverlay* GetOverlay()`
- L55 _public function_ `const FDynamicMeshUVOverlay* GetOverlay() const`
- L60 _public prototype_ `void CreateUVLayer(int32 UVLayerIndex);` — Create specified UVLayer if it does not exist
- L65 _public prototype_ `int32 AddUVLayer();` — Append new UV layer to the end of the array, returning the newly added index, or -1 if at max layers already
- L70 _public prototype_ `void SwitchActiveLayer(int32 UVLayerIndex);` — Switch to new layer
- L75 _public prototype_ `int32 RemoveUVLayer();` — Remove active layer, setting active layer to highest, preceeding layer. Will not remove the final layer from the mesh. Returns the resulting active layer index.
- L80 _public prototype_ `void ResetUVs();` — Clear UVs for all triangles on active layer
- L85 _public prototype_ `void ResetUVs(const TArray<int32>& Triangles);` — Clear UVs for given triangles on active layer
- L90 _public prototype_ `bool CopyUVLayer(FDynamicMeshUVOverlay* FromUVOverlay);` — Copy UVs from another overlay
- L98 _public prototype_ `void SetToPerVertexUVs(TArray<int32>& VertexToUVOut, bool& bIsIdentityMapOut, FUVEditResult* Result = nullptr);` — Initialize UV topology to be one UV per vertex. UVs are initialized to (0,0) @param VertexToUVOut returned new overlay UV ID for each mesh Vertex ID (array size is mesh MaxVertexID) @param bIsIdentityMapOut returned as true if UV ID == Vertex ID for every vertex  (even if there are gaps)
- L104 _public prototype_ `void SetPerTriangleUVs(const TArray<int32>& Triangles, double ScaleFactor = 1.0, FUVEditResult* Result = nullptr);` — Create new UV island for each Triangle, by planar projection onto plane of Triangle. No transforms/etc are applied.
- L109 _public prototype_ `void SetPerTriangleUVs(double ScaleFactor = 1.0, FUVEditResult* Result = nullptr);` — Create new UV island for given Triangles, and set UVs by planar projection to ProjectionFrame. No transforms/etc are applied.
- L114 _public prototype_ `void TransformUVElements(const TArray<int32>& ElementIDs, TFunctionRef<FVector2f(const FVector2f&)> TransformFunc);` — Apply arbitrary transform to UV elements
- L120 _public prototype_ `void SetTriangleUVsFromProjection(const TArray<int32>& Triangles, const FFrame3d& ProjectionFrame, FUVEditResult* Result = nullptr);` — Create new UV island for given Triangles, and set UVs by planar projection to ProjectionFrame. No transforms/etc are applied.
- L127 _public prototype_ `void SetTriangleUVsFromPlanarProjection(const TArray<int32>& Triangles, TFunctionRef<FVector3d(const FVector3d&)> PointTransform, const FFrame3d& ProjectionFrame, const FVector2d& Dimensions, FUVEditResult* Result = nullptr);` — Create new UV island for given Triangles, and set UVs by planar projection to ProjectionFrame. PointTransform is applied to points before projectiong onto ProjectionFrame X/Y axes Projected U/V coordinates are divided by Dimensions.X/Y
- L152 _public prototype_ `bool SetTriangleUVsFromExpMap(const TArray<int32>& Triangles, const FExpMapOptions& Options = FExpMapOptions(), FUVEditResult* Result = nullptr);` — Create new UV island for given Triangles, and set UVs for that island using Discrete Exponential Map. ExpMap center-point is calculated by finding maximum (Dijkstra-approximated) geodesic distance from border of island. @warning computes a single ExpMap, so input triangle set must be connected, however this is not verified internally
- L160 _public prototype_ `bool SetTriangleUVsFromExpMap( const TArray<int32>& Triangles, TFunctionRef<FVector3d(const FVector3d&)> PointTransform, const FFrame3d& ProjectionFrame, const FVector2d& Dimensions, int32 NormalSmoothingRounds = 0, double NormalSmoothingAlpha = 0.5, double FrameNormalBlendWeight = 0, FUVEditResult* Result = nullptr);` — Create new UV island for given Triangles, and set UVs for that island using Discrete Exponential Map. ExpMap center-point is calculated by finding maximum (Dijkstra-approximated) geodesic distance from border of island. @warning computes a single ExpMap, so input triangle set must be connected, however this is not verified internally
- L175 _public prototype_ `bool SetTriangleUVsFromFreeBoundaryConformal(const TArray<int32>& Triangles, FUVEditResult* Result = nullptr);` — Create new UV island for given Triangles, and set UVs for that island using Discrete Natural Conformal Map (equivalent to Least-Squares Conformal Map) @warning computes a single parameterization, so input triangle set must be connected, however this is not verified internally
- L183 _public prototype_ `bool SetTriangleUVsFromFreeBoundaryConformal(const TArray<int32>& Triangles, bool bUseExistingUVTopology, FUVEditResult* Result = nullptr);` — Create new UV island for given Triangles, and set UVs for that island using Discrete Natural Conformal Map (equivalent to Least-Squares Conformal Map) @param Triangles list of triangles @param bUseExistingUVTopology if true, re-solve for existing UV set, rather than constructing per-vertex UVs from triangle set. Allows for solving w/ partial seams, interior cuts, etc. @warning computes a single parameterization, so input triangle set must be connected, however this is not verified internally
- L193 _public prototype_ `bool SetTriangleUVsFromFreeBoundaryConformal(const TArray<int32>& Triangles, const TSet<int32>& PinnedElementIDs, FUVEditResult* Result = nullptr);` — Create new UV island for given Triangles, and set UVs for that island using Discrete Natural Conformal Map (equivalent to Least-Squares Conformal Map). Using this overload implies that we're re-solving for existing UV set rather than constructing per-vertex UVs from triangle set, since pinned elements rely on existing values. @param Triangles list of triangles @param PinnedElementIDs Elements for which to use unmodified UV values. @warning computes a single parameterization, so input triangle set must be connected, however this is not verified internally
- L202 _public prototype_ `bool SetTriangleUVsFromFreeBoundarySpectralConformal(const TArray<int32>& Triangles, bool bUseExistingUVTopology, bool bPreserveIrregularity, FUVEditResult* Result = nullptr);` — Create new UV island for given Triangles, and set UVs for that island using Spectral Conformal Map. @param Triangles list of triangles @param bUseExistingUVTopology if true, re-solve for existing UV set, rather than constructing per-vertex UVs from triangle set. Allows for solving w/ partial seams, interior cuts, etc. @param bPreserveIrregularity if true, reduces distortion for meshes with triangles of vastly different sizes. @warning computes a single parameterization, so input triangle set must be connected, however this is not verified internally
- L208 _public prototype_ `void MakeSureUVsAreSet(const TSet<int32>& Triangles, FUVEditResult* Result = nullptr, TSet<int32>* ChangedTrianglesOut = nullptr);` — Initializes any uninitialized triangles in the set to per-vertex (0,0) UVs. Doesn't clear or modify any existing UVs, and only operates on the given set.
- L216 _public prototype_ `bool RemoveSeamsAtEdges(const TSet<int32>& EidsToRemoveAsSeams);` — Merge existing UV topology with a set of edges, removing seams at edges if they exist within the UV topology. @param EidsToRemoveAsSeams list of edges to remove seams from @return true on success
- L229 _public prototype_ `bool CreateSeamsAtEdges(const TSet<int32>& EidsToMakeIntoSeams, FUVEditResult* Result = nullptr);` — Cut existing UV topology with a set of edges. This allows for creating partial seams/darts, interior cuts, etc. Avoids creating bowties. In cases where an edge is not next to any present or future seams/borders, some adjacent edge will be picked to be made into a seam as well, since it's impossible to make the original into a seam otherwise. @param EidsToMakeIntoSeams list of edges to turn into seams @param Result if non-null, list of new UV elements created along the path will be stored here (not ordered) @return true on success
- L244 _public prototype_ `bool MakeIsland(const TSet<int32>& TidsToMakeIntoIsland, FUVEditResult* Result = nullptr, TSet<int32>* ChangedTrianglesOut = nullptr);` — Takes the currently selected triangles and makes a separate UV island out of them, i.e. any interior seams are removed, and seams are added around the boundary of the selection. If the selection is not connected in the mesh, islands will be created for each connected component of selected triangles. If some of the selected triangles have unset UVs, they will be initialized to per-vertex zero UVs for the purposes of creating an island. @param TidsToMakeIntoIsland Triangles in the mesh @param Result if non-null, list of new UV elements created for new seams, or to initialize UVs. @param ChangedTrianglesOut Optional output of triangles that had their UVs changed. Currently this is a conservative superset, so some might not have actually changed. Not cleared before use. @return true on success
- L252 _public prototype_ `void SetTriangleUVsFromBoxProjection(const TArray<int32>& Triangles, TFunctionRef<FVector3d(const FVector3d&)> PointTransform, const FFrame3d& BoxFrame, const FVector3d& BoxDimensions, int32 MinIslandTriCount = 2, FUVEditResult* Result = nullptr);` — Set UVs by box projection. Triangles will be grouped to "best" box face PointTransform is applied to points before projectiong onto ProjectionFrame X/Y axes Projected U/V coordinates are divided by Dimensions.X/Y @param MinIslandTriCount Any UV island with fewer triangles than this count will be merged into a neighbouring island
- L260 _public prototype_ `void SetTriangleUVsFromCylinderProjection(const TArray<int32>& Triangles, TFunctionRef<FVector3d(const FVector3d&)> PointTransform, const FFrame3d& CylFrame, const FVector3d& CylDimensions, float CylinderSplitAngle, FUVEditResult* Result = nullptr);` — Set UVs by cylinder projection. Triangles will be grouped to cylinder endcaps or side based on CylinderSplitAngle. PointTransform is applied to points before projectiong onto ProjectionFrame X/Y axes Projected U/V coordinates are divided by Dimensions.X/Y
- L287 _public prototype_ `void TransferTriangleUVsFromMeshViaDirectionProjection(TArrayView<const int32> Triangles, TFunctionRef<FVector3d(const FVector3d&)> TransformTargetToSourceSpacePosition, const FVector3d& ProjectionDirection, double ProjectionOffset, TFunctionRef<FVector3d(const FVector3d&)> TransformProjectionToSourceSpaceVector, const FDynamicMeshAABBTree3& SourceMeshSpatial, int32 SourceMeshUVChannel, const FTransferFromMeshViaProjectionSettings& Settings, FUVEditResult* Result = nullptr);` — Transfer UVs from a source mesh by projecting along the specified direction @param Triangles Triangles to update with new UVs @param TransformTargetToSourceSpacePosition Transform to take target mesh vertices to the space of the source mesh @param ProjectionDirection Direction to project, in local space of TargetMesh @param ProjectionOffset Distance to offset from TargetMesh vertices before projecting @param TransformProjectionToSourceSpaceVector Transform to take the ProjectionDirection to the source mesh space @param SourceMeshSpatial AABB Tree of source mesh @param SourceMeshUVChannel UV Channel to read from on source mesh @param Settings Projection settings @param Result If non-null, contains new UV elements IDs created on target mesh
- L299 _public prototype_ `bool ScaleUVAreaTo3DArea(const TArray<int32>& Triangles, bool bRecenterAtOrigin, float ScaleFactor = 1.0f);` — Compute the UV-space and 3D area of the given Triangles, and then scale the UV area to be equvalent to the 3D area. Scaling is around the center of the UV bounding box. @param bRecenterAtOrigin if true, UVs are translated after scaling such that the UV bounding box center is at (0,0) @param ScaleFactor Additional scale factor to multiply into resulting UVs
- L308 _public prototype_ `bool ScaleUVAreaToBoundingBox(const TArray<int32>& Triangles, const FAxisAlignedBox2f& BoundingBox, bool bPreserveAspectRatio, bool bRecenterAtBoundingBox);` — Scale UVs of the given triangles to fit within the provided provided bounding box. @param BoundingBox the 2D bounding box to constraint the requested UVs within. @param bPreserveAspectRatio if true, when scaling UVs, maintain original aspect ratio instead of fitting to box bounds @param bRecenterAtBoundingBox if true, UVs are translated such that their centroid is at the bounding box center
- L316 _public prototype_ `bool AutoOrientUVArea(const TArray<int32>& Triangles);` — Compute an oriented UV-space bounding box for the given Triangles, and then rotate the UVs such that the box is aligned with the X axis. The UV-space box is found by computing the 2D Convex Hull and then finding the hull edge that results in the minimal box.
- L322 _public prototype_ `bool QuickPack(int32 TargetTextureResolution = 512, float GutterSize = 1.0f);` — Pack UVs into unit rectangle
- L329 _public prototype_ `bool UDIMPack(int32 TargetTextureResolution = 512, float GutterSize = 1.0f, const FVector2i& UDIMCoordsIn = FVector2i(0,0), const TArray<int32>* Triangles = nullptr);` — Pack specific UVs triangles into the specific unit rectangle at the specified index @param UDIMCoordsIn Which unit rectangle tile should the UVs be packed in, indicated by the coordinate of it's lower left hand corner @param Triangles Which UV triangles to pack, all triangles if nullptr
- L340 _public prototype_ `static bool EstimateGeodesicCenterFrameVertex(const FDynamicMesh3& Mesh, FFrame3d& FrameOut, int32 &VertexIDOut, bool bAlignToUnitAxes = true);` — Compute geodesic center of given Mesh @return true if a central vertex was found (but if false, will still give a frame for *some* vertex as long as there is at least one vertex in the mesh)
- L346 _public prototype_ `static bool EstimateGeodesicCenterFrameVertex(const FDynamicMesh3& Mesh, const TArray<int32>& Triangles, FFrame3d& FrameOut, int32& VertexIDOut, bool bAlignToUnitAxes = true);` — Compute geodesic center of given Mesh triangles (assumes they are connected) @return true if a central vertex was found (but if false, will still give a frame for *some* vertex as long as there is at least one triangle)
- L352 _public prototype_ `static double DetermineAreaFromUVs(const FDynamicMeshUVOverlay& UVOverlay, const TArray<int32>& Triangles, FAxisAlignedBox2f* BoundingBox = nullptr);` — Compute the occupied 2D area for the UVs for the specified triangles and channel. @param BoundingBox if not null, return the overall bounding box of the UVs for the specified triangles along with the exact area occupied.
- L357 _public prototype_ `static void TransformTriangleSelectionUVs(FDynamicMeshUVOverlay& UVOverlay, TConstArrayView<int32> Triangles, TFunctionRef<FVector2f(const FVector2f&)> TransformFunc);` — Transform UVs of the specified triangles
- L372 _private prototype_ `bool SetTriangleUVsFromConformal(const TArray<int32>& Triangles, const FSetUVsFromConformalOptions& Options, FUVEditResult* Result);` — Helper method to solve either the Least Squares Conformal Map or the Spectral Conformal Map problems.
- L375 _private prototype_ `void SplitBowtiesOnUVElements(TArray<int32>& UVElementIDs, bool bAddNewElementsToInputArray = true);` — Helper to split bowties on element IDs

#### struct `UE::Geometry::FDynamicMeshUVEditor::FExpMapOptions`  
`struct FExpMapOptions`  
_L133-145_
- desc: FExpMapOptions provides additional control over ExpMap UV generation below
- L136 _public member_ `int32 NormalSmoothingRounds;` — Number of rounds of explicit uniform normal smoothing to apply to mesh normals
- L138 _public member_ `double NormalSmoothingAlpha;` — Alpha for smoothing, valid range is 0-1
- L140 _public function_ `FExpMapOptions()`

#### struct `UE::Geometry::FDynamicMeshUVEditor::FTransferFromMeshViaProjectionSettings`  
`struct FTransferFromMeshViaProjectionSettings`  
_L263-273_
- L266 _public member_ `float MinDistance = -FMathf::MaxReal, MaxDistance = FMathf::MaxReal;` — Range to search for source triangles
- L266 _public member_ `float MinDistance = -FMathf::MaxReal, MaxDistance = FMathf::MaxReal;` — Range to search for source triangles
- L269 _public member_ `bool bResetUVsForUnmatched = false;` — For triangles without matching source triangles, whether reset the UVs -- if false, they will be left as-is
- L272 _public member_ `TFunction<bool(int32)> SourceMeshTriFilter = nullptr;` — If a filter is provided, will only transfer UVs from triangles where the filter returns 'true'

#### struct `UE::Geometry::FDynamicMeshUVEditor::FSetUVsFromConformalOptions`  
`struct FSetUVsFromConformalOptions`  
_L361-368_
- L363 _public member_ `bool bUseExistingUVTopology = false;`
- L364 _public member_ `bool bUseSpectral = false;`
- L365 _public member_ `bool bPreserveIrregularity = false;`
- L367 _public member_ `const TSet<int32>* PinnedElementIDs = nullptr;` — currently only used if bUseSpectral is false

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Parameterization/MeshPlanarSymmetry.h` (Public)


#### class `UE::Geometry::FMeshPlanarSymmetry`  
`class FMeshPlanarSymmetry`  
_L27-183_
- desc: FMeshPlanarSymmetry detects pairwise symmetry relationships between vertices in a mesh, given a symmetry frame. Once those relationships are known, symmetry can be re-enforced after mesh edits. Vertices within a tolerance band of the symmetry plane do not have a mirror and are considered "on plane" and will be snapped to the symmetry plane when enforcing symmetry after edits. The Symmetry Plane is specified by a Frame3d where the XY axes define the plane and the Z axis is the plane normal. So references to "Positive" side below are relative to that Z axis/plane
- L32 _public member_ `bool bCanIgnoreDegenerateSymmetries = true;` — If true, symmetry-finding can return false if it detects a symmetry where all points are on the symmetry plane, rather than attempt to fit a symmetry plane in that case.
- L39 _public prototype_ `bool Initialize(FDynamicMesh3* Mesh, FDynamicMeshAABBTree3* Spatial, FFrame3d SymmetryFrameIn);` — Given a Mesh, an AABBTree, and a Symmetry Plane/Frame, detect any pairs of vertices with planar/mirror-symmetry relationships, as well as "on plane" vertices @return false if any non-on-plane vertex fails to find a match.
- L45 _public prototype_ `bool Initialize(FDynamicMesh3* Mesh, const FAxisAlignedBox3d& Bounds, FFrame3d SymmetryFrameIn);` — Given a Mesh and its bounding box, and a Symmetry Plane/Frame, detect any pairs of vertices with planar/mirror-symmetry relationships, as well as "on plane" vertices @return false if any non-on-plane vertex fails to find a match.
- L53 _public prototype_ `bool Initialize(FDynamicMesh3* Mesh, const FAxisAlignedBox3d& Bounds, FFrame3d SymmetryFrameIn, bool bForceComputeVertexPairs);` — Given a Mesh and its bounding box, and a Symmetry Plane/Frame, detect any pairs of vertices with planar/mirror-symmetry relationships, as well as "on plane" vertices @param bForceComputeVertexPairs Computes vertex pairs even if the mesh doesn't pass quick full symmetry test @return false if any non-on-plane vertex fails to find a match.
- L62 _public prototype_ `bool FindPlaneAndInitialize(FDynamicMesh3* Mesh, const FAxisAlignedBox3d& Bounds, FFrame3d& SymmetryFrameOut, TArrayView<const FVector3d> PreferredNormals = TArrayView<const FVector3d>());` — Given a Mesh and its bounding box, find a Symmetry Plane/Frame and detect any pairs of vertices with planar/mirror-symmetry relationships, as well as "on plane" vertices @param SymmetryFrameOut Returns the discovered symmetry frame by reference, if one was found. @param PreferredNormals Optionally try to find a symmetry frame aligned to any normals passed in to this array. Tries the normals in order, so the first normal that fits (if any) will be used. @return false if any non-on-plane vertex fails to find a match.
- L67 _public prototype_ `FVector3d GetMirroredPosition(const FVector3d& Position) const;` — @return the input Point mirrored across the Symmetry plane
- L72 _public prototype_ `FVector3d GetMirroredAxis(const FVector3d& Axis) const;` — @return the input Vector/Axis mirrored across the Symmetry plane
- L77 _public prototype_ `FQuaterniond GetMirroredOrientation(const FQuaterniond& Orientation) const;` — @return the input Quaternion mirrored across the Symmetry plane
- L82 _public prototype_ `FFrame3d GetPositiveSideFrame(FFrame3d FromFrame) const;` — @return the input Frame mirrored to the "positive" side (unchanged if it is already on the positive side)
- L89 _public prototype_ `void FullSymmetryUpdate();` — Update all the symmetry vertex positions based on their Positive-side pair vertex. Also snap all on-plane vertices to the symmetry plane
- L93 _public prototype_ `bool ValidateSymmetry(const FDynamicMesh3& TestMesh) const;` — @return true if the TestMesh vertices match the current tracked vertex symmetry correspondence (i.e., the TestMesh vertex IDs match the known correspondence, and have the expected mirror symmetry)
- L96 _public prototype_ `bool ValidateSymmetry(const FDynamicMesh3& TestMesh, TConstArrayView<int32> VertexROI) const;` — @return true if the TestMesh vertices in VertexROI match the current tracked vertex symmetry correspondence (i.e., the vertex IDs match the known correspondence, and have the expected mirror symmetry)
- L113 _public function_ `void GetMirrorVertexROI(const TArray<int>& VertexROI, TArray<int>& MirrorVertexROIOut, bool bForceSameSizeWithGaps, TFunctionRef<bool(int32 VID)> ShouldExcludeVertex = [](int32) {return false;}) const;` — Computes list of vertices that are mirror-constrained to vertices in VertexROI. If bForceSameSizeWithGaps is true, MirrorVertexROIOut will be the same size as VertexROI, and -1 is stored for vertices in VertexROI that are source vertices, or on the symmetry plane, or excluded by ShouldExcludeVertex(). Otherwise those vertices are skipped. @param ShouldExcludeVertex Optional filter to exclude vertices: takes vertex ID, returns true if the vertex should not be added to the ROI, false otherwise
- L113 _public prototype_ `void GetMirrorVertexROI(const TArray<int>& VertexROI, TArray<int>& MirrorVertexROIOut, bool bForceSameSizeWithGaps, TFunctionRef<bool(int32 VID)> ShouldExcludeVertex = [](int32) {return false;}) const;` — Computes list of vertices that are mirror-constrained to vertices in VertexROI. If bForceSameSizeWithGaps is true, MirrorVertexROIOut will be the same size as VertexROI, and -1 is stored for vertices in VertexROI that are source vertices, or on the symmetry plane, or excluded by ShouldExcludeVertex(). Otherwise those vertices are skipped. @param ShouldExcludeVertex Optional filter to exclude vertices: takes vertex ID, returns true if the vertex should not be added to the ROI, false otherwise
- L119 _public prototype_ `void ApplySymmetryPlaneConstraints(const TArray<int>& VertexIndices, TArray<FVector3d>& VertexPositionsInOut) const;` — For any vertices in VertexIndices that are on-plane, take the position in VertexPositionsInOut, apply the on-plane constraint, and return the constrained position in VertexPositionsInOut  (ie VertexPositionsInOut is updated to new positions)
- L127 _public prototype_ `void ComputeSymmetryConstrainedPositions( const TArray<int>& SourceVertexROI, const TArray<int>& MirrorVertexROI, const TArray<FVector3d>& SourceVertexPositions, TArray<FVector3d>& MirrorVertexPositionsOut) const;` — Given the pairing (SourceVertexROI, SourceVertexPositions), compute the symmetry-constrained vertex positions for MirrorVertexROI and store in MirrorVertexPositionsOut. This function assumes that the MirrorVertexROI was computed by calling GetMirrorVertexROI(SourceVertexROI, MirrorVertexROI, bForceSameSizeWithGaps=true), ie all the arrays must be the same length
- L135 _protected member_ `FDynamicMesh3* TargetMesh = nullptr;`
- L137 _protected member_ `FFrame3d SymmetryFrame;`
- L138 _protected member_ `FVector3d CachedSymmetryAxis;`
- L153 _protected member_ `TArray<FSymmetryVertex> Vertices;` — list of vertices, size == TargetMesh.MaxVertexID()
- L155 _protected prototype_ `void UpdateSourceVertex(int32 VertexID);`
- L156 _protected prototype_ `void UpdatePlaneVertex(int32 VertexID);`
- L161 _private prototype_ `bool AssignMatches(const FDynamicMesh3* Mesh, const TPointHashGrid3d<int32>& VertexHash, const TArray<FVector3d>& InvariantFeatures, FFrame3d SymmetryFrameIn);` — Helper for computing + assigning symmetry matches
- L162 _private prototype_ `void ComputeMeshInfo(const FDynamicMesh3* Mesh, const FAxisAlignedBox3d& Bounds, TArray<FVector3d>& InvariantFeaturesOut, FVector3d& MeshCentroidOut);`
- L163 _private prototype_ `bool Validate(const FDynamicMesh3* Mesh);`
- L172 _private member_ `constexpr static double OnPlaneToleranceFactor = (double)FMathf::ZeroTolerance * .5;` — Point must be within this distance from the symmetry plane to be considered "on" the plane. Note: Vertices can still be matched below this tolerance; this is just the distance at which a lack of match is considered a lack of symmetry Note: Each Tolerance Factor will be multiplied by "ErrorScale", so that it can appropriately scale up for larger inputs.  SetErrorScale() must be called before using these tolerances.
- L173 _private member_ `constexpr static double MatchVertexToleranceFactor = OnPlaneToleranceFactor * 2;`
- L175 _private member_ `constexpr static double VertexHashCellSizeFactor = MatchVertexToleranceFactor * 10;` — Note performance of vertex hashing is much better when VertexHashCellSize is large enough that most hash lookups only need to look at a single cell
- L177 _private member_ `constexpr static double MatchFeaturesTolerance = UE_DOUBLE_KINDA_SMALL_NUMBER;` — Note for features we specify a direct tolerance instead of a factor, as features are already in their own re-scaled space
- L179 _private member_ `double ErrorScale = 1;` — Internal error scale; for large meshes, we need larger tolerances because floating point values will be less accurate
- L181 _private prototype_ `void SetErrorScale(const FAxisAlignedBox3d& Bounds);`

#### struct `UE::Geometry::FMeshPlanarSymmetry::FSymmetryVertex`  
`struct FSymmetryVertex`  
_L140-150_
- L143 _public member_ `double PlaneSignedDistance = 0.0;` — initial distance to symmetry plane
- L145 _public member_ `bool bIsSourceVertex = true;` — true if this is a positive-side vertex
- L147 _public member_ `bool bOnPlane = false;` — true if this is an on-plane vertex (todo: possibly combine with bIsSourceVertex as an enum)
- L149 _public member_ `int32 PairedVertex = -1;` — VertexID of paired vertex

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DYNAMICMESH_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Parameterization/MeshRegionGraph.h` (Public)


#### class `UE::Geometry::FMeshRegionGraph`  
`class FMeshRegionGraph`  
_L28-160_
- desc: FMeshRegionGraph represents neighbourhood relationships between mesh patches. This is similar in some ways to a FGroupTopology, however only patch-adjacency connections are tracked. Connectivity between patches can be queried, and patches can be merged without rebuilding the graph. Each mesh Patch/Region is assigned an integer ID/RegionIndex. After removing or merging regions, some RegionIndex values may be invalid, use IsRegion() to check An integer ID can be associated with each Region using the ExternalIDFunc passed to the various Build() functions.
- L36 _public prototype_ `void BuildFromComponents(const FDynamicMesh3& Mesh, const FMeshConnectedComponents& Components, TFunctionRef<int32(int32)> ExternalIDFunc, TFunctionRef<bool(int32, int32)> TrisConnectedPredicate = [](int, int) { return true; } );` — Build a region graph for a Mesh using the given ConnectedComponents @param ExternalIDFunc This allows the client to provide an integer ID that will be associated with each Region - called with the region index in Components
- L39 _public function_ `void BuildFromComponents(const FDynamicMesh3& Mesh, const FMeshConnectedComponents& Components, TFunctionRef<int32(int32)> ExternalIDFunc, TFunctionRef<bool(int32, int32)> TrisConnectedPredicate = [](int, int) { return true; } );` — Build a region graph for a Mesh using the given ConnectedComponents @param ExternalIDFunc This allows the client to provide an integer ID that will be associated with each Region - called with the region index in Components
- L45 _public prototype_ `void BuildFromTriangleSets(const FDynamicMesh3& Mesh, const TArray<TArray<int32>>& TriangleSets, TFunctionRef<int32(int32)> ExternalIDFunc, TFunctionRef<bool(int32, int32)> TrisConnectedPredicate = [](int, int) { return true; });` — Build a region graph for a Mesh using the given triangle sets @param ExternalIDFunc This allows the client to provide an integer ID that will be associated with each Region - called with the region index in TriangleSets
- L48 _public function_ `void BuildFromTriangleSets(const FDynamicMesh3& Mesh, const TArray<TArray<int32>>& TriangleSets, TFunctionRef<int32(int32)> ExternalIDFunc, TFunctionRef<bool(int32, int32)> TrisConnectedPredicate = [](int, int) { return true; });` — Build a region graph for a Mesh using the given triangle sets @param ExternalIDFunc This allows the client to provide an integer ID that will be associated with each Region - called with the region index in TriangleSets
- L53 _public function_ `int32 MaxRegionIndex() const` — @return Max valid region index. Some region indices may be invalid.
- L58 _public function_ `int32 IsRegion(int32 RegionIdx) const` — @return true if the RegionIndex is valid
- L63 _public function_ `int32 GetExternalID(int32 RegionIdx) const` — @return the ExternalID for a Region, defined at Build time
- L68 _public function_ `int32 GetRegionTriCount(int32 RegionIdx) const` — @return the triangle count for a Region
- L73 _public function_ `const TArray<int32>& GetRegionTris(int32 RegionIdx) const` — @return list of triangles in a Region
- L78 _public prototype_ `TArray<int32> GetNeighbours(int32 RegionIdx) const;` — @return list of Neigbour Region Indices for a Region
- L83 _public prototype_ `bool AreRegionsConnected(int32 RegionAIndex, int32 RegionBIndex) const;` — @return true if the two regions are adjacent, ie they share an edge on at least one triangle
- L86 _public function_ `bool AreTrianglesConnected(int32 TriangleA, int32 TriangleB) const` — @return true if the two triangles are in the same region
- L96 _public prototype_ `bool MergeSmallRegions(int32 SmallThreshold, TFunctionRef<float(int32 SmallRgnIdx, int32 NbrRgnIdx)> RegionSimilarityFunc );` — Incrementally merge regions with a triangle count below the given SmallThreshold. A Small region is merged to it's most-similar neighbour, as defined by RegionSimilarityFunc. The merge order is sorted by largest Similarity, ie most-similar regions are merged first.
- L104 _public prototype_ `bool MergeRegion(int32 RemoveRgnIdx, int32 MergeToRgnIdx);` — Merge one existing Region into another @param RemoveRgnIdx this region will be removed @param MergeToRgnIdx this region will be added to
- L112 _public prototype_ `bool OptimizeBorders(int32 MaxRounds = 25);` — Optimize region borders by swapping triangles. The swap criteria is, if 2/3 of the neighbours of a given Triangle in region A are both in region B, swap it to region B. This swapping process is repeated in rounds, MaxRounds times. @return true if any swaps were applied
- L119 _public function_ `TArray<int32>&& MoveRegionTris(int32 RegionIdx)` — @return list of triangles in a Region @warning This method leaves the FMeshRegionGraph in an invalid state, and should only be used as a means to avoid memory copies while extracting the triangle sets from a FMeshRegionGraph that will then be discarded
- L144 _public member_ `TArray<FRegion> Regions;`
- L145 _public member_ `TArray<int32> TriangleToRegionMap;`
- L146 _public member_ `TArray<FIndex3i> TriangleNbrTris;`
- L148 _public member_ `TArray<int32> EmptyTriSet;`
- L151 _protected prototype_ `void BuildNeigbours(int32 RegionIdx);`
- L153 _protected prototype_ `bool MergeSmallRegionsPass(int32 SmallThreshold, TFunctionRef<float(int32 SmallRgnIdx, int32 NbrRgnIdx)> RegionSimilarityFunc);`
- L158 _private prototype_ `bool MergeRegionUnsafe(int32 RemoveRgnIdx, int32 MergeToRgnIdx);` — MergeRegion without validation, for internal use where we know the inputs are valid neighbors

#### struct `UE::Geometry::FMeshRegionGraph::FNeighbour`  
`struct FNeighbour`  
_L125-129_
- L127 _public member_ `int32 RegionIndex;`
- L128 _public member_ `int32 Count;`

#### struct `UE::Geometry::FMeshRegionGraph::FRegion`  
`struct FRegion`  
_L131-142_
- L133 _public member_ `bool bValid = true;`
- L135 _public member_ `int32 ExternalID;`
- L137 _public member_ `TArray<int32> Triangles;`
- L138 _public member_ `TArray<FNeighbour> Neighbours;`
- L140 _public member_ `bool bIsOnMeshBoundary = false;`
- L141 _public member_ `bool bIsOnROIBoundary = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Parameterization/MeshUDIMClassifier.h` (Public)


#### class `UE::Geometry::FDynamicMeshUDIMClassifier`  
`class FDynamicMeshUDIMClassifier`  
_L22-44_
- desc: FDynamicMeshUDIMClassifier is a utility class for identifying active UDIMs from a FDynamicMesh's UV overlay
- L25 _public prototype_ `explicit FDynamicMeshUDIMClassifier(const FDynamicMeshUVOverlay* UVOverlay, TOptional<TArray<int32>> Selection = TOptional<TArray<int32>>());`
- L27 _public prototype_ `TArray<FVector2i> ActiveTiles() const;`
- L28 _public prototype_ `TArray<int32> TidsForTile(FVector2i TileIndexIn) const;`
- L30 _public prototype_ `static FVector2i ClassifyTrianglesToUDIM(const FDynamicMeshUVOverlay* UVOverlay, TArray<int32> Tids);`
- L31 _public prototype_ `static FVector2i ClassifyBoundingBoxToUDIM(const FDynamicMeshUVOverlay* UVOverlay, const FAxisAlignedBox2d& BoundingBox);`
- L32 _public prototype_ `static FVector2i ClassifyPointToUDIM(const FVector2f& UVPoint);`
- L36 _protected prototype_ `void ClassifyUDIMs();`
- L39 _protected member_ `const FDynamicMeshUVOverlay* UVOverlay = nullptr;` — The UV Overlay to analyze for UDIMs
- L41 _protected member_ `TOptional<TArray<int32>> Selection;`
- L43 _protected member_ `TMap<FVector2i, TArray<int32> > UDIMs;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Parameterization/MeshUVPacking.h` (Public)


#### class `UE::Geometry::FDynamicMeshUVPacker`  
`class FDynamicMeshUVPacker`  
_L24-74_
- desc: FDynamicMeshUVPacker implements various strategies for packing UV islands in a UV Overlay. The island topology and UV unwraps must already be created, this class simply scales/rotates/translates the islands to fit.
- L28 _public member_ `FDynamicMeshUVOverlay* UVOverlay = nullptr;` — The UV Overlay we will be repacking
- L31 _public member_ `TUniquePtr<TArray<int32>> TidsToRepack;` — The explicit triangle ids to repack, repack all triangles if null
- L34 _public member_ `int32 TextureResolution = 512;` — Resolution of the target texture. This is used to convert pixel gutter/border thickness to UV space
- L37 _public member_ `float GutterSize = 1.0;` — Thickness of gutter/border in pixel dimensions. Not supported by all packing methods
- L40 _public member_ `bool bPreserveScale = false;` — If true, original island scale is maintained during any packing process.
- L43 _public member_ `bool bPreserveRotation = false;` — If true, original island rotation is maintained during any packing process. Automatically prevents bAllowFlips from applying, if set.
- L46 _public member_ `bool bAllowFlips = false;` — If true, islands can be flipped in addition to rotate/translate/scale
- L49 _public member_ `bool bScaleIslandsByWorldSpaceTexelRatio = false;` — Attempt to rescale islands to match texel-to-world-space ratio across islands, based on ratio of World- and UV-space edge lengths
- L51 _public prototype_ `explicit FDynamicMeshUVPacker(FDynamicMeshUVOverlay* UVOverlay);`
- L52 _public prototype_ `explicit FDynamicMeshUVPacker(FDynamicMeshUVOverlay* UVOverlay, TUniquePtr<TArray<int32>>&& TidsToRepackIn);`
- L60 _public prototype_ `bool StandardPack();` — Standard UnrealEngine UV layout, similar to that used for Lightmap UVs. All UV islands are packed into standard positive-unit-square. Only supports single-pixel border size.
- L67 _public prototype_ `bool StackPack();` — Uniformly scale all UV islands so that the largest fits in positive-unit-square, and translate each islands separately so that it's bbox-min is at the origin. So the islands are "stacked" and all fit in the unit box.
- L72 _protected prototype_ `FMeshConnectedComponents CollectUVIslandsToPack(const FUVOverlayView& MeshView);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Parameterization/MeshUVTransforms.h` (Public)


#### enum `UE::MeshUVTransforms::EIslandPositionType`  
`enum class EIslandPositionType`  
_L19-24_
- L21 _public enumerator_ `CurrentPosition`
- L22 _public enumerator_ `MinBoxCornerToOrigin`
- L23 _public enumerator_ `CenterToOrigin`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshUVTransforms` (scope `UE`)
- L30 _prototype_ `void RecenterScale(FDynamicMeshUVOverlay* UVOverlay, const TArray<int32>& UVElementIDs, EIslandPositionType NewPosition, double UVScale);` (scope `UE::MeshUVTransforms`) — Recenter given UV element IDs using given IslandPositionType strategy (based on centroid, bounding-box, etc) and then apply uniform scaling
- L37 _prototype_ `void FitToBox(FDynamicMeshUVOverlay* UVOverlay, const TArray<int32>& UVElementIDs, const FAxisAlignedBox2d& Box, bool bUniformScale = true);` (scope `UE::MeshUVTransforms`) — Fit given UV element IDs inside the specified Box. @param bUniformScale if false, UVs will be non-uniformly scaled to maximally fill the box
- L43 _prototype_ `void FitToBox(FDynamicMeshUVOverlay* UVOverlay, const FAxisAlignedBox2d& Box, bool bUniformScale = true);` (scope `UE::MeshUVTransforms`) — Fit all UV element IDs of the UV Overlay inside the specified Box. @param bUniformScale if false, UVs will be non-uniformly scaled to maximally fill the box
- L50 _prototype_ `void MakeSeamsDisjoint(FDynamicMeshUVOverlay* UVOverlay);` (scope `UE::MeshUVTransforms`) — For all UV seam elements, apply a small displacement so that they have unique positions. This allows unwelding/re-welding the UVs without breaking the seams (which is horrible but necessary in some cases)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Parameterization/PatchBasedMeshUVGenerator.h` (Public)


#### class `UE::Geometry::FPatchBasedMeshUVGenerator`  
`class FPatchBasedMeshUVGenerator`  
_L26-134_
- desc: FPatchBasedMeshUVGenerator is an automatic UV generator for a triangle mesh that, generally, works by first decomposing the mesh into small patches for which a "known good" parameterization can be computed, and then incrementally merging those patches into larger ones to create final UV islands. The various steps of the generator can be called independently, eg if one already has a patch decomposition, then the initial steps can be skipped
- L35 _public member_ `FPolygroupSet* GroupConstraint = nullptr;` — If this is set, then the output patches will respect the borders of the input polygroups, eg as if they were disconnected components. Must be a PolygroupSet for the TargetMesh passed to functions below
- L41 _public member_ `int32 TargetPatchCount = 100;` — Parameters for patch generation (ComputeInitialMeshPatches)
- L42 _public member_ `bool bNormalWeightedPatches = true;`
- L43 _public member_ `double PatchNormalWeight = 1.0;`
- L44 _public member_ `int32 MinPatchSize = 2;`
- L49 _public member_ `double MergingThreshold = 1.5;` — Parameters for island merging (ComputeIslandsByRegionMerging)
- L50 _public member_ `double CompactnessThreshold = 9999999.0;` — effectively disabled as it usually is not a good idea
- L51 _public member_ `double MaxNormalDeviationDeg = 45.0;`
- L56 _public member_ `int32 NormalSmoothingRounds = 0;` — ExpMap parameters (ComputeUVsFromTriangleSets)
- L57 _public member_ `double NormalSmoothingAlpha = 0.25;`
- L62 _public member_ `bool bAutoAlignPatches = true;` — Packing parameters (used in AutoComputeUVs)
- L63 _public member_ `bool bAutoPack = true;`
- L64 _public member_ `int32 PackingTextureResolution = 512;`
- L65 _public member_ `float PackingGutterWidth = 1.0f;`
- L73 _public prototype_ `FGeometryResult AutoComputeUVs( FDynamicMesh3& TargetMesh, FDynamicMeshUVOverlay& TargetUVOverlay, FProgressCancel* Progress = nullptr);` — Top-level driver function, automatically computes UVs on the given TargetMesh and stores in the given TargetUVOverlay, using the steps below, based on the parameters above @return result information, which may include warnings/etc
- L83 _public prototype_ `bool ComputeInitialMeshPatches( FDynamicMesh3& TargetMesh, FMeshConnectedComponents& InitialComponentsOut, FProgressCancel* Progress = nullptr);` — Compute a decomposition of TargetMesh into many small patches (driven by TargetPatchCount). @param InitialComponentsOut returned decomposition into triangle sets @return true on success
- L97 _public prototype_ `bool ComputeIslandsByRegionMerging( FDynamicMesh3& TargetMesh, FDynamicMeshUVOverlay& TargetUVOverlay, const FMeshConnectedComponents& InitialComponents, TArray<TArray<int32>>& IslandsOut, FProgressCancel* Progress = nullptr);` — Incrementally combine existing mesh patches into larger patches that meet the various criteria defined by the parameters above. Note: This overload always outputs all islands (i.e., equivalent to calling the other overload with bOnlyOutputMergedRegions=false) @param InitialComponents the initial mesh patches, ie triangle lists @param IslandsOut the set of output mesh patches / triangle lists @return false if catastrophic failure ocurred (ie IslandsOut is invalid) or if Progress was cancelled
- L113 _public prototype_ `bool ComputeIslandsByRegionMerging( FDynamicMesh3& TargetMesh, FDynamicMeshUVOverlay& TargetUVOverlay, const FMeshConnectedComponents& InitialComponents, bool bOnlyOutputMergedRegions, TArray<TArray<int32>>& IslandsOut, FProgressCancel* Progress = nullptr);` — Incrementally combine existing mesh patches into larger patches that meet the various criteria defined by the parameters above @param InitialComponents the initial mesh patches, ie triangle lists @param bOnlyOutputMergedRegions whether to restrict IslandsOut to just the regions where components were merged, skipping unchanged islands @param IslandsOut the set of output mesh patches / triangle lists @return false if catastrophic failure ocurred (ie IslandsOut is invalid) or if Progress was cancelled
- L127 _public prototype_ `int32 ComputeUVsFromTriangleSets( FDynamicMesh3& TargetMesh, FDynamicMeshUVOverlay& TargetUVOverlay, const TArray<TArray<int32>>& TriangleSets, TArray<bool>& bValidUVsComputedOut, FProgressCancel* Progress = nullptr );` — Calculate UVs for the input mesh patches of TargetMesh and store in TargetUVOVerlay @param TriangleSets the set of desired UV islands, defined as triangle lists @param bValidUVsComputedOut output list of booleans the same length as TriangleSets, set to false if UV computation failed for that island @return number of failed UV islands, 0 if all were successful, and -1 if Progress was cancelled

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Parameterization/UVTransfer.h` (Public)


#### class `UE::Geometry::FDynamicMeshUVTransfer`  
`class FDynamicMeshUVTransfer`  
_L22-92_
- desc: Transfers UVs from a low-resolution mesh to a high-resolution mesh. The source mesh is expected to be a simplified version of the destination mesh, simplified using existing vertices only. Thus, correspondences are found by position.
- L25 _public function_ `FDynamicMeshUVTransfer(const FDynamicMesh3* SourceMeshIn, FDynamicMesh3* DestinationMeshIn, int32 UVLayerIndexIn) : FDynamicMeshUVTransfer(SourceMeshIn, DestinationMeshIn, UVLayerIndexIn, UVLayerIndexIn)`
- L30 _public prototype_ `FDynamicMeshUVTransfer(const FDynamicMesh3* SourceMeshIn, FDynamicMesh3* DestinationMeshIn, int32 SourceUVLayerIndex, int32 DestUVLayerIndex);`
- L33 _public member_ `const FDynamicMesh3* SourceMesh = nullptr;`
- L34 _public member_ `FDynamicMesh3* DestinationMesh = nullptr;`
- L35 _public member_ `int UVLayerIndex = 0;` — source UV layer index
- L36 _public member_ `int DestUVLayerIndex = 0;`
- L39 _public member_ `double VertexSearchDistance = KINDA_SMALL_NUMBER;` — How far to search for a matching vertex on the destination mesh.
- L41 _public member_ `double VertexSearchCellSize = VertexSearchDistance * 3.0;` — Cell size used in hash grid when finding correspndence (only affects performance)
- L50 _public member_ `double PathSimilarityWeight = 200.0;` — Tuning parameter to make found destination paths follow source edges closer. The higher the value, the more the path similarity metric gets weighed relative to simple euclidean length of the path, which helps select a zigzagging path that follows the edge closer over an "up and over" path that might have slightly shorter length (particularly relevant on against-the-grain diagonals in a gridded region, where path lengths are manhattan distance-like).
- L55 _public member_ `bool bClearExistingSeamsInDestination = true;` — If true, existing seams in the destination are removed before adding new ones.
- L57 _public prototype_ `bool TransferSeams(FProgressCancel* Progress);`
- L58 _public prototype_ `bool TransferSeamsAndUVs(FProgressCancel* Progress);`
- L63 _private member_ `TSet<int32>* SourceSelectionTids = nullptr;` — TODO: Expose and test selection-constrained transfers when support for selecting elements on multiple meshes is available. Selection should be settable on either mesh (it is not necessary to set both).
- L64 _private member_ `TSet<int32>* DestinationSelectionTids = nullptr;`
- L66 _private prototype_ `void InitializeHashGrid();`
- L68 _private prototype_ `int32 GetCorrespondingDestVid(int32 SourceVid);` — Should only be called after InitializeHashGrid
- L70 _private prototype_ `void ResetDestinationUVTopology(FProgressCancel* Progress);`
- L71 _private prototype_ `bool PerformSeamTransfer(FProgressCancel* Progress);`
- L74 _private prototype_ `bool PerformElementsTransfer(FProgressCancel* Progress);` — Expects PerformSeamTransfer to have been called so that seams are transferred, and SourceEidToDestinationEndpointEidsVids and SourceBoundaryElements are initialized
- L76 _private member_ `const FDynamicMeshUVOverlay* SourceOverlay = nullptr;`
- L77 _private member_ `FDynamicMeshUVOverlay* DestOverlay = nullptr;`
- L80 _private member_ `TUniquePtr<TPointHashGrid3<int32, double>> HashGrid;` — Used for getting a correspondence between low res mesh and high res mesh
- L81 _private member_ `TMap<int32, int32> SourceVidToDestinationVid;`
- L83 _private member_ `TMap<int32, TPair<FIndex2i, FIndex2i>> SourceEidToDestinationEndpointEidsVids;`
- L84 _private member_ `TSet<int32> SourceBoundaryElements;`
- L89 _private member_ `double PathLengthToleranceMultiplier = 4.0;` — This gets multiplied by (SourceEdgeLength + PathSimilarityWeight * PathSimilarityMetric) to limit the max search distance when looking for corresponding paths. This is speculative, to avoid looking for inexistent paths on very dense meshes on incorrect inputs.
- L91 _private member_ `double MinimalPathSearchDistance = 20.0;` — Minimal max distance to use in looking for corresponding paths, in case the source edge is near-degenerate.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Parameterization/UVUnwrapMeshUtil.h` (Public)


#### Free symbols / members of external scopes

- L12 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L14 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L16 _namespace_ `namespace UVUnwrapMeshUtil` (scope `UE::Geometry`)
- L24 _prototype_ `void GenerateUVUnwrapMesh(const FDynamicMeshUVOverlay& UVOverlay, FDynamicMesh3& UnwrapMeshOut, TFunctionRef<FVector3d(const FVector2f&)> UVToVertPosition);` (scope `UE::Geometry::UVUnwrapMeshUtil`) — Given a UV overlay, generate a mesh out of the overlay using the given UV to 3d position function. The resulting mesh's vertex IDs will match the overlay element IDs, and the triangle IDs will match the overlay triangle IDs. The mesh will have a UV overlay of its own that will match the source overlay except for the parent verts.
- L35 _prototype_ `void UpdateUVUnwrapMesh(const FDynamicMeshUVOverlay& UVOverlayIn, FDynamicMesh3& UnwrapMeshOut, TFunctionRef<FVector3d(const FVector2f&)> UVToVertPosition, const TArray<int32>* ChangedElementIDs = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr);` (scope `UE::Geometry::UVUnwrapMeshUtil`) — Given a mesh that corresponds to an overlay with an exact mapping of triangle IDs and element IDs to vertex IDs (i.e. one generated by GenerateUVUnwrapMesh), update the vertex locations and triangle connectivity of the mesh. @param ChangedElementIDs If not null, only update vertex locations corresponding to the given elements. @param ChangedConnectivityTids If not null, only update triangle connectivity corresponding to the given triangle IDs.
- L46 _prototype_ `void UpdateUVUnwrapMesh(const FDynamicMesh3& SourceUnwrapMesh, FDynamicMesh3& DestUnwrapMesh, const TArray<int32>* ChangedVids = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr);` (scope `UE::Geometry::UVUnwrapMeshUtil`) — Given a copy of a UV Unwrap mesh whose positions and connectivity have been updated, update the destination unwrap mesh. Note that SourceUnwrapMesh is expected to have its overlay already updated. @param ChangedVids If not null, only update elements corresponding to the given vertex IDs. @param ChangedConnectivityTids If not null, only update triangle connectivity corresponding to the given triangle IDs.
- L57 _prototype_ `void UpdateUVOverlayFromUnwrapMesh( const FDynamicMesh3& UnwrapMeshIn, FDynamicMeshUVOverlay& UVOverlayOut, TFunctionRef<FVector2f(const FVector3d&)> VertPositionToUV, const TArray<int32>* ChangedVids = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr);` (scope `UE::Geometry::UVUnwrapMeshUtil`) — Given a mesh that corresponds to an overlay with an exact mapping of triangle IDs and element IDs to vertex IDs (i.e. one generated by GenerateUVUnwrapMesh), update the element values and connectivity of the overlay. @param ChangedVids If not null, only update elements corresponding to the given vertex IDs. @param ChangedConnectivityTids If not null, only update triangle connectivity corresponding to the given triangle IDs.
- L72 _prototype_ `void UpdateOverlayFromOverlay(const FDynamicMeshUVOverlay& OverlayIn, FDynamicMeshUVOverlay& OverlayOut, bool bParentVertsIdentical, const TArray<int32>* ChangedElements = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr);` (scope `UE::Geometry::UVUnwrapMeshUtil`) — Given two overlays that have the same triangle IDs, copy all or part of one overlay into another. @param bSameParentVerts If true, underlying meshes have same connectivity/id's, meaning that overlays have same parent verts, and we can use a simple copy when updating everything. Can be set true when copying between a canonical/preview version of the same mesh, but must be false when copying between an unwrap mesh and an applied mesh. @param ChangedVids If not null, only update elements corresponding to the given vertex IDs. @param ChangedConnectivityTids If not null, only update triangle connectivity corresponding to the given triangle IDs.
- L86 _prototype_ `template <EValidityCheckFailMode FailMode = EValidityCheckFailMode::ReturnOnly> bool DoesUnwrapMatchOverlay(const FDynamicMeshUVOverlay& OverlayIn, const FDynamicMesh3& UnwrapMeshIn, TFunctionRef<FVector3d(const FVector2f&)> UVToVertPosition, double Tolerance = 0);` (scope `UE::Geometry::UVUnwrapMeshUtil`) — Checks that the vertices in the unwrap correspond to elements in the overlay in both ID and value, and that set triangles in the overlay correspond to triangles in the unwrap. The fail mode is a template parameter so that we can do compile time branching. The function will return on the first mismatch it finds. @param Tolerance Used in comparing the expected unwrap position to the actual unwrap position for an element/vertex

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Polygroups/GroupSetAdapter.h` (Public)


#### class `UE::Geometry::ITriangleGroupSetAdapter`  
`class UE_INTERNAL ITriangleGroupSetAdapter`  
_L23-44_
- L27 _public prototype_ `virtual ~ITriangleGroupSetAdapter() = 0;` — Default Destructor
- L29 _public prototype_ `const FDynamicMesh3* GetMesh() const;` — @return Mesh this GroupSetAdapter references.
- L31 _public prototype_ `virtual int32 GetGroup(const int32 TriangleID) const = 0;` — @return Group ID for a TriangleID
- L33 _public prototype_ `virtual void SetGroup(const int32 TriangleID, const int32 GroupID, FDynamicMesh3& WritableMesh) = 0;` — Set the Group ID for a TriangleID
- L35 _public prototype_ `int32 GetMaxGroupID() const;`
- L39 _protected prototype_ `ITriangleGroupSetAdapter(const FDynamicMesh3* InMesh);` — Initialize a GroupSetAdapter for the given Mesh.
- L41 _protected member_ `const FDynamicMesh3* Mesh = nullptr;` — The mesh this GroupSetAdapter references.
- L43 _protected member_ `int32 MaxGroupID = 0;` — Max Group ID.

#### class `UE::Geometry::FPolygroupLayerAdapter`  
`class UE_INTERNAL FPolygroupLayerAdapter: public ITriangleGroupSetAdapter`  
_L49-66_
- inherits: `ITriangleGroupSetAdapter`
- desc: FPolygroupLayerAdapter provides an interface to Get/Set group IDs per triangle using a FDynamicMeshPolygroupAttribute as the actual data storage.
- L53 _public prototype_ `FPolygroupLayerAdapter(const FDynamicMesh3* InMesh, const FDynamicMeshPolygroupAttribute* Attribute);` — Initialize a FPolygroupLayerAdapter for given Mesh and specific Polygroup attribute layer.
- L55 _public prototype_ `virtual int32 GetGroup(const int32 TriangleID) const override;` — @return Group ID for a TriangleID.
- L57 _public prototype_ `virtual void SetGroup(const int32 TriangleID, const int32 NewGroupID, FDynamicMesh3& WritableMesh) override;` — Set the Group ID for a TriangleID.
- L61 _protected member_ `FPolygroupSet PolygroupSet;` — the PolygroupAttribute this GroupSetAdapter references.
- L63 _protected prototype_ `int32 GetLayerIndex() const;` — @return index of current PolygroupAttribute into Mesh AttributeSet, or -1 if this information does not exist.
- L65 _protected member_ `int32 GroupLayerIndex = -1;` — Default layer index.

#### class `UE::Geometry::FTriangleReadOnlyAttributeAdapter`  
`template<typename AttribValueType> class UE_INTERNAL FTriangleReadOnlyAttributeAdapter: public ITriangleGroupSetAdapter`  
_L73-130_
- inherits: `ITriangleGroupSetAdapter`
- desc: FTriangleReadOnlyAttributeAdapter provides a read-only typed interface to Get group IDs per triangle (as typed values instead on integers) using a TDynamicMeshSingleTriangleAttribute as the actual data storage and ensuring a group ID - AttribValueType value mapping.
- L76 _public typedef_ `using TriangleAttributeType = TDynamicMeshSingleTriangleAttribute<AttribValueType>;`
- L77 _public typedef_ `using ValueType = AttribValueType;`
- L80 _public function_ `FTriangleReadOnlyAttributeAdapter(const FDynamicMesh3* InMesh, const TriangleAttributeType* InAttribute) : ITriangleGroupSetAdapter(InMesh) , TriangleAttribute(InAttribute)` — Initialize a FTriangleReadOnlyAttributeAdapter for given Mesh and specific triangle attribute.
- L104 _public function_ `virtual int32 GetGroup(const int32 TriangleID) const override` — @return Group ID for a TriangleID or INDEX_NONE if there's no value mapped to that Group ID.
- L112 _public function_ `virtual void SetGroup(const int32 TriangleID, const int32 GroupID, FDynamicMesh3& WritableMesh) override` — Do not update any group id.
- L117 _protected function_ `bool CheckValidity() const` — @return true if this adapter is valid for use.
- L125 _protected member_ `const TriangleAttributeType* TriangleAttribute = nullptr;` — the per-triangle attribute this adapter references.
- L127 _protected member_ `TMap<ValueType, int32> ValueToID;` — Value-Group ID mapping.
- L129 _protected member_ `TMap<int32, ValueType> IDToValue;` — Group ID-Value mapping.

#### class `UE::Geometry::FTriangleAttributeAdapter`  
`template<typename AttribValueType> class UE_INTERNAL FTriangleAttributeAdapter: public ITriangleGroupSetAdapter`  
_L137-286_
- inherits: `ITriangleGroupSetAdapter`
- desc: FTriangleAttributeAdapter provides a typed interface to Get/Set group IDs per triangle (as typed values instead on integers) using a TDynamicMeshSingleTriangleAttribute as the actual data storage and ensuring a group ID - AttribValueType value mapping.
- L140 _public typedef_ `using TriangleAttributeType = TDynamicMeshSingleTriangleAttribute<AttribValueType>;`
- L141 _public typedef_ `using ValueType = AttribValueType;`
- L144 _public function_ `FTriangleAttributeAdapter(const FDynamicMesh3* InMesh, TriangleAttributeType* InAttribute) : ITriangleGroupSetAdapter(InMesh) , TriangleAttribute(InAttribute)` — Initialize a FTriangleAttributeAdapter for given Mesh and specific triangle attribute.
- L167 _public function_ `FTriangleAttributeAdapter(const FTriangleAttributeAdapter* InCopy) : ITriangleGroupSetAdapter(InCopy->Mesh) , TriangleAttribute(InCopy->TriangleAttribute) , ValueToID(InCopy->ValueToID) , IDToValue(InCopy->IDToValue)`
- L177 _public function_ `void SetGroup(const int32 TriangleID, const int32 GroupID)` — Set the Group ID for a TriangleID and updates the value-id mappings.
- L196 _public function_ `virtual void SetGroup(const int32 TriangleID, const int32 GroupID, FDynamicMesh3& InMesh) override` — Set the Group ID for a TriangleID and updates the value-id mappings. InMesh can be used to perform additional tests.
- L202 _public function_ `virtual int32 GetGroup(const int32 TriangleID) const override` — @return Group ID for a TriangleID or INDEX_NONE if there's no value mapped to that Group ID.
- L213 _public function_ `int32 GetGroupFromValue(const ValueType Value)` — @return Group ID from a Value. If the value is not yet registered, a new group ID is added and the mapping created.
- L229 _public function_ `ValueType GetValueFromGroup(const int32 GroupID)` — @return Value from a Group ID. If the group ID is not yet registered, a new value is added and the mapping is created.
- L245 _public function_ `ValueType GetValue(const int32 TriangleID) const` — @return Value for a TriangleID.
- L251 _public function_ `void SetValue(const int32 TriangleID, ValueType NewValue)` — Set the Value for a TriangleID and register mapping if needed.
- L266 _protected function_ `virtual ValueType GetUniqueValue() const` — @return New unique value.
- L273 _protected function_ `bool CheckValidity() const` — @return true if this adapter is valid for use.
- L281 _protected member_ `TriangleAttributeType* TriangleAttribute = nullptr;` — the per-triangle attribute this adapter references.
- L283 _protected member_ `TMap<ValueType, int32> ValueToID;` — Value-Group ID mapping.
- L285 _protected member_ `TMap<int32, ValueType> IDToValue;` — Group ID-Value mapping.

#### class `UE::Geometry::FTriangleLabelAdapter`  
`class UE_INTERNAL FTriangleLabelAdapter: public FTriangleAttributeAdapter<FName>`  
_L292-305_
- inherits: `FTriangleAttributeAdapter<FName>`
- desc: FTriangleLabelAdapter provides a FTriangleAttributeAdapter interface specialized for FName. The actual attribute that this adapter references must be contained in FDynamicMeshAttributeSet::TriangleLabelAttributes. (this is actually checked in the constructor).
- L295 _public prototype_ `FTriangleLabelAdapter(const FDynamicMesh3* InMesh, TriangleAttributeType* InAttribute, const FName InBaseLabel = "lab`
- L296 _public prototype_ `FTriangleLabelAdapter(const FTriangleLabelAdapter* InCopy);`
- L297 _public prototype_ `FName GetLayerName() const;`
- L300 _protected member_ `FName LayerName = NAME_None;`
- L302 _protected prototype_ `virtual FName GetUniqueValue() const override;` — @return New unique FName.
- L304 _protected member_ `FName BaseLabel = "la` — Base name used for unique FName generation.

#### class `UE::Geometry::FTriangleReadOnlyLabelAdapter`  
`class UE_INTERNAL FTriangleReadOnlyLabelAdapter: public FTriangleReadOnlyAttributeAdapter<FName>`  
_L310-314_
- inherits: `FTriangleReadOnlyAttributeAdapter<FName>`
- desc: FTriangleReadOnlyLabelAdapter provides a read-only FTriangleAttributeAdapter interface specialized for FName.
- L313 _public prototype_ `FTriangleReadOnlyLabelAdapter(const FDynamicMesh3* InMesh, const TriangleAttributeType* InAttribute);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L12 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Polygroups/PolygroupSet.h` (Public)


#### struct `UE::Geometry::FPolygroupLayer`  
`struct FPolygroupLayer`  
_L22-51_
- desc: FPolygroupLayer represents a polygroup set on a FDynamicMesh3, which supports a "default" group set stored on the mesh, and then N extended group layers stored in the mesh AttributeSet. This struct can represent either.
- L25 _public member_ `bool bIsDefaultLayer = true;` — If true, layer is the default FDynamicMesh3 triangle groups layer
- L27 _public member_ `int32 LayerIndex = -1;` — If bIsDefaultLayer is false, this is the index of the AttributeSet Polygroup Layer
- L30 _public function_ `static FPolygroupLayer Default()` — Construct a FPolygroupLayer for the default layer
- L32 _public function_ `static FPolygroupLayer Layer(int32 Index)` — Construct a FPolygroupLayer for an extended layer
- L34 _public function_ `bool operator==(const FPolygroupLayer& OtherLayer) const`
- L47 _public prototype_ `bool CheckExists(const FDynamicMesh3* Mesh) const;` — @return true if the specified layer (default or extended) exist and is initialized on the given Mesh
- L50 _public prototype_ `void EnableOnMesh(FDynamicMesh3& Mesh) const;` — Enable the specified layer on the given Mesh, if it's not already there

#### struct `UE::Geometry::FPolygroupSet`  
`struct FPolygroupSet`  
_L65-151_
- desc: Polygroup sets can be stored in multiple places. The default location is in the per-triangle group integer stored directly on a FDynamicMesh3. Additional layers may be stored in the FDynamicMeshAttributeSet. Future iterations could store packed polygroups in other places, store them in separate arrays, and so on. FPolygroupSet can be used to abstract these different cases, by providing a standard Polygroup Get/Set API. To support unique Polygroup ID allocation, FPolygroupSet calculates the maximum GroupID on creation, and updates this maximum across SetGroup() calls. AllocateNewGroupID() can be used to provide new unused GroupIDs. For consistency with FDynamicMesh3, MaxGroupID is set such that all GroupIDs are less than MaxGroupID
- L67 _public member_ `const FDynamicMesh3* Mesh = nullptr;`
- L68 _public member_ `const FDynamicMeshPolygroupAttribute* PolygroupAttrib = nullptr;`
- L69 _public member_ `int32 GroupLayerIndex = -1;`
- L70 _public member_ `int32 MaxGroupID = 0;` — Note: all group IDs are less than MaxGroupID
- L73 _public prototype_ `explicit FPolygroupSet(const FDynamicMesh3* MeshIn);` — Initialize a PolygroupSet for the given Mesh, and standard triangle group layer
- L76 _public prototype_ `explicit FPolygroupSet(const FDynamicMesh3* MeshIn, FPolygroupLayer GroupLayer);` — Initialize a PolygroupSet for the given Mesh, and standard triangle group layer
- L79 _public prototype_ `explicit FPolygroupSet(const FDynamicMesh3* MeshIn, const FDynamicMeshPolygroupAttribute* PolygroupAttribIn);` — Initialize a PolygroupSet for given Mesh and specific Polygroup attribute layer
- L82 _public prototype_ `explicit FPolygroupSet(const FDynamicMesh3* MeshIn, int32 PolygroupLayerIndex);` — Initialize a PolygroupSet for given Mesh and specific Polygroup attribute layer, found by index. If not valid, fall back to standard triangle group layer.
- L85 _public prototype_ `explicit FPolygroupSet(const FDynamicMesh3* MeshIn, FName AttribName);` — Initialize a PolygroupSet for given Mesh and specific Polygroup attribute layer, found by name. If not valid, fall back to standard triangle group layer.
- L88 _public prototype_ `explicit FPolygroupSet(const FPolygroupSet* CopyIn);` — Initialize a PolygroupSet by copying an existing PolygroupSet
- L92 _public function_ `const FDynamicMesh3* GetMesh()` — @return Mesh this PolygroupSet references
- L95 _public function_ `const FDynamicMeshPolygroupAttribute* GetPolygroup()` — @return PolygroupAttribute this PolygroupSet references, or null if no PolygroupAttribute is in use
- L98 _public function_ `int32 GetPolygroupIndex() const` — @return index of current PolygroupAttribute into Mesh AttributeSet, or -1 if this information does not exist
- L104 _public function_ `int32 GetGroup(int32 TriangleID) const` — @return PolygroupID for a TriangleID
- L112 _public function_ `int32 GetTriangleGroup(int32 TriangleID) const` — @return PolygroupID for a TriangleID
- L120 _public function_ `void SetGroup(int32 TriangleID, int32 NewGroupID, FDynamicMesh3& WritableMesh)` — Set the PolygroupID for a TriangleID
- L142 _public prototype_ `void RecalculateMaxGroupID();` — Calculate the current maximum PolygroupID used in the active set and store in MaxGroupID member
- L147 _public function_ `int32 AllocateNewGroupID()` — Allocate a new unused PolygroupID by incrementing the MaxGroupID member

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Polygroups/PolygroupUtil.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)
- L18 _prototype_ `FDynamicMeshPolygroupAttribute* FindPolygroupLayerByName(FDynamicMesh3& Mesh, FName Name);` (scope `UE::Geometry`) — Find the first FDynamicMeshPolygroupAttribute with the given FName in the AttributeSet of a Mesh. @return nullptr if no Polygroup layer is found
- L24 _prototype_ `const FDynamicMeshPolygroupAttribute* FindPolygroupLayerByName(const FDynamicMesh3& Mesh, FName Name);` (scope `UE::Geometry`) — Find the first FDynamicMeshPolygroupAttribute with the given FName in the AttributeSet of a Mesh. @return nullptr if no Polygroup layer is found
- L30 _prototype_ `FDynamicMeshTriangleLabelAttribute* FindTriangleLabelLayerByName(FDynamicMesh3& Mesh, const FName Name);` (scope `UE::Geometry`) — Find the FDynamicMeshTriangleLabelAttribute with the given FName in the AttributeSet of a Mesh. @return nullptr if no triangle label layer is found.
- L36 _prototype_ `const FDynamicMeshTriangleLabelAttribute* FindTriangleLabelLayerByName(const FDynamicMesh3& Mesh, FName Name);` (scope `UE::Geometry`) — Find the FDynamicMeshTriangleLabelAttribute with the given FName in the AttributeSet of a Mesh. @return nullptr if no triangle label layer is found.
- L41 _prototype_ `int32 FindPolygroupLayerIndexByName(const FDynamicMesh3& Mesh, FName Name);` (scope `UE::Geometry`) — @return index of the first Layer with the given FName in Mesh AttributeSet, or -1 if not found
- L46 _prototype_ `int32 FindPolygroupLayerIndex(const FDynamicMesh3& Mesh, const FDynamicMeshPolygroupAttribute* Layer);` (scope `UE::Geometry`) — @return index of Layer in Mesh AttributeSet, or -1 if not found
- L51 _prototype_ `int32 ComputeGroupIDBound(const FDynamicMesh3& Mesh, const FDynamicMeshPolygroupAttribute* Layer);` (scope `UE::Geometry`) — @return Compute the upper bound of the group IDs for the given layer (one greater than the highest group ID)
- L56 _prototype_ `FString MakeUniqueGroupLayerName(const FDynamicMesh3& Mesh, FString BaseName);` (scope `UE::Geometry`) — @return unique group layer name derived from BaseName by appending a numeric suffix in the form _0, _1, etc

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Polygroups/PolygroupsGenerator.h` (Public)


#### class `UE::Geometry::FPolygroupsGenerator`  
`class FPolygroupsGenerator`  
_L23-175_
- desc: FPolygroupsGenerator generates (face/tri/poly)groups for an input mesh based on the geometry and attributes of the input mesh. The various FindPolygroupsFromX() are the driving functions, each performs the full computation.
- L27 _public function_ `FPolygroupsGenerator()`
- L28 _public prototype_ `FPolygroupsGenerator(FDynamicMesh3* MeshIn);`
- L35 _public member_ `FDynamicMesh3* Mesh = nullptr;` — source mesh
- L38 _public member_ `bool bApplyPostProcessing = true;` — if true, then groups will be post-processed to optimize them, based on parmeters below
- L41 _public member_ `int32 MinGroupSize = 0;` — if > 1, groups with a triangle count smaller than this will be merged with a neighbouring group
- L44 _public member_ `bool bCopyToMesh = true;` — if true, after groups are computed they will be copied to the output mesh
- L47 _public member_ `int32 InitialGroupID = 0;` — start at this GroupID when assigning new groups
- L54 _public member_ `TArray<TArray<int>> FoundPolygroups;` — lists of triangle IDs, each list defines a polygroup/polygon
- L57 _public member_ `TArray<int> PolygroupEdges;` — list of edge IDs of mesh edges that are on polygroup borders
- L64 _public prototype_ `bool FindPolygroupsFromFaceNormals( double OneMinusCosAngleTolerance = 0.0001, bool bRespectUVSeams = false, bool bRespectNormalSeams = false, bool bUseAveragePolygroupNormals = false);` — Find Polygroups by randomly picking initial seed triangles and then flood-filling outwards, stopping when the opening angle at an edge is larger than the angle defined by the OneMinusCosAngleTolerance.
- L73 _public prototype_ `bool FindPolygroupsFromUVIslands(int32 UVLayer = 0);` — Find Polygroups based on UV Islands, ie each UV Island becomes a Polygroup
- L78 _public prototype_ `bool FindPolygroupsFromMaterialIDs();` — Find PolyGroups based on Material IDs -- i.e., connected groups of triangles with the same Material ID become a PolyGroup
- L83 _public prototype_ `bool FindPolygroupsFromHardNormalSeams();` — Find Polygroups based on Seams in UV Overlay
- L90 _public prototype_ `bool FindPolygroupsFromConnectedTris(TFunction<bool(int32 TriA, int32 TriB)> AreTrisConnected = nullptr);` — Find PolyGroups based on mesh connectivity and optionally a custom indicator function @param AreTrisConnected Optional custom function: Takes neighboring triangle IDs and returns true if they should be in the same PolyGroup @return true if at least one polygroup was found
- L95 _public prototype_ `bool FindSourceMeshPolygonPolygroups( bool bRespectUVSeams = true, bool bRespectNormalSeams = false, double QuadAdjacencyWeight = 1.0, double QuadMetricClamp = 1.0, int MaxSearchRounds = 1 );` — Find Polygroups by trying to invert triangluation of a polygon mesh
- L119 _public prototype_ `bool FindPolygroupsFromFurthestPointSampling( int32 NumPoints, EWeightingType WeightingType, FVector3d WeightingCoeffs = FVector3d::One(), FPolygroupSet* StartingGroups = nullptr);` — Incrementally compute approximate-geodesic-based furthest-point sampling of the mesh until NumPoints samples have been found, then compute local geodesic patches (eg approximate surface voronoi diagaram). Optionally weight geodesic-distance computation, which will produce different patch shapes. If StartingGroups are provided, then new groups are constrained to subdivide existing groups, ie none of the new groups will cross the boundaries of the StartingGroups
- L146 _public prototype_ `bool FindPolygroupsFromAreaDensityPointSampling( int32 NumPoints, EWeightingType WeightingType, FVector3d WeightingCoeffs = FVector3d::One(), FPolygroupSet* StartingGroups = nullptr);` — Similar to the technique used in FindPolygroupsFromFurthestPointSampling, except this algorithm attempts to select sample points in connected mesh regions based on the rough area of each region, granting more initial points to larger regions and fewer points to smaller regions, minium of one. This approach handles cases better when there is a large varience in region sizes and a large number of small regions compared to large regions. In this case, the alternative routine can over focus on small regions, granting the larger regions too few points. This leads to a relative over sampling of small regions and creates large polygroups out of the larger regions instead of more equitably breaking up larger regions into multiple groups. In this algorithm, NumPoints is less a strict target of final patches, but a rough guideline to direct the area sampler on how much total area each sample should occupy. E.g. a value of 100 would indicate we ideally want 100 equal sized regions of the mesh. However, since each connected region must have at least one sample, the final count may not be exactly NumPoints. Instead, each region, and it's area, is considered independently according to this desired "sample density". A "perfect" mesh (with one connected region and a high tesselation of equal sized triangles) should generate equal sized patches of NumPoints in count. A poorer quality mesh will result in a best effort take at this, while ensuring all triangles are part of a group.
- L156 _public prototype_ `void CopyPolygroupsToMesh();` — Copy the computed Polygroups to the input Mesh. Will be automatically called by the FindPolygroupsFromX() functions above if bCopyToMesh=true
- L161 _public prototype_ `void CopyPolygroupsToPolygroupSet(FPolygroupSet& Polygroups, FDynamicMesh3& TargetMesh);` — Copy the computed Polygroups to the given PolygroupSet and Mesh
- L167 _public prototype_ `bool FindPolygroupEdges();` — Initialize the PolygroupEdges output member by finding all the mesh edges that are on polygroup borders. Requires that polygroups have been computed and copied to the mesh
- L171 _protected function_ `void PostProcessPolygroups(bool bApplyMerging, TFunctionRef<bool(int32, int32)> TrisConnectedPredicate = [](int, int) { return true; });`
- L171 _protected prototype_ `void PostProcessPolygroups(bool bApplyMerging, TFunctionRef<bool(int32, int32)> TrisConnectedPredicate = [](int, int) { return true; });`
- L172 _protected function_ `void OptimizePolygroups(TFunctionRef<bool(int32, int32)> TrisConnectedPredicate = [](int, int) { return true; });`
- L172 _protected prototype_ `void OptimizePolygroups(TFunctionRef<bool(int32, int32)> TrisConnectedPredicate = [](int, int) { return true; });`
- L174 _protected prototype_ `void GetSeamConstraintEdges(bool bUVSeams, bool bNormalSeams, TSet<int32>& ConstraintEdgesOut) const;`

#### enum `UE::Geometry::FPolygroupsGenerator::EWeightingType`  
`enum class EWeightingType`  
_L106-110_
- desc: Weight potions for algorithms below
- L108 _public enumerator_ `None`
- L109 _public enumerator_ `NormalDeviation`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/ProjectionTargets.h` (Public)


#### class `UE::Geometry::FMeshProjectionTarget`  
`class FMeshProjectionTarget : public IOrientedProjectionTarget`  
_L20-49_
- inherits: `IOrientedProjectionTarget`
- desc: FMeshProjectionTarget provides an IProjectionTarget interface to a FDynamicMesh + FDynamicMeshAABBTree3 Use to project points to mesh surface.
- L24 _public member_ `const FDynamicMesh3* Mesh = nullptr;` — The mesh to project onto
- L26 _public member_ `FDynamicMeshAABBTree3* Spatial = nullptr;` — An AABBTree for Mesh
- L28 _public prototype_ `virtual ~FMeshProjectionTarget() = default;`
- L29 _public prototype_ `FMeshProjectionTarget() = default;`
- L31 _public function_ `FMeshProjectionTarget(const FDynamicMesh3* MeshIn, FDynamicMeshAABBTree3* SpatialIn)`
- L41 _public prototype_ `virtual FVector3d Project(const FVector3d& Point, int Identifier = -1) override;` — @return Projection of Point onto this target
- L46 _public prototype_ `virtual FVector3d Project(const FVector3d& Point, FVector3d& ProjectNormalOut, int Identifier = -1) override;` — @return Projection of Point onto this target, and set ProjectNormalOut to the triangle normal at the returned point (*not* interpolated vertex normal)

#### class `UE::Geometry::FWorldSpaceProjectionTarget`  
`class FWorldSpaceProjectionTarget : public FMeshProjectionTarget`  
_L52-113_
- inherits: `FMeshProjectionTarget`
- L56 _public prototype_ `virtual ~FWorldSpaceProjectionTarget() = default;`
- L57 _public prototype_ `FWorldSpaceProjectionTarget() = default;`
- L59 _public function_ `FWorldSpaceProjectionTarget(const FDynamicMesh3* MeshIn, FDynamicMeshAABBTree3* SpatialIn, const FTransformSRT3d& TargetMeshLocalToWorldIn, const FTransformSRT3d& ToolMeshLocalToWorldIn) : FMeshProjectionTarget(MeshIn, SpatialIn), TargetMeshLocalToWorld(TargetMeshLocalToWorldIn), ToolMeshLocalToWorld(ToolMeshLocalToWorldIn)`
- L71 _public function_ `virtual FVector3d Project(const FVector3d& Point, int Identifier = -1) override` — @return Projection of Point onto this target
- L90 _public function_ `virtual FVector3d Project(const FVector3d& Point, FVector3d& ProjectNormalOut, int Identifier = -1) override` — @return Projection of Point onto this target, and set ProjectNormalOut to the triangle normal at the returned point (*not* interpolated vertex normal)
- L110 _protected member_ `FTransformSRT3d TargetMeshLocalToWorld;`
- L111 _protected member_ `FTransformSRT3d ToolMeshLocalToWorld;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/QueueRemesher.h` (Public)


#### class `UE::Geometry::FQueueRemesher`  
`class FQueueRemesher : public FRemesher`  
_L24-164_
- inherits: `FRemesher`
- desc: Extension to Remesher that is smarter about which edges/vertices to touch: - A buffer tracks edges that were affected on last pass, and hence might need to be updated - FastSplitIteration() just does splits, to reach target edge length as quickly as possible - RemeshIteration() applies remesh pass for modified edges - TrackedFullSmoothPass_Buffer() smooths all vertices but only adds to queue if edge changes enough - TrackedFullProjectionPass() projects all vertices but only adds to queue if edge changes enough
- L29 _public function_ `FQueueRemesher(FDynamicMesh3* MeshIn) : FRemesher(MeshIn)`
- L32 _public member_ `int MaxFastSplitIterations = 20;` — Max number of passes just doing edge splits
- L35 _public member_ `int MaxRemeshIterations = 20;` — Max number of passes doing full remeshing operations
- L38 _public member_ `double MinActiveEdgeFraction = 0.01;` — If fraction of active edges falls below this threshold, consider result converged and terminate before MaxRemeshIterations
- L41 _public prototype_ `void FastestRemesh();` — Converge on remeshed result as quickly as possible
- L44 _public function_ `void BasicRemeshPass() override` — "Outer loop" for all remeshing operations
- L52 _protected prototype_ `virtual void TrackedFullProjectionPass(bool bParallel);` — Note: FRemesher has this: virtual void FullProjectionPass();
- L57 _protected member_ `TOptional<TSet<int>> ModifiedEdges;` — Set of edges that have been modified during a given iteration. Before the first iteration, this Optional is unset, signaling that the first iteration should process all edges in the mesh.  Subsequent iterations will only operate on this set of edges.
- L60 _protected member_ `TSet<int> EdgeBuffer;` — Persistent buffer of edges to be processed. This buffer is filled then iterated over.
- L63 _protected member_ `TFunction<void(int, int, int, int)> PostEdgeSplitFunction;` — The function called after an edge split occurs. This function will enqueue edges in ModifiedEdges.
- L66 _protected function_ `void OnEdgeSplit(int EdgeID, int VertexA, int VertexB, const FDynamicMesh3::FEdgeSplitInfo& SplitInfo) final` — Call the function above to enqueue edges in the ModifiedEdges set
- L90 _protected member_ `SettingState SavedState;`
- L92 _protected function_ `void PushState()`
- L105 _protected function_ `void PopState()`
- L119 _protected function_ `void QueueOneRing(int vid)`
- L131 _protected function_ `void QueueEdge(int eid)`
- L137 _protected function_ `void ResetQueue()`
- L142 _protected prototype_ `int FastSplitIteration();` — This pass only does edge splits and enqueues modified vertex neighborhoods. @return Number of split edges.
- L146 _protected prototype_ `void RemeshIteration( TFunctionRef<bool(void)> EarlyTerminationCheck );` — This pass does all edge operations plug smoothing and reprojection. EarlyTerminationCheck will be called after remesh operations, before smoothing/reprojection. Caller can return true to abort further computation.
- L151 _protected member_ `TArray<bool> EdgeShouldBeQueuedBuffer;` — Whether an edge should be added to ModifiedEdges (used in async tasks)
- L153 _protected prototype_ `virtual void InitializeVertexBufferForPass();`
- L158 _protected prototype_ `void TrackedMoveVerticesParallel(TFunction<FVector3d(int, bool&)> NewVertexPosition);` — Move all vertices in parallel. Update the timestamps. Add edges whose endpoints change to ModifiedEdges. The NewVertexPosition function accepts a vertex index and returns a new vertex position, as well as setting the bool out-param to indicate that the vertex has moved.
- L161 _protected prototype_ `void TrackedFullSmoothPass_Buffer(bool bParallel);` — Note: superclass has this: virtual void FullSmoothPass_Buffer(bool bParallel);

#### struct `UE::Geometry::FQueueRemesher::SettingState`  
`struct SettingState`  
_L77-88_
- desc: We occasionally want to override the user-specified choices of edge operations to achieve some sub-step of a full remesh algorithm. This struct encapsulates the Remesher settings so they can be saved, overwritten, and restored.
- L79 _public member_ `bool bEnableFlips;`
- L80 _public member_ `bool bEnableCollapses;`
- L81 _public member_ `bool bEnableSplits;`
- L82 _public member_ `bool bEnableSmoothing;`
- L83 _public member_ `double MinEdgeLength;`
- L84 _public member_ `double MaxEdgeLength;`
- L85 _public member_ `double SmoothSpeedT;`
- L86 _public member_ `ESmoothTypes SmoothType;`
- L87 _public member_ `ETargetProjectionMode ProjectionMode;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Remesher.h` (Public)


#### class `UE::Geometry::FRemesher`  
`class FRemesher : public FMeshRefinerBase`  
_L43-388_
- inherits: `FMeshRefinerBase`
- desc: FRemesher implements edge flip/split/collapse/smooth Remeshing. The basic process is very similar to the one described in: A Remeshing Approach to Multiresolution Modeling. Botsch & Kobbelt, SGP 2004. https://graphics.uni-bielefeld.de/publications/sgp04.pdf In the iterative usage, each call to BasicRemeshPass() makes a pass over the mesh and attempts to update the topology and shape to satisfy the target criteria. This function iterates over the mesh edges and calls ProcessEdge(), which tries to Collapse, then Split, then Flip the edge. After the topology pass, we optionally do a full-mesh Smoothing pass, and a full-mesh Reprojection pass, to project onto a target surface. A highly flexible constraint system can be used to control what is allowed to happen to individual edges and vertices, as well as Project vertices onto arbitrary proejction targets. This is done via FMeshConstraints which is set in the MeshRefinerBase base class. Many aspects of the algorithm can be controlled by the public variables in the block below. In addition many of the core internal functions can be overriden to customize behavior. Various callbacks functions are called when topology changes occur which allows you to for instance track changed regions of the mesh. @todo parallel smoothing and projection @todo port fast queue-based convergent remeshing
- L51 _public member_ `bool bEnableFlips = true;` — Controls whether edge-flips are allowed during remeshing pass
- L53 _public member_ `bool bEnableCollapses = true;` — Controls whether edge collapses are allowed during remeshing pass
- L55 _public member_ `bool bEnableSplits = true;` — Controls whether edge splits are allowed during remeshing pass
- L57 _public member_ `bool bEnableSmoothing = true;` — Controls whether vertex smoothing is applied during remeshing pass
- L62 _public member_ `bool bPreventNormalFlips = false;` — Controls whether we try to prevent normal flips inside operations and smoothing. This is moderately expensive and often is not needed. Disabled by default.
- L67 _public member_ `bool bPreventTinyTriangles = false;` — Controls whether we disallow creation of triangles with small areas inside edge operations. This is moderately expensive and in some cases can result in lower-quality meshes. Disabled by default.
- L77 _public member_ `EFlipMetric FlipMetric = EFlipMetric::OptimalValence;` — Type of flip metric that will be applied
- L80 _public member_ `double MinLengthFlipThresh = 0.9;` — For MinEdgeLength metric, only flip if NewLength < (MinLengthFlipThresh * CurLength)
- L83 _public member_ `double MinEdgeLength = 1.0;` — Minimum target edge length. Edges shorter than this will be collapsed if possible.
- L85 _public member_ `double MaxEdgeLength = 3.0;` — Maximum target edge length. Edges longer than this will be split if possible.
- L88 _public member_ `double SmoothSpeedT = 0.1;` — Smoothing speed, in range [0,1]
- L99 _public member_ `ESmoothTypes SmoothType = ESmoothTypes::Uniform;` — Type of smoothing that will be applied unless overridden by CustomSmoothF
- L102 _public member_ `TFunction<FVector3d(const FDynamicMesh3&, int, double)> CustomSmoothF;` — Override default smoothing function
- L105 _public member_ `TFunction<double(const FDynamicMesh3&, int)> CustomSmoothSpeedF;` — Override constant SmoothSpeedT with function
- L108 _public member_ `TFunction<double(const FDynamicMesh3& Mesh, int VertexA, int VertexB)> CustomEdgeLengthScaleF;` — Scale the computed edge length to allow for adaptive remeshing
- L112 _public member_ `bool bEnableParallelProjection = true;` — enable parallel projection. Only applied in AfterRefinement mode
- L118 _public member_ `bool bEnableParallelSmooth = true;` — Enable parallel smoothing. This will produce slightly different results across runs because we smooth in-place and hence there will be order side-effects.
- L123 _public member_ `bool bEnableSmoothInPlace = false;` — If smoothing is done in-place, we don't need an extra buffer, but also there will some randomness introduced in results. Probably worse.
- L132 _public function_ `FRemesher(FDynamicMesh3* MeshIn) : FMeshRefinerBase(MeshIn)`
- L136 _public prototype_ `virtual ~FRemesher() = default;`
- L139 _public prototype_ `void SetTargetEdgeLength(double fLength);` — Set min/max edge-lengths to sane values for given target edge length
- L148 _public prototype_ `virtual void Precompute();` — We can speed things up if we precompute some invariants. You need to re-run this if you are changing the mesh externally between remesh passes, otherwise you will get weird results. But you will probably still come out ahead, computation-time-wise
- L158 _public prototype_ `virtual void BasicRemeshPass();` — Linear edge-refinement pass, followed by smoothing and projection - Edges are processed in prime-modulo-order to break symmetry - smoothing is done in parallel if EnableParallelSmooth = true - Projection pass if ProjectionMode == AfterRefinement - number of modified edges returned in ModifiedEdgesLastPass
- L169 _public function_ `virtual void OnEdgeSplit(int EdgeID, int VertexA, int VertexB, const FDynamicMesh3::FEdgeSplitInfo& SplitInfo)` — Callback for subclasses to override to implement custom behavior
- L175 _public function_ `virtual void OnEdgeCollapse(int EdgeID, int VertexA, int VertexB, const FDynamicMesh3::FEdgeCollapseInfo& CollapseInfo)` — Callback for subclasses to override to implement custom behavior
- L181 _public function_ `virtual void OnEdgeFlip(int EdgeID, const FDynamicMesh3::FEdgeFlipInfo& FlipInfo)` — Callback for subclasses to override to implement custom behavior
- L191 _public member_ `int ModifiedEdgesLastPass = 0;` — Number of edges that were modified in previous Remesh pass. If this number gets small relative to edge count, you have probably converged (ish)
- L196 _protected function_ `FRemesher()` — for subclasses that extend our behavior
- L201 _protected member_ `bool bMeshIsClosed = false;` — we can avoid some checks/etc if we know that the mesh has no boundary edges. Set by Precompute()
- L204 _protected function_ `bool EnableInlineProjection() const` — this just lets us write more concise code
- L217 _protected member_ `uint64 MaxEdgeID = 0;` — We are using a modulo-index loop to break symmetry/pathological conditions. For example in a highly tessellated minimal cylinder, if the top/bottom loops have sequential edge IDs, and all edges are < min edge length, then we can easily end up successively collapsing each tiny edge, and eroding away the entire mesh! By using modulo-index loop we jump around and hence this is unlikely to happen.
- L218 _protected function_ `virtual int StartEdges()`
- L224 _protected function_ `virtual int GetNextEdge(int CurEdgeID, bool& bDone)`
- L247 _protected prototype_ `virtual EProcessResult ProcessEdge(int edgeID);`
- L255 _protected prototype_ `virtual void UpdateAfterSplit(int edgeID, int va, int vb, const FDynamicMesh3::FEdgeSplitInfo& splitInfo);` — After we split an edge, we have created a new edge and a new vertex. The edge needs to inherit the constraint on the other pre-existing edge that we kept. In addition, if the edge vertices were both constrained, then we /might/ want to also constrain this new vertex, possibly project to constraint target.
- L257 _protected member_ `TDynamicVector<FVector3d> TempPosBuffer;` — this is a temporary buffer used by smoothing and projection
- L258 _protected member_ `TArray<bool> TempFlagBuffer;` — list of which indices in TempPosBuffer were modified
- L260 _protected prototype_ `virtual void InitializeVertexBufferForPass();`
- L262 _protected prototype_ `virtual void ApplyVertexBuffer(bool bParallel);`
- L267 _protected prototype_ `virtual void FullSmoothPass_Buffer(bool bParallel);` — applies a smoothing pass to the mesh, storing intermediate positions in a buffer and then writing them at the end (so, no order effect)
- L270 _protected prototype_ `virtual FVector3d ComputeSmoothedVertexPos(int VertexID, TFunction<FVector3d(const FDynamicMesh3 &, int, double)> SmoothFunc, bool& bModified);` — computes smoothed vertex position w/ proper constraints/etc. Does not modify mesh.
- L274 _protected prototype_ `virtual void ApplyToSmoothVertices(const TFunction<void(int)>& VertexSmoothFunc);` — FullSmoothPass_Buffer this to calls VertexSmoothFunc for each vertex of the mesh
- L277 _protected prototype_ `virtual TFunction<FVector3d(const FDynamicMesh3&, int, double)> GetSmoothFunction();` — returns the function we want to use to compute a smoothed vertex position - will be CustomSmoothF if set, otherwise one of cotan/meanvalue/uniform
- L281 _protected prototype_ `virtual void FullProjectionPass(bool bParallel);` — Project vertices onto projection target.
- L284 _protected prototype_ `virtual void ProjectVertex(int VertexID, IProjectionTarget* UseTarget);` — Project a single vertex using the given target
- L287 _protected prototype_ `virtual FVector3d GetProjectedCollapsePosition(int VertexID, const FVector3d& vNewPos);` — used by collapse-edge to get projected position for new vertex
- L290 _protected prototype_ `virtual void ApplyToProjectVertices(const TFunction<void(int)>& VertexProjectFunc);` — Apply the given projection function to all vertices in the mesh
- L295 _protected prototype_ `void MoveVerticesParallel(TFunction<FVector3d(int, bool&)> NewVertexPosition);` — Move all vertices in parallel. Update the timestamps. The NewVertexPosition function accepts a vertex index and returns a new vertex position, as well as setting the bool out-param to indicate that the vertex has moved.
- L306 _protected member_ `int COUNT_SPLITS, COUNT_COLLAPSES, COUNT_FLIPS;` — profiling functions, turn on ENABLE_PROFILING to see output in console
- L306 _protected member_ `int COUNT_SPLITS, COUNT_COLLAPSES, COUNT_FLIPS;` — profiling functions, turn on ENABLE_PROFILING to see output in console
- L306 _protected member_ `int COUNT_SPLITS, COUNT_COLLAPSES, COUNT_FLIPS;` — profiling functions, turn on ENABLE_PROFILING to see output in console
- L309 _protected function_ `virtual void ProfileBeginPass()`
- L323 _protected function_ `virtual void ProfileEndPass()`
- L338 _protected function_ `virtual void ProfileBeginOps()`
- L342 _protected function_ `virtual void ProfileEndOps()`
- L346 _protected function_ `virtual void ProfileBeginSmooth()`
- L350 _protected function_ `virtual void ProfileEndSmooth()`
- L354 _protected function_ `virtual void ProfileBeginProject()`
- L358 _protected function_ `virtual void ProfileEndProject()`
- L363 _protected function_ `virtual void ProfileBeginCollapse()`
- L367 _protected function_ `virtual void ProfileEndCollapse()`
- L371 _protected function_ `virtual void ProfileBeginFlip()`
- L375 _protected function_ `virtual void ProfileEndFlip()`
- L379 _protected function_ `virtual void ProfileBeginSplit()`
- L383 _protected function_ `virtual void ProfileEndSplit()`

#### enum `UE::Geometry::FRemesher::EFlipMetric`  
`enum class EFlipMetric`  
_L70-74_
- desc: Available Edge Flip metrics
- L72 _public enumerator_ `OptimalValence = 0`
- L73 _public enumerator_ `MinEdgeLength = 1` — OptimalValence = 0,		  Flip towards Valence=6

#### enum `UE::Geometry::FRemesher::ESmoothTypes`  
`enum class ESmoothTypes`  
_L91-96_
- desc: Built-in Smoothing types
- L93 _public enumerator_ `Uniform = 0`
- L94 _public enumerator_ `Cotan = 1` — Uniform = 0,	  Uniform weights, produces regular mesh and fastest convergence
- L95 _public enumerator_ `MeanValue = 2` — Cotan = 1,		  Cotangent weights prevent tangential flow and hence preserve triangle shape / texture coordinates, but can become unstable...

#### enum `UE::Geometry::FRemesher::EProcessResult`  
`enum class EProcessResult`  
_L236-245_
- L238 _public enumerator_ `Ok_Collapsed`
- L239 _public enumerator_ `Ok_Flipped`
- L240 _public enumerator_ `Ok_Split`
- L241 _public enumerator_ `Ignored_EdgeIsFine`
- L242 _public enumerator_ `Ignored_EdgeIsFullyConstrained`
- L243 _public enumerator_ `Failed_OpNotSuccessful`
- L244 _public enumerator_ `Failed_NotAnEdge`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshBakerCommon.h` (Public)


#### class `UE::Geometry::FMeshMapTileBuffer`  
`class FMeshMapTileBuffer`  
_L49-85_
- desc: Image tile storage for map bakes.
- L52 _public function_ `FMeshMapTileBuffer(const FImageTile& TileIn, const int32 PixelSizeIn) : Tile(TileIn) , PixelSize(PixelSizeIn + 1)`
- L59 _public function_ `~FMeshMapTileBuffer()`
- L64 _public function_ `float& GetPixelWeight(const int64 LinearIdx) const`
- L70 _public function_ `float* GetPixel(const int64 LinearIdx) const`
- L76 _public function_ `const FImageTile& GetTile() const`
- L82 _private member_ `const FImageTile Tile;`
- L83 _private member_ `const int32 PixelSize;`
- L84 _private member_ `float* Buffer;`

#### class `UE::Geometry::IMeshBakerDetailSampler`  
`class IMeshBakerDetailSampler`  
_L95-363_
- desc: Base bake detail sampler class. This class defines the interface for all sample queries that FMeshBaseBaker supports including the spatial queries for base to detail correspondence sampling.
- L99 _public typedef_ `using FBakeDetailTexture = TTuple<const TImageBuilder<FVector4f>*, int>;` — (Image, UVLayer) pair for detail textures
- L108 _public typedef_ `using FBakeDetailNormalTexture = TTuple<const TImageBuilder<FVector4f>*, int, EBakeDetailNormalSpace>;` — (Image, NormalSpace, UVLayer) tuple for detail normal textures
- L110 _public prototype_ `virtual ~IMeshBakerDetailSampler() = default;`
- L113 _public prototype_ `virtual void ProcessMeshes(TFunctionRef<void(const void*)> ProcessFn) const = 0;` — Iterate over each mesh in the detail set.
- L116 _public prototype_ `virtual int32 GetTriangleCount(const void* Mesh) const = 0;` — @return the triangle count of a given mesh.
- L119 _public function_ `virtual void SetTangents(const void* Mesh, FMeshTangentsd* Tangents)` — Set the tangents for a given mesh
- L124 _public prototype_ `virtual void SetTextureMap(const void* Mesh, const FBakeDetailTexture& Map) = 0;` — Associate a texture map and UV layer index for a given mesh in the detail set
- L127 _public prototype_ `virtual void SetNormalTextureMap(const void* Mesh, const FBakeDetailNormalTexture& Map) = 0;` — Associate a normal map and UV layer index for a given mesh in the detail set
- L130 _public prototype_ `virtual const FBakeDetailTexture* GetTextureMap(const void* Mesh) const = 0;` — Retrieve a texture map and UV layer index from a given mesh in the detail set
- L132 _public prototype_ `virtual const FBakeDetailNormalTexture* GetNormalTextureMap(const void* Mesh) const = 0;`
- L135 _public prototype_ `virtual bool SupportsIdentityCorrespondence() const = 0;` — @return true if identity correspondence is supported
- L138 _public prototype_ `virtual bool SupportsNearestPointCorrespondence() const = 0;` — @return true if nearest point to triangle distance correspondence is supported
- L141 _public prototype_ `virtual bool SupportsRaycastCorrespondence() const = 0;` — @return true if triangle ray intersection correspondence is supported
- L144 _public function_ `virtual bool SupportsCustomCorrespondence() const` — @return true if a user-defined correspondence test is supported
- L149 _public function_ `virtual void* ComputeCustomCorrespondence(const FMeshUVSampleInfo& SampleInfo, FMeshMapEvaluator::FCorrespondenceSample& ValueOut) const`
- L154 _public function_ `virtual bool IsValidCorrespondence(const FMeshMapEvaluator::FCorrespondenceSample& Sample) const`
- L167 _public function_ `virtual const void* FindNearestTriangle( const FVector3d& Point, double& NearestDistSqrOut, int& TriId, FVector3d& TriBaryCoords, const IMeshSpatial::FQueryOptions& Options = IMeshSpatial::FQueryOptions()) const` — @param Point query point @param NearestDistSqrOut [Out] returned nearest squared distance, if triangle is found @param TriId [Out] ID of triangle nearest to Point within MaxDistance, or InvalidID if not found @param TriBaryCoords [Out] barycentric coordinates of the nearest point on the nearest tri. @param Options query options @return a pointer to the mesh that holds the nearest triangle
- L186 _public function_ `virtual const void* FindNearestHitTriangle( const FRay3d& Ray, double& NearestT, int& TriId, FVector3d& TriBaryCoords, const IMeshSpatial::FQueryOptions& Options = IMeshSpatial::FQueryOptions()) const` — Find nearest triangle from the given ray @param Ray query ray @param NearestT [Out] parameter of the nearest hit @param TriId [Out] ID of triangle intersected by ray within MaxDistance, or InvalidID if not found @param TriBaryCoords [Out] barycentric coordinates of intersection point on the hit tri. @param Options query options @return a pointer to the mesh whose triangle was intersected, nullptr otherwise.
- L202 _public function_ `virtual bool TestAnyHitTriangle( const FRay3d& Ray, const IMeshSpatial::FQueryOptions& Options = IMeshSpatial::FQueryOptions()) const` — Return true if any triangles hit by the given ray @param Ray query ray @param Options query options @return true if any triangles hit by the given ray
- L210 _public prototype_ `virtual FAxisAlignedBox3d GetBounds() const = 0;` — @return axis aligned bounding box for the detail mesh(es).
- L217 _public prototype_ `virtual bool IsTriangle(const void* Mesh, const int TriId) const = 0;` — @param Mesh pointer to mesh to query @param TriId the triangle index to test @return true if the given triangle index is valid.
- L224 _public prototype_ `virtual FIndex3i GetTriangle(const void* Mesh, const int TriId) const = 0;` — @param Mesh pointer to mesh to query @param TriId the triangle index to test @return 3 vertex indices of the given triangle.
- L231 _public prototype_ `virtual FVector3d GetTriNormal(const void* Mesh, const int TriId) const = 0;` — @param Mesh pointer to mesh to query @param TriId the triangle index to test @return the normal for the given triangle.
- L242 _public prototype_ `virtual bool GetTriUVs(const void* Mesh, int TriId, int UVLayer, FVector2f& UV0, FVector2f& UV1, FVector2f& UV2) const = 0;` — @param Mesh pointer to mesh to query @param TriId the triangle index to test @param UVLayer the UVLayer index to query @param UV0 the output UV for triangle vertex 0 @param UV1 the output UV for triangle vertex 1 @param UV2 the output UV for triangle vertex 2 @return true if a valid UV was returned, false otherwise.
- L249 _public prototype_ `virtual int32 GetMaterialID(const void* Mesh, const int TriId) const = 0;` — @param Mesh pointer to mesh to query @param TriId the triangle index to test @return the material ID for the given triangle.
- L256 _public prototype_ `virtual int32 GetPolyGroupID(const void* Mesh, const int TriId) const = 0;` — @param Mesh pointer to mesh to query @param TriId the triangle index to test @return the group ID for the given triangle.
- L262 _public prototype_ `virtual bool HasNormals(const void* Mesh) const = 0;` — @param Mesh pointer to mesh to query @return true if this mesh has normals
- L269 _public prototype_ `virtual bool HasUVs(const void* Mesh, int UVLayer = 0) const = 0;` — @param Mesh pointer to mesh to query @param UVLayer the UV layer to check for existence @return true if this mesh has UVs on the given layer
- L275 _public prototype_ `virtual bool HasTangents(const void* Mesh) const = 0;` — @param Mesh pointer to mesh to query @return true if this mesh has tangents
- L281 _public prototype_ `virtual bool HasColors(const void* Mesh) const = 0;` — @param Mesh pointer to mesh to query @return true if this mesh has vertex colors on the given layer
- L290 _public prototype_ `virtual FVector3d TriBaryInterpolatePoint( const void* Mesh, const int32 TriId, const FVector3d& BaryCoords) const = 0;` — Compute interpolated Position value inside triangle using barycentric coordinates @param Mesh pointer to mesh to query @param TriId index of triangle @param BaryCoords 3 barycentric coordinates inside triangle @return resulting interpolated Position parameter value
- L303 _public prototype_ `virtual bool TriBaryInterpolateNormal( const void* Mesh, const int32 TriId, const FVector3d& BaryCoords, FVector3f& NormalOut) const = 0;` — Compute interpolated Normal value inside triangle using barycentric coordinates @param Mesh pointer to mesh to query @param TriId index of triangle @param BaryCoords 3 barycentric coordinates inside triangle @param NormalOut resulting interpolated Normal parameter value @return true if a valid normal was returned, false otherwise
- L318 _public prototype_ `virtual bool TriBaryInterpolateUV( const void* Mesh, const int32 TriId, const FVector3d& BaryCoords, const int UVLayer, FVector2f& UVOut ) const = 0;` — Compute interpolated UV value inside triangle using barycentric coordinates @param Mesh pointer to mesh to query @param TriId index of triangle @param BaryCoords 3 barycentric coordinates inside triangle @param UVLayer UV layer to query @param UVOut resulting interpolated UV parameter value @return true if a valid UV was returned, false otherwise
- L333 _public prototype_ `virtual bool TriBaryInterpolateColor( const void* Mesh, const int32 TriId, const FVector3d& BaryCoords, FVector4f& ColorOut) const = 0;` — Compute interpolated vertex color value inside triangle using barycentric coordinates @param Mesh pointer to mesh to query @param TriId index of triangle @param BaryCoords 3 barycentric coordinates inside triangle @param ColorOut resulting interpolated vertex color parameter value @return true if a valid vertex color was returned, false otherwise
- L348 _public prototype_ `virtual bool TriBaryInterpolateTangents( const void* Mesh, const int32 TriId, const FVector3d& BaryCoords, FVector3d& TangentX, FVector3d& TangentY) const = 0;` — Compute interpolated tangent values inside triangle using barycentric coordinates @param Mesh pointer to mesh to query @param TriId index of triangle @param BaryCoords 3 barycentric coordinates inside triangle @param TangentX resulting interpolated tangentX value @param TangentY resulting interpolated tangentY value @return true if valid tangents were returned, false otherwise
- L360 _public prototype_ `virtual void GetCurvature( const void* Mesh, FMeshVertexCurvatureCache& CurvatureCache) const = 0;` — @param Mesh pointer to mesh to query @param CurvatureCache [Out] the curvature data to populate

#### enum `UE::Geometry::IMeshBakerDetailSampler::EBakeDetailNormalSpace`  
`enum class EBakeDetailNormalSpace`  
_L101-105_
- L103 _public enumerator_ `Tangent`
- L104 _public enumerator_ `Object`

#### class `UE::Geometry::FMeshBakerDynamicMeshSampler`  
`class FMeshBakerDynamicMeshSampler : public IMeshBakerDetailSampler`  
_L369-636_
- inherits: `IMeshBakerDetailSampler`
- desc: DynamicMesh bake detail sampler for baking 1 detail mesh to 1 target mesh.
- L374 _public function_ `FMeshBakerDynamicMeshSampler(const FDynamicMesh3* Mesh, const FDynamicMeshAABBTree3* Spatial, const FMeshTangentsd* Tangents = nullptr) : DetailMesh(Mesh), DetailSpatial(Spatial), DetailTangents(Tangents)`
- L379 _public function_ `virtual void ProcessMeshes(TFunctionRef<void(const void*)> ProcessFn) const override`
- L384 _public function_ `virtual int32 GetTriangleCount(const void* Mesh) const override`
- L390 _public function_ `virtual void SetTangents(const void* Mesh, FMeshTangentsd* Tangents) override`
- L395 _public function_ `virtual void SetTextureMap(const void* Mesh, const FBakeDetailTexture& Map) override`
- L400 _public function_ `virtual void SetNormalTextureMap(const void* Mesh, const FBakeDetailNormalTexture& Map) override`
- L405 _public function_ `virtual const FBakeDetailTexture* GetTextureMap(const void* Mesh) const override`
- L410 _public function_ `virtual const FBakeDetailNormalTexture* GetNormalTextureMap(const void* Mesh) const override`
- L415 _public function_ `virtual bool SupportsIdentityCorrespondence() const override`
- L420 _public function_ `virtual bool SupportsNearestPointCorrespondence() const override`
- L425 _public function_ `virtual bool SupportsRaycastCorrespondence() const override`
- L430 _public function_ `virtual const void* FindNearestTriangle( const FVector3d& Point, double& NearestDistSqrOut, int& TriId, FVector3d& TriBaryCoords, const IMeshSpatial::FQueryOptions& Options = IMeshSpatial::FQueryOptions()) const override`
- L446 _public function_ `virtual const void* FindNearestHitTriangle( const FRay3d& Ray, double& NearestT, int& TriId, FVector3d& TriBaryCoords, const IMeshSpatial::FQueryOptions& Options = IMeshSpatial::FQueryOptions()) const override`
- L457 _public function_ `virtual bool TestAnyHitTriangle( const FRay3d& Ray, const IMeshSpatial::FQueryOptions& Options = IMeshSpatial::FQueryOptions()) const override`
- L464 _public function_ `virtual FAxisAlignedBox3d GetBounds() const override`
- L469 _public function_ `virtual bool IsTriangle(const void* Mesh, const int TriId) const override`
- L475 _public function_ `virtual FIndex3i GetTriangle(const void* Mesh, const int TriId) const override`
- L481 _public function_ `virtual FVector3d GetTriNormal(const void* Mesh, const int TriId) const override`
- L487 _public function_ `virtual bool GetTriUVs(const void* Mesh, int TriId, int UVLayer, FVector2f& UV0, FVector2f& UV1, FVector2f& UV2) const override`
- L504 _public function_ `virtual int32 GetMaterialID(const void* Mesh, const int TriId) const override`
- L511 _public function_ `virtual int32 GetPolyGroupID(const void* Mesh, const int TriID) const override`
- L517 _public function_ `virtual bool HasNormals(const void* Mesh) const override`
- L523 _public function_ `virtual bool HasUVs(const void* Mesh, const int UVLayer = 0) const override`
- L529 _public function_ `virtual bool HasTangents(const void* Mesh) const override`
- L534 _public function_ `virtual bool HasColors(const void* Mesh) const override`
- L540 _public function_ `virtual FVector3d TriBaryInterpolatePoint( const void* Mesh, const int32 TriId, const FVector3d& BaryCoords) const override`
- L549 _public function_ `virtual bool TriBaryInterpolateNormal( const void* Mesh, const int32 TriId, const FVector3d& BaryCoords, FVector3f& NormalOut) const override`
- L567 _public function_ `virtual bool TriBaryInterpolateUV( const void* Mesh, const int32 TriId, const FVector3d& BaryCoords, const int UVLayer, FVector2f& UVOut ) const override`
- L586 _public function_ `virtual bool TriBaryInterpolateColor( const void* Mesh, const int32 TriId, const FVector3d& BaryCoords, FVector4f& ColorOut) const override`
- L604 _public function_ `virtual bool TriBaryInterpolateTangents( const void* Mesh, const int32 TriId, const FVector3d& BaryCoords, FVector3d& TangentX, FVector3d& TangentY) const override`
- L621 _public function_ `virtual void GetCurvature( const void* Mesh, FMeshVertexCurvatureCache& CurvatureCache) const override`
- L631 _protected member_ `const FDynamicMesh3* DetailMesh = nullptr;`
- L632 _protected member_ `const FDynamicMeshAABBTree3* DetailSpatial = nullptr;`
- L633 _protected member_ `const FMeshTangentsd* DetailTangents = nullptr;`
- L634 _protected member_ `FBakeDetailTexture DetailTextureMap = FBakeDetailTexture(nullptr, 0);`
- L635 _protected member_ `FBakeDetailNormalTexture DetailNormalTextureMap = FBakeDetailNormalTexture(nullptr, 0, EBakeDetailNormalSpace::Tangent);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)
- L26 _prototype_ `const void* GetDetailMeshTrianglePoint_Raycast( const IMeshBakerDetailSampler* DetailSpatial, const FVector3d& BasePoint, const FVector3d& BaseNormal, int32& DetailTriangleOut, FVector3d& DetailTriBaryCoords, double Thickness, bool bFailToNearestPoint );` (scope `UE::Geometry`) — Compute base/detail mesh correspondence by raycast @return a pointer to the hit mesh, otherwise nullptr.
- L41 _prototype_ `const void* GetDetailMeshTrianglePoint_Nearest( const IMeshBakerDetailSampler* DetailSpatial, const FVector3d& BasePoint, int32& DetailTriangleOut, FVector3d& DetailTriBaryCoords);` (scope `UE::Geometry`) — Compute base/detail mesh correspondence by nearest distance @return a pointer to the nearest mesh, otherwise nullptr.

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshBaseBaker.h` (Public)


#### class `UE::Geometry::FMeshBaseBaker`  
`class FMeshBaseBaker`  
_L18-117_
- L21 _public prototype_ `virtual ~FMeshBaseBaker() = default;`
- L43 _public function_ `void SetDetailSampler(IMeshBakerDetailSampler* Sampler)` — Setters
- L47 _public function_ `void SetTargetMesh(const FDynamicMesh3* Mesh)`
- L51 _public function_ `void SetTargetMeshTangents(const TSharedPtr<FMeshTangentsd, ESPMode::ThreadSafe>& Tangents)`
- L55 _public function_ `void SetTargetMeshUVLayer(const int32 UVLayerIn)`
- L59 _public function_ `void SetProjectionDistance(const double ProjectionDistanceIn)`
- L63 _public function_ `void SetCorrespondenceStrategy(const ECorrespondenceStrategy Strategy)`
- L69 _public function_ `const FDynamicMesh3* GetTargetMesh() const` — TargetMesh Getters
- L73 _public function_ `const FDynamicMeshUVOverlay* GetTargetMeshUVs() const`
- L78 _public function_ `int32 GetTargetMeshUVLayer() const`
- L82 _public function_ `const FDynamicMeshNormalOverlay* GetTargetMeshNormals() const`
- L87 _public function_ `const FMeshTangentsd* GetTargetMeshTangents() const`
- L93 _public function_ `const IMeshBakerDetailSampler* GetDetailSampler() const` — DetailMesh Getters
- L99 _public function_ `double GetProjectionDistance() const` — Other Getters
- L103 _public function_ `ECorrespondenceStrategy GetCorrespondenceStrategy() const`
- L109 _protected member_ `const FDynamicMesh3* TargetMesh = nullptr;`
- L110 _protected member_ `TSharedPtr<FMeshTangentsd, ESPMode::ThreadSafe> TargetMeshTangents;`
- L111 _protected member_ `int32 TargetMeshUVLayer = 0;`
- L113 _protected member_ `double ProjectionDistance = 3.0;`
- L114 _protected member_ `ECorrespondenceStrategy CorrespondenceStrategy = ECorrespondenceStrategy::RaycastStandard;`
- L116 _protected member_ `IMeshBakerDetailSampler* DetailSampler = nullptr;`

#### enum `UE::Geometry::FMeshBaseBaker::ECorrespondenceStrategy`  
`enum class ECorrespondenceStrategy`  
_L28-40_
- desc: ECorrespondenceStrategy determines the basic approach that will be used to establish a mapping from points on the BakeTarget Mesh (usually low-poly) to points on the Detail Mesh (eg highpoly). Geometrically this is not a 1-1 mapping so there are various options
- L31 _public enumerator_ `RaycastStandard` — Raycast inwards from Point+Thickness*Normal, if that misses, try Outwards from Point, then Inwards from Point
- L33 _public enumerator_ `NearestPoint` — Use geometrically nearest point. Thickness is ignored
- L35 _public enumerator_ `RaycastStandardThenNearest` — Use RaycastStandard but fall back to NearestPoint if none of the rays hit
- L37 _public enumerator_ `Identity` — Assume that BakeTarget == DetailMesh and so no mapping is necessary
- L39 _public enumerator_ `Custom` — Use user-defined strategy for finding correspondence

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshConstantMapEvaluator.h` (Public)


#### class `UE::Geometry::FMeshConstantMapEvaluator`  
`class FMeshConstantMapEvaluator : public FMeshMapEvaluator`  
_L19-42_
- inherits: `FMeshMapEvaluator`
- desc: A mesh evaluator for constant data. This evaluator can be useful as a filler when computing per channel color data.
- L22 _public prototype_ `FMeshConstantMapEvaluator() = default;`
- L23 _public prototype_ `explicit FMeshConstantMapEvaluator(float ValueIn);`
- L26 _public prototype_ `virtual void Setup(const FMeshBaseBaker& Baker, FEvaluationContext& Context) override;`
- L28 _public prototype_ `virtual const TArray<EComponents>& DataLayout() const override;`
- L30 _public function_ `virtual EMeshMapEvaluatorType Type() const override`
- L33 _public prototype_ `static void EvaluateSample(float*& Out, const FCorrespondenceSample& Sample, void* EvalData);`
- L35 _public prototype_ `static void EvaluateDefault(float*& Out, void* EvalData);`
- L37 _public prototype_ `static void EvaluateColor(const int DataIdx, float*& In, FVector4f& Out, void* EvalData);`
- L38 _public prototype_ `static void EvaluateChannel(const int DataIdx, float*& In, float& Out, void* EvalData);`
- L41 _public member_ `float Value = 0.0f;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshCurvatureMapBaker.h` (Public)


#### class `UE::Geometry::FMeshCurvatureMapBaker`  
`class FMeshCurvatureMapBaker : public FMeshImageBaker`  
_L16-95_
- inherits: `FMeshImageBaker`
- L19 _public prototype_ `virtual ~FMeshCurvatureMapBaker() = default;`
- L32 _public member_ `ECurvatureType UseCurvatureType = ECurvatureType::Mean;`
- L40 _public member_ `EColorMode UseColorMode = EColorMode::RedGreenBlue;`
- L48 _public member_ `EClampMode UseClampMode = EClampMode::FullRange;`
- L50 _public member_ `double RangeScale = 1.0;`
- L51 _public member_ `double MinRangeScale = 0.0;`
- L54 _public member_ `bool bOverrideCurvatureRange = false;` — allows override of the max curvature; if false, range is set based on [-(avg+stddev), avg+stddev]
- L55 _public member_ `double OverrideRangeMax = .1;`
- L58 _public member_ `double BlurRadius = 0.0;`
- L64 _public member_ `TSharedPtr<FMeshVertexCurvatureCache> Curvatures;`
- L72 _public prototype_ `virtual void Bake() override;` — Calculate bake result
- L75 _public prototype_ `void CacheDetailCurvatures(const FDynamicMesh3* DetailMesh);` — populate Curvatures member if valid data has not been provided
- L81 _public function_ `const TUniquePtr<TImageBuilder<FVector3f>>& GetResult() const`
- L83 _public function_ `TUniquePtr<TImageBuilder<FVector3f>> TakeResult()`
- L87 _protected member_ `TUniquePtr<TImageBuilder<FVector3f>> ResultBuilder;`
- L89 _protected prototype_ `void Bake_Single();`
- L91 _protected prototype_ `void Bake_Multi();`
- L94 _protected prototype_ `void GetColorMapRange(FVector3f& NegativeColor, FVector3f& ZeroColor, FVector3f& PositiveColor);`

#### enum `UE::Geometry::FMeshCurvatureMapBaker::ECurvatureType`  
`enum class ECurvatureType`  
_L25-31_
- L27 _public enumerator_ `Mean = 0`
- L28 _public enumerator_ `Gaussian = 1`
- L29 _public enumerator_ `MaxPrincipal = 2`
- L30 _public enumerator_ `MinPrincipal = 3`

#### enum `UE::Geometry::FMeshCurvatureMapBaker::EColorMode`  
`enum class EColorMode`  
_L34-39_
- L36 _public enumerator_ `BlackGrayWhite = 0`
- L37 _public enumerator_ `RedGreenBlue = 1`
- L38 _public enumerator_ `RedBlue = 2`

#### enum `UE::Geometry::FMeshCurvatureMapBaker::EClampMode`  
`enum class EClampMode`  
_L42-47_
- L44 _public enumerator_ `FullRange = 0`
- L45 _public enumerator_ `Positive = 1`
- L46 _public enumerator_ `Negative = 2`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshCurvatureMapEvaluator.h` (Public)


#### class `UE::Geometry::FMeshCurvatureMapEvaluator`  
`class FMeshCurvatureMapEvaluator : public FMeshMapEvaluator`  
_L20-94_
- inherits: `FMeshMapEvaluator`
- desc: A mesh evaluator for mesh curvatures.
- L30 _public member_ `ECurvatureType UseCurvatureType = ECurvatureType::Mean;`
- L38 _public member_ `EColorMode UseColorMode = EColorMode::RedGreenBlue;`
- L46 _public member_ `EClampMode UseClampMode = EClampMode::FullRange;`
- L48 _public member_ `double RangeScale = 1.0;`
- L49 _public member_ `double MinRangeScale = 0.0;`
- L52 _public member_ `bool bOverrideCurvatureRange = false;` — Allows override of the max curvature; if false, range is set based on [-(avg+stddev), avg+stddev]
- L53 _public member_ `double OverrideRangeMax = 0.1;`
- L56 _public member_ `TSharedPtr<FMeshVertexCurvatureCache> Curvatures;` — Required input data, can be provided, will be computed otherwise
- L60 _public prototype_ `virtual void Setup(const FMeshBaseBaker& Baker, FEvaluationContext& Context) override;`
- L62 _public prototype_ `virtual const TArray<EComponents>& DataLayout() const override;`
- L64 _public function_ `virtual EMeshMapEvaluatorType Type() const override`
- L67 _public prototype_ `static void EvaluateSample(float*& Out, const FCorrespondenceSample& Sample, void* EvalData);`
- L69 _public prototype_ `static void EvaluateDefault(float*& Out, void* EvalData);`
- L71 _public prototype_ `static void EvaluateColor(const int DataIdx, float*& In, FVector4f& Out, void* EvalData);`
- L73 _public prototype_ `static void EvaluateChannel(const int DataIdx, float*& In, float& Out, void* EvalData);`
- L76 _public prototype_ `void CacheDetailCurvatures();` — Populate Curvatures member if valid data has not been provided
- L80 _protected member_ `const IMeshBakerDetailSampler* DetailSampler = nullptr;` — Cached data
- L81 _protected member_ `double MinPreClamp = -TNumericLimits<double>::Max();`
- L82 _protected member_ `double MaxPreClamp = TNumericLimits<double>::Max();`
- L83 _protected member_ `FInterval1d ClampRange;`
- L84 _protected member_ `FVector3f NegativeColor;`
- L85 _protected member_ `FVector3f ZeroColor;`
- L86 _protected member_ `FVector3f PositiveColor;`
- L89 _protected prototype_ `double GetCurvature(int32 vid) const;`
- L90 _protected prototype_ `void GetColorMapRange(FVector3f& NegativeColorOut, FVector3f& ZeroColorOut, FVector3f& PositiveColorOut) const;`
- L93 _private prototype_ `double SampleFunction(const FCorrespondenceSample& SampleData) const;`

#### enum `UE::Geometry::FMeshCurvatureMapEvaluator::ECurvatureType`  
`enum class ECurvatureType`  
_L23-29_
- L25 _public enumerator_ `Mean = 0`
- L26 _public enumerator_ `Gaussian = 1`
- L27 _public enumerator_ `MaxPrincipal = 2`
- L28 _public enumerator_ `MinPrincipal = 3`

#### enum `UE::Geometry::FMeshCurvatureMapEvaluator::EColorMode`  
`enum class EColorMode`  
_L32-37_
- L34 _public enumerator_ `BlackGrayWhite = 0`
- L35 _public enumerator_ `RedGreenBlue = 1`
- L36 _public enumerator_ `RedBlue = 2`

#### enum `UE::Geometry::FMeshCurvatureMapEvaluator::EClampMode`  
`enum class EClampMode`  
_L40-45_
- L42 _public enumerator_ `FullRange = 0`
- L43 _public enumerator_ `Positive = 1`
- L44 _public enumerator_ `Negative = 2`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DYNAMICMESH_API`
- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshGenericWorldPositionBaker.h` (Public)


#### class `UE::Geometry::FMeshGenericWorldPositionColorBaker`  
`class FMeshGenericWorldPositionColorBaker : public FMeshImageBaker`  
_L22-52_
- inherits: `FMeshImageBaker`
- desc: Bake Colors based on arbitrary Position/Normal sampling. Useful for (eg) baking from an arbitrary function defined over space
- L25 _public prototype_ `virtual ~FMeshGenericWorldPositionColorBaker() = default;`
- L31 _public member_ `FVector4f DefaultColor = FVector4f(0, 0, 0, 1);`
- L33 _public member_ `TFunction<FVector4f(FVector3d, FVector3d)> ColorSampleFunction = [this](FVector3d Position, FVector3d Normal) { return DefaultColor; };`
- L34 _public function_ `= [this](FVector3d Position, FVector3d Normal)`
- L40 _public prototype_ `virtual void Bake() override;`
- L46 _public function_ `const TUniquePtr<TImageBuilder<FVector4f>>& GetResult() const`
- L48 _public function_ `TUniquePtr<TImageBuilder<FVector4f>> TakeResult()`
- L51 _protected member_ `TUniquePtr<TImageBuilder<FVector4f>> ResultBuilder;`

#### class `UE::Geometry::FMeshGenericWorldPositionNormalBaker`  
`class FMeshGenericWorldPositionNormalBaker : public FMeshImageBaker`  
_L61-93_
- inherits: `FMeshImageBaker`
- desc: Bake Tangent-Space Normals based on arbitrary Position/Normal sampling. Useful for (eg) baking from an arbitrary function defined over space.
- L64 _public prototype_ `virtual ~FMeshGenericWorldPositionNormalBaker() = default;`
- L70 _public member_ `const TMeshTangents<double>* BaseMeshTangents;`
- L72 _public member_ `FVector3f DefaultNormal = FVector3f(0, 0, 1);`
- L74 _public member_ `TFunction<FVector3f(FVector3d, FVector3d)> NormalSampleFunction = [this](FVector3d Position, FVector3d Normal) { return DefaultNormal; };`
- L75 _public function_ `= [this](FVector3d Position, FVector3d Normal)`
- L81 _public prototype_ `virtual void Bake() override;`
- L87 _public function_ `const TUniquePtr<TImageBuilder<FVector3f>>& GetResult() const`
- L89 _public function_ `TUniquePtr<TImageBuilder<FVector3f>> TakeResult()`
- L92 _protected member_ `TUniquePtr<TImageBuilder<FVector3f>> NormalsBuilder;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshHeightMapEvaluator.h` (Public)


#### class `UE::Geometry::FMeshHeightMapEvaluator`  
`class FMeshHeightMapEvaluator : public FMeshMapEvaluator`  
_L20-60_
- inherits: `FMeshMapEvaluator`
- desc: A mesh evaluator for mesh height as color data.
- L30 _public member_ `EHeightRangeMode RangeMode = EHeightRangeMode::Absolute;`
- L31 _public member_ `FInterval1f Range;`
- L34 _public prototype_ `FMeshHeightMapEvaluator() = default;`
- L35 _public prototype_ `FMeshHeightMapEvaluator(const FMeshHeightMapEvaluator&) = default;`
- L36 _public prototype_ `FMeshHeightMapEvaluator& operator=(const FMeshHeightMapEvaluator&) = default;`
- L39 _public prototype_ `virtual void Setup(const FMeshBaseBaker& Baker, FEvaluationContext& Context) override;`
- L41 _public prototype_ `virtual const TArray<EComponents>& DataLayout() const override;`
- L43 _public function_ `virtual EMeshMapEvaluatorType Type() const override`
- L46 _public prototype_ `static void EvaluateSample(float*& Out, const FCorrespondenceSample& Sample, void* EvalData);`
- L48 _public prototype_ `static void EvaluateDefault(float*& Out, void* EvalData);`
- L50 _public prototype_ `static void EvaluateColor(const int DataIdx, float*& In, FVector4f& Out, void* EvalData);`
- L51 _public prototype_ `static void EvaluateChannel(const int DataIdx, float*& In, float& Out, void* EvalData);`
- L55 _protected member_ `const IMeshBakerDetailSampler* DetailSampler = nullptr;` — Cached data
- L56 _protected member_ `FInterval1f CachedRange;`
- L59 _private prototype_ `float SampleFunction(const FCorrespondenceSample& SampleData) const;`

#### enum `UE::Geometry::FMeshHeightMapEvaluator::EHeightRangeMode`  
`enum class EHeightRangeMode`  
_L23-29_
- L26 _public enumerator_ `Absolute` — Absolute units in object space
- L28 _public enumerator_ `RelativeBounds` — Ratio of maximum bounding box axis

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshImageBaker.h` (Public)


#### class `UE::Geometry::FMeshImageBaker`  
`class FMeshImageBaker`  
_L12-37_
- L15 _public prototype_ `virtual ~FMeshImageBaker() = default;`
- L17 _public function_ `void SetCache(const FMeshImageBakingCache* CacheIn)`
- L22 _public function_ `const FMeshImageBakingCache* GetCache() const`
- L27 _public function_ `virtual void Bake()`
- L35 _protected member_ `const FMeshImageBakingCache* ImageBakeCache;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshImageBakingCache.h` (Public)


#### class `UE::Geometry::FMeshImageBakingCache`  
`class FMeshImageBakingCache`  
_L20-121_
- L41 _public prototype_ `void SetDetailMesh(const FDynamicMesh3* Mesh, const FDynamicMeshAABBTree3* Spatial);`
- L42 _public prototype_ `void SetBakeTargetMesh(const FDynamicMesh3* Mesh);`
- L44 _public prototype_ `void SetDimensions(FImageDimensions Dimensions);`
- L45 _public prototype_ `void SetUVLayer(int32 UVLayer);`
- L46 _public prototype_ `void SetThickness(double Thickness);`
- L47 _public prototype_ `void SetCorrespondenceStrategy(ECorrespondenceStrategy Strategy);`
- L48 _public prototype_ `void SetGutterSize(int32 GutterSize);`
- L50 _public function_ `FImageDimensions GetDimensions() const`
- L51 _public function_ `int32 GetUVLayer() const`
- L52 _public function_ `double GetThickness() const`
- L53 _public function_ `ECorrespondenceStrategy GetCorrespondenceStrategy() const`
- L55 _public function_ `const FDynamicMesh3* GetBakeTargetMesh() const`
- L56 _public prototype_ `const FDynamicMeshUVOverlay* GetBakeTargetUVs() const;`
- L57 _public prototype_ `const FDynamicMeshNormalOverlay* GetBakeTargetNormals() const;`
- L59 _public function_ `const FDynamicMesh3* GetDetailMesh() const`
- L60 _public function_ `const FDynamicMeshAABBTree3* GetDetailSpatial() const`
- L61 _public prototype_ `const FDynamicMeshNormalOverlay* GetDetailNormals() const;`
- L64 _public function_ `bool IsCacheValid() const`
- L66 _public prototype_ `bool ValidateCache();`
- L79 _public prototype_ `void EvaluateSamples(TFunctionRef<void(const FVector2i&, const FCorrespondenceSample&)> SampleFunction, bool bParallel = true) const;`
- L82 _public prototype_ `const FImageOccupancyMap* GetOccupancyMap() const;`
- L93 _public prototype_ `void FindSamplingHoles(TFunctionRef<bool(const FVector2i&)> IsValidSampleFunction, TArray<FVector2i>& HolePixelsOut, bool bParallel = true) const;` — Iterate over valid samples in the Occupancy map to find "holes", ie pixels where no valid sample could be computed according to IsValidSampleFunction. This can be used after a bake to find locations where the baked map needs to be repaired as a post-process (eg using image infilling/etc), which can produce better results than (eg) using a "worse" sampling strategy to guarantee some non-garbage result (eg Nearest-point sampling)
- L99 _public function_ `TFunction<bool(void)> CancelF = []()` — if this function returns true, we should abort calculation
- L99 _public member_ `TFunction<bool(void)> CancelF = []() { return false; };` — if this function returns true, we should abort calculation
- L102 _protected member_ `const FDynamicMesh3* DetailMesh = nullptr;`
- L103 _protected member_ `const FDynamicMeshAABBTree3* DetailSpatial = nullptr;`
- L104 _protected member_ `const FDynamicMesh3* TargetMesh = nullptr;`
- L106 _protected member_ `FImageDimensions Dimensions = FImageDimensions(128,128);`
- L107 _protected member_ `int32 UVLayer = 0;`
- L108 _protected member_ `double Thickness = 3.0;`
- L109 _protected member_ `ECorrespondenceStrategy CorrespondenceStrategy = ECorrespondenceStrategy::RaycastStandard;`
- L110 _protected member_ `int32 GutterSize = 4;`
- L112 _protected member_ `TDenseGrid2<FCorrespondenceSample> SampleMap;`
- L113 _protected member_ `bool bSamplesValid = false;`
- L114 _protected prototype_ `void InvalidateSamples();`
- L117 _protected member_ `TUniquePtr<FImageOccupancyMap> OccupancyMap;`
- L118 _protected member_ `bool bOccupancyValid = false;`
- L119 _protected prototype_ `void InvalidateOccupancy();`

#### enum `UE::Geometry::FMeshImageBakingCache::ECorrespondenceStrategy`  
`enum class ECorrespondenceStrategy`  
_L29-39_
- desc: ECorrespondenceStrategy determines the basic approach that will be used to establish a mapping from points on the BakeTarget Mesh (usually low-poly) to points on the Detail Mesh (eg highpoly). Geometrically this is not a 1-1 mapping so there are various options
- L32 _public enumerator_ `RaycastStandard` — Raycast inwards from Point+Thickness*Normal, if that misses, try Outwards from Point, then Inwards from Point
- L34 _public enumerator_ `NearestPoint` — Use geometrically nearest point. Thickness is ignored
- L36 _public enumerator_ `RaycastStandardThenNearest` — Use RaycastStandard but fall back to NearestPoint if none of the rays hit
- L38 _public enumerator_ `Identity` — Assume that BakeTarget == DetailMesh and so no mapping is necessary

#### struct `UE::Geometry::FMeshImageBakingCache::FCorrespondenceSample`  
`struct FCorrespondenceSample`  
_L69-76_
- L71 _public member_ `FMeshUVSampleInfo BaseSample;`
- L72 _public member_ `FVector3d BaseNormal;`
- L74 _public member_ `int32 DetailTriID;`
- L75 _public member_ `FVector3d DetailBaryCoords;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DYNAMICMESH_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshMapBaker.h` (Public)


#### class `UE::Geometry::FMeshMapBaker`  
`class FMeshMapBaker : public FMeshBaseBaker`  
_L26-263_
- inherits: `FMeshBaseBaker`
- L35 _public prototype_ `void Bake();` — Process all bakers to generate image results for each.
- L38 _public prototype_ `int32 AddEvaluator(const TSharedPtr<FMeshMapEvaluator, ESPMode::ThreadSafe>& Eval);` — Add a baker to be processed.
- L41 _public prototype_ `FMeshMapEvaluator* GetEvaluator(int32 EvalIdx) const;` — @return the evaluator at the given index.
- L44 _public prototype_ `int32 NumEvaluators() const;` — @return the number of bake evaluators on this baker.
- L47 _public prototype_ `void Reset();` — Reset the list of bakers.
- L50 _public prototype_ `const TArrayView<TUniquePtr<TImageBuilder<FVector4f>>> GetBakeResults(int32 EvalIdx);` — @return the bake result image for a given baker index.
- L53 _public function_ `TFunction<bool(void)> CancelF = []()` — @return true if we should abort calculation
- L53 _public member_ `TFunction<bool(void)> CancelF = []() { return false; };` — @return true if we should abort calculation
- L56 _public member_ `TFunction<void(TArray<TUniquePtr<TImageBuilder<FVector4f>>>&)> PostWriteToImageCallback = [](TArray<TUniquePtr<TImageBuilder<FVector4f>>>& PostWriteToImageBakeResults) {};` — Function to call after evaluator data is written to the final image, but before any gutter processing occurs
- L57 _public function_ `= [](TArray<TUniquePtr<TImageBuilder<FVector4f>>>& PostWriteToImageBakeResults)`
- L60 _public member_ `TFunction<void(bool, const FMeshMapEvaluator::FCorrespondenceSample&, const FVector2d&, const FVector2i&)> InteriorSampleCallback = [](bool bSampleValid, const FMeshMapEvaluator::FCorrespondenceSample& Sample, const FVector2d& UVPosition, const FVector2i& ImageCoords) {};` — Function to call for each interior sample
- L61 _public function_ `= [](bool bSampleValid, const FMeshMapEvaluator::FCorrespondenceSample& Sample, const FVector2d& UVPosition, const FVector2i& ImageCoords)`
- L72 _public member_ `TFunction<float(const FVector2i&, const FVector2d&, int32)> SampleFilterF = nullptr;` — @param ImageCoords the output image coordinates to be evaluated @param UV the target mesh UV coordinates to be evaluated @param TriID the target mesh triangle ID to be evaluated @return a weight (clamped by the baker to the range [0,1]) used to combine evaluator sample values with evaluator defaults. For evaluators using EAccumulateMode::Overwrite the default is used when weight == 0, and the value is used otherwise. For evaluators using EAccumulateMode::Add the sample's value and default are blended using the expression: `weight * value + (1 - weight) * default`
- L86 _public prototype_ `void SetDimensions(FImageDimensions DimensionsIn);`
- L87 _public prototype_ `void SetGutterEnabled(bool bEnabled);`
- L88 _public prototype_ `void SetGutterSize(int32 GutterSizeIn);`
- L89 _public prototype_ `void SetSamplesPerPixel(int32 SamplesPerPixelIn);`
- L90 _public prototype_ `void SetFilter(EBakeFilterType FilterTypeIn);`
- L91 _public prototype_ `void SetTileSize(int TileSizeIn);`
- L93 _public function_ `FImageDimensions GetDimensions() const`
- L94 _public function_ `bool GetGutterEnabled() const`
- L95 _public function_ `int32 GetGutterSize() const`
- L96 _public function_ `int32 GetSamplesPerPixel() const`
- L97 _public function_ `EBakeFilterType GetFilter() const`
- L98 _public function_ `int32 GetTileSize() const`
- L108 _public prototype_ `static void ComputeUVCharts(const FDynamicMesh3& Mesh, TArray<int32>& MeshUVCharts);` — Computes the connected UV triangles and returns an array containing the mapping from triangle ID to unique UV chart ID. If the mesh has no UVs, the UVCharts will be initialized to 0. @param Mesh the mesh to compute UV charts. @param MeshUVCharts the triangle ID to UV Chart ID array.
- L119 _public function_ `void SetTargetMeshUVCharts(TArray<int32>* UVChartsIn)` — Set an a Triangle ID to UV Chart ID array for TargetMesh. If this is not set, then the baker will compute it as part of Bake(). Since ComputeUVCharts() is non-trivial, this method is intended to allow a client to externally cache the result of ComputeUVCharts to minimize the overhead per bake. @param UVChartsIn the TriID to UVChartID map
- L125 _public function_ `const TArray<int32>* GetTargetMeshUVCharts() const` — @return the Triangle ID to UV Chart ID mapping
- L150 _public member_ `FBakeAnalytics BakeAnalytics;`
- L154 _protected prototype_ `void BakeSample( FMeshMapTileBuffer& TileBuffer, const FMeshMapEvaluator::FCorrespondenceSample& Sample, const FVector2d& QueryUVPosition, const FVector2i& ImageCoords, const FImageOccupancyMap& OccupancyMap);` — Evaluate this sample.
- L162 _protected prototype_ `void InitBake();` — Initialize evaluation contexts and precompute data for bake evaluation.
- L165 _protected prototype_ `void InitBakeDefaults();` — Initialize bake sample default floats and colors.
- L168 _protected prototype_ `void InitFilter();` — Initialize filter
- L171 _protected member_ `const bool bParallel = true;`
- L173 _protected member_ `FDynamicMesh3 FlatMesh;`
- L174 _protected member_ `FMeshSurfaceUVSampler MeshUVSampler;`
- L176 _protected member_ `FImageDimensions Dimensions = FImageDimensions(128, 128);`
- L179 _protected function_ `const TArray<int32>& EvaluatorIdsForMode(FMeshMapEvaluator::EAccumulateMode Mode) const` — @return evaluator ids with the corresponding mode
- L188 _protected member_ `bool bGutterEnabled = true;` — If true, the baker will pad the baked content past the UV borders by GutterSize. This is useful to minimize artifacts when filtering or mipmapping.
- L191 _protected member_ `int32 GutterSize = 4;` — The pixel distance (in texel diagonal length) to pad baked content past the UV borders.
- L194 _protected member_ `int32 SamplesPerPixel = 1;` — The number of samples to evaluate per pixel.
- L197 _protected member_ `int32 TileSize = 32;` — The square dimensions for tiled processing of the output image(s).
- L200 _protected member_ `int32 TilePadding = 2;` — The amount of padding for tiled processing of the output image(s).
- L203 _protected member_ `int32 FilterKernelSize = 0;` — The pixel distance around the sample texel to be considered by the filter. [0, TilePadding]
- L206 _protected member_ `EBakeFilterType FilterType = EBakeFilterType::BSpline;` — The texture filter type.
- L209 _protected member_ `static FBoxFilter BoxFilter;` — Texture filters
- L210 _protected member_ `static FBSplineFilter BSplineFilter;`
- L211 _protected member_ `static FMitchellNetravaliFilter MitchellNetravaliFilter;`
- L214 _protected typedef_ `using TextureFilterFn = float(*)(const FVector2d& Dist);` — Texture filter function
- L215 _protected member_ `TextureFilterFn TextureFilterEval = nullptr;`
- L216 _protected typedef_ `using IsInFilterRegionFn = bool(*)(const FVector2d& Dist);`
- L217 _protected member_ `IsInFilterRegionFn IsInFilterRegionEval = nullptr;`
- L220 _protected prototype_ `template<EBakeFilterType BakeFilterType> static float EvaluateFilter(const FVector2d& Dist);`
- L223 _protected prototype_ `template<EBakeFilterType BakeFilterType> static bool EvaluateIsInFilterRegion(const FVector2d& Dist);`
- L226 _protected member_ `int32 BakeSampleBufferSize = 0;` — The total size of the temporary float buffer for BakeSample.
- L229 _protected member_ `TArray<TSharedPtr<FMeshMapEvaluator, ESPMode::ThreadSafe>> Bakers;` — The list of evaluators to process.
- L232 _protected member_ `TArray<FMeshMapEvaluator::FEvaluationContext> BakeContexts;` — Evaluation contexts for each mesh evaluator.
- L235 _protected member_ `TArray<TArray<int32>> BakeAccumulateLists;` — Lists of Bake indices for each accumulation mode.
- L238 _protected member_ `TArray<float> BakeDefaults;` — Array of default values/colors per BakeResult.
- L239 _protected member_ `TArray<FVector4f> BakeDefaultColors;`
- L242 _protected member_ `TArray<int32> BakeOffsets;` — Offsets per Baker into the BakeResults array.
- L245 _protected member_ `TArray<int32> BakeSampleOffsets;` — Offsets per BakeResult into the BakeSample buffer.
- L248 _protected member_ `TArray<TUniquePtr<TImageBuilder<FVector4f>>> BakeResults;` — Array of bake result images.
- L255 _protected member_ `TArray<int32>* TargetMeshUVCharts = nullptr;` — Array of TargetMesh triangle ID to UV chart ID mapping. Can be optionally provided by the client. If not provided, will be computed as part of the bake.
- L262 _protected member_ `TArray<int32> TargetMeshUVChartsLocal;` — Local Array of TargetMesh triangle ID to UV chart ID mapping. This will be populated only if not provided by the client via TargetMeshUVCharts.

#### enum `UE::Geometry::FMeshMapBaker::EBakeFilterType`  
`enum class EBakeFilterType`  
_L78-84_
- L80 _public enumerator_ `None`
- L81 _public enumerator_ `Box`
- L82 _public enumerator_ `BSpline`
- L83 _public enumerator_ `MitchellNetravali`

#### struct `UE::Geometry::FMeshMapBaker::FBakeAnalytics`  
`struct FBakeAnalytics`  
_L133-149_
- desc: Analytics
- L135 _public member_ `double TotalBakeDuration = 0.0;`
- L136 _public member_ `double WriteToImageDuration = 0.0;`
- L137 _public member_ `double WriteToGutterDuration = 0.0;`
- L138 _public member_ `std::atomic<int64> NumSamplePixels = 0;`
- L139 _public member_ `std::atomic<int64> NumGutterPixels = 0;`
- L141 _public function_ `void Reset()`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API DYNAMICMESH_API`
- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshMapBakerQueue.h` (Public)


#### class `UE::Geometry::FMeshMapBakerQueue`  
`class FMeshMapBakerQueue`  
_L25-136_
- desc: Multi-producer/single-consumer queue for the ordered processing of data in FMeshMapBaker. This queue is designed to mediate the aggregation of data into a shared output buffer. The number of data to be aggregated must be provided at initialization. Producer threads then "post" data to the queue and any single thread can temporarily assume the role of consumer to "process" the data.
- L29 _private member_ `static constexpr SIZE_T Alignment = PLATFORM_CACHE_LINE_SIZE;` — Align to cache line size and pad our slot data to avoid false sharing.
- L37 _private member_ `SIZE_T NumSlots = 0;` — Cached size of the queue
- L40 _private member_ `FSlotData* Slots = nullptr;` — The aligned pointer for our atomic data.
- L43 _private member_ `SIZE_T Current = 0;` — The current index to be processed.
- L46 _private member_ `std::atomic_flag Acquired = ATOMIC_FLAG_INIT;` — Atomic flag to control ownership of consumer.
- L49 _public function_ `explicit FMeshMapBakerQueue(SIZE_T Size) : NumSlots(Size)`
- L59 _public function_ `~FMeshMapBakerQueue()`
- L75 _public function_ `void Post(SIZE_T Idx, void* Data)` — Post Data pointer into the queue at a given index. @param Idx The slot index to update. @param Data The data to post to the queue.
- L88 _public function_ `bool AcquireProcessLock()` — Acquire ownership over processing queue data. It is the responsibility of the caller to release the ownership if it was acquired via ReleaseProcessLock(). @return true if ownership of queue processing was acquired.
- L106 _public function_ `template<bool bFlush = false> void* Process()` — Retrieve the next item in the queue to process. The current index is only advanced if the item is valid or <bFlush = true>. @param bFlush When true, increments the current index regardless of the validity of the data. Useful for flushing/clearing the contents of the queue. @return A void* to the data to be processed, nullptr if the data for the next item in the queue is not available yet.
- L126 _public function_ `void ReleaseProcessLock()` — Release ownership of queue processing. This should only be invoked by the thread that successfully acquired ownership of queue processing via AcquireProcessLock().
- L132 _public function_ `bool IsDone() const` — @return true if all items in the queue have been processed.

#### struct `UE::Geometry::FMeshMapBakerQueue::FSlotData`  
`struct alignas(Alignment) FSlotData`  
_L30-33_
- L32 _public member_ `std::atomic<void*> Ptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshMapEvaluator.h` (Public)


#### enum `UE::Geometry::EMeshMapEvaluatorType`  
`enum class EMeshMapEvaluatorType`  
_L14-26_
- L16 _public enumerator_ `Constant`
- L17 _public enumerator_ `Normal`
- L18 _public enumerator_ `Occlusion`
- L19 _public enumerator_ `Curvature`
- L20 _public enumerator_ `Property`
- L21 _public enumerator_ `ResampleImage`
- L22 _public enumerator_ `MultiResampleImage`
- L23 _public enumerator_ `RenderCapture`
- L24 _public enumerator_ `UVShell`
- L25 _public enumerator_ `Height`

#### class `UE::Geometry::FMeshMapEvaluator`  
`class FMeshMapEvaluator`  
_L28-228_
- L159 _public prototype_ `virtual ~FMeshMapEvaluator() = default;`
- L170 _public prototype_ `virtual void Setup(const FMeshBaseBaker& Baker, FEvaluationContext& Context) = 0;` — Invoked at start of bake to setup this evaluator and return an evaluation context to the baker. The evaluation context indicates to the baker how the evaluator should be invoked. See FEvaluationContext for more details. @param Baker the baker that owns this evaluator. @param Context [out] the evaluation context.
- L173 _public prototype_ `virtual const TArray<EComponents>& DataLayout() const = 0;` — @return the data layout of the evaluator
- L176 _public prototype_ `virtual EMeshMapEvaluatorType Type() const = 0;` — @return the type of evaluator.
- L185 _protected function_ `static void WriteToBuffer(float*& Out, const float Data)` — Write float data to a float buffer and increment. @param Out the target float buffer. @param Data the data to write into the buffer.
- L196 _protected function_ `static void WriteToBuffer(float*& Out, const FVector2f& Data)` — Write FVector2f data to a float buffer and increment. @param Out the target float buffer. @param Data the data to write into the buffer.
- L208 _protected function_ `static void WriteToBuffer(float*& Out, const FVector3f& Data)` — Write FVector3f data to a float buffer and increment. @param Out the target float buffer. @param Data the data to write into the buffer.
- L221 _protected function_ `static void WriteToBuffer(float*& Out, const FVector4f& Data)` — Write FVector4f data to a float buffer and increment. @param Out the target float buffer. @param Data the data to write into the buffer.

#### enum `UE::Geometry::FMeshMapEvaluator::EComponents`  
`enum class EComponents`  
_L32-38_
- desc: The number of float components of an evaluator result/target.
- L34 _public enumerator_ `Float1 = 1`
- L35 _public enumerator_ `Float2 = 2`
- L36 _public enumerator_ `Float3 = 3`
- L37 _public enumerator_ `Float4 = 4`

#### enum `UE::Geometry::FMeshMapEvaluator::EAccumulateMode`  
`enum class EAccumulateMode`  
_L41-49_
- desc: Accumulate mode informs the baker how samples should be accumulated into the buffer.
- L44 _public enumerator_ `Add` — Accumulate sample results (valid & default) into the buffer.
- L46 _public enumerator_ `Overwrite` — Overwrite the previous sample result with the new value into the buffer.
- L48 _public enumerator_ `Last` — Last mode. Used to count modes. Ensure this is always last.

#### struct `UE::Geometry::FMeshMapEvaluator::FCorrespondenceSample`  
`struct FCorrespondenceSample`  
_L52-61_
- desc: Detail to target mesh correspondence sample.
- L54 _public member_ `FMeshUVSampleInfo BaseSample;`
- L55 _public member_ `FVector3d BaseNormal = FVector3d::Zero();`
- L58 _public member_ `const void* DetailMesh = nullptr;` — The following data has an interpretation which depends on the concrete MeshMapEvaluator/IMeshBakerDetailSampler
- L59 _public member_ `int32 DetailTriID = IndexConstants::InvalidID;`
- L60 _public member_ `FVector3d DetailBaryCoords = FVector3d::Zero();`

#### struct `UE::Geometry::FMeshMapEvaluator::FEvaluationContext`  
`struct FEvaluationContext`  
_L70-157_
- desc: Evaluator context data to indicate to the baker: 1. The evaluation functions. 2. The accumulation method for data samples. 3. The number of output results/targets for this evaluator. 4. The data layout of each output result/target for this evaluator.
- L83 _public typedef_ `using EvaluateFn = void(*)(float*& Out, const FCorrespondenceSample& Sample, void* EvalData);` — Function pointer to evaluate a mesh correspondence sample into a float buffer. This function should: - assume that the size of the buffer is correct. - advance the buffer pointer by the DataLayout stride. @param Out the buffer to populate. @param Sample the detail/target mesh correspondence sample data. @param EvalData custom data pointer provided by the evaluation context.
- L84 _public member_ `EvaluateFn Evaluate = nullptr;`
- L102 _public typedef_ `using EvaluateDefaultFn = void(*)(float*& Out, void* EvalData);` — Function pointer to evaluate the default sample into a float buffer. The default sample is used: - to clear the output image on initialization. - for samples for which there is no mesh image occupancy nor correspondence. This function should: - assume that the size of the buffer is correct. - advance the buffer pointer by the DataLayout stride. @param Out the buffer to populate. @param Sample the detail/target mesh correspondence sample data. @param EvalData custom data pointer provided by the evaluation context.
- L103 _public member_ `EvaluateDefaultFn EvaluateDefault = nullptr;`
- L121 _public typedef_ `using EvaluateColorFn = void(*)(const int DataIdx, float*& In, FVector4f& Out, void* EvalData);` — Function pointer to evaluate the color representation of an evaluated sample result. This function will be invoked once per pixel after the evaluated samples have been accumulated. This function should: - assume that the size of the buffer is correct. - advance the [In] buffer pointer by the DataLayout stride. @param DataIdx the index into the DataLayout being processed. @param In the buffer containing the accumulated sample result. @param Out the output float4 color to populate @param EvalData custom data pointer provided by the evaluation context.
- L122 _public member_ `EvaluateColorFn EvaluateColor = nullptr;`
- L140 _public typedef_ `using EvaluateChannelFn = void(*)(const int DataIdx, float*& In, float& Out, void* EvalData);` — Function pointer to evaluate the single channel representation of an evaluated sample result. This function will be invoked once per pixel channel after the evaluated samples have been accumulated. This function should: - assume that the size of the buffer is correct. - advance the [In] buffer pointer by the DataLayout stride. @param DataIdx the index into the DataLayout being processed. @param In the buffer containing the accumulated sample result. @param Out the output float channel to populate @param EvalData custom data pointer provided by the evaluation context.
- L141 _public member_ `EvaluateChannelFn EvaluateChannel = nullptr;`
- L146 _public member_ `void* EvalData = nullptr;` — Define custom data to be passed to the evaluation function.
- L149 _public member_ `EAccumulateMode AccumulateMode = EAccumulateMode::Add;` — Define how the results should be accumulatd by the Baker.
- L156 _public member_ `TArray<EComponents> DataLayout;` — The data layout of this evaluator including: 1. The number of outputs. 2. The number of floats (stride) per output. [1,4]

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshNormalMapBaker.h` (Public)


#### class `UE::Geometry::FMeshNormalMapBaker`  
`class FMeshNormalMapBaker : public FMeshImageBaker`  
_L18-48_
- inherits: `FMeshImageBaker`
- L21 _public prototype_ `virtual ~FMeshNormalMapBaker() = default;`
- L27 _public member_ `const TMeshTangents<double>* BaseMeshTangents;`
- L29 _public member_ `FVector3f DefaultNormal = FVector3f(0, 0, 1);`
- L35 _public prototype_ `virtual void Bake() override;`
- L41 _public function_ `const TUniquePtr<TImageBuilder<FVector3f>>& GetResult() const`
- L43 _public function_ `TUniquePtr<TImageBuilder<FVector3f>> TakeResult()`
- L46 _protected member_ `TUniquePtr<TImageBuilder<FVector3f>> NormalsBuilder;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshNormalMapEvaluator.h` (Public)


#### class `UE::Geometry::FMeshNormalMapEvaluator`  
`class FMeshNormalMapEvaluator : public FMeshMapEvaluator`  
_L21-62_
- inherits: `FMeshMapEvaluator`
- desc: A mesh evaluator for tangent space normals.
- L25 _public prototype_ `FMeshNormalMapEvaluator() = default;`
- L26 _public prototype_ `FMeshNormalMapEvaluator(const FMeshNormalMapEvaluator&) = default;`
- L27 _public prototype_ `FMeshNormalMapEvaluator& operator=( const FMeshNormalMapEvaluator& ) = default;`
- L31 _public prototype_ `virtual void Setup(const FMeshBaseBaker& Baker, FEvaluationContext& Context) override;`
- L33 _public prototype_ `virtual const TArray<EComponents>& DataLayout() const override;`
- L35 _public function_ `virtual EMeshMapEvaluatorType Type() const override`
- L39 _public prototype_ `template <bool bUseDetailNormalMap> static void EvaluateSample(float*& Out, const FCorrespondenceSample& Sample, void* EvalData);`
- L41 _public prototype_ `static void EvaluateDefault(float*& Out, void* EvalData);`
- L43 _public prototype_ `static void EvaluateColor(const int DataIdx, float*& In, FVector4f& Out, void* EvalData);`
- L44 _public prototype_ `static void EvaluateChannel(const int DataIdx, float*& In, float& Out, void* EvalData);`
- L48 _protected member_ `const IMeshBakerDetailSampler* DetailSampler = nullptr;` — Cached data
- L50 _protected typedef_ `using FNormalTexture = IMeshBakerDetailSampler::FBakeDetailNormalTexture;`
- L51 _protected typedef_ `using FNormalTextureMap = TMap<const void*, FNormalTexture>;`
- L52 _protected member_ `FNormalTextureMap DetailNormalMaps;`
- L54 _protected member_ `bool bHasDetailNormalTextures = false;`
- L55 _protected member_ `const TMeshTangents<double>* BaseMeshTangents = nullptr;`
- L57 _protected member_ `FVector3f DefaultNormal = FVector3f::UnitZ();`
- L61 _private prototype_ `template <bool bUseDetailNormalMap> FVector3f SampleFunction(const FCorrespondenceSample& SampleData) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshOcclusionMapBaker.h` (Public)


#### enum `UE::Geometry::EOcclusionMapType`  
`enum class EOcclusionMapType : uint8`  
_L16-22_
- L18 _public enumerator_ `None = 0`
- L19 _public enumerator_ `AmbientOcclusion = 1`
- L20 _public enumerator_ `BentNormal = 2`
- L21 _public enumerator_ `All = 3`

#### class `UE::Geometry::FMeshOcclusionMapBaker`  
`class FMeshOcclusionMapBaker : public FMeshImageBaker`  
_L25-127_
- inherits: `FMeshImageBaker`
- L28 _public prototype_ `virtual ~FMeshOcclusionMapBaker() = default;`
- L34 _public member_ `const TMeshTangents<double>* BaseMeshTangents = nullptr;`
- L52 _public member_ `EOcclusionMapType OcclusionType = EOcclusionMapType::All;`
- L53 _public member_ `int32 NumOcclusionRays = 32;`
- L54 _public member_ `double MaxDistance = TNumericLimits<double>::Max();`
- L55 _public member_ `double SpreadAngle = 180.0;`
- L56 _public member_ `EDistribution Distribution = EDistribution::Cosine;`
- L59 _public member_ `double BiasAngleDeg = 15.0;` — Ambient Occlusion
- L60 _public member_ `double BlurRadius = 0.0;`
- L63 _public member_ `ESpace NormalSpace = ESpace::Tangent;` — Bent Normal
- L70 _public prototype_ `virtual void Bake() override;`
- L82 _public function_ `const TUniquePtr<TImageBuilder<FVector3f>>& GetResult(EResult Result) const`
- L96 _public function_ `TUniquePtr<TImageBuilder<FVector3f>> TakeResult(EResult Result)`
- L114 _public function_ `inline bool WantAmbientOcclusion() const`
- L119 _public function_ `inline bool WantBentNormal() const`
- L125 _protected member_ `TUniquePtr<TImageBuilder<FVector3f>> OcclusionBuilder;`
- L126 _protected member_ `TUniquePtr<TImageBuilder<FVector3f>> NormalBuilder;`

#### enum `UE::Geometry::FMeshOcclusionMapBaker::EDistribution`  
`enum class EDistribution`  
_L40-44_
- L42 _public enumerator_ `Uniform`
- L43 _public enumerator_ `Cosine`

#### enum `UE::Geometry::FMeshOcclusionMapBaker::ESpace`  
`enum class ESpace`  
_L46-50_
- L48 _public enumerator_ `Tangent`
- L49 _public enumerator_ `Object`

#### enum `UE::Geometry::FMeshOcclusionMapBaker::EResult`  
`enum class EResult`  
_L76-80_
- L78 _public enumerator_ `AmbientOcclusion`
- L79 _public enumerator_ `BentNormal`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)
- L23 _prototype_ `ENUM_CLASS_FLAGS(EOcclusionMapType);` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshOcclusionMapEvaluator.h` (Public)


#### enum `UE::Geometry::EMeshOcclusionMapType`  
`enum class EMeshOcclusionMapType : uint8`  
_L19-25_
- L21 _public enumerator_ `None = 0`
- L22 _public enumerator_ `AmbientOcclusion = 1`
- L23 _public enumerator_ `BentNormal = 2`
- L24 _public enumerator_ `All = 3`

#### class `UE::Geometry::FMeshOcclusionMapEvaluator`  
`class FMeshOcclusionMapEvaluator : public FMeshMapEvaluator`  
_L31-94_
- inherits: `FMeshMapEvaluator`
- desc: A mesh evaluator for occlusion data (Ambient Occlusion & Bent Normals).
- L46 _public member_ `EMeshOcclusionMapType OcclusionType = EMeshOcclusionMapType::All;`
- L47 _public member_ `int32 NumOcclusionRays = 32;`
- L48 _public member_ `double MaxDistance = TNumericLimits<double>::Max();`
- L49 _public member_ `double SpreadAngle = 180.0;`
- L50 _public member_ `EDistribution Distribution = EDistribution::Cosine;`
- L53 _public member_ `double BiasAngleDeg = 15.0;` — Ambient Occlusion
- L56 _public member_ `ESpace NormalSpace = ESpace::Tangent;` — Bent Normal
- L58 _public typedef_ `using FOcclusionTuple = TTuple<float, FVector3f>;`
- L62 _public prototype_ `virtual void Setup(const FMeshBaseBaker& Baker, FEvaluationContext& Context) override;`
- L64 _public prototype_ `virtual const TArray<EComponents>& DataLayout() const override;`
- L66 _public function_ `virtual EMeshMapEvaluatorType Type() const override`
- L70 _public prototype_ `template <EMeshOcclusionMapType OcclusionType, ESpace NormalSpace> static void EvaluateSample(float*& Out, const FCorrespondenceSample& Sample, void* EvalData);`
- L73 _public prototype_ `template <EMeshOcclusionMapType OcclusionType, ESpace NormalSpace> static void EvaluateDefault(float*& Out, void* EvalData);`
- L76 _public prototype_ `template <EMeshOcclusionMapType OcclusionType, ESpace NormalSpace> static void EvaluateColor(const int DataIdx, float*& In, FVector4f& Out, void* EvalData);`
- L79 _public prototype_ `template <EMeshOcclusionMapType OcclusionType, ESpace NormalSpace> static void EvaluateChannel(const int DataIdx, float*& In, float& Out, void* EvalData);`
- L83 _protected member_ `const IMeshBakerDetailSampler* DetailSampler = nullptr;` — Cached data
- L84 _protected member_ `const TMeshTangents<double>* BaseMeshTangents = nullptr;`
- L85 _protected member_ `double BiasDotThreshold = 0.25;`
- L86 _protected member_ `TArray<FVector3d> RayDirections;`
- L88 _protected member_ `static const FVector3d DefaultTangentNormal;`
- L89 _protected member_ `static const FVector3d DefaultObjectNormal;`
- L93 _private prototype_ `template <EMeshOcclusionMapType OcclusionType, ESpace NormalSpace> FOcclusionTuple SampleFunction(const FCorrespondenceSample& SampleData, const FVector3d& DefaultNormal);`

#### enum `UE::Geometry::FMeshOcclusionMapEvaluator::EDistribution`  
`enum class EDistribution`  
_L34-38_
- L36 _public enumerator_ `Uniform`
- L37 _public enumerator_ `Cosine`

#### enum `UE::Geometry::FMeshOcclusionMapEvaluator::ESpace`  
`enum class ESpace`  
_L40-44_
- L42 _public enumerator_ `Tangent`
- L43 _public enumerator_ `Object`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DYNAMICMESH_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)
- L26 _prototype_ `ENUM_CLASS_FLAGS(EMeshOcclusionMapType);` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshPropertyMapBaker.h` (Public)


#### enum `UE::Geometry::EMeshPropertyBakeType`  
`enum class EMeshPropertyBakeType`  
_L17-24_
- L19 _public enumerator_ `Position = 1`
- L20 _public enumerator_ `Normal = 2`
- L21 _public enumerator_ `FacetNormal = 3`
- L22 _public enumerator_ `UVPosition = 4`
- L23 _public enumerator_ `MaterialID = 5`

#### class `UE::Geometry::FMeshPropertyMapBaker`  
`class FMeshPropertyMapBaker : public FMeshImageBaker`  
_L27-54_
- inherits: `FMeshImageBaker`
- L30 _public prototype_ `virtual ~FMeshPropertyMapBaker() = default;`
- L36 _public member_ `EMeshPropertyBakeType Property = EMeshPropertyBakeType::Normal;`
- L42 _public prototype_ `virtual void Bake() override;`
- L48 _public function_ `const TUniquePtr<TImageBuilder<FVector3f>>& GetResult() const`
- L50 _public function_ `TUniquePtr<TImageBuilder<FVector3f>> TakeResult()`
- L53 _protected member_ `TUniquePtr<TImageBuilder<FVector3f>> ResultBuilder;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DYNAMICMESH_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshPropertyMapEvaluator.h` (Public)


#### enum `UE::Geometry::EMeshPropertyMapType`  
`enum class EMeshPropertyMapType`  
_L18-27_
- L20 _public enumerator_ `Position = 1`
- L21 _public enumerator_ `Normal = 2`
- L22 _public enumerator_ `FacetNormal = 3`
- L23 _public enumerator_ `UVPosition = 4`
- L24 _public enumerator_ `MaterialID = 5`
- L25 _public enumerator_ `VertexColor = 6`
- L26 _public enumerator_ `PolyGroupID = 7`

#### class `UE::Geometry::FMeshPropertyMapEvaluator`  
`class FMeshPropertyMapEvaluator : public FMeshMapEvaluator`  
_L32-101_
- inherits: `FMeshMapEvaluator`
- desc: A mesh evaluator for mesh properties as color data.
- L35 _public member_ `EMeshPropertyMapType Property = EMeshPropertyMapType::Normal;`
- L39 _public prototype_ `FMeshPropertyMapEvaluator() = default;`
- L40 _public prototype_ `FMeshPropertyMapEvaluator(const FMeshPropertyMapEvaluator&) = default;`
- L41 _public prototype_ `FMeshPropertyMapEvaluator& operator=(const FMeshPropertyMapEvaluator&) = default;`
- L45 _public prototype_ `virtual void Setup(const FMeshBaseBaker& Baker, FEvaluationContext& Context) override;`
- L47 _public prototype_ `virtual const TArray<EComponents>& DataLayout() const override;`
- L49 _public function_ `virtual EMeshMapEvaluatorType Type() const override`
- L53 _public prototype_ `template <bool bUseDetailNormalMap> static void EvaluateSample(float*& Out, const FCorrespondenceSample& Sample, void* EvalData);`
- L55 _public prototype_ `static void EvaluateDefault(float*& Out, void* EvalData);`
- L57 _public prototype_ `static void EvaluateColor(const int DataIdx, float*& In, FVector4f& Out, void* EvalData);`
- L58 _public prototype_ `static void EvaluateChannel(const int DataIdx, float*& In, float& Out, void* EvalData);`
- L61 _protected prototype_ `FVector4f GetDefaultValue(EMeshPropertyMapType InProperty) const;`
- L64 _protected member_ `const IMeshBakerDetailSampler* DetailSampler = nullptr;` — Cached data
- L66 _protected typedef_ `using FNormalTexture = IMeshBakerDetailSampler::FBakeDetailNormalTexture;`
- L67 _protected typedef_ `using FNormalTextureMap = TMap<const void*, FNormalTexture>;`
- L68 _protected member_ `FNormalTextureMap DetailNormalMaps;`
- L70 _protected member_ `bool bHasDetailNormalTextures = false;`
- L71 _protected member_ `FAxisAlignedBox3d Bounds;`
- L74 _protected member_ `FVector3f DefaultValue = FVector3f::Zero();` — `UE_DEPRECATED(5.6, "DefaultValue is deprecated. Please use GetDefaultValue() instead.")`
- L77 _private function_ `static FVector4f NormalToColor(const FVector3f Normal)`
- L82 _private function_ `static FVector4f UVToColor(const FVector2f UV)`
- L89 _private function_ `static FVector4f PositionToColor(const FVector3d Position, const FAxisAlignedBox3d SafeBounds)`
- L98 _private prototype_ `template <bool bUseDetailNormalMap> FVector4f SampleFunction(const FCorrespondenceSample& SampleData) const;`
- L100 _private member_ `FVector4f DefaultValue4f = FVector4f();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshResampleImageBaker.h` (Public)


#### class `UE::Geometry::FMeshResampleImageBaker`  
`class FMeshResampleImageBaker : public FMeshImageBaker`  
_L17-47_
- inherits: `FMeshImageBaker`
- L20 _public prototype_ `virtual ~FMeshResampleImageBaker() = default;`
- L26 _public function_ `TFunction<FVector4f(FVector2d)> SampleFunction = [](FVector2d Position)`
- L26 _public member_ `TFunction<FVector4f(FVector2d)> SampleFunction = [](FVector2d Position) { return FVector4f::Zero(); };`
- L27 _public member_ `const FDynamicMeshUVOverlay* DetailUVOverlay = nullptr;`
- L29 _public member_ `FVector4f DefaultColor = FVector4f(0, 0, 0, 1);`
- L35 _public prototype_ `virtual void Bake() override;`
- L41 _public function_ `const TUniquePtr<TImageBuilder<FVector4f>>& GetResult() const`
- L43 _public function_ `TUniquePtr<TImageBuilder<FVector4f>> TakeResult()`
- L46 _protected member_ `TUniquePtr<TImageBuilder<FVector4f>> ResultBuilder;`

#### class `UE::Geometry::FMeshMultiResampleImageBaker`  
`class FMeshMultiResampleImageBaker : public FMeshResampleImageBaker`  
_L51-63_
- inherits: `FMeshResampleImageBaker`
- L55 _public member_ `TMap<int32, TSharedPtr<UE::Geometry::TImageBuilder<FVector4f>, ESPMode::ThreadSafe>> MultiTextures;`
- L57 _public prototype_ `virtual void Bake() override;`
- L61 _protected prototype_ `void InitResult();`
- L62 _protected prototype_ `void BakeMaterial(int32 MaterialID);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DYNAMICMESH_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshResampleImageEvaluator.h` (Public)


#### class `UE::Geometry::FMeshResampleImageEvaluator`  
`class FMeshResampleImageEvaluator : public FMeshMapEvaluator`  
_L21-48_
- inherits: `FMeshMapEvaluator`
- desc: A mesh evaluator for sampling 2D texture data.
- L24 _public member_ `FVector4f DefaultColor = FVector4f(0, 0, 0, 1);`
- L28 _public prototype_ `virtual void Setup(const FMeshBaseBaker& Baker, FEvaluationContext& Context) override;`
- L30 _public prototype_ `virtual const TArray<EComponents>& DataLayout() const override;`
- L32 _public function_ `virtual EMeshMapEvaluatorType Type() const override`
- L35 _public prototype_ `static void EvaluateSample(float*& Out, const FCorrespondenceSample& Sample, void* EvalData);`
- L37 _public prototype_ `static void EvaluateDefault(float*& Out, void* EvalData);`
- L39 _public prototype_ `static void EvaluateColor(const int DataIdx, float*& In, FVector4f& Out, void* EvalData);`
- L40 _public prototype_ `static void EvaluateChannel(const int DataIdx, float*& In, float& Out, void* EvalData);`
- L44 _protected member_ `const IMeshBakerDetailSampler* DetailSampler = nullptr;` — Cached data
- L47 _private prototype_ `FVector4f ImageSampleFunction(const FCorrespondenceSample& Sample) const;`

#### class `UE::Geometry::FMeshMultiResampleImageEvaluator`  
`class FMeshMultiResampleImageEvaluator : public FMeshResampleImageEvaluator`  
_L55-78_
- inherits: `FMeshResampleImageEvaluator`
- desc: A mesh evaluator for sampling multiple 2D textures by material ID
- L59 _public member_ `TArray<TSharedPtr<UE::Geometry::TImageBuilder<FVector4f>, ESPMode::ThreadSafe>> MultiTextures;` — List of textures indexed by material ID. Entries can be null.
- L62 _public member_ `int DetailUVLayer = 0;` — The UV channel used to sample the textures.
- L66 _public prototype_ `virtual void Setup(const FMeshBaseBaker& Baker, FEvaluationContext& Context) override;`
- L68 _public function_ `virtual EMeshMapEvaluatorType Type() const override`
- L71 _public prototype_ `static void EvaluateSampleMulti(float*& Out, const FCorrespondenceSample& Sample, void* EvalData);`
- L74 _private prototype_ `FVector4f ImageSampleFunction(const FCorrespondenceSample& Sample) const;`
- L77 _private member_ `int NumMultiTextures = 0;` — Cached data

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshSurfaceSampler.h` (Public)


#### struct `UE::Geometry::FDynamicMeshUVMesh`  
`struct FDynamicMeshUVMesh`  
_L20-79_
- desc: Wrapper around a Mesh and UV Overlay that provides UVs triangles as vertices. This allows building a TMeshAABBTree3 for the UV mesh
- L22 _public member_ `const FDynamicMesh3* Mesh = nullptr;`
- L23 _public member_ `const FDynamicMeshUVOverlay* UV = nullptr;`
- L25 _public function_ `inline bool IsTriangle(int32 TriangleIndex) const`
- L30 _public function_ `inline bool IsVertex(int32 VertexIndex) const`
- L35 _public function_ `inline int32 MaxTriangleID() const`
- L40 _public function_ `inline int32 TriangleCount() const`
- L45 _public function_ `inline int32 MaxVertexID() const`
- L50 _public function_ `inline int32 VertexCount() const`
- L55 _public function_ `inline uint64 GetChangeStamp() const`
- L60 _public function_ `inline FIndex3i GetTriangle(int32 TriangleIndex) const`
- L65 _public function_ `inline FVector3d GetVertex(int32 ElementIndex) const`
- L72 _public function_ `template<typename VecType> inline void GetTriVertices(int32 TriangleIndex, VecType& V0, VecType& V1, VecType& V2) const`

#### struct `UE::Geometry::FMeshUVSampleInfo`  
`struct FMeshUVSampleInfo`  
_L85-104_
- desc: Information about a UV sample
- L88 _public member_ `int32 TriangleIndex = IndexConstants::InvalidID;` — Triangle containing the sample
- L91 _public member_ `FIndex3i MeshVertices;` — 3D vertices
- L93 _public member_ `FTriangle3d Triangle3D { FVector3d::ZeroVector, FVector3d::ZeroVector, FVector3d::ZeroVector };` — 3D triangle
- L96 _public member_ `FIndex3i UVVertices;` — UV overlay vertices
- L98 _public member_ `FTriangle2d TriangleUV { FVector2d(0.0,0.0), FVector2d(0.0,0.0), FVector2d(0.0,0.0) };` — 2D triangle
- L101 _public member_ `FVector3d BaryCoords = FVector3d::ZeroVector;` — barycentric coords in triangle
- L103 _public member_ `FVector3d SurfacePoint = FVector3d::ZeroVector;` — surface point (lying in Triangle3D)

#### enum `UE::Geometry::EMeshSurfaceSamplerQueryType`  
`enum class EMeshSurfaceSamplerQueryType : uint8`  
_L108-114_
- desc: Types of query that FMeshSurfaceUVSampler/TMeshSurfaceUVSampler supports
- L111 _public enumerator_ `UVOnly` — Query with arbitrary UV value
- L113 _public enumerator_ `TriangleAndUV` — Query with given TriangleID and UV that is assumed to lie within that Triangle

#### class `UE::Geometry::FMeshSurfaceUVSamplerFixLayout`  
`class FMeshSurfaceUVSamplerFixLayout`  
_L117-121_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L120 _public prototype_ `virtual ~FMeshSurfaceUVSamplerFixLayout() = default;`

#### class `UE::Geometry::FMeshSurfaceUVSampler`  
`class FMeshSurfaceUVSampler : public FMeshSurfaceUVSamplerFixLayout`  
_L133-170_
- inherits: `FMeshSurfaceUVSamplerFixLayout`
- desc: FMeshSurfaceUVSampler computes FMeshUVSampleInfo's on a given mesh at given UV-space positions, this info can then be used by an external function to compute some application-specific sample. Note: This class is similar to TMeshSurfaceUVSampler (the "old" class) but provides a more convenient API. This class computes the sample info and that's it. The old class computes the sample info internally but also immediately forwards it to an application-specific sampling function which must be provided as a callback and hence has a fixed signature and requires that the sample type is passed as a template parameter. Also the old class is more awkward to use when sampling multiple things, see the documentation of TMeshSurfaceUVSampler for more details.
- L143 _public prototype_ `virtual void Initialize(const FDynamicMesh3* Mesh, const FDynamicMeshUVOverlay* UVOverlay, EMeshSurfaceSamplerQueryType QueryType);` — Initialize the sampler. @param Mesh      Mesh to sample @param UVOverlay UV overlay of Mesh @param QueryType Type of query functions we will call. Some queries are simpler and do not require spatial data structures
- L150 _public prototype_ `virtual bool QuerySampleInfo(const FVector2d& UV, FMeshUVSampleInfo& SampleInfo);` — Fill in the given SampleInfo for the given UV location. @pre The Initialize function must have been called with EMeshSurfaceSamplerQueryType::UVOnly @return If the query location is not on a triangle in the Mesh then return false (SampleInfo will be invalid)
- L156 _public prototype_ `virtual bool QuerySampleInfo(int32 UVTriangleID, const FVector2d& UV, FMeshUVSampleInfo& SampleInfo);` — Fill in the given SampleInfo for the given UV location in the given UVTriangleID. @return If the query location is not on a triangle in the Mesh then return false (SampleInfo will be invalid)
- L160 _protected member_ `const FDynamicMesh3* Mesh = nullptr;`
- L161 _protected member_ `const FDynamicMeshUVOverlay* UVOverlay = nullptr;`
- L162 _protected member_ `EMeshSurfaceSamplerQueryType QueryType = EMeshSurfaceSamplerQueryType::TriangleAndUV;`
- L164 _protected member_ `bool bUVMeshSpatialInitialized = false;`
- L167 _protected member_ `FDynamicMeshUVMesh UVMeshAdapter;` — BV tree for finding triangle for a given UV. Not always initialized.
- L168 _protected member_ `TMeshAABBTree3<FDynamicMeshUVMesh> UVMeshSpatial;`
- L169 _protected prototype_ `void InitializeUVMeshSpatial();`

#### class `UE::Geometry::TMeshSurfaceUVSampler`  
`template<typename SampleType> class TMeshSurfaceUVSampler : public FMeshSurfaceUVSamplerFixLayout`  
_L189-253_
- inherits: `FMeshSurfaceUVSamplerFixLayout`
- desc: Consider using FMeshSurfaceUVSampler instead, it is more flexible and easier to understand! TMeshSurfaceUVSampler computes point samples of the given SampleType at positions on the mesh based on UV-space positions. The standard use case for this class is to compute samples used in building Normal Maps, AO Maps, etc. Note that for UVOnly sample type, an internal UV-space BVTree will be constructed, and each sample will query that to find the UV/3D correspondence. If you already know the TriangleID, you can use the TriangleAndUV type to avoid the BVTree construction and queries. Note that if you need to sample multiple things, rather than building up an uber-SampleType, you can first compute a sample with SampleType=FMeshUVSampleInfo to find the correspondence information, and then construction additional samplers of type EMeshSurfaceSamplerQueryType::TriangleAndUV, and call CachedSampleUV(), to avoid expensive BVTree constructions and UV-to-3D recalculation.
- L201 _public function_ `virtual void Initialize( const FDynamicMesh3* MeshIn, const FDynamicMeshUVOverlay* UVOverlayIn, EMeshSurfaceSamplerQueryType QueryTypeIn, SampleType ZeroValueIn, TUniqueFunction<void(const FMeshUVSampleInfo& SampleInfo, SampleType& SampleValueOut)> SampleValueFunctionIn)` — Configure the sampler. @param MeshIn mesh to sample @param UVOverlayIn UV overlay of MeshIn to sample @param QueryTypeIn type of query functions we will call. Some queries are simpler and do not require spatial data structures. @param ZeroValueIn the value that is returned if a sample cannot be found @param SampleValueFunctionIn This function is called to compute the sample at a given UV location. SampleInfo provides the necessary UV/3D correspondence data.
- L225 _public prototype_ `virtual bool SampleUV(const FVector2d& UV, SampleType& ResultOut);` — Compute a sample at the given UV location @return true if valid sample was computed
- L231 _public prototype_ `virtual bool SampleUV(int32 UVTriangleID, const FVector2d& UV, SampleType& ResultOut);` — Compute a sample at the given UV location in the given Triangle @return true if valid sample was computed
- L237 _public prototype_ `virtual bool CachedSampleUV(const FMeshUVSampleInfo& CachedSampleInfo, SampleType& ResultOut);` — Compute a sample at the given UV/3D location specified by CachedSampleInfo, which presumably was produced by previous calls to SampleUV() @return true if valid sample was computed
- L240 _protected member_ `EMeshSurfaceSamplerQueryType QueryType = EMeshSurfaceSamplerQueryType::TriangleAndUV;`
- L241 _protected member_ `bool bUVSpatialValid = false;`
- L242 _protected member_ `const FDynamicMesh3* Mesh = nullptr;`
- L243 _protected member_ `const FDynamicMeshUVOverlay* UVOverlay = nullptr;`
- L245 _protected member_ `TUniqueFunction<void(const FMeshUVSampleInfo& SampleInfo, SampleType& SampleValueOut)> ValueFunction;`
- L247 _protected member_ `SampleType ZeroValue;`
- L250 _protected member_ `FDynamicMeshUVMesh UVMeshAdapter;` — BV tree for finding triangle for a given UV. Not always initialized.
- L251 _protected member_ `TMeshAABBTree3<FDynamicMeshUVMesh> UVBVTree;`
- L252 _protected prototype_ `void InitializeBVTree();`
- L258 _function_ `template<typename SampleType> void TMeshSurfaceUVSampler<SampleType>::InitializeBVTree()`
- L277 _function_ `template<typename SampleType> bool TMeshSurfaceUVSampler<SampleType>::SampleUV(const FVector2d& UV, SampleType& ResultOut)`
- L292 _function_ `template<typename SampleType> bool TMeshSurfaceUVSampler<SampleType>::SampleUV(int32 UVTriangleID, const FVector2d& UV, SampleType& ResultOut)`
- L328 _function_ `template<typename SampleType> bool TMeshSurfaceUVSampler<SampleType>::CachedSampleUV(const FMeshUVSampleInfo& CachedSampleInfo, SampleType& ResultOut)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshUVShellMapEvaluator.h` (Public)


#### class `UE::Geometry::FMeshUVShellMapEvaluator`  
`class FMeshUVShellMapEvaluator : public FMeshMapEvaluator`  
_L18-57_
- inherits: `FMeshMapEvaluator`
- desc: A mesh evaluator for mesh properties as color data.
- L21 _public member_ `FVector2d TexelSize = FVector2d::One();`
- L22 _public member_ `float WireframeThickness = 1.0f;`
- L23 _public member_ `FVector4f WireframeColor = FLinearColor::Blue;`
- L24 _public member_ `FVector4f ShellColor = FLinearColor::Gray;`
- L25 _public member_ `FVector4f BackgroundColor = FVector4f(0.0f, 0.0f, 0.0f, 0.0f);`
- L27 _public member_ `int UVLayer = 0;`
- L31 _public prototype_ `FMeshUVShellMapEvaluator() = default;`
- L32 _public prototype_ `FMeshUVShellMapEvaluator(const FMeshUVShellMapEvaluator&) = default;`
- L33 _public prototype_ `FMeshUVShellMapEvaluator& operator=(const FMeshUVShellMapEvaluator&) = default;`
- L37 _public prototype_ `virtual void Setup(const FMeshBaseBaker& Baker, FEvaluationContext& Context) override;`
- L39 _public prototype_ `virtual const TArray<EComponents>& DataLayout() const override;`
- L41 _public function_ `virtual EMeshMapEvaluatorType Type() const override`
- L44 _public prototype_ `static void EvaluateSample(float*& Out, const FCorrespondenceSample& Sample, void* EvalData);`
- L46 _public prototype_ `static void EvaluateDefault(float*& Out, void* EvalData);`
- L48 _public prototype_ `static void EvaluateColor(const int DataIdx, float*& In, FVector4f& Out, void* EvalData);`
- L49 _public prototype_ `static void EvaluateChannel(const int DataIdx, float*& In, float& Out, void* EvalData);`
- L53 _protected member_ `const IMeshBakerDetailSampler* DetailSampler = nullptr;` — Cached data
- L56 _private prototype_ `FVector4f SampleFunction(const FCorrespondenceSample& SampleData) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/MeshVertexBaker.h` (Public)


#### class `UE::Geometry::FMeshVertexBaker`  
`class FMeshVertexBaker : public FMeshBaseBaker`  
_L18-91_
- inherits: `FMeshBaseBaker`
- L27 _public member_ `EBakeMode BakeMode = EBakeMode::RGBA;`
- L30 _public member_ `TSharedPtr<FMeshMapEvaluator, ESPMode::ThreadSafe> ColorEvaluator;` — Evaluator to use for full color bakes
- L33 _public member_ `TSharedPtr<FMeshMapEvaluator, ESPMode::ThreadSafe> ChannelEvaluators[4];` — Evaluators to use for per channel (RGBA) bakes
- L38 _public member_ `double TotalBakeDuration = 0.0;` — Analytics
- L46 _public prototype_ `void Bake();` — Process all bakers to generate the image result.
- L49 _public prototype_ `const TImageBuilder<FVector4f>* GetBakeResult() const;` — @return the bake result image.
- L52 _public function_ `TFunction<bool(void)> CancelF = []()` — if this function returns true, we should abort calculation
- L52 _public member_ `TFunction<bool(void)> CancelF = []() { return false; };` — if this function returns true, we should abort calculation
- L61 _protected prototype_ `template<EBakeMode ComputeMode> static void BakeImpl(void* Data);` — Template bake implementation.
- L64 _protected member_ `const bool bParallel = true;`
- L67 _protected member_ `FImageDimensions Dimensions;` — Internally cached image dimensions proportional to the number of unique vertex color elements.
- L70 _protected member_ `TUniquePtr<TImageBuilder<FVector4f>> BakeResult;` — Bake output image.
- L73 _protected member_ `TArray<FMeshMapEvaluator*> Bakers;` — Internal list of bake evaluators.
- L76 _protected member_ `TArray<FMeshMapEvaluator::FEvaluationContext> BakeContexts;` — Evaluation contexts for each mesh evaluator.
- L79 _protected member_ `FVector4f BakeDefaults;` — Internal cached default bake data.
- L82 _protected member_ `int32 BakeSampleBufferSize = 0;` — The total size of the temporary float buffer for BakeSample.
- L85 _protected typedef_ `using BakeFn = void(*)(void* Data);` — Function pointer to internal bake implementation.
- L86 _protected member_ `BakeFn BakeInternal = nullptr;`
- L89 _protected member_ `static FMeshConstantMapEvaluator ZeroEvaluator;` — Constant evaluator for empty channels.
- L90 _protected member_ `static FMeshConstantMapEvaluator OneEvaluator;`

#### enum `UE::Geometry::FMeshVertexBaker::EBakeMode`  
`enum class EBakeMode`  
_L21-25_
- L23 _public enumerator_ `RGBA` — Bake color data to RGBA
- L24 _public enumerator_ `PerChannel` — Bake scalar data into color channels

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Sampling/RenderCaptureMapEvaluator.h` (Public)


#### enum `UE::Geometry::ERenderCaptureChannel`  
`enum class ERenderCaptureChannel`  
_L13-25_
- desc: TODO Consolidate this with ERenderCaptureType
- L15 _public enumerator_ `BaseColor = 1`
- L16 _public enumerator_ `Roughness = 2`
- L17 _public enumerator_ `Metallic = 4`
- L18 _public enumerator_ `Specular = 8`
- L19 _public enumerator_ `Emissive = 16`
- L20 _public enumerator_ `WorldNormal = 32`
- L21 _public enumerator_ `DeviceDepth = 64`
- L22 _public enumerator_ `CombinedMRS = 128`
- L23 _public enumerator_ `Opacity = 256`
- L24 _public enumerator_ `SubsurfaceColor = 512`

#### class `UE::Geometry::FRenderCaptureMapEvaluator`  
`template <typename DataType> class FRenderCaptureMapEvaluator : public FMeshMapEvaluator`  
_L28-83_
- inherits: `FMeshMapEvaluator`
- L32 _public member_ `ERenderCaptureChannel Channel = ERenderCaptureChannel::BaseColor;`
- L37 _public member_ `DataType DefaultResult;`
- L38 _public member_ `TFunction<DataType(const FCorrespondenceSample& Sample)> EvaluateSampleCallback;`
- L39 _public member_ `TFunction<FVector4f(const int DataIdx, float*& In)> EvaluateColorCallback;`
- L42 _public prototype_ `virtual ~FRenderCaptureMapEvaluator() = default;`
- L45 _public function_ `virtual void Setup(const FMeshBaseBaker& Baker, FEvaluationContext& Context) override`
- L55 _public function_ `virtual const TArray<EComponents>& DataLayout() const override`
- L62 _public function_ `virtual EMeshMapEvaluatorType Type() const override`
- L65 _public function_ `static void EvaluateSample(float*& Out, const FCorrespondenceSample& Sample, void* EvalData)`
- L72 _public function_ `static void EvaluateDefault(float*& Out, void* EvalData)`
- L78 _public function_ `static void EvaluateColor(const int DataIdx, float*& In, FVector4f& Out, void* EvalData)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Selections/GeometrySelection.h` (Public)


#### struct `UE::Geometry::FGeoSelectionID`  
`struct FGeoSelectionID`  
_L31-106_
- desc: FGeoSelectionID provides a pair of 32-bit unsigned integers that can be packed into a 64-bit unsigned integer for use with FGeometrySelection. This is generally intended to be used to encode a mesh geometry ID (eg TriangleID, EdgeID, VertexID) combined with a "Topology ID", eg something like a Face Group ID. However none of this is enforced and so a caller can use these two integers for any purpose. Note that since the ints are unsigned, IndexConstants::InvalidID is not directly representable (-1 will become positive 0xFFFFFFFF).
- L34 _public member_ `uint32 TopologyID;` — Topology ID, stored in upper 32 bits when packed into 64-bits
- L36 _public member_ `uint32 GeometryID;` — Geometry ID, stored in lower 32 bits when packed into 64-bits
- L38 _public function_ `FGeoSelectionID()`
- L47 _public function_ `explicit FGeoSelectionID(uint32 GeometryIDIn, uint32 TopologyIDIn = 0)` — Initialize the TopologyID and GeometryID with the given values
- L56 _public function_ `explicit FGeoSelectionID(uint64 EncodedID)` — Initialize the TopologyID and GeometryID by unpacking the 64-bit packed EncodedID
- L65 _public function_ `uint64 Encoded() const` — @return the packed 64-bit representation of [TopologyID, GeometryID]
- L73 _public function_ `static FGeoSelectionID MeshTriangle(int32 TriangleID)` — @return a FGeoSelectionID initialized with the given TriangleID, and a TopologyID of 0
- L81 _public function_ `static FGeoSelectionID MeshVertex(int32 VertexID)` — @return a FGeoSelectionID initialized with the given VertexID, and a TopologyID of 0
- L89 _public function_ `static FGeoSelectionID MeshEdge(UE::Geometry::FMeshTriEdgeID EdgeKey)` — @return a FGeoSelectionID initialized with the given 32-bit encoding of the MeshTriEdgeID, and a TopologyID of 0
- L97 _public function_ `static FGeoSelectionID GroupFace(int32 TriangleID, int32 GroupID)` — @return a FGeoSelectionID initialized with the given TriangleID and GroupID used as the TopologyID

#### enum `UE::Geometry::EGeometryElementType`  
`enum class EGeometryElementType`  
_L114-122_
- desc: Type of selected Elements in a FGeometrySelection
- L117 _public enumerator_ `Vertex = 1` — Mesh Vertices, Polygroup Corners, ...
- L119 _public enumerator_ `Edge = 2` — Mesh Edges, Polygroup Edges, ...
- L121 _public enumerator_ `Face = 4` — Mesh Triangles, Polygroup Faces, ...

#### enum `UE::Geometry::EGeometryTopologyType`  
`enum class EGeometryTopologyType`  
_L127-131_
- desc: Type of selected Topology in a FGeometrySelection.
- L129 _public enumerator_ `Triangle = 1`
- L130 _public enumerator_ `Polygroup = 2`

#### struct `UE::Geometry::FGeometrySelection`  
`struct FGeometrySelection`  
_L141-218_
- desc: FGeometrySelection represents a subset of geometric elements of a larger object, for example a Mesh (currently the only use case). The main selection is represented via 64-bit unsigned integers. The integers are stored in a TSet for efficient unique adds and removals. No assumptions are made about the values, they could be (eg) mesh indices, IDs of some type, or even pointer values.
- L144 _public member_ `EGeometryElementType ElementType = EGeometryElementType::Face;` — Type of geometric element represented by this selection, if applicable
- L147 _public member_ `EGeometryTopologyType TopologyType = EGeometryTopologyType::Triangle;` — Type of geometric topology this selection is defined relative to, if applicable
- L150 _public member_ `TSet<uint64> Selection;` — Set of selected items/elements
- L153 _public member_ `TMap<uint64, double> SoftSelectedVertices;` — Map of soft selected vertices and their weights
- L158 _public function_ `bool IsEmpty() const` — @return true if Selection is empty
- L166 _public function_ `int32 Num() const` — @return number of elements in Selection
- L174 _public function_ `void Reset()` — Clear the Selection (may not release memory)
- L182 _public function_ `void InitializeTypes(EGeometryElementType ElementTypeIn, EGeometryTopologyType TopologyTypeIn)` — Initialize the Element and Topology types for this Selection
- L191 _public function_ `void InitializeTypes(const FGeometrySelection& FromSelection)` — Initialize the Element and Topology types for this Selection based on another Selection
- L200 _public function_ `bool IsSameType(const FGeometrySelection& OtherSelection) const` — @return true if the two selections have the same type
- L208 _public function_ `FGeometrySelection GetSoftSelectedVertices() const` — @return a FGeometrySelection containing the soft selected vertices

#### struct `UE::Geometry::FGeometrySelectionHitQueryConfig`  
`struct FGeometrySelectionHitQueryConfig`  
_L225-240_
- desc: FGeometrySelectionHitQueryConfig defines the desired settings for a "hit query" on selected meshes/objects.
- L228 _public member_ `EGeometryTopologyType TopologyType = EGeometryTopologyType::Polygroup;` — Type of object topology to query
- L230 _public member_ `EGeometryElementType ElementType = EGeometryElementType::Face;` — Type of object topological element to query
- L233 _public member_ `bool bOnlyVisible = true;` — If true, only "visible" elements are considered, otherwise query may return obscured elements (eg, hidden edges occluded by mesh surface)
- L239 _public member_ `bool bHitBackFaces = false;` — When false, triangles that are facing away from the camera are not considered. This can be useful when working with inside-out meshes, where we usually want to select the farther, visible wall.

#### enum `UE::Geometry::EGeometrySelectionChangeType`  
`enum class EGeometrySelectionChangeType`  
_L247-255_
- desc: Type of change, relative to a FGeometrySelection
- L250 _public enumerator_ `Add` — Elements Added to Selection
- L252 _public enumerator_ `Remove` — Elements Removed from Selection
- L254 _public enumerator_ `Replace` — Selected Elements replaced with a new set of Selected Elements

#### struct `UE::Geometry::FGeometrySelectionUpdateConfig`  
`struct FGeometrySelectionUpdateConfig`  
_L263-266_
- desc: FGeometrySelectionUpdateConfig is passed to various Selection Editing functions/classes to indicate what type of change should be applied to a FGeometrySelection (based on additional parameters, generally)
- L265 _public member_ `EGeometrySelectionChangeType ChangeType = EGeometrySelectionChangeType::Add;`

#### struct `UE::Geometry::FGeometrySelectionDelta`  
`struct FGeometrySelectionDelta`  
_L276-289_
- desc: FGeometrySelectionDelta represents a change to the set of elements in a FGeometrySelection. The delta is ordered, ie if the Delta was to be re-applied, the Removed elements should be removed before the Added elements are added. (Currently there is no way to swap the order)
- L281 _public member_ `TArray<uint64> Removed;` — Elements removed from a FGeometrySelection during some selection edit
- L285 _public member_ `TArray<uint64> Added;` — Elements added to a FGeometrySelection during some selection edit
- L288 _public function_ `bool IsEmpty() const` — @return true if the Delta is empty (nothing Removed or Added)

#### struct `UE::Geometry::FGeometrySelectionBounds`  
`struct FGeometrySelectionBounds`  
_L296-299_
- desc: 3D Bounding information for a FGeometrySelection
- L298 _public member_ `UE::Geometry::FAxisAlignedBox3d WorldBounds = UE::Geometry::FAxisAlignedBox3d::Empty();`

#### struct `UE::Geometry::FGeometrySelectionElements`  
`struct FGeometrySelectionElements`  
_L306-318_
- desc: 3D Geometry representing a FGeometrySelection, for example suitable for passing to rendering code, etc
- L308 _public member_ `TArray<UE::Geometry::FTriangle3d> Triangles;`
- L309 _public member_ `TArray<UE::Geometry::FSegment3d> Segments;`
- L310 _public member_ `TArray<FVector3d> Points;`
- L312 _public function_ `void Reset()`

#### struct `UE::Geometry::FGeometrySelectionUpdateResult`  
`struct FGeometrySelectionUpdateResult`  
_L321-327_
- L323 _public member_ `bool bSelectionMissed = false;`
- L324 _public member_ `bool bSelectionModified = false;`
- L326 _public member_ `FGeometrySelectionDelta SelectionDelta;`

#### class `UE::Geometry::FGeometrySelectionEditor`  
`class FGeometrySelectionEditor`  
_L346-449_
- desc: FGeometrySelectionEditor is a utility/helper class used for modifying a FGeometrySelection. The various functions can be used to add or remove to the Selection, while also tracking what changed, returned via FGeometrySelectionDelta structs. In some cases (eg Polygroup selections on faces and edges), only the TopologyIDs are unique, and the same TopologyID may be paired with an arbitrary TriangleID/EdgeID. FGeometrySelection is currently not aware of this distinction, however it means when (for example) adding to a selection, a new uint64 ID should only be added if the TopologyID is unique, ie the ElementID bit should be ignored. FGeometrySelectionEditor can do this, by enabling TopologyIDFiltering in the various setup/config functions. Note, however, this means that FGeometrySelectionEditor.IsSelected() must be used to determine whether an ID is selected, rather than Selection.Contains()
- L353 _public prototype_ `void Initialize( FGeometrySelection* TargetSelectionIn, const FGeometrySelectionHitQueryConfig& QueryConfigIn, bool bEnableTopologyIDFiltering);` — Initialize the Editor with the given Selection. The TargetSelectionIn must live longer than the FGeometrySelectionEditor
- L362 _public prototype_ `void Initialize( FGeometrySelection* TargetSelectionIn, bool bEnableTopologyIDFiltering);` — Initialize the Editor with the given Selection. The TargetSelectionIn must live longer than the FGeometrySelectionEditor
- L367 _public function_ `EGeometryElementType GetElementType() const` — @return the Element Type of the Target Selection
- L369 _public function_ `EGeometryTopologyType GetTopologyType() const` — @return the Topology Type of the Target Selection
- L372 _public function_ `const FGeometrySelectionHitQueryConfig& GetQueryConfig() const` — @return the active configuration for this Selection Editor, eg what type of element/topology is being selected. This is redundant w/ the above fields.
- L374 _public function_ `bool GetIsTopologyIDFilteringEnabled() const`
- L381 _public prototype_ `void UpdateQueryConfig(const FGeometrySelectionHitQueryConfig& NewConfig, bool bEnableTopologyIDFilteringIn);` — Update the active QueryConfig for this SelectionEditor. This is necessary to keep it in sync w/ the TargetSelection, if the ElementType or TopologyType are modified. This perhaps should be revisited as they basically always need to be the same...
- L384 _public prototype_ `bool IsSelected(uint64 ID) const;` — @return true if the given ID is currently selected in the Target Selection
- L387 _public prototype_ `void ClearSelection(FGeometrySelectionDelta& DeltaOut);` — Clear the Target Selection and return change information in DeltaOut
- L390 _public prototype_ `bool RemoveFromSelection(uint64 ID);` — Remove ID from Selection
- L393 _public function_ `const FGeometrySelection& GetSelection() const` — Access the Selection object this Editor is modifying
- L396 _public function_ `bool Select(uint64 ID)` — Add the items to the Target Selection
- L408 _public function_ `template<typename ListType> bool Select(const ListType& List, FGeometrySelectionDelta& DeltaOut)` — Add the items in the List to the Target Selection and return change information in DeltaOut
- L425 _public function_ `template<typename ListType> bool Deselect(const ListType& List, FGeometrySelectionDelta& DeltaOut)` — Remove the items in the List from the Target Selection and return change information in DeltaOut
- L440 _public prototype_ `bool Replace(const FGeometrySelection& NewSelection, FGeometrySelectionDelta& DeltaOut);` — Replace the current set of selected items with those in the NewSelection, and return change information in DeltaOut
- L444 _protected member_ `FGeometrySelection* TargetSelection = nullptr;`
- L445 _protected member_ `FGeometrySelectionHitQueryConfig QueryConfig;`
- L447 _protected member_ `bool bEnableTopologyIDFiltering = false;`
- L448 _protected prototype_ `uint64 RemapToExistingTopologyID(uint64 ID, bool& bFoundOut) const;`

#### class `UE::Geometry::FGeometrySelectionPreview`  
`class FGeometrySelectionPreview : public FGeometrySelectionEditor`  
_L459-471_
- inherits: `FGeometrySelectionEditor`
- desc: FGeometrySelectionPreview is a combined FGeometrySelection and FGeometrySelectionEditor. The purpose of this class is to support things like hover-highlighting, where the Selection system needs to be queried but the result is going to be discarded. FGeometrySelectionPreview can only be constructed based on a parent FGeometrySelectionEditor, from which it derives it's configuration, which is then how the rest of the system knows what geometry to provide as a preview/etc
- L462 _public member_ `FGeometrySelection PreviewSelection;`
- L464 _public function_ `FGeometrySelectionPreview(const FGeometrySelectionEditor& ActiveEditor)`
- L470 _public function_ `bool IsEmpty() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DYNAMICMESH_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)
- L102 _function_ `friend uint32 GetTypeHash(const FGeoSelectionID& TopoKey)` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Selections/GeometrySelectionUtil.h` (Public)


#### enum `UE::Geometry::EEnumerateSelectionMapping`  
`enum class EEnumerateSelectionMapping : uint8`  
_L22-30_
- L24 _public enumerator_ `None = 0`
- L26 _public enumerator_ `FacesToFaces = 1 << 0`
- L27 _public enumerator_ `FacesToEdges = 1 << 1`
- L29 _public enumerator_ `Default = FacesToFaces`

#### enum `UE::Geometry::EEnumerateSelectionConversionParams`  
`enum class EEnumerateSelectionConversionParams`  
_L33-39_
- L36 _public enumerator_ `ContainSelection` — Converts to components whose constituent parts are all contained in the initial selection.
- L38 _public enumerator_ `ExpandSelection` — Converts to components where any of its constituent parts are included in the initial selection.

#### enum `UE::Geometry::EGeometrySelectionCombineModes`  
`enum class EGeometrySelectionCombineModes : uint8`  
_L546-551_
- L548 _public enumerator_ `Add`
- L549 _public enumerator_ `Subtract`
- L550 _public enumerator_ `Intersection`

#### Free symbols / members of external scopes

- L11 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L31 _prototype_ `ENUM_CLASS_FLAGS(EEnumerateSelectionMapping);` (scope `UE::Geometry`)
- L46 _prototype_ `bool AreSelectionsIdentical( const FGeometrySelection& SelectionA, const FGeometrySelection& SelectionB);` (scope `UE::Geometry`) — Test if SelectionA and SelectionB are the same selection. This is currently relatively expensive on Polygroup selections due to how they are encoded @return true if the selections are iddentical
- L58 _prototype_ `bool FindInSelectionByTopologyID( const FGeometrySelection& GeometrySelection, uint32 TopologyID, uint64& FoundValue);` (scope `UE::Geometry`) — Assuming that the uint64 values in the GeometrySelection are encoded FGeoSelectionID's, find the item that has a matching TopologyID, ignoring the GeometryID. @param FoundValue the hash value found @return true if an item was found
- L70 _prototype_ `void UpdateTriangleSelectionViaRaycast( const FColliderMesh* ColliderMesh, FGeometrySelectionEditor* Editor, const FRay3d& LocalRay, const FGeometrySelectionUpdateConfig& UpdateConfig, FGeometrySelectionUpdateResult& ResultOut);` (scope `UE::Geometry`) — Update a FGeometrySelection (via the Editor) of mesh vertices/edges/triangles based on a raycast @param UpdateConfig type of update (add/remove/replace) and other update controls @param ResultOut selection delta and information on hit/miss are returned here
- L83 _prototype_ `void UpdateGroupSelectionViaRaycast( const FColliderMesh* ColliderMesh, const FGroupTopology* GroupTopology, FGeometrySelectionEditor* Editor, const FRay3d& LocalRay, const FGeometrySelectionUpdateConfig& UpdateConfig, FGeometrySelectionUpdateResult& ResultOut);` (scope `UE::Geometry`) — Update a FGeometrySelection (via the Editor) of mesh polygroup faces/edges/corners, based on a raycast @param UpdateConfig type of update (add/remove/replace) and other update controls @param ResultOut selection delta and information on hit/miss are returned here
- L98 _prototype_ `bool UpdateSelectionWithNewElements( FGeometrySelectionEditor* Editor, EGeometrySelectionChangeType ChangeType, const TArray<uint64>& NewIDs, FGeometrySelectionDelta* DeltaOut = nullptr);` (scope `UE::Geometry`) — Update a FGeometrySelection (via the Editor) @param ChangeType type of change to make (add/remove/replace) @param NewIDs set of new IDs to use to update the selection @param Delta selection delta will be stored here, if non-nullptr is provided
- L110 _prototype_ `bool EnumerateTriangleSelectionVertices( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, const FTransform& ApplyTransform, TFunctionRef<void(uint64, const FVector3d&)> VertexFunc );` (scope `UE::Geometry`) — `UE_DEPRECATED(5.5, "EnumerateTriangleSelectionVertices with ApplyTransform passed a reference is deprecated. " "Please use the function of the same name which takes ApplyTransform as a pointer instead")` — Prefer pointer version for ApplyTransform in EnumerateTriangleSelectionVertices
- L125 _prototype_ `bool EnumerateTriangleSelectionVertices( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, const FTransform* ApplyTransform, TFunctionRef<void(uint64, const FVector3d&)> VertexFunc );` (scope `UE::Geometry`) — Call VertexFunc for each selected Mesh element (vertex/edge/tri) in MeshSelection. ApplyTransform will be applied to Vertex Positions before calling VertexFunc For Triangles: includes all 3 points which make up each selected triangle For Edges: includes both vertex endpoints of each selected edge For Vertices: includes each selected vertex
- L143 _prototype_ `bool EnumeratePolygroupSelectionVertices( const FGeometrySelection& GroupSelection, const UE::Geometry::FDynamicMesh3& Mesh, const FGroupTopology* GroupTopology, const FTransform& ApplyTransform, TFunctionRef<void(uint64, const FVector3d&)> VertexFunc );` (scope `UE::Geometry`) — Call VertexFunc for each selected Mesh element (vertex/edge/tri) in the set of polygroup faces/edges/corners specified by GroupSelection (relative to GroupTopology parameter) ApplyTransform will be applied to Vertex Positions before calling VertexFunc For Faces: enumerates all vertices in the selected polygroup(s), including internal, non-Corner vertices For Edges/Boundaries: enumerates the TriVerts which make up the selected PolyEdge(s) For Verts/Corners: returns the TriVert that corresponds to the selected Corner(s) For rendering purposes, use EnumeratePolygroupSelectionElements
- L159 _prototype_ `bool EnumerateSelectionTriangles( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, TFunctionRef<void(int32)> TriangleFunc, const UE::Geometry::FPolygroupSet* UseGroupSet = nullptr );` (scope `UE::Geometry`) — Call TriangleFunc for each mesh TriangleID included in MeshSelection. TriangleFunc may be called multiple times for the same TriangleID. This will forward to EnumerateTriangleSelectionTriangles() or EnumeratePolygroupSelectionTriangles() depending on the selection topology type. If UseGroupSet and MeshSelection is for polygroups, the default Mesh group layer will be used.
- L170 _prototype_ `bool EnumerateTriangleSelectionTriangles( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, TFunctionRef<void(int32)> TriangleFunc );` (scope `UE::Geometry`) — Call TriangleFunc for each mesh TriangleID included in MeshSelection. For Edges, both connected edges are included. For Vertices, all triangles in the vertex one-ring are included.
- L181 _prototype_ `bool EnumeratePolygroupSelectionTriangles( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, const UE::Geometry::FPolygroupSet& GroupSet, TFunctionRef<void(int32)> TriangleFunc );` (scope `UE::Geometry`) — Call TriangleFunc for each mesh TriangleID included in MeshSelection, where MeshSelection has polygroup topology. For Polygroup Faces, all triangles in the face are included. For Polygroup Edges, currently all triangles in any group adjacent to the edge For Polygroup Corners, currently all triangles in any group touching the corner
- L195 _prototype_ `bool EnumerateSelectionEdges( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, TFunctionRef<void(int32)> EdgeFunc, const UE::Geometry::FPolygroupSet* UseGroupSet = nullptr );` (scope `UE::Geometry`) — Call EdgeFunc for each mesh EdgeID included in MeshSelection. EdgeFunc may be called multiple times for the same EdgeID. This will forward to EnumerateTriangleSelectionEdges() or EnumeratePolygroupSelectionEdges() depending on the selection topology type. If UseGroupSet and MeshSelection is for polygroups, the default Mesh group layer will be used. For polygroups - all edges and vertices within the polygroup are included, not exclusively Group Boundaries or Group Corners
- L207 _prototype_ `bool EnumerateTriangleSelectionEdges( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, TFunctionRef<void(int32)> EdgeFunc );` (scope `UE::Geometry`) — Call EdgeFunc for each mesh EdgeID included in MeshSelection. For Triangles, all 3 edges are included. For Edges, all selected edges are included For Vertices, all edges touching each selected vertex are included.
- L220 _prototype_ `bool EnumeratePolygroupSelectionEdges( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, const UE::Geometry::FPolygroupSet& GroupSet, TFunctionRef<void(int32)> EdgeFunc );` (scope `UE::Geometry`) — Call EdgeFunc for each mesh EdgeID included in MeshSelection, where MeshSelection has polygroup topology. For Polygroup Faces, all edges (including internal, non-border edges) in the polygroup are included. For Polygroup Borders, includes all mesh edges which are a part of the selected GroupEdge(s)/BorderEdge(s) For Polygroup Corners, includes all mesh edges in all GroupEdge(s) which touch the selected Corner(s) For rendering purposes, use EnumeratePolygroupSelectionElements
- L235 _prototype_ `bool EnumeratePolygroupSelectionEdges( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, const UE::Geometry::FGroupTopology& GroupTopology, TFunctionRef<void(int32)> EdgeFunc );` (scope `UE::Geometry`) — Version of EnumeratePolygroupSelectionEdges which uses GroupTopology Call EdgeFunc for each mesh EdgeID included in MeshSelection, where MeshSelection has polygroup topology. For Polygroup Faces, all edges (including internal, non-border edges) in the polygroup are included. For Polygroup Borders, includes all mesh edges which are a part of the selected GroupEdge(s)/BorderEdge(s) For Polygroup Corners, includes all mesh edges in all GroupEdge(s) which touch the selected Corner(s)
- L243 _prototype_ `bool EnumerateTriangleSelectionElements( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, TFunctionRef<void(int32, const FVector3d&)> VertexFunc, TFunctionRef<void(int32, const FSegment3d&)> EdgeFunc, TFunctionRef<void(int32, const FTriangle3d&)> TriangleFunc, const FTransform* ApplyTransform = nullptr, const bool bMapFacesToEdgeLoops = false );` (scope `UE::Geometry`) — Prefer EnumerateTriangleSelectionElements with Flags parameter.
- L281 _prototype_ `bool EnumeratePolygroupSelectionElements( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, const FGroupTopology* GroupTopology, TFunctionRef<void(int32, const FVector3d&)> VertexFunc, TFunctionRef<void(int32, const FSegment3d&)> EdgeFunc, TFunctionRef<void(int32, const FTriangle3d&)> TriangleFunc, const FTransform* ApplyTransform = nullptr, const bool bMapFacesToEdgeLoops = false );` (scope `UE::Geometry`) — Prefer EnumeratePolygroupSelectionElements with Flags parameter.
- L322 _prototype_ `bool ConvertPolygroupSelectionToTopologySelection( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, const FGroupTopology* GroupTopology, FGroupTopologySelection& TopologySelectionOut );` (scope `UE::Geometry`) — Convert a MeshSelection with Polygroup topology type to a FGroupTopologySelection
- L333 _prototype_ `bool InitializeSelectionFromTriangles( const UE::Geometry::FDynamicMesh3& Mesh, const FGroupTopology* GroupTopology, TArrayView<const int> Triangles, FGeometrySelection& SelectionOut);` (scope `UE::Geometry`) — Convert Triangle IDs to target Selection type
- L376 _prototype_ `bool ConvertSelection( const UE::Geometry::FDynamicMesh3& Mesh, const FGroupTopology* GroupTopology, const FGeometrySelection& FromSelectionIn, FGeometrySelection& ToSelectionOut);` (scope `UE::Geometry`) — `UE_DEPRECATED(5.5, "This version of ConvertSelection is deprecated, please use the version with the EENumerateSelectionConversionParams parameter going forward.")` — Convert Selection from one type to another, based on geometry/topology types in FromSelectionIn and ToSelectionOut. The following table describes the conversions, the FromSelectionIn/ToSelectionOut type are rows/columns respectively: To:    Triangle               Polygroup From:                Vertex  Edge    Face   Vertex  Edge    Face Triangle Vertex      1       1       7      4#      7#       7# Triangle Edge        1       1       8      4#      1#       8# Triangle Face        1       1       1      4#      3#       2# Polygroup Vertex     6#      9#      9      1       7#       7# Polygroup Edge       5#      1#      8      1#      1        8# Polygroup Face       1#      1#      1      1#      1#       1 Key: .  These conversions are not implemented... yet? GroupTopology is ignored 1  - The implementation is obvious/unambiguous 2  - Polygroup faces containing any input triangle are selected 3  - Polygroup edges containing any input triangle edge are selected, but polygroup edges containing only input triangle vertices are not. 4  - Polygroup corners coinciding with any input triangle face/edge/vertex are selected 5  - All mesh vertices along the polygroup edge are selected 6  - All mesh vertices coinciding with polygroup corners are selected 7  - All Elements which immediately touch any input vertex/corner are selected 8  - All triangles or faces on either side of the any input edge are selected PolyEdge->TriFace includes all triangles in both groups which the edge bo
- L382 _prototype_ `bool ConvertSelection( const UE::Geometry::FDynamicMesh3& Mesh, const FGroupTopology* GroupTopology, const FGeometrySelection& FromSelectionIn, FGeometrySelection& ToSelectionOut, const EEnumerateSelectionConversionParams ConversionParams);` (scope `UE::Geometry`)
- L402 _prototype_ `bool ConvertTriangleSelectionToOverlaySelection( const UE::Geometry::FDynamicMesh3& Mesh, const FGeometrySelection& MeshSelection, TSet<int>& TrianglesOut, TSet<int>& VerticesOut, FGeometrySelection* TriangleVertexSelectionIncidentToEdgeSelection = nullptr);` (scope `UE::Geometry`) — Convert the given MeshSelection to a list of Triangles and Vertices into the Mesh, which can be used to represent a selection of overlay elements. This is always possible since any FGeometrySelection can be represented as an overlay element selection because any overlay element can be represented as a (Triangle,Vertex) pair. If TriangleVertexSelectionIncidentToEdgeSelection is not null and MeshSelection is an Edge Selection it will be set to a Vertex selection with Triangle Topology corresponding to the vertices touched by the edge selection. This is useful when users expect an edge selection to behave similarly to the incident vertex selection. @note it is not necessarily the case that all vertices of triangles in TrianglesOut will be in VerticesOut. @return false if the MeshSelection topology type is not Triangle and true otherwise
- L423 _prototype_ `bool ConvertPolygroupSelectionToOverlaySelection( const UE::Geometry::FDynamicMesh3& Mesh, const FPolygroupSet& GroupSet, const FGeometrySelection& MeshSelection, TSet<int>& TrianglesOut, TSet<int>& VerticesOut);` (scope `UE::Geometry`) — Convert the given MeshSelection to a list of Triangles and Vertices into the Mesh, which can be used to represent a selection of overlay elements. This is always possible since any FGeometrySelection can be represented as an overlay element selection because any overlay element can be represented as a (Triangle,Vertex) pair. For Polygroup Faces, all triangles in the face are included. For Polygroup Edges, all triangles in any group adjacent to the edge are included. For Polygroup Corners, all triangles in any group touching the corner are included. See ConvertPolygroupSelectionToIncidentOverlaySelection for a similar function which only includes triangles immediately incident to the polygroup element @return false if the MeshSelection topology type is not Polygroup and true otherwise
- L441 _prototype_ `bool ConvertPolygroupSelectionToIncidentOverlaySelection( const UE::Geometry::FDynamicMesh3& Mesh, const FGroupTopology& GroupTopology, const FGeometrySelection& MeshSelection, TSet<int>& TrianglesOut, TSet<int>& VerticesOut, FGeometrySelection* TriangleVertexSelectionIncidentToEdgeOrVertexSelection = nullptr);` (scope `UE::Geometry`) — Like ConvertPolygroupSelectionToOverlaySelection but only includes overlay elements that are immediately incident to Polygroup Vertices/Edges. If TriangleVertexSelectionIncidentToEdgeOrVertexSelection is not null and MeshSelection is an Edge or Vertex selection it will be set to a Vertex selection with Triangle Topology corresponding to the vertices touched by the edge selection. This is useful when users expect an edge selection to behave similarly to the incident vertex selection. @return false if the MeshSelection topology type is not Polygroup and true otherwise
- L457 _prototype_ `bool MakeSelectAllSelection( const UE::Geometry::FDynamicMesh3& Mesh, const FGroupTopology* GroupTopology, TFunctionRef<bool(FGeoSelectionID)> SelectionIDPredicate, FGeometrySelection& AllSelection);` (scope `UE::Geometry`) — Select all elements of the provided Mesh and GroupTopology that pass the provided SelectionIDPredicate, and store in the output AllSelection. The type of elements selected is defined by the existing configured type of the AllSelection parameter. @param GroupTopology precomputed group topology for Mesh, can be passed as null for EGeometryTopologyType::Triangle selections @return true if AllSelection had a known geometry/topology type pair and was populated
- L471 _prototype_ `bool MakeSelectAllConnectedSelection( const UE::Geometry::FDynamicMesh3& Mesh, const FGroupTopology* GroupTopology, const FGeometrySelection& ReferenceSelection, TFunctionRef<bool(FGeoSelectionID)> SelectionIDPredicate, TFunctionRef<bool(FGeoSelectionID A, FGeoSelectionID B)> IsConnectedPredicate, FGeometrySelection& AllConnectedSelection);` (scope `UE::Geometry`) — Expand the input ReferenceSelection to include all "connected" elements and return in AllConnectedSelection. The type of selected element is defined by ReferenceSelection. @param GroupTopology precomputed group topology for Mesh, can be passed as null for EGeometryTopologyType::Triangle selections @param SelectionIDPredicate only elements that pass this filter will be expanded "to"  (but elements of ReferenceSelection that fail the filter will still be included in output) @param IsConnectedPredicate this function determines if "A" should be considered connected to "B", ie can "expand" along that connection @return true if ReferenceSelection had a known geometry/topology type pair and AllConnectedSelection was populated
- L490 _prototype_ `bool MakeBoundaryConnectedSelection( const UE::Geometry::FDynamicMesh3& Mesh, const FGroupTopology* GroupTopology, const FGeometrySelection& ReferenceSelection, TFunctionRef<bool(FGeoSelectionID)> SelectionIDPredicate, FGeometrySelection& BoundaryConnectedSelection);` (scope `UE::Geometry`) — Create a selection of the elements adjacent to the "Border" of the given ReferenceSelection and return in BoundaryConnectedSelection. The type of selected element is defined by ReferenceSelection. Currently "adjacency" is defined as "included in the one-ring of the boundary vertices of the ReferenceSelection", ie first the vertices on boundary edges are found, and then their one-rings are enumerated. Note that this will include "inside" and "outside" adjacent elements, and for vertices, the boundary vertices will still also be included. The main purpose of this function is to implement expand/contract selection operations, which would typically involve first finding the boundary-connected set and then using CombineSelectionInPlace to modify the original selection. @param GroupTopology precomputed group topology for Mesh, can be passed as null for EGeometryTopologyType::Triangle selections @param SelectionIDPredicate only elements that pass this filter will be expanded "to"  (but elements of ReferenceSelection that fail the filter will still be included in output) @return true if ReferenceSelection had a known geometry/topology type pair and BoundaryConnectedSelection was populated
- L517 _prototype_ `bool GetSelectionBoundaryVertices( const UE::Geometry::FDynamicMesh3& Mesh, const UE::Geometry::FGroupTopology* GroupTopology, const UE::Geometry::FGeometrySelection& ReferenceSelection, TSet<int32>& BorderVidsOut, TSet<int32>& CurVerticesOut);` (scope `UE::Geometry`) — Given a selection, return the vertex IDs of the vertices on the boundary of this selection. A selected vertex is considered to be on the boundary either if it is on the actual mesh boundary (for an open mesh) or it is connected to a triangle element that is not part of the selection (i.e. if the vertex has a neighbor vertex not in selection for a selection of type EGeometryElementType::Vertex, or an adjacent edge not in selection for a selection of type EGeometryElementType::Edge, an adjacent triangle not in the selection for a selection of type EGeometryElementType::Face). For selections of type EGeometryTopologyType::Polygroup, the results are equivalent to first converting the selection to corresponding EGeometryTopologyType::Triangle selection and then finding the boundary vertices. This gives the intuitive result for face selections, but may or may not be what is desired for polygroup vertex/edge selections, because vertices/edges that seem to be on the interior of the polygroup selection may be considered border vertices if the tesselation is such that they are adjacent to unselected triangle vertices/edges. @param GroupTopology Must not be null for selections of type EGeometryTopologyType::Polygroup @param BorderVidsOut Output vertex IDs of border vertices @param CurVerticesOut Output vertex IDs of all vertices in the current selection @return true if successful. For instance, could fail if GroupTopology was null for a EGeometryTopologyType::Polygroup selection
- L538 _prototype_ `bool GetSelectionBoundaryCorners( const UE::Geometry::FDynamicMesh3& Mesh, const UE::Geometry::FGroupTopology* GroupTopology, const UE::Geometry::FGeometrySelection& ReferenceSelection, TSet<int32>& BorderCornerIDsOut, TSet<int32>& CurCornerIDsOut);` (scope `UE::Geometry`) — Given a EGeometryTopologyType::Polygroup selection, return the corner IDs of the polygroup corners on the boundary of the selection. A selected corner is considered to be on the boundary either if it is on the actual mesh boundary (for an open mesh) or it is connected to an element that is not part of the selection (i.e. if there is a neighbor corner not in the selection for a selection of type EGeometryElementType::Vertex, or an adjoining edge not in the selection for a selection of type EGeometryElementType::Edge, or an adjoining group not in the selection for a selection of type EGeometryElementType::Face). Selection must be of type EGeometryTopologyType::Polygroup, and GroupTopology must not be null. @param GroupTopology Must not be null @param BorderCornerIDsOut Output corner IDs of border corners @param CurCornerIDsOut Output corner IDs of all corners included in the current selection @return true if successful. For instance, could fail if GroupTopology was null
- L558 _prototype_ `bool CombineSelectionInPlace( FGeometrySelection& SelectionA, const FGeometrySelection& SelectionB, EGeometrySelectionCombineModes CombineMode );` (scope `UE::Geometry`) — Combine the elements of SelectionA and SelectionB using the provided CombineMode, and store the result in SelectionA. @return true if the selectins were compatible (ie both the same type) and of supported geometry/topology type.
- L569 _prototype_ `bool GetTriangleSelectionFrame( const FGeometrySelection& MeshSelection, const UE::Geometry::FDynamicMesh3& Mesh, FFrame3d& SelectionFrameOut);` (scope `UE::Geometry`) — Compute a 3D Frame suitable for use as a 3D transform gizmo position/orientation for the given MeshSelection
- L588 _prototype_ `void TaperPerTriangleValues(const UE::Geometry::FDynamicMesh3& Mesh, const TSet<int32>& TriangleROI, TFunction<int32(int32)> ValueForTriangleFunc, TArray<int>& OutTriangleValues);` (scope `UE::Geometry`) — Computes and smooths per-triangle integer values across a specified region of a mesh. Each triangle in the mesh is assigned an initial value via the user-provided `ValueForTriangleFunc`. Triangles that are on the boundary of the mesh or on the boundary of the specified `InsideTriangles` region are assigned a value of zero. Triangle values are then adjusted within the region to ensure that each triangle's value does not exceed one more than the minimum value of its neighboring triangles. This produces a smoothly varying integer field that respects the boundary constraints. Note the field varies with topological distance (triangle connectivity), not distance along the surface or Euclidean distance @param TriangleROI          Triangles to consider @param LevelForTriangleFunc Function that takes a triangle ID and returns the maximum value for that triangle @param OutTriangleLevels    Output array of triangle values

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Selections/QuadGridPatch.h` (Public)


#### class `UE::Geometry::FQuadGridPatch`  
`class FQuadGridPatch`  
_L29-164_
- desc: FQuadGridPatch represents a set of quads, formed by pairs of triangles, arranged in a 2D grid pattern. U is the "across"/column direction and "V" is the "up"/row direction, and if you were thinking about it in terms of a piece of graph paper, (U=0,V=0) would be in the bottom-left. Each row of Vertices is stored, as well as each row of Quads. In the case of a Quad grid that is a loop, the last vertex in each row is a duplicate of the first. Note, however, that there is currently no explicit tracking of whether or not there is a Loop in U or V - this must be tracked externally. Generally the quad triangles will not be assumed to form any consistent pattern. This complicates some of the functions however, and perhaps this assumption could be optionally provided in the future
- L32 _public member_ `int NumVertexColsU = 0;`
- L33 _public member_ `int NumVertexRowsV = 0;`
- L36 _public member_ `TArray<TArray<int32>> VertexSpans;` — NumVertexRowsV rows of NumVertexColsU VertexIDs, may contain repeated element if the patch forms a loop
- L39 _public member_ `TArray<TArray<FIndex2i>> QuadTriangles;` — Quads stored as pairs of triangle indices, (NumVertexRowsV-1) rows of (NumVertexColsU-1)
- L42 _public function_ `int NumVertexCols() const`
- L43 _public function_ `int NumVertexRows() const`
- L44 _public function_ `int NumQuadCols() const`
- L45 _public function_ `int NumQuadRows() const`
- L47 _public function_ `bool IsEmpty() const`
- L52 _public prototype_ `void InitializeFromQuadStrip(const FDynamicMesh3& Mesh, const TArray<FIndex2i>& SequentialQuadsIn, const TArray<int32>& FirstVertexSpan );` — Initialize an Nx1 grid from a list of quads (represented as a pair of triangles) and the row of vertices on the "bottom" (ie first span)
- L59 _public prototype_ `bool InitializeFromQuadPatch(const FDynamicMesh3& Mesh, const TArray<TArray<FIndex2i>>& QuadRowsIn, const TArray<TArray<int32>>& VertexSpansIn);` — Initialize an NxM grid from a list of quads (represented as a pair of triangles) and corresponding rows of vertices. For N quad-rows, there must be N+1 vertex spans. @return false if the input data is detected to be invalid, in this case the patch is also cleared
- L64 _public prototype_ `void ReverseRows();` — Reverse the order of the vertex/quad rows, ie "flip" vertically
- L74 _public prototype_ `bool AppendQuadPatchRows(FQuadGridPatch&& NextPatch, bool bChecked);` — Append the rows of NextPatch to the rows of the current QuadGrid. NextPatch must have the same number of vertex-columns as this Patch. Requires that the last vertex-row of this Patch be the same as the first vertex-row of NextPatch. @param bChecked if true, function verifies requirements and returns false if a mismatch is detected @return true if append succeeded
- L78 _public function_ `int32 GetNumQuads() const` — @return the total number of quads in the grid
- L81 _public prototype_ `void GetAllTriangles(TArray<int32>& AllTrianglesOut) const;` — @return a list of all the triangles in the grid
- L86 _public function_ `int32 EncodeRowColumnIndex(int32 Row, int32 Column ) const` — Map a row and column index pair into a single int32. 11 Bits are available for the row, and 20 for the column
- L93 _public function_ `FIndex2i DecodeRowColumnIndex(int32 Encoded) const` — Recover row and column indices from an int32 encoded via EncodeRowColumnIndex
- L111 _public prototype_ `FIndex3i GetQuadTriMappedToSpanIndices(const FDynamicMesh3& Mesh, int QuadRow, int QuadIndex, int TriIndex) const;` — In cases like assigning UVs or Normals to a QuadGridPatch, we want to assign a unique element to each of the vertices in the grid, and then generate "element triangles" that index into those new elements. To do this we need to know the (row,column) pair ("Vertex Span Index") for each triangle vertex. This function returns a 3-tuple of vertex span indices for a given quad triangle. The function EncodeRowColumnIndex() is used to map the (row,column) to a single integer, and callers can use DecodeRowColumnIndex() to recover the (row,column) @param QuadRow the row of quads the requested triangle is in @param QuadIndex the "column" index of the quad containing the request triangle @param TriIndex the index of the triangle in the quad, only 0 and 1 are valid @return tuple of encoded (row,column) vertex span indices, in the same ordering as the identified triangle
- L117 _public function_ `void ForEachQuad(TFunctionRef<void(int32 QuadRow, int32 QuadCol, FIndex2i QuadTris)> ApplyFunc) const` — Call ApplyFunc for each quad, passing it's grid index and triangle pair
- L131 _public prototype_ `bool GetVertexColumn(int32 ColumnIndex, TArray<int32>& VerticesOut) const;` — Return vertices in specified Column
- L136 _public prototype_ `int32 FindColumnIndex(int32 VertexID) const;` — Find column that contains vertex, or InvalidID
- L143 _public prototype_ `void GetSubPatchByQuadRange(int StartQuadRow, int EndQuadRow, int StartQuadCol, int EndQuadCol, FQuadGridPatch& PatchOut ) const;` — Construct a new QuadGridPatch that is a subset of the current QuadGridPatch The values (Start|End)Quad(Row|Col) define the sub-patch, the values are inclusive, so passing (1,2,1,2) defines a 2x2 quad patch
- L150 _public prototype_ `void SplitColumnsByPredicate( TFunctionRef<bool(int32 QuadColumn0, int32 QuadColumn1)> PredicateFunc, TArray<FQuadGridPatch>& SplitPatchesOut) const;` — Split the Columns of the QuadGridPatch into new QuadGridPatches where the columns are grouped via the PredicateFunc.
- L162 _public prototype_ `double GetQuadOpeningAngleDeg(const FDynamicMesh3& Mesh, int32 Column0, int32 Column1, int32 Row) const;` — Compute the opening angle between the two quads in Column0 and Column1 of the given Row. This is based on the face normals of the two triangles connected to the edge between Column0 and Column1, so any non-planarity of the quads is ignored. @return unsigned opening angle in degrees in range [0,180], where 0 means quads are parallel

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DYNAMICMESH_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/ShapeApproximation/MeshSimpleShapeApproximation.h` (Public)


#### enum `UE::Geometry::EDetectedSimpleShapeType`  
`enum class EDetectedSimpleShapeType`  
_L19-31_
- desc: EDetectedSimpleShapeType is used to identify auto-detected simple shapes for a mesh/etc
- L22 _public enumerator_ `None = 0` — Object is not a simple shape
- L24 _public enumerator_ `Sphere = 2` — Object has been identified as a sphere
- L26 _public enumerator_ `Box = 4` — Object has been identified as a box
- L28 _public enumerator_ `Capsule = 8` — Object has been identified as a capsule
- L30 _public enumerator_ `Convex = 16` — Object has been identified as a Convex

#### class `UE::Geometry::FMeshSimpleShapeApproximation`  
`class FMeshSimpleShapeApproximation`  
_L46-213_
- desc: FMeshSimpleShapeApproximation can calculate various "simple" shape approximations for a set of meshes, by fitting various primitives/hulls/etc to each mesh. The assumption is that the input mesh(es) are already partitioned into pieces. There are various Generate_X() functions which apply different strategies, generally to fit a containing simple shape or hull to the mesh. However in addition to these explicit strategies, input meshes that are very close to approximations of spheres/boxes/capsules (ie basically meshed versions of these primitives) can be identified and used directly, skipping the fitting process.
- L55 _public member_ `bool bDetectSpheres = true;` — Should spheres be auto-detected
- L57 _public member_ `bool bDetectBoxes = true;` — Should boxes be auto-detected
- L59 _public member_ `bool bDetectCapsules = true;` — Should capsules be auto-detected
- L61 _public member_ `bool bDetectConvexes = true;` — Should convex be auto-detected
- L64 _public member_ `double MinDimension = 0.0;` — minimal dimension of fit shapes, eg thickness/radius/etc (currently only enforced in certain cases)
- L67 _public member_ `bool bSimplifyHulls = true;` — should hulls be simplified as a post-process
- L69 _public member_ `int32 HullTargetFaceCount = 50;` — target number of triangles when simplifying 3D convex hulls
- L71 _public member_ `double HullGeometricToleranceAfterTarget = 0.;` — simplification tolerance for 3D convex hulls, if > 0, applies *after* hull target face count is reached to futher simplify
- L74 _public member_ `double HullSimplifyTolerance = 1.0;` — simplification tolerance when simplifying 2D (swept/projected) convex hulls; note HullGeometricToleranceAfterTarget is used instead for 3D hulls
- L77 _public member_ `bool bDecompositionPreSimplifyWithEdgeLength = false;` — Whether to use apply an edge-length based simplification to the input before running convex decompositions. Useful for very dense input meshes where the decomposition will be slow to compute.
- L79 _public member_ `double DecompositionPreSimplifyEdgeLength = 1.0;` — If enabled by the above bool flag, pre-simplify input geometry to this edge length before computing convex decompositions.
- L82 _public member_ `int32 ConvexDecompositionMaxPieces = 1;` — How many convex pieces to target per mesh when creating convex decompositions. Ignored if < 1. If ErrorTolerance or ProtectNegativeSpace are used, can create fewer pieces.
- L84 _public member_ `bool bUseConvexDecompositionMaxPieces = true;` — Whether to use the above Max Pieces to drive the convex decomposition. Otherwise, will allow the error tolerances / negative space protection settings to drive the number of pieces generated.
- L89 _public member_ `float ConvexDecompositionSearchFactor = .5;` — How much additional decomposition decomposition + merging to do, as a fraction of max pieces.  Larger values can help better-cover small features, while smaller values create a cleaner decomposition with less overlap between hulls. Note: Not used if bConvexDecompositionProtectNegativeSpace is true.
- L91 _public member_ `double ConvexDecompositionErrorTolerance = 0;` — Error tolerance to guide convex decomposition (in cm); we stop adding new parts if the volume error is below the threshold.  For volumetric errors, value will be cubed.
- L93 _public member_ `double ConvexDecompositionMinPartThickness = .1;` — Minimum part thickness for convex decomposition (in cm); hulls thinner than this will be merged into adjacent hulls, if possible.
- L95 _public member_ `bool bConvexDecompositionProtectNegativeSpace = false;` — Whether to use 'navigation-driven' convex decomposition -- using NegativeSpaceTolerance and NegativeSpaceMinRadius to define space that the decomposition hulls cannot occupy
- L98 _public member_ `double NegativeSpaceTolerance = 3;` — Negative space closer to the input than this tolerance distance can be filled in
- L100 _public member_ `double NegativeSpaceMinRadius = 10;` — Minimum radius of negative space to protect; tunnels with radius smaller than this could be filled in
- L102 _public member_ `bool bIgnoreInternalNegativeSpace = true;` — Whether to ignore negative space that is not accessible by traversing from the convex hull (via paths w/ radius of at least Negative Space Tolerance)
- L104 _public member_ `bool bUseExactComputationForBox = false;`
- L107 _public member_ `int32 LevelSetGridResolution = 10;` — Level Set Grid resolution along longest axis
- L120 _public prototype_ `void InitializeSourceMeshes(const TArray<const FDynamicMesh3*>& InputMeshSet);` — Initialize internal mesh sets. This also detects/caches the precise simple shape fits controlled by bDetectSpheres/etc above, so those cannot be modified without calling InitializeSourceMeshes() again. The TSharedPtrs are stored, rather than making a copy of the input meshes @param bIsParallelSafe if true
- L130 _public prototype_ `void Generate_AlignedBoxes(FSimpleShapeSet3d& ShapeSetOut);` — Fit containing axis-aligned boxes to each input mesh and store in ShapeSetOut
- L135 _public prototype_ `void Generate_OrientedBoxes(FSimpleShapeSet3d& ShapeSetOut, FProgressCancel* Progress = nullptr);` — Fit containing minimal-volume oriented boxes to each input mesh and store in ShapeSetOut
- L140 _public prototype_ `void Generate_MinimalSpheres(FSimpleShapeSet3d& ShapeSetOut);` — Fit containing minimal-volume spheres to each input mesh and store in ShapeSetOut
- L146 _public prototype_ `void Generate_Capsules(FSimpleShapeSet3d& ShapeSetOut);` — Fit containing approximate-minimum-volume capsules to each input mesh and store in ShapeSetOut @warning the capsule is fit by first fitting a line to the vertices, and then containing the points, so the fit can deviate quite a bit from a truly "minimal" capsule
- L152 _public prototype_ `void Generate_ConvexHulls(FSimpleShapeSet3d& ShapeSetOut, FProgressCancel* Progress = nullptr);` — Calculate 3D Convex Hulls for each input mesh and store in ShapeSetOut. Each convex hull is stored as a triangle mesh, and optionally simplified if bSimplifyHulls=true
- L158 _public prototype_ `void Generate_ConvexHullDecompositions(FSimpleShapeSet3d& ShapeSetOut, FProgressCancel* Progress = nullptr);` — Calculate multiple 3D Convex Hulls for each input mesh and store in ShapeSetOut. Each convex hull is stored as a triangle mesh, and optionally simplified if bSimplifyHulls=true
- L183 _public prototype_ `void Generate_ProjectedHulls(FSimpleShapeSet3d& ShapeSetOut, EProjectedHullAxisMode AxisMode);` — Calculate Projected Convex Hulls for each input mesh and store in ShapeSetOut. A Projected Hull is computed by first projecting all the mesh vertices to a plane, computing a 2D convex hull polygon, and then sweeping the polygon in 3D to contain all the mesh vertices. The 2D convex hull polygons are optionally simplified if bSimplifyHulls=true. @param AxisMode which axis to use for the planar projection
- L185 _public prototype_ `void Generate_LevelSets(FSimpleShapeSet3d& ShapeSetOut, FProgressCancel* Progress = nullptr);`
- L192 _public prototype_ `void Generate_MinVolume(FSimpleShapeSet3d& ShapeSetOut);` — Fit containing axis-aligned box, oriented box, capsule, and sphere to each input mesh, and store the one with smallest volume in ShapeSetOut
- L197 _protected member_ `TArray<const FDynamicMesh3*> SourceMeshes;`
- L207 _protected member_ `TArray<FSourceMeshCache> SourceMeshCaches;`
- L210 _protected prototype_ `void DetectAndCacheSimpleShapeType(const FDynamicMesh3* SourceMesh, FSourceMeshCache& CacheOut);`
- L211 _protected prototype_ `bool GetDetectedSimpleShape(const FSourceMeshCache& Cache, FSimpleShapeSet3d& ShapeSetOut, FCriticalSection& ShapeSetLock);`

#### enum `UE::Geometry::FMeshSimpleShapeApproximation::EProjectedHullAxisMode`  
`enum class EProjectedHullAxisMode`  
_L162-174_
- desc: Type/Mode for deciding 3D axis to use in Generate_ProjectedHulls()
- L165 _public enumerator_ `X = 0` — Use Unit X axis
- L167 _public enumerator_ `Y = 1` — Use Unit Y axis
- L169 _public enumerator_ `Z = 2` — Use Unit Z axis
- L171 _public enumerator_ `SmallestBoxDimension = 3` — Use X/Y/Z axis with smallest axis-aligned-bounding-box dimension
- L173 _public enumerator_ `SmallestVolume = 4` — Compute projected hull for each of X/Y/Z axes and use the one that has the smallest volume

#### struct `UE::Geometry::FMeshSimpleShapeApproximation::FSourceMeshCache`  
`struct FSourceMeshCache`  
_L199-206_
- L201 _public member_ `EDetectedSimpleShapeType DetectedType = EDetectedSimpleShapeType::None;`
- L203 _public member_ `FSphere3d DetectedSphere;`
- L204 _public member_ `FOrientedBox3d DetectedBox;`
- L205 _public member_ `FCapsule3d DetectedCapsule;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DYNAMICMESH_API`
- L13 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/ShapeApproximation/ShapeDetection3.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L24 _prototype_ `bool IsSphereMesh(const FDynamicMesh3& Mesh, FSphere3d& SphereOut, double RelativeDeviationTol = 0.025, double MaxAngleRangeDegrees = 72);` (scope `UE::Geometry`) — Detect if input Mesh is a meshed approximation of an analytic Sphere, and if so return best guess in SphereOut. Fits a sphere to input points with several rounds of incremental improvement, then measures chordal deviation of edge midpoints. @param RelativeDeviationTol Scaled by sphere diameter. The allowed difference in the distance from edge midpoints to the surface of the sphere vs the ideal distance for an edge of the same length. @param MaxAngleRangeDegrees Maximum angle difference in vectors from center of sphere to the endpoints of any surface edge. Controls how coarsely tessellated a sphere can be before it is not considered a sphere. @return true if mesh is a Sphere and SphereOut is initialized
- L35 _prototype_ `bool IsBoxMesh(const FDynamicMesh3& Mesh, FOrientedBox3d& BoxOut, double AngleToleranceDeg = 0.1, double PlaneDistanceTolerance = 1e-2);` (scope `UE::Geometry`) — Detect if input Mesh is a meshed box, and if so return analytic box in BoxOut. Clusters face planes, looking to find 6 unique planes with normals grouped into 3 opposite-direction pairs. If this configuraiton is found, computing minimal box is trivial. @param AngleToleranceDeg normals are allowed to deviate by this amount and still be considered coplanar @param PlaneDistanceTolerance planes with the same normal are allowed to be this far apart and still be considered coplanar @return true if mesh is a Box and BoxOut is initialized
- L45 _prototype_ `bool IsCapsuleMesh(const FDynamicMesh3& Mesh, FCapsule3d& CapsuleOut, double RelativeDeviationTol = 0.025, double MaxAngleRangeDegrees = 72);` (scope `UE::Geometry`) — Detect if input Mesh is a meshed approximation of an analytic Capsule, and if so return best guess in CapsuleOut. Fits a capsule to input points, then measures chordal deviation of edge midpoints. @param RelativeDeviationTol Scaled by capsule diameter. The allowed difference in the distance from edge midpoints to the surface of the capsule vs the ideal distance for an edge of the same length. @param MaxAngleRangeDegrees Maximum angle range an edge can cover over the cylinder or the spherical endcaps. Controls how coarsely tessellated a capsule can be before it is not considered a capsule. @return true if mesh is a Capsule and CapsuleOut is initialized

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/ShapeApproximation/SimpleShapeSet3.h` (Public)


#### enum `UE::Geometry::ESimpleShapeType`  
`enum class ESimpleShapeType`  
_L26-33_
- desc: Supported/known types of Simple Shapes
- L28 _public enumerator_ `Sphere = 2`
- L29 _public enumerator_ `Box = 4`
- L30 _public enumerator_ `Capsule = 8`
- L31 _public enumerator_ `Convex = 16`
- L32 _public enumerator_ `LevelSet = 32`

#### class `UE::Geometry::FSphereShape3d`  
`class FSphereShape3d`  
_L40-53_
- desc: FSphereShape is a 3D sphere
- L43 _public member_ `FSphere3d Sphere;`
- L45 _public prototype_ `FSphereShape3d() = default;`
- L47 _public function_ `FSphereShape3d(const FSphere3d& SphereIn) : Sphere(SphereIn)`
- L52 _public function_ `ESimpleShapeType GetShapeType() const`

#### struct `UE::Geometry::FBoxShape3d`  
`struct FBoxShape3d`  
_L59-71_
- desc: FBoxShape is a 3D oriented box
- L61 _public member_ `FOrientedBox3d Box;`
- L63 _public prototype_ `FBoxShape3d() = default;`
- L65 _public function_ `FBoxShape3d(const FOrientedBox3d& BoxIn) : Box(BoxIn)`
- L70 _public function_ `ESimpleShapeType GetShapeType() const`

#### struct `UE::Geometry::FCapsuleShape3d`  
`struct FCapsuleShape3d`  
_L77-89_
- desc: FCapsuleShape is a 3D oriented capsule/sphyl
- L79 _public member_ `FCapsule3d Capsule;`
- L81 _public prototype_ `FCapsuleShape3d() = default;`
- L83 _public function_ `FCapsuleShape3d(const FCapsule3d& CapsuleIn) : Capsule(CapsuleIn)`
- L88 _public function_ `ESimpleShapeType GetShapeType() const`

#### struct `UE::Geometry::FConvexShape3d`  
`struct FConvexShape3d`  
_L95-112_
- desc: FConvexShape is a 3D convex hull, currently stored as a triangle mesh
- L97 _public member_ `FDynamicMesh3 Mesh;`
- L99 _public prototype_ `FConvexShape3d() = default;`
- L101 _public function_ `FConvexShape3d(const FDynamicMesh3& MeshIn) : Mesh(MeshIn)`
- L106 _public function_ `FConvexShape3d(FDynamicMesh3&& MeshIn) : Mesh(MoveTemp(MeshIn))`
- L111 _public function_ `ESimpleShapeType GetShapeType() const`

#### struct `UE::Geometry::FLevelSetShape3d`  
`struct FLevelSetShape3d`  
_L118-149_
- L120 _public member_ `FTransform3d GridTransform;`
- L121 _public member_ `FDenseGrid3f Grid;`
- L122 _public member_ `float CellSize;`
- L124 _public prototype_ `FLevelSetShape3d() = default;`
- L126 _public function_ `FLevelSetShape3d(const FTransform3d& GridTransform, const FDenseGrid3f& Grid, float CellSize) : GridTransform(GridTransform), Grid(Grid), CellSize(CellSize)`
- L133 _public function_ `FLevelSetShape3d(FTransform3d&& GridTransform, FDenseGrid3f&& Grid, float CellSize) : GridTransform(MoveTemp(GridTransform)), Grid(MoveTemp(Grid)), CellSize(CellSize)`
- L140 _public function_ `ESimpleShapeType GetShapeType() const`
- L142 _public function_ `FOrientedBox3d GetGridBox() const`

#### struct `UE::Geometry::FSimpleShapeSet3d`  
`struct FSimpleShapeSet3d`  
_L156-218_
- desc: FSimpleShapeSet stores a set of simple geometry shapes useful for things like collision detection/etc. Various functions set-processing operations are supported.
- L158 _public member_ `TArray<FSphereShape3d> Spheres;`
- L159 _public member_ `TArray<FBoxShape3d> Boxes;`
- L160 _public member_ `TArray<UE::Geometry::FCapsuleShape3d> Capsules;`
- L161 _public member_ `TArray<FConvexShape3d> Convexes;`
- L162 _public member_ `TArray<FLevelSetShape3d> LevelSets;`
- L165 _public function_ `int32 TotalElementsNum() const` — @return total number of elements in all sets
- L170 _public prototype_ `void Append(const FSimpleShapeSet3d& OtherShapeSet);` — Append elements of another shape set
- L176 _public prototype_ `void Append(const FSimpleShapeSet3d& OtherShapeSet, const FTransform3d& Transform);` — Append elements of another shape set with given transform applied
- L182 _public prototype_ `void Append(const FSimpleShapeSet3d& OtherShapeSet, const TArray<FTransform3d>& TransformSequence);` — Append elements of another shape set with given transforms applied
- L187 _public prototype_ `void Append(const FSimpleShapeSet3d& OtherShapeSet, const FTransformSequence3d& TransformSequence);` — Append elements of another shape set with given transforms applied
- L192 _public prototype_ `void RemoveContainedGeometry();` — Remove any of the elements that are fully contained in larger elements
- L197 _public prototype_ `void FilterByVolume(int32 MaximumCount);` — Sort the elements by volume and then discard all but the largest MaximumCount elements
- L212 _public prototype_ `bool MergeShapes(int32 MergeAboveCount, const FMergeShapesSettings& MergeSettings);` — Attempt to reduce the number of simple collision shapes by merging neighboring shapes, while still optionally protecting negative space
- L217 _public prototype_ `void ApplyTransform(const FTransform3d& Transform);` — Transform shape elements. This will be a best-effort as if there is non-uniform scaling only Convexes can be transformed correctly

#### struct `UE::Geometry::FSimpleShapeSet3d::FMergeShapesSettings`  
`struct FMergeShapesSettings`  
_L199-210_
- L202 _public member_ `bool bMergeShapesProtectNegativeSpace = false;` — Whether to use the negative space protection settings when merging collision shapes
- L205 _public member_ `double NegativeSpaceTolerance = 3;` — Negative space closer to the input than this tolerance distance can be filled in
- L207 _public member_ `double NegativeSpaceMinRadius = 10;` — Minimum radius of negative space to protect; tunnels with radius smaller than this could be filled in
- L209 _public member_ `bool bIgnoreInternalNegativeSpace = true;` — Whether to ignore negative space that is not accessible by traversing from the convex hull (via paths w/ radius of at least Negative Space Tolerance)

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DYNAMICMESH_API`
- L19 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Geometry` (scope `UE`)
- L34 _prototype_ `ENUM_CLASS_FLAGS(ESimpleShapeType);` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Solvers/ConstrainedMeshDeformer.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshDeformation` (scope `UE`)
- L59 _prototype_ `TUniquePtr<UE::Solvers::IConstrainedMeshSolver> ConstructConstrainedMeshDeformer(const ELaplacianWeightScheme WeightScheme, const FDynamicMesh3& DynamicMesh);` (scope `UE::MeshDeformation`) — Solves the linear system for p_vec ( Transpose(L) * L   + (0  0      )  ) p_vec = source_vec + ( 0              ) (                      (0 lambda^2)  )                      ( lambda^2 c_vec ) where:  L := laplacian for the mesh, source_vec := Transpose(L)*L mesh_vertex_positions lambda := weights c_vec := constrained positions Expected Use: // Create Deformation Solver from Mesh TUniquePtr<IConstrainedMeshSolver>  MeshDeformer = ConstructConstrainedMeshDeformer(ELaplacianWeightScheme::ClampedCotangent, DynamicMesh); // Add constraints. for.. { int32 VtxId = ..; double Weight = ..; FVector3d TargetPos = ..;  bool bPostFix = ...; MeshDeformer->AddConstraint(VtxId, Weight, TargetPos, bPostFix); } // Solve for new mesh vertex locations TArray<FVector3d> PositionBuffer; MeshDeformer->Deform(PositionBuffer); // Update Mesh? for (int32 VtxId : DynamicMesh.VertexIndices()) DynamicMesh.SetVertex(VtxId, PositionBuffer[VtxId]); ... // Update constraint positions. for .. { int32 VtxId = ..;  FVector3d TargetPos = ..; bool bPostFix = ...; MeshDeformer->UpdateConstraintPosition(VtxId, TargetPos, bPostFix); } // Solve for new vertex locations. MeshDeformer->Deform(PositionBuffer); // Update Mesh?
- L88 _prototype_ `TUniquePtr<UE::Solvers::IConstrainedMeshSolver> ConstructUniformConstrainedMeshDeformer(const FDynamicGraph3d& Graph);` (scope `UE::MeshDeformation`) — Construct a Mesh Deformer object for the given generic mesh that uses Biharmonic Laplacian Mesh Deformation to solve for the deformed vertex positions. Similar to ConstructConstrainedMeshDeformer() however a uniform-weighted Laplacian is always used. This allows for the solution of deformation problems on a more generic mesh type (triangles or faces are not required.)
- L101 _prototype_ `TUniquePtr<UE::Solvers::IConstrainedLaplacianMeshSolver> ConstructSoftMeshDeformer(const FDynamicMesh3& DynamicMesh);` (scope `UE::MeshDeformation`) — Construct a Mesh Deformer object for the given mesh that uses Biharmonic Laplacian Mesh Deformation to solve for the deformed vertex positions. Similar to ConstructConstrainedMeshDeformer() however (1) a Voronoi-Area Weighted Clamped Cotangent Laplacian is always used and (2) the boundary positions are included in the system. This allows for the solution of deformation problems where the boundary also moves, however it also means that constraints should be added for all boundary vertices or the deformation may be unstable.

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Solvers/ConstrainedMeshSmoother.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshDeformation` (scope `UE`)
- L30 _prototype_ `TUniquePtr<UE::Solvers::IConstrainedMeshSolver> ConstructConstrainedMeshSmoother(const ELaplacianWeightScheme WeightScheme, const FDynamicMesh3& DynamicMesh);` (scope `UE::MeshDeformation`) — Solves the linear system for p_vec ( Transpose(L) * L   + (0  0      )  ) p_vec = ( 0              ) (                      (0 lambda^2)  )         ( lambda^2 c_vec ) where:  L := laplacian for the mesh, lambda := weights c_vec := constrained positions Expected Use: same as the ConstrainedMeshDeformer above.

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Solvers/ConstrainedMeshSolver.h` (Public)


#### class `UE::Solvers::IConstrainedMeshSolver`  
`class IConstrainedMeshSolver`  
_L19-53_
- desc: Interface to a index-based deformation solver for a 3D mesh vertex set that supports weighted point constraints.
- L23 _public prototype_ `virtual ~IConstrainedMeshSolver() = default;`
- L27 _public prototype_ `virtual void AddConstraint(const int32 VtxId, const double Weight, const FVector3d& Position, const bool bPostFix) = 0;` — Add or update a weighted positional constraint associated with VtxId @param bPostFix if true, this constraint will be explicitly applied after the solve
- L31 _public prototype_ `virtual bool UpdateConstraintPosition(const int32 VtxId, const FVector3d& Position, const bool bPostFix) = 0;` — Update or Create a constraint position associated with @param VtxId @return true if a constraint weight is associated with @param VtxId
- L35 _public prototype_ `virtual bool UpdateConstraintWeight(const int32 VtxId, const double Weight) = 0;` — Update or Create a constraint weight associated with @param VtxId @return true if a constraint position is associated with @param VtxId
- L38 _public prototype_ `virtual void ClearConstraints() = 0;` — Clear all constraints (Positions and Weights)
- L41 _public prototype_ `virtual void ClearConstraintWeights() = 0;` — Clear all Constraint Weights
- L44 _public prototype_ `virtual void ClearConstraintPositions() = 0;` — Clear all Constraint Positions
- L48 _public prototype_ `virtual bool IsConstrained(const int32 VtxId) const = 0;` — Test if a non-zero weighted constraint is associated with VtxId
- L52 _public prototype_ `virtual bool Deform(TArray<FVector3d>& PositionBuffer) = 0;` — Returns the vertex locations of the deformed mesh. Note the array may have empty elements as the index matches the Mesh based VtxId.  PositionBuffer[VtxId] = Pos.

#### class `UE::Solvers::IConstrainedLaplacianMeshSolver`  
`class IConstrainedLaplacianMeshSolver : public IConstrainedMeshSolver`  
_L60-67_
- inherits: `IConstrainedMeshSolver`
- desc: Extension of IConstrainedMeshSolver that supports manipulating the underlying Laplacian vectors used in Laplacian-based Deformation Solvers.
- L63 _public prototype_ `virtual ~IConstrainedLaplacianMeshSolver() = default;`
- L66 _public prototype_ `virtual void UpdateLaplacianScale(double UniformScale) = 0;` — Update global scale applied to Laplacian vectors before solve.

#### class `UE::Solvers::IConstrainedMeshUVSolver`  
`class IConstrainedMeshUVSolver`  
_L73-100_
- desc: Interface to a index-based UV solver for a 3D triangle mesh that supports weighted point constraints.
- L77 _public prototype_ `virtual ~IConstrainedMeshUVSolver() = default;`
- L81 _public prototype_ `virtual void AddConstraint(const int32 VtxId, const double Weight, const FVector2d& Position, const bool bPostFix) = 0;` — Add or update a weighted positional constraint associated with VtxId @param bPostFix if true, this constraint will be explicitly applied after the solve
- L85 _public prototype_ `virtual bool UpdateConstraintPosition(const int32 VtxId, const FVector2d& Position, const bool bPostFix) = 0;` — Update or Create a constraint position associated with @param VtxId @return true if a constraint weight is associated with @param VtxId
- L89 _public prototype_ `virtual bool UpdateConstraintWeight(const int32 VtxId, const double Weight) = 0;` — Update or Create a constraint weight associated with @param VtxId @return true if a constraint position is associated with @param VtxId
- L92 _public prototype_ `virtual void ClearConstraints() = 0;` — Clear all constraints (Positions and Weights)
- L95 _public prototype_ `virtual bool IsConstrained(const int32 VtxId) const = 0;` — Test if a non-zero weighted constraint is associated with VtxId
- L99 _public prototype_ `virtual bool SolveUVs(const FDynamicMesh3* DynamicMesh, TArray<FVector2d>& UVBuffer) = 0;` — Returns the vertex locations of the deformed mesh. Note the array may have empty elements as the index matches the Mesh based VtxId.  PositionBuffer[VtxId] = Pos.

#### Free symbols / members of external scopes

- L8 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Solvers` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Solvers/LaplacianMatrixAssembly.h` (Public)


#### enum `UE::MeshDeformation::ECotangentWeightMode`  
`enum class ECotangentWeightMode`  
_L196-204_
- L199 _public enumerator_ `Default = 0` — Standard cotangent weights
- L201 _public enumerator_ `ClampedMagnitude = 1` — Magnitude of matrix entries clamped to [-1e5,1e5], scaled by area weight
- L203 _public enumerator_ `TriangleArea = 2` — Divide cotangent weights by the area of the triangle

#### enum `UE::MeshDeformation::ECotangentAreaMode`  
`enum class ECotangentAreaMode`  
_L207-213_
- L210 _public enumerator_ `NoArea = 0` — uniform-weighted cotangents
- L212 _public enumerator_ `VoronoiArea = 1` — weight each vertex/row by 1/voronoi_area

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MeshDeformation` (scope `UE`)
- L44 _prototype_ `template<typename RealType, typename MeshType> void ConstructUniformLaplacian(const MeshType& Mesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary);` (scope `UE::MeshDeformation`) — Construct a sparse matrix representation of a uniform weighted Laplacian. The uniform weighted Laplacian is defined solely in terms of the connectivity of the mesh.  Note, by construction this should be a symmetric matrix. The mesh itself is assumed to have N interior vertices, and M boundary vertices. Row i represents the Laplacian at vert_i, the non-zero entries correspond to the incident one-ring vertices vert_j. L_{ij} = 1                      if vert_j is in the one-ring of vert_i L_{ii} = -Sum{ L_{ij}, j != i} @param DynamicMesh        The triangle mesh @param VertexMap          On return, Additional arrays used to map between vertexID and offset in a linear array (i.e. the row). The vertices are ordered so that last M ( = VertexMap.NumBoundaryVerts() )  correspond to those on the boundary. @param LaplacianInterior  On return, the laplacian operator that acts on the interior vertices: sparse  N x N matrix @param LaplacianBoundary  On return, the portion of the operator that acts on the boundary vertices: sparse  N x M matrix LaplacianInterior * Vector_InteriorVerts + LaplacianBoundary * Vector_BoundaryVerts = Full Laplacian applied to interior vertices.
- L72 _prototype_ `template<typename RealType> void ConstructUmbrellaLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary);` (scope `UE::MeshDeformation`) — Construct a sparse matrix representation of an umbrella weighted Laplacian. This Laplacian is defined solely in terms of the connectivity of the mesh.  Note, there is no expectation that the resulting matrix will be symmetric. The mesh itself is assumed to have N interior vertices, and M boundary vertices. Row i represents the Laplacian at vert_i, the non-zero entries correspond to the incident one-ring vertices vert_j. L_{ij} = 1 / valence(of i)                      if vert_j is in the one-ring of vert_i L_{ii} = -Sum{ L_{ij}, j != i} = -1 @param DynamicMesh        The triangle mesh @param VertexMap          Additional arrays used to map between vertexID and offset in a linear array (i.e. the row). The vertices are ordered so that last M ( = VertexMap.NumBoundaryVerts() )  correspond to those on the boundary. @param LaplacianInterior  On return, the laplacian operator that acts on the interior vertices: sparse  N x N matrix @param LaplacianBoundary  On return, the portion of the operator that acts on the boundary vertices: sparse  N x M matrix LaplacianInterior * Vector_InteriorVerts + LaplacianBoundary * Vector_BoundaryVerts = Full Laplacian applied to interior vertices.
- L98 _prototype_ `template<typename RealType> void ConstructValenceWeightedLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary);` (scope `UE::MeshDeformation`) — Construct a sparse matrix representation of a valence-weighted Laplacian. The valence weighted Laplacian is defined solely in terms of the connectivity of the mesh.  Note, by construction this should be a symmetric matrix. The mesh itself is assumed to have N interior vertices, and M boundary vertices. Row i represents the Laplacian at vert_i, the non-zero entries correspond to the incident one-ring vertices vert_j. L_{ij} = 1/\sqrt(valence(i) + valence(j))   if vert_j is in the one-ring of vert_i L_{ii} = -Sum{ L_{ij}, j != i} @param DynamicMesh        The triangle mesh @param VertexMap          Additional arrays used to map between vertexID and offset in a linear array (i.e. the row). The vertices are ordered so that last M ( = VertexMap.NumBoundaryVerts() )  correspond to those on the boundary. @param LaplacianInterior  On return, the laplacian operator that acts on the interior vertices: sparse  N x N matrix @param LaplacianBoundary  On return, the portion of the operator that acts on the boundary vertices: sparse  N x M matrix LaplacianInterior * Vector_InteriorVerts + LaplacianBoundary * Vector_BoundaryVerts = Full Laplacian applied to interior vertices.
- L117 _prototype_ `template<typename RealType> void ConstructMeanValueWeightLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary);` (scope `UE::MeshDeformation`) — Construct a sparse matrix representation using a meanvalue-weighted  Laplacian. NB: there is no reason to expect this to be a symmetric matrix. The mesh itself is assumed to have N interior vertices, and M boundary vertices. @param DynamicMesh        The triangle mesh @param VertexMap          Additional arrays used to map between vertexID and offset in a linear array (i.e. the row). The vertices are ordered so that last M ( = VertexMap.NumBoundaryVerts() )  correspond to those on the boundary. @param LaplacianInterior  On return, the laplacian operator that acts on the interior vertices: sparse  N x N matrix @param LaplacianBoundary  On return, the portion of the operator that acts on the boundary vertices: sparse  N x M matrix LaplacianInterior * Vector_InteriorVerts + LaplacianBoundary * Vector_BoundaryVerts = Full Laplacian applied to interior vertices.
- L141 _prototype_ `template<typename RealType> void ConstructCotangentLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& AreaMatrix, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary);` (scope `UE::MeshDeformation`) — Construct a sparse matrix representation using a cotangent-weighted  Laplacian. but returns the result in two symmetric parts. The mesh itself is assumed to have N interior vertices, and M boundary vertices. (AreaMatrix^{-1}) * L_hat  = Cotangent weighted Laplacian. @param DynamicMesh        The triangle mesh @param VertexMap          Additional arrays used to map between vertexID and offset in a linear array (i.e. the row). The vertices are ordered so that last M ( = VertexMap.NumBoundaryVerts() )  correspond to those on the boundary. @param AreaMatrix         On return, the mass matrix for the internal vertices.  sparse N x N matrix @param LaplacianInterior  On return, the laplacian operator that acts on the interior vertices: sparse  N x N matrix - symmetric @param LaplacianBoundary  On return, the portion of the operator that acts on the boundary vertices: sparse  N x M matrix AreaMatrix^{-1} * ( LaplacianInterior * Vector_InteriorVerts + LaplacianBoundary * Vector_BoundaryVerts) = Full Laplacian applied to interior vertices.
- L166 _prototype_ `template<typename RealType> void ConstructCotangentLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary, const bool bClampWeights);` (scope `UE::MeshDeformation`) — Construct a sparse matrix representation using a pre-multiplied cotangent-weighted Laplacian. NB: there is no reason to expect this to be a symmetric matrix. This computes the laplacian scaled by the average area A_ave:  ie.  LScaled =   A_ave/(2A_i) ( Cot alpha_ij + Cot beta_ij ) The mesh itself is assumed to have N interior vertices, and M boundary vertices. @param DynamicMesh        The triangle mesh @param VertexMap          Additional arrays used to map between vertexID and offset in a linear array (i.e. the row). The vertices are ordered so that last M ( = VertexMap.NumBoundaryVerts() )  correspond to those on the boundary. @param LaplacianInterior  On return, scaled laplacian operator that acts on the interior vertices: sparse  N x N matrix @param LaplacianBoundary  On return, scaled portion of the operator that acts on the boundary vertices: sparse  N x M matrix @param bClampAreas        Indicates if (A_ave / A_i) should be clamped to (0.5, 5) range. in practice this is desirable when creating the biharmonic operator, but not the mean curvature flow operator LaplacianInterior * Vector_InteriorVerts + LaplacianBoundary * Vector_BoundaryVerts = Full Laplacian applied to interior vertices.
- L190 _prototype_ `template<typename RealType> void ConstructIDTCotangentLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary, const bool bClampWeights);` (scope `UE::MeshDeformation`) — Construct a sparse matrix representation using a pre-multiplied cotangent-weighted Laplacian, using an intrinsic Delaunay mesh internally NB: there is no reason to expect this to be a symmetric matrix. This computes the laplacian scaled by the average area A_ave:  ie.  LScaled =   A_ave/(2A_i) ( Cot alpha_ij + Cot beta_ij ) The mesh itself is assumed to have N interior vertices, and M boundary vertices. @param DynamicMesh        The triangle mesh @param VertexMap          Additional arrays used to map between vertexID and offset in a linear array (i.e. the row). The vertices are ordered so that last M ( = VertexMap.NumBoundaryVerts() )  correspond to those on the boundary. @param LaplacianInterior  On return, scaled laplacian operator that acts on the interior vertices: sparse  N x N matrix @param LaplacianBoundary  On return, scaled portion of the operator that acts on the boundary vertices: sparse  N x M matrix @param bClampAreas        Indicates if (A_ave / A_i) should be clamped to (0.5, 5) range. in practice this is desirable when creating the biharmonic operator, but not the mean curvature flow operator LaplacianInterior * Vector_InteriorVerts + LaplacianBoundary * Vector_BoundaryVerts = Full Laplacian applied to interior vertices.
- L234 _prototype_ `template<typename RealType> void ConstructFullCotangentLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianMatrix, ECotangentWeightMode WeightMode = ECotangentWeightMode::ClampedMagnitude, ECotangentAreaMode AreaMode = ECotangentAreaMode::NoArea );` (scope `UE::MeshDeformation`) — Construct sparse Cotangent Laplacian matrix. This variant combines the N interior and M boundary vertices into a single (N+M) matrix and does not do any special treatment of boundaries, they just get standard Cotan weights If you don't want to move the boundary vertices to the end, then initialize the VertexMap with bRemapBoundary set to false. Example usage: If you want to get the standard cotangent weight matrix for a mesh with no boundary reordering: FDynamicMesh3 DynamicMesh; const bool bRemapBoundary = false; FVertexLinearization VertexMap(DynamicMesh, bRemapBoundary); ConstructFullCotangentLaplacian(DynamicMesh, VertexMap, ECotangentWeightMode::Default, ECotangentAreaMode::NoArea);
- L244 _prototype_ `template<typename RealType> void ConstructFullIDTCotangentLaplacian(const FDynamicMesh3& Mesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianMatrix, ECotangentWeightMode WeightMode = ECotangentWeightMode::ClampedMagnitude, ECotangentAreaMode AreaMode = ECotangentAreaMode::NoArea);` (scope `UE::MeshDeformation`) — Use intrinsic Delaunay mesh to construct sparse Cotangent Laplacian matrix. This variant combines the N interior and M boundary vertices into a single (N+M) matrix and does not do any special treatment of boundaries, they just get standard Cotan weights.
- L265 _function_ `template<typename RealType, typename MeshType> void UE::MeshDeformation::ConstructUniformLaplacian(const MeshType& Mesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary)` (scope `UE::MeshDeformation`)
- L316 _function_ `template<typename RealType> void UE::MeshDeformation::ConstructUmbrellaLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary)` (scope `UE::MeshDeformation`)
- L381 _function_ `template<typename RealType> void UE::MeshDeformation::ConstructValenceWeightedLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary)` (scope `UE::MeshDeformation`)
- L443 _function_ `template<typename RealType> void UE::MeshDeformation::ConstructMeanValueWeightLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary)` (scope `UE::MeshDeformation`)
- L515 _function_ `template<typename RealType> void UE::MeshDeformation::ConstructCotangentLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& AreaMatrix, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary)` (scope `UE::MeshDeformation`)
- L616 _function_ `template<typename RealType> void UE::MeshDeformation::ConstructCotangentLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary, const bool bClampWeights)` (scope `UE::MeshDeformation`)
- L712 _function_ `template<typename RealType> void UE::MeshDeformation::ConstructIDTCotangentLaplacian(const FDynamicMesh3& DynamicMesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianInterior, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianBoundary, const bool bClampWeights)` (scope `UE::MeshDeformation`)
- L855 _function_ `template<typename RealType> void UE::MeshDeformation::ConstructFullCotangentLaplacian(const FDynamicMesh3& Mesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianMatrix, ECotangentWeightMode WeightMode, ECotangentAreaMode AreaMode)` (scope `UE::MeshDeformation`)
- L878 _function_ `` (scope `UE::MeshDeformation::ConstructFullCotangentLaplacian`)
- L890 _typedef_ `using MatrixEntry = typename UE::Solvers::TSparseMatrixAssembler<RealType>::FTupleData;` (scope `UE::MeshDeformation::ConstructFullCotangentLaplacian`)
- L914 _function_ `Mesh.EnumerateVertexTriangles(IVertId, [&](int32 TriId) { const int32 TriIdx = ToTriIdx[TriId]; const CotanTriangleData& TriData = CotangentTriangleDataArray[TriIdx]; const FIndex3i TriVertIds = Mesh.GetTriangle(TriId); int32 TriVertIndex = IndexUtil::FindTriIndex(IVertId, TriVertIds); WeightArea += TriData.VoronoiArea[TriVertIndex]; });` (scope `UE::MeshDeformation::ConstructFullCotangentLaplacian::__anon189c182e0202`)
- L983 _function_ `template<typename RealType> void UE::MeshDeformation::ConstructFullIDTCotangentLaplacian(const FDynamicMesh3& Mesh, const FVertexLinearization& VertexMap, UE::Solvers::TSparseMatrixAssembler<RealType>& LaplacianMatrix, ECotangentWeightMode WeightMode, ECotangentAreaMode AreaMode)` (scope `UE::MeshDeformation`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Solvers/MeshLaplacian.h` (Public)


#### enum `ELaplacianWeightScheme`  
`enum class ELaplacianWeightScheme`  
_L13-29_
- desc: Types of Laplacian weights. This enum is used to indicate which type of Mesh Laplacian should be used in various Mesh Deformation solvers. See LaplacianMatrixAssembly.h for specifics
- L16 _public enumerator_ `Uniform` — Weight on each vertex is 1
- L18 _public enumerator_ `Umbrella` — Weight on each vertex is 1/N, where N is valence of vertex
- L20 _public enumerator_ `Valence` — Weight on each vertex is 1/ Sqrt(Valence + Nbr_Valence)
- L22 _public enumerator_ `MeanValue` — Mean-Value weight on each vertex, where Mean Value weight is defined by formula 9 in https://www.inf.usi.ch/hormann/papers/Floater.2006.AGC.pdf
- L24 _public enumerator_ `Cotangent`
- L26 _public enumerator_ `ClampedCotangent`
- L28 _public enumerator_ `IDTCotanget` — Cotan for Intrinsic Delaunay triangulation

#### Free symbols / members of external scopes

- L35 _prototype_ `FString LaplacianSchemeName(const ELaplacianWeightScheme Scheme);` — Utility to map the enum names for debuging etc.
- L41 _prototype_ `bool bIsSymmetricLaplacian(const ELaplacianWeightScheme Scheme);` — @return true if Laplacian scheme produces a symmetric matrix

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Solvers/MeshLinearization.h` (Public)


#### class `UE::Geometry::FVertexLinearization`  
`class FVertexLinearization : public FElementLinearization`  
_L22-110_
- inherits: `FElementLinearization`
- desc: Used to linearize the VtxIds in a mesh as a single array and allow mapping from array offset to mesh VtxId. Generally, the array offset will correspond to a matrix row when forming a Laplacian. The last NumBoundaryVerts are the boundary verts. This may be zero.
- L25 _public prototype_ `FVertexLinearization() = default;`
- L33 _public function_ `template<typename MeshType> FVertexLinearization(const MeshType& Mesh, bool bRemapBoundary = true)` — @param Mesh 			  The mesh to lineralize. @param bRemapBoundary  If true, will move the boundary vertices to the end of the arrays and record the number of boundary vertices.
- L39 _public function_ `template<typename MeshType> void Reset(const MeshType& Mesh, bool bRemapBoundary = true)`
- L50 _public function_ `int32 NumVerts() const`
- L52 _public function_ `int32 NumBoundaryVerts() const`
- L58 _private function_ `template<typename MeshType> void RemapBoundaryVerts(const MeshType& DynamicMesh)` — Moves the boundary verts to the end of the arrays and records the number of boundary verts
- L107 _private prototype_ `FVertexLinearization(const FVertexLinearization&);`
- L109 _private member_ `int32 NumBndryVerts = 0;`

#### class `UE::Geometry::FTriangleLinearization`  
`class FTriangleLinearization : public FElementLinearization`  
_L118-139_
- inherits: `FElementLinearization`
- desc: Used linearize the TriIds in a mesh as a single array and allow mapping from array offset to mesh TriId.
- L121 _public prototype_ `FTriangleLinearization() = default;`
- L123 _public function_ `FTriangleLinearization(const FDynamicMesh3& DynamicMesh)`
- L128 _public function_ `void Reset(const FDynamicMesh3& DynamicMesh)`
- L134 _public function_ `int32 NumTris() const`
- L138 _private prototype_ `FTriangleLinearization(const FTriangleLinearization&);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Solvers/MeshParameterizationSolvers.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshDeformation` (scope `UE`)
- L20 _prototype_ `TUniquePtr<UE::Solvers::IConstrainedMeshUVSolver> ConstructNaturalConformalParamSolver(const FDynamicMesh3& DynamicMesh);` (scope `UE::MeshDeformation`) — Create solver for the Least Squares Conformal UV Parameterization for this mesh. @warning Assumption is that mesh is a single connected component.
- L26 _prototype_ `TUniquePtr<UE::Solvers::IConstrainedMeshUVSolver> ConstructSpectralConformalParamSolver(const FDynamicMesh3& DynamicMesh, bool bPreserveIrregularity);` (scope `UE::MeshDeformation`) — Create solver for the Spectral Conformal UV Parameterization for this mesh. @warning Assumption is that mesh is a single connected component.

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Solvers/MeshSmoothing.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshDeformation` (scope `UE`)
- L40 _prototype_ `void ComputeSmoothing_BiHarmonic(const ELaplacianWeightScheme WeightingScheme, const FDynamicMesh3& OriginalMesh, const double Speed, const double Weight, const int32 NumIterations, TArray<FVector3d>& PositionArray, FProgressCancel* Progress = nullptr);` (scope `UE::MeshDeformation`) — This is equivalent to taking a single backward Euler time step of bi-harmonic diffusion where L is the Laplacian (Del^2) , and L^T L is an approximation of the Del^4. dp/dt = - k*k L^T L[p] p^{n+1} + dt * k * k L^TL [p^{n+1}] = p^{n} re-write as L^TL[p^{n+1}] + weight * weight p^{n+1} = weight * weight p^{n} with weight = 1 / (k * Sqrt[dt] ) The result is returned in the PositionArray Note: if canceled using the optional FProgressCancel, the results may be in an unusable state.
- L43 _prototype_ `void ComputeSmoothing_ImplicitBiHarmonicPCG(const ELaplacianWeightScheme WeightScheme, const FDynamicMesh3& OriginalMesh, const double Speed, const double Weight, const int32 MaxIterations, TArray<FVector3d>& PositionArray);` (scope `UE::MeshDeformation`)
- L58 _prototype_ `void ComputeSmoothing_Diffusion(const ELaplacianWeightScheme WeightScheme, const FDynamicMesh3& OriginalMesh, bool bForwardEuler, const double Speed, double Weight, const int32 NumIterations, TArray<FVector3d>& PositionArray, FProgressCancel* Progress = nullptr);` (scope `UE::MeshDeformation`) — This is equivalent to forward or backward Euler time steps of the diffusion equation dp/dt = L[p] p^{n+1} = p^{n} + dt L[p^{n}] with dt = Speed / Max(|w_ii|) here w_ii are the diagonal values of L Note: if canceled using the optional FProgressCancel, the results may be in an unusable state.
- L74 _prototype_ `void ComputeSmoothing_Forward(bool bUniformWeightScheme, bool bSmoothBoundary, const FDynamicMesh3& OriginalMesh, TFunctionRef<double(int VID, bool bBoundary)> GetSmoothingAlpha, const int32 NumIterations, TArray<FVector3d>& PositionArray, class FProgressCancel* Progress = nullptr);` (scope `UE::MeshDeformation`) — Simple iterative smoothing with an optional weight map Each iteration Lerps towards the weighted neighbor centroid by the GetSmoothingAlpha amount @param bUniformWeightScheme If true, uses uniform weights for centroid; else uses cotan weights @param bSmoothBoundary If true, boundary vertices are smoothed (toward the centroid of neighboring boundary vertices); else boundary is fixed @param OriginalMesh The source mesh, used for topology @param GetSmoothingAlpha The amount to lerp each vertex towards the centroid, per iteration @param NumIterations Number of iterations to smooth @param PositionsArray Vertex positions (input and output) @param Progress An optional interrupter that can terminate the iterations, leaving the results in an unusable state.

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Solvers/PrecomputedMeshWeightData.h` (Public)


#### class `UE::MeshDeformation::CotanTriangleData`  
`class CotanTriangleData`  
_L52-148_
- desc: The per-triangle data used in constructing the cotangent weighted laplacian.
- L56 _public typedef_ `typedef FVector3d TriangleVertices[3];`
- L58 _public prototype_ `CotanTriangleData() = default;`
- L60 _public function_ `CotanTriangleData(const FDynamicMesh3& DynamicMesh, int32 TriId)`
- L65 _public prototype_ `void Initialize(const FDynamicMesh3& DynamicMesh, int32 SrcTriId);`
- L67 _public function_ `int32 GetLocalEdgeIdx(const int32 DynamicsMeshEdgeId) const`
- L91 _public function_ `double GetOpposingCotangent(const int32 DynamicsMeshEdgeId, bool& bValid) const` — helper to return the cotangent of the angle opposite the given edge @param DynamicsMeshEdgeId is the id used by FDynamicMesh3 for this edge. @param bValid will false on return if the requested edge is not part of this triangle @return Cotangent of the opposite angle.
- L106 _public function_ `double GetOpposingCotangent(const int32 DynamicsMeshEdgeId) const`
- L114 _public function_ `bool bIsObtuse() const`
- L124 _public member_ `static constexpr double SmallTriangleArea = SMALL_NUMBER;` — 1.e-8;
- L127 _public member_ `int32 TriId = -1;` — testing
- L133 _public member_ `double Cotangent[3] = { 0. };`
- L137 _public member_ `double VoronoiArea[3] = { 0. };`
- L141 _public member_ `double Area = -1;`
- L146 _public member_ `int32 OppositeEdge[3] = { -1 };`

#### class `UE::MeshDeformation::MeanValueTriangleData`  
`class MeanValueTriangleData`  
_L155-199_
- desc: The per-triangle data used in constructing the mean-value weighted laplacian.
- L160 _public prototype_ `void Initialize(const FDynamicMesh3& DynamicMesh, int32 SrcTriId);`
- L163 _public function_ `double GetTanHalfAngle(int32 VtxId) const` — return Tan(angle / 2) for the corner indicated by this vert id.
- L177 _public function_ `double GetEdgeLength(int32 EdgeId) const` — return the length of the indicated edge
- L191 _public member_ `int32 TriId = -1;`
- L192 _public member_ `FIndex3i TriVtxIds;`
- L193 _public member_ `FIndex3i TriEdgeIds;`
- L195 _public member_ `bool bDegenerate = true;`
- L197 _public member_ `double EdgeLength[3] = { 0. };`
- L198 _public member_ `double TanHalfAngle[3] = { 0. };`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DYNAMICMESH_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshDeformation` (scope `UE`)
- L20 _function_ `template<typename MeshT> int32 ComputeNumMatrixElements(const MeshT& DynamicMesh, const TArray<int32>& ToVtxId)` (scope `UE::MeshDeformation`) — Utility to compute the number of elements in the sparse laplacian matrix
- L208 _function_ `template <typename TriangleDataType> void ConstructTriangleDataArray(const FDynamicMesh3& DynamicMesh, const FTriangleLinearization& TriangleLinearization, TArray<TriangleDataType>& TriangleDataArray)` (scope `UE::MeshDeformation`) — Return and array in triangle order that holds the per-triangle derived data needed
- L228 _function_ `` (scope `UE::MeshDeformation::ConstructTriangleDataArray`)
- L248 _prototype_ `void ConstructEdgeCotanWeightsDataArray(const FDynamicMesh3& Mesh, TArray<double>& EdgeWeightsDataArray, double ClampMin = -1.e5, double ClampMax = 1.e5);` (scope `UE::MeshDeformation`) — @return Edge cotanget weights. @todo Add an option to return the weights computed on an intrinsic mesh.

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/SubRegionRemesher.h` (Public)


#### class `UE::Geometry::FSubRegionRemesher`  
`class FSubRegionRemesher : public FRemesher`  
_L25-464_
- inherits: `FRemesher`
- desc: FSubRegionRemesher is an extension of FRemesher that allows for constraining remeshing to a localized region of a mesh. Currently this is initialized from a Vertex ROI. @warning Currently "boundary" edges of the ROI that are split will result in the ROI growing to include both new edges created by the split.
- L33 _protected member_ `TSet<int> VertexROI;` — Set of vertices in ROI. You add vertices here initially, then we will update the list during each Remesh pass
- L37 _protected member_ `TSet<int> EdgeROI;` — active set of edges we will consider for remeshing. This set is updated on each edge flip/split/collapse, but is not used during the pass.
- L42 _protected member_ `TSet<int> TriangleROI;` — Active set of triangles. This is conservative, ideally contains one-rings of all edge-vertices of EdgeROI set, but may include additional triangles accumulated over time (should *not* contain any triangles that no longer exist)
- L45 _protected member_ `TArray<int> Edges;` — static list of edges to consider during a pass (set in UpdateROI which must be called each pass)
- L48 _protected member_ `int CurEdge = -1;` — index of current edge in .Edges we are at in StartEdges/GetNextEdge modulo-iteration
- L51 _protected member_ `TSet<int> RemovedLastPassTris;` — set of triangles removed in last pass. Enable this by calling BeginTrackRemovedTrisInPass()
- L55 _protected member_ `FUniqueIndexSet InitialROIEdgeVertices;` — `UE_DEPRECATED(5.6, "This member is no longer used")` — When deleted, remove PRAGMA_DISABLE_DEPRECATION_WARNINGS / PRAGMA_ENABLE_DEPRECATION_WARNINGS from ~FSubRegionRemesher()
- L59 _protected member_ `FUniqueIndexSet InitialROITriangles;` — temporary data structure used to quickly convert vertex set to triangle set. Currenlty it is faster to construct this and then copy to a properly-sized TSet, than to incrementally build the TSet
- L62 _protected member_ `bool bTrackRemoved = false;` — controls whether RemovedLastPass will be populated
- L65 _protected member_ `uint32 LastUpdateROICounter = 0;` — counters for making sure that UpdateROI has been called
- L66 _protected member_ `uint32 LastRemeshPassCounter = 0;`
- L72 _public function_ `FSubRegionRemesher(FDynamicMesh3* Mesh) : FRemesher(Mesh)`
- L80 _public prototype_ `virtual ~FSubRegionRemesher() = default;`
- L83 _public function_ `void Reset()`
- L95 _public function_ `void SetInitialVertexROI(const TSet<int>& Vertices)`
- L100 _public function_ `void SetInitialVertexROI(TSet<int>&& Vertices)`
- L105 _public function_ `void SetInitialVertexROI(const TArray<int>& Vertices)`
- L119 _public function_ `void InitializeFromVertexROI()` — Initialize edge-subregion ROI from the VertexROI member that has been externally initialized. Edge ROI is initialized to fully-contained edges (i.e. both endpoints are in VertexROI).
- L164 _public function_ `void InitializeFromTriangleROI(const TSet<int>& InTriangleROI)`
- L188 _public function_ `void UpdateROI()` — Update the internal data structures in preparation for a call to FRemesher::BasicRemeshPass. This must be called before each remesh pass!
- L201 _public function_ `void BeginTrackRemovedTrisInPass()` — Call before BasicRemeshPass() to enable tracking of removed triangles
- L211 _public function_ `const TSet<int32>& EndTrackRemovedTrisInPass()` — Call after BasicRemeshPass() to disable and return tracking of removed triangles @return set of removed triangles. This set will be cleared on next call to BeginTrackRemovedTrisInPass()
- L222 _public function_ `virtual void BasicRemeshPass() override` — forwards to FRemesher::BasicRemeshPass
- L236 _public function_ `void SaveActiveROI(FDynamicMeshChangeTracker* Change)` — Tell a MeshChangeTracker about the set of triangles that we might modify in the next remesh pass. This could include one-rings of either side of an edge in the ROI, if we collapse.
- L247 _public function_ `const TSet<int>& GetCurrentVertexROI() const` — @return
- L255 _public function_ `const TSet<int>& GetCurrentTriangleROI() const` — @return set of triangles that contains edge ROI (note: may also contain additional triangles)
- L263 _public function_ `const TSet<int>& GetCurrentEdgeROI() const` — @return set of edges in current edge ROI
- L272 _public function_ `const TArray<int>& GetCurrentEdgeArray() const` — @return current edge array. @warning This is only valid after calling UpdateROI() and before calling BasicRemeshPass().
- L284 _public function_ `TSet<int>&& ExtractFinalTriangleROI()` — Extract final triangle ROI. After calling this function, the ROI will be cleared, and must be re-initialized. This can be used to avoid having to copy the TSet. @return set of triangles that contains edge ROI (note: may also contain additional triangles)
- L296 _protected function_ `virtual int StartEdges() override`
- L302 _protected function_ `virtual int GetNextEdge(int CurEdgeID, bool& bDone) override`
- L326 _protected function_ `virtual void OnEdgeSplit(int EdgeID, int VertexA, int VertexB, const FDynamicMesh3::FEdgeSplitInfo& SplitInfo) override`
- L354 _protected function_ `virtual void OnEdgeCollapse(int EdgeID, int VertexA, int VertexB, const FDynamicMesh3::FEdgeCollapseInfo& CollapseInfo) override`
- L386 _protected function_ `virtual void OnEdgeFlip(int EdgeID, const FDynamicMesh3::FEdgeFlipInfo& FlipInfo)`
- L400 _protected function_ `void AddVertexToTriangleROI(int VertexID)`
- L408 _protected function_ `void AddEdgeToTriangleROI(int EdgeID)`
- L417 _protected function_ `EVertexControl VertexFilter(int VertexID)`
- L430 _protected member_ `TArray<int32> SmoothIndices;`
- L431 _protected member_ `TArray<FVector3d> SmoothedPositions;`
- L433 _protected function_ `virtual void FullSmoothPass_Buffer(bool bParallel) override`

#### class `UE::Geometry::FRestrictedSubRegionRemesher`  
`class FRestrictedSubRegionRemesher : public FSubRegionRemesher`  
_L473-575_
- inherits: `FSubRegionRemesher`
- desc: FRestrictedSubRegionRemesher is similar to FSubRegionRemesher but does not allow the ROI to grow outside of the original ROI boundary. It is initialized from a set of Triangles and the initial ROI boundary is inferred from those triangles.
- L478 _public function_ `FRestrictedSubRegionRemesher(FDynamicMesh3* Mesh, const TSet<int>& InTriangleROI) : FSubRegionRemesher(Mesh)`
- L485 _public function_ `void OnEdgeSplit(int EdgeID, int VertexA, int VertexB, const FDynamicMesh3::FEdgeSplitInfo& SplitInfo) override`
- L520 _public function_ `void OnEdgeFlip(int EdgeID, const FDynamicMesh3::FEdgeFlipInfo& FlipInfo) override`
- L537 _private function_ `bool EdgeVerticesAreInVertexROI(int EdgeID) const`
- L543 _private function_ `bool TriangleEdgesAreInEdgeROI(int TriangleID) const`
- L549 _private function_ `bool EdgeIsROIBoundary(int EdgeID) const`
- L555 _private function_ `void InitializeFromTriangleROI(const TSet<int>& InTriangleROI)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)
- L74 _function_ `VertexControlF = [this](int vid)` (scope `UE::Geometry::FSubRegionRemesher::FSubRegionRemesher`)
- L132 _function_ `` (scope `UE::Geometry::FSubRegionRemesher::InitializeFromVertexROI`)
- L403 _function_ `` (scope `UE::Geometry::FSubRegionRemesher::AddVertexToTriangleROI`)
- L448 _function_ `` (scope `UE::Geometry::FSubRegionRemesher::FullSmoothPass_Buffer`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Tessellation/AdaptiveDisplacement.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)
- L31 _prototype_ `bool ApplyAdaptiveDisplacement( FDynamicMesh3& Mesh, FDynamicMeshUVOverlay* UVOverlay, const FDisplacementMap& DisplacementMap, const FAdaptiveTessellatorOptions& Options, const float FeatureSensitivity, FMeshConstraints& MeshConstraints, TBitArray<>& ActiveTriangles, const bool bApplyPostOptimization = true );` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/DynamicMesh/Public/Tessellation/DynamicMeshPolicy.h` (Public)


#### class `UE::Geometry::FDynamicMesh3Policy`  
`class FDynamicMesh3Policy`  
_L21-320_
- desc: Mesh policy on FDynamicMesh3 for use with FAdaptiveTesselator2
- L23 _private function_ `inline static constexpr int32 NextEdge(int32 e)`
- L24 _private function_ `inline static constexpr int32 PrevEdge(int32 e)`
- L28 _public typedef_ `using VecType = FVector3d;`
- L29 _public typedef_ `using RealType = double;`
- L31 _public function_ `FDynamicMesh3Policy( FDynamicMesh3& InMesh, FMeshConstraints& InConstraints)`
- L40 _public function_ `inline int32 GetVertexIndex(const int32 TriIndex, const int32 TriEdgeIndex) const`
- L45 _public function_ `inline FIndex3i GetTriangle(const int32 TriIndex) const`
- L50 _public function_ `inline FVector3d GetVertexPosition(const int TriIndex, const int TriEdgeIndex) const`
- L55 _public function_ `inline FVector3d GetVertexPosition(const int32 VertexIndex) const`
- L60 _public function_ `inline void SetVertexPosition(const int32 VertexIndex, const FVector3d Position) const`
- L65 _public function_ `inline void GetTriVertices(int TriIndex, FVector3d& P0, FVector3d& P1, FVector3d& P2) const`
- L70 _public function_ `inline int32 MaxVertexID() const`
- L75 _public function_ `inline bool IsValidVertex(int32 VertexID) const`
- L80 _public function_ `inline int32 TriangleCount2() const`
- L85 _public function_ `inline int32 MaxTriID() const`
- L90 _public function_ `inline bool IsValidTri(int32 TriIndex) const`
- L95 _public function_ `inline int32 GetAdjTriangle(const int32 TriIndex, const int32 TriEdgeIndex) const`
- L108 _public function_ `inline TPair<int32,int32> GetAdjEdge(const int32 TriIndex, const int32 TriEdgeIndex) const` — (triangle index, edge index in 0..2)
- L147 _public function_ `inline bool EdgeManifoldCheck(const int32 TriIndex, const int32 TriEdgeIndex) const`
- L155 _public function_ `inline bool AllowEdgeFlip(const int32 TriIndex, const int32 TriEdgeIndex, const int32 AdjTriIndex ) const`
- L168 _public function_ `inline bool AllowEdgeSplit(const int32 TriIndex, const int32 TriEdgeIndex ) const`
- L181 _public function_ `inline FVector3d GetTriangleNormal(const int32 TriIndex) const`
- L193 _public function_ `UE::Geometry::FEdgeSplitInfo SplitEdge(const int32 TriIndex, const int32 TriEdgeIndex, const double SplitWeight )`
- L231 _public function_ `UE::Geometry::FPokeInfo PokeTriangle(const int32 TriIndex, const FVector3d Barycentrics)`
- L275 _public function_ `UE::Geometry::FFlipEdgeInfo FlipEdge(const int32 TriIndex, const int32 TriEdgeIndex)`
- L314 _public function_ `static constexpr bool IsTriangleSoup()`
- L317 _private member_ `FDynamicMesh3& Mesh;`
- L318 _private member_ `FMeshConstraints& Constraints;`
- L319 _private member_ `const bool bHasEdgeConstraints;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Geometry` (scope `UE`)
