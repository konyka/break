# Plugins / DatasmithExternalSource

- module root: `Plugins/Enterprise/DatasmithImporter/Source/DatasmithExternalSource`
- headers: 5; symbols: 47
- symbol kinds: class=5, delegate=1, function=9, macro=1, member=4, namespace=8, prototype=19
- PrivateDependencyModuleNames: DatasmithCore, DatasmithTranslator, DesktopPlatform, DirectLinkExtensionEditor, Projects, Slate, UnrealEd
- PublicDependencyModuleNames: Core, DatasmithNativeTranslator, DirectLinkExtension, ExternalSource

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithExternalSource/Private/DatasmithDirectLinkExternalSource.h` (Private)


#### class `UE::DatasmithImporter::FDatasmithDirectLinkExternalSource`  
`class FDatasmithDirectLinkExternalSource : public FDirectLinkExternalSource`  
_L14-43_
- inherits: `FDirectLinkExternalSource`
- L17 _public function_ `explicit FDatasmithDirectLinkExternalSource(const FSourceUri& InSourceUri) : FDirectLinkExternalSource(InSourceUri)`
- L21 _public prototype_ `virtual ~FDatasmithDirectLinkExternalSource();`
- L24 _public prototype_ `virtual TSharedPtr<IDatasmithScene> GetDatasmithScene() const;` — FExternalSource interface begin
- L25 _public prototype_ `virtual FString GetFallbackFilepath() const override;`
- L29 _public function_ `virtual bool CanOpenNewConnection(const DirectLink::IConnectionRequestHandler::FSourceInformation& Source) override` — DirectLink::IConnectionRequestHandler interface begin
- L34 _protected prototype_ `virtual TSharedPtr<class DirectLink::ISceneReceiver> GetSceneReceiverInternal(const DirectLink::IConnectionRequestHandler::FSourceInformation& Source) override;` — UE::DatasmithImporter::FDirectLinkExternalSource interface begin
- L42 _private member_ `TSharedPtr<FDatasmithSceneReceiver> SceneReceiver;` — The SceneReceiver used to parse the DirectLink snapshot into a DatasmithScene.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithExternalSource/Private/DatasmithDirectLinkTranslator.h` (Private)


#### class `UE::DatasmithImporter::FDatasmithDirectLinkTranslator`  
`class FDatasmithDirectLinkTranslator : public FDatasmithNativeTranslator`  
_L16-24_
- inherits: `FDatasmithNativeTranslator`
- desc: Due to the way the Editor's import/reimport utilities currently work, we must provide a path to an existing file. The FDatasmithDirecTLinkTranslator is a workaround used to be directed to the DatasmithImportFactory when the source file has a ".directlink" extention. In that case, the actual scene is loaded using the FExternalSource generated from the directlink URI.
- L19 _public function_ `virtual FName GetFName() const override`
- L21 _public prototype_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities) override;`
- L23 _public prototype_ `virtual bool LoadScene(TSharedRef<IDatasmithScene> OutScene) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithExternalSource/Private/DatasmithFileExternalSource.h` (Private)


#### class `UE::DatasmithImporter::FDatasmithFileExternalSource`  
`class FDatasmithFileExternalSource : public FExternalSource`  
_L16-44_
- inherits: `FExternalSource`
- L19 _public function_ `explicit FDatasmithFileExternalSource(const FSourceUri& InSourceUri) : FExternalSource(InSourceUri)`
- L26 _public prototype_ `virtual FString GetSourceName() const override;` — UFileExternalSource interface begin
- L27 _public prototype_ `virtual bool IsAvailable() const override;`
- L28 _public prototype_ `virtual bool IsOutOfSync() const override;`
- L29 _public function_ `virtual FMD5Hash GetSourceHash() const override`
- L30 _public prototype_ `virtual FExternalSourceCapabilities GetCapabilities() const override;`
- L31 _public function_ `virtual TSharedPtr<IDatasmithScene> GetDatasmithScene() const override`
- L32 _public prototype_ `virtual FString GetFallbackFilepath() const override;`
- L34 _protected prototype_ `virtual TSharedPtr<IDatasmithScene> LoadImpl();`
- L35 _protected function_ `virtual bool StartAsyncLoad()`
- L39 _private member_ `FString FilePath;`
- L41 _private member_ `FMD5Hash CachedHash;`
- L43 _private member_ `TSharedPtr<IDatasmithScene> DatasmithScene;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithFileExternalSource, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithFileExternalSource, Log, All);`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithExternalSource/Private/DatasmithFileUriResolver.h` (Private)


#### class `UE::DatasmithImporter::FDatasmithFileUriResolver`  
`class FDatasmithFileUriResolver : public IUriResolver`  
_L10-21_
- inherits: `IUriResolver`
- L14 _public prototype_ `virtual TSharedPtr<FExternalSource> GetOrCreateExternalSource(const FSourceUri& URI) const override;` — IUriResolver interface begin
- L15 _public prototype_ `virtual bool CanResolveUri(const FSourceUri& URI) const override;`
- L16 _public prototype_ `virtual FName GetScheme() const override;`
- L18 _public prototype_ `virtual TSharedPtr<FExternalSource> BrowseExternalSource(const FSourceUri& DefaultUri) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithExternalSource/Public/DatasmithExternalSourceModule.h` (Public)


#### class `FDatasmithExternalSourceModule`  
`class FDatasmithExternalSourceModule : public IModuleInterface`  
_L14-31_
- inherits: `IModuleInterface`
- desc: Module adding support for Datasmith DirectLink and file external sources.
- L18 _public function_ `static FDatasmithExternalSourceModule& Get()`
- L23 _public function_ `static bool IsAvailable()`
- L28 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define DATASMITHEXTERNALSOURCE_MODULE_NAME TEXT("DatasmithExternalSource")`
