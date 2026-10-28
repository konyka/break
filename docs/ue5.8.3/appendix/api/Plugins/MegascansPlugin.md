# Plugins / MegascansPlugin

- module root: `Plugins/Bridge/Source/MegascansPlugin`
- headers: 17; symbols: 246
- symbol kinds: class=20, delegate=3, enum=1, enumerator=5, function=3, macro=6, member=105, namespace=2, prototype=84, struct=17
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, ContentBrowser, Core, CoreUObject, EditorScriptingUtilities, EditorStyle, Engine, Foliage, FoliageEdit, HTTP, Json, JsonUtilities, LevelEditor, MaterialEditor, MeshBuilder, MetaHumanSDKEditor, Networking, Projects, Settings, Slate, SlateCore, Sockets, StaticMeshEditor, TargetPlatform, UnrealEd

### `Plugins/Bridge/Source/MegascansPlugin/Internal/BridgeDragDropHelper.h` (Internal)


#### class `FBridgeDragDropHelperImpl`  
`class FBridgeDragDropHelperImpl : public TSharedFromThis<FBridgeDragDropHelperImpl>`  
_L15-22_
- inherits: `TSharedFromThis<FBridgeDragDropHelperImpl>`
- L18 _public member_ `FOnAddProgressiveStageDataCallbackInternal OnAddProgressiveStageDataDelegate;`
- L19 _public member_ `TMap<FString, AActor*> SurfaceToActorMap;`
- L21 _public prototype_ `void SetOnAddProgressiveStageData(FOnAddProgressiveStageDataCallbackInternal InDelegate);`

#### class `FBridgeDragDropHelper`  
`class FBridgeDragDropHelper`  
_L24-29_
- L27 _public prototype_ `static void Initialize();`
- L28 _public member_ `static TSharedPtr<FBridgeDragDropHelperImpl> Instance;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API MEGASCANSPLUGIN_API`
- L13 _delegate_ `DECLARE_DELEGATE_FourParams(FOnAddProgressiveStageDataCallbackInternal, FAssetData AssetData, FString AssetId, FString AssetType, AStaticMeshActor* SpawnedActor);`
- L13 _prototype_ `DECLARE_DELEGATE_FourParams(FOnAddProgressiveStageDataCallbackInternal, FAssetData AssetData, FString AssetId, FString AssetType, AStaticMeshActor* SpawnedActor);`

### `Plugins/Bridge/Source/MegascansPlugin/Private/AssetImporters/ImportFactory.h` (Private)


#### class `IAssetImportFactory`  
`class IAssetImportFactory`  
_L9-15_
- L12 _public prototype_ `static TSharedPtr<IAssetImportFactory> CreateImporter(EAssetImportType ImporterType) ;`
- L13 _public prototype_ `virtual void ImportAsset(TSharedPtr<FJsonObject> AssetImportJson) = 0;`

### `Plugins/Bridge/Source/MegascansPlugin/Private/AssetImporters/ProgressiveImport3D.h` (Private)


#### struct `FProgressiveData`  
`struct FProgressiveData`  
_L12-18_
- L14 _public member_ `AStaticMeshActor* ActorInLevel;`
- L15 _public member_ `UMaterialInstanceConstant* PreviewInstance;`
- L16 _public member_ `FString PreviewFolderPath;`
- L17 _public member_ `FString PreviewMeshPath;`

#### class `FImportProgressive3D`  
`class FImportProgressive3D`  
_L20-49_
- L24 _private prototype_ `FImportProgressive3D() = default;`
- L25 _private member_ `static TSharedPtr<FImportProgressive3D> ImportProgressive3DInst;`
- L26 _private prototype_ `void SpawnAtCenter(FAssetData AssetData, TSharedPtr<FUAssetData> ImportData, float LocationOffset, bool bIsNormal= false);`
- L29 _private member_ `TMap<FString, TSharedPtr<FProgressiveData>> PreviewDetails;`
- L32 _private prototype_ `void AsyncCacheData(FAssetData HighAssetData, FString AssetID, FUAssetMeta AssetMetaData, bool bWaitNaniteConversion=false);`
- L33 _private prototype_ `void SwitchHigh(FAssetData HighAssetData, FString AssetID);`
- L35 _private prototype_ `void AsyncNormalImportCache(FAssetData HighAssetData, FUAssetMeta AssetMetaData, float LocationOffset);`
- L39 _public prototype_ `static TSharedPtr<FImportProgressive3D> Get();`
- L40 _public prototype_ `void ImportAsset(TSharedPtr<FJsonObject> AssetImportJson, float LocationOffset, bool bIsNormal = false);`
- L42 _public prototype_ `void HandlePreviewTextureLoad(FAssetData TextureData, FString AssetID, FString Type);`
- L43 _public prototype_ `void HandlePreviewInstanceLoad(FAssetData PreviewInstanceData, FString AssetID);`
- L45 _public prototype_ `void HandleHighAssetLoad(FAssetData HighAssetData, FString AssetID, FUAssetMeta AssetMetaData, bool bWaitNaniteConversion = false);`
- L47 _public prototype_ `void HandleNormalAssetLoad(FAssetData NormalAssetData , FUAssetMeta AssetMetaData, float LocationOffset);`

### `Plugins/Bridge/Source/MegascansPlugin/Private/AssetImporters/ProgressiveImportSurfaces.h` (Private)


#### struct `FProgressiveSurfaces`  
`struct FProgressiveSurfaces`  
_L10-16_
- L12 _public member_ `TArray<AStaticMeshActor*> ActorsInLevel;`
- L13 _public member_ `UMaterialInstanceConstant* PreviewInstance = nullptr;`
- L14 _public member_ `FString PreviewFolderPath;`
- L15 _public member_ `FString PreviewMeshPath;`

#### class `FImportProgressiveSurfaces`  
`class FImportProgressiveSurfaces`  
_L18-40_
- L22 _private prototype_ `FImportProgressiveSurfaces() = default;`
- L23 _private member_ `static TSharedPtr<FImportProgressiveSurfaces> ImportProgressiveSurfacesInst;`
- L25 _private member_ `TMap<FString, TSharedPtr<FProgressiveSurfaces>> PreviewDetails;`
- L26 _private prototype_ `void SpawnMaterialPreviewActor(FString AssetID, float LocationOffset, bool bIsNormal = false, FAssetData MInstanceData = NULL);`
- L30 _public prototype_ `static TSharedPtr<FImportProgressiveSurfaces> Get();`
- L31 _public prototype_ `void ImportAsset(TSharedPtr<FJsonObject> AssetImportJson, float LocationOffset, bool bIsNormal = false);`
- L33 _public prototype_ `void HandlePreviewInstanceLoad(FAssetData PreviewInstanceData, FString AssetID, float LocationOffset);`
- L34 _public prototype_ `void HandlePreviewTextureLoad(FAssetData TextureData, FString AssetID, FString Type);`
- L36 _public prototype_ `void HandleHighInstanceLoad(FAssetData HighInstanceData, FString AssetID, FUAssetMeta AssetMetaData);`
- L38 _public prototype_ `void HandleNormalMaterialLoad(FAssetData AssetInstanceData, FUAssetMeta AssetMetaData, float LocationOffset);`

### `Plugins/Bridge/Source/MegascansPlugin/Private/AssetImporters/UAssetNormalImport.h` (Private)


#### class `FImportUAssetNormal`  
`class FImportUAssetNormal`  
_L10-21_
- L15 _private prototype_ `FImportUAssetNormal() = default;`
- L16 _private member_ `static TSharedPtr<FImportUAssetNormal> ImportUassetNormalInst;`
- L19 _public prototype_ `static TSharedPtr<FImportUAssetNormal> Get();`
- L20 _public prototype_ `void ImportAsset(TSharedPtr<FJsonObject> AssetImportJson);`

### `Plugins/Bridge/Source/MegascansPlugin/Private/MSAssetImportData.h` (Private)


#### enum `EAssetImportType`  
`enum EAssetImportType`  
_L8-14_
- desc: Types of imports this plugin will handle
- L9 _public enumerator_ `MEGASCANS_SOURCE`
- L10 _public enumerator_ `MEGASCANS_UASSET`
- L11 _public enumerator_ `TEMPLATE`
- L12 _public enumerator_ `DHI_CHARACTER`
- L13 _public enumerator_ `NONE`

#### struct `FUAssetData`  
`struct FUAssetData`  
_L18-30_
- desc: Data strcutures to hold json data for specific import types UAsset asset import data
- L21 _public member_ `FString ImportType;` — Should be converted to EAssetImportType
- L22 _public member_ `uint8 AssetTier;`
- L23 _public member_ `FString AssetType;`
- L24 _public member_ `FString ExportMode;`
- L25 _public member_ `int8 ProgressiveStage;`
- L26 _public member_ `FString ImportJsonPath;`
- L27 _public member_ `FString AssetId;`
- L28 _public member_ `TArray<FString> FilePaths;`

#### struct `FMaterialUsage`  
`struct FMaterialUsage`  
_L38-45_
- reflection: `USTRUCT()`
- L42 _public member_ `FString instanceID = "";` — `UPROPERTY()`
- L44 _public member_ `FString materialSlot = "";` — `UPROPERTY()`

#### struct `FMeshInfo`  
`struct FMeshInfo`  
_L48-62_
- reflection: `USTRUCT()`
- L52 _public member_ `FString meshID = "";` — `UPROPERTY()`
- L54 _public member_ `FString name = "";` — `UPROPERTY()`
- L56 _public member_ `FString path = "";` — `UPROPERTY()`
- L58 _public member_ `int8 numberOfLods = 0;` — `UPROPERTY()`
- L60 _public member_ `TArray<FMaterialUsage> materialUsage;` — `UPROPERTY()`

#### struct `FFoliageTypeInfo`  
`struct FFoliageTypeInfo`  
_L65-70_
- reflection: `USTRUCT()`
- L69 _public member_ `FString path;` — `UPROPERTY()`

#### struct `FMaterialParams`  
`struct FMaterialParams`  
_L73-80_
- reflection: `USTRUCT()`
- L77 _public member_ `FString paramName;` — `UPROPERTY()`
- L79 _public member_ `FString usedTextureID;` — `UPROPERTY()`

#### struct `FMaterialInstanceInfo`  
`struct FMaterialInstanceInfo`  
_L84-99_
- reflection: `USTRUCT()`
- L88 _public member_ `FString instanceID;` — `UPROPERTY()`
- L90 _public member_ `FString instanceName;` — `UPROPERTY()`
- L92 _public member_ `FString instancePath;` — `UPROPERTY()`
- L94 _public member_ `FString instanceMaster;` — `UPROPERTY()`
- L96 _public member_ `FString type;` — `UPROPERTY()`
- L98 _public member_ `TArray<FMaterialParams> params;` — `UPROPERTY()`

#### struct `FMasterMaterialInfo`  
`struct FMasterMaterialInfo`  
_L102-111_
- reflection: `USTRUCT()`
- L106 _public member_ `FString masterID;` — `UPROPERTY()`
- L108 _public member_ `FString masterMaterialName;` — `UPROPERTY()`
- L110 _public member_ `FString path;` — `UPROPERTY()`

#### struct `FChannelPackedInfo`  
`struct FChannelPackedInfo`  
_L115-123_
- reflection: `USTRUCT()`
- L119 _public member_ `FString channel = "";` — `UPROPERTY()`
- L121 _public member_ `FString packedType = "";` — `UPROPERTY()`

#### struct `FTextureUsage`  
`struct FTextureUsage`  
_L126-133_
- reflection: `USTRUCT()`
- L130 _public member_ `FString matID = "";` — `UPROPERTY()`
- L132 _public member_ `FString matParams = "";` — `UPROPERTY()`

#### struct `FTexturesList`  
`struct FTexturesList`  
_L136-155_
- reflection: `USTRUCT()`
- L140 _public member_ `FString textureID = "";` — `UPROPERTY()`
- L142 _public member_ `FString type = "";` — `UPROPERTY()`
- L144 _public member_ `FString resolution = "";` — `UPROPERTY()`
- L146 _public member_ `FString name = "";` — `UPROPERTY()`
- L148 _public member_ `FString path = "";` — `UPROPERTY()`
- L150 _public member_ `bool isChannelPacked = true;` — `UPROPERTY()`
- L152 _public member_ `TArray<FChannelPackedInfo> channelPackInfo;` — `UPROPERTY()`
- L154 _public member_ `TArray<FTextureUsage> pluggedIn;` — `UPROPERTY()`

#### struct `FUAssetMeta`  
`struct FUAssetMeta`  
_L159-186_
- reflection: `USTRUCT()`
- L164 _public member_ `FString assetID;` — `UPROPERTY()`
- L166 _public member_ `FString assetName;` — `UPROPERTY()`
- L168 _public member_ `FString assetType;` — `UPROPERTY()`
- L170 _public member_ `FString assetSubType;` — `UPROPERTY()`
- L172 _public member_ `int8 assetTier = 0;` — `UPROPERTY()`
- L174 _public member_ `FString assetRootPath;` — `UPROPERTY()`
- L176 _public member_ `TArray<FMeshInfo> meshList;` — `UPROPERTY()`
- L178 _public member_ `TArray<FString> foliageAssetPaths;` — `UPROPERTY()`
- L180 _public member_ `TArray<FMaterialInstanceInfo> materialInstances;` — `UPROPERTY()`
- L182 _public member_ `TArray<FTexturesList> textureSets;` — `UPROPERTY()`
- L184 _public member_ `TArray<FMasterMaterialInfo> masterMaterials;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L5 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(MSLiveLinkLog, Log, All);`
- L5 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(MSLiveLinkLog, Log, All);`

### `Plugins/Bridge/Source/MegascansPlugin/Private/Tools/BlendMaterials.h` (Private)


#### class `FMaterialBlend`  
`class FMaterialBlend`  
_L9-35_
- L12 _private prototype_ `FMaterialBlend() = default;`
- L13 _private member_ `static TSharedPtr<FMaterialBlend> MaterialBlendInst;`
- L14 _private member_ `FString DBlendDestinationPath = TEXT("/Ga`
- L15 _private member_ `FString DBlendInstanceName = TEXT("Ble`
- L16 _private member_ `FString DBlendMasterMaterial = TEXT("Sur`
- L19 _private member_ `TArray<FString> BlendSets = {"Base", "Mid` — TArray<FString> BlendSets = { "Base", "R", "G", "B", "A" };
- L21 _private member_ `TArray<FString> SupportedMapTypes = {"albedo", "n` — TArray<FString> SupportedMapTypes = { "albedo", "normal", "roughness", "specular", "gloss", "displacement", "opacity", "translucency" };
- L23 _private prototype_ `bool ValidateSelectedAssets(TArray<FString> SelectedMaterials, FString &Failure);`
- L24 _private member_ `FString MasterMaterialPath = TEXT("/Ga`
- L26 _private prototype_ `void HandleTextureLoading(FAssetData TextureData);`
- L31 _public prototype_ `static TSharedPtr<FMaterialBlend> Get();`
- L32 _public prototype_ `void BlendSelectedMaterials();`
- L34 _public prototype_ `void ConvertToVirtualTextures(FUAssetMeta AssetMetaData);`

### `Plugins/Bridge/Source/MegascansPlugin/Private/UI/MaterialBlendingDetails.h` (Private)


#### class `BlendSettingsCustomization`  
`class BlendSettingsCustomization : public IDetailCustomization`  
_L7-19_
- inherits: `IDetailCustomization`
- L11 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _private prototype_ `bool CanCreateMaterialBlend() const;`
- L17 _private prototype_ `FReply CreateMaterialBlend();`

### `Plugins/Bridge/Source/MegascansPlugin/Private/Utilities/MaterialUtils.h` (Private)


#### class `FMaterialUtils`  
`class FMaterialUtils`  
_L10-19_
- L13 _public prototype_ `static UMaterialInstanceConstant* CreateInstanceMaterial(const FString& MasterMaterialPath, const FString& InstanceDestination, const FString& AssetName);`
- L14 _public prototype_ `static bool ShouldOverrideMaterial(const FString& AssetType);`
- L15 _public prototype_ `static TArray<AStaticMeshActor*> ApplyMaterialToSelection(const FString& InstancePath );`
- L16 _public prototype_ `static UMaterialInstanceConstant* CreateMaterialOverride(FUAssetMeta AssetMetaData);`
- L17 _public prototype_ `static void ApplyMaterialInstance(FUAssetMeta AssetMetaData, UMaterialInstanceConstant* MaterialInstance);`

### `Plugins/Bridge/Source/MegascansPlugin/Private/Utilities/MiscUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _prototype_ `TSharedPtr<FJsonObject> DeserializeJson(const FString& JsonStringData);`
- L15 _prototype_ `FString GetPluginPath();`
- L16 _prototype_ `FString GetSourceMSPresetsPath();`
- L18 _prototype_ `bool CopyMaterialPreset(const FString & MaterialName);`
- L19 _prototype_ `FString GetMSPresetsName();`
- L20 _prototype_ `void CopyMSPresets();`
- L21 _prototype_ `bool CopyPresetTextures();`
- L22 _prototype_ `void CopyUassetFiles(TArray<FString> FilesToCopy, FString DestinationDirectory);`
- L23 _prototype_ `void CopyUassetFilesPlants(TArray<FString> FilesToCopy, FString DestinationDirectory, const int8 & AssetTier);`
- L26 _namespace_ `namespace AssetUtils`
- L28 _prototype_ `void FocusOnSelected(const FString& Path);` (scope `AssetUtils`)
- L29 _prototype_ `void SavePackage(UObject* SourceObject);` (scope `AssetUtils`)
- L30 _prototype_ `void DeleteDirectory(FString TargetDirectory);` (scope `AssetUtils`)
- L31 _prototype_ `bool DeleteAsset(const FString& AssetPath);` (scope `AssetUtils`)
- L32 _prototype_ `FUAssetMeta GetAssetMetaData(const FString& JsonPath);` (scope `AssetUtils`)
- L33 _prototype_ `TArray<UMaterialInstanceConstant*> GetSelectedAssets(const FTopLevelAssetPath& AssetClass);` (scope `AssetUtils`)
- L34 _prototype_ `void AddFoliageTypesToLevel(TArray<FString> FoliageTypePaths);` (scope `AssetUtils`)
- L37 _prototype_ `void ManageImportSettings(FUAssetMeta AssetMetaData);` (scope `AssetUtils`) — To manage import settings like Auto-Populate Foliage types etc.
- L38 _prototype_ `void SyncFolder(const FString& TargetFolder);` (scope `AssetUtils`)
- L39 _prototype_ `void RegisterAsset(const FString& PackagePath);` (scope `AssetUtils`)
- L41 _prototype_ `void ConvertToVT(FUAssetMeta AssetMetaData);` (scope `AssetUtils`)
- L42 _prototype_ `bool IsVTEnabled();` (scope `AssetUtils`)
- L46 _namespace_ `namespace JsonUtils`
- L48 _prototype_ `EAssetImportType GetImportType(TSharedPtr<FJsonObject> ImportJsonObject);` (scope `JsonUtils`)
- L49 _prototype_ `void ParseImportJson(const FString& InputImportData);` (scope `JsonUtils`)
- L50 _prototype_ `TSharedPtr<FUAssetData> ParseUassetJson(TSharedPtr<FJsonObject> ImportJsonObject);` (scope `JsonUtils`)

### `Plugins/Bridge/Source/MegascansPlugin/Private/Utilities/VersionInfoHandler.h` (Private)


#### struct `FAssetInfo`  
`struct FAssetInfo`  
_L7-14_
- reflection: `USTRUCT()`
- L11 _public member_ `FString path = "";` — `UPROPERTY()`
- L13 _public member_ `FString version = "";` — `UPROPERTY()`

#### struct `FVersionData`  
`struct FVersionData`  
_L17-23_
- reflection: `USTRUCT()`
- L22 _public member_ `TArray<FAssetInfo> assets;` — `UPROPERTY()`

#### struct `FAssetImportTime`  
`struct FAssetImportTime`  
_L27-34_
- reflection: `USTRUCT()`
- L31 _public member_ `FString path = "";` — `UPROPERTY()`
- L33 _public member_ `FString time = "";` — `UPROPERTY()`

#### struct `FImportTimeData`  
`struct FImportTimeData`  
_L37-43_
- reflection: `USTRUCT()`
- L42 _public member_ `TArray<FAssetImportTime> assets;` — `UPROPERTY()`

#### class `UVersionInfoHandler`  
`class UVersionInfoHandler : public UObject`  
_L46-57_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- L53 _public prototype_ `static UVersionInfoHandler* Get();` — `UFUNCTION(BlueprintCallable, Category = Python)`
- L56 _public member_ `FVersionData CommonVersionData;` — `UPROPERTY()`

### `Plugins/Bridge/Source/MegascansPlugin/Public/AssetsImportController.h` (Public)


#### class `FAssetsImportController`  
`class FAssetsImportController`  
_L8-23_
- L11 _private prototype_ `FAssetsImportController() = default;`
- L12 _private member_ `static TSharedPtr<FAssetsImportController> AssetsImportController;`
- L13 _private member_ `TArray<FString> SupportedAssetTypes = { TEXT("3d"), TEXT("3dplant"), TEXT("atlas"), TEXT("surface") };`
- L21 _public prototype_ `static TSharedPtr<FAssetsImportController> Get();`
- L22 _public prototype_ `void DataReceived(const FString DataFromBridge);`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API MEGASCANSPLUGIN_API`

### `Plugins/Bridge/Source/MegascansPlugin/Public/BridgeDragDropUtils.h` (Public)


#### class `FBridgeDragDropImpl`  
`class FBridgeDragDropImpl : public TSharedFromThis<FBridgeDragDropImpl>`  
_L14-20_
- inherits: `TSharedFromThis<FBridgeDragDropImpl>`
- L17 _public member_ `FOnAddProgressiveStageDataCallback OnAddProgressiveStageDataDelegate;`
- L19 _public prototype_ `void SetOnAddProgressiveStageData(FOnAddProgressiveStageDataCallback InDelegate);`

#### class `FBridgeDragDrop`  
`class FBridgeDragDrop`  
_L22-27_
- L25 _public prototype_ `static void Initialize();`
- L26 _public member_ `static TSharedPtr<FBridgeDragDropImpl> Instance;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API MEGASCANSPLUGIN_API`
- L12 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnAddProgressiveStageDataCallback, FAssetData AssetData, FString AssetId, AStaticMeshActor* SpawnedActor);`
- L12 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnAddProgressiveStageDataCallback, FAssetData AssetData, FString AssetId, AStaticMeshActor* SpawnedActor);`

### `Plugins/Bridge/Source/MegascansPlugin/Public/IMegascansLiveLinkModule.h` (Public)


#### class `IMegascansLiveLinkModule`  
`class IMegascansLiveLinkModule : public IModuleInterface`  
_L12-29_
- inherits: `IModuleInterface`
- L20 _public function_ `static inline IMegascansLiveLinkModule& Get()`
- L25 _public function_ `static inline bool IsAvailable()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define MS_MODULE_NAME TEXT("MegascansPlugin")`

### `Plugins/Bridge/Source/MegascansPlugin/Public/MSSettings.h` (Public)


#### class `UMegascansSettings`  
`class UMegascansSettings : public UObject`  
_L10-34_
- reflection: `UCLASS(Config = Editor)`
- inherits: `UObject`
- L20 _public member_ `bool bCreateFoliage;` — `UPROPERTY(Config, DisplayName = "Auto-Populate Foliage Painter", EditAnywhere, Category = "MegascansSettings")` — Populate Foliage Editor with Foliage Types for 3D Plants.
- L30 _public member_ `bool bApplyToSelection;` — `UPROPERTY(Config, DisplayName = "Apply to Selection", EditAnywhere, Category = "MegascansSettings")` — Apply imported Surface on selected Actors in Editor.

#### class `UMaterialBlendSettings`  
`class UMaterialBlendSettings : public UObject`  
_L37-51_
- reflection: `UCLASS(Config = Editor)`
- inherits: `UObject`
- L46 _public member_ `FString BlendedMaterialName;` — `UPROPERTY(Config, DisplayName = "Material Name", EditAnywhere, Category = "MaterialBlendSettings")` — Package name for Material Blend instance.
- L50 _public member_ `FDirectoryPath BlendedMaterialPath;` — `UPROPERTY(Config, DisplayName = "Destination Path", EditAnywhere, Category = "MaterialBlendSettings", meta = (ContentDir))` — Destination path for Material Blend instance.

#### class `UMaterialAssetSettings`  
`class UMaterialAssetSettings : public UObject`  
_L55-72_
- reflection: `UCLASS(Config = Editor)`
- inherits: `UObject`
- L64 _public member_ `FString MasterMaterial3d;` — `UPROPERTY(Config, DisplayName = "3D Master Material", EditAnywhere, Category = "MasterMaterialOverrides")`
- L67 _public member_ `FString MasterMaterialSurface;` — `UPROPERTY(Config, DisplayName = "Surface Master Material", EditAnywhere, Category = "MasterMaterialOverrides")`
- L70 _public member_ `FString MasterMaterialPlant;` — `UPROPERTY(Config, DisplayName = "Plant Master Material", EditAnywhere, Category = "MasterMaterialOverrides")`

#### class `UMaterialPresetsSettings`  
`class UMaterialPresetsSettings : public UObject`  
_L75-100_
- reflection: `UCLASS(Config = Editor)`
- inherits: `UObject`
- L85 _public member_ `TSoftObjectPtr<class UMaterial> MasterMaterial3d;` — `UPROPERTY(Transient, DisplayName = "3D Master Material", EditAnywhere, Category = "MasterMaterialOverrides")` — Replace default master material with your own custom master material for all 3D assets. Default material is used if field is left empty.
- L90 _public member_ `TSoftObjectPtr<class UMaterial> MasterMaterialSurface;` — `UPROPERTY(Transient, DisplayName = "Surface Master Material", EditAnywhere, Category = "MasterMaterialOverrides")` — Replace default master material with your own custom master material for all Surfaces. Default material is used if field is left empty.
- L94 _public member_ `TSoftObjectPtr<class UMaterial> MasterMaterialPlant;` — `UPROPERTY(Transient, DisplayName = "Plant Master Material", EditAnywhere, Category = "MasterMaterialOverrides")` — Replace default master material with your own custom master material for all 3D Plants. Default material is used if field is left empty.
- L97 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyThatWillChange) override;`

### `Plugins/Bridge/Source/MegascansPlugin/Public/SMSWindow.h` (Public)


#### class `MegascansSettingsWindow`  
`class MegascansSettingsWindow`  
_L15-24_
- L20 _public prototype_ `static void OpenSettingsWindow( );`
- L21 _public prototype_ `static void SaveSettings(const TSharedRef<SWindow>& Window, UMegascansSettings* MegascansSettings);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MEGASCANSPLUGIN_API`

### `Plugins/Bridge/Source/MegascansPlugin/Public/TCPServer.h` (Public)


#### class `FTCPServer`  
`class FTCPServer : public FRunnable`  
_L17-50_
- inherits: `FRunnable`
- L21 _public prototype_ `FTCPServer();`
- L22 _public prototype_ `~FTCPServer();`
- L23 _public prototype_ `virtual bool Init() override;`
- L24 _public prototype_ `virtual uint32 Run() override;`
- L26 _public function_ `virtual void Stop() override`
- L32 _public prototype_ `bool RecvMessage(FSocket *Socket, uint32 DataSize, FString& Message);`
- L33 _public prototype_ `bool HandleListenerConnectionAccepted(class FSocket *ClientSocket, const FIPv4Endpoint& ClientEndpoint);`
- L35 _public member_ `FSocket* ListenerSocket;`
- L36 _public member_ `FString LocalHostIP = "12`
- L37 _public member_ `int32 PortNum = 13429;`
- L38 _public member_ `int32 ConnectionTimeout;`
- L39 _public member_ `TArray<class FSocket*> Clients;`
- L41 _public prototype_ `void HandleIncomingSocket(FSocket* IncomingConnection);`
- L42 _public member_ `static TQueue<FString> ImportQueue;`
- L45 _private member_ `TQueue<class FSocket*, EQueueMode::Mpsc> PendingClients;`
- L46 _private member_ `bool Stopping;`
- L47 _private member_ `FRunnableThread* ClientThread = NULL;`
- L48 _private member_ `class FTcpListener *Listener = NULL;`
- L49 _private member_ `TArray<int32> ConnectionTimer;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MEGASCANSPLUGIN_API`
