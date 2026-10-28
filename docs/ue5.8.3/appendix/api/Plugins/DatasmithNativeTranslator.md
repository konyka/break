# Plugins / DatasmithNativeTranslator

- module root: `Plugins/Enterprise/DatasmithImporter/Source/DatasmithNativeTranslator`
- headers: 2; symbols: 15
- symbol kinds: class=2, function=3, macro=1, prototype=9
- PrivateDependencyModuleNames: DatasmithCore, DatasmithTranslator, Engine, MeshDescription, RawMesh, StaticMeshDescription
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithNativeTranslator/Public/DatasmithNativeTranslator.h` (Public)


#### class `FDatasmithNativeTranslator`  
`class FDatasmithNativeTranslator : public IDatasmithTranslator`  
_L9-30_
- inherits: `IDatasmithTranslator`
- L12 _public function_ `virtual FName GetFName() const override`
- L14 _public prototype_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities) override;`
- L16 _public prototype_ `virtual bool LoadScene(TSharedRef<IDatasmithScene> OutScene) override;`
- L18 _public prototype_ `virtual bool LoadStaticMesh(const TSharedRef<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload) override;`
- L20 _public prototype_ `virtual bool LoadLevelSequence(const TSharedRef<IDatasmithLevelSequenceElement> LevelSequenceElement, FDatasmithLevelSequencePayload& OutLevelSequencePayload) override;`
- L24 _public prototype_ `virtual bool LoadCloth(const TSharedRef<IDatasmithClothElement> ClothElement, FDatasmithClothElementPayload& OutClothPayload) override;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L28 _protected prototype_ `static FString ResolveFilePath(const FString& FilePath, const TArray<FString>& ResourcePaths);`
- L29 _protected prototype_ `static void ResolveSceneFilePaths(TSharedRef<IDatasmithScene> Scene, const TArray<FString>& ResourcePaths);`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithNativeTranslator/Public/DatasmithNativeTranslatorModule.h` (Public)


#### class `FDatasmithNativeTranslatorModule`  
`class FDatasmithNativeTranslatorModule : public IModuleInterface`  
_L14-31_
- inherits: `IModuleInterface`
- desc: Datasmith Translator for .udatasmith files.
- L18 _public function_ `static FDatasmithNativeTranslatorModule& Get()`
- L23 _public function_ `static bool IsAvailable()`
- L28 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define DATASMITHNATIVETRANSLATOR_MODULE_NAME TEXT("DatasmithNativeTranslator")`
