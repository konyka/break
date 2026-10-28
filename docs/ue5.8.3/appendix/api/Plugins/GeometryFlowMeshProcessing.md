# Plugins / GeometryFlowMeshProcessing

- module root: `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing`
- headers: 30; symbols: 568
- symbol kinds: class=35, enum=15, enumerator=85, function=131, macro=12, member=112, namespace=73, prototype=50, struct=30, typedef=25
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryAlgorithms, GeometryCore, GeometryFlowCore

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/DataTypes/CollisionGeometryData.h` (Public)


#### struct `UE::GeometryFlow::FCollisionGeometry`  
`struct FCollisionGeometry`  
_L19-24_
- L21 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(EMeshProcessingDataTypes::CollisionGeometry);`
- L23 _public member_ `UE::Geometry::FSimpleShapeSet3d Geometry;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L32 _typedef_ `typedef TTransferNode<FCollisionGeometry, (int)EMeshProcessingDataTypes::CollisionGeometry> FCollisionGeometryTransferNode;` (scope `UE::GeometryFlow`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/DataTypes/DynamicMeshData.h` (Public)


#### struct `UE::GeometryFlow::TSerializationMethod`  
`template<> struct TSerializationMethod<FDynamicMesh3>`  
_L22-22_
- desc: declares FDataDynamicMesh, FDynamicMeshInput, FDynamicMeshOutput, FDynamicMeshSourceNode
- L22 _public function_ `template<> struct TSerializationMethod<FDynamicMesh3>` — declares FDataDynamicMesh, FDynamicMeshInput, FDynamicMeshOutput, FDynamicMeshSourceNode

#### class `UE::GeometryFlow::FDynamicMeshSourceNode`  
`class FDynamicMeshSourceNode : public TSourceNodeBase<FDynamicMesh3, (int)EMeshProcessingDataTypes::DynamicMesh>`  
_L26-30_
- inherits: `TSourceNodeBase<FDynamicMesh3,(int)EMeshProcessingDataTypes::DynamicMesh>`
- L28 _private member_ `static constexpr int Version = 1;`

#### class `UE::GeometryFlow::FDynamicMeshTransferNode`  
`class FDynamicMeshTransferNode : public TTransferNode<FDynamicMesh3, (int)EMeshProcessingDataTypes::DynamicMesh>`  
_L33-37_
- inherits: `TTransferNode<FDynamicMesh3,(int)EMeshProcessingDataTypes::DynamicMesh>`
- L35 _private member_ `static constexpr int Version = 1;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L23 _typedef_ `typedef TMovableData<FDynamicMesh3, (int)EMeshProcessingDataTypes::DynamicMesh> FDataDynamicMesh;` (scope `UE::GeometryFlow`)
- L24 _typedef_ `typedef TBasicNodeInput<FDynamicMesh3, (int)EMeshProcessingDataTypes::DynamicMesh> FDynamicMeshInput;` (scope `UE::GeometryFlow`)
- L25 _typedef_ `typedef TBasicNodeOutput<FDynamicMesh3, (int)EMeshProcessingDataTypes::DynamicMesh> FDynamicMeshOutput;` (scope `UE::GeometryFlow`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/DataTypes/IndexSetsData.h` (Public)


#### struct `UE::GeometryFlow::FIndexSets`  
`struct FIndexSets`  
_L15-49_
- L17 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(EMeshProcessingDataTypes::IndexSets);`
- L19 _public member_ `TArray<TArray<int32>> IndexSets;`
- L25 _public function_ `void AppendSet()` — utility functions
- L31 _public function_ `void AppendSet(const TArray<int32>& SetValues)`
- L36 _public function_ `int32 NumSets() const`
- L39 _public function_ `template<typename ListType> void GetAllValues(ListType& ValuesOut) const`

#### struct `UE::GeometryFlow::TSerializationMethod`  
`template<> struct TSerializationMethod<FIndexSets>`  
_L53-53_
- desc: declares FDataIndexSets, FIndexSetsInput, FIndexSetsOutput, FIndexSetsSourceNode
- L53 _public function_ `template<> struct TSerializationMethod<FIndexSets>` — declares FDataIndexSets, FIndexSetsInput, FIndexSetsOutput, FIndexSetsSourceNode

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/DataTypes/MeshImageBakingData.h` (Public)


#### struct `FMeshMakeBakingCacheSettings`  
`struct FMeshMakeBakingCacheSettings`  
_L19-35_
- reflection: `USTRUCT()`
- L23 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::MakeBakingCacheSettings);`
- L27 _public member_ `FIntPoint Dimensions{ EForceInit::ForceInit };` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")` — FImageDimensions Dimensions;
- L30 _public member_ `int32 UVLayer = 0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L33 _public member_ `float Thickness = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### struct `UE::GeometryFlow::FMeshBakingCache`  
`struct FMeshBakingCache`  
_L47-57_
- L49 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(EMeshProcessingDataTypes::BakingCache);`
- L52 _public member_ `FDynamicMesh3 DetailMesh;` — have to make copies of these - boo!
- L53 _public member_ `FDynamicMeshAABBTree3 DetailSpatial;`
- L54 _public member_ `FDynamicMesh3 TargetMesh;`
- L56 _public member_ `UE::Geometry::FMeshImageBakingCache BakeCache;`

#### class `UE::GeometryFlow::FMakeMeshBakingCacheNode`  
`class FMakeMeshBakingCacheNode : public FNode`  
_L69-96_
- inherits: `FNode`
- L72 _protected typedef_ `using SettingsDataType = TMovableData<FMeshMakeBakingCacheSettings, FMeshMakeBakingCacheSettings::DataTypeIdentifier>;`
- L73 _protected member_ `static constexpr int Version = 1;`
- L76 _public function_ `static const FString InParamDetailMesh()`
- L77 _public function_ `static const FString InParamTargetMesh()`
- L78 _public function_ `static const FString InParamSettings()`
- L80 _public function_ `static const FString OutParamCache()`
- L83 _public function_ `FMakeMeshBakingCacheNode()`
- L92 _public prototype_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSING_API`
- L38 _namespace_ `namespace UE`
- L40 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L45 _typedef_ `typedef FMeshMakeBakingCacheSettings FMeshMakeBakingCacheSettings;` (scope `UE::GeometryFlow`)
- L60 _typedef_ `typedef TImmutableData<FMeshBakingCache, FMeshBakingCache::DataTypeIdentifier> FMeshBakingCacheData;` (scope `UE::GeometryFlow`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/DataTypes/NormalMapData.h` (Public)


#### struct `UE::GeometryFlow::FNormalMapImage`  
`struct FNormalMapImage`  
_L18-23_
- L20 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(EMeshProcessingDataTypes::NormalMapImage);`
- L22 _public member_ `TImageBuilder<FVector3f> Image;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/DataTypes/TextureImageData.h` (Public)


#### struct `UE::GeometryFlow::FTextureImage`  
`struct FTextureImage`  
_L17-22_
- L19 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(EMeshProcessingDataTypes::TextureImage);`
- L21 _public member_ `TImageBuilder<FVector4f> Image;`

#### struct `UE::GeometryFlow::FMaterialIDToTextureMap`  
`struct FMaterialIDToTextureMap`  
_L28-33_
- L30 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(EMeshProcessingDataTypes::MaterialIDToTextureMap);`
- L32 _public member_ `TMap<int32, TSafeSharedPtr<TImageBuilder<FVector4f>>> MaterialIDTextureMap;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/DataTypes/WeightMapData.h` (Public)


#### struct `UE::GeometryFlow::FWeightMap`  
`struct FWeightMap`  
_L15-22_
- L17 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(EMeshProcessingDataTypes::WeightMap);`
- L19 _public member_ `TArray<float> Weights;`

#### struct `UE::GeometryFlow::TSerializationMethod`  
`template <> struct TSerializationMethod<FWeightMap>`  
_L26-26_
- desc: @todo - serialize, or reconsider this node as just being some form of graph output.
- L26 _public function_ `template <> struct TSerializationMethod<FWeightMap>` — @todo - serialize, or reconsider this node as just being some form of graph output.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/GeometryFlowMeshProcessingModule.h` (Public)


#### class `FGeometryFlowMeshProcessingModule`  
`class FGeometryFlowMeshProcessingModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryFlowMeshProcessing, Log, All);`

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshBakingNodes/BakeMeshMultiTextureNode.h` (Public)


#### struct `FBakeMeshMultiTextureSettings`  
`struct FBakeMeshMultiTextureSettings : public FBakeMeshTextureImageSettings`  
_L15-19_
- reflection: `USTRUCT()`
- inherits: `FBakeMeshTextureImageSettings`
- L18 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::BakeMultiTextureSettings);`

#### class `UE::GeometryFlow::FBakeMeshMultiTextureNode`  
`class FBakeMeshMultiTextureNode : public FNode`  
_L30-57_
- inherits: `FNode`
- L32 _private member_ `static constexpr int Version = 1;`
- L36 _protected typedef_ `using SettingsDataType = TMovableData<FBakeMeshMultiTextureSettings, FBakeMeshMultiTextureSettings::DataTypeIdentifier>;`
- L39 _public function_ `static const FString InParamBakeCache()`
- L40 _public function_ `static const FString InParamMaterialTextures()`
- L41 _public function_ `static const FString InParamSettings()`
- L42 _public function_ `static const FString OutParamTextureImage()`
- L45 _public function_ `FBakeMeshMultiTextureNode()`
- L53 _public prototype_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSING_API`
- L22 _namespace_ `namespace UE`
- L24 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshBakingNodes/BakeMeshNormalMapNode.h` (Public)


#### struct `FBakeMeshNormalMapSettings`  
`struct FBakeMeshNormalMapSettings`  
_L15-22_
- reflection: `USTRUCT()`
- L18 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::BakeNormalMapSettings);`
- L21 _public member_ `double MaxDistance = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### class `UE::GeometryFlow::FBakeMeshNormalMapNode`  
`class FBakeMeshNormalMapNode : public FNode`  
_L35-64_
- inherits: `FNode`
- L37 _private member_ `static constexpr int Version = 1;`
- L41 _protected typedef_ `using SettingsDataType = TMovableData<FBakeMeshNormalMapSettings, FBakeMeshNormalMapSettings::DataTypeIdentifier>;`
- L44 _public function_ `static const FString InParamBakeCache()`
- L45 _public function_ `static const FString InParamTangents()`
- L46 _public function_ `static const FString InParamSettings()`
- L48 _public function_ `static const FString OutParamNormalMap()`
- L51 _public function_ `FBakeMeshNormalMapNode()`
- L60 _public prototype_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSING_API`
- L24 _namespace_ `namespace UE`
- L26 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshBakingNodes/BakeMeshTextureImageNode.h` (Public)


#### struct `FBakeMeshTextureImageSettings`  
`struct FBakeMeshTextureImageSettings`  
_L14-24_
- reflection: `USTRUCT()`
- L17 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::BakeTextureImageSettings);`
- L20 _public member_ `int32 DetailUVLayer = 0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L23 _public member_ `double MaxDistance = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### class `UE::GeometryFlow::FBakeMeshTextureImageNode`  
`class FBakeMeshTextureImageNode : public FNode`  
_L36-65_
- inherits: `FNode`
- L38 _private member_ `static constexpr int Version = 1;`
- L42 _protected typedef_ `using SettingsDataType = TMovableData<FBakeMeshTextureImageSettings, FBakeMeshTextureImageSettings::DataTypeIdentifier>;`
- L45 _public function_ `static const FString InParamBakeCache()`
- L46 _public function_ `static const FString InParamImage()`
- L47 _public function_ `static const FString InParamSettings()`
- L49 _public function_ `static const FString OutParamTextureImage()`
- L52 _public function_ `FBakeMeshTextureImageNode()`
- L61 _public prototype_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSING_API`
- L26 _namespace_ `namespace UE`
- L28 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshDecompositionNodes/MakeTriangleSetsNode.h` (Public)


#### class `UE::GeometryFlow::FMakeTriangleSetsFromMeshNode`  
`class FMakeTriangleSetsFromMeshNode : public FNode`  
_L19-82_
- inherits: `FNode`
- L21 _private member_ `static constexpr int Version = 1;`
- L24 _public function_ `static const FString InParam()`
- L26 _public function_ `static const FString OutParamIndexSets()`
- L29 _public function_ `FMakeTriangleSetsFromMeshNode()`
- L36 _public function_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L66 _public function_ `virtual void CheckAdditionalInputs(const FNamedDataMap& DatasIn, bool& bRecomputeRequired, bool& bAllInputsValid)`
- L72 _public function_ `virtual void ComputeIndexSets(const FNamedDataMap& DatasIn, const FDynamicMesh3& Mesh, FIndexSets& SetsOut)`

#### class `UE::GeometryFlow::FMakeTriangleSetsFromGroupsNode`  
`class FMakeTriangleSetsFromGroupsNode : public FMakeTriangleSetsFromMeshNode`  
_L89-198_
- inherits: `FMakeTriangleSetsFromMeshNode`
- L91 _private member_ `static constexpr int Version = 1;`
- L94 _public function_ `static const FString InParamGroupLayer()`
- L95 _public function_ `static const FString InParamIgnoreGroups()`
- L98 _public function_ `FMakeTriangleSetsFromGroupsNode() : FMakeTriangleSetsFromMeshNode()`
- L108 _public function_ `virtual void CheckAdditionalInputs(const FNamedDataMap& DatasIn, bool& bRecomputeRequired, bool& bAllInputsValid) override`
- L116 _protected function_ `void ComputeIndexSetsForGroups(const FDynamicMesh3& Mesh, const TSet<int32>& IgnoreGroups, TFunction<int32(int)> TriangleGroupFn, FIndexSets& SetsOut)`
- L166 _public function_ `virtual void ComputeIndexSets(const FNamedDataMap& DatasIn, const FDynamicMesh3& Mesh, FIndexSets& SetsOut) override`

#### class `UE::GeometryFlow::FMakeTriangleSetsFromConnectedComponentsNode`  
`class FMakeTriangleSetsFromConnectedComponentsNode : public FMakeTriangleSetsFromMeshNode`  
_L201-218_
- inherits: `FMakeTriangleSetsFromMeshNode`
- L203 _private member_ `static constexpr int Version = 1;`
- L207 _public function_ `virtual void ComputeIndexSets(const FNamedDataMap& DatasIn, const FDynamicMesh3& Mesh, FIndexSets& SetsOut) override`

#### class `UE::GeometryFlow::FMakeTriangleSetsFromWeightMapNode`  
`class FMakeTriangleSetsFromWeightMapNode : public FMakeTriangleSetsFromMeshNode`  
_L224-273_
- inherits: `FMakeTriangleSetsFromMeshNode`
- desc: If one triangle vertex has a weight greater than the given threshold, include it in the output triangle set. TODO: Optionally make it so the *average* triangle vertex weight has to exceed the threshold. Or the minumum triangle vertex weight.
- L226 _private member_ `static constexpr int Version = 1;`
- L230 _public function_ `static const FString InParamWeightMap()`
- L231 _public function_ `static const FString InParamThreshold()`
- L233 _public function_ `FMakeTriangleSetsFromWeightMapNode() : FMakeTriangleSetsFromMeshNode()`
- L239 _public function_ `virtual void CheckAdditionalInputs(const FNamedDataMap& DatasIn, bool& bRecomputeRequired, bool& bAllInputsValid) override`
- L245 _public function_ `virtual void ComputeIndexSets(const FNamedDataMap& DatasIn, const FDynamicMesh3& Mesh, FIndexSets& SetsOut) override`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L182 _function_ `ComputeIndexSetsForGroups(Mesh, IgnoreGroups, [&Mesh](int TriangleID) { return Mesh.GetTriangleGroup(TriangleID); }, SetsOut);` (scope `UE::GeometryFlow::FMakeTriangleSetsFromGroupsNode::ComputeIndexSets`)
- L191 _function_ `ComputeIndexSetsForGroups(Mesh, IgnoreGroups, [&PolygroupLayer](int TriangleID) { return PolygroupLayer->GetValue(TriangleID); }, SetsOut);` (scope `UE::GeometryFlow::FMakeTriangleSetsFromGroupsNode::ComputeIndexSets`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodeRegistration.h` (Public)


#### struct `UE::GeometryFlow::FMeshProcessingNodeRegistration`  
`struct FMeshProcessingNodeRegistration`  
_L12-16_
- L15 _public prototype_ `static void RegisterNodes();` — Required registration of the geometry flow graph nodes in the MeshProcessing Module.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/CompactMeshNode.h` (Public)


#### class `UE::GeometryFlow::FCompactMeshNode`  
`class FCompactMeshNode : public FProcessMeshBaseNode`  
_L16-45_
- inherits: `FProcessMeshBaseNode`
- desc: FCompactMeshNode compacts the input mesh, to remove gaps in the vertex/triangle indexing. This node can be applied in-place.
- L18 _private member_ `static constexpr int Version = 1;`
- L22 _public function_ `FCompactMeshNode()`
- L28 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L37 _public function_ `virtual void ProcessMeshInPlace( const FNamedDataMap& DatasIn, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/GenerateConvexHullMeshNode.h` (Public)


#### struct `FGenerateConvexHullMeshSettings`  
`struct FGenerateConvexHullMeshSettings`  
_L12-22_
- reflection: `USTRUCT()`
- L15 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::GenerateConvexHullMeshSettings);`
- L18 _public member_ `bool bPrefilterVertices = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L21 _public member_ `int PrefilterGridResolution = 10;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### class `UE::GeometryFlow::FGenerateConvexHullMeshNode`  
`class FGenerateConvexHullMeshNode : public TProcessMeshWithSettingsBaseNode<FGenerateConvexHullMeshSettings>`  
_L37-59_
- inherits: `TProcessMeshWithSettingsBaseNode<FGenerateConvexHullMeshSettings>`
- L39 _private member_ `static constexpr int Version = 1;`
- L44 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FGenerateConvexHullMeshSettings& SettingsIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L54 _public prototype_ `EGeometryFlowResult MakeConvexHullMesh(const FDynamicMesh3& MeshIn, const FGenerateConvexHullMeshSettings& Settings, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSING_API`
- L24 _namespace_ `namespace UE`
- L26 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L32 _typedef_ `typedef FGenerateConvexHullMeshSettings FGenerateConvexHullMeshSettings;` (scope `UE::GeometryFlow`) — bring settings into the namespace.  @todo - fix code the expects the UE::GeometryFlow:: for this struct and delete this

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshDeleteTrianglesNode.h` (Public)


#### class `UE::GeometryFlow::FMeshDeleteTrianglesNode`  
`class FMeshDeleteTrianglesNode : public FProcessMeshBaseNode`  
_L16-70_
- inherits: `FProcessMeshBaseNode`
- L18 _private member_ `static constexpr int Version = 1;`
- L22 _public function_ `static const FString InParamTriangleLists()`
- L26 _public function_ `FMeshDeleteTrianglesNode()`
- L34 _public function_ `virtual void CheckAdditionalInputs(const FNamedDataMap& DatasIn, bool& bRecomputeRequired, bool& bAllInputsValid) override`
- L40 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L50 _public function_ `virtual void ProcessMeshInPlace( const FNamedDataMap& DatasIn, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L59 _public function_ `void DeleteTrianglesForMesh(const FNamedDataMap& DatasIn, FDynamicMesh3& EditMesh)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshMakeCleanGeometryNode.h` (Public)


#### struct `FMeshMakeCleanGeometrySettings`  
`struct FMeshMakeCleanGeometrySettings`  
_L12-46_
- reflection: `USTRUCT()`
- L15 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::MakeCleanGeometrySettings);`
- L18 _public member_ `int FillHolesEdgeCountThresh = 8;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L21 _public member_ `double FillHolesEstimatedAreaFraction = 0.001;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L24 _public member_ `bool bDiscardAllAttributes = false;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L27 _public member_ `bool bClearUVs = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L30 _public member_ `bool bClearNormals = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L33 _public member_ `bool bClearTangents = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L36 _public member_ `bool bClearVertexColors = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L39 _public member_ `bool bClearMaterialIDs = false;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L42 _public member_ `bool bOutputMeshVertexNormals = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L45 _public member_ `bool bOutputOverlayVertexNormals = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### class `UE::GeometryFlow::FMeshMakeCleanGeometryNode`  
`class FMeshMakeCleanGeometryNode : public TProcessMeshWithSettingsBaseNode<FMeshMakeCleanGeometrySettings>`  
_L62-86_
- inherits: `TProcessMeshWithSettingsBaseNode<FMeshMakeCleanGeometrySettings>`
- L64 _private member_ `static constexpr int Version = 1;`
- L69 _public prototype_ `void ProcessMesh( const FNamedDataMap& DatasIn, const FMeshMakeCleanGeometrySettings& SettingsIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override;`
- L76 _public prototype_ `void ProcessMeshInPlace( const FNamedDataMap& DatasIn, const FMeshMakeCleanGeometrySettings& Settings, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override;`
- L84 _protected prototype_ `void ApplyMakeCleanGeometry(FDynamicMesh3& MeshInOut, const FMeshMakeCleanGeometrySettings& Settings);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSING_API`
- L48 _namespace_ `namespace UE`
- L50 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L55 _typedef_ `typedef FMeshMakeCleanGeometrySettings FMeshMakeCleanGeometrySettings;` (scope `UE::GeometryFlow`) — bringing this into the namespace so other code that relies on UE::GeometryFlow::FMeshMakeCleanGeometrySettings will just work @todo, update client code and remove this type def

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshNormalFlowNode.h` (Public)


#### enum `EGeometryFlow_SmoothTypes`  
`enum class EGeometryFlow_SmoothTypes`  
_L14-19_
- reflection: `UENUM()`
- L16 _public enumerator_ `Uniform = 0`
- L17 _public enumerator_ `Cotan = 1` — Uniform = 0,	  Uniform weights, produces regular mesh and fastest convergence
- L18 _public enumerator_ `MeanValue = 2` — Cotan = 1,		  Cotangent weights prevent tangential flow and hence preserve triangle shape / texture coordinates, but can become unstable...

#### struct `FMeshNormalFlowSettings`  
`struct FMeshNormalFlowSettings : public FMeshSimplifySettings`  
_L33-58_
- reflection: `USTRUCT()`
- inherits: `FMeshSimplifySettings`
- L36 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::NormalFlowSettings);`
- L39 _public member_ `int MaxRemeshIterations = 20;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L42 _public member_ `int NumExtraProjectionIterations = 5;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L45 _public member_ `bool bFlips = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L48 _public member_ `bool bSplits = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L51 _public member_ `bool bCollapses = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L54 _public member_ `EGeometryFlow_SmoothTypes SmoothingType = UE::GeometryFlow::ToUEnum(UE::Geometry::FRemesher::ESmoothTypes::Uniform);` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L57 _public member_ `float SmoothingStrength = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### class `UE::GeometryFlow::FMeshNormalFlowNode`  
`class FMeshNormalFlowNode : public TProcessMeshWithSettingsBaseNode<FMeshNormalFlowSettings>`  
_L70-110_
- inherits: `TProcessMeshWithSettingsBaseNode<FMeshNormalFlowSettings>`
- L72 _private member_ `static constexpr int Version = 1;`
- L78 _public function_ `static const FString InParamTargetMesh()` — Beside the intput mesh and settings, we also take a "target mesh" that will be the projection target.
- L80 _public function_ `FMeshNormalFlowNode() : TProcessMeshWithSettingsBaseNode<FMeshNormalFlowSettings>()`
- L85 _public prototype_ `void ProcessMesh( const FNamedDataMap& DatasIn, const FMeshNormalFlowSettings& SettingsIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override;`
- L92 _public prototype_ `void ProcessMeshInPlace( const FNamedDataMap& DatasIn, const FMeshNormalFlowSettings& SettingsIn, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override;`
- L98 _public prototype_ `void CheckAdditionalInputs(const FNamedDataMap& DatasIn, bool& bRecomputeRequired, bool& bAllInputsValid) override;`
- L105 _protected prototype_ `void DoNormalFlow(const FMeshNormalFlowSettings& SettingsIn, const FDynamicMesh3& ProjectionTargetMesh, bool bAttributesHaveBeenDiscarded, FDynamicMesh3& EditMesh);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSING_API`
- L23 _namespace_ `namespace UE`
- L25 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L27 _function_ `static UE::Geometry::FRemesher::ESmoothTypes FromUEnum(const EGeometryFlow_SmoothTypes& SmoothType)` (scope `UE::GeometryFlow`)
- L28 _function_ `static EGeometryFlow_SmoothTypes ToUEnum(const UE::Geometry::FRemesher::ESmoothTypes& SmoothType)` (scope `UE::GeometryFlow`)
- L60 _namespace_ `namespace UE`
- L62 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshNormalsNodes.h` (Public)


#### enum `EGeometryFlow_ComputeNormalsType`  
`enum class EGeometryFlow_ComputeNormalsType`  
_L13-20_
- reflection: `UENUM()`
- L15 _public enumerator_ `PerTriangle = 0`
- L16 _public enumerator_ `PerVertex = 1`
- L17 _public enumerator_ `RecomputeExistingTopology = 2`
- L18 _public enumerator_ `FromFaceAngleThreshold = 3`
- L19 _public enumerator_ `FromGroups = 4`

#### struct `FMeshNormalsSettings`  
`struct FMeshNormalsSettings`  
_L23-42_
- reflection: `USTRUCT()`
- L26 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::NormalsSettings);`
- L29 _public member_ `EGeometryFlow_ComputeNormalsType NormalsType = EGeometryFlow_ComputeNormalsType::FromFaceAngleThreshold;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L32 _public member_ `bool bInvert = false;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L35 _public member_ `bool bAreaWeighted = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L38 _public member_ `bool bAngleWeighted = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L41 _public member_ `double AngleThresholdDeg = 180.0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### enum `UE::GeometryFlow::EComputeNormalsType`  
`enum class EComputeNormalsType`  
_L51-58_
- L53 _public enumerator_ `PerTriangle = 0`
- L54 _public enumerator_ `PerVertex = 1`
- L55 _public enumerator_ `RecomputeExistingTopology = 2`
- L56 _public enumerator_ `FromFaceAngleThreshold = 3`
- L57 _public enumerator_ `FromGroups = 4`

#### class `UE::GeometryFlow::FComputeMeshNormalsNode`  
`class FComputeMeshNormalsNode : public TProcessMeshWithSettingsBaseNode<FMeshNormalsSettings>`  
_L79-157_
- inherits: `TProcessMeshWithSettingsBaseNode<FMeshNormalsSettings>`
- desc: Recompute Normals overlay for input Mesh. Can apply in-place.
- L81 _private member_ `static constexpr int Version = 1;`
- L84 _public function_ `FComputeMeshNormalsNode() : TProcessMeshWithSettingsBaseNode<FMeshNormalsSettings>()`
- L91 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FMeshNormalsSettings& Settings, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L102 _public function_ `virtual void ProcessMeshInPlace( const FNamedDataMap& DatasIn, const FMeshNormalsSettings& Settings, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo)`
- L112 _public function_ `void ComputeNormals(const FMeshNormalsSettings& Settings, FDynamicMesh3& MeshInOut)`

#### class `UE::GeometryFlow::FComputeMeshPerVertexOverlayNormalsNode`  
`class FComputeMeshPerVertexOverlayNormalsNode : public FSimpleInPlaceProcessMeshBaseNode`  
_L164-183_
- inherits: `FSimpleInPlaceProcessMeshBaseNode`
- desc: Recompute per-vertex normals in Normals Overlay for input mesh. Can apply in-place.
- L166 _private member_ `static constexpr int Version = 1;`
- L169 _public function_ `virtual void ApplyNodeToMesh(FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`

#### class `UE::GeometryFlow::FComputeMeshPerVertexNormalsNode`  
`class FComputeMeshPerVertexNormalsNode : public FSimpleInPlaceProcessMeshBaseNode`  
_L190-199_
- inherits: `FSimpleInPlaceProcessMeshBaseNode`
- desc: Recompute per-vertex normals stored directly on the mesh. Can apply in-place.
- L192 _private member_ `static constexpr int Version = 1;`
- L195 _public function_ `virtual void ApplyNodeToMesh(FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace UE`
- L46 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L60 _function_ `static EComputeNormalsType FromUEnum(const EGeometryFlow_ComputeNormalsType& ComputeNormalsType)` (scope `UE::GeometryFlow`)
- L64 _function_ `static EGeometryFlow_ComputeNormalsType ToUEnum(const EComputeNormalsType& ComputeNormalsType)` (scope `UE::GeometryFlow`)
- L71 _typedef_ `typedef FMeshNormalsSettings FMeshNormalsSettings;` (scope `UE::GeometryFlow`) — bring settings into the namespace.  @todo - fix code the expects the UE::GeometryFlow:: for this struct and delete this

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshProcessingBaseNodes.h` (Public)


#### class `UE::GeometryFlow::FProcessMeshBaseNode`  
`class FProcessMeshBaseNode : public FNode`  
_L19-132_
- inherits: `FNode`
- L21 _private member_ `static constexpr int Version = 1;`
- L24 _public function_ `static const FString InParamMesh()`
- L25 _public function_ `static const FString OutParamResultMesh()`
- L28 _public function_ `FProcessMeshBaseNode()`
- L42 _protected function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo)`
- L51 _protected function_ `virtual void ProcessMeshInPlace( const FNamedDataMap& DatasIn, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo)`
- L60 _protected function_ `virtual void CheckAdditionalInputs(const FNamedDataMap& DatasIn, bool& bRecomputeRequired, bool& bAllInputsValid)`
- L67 _public function_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`

#### class `UE::GeometryFlow::FSimpleInPlaceProcessMeshBaseNode`  
`class FSimpleInPlaceProcessMeshBaseNode : public FProcessMeshBaseNode`  
_L144-169_
- inherits: `FProcessMeshBaseNode`
- desc: FSimpleInPlaceProcessMeshBaseNode provides a standard pattern for a simple "In-Place" mesh processing operation, eg something like recomputing normals where it would not make sense to cache the output and there are no configuration settings. The subclass only has to implement the ApplyNodeToMesh() function.
- L146 _private member_ `static constexpr int Version = 1;`
- L149 _public function_ `FSimpleInPlaceProcessMeshBaseNode()`
- L155 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L161 _public function_ `virtual void ProcessMeshInPlace( const FNamedDataMap& DatasIn, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L167 _public prototype_ `virtual void ApplyNodeToMesh(FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) = 0;` — subclasses only have to implement this

#### class `UE::GeometryFlow::TProcessMeshWithSettingsBaseNode`  
`template<typename SettingsType> class TProcessMeshWithSettingsBaseNode : public FNode`  
_L189-306_
- inherits: `FNode`
- L191 _private typedef_ `typedef FNode Super;`
- L193 _public typedef_ `using SettingsDataType = TMovableData<SettingsType, SettingsType::DataTypeIdentifier>;`
- L196 _public function_ `static const FString InParamMesh()`
- L197 _public function_ `static const FString InParamSettings()`
- L198 _public function_ `static const FString OutParamResultMesh()`
- L201 _protected function_ `TProcessMeshWithSettingsBaseNode()`
- L210 _protected function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const SettingsType& SettingsIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo)`
- L219 _protected function_ `virtual void ProcessMeshInPlace( const FNamedDataMap& DatasIn, const SettingsType& SettingsIn, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo)`
- L229 _protected function_ `virtual void CheckAdditionalInputs(const FNamedDataMap& DatasIn, bool& bRecomputeRequired, bool& bAllInputsValid)`
- L236 _public function_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L175 _namespace_ `namespace Private` (scope `UE::GeometryFlow`)
- L181 _function_ `inline void LogMeshProcessing(const TCHAR* Identifier, const TCHAR* Message)` (scope `UE::GeometryFlow::Private`) — This function is a workaround for an issue with Clang targeting Windows. A function in a class template cannot contain log statements if that class template is derived from by a type annotated with {Module}_API.

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshProcessingDataTypes.h` (Public)


#### enum `UE::GeometryFlow::EMeshProcessingDataTypes`  
`enum class EMeshProcessingDataTypes`  
_L12-53_
- L14 _public enumerator_ `DynamicMesh = (int)EDataTypes::BaseMeshProcessingTypes + 1`
- L15 _public enumerator_ `MeshNormalSet = (int)EDataTypes::BaseMeshProcessingTypes + 2`
- L16 _public enumerator_ `MeshTangentSet = (int)EDataTypes::BaseMeshProcessingTypes + 3`
- L18 _public enumerator_ `BakingCache = (int)EDataTypes::BaseMeshProcessingTypes + 10`
- L19 _public enumerator_ `TextureImage = (int)EDataTypes::BaseMeshProcessingTypes + 11`
- L20 _public enumerator_ `NormalMapImage = (int)EDataTypes::BaseMeshProcessingTypes + 12`
- L21 _public enumerator_ `CollisionGeometry = (int)EDataTypes::BaseMeshProcessingTypes + 13`
- L22 _public enumerator_ `IndexSets = (int)EDataTypes::BaseMeshProcessingTypes + 14`
- L23 _public enumerator_ `WeightMap = (int)EDataTypes::BaseMeshProcessingTypes + 15`
- L24 _public enumerator_ `MaterialIDToTextureMap = (int)EDataTypes::BaseMeshProcessingTypes + 16`
- L26 _public enumerator_ `SolidifySettings = (int)EDataTypes::BaseMeshProcessingTypes + 100`
- L27 _public enumerator_ `VoxMorphologyOpSettings = (int)EDataTypes::BaseMeshProcessingTypes + 101`
- L28 _public enumerator_ `ThickenSettings = (int)EDataTypes::BaseMeshProcessingTypes + 102`
- L29 _public enumerator_ `GenerateConvexHullMeshSettings = (int)EDataTypes::BaseMeshProcessingTypes + 103`
- L31 _public enumerator_ `SimplifySettings = (int)EDataTypes::BaseMeshProcessingTypes + 110`
- L32 _public enumerator_ `NormalFlowSettings = (int)EDataTypes::BaseMeshProcessingTypes + 111`
- L36 _public enumerator_ `NormalsSettings = (int)EDataTypes::BaseMeshProcessingTypes + 120`
- L37 _public enumerator_ `TangentsSettings = (int)EDataTypes::BaseMeshProcessingTypes + 121`
- L39 _public enumerator_ `MakeCleanGeometrySettings = (int)EDataTypes::BaseMeshProcessingTypes + 130`
- L41 _public enumerator_ `RecalculateUVsSettings = (int)EDataTypes::BaseMeshProcessingTypes + 150`
- L42 _public enumerator_ `RepackUVsSettings = (int)EDataTypes::BaseMeshProcessingTypes + 151`
- L45 _public enumerator_ `MakeBakingCacheSettings = (int)EDataTypes::BaseMeshProcessingTypes + 160`
- L46 _public enumerator_ `BakeNormalMapSettings = (int)EDataTypes::BaseMeshProcessingTypes + 161`
- L47 _public enumerator_ `BakeTextureImageSettings = (int)EDataTypes::BaseMeshProcessingTypes + 162`
- L48 _public enumerator_ `BakeMultiTextureSettings = (int)EDataTypes::BaseMeshProcessingTypes + 163`
- L51 _public enumerator_ `GenerateCollisionConvexHullsSettings = (int)EDataTypes::BaseMeshProcessingTypes + 200`
- L52 _public enumerator_ `GenerateSimpleCollisionSettings = (int)EDataTypes::BaseMeshProcessingTypes + 201`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshRecalculateUVsNode.h` (Public)


#### enum `EGeometryFlow_RecalculateUVsUnwrapType`  
`enum class EGeometryFlow_RecalculateUVsUnwrapType : uint8`  
_L12-17_
- reflection: `UENUM()`
- L14 _public enumerator_ `Auto = 0`
- L15 _public enumerator_ `ExpMap = 1`
- L16 _public enumerator_ `Conformal = 2`

#### struct `FMeshRecalculateUVsSettings`  
`struct FMeshRecalculateUVsSettings`  
_L20-30_
- reflection: `USTRUCT()`
- L23 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::RecalculateUVsSettings);`
- L26 _public member_ `EGeometryFlow_RecalculateUVsUnwrapType UnwrapType = EGeometryFlow_RecalculateUVsUnwrapType::Auto;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L29 _public member_ `int32 UVLayer = 0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### enum `UE::GeometryFlow::ERecalculateUVsUnwrapType`  
`enum class ERecalculateUVsUnwrapType : uint8`  
_L36-41_
- L38 _public enumerator_ `Auto = 0`
- L39 _public enumerator_ `ExpMap = 1`
- L40 _public enumerator_ `Conformal = 2`

#### class `UE::GeometryFlow::FMeshRecalculateUVsNode`  
`class FMeshRecalculateUVsNode : public TProcessMeshWithSettingsBaseNode<FMeshRecalculateUVsSettings>`  
_L61-93_
- inherits: `TProcessMeshWithSettingsBaseNode<FMeshRecalculateUVsSettings>`
- L63 _private member_ `static constexpr int Version = 1;`
- L66 _public function_ `FMeshRecalculateUVsNode() : TProcessMeshWithSettingsBaseNode<FMeshRecalculateUVsSettings>()`
- L72 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FMeshRecalculateUVsSettings& Settings, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L83 _public function_ `virtual void ProcessMeshInPlace( const FNamedDataMap& DatasIn, const FMeshRecalculateUVsSettings& Settings, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo)`
- L92 _public prototype_ `void RecalculateUVsOnMesh(FDynamicMesh3& EditMesh, const FMeshRecalculateUVsSettings& Settings);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSING_API`
- L31 _namespace_ `namespace UE`
- L33 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L43 _function_ `static ERecalculateUVsUnwrapType FromUEnum(const EGeometryFlow_RecalculateUVsUnwrapType& UVsUnwrapType)` (scope `UE::GeometryFlow`)
- L47 _function_ `static EGeometryFlow_RecalculateUVsUnwrapType ToUEnum(const ERecalculateUVsUnwrapType& UVsUnwrapType)` (scope `UE::GeometryFlow`)
- L55 _typedef_ `typedef FMeshRecalculateUVsSettings FMeshRecalculateUVsSettings;` (scope `UE::GeometryFlow`) — bringing this into the namespace so other code that relies on UE::GeometryFlow::FMeshRecalculateUVsSettings will just work @todo, update client code and remove this type def

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshRepackUVsNode.h` (Public)


#### struct `FMeshRepackUVsSettings`  
`struct FMeshRepackUVsSettings`  
_L12-34_
- reflection: `USTRUCT()`
- L15 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::RepackUVsSettings);`
- L18 _public member_ `int32 UVLayer = 0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L21 _public member_ `int32 TextureResolution = 512;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L24 _public member_ `int32 GutterSize = 1;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L27 _public member_ `bool bAllowFlips = false;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L30 _public member_ `FVector2f UVScale = FVector2f::One();` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L33 _public member_ `FVector2f UVTranslation = FVector2f::Zero();` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### class `UE::GeometryFlow::FMeshRepackUVsNode`  
`class FMeshRepackUVsNode : public TProcessMeshWithSettingsBaseNode<FMeshRepackUVsSettings>`  
_L44-76_
- inherits: `TProcessMeshWithSettingsBaseNode<FMeshRepackUVsSettings>`
- L46 _private member_ `static constexpr int Version = 1;`
- L49 _public function_ `FMeshRepackUVsNode() : TProcessMeshWithSettingsBaseNode<FMeshRepackUVsSettings>()`
- L55 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FMeshRepackUVsSettings& Settings, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L66 _public function_ `virtual void ProcessMeshInPlace( const FNamedDataMap& DatasIn, const FMeshRepackUVsSettings& Settings, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo)`
- L75 _public prototype_ `void RepackUVsForMesh(FDynamicMesh3& EditMesh, const FMeshRepackUVsSettings& Settings);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSING_API`
- L36 _namespace_ `namespace UE`
- L38 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshSimplifyNode.h` (Public)


#### enum `EGeometryFlow_MeshSimplifyType`  
`enum class EGeometryFlow_MeshSimplifyType`  
_L19-24_
- reflection: `UENUM()`
- L21 _public enumerator_ `Standard = 0`
- L22 _public enumerator_ `VolumePreserving = 1`
- L23 _public enumerator_ `AttributeAware = 2`

#### enum `EGeomtryFlow_MeshSimplifyTargetType`  
`enum class EGeomtryFlow_MeshSimplifyTargetType`  
_L27-33_
- reflection: `UENUM()`
- L29 _public enumerator_ `TriangleCount = 0`
- L30 _public enumerator_ `VertexCount = 1`
- L31 _public enumerator_ `TrianglePercentage = 2`
- L32 _public enumerator_ `GeometricDeviation = 3`

#### enum `EGeometryFlow_EdgeRefineFlags`  
`enum class EGeometryFlow_EdgeRefineFlags`  
_L36-54_
- reflection: `UENUM()`
- L39 _public enumerator_ `NoConstraint = 0` — Edge is unconstrained
- L41 _public enumerator_ `NoFlip = 1` — Edge cannot be flipped
- L43 _public enumerator_ `NoSplit = 2` — Edge cannot be split
- L45 _public enumerator_ `NoCollapse = 4` — Edge cannot be collapsed
- L47 _public enumerator_ `FullyConstrained = NoFlip | NoSplit | NoCollapse` — Edge cannot be flipped, split, or collapsed
- L49 _public enumerator_ `SplitsOnly = NoFlip | NoCollapse` — Edge can only be split
- L51 _public enumerator_ `FlipOnly = NoSplit | NoCollapse` — Edge can only flip
- L53 _public enumerator_ `CollapseOnly = NoFlip | NoSplit` — Edge can only collapse

#### struct `FMeshSimplifySettings`  
`struct FMeshSimplifySettings`  
_L65-109_
- reflection: `USTRUCT()`
- L69 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::SimplifySettings);`
- L72 _public member_ `EGeometryFlow_MeshSimplifyType SimplifyType = EGeometryFlow_MeshSimplifyType::AttributeAware;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L75 _public member_ `EGeomtryFlow_MeshSimplifyTargetType TargetType = EGeomtryFlow_MeshSimplifyTargetType::TrianglePercentage;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L78 _public member_ `int TargetCount = 100;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L81 _public member_ `float TargetFraction = 0.5;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L84 _public member_ `float GeometricTolerance = 0.5;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L87 _public member_ `bool bDiscardAttributes = false;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L90 _public member_ `bool bPreventNormalFlips = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L93 _public member_ `bool bPreserveSharpEdges = false;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L96 _public member_ `bool bAllowSeamCollapse = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L99 _public member_ `bool bAllowSeamSplits = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L102 _public member_ `EGeometryFlow_EdgeRefineFlags MeshBoundaryConstraints = EGeometryFlow_EdgeRefineFlags::NoConstraint;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L105 _public member_ `EGeometryFlow_EdgeRefineFlags GroupBorderConstraints = EGeometryFlow_EdgeRefineFlags::NoConstraint;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L108 _public member_ `EGeometryFlow_EdgeRefineFlags MaterialBorderConstraints = EGeometryFlow_EdgeRefineFlags::NoConstraint;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### enum `UE::GeometryFlow::EMeshSimplifyType`  
`enum class EMeshSimplifyType`  
_L126-131_
- L128 _public enumerator_ `Standard = 0`
- L129 _public enumerator_ `VolumePreserving = 1`
- L130 _public enumerator_ `AttributeAware = 2`

#### enum `UE::GeometryFlow::EMeshSimplifyTargetType`  
`enum class EMeshSimplifyTargetType`  
_L133-139_
- L135 _public enumerator_ `TriangleCount = 0`
- L136 _public enumerator_ `VertexCount = 1`
- L137 _public enumerator_ `TrianglePercentage = 2`
- L138 _public enumerator_ `GeometricDeviation = 3`

#### class `UE::GeometryFlow::FSimplifyMeshNode`  
`class FSimplifyMeshNode : public TProcessMeshWithSettingsBaseNode<FMeshSimplifySettings>`  
_L152-275_
- inherits: `TProcessMeshWithSettingsBaseNode<FMeshSimplifySettings>`
- L154 _private member_ `static constexpr int Version = 1;`
- L157 _public function_ `FSimplifyMeshNode() : TProcessMeshWithSettingsBaseNode<FMeshSimplifySettings>()`
- L163 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FMeshSimplifySettings& Settings, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L174 _public function_ `virtual void ProcessMeshInPlace( const FNamedDataMap& DatasIn, const FMeshSimplifySettings& Settings, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo)`
- L185 _public function_ `template<typename SimplifierType> void DoSimplifyOfType(const FMeshSimplifySettings& Settings, FDynamicMesh3* TargetMesh, TUniquePtr<FEvaluationInfo>& EvaluationInfo)`
- L250 _public function_ `void ApplySimplify(const FMeshSimplifySettings& Settings, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo)`

#### Free symbols / members of external scopes

- L56 _namespace_ `namespace UE`
- L57 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L58 _function_ `static EEdgeRefineFlags ToEdgeRefineFlags2(const EGeometryFlow_EdgeRefineFlags& Flag)` (scope `UE::GeometryFlow`)
- L111 _namespace_ `namespace UE`
- L111 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L115 _namespace_ `namespace UE`
- L117 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L124 _typedef_ `typedef FMeshSimplifySettings FMeshSimplifySettings;` (scope `UE::GeometryFlow`) — bringing this into the namespace so other code that relies on UE::GeometryFlow::FMeshSimplifySettings will just work @todo, update client code and remove this type def
- L143 _function_ `static EEdgeRefineFlags FromUEnum(const EGeometryFlow_EdgeRefineFlags& Flag)` (scope `UE::GeometryFlow`)
- L144 _function_ `static EGeometryFlow_EdgeRefineFlags ToUEnum(const EEdgeRefineFlags& Flag)` (scope `UE::GeometryFlow`)
- L146 _function_ `static EMeshSimplifyType FromUEnum(const EGeometryFlow_MeshSimplifyType& SimplifyType)` (scope `UE::GeometryFlow`)
- L147 _function_ `static EGeometryFlow_MeshSimplifyType ToUEnum(const EMeshSimplifyType& SimplifyType)` (scope `UE::GeometryFlow`)
- L149 _function_ `static EMeshSimplifyTargetType FromUEnum(const EGeomtryFlow_MeshSimplifyTargetType& TargetType)` (scope `UE::GeometryFlow`)
- L150 _function_ `static EGeomtryFlow_MeshSimplifyTargetType ToUEnum(const EMeshSimplifyTargetType& TargetType)` (scope `UE::GeometryFlow`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshSolidifyNode.h` (Public)


#### struct `FMeshSolidifySettings`  
`struct FMeshSolidifySettings`  
_L15-32_
- reflection: `USTRUCT()`
- L19 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::SolidifySettings);`
- L22 _public member_ `int VoxelResolution = 64;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L25 _public member_ `float WindingThreshold = 0.5;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L28 _public member_ `int SurfaceConvergeSteps = 5;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L31 _public member_ `float ExtendBounds = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### class `UE::GeometryFlow::FSolidifyMeshNode`  
`class FSolidifyMeshNode : public TProcessMeshWithSettingsBaseNode<FMeshSolidifySettings>`  
_L51-84_
- inherits: `TProcessMeshWithSettingsBaseNode<FMeshSolidifySettings>`
- L53 _private member_ `static constexpr int Version = 1;`
- L57 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FMeshSolidifySettings& SettingsIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L67 _public function_ `void ApplySolidify(const FDynamicMesh3& MeshIn, const FMeshSolidifySettings& Settings, FDynamicMesh3& MeshOut)`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace UE`
- L38 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L46 _typedef_ `typedef FMeshSolidifySettings FMeshSolidifySettings;` (scope `UE::GeometryFlow`) — bringing this into the namespace so other code that relies on UE::GeometryFlow::FMeshSolidifySettings will just work @todo, update client code and remove this type def

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshTangentsNodes.h` (Public)


#### enum `EGeometryFlow_ComputeTangentsType`  
`enum class EGeometryFlow_ComputeTangentsType`  
_L19-23_
- reflection: `UENUM()`
- L21 _public enumerator_ `PerTriangle = 0`
- L22 _public enumerator_ `FastMikkT = 1`

#### struct `FMeshTangentsSettings`  
`struct FMeshTangentsSettings`  
_L26-36_
- reflection: `USTRUCT()`
- L29 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::TangentsSettings);`
- L32 _public member_ `EGeometryFlow_ComputeTangentsType TangentsType = EGeometryFlow_ComputeTangentsType::FastMikkT;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L35 _public member_ `int UVLayer = 0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### enum `UE::GeometryFlow::EComputeTangentsType`  
`enum class EComputeTangentsType`  
_L45-49_
- L47 _public enumerator_ `PerTriangle = 0`
- L48 _public enumerator_ `FastMikkT = 1`

#### class `UE::GeometryFlow::FMeshTangentsTransferNode`  
`class FMeshTangentsTransferNode : public TTransferNode<FMeshTangentsd, (int)EMeshProcessingDataTypes::MeshTangentSet>`  
_L62-62_
- inherits: `TTransferNode<FMeshTangentsd,(int)EMeshProcessingDataTypes::MeshTangentSet>`
- L62 _private member_ `class FMeshTangentsTransferNode : public TTransferNode<FMeshTangentsd, (int)EMeshProcessingDataTypes::MeshTangentSet> {static constexpr int Version =1; GEOMETRYFLOW_NODE_INTERNAL(FMeshTangentsTransferNode, Version, FNode) };`

#### class `UE::GeometryFlow::FComputeMeshTangentsNode`  
`class FComputeMeshTangentsNode : public TTransformerWithSettingsNode< FDynamicMesh3, (int)EMeshProcessingDataTypes::DynamicMesh, FMeshTangentsSettings, (int)EMeshProcessingDataTypes::TangentsSettings, FMeshTangentsd, (int)EMeshProcessingDataTypes::MeshTangentSet>`  
_L65-107_
- inherits: `TTransformerWithSettingsNode<FDynamicMesh3,(int)EMeshProcessingDataTypes::DynamicMesh,FMeshTangentsSettings,(int)EMeshProcessingDataTypes::TangentsSettings,FMeshTangentsd,(int)EMeshProcessingDataTypes::MeshTangentSet>`
- L70 _private member_ `static constexpr int Version = 1;`
- L73 _public function_ `FComputeMeshTangentsNode() : TTransformerWithSettingsNode()`
- L77 _public function_ `virtual void ComputeOutput( const FNamedDataMap& DatasIn, const FMeshTangentsSettings& Settings, const FDynamicMesh3& MeshIn, FMeshTangentsd& TangentsOut)`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L38 _namespace_ `namespace UE`
- L40 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L51 _function_ `static EComputeTangentsType FromUEnum(const EGeometryFlow_ComputeTangentsType& type)` (scope `UE::GeometryFlow`)
- L52 _function_ `static EGeometryFlow_ComputeTangentsType ToUEnum(const EComputeTangentsType& type)` (scope `UE::GeometryFlow`)
- L56 _typedef_ `typedef FMeshTangentsSettings FMeshTangentsSettings;` (scope `UE::GeometryFlow`) — bringing this into the namespace so other code that relies on UE::GeometryFlow:: will work @todo, update client code and remove this type def

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshThickenNode.h` (Public)


#### struct `FMeshThickenSettings`  
`struct FMeshThickenSettings`  
_L13-19_
- reflection: `USTRUCT()`
- L16 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::ThickenSettings);`
- L18 _public member_ `float ThickenAmount = 1.0f;`

#### class `UE::GeometryFlow::FMeshThickenNode`  
`class FMeshThickenNode : public TProcessMeshWithSettingsBaseNode<FMeshThickenSettings>`  
_L32-69_
- inherits: `TProcessMeshWithSettingsBaseNode<FMeshThickenSettings>`
- L34 _private member_ `static constexpr int Version = 1;`
- L38 _public function_ `static const FString InParamWeightMap()`
- L40 _public function_ `FMeshThickenNode()`
- L45 _public function_ `void CheckAdditionalInputs(const FNamedDataMap& DatasIn, bool& bRecomputeRequired, bool& bAllInputsValid) override`
- L52 _public prototype_ `void ProcessMesh( const FNamedDataMap& DatasIn, const FMeshThickenSettings& SettingsIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override;`
- L59 _public prototype_ `void ProcessMeshInPlace( const FNamedDataMap& DatasIn, const FMeshThickenSettings& Settings, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override;`
- L67 _protected prototype_ `void ApplyThicken(FDynamicMesh3& MeshInOut, const FMeshThickenSettings& Settings, const TArray<float>& VertexWeights);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSING_API`
- L21 _namespace_ `namespace UE`
- L23 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L27 _typedef_ `typedef FMeshThickenSettings FMeshThickenSettings;` (scope `UE::GeometryFlow`) — @todo - remove this when other code is no longer expecting FMeshThickenSettings to be in the UE::GeometryFlow namespace

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/MeshVoxMorphologyNode.h` (Public)


#### struct `FVoxMorphologyOpSettings`  
`struct FVoxMorphologyOpSettings`  
_L14-25_
- reflection: `USTRUCT()`
- L18 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::VoxMorphologyOpSettings);`
- L21 _public member_ `int VoxelResolution = 64;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L24 _public member_ `double Distance = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### struct `UE::GeometryFlow::TSerializationMethod`  
`template<> struct TSerializationMethod<FVoxMorphologyOpSettings>`  
_L35-35_
- L35 _public function_ `template<> struct TSerializationMethod<FVoxMorphologyOpSettings>`

#### class `UE::GeometryFlow::TVoxMorphologyMeshNode`  
`template<TImplicitMorphology<FDynamicMesh3>::EMorphologyOp MorphologyOp> class TVoxMorphologyMeshNode : public TProcessMeshWithSettingsBaseNode<FVoxMorphologyOpSettings>`  
_L56-98_
- inherits: `TProcessMeshWithSettingsBaseNode<FVoxMorphologyOpSettings>`
- L61 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FVoxMorphologyOpSettings& SettingsIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L71 _public function_ `void ApplyMorphology(const FDynamicMesh3& MeshIn, const FVoxMorphologyOpSettings& Settings, FDynamicMesh3& MeshOut)`

#### class `UE::GeometryFlow::FVoxDilateMeshNode`  
`class FVoxDilateMeshNode : public TVoxMorphologyMeshNode<TImplicitMorphology<FDynamicMesh3>::EMorphologyOp::Dilate>`  
_L100-100_
- inherits: `TVoxMorphologyMeshNode<TImplicitMorphology<FDynamicMesh3>::EMorphologyOp::Dilate>`
- L100 _private member_ `class FVoxDilateMeshNode : public TVoxMorphologyMeshNode<TImplicitMorphology<FDynamicMesh3>::EMorphologyOp::Dilate> { static constexpr int Version = 1; GEOMETRYFLOW_NODE_INTERNAL(FVoxDilateMeshNode, Version, FNode) };`

#### class `UE::GeometryFlow::FVoxClosureMeshNode`  
`class FVoxClosureMeshNode: public TVoxMorphologyMeshNode<TImplicitMorphology<FDynamicMesh3>::EMorphologyOp::Close>`  
_L101-101_
- inherits: `TVoxMorphologyMeshNode<TImplicitMorphology<FDynamicMesh3>::EMorphologyOp::Close>`
- L101 _private member_ `class FVoxClosureMeshNode: public TVoxMorphologyMeshNode<TImplicitMorphology<FDynamicMesh3>::EMorphologyOp::Close> { static constexpr int Version = 1; GEOMETRYFLOW_NODE_INTERNAL(FVoxClosureMeshNode, Version, FNode) };`

#### class `UE::GeometryFlow::FVoxOpeningMeshNode`  
`class FVoxOpeningMeshNode: public TVoxMorphologyMeshNode<TImplicitMorphology<FDynamicMesh3>::EMorphologyOp::Open>`  
_L102-102_
- inherits: `TVoxMorphologyMeshNode<TImplicitMorphology<FDynamicMesh3>::EMorphologyOp::Open>`
- L102 _private member_ `class FVoxOpeningMeshNode: public TVoxMorphologyMeshNode<TImplicitMorphology<FDynamicMesh3>::EMorphologyOp::Open> { static constexpr int Version = 1; GEOMETRYFLOW_NODE_INTERNAL(FVoxOpeningMeshNode, Version, FNode) };`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L29 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L38 _typedef_ `typedef FVoxMorphologyOpSettings FVoxOffsetSettings;` (scope `UE::GeometryFlow`)
- L39 _typedef_ `typedef FVoxMorphologyOpSettings FVoxClosureSettings;` (scope `UE::GeometryFlow`)
- L40 _typedef_ `typedef FVoxMorphologyOpSettings FVoxOpeningSettings;` (scope `UE::GeometryFlow`)
- L43 _macro_ `#define GEOMETRYFLOW_DECLARE_MORPHOLOGY_SETTINGS_TYPES(CppType, ReadableName) \`
- L48 _prototype_ `GEOMETRYFLOW_DECLARE_MORPHOLOGY_SETTINGS_TYPES(FVoxOffsetSettings, VoxOffset);` (scope `UE::GeometryFlow`)
- L49 _prototype_ `GEOMETRYFLOW_DECLARE_MORPHOLOGY_SETTINGS_TYPES(FVoxClosureSettings, VoxClosure);` (scope `UE::GeometryFlow`)
- L50 _prototype_ `GEOMETRYFLOW_DECLARE_MORPHOLOGY_SETTINGS_TYPES(FVoxOpeningSettings, VoxOpening);` (scope `UE::GeometryFlow`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/MeshProcessingNodes/TransferMeshMaterialIDsNode.h` (Public)


#### class `UE::GeometryFlow::FTransferMeshMaterialIDsNode`  
`class FTransferMeshMaterialIDsNode : public FProcessMeshBaseNode`  
_L17-77_
- inherits: `FProcessMeshBaseNode`
- desc: FTransferMeshMaterialIDsNode transfers Material IDs from a SourceMesh to the Input mesh and returns in the Output mesh (can be applied in-place)
- L19 _private member_ `static constexpr int Version = 1;`
- L22 _public function_ `static const FString InParamMaterialSourceMesh()`
- L25 _public function_ `FTransferMeshMaterialIDsNode()`
- L33 _public function_ `virtual void CheckAdditionalInputs(const FNamedDataMap& DatasIn, bool& bRecomputeRequired, bool& bAllInputsValid) override`
- L39 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L49 _public function_ `virtual void ProcessMeshInPlace( const FNamedDataMap& DatasIn, FDynamicMesh3& MeshInOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L58 _public function_ `virtual void TransferMaterialIDs(const FNamedDataMap& DatasIn, FDynamicMesh3* TargetMesh)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessing/Public/PhysicsNodes/GenerateSimpleCollisionNode.h` (Public)


#### enum `EGeometryFlow_SimpleCollisionGeometryType`  
`enum class EGeometryFlow_SimpleCollisionGeometryType : uint8`  
_L18-30_
- reflection: `UENUM()`
- L22 _public enumerator_ `AlignedBoxes`
- L23 _public enumerator_ `OrientedBoxes`
- L24 _public enumerator_ `MinimalSpheres`
- L25 _public enumerator_ `Capsules`
- L26 _public enumerator_ `ConvexHulls`
- L27 _public enumerator_ `SweptHulls`
- L28 _public enumerator_ `MinVolume`
- L29 _public enumerator_ `None`

#### enum `EGeometryFlow_ProjectedHullAxisMode`  
`enum class EGeometryFlow_ProjectedHullAxisMode`  
_L33-45_
- reflection: `UENUM()`
- L36 _public enumerator_ `X = 0` — Use Unit X axis
- L38 _public enumerator_ `Y = 1` — Use Unit Y axis
- L40 _public enumerator_ `Z = 2` — Use Unit Z axis
- L42 _public enumerator_ `SmallestBoxDimension = 3` — Use X/Y/Z axis with smallest axis-aligned-bounding-box dimension
- L44 _public enumerator_ `SmallestVolume = 4` — Compute projected hull for each of X/Y/Z axes and use the one that has the smallest volume

#### struct `FGenerateConvexHullSettings`  
`struct FGenerateConvexHullSettings`  
_L49-64_
- reflection: `USTRUCT()`
- L54 _public member_ `int32 SimplifyToTriangleCount = 50;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L57 _public member_ `double GeometricToleranceAfterTarget = 0.;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L60 _public member_ `bool bPrefilterVertices = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L63 _public member_ `int PrefilterGridResolution = 10;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### struct `FGenerateSweptHullSettings`  
`struct FGenerateSweptHullSettings`  
_L67-79_
- reflection: `USTRUCT()`
- L72 _public member_ `bool bSimplifyPolygons = true;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L75 _public member_ `EGeometryFlow_ProjectedHullAxisMode SweepAxis = EGeometryFlow_ProjectedHullAxisMode::SmallestVolume;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L78 _public member_ `float HullTolerance = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### struct `FGenerateSimpleCollisionSettings`  
`struct FGenerateSimpleCollisionSettings`  
_L82-94_
- reflection: `USTRUCT()`
- L85 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypes::GenerateSimpleCollisionSettings);`
- L87 _public member_ `EGeometryFlow_SimpleCollisionGeometryType Type = EGeometryFlow_SimpleCollisionGeometryType::ConvexHulls;`
- L90 _public member_ `FGenerateConvexHullSettings ConvexHullSettings;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L93 _public member_ `FGenerateSweptHullSettings SweptHullSettings;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### class `UE::GeometryFlow::FGenerateSimpleCollisionNode`  
`class FGenerateSimpleCollisionNode : public FNode`  
_L109-146_
- inherits: `FNode`
- L111 _private member_ `static constexpr int Version = 1;`
- L114 _protected typedef_ `using SettingsDataType = TMovableData<FGenerateSimpleCollisionSettings, FGenerateSimpleCollisionSettings::DataTypeIdentifier>;`
- L117 _public function_ `static const FString InParamMesh()`
- L118 _public function_ `static const FString InParamIndexSets()`
- L119 _public function_ `static const FString InParamSettings()`
- L120 _public function_ `static const FString OutParamGeometry()`
- L124 _public function_ `FGenerateSimpleCollisionNode()`
- L133 _public prototype_ `virtual void Evaluate( const FNamedDataMap& DatasIn, FNamedDataMap& DatasOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override;`
- L140 _protected prototype_ `EGeometryFlowResult EvaluateInternal(const FDynamicMesh3& Mesh, const FIndexSets& IndexData, const FGenerateSimpleCollisionSettings& Settings, TUniquePtr<FEvaluationInfo>& EvaluationInfo, FCollisionGeometry& OutCollisionGeometry);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSING_API`
- L96 _namespace_ `namespace UE`
- L98 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L103 _typedef_ `typedef FGenerateSimpleCollisionSettings FGenerateSimpleCollisionSettings;` (scope `UE::GeometryFlow`)
