# Plugins / MetaHumanFaceAnimationSolverEditor

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceAnimationSolverEditor`
- headers: 3; symbols: 12
- symbol kinds: class=3, prototype=9
- PrivateDependencyModuleNames: AssetDefinition, CoreUObject, MetaHumanConfig, MetaHumanConfigEditor, MetaHumanCoreEditor, MetaHumanFaceAnimationSolver, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceAnimationSolverEditor/Private/AssetDefinitions/AssetDefinition_MetaHumanFaceAnimationSolver.h` (Private)


#### class `UAssetDefinition_MetaHumanFaceAnimationSolver`  
`class UAssetDefinition_MetaHumanFaceAnimationSolver : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceAnimationSolverEditor/Private/Customizations/MetaHumanFaceAnimationSolverCustomizations.h` (Private)


#### class `FMetaHumanFaceAnimationSolverCustomization`  
`class FMetaHumanFaceAnimationSolverCustomization : public IDetailCustomization`  
_L8-17_
- inherits: `IDetailCustomization`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceAnimationSolverEditor/Private/MetaHumanFaceAnimationSolverFactoryNew.h` (Private)


#### class `UMetaHumanFaceAnimationSolverFactoryNew`  
`class UMetaHumanFaceAnimationSolverFactoryNew : public UFactory`  
_L14-27_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L21 _public prototype_ `UMetaHumanFaceAnimationSolverFactoryNew();`
- L24 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* Context, FFeedbackContext* Warn) override;`
- L25 _public prototype_ `virtual FText GetToolTip() const override;`
