# Plugins / SoundUtilitiesEditor

- module root: `Plugins/Runtime/SoundUtilities/Source/SoundUtilitiesEditor`
- headers: 4; symbols: 15
- symbol kinds: class=4, function=3, member=1, prototype=7
- PrivateIncludePathModuleNames: AssetTools, AudioEditor
- PublicDependencyModuleNames: AssetDefinition, AudioEditor, AudioMixer, ContentBrowser, Core, CoreUObject, EditorFramework, Engine, Slate, SlateCore, SoundUtilities, ToolMenus, UnrealEd

### `Plugins/Runtime/SoundUtilities/Source/SoundUtilitiesEditor/Private/AssetTypeActions_SoundSimple.h` (Private)


#### class `FAssetTypeActions_SoundSimple`  
`class FAssetTypeActions_SoundSimple : public FAssetTypeActions_SoundBase`  
_L7-15_
- inherits: `FAssetTypeActions_SoundBase`
- L11 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L12 _public function_ `virtual FColor GetTypeColor() const override`
- L13 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L14 _public function_ `virtual bool CanFilter() override`

### `Plugins/Runtime/SoundUtilities/Source/SoundUtilitiesEditor/Private/SoundSimpleFactory.h` (Private)


#### class `USoundSimpleFactory`  
`class USoundSimpleFactory : public UFactory`  
_L11-22_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L21 _private member_ `TArray<TObjectPtr<USoundWave>> SoundWaves;` — `UPROPERTY()` — Sound waves to create the simple sound with

### `Plugins/Runtime/SoundUtilities/Source/SoundUtilitiesEditor/Public/SoundUtilitiesEditorModule.h` (Public)


#### class `FSoundUtilitiesEditorModule`  
`class FSoundUtilitiesEditorModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private prototype_ `void RegisterMenus();`

### `Plugins/Runtime/SoundUtilities/Source/SoundUtilitiesEditor/Public/SoundWaveAssetActionExtender.h` (Public)


#### class `FSoundWaveAssetActionExtender`  
`class FSoundWaveAssetActionExtender`  
_L5-10_
- L8 _public prototype_ `static void RegisterMenus();`
- L9 _public prototype_ `static void ExecuteCreateSimpleSound(const struct FToolMenuContext& MenuContext);`
