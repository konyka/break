# Plugins / InterchangeExport

- module root: `Plugins/Interchange/Runtime/Source/Export`
- headers: 2; symbols: 6
- symbol kinds: class=2, function=2, macro=1, prototype=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InterchangeCore, InterchangeEngine

### `Plugins/Interchange/Runtime/Source/Export/Public/InterchangeExportModule.h` (Public)


#### class `IInterchangeExportModule`  
`class IInterchangeExportModule : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IInterchangeExportModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Interchange/Runtime/Source/Export/Public/InterchangeTextureWriter.h` (Public)


#### class `UInterchangeTextureWriter`  
`class UInterchangeTextureWriter : public UInterchangeWriterBase`  
_L16-27_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental)`
- inherits: `UInterchangeWriterBase`
- L26 _public prototype_ `virtual bool Export(UInterchangeBaseNodeContainer* BaseNodeContainer) const override;` — Export all nodes of type FTextureNode hold by the BaseNodeContainer @param BaseNodeContainer - Contain nodes describing what to export @return true if the writer can export the nodes, false otherwise.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INTERCHANGEEXPORT_API`
