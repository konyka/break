# Plugins / CADKernelSurface

- module root: `Plugins/Enterprise/DatasmithCADImporter/Source/CADKernelSurface`
- headers: 3; symbols: 28
- symbol kinds: class=3, function=10, macro=1, member=6, namespace=2, prototype=6
- PrivateDependencyModuleNames: CADKernel, CADLibrary, CADTools, CoreUObject, DatasmithContent, DatasmithCore, DatasmithTranslator, Engine, MeshDescription, ParametricSurface, StaticMeshDescription
- PublicDependencyModuleNames: Core

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADKernelSurface/Public/CADKernelSurfaceExtension.h` (Public)


#### class `UCADKernelParametricSurfaceData`  
`class UCADKernelParametricSurfaceData : public UDatasmithParametricSurfaceData`  
_L16-26_
- reflection: `UCLASS(meta = (DisplayName = "CADKernel Parametric Surface Data"))`
- inherits: `UDatasmithParametricSurfaceData`
- L21 _public prototype_ `virtual bool Tessellate(UStaticMesh& StaticMesh, const FDatasmithRetessellationOptions& RetessellateOptions) override;`
- L25 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace CADLibrary`
- L36 _namespace_ `namespace CADKernelSurface`
- L38 _prototype_ `void AddSurfaceDataForMesh(const TCHAR* CADKernelArchive, const CADLibrary::FImportParameters& InSceneParameters, const CADLibrary::FMeshParameters&, const FDatasmithTessellationOptions& InTessellationOptions, FDatasmithMeshElementPayload& OutMeshPayload);` (scope `CADKernelSurface`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADKernelSurface/Public/CADKernelSurfaceModule.h` (Public)


#### class `FCADKernelSurfaceModule`  
`class FCADKernelSurfaceModule : public IModuleInterface`  
_L12-19_
- inherits: `IModuleInterface`
- desc: This module exposes additional features for assets containing CADKernel data.
- L15 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `static FCADKernelSurfaceModule& Get();`
- L18 _public prototype_ `static bool IsAvailable();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define CADKERNELSURFACE_MODULE_NAME TEXT("CADKernelSurface")`

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADKernelSurface/Public/CADModelToCADKernelConverterBase.h` (Public)


#### class `FCADModelToCADKernelConverterBase`  
`class FCADModelToCADKernelConverterBase : public CADLibrary::ICADModelConverter`  
_L22-112_
- inherits: `CADLibrary::ICADModelConverter`
- L26 _public function_ `FCADModelToCADKernelConverterBase(const CADLibrary::FImportParameters& InImportParameters) : CADKernelSession(0.01) , ImportParameters(InImportParameters)`
- L32 _public function_ `virtual void InitializeProcess() override`
- L37 _public function_ `virtual bool RepairTopology() override`
- L54 _public function_ `virtual bool SaveModel(const TCHAR* InFolderPath, TSharedPtr<IDatasmithMeshElement> MeshElement) override`
- L67 _public function_ `virtual bool Tessellate(const CADLibrary::FMeshParameters& InMeshParameters, FMeshDescription& OutMeshDescription) override`
- L76 _public function_ `virtual void SetImportParameters(double ChordTolerance, double MaxEdgeLength, double NormalTolerance, CADLibrary::EStitchingTechnique StitchingTechnique) override`
- L81 _public function_ `virtual bool IsSessionValid() override`
- L86 _public function_ `virtual bool AddGeometry(const CADLibrary::FCADModelGeometry& Geometry) override`
- L88 _public function_ `virtual void AddSurfaceDataForMesh(const TCHAR* InFilePath, const CADLibrary::FMeshParameters& InMeshParameters, const FDatasmithTessellationOptions& InTessellationOptions, FDatasmithMeshElementPayload& OutMeshPayload) const override`
- L94 _protected function_ `void SetTolerances(double InGeometryTolerance = 0.01, double InStitchingTolerance = 0.01)`
- L105 _protected member_ `UE::CADKernel::FSession CADKernelSession;`
- L107 _protected member_ `CADLibrary::FImportParameters ImportParameters;`
- L108 _protected member_ `double GeometricTolerance = 0.01;`
- L109 _protected member_ `double SquareTolerance = 0.0001;`
- L110 _protected member_ `double EdgeLengthTolerance = 0.02;`
- L111 _protected member_ `double StitchingTolerance = 0.01;`
