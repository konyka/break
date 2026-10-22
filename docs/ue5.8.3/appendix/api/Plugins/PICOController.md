# Plugins / PICOController

- module root: `Plugins/Runtime/PICOController/Source`
- headers: 1; symbols: 8
- symbol kinds: class=1, function=2, prototype=5
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, OpenXRHMD

### `Plugins/Runtime/PICOController/Source/PICOController/Private/PICOController.h` (Private)


#### class `FPICOControllerModule`  
`class FPICOControllerModule : public IModuleInterface, public IOpenXRExtensionPlugin`  
_L8-26_
- inherits: `IModuleInterface,IOpenXRExtensionPlugin`
- L13 _public function_ `FPICOControllerModule()`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public function_ `virtual FString GetDisplayName() override`
- L23 _public prototype_ `virtual bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions) override;`
- L24 _public prototype_ `virtual bool GetOptionalExtensions(TArray<const ANSICHAR*>& OutExtensions) override;`
- L25 _public prototype_ `virtual bool GetInteractionProfiles(XrInstance InInstance, TArray<FString>& OutKeyPrefixes, TArray<XrPath>& OutPaths, TArray<bool>& OutHasHaptics) override;`
