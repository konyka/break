# Plugins / DatasmithContent

- module root: `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent`
- headers: 27; symbols: 582
- symbol kinds: class=44, delegate=1, enum=11, enumerator=42, function=36, macro=28, member=228, namespace=4, prototype=164, struct=18, typedef=3, variable=3
- PrivateDependencyModuleNames: EditorFramework, Landscape, LevelSequence, MeshDescription, Projects, StaticMeshDescription, UnrealEd, VariantManagerContent
- PrivateIncludePathModuleNames: MainFrame
- PublicDependencyModuleNames: CinematicCamera, Core, CoreUObject, Engine, RenderCore

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithAdditionalData.h` (Public)


#### class `UDatasmithAdditionalData`  
`class UDatasmithAdditionalData : public UObject`  
_L25-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class for all additional data storable on datasmith assets. @usage: Translator can push custom data on assets in order to exploit that data latter (@see UDatasmithCustomActionBase)
- L30 _public prototype_ `UDatasmithAdditionalData();`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DATASMITHCONTENT_API`
- L34 _namespace_ `namespace Datasmith`
- L46 _function_ `inline DataType* MakeAdditionalData()` (scope `Datasmith`)
- L67 _function_ `inline TArray<DataType*> GetMultipleAdditionalData(const FAssetData& SourceAssetData, int MaxCount=0)` (scope `Datasmith`)
- L103 _function_ `inline DataType* GetAdditionalData(const FAssetData& SourceAssetData)` (scope `Datasmith`)

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithAreaLightActor.h` (Public)


#### enum `EDatasmithAreaLightActorShape`  
`enum class EDatasmithAreaLightActorShape : uint8`  
_L12-19_
- reflection: `UENUM(BlueprintType)`
- desc: Keep in sync with EDatasmithLightShape from DatasmithDefinitions
- L14 _public enumerator_ `Rectangle`
- L15 _public enumerator_ `Disc`
- L16 _public enumerator_ `Sphere`
- L17 _public enumerator_ `Cylinder`
- L18 _public enumerator_ `None`

#### enum `EDatasmithAreaLightActorType`  
`enum class EDatasmithAreaLightActorType : uint8`  
_L22-29_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `Point`
- L25 _public enumerator_ `Spot`
- L26 _public enumerator_ `IES_DEPRECATED` — Added for consistency with type EDatasmithAreaLightType.
- L28 _public enumerator_ `Rect` — Removing this will result in 'EDatasmithAreaLightActorType MAX' enum value in the editor.

#### class `ADatasmithAreaLightActor`  
`class ADatasmithAreaLightActor : public AActor`  
_L32-90_
- reflection: `UCLASS(BlueprintType, Blueprintable, MinimalAPI)`
- inherits: `AActor`
- L38 _public member_ `TEnumAsByte<EComponentMobility::Type> Mobility;` — `UPROPERTY(Category = Mobility, EditAnywhere, BlueprintReadOnly)`
- L41 _public member_ `EDatasmithAreaLightActorType LightType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")`
- L44 _public member_ `EDatasmithAreaLightActorShape LightShape;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")`
- L47 _public member_ `FVector2D Dimensions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta = (EditCondition = "LightShape != EDatasmithAreaLightActorShape::None"))`
- L50 _public member_ `float Intensity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")`
- L53 _public member_ `ELightUnits IntensityUnits;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")`
- L56 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")`
- L59 _public member_ `float Temperature;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")`
- L62 _public member_ `TObjectPtr<class UTextureLightProfile> IESTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")`
- L65 _public member_ `bool bUseIESBrightness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta=(DisplayName = "Use IES Intensity"))`
- L68 _public member_ `float IESBrightnessScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta=(DisplayName = "IES Intensity Scale"))`
- L71 _public member_ `FRotator Rotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")`
- L74 _public member_ `float SourceRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")`
- L77 _public member_ `float SourceLength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")`
- L80 _public member_ `float AttenuationRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta=(UIMin = "8.0", UIMax = "16384.0", SliderExponent = "5.0"))`
- L83 _public member_ `float SpotlightInnerAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta = (UIMin = "1.0", UIMax = "80.0", SliderExponent = "1.0"))`
- L86 _public member_ `float SpotlightOuterAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta = (UIMin = "0.0", UIMax = "80.0", SliderExponent = "1.0"))`
- L89 _public prototype_ `ADatasmithAreaLightActor();`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithAssetImportData.h` (Public)


#### struct `FDatasmithImportInfo`  
`struct FDatasmithImportInfo`  
_L18-51_
- reflection: `USTRUCT()`
- desc: Structure that fill the same role as FAssetImportInfo, but for SourceUri. Eventually, the SourceUri should be directly added to FAssetImportInfo and replace the "RelativeFilename".
- L24 _public function_ `FDatasmithImportInfo()`
- L27 _public function_ `explicit FDatasmithImportInfo(const FString& InSourceUri, FString InSourceHashString = FString()) : SourceUri(InSourceUri) , SourceHash(InSourceHashString)`
- L32 _public function_ `FDatasmithImportInfo(const FString& InSourceUri, FMD5Hash InSourceHash) : SourceUri(InSourceUri) , SourceHash(LexToString(InSourceHash))`
- L39 _public member_ `FString SourceUri;` — `UPROPERTY()` — The Uri of to the source that this asset was imported from.
- L45 _public member_ `FString SourceHash;` — `UPROPERTY()` — The MD5 hash of the source when it was imported. Should be updated alongside the SourceUri
- L47 _public prototype_ `void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const;`
- L49 _public prototype_ `void GetAssetRegistryTags(TArray<UObject::FAssetRegistryTag>& OutTags) const;` — `UE_DEPRECATED(5.4, "Call the version that takes FAssetRegistryTagsContext instead.")`

#### class `UDatasmithAssetImportData`  
`class UDatasmithAssetImportData : public UAssetImportData`  
_L54-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetImportData`
- L61 _public member_ `FDatasmithAssetImportOptions AssetImportOptions;` — `UPROPERTY(BlueprintReadWrite, Category = Asset, meta = (ShowOnlyInnerProperties))`
- L64 _public member_ `TArray<TObjectPtr<class UDatasmithAdditionalData>> AdditionalData;` — `UPROPERTY(EditAnywhere, Instanced, Category = Asset, meta = (ShowOnlyInnerProperties))`
- L67 _public member_ `FDatasmithImportInfo DatasmithImportInfo;` — `UPROPERTY(EditAnywhere, Category = "External Source")`

#### class `UDatasmithStaticMeshImportData`  
`class UDatasmithStaticMeshImportData : public UDatasmithAssetImportData`  
_L72-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithAssetImportData`
- L79 _public member_ `FDatasmithStaticMeshImportOptions ImportOptions;` — `UPROPERTY(EditAnywhere, Category = StaticMesh, meta = (ShowOnlyInnerProperties))`
- L82 _public typedef_ `typedef TPair< FDatasmithStaticMeshImportOptions, FDatasmithAssetImportOptions > DefaultOptionsPair;`
- L83 _public prototype_ `static UDatasmithStaticMeshImportData* GetImportDataForStaticMesh( UStaticMesh* StaticMesh, TOptional< DefaultOptionsPair > DefaultImportOptions = TOptional< DefaultOptionsPair >() );`

#### class `UDatasmithStaticMeshCADImportData`  
`UDatasmithStaticMeshCADImportData : public UDatasmithStaticMeshImportData`  
_L90-126_
- reflection: `UCLASS(MinimalAPI, HideCategories = (InternalProperty))`
- reflection: `UE_DEPRECATED(5.8, "The class UDatasmithStaticMeshCADImportData has been deprecated and will be removed next release. Please use UDatasmithParametricSurfaceData and child classes instead.")`
- inherits: `UDatasmithStaticMeshImportData`
- L97 _public member_ `FDatasmithTessellationOptions TessellationOptions;` — `UPROPERTY(EditAnywhere, Category = StaticMesh, meta = (ShowOnlyInnerProperties))`
- L100 _public member_ `double ModelUnit;` — `UPROPERTY(VisibleDefaultsOnly, Category = InternalProperty)`
- L103 _public member_ `double ModelTolerance;` — `UPROPERTY(VisibleDefaultsOnly, Category = InternalProperty)`
- L107 _protected member_ `FString ResourcePath;` — `UPROPERTY(VisibleDefaultsOnly, Category = InternalProperty)`
- L110 _protected member_ `FString ResourceFilename;` — `UPROPERTY(VisibleDefaultsOnly, Category = InternalProperty)`
- L113 _protected member_ `TArray<FString> AuxiliaryFilenames;` — `UPROPERTY(VisibleDefaultsOnly, Category = InternalProperty)`
- L116 _public typedef_ `typedef TTuple<FDatasmithTessellationOptions, FDatasmithStaticMeshImportOptions, FDatasmithAssetImportOptions> DefaultOptionsTuple;`
- L117 _public prototype_ `static UDatasmithStaticMeshCADImportData* GetCADImportDataForStaticMesh( UStaticMesh* StaticMesh, TOptional< DefaultOptionsTuple > DefaultImportOptions = TOptional< DefaultOptionsTuple >() );`
- L119 _public prototype_ `void SetResourcePath(const FString& FilePath);`
- L120 _public prototype_ `const FString& GetResourcePath();`
- L125 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;` — Overridden serialize function to read in/write out the unexposed data

#### class `UDatasmithSceneImportData`  
`class UDatasmithSceneImportData : public UAssetImportData`  
_L132-151_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetImportData`
- desc: Base class for import data and options used when importing any asset from Datasmith
- L139 _public member_ `FDatasmithImportBaseOptions BaseOptions;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (ShowOnlyInnerProperties))`
- L142 _public member_ `FDatasmithImportInfo DatasmithImportInfo;` — `UPROPERTY(EditAnywhere, Category = "External Source")`
- L146 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`

#### class `UDatasmithTranslatedSceneImportData`  
`class UDatasmithTranslatedSceneImportData : public UDatasmithSceneImportData`  
_L157-166_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithSceneImportData`
- desc: Import data and options specific to Datasmith scenes imported through the translator system
- L164 _public member_ `TArray<TObjectPtr<UDatasmithOptionsBase>> AdditionalOptions;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (ShowOnlyInnerProperties))`

#### class `UDatasmithCADImportSceneData`  
`class UDatasmithCADImportSceneData : public UDatasmithSceneImportData`  
_L172-181_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithSceneImportData`
- desc: Import data and options specific to tessellated Datasmith scenes
- L179 _public member_ `FDatasmithTessellationOptions TessellationOptions;` — `UPROPERTY(EditAnywhere, Category = "Tessellation", meta = (ShowOnlyInnerProperties))`

#### class `UDatasmithMDLSceneImportData`  
`class UDatasmithMDLSceneImportData : public UDatasmithSceneImportData`  
_L184-187_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithSceneImportData`

#### class `UDatasmithGLTFSceneImportData`  
`class UDatasmithGLTFSceneImportData : public UDatasmithSceneImportData`  
_L190-208_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UDatasmithSceneImportData`
- L195 _public member_ `FString Generator;` — `UPROPERTY(VisibleAnywhere, Category = "Scene Info", DisplayName="Generator Name")`
- L198 _public member_ `float Version;` — `UPROPERTY(VisibleAnywhere, Category = "Scene Info", DisplayName="Version")`
- L201 _public member_ `FString Author;` — `UPROPERTY(VisibleAnywhere, Category = "Scene Info", DisplayName="Author")`
- L204 _public member_ `FString License;` — `UPROPERTY(VisibleAnywhere, Category = "Scene Info", DisplayName="License")`
- L207 _public member_ `FString Source;` — `UPROPERTY(VisibleAnywhere, Category = "Scene Info", DisplayName="Source")`

#### class `UDatasmithStaticMeshGLTFImportData`  
`class UDatasmithStaticMeshGLTFImportData : public UDatasmithStaticMeshImportData`  
_L211-218_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UDatasmithStaticMeshImportData`
- L217 _public member_ `FString SourceMeshName;` — `UPROPERTY(VisibleAnywhere, Category = InternalProperty)`

#### class `UDatasmithFBXSceneImportData`  
`class UDatasmithFBXSceneImportData : public UDatasmithSceneImportData`  
_L221-238_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UDatasmithSceneImportData`
- L227 _public member_ `bool bGenerateLightmapUVs;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L230 _public member_ `FString TexturesDir;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L234 _public member_ `uint8 IntermediateSerialization;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)` — Corresponds to a EDatasmithFBXIntermediateSerializationType
- L237 _public member_ `bool bColorizeMaterials;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`

#### class `UDatasmithDeltaGenAssetImportData`  
`class UDatasmithDeltaGenAssetImportData : public UDatasmithAssetImportData`  
_L241-244_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UDatasmithAssetImportData`

#### class `UDatasmithDeltaGenSceneImportData`  
`class UDatasmithDeltaGenSceneImportData : public UDatasmithFBXSceneImportData`  
_L247-281_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UDatasmithFBXSceneImportData`
- L253 _public member_ `bool bMergeNodes;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L256 _public member_ `bool bOptimizeDuplicatedNodes;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L259 _public member_ `bool bRemoveInvisibleNodes;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L262 _public member_ `bool bSimplifyNodeHierarchy;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L265 _public member_ `bool bImportVar;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L268 _public member_ `FString VarPath;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L271 _public member_ `bool bImportPos;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L274 _public member_ `FString PosPath;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L277 _public member_ `bool bImportTml;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L280 _public member_ `FString TmlPath;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`

#### class `UDatasmithVREDAssetImportData`  
`class UDatasmithVREDAssetImportData : public UDatasmithAssetImportData`  
_L284-287_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UDatasmithAssetImportData`

#### class `UDatasmithVREDSceneImportData`  
`class UDatasmithVREDSceneImportData : public UDatasmithFBXSceneImportData`  
_L290-327_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `UDatasmithFBXSceneImportData`
- L296 _public member_ `bool bMergeNodes;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L299 _public member_ `bool bOptimizeDuplicatedNodes;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L302 _public member_ `bool bImportMats;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L305 _public member_ `FString MatsPath;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L308 _public member_ `bool bImportVar;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L311 _public member_ `bool bCleanVar;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L314 _public member_ `FString VarPath;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L317 _public member_ `bool bImportLightInfo;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L320 _public member_ `FString LightInfoPath;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L323 _public member_ `bool bImportClipInfo;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`
- L326 _public member_ `FString ClipInfoPath;` — `UPROPERTY(VisibleAnywhere, Category = ImportOptions)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATASMITHCONTENT_API`
- L329 _namespace_ `namespace Datasmith`
- L331 _prototype_ `UAssetImportData* GetAssetImportData(UObject* Asset);` (scope `Datasmith`)

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithAssetUserData.h` (Public)


#### class `UDatasmithAssetUserData`  
`class UDatasmithAssetUserData : public UAssetUserData`  
_L16-43_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (ScriptName = "DatasmithUserData", DisplayName = "Datasmith User Data"))`
- inherits: `UAssetUserData`
- desc: Asset user data that can be used with Datasmith on Actors and other objects
- L23 _public typedef_ `typedef TMap<FName, FString> FMetaDataContainer;` — Meta-data are available at runtime in game, i.e. used in blueprint to display build-boarded information
- L26 _public member_ `TMap<FName, FString> MetaData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Datasmith User Data", meta = (ScriptName = "Metadata", DisplayName = "Metadata"))`
- L30 _public member_ `TMap< TSubclassOf< UDatasmithObjectTemplate >, TObjectPtr<UDatasmithObjectTemplate> > ObjectTemplates;` — `UPROPERTY()`
- L32 _public prototype_ `virtual bool IsPostLoadThreadSafe() const override;`
- L33 _public prototype_ `virtual void PostLoad() override;`
- L36 _public prototype_ `static FString GetDatasmithUserDataValueForKey(UObject* Object, FName Key, bool bPartialMatchKey = false);`
- L37 _public prototype_ `static TArray<FString> GetDatasmithUserDataValuesForKey(UObject* Object, FName Key, bool bPartialMatchKey = false);`
- L38 _public prototype_ `static UDatasmithAssetUserData* GetDatasmithUserData(UObject* Object);`
- L39 _public prototype_ `static bool SetDatasmithUserDataValueForKey(UObject* Object, FName Key, const FString & Value);`
- L42 _public member_ `static const TCHAR* UniqueIdMetaDataKey;` — Meta data keys for Datasmith objects

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithContentBlueprintLibrary.h` (Public)


#### class `UDatasmithContentBlueprintLibrary`  
`class UDatasmithContentBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L15-80_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "DatasmithContentLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L26 _public prototype_ `static UDatasmithAssetUserData* GetDatasmithUserData(UObject* Object);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith User Data")` — Get the Datasmith User Data of a given object @param	Object	The Object from which to retrieve the Datasmith User Data. @return			The Datasmith User Data if it exists; nullptr, otherwise
- L35 _public prototype_ `static FString GetDatasmithUserDataValueForKey(UObject* Object, FName Key, bool bPartialMatchKey = false);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith User Data")` — Get the value of the given key for the Datasmith User Data of the given object. @param	Object				The Object from which to retrieve the Datasmith User Data. @param	Key					The key to find in the Datasmith User Data. @return						The string value associated with the given key
- L45 _public prototype_ `static TArray<FString> GetDatasmithUserDataValuesForKey(UObject* Object, FName Key, bool bPartialMatchKey = false);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith User Data")` — Get the values of the given key for the Datasmith User Data of the given object. @param	Object				The Object from which to retrieve the Datasmith User Data. @param	Key					The key to find in the Datasmith User Data. @param	bPartialMatchKey	If true, check for contains, rather than exact match. @return						The string value associated with the given key
- L55 _public prototype_ `static void GetDatasmithUserDataKeysAndValuesForValue(UObject* Object, const FString& StringToMatch, TArray<FName>& OutKeys, TArray<FString>& OutValues);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith User Data")` — Get the keys and values for which the associated value contains the string to match for the Datasmith User Data of the given object. @param	Object			The Object from which to retrieve the Datasmith User Data. @param	StringToMatch	The string to match in the values. @param	OutKeys			Output array of keys for which the associated values contain the string to match. @param	OutValues		Output array of values associated to the keys.
- L66 _public prototype_ `static void GetAllDatasmithUserData(TSubclassOf<UObject> ObjectClass, TArray<UDatasmithAssetUserData*>& OutUserData);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Datasmith User Data")` — Find all Datasmith User Data of loaded objects of the given type. This is a slow operation, so editor only. @param	ObjectClass		Class of the object on which to filter, if specificed; otherwise there's no filtering @param	OutUserData		Output array of Datasmith User Data.
- L77 _public prototype_ `static void GetAllObjectsAndValuesForKey(FName Key, TSubclassOf<UObject> ObjectClass, TArray<UObject*>& OutObjects, TArray<FString>& OutValues);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Datasmith User Data", meta = (DeterminesOutputType = "ObjectClass", DynamicOutputParam = "OutObjects"))` — Find all loaded objects of the given type that have a Datasmith User Data that contains the given key and their associated values. This is a slow operation, so editor only. @param	Key			The key to find in the Datasmith User Data. @param	ObjectClass	Class of the object on which to filter, if specificed; otherwise there's no filtering @param	OutObjects	Output array of objects for which the Datasmith User Data match the given key. @param	OutValues	Output array of values associated with each object in OutObjects.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithContentModule.h` (Public)


#### class `IDatasmithContentModule`  
`class IDatasmithContentModule : public IModuleInterface`  
_L16-46_
- inherits: `IModuleInterface`
- desc: The public interface of the DatasmithContent module
- L26 _public function_ `static inline IDatasmithContentModule& Get()` — Singleton-like access to IDatasmithContent @return Returns DatasmithContent singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L45 _public prototype_ `virtual const FString& GetTempDir() const = 0;` — `UE_DEPRECATED(5.8, "IDatasmithContentModule::GetTempDir will be removed in next release.")` — @returns temporary directory created for this process

#### Free symbols / members of external scopes

- L9 _macro_ `#define DATASMITHCONTENT_MODULE_NAME TEXT("DatasmithContent")`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN( LogDatasmithContent, Log, All );`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN( LogDatasmithContent, Log, All );`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithCustomAction.h` (Public)


#### class `IDatasmithCustomAction`  
`class IDatasmithCustomAction`  
_L16-56_
- desc: Interface of a CustomAction. This is a way to quickly expose some custom processing.
- L19 _public prototype_ `virtual ~IDatasmithCustomAction() = default;`
- L22 _public prototype_ `virtual const FText& GetLabel() = 0;` — @return Displayed name of the action
- L25 _public prototype_ `virtual const FText& GetTooltip() = 0;` — @return Displayed tooltip of the action
- L34 _public prototype_ `virtual bool CanApplyOnAssets(const TArray<FAssetData>& SelectedAssets) = 0;` — Called by Datasmith when we displays potential action for some assets (eg. when the context menu of the content browser is used). @param SelectedAssets: Set of candidate assets for processing @return true when this action is applicable on the given set
- L40 _public prototype_ `virtual void ApplyOnAssets(const TArray<FAssetData>& SelectedAssets) = 0;` — The actual processing, called by Datasmith when the user trigger an action. @param SelectedAssets: Set of candidate assets for processing
- L49 _public prototype_ `virtual bool CanApplyOnActors(const TArray<AActor*>& SelectedActors) = 0;` — Called by Datasmith when we displays potential action for some actors (eg. when the context menu of the level editor is used). @param SelectedActors: Set of candidate actors for processing @return true when this action is applicable on the given set
- L55 _public prototype_ `virtual void ApplyOnActors(const TArray<AActor*>& SelectedActors) = 0;` — The actual processing, called by Datasmith when the user trigger an action. @param SelectedActors: Set of candidate actors for processing

#### class `UDatasmithCustomActionBase`  
`class UDatasmithCustomActionBase : public UObject, public IDatasmithCustomAction`  
_L64-77_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject,IDatasmithCustomAction`
- desc: Base class for actions available to the end-user through the Content browser contextual menu. By extending this class, the custom action is automatically registered to be available for the end user
- L69 _public function_ `virtual const FText& GetLabel() override PURE_VIRTUAL( GetLabel, return FText::GetEmpty(); ) virtual const FText& GetTooltip() override PURE_VIRTUAL( GetTooltip, return FText::GetEmpty(); ) virtual bool CanApplyOnAssets(const TArray<FAssetData>&)`
- L73 _public function_ `virtual void ApplyOnAssets(const TArray<FAssetData>&)`
- L75 _public function_ `virtual bool CanApplyOnActors(const TArray<AActor*>&)`
- L76 _public function_ `virtual void ApplyOnActors(const TArray<AActor*>&)`

#### class `FDatasmithCustomActionManager`  
`class FDatasmithCustomActionManager`  
_L80-90_
- L83 _public prototype_ `FDatasmithCustomActionManager();`
- L85 _public prototype_ `TArray<UDatasmithCustomActionBase*> GetApplicableActions(const TArray<FAssetData>& SelectedAssets);`
- L86 _public prototype_ `TArray<UDatasmithCustomActionBase*> GetApplicableActions(const TArray<AActor*>& SelectedActors);`
- L89 _private member_ `TArray<TStrongObjectPtr<UDatasmithCustomActionBase>> RegisteredActions;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithImportOptions.h` (Public)


#### enum `EDatasmithImportSearchPackagePolicy`  
`enum class EDatasmithImportSearchPackagePolicy : uint8`  
_L16-23_
- reflection: `UENUM()`
- L19 _public enumerator_ `Current UMETA(DisplayName = "Current", DisplayValue = "Current")` — Search only in current package
- L22 _public enumerator_ `All` — Search in all packages

#### enum `EDatasmithImportAssetConflictPolicy`  
`enum class EDatasmithImportAssetConflictPolicy : uint8`  
_L26-39_
- reflection: `UENUM()`
- L29 _public enumerator_ `Replace` — Replace existing asset with new one
- L32 _public enumerator_ `Update` — Update existing asset with new values
- L35 _public enumerator_ `Use` — Use existing asset instead of creating new one
- L38 _public enumerator_ `Ignore` — Skip new asset

#### enum `EDatasmithImportActorPolicy`  
`enum class EDatasmithImportActorPolicy : uint8`  
_L42-52_
- reflection: `UENUM()`
- L45 _public enumerator_ `Update` — Import new actors, update and delete existing actors. Doesn't recreate actors that exist in the source both not in the destination.
- L48 _public enumerator_ `Full` — Same as update but recreates deleted actors so that the source and destination are the same.
- L51 _public enumerator_ `Ignore` — Skip importing a certain type of actors

#### enum `EDatasmithImportMaterialQuality`  
`enum class EDatasmithImportMaterialQuality : uint8`  
_L55-62_
- reflection: `UENUM()`
- L57 _public enumerator_ `UseNoFresnelCurves`
- L59 _public enumerator_ `UseSimplifierFresnelCurves`
- L61 _public enumerator_ `UseRealFresnelCurves`

#### enum `EDatasmithImportLightmapMin`  
`enum class EDatasmithImportLightmapMin : uint8`  
_L65-73_
- reflection: `UENUM()`
- L67 _public enumerator_ `LIGHTMAP_16 UMETA(DisplayName = "16")`
- L68 _public enumerator_ `LIGHTMAP_32 UMETA(DisplayName = "32")`
- L69 _public enumerator_ `LIGHTMAP_64 UMETA(DisplayName = "64")`
- L70 _public enumerator_ `LIGHTMAP_128 UMETA(DisplayName = "128")`
- L71 _public enumerator_ `LIGHTMAP_256 UMETA(DisplayName = "256")`
- L72 _public enumerator_ `LIGHTMAP_512 UMETA(DisplayName = "512")`

#### enum `EDatasmithImportLightmapMax`  
`enum class EDatasmithImportLightmapMax : uint8`  
_L76-85_
- reflection: `UENUM()`
- L78 _public enumerator_ `LIGHTMAP_64 UMETA(DisplayName = "64")`
- L79 _public enumerator_ `LIGHTMAP_128 UMETA(DisplayName = "128")`
- L80 _public enumerator_ `LIGHTMAP_256 UMETA(DisplayName = "256")`
- L81 _public enumerator_ `LIGHTMAP_512 UMETA(DisplayName = "512")`
- L82 _public enumerator_ `LIGHTMAP_1024 UMETA(DisplayName = "1024")`
- L83 _public enumerator_ `LIGHTMAP_2048 UMETA(DisplayName = "2048")`
- L84 _public enumerator_ `LIGHTMAP_4096 UMETA(DisplayName = "4096")`

#### enum `EDatasmithImportScene`  
`enum class EDatasmithImportScene : uint8`  
_L88-95_
- reflection: `UENUM()`
- L90 _public enumerator_ `NewLevel UMETA(DisplayName = "Create New Level", ToolTip = "Create a new Level and spawn the actors after the import.")`
- L92 _public enumerator_ `CurrentLevel UMETA(DisplayName = "Merge to Current Level", ToolTip = "Use the current Level to spawn the actors after the import.")`
- L94 _public enumerator_ `AssetsOnly UMETA(DisplayName = "Assets Only", ToolTip = "Do not modify the Level after import. No actor will be created (including the Blueprint if requested by the ImportHierarchy"), }; UENUM() enum class EDatasmithCADStitchingTechnique : uint8 { StitchingNone = 0, StitchingHeal,`

#### enum `EDatasmithCADStitchingTechnique`  
`enum class EDatasmithCADStitchingTechnique : uint8`  
_L98-103_
- reflection: `UENUM()`
- L100 _public enumerator_ `StitchingNone = 0`
- L101 _public enumerator_ `StitchingHeal`
- L102 _public enumerator_ `StitchingSew`

#### enum `EDatasmithCADRetessellationRule`  
`enum class EDatasmithCADRetessellationRule : uint8`  
_L106-110_
- reflection: `UENUM()`
- L108 _public enumerator_ `All = 0`
- L109 _public enumerator_ `SkipDeletedSurfaces`

#### struct `FDatasmithAssetImportOptions`  
`struct FDatasmithAssetImportOptions`  
_L113-119_
- reflection: `USTRUCT(BlueprintType)`
- L118 _public member_ `FName PackagePath;` — `UPROPERTY()`

#### struct `FDatasmithStaticMeshImportOptions`  
`struct FDatasmithStaticMeshImportOptions`  
_L122-157_
- reflection: `USTRUCT(BlueprintType)`
- L126 _public prototype_ `FDatasmithStaticMeshImportOptions();`
- L130 _public member_ `EDatasmithImportLightmapMin MinLightmapResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lightmap)` — Minimum resolution for auto-generated lightmap UVs
- L134 _public member_ `EDatasmithImportLightmapMax MaxLightmapResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lightmap)` — Maximum resolution for auto-generated lightmap UVs
- L137 _public member_ `bool bGenerateLightmapUVs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lightmap, meta = (DisplayName = "Generate Lightmap UVs"))`
- L140 _public member_ `bool bRemoveDegenerates;` — `UPROPERTY(BlueprintReadWrite, Category = Mesh, Transient)`
- L143 _public prototype_ `static int32 ConvertLightmapEnumToValue( EDatasmithImportLightmapMin EnumValue );`
- L144 _public prototype_ `static int32 ConvertLightmapEnumToValue( EDatasmithImportLightmapMax EnumValue );`
- L146 _public function_ `bool operator == (const FDatasmithStaticMeshImportOptions& Other) const`
- L154 _public function_ `bool operator != (const FDatasmithStaticMeshImportOptions& Other) const`

#### struct `FDatasmithReimportOptions`  
`struct FDatasmithReimportOptions`  
_L160-174_
- reflection: `USTRUCT(BlueprintType)`
- L165 _public prototype_ `FDatasmithReimportOptions();`
- L169 _public member_ `bool bUpdateActors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SyncCurrentLevelActors", meta = (DisplayName = "Datasmith Scene Actors"))` — Specifies whether or not to update Datasmith Scene Actors in the current Level
- L173 _public member_ `bool bRespawnDeletedActors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SyncCurrentLevelActors", meta = (DisplayName = "Re-Spawn Deleted Actors", EditCondition = "bUpdateActors"))` — Specifies whether or not to add back Actors you've deleted from the current Level

#### struct `FDatasmithImportBaseOptions`  
`struct FDatasmithImportBaseOptions`  
_L177-214_
- reflection: `USTRUCT(BlueprintType)`
- L181 _public prototype_ `FDatasmithImportBaseOptions();`
- L185 _public member_ `EDatasmithImportScene SceneHandling;` — `UPROPERTY(BlueprintReadWrite, Category = Import, Transient)` — Specifies where to put the content
- L189 _public member_ `bool bIncludeGeometry;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Process, meta = (DisplayName = "Geometry"))` — Specifies whether or not to import geometry
- L193 _public member_ `bool bIncludeMaterial;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Process, meta = (DisplayName = "Materials & Textures"))` — Specifies whether or not to import materials and textures
- L197 _public member_ `bool bIncludeLight;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Process, meta = (DisplayName = "Lights"))` — Specifies whether or not to import lights
- L201 _public member_ `bool bIncludeCamera;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Process, meta = (DisplayName = "Cameras"))` — Specifies whether or not to import cameras
- L205 _public member_ `bool bIncludeAnimation;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Process, meta = (DisplayName = "Animations"))` — Specifies whether or not to import animations
- L208 _public member_ `FDatasmithAssetImportOptions AssetOptions;` — `UPROPERTY(BlueprintReadWrite, AdvancedDisplay, Category = Process, meta = (ShowOnlyInnerProperties))`
- L211 _public member_ `FDatasmithStaticMeshImportOptions StaticMeshOptions;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = Process, meta = (ShowOnlyInnerProperties))`
- L213 _public function_ `bool CanIncludeAnimation() const`

#### struct `FDatasmithTessellationOptions`  
`struct FDatasmithTessellationOptions`  
_L224-313_
- reflection: `USTRUCT(BlueprintType)`
- L228 _public function_ `FDatasmithTessellationOptions(float InChordTolerance = 0.2f, float InMaxEdgeLength = 0.0f, float InNormalTolerance = 20.0f, EDatasmithCADStitchingTechnique InStitchingTechnique = EDatasmithCADStitchingTechnique::StitchingSew) : ChordTolerance(InChordTolerance) , MaxEdgeLength(InMaxEdgeLength) , NormalTolerance(InNormalTolerance) , StitchingTechnique(InStitchingTechnique)`
- L242 _public member_ `float ChordTolerance;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Geometry & Tessellation Options", meta = (Units = cm, ToolTip = "Maximum distance between any generated triangle and the original surface. Smaller values make more triangles.", ClampMin = "0.005"))` — Maximum distance between any point on a triangle generated by the tessellation process and the actual surface. The lower the value the more triangles. Default value is 0.2, minimal value is 0.005 cm.
- L251 _public member_ `float MaxEdgeLength;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (Units = cm, DisplayName = "Max Edge Length", ToolTip = "Maximum length of any edge in the generated triangles. Smaller values make more triangles.", ClampMin = "0.0"))` — Maximum length of edges of triangles generated by the tessellation process. The length is in scene/model unit. The smaller the more triangles are generated. Value of 0 means no constraint on length of edges Default value is 0 to disable this criteria, and 1. cm is its minimal value if enable.
- L259 _public member_ `float NormalTolerance;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (Units = deg, ToolTip = "Maximum angle between adjacent triangles. Smaller values make more triangles.", ClampMin = "5.0", ClampMax = "90.0"))` — Maximum angle between the normal of two triangles generated by the tessellation process. The angle is expressed in degree. The smaller the more triangles are generated. Default value is 20 degrees, min value is 5 degrees.
- L270 _public member_ `EDatasmithCADStitchingTechnique StitchingTechnique;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (ToolTip = "Stitching technique applied on model before tessellation. Sewing could impact number of objects."))` — Stitching technique applied on neighbouring surfaces before tessellation. None : No stitching applied. This is the default. Sewing : Connects surfaces which physically share a boundary but not topologically within a set of objects. This technique can modify the structure of the model by removing and adding objects. Healing : Connects surfaces which physically share a boundary but not topologically within an object.
- L272 _public member_ `bool bUseCADKernel = false;`
- L282 _protected member_ `double GeometricTolerance = 0.001;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (Units = cm, ToolTip = "Tolerance used to determine if a surface should be tessellated or not."))` — Tolerance used to determine if a surface should be tessellate or not. Any surface which is narrower than the geometric tolerance in one of the iso direction will not be tessellated Value is in centimeter
- L288 _protected member_ `double StitchingTolerance = 0.001;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (Units = cm, ToolTip = "Tolerance used to determine if two surfaces should be stitched.", editCondition = "StitchingTechnique!=EDatasmithCADStitchingTechnique::StitchingNone"))` — Tolerance used to determine if two surfaces should be stitched.
- L291 _public function_ `bool operator == (const FDatasmithTessellationOptions& Other) const`
- L301 _public function_ `uint32 GetHash() const`
- L311 _public function_ `double GetGeometricTolerance( bool bInMillimeter = false ) const` — Helper functions to get geometrical values in the right unit, cm (native) or mm
- L312 _public function_ `double GetStitchingTolerance( bool bInMillimeter = false ) const`

#### struct `FDatasmithRetessellationOptions`  
`struct FDatasmithRetessellationOptions : public FDatasmithTessellationOptions`  
_L316-339_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDatasmithTessellationOptions`
- L320 _public function_ `FDatasmithRetessellationOptions(float InChordTolerance = 0.2f, float InMaxEdgeLength = 0.0f, float InNormalTolerance = 20.0f, EDatasmithCADStitchingTechnique InStitchingTechnique = EDatasmithCADStitchingTechnique::StitchingSew, EDatasmithCADRetessellationRule InRetessellationRule = EDatasmithCADRetessellationRule::All) : FDatasmithTessellationOptions(InChordTolerance, InMaxEdgeLength, InNormalTolerance, InStitchingTechnique) , RetessellationRule(InRetessellationRule)`
- L327 _public member_ `EDatasmithCADRetessellationRule RetessellationRule = EDatasmithCADRetessellationRule::All;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Retessellation Options", meta = (ToolTip = "Regenerate deleted surfaces during retesselate or ignore them"))`
- L330 _public function_ `void operator = (const FDatasmithTessellationOptions& Other)`

#### class `UDatasmithOptionsBase`  
`class UDatasmithOptionsBase : public UObject`  
_L349-355_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class for all import options in datasmith. Notable feature: forces a full serialization of its properties (by opposition to the standard delta serialization which stores only the diff wrt the CDO) The intent is to store the exact options used in a previous import.
- L354 _public prototype_ `void Serialize(FStructuredArchive::FRecord Record) override;`

#### class `UDatasmithCommonTessellationOptions`  
`class UDatasmithCommonTessellationOptions : public UDatasmithOptionsBase`  
_L359-366_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = EditorPerProjectUserSettings)`
- inherits: `UDatasmithOptionsBase`
- L365 _public member_ `FDatasmithTessellationOptions Options;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Geometry & Tessellation Options", meta = (ShowOnlyInnerProperties))`

#### class `UDatasmithImportOptions`  
`class UDatasmithImportOptions : public UDatasmithOptionsBase`  
_L369-437_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings, HideCategories = ("NotVisible"))`
- inherits: `UDatasmithOptionsBase`
- L376 _public member_ `EDatasmithImportSearchPackagePolicy SearchPackagePolicy;` — `UPROPERTY(Transient, AdvancedDisplay)` — Specifies where to search for assets
- L380 _public member_ `EDatasmithImportAssetConflictPolicy MaterialConflictPolicy;` — `UPROPERTY(Transient, AdvancedDisplay)` — Specifies what to do when material conflicts
- L384 _public member_ `EDatasmithImportAssetConflictPolicy TextureConflictPolicy;` — `UPROPERTY(Transient, AdvancedDisplay)` — Specifies what to do when texture conflicts
- L388 _public member_ `EDatasmithImportActorPolicy StaticMeshActorImportPolicy;` — `UPROPERTY(Transient, AdvancedDisplay)` — Specifies what to do when actor conflicts
- L392 _public member_ `EDatasmithImportActorPolicy LightImportPolicy;` — `UPROPERTY(Transient, AdvancedDisplay)` — Specifies what to do when light conflicts
- L396 _public member_ `EDatasmithImportActorPolicy CameraImportPolicy;` — `UPROPERTY(Transient, AdvancedDisplay)` — Specifies what to do when material conflicts
- L400 _public member_ `EDatasmithImportActorPolicy OtherActorImportPolicy;` — `UPROPERTY(Transient, AdvancedDisplay)` — Specifies what to do when actor conflicts
- L404 _public member_ `EDatasmithImportMaterialQuality MaterialQuality;` — `UPROPERTY(Transient, AdvancedDisplay)` — Specifies what to do when material conflicts
- L407 _public member_ `FDatasmithImportBaseOptions BaseOptions;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Options", meta = (ShowOnlyInnerProperties))`
- L411 _public member_ `FDatasmithReimportOptions ReimportOptions;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Reimport", meta = (ShowOnlyInnerProperties))` — Options specific to the reimport process
- L415 _public member_ `FString FileName;` — `UPROPERTY(BlueprintReadWrite, Category = "NotVisible")` — Name of the imported file without its path
- L419 _public member_ `FString FilePath;` — `UPROPERTY(BlueprintReadWrite, Category = "NotVisible")` — Full path of the imported file
- L422 _public member_ `FString SourceUri;` — `UPROPERTY(BlueprintReadWrite, Category = "NotVisible")`
- L425 _public member_ `FMD5Hash SourceHash;` — The hash of the source referenced by SourceUri
- L428 _public member_ `bool bUseSameOptions;` — Whether to use or not the same options when loading multiple files. Default false
- L430 _public prototype_ `void UpdateNotDisplayedConfig( bool bIsAReimport );`
- L434 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATASMITHCONTENT_API`
- L216 _namespace_ `namespace UE`
- L216 _namespace_ `namespace DatasmithTessellation` (scope `UE`)
- L218 _variable_ `const double MinTessellationAngle = 5;` (scope `UE::DatasmithTessellation`)
- L219 _variable_ `const double MinTessellationEdgeLength = 1.;` (scope `UE::DatasmithTessellation`)
- L220 _variable_ `const double MinTessellationChord = 0.005;` (scope `UE::DatasmithTessellation`) — Usual value in CAD software is 0.02 cm

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithImportedSequencesActor.h` (Public)


#### class `ADatasmithImportedSequencesActor`  
`class ADatasmithImportedSequencesActor : public AActor`  
_L13-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L19 _public prototype_ `ADatasmithImportedSequencesActor(const FObjectInitializer& Init);`
- L22 _public member_ `TArray<TObjectPtr<ULevelSequence>> ImportedSequences;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ImportedSequences")`
- L25 _public prototype_ `void PlayLevelSequence(ULevelSequence* SequenceToPlay);` — `UFUNCTION(BlueprintCallable, Category="ImportedSequences")`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithScene.h` (Public)


#### class `UDatasmithScene`  
`class UDatasmithScene : public UObject, public IInterface_AssetUserData`  
_L23-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IInterface_AssetUserData`
- L28 _public prototype_ `UDatasmithScene();`
- L30 _public prototype_ `virtual ~UDatasmithScene();`
- L35 _public member_ `TObjectPtr<class UDatasmithSceneImportData> AssetImportData;` — `UPROPERTY(EditAnywhere, Instanced, Category=ImportSettings)` — Importing data and options used for this Datasmith scene
- L38 _public member_ `int32 BulkDataVersion;` — `UPROPERTY()` — Need an external version number because loading of the bulk data is handled externally
- L40 _public member_ `FByteBulkData DatasmithSceneBulkData;`
- L44 _public member_ `TMap< FName, TSoftObjectPtr< UStaticMesh > > StaticMeshes;` — `UPROPERTY(VisibleAnywhere, Category="Datasmith", AdvancedDisplay)` — Map of all the static meshes related to this Datasmith Scene
- L49 _public member_ `TMap< FName, TSoftObjectPtr< UObject > > Clothes;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")` — `UPROPERTY(VisibleAnywhere, Category="Datasmith", AdvancedDisplay)` — Map of all the cloth related to this Datasmith Scene
- L53 _public member_ `TMap< FName, TSoftObjectPtr< UTexture > > Textures;` — `UPROPERTY(VisibleAnywhere, Category="Datasmith", AdvancedDisplay)` — Map of all the textures related to this Datasmith Scene
- L57 _public member_ `TMap< FName, TSoftObjectPtr< UMaterialFunction > > MaterialFunctions;` — `UPROPERTY(VisibleAnywhere, Category="Datasmith", AdvancedDisplay)` — Map of all the material functions related to this Datasmith Scene
- L61 _public member_ `TMap< FName, TSoftObjectPtr< UMaterialInterface > > Materials;` — `UPROPERTY(VisibleAnywhere, Category="Datasmith", AdvancedDisplay)` — Map of all the materials related to this Datasmith Scene
- L65 _public member_ `TMap< FName, TSoftObjectPtr< ULevelSequence > > LevelSequences;` — `UPROPERTY(VisibleAnywhere, Category="Datasmith", AdvancedDisplay)` — Map of all the level sequences related to this Datasmith Scene
- L69 _public member_ `TMap< FName, TSoftObjectPtr< ULevelVariantSets > > LevelVariantSets;` — `UPROPERTY(VisibleAnywhere, Category="Datasmith", AdvancedDisplay)` — Map of all the level variant sets related to this Datasmith Scene
- L73 _public member_ `TArray< TObjectPtr<UAssetUserData> > AssetUserData;` — `UPROPERTY()` — Array of user data stored with the asset
- L77 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L79 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L83 _public prototype_ `void RegisterPreWorldRenameCallback();` — Register the DatasmithScene to the PreWorldRename callback as needed
- L86 _public prototype_ `virtual void AddAssetUserData( UAssetUserData* InUserData ) override;`
- L87 _public prototype_ `virtual void RemoveUserDataOfClass( TSubclassOf<UAssetUserData> InUserDataClass ) override;`
- L88 _public prototype_ `virtual UAssetUserData* GetAssetUserDataOfClass( TSubclassOf<UAssetUserData> InUserDataClass ) override;`
- L89 _public prototype_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override;`
- L95 _private prototype_ `void OnPreWorldRename(UWorld* World, const TCHAR* InName, UObject* NewOuter, ERenameFlags Flags, bool& bShouldFailRename);` — Called before a world is renamed
- L97 _private member_ `bool bPreWorldRenameCallbackRegistered;`
- L101 _public prototype_ `virtual void Serialize( FArchive& Archive ) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithSceneActor.h` (Public)


#### class `ADatasmithSceneActor`  
`class ADatasmithSceneActor : public AActor`  
_L14-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L20 _public prototype_ `ADatasmithSceneActor();`
- L23 _public member_ `TObjectPtr<class UDatasmithScene> Scene;` — `UPROPERTY(VisibleAnywhere, Category="Datasmith")`
- L27 _public member_ `TMap< FName, TSoftObjectPtr< AActor > > RelatedActors;` — `UPROPERTY(VisibleAnywhere, Category="Datasmith", AdvancedDisplay)` — Map of all the actors related to this Datasmith Scene
- L30 _public prototype_ `void BeginDestroy() override;` — Clean up delegates before destruction
- L35 _private prototype_ `void EnsureDatasmithIdsForRelatedActors();` — For backward compatibility with UE <= 4.21
- L38 _private prototype_ `void PostLoad() override;` — Backward compatibility fix will happen on PostLoad.
- L41 _private prototype_ `void OnMapChange(uint32 MapChangeFlags);` — We need this to monitor when a sub-level is loaded
- L44 _private prototype_ `void OnActorDeleted(AActor* ActorDeleted);` — Cleans the invalid Soft Object Ptr
- L47 _private prototype_ `void OnAssetPostImport(UFactory* InFactory, UObject* ActorAdded);` — Reattach newly imported actors if they've been moved / cut and pasted
- L49 _private prototype_ `void RegisterDelegates();`
- L50 _private prototype_ `void UnregisterDelegates();`
- L52 _private member_ `FDelegateHandle OnActorDeletedDelegateHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithActorTemplate.h` (Public)


#### class `UDatasmithActorTemplate`  
`class UDatasmithActorTemplate : public UDatasmithObjectTemplate`  
_L15-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- desc: hold template informations common to all AActors.
- L21 _public function_ `UDatasmithActorTemplate() : UDatasmithObjectTemplate(true)`
- L27 _public member_ `TSet<FName> Layers;` — `UPROPERTY()` — Layers this actor belongs to. (see AActor::Layers)
- L31 _public member_ `TSet<FName> Tags;` — `UPROPERTY()` — Tags on this actor. (see AActor::Tags)
- L33 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L34 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L35 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`
- L39 _public function_ `template< typename T > static T* GetActor( UObject* Object )` — Helper function to get the typed Actor from either a component or an actor
- L45 _public function_ `template< typename T > static const T* GetActor( const UObject* Object )`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithAreaLightActorTemplate.h` (Public)


#### class `UDatasmithAreaLightActorTemplate`  
`class UDatasmithAreaLightActorTemplate : public UDatasmithObjectTemplate`  
_L15-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- L21 _public member_ `EDatasmithAreaLightActorType LightType;` — `UPROPERTY()`
- L24 _public member_ `EDatasmithAreaLightActorShape LightShape;` — `UPROPERTY()`
- L27 _public member_ `FVector2D Dimensions;` — `UPROPERTY()`
- L30 _public member_ `FLinearColor Color;` — `UPROPERTY()`
- L33 _public member_ `float Intensity;` — `UPROPERTY()`
- L36 _public member_ `ELightUnits IntensityUnits;` — `UPROPERTY()`
- L39 _public member_ `float Temperature;` — `UPROPERTY()`
- L42 _public member_ `TSoftObjectPtr< class UTextureLightProfile > IESTexture;` — `UPROPERTY()`
- L45 _public member_ `bool bUseIESBrightness;` — `UPROPERTY()`
- L48 _public member_ `float IESBrightnessScale;` — `UPROPERTY()`
- L51 _public member_ `FRotator Rotation;` — `UPROPERTY()`
- L54 _public member_ `float SourceRadius;` — `UPROPERTY()`
- L57 _public member_ `float SourceLength;` — `UPROPERTY()`
- L60 _public member_ `float AttenuationRadius;` — `UPROPERTY()`
- L63 _public prototype_ `UDatasmithAreaLightActorTemplate();`
- L65 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L66 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L67 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithCineCameraActorTemplate.h` (Public)


#### struct `FDatasmithCameraLookatTrackingSettingsTemplate`  
`struct FDatasmithCameraLookatTrackingSettingsTemplate`  
_L14-34_
- reflection: `USTRUCT()`
- L20 _public member_ `uint8 bEnableLookAtTracking : 1;` — `UPROPERTY()`
- L23 _public member_ `uint8 bAllowRoll : 1;` — `UPROPERTY()`
- L26 _public member_ `TSoftObjectPtr< AActor > ActorToTrack;` — `UPROPERTY()`
- L29 _public prototype_ `FDatasmithCameraLookatTrackingSettingsTemplate();`
- L31 _public prototype_ `void Apply( FCameraLookatTrackingSettings* Destination, FDatasmithCameraLookatTrackingSettingsTemplate* PreviousTemplate );`
- L32 _public prototype_ `void Load( const FCameraLookatTrackingSettings& Source );`
- L33 _public prototype_ `bool Equals( const FDatasmithCameraLookatTrackingSettingsTemplate& Other ) const;`

#### class `UDatasmithCineCameraActorTemplate`  
`class UDatasmithCineCameraActorTemplate : public UDatasmithObjectTemplate`  
_L37-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- L42 _public function_ `UDatasmithCineCameraActorTemplate() : UDatasmithObjectTemplate(true)`
- L47 _public member_ `FDatasmithCameraLookatTrackingSettingsTemplate LookatTrackingSettings;` — `UPROPERTY()`
- L49 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L50 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L51 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithCineCameraComponentTemplate.h` (Public)


#### struct `FDatasmithCameraFilmbackSettingsTemplate`  
`struct FDatasmithCameraFilmbackSettingsTemplate`  
_L18-31_
- reflection: `USTRUCT()`
- L23 _public member_ `float SensorWidth = 0.0f;` — `UPROPERTY()`
- L26 _public member_ `float SensorHeight = 0.0f;` — `UPROPERTY()`
- L28 _public prototype_ `void Apply( FCameraFilmbackSettings* Destination, const FDatasmithCameraFilmbackSettingsTemplate* PreviousTemplate );`
- L29 _public prototype_ `void Load( const FCameraFilmbackSettings& Source );`
- L30 _public prototype_ `bool Equals( const FDatasmithCameraFilmbackSettingsTemplate& Other ) const;`

#### struct `FDatasmithCameraLensSettingsTemplate`  
`struct FDatasmithCameraLensSettingsTemplate`  
_L34-44_
- reflection: `USTRUCT()`
- L39 _public member_ `float MaxFStop = 0.0f;` — `UPROPERTY()`
- L41 _public prototype_ `void Apply( FCameraLensSettings* Destination, const FDatasmithCameraLensSettingsTemplate* PreviousTemplate );`
- L42 _public prototype_ `void Load( const FCameraLensSettings& Source );`
- L43 _public prototype_ `bool Equals( const FDatasmithCameraLensSettingsTemplate& Other ) const;`

#### struct `FDatasmithCameraFocusSettingsTemplate`  
`struct FDatasmithCameraFocusSettingsTemplate`  
_L47-60_
- reflection: `USTRUCT()`
- L52 _public member_ `ECameraFocusMethod FocusMethod = ECameraFocusMethod::DoNotOverride;` — `UPROPERTY()`
- L55 _public member_ `float ManualFocusDistance = 0.0f;` — `UPROPERTY()`
- L57 _public prototype_ `void Apply( FCameraFocusSettings* Destination, const FDatasmithCameraFocusSettingsTemplate* PreviousTemplate );`
- L58 _public prototype_ `void Load( const FCameraFocusSettings& Source );`
- L59 _public prototype_ `bool Equals( const FDatasmithCameraFocusSettingsTemplate& Other ) const;`

#### struct `FDatasmithPostProcessSettingsTemplate`  
`struct FDatasmithPostProcessSettingsTemplate`  
_L63-116_
- reflection: `USTRUCT()`
- L69 _public member_ `uint32 bOverride_WhiteTemp:1;` — `UPROPERTY()`
- L72 _public member_ `uint32 bOverride_ColorSaturation:1;` — `UPROPERTY()`
- L75 _public member_ `uint32 bOverride_VignetteIntensity:1;` — `UPROPERTY()`
- L78 _public member_ `uint32 bOverride_AutoExposureMethod:1;` — `UPROPERTY()`
- L81 _public member_ `uint32 bOverride_CameraISO:1;` — `UPROPERTY()`
- L84 _public member_ `uint32 bOverride_CameraShutterSpeed:1;` — `UPROPERTY()`
- L87 _public member_ `uint8 bOverride_DepthOfFieldFstop:1;` — `UPROPERTY()`
- L90 _public member_ `float WhiteTemp = 0.0f;` — `UPROPERTY()`
- L93 _public member_ `float VignetteIntensity = 0.0f;` — `UPROPERTY()`
- L96 _public member_ `FVector4 ColorSaturation;` — `UPROPERTY()`
- L102 _public member_ `float CameraISO = 0.0f;` — `UPROPERTY()`
- L105 _public member_ `float CameraShutterSpeed = 0.0f;` — `UPROPERTY()`
- L108 _public member_ `float DepthOfFieldFstop = 0.0f;` — `UPROPERTY()`
- L111 _public prototype_ `FDatasmithPostProcessSettingsTemplate();`
- L113 _public prototype_ `void Apply( struct FPostProcessSettings* Destination, const FDatasmithPostProcessSettingsTemplate* PreviousTemplate );`
- L114 _public prototype_ `void Load( const FPostProcessSettings& Source );`
- L115 _public prototype_ `bool Equals( const FDatasmithPostProcessSettingsTemplate& Other ) const;`

#### class `UDatasmithCineCameraComponentTemplate`  
`class UDatasmithCineCameraComponentTemplate : public UDatasmithObjectTemplate`  
_L119-145_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- L125 _public member_ `FDatasmithCameraFilmbackSettingsTemplate FilmbackSettings;` — `UPROPERTY()`
- L128 _public member_ `FDatasmithCameraLensSettingsTemplate LensSettings;` — `UPROPERTY()`
- L131 _public member_ `FDatasmithCameraFocusSettingsTemplate FocusSettings;` — `UPROPERTY()`
- L134 _public member_ `float CurrentFocalLength = 0.0f;` — `UPROPERTY()`
- L137 _public member_ `float CurrentAperture = 0.0f;` — `UPROPERTY()`
- L140 _public member_ `FDatasmithPostProcessSettingsTemplate PostProcessSettings;` — `UPROPERTY()`
- L142 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L143 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L144 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithDecalComponentTemplate.h` (Public)


#### class `UDatasmithDecalComponentTemplate`  
`class UDatasmithDecalComponentTemplate : public UDatasmithObjectTemplate`  
_L12-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- L17 _public prototype_ `UDatasmithDecalComponentTemplate();`
- L20 _public member_ `int32 SortOrder;` — `UPROPERTY()`
- L23 _public member_ `FVector DecalSize;` — `UPROPERTY()`
- L26 _public member_ `TObjectPtr<class UMaterialInterface> Material;` — `UPROPERTY()`
- L28 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L29 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L30 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithLandscapeTemplate.h` (Public)


#### class `UDatasmithLandscapeTemplate`  
`class UDatasmithLandscapeTemplate : public UDatasmithObjectTemplate`  
_L14-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- L19 _public function_ `UDatasmithLandscapeTemplate() : UDatasmithObjectTemplate(true)`
- L24 _public member_ `TObjectPtr<UMaterialInterface> LandscapeMaterial;` — `UPROPERTY()`
- L27 _public member_ `int32 StaticLightingLOD;` — `UPROPERTY()`
- L29 _public prototype_ `virtual UObject* UpdateObject(UObject* Destination, bool bForce = false) override;`
- L30 _public prototype_ `virtual void Load(const UObject* Source) override;`
- L31 _public prototype_ `virtual bool Equals(const UDatasmithObjectTemplate* Other) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithLightComponentTemplate.h` (Public)


#### class `UDatasmithLightComponentTemplate`  
`class UDatasmithLightComponentTemplate : public UDatasmithObjectTemplate`  
_L12-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- L17 _public prototype_ `UDatasmithLightComponentTemplate();`
- L20 _public member_ `uint8 bVisible : 1;` — `UPROPERTY()`
- L23 _public member_ `uint32 CastShadows : 1;` — `UPROPERTY()`
- L26 _public member_ `uint32 bUseTemperature : 1;` — `UPROPERTY()`
- L29 _public member_ `uint32 bUseIESBrightness : 1;` — `UPROPERTY()`
- L32 _public member_ `float Intensity;` — `UPROPERTY()`
- L35 _public member_ `float Temperature;` — `UPROPERTY()`
- L38 _public member_ `float IESBrightnessScale;` — `UPROPERTY()`
- L41 _public member_ `FLinearColor LightColor;` — `UPROPERTY()`
- L44 _public member_ `TObjectPtr<class UMaterialInterface> LightFunctionMaterial;` — `UPROPERTY()`
- L47 _public member_ `TObjectPtr<class UTextureLightProfile> IESTexture;` — `UPROPERTY()`
- L49 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L50 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L51 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithMaterialInstanceTemplate.h` (Public)


#### struct `FDatasmithStaticParameterSetTemplate`  
`struct FDatasmithStaticParameterSetTemplate`  
_L20-33_
- reflection: `USTRUCT()`
- L26 _public member_ `TMap< FName, bool > StaticSwitchParameters;` — `UPROPERTY()`
- L29 _public prototype_ `void Apply( UMaterialInstanceConstant* Destination, FDatasmithStaticParameterSetTemplate* PreviousTemplate );`
- L30 _public prototype_ `void Load( const UMaterialInstanceConstant& Source, bool bOverridesOnly = true );`
- L31 _public prototype_ `void LoadRebase( const UMaterialInstanceConstant& Source, const FDatasmithStaticParameterSetTemplate& ComparedTemplate, const FDatasmithStaticParameterSetTemplate* MergedTemplate);`
- L32 _public prototype_ `bool Equals( const FDatasmithStaticParameterSetTemplate& Other ) const;`

#### class `UDatasmithMaterialInstanceTemplate`  
`class UDatasmithMaterialInstanceTemplate : public UDatasmithObjectTemplate`  
_L40-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- desc: Applies material instance data to a material instance if it hasn't changed since the last time we've applied a template. Supports Scalar parameters, Vector parameters, Texture parameters and Static parameters
- L45 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L46 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L47 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`
- L50 _public member_ `TSoftObjectPtr< UMaterialInterface > ParentMaterial;` — `UPROPERTY()`
- L53 _public member_ `TMap< FName, float > ScalarParameterValues;` — `UPROPERTY()`
- L56 _public member_ `TMap< FName, FLinearColor > VectorParameterValues;` — `UPROPERTY()`
- L59 _public member_ `TMap< FName, TSoftObjectPtr< UTexture > > TextureParameterValues;` — `UPROPERTY()`
- L62 _public member_ `FDatasmithStaticParameterSetTemplate StaticParameters;` — `UPROPERTY()`
- L65 _protected prototype_ `virtual void LoadRebase(const UObject* Source, const UDatasmithObjectTemplate* BaseTemplate, bool bMergeTemplate) override;`
- L66 _protected prototype_ `virtual bool HasSameBase(const UDatasmithObjectTemplate* Other) const override;`
- L70 _protected prototype_ `virtual void LoadAll(const UObject* Source);` — Loads all the source object properties into the template, regardless if they are different from the default values or not.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithObjectTemplate.h` (Public)


#### class `UDatasmithObjectTemplate`  
`class UDatasmithObjectTemplate : public UObject`  
_L12-83_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UObject`
- L18 _public function_ `UDatasmithObjectTemplate() : UObject() , bIsActorTemplate(false)`
- L24 _public function_ `UDatasmithObjectTemplate(bool bInIsActorTemplate) : UObject() , bIsActorTemplate(bInIsActorTemplate)`
- L36 _public function_ `virtual UObject* UpdateObject(UObject* Destination, bool bForce = false)` — Updates the Destination object with the values stored in the object template @param Destination	The object to apply this template to @param bForce		Force the update of the template on all properties, even if they were changed from the previous template values. @return The UObject on which the object template could be set on. Returns nullptr if the update has failed
- L41 _public function_ `virtual void Load( const UObject* Source )` — Fills this template properties with the values from the Source object.
- L46 _public function_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const` — Returns if this template equals another template of the same type.
- L55 _public prototype_ `void Apply( UObject* Destination, bool bForce = false );` — Updates the Destination object with the values stored in the object template If the update is successful, replaces the object template of the Destination object with itself @param Destination	The object to apply this template to @param bForce		Force the update of the template on all properties, even if they were changed from the previous template values.
- L58 _public member_ `const bool bIsActorTemplate = false;` — Is this template for an actor
- L67 _public prototype_ `static UDatasmithObjectTemplate* GetDifference(UObject* Destination, UDatasmithObjectTemplate* Source);` — Returns the difference between the object template of the Destination object and the SourceTemplate object template @param Destination		The object to get the difference from @param SourceTemplate	The object template to compare to.
- L77 _protected function_ `virtual void LoadRebase(const UObject* Source, const UDatasmithObjectTemplate* BaseTemplate, bool bLoadDiff = false)` — Fills this template properties with the values from the Source object after rebasing (changing its parent) with the base object defined in BaseTemplate. @param Source			The object to get the template from. @param BaseTemplate		The template which is using a different base object. Its base will be used to rebase the template. @param bMergeTemplate	If True, the loaded template will merge the changes contained in the BaseTemplate as well.
- L82 _protected function_ `virtual bool HasSameBase(const UDatasmithObjectTemplate* Other) const` — Returns if this template has the same base as another template of the same type, this indicates if their diffs can be safely compared.

#### struct `FDatasmithObjectTemplateUtils`  
`struct FDatasmithObjectTemplateUtils`  
_L106-143_
- L108 _public prototype_ `static bool HasObjectTemplates( UObject* Outer );`
- L110 _public prototype_ `static class UDatasmithAssetUserData* FindOrCreateDatasmithUserData( UObject* Outer );`
- L112 _public prototype_ `static TMap< TSubclassOf< UDatasmithObjectTemplate >, TObjectPtr<UDatasmithObjectTemplate> >* FindOrCreateObjectTemplates( UObject* Outer );`
- L114 _public prototype_ `static UDatasmithObjectTemplate* GetObjectTemplate( UObject* Outer, TSubclassOf< UDatasmithObjectTemplate > Subclass );`
- L117 _public function_ `template < typename T > static T* GetObjectTemplate( UObject* Outer )`
- L122 _public prototype_ `static void SetObjectTemplate( UObject* Outer, UDatasmithObjectTemplate* ObjectTemplate );`
- L135 _public prototype_ `static TSet<FName> ThreeWaySetMerge(const TSet<FName>& OldSet, const TSet<FName>& CurrentSet, const TSet<FName>& NewSet);` — Based on existing data, last import and current import, deduce resulting data that reflects User work. - Use values from the new set - Keep User-added values - Ignore User-removed values @param OldSet        Previously imported set @param CurrentSet    Data after user edition @param NewSet        Data being imported @return              Merged data set
- L141 _public prototype_ `static bool SetsEquals(const TSet<FName>& Left, const TSet<FName>& Right);` — Compares two sets for equality. Order has no influence. @note: LegacyCompareEqual also check for order

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATASMITHCONTENT_API`
- L87 _macro_ `#define DATASMITHOBJECTTEMPLATE_CONDITIONALSET(MemberName, Destination, PreviousTemplate) \` — Sets Destination->MemberName with the value of MemberName only if PreviousTemplate is null or has the same value for MemberName as the Destination. The goal is to set a new value only if it wasn't changed (overriden) in the Destination.
- L93 _macro_ `#define DATASMITHOBJECTTEMPLATE_CONDITIONALSET_ACCESSORS(MemberName, Destination, PreviousTemplate) \`
- L100 _macro_ `#define DATASMITHOBJECTTEMPLATE_CONDITIONALSETSOFTOBJECTPTR(MemberName, Destination, PreviousTemplate) \` — Specialized version of DATASMITHOBJECTTEMPLATE_CONDITIONALSET to handle SoftObjectPtr to Ptr assignment

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithPointLightComponentTemplate.h` (Public)


#### class `UDatasmithPointLightComponentTemplate`  
`class UDatasmithPointLightComponentTemplate : public UDatasmithObjectTemplate`  
_L13-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- L18 _public prototype_ `UDatasmithPointLightComponentTemplate();`
- L21 _public member_ `ELightUnits IntensityUnits;` — `UPROPERTY()`
- L24 _public member_ `float SourceRadius;` — `UPROPERTY()`
- L27 _public member_ `float SourceLength;` — `UPROPERTY()`
- L30 _public member_ `float AttenuationRadius;` — `UPROPERTY()`
- L32 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L33 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L34 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithPostProcessVolumeTemplate.h` (Public)


#### class `UDatasmithPostProcessVolumeTemplate`  
`class UDatasmithPostProcessVolumeTemplate : public UDatasmithObjectTemplate`  
_L16-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- desc: Represents an APostProcessVolume
- L21 _public function_ `UDatasmithPostProcessVolumeTemplate() : UDatasmithObjectTemplate(true)`
- L26 _public member_ `FDatasmithPostProcessSettingsTemplate Settings;` — `UPROPERTY()`
- L29 _public member_ `uint32 bEnabled:1;` — `UPROPERTY()`
- L32 _public member_ `uint32 bUnbound:1;` — `UPROPERTY()`
- L34 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L35 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L36 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithSceneComponentTemplate.h` (Public)


#### class `UDatasmithSceneComponentTemplate`  
`class UDatasmithSceneComponentTemplate : public UDatasmithObjectTemplate`  
_L13-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- L20 _public member_ `FTransform RelativeTransform;` — `UPROPERTY()`
- L23 _public member_ `TEnumAsByte< EComponentMobility::Type > Mobility;` — `UPROPERTY()`
- L26 _public member_ `TSoftObjectPtr< USceneComponent > AttachParent;` — `UPROPERTY()`
- L29 _public member_ `bool bVisible;` — `UPROPERTY()`
- L32 _public member_ `bool bCastShadow = true;` — `UPROPERTY()`
- L35 _public member_ `TSet<FName> Tags;` — `UPROPERTY()`
- L37 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L38 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L39 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithSkyLightComponentTemplate.h` (Public)


#### class `UDatasmithSkyLightComponentTemplate`  
`class UDatasmithSkyLightComponentTemplate : public UDatasmithObjectTemplate`  
_L14-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- L19 _public prototype_ `UDatasmithSkyLightComponentTemplate();`
- L22 _public member_ `TEnumAsByte< ESkyLightSourceType > SourceType;` — `UPROPERTY()`
- L25 _public member_ `int32 CubemapResolution;` — `UPROPERTY()`
- L28 _public member_ `TObjectPtr<class UTextureCube> Cubemap;` — `UPROPERTY()`
- L30 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L31 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L32 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithSpotLightComponentTemplate.h` (Public)


#### class `UDatasmithSpotLightComponentTemplate`  
`class UDatasmithSpotLightComponentTemplate : public UDatasmithObjectTemplate`  
_L10-26_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectTemplate`
- L15 _public prototype_ `UDatasmithSpotLightComponentTemplate();`
- L18 _public member_ `float InnerConeAngle;` — `UPROPERTY()`
- L21 _public member_ `float OuterConeAngle;` — `UPROPERTY()`
- L23 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L24 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L25 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithStaticMeshComponentTemplate.h` (Public)


#### class `UDatasmithStaticMeshComponentTemplate`  
`class UDatasmithStaticMeshComponentTemplate : public UDatasmithObjectTemplate`  
_L12-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- L19 _public member_ `TObjectPtr<class UStaticMesh> StaticMesh;` — `UPROPERTY()`
- L22 _public member_ `TArray< TObjectPtr<class UMaterialInterface> > OverrideMaterials;` — `UPROPERTY()`
- L24 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L25 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L26 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATASMITHCONTENT_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/ObjectTemplates/DatasmithStaticMeshTemplate.h` (Public)


#### struct `FDatasmithMeshBuildSettingsTemplate`  
`struct FDatasmithMeshBuildSettingsTemplate`  
_L17-58_
- reflection: `USTRUCT()`
- L23 _public member_ `uint8 bUseMikkTSpace:1;` — `UPROPERTY()`
- L26 _public member_ `uint8 bRecomputeNormals:1;` — `UPROPERTY()`
- L29 _public member_ `uint8 bRecomputeTangents:1;` — `UPROPERTY()`
- L32 _public member_ `uint8 bRemoveDegenerates:1;` — `UPROPERTY()`
- L35 _public member_ `uint8 bUseHighPrecisionTangentBasis:1;` — `UPROPERTY()`
- L38 _public member_ `uint8 bUseFullPrecisionUVs:1;` — `UPROPERTY()`
- L41 _public member_ `uint8 bGenerateLightmapUVs:1;` — `UPROPERTY()`
- L44 _public member_ `int32 MinLightmapResolution;` — `UPROPERTY()`
- L47 _public member_ `int32 SrcLightmapIndex;` — `UPROPERTY()`
- L50 _public member_ `int32 DstLightmapIndex;` — `UPROPERTY()`
- L53 _public prototype_ `FDatasmithMeshBuildSettingsTemplate();`
- L55 _public prototype_ `void Apply( FMeshBuildSettings* Destination, FDatasmithMeshBuildSettingsTemplate* PreviousTemplate );`
- L56 _public prototype_ `void Load( const FMeshBuildSettings& Source );`
- L57 _public prototype_ `bool Equals( const FDatasmithMeshBuildSettingsTemplate& Other ) const;`

#### struct `FDatasmithStaticMaterialTemplate`  
`struct FDatasmithStaticMaterialTemplate`  
_L61-77_
- reflection: `USTRUCT()`
- L66 _public prototype_ `FDatasmithStaticMaterialTemplate();`
- L69 _public member_ `FName MaterialSlotName;` — `UPROPERTY()`
- L72 _public member_ `TObjectPtr<class UMaterialInterface> MaterialInterface;` — `UPROPERTY()`
- L74 _public prototype_ `void Apply( FStaticMaterial* Destination, FDatasmithStaticMaterialTemplate* PreviousTemplate );`
- L75 _public prototype_ `void Load( const FStaticMaterial& Source );`
- L76 _public prototype_ `bool Equals( const FDatasmithStaticMaterialTemplate& Other ) const;`

#### struct `FDatasmithMeshSectionInfoTemplate`  
`struct FDatasmithMeshSectionInfoTemplate`  
_L80-93_
- reflection: `USTRUCT()`
- L85 _public prototype_ `FDatasmithMeshSectionInfoTemplate();`
- L88 _public member_ `int32 MaterialIndex;` — `UPROPERTY()`
- L90 _public prototype_ `void Apply( FMeshSectionInfo* Destination, FDatasmithMeshSectionInfoTemplate* PreviousTemplate );`
- L91 _public prototype_ `void Load( const FMeshSectionInfo& Source );`
- L92 _public prototype_ `bool Equals( const FDatasmithMeshSectionInfoTemplate& Other ) const;`

#### struct `FDatasmithMeshSectionInfoMapTemplate`  
`struct FDatasmithMeshSectionInfoMapTemplate`  
_L96-106_
- reflection: `USTRUCT()`
- L101 _public member_ `TMap< uint32, FDatasmithMeshSectionInfoTemplate > Map;` — `UPROPERTY()`
- L103 _public prototype_ `void Apply( FMeshSectionInfoMap* Destination, FDatasmithMeshSectionInfoMapTemplate* PreviousTemplate );`
- L104 _public prototype_ `void Load( const FMeshSectionInfoMap& Source );`
- L105 _public prototype_ `bool Equals( const FDatasmithMeshSectionInfoMapTemplate& Other ) const;`

#### class `UDatasmithStaticMeshTemplate`  
`class UDatasmithStaticMeshTemplate : public UDatasmithObjectTemplate`  
_L109-132_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDatasmithObjectTemplate`
- L114 _public prototype_ `virtual UObject* UpdateObject( UObject* Destination, bool bForce = false ) override;`
- L115 _public prototype_ `virtual void Load( const UObject* Source ) override;`
- L116 _public prototype_ `virtual bool Equals( const UDatasmithObjectTemplate* Other ) const override;`
- L119 _public member_ `FDatasmithMeshSectionInfoMapTemplate SectionInfoMap;` — `UPROPERTY(VisibleAnywhere, Category = StaticMesh)`
- L122 _public member_ `int32 LightMapCoordinateIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = StaticMesh)`
- L125 _public member_ `int32 LightMapResolution = 0;` — `UPROPERTY(VisibleAnywhere, Category = StaticMesh)`
- L128 _public member_ `TArray< FDatasmithMeshBuildSettingsTemplate > BuildSettings;` — `UPROPERTY(VisibleAnywhere, Category = StaticMesh)`
- L131 _public member_ `TArray< FDatasmithStaticMaterialTemplate > StaticMaterials;` — `UPROPERTY(VisibleAnywhere, Category = StaticMesh)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATASMITHCONTENT_API`
