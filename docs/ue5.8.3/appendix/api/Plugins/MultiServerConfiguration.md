# Plugins / MultiServerConfiguration

- module root: `Plugins/Runtime/MultiServerReplication/Source/MultiServerConfiguration`
- headers: 2; symbols: 7
- symbol kinds: class=2, function=4, member=1
- PrivateDependencyModuleNames: Core, CoreUObject

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerConfiguration/Public/MultiServerConfigurationModule.h` (Public)


#### class `FMultiServerConfigurationModule`  
`class FMultiServerConfigurationModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- desc: See MultiServerNode for more details about multi-server networking as a whole.
- L12 _public function_ `FMultiServerConfigurationModule()`
- L13 _public function_ `virtual ~FMultiServerConfigurationModule()`
- L16 _public function_ `virtual bool SupportsDynamicReloading() override` — IModuleInterface
- L17 _public function_ `virtual bool SupportsAutomaticShutdown() override`

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerConfiguration/Public/MultiServerSettings.h` (Public)


#### class `UMultiServerSettings`  
`class UMultiServerSettings : public UObject`  
_L15-23_
- reflection: `UCLASS(Config=Game)`
- inherits: `UObject`
- desc: Settings that control how a multi-server setup is configured and launched. For example, to define 4 servers in a Game ini file it might look like this: [/Script/MultiServerConfiguration.MultiServerSettings] TotalNumServers=4
- L22 _private member_ `int32 TotalNumServers = 0;` — `UPROPERTY(Config)` — This is read from the LaunchMultiServer script (not code). We take the runtime value from -MultiServerNumServers parameter.
