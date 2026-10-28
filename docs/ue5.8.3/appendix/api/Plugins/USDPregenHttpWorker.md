# Plugins / USDPregenHttpWorker

- module root: `Plugins/Experimental/USDPregen/Source/USDPregenHttpWorker`
- headers: 1; symbols: 4
- symbol kinds: class=1, member=1, prototype=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Engine, HTTP, HTTPServer, Json, JsonUtilities, USDPregenInterchange
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/USDPregen/Source/USDPregenHttpWorker/Public/USDPregenHttpWorker.h` (Public)


#### class `FUSDPregenHttpWorkerModule`  
`class FUSDPregenHttpWorkerModule final : public IModuleInterface`  
_L16-25_
- inherits: `IModuleInterface`
- desc: Headless worker for UsdPregen-based imports.
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _private member_ `TSharedPtr<struct FUSDPregenWorkerState, ESPMode::ThreadSafe> State;`
