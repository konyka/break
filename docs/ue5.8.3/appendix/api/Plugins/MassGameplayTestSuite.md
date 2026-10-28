# Plugins / MassGameplayTestSuite

- module root: `Plugins/Runtime/MassGameplay/Source/MassGameplayTestSuite`
- headers: 1; symbols: 3
- symbol kinds: class=1, function=2
- PublicDependencyModuleNames: AITestSuite, Core, CoreUObject, Engine, MassCharacterTrajectory, MassCore, MassEntity, MassEntityTestSuite, MassLOD, MassMovement, MassSpawner, PoseSearch

### `Plugins/Runtime/MassGameplay/Source/MassGameplayTestSuite/Public/MassGameplayTestSuiteModule.h` (Public)


#### class `IMassGameplayTestSuiteModule`  
`class IMassGameplayTestSuiteModule : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IMassGameplayTestSuiteModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
