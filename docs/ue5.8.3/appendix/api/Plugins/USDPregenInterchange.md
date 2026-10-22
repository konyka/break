# Plugins / USDPregenInterchange

- module root: `Plugins/Experimental/USDPregen/Source/USDPregenInterchange`
- headers: 5; symbols: 32
- symbol kinds: class=5, delegate=1, member=15, prototype=9, struct=1, typedef=1
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, ContentBrowser, InterchangeEngine, InterchangeFactoryNodes, InterchangeOpenUSDImport, LevelSequence, USDUtilities, UnrealEd, UnrealUSDWrapper
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, InterchangeCore, USDPregenWrapper

### `Plugins/Experimental/USDPregen/Source/USDPregenInterchange/Public/USDPregenBlueprintLibrary.h` (Public)


#### class `UUSDPregenBlueprintLibrary`  
`class UUSDPregenBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L18-58_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L57 _public prototype_ `static void ImportFile(const FPregenImportOptions& ImportOptions, const FUSDPregenOnImportDoneDynamic& OnImportDone);` — `UFUNCTION(BlueprintCallable, Category = "USD Pregen", meta = (AutoCreateRefTerm = "OnImportDone"))` — Kicks off an asynchronous USD pregen import described by ImportOptions. If bound, OnImportDone fires on the game thread once manifests have been stored, optionally persisted, and (when ImportOptions.bAutoSavePackages is true) imported asset packages have been saved to disk. This wraps FUSDPregenInterchangeModule::ImportFile for Python and blueprint usage. OnImportDone is optional. === Python usage === import unreal import_options = unreal.PregenImportOptions() import_options.source_file_path = '/abs/path/to/scene.usda' # Plugin choice and discovery/storage options all live on the # nested option structs. Leave any field empty for the default. import_options.discovery_options.discovery_plugin_name = 'my_studio_discovery' import_options.discovery_options.definition_prefix = 'Shot_42_' import_options.discovery_options.initial_path = '/Root/Hero' import_options.storage_options.storage_plugin_name = 'json_storage' import_options.storage_options.package_sub_path_template = 'assets/${DEFINITION_NAME}/${PERMUTATION_ID}' # Without callback (fire-and-forget): unreal.USDPregenBlueprintLibrary.import_file(import_options, unreal.USDPregenOnImportDoneDynamic()) # With callback: def on_done(completed_options, success, saved_paths): print('Done!') delegate = unreal.USDPregenOnImportDoneDynamic() delegate.bind_callable(on_done) unreal.USDPregenBlueprintLibrary.import_file(import_options, delegate)

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams( FUSDPregenOnImportDoneDynamic, const FPregenImportOptions&, ImportOptions, bool, bSuccess, const TArray<FString>&, SavedPackageFilePaths);`
- L11 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams( FUSDPregenOnImportDoneDynamic, const FPregenImportOptions&, ImportOptions, bool, bSuccess, const TArray<FString>&, SavedPackageFilePaths);`

### `Plugins/Experimental/USDPregen/Source/USDPregenInterchange/Public/USDPregenContext.h` (Public)


#### class `UUSDPregenContext`  
`class UUSDPregenContext : public UInterchangeUsdContext`  
_L22-44_
- reflection: `UCLASS()`
- inherits: `UInterchangeUsdContext`
- desc: Pregen-aware USD context that overrides asset node UID generation to produce stable, target-remapped UIDs. This causes all instances of the same pregen target to converge to the same node UID, achieving deduplication. Set as the USD context on SourceData (via the standard "USD" tag) in place of the base UInterchangeUsdContext.
- L27 _public prototype_ `virtual FString MakeAssetNodeUid(const UE::FUsdPrim& Prim, const FString& Prefix = FString(), const FString& Suffix = FString()) const override;`
- L31 _public member_ `TSharedPtr<UE::UsdPregen::FSceneDiscovery> SceneDiscovery;` — SceneDiscovery instance, needed for GetTargetData() lookups. Wrapped in TSharedPtr because FSceneDiscovery has no default constructor.
- L34 _public member_ `UE::UsdPregen::FSceneDiscovery::ResultMap SceneDiscoveryResults;` — Map of prim path -> target UIDs from the discovery/traversal phase
- L37 _public member_ `UE::UsdPregen::FStoragePlugin Storage;` — Storage plugin used for GetPackageSubPathForUAsset
- L43 _public member_ `FString AllowedTargetUid;` — When non-empty, only prims whose owning pregen target's UID string matches this value are processed by the pipeline / accumulated into manifests. Every other factory node is disabled. Empty = process every discovered target (default editor behavior).

### `Plugins/Experimental/USDPregen/Source/USDPregenInterchange/Public/USDPregenInterchangeModule.h` (Public)


#### struct `FPregenImportOptions`  
`struct FPregenImportOptions`  
_L18-61_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes a single pregen import. Passed to FUSDPregenInterchangeModule::ImportFile and also exposed to Blueprint / Python via UUSDPregenBlueprintLibrary. Forward-compatible with worker-driven imports that need to filter to a single target, apply permutation overlays, override plugins, etc.
- L24 _public member_ `FString SourceFilePath;` — `UPROPERTY(BlueprintReadWrite, Category = "USD Pregen")` — Required: USD file to import.
- L29 _public member_ `FString TargetUid;` — `UPROPERTY(BlueprintReadWrite, Category = "USD Pregen")` — Optional filter to import only a specific target. Empty means to import all discovered targets.
- L34 _public member_ `FString PermutationLayerPath;` — `UPROPERTY(BlueprintReadWrite, Category = "USD Pregen")` — Optional USD layer to sublayer onto the entry stage to apply permutation operations. Empty means no permutation layer.
- L38 _public member_ `FString Title;` — `UPROPERTY(BlueprintReadWrite, Category = "USD Pregen")` — Optional human-readable label for logs.
- L43 _public member_ `FPregenDiscoveryOptions DiscoveryOptions;` — `UPROPERTY(BlueprintReadWrite, Category = "USD Pregen")` — Options for the discovery plugin, including the name of the plugin to use. Empty values fall back to defaults
- L48 _public member_ `FPregenStorageOptions StorageOptions;` — `UPROPERTY(BlueprintReadWrite, Category = "USD Pregen")` — Options for the storage plugin, including the name of the plugin to use. Empty values fall back to defaults
- L54 _public member_ `bool bAutomated = true;` — `UPROPERTY(BlueprintReadWrite, Category = "USD Pregen")` — When true, ImportFile runs the underlying Interchange import in automated mode (FImportAssetParameters::bIsAutomated = true), which suppresses the modal pipeline-options dialog and any other UI prompts.
- L60 _public member_ `bool bAutoSavePackages = false;` — `UPROPERTY(BlueprintReadWrite, Category = "USD Pregen")` — When true, ImportFile calls Storage->PersistManifestPayload(...) for each target whose manifest was Stored, AND saves imported asset packages to disk after import completes

#### class `FUSDPregenInterchangeModule`  
`class FUSDPregenInterchangeModule : public IModuleInterface`  
_L63-81_
- inherits: `IModuleInterface`
- L66 _public prototype_ `virtual void StartupModule() override;`
- L67 _public prototype_ `virtual void ShutdownModule() override;`
- L73 _public typedef_ `using FOnImportDone = TFunction<void( const FPregenImportOptions& ImportOptions, bool bSuccess, const TArray<FString>& SavedPackageFilePaths)>;` — Callback fired on the game thread when an async pregen import completes. Receives the originating ImportOptions so callers can correlate to their submission, a success bool, and the on-disk file paths for any UAssets that were saved (only populated when ImportOptions.bAutoSavePackages was true).
- L80 _public prototype_ `static void ImportFile(const FPregenImportOptions& ImportOptions, FOnImportDone OnImportDone = nullptr);` — Runs a full pregen import described by ImportOptions via Interchange. Optionally fires OnImportDone when the async import completes.

### `Plugins/Experimental/USDPregen/Source/USDPregenInterchange/Public/USDPregenPipeline.h` (Public)


#### class `UUSDPregenPipeline`  
`class UUSDPregenPipeline : public UInterchangePipelineBase`  
_L15-25_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UInterchangePipelineBase`
- desc: Pipeline that handles managing the produced assets for USD Pregen
- L20 _protected prototype_ `virtual void ExecutePipeline( UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath ) override;`

### `Plugins/Experimental/USDPregen/Source/USDPregenInterchange/Public/USDPregenSettings.h` (Public)


#### class `UUSDPregenSettings`  
`class UUSDPregenSettings : public UDeveloperSettings`  
_L12-54_
- reflection: `UCLASS(BlueprintType, config = USDPregen, defaultconfig, meta = (DisplayName = "USD Pregen"))`
- inherits: `UDeveloperSettings`
- L17 _public prototype_ `UUSDPregenSettings();`
- L21 _public member_ `FDirectoryPath ImportContentPath;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, config, Category = "USD Pregen", meta = (ContentDir))` — Content directory where USD Pregen imports will place assets.
- L42 _public member_ `FString PackageSubPathTemplate = TEXT("ass` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, config, Category = "USD Pregen")` — Template used to build the package sub-path for UAssets produced by USD Pregen imports. Recognized ${PLACEHOLDER} substitutions: ${DEFINITION_NAME}    - leaf asset definition name (e.g. "tree_02") ${DEFINITION_VERSION} - leaf asset definition version (e.g. "v2.1") ${DEFINITION_UID}     - leaf asset definition unique id ${PERMUTATION_ID}     - target's permutation id ${ASSET_TYPE}         - Unreal asset type (e.g. "StaticMesh") ${METADATA:KEY}       - looks up KEY in the leaf definition's metadata (populated from USD assetInfo, less the built-in keys). Nested dicts are descended via colon-separated paths, e.g. ${METADATA:nested:subcategory}. Missing keys, dict-valued leaves, and array-valued leaves collapse to the "_" sentinel. Values are sanitized to package-name-safe characters (alphanumeric and underscore). Empty values become the sentinel "_" so adjacent labels don't end up as orphans: e.g. "versions/${DEFINITION_VERSION}/" with no version becomes "versions/_/"
- L49 _public member_ `TArray<FSoftObjectPath> Pipelines;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, config, Category = "USD Pregen", meta = (AllowedClasses = "/Script/InterchangeCore.InterchangePipelineBase, /Script/InterchangeEngine.InterchangeBlueprintPipelineBase, /Script/InterchangeEngine.InterchangePythonPipelineAsset"))` — Pipeline stack used for USD Pregen scene imports via Interchange. These pipelines override the default Interchange pipeline stack when importing through the Pregen button.
- L52 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
