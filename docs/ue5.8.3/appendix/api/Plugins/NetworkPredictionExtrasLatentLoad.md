# Plugins / NetworkPredictionExtrasLatentLoad

- module root: `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtrasLatentLoad`
- headers: 1; symbols: 5
- symbol kinds: class=2, function=3
- PrivateDependencyModuleNames: Engine, TraceLog, UnrealEd
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, Engine, InputCore, NetworkPrediction, PhysicsCore, RenderCore

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtrasLatentLoad/Public/NetworkPredictionExtrasLatentLoadModule.h` (Public)


#### class `INetworkPredictionExtrasLatentLoadModule`  
`class INetworkPredictionExtrasLatentLoadModule : public IModuleInterface`  
_L14-28_
- inherits: `IModuleInterface`
- L19 _public function_ `static inline INetworkPredictionExtrasLatentLoadModule& Get()`
- L24 _public function_ `static inline bool IsAvailable()`

#### class `UNetworkPredictionExtrasLatentLoadStubObject`  
`class UNetworkPredictionExtrasLatentLoadStubObject : public UObject`  
_L32-37_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Required stub object for unloading (non abandoning) module
- L36 _private function_ `UNetworkPredictionExtrasLatentLoadStubObject()`
