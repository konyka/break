# Plugins / LinuxDeviceProfileSelector

- module root: `Plugins/Runtime/LinuxDeviceProfileSelector/Source/LinuxDeviceProfileSelector`
- headers: 2; symbols: 5
- symbol kinds: class=1, function=1, prototype=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, HeadMountedDisplay
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/LinuxDeviceProfileSelector/Source/LinuxDeviceProfileSelector/Private/LinuxDeviceProfileSelectorModule.h` (Private)


#### class `FLinuxDeviceProfileSelectorModule`  
`class FLinuxDeviceProfileSelectorModule : public IDeviceProfileSelectorModule`  
_L10-32_
- inherits: `IDeviceProfileSelectorModule`
- desc: Implements the Linux Device Profile Selector module.
- L16 _public prototype_ `virtual const FString GetRuntimeDeviceProfileName() override;`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _public function_ `virtual ~FLinuxDeviceProfileSelectorModule()` — Virtual destructor.

### `Plugins/Runtime/LinuxDeviceProfileSelector/Source/LinuxDeviceProfileSelector/Public/LinuxDeviceProfileSelector.h` (Public)
_(no declarations extracted)_
