# Plugins / XRBaseEditor

- module root: `Plugins/Runtime/XRBase/Source/XRBaseEditor`
- headers: 1; symbols: 22
- symbol kinds: class=1, member=6, prototype=15
- PrivateDependencyModuleNames: Core, CoreUObject, HeadMountedDisplay, InputCore, PropertyEditor, Slate, SlateCore, XRBase

### `Plugins/Runtime/XRBase/Source/XRBaseEditor/Private/XRDeviceVisualizationDetails.h` (Private)


#### class `FXRDeviceVisualizationDetails`  
`class FXRDeviceVisualizationDetails : public IDetailCustomization`  
_L17-50_
- inherits: `IDetailCustomization`
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L27 _private prototype_ `void RefreshXRSourceList();`
- L28 _private prototype_ `void SetSourcePropertyValue(const FName NewSystemName);`
- L29 _private prototype_ `void UpdateSourceSelection(TSharedPtr<FName> NewSelection);`
- L31 _private prototype_ `void CustomizeModelSourceRow(TSharedRef<IPropertyHandle>& Property, IDetailPropertyRow& PropertyRow);`
- L32 _private prototype_ `void OnResetSourceValue(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L33 _private prototype_ `bool IsSourceValueModified(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L34 _private prototype_ `FText OnGetSelectedSourceText() const;`
- L35 _private prototype_ `void OnSourceMenuOpened();`
- L36 _private prototype_ `void OnSourceNameCommited(const FText& NewText, ETextCommit::Type InTextCommit);`
- L37 _private prototype_ `TSharedRef<ITableRow> MakeSourceSelectionWidget(TSharedPtr<FName> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L38 _private prototype_ `void OnSourceSelectionChanged(TSharedPtr<FName> NewSelection, ESelectInfo::Type SelectInfo);`
- L40 _private prototype_ `void CustomizeCustomMeshRow(IDetailPropertyRow& PropertyRow);`
- L41 _private prototype_ `bool IsCustomMeshPropertyEnabled() const;`
- L43 _private member_ `TArray< TWeakObjectPtr<UObject> > SelectedObjects;`
- L44 _private member_ `TSharedPtr<IPropertyHandle> XRSourceProperty;`
- L45 _private member_ `TArray< TSharedPtr<FName> > XRSourceNames;`
- L46 _private member_ `TAttribute<bool> UseCustomMeshAttr;`
- L47 _private member_ `TSharedPtr<IPropertyHandle> DisplayMaterialsProperty;`
- L49 _private member_ `static TMap< FName, TSharedPtr<FName> > CustomSourceNames;`
