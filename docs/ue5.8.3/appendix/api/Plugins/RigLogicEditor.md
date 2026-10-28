# Plugins / RigLogicEditor

- module root: `Plugins/Animation/RigLogic/Source/RigLogicEditor`
- headers: 12; symbols: 116
- symbol kinds: class=11, delegate=1, function=17, macro=2, member=22, prototype=63
- PrivateDependencyModuleNames: AssetRegistry, SourceControl
- PrivateIncludePathModuleNames: Settings, UnrealEd
- PublicDependencyModuleNames: ApplicationCore, AssetDefinition, AssetTools, ContentBrowser, ContentBrowserData, ControlRig, Core, CoreUObject, DesktopPlatform, DetailCustomizations, DeveloperSettings, EditorFramework, EditorWidgets, Engine, InputCore, MainFrame, PropertyEditor, RigLogicLib, RigLogicModule, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Private/AssetDefinitions/AssetDefinition_DNAAsset.h` (Private)


#### class `UAssetDefinition_DNAAsset`  
`class UAssetDefinition_DNAAsset : public UAssetDefinitionDefault`  
_L10-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L20 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L21 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`
- L22 _public prototype_ `virtual EAssetCommandResult GetSourceFiles(const FAssetSourceFilesArgs& InArgs, TFunctionRef<bool(const FAssetSourceFilesResult& InSourceFile)> SourceFileFunc) const override;`
- L23 _public function_ `virtual bool CanImport() const override`

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Private/CoordinateSystemCustomization.h` (Private)


#### class `FCoordinateSystemCustomization`  
`class FCoordinateSystemCustomization : public IPropertyTypeCustomization`  
_L12-73_
- inherits: `IPropertyTypeCustomization`
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& Utils) override;`
- L18 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& Utils) override;`
- L22 _private prototype_ `void ReadFromProperty();` — Read the current committed values from the property handles
- L25 _private prototype_ `void RefreshComboSelections();` — Push the current staged values into the combo boxes' selected-item state
- L28 _private prototype_ `TSharedPtr<FString> FindOption(EDirection Dir) const;` — Look up the shared options pointer for a given direction (combo box compares by pointer)
- L31 _private prototype_ `bool HasPendingChanges() const;` — Is the staged state different from the committed property?
- L34 _private prototype_ `bool IsValid() const;` — Is the staged coordinate system valid? (3 distinct spatial dimensions, no indeterminate axes)
- L41 _private prototype_ `bool IsValueEditable() const;` — Whether the value widget should accept edits. Mirrors the host UPROPERTY's edit-const state (e.g. a VisibleAnywhere member is read-only) so the combo boxes and Apply button don't bypass it.
- L43 _private prototype_ `FReply OnApplyClicked();`
- L46 _private prototype_ `bool IsResetToDefaultVisible(TSharedPtr<IPropertyHandle> Handle) const;` — Reset-to-default override hooks
- L47 _private prototype_ `void OnResetToDefault(TSharedPtr<IPropertyHandle> Handle);`
- L49 _private prototype_ `TSharedRef<SWidget> GenerateDirectionWidget(TSharedPtr<FString> InItem);`
- L50 _private prototype_ `FText GetCurrentText(int32 AxisIndex) const;`
- L51 _private prototype_ `void OnAxisSelectionChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo, int32 AxisIndex);`
- L54 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — The struct-level property handle
- L57 _private member_ `TSharedPtr<IPropertyHandle> AxisHandles[3];` — Child handles for XAxis, YAxis, ZAxis
- L60 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> AxisCombos[3];` — Combo box widgets for XAxis, YAxis, ZAxis (kept so we can sync their selected item with StagedAxes)
- L63 _private member_ `EDirection StagedAxes[3] = { EDirection::Left, EDirection::Front, EDirection::Up };` — Staged values (local edits before Apply)
- L66 _private member_ `bool bIndeterminate[3] = { false, false, false };` — Per-axis indeterminate flag (set when GetValue returns MultipleValues across a multi-select)
- L69 _private member_ `TArray<TSharedPtr<FString>> DirectionOptions;` — Options for the combo boxes
- L72 _private member_ `FSlateFontInfo DetailFont;` — Cached detail panel font

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Private/DNAAutoConfig.h` (Private)


#### Free symbols / members of external scopes

- L8 _prototype_ `FDNAConfig AutoDetectDNAConfig(const FString& Path);`

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Private/RigLogicPerPlatformCustomization.h` (Private)


#### class `FPerPlatformEnumCustomization`  
`class FPerPlatformEnumCustomization : public IPropertyTypeCustomization`  
_L17-46_
- inherits: `IPropertyTypeCustomization`
- desc: Property customization for FPerPlatformInt-derived structs that represent enums. Shows enum dropdowns instead of numeric spinners in the per-platform widget.
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstanceCalculationType();`
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstanceFloatingPointType();`
- L23 _public prototype_ `FPerPlatformEnumCustomization(const UEnum* InEnum);`
- L26 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override` — IPropertyTypeCustomization
- L32 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L37 _private prototype_ `TSharedRef<SWidget> MakeEnumWidget(FName PlatformGroupName, TSharedRef<IPropertyHandle> StructPropertyHandle) const;`
- L40 _private prototype_ `TArray<FName> GetPlatformOverrideNames(TSharedRef<IPropertyHandle> StructPropertyHandle) const;`
- L41 _private prototype_ `bool AddPlatformOverride(FName PlatformGroupName, TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L42 _private prototype_ `bool RemovePlatformOverride(FName PlatformGroupName, TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L44 _private member_ `const UEnum* Enum;`
- L45 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtilities;`

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Public/Commandlets/ConvertLegacyDNAAssetsCommandlet.h` (Public)


#### class `UConvertLegacyDNAAssetsCommandlet`  
`class UConvertLegacyDNAAssetsCommandlet : public UCommandlet`  
_L26-36_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Editor commandlet that converts every USkeletalMesh carrying a legacy UDNAAsset (UAssetUserData) into a standalone UDNA asset, using the engine's existing UDNAImporter::ConvertFromLegacyAssetUserData (or, when -ReimportFromSource is requested, UDNAImporterLibrary::ImportDNAAutomated). Pair this with the stock -run=ResavePackages to bump the on-disk FDNAAssetCustomVersion across all DNA-bearing packages once conversion is done. Usage: UnrealEditor-Cmd.exe <Project>.uproject -run=ConvertLegacyDNAAssets \ [-PathFilter=/Game/MetaHumans] [-DryRun] [-NoSCC] \ [-ReimportFromSource] [-Verbose] [-help]
- L31 _public prototype_ `UConvertLegacyDNAAssetsCommandlet();`
- L34 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Public/DNAAssetImportFactory.h` (Public)


#### class `UDNAAssetImportFactory`  
`class UDNAAssetImportFactory: public UFactory, public FReimportHandler`  
_L18-47_
- reflection: `UCLASS(transient)`
- inherits: `UFactory,FReimportHandler`
- desc: Factory responsible for importing DNA file and attaching DNA data into SkeletalMesh Also extends ReimportHandler for importing DNA file with the same name as SkeletalMesh
- L27 _public member_ `TObjectPtr<class UDEPRECATED_DNAAssetImportUI> ImportUI_DEPRECATED;` — `UE_DEPRECATED(5.8, "Import UI is not needed since it adds unnecessary complexity and therefor it's deprecated")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Import UI is not needed since it adds unnecessary complexity and therefor it's deprecated"))`
- L31 _public member_ `TObjectPtr<class UDEPRECATED_DNAAssetImportUI> OriginalImportUI_DEPRECATED;` — `UE_DEPRECATED(5.8, "Import UI is not needed since it adds unnecessary complexity and therefor it's deprecated")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Import UI is not needed since it adds unnecessary complexity and therefor it's deprecated"))`
- L34 _public prototype_ `virtual void PostInitProperties() override;` — UObject properties
- L37 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L38 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L39 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L40 _public function_ `virtual void PostImportCleanUp()`
- L44 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;` — UFactory interface
- L45 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L46 _public function_ `virtual void CleanUp() override`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNAImportFactory, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDNAImportFactory, Log, All);`

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Public/DNAAssetImportUI.h` (Public)


#### class `UDEPRECATED_DNAAssetImportUI`  
`class UDEPRECATED_DNAAssetImportUI : public UObject, public IImportSettingsParser`  
_L17-47_
- reflection: `UCLASS(Deprecated, meta = (DeprecationMessage = "This class is not needed and will be removed."))`
- inherits: `UObject,IImportSettingsParser`
- L25 _public member_ `TObjectPtr<class USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (ImportType = "DNAAsset"))` — Skeletal mesh to use for imported DNA asset. When importing DNA, leaving this as "None" will generate new skeletal mesh.
- L28 _public function_ `void ResetToDefault()` — `UFUNCTION(BlueprintCallable, Category = Miscellaneous)`
- L31 _public function_ `virtual void ParseFromJson(TSharedRef<class FJsonObject> ImportSettingsJson) override` — IImportSettings Interface
- L34 _public member_ `bool bIsReimport;` — Whether this UI is construct for a reimport
- L37 _public member_ `UObject* ReimportMesh;` — When we are reimporting, we need the current object to preview skeletal mesh match issues.
- L46 _public member_ `FString FileName;` — `UPROPERTY(VisibleAnywhere, Transient, Category = DNAFileInformation, meta = (ImportType = "DNAAsset", DisplayName = "File Name"))` — The DNA file name

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Public/DNAAssetImportWindow.h` (Public)


#### class `SDNAAssetImportWindow`  
`class UE_DEPRECATED(5.8, "SDNAAssetImportWindow is deprecated and not needed anymore") SDNAAssetImportWindow : public SCompoundWidget`  
_L15-90_
- reflection: `UE_DEPRECATED(5.8, "SDNAAssetImportWindow is deprecated and not needed anymore")`
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SDNAAssetImportWindow) : _WidgetWindow() , _FullPath() , _MaxWindowHeight(0.0f) , _MaxWindowWidth(0.0f)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs);`
- L33 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L35 _public function_ `FReply OnImport()`
- L45 _public function_ `FReply OnImportAll()`
- L50 _public function_ `FReply OnCancel()`
- L60 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L70 _public function_ `bool ShouldImport() const`
- L75 _public function_ `SDNAAssetImportWindow() : bShouldImport(false)`
- L81 _private prototype_ `bool CanImport() const;`
- L82 _private prototype_ `FReply OnResetToDefaultClick() const;`
- L83 _private prototype_ `FText GetImportTypeDisplayText() const;`
- L86 _private member_ `TSharedPtr<class IDetailsView> DetailsView;`
- L87 _private member_ `TWeakPtr< SWindow > WidgetWindow;`
- L88 _private member_ `TSharedPtr< SButton > ImportButton;`
- L89 _private member_ `bool bShouldImport;`

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Public/DNAImportSettings.h` (Public)


#### class `UDNAImportSettings`  
`class UDNAImportSettings : public UDeveloperSettings`  
_L17-50_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, defaultconfig, meta=(DisplayName="RigLogic"))`
- inherits: `UDeveloperSettings`
- desc: Project-level settings for DNA asset import defaults. Allows teams to configure default MaxLOD and MinLOD per-platform values that will be applied to every newly imported DNA asset.
- L22 _public prototype_ `UDNAImportSettings();`
- L24 _public function_ `virtual FName GetContainerName() const override`
- L25 _public function_ `virtual FName GetCategoryName() const override`
- L26 _public function_ `virtual FName GetSectionName() const override`
- L37 _public member_ `FDNAConfig DefaultDNAConfig;` — `UPROPERTY(EditAnywhere, config, Category="Import Defaults")` — Default LOD configuration applied to every newly imported DNA asset. Set MaxLODPerPlatform / MinLODPerPlatform here to pre-fill those fields for each platform (e.g., Android, PS5, XSX) without touching existing assets. Reimporting existing assets will preserve their current LOD settings. Only affects new imports going forward.
- L49 _public member_ `FRigLogicConfiguration DefaultRigLogicConfiguration;` — `UPROPERTY(EditAnywhere, config, Category="Import Defaults")` — Default RigLogic configuration applied to every newly imported DNA asset. Controls the per-platform calculation backend (Scalar, SSE, AVX, NEON), floating point precision, multi-threaded ML compute, and which rig systems are loaded (joints, blend shapes, animated maps, etc.). Reimporting existing assets will preserve their current RigLogic settings. Only affects new imports going forward.

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Public/DNAImporter.h` (Public)


#### class `UDNAImporter`  
`class UDNAImporter : public UObject`  
_L13-50_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L22 _public prototype_ `UDNA* ImportDNAWithPrompt(TArray<USkeletalMesh*> SkeletalMeshes);` — Importing DNA asset with prompt for choosing a DNA file from disk
- L27 _public prototype_ `bool ImportDNAAutomated(const FString FileName, USkeletalMesh* SkeletalMesh, bool bReplaceExisting = true);` — Importing DNA asset automatically from sent file and SkeletalMesh provided
- L32 _public prototype_ `bool ConvertFromLegacyAssetUserData(USkeletalMesh* SkeletalMesh);` — Creating a DNA Asset from legacy DNA Asset User Data that should exist on Skeletal Mesh
- L37 _public prototype_ `void ReimportDNA(UDNA* ReimportDNA);` — Reimporting DNA asset provided
- L42 _public prototype_ `void ExportDNAWithPrompt(UDNA* DNAToExport);` — Export DNA asset to choosen folder
- L44 _public prototype_ `void ExportDNA(UDNA* DNAToExport, const FString FolderToExportTo);`
- L48 _private prototype_ `FString PromptForDNAImportFile();`
- L49 _private prototype_ `UDNA* ImportDNA(const FString Filename, USkeletalMesh* SkeletalMesh, bool bReplaceExisting = true);`

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Public/DNAImporterLibrary.h` (Public)


#### class `UDNAImporterLibrary`  
`class UDNAImporterLibrary : public UBlueprintFunctionLibrary`  
_L15-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L22 _private prototype_ `static void ImportSkeletalMeshDNA(const FString FileName, UObject* Mesh);` — `UE_DEPRECATED(5.8, "This function is deprecated, please use ImportAndAttachDNA.")` — `UFUNCTION(CallInEditor, BlueprintCallable, meta = (DisplayName = "Import Skeletal Mesh DNA File", Keywords = "DNA Importer Skeletal Mesh"), Category = "DNA")` — Import a DNA file onto the specified mesh asset.
- L26 _private prototype_ `static void ImportAndAttachDNA(const FString FileName, USkeletalMesh* Mesh, bool bReplaceExisting);` — `UFUNCTION(CallInEditor, BlueprintCallable, meta = (DisplayName = "Import Skeletal Mesh DNA File", Keywords = "DNA Importer Skeletal Mesh"), Category = "DNA")` — Import a DNA file onto the specified mesh asset.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGLOGICEDITOR_API`

### `Plugins/Animation/RigLogic/Source/RigLogicEditor/Public/RigLogicEditor.h` (Public)


#### class `FRigLogicEditor`  
`class FRigLogicEditor : public IModuleInterface`  
_L15-32_
- inherits: `IModuleInterface`
- L18 _public prototype_ `void StartupModule() override;`
- L19 _public prototype_ `void ShutdownModule() override;`
- L22 _private member_ `TArray<TSharedRef<class IAssetTypeActions>> AssetTypeActions;`
- L24 _private prototype_ `static TSharedRef<FExtender> OnExtendSkelMeshWithDNASelectionMenu(const TArray<FAssetData>& SelectedAssets);`
- L25 _private prototype_ `static void CreateDnaActionsSubMenu(FMenuBuilder& MenuBuilder, const TArray<FAssetData> SelectedAssets);`
- L26 _private prototype_ `static void GetDNAMenu(FMenuBuilder& MenuBuilder, const TArray<FAssetData> SelectedAssets);`
- L28 _private prototype_ `static void ExecuteDNAImport(UObject* Mesh);`
- L29 _private prototype_ `static void ExecuteDNAReimport(UObject* Mesh);`
- L31 _private prototype_ `static void GetAssetRegistryTagsForDNA(FAssetRegistryTagsContext Context);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGLOGICEDITOR_API`
