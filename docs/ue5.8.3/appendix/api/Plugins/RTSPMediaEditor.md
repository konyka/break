# Plugins / RTSPMediaEditor

- module root: `Plugins/Media/RTSPMedia/Source/RTSPMediaEditor`
- headers: 2; symbols: 10
- symbol kinds: class=2, function=4, prototype=4
- PrivateDependencyModuleNames: AssetDefinition, Core, CoreUObject, MediaPlayerEditor, Projects, RTSPMedia, Slate, SlateCore, UnrealEd

### `Plugins/Media/RTSPMedia/Source/RTSPMediaEditor/Private/AssetDefinition/AssetDefinition_RtspMediaSource.h` (Private)


#### class `UAssetDefinition_RtspMediaSource`  
`class UAssetDefinition_RtspMediaSource : public UAssetDefinition_MediaSource`  
_L9-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaSource`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/RTSPMedia/Source/RTSPMediaEditor/Private/RtspMediaSourceFactory.h` (Private)


#### class `URtspMediaSourceFactory`  
`class URtspMediaSourceFactory : public UFactory`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _public prototype_ `URtspMediaSourceFactory(const FObjectInitializer& ObjectInitializer);`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`
- L19 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L20 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
