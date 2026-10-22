# Plugins / DatasmithDeltaGenTranslator

- module root: `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator`
- headers: 11; symbols: 210
- symbol kinds: class=15, delegate=1, enum=5, enumerator=26, function=3, macro=2, member=85, namespace=1, prototype=51, struct=19, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, DatasmithCore, EditorFramework, Engine, FBX, LevelSequence, MeshDescription, StaticMeshDescription, UnrealEd, XmlParser
- PublicDependencyModuleNames: DatasmithContent, DatasmithFBXTranslator, DatasmithTranslator

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Private/DatasmithDeltaGenAnimationInterpolator.h` (Private)


#### class `DeltaGen::FInterpolator`  
`class FInterpolator`  
_L14-43_
- desc: Utility to interpolate animation curves with different types of interpolations. This is used instead of other existing utilities as this allows interpolation directly with Bezier control points, without going through tangents and tangent weights
- L17 _public prototype_ `FInterpolator(const TArray<float>& InTimes, const TArray<FVector>& InValues);`
- L18 _public prototype_ `virtual ~FInterpolator();`
- L21 _public prototype_ `virtual FVector Evaluate(float Time) const = 0;` — Evaluates the interpolator for when the interpolation constant is Time
- L28 _public prototype_ `virtual FVector SolveForX(float X) const = 0;` — Finds an interpolated value that has a certain X. Requires that Values contains points that are function of X (so no more than one Value for each given x). DeltaGen enforces this constraint for timing curves
- L31 _public prototype_ `float GetMinTime() const;` — Gets the smallest stored Time value
- L34 _public prototype_ `float GetMaxTime() const;` — Gets the largest stored Time value
- L37 _public prototype_ `bool IsValid() const;` — Returns whether our arrays are valid for interpolation
- L40 _protected member_ `const TArray<float>& Times;`
- L41 _protected member_ `const TArray<FVector>& Values;`
- L42 _protected member_ `bool bIsValid;`

#### class `DeltaGen::FConstInterpolator`  
`class FConstInterpolator : public FInterpolator`  
_L45-51_
- inherits: `FInterpolator`
- L48 _public prototype_ `FConstInterpolator(const TArray<float>& InTimes, const TArray<FVector>& InValues);`
- L49 _public prototype_ `virtual FVector Evaluate(float Time) const override;`
- L50 _public prototype_ `virtual FVector SolveForX(float X) const override;`

#### class `DeltaGen::FLinearInterpolator`  
`class FLinearInterpolator : public FInterpolator`  
_L53-59_
- inherits: `FInterpolator`
- L56 _public prototype_ `FLinearInterpolator(const TArray<float>& InTimes, const TArray<FVector>& InValues);`
- L57 _public prototype_ `virtual FVector Evaluate(float Time) const override;`
- L58 _public prototype_ `virtual FVector SolveForX(float X) const override;`

#### class `DeltaGen::FCubicInterpolator`  
`class FCubicInterpolator : public FInterpolator`  
_L65-71_
- inherits: `FInterpolator`
- desc: Corresponds to DeltaGen's "Smooth" type of interpolation curve, which is the same as cubic interpolation, or concatenated N=4 Bezier curves (e.g. P0, P1, P2 and P3 for each segment)
- L68 _public prototype_ `FCubicInterpolator(const TArray<float>& InTimes, const TArray<FVector>& InValues);`
- L69 _public prototype_ `virtual FVector Evaluate(float Time) const override;`
- L70 _public prototype_ `virtual FVector SolveForX(float X) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace DeltaGen`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Private/DatasmithDeltaGenImportData.h` (Private)


#### enum `EObjectSetDataType`  
`enum class EObjectSetDataType : uint8`  
_L6-14_
- L8 _public enumerator_ `None`
- L9 _public enumerator_ `Translation`
- L10 _public enumerator_ `Rotation`
- L11 _public enumerator_ `Scaling`
- L12 _public enumerator_ `Visibility`
- L13 _public enumerator_ `Center`

#### enum `EDeltaGenVarDataVariantSwitchType`  
`enum class EDeltaGenVarDataVariantSwitchType : uint8`  
_L16-24_
- L18 _public enumerator_ `Unsupported`
- L19 _public enumerator_ `Camera`
- L20 _public enumerator_ `Geometry`
- L21 _public enumerator_ `Package`
- L22 _public enumerator_ `SwitchObject`
- L23 _public enumerator_ `ObjectSet`

#### struct `FDeltaGenVarDataGeometryVariant`  
`struct FDeltaGenVarDataGeometryVariant`  
_L26-31_
- L28 _public member_ `FString Name;`
- L29 _public member_ `TArray<FName> VisibleMeshes;`
- L30 _public member_ `TArray<FName> HiddenMeshes;`

#### struct `FDeltaGenVarDataCameraVariant`  
`struct FDeltaGenVarDataCameraVariant`  
_L33-38_
- L35 _public member_ `FString Name;`
- L36 _public member_ `FVector Location;`
- L37 _public member_ `FRotator Rotation;`

#### struct `FDeltaGenVarDataPackageVariant`  
`struct FDeltaGenVarDataPackageVariant`  
_L40-44_
- L42 _public member_ `FString Name;`
- L43 _public member_ `TArray<int32> SelectedVariants;` — variant id for variant selected in  each variant set(TargetVariantSet)

#### struct `FDeltaGenVarDataSwitchObjectVariant`  
`struct FDeltaGenVarDataSwitchObjectVariant`  
_L46-50_
- L48 _public member_ `FString Name;`
- L49 _public member_ `int32 Selection;`

#### struct `FDeltaGenVarDataObjectSetVariantValue`  
`struct FDeltaGenVarDataObjectSetVariantValue`  
_L52-57_
- L54 _public member_ `FName TargetNodeNameSanitized = NAME_None;`
- L55 _public member_ `EObjectSetDataType DataType = EObjectSetDataType::None;`
- L56 _public member_ `TArray<uint8> Data;`

#### struct `FDeltaGenVarDataObjectSetVariant`  
`struct FDeltaGenVarDataObjectSetVariant`  
_L59-63_
- L61 _public member_ `FString Name;`
- L62 _public member_ `TArray<FDeltaGenVarDataObjectSetVariantValue> Values;`

#### struct `FDeltaGenVarDataVariantSwitchCamera`  
`struct FDeltaGenVarDataVariantSwitchCamera`  
_L65-68_
- L67 _public member_ `TArray<FDeltaGenVarDataCameraVariant> Variants;`

#### struct `FDeltaGenVarDataVariantSwitchGeometry`  
`struct FDeltaGenVarDataVariantSwitchGeometry`  
_L70-74_
- L72 _public member_ `TArray<FName> TargetNodes;`
- L73 _public member_ `TArray<FDeltaGenVarDataGeometryVariant> Variants;`

#### struct `FDeltaGenVarDataVariantSwitchPackage`  
`struct FDeltaGenVarDataVariantSwitchPackage`  
_L76-80_
- L78 _public member_ `TArray<FString> TargetVariantSets;`
- L79 _public member_ `TArray<FDeltaGenVarDataPackageVariant> Variants;`

#### struct `FDeltaGenVarDataVariantSwitchSwitchObject`  
`struct FDeltaGenVarDataVariantSwitchSwitchObject`  
_L82-86_
- L84 _public member_ `FName TargetSwitchObject;`
- L85 _public member_ `TArray<FDeltaGenVarDataSwitchObjectVariant> Variants;`

#### struct `FDeltaGenVarDataVariantSwitchObjectSet`  
`struct FDeltaGenVarDataVariantSwitchObjectSet`  
_L88-91_
- L90 _public member_ `TArray<FDeltaGenVarDataObjectSetVariant> Variants;`

#### struct `FDeltaGenVarDataVariantSwitch`  
`struct FDeltaGenVarDataVariantSwitch : public FTableRowBase`  
_L93-105_
- inherits: `FTableRowBase`
- L95 _public member_ `FString Name;`
- L96 _public member_ `EDeltaGenVarDataVariantSwitchType Type;`
- L97 _public member_ `TMap<int32, int32> VariantIDToVariantIndex;`
- L98 _public member_ `TMap<int32, FString> VariantIDToVariantName;`
- L100 _public member_ `FDeltaGenVarDataVariantSwitchCamera Camera;`
- L101 _public member_ `FDeltaGenVarDataVariantSwitchGeometry Geometry;`
- L102 _public member_ `FDeltaGenVarDataVariantSwitchSwitchObject SwitchObject;`
- L103 _public member_ `FDeltaGenVarDataVariantSwitchPackage Package;`
- L104 _public member_ `FDeltaGenVarDataVariantSwitchObjectSet ObjectSet;`

#### struct `FDeltaGenVarData`  
`struct FDeltaGenVarData`  
_L107-110_
- L109 _public member_ `TArray<FDeltaGenVarDataVariantSwitch> VariantSwitches;`

#### struct `FDeltaGenPosDataState`  
`struct FDeltaGenPosDataState : public FTableRowBase`  
_L112-125_
- inherits: `FTableRowBase`
- L115 _public member_ `FString Name;` — Name of the actual state
- L118 _public member_ `TMap<FString, bool> States;` — Maps Actor name to whether it's on or off (visibility)
- L121 _public member_ `TMap<FName, int> Switches;` — Maps Actor name to a switch choice (index of the child that is visible)
- L124 _public member_ `TMap<FString, FString> Materials;` — Maps Actor name to a material name

#### struct `FDeltaGenPosData`  
`struct FDeltaGenPosData`  
_L127-130_
- L129 _public member_ `TArray<FDeltaGenPosDataState> States;`

#### enum `EDeltaGenTmlDataAnimationTrackType`  
`enum class EDeltaGenTmlDataAnimationTrackType : uint8`  
_L132-140_
- L134 _public enumerator_ `Unsupported = 0`
- L135 _public enumerator_ `Translation = 1`
- L136 _public enumerator_ `Rotation = 2`
- L137 _public enumerator_ `RotationDeltaGenEuler = 4`
- L138 _public enumerator_ `Scale = 8`
- L139 _public enumerator_ `Center = 16`

#### enum `EDeltaGenAnimationInterpolation`  
`enum class EDeltaGenAnimationInterpolation : uint8`  
_L143-149_
- L145 _public enumerator_ `Unsupported = 0`
- L146 _public enumerator_ `Constant = 1`
- L147 _public enumerator_ `Linear = 2`
- L148 _public enumerator_ `Cubic = 3`

#### struct `FDeltaGenTmlDataAnimationTrack`  
`struct FDeltaGenTmlDataAnimationTrack`  
_L151-161_
- L153 _public member_ `EDeltaGenTmlDataAnimationTrackType Type = EDeltaGenTmlDataAnimationTrackType::Unsupported;`
- L154 _public member_ `EDeltaGenAnimationInterpolation ValueInterpolation = EDeltaGenAnimationInterpolation::Unsupported;`
- L155 _public member_ `EDeltaGenAnimationInterpolation KeyInterpolation = EDeltaGenAnimationInterpolation::Unsupported;`
- L156 _public member_ `TArray<float> Keys;`
- L157 _public member_ `TArray<FVector> KeyControlPoints;`
- L158 _public member_ `TArray<FVector> Values;`
- L159 _public member_ `TArray<FVector> ValueControlPoints;`
- L160 _public member_ `float DelayMs = 0.0f;`

#### struct `FDeltaGenTmlDataTimelineAnimation`  
`struct FDeltaGenTmlDataTimelineAnimation`  
_L163-168_
- L165 _public member_ `FName TargetNode;`
- L166 _public member_ `TArray<FDeltaGenTmlDataAnimationTrack> Tracks;`
- L167 _public member_ `float DelayMs = 0.0f;`

#### struct `FDeltaGenTmlDataTimeline`  
`struct FDeltaGenTmlDataTimeline : public FTableRowBase`  
_L170-175_
- inherits: `FTableRowBase`
- L172 _public member_ `FString Name;`
- L173 _public member_ `float Framerate;`
- L174 _public member_ `TArray<FDeltaGenTmlDataTimelineAnimation> Animations;`

#### struct `FDeltaGenAnimationsData`  
`struct FDeltaGenAnimationsData`  
_L177-180_
- L179 _public member_ `TArray<FDeltaGenTmlDataTimeline> Timelines;`

#### Free symbols / members of external scopes

- L141 _prototype_ `ENUM_CLASS_FLAGS(EDeltaGenTmlDataAnimationTrackType);`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Private/DatasmithDeltaGenImportOptions.h` (Private)


#### enum `EShadowTextureMode`  
`enum class EShadowTextureMode : uint8`  
_L13-19_
- reflection: `UENUM()`
- L15 _public enumerator_ `Ignore UMETA(Tooltip="Ignore exported shadow textures")`
- L16 _public enumerator_ `AmbientOcclusion UMETA(Tooltip="Use shadow textures as ambient occlusion maps")`
- L17 _public enumerator_ `Multiplier UMETA(Tooltip="Use shadow textures as multipliers for base color and specular")`
- L18 _public enumerator_ `AmbientOcclusionAndMultiplier UMETA(Tooltip="Use shadow textures as ambient occlusion maps as well as multipliers for base color and specular")`

#### class `UDatasmithDeltaGenImportOptions`  
`class UDatasmithDeltaGenImportOptions : public UDatasmithFBXImportOptions`  
_L22-56_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, HideCategories=(Debug))`
- inherits: `UDatasmithFBXImportOptions`
- L28 _public member_ `bool bRemoveInvisibleNodes;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Processing, meta = (ToolTip = "Don't keep nodes that marked invisible in FBX(an din the original scene), except switch variants"))`
- L31 _public member_ `bool bSimplifyNodeHierarchy;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Processing, meta = (ToolTip = "Collapse nodes that have identity transform, have no mesh and not used in animation/variants/switches"))`
- L34 _public member_ `bool bImportVar;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Import Variants", ToolTip="import VAR files"))`
- L37 _public member_ `FFilePath VarPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Variants file path", EditCondition = "bImportVar", ToolTip="Path to the *.var file. By default it will search for a *.var file in the same folder as the FBX file, with the same base filename as it", FilePathFilter="var"))`
- L40 _public member_ `bool bImportPos;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Import POS States", ToolTip="import POS files"))`
- L43 _public member_ `FFilePath PosPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="POS file path", EditCondition = "bImportPos", ToolTip="Path to the *.pos file. By default it will search for a *.pos file in the same folder as the FBX file, with the same base filename as it", FilePathFilter="pos"))`
- L46 _public member_ `bool bImportTml;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Import TML Animations", ToolTip="import TML files"))`
- L49 _public member_ `FFilePath TmlPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="TML file path", EditCondition = "bImportTml", ToolTip="Path to the *.tml file. By default it will search for a *.tml file in the same folder as the FBX file, with the same base filename as it", FilePathFilter="tml"))`
- L52 _public member_ `EShadowTextureMode ShadowTextureMode;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=AssetImporting, meta=(DisplayName="Shadow Textures", ToolTip="How to handle shadow textures"))`
- L55 _public prototype_ `void ResetPaths(const FString& InFBXFilename, bool bJustEmptyPaths=true);`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Private/DatasmithDeltaGenImporter.h` (Private)


#### class `FDatasmithDeltaGenImporter`  
`class FDatasmithDeltaGenImporter : public FDatasmithFBXImporter`  
_L19-70_
- inherits: `FDatasmithFBXImporter`
- L22 _public prototype_ `FDatasmithDeltaGenImporter(TSharedRef<IDatasmithScene>& OutScene, UDatasmithDeltaGenImportOptions* InOptions);`
- L23 _public prototype_ `virtual ~FDatasmithDeltaGenImporter();`
- L26 _public prototype_ `void SetImportOptions(UDatasmithDeltaGenImportOptions* InOptions);` — Updates the used import options to InOptions
- L29 _public prototype_ `bool OpenFile(const FString& FilePath);` — Open and load a scene file.
- L32 _public prototype_ `bool SendSceneToDatasmith();` — Finalize import of the DeltaGen scene into the engine
- L35 _public prototype_ `void UnloadScene();` — Clean up any unused memory or data.
- L39 _private prototype_ `bool ParseFbxFile(const FString& FBXPath);` — Open and load a DeltaGen .fbx scene file, placing its data in the context
- L42 _private prototype_ `void ParseAuxFiles(const FString& FBXPath);` — Open auxilliary .lights, .clips and/or .var files exported from VRED into the context
- L45 _private prototype_ `bool ProcessScene();` — Perform processing of internal scene data for better performance after import
- L48 _private prototype_ `bool CheckNodeType(const TSharedPtr<FDatasmithFBXSceneNode>& Node);` — Checks if the NodeType flag has a combination supported for this plugin
- L50 _private prototype_ `TSharedPtr<IDatasmithActorElement> ConvertNode(const TSharedPtr<FDatasmithFBXSceneNode>& Node);`
- L52 _private prototype_ `TSharedPtr<IDatasmithBaseMaterialElement> ConvertMaterial(const TSharedPtr<FDatasmithFBXSceneMaterial>& Material);`
- L54 _private prototype_ `TSharedPtr<IDatasmithLevelSequenceElement> ConvertAnimationTimeline(const FDeltaGenTmlDataTimeline& TmlTimeline);`
- L58 _private member_ `TSharedRef<IDatasmithScene> DatasmithScene;` — Output Datasmith scene
- L61 _private member_ `const UDatasmithDeltaGenImportOptions* ImportOptions;` — All options to configure importer
- L64 _private member_ `TSet<FString> CreatedTextureElementPaths;` — Used to prevent us from needlessly importing the same texture multiple times
- L67 _private member_ `TArray<FDeltaGenVarDataVariantSwitch> VariantSwitches;` — Things parsed from aux files
- L68 _private member_ `TArray<FDeltaGenPosDataState> PosStates;`
- L69 _private member_ `TArray<FDeltaGenTmlDataTimeline> TmlTimelines;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Private/DatasmithDeltaGenImporterAuxFiles.h` (Private)


#### class `FDatasmithDeltaGenImportVariantsResult`  
`class FDatasmithDeltaGenImportVariantsResult`  
_L13-20_
- L16 _public member_ `TArray<FDeltaGenVarDataVariantSwitch> VariantSwitches;`
- L17 _public member_ `TSet<FName> SwitchObjects;`
- L18 _public member_ `TSet<FName> ToggleObjects;`
- L19 _public member_ `TSet<FName> ObjectSetObjects;`

#### class `FDatasmithDeltaGenImportTmlResult`  
`class FDatasmithDeltaGenImportTmlResult`  
_L22-27_
- L25 _public member_ `TArray<FDeltaGenTmlDataTimeline> Timelines;`
- L26 _public member_ `TSet<FName> AnimatedObjects;`

#### class `FDatasmithDeltaGenImportPosResult`  
`class FDatasmithDeltaGenImportPosResult`  
_L29-36_
- L32 _public member_ `TArray<FDeltaGenPosDataState> PosStates;`
- L33 _public member_ `TSet<FName> StateObjects;`
- L34 _public member_ `TSet<FName> SwitchObjects;`
- L35 _public member_ `TSet<FName> SwitchMaterialObjects;`

#### class `FDatasmithDeltaGenAuxFiles`  
`class FDatasmithDeltaGenAuxFiles`  
_L38-44_
- L41 _public prototype_ `static FDatasmithDeltaGenImportVariantsResult ParseVarFile(const FString& InFilePath);`
- L42 _public prototype_ `static FDatasmithDeltaGenImportPosResult ParsePosFile(const FString& InFilePath);`
- L43 _public prototype_ `static FDatasmithDeltaGenImportTmlResult ParseTmlFile(const FString& InFilePath);`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Private/DatasmithDeltaGenImporterMaterialSelector.h` (Private)


#### class `FDatasmithDeltaGenImporterMaterialSelector`  
`class FDatasmithDeltaGenImporterMaterialSelector : public FDatasmithReferenceMaterialSelector`  
_L12-26_
- inherits: `FDatasmithReferenceMaterialSelector`
- L15 _public prototype_ `FDatasmithDeltaGenImporterMaterialSelector();`
- L17 _public prototype_ `virtual bool IsValid() const override;`
- L18 _public prototype_ `virtual const FDatasmithReferenceMaterial& GetReferenceMaterial( const TSharedPtr< IDatasmithMaterialInstanceElement >& InDatasmithMaterial ) const override;`
- L21 _protected prototype_ `bool IsValidMaterialType( EDatasmithReferenceMaterialType InType ) const;`
- L24 _private member_ `FDatasmithReferenceMaterial ReferenceMaterial;`
- L25 _private member_ `FDatasmithReferenceMaterial ReferenceMaterialTransparent;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Private/DatasmithDeltaGenLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithDeltaGenImport, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithDeltaGenImport, Log, All);`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Private/DatasmithDeltaGenSceneProcessor.h` (Private)


#### class `FDatasmithDeltaGenSceneProcessor`  
`class FDatasmithDeltaGenSceneProcessor : public FDatasmithFBXSceneProcessor`  
_L12-28_
- inherits: `FDatasmithFBXSceneProcessor`
- L15 _public prototype_ `FDatasmithDeltaGenSceneProcessor(FDatasmithFBXScene* InScene);`
- L21 _public prototype_ `void SetupAOTextures(const TArray<FDirectoryPath>& TextureFolders);` — Fetches AO textures matching corresponding mesh names, and assigns them to materials used for each node. May create additional materials, as we may have to clone material instances to use different AO textures per mesh.
- L27 _public prototype_ `void DecomposePivots(TArray<FDeltaGenTmlDataTimeline>& Timelines);` — Decompose all scene nodes with nonzero rotation and scaling pivots using dummy actors, and handle their animations

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Private/DatasmithDeltaGenTranslator.h` (Private)


#### class `FDatasmithDeltaGenTranslator`  
`class FDatasmithDeltaGenTranslator : public IDatasmithTranslator`  
_L10-30_
- inherits: `IDatasmithTranslator`
- L13 _public function_ `virtual FName GetFName() const override`
- L15 _public prototype_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities) override;`
- L16 _public prototype_ `virtual bool IsSourceSupported(const FDatasmithSceneSource& Source);`
- L18 _public prototype_ `virtual bool LoadScene(TSharedRef<IDatasmithScene> OutScene) override;`
- L19 _public prototype_ `virtual void UnloadScene() override;`
- L21 _public prototype_ `virtual bool LoadStaticMesh(const TSharedRef<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload) override;`
- L22 _public prototype_ `virtual bool LoadLevelSequence(const TSharedRef<IDatasmithLevelSequenceElement> LevelSequenceElement, FDatasmithLevelSequencePayload& OutLevelSequencePayload) override;`
- L24 _public prototype_ `virtual void GetSceneImportOptions(TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L25 _public prototype_ `virtual void SetSceneImportOptions(const TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L28 _private member_ `TStrongObjectPtr<UDatasmithDeltaGenImportOptions> ImportOptions;`
- L29 _private member_ `TSharedPtr<class FDatasmithDeltaGenImporter> Importer;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Private/DatasmithDeltaGenVariantConverter.h` (Private)


#### class `FDeltaGenVariantConverter`  
`class FDeltaGenVariantConverter`  
_L20-24_
- L23 _public prototype_ `static TSharedPtr<IDatasmithLevelVariantSetsElement> ConvertVariants(TArray<FDeltaGenVarDataVariantSwitch>& Vars, TArray<FDeltaGenPosDataState>& PosStates, FActorMap& ActorsByOriginalName, FMaterialMap& MaterialsByName);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define SCENECAMERA_NAME TEXT("Camera")`
- L17 _typedef_ `using FActorMap = TMap<FName, TArray<TSharedPtr<IDatasmithActorElement>>>;`
- L18 _typedef_ `using FMaterialMap = TMap<FName, TSharedPtr<IDatasmithBaseMaterialElement>>;`

### `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Public/DatasmithDeltaGenTranslatorModule.h` (Public)


#### class `IDatasmithDeltaGenTranslatorModule`  
`class IDatasmithDeltaGenTranslatorModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L13 _public function_ `static inline IDatasmithDeltaGenTranslatorModule& Get()`
- L18 _public function_ `static inline bool IsAvailable()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define DELTAGENTRANSLATOR_MODULE_NAME TEXT("DatasmithDeltaGenTranslator")`
