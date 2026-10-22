# Plugins / OpenXRMsftHandInteraction

- module root: `Plugins/Runtime/OpenXRMsftHandInteraction/Source/OpenXRMsftHandInteraction`
- headers: 1; symbols: 5
- symbol kinds: class=1, function=1, prototype=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, OpenXRHMD

### `Plugins/Runtime/OpenXRMsftHandInteraction/Source/OpenXRMsftHandInteraction/Public/OpenXRMsftHandInteraction.h` (Public)


#### class `FOpenXRMsftHandInteraction`  
`class FOpenXRMsftHandInteraction : public IModuleInterface, public IOpenXRExtensionPlugin`  
_L21-38_
- inherits: `IModuleInterface,IOpenXRExtensionPlugin`
- L27 _public prototype_ `virtual void StartupModule() override;` — /
- L32 _public function_ `virtual FString GetDisplayName() override` — /
- L36 _public prototype_ `virtual bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions) override;`
- L37 _public prototype_ `virtual bool GetInteractionProfiles(XrInstance InInstance, TArray<FString>& OutKeyPrefixes, TArray<XrPath>& OutPaths, TArray<bool>& OutHasHaptics) override;`
