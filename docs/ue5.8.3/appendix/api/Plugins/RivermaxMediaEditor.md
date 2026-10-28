# Plugins / RivermaxMediaEditor

- module root: `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMediaEditor`
- headers: 7; symbols: 35
- symbol kinds: class=7, function=7, prototype=21
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, Core, CoreUObject, DisplayClusterModularFeaturesEditor, EditorStyle, Engine, InputCore, MediaAssets, MediaIOCore, MediaIOEditor, MediaPlayerEditor, RivermaxCore, RivermaxEditor, RivermaxMedia, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMediaEditor/Private/AssetDefinition/AssetDefinition_RivermaxMediaOutput.h` (Private)


#### class `UAssetDefinition_RivermaxMediaOutput`  
`class UAssetDefinition_RivermaxMediaOutput : public UAssetDefinition_MediaOutput`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaOutput`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMediaEditor/Private/AssetDefinition/AssetDefinition_RivermaxMediaSource.h` (Private)


#### class `UAssetDefinition_RivermaxMediaSource`  
`class UAssetDefinition_RivermaxMediaSource : public UAssetDefinition_MediaSource`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaSource`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMediaEditor/Private/Customization/RivermaxMediaDetailsCustomization.h` (Private)


#### class `FRivermaxMediaDetailsCustomization`  
`class FRivermaxMediaDetailsCustomization : public IDetailCustomization`  
_L11-25_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L24 _private prototype_ `FReply OnExportSDP(URivermaxMediaOutput* Output);` — Shows up a path selection dialog and exports SDP there. Currently only works in Media Output and not in ndisplay.

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMediaEditor/Private/Customization/RivermaxMediaPropertyCustomization.h` (Private)


#### class `FRivermaxStreamCustomization`  
`class FRivermaxStreamCustomization : public IPropertyTypeCustomization`  
_L7-20_
- inherits: `IPropertyTypeCustomization`
- L10 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization
- L18 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMediaEditor/Private/ModularFeatures/RivermaxMediaInitializerFeature.h` (Private)


#### class `FRivermaxMediaInitializerFeature`  
`class FRivermaxMediaInitializerFeature : public IDisplayClusterModularFeatureMediaInitializer`  
_L12-35_
- inherits: `IDisplayClusterModularFeatureMediaInitializer`
- desc: Rivermax media source/output initializer for nDisplay
- L18 _public prototype_ `virtual bool IsMediaObjectSupported(const UObject* MediaObject) override;`
- L19 _public prototype_ `virtual bool AreMediaObjectsCompatible(const UObject* MediaSource, const UObject* MediaOutput) override;`
- L20 _public prototype_ `virtual bool GetSupportedMediaPropagationTypes(const UObject* MediaSource, const UObject* MediaOutput, EMediaStreamPropagationType& OutPropagationTypes) override;`
- L21 _public prototype_ `virtual void InitializeMediaObjectForTile(UObject* MediaObject, const FMediaObjectOwnerInfo& OnwerInfo, const FIntPoint& TilePos) override;`
- L22 _public prototype_ `virtual void InitializeMediaObjectForFullFrame(UObject* MediaObject, const FMediaObjectOwnerInfo& OnwerInfo) override;`
- L28 _private prototype_ `FString GetRivermaxInterfaceAddress() const;` — Returns first interface address if available
- L31 _private prototype_ `FString GenerateStreamAddress(uint8 OwnerUniqueIdx, const FIntPoint& TilePos) const;` — Generates stream address based on the function parameters
- L34 _private prototype_ `FString GenerateStreamAddress(uint8 ClusterNodeUniqueIdx, uint8 OwnerUniqueIdx, const FMediaObjectOwnerInfo::EMediaObjectOwnerType OwnerType) const;` — Generates stream address based on the function parameters

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMediaEditor/Private/RivermaxMediaOutputFactoryNew.h` (Private)


#### class `URivermaxMediaOutputFactoryNew`  
`class URivermaxMediaOutputFactoryNew : public UFactory`  
_L15-27_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for URivermaxMediaOutput objects.
- L21 _public prototype_ `URivermaxMediaOutputFactoryNew();`
- L24 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L25 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L26 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMediaEditor/Private/RivermaxMediaSourceFactoryNew.h` (Private)


#### class `URivermaxMediaSourceFactoryNew`  
`class URivermaxMediaSourceFactoryNew : public UFactory`  
_L13-27_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for URivermaxMediaSource objects.
- L20 _public prototype_ `URivermaxMediaSourceFactoryNew();`
- L24 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L25 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L26 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
