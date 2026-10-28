# Plugins / BlackmagicMediaEditor

- module root: `Plugins/Media/BlackmagicMedia/Source/BlackmagicMediaEditor`
- headers: 4; symbols: 16
- symbol kinds: class=4, function=6, prototype=6
- PrivateDependencyModuleNames: AssetDefinition, BlackmagicMedia, BlackmagicMediaOutput, Engine, MediaAssets, MediaIOEditor, MediaPlayerEditor, Projects, SlateCore
- PrivateIncludePathModuleNames: AssetTools
- PublicDependencyModuleNames: Core, CoreUObject, EditorFramework, MediaIOCore, UnrealEd

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMediaEditor/Private/AssetDefinition/AssetDefinition_BlackmagicMediaOutput.h` (Private)


#### class `UAssetDefinition_BlackmagicMediaOutput`  
`class UAssetDefinition_BlackmagicMediaOutput : public UAssetDefinition_MediaOutput`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaOutput`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMediaEditor/Private/AssetDefinition/AssetDefinition_BlackmagicMediaSource.h` (Private)


#### class `UAssetDefinition_BlackmagicMediaSource`  
`class UAssetDefinition_BlackmagicMediaSource : public UAssetDefinition_MediaSource`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaSource`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMediaEditor/Private/Factories/BlackmagicMediaOutputFactoryNew.h` (Private)


#### class `UBlackmagicMediaOutputFactoryNew`  
`class UBlackmagicMediaOutputFactoryNew : public UFactory`  
_L13-22_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for objects.
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L21 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMediaEditor/Private/Factories/BlackmagicMediaSourceFactoryNew.h` (Private)


#### class `UBlackmagicMediaSourceFactoryNew`  
`class UBlackmagicMediaSourceFactoryNew : public UFactory`  
_L13-25_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for objects.
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L24 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
