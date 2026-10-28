# Plugins / MediaProfileEditor

- module root: `Plugins/Media/MediaProfile/Source/MediaProfileEditor`
- headers: 10; symbols: 52
- symbol kinds: class=9, delegate=1, function=9, macro=2, member=3, namespace=3, prototype=25
- PrivateDependencyModuleNames: AssetDefinition, CoreUObject, Engine, MediaAssets, MediaIOCore, MediaIOEditor, MediaPlayerEditor, MediaProfile, Projects, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Media/MediaProfile/Source/MediaProfileEditor/Private/AssetDefinition/AssetDefinition_ProxyMediaOutput.h` (Private)


#### class `UAssetDefinition_ProxyMediaOutput`  
`class UAssetDefinition_ProxyMediaOutput : public UAssetDefinition_MediaOutput`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaOutput`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/MediaProfile/Source/MediaProfileEditor/Private/AssetDefinition/AssetDefinition_ProxyMediaSource.h` (Private)


#### class `UAssetDefinition_ProxyMediaSource`  
`class UAssetDefinition_ProxyMediaSource : public UAssetDefinition_MediaSource`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaSource`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/MediaProfile/Source/MediaProfileEditor/Private/Factories/MediaProfileFactoryNew.h` (Private)


#### class `UMediaProfileFactoryNew`  
`class UMediaProfileFactoryNew : public UFactory`  
_L12-24_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UMediaProfileFactoryNew objects.
- L21 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L22 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L23 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/MediaProfile/Source/MediaProfileEditor/Private/Factories/ProxyMediaOutputFactoryNew.h` (Private)


#### class `UProxyMediaOutputFactoryNew`  
`class UProxyMediaOutputFactoryNew : public UFactory`  
_L12-24_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UProxyMediaOutput objects.
- L21 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L22 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L23 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/MediaProfile/Source/MediaProfileEditor/Private/Factories/ProxyMediaSourceFactoryNew.h` (Private)


#### class `UProxyMediaSourceFactoryNew`  
`class UProxyMediaSourceFactoryNew : public UFactory`  
_L12-24_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UProxyMediaSource objects.
- L21 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L22 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L23 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/MediaProfile/Source/MediaProfileEditor/Private/MediaProfileEditorModule.h` (Private)


#### class `FMediaProfileEditorModule`  
`class FMediaProfileEditorModule : public IMediaProfileEditorModule`  
_L9-19_
- inherits: `IMediaProfileEditorModule`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _public function_ `virtual TSharedPtr<FExtender> GetMediaProfileMenuExtender() const override`
- L18 _private member_ `TSharedPtr<FExtender> MediaProfileMenuExtender;`

### `Plugins/Media/MediaProfile/Source/MediaProfileEditor/Private/UI/MediaProfileEditorStyle.h` (Private)


#### class `FMediaProfileEditorStyle`  
`class FMediaProfileEditorStyle : public FSlateStyleSet`  
_L7-17_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `static FMediaProfileEditorStyle& Get();`
- L12 _public prototype_ `void Register();`
- L13 _public prototype_ `void Unregister();`
- L16 _private prototype_ `FMediaProfileEditorStyle();`

### `Plugins/Media/MediaProfile/Source/MediaProfileEditor/Public/IMediaProfileEditorModule.h` (Public)


#### class `IMediaProfileEditorModule`  
`class IMediaProfileEditorModule : public IModuleInterface`  
_L10-21_
- inherits: `IModuleInterface`
- L13 _public function_ `static IMediaProfileEditorModule& Get()`
- L20 _public prototype_ `virtual TSharedPtr<FExtender> GetMediaProfileMenuExtender() const = 0;` — Gets a menu extender that allows the media profile toolbar/dropdown menu to be extended

### `Plugins/Media/MediaProfile/Source/MediaProfileEditor/Public/MediaProfileMenus.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MEDIAPROFILEEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MediaProfile` (scope `UE`)
- L12 _namespace_ `namespace Menus` (scope `UE::MediaProfile`)
- L18 _prototype_ `void OpenExistingOrCreateNewMediaProfile();` (scope `UE::MediaProfile::Menus`) — If there is an existing media profile set as the current profile, opens that media profile in the media profile editor. Otherwise, opens the asset creation dialog box to allow users to create a new media profile asset
- L21 _prototype_ `TSharedRef<SWidget> GenerateMediaProfileDropdownMenu();` (scope `UE::MediaProfile::Menus`) — Creates a dropdown menu widget populated with contents related to the current media profile
- L24 _prototype_ `TSharedRef<SWidget> CreateMediaProfileToolBarButton(const FText& InToolTipText = FText::GetEmpty());` (scope `UE::MediaProfile::Menus`) — Creates a toolbar dropdown button widget populated with contents related to the current media profile

### `Plugins/Media/MediaProfile/Source/MediaProfileEditor/Public/SMediaProfileSourceTexturePicker.h` (Public)


#### class `SMediaProfileSourceTexturePicker`  
`class SMediaProfileSourceTexturePicker : public SObjectPropertyEntryBox`  
_L14-58_
- inherits: `SObjectPropertyEntryBox`
- desc: A SObjectPropertyEntryBox for picking a texture that adds a dropdown for picking the media texture from a media source in the active media profile
- L17 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnMediaSourceSelected, UMediaProfile* , int32 );`
- L20 _public function_ `SLATE_BEGIN_ARGS(SMediaProfileSourceTexturePicker) : _AllowedClass(nullptr)`
- L23 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, TexturePropertyHandle) SLATE_ARGUMENT(TSharedPtr<FAssetThumbnailPool>, ThumbnailPool) SLATE_ARGUMENT(UClass*, AllowedClass) SLATE_EVENT(FOnShouldFilterAsset, OnShouldFilterAsset) SLATE_EVENT(FOnMediaSourceSelected, OnMediaSourceSelected) SLATE_NAMED_SLOT(FArguments, AdditionalContent) SLATE_ARGUMENT(bool, AdditionalContentBeforeMediaButton) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L41 _private prototype_ `TSharedRef<SWidget> GetMediaProfileSourceSelectorMenu();` — Constructs the dropdown menu that shows all the media sources in the active media profile
- L44 _private prototype_ `bool HasActiveMediaProfile() const;` — Gets whether there is a valid active media profile
- L47 _private prototype_ `void SetTextureToMediaProfileSource(int32 InMediaSourceIndex);` — Raised when the user has selected a media source whose media texture should be used from the media sources dropdown
- L50 _private prototype_ `void OpenMediaProfile();` — Opens the active media profile in the media profile editor
- L54 _private member_ `TSharedPtr<IPropertyHandle> TexturePropertyHandle;` — The property handle to store the texture in
- L57 _private member_ `FOnMediaSourceSelected OnMediaSourceSelected;` — Raised when a media source is selected

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MEDIAPROFILEEDITOR_API`
- L17 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMediaSourceSelected, UMediaProfile* , int32 );`
