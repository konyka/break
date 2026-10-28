# Runtime / ClientPilot

- module root: `Source/Runtime/ClientPilot`
- headers: 3; symbols: 21
- symbol kinds: class=3, function=2, member=3, prototype=13
- DynamicallyLoadedModuleNames: AutomationController
- PrivateDependencyModuleNames: Core, CoreUObject
- PublicIncludePathModuleNames: AutomationController, AutomationTest

### `Source/Runtime/ClientPilot/Public/ClientPilotBlackboard.h` (Public)


#### class `UClientPilotBlackboard`  
`class UClientPilotBlackboard : public UObject`  
_L14-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L18 _public prototype_ `virtual void InitializeFromProfile(FString CategoryToUse);`
- L20 _public prototype_ `void AddOrUpdateValue(FString KeyName, float Value);`
- L21 _public prototype_ `void AddOrUpdateValue(FString KeyName, int Value);`
- L22 _public prototype_ `void AddOrUpdateValue(FString KeyName, FString Value);`
- L23 _public prototype_ `void AddOrUpdateValue(FString KeyName, FVector Value);`
- L25 _public prototype_ `FString GetStringValue(FString KeyName);`
- L26 _public prototype_ `int GetIntValue(FString KeyName);`
- L27 _public prototype_ `float GetFloatValue(FString KeyName);`
- L28 _public prototype_ `FVector GetVectorValue(FString KeyName);`
- L30 _public function_ `void RemoveKey(FString Key)`
- L34 _public function_ `void ResetBlackboard()`
- L40 _protected member_ `TMap<FString, FString> Blackboard;`

### `Source/Runtime/ClientPilot/Public/ClientPilotBlackboardManager.h` (Public)


#### class `UClientPilotBlackboardManager`  
`class UClientPilotBlackboardManager : public UObject`  
_L16-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L20 _protected member_ `static UClientPilotBlackboardManager * ObjectInstance;`
- L23 _public prototype_ `static UClientPilotBlackboardManager * GetInstance();`
- L25 _public member_ `TObjectPtr<UClientPilotBlackboard> PilotBlackboard;` — `UPROPERTY()`

### `Source/Runtime/ClientPilot/Public/ClientPilotComponent.h` (Public)


#### class `UClientPilotComponent`  
`class UClientPilotComponent : public UObject`  
_L14-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L18 _public prototype_ `UClientPilotComponent();`
- L19 _public prototype_ `UClientPilotBlackboard* GetBlackboardInstance();`
- L20 _public prototype_ `virtual void ThinkAndAct();`
