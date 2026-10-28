# Programs / ChaosPhysicsTests

- module root: `Source/Programs/ChaosPhysicsTests`
- headers: 3; symbols: 15
- symbol kinds: class=2, function=8, member=4, prototype=1
- PrivateDependencyModuleNames: ChaosTestHarness, Core, CoreUObject, Engine

### `Source/Programs/ChaosPhysicsTests/Private/ChaosTestHarness.h` (Private)
_(no declarations extracted)_

### `Source/Programs/ChaosPhysicsTests/Private/ChaosTestScene.h` (Private)
_(no declarations extracted)_

### `Source/Programs/ChaosPhysicsTests/Private/ScopedCVar.h` (Private)


#### class `FCVarSetter`  
`template<typename T> class FCVarSetter`  
_L7-39_
- L10 _public function_ `FCVarSetter(const FString& InConsoleVariableName) : ConsoleVariableName(InConsoleVariableName) , OriginalValue() , bIsSet(false)`
- L17 _public function_ `virtual ~FCVarSetter()`
- L21 _public prototype_ `void Set(T Value);`
- L23 _public function_ `void Restore()`
- L36 _private member_ `FString ConsoleVariableName;`
- L37 _private member_ `T OriginalValue;`
- L38 _private member_ `bool bIsSet;`
- L42 _function_ `template<> FORCEINLINE void FCVarSetter<bool>::Set(bool Value)`
- L54 _function_ `template<> FORCEINLINE void FCVarSetter<int32>::Set(int32 Value)`
- L66 _function_ `template<> FORCEINLINE void FCVarSetter<float>::Set(float Value)`

#### class `FCVarScopeGuard`  
`template<typename T> class FCVarScopeGuard`  
_L78-93_
- L81 _public function_ `FCVarScopeGuard(const FString& InConsoleVariableName, T InValue) : CVarSetter(InConsoleVariableName)`
- L87 _public function_ `~FCVarScopeGuard()`
- L92 _private member_ `FCVarSetter<T> CVarSetter;`
