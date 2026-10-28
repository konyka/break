# Plugins / InterchangeEditor

- module root: `Plugins/Interchange/Editor/Source/InterchangeEditor`
- headers: 7; symbols: 41
- symbol kinds: class=6, delegate=1, function=4, macro=3, member=4, prototype=23
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, ContentBrowser, EditorSubsystem, InputCore, InterchangeCommonParser, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeFbxParser, InterchangeImport, InterchangeNodes, InterchangePipelines, LevelEditor, MessageLog, Slate, SlateCore, ToolMenus
- PublicDependencyModuleNames: Core, CoreUObject, Engine, UnrealEd

### `Plugins/Interchange/Editor/Source/InterchangeEditor/Private/AssetDefinition_InterchangeSceneImportAsset.h` (Private)


#### class `UAssetDefinition_InterchangeSceneImportAsset`  
`class UAssetDefinition_InterchangeSceneImportAsset : public UAssetDefinitionDefault`  
_L11-31_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L26 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L30 _private member_ `static FAssetCategoryPath Interchange;`

### `Plugins/Interchange/Editor/Source/InterchangeEditor/Private/InterchangePipelineSettingsCacheHandler.h` (Private)


#### class `FInterchangePipelineSettingsCacheHandler`  
`class FInterchangePipelineSettingsCacheHandler`  
_L9-22_
- L12 _public prototype_ `static void InitializeCacheHandler();`
- L14 _public prototype_ `static void OnAssetRemoved(const FAssetData& RemovedAsset);`
- L16 _public prototype_ `static void ShutdownCacheHandler();`
- L19 _private member_ `static TSet<uint32> CachedPipelineHashes;`
- L21 _private member_ `static FDelegateHandle AssetRemovedHandle;`

### `Plugins/Interchange/Editor/Source/InterchangeEditor/Private/InterchangeResetContextMenuExtender.h` (Private)


#### class `FInterchangeResetContextMenuExtender`  
`class FInterchangeResetContextMenuExtender`  
_L6-14_
- L9 _public prototype_ `static void SetupLevelEditorContextMenuExtender();`
- L10 _public prototype_ `static void RemoveLevelEditorContextMenuExtender();`
- L13 _private member_ `static FDelegateHandle LevelEditorExtenderDelegateHandle;`

### `Plugins/Interchange/Editor/Source/InterchangeEditor/Public/InterchangeEditorLog.h` (Public)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeEditor, Log, All)`

### `Plugins/Interchange/Editor/Source/InterchangeEditor/Public/InterchangeEditorModule.h` (Public)


#### class `FInterchangeEditorModule`  
`class FInterchangeEditorModule : public IModuleInterface`  
_L11-20_
- inherits: `IModuleInterface`
- desc: This module allows out-of-process Interchange translators in case a third-party SDK is not thread-safe.
- L14 _public prototype_ `static FInterchangeEditorModule& Get();`
- L15 _public prototype_ `static bool IsAvailable();`
- L18 _private prototype_ `virtual void StartupModule() override;`
- L19 _private prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define INTERCHANGEEDITOR_MODULE_NAME TEXT("InterchangeEditor")`

### `Plugins/Interchange/Editor/Source/InterchangeEditor/Public/InterchangeEditorScriptLibrary.h` (Public)


#### class `UInterchangeEditorScriptLibrary`  
`class UInterchangeEditorScriptLibrary : public UBlueprintFunctionLibrary`  
_L17-97_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L26 _public prototype_ `static void ResetLevelAsset(UWorld* World);` — `UFUNCTION(BlueprintCallable, Category="Interchange Utilities | Reset")` — Performs Interchange Reset on a Level Asset. @param World is the level asset to reset.
- L34 _public prototype_ `static void ResetSceneImportAsset(UInterchangeSceneImportAsset* SceneImportAsset);` — `UFUNCTION(BlueprintCallable, Category = "Interchange Utilities | Reset")` — Performs Interchange Reset on an Interchange Scene Import Asset. Resets all the actors added to the level and assets imported. @param SceneImportAsset to reset
- L42 _public prototype_ `static void ResetActors(TArray<AActor*> Actors);` — `UFUNCTION(BlueprintCallable, Category = "Interchange Utilities | Reset")` — Performs Interchange Reset on Actors. Resets all qualifying actors. Does nothing to actors that cannot be reset. @param Actors array containing actors to reset
- L50 _public prototype_ `static bool CanResetActor(const AActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = "Interchange Utilities | Reset")` — Checks if an actor can be reset. @param Actor to check @return can actor be reset.
- L58 _public prototype_ `static bool CanResetWorld(const UWorld* World);` — `UFUNCTION(BlueprintCallable, Category = "Interchange Utilities | Reset")` — Checks if an world can be reset. @param World to check @return can world be reset.
- L66 _public prototype_ `static bool LevelInstanceEnterEditMode(ALevelInstance* LevelInstance);` — `UFUNCTION(BlueprintCallable, Category = "Interchange Utilities | Reset")` — Make Level Instance Actor editable. @param LevelInstance actor to edit @return whether putting level instance in edit mode was successful.
- L75 _public prototype_ `static bool LevelInstanceCommit(ALevelInstance* LevelInstance, bool bDiscardChanges);` — `UFUNCTION(BlueprintCallable, Category = "Interchange Utilities | Reset")` — Apply/Discard the changes to Level Instance Actor. @param LevelInstance actor to commit @param bDiscardChanges should changes be applied or discarded. @return whether committing level instance was successful.
- L85 _public prototype_ `static const TArray<AActor*> LevelInstanceGetEditableActors(ALevelInstance* LevelInstance);` — `UFUNCTION(BlueprintCallable, Category = "Interchange Utilities | Reset")` — Returns array of actors that are editable in the editor when the level instance is put in edit mode. NOTE: This will return a non-empty array if the LevelInstance is put in the edit mode. @param LevelInstance to get editable actors from @return Array of editable actors.
- L96 _public prototype_ `static TArray<AActor*> LevelInstanceGetActors(ALevelInstance* LevelInstance);` — `UFUNCTION(BlueprintCallable, Category = "Interchange Utilities | Level Instance")` — Returns all actors contained within a loaded level instance. Does not require the level instance to be in edit mode. Returns an empty array if the level instance is not loaded. @param LevelInstance to get actors from @return Array of actors in the level instance.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API INTERCHANGEEDITOR_API`

### `Plugins/Interchange/Editor/Source/InterchangeEditor/Public/InterchangeFbxAssetImportDataConverter.h` (Public)


#### class `UInterchangeFbxAssetImportDataConverter`  
`class UInterchangeFbxAssetImportDataConverter : public UInterchangeAssetImportDataConverterBase`  
_L15-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeAssetImportDataConverterBase`
- L20 _public prototype_ `virtual bool CanConvertClass(const UClass* SourceClass, const UClass* DestinationClass) const override;`
- L22 _public prototype_ `virtual bool ConvertImportData(UObject* Asset, const FString& ToExtension) const override;`
- L23 _public prototype_ `virtual bool ConvertImportData(const UObject* SourceImportData, const UClass* DestinationClass, UObject** DestinationImportData) const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEEDITOR_API`
