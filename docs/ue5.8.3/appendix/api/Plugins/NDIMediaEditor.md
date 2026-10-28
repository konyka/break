# Plugins / NDIMediaEditor

- module root: `Plugins/Media/NDIMedia/Source/NDIMediaEditor`
- headers: 6; symbols: 25
- symbol kinds: class=5, delegate=1, function=5, prototype=14
- PrivateDependencyModuleNames: AssetDefinition, MediaPlayerEditor, Projects
- PrivateIncludePathModuleNames: AssetTools, TargetPlatform
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MediaIOCore, MediaIOEditor, NDIMedia, Slate, SlateCore, TimeManagement, UnrealEd

### `Plugins/Media/NDIMedia/Source/NDIMediaEditor/Private/AssetDefinition/AssetDefinition_NDIMediaOutput.h` (Private)


#### class `UAssetDefinition_NDIMediaOutput`  
`class UAssetDefinition_NDIMediaOutput : public UAssetDefinitionDefault`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Media/NDIMedia/Source/NDIMediaEditor/Private/AssetDefinition/AssetDefinition_NDIMediaSource.h` (Private)


#### class `UAssetDefinition_NDIMediaSource`  
`class UAssetDefinition_NDIMediaSource : public UAssetDefinition_MediaSource`  
_L9-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaSource`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override` — From NDI Brand Guidelines: #6257FF
- L17 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L18 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/NDIMedia/Source/NDIMediaEditor/Private/Customization/NDIMediaSettingsCustomization.h` (Private)


#### class `FNDIMediaSettingsCustomization`  
`class FNDIMediaSettingsCustomization : public IDetailCustomization`  
_L10-30_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L23 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Creates an instance of this class. @return The new instance.
- L29 _private prototype_ `FReply OnButtonClicked();`

### `Plugins/Media/NDIMedia/Source/NDIMediaEditor/Private/NDIMediaEditorModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNDIMediaEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNDIMediaEditor, Log, All);`

### `Plugins/Media/NDIMedia/Source/NDIMediaEditor/Private/NDIMediaOutputFactory.h` (Private)


#### class `UNDIMediaOutputFactory`  
`class UNDIMediaOutputFactory : public UFactory`  
_L13-21_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Implements a factory for UNDIMediaOutputFactory objects.
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L19 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L20 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/NDIMedia/Source/NDIMediaEditor/Private/NDIMediaSourceFactory.h` (Private)


#### class `UNDIMediaSourceFactory`  
`class UNDIMediaSourceFactory : public UFactory`  
_L12-24_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Implements a factory for UNDIMediaSource objects.
- L17 _public prototype_ `UNDIMediaSourceFactory(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`
- L21 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L22 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
