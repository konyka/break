# Plugins / ParametricSurface

- module root: `Plugins/Enterprise/DatasmithCADImporter/Source/ParametricSurface`
- headers: 6; symbols: 74
- symbol kinds: class=6, function=11, macro=1, member=17, namespace=4, prototype=27, struct=3, typedef=5
- PrivateDependencyModuleNames: CADInterfaces, CADKernel, CADLibrary, CADTools, Core, CoreUObject, DatasmithContent, DatasmithTranslator, Engine, Json, MeshDescription, StaticMeshDescription
- PublicDependencyModuleNames: Core

### `Plugins/Enterprise/DatasmithCADImporter/Source/ParametricSurface/Private/TechSoft/TechSoftParametricSurface.h` (Private)


#### class `UTechSoftParametricSurfaceData`  
`class UTechSoftParametricSurfaceData : public UDatasmithParametricSurfaceData`  
_L16-22_
- reflection: `UCLASS(meta = (DisplayName = "TechSoft Parametric Surface Data"))`
- inherits: `UDatasmithParametricSurfaceData`
- L21 _public prototype_ `virtual bool Tessellate(UStaticMesh& StaticMesh, const FDatasmithRetessellationOptions& RetessellateOptions) override;`

### `Plugins/Enterprise/DatasmithCADImporter/Source/ParametricSurface/Public/CADModelConverter.h` (Public)


#### struct `CADLibrary::FCADModelGeometry`  
`struct FCADModelGeometry`  
_L34-37_
- desc: Interface to convert CAD Model (like Alias, Rhino, ...) into the internal CAD Modeler (CADKernel, ...) The derived class must also implement IAddXXXBrepModel according to the CAD model (IAddAliasBrepModel, IAddRhinoBrepModel, ...) The derived class is instantiated for an import session. It processes a subset of the model corresponding to a static mesh actor. The main step of the process is: - InitializeProcess - Fill the modeler database with the subset of the model: - this step is done with AddBRep function of the format interface (IAddAliasBrepModel, IAddRhinoBrepModel) - many bodies can be added to the model to generate only one static mesh actor - RepairTopology if needed - SaveBrep(const FString& FilePath) for retessellate purpose - Tessellate In a second step, the saved file is associated to its UStaticMesh with AddSurfaceDataForMesh function
- L36 _public member_ `int32 Type = -1;`

#### class `CADLibrary::ICADModelConverter`  
`class ICADModelConverter`  
_L39-66_
- L42 _public prototype_ `virtual ~ICADModelConverter() = default;`
- L44 _public prototype_ `virtual void InitializeProcess() = 0;`
- L46 _public prototype_ `virtual bool RepairTopology() = 0;`
- L47 _public prototype_ `virtual bool SaveModel(const TCHAR* OutputPath, TSharedPtr<IDatasmithMeshElement> MeshElement) = 0;`
- L48 _public prototype_ `virtual bool Tessellate(const CADLibrary::FMeshParameters& InMeshParameters, FMeshDescription& OutMeshDescription) = 0;`
- L59 _public prototype_ `virtual void SetImportParameters(double ChordTolerance, double MaxEdgeLength, double NormalTolerance, CADLibrary::EStitchingTechnique StitchingTechnique) = 0;` — Set Import parameters, Tack care to set scale factor before because import parameters will be scale according to scale factor @param ChordTolerance : SAG @param MaxEdgeLength : max length of element's edge @param NormalTolerance : Angle between two adjacent triangles @param StitchingTechnique : CAD topology correction technique @param bScaleUVMap : Scale the UV map to a world unit.
- L61 _public prototype_ `virtual bool AddGeometry(const FCADModelGeometry& Geometry) = 0;`
- L62 _public prototype_ `virtual bool IsSessionValid() = 0;`
- L64 _public prototype_ `virtual void AddSurfaceDataForMesh(const TCHAR* InFilePath, const FMeshParameters& InMeshParameters, const FDatasmithTessellationOptions& InTessellationOptions, FDatasmithMeshElementPayload& OutMeshPayload) const = 0;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace CADLibrary`

### `Plugins/Enterprise/DatasmithCADImporter/Source/ParametricSurface/Public/CADModelToTechSoftConverterBase.h` (Public)


#### class `FCADModelToTechSoftConverterBase`  
`class FCADModelToTechSoftConverterBase : public CADLibrary::ICADModelConverter`  
_L23-58_
- inherits: `CADLibrary::ICADModelConverter`
- L27 _public function_ `FCADModelToTechSoftConverterBase(CADLibrary::FImportParameters InImportParameters) : ImportParameters(InImportParameters)`
- L32 _public prototype_ `virtual void InitializeProcess() override;`
- L34 _public prototype_ `virtual bool RepairTopology() override;`
- L36 _public prototype_ `virtual bool SaveModel(const TCHAR* InFolderPath, TSharedPtr<IDatasmithMeshElement> MeshElement) override;`
- L38 _public prototype_ `virtual bool Tessellate(const CADLibrary::FMeshParameters& InMeshParameters, FMeshDescription& OutMeshDescription) override;`
- L40 _public function_ `virtual void SetImportParameters(double ChordTolerance, double MaxEdgeLength, double NormalTolerance, CADLibrary::EStitchingTechnique StitchingTechnique) override`
- L45 _public function_ `virtual bool IsSessionValid() override`
- L50 _public function_ `virtual bool AddGeometry(const CADLibrary::FCADModelGeometry& Geometry) override`
- L52 _public prototype_ `virtual void AddSurfaceDataForMesh(const TCHAR* InFilePath, const CADLibrary::FMeshParameters& InMeshParameters, const FDatasmithTessellationOptions& InTessellationOptions, FDatasmithMeshElementPayload& OutMeshPayload) const override;`
- L55 _protected member_ `CADLibrary::FImportParameters ImportParameters;`
- L56 _protected member_ `TArray<A3DRiRepresentationItem*> RiRepresentationItems;`
- L57 _protected member_ `CADLibrary::FUniqueTechSoftModelFile ModelFile;`

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef void A3DAsmPartDefinition;`
- L17 _typedef_ `typedef void A3DAsmProductOccurrence;`
- L18 _typedef_ `typedef void A3DEntity;`
- L19 _typedef_ `typedef void A3DRiRepresentationItem;`
- L20 _typedef_ `typedef void A3DTopoBrepData;`

### `Plugins/Enterprise/DatasmithCADImporter/Source/ParametricSurface/Public/DatasmithParametricSurfaceData.h` (Public)


#### struct `FParametricSceneParameters`  
`struct FParametricSceneParameters`  
_L23-36_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `uint8 ModelCoordSys = (uint8)FDatasmithUtils::EModelCoordSystem::ZUp_LeftHanded;` — `UPROPERTY()` — value from FDatasmithUtils::EModelCoordSystem
- L32 _public member_ `float MetricUnit = 0.01f;` — `UPROPERTY()`
- L35 _public member_ `float ScaleFactor = 1.0f;` — `UPROPERTY()`

#### struct `FParametricMeshParameters`  
`struct FParametricMeshParameters`  
_L39-66_
- reflection: `USTRUCT()`
- L44 _public member_ `bool bNeedSwapOrientation = false;` — `UPROPERTY()`
- L47 _public member_ `bool bIsSymmetric = false;` — `UPROPERTY()`
- L50 _public member_ `FVector SymmetricOrigin = FVector::ZeroVector;` — `UPROPERTY()`
- L53 _public member_ `FVector SymmetricNormal = FVector::ZeroVector;` — `UPROPERTY()`
- L55 _public function_ `operator CADLibrary::FMeshParameters()`

#### class `UDatasmithParametricSurfaceData`  
`class UDatasmithParametricSurfaceData : public UDatasmithAdditionalData`  
_L69-119_
- reflection: `UCLASS(meta = (DisplayName = "Datasmith Parametric Surface Data"))`
- inherits: `UDatasmithAdditionalData`
- L75 _public function_ `virtual bool IsValid()`
- L80 _public prototype_ `virtual bool SetFile(const TCHAR* FilePath);`
- L82 _public prototype_ `virtual void SetImportParameters(const CADLibrary::FImportParameters& InSceneParameters);`
- L84 _public prototype_ `virtual void SetMeshParameters(const CADLibrary::FMeshParameters& InMeshParameters);`
- L86 _public function_ `virtual const FDatasmithTessellationOptions& GetLastTessellationOptions() const`
- L91 _public function_ `virtual void SetLastTessellationOptions(const FDatasmithTessellationOptions& InTessellationOptions)`
- L96 _public function_ `virtual bool Tessellate(UStaticMesh& StaticMesh, const FDatasmithRetessellationOptions& RetessellateOptions)`
- L102 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L106 _protected member_ `FParametricSceneParameters SceneParameters;` — `UPROPERTY()`
- L109 _protected member_ `FParametricMeshParameters MeshParameters;` — `UPROPERTY()`
- L112 _protected member_ `FDatasmithTessellationOptions LastTessellationOptions;` — `UPROPERTY(EditAnywhere, Category = NURBS)`
- L115 _protected member_ `TArray<uint8> RawData_DEPRECATED;` — `UPROPERTY()`
- L118 _protected member_ `TArray<uint8> RawData;` — Too costly to serialize as a UPROPERTY, will use custom serialization.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace CADLibrary`

### `Plugins/Enterprise/DatasmithCADImporter/Source/ParametricSurface/Public/ParametricSurfaceModule.h` (Public)


#### class `FParametricSurfaceModule`  
`class FParametricSurfaceModule : public IModuleInterface`  
_L12-21_
- inherits: `IModuleInterface`
- desc: This module exposes additional features for assets containing Parametric data.
- L15 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `static FParametricSurfaceModule& Get();`
- L18 _public prototype_ `static bool IsAvailable();`
- L20 _public prototype_ `static class UDatasmithParametricSurfaceData* CreateParametricSurface();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define PARAMETRICSURFACE_MODULE_NAME TEXT("ParametricSurface")`

### `Plugins/Enterprise/DatasmithCADImporter/Source/ParametricSurface/Public/ParametricSurfaceTranslator.h` (Public)


#### class `FParametricSurfaceTranslator`  
`class FParametricSurfaceTranslator : public IDatasmithTranslator`  
_L18-44_
- inherits: `IDatasmithTranslator`
- L22 _public prototype_ `FParametricSurfaceTranslator();`
- L25 _public prototype_ `virtual void GetSceneImportOptions(TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L26 _public prototype_ `virtual void SetSceneImportOptions(const TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L30 _protected function_ `const FDatasmithTessellationOptions& GetCommonTessellationOptions()`
- L40 _protected function_ `virtual void InitCommonTessellationOptions(FDatasmithTessellationOptions& TessellationOptions)` — Call when the UDatasmithCommonTessellationOptions object is created. This is the unique opportunity for child class to overwrite some values @param TessellationOptions Reference on member of UDatasmithCommonTessellationOptions
- L43 _protected member_ `FDatasmithTessellationOptions CommonTessellationOptions;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace CADLibrary`
- L46 _namespace_ `namespace ParametricSurfaceUtils`
- L48 _prototype_ `bool AddSurfaceData(const TCHAR* MeshFilePath, const CADLibrary::FImportParameters& InSceneParameters, const CADLibrary::FMeshParameters& InMeshParameters, const FDatasmithTessellationOptions& InCommonTessellationOptions, FDatasmithMeshElementPayload& OutMeshPayload);` (scope `ParametricSurfaceUtils`)
