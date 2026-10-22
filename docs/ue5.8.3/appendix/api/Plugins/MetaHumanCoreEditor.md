# Plugins / MetaHumanCoreEditor

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCoreEditor`
- headers: 3; symbols: 32
- symbol kinds: class=3, delegate=1, macro=2, member=13, prototype=13
- PrivateDependencyModuleNames: AssetDefinition, CaptureDataCore, CaptureDataEditor, CoreUObject, Engine, InputCore, MetaHumanCore, PropertyEditor, RigLogicModule, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCoreEditor/Public/MetaHumanCameraCalibrationImporterFactory.h` (Public)


#### class `UMetaHumanCameraCalibrationImporterFactory`  
`class UMetaHumanCameraCalibrationImporterFactory : public UFactory , public FReimportHandler`  
_L13-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory,FReimportHandler`
- L20 _public prototype_ `UMetaHumanCameraCalibrationImporterFactory(const FObjectInitializer& InObjectInitializer);`
- L25 _protected prototype_ `virtual FText GetToolTip() const override;`
- L26 _protected prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L27 _protected prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, const FString& InFileName, const TCHAR* InParams, FFeedbackContext* InWarn, bool& bOutOperationCanceled);`
- L30 _protected prototype_ `virtual bool CanReimport(UObject* InObj, TArray<FString>& OutFilenames) override;`
- L31 _protected prototype_ `virtual void SetReimportPaths(UObject* InObj, const TArray<FString>& InNewReimportPaths) override;`
- L32 _protected prototype_ `virtual EReimportResult::Type Reimport(UObject* InObj) override;`
- L34 _protected prototype_ `virtual TObjectPtr<UObject>* GetFactoryObject() const override;`
- L35 _protected member_ `mutable TObjectPtr<UObject> GCMark{ this };`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCOREEDITOR_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCoreEditor/Public/MetaHumanCoreEditorModule.h` (Public)


#### class `IMetaHumanCoreEditorModule`  
`class IMetaHumanCoreEditorModule : public IModuleInterface`  
_L8-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetMetaHumanAssetCategoryPath() const = 0;`
- L13 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetMetaHumanAdvancedAssetCategoryPath() const = 0;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCoreEditor/Public/MetaHumanEditorSettings.h` (Public)


#### class `UMetaHumanEditorSettings`  
`class UMetaHumanEditorSettings : public UObject`  
_L15-72_
- reflection: `UCLASS(MinimalAPI, Config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L22 _public prototype_ `UMetaHumanEditorSettings();`
- L25 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangeEvent) override;`
- L31 _public member_ `int32 SampleCount;` — `UPROPERTY(Config, EditAnywhere, Category = "A/B split", meta = (ClampMin = "1", ClampMax = "8", UIMin = "1", UIMax = "8"))` — Number of samples when using A/B split window - higher value gives better quality but uses more memory
- L35 _public member_ `int32 MaximumResolution;` — `UPROPERTY(Config, EditAnywhere, Category = "A/B split", meta = (ClampMin = "128", ClampMax = "65536", UIMin = "128", UIMax = "65536"))` — Maximum effective resolution of A/B split window
- L39 _public member_ `bool bForceSerialIngestion;` — `UPROPERTY(Config, EditAnywhere, Category = "Capture Source")` — If true will force the ingestion process to run sequentially
- L43 _public member_ `bool bShowDevelopersContent;` — `UPROPERTY(Config, EditAnywhere, Category = "Capture Source")` — If true, capture sources from the developers content folder will be shown in the Capture Manager
- L47 _public member_ `bool bShowOtherDevelopersContent;` — `UPROPERTY(Config, EditAnywhere, Category = "Capture Source")` — If true, capture sources from the developers content folder of other users will be shown in the Capture Manager
- L51 _public member_ `bool bLoadTrackersOnStartup;` — `UPROPERTY(Config, EditAnywhere, Category = "Tracking")` — If true trackers will be loaded when opening identity
- L55 _public member_ `bool bTrainSolversFastLowMemory_DEPRECATED;` — `UPROPERTY(Config)` — If true identities will be prepared for performance using a fast, but memory intensive, method. Only applicable to machines with <64Gb of memory
- L59 _public member_ `TMap<FString, FString> PerformanceViewSetupSlot1;` — `UPROPERTY(Config, EditAnywhere, Category = "Performance view setup", DisplayName = "Slot 1")` — Slots for storing the Performance editor's view setup. A means of saving and recalling A/B modes, display options, open widgets etc
- L62 _public member_ `TMap<FString, FString> PerformanceViewSetupSlot2;` — `UPROPERTY(Config, EditAnywhere, Category = "Performance view setup", DisplayName = "Slot 2")`
- L65 _public member_ `TMap<FString, FString> PerformanceViewSetupSlot3;` — `UPROPERTY(Config, EditAnywhere, Category = "Performance view setup", DisplayName = "Slot 3")`
- L68 _public member_ `TMap<FString, FString> PerformanceViewSetupSlot4;` — `UPROPERTY(Config, EditAnywhere, Category = "Performance view setup", DisplayName = "Slot 4")`
- L71 _public member_ `FMetaHumanEditorSettingsChanged OnSettingsChanged;` — Delegate called when a property changes

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCOREEDITOR_API`
- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE(FMetaHumanEditorSettingsChanged);`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE(FMetaHumanEditorSettingsChanged);`
