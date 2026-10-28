# Plugins / GeneSplicerEditor

- module root: `Plugins/Animation/GeneSplicer/Source/GeneSplicerEditor`
- headers: 6; symbols: 27
- symbol kinds: class=6, function=2, member=1, prototype=18
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, RigLogicModule, UnrealEd
- PublicDependencyModuleNames: Core, GeneSplicerModule

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerEditor/Public/GenePoolAssetActions.h` (Public)


#### class `FGenePoolAssetTypeActions`  
`class FGenePoolAssetTypeActions : public FAssetTypeActions_Base`  
_L8-15_
- inherits: `FAssetTypeActions_Base`
- L11 _public prototype_ `UClass* GetSupportedClass() const override;`
- L12 _public prototype_ `FText GetName() const override;`
- L13 _public prototype_ `FColor GetTypeColor() const override;`
- L14 _public prototype_ `uint32 GetCategories() override;`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerEditor/Public/GenePoolAssetFactory.h` (Public)


#### class `UGenePoolAssetFactory`  
`class UGenePoolAssetFactory : public UFactory`  
_L13-19_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L17 _public prototype_ `UGenePoolAssetFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerEditor/Public/GenePoolAssetImportFactory.h` (Public)


#### class `UGenePoolAssetImportFactory`  
`class UGenePoolAssetImportFactory: public UFactory`  
_L11-21_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L16 _public prototype_ `UGenePoolAssetImportFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;` — UFactory interface
- L19 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L20 _public function_ `virtual void CleanUp() override`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerEditor/Public/GeneSplicerEditor.h` (Public)


#### class `FGeneSplicerEditorModule`  
`class FGeneSplicerEditorModule : public IModuleInterface`  
_L9-18_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `TSharedPtr<FGenePoolAssetTypeActions> GenePoolAssetTypeActions;`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerEditor/Public/RegionAffiliationAssetActions.h` (Public)


#### class `FRegionAffiliationAssetTypeActions`  
`class FRegionAffiliationAssetTypeActions : public FAssetTypeActions_Base`  
_L9-16_
- inherits: `FAssetTypeActions_Base`
- L12 _public prototype_ `UClass* GetSupportedClass() const override;`
- L13 _public prototype_ `FText GetName() const override;`
- L14 _public prototype_ `FColor GetTypeColor() const override;`
- L15 _public prototype_ `uint32 GetCategories() override;`

### `Plugins/Animation/GeneSplicer/Source/GeneSplicerEditor/Public/RegionAffiliationAssetImportFactory.h` (Public)


#### class `URegionAffiliationAssetImportFactory`  
`class URegionAffiliationAssetImportFactory: public UFactory`  
_L11-21_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L16 _public prototype_ `URegionAffiliationAssetImportFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;` — UFactory interface
- L19 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L20 _public function_ `virtual void CleanUp() override`
