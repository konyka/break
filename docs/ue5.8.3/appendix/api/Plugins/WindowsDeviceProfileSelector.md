# Plugins / WindowsDeviceProfileSelector

- module root: `Plugins/Runtime/WindowsDeviceProfileSelector/Source/WindowsDeviceProfileSelector`
- headers: 2; symbols: 5
- symbol kinds: class=1, prototype=4
- PrivateDependencyModuleNames: Engine, RHI
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/WindowsDeviceProfileSelector/Source/WindowsDeviceProfileSelector/Private/WindowsDeviceProfileSelectorModule.h` (Private)


#### class `FWindowsDeviceProfileSelectorModule`  
`class FWindowsDeviceProfileSelectorModule : public IDeviceProfileSelectorModule`  
_L11-31_
- inherits: `IDeviceProfileSelectorModule`
- desc: Implements the Windows Device Profile Selector module.
- L17 _public prototype_ `virtual const FString GetRuntimeDeviceProfileName() override;`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public prototype_ `virtual ~FWindowsDeviceProfileSelectorModule() = default;` — Virtual destructor.

### `Plugins/Runtime/WindowsDeviceProfileSelector/Source/WindowsDeviceProfileSelector/Public/WindowsDeviceProfileSelector.h` (Public)
_(no declarations extracted)_
