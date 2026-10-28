# Plugins / AjaMediaEditor

- module root: `Plugins/Media/AjaMedia/Source/AjaMediaEditor`
- headers: 5; symbols: 24
- symbol kinds: class=5, function=7, member=2, prototype=10
- PrivateDependencyModuleNames: AjaMedia, AjaMediaOutput, AssetDefinition, Core, CoreUObject, EditorFramework, Engine, MediaAssets, MediaIOCore, MediaIOEditor, MediaPlayerEditor, Projects, PropertyEditor, Settings, Slate, SlateCore, TimeManagement, UnrealEd
- PrivateIncludePathModuleNames: AssetTools

### `Plugins/Media/AjaMedia/Source/AjaMediaEditor/Private/AssetDefinition/AssetDefinition_AjaMediaOutput.h` (Private)


#### class `UAssetDefinition_AjaMediaOutput`  
`class UAssetDefinition_AjaMediaOutput : public UAssetDefinition_MediaOutput`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaOutput`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/AjaMedia/Source/AjaMediaEditor/Private/AssetDefinition/AssetDefinition_AjaMediaSource.h` (Private)


#### class `UAssetDefinition_AjaMediaSource`  
`class UAssetDefinition_AjaMediaSource : public UAssetDefinition_MediaSource`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaSource`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/AjaMedia/Source/AjaMediaEditor/Private/Customizations/AjaMediaTimecodeReferenceCustomization.h` (Private)


#### class `FAjaMediaTimecodeReferenceCustomization`  
`class FAjaMediaTimecodeReferenceCustomization : public FMediaIOCustomizationBase`  
_L13-27_
- inherits: `FMediaIOCustomizationBase`
- desc: Implements a details view customization for the FAjaMediaTimecodeReferenceConfiguration
- L16 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L19 _private prototype_ `virtual TAttribute<FText> GetContentText() override;`
- L20 _private prototype_ `virtual TSharedRef<SWidget> HandleSourceComboButtonMenuContent() override;`
- L22 _private prototype_ `void OnSelectionChanged(FAjaMediaTimecodeReference SelectedItem);`
- L23 _private prototype_ `FReply OnButtonClicked() const;`
- L25 _private member_ `TWeakPtr<SWidget> PermutationSelector;`
- L26 _private member_ `FAjaMediaTimecodeReference SelectedConfiguration;`

### `Plugins/Media/AjaMedia/Source/AjaMediaEditor/Private/Factories/AjaMediaOutputFactoryNew.h` (Private)


#### class `UAjaMediaOutputFactoryNew`  
`class UAjaMediaOutputFactoryNew : public UFactory`  
_L13-22_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UAjaMediaOutput objects.
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L21 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/AjaMedia/Source/AjaMediaEditor/Private/Factories/AjaMediaSourceFactoryNew.h` (Private)


#### class `UAjaMediaSourceFactoryNew`  
`class UAjaMediaSourceFactoryNew : public UFactory`  
_L13-25_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UAjaMediaSource objects.
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L24 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
