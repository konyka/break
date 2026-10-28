# Plugins / AvalancheAttributeEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttributeEditor`
- headers: 5; symbols: 36
- symbol kinds: class=5, function=4, member=8, prototype=19
- PrivateDependencyModuleNames: AvalancheAttribute, CoreUObject, Engine, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttributeEditor/Private/AvaAttributeEditorModule.h` (Private)


#### class `FAvaAttributeEditorModule`  
`class FAvaAttributeEditorModule : public IAvaAttributeEditorModule`  
_L7-13_
- inherits: `IAvaAttributeEditorModule`
- L11 _public prototype_ `virtual void CustomizeAttributes(const TSharedRef<IPropertyHandle>& InAttributesHandle, IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttributeEditor/Private/Customizations/AvaAttributeNodeBuilder.h` (Private)


#### class `FAvaAttributeNodeBuilder`  
`class FAvaAttributeNodeBuilder : public IDetailCustomNodeBuilder`  
_L11-33_
- inherits: `IDetailCustomNodeBuilder`
- L14 _public function_ `explicit FAvaAttributeNodeBuilder(const TSharedRef<IPropertyHandle>& InAttributeHandle, const TWeakPtr<IPropertyUtilities>& InPropertyUtilitiesWeak) : AttributeHandle(InAttributeHandle) , PropertyUtilitiesWeak(InPropertyUtilitiesWeak)`
- L22 _private prototype_ `virtual FName GetName() const override;`
- L23 _private prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& InNodeRow) override;`
- L24 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& InChildrenBuilder) override;`
- L25 _private prototype_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override;`
- L28 _private prototype_ `void GenerateChildContentRecursive(const TSharedRef<IPropertyHandle>& InParentHandle, IDetailChildrenBuilder& InChildrenBuilder, FName InDefaultCategoryName);`
- L30 _private member_ `TSharedRef<IPropertyHandle> AttributeHandle;`
- L32 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtilitiesWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttributeEditor/Private/DragDrop/AvaArrayItemDragDropHandler.h` (Private)


#### class `FAvaArrayItemDragDropHandler`  
`class FAvaArrayItemDragDropHandler : public IDetailDragDropHandler`  
_L22-39_
- inherits: `IDetailDragDropHandler`
- desc: Detail Drag Drop Handler for Custom Builders to re-order the array items Its existence is due to the following, 1) The Property Editor API only adds a reorder handle widget if the FProperty of GetPropertyNode is able to re-order (owner is an array property that can re-order) 2) The Array item property handle in question is being presented through a Custom Builder instead of directly as a property 3) Custom Builder customizations don't have a Property Node set (null), so the Property Editor API does not pick up the property to check with (1) 4) The only other way for the Property Editor API to add a reorder handle widget is by having a custom drag drop handler 5) There's no Array Detail Drag Drop Handler built-in; the default array reordering is handled differently (and is private) rather than through a IDetailDragDropHandler
- L25 _public prototype_ `explicit FAvaArrayItemDragDropHandler(const TSharedRef<IPropertyHandle>& InArrayItemHandle, const TSharedRef<SWidget>& InRowWidget, const TWeakPtr<IPropertyUtilities>& InPropertyUtilities);`
- L28 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation() const override;`
- L29 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) const override;`
- L30 _public prototype_ `virtual bool AcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) const override;`
- L34 _private member_ `TWeakPtr<IPropertyHandle> ArrayItemHandleWeak;`
- L36 _private member_ `TWeakPtr<SWidget> RowWidgetWeak;`
- L38 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtilitiesWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttributeEditor/Private/Widgets/SAvaAttributePicker.h` (Private)


#### class `SAvaAttributePicker`  
`class SAvaAttributePicker : public SCompoundWidget`  
_L17-43_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SAvaAttributePicker)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InAttributeHandle);`
- L26 _private prototype_ `bool IsPropertyEnabled() const;`
- L28 _private prototype_ `UAvaAttribute* GetAttribute() const;`
- L30 _private prototype_ `FText GetDisplayName() const;`
- L32 _private prototype_ `const FSlateBrush* GetIcon() const;`
- L34 _private prototype_ `TSharedRef<SWidget> GenerateClassPicker();`
- L36 _private prototype_ `void OnClassPicked(UClass* InClassPicked);`
- L38 _private prototype_ `TArray<FString> GenerateNewValues(TConstArrayView<FString> InCurrentValues, UClass* InClassPicked) const;`
- L40 _private member_ `TSharedPtr<IPropertyHandle> AttributeHandle;`
- L42 _private member_ `TSharedPtr<SComboButton> PickerComboButton;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttributeEditor/Public/IAvaAttributeEditorModule.h` (Public)


#### class `IAvaAttributeEditorModule`  
`class IAvaAttributeEditorModule : public IModuleInterface`  
_L11-27_
- inherits: `IModuleInterface`
- L13 _private member_ `static constexpr const TCHAR* ModuleName = TEXT("Ava`
- L16 _public function_ `static bool IsLoaded()`
- L21 _public function_ `static IAvaAttributeEditorModule& Get()`
- L26 _public prototype_ `virtual void CustomizeAttributes(const TSharedRef<IPropertyHandle>& InAttributesHandle, IDetailLayoutBuilder& InDetailBuilder) = 0;`
