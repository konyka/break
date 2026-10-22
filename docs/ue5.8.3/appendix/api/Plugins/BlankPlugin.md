# Plugins / BlankPlugin

- module root: `Plugins/Developer/BlankPlugin/Source/BlankPlugin`
- headers: 1; symbols: 3
- symbol kinds: class=1, function=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core

### `Plugins/Developer/BlankPlugin/Source/BlankPlugin/Public/IBlankPlugin.h` (Public)


#### class `IBlankPlugin`  
`class IBlankPlugin : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IBlankPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
