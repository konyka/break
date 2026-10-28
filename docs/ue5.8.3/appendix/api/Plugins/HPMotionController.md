# Plugins / HPMotionController

- module root: `Plugins/Runtime/HPMotionController/Source/HPMotionController`
- headers: 1; symbols: 12
- symbol kinds: class=1, function=2, member=2, prototype=7
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, OpenXRHMD

### `Plugins/Runtime/HPMotionController/Source/HPMotionController/Private/HPMotionController.h` (Private)


#### class `FHPMotionControllerModule`  
`class FHPMotionControllerModule : public IModuleInterface, public IOpenXRExtensionPlugin`  
_L8-32_
- inherits: `IModuleInterface,IOpenXRExtensionPlugin`
- L13 _public function_ `FHPMotionControllerModule()`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public function_ `virtual FString GetDisplayName() override`
- L23 _public prototype_ `bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions) override;`
- L24 _public prototype_ `void PostCreateInstance(XrInstance InInstance) override;`
- L25 _public prototype_ `bool GetInteractionProfiles(XrInstance InInstance, TArray<FString>& OutKeyPrefixes, TArray<XrPath>& OutPaths, TArray<bool>& OutHasHaptics) override;`
- L26 _public prototype_ `bool GetControllerModel(XrInstance InInstance, XrPath InInteractionProfile, XrPath InDevicePath, FSoftObjectPath& OutPath) override;`
- L27 _public prototype_ `void GetControllerModelsForCooking(TArray<FSoftObjectPath>& OutPaths) override;`
- L30 _private member_ `XrPath InteractionProfile;`
- L31 _private member_ `TMap<XrPath, FSoftObjectPath> ControllerModels;`
