# Plugins / MetaHumanConfigEditor

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanConfigEditor`
- headers: 4; symbols: 25
- symbol kinds: class=4, function=1, macro=1, member=4, prototype=14, typedef=1
- PrivateDependencyModuleNames: AssetDefinition, CoreUObject, InputCore, MetaHumanConfig, MetaHumanCoreEditor, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanConfigEditor/Private/AssetDefinitions/AssetDefinition_MetaHumanConfig.h` (Private)


#### class `UAssetDefinition_MetaHumanConfig`  
`class UAssetDefinition_MetaHumanConfig : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanConfigEditor/Private/Customizations/MetaHumanConfigCustomizations.h` (Private)


#### class `FMetaHumanConfigCustomization`  
`class FMetaHumanConfigCustomization : public IDetailCustomization`  
_L8-17_
- inherits: `IDetailCustomization`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanConfigEditor/Private/MetaHumanConfigFactory.h` (Private)


#### class `UMetaHumanConfigFactory`  
`class UMetaHumanConfigFactory : public UFactory`  
_L14-27_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L21 _public prototype_ `UMetaHumanConfigFactory();`
- L24 _public prototype_ `virtual bool FactoryCanImport(const FString& InFilename) override;`
- L25 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, const FString& InFilename, const TCHAR* InParms, FFeedbackContext* InWarn, bool& bOutOperationCanceled) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanConfigEditor/Public/SMetaHumanConfigCombo.h` (Public)


#### class `SMetaHumanConfigCombo`  
`class SMetaHumanConfigCombo : public SCompoundWidget`  
_L14-41_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanConfigCombo)`
- L23 _public typedef_ `typedef TSharedPtr<FAssetData> FComboItemType;`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, EMetaHumanConfigType InMetaHumanConfigType, TObjectPtr<UObject> InPropertyOwner, TSharedPtr<IPropertyHandle> InProperty);`
- L27 _public prototype_ `TSharedRef<SWidget> MakeWidgetForOption(FComboItemType InOption);`
- L29 _public prototype_ `void OnSelectionChanged(FComboItemType InNewValue, ESelectInfo::Type);`
- L31 _public prototype_ `FText GetCurrentItemLabel() const;`
- L33 _public prototype_ `bool IsEnabled() const;`
- L37 _private member_ `TArray<TSharedPtr<FAssetData>> OptionsSource;`
- L38 _private member_ `TObjectPtr<UObject> PropertyOwner;`
- L39 _private member_ `TSharedPtr<IPropertyHandle> Property;`
- L40 _private member_ `TSharedPtr<SComboBox<FComboItemType>> Combo;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCONFIGEDITOR_API`
