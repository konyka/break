# Plugins / AndroidDeviceProfileSelectorRuntime

- module root: `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileSelectorRuntime`
- headers: 2; symbols: 7
- symbol kinds: class=1, function=1, prototype=5
- PrivateDependencyModuleNames: AndroidDeviceProfileSelector, Core, CoreUObject, Engine, HeadMountedDisplay
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileSelectorRuntime/Private/AndroidDeviceProfileSelectorRuntimeModule.h` (Private)


#### class `FAndroidDeviceProfileSelectorRuntimeModule`  
`class FAndroidDeviceProfileSelectorRuntimeModule : public IDeviceProfileSelectorModule`  
_L11-41_
- inherits: `IDeviceProfileSelectorModule`
- desc: Implements the Android Device Profile Selector module.
- L17 _public prototype_ `virtual const FString GetRuntimeDeviceProfileName() override;`
- L18 _public prototype_ `virtual bool GetSelectorPropertyValue(const FName& PropertyType, FString& PropertyValueOUT) override;`
- L23 _public prototype_ `virtual void StartupModule() override;`
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public function_ `virtual ~FAndroidDeviceProfileSelectorRuntimeModule()` — Virtual destructor.
- L40 _private prototype_ `void CheckForJavaSurfaceViewWorkaround(const FString& DeviceMake, const FString& DeviceModel) const;` — Make sure we use the java workaround for view scaling on devices that require this

### `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileSelectorRuntime/Public/AndroidDeviceProfileSelectorRuntime.h` (Public)
_(no declarations extracted)_
