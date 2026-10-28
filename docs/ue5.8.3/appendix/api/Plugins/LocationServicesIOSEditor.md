# Plugins / LocationServicesIOSEditor

- module root: `Plugins/Runtime/LocationServicesIOSImpl/Source/LocationServicesIOSEditor`
- headers: 2; symbols: 6
- symbol kinds: class=2, member=2, prototype=2
- DynamicallyLoadedModuleNames: Settings
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PrivateIncludePathModuleNames: Settings
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/LocationServicesIOSImpl/Source/LocationServicesIOSEditor/Classes/LocationServicesIOSSettings.h` (Public)


#### class `ULocationServicesIOSSettings`  
`class ULocationServicesIOSSettings : public UObject`  
_L9-21_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- inherits: `UObject`
- L16 _private member_ `FString LocationAlwaysUsageDescription;` — `UPROPERTY(config, EditAnywhere, Category = LocationServices, meta = (DisplayName = "Location Services Always Use Permission Text" ))` — Text to display when requesting permission for Location Services
- L20 _private member_ `FString LocationWhenInUseDescription;` — `UPROPERTY(config, EditAnywhere, Category = LocationServices, meta = (DisplayName = "Location Services In-Use Permission Text" ))` — Text to display when requesting permission for Location Services

### `Plugins/Runtime/LocationServicesIOSImpl/Source/LocationServicesIOSEditor/Public/LocationServicesIOSEditor.h` (Public)


#### class `FLocationServicesIOSEditorModule`  
`class FLocationServicesIOSEditorModule : public IModuleInterface`  
_L6-12_
- inherits: `IModuleInterface`
- L10 _private prototype_ `virtual void StartupModule() override;`
- L11 _private prototype_ `virtual void ShutdownModule() override;`
