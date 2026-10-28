# Plugins / ExampleDeviceProfileSelector

- module root: `Plugins/Runtime/ExampleDeviceProfileSelector/Source/ExampleDeviceProfileSelector`
- headers: 2; symbols: 5
- symbol kinds: class=1, function=1, prototype=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/ExampleDeviceProfileSelector/Source/ExampleDeviceProfileSelector/Private/ExampleDeviceProfileSelectorModule.h` (Private)


#### class `FExampleDeviceProfileSelectorModule`  
`class FExampleDeviceProfileSelectorModule : public IDeviceProfileSelectorModule`  
_L10-32_
- inherits: `IDeviceProfileSelectorModule`
- desc: Implements the Example Device Profile Selector module.
- L16 _public prototype_ `virtual const FString GetRuntimeDeviceProfileName() override;`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _public function_ `virtual ~FExampleDeviceProfileSelectorModule()` — Virtual destructor.

### `Plugins/Runtime/ExampleDeviceProfileSelector/Source/ExampleDeviceProfileSelector/Public/ExampleDeviceProfileSelector.h` (Public)
_(no declarations extracted)_
