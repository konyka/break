# Plugins / MaterialAssetWizard

- module root: `Plugins/Editor/MaterialAssetWizard/Source/MaterialAssetWizard`
- headers: 2; symbols: 23
- symbol kinds: class=4, function=1, member=4, prototype=14
- PrivateDependencyModuleNames: CoreUObject, Engine, MaterialEditor, Slate, SlateCore
- PublicDependencyModuleNames: Core, UnrealEd, UserAssetTagsEditor

### `Plugins/Editor/MaterialAssetWizard/Source/MaterialAssetWizard/Public/MaterialAssetWizardModule.h` (Public)


#### class `FMaterialAssetWizardModule`  
`class FMaterialAssetWizardModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Editor/MaterialAssetWizard/Source/MaterialAssetWizard/Public/MaterialFactoryWithAssetWizard.h` (Public)


#### class `UMaterialFactoryWithAssetWizardBase`  
`class UMaterialFactoryWithAssetWizardBase : public UFactory`  
_L15-45_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UFactory`
- desc: Abstract base factory that summons material wizard.
- L20 _public prototype_ `UMaterialFactoryWithAssetWizardBase() = default;`
- L22 _public prototype_ `virtual bool ConfigureProperties() override;`
- L23 _public prototype_ `virtual bool ConfigurePropertiesAsync(FOnFactoryConfigurePropertiesAsyncComplete OnComplete, FOnFactoryConfigurePropertiesAsyncCancelled OnCancelled) override;`
- L24 _public function_ `virtual bool ShouldShowInNewMenu() const override`
- L27 _private prototype_ `void OnAssetsActivated(const TArray<FAssetData>& AssetData, EAssetTypeActivationMethod::Type Method);`
- L29 _private prototype_ `SWindow::FArguments CreateWindowArguments() const;`
- L30 _private prototype_ `STaggedAssetBrowser::FArguments CreateTaggedAssetBrowserArguments() const;`
- L35 _protected member_ `FSoftObjectPath ConfigurationPath;` — `UPROPERTY()` — The path to the tagged asset browser configuration asset. Needs to be valid.
- L38 _protected member_ `FText WindowTitle;` — `UPROPERTY()`
- L41 _protected member_ `FText EmptySelectionMessage;` — `UPROPERTY()`
- L44 _protected member_ `TWeakObjectPtr<UMaterial> BaseMaterial;` — The selected base material, if any.

#### class `UMaterialFactoryWithAssetWizard`  
`class UMaterialFactoryWithAssetWizard : public UMaterialFactoryWithAssetWizardBase`  
_L49-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMaterialFactoryWithAssetWizardBase`
- desc: Concrete material factory that will create a new material based on the selected material, or an empty one.
- L54 _public prototype_ `UMaterialFactoryWithAssetWizard();`
- L56 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L57 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

#### class `UMaterialInstanceConstantFactoryWithAssetWizard`  
`class UMaterialInstanceConstantFactoryWithAssetWizard : public UMaterialFactoryWithAssetWizardBase`  
_L62-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMaterialFactoryWithAssetWizardBase`
- desc: Concrete material instance constant factory that will create a new material instance based on the selected material, or an empty one.
- L67 _public prototype_ `UMaterialInstanceConstantFactoryWithAssetWizard();`
- L69 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L70 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
