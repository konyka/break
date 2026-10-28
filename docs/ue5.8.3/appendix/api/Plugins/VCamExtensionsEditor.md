# Plugins / VCamExtensionsEditor

- module root: `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensionsEditor`
- headers: 5; symbols: 26
- symbol kinds: class=4, delegate=1, prototype=21
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, CoreUObject, Engine, UnrealEd, VCamCore, VCamCoreEditor, VCamExtensions
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensionsEditor/Private/AssetDefinition/AssetDefinition_ModifierBoundWidgetStyles.h` (Private)


#### class `UAssetDefinition_ModifierBoundWidgetStyles`  
`class UAssetDefinition_ModifierBoundWidgetStyles : public UAssetDefinitionDefault`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensionsEditor/Private/AssetDefinition/AssetDefinition_ModifierHierarchy.h` (Private)


#### class `UAssetDefinition_ModifierHierarchy`  
`class UAssetDefinition_ModifierHierarchy : public UAssetDefinitionDefault`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensionsEditor/Private/Factories/ModifierBoundWidgetStylesAssetFactory.h` (Private)


#### class `UModifierBoundWidgetStylesAssetFactory`  
`class UModifierBoundWidgetStylesAssetFactory : public UFactory`  
_L12-26_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L17 _public prototype_ `UModifierBoundWidgetStylesAssetFactory();`
- L20 _public prototype_ `virtual FText GetDisplayName() const override;`
- L21 _public prototype_ `virtual FText GetToolTip() const override;`
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L24 _public prototype_ `virtual const TArray<FText>& GetMenuCategorySubMenus() const override;`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensionsEditor/Private/Factories/ModifierHierarchyAssetFactory.h` (Private)


#### class `UModifierHierarchyAssetFactory`  
`class UModifierHierarchyAssetFactory : public UFactory`  
_L12-26_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L17 _public prototype_ `UModifierHierarchyAssetFactory();`
- L20 _public prototype_ `virtual FText GetDisplayName() const override;`
- L21 _public prototype_ `virtual FText GetToolTip() const override;`
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L24 _public prototype_ `virtual const TArray<FText>& GetMenuCategorySubMenus() const override;`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensionsEditor/Private/VCamExtensionsEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamEditorExtensions, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamEditorExtensions, Log, All);`
