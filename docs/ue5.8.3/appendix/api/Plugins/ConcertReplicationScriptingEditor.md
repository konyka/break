# Plugins / ConcertReplicationScriptingEditor

- module root: `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScriptingEditor`
- headers: 10; symbols: 108
- symbol kinds: class=8, delegate=4, externvar=1, function=7, member=29, namespace=22, prototype=37
- PrivateDependencyModuleNames: ConcertSharedSlate, ConcertTransport, InputCore, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: ConcertReplicationScripting, ConcertSyncCore, Core, CoreUObject, Engine, Slate, SlateCore

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScriptingEditor/Private/ConcertReplicationScriptingEditorModule.h` (Private)


#### class `UE::ConcertReplicationScriptingEditor::FConcertReplicationScriptingEditorModule`  
`class FConcertReplicationScriptingEditorModule : public IModuleInterface`  
_L10-23_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _private member_ `FClassRememberer SharedClassRememberer;` — Customizations use this cache so users do not constantly have to re-select the class in the drop-down menus.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertReplicationScriptingEditor` (scope `UE`)

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScriptingEditor/Private/Customization/ConcertPropertyContainerCustomization.h` (Private)


#### class `UE::ConcertReplicationScriptingEditor::FConcertPropertyContainerCustomization`  
`class FConcertPropertyContainerCustomization : public IPropertyTypeCustomization`  
_L16-58_
- inherits: `IPropertyTypeCustomization`
- desc: Shows a combo button that allows selecting a property from a class.
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(FClassRememberer* ClassRememberer);`
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L28 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L33 _private function_ `FConcertPropertyContainerCustomization(FClassRememberer& InClassRememberer) : ClassRememberer(InClassRememberer)`
- L38 _private member_ `FClassRememberer& ClassRememberer;` — Customizations use this cache so users do not constantly have to re-select the class in the drop-down menus.
- L41 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Handle to the property containing the FConcertPropertyChainWrapper struct.
- L44 _private member_ `TSharedPtr<SConcertPropertyChainCombo> PropertyComboBox;` — The UI displayed for the property.
- L50 _private member_ `TSet<FConcertPropertyChain> Properties;` — Dummy passed in to the SConcertPropertyChainCombo. Holds all the values from the different property sources.
- L51 _private member_ `bool bHasMultipleValues = false;`
- L53 _private prototype_ `void RefreshProperties();`
- L54 _private prototype_ `void RefreshPropertiesAndUpdateUI();`
- L56 _private prototype_ `void OnPropertySelectionChanged(const FConcertPropertyChain& Property, bool bIsSelected);`
- L57 _private prototype_ `void OnObjectTransacted(UObject* Object, const FTransactionObjectEvent& TransactionObjectEvent);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertReplicationScriptingEditor` (scope `UE`)

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScriptingEditor/Private/Customization/ConcertPropertyCustomization.h` (Private)


#### class `UE::ConcertReplicationScriptingEditor::FConcertPropertyCustomization`  
`class FConcertPropertyCustomization : public IPropertyTypeCustomization`  
_L16-58_
- inherits: `IPropertyTypeCustomization`
- desc: Shows a combo button that allows selecting a property from a class.
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(FClassRememberer* ClassRememberer);`
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L28 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L33 _private function_ `FConcertPropertyCustomization(FClassRememberer& InClassRememberer) : ClassRememberer(InClassRememberer)`
- L38 _private member_ `FClassRememberer& ClassRememberer;` — Customizations use this cache so users do not constantly have to re-select the class in the drop-down menus.
- L41 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Handle to the property containing the FConcertPropertyChainWrapper struct.
- L44 _private member_ `TSharedPtr<SConcertPropertyChainCombo> PropertyComboBox;` — The UI displayed for the property.
- L50 _private member_ `TSet<FConcertPropertyChain> Properties;` — Dummy passed in to the SConcertPropertyChainCombo. Holds all the values from the different property sources.
- L51 _private member_ `bool bHasMultipleValues = false;`
- L53 _private prototype_ `void RefreshProperties();`
- L54 _private prototype_ `void RefreshPropertiesAndUpdateUI();`
- L56 _private prototype_ `void OnPropertySelectionChanged(const FConcertPropertyChain& Property, bool bIsSelected);`
- L57 _private prototype_ `void OnObjectTransacted(UObject* Object, const FTransactionObjectEvent& TransactionObjectEvent);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertReplicationScriptingEditor` (scope `UE`)

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScriptingEditor/Private/ReplicationScriptingStyle.h` (Private)


#### class `UE::ConcertReplicationScriptingEditor::FReplicationScriptingStyle`  
`class FReplicationScriptingStyle`  
_L10-23_
- L14 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static TSharedPtr<ISlateStyle> Get();`
- L18 _public prototype_ `static FName GetStyleSetName();`
- L22 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertReplicationScriptingEditor` (scope `UE`)

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScriptingEditor/Private/Util/ClassRememberer.h` (Private)


#### class `UE::ConcertReplicationScriptingEditor::FClassRememberer`  
`class FClassRememberer : public FNoncopyable`  
_L15-34_
- inherits: `FNoncopyable`
- desc: Remembers which classes were used based per customized property so users do not constantly have to re-select it in the drop-down menus.
- L20 _public prototype_ `const UClass* GetLastUsedContextClassFor(IPropertyHandle& Property) const;` — Gets the class to use for searching properties in the FConcertPropertyChainWrapper or FConcertPropertyChainWrapperContainer.
- L23 _public prototype_ `void OnUseClass(IPropertyHandle& Property, const UClass* Class);` — Caches a class for the property.
- L28 _private member_ `TWeakObjectPtr<const UClass> LastSelectedClass;` — Keeps track of the last class that was used for searching properties in SConcertPropertyChainCombo.
- L33 _private member_ `TMap<FString, TWeakObjectPtr<const UClass>> PropertyToLastUsedClass;` — Maps every property path to the last used class. This why when a user works with multiple properties, each one will remember the last used class for convenience. This leaks memory but a user must edit a lot of properties to really be noticeable... should be ok.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertReplicationScriptingEditor` (scope `UE`)

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScriptingEditor/Private/Widgets/PropertyChainDelegates.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertReplicationScriptingEditor` (scope `UE`)
- L12 _delegate_ `DECLARE_DELEGATE(FOnPressed);`
- L12 _prototype_ `DECLARE_DELEGATE(FOnPressed);` (scope `UE::ConcertReplicationScriptingEditor`)
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnClassChanged, const UClass* Class);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FOnClassChanged, const UClass* Class);` (scope `UE::ConcertReplicationScriptingEditor`)
- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSelectedPropertiesChanged, const FConcertPropertyChain& Property, bool bIsSelected);`
- L15 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSelectedPropertiesChanged, const FConcertPropertyChain& Property, bool bIsSelected);` (scope `UE::ConcertReplicationScriptingEditor`)

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScriptingEditor/Private/Widgets/PropertySelectionColumn.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertReplicationScriptingEditor` (scope `UE`)
- L10 _externvar_ `extern const FName PropertySelectionCheckboxColumnId;` (scope `UE::ConcertReplicationScriptingEditor`)
- L12 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSelectProperty, const FConcertPropertyChain& PropertyChain, bool bIsSelected);`
- L12 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSelectProperty, const FConcertPropertyChain& PropertyChain, bool bIsSelected);` (scope `UE::ConcertReplicationScriptingEditor`)
- L20 _prototype_ `ConcertSharedSlate::FPropertyColumnEntry MakePropertySelectionCheckboxColumn( const TSet<FConcertPropertyChain>& SelectedProperties, FOnSelectProperty OnSelectPropertyDelegate, bool bIsEditable, int32 SortPriority = 0 );` (scope `UE::ConcertReplicationScriptingEditor`) — Creates a checkbox column. @param SelectedProperties The checkbox is checked if the path is in SelectedProperties. @param OnSelectPropertyDelegate Executed when a checkbox is checked or unchecked.

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScriptingEditor/Private/Widgets/SConcertPropertyChainChip.h` (Private)


#### class `UE::ConcertReplicationScriptingEditor::SConcertPropertyChainChip`  
`class SConcertPropertyChainChip : public SCompoundWidget`  
_L14-34_
- inherits: `SCompoundWidget`
- desc: Displays a FConcertPropertyChain
- L18 _public function_ `SLATE_BEGIN_ARGS(SConcertPropertyChainChip)`
- L21 _public prototype_ `SLATE_ATTRIBUTE(FConcertPropertyChain, DisplayedProperty) SLATE_ARGUMENT(bool, ShowClearButton) SLATE_EVENT(FOnPressed, OnClearPressed) SLATE_EVENT(FOnPressed, OnEditPressed) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The property to display

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertReplicationScriptingEditor` (scope `UE`)

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScriptingEditor/Private/Widgets/SConcertPropertyChainCombo.h` (Private)


#### class `UE::ConcertReplicationScriptingEditor::SConcertPropertyChainCombo`  
`class SConcertPropertyChainCombo : public SCompoundWidget`  
_L21-87_
- inherits: `SCompoundWidget`
- desc: A combo button that displays a list of properties as content and as menu opens a property tree view for editing the list of properties.
- L25 _public function_ `SLATE_BEGIN_ARGS(SConcertPropertyChainCombo) : _InitialClassSelection(nullptr)`
- L34 _public prototype_ `SLATE_ARGUMENT(const TSet<FConcertPropertyChain>*, ContainedProperties) SLATE_ARGUMENT(bool, IsEditable) SLATE_ATTRIBUTE(bool, HasMultipleValues) SLATE_ARGUMENT(const UClass*, InitialClassSelection) SLATE_EVENT(FOnClassChanged, OnClassChanged) SLATE_EVENT(FOnSelectedPropertiesChanged, OnPropertySelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The properties that are supposed to be displayed inside of the button. This must always contain at least one property. If there are "no" properties, this should contain the empty, default constructed FConcertPropertyChain. This requirement is needed so the button shows the "Empty" widget.
- L53 _public prototype_ `void RefreshPropertyContent();` — Regenerates the button's content.
- L58 _private member_ `const UClass* LastClassUsed = nullptr;` — Class set by the last menu this widget had used.
- L60 _private member_ `const TSet<FConcertPropertyChain>* ContainedProperties;` — The properties that are supposed to be displayed inside of the button
- L63 _private member_ `bool bIsEditable;` — Whether the UI should allow editing.
- L66 _private member_ `TSharedPtr<SComboButton> ComboButton;` — The combo button being displayed.
- L68 _private member_ `TWeakPtr<SConcertPropertyChainPicker> WeakButtonMenu;` — Used to scroll into view when clicking an item in the button content.
- L71 _private member_ `TArray<TSharedPtr<FConcertPropertyChain>> DisplayedProperties;` — The properties displayed in PropertyListView.
- L73 _private member_ `TSharedPtr<SListView<TSharedPtr<FConcertPropertyChain>>> PropertyListView;` — The content of this button
- L76 _private member_ `TAttribute<bool> HasMultipleValuesAttribute;` — If true, then ContainedProperties contains the accumulated values of multiple sources. If false, all sources have the same value.
- L79 _private member_ `FOnClassChanged OnClassChangedDelegate;` — Triggered when the class changes
- L81 _private member_ `FOnSelectedPropertiesChanged OnPropertySelectionChangedDelegate;` — Called when the selection of a property changes.
- L84 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();` — Generates the combo button menu content.
- L86 _private prototype_ `TSharedRef<ITableRow> MakePropertyChainRow(TSharedPtr<FConcertPropertyChain> Item, const TSharedRef<STableViewBase>& OwnerTable);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertReplicationScriptingEditor` (scope `UE`)

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScriptingEditor/Private/Widgets/SConcertPropertyChainPicker.h` (Private)


#### class `UE::ConcertReplicationScriptingEditor::SConcertPropertyChainPicker`  
`class SConcertPropertyChainPicker : public SCompoundWidget`  
_L20-67_
- inherits: `SCompoundWidget`
- desc: Menu that has a class picker and tree view of properties in the class.
- L24 _public function_ `SLATE_BEGIN_ARGS(SConcertPropertyChainPicker) : _InitialClassSelection(nullptr) , _ContainedProperties(nullptr)`
- L29 _public prototype_ `SLATE_ARGUMENT(const UClass*, InitialClassSelection) SLATE_ARGUMENT(bool, IsEditable) SLATE_ARGUMENT(const TSet<FConcertPropertyChain>*, ContainedProperties) SLATE_EVENT(FOnClassChanged, OnClassChanged) SLATE_EVENT(FOnSelectedPropertiesChanged, OnSelectedPropertiesChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The initial class to search in
- L44 _public prototype_ `void RequestScrollIntoView(const FConcertPropertyChain& PropertyChain);`
- L49 _private member_ `const UClass* SelectedClass = nullptr;` — The class for which to display the hierarchy
- L51 _private member_ `const TSet<FConcertPropertyChain>* ContainedProperties;` — The properties that are supposed to be displayed inside of the button
- L54 _private member_ `TSharedPtr<ConcertSharedSlate::IPropertyTreeView> TreeView;` — Displays the properties
- L57 _private member_ `FOnClassChanged OnClassChangedDelegate;` — Triggered when the class changes
- L59 _private member_ `FOnSelectedPropertiesChanged OnSelectedPropertiesChangedDelegate;` — Called when the user's property selection changes
- L61 _private prototype_ `TSharedRef<SWidget> CreateClassPickerSection();`
- L62 _private prototype_ `TSharedRef<SWidget> CreatePropertyTreeView(const FArguments& InArgs);`
- L64 _private prototype_ `void OnSetClass(const UClass* Class);`
- L65 _private prototype_ `void RefreshPropertiesDisplayedInTree();`
- L66 _private prototype_ `void OnPropertySelected(const FConcertPropertyChain& ConcertPropertyChain, bool bIsSelected);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSharedSlate` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertReplicationScriptingEditor` (scope `UE`)
