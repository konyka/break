# Plugins / Text3DEditor

- module root: `Plugins/VirtualProduction/Text3D/Source/Text3DEditor`
- headers: 22; symbols: 235
- symbol kinds: class=21, delegate=7, enum=1, enumerator=3, function=18, member=51, namespace=18, prototype=114, struct=2
- PrivateDependencyModuleNames: AssetDefinition, Core, CoreUObject, DeveloperSettings, DirectX, EditorFramework, EditorSubsystem, Engine, FreeType2, InputCore, Projects, PropertyEditor, Slate, SlateCore, Text3D, ToolMenus, UnrealEd

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/AssetTypeActions/AssetDefinition_Text3DStyleSet.h` (Private)


#### class `UAssetDefinition_Text3DStyleSet`  
`class UAssetDefinition_Text3DStyleSet : public UAssetDefinitionDefault`  
_L10-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- desc: Defines a new asset : StyleSet
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Commands/Text3DEditorFontSelectorCommands.h` (Private)


#### class `FText3DEditorFontSelectorCommands`  
`class FText3DEditorFontSelectorCommands : public TCommands<FText3DEditorFontSelectorCommands>`  
_L8-20_
- inherits: `TCommands<FText3DEditorFontSelectorCommands>`
- L11 _public prototype_ `FText3DEditorFontSelectorCommands();`
- L14 _public prototype_ `virtual void RegisterCommands() override;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> ShowMonospacedFonts;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> ShowBoldFonts;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> ShowItalicFonts;`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Customizations/Text3DEditorCharacterPropertyTypeCustomization.h` (Private)


#### class `UE::Text3DEditor::Customization::FText3DEditorCharacterPropertyTypeIdentifier`  
`class FText3DEditorCharacterPropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L20-29_
- inherits: `IPropertyTypeIdentifier`
- desc: Only allow property customization with "TextCharacterSelector" metadata
- L24 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override`

#### class `UE::Text3DEditor::Customization::FText3DEditorCharacterPropertyTypeCustomization`  
`class FText3DEditorCharacterPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L32-56_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for UText3DCharacter object
- L35 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L38 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle , FDetailWidgetRow& InHeaderRow , IPropertyTypeCustomizationUtils& InUtils) override;`
- L42 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle , IDetailChildrenBuilder& InChildBuilder , IPropertyTypeCustomizationUtils& InUtils) override;`
- L48 _private prototype_ `FText GetCharacterText() const;`
- L49 _private prototype_ `TOptional<uint16> GetCharacterLastIndex() const;`
- L50 _private prototype_ `void OnTextCharacterChanged();`
- L52 _private member_ `uint16 ActiveIndex = 0;`
- L53 _private member_ `TWeakPtr<IPropertyHandle> CharacterPropertyHandleWeak;`
- L54 _private member_ `TWeakObjectPtr<UText3DCharacterExtensionBase> CharacterExtensionWeak;`
- L55 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtilitiesWeak;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Text3DEditor` (scope `UE`)
- L17 _namespace_ `namespace Customization` (scope `UE::Text3DEditor`)

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Customizations/Text3DEditorFontPropertyTypeCustomization.h` (Private)


#### class `FText3DEditorFontPropertyTypeIdentifier`  
`class FText3DEditorFontPropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L16-25_
- inherits: `IPropertyTypeIdentifier`
- desc: Only allow property customization with "AdvancedFontPicker" metadata
- L20 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override`

#### class `FText3DEditorFontPropertyTypeCustomization`  
`class FText3DEditorFontPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L28-45_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for UFont object to display an advanced font picker for project and system fonts
- L31 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L34 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle , FDetailWidgetRow& InHeaderRow , IPropertyTypeCustomizationUtils& InUtils) override;`
- L38 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle , IDetailChildrenBuilder& InChildBuilder , IPropertyTypeCustomizationUtils& InUtils) override;`
- L44 _private member_ `TSharedPtr<IPropertyHandle> FontPropertyHandle;`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Customizations/Text3DEditorHorizontalPropertyTypeCustomization.h` (Private)


#### class `FText3DEditorHorizontalPropertyTypeIdentifier`  
`class FText3DEditorHorizontalPropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L14-23_
- inherits: `IPropertyTypeIdentifier`
- desc: Only allow property customization with "CustomAlignmentWidget" metadata
- L18 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override`

#### class `FText3DEditorHorizontalPropertyTypeCustomization`  
`class FText3DEditorHorizontalPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L26-38_
- inherits: `IPropertyTypeCustomization`
- desc: Used to customize EText3DHorizontalTextAlignment enum
- L29 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L32 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InRow, IPropertyTypeCustomizationUtils& InUtils) override;`
- L33 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InBuilder, IPropertyTypeCustomizationUtils& InUtils) override;`
- L37 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Customizations/Text3DEditorTextComponentDetailCustomization.h` (Private)


#### class `UE::Text3DEditor::Customization::FText3DEditorTextComponentDetailCustomization`  
`class FText3DEditorTextComponentDetailCustomization : public IDetailCustomization`  
_L19-43_
- inherits: `IDetailCustomization`
- desc: Used to customize Text3D component properties in details panel
- L22 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L39 _protected prototype_ `FReply OnFunctionButtonClicked(FName InFunctionName);` — Execute ufunction with that name on selected objects
- L42 _protected member_ `TMap<FName, TArray<FObjectFunction>> NamedObjectFunctions;` — Function name to object ufunction mapping

#### struct `UE::Text3DEditor::Customization::FText3DEditorTextComponentDetailCustomization::FObjectFunction`  
`struct FObjectFunction`  
_L32-36_
- L34 _public member_ `TWeakObjectPtr<UObject> Owner;`
- L35 _public member_ `TWeakObjectPtr<UFunction> Function;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Text3DEditor` (scope `UE`)
- L16 _namespace_ `namespace Customization` (scope `UE::Text3DEditor`)

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Customizations/Text3DEditorVerticalPropertyTypeCustomization.h` (Private)


#### class `FText3DEditorVerticalPropertyTypeIdentifier`  
`class FText3DEditorVerticalPropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L14-23_
- inherits: `IPropertyTypeIdentifier`
- desc: Only allow property customization with "CustomAlignmentWidget" metadata
- L18 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override`

#### class `FText3DEditorVerticalPropertyTypeCustomization`  
`class FText3DEditorVerticalPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L26-38_
- inherits: `IPropertyTypeCustomization`
- desc: Used to customize EText3DVerticalTextAlignment enum
- L29 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L32 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InRow, IPropertyTypeCustomizationUtils& InUtils) override;`
- L33 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InBuilder, IPropertyTypeCustomizationUtils& InUtils) override;`
- L37 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Factories/Text3DEditorActorFactory.h` (Private)


#### class `UText3DEditorActorFactory`  
`class UText3DEditorActorFactory : public UActorFactory`  
_L9-15_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L14 _public prototype_ `UText3DEditorActorFactory();`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Factories/Text3DEditorStyleSetFactory.h` (Private)


#### class `UText3DEditorStyleSetFactory`  
`class UText3DEditorStyleSetFactory : public UFactory`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Factory that creates a Style Set asset
- L14 _private prototype_ `UText3DEditorStyleSetFactory();`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Logs/Text3DEditorLogs.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogText3DEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogText3DEditor, Log, All);`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Platforms/Linux/LinuxSystemFontLoading.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Text3D` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Text3D`)
- L11 _namespace_ `namespace Fonts` (scope `UE::Text3D::Private`)
- L13 _prototype_ `void GetSystemFontInfo(TMap<FString, FText3DFontFamily>& OutFontsInfo);` (scope `UE::Text3D::Private::Fonts`)
- L14 _prototype_ `void ListAvailableFontFiles();` (scope `UE::Text3D::Private::Fonts`)

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Platforms/Mac/MacSystemFontLoading.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Text3D` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Text3D`)
- L10 _namespace_ `namespace Fonts` (scope `UE::Text3D::Private`)
- L12 _prototype_ `void GetSystemFontInfo(TMap<FString, FText3DFontFamily>& OutFontsInfo);` (scope `UE::Text3D::Private::Fonts`)
- L13 _prototype_ `void ListAvailableFontFiles();` (scope `UE::Text3D::Private::Fonts`)

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Platforms/PlatformSystemFontLoading.h` (Private)
_(no declarations extracted)_

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Platforms/Windows/WindowsSystemFontLoading.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Text3D` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Text3D`)
- L10 _namespace_ `namespace Fonts` (scope `UE::Text3D::Private`)
- L12 _prototype_ `void GetSystemFontInfo(TMap<FString, FText3DFontFamily>& OutFontsInfo);` (scope `UE::Text3D::Private::Fonts`)
- L13 _prototype_ `void ListAvailableFontFiles();` (scope `UE::Text3D::Private::Fonts`)

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Styles/Text3DEditorStyle.h` (Private)


#### class `FText3DEditorStyle`  
`class FText3DEditorStyle : public FSlateStyleSet`  
_L7-19_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `FText3DEditorStyle();`
- L14 _public function_ `static FText3DEditorStyle& Get()`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Subsystems/Text3DEditorFontSubsystem.h` (Private)


#### enum `EText3DEditorFontLocationFlags`  
`enum class EText3DEditorFontLocationFlags : uint8`  
_L16-23_
- reflection: `UENUM()`
- L18 _public enumerator_ `None = 0`
- L20 _public enumerator_ `Project = 1 << 0` — Font is available in the project
- L22 _public enumerator_ `System = 1 << 2` — Font is available on the system

#### struct `FText3DEditorFont`  
`struct FText3DEditorFont`  
_L27-50_
- reflection: `USTRUCT()`
- desc: Helper to manipulate a font in editor
- L33 _public member_ `EText3DEditorFontLocationFlags FontLocationFlags = EText3DEditorFontLocationFlags::None;` — `UPROPERTY()` — Current location of the font
- L37 _public member_ `FString FontName;` — `UPROPERTY()` — The font name to lookup the font
- L41 _public member_ `TObjectPtr<UFont> Font;` — `UPROPERTY()` — The actual font object if available
- L45 _public member_ `TArray<TObjectPtr<UFontFace>> FontFaces;` — `UPROPERTY()` — Font faces available composing this font
- L49 _public member_ `EText3DFontStyleFlags FontStyleFlags = EText3DFontStyleFlags::None;` — `UPROPERTY()` — Font style flags

#### class `UText3DEditorFontSubsystem`  
`class UText3DEditorFontSubsystem : public UEditorSubsystem`  
_L53-140_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- L58 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnProjectFontRegistered, const FString& InFontName) DECLARE_MULTICAST_DELEGATE_OneParam(FOnProjectFontUnregistered, const FString& InFontName) DECLARE_MULTICAST_DELEGATE_OneParam(FOnSystemFontRegistered, const FString& InFontName) DECLARE_MULTICAST_DELEGATE_OneParam(FOnSystemFontUnregistered, const FString& InFontName) static UText3DEditorFontSubsystem* Get();`
- L65 _public prototype_ `static bool IsFontFileSupported(const FString& InFontFilePath);`
- L67 _public function_ `FOnProjectFontRegistered::RegistrationType& OnProjectFontRegistered()`
- L72 _public function_ `FOnProjectFontUnregistered::RegistrationType& OnProjectFontUnregistered()`
- L77 _public function_ `FOnSystemFontRegistered::RegistrationType& OnSystemFontRegistered()`
- L82 _public function_ `FOnSystemFontUnregistered::RegistrationType& OnSystemFontUnregistered()`
- L88 _public prototype_ `bool ImportSystemFont(const FString& InFontName);` — Imports system font into project font
- L90 _public prototype_ `TArray<FString> GetProjectFontNames() const;`
- L91 _public prototype_ `TArray<FString> GetSystemFontNames() const;`
- L92 _public prototype_ `TArray<FString> GetFavoriteFontNames() const;`
- L94 _public prototype_ `const FText3DEditorFont* GetEditorFont(const FString& InFontName) const;`
- L95 _public prototype_ `const FText3DEditorFont* GetSystemFont(const FString& InFontName) const;`
- L96 _public prototype_ `const FText3DEditorFont* GetProjectFont(const FString& InFontName) const;`
- L97 _public prototype_ `const FText3DEditorFont* FindEditorFont(const UFont* InFont) const;`
- L101 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& InCollection) override;`
- L102 _protected prototype_ `virtual void Deinitialize() override;`
- L105 _protected prototype_ `bool IsProjectFontUpToDate(const FString& InFontName);`
- L106 _protected prototype_ `void OnSaveImportedFonts(UWorld* InWorld, FObjectPreSaveContext InContext);`
- L108 _protected prototype_ `void OnAssetLoaded();`
- L109 _protected prototype_ `void OnAssetAdded(const FAssetData& InAssetData);`
- L110 _protected prototype_ `void OnAssetDeleted(UObject* InObject);`
- L112 _protected prototype_ `void LoadProjectFonts();`
- L113 _protected prototype_ `bool RegisterProjectFont(UFont* InFont);`
- L114 _protected prototype_ `bool UnregisterProjectFont(const UFont* InFont);`
- L116 _protected prototype_ `void LoadSystemFonts();`
- L117 _protected prototype_ `bool RegisterSystemFont(const FText3DFontFamily& InFontFamily);`
- L118 _protected prototype_ `bool UnregisterSystemFont(const FString& InFontName);`
- L120 _protected prototype_ `UFont* ResolveFontByName(const FString& InFontName);`
- L124 _protected member_ `TMap<FString, FText3DEditorFont> ProjectFonts;` — `UPROPERTY()` — Registered font available to use within the project
- L128 _protected member_ `TMap<FString, FText3DEditorFont> SystemFonts;` — `UPROPERTY()` — Registered font available to use within the system
- L131 _protected member_ `TArray<TObjectPtr<UPackage>> PackagesToSave;` — `UPROPERTY()`
- L134 _protected member_ `bool bInitialized = false;` — Is the subsystem initialized
- L136 _protected member_ `FOnProjectFontRegistered OnProjectFontRegisteredDelegate;`
- L137 _protected member_ `FOnProjectFontUnregistered OnProjectFontUnregisteredDelegate;`
- L138 _protected member_ `FOnSystemFontRegistered OnSystemFontRegisteredDelegate;`
- L139 _protected member_ `FOnSystemFontUnregistered OnSystemFontUnregisteredDelegate;`

#### Free symbols / members of external scopes

- L58 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnProjectFontRegistered, const FString& InFontName) DECLARE_MULTICAST_DELEGATE_OneParam(FOnProjectFontUnregistered, const FString& InFontName) DECLARE_MULTICAST_DELEGATE_OneParam(FOnSystemFontRegistered, const FString& InFontName) DECLARE_MULTICAST_DELEGATE_OneParam(FOnSystemFontUnregistered, const FString& InFontName) static UText3DEditorFontSubsystem* Get();`
- L59 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnProjectFontUnregistered, const FString& InFontName) DECLARE_MULTICAST_DELEGATE_OneParam(FOnSystemFontRegistered, const FString& InFontName) DECLARE_MULTICAST_DELEGATE_OneParam(FOnSystemFontUnregistered, const FString& InFontName) static UText3DEditorFontSubsystem* Get();`
- L60 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSystemFontRegistered, const FString& InFontName) DECLARE_MULTICAST_DELEGATE_OneParam(FOnSystemFontUnregistered, const FString& InFontName) static UText3DEditorFontSubsystem* Get();`
- L61 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSystemFontUnregistered, const FString& InFontName) static UText3DEditorFontSubsystem* Get();`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Text3DEditorModule.h` (Private)


#### class `FText3DEditorModule`  
`class FText3DEditorModule final : public IModuleInterface`  
_L9-21_
- inherits: `IModuleInterface`
- L12 _public prototype_ `FText3DEditorModule() = default;`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private member_ `TArray<FName> RegisteredTypeNames;`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Widgets/SText3DEditorFontField.h` (Private)


#### class `SText3DEditorFontField`  
`class SText3DEditorFontField : public SCompoundWidget`  
_L15-41_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SText3DEditorFontField)`
- L19 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FString>, FontItem) SLATE_ARGUMENT(bool, ShowFavoriteButton) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L26 _protected prototype_ `void UpdateFont();`
- L28 _protected prototype_ `FReply OnToggleFavoriteClicked();`
- L29 _protected prototype_ `ECheckBoxState GetFavoriteState() const;`
- L30 _protected prototype_ `FSlateColor GetToggleFavoriteColor() const;`
- L31 _protected prototype_ `EVisibility GetFavoriteVisibility() const;`
- L33 _protected prototype_ `FReply OnBrowseToAssetClicked() const;`
- L34 _protected prototype_ `EVisibility GetLocallyAvailableIconVisibility() const;`
- L36 _protected prototype_ `FText GetFontTooltipText() const;`
- L38 _protected member_ `TSharedPtr<STextBlock> LeftFontNameText;`
- L39 _protected member_ `TSharedPtr<STextBlock> RightFontNameText;`
- L40 _protected member_ `TWeakPtr<FString> FontItemWeak;`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Widgets/SText3DEditorFontSearchSettingsMenu.h` (Private)


#### class `SText3DEditorFontSearchSettingsMenu`  
`class SText3DEditorFontSearchSettingsMenu : public SCompoundWidget`  
_L11-47_
- inherits: `SCompoundWidget`
- desc: Widget to apply settings on font selector
- L14 _public function_ `SLATE_BEGIN_ARGS(SText3DEditorFontSearchSettingsMenu)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _protected prototype_ `void BindCommands();`
- L23 _protected prototype_ `bool ShowMonospacedToggle_IsChecked();`
- L24 _protected prototype_ `bool ShowBoldToggle_IsChecked();`
- L25 _protected prototype_ `bool ShowItalicToggle_IsChecked();`
- L27 _protected prototype_ `void ShowMonospacedToggle_Execute();`
- L28 _protected prototype_ `void ShowBoldToggle_Execute();`
- L29 _protected prototype_ `void ShowItalicToggle_Execute();`
- L31 _protected function_ `bool ShowMonospacedToggle_CanExecute() const`
- L36 _protected function_ `bool ShowBoldToggle_CanExecute() const`
- L41 _protected function_ `bool ShowItalicToggle_CanExecute() const`
- L46 _protected member_ `TSharedPtr<FUICommandList> CommandList;`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Widgets/SText3DEditorFontSelector.h` (Private)


#### class `SText3DEditorFontSelector`  
`class SText3DEditorFontSelector : public SCompoundWidget`  
_L18-83_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SText3DEditorFontSelector)`
- L25 _public prototype_ `virtual ~SText3DEditorFontSelector() override;`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L30 _protected prototype_ `void BindDelegates();`
- L31 _protected prototype_ `void UnbindDelegates() const;`
- L32 _protected prototype_ `void UpdateItems();`
- L33 _protected prototype_ `void ApplyItemFilters(TArray<FString>& OutFilteredFontItems) const;`
- L34 _protected prototype_ `void UpdateSeparatorsVisibility() const;`
- L36 _protected prototype_ `void OnProjectFontRegistered(const FString& InFontName);`
- L37 _protected prototype_ `void OnProjectFontUnregistered(const FString& InFontName);`
- L38 _protected prototype_ `void OnSystemFontRegistered(const FString& String);`
- L39 _protected prototype_ `void OnSystemFontUnregistered(const FString& String);`
- L40 _protected prototype_ `void OnSettingsChanged(UObject*, FPropertyChangedEvent&);`
- L42 _protected prototype_ `void OnFavoriteFontItemSelectionChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectInfo);`
- L43 _protected prototype_ `void OnProjectFontItemSelectionChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectInfo);`
- L44 _protected prototype_ `void OnSystemFontItemSelectionChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectInfo);`
- L46 _protected prototype_ `void OnFontItemSelectionChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectInfo);`
- L47 _protected prototype_ `void OnPropertyResetToDefault();`
- L48 _protected prototype_ `void UpdateSelectedItem();`
- L50 _protected prototype_ `FReply OnSearchFieldKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);`
- L51 _protected prototype_ `void OnFilterTextChanged(const FText& Text);`
- L53 _protected prototype_ `TSharedRef<ITableRow> GenerateMenuItemRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& InOwnerTable) const;`
- L54 _protected prototype_ `void OnMenuOpenChanged(bool bInOpen);`
- L56 _protected prototype_ `FText GetFavoriteFontLabel() const;`
- L57 _protected prototype_ `FText GetProjectFontLabel() const;`
- L58 _protected prototype_ `FText GetSystemFontLabel() const;`
- L60 _protected member_ `TSharedPtr<SListView<TSharedPtr<FString>>> FavoriteFontsListView;`
- L61 _protected member_ `TSharedPtr<SListView<TSharedPtr<FString>>> ProjectFontsListView;`
- L62 _protected member_ `TSharedPtr<SListView<TSharedPtr<FString>>> SystemFontsListView;`
- L64 _protected member_ `TArray<TSharedPtr<FString>> FavoriteFontsItems;`
- L65 _protected member_ `TArray<TSharedPtr<FString>> ProjectFontsItems;`
- L66 _protected member_ `TArray<TSharedPtr<FString>> SystemFontItems;`
- L68 _protected member_ `TSharedPtr<SBox> FavoriteSeparator;`
- L69 _protected member_ `TSharedPtr<SBox> ProjectSeparator;`
- L70 _protected member_ `TSharedPtr<SBox> SystemSeparator;`
- L72 _protected member_ `TSharedPtr<STextBlock> FavoriteLabel;`
- L73 _protected member_ `TSharedPtr<STextBlock> ProjectLabel;`
- L74 _protected member_ `TSharedPtr<STextBlock> SystemLabel;`
- L76 _protected member_ `TSharedPtr<SSearchBox> SearchBox;`
- L77 _protected member_ `TSharedPtr<SBox> FontContainer;`
- L78 _protected member_ `TSharedPtr<SComboButton> ComboButton;`
- L80 _protected member_ `TSharedPtr<IPropertyHandle> FontPropertyHandle;`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Widgets/SText3DEditorHorizontalAlignment.h` (Private)


#### class `SText3DEditorHorizontalAlignment`  
`class SText3DEditorHorizontalAlignment : public SCompoundWidget`  
_L16-38_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SText3DEditorHorizontalAlignment) : _OnHorizontalAlignmentChanged()`
- L22 _public prototype_ `SLATE_EVENT(FOnHorizontalAlignmentChanged, OnHorizontalAlignmentChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L28 _private prototype_ `TSharedRef<SButton> MakeAlignmentButton(EText3DHorizontalTextAlignment InAlignment, FName InBrushName, const FText& InTooltip);`
- L29 _private prototype_ `FSlateColor GetButtonColorAndOpacity(EText3DHorizontalTextAlignment InAlignment) const;`
- L30 _private prototype_ `FReply OnAlignmentButtonClicked(EText3DHorizontalTextAlignment InAlignment);`
- L31 _private prototype_ `EText3DHorizontalTextAlignment GetPropertyAlignment() const;`
- L32 _private prototype_ `void OnPropertyChanged();`
- L34 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L35 _private member_ `FOnHorizontalAlignmentChanged AlignmentChangedDelegate;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnHorizontalAlignmentChanged, EText3DHorizontalTextAlignment) class SText3DEditorHorizontalAlignment : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SText3DEditorHorizontalAlignment) : _OnHorizontalAlignmentChanged() {} SLATE_EVENT(FOnHorizontalAlignmentChanged, OnHorizontalAlignmentChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle); private: TSharedRef<SButton> MakeAlignmentButton(EText3DHorizontalTextAlignment InAlignment, FName InBrushName, const FText& InTooltip); FSlateColor GetButtonColorAndOpacity(EText3DHorizontalTextAlignment InAlignment) const; FReply OnAlignmentButtonClicked(EText3DHorizontalTextAlignment InAlignment); EText3DHorizontalTextAlignment GetPropertyAlignment() const; void OnPropertyChanged(); TSharedPtr<IPropertyHandle> PropertyHandle; FOnHorizontalAlignmentChanged AlignmentChangedDelegate; friend class UText3DEditorAccessHelper; };`

### `Plugins/VirtualProduction/Text3D/Source/Text3DEditor/Private/Widgets/SText3DEditorVerticalAlignment.h` (Private)


#### class `SText3DEditorVerticalAlignment`  
`class SText3DEditorVerticalAlignment : public SCompoundWidget`  
_L15-37_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SText3DEditorVerticalAlignment) : _OnVerticalAlignmentChanged()`
- L21 _public prototype_ `SLATE_EVENT(FOnVerticalAlignmentChanged, OnVerticalAlignmentChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L27 _private prototype_ `TSharedRef<SButton> MakeAlignmentButton(EText3DVerticalTextAlignment InAlignment, FName InBrushName, const FText& InTooltip);`
- L28 _private prototype_ `FSlateColor GetButtonColorAndOpacity(EText3DVerticalTextAlignment InAlignment) const;`
- L29 _private prototype_ `FReply OnAlignmentButtonClicked(EText3DVerticalTextAlignment InAlignment);`
- L30 _private prototype_ `EText3DVerticalTextAlignment GetPropertyAlignment() const;`
- L31 _private prototype_ `void OnPropertyChanged();`
- L33 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L34 _private member_ `FOnVerticalAlignmentChanged AlignmentChangedDelegate;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnVerticalAlignmentChanged, EText3DVerticalTextAlignment) class SText3DEditorVerticalAlignment : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SText3DEditorVerticalAlignment) : _OnVerticalAlignmentChanged() {} SLATE_EVENT(FOnVerticalAlignmentChanged, OnVerticalAlignmentChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle); private: TSharedRef<SButton> MakeAlignmentButton(EText3DVerticalTextAlignment InAlignment, FName InBrushName, const FText& InTooltip); FSlateColor GetButtonColorAndOpacity(EText3DVerticalTextAlignment InAlignment) const; FReply OnAlignmentButtonClicked(EText3DVerticalTextAlignment InAlignment); EText3DVerticalTextAlignment GetPropertyAlignment() const; void OnPropertyChanged(); TSharedPtr<IPropertyHandle> PropertyHandle; FOnVerticalAlignmentChanged AlignmentChangedDelegate; friend class UText3DEditorAccessHelper; };`
