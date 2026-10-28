# Plugins / LocationServicesAndroidImpl

- module root: `Plugins/Runtime/LocationServicesAndroidImpl/Source/LocationServicesAndroidImpl`
- headers: 3; symbols: 22
- symbol kinds: class=2, delegate=1, function=1, member=2, namespace=2, prototype=11, struct=1, typedef=1, variable=1
- PrivateDependencyModuleNames: Launch, LocationServicesBPLibrary
- PublicDependencyModuleNames: Core, CoreUObject, Engine, LocationServicesBPLibrary
- PublicIncludePathModuleNames: AndroidPermission, LocationServicesAndroidImpl, LocationServicesBPLibrary

### `Plugins/Runtime/LocationServicesAndroidImpl/Source/LocationServicesAndroidImpl/Classes/LocationServicesAndroidImpl.h` (Public)


#### class `ULocationServicesAndroidImpl`  
`class ULocationServicesAndroidImpl : public ULocationServicesImpl`  
_L11-61_
- reflection: `UCLASS()`
- inherits: `ULocationServicesImpl`
- L17 _public prototype_ `virtual ~ULocationServicesAndroidImpl();`
- L27 _public prototype_ `virtual bool InitLocationServices(ELocationAccuracy Accuracy, float UpdateFrequency, float MinDistanceFilter) override;` — Called to set up the Location Service before use @param Accuracy - as seen in the enum above @param UpdateFrequency - in milliseconds. (Android only) @param MinDistance - minDistance before a location update, in meters. 0 here means "update asap" @return - true if Initialization was succesful
- L33 _public prototype_ `virtual bool StartLocationService() override;` — Starts requesting location updates from the appropriate Location Service @return - true if startup successful
- L39 _public prototype_ `virtual bool StopLocationService() override;` — Stops the updates of location from the Location Service that was started with StartLocationService @return - true if stop is successful
- L46 _public prototype_ `virtual FLocationServicesData GetLastKnownLocation() override;` — Returns the last location information returned by the location service. If no location update has been made, will return a default-value-filled struct. @return - the last known location from updates
- L53 _public prototype_ `virtual bool IsLocationAccuracyAvailable(ELocationAccuracy Accuracy) override;` — Checks if the supplied Accuracy is available on the current device. @param Accuracy - the accuracy to check @return - true if the mobile device can support the Accuracy, false if it will use a different accuracy
- L59 _public prototype_ `virtual bool IsLocationServiceEnabled() override;` — Checks if the Location Services on the mobile device are enabled for this application @return - true if the mobile device has enabled the appropriate service for the app

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLocationServicesAndroid, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLocationServicesAndroid, Log, All);`

### `Plugins/Runtime/LocationServicesAndroidImpl/Source/LocationServicesAndroidImpl/Private/AndroidJniLocationServices.h` (Private)


#### struct `UE::Jni::FLocationServices`  
`struct FLocationServices`  
_L11-21_
- L13 _public typedef_ `using PartialClass = FGameActivity;`
- L15 _public prototype_ `static void JNICALL nativeHandleLocationChanged(JNIEnv* env, jobject thiz, jlong time, jdouble longitude, jdouble latitude, jfloat accuracy, jdouble altitude);`
- L17 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(nativeHandleLocationChanged) };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L23 _variable_ `template struct TInitialize<FLocationServices>;` (scope `UE::Jni`)

### `Plugins/Runtime/LocationServicesAndroidImpl/Source/LocationServicesAndroidImpl/Public/LocationServicesAndroidImplModule.h` (Public)


#### class `FLocationServicesAndroidImplModule`  
`class FLocationServicesAndroidImplModule : public IModuleInterface`  
_L13-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L26 _public function_ `static inline FLocationServicesAndroidImplModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _private member_ `ULocationServicesAndroidImpl* ImplInstance;`
- L34 _private prototype_ `virtual void StartupModule() override;`
- L35 _private prototype_ `virtual void ShutdownModule() override;`
