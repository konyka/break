# Plugins / DatasmithCADTranslator

- module root: `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithCADTranslator`
- headers: 4; symbols: 77
- symbol kinds: class=6, delegate=1, function=8, macro=1, member=30, namespace=1, prototype=30
- PrivateDependencyModuleNames: CADInterfaces, CADKernelSurface, CADLibrary, CADTools, DatasmithContent, DatasmithCore, DatasmithDispatcher, DatasmithTranslator, Engine, MeshDescription, ParametricSurface, Sockets
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithCADTranslator/Private/DatasmithCADTranslator.h` (Private)


#### class `FDatasmithCADTranslator`  
`class FDatasmithCADTranslator : public FParametricSurfaceTranslator`  
_L20-40_
- inherits: `FParametricSurfaceTranslator`
- L23 _public function_ `virtual FName GetFName() const override`
- L25 _public prototype_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities) override;`
- L26 _public prototype_ `virtual bool IsSourceSupported(const FDatasmithSceneSource& Source) override;`
- L28 _public prototype_ `virtual bool LoadScene(TSharedRef<IDatasmithScene> OutScene) override;`
- L30 _public prototype_ `virtual void UnloadScene() override;`
- L32 _public prototype_ `virtual bool LoadStaticMesh(const TSharedRef<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload) override;`
- L35 _private member_ `TMap<uint32, FString> CADFileToUEGeomMap;`
- L37 _private member_ `CADLibrary::FImportParameters ImportParameters;`
- L39 _private member_ `TUniquePtr<FDatasmithMeshBuilder> MeshBuilderPtr;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCADTranslator, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCADTranslator, Log, All);`

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithCADTranslator/Public/DatasmithCADTranslatorModule.h` (Public)


#### class `FDatasmithCADTranslatorModule`  
`class FDatasmithCADTranslatorModule : public IModuleInterface`  
_L14-37_
- inherits: `IModuleInterface`
- desc: Datasmith Translator for .wire files.
- L18 _public function_ `static FDatasmithCADTranslatorModule& Get()`
- L23 _public function_ `static bool IsAvailable()`
- L28 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L32 _public prototype_ `FString GetCacheDir() const;`
- L35 _private member_ `FString TempDir;`
- L36 _private member_ `FString CacheDir;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define DATASMITHCADTRANSLATOR_MODULE_NAME TEXT("DatasmithCADTranslator")`

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithCADTranslator/Public/DatasmithMeshBuilder.h` (Public)


#### class `FDatasmithMeshBuilder`  
`class FDatasmithMeshBuilder`  
_L15-42_
- L18 _public prototype_ `FDatasmithMeshBuilder(TMap<uint32, FString>& InCADFileToMeshFileMap, const FString& InCachePath, const CADLibrary::FImportParameters& InImportParameters);`
- L20 _public function_ `FDatasmithMeshBuilder(TArray<CADLibrary::FBodyMesh>& InBodyMeshSet, const CADLibrary::FImportParameters& InImportParameters) : ImportParameters(InImportParameters)`
- L31 _public prototype_ `TOptional<FMeshDescription> GetMeshDescription(TSharedRef<IDatasmithMeshElement> OutMeshElement, CADLibrary::FMeshParameters& OutMeshParameters);`
- L34 _protected member_ `FString CachePath;`
- L36 _protected prototype_ `void LoadMeshFiles(TMap<uint32, FString>& CADFileToMeshFile);`
- L38 _protected member_ `TArray<TArray<CADLibrary::FBodyMesh>> BodyMeshes;`
- L39 _protected member_ `TMap<FCadUuid, CADLibrary::FBodyMesh*> MeshActorNameToBodyMesh;`
- L41 _protected member_ `CADLibrary::FImportParameters ImportParameters;`

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithCADTranslator/Public/DatasmithSceneGraphBuilder.h` (Public)


#### class `FActorData`  
`class FActorData`  
_L26-52_
- L29 _public function_ `FActorData(const TCHAR* NodeUuid, const FActorData& ParentData) : Uuid(NodeUuid) , Inheritance(ParentData.Inheritance) , MaterialUId(ParentData.MaterialUId) , ColorUId(ParentData.ColorUId)`
- L37 _public function_ `FActorData(const TCHAR* NodeUuid) : Uuid(NodeUuid) , Inheritance(CADLibrary::ECADGraphicPropertyInheritance::Unset) , MaterialUId(0) , ColorUId(0)`
- L45 _public member_ `const TCHAR* Uuid;`
- L46 _public member_ `CADLibrary::ECADGraphicPropertyInheritance Inheritance = CADLibrary::ECADGraphicPropertyInheritance::Unset;`
- L47 _public member_ `FMaterialUId MaterialUId;`
- L48 _public member_ `FMaterialUId ColorUId;`
- L50 _public member_ `uint32 SceneGraphId = 0;`
- L51 _public member_ `TArray<FCadId> OverridenChildren;`

#### class `FDatasmithSceneBaseGraphBuilder`  
`class FDatasmithSceneBaseGraphBuilder`  
_L54-107_
- L57 _public prototype_ `FDatasmithSceneBaseGraphBuilder( CADLibrary::FArchiveSceneGraph* InSceneGraph, const FString& InCachePath, TSharedRef<IDatasmithScene> InScene, const FDatasmithSceneSource& InSource, const CADLibrary::FImportParameters& InImportParameters);`
- L64 _public function_ `virtual ~FDatasmithSceneBaseGraphBuilder()`
- L66 _public prototype_ `virtual bool Build();`
- L69 _protected prototype_ `TSharedPtr<IDatasmithActorElement> BuildInstance(FCadId InstanceId, const FActorData& ParentData);`
- L70 _protected prototype_ `TSharedPtr<IDatasmithActorElement> BuildReference(CADLibrary::FArchiveReference& Reference, const FActorData& ParentData);`
- L71 _protected prototype_ `TSharedPtr<IDatasmithActorElement> BuildBody(FCadId BodyId, const FActorData& ParentData);`
- L73 _protected prototype_ `void OverrideInstance(CADLibrary::FArchiveOverrideOccurrence* OverrideOccurrence, CADLibrary::FArchiveInstance& Instance, FActorData& InstanceData);`
- L75 _protected prototype_ `void AddMetaData(TSharedPtr<IDatasmithActorElement> ActorElement, const CADLibrary::FArchiveCADObject& Instance, const CADLibrary::FArchiveCADObject& Reference);`
- L76 _protected prototype_ `void AddChildren(TSharedPtr<IDatasmithActorElement> Actor, const CADLibrary::FArchiveReference& Reference, const FActorData& ParentData);`
- L77 _protected prototype_ `bool DoesActorHaveChildrenOrIsAStaticMesh(const TSharedPtr< IDatasmithActorElement >& ActorElement);`
- L79 _protected prototype_ `TSharedPtr<IDatasmithUEPbrMaterialElement> GetDefaultMaterial();`
- L80 _protected prototype_ `TSharedPtr<IDatasmithMaterialIDElement> FindOrAddMaterial(FMaterialUId MaterialUuid);`
- L82 _protected prototype_ `TSharedPtr<IDatasmithActorElement> CreateActor(const TCHAR* ActorUUID, const TCHAR* ActorLabel);`
- L83 _protected prototype_ `virtual TSharedPtr<IDatasmithMeshElement> FindOrAddMeshElement(CADLibrary::FArchiveBody& Body);`
- L85 _protected prototype_ `CADLibrary::FArchiveSceneGraph* FindSceneGraphArchive(const CADLibrary::FFileDescriptor& File, uint32& FileHash) const;`
- L88 _protected member_ `CADLibrary::FArchiveSceneGraph* SceneGraph;`
- L89 _protected member_ `const FString& CachePath;`
- L90 _protected member_ `TSharedRef<IDatasmithScene> DatasmithScene;`
- L91 _protected member_ `const CADLibrary::FImportParameters& ImportParameters;`
- L92 _protected member_ `const uint32 ImportParametersHash;`
- L93 _protected member_ `CADLibrary::FFileDescriptor RootFileDescription;`
- L95 _protected member_ `TArray<CADLibrary::FArchiveSceneGraph> ArchiveMockUps;`
- L96 _protected member_ `TMap<uint32, CADLibrary::FArchiveSceneGraph*> CADFileToSceneGraphArchive;`
- L98 _protected member_ `TMap<FCadUuid, TSharedPtr< IDatasmithMeshElement>> BodyUuidToMeshElement;`
- L100 _protected member_ `TMap<FMaterialUId, TSharedPtr< IDatasmithUEPbrMaterialElement>> MaterialUuidMap;`
- L101 _protected member_ `TSharedPtr<IDatasmithUEPbrMaterialElement> DefaultMaterial;`
- L103 _protected member_ `TMap<FMaterialUId, CADLibrary::FArchiveColor> ColorUIdToColorArchive;`
- L104 _protected member_ `TMap<FMaterialUId, CADLibrary::FArchiveMaterial> MaterialUIdToMaterialArchive;`
- L106 _protected member_ `TArray<uint32> AncestorSceneGraphHash;`

#### class `FDatasmithSceneGraphBuilder`  
`class FDatasmithSceneGraphBuilder : public FDatasmithSceneBaseGraphBuilder`  
_L109-129_
- inherits: `FDatasmithSceneBaseGraphBuilder`
- L112 _public prototype_ `FDatasmithSceneGraphBuilder( TMap<uint32, FString>& InCADFileToUE4FileMap, const FString& InCachePath, TSharedRef<IDatasmithScene> InScene, const FDatasmithSceneSource& InSource, const CADLibrary::FImportParameters& InImportParameters);`
- L119 _public function_ `virtual ~FDatasmithSceneGraphBuilder()`
- L121 _public prototype_ `virtual bool Build() override;`
- L123 _public prototype_ `void LoadSceneGraphDescriptionFiles();`
- L125 _public prototype_ `void FillAnchorActor(const TSharedRef< IDatasmithActorElement >& ActorElement, const FString& CleanFilenameOfCADFile);`
- L128 _protected member_ `TMap<uint32, FString>& CADFileToSceneGraphDescriptionFile;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace CADLibrary`
