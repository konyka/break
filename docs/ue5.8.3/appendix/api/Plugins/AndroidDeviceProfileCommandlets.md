# Plugins / AndroidDeviceProfileCommandlets

- module root: `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileCommandlets`
- headers: 2; symbols: 2
- symbol kinds: class=1, prototype=1
- PrivateDependencyModuleNames: AndroidDeviceProfileSelector, Engine, Json, JsonUtilities, PIEPreviewDeviceSpecification
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileCommandlets/Private/CreateAndroidPreviewDataFromADBCommandlet.h` (Private)


#### class `UCreateAndroidPreviewDataFromADBCommandlet`  
`class UCreateAndroidPreviewDataFromADBCommandlet : public UCommandlet`  
_L17-30_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: This commandlet runs in an infinite loop. It waits for new devices to be plugged in (or to become visible to adb) When a new device is encountered it is queried and a new .json containing it's particulars is saved. The json file is then usable by editor for device preview and also for the android device profile matching system. Usage commandline: <game> -run=AndroidDeviceDetection.CreateAndroidPreviewDataFromADB -ConfigRules=[path to configrules.txt] -DeviceSpecsFolder=[Path to json output folder, e.g."\Engine\Content\Editor\PIEPreviewDeviceSpecs\Android"]
- L25 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileCommandlets/Public/AndroidDeviceProfileCommandlets.h` (Public)
_(no declarations extracted)_
