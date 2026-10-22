# Plugins / PortableObjectFileDataSource

- module root: `Plugins/Editor/Localization/PortableObjectFileDataSource/Source/PortableObjectFileDataSource`
- headers: 1; symbols: 6
- symbol kinds: class=1, function=2, prototype=2, typedef=1
- PrivateDependencyModuleNames: ContentBrowserFileDataSource, Localization
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Editor/Localization/PortableObjectFileDataSource/Source/PortableObjectFileDataSource/Public/IPortableObjectFileDataSourceModule.h` (Public)


#### class `IPortableObjectFileDataSourceModule`  
`class IPortableObjectFileDataSourceModule : public IModuleInterface`  
_L8-33_
- inherits: `IModuleInterface`
- L11 _public function_ `static IPortableObjectFileDataSourceModule& Get()`
- L16 _public function_ `static IPortableObjectFileDataSourceModule* GetPtr()`
- L21 _public typedef_ `using FCanEditFileDelegate = TDelegate<bool(const FName InFilePath, const FString& InFilename, FText* OutErrorMsg)>;`
- L27 _public prototype_ `virtual FDelegateHandle RegisterCanEditFileOverride(FCanEditFileDelegate&& Delegate) = 0;` — Register an override handler for the "CanEdit" logic for Portable Object files. Each handler is queried in turn to see if they all allow editing of the file, and editing is refused if any return false.
- L32 _public prototype_ `virtual void UnregisterCanEditFileOverride(const FDelegateHandle& Handle) = 0;` — Unregister an override handler for the "CanEdit" logic for Portable Object files, as previously registered by RegisterCanEditFileOverride.
