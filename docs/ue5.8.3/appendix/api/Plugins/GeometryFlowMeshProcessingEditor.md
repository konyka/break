# Plugins / GeometryFlowMeshProcessingEditor

- module root: `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessingEditor`
- headers: 4; symbols: 44
- symbol kinds: class=2, enum=3, enumerator=7, function=4, macro=1, member=13, namespace=6, prototype=5, struct=2, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, ModelingOperatorsEditorOnly
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryAlgorithms, GeometryCore, GeometryFlowCore, GeometryFlowMeshProcessing

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessingEditor/Public/GeometryFlowMeshProcessingEditorModule.h` (Public)


#### class `FGeometryFlowMeshProcessingEditorModule`  
`class FGeometryFlowMeshProcessingEditorModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessingEditor/Public/MeshProcessingEditorNodeRegistration.h` (Public)


#### struct `UE::GeometryFlow::FMeshProcessingEditorNodeRegistration`  
`struct FMeshProcessingEditorNodeRegistration`  
_L12-16_
- L15 _public prototype_ `static void RegisterNodes();` — Registration is required for serialization.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace GeometryFlow` (scope `UE`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessingEditor/Public/MeshProcessingNodes/MeshAutoGenerateUVsNode.h` (Public)


#### enum `EGeometryFlow_AutoUVMethod`  
`enum class EGeometryFlow_AutoUVMethod : uint8`  
_L16-21_
- reflection: `UENUM()`
- L18 _public enumerator_ `PatchBuilder = 0`
- L19 _public enumerator_ `UVAtlas = 1`
- L20 _public enumerator_ `XAtlas = 2`

#### struct `FMeshAutoGenerateUVsSettings`  
`struct FMeshAutoGenerateUVsSettings`  
_L25-69_
- reflection: `USTRUCT()`
- L29 _public prototype_ `DECLARE_GEOMETRYFLOW_DATA_TYPE_IDENTIFIER(UE::GeometryFlow::EMeshProcessingDataTypesEditor::MeshAutoGenerateUVsSettings);`
- L32 _public member_ `EGeometryFlow_AutoUVMethod Method = EGeometryFlow_AutoUVMethod::PatchBuilder;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L36 _public member_ `double UVAtlasStretch = 0.5;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")` — UVAtlas parameters
- L39 _public member_ `int UVAtlasNumCharts = 0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L43 _public member_ `int XAtlasMaxIterations = 1;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")` — XAtlas parameters
- L47 _public member_ `int NumInitialPatches = 100;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")` — PatchBuilder parameters
- L50 _public member_ `double CurvatureAlignment = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L53 _public member_ `double MergingThreshold = 1.5;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L56 _public member_ `double MaxAngleDeviationDeg = 45.0;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L59 _public member_ `int SmoothingSteps = 5;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L62 _public member_ `double SmoothingAlpha = 0.25;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L65 _public member_ `bool bAutoPack = false;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`
- L68 _public member_ `int PackingTargetWidth = 512;` — `UPROPERTY(EditAnywhere, Category = "Geometry Flow")`

#### enum `UE::GeometryFlow::EAutoUVMethod`  
`enum class EAutoUVMethod : uint8`  
_L80-85_
- L82 _public enumerator_ `PatchBuilder = 0`
- L83 _public enumerator_ `UVAtlas = 1`
- L84 _public enumerator_ `XAtlas = 2`

#### class `UE::GeometryFlow::FMeshAutoGenerateUVsNode`  
`class FMeshAutoGenerateUVsNode : public TProcessMeshWithSettingsBaseNode<FMeshAutoGenerateUVsSettings>`  
_L100-124_
- inherits: `TProcessMeshWithSettingsBaseNode<FMeshAutoGenerateUVsSettings>`
- L102 _private member_ `static constexpr int Version = 1;`
- L105 _public function_ `FMeshAutoGenerateUVsNode() : TProcessMeshWithSettingsBaseNode<FMeshAutoGenerateUVsSettings>()`
- L109 _public function_ `virtual void ProcessMesh( const FNamedDataMap& DatasIn, const FMeshAutoGenerateUVsSettings& Settings, const FDynamicMesh3& MeshIn, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo) override`
- L119 _public prototype_ `virtual void GenerateUVs(const FDynamicMesh3& MeshIn, const FMeshAutoGenerateUVsSettings& Settings, FDynamicMesh3& MeshOut, TUniquePtr<FEvaluationInfo>& EvaluationInfo);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GEOMETRYFLOWMESHPROCESSINGEDITOR_API`
- L72 _namespace_ `namespace UE`
- L74 _namespace_ `namespace GeometryFlow` (scope `UE`)
- L78 _typedef_ `typedef FMeshAutoGenerateUVsSettings FMeshAutoGenerateUVsSettings;` (scope `UE::GeometryFlow`)
- L86 _function_ `static EAutoUVMethod FromUEnum(const EGeometryFlow_AutoUVMethod& UVsUnwrapType)` (scope `UE::GeometryFlow`)
- L90 _function_ `static EGeometryFlow_AutoUVMethod ToUEnum(const EAutoUVMethod& UVsUnwrapType)` (scope `UE::GeometryFlow`)

### `Plugins/Experimental/GeometryFlow/Source/GeometryFlowMeshProcessingEditor/Public/MeshProcessingNodes/MeshProcessingDataTypesEditor.h` (Public)


#### enum `UE::GeometryFlow::EMeshProcessingDataTypesEditor`  
`enum class EMeshProcessingDataTypesEditor`  
_L12-15_
- L14 _public enumerator_ `MeshAutoGenerateUVsSettings = (int)EDataTypes::BaseMeshProcessingTypesEditor + 1`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace GeometryFlow` (scope `UE`)
