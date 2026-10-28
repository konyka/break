# Runtime / ChaosVehiclesEngine

- module root: `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesEngine`
- headers: 2; symbols: 6
- symbol kinds: class=2, function=3, prototype=1
- PublicDependencyModuleNames: Chaos, ChaosVehiclesCore, Core, CoreUObject, Engine, RHI, RenderCore

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesEngine/Public/ChaosVehicles.h` (Public)


#### class `UChaosVehicles`  
`class UChaosVehicles : public UObject`  
_L17-24_
- reflection: `UCLASS(customconstructor)`
- inherits: `UObject`
- desc: UChaosVehicles (UObject)
- L22 _public prototype_ `UChaosVehicles(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L23 _public function_ `bool IsVisible()`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesEngine/Public/ChaosVehiclesEngineModule.h` (Public)


#### class `FChaosVehiclesEngineModule`  
`class FChaosVehiclesEngineModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public function_ `virtual void StartupModule() override`
- L11 _public function_ `virtual void ShutdownModule() override`
