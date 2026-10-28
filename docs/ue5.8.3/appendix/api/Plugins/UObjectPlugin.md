# Plugins / UObjectPlugin

- module root: `Plugins/Developer/UObjectPlugin/Source/UObjectPlugin`
- headers: 2; symbols: 7
- symbol kinds: class=2, function=2, member=2, struct=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Developer/UObjectPlugin/Source/UObjectPlugin/Classes/MyPluginObject.h` (Public)


#### struct `FMyPluginStruct`  
`struct FMyPluginStruct`  
_L15-21_
- reflection: `USTRUCT()`
- desc: Example UStruct declared in a plugin module
- L20 _public member_ `FString TestString;` — `UPROPERTY()`

#### class `UMyPluginObject`  
`class UMyPluginObject : public UObject`  
_L28-39_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Example of declaring a UObject in a plugin module
- L37 _private member_ `FMyPluginStruct MyStruct;` — `UPROPERTY()`

### `Plugins/Developer/UObjectPlugin/Source/UObjectPlugin/Public/IUObjectPlugin.h` (Public)


#### class `IUObjectPlugin`  
`class IUObjectPlugin : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IUObjectPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
