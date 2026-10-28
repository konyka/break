# Plugins / USDExporter

- module root: `Plugins/Importers/USDImporter/Source/USDExporter`
- headers: 20; symbols: 353
- symbol kinds: class=18, macro=3, member=74, namespace=9, prototype=245, struct=4
- PrivateDependencyModuleNames: Analytics, AnalyticsBlueprintLibrary, CinematicCamera, Constraints, ControlRig, EditorStyle, GeometryCache, InputCore, JsonUtilities, Landscape, LevelSequence, LevelSequenceEditor, MaterialBaking, MaterialUtilities, MeshDescription, MeshUtilities, MessageLog, MovieScene, MovieSceneTracks, PropertyEditor, PythonScriptPlugin, RHI, RawMesh, RenderCore, Sequencer, Slate, SlateCore, StaticMeshDescription, USDClasses, USDStage, USDStageImporter, USDUtilities, UniversalObjectLocator, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Foliage, UnrealUSDWrapper

### `Plugins/Importers/USDImporter/Source/USDExporter/Private/LevelExporterUSDOptionsCustomization.h` (Private)


#### class `FLevelExporterUSDOptionsCustomization`  
`class FLevelExporterUSDOptionsCustomization : public IDetailCustomization`  
_L10-18_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/AnimSequenceExporterUSD.h` (Public)


#### class `UAnimSequenceExporterUSD`  
`class UAnimSequenceExporterUSD : public UExporter`  
_L12-23_
- reflection: `UCLASS()`
- inherits: `UExporter`
- L17 _public prototype_ `UAnimSequenceExporterUSD();`
- L20 _public prototype_ `virtual bool ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex = 0, uint32 PortFlags = 0) override;`

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/AnimSequenceExporterUSDOptions.h` (Public)


#### class `UAnimSequenceExporterUSDOptions`  
`class UAnimSequenceExporterUSDOptions : public UObject`  
_L17-50_
- reflection: `UCLASS(MinimalAPI, Config = Editor, Blueprintable)`
- inherits: `UObject`
- desc: Options for exporting skeletal mesh animations to USD format.
- L24 _public member_ `FUsdStageOptions StageOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Stage options", meta = (ShowOnlyInnerProperties))` — Export options to use for the layer where the animation is emitted
- L28 _public member_ `bool bExportPreviewMesh;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Mesh options")` — Whether to also export the skeletal mesh data of the preview mesh
- L38 _public member_ `FUsdMeshAssetOptions PreviewMeshOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Mesh options", meta = (ShowOnlyInnerProperties, EditCondition = bExportPreviewMesh))` — Export options to use for the preview mesh, if enabled
- L42 _public member_ `FUsdMetadataExportOptions MetadataOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Metadata options", meta = (ShowOnlyInnerProperties))` — Options to use when exporting UsdAssetUserData metadata to USD for all assets (including the preview mesh)
- L49 _public member_ `bool bReExportIdenticalAssets = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Collision", meta = (DisplayName = "Re-export Identical Assets"))` — Whether to export any asset (StaticMesh, Material, etc.) even if the existing file already describes the same version of a compatible asset. This is only checked when bReplaceIdentical is set on the asset export task. Otherwise we'll never overwrite files.

#### Free symbols / members of external scopes

- L52 _namespace_ `namespace UsdUtils`
- L54 _prototype_ `void AddAnalyticsAttributes(const UAnimSequenceExporterUSDOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L56 _prototype_ `void HashForAnimSequenceExport(const UAnimSequenceExporterUSDOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/GeometryCacheExporterUSD.h` (Public)


#### class `UGeometryCacheExporterUSD`  
`class UGeometryCacheExporterUSD : public UExporter`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UExporter`
- L15 _public prototype_ `UGeometryCacheExporterUSD();`
- L18 _public prototype_ `virtual bool ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex = 0, uint32 PortFlags = 0) override;`

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/GeometryCacheExporterUSDOptions.h` (Public)


#### class `UGeometryCacheExporterUSDOptions`  
`class UGeometryCacheExporterUSDOptions : public UObject`  
_L17-37_
- reflection: `UCLASS(MinimalAPI, Config = Editor, Blueprintable)`
- inherits: `UObject`
- desc: Options for exporting geometry caches to USD format.
- L23 _public member_ `FUsdStageOptions StageOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Stage options", meta = (ShowOnlyInnerProperties))`
- L26 _public member_ `FUsdMeshAssetOptions MeshAssetOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Mesh options", meta = (ShowOnlyInnerProperties))`
- L29 _public member_ `FUsdMetadataExportOptions MetadataOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Metadata options", meta = (ShowOnlyInnerProperties))`
- L36 _public member_ `bool bReExportIdenticalAssets = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Collision", meta = (DisplayName = "Re-export Identical Assets"))` — Whether to export any asset (StaticMesh, Material, etc.) even if the existing file already describes the same version of a compatible asset. This is only checked when bReplaceIdentical is set on the asset export task. Otherwise we'll never overwrite files.

#### Free symbols / members of external scopes

- L39 _namespace_ `namespace UsdUtils`
- L41 _prototype_ `void AddAnalyticsAttributes(const UGeometryCacheExporterUSDOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L43 _prototype_ `void HashForGeometryCacheExport(const UGeometryCacheExporterUSDOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/LevelExporterUSD.h` (Public)


#### class `ULevelExporterUSD`  
`class ULevelExporterUSD : public UExporter`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UExporter`
- L15 _public prototype_ `ULevelExporterUSD();`
- L18 _public prototype_ `virtual bool ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex = 0, uint32 PortFlags = 0) override;`

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/LevelExporterUSDOptions.h` (Public)


#### struct `FLevelExporterUSDOptionsInner`  
`struct FLevelExporterUSDOptionsInner`  
_L19-90_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public member_ `FString RootPrimName = TEXT("Roo` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Export options")` — Name of the single top-level prim that is emitted when exporting Levels and LevelSequences to USD
- L29 _public member_ `bool bSelectionOnly = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Export options")` — Whether to export only the selected actors, and assets used by them
- L33 _public member_ `bool bExportActorFolders = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Export options")` — Whether to use UE actor folders as empty prims
- L38 _public member_ `bool bIgnoreSequencerAnimations = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Export options")` — If true, and if we have a level sequence animating the level during export, it will revert any actor or component to its unanimated state before writing to USD
- L46 _public member_ `bool bExportFoliageOnActorsLayer = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Export options")` — By default foliage instances will be exported to the same layer as the component they were placed on in the editor. Enable this to instead export the foliage instances to the same layer as the foliage actor they belong to. This is useful if those foliage instances were placed with the "Place In Current Level" option.
- L50 _public member_ `FDirectoryPath AssetFolder;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Asset options")` — Where to place all the generated asset files
- L57 _public member_ `bool bExportToNestedSubFolders = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Asset options", AdvancedDisplay)` — Export the asset files in a folder structure that mirrors their Unreal project content folder structure. Warning: This can produce very long file paths that could cause issues depending on the operating system settings.
- L61 _public member_ `FUsdMeshAssetOptions AssetOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Asset options", meta = (ShowOnlyInnerProperties))` — Options to use for all exported assets when appropriate (e.g. static and skeletal meshes, materials, etc.)
- L65 _public member_ `FUsdMetadataExportOptions MetadataOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Metadata options", meta = (ShowOnlyInnerProperties))` — Options to use when exporting UsdAssetUserData metadata to USD for all assets (including the level itself)
- L69 _public member_ `int32 LowestLandscapeLOD = 0;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Landscape options", meta = (ClampMin = "0"))` — Lowest of the LOD indices to export landscapes with (use 0 for full resolution)
- L76 _public member_ `int32 HighestLandscapeLOD = 0;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Landscape options", meta = (ClampMin = "0"))` — Highest of the LOD indices to export landscapes with. Each value above 0 halves resolution. The max value depends on the number of components and sections per component of each landscape, and may be clamped.
- L80 _public member_ `FIntPoint LandscapeBakeResolution = FIntPoint(1024, 1024);` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Landscape options", meta = (ClampMin = "1"))` — Resolution to use when baking landscape materials into textures
- L85 _public member_ `bool bExportSublayers = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Sublayers", meta = (DisplayName = "Export Sublevels as Layers"))` — If true, will export sub-levels as separate layers (referenced as sublayers). If false, will collapse all sub-levels in a single exported root layer
- L89 _public member_ `TSet<FString> LevelsToIgnore;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Sublayers")` — Names of levels that should be ignored when collecting actors to export (e.g. "Persistent Level", "Level1", "MySubLevel", etc.)

#### class `ULevelExporterUSDOptions`  
`class ULevelExporterUSDOptions : public UObject`  
_L96-142_
- reflection: `UCLASS(MinimalAPI, Config = Editor, Blueprintable, HideCategories = Hidden)`
- inherits: `UObject`
- desc: Options for exporting levels to USD format.
- L103 _public member_ `FUsdStageOptions StageOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Stage options", meta = (ShowOnlyInnerProperties))` — Basic options about the stage to export
- L107 _public member_ `float StartTimeCode = 0.0f;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Stage options")` — StartTimeCode to be used for all exported layers
- L111 _public member_ `float EndTimeCode = 0.0f;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Stage options")` — EndTimeCode to be used for all exported layers
- L115 _public member_ `FLevelExporterUSDOptionsInner Inner;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Export settings", meta = (ShowOnlyInnerProperties))` — Inner struct that actually contains most of the export options
- L122 _public member_ `bool bReExportIdenticalLevelsAndSequences = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Collision", meta = (DisplayName = "Re-export Identical Levels and Sequences"))` — Whether to export levels and LevelSequences even if the existing files already describe the same versions of compatible assets. This is only checked when bReplaceIdentical is set on the asset export task. Otherwise we'll never overwrite files.
- L129 _public member_ `bool bReExportIdenticalAssets = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Collision", meta = (DisplayName = "Re-export Identical Assets"))` — Whether to export any asset (StaticMesh, Material, etc.) even if the existing file already describes the same version of a compatible asset. This is only checked when bReplaceIdentical is set on the asset export task. Otherwise we'll never overwrite files.
- L137 _public member_ `TWeakObjectPtr<UAssetExportTask> CurrentTask;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hidden)` — We temporarily stash our export task here as a way of passing our options down to the Python exporter, that does the actual level exporting. This is weak because we often use the CDO of this class directly, and we never want to permanently hold on to a particular export task
- L141 _private prototype_ `static TArray<FString> GetUsdExtensions();` — `UFUNCTION()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API USDEXPORTER_API`
- L144 _namespace_ `namespace UsdUtils`
- L146 _prototype_ `void AddAnalyticsAttributes(const FLevelExporterUSDOptionsInner& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L148 _prototype_ `void AddAnalyticsAttributes(const ULevelExporterUSDOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L150 _prototype_ `void HashForLevelExport(const FLevelExporterUSDOptionsInner& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)
- L152 _prototype_ `void HashForLevelExport(const ULevelExporterUSDOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/LevelSequenceExporterUSD.h` (Public)


#### class `ULevelSequenceExporterUsd`  
`class ULevelSequenceExporterUsd : public UExporter`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UExporter`
- L15 _public prototype_ `ULevelSequenceExporterUsd();`
- L18 _public prototype_ `virtual bool ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex = 0, uint32 PortFlags = 0) override;`

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/LevelSequenceExporterUSDOptions.h` (Public)


#### class `ULevelSequenceExporterUsdOptions`  
`class ULevelSequenceExporterUsdOptions : public UObject`  
_L19-107_
- reflection: `UCLASS(MinimalAPI, Config = Editor, Blueprintable)`
- inherits: `UObject`
- desc: Options for level sequences to the USD format.
- L26 _public member_ `FUsdStageOptions StageOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = USDSettings, meta = (ShowOnlyInnerProperties))` — Export options to use for the layer where the animation is emitted
- L32 _public member_ `float TimeCodesPerSecond = 24.0f;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Level Sequence")` — Value to bake all generated USD layers with
- L39 _public member_ `bool bOverrideExportRange = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Level Sequence")` — If checked will cause StartFrame and EndFrame to be used as the frame range for the level sequence export. If unchecked the existing playback range of each level sequence will be used instead.
- L43 _public member_ `int32 StartFrame = 0;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Level Sequence", meta = (EditCondition = "bOverrideExportRange"))` — Initial frame of the level sequence to bake out to USD (inclusive)
- L47 _public member_ `int32 EndFrame = 0;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Level Sequence", meta = (EditCondition = "bOverrideExportRange"))` — Final frame of the level sequence to bake out to USD (inclusive)
- L53 _public member_ `bool bSelectionOnly = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Level Sequence")` — Whether to export animations exclusively from selected actors or components
- L60 _public member_ `bool bExportSubsequencesAsLayers = true;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Level Sequence")` — The effect of subsequences is always included on the main exported layer, but if this option is true we will also export individual sublayers for each subsequence, so that they can be used by themselves if needed.
- L66 _public member_ `bool bExportLevel = true;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Level Sequence")` — Exports the provided level alongside the layer that represents the exported Level Sequence
- L78 _public member_ `bool bUseExportedLevelAsSublayer = true;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Level Sequence", meta = (EditCondition = "bExportLevel", DisplayName = "Use Exported Level as USD Sublayer"))` — If checked this will also add the exported level as a sublayer to the USD files emitted for all exported level sequences
- L86 _public member_ `bool bExportSeparatePrimsPerSpawnableInstance = true;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Level Sequence")` — If you have multiple instances of a same LevelSequence subsection with spawnables, setting this to true means each separate subsection instance will get its own individual copy of the prim exported for the spawnable. Setting this to false means that only a single prim will be exported for that spawnable, and shared for all subsection instances.
- L93 _public member_ `bool bReExportIdenticalLevelsAndSequences = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Collision", meta = (DisplayName = "Re-export Identical Levels and Sequences"))` — Whether to export levels and LevelSequences even if the existing files already describe the same versions of compatible assets. This is only checked when bReplaceIdentical is set on the asset export task. Otherwise we'll never overwrite files.
- L100 _public member_ `bool bReExportIdenticalAssets = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Collision", meta = (DisplayName = "Re-export Identical Assets"))` — Whether to export any asset (StaticMesh, Material, etc.) even if the existing file already describes the same version of a compatible asset. This is only checked when bReplaceIdentical is set on the asset export task. Otherwise we'll never overwrite files.
- L103 _public member_ `TWeakObjectPtr<UWorld> Level = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Export", meta = (EditCondition = "bExportLevel"))`
- L106 _public member_ `FLevelExporterUSDOptionsInner LevelExportOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Level Export", meta = (EditCondition = "bExportLevel"))`

#### Free symbols / members of external scopes

- L109 _namespace_ `namespace UsdUtils`
- L111 _prototype_ `void AddAnalyticsAttributes(const ULevelSequenceExporterUsdOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L113 _prototype_ `void HashForLevelSequenceExport(const ULevelSequenceExporterUsdOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/MaterialExporterUSD.h` (Public)


#### class `UMaterialExporterUsd`  
`class UMaterialExporterUsd : public UExporter`  
_L14-82_
- reflection: `UCLASS()`
- inherits: `UExporter`
- L19 _public prototype_ `UMaterialExporterUsd();`
- L22 _public prototype_ `virtual bool ExportBinary( UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex = 0, uint32 PortFlags = 0 ) override;`
- L42 _public prototype_ `static bool ExportMaterial( const UMaterialInterface& Material, const FUsdMaterialBakingOptions& Options, const FUsdMetadataExportOptions& MetadataOptions, const FFilePath& FilePath, bool bReplaceIdentical = true, bool bReExportIdenticalAssets = false, bool bIsAutomated = false );` — Exports a single material with given options to the target filepath as a UsdPreviewSurface USD asset. @param Material - Material to bake @param Options - Options to use when baking @param FilePath - Filepath of the destination file (e.g. "C:/MyFolder/Red.usda") @param ReplaceIdentical - Whether to overwrite the destination file in case it already exists @param bReExportIdenticalAssets - Whether to overwrite the destination file even if it already describes an up-to-date version of Material @param bIsAutomated - Whether the export is being done by a script or not. Just used for analytics @return Whether the export was successful or not.
- L71 _public prototype_ `static bool ExportMaterialsForStage( const TArray<UMaterialInterface*>& Materials, const FUsdMaterialBakingOptions& Options, const FUsdMetadataExportOptions& MetadataOptions, const FString& StageRootLayerPath, bool bIsAssetLayer, bool bUsePayload, bool bReplaceIdentical = true, bool bReExportIdenticalAssets = false, bool bIsAutomated = false );` — Exports the provided materials next to the stage's root layer on disk, replacing usages of unrealMaterials within `Stage` with references to the exported UsdPreviewMaterial assets. @param Materials - Materials to bake @param Options - Options to use when baking @param StageRootLayerPath - Path to the stage to replace the unrealMaterials attributes in. Note that this stage must not be opened in case you want this function to be able to replace exported materials with new files. All of it's layers will be traversed. The root layer folder on disk is used as destination folder for the baked materials @param bIsAssetLayer - True when we're exporting a single mesh/animation asset. False when we're exporting a level. Dictates minor behaviors when authoring the material binding relationships, e.g. whether we author them inside variants or not @param bUsePayload - Should be True if the Stage was exported using payload files to store the actual Mesh prims. Also dictates minor behaviors when authoring the material binding relationships. @param ReplaceIdentical - Whether to overwrite the destination files in case they already exist @param bReExportIdenticalAssets - Whether to overwrite the destination files even if they already describe up-to-date versions of Materials @param bIsAutomated - Whether the export is being done by a script or not. Just used for analytics @return Whether the export was successful or not.

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/MaterialExporterUSDOptions.h` (Public)


#### class `UMaterialExporterUSDOptions`  
`class UMaterialExporterUSDOptions : public UObject`  
_L18-35_
- reflection: `UCLASS(MinimalAPI, Config = Editor, Blueprintable)`
- inherits: `UObject`
- desc: Options for exporting materials to USD format. We use a dedicated object instead of reusing the MaterialBaking module as automated export tasks can only have one options object, and we need to also provide the textures directory.
- L24 _public member_ `FUsdMaterialBakingOptions MaterialBakingOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Material baking options", meta = (ShowOnlyInnerProperties))`
- L27 _public member_ `FUsdMetadataExportOptions MetadataOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Metadata options", meta = (ShowOnlyInnerProperties))`
- L34 _public member_ `bool bReExportIdenticalAssets = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Collision", meta = (DisplayName = "Re-export Identical Assets"))` — Whether to export any asset (StaticMesh, Material, etc.) even if the existing file already describes the same version of a compatible asset. This is only checked when bReplaceIdentical is set on the asset export task. Otherwise we'll never overwrite files.

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace UsdUtils`
- L39 _prototype_ `void AddAnalyticsAttributes(const UMaterialExporterUSDOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L41 _prototype_ `void HashForMaterialExport(const UMaterialExporterUSDOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/SkeletalMeshExporterUSD.h` (Public)


#### class `USkeletalMeshExporterUsd`  
`class USkeletalMeshExporterUsd : public UExporter`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UExporter`
- L15 _public prototype_ `USkeletalMeshExporterUsd();`
- L18 _public prototype_ `virtual bool ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex = 0, uint32 PortFlags = 0) override;`

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/SkeletalMeshExporterUSDOptions.h` (Public)


#### class `USkeletalMeshExporterUSDOptions`  
`class USkeletalMeshExporterUSDOptions : public UObject`  
_L17-37_
- reflection: `UCLASS(MinimalAPI, Config = Editor, Blueprintable)`
- inherits: `UObject`
- desc: Options for exporting skeletal meshes to USD format.
- L23 _public member_ `FUsdStageOptions StageOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Stage options", meta = (ShowOnlyInnerProperties))`
- L26 _public member_ `FUsdMeshAssetOptions MeshAssetOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Mesh options", meta = (ShowOnlyInnerProperties))`
- L29 _public member_ `FUsdMetadataExportOptions MetadataOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Metadata options", meta = (ShowOnlyInnerProperties))`
- L36 _public member_ `bool bReExportIdenticalAssets = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Collision", meta = (DisplayName = "Re-export Identical Assets"))` — Whether to export any asset (StaticMesh, Material, etc.) even if the existing file already describes the same version of a compatible asset. This is only checked when bReplaceIdentical is set on the asset export task. Otherwise we'll never overwrite files.

#### Free symbols / members of external scopes

- L39 _namespace_ `namespace UsdUtils`
- L41 _prototype_ `void AddAnalyticsAttributes(const USkeletalMeshExporterUSDOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L43 _prototype_ `void HashForSkeletalMeshExport(const USkeletalMeshExporterUSDOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/StaticMeshExporterUSD.h` (Public)


#### class `UStaticMeshExporterUsd`  
`class UStaticMeshExporterUsd : public UExporter`  
_L10-25_
- reflection: `UCLASS()`
- inherits: `UExporter`
- L16 _public prototype_ `static bool IsUsdAvailable();` — `UFUNCTION(BlueprintCallable, Category = "USD")`
- L19 _public prototype_ `UStaticMeshExporterUsd();`
- L22 _public prototype_ `virtual bool ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex = 0, uint32 PortFlags = 0) override;`

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/StaticMeshExporterUSDOptions.h` (Public)


#### class `UStaticMeshExporterUSDOptions`  
`class UStaticMeshExporterUSDOptions : public UObject`  
_L17-37_
- reflection: `UCLASS(MinimalAPI, Config = Editor, Blueprintable)`
- inherits: `UObject`
- desc: Options for exporting static meshes to USD format.
- L23 _public member_ `FUsdStageOptions StageOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Stage options", meta = (ShowOnlyInnerProperties))`
- L26 _public member_ `FUsdMeshAssetOptions MeshAssetOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Mesh options", meta = (ShowOnlyInnerProperties))`
- L29 _public member_ `FUsdMetadataExportOptions MetadataOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Metadata options", meta = (ShowOnlyInnerProperties))`
- L36 _public member_ `bool bReExportIdenticalAssets = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Collision", meta = (DisplayName = "Re-export Identical Assets"))` — Whether to export any asset (StaticMesh, Material, etc.) even if the existing file already describes the same version of a compatible asset. This is only checked when bReplaceIdentical is set on the asset export task. Otherwise we'll never overwrite files.

#### Free symbols / members of external scopes

- L39 _namespace_ `namespace UsdUtils`
- L41 _prototype_ `void AddAnalyticsAttributes(const UStaticMeshExporterUSDOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L43 _prototype_ `void HashForStaticMeshExport(const UStaticMeshExporterUSDOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/USDAssetOptions.h` (Public)


#### struct `FUsdMaterialBakingOptions`  
`struct FUsdMaterialBakingOptions`  
_L14-46_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `TArray<FPropertyEntry> Properties = { MP_BaseColor, MP_Metallic, MP_Specular, MP_Roughness, MP_Anisotropy, MP_EmissiveColor, MP_Opacity, MP_OpacityMask, MP_Normal, MP_Tangent, MP_SubsurfaceColor, MP_AmbientOcclusion};` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Material baking options")` — Properties which are supposed to be baked out for the material
- L41 _public member_ `bool bConstantColorAsSingleValue = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material baking options")` — When this is true and a baked texture contains a single flat color we will write out that color value directly on the USD layer and skip generating a texture
- L45 _public member_ `FDirectoryPath TexturesDir;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material baking options")` — Where baked textures are placed. Intentionally not a config as it's heavily dependent on where the stage is

#### struct `FUsdMeshAssetOptions`  
`struct FUsdMeshAssetOptions`  
_L49-110_
- reflection: `USTRUCT(BlueprintType)`
- L55 _public member_ `bool bUsePayload = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Mesh options")` — If true, the mesh data is exported to yet another "payload" file, and referenced via a payload composition arc
- L65 _public member_ `FString PayloadFormat = TEXT("usd` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Mesh options", meta = (EditCondition = bUsePayload, GetOptions = "USDExporter.LevelExporterUSDOptions.GetUsdExtensions"))` — USD format to use for exported payload files
- L69 _public member_ `bool bBakeMaterials = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Material options")` — Whether to bake the mesh's assigned material and export these as separate UsdPreviewSurface assets
- L74 _public member_ `bool bRemoveUnrealMaterials_DEPRECATED = false;` — `UE_DEPRECATED(all, "This option is now deprecated as UE material assignments are only visible in the 'unreal' render context anyway")` — `UPROPERTY(config, meta = (EditCondition = bBakeMaterials))` — Whether to remove the 'unrealMaterial' attribute after binding the corresponding baked material
- L77 _public member_ `FUsdMaterialBakingOptions MaterialBakingOptions;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Material options", meta = (EditCondition = bBakeMaterials))`
- L90 _public member_ `bool bExportStaticMeshSourceData = true;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Mesh options")` — If true it means we'll try exporting the source data when exporting static meshes. Not all meshes contain their source data though. If we fail to find any source data, we'll fall back to exporting the render data instead. If false it means we'll export the render data instead: This can be closer to what is seen on the viewport, but it can also be the most processed. For example, if the mesh has Nanite enabled this render data may be a much coarser version of the source mesh. This is only relevant for StaticMeshes, and has no effect on other mesh types (SkeletalMeshes, GeometryCaches, etc.)
- L94 _public member_ `bool bConvertSkeletalToNonSkeletal = false;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Mesh options")` — Whether to convert skeletal data to non-skeletal, ie. skeletal mesh to static mesh, anim sequence to animated mesh
- L98 _public member_ `int32 LowestMeshLOD = 0;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Mesh options", meta = (ClampMin = "0"))` — Lowest of the LOD indices to export static and skeletal meshes with (use 0 for full detail)
- L102 _public member_ `int32 HighestMeshLOD = MAX_MESH_LOD_COUNT - 1;` — `UPROPERTY(EditAnywhere, config, BlueprintReadWrite, Category = "Mesh options", meta = (ClampMin = "0"))` — Highest of the LOD indices to export static and skeletal meshes with
- L106 _public prototype_ `FUsdMeshAssetOptions() = default;` — We need this as clang would otherwise emit some warnings when generating these due to the usages of bRemoveUnrealMaterials
- L107 _public prototype_ `FUsdMeshAssetOptions(const FUsdMeshAssetOptions&) = default;`
- L108 _public prototype_ `FUsdMeshAssetOptions& operator=(const FUsdMeshAssetOptions&) = default;`

#### Free symbols / members of external scopes

- L112 _namespace_ `namespace UsdUtils`
- L114 _prototype_ `void AddAnalyticsAttributes(const FUsdMaterialBakingOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L116 _prototype_ `void AddAnalyticsAttributes(const FUsdMeshAssetOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L118 _prototype_ `void HashForMaterialExport(const FUsdMaterialBakingOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)
- L120 _prototype_ `void HashForMeshExport(const FUsdMeshAssetOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/USDConversionBlueprintContext.h` (Public)


#### class `UUsdConversionBlueprintContext`  
`class UUsdConversionBlueprintContext : public UObject`  
_L52-269_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "UsdConversionContext"))`
- inherits: `UObject`
- desc: Wraps the UnrealToUsd component conversion functions from the USDUtilities module so that they can be used by scripting languages. This is an instanceable object instead of just static functions so that the USDStage to use for the conversions can be provided and cached between function calls, which is helpful because we're forced to provide at most prim and layer file paths (as opposed to direct pxr::UsdPrim objects). We can't provide the pxr::UsdPrim object directly because USD types can't be part of C++ function signatures that are automatically exposed to scripting languages. Lucikly we can use UsdUtils' stage cache to make sure that C++ and e.g. Python are still referencing the same USD Stage in memory, so that we can e.g. use these functions to convert data within stages created via Python.
- L56 _private prototype_ `virtual ~UUsdConversionBlueprintContext();`
- L60 _private member_ `UE::FUsdStage Stage;` — Stage to use when converting components
- L66 _private member_ `bool bEraseFromStageCache = false;` — Whether we will erase our current stage from the stage cache when we Cleanup(). This is true if we were the ones that put the stage in the cache in the first place.
- L75 _public prototype_ `void SetStageRootLayer(FFilePath StageRootLayerPath);` — `UFUNCTION(BlueprintCallable, Category = "Export context")` — Opens or creates a USD stage using `StageRootLayerPath` as root layer, creating the root layer if needed. All future conversions will fetch prims and get/set USD data to/from this stage. Note: You must remember to call Cleanup() when done, or else this object will permanently hold a reference to the opened stage!
- L81 _public prototype_ `FFilePath GetStageRootLayer();` — `UFUNCTION(BlueprintCallable, Category = "Export context")` — Gets the file path of the root layer of our current stage
- L88 _public prototype_ `void SetEditTarget(FFilePath EditTargetLayerPath);` — `UFUNCTION(BlueprintCallable, Category = "Export context")` — Sets the current edit target of our internal stage. When calling the conversion functions, prims and attributes will be authored on this edit target only
- L94 _public prototype_ `FFilePath GetEditTarget();` — `UFUNCTION(BlueprintCallable, Category = "Export context")` — Gets the filepath of the current edit target layer of our internal stage
- L101 _public prototype_ `void Cleanup();` — `UFUNCTION(BlueprintCallable, Category = "Export context")` — Discards the currently opened stage. This is critical when using this class via scripting: The C++ destructor will not be called when the python object runs out of scope, so we would otherwise keep a strong reference to the stage
- L110 _public prototype_ `bool ConvertLightComponent(const ULightComponentBase* Component, const FString& PrimPath, float TimeCode = 3.402823466e+38F);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L113 _public prototype_ `bool ConvertDirectionalLightComponent(const UDirectionalLightComponent* Component, const FString& PrimPath, float TimeCode = 3.402823466e+38F);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L116 _public prototype_ `bool ConvertRectLightComponent(const URectLightComponent* Component, const FString& PrimPath, float TimeCode = 3.402823466e+38F);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L119 _public prototype_ `bool ConvertPointLightComponent(const UPointLightComponent* Component, const FString& PrimPath, float TimeCode = 3.402823466e+38F);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L122 _public prototype_ `bool ConvertSkyLightComponent(const USkyLightComponent* Component, const FString& PrimPath, float TimeCode = 3.402823466e+38F);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L125 _public prototype_ `bool ConvertSpotLightComponent(const USpotLightComponent* Component, const FString& PrimPath, float TimeCode = 3.402823466e+38F);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L128 _public prototype_ `bool ConvertDrawModeComponent(const UUsdDrawModeComponent* Component, const FString& PrimPath, float TimeCode = 3.402823466e+38F);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L131 _public prototype_ `bool ConvertAudioComponent(const UAudioComponent* Component, const FString& PrimPath, float TimeCode = 3.402823466e+38F, bool bFilePathOnly = false);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L134 _public prototype_ `bool ConvertSceneComponent(const USceneComponent* Component, const FString& PrimPath);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L137 _public prototype_ `bool ConvertIsmComponent(const UInstancedStaticMeshComponent* Component, const FString& PrimPath, float TimeCode = 3.402823466e+38F);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L140 _public prototype_ `bool ConvertHismComponent(const UHierarchicalInstancedStaticMeshComponent* Component, const FString& PrimPath, float TimeCode = 3.402823466e+38F);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L143 _public prototype_ `bool ConvertMeshComponent(const UMeshComponent* Component, const FString& PrimPath);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L146 _public prototype_ `bool ConvertCineCameraComponent(const UCineCameraComponent* Component, const FString& PrimPath, float TimeCode = 3.402823466e+38F);` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L149 _public prototype_ `bool ConvertInstancedFoliageActor( const AInstancedFoliageActor* Actor, const FString& PrimPath, ULevel* InstancesLevel = nullptr, float TimeCode = 3.402823466e+38F );` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L157 _public prototype_ `bool ConvertLandscapeProxyActorMesh( const ALandscapeProxy* Actor, const FString& PrimPath, int32 LowestLOD, int32 HighestLOD, float TimeCode = 3.402823466e+38F );` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L166 _public prototype_ `bool ConvertLandscapeProxyActorMaterial( ALandscapeProxy* Actor, const FString& PrimPath, const TArray<FPropertyEntry>& PropertiesToBake, const FIntPoint& DefaultTextureSize, const FDirectoryPath& TexturesDir, float TimeCode = 3.402823466e+38F );` — `UFUNCTION(BlueprintCallable, Category = "Component conversion")`
- L186 _public prototype_ `bool ConvertMaterialOverrides( const UObject* MeshAsset, const TArray<UMaterialInterface*> MaterialOverrides, const FString& PrimPath, int32 LowestLOD, int32 HighestLOD, bool bCheckAssetUserData = true );` — `UFUNCTION(BlueprintCallable, Category = "Conversion utils")` — Sets the material overrides as opinions on MeshPrim, taking care to figure out whether it needs to create LOD or subsection prims, and which ones given the chosen export LOD range. MeshAsset should be an UStaticMesh, USkeletalMesh or UGeometryCache. If bCheckAssetUserData is enabled, this function which check the asset's USD Asset User Data in order to determine the mapping between material slot and prim path, which is useful when exporting multiple slots to geom subsets or LOD prims. If this is false, The overrides will be authored to standard paths used by the USDImporter plugin (i.e. LOD<N> prims when needed, UsdGeomSubsets named "Section<N>")
- L207 _public prototype_ `void ReplaceUnrealMaterialsWithBaked( const FFilePath& LayerToAuthorIn, const TMap<FString, FString>& BakedMaterials, bool bIsAssetLayer, bool bUsePayload, bool bRemoveUnrealMaterials = false );` — `UFUNCTION(BlueprintCallable, Category = "Conversion utils")` — Traverses the context's stage and authors material binding attributes for all `unrealMaterials` that were baked into USD material assets. @param LayerToAuthorIn - File path to the layer where the material binding opinions are authored @param BakedMaterials - Maps from material path names to file paths where they were baked Example: { "/Game/MyMaterials/Red.Red": "C:/MyFolder/Red.usda" } @param bIsAssetLayer - True when we're exporting a single mesh/animation asset. False when we're exporting a level. Dictates minor behaviors when authoring the material binding relationships, e.g. whether we author them inside variants or not @param bUsePayload - Should be True if the Stage was exported using payload files to store the actual Mesh prims. Also dictates minor behaviors when authoring the material binding relationships. @param bRemoveUnrealMaterials - No longer used.
- L221 _public prototype_ `void AuthorUnrealMaterialBinding( const FString& MeshLikePrimPath, const FString& UnrealMaterialPathName, bool bStrongerThanDescendants = false );` — `UFUNCTION(BlueprintCallable, Category = "Conversion utils")` — Writes UnrealMaterialPathName as a material binding for MeshLikePrimPath, either by reusing an existing UsdShadeMaterial binding if it already has an 'unreal' render context output and the expected structure, or by creating a new Material prim that fulfills those requirements and binding to it (optionally with strongerThanDescendants strength in that case).
- L229 _public prototype_ `bool RemoveUnrealSurfaceOutput(const FString& PrimPath, const FFilePath& LayerToAuthorIn);` — `UE_DEPRECATED(all, "No longer used as UE material assignments are only visible in the 'unreal' render context anyway")` — `UFUNCTION()`
- L233 _public prototype_ `int32 GetUsdStageNumFrames();` — `UFUNCTION(BlueprintCallable, Category = "Conversion utils")` — Returns how many frames of animation the stage would generate if imported
- L237 _public prototype_ `void SetPrimAssetInfo(const FString& PrimPath, const FUsdUnrealAssetInfo& Info);` — `UFUNCTION(BlueprintCallable, Category = "Conversion utils|Metadata")` — Adds to Prim the assetInfo metadata the values described in Info
- L241 _public prototype_ `FUsdUnrealAssetInfo GetPrimAssetInfo(const FString& PrimPath);` — `UFUNCTION(BlueprintCallable, Category = "Conversion utils|Metadata")` — Retrieves from Prim the assetInfo metadata values that we use as export metadata, when exporting Unreal assets
- L245 _public prototype_ `void SetPrimMetadata( const FString& PrimPath, const FUsdCombinedPrimMetadata& Metadata, const TArray<FString>& BlockedPrefixFilter, bool bInvertFilter );` — `UFUNCTION(BlueprintCallable, Category = "Conversion utils|Metadata")` — Applies Metadata to the prim specified at PrimPath, using the provided filters
- L254 _public prototype_ `void SetPrimMetadataFromUserData( const FString& PrimPath, const UUsdAssetUserData* UserData, const TArray<FString>& BlockedPrefixFilter, bool bInvertFilter );` — `UFUNCTION(BlueprintCallable, Category = "Conversion utils|Metadata")` — Applies all the metadata contained in UserData to the prim specified at PrimPath, using the provided filters
- L263 _public prototype_ `FUsdCombinedPrimMetadata GetPrimMetadata( const FString& PrimPath, const TArray<FString>& BlockedPrefixFilter, bool bInvertFilter, bool bCollectFromEntireSubtrees );` — `UFUNCTION(BlueprintCallable, Category = "Conversion utils|Metadata")` — Extracts metadata from the prim at PrimPath using the provided filters and returns it

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API USDEXPORTER_API`

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/USDConversionBlueprintLibrary.h` (Public)


#### class `UUsdConversionBlueprintLibrary`  
`class UUsdConversionBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L26-769_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "UsdConversionLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Wrapped static conversion functions from the UsdUtilities module, so that they can be used via scripting
- L33 _public prototype_ `static int32 GetNumLevelsToExport(UWorld* World, const TSet<FString>& LevelsToIgnore);` — `UFUNCTION(BlueprintCallable, Category = "USD|World utils")` — Returns how many total Unreal levels (persistent + all sublevels) will be exported if we consider LevelsToIgnore
- L37 _public prototype_ `static void StreamInRequiredLevels(UWorld* World, const TSet<FString>& LevelsToIgnore);` — `UFUNCTION(BlueprintCallable, Category = "USD|World utils")` — Fully streams in and displays all levels whose names are not in LevelsToIgnore
- L44 _public prototype_ `static void RevertSequencerAnimations();` — `UFUNCTION(BlueprintCallable, Category = "USD|World utils")` — If we have the Sequencer open with a level sequence animating the level before export, this function can revert any actor or component to its unanimated state
- L51 _public prototype_ `static void ReapplySequencerAnimations();` — `UFUNCTION(BlueprintCallable, Category = "USD|World utils")` — If we used `ReverseSequencerAnimations` to undo the effect of an opened sequencer before export, this function can be used to re-apply the sequencer state back to the level after the export is complete
- L58 _public prototype_ `static TArray<FString> GetLoadedLevelNames(UWorld* World);` — `UFUNCTION(BlueprintCallable, Category = "USD|World utils")` — Returns the path name (e.g. "/Game/Maps/MyLevel") of levels that are loaded on `World`. We use these to revert the `World` to its initial state after we force-stream levels in for exporting
- L65 _public prototype_ `static TArray<FString> GetVisibleInEditorLevelNames(UWorld* World);` — `UFUNCTION(BlueprintCallable, Category = "USD|World utils")` — Returns the path name (e.g. "/Game/Maps/MyLevel") of levels that checked to be visible in the editor within `World`. We use these to revert the `World` to its initial state after we force-stream levels in for exporting
- L69 _public prototype_ `static void StreamOutLevels(UWorld* OwningWorld, const TArray<FString>& LevelNamesToStreamOut, const TArray<FString>& LevelNamesToHide);` — `UFUNCTION(BlueprintCallable, Category = "USD|World utils")` — Streams out/hides sublevels that were streamed in before export
- L72 _public prototype_ `static TSet<AActor*> GetActorsToConvert(UWorld* World);` — `UFUNCTION(BlueprintCallable, Category = "USD|World utils")`
- L84 _public prototype_ `static FString GenerateObjectVersionString(const UObject* ObjectToExport, UObject* ExportOptions);` — `UFUNCTION(BlueprintCallable, Category = "USD|World utils")` — Generates a unique identifier string that involves ObjectToExport's package's persistent guid, the corresponding file save date and time, and the number of times the package has been dirtied since last being saved. Optionally it can also combine that hash with a hash of the export options being used for the export, if available. This can be used to track the version of exported assets and levels, to prevent reexporting of actors and components.
- L88 _public prototype_ `static bool CanExportToLayer(const FString& TargetFilePath);` — `UFUNCTION(BlueprintCallable, Category = "USD|World utils")` — Checks whether we can create a USD Layer with "TargetFilePath" as identifier and export to it
- L91 _public prototype_ `static FString MakePathRelativeToLayer(const FString& AnchorLayerPath, const FString& PathToMakeRelative);` — `UFUNCTION(BlueprintCallable, Category = "USD|Layer utils")`
- L94 _public prototype_ `static void InsertSubLayer(const FString& ParentLayerPath, const FString& SubLayerPath, int32 Index = -1);` — `UFUNCTION(BlueprintCallable, Category = "USD|Layer utils")`
- L112 _public prototype_ `static void AddReference( const FString& ReferencingStagePath, const FString& ReferencingPrimPath, const FString& TargetStagePath, const FString& TargetPrimPath = TEXT(""), double TimeCodeOffset = 0.0, double TimeCodeScale = 1.0, bool bUseProjectDefaultTypeHandling = false, EReferencerTypeHandling ReferencerTypeHandling = EReferencerTypeHandling::MatchReferencedType );` — `UFUNCTION(BlueprintCallable, Category = "USD|Layer utils")` — Adds a reference to the layer at AbsoluteFilePath, optionally specifying a target prim inside that layer. @param ReferencingStagePath - Stage identifier that contains the referencer prim @param ReferencingPrimPath - Path to the referencer prim inside the referencer stage @param TargetStagePath - Path to the layer to reference (can be empty for internal references). e.g. "C:\MyFolder\Cube.usda" @param TargetPrimPath - Path to a specific prim to reference within the target layer. e.g. "/SomeOtherPrim" @param TimeCodeOffset - Offset in timeCodes to author on the reference @param TimeCodeScale - TimeCode scale to author on the reference @param bUseProjectDefaultTypeHandling - If true it means we will use the ReferencerTypeHandling set on the USD project settings. If false it means we will use the provided ReferencerSchemaHandling @param ReferencerSchemaHandling - How to behave when Prim has a different type than the referenced prim. Passing an unset TOptional will check the project settings for the value instead. The default value is MatchReferencedType for backwards compatibility. Note: If this is set to ShowDialog, the call may create an Editor transaction.
- L139 _public prototype_ `static void AddPayload( const FString& ReferencingStagePath, const FString& ReferencingPrimPath, const FString& TargetStagePath, const FString& TargetPrimPath = TEXT(""), double TimeCodeOffset = 0.0, double TimeCodeScale = 1.0, bool bUseProjectDefaultTypeHandling = false, EReferencerTypeHandling ReferencerTypeHandling = EReferencerTypeHandling::MatchReferencedType );` — `UFUNCTION(BlueprintCallable, Category = "USD|Layer utils")` — Adds a payload to the layer at AbsoluteFilePath, optionally specifying a target prim inside that layer. @param ReferencingStagePath - Stage identifier that contains the prim to receive the payload @param ReferencingPrimPath - Path to the prim inside the referencing stage that will receive the payload @param TargetStagePath - Path to the layer to add as payload (can be empty for internal payloads). e.g. "C:\MyFolder\Cube.usda" @param TargetPrimPath - Path to a specific prim to target within the target layer. e.g. "/SomeOtherPrim" @param TimeCodeOffset - Offset in timeCodes to author on the payload @param TimeCodeScale - TimeCode scale to author on the payload @param bUseProjectDefaultTypeHandling - If true it means we will use the ReferencerTypeHandling set on the USD project settings. If false it means we will use the provided ReferencerSchemaHandling @param ReferencerSchemaHandling - How to behave when Prim has a different type than the target prim. Passing an unset TOptional will check the project settings for the value instead. The default value is MatchReferencedType for backwards compatibility. Note: If this is set to ShowDialog, the call may create an Editor transaction.
- L151 _public prototype_ `static FString GetPrimPathForObject( const UObject* ActorOrComponent, const FString& ParentPrimPath = TEXT(""), bool bUseActorFolders = false, const FString& RootPrimName = TEXT("Root") );` — `UFUNCTION(BlueprintCallable, Category = "USD|Prim utils")`
- L159 _public prototype_ `static FString GetSchemaNameForComponent(const USceneComponent* Component);` — `UFUNCTION(BlueprintCallable, Category = "USD|Prim utils")`
- L168 _public prototype_ `static AInstancedFoliageActor* GetInstancedFoliageActorForLevel(bool bCreateIfNone = false, ULevel* Level = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "USD|Foliage Exporter")` — Wraps AInstancedFoliageActor::GetInstancedFoliageActorForLevel, and allows retrieving the current AInstancedFoliageActor for a level. Will default to the current editor level if Level is left nullptr. This function is useful because it's difficult to retrieve this actor otherwise, as it will be filtered from the results of functions like EditorLevelLibrary.get_all_level_actors()
- L176 _public prototype_ `static TArray<UFoliageType*> GetUsedFoliageTypes(AInstancedFoliageActor* Actor);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "USD|Foliage Exporter")` — Returns all the different types of UFoliageType assets that a particular AInstancedFoliageActor uses. This function exists because we want to retrieve all instances of all foliage types on an actor, but we can't return nested containers from UFUNCTIONs, so users of this API should call this, and then GetInstanceTransforms.
- L183 _public prototype_ `static UObject* GetSource(UFoliageType* FoliageType);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "USD|Foliage Exporter")` — Returns the source asset for a UFoliageType. It can be a UStaticMesh in case we're dealing with a UFoliageType_InstancedStaticMesh, but it can be other types of objects.
- L190 _public prototype_ `static TArray<FTransform> GetInstanceTransforms(AInstancedFoliageActor* Actor, UFoliageType* FoliageType, ULevel* InstancesLevel = nullptr);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "USD|Foliage Exporter")` — Returns the transforms of all instances of a particular UFoliageType on a given level. If no level is provided all instances will be returned. Use GetUsedFoliageTypes() to retrieve all foliage types managed by a particular actor.
- L194 _public prototype_ `static TArray<FAnalyticsEventAttr> GetAnalyticsAttributes(const ULevelExporterUSDOptions* Options);` — `UFUNCTION(BlueprintCallable, Category = "USD|Analytics")` — Retrieves the analytics attributes to send for the provided options object
- L198 _public prototype_ `static void SendAnalytics( const TArray<FAnalyticsEventAttr>& Attrs, const FString& EventName, bool bAutomated, double ElapsedSeconds, double NumberOfFrames, const FString& Extension );` — `UFUNCTION(BlueprintCallable, Category = "USD|Analytics")` — Defer to the USDClasses module to actually send analytics information
- L208 _public prototype_ `static void BlockAnalyticsEvents();` — `UFUNCTION(BlueprintCallable, Category = "USD|Analytics")`
- L211 _public prototype_ `static void ResumeAnalyticsEvents();` — `UFUNCTION(BlueprintCallable, Category = "USD|Analytics")`
- L222 _public prototype_ `static void BeginUniquePathScope();` — `UFUNCTION(BlueprintCallable, Category = "USD|Exporting utils")` — Begins a UniquePathScope, incrementing the internal scope counter. During a UniquePathScope, all paths returned by GetUniqueFilePathForExport will be globally unique (i.e. it will never return the same path twice). Opening a scope while another scope is opened has no effect but to increment the scope counter further.
- L231 _public prototype_ `static void EndUniquePathScope();` — `UFUNCTION(BlueprintCallable, Category = "USD|Exporting utils")` — Ends a UniquePathScope, decrementing the internal scope counter. If the internal scope counter reaches zero (i.e. all previously opened scopes are ended) this also clears the cache of unique paths.
- L240 _public prototype_ `static FString GetUniqueFilePathForExport(const FString& DesiredPathWithExtension);` — `UFUNCTION(BlueprintCallable, Category = "USD|Exporting utils")` — If we're inside of a UniquePathScope, returns a sanitized (and potentially suffixed) path that is guaranteed to not collide with any other path returned from this function during the UniquePathScope. If we're not inside of a UniquePathScope, returns the sanitized version of DesiredPathWithExtension.
- L257 _public prototype_ `static void RemoveAllPrimSpecs(const FString& StageRootLayer, const FString& PrimPath, const FString& TargetLayer);` — `UFUNCTION(BlueprintCallable, Category = "USD|Prim utils")` — Removes all the prim specs for Prim on the given Layer. This function is useful in case the prim is inside a variant set: In that case, just calling FUsdStage::RemovePrim() will attempt to remove the "/Root/Example/Child", which wouldn't remove the "/Root{Varset=Var}Example/Child" spec, meaning the prim may still be left on the stage. Note that it's even possible to have both of those specs at the same time: for example when we have a prim inside a variant set, but outside of it we have overrides to the same prim. This function will remove both. @param StageRootLayer - Path to the root layer of the stage from which we should fetch the Prims @param PrimPath - Prim to remove @param Layer - Layer to remove prim specs from. This can be left with the invalid layer (default) in order to remove all specs from the entire stage's local layer stack.
- L268 _public prototype_ `static bool CutPrims(const FString& StageRootLayer, const TArray<FString>& PrimPaths);` — `UFUNCTION(BlueprintCallable, Category = "USD|Prim utils")` — Copies flattened versions of the input prims onto the clipboard stage and removes all the prim specs for Prims from their stages. These cut prims can then be pasted with PastePrims. @param StageRootLayer - Path to the root layer of the stage from which we should fetch the Prims @param PrimPaths - Prims to cut @return True if we managed to cut
- L279 _public prototype_ `static bool CopyPrims(const FString& StageRootLayer, const TArray<FString>& PrimPaths);` — `UFUNCTION(BlueprintCallable, Category = "USD|Prim utils")` — Copies flattened versions of the input prims onto the clipboard stage. These copied prims can then be pasted with PastePrims. @param StageRootLayer - Path to the root layer of the stage from which we should fetch the Prims @param PrimPaths - Prims to copy @return True if we managed to copy
- L295 _public prototype_ `static TArray<FString> PastePrims(const FString& StageRootLayer, const FString& ParentPrimPath);` — `UFUNCTION(BlueprintCallable, Category = "USD|Prim utils")` — Pastes the prims from the clipboard stage as children of ParentPrim. The pasted prims may be renamed in order to have valid names for the target location, which is why this function returns the pasted prim paths. This function returns just paths instead of actual prims because USD needs to respond to the notices about the created prim specs before the prims are fully created, which means we wouldn't be able to return the created prims yet, in case this function was called from within an SdfChangeBlock. @param StageRootLayer - Path to the root layer of the stage from which we should fetch the Prims @param ParentPrimPath - Prim that will become parent to the pasted prims @return Paths to the pasted prim specs, after they were added as children of ParentPrim
- L299 _public prototype_ `static bool CanPastePrims();` — `UFUNCTION(BlueprintCallable, Category = "USD|Prim utils")` — Returns true if we have prims that we can paste within our clipboard stage
- L303 _public prototype_ `static void ClearPrimClipboard();` — `UFUNCTION(BlueprintCallable, Category = "USD|Prim utils")` — Clears all prims from our clipboard stage
- L322 _public prototype_ `static TArray<FString> DuplicatePrims( const FString& StageRootLayer, const TArray<FString>& PrimPaths, EUsdDuplicateType DuplicateType, const FString& TargetLayer );` — `UFUNCTION(BlueprintCallable, Category = "USD|Prim utils")` — Duplicates all provided Prims one-by-one, performing the requested DuplicateType. See the documentation on EUsdDuplicateType for the different operation types. The duplicated prims may be renamed in order to have valid names for the target location, which is why this function returns the pasted prim paths. This function returns just paths instead of actual prims because USD needs to respond to the notices about the created prim specs before the prims are fully created, which means we wouldn't be able to return the created prims yet, in case this function was called from within an SdfChangeBlock. @param StageRootLayer - Path to the root layer of the stage from which we should fetch the Prims @param PrimPaths - Prims to duplicate @param DuplicateType - Type of prim duplication to perform @param TargetLayer - Target layer to use when duplicating, if relevant for that duplication type @return Paths to the duplicated prim specs, after they were added as children of ParentPrim.
- L331 _public prototype_ `static UUsdAssetUserData* GetUsdAssetUserData(UObject* Object);` — `UFUNCTION(BlueprintCallable, Category = "USD|Metadata utils")` — Retrieve the first instance of UUsdAssetUserData contained on the Object, if any
- L338 _public prototype_ `static bool SetUsdAssetUserData(UObject* Object, UUsdAssetUserData* AssetUserData);` — `UFUNCTION(BlueprintCallable, Category = "USD|Metadata utils")` — Sets AssetUserData as the single UUsdAssetUserData on the Object, overwriting an existing one if encountered. Returns true if it managed to add AssetUserData to Object.
- L356 _public prototype_ `static bool SetMetadataField( UUsdAssetUserData* AssetUserData, const FString& Key, const FString& Value, const FString& ValueTypeName, const FString& StageIdentifier = "", const FString& PrimPath = "", bool bTriggerPropertyChangeEvents = true );` — `UFUNCTION(BlueprintCallable, Category = "USD|Metadata utils")` — Utilities that make it easier to get/set metadata fields without having to manipulate the nested struct instances directly. It will create the struct entries automatically if needed, and overwrite existing entries with the same key if needed. If the AssetUserData contains exactly one entry for StageIdentifier and one entry for PrimPath, you can omit those arguments and that single entry will be used. If there are more or less than exactly one entry for StageIdentifier or for PrimPath however, you must specify which one to use, and failing to do so will cause the functions to return false and emit a warning. It is possible to get these functions to automatically trigger pre/post property changed events by providing "true" for bTriggerPropertyChangeEvents, which is useful as it is not trivial to trigger those from Python/Blueprint given how the metadata is stored inside nested structs and maps. If these AssetUserData belong to generated transient assets when opening stages, emitting property change events causes those edits to be immediately written out to the opened USD Stage. Returns true if it managed to set the new key-value pair.
- L366 _public prototype_ `static bool ClearMetadataField( UUsdAssetUserData* AssetUserData, const FString& Key, const FString& StageIdentifier = "", const FString& PrimPath = "", bool bTriggerPropertyChangeEvents = true );` — `UFUNCTION(BlueprintCallable, Category = "USD|Metadata utils")`
- L374 _public prototype_ `static bool HasMetadataField( UUsdAssetUserData* AssetUserData, const FString& Key, const FString& StageIdentifier = "", const FString& PrimPath = "" );` — `UFUNCTION(BlueprintCallable, Category = "USD|Metadata utils")`
- L381 _public prototype_ `static FUsdMetadataValue GetMetadataField( UUsdAssetUserData* AssetUserData, const FString& Key, const FString& StageIdentifier = "", const FString& PrimPath = "" );` — `UFUNCTION(BlueprintCallable, Category = "USD|Metadata utils")`
- L390 _public prototype_ `static FString StringifyAsBool(bool Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L393 _public prototype_ `static FString StringifyAsUChar(uint8 Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "stringify_as_uchar"))`
- L396 _public prototype_ `static FString StringifyAsInt(int32 Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L399 _public prototype_ `static FString StringifyAsUInt(int32 Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "stringify_as_uint"))`
- L402 _public prototype_ `static FString StringifyAsInt64(int64 Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L405 _public prototype_ `static FString StringifyAsUInt64(int64 Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "stringify_as_uint64"))`
- L408 _public prototype_ `static FString StringifyAsHalf(float Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L411 _public prototype_ `static FString StringifyAsFloat(float Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L414 _public prototype_ `static FString StringifyAsDouble(double Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L417 _public prototype_ `static FString StringifyAsTimeCode(double Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "stringify_as_timecode"))`
- L420 _public prototype_ `static FString StringifyAsString(const FString& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L423 _public prototype_ `static FString StringifyAsToken(const FString& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L426 _public prototype_ `static FString StringifyAsAssetPath(const FString& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L429 _public prototype_ `static FString StringifyAsMatrix2d(const FMatrix2D& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L432 _public prototype_ `static FString StringifyAsMatrix3d(const FMatrix3D& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L435 _public prototype_ `static FString StringifyAsMatrix4d(const FMatrix& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L438 _public prototype_ `static FString StringifyAsQuatd(const FQuat& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L441 _public prototype_ `static FString StringifyAsQuatf(const FQuat& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L444 _public prototype_ `static FString StringifyAsQuath(const FQuat& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L447 _public prototype_ `static FString StringifyAsDouble2(const FVector2D& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L450 _public prototype_ `static FString StringifyAsFloat2(const FVector2D& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L453 _public prototype_ `static FString StringifyAsHalf2(const FVector2D& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L456 _public prototype_ `static FString StringifyAsInt2(const FIntPoint& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L459 _public prototype_ `static FString StringifyAsDouble3(const FVector& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L462 _public prototype_ `static FString StringifyAsFloat3(const FVector& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L465 _public prototype_ `static FString StringifyAsHalf3(const FVector& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L468 _public prototype_ `static FString StringifyAsInt3(const FIntVector& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L471 _public prototype_ `static FString StringifyAsDouble4(const FVector4& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L474 _public prototype_ `static FString StringifyAsFloat4(const FVector4& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L477 _public prototype_ `static FString StringifyAsHalf4(const FVector4& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L480 _public prototype_ `static FString StringifyAsInt4(const FIntVector4& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L484 _public prototype_ `static FString StringifyAsBoolArray(const TArray<bool>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L487 _public prototype_ `static FString StringifyAsUCharArray(const TArray<uint8>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "stringify_as_uchar_array"))`
- L490 _public prototype_ `static FString StringifyAsIntArray(const TArray<int32>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L493 _public prototype_ `static FString StringifyAsUIntArray(const TArray<int32>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "stringify_as_uint_array"))`
- L496 _public prototype_ `static FString StringifyAsInt64Array(const TArray<int64>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L499 _public prototype_ `static FString StringifyAsUInt64Array(const TArray<int64>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "stringify_as_uint64_array"))`
- L502 _public prototype_ `static FString StringifyAsHalfArray(const TArray<float>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L505 _public prototype_ `static FString StringifyAsFloatArray(const TArray<float>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L508 _public prototype_ `static FString StringifyAsDoubleArray(const TArray<double>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L511 _public prototype_ `static FString StringifyAsTimeCodeArray(const TArray<double>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "stringify_as_timecode_array"))`
- L514 _public prototype_ `static FString StringifyAsStringArray(const TArray<FString>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L517 _public prototype_ `static FString StringifyAsTokenArray(const TArray<FString>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L520 _public prototype_ `static FString StringifyAsAssetPathArray(const TArray<FString>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L523 _public prototype_ `static FString StringifyAsListOpTokens(const TArray<FString>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L526 _public prototype_ `static FString StringifyAsMatrix2dArray(const TArray<FMatrix2D>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L529 _public prototype_ `static FString StringifyAsMatrix3dArray(const TArray<FMatrix3D>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L532 _public prototype_ `static FString StringifyAsMatrix4dArray(const TArray<FMatrix>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L535 _public prototype_ `static FString StringifyAsQuatdArray(const TArray<FQuat>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L538 _public prototype_ `static FString StringifyAsQuatfArray(const TArray<FQuat>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L541 _public prototype_ `static FString StringifyAsQuathArray(const TArray<FQuat>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L544 _public prototype_ `static FString StringifyAsDouble2Array(const TArray<FVector2D>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L547 _public prototype_ `static FString StringifyAsFloat2Array(const TArray<FVector2D>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L550 _public prototype_ `static FString StringifyAsHalf2Array(const TArray<FVector2D>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L553 _public prototype_ `static FString StringifyAsInt2Array(const TArray<FIntPoint>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L556 _public prototype_ `static FString StringifyAsDouble3Array(const TArray<FVector>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L559 _public prototype_ `static FString StringifyAsFloat3Array(const TArray<FVector>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L562 _public prototype_ `static FString StringifyAsHalf3Array(const TArray<FVector>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L565 _public prototype_ `static FString StringifyAsInt3Array(const TArray<FIntVector>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L568 _public prototype_ `static FString StringifyAsDouble4Array(const TArray<FVector4>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L571 _public prototype_ `static FString StringifyAsFloat4Array(const TArray<FVector4>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L574 _public prototype_ `static FString StringifyAsHalf4Array(const TArray<FVector4>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L577 _public prototype_ `static FString StringifyAsInt4Array(const TArray<FIntVector4>& Value);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L581 _public prototype_ `static bool UnstringifyAsBool(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L584 _public prototype_ `static uint8 UnstringifyAsUChar(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "unstringify_as_uchar"))`
- L587 _public prototype_ `static int32 UnstringifyAsInt(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L590 _public prototype_ `static int32 UnstringifyAsUInt(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "unstringify_as_uint"))`
- L593 _public prototype_ `static int64 UnstringifyAsInt64(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L596 _public prototype_ `static int64 UnstringifyAsUInt64(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "unstringify_as_uint64"))`
- L599 _public prototype_ `static float UnstringifyAsHalf(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L602 _public prototype_ `static float UnstringifyAsFloat(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L605 _public prototype_ `static double UnstringifyAsDouble(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L608 _public prototype_ `static double UnstringifyAsTimeCode(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "unstringify_as_timecode"))`
- L611 _public prototype_ `static FString UnstringifyAsString(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L614 _public prototype_ `static FString UnstringifyAsToken(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L617 _public prototype_ `static FString UnstringifyAsAssetPath(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L620 _public prototype_ `static FMatrix2D UnstringifyAsMatrix2d(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L623 _public prototype_ `static FMatrix3D UnstringifyAsMatrix3d(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L626 _public prototype_ `static FMatrix UnstringifyAsMatrix4d(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L629 _public prototype_ `static FQuat UnstringifyAsQuatd(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L632 _public prototype_ `static FQuat UnstringifyAsQuatf(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L635 _public prototype_ `static FQuat UnstringifyAsQuath(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L638 _public prototype_ `static FVector2D UnstringifyAsDouble2(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L641 _public prototype_ `static FVector2D UnstringifyAsFloat2(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L644 _public prototype_ `static FVector2D UnstringifyAsHalf2(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L647 _public prototype_ `static FIntPoint UnstringifyAsInt2(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L650 _public prototype_ `static FVector UnstringifyAsDouble3(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L653 _public prototype_ `static FVector UnstringifyAsFloat3(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L656 _public prototype_ `static FVector UnstringifyAsHalf3(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L659 _public prototype_ `static FIntVector UnstringifyAsInt3(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L662 _public prototype_ `static FVector4 UnstringifyAsDouble4(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L665 _public prototype_ `static FVector4 UnstringifyAsFloat4(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L668 _public prototype_ `static FVector4 UnstringifyAsHalf4(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L671 _public prototype_ `static FIntVector4 UnstringifyAsInt4(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L675 _public prototype_ `static TArray<bool> UnstringifyAsBoolArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L678 _public prototype_ `static TArray<uint8> UnstringifyAsUCharArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "unstringify_as_uchar_array"))`
- L681 _public prototype_ `static TArray<int32> UnstringifyAsIntArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L684 _public prototype_ `static TArray<int32> UnstringifyAsUIntArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "unstringify_as_uint_array"))`
- L687 _public prototype_ `static TArray<int64> UnstringifyAsInt64Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L690 _public prototype_ `static TArray<int64> UnstringifyAsUInt64Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "unstringify_as_uint64_array"))`
- L693 _public prototype_ `static TArray<float> UnstringifyAsHalfArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L696 _public prototype_ `static TArray<float> UnstringifyAsFloatArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L699 _public prototype_ `static TArray<double> UnstringifyAsDoubleArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L702 _public prototype_ `static TArray<double> UnstringifyAsTimeCodeArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils", Meta = (ScriptName = "unstringify_as_timecode_array"))`
- L705 _public prototype_ `static TArray<FString> UnstringifyAsStringArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L708 _public prototype_ `static TArray<FString> UnstringifyAsTokenArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L711 _public prototype_ `static TArray<FString> UnstringifyAsAssetPathArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L714 _public prototype_ `static TArray<FString> UnstringifyAsListOpTokens(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L717 _public prototype_ `static TArray<FMatrix2D> UnstringifyAsMatrix2dArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L720 _public prototype_ `static TArray<FMatrix3D> UnstringifyAsMatrix3dArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L723 _public prototype_ `static TArray<FMatrix> UnstringifyAsMatrix4dArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L726 _public prototype_ `static TArray<FQuat> UnstringifyAsQuatdArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L729 _public prototype_ `static TArray<FQuat> UnstringifyAsQuatfArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L732 _public prototype_ `static TArray<FQuat> UnstringifyAsQuathArray(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L735 _public prototype_ `static TArray<FVector2D> UnstringifyAsDouble2Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L738 _public prototype_ `static TArray<FVector2D> UnstringifyAsFloat2Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L741 _public prototype_ `static TArray<FVector2D> UnstringifyAsHalf2Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L744 _public prototype_ `static TArray<FIntPoint> UnstringifyAsInt2Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L747 _public prototype_ `static TArray<FVector> UnstringifyAsDouble3Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L750 _public prototype_ `static TArray<FVector> UnstringifyAsFloat3Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L753 _public prototype_ `static TArray<FVector> UnstringifyAsHalf3Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L756 _public prototype_ `static TArray<FIntVector> UnstringifyAsInt3Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L759 _public prototype_ `static TArray<FVector4> UnstringifyAsDouble4Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L762 _public prototype_ `static TArray<FVector4> UnstringifyAsFloat4Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L765 _public prototype_ `static TArray<FVector4> UnstringifyAsHalf4Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`
- L768 _public prototype_ `static TArray<FIntVector4> UnstringifyAsInt4Array(const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "USD|Stringify utils")`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API USDEXPORTER_API`

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/USDExporterModule.h` (Public)


#### class `IUsdExporterModule`  
`class IUsdExporterModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L11 _public prototype_ `static void HashEditorSelection(FSHA1& HashToUpdate);`
- L14 _public prototype_ `static bool CanExportToLayer(const FString& TargetFilePath);` — Checks whether we can create a USD Layer with "TargetFilePath" as identifier and export to it

### `Plugins/Importers/USDImporter/Source/USDExporter/Public/USDMetadataExportOptions.h` (Public)


#### struct `FUsdMetadataExportOptions`  
`struct FUsdMetadataExportOptions`  
_L10-54_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `bool bExportAssetInfo = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata", config)` — Export generic assetInfo when exporting assets (such as export time, engine version, etc.). Note that exporting assetInfo is required in order to avoid the re-export of identical assets to the same file.
- L24 _public member_ `bool bExportAssetMetadata = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata", config)` — Export metadata held on assets' UsdAssetUserData to the output prim. Note that metadata is always exported afterwards assetInfo, which means that if assetInfo entries are specified within the collected metadata, those will override the automatically generated assetInfo vallues
- L29 _public member_ `bool bExportComponentMetadata = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata", config)` — Export metadata held on components' UsdAssetUserData to the output prims. This only has an effect for Level/LevelSequence exports.
- L40 _public member_ `TArray<FString> BlockedPrefixFilters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata", config, meta = (EditCondition = "bExportAssetMetadata || bExportComponentMetadata"))` — When exporting metadata, we will ignore all entries that start with these prefixes. Note that you can use the ":" separator for nested dictionaries in USD.
- L53 _public member_ `bool bInvertFilters = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata", config, meta = (EditCondition = "bExportAssetMetadata || bExportComponentMetadata"))` — When this is false (default), the "BlockedPrefixFilters" property describe prefixes to block, and metadata entries that match any of those prefixes are ignored and not exported. When this is true, the "BlockedPrefixFilters" property is inverted, and describes prefixes to *allow*. In that case, entries are only allowed and exported if they match at least one of the provided prefixes.

#### Free symbols / members of external scopes

- L56 _namespace_ `namespace UsdUtils`
- L58 _prototype_ `void AddAnalyticsAttributes(const FUsdMetadataExportOptions& Options, TArray<FAnalyticsEventAttribute>& InOutAttributes);` (scope `UsdUtils`)
- L59 _prototype_ `void HashForExport(const FUsdMetadataExportOptions& Options, FSHA1& HashToUpdate);` (scope `UsdUtils`)
