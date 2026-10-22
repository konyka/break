# Plugins / MetaHumanFaceFittingSolverEditor

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceFittingSolverEditor`
- headers: 3; symbols: 12
- symbol kinds: class=3, prototype=9
- PrivateDependencyModuleNames: AssetDefinition, CoreUObject, MetaHumanConfig, MetaHumanConfigEditor, MetaHumanCoreEditor, MetaHumanFaceFittingSolver, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceFittingSolverEditor/Private/AssetDefinitions/AssetDefinition_MetaHumanFaceFittingSolver.h` (Private)


#### class `UAssetDefinition_MetaHumanFaceFittingSolver`  
`class UAssetDefinition_MetaHumanFaceFittingSolver : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceFittingSolverEditor/Private/Customizations/MetaHumanFaceFittingSolverCustomizations.h` (Private)


#### class `FMetaHumanFaceFittingSolverCustomization`  
`class FMetaHumanFaceFittingSolverCustomization : public IDetailCustomization`  
_L8-17_
- inherits: `IDetailCustomization`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceFittingSolverEditor/Private/MetaHumanFaceFittingSolverFactoryNew.h` (Private)


#### class `UMetaHumanFaceFittingSolverFactoryNew`  
`class UMetaHumanFaceFittingSolverFactoryNew : public UFactory`  
_L14-27_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L21 _public prototype_ `UMetaHumanFaceFittingSolverFactoryNew();`
- L24 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* Context, FFeedbackContext* Warn) override;`
- L25 _public prototype_ `virtual FText GetToolTip() const override;`
