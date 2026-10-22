# Plugins / DumpGPUServices

- module root: `Plugins/Developer/DumpGPUServices/Source/DumpGPUServices`
- headers: 2; symbols: 5
- symbol kinds: class=1, delegate=1, function=2, prototype=1
- PrivateDependencyModuleNames: HTTP, Json, RenderCore, Slate
- PublicDependencyModuleNames: Core

### `Plugins/Developer/DumpGPUServices/Source/DumpGPUServices/Private/DumpGPUServices.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDumpGPUServices, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDumpGPUServices, Log, All);`

### `Plugins/Developer/DumpGPUServices/Source/DumpGPUServices/Public/IDumpGPUServices.h` (Public)


#### class `IDumpGPUServices`  
`class IDumpGPUServices : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L23 _public function_ `static inline IDumpGPUServices& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
