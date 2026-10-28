# Runtime / BlueprintRuntime

- module root: `Source/Runtime/BlueprintRuntime`
- headers: 2; symbols: 14
- symbol kinds: class=2, enum=1, enumerator=3, function=1, member=4, prototype=2, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/BlueprintRuntime/Public/BlueprintRuntime.h` (Public)


#### class `IBlueprintRuntime`  
`class IBlueprintRuntime : public IModuleInterface`  
_L14-30_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline IBlueprintRuntime& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L28 _public prototype_ `virtual void PropagateWarningSettings() = 0;`
- L29 _public prototype_ `virtual UBlueprintRuntimeSettings* GetMutableBlueprintRuntimeSettings() = 0;`

### `Source/Runtime/BlueprintRuntime/Public/BlueprintRuntimeSettings.h` (Public)


#### enum `EBlueprintWarningBehavior`  
`enum class EBlueprintWarningBehavior : uint8`  
_L19-24_
- reflection: `UENUM()`
- L21 _public enumerator_ `Warn`
- L22 _public enumerator_ `Error`
- L23 _public enumerator_ `Suppress`

#### struct `FBlueprintWarningSettings`  
`struct FBlueprintWarningSettings`  
_L27-39_
- reflection: `USTRUCT()`
- L32 _public member_ `FName WarningIdentifier;` — `UPROPERTY()`
- L35 _public member_ `FText WarningDescription;` — `UPROPERTY()`
- L38 _public member_ `EBlueprintWarningBehavior WarningBehavior = EBlueprintWarningBehavior::Warn;` — `UPROPERTY()`

#### class `UBlueprintRuntimeSettings`  
`class UBlueprintRuntimeSettings : public UObject`  
_L45-51_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the BlueprintRuntime module
- L50 _private member_ `TArray<FBlueprintWarningSettings> WarningSettings;` — `UPROPERTY(EditAnywhere, config, Category = Warnings)`
