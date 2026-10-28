# Plugins / DisplayClusterMoviePipelineEditor

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipelineEditor`
- headers: 7; symbols: 72
- symbol kinds: class=6, delegate=1, enum=1, enumerator=2, function=6, macro=1, member=19, prototype=36
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, AssetTools, BlueprintGraph, Core, CoreUObject, DesktopPlatform, DisplayCluster, DisplayClusterConfiguration, DisplayClusterMoviePipeline, EditorFramework, EditorSubsystem, EditorWidgets, Engine, GraphEditor, ImageWrapper, InputCore, Kismet, KismetCompiler, MainFrame, MediaAssets, MessageLog, PinnedCommandList, Projects, PropertyEditor, Serialization, Settings, Slate, SlateCore, SubobjectDataInterface, SubobjectEditor, ToolMenus, ToolWidgets, UnrealEd

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipelineEditor/Private/Details/DisplayClusterMoviePipelineEditorBaseTypeCustomization.h` (Private)


#### class `FDisplayClusterMoviePipelineEditorBaseTypeCustomization`  
`class FDisplayClusterMoviePipelineEditorBaseTypeCustomization : public IPropertyTypeCustomization`  
_L13-84_
- inherits: `IPropertyTypeCustomization`
- desc: A base class for type customization in DisplayClusterMoviePipelineEditor. Contains support for common custom metadata specifiers.
- L21 _public member_ `static const FName NoHeaderMetadataKey;` — Metadata specifier used to indicate that a type should not have a header to encapsulate its properties in a details panel; similar to ShowOnlyInnerProperties, but forces all child properties to be within the category the parent type belongs to, and is applied at any depth within a details panel.
- L24 _public member_ `static const FName HideChildrenMetadataKey;` — Metadata specifier used to indicate that a type should not display any of its child properties in a details panel.
- L27 _public member_ `static const FName SubstitutionsMetadataKey;` — Metadata specifier used specify substitutions to make to the display text of any of this type's child properties.
- L30 _public member_ `static const FName DefaultSubstitutionsMetadataKey;` — Metadata specifier used specify the default substitutions to make to the display text of any of this type's child properties when no substitutions are specified.
- L33 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L39 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L40 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L45 _protected prototype_ `TSharedPtr<IPropertyHandle> GetChildHandleChecked(const TSharedRef<IPropertyHandle>& InPropertyHandle, const FName& ChildPropertyName) const;` — Gets the child property handle from the specified property handle, and performs checks to ensure the child handle is valid.
- L48 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils);` — Initializes the type customization just before specifying the type's header, giving the customization the opportunity to initialize anything before generating the customized UI.
- L51 _protected prototype_ `virtual void SetHeader(const TSharedRef<IPropertyHandle>& InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils);` — Sets the header of the type customization. By default, sets the header to the property's default name and value widget. Override to customize the type's header.
- L54 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);` — Sets the children of the type customization. By default, adds all of the type's children to the customized layout. Override to customize the type's children.
- L57 _protected prototype_ `void AddAllChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder);` — Adds all of the type's children to the customization's child builder.
- L60 _protected prototype_ `void FillSubstitutionMap(const TSharedRef<IPropertyHandle>& InPropertyHandle);` — Fills the substitutiom map to use for any text subsitutions using the metadata of the specified property handle
- L63 _protected prototype_ `void ParseSubstitutions(FFormatNamedArguments& OutSubstitutionsMap, const FString& InSubstitutionsStr) const;` — Parses the specified comma-deliminated substitution string into a list of key-value substitution pairs
- L64 _protected prototype_ `FText ApplySubstitutions(const FText& InText) const;`
- L67 _protected prototype_ `virtual bool ShouldShowHeader(const TSharedRef<IPropertyHandle>& InPropertyHandle) const;` — Gets whether the type should display a header when displayed in a details panel. By default, check's the property's metadata for the NoHeader or ShowOnlyInnerProperties specifier.
- L70 _protected prototype_ `virtual bool ShouldShowChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle) const;` — Gets whether the type should display its children when displayed in a details panel. By default, check's the property's metadata for the HideChildren specifier.
- L73 _protected prototype_ `const FString* FindMetaData(TSharedPtr<IPropertyHandle> PropertyHandle, const FName& Key) const;` — Searches the specified property's instanced and default metadata maps for metadata using the specified key
- L77 _protected member_ `TWeakPtr<IPropertyHandle> RootPropertyHandle;` — A root property handle used by this type customization
- L80 _protected member_ `TWeakPtr<IPropertyUtilities> PropertyUtilities;` — A weak reference to the property utilities used by this type customization
- L83 _protected member_ `FFormatNamedArguments SubstitutionsMap;` — A list of substitutions that will be applied to the display text of each child property of the customized type

#### Free symbols / members of external scopes

- L8 _macro_ `#define GET_CHILD_HANDLE(ParentType, ChildName) GetChildHandleChecked(InPropertyHandle, GET_MEMBER_NAME_CHECKED(ParentType, ChildName))`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipelineEditor/Private/Details/DisplayClusterMoviePipelineEditorNodeSelection.h` (Private)


#### class `FDisplayClusterMoviePipelineEditorNodeSelection`  
`class FDisplayClusterMoviePipelineEditorNodeSelection : public TSharedFromThis<FDisplayClusterMoviePipelineEditorNodeSelection>`  
_L17-93_
- inherits: `TSharedFromThis<FDisplayClusterMoviePipelineEditorNodeSelection>`
- desc: Helper class used to construct and manage a custom array property widget that displays for each element a dropdown containing a list of the display cluster's cluster nodes or viewports to select from.
- L21 _public member_ `static const FName NAME_ElementToolTip;` — Custom "ElementToolTip" metadata specifier that can be used to specify the tooltip to apply to each element of the displayed array
- L30 _public prototype_ `FDisplayClusterMoviePipelineEditorNodeSelection(EOperationMode InMode, const TSharedPtr<IPropertyHandle>& InDCRAPropertyHandle, const TSharedPtr<IPropertyHandle>& InSelectedOptionsHandle);`
- L32 _public function_ `~FDisplayClusterMoviePipelineEditorNodeSelection()`
- L39 _public prototype_ `UDisplayClusterConfigurationData* GetConfigData() const;` — Gets the cluster configuration data object of the root actor being edited by the current details panel
- L42 _public prototype_ `void CreateArrayBuilder(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder);` — Creates the child array builder that will be used to construct the cluster item selection array elements for the details panel
- L45 _public function_ `FDisplayClusterMoviePipelineEditorNodeSelection& IsEnabled(const TAttribute<bool>& InIsEnabled)` — Sets the IsEnabled attribute to use on the array property handle
- L52 _public prototype_ `static EOperationMode GetOperationModeFromProperty(FProperty* Property);` — Inspects the specified property's metadata to determine if the node selection array should show cluster nodes or viewports in its dropdown lists
- L54 _public prototype_ `void ResetOptionsList();`
- L58 _protected prototype_ `void GenerateSelectionWidget(TSharedRef<IPropertyHandle> PropertyHandle, int32 ArrayIndex, IDetailChildrenBuilder& ChildrenBuilder);` — Generates a widget to display the currently selected cluster item for the specified element in the array widget and adds it to the details panel
- L61 _protected prototype_ `void ResetOptions();` — Resets the list of cluster items to display in the dropdown lists for each element of the array widget
- L64 _protected prototype_ `TSharedRef<SWidget> MakeOptionComboWidget(TSharedPtr<FString> InItem);` — Constructs the text widget to display in the dropdown menu for the specified item
- L67 _protected prototype_ `void OnOptionSelected(TSharedPtr<FString> InValue, ESelectInfo::Type SelectInfo, TSharedRef<IPropertyHandle> InPropertyHandle);` — Raised when an item within the dropdown menu is selected
- L70 _protected prototype_ `FText GetSelectedOptionText(TSharedRef<IPropertyHandle> InPropertyHandle) const;` — Gets the display text for the currently selected item of the element in the array widget
- L74 _private member_ `TAttribute<bool> IsEnabledAttr;` — A custom attribute to apply to the array widget to determine if it is enabled or not
- L77 _private member_ `TSharedPtr<SDisplayClusterMoviePipelineEditorSearchableComboBox> OptionsComboBox;` — The combo box widget to display for each element in the array widget
- L80 _private member_ `TArray<TSharedPtr<FString>> Options;` — The list of options to display in each combo box's dropdown menu
- L83 _private member_ `TSharedPtr<IPropertyHandle> DCRAPropertyHandle;` — A reference to the current display cluster root actor property handle that is being edited by the details panel
- L86 _private member_ `TSharedPtr<IPropertyHandle> SelectedOptionsHandle;` — A reference to the string list property handle that is being edited by the details panel
- L89 _private member_ `EOperationMode OperationMode = ClusterNodes;` — The operation mode which indicates whether to display cluster nodes or viewports in each element's combo box
- L92 _private member_ `bool bResetOptionsListFunctionInPerformed= false;` — Protect frunction ResetOptionsList() from recursion

#### enum `FDisplayClusterMoviePipelineEditorNodeSelection::EOperationMode`  
`enum EOperationMode`  
_L24-28_
- desc: Flag to indicate which cluster item is displayed in the dropdown menus of the elements of the array widget
- L26 _public enumerator_ `Viewports`
- L27 _public enumerator_ `ClusterNodes`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipelineEditor/Private/Details/DisplayClusterMoviePipelineEditorSettingsCustomization.h` (Private)


#### class `FDisplayClusterMoviePipelineEditorSettingsCustomization`  
`class FDisplayClusterMoviePipelineEditorSettingsCustomization final : public FDisplayClusterMoviePipelineEditorBaseTypeCustomization`  
_L9-35_
- inherits: `FDisplayClusterMoviePipelineEditorBaseTypeCustomization`
- desc: Type customization for the FDisplayClusterMoviePipelineConfiguration type, to customize the AllowedViewportNamesList list property
- L13 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L18 _public function_ `virtual ~FDisplayClusterMoviePipelineEditorSettingsCustomization() override`
- L25 _protected prototype_ `virtual void Initialize(const TSharedRef<IPropertyHandle>& InPropertyHandle, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L26 _protected prototype_ `virtual void SetHeader(const TSharedRef<IPropertyHandle>& InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L27 _protected prototype_ `virtual void SetChildren(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L30 _protected prototype_ `void OnRootActorReferencedPropertyValueChanged(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L31 _protected prototype_ `void OnAllowedViewportNamesListHandleChanged();`
- L34 _private member_ `TSharedPtr<FDisplayClusterMoviePipelineEditorNodeSelection> NodeSelection;` — The helper object used to generate the custom array widget to display in place of a string list for the AllowedViewportNamesList property

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipelineEditor/Private/DisplayClusterMoviePipelineEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMoviePipelineEditor, Log, All);` — Plugin-wide log categories
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMoviePipelineEditor, Log, All);` — Plugin-wide log categories

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipelineEditor/Private/DisplayClusterMoviePipelineEditorModule.h` (Private)


#### class `FDisplayClusterMoviePipelineEditorModule`  
`class FDisplayClusterMoviePipelineEditorModule : public IDisplayClusterMoviePipelineEditor`  
_L10-25_
- inherits: `IDisplayClusterMoviePipelineEditor`
- desc: Display Cluster Movie Pipeline Editor module
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private prototype_ `void RegisterCustomLayouts();`
- L20 _private prototype_ `void UnregisterCustomLayouts();`
- L23 _private member_ `TArray<FName> RegisteredClassLayoutNames;`
- L24 _private member_ `TArray<FName> RegisteredPropertyLayoutNames;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipelineEditor/Private/Widgets/SDisplayClusterMoviePipelineEditorSearchableComboBox.h` (Private)


#### class `SDisplayClusterMoviePipelineEditorSearchableComboBox`  
`class SDisplayClusterMoviePipelineEditorSearchableComboBox : public SSearchableComboBox`  
_L12-93_
- inherits: `SSearchableComboBox`
- desc: A searchable text combo box Mostly copied from SearchableComboBox, but with extension for dynamically update the Option source list
- L17 _public function_ `SLATE_BEGIN_ARGS(SDisplayClusterMoviePipelineEditorSearchableComboBox) : _Content() , _ComboBoxStyle(&FAppStyle::Get().GetWidgetStyle<FComboBoxStyle>("ComboBox")) , _ButtonStyle(nullptr) , _ItemStyle(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("ComboBox.Row")) , _ContentPadding(_ComboBoxStyle->ContentPadding) , _ForegroundColor(FSlateColor::UseStyle()) , _OptionsSource() , _OnSelectionChanged() , _OnGenerateWidget() , _InitiallySelectedItem(nullptr) , _Method() , _MaxListHeight(450.0f) , _HasDownArrow(true) , _SearchVisibility()`
- L35 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_STYLE_ARGUMENT(FComboBoxStyle, ComboBoxStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_STYLE_ARGUMENT(FTableRowStyle, ItemStyle) SLATE_ATTRIBUTE(FMargin, ContentPadding) SLATE_ATTRIBUTE(FSlateColor, ForegroundColor) SLATE_ARGUMENT(const TArray< TSharedPtr<FString> >*, OptionsSource) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnGenerateWidget, OnGenerateWidget) SLATE_EVENT(FOnComboBoxOpening, OnComboBoxOpening) SLATE_ARGUMENT(TSharedPtr<SScrollBar>, CustomScrollbar) SLATE_ARGUMENT(TSharedPtr<FString>, InitiallySelectedItem) SLATE_ARGUMENT(TOptional<EPopupMethod>, Method) SLATE_ARGUMENT(float, MaxListHeight) SLATE_ARGUMENT(bool, HasDownArrow) SLATE_ATTRIBUTE(EVisibility, SearchVisibility) SLATE_END_ARGS()` — Slot for this button's content (optional)
- L88 _public prototype_ `void ResetOptionsSource(const TArray<TSharedPtr<FString>>* NewOptionsSource = nullptr);` — Reset the source in the Combo Box List. The options source is intelligently refreshed based on if the Source is the same or not. @param NewOptionsSource The options data to use. If null the original will be used.
- L92 _protected member_ `const TArray< TSharedPtr<FString> >* DisplayClusterOptionsSource;` — Local version of parent class private variable `OptionsSource`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMoviePipelineEditor/Public/IDisplayClusterMoviePipelineEditor.h` (Public)


#### class `IDisplayClusterMoviePipelineEditor`  
`class IDisplayClusterMoviePipelineEditor : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- desc: Display Cluster editor module interface
- L16 _public prototype_ `virtual ~IDisplayClusterMoviePipelineEditor() = default;`
