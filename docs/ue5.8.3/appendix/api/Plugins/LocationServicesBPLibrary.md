# Plugins / LocationServicesBPLibrary

- module root: `Plugins/Runtime/LocationServicesBPLibrary/Source/LocationServicesBPLibrary`
- headers: 3; symbols: 41
- symbol kinds: class=3, delegate=1, enum=1, enumerator=6, function=9, macro=1, member=8, prototype=11, struct=1
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/LocationServicesBPLibrary/Source/LocationServicesBPLibrary/Classes/LocationServicesBPLibrary.h` (Public)


#### enum `ELocationAccuracy`  
`enum class ELocationAccuracy : uint8`  
_L19-27_
- reflection: `UENUM(BlueprintType)`
- desc: Enum used to determine what accuracy the Location Services should be run with. Based off the iOS kCLLocationAccuracy enums since those were the most restrictive (but convienently also had descriptive names)
- L21 _public enumerator_ `LA_ThreeKilometers UMETA(DisplayName = "Three Kilometers")`
- L22 _public enumerator_ `LA_OneKilometer UMETA(DisplayName = "One Kilometer")`
- L23 _public enumerator_ `LA_HundredMeters UMETA(DisplayName = "One Hundred Meters")`
- L24 _public enumerator_ `LA_TenMeters UMETA(DisplayName = "Ten Meters")`
- L25 _public enumerator_ `LA_Best UMETA(DisplayName = "Best")`
- L26 _public enumerator_ `LA_Navigation UMETA(DisplayName = "Best for Navigation")`

#### struct `FLocationServicesData`  
`struct FLocationServicesData`  
_L33-69_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct to hold relevant location data retrieved from the mobile implementation's Location Service
- L39 _public member_ `float Timestamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Location Data Struct")` — Timestamp from when this location data was taken (UTC time in milliseconds since 1 January 1970)
- L42 _public member_ `float Longitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Location Data Struct")`
- L45 _public member_ `float Latitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Location Data Struct")`
- L49 _public member_ `float HorizontalAccuracy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Location Data Struct")` — Estimated horizontal (Android: overall) accuracy of the result, in meters
- L53 _public member_ `float VerticalAccuracy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Location Data Struct")` — Estimated accuracy of the result, in meters (iOS only)
- L57 _public member_ `float Altitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Location Data Struct")` — In meters, if provided with the result
- L59 _public function_ `FLocationServicesData()`

#### class `ULocationServices`  
`class ULocationServices : public UBlueprintFunctionLibrary`  
_L76-149_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L91 _public prototype_ `static bool InitLocationServices(ELocationAccuracy Accuracy, float UpdateFrequency, float MinDistanceFilter);` — `UFUNCTION(BlueprintCallable, Category="Services|Mobile|Location")` — Called to set up the Location Service before use @param Accuracy - as seen in the enum above @param UpdateFrequency - in milliseconds. (Android only) @param MinDistance - minDistance before a location update, in meters. 0 here means "update asap" @return - true if Initialization was succesful
- L98 _public prototype_ `static bool StartLocationServices();` — `UFUNCTION(BlueprintCallable, Category = "Services|Mobile|Location")` — Starts requesting location updates from the appropriate Location Service @return - true if startup successful
- L105 _public prototype_ `static bool StopLocationServices();` — `UFUNCTION(BlueprintCallable, Category = "Services|Mobile|Location")` — Stops the updates of location from the Location Service that was started with StartLocationService @return - true if stop is successful
- L113 _public prototype_ `static FLocationServicesData GetLastKnownLocation();` — `UFUNCTION(BlueprintCallable, Category = "Services|Mobile|Location")` — Returns the last location information returned by the location service. If no location update has been made, will return a default-value-filled struct. @return - the last known location from updates
- L120 _public prototype_ `static bool AreLocationServicesEnabled();` — `UFUNCTION(BlueprintCallable, Category = "Services|Mobile|Location")` — Checks if the Location Services on the mobile device are enabled for this application @return - true if the mobile device has enabled the appropriate service for the app
- L128 _public prototype_ `static bool IsLocationAccuracyAvailable(ELocationAccuracy Accuracy);` — `UFUNCTION(BlueprintCallable, Category = "Services|Mobile|Location")` — Checks if the supplied Accuracy is available on the current device. @param Accuracy - the accuracy to check @return - true if the mobile device can support the Accuracy, false if it will use a different accuracy
- L134 _public prototype_ `static void SetLocationServicesImpl(ULocationServicesImpl* Impl);` — Set and clear the Location Services implementation object. Used by the module at startup and shutdown, not intended for use outside of that
- L135 _public prototype_ `static void ClearLocationServicesImpl();`
- L143 _public function_ `static ULocationServicesImpl* GetLocationServicesImpl()` — `UFUNCTION(BlueprintCallable, Category = "Services|Mobile|Location")` — Returns the Location Services implementation object. Intended to be used to set up the FLocationServicesData_OnLocationChanged delegate in Blueprints. @return - the Android or IOS impl object
- L147 _private member_ `static ULocationServicesImpl* ImplInstance;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LOCATIONSERVICESBPLIBRARY_API`
- L71 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLocationServicesData_OnLocationChanged, FLocationServicesData, LocationData);`
- L71 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLocationServicesData_OnLocationChanged, FLocationServicesData, LocationData);`

### `Plugins/Runtime/LocationServicesBPLibrary/Source/LocationServicesBPLibrary/Classes/LocationServicesImpl.h` (Public)


#### class `ULocationServicesImpl`  
`class ULocationServicesImpl : public UObject`  
_L10-57_
- reflection: `UCLASS(abstract)`
- inherits: `UObject`
- L23 _public function_ `virtual bool InitLocationServices(ELocationAccuracy Accuracy, float UpdateFrequency, float MinDistanceFilter)` — Called to set up the Location Service before use @param Accuracy - as seen in the enum above @param UpdateFrequency - in milliseconds. (Android only) @param MinDistance - minDistance before a location update, in meters. 0 here means "update asap" @return - true if Initialization was succesful
- L29 _public function_ `virtual bool StartLocationService()` — Starts requesting location updates from the appropriate Location Service @return - true if startup successful
- L35 _public function_ `virtual bool StopLocationService()` — Stops the updates of location from the Location Service that was started with StartLocationService @return - true if stop is successful
- L42 _public function_ `virtual FLocationServicesData GetLastKnownLocation()` — Returns the last location information returned by the location service. If no location update has been made, will return a default-value-filled struct. @return - the last known location from updates
- L49 _public function_ `virtual bool IsLocationAccuracyAvailable(ELocationAccuracy Accuracy)` — Checks if the supplied Accuracy is available on the current device. @param Accuracy - the accuracy to check @return - true if the mobile device can support the Accuracy, false if it will use a different accuracy
- L52 _public function_ `virtual bool IsLocationServiceEnabled()` — @return true if the mobile device has enabled the appropriate service for the app
- L55 _public member_ `FLocationServicesData_OnLocationChanged OnLocationChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Services|Mobile|Location")`

### `Plugins/Runtime/LocationServicesBPLibrary/Source/LocationServicesBPLibrary/Public/LocationServicesBPLibraryModule.h` (Public)


#### class `FLocationServicesBPLibraryModule`  
`class FLocationServicesBPLibraryModule : public IModuleInterface`  
_L10-31_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline FLocationServicesBPLibraryModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L29 _private prototype_ `virtual void StartupModule() override;`
- L30 _private prototype_ `virtual void ShutdownModule() override;`
