# Plugins / ChaosFleshDeprecatedNodes

- module root: `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshDeprecatedNodes`
- headers: 6; symbols: 93
- symbol kinds: class=1, delegate=1, function=8, member=49, namespace=4, prototype=15, struct=11, typedef=4
- PublicDependencyModuleNames: Chaos, ChaosCore, ChaosFlesh, ChaosFleshEngine, ChaosFleshNodes, Core, CoreUObject, DataflowCore, DataflowEngine, Engine, GeometryAlgorithms, GeometryCore, MeshConversion, MeshConversionEngineTypes, MeshDescription, TetMeshing

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshDeprecatedNodes/Public/Dataflow/ChaosFleshConstructTetGridNode.h` (Public)


#### struct `FConstructTetGridNode`  
`struct FConstructTetGridNode : public FDataflowNode`  
_L14-42_
- reflection: `USTRUCT(meta = (DataflowFlesh, Deprecated = "5.4"))`
- inherits: `FDataflowNode`
- L20 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L23 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection"))`
- L26 _public member_ `FIntVector GridCellCount = FIntVector(10, 10, 10);` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "1"))`
- L29 _public member_ `FVector GridDomain = FVector(10.0, 10.0, 10.0);` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0"))`
- L32 _public member_ `bool bDiscardInteriorTriangles = true;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L34 _public function_ `FConstructTetGridNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L41 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshDeprecatedNodes/Public/Dataflow/ChaosFleshCreateTetrahedralCollectionNode.h` (Public)


#### struct `FGenerateTetrahedralCollectionDataflowNodes`  
`struct FGenerateTetrahedralCollectionDataflowNodes : public FDataflowNode`  
_L27-121_
- reflection: `USTRUCT(meta = (DataflowFlesh, Deprecated = "5.4"))`
- inherits: `FDataflowNode`
- desc: Note: disabled deprecation warnings due to deprecated member: IdealEdgeLength. Can remove these disable/enable pragmas once that member variable is removed.
- L34 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L37 _public member_ `TEnumAsByte<TetMeshingMethod> Method = TetMeshingMethod::IsoStuffing;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L44 _public member_ `int32 NumCells = 32;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "1", EditCondition = "Method == TetMeshingMethod::IsoStuffing", EditConditionHides))`
- L47 _public member_ `double OffsetPercent = 0.05;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "-0.5", ClampMax = "0.5", EditCondition = "Method == TetMeshingMethod::IsoStuffing", EditConditionHides))`
- L55 _public member_ `double IdealEdgeLengthRel = 0.05;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Desired relative edge length, as a fraction of bounding box size
- L58 _public member_ `double IdealEdgeLength = 0.05;` — `UE_DEPRECATED(5.6, "Use IdealEdgeLengthRel instead, which is relative to the bounding box size")`
- L62 _public member_ `int32 MaxIterations = 80;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "1", EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Maximum number of optimization iterations.
- L66 _public member_ `double StopEnergy = 10;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Energy at which to stop optimizing tet quality and accept the result.
- L70 _public member_ `double EpsRel = 1e-3;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Relative tolerance, controlling how closely the mesh must follow the input surface.
- L74 _public member_ `bool bCoarsen = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Coarsen the tet mesh result.
- L78 _public member_ `bool bExtractManifoldBoundarySurface = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Enforce that the output boundary surface should be manifold.
- L82 _public member_ `bool bSkipSimplification = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Skip the initial simplification step.
- L86 _public member_ `bool bInvertOutputTets = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Invert tetrahedra.
- L93 _public member_ `TObjectPtr<const UStaticMesh> StaticMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "StaticMesh"))`
- L96 _public member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L99 _public member_ `bool bComputeByComponent = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L102 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection"))`
- L105 _public member_ `bool bDiscardInteriorTriangles = true;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L107 _public function_ `FGenerateTetrahedralCollectionDataflowNodes(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L116 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L119 _protected prototype_ `void EvaluateIsoStuffing(UE::Dataflow::FContext& Context, TUniquePtr<FFleshCollection>& InCollection, const UE::Geometry::FDynamicMesh3& DynamicMesh) const;`
- L120 _protected prototype_ `void EvaluateTetWild(UE::Dataflow::FContext& Context, TUniquePtr<FFleshCollection>& InCollection, const UE::Geometry::FDynamicMesh3& DynamicMesh) const;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshDeprecatedNodes/Public/Dataflow/ChaosFleshDeprecatedNodesPlugin.h` (Public)


#### class `IChaosFleshDeprecatedNodesPlugin`  
`class IChaosFleshDeprecatedNodesPlugin : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshDeprecatedNodes/Public/Dataflow/ChaosFleshImportGEO.h` (Public)


#### struct `FGEOMapStringInt`  
`struct FGEOMapStringInt`  
_L16-20_
- reflection: `USTRUCT(meta = (DataflowFlesh, Deprecated = "5.4"))`
- desc: Transient Dataflow container for \c TMap<FString, int32>.
- L19 _public member_ `TMap<FString, int32> IntVars;`

#### struct `FGEOMapStringArrayInt`  
`struct FGEOMapStringArrayInt`  
_L24-28_
- reflection: `USTRUCT(meta = (DataflowFlesh, Deprecated = "5.4"))`
- desc: Transient Dataflow container for \c TMap<FString, TArray<int32>>.
- L27 _public member_ `TMap<FString, TArray<int32>> IntVectorVars;`

#### struct `FGEOMapStringArrayFloat`  
`struct FGEOMapStringArrayFloat`  
_L32-36_
- reflection: `USTRUCT(meta = (DataflowFlesh, Deprecated = "5.4"))`
- desc: Transient Dataflow container for \c TMap<FString, TArray<float>>.
- L35 _public member_ `TMap<FString, TArray<float>> FloatVectorVars;`

#### struct `FExtractGEOInt`  
`struct FExtractGEOInt : public FDataflowNode`  
_L40-66_
- reflection: `USTRUCT(meta = (DataflowFlesh, Deprecated = "5.4"))`
- inherits: `FDataflowNode`
- desc: Extract a named integer from the results of an ImportGEO node.
- L52 _public member_ `FString VarName;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — Variable name to extract the value for. (See output log from ImportGEO for available list.)
- L56 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowOutput))` — Output value.
- L58 _public function_ `FExtractGEOInt(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L65 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FExtractGEOIntVector`  
`struct FExtractGEOIntVector : public FDataflowNode`  
_L70-96_
- reflection: `USTRUCT(meta = (DataflowFlesh, Deprecated = "5.4"))`
- inherits: `FDataflowNode`
- desc: Extract a named integer array from the results of an ImportGEO node.
- L82 _public member_ `FString VarName;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — Variable name to extract the value for. (See output log from ImportGEO for available list.)
- L86 _public member_ `TArray<int32> Value;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowOutput))` — Output value.
- L88 _public function_ `FExtractGEOIntVector(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L95 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FExtractGEOFloatVector`  
`struct FExtractGEOFloatVector : public FDataflowNode`  
_L100-126_
- reflection: `USTRUCT(meta = (DataflowFlesh, Deprecated = "5.4"))`
- inherits: `FDataflowNode`
- desc: Extract a named float array from the results of an ImportGEO node.
- L112 _public member_ `FString VarName;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — Variable name to extract the value for. (See output log from ImportGEO for available list.)
- L116 _public member_ `TArray<float> Value;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowOutput))` — Output value.
- L118 _public function_ `FExtractGEOFloatVector(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L125 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FImportGEO`  
`struct FImportGEO : public FDataflowNode`  
_L130-196_
- reflection: `USTRUCT(meta = (DataflowFlesh, Deprecated = "5.4"))`
- inherits: `FDataflowNode`
- desc: Import data from GEO file.
- L142 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DisplayName = "Collection"))` — Passthrough geometry collection, used only for tetrahedron mesh extraction.
- L150 _public member_ `bool bImportTetrahedronMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — Import the tetrahedron mesh from the GEO file.
- L157 _public member_ `bool bDiscardInteriorTriangles = true;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — If \c false, all triangles on the interior of the tetrahedral mesh are retained in the mesh, which is useful for debugging, but makes rendering more costly.
- L165 _public member_ `FGEOMapStringInt IntVarsOutput;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowOutput, DisplayName = "IntVars"))` — Integer outputs. Use ExtractGEOInt node.
- L169 _public member_ `FGEOMapStringArrayInt IntVectorVarsOutput;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowOutput, DisplayName = "IntVectorVars"))` — Integer array outputs. Use ExtractGEOIntVector node.
- L173 _public member_ `FGEOMapStringArrayFloat FloatVectorVarsOutput;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowOutput, DisplayName = "FloatVectorVars"))` — Float array outputs. Use ExtractGEOFloatVector node.
- L175 _public function_ `FImportGEO(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L185 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L188 _protected prototype_ `bool ReadGEOFile(const bool PrintStats=true) const;`
- L190 _protected member_ `mutable FString FilePath;`
- L191 _protected member_ `mutable FDateTime FileModTime;`
- L192 _protected member_ `mutable TMap<FString, int32> IntVars;`
- L193 _protected member_ `mutable TMap<FString, TArray<int32>> IntVectorVars;`
- L194 _protected member_ `mutable TMap<FString, TArray<float>> FloatVectorVars;`
- L195 _protected member_ `mutable TMap<FString, TPair<TArray<std::string>, TArray<int32>>> IndexedStringVars;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogImportGEO, Verbose, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogImportGEO, Verbose, All);`
- L198 _namespace_ `namespace UE`
- L198 _namespace_ `namespace Dataflow` (scope `UE`)
- L200 _prototype_ `void RegisterChaosFleshImportGEONodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshDeprecatedNodes/Public/Dataflow/ChaosFleshKinematicOriginInsertionInitializationNode.h` (Public)


#### struct `FKinematicOriginInsertionInitializationDataflowNode`  
`struct FKinematicOriginInsertionInitializationDataflowNode : public FDataflowNode`  
_L14-46_
- reflection: `USTRUCT(meta = (DataflowFlesh, Deprecated = "5.4"))`
- inherits: `FDataflowNode`
- desc: @todo(deprecate), rename to FKinematicSomethingBetterThanThisNameDataflowNode
- L20 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L23 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L26 _public member_ `TArray<int32> OriginVertexIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "OriginSelectionSet"))`
- L29 _public member_ `TArray<int32> InsertionVertexIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "InsertionSelectionSet"))`
- L32 _public member_ `TObjectPtr<USkeletalMesh> BoneSkeletalMeshIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "BoneSkeletalMesh"))`
- L35 _public function_ `FKinematicOriginInsertionInitializationDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L45 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshDeprecatedNodes/Public/Dataflow/ChaosFleshKinematicTetrahedralConstraintNode.h` (Public)


#### struct `FKinematicTetrahedralBindingsDataflowNode`  
`struct FKinematicTetrahedralBindingsDataflowNode : public FDataflowNode`  
_L15-41_
- reflection: `USTRUCT(meta = (DataflowFlesh, Deprecated = "5.4"))`
- inherits: `FDataflowNode`
- desc: @todo(deprecate), rename to FKinematicTetrahedralConstraintDataflowNode ... This should really be a mode on the KinematicConstraint.
- L21 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L24 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMeshIn = nullptr;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L27 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L30 _public member_ `FString ExclusionList = "tw` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L32 _public function_ `FKinematicTetrahedralBindingsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L40 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
