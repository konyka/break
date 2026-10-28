# Plugins / MSGamingRuntime

- module root: `Plugins/Runtime/Windows/MSGamingRuntime/Source/MSGamingRuntime`
- headers: 1; symbols: 3
- symbol kinds: class=1, function=1, prototype=1
- PrivateDependencyModuleNames: UnrealEd

### `Plugins/Runtime/Windows/MSGamingRuntime/Source/MSGamingRuntime/Public/MSGamingRuntimeModule.h` (Public)


#### class `IMSGamingRuntimeModule`  
`class IMSGamingRuntimeModule : public IModuleInterface`  
_L9-26_
- inherits: `IModuleInterface`
- L16 _public function_ `static inline IMSGamingRuntimeModule& Get()` — Singleton-like access to the MS Gaming Runtime module instance @return Returns IMSGamingRuntimeModule singleton instance, loading the module on demand if needed
- L25 _public prototype_ `virtual bool IsAvailable() const = 0;` — Returns whether the GRDK is available It will be safe to access IGDKRuntimeModule if this returns true
