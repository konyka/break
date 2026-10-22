# Plugins / LoginFlow

- module root: `Plugins/Online/OnlineFramework/Source/LoginFlow`
- headers: 7; symbols: 88
- symbol kinds: class=5, delegate=6, enum=1, enumerator=2, function=6, macro=2, member=19, prototype=45, struct=2
- DynamicallyLoadedModuleNames: Analytics, AnalyticsET
- PrivateDependencyModuleNames: OnlineSubsystem, SlateCore, WebBrowser
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core, CoreOnline, CoreUObject, InputCore, Slate

### `Plugins/Online/OnlineFramework/Source/LoginFlow/Private/LoginFlowPrivate.h` (Private)


#### Free symbols / members of external scopes

- L15 _macro_ `#define FACTORY(ReturnType, Type, ...) \`
- L22 _macro_ `#define IFACTORY(ReturnType, Type, ...) \`

### `Plugins/Online/OnlineFramework/Source/LoginFlow/Private/LoginFlowViewModel.h` (Private)


#### class `FLoginFlowViewModel`  
`class FLoginFlowViewModel : public TSharedFromThis<FLoginFlowViewModel>`  
_L12-49_
- inherits: `TSharedFromThis<FLoginFlowViewModel>`
- desc: Represents the view transformation for the login flow.
- L16 _public prototype_ `virtual ~FLoginFlowViewModel() = default;`
- L19 _public prototype_ `virtual FString GetLoginFlowUrl() = 0;` — @return the starting web page
- L26 _public prototype_ `virtual void HandleRequestClose(const FString& CloseInfo) = 0;` — Handle a request to close the browser window @param CloseInfo reason for the closure
- L31 _public prototype_ `virtual void HandleLoadError() = 0;` — Handle a browser window load error
- L38 _public prototype_ `virtual bool HandleBrowserUrlChanged(const FText& Url) = 0;` — Browser window URL has changed @param Url new location
- L40 _public prototype_ `virtual bool HandleBeforeBrowse(const FString& Url) = 0;`
- L42 _public prototype_ `virtual bool HandleNavigation(const FString& Url) = 0;`
- L45 _public prototype_ `virtual const TSharedPtr<FBrowserContextSettings>& GetBrowserContextSettings() const = 0;` — @return the context settings for the underlying browser
- L48 _public prototype_ `virtual bool ShouldConsumeInput() const = 0;` — @return whether or not the login flow should consume any input not handled by the browser window

#### Free symbols / members of external scopes

- L51 _prototype_ `FACTORY(TSharedRef<FLoginFlowViewModel>, FLoginFlowViewModel, const FString& HomePage, const TSharedPtr<FBrowserContextSettings>& BrowserContextSettings, const FOnLoginFlowRequestClose& OnRequestClose, const FOnLoginFlowError& OnError, const FOnLoginFlowRedirectURL& OnRedirectURL, const bool bConsumeInput);`

### `Plugins/Online/OnlineFramework/Source/LoginFlow/Private/SLoginFlow.h` (Private)


#### class `SLoginFlow`  
`class SLoginFlow : public SUserWidget`  
_L13-26_
- inherits: `SUserWidget`
- desc: Top level widget expected to handle login flow through to completion (success, cancel, error)
- L18 _public function_ `SLATE_USER_ARGS(SLoginFlow) : _StyleSet(&FCoreStyle::Get())`
- L21 _public prototype_ `SLATE_ARGUMENT(const ISlateStyle*, StyleSet) SLATE_END_ARGS() virtual void Construct(const FArguments& InArgs, const TSharedRef<FLoginFlowViewModel>& InViewModel) = 0;`

### `Plugins/Online/OnlineFramework/Source/LoginFlow/Public/ILoginFlowManager.h` (Public)


#### class `ILoginFlowManager`  
`class ILoginFlowManager : public TSharedFromThis<ILoginFlowManager>`  
_L14-60_
- inherits: `TSharedFromThis<ILoginFlowManager>`
- desc: Create and configure one of these to enable web login flow in your application OnlineSubsystemFacebook for Windows requires this
- L18 _public function_ `ILoginFlowManager()`
- L19 _public prototype_ `virtual ~ILoginFlowManager() = default;`
- L24 _public prototype_ `DECLARE_DELEGATE(FOnPopupDismissed);` — Called when a popup is ready to be dismissed.
- L32 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FOnPopupDismissed, FOnDisplayPopup, const TSharedRef<SWidget>& );` — Fired when a login flow Pop-Up (web) window needs to be displayed. @Returns Delegate that will be called when the popup is dismissed (to clean up any slate borders created) @Param PopupWidget The widget that contains the browser window.
- L44 _public prototype_ `virtual bool AddLoginFlow(FName OnlineIdentifier, const FOnDisplayPopup& InPopupDelegate, const FOnDisplayPopup& InCreationFlowPopupDelegate, bool bPersistCookies = true, bool bConsumeInput = false) = 0;` — Register an online subsystem with the login flow factory (call at startup) @param OnlineIdentifier online subsystem identifier requiring a login flow UI @param InPopupDelegate external delegate to receive widgets from the login flow @param InCreationFlowPopupDelegate external delegate to receive widgets from the account creation flow @param bPersistCookies let the global web context manage cookies, or keep them in memory only @param bConsumeInput whether or not input, not handled by the widget, should be consumed an not bubbled up @return whether or not the login flow was successfully added
- L51 _public prototype_ `virtual bool HasLoginFlow(FName OnlineIdentifier) = 0;` — Has a given login flow been setup @return true if login flow added, false otherwise
- L54 _public prototype_ `virtual void CancelLoginFlow() = 0;` — Cancel an active login flow
- L56 _public prototype_ `virtual void CancelAccountCreationFlow() = 0;` — Cancel an active account creation flow
- L59 _public prototype_ `virtual void Reset() = 0;` — Cleanup and remove all registered login flows, detaching from online subsystems

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DELEGATE(FOnPopupDismissed);` — Called when a popup is ready to be dismissed.
- L32 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FOnPopupDismissed, FOnDisplayPopup, const TSharedRef<SWidget>& );` — Fired when a login flow Pop-Up (web) window needs to be displayed. @Returns Delegate that will be called when the popup is dismissed (to clean up any slate borders created) @Param PopupWidget The widget that contains the browser window.

### `Plugins/Online/OnlineFramework/Source/LoginFlow/Public/ILoginFlowModule.h` (Public)


#### enum `ELoginFlowErrorResult`  
`enum class ELoginFlowErrorResult : uint8`  
_L12-17_
- L14 _public enumerator_ `Unknown`
- L16 _public enumerator_ `LoadFail` — Webpage failed to load

#### class `ILoginFlowModule`  
`class ILoginFlowModule : public IModuleInterface`  
_L48-113_
- inherits: `IModuleInterface`
- desc: Interface for the login flow module.
- L59 _public function_ `static inline ILoginFlowModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L69 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L77 _public prototype_ `virtual TSharedPtr<ILoginFlowManager> CreateLoginFlowManager() const = 0;` — Create a login flow manager that will handle the proper interactions between the code requiring a login flow UI and the application
- L107 _public prototype_ `virtual TSharedRef<class SWidget> CreateLoginFlowWidget(const FCreateSettings& Settings) const = 0;` — Creates a login flow widget. @return The new widget.
- L112 _public prototype_ `virtual ~ILoginFlowModule() = default;` — Virtual destructor.

#### struct `ILoginFlowModule::FCreateSettings`  
`struct FCreateSettings`  
_L79-100_
- L82 _public member_ `FString Url;` — Starting URL for login flow
- L84 _public member_ `ISlateStyle* StyleSet;` — Optional Slate style for the internal widgets
- L86 _public member_ `TSharedPtr<FBrowserContextSettings> BrowserContextSettings;` — Optional browser context settings
- L88 _public member_ `FOnLoginFlowRequestClose CloseCallback;` — Delegate to fire on widget closure
- L90 _public member_ `FOnLoginFlowError ErrorCallback;` — Delegate to fire on flow error
- L92 _public member_ `FOnLoginFlowRedirectURL RedirectCallback;` — Delegate to fire for every URL redirect
- L94 _public member_ `bool bConsumeInput;` — Whether or not the widget should consume input not handled by the browser
- L96 _public function_ `FCreateSettings() : StyleSet(nullptr) , bConsumeInput(false)`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLoginFlow, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLoginFlow, Log, All);`
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnLoginFlowError, ELoginFlowErrorResult , const FString& );` — Delegate executed when there is an error dealing with the entirety of the login flow @param ErrorType type of login flow failure @param ErrorInfo extended information about the error
- L25 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnLoginFlowError, ELoginFlowErrorResult , const FString& );` — Delegate executed when there is an error dealing with the entirety of the login flow @param ErrorType type of login flow failure @param ErrorInfo extended information about the error
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLoginFlowRequestClose, const FString& );` — Delegate executed when the login flow is handling a closure of the browser window @param CloseInfo reason for the closure
- L32 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLoginFlowRequestClose, const FString& );` — Delegate executed when the login flow is handling a closure of the browser window @param CloseInfo reason for the closure
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnLoginFlowRedirectURL, const FString& );` — Delegate executed when a redirect URL is about to be handled by the browser window @param RedirectURL destination of the redirect @return true if the redirect was handled, false otherwise
- L41 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnLoginFlowRedirectURL, const FString& );` — Delegate executed when a redirect URL is about to be handled by the browser window @param RedirectURL destination of the redirect @return true if the redirect was handled, false otherwise

### `Plugins/Online/OnlineFramework/Source/LoginFlow/Public/LoginFlow.h` (Public)
_(no declarations extracted)_

### `Plugins/Online/OnlineFramework/Source/LoginFlow/Public/LoginFlowManager.h` (Public)


#### class `FLoginFlowManager`  
`class FLoginFlowManager : public ILoginFlowManager`  
_L20-113_
- inherits: `ILoginFlowManager`
- desc: Create and configure one of these to enable web login flow in your application OnlineSubsystemFacebook and OnlineSubsystemGoogle for Windows requires this
- L24 _public prototype_ `FLoginFlowManager();`
- L25 _public prototype_ `~FLoginFlowManager();`
- L28 _public prototype_ `virtual bool AddLoginFlow(FName OnlineIdentifier, const FOnDisplayPopup& InPopupDelegate, const FOnDisplayPopup& InCreationFlowPopupDelegate, bool bPersistCookies, bool bConsumeInput) override;`
- L29 _public prototype_ `virtual bool HasLoginFlow(FName OnlineIdentifier) override;`
- L30 _public prototype_ `virtual void CancelLoginFlow() override;`
- L31 _public prototype_ `virtual void CancelAccountCreationFlow() override;`
- L32 _public prototype_ `virtual void Reset() override;`
- L42 _private prototype_ `void OnLoginFlow_Error(ELoginFlowErrorResult ErrorType, const FString& ErrorInfo, FString InstanceId);` — Delegate fired by the web engine on any error
- L44 _private prototype_ `void OnLoginFlow_Close(const FString& CloseInfo, FString InstanceId);` — Delegate fired when the browser window is closed
- L46 _private prototype_ `bool OnLoginFlow_RedirectURL(const FString& RedirectURL, FString InstanceId);` — Delegate fired when the browser window indicates a URL redirect
- L48 _private prototype_ `void OnLoginFlowStarted(const FString& RequestedURL, const FOnLoginRedirectURL& OnRedirectURL, const FOnLoginFlowComplete& OnLoginFlowComplete, bool& bOutShouldContinueLogin, FName InOnlineIdentifier);` — Delegate fired when a login flow is requested by an external provider
- L50 _private prototype_ `void FinishLogin();` — Finish login flow, notifying listeners
- L53 _private prototype_ `void OnLoginFlowLogout(const TArray<FString>& LoginDomains, FName OnlineIdentifier);` — Delegate fired by online identity when a logout/cleanup is requested
- L62 _private prototype_ `void OnAccountCreationFlow_Error(ELoginFlowErrorResult ErrorType, const FString& ErrorInfo, FString InstanceId);` — Delegate fired by the web engine on any error
- L64 _private prototype_ `void OnAccountCreationFlow_Close(const FString& CloseInfo, FString InstanceId);` — Delegate fired when the browser window is closed
- L66 _private prototype_ `bool OnAccountCreationFlow_RedirectURL(const FString& RedirectURL, FString InstanceId);` — Delegate fired when the browser window indicates a URL redirect
- L68 _private prototype_ `void OnAccountCreationFlowStarted(const FString& RequestedURL, const FOnLoginRedirectURL& OnRedirectURL, const FOnLoginFlowComplete& OnAccountCreationFlowComplete, bool& bOutShouldContinueAccountCreation, FName InOnlineIdentifier);` — Delegate fired when an account creation flow is requested by an external provider
- L70 _private prototype_ `void FinishAccountCreation();` — Finish account creation flow, notifying listeners
- L75 _private function_ `bool IsFlowInProgress() const`
- L104 _private prototype_ `void RegisterBrowserContext(FOnlineParams* Params);` — Register a flow with the web browser singleton @param Params online flow parameters to register
- L107 _private member_ `TMap<FName, FOnlineParams> OnlineSubsystemsMap;` — Mapping of online subsystem identifiers to the parameters they have setup for login flow
- L110 _private member_ `TUniquePtr<FLoginFlowProperties> PendingLogin;` — Properties related to the current login attempt
- L112 _private member_ `TUniquePtr<FAccountCreationFlowProperties> PendingAccountCreation;` — Properties related to the current account creation attempt

#### struct `FLoginFlowManager::FOnlineParams`  
`struct FOnlineParams`  
_L77-97_
- L80 _public member_ `FName OnlineIdentifier;` — Online identifier <subsystem>:<instancename> that describes the OnlineSubsystem
- L82 _public member_ `FOnDisplayPopup OnLoginFlowPopup;` — Single-cast delegate instance (bind to this to handle login flow display)
- L84 _public member_ `FDelegateHandle LoginFlowUIRequiredDelegateHandle;` — Handle to bound login flow ui required delegate
- L86 _public member_ `FDelegateHandle LoginFlowLogoutDelegateHandle;` — Handle to bound login flow logout delegate
- L88 _public member_ `FOnDisplayPopup OnAccountCreationFlowPopup;` — Single-cast delegate instance (bind to this to handle account creation flow display)
- L90 _public member_ `FDelegateHandle AccountCreationFlowUIRequiredDelegateHandle;` — Handle to bound account creation flow ui required delegate
- L92 _public member_ `TSharedPtr<FBrowserContextSettings> BrowserContextSettings;` — Optional browser context settings if bPersistCookies is false
- L94 _public member_ `bool bRegisteredContext = false;` — Has this context been registered
- L96 _public member_ `bool bConsumeInput = false;` — Whether or not keyboard input, not handled by the browser, should be consumed
