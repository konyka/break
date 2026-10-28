# Plugins / SceneStateEventEditor

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor`
- headers: 11; symbols: 130
- symbol kinds: class=10, function=6, member=22, namespace=29, prototype=62, struct=1
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, BlueprintGraph, Core, CoreUObject, DetailCustomizations, Engine, GraphEditor, InputCore, KismetWidgets, PropertyEditor, SceneStateEvent, Slate, SlateCore, StructUtilsEditor, UnrealEd

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor/Private/AssetDefinition_SceneStateEventSchemaCollection.h` (Private)


#### class `UAssetDefinition_SceneStateEventSchemaCollection`  
`class UAssetDefinition_SceneStateEventSchemaCollection : public UAssetDefinitionDefault`  
_L10-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor/Private/DetailsView/SceneStateEventHandlerCustomization.h` (Private)


#### class `UE::SceneState::Editor::FEventHandlerCustomization`  
`class FEventHandlerCustomization : public IPropertyTypeCustomization`  
_L10-23_
- inherits: `IPropertyTypeCustomization`
- L13 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L20 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L21 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor/Private/DetailsView/SceneStateEventSchemaCollectionCustomization.h` (Private)


#### class `UE::SceneState::Editor::FEventSchemaCollectionCustomization`  
`class FEventSchemaCollectionCustomization : public IDetailCustomization`  
_L10-22_
- inherits: `IDetailCustomization`
- L13 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L20 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor/Private/DetailsView/SceneStateEventSchemaFieldNodeBuilder.h` (Private)


#### class `UE::SceneState::Editor::FEventSchemaFieldNodeBuilder`  
`class FEventSchemaFieldNodeBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FEventSchemaFieldNodeBuilder>`  
_L25-81_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FEventSchemaFieldNodeBuilder>`
- desc: Builder for a single field in the user defined struct of an Event Schema
- L28 _public prototype_ `explicit FEventSchemaFieldNodeBuilder(const TSharedRef<IPropertyHandle>& InEventSchemaHandle, const FGuid& InFieldGuid);`
- L31 _public prototype_ `USceneStateEventSchemaObject* GetEventSchema() const;` — Gets the Event Schema for this node builder, or  null if multiple or no event schemas are present
- L34 _public prototype_ `void OnChildrenChanged();` — Called when children layout has changed and needs to be refreshed
- L37 _public prototype_ `void OnSiblingsChanged();` — Called when this changed the parent layout so itself and siblings need to be rebuilt
- L40 _public prototype_ `FText GetFieldDisplayName() const;` — Retrieves the friendly name of the field
- L43 _public prototype_ `void OnFieldNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);` — Called when the friendly name for the field needs to be set
- L46 _public prototype_ `FEdGraphPinType OnGetPinInfo() const;` — Retrieves the current type of the field
- L49 _public prototype_ `void PinInfoChanged(const FEdGraphPinType& InPinType);` — Called when the type of the field needs updating
- L52 _public prototype_ `void RemoveField();` — Removes this field from the struct
- L55 _public prototype_ `EVisibility GetErrorIconVisibility() const;` — Returns visible whether this field is current invalid, collapsed otherwise
- L58 _public prototype_ `void SetOnRebuildSiblings(FSimpleDelegate InOnRegenerateSiblings);` — Set callback to when siblings require rebuilding
- L61 _public prototype_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override;`
- L62 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& InNodeRow) override;`
- L63 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& InChildrenBuilder) override;`
- L64 _public prototype_ `virtual bool RequiresTick() const override;`
- L65 _public prototype_ `virtual FName GetName() const override;`
- L66 _public prototype_ `virtual bool InitiallyCollapsed() const override;`
- L71 _private member_ `TWeakPtr<IPropertyHandle> EventSchemaHandleWeak;` — Handle to the Event schema property
- L74 _private member_ `FGuid FieldId;` — Var Guid of the field
- L77 _private member_ `FSimpleDelegate OnRegenerateSiblings;` — Delegate to execute if parent layout has changed and requires siblings to be rebuilt
- L80 _private member_ `FSimpleDelegate OnRegenerateChildren;` — Delegate to execute if this layout has changed and requires children to be rebuilt

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace ETextCommit`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace SceneState` (scope `UE`)
- L21 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor/Private/DetailsView/SceneStateEventSchemaHandleCustomization.h` (Private)


#### class `UE::SceneState::Editor::FEventSchemaHandleCustomization`  
`class FEventSchemaHandleCustomization : public IPropertyTypeCustomization`  
_L10-23_
- inherits: `IPropertyTypeCustomization`
- L13 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L20 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L21 _protected function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor/Private/DetailsView/SceneStateEventSchemaNodeBuilder.h` (Private)


#### class `UE::SceneState::Editor::FEventSchemaNodeBuilder`  
`class FEventSchemaNodeBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FEventSchemaNodeBuilder>`  
_L23-66_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FEventSchemaNodeBuilder>`
- desc: Builder for the Event Schema element entry in the Collection Event Schemas array
- L26 _public prototype_ `explicit FEventSchemaNodeBuilder(const TSharedRef<IPropertyHandle>& InEventSchemaHandle);`
- L30 _private prototype_ `TSharedRef<SWidget> CreateEventSchemaNameWidget();` — Generates editable text box to edit the Event Schema name
- L33 _private prototype_ `TSharedRef<SWidget> CreateAddPropertyButton();` — Generates the button to add properties to the Event Schema struct
- L36 _private prototype_ `void CreateEventSchema();` — Creates the event schema for the given event schema handle
- L39 _private prototype_ `USceneStateEventSchemaObject* GetEventSchema() const;` — Gets the current event schema value from the handle
- L42 _private prototype_ `FText GetEventSchemaName() const;` — Gets the name of the event schema
- L45 _private prototype_ `void SetEventSchemaName(const FText& InText, ETextCommit::Type InCommitType);` — Sets the name for the event schema
- L48 _private prototype_ `FReply OnAddPropertyClicked();` — Called to add a new property to the struct
- L51 _private prototype_ `void OnChildrenChanged();` — Called when the struct layout has changed
- L54 _private prototype_ `virtual FName GetName() const override;`
- L55 _private prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& InNodeRow) override;`
- L56 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& InChildrenBuilder) override;`
- L57 _private prototype_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override;`
- L58 _private prototype_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override;`
- L62 _private member_ `TSharedRef<IPropertyHandle> EventSchemaHandle;` — Handle to the Event schema property
- L65 _private member_ `FSimpleDelegate OnRegenerateChildren;` — Delegate to execute if the struct layout has changed and requires children to be rebuilt

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ETextCommit`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace SceneState` (scope `UE`)
- L19 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor/Private/DetailsView/SceneStateEventTemplateCustomization.h` (Private)


#### class `UE::SceneState::Editor::FEventTemplateCustomization`  
`class FEventTemplateCustomization : public IPropertyTypeCustomization`  
_L10-27_
- inherits: `IPropertyTypeCustomization`
- L13 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L20 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L21 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L24 _protected prototype_ `void OnEventSchemaHandleChanged();`
- L26 _protected member_ `TSharedPtr<IPropertyHandle> EventTemplateHandle;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor/Private/DetailsView/Widgets/SSceneStateEventSchemaPicker.h` (Private)


#### struct `UE::SceneState::Editor::FEventSchemaItem`  
`struct FEventSchemaItem`  
_L19-24_
- desc: Schema list item struct
- L21 _public member_ `FName Name;`
- L22 _public member_ `TWeakObjectPtr<USceneStateEventSchemaObject> EventSchemaWeak;`
- L23 _public member_ `TWeakObjectPtr<UUserDefinedStruct> EventStructWeak;`

#### class `UE::SceneState::Editor::SEventSchemaPicker`  
`class SEventSchemaPicker : public SCompoundWidget`  
_L27-93_
- inherits: `SCompoundWidget`
- desc: Widget to pick both an event schema collection and a schema from the available schemas within the collection
- L30 _public function_ `SLATE_BEGIN_ARGS(SEventSchemaPicker)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InStructHandle);`
- L36 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L41 _private prototype_ `FText GetCurrentEventSchemaName() const;` — Gets the selected event schema's name
- L44 _private prototype_ `USceneStateEventSchemaObject* GetEventSchema() const;` — Gets the current event schema in the handle
- L47 _private prototype_ `FString GetEventSchemaCollectionPath() const;` — Gets the path to the current selected event schema collection
- L50 _private prototype_ `void OnEventSchemaCollectionChanged(const FAssetData& InEventSchemaCollection);` — Called when an event schema collection has been selected
- L53 _private prototype_ `TSharedRef<SWidget> CreateSchemaItemWidget(TSharedRef<FEventSchemaItem> InSchemaItem);` — Creates the schema option entry row widget
- L56 _private prototype_ `void RefreshSchemaOptions(bool bIsComboBoxOpening);` — Discovers / builds the list of schema items based on the current event schema
- L59 _private prototype_ `void RebuildSchemaItems(const USceneStateEventSchemaCollection* InCollection, const FGuid& InCurrentId);` — Builds the list of schema items based on the given schema collection
- L62 _private prototype_ `void OnSchemaItemSelectionChanged(TSharedPtr<FEventSchemaItem> InSchemaItem, ESelectInfo::Type InSelectionType);` — Called when the schema item has been selected
- L65 _private member_ `TSharedPtr<IPropertyHandle> EventSchemaHandle;` — Handle to the Event Schema soft ref property
- L68 _private member_ `TSharedPtr<IPropertyHandle> EventStructHandle;` — Handle to the soft ref of the Event Schema struct
- L71 _private member_ `FObjectKey SelectedSchemaCollection;` — Current event schema collection
- L74 _private member_ `FString SelectedSchemaCollectionPath;` — Path to the current event schema collection
- L77 _private member_ `TSharedPtr<SObjectPropertyEntryBox> CollectionPicker;` — Object picker widget selecting the Event Schema Collection object
- L80 _private member_ `TSharedPtr<SComboBox<TSharedRef<FEventSchemaItem>>> SchemaPicker;` — Combo box listing the schemas in the current collection, if any
- L83 _private member_ `TSharedPtr<FEventSchemaItem> SelectedSchemaItem;` — Currently selected event schema
- L86 _private member_ `TArray<TSharedRef<FEventSchemaItem>> SchemaItems;` — The available id options within the collection
- L89 _private member_ `bool bRequestOpenCollectionPicker = false;` — Flag to request open the collection asset picker in next tick
- L92 _private member_ `bool bRequestOpenSchemaPicker = false;` — Flag to request open the Schema picker in next tick

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SceneState` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor/Private/SceneStateEventEditorModule.h` (Private)


#### class `UE::SceneState::Editor::FEventEditorModule`  
`class FEventEditorModule : public IModuleInterface`  
_L13-25_
- inherits: `IModuleInterface`
- L16 _private prototype_ `virtual void StartupModule() override;`
- L17 _private prototype_ `virtual void ShutdownModule() override;`
- L20 _private prototype_ `void RegisterDetailCustomizations();`
- L21 _private prototype_ `void UnregisterDetailCustomizations();`
- L23 _private member_ `TArray<FName> CustomizedTypes;`
- L24 _private member_ `TArray<FName> CustomizedClasses;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneState` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor/Private/SceneStateEventEditorUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneState` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L16 _prototype_ `bool CreateVariable(USceneStateEventSchemaObject* InEventSchema);` (scope `UE::SceneState::Editor`) — Creates a new boolean variable within the Event schema's struct If the current event schema struct is null, it creates a new struct and then creates the variable
- L22 _prototype_ `void RemoveVariable(USceneStateEventSchemaObject* InEventSchema, const FGuid& InFieldId);` (scope `UE::SceneState::Editor`) — Removes the variable matching the given field id in the event schema's struct If this is the last variable to remove, the struct will be removed (user defined structs cannot be empty)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventEditor/Private/SceneStateEventSchemaCollectionFactory.h` (Private)


#### class `USceneStateEventSchemaCollectionFactory`  
`class USceneStateEventSchemaCollectionFactory : public UFactory`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L13 _private prototype_ `USceneStateEventSchemaCollectionFactory();`
- L16 _private prototype_ `virtual FText GetDisplayName() const override;`
- L17 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L18 _private prototype_ `virtual uint32 GetMenuCategories() const override;`
- L19 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`
