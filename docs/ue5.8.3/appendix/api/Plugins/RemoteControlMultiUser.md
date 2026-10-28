# Plugins / RemoteControlMultiUser

- module root: `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlMultiUser`
- headers: 1; symbols: 3
- symbol kinds: class=1, prototype=2
- PrivateDependencyModuleNames: ConcertSyncClient, Core, CoreUObject, RemoteControl
- PublicDependencyModuleNames: 

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlMultiUser/Private/RemoteControlMultiUserModule.h` (Private)


#### class `FRemoteControlMultiUserModule`  
`class FRemoteControlMultiUserModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- desc: Implements a simple Remote Control Multiuser module to register our own transaction filter.
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
