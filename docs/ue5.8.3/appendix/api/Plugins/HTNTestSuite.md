# Plugins / HTNTestSuite

- module root: `Plugins/AI/HTNPlanner/Source/HTNTestSuite`
- headers: 2; symbols: 23
- symbol kinds: class=2, enum=2, enumerator=17, function=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, AITestSuite, Core, CoreUObject, Engine, HTNPlanner

### `Plugins/AI/HTNPlanner/Source/HTNTestSuite/Private/MockHTN.h` (Private)


#### enum `EMockHTNWorldState`  
`enum class EMockHTNWorldState : uint8`  
_L8-21_
- L10 _public enumerator_ `EnemyHealth`
- L11 _public enumerator_ `EnemyActor`
- L12 _public enumerator_ `Ammo`
- L13 _public enumerator_ `AbilityRange`
- L14 _public enumerator_ `HasWeapon`
- L15 _public enumerator_ `MoveDestination`
- L16 _public enumerator_ `PickupLocation`
- L17 _public enumerator_ `CurrentLocation`
- L18 _public enumerator_ `CanSeeEnemy`
- L20 _public enumerator_ `MAX`

#### enum `EMockHTNTaskOperator`  
`enum class EMockHTNTaskOperator : uint8`  
_L23-33_
- L25 _public enumerator_ `DummyOperation`
- L26 _public enumerator_ `FindPatrolPoint`
- L27 _public enumerator_ `FindWeapon`
- L28 _public enumerator_ `NavigateTo`
- L29 _public enumerator_ `PickUp`
- L30 _public enumerator_ `UseWeapon`
- L32 _public enumerator_ `MAX`

#### class `UMockHTNComponent`  
`class UMockHTNComponent : public UHTNBrainComponent`  
_L36-42_
- reflection: `UCLASS()`
- inherits: `UHTNBrainComponent`

### `Plugins/AI/HTNPlanner/Source/HTNTestSuite/Public/HTNTestSuiteModule.h` (Public)


#### class `IHTNTestSuiteModule`  
`class IHTNTestSuiteModule : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public function_ `static inline IHTNTestSuiteModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
