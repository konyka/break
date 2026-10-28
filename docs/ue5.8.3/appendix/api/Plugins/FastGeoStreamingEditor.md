# Plugins / FastGeoStreamingEditor

- module root: `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreamingEditor`
- headers: 4; symbols: 17
- symbol kinds: class=4, function=1, member=1, prototype=11
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, Core, CoreUObject, Engine, FastGeoStreaming, Slate, SlateCore, UnrealEd

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreamingEditor/Private/FastGeoAssetDefinitions.h` (Private)


#### class `UAssetDefinition_FastGeoTransformerSettings`  
`class UAssetDefinition_FastGeoTransformerSettings : public UAssetDefinitionDefault`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreamingEditor/Private/FastGeoDetailsCustomization.h` (Private)


#### class `FConvertFastGeoSettingsAssetButtonCustomization`  
`class FConvertFastGeoSettingsAssetButtonCustomization : public IPropertyTypeCustomization`  
_L11-19_
- inherits: `IPropertyTypeCustomization`
- desc: Unfortunately, because UFastGeoTransformerSettings are Instanced in the case where we want the convert button to be available, and because IDetailCustomization currently doesn't work for Instanced properties, we customize a virtual property instead
- L14 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L18 _public function_ `void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreamingEditor/Private/FastGeoFactory.h` (Private)


#### class `UFastGeoFactory`  
`class UFastGeoFactory : public UFactory`  
_L12-23_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L18 _private member_ `TObjectPtr<class UFastGeoTransformerSettings> InitialSettings;` — `UPROPERTY()` — Set this in order for the factory to duplicate an object
- L21 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreamingEditor/Private/FastGeoStreamingEditorModule.h` (Private)


#### class `FFastGeoStreamingEditorModule`  
`class FFastGeoStreamingEditorModule : public IModuleInterface`  
_L8-16_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _private prototype_ `void OnEditorSelectionChanged(UObject* );`
