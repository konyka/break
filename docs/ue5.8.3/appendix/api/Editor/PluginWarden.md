# Editor / PluginWarden

- module root: `Source/Editor/PluginWarden`
- headers: 4; symbols: 80
- symbol kinds: class=4, delegate=1, enum=2, enumerator=20, externvar=1, function=7, member=27, prototype=17, struct=1
- DynamicallyLoadedModuleNames: LauncherServices
- PrivateDependencyModuleNames: Analytics, Core, CoreUObject, EditorFramework, Engine, InputCore, LauncherPlatform, PortalServices, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: 

### `Source/Editor/PluginWarden/Private/PluginWardenAuthorizer.h` (Private)


#### enum `EPluginAuthorizationState`  
`enum class EPluginAuthorizationState`  
_L13-32_
- L15 _public enumerator_ `Initializing`
- L16 _public enumerator_ `StartLauncher`
- L17 _public enumerator_ `StartLauncher_Waiting`
- L18 _public enumerator_ `AuthorizePlugin`
- L19 _public enumerator_ `AuthorizePlugin_Waiting`
- L20 _public enumerator_ `IsUserSignedIn`
- L21 _public enumerator_ `IsUserSignedIn_Waiting`
- L22 _public enumerator_ `SigninRequired`
- L23 _public enumerator_ `SigninRequired_Waiting`
- L24 _public enumerator_ `Signin_Waiting`
- L25 _public enumerator_ `Signin_Timeout`
- L26 _public enumerator_ `SigninFailed`
- L27 _public enumerator_ `Authorized`
- L28 _public enumerator_ `Unauthorized`
- L29 _public enumerator_ `LauncherStartFailed`
- L30 _public enumerator_ `Timeout`
- L31 _public enumerator_ `Canceled`

#### class `FPluginWardenAuthorizer`  
`class FPluginWardenAuthorizer`  
_L34-94_
- L37 _public prototype_ `FPluginWardenAuthorizer(const FText& InPluginFriendlyName, const FString& InPluginItemId, const FString& InPluginOfferId, const EEntitlementCacheLevelRequest InCacheLevel);`
- L40 _public prototype_ `EPluginAuthorizationState UpdateAuthorizationState(float DeltaTime);` — Returns new state after elapsed time
- L42 _public function_ `const FText& GetPluginFriendlyName()`
- L43 _public function_ `const FString& GetPluginItemId()`
- L44 _public function_ `const FString& GetPluginOfferId()`
- L48 _private member_ `EPluginAuthorizationState CurrentState;` — The current state of the plug-in authorization pipeline.
- L51 _private member_ `EEntitlementCacheLevelRequest CacheLevel;` — Cache level to check for the entitlement
- L54 _private member_ `float WaitingTime;` — The amount of time we've been waiting for confirmation for a given step.  It's possible a problem may arise and we need to timeout.
- L57 _private member_ `FText PluginFriendlyName;` — The display name of the plug-in used in the auto generated dialog text.
- L60 _private member_ `FString PluginItemId;` — The unique id of the item for the plug-in on the marketplace.
- L63 _private member_ `FString PluginOfferId;` — The unique id of the offer for the plug-in on the marketplace.
- L66 _private member_ `unsigned int NumAuthorizationRetries;` — The current number of authorization check retries.
- L69 _private member_ `unsigned int NumSignInRetries;` — The current number of sign-in retries.
- L72 _private member_ `unsigned int NumLauncherRetries;` — The current number of Launcher start retries.
- L75 _private member_ `unsigned int CurrentWaitLoopNumber;` — The current loop number of wait loops during the sign-in wait phase.
- L78 _private member_ `TSharedPtr<IPortalApplicationWindow> PortalWindowService;` — The portal application communication service.
- L81 _private member_ `TSharedPtr<IPortalUser> PortalUserService;` — The portal user service, to allow us to check entitlements for plugins.
- L84 _private member_ `TSharedPtr<IPortalUserLogin> PortalUserLoginService;` — The portal user login service, to allow us to trigger a prompt to sign-in, if required.
- L87 _private member_ `TAsyncResult<FPortalUserIsEntitledToItemResult> EntitlementResult;` — The entitlement result we may be waiting on.
- L90 _private member_ `TAsyncResult<FPortalUserDetails> UserDetailsResult;` — The result from the request for user details.
- L93 _private member_ `TAsyncResult<bool> UserSigninResult;` — The result from requesting the user sign-in, they may sign-in, they may cancel.

### `Source/Editor/PluginWarden/Private/PluginWardenModule.h` (Private)


#### class `FPluginWardenModule`  
`class FPluginWardenModule : public IPluginWardenModule`  
_L20-59_
- inherits: `IPluginWardenModule`
- desc: The Plugin Warden is a simple module used to verify a user has purchased a plug-in.  This module won't prevent a determined user from avoiding paying for a plug-in, it is merely to prevent accidental violation of a per-seat license on a plug-in, and to direct those users to the marketplace page where they may purchase the plug-in.
- L27 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L32 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L51 _public prototype_ `virtual void CheckEntitlementForPlugin(const FText& PluginFriendlyName, const FString& PluginItemId, const FString& PluginOfferId, const EEntitlementCacheLevelRequest CacheLevel, const FText& UnauthorizedMessageOverride, EUnauthorizedErrorHandling UnauthorizedErrorHandling, TFunction<void()> AuthorizedCallback) override;` — Ask the launcher if the user has authorization to use the given plug-in. The authorized callback will only be called if the user is authorized to use the plug-in. FPluginWardenModule& PluginWarden = FModuleManager::LoadModuleChecked<FPluginWardenModule>("PluginWarden"); PluginWarden.CheckEntitlementForPlugin(LOCTEXT("AwesomePluginName", "My Awesome Plugin"), TEXT("PLUGIN_MARKETPLACE_GUID"), [&] () { // Authorized Code Here }); @param PluginFriendlyName The localized friendly name of the plug-in. @param PluginItemId The unique identifier of the item plug-in on the marketplace. @param PluginOfferId The unique identifier of the offer for the plug-in on the marketplace. @param CacheLevel Where to check for the entitlements. Defaults to memory. @param UnauthorizedMessageOverride The error message to display for unauthorized plugins, overriding the default message if not empty. @param UnauthorizedErrorHandling How to handle the unauthorized error. @param AuthorizedCallback This function will be called after the user has been given entitlement.
- L54 _public prototype_ `virtual void CheckEntitlementForPlugin(const FText& PluginFriendlyName, const FString& PluginItemId, const FString& PluginOfferId, const FText& UnauthorizedMessageOverride, EUnauthorizedErrorHandling UnauthorizedErrorHandling, TFunction<void()> AuthorizedCallback) override;`
- L58 _private prototype_ `bool RunAuthorizationPipeline(const FText& PluginFriendlyName, const FString& PluginItemId, const FString& PluginOfferId, const EEntitlementCacheLevelRequest CacheLevel);`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(PluginWarden, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(PluginWarden, Log, All);`

### `Source/Editor/PluginWarden/Private/SAuthorizingPlugin.h` (Private)


#### class `SAuthorizingPlugin`  
`class SAuthorizingPlugin : public SCompoundWidget`  
_L21-90_
- inherits: `SCompoundWidget`
- desc: The authorizing plug-in ui guides the user through the process of certifying their access to the plug-in.
- L24 _public function_ `SLATE_BEGIN_ARGS(SAuthorizingPlugin)`
- L42 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SWindow>& InParentWindow, const FPluginInfo& PluginInfo, const EEntitlementCacheLevelRequest CacheLevel, TFunction<void()> InAuthorizedCallback);`
- L50 _public prototype_ `void SetUnauthorizedOverride(const FText& InUnauthorizedMessageOverride, IPluginWardenModule::EUnauthorizedErrorHandling UnauthorizedErrorHandling);` — Override the default message and behavior in the case where the plugin is unauthorized. @param UnauthorizedMessageOverride The error message to display for unauthorized plugins, overriding the default message if not empty. @param UnauthorizedErrorHandling How to handle the unauthorized error.
- L54 _private prototype_ `FText GetWaitingText() const;`
- L56 _private prototype_ `EActiveTimerReturnType RefreshStatus(double InCurrentTime, float InDeltaTime);`
- L59 _private prototype_ `FReply OnCancel();` — Called when the user presses the Cancel button.
- L61 _private prototype_ `void OnWindowClosed(const TSharedRef<SWindow>& InWindow);`
- L64 _private prototype_ `void ShowStorePageForPlugin();` — Show the store page for the plug-in, happens in response to the user asking to see the store page when license detection fails.
- L68 _private member_ `TWeakPtr<SWindow> ParentWindow;` — The parent window holding this dialog, for when we need to trigger a close.
- L71 _private member_ `FText UnauthorizedMessageOverride;` — The optional error message to display in case plugin is unauthorized. If empty, will default to standard message.
- L74 _private member_ `IPluginWardenModule::EUnauthorizedErrorHandling UnauthorizedErrorHandling;` — Flag that sets the handling mechanism for when plugin is not authorized
- L77 _private member_ `bool bUserInterrupted;` — Flag for tracking user interruption of the process, either with the cancel button or the close button.
- L80 _private member_ `EPluginAuthorizationState AuthorizationState;` — The latest state of the plug-in authorization pipeline.
- L83 _private member_ `EPluginAuthorizationState PreviousAuthorizationState;` — The previous state of the plug-in authorization pipeline.
- L86 _private member_ `TFunction<void()> AuthorizedCallback;` — If the user is authorized to us the plug-in, we'll call this function to alert the plug-in that everything is good to go.
- L89 _private member_ `TSharedPtr<FPluginWardenAuthorizer> Authorizer;` — The executioner of the authorization pipeline.

#### struct `SAuthorizingPlugin::FPluginInfo`  
`struct FPluginInfo`  
_L28-40_
- L30 _public function_ `FPluginInfo( const FText& InFriendlyName, const FString& InItemId, const FString& InOfferId ) : FriendlyName( InFriendlyName ) , ItemId( InItemId ) , OfferId( InOfferId )`
- L37 _public member_ `const FText& FriendlyName;`
- L38 _public member_ `const FString& ItemId;`
- L39 _public member_ `const FString& OfferId;`

#### Free symbols / members of external scopes

- L16 _externvar_ `extern TSet<FString> AuthorizedPlugins;`

### `Source/Editor/PluginWarden/Public/IPluginWardenModule.h` (Public)


#### class `IPluginWardenModule`  
`class IPluginWardenModule : public IModuleInterface`  
_L16-84_
- inherits: `IModuleInterface`
- desc: The Plugin Warden is a simple module used to verify a user has purchased a plug-in.  This module won't prevent a determined user from avoiding paying for a plug-in, it is merely to prevent accidental violation of a per-seat license on a plug-in, and to direct those users to the marketplace page where they may purchase the plug-in.
- L26 _public function_ `static inline IPluginWardenModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L79 _public prototype_ `virtual void CheckEntitlementForPlugin(const FText& PluginFriendlyName, const FString& PluginItemId, const FString& PluginOfferId, const EEntitlementCacheLevelRequest CacheLevel, const FText& UnauthorizedMessageOverride, EUnauthorizedErrorHandling UnauthorizedErrorHandling, TFunction<void()> AuthorizedCallback) = 0;` — Ask the Unreal Engine Launcher if the user has authorization to use the given plug-in. The authorized callback will only be called if the user is authorized to use the plug-in. ### WARNING ### WARNING ### WARNING ### WARNING ### WARNING ### Do not gate the user in inline custom plug-in UI, like inside a customization in the details panel.  Only use this to gate the user from opening a dialog or some other big explicit action that opens up into UI that is exclusively the domain of your plug-in.  An example of a good place to use this would be inside of OpenAssetEditor(), in your derived version of FAssetTypeActions_Base for the custom assets your plug-in handles. ### WARNING ### WARNING ### WARNING ### WARNING ### WARNING ### IPluginWardenModule::Get().CheckEntitlementForPlugin(LOCTEXT("AwesomePluginName", "My Awesome Plugin"), TEXT("PLUGIN_MARKETPLACE_GUID"), [&] () { // Code Here Will Run If Authorized }); @param PluginFriendlyName The localized friendly name of the plug-in. @param PluginItemId The unique identifier of the item plug-in on the marketplace. @param PluginOfferId The unique identifier of the offer for the plug-in on the marketplace. @param CacheLevel Where to check for the entitlements. Defaults to memory. @param UnauthorizedMessageOverride The error message to display for unauthorized plugins, overriding the default message if not empty. @param UnauthorizedErrorHandling How to handle the unauthorized error. @param AuthorizedCallback This function will be called
- L82 _public prototype_ `virtual void CheckEntitlementForPlugin(const FText& PluginFriendlyName, const FString& PluginItemId, const FString& PluginOfferId, const FText& UnauthorizedMessageOverride, EUnauthorizedErrorHandling UnauthorizedErrorHandling, TFunction<void()> AuthorizedCallback) = 0;`

#### enum `IPluginWardenModule::EUnauthorizedErrorHandling`  
`enum class EUnauthorizedErrorHandling`  
_L44-52_
- desc: This enum efines how Unauthorized items are handled
- L47 _public enumerator_ `Silent` — Handle error silently, no popups
- L49 _public enumerator_ `ShowMessage` — Show the default or overriden message in a popup
- L51 _public enumerator_ `ShowMessageOpenStore` — Show the default or overriden message in a popup, and ask the user if they want to open the Marketplace
