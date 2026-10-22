# Plugins / AISupportModule

- module root: `Plugins/AI/AISupport/Source/AISupportModule`
- headers: 1; symbols: 3
- symbol kinds: class=1, function=2
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, NavigationSystem

### `Plugins/AI/AISupport/Source/AISupportModule/Public/AISupportModule.h` (Public)


#### class `IAISupportModule`  
`class IAISupportModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IAISupportModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
