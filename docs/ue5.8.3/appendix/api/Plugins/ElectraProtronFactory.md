# Plugins / ElectraProtronFactory

- module root: `Plugins/Media/ElectraPlayer/Source/ElectraProtronFactory`
- headers: 2; symbols: 5
- symbol kinds: class=1, delegate=1, member=2, prototype=1
- DynamicallyLoadedModuleNames: ElectraProtron, Media, Settings
- PrivateDependencyModuleNames: ElectraBase, MediaAssets
- PrivateIncludePathModuleNames: ElectraProtron, Media, Settings
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Media/ElectraPlayer/Source/ElectraProtronFactory/Private/ElectraProtronFactoryPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraProtronFactory, Log, All);` — Log category
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraProtronFactory, Log, All);` — Log category

### `Plugins/Media/ElectraPlayer/Source/ElectraProtronFactory/Private/ElectraProtronFactorySettings.h` (Private)


#### class `UElectraProtronFactorySettings`  
`class UElectraProtronFactorySettings : public UObject`  
_L11-23_
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- desc: Settings for the Electra Protron Factory module.
- L18 _public member_ `bool bPreferProtronInEditor = false;` — `UPROPERTY(config, EditAnywhere, Category=General)` — When the media source leaves the player selection to automatic, Protron will be used instead of Electra in editor.
- L22 _public member_ `bool bPreferProtronInGame = false;` — `UPROPERTY(config, EditAnywhere, Category=General)` — When the media source leaves the player selection to automatic, Protron will be used instead of Electra in game.
