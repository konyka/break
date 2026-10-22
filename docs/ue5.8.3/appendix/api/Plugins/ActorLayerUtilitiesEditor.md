# Plugins / ActorLayerUtilitiesEditor

- module root: `Plugins/Runtime/ActorLayerUtilities/Source/ActorLayerUtilitiesEditor`
- headers: 1; symbols: 12
- symbol kinds: function=1, member=1, prototype=9, struct=1
- PrivateDependencyModuleNames: ActorLayerUtilities, Core, CoreUObject, EditorStyle, EditorWidgets, Engine, Layers, LevelEditor, PropertyEditor, Slate, SlateCore, UnrealEd

### `Plugins/Runtime/ActorLayerUtilities/Source/ActorLayerUtilitiesEditor/Private/ActorLayerPropertyTypeCustomization.h` (Private)


#### struct `FActorLayerPropertyTypeCustomization`  
`struct FActorLayerPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L15-38_
- inherits: `IPropertyTypeCustomization`
- L17 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L18 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L22 _private prototype_ `FText GetLayerText() const;`
- L24 _private prototype_ `TSharedRef<SWidget> OnGetLayerMenu();`
- L26 _private prototype_ `EVisibility GetSelectLayerVisibility() const;`
- L28 _private prototype_ `FReply OnSelectLayer();`
- L30 _private prototype_ `void AssignLayer(FName InNewLayer);`
- L32 _private prototype_ `void OpenLayerBrowser();`
- L34 _private prototype_ `FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L35 _private prototype_ `bool OnVerifyDrag(TSharedPtr<FDragDropOperation> InDragDrop);`
- L37 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
