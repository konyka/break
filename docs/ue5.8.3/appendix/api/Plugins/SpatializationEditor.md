# Plugins / SpatializationEditor

- module root: `Plugins/Runtime/Spatialization/Source/SpatializationEditor`
- headers: 3; symbols: 11
- symbol kinds: class=3, function=4, prototype=4
- PrivateDependencyModuleNames: AssetDefinition, AudioMixer, CoreUObject, EditorFramework, Engine, LevelEditor, Spatialization, UnrealEd
- PrivateIncludePathModuleNames: TargetPlatform
- PublicDependencyModuleNames: AudioEditor, Core

### `Plugins/Runtime/Spatialization/Source/SpatializationEditor/Private/AssetDefinition_ITDSpatializationSettings.h` (Private)


#### class `UAssetDefinition_ITDSpatializationSettings`  
`class UAssetDefinition_ITDSpatializationSettings : public UAssetDefinitionDefault`  
_L9-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/Spatialization/Source/SpatializationEditor/Public/ITDSpatializationSourceSettingsFactory.h` (Public)


#### class `UITDSpatializationSettingsFactory`  
`class UITDSpatializationSettingsFactory : public UFactory`  
_L11-19_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L15 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L18 _private prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/Runtime/Spatialization/Source/SpatializationEditor/Public/SpatializationEditorModule.h` (Public)


#### class `FSpatializationEditorModule`  
`class FSpatializationEditorModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
