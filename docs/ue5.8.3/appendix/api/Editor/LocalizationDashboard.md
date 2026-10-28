# Editor / LocalizationDashboard

- module root: `Source/Editor/LocalizationDashboard`
- headers: 12; symbols: 242
- symbol kinds: class=20, function=14, member=44, prototype=162, struct=2
- PrivateDependencyModuleNames: DesktopPlatform, EditorFramework, Engine, InputCore, InternationalizationSettings, LocalizationCommandletExecution, LocalizationService, MainFrame, SharedSettingsWidgets, Slate, SlateCore, SourceControl, ToolMenus, TranslationEditor, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, Localization, PropertyEditor

### `Source/Editor/LocalizationDashboard/Private/GatherTextDetailCustomizations.h` (Private)


#### class `FGatherTextSearchDirectoryStructCustomization`  
`class FGatherTextSearchDirectoryStructCustomization : public IStructCustomization`  
_L10-15_
- inherits: `IStructCustomization`
- L13 _public prototype_ `virtual void CustomizeStructHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IStructCustomizationUtils& StructCustomizationUtils) override;`
- L14 _public function_ `virtual void CustomizeStructChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IStructCustomizationUtils& StructCustomizationUtils) override`

#### class `FGatherTextIncludePathStructCustomization`  
`class FGatherTextIncludePathStructCustomization : public IStructCustomization`  
_L17-22_
- inherits: `IStructCustomization`
- L20 _public prototype_ `virtual void CustomizeStructHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IStructCustomizationUtils& StructCustomizationUtils) override;`
- L21 _public function_ `virtual void CustomizeStructChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IStructCustomizationUtils& StructCustomizationUtils) override`

#### class `FGatherTextExcludePathStructCustomization`  
`class FGatherTextExcludePathStructCustomization : public IStructCustomization`  
_L24-29_
- inherits: `IStructCustomization`
- L27 _public prototype_ `virtual void CustomizeStructHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IStructCustomizationUtils& StructCustomizationUtils) override;`
- L28 _public function_ `virtual void CustomizeStructChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IStructCustomizationUtils& StructCustomizationUtils) override`

#### class `FGatherTextFileExtensionStructCustomization`  
`class FGatherTextFileExtensionStructCustomization : public IStructCustomization`  
_L31-36_
- inherits: `IStructCustomization`
- L34 _public prototype_ `virtual void CustomizeStructHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IStructCustomizationUtils& StructCustomizationUtils) override;`
- L35 _public function_ `virtual void CustomizeStructChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IStructCustomizationUtils& StructCustomizationUtils) override`

#### class `FGatherTextFromTextFilesConfigurationStructCustomization`  
`class FGatherTextFromTextFilesConfigurationStructCustomization : public IStructCustomization`  
_L38-43_
- inherits: `IStructCustomization`
- L41 _public prototype_ `virtual void CustomizeStructHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IStructCustomizationUtils& StructCustomizationUtils) override;`
- L42 _public prototype_ `virtual void CustomizeStructChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IStructCustomizationUtils& StructCustomizationUtils) override;`

#### class `FGatherTextFromPackagesConfigurationStructCustomization`  
`class FGatherTextFromPackagesConfigurationStructCustomization : public IStructCustomization`  
_L45-50_
- inherits: `IStructCustomization`
- L48 _public prototype_ `virtual void CustomizeStructHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IStructCustomizationUtils& StructCustomizationUtils) override;`
- L49 _public prototype_ `virtual void CustomizeStructChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IStructCustomizationUtils& StructCustomizationUtils) override;`

#### class `FMetaDataTextKeyPatternStructCustomization`  
`class FMetaDataTextKeyPatternStructCustomization : public IStructCustomization`  
_L52-57_
- inherits: `IStructCustomization`
- L55 _public prototype_ `virtual void CustomizeStructHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IStructCustomizationUtils& StructCustomizationUtils) override;`
- L56 _public function_ `virtual void CustomizeStructChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IStructCustomizationUtils& StructCustomizationUtils) override`

#### class `FMetaDataKeyNameStructCustomization`  
`class FMetaDataKeyNameStructCustomization : public IStructCustomization`  
_L59-64_
- inherits: `IStructCustomization`
- L62 _public prototype_ `virtual void CustomizeStructHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IStructCustomizationUtils& StructCustomizationUtils) override;`
- L63 _public function_ `virtual void CustomizeStructChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IStructCustomizationUtils& StructCustomizationUtils) override`

#### class `FMetaDataKeyGatherSpecificationStructCustomization`  
`class FMetaDataKeyGatherSpecificationStructCustomization : public IStructCustomization`  
_L66-71_
- inherits: `IStructCustomization`
- L69 _public prototype_ `virtual void CustomizeStructHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IStructCustomizationUtils& StructCustomizationUtils) override;`
- L70 _public prototype_ `virtual void CustomizeStructChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IStructCustomizationUtils& StructCustomizationUtils) override;`

#### class `FGatherTextFromMetaDataConfigurationStructCustomization`  
`class FGatherTextFromMetaDataConfigurationStructCustomization : public IStructCustomization`  
_L73-78_
- inherits: `IStructCustomization`
- L76 _public prototype_ `virtual void CustomizeStructHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IStructCustomizationUtils& StructCustomizationUtils) override;`
- L77 _public prototype_ `virtual void CustomizeStructChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IStructCustomizationUtils& StructCustomizationUtils) override;`

### `Source/Editor/LocalizationDashboard/Private/LocalizationDashboard.h` (Private)


#### class `FLocalizationDashboard`  
`class FLocalizationDashboard`  
_L11-30_
- L14 _public prototype_ `static FLocalizationDashboard* Get();`
- L15 _public prototype_ `static void Initialize();`
- L16 _public prototype_ `static void Terminate();`
- L17 _public prototype_ `void Show();`
- L18 _public prototype_ `TWeakPtr<SDockTab> ShowTargetEditorTab(ULocalizationTarget* const LocalizationTarget);`
- L21 _private prototype_ `FLocalizationDashboard();`
- L22 _private prototype_ `~FLocalizationDashboard();`
- L23 _private prototype_ `void RegisterTabSpawner();`
- L24 _private prototype_ `void UnregisterTabSpawner();`
- L27 _private member_ `static const FName TabName;`
- L28 _private member_ `static FLocalizationDashboard* Instance;`
- L29 _private member_ `TSharedPtr<SLocalizationDashboard> LocalizationDashboardWidget;`

### `Source/Editor/LocalizationDashboard/Private/LocalizationDashboardSettings.h` (Private)


#### class `ULocalizationDashboardSettings`  
`class ULocalizationDashboardSettings : public UObject`  
_L12-15_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Currently just a dummy class used for detail customizations

### `Source/Editor/LocalizationDashboard/Private/LocalizationDashboardSettingsDetailCustomization.h` (Private)


#### struct `FLocalizationServiceProviderWrapper`  
`struct FLocalizationServiceProviderWrapper`  
_L17-23_
- L19 _public function_ `FLocalizationServiceProviderWrapper() : Provider(nullptr)`
- L20 _public function_ `FLocalizationServiceProviderWrapper(ILocalizationServiceProvider* const InProvider) : Provider(InProvider)`
- L22 _public member_ `ILocalizationServiceProvider* Provider;`

#### class `FLocalizationDashboardSettingsDetailCustomization`  
`class FLocalizationDashboardSettingsDetailCustomization : public IDetailCustomization`  
_L25-41_
- inherits: `IDetailCustomization`
- L28 _public prototype_ `FLocalizationDashboardSettingsDetailCustomization();`
- L29 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L32 _private prototype_ `FText GetCurrentServiceProviderDisplayName() const;`
- L33 _private prototype_ `TSharedRef<SWidget> ServiceProviderComboBox_OnGenerateWidget(TSharedPtr<FLocalizationServiceProviderWrapper> LSPWrapper) const;`
- L34 _private prototype_ `void ServiceProviderComboBox_OnSelectionChanged(TSharedPtr<FLocalizationServiceProviderWrapper> LSPWrapper, ESelectInfo::Type SelectInfo);`
- L37 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder;`
- L39 _private member_ `IDetailCategoryBuilder* ServiceProviderCategoryBuilder;`
- L40 _private member_ `TArray< TSharedPtr<FLocalizationServiceProviderWrapper> > Providers;`

### `Source/Editor/LocalizationDashboard/Private/LocalizationTargetDetailCustomization.h` (Private)


#### class `FLocalizationTargetDetailCustomization`  
`class FLocalizationTargetDetailCustomization : public IDetailCustomization`  
_L40-128_
- inherits: `IDetailCustomization`
- L43 _public prototype_ `FLocalizationTargetDetailCustomization();`
- L44 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L46 _public prototype_ `FLocalizationTargetSettings* GetTargetSettings() const;`
- L47 _public prototype_ `TSharedPtr<IPropertyHandle> GetTargetSettingsPropertyHandle() const;`
- L50 _private prototype_ `FText GetTargetName() const;`
- L51 _private prototype_ `bool IsTargetNameUnique(const FString& Name) const;`
- L52 _private prototype_ `void OnTargetNameChanged(const FText& NewText);`
- L53 _private prototype_ `void OnTargetNameCommitted(const FText& NewText, ETextCommit::Type Type);`
- L55 _private prototype_ `ELocalizationTargetLoadingPolicy GetLoadingPolicy() const;`
- L56 _private prototype_ `void SetLoadingPolicy(const ELocalizationTargetLoadingPolicy LoadingPolicy);`
- L57 _private prototype_ `void OnLoadingPolicySelectionChanged(TSharedPtr<ELocalizationTargetLoadingPolicy> LoadingPolicy, ESelectInfo::Type SelectInfo);`
- L58 _private prototype_ `TSharedRef<SWidget> GenerateWidgetForLoadingPolicy(TSharedPtr<ELocalizationTargetLoadingPolicy> LoadingPolicy);`
- L60 _private prototype_ `void RebuildTargetDependenciesBox();`
- L61 _private prototype_ `void RebuildTargetsList();`
- L62 _private prototype_ `TSharedRef<ITableRow> OnGenerateTargetRow(ULocalizationTarget* OtherLocalizationTarget, const TSharedRef<STableViewBase>& Table);`
- L63 _private prototype_ `void OnTargetDependencyCheckStateChanged(ULocalizationTarget* const OtherLocalizationTarget, const ECheckBoxState State);`
- L64 _private prototype_ `ECheckBoxState IsTargetDependencyChecked(ULocalizationTarget* const OtherLocalizationTarget) const;`
- L66 _private prototype_ `bool CanGatherText() const;`
- L67 _private prototype_ `void GatherText();`
- L69 _private prototype_ `bool CanImportTextAllCultures() const;`
- L70 _private prototype_ `void ImportTextAllCultures();`
- L72 _private prototype_ `bool CanExportTextAllCultures() const;`
- L73 _private prototype_ `void ExportTextAllCultures();`
- L75 _private prototype_ `bool CanImportDialogueScriptAllCultures() const;`
- L76 _private prototype_ `void ImportDialogueScriptAllCultures();`
- L78 _private prototype_ `bool CanExportDialogueScriptAllCultures() const;`
- L79 _private prototype_ `void ExportDialogueScriptAllCultures();`
- L81 _private prototype_ `bool CanImportDialogueAllCultures() const;`
- L82 _private prototype_ `void ImportDialogueAllCultures();`
- L84 _private prototype_ `bool CanCountWords() const;`
- L85 _private prototype_ `void CountWords();`
- L87 _private prototype_ `bool CanCompileTextAllCultures() const;`
- L88 _private prototype_ `void CompileTextAllCultures();`
- L90 _private prototype_ `void UpdateTargetFromReports();`
- L92 _private prototype_ `void BuildListedCulturesList();`
- L93 _private prototype_ `void RebuildListedCulturesList();`
- L94 _private prototype_ `TSharedRef<ITableRow> OnGenerateCultureRow(TSharedPtr<IPropertyHandle> CulturePropertyHandle, const TSharedRef<STableViewBase>& Table);`
- L96 _private prototype_ `bool IsCultureSelectableAsSupported(FCulturePtr Culture);`
- L97 _private prototype_ `void OnNewSupportedCultureSelected(FCulturePtr SelectedCulture, ESelectInfo::Type SelectInfo);`
- L100 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder;`
- L102 _private member_ `TWeakObjectPtr<ULocalizationTargetSet> TargetSet;`
- L103 _private member_ `TWeakObjectPtr<ULocalizationTarget> LocalizationTarget;`
- L105 _private member_ `TSharedPtr<IPropertyHandle> TargetSettingsPropertyHandle;`
- L107 _private member_ `TSharedPtr<SEditableTextBox> TargetNameEditableTextBox;`
- L109 _private member_ `TSharedPtr<SHorizontalBox> TargetDependenciesHorizontalBox;`
- L110 _private member_ `TArray< TSharedPtr<SWidget> > TargetDependenciesWidgets;`
- L111 _private member_ `TArray<ULocalizationTarget*> TargetDependenciesOptionsList;`
- L112 _private member_ `TSharedPtr< SListView<ULocalizationTarget*> > TargetDependenciesListView;`
- L114 _private member_ `TArray<FCulturePtr> AllCultures;`
- L116 _private member_ `TSharedPtr<IPropertyHandle> NativeCultureIndexPropertyHandle;`
- L117 _private member_ `TSharedPtr<IPropertyHandle> SupportedCulturesStatisticsPropertyHandle;`
- L118 _private member_ `FSimpleDelegate SupportedCulturesStatisticsPropertyHandle_OnNumElementsChanged;`
- L119 _private member_ `TSharedPtr< SListView< TSharedPtr<IPropertyHandle> > > SupportedCultureListView;`
- L120 _private member_ `TSharedPtr<SErrorText> NoSupportedCulturesErrorText;`
- L121 _private member_ `TSharedPtr<SComboButton> AddNewSupportedCultureComboButton;`
- L122 _private member_ `TSharedPtr<SCulturePicker> SupportedCulturePicker;`
- L123 _private member_ `TArray< TSharedPtr<IPropertyHandle> > ListedCultureStatisticProperties;`
- L126 _private member_ `int32 NewEntryIndexToBeInitialized;` — If set, the entry at the index specified needs to be initialized as soon as possible.
- L127 _private member_ `FCulturePtr SelectedNewCulture;`

### `Source/Editor/LocalizationDashboard/Private/LocalizationTargetSetDetailCustomization.h` (Private)


#### class `FLocalizationTargetSetDetailCustomization`  
`class FLocalizationTargetSetDetailCustomization : public IDetailCustomization`  
_L28-79_
- inherits: `IDetailCustomization`
- L31 _public prototype_ `FLocalizationTargetSetDetailCustomization();`
- L32 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L35 _private prototype_ `void BuildTargetsList();`
- L36 _private prototype_ `void RebuildTargetsList();`
- L38 _private prototype_ `bool CanGatherTextAllTargets() const;`
- L39 _private prototype_ `void GatherTextAllTargets();`
- L41 _private prototype_ `bool CanImportTextAllTargets() const;`
- L42 _private prototype_ `void ImportTextAllTargets();`
- L44 _private prototype_ `bool CanExportTextAllTargets() const;`
- L45 _private prototype_ `void ExportTextAllTargets();`
- L47 _private prototype_ `bool CanImportDialogueScriptAllTargets() const;`
- L48 _private prototype_ `void ImportDialogueScriptAllTargets();`
- L50 _private prototype_ `bool CanExportDialogueScriptAllTargets() const;`
- L51 _private prototype_ `void ExportDialogueScriptAllTargets();`
- L53 _private prototype_ `bool CanImportDialogueAllTargets() const;`
- L54 _private prototype_ `void ImportDialogueAllTargets();`
- L56 _private prototype_ `bool CanCountWordsForAllTargets() const;`
- L57 _private prototype_ `void CountWordsForAllTargets();`
- L59 _private prototype_ `bool CanCompileTextAllTargets() const;`
- L60 _private prototype_ `void CompileTextAllTargets();`
- L62 _private prototype_ `void UpdateTargetFromReports(ULocalizationTarget* const LocalizationTarget);`
- L64 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<IPropertyHandle> TargetObjectPropertyHandle, const TSharedRef<STableViewBase>& Table);`
- L65 _private prototype_ `FReply OnNewTargetButtonClicked();`
- L68 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder;`
- L70 _private member_ `TWeakObjectPtr<ULocalizationTargetSet> TargetSet;`
- L72 _private member_ `TSharedPtr<IPropertyHandle> TargetObjectsPropertyHandle;`
- L73 _private member_ `FSimpleDelegate TargetsArrayPropertyHandle_OnNumElementsChanged;`
- L74 _private member_ `TArray< TSharedPtr<IPropertyHandle> > TargetsList;`
- L75 _private member_ `TSharedPtr< SListView< TSharedPtr<IPropertyHandle> > > TargetsListView;`
- L78 _private member_ `int32 NewEntryIndexToBeInitialized;` — If set, the entry at the index specified needs to be initialized as soon as possible.

### `Source/Editor/LocalizationDashboard/Private/SLocalizationDashboardTargetRow.h` (Private)


#### class `SLocalizationDashboardTargetRow`  
`class SLocalizationDashboardTargetRow : public SMultiColumnTableRow< TSharedPtr<IPropertyHandle> >`  
_L24-76_
- inherits: `SMultiColumnTableRow<TSharedPtr<IPropertyHandle>>`
- L27 _public prototype_ `void Construct(const FTableRowArgs& InArgs, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedRef<IPropertyUtilities>& InPropertyUtilities, const TSharedRef<IPropertyHandle>& InTargetObjectPropertyHandle);`
- L28 _public prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override;`
- L31 _private prototype_ `ULocalizationTarget* GetTarget() const;`
- L32 _private prototype_ `FLocalizationTargetSettings* GetTargetSettings() const;`
- L34 _private prototype_ `FText GetTargetName() const;`
- L35 _private prototype_ `void OnNavigate();`
- L37 _private prototype_ `FText GetCulturesText() const;`
- L39 _private prototype_ `uint32 GetWordCount() const;`
- L40 _private prototype_ `uint32 GetNativeWordCount() const;`
- L41 _private prototype_ `FText GetWordCountText() const;`
- L43 _private prototype_ `void UpdateTargetFromReports();`
- L45 _private prototype_ `bool CanGatherText() const;`
- L46 _private prototype_ `FReply GatherText();`
- L48 _private prototype_ `bool CanImportText() const;`
- L49 _private prototype_ `FReply ImportText();`
- L51 _private prototype_ `bool CanExportText() const;`
- L52 _private prototype_ `FReply ExportText();`
- L54 _private prototype_ `bool CanImportDialogueScript() const;`
- L55 _private prototype_ `FReply ImportDialogueScript();`
- L57 _private prototype_ `bool CanExportDialogueScript() const;`
- L58 _private prototype_ `FReply ExportDialogueScript();`
- L60 _private prototype_ `bool CanImportDialogue() const;`
- L61 _private prototype_ `FReply ImportDialogue();`
- L63 _private prototype_ `bool CanCountWords() const;`
- L64 _private prototype_ `FReply CountWords();`
- L66 _private prototype_ `bool CanCompileText() const;`
- L67 _private prototype_ `FReply CompileText();`
- L69 _private prototype_ `FReply EnqueueDeletion();`
- L70 _private prototype_ `void Delete();`
- L73 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L74 _private member_ `TSharedPtr<IPropertyHandle> TargetObjectPropertyHandle;`
- L75 _private member_ `TWeakPtr<SDockTab> TargetEditorDockTab;`

### `Source/Editor/LocalizationDashboard/Private/SLocalizationTargetEditor.h` (Private)


#### class `SLocalizationTargetEditor`  
`class SLocalizationTargetEditor : public SCompoundWidget`  
_L15-28_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SLocalizationTargetEditor)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULocalizationTargetSet* const InProjectSettings, ULocalizationTarget* const InTarget, const FIsPropertyEditingEnabled& IsPropertyEditingEnabled);`
- L24 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& InEvent);`
- L27 _private member_ `TWeakObjectPtr<ULocalizationTarget> LocalizationTarget;` — Localization target being edited

### `Source/Editor/LocalizationDashboard/Private/SLocalizationTargetEditorCultureRow.h` (Private)


#### class `SLocalizationTargetEditorCultureRow`  
`class SLocalizationTargetEditorCultureRow : public SMultiColumnTableRow<FCulturePtr>`  
_L17-71_
- inherits: `SMultiColumnTableRow<FCulturePtr>`
- L20 _public prototype_ `void Construct(const FTableRowArgs& InArgs, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedRef<IPropertyUtilities>& InPropertyUtilities, const TSharedRef<IPropertyHandle>& InTargetSettingsPropertyHandle, const int32 InCultureIndex);`
- L21 _public prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override;`
- L24 _private prototype_ `ULocalizationTarget* GetTarget() const;`
- L25 _private prototype_ `FLocalizationTargetSettings* GetTargetSettings() const;`
- L26 _private prototype_ `FCultureStatistics* GetCultureStatistics() const;`
- L27 _private prototype_ `FCulturePtr GetCulture() const;`
- L28 _private prototype_ `bool IsNativeCultureForTarget() const;`
- L30 _private prototype_ `void OnNativeCultureCheckStateChanged(const ECheckBoxState CheckState);`
- L31 _private prototype_ `uint32 GetWordCount() const;`
- L32 _private prototype_ `uint32 GetNativeWordCount() const;`
- L34 _private prototype_ `FText GetCultureDisplayName() const;`
- L35 _private prototype_ `FText GetCultureName() const;`
- L37 _private prototype_ `FText GetWordCountText() const;`
- L38 _private prototype_ `TOptional<float> GetProgressPercentage() const;`
- L40 _private prototype_ `void UpdateTargetFromReports();`
- L42 _private prototype_ `bool CanEditText() const;`
- L43 _private prototype_ `FReply EditText();`
- L45 _private prototype_ `bool CanImportText() const;`
- L46 _private prototype_ `FReply ImportText();`
- L48 _private prototype_ `bool CanExportText() const;`
- L49 _private prototype_ `FReply ExportText();`
- L51 _private prototype_ `bool CanImportDialogueScript() const;`
- L52 _private prototype_ `FReply ImportDialogueScript();`
- L54 _private prototype_ `bool CanExportDialogueScript() const;`
- L55 _private prototype_ `FReply ExportDialogueScript();`
- L57 _private prototype_ `bool CanImportDialogue() const;`
- L58 _private prototype_ `FReply ImportDialogue();`
- L60 _private prototype_ `bool CanCompileText() const;`
- L61 _private prototype_ `FReply CompileText();`
- L63 _private prototype_ `bool CanDelete() const;`
- L64 _private prototype_ `FReply EnqueueDeletion();`
- L65 _private prototype_ `void Delete();`
- L68 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L69 _private member_ `TSharedPtr<IPropertyHandle> TargetSettingsPropertyHandle;`
- L70 _private member_ `int32 CultureIndex;`

### `Source/Editor/LocalizationDashboard/Private/SLocalizationTargetStatusButton.h` (Private)


#### class `SLocalizationTargetStatusButton`  
`class SLocalizationTargetStatusButton : public SButton`  
_L13-29_
- inherits: `SButton`
- L16 _public function_ `SLATE_BEGIN_ARGS( SLocalizationTargetStatusButton )`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULocalizationTarget& Target);`
- L22 _private prototype_ `const FSlateBrush* GetImageBrush() const;`
- L23 _private prototype_ `FSlateColor GetColorAndOpacity() const;`
- L24 _private prototype_ `FText GetToolTipText() const;`
- L25 _private prototype_ `FReply OnClicked();`
- L28 _private member_ `ULocalizationTarget* Target;`

### `Source/Editor/LocalizationDashboard/Private/TargetsTableEntry.h` (Private)


#### struct `FTargetsTableEntry`  
`struct FTargetsTableEntry`  
_L8-32_
- L10 _public member_ `TSharedPtr<IPropertyHandle> TargetObjectPropertyHandle;`
- L11 _public member_ `int32 CultureIndex;`
- L13 _public function_ `FTargetsTableEntry() : CultureIndex(INDEX_NONE)`
- L17 _public function_ `FTargetsTableEntry(const TSharedPtr<IPropertyHandle>& InTargetObjectPropertyHandle, const int32 InCultureIndex = INDEX_NONE) : TargetObjectPropertyHandle(InTargetObjectPropertyHandle) , CultureIndex(InCultureIndex)`
- L22 _public function_ `ULocalizationTarget* GetTarget()`

### `Source/Editor/LocalizationDashboard/Public/ILocalizationDashboardModule.h` (Public)


#### class `ILocalizationDashboardModule`  
`class ILocalizationDashboardModule : public IModuleInterface`  
_L14-33_
- inherits: `IModuleInterface`
- desc: Interface for localization dashboard module.
- L19 _public prototype_ `virtual ~ILocalizationDashboardModule() = default;` — Virtual destructor.
- L24 _public prototype_ `virtual void Show() = 0;` — Shows the localization dashboard UI.
- L26 _public prototype_ `virtual const TArray<ILocalizationServiceProvider*>& GetLocalizationServiceProviders() const = 0;`
- L27 _public prototype_ `virtual ILocalizationServiceProvider* GetCurrentLocalizationServiceProvider() const = 0;`
- L29 _public function_ `static ILocalizationDashboardModule& Get()`
