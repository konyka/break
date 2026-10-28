# Editor / ConfigEditor

- module root: `Source/Editor/ConfigEditor`
- headers: 8; symbols: 88
- symbol kinds: class=10, enum=1, enumerator=3, function=4, macro=4, member=23, prototype=43
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Core, CoreUObject, PropertyEditor, Slate, SlateCore, SourceControl, TargetPlatform
- PrivateIncludePathModuleNames: 
- PublicIncludePathModuleNames: PropertyEditor

### `Source/Editor/ConfigEditor/Private/ConfigEditorModule.h` (Private)


#### class `FConfigEditorModule`  
`class FConfigEditorModule : public IConfigEditorModule`  
_L21-58_
- inherits: `IConfigEditorModule`
- desc: FConfigEditorModule
- L25 _public prototype_ `virtual void StartupModule() override;`
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L32 _public prototype_ `virtual void CreateHierarchyEditor(FProperty* EditProperty) override;`
- L33 _public prototype_ `virtual void AddExternalPropertyValueWidgetAndConfigPairing(const FString& ConfigFile, const TSharedPtr<SWidget> ValueWidget) override;`
- L34 _public prototype_ `virtual TSharedRef<SWidget> GetValueWidgetForConfigProperty(const FString& ConfigFile) override;`
- L44 _private prototype_ `TSharedRef<class SDockTab> SpawnConfigEditorTab(const FSpawnTabArgs& Args);` — Creates a new Config editor tab @return A spawned tab containing a config editor for a pre-defined property
- L51 _private member_ `TMap<FString, TSharedPtr<SWidget>> ExternalPropertyValueWidgetAndConfigPairings;` — We use this to maintain a reference to a property value widget, ie. a combobox for enum, a check box for bool... and provide these references when they are needed later in the details view construction This is important.
- L54 _private member_ `TSharedPtr<SConfigEditor> PropertyConfigEditor;` — Reference to the Config editor widget
- L57 _private member_ `TWeakFieldPtr<FProperty> CachedPropertyToView;` — Reference to the property the hierarchy is to view.

### `Source/Editor/ConfigEditor/Private/PropertyVisualization/ConfigPropertyCellPresenter.h` (Private)


#### class `FConfigPropertyCellPresenter`  
`class FConfigPropertyCellPresenter : public TSharedFromThis< FConfigPropertyCellPresenter >, public IPropertyTableCellPresenter`  
_L13-35_
- inherits: `TSharedFromThis<FConfigPropertyCellPresenter>,IPropertyTableCellPresenter`
- L17 _public prototype_ `FConfigPropertyCellPresenter(const TSharedPtr< IPropertyHandle > PropertyHandle);`
- L18 _public prototype_ `virtual ~FConfigPropertyCellPresenter() = default;`
- L22 _public prototype_ `virtual TSharedRef< class SWidget > ConstructDisplayWidget() override;` — Begin IPropertyTableCellPresenter interface
- L23 _public prototype_ `virtual bool RequiresDropDown() override;`
- L24 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeCellWidget() override;`
- L25 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeDropDownWidget() override;`
- L26 _public prototype_ `virtual TSharedRef< class SWidget > WidgetToFocusOnEdit() override;`
- L27 _public prototype_ `virtual bool HasReadOnlyEditMode() override;`
- L28 _public prototype_ `virtual FString GetValueAsString() override;`
- L29 _public prototype_ `virtual FText GetValueAsText() override;`
- L34 _protected member_ `TSharedPtr<SWidget> DisplayWidget;` — The cell content

### `Source/Editor/ConfigEditor/Private/SConfigEditor.h` (Private)


#### class `SConfigEditor`  
`class SConfigEditor : public SCompoundWidget`  
_L24-60_
- inherits: `SCompoundWidget`
- desc: SConfigEditor
- L27 _public function_ `SLATE_USER_ARGS(SConfigEditor)`
- L28 _public prototype_ `SLATE_END_ARGS()`
- L38 _private prototype_ `void HandleTargetPlatformChanged();` — Handle a change of target platform in the Config Editor UI
- L41 _private member_ `TSharedPtr<class STargetPlatformSelector> TargetPlatformSelection;` — Panel used to select an available target platform.
- L46 _private prototype_ `void CreateDisplayObjectForSelectedTargetPlatform();` — Create the displayable area object for the selected platform
- L50 _private member_ `TWeakObjectPtr<UConfigHierarchyPropertyView> PropHelper;` — This is an object we use to create a config hierarchy display for a property
- L53 _private member_ `TSharedPtr<SWidget> PropertyValueEditor;` — The display area for the config hierarchy editor.
- L56 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — The bulk of the display of this hierarchy.
- L59 _private member_ `TWeakFieldPtr<FProperty> EditProperty;` — Keep track of the property we are viewing.

#### Free symbols / members of external scopes

- L15 _macro_ `#define LOCTEXT_NAMESPACE "ConfigEditor"`

### `Source/Editor/ConfigEditor/Private/STargetPlatformSelector.h` (Private)


#### class `STargetPlatformSelector`  
`class STargetPlatformSelector : public SCompoundWidget`  
_L20-63_
- inherits: `SCompoundWidget`
- desc: STargetPlatformSelector
- L23 _public function_ `SLATE_BEGIN_ARGS(STargetPlatformSelector)`
- L24 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnTargetPlatformChanged) SLATE_END_ARGS()`
- L36 _public prototype_ `TSharedPtr<FString> GetSelectedTargetPlatform();` — Access to the selected target platform in this widget. @return - The selected platform from the target platform ComboBox.
- L43 _private prototype_ `void HandleTargetPlatformChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);` — Callback when the user has made a change to the target platform.
- L48 _private prototype_ `void CollateAvailableTargetPlatformEntries();` — Build a list of available target platforms.
- L53 _private member_ `TSharedPtr<FString> SelectedTargetPlatform;` — The currently selected target platform in this widget.
- L56 _private member_ `TSharedPtr<STextComboBox> AvailableTargetPlatformComboBox;` — The combo widget used to make a change to selected target platform.
- L59 _private member_ `TArray< TSharedPtr<FString> > TargetPlatformOptionsSource;` — The list of available target platforms for the combo widget.
- L62 _private member_ `FSimpleDelegate OnTargetPlatformChanged;` — Delegate called to let the listener know there has been a change to the target platform.

#### Free symbols / members of external scopes

- L15 _macro_ `#define LOCTEXT_NAMESPACE "ConfigEditor"`

### `Source/Editor/ConfigEditor/Public/ConfigPropertyHelper.h` (Public)


#### enum `EConfigFileSourceControlStatus`  
`enum EConfigFileSourceControlStatus : int`  
_L22-27_
- reflection: `UENUM()`
- L24 _public enumerator_ `CFSCS_Unknown UMETA(DisplayName=Unknown)`
- L25 _public enumerator_ `CFSCS_Writable UMETA(DisplayName = "Available to edit")`
- L26 _public enumerator_ `CFSCS_Locked UMETA(DisplayName = "File is locked")`

#### class `UPropertyConfigFileDisplayRow`  
`class UPropertyConfigFileDisplayRow : public UObject`  
_L30-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L35 _public prototype_ `void InitWithConfigAndProperty(const FString& InConfigFileName, FProperty* InEditProperty);`
- L39 _public member_ `FString ConfigFileName;` — `UPROPERTY(Transient, Category = Helper, VisibleAnywhere)`
- L41 _public member_ `FString NormalizedConfigFileName;`
- L42 _public member_ `TObjectPtr<UObject> TempConfigObject;`
- L45 _public member_ `TFieldPath<FProperty> ExternalProperty;` — `UPROPERTY(Transient, Category = Helper, EditAnywhere, meta=(EditCondition="bIsFileWritable"))`
- L48 _public member_ `bool bIsFileWritable;` — `UPROPERTY(Transient, Category = Helper, VisibleAnywhere)`

#### class `UConfigHierarchyPropertyView`  
`class UConfigHierarchyPropertyView : public UObject`  
_L53-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L59 _public member_ `TFieldPath<FProperty> EditProperty;` — `UPROPERTY(Transient, Category=Helper, EditAnywhere)`
- L62 _public member_ `TArray<TObjectPtr<UPropertyConfigFileDisplayRow>> ConfigFilePropertyObjects;` — `UPROPERTY(Transient, Category = Helper, EditAnywhere)`

### `Source/Editor/ConfigEditor/Public/IConfigEditorModule.h` (Public)


#### class `IConfigEditorModule`  
`class IConfigEditorModule : public IModuleInterface`  
_L12-32_
- inherits: `IModuleInterface`
- desc: IConfigEditorModule
- L18 _public prototype_ `virtual void CreateHierarchyEditor(FProperty* EditProperty) = 0;` — Creates a config hierarchy editor for the given property
- L23 _public prototype_ `virtual void AddExternalPropertyValueWidgetAndConfigPairing(const FString& ConfigFile, const TSharedPtr<SWidget> ValueWidget) = 0;` — Maintain a reference to a value widget used in the config editor for the current property.
- L31 _public prototype_ `virtual TSharedRef<SWidget> GetValueWidgetForConfigProperty(const FString& ConfigFile) = 0;` — Access a reference to a value widget used in the config editor for the current property. @return -	A widget which represents the config value for a specific property. This is a different widget based on the property type ie. a combobox for enum, a check box for bool...

### `Source/Editor/ConfigEditor/Public/PropertyVisualization/ConfigPropertyColumn.h` (Public)


#### class `FConfigPropertyCustomColumn`  
`class FConfigPropertyCustomColumn : public IPropertyTableCustomColumn`  
_L24-37_
- inherits: `IPropertyTableCustomColumn`
- desc: A property table custom column used to display source control condition of files.
- L27 _public function_ `FConfigPropertyCustomColumn()`
- L30 _public prototype_ `virtual bool Supports(const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities) const override;` — Begin IPropertyTableCustomColumn interface
- L31 _public prototype_ `virtual TSharedPtr< SWidget > CreateColumnLabel(const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style) const override;`
- L32 _public prototype_ `virtual TSharedPtr< IPropertyTableCellPresenter > CreateCellPresenter(const TSharedRef< IPropertyTableCell >& Cell, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style) const override;`
- L36 _public member_ `FProperty* EditProperty;` — The property type which can be displayed in this column

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CONFIGEDITOR_API`

### `Source/Editor/ConfigEditor/Public/PropertyVisualization/ConfigPropertyConfigFileStateColumn.h` (Public)


#### class `FConfigPropertyConfigFileStateCellPresenter`  
`class FConfigPropertyConfigFileStateCellPresenter : public TSharedFromThis< FConfigPropertyConfigFileStateCellPresenter >, public IPropertyTableCellPresenter`  
_L24-51_
- inherits: `TSharedFromThis<FConfigPropertyConfigFileStateCellPresenter>,IPropertyTableCellPresenter`
- L28 _public prototype_ `FConfigPropertyConfigFileStateCellPresenter(const TSharedPtr< IPropertyHandle > PropertyHandle);`
- L29 _public prototype_ `virtual ~FConfigPropertyConfigFileStateCellPresenter() = default;`
- L33 _public prototype_ `virtual TSharedRef< class SWidget > ConstructDisplayWidget() override;` — Begin IPropertyTableCellPresenter interface
- L34 _public prototype_ `virtual bool RequiresDropDown() override;`
- L35 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeCellWidget() override;`
- L36 _public prototype_ `virtual TSharedRef< class SWidget > ConstructEditModeDropDownWidget() override;`
- L37 _public prototype_ `virtual TSharedRef< class SWidget > WidgetToFocusOnEdit() override;`
- L38 _public prototype_ `virtual bool HasReadOnlyEditMode() override;`
- L39 _public prototype_ `virtual FString GetValueAsString() override;`
- L41 _public prototype_ `virtual FText GetValueAsText() override;`
- L50 _protected member_ `FText Text;` — The text we display - we just store this as we never need to *edit* properties in the stats viewer, only view them. Therefore we dont need to dynamically update this string.

#### class `FConfigPropertyConfigFileStateCustomColumn`  
`class FConfigPropertyConfigFileStateCustomColumn : public IPropertyTableCustomColumn`  
_L58-71_
- inherits: `IPropertyTableCustomColumn`
- desc: A property table custom column used to display source control condition of files.
- L61 _public function_ `FConfigPropertyConfigFileStateCustomColumn()`
- L64 _public prototype_ `virtual bool Supports(const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities) const override;` — Begin IPropertyTableCustomColumn interface
- L65 _public prototype_ `virtual TSharedPtr< SWidget > CreateColumnLabel(const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style) const override;`
- L66 _public prototype_ `virtual TSharedPtr< IPropertyTableCellPresenter > CreateCellPresenter(const TSharedRef< IPropertyTableCell >& Cell, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style) const override;`
- L70 _public member_ `FProperty* SupportedProperty;` — The property type which can be displayed in this column

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CONFIGEDITOR_API`
