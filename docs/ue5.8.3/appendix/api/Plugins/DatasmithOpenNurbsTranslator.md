# Plugins / DatasmithOpenNurbsTranslator

- module root: `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithOpenNurbsTranslator`
- headers: 6; symbols: 56
- symbol kinds: class=6, enum=1, enumerator=2, function=8, macro=1, member=9, namespace=2, prototype=26, struct=1
- PrivateDependencyModuleNames: CADInterfaces, CADKernel, CADKernelSurface, CADLibrary, CADTools, DatasmithContent, DatasmithCore, DatasmithTranslator, Engine, MeshDescription, MessageLog, OpenNurbs6, ParametricSurface, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithOpenNurbsTranslator/Private/DatasmithOpenNurbsTranslator.h` (Private)


#### class `FDatasmithOpenNurbsTranslator`  
`class FDatasmithOpenNurbsTranslator : public FParametricSurfaceTranslator`  
_L15-45_
- inherits: `FParametricSurfaceTranslator`
- L18 _public function_ `virtual FName GetFName() const override`
- L21 _public function_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities) override`
- L24 _public prototype_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities) override;`
- L26 _public prototype_ `virtual bool LoadScene(TSharedRef<IDatasmithScene> OutScene) override;`
- L28 _public prototype_ `virtual void UnloadScene() override;`
- L30 _public prototype_ `virtual bool LoadStaticMesh(const TSharedRef<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload) override;`
- L32 _public prototype_ `virtual void SetSceneImportOptions(const TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L34 _public prototype_ `virtual void GetSceneImportOptions(TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L37 _private member_ `TSharedPtr<FOpenNurbsTranslatorImpl> Translator;`
- L41 _private member_ `FDatasmithImportBaseOptions BaseOptions;` — Temporarily store this here for UE-81278 so that we can trigger the recreation of static meshes if we're reimporting with new materials that haven't been assigned yet
- L43 _private member_ `FDatasmithOpenNurbsOptions OpenNurbsOptions;`

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithOpenNurbsTranslator/Private/OpenNurbsBRepConverter.h` (Private)


#### class `IOpenNurbsBRepConverter`  
`class IOpenNurbsBRepConverter`  
_L10-22_
- L13 _public prototype_ `virtual bool AddBRep(ON_Brep& Brep, const ON_3dVector& Offset) = 0;`
- L14 _public function_ `void SetScaleFactor(double NewScaleFactor)`
- L21 _protected member_ `double ScaleFactor = 1;` — mm to mm

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithOpenNurbsTranslator/Private/OpenNurbsBRepToCADKernelConverter.h` (Private)


#### class `FOpenNurbsBRepToCADKernelConverter`  
`class FOpenNurbsBRepToCADKernelConverter : public FCADModelToCADKernelConverterBase, public IOpenNurbsBRepConverter`  
_L31-69_
- inherits: `FCADModelToCADKernelConverterBase,IOpenNurbsBRepConverter`
- L35 _public function_ `FOpenNurbsBRepToCADKernelConverter(const CADLibrary::FImportParameters& InImportParameters, const FDatasmithTessellationOptions& Options) : FCADModelToCADKernelConverterBase(InImportParameters)`
- L41 _public prototype_ `virtual ~FOpenNurbsBRepToCADKernelConverter() = default;`
- L49 _public prototype_ `bool AddBRep(ON_Brep& Brep, const ON_3dVector& Offset);` — Set BRep to tessellate, offsetting it prior to tessellation(used to set mesh pivot at the center of the surface bounding box) @param  Brep	a BRep to tessellate @param  Offset translate BRep by this value before tessellating
- L52 _private prototype_ `TSharedPtr<UE::CADKernel::FTopologicalFace> AddFace(const ON_BrepFace& OpenNurbsFace);`
- L53 _private prototype_ `TSharedPtr<UE::CADKernel::FSurface> AddSurface(ON_NurbsSurface& Surface);`
- L55 _private prototype_ `TSharedPtr<UE::CADKernel::FTopologicalLoop> AddLoop(const ON_BrepLoop& OpenNurbsLoop, TSharedPtr<UE::CADKernel::FSurface>& CarrierSurface, const bool bIsExternal);`
- L61 _private prototype_ `void LinkEdgesLoop(const ON_BrepLoop& OpenNurbsLoop, UE::CADKernel::FTopologicalLoop& Loop);` — Build face's links with its neighbor have to be done after the loop is finalize. This is to avoid to link an edge with another and then to delete it...
- L63 _private prototype_ `TSharedPtr<UE::CADKernel::FTopologicalEdge> AddEdge(const ON_BrepTrim& OpenNurbsTrim, TSharedPtr<UE::CADKernel::FSurface>& CarrierSurface);`
- L67 _protected member_ `TMap<int32, TSharedPtr<UE::CADKernel::FTopologicalEdge>> OpenNurbsTrimId2CADKernelEdge;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace CADKernel` (scope `UE`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithOpenNurbsTranslator/Private/OpenNurbsBRepToTechSoftConverter.h` (Private)


#### class `FOpenNurbsBRepToTechSoftConverter`  
`class FOpenNurbsBRepToTechSoftConverter : public FCADModelToTechSoftConverterBase, public IOpenNurbsBRepConverter`  
_L26-63_
- inherits: `FCADModelToTechSoftConverterBase,IOpenNurbsBRepConverter`
- L35 _public function_ `explicit FOpenNurbsBRepToTechSoftConverter(const CADLibrary::FImportParameters& ImportParameters) : FCADModelToTechSoftConverterBase(ImportParameters)` — Make sure CT is initialized, and a main object is ready. Handle input file unit and an output unit @param InOwner
- L40 _public prototype_ `virtual ~FOpenNurbsBRepToTechSoftConverter() = default;`
- L48 _public prototype_ `virtual bool AddBRep(ON_Brep& Brep, const ON_3dVector& Offset) override;` — Set BRep to tessellate, offsetting it prior to tessellation(used to set mesh pivot at the center of the surface bounding box) @param  Brep	a BRep to tessellate @param  Offset translate Brep by this value before tessellating
- L53 _private member_ `TMap<int32, A3DTopoCoEdge*> OpenNurbsTrimId2TechSoftCoEdge;`
- L55 _private prototype_ `A3DTopoCoEdge* CreateTopoCoEdge(ON_BrepTrim& Trim);`
- L56 _private prototype_ `A3DTopoFace* CreateTopoFace(const ON_BrepFace& OpenNurbsFace);`
- L57 _private prototype_ `A3DTopoLoop* CreateTopoLoop(const ON_BrepLoop& OpenNurbsLoop);`
- L58 _private prototype_ `A3DSurfBase* CreateSurface(const ON_NurbsSurface& OpenNurbsSurface);`
- L59 _private prototype_ `A3DCrvBase* CreateCurve(const ON_NurbsCurve& OpenNurbsCurve);`
- L61 _private prototype_ `void LinkEdgesLoop(const ON_BrepLoop& OpenNurbsLoop);`

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithOpenNurbsTranslator/Public/DatasmithOpenNurbsImportOptions.h` (Public)


#### enum `EDatasmithOpenNurbsBrepTessellatedSource`  
`enum class EDatasmithOpenNurbsBrepTessellatedSource : uint8`  
_L17-24_
- reflection: `UENUM()`
- L20 _public enumerator_ `UseUnrealNurbsTessellation UMETA(DisplayName = "Import as NURBS, Tessellate in Unreal")` — Tessellate all Breps on import
- L23 _public enumerator_ `UseRenderMeshes UMETA(DisplayName = "Import Rhino Meshes and UVs")` — Use render meshes stored in the scene file

#### struct `FDatasmithOpenNurbsOptions`  
`struct FDatasmithOpenNurbsOptions : public FDatasmithTessellationOptions`  
_L28-39_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDatasmithTessellationOptions`
- L33 _public member_ `EDatasmithOpenNurbsBrepTessellatedSource Geometry = EDatasmithOpenNurbsBrepTessellatedSource::UseRenderMeshes;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Geometry & Tessellation Options")`
- L35 _public function_ `uint32 GetHash() const`

#### class `UDatasmithOpenNurbsImportOptions`  
`class UDatasmithOpenNurbsImportOptions : public UDatasmithOptionsBase`  
_L43-55_
- reflection: `UCLASS(BlueprintType, config = EditorPerProjectUserSettings)`
- inherits: `UDatasmithOptionsBase`
- L49 _public member_ `FDatasmithOpenNurbsOptions Options;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Geometry & Tessellation Options", meta = (ShowOnlyInnerProperties))`
- L52 _public prototype_ `bool CanEditChange(const FProperty* InProperty) const override;`

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithOpenNurbsTranslator/Public/DatasmithOpenNurbsTranslatorModule.h` (Public)


#### class `FDatasmithOpenNurbsTranslatorModule`  
`class FDatasmithOpenNurbsTranslatorModule : public IModuleInterface`  
_L14-36_
- inherits: `IModuleInterface`
- desc: Datasmith Translator for .3dm files.
- L18 _public function_ `static FDatasmithOpenNurbsTranslatorModule& Get()`
- L23 _public function_ `static bool IsAvailable()`
- L28 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L32 _public prototype_ `FString GetTempDir() const;`
- L35 _private member_ `FString TempDir;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define DATASMITHOPENNURBSTRANSLATOR_MODULE_NAME TEXT("DatasmithOpenNurbsTranslator")`
