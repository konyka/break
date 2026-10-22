# Plugins / WebAuth

- module root: `Plugins/Online/WebAuth/Source`
- headers: 8; symbols: 56
- symbol kinds: class=8, delegate=1, function=4, macro=1, member=6, namespace=2, prototype=28, struct=1, typedef=4, variable=1
- PrivateDependencyModuleNames: ApplicationCore, Core, Launch

### `Plugins/Online/WebAuth/Source/Private/Android/AndroidJniWebAuth.h` (Private)


#### struct `UE::Jni::FWebAuth`  
`struct FWebAuth`  
_L11-21_
- L13 _public typedef_ `using PartialClass = FGameActivity;`
- L15 _public prototype_ `static void JNICALL handleAuthSessionResponse(JNIEnv* env, jobject thiz, jstring redirectURL);`
- L17 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(handleAuthSessionResponse) };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L23 _variable_ `template struct TInitialize<FWebAuth>;` (scope `UE::Jni`)

### `Plugins/Online/WebAuth/Source/Public/Android/AndroidPlatformWebAuth.h` (Public)


#### class `FAndroidWebAuth`  
`class FAndroidWebAuth : public IWebAuth`  
_L14-41_
- inherits: `IWebAuth`
- desc: Android implementation of Web Authentication
- L18 _public prototype_ `virtual bool AuthSessionWithURL(const FString &UrlStr, const FString &SchemeStr, const FWebAuthSessionCompleteDelegate& Delegate);`
- L20 _public prototype_ `virtual bool SaveCredentials(const FString& IdStr, const FString& TokenStr, const FString& EnvironmentNameStr);`
- L21 _public prototype_ `virtual bool LoadCredentials(FString& OutIdStr, FString& OutTokenStr, const FString& EnvironmentNameStr);`
- L23 _public prototype_ `virtual void DeleteLoginCookies(const FString& PrefixStr, const FString& SchemeStr, const FString& DomainStr, const FString& PathStr);`
- L26 _public prototype_ `void OnAuthSessionComplete(const FString &RedirectURL, bool bHasResponse);`
- L31 _public prototype_ `FAndroidWebAuth();` — Constructor
- L36 _public prototype_ `virtual ~FAndroidWebAuth();` — Destructor
- L40 _private member_ `FWebAuthSessionCompleteDelegate AuthSessionCompleteDelegate;` — Delegate that will get called once an authentication session completes or for an error condition

#### class `FAndroidPlatformWebAuth`  
`class FAndroidPlatformWebAuth : public FGenericPlatformWebAuth`  
_L47-51_
- inherits: `FGenericPlatformWebAuth`
- desc: Platform specific WebAuth implementations
- L50 _public prototype_ `static IWebAuth* CreatePlatformWebAuth();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WEBAUTH_API`
- L54 _typedef_ `typedef FAndroidPlatformWebAuth FPlatformWebAuth;`

### `Plugins/Online/WebAuth/Source/Public/GenericPlatform/GenericPlatformWebAuth.h` (Public)


#### class `FGenericPlatformWebAuth`  
`class FGenericPlatformWebAuth`  
_L11-23_
- desc: Platform specific WebAuth implementations Intended usage is to use FPlatformWebAuth instead of FGenericPlatformWebAuth
- L19 _public function_ `static IWebAuth* CreatePlatformWebAuth()` — Creates a platform-specific WebAuth. @return nullptr if no implementation is available

### `Plugins/Online/WebAuth/Source/Public/IOS/IOSPlatformWebAuth.h` (Public)


#### class `FIOSWebAuth`  
`class FIOSWebAuth : public IWebAuth`  
_L16-43_
- inherits: `IWebAuth`
- desc: IOS implementation of Web Authentication
- L20 _public prototype_ `virtual bool AuthSessionWithURL(const FString &UrlStr, const FString &SchemeStr, const FWebAuthSessionCompleteDelegate& Delegate);`
- L22 _public prototype_ `virtual bool SaveCredentials(const FString& IdStr, const FString& TokenStr, const FString& EnvironmentNameStr);`
- L23 _public prototype_ `virtual bool LoadCredentials(FString& OutIdStr, FString& OutTokenStr, const FString& EnvironmentNameStr);`
- L25 _public prototype_ `virtual void DeleteLoginCookies(const FString& PrefixStr, const FString& SchemeStr, const FString& DomainStr, const FString& PathStr);`
- L31 _public prototype_ `FIOSWebAuth();` — Constructor
- L36 _public prototype_ `virtual ~FIOSWebAuth();` — Destructor
- L40 _private member_ `FDelegateHandle OpenUrlHandle;` — Delegate handle to get auth response from external browser
- L42 _private member_ `FWebAuthSessionCompleteDelegate AuthSessionCompleteDelegate;` — Delegate that will get called once an authentication session completes or for an error condition

#### class `FIOSPlatformWebAuth`  
`class FIOSPlatformWebAuth : public FGenericPlatformWebAuth`  
_L49-53_
- inherits: `FGenericPlatformWebAuth`
- desc: Platform specific WebAuth implementations
- L52 _public prototype_ `static IWebAuth* CreatePlatformWebAuth();`

#### Free symbols / members of external scopes

- L56 _typedef_ `typedef FIOSPlatformWebAuth FPlatformWebAuth;`

### `Plugins/Online/WebAuth/Source/Public/NullPlatformWebAuth.h` (Public)


#### class `FNullPlatformWebAuth`  
`class FNullPlatformWebAuth`  
_L10-22_
- desc: Null implementation of Web Authentication
- L18 _public function_ `static IWebAuth* CreatePlatformWebAuth()` — Creates a platform-specific WebAuth. @return nullptr if no implementation is available

#### Free symbols / members of external scopes

- L25 _typedef_ `typedef FNullPlatformWebAuth FPlatformWebAuth;`

### `Plugins/Online/WebAuth/Source/Public/PlatformWebAuth.h` (Public)
_(no declarations extracted)_

### `Plugins/Online/WebAuth/Source/Public/WebAuth.h` (Public)


#### class `IWebAuth`  
`class IWebAuth`  
_L17-31_
- L20 _public prototype_ `virtual bool AuthSessionWithURL(const FString &UrlStr, const FString &SchemeStr, const FWebAuthSessionCompleteDelegate& Delegate) = 0;`
- L22 _public prototype_ `virtual bool SaveCredentials(const FString& IdStr, const FString& TokenStr, const FString& EnvironmentNameStr) = 0;`
- L23 _public prototype_ `virtual bool LoadCredentials(FString& OutIdStr, FString& OutTokenStr, const FString& EnvironmentNameStr) = 0;`
- L25 _public prototype_ `virtual void DeleteLoginCookies(const FString& PrefixStr, const FString& SchemeStr, const FString& DomainStr, const FString& PathStr) = 0;`
- L30 _public prototype_ `virtual ~IWebAuth() = default;` — Destructor for overrides

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(FWebAuthSessionCompleteDelegate, const FString & , bool );` — Delegate called when an authentication session completes @param RedirectURL result received from authenication session attempt @param bHasResponse - true if the request was made, false if we did not proceed
- L15 _prototype_ `DECLARE_DELEGATE_TwoParams(FWebAuthSessionCompleteDelegate, const FString & , bool );` — Delegate called when an authentication session completes @param RedirectURL result received from authenication session attempt @param bHasResponse - true if the request was made, false if we did not proceed

### `Plugins/Online/WebAuth/Source/Public/WebAuthModule.h` (Public)


#### class `FWebAuthModule`  
`class FWebAuthModule : public IModuleInterface, public FSelfRegisteringExec`  
_L20-95_
- inherits: `IModuleInterface,FSelfRegisteringExec`
- desc: Module for Web Authentication implementation
- L29 _public prototype_ `bool HandleWebAuthCommand(const TCHAR* Cmd, FOutputDevice& Ar);` — Exec command handlers
- L39 _public prototype_ `static FWebAuthModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L46 _public function_ `inline IWebAuth& GetWebAuth()` — Get the WebAuth interface @return Web authentication request manager used by the module
- L58 _public function_ `inline bool IsAvailable()`
- L75 _protected prototype_ `virtual bool Exec_Dev(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — Handle exec commands starting with "WebAuth" @param InWorld	the world context @param Cmd		the exec command being executed @param Ar		the archive to log results to @return true if the handler consumed the input, false to continue searching handlers
- L84 _private prototype_ `virtual void StartupModule() override;` — Called when WebAuth module is loaded load dependant modules
- L89 _private prototype_ `virtual void ShutdownModule() override;` — Called when WebAuth module is unloaded
- L91 _private member_ `IWebAuth* WebAuth;`
- L94 _private member_ `static FWebAuthModule* Singleton;` — singleton for the module while loaded and available

#### Free symbols / members of external scopes

- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebAuth, Log, All);`
