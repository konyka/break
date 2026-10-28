# Plugins / MassAIBehaviorEditor

- module root: `Plugins/AI/MassAI/Source/MassAIBehaviorEditor`
- headers: 3; symbols: 21
- symbol kinds: class=3, macro=1, member=5, prototype=12
- PrivateDependencyModuleNames: AIModule, AppFramework, Core, CoreUObject, Engine, InputCore, MassAIBehavior, MassCore, MassEntity, PropertyEditor, Slate, SlateCore
- PublicDependencyModuleNames: 

### `Plugins/AI/MassAI/Source/MassAIBehaviorEditor/Private/MassAIBehaviorEditorModule.h` (Private)


#### class `FMassAIBehaviorEditorModule`  
`class FMassAIBehaviorEditorModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MASSAIBEHAVIOREDITOR_API`

### `Plugins/AI/MassAI/Source/MassAIBehaviorEditor/Private/MassLookAtPriorityDetails.h` (Private)


#### class `FMassLookAtPriorityDetails`  
`class FMassLookAtPriorityDetails final : public IPropertyTypeCustomization`  
_L13-38_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FMassLookAtPriority.
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L27 _private prototype_ `FText GetDescription() const;` — @return Description for the current priority value
- L30 _private prototype_ `TSharedRef<SWidget> OnGetComboContent() const;` — Builds the priority drop down
- L33 _private prototype_ `void CachePriorityInfos();` — Cache priority values from MassLookAtSetting into 'PriorityInfos'
- L35 _private member_ `TArray<FMassLookAtPriorityInfo> PriorityInfos;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> PriorityValueProperty;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/AI/MassAI/Source/MassAIBehaviorEditor/Private/MassLookAtPriorityInfoDetails.h` (Private)


#### class `FMassLookAtPriorityInfoDetails`  
`class FMassLookAtPriorityInfoDetails : public IPropertyTypeCustomization`  
_L12-31_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FMassLookAtPriorityInfo.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L27 _private prototype_ `FText GetPriorityDescription() const;`
- L29 _private member_ `TSharedPtr<IPropertyHandle> PriorityProperty;`
- L30 _private member_ `TSharedPtr<IPropertyHandle> NameProperty;`
