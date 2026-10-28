# Plugins / DatasmithTranslator

- module root: `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator`
- headers: 15; symbols: 185
- symbol kinds: class=13, function=32, macro=1, member=40, namespace=3, prototype=88, struct=8
- PrivateDependencyModuleNames: Engine, MeshDescription, RawMesh, StaticMeshDescription
- PublicDependencyModuleNames: Core, CoreUObject, DatasmithContent, DatasmithCore, XmlParser

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Private/ReferenceMaterials/DatasmithC4DImporterMaterialSelector.h` (Private)


#### class `FDatasmithC4DImporterMaterialSelector`  
`class FDatasmithC4DImporterMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L13-26_
- inherits: `FDatasmithReferenceMaterialSelector`
- L16 _public prototype_ `FDatasmithC4DImporterMaterialSelector();`
- L17 _public prototype_ `virtual ~FDatasmithC4DImporterMaterialSelector() = default;`
- L19 _public prototype_ `virtual bool IsValid() const override;`
- L20 _public prototype_ `virtual const FDatasmithReferenceMaterial& GetReferenceMaterial( const TSharedPtr< IDatasmithMaterialInstanceElement >& ) const override;`
- L21 _public prototype_ `virtual void FinalizeMaterialInstance(const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial, UMaterialInstanceConstant* MaterialInstance) const override;`
- L25 _private member_ `FDatasmithReferenceMaterial ReferenceMaterial;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Private/ReferenceMaterials/DatasmithCityEngineMaterialSelector.h` (Private)


#### class `FDatasmithCityEngineMaterialSelector`  
`class FDatasmithCityEngineMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L12-27_
- inherits: `FDatasmithReferenceMaterialSelector`
- L15 _public prototype_ `FDatasmithCityEngineMaterialSelector();`
- L17 _public prototype_ `virtual bool IsValid() const override;`
- L18 _public prototype_ `virtual const FDatasmithReferenceMaterial& GetReferenceMaterial( const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial ) const override;`
- L21 _protected prototype_ `bool IsValidMaterialType( EDatasmithReferenceMaterialType InType ) const;`
- L24 _private member_ `FDatasmithReferenceMaterial ReferenceMaterial;`
- L25 _private member_ `FDatasmithReferenceMaterial ReferenceMaterialTransparent;`
- L26 _private member_ `FDatasmithReferenceMaterial ReferenceMaterialTransparentSimple;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Private/ReferenceMaterials/DatasmithRevitMaterialSelector.h` (Private)


#### class `FDatasmithRevitMaterialSelector`  
`class FDatasmithRevitMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L12-25_
- inherits: `FDatasmithReferenceMaterialSelector`
- L15 _public prototype_ `FDatasmithRevitMaterialSelector();`
- L16 _public prototype_ `virtual ~FDatasmithRevitMaterialSelector() = default;`
- L18 _public prototype_ `virtual bool IsValid() const override;`
- L19 _public prototype_ `virtual const FDatasmithReferenceMaterial& GetReferenceMaterial( const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial ) const override;`
- L20 _public prototype_ `virtual void FinalizeMaterialInstance(const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial, UMaterialInstanceConstant* MaterialInstance) const override;`
- L23 _private member_ `FDatasmithReferenceMaterial ReferenceMaterial;`
- L24 _private member_ `FDatasmithReferenceMaterial ReferenceMaterialDecal;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Private/ReferenceMaterials/DatasmithSketchupMaterialSelector.h` (Private)


#### class `FDatasmithSketchUpMaterialSelector`  
`class FDatasmithSketchUpMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L12-24_
- inherits: `FDatasmithReferenceMaterialSelector`
- L15 _public prototype_ `FDatasmithSketchUpMaterialSelector();`
- L16 _public prototype_ `virtual ~FDatasmithSketchUpMaterialSelector() = default;`
- L18 _public prototype_ `virtual bool IsValid() const override;`
- L19 _public prototype_ `virtual const FDatasmithReferenceMaterial& GetReferenceMaterial( const TSharedPtr< IDatasmithMaterialInstanceElement >& ) const override;`
- L20 _public prototype_ `virtual void FinalizeMaterialInstance(const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial, UMaterialInstanceConstant* MaterialInstance) const override;`
- L23 _private member_ `FDatasmithReferenceMaterial ReferenceMaterial;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Private/ReferenceMaterials/DatasmithStdMaterialSelector.h` (Private)


#### class `FDatasmithStdMaterialSelector`  
`class FDatasmithStdMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L12-26_
- inherits: `FDatasmithReferenceMaterialSelector`
- L15 _public prototype_ `FDatasmithStdMaterialSelector();`
- L16 _public prototype_ `virtual ~FDatasmithStdMaterialSelector() = default;`
- L18 _public prototype_ `virtual bool IsValid() const override;`
- L19 _public prototype_ `virtual const FDatasmithReferenceMaterial& GetReferenceMaterial( const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial ) const override;`
- L20 _public function_ `virtual void FinalizeMaterialInstance(const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial, UMaterialInstanceConstant* MaterialInstance) const override`
- L23 _private member_ `FDatasmithReferenceMaterial ReferenceMaterialOpaque;`
- L24 _private member_ `FDatasmithReferenceMaterial ReferenceMaterialTranslucent;`
- L25 _private member_ `FDatasmithReferenceMaterial ReferenceMaterialEmissive;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Public/DatasmithPayload.h` (Public)


#### struct `FDatasmithPayload`  
`struct FDatasmithPayload`  
_L9-12_
- L11 _public member_ `TArray<class UDatasmithAdditionalData*> AdditionalData;`

#### struct `FDatasmithMeshElementPayload`  
`struct FDatasmithMeshElementPayload : public FDatasmithPayload`  
_L15-20_
- inherits: `FDatasmithPayload`
- L17 _public member_ `TArray<FMeshDescription> LodMeshes;`
- L18 _public member_ `FMeshDescription CollisionMesh;`
- L19 _public member_ `TArray<FVector3f> CollisionPointCloud;` — compatibility, favor the CollisionMesh member

#### struct `FDatasmithClothElementPayload`  
`struct UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") FDatasmithClothElementPayload : public FDatasmithPayload`  
_L26-31_
- inherits: `FDatasmithPayload`
- desc: Describes a Cloth element payload, which is the actual data to be imported.
- L29 _public member_ `FDatasmithCloth Cloth;`

#### struct `FDatasmithLevelSequencePayload`  
`struct FDatasmithLevelSequencePayload : public FDatasmithPayload`  
_L34-37_
- inherits: `FDatasmithPayload`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Public/DatasmithSceneSource.h` (Public)


#### class `FDatasmithSceneSource`  
`class FDatasmithSceneSource`  
_L12-58_
- desc: Describe a source that can be processed by Datasmith to generate a scene.
- L19 _public prototype_ `void SetSourceFile(const FString& InFilePath);` — Set the path of the source @param InFilename New file path
- L25 _public function_ `const FString& GetSourceFile() const` — Get the file path for this source @return The source path
- L31 _public function_ `const FString& GetSourceFileExtension() const` — Get the source file extension @return const FString&
- L38 _public prototype_ `void SetSceneName(const FString& InSceneName);` — Set a custom name for this scene. This overrides the default name deduced form the source file @param InSceneName New name
- L43 _public prototype_ `const FString& GetSceneName() const ;` — @return the scene name
- L48 _private member_ `FString FilePath;` — source path (can be relative)
- L51 _private member_ `FString FileExtension;` — Extracted from the source file path
- L54 _private member_ `FString SceneDeducedName;` — Default name when not overriden
- L57 _private member_ `FString SceneOverrideName;` — Explicit name (overrides deduced name)

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Public/DatasmithTranslatableSource.h` (Public)


#### class `FDatasmithSceneGuard`  
`class FDatasmithSceneGuard`  
_L16-25_
- desc: Scopes a translator's loading lifecycle.
- L19 _public prototype_ `FDatasmithSceneGuard(const TSharedPtr<IDatasmithTranslator>& Translator, const TSharedRef<IDatasmithScene>& Scene, bool& bOutLoadOk);`
- L21 _public prototype_ `~FDatasmithSceneGuard();`
- L24 _private member_ `TSharedPtr<IDatasmithTranslator> Translator;`

#### struct `FDatasmithTranslatableSceneSource`  
`struct FDatasmithTranslatableSceneSource`  
_L31-48_
- desc: Wrap a source with an adapted translator. This scopes the lifecycle of a translator,
- L33 _public prototype_ `FDatasmithTranslatableSceneSource(const FDatasmithSceneSource& Source);`
- L34 _public prototype_ `~FDatasmithTranslatableSceneSource();`
- L36 _public prototype_ `bool IsTranslatable() const;`
- L38 _public prototype_ `bool Translate(TSharedRef<IDatasmithScene> Scene);`
- L40 _public prototype_ `TSharedPtr<IDatasmithTranslator> GetTranslator() const;`
- L44 _private member_ `TSharedPtr<IDatasmithTranslator> Translator;` — Translator currently in use (null when not importing)
- L47 _private member_ `TUniquePtr<FDatasmithSceneGuard> SceneGuard;` — internal helper to release scene

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Public/DatasmithTranslator.h` (Public)


#### struct `FFileFormatInfo`  
`struct FFileFormatInfo`  
_L20-27_
- L22 _public function_ `FFileFormatInfo(const TCHAR* InExtension, const TCHAR* InDescription) :Extension(InExtension), Description(InDescription)`
- L25 _public member_ `FString Extension;`
- L26 _public member_ `FString Description;`

#### struct `FDatasmithTranslatorCapabilities`  
`struct FDatasmithTranslatorCapabilities`  
_L33-38_
- desc: Description of Translator capabilities
- L35 _public member_ `bool bIsEnabled = true;`
- L36 _public member_ `bool bParallelLoadStaticMeshSupported = false;`
- L37 _public member_ `TArray<FFileFormatInfo> SupportedFileFormats;`

#### class `IDatasmithTranslator`  
`class IDatasmithTranslator`  
_L44-142_
- desc: Generic Scene exploration and realization API
- L47 _public prototype_ `virtual ~IDatasmithTranslator() = default;`
- L49 _public prototype_ `virtual FName GetFName() const = 0;`
- L55 _public function_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities)` — Called to initialize this Translator instance @param OutCapabilities	Declared capabilities for this Translator
- L63 _public function_ `virtual bool IsSourceSupported(const FDatasmithSceneSource& Source)` — Additional validation step to ensure the given file is supported (Optional) @param Source	Candidate Source @returns			True if the given source is supported by this Translator
- L70 _public function_ `void SetSource(const FDatasmithSceneSource& Source)` — Beginning of a translator instance lifecycle: setup of the source @param Source    Source of the scene to translate
- L75 _public function_ `const FDatasmithSceneSource& GetSource() const` — @return the initial source
- L84 _public function_ `virtual bool LoadScene(TSharedRef<IDatasmithScene> OutScene)` — Main feature of the translator system, convert source to a datasmith scene @param Source	Source to translate @param OutScene	DatasmithScene to fill with source informations @returns			Load succeed
- L89 _public function_ `virtual void UnloadScene()` — Called when the scene loading is over. All translator resources can be released.
- L98 _public function_ `virtual bool LoadStaticMesh(const TSharedRef<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload)` — Get payload related to the given Element @param MeshElement		Element for which the payload is required @param OutMeshPayload	Actual mesh data from the source @returns					Operation succeed
- L109 _public function_ `virtual bool LoadCloth(const TSharedRef<IDatasmithClothElement> ClothElement, FDatasmithClothElementPayload& OutClothPayload)` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")` — Get payload related to the given Element @param ClothElement       Element for which the payload is required @param OutClothPayload    Actual cloth data from the source @returns                  Operation succeed
- L119 _public function_ `virtual bool LoadLevelSequence(const TSharedRef<IDatasmithLevelSequenceElement> LevelSequenceElement, FDatasmithLevelSequencePayload& OutLevelSequencePayload)` — Get payload related to the given Element @param LevelSequenceElement		Element for which the payload is required @param OutLevelSequencePayload	Data associated with this element @returns							Operation succeed
- L127 _public function_ `virtual void GetSceneImportOptions(TArray<TObjectPtr<UDatasmithOptionsBase>>& Options)` — Get the additional scene import options. Implementation can expose additional options to the user here. @param OptionClasses list of classes that will be displayed to the user
- L129 _public function_ `virtual void GetSceneImportOptions(TArray<TStrongObjectPtr<UDatasmithOptionsBase>>& Options)` — `UE_DEPRECATED(5.1, "Deprecated, please use same method using array of TObjectPtr instead")`
- L136 _public function_ `virtual void SetSceneImportOptions(const TArray<TObjectPtr<UDatasmithOptionsBase>>& Options)` — Values of additional options as entered by the user @param Options Actual values for the displayed options.
- L138 _public function_ `virtual void SetSceneImportOptions(TArray<TStrongObjectPtr<UDatasmithOptionsBase>>& Options)` — `UE_DEPRECATED(5.1, "Deprecated, please use same method using array of TObjectPtr instead")`
- L141 _private member_ `FDatasmithSceneSource SceneSource;`

#### struct `Datasmith::FTranslatorRegisterInformation`  
`struct FTranslatorRegisterInformation`  
_L146-150_
- L148 _public member_ `FName TranslatorName = NAME_None;`
- L149 _public member_ `TFunction<TSharedPtr<IDatasmithTranslator>()> SpawnFunction;`

#### Free symbols / members of external scopes

- L144 _namespace_ `namespace Datasmith`
- L152 _namespace_ `namespace Details` (scope `Datasmith`)
- L154 _prototype_ `void RegisterTranslatorImpl(const FTranslatorRegisterInformation& Info);` (scope `Datasmith::Details`)
- L155 _prototype_ `void UnregisterTranslatorImpl(const FTranslatorRegisterInformation& Info);` (scope `Datasmith::Details`)
- L160 _function_ `template<typename ImplType> void RegisterTranslator()` (scope `Datasmith`)
- L165 _function_ `RegInfo.SpawnFunction = []` (scope `Datasmith::RegisterTranslator`)
- L170 _function_ `template<typename ImplType> void UnregisterTranslator()` (scope `Datasmith`)
- L179 _function_ `template<class UOptionClass> inline UOptionClass* MakeOptionsPtr()` (scope `Datasmith`)
- L185 _function_ `template<class UOptionClass> inline TStrongObjectPtr<UOptionClass> MakeOptions()` (scope `Datasmith`)
- L192 _function_ `template<class UOptionClass> inline TObjectPtr<UOptionClass> MakeOptionsObjectPtr()` (scope `Datasmith`)
- L197 _prototype_ `FString GetXMLFileSchema(const FString& XmlFilePath);` (scope `Datasmith`)
- L200 _function_ `template<typename ValueType> bool CheckXMLSchema(const FString& FileXmlSchema, ValueType Format)` (scope `Datasmith`)
- L206 _function_ `template<typename ValueType, class... ValueTypes> bool CheckXMLSchema(const FString& FileXmlSchema, ValueType Format, ValueTypes... OtherFormats)` (scope `Datasmith`)
- L219 _function_ `template<class... ValueTypes> bool CheckXMLFileSchema(const FString& XmlFilePath, ValueTypes&... SupportedSchema)` (scope `Datasmith`) — Check if the xml file schema is in the list of supported schema

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Public/DatasmithTranslatorManager.h` (Public)


#### class `FDatasmithTranslatorManager`  
`class FDatasmithTranslatorManager`  
_L11-48_
- desc: Responsible of the Translators lifecycle.
- L13 _private prototype_ `FDatasmithTranslatorManager() = default;`
- L16 _public prototype_ `static FDatasmithTranslatorManager& Get();` — Gather all viable translators
- L19 _public prototype_ `const TArray<FString>& GetSupportedFormats() const;` — Get the list of "ext;description" formats
- L26 _public prototype_ `TSharedPtr<IDatasmithTranslator> SelectFirstCompatible(const FDatasmithSceneSource& Source);` — Based on source file extension, select a suitable Translator @param Source	import source @return			First Translator capable of handling the given file
- L33 _public prototype_ `void Register(const Datasmith::FTranslatorRegisterInformation& Info);` — Register an implementation.(Only registered Implementations are usable.) @note: Do not use directly, use Datasmith::RegisterTranslator<>() function instead @param Info required informations to dynamically handle various Translators
- L40 _public prototype_ `void Unregister(FName TranslatorName);` — Revert a call to Register. @note: Do not use directly, use Datasmith::UnregisterTranslator<>() function instead @param TranslatorName Name of the registered Translator to remove.
- L43 _private prototype_ `void InvalidateCache();`
- L46 _private member_ `TArray<Datasmith::FTranslatorRegisterInformation> RegisteredTranslators;`
- L47 _private member_ `mutable TArray<FString> Formats;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Public/DatasmithTranslatorModule.h` (Public)


#### class `IDatasmithTranslatorModule`  
`class IDatasmithTranslatorModule : public IModuleInterface`  
_L11-28_
- inherits: `IModuleInterface`
- L15 _public function_ `static IDatasmithTranslatorModule& Get()`
- L20 _public function_ `static bool IsAvailable()`
- L25 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define DATASMITHTRANSLATOR_MODULE_NAME TEXT("DatasmithTranslator")`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Public/ReferenceMaterials/DatasmithReferenceMaterial.h` (Public)


#### class `FDatasmithReferenceMaterial`  
`class FDatasmithReferenceMaterial`  
_L14-35_
- desc: Represents a material that exposes named parameters for override purpose. Note that this can be a Material or a MaterialInstance.
- L17 _public prototype_ `FDatasmithReferenceMaterial();`
- L19 _public prototype_ `void FromMaterial( UMaterialInterface* InMaterial );`
- L20 _public prototype_ `void FromSoftObjectPath( const FSoftObjectPath& InObjectPath );`
- L22 _public function_ `UMaterialInterface* GetMaterial() const`
- L24 _public function_ `bool IsValid() const`
- L26 _public member_ `TSet< FString > VectorParams;`
- L27 _public member_ `TSet< FString > ScalarParams;`
- L28 _public member_ `TSet< FString > TextureParams;`
- L30 _public member_ `TSet< FString > BoolParams;`
- L34 _private member_ `UMaterialInterface* Material;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Public/ReferenceMaterials/DatasmithReferenceMaterialManager.h` (Public)


#### class `FDatasmithReferenceMaterialManager`  
`class FDatasmithReferenceMaterialManager`  
_L10-31_
- L13 _public prototype_ `FDatasmithReferenceMaterialManager() = default;`
- L14 _public prototype_ `~FDatasmithReferenceMaterialManager();`
- L16 _public prototype_ `static void Create();`
- L17 _public prototype_ `static void Destroy();`
- L18 _public prototype_ `static FDatasmithReferenceMaterialManager& Get();`
- L20 _public prototype_ `FString GetHostFromString( const FString& HostString );`
- L22 _public prototype_ `void RegisterSelector( const TCHAR* Host, TSharedPtr< FDatasmithReferenceMaterialSelector > Selector );`
- L23 _public prototype_ `void UnregisterSelector( const TCHAR* Host );`
- L25 _public prototype_ `const TSharedPtr< FDatasmithReferenceMaterialSelector > GetSelector( const TCHAR* Host ) const;`
- L28 _private member_ `static TUniquePtr< FDatasmithReferenceMaterialManager > Instance;`
- L30 _private member_ `TMap< FString, TSharedPtr< FDatasmithReferenceMaterialSelector > > Selectors;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Public/ReferenceMaterials/DatasmithReferenceMaterialSelector.h` (Public)


#### class `FDatasmithReferenceMaterialSelector`  
`class FDatasmithReferenceMaterialSelector`  
_L12-30_
- L15 _public prototype_ `virtual ~FDatasmithReferenceMaterialSelector() = default;`
- L17 _public function_ `virtual bool IsValid() const`
- L18 _public prototype_ `virtual const FDatasmithReferenceMaterial& GetReferenceMaterial( const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial ) const;`
- L19 _public function_ `virtual void FinalizeMaterialInstance(const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial, UMaterialInstanceConstant* MaterialInstance) const`
- L21 _public prototype_ `virtual bool GetColor( const TSharedPtr< IDatasmithKeyValueProperty >& InMaterialProperty, FLinearColor& OutValue ) const;`
- L22 _public prototype_ `virtual bool GetFloat( const TSharedPtr< IDatasmithKeyValueProperty >& InMaterialProperty, float& OutValue ) const;`
- L23 _public prototype_ `virtual bool GetBool( const TSharedPtr< IDatasmithKeyValueProperty >& InMaterialProperty, bool& OutValue ) const;`
- L24 _public prototype_ `virtual bool GetTexture( const TSharedPtr< IDatasmithKeyValueProperty >& InMaterialProperty, FString& OutValue ) const;`
- L25 _public prototype_ `virtual bool GetString( const TSharedPtr< IDatasmithKeyValueProperty >& InMaterialProperty, FString& OutValue ) const;`
- L28 _protected member_ `static FDatasmithReferenceMaterial InvalidReferenceMaterial;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithTranslator/Public/Utility/DatasmithMeshHelper.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace DatasmithMeshHelper`
- L25 _prototype_ `int32 GetPolygonCount(const FMeshDescription& Mesh);` (scope `DatasmithMeshHelper`) — Number of polygon in the given Mesh @param Mesh      Source mesh @return int32    number of polys
- L33 _prototype_ `int32 GetTriangleCount(const FMeshDescription& Mesh);` (scope `DatasmithMeshHelper`) — Number of triangles in the given Mesh @param Mesh      Source mesh @return int32    number of triangles
- L43 _prototype_ `void ExtractVertexPositions(const FMeshDescription& Mesh, TArray<FVector3f>& OutPositions);` (scope `DatasmithMeshHelper`) — Build a copy of all positions. Can be used to build a convexHull, a bounding box, etc... @param Mesh @param Positions @return DATASMITHIMPORTER_API void
- L51 _prototype_ `void PrepareAttributeForStaticMesh(FMeshDescription& Mesh);` (scope `DatasmithMeshHelper`) — Register all attributes required to correctly interact with StaticMesh. @note: Delegates to FStaticMesh the registering of standard attributes @param Mesh   MeshDescription to prepare for StaticMesh usage
- L60 _prototype_ `bool IsTriangleDegenerated(const FMeshDescription& Mesh, const FMeshTriangle& MeshTriangle);` (scope `DatasmithMeshHelper`) — Test if a triangle is extremely small or if its corners are aligned. @param Mesh		    Source mesh that contains the tested triangle @param MeshTriangle	Triangle in that mesh @return bool         True for degenerated triangles, false otherwise
- L67 _prototype_ `void RemoveEmptyPolygonGroups(FMeshDescription& Mesh);` (scope `DatasmithMeshHelper`) — Remove any empty polygon groups in the mesh description and compact it if needed. @param Mesh		    The source mesh
- L78 _prototype_ `void FillUStaticMesh(UStaticMesh* StaticMesh, int32 LodIndex, FRawMesh& RawMesh, const TMap<int32, FName>* InMaterialMapInverse = nullptr);` (scope `DatasmithMeshHelper`) — Write mesh data on a UStaticMesh. RawMesh will be converted to MeshDescription beforehand. @param StaticMesh    Destination StaticMesh @param LodIndex      Destination index in the StaticMesh @param Mesh          Source data to write into the StaticMesh
- L79 _prototype_ `void FillUStaticMesh(UStaticMesh* StaticMesh, int32 LodIndex, FDatasmithMesh& DSMesh);` (scope `DatasmithMeshHelper`)
- L80 _prototype_ `void FillUStaticMeshByCopy(UStaticMesh* StaticMesh, int LodIndex, FMeshDescription MeshDescription);` (scope `DatasmithMeshHelper`)
- L81 _prototype_ `void FillUStaticMesh(UStaticMesh* StaticMesh, int LodIndex, FMeshDescription&& MeshDescription);` (scope `DatasmithMeshHelper`)
- L88 _prototype_ `void PrepareStaticMaterials(UStaticMesh* StaticMesh, int32 MaterialCount);` (scope `DatasmithMeshHelper`) — Make sure the StaticMesh can host all used materials @param				    StaticMesh Mesh to prepare @param MaterialCount     Number of slot required
- L99 _prototype_ `void BuildMaterialMappingFromStaticMesh(UStaticMesh* StaticMesh, TMap<FName, int32>& MaterialMap, TMap<int32, FName>& MaterialMapInverse);` (scope `DatasmithMeshHelper`) — Used in FRawMesh <-> FMeshDescription context, create the SlotName <-> MaterialIndex mapping MaterialIndex in range [0, StaticMaterials.Num()-1] SlotName extracted from, StaticMaterials.ImportedMaterialSlotName @param StaticMesh            Source of the mapping information @param MaterialMap	        map SlotName to MaterialIndex @param MaterialMapInverse    map a MaterialIndex to SlotName
- L109 _prototype_ `void HashMeshLOD(UStaticMesh* StaticMesh, int32 LodIndex, FMD5& MD5);` (scope `DatasmithMeshHelper`) — Hash a Mesh at specified LOD index in a StaticMesh @param StaticMesh    Source Mesh set @param LodIndex      LOD index of the Mesh to hash @param MD5           Hash to update @return DATASMITHIMPORTER_API void
- L118 _prototype_ `void HashMeshDescription(const FMeshDescription& Mesh, FMD5& MD5);` (scope `DatasmithMeshHelper`) — Hash a MeshDescription @param Mesh  MeshDescription to hash @param MD5   Hash to update
- L125 _prototype_ `FName DefaultSlotName(int32 MaterialIndex);` (scope `DatasmithMeshHelper`) — Generate a default FName to name a material slot based on the index @param MaterialIndex index of the slot to name
- L127 _prototype_ `int32 GetNumUVChannel(const FMeshDescription& Mesh);` (scope `DatasmithMeshHelper`)
- L128 _prototype_ `bool HasUVChannel(const FMeshDescription& Mesh, int32 ChannelIndex);` (scope `DatasmithMeshHelper`)
- L130 _prototype_ `bool HasUVData(const FMeshDescription& Mesh, int32 ChannelIndex);` (scope `DatasmithMeshHelper`)
- L132 _prototype_ `bool RequireUVChannel(FMeshDescription& Mesh, int32 ChannelIndex);` (scope `DatasmithMeshHelper`)
- L139 _prototype_ `void CreateDefaultUVs(FDatasmithMesh& DatasmithMesh);` (scope `DatasmithMeshHelper`) — Generate simple UV data at channel 0. @param DatasmithMesh		The DatasmithMesh in which the UV data will be created.
- L146 _prototype_ `void CreateDefaultUVs(FMeshDescription& MeshDescription);` (scope `DatasmithMeshHelper`) — Generate simple UV data at channel 0. @param MeshDescription	The MeshDescription in which the UV data will be created.
- L155 _prototype_ `bool IsMeshValid(const FMeshDescription& Mesh, FVector3f BuildScale=FVector3f::OneVector);` (scope `DatasmithMeshHelper`) — Verify that at least one triangle in that mesh is not degenerated @param Mesh @param BuildScale @return DATASMITHIMPORTER_API bool
