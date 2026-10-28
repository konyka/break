# Plugins / MassGameplayExternalTraits

- module root: `Plugins/Runtime/MassGameplay/Source/MassGameplayExternalTraits`
- headers: 2; symbols: 3
- symbol kinds: class=1, function=2
- PublicDependencyModuleNames: Core, MassCore, MassEntity

### `Plugins/Runtime/MassGameplay/Source/MassGameplayExternalTraits/Public/IMassGameplayExternalTraitsModule.h` (Public)


#### class `IMassGameplayExternalTraitsModule`  
`class IMassGameplayExternalTraitsModule : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L24 _public function_ `static inline IMassGameplayExternalTraitsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassGameplayExternalTraits/Public/MassGameplayExternalTraits.h` (Public)
_(no declarations extracted)_
