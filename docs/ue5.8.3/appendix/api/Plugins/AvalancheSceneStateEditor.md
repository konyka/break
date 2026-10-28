# Plugins / AvalancheSceneStateEditor

- module root: `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneStateEditor`
- headers: 6; symbols: 57
- symbol kinds: class=5, function=3, member=9, namespace=5, prototype=35
- PrivateDependencyModuleNames: AvalancheEditorCore, AvalancheSceneState, AvalancheSceneStateBlueprint, BlueprintGraph, Core, CoreUObject, Engine, KismetWidgets, Projects, PropertyEditor, RemoteControlLogic, SceneStateBlueprint, SceneStateBlueprintEditor, SceneStateGameplay, Slate, SlateCore, StructUtilsEditor, ToolMenus, UnrealEd

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneStateEditor/Private/AvaSceneStateEditorModule.h` (Private)


#### class `FAvaSceneStateEditorModule`  
`class FAvaSceneStateEditorModule : public IModuleInterface`  
_L10-23_
- inherits: `IModuleInterface`
- L13 _private prototype_ `virtual void StartupModule() override;`
- L14 _private prototype_ `virtual void ShutdownModule() override;`
- L17 _private prototype_ `void RegisterCustomizations();`
- L18 _private prototype_ `void UnregisterCustomizations();`
- L20 _private member_ `FDelegateHandle OnEditorBuildHandle;`
- L22 _private member_ `TArray<FName> CustomizedTypes;`

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneStateEditor/Private/AvaSceneStateEditorStyle.h` (Private)


#### class `UE::AvaSceneState::Editor::FEditorStyle`  
`class FEditorStyle : public FSlateStyleSet`  
_L10-21_
- inherits: `FSlateStyleSet`
- L13 _public function_ `static FEditorStyle& Get()`
- L19 _public prototype_ `FEditorStyle();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace AvaSceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::AvaSceneState`)

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneStateEditor/Private/AvaSceneStateExtension.h` (Private)


#### class `FAvaSceneStateExtension`  
`class FAvaSceneStateExtension : public FAvaEditorExtension`  
_L10-40_
- inherits: `FAvaEditorExtension`
- L13 _public prototype_ `UE_AVA_INHERITS(FAvaSceneStateExtension, FAvaEditorExtension);`
- L16 _public prototype_ `virtual void ExtendToolbarMenu(UToolMenu& InMenu) override;`
- L17 _public prototype_ `virtual void Cleanup() override;`
- L21 _private prototype_ `void GenerateSceneStateOptions(UToolMenu* InMenu);`
- L24 _private prototype_ `AAvaSceneStateActor* FindSceneStateActor() const;` — Finds an existing scene state actor in the current world
- L27 _private prototype_ `AAvaSceneStateActor* FindOrSpawnSceneStateActor() const;` — Finds or spawns a scene state actor in the current world
- L30 _private prototype_ `USceneStateBlueprint* CreateSceneStateBlueprint(AAvaSceneStateActor* InSceneStateActor) const;` — Creates a new scene state blueprint and assigns it to the given scene state actor
- L33 _private prototype_ `bool CanDeleteSceneStateActor() const;` — Returns whether there's an existing scene state actor that can be destroyed
- L36 _private prototype_ `void DeleteSceneStateActor();` — Destroys the existing scene state actor in the current world
- L39 _private prototype_ `void OpenSceneStateBlueprintEditor();` — Opens the existing scene state blueprint in the current world

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneStateEditor/Private/DetailsView/AvaSceneStateRCTaskDetails.h` (Private)


#### class `FAvaSceneStateRCTaskDetails`  
`class FAvaSceneStateRCTaskDetails : public IPropertyTypeCustomization`  
_L7-20_
- inherits: `IPropertyTypeCustomization`
- L10 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L17 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L18 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneStateEditor/Private/DetailsView/AvaSceneStateRCUtils.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AvaSceneStateRCUtils` (scope `UE`)
- L18 _prototype_ `void ForEachControllerSupportedType(TFunctionRef<void(const FEdGraphPinType&)> InFunctor);` (scope `UE::AvaSceneStateRCUtils`) — Calls the given functor for every supported type for Remote Control controllers
- L21 _prototype_ `FEdGraphPinType GetPinInfo(const TSharedRef<IPropertyHandle>& InPropertyHandle);` (scope `UE::AvaSceneStateRCUtils`) — Gets the pin type for the property under the given property handle
- L24 _prototype_ `FPropertyBagPropertyDesc MakeControllerPropertyDesc();` (scope `UE::AvaSceneStateRCUtils`) — Creates a new generic property desc
- L31 _prototype_ `bool SyncPropertyDescs(TArray<FPropertyBagPropertyDesc>& InOutPropertyDescs, TArrayView<FAvaSceneStateRCControllerMapping> InMappings);` (scope `UE::AvaSceneStateRCUtils`) — Returns a copy of property descs (some that could already exist in the property bag) that matches the structure in the given mappings @param InOutPropertyDescs the array of property descs to sync @param InMappings the mappings to match against

### `Plugins/VirtualProduction/AvalancheSceneState/Source/AvalancheSceneStateEditor/Private/DetailsView/AvaSceneStateRCValuesDetails.h` (Private)


#### class `FAvaSceneStateRCValuesDetails`  
`class FAvaSceneStateRCValuesDetails : public IDetailCustomNodeBuilder, public TSharedFromThis<FAvaSceneStateRCValuesDetails>`  
_L14-78_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FAvaSceneStateRCValuesDetails>`
- desc: Builder to group the controller mapping entries to the instanced property bag value properties
- L17 _public prototype_ `explicit FAvaSceneStateRCValuesDetails(const TSharedRef<IPropertyHandle>& InStructHandle, const FGuid& InValuesId, TSharedPtr<IPropertyUtilities> InPropUtils);`
- L20 _public prototype_ `void Initialize();` — Called once per instance to bind to delegates
- L26 _public prototype_ `void SyncControllerValues();` — Called when mapping has changed, while still during a transaction. Syncs the value instanced property bag ensuring there's a valid matching value to every mapping entry.
- L29 _public prototype_ `void OnControllerMappingsNumChanged();` — Called on rebuild time when the mapping num has changed
- L32 _public prototype_ `void ConfigureMappingRow(const TSharedRef<IPropertyHandle>& InMappingHandle, IDetailPropertyRow& InChildRow);` — Customizes the controller mapping row
- L35 _public prototype_ `void ConfigureValueRow(IDetailPropertyRow& InChildRow);` — Customizes the value row
- L38 _public prototype_ `void OnPinInfoChanged(const FEdGraphPinType& InPinType, TSharedRef<IPropertyHandle> InValueHandle);` — Called when the type of the value property has changed
- L41 _public prototype_ `void GetControllerSupportedTypes(TArray<FPinTypeTreeItem>& OutTreeItems, ETypeTreeFilter InTreeFilter);` — Gathers all the supported types for a remote control preset controller
- L44 _public prototype_ `virtual FName GetName() const override;`
- L45 _public function_ `virtual bool InitiallyCollapsed() const override`
- L46 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& InNodeRow) override;`
- L47 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& InChildrenBuilder) override;`
- L48 _public prototype_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRebuildChildren ) override;`
- L53 _private prototype_ `TArray<FAvaSceneStateRCControllerMapping>& GetControllerMappings();` — Gets the controller mappings. Expects only one instance to be available
- L56 _private prototype_ `FInstancedPropertyBag& GetInstancedPropertyBag();` — Gets the instanced property bag from ValuesHandle. Expects only one instance to be available
- L59 _private member_ `TSharedRef<IPropertyHandle> StructHandle;` — Handle to the FAvaSceneStateRCTaskInstance holding the values and mappings properties
- L62 _private member_ `TSharedRef<IPropertyHandle> ValuesHandle;` — Handle to the controller values instanced property bag in FAvaSceneStateRCTaskInstance
- L65 _private member_ `TSharedRef<IPropertyHandle> MappingsHandle;` — Handle to the controller mappings array in FAvaSceneStateRCTaskInstance
- L68 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utilities to use for refreshing the details view
- L71 _private member_ `FGuid ValuesId;` — Binding id to the values Instanced property bag
- L74 _private member_ `FSimpleDelegate OnRebuildChildren;` — Delegate called when needing to rebuild the children items
- L77 _private member_ `bool bInitialized = false;` — Flag to ensure Initialize() only gets called once
