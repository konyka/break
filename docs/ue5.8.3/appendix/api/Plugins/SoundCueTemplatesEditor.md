# Plugins / SoundCueTemplatesEditor

- module root: `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplatesEditor`
- headers: 4; symbols: 24
- symbol kinds: class=6, function=5, member=5, prototype=8
- PrivateDependencyModuleNames: ContentBrowser, CoreUObject, Engine, GameProjectGeneration, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: AssetTools
- PublicDependencyModuleNames: AssetDefinition, AudioEditor, Core, SoundCueTemplates, ToolMenus

### `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplatesEditor/Private/AssetDefinition_SoundCueTemplate.h` (Private)


#### class `UAssetDefinition_SoundCueTemplate`  
`class UAssetDefinition_SoundCueTemplate : public UAssetDefinition_SoundBase`  
_L16-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_SoundBase`
- L22 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L23 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L24 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L25 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplatesEditor/Private/SoundCueTemplateClassFilter.h` (Private)


#### class `FSoundCueTemplateAssetParentFilter`  
`class FSoundCueTemplateAssetParentFilter : public IClassViewerFilter`  
_L8-26_
- inherits: `IClassViewerFilter`
- L12 _public member_ `TSet< const UClass* > AllowedChildrenOfClasses;` — All children of these classes will be included unless filtered out by another setting.
- L15 _public member_ `EClassFlags DisallowedClassFlags;` — Disallowed class flags.
- L17 _public function_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override`
- L22 _public function_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override`

### `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplatesEditor/Public/SoundCueTemplateFactory.h` (Public)


#### class `USoundCueTemplateCopyFactory`  
`class USoundCueTemplateCopyFactory : public UFactory`  
_L14-25_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L19 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _public member_ `TWeakObjectPtr<USoundCueTemplate> SoundCueTemplate;` — `UPROPERTY()`

#### class `USoundCueTemplateFactory`  
`class USoundCueTemplateFactory : public UFactory`  
_L28-43_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L33 _private member_ `TSubclassOf<USoundCueTemplate> SoundCueTemplateClass;` — `UPROPERTY(EditAnywhere, Category = SoundCueTemplateFacotry)`
- L36 _private member_ `TArray<TWeakObjectPtr<USoundWave>> SoundWaves;` — `UPROPERTY(EditAnywhere, Category = SoundCueTemplateFactory)`
- L39 _private prototype_ `virtual bool ConfigureProperties() override;`
- L40 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L41 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`

#### class `USoundCueTemplateClassTemplate`  
`class USoundCueTemplateClassTemplate : public UPluginClassTemplate`  
_L46-49_
- reflection: `UCLASS()`
- inherits: `UPluginClassTemplate`

### `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplatesEditor/Public/SoundCueTemplatesEditorModule.h` (Public)


#### class `FSoundCueTemplatesEditorModule`  
`class FSoundCueTemplatesEditorModule : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(SoundCueTemplatesEditor, Log, All);`
