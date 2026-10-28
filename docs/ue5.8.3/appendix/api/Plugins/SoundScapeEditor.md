# Plugins / SoundScapeEditor

- module root: `Plugins/Runtime/Soundscape/Source/SoundScapeEditor`
- headers: 5; symbols: 19
- symbol kinds: class=5, function=10, prototype=4
- PrivateDependencyModuleNames: AssetDefinition, CoreUObject, Engine, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: AudioMixer, Core, Soundscape

### `Plugins/Runtime/Soundscape/Source/SoundScapeEditor/Private/AssetDefinition_SoundScapeColor.h` (Private)


#### class `UAssetDefinition_SoundScapeColor`  
`class UAssetDefinition_SoundScapeColor : public UAssetDefinitionDefault`  
_L9-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/Soundscape/Source/SoundScapeEditor/Private/AssetDefinition_SoundScapePalette.h` (Private)


#### class `UAssetDefinition_SoundScapePalette`  
`class UAssetDefinition_SoundScapePalette : public UAssetDefinitionDefault`  
_L9-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/Soundscape/Source/SoundScapeEditor/Private/SoundScapePaletteFactory.h` (Private)


#### class `USoundscapePaletteFactory`  
`class USoundscapePaletteFactory : public UFactory`  
_L9-21_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L14 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L16 _private function_ `virtual bool ShouldShowInNewMenu() const override`

### `Plugins/Runtime/Soundscape/Source/SoundScapeEditor/Private/SoundscapeColorFactory.h` (Private)


#### class `USoundscapeColorFactory`  
`class USoundscapeColorFactory : public UFactory`  
_L9-21_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L14 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L16 _private function_ `virtual bool ShouldShowInNewMenu() const override`

### `Plugins/Runtime/Soundscape/Source/SoundScapeEditor/Public/SoundScapeEditorModule.h` (Public)


#### class `FSoundscapeEditorModule`  
`class FSoundscapeEditorModule : public IModuleInterface`  
_L9-17_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L15 _public prototype_ `virtual void ShutdownModule() override;`
