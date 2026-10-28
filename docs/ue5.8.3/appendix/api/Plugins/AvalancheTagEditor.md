# Plugins / AvalancheTagEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor`
- headers: 22; symbols: 161
- symbol kinds: class=22, function=17, member=27, prototype=94, struct=1
- PrivateDependencyModuleNames: AssetDefinition, AvalancheTag, Core, CoreUObject, Engine, InputCore, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/AssetDefinition_AvaTagCollection.h` (Private)


#### class `UAssetDefinition_AvaTagCollection`  
`class UAssetDefinition_AvaTagCollection : public UAssetDefinitionDefault`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/AvaTagCollectionFactory.h` (Private)


#### class `UAvaTagCollectionFactory`  
`class UAvaTagCollectionFactory : public UFactory`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L13 _private prototype_ `UAvaTagCollectionFactory();`
- L16 _private prototype_ `virtual uint32 GetMenuCategories() const override;`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/AvaTagEditorModule.h` (Private)


#### class `FAvalancheTagEditorModule`  
`class FAvalancheTagEditorModule : public IModuleInterface`  
_L9-24_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _public prototype_ `void RegisterCustomizations();`
- L19 _public prototype_ `void UnregisterCustomizations();`
- L21 _public member_ `TArray<FName> CustomizedTypes;`
- L23 _public member_ `TArray<FName> CustomizedClasses;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/AvaTagEditorStyle.h` (Private)


#### class `FAvaTagEditorStyle`  
`class FAvaTagEditorStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaTagEditorStyle& Get()`
- L16 _public prototype_ `FAvaTagEditorStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/AvaTagAliasCustomization.h` (Private)


#### class `FAvaTagAliasCustomization`  
`class FAvaTagAliasCustomization : public IPropertyTypeCustomization`  
_L10-23_
- inherits: `IPropertyTypeCustomization`
- L13 _public prototype_ `FAvaTagAliasCustomization();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L17 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`
- L20 _public member_ `TSharedRef<FAvaTagElementHelper> TagElementHelper;`
- L22 _public member_ `TSharedRef<IAvaTagHandleCustomizer> TagCustomizer;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/AvaTagCollectionCustomization.h` (Private)


#### class `FAvaTagCollectionCustomization`  
`class FAvaTagCollectionCustomization : public IDetailCustomization`  
_L10-18_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L17 _public prototype_ `TSharedRef<SWidget> BuildHeaderContent(const TSharedRef<IPropertyHandle>& InPropertyHandle);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/AvaTagHandleCustomization.h` (Private)


#### class `FAvaTagHandleCustomization`  
`class FAvaTagHandleCustomization : public IPropertyTypeCustomization`  
_L9-24_
- inherits: `IPropertyTypeCustomization`
- L12 _public function_ `explicit FAvaTagHandleCustomization(TSharedRef<IAvaTagHandleCustomizer>&& InTagCustomizer) : TagCustomizer(MoveTemp(InTagCustomizer))`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L19 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`
- L23 _private member_ `TSharedRef<IAvaTagHandleCustomizer> TagCustomizer;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/Builders/AvaTagAliasMapBuilder.h` (Private)


#### class `FAvaTagAliasMapBuilder`  
`class FAvaTagAliasMapBuilder : public FAvaTagMapBuilder`  
_L8-19_
- inherits: `FAvaTagMapBuilder`
- desc: Map builder for the Alias Map
- L11 _public function_ `explicit FAvaTagAliasMapBuilder(const TSharedRef<IPropertyHandle>& InMapProperty) : FAvaTagMapBuilder(InMapProperty)`
- L17 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& InChildrenBuilder) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/Builders/AvaTagElementHelper.h` (Private)


#### class `FAvaTagElementHelper`  
`class FAvaTagElementHelper : public TSharedFromThis<FAvaTagElementHelper>`  
_L11-21_
- inherits: `TSharedFromThis<FAvaTagElementHelper>`
- desc: Helper class to re-use same functionality across Node Builders and Customizations
- L14 _public prototype_ `TSharedRef<SWidget> CreatePropertyButtonsWidget(TSharedPtr<IPropertyHandle> InElementHandle);`
- L16 _public prototype_ `bool CanDeleteItem(const TSharedPtr<IPropertyHandle>& InElementHandle) const;`
- L18 _public prototype_ `void DeleteItem(TSharedPtr<IPropertyHandle> InElementHandle);`
- L20 _public prototype_ `void SearchForReferences(TSharedPtr<IPropertyHandle> InTagIdHandle);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/Builders/AvaTagMapBuilder.h` (Private)


#### class `FAvaTagMapBuilder`  
`class FAvaTagMapBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FAvaTagMapBuilder>`  
_L12-39_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FAvaTagMapBuilder>`
- desc: Base class to Build Map properties
- L15 _public prototype_ `FAvaTagMapBuilder(const TSharedRef<IPropertyHandle>& InMapProperty);`
- L20 _public prototype_ `virtual FName GetName() const override;`
- L21 _public function_ `virtual bool InitiallyCollapsed() const override`
- L22 _public function_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& InNodeRow) override`
- L23 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override;`
- L24 _public prototype_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRebuildChildren) override;`
- L28 _protected prototype_ `void ForEachChildProperty(TFunctionRef<void(const TSharedRef<IPropertyHandle>&)> InCallable);`
- L30 _protected prototype_ `void OnNumChildrenChanged();`
- L32 _protected member_ `TSharedRef<IPropertyHandle> BaseProperty;`
- L34 _protected member_ `TSharedRef<IPropertyHandleMap> MapProperty;`
- L36 _protected member_ `FDelegateHandle OnNumElementsChangedHandle;`
- L38 _protected member_ `FSimpleDelegate OnRebuildChildren;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/Builders/AvaTagTagMapBuilder.h` (Private)


#### class `FAvaTagTagMapBuilder`  
`class FAvaTagTagMapBuilder : public FAvaTagMapBuilder`  
_L10-21_
- inherits: `FAvaTagMapBuilder`
- desc: Map builder for the Tag Map
- L13 _public prototype_ `explicit FAvaTagTagMapBuilder(const TSharedRef<IPropertyHandle>& InMapProperty);`
- L16 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& InChildrenBuilder) override;`
- L20 _private member_ `TSharedRef<FAvaTagElementHelper> TagElementHelper;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/Menu/AvaTagCollectionMenuContext.h` (Private)


#### class `UAvaTagCollectionMenuContext`  
`class UAvaTagCollectionMenuContext : public UObject`  
_L12-18_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _public member_ `TWeakPtr<IPropertyHandle> TagCollectionHandleWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/Menu/AvaTagCollectionPickerContextMenu.h` (Private)


#### class `FAvaTagCollectionPickerContextMenu`  
`class FAvaTagCollectionPickerContextMenu : public TSharedFromThis<FAvaTagCollectionPickerContextMenu>`  
_L12-31_
- inherits: `TSharedFromThis<FAvaTagCollectionPickerContextMenu>`
- L17 _public function_ `explicit FAvaTagCollectionPickerContextMenu(FPrivateToken)`
- L19 _public prototype_ `static FAvaTagCollectionPickerContextMenu& Get();`
- L21 _public prototype_ `TSharedRef<SWidget> GenerateContextMenuWidget(const TSharedPtr<IPropertyHandle>& InTagCollectionHandle);`
- L24 _private prototype_ `void PopulateContextMenu(UToolMenu* InToolMenu);`
- L26 _private prototype_ `bool TryGetAsset(const TWeakPtr<IPropertyHandle>& InTagCollectionHandleWeak, FAssetData& OutAssetData) const;`
- L28 _private prototype_ `void EditAsset(TWeakPtr<IPropertyHandle> InTagCollectionHandleWeak);`
- L30 _private prototype_ `void FindInContentBrowser(TWeakPtr<IPropertyHandle> InTagCollectionHandleWeak);`

#### struct `FAvaTagCollectionPickerContextMenu::FPrivateToken`  
`struct FPrivateToken`  
_L14-14_
- L14 _public prototype_ `struct FPrivateToken`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/SAvaTagCollectionPicker.h` (Private)


#### class `SAvaTagCollectionPicker`  
`class SAvaTagCollectionPicker : public SCompoundWidget`  
_L14-47_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SAvaTagCollectionPicker)`
- L18 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnTagCollectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InTagCollectionPropertyHandle);`
- L23 _public prototype_ `bool IsOpen() const;`
- L25 _public prototype_ `void SetIsOpen(bool bInIsOpen);`
- L28 _private prototype_ `FText GetTagCollectionTitleText() const;`
- L30 _private prototype_ `FText GetTagCollectionTooltipText() const;`
- L32 _private prototype_ `TSharedRef<SWidget> MakeTagCollectionPicker();`
- L34 _private prototype_ `void OnTagCollectionMenuOpenChanged(bool bInIsOpened);`
- L36 _private prototype_ `DLLEXPORT void OnTagCollectionSelected(const FAssetData& InAssetData);`
- L38 _private prototype_ `void CloseTagCollectionPicker();`
- L40 _private member_ `TSharedPtr<IPropertyHandle> TagCollectionPropertyHandle;`
- L42 _private member_ `TSharedPtr<SComboButton> TagCollectionPickerButton;`
- L44 _private member_ `FSimpleDelegate OnTagCollectionChanged;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/SAvaTagHandleEntry.h` (Private)


#### class `SAvaTagHandleEntry`  
`class SAvaTagHandleEntry : public SCompoundWidget`  
_L11-41_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SAvaTagHandleEntry)`
- L15 _public prototype_ `SLATE_ARGUMENT(bool, ShowCheckBox) SLATE_ATTRIBUTE(bool, IsSelected) SLATE_EVENT(TDelegate<void(const FAvaTagHandle&, bool)>, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAvaTagHandle& InTagHandle);`
- L24 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L25 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L28 _private prototype_ `FText GetTagText() const;`
- L30 _private prototype_ `ECheckBoxState GetCheckState() const;`
- L32 _private prototype_ `void OnCheckStateChanged(ECheckBoxState InState);`
- L34 _private member_ `TAttribute<bool> IsSelected;`
- L36 _private member_ `TDelegate<void(const FAvaTagHandle&, bool)> OnSelectionChanged;`
- L38 _private member_ `FAvaTagHandle TagHandle;`
- L40 _private member_ `bool bIsPressed = true;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/SAvaTagPicker.h` (Private)


#### class `SAvaTagPicker`  
`class SAvaTagPicker : public SCompoundWidget`  
_L21-75_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SAvaTagPicker)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InStructPropertyHandle, const TSharedRef<IAvaTagHandleCustomizer>& InTagCustomizer);`
- L31 _private prototype_ `virtual void Tick(const FGeometry& InGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L32 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L35 _private prototype_ `FReply OpenContextMenu();`
- L37 _private prototype_ `const UAvaTagCollection* GetOrLoadTagCollection() const;`
- L39 _private prototype_ `void RefreshTagOptions();`
- L41 _private prototype_ `void OnTagCollectionChanged();`
- L43 _private prototype_ `void OnTagMenuOpenChanged(bool bInIsOpen);`
- L45 _private prototype_ `TSharedRef<ITableRow> CreateTagTableRow(TSharedPtr<FAvaTagHandle> InTagHandle, const TSharedRef<STableViewBase>& InOwnerTable);`
- L47 _private prototype_ `bool IsTagHandleSelected(FAvaTagHandle InTagHandle) const;`
- L49 _private prototype_ `DLLEXPORT void OnTagHandleSelectionChanged(const FAvaTagHandle& InTagHandle, bool bInIsSelected);`
- L51 _private prototype_ `FText GetValueDisplayText() const;`
- L54 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the struct property
- L57 _private member_ `TSharedPtr<IPropertyHandle> TagCollectionPropertyHandle;` — Handle to the Tag Collection property
- L59 _private member_ `TSharedPtr<SAvaTagCollectionPicker> TagCollectionPicker;`
- L61 _private member_ `TSharedPtr<SMenuAnchor> TagCollectionOptions;`
- L63 _private member_ `TSharedPtr<SListView<TSharedPtr<FAvaTagHandle>>> TagListView;`
- L65 _private member_ `TSharedPtr<IAvaTagHandleCustomizer> TagCustomizer;`
- L67 _private member_ `TSharedPtr<SComboButton> TagComboButton;`
- L70 _private member_ `TArray<TSharedPtr<FAvaTagHandle>> TagOptions;` — The available tag options
- L72 _private member_ `bool bRequestOpenTagCollectionPicker = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/TagCustomizers/AvaTagAliasCustomizer.h` (Private)


#### class `FAvaTagAliasCustomizer`  
`class FAvaTagAliasCustomizer : public IAvaTagHandleCustomizer`  
_L8-20_
- inherits: `IAvaTagHandleCustomizer`
- desc: Customizer for FAvaTagAlias
- L12 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetTagCollectionHandle(const TSharedRef<IPropertyHandle>& InStructHandle) const override;`
- L13 _public prototype_ `virtual const UAvaTagCollection* GetOrLoadTagCollection(const void* InStructRawData) const override;`
- L14 _public prototype_ `virtual void SetTagHandleAdded(const TSharedRef<IPropertyHandle>& InContainerProperty, const FAvaTagHandle& InTagHandle, bool bInAdd) const override;`
- L15 _public prototype_ `virtual bool ContainsTagHandle(const void* InStructRawData, const FAvaTagHandle& InTagHandle) const override;`
- L16 _public prototype_ `virtual FName GetDisplayValueName(const void* InStructRawData) const override;`
- L17 _public function_ `virtual bool AllowMultipleTags() const override`
- L18 _public function_ `virtual bool AllowAliasTags() const override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/TagCustomizers/AvaTagHandleContainerCustomizer.h` (Private)


#### class `FAvaTagHandleContainerCustomizer`  
`class FAvaTagHandleContainerCustomizer : public IAvaTagHandleCustomizer`  
_L8-19_
- inherits: `IAvaTagHandleCustomizer`
- desc: Customizer for FAvaTagHandleContainer
- L12 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetTagCollectionHandle(const TSharedRef<IPropertyHandle>& InStructHandle) const override;`
- L13 _public prototype_ `virtual const UAvaTagCollection* GetOrLoadTagCollection(const void* InStructRawData) const override;`
- L14 _public prototype_ `virtual void SetTagHandleAdded(const TSharedRef<IPropertyHandle>& InContainerProperty, const FAvaTagHandle& InTagHandle, bool bInAdd) const override;`
- L15 _public prototype_ `virtual bool ContainsTagHandle(const void* InStructRawData, const FAvaTagHandle& InTagHandle) const override;`
- L16 _public prototype_ `virtual FName GetDisplayValueName(const void* InStructRawData) const override;`
- L17 _public function_ `virtual bool AllowMultipleTags() const override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/TagCustomizers/AvaTagHandleCustomizer.h` (Private)


#### class `FAvaTagHandleCustomizer`  
`class FAvaTagHandleCustomizer : public IAvaTagHandleCustomizer`  
_L8-18_
- inherits: `IAvaTagHandleCustomizer`
- desc: Customizer for FAvaTagHandle
- L12 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetTagCollectionHandle(const TSharedRef<IPropertyHandle>& InStructHandle) const override;`
- L13 _public prototype_ `virtual const UAvaTagCollection* GetOrLoadTagCollection(const void* InStructRawData) const override;`
- L14 _public prototype_ `virtual void SetTagHandleAdded(const TSharedRef<IPropertyHandle>& InContainerProperty, const FAvaTagHandle& InTagHandle, bool bInAdd) const override;`
- L15 _public prototype_ `virtual bool ContainsTagHandle(const void* InStructRawData, const FAvaTagHandle& InTagHandle) const override;`
- L16 _public prototype_ `virtual FName GetDisplayValueName(const void* InStructRawData) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/TagCustomizers/AvaTagSoftHandleContainerCustomizer.h` (Private)


#### class `FAvaTagSoftHandleContainerCustomizer`  
`class FAvaTagSoftHandleContainerCustomizer : public IAvaTagHandleCustomizer`  
_L8-22_
- inherits: `IAvaTagHandleCustomizer`
- desc: Customizer for FAvaTagSoftHandleContainer
- L12 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetTagCollectionHandle(const TSharedRef<IPropertyHandle>& InStructHandle) const override;`
- L13 _public prototype_ `virtual const UAvaTagCollection* GetOrLoadTagCollection(const void* InStructRawData) const override;`
- L14 _public prototype_ `virtual void SetTagHandleAdded(const TSharedRef<IPropertyHandle>& InContainerProperty, const FAvaTagHandle& InTagHandle, bool bInAdd) const override;`
- L15 _public prototype_ `virtual bool ContainsTagHandle(const void* InStructRawData, const FAvaTagHandle& InTagHandle) const override;`
- L16 _public prototype_ `virtual FName GetDisplayValueName(const void* InStructRawData) const override;`
- L17 _public function_ `virtual bool AllowMultipleTags() const override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/TagCustomizers/AvaTagSoftHandleCustomizer.h` (Private)


#### class `FAvaTagSoftHandleCustomizer`  
`class FAvaTagSoftHandleCustomizer : public IAvaTagHandleCustomizer`  
_L8-18_
- inherits: `IAvaTagHandleCustomizer`
- desc: Customizer for FAvaTagSoftHandle
- L12 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetTagCollectionHandle(const TSharedRef<IPropertyHandle>& InStructHandle) const override;`
- L13 _public prototype_ `virtual const UAvaTagCollection* GetOrLoadTagCollection(const void* InStructRawData) const override;`
- L14 _public prototype_ `virtual void SetTagHandleAdded(const TSharedRef<IPropertyHandle>& InContainerProperty, const FAvaTagHandle& InTagHandle, bool bInAdd) const override;`
- L15 _public prototype_ `virtual bool ContainsTagHandle(const void* InStructRawData, const FAvaTagHandle& InTagHandle) const override;`
- L16 _public prototype_ `virtual FName GetDisplayValueName(const void* InStructRawData) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTagEditor/Private/Customization/TagCustomizers/IAvaTagHandleCustomizer.h` (Private)


#### class `IAvaTagHandleCustomizer`  
`class IAvaTagHandleCustomizer`  
_L13-41_
- desc: Abstraction Layer between the Tag Handle Types and the Tag Handle Customization
- L16 _public prototype_ `virtual ~IAvaTagHandleCustomizer() = default;`
- L22 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetTagCollectionHandle(const TSharedRef<IPropertyHandle>& InStructHandle) const = 0;` — Gets the Child Property Handle to the Tag Collection Property If returning nullptr, the picker will not generate a Tag Collection Source Picker
- L25 _public prototype_ `virtual const UAvaTagCollection* GetOrLoadTagCollection(const void* InStructRawData) const = 0;` — Gets or Loads the Tag Collection from the Raw Data Struct
- L28 _public prototype_ `virtual void SetTagHandleAdded(const TSharedRef<IPropertyHandle>& InStructHandle, const FAvaTagHandle& InTagHandle, bool bInAdd) const = 0;` — Sets the Tag Handled as added or removed
- L31 _public prototype_ `virtual bool ContainsTagHandle(const void* InStructRawData, const FAvaTagHandle& InTagHandle) const = 0;` — Returns whether the given Handle is contained by (or matches) the given Struct
- L34 _public prototype_ `virtual FName GetDisplayValueName(const void* InStructRawData) const = 0;` — Gets the Display Value Name of the Tags in the given Struct
- L37 _public function_ `virtual bool AllowMultipleTags() const` — Whether multiple tags are allowed to be selected, or just a single one
- L40 _public function_ `virtual bool AllowAliasTags() const` — Whether to show alias tags as options
