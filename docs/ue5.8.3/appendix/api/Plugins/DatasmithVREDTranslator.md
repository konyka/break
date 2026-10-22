# Plugins / DatasmithVREDTranslator

- module root: `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator`
- headers: 11; symbols: 158
- symbol kinds: class=12, delegate=1, enum=1, enumerator=7, function=4, macro=1, member=71, namespace=1, prototype=46, struct=12, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, DatasmithCore, EditorFramework, Engine, FBX, LevelSequence, MeshDescription, UnrealEd, XmlParser
- PublicDependencyModuleNames: DatasmithContent, DatasmithFBXTranslator, DatasmithTranslator

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Private/DatasmithVREDClipProcessor.h` (Private)


#### class `FDatasmithVREDClipProcessor`  
`class FDatasmithVREDClipProcessor`  
_L14-50_
- desc: Expects all clips and blocks to have unique names Expects DSIDs to have been removed from the curves already
- L17 _public function_ `FDatasmithVREDClipProcessor(TArray<FDatasmithFBXSceneAnimClip>& InClips, TArray<FDatasmithFBXSceneAnimNode>& InAnimNodes) : Clips(InClips) , AnimNodes(InAnimNodes)`
- L22 _public prototype_ `void Process();`
- L26 _private prototype_ `void BuildMaps();` — Prepare some common datastructures to help reference clips and blocks
- L33 _private prototype_ `void RecursivelyRemoveNestedClipDelay (FDatasmithFBXSceneAnimClip* Clip, float Delay);` — VRED has this strange convention where if a top level clip A plays a clip B starting at t=2s, clip B's contents will, themselves, all start at t=2s. This is not how the sequencer works (which would play clip B starts at t=0), so here we remove this "nested clip delay". It is also a lot handier because clips can't be reused in VRED, but subsequences can be reused in UnrealEditor
- L34 _private prototype_ `void RecursivelyPropagateFlippedToBlockUsages(FDatasmithFBXSceneAnimClip* Clip, bool bFlipped);`
- L38 _private prototype_ `TSharedPtr<FBlockToAdd> GetReversedDuplicateAnimBlock(FDatasmithFBXSceneAnimBlock* Block);` — Creates an AnimBlock that play as if 'Block' had been played back to front, and adds it to the correct AnimNode. Will just return an existing one, if it has been created for this Block already
- L41 _private member_ `TArray<FDatasmithFBXSceneAnimClip>& Clips;`
- L42 _private member_ `TArray<FDatasmithFBXSceneAnimNode>& AnimNodes;`
- L44 _private member_ `TSet<FString> AllNames;`
- L45 _private member_ `TMap<FString, FDatasmithFBXSceneAnimClip*> AllClips;`
- L46 _private member_ `TMap<FString, FDatasmithFBXSceneAnimBlock*> AllBlocks;`
- L47 _private member_ `TMap<FString, FDatasmithFBXSceneAnimClip*> TopLevelClips;`
- L48 _private member_ `TMap<FString, FDatasmithFBXSceneAnimNode*> BlockParents;`
- L49 _private member_ `TMap<FString, TSharedPtr<FBlockToAdd>> OldBlockToReversed;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Private/DatasmithVREDImportData.h` (Private)


#### enum `EVREDCppVariantType`  
`enum class EVREDCppVariantType : uint8`  
_L9-18_
- reflection: `UENUM(BlueprintType)`
- L11 _public enumerator_ `Unsupported`
- L12 _public enumerator_ `Camera`
- L13 _public enumerator_ `Geometry`
- L14 _public enumerator_ `VariantSet`
- L15 _public enumerator_ `Material`
- L16 _public enumerator_ `Transform`
- L17 _public enumerator_ `Light`

#### struct `FVREDCppVariantGeometryOption`  
`struct FVREDCppVariantGeometryOption`  
_L21-33_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L29 _public member_ `TArray<FString> VisibleMeshes;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L32 _public member_ `TArray<FString> HiddenMeshes;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

#### struct `FVREDCppVariantCameraOption`  
`struct FVREDCppVariantCameraOption`  
_L36-48_
- reflection: `USTRUCT(BlueprintType)`
- L41 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L44 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L47 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

#### struct `FVREDCppVariantMaterialOption`  
`struct FVREDCppVariantMaterialOption`  
_L51-57_
- reflection: `USTRUCT(BlueprintType)`
- L56 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

#### struct `FVREDCppVariantTransformOption`  
`struct FVREDCppVariantTransformOption`  
_L60-69_
- reflection: `USTRUCT(BlueprintType)`
- L65 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L68 _public member_ `FTransform Transform;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

#### struct `FVREDCppVariantLightOption`  
`struct FVREDCppVariantLightOption`  
_L72-78_
- reflection: `USTRUCT(BlueprintType)`
- L77 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

#### struct `FVREDCppVariantCamera`  
`struct FVREDCppVariantCamera`  
_L81-87_
- reflection: `USTRUCT(BlueprintType)`
- L86 _public member_ `TArray<FVREDCppVariantCameraOption> Options;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

#### struct `FVREDCppVariantGeometry`  
`struct FVREDCppVariantGeometry`  
_L90-99_
- reflection: `USTRUCT(BlueprintType)`
- L95 _public member_ `TArray<FString> TargetNodes;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L98 _public member_ `TArray<FVREDCppVariantGeometryOption> Options;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

#### struct `FVREDCppVariantSet`  
`struct FVREDCppVariantSet`  
_L102-120_
- reflection: `USTRUCT(BlueprintType)`
- L107 _public member_ `TArray<FString> TargetVariantNames;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L110 _public member_ `TArray<FString> ChosenOptions;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L113 _public member_ `FString VariantSetGroupName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L116 _public member_ `TArray<FString> AnimClips;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L119 _public member_ `bool bSequentialAnimation = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

#### struct `FVREDCppVariantMaterial`  
`struct FVREDCppVariantMaterial`  
_L123-132_
- reflection: `USTRUCT(BlueprintType)`
- L128 _public member_ `TArray<FString> TargetNodes;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L131 _public member_ `TArray<FVREDCppVariantMaterialOption> Options;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

#### struct `FVREDCppVariantTransform`  
`struct FVREDCppVariantTransform`  
_L135-144_
- reflection: `USTRUCT(BlueprintType)`
- L140 _public member_ `TArray<FString> TargetNodes;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L143 _public member_ `TArray<FVREDCppVariantTransformOption> Options;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

#### struct `FVREDCppVariantLight`  
`struct FVREDCppVariantLight`  
_L147-156_
- reflection: `USTRUCT(BlueprintType)`
- L152 _public member_ `TArray<FString> TargetNodes;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L155 _public member_ `TArray<FVREDCppVariantLightOption> Options;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

#### struct `FVREDCppVariant`  
`struct FVREDCppVariant : public FTableRowBase`  
_L159-186_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FTableRowBase`
- L164 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L167 _public member_ `EVREDCppVariantType Type = EVREDCppVariantType::Unsupported;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L170 _public member_ `FVREDCppVariantCamera Camera;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L173 _public member_ `FVREDCppVariantGeometry Geometry;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L176 _public member_ `FVREDCppVariantMaterial Material;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L179 _public member_ `FVREDCppVariantSet VariantSet;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L182 _public member_ `FVREDCppVariantTransform Transform;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`
- L185 _public member_ `FVREDCppVariantLight Light;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VRED)`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Private/DatasmithVREDImportOptions.h` (Private)


#### class `UDatasmithVREDImportOptions`  
`class UDatasmithVREDImportOptions : public UDatasmithFBXImportOptions`  
_L13-47_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, HideCategories=(Debug))`
- inherits: `UDatasmithFBXImportOptions`
- L19 _public member_ `bool bImportMats;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category= AssetImporting, meta=(DisplayName="Import materials file", ToolTip="Uses the *.mats file saved alongside the exported FBX for a more accurate material reproduction"))`
- L22 _public member_ `FFilePath MatsPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Materials file path", EditCondition = "bImportMats", ToolTip="Path to the *.mats file. By default it will search for a *.mats file in the same folder as the FBX file, with the same base filename as it", FilePathFilter="mats"))`
- L25 _public member_ `bool bImportVar;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category= AssetImporting, meta=(DisplayName="Import variants file", ToolTip="Uses the *.var file saved alongside the exported FBX"))`
- L28 _public member_ `bool bCleanVar;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Clean variants", ToolTip="Removes empty variants, variant sets and invalid options. All discarded items will be logged to console."))`
- L31 _public member_ `FFilePath VarPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Variants file path", EditCondition = "bImportVar", ToolTip="Path to the *.var file. By default it will search for a *.var file in the same folder as the FBX file, with the same base filename as it", FilePathFilter="var"))`
- L34 _public member_ `bool bImportLightInfo;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Import lights file", ToolTip="Uses the *.lights file saved alongside the exported FBX to import extra information about lights not saved in the FBX file"))`
- L37 _public member_ `FFilePath LightInfoPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Lights file path", EditCondition = "bImportLightInfo", ToolTip="Path to the *.lights file. By default it will search for a *.light file in the same folder as the FBX file, with the same base filename as it", FilePathFilter="lights"))`
- L40 _public member_ `bool bImportClipInfo;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Import clips file", ToolTip="Uses the *.clips file saved alongside the exported FBX to import information about animation clips and blocks, mirroring VRED's animation system"))`
- L43 _public member_ `FFilePath ClipInfoPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="AnimClips file path", EditCondition = "bImportClipInfo", ToolTip="Path to the *.clips file. By default it will search for a *.clips file in the same folder as the FBX file, with the same base filename as it", FilePathFilter="clips"))`
- L46 _public prototype_ `void ResetPaths(const FString& InFBXFilename, bool bJustEmptyPaths=true);`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Private/DatasmithVREDImporter.h` (Private)


#### class `FDatasmithVREDImporter`  
`class FDatasmithVREDImporter : public FDatasmithFBXImporter`  
_L21-76_
- inherits: `FDatasmithFBXImporter`
- L24 _public prototype_ `FDatasmithVREDImporter(TSharedRef<IDatasmithScene>& OutScene, UDatasmithVREDImportOptions* InOptions);`
- L25 _public prototype_ `virtual ~FDatasmithVREDImporter();`
- L28 _public prototype_ `void SetImportOptions(UDatasmithVREDImportOptions* InOptions);` — Updates the used import options to InOptions
- L31 _public prototype_ `bool OpenFile(const FString& FilePath);` — Open and load a scene file.
- L34 _public prototype_ `bool SendSceneToDatasmith();` — Finalize import of the VRED scene into datasmith
- L37 _public prototype_ `void UnloadScene();` — Clean up any unused memory or data.
- L41 _private prototype_ `bool ParseFbxFile(const FString& FBXPath);` — Open and load a VRED .fbx scene file, placing its data in the context
- L44 _private prototype_ `void ParseAuxFiles(const FString& FBXPath);` — Open auxilliary .lights, .clips and/or .var files exported from VRED into the context
- L47 _private prototype_ `void ProcessScene();` — Perform processing of internal scene data for better performance after import
- L50 _private prototype_ `bool CheckNodeType(const TSharedPtr<FDatasmithFBXSceneNode>& Node);` — Checks if the NodeType flag has a combination supported for this plugin
- L52 _private prototype_ `TSharedPtr<IDatasmithActorElement> ConvertNode(const TSharedPtr<FDatasmithFBXSceneNode>& Node);`
- L54 _private prototype_ `TSharedPtr<IDatasmithBaseMaterialElement> ConvertMaterial(const TSharedPtr<FDatasmithFBXSceneMaterial>& Material);`
- L59 _private prototype_ `TSharedPtr<IDatasmithLevelSequenceElement> ConvertAnimBlock(const FCombinedAnimBlock& CombinedBlock);` — Converts an anim block into IDatasmithLevelSequenceElement.	Each AnimBlock is a set of transform/visibility tracks. Note that if no AnimClips are present, these AnimBlocks are a completely arbitrary selection of tracks, as that is the best we can possibly do
- L63 _private member_ `TSharedRef<IDatasmithScene> DatasmithScene;` — Output Datasmith scene
- L66 _private member_ `const UDatasmithVREDImportOptions* ImportOptions;` — All options to configure importer
- L69 _private member_ `TSet<FString> CreatedTextureElementPaths;` — Used to prevent us from needlessly importing the same texture multiple times
- L72 _private member_ `TArray<FDatasmithFBXSceneAnimClip> ParsedAnimClips;` — Things parsed from aux files
- L73 _private member_ `TArray<FDatasmithFBXSceneLight> ParsedLightsInfo;`
- L74 _private member_ `TArray<FDatasmithFBXSceneMaterial> ParsedMats;`
- L75 _private member_ `TArray<FVREDCppVariant> ParsedVariants;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Private/DatasmithVREDImporterAuxFiles.h` (Private)


#### class `FDatasmithVREDImportMatsResult`  
`class FDatasmithVREDImportMatsResult`  
_L16-20_
- L19 _public member_ `TArray<FDatasmithFBXSceneMaterial> Mats;`

#### class `FDatasmithVREDImportVariantsResult`  
`class FDatasmithVREDImportVariantsResult`  
_L22-29_
- L25 _public member_ `TArray<FVREDCppVariant> VariantSwitches;`
- L26 _public member_ `TSet<FString> SwitchObjects;`
- L27 _public member_ `TSet<FString> SwitchMaterialObjects;`
- L28 _public member_ `TSet<FString> TransformVariantObjects;`

#### class `FDatasmithVREDImportLightsResult`  
`class FDatasmithVREDImportLightsResult`  
_L31-35_
- L34 _public member_ `TArray<FDatasmithFBXSceneLight> Lights;`

#### class `FDatasmithVREDImportClipsResult`  
`class FDatasmithVREDImportClipsResult`  
_L37-45_
- L40 _public member_ `TArray<FDatasmithFBXSceneAnimNode> AnimNodes;`
- L41 _public member_ `TArray<FDatasmithFBXSceneAnimClip> AnimClips;`
- L42 _public member_ `float KeyTime = FLT_MAX;`
- L43 _public member_ `float BaseTime = 24.0f;`
- L44 _public member_ `float PlaybackSpeed = 24.0f;`

#### Free symbols / members of external scopes

- L47 _namespace_ `namespace FDatasmithVREDAuxFiles`
- L49 _prototype_ `FDatasmithVREDImportMatsResult ParseMatsFile(const FString& InFilePath);` (scope `FDatasmithVREDAuxFiles`)
- L50 _prototype_ `FDatasmithVREDImportVariantsResult ParseVarFile(const FString& InFilePath);` (scope `FDatasmithVREDAuxFiles`)
- L51 _prototype_ `FDatasmithVREDImportLightsResult ParseLightsFile(const FString& InFilePath);` (scope `FDatasmithVREDAuxFiles`)
- L52 _prototype_ `FDatasmithVREDImportClipsResult ParseClipsFile(const FString& InFilePath);` (scope `FDatasmithVREDAuxFiles`)

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Private/DatasmithVREDImporterMaterialSelector.h` (Private)


#### class `FDatasmithVREDImporterMaterialSelector`  
`class FDatasmithVREDImporterMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L12-26_
- inherits: `FDatasmithReferenceMaterialSelector`
- L15 _public prototype_ `FDatasmithVREDImporterMaterialSelector();`
- L17 _public prototype_ `virtual bool IsValid() const override;`
- L18 _public prototype_ `virtual const FDatasmithReferenceMaterial& GetReferenceMaterial( const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial ) const override;`
- L19 _public prototype_ `virtual void FinalizeMaterialInstance(const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial, UMaterialInstanceConstant* MaterialInstance) const override;`
- L22 _protected prototype_ `bool IsValidMaterialType( EDatasmithReferenceMaterialType InType ) const;`
- L25 _private member_ `TMap<FString, FDatasmithReferenceMaterial> ReferenceMaterials;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Private/DatasmithVREDLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithVREDImport, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithVREDImport, Log, All);`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Private/DatasmithVREDSceneProcessor.h` (Private)


#### class `FDatasmithVREDSceneProcessor`  
`class FDatasmithVREDSceneProcessor : public FDatasmithFBXSceneProcessor`  
_L12-40_
- inherits: `FDatasmithFBXSceneProcessor`
- L15 _public prototype_ `FDatasmithVREDSceneProcessor(FDatasmithFBXScene* InScene);`
- L18 _public prototype_ `void AddExtraLightInfo(TArray<FDatasmithFBXSceneLight>* InExtraLightsInfo);` — Add the extra info to the corresponding light nodes in the hierarchy
- L21 _public prototype_ `void AddExtraLightNodesRecursive(TSharedPtr<FDatasmithFBXSceneNode> Node);` — Recursively add missing info to lights nodes
- L24 _public prototype_ `void AddMatsMaterials(TArray<FDatasmithFBXSceneMaterial>* InMatsMaterials);` — Overwrite FBX imported materials with mats material parameters and info
- L27 _public prototype_ `void DecomposeRotationPivots();` — Decompose all scene nodes with nonzero RotationPivots using dummy actors, and handle their animations
- L30 _public prototype_ `void DecomposeRotationPivotsForNode(TSharedPtr<FDatasmithFBXSceneNode> Node, TMap<FString, FDatasmithFBXSceneAnimNode*>& NodeNameToAnimNode, TArray<FDatasmithFBXSceneAnimNode>& NewAnimNodes);` — Recursively decompose nodes with nonzero RotationPivots using dummy actors, and handle their animations
- L33 _public prototype_ `void DecomposeScalingPivots();` — Decompose all scene nodes with nonzero ScalingPivots using dummy actors, and handle their animations
- L36 _public prototype_ `void DecomposeScalingPivotsForNode(TSharedPtr<FDatasmithFBXSceneNode> Node, TMap<FString, FDatasmithFBXSceneAnimNode*>& NodeNameToAnimNode, TArray<FDatasmithFBXSceneAnimNode>& NewAnimNodes);` — Recursively decompose nodes with nonzero ScalingPivots using dummy actors, and handle their animations
- L39 _protected member_ `TMap<FString, TSharedPtr<FDatasmithFBXSceneLight>> ExtraLightsInfo;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Private/DatasmithVREDTranslator.h` (Private)


#### class `FDatasmithVREDTranslator`  
`class FDatasmithVREDTranslator : public IDatasmithTranslator`  
_L10-30_
- inherits: `IDatasmithTranslator`
- L13 _public function_ `virtual FName GetFName() const override`
- L15 _public prototype_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities) override;`
- L16 _public prototype_ `virtual bool IsSourceSupported(const FDatasmithSceneSource& Source) override;`
- L18 _public prototype_ `virtual bool LoadScene(TSharedRef<IDatasmithScene> OutScene) override;`
- L19 _public prototype_ `virtual void UnloadScene() override;`
- L21 _public prototype_ `virtual bool LoadStaticMesh(const TSharedRef<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload) override;`
- L22 _public prototype_ `virtual bool LoadLevelSequence(const TSharedRef<IDatasmithLevelSequenceElement> LevelSequenceElement, FDatasmithLevelSequencePayload& OutLevelSequencePayload) override;`
- L24 _public prototype_ `virtual void GetSceneImportOptions(TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L25 _public prototype_ `virtual void SetSceneImportOptions(const TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L28 _private member_ `TStrongObjectPtr<UDatasmithVREDImportOptions> ImportOptions;`
- L29 _private member_ `TSharedPtr<class FDatasmithVREDImporter> Importer;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Private/DatasmithVREDVariantConverter.h` (Private)


#### class `FVREDVariantConverter`  
`class FVREDVariantConverter`  
_L17-21_
- L20 _public prototype_ `static TSharedPtr<IDatasmithLevelVariantSetsElement> ConvertVariants(TArray<FVREDCppVariant>& Vars, FActorMap& ActorsByOriginalName, FMaterialMap& MaterialsByName);`

#### Free symbols / members of external scopes

- L14 _typedef_ `using FActorMap = TMap<FName, TArray<TSharedPtr<IDatasmithActorElement>>>;`
- L15 _typedef_ `using FMaterialMap = TMap<FName, TSharedPtr<IDatasmithBaseMaterialElement>>;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Public/DatasmithVREDTranslatorModule.h` (Public)


#### class `IDatasmithVREDTranslatorModule`  
`class IDatasmithVREDTranslatorModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L13 _public function_ `static inline IDatasmithVREDTranslatorModule& Get()`
- L18 _public function_ `static inline bool IsAvailable()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define VREDTRANSLATOR_MODULE_NAME TEXT("DatasmithVREDTranslator")`
