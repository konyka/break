# Plugins / Firebase

- module root: `Plugins/Runtime/Firebase/Source`
- headers: 2; symbols: 24
- symbol kinds: class=1, delegate=1, function=2, macro=1, member=5, prototype=12, struct=1, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Launch, Swift
- PublicIncludePathModuleNames: Launch

### `Plugins/Runtime/Firebase/Source/IOS/notifications/EpicFirebaseIOSNotifications.h` (Other)


#### struct `FFirebaseIOSNotifications`  
`struct FFirebaseIOSNotifications`  
_L13-31_
- L16 _private member_ `static bool bIsInitialized;`
- L17 _private member_ `static bool bIsConfigured;`
- L18 _private member_ `static FString IOSFirebaseToken;`
- L20 _private prototype_ `static bool IsConfigured();`
- L23 _public prototype_ `static void ConfigureFirebase();`
- L24 _public prototype_ `static void ConfigureFirebaseWithCustomFile(const FString& FileName);`
- L25 _public prototype_ `static void EnableFirebaseAutoInit();`
- L26 _public prototype_ `static void Initialize(uint64 TokenQueryTimeoutNanoseconds, bool bEnableAnalytics);`
- L27 _public prototype_ `static void SetFirebaseToken(FString Token);`
- L28 _public prototype_ `static FString GetFirebaseToken();`
- L29 _public prototype_ `static void DeleteFirebaseToken();`
- L30 _public prototype_ `static void OnAPNSTokenReceived(TArrayView<uint8> Token);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define WITH_IOS_FIREBASE_INTEGRATION 0`

### `Plugins/Runtime/Firebase/Source/Public/Firebase.h` (Public)


#### class `IFirebaseModuleInterface`  
`class IFirebaseModuleInterface : public IModuleInterface`  
_L13-46_
- inherits: `IModuleInterface`
- L16 _private member_ `FDelegateHandle ApplicationRegisteredForRemoteNotificationsHandle;`
- L26 _public function_ `static IFirebaseModuleInterface& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase - the module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L42 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L43 _public prototype_ `virtual void ShutdownModule() override;`
- L45 _public member_ `TMulticastDelegate<void(const FString&, const FString&)> OnTokenUpdate;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFirebase, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFirebase, Log, All);`
- L11 _variable_ `static const char* FIREBASE_MODULE_NAME = "Fi`
