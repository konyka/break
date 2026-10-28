# Plugins / ImagePlateEditor

- module root: `Plugins/Experimental/ImagePlate/Source/ImagePlateEditor`
- headers: 2; symbols: 9
- symbol kinds: class=2, function=4, prototype=3
- PrivateDependencyModuleNames: AssetDefinition, Core, CoreUObject, ImagePlate, Settings, SlateCore, UnrealEd

### `Plugins/Experimental/ImagePlate/Source/ImagePlateEditor/Private/AssetDefinition_ImagePlateFileSequence.h` (Private)


#### class `UAssetDefinition_ImagePlateFileSequence`  
`class UAssetDefinition_ImagePlateFileSequence : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Experimental/ImagePlate/Source/ImagePlateEditor/Private/ImagePlateFileSequenceFactory.h` (Private)


#### class `UImagePlateFileSequenceFactory`  
`class UImagePlateFileSequenceFactory : public UFactory`  
_L9-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L13 _private prototype_ `UImagePlateFileSequenceFactory(const FObjectInitializer& ObjectInitializer);`
- L15 _private prototype_ `virtual FText GetDisplayName() const override;`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`
