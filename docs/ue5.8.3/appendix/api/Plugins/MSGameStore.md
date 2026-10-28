# Plugins / MSGameStore

- module root: `Plugins/Runtime/Windows/MSGameStore/Source/MSGameStore`
- headers: 1; symbols: 4
- symbol kinds: class=1, function=1, prototype=2
- PrivateDependencyModuleNames: Core

### `Plugins/Runtime/Windows/MSGameStore/Source/MSGameStore/Public/MSGameStoreModule.h` (Public)


#### class `IMSGameStoreModule`  
`class IMSGameStoreModule : public IModuleInterface`  
_L10-32_
- inherits: `IModuleInterface`
- L17 _public function_ `static inline IMSGameStoreModule& Get()` — Singleton-like access to the MS Game Store module instance @return Returns IMSGameStoreModule singleton instance, loading the module on demand if needed
- L25 _public prototype_ `virtual bool IsPackaged() const = 0;` — Returns whether we are installed as an app package
- L31 _public prototype_ `virtual IPlatformChunkInstall* GetChunkInstaller() const = 0;` — Helper function to get the GDK chunk installer, if it is available
