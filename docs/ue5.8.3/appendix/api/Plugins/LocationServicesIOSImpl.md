# Plugins / LocationServicesIOSImpl

- module root: `Plugins/Runtime/LocationServicesIOSImpl/Source/LocationServicesIOSImpl`
- headers: 2; symbols: 16
- symbol kinds: class=2, delegate=1, function=1, member=2, prototype=10
- PrivateDependencyModuleNames: Launch, LocationServicesBPLibrary
- PublicDependencyModuleNames: Core, CoreUObject, Engine, LocationServicesBPLibrary
- PublicIncludePathModuleNames: LocationServicesBPLibrary, LocationServicesIOSImpl

### `Plugins/Runtime/LocationServicesIOSImpl/Source/LocationServicesIOSImpl/Classes/LocationServicesIOSImpl.h` (Public)


#### class `ULocationServicesIOSImpl`  
`class ULocationServicesIOSImpl : public ULocationServicesImpl`  
_L14-68_
- reflection: `UCLASS()`
- inherits: `ULocationServicesImpl`
- L20 _public prototype_ `virtual ~ULocationServicesIOSImpl();`
- L30 _public prototype_ `virtual bool InitLocationServices(ELocationAccuracy Accuracy, float UpdateFrequency, float MinDistance) override;` — Called to set up the Location Service before use @param Accuracy - as seen in the enum above @param UpdateFrequency - in milliseconds. (Android only) @param MinDistance - minDistance before a location update, in meters. 0 here means "update asap" @return - true if Initialization was succesful
- L36 _public prototype_ `virtual bool StartLocationService() override;` — Starts requesting location updates from the appropriate Location Service @return - true if startup successful
- L42 _public prototype_ `virtual bool StopLocationService() override;` — Stops the updates of location from the Location Service that was started with StartLocationService @return - true if stop is successful
- L49 _public prototype_ `virtual FLocationServicesData GetLastKnownLocation() override;` — Returns the last location information returned by the location service. If no location update has been made, will return a default-value-filled struct. @return - the last known location from updates
- L56 _public prototype_ `virtual bool IsLocationAccuracyAvailable(ELocationAccuracy Accuracy) override;` — Checks if the supplied Accuracy is available on the current device. @param Accuracy - the accuracy to check @return - true if the mobile device can support the Accuracy, false if it will use a different accuracy
- L62 _public prototype_ `virtual bool IsLocationServiceEnabled() override;` — Checks if the Location Services on the mobile device are enabled for this application @return - true if the mobile device has enabled the appropriate service for the app
- L66 _private member_ `FLocationManagerDelegate *LocationDelegate;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLocationServicesIOS, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLocationServicesIOS, Log, All);`

### `Plugins/Runtime/LocationServicesIOSImpl/Source/LocationServicesIOSImpl/Public/LocationServicesIOSImplModule.h` (Public)


#### class `FLocationServicesIOSImplModule`  
`class FLocationServicesIOSImplModule : public IModuleInterface`  
_L13-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L26 _public function_ `static inline FLocationServicesIOSImplModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _private member_ `ULocationServicesIOSImpl* ImplInstance;`
- L34 _private prototype_ `virtual void StartupModule() override;`
- L35 _private prototype_ `virtual void ShutdownModule() override;`
