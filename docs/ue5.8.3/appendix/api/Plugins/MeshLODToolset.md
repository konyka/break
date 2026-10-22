# Plugins / MeshLODToolset

- module root: `Plugins/Editor/MeshLODToolset/Source/MeshLODToolset`
- headers: 9; symbols: 504
- symbol kinds: class=22, delegate=1, enum=14, enumerator=55, function=52, macro=2, member=230, namespace=12, prototype=97, struct=19
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AssetDefinition, CoreUObject, EditorScriptingUtilities, Engine, RenderCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryCore, GeometryFlowCore, GeometryFlowMeshProcessing, GeometryFlowMeshProcessingEditor, InteractiveToolsFramework, MeshConversion, MeshConversionEngineTypes, MeshDescription, MeshModelingToolsExp, ModelingComponents, ModelingComponentsEditorOnly, StaticMeshDescription

### `Plugins/Editor/MeshLODToolset/Source/MeshLODToolset/Public/AssetDefinition_StaticMeshLODGenerationSettings.h` (Public)


#### class `UAssetDefinition_StaticMeshLODGenerationSettings`  
`class UAssetDefinition_StaticMeshLODGenerationSettings : public UAssetDefinitionDefault`  
_L13-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- desc: Asset Definition for UStaticMeshLODGenerationSettings Assets
- L18 _private function_ `virtual FText GetAssetDisplayName() const override`
- L19 _private function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _private function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _private function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _private function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const`

### `Plugins/Editor/MeshLODToolset/Source/MeshLODToolset/Public/Graphs/GenerateMeshLODGraph.h` (Public)


#### struct `FMeshLODGraphPreFilterSettings`  
`struct FMeshLODGraphPreFilterSettings`  
_L25-28_
- L27 _public member_ `FName FilterGroupLayerName = FName();`

#### class `FGenerateMeshLODGraph`  
`class FGenerateMeshLODGraph`  
_L30-195_
- L37 _public prototype_ `void BuildGraph(const FDynamicMesh3* SourceMeshHint = nullptr);` — Initialize the LOD generation graph. @param SourceMesh if the SourceMesh is known, some optimizations can be made in the graph, but this is optional
- L39 _public prototype_ `int32 AppendTextureBakeNode(const UE::Geometry::TImageBuilder<FVector4f>& SourceImage, const FString& Identifier);`
- L41 _public prototype_ `void AppendMultiTextureBakeNode(const TMap<int32, UE::GeometryFlow::TSafeSharedPtr<UE::Geometry::TImageBuilder<FVector4f>>>& SourceMaterialImages);`
- L43 _public prototype_ `void SetSourceMesh(const FDynamicMesh3& SourceMesh);`
- L46 _public prototype_ `void UpdatePreFilterSettings(const FMeshLODGraphPreFilterSettings& PreFilterSettings);`
- L47 _public function_ `const FMeshLODGraphPreFilterSettings& GetCurrentPreFilterSettings() const`
- L57 _public prototype_ `void UpdateCoreMeshGeneratorMode(ECoreMeshGeneratorMode NewMode);`
- L58 _public function_ `ECoreMeshGeneratorMode GetCurrentCoreMeshGeneratorMode() const`
- L60 _public prototype_ `void UpdateSolidifySettings(const FMeshSolidifySettings& SolidifySettings);`
- L61 _public function_ `const UE::GeometryFlow::FMeshSolidifySettings& GetCurrentSolidifySettings() const`
- L63 _public prototype_ `void UpdateMorphologySettings(const UE::GeometryFlow::FVoxClosureSettings& MorphologySettings);`
- L64 _public function_ `const UE::GeometryFlow::FVoxClosureSettings& GetCurrentMorphologySettings() const`
- L66 _public prototype_ `void UpdateMeshCleaningSettings(const UE::GeometryFlow::FMeshMakeCleanGeometrySettings& CleaningSettings);`
- L67 _public function_ `const UE::GeometryFlow::FMeshMakeCleanGeometrySettings& GetCurrentMeshCleaningSettings() const`
- L69 _public prototype_ `void UpdateSimplifySettings(const UE::GeometryFlow::FMeshSimplifySettings& SimplifySettings);`
- L70 _public function_ `const UE::GeometryFlow::FMeshSimplifySettings& GetCurrentSimplifySettings() const`
- L72 _public prototype_ `void UpdateGenerateConvexHullMeshSettings(const UE::GeometryFlow::FGenerateConvexHullMeshSettings& ConvexHullSettings);`
- L73 _public function_ `const UE::GeometryFlow::FGenerateConvexHullMeshSettings& GetCurrentGenerateConvexHullMeshSettings() const`
- L75 _public prototype_ `void UpdateNormalsSettings(const UE::GeometryFlow::FMeshNormalsSettings& NormalsSettings);`
- L76 _public function_ `const UE::GeometryFlow::FMeshNormalsSettings& GetCurrentNormalsSettings() const`
- L78 _public prototype_ `void UpdateAutoUVSettings(const UE::GeometryFlow::FMeshAutoGenerateUVsSettings& AutoUVSettings);`
- L79 _public function_ `const UE::GeometryFlow::FMeshAutoGenerateUVsSettings& GetCurrentAutoUVSettings() const`
- L81 _public prototype_ `void UpdateBakeCacheSettings(const UE::GeometryFlow::FMeshMakeBakingCacheSettings& BakeCacheSettings);`
- L82 _public function_ `const UE::GeometryFlow::FMeshMakeBakingCacheSettings& GetCurrentBakeCacheSettings() const`
- L84 _public prototype_ `void UpdateGenerateSimpleCollisionSettings(const UE::GeometryFlow::FGenerateSimpleCollisionSettings& SimpleCollisionSettings);`
- L85 _public function_ `const UE::GeometryFlow::FGenerateSimpleCollisionSettings& GetCurrentGenerateSimpleCollisionSettings() const`
- L87 _public prototype_ `void UpdateThickenWeightMap(const TArray<float>& ThickenWeightMap);`
- L89 _public prototype_ `void UpdateCollisionGroupLayerName(const FName& CollisionGroupLayerName);`
- L91 _public prototype_ `void UpdateThickenSettings(const UE::GeometryFlow::FMeshThickenSettings& ThickenSettings);`
- L92 _public function_ `const UE::GeometryFlow::FMeshThickenSettings& GetCurrentThickenSettings() const`
- L94 _public prototype_ `void EvaluateResult( FDynamicMesh3& ResultMesh, UE::Geometry::FMeshTangentsd& ResultTangents, UE::Geometry::FSimpleShapeSet3d& ResultCollision, UE::GeometryFlow::FNormalMapImage& NormalMap, TArray<TUniquePtr<UE::GeometryFlow::FTextureImage>>& TextureImages, UE::GeometryFlow::FTextureImage& MultiTextureImage, FProgressCancel* Progress);`
- L107 _protected member_ `TUniquePtr<UE::GeometryFlow::FGraph> Graph;`
- L110 _protected member_ `UE::GeometryFlow::FGraph::FHandle MeshSourceNode;`
- L112 _protected member_ `UE::GeometryFlow::FGraph::FHandle FilterGroupsLayerNameNode;` — FNameSourceNode that defines name of polygroups layer
- L113 _protected member_ `UE::GeometryFlow::FGraph::FHandle FilterTrianglesNode;`
- L114 _protected member_ `FMeshLODGraphPreFilterSettings CurrentPreFilterSettings;`
- L116 _protected member_ `UE::GeometryFlow::FGraph::FHandle MeshGeneratorSwitchNode;`
- L117 _protected member_ `ECoreMeshGeneratorMode CurrentCoreMeshGeneratorMode = ECoreMeshGeneratorMode::SolidifyAndClose;`
- L119 _protected member_ `UE::GeometryFlow::FGraph::FHandle SolidifyNode;`
- L120 _protected member_ `UE::GeometryFlow::FGraph::FHandle SolidifySettingsNode;`
- L121 _protected member_ `UE::GeometryFlow::FMeshSolidifySettings CurrentSolidifySettings;`
- L123 _protected member_ `UE::GeometryFlow::FGraph::FHandle MorphologyNode;`
- L124 _protected member_ `UE::GeometryFlow::FGraph::FHandle MorphologySettingsNode;`
- L125 _protected member_ `UE::GeometryFlow::FVoxClosureSettings CurrentMorphologySettings;`
- L127 _protected member_ `UE::GeometryFlow::FGraph::FHandle CleanMeshNode;`
- L128 _protected member_ `UE::GeometryFlow::FGraph::FHandle CleanMeshSettingsNode;`
- L129 _protected member_ `UE::GeometryFlow::FMeshMakeCleanGeometrySettings CurrentCleanMeshSettings;`
- L131 _protected member_ `UE::GeometryFlow::FGraph::FHandle SimplifyNode;`
- L132 _protected member_ `UE::GeometryFlow::FGraph::FHandle SimplifySettingsNode;`
- L133 _protected member_ `UE::GeometryFlow::FMeshSimplifySettings CurrentSimplifySettings;`
- L135 _protected member_ `UE::GeometryFlow::FGraph::FHandle GenerateConvexHullMeshNode;`
- L136 _protected member_ `UE::GeometryFlow::FGraph::FHandle GenerateConvexHullMeshSettingsNode;`
- L137 _protected member_ `UE::GeometryFlow::FGenerateConvexHullMeshSettings CurrentGenerateConvexHullMeshSettings;`
- L139 _protected member_ `UE::GeometryFlow::FGraph::FHandle NormalsNode;`
- L140 _protected member_ `UE::GeometryFlow::FGraph::FHandle NormalsSettingsNode;`
- L141 _protected member_ `UE::GeometryFlow::FMeshNormalsSettings CurrentNormalsSettings;`
- L143 _protected member_ `UE::GeometryFlow::FGraph::FHandle AutoUVNode;`
- L144 _protected member_ `UE::GeometryFlow::FGraph::FHandle AutoUVSettingsNode;`
- L145 _protected member_ `UE::GeometryFlow::FMeshAutoGenerateUVsSettings CurrentAutoUVSettings;`
- L150 _protected member_ `UE::GeometryFlow::FGraph::FHandle RepackUVNode;`
- L151 _protected member_ `UE::GeometryFlow::FGraph::FHandle RepackUVSettingsNode;`
- L153 _protected member_ `UE::GeometryFlow::FGraph::FHandle TangentsNode;`
- L154 _protected member_ `UE::GeometryFlow::FGraph::FHandle TangentsSettingsNode;`
- L156 _protected member_ `UE::GeometryFlow::FGraph::FHandle BakeCacheNode;`
- L157 _protected member_ `UE::GeometryFlow::FGraph::FHandle BakeCacheSettingsNode;`
- L158 _protected member_ `UE::GeometryFlow::FMeshMakeBakingCacheSettings CurrentBakeCacheSettings;`
- L160 _protected member_ `UE::GeometryFlow::FGraph::FHandle BakeNormalMapNode;`
- L161 _protected member_ `UE::GeometryFlow::FGraph::FHandle BakeNormalMapSettingsNode;`
- L163 _protected member_ `UE::GeometryFlow::FGraph::FHandle BakeMultiTextureNode;`
- L164 _protected member_ `UE::GeometryFlow::FGraph::FHandle BakeMultiTextureSettingsNode;`
- L165 _protected member_ `UE::GeometryFlow::FGraph::FHandle MaterialIDTextureSourceNode;`
- L167 _protected member_ `UE::GeometryFlow::FGraph::FHandle ThickenNode;`
- L168 _protected member_ `UE::GeometryFlow::FGraph::FHandle ThickenSettingsNode;`
- L169 _protected member_ `UE::GeometryFlow::FGraph::FHandle ThickenWeightMapNode;`
- L170 _protected member_ `UE::GeometryFlow::FMeshThickenSettings CurrentThickenSettings;`
- L172 _protected member_ `UE::GeometryFlow::FGraph::FHandle GroupLayerNameNode;`
- L181 _protected member_ `TArray<FBakeTextureGraphInfo> BakeTextureNodes;`
- L183 _protected member_ `UE::GeometryFlow::FGraph::FHandle DecomposeMeshForCollisionNode;`
- L185 _protected member_ `UE::GeometryFlow::FGraph::FHandle GenerateSimpleCollisionNode;`
- L186 _protected member_ `UE::GeometryFlow::FGraph::FHandle GenerateSimpleCollisionSettingsNode;`
- L187 _protected member_ `UE::GeometryFlow::FGenerateSimpleCollisionSettings CurrentGenerateSimpleCollisionSettings;`
- L189 _protected member_ `UE::GeometryFlow::FGraph::FHandle CollisionOutputNode;`
- L190 _protected member_ `UE::GeometryFlow::FGraph::FHandle MeshOutputNode;`
- L191 _protected member_ `UE::GeometryFlow::FGraph::FHandle TangentsOutputNode;`
- L193 _protected member_ `FName CollisionGroupLayerName = TEXT("Def`

#### enum `FGenerateMeshLODGraph::ECoreMeshGeneratorMode`  
`enum class ECoreMeshGeneratorMode`  
_L50-56_
- L52 _public enumerator_ `Solidify = 0`
- L53 _public enumerator_ `SolidifyAndClose = 1`
- L54 _public enumerator_ `SimplifyOnly = 2`
- L55 _public enumerator_ `ConvexHull = 3`

#### struct `FGenerateMeshLODGraph::FBakeTextureGraphInfo`  
`struct FBakeTextureGraphInfo`  
_L174-180_
- L176 _public member_ `int32 Index;`
- L177 _public member_ `FString Identifier;`
- L178 _public member_ `UE::GeometryFlow::FGraph::FHandle TexSourceNode;`
- L179 _public member_ `UE::GeometryFlow::FGraph::FHandle BakeNode;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Geometry` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Editor/MeshLODToolset/Source/MeshLODToolset/Public/Graphs/GenerateStaticMeshLODProcess.h` (Public)


#### enum `EGenerateStaticMeshLODProcess_MeshGeneratorModes`  
`enum class EGenerateStaticMeshLODProcess_MeshGeneratorModes : uint8`  
_L27-48_
- reflection: `UENUM()`
- L35 _public enumerator_ `Solidify = 0` — Generate a mesh using Marching Cubes to remesh the input shape. Use Winding Numbers to determine what is inside
- L41 _public enumerator_ `SolidifyAndClose = 1` — Like Solidify, but Dilate and Contract the shape to delete small negative features (sharp inner corners, small holes) before remeshing
- L44 _public enumerator_ `CleanAndSimplify = 2` — Generate a mesh by simplifying input Mesh attributes and filling small holes
- L47 _public enumerator_ `ConvexHull = 3` — Generate a mesh by calculating the Convex Hull of the input shape

#### struct `FGenerateStaticMeshLODProcessSettings`  
`struct FGenerateStaticMeshLODProcessSettings`  
_L52-91_
- reflection: `USTRUCT()`
- L58 _public member_ `EGenerateStaticMeshLODProcess_MeshGeneratorModes MeshGenerator = EGenerateStaticMeshLODProcess_MeshGeneratorModes::SolidifyAndClose;` — `UPROPERTY(EditAnywhere, Category = MeshGenerator, meta = (DisplayName="Mesh Generator"))` — Method used to generate the initial mesh for AutoLOD processing
- L65 _public member_ `int SolidifyVoxelResolution = 128;` — `UPROPERTY(EditAnywhere, Category = Solidify, meta = (UIMin = "8", UIMax = "1024", ClampMin = "8", ClampMax = "1024", DisplayName="Voxel Resolution", EditConditionHides, EditCondition = "MeshGenerator == EGenerateStaticMeshLODProcess_MeshGeneratorModes::Solidify || MeshGenerator == EGenerateStaticMeshLODProcess_MeshGeneratorModes::SolidifyAndClose"))` — Target number of voxels along the maximum dimension for Solidify operation
- L70 _public member_ `float WindingThreshold = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Solidify, AdvancedDisplay, meta = (UIMin = "0.1", UIMax = ".9", ClampMin = "-10", ClampMax = "10", EditConditionHides, EditCondition = "MeshGenerator == EGenerateStaticMeshLODProcess_MeshGeneratorModes::Solidify || MeshGenerator == EGenerateStaticMeshLODProcess_MeshGeneratorModes::SolidifyAndClose"))` — Winding number threshold to determine what is considered inside the mesh during Solidify
- L78 _public member_ `float ClosureDistance = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Morphology, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000", DisplayName = "Closure Distance", EditConditionHides, EditCondition = "MeshGenerator == EGenerateStaticMeshLODProcess_MeshGeneratorModes::SolidifyAndClose"))` — Offset distance in the Morpohological Closure operation
- L85 _public member_ `bool bPrefilterVertices = true;` — `UPROPERTY(EditAnywhere, Category = Collision, meta = (EditConditionHides, EditCondition = "MeshGenerator == EGenerateStaticMeshLODProcess_MeshGeneratorModes::ConvexHull"))` — Whether to subsample input vertices using a regular grid before computing the convex hull
- L89 _public member_ `int PrefilterGridResolution = 10;` — `UPROPERTY(EditAnywhere, Category = Collision, meta = (NoSpinbox = "true", EditConditionHides, EditCondition = "MeshGenerator == EGenerateStaticMeshLODProcess_MeshGeneratorModes::ConvexHull && bPrefilterVertices", ClampMin = "4", ClampMax = "100"))` — Grid resolution (along the maximum-length axis) for subsampling before computing the convex hull

#### struct `FGenerateStaticMeshLODProcess_PreprocessSettings`  
`struct FGenerateStaticMeshLODProcess_PreprocessSettings`  
_L96-131_
- reflection: `USTRUCT()`
- L109 _public member_ `FName FilterGroupLayer = FName();` — `UPROPERTY(EditAnywhere, Category = Preprocessing, meta = (DisplayName = "Detail Filter Group Layer"))` — Group layer to use for filtering out detail before processing
- L119 _public member_ `FName ThickenWeightMapName = FName();` — `UPROPERTY(EditAnywhere, Category = Preprocessing, meta = (DisplayName = "Thicken Weight Map"))` — Weight map used during mesh thickening
- L126 _public member_ `float ThickenAmount = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Preprocessing, meta = (EditCondition = "bIsThickenAmountEnabled", HideEditConditionToggle, UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000"))` — Amount to thicken the mesh prior to Solidifying. The thicken weight map values are multiplied by this value. Thickening is primarily intended to repair shape erosion that can occur when using the Solidify Mesh Generators.
- L130 _public member_ `bool bIsThickenAmountEnabled = false;` — `UPROPERTY(meta = (TransientToolProperty))` — Transient property, not exposed to the user.

#### enum `EGenerateStaticMeshLODProcess_SimplifyMethod`  
`enum class EGenerateStaticMeshLODProcess_SimplifyMethod : uint8`  
_L137-144_
- reflection: `UENUM()`
- L140 _public enumerator_ `TriangleCount = 0`
- L141 _public enumerator_ `VertexCount = 1`
- L142 _public enumerator_ `TrianglePercentage = 2`
- L143 _public enumerator_ `GeometricTolerance = 3`

#### struct `FGenerateStaticMeshLODProcess_SimplifySettings`  
`struct FGenerateStaticMeshLODProcess_SimplifySettings`  
_L148-167_
- reflection: `USTRUCT()`
- L154 _public member_ `EGenerateStaticMeshLODProcess_SimplifyMethod Method = EGenerateStaticMeshLODProcess_SimplifyMethod::GeometricTolerance;` — `UPROPERTY(EditAnywhere, Category = Simplify, meta = (DisplayName = "Simplification Target"))` — Method used to simplify the mesh created in the Mesh Generation step
- L158 _public member_ `int TargetCount = 500;` — `UPROPERTY(EditAnywhere, Category = Simplify, meta = (UIMin = "1", ClampMin = "1", EditConditionHides, EditCondition = "Method == EGenerateStaticMeshLODProcess_SimplifyMethod::TriangleCount || Method == EGenerateStaticMeshLODProcess_SimplifyMethod::VertexCount"))` — Target triangle/vertex count after simplification
- L162 _public member_ `float TargetPercentage = 5.0;` — `UPROPERTY(EditAnywhere, Category = Simplify, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "100", EditConditionHides, EditCondition = "Method == EGenerateStaticMeshLODProcess_SimplifyMethod::TrianglePercentage"))` — Target triangle/vertex count after simplification
- L166 _public member_ `float Tolerance = 0.5;` — `UPROPERTY(EditAnywhere, Category = Simplify, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "100", EditConditionHides, EditCondition = "Method == EGenerateStaticMeshLODProcess_SimplifyMethod::GeometricTolerance"))` — Deviation in World Units (Centimeters)

#### enum `EGenerateStaticMeshLODProcess_NormalsMethod`  
`enum class EGenerateStaticMeshLODProcess_NormalsMethod : uint8`  
_L173-178_
- reflection: `UENUM()`
- L175 _public enumerator_ `FromAngleThreshold = 0`
- L176 _public enumerator_ `PerVertex = 1`
- L177 _public enumerator_ `PerTriangle = 2`

#### struct `FGenerateStaticMeshLODProcess_NormalsSettings`  
`struct FGenerateStaticMeshLODProcess_NormalsSettings`  
_L182-195_
- reflection: `USTRUCT()`
- L188 _public member_ `EGenerateStaticMeshLODProcess_NormalsMethod Method = EGenerateStaticMeshLODProcess_NormalsMethod::FromAngleThreshold;` — `UPROPERTY(EditAnywhere, Category = Normals, meta = (DisplayName = "Normals Method"))` — Type of Normals to generate
- L192 _public member_ `float Angle = 60.0;` — `UPROPERTY(EditAnywhere, Category = Normals, meta = (UIMin = "0", UIMax = "180", ClampMin = "0", ClampMax = "180", EditConditionHides, EditCondition = "Method == EGenerateStaticMeshLODProcess_NormalsMethod::FromAngleThreshold"))` — Split Normals (ie sharp edge) will be created along mesh edges with opening angles above this threshold
- L194 _public prototype_ `static int32 MapMethodType(int32 From, bool bProcessToGraph);`

#### enum `EGenerateStaticMeshLODProcess_AutoUVMethod`  
`enum class EGenerateStaticMeshLODProcess_AutoUVMethod : uint8`  
_L201-206_
- reflection: `UENUM()`
- L203 _public enumerator_ `PatchBuilder = 0`
- L204 _public enumerator_ `UVAtlas = 1`
- L205 _public enumerator_ `XAtlas = 2`

#### struct `FGenerateStaticMeshLODProcess_UVSettings_PatchBuilder`  
`struct FGenerateStaticMeshLODProcess_UVSettings_PatchBuilder`  
_L210-225_
- reflection: `USTRUCT()`
- L216 _public member_ `float CurvatureAlignment = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "PatchBuilder", meta = (UIMin = "0.1", UIMax = "2.0", ClampMin = "0.01", ClampMax = "100.0"))` — This parameter controls alignment of the initial patches to creases in the mesh
- L220 _public member_ `int SmoothingSteps = 5;` — `UPROPERTY(EditAnywhere, Category = "PatchBuilder", AdvancedDisplay, meta = (UIMin = "0", UIMax = "25", ClampMin = "0", ClampMax = "1000"))` — Number of smoothing steps to apply; this slightly increases distortion but produces more stable results.
- L224 _public member_ `float SmoothingAlpha = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "PatchBuilder", AdvancedDisplay, meta = (UIMin = "0", UIMax = "1.0", ClampMin = "0", ClampMax = "1.0"))` — Smoothing parameter; larger values result in faster smoothing in each step.

#### struct `FGenerateStaticMeshLODProcess_UVSettings`  
`struct FGenerateStaticMeshLODProcess_UVSettings`  
_L228-253_
- reflection: `USTRUCT()`
- L233 _public member_ `EGenerateStaticMeshLODProcess_AutoUVMethod UVMethod = EGenerateStaticMeshLODProcess_AutoUVMethod::PatchBuilder;` — `UPROPERTY(EditAnywhere, Category = UVGeneration, meta = (DisplayName = "UV Method"))`
- L237 _public member_ `int NumUVAtlasCharts = 0;` — `UPROPERTY(EditAnywhere, Category = "UVAtlas", meta = (DisplayName = "Max Charts", UIMin = 0, UIMax = 1000, EditConditionHides, EditCondition = "UVMethod == EGenerateStaticMeshLODProcess_AutoUVMethod::UVAtlas"))` — Maximum number of charts to create in UVAtlas
- L241 _public member_ `int NumInitialPatches = 100;` — `UPROPERTY(EditAnywhere, Category = "PatchBuilder", meta = (UIMin = "1", UIMax = "1000", ClampMin = "1", ClampMax = "99999999", EditConditionHides, EditCondition = "UVMethod == EGenerateStaticMeshLODProcess_AutoUVMethod::PatchBuilder"))` — Number of initial patches mesh will be split into before computing island merging
- L245 _public member_ `float MergingThreshold = 1.5f;` — `UPROPERTY(EditAnywhere, Category = "PatchBuilder", meta = (UIMin = "1.0", UIMax = "5.0", ClampMin = "1.0", EditConditionHides, EditCondition = "UVMethod == EGenerateStaticMeshLODProcess_AutoUVMethod::PatchBuilder"))` — Distortion/Stretching Threshold for island merging - larger values increase the allowable UV stretching
- L249 _public member_ `float MaxAngleDeviation = 45.0f;` — `UPROPERTY(EditAnywhere, Category = "PatchBuilder", meta = (UIMin = "0.0", UIMax = "90.0", ClampMin = "0.0", ClampMax = "180.0", EditConditionHides, EditCondition = "UVMethod == EGenerateStaticMeshLODProcess_AutoUVMethod::PatchBuilder"))` — UV islands will not be merged if their average face normals deviate by larger than this amount
- L252 _public member_ `FGenerateStaticMeshLODProcess_UVSettings_PatchBuilder PatchBuilder;` — `UPROPERTY(EditAnywhere, Category = "PatchBuilder", meta = (DisplayName = "UV - PatchBuilder", UIMin = "0.0", UIMax = "90.0", ClampMin = "0.0", ClampMax = "180.0", EditConditionHides, EditCondition = "UVMethod == EGenerateStaticMeshLODProcess_AutoUVMethod::PatchBuilder"))`

#### enum `EGenerateStaticMeshLODBakeResolution`  
`enum class EGenerateStaticMeshLODBakeResolution`  
_L259-271_
- reflection: `UENUM()`
- L261 _public enumerator_ `Resolution16 = 16 UMETA(DisplayName = "16 x 16")`
- L262 _public enumerator_ `Resolution32 = 32 UMETA(DisplayName = "32 x 32")`
- L263 _public enumerator_ `Resolution64 = 64 UMETA(DisplayName = "64 x 64")`
- L264 _public enumerator_ `Resolution128 = 128 UMETA(DisplayName = "128 x 128")`
- L265 _public enumerator_ `Resolution256 = 256 UMETA(DisplayName = "256 x 256")`
- L266 _public enumerator_ `Resolution512 = 512 UMETA(DisplayName = "512 x 512")`
- L267 _public enumerator_ `Resolution1024 = 1024 UMETA(DisplayName = "1024 x 1024")`
- L268 _public enumerator_ `Resolution2048 = 2048 UMETA(DisplayName = "2048 x 2048")`
- L269 _public enumerator_ `Resolution4096 = 4096 UMETA(DisplayName = "4096 x 4096")`
- L270 _public enumerator_ `Resolution8192 = 8192 UMETA(DisplayName = "8192 x 8192")`

#### struct `FGenerateStaticMeshLODProcess_TextureSettings`  
`struct FGenerateStaticMeshLODProcess_TextureSettings`  
_L276-291_
- reflection: `USTRUCT()`
- L282 _public member_ `EGenerateStaticMeshLODBakeResolution BakeResolution = EGenerateStaticMeshLODBakeResolution::Resolution1024;` — `UPROPERTY(EditAnywhere, Category = Baking , meta = (DisplayName = "Bake Image Res"))` — Resolution for normal map and texture baking
- L286 _public member_ `float BakeThickness = 5.0f;` — `UPROPERTY(EditAnywhere, Category = Baking, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000", DisplayName = "Bake Thickness"))` — How far away from the output mesh to search for input mesh during baking
- L290 _public member_ `bool bCombineTextures = true;` — `UPROPERTY(EditAnywhere, Category = Baking, meta = (DisplayName = "Combine Textures"))` — Generate an atlassed texture where multiple textures are combined into a single output texture

#### enum `EGenerateStaticMeshLODSimpleCollisionGeometryType`  
`enum class EGenerateStaticMeshLODSimpleCollisionGeometryType : uint8`  
_L297-308_
- reflection: `UENUM()`
- L300 _public enumerator_ `AlignedBoxes`
- L301 _public enumerator_ `OrientedBoxes`
- L302 _public enumerator_ `MinimalSpheres`
- L303 _public enumerator_ `Capsules`
- L304 _public enumerator_ `ConvexHulls`
- L305 _public enumerator_ `SweptHulls`
- L306 _public enumerator_ `MinVolume`
- L307 _public enumerator_ `None`

#### enum `EGenerateStaticMeshLODProjectedHullAxisMode`  
`enum class EGenerateStaticMeshLODProjectedHullAxisMode : uint8`  
_L312-320_
- reflection: `UENUM()`
- L315 _public enumerator_ `X = 0`
- L316 _public enumerator_ `Y = 1`
- L317 _public enumerator_ `Z = 2`
- L318 _public enumerator_ `SmallestBoxDimension = 3`
- L319 _public enumerator_ `SmallestVolume = 4`

#### struct `FGenerateStaticMeshLODProcess_CollisionSettings`  
`struct FGenerateStaticMeshLODProcess_CollisionSettings`  
_L325-368_
- reflection: `USTRUCT()`
- L332 _public member_ `FName CollisionGroupLayerName = TEXT("Def` — `UPROPERTY(meta = (TransientToolProperty))` — Transient property, not set directly by the user. The user controls a CollisionGroupLayerName dropdown property on the Tool and that value is copied here.
- L336 _public member_ `EGenerateStaticMeshLODSimpleCollisionGeometryType CollisionType = EGenerateStaticMeshLODSimpleCollisionGeometryType::ConvexHulls;` — `UPROPERTY(EditAnywhere, Category = Collision, meta = (DisplayName = "Collision Type"))` — Type of simple collision objects to produce
- L343 _public member_ `int ConvexTriangleCount = 50;` — `UPROPERTY(EditAnywhere, Category = Collision, meta = (NoSpinbox = "true", DisplayName = "Convex Tri Count", EditConditionHides, EditCondition = "CollisionType == EGenerateStaticMeshLODSimpleCollisionGeometryType::ConvexHulls"))` — Target triangle count for each convex hull after simplification
- L347 _public member_ `bool bPrefilterVertices = true;` — `UPROPERTY(EditAnywhere, Category = Collision, meta = (EditConditionHides, EditCondition = "CollisionType == EGenerateStaticMeshLODSimpleCollisionGeometryType::ConvexHulls"))` — Whether to subsample input vertices using a regular grid before computing the convex hull
- L351 _public member_ `int PrefilterGridResolution = 10;` — `UPROPERTY(EditAnywhere, Category = Collision, meta = (NoSpinbox = "true", EditConditionHides, EditCondition = "CollisionType == EGenerateStaticMeshLODSimpleCollisionGeometryType::ConvexHulls && bPrefilterVertices", UIMin = 4, UIMax = 100))` — Grid resolution (along the maximum-length axis) for subsampling before computing the convex hull
- L358 _public member_ `bool bSimplifyPolygons = true;` — `UPROPERTY(EditAnywhere, Category = Collision, meta = (EditConditionHides, EditCondition = "CollisionType == EGenerateStaticMeshLODSimpleCollisionGeometryType::SweptHulls"))` — Whether to simplify polygons used for swept convex hulls
- L363 _public member_ `float HullTolerance = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Collision, meta = (NoSpinbox = "true", UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "100000", EditConditionHides, EditCondition = "CollisionType == EGenerateStaticMeshLODSimpleCollisionGeometryType::SweptHulls"))` — Target minumum edge length for simplified swept convex hulls
- L367 _public member_ `EGenerateStaticMeshLODProjectedHullAxisMode SweepAxis = EGenerateStaticMeshLODProjectedHullAxisMode::SmallestVolume;` — `UPROPERTY(EditAnywhere, Category = Collision, meta = (EditConditionHides, EditCondition = "CollisionType == EGenerateStaticMeshLODSimpleCollisionGeometryType::SweptHulls"))` — Which axis to sweep along when computing swept convex hulls

#### class `UGenerateStaticMeshLODProcess`  
`class UGenerateStaticMeshLODProcess : public UObject`  
_L373-648_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- L385 _public prototype_ `[[nodiscard]] bool Initialize(UStaticMesh* SourceMesh, FProgressCancel* Progress = nullptr);` — Initialize the Process, this will: - read the Source Mesh, either LOD0 or the HiRes LOD if available - Extract all Materials and Textures from the Source Asset and determine what needs to be baked - Read all the Source Texture Images that need to be baked - call InitializeGenerator() to set up the compute graph
- L389 _public function_ `UStaticMesh* GetSourceStaticMesh() const` — @return the source UStaticMesh passed to Initialize()
- L391 _public function_ `const FDynamicMesh3& GetSourceMesh() const` — @return the converted source MeshDescription as a FDynamicMesh3, valid after Initialize() finishes
- L399 _public function_ `const FGenerateStaticMeshLODProcess_PreprocessSettings& GetCurrentPreprocessSettings() const`
- L400 _public prototype_ `void UpdatePreprocessSettings(const FGenerateStaticMeshLODProcess_PreprocessSettings& NewSettings);`
- L402 _public function_ `const FGenerateStaticMeshLODProcessSettings& GetCurrentSettings() const`
- L403 _public prototype_ `void UpdateSettings(const FGenerateStaticMeshLODProcessSettings& NewSettings);`
- L405 _public function_ `const FGenerateStaticMeshLODProcess_SimplifySettings& GetCurrentSimplifySettings() const`
- L406 _public prototype_ `void UpdateSimplifySettings(const FGenerateStaticMeshLODProcess_SimplifySettings& NewSettings);`
- L408 _public function_ `const FGenerateStaticMeshLODProcess_NormalsSettings& GetCurrentNormalsSettings() const`
- L409 _public prototype_ `void UpdateNormalsSettings(const FGenerateStaticMeshLODProcess_NormalsSettings& NewSettings);`
- L411 _public function_ `const FGenerateStaticMeshLODProcess_TextureSettings& GetCurrentTextureSettings() const`
- L412 _public prototype_ `void UpdateTextureSettings(const FGenerateStaticMeshLODProcess_TextureSettings& NewSettings);`
- L414 _public function_ `const FGenerateStaticMeshLODProcess_UVSettings& GetCurrentUVSettings() const`
- L415 _public prototype_ `void UpdateUVSettings(const FGenerateStaticMeshLODProcess_UVSettings& NewSettings);`
- L417 _public function_ `const FGenerateStaticMeshLODProcess_CollisionSettings& GetCurrentCollisionSettings() const`
- L418 _public prototype_ `void UpdateCollisionSettings(const FGenerateStaticMeshLODProcess_CollisionSettings& NewSettings);`
- L426 _public prototype_ `TArray<UMaterialInterface*> GetSourceBakeMaterials() const;` — @return the set of Materials that were identified on the Source Asset
- L435 _public prototype_ `void UpdateSourceBakeMaterialConstraint(UMaterialInterface* Material, EMaterialBakingConstraint Constraint);` — Configure the constraint on the specified Source Material
- L443 _public prototype_ `TArray<UTexture2D*> GetSourceBakeTextures() const;` — @return the set of Textures that were identified as being parameters to the Source Materials, that are identified as potentially needing to be baked to the Derived Asset UVs
- L453 _public prototype_ `void UpdateSourceBakeTextureConstraint(UTexture2D* Texture, ETextureBakingConstraint Constraint);` — Configure the constraint on the specified Source Texture
- L464 _public prototype_ `void UpdateDerivedPathName(const FString& NewAssetBaseName, const FString& NewAssetSuffix);` — Configure the output Name and Suffix for the Mesh Asset. The various strings below will be computed based on this input
- L467 _public function_ `const FString& GetSourceAssetPath() const`
- L468 _public function_ `const FString& GetSourceAssetFolder() const`
- L469 _public function_ `const FString& GetSourceAssetName() const`
- L470 _public function_ `static FString GetDefaultDerivedAssetSuffix()`
- L471 _public function_ `const FString& GetDerivedAssetName() const`
- L478 _public prototype_ `bool ComputeDerivedSourceData(FProgressCancel* Progress);`
- L481 _public function_ `const FDynamicMesh3& GetDerivedLOD0Mesh() const` — The Generated Mesh
- L483 _public function_ `const UE::Geometry::FMeshTangentsd& GetDerivedLOD0MeshTangents() const` — Tangents for the Generated Mesh
- L485 _public function_ `const UE::Geometry::FSimpleShapeSet3d& GetDerivedCollision() const` — Collision geometry for the Generated Mesh
- L493 _public prototype_ `void GetDerivedMaterialsPreview(FPreviewMaterials& MaterialSetOut);` — Set of Materials and Textures to be applied to the Generated Mesh
- L503 _public prototype_ `virtual bool WriteDerivedAssetData();` — Creates new UStaticMesh Asset, Material Instances, and Textures
- L510 _public prototype_ `virtual void UpdateSourceAsset(bool bSetNewHDSourceAsset = false);` — Update the input UStaticMesh Asset (ie the asset passed to Initialize) @param bSetNewHDSourceAsset If true, the original source mesh copied to the UStaticMesh's HiRes SourceModel slot
- L521 _public member_ `FCriticalSection GraphEvalCriticalSection;` — This FCriticalSection is used to co-ordinate evaluation of the internal compute graph by external classes. Generally while doing things like changing settings, reading output, etc, the internal compute graph cannot be executing. Often this needs to be locked across multiple function calls, so it is exposed publicly.  (TODO: clean this up...)
- L526 _protected member_ `TObjectPtr<UStaticMesh> SourceStaticMesh;` — `UPROPERTY()`
- L528 _protected member_ `FString SourceAssetPath;`
- L529 _protected member_ `FString SourceAssetFolder;`
- L530 _protected member_ `FString SourceAssetName;`
- L533 _protected member_ `bool bUsingHiResSource = false;` — if true, we are building new LOD0 from the StaticMesh HiRes SourceModel, instead of from the mesh in LOD0
- L536 _protected member_ `TSharedPtr<FMeshDescription> SourceMeshDescription;` — copy of input MeshDescription with autogenerated attributes computed
- L538 _protected member_ `FDynamicMesh3 SourceMesh;` — SourceMeshDescription converted to FDynamicMesh3
- L553 _protected prototype_ `int SelectTextureToBake(const TArray<FTextureInfo>& TextureInfos) const;`
- L571 _protected member_ `TArray<FSourceMaterialInfo> SourceMaterials;` — list of initial Source Materials, length equivalent to StaticMesh.StaticMaterials
- L573 _protected member_ `FString DerivedSuffix;`
- L574 _protected member_ `FString DerivedAssetPath;`
- L575 _protected member_ `FString DerivedAssetFolder;`
- L576 _protected member_ `FString DerivedAssetName;`
- L577 _protected member_ `FString DerivedAssetNameNoSuffix;`
- L580 _protected member_ `FDynamicMesh3 DerivedLODMesh;` — the new generated LOD0 mesh
- L581 _protected member_ `UE::Geometry::FMeshTangentsd DerivedLODMeshTangents;` — Tangents for DerivedLODMesh
- L582 _protected member_ `UE::Geometry::FSimpleShapeSet3d DerivedCollision;` — Simple Collision for DerivedLODMesh
- L585 _protected member_ `UE::GeometryFlow::FNormalMapImage DerivedNormalMapImage;` — Texture set potentially required by output Material set
- L586 _protected member_ `TArray<TUniquePtr<UE::GeometryFlow::FTextureImage>> DerivedTextureImages;` — generated Textures
- L587 _protected member_ `UE::GeometryFlow::FTextureImage DerivedMultiTextureBakeImage;`
- L588 _protected member_ `TMap<UTexture2D*, int32> SourceTextureToDerivedTexIndex;` — mapping from input Textures to DerivedTextureImages index
- L601 _protected member_ `TArray<FDerivedMaterialInfo> DerivedMaterials;` — list of generated/Derived Materials. Length is the same as SourceMaterials and indices correspond, however some Derived Materials may not be initialized (if Source is reusable or generated)
- L606 _protected member_ `TSet<TObjectPtr<UTexture2D>> AllDerivedTextures;` — `UPROPERTY()` — This list is for accumulating derived UTexture2D's created during WriteDerivedTextures(). We have to maintain uproperty references to these or they may be garbage collected
- L610 _protected member_ `TObjectPtr<UTexture2D> DerivedNormalMapTex;` — `UPROPERTY()` — Derived Normal Map
- L613 _protected member_ `TMap<int32, FName> MultiTextureParameterName;` — For each material participating in multi-texture baking, the parameter name of the texture
- L616 _protected member_ `TObjectPtr<UTexture2D> DerivedMultiTextureBakeResult;` — `UPROPERTY()`
- L619 _protected member_ `TUniquePtr<FGenerateMeshLODGraph> Generator;` — active LODGenerator Graph
- L620 _protected prototype_ `bool InitializeGenerator();`
- L622 _protected member_ `FGenerateStaticMeshLODProcess_PreprocessSettings CurrentSettings_Preprocess;`
- L623 _protected member_ `FGenerateStaticMeshLODProcessSettings CurrentSettings;`
- L624 _protected member_ `FGenerateStaticMeshLODProcess_SimplifySettings CurrentSettings_Simplify;`
- L625 _protected member_ `FGenerateStaticMeshLODProcess_NormalsSettings CurrentSettings_Normals;`
- L626 _protected member_ `FGenerateStaticMeshLODProcess_TextureSettings CurrentSettings_Texture;`
- L627 _protected member_ `FGenerateStaticMeshLODProcess_UVSettings CurrentSettings_UV;`
- L628 _protected member_ `FGenerateStaticMeshLODProcess_CollisionSettings CurrentSettings_Collision;`
- L632 _protected member_ `FString DerivedAssetGUIDKey;` — This value will be stored in Asset Metadata for each generated Asset Texture, Material/MIC, and StaticMesh, under the key StaticMeshLOD.GenerationGUID.
- L634 _protected prototype_ `bool WriteDerivedTexture(UTexture2D* SourceTexture, UTexture2D* DerivedTexture, bool bCreatingNewStaticMeshAsset);`
- L635 _protected prototype_ `bool WriteDerivedTexture(UTexture2D* DerivedTexture, FString BaseTexName, bool bCreatingNewStaticMeshAsset);`
- L636 _protected prototype_ `void WriteDerivedTextures(bool bCreatingNewStaticMeshAsset);`
- L637 _protected prototype_ `void WriteDerivedMaterials(bool bCreatingNewStaticMeshAsset);`
- L638 _protected prototype_ `void UpdateMaterialTextureParameters(UMaterialInstanceConstant* Material, FDerivedMaterialInfo& DerivedMaterialInfo);`
- L639 _protected prototype_ `void WriteDerivedStaticMeshAsset();`
- L641 _protected prototype_ `void UpdateSourceStaticMeshAsset(bool bSetNewHDSourceAsset);`
- L643 _protected prototype_ `void UpdateMaterialTextureParameters(UMaterialInstanceDynamic* Material, const FSourceMaterialInfo& SourceMaterialInfo, const TMap<UTexture2D*,UTexture2D*>& PreviewTextures, UTexture2D* PreviewNormalMap);`
- L647 _protected prototype_ `bool IsSourceAsset(const FString& AssetPath) const;` — Return true if the given path corresponds to a material or texture in SourceMaterials

#### enum `UGenerateStaticMeshLODProcess::EMaterialBakingConstraint`  
`enum class EMaterialBakingConstraint`  
_L428-432_
- L430 _public enumerator_ `NoConstraint = 0`
- L431 _public enumerator_ `UseExistingMaterial = 1`

#### enum `UGenerateStaticMeshLODProcess::ETextureBakingConstraint`  
`enum class ETextureBakingConstraint`  
_L446-450_
- L448 _public enumerator_ `NoConstraint = 0`
- L449 _public enumerator_ `UseExistingTexture = 1`

#### struct `UGenerateStaticMeshLODProcess::FPreviewMaterials`  
`struct FPreviewMaterials`  
_L487-491_
- L489 _public member_ `TArray<UMaterialInterface*> Materials;`
- L490 _public member_ `TArray<UTexture2D*> Textures;`

#### struct `UGenerateStaticMeshLODProcess::FTextureInfo`  
`struct FTextureInfo`  
_L540-551_
- L542 _public member_ `UTexture2D* Texture = nullptr;`
- L543 _public member_ `FName ParameterName;`
- L544 _public member_ `UE::Geometry::FImageDimensions Dimensions;`
- L545 _public member_ `UE::Geometry::TImageBuilder<FVector4f> Image;`
- L546 _public member_ `bool bIsNormalMap = false;`
- L547 _public member_ `bool bIsDefaultTexture = false;`
- L548 _public member_ `bool bShouldBakeTexture = false;`
- L549 _public member_ `bool bIsUsedInMultiTextureBaking = false;`
- L550 _public member_ `ETextureBakingConstraint Constraint = ETextureBakingConstraint::NoConstraint;`

#### struct `UGenerateStaticMeshLODProcess::FSourceMaterialInfo`  
`struct FSourceMaterialInfo`  
_L556-568_
- desc: Information about one of the input StaticMesh Materials. Computed in Initialize() and not modified afterwards
- L558 _public member_ `FStaticMaterial SourceMaterial;`
- L559 _public member_ `TArray<FTextureInfo> SourceTextures;`
- L561 _public member_ `bool bHasNormalMap = false;` — if true, Material has an exposed NormalMap input texture parameter
- L562 _public member_ `bool bHasTexturesToBake = false;` — if true, Material has at least one SourceTexture that should be baked
- L563 _public member_ `bool bIsReusable = false;` — if true, Material doesn't need any texture baking and can be re-used by LOD0
- L564 _public member_ `bool bIsPreviouslyGeneratedMaterial = false;` — if true, this Material was previously generated by AutoLOD and should be discarded.
- L567 _public member_ `EMaterialBakingConstraint Constraint = EMaterialBakingConstraint::NoConstraint;`

#### struct `UGenerateStaticMeshLODProcess::FDerivedMaterialInfo`  
`struct FDerivedMaterialInfo`  
_L591-598_
- desc: Information about an output Material
- L593 _public member_ `int32 SourceMaterialIndex = -1;` — Index into SourceMaterials
- L594 _public member_ `bool bUseSourceMaterialDirectly = false;` — If true, do not create/use a Derived Material, directly re-use SourceMaterials[SourceMaterialIndex]
- L596 _public member_ `FStaticMaterial DerivedMaterial;` — points to generated Material
- L597 _public member_ `TArray<FTextureInfo> DerivedTextures;` — List of generated Textures

### `Plugins/Editor/MeshLODToolset/Source/MeshLODToolset/Public/MeshLODToolsetModule.h` (Public)


#### class `FMeshLODToolsetModule`  
`class FMeshLODToolsetModule : public IModuleInterface`  
_L12-29_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public prototype_ `void OnPostEngineInit();`
- L23 _public member_ `TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;` — registered asset actions
- L27 _private member_ `TArray<FName> ClassesToUnregisterOnShutdown;` — StaticClass is not safe on shutdown, so we cache the name, and use this to unregister on shut down

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshLODToolset, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshLODToolset, Log, All);`

### `Plugins/Editor/MeshLODToolset/Source/MeshLODToolset/Public/Tools/DetailsCustomizations/AutoLODToolCustomizations.h` (Public)


#### class `FAutoLODToolDetails`  
`class FAutoLODToolDetails : public IDetailCustomization`  
_L11-16_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/Editor/MeshLODToolset/Source/MeshLODToolset/Public/Tools/GenerateStaticMeshLODAssetTool.h` (Public)


#### enum `EGenerateLODAssetOutputMode`  
`enum class EGenerateLODAssetOutputMode : uint8`  
_L30-34_
- reflection: `UENUM()`
- L32 _public enumerator_ `CreateNewAsset = 0`
- L33 _public enumerator_ `UpdateExistingAsset = 1`

#### class `UGenerateStaticMeshLODAssetToolBuilder`  
`class UGenerateStaticMeshLODAssetToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L41-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- desc: Tool builder
- L46 _public member_ `bool bUseAssetEditorMode = false;`
- L47 _public member_ `bool bInRestrictiveMode = false;`
- L49 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L50 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L53 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UGenerateStaticMeshLODAssetToolOutputProperties`  
`class UGenerateStaticMeshLODAssetToolOutputProperties : public UInteractiveToolPropertySet`  
_L59-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L65 _public member_ `EGenerateLODAssetOutputMode OutputMode = EGenerateLODAssetOutputMode::CreateNewAsset;` — `UPROPERTY(EditAnywhere, Category = "Output Options", meta = (TransientToolProperty, HideEditConditionToggle, EditCondition = "bShowOutputMode"))` — Whether to modify the static mesh in place or create a new one.
- L69 _public member_ `FString NewAssetName;` — `UPROPERTY(EditAnywhere, Category = "Output Options", meta = (TransientToolProperty, EditConditionHides, EditCondition = "OutputMode == EGenerateLODAssetOutputMode::CreateNewAsset"))` — Base name for newly-generated asset
- L73 _public member_ `bool bSaveInputAsHiResSource = true;` — `UPROPERTY(EditAnywhere, Category = "Output Options", meta = (EditConditionHides, EditCondition = "OutputMode == EGenerateLODAssetOutputMode::UpdateExistingAsset"))` — If the Asset doesn't already have a HiRes source, store the input mesh as the HiRes source
- L77 _public member_ `FString GeneratedSuffix = TEXT("_Au` — `UPROPERTY(EditAnywhere, Category = "Output Options", meta = (TransientToolProperty))` — Suffix to append to newly-generated Asset (Meshes, Textures, Materials, etc)
- L81 _public member_ `bool bShowOutputMode = true;` — `UPROPERTY(meta = (TransientToolProperty))` — If false, then OutputMode will not be shown in DetailsView panels (otherwise no effect)

#### enum `EGenerateLODAssetToolPresetAction`  
`enum class EGenerateLODAssetToolPresetAction : uint8`  
_L88-92_
- reflection: `UENUM()`
- L90 _public enumerator_ `ReadFromPreset`
- L91 _public enumerator_ `WriteToPreset`

#### class `UGenerateStaticMeshLODAssetToolPresetProperties`  
`class UGenerateStaticMeshLODAssetToolPresetProperties : public UInteractiveToolPropertySet`  
_L96-123_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L101 _public member_ `TWeakObjectPtr<UGenerateStaticMeshLODAssetTool> ParentTool;`
- L102 _public function_ `void Initialize(UGenerateStaticMeshLODAssetTool* ParentToolIn)`
- L103 _public prototype_ `virtual void PostAction(EGenerateLODAssetToolPresetAction Action);`
- L108 _public member_ `TWeakObjectPtr<UStaticMeshLODGenerationSettings> Preset;` — `UPROPERTY(EditAnywhere, Category = Preset, meta = (DisplayName = "Settings Preset"))` — Preset Asset represents a set of Saved Settings for this Tool
- L112 _public function_ `void ReadFromPreset()` — `UFUNCTION(CallInEditor, Category = Preset, meta = (DisplayPriority = 0))` — Read the current Tool settings from the Preset Asset
- L119 _public function_ `void WriteToPreset()` — `UFUNCTION(CallInEditor, Category = Preset, meta = (DisplayPriority = 1))` — Save the current Tool settings to the Preset Asset

#### class `UGenerateStaticMeshLODAssetToolProperties`  
`class UGenerateStaticMeshLODAssetToolProperties : public UInteractiveToolPropertySet`  
_L131-195_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties
- L137 _public member_ `FGenerateStaticMeshLODProcess_PreprocessSettings Preprocessing;` — `UPROPERTY(EditAnywhere, Category = "Generator Configuration")`
- L140 _public member_ `FGenerateStaticMeshLODProcessSettings MeshGeneration;` — `UPROPERTY(EditAnywhere, Category = "Generator Configuration", meta = (ExpandByDefault))`
- L143 _public member_ `FGenerateStaticMeshLODProcess_SimplifySettings Simplification;` — `UPROPERTY(EditAnywhere, Category = "Generator Configuration", meta = (ExpandByDefault))`
- L146 _public member_ `FGenerateStaticMeshLODProcess_NormalsSettings Normals;` — `UPROPERTY(EditAnywhere, Category = "Generator Configuration", meta = (ExpandByDefault))`
- L149 _public member_ `FGenerateStaticMeshLODProcess_TextureSettings TextureBaking;` — `UPROPERTY(EditAnywhere, Category = "Generator Configuration", meta = (ExpandByDefault))`
- L152 _public member_ `FGenerateStaticMeshLODProcess_UVSettings UVGeneration;` — `UPROPERTY(EditAnywhere, Category = "Generator Configuration")`
- L155 _public member_ `FGenerateStaticMeshLODProcess_CollisionSettings SimpleCollision;` — `UPROPERTY(EditAnywhere, Category = "Generator Configuration")`
- L163 _public member_ `FName CollisionGroupLayerName = TEXT("Def` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (GetOptions = GetGroupLayersFunc))` — Group layer to use for partitioning the mesh for simple collision generation
- L167 _public function_ `TArray<FString> GetGroupLayersFunc()` — `UFUNCTION()` — this function is called provide set of available group layers
- L174 _public member_ `TArray<FString> GroupLayersList;` — `UPROPERTY(meta = (TransientToolProperty))` — internal list used to implement above
- L176 _public function_ `void InitializeGroupLayers(const FDynamicMesh3* Mesh)`

#### enum `EGenerateStaticMeshLOD_BakeConstraint`  
`enum class EGenerateStaticMeshLOD_BakeConstraint`  
_L199-203_
- reflection: `UENUM()`
- L201 _public enumerator_ `NoConstraint = 0`
- L202 _public enumerator_ `DoNotBake = 1`

#### struct `FGenerateStaticMeshLOD_TextureConfig`  
`struct FGenerateStaticMeshLOD_TextureConfig`  
_L206-220_
- reflection: `USTRUCT()`
- L211 _public member_ `TObjectPtr<UTexture2D> Texture = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Texture)`
- L214 _public member_ `EGenerateStaticMeshLOD_BakeConstraint Constraint = EGenerateStaticMeshLOD_BakeConstraint::NoConstraint;` — `UPROPERTY(EditAnywhere, Category = Texture)`
- L216 _public function_ `bool operator==(const FGenerateStaticMeshLOD_TextureConfig& Other) const`

#### struct `FGenerateStaticMeshLOD_MaterialConfig`  
`struct FGenerateStaticMeshLOD_MaterialConfig`  
_L224-238_
- reflection: `USTRUCT()`
- L229 _public member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Material, meta = (TransientToolProperty, NoResetToDefault))`
- L232 _public member_ `EGenerateStaticMeshLOD_BakeConstraint Constraint = EGenerateStaticMeshLOD_BakeConstraint::NoConstraint;` — `UPROPERTY(EditAnywhere, Category = Texture, meta = (TransientToolProperty, NoResetToDefault))`
- L234 _public function_ `bool operator==(const FGenerateStaticMeshLOD_MaterialConfig& Other) const`

#### class `UGenerateStaticMeshLODAssetToolTextureProperties`  
`class UGenerateStaticMeshLODAssetToolTextureProperties : public UInteractiveToolPropertySet`  
_L243-255_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L248 _public member_ `TArray<FGenerateStaticMeshLOD_MaterialConfig> Materials;` — `UPROPERTY(EditAnywhere, Category = "Source Materials Configuration", meta = (TransientToolProperty, NoResetToDefault))`
- L251 _public member_ `TArray<FGenerateStaticMeshLOD_TextureConfig> Textures;` — `UPROPERTY(EditAnywhere, Category = "Source Textures Configuration", meta = (TransientToolProperty, NoResetToDefault))`
- L254 _public member_ `TArray<TObjectPtr<UTexture2D>> PreviewTextures;` — `UPROPERTY(VisibleAnywhere, Category = "Baked Texture Previews", meta = (TransientToolProperty, NoResetToDefault))`

#### class `UGenerateStaticMeshLODAssetTool`  
`class UGenerateStaticMeshLODAssetTool : public UMultiSelectionMeshEditingTool`  
_L264-345_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool`
- desc: Simple tool to combine multiple meshes into a single mesh asset
- L271 _public prototype_ `virtual void SetUseAssetEditorMode(bool bEnable);` — Enable UI Customization for running this Tool in the Static Mesh Asset Editor. Must be called before Setup.
- L274 _public prototype_ `virtual void SetRestrictiveMode(bool bEnable);` — Enable restrictive mode. Must be called before Setup.
- L276 _public prototype_ `virtual void Setup() override;`
- L277 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L279 _public prototype_ `virtual void OnTick(float DeltaTime);`
- L281 _public function_ `virtual bool HasCancel() const override`
- L282 _public function_ `virtual bool HasAccept() const override`
- L283 _public prototype_ `virtual bool CanAccept() const override;`
- L285 _public prototype_ `virtual void RequestPresetAction(EGenerateLODAssetToolPresetAction ActionType);`
- L290 _protected member_ `TObjectPtr<UGenerateStaticMeshLODAssetToolOutputProperties> OutputProperties = nullptr;` — `UPROPERTY()`
- L293 _protected member_ `TObjectPtr<UGenerateStaticMeshLODAssetToolProperties> BasicProperties = nullptr;` — `UPROPERTY()`
- L296 _protected member_ `TObjectPtr<UGenerateStaticMeshLODAssetToolPresetProperties> PresetProperties = nullptr;` — `UPROPERTY()`
- L299 _protected member_ `TObjectPtr<UGenerateStaticMeshLODAssetToolTextureProperties> TextureProperties = nullptr;` — `UPROPERTY()`
- L302 _protected member_ `TObjectPtr<UCollisionGeometryVisualizationProperties> CollisionVizSettings = nullptr;` — `UPROPERTY()`
- L311 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> PreviewWithBackgroundCompute = nullptr;` — `UPROPERTY()`
- L314 _protected member_ `TArray<TObjectPtr<UTexture2D>> PreviewTextures;` — `UPROPERTY()`
- L317 _protected member_ `TArray<TObjectPtr<UMaterialInterface>> PreviewMaterials;` — `UPROPERTY()`
- L323 _protected member_ `TObjectPtr<UPhysicsObjectToolPropertySet> ObjectData = nullptr;` — `UPROPERTY()`
- L326 _protected member_ `TObjectPtr<UPreviewGeometry> CollisionPreview;` — `UPROPERTY()`
- L329 _protected member_ `bool bIsInAssetEditorMode = false;`
- L330 _protected member_ `bool bRestrictiveMode = false;`
- L333 _protected member_ `TObjectPtr<UGenerateStaticMeshLODProcess> GenerateProcess;` — `UPROPERTY()`
- L335 _protected member_ `TUniquePtr<UE::Geometry::IDynamicMeshOperatorFactory> OpFactory;`
- L337 _protected prototype_ `void OnSettingsModified();`
- L339 _protected prototype_ `void CreateNewAsset();`
- L340 _protected prototype_ `void UpdateExistingAsset();`
- L342 _protected prototype_ `void OnPresetSelectionChanged();`
- L344 _protected prototype_ `bool ValidateSettings() const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHLODTOOLSET_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L24 _namespace_ `namespace GenerateStaticMeshLODAssetLocals`

### `Plugins/Editor/MeshLODToolset/Source/MeshLODToolset/Public/Tools/LODGenerationSettingsAsset.h` (Public)


#### class `UStaticMeshLODGenerationSettings`  
`class UStaticMeshLODGenerationSettings : public UObject`  
_L19-46_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- desc: UStaticMeshLODGenerationSettings is intended to be a stored version of the settings used by UGenerateStaticMeshLODProcess (and the associated UGenerateStaticMeshLODAssetTool). This UObject is exposed as an Asset type in the Editor via UStaticMeshLODGenerationSettingsFactory. The Tool uses these serialized settings as a 'Preset', ie the user can save a set of configured settings, or load previously-saved settings.
- L26 _public member_ `FGenerateStaticMeshLODProcess_PreprocessSettings Preprocessing;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L29 _public member_ `FGenerateStaticMeshLODProcessSettings MeshGeneration;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L32 _public member_ `FGenerateStaticMeshLODProcess_SimplifySettings Simplification;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L35 _public member_ `FGenerateStaticMeshLODProcess_NormalsSettings Normals;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L38 _public member_ `FGenerateStaticMeshLODProcess_TextureSettings TextureBaking;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L41 _public member_ `FGenerateStaticMeshLODProcess_UVSettings UVGeneration;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L44 _public member_ `FGenerateStaticMeshLODProcess_CollisionSettings SimpleCollision;` — `UPROPERTY(EditAnywhere, Category=Settings)`

### `Plugins/Editor/MeshLODToolset/Source/MeshLODToolset/Public/Tools/LODGenerationSettingsFactory.h` (Public)


#### class `UStaticMeshLODGenerationSettingsFactory`  
`class UStaticMeshLODGenerationSettingsFactory : public UFactory`  
_L13-24_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- desc: Asset Factory for UStaticMeshLODGenerationSettings, which is used to save settings for the AutoLOD Tool/Process as an Asset in the Editor
- L18 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L19 _private prototype_ `virtual uint32 GetMenuCategories() const override;`
- L20 _private prototype_ `virtual FText GetDisplayName() const override;`
- L21 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L22 _private function_ `virtual bool ShouldShowInNewMenu() const override`

### `Plugins/Editor/MeshLODToolset/Source/MeshLODToolset/Public/Tools/LODManagerTool.h` (Public)


#### class `ULODManagerToolBuilder`  
`class ULODManagerToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L23-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L28 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L29 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L32 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### struct `FLODManagerLODInfo`  
`struct FLODManagerLODInfo`  
_L37-46_
- reflection: `USTRUCT()`
- L42 _public member_ `int32 VertexCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = LODInformation, meta=(NoResetToDefault))`
- L45 _public member_ `int32 TriangleCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = LODInformation, meta=(NoResetToDefault))`

#### class `ULODManagerLODProperties`  
`class ULODManagerLODProperties : public UInteractiveToolPropertySet`  
_L51-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L56 _public member_ `TArray<FLODManagerLODInfo> SourceLODs;` — `UPROPERTY(VisibleAnywhere, Category = LODInformation, meta = (NoResetToDefault))`
- L59 _public member_ `TArray<FLODManagerLODInfo> HiResSource;` — `UPROPERTY(VisibleAnywhere, Category = LODInformation, meta = (NoResetToDefault))`
- L63 _public member_ `TArray<FLODManagerLODInfo> RenderLODs;` — `UPROPERTY(VisibleAnywhere, Category = LODInformation, meta = (NoResetToDefault))`
- L66 _public member_ `bool bNaniteEnabled = false;` — `UPROPERTY(VisibleAnywhere, Category = Nanite, meta = (NoResetToDefault, DisplayName="Enabled"))`
- L70 _public member_ `float KeepTrianglePercent = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Nanite, meta = (NoResetToDefault))` — Percentage of triangles kept by Nanite
- L73 _public member_ `TArray<FStaticMaterial> Materials;` — `UPROPERTY(VisibleAnywhere, Category = Materials, meta = (NoResetToDefault))`

#### class `ULODManagerPreviewLODProperties`  
`class ULODManagerPreviewLODProperties : public UInteractiveToolPropertySet`  
_L80-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L86 _public member_ `FString VisibleLOD;` — `UPROPERTY(EditAnywhere, Category = LODPreview, meta = (DisplayName = "Show LOD", NoResetToDefault, GetOptions = GetLODNamesFunc))` — LOD to visualise. Default option is equivalent to disabling the Tool, RenderData is the mesh used for rendering derived from the SourceModel (possibly simplified)
- L89 _public function_ `const TArray<FString>& GetLODNamesFunc() const` — `UFUNCTION()`
- L92 _public member_ `TArray<FString> LODNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L96 _public member_ `bool bShowSeams = true;` — `UPROPERTY(EditAnywhere, DisplayName = "Show Borders", Category = LODPreview)` — Control whether mesh borders are displayed

#### enum `ELODManagerToolActions`  
`enum class ELODManagerToolActions`  
_L107-114_
- reflection: `UENUM()`
- L109 _public enumerator_ `NoAction`
- L111 _public enumerator_ `MoveHiResToLOD0`
- L112 _public enumerator_ `DeleteHiResSourceModel`
- L113 _public enumerator_ `RemoveUnreferencedMaterials`

#### class `ULODManagerActionPropertySet`  
`class ULODManagerActionPropertySet : public UInteractiveToolPropertySet`  
_L119-129_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L124 _public member_ `TWeakObjectPtr<ULODManagerTool> ParentTool;`
- L126 _public function_ `void Initialize(ULODManagerTool* ParentToolIn)`
- L127 _public prototype_ `void PostAction(ELODManagerToolActions Action);`

#### class `ULODManagerHiResSourceModelActions`  
`class ULODManagerHiResSourceModelActions : public ULODManagerActionPropertySet`  
_L133-150_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULODManagerActionPropertySet`
- L139 _public function_ `void MoveToLOD0()` — `UFUNCTION(CallInEditor, Category = HiResSourceModel, meta = (DisplayPriority = 0))` — Move the HiRes Source Model to LOD0
- L146 _public function_ `void Delete()` — `UFUNCTION(CallInEditor, Category = HiResSourceModel, meta = (DisplayPriority = 1))` — Delete the HiRes Source Model

#### class `ULODManagerMaterialActions`  
`class ULODManagerMaterialActions : public ULODManagerActionPropertySet`  
_L154-164_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULODManagerActionPropertySet`
- L160 _public function_ `void CleanMaterials()` — `UFUNCTION(CallInEditor, Category = MaterialSet, meta = (DisplayPriority = 0))` — Discard any Materials that are not referenced by any LOD

#### class `ULODManagerToolChangeTarget`  
`class ULODManagerToolChangeTarget : public UInterface`  
_L176-179_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ILODManagerToolChangeTarget`  
`class ILODManagerToolChangeTarget`  
_L183-188_
- desc: IMeshVertexCommandChangeTarget is an interface which is used to apply a FLODManagerToolChange
- L187 _public prototype_ `virtual void ApplyChange(const UE::Geometry::LODManagerHelper::FLODManagerToolChange* Change, bool bRevert) = 0;`

#### class `ULODManagerTool`  
`class ULODManagerTool : public UMultiSelectionMeshEditingTool, public ILODManagerToolChangeTarget`  
_L194-292_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,ILODManagerToolChangeTarget`
- desc: Mesh Attribute Editor Tool
- L199 _public prototype_ `ULODManagerTool();`
- L201 _public prototype_ `virtual void Setup() override;`
- L202 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L203 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L205 _public function_ `virtual bool HasCancel() const override`
- L206 _public function_ `virtual bool HasAccept() const override`
- L208 _public prototype_ `virtual void RequestAction(ELODManagerToolActions ActionType);`
- L210 _public prototype_ `virtual void ApplyChange(const UE::Geometry::LODManagerHelper::FLODManagerToolChange* Change, bool bRevert) override;`
- L215 _protected member_ `TObjectPtr<ULODManagerLODProperties> LODInfoProperties;` — `UPROPERTY()`
- L218 _protected member_ `TObjectPtr<ULODManagerPreviewLODProperties> LODPreviewProperties;` — `UPROPERTY()`
- L221 _protected member_ `TObjectPtr<ULODManagerHiResSourceModelActions> HiResSourceModelActions;` — `UPROPERTY()`
- L224 _protected member_ `TObjectPtr<ULODManagerMaterialActions> MaterialActions;` — `UPROPERTY()`
- L230 _public prototype_ `void DeleteHiResSourceModel();` — `UFUNCTION()`
- L233 _public prototype_ `void MoveHiResToLOD0();` — `UFUNCTION()`
- L236 _public prototype_ `void RemoveUnreferencedMaterials();` — `UFUNCTION()`
- L255 _protected prototype_ `UStaticMesh* GetSingleStaticMesh();`
- L257 _protected member_ `ELODManagerToolActions PendingAction = ELODManagerToolActions::NoAction;`
- L260 _protected member_ `bool bLODInfoValid = false;`
- L262 _protected prototype_ `void UpdateLODInfo();` — captures the material list and triangle and vertex counts for the current configuration of lods
- L265 _protected member_ `TMap<FString, FLODName> ActiveLODNames;` — maps pretty name in UI to description of the LOD
- L266 _protected prototype_ `void UpdateLODNames();`
- L269 _protected member_ `TObjectPtr<UPreviewMesh> LODPreview;` — `UPROPERTY()`
- L272 _protected member_ `TObjectPtr<UPreviewGeometry> LODPreviewLines;` — `UPROPERTY()`
- L274 _protected member_ `bool bPreviewLODValid = false;`
- L275 _protected prototype_ `void UpdatePreviewLOD();`
- L276 _protected prototype_ `void UpdatePreviewLines(FLODMeshInfo& LODMeshInfo);`
- L277 _protected prototype_ `void ClearPreviewLines();`
- L280 _protected prototype_ `TUniquePtr<ULODManagerTool::FLODMeshInfo> GetLODMeshInfo(const FLODName& LODName);` — returns the requested LOD as a dynamic mesh along with boundary edges.  Has internal cache
- L283 _protected member_ `TUniquePtr< UE::Geometry::LODManagerHelper::FLODManagerToolChange > ActiveChange;` — For undo / redo system with our custom changes.
- L284 _protected prototype_ `void BeginChange(FText TransactionName);`
- L285 _protected prototype_ `void EndChange();`
- L288 _protected member_ `TUniquePtr< UE::Geometry::LODManagerHelper::FProxyLODState> ProxyLODState;` — state information used for undo within the tool
- L291 _protected member_ `TUniquePtr< UE::Geometry::LODManagerHelper::FDynamicMeshLODCache > DynamicMeshCache;` — cache of dynamic mesh representation for each lod, imported and renderdata.

#### struct `ULODManagerTool::FLODName`  
`struct FLODName`  
_L239-245_
- L241 _public member_ `int32 SourceModelIndex = -1;`
- L242 _public member_ `int32 RenderDataIndex = -1;`
- L243 _public member_ `int32 OtherIndex = -1;`
- L244 _public function_ `bool IsValid() const`

#### struct `ULODManagerTool::FLODMeshInfo`  
`struct FLODMeshInfo`  
_L247-251_
- L249 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3> Mesh;`
- L250 _public member_ `TArray<int> BoundaryEdges;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHLODTOOLSET_API`
- L167 _namespace_ `namespace UE`
- L167 _namespace_ `namespace Geometry` (scope `UE`)
- L167 _namespace_ `namespace LODManagerHelper` (scope `UE::Geometry`)
