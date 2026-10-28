# Plugins / GameFeaturesEditor

- module root: `Plugins/Runtime/GameFeatures/Source/GameFeaturesEditor`
- headers: 7; symbols: 81
- symbol kinds: class=6, delegate=1, function=4, macro=1, member=31, namespace=2, prototype=34, struct=2
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, DataLayerEditor, DataValidation, DeveloperSettings, EditorFramework, EditorSubsystem, Engine, Json, ModularGameplay, Projects, PropertyEditor, SharedSettingsWidgets, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, GameFeatures, UnrealEd

### `Plugins/Runtime/GameFeatures/Source/GameFeaturesEditor/Private/GameFeatureActionConvertContentBundleWorldPartitionBuilder.h` (Private)


#### class `UGameFeatureActionConvertContentBundleWorldPartitionBuilder`  
`class UGameFeatureActionConvertContentBundleWorldPartitionBuilder : public UWorldPartitionBuilder`  
_L15-37_
- reflection: `UCLASS()`
- inherits: `UWorldPartitionBuilder`
- L20 _public function_ `virtual bool RequiresCommandletRendering() const override` — UWorldPartitionBuilder interface begin
- L21 _public function_ `virtual ELoadingMode GetLoadingMode() const override`
- L22 _public prototype_ `virtual bool PreRun(UWorld* World, FPackageSourceControlHelper& PackageHelper) override;`
- L23 _public prototype_ `virtual bool RunInternal(UWorld* World, const FCellInfo& InCellInfo, FPackageSourceControlHelper& PackageHelper) override;`
- L27 _private prototype_ `UExternalDataLayerAsset* GetOrCreateExternalDataLayerAsset(const UContentBundleDescriptor* InContentBundleDescriptor, UExternalDataLayerFactory* InExternalDataLayerFactory, TSet<UPackage*>& OutPackagesToSave) const;`
- L29 _private member_ `TSet<TSharedPtr<FContentBundleEditor>> SkippedEmptyContentBundles;`
- L30 _private member_ `TSet<TSharedPtr<FContentBundleEditor>> ConvertedContentBundles;`
- L31 _private member_ `TArray<FString> FinalReport;`
- L32 _private member_ `TArray<FString> ContentBundlesToConvert;`
- L33 _private member_ `FString DestinationFolder;`
- L34 _private member_ `bool bReportOnly;`
- L35 _private member_ `bool bRemoveContentBundleAction;`
- L36 _private member_ `bool bDeleteHLODs;`

### `Plugins/Runtime/GameFeatures/Source/GameFeaturesEditor/Private/GameFeatureDataDetailsCustomization.h` (Private)


#### class `FGameFeatureDataDetailsCustomization`  
`class FGameFeatureDataDetailsCustomization : public IDetailCustomization`  
_L21-50_
- inherits: `IDetailCustomization`
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L32 _protected prototype_ `void ChangeDesiredState(EGameFeaturePluginState State);`
- L34 _protected prototype_ `EGameFeaturePluginState GetCurrentState() const;`
- L35 _protected prototype_ `EVisibility GetVisbililty() const;`
- L37 _protected prototype_ `ECheckBoxState GetDebugStateEnabled() const;`
- L38 _protected prototype_ `void SetDebugStateEnabled(ECheckBoxState InCheckState);`
- L40 _protected prototype_ `FText GetInitialStateText() const;`
- L41 _protected prototype_ `FText GetTagConfigPathText() const;`
- L43 _protected prototype_ `static void OnOperationCompletedOrFailed(const UE::GameFeatures::FResult& Result, const TWeakPtr<FGameFeatureDataDetailsCustomization> WeakThisPtr);`
- L45 _protected member_ `TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;`
- L46 _protected member_ `FString PluginURL;`
- L47 _protected member_ `TSharedPtr<IPlugin> PluginPtr;`
- L49 _protected member_ `TSharedPtr<SErrorText> ErrorTextWidget;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace GameFeatures` (scope `UE`)

### `Plugins/Runtime/GameFeatures/Source/GameFeaturesEditor/Private/GameFeaturePluginMetadataCustomization.h` (Private)


#### class `FGameFeaturePluginMetadataCustomization`  
`class FGameFeaturePluginMetadataCustomization : public FPluginEditorExtension`  
_L16-30_
- inherits: `FPluginEditorExtension`
- L19 _public prototype_ `void CustomizeDetails(FPluginEditingContext& InPluginContext, IDetailLayoutBuilder& DetailBuilder);`
- L21 _public prototype_ `virtual void CommitEdits(FPluginDescriptor& Descriptor) override;`
- L23 _private prototype_ `EGameFeaturePluginState GetDefaultState() const;`
- L25 _private prototype_ `void ChangeDefaultState(EGameFeaturePluginState DesiredState);`
- L27 _private member_ `TSharedPtr<IPlugin> Plugin;`
- L29 _private member_ `EGameFeaturePluginState InitialState;`

### `Plugins/Runtime/GameFeatures/Source/GameFeaturesEditor/Private/GameFeaturesEditorSettings.h` (Private)


#### struct `FPluginTemplateData`  
`struct FPluginTemplateData`  
_L20-61_
- reflection: `USTRUCT()`
- desc: Data for specifying a usable plugin template. -Plugin templates are a folder/file structure that are duplicated and renamed by the plugin creation wizard to easily create new plugins with a standard format. See PluginUtils.h for more information.
- L25 _public member_ `FDirectoryPath Path;` — `UPROPERTY(EditAnywhere, Category = PluginTemplate, meta = (RelativePath))`
- L28 _public member_ `FText Label;` — `UPROPERTY(EditAnywhere, Category = PluginTemplate)`
- L31 _public member_ `FText Description;` — `UPROPERTY(EditAnywhere, Category = PluginTemplate)`
- L35 _public member_ `FString DefaultSubfolder;` — `UPROPERTY(EditAnywhere, Category = PluginTemplate)` — Optional sub folder that new plugins will be created in.
- L39 _public member_ `FString DefaultPluginName;` — `UPROPERTY(EditAnywhere, Category = PluginTemplate)` — Optional plugin name to default the new plugin to.
- L43 _public member_ `TSubclassOf<UGameFeatureData> DefaultGameFeatureDataClass;` — `UPROPERTY(config, EditAnywhere, Category = Plugins)` — The default class of game feature data to create for new game feature plugins (if not set, UGameFeatureData will be used)
- L47 _public member_ `FString DefaultGameFeatureDataName;` — `UPROPERTY(config, EditAnywhere, Category = Plugins)` — The default name of the created game feature data assets. If empty, will use the plugin name.
- L51 _public member_ `bool bIsEnabledByDefault = false;` — `UPROPERTY(config, EditAnywhere, Category = Plugins)` — If true, the created plugin will be enabled by default without needing to be added to the project file.
- L55 _public member_ `FFilePath PostCreatePythonScriptPath;` — `UPROPERTY(config, EditAnywhere, Category = Plugins, meta = (RelativePath))` — Optional path to a post create python script that will run when new plugins are created from this template.
- L59 _public member_ `FString PostCreatePythonScriptArguments;` — `UPROPERTY(config, EditAnywhere, Category = Plugins)` — Optional post create python script arguments.

#### class `UGameFeaturesEditorSettings`  
`class UGameFeaturesEditorSettings : public UDeveloperSettings`  
_L65-73_
- reflection: `UCLASS(MinimalAPI, config = Editor, defaultconfig)`
- inherits: `UDeveloperSettings`
- L72 _public member_ `TArray<FPluginTemplateData> PluginTemplates;` — `UPROPERTY(config, EditAnywhere, Category = Plugins)` — Array of Plugin templates. Allows projects to specify reusable plugin templates for the plugin creation wizard.

### `Plugins/Runtime/GameFeatures/Source/GameFeaturesEditor/Private/IllegalPluginDependenciesValidator.h` (Private)


#### class `UIllegalPluginDependenciesValidator`  
`class UIllegalPluginDependenciesValidator : public UEditorValidatorBase`  
_L16-23_
- reflection: `UCLASS()`
- inherits: `UEditorValidatorBase`
- desc: Ensures that non-GameFeaturePlugins do not depend on GameFeaturePlugins. GameFeaturePlugins will load content later than non-GameFeaturePlugins which could cause linker load issues if they do not exist.
- L21 _protected prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;`
- L22 _protected prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;`

### `Plugins/Runtime/GameFeatures/Source/GameFeaturesEditor/Private/SGameFeatureStateWidget.h` (Private)


#### class `SGameFeatureStateWidget`  
`class SGameFeatureStateWidget : public SCompoundWidget`  
_L17-39_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SGameFeatureStateWidget)`
- L26 _public function_ `SGameFeatureStateWidget()`
- L28 _public prototype_ `void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `static FText GetDisplayNameOfState(EGameFeaturePluginState State);`
- L31 _public prototype_ `static FText GetTooltipOfState(EGameFeaturePluginState StateID);`
- L34 _private prototype_ `FText GetStateStatusDisplay() const;`
- L35 _private prototype_ `FText GetStateStatusDisplayTooltip() const;`
- L38 _private member_ `TAttribute<EGameFeaturePluginState> CurrentState;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWidgetChangesGameFeatureState, EGameFeaturePluginState) class SGameFeatureStateWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SGameFeatureStateWidget) {} SLATE_ATTRIBUTE(EGameFeaturePluginState, CurrentState) SLATE_EVENT(FOnWidgetChangesGameFeatureState, OnStateChanged) SLATE_END_ARGS() public: SGameFeatureStateWidget() {} void Construct(const FArguments& InArgs); static FText GetDisplayNameOfState(EGameFeaturePluginState State); static FText GetTooltipOfState(EGameFeaturePluginState StateID); private: FText GetStateStatusDisplay() const; FText GetStateStatusDisplayTooltip() const; private: TAttribute<EGameFeaturePluginState> CurrentState; };` — A delegate that is invoked when widgets want to notify a user that they have been clicked. Intended for use by buttons and other button-like widgets.

### `Plugins/Runtime/GameFeatures/Source/GameFeaturesEditor/Public/GameFeaturePluginTemplate.h` (Public)


#### struct `FGameFeaturePluginTemplateDescription`  
`struct FGameFeaturePluginTemplateDescription : public FPluginTemplateDescription`  
_L14-38_
- inherits: `FPluginTemplateDescription`
- desc: Used to create custom templates for GameFeaturePlugins.
- L16 _public prototype_ `FGameFeaturePluginTemplateDescription(FText InName, FText InDescription, FString InOnDiskPath, FString InDefaultSubfolder, FString InDefaultPluginName , TSubclassOf<UGameFeatureData> GameFeatureDataClassOverride, FString GameFeatureDataNameOverride, EPluginEnabledByDefault InEnabledByDefault , FString InPostCreatePythonScriptPath, FString InPostCreatePythonScriptArguments);`
- L20 _public prototype_ `virtual bool ValidatePathForPlugin(const FString& ProposedAbsolutePluginPath, FText& OutErrorMessage) override;`
- L21 _public prototype_ `virtual void UpdatePathWhenTemplateSelected(FString& InOutPath) override;`
- L22 _public prototype_ `virtual void UpdatePathWhenTemplateUnselected(FString& InOutPath) override;`
- L24 _public prototype_ `virtual void UpdatePluginNameTextWhenTemplateSelected(FText& OutPluginNameText) override;`
- L25 _public prototype_ `virtual void UpdatePluginNameTextWhenTemplateUnselected(FText& OutPluginNameText) override;`
- L27 _public prototype_ `virtual void CustomizeDescriptorBeforeCreation(FPluginDescriptor& Descriptor) override;`
- L28 _public prototype_ `virtual void OnPluginCreated(TSharedPtr<IPlugin> NewPlugin) override;`
- L30 _public prototype_ `FString GetGameFeatureRoot() const;`
- L31 _public prototype_ `bool IsRootedInGameFeaturesRoot(const FString& InStr) const;`
- L33 _public member_ `FString DefaultSubfolder;`
- L34 _public member_ `FString DefaultPluginName;`
- L35 _public member_ `TSubclassOf<UGameFeatureData> GameFeatureDataClass;`
- L36 _public member_ `FString GameFeatureDataName;`
- L37 _public member_ `EPluginEnabledByDefault PluginEnabledByDefault = EPluginEnabledByDefault::Disabled;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEFEATURESEDITOR_API`
