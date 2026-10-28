# Plugins / ZoneGraphTestSuite

- module root: `Plugins/Runtime/ZoneGraph/Source/ZoneGraphTestSuite`
- headers: 1; symbols: 3
- symbol kinds: class=1, function=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, AITestSuite, Core, CoreUObject, Engine, ZoneGraph

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphTestSuite/Public/ZoneGraphTestSuite.h` (Public)


#### class `IZoneGraphTestSuite`  
`class IZoneGraphTestSuite : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public function_ `static inline IZoneGraphTestSuite& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
