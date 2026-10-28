# Plugins / LiveLinkMultiUser

- module root: `Plugins/Animation/LiveLink/Source/LiveLinkMultiUser`
- headers: 1; symbols: 3
- symbol kinds: class=1, prototype=2
- PrivateDependencyModuleNames: ConcertSyncClient, Core, CoreUObject, LiveLinkComponents
- PublicDependencyModuleNames: 

### `Plugins/Animation/LiveLink/Source/LiveLinkMultiUser/Private/LiveLinkMultiUserModule.h` (Private)


#### class `FLiveLinkMultiUserModule`  
`class FLiveLinkMultiUserModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- desc: Implements a simple LiveLink Multiuser module to register our own transaction filter.
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
