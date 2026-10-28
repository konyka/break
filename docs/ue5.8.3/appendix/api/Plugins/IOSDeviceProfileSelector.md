# Plugins / IOSDeviceProfileSelector

- module root: `Plugins/Runtime/IOSDeviceProfileSelector/Source/IOSDeviceProfileSelector`
- headers: 1; symbols: 5
- symbol kinds: class=1, function=1, prototype=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/IOSDeviceProfileSelector/Source/IOSDeviceProfileSelector/Private/IOSDeviceProfileSelectorModule.h` (Private)


#### class `FIOSDeviceProfileSelectorModule`  
`class FIOSDeviceProfileSelectorModule : public IDeviceProfileSelectorModule`  
_L11-33_
- inherits: `IDeviceProfileSelectorModule`
- desc: Implements the IOS Device Profile Selector module.
- L17 _public prototype_ `virtual const FString GetRuntimeDeviceProfileName() override;`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public function_ `virtual ~FIOSDeviceProfileSelectorModule()` — Virtual destructor.
