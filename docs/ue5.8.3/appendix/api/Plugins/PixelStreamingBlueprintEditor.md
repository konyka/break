# Plugins / PixelStreamingBlueprintEditor

- module root: `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprintEditor`
- headers: 4; symbols: 18
- symbol kinds: class=4, function=1, prototype=13
- PrivateDependencyModuleNames: AssetDefinition, Core, CoreUObject, PixelStreaming, PixelStreamingBlueprint, PixelStreamingEditor, SlateCore, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprintEditor/Private/AssetDefinition_StreamerVideoInput.h` (Private)


#### class `UAssetDefinition_StreamerVideoInput`  
`class UAssetDefinition_StreamerVideoInput : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public function_ `virtual void BuildFilters(TArray<FAssetFilterData>& OutFilters) const override`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprintEditor/Private/PixelStreamingStreamerVideoInputBackBufferFactory.h` (Private)


#### class `UPixelStreamingStreamerVideoInputBackBufferFactory`  
`class UPixelStreamingStreamerVideoInputBackBufferFactory : public UFactory`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L17 _public prototype_ `virtual FText GetDisplayName() const override;`
- L18 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprintEditor/Private/PixelStreamingStreamerVideoInputMediaCaptureFactory.h` (Private)


#### class `UPixelStreamingStreamerVideoInputMediaCaptureFactory`  
`class UPixelStreamingStreamerVideoInputMediaCaptureFactory : public UFactory`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L17 _public prototype_ `virtual FText GetDisplayName() const override;`
- L18 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprintEditor/Private/PixelStreamingStreamerVideoInputRenderTargetFactory.h` (Private)


#### class `UPixelStreamingStreamerVideoInputRenderTargetFactory`  
`class UPixelStreamingStreamerVideoInputRenderTargetFactory : public UFactory`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L17 _public prototype_ `virtual FText GetDisplayName() const override;`
- L18 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
