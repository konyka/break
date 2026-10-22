# Plugins / OptionalMobileFeaturesBPLibrary

- module root: `Plugins/Runtime/OptionalMobileFeaturesBPLibrary/Source/OptionalMobileFeaturesBPLibrary`
- headers: 2; symbols: 9
- symbol kinds: class=2, function=1, prototype=6
- PrivateDependencyModuleNames: ApplicationCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/OptionalMobileFeaturesBPLibrary/Source/OptionalMobileFeaturesBPLibrary/Classes/OptionalMobileFeaturesBPLibrary.h` (Public)


#### class `UOptionalMobileFeaturesBPLibrary`  
`class UOptionalMobileFeaturesBPLibrary : public UBlueprintFunctionLibrary`  
_L9-30_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L16 _private prototype_ `static int GetVolumeState();` — `UFUNCTION(BlueprintCallable, Category="Mobile")` — Returns the current volume state of the device in a range of 0-100 (%)
- L20 _private prototype_ `static int GetBatteryLevel();` — `UFUNCTION(BlueprintCallable, Category = "Mobile")` — Returns the current battery level of the device in a range of [0, 100]
- L24 _private prototype_ `static float GetBatteryTemperature();` — `UFUNCTION(BlueprintCallable, Category = "Mobile")` — Returns the device's temperature, in Celsius
- L28 _private prototype_ `static bool AreHeadphonesPluggedIn();` — `UFUNCTION(BlueprintCallable, Category = "Mobile")` — Returns if headphones are plugged into the device

### `Plugins/Runtime/OptionalMobileFeaturesBPLibrary/Source/OptionalMobileFeaturesBPLibrary/Public/OptionalMobileFeaturesBPLibraryModule.h` (Public)


#### class `FOptionalMobileFeaturesBPLibraryModule`  
`class FOptionalMobileFeaturesBPLibraryModule : public IModuleInterface`  
_L10-31_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline FOptionalMobileFeaturesBPLibraryModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L29 _private prototype_ `virtual void StartupModule() override;`
- L30 _private prototype_ `virtual void ShutdownModule() override;`
