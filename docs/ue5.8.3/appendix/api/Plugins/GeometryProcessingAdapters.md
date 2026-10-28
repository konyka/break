# Plugins / GeometryProcessingAdapters

- module root: `Plugins/Experimental/MeshModelingToolsetExp/Source/GeometryProcessingAdapters`
- headers: 3; symbols: 21
- symbol kinds: class=3, macro=2, member=2, namespace=6, prototype=8
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, MaterialUtilities, MeshBuilder, MeshReductionInterface, MeshUtilities, RenderCore
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryAlgorithms, GeometryCore, GeometryProcessingInterfaces, InteractiveToolsFramework, MeshConversion, MeshDescription, MeshUtilitiesCommon, ModelingComponents, ModelingComponentsEditorOnly, ModelingOperators, ModelingOperatorsEditorOnly, StaticMeshDescription

### `Plugins/Experimental/MeshModelingToolsetExp/Source/GeometryProcessingAdapters/Public/GeometryProcessing/ApproximateActorsImpl.h` (Public)


#### class `UE::Geometry::FApproximateActorsImpl`  
`class FApproximateActorsImpl : public IGeometryProcessing_ApproximateActors`  
_L22-41_
- inherits: `IGeometryProcessing_ApproximateActors`
- desc: Implementation of IGeometryProcessing_ApproximateActors
- L25 _public prototype_ `virtual FOptions ConstructOptions(const FMeshApproximationSettings& MeshApproximationSettings) override;`
- L27 _public prototype_ `virtual void ApproximateActors(const FInput& Input, const FOptions& Options, FResults& ResultsOut) override;`
- L33 _protected prototype_ `virtual void GenerateApproximationForActorSet(const FInput& Input, const FOptions& Options, FResults& ResultsOut);`
- L35 _protected prototype_ `virtual UStaticMesh* EmitGeneratedMeshAsset( const FOptions& Options, FResults& ResultsOut, FDynamicMesh3* FinalMesh, UMaterialInterface* Material = nullptr, FDynamicMesh3* DebugMesh = nullptr);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYPROCESSINGADAPTERS_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/MeshModelingToolsetExp/Source/GeometryProcessingAdapters/Public/GeometryProcessing/MeshAutoUVImpl.h` (Public)


#### class `UE::Geometry::FMeshAutoUVImpl`  
`class FMeshAutoUVImpl : public IGeometryProcessing_MeshAutoUV`  
_L19-25_
- inherits: `IGeometryProcessing_MeshAutoUV`
- desc: Implementation of IGeometryProcessing_MeshAutoUV
- L22 _public prototype_ `virtual FOptions ConstructDefaultOptions() override;`
- L24 _public prototype_ `virtual void GenerateUVs(FMeshDescription& InOutMesh, const FOptions& Options, FResults& ResultsOut) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GEOMETRYPROCESSINGADAPTERS_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/MeshModelingToolsetExp/Source/GeometryProcessingAdapters/Public/GeometryProcessingAdaptersModule.h` (Public)


#### class `FGeometryProcessingAdaptersModule`  
`class FGeometryProcessingAdaptersModule : public IModuleInterface`  
_L14-26_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _protected member_ `TSharedPtr<UE::Geometry::FApproximateActorsImpl> ApproximateActors;`
- L25 _protected member_ `TSharedPtr<UE::Geometry::FMeshAutoUVImpl> MeshAutoUV;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Geometry` (scope `UE`)
