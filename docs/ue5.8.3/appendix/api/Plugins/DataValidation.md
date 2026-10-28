# Plugins / DataValidation

- module root: `Plugins/Editor/DataValidation/Source/DataValidation`
- headers: 17; symbols: 425
- symbol kinds: class=14, delegate=1, enum=3, enumerator=11, function=21, macro=11, member=146, namespace=12, prototype=180, struct=24, typedef=2
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, BlueprintGraph, Blutility, CollectionManager, ContentBrowser, EditorFramework, EditorToolEvents, GraphEditor, InputCore, Json, KismetCompiler, LevelEditor, PropertyEditor, RHI, SandboxFile, Slate, SlateCore, SourceControl, TelemetryUtils, ToolMenus, TypedElementRuntime, UncontrolledChangelists, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, EditorSubsystem, Engine, TargetPlatform

### `Plugins/Editor/DataValidation/Source/DataValidation/Private/DataValidationTestActor.h` (Private)


#### class `ADataValidationTestActor`  
`class ADataValidationTestActor : public AActor`  
_L12-28_
- reflection: `UCLASS(showcategories=(HLOD, WorldPartition, DataLayers, Transformation))`
- inherits: `AActor`
- L17 _public prototype_ `ADataValidationTestActor(const FObjectInitializer& ObjectInitializer);`
- L20 _public member_ `bool bPassValidation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Validation")`
- L23 _public prototype_ `EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;`
- L27 _public member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY()`

### `Plugins/Editor/DataValidation/Source/DataValidation/Private/LoadExternalObjectsForValidation.h` (Private)


#### struct `UE::DataValidation::FScopedLoadExternalObjects`  
`struct FScopedLoadExternalObjects`  
_L17-27_
- desc: Utility to load external objects (e.g. actors) associated with an asset (e.g. a map) for validation so that they are available to validators inspecting the main asset. Should only be used on the stack.
- L19 _public prototype_ `FScopedLoadExternalObjects(UObject* InAsset, FDataValidationContext& InContext, bool bEnabled);`
- L20 _public prototype_ `~FScopedLoadExternalObjects();`
- L24 _private member_ `TArray<FWorldPartitionReference> ActorRefs;` — Hard refs keeping actors loaded for the same lifetime as this object
- L26 _private member_ `TArray<TStrongObjectPtr<UActorDescContainerInstance>> ContainersToUninit;` — Containers used for actor loading which must be explicitly uninitialized at the end of this object's lifetime

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DataValidation` (scope `UE`)

### `Plugins/Editor/DataValidation/Source/DataValidation/Private/PackageFileValidator.h` (Private)


#### class `UPackageFileValidator`  
`class UPackageFileValidator : public UEditorValidatorBase`  
_L21-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorValidatorBase`
- desc: This validator checks the format of the package on disk to make sure that is has not become corrupted since it was last saved. To disable the validator entirely, set ini:Editor:[/Script/DataValidation.PackageFileValidator]:bIsConfigDisabled=true To disable validation of payload hashes (which is much slower than the rest of the validation) set ini:Editor:[/Script/DataValidation.PackageFileValidator]:bValidatePayloadHashes=true
- L27 _protected prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& AssetData, UObject* Asset, FDataValidationContext& Context) const override;`
- L28 _protected prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& AssetData, UObject* Asset, FDataValidationContext& Context) override;`
- L32 _private prototype_ `bool ValidatePackageSummary(FName PackageName, FArchive& Ar, FDataValidationContext& Context, FPackageFileSummary& OutSummary);`
- L33 _private prototype_ `bool ValidatePackageTrailer(FName PackageName, FArchive& Ar, FDataValidationContext& Context);`
- L35 _private prototype_ `bool TryResolvePackagePath(FName PackageName, FPackagePath& OutPackagePath) const;`
- L38 _private member_ `bool bValidatePayloadHashes = true;` — `UPROPERTY(Config)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAVALIDATION_API`

### `Plugins/Editor/DataValidation/Source/DataValidation/Private/WorldPartitionChangelistValidator.h` (Private)


#### class `UWorldPartitionChangelistValidator`  
`class UWorldPartitionChangelistValidator : public UEditorValidatorBase, public IStreamingGenerationErrorHandler`  
_L16-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorValidatorBase,IStreamingGenerationErrorHandler`
- L21 _protected member_ `FTopLevelAssetPath RelevantMap;`
- L22 _protected member_ `TSet<FGuid> RelevantActorGuids;`
- L23 _protected member_ `TSet<FString> RelevantDataLayerAssets;`
- L24 _protected member_ `TSet<FString> RelevantExternalPackageDataLayerInstances;`
- L25 _protected member_ `UObject* CurrentAsset = nullptr;`
- L26 _protected member_ `bool bSubmittingWorldDataLayers = false;`
- L28 _protected prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;`
- L29 _protected prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;`
- L31 _protected prototype_ `void ValidateActorsAndDataLayersFromChangeList(UDataValidationChangelist* Changelist);`
- L34 _protected prototype_ `bool Filter(const IWorldPartitionActorDescInstanceView& ActorDescView);` — Return true if this ActorDescView is pertinent to the current ChangeList
- L37 _protected prototype_ `bool Filter(const UDataLayerInstance* DataLayerInstance);` — Return true if this UDataLayerInstance is pertinent to the current ChangeList
- L40 _protected prototype_ `virtual void OnInvalidRuntimeGrid(const IWorldPartitionActorDescInstanceView& ActorDescView, FName GridName) override;` — IStreamingGenerationErrorHandler Interface methods
- L41 _protected prototype_ `virtual void OnInvalidReference(const IWorldPartitionActorDescInstanceView& ActorDescView, const FGuid& ReferenceGuid, IWorldPartitionActorDescInstanceView* ReferenceActorDescView) override;`
- L42 _protected prototype_ `virtual void OnInvalidReferenceGridPlacement(const IWorldPartitionActorDescInstanceView& ActorDescView, const IWorldPartitionActorDescInstanceView& ReferenceActorDescView) override;`
- L43 _protected prototype_ `virtual void OnInvalidReferenceDataLayers(const IWorldPartitionActorDescInstanceView& ActorDescView, const IWorldPartitionActorDescInstanceView& ReferenceActorDescView, EDataLayerInvalidReason Reason) override;`
- L44 _protected prototype_ `virtual void OnInvalidWorldReference(const IWorldPartitionActorDescInstanceView& ActorDescView, EWorldReferenceInvalidReason Reason) override;`
- L45 _protected prototype_ `virtual void OnInvalidReferenceRuntimeGrid(const IWorldPartitionActorDescInstanceView& ActorDescView, const IWorldPartitionActorDescInstanceView& ReferenceActorDescView) override;`
- L46 _protected prototype_ `virtual void OnDataLayersLoadFilterMismatch(const IWorldPartitionActorDescInstanceView& ActorDescView) override;`
- L47 _protected prototype_ `virtual void OnInvalidReferenceDataLayerAsset(const UDataLayerInstanceWithAsset* DataLayerInstance) override;`
- L48 _protected prototype_ `virtual void OnInvalidDataLayerAssetType(const UDataLayerInstanceWithAsset* DataLayerInstance, const UDataLayerAsset* DataLayerAsset) override;`
- L49 _protected prototype_ `virtual void OnDataLayerHierarchyTypeMismatch(const UDataLayerInstance* DataLayerInstance, const UDataLayerInstance* Parent, EDataLayerHierarchyInvalidReason Reason) override;`
- L50 _protected prototype_ `virtual void OnInvalidWorldDataLayersReference(const AWorldDataLayers* WorldDataLayers, const UDataLayerInstance* DataLayerInstance, const FText& Reason) override;`
- L51 _protected prototype_ `virtual void OnDataLayerAssetConflict(const UDataLayerInstanceWithAsset* DataLayerInstance, const UDataLayerInstanceWithAsset* ConflictingDataLayerInstance) override;`
- L52 _protected prototype_ `virtual void OnActorNeedsResave(const IWorldPartitionActorDescInstanceView& ActorDescView) override;`
- L53 _protected prototype_ `virtual void OnLevelInstanceInvalidWorldAsset(const IWorldPartitionActorDescInstanceView& ActorDescView, FName WorldAsset, ELevelInstanceInvalidReason Reason) override;`
- L54 _protected prototype_ `virtual void OnInvalidActorFilterReference(const IWorldPartitionActorDescInstanceView& ActorDescView, const IWorldPartitionActorDescInstanceView& ReferenceActorDescView) override;`
- L55 _protected prototype_ `virtual void OnInvalidHLODLayer(const IWorldPartitionActorDescInstanceView& ActorDescView) override;`
- L56 _protected prototype_ `virtual void OnUnsupportedHLODLayer(const IWorldPartitionActorDescInstanceView& ActorDescView, const UHLODLayer* HLODLayer, EHLODLayerUnsupportedReason Reason) override;`
- L57 _protected prototype_ `virtual void OnRejectedActorDescViewMutator(const IWorldPartitionActorDescInstanceView& ActorDescView, const FActorDescViewMutator& RejectedOverrides, EActorDescViewMutatorRejectedReason Reason) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAVALIDATION_API`

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/DataValidationChangelist.h` (Public)


#### class `UDataValidationChangelist`  
`class UDataValidationChangelist : public UObject`  
_L18-50_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UObject`
- desc: Changelist abstraction to allow changelist-level data validation
- L24 _public prototype_ `UDataValidationChangelist() = default;` — Default constructor with nothing
- L26 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L29 _public prototype_ `void Initialize(TConstArrayView<FSourceControlStateRef> InFileStates);` — Initializes from a list of file states as a pseudo-changelist
- L31 _public prototype_ `void Initialize(FSourceControlChangelistPtr InChangelist);` — Initializes from a changelist reference, querying the state from the provider
- L33 _public prototype_ `void Initialize(FSourceControlChangelistStateRef InChangelistState);` — Initializes from an already-queried changelist state
- L35 _public prototype_ `static void GatherDependencies(const FName& InPackageName, TSet<TPair<FName, FName>>& OutDependencies);`
- L36 _public prototype_ `static FString GetPrettyPackageName(const FName& InPackageName);`
- L39 _public member_ `FSourceControlChangelistPtr Changelist;` — Changelist to validate - may be null if this was constructed from a list of files
- L42 _public member_ `TArray<FName> ModifiedPackageNames;` — Asset files in the changelist
- L43 _public member_ `TArray<FName> DeletedPackageNames;`
- L46 _public member_ `TArray<FString> ModifiedFiles;` — Non-asset files in the changelist
- L47 _public member_ `TArray<FString> DeletedFiles;`
- L49 _public member_ `FText Description;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DATAVALIDATION_API`

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/DataValidationCommandlet.h` (Public)


#### class `UDataValidationCommandlet`  
`class UDataValidationCommandlet : public UCommandlet`  
_L10-51_
- reflection: `UCLASS(MinimalAPI, CustomConstructor)`
- inherits: `UCommandlet`
- L15 _public function_ `UDataValidationCommandlet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L22 _public prototype_ `virtual int32 Main(const FString& FullCommandLine) override;`
- L26 _public prototype_ `static bool ValidateData(const FString& FullCommandLine);` — Run the commandlet validation logic without actually launching the editor in a commandlet mode.
- L29 _protected prototype_ `bool ValidateDataImpl(const FString& FullCommandLine);`
- L32 _protected prototype_ `void ProcessCommandLine(const FString& FullCommandLine);` — Parses the commandline and processes any found tokens/switch/parameters.
- L33 _protected prototype_ `virtual void ProcessCommandLine(const TArray<FString>& Tokens, const TArray<FString>& Switches, const TMap<FString, FString>& Params);`
- L35 _protected prototype_ `virtual bool GetAssetsToValidate(class IAssetRegistry& AssetRegistry, TArray<FAssetData>& OutAssetDataList);`
- L36 _protected prototype_ `virtual void FilterAssetsToValidate(TArray<FAssetData>& AssetDataList);`
- L38 _protected prototype_ `virtual bool ShouldLoadDefaultEditorModules(const TArray<FAssetData>& AssetDataList);`
- L40 _protected prototype_ `virtual void SetupValidationSettings(struct FValidateAssetsSettings& Settings);`
- L41 _protected prototype_ `virtual void ValidateAssets(const TArray<FAssetData>& AssetDataList, const struct FValidateAssetsSettings& InSettings, struct FValidateAssetsResults& OutResults);`
- L42 _protected prototype_ `virtual bool ProcessValidationResults(struct FValidateAssetsResults& Results);`
- L45 _protected prototype_ `static void WaitForAssetRegistry();` — Checks if the AssetRegistry is performing its initial startup scan, and if so waits for the scan to complete.
- L48 _protected member_ `FString AssetTypeFilterString;`
- L49 _protected member_ `bool bIncludeOnlyOnDiskAssets = false;`
- L50 _protected member_ `bool bWithoutEngine = true;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DATAVALIDATION_API`

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/DataValidationFixers.h` (Public)


#### struct `UE::DataValidation::FFixAlwaysApplicable`  
`struct FFixAlwaysApplicable`  
_L16-22_
- desc: Functor which always returns EFixApplicability::CanBeApplied.
- L18 _public function_ `EFixApplicability operator()() const`

#### struct `UE::DataValidation::TLambdaFixer`  
`template <typename GetApplicabilityT, typename ApplyFixT> struct TLambdaFixer : IFixer`  
_L29-49_
- inherits: `IFixer`
- desc: IFixer created out of a pair of lambdas. This can be constructed conveniently using MakeFix.
- L31 _public function_ `TLambdaFixer(GetApplicabilityT&& GetApplicabilityImpl, ApplyFixT&& ApplyFixImpl) : GetApplicabilityImpl(MoveTemp(GetApplicabilityImpl)) , ApplyFixImpl(MoveTemp(ApplyFixImpl))`
- L36 _public function_ `virtual EFixApplicability GetApplicability(int32 FixIndex) const override`
- L41 _public function_ `virtual FFixResult ApplyFix(int32 FixIndex) override`
- L47 _private member_ `GetApplicabilityT GetApplicabilityImpl;`
- L48 _private member_ `ApplyFixT ApplyFixImpl;`

#### struct `UE::DataValidation::FSingleUseFixer`  
`struct FSingleUseFixer : IFixer`  
_L69-78_
- inherits: `IFixer`
- desc: IFixer which wraps another fixer and makes it single use only. All fixers which are not idempotent will want to use this.
- L71 _public member_ `TSharedPtr<IFixer> Inner;`
- L72 _public member_ `TSet<int32> UsedFixes;`
- L74 _public prototype_ `virtual EFixApplicability GetApplicability(int32 FixIndex) const override;`
- L75 _public prototype_ `virtual FFixResult ApplyFix(int32 FixIndex) override;`
- L77 _public prototype_ `static TSharedRef<FSingleUseFixer> Create(TSharedRef<IFixer> Inner);`

#### struct `UE::DataValidation::FObjectSetDependentFixer`  
`struct FObjectSetDependentFixer : IFixer`  
_L81-90_
- inherits: `IFixer`
- desc: IFixer which wraps another fixer in a set of dependencies.
- L83 _public member_ `TSharedPtr<IFixer> Inner;`
- L84 _public member_ `TArray<TWeakObjectPtr<>> Dependencies;`
- L86 _public prototype_ `virtual EFixApplicability GetApplicability(int32 FixIndex) const override;`
- L87 _public prototype_ `virtual FFixResult ApplyFix(int32 FixIndex) override;`
- L89 _public prototype_ `static TSharedRef<FObjectSetDependentFixer> Create(TSharedRef<IFixer> Inner, TArray<TWeakObjectPtr<>> Dependencies);`

#### struct `UE::DataValidation::FAutoSavingFixer`  
`struct FAutoSavingFixer : IFixer`  
_L93-101_
- inherits: `IFixer`
- desc: IFixer which wraps another fixer and makes it auto-save the asset after the fix is applied.
- L95 _public member_ `TSharedPtr<IFixer> Inner;`
- L97 _public prototype_ `virtual EFixApplicability GetApplicability(int32 FixIndex) const override;`
- L98 _public prototype_ `virtual FFixResult ApplyFix(int32 FixIndex) override;`
- L100 _public prototype_ `static TSharedRef<FAutoSavingFixer> Create(TSharedRef<IFixer> Inner);`

#### struct `UE::DataValidation::FValidatingFixer`  
`struct FValidatingFixer : IFixer`  
_L104-112_
- inherits: `IFixer`
- desc: IFixer which wraps another fixer and makes it validate any assets touched by the fix.
- L106 _public member_ `TSharedPtr<IFixer> Inner;`
- L108 _public prototype_ `virtual EFixApplicability GetApplicability(int32 FixIndex) const override;`
- L109 _public prototype_ `virtual FFixResult ApplyFix(int32 FixIndex) override;`
- L111 _public prototype_ `static TSharedRef<FValidatingFixer> Create(TSharedRef<IFixer> Inner);`

#### struct `UE::DataValidation::FMutuallyExclusiveFixSet`  
`struct FMutuallyExclusiveFixSet`  
_L118-160_
- desc: IFixer made out of many smaller fixers. Only one of the fixes in the set may be applied. Once applied, the remaining fixers become non-applicable.
- L120 _public prototype_ `FMutuallyExclusiveFixSet();`
- L123 _public prototype_ `void Add(const FText& Label, TSharedRef<IFixer> Inner);` — Add a fixer to the set.
- L128 _public prototype_ `void Transform(const TFunctionRef<TSharedRef<IFixer>(TSharedRef<IFixer>)>& Callback);` — Transform all fixes. The callback will be called for each fix and should return a new, transformed fix.
- L130 _public prototype_ `void CreateTokens(const TFunctionRef<void(TSharedRef<FFixToken>)>& Callback) const;` — Generate FFixTokens from the set. These tokens can then be added to a message.
- L137 _private member_ `TSharedPtr<FSharedData> SharedData;`
- L159 _private member_ `TArray<FQueuedToken> QueuedTokens;`

#### struct `UE::DataValidation::FMutuallyExclusiveFixSet::FSharedData`  
`struct FSharedData`  
_L133-136_
- L135 _public member_ `int32 AppliedFix = INDEX_NONE;`

#### struct `UE::DataValidation::FMutuallyExclusiveFixSet::FFixer`  
`struct FFixer : IFixer`  
_L140-147_
- inherits: `IFixer`
- desc: Fix belonging to the mutually exclusive fix set.
- L142 _public member_ `TSharedPtr<IFixer> Inner;`
- L143 _public member_ `TSharedPtr<FSharedData> SharedData;`
- L145 _public prototype_ `virtual EFixApplicability GetApplicability(int32 FixIndex) const override;`
- L146 _public prototype_ `virtual FFixResult ApplyFix(int32 FixIndex) override;`

#### struct `UE::DataValidation::FMutuallyExclusiveFixSet::FQueuedToken`  
`struct FQueuedToken`  
_L153-157_
- desc: Token that is about to be created from the set. Note that tokens are not created immediately to allow Transform to work.
- L155 _public member_ `FText Label;`
- L156 _public member_ `TSharedRef<FFixer> Fixer;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATAVALIDATION_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DataValidation` (scope `UE`)
- L53 _function_ `template <typename GetApplicabilityT, typename ApplyFixT> TSharedRef<TLambdaFixer<GetApplicabilityT, ApplyFixT>> MakeFix(GetApplicabilityT&& GetApplicability, ApplyFixT&& ApplyFix)` (scope `UE::DataValidation`) — Makes an IFixer from applicability and application lambdas.
- L60 _function_ `template <typename ApplyFixT> TSharedRef<TLambdaFixer<FFixAlwaysApplicable, ApplyFixT>> MakeFix(ApplyFixT&& ApplyFix)` (scope `UE::DataValidation`) — Makes an always applicable IFixer from an application lambda.

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/DataValidationModule.h` (Public)


#### class `IDataValidationModule`  
`class IDataValidationModule : public IModuleInterface`  
_L14-45_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L25 _public function_ `static inline IDataValidationModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L44 _public prototype_ `virtual void ValidateAssets(const TArray<FAssetData>& SelectedAssets, bool bValidateDependencies, const EDataValidationUsecase InValidationUsecase) = 0;` — Validates selected assets and opens a window to report the results. If bValidateDependencies is true it will also validate any assets that the selected assets depend on.

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/DataValidationSettings.h` (Public)


#### class `UDataValidationSettings`  
`class UDataValidationSettings : public UDeveloperSettings`  
_L16-43_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UDeveloperSettings`
- desc: Project-wide settings for data validation
- L22 _public prototype_ `UDataValidationSettings();` — Default constructor that sets up CDO properties
- L26 _public member_ `uint32 bValidateOnSave : 1 = true;` — `UPROPERTY(EditAnywhere, Config, Category="Data Validation")` — Whether or not to validate assets on save
- L30 _public member_ `uint32 bLoadAssetsWhenValidatingChangelists : 1 = true;` — `UPROPERTY(EditAnywhere, Config, Category="Data Validation")` — Whether or not to load & validate assets in changelists by default
- L33 _public member_ `bool bEnableMaterialValidation = true;` — `UPROPERTY(EditAnywhere, Config, Category="Data Validation")`
- L36 _public member_ `bool bMaterialValidationAllowCompilingShaders = true;` — `UPROPERTY(Config)`
- L39 _public member_ `bool bMaterialValidationShowWarningsWhenNotCompilingShaders = true;` — `UPROPERTY(Config)`
- L42 _public member_ `TArray<FMaterialEditorValidationPlatform> MaterialValidationPlatforms;` — `UPROPERTY(EditAnywhere, Config, Category="Data Validation", meta=(EditCondition="bEnableMaterialValidation"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATAVALIDATION_API`

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/DataValidationTelemetry.h` (Public)


#### enum `UE::Telemetry::DataValidation::EValidationMode`  
`enum class EValidationMode`  
_L16-21_
- L18 _public enumerator_ `Unknown`
- L19 _public enumerator_ `Editor`
- L20 _public enumerator_ `Commandlet`

#### struct `UE::Telemetry::DataValidation::FValidatorStatistics`  
`struct FValidatorStatistics`  
_L23-27_
- L25 _public member_ `int32 AssetsValidated = 0;`
- L26 _public member_ `int32 AssetsAddedForValidation = 0;`

#### struct `UE::Telemetry::DataValidation::FValidateAssets`  
`struct FValidateAssets`  
_L30-65_
- desc: Telemetry for an operation where we validate some assets (or some changelists)
- L32 _public member_ `static inline constexpr FGuid TelemetryID{0x0e4e8035, 0xdce94c98, 0x94f64b35, 0xef12b049};`
- L34 _public prototype_ `FValidateAssets() = default;`
- L35 _public prototype_ `FValidateAssets(const FValidateAssetsSettings& InSettings);`
- L37 _public prototype_ `void SetResults(EDataValidationResult InOverallResult, const FValidateAssetsResults& InResults);`
- L39 _public member_ `double Duration = 0.0f;`
- L40 _public member_ `EValidationMode Mode = EValidationMode::Unknown;`
- L41 _public member_ `EDataValidationResult Result = EDataValidationResult::NotValidated;`
- L44 _public member_ `bool bSkipExcludedDirectories = false;` — From FValidateAssetsSettings
- L45 _public member_ `EDataValidationUsecase ValidationUsecase = EDataValidationUsecase::None;`
- L46 _public member_ `bool bLoadAssetsForValidation = false;`
- L47 _public member_ `bool bUnloadAssetsLoadedForValidation = false;`
- L48 _public member_ `bool bLoadExternalObjectsForValidation = false;`
- L49 _public member_ `bool bCaptureAssetLoadLogs = false;`
- L50 _public member_ `bool bCaptureLogsDuringValidation = false;`
- L51 _public member_ `bool bCaptureWarningsDuringValidationAsErrors = false;`
- L52 _public member_ `int32 MaxAssetsToValidate = 0;`
- L53 _public member_ `bool bValidateReferencersOfDeletedAssets = false;`
- L55 _public member_ `int NumRequested = 0;`
- L56 _public member_ `int NumExternalObjects = 0;`
- L57 _public member_ `int NumChecked = 0;`
- L58 _public member_ `int NumValid = 0;`
- L59 _public member_ `int NumInvalid = 0;`
- L60 _public member_ `int NumSkipped = 0;`
- L61 _public member_ `int NumWarnings = 0;`
- L62 _public member_ `int NumUnableToValidate = 0;`
- L63 _public member_ `bool bAssetLimitReached = false;`
- L64 _public member_ `TMap<FTopLevelAssetPath, FValidatorStatistics> ValidatorStatistics;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Telemetry` (scope `UE`)
- L14 _namespace_ `namespace DataValidation` (scope `UE::Telemetry`)

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/DirtyFilesChangelistValidator.h` (Public)


#### class `UDirtyFilesChangelistValidator`  
`class UDirtyFilesChangelistValidator : public UEditorValidatorBase`  
_L16-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorValidatorBase`
- desc: Validates there is no unsaved files in the changelist about to be submitted.
- L21 _protected prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;`
- L22 _protected prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAVALIDATION_API`

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/EditorValidatorBase.h` (Public)


#### class `UEditorValidatorBase`  
`class UEditorValidatorBase : public UObject`  
_L28-157_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (ShowWorldContextPin), Config=Editor)`
- inherits: `UObject`
- desc: The EditorValidatorBase is a class which verifies that an asset meets a specific ruleset. It should be used when checking engine-level classes, as UObject::IsDataValid requires overriding the base class. You can create project-specific version of the validator base, with custom logging and enabled logic. C++ and Blueprint validators will be gathered on editor start, while python validators need to register themselves
- L35 _public prototype_ `EDataValidationResult ValidateLoadedAsset(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& Context);` — Validation entry point - will dispatch to native and/or BP validation as appropriate and return results. If validator doesn't want to validate this asset/in this context, it will return NotValidated which is acceptable.
- L38 _public function_ `virtual TArray<FAssetData> GetAssetsToValidateFromChangelist(UDataValidationChangelist* InChangelist, FDataValidationContext& InContext) const` — Override this to return additional assets that need validation because of other changes in a changelist. e.g. referencers of a specific type may be broken by edits to a dependency.
- L44 _public function_ `virtual void PostAssetValidation(TArray<TSharedRef<FTokenizedMessage>>& OutMessages)` — Override this to do any state cleanup or add additional validation messages after all per asset validation is complete.
- L51 _protected function_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InObject, FDataValidationContext& InContext) const` — Override this to determine whether or not you can use this validator given this context. Context can be used to add errors if validation cannot be performed because of some issue
- L57 _protected function_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& Context)` — Override this to validate in C++ with access to FDataValidationContext
- L64 _protected prototype_ `bool K2_CanValidate(const EDataValidationUsecase InUsecase) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Asset Validation", DisplayName="Can Validate")` — Override this to determine whether or not you can use this validator given this usecase
- L68 _protected prototype_ `bool K2_CanValidateAsset(UObject* InAsset) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Asset Validation", DisplayName="Can Validate Asset")` — Override this to determine whether or not you can validate a given asset with this validator
- L69 _protected prototype_ `virtual bool K2_CanValidateAsset_Implementation(UObject* InAsset) const;`
- L73 _protected prototype_ `EDataValidationResult K2_ValidateLoadedAsset(UObject* InAsset);` — `UFUNCTION(BlueprintNativeEvent, Category = "Asset Validation", DisplayName="Validate Loaded Asset")` — Override this in blueprint to validate assets
- L74 _protected prototype_ `virtual EDataValidationResult K2_ValidateLoadedAsset_Implementation(UObject* InAsset);`
- L79 _public prototype_ `void AssetFails(const UObject* InAsset, const FText& InMessage);` — `UFUNCTION(BlueprintCallable, Category = "Asset Validation")` — Marks the validation as failed and adds an error message.
- L83 _public prototype_ `void AssetPasses(const UObject* InAsset);` — `UFUNCTION(BlueprintCallable, Category = "Asset Validation")` — Marks the validation as successful. Failure to call this will report the validator as not having checked the asset.
- L87 _public prototype_ `void AssetWarning(const UObject* InAsset, const FText& InMessage);` — `UFUNCTION(BlueprintCallable, Category = "Asset Validation")` — Adds a message to this validation but doesn't mark it as failed.
- L92 _public prototype_ `TSharedRef<FTokenizedMessage> AssetMessage(const FAssetData& InAssetData, EMessageSeverity::Type InSeverity, const FText& InText = {});` — Add a tokenized message to the validation results. If the severity is error, marks the validation as failed.
- L93 _public prototype_ `TSharedRef<FTokenizedMessage> AssetMessage(EMessageSeverity::Type InSeverity, const FText& InText = {});`
- L95 _public function_ `virtual bool IsEnabled() const`
- L100 _public prototype_ `void ResetValidationState();`
- L102 _public function_ `bool IsValidationStateSet() const`
- L108 _public function_ `EDataValidationResult GetValidationResult() const` — `UFUNCTION(BlueprintCallable, Category = "Asset Validation")`
- L113 _public prototype_ `const TArray<FText>& GetAllWarnings() const;`
- L115 _public prototype_ `void AddLegacyValidationErrors(TArray<FText> InErrors);`
- L116 _public prototype_ `EDataValidationResult ExtractValidationState(FDataValidationContext& InOutContext) const;`
- L121 _protected function_ `virtual bool CanValidate_Implementation(const EDataValidationUsecase InUsecase) const` — `UE_DEPRECATED("5.4", "CanValidate_Implementation(const EDataValidationUsecase InUsecase) is deprecated, override CanValidateAsset_Implementation(UObject* InObject, FDataValidationContext& InContext) instead")` — Legacy entry points from old interface
- L126 _protected function_ `virtual bool CanValidateAsset_Implementation(UObject* InAsset) const` — `UE_DEPRECATED("5.4", "CanValidateAsset_Implementation(UObject* InAsset) is deprecated, override CanValidateAsset_Implementation(UObject* InObject, FDataValidationContext& InContext) instead")`
- L131 _protected function_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(UObject* InAsset, TArray<FText>& ValidationErrors)` — `UE_DEPRECATED("5.4", "ValidateLoadedAsset_Implementation(UObject* InAsset, TArray<FText>& ValidationErrors) is deprecated, override ValidateLoadedAsset_Implementation(UObject* InAsset, FDataValidationContext& Context) instead")`
- L138 _protected member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Asset Validation", meta = (BlueprintProtected = "true"))`
- L142 _protected member_ `bool bIsConfigDisabled = false;` — `UPROPERTY(Config)` — Allows disabling validators from config without checking in assets/modifying code.
- L146 _protected member_ `bool bOnlyPrintCustomMessage = false;` — `UPROPERTY(EditAnywhere, Category = "Asset Validation", meta = (BlueprintProtected = "true"))` — Whether we should also print out the source validator when printing validation errors.
- L149 _private member_ `EDataValidationResult ValidationResult = EDataValidationResult::NotValidated;`
- L150 _private member_ `TArray<FText> AllWarnings;`
- L151 _private member_ `TArray<FText> AllErrors;`
- L152 _private member_ `TArray<TSharedRef<FTokenizedMessage>> AllMessages;`
- L155 _private member_ `TObjectPtr<UObject> CurrentObjectBeingValidated = nullptr;` — `UPROPERTY(Transient)`
- L156 _private member_ `const FAssetData* CurrentAssetBeingValidated = nullptr;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATAVALIDATION_API`
- L13 _namespace_ `namespace EMessageSeverity`

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/EditorValidatorHelpers.h` (Public)


#### struct `UE::DataValidation::FScopedLogMessageGatherer`  
`struct FScopedLogMessageGatherer`  
_L34-92_
- L36 _public prototype_ `FScopedLogMessageGatherer(bool bEnabled = true);`
- L37 _public prototype_ `~FScopedLogMessageGatherer();`
- L39 _public prototype_ `FScopedLogMessageGatherer(const FScopedLogMessageGatherer&) = delete;`
- L40 _public prototype_ `FScopedLogMessageGatherer& operator=(const FScopedLogMessageGatherer&) = delete;`
- L42 _public prototype_ `FScopedLogMessageGatherer(FScopedLogMessageGatherer&&) = delete;`
- L43 _public prototype_ `FScopedLogMessageGatherer& operator=(FScopedLogMessageGatherer&&) = delete;`
- L46 _public prototype_ `static FScopedLogMessageGatherer* GetCurrentThreadGatherer();` — Returns the current gather constructed on this thread in an enclosing scope if any
- L51 _public prototype_ `void Stop(TArray<FString>& OutWarnings, TArray<FString>& OutErrors);` — Stop gathering logs and return the warnings and errors gathered so far
- L57 _public prototype_ `TTuple<int32, int32> AddIgnoreCategories(TConstArrayView<FName> NewCategories);` — Tell this scope to ignore certain log messages @return A tuple that can be passed to RemoveIgnoreCategories to reverse this
- L63 _public prototype_ `void RemoveIgnoreCategories(TTuple<int32, int32> Range);` — Tell this scope to stop ignoring certain log messages. @param Range The return value from a previous call to AddIgnoreCategories
- L69 _public prototype_ `TTuple<int32, int32> AddIgnorePatterns(TConstArrayView<FWildcardString> NewPatterns);` — Tell this scope to ignore certain log messages @return A tuple that can be passed to RemoveIgnorePatterns to reverse this
- L75 _public prototype_ `void RemoveIgnorePatterns(TTuple<int32, int32> Range);` — Tell this scope to stop ignoring certain log messages. @param Range The return value from a previous call to AddIgnorePatterns
- L81 _public prototype_ `static TDelegate<TArray<FName>(void)>& GetDefaultIgnoreCategoriesDelegate();` — Delegate that may be bound by a project to set a default list of log categories to ignore during asset validation
- L87 _public prototype_ `static TDelegate<TArray<FWildcardString>(void)>& GetDefaultIgnorePatternsDelegate();` — Delegate that may be bound by a project to set a default list of log patterns to ignore during asset validation
- L90 _protected member_ `FScopedLogMessageGatherer* Previous = nullptr;`
- L91 _protected member_ `FLogMessageGathererImpl* Impl = nullptr;`

#### struct `UE::DataValidation::FScopedIgnoreLogMessages`  
`struct FScopedIgnoreLogMessages`  
_L95-103_
- desc: Utility to tell the closest enclosing FScopedLogMessageGatherer to ignore certain messages
- L97 _public prototype_ `FScopedIgnoreLogMessages(TConstArrayView<FWildcardString> Patterns, TConstArrayView<FName> Categories);`
- L98 _public prototype_ `~FScopedIgnoreLogMessages();`
- L101 _protected member_ `TTuple<int32, int32> PatternsRange = {0, 0};`
- L102 _protected member_ `TTuple<int32, int32> CategoriesRange = {0, 0};`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAVALIDATION_API`
- L24 _namespace_ `namespace EMessageSeverity`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace DataValidation` (scope `UE`)
- L106 _prototype_ `void AddAssetValidationMessages( const FAssetData& ForAsset, FMessageLog& Log, const FDataValidationContext& InContext);` (scope `UE::DataValidation`) — Helper to add asset validation messages from a validation context to a message log
- L112 _prototype_ `void AddAssetValidationMessages( FMessageLog& Log, const FDataValidationContext& InContext);` (scope `UE::DataValidation`) — Helper to add asset validation messages from a validation context to a message log
- L117 _prototype_ `void AddAssetValidationMessages( const FAssetData& ForAsset, FMessageLog& Log, EMessageSeverity::Type Severity, TConstArrayView<FText> Messages);` (scope `UE::DataValidation`) — Helper to format asset validation messages where the messages may contain references to assets that should be replaced by clickable tokens.
- L124 _prototype_ `FText MakeTimestampedMessageLogPageTitle(const FText& BaseTitle);` (scope `UE::DataValidation`) — Prepend the given UTC timestamp (or UtcNow if none provided) to the given base title to provide a pseudo-unique title, eg) "[Timestamp] BaseTitle"
- L125 _prototype_ `FText MakeTimestampedMessageLogPageTitle(const FText& BaseTitle, const FDateTime& UtcTimestamp);` (scope `UE::DataValidation`)
- L127 _prototype_ `void ValidationStatsToAnalyticEventData(const TMap<FTopLevelAssetPath, FValidatorStatistics>& ValidationStats, TArray<FAnalyticsEventAttribute>& OutEventAttributes);` (scope `UE::DataValidation`)
- L129 _prototype_ `void ValidationStatsToAnalyticEventData(const TMap<FTopLevelAssetPath, FValidatorStatistics>& ValidationStats, FCookStatsManager::AddStatFuncRef AddStat);` (scope `UE::DataValidation`)

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/EditorValidatorSubsystem.h` (Public)


#### struct `FValidateAssetsExternalObject`  
`struct FValidateAssetsExternalObject`  
_L37-44_
- L40 _public member_ `FName PackageName;` — Package Name
- L43 _public member_ `FName AssetName;` — Asset Name

#### struct `FValidateAssetsDetails`  
`struct FValidateAssetsDetails`  
_L47-71_
- reflection: `USTRUCT(BlueprintType)`
- L52 _public member_ `FName PackageName;` — Package Name
- L55 _public member_ `FName AssetName;` — Asset Name
- L58 _public member_ `EDataValidationResult Result = EDataValidationResult::Valid;` — Validation Result
- L61 _public member_ `TArray<FText> ValidationErrors;` — Validation Errors
- L64 _public member_ `TArray<FText> ValidationWarnings;` — Validation Warnings
- L67 _public member_ `TArray<TSharedRef<FTokenizedMessage>> ValidationMessages;` — Rich validation messages including tokens that can generate images or hyperlinks
- L70 _public member_ `TArray<FValidateAssetsExternalObject> ExternalObjects;` — List of external objects for this asset

#### struct `FValidatorStatistics`  
`struct FValidatorStatistics`  
_L74-89_
- reflection: `USTRUCT(BlueprintType)`
- L80 _public member_ `int32 AssetsValidated = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Validation")` — Number of assets validated by this validator
- L84 _public member_ `int32 AssetsAddedForValidation = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Validation")` — Number of assets that this validator marked as needing validation e.g. because a dependency changed
- L88 _public member_ `double TotalDurationSeconds = 0.0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — Total time (in seconds) that this validator spent validating assets

#### struct `FValidateAssetsResults`  
`struct FValidateAssetsResults`  
_L92-148_
- reflection: `USTRUCT(BlueprintType)`
- L96 _public prototype_ `FValidateAssetsResults() = default;`
- L100 _public member_ `int NumRequested = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — Total amount of assets that were gathered to validate, not including external objects such as actors.
- L104 _public member_ `int NumExternalObjects = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — Total amount of external objects to validate with their owning asset (e.g. actors with maps).
- L108 _public member_ `int NumChecked = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — Amount of tested assets
- L112 _public member_ `int NumValid = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — Amount of assets without errors or warnings
- L116 _public member_ `int NumInvalid = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — Amount of assets with errors
- L120 _public member_ `int NumSkipped = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — Amount of assets skipped
- L124 _public member_ `int NumWarnings = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — Amount of assets with warnings
- L128 _public member_ `int NumUnableToValidate = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — Amount of assets that could not be validated
- L132 _public member_ `bool bAssetLimitReached = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — True if FValidateAssetSettings::MaxAssetsToValidation was reached
- L136 _public member_ `TMap<FTopLevelAssetPath, FValidatorStatistics> ValidatorStatistics;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — Per-validator statistics on assets validated and assets added for validation
- L144 _public member_ `TMap<FString, FValidateAssetsDetails> AssetsDetails;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Validation")` — Per asset details Indexed by object path Only returned if FValidateAssetsSettings::bCollectPerAssetDetails is true.
- L147 _public member_ `TArray<TSharedRef<FTokenizedMessage>> ValidatorMessages;` — Additional validator tokenized messages not specific to a single asset.

#### struct `FValidateAssetsSettings`  
`struct FValidateAssetsSettings`  
_L151-223_
- reflection: `USTRUCT(BlueprintType)`
- L155 _public prototype_ `FValidateAssetsSettings();`
- L156 _public prototype_ `~FValidateAssetsSettings();`
- L160 _public member_ `bool bSkipExcludedDirectories = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")` — If true, will not validate files in excluded directories
- L164 _public member_ `bool bShowIfNoFailures = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")` — If true, will add notifications for files with no validation and display even if everything passes
- L168 _public member_ `bool bCollectPerAssetDetails = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")` — If true, will add an FValidateAssetsDetails for each asset to the results
- L172 _public member_ `EDataValidationUsecase ValidationUsecase = EDataValidationUsecase::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")` — The usecase requiring datavalidation
- L176 _public member_ `bool bLoadAssetsForValidation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")` — If false, unloaded assets will get skipped from validation.
- L180 _public member_ `bool bUnloadAssetsLoadedForValidation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")` — If true, will attempt to unload assets which were previously unloaded, and loaded for validation.
- L187 _public member_ `bool bLoadExternalObjectsForValidation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")` — If false, external objects (e.g. actors stored separately from maps) will not be loaded when validating their associated asset (e.g. the map)
- L191 _public member_ `bool bCaptureAssetLoadLogs = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")` — If true, captures log warnings and errors from loading assets for validation and reports them as validation results
- L195 _public member_ `bool bCaptureLogsDuringValidation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")` — If true, captures log warnings and errors from other operations that happen during validation and adds them to validation results
- L199 _public member_ `bool bCaptureWarningsDuringValidationAsErrors = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")` — If true, captured log warnings during validation are added to the validation results as errors (requires bCaptureLogsDuringValidation)
- L203 _public member_ `int32 MaxAssetsToValidate = MAX_int32;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")` — Maximum number of assets to attempt to validate
- L207 _public member_ `bool bValidateReferencersOfDeletedAssets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Validation")` — Should we validate referencers of deleted assets in changelists
- L213 _public member_ `TOptional<EMessageSeverity::Type> ShowMessageLogSeverity;` — Minimum severity of validation messages to make the message log visible after validation. Defaults to warning, can be disabled by emptying the optional.
- L216 _public member_ `FName MessageLogName;` — The name of the message log to use for warnings/errors/etc
- L219 _public member_ `FText MessageLogPageTitle;` — Title of message log page to use for warnings/errors/etc
- L222 _public member_ `bool bSilent = false;` — Show progress window

#### struct `FScopedDisableValidateOnSave`  
`struct FScopedDisableValidateOnSave`  
_L229-239_
- desc: Utility to disable "validate on save" in UEditorValidatorSubsystem for the lifetime of this object. Calls UEditorValidatorSubsystem::PushDisableValidateOnSave on construction and UEditorValidatorSubsystem::PopDisableValidateOnSave on destruction.
- L232 _public prototype_ `FScopedDisableValidateOnSave();`
- L233 _public prototype_ `~FScopedDisableValidateOnSave();`
- L238 _private member_ `UEditorValidatorSubsystem* EditorValidationSubsystem;`

#### class `UEditorValidatorSubsystem`  
`class UEditorValidatorSubsystem : public UEditorSubsystem`  
_L258-575_
- reflection: `UCLASS(MinimalAPI, Config = Editor)`
- inherits: `UEditorSubsystem`
- desc: UEditorValidatorSubsystem manages all the asset validation in the engine. The first validation handled is UObject::IsDataValid and its overridden functions. Those validations require custom classes and are most suited to project-specific classes. The next validation set is of all registered UEditorValidationBases. These validators have a function to determine if they can validate a given asset, and if they are currently enabled. They are good candidates for validating engine classes or very specific project logic. Finally, this subsystem may be subclassed to change the overally behavior of validation in your project. If a subclass exist in your project module, it will supercede the engine validation subsystem.
- L263 _public prototype_ `UEditorValidatorSubsystem();`
- L265 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L266 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection);`
- L267 _public prototype_ `virtual void Deinitialize();`
- L273 _public prototype_ `void PushDisableValidateOnSave();` — Push a new request to temporarily disable "validate on save". Should be paired with a call to PopDisableValidateOnSave.
- L279 _public prototype_ `void PopDisableValidateOnSave();` — Pop a previous request to temporarily disable "validate on save". Should be paired with a call to PushDisableValidateOnSave.
- L290 _public prototype_ `virtual int32 ValidateAssetsWithSettings( const TArray<FAssetData>& AssetDataList, const FValidateAssetsSettings& InSettings, FValidateAssetsResults& OutResults) const;` — `UFUNCTION(BlueprintCallable, Category = "Asset Validation")` — Called to validate assets from either the UI or a commandlet. Loads the specified assets and runs all registered validators on them. Populates the message log with errors and warnings with clickable links. @param InSettings Structure passing context and settings for ValidateAssetsWithSettings @param OutResults More detailed information about the results of the validate assets command @returns Number of assets with validation failures or warnings
- L304 _public prototype_ `virtual EDataValidationResult ValidateChangelist( UDataValidationChangelist* InChangelist, const FValidateAssetsSettings& InSettings, FValidateAssetsResults& OutResults) const;` — `UFUNCTION(BlueprintCallable, Category = "Asset Validation")` — Called to validate assets from either the UI or a commandlet. Loads the specified assets and runs all registered validators on them. Populates the message log with errors and warnings with clickable links. @param InSettings Structure passing context and settings for ValidateAssetsWithSettings @param OutResults More detailed information about the results of the validate assets command @returns Validation results for the changelist object itself
- L310 _public prototype_ `virtual EDataValidationResult ValidateChangelists( const TArray<UDataValidationChangelist*> InChangelists, const FValidateAssetsSettings& InSettings, FValidateAssetsResults& OutResults) const;` — `UFUNCTION(BlueprintCallable, Category = "Asset Validation")`
- L319 _public prototype_ `void AddValidator(UEditorValidatorBase* InValidator);` — `UFUNCTION(BlueprintCallable, Category = "Validation")` — Adds a validator to the list, making sure it is a unique instance
- L326 _public prototype_ `void RemoveValidator(UEditorValidatorBase* InValidator);` — `UFUNCTION(BlueprintCallable, Category = "Validation")` — Removes a validator Should be called during module shutdown if a validator was added.
- L332 _public prototype_ `void ForEachEnabledValidator(TFunctionRef<bool(UEditorValidatorBase* Validator)> Callback) const;` — Iterate the enabled set of validators. @note Return true to continue iteration, or false to stop.
- L340 _public prototype_ `virtual EDataValidationResult IsObjectValid( UObject* InObject, TArray<FText>& ValidationErrors, TArray<FText>& ValidationWarnings, const EDataValidationUsecase InValidationUsecase) const;` — `UFUNCTION(BlueprintCallable, Category = "Asset Validation")` — Runs registered validators on the provided object. Does not add anything to any FMessageLog tabs. @return Returns Valid if the object contains valid data; returns Invalid if the object contains invalid data; returns NotValidated if no validations was performed on the object
- L351 _public prototype_ `virtual EDataValidationResult IsObjectValidWithContext( UObject* InObject, FDataValidationContext& InContext) const;` — Runs registered validators on the provided object. Does not add anything to any FMessageLog tabs. @return Returns Valid if the object contains valid data; returns Invalid if the object contains invalid data; returns NotValidated if no validations was performed on the object
- L361 _public prototype_ `virtual EDataValidationResult IsAssetValid( const FAssetData& AssetData, TArray<FText>& ValidationErrors, TArray<FText>& ValidationWarnings, const EDataValidationUsecase InValidationUsecase) const;` — `UFUNCTION(BlueprintCallable, Category = "Asset Validation")` — Loads the object referred to by the provided AssetData and runs registered validators on it. Does not add anything to any FMessageLog tabs. @return Returns Valid if the object pointed to by AssetData contains valid data; returns Invalid if the object contains invalid data or does not exist; returns NotValidated if no validations was performed on the object
- L372 _public prototype_ `virtual EDataValidationResult IsAssetValidWithContext( const FAssetData& AssetData, FDataValidationContext& InContext) const;` — Loads the object referred to by the provided AssetData and runs registered validators on it. Does not add anything to any FMessageLog tabs. @return Returns Valid if the object pointed to by AssetData contains valid data; returns Invalid if the object contains invalid data or does not exist; returns NotValidated if no validations was performed on the object
- L382 _public prototype_ `virtual void ValidateOnSave(TArray<FAssetData> AssetDataList, bool bProceduralSave) const;` — Called to validate from an interactive save @param AssetDataList List of Assets to validate @param bProceduralSave True iff this is e.g. a save from the editor, false if it is a procedural change from e.g. cooking
- L390 _public prototype_ `virtual void ValidateSavedPackage(FName PackageName, bool bProceduralSave);` — Schedule a validation of a saved package, this will activate next frame by default so it can combine them @param PackageName Package to validate @param bProceduralSave True iff this is e.g. a save from the editor, false if it is a procedural change from e.g. cooking
- L398 _public prototype_ `virtual void GatherAssetsToValidateFromChangelist( UDataValidationChangelist* InChangelist, const FValidateAssetsSettings& Settings, TSet<FAssetData>& OutAssets, FDataValidationContext& InContext, FValidateAssetsResults& OutResults) const;` — From a changelist, return a list of assets to validate. The base implementation returns assets in modified packages in the changelist. Subclasses may wish to validate additional assets based on files in the changelist (e.g. dependencies, relevant code changes, configuration changes, etc)
- L412 _public prototype_ `virtual bool ShouldValidateAsset( const FAssetData& Asset, const FValidateAssetsSettings& Settings, FDataValidationContext& InContext) const;` — Returns true if the given asset should be validated at all. May be overridden to e.g. skip developer/test assets. Used to determine which assets should be validated when gathering assets from a source such as a changelist. Will be ignored when an asset is directly passed for validation.
- L421 _public prototype_ `TArray<FAssetData> GetAssetsResolvingRedirectors(FARFilter& InFilter);` — Retrieve all assets matching the given filter from the asset registry and then recursively resolve redirectors to produce a single set of assets.
- L427 _public function_ `const FString& GetDataValidationCommandletClassName() const` — Gets the full class object path of the UDataValidationCommandlet class to use when the Editor needs to instantiate the commandlet to run validation on the entire project. If empty, UDataValidationCommandlet will be used.
- L431 _protected prototype_ `bool ShouldValidateOnSave(bool bProceduralSave) const;`
- L433 _protected prototype_ `void CleanupValidators();`
- L435 _protected prototype_ `void WaitForAssetCompilationIfNecessary(EDataValidationUsecase InUsecase, bool bShowProgress = true) const;`
- L440 _protected prototype_ `virtual bool IsPathExcludedFromValidation(FStringView Path) const;` — @return Returns true if the current Path should be skipped for validation. Returns false otherwise.
- L445 _protected prototype_ `void ValidateAllSavedPackages();` — Handles validating all pending save packages
- L447 _protected prototype_ `void RegisterNativeValidators();`
- L449 _protected prototype_ `void RegisterBlueprintValidators();`
- L454 _protected prototype_ `void ValidateChangelistPreSubmit(FSourceControlChangelistPtr Changelist, FSourceControlValidationDelegateResult& OutResult) const;` — Validates changelist before SCC submit operation
- L459 _protected prototype_ `void ValidateFilesPreSubmit(TArray<FSourceControlStateRef>& States, FSourceControlValidationDelegateResult& OutResult) const;` — Validates files before SCC submit operation
- L464 _protected prototype_ `void OnNativeModulesChanged(FName InModuleName, EModuleChangeReason InModuleChangeReason);` — Handle native modules being loaded or unloaded (@see NativeModulesPendingLoad and NativeModulesPendingUnload)
- L469 _protected prototype_ `void OnAssetsAdded(TConstArrayView<FAssetData> InAssets);` — Handle Blueprint assets being added or removed (@see ValidatorClassesPendingLoad)
- L470 _protected prototype_ `void OnAssetsRemoved(TConstArrayView<FAssetData> InAssets);`
- L471 _protected prototype_ `void OnAssetsAddedOrRemoved(TConstArrayView<FAssetData> InAssets, TFunctionRef<void(const FTopLevelAssetPath& BPGC)> Callback);`
- L476 _protected prototype_ `void UpdateValidators() const;` — Apply any pending changes to the list of active validators (@see ValidatorClassesPendingLoad, NativeModulesPendingLoad, and NativeModulesPendingUnload)
- L477 _protected prototype_ `void UpdateValidators();`
- L482 _protected prototype_ `void AddValidator(const FTopLevelAssetPath& InValidatorClass);` — Adds a validator to the list making sure it is a unique instance, but wait for the first use to load the class (for Blueprints).
- L487 _protected prototype_ `void RemoveValidator(const FTopLevelAssetPath& InValidatorClass);` — Remove any validators (active or pending) for the given class.
- L490 _private prototype_ `void AddValidator_Internal(UEditorValidatorBase* InValidator);`
- L491 _private prototype_ `void AddValidator_Internal(FTopLevelAssetPath InValidatorClass);`
- L492 _private prototype_ `void RemoveValidator_Internal(UEditorValidatorBase* InValidator);`
- L493 _private prototype_ `void RemoveValidator_Internal(FTopLevelAssetPath InValidatorClass);`
- L500 _protected prototype_ `EDataValidationResult ValidateAssetsInternal( FMessageLog& DataValidationLog, TSet<FAssetData> Assets, const FValidateAssetsSettings& InSettings, FValidateAssetsResults& OutResults ) const;` — Validate a set of assets, adding the results to the log/output of a higher level task (e.g. changelist validation).
- L507 _protected prototype_ `EDataValidationResult ValidateChangelistsInternal( TConstArrayView<UDataValidationChangelist*> InChangelists, const FValidateAssetsSettings& InSettings, FValidateAssetsResults& OutResults) const;`
- L512 _protected prototype_ `void LogAssetValidationSummary(FMessageLog& DataValidationLog, const FValidateAssetsSettings& InSettings, EDataValidationResult Result, const FValidateAssetsResults& Results) const;`
- L514 _protected prototype_ `EDataValidationResult ValidateObjectInternal( const FAssetData& InAssetData, UObject* InObject, FDataValidationContext& InContext, TMap<FTopLevelAssetPath, FValidatorStatistics>* ValidatorStatistics = nullptr) const;`
- L524 _protected member_ `TArray<FDirectoryPath> ExcludedDirectories;` — `UPROPERTY(config)` — Directories to ignore for data validation. Useful for test assets
- L531 _protected member_ `FString DataValidationCommandletClassName;` — `UPROPERTY(config)` — The full class object path of the UDataValidationCommandlet class to use when the Editor needs to instantiate the commandlet to run validation on the entire project. If empty, UDataValidationCommandlet will be used.
- L537 _protected member_ `bool bValidateOnSave;` — `UPROPERTY(config, meta = (DeprecatedProperty, DeprecationMessage = "Use bValidateOnSave on UDataValidationSettings instead."))` — Whether it should validate assets on save inside the editor
- L540 _protected member_ `mutable TSet<FName> SavedPackagesToValidate;` — List of saved package names to validate next frame
- L547 _protected member_ `TMap<FTopLevelAssetPath, TObjectPtr<UEditorValidatorBase>> Validators;` — `UPROPERTY(Transient)` — Active validator instances, mapped from their class. @note Some instances may be null until UpdateValidators has been called (@see ValidatorClassesPendingLoad)
- L552 _protected member_ `TSet<FTopLevelAssetPath> ValidatorClassesPendingLoad;` — Set of Blueprint validator classes (from Validators) that have been discovered since the set of validators was last updated, and need to be loaded by the next call to UpdateValidators.
- L557 _protected member_ `TSet<FName> NativeModulesPendingLoad;` — Set of native modules that have been loaded since the set of validators was last updated, and should be queried for new validator classes by the next call to UpdateValidators.
- L562 _protected member_ `TSet<FName> NativeModulesPendingUnload;` — Set of native modules that have been unloaded since the set of validators was last updated, and should be removed from Validators by the next call to UpdateValidators.
- L564 _protected member_ `bool bHasRegisteredNativeValidators = false;`
- L565 _protected member_ `bool bHasRegisteredBlueprintValidators = false;`
- L569 _protected member_ `bool bAllowBlueprintValidators;` — `UPROPERTY(config)` — Specifies whether or not to allow Blueprint validators
- L574 _protected member_ `uint32 DisableValidateOnSaveCount = 0;` — Counter used by PushDisableValidateOnSave and PopDisableValidateOnSave to know whether "validate on save" is temporarily disabled.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DATAVALIDATION_API`
- L25 _typedef_ `typedef TSharedPtr<class ISourceControlChangelist, ESPMode::ThreadSafe> FSourceControlChangelistPtr;`
- L26 _typedef_ `typedef TSharedRef<class ISourceControlState, ESPMode::ThreadSafe> FSourceControlStateRef;`
- L30 _namespace_ `namespace EMessageSeverity`
- L35 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogContentValidation, Log, All);`
- L35 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogContentValidation, Log, All);`

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/EditorValidator_ActionUtility.h` (Public)


#### class `UEditorValidator_ActionUtility`  
`class UEditorValidator_ActionUtility : public UEditorValidatorBase`  
_L15-22_
- reflection: `UCLASS()`
- inherits: `UEditorValidatorBase`
- desc: Checks if UActorActionUtility and UAssetActionUtility data is valid
- L20 _protected prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;`
- L21 _protected prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;`

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/EditorValidator_Localization.h` (Public)


#### class `UEditorValidator_Localization`  
`class UEditorValidator_Localization : public UEditorValidatorBase`  
_L15-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorValidatorBase`
- desc: Validates that localized assets (within the L10N folder) conform to a corresponding source asset of the correct type. Localized assets that fail this validation will never be loaded as localized variants at runtime.
- L20 _public prototype_ `UEditorValidator_Localization();`
- L23 _protected prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;`
- L24 _protected prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;`
- L26 _protected prototype_ `const TArray<FString>* FindOrCacheCulturesForLocalizedRoot(const FString& InLocalizedRootPath);`
- L28 _protected member_ `TMap<FString, TArray<FString>> CachedCulturesForLocalizedRoots;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAVALIDATION_API`

### `Plugins/Editor/DataValidation/Source/DataValidation/Public/EditorValidator_Material.h` (Public)


#### class `UEditorValidator_Material`  
`class UEditorValidator_Material : public UEditorValidatorBase`  
_L19-44_
- reflection: `UCLASS()`
- inherits: `UEditorValidatorBase`
- desc: Checks if UMaterial and UMaterialInstance are compiling on all validation shader platforms
- L24 _public prototype_ `UEditorValidator_Material();`
- L27 _protected prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;`
- L28 _protected prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;`
- L39 _private member_ `TArray<FShaderValidationPlatform> ValidationPlatforms;`
- L42 _private prototype_ `static UMaterial* DuplicateMaterial(UMaterial* OriginalMaterial);` — Creates a duplicate asset in transient package, will return nullptr if nullptr is passed.
- L43 _private prototype_ `static UMaterialInstance* DuplicateMaterialInstance(UMaterialInstance* OriginalMaterialInstance);`

#### struct `UEditorValidator_Material::FShaderValidationPlatform`  
`struct FShaderValidationPlatform`  
_L31-37_
- L33 _public member_ `FName ShaderPlatformName;`
- L34 _public member_ `EShaderPlatform ShaderPlatform;`
- L35 _public member_ `ERHIFeatureLevel::Type FeatureLevel;`
- L36 _public member_ `EMaterialQualityLevel::Type MaterialQualityLevel;`

#### class `UValidationMaterial`  
`class UValidationMaterial : public UMaterial`  
_L47-54_
- reflection: `UCLASS()`
- inherits: `UMaterial`
- L52 _public prototype_ `virtual FMaterialResource* AllocateResource() override;`
- L53 _public function_ `virtual bool IsAsset() const override`

#### struct `FMaterialEditorValidationShaderPlatform`  
`struct FMaterialEditorValidationShaderPlatform`  
_L57-71_
- reflection: `USTRUCT()`
- L62 _public member_ `FName Name = MaxRHIShaderPlatformName;` — `UPROPERTY(EditAnywhere, config, Category="Data Validation")`
- L65 _public member_ `static constexpr FStringView MaxRHIShaderPlatformNameView = TEXTVIEW("GMa` — if Name == MaxRHIShaderPlatformName, use GMaxRHIShaderPlatform instead
- L66 _public member_ `static FName MaxRHIShaderPlatformName;`
- L68 _public member_ `static FName CustomPropertyTypeLayoutName;`
- L69 _public prototype_ `static void RegisterCustomPropertyTypeLayout();`
- L70 _public prototype_ `static void UnregisterCustomPropertyTypeLayout();`

#### enum `EMaterialEditorValidationFeatureLevel`  
`enum class EMaterialEditorValidationFeatureLevel : int32`  
_L74-80_
- reflection: `UENUM()`
- L76 _public enumerator_ `CurrentMaxFeatureLevel = ERHIFeatureLevel::Num + 1 UMETA(DisplayName="Current Max Feature Level")`
- L77 _public enumerator_ `ES3_1 = ERHIFeatureLevel::ES3_1 UMETA(DisplayName="ES3.1")`
- L78 _public enumerator_ `SM5 = ERHIFeatureLevel::SM5`
- L79 _public enumerator_ `SM6 = ERHIFeatureLevel::SM6`

#### enum `EMaterialEditorValidationQualityLevel`  
`enum class EMaterialEditorValidationQualityLevel : uint8`  
_L83-89_
- reflection: `UENUM()`
- L85 _public enumerator_ `Low = EMaterialQualityLevel::Low`
- L86 _public enumerator_ `Medium = EMaterialQualityLevel::Medium`
- L87 _public enumerator_ `High = EMaterialQualityLevel::High`
- L88 _public enumerator_ `Epic = EMaterialQualityLevel::Epic`

#### struct `FMaterialEditorValidationPlatform`  
`struct FMaterialEditorValidationPlatform`  
_L92-104_
- reflection: `USTRUCT()`
- L97 _public member_ `FMaterialEditorValidationShaderPlatform ShaderPlatform = {};` — `UPROPERTY(EditAnywhere, config, Category="Data Validation")`
- L100 _public member_ `EMaterialEditorValidationFeatureLevel FeatureLevel = EMaterialEditorValidationFeatureLevel::CurrentMaxFeatureLevel;` — `UPROPERTY(EditAnywhere, config, Category="Data Validation")`
- L103 _public member_ `EMaterialEditorValidationQualityLevel MaterialQualityLevel = EMaterialEditorValidationQualityLevel::Epic;` — `UPROPERTY(EditAnywhere, config, Category="Data Validation")`
