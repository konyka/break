# Plugins / AvfMediaFactory

- module root: `Plugins/Media/AvfMedia/Source/AvfMediaFactory`
- headers: 2; symbols: 6
- symbol kinds: class=1, delegate=1, macro=1, member=1, prototype=2
- DynamicallyLoadedModuleNames: AvfMedia, Media, Settings
- PrivateDependencyModuleNames: MediaAssets
- PrivateIncludePathModuleNames: AvfMedia, Media, Settings
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Media/AvfMedia/Source/AvfMediaFactory/Private/AvfMediaFactoryPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvfMediaFactory, Log, All);` — Log category for the AvfMedia module.
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvfMediaFactory, Log, All);` — Log category for the AvfMedia module.

### `Plugins/Media/AvfMedia/Source/AvfMediaFactory/Public/AvfMediaSettings.h` (Public)


#### class `UAvfMediaSettings`  
`class UAvfMediaSettings : public UObject`  
_L17-32_
- reflection: `UCLASS(MinimalAPI, config=Engine)`
- inherits: `UObject`
- desc: Settings for the AvfMedia plug-in.
- L25 _public prototype_ `UAvfMediaSettings();` — Default constructor.
- L31 _public member_ `bool NativeAudioOut;` — `UPROPERTY(config, EditAnywhere, Category=Debug)` — Play audio tracks via the operating system's native sound mixer.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AVFMEDIAFACTORY_API`
