# Developer / HotReload

- module root: `Source/Developer/HotReload`
- headers: 2; symbols: 5
- symbol kinds: class=1, delegate=1, function=2, prototype=1
- PrivateDependencyModuleNames: Analytics, DesktopPlatform, DirectoryWatcher, Engine, Projects, UnrealEd
- PrivateIncludePathModuleNames: LiveCoding
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Developer/HotReload/Private/HotReloadLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHotReload, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHotReload, Log, All);`

### `Source/Developer/HotReload/Public/IHotReload.h` (Public)


#### class `IHotReloadModule`  
`class IHotReloadModule : public IHotReloadInterface`  
_L13-38_
- inherits: `IHotReloadInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L24 _public function_ `static inline IHotReloadModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
