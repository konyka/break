# Plugins / MoverIntegrations

- module root: `Plugins/Experimental/MoverIntegrations/Source/MoverIntegrations`
- headers: 1; symbols: 3
- symbol kinds: class=1, prototype=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/MoverIntegrations/Source/MoverIntegrations/Public/MoverIntegrations.h` (Public)


#### class `FMoverIntegrationsModule`  
`class FMoverIntegrationsModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- desc: Module that serves as umbrella of a variety of integration modules between Mover and other systems (such as animation, AI, and other gameplay systems)
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`
