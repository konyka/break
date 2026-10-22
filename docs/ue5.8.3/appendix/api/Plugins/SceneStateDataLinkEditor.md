# Plugins / SceneStateDataLinkEditor

- module root: `Plugins/VirtualProduction/SceneStateDataLink/Source/SceneStateDataLinkEditor`
- headers: 2; symbols: 21
- symbol kinds: class=2, function=1, member=3, namespace=4, prototype=11
- PrivateDependencyModuleNames: Core, CoreUObject, DataLink, Engine, PropertyEditor, SceneStateBlueprintEditor, SceneStateDataLink

### `Plugins/VirtualProduction/SceneStateDataLink/Source/SceneStateDataLinkEditor/Private/DetailsView/SceneStateDataLinkRequestTaskDetails.h` (Private)


#### class `UE::SceneStateDataLink::FRequestTaskInstanceDetails`  
`class FRequestTaskInstanceDetails : public IPropertyTypeCustomization`  
_L14-46_
- inherits: `IPropertyTypeCustomization`
- desc: Details Customization for FSceneStateDataLinkRequestTaskInstance
- L17 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L26 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L27 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L32 _private prototype_ `UDataLinkGraph* GetDataLinkGraph() const;` — Gets the value of the data link graph property handle
- L34 _private prototype_ `TArray<FDataLinkInputData>* GetInputData() const;` — Gets the value of the input data property handle
- L37 _private prototype_ `void OnGraphCompiled(UDataLinkGraph* InDataLinkGraph);` — Called when a data link graph has compiled. Used to update the input data
- L39 _private prototype_ `void OnGraphChanged();` — Called when the graph has changed to update the input data
- L42 _private prototype_ `void UpdateInputData();` — Updates the input data array to match the data link graph's input pins
- L44 _private member_ `TSharedPtr<IPropertyHandle> DataLinkGraphHandle;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> InputDataHandle;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneStateDataLink` (scope `UE`)

### `Plugins/VirtualProduction/SceneStateDataLink/Source/SceneStateDataLinkEditor/Private/SceneStateDataLinkEditorModule.h` (Private)


#### class `UE::SceneStateDataLink::FEditorModule`  
`class FEditorModule : public IModuleInterface`  
_L12-25_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _private prototype_ `void RegisterDetailCustomizations();`
- L22 _private prototype_ `void UnregisterDetailCustomizations();`
- L24 _private member_ `TArray<FName> CustomizedTypes;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SceneStateDataLink` (scope `UE`)
