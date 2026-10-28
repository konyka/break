# Plugins / LocationServicesAndroidEditor

- module root: `Plugins/Runtime/LocationServicesAndroidImpl/Source/LocationServicesAndroidEditor`
- headers: 2; symbols: 7
- symbol kinds: class=2, member=3, prototype=2
- DynamicallyLoadedModuleNames: Settings
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PrivateIncludePathModuleNames: Settings
- PublicDependencyModuleNames: AndroidPermission, Core

### `Plugins/Runtime/LocationServicesAndroidImpl/Source/LocationServicesAndroidEditor/Classes/LocationServicesAndroidSettings.h` (Public)


#### class `ULocationServicesAndroidSettings`  
`class ULocationServicesAndroidSettings : public UObject`  
_L9-22_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- inherits: `UObject`
- L15 _private member_ `bool bCoarseLocationEnabled;` — `UPROPERTY(config, EditAnywhere, Category=LocationServices, meta=(DisplayName = "Enable Coarse Location Accuracy (Network Provider)"))`
- L18 _private member_ `bool bFineLocationEnabled;` — `UPROPERTY(config, EditAnywhere, Category= LocationServices, meta=(DisplayName = "Enable Fine Location Accuracy (GPS Provider)"))`
- L21 _private member_ `bool bLocationUpdatesEnabled;` — `UPROPERTY(config, EditAnywhere, Category= LocationServices, meta=(DisplayName = "Enable Location Updates"))`

### `Plugins/Runtime/LocationServicesAndroidImpl/Source/LocationServicesAndroidEditor/Public/LocationServicesAndroidEditor.h` (Public)


#### class `FLocationServicesAndroidEditorModule`  
`class FLocationServicesAndroidEditorModule : public IModuleInterface`  
_L6-12_
- inherits: `IModuleInterface`
- L10 _private prototype_ `virtual void StartupModule() override;`
- L11 _private prototype_ `virtual void ShutdownModule() override;`
