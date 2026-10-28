# Editor / UserAssetTagsEditor

- module root: `Source/Editor/UserAssetTagsEditor`
- headers: 28; symbols: 683
- symbol kinds: class=38, delegate=17, enum=3, enumerator=6, function=58, macro=21, member=185, namespace=11, prototype=311, struct=32, variable=1
- DynamicallyLoadedModuleNames: PropertyEditor
- PrivateDependencyModuleNames: AdvancedPreviewScene, ApplicationCore, AssetDefinition, AssetTools, ContentBrowser, ContentBrowserData, CoreUObject, DeveloperSettings, EditorConfig, Engine, InputCore, Kismet, Slate, SlateCore, ToolMenus, ToolWidgets
- PublicDependencyModuleNames: Core, DataHierarchyEditor, EditorWidgets, UnrealEd

### `Source/Editor/UserAssetTagsEditor/Private/AssetEditors/AssetEditor_TaggedAssetBrowserConfiguration.h` (Private)


#### class `UAssetEditor_TaggedAssetBrowserConfiguration`  
`class UAssetEditor_TaggedAssetBrowserConfiguration : public UAssetEditor`  
_L15-29_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UAssetEditor`
- L20 _public prototype_ `void SetObjectToEdit(UObject* InObject);`
- L23 _protected prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& OutObjectsToEdit) override;`
- L24 _protected prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L28 _private member_ `TObjectPtr<UObject> ObjectToEdit;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`

### `Source/Editor/UserAssetTagsEditor/Private/AssetEditors/TaggedAssetBrowserConfigurationToolkit.h` (Private)


#### class `UE::UserAssetTags::AssetEditor::FTaggedAssetBrowserConfigurationToolkit`  
`class FTaggedAssetBrowserConfigurationToolkit : public FBaseAssetToolkit`  
_L16-43_
- inherits: `FBaseAssetToolkit`
- L19 _public prototype_ `FTaggedAssetBrowserConfigurationToolkit(UAssetEditor* InOwningAssetBrowser);`
- L22 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L23 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L25 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L26 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L27 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L28 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L29 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L30 _public function_ `virtual bool IsPrimaryEditor() const override`
- L33 _private prototype_ `TSharedRef<class SDockTab> SpawnHierarchyEditorTab(const FSpawnTabArgs& SpawnTabArgs);`
- L35 _private member_ `TStrongObjectPtr<UTaggedAssetBrowserConfigurationHierarchyViewModel> HierarchyViewModel;`
- L37 _private prototype_ `static TSharedRef<SWidget> GenerateFilterRowContent(TSharedRef<FHierarchyElementViewModel> HierarchyElementViewModel);`
- L39 _private member_ `static const FName ToolkitFName;`
- L42 _private member_ `static const FName HierarchyEditorTabId;` — The tab ids for all the tabs used

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UserAssetTags` (scope `UE`)
- L14 _namespace_ `namespace AssetEditor` (scope `UE::UserAssetTags`)

### `Source/Editor/UserAssetTagsEditor/Private/Assets/AssetDefinition_TaggedAssetBrowserConfiguration.h` (Private)


#### class `UAssetDefinition_TaggedAssetBrowserConfiguration`  
`class UAssetDefinition_TaggedAssetBrowserConfiguration : public UAssetDefinitionDefault`  
_L15-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L19 _private prototype_ `virtual FText GetAssetDisplayName() const override;`
- L20 _private prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _private prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L22 _private prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L23 _private prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`

### `Source/Editor/UserAssetTagsEditor/Private/Commands/UserAssetTagCommands.h` (Private)


#### class `FUserAssetTagCommands`  
`class FUserAssetTagCommands : public TCommands<FUserAssetTagCommands>`  
_L15-27_
- inherits: `TCommands<FUserAssetTagCommands>`
- desc: User Asset Tag Commands
- L19 _public function_ `FUserAssetTagCommands() : TCommands<FUserAssetTagCommands>( TEXT("UserAssetTags"), NSLOCTEXT("Contexts", "UserAssetTags", "User Asset Tags"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L24 _public prototype_ `virtual void RegisterCommands() override;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ManageTags;`

### `Source/Editor/UserAssetTagsEditor/Private/Customizations/TaggedAssetBrowserConfigurationCustomization.h` (Private)


#### class `FTaggedAssetBrowserConfigurationCustomization`  
`class FTaggedAssetBrowserConfigurationCustomization : public IDetailCustomization`  
_L12-42_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `FTaggedAssetBrowserConfigurationCustomization() = default;`
- L18 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L24 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L27 _protected prototype_ `TArray<FString> GetProfileNameSuggestionsForExtension() const;`
- L28 _protected prototype_ `FName GetCurrentProfileName() const;`
- L30 _protected prototype_ `void OnProfileNameSelectionChanged(TSharedPtr<FString> Text, ESelectInfo::Type SelectInfo) const;`
- L31 _protected prototype_ `void OnProfileNameReset();`
- L33 _protected prototype_ `void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L36 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetaillLayoutBuilderWeak;`
- L37 _private member_ `TWeakObjectPtr<UTaggedAssetBrowserConfiguration> ConfigurationAsset;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> ProfileNameHandle;`
- L39 _private member_ `TSharedPtr<FString> InitialProfileName;`
- L40 _private member_ `TArray<TSharedPtr<FString>> AvailableProfileNames;`
- L41 _private member_ `FDelegateHandle OnObjectPropertyChangeDelegateHandle;`

### `Source/Editor/UserAssetTagsEditor/Private/Settings/ProjectUserAssetTagSettings.h` (Private)


#### class `UProjectUserAssetTagSettings`  
`class UProjectUserAssetTagSettings : public UDeveloperSettings`  
_L14-25_
- reflection: `UCLASS(Config=Editor, DefaultConfig, DisplayName="User Asset Tags", MinimalAPI)`
- inherits: `UDeveloperSettings`
- L20 _public member_ `TMap<FSoftClassPath, FPerTypeFavoriteUserAssetTags> UserAssetTagsPerType;` — `UPROPERTY(EditAnywhere, Config, Category="UserAssetTags")`
- L22 _public prototype_ `TSet<FName> GetProjectUserAssetTagsForClass(const UClass* Class) const;`
- L24 _public prototype_ `virtual FName GetCategoryName() const override;`

### `Source/Editor/UserAssetTagsEditor/Private/UserAssetTagProviders/UserAssetTagProvider_LocalAssetTypeFavorites.h` (Private)


#### class `UUserAssetTagProvider_LocalAssetTypeFavorites`  
`class UUserAssetTagProvider_LocalAssetTypeFavorites : public UUserAssetTagProvider`  
_L18-33_
- reflection: `UCLASS(MinimalAPI, DisplayName="Favorites by type")`
- inherits: `UUserAssetTagProvider`
- desc: The local favorites provider lets you add your own selection of favorite tags per asset type for quick reuse without affecting project settings.
- L23 _public prototype_ `UUserAssetTagProvider_LocalAssetTypeFavorites();`
- L25 _public prototype_ `virtual FText GetDisplayNameText(const UUserAssetTagEditorContext* Context) const override;`
- L26 _public prototype_ `virtual TSet<FName> GetSuggestedUserAssetTags(const UUserAssetTagEditorContext* Context) const override;`
- L29 _public prototype_ `virtual FResultWithUserFeedback IsValid(const UUserAssetTagEditorContext* Context) const override;` — Favorites are per asset type, so we disable this provider if we encounter multiple asset types.
- L31 _public prototype_ `virtual TSharedPtr<SWidget> AddAdditionalSuggestedWidgets(FName UserAssetTag, const UUserAssetTagEditorContext* Context) const override;`
- L32 _public prototype_ `virtual TSharedPtr<SWidget> AddAdditionalOwnedTagWidgets(FName UserAssetTag, const UUserAssetTagEditorContext* Context) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`

### `Source/Editor/UserAssetTagsEditor/Private/UserAssetTagProviders/UserAssetTagProvider_Project.h` (Private)


#### class `UUserAssetTagProvider_Project`  
`class UUserAssetTagProvider_Project : public UUserAssetTagProvider`  
_L16-27_
- reflection: `UCLASS(MinimalAPI, DisplayName="Project Tags by type")`
- inherits: `UUserAssetTagProvider`
- desc: A provider with the commonly used tags for this project, per asset type. You can assign tags per asset type in the project settings.
- L20 _private prototype_ `virtual FText GetDisplayNameText(const UUserAssetTagEditorContext* Context) const override;`
- L21 _private prototype_ `virtual TSet<FName> GetSuggestedUserAssetTags(const UUserAssetTagEditorContext* Context) const override;`
- L22 _private prototype_ `virtual FResultWithUserFeedback IsValid(const UUserAssetTagEditorContext* Context) const override;`
- L24 _private prototype_ `static void NavigateToProjectTags();`
- L26 _protected prototype_ `virtual void AddToolbarMenuEntries(class UToolMenu* DynamicMenu, const UUserAssetTagEditorContext* Context) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`

### `Source/Editor/UserAssetTagsEditor/Public/AssetFactories/TaggedAssetBrowserConfigurationFactory.h` (Public)


#### class `UTaggedAssetBrowserConfigurationFactory`  
`class UTaggedAssetBrowserConfigurationFactory : public UFactory`  
_L12-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L16 _private prototype_ `UTaggedAssetBrowserConfigurationFactory();`
- L18 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`

### `Source/Editor/UserAssetTagsEditor/Public/Assets/TaggedAssetBrowserConfiguration.h` (Public)


#### struct `FTaggedAssetBrowserConfigurationDataBase`  
`struct FTaggedAssetBrowserConfigurationDataBase`  
_L15-18_
- reflection: `USTRUCT()`

#### struct `FTaggedAssetBrowserConfigurationData_Standalone`  
`struct FTaggedAssetBrowserConfigurationData_Standalone : public FTaggedAssetBrowserConfigurationDataBase`  
_L22-40_
- reflection: `USTRUCT()`
- inherits: `FTaggedAssetBrowserConfigurationDataBase`
- desc: Data relevant for standalone assets.
- L27 _public member_ `bool bDisplayAllSection = true;` — `UPROPERTY(EditAnywhere, Category="Configuration")`
- L31 _public member_ `bool bMergeExtensionsPerSection = true;` — `UPROPERTY(EditAnywhere, Category = "Configuration")` — True implies we should merge extensions by section
- L35 _public member_ `TArray<TSubclassOf<UTaggedAssetBrowserFilterBase>> StandaloneFilterClasses;` — `UPROPERTY(EditAnywhere, Category="Configuration", meta=(ShowDisplayNames))` — The list of available hierarchy elements to add in the filter hierarchy for standalone configuration assets.
- L39 _public member_ `TArray<TSubclassOf<UTaggedAssetBrowserFilterBase>> ExtensionFilterClasses;` — `UPROPERTY(EditAnywhere, Category="Configuration", meta=(ShowDisplayNames))` — The list of available hierarchy elements to add in the filter hierarchy and section filters for extension assets, as defined by a standalone asset.

#### struct `FTaggedAssetBrowserConfigurationData_Extension`  
`struct FTaggedAssetBrowserConfigurationData_Extension : public FTaggedAssetBrowserConfigurationDataBase`  
_L44-47_
- reflection: `USTRUCT()`
- inherits: `FTaggedAssetBrowserConfigurationDataBase`
- desc: Data relevant for extension assets. Currently empty.

#### class `UTaggedAssetBrowserConfiguration`  
`class UTaggedAssetBrowserConfiguration : public UObject`  
_L51-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The actual configuration asset. Contains a hierarchy root that lets you add new elements and has drag & drop support via Data Hierarchy Editor.
- L56 _public prototype_ `UTaggedAssetBrowserConfiguration();`
- L60 _public member_ `FName ProfileName;` — `UPROPERTY(EditAnywhere, Category="Configuration", AssetRegistrySearchable)` — Used for saving filter state and various menus. Should be unique. Is also used for extension identification.
- L65 _public member_ `bool bIsExtension = false;` — `UPROPERTY(EditAnywhere, Category="Configuration", AssetRegistrySearchable)` — If this asset is used as extension, the matching standalone configuration asset will dictate what elements you can add. The ProfileName has to match the standalone asset.
- L68 _public member_ `FTaggedAssetBrowserConfigurationData_Standalone StandaloneData;` — `UPROPERTY(EditAnywhere, Category="Configuration", meta=(EditCondition="bIsExtension==false", EditConditionHides))`
- L71 _public member_ `FTaggedAssetBrowserConfigurationData_Extension ExtensionData;` — `UPROPERTY(EditAnywhere, Category="Configuration", meta=(EditCondition="bIsExtension==true", EditConditionHides))`
- L74 _public member_ `TObjectPtr<UTaggedAssetBrowserFilterRoot> FilterRoot;` — `UPROPERTY()`
- L77 _protected prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`

### `Source/Editor/UserAssetTagsEditor/Public/Config/LocalFavoriteUserAssetTagsConfig.h` (Public)


#### struct `FPerTypeFavoriteUserAssetTags`  
`struct FPerTypeFavoriteUserAssetTags`  
_L12-18_
- reflection: `USTRUCT()`
- L17 _public member_ `TSet<FName> FavoriteUserAssetTags;` — `UPROPERTY(EditAnywhere, Category="User Asset Tags")`

#### class `ULocalFavoriteUserAssetTagsConfig`  
`class ULocalFavoriteUserAssetTagsConfig : public UEditorConfigBase`  
_L23-45_
- reflection: `UCLASS(MinimalAPI, EditorConfig="FavoriteUserAssetTags")`
- inherits: `UEditorConfigBase`
- L28 _public prototype_ `static ULocalFavoriteUserAssetTagsConfig* Get();`
- L29 _public prototype_ `static void Shutdown();`
- L31 _public function_ `TMap<FSoftClassPath, FPerTypeFavoriteUserAssetTags>& GetFavoriteUserAssetTagsMutable()`
- L33 _public function_ `const TMap<FSoftClassPath, FPerTypeFavoriteUserAssetTags>& GetFavoriteUserAssetTags() const`
- L35 _public prototype_ `TSet<FName> GetFavoriteUserAssetTagsForClass(const UClass* Class);`
- L36 _public prototype_ `void ToggleFavoriteUserAssetTag(const UClass* Class, FName InUserAssetTag);`
- L39 _private member_ `TMap<FSoftClassPath, FPerTypeFavoriteUserAssetTags> FavoriteUserAssetTagsPerClass;` — `UPROPERTY(meta=(EditorConfig))`
- L42 _private member_ `int32 MaxRecentUserAssetTags = 10;` — `UPROPERTY(meta=(EditorConfig))`
- L44 _private member_ `static TStrongObjectPtr<ULocalFavoriteUserAssetTagsConfig> Instance;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`

### `Source/Editor/UserAssetTagsEditor/Public/Config/TaggedAssetBrowserConfig.h` (Public)


#### struct `FPerTaggedAssetBrowserSavedState`  
`struct FPerTaggedAssetBrowserSavedState`  
_L11-17_
- reflection: `USTRUCT()`
- L16 _public member_ `TArray<FName> PrimaryFilterSelection;` — `UPROPERTY()`

#### class `UTaggedAssetBrowserConfig`  
`class UTaggedAssetBrowserConfig : public UEditorConfigBase`  
_L20-46_
- reflection: `UCLASS(MinimalAPI, EditorConfig="TaggedAssetBrowser")`
- inherits: `UEditorConfigBase`
- L24 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropertyChanged, const FPropertyChangedEvent&);`
- L26 _public prototype_ `static UTaggedAssetBrowserConfig* Get();`
- L27 _public prototype_ `static void Shutdown();`
- L28 _public prototype_ `static bool HasInstance();`
- L30 _public function_ `FOnPropertyChanged& OnPropertyChanged()`
- L33 _public member_ `TMap<FName, FPerTaggedAssetBrowserSavedState> PerTaggedAssetBrowserSettings;` — `UPROPERTY(meta=(EditorConfig))`
- L36 _public member_ `bool bShowHiddenAssets = false;` — `UPROPERTY(meta=(EditorConfig))`
- L39 _public member_ `bool bShowDeprecatedAssets = false;` — `UPROPERTY(meta=(EditorConfig))`
- L41 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _private member_ `static TStrongObjectPtr<UTaggedAssetBrowserConfig> Instance;`
- L45 _private member_ `FOnPropertyChanged OnPropertyChangedDelegate;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropertyChanged, const FPropertyChangedEvent&);`

### `Source/Editor/UserAssetTagsEditor/Public/Config/UserAssetTagsEditorConfig.h` (Public)


#### struct `FPerUserAssetTagProviderViewOptions`  
`struct FPerUserAssetTagProviderViewOptions`  
_L14-24_
- reflection: `USTRUCT()`
- L19 _public member_ `bool bEnabled = true;` — `UPROPERTY()`
- L23 _public member_ `EUserAssetTagProviderMenuType MenuType = EUserAssetTagProviderMenuType::Section;` — `UPROPERTY()` — 0: Section; 1: SubMenu.

#### struct `FUserAssetTagProviderViewOptions`  
`struct FUserAssetTagProviderViewOptions`  
_L27-33_
- reflection: `USTRUCT()`
- L32 _public member_ `TMap<FName, FPerUserAssetTagProviderViewOptions> PerProviderViewOptions;` — `UPROPERTY()`

#### class `UUserAssetTagsEditorConfig`  
`class UUserAssetTagsEditorConfig : public UEditorConfigBase`  
_L38-62_
- reflection: `UCLASS(MinimalAPI, EditorConfig=UserAssetTags)`
- inherits: `UEditorConfigBase`
- L43 _public prototype_ `void ToggleSortByAlphabet();`
- L44 _public prototype_ `bool ShouldSortByAlphabet() const;`
- L46 _public prototype_ `bool IsProviderEnabled(const UClass* ProviderClass) const;`
- L47 _public prototype_ `void ToggleProviderEnabled(const UClass* ProviderClass);`
- L49 _public prototype_ `EUserAssetTagProviderMenuType GetProviderMenuType(const UClass* ProviderClass) const;`
- L50 _public prototype_ `void SetProviderMenuType(const UClass* ProviderClass, EUserAssetTagProviderMenuType InMenuType);`
- L52 _public prototype_ `static UUserAssetTagsEditorConfig* Get();`
- L53 _public prototype_ `static void Shutdown();`
- L56 _private member_ `bool bSortByAlphabet = false;` — `UPROPERTY(meta=(EditorConfig))`
- L59 _private member_ `FUserAssetTagProviderViewOptions ProviderViewOptions;` — `UPROPERTY(meta=(EditorConfig))`
- L61 _private member_ `static TStrongObjectPtr<UUserAssetTagsEditorConfig> Instance;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`

### `Source/Editor/UserAssetTagsEditor/Public/DataHierarchyEditor/TaggedAssetBrowserConfigurationHierarchyViewModel.h` (Public)


#### class `UTaggedAssetBrowserConfigurationHierarchyViewModel`  
`class UTaggedAssetBrowserConfigurationHierarchyViewModel : public UDataHierarchyViewModelBase`  
_L22-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataHierarchyViewModelBase`
- desc: The view model for Data Hierarchy Editor integration to author filter views for a Tagged Asset Browser.
- L27 _public prototype_ `void Initialize(UTaggedAssetBrowserConfiguration& InAsset);`
- L28 _public function_ `UTaggedAssetBrowserConfiguration* GetConfigurationAsset() const`
- L30 _public prototype_ `virtual UHierarchyRoot* GetHierarchyRoot() const override;`
- L31 _public prototype_ `virtual TSharedPtr<FHierarchyElementViewModel> CreateCustomViewModelForElement(UHierarchyElement* Element, TSharedPtr<FHierarchyElementViewModel> Parent) override;`
- L34 _public function_ `virtual bool SupportsSourcePanel() const override` — We don't need a sources panel or root as we only add new elements.
- L37 _public prototype_ `virtual TSubclassOf<UHierarchySection> GetSectionDataClass() const override;` — We specify our custom section class
- L40 _public function_ `virtual TSubclassOf<UHierarchyCategory> GetCategoryDataClass() const override` — We disables categories
- L43 _public prototype_ `virtual TArray<TSubclassOf<UHierarchyElement>> GetAdditionalTypesToAddInUi() const override;` — The types to add in the UI are specified here. We differentiate between standalone and extension elements.
- L46 _public function_ `virtual bool SelectRootInsteadOfNone() const override` — If we select nothing, we select the root. The custom root view model points at the asset for editing in the details panel.
- L48 _private prototype_ `TArray<TSubclassOf<UTaggedAssetBrowserFilterBase>> GetAdditionalTypesToAddInUi_Standalone() const;`
- L49 _private prototype_ `TArray<TSubclassOf<UTaggedAssetBrowserFilterBase>> GetAdditionalTypesToAddInUi_Extension() const;`
- L51 _private prototype_ `void EmptyCache(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L54 _protected prototype_ `virtual void InitializeInternal() override;`
- L55 _protected prototype_ `virtual void FinalizeInternal() override;`
- L57 _protected member_ `TWeakObjectPtr<UTaggedAssetBrowserConfiguration> ConfigurationAsset;`
- L58 _protected member_ `mutable TOptional<TArray<TSubclassOf<UHierarchyElement>>> AdditionalTypesCache;`

#### struct `UE::UserAssetTags::ViewModels::FFilterViewModel_Root`  
`struct FFilterViewModel_Root : public FHierarchyRootViewModel`  
_L63-73_
- inherits: `FHierarchyRootViewModel`
- L65 _public function_ `FFilterViewModel_Root(UHierarchyRoot* Root, TWeakObjectPtr<UDataHierarchyViewModelBase> ViewModel, bool bInIsForHierarchy) : FHierarchyRootViewModel(Root, ViewModel, bInIsForHierarchy)`
- L70 _private prototype_ `virtual FResultWithUserFeedback CanDropOnInternal(TSharedPtr<FHierarchyElementViewModel> DraggedElement, EItemDropZone ItemDropZone) override;` — Unlike the default implementation, our root can accept items even when another section is active.
- L72 _private prototype_ `virtual UObject* GetObjectForEditing() override;` — If the root gets selected, we select the actual asset instead since it houses properties we want to be able to edit.

#### struct `UE::UserAssetTags::ViewModels::FFilterViewModel_Section`  
`struct FFilterViewModel_Section : public FHierarchySectionViewModel`  
_L76-82_
- inherits: `FHierarchySectionViewModel`
- desc: We have a custom section view model that supports associating random elements to sections.
- L78 _public prototype_ `FFilterViewModel_Section(UTaggedAssetBrowserSection* InSection, TSharedRef<FHierarchyRootViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> ViewModel);`
- L80 _public prototype_ `virtual const FSlateBrush* GetSectionImageBrush() const override;`
- L81 _public prototype_ `virtual FResultWithUserFeedback CanContainInternal(TSubclassOf<UHierarchyElement> InHierarchyElementType) override;`

#### struct `UE::UserAssetTags::ViewModels::FFilterViewModelBase`  
`struct FFilterViewModelBase : public FHierarchyItemViewModel`  
_L85-88_
- inherits: `FHierarchyItemViewModel`
- desc: The base view model for all our filters.
- L87 _public prototype_ `FFilterViewModelBase(UTaggedAssetBrowserFilterBase* InFilter, TSharedRef<FHierarchyElementViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel);`

#### struct `UE::UserAssetTags::ViewModels::FFilterViewModel_All`  
`struct FFilterViewModel_All : public FFilterViewModelBase`  
_L90-95_
- inherits: `FFilterViewModelBase`
- L92 _public prototype_ `FFilterViewModel_All(UTaggedAssetBrowserFilter_All* InFilter, TSharedRef<FHierarchyElementViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel);`
- L94 _public function_ `virtual FResultWithUserFeedback CanHaveChildren() const override`

#### struct `UE::UserAssetTags::ViewModels::FFilterViewModel_UserAssetTag`  
`struct FFilterViewModel_UserAssetTag : public FFilterViewModelBase`  
_L97-105_
- inherits: `FFilterViewModelBase`
- L99 _public prototype_ `FFilterViewModel_UserAssetTag(UTaggedAssetBrowserFilter_UserAssetTag* InFilter, TSharedRef<FHierarchyElementViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel);`
- L101 _public function_ `virtual FResultWithUserFeedback CanHaveChildren() const override`
- L102 _public prototype_ `virtual FResultWithUserFeedback CanContainInternal(TSubclassOf<UHierarchyElement> InHierarchyElementType) override;`
- L103 _public function_ `virtual bool CanRenameInternal() override`
- L104 _public prototype_ `virtual void RenameInternal(FName NewName) override;`

#### struct `UE::UserAssetTags::ViewModels::FFilterViewModel_UserAssetTagCollection`  
`struct FFilterViewModel_UserAssetTagCollection : public FFilterViewModelBase`  
_L107-117_
- inherits: `FFilterViewModelBase`
- L109 _public prototype_ `FFilterViewModel_UserAssetTagCollection(UTaggedAssetBrowserFilter_UserAssetTagCollection* InFilter, TSharedRef<FHierarchyElementViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel);`
- L111 _public function_ `virtual FResultWithUserFeedback CanHaveChildren() const override`
- L112 _public prototype_ `virtual FResultWithUserFeedback CanContainInternal(TSubclassOf<UHierarchyElement> InHierarchyElementType) override;`
- L113 _public prototype_ `virtual FResultWithUserFeedback CanDropOnInternal(TSharedPtr<FHierarchyElementViewModel>, EItemDropZone ItemDropZone) override;`
- L115 _public function_ `virtual bool CanRenameInternal() override`
- L116 _public prototype_ `virtual void RenameInternal(FName NewName) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`
- L61 _namespace_ `namespace UE`
- L61 _namespace_ `namespace UserAssetTags` (scope `UE`)
- L61 _namespace_ `namespace ViewModels` (scope `UE::UserAssetTags`)

### `Source/Editor/UserAssetTagsEditor/Public/TaggedAssetBrowserEditorStyle.h` (Public)


#### class `FTaggedAssetBrowserEditorStyle`  
`class FTaggedAssetBrowserEditorStyle : public FSlateStyleSet`  
_L8-29_
- inherits: `FSlateStyleSet`
- desc: Manages the style which provides resources for niagara editor widgets.
- L11 _public prototype_ `static void Register();`
- L12 _public prototype_ `static void Unregister();`
- L13 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L19 _public prototype_ `static const FTaggedAssetBrowserEditorStyle& Get();` — @return The Slate style set for niagara editor widgets
- L21 _public prototype_ `static void ReinitializeStyle();`
- L24 _private prototype_ `FTaggedAssetBrowserEditorStyle();`
- L26 _private prototype_ `void InitStyle();`
- L28 _private member_ `static TSharedPtr<FTaggedAssetBrowserEditorStyle> TaggedAssetBrowserEditorStyle;`

### `Source/Editor/UserAssetTagsEditor/Public/TaggedAssetBrowserFilters/TaggedAssetBrowser_CommonFilters.h` (Public)


#### class `UTaggedAssetBrowserFilterRoot`  
`class UTaggedAssetBrowserFilterRoot : public UHierarchyRoot`  
_L16-19_
- reflection: `UCLASS()`
- inherits: `UHierarchyRoot`

#### struct `FTaggedAssetBrowserSectionIconData`  
`struct FTaggedAssetBrowserSectionIconData`  
_L22-41_
- reflection: `USTRUCT()`
- L28 _public member_ `bool bUseTextureForIcon = false;` — `UPROPERTY(EditAnywhere, Category="Icon")` — If true, will use a texture.
- L32 _public member_ `FName StyleName;` — `UPROPERTY(EditAnywhere, Category="Icon", meta=(EditCondition="bUseTextureForIcon==false"))` — The actual name of the icon to use within the styleset.
- L36 _public member_ `TObjectPtr<UTexture2D> Icon;` — `UPROPERTY(EditAnywhere, Category = "Icon", meta=(EditCondition="bUseTextureForIcon==true"))` — The icon to display for this section.
- L38 _public prototype_ `const FSlateBrush* GetImageBrush() const;`
- L40 _private member_ `mutable FSlateBrush TextureBrush;`

#### class `UTaggedAssetBrowserSection`  
`class UTaggedAssetBrowserSection : public UHierarchySection`  
_L45-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UHierarchySection`
- desc: The section class for the tagged asset browser. Can contain additional filters.
- L50 _public prototype_ `UTaggedAssetBrowserSection() = default;`
- L53 _public member_ `FTaggedAssetBrowserSectionIconData IconData;` — `UPROPERTY(EditAnywhere, Category = "Section", meta=(ShowOnlyInnerProperties))`
- L57 _public member_ `bool bAllowSectionMerge = true;` — `UPROPERTY(EditAnywhere, Category = "Section")` — True implies this section should support merging
- L61 _public member_ `TArray<TObjectPtr<UTaggedAssetBrowserFilterBase>> Filters;` — `UPROPERTY(EditAnywhere, Category = "Section", Instanced)` — A list of filters that can be specified optionally. This way, a section can display its associated elements, OR additionally filter assets by itself.

#### class `UTaggedAssetBrowserFilter_All`  
`class UTaggedAssetBrowserFilter_All : public UTaggedAssetBrowserFilterBase`  
_L66-69_
- reflection: `UCLASS(MinimalAPI, DisplayName="All")`
- inherits: `UTaggedAssetBrowserFilterBase`
- desc: Show all assets.

#### class `UTaggedAssetBrowserFilter_UserAssetTag`  
`class UTaggedAssetBrowserFilter_UserAssetTag : public UTaggedAssetBrowserFilterBase`  
_L73-89_
- reflection: `UCLASS(MinimalAPI, DisplayName="User Asset Tag")`
- inherits: `UTaggedAssetBrowserFilterBase`
- desc: A filter that returns assets that have the specified User Asset Tag. Nested User Asset Tag filters will be combined.
- L77 _public prototype_ `virtual FString ToString() const override;`
- L78 _public function_ `virtual TOptional<FString> GetInstanceIdentifier() const override`
- L79 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L80 _public prototype_ `virtual void ModifyARFilterInternal(FARFilter& Filter) const override;`
- L81 _public prototype_ `virtual bool ShouldFilterAssetInternal(const FAssetData& InAssetData) const override;`
- L83 _public prototype_ `void SetUserAssetTag(FName InUserAssetTag);`
- L84 _public prototype_ `bool DoesAssetHaveTag(const FAssetData& AssetCandidate) const;`
- L88 _protected member_ `FName UserAssetTag;` — `UPROPERTY(EditAnywhere, Category="Filter")`

#### class `UTaggedAssetBrowserFilter_UserAssetTagCollection`  
`class UTaggedAssetBrowserFilter_UserAssetTagCollection : public UTaggedAssetBrowserFilterBase`  
_L93-121_
- reflection: `UCLASS(MinimalAPI, DisplayName="User Asset Tag Collection")`
- inherits: `UTaggedAssetBrowserFilterBase`
- desc: A collection of multiple User Asset Tags. Will show all assets that own at least one of the contained tags.
- L99 _public prototype_ `virtual FString ToString() const override;`
- L100 _public function_ `virtual TOptional<FString> GetInstanceIdentifier() const override`
- L101 _public prototype_ `virtual FText GetTooltip() const override;`
- L102 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L103 _public prototype_ `virtual void CreateAdditionalWidgets(TSharedPtr<SHorizontalBox> ExtensionBox) override;`
- L105 _public prototype_ `virtual void ModifyARFilterInternal(FARFilter& Filter) const override;`
- L106 _public prototype_ `virtual bool ShouldFilterAssetInternal(const FAssetData& InAssetData) const override;`
- L108 _public prototype_ `void SetCollectionName(FName InName);`
- L112 _protected member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category="Filter")`
- L115 _protected member_ `FText Description;` — `UPROPERTY(EditAnywhere, Category="Filter", meta=(MultiLine))`
- L118 _private prototype_ `FText GetContainedChildrenNumberText() const;`
- L119 _private prototype_ `EVisibility GetContainedChildrenNumberTextVisibility() const;`
- L120 _private prototype_ `FText GetContainedChildrenNumberTooltip() const;`

#### class `UTaggedAssetBrowserFilter_Recent`  
`class UTaggedAssetBrowserFilter_Recent : public UTaggedAssetBrowserFilterBase`  
_L125-138_
- reflection: `UCLASS(MinimalAPI, DisplayName="Recent")`
- inherits: `UTaggedAssetBrowserFilterBase`
- desc: Filter for recently used assets.
- L131 _public prototype_ `virtual void InitializeInternal(const FTaggedAssetBrowserContext& InContext) override;`
- L132 _public prototype_ `virtual bool ShouldFilterAssetInternal(const FAssetData& InAssetData) const override;`
- L133 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L135 _public prototype_ `bool IsAssetRecent(const FAssetData& AssetCandidate) const;`
- L137 _public member_ `TAttribute<const FMainMRUFavoritesList*> ListAttribute;`

#### class `UTaggedAssetBrowserFilter_Directories`  
`class UTaggedAssetBrowserFilter_Directories : public UTaggedAssetBrowserFilterBase`  
_L142-160_
- reflection: `UCLASS(MinimalAPI, DisplayName="Directories")`
- inherits: `UTaggedAssetBrowserFilterBase`
- desc: Filter for assets based on directories.
- L148 _public prototype_ `virtual FString ToString() const override;`
- L149 _public function_ `virtual TOptional<FString> GetInstanceIdentifier() const override`
- L150 _public prototype_ `virtual void ModifyARFilterInternal(FARFilter& Filter) const override;`
- L151 _public prototype_ `virtual FText GetTooltip() const override;`
- L152 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L155 _public member_ `TArray<FDirectoryPath> DirectoryPaths;` — `UPROPERTY(EditAnywhere, Category="Filter", meta=(ContentDir))`
- L159 _public member_ `FName FilterName;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — Name for this directory filter, by default will use first directory name if not set

#### class `UTaggedAssetBrowserFilter_Class`  
`class UTaggedAssetBrowserFilter_Class : public UTaggedAssetBrowserFilterBase`  
_L164-187_
- reflection: `UCLASS(MinimalAPI, DisplayName="Classes")`
- inherits: `UTaggedAssetBrowserFilterBase`
- desc: Filter for assets based on class. By default will use first class as an icon.
- L170 _public prototype_ `virtual FString ToString() const override;`
- L171 _public function_ `virtual TOptional<FString> GetInstanceIdentifier() const override`
- L172 _public prototype_ `virtual FText GetTooltip() const override;`
- L173 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L175 _public prototype_ `virtual void ModifyARFilterInternal(FARFilter& Filter) const override;`
- L178 _public member_ `TArray<TObjectPtr<UClass>> Classes;` — `UPROPERTY(EditAnywhere, Category="Filter", meta=(AllowAbstract))`
- L182 _public member_ `bool bAllowChildClasses = true;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — True if we should allow child classes in our search.
- L186 _public member_ `FName FilterName;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — Name for this class filter, by default will use first class in list as name if not set

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`

### `Source/Editor/UserAssetTagsEditor/Public/TaggedAssetBrowserMenuFilters.h` (Public)


#### struct `FTaggedAssetBrowserContext`  
`struct FTaggedAssetBrowserContext`  
_L12-20_
- desc: A helper struct passed into filters for initialization, since some filters require contextual knowledge to filter correctly.
- L14 _public prototype_ `DECLARE_DELEGATE_RetVal(const class UTaggedAssetBrowserSection*, FOnGetActiveSection) DECLARE_DELEGATE_RetVal(TArray<const class UTaggedAssetBrowserFilterBase*>, FOnGetSelectedFilters) TWeakPtr<class STaggedAssetBrowser> TaggedAssetBrowser;`
- L18 _public member_ `FOnGetActiveSection OnGetActiveSectionDelegate;`
- L19 _public member_ `FOnGetSelectedFilters OnGetSelectedFilters;`

#### enum `ETaggedAssetBrowserFilterMergeBehavior`  
`enum class ETaggedAssetBrowserFilterMergeBehavior`  
_L24-28_
- reflection: `UENUM()`
- desc: How to resolve extension filter merging
- L26 _public enumerator_ `Append` — Add Filter at end
- L27 _public enumerator_ `Insert` — Insert before or after a filter by name

#### enum `ETaggedAssetBrowserFilterInsertBehavior`  
`enum class ETaggedAssetBrowserFilterInsertBehavior`  
_L32-36_
- reflection: `UENUM()`
- desc: How to insert a filter
- L34 _public enumerator_ `Before`
- L35 _public enumerator_ `After`

#### struct `FTaggedAssetBrowserFilterData_Extension`  
`struct FTaggedAssetBrowserFilterData_Extension`  
_L40-57_
- reflection: `USTRUCT()`
- desc: Data relevant for extension filters.
- L48 _public member_ `ETaggedAssetBrowserFilterMergeBehavior MergeBehavior = ETaggedAssetBrowserFilterMergeBehavior::Append;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — How this filter should be merged
- L52 _public member_ `ETaggedAssetBrowserFilterInsertBehavior InsertBehavior = ETaggedAssetBrowserFilterInsertBehavior::After;` — `UPROPERTY(EditAnywhere, Category = "Filter", meta = (EditCondition = "MergeBehavior==ETaggedAssetBrowserFilterMergeBehavior::Insert", EditConditionHides))` — How this filter should be inserted
- L56 _public member_ `FName InsertFilterName;` — `UPROPERTY(EditAnywhere, Category = "Filter", meta = (EditCondition = "MergeBehavior==ETaggedAssetBrowserFilterMergeBehavior::Insert", EditConditionHides))` — Name for filter this filter should be inserted relative to, assuming this is from / in an extension.

#### class `UTaggedAssetBrowserFilterBase`  
`class UTaggedAssetBrowserFilterBase : public UHierarchyItem`  
_L67-124_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew)`
- inherits: `UHierarchyItem`
- desc: A filter is the base element of the filter hierarchy built in the TaggedAssetBrowserConfiguration asset. It filters using two methods: - ModifyARFilter, which modifies the filter used to query the Asset Registry (override the Internal function for your implementation) - ShouldFilterAsset, which should return true if you want to remove an asset from display. This is for filtering beyond what the ARFilter allows, such as 'Recent' assets. While filters are generally part of the hierarchy, sections can also specify additional filters
- L75 _public member_ `FTaggedAssetBrowserFilterData_Extension ExtensionData;` — `UPROPERTY(EditAnywhere, Category = "Filter", meta = (EditCondition = "IsExtensionFilter", EditConditionHides))` — Data for this filter that is only needed when we are in an extension.
- L80 _public prototype_ `bool IsExtensionFilter() const;` — `UFUNCTION()` — Check outer for if we are a filter in an extension config
- L84 _public prototype_ `void Initialize(const FTaggedAssetBrowserContext& InContext);` — The filter has a chance to initialize itself with contextual data to actually work.
- L86 _public prototype_ `FName GetIdentifier() const;`
- L89 _public function_ `virtual FString ToString() const override` — The string to display for this filter.
- L91 _public function_ `virtual FText GetTooltip() const` — The tooltip to display for this filter.
- L93 _public prototype_ `virtual FSlateIcon GetIcon() const;` — The optional icon to display for this filter.
- L95 _public function_ `virtual void CreateAdditionalWidgets(TSharedPtr<SHorizontalBox> ExtensionBox)` — The optional widgets to display for this filter's row.
- L97 _public prototype_ `const FSlateBrush* GetIconBrush() const;`
- L100 _public prototype_ `void ModifyARFilter(FARFilter& Filter) const;` — How this filter should modify the AR filter, when selected.
- L102 _public prototype_ `bool ShouldFilterAsset(const FAssetData& InAssetData) const;` — An additional check for each asset that passes the AR filter.
- L105 _public prototype_ `virtual bool DoesFilterMatchTextQuery(const FText& Text);` — Used for search purposes. Override this to add your own implementation for your custom filter.
- L108 _public prototype_ `bool IsSelectedFilter() const;` — If this filter is selected in the Tagged Asset Browser.
- L111 _private function_ `virtual void InitializeInternal(const FTaggedAssetBrowserContext& InContext)` — Implementation of your own initialization when the Tagged Asset Browser starts using this filter.
- L114 _private function_ `virtual TOptional<FString> GetInstanceIdentifier() const` — Optional identifier if you are likely to have multiple filters of the same type. Will use only the class name as identifier if not implemented.
- L117 _private function_ `virtual void ModifyARFilterInternal(FARFilter& Filter) const` — Implementation of your own AR Filter modification.
- L119 _private function_ `virtual bool ShouldFilterAssetInternal(const FAssetData& InAssetData) const` — Implementation of your own ShouldFilterAsset function.
- L123 _protected member_ `TOptional<FTaggedAssetBrowserContext> ActiveContext;` — Will be valid during usage in a Tagged Asset Browser.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal(const class UTaggedAssetBrowserSection*, FOnGetActiveSection) DECLARE_DELEGATE_RetVal(TArray<const class UTaggedAssetBrowserFilterBase*>, FOnGetSelectedFilters) TWeakPtr<class STaggedAssetBrowser> TaggedAssetBrowser;`
- L15 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<const class UTaggedAssetBrowserFilterBase*>, FOnGetSelectedFilters) TWeakPtr<class STaggedAssetBrowser> TaggedAssetBrowser;`
- L126 _prototype_ `uint32 GetTypeHash(const UTaggedAssetBrowserFilterBase& Filter);`

### `Source/Editor/UserAssetTagsEditor/Public/UserAssetTagEditorMenuContexts.h` (Public)


#### class `UUserAssetTagEditorContext`  
`class UUserAssetTagEditorContext : public UObject`  
_L9-15_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L14 _public member_ `TWeakPtr<class SUserAssetTagsEditor> UserAssetTagsEditor;`

#### class `UTaggedAssetBrowserMenuContext`  
`class UTaggedAssetBrowserMenuContext : public UObject`  
_L18-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L23 _public member_ `TWeakPtr<class STaggedAssetBrowser> TaggedAssetBrowser;`

### `Source/Editor/UserAssetTagsEditor/Public/UserAssetTagEditorUtilities.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UserAssetTags` (scope `UE`)
- L23 _prototype_ `bool HasUserAssetTag(UObject* Object, FName UserAssetTag);` (scope `UE::UserAssetTags`)
- L24 _prototype_ `bool HasUserAssetTag(const FAssetData& InAssetData, FName UserAssetTag);` (scope `UE::UserAssetTags`)
- L26 _prototype_ `void AddUserAssetTag(UObject* Object, FName UserAssetTag);` (scope `UE::UserAssetTags`)
- L27 _prototype_ `bool RemoveUserAssetTag(UObject* Object, FName UserAssetTag);` (scope `UE::UserAssetTags`)
- L30 _prototype_ `TArray<FName> GetUserAssetTagsForObject(const UObject* InObject, bool bWithPrefix = false);` (scope `UE::UserAssetTags`) — Querying all user asset tags is relatively slow since we construct the list of tags by parsing prefixes.
- L31 _prototype_ `TArray<FName> GetUserAssetTagsForAssetData(const FAssetData& InAssetData);` (scope `UE::UserAssetTags`)
- L32 _prototype_ `TArray<FName> GetUserAssetTagsFromMetaData(const FMetaData& MetaData, bool bWithPrefix = false);` (scope `UE::UserAssetTags`)
- L38 _variable_ `inline FString UAT_METADATA_PREFIX = "UA` (scope `UE::UserAssetTags`) — The prefix used for User Asset Tags in both FMetaData and the Asset Registry. For display purposes we remove the prefix again.
- L41 _prototype_ `FName GetUATPrefixedTag(FName InUserAssetTag);` (scope `UE::UserAssetTags`) — Ensures the User Asset Tag is properly prefixed.
- L44 _prototype_ `FName GetUATWithoutPrefix(FName InUserAssetTag);` (scope `UE::UserAssetTags`) — Ensures the User Asset Tag is without prefix.
- L47 _prototype_ `void SummonUserAssetTagsEditor();` (scope `UE::UserAssetTags`) — Summons the user asset tags editor by invoking its tab.
- L50 _prototype_ `TArray<FAssetData> FindStandaloneConfigurationForExtension(const UTaggedAssetBrowserConfiguration* InExtensionAsset);` (scope `UE::UserAssetTags`) — Helper function to find the matching standalone configuration asset for a given extension asset.
- L53 _prototype_ `TArray<FName> FindAllStandaloneConfigurationAssetProfileNames();` (scope `UE::UserAssetTags`) — Helper function to find all profile names for standalone configuration assets.

### `Source/Editor/UserAssetTagsEditor/Public/UserAssetTagMenuHelpers.h` (Public)


#### struct `UE::UserAssetTags::Menus::FMultipleAssetsTagSingleTagInfo`  
`struct FMultipleAssetsTagSingleTagInfo`  
_L21-24_
- L23 _public member_ `TArray<FAssetData> AssetsOwningThisTag;`

#### struct `UE::UserAssetTags::Menus::FMultipleAssetsTagInfo`  
`struct FMultipleAssetsTagInfo`  
_L25-28_
- L27 _public member_ `TMap<FName, FMultipleAssetsTagSingleTagInfo> TagInfos;`

#### struct `UE::UserAssetTags::Menus::FMenuRowWidgetConfiguration`  
`struct FMenuRowWidgetConfiguration`  
_L38-43_
- L40 _public member_ `bool bAllowAdd = false;`
- L41 _public member_ `bool bAllowRemoval = false;`
- L42 _public member_ `TArray<FAssetData> ContextAssets;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UserAssetTags` (scope `UE`)
- L11 _namespace_ `namespace Menus` (scope `UE::UserAssetTags`)
- L13 _prototype_ `void RegisterMenusAndProfiles();` (scope `UE::UserAssetTags::Menus`)
- L16 _prototype_ `void RegisterDefaultTaggedAssetBrowserViewOptionsProfile();` (scope `UE::UserAssetTags::Menus`) — Registers a runtime profile for the AssetViewOptions under the name "TaggedAssetBrowser" to hide entries we don't need to display
- L19 _prototype_ `void ExtendContentBrowserAssetContextMenu();` (scope `UE::UserAssetTags::Menus`) — Extends the Content Browser context menu by adding the ManageTags UI action.
- L30 _prototype_ `FMultipleAssetsTagInfo GatherInfoAboutTags(const TArray<FAssetData>& Assets);` (scope `UE::UserAssetTags::Menus`)
- L31 _prototype_ `TOptional<FText> DetermineInfoText(const FMultipleAssetsTagSingleTagInfo& SingleTagInfo, const FMultipleAssetsTagInfo& TotalInfo);` (scope `UE::UserAssetTags::Menus`)
- L33 _prototype_ `void AddTagsToAssets(FName InUserAssetTag, const TArray<FAssetData>& InAssetData);` (scope `UE::UserAssetTags::Menus`)
- L34 _prototype_ `void RemoveTagsFromAssets(FName InUserAssetTag, const TArray<FAssetData>& InAssetData);` (scope `UE::UserAssetTags::Menus`)
- L36 _prototype_ `ECheckBoxState DetermineTagUIStatus(FName InUserAssetTag, const TArray<FAssetData>& InAssetData);` (scope `UE::UserAssetTags::Menus`)

### `Source/Editor/UserAssetTagsEditor/Public/UserAssetTagProvider.h` (Public)


#### enum `EUserAssetTagProviderMenuType`  
`enum class EUserAssetTagProviderMenuType`  
_L16-20_
- reflection: `UENUM()`
- L18 _public enumerator_ `Section`
- L19 _public enumerator_ `SubMenu`

#### class `UUserAssetTagProvider`  
`class UUserAssetTagProvider : public UObject`  
_L29-86_
- reflection: `UCLASS(MinimalAPI, Transient, Abstract)`
- inherits: `UObject`
- desc: To add your own source of tags, inherit from this. Specify a Display Name for UI purposes. Suggested Tags will get displayed in the Tag Editor. A Tag Provider can override functions to add custom UI elements to the Tag Editor that help with managing tags. E.g.: A 'Favorites' tag provider can add a 'favorite/unfavorite' toggle to individual tag rows.
- L61 _public prototype_ `virtual FText GetDisplayNameText(const UUserAssetTagEditorContext* Context) const;` — By default we return the class display name text.
- L63 _public prototype_ `virtual FText GetToolTipText(const UUserAssetTagEditorContext* Context) const;` — By default we return the class tooltip text.
- L66 _public function_ `virtual TSet<FName> GetSuggestedUserAssetTags(const UUserAssetTagEditorContext* Context) const PURE_VIRTUAL(UUserAssetTagProvider::GetSuggestedUserAssetTags, return {}; ) virtual bool IsEnabledByDefault() const` — Returns a list of suggested user asset tags.
- L72 _public function_ `virtual FResultWithUserFeedback IsValid(const UUserAssetTagEditorContext* Context) const` — If a provider is only valid for certain assets depending on some conditions, check for it here. If invalid, it can't be displayed.
- L76 _public function_ `virtual EUserAssetTagProviderMenuType GetMenuTypeByDefault() const` — The menu type, if enabled and valid, how this provider should be presented by default. The type can still be changed in the view options. If it's expected to show a large amount of tags, consider returning menu instead of section.
- L79 _public function_ `virtual TSharedPtr<SWidget> AddAdditionalSuggestedWidgets(FName UserAssetTag, const UUserAssetTagEditorContext* Context) const` — Lets you add additional widgets to the row containing a suggested tag in the User Asset Tag Editor
- L82 _public function_ `virtual TSharedPtr<SWidget> AddAdditionalOwnedTagWidgets(FName UserAssetTag, const UUserAssetTagEditorContext* Context) const` — Lets you add additional widgets to the row containing an owned tag in the User Asset Tag Editor
- L85 _public function_ `virtual void AddToolbarMenuEntries(class UToolMenu* DynamicMenu, const UUserAssetTagEditorContext* Context) const` — Lets you add additional

#### struct `UUserAssetTagProvider::FResultWithUserFeedback`  
`struct FResultWithUserFeedback`  
_L34-51_
- L36 _public function_ `FResultWithUserFeedback(bool bInCanPerform) : bResult(bInCanPerform)`
- L38 _public member_ `bool bResult = false;`
- L40 _public member_ `TOptional<FText> UserFeedback;` — A message that can be used for user feedback.
- L42 _public function_ `bool operator==(const bool& bOther) const`
- L47 _public function_ `bool operator!=(const bool& bOther) const`

#### struct `UUserAssetTagProvider::FSuggestedUserAssetTags`  
`struct FSuggestedUserAssetTags`  
_L53-58_
- L56 _public member_ `bool bUseSubMenu = false;` — If true, will contract to a submenu. Useful if
- L57 _public member_ `TSet<FName> UserAssetTags;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`

### `Source/Editor/UserAssetTagsEditor/Public/UserAssetTagsEditorModule.h` (Public)


#### class `FUserAssetTagsEditorModule`  
`class FUserAssetTagsEditorModule : public IModuleInterface`  
_L19-55_
- inherits: `IModuleInterface`
- L22 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedPtr<FHierarchyElementViewModel>, FOnGetViewModelFactory, UHierarchyElement* Element, TSharedPtr<FHierarchyElementViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InViewModel);`
- L24 _public prototype_ `FUserAssetTagsEditorModule();`
- L27 _public prototype_ `static FUserAssetTagsEditorModule& Get();`
- L29 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L33 _public prototype_ `void RegisterConfigurationHierarchyElementViewModel(TSubclassOf<UHierarchyElement> FilterType, FOnGetViewModelFactory InFactory);` — To register a custom view model for display in the Tagged Asset Browser.
- L34 _public prototype_ `void UnregisterConfigurationHierarchyElementViewModel(TSubclassOf<UHierarchyElement> FilterType);`
- L35 _public function_ `const TMap<TSubclassOf<UHierarchyElement>, FOnGetViewModelFactory>& GetConfigurationHierarchyViewModelFactories() const`
- L37 _public member_ `static FName ManageTagsTabId;`
- L39 _private prototype_ `void RegisterDefaultConfigurationHierarchyElementViewModels();`
- L40 _private prototype_ `void RegisterDetailsCustomizations();`
- L43 _private prototype_ `void OnRegisterCommandList(FName ContextName, TSharedRef<FUICommandList> CommandList);` — We extend the Content Browser command list so that the shortcut works.
- L45 _private prototype_ `static TSharedRef<SDockTab> SpawnUserAssetTagsEditorNomadTab(const FSpawnTabArgs& SpawnTabArgs);`
- L47 _private prototype_ `static void GetAssetRegistryTagsFromUserAssetTags(FAssetRegistryTagsContext AssetRegistryTagsContext);`
- L48 _private prototype_ `static void TransferUserAssetTagsFromOldPackageToNewPackage(const FMetaData& OldMetaData, FMetaData& NewMetaData, const UPackage* OldPackage, UPackage* NewPackage);`
- L51 _private member_ `TMap<TSubclassOf<UHierarchyElement>, FOnGetViewModelFactory> ConfigurationHierarchyViewModelFactories;`
- L52 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L53 _private member_ `FDelegateHandle GetAssetRegistryTagsFromUserAssetTagsDelegateHandle;`
- L54 _private member_ `FDelegateHandle TransferUserAssetTagsFromOldPackageToNewPackageDelegateHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUserAssetTags, Log, All);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedPtr<FHierarchyElementViewModel>, FOnGetViewModelFactory, UHierarchyElement* Element, TSharedPtr<FHierarchyElementViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InViewModel);`

### `Source/Editor/UserAssetTagsEditor/Public/Widgets/STaggedAssetBrowser.h` (Public)


#### struct `FTaggedAssetBrowserCustomTabInfo`  
`struct FTaggedAssetBrowserCustomTabInfo`  
_L27-42_
- desc: You can provide custom tabs to be displayed in the right column. Useful if you want to add custom content.
- L29 _public function_ `FTaggedAssetBrowserCustomTabInfo()`
- L32 _public member_ `FText Title;` — The title displayed in the browser.
- L35 _public member_ `const FSlateBrush* Icon = nullptr;` — The icon displayed next to the title. Optional.
- L38 _public member_ `FOnGetContent OnGetTabContent;` — The content of the tab to be displayed.
- L41 _public member_ `FOnAssetSelected OnAssetSelected;` — Will be called when an asset gets selected so the custom tab content can react accordingly.

#### struct `FDefaultDetailsTabConfiguration`  
`struct FDefaultDetailsTabConfiguration`  
_L44-51_
- L46 _public function_ `FDefaultDetailsTabConfiguration()`
- L48 _public member_ `bool bUseDefaultDetailsTab = true;`
- L49 _public member_ `TOptional<FText> EmptySelectionMessage;`
- L50 _public member_ `FOnGenerateAssetWidget OnGenerateAssetThumbnailOverrideWidgetDelegate;`

#### class `STaggedAssetBrowser`  
`class STaggedAssetBrowser : public SCompoundWidget`  
_L53-317_
- inherits: `SCompoundWidget`
- L70 _public function_ `SLATE_BEGIN_ARGS(STaggedAssetBrowser) : _RecentAndFavoritesList(GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->GetRecentlyOpenedAssets()) , _AssetSelectionMode(ESelectionMode::Single)`
- L76 _public prototype_ `SLATE_ARGUMENT(TArray<UClass*>, AvailableClasses) SLATE_ARGUMENT(FDefaultDetailsTabConfiguration, DefaultDetailsTabConfiguration) SLATE_ARGUMENT(TArray<FTaggedAssetBrowserCustomTabInfo>, CustomTabInfos) SLATE_ARGUMENT(FInterfaceOverrideProfiles, InterfaceOverrideProfiles) SLATE_ATTRIBUTE(const FMainMRUFavoritesList*, RecentAndFavoritesList) SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle) SLATE_ARGUMENT(TArray<FAssetData>, AdditionalReferencingAssets) SLATE_EVENT(FOnGetExtraFrontendFilters, OnGetExtraFrontendFilters) SLATE_EVENT(FOnExtendAddFilterMenu, OnExtendAddFilterMenu) SLATE_EVENT(FOnShouldFilterAsset, OnAdditionalShouldFilterAsset) SLATE_EVENT(FOnOverrideAssetPickerConfig, OnOverrideAssetPickerConfig) SLATE_EVENT(FOnGenerateAssetWidget, OnGenerateAssetTooltipWidget) SLATE_EVENT(FOnIsAssetValidForCustomToolTip, OnIsAssetValidForCustomToolTip) /** Determines the asset selection mode;` — The asset types to display.
- L133 _public prototype_ `STaggedAssetBrowser();`
- L136 _public prototype_ `void RefreshBackendFilter() const;`
- L138 _public prototype_ `TArray<FAssetData> GetSelectedAssets() const;`
- L140 _public prototype_ `TArray<UClass*> GetDisplayedAssetTypes() const;`
- L142 _public prototype_ `TAttribute<const FMainMRUFavoritesList*> GetFavoritesListAttribute() const;`
- L145 _public prototype_ `const UTaggedAssetBrowserSection* GetActiveSection() const;` — Returns the currently active section, or nullptr if no section is active.
- L148 _public prototype_ `TSharedPtr<SAssetPicker> GetAssetPicker() const;` — Returns the asset picker widget inside this browser, if it exists
- L151 _public prototype_ `TArray<const UTaggedAssetBrowserFilterBase*> GetSelectedPrimaryFilters() const;` — Returns the currently selected primary filter items.
- L154 _public prototype_ `TArray<const UTaggedAssetBrowserFilterBase*> GetAllPrimaryFilters() const;` — Returns all primary filter items in the current section, regardless of selection.
- L157 _private prototype_ `void InitializeValues();`
- L159 _private prototype_ `void RefreshPrimaryFilterRootItems(bool bRefreshWidget = true);`
- L161 _private prototype_ `void ApplyFilterExtensions();`
- L163 _private prototype_ `void InitAssetContextMenu();`
- L164 _private prototype_ `void CheckValidSetup() const;`
- L167 _private prototype_ `FARFilter CreateCurrentBackendFilter() const;` — This function should take into account all the different widgets states that could affect the FARFilter.
- L169 _private prototype_ `bool ShouldFilterAsset(const FAssetData& AssetData) const;`
- L170 _private prototype_ `bool NeedsCustomTabArea() const;`
- L172 _private prototype_ `void PopulateSectionsSlot();`
- L173 _private prototype_ `void PopulatePrimaryFiltersSlot();`
- L174 _private prototype_ `void PopulateAssetBrowserSplitterSlot();`
- L175 _private prototype_ `void PopulateAssetBrowserContentSlot();`
- L176 _private prototype_ `void PopulateCustomTabsSlot();`
- L178 _private prototype_ `void OnPrimaryFiltersSlotResized(float InSize);`
- L179 _private prototype_ `float OnGetPrimaryFiltersSlotMinSize() const;`
- L180 _private prototype_ `float OnGetPrimaryFiltersSlotSizeValue() const;`
- L183 _private prototype_ `void InitializeFilters();` — We initialize the duplicated filters contained in the filter root of the asset so that the filters have context available.
- L187 _private prototype_ `void OnFilterChanged() const;` — This has to be called whenever any kind of filtering changes and refreshes the actual asset view
- L212 _private prototype_ `void OnFilterSearchTextChanged(const FText& Text);` — Search functionality
- L213 _private prototype_ `void OnSearchButtonClicked(SSearchBox::SearchDirection SearchDirection);`
- L214 _private prototype_ `void OnFilterSearchTextCommitted(const FText& Text, ETextCommit::Type Arg);`
- L215 _private prototype_ `TOptional<SSearchBox::FSearchResultData> GetSearchResultData() const;`
- L216 _private prototype_ `void GenerateSearchItems(TWeakObjectPtr<UHierarchyElement> Root, TArray<TWeakObjectPtr<UHierarchyElement>> ParentChain, TArray<FFilterPath>& OutSearchItems) const;`
- L217 _private prototype_ `void ExpandPrimaryFilterSearchResults();`
- L218 _private prototype_ `void SelectNextPrimaryFilterSearchResult();`
- L219 _private prototype_ `void SelectPreviousPrimaryFilterSearchResult();`
- L222 _private prototype_ `void OnSectionSelected(const UTaggedAssetBrowserSection* InTaggedAssetBrowserSection);` — Sections functionality
- L224 _private prototype_ `void OnGetChildFiltersForFilter(TObjectPtr<UHierarchyElement> PrimaryFilter, TArray<TObjectPtr<UHierarchyElement>>& OutChildren) const;`
- L225 _private prototype_ `bool OnCompareFiltersForEquality(const UTaggedAssetBrowserFilterBase& PrimaryFilterA, const UTaggedAssetBrowserFilterBase& PrimaryFilterB) const;`
- L227 _private prototype_ `TSharedRef<ITableRow> GenerateWidgetRowForPrimaryFilter(TObjectPtr<UHierarchyElement> PrimaryFilter, const TSharedRef<STableViewBase>& OwningTable) const;`
- L229 _private prototype_ `void OnAssetSelected(const FAssetData& AssetData);`
- L230 _private prototype_ `void OnAssetsActivated(const TArray<FAssetData>& AssetData, EAssetTypeActivationMethod::Type) const;`
- L231 _private prototype_ `TSharedPtr<SWidget> OnGetAssetContextMenu(const TArray<FAssetData>& AssetData) const;`
- L232 _private prototype_ `TSharedRef<SToolTip> OnGetCustomAssetTooltip(FAssetData& AssetData);`
- L233 _private prototype_ `void OnPrimaryFilterSelected(TObjectPtr<UHierarchyElement> Filter, ESelectInfo::Type Arg);`
- L235 _private prototype_ `TArray<TSharedRef<FFrontendFilter>> OnGetExtraFrontendFilters() const;`
- L237 _private prototype_ `void OnAssetBrowserConfigPropertyChanged(const FPropertyChangedEvent& PropertyChangedEvent);`
- L239 _private prototype_ `void SaveSettings() const;`
- L240 _private prototype_ `void LoadSettings();`
- L242 _private prototype_ `TArray<UTaggedAssetBrowserConfiguration*> GetExtensionAssets() const;`
- L244 _private prototype_ `FName GetAssetContextMenuName() const;`
- L246 _private member_ `TWeakObjectPtr<const UTaggedAssetBrowserConfiguration> Configuration;`
- L248 _private member_ `TArray<UClass*> AvailableClasses;`
- L249 _private member_ `TStrongObjectPtr<UTaggedAssetBrowserFilterRoot> FilterHierarchyRoot;`
- L250 _private member_ `FDefaultDetailsTabConfiguration DefaultDetailsTabConfiguration;`
- L251 _private member_ `TArray<FTaggedAssetBrowserCustomTabInfo> CustomTabInfos;`
- L252 _private member_ `TAttribute<const FMainMRUFavoritesList*> RecentAndFavoritesList;`
- L253 _private member_ `TOptional<FName> TaggedBrowserProfileName;`
- L254 _private member_ `FInterfaceOverrideProfiles InterfaceOverrideProfiles;`
- L255 _private member_ `FOnAssetSelected OnAssetSelectedDelegate;`
- L256 _private member_ `FOnGenerateAssetWidget OnGenerateAssetTooltipWidgetDelegate;`
- L257 _private member_ `FOnIsAssetValidForCustomToolTip OnIsAssetValidForCustomToolTipDelegate;`
- L258 _private member_ `FOnAssetsActivated OnAssetsActivatedDelegate;`
- L259 _private member_ `FOnGetExtraFrontendFilters OnGetExtraFrontendFiltersDelegate;`
- L260 _private member_ `FOnExtendAddFilterMenu OnExtendAddFilterMenuDelegate;`
- L261 _private member_ `FOnShouldFilterAsset OnAdditionalShouldFilterAssetDelegate;`
- L262 _private member_ `FOnOverrideAssetPickerConfig OnOverrideAssetPickerConfigDelegate;`
- L263 _private member_ `FOnActiveSectionChanged OnActiveSectionChangedDelegate;`
- L264 _private member_ `FOnPrimaryFilterSelectionChanged OnPrimaryFilterSelectionChangedDelegate;`
- L265 _private member_ `ESelectionMode::Type AssetSelectionMode = ESelectionMode::Single;`
- L266 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L267 _private member_ `TArray<FAssetData> AdditionalReferencingAssets;`
- L269 _private member_ `TArray<FFilterPath> SourceSearchResults;`
- L270 _private member_ `TOptional<FFilterPath> FocusedSearchResult;`
- L272 _private member_ `TArray<TObjectPtr<UHierarchyElement>> PrimaryFilterRootItems;`
- L273 _private member_ `TSharedPtr<STreeView<TObjectPtr<UHierarchyElement>>> PrimaryFilterSelector;`
- L274 _private member_ `TSharedPtr<STaggedAssetBrowserContent> AssetBrowserContent;`
- L276 _private member_ `SSplitter::FSlot* PrimaryFiltersSlot = nullptr;`
- L277 _private member_ `SHorizontalBox::FSlot* SectionsSlot = nullptr;`
- L278 _private member_ `SHorizontalBox::FSlot* AssetBrowserAreaSplitterSlot = nullptr;`
- L279 _private member_ `SSplitter::FSlot* AssetBrowserContentSlot = nullptr;`
- L280 _private member_ `SSplitter::FSlot* CustomTabsSlot = nullptr;`
- L281 _private member_ `SVerticalBox::FSlot* AdditionalWidgetSlot = nullptr;`
- L283 _private member_ `TSharedPtr<class STaggedAssetBrowserSections> SectionsSlotWidget;`
- L284 _private member_ `TSharedPtr<SWidget> PrimaryFiltersSlotWidget;`
- L286 _private member_ `TStrongObjectPtr<UTaggedAssetBrowserMenuContext> ThisContext;`
- L297 _private member_ `TSharedPtr<FDefaultDetailsTabMembers> DefaultDetailsTabMembers;` — A struct encapsulating members who are only relevant if the default details tab is created.
- L301 _private member_ `bool bSuppressSaveAndLoad = false;` — Used to temporarily stop saving & loading config state. This is used for initialization where setting the default state should not be saved into config.
- L304 _private member_ `mutable FName LastSelectedPrimaryFilterIdentifierFallback = NAME_None;` — We use this fallback as a means to save our last selected filter, in case we have no valid active selections anymore.
- L316 _private member_ `mutable FSlotValues PrimaryFiltersSlotValues;`

#### struct `STaggedAssetBrowser::FInterfaceOverrideProfiles`  
`struct FInterfaceOverrideProfiles`  
_L62-68_
- desc: Contains override names for specific menu names. By default, the ProfileName is used as suffix for all menus.
- L64 _public member_ `TOptional<FName> AssetViewOptionsProfileName;`
- L65 _public member_ `TOptional<FName> AssetViewContextMenuName;`
- L66 _public member_ `TOptional<FName> FilterBarSaveName;`
- L67 _public member_ `TOptional<EAssetTypeCategories::Type> DefaultFilterMenuExpansion;`

#### struct `STaggedAssetBrowser::FFilterPath`  
`struct FFilterPath`  
_L189-209_
- L191 _public member_ `TArray<TWeakObjectPtr<UHierarchyElement>> Path;`
- L193 _public function_ `TWeakObjectPtr<UHierarchyElement> GetEntry() const`
- L205 _public function_ `bool operator==(const FFilterPath& Item) const`

#### struct `STaggedAssetBrowser::FDefaultDetailsTabMembers`  
`struct FDefaultDetailsTabMembers : public TSharedFromThis<FDefaultDetailsTabMembers>`  
_L288-294_
- inherits: `TSharedFromThis<FDefaultDetailsTabMembers>`
- L290 _public member_ `TSharedPtr<SWidgetSwitcher> DefaultDetailsSwitcher;`
- L291 _public member_ `SWidgetSwitcher::FSlot* AssetBrowserDefaultDetailsSlot = nullptr;`
- L293 _public prototype_ `EVisibility OnGetThumbnailVisibility() const;`

#### struct `STaggedAssetBrowser::FSlotValues`  
`struct FSlotValues`  
_L306-314_
- L308 _public prototype_ `FSlotValues() = default;`
- L310 _public member_ `float CurrentSizeValue = 0.15f;`
- L312 _public member_ `float DefaultSizeValue = 0.15f;`
- L313 _public member_ `float DefaultMinSize = 50.f;`

#### class `STaggedAssetBrowserWindow`  
`class STaggedAssetBrowserWindow : public SWindow`  
_L319-343_
- inherits: `SWindow`
- L322 _public function_ `SLATE_BEGIN_ARGS(STaggedAssetBrowserWindow)`
- L325 _public prototype_ `SLATE_ARGUMENT(STaggedAssetBrowser::FArguments, AssetBrowserArgs) SLATE_ARGUMENT(SWindow::FArguments, WindowArgs) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UTaggedAssetBrowserConfiguration& Configuration);`
- L331 _public function_ `STaggedAssetBrowserWindow()`
- L332 _public function_ `virtual ~STaggedAssetBrowserWindow() override`
- L334 _public prototype_ `bool HasSelectedAssets() const;`
- L336 _public prototype_ `TArray<FAssetData> GetSelectedAssets() const;`
- L339 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L342 _protected member_ `TSharedPtr<STaggedAssetBrowser> AssetBrowser;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGenerateAssetWidget, const FAssetData& Asset) struct FTaggedAssetBrowserCustomTabInfo { FTaggedAssetBrowserCustomTabInfo() {}; FText Title; const FSlateBrush* Icon = nullptr; FOnGetContent OnGetTabContent; FOnAssetSelected OnAssetSelected; };`
- L56 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<TSharedRef<FFrontendFilter>>, FOnGetExtraFrontendFilters) DECLARE_DELEGATE_OneParam(FOnOverrideAssetPickerConfig, FAssetPickerConfig&) DECLARE_DELEGATE_OneParam(FOnActiveSectionChanged, const UTaggedAssetBrowserSection*) DECLARE_DELEGATE(FOnPrimaryFilterSelectionChanged) struct FInterfaceOverrideProfiles { TOptional<FName> AssetViewOptionsProfileName; TOptional<FName> AssetViewContextMenuName; TOptional<FName> FilterBarSaveName; TOptional<EAssetTypeCategories::Type> DefaultFilterMenuExpansion; };`
- L57 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOverrideAssetPickerConfig, FAssetPickerConfig&) DECLARE_DELEGATE_OneParam(FOnActiveSectionChanged, const UTaggedAssetBrowserSection*) DECLARE_DELEGATE(FOnPrimaryFilterSelectionChanged) struct FInterfaceOverrideProfiles { TOptional<FName> AssetViewOptionsProfileName; TOptional<FName> AssetViewContextMenuName; TOptional<FName> FilterBarSaveName; TOptional<EAssetTypeCategories::Type> DefaultFilterMenuExpansion; };`
- L58 _delegate_ `DECLARE_DELEGATE_OneParam(FOnActiveSectionChanged, const UTaggedAssetBrowserSection*) DECLARE_DELEGATE(FOnPrimaryFilterSelectionChanged) struct FInterfaceOverrideProfiles { TOptional<FName> AssetViewOptionsProfileName; TOptional<FName> AssetViewContextMenuName; TOptional<FName> FilterBarSaveName; TOptional<EAssetTypeCategories::Type> DefaultFilterMenuExpansion; };`
- L59 _delegate_ `DECLARE_DELEGATE(FOnPrimaryFilterSelectionChanged) struct FInterfaceOverrideProfiles { TOptional<FName> AssetViewOptionsProfileName; TOptional<FName> AssetViewContextMenuName; TOptional<FName> FilterBarSaveName; TOptional<EAssetTypeCategories::Type> DefaultFilterMenuExpansion; };`

### `Source/Editor/UserAssetTagsEditor/Public/Widgets/STaggedAssetBrowserAssetFactoryWindow.h` (Public)


#### class `STaggedAssetBrowserAssetFactoryWindow`  
`class STaggedAssetBrowserAssetFactoryWindow : public STaggedAssetBrowserWindow`  
_L15-84_
- inherits: `STaggedAssetBrowserWindow`
- desc: This window is meant to be used within a factory. Modal: Summon this window from ConfigureProperties, then check "ShouldProceedWithAction", retrieve selected assets and settings. Non-Modal: Summon this window from ConfigurePropertiesAsync and pass in the AsyncFactoryArguments. In both cases, the actual asset creation invocation of the factory is handled by the Content Browser or the Asset Tools.
- L29 _public function_ `SLATE_BEGIN_ARGS(STaggedAssetBrowserAssetFactoryWindow)`
- L30 _public prototype_ `SLATE_ARGUMENT(STaggedAssetBrowserWindow::FArguments, AssetBrowserWindowArgs) SLATE_ARGUMENT(TOptional<FAsyncFactoryArguments>, AsyncFactoryArguments) SLATE_ARGUMENT_DEFAULT(UClass*, AdditionalFactorySettingsClass) = nullptr;`
- L36 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, bUseAssetDefinition) = true;` — If the asset definition is used, data such as its AssetDisplayName will be used. If not, the class display name is used.
- L38 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, bAllowEmptyAssetCreation) = true;` — If empty asset creation is allowed, a "Create Empty" button will show up on the bottom left that will terminate the window without a selection.
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UTaggedAssetBrowserConfiguration& Configuration, UClass& CreatedClass);`
- L43 _public function_ `STaggedAssetBrowserAssetFactoryWindow()`
- L47 _public function_ `bool ShouldProceedWithAction() const` — For use in a modal context: retrieve whether the user activated assets or clicked a Proceed button, or closed the window.
- L50 _public function_ `UObject* RetrieveFactorySettings() const` — Retrieve the factory settings object, if available. This can be used to further customize the factory process.
- L53 _private prototype_ `bool CheckValidArguments(const FArguments& InArgs) const;`
- L56 _private prototype_ `void OnAssetsActivated(const TArray<FAssetData>& AssetData, EAssetTypeActivationMethod::Type);` — The function that will be called by our buttons or by the asset picker itself if double-clicking, hitting enter etc.
- L58 _private prototype_ `FReply Proceed();`
- L59 _private prototype_ `FReply Cancel();`
- L61 _private prototype_ `FText GetAssetTypeName() const;`
- L63 _private prototype_ `FText GetCreateButtonTooltip() const;`
- L65 _private prototype_ `TSharedRef<SWidget> CreateFactorySettingsTab();`
- L67 _private prototype_ `virtual FString GetReferencerName() const override;`
- L68 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L70 _private prototype_ `void CloseIfOtherWindowFocused(const FFocusEvent& FocusEvent, const FWeakWidgetPath& OldWidgetPath, const TSharedPtr<SWidget>& OldFocusedWidget, const FWidgetPath& NewWidgetPath, const TSharedPtr<SWidget>& NewFocusedWidget);`
- L73 _private member_ `TWeakObjectPtr<UClass> CreatedClass;`
- L74 _private member_ `TWeakObjectPtr<UClass> AdditionalFactorySettingsClass;`
- L75 _private member_ `TWeakObjectPtr<const UAssetDefinition> AssetDefinition;`
- L77 _private member_ `TObjectPtr<UObject> FactorySettingsObject;`
- L78 _private member_ `TSharedPtr<class IDetailsView> FactorySettingsWidget;`
- L80 _private member_ `bool bProceedWithAction = false;`
- L81 _private member_ `bool bAllowEmptyAssetCreation = false;`
- L83 _private member_ `TOptional<FAsyncFactoryArguments> AsyncFactoryArguments;`

#### struct `STaggedAssetBrowserAssetFactoryWindow::FAsyncFactoryArguments`  
`struct FAsyncFactoryArguments`  
_L18-27_
- L21 _public member_ `TStrongObjectPtr<UFactory> Factory;` — The factory that summoned this window from ConfigurePropertiesAsync.
- L23 _public member_ `FOnAssetsActivated OnAssetsActivated;` — A callback to let your factory be informed of asset activation so it can configure its properties accordingly.
- L25 _public member_ `FOnFactoryConfigurePropertiesAsyncComplete OnFactoryConfigurePropertiesComplete;` — The callbacks from ConfigurePropertiesAsync to let the process know to continue or to cancel.
- L26 _public member_ `FOnFactoryConfigurePropertiesAsyncCancelled OnFactoryConfigurePropertiesCancelled;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`

### `Source/Editor/UserAssetTagsEditor/Public/Widgets/STaggedAssetBrowserContent.h` (Public)


#### class `STaggedAssetBrowserContent`  
`class STaggedAssetBrowserContent : public SCompoundWidget`  
_L14-45_
- inherits: `SCompoundWidget`
- L17 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterAsset, const FAssetData&) DECLARE_DELEGATE_RetVal(TArray<TSharedRef<FFrontendFilter>>, FOnGetExtraFrontendFilters) SLATE_BEGIN_ARGS(STaggedAssetBrowserContent)`
- L23 _public prototype_ `SLATE_ARGUMENT(FAssetPickerConfig, InitialConfig) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `void SetARFilter(FARFilter InFilter);`
- L31 _public prototype_ `TArray<FAssetData> GetCurrentSelection() const;`
- L34 _public prototype_ `TSharedPtr<SAssetPicker> GetAssetPicker() const;` — Returns the asset picker widget created during construction, if it exists.
- L37 _private member_ `FRefreshAssetViewDelegate RefreshAssetViewDelegate;`
- L38 _private member_ `FSyncToAssetsDelegate SyncToAssetsDelegate;`
- L39 _private member_ `FSetARFilterDelegate SetNewFilterDelegate;`
- L40 _private member_ `FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;`
- L42 _private member_ `FAssetPickerConfig InitialAssetPickerConfig;`
- L44 _private member_ `TSharedPtr<SAssetPicker> AssetPickerPtr;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterAsset, const FAssetData&) DECLARE_DELEGATE_RetVal(TArray<TSharedRef<FFrontendFilter>>, FOnGetExtraFrontendFilters) SLATE_BEGIN_ARGS(STaggedAssetBrowserContent) { } SLATE_ARGUMENT(FAssetPickerConfig, InitialConfig) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<TSharedRef<FFrontendFilter>>, FOnGetExtraFrontendFilters) SLATE_BEGIN_ARGS(STaggedAssetBrowserContent) { } SLATE_ARGUMENT(FAssetPickerConfig, InitialConfig) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Source/Editor/UserAssetTagsEditor/Public/Widgets/STaggedAssetBrowserSections.h` (Public)


#### class `STaggedAssetBrowserSection`  
`class STaggedAssetBrowserSection : public SCompoundWidget`  
_L16-43_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(STaggedAssetBrowserSection)`
- L21 _public prototype_ `SLATE_EVENT(FOnCheckStateChanged, OnCheckStateChanged) SLATE_ATTRIBUTE(ECheckBoxState, IsChecked) SLATE_EVENT(FOnGetContent, OnGetMenuContent) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UTaggedAssetBrowserSection& InSection);`
- L29 _private prototype_ `void OnCheckStateChanged(ECheckBoxState CheckBoxState);`
- L30 _private prototype_ `ECheckBoxState GetCheckState() const;`
- L31 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();`
- L32 _private prototype_ `FSlateColor GetIconForegroundColor() const;`
- L33 _private prototype_ `const FSlateBrush* GetIconBrush() const;`
- L34 _private prototype_ `EVisibility GetLabelVisibility() const;`
- L35 _private prototype_ `FText GetLabelText() const;`
- L38 _private member_ `TWeakObjectPtr<const UTaggedAssetBrowserSection> Section;`
- L40 _private member_ `FOnCheckStateChanged OnCheckStateChangedDelegate;`
- L41 _private member_ `TAttribute<ECheckBoxState> IsCheckedAttribute;`
- L42 _private member_ `FOnGetContent OnGetMenuContentDelegate;`

#### class `STaggedAssetBrowserSections`  
`class STaggedAssetBrowserSections : public SCompoundWidget`  
_L45-76_
- inherits: `SCompoundWidget`
- L48 _public function_ `DECLARE_DELEGATE_OneParam(FOnSectionSelected, const UTaggedAssetBrowserSection* Section) SLATE_BEGIN_ARGS(STaggedAssetBrowserSections) : _InitiallyActiveSection(nullptr)`
- L53 _public prototype_ `SLATE_ARGUMENT(const UTaggedAssetBrowserSection*, InitiallyActiveSection) SLATE_EVENT(FOnSectionSelected, OnSectionSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UTaggedAssetBrowserFilterRoot& InFilterRoot);`
- L60 _public prototype_ `void RebuildWidget();`
- L62 _public function_ `const UTaggedAssetBrowserSection* GetActiveSection() const`
- L65 _private prototype_ `void OnSectionSelected(ECheckBoxState CheckBoxState, const UTaggedAssetBrowserSection* InSection);`
- L66 _private prototype_ `ECheckBoxState IsSectionActive(const UTaggedAssetBrowserSection* InSection) const;`
- L69 _private member_ `TWeakObjectPtr<const UTaggedAssetBrowserFilterRoot> FilterRoot;`
- L71 _private member_ `FOnSectionSelected OnSectionSelectedDelegate;`
- L73 _private member_ `TWeakObjectPtr<const UTaggedAssetBrowserSection> ActiveSection;`
- L74 _private member_ `TSharedPtr<SScrollBox> ScrollBox;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSectionSelected, const UTaggedAssetBrowserSection* Section) SLATE_BEGIN_ARGS(STaggedAssetBrowserSections) : _InitiallyActiveSection(nullptr) {} SLATE_ARGUMENT(const UTaggedAssetBrowserSection*, InitiallyActiveSection) SLATE_EVENT(FOnSectionSelected, OnSectionSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UTaggedAssetBrowserFilterRoot& InFilterRoot);`

### `Source/Editor/UserAssetTagsEditor/Public/Widgets/SUserAssetTagBrowserSelectedAssetDetails.h` (Public)


#### struct `FDisplayedPropertyData`  
`struct FDisplayedPropertyData`  
_L11-19_
- L13 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldDisplayProperty, const FAssetData&) DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FGenerateWidget, const FAssetData&) FShouldDisplayProperty ShouldDisplayPropertyDelegate;`
- L17 _public member_ `FGenerateWidget NameWidgetDelegate;`
- L18 _public member_ `FGenerateWidget ValueWidgetDelegate;`

#### struct `FAssetDetailsDisplayInfo`  
`struct FAssetDetailsDisplayInfo`  
_L21-27_
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetDescription, const FAssetData&);`
- L25 _public member_ `FGetDescription GetDescriptionDelegate;`
- L26 _public member_ `TArray<FDisplayedPropertyData> DisplayedProperties;`

#### struct `FTaggedAssetBrowserDetailsDisplayDatabase`  
`struct FTaggedAssetBrowserDetailsDisplayDatabase`  
_L29-33_
- L31 _public prototype_ `static void RegisterClass(UClass* Class, FAssetDetailsDisplayInfo ClassInfo);`
- L32 _public member_ `static TMap<UClass*, FAssetDetailsDisplayInfo> Data;`

#### class `SUserAssetTag`  
`class SUserAssetTag : public SCompoundWidget`  
_L37-56_
- inherits: `SCompoundWidget`
- L39 _private function_ `SLATE_BEGIN_ARGS(SUserAssetTag)`
- L42 _private prototype_ `SLATE_EVENT(FOnAssetTagActivated, OnAssetTagActivated) SLATE_ARGUMENT(TOptional<FText>, OnAssetTagActivatedTooltip) SLATE_END_ARGS()`
- L50 _private prototype_ `FReply OnClicked() const;`
- L53 _private member_ `FName UserAssetTag;`
- L54 _private member_ `FOnAssetTagActivated OnAssetTagActivated;`
- L55 _private member_ `TOptional<FText> OnAssetTagActivatedTooltip;`

#### class `SUserAssetTagRow`  
`class SUserAssetTagRow : public SCompoundWidget`  
_L58-68_
- inherits: `SCompoundWidget`
- L60 _private function_ `SLATE_BEGIN_ARGS(SUserAssetTagRow)`
- L63 _private prototype_ `SLATE_EVENT(FOnAssetTagActivated, OnAssetTagActivated) SLATE_ARGUMENT(TOptional<FText>, OnAssetTagActivatedTooltip) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAssetData& Asset);`

#### class `SUserAssetTagBrowserSelectedAssetDetails`  
`class SUserAssetTagBrowserSelectedAssetDetails : public SCompoundWidget`  
_L74-120_
- inherits: `SCompoundWidget`
- desc: The default widget for the right hand side of the tagged asset browser, showing details of the selected assets. It requires previous configuration using the FUserAssetTag
- L77 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGenerateWidget, const FAssetData& AssetData) SLATE_BEGIN_ARGS(SUserAssetTagBrowserSelectedAssetDetails) : _ShowThumbnailSlotWidget(EVisibility::Visible) , _MaxDesiredDescriptionWidth(300.f) , _MaxDesiredPropertiesWidth(300.f)`
- L85 _public prototype_ `SLATE_ATTRIBUTE(EVisibility, ShowThumbnailSlotWidget) SLATE_EVENT(FOnGenerateWidget, OnGenerateThumbnailReplacementWidget) SLATE_EVENT(FOnAssetTagActivated, OnAssetTagActivated) SLATE_ARGUMENT(TOptional<FText>, OnAssetTagActivatedTooltip) /* Text will automatically wrap according to actual width. * With this you can specify the maximum width you want the description to be;`
- L103 _private prototype_ `FReply CopyAssetPathToClipboard() const;`
- L106 _private member_ `FAssetData AssetData;`
- L107 _private member_ `TAttribute<EVisibility> ShowThumbnailSlot;`
- L108 _private member_ `FOnGenerateWidget OnGenerateThumbnailReplacementWidgetDelegate;`
- L109 _private member_ `TSharedPtr<FAssetThumbnail> CurrentAssetThumbnail;`
- L110 _private member_ `FOnAssetTagActivated OnAssetTagActivated;`
- L111 _private member_ `TOptional<FText> OnAssetTagActivatedTooltip;`
- L113 _private prototype_ `TSharedRef<SWidget> CreateAssetThumbnailWidget();`
- L114 _private prototype_ `TSharedRef<SWidget> CreateTitleWidget();`
- L115 _private prototype_ `TSharedRef<SWidget> CreateTypeWidget();`
- L116 _private prototype_ `TSharedRef<SWidget> CreatePathWidget();`
- L117 _private prototype_ `TSharedRef<SWidget> CreateDescriptionWidget();`
- L118 _private prototype_ `TSharedRef<SWidget> CreateOptionalPropertiesList();`
- L119 _private prototype_ `TSharedRef<SWidget> CreateAssetTagRow();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`
- L13 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldDisplayProperty, const FAssetData&) DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FGenerateWidget, const FAssetData&) FShouldDisplayProperty ShouldDisplayPropertyDelegate;`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FGenerateWidget, const FAssetData&) FShouldDisplayProperty ShouldDisplayPropertyDelegate;`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetDescription, const FAssetData&);`
- L35 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetTagActivated, const FName& UserAssetTag);`
- L35 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetTagActivated, const FName& UserAssetTag);`
- L77 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGenerateWidget, const FAssetData& AssetData) SLATE_BEGIN_ARGS(SUserAssetTagBrowserSelectedAssetDetails) : _ShowThumbnailSlotWidget(EVisibility::Visible) , _MaxDesiredDescriptionWidth(300.f) , _MaxDesiredPropertiesWidth(300.f) { } SLATE_ATTRIBUTE(EVisibility, ShowThumbnailSlotWidget) SLATE_EVENT(FOnGenerateWidget, OnGenerateThumbnailReplacementWidget) SLATE_EVENT(FOnAssetTagActivated, OnAssetTagActivated) SLATE_ARGUMENT(TOptional<FText>, OnAssetTagActivatedTooltip) /* Text will automatically wrap according to actual width. * With this you can specify the maximum width you want the description to be;`

### `Source/Editor/UserAssetTagsEditor/Public/Widgets/SUserAssetTagsEditor.h` (Public)


#### struct `FUserAssetTagInfo`  
`struct FUserAssetTagInfo`  
_L18-22_
- desc: Optional info relating to a specific tag, useful to surface more information to the user.
- L21 _public member_ `TArray<const UUserAssetTagProvider*> Sources;` — A tag can come from multiple sources at once.

#### class `SUserAssetTagsEditor`  
`class SUserAssetTagsEditor : public SCompoundWidget`  
_L25-107_
- inherits: `SCompoundWidget`
- desc: The actual editor widget to assign/unassign tags.
- L28 _public function_ `SLATE_BEGIN_ARGS(SUserAssetTagsEditor)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L38 _public function_ `const TArray<FAssetData>& GetSelectedAssets() const`
- L40 _public prototype_ `void RefreshDataAndMenus();`
- L41 _public prototype_ `static void RefreshMenus();`
- L42 _public prototype_ `static void RefreshSelectedAssetsMenu();`
- L43 _public prototype_ `static void RefreshSuggestedTagMenus();`
- L44 _public prototype_ `static void RefreshOwnedTagMenus();`
- L45 _public prototype_ `static void RefreshProviderExtensionToolbarMenu();`
- L48 _private prototype_ `TSharedPtr<SWidget> CreateSelectedAssetList();`
- L49 _private prototype_ `TSharedPtr<SWidget> CreateSuggestedTagList();`
- L50 _private prototype_ `TSharedPtr<SWidget> CreateOwnedTagsList();`
- L51 _private prototype_ `TSharedPtr<SWidget> CreateToolbar();`
- L53 _private prototype_ `static TArray<FAssetData> GetCurrentContentBrowserAssetSelection();`
- L55 _private prototype_ `void OnCommitNewTag(const FText& Text, ETextCommit::Type CommitType);`
- L56 _private prototype_ `FReply OnAddTagButtonClicked();`
- L57 _private prototype_ `bool IsAddTagButtonEnabled() const;`
- L59 _private prototype_ `const FSlateBrush* GetViewOptionsBadgeIcon() const;`
- L61 _private prototype_ `static TSharedRef<SWidget> GenerateRowContent_SelectedAsset(const FAssetData& AssetData, const UUserAssetTagEditorContext* Context);`
- L62 _private prototype_ `static TSharedRef<SWidget> GenerateRowContent_SuggestedTag(FName UserAssetTag, const UUserAssetTagEditorContext* Context);`
- L63 _private prototype_ `static TSharedRef<SWidget> GenerateRowContent_OwnedTag(FName UserAssetTag, const UUserAssetTagEditorContext* Context);`
- L64 _private prototype_ `static TSharedRef<SWidget> CreateMenuControlWidget(const FToolMenuContext& ToolMenuContext, const FToolMenuCustomWidgetContext& ToolMenuCustomWidgetContext, const UClass* Class);`
- L66 _private prototype_ `TSharedRef<SWidget> OnGetViewOptions();`
- L67 _private prototype_ `static void ToggleSortByAlphabet(const FToolMenuContext& ToolMenuContext);`
- L68 _private prototype_ `static ECheckBoxState GetShouldSortByAlphabet(const FToolMenuContext& ToolMenuContext);`
- L69 _private prototype_ `static void ToggleViewOption_ProviderClass(const FToolMenuContext& ToolMenuContext, const UClass* ProviderClass);`
- L70 _private prototype_ `static ECheckBoxState GetViewOptions_IsProviderClassEnabled(const FToolMenuContext& ToolMenuContext, const UClass* Class);`
- L72 _private prototype_ `static void SetViewOption_ProviderClassMenuType(EUserAssetTagProviderMenuType InMenuType, const UClass* ProviderClass);`
- L73 _private prototype_ `static EUserAssetTagProviderMenuType GetViewOptions_ProviderClassMenuType(const UClass* ProviderClass);`
- L75 _private prototype_ `static const TArray<const UUserAssetTagProvider*>& GetAllProviderCDOs();`
- L76 _private prototype_ `static TArray<const UUserAssetTagProvider*> GetAllValidDefaultEnabledProviderCDOs(const UUserAssetTagEditorContext* Context);`
- L77 _private prototype_ `static TArray<const UUserAssetTagProvider*> GetValidProviderCDOs(const UUserAssetTagEditorContext* Context);`
- L78 _private prototype_ `static TArray<const UUserAssetTagProvider*> GetEnabledProviderCDOs(const UUserAssetTagEditorContext* Context);`
- L80 _private prototype_ `static FToolUIAction CreateToggleTagCheckboxAction_SuggestedTag(const FName& InUserAssetTag);`
- L81 _private prototype_ `static FToolUIAction CreateToggleTagCheckboxAction_OwnedTag(const FName& InUserAssetTag);`
- L83 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L85 _private prototype_ `static FReply OnDocumentationRequested();`
- L86 _private prototype_ `static FText GetDocumentationButtonTooltipText();`
- L88 _private prototype_ `static FReply OnDeleteTagClicked(FName InUserAssetTag, const UUserAssetTagEditorContext* Context);`
- L90 _private prototype_ `void HandleAssetSelectionChanged(const TArray<FAssetData>& AssetData, bool bIsPrimaryBrowser);`
- L93 _private member_ `TSharedPtr<SWidget> SelectedAssetList;`
- L94 _private member_ `TSharedPtr<SWidget> TagSuggestionList;`
- L95 _private member_ `TSharedPtr<SWidget> OwnedTagsList;`
- L97 _private member_ `TArray<FAssetData> SelectedAssets;`
- L99 _private member_ `TSharedPtr<class SEditableTextBox> AddTagTextBox;`
- L100 _private member_ `TSharedPtr<SWidget> ToolbarWidget;`
- L103 _private member_ `TStrongObjectPtr<UUserAssetTagEditorContext> ThisContext;` — The editor relies on UToolMenus a lot. We construct a context object once, and then pass it around to mostly static functions that generate the UI.
- L106 _private member_ `static TArray<const UUserAssetTagProvider*> CachedProviderCDOs;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API USERASSETTAGSEDITOR_API`
