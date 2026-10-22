# Plugins / USDClassesEditor

- module root: `Plugins/Importers/USDImporter/Source/USDClassesEditor`
- headers: 4; symbols: 24
- symbol kinds: class=4, member=3, prototype=17
- PrivateDependencyModuleNames: ContentBrowser, InputCore, USDClasses, UnrealEd
- PublicDependencyModuleNames: AssetDefinition, Core, CoreUObject, Engine, Slate, SlateCore

### `Plugins/Importers/USDImporter/Source/USDClassesEditor/Private/AssetDefinition_USDAssetCache.h` (Private)


#### class `UAssetDefinition_UsdAssetCache`  
`class UAssetDefinition_UsdAssetCache : public UAssetDefinitionDefault`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual bool CanImport() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Importers/USDImporter/Source/USDClassesEditor/Private/USDAssetCacheAssetEditorToolkit.h` (Private)


#### class `FUsdAssetCacheAssetEditorToolkit`  
`class FUsdAssetCacheAssetEditorToolkit : public FAssetEditorToolkit , public FGCObject`  
_L10-37_
- inherits: `FAssetEditorToolkit,FGCObject`
- L15 _public prototype_ `void Initialize(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UUsdAssetCache3* InAssetCache);`
- L18 _private prototype_ `virtual FText GetBaseToolkitName() const override;`
- L19 _private prototype_ `virtual FName GetToolkitFName() const override;`
- L20 _private prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L21 _private prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L23 _private prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L24 _private prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L26 _private prototype_ `TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args);`
- L28 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L29 _private prototype_ `virtual FString GetReferencerName() const override;`
- L32 _private member_ `TObjectPtr<UUsdAssetCache3> AssetCache;`
- L34 _private member_ `TSharedPtr<class IDetailsView> AssetCacheEditorWidget;`
- L36 _private member_ `static const FName TabId;`

### `Plugins/Importers/USDImporter/Source/USDClassesEditor/Private/USDAssetCacheFactory.h` (Private)


#### class `UUsdAssetCacheFactory`  
`class UUsdAssetCacheFactory : public UFactory`  
_L12-22_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L20 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Importers/USDImporter/Source/USDClassesEditor/Public/USDClassesEditorModule.h` (Public)


#### class `IUsdClassesEditorModule`  
`class IUsdClassesEditorModule : public IModuleInterface`  
_L7-9_
- inherits: `IModuleInterface`
