# Plugins / MetaHumanFaceContourTrackerEditor

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceContourTrackerEditor`
- headers: 2; symbols: 10
- symbol kinds: class=2, prototype=8
- PrivateDependencyModuleNames: AssetDefinition, Core, CoreUObject, MetaHumanCore, MetaHumanCoreEditor, MetaHumanFaceContourTracker, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceContourTrackerEditor/Private/AssetDefinitions/AssetDefinition_MetaHumanFaceContourTracker.h` (Private)


#### class `UAssetDefinition_MetaHumanFaceContourTracker`  
`class UAssetDefinition_MetaHumanFaceContourTracker : public UAssetDefinitionDefault`  
_L10-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L21 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceContourTrackerEditor/Private/MetaHumanFaceContourTrackerAssetFactoryNew.h` (Private)


#### class `UMetaHumanFaceContourTrackerAssetFactoryNew`  
`class UMetaHumanFaceContourTrackerAssetFactoryNew : public UFactory`  
_L15-27_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- desc: Implements a factory for UMetaHumanFaceContourTrackerAsset objects from new
- L21 _public prototype_ `UMetaHumanFaceContourTrackerAssetFactoryNew();`
- L24 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* Context, FFeedbackContext* Warn) override;`
- L25 _public prototype_ `virtual FText GetToolTip() const override;`
