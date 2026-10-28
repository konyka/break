# Plugins / DatasmithPLMXMLTranslator

- module root: `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithPLMXMLTranslator`
- headers: 3; symbols: 25
- symbol kinds: class=3, function=3, member=5, namespace=1, prototype=12, typedef=1
- PrivateDependencyModuleNames: CADInterfaces, CADKernelSurface, CADLibrary, CADTools, DatasmithCADTranslator, DatasmithContent, DatasmithCore, DatasmithDispatcher, DatasmithTranslator, Engine, MeshDescription, MessageLog, ParametricSurface, UnrealEd, XmlParser
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithPLMXMLTranslator/Private/DatasmithPlmXmlImporter.h` (Private)


#### class `FDatasmithPlmXmlImporter`  
`class FDatasmithPlmXmlImporter : FNoncopyable`  
_L22-37_
- inherits: `FNoncopyable`
- L25 _public prototype_ `explicit FDatasmithPlmXmlImporter(TSharedRef<IDatasmithScene> OutScene);`
- L26 _public prototype_ `~FDatasmithPlmXmlImporter();`
- L28 _public prototype_ `bool OpenFile(const FString& InFilePath, const FDatasmithSceneSource& Source, FDatasmithTessellationOptions& TessellationOptions);`
- L29 _public prototype_ `bool LoadStaticMesh(const TSharedRef<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload);`
- L31 _public prototype_ `void UnloadScene();`
- L33 _private member_ `TSharedRef<IDatasmithScene> DatasmithScene;`
- L35 _private member_ `TUniquePtr<PlmXml::FPlmXmlMeshLoader> MeshLoader;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace PlmXml`
- L19 _typedef_ `using FPlmXmlMeshLoader = FPlmXmlMeshLoaderWithDatasmithDispatcher;` (scope `PlmXml`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithPLMXMLTranslator/Private/DatasmithPlmXmlTranslator.h` (Private)


#### class `FDatasmithPlmXmlTranslator`  
`class FDatasmithPlmXmlTranslator : public IDatasmithTranslator`  
_L15-35_
- inherits: `IDatasmithTranslator`
- L20 _public function_ `virtual FName GetFName() const override` — IDatasmithTranslator interface
- L21 _public prototype_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities) override;`
- L22 _public prototype_ `virtual bool LoadScene(TSharedRef<IDatasmithScene> OutScene) override;`
- L23 _public prototype_ `virtual void UnloadScene() override;`
- L25 _public prototype_ `virtual bool LoadStaticMesh(const TSharedRef<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload) override;`
- L27 _public prototype_ `virtual void GetSceneImportOptions(TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L28 _public prototype_ `virtual void SetSceneImportOptions(const TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L29 _public prototype_ `virtual bool IsSourceSupported(const FDatasmithSceneSource& Source) override;`
- L33 _private member_ `TUniquePtr<FDatasmithPlmXmlImporter> Importer;`
- L34 _private member_ `FDatasmithTessellationOptions CommonTessellationOptions;`

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithPLMXMLTranslator/Public/DatasmithPlmXmlTranslatorModule.h` (Public)


#### class `IDatasmithPlmXmlTranslatorModule`  
`class IDatasmithPlmXmlTranslatorModule : public IModuleInterface`  
_L8-32_
- inherits: `IModuleInterface`
- L11 _public member_ `static const TCHAR* ModuleName;`
- L18 _public function_ `static IDatasmithPlmXmlTranslatorModule& Get()` — Singleton-like access to the module @return Returns module singleton instance, loading it on demand if needed
- L28 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready. It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
