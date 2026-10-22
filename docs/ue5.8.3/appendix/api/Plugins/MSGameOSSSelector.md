# Plugins / MSGameOSSSelector

- module root: `Plugins/Runtime/Windows/MSGameOSSSelector/Source/MSGameOSSSelector`
- headers: 1; symbols: 3
- symbol kinds: class=1, function=1, prototype=1

### `Plugins/Runtime/Windows/MSGameOSSSelector/Source/MSGameOSSSelector/Public/MSGameOSSSelectorModule.h` (Public)


#### class `IMSGameOSSSelectorModule`  
`class IMSGameOSSSelectorModule : public IModuleInterface`  
_L9-25_
- inherits: `IModuleInterface`
- L16 _public function_ `static inline IMSGameOSSSelectorModule& Get()` — Singleton-like access to the OSS selector module instance @return Returns IMSGameOSSSelectorModule singleton instance, loading the module on demand if needed
- L24 _public prototype_ `virtual bool HasModifiedConfiguration() const = 0;` — Returns whether the configuration patch was applied
