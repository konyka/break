# Plugins / EOSShared

- module root: `Plugins/Online/EOSShared/Source/EOSShared`
- headers: 11; symbols: 367
- symbol kinds: class=14, delegate=12, function=29, macro=9, member=73, namespace=5, prototype=193, struct=8, typedef=24
- PrivateDependencyModuleNames: ApplicationCore, Slate
- PrivateIncludePathModuleNames: Engine, SteamShared
- PublicDependencyModuleNames: Core, EOSSDK

### `Plugins/Online/EOSShared/Source/EOSShared/Private/Android/AndroidEOSSDKManager.h` (Private)


#### class `FAndroidEOSSDKManager`  
`class FAndroidEOSSDKManager : public FEOSSDKManager`  
_L9-17_
- inherits: `FEOSSDKManager`
- L12 _public prototype_ `FAndroidEOSSDKManager();`
- L13 _public prototype_ `~FAndroidEOSSDKManager();`
- L15 _public prototype_ `virtual EOS_EResult EOSInitialize(EOS_InitializeOptions& Options) override;`
- L16 _public prototype_ `virtual FString GetCacheDirBase() const override;`

#### Free symbols / members of external scopes

- L19 _typedef_ `using FPlatformEOSSDKManager = FAndroidEOSSDKManager;`

### `Plugins/Online/EOSShared/Source/EOSShared/Private/EOSSDKManager.h` (Private)


#### class `FEOSSDKManager`  
`class FEOSSDKManager : public IEOSSDKManager, public FSelfRegisteringExec`  
_L32-169_
- inherits: `IEOSSDKManager,FSelfRegisteringExec`
- L37 _public prototype_ `FEOSSDKManager();`
- L38 _public prototype_ `virtual ~FEOSSDKManager();`
- L41 _public function_ `virtual bool IsInitialized() const override`
- L43 _public prototype_ `virtual const FEOSSDKPlatformConfig* GetPlatformConfig(const FString& PlatformConfigName, bool bLoadIfMissing = false) override;`
- L44 _public prototype_ `virtual bool AddPlatformConfig(const FEOSSDKPlatformConfig& PlatformConfig, bool bOverwriteExistingConfig = false) override;`
- L45 _public prototype_ `virtual const FString& GetDefaultPlatformConfigName() override;`
- L46 _public prototype_ `virtual void SetDefaultPlatformConfigName(const FString& PlatformConfigName) override;`
- L48 _public prototype_ `virtual IEOSPlatformHandlePtr CreatePlatform(const FString& PlatformConfigName, FName InstanceName = NAME_None) override;`
- L49 _public prototype_ `virtual IEOSPlatformHandlePtr CreatePlatform(EOS_Platform_Options& PlatformOptions) override;`
- L50 _public prototype_ `virtual TArray<IEOSPlatformHandlePtr> GetActivePlatforms() override;`
- L52 _public prototype_ `virtual FString GetSDKVersion() const override;`
- L53 _public prototype_ `virtual FString GetProductName() const override;`
- L54 _public prototype_ `virtual FString GetProductVersion() const override;`
- L55 _public prototype_ `virtual FString GetCacheDirBase() const override;`
- L56 _public prototype_ `virtual FString GetOverrideCountryCode(const EOS_HPlatform Platform) const override;`
- L57 _public prototype_ `virtual FString GetOverrideLocaleCode(const EOS_HPlatform Platform) const override;`
- L59 _public prototype_ `virtual void LogInfo(int32 Indent = 0) const override;`
- L60 _public prototype_ `virtual void LogPlatformInfo(const EOS_HPlatform Platform, int32 Indent = 0) const override;`
- L61 _public prototype_ `virtual void LogAuthInfo(const EOS_HPlatform Platform, const EOS_EpicAccountId LoggedInAccount, int32 Indent = 0) const override;`
- L62 _public prototype_ `virtual void LogUserInfo(const EOS_HPlatform Platform, const EOS_EpicAccountId LoggedInAccount, const EOS_EpicAccountId TargetAccount, int32 Indent = 0) const override;`
- L63 _public prototype_ `virtual void LogPresenceInfo(const EOS_HPlatform Platform, const EOS_EpicAccountId LoggedInAccount, const EOS_EpicAccountId TargetAccount, int32 Indent = 0) const override;`
- L64 _public prototype_ `virtual void LogFriendsInfo(const EOS_HPlatform Platform, const EOS_EpicAccountId LoggedInAccount, int32 Indent = 0) const override;`
- L65 _public prototype_ `virtual void LogConnectInfo(const EOS_HPlatform Platform, const EOS_ProductUserId LoggedInAccount, int32 Indent = 0) const override;`
- L67 _public prototype_ `virtual void AddCallbackObject(TUniquePtr<class FCallbackBase> CallbackObj) override;`
- L69 _public prototype_ `virtual TSharedRef<IEOSFastTickLock> GetFastTickLock() override;`
- L72 _public prototype_ `virtual EOS_EResult Initialize();`
- L73 _public prototype_ `void Shutdown();`
- L77 _protected prototype_ `virtual bool Exec_Runtime(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L80 _protected prototype_ `virtual EOS_EResult EOSInitialize(EOS_InitializeOptions& Options);`
- L81 _protected prototype_ `virtual IEOSPlatformHandlePtr CreatePlatform(const FEOSSDKPlatformConfig& PlatformConfig, EOS_Platform_Options& PlatformOptions);`
- L82 _protected prototype_ `virtual bool Tick(float);`
- L83 _protected prototype_ `virtual const void* GetIntegratedPlatformOptions();`
- L84 _protected prototype_ `virtual EOS_IntegratedPlatformType GetIntegratedPlatformType();`
- L88 _protected prototype_ `virtual void OnBackBufferReady_RenderThread(SWindow& SlateWindow, ISlateViewportProvider& ViewportProvider);` — Provided to `OnBackBufferReadyToPresent` to get access to the render thread.
- L93 _protected prototype_ `virtual bool IsRenderReady();` — Check that the overlay is ready to be rendered. This will also add the Back Buffer Ready To Present handler.
- L96 _protected prototype_ `static void OnDisplaySettingsUpdated(const EOS_UI_OnDisplaySettingsUpdatedCallbackInfo* Data);`
- L97 _protected prototype_ `void RegisterDisplaySettingsUpdatedCallback(const EOS_HPlatform PlatformHandle);`
- L99 _protected prototype_ `void SetInvokeOverlayButton(const EOS_HPlatform PlatformHandle);`
- L100 _protected prototype_ `void ApplyOverlayPlatformOptions(EOS_Platform_Options& PlatformOptions);`
- L101 _protected prototype_ `EOS_HIntegratedPlatformOptionsContainer CreateIntegratedPlatformOptionsContainer();`
- L102 _protected prototype_ `void ApplyIntegratedPlatformOptions(EOS_HIntegratedPlatformOptionsContainer& Container);`
- L103 _protected prototype_ `virtual void ApplySystemSpecificOptions(const void*& SystemSpecificOptions);`
- L104 _protected prototype_ `void CallUIPrePresent(const EOS_UI_PrePresentOptions& Options);`
- L106 _protected prototype_ `static EOS_ENetworkStatus ConvertNetworkStatus(ENetworkConnectionStatus Status);`
- L107 _protected prototype_ `void OnNetworkConnectionStatusChanged(ENetworkConnectionStatus LastConnectionState, ENetworkConnectionStatus ConnectionState);`
- L108 _protected prototype_ `void OnApplicationStatusChanged(EOS_EApplicationStatus ApplicationStatus);`
- L109 _protected member_ `EOS_EApplicationStatus CachedApplicationStatus = EOS_EApplicationStatus::EOS_AS_Foreground;`
- L114 _protected prototype_ `void OnConfigSectionsChanged(const FString& IniFilename, const TSet<FString>& SectionName);`
- L115 _protected prototype_ `void LoadConfig();`
- L116 _protected prototype_ `void ReleasePlatform(EOS_HPlatform PlatformHandle);`
- L117 _protected prototype_ `void ReleaseReleasedPlatforms();`
- L118 _protected prototype_ `void SetupTicker();`
- L119 _protected prototype_ `void OnLogVerbosityChanged(const FLogCategoryName& CategoryName, ELogVerbosity::Type OldVerbosity, ELogVerbosity::Type NewVerbosity);`
- L122 _protected prototype_ `void LoadSDKHandle();`
- L123 _protected member_ `void* SDKHandle = nullptr;`
- L127 _protected member_ `mutable FRWLock ActivePlatformsCS;` — Critical Section to make sure the ActivePlatforms and ReleasedPlatforms arrays are thread safe
- L130 _protected member_ `bool bInitialized = false;` — Are we currently initialized
- L132 _protected member_ `bool bRenderReady = false;` — Tracks if the render init has completed.
- L134 _protected member_ `uint8 PlatformTickIdx = 0;` — Index of the last ticked platform, used for round-robin ticking when ConfigTickIntervalSeconds > 0
- L136 _protected member_ `TMap<EOS_HPlatform, IEOSPlatformHandleWeakPtr> ActivePlatforms;` — Created platforms actively ticking
- L138 _protected member_ `TArray<EOS_HPlatform> ReleasedPlatforms;` — Contains platforms released with ReleasePlatform, which we will release on the next Tick.
- L141 _protected member_ `FTSTicker::FDelegateHandle TickerHandle;` — Handle to ticker delegate for Tick(), valid whenever there are ActivePlatforms to tick, or ReleasedPlatforms to release.
- L143 _protected member_ `TArray<TUniquePtr<FCallbackBase>> CallbackObjects;` — Callback objects, to be released after EOS_Shutdown
- L145 _protected member_ `TMap<FString, FEOSSDKPlatformConfig> PlatformConfigs;` — Cache of named platform configs that have been loaded from ini files or added manually.
- L147 _protected member_ `FString DefaultPlatformConfigName;` — Default platform config name to use.
- L149 _protected member_ `TMap<FString, TMap<FName, IEOSPlatformHandleWeakPtr>> PlatformHandles;` — Cache of named platform handles that have been created.
- L151 _protected member_ `TWeakPtr<IEOSFastTickLock> FastTickLock;` — If this is set, then we should ignore the config tick rate and tick at full speed.
- L155 _protected member_ `double ConfigTickIntervalSeconds = 0.f;` — Interval between platform ticks. 0 means we tick every frame.
- L158 _protected member_ `bool bEnablePlatformIntegration = false;` — Whether or not the integrated platform options container will be set at platform creation time
- L161 _protected member_ `bool bEnableOverlayIntegration = false;` — Whether or not to integrate with the overlay (forward inputs, set up renderer callbacks etc)
- L164 _protected member_ `EOS_UI_EInputStateButtonFlags InvokeOverlayButtonCombination;` — Button combination to bring up the overlay (only used in certain platforms)
- L167 _protected member_ `EOS_EIntegratedPlatformManagementFlags IntegratedPlatformManagementFlags = {};` — Management flags passed on as options in integrated platform setup

#### struct `FEOSPlatformHandle`  
`struct FEOSPlatformHandle : public IEOSPlatformHandle`  
_L171-198_
- inherits: `IEOSPlatformHandle`
- L173 _public function_ `FEOSPlatformHandle(FEOSSDKManager& InManager, EOS_HPlatform InPlatformHandle) : IEOSPlatformHandle(InPlatformHandle), Manager(InManager)`
- L178 _public prototype_ `virtual ~FEOSPlatformHandle();`
- L179 _public prototype_ `virtual void Tick() override;`
- L180 _public prototype_ `virtual TSharedRef<IEOSFastTickLock> GetFastTickLock() override;`
- L182 _public prototype_ `virtual FString GetConfigName() const override;`
- L183 _public prototype_ `virtual FString GetOverrideCountryCode() const override;`
- L184 _public prototype_ `virtual FString GetOverrideLocaleCode() const override;`
- L186 _public prototype_ `virtual void LogInfo(int32 Indent = 0) const override;`
- L187 _public prototype_ `virtual void LogAuthInfo(const EOS_EpicAccountId LoggedInAccount, int32 Indent = 0) const override;`
- L188 _public prototype_ `virtual void LogUserInfo(const EOS_EpicAccountId LoggedInAccount, const EOS_EpicAccountId TargetAccount, int32 Indent = 0) const override;`
- L189 _public prototype_ `virtual void LogPresenceInfo(const EOS_EpicAccountId LoggedInAccount, const EOS_EpicAccountId TargetAccount, int32 Indent = 0) const override;`
- L190 _public prototype_ `virtual void LogFriendsInfo(const EOS_EpicAccountId LoggedInAccount, int32 Indent = 0) const override;`
- L191 _public prototype_ `virtual void LogConnectInfo(const EOS_ProductUserId LoggedInAccount, int32 Indent = 0) const override;`
- L194 _public member_ `FEOSSDKManager& Manager;` — Reference to the EOSSDK manager
- L197 _public member_ `FString ConfigName;` — The name of the config used to instantiate this handle

#### struct `FEOSFastTickLock`  
`struct FEOSFastTickLock : public IEOSFastTickLock`  
_L200-203_
- inherits: `IEOSFastTickLock`
- L202 _public prototype_ `virtual ~FEOSFastTickLock();`

### `Plugins/Online/EOSShared/Source/EOSShared/Private/EOSSharedModule.h` (Private)


#### class `FEOSSharedModule`  
`class FEOSSharedModule: public IModuleInterface`  
_L13-43_
- inherits: `IModuleInterface`
- L16 _public prototype_ `FEOSSharedModule() = default;`
- L17 _public prototype_ `~FEOSSharedModule() = default;`
- L19 _public prototype_ `static FEOSSharedModule* Get();`
- L21 _public function_ `const TArray<FString>& GetSuppressedLogStrings_Log() const`
- L22 _public function_ `const TArray<FString>& GetSuppressedLogCategories_Log() const`
- L23 _public function_ `const TArray<FString>& GetSuppressedLogStrings_VeryVerbose() const`
- L24 _public function_ `const TArray<FString>& GetSuppressedLogCategories_VeryVerbose() const`
- L27 _private prototype_ `virtual void StartupModule() override;`
- L28 _private prototype_ `virtual void ShutdownModule() override;`
- L31 _private prototype_ `void OnConfigSectionsChanged(const FString& IniFilename, const TSet<FString>& SectionNames);`
- L32 _private prototype_ `void LoadConfig();`
- L36 _private member_ `TUniquePtr<FEOSSDKManager> SDKManager;`
- L38 _private member_ `TArray<FString> SuppressedLogStrings_Log;`
- L39 _private member_ `TArray<FString> SuppressedLogCategories_Log;`
- L40 _private member_ `TArray<FString> SuppressedLogStrings_VeryVerbose;`
- L41 _private member_ `TArray<FString> SuppressedLogCategories_VeryVerbose;`
- L42 _private member_ `FDelegateHandle OnPostForkDelegateHandle;`

### `Plugins/Online/EOSShared/Source/EOSShared/Private/EOSVirtualMemoryCallbacks.h` (Private)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace EOSVirtualMemoryCallbacks`
- L21 _prototype_ `void* EOS_MEMORY_CALL Reserve(size_t SizeInBytes, EOS_EVM_AccessType AccessType, void** OutContextData);` (scope `EOSVirtualMemoryCallbacks`)
- L22 _prototype_ `EOS_Bool EOS_MEMORY_CALL Release(void* Address, size_t SizeInBytes, void* ContextData);` (scope `EOSVirtualMemoryCallbacks`)
- L23 _prototype_ `EOS_Bool EOS_MEMORY_CALL Commit(void* Address, size_t SizeInBytes, void* ContextData);` (scope `EOSVirtualMemoryCallbacks`)
- L24 _prototype_ `EOS_Bool EOS_MEMORY_CALL Decommit(void* Address, size_t SizeInBytes, void* ContextData);` (scope `EOSVirtualMemoryCallbacks`)

### `Plugins/Online/EOSShared/Source/EOSShared/Private/IOS/IOSEOSSDKManager.h` (Private)


#### class `FIOSEOSSDKManager`  
`class FIOSEOSSDKManager : public FEOSSDKManager`  
_L9-18_
- inherits: `FEOSSDKManager`
- L12 _public prototype_ `FIOSEOSSDKManager();`
- L13 _public prototype_ `~FIOSEOSSDKManager();`
- L15 _public prototype_ `virtual FString GetCacheDirBase() const override;`
- L17 _private prototype_ `void OnApplicationForegroundChanged(bool bWillBeOnBackground);`

#### Free symbols / members of external scopes

- L20 _typedef_ `using FPlatformEOSSDKManager = FIOSEOSSDKManager;`

### `Plugins/Online/EOSShared/Source/EOSShared/Private/Linux/LinuxEOSSDKManager.h` (Private)


#### Free symbols / members of external scopes

- L9 _typedef_ `using FPlatformEOSSDKManager = FEOSSDKManager;`

### `Plugins/Online/EOSShared/Source/EOSShared/Private/Mac/MacEOSSDKManager.h` (Private)


#### Free symbols / members of external scopes

- L9 _typedef_ `using FPlatformEOSSDKManager = FEOSSDKManager;`

### `Plugins/Online/EOSShared/Source/EOSShared/Private/Windows/WindowsEOSSDKManager.h` (Private)


#### class `FWindowsEOSSDKManager`  
`class FWindowsEOSSDKManager : public FEOSSDKManager`  
_L9-33_
- inherits: `FEOSSDKManager`
- L12 _public typedef_ `using Super = FEOSSDKManager;`
- L14 _public prototype_ `FWindowsEOSSDKManager();`
- L15 _public prototype_ `virtual ~FWindowsEOSSDKManager();`
- L16 _public prototype_ `virtual EOS_EResult Initialize() override;`
- L17 _public prototype_ `virtual IEOSPlatformHandlePtr CreatePlatform(EOS_Platform_Options& PlatformOptions) override;`
- L19 _protected prototype_ `virtual IEOSPlatformHandlePtr CreatePlatform(const FEOSSDKPlatformConfig& PlatformConfig, EOS_Platform_Options& PlatformOptions) override;`
- L21 _protected prototype_ `virtual const void* GetIntegratedPlatformOptions() override;`
- L22 _protected prototype_ `virtual EOS_IntegratedPlatformType GetIntegratedPlatformType() override;`
- L26 _protected member_ `TSharedPtr<class FSteamClientInstanceHandler> SteamAPIClientHandle;` — Steam Client API Handle
- L28 _protected member_ `EOS_IntegratedPlatform_Steam_Options PlatformSteamOptions;`
- L32 _public prototype_ `virtual FString GetCacheDirBase() const override;`

#### Free symbols / members of external scopes

- L35 _typedef_ `using FPlatformEOSSDKManager = FWindowsEOSSDKManager;`

### `Plugins/Online/EOSShared/Source/EOSShared/Public/EOSShared.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_WITH_EOS_SDK_APIVERSION_WARNINGS 1`
- L21 _macro_ `#define UE_EOS_CHECK_API_MISMATCH(Actual, Expected) \`
- L29 _macro_ `#define UE_EOS_CHECK_API_MISMATCH(Actual, Expected)`
- L44 _macro_ `#define WITH_EOS_RTC WITH_EOS_SDK && (EOS_MAJOR_VERSION >= 1 && EOS_MINOR_VERSION >= 13)`
- L48 _macro_ `#define WITH_EOS_P2P WITH_EOS_SDK`
- L51 _macro_ `#define EOS_ENUM_FORWARD_DECL(name) enum class name : int32_t;`
- L52 _prototype_ `EOS_ENUM_FORWARD_DECL(EOS_EApplicationStatus);`
- L53 _prototype_ `EOS_ENUM_FORWARD_DECL(EOS_EAuthScopeFlags);`
- L54 _prototype_ `EOS_ENUM_FORWARD_DECL(EOS_EAuthTokenType);`
- L55 _prototype_ `EOS_ENUM_FORWARD_DECL(EOS_EDesktopCrossplayStatus);`
- L56 _prototype_ `EOS_ENUM_FORWARD_DECL(EOS_EFriendsStatus);`
- L57 _prototype_ `EOS_ENUM_FORWARD_DECL(EOS_ELoginCredentialType);`
- L58 _prototype_ `EOS_ENUM_FORWARD_DECL(EOS_ENetworkStatus);`
- L59 _prototype_ `EOS_ENUM_FORWARD_DECL(EOS_EPacketReliability);`
- L60 _prototype_ `EOS_ENUM_FORWARD_DECL(EOS_ERTCAudioInputStatus);`
- L61 _prototype_ `EOS_ENUM_FORWARD_DECL(EOS_Presence_EStatus);`
- L62 _prototype_ `EOS_ENUM_FORWARD_DECL(EOS_UI_EInputStateButtonFlags);`
- L65 _macro_ `#define EOS_STRUCT_FORWARD_DECL(name) extern "C" typedef struct _tag ## name name;`
- L66 _prototype_ `EOS_STRUCT_FORWARD_DECL(EOS_UserInfo);`
- L67 _prototype_ `EOS_STRUCT_FORWARD_DECL(EOS_UserInfo_BestDisplayName);`
- L68 _prototype_ `EOS_STRUCT_FORWARD_DECL(EOS_RTC_Option);`
- L71 _typedef_ `extern "C" typedef uint32_t EOS_OnlinePlatformType`
- L73 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEOSSDK, Log, All);`
- L73 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEOSSDK, Log, All);`
- L74 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEOSShared, Log, All);`
- L74 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEOSShared, Log, All);`
- L76 _prototype_ `FString LexToString(const EOS_EResult EosResult);`
- L77 _prototype_ `const char* LexToUtf8String(const EOS_EResult EosResult);`
- L79 _prototype_ `FString LexToString(const EOS_ProductUserId UserId);`
- L80 _prototype_ `void LexFromString(EOS_ProductUserId& UserId, const TCHAR* String);`
- L81 _function_ `inline EOS_ProductUserId EOSProductUserIdFromString(const TCHAR* String)`
- L88 _prototype_ `FString LexToString(const EOS_EpicAccountId AccountId);`
- L89 _prototype_ `void LexFromString(EOS_EpicAccountId& AccountId, const TCHAR* String);`
- L91 _prototype_ `const TCHAR* LexToString(const EOS_EApplicationStatus ApplicationStatus);`
- L92 _prototype_ `const TCHAR* LexToString(const EOS_EAuthTokenType AuthTokenType);`
- L93 _prototype_ `const TCHAR* LexToString(const EOS_EDesktopCrossplayStatus DesktopCrossplayStatus);`
- L94 _prototype_ `const TCHAR* LexToString(const EOS_EExternalAccountType ExternalAccountType);`
- L95 _prototype_ `const TCHAR* LexToString(const EOS_EFriendsStatus FriendStatus);`
- L96 _prototype_ `const TCHAR* LexToString(const EOS_ELoginStatus LoginStatus);`
- L97 _prototype_ `const TCHAR* LexToString(const EOS_ENetworkStatus NetworkStatus);`
- L98 _prototype_ `const TCHAR* LexToString(const EOS_ERTCAudioInputStatus Status);`
- L99 _prototype_ `const TCHAR* LexToString(const EOS_Presence_EStatus PresenceStatus);`
- L100 _prototype_ `const TCHAR* LexToString(const EOS_EExternalCredentialType ExternalCredentialType);`
- L102 _prototype_ `bool LexFromString(EOS_EAuthScopeFlags& OutEnum, const FStringView& InString);`
- L103 _prototype_ `bool LexFromString(EOS_EExternalAccountType& OutEnum, const TCHAR* InString);`
- L104 _prototype_ `bool LexFromString(EOS_EIntegratedPlatformManagementFlags& OutEnum, const TCHAR* InString);`
- L105 _prototype_ `bool LexFromString(EOS_ELoginCredentialType& OutEnum, const TCHAR* InString);`
- L106 _prototype_ `bool LexFromString(EOS_EPacketReliability& OutEnum, const TCHAR* InString);`
- L107 _prototype_ `bool LexFromString(EOS_ERTCBackgroundMode& OutEnum, const TCHAR* InString);`
- L108 _prototype_ `bool LexFromString(EOS_UI_EInputStateButtonFlags& OutEnum, const TCHAR* InString);`
- L109 _prototype_ `bool LexFromString(EOS_EExternalCredentialType& OutEnum, const TCHAR* InString);`
- L111 _prototype_ `EOS_OnlinePlatformType EOSOnlinePlatformTypeFromString(const FStringView& InString);`
- L114 _prototype_ `FString GetBestDisplayNameStr(const EOS_UserInfo_BestDisplayName& BestDisplayName);` — Extracts the display name FString from a EOS_UserInfo_BestDisplayName using the following logic: Nickname > DisplayNameSanitized > DisplayName
- L116 _prototype_ `FString GetUserInfoDisplayNameStr(const EOS_UserInfo& UserInfo);` — Extracts the display name FString from a EOS_UserInfo using the following logic: Nickname > DisplayNameSanitized > DisplayName
- L118 _prototype_ `FString LexToString(const EOS_RTC_Option& Option);`

### `Plugins/Online/EOSShared/Source/EOSShared/Public/EOSSharedTypes.h` (Public)


#### class `FCallbackBase`  
`class FCallbackBase`  
_L23-27_
- desc: Used to store a pointer to the EOS callback object without knowing type
- L26 _public prototype_ `virtual ~FCallbackBase() = default;`

#### class `TEOSGlobalCallback`  
`template<typename CallbackFuncType, typename CallbackParamType, typename OwningType, typename CallbackReturnType = void, typename... CallbackExtraParams> class TEOSGlobalCallback : public FCallbackBase`  
_L33-89_
- inherits: `FCallbackBase`
- desc: Wrapper for EOS notification callbacks, ensures calling object is still alive before calling passed lambda.
- L37 _public member_ `TFunction<CallbackReturnType(const CallbackParamType*, CallbackExtraParams... ExtraParams)> CallbackLambda;`
- L39 _public function_ `TEOSGlobalCallback(TWeakPtr<OwningType> InOwner) : FCallbackBase() , Owner(InOwner)`
- L44 _public prototype_ `virtual ~TEOSGlobalCallback() = default;`
- L46 _public function_ `CallbackFuncType GetCallbackPtr()`
- L52 _public member_ `bool bIsGameThreadCallback = true;` — Is this callback intended for the game thread
- L56 _private member_ `TWeakPtr<OwningType> Owner;` — The object that needs to be checked for lifetime before calling the callback
- L58 _private function_ `static CallbackReturnType EOS_CALL CallbackImpl(const CallbackParamType* Data, CallbackExtraParams... ExtraParams)`

#### class `TEOSCallback`  
`template<typename CallbackFuncType, typename CallbackType, typename OwningType> class TEOSCallback : public FCallbackBase`  
_L93-140_
- inherits: `FCallbackBase`
- desc: Wrapper for EOS async API callbacks, ensures the caller is still alive before calling passed lambda, then deletes itself.
- L97 _public member_ `TFunction<void(const CallbackType*)> CallbackLambda;`
- L99 _public function_ `TEOSCallback(TWeakPtr<OwningType> InOwner) : FCallbackBase() , Owner(InOwner)`
- L104 _public function_ `TEOSCallback(TWeakPtr<const OwningType> InOwner) : FCallbackBase() , Owner(InOwner)`
- L109 _public prototype_ `virtual ~TEOSCallback() = default;`
- L111 _public function_ `CallbackFuncType GetCallbackPtr()`
- L118 _protected member_ `TWeakPtr<const OwningType> Owner;` — The object that needs to be checked for lifetime before calling the callback
- L121 _private function_ `static void EOS_CALL CallbackImpl(const CallbackType* Data)`

#### class `UE::Online::Private::TEOSCallback`  
`template<typename CallbackType> class TEOSCallback`  
_L148-182_
- desc: Class to handle all callbacks generically using a future to forward callback results
- L150 _private typedef_ `using CallbackFuncType = void (EOS_CALL*)(const CallbackType*);`
- L152 _public prototype_ `TEOSCallback() = default;`
- L153 _public function_ `TEOSCallback(TPromise<const CallbackType*>&& InPromise) : Promise(MoveTemp(InPromise))`
- L154 _public prototype_ `virtual ~TEOSCallback() = default;`
- L156 _public function_ `operator CallbackFuncType()`
- L161 _public function_ `TFuture<const CallbackType*> GetFuture()`
- L164 _private member_ `TPromise<const CallbackType*> Promise;`
- L166 _private function_ `static void EOS_CALL CallbackImpl(const CallbackType* Data)`

#### struct `UE::Online::Private::FEOSAsyncCallbackTraits`  
`template<typename Function> struct FEOSAsyncCallbackTraits;`  
_L186-189_
- L188 _public typedef_ `typedef TCallbackData CallbackDataType;`

#### struct `UE::Online::Private::FEOSAsyncTraits`  
`template<typename Function> struct FEOSAsyncTraits;`  
_L193-197_
- L195 _public typedef_ `typedef TEOSCallback CallbackType;`
- L196 _public typedef_ `typedef typename FEOSAsyncCallbackTraits<TEOSCallback>::CallbackDataType CallbackDataType;`

#### class `UE::Online::FEOSEventRegistration`  
`class FEOSEventRegistration`  
_L249-253_
- L252 _public prototype_ `virtual ~FEOSEventRegistration() = default;`

#### struct `UE::Online::Private::TEOSCallbackTraitsBase`  
`template<typename Component, typename EventData> struct TEOSCallbackTraitsBase<void (Component::*)(const EventData*)>`  
_L291-295_
- L293 _public typedef_ `typedef Component ComponentType;`
- L294 _public typedef_ `typedef EventData EventDataType;`

#### struct `UE::Online::Private::TEOSCallbackTraits`  
`template<typename Function> struct TEOSCallbackTraits : public TEOSCallbackTraitsBase<typename std::remove_reference<Function>::type>`  
_L298-300_
- inherits: `TEOSCallbackTraitsBase<typenamestd::remove_reference<Function>::type>`

#### struct `UE::Online::Private::TEOSNotifyRegisterTraits`  
`template<typename EOSHandle, typename Options, typename ClientData, typename NotificationFn, typename NotificationId> struct TEOSNotifyRegisterTraits<NotificationId (*)(EOSHandle, const Options*, ClientData*, NotificationFn)>`  
_L305-309_
- L307 _public typedef_ `typedef Options OptionsType;`
- L308 _public typedef_ `typedef NotificationId NotificationIdType;`

#### class `UE::Online::Private::FEOSEventRegistrationImpl`  
`class FEOSEventRegistrationImpl : public FEOSEventRegistration`  
_L317-367_
- inherits: `FEOSEventRegistration`
- L325 _public typedef_ `EOSHandle, EOSNotfyRegisterFunction, EOSNotfyUnregisterFunction, ComponentHandlerFunction> ThisClass;`
- L327 _public function_ `FEOSEventRegistrationImpl( ComponentHandlerClass* HandlerClass, EOSHandle ClientHandle, int32_t ApiVersion, EOSNotfyRegisterFunction NotfyRegisterFunction, EOSNotfyUnregisterFunction NotfyUnregisterFunction, ComponentHandlerFunction HandlerFunction) : HandlerClass(HandlerClass) , ClientHandle(ClientHandle) , NotfyUnregisterFunction(NotfyUnregisterFunction) , HandlerFunction(HandlerFunction)`
- L350 _public function_ `virtual ~FEOSEventRegistrationImpl()`
- L356 _private prototype_ `FEOSEventRegistrationImpl() = delete;`
- L357 _private prototype_ `FEOSEventRegistrationImpl(const FEOSEventRegistrationImpl&) = delete;`
- L358 _private prototype_ `FEOSEventRegistrationImpl& operator=(const FEOSEventRegistrationImpl&) = delete;`
- L360 _private typedef_ `typedef typename TEOSNotifyRegisterTraits<EOSNotfyRegisterFunction>::NotificationIdType NotificationIdType;`
- L362 _private member_ `NotificationIdType NotificationId;`
- L363 _private member_ `ComponentHandlerClass* HandlerClass;`
- L364 _private member_ `EOSHandle ClientHandle;`
- L365 _private member_ `EOSNotfyUnregisterFunction NotfyUnregisterFunction;`
- L366 _private member_ `ComponentHandlerFunction HandlerFunction;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define EOS_CONNECTION_URL_PREFIX TEXT("EOS")` — Expect URLs to look like "EOS:PUID:SocketName:Channel"
- L20 _macro_ `#define EOS_URL_SEPARATOR TEXT(":")`
- L142 _namespace_ `namespace UE`
- L142 _namespace_ `namespace Online` (scope `UE`)
- L144 _namespace_ `namespace Private` (scope `UE::Online`)
- L221 _function_ `template<typename TEOSResult, typename TEOSHandle, typename TEOSParameters, typename TEOSFn> decltype(auto) EOS_Async(TEOSFn EOSFn, TEOSHandle EOSHandle, TEOSParameters Parameters, TPromise<const TEOSResult*>&& Promise)` (scope `UE::Online`) — Warning: This signature will crash if the async method returns immediately. The callback object is deleted inside the callback before EOS_Async returns the future back to the user.
- L232 _function_ `template<typename TEOSHandle, typename TEOSParameters, typename TEOSFn, typename TCallback> decltype(auto) EOS_Async(TEOSFn EOSFn, TEOSHandle EOSHandle, const TEOSParameters& Parameters, TCallback&& Callback)` (scope `UE::Online`) — This method requires a Callback (lambda / function pointer) which will be called by the EOS callback with the CallbackInfo.
- L234 _typedef_ `using CallbackDataType = typename Private::FEOSAsyncTraits<TEOSFn>::CallbackDataType;` (scope `UE::Online::EOS_Async`)
- L238 _function_ `` (scope `UE::Online::EOS_Async`)
- L254 _typedef_ `typedef TUniquePtr<FEOSEventRegistration> FEOSEventRegistrationPtr;` (scope `UE::Online`)
- L256 _typedef_ `using EOSEventRegistration UE_DEPRECATED(5.6, "EOSEventRegistration rename` (scope `UE::Online`)
- L257 _typedef_ `using EOSEventRegistrationPtr UE_DEPRECATED(5.6, "EOSEventRegistrationPtr rename` (scope `UE::Online`) — `UE_DEPRECATED(5.6, "EOSEventRegistration renamed to FEOSEventRegistration")`
- L278 _prototype_ `FEOSEventRegistrationPtr EOS_RegisterComponentEventHandler( ComponentHandlerClass* HandlerClass, EOSHandle ClientHandle, int32_t ApiVersion, EOSNotfyRegisterFunction NotfyRegisterFunction, EOSNotfyUnregisterFunction NotfyUnregisterFunction, ComponentHandlerFunction HandlerFunction);` (scope `UE::Online`)
- L286 _namespace_ `namespace Private` (scope `UE::Online`)
- L339 _typedef_ `using EventDataType = typename TEOSCallbackTraits<ComponentHandlerFunction>::EventDataType;` (scope `UE::Online::Private::FEOSEventRegistrationImpl::FEOSEventRegistrationImpl`)
- L344 _function_ `` (scope `UE::Online::Private::FEOSEventRegistrationImpl::FEOSEventRegistrationImpl`)
- L377 _function_ `FEOSEventRegistrationPtr EOS_RegisterComponentEventHandler( ComponentHandlerClass* HandlerClass, EOSHandle ClientHandle, int32_t ApiVersion, EOSNotfyRegisterFunction NotfyRegisterFunction, EOSNotfyUnregisterFunction NotfyUnregisterFunction, ComponentHandlerFunction HandlerFunction)` (scope `UE::Online`)

### `Plugins/Online/EOSShared/Source/EOSShared/Public/IEOSSDKManager.h` (Public)


#### struct `FEOSSDKPlatformConfig`  
`struct FEOSSDKPlatformConfig`  
_L16-40_
- L18 _public member_ `FString Name;`
- L19 _public member_ `FString ProductId;`
- L20 _public member_ `FString SandboxId;`
- L21 _public member_ `FString ClientId;`
- L22 _public member_ `FString ClientSecret;`
- L23 _public member_ `FString EncryptionKey;`
- L24 _public member_ `FString RelyingPartyURI;`
- L25 _public member_ `FString OverrideCountryCode;`
- L26 _public member_ `FString OverrideLocaleCode;`
- L27 _public member_ `FString DeploymentId;`
- L28 _public member_ `FString CacheDirectory;`
- L29 _public member_ `EOS_ERTCBackgroundMode RTCBackgroundMode = EOS_ERTCBackgroundMode::EOS_RTCBM_KeepRoomsAlive;`
- L30 _public member_ `bool bIsServer = false;`
- L31 _public member_ `bool bLoadingInEditor = false;`
- L32 _public member_ `bool bDisableOverlay = false;`
- L33 _public member_ `bool bDisableSocialOverlay = false;`
- L34 _public member_ `bool bWindowsEnableOverlayD3D9 = false;`
- L35 _public member_ `bool bWindowsEnableOverlayD3D10 = false;`
- L36 _public member_ `bool bWindowsEnableOverlayOpenGL = false;`
- L37 _public member_ `bool bEnableRTC = true;`
- L38 _public member_ `int32 TickBudgetInMilliseconds = 1;`
- L39 _public member_ `TArray<FString> OptionalConfig;`

#### class `IEOSFastTickLock`  
`class IEOSFastTickLock`  
_L46-50_
- desc: Allows temporary RAII style overriding of the config driven tick rate, for scenarios where you want the SDK To tick as fast as possible, i.e. overlay visible, or time critical operations
- L49 _public prototype_ `virtual ~IEOSFastTickLock() = default;`

#### class `IEOSPlatformHandle`  
`class IEOSPlatformHandle`  
_L52-79_
- L55 _public function_ `IEOSPlatformHandle(EOS_HPlatform InPlatformHandle) : PlatformHandle(InPlatformHandle)`
- L59 _public prototype_ `virtual ~IEOSPlatformHandle() = default;`
- L61 _public prototype_ `virtual void Tick() = 0;`
- L62 _public prototype_ `virtual TSharedRef<IEOSFastTickLock> GetFastTickLock() = 0;`
- L64 _public function_ `operator EOS_HPlatform() const`
- L66 _public prototype_ `virtual FString GetConfigName() const = 0;`
- L67 _public prototype_ `virtual FString GetOverrideCountryCode() const = 0;`
- L68 _public prototype_ `virtual FString GetOverrideLocaleCode() const = 0;`
- L70 _public prototype_ `virtual void LogInfo(int32 Indent = 0) const = 0;`
- L71 _public prototype_ `virtual void LogAuthInfo(const EOS_EpicAccountId LoggedInAccount, int32 Indent = 0) const = 0;`
- L72 _public prototype_ `virtual void LogUserInfo(const EOS_EpicAccountId LoggedInAccount, const EOS_EpicAccountId TargetAccount, int32 Indent = 0) const = 0;`
- L73 _public prototype_ `virtual void LogPresenceInfo(const EOS_EpicAccountId LoggedInAccount, const EOS_EpicAccountId TargetAccount, int32 Indent = 0) const = 0;`
- L74 _public prototype_ `virtual void LogFriendsInfo(const EOS_EpicAccountId LoggedInAccount, int32 Indent = 0) const = 0;`
- L75 _public prototype_ `virtual void LogConnectInfo(const EOS_ProductUserId LoggedInAccount, int32 Indent = 0) const = 0;`
- L78 _protected member_ `EOS_HPlatform PlatformHandle;`

#### class `IEOSSDKManager`  
`class IEOSSDKManager : public IModularFeature`  
_L97-166_
- inherits: `IModularFeature`
- L100 _public function_ `static IEOSSDKManager* Get()`
- L109 _public function_ `static FName GetModularFeatureName()`
- L115 _public prototype_ `virtual ~IEOSSDKManager() = default;`
- L117 _public prototype_ `virtual bool IsInitialized() const = 0;`
- L119 _public prototype_ `virtual const FEOSSDKPlatformConfig* GetPlatformConfig(const FString& PlatformConfigName, bool bLoadIfMissing = false) = 0;`
- L120 _public prototype_ `virtual bool AddPlatformConfig(const FEOSSDKPlatformConfig& PlatformConfig, bool bOverwriteExistingConfig = false) = 0;`
- L121 _public prototype_ `virtual const FString& GetDefaultPlatformConfigName() = 0;`
- L122 _public prototype_ `virtual void SetDefaultPlatformConfigName(const FString& PlatformConfigName) = 0;`
- L128 _public prototype_ `virtual IEOSPlatformHandlePtr CreatePlatform(const FString& PlatformConfigName, FName InstanceName = NAME_None) = 0;` — Create a platform handle for a platform config name. Config is loaded from .ini files if it was not added with AddPlatformConfig. If a platform handle already exists for the config name, this will return a shared pointer to that handle and not create a new one.
- L131 _public prototype_ `virtual IEOSPlatformHandlePtr CreatePlatform(EOS_Platform_Options& PlatformOptions) = 0;` — Create a platform handle using EOSSDK options directly.
- L134 _public prototype_ `virtual TArray<IEOSPlatformHandlePtr> GetActivePlatforms() = 0;` — Retrieves the array of platform handles for all active platforms
- L136 _public prototype_ `virtual FString GetSDKVersion() const = 0;`
- L137 _public prototype_ `virtual FString GetProductName() const = 0;`
- L138 _public prototype_ `virtual FString GetProductVersion() const = 0;`
- L139 _public prototype_ `virtual FString GetCacheDirBase() const = 0;`
- L140 _public prototype_ `virtual FString GetOverrideCountryCode(const EOS_HPlatform Platform) const = 0;`
- L141 _public prototype_ `virtual FString GetOverrideLocaleCode(const EOS_HPlatform Platform) const = 0;`
- L143 _public prototype_ `virtual void LogInfo(int32 Indent = 0) const = 0;`
- L144 _public prototype_ `virtual void LogPlatformInfo(const EOS_HPlatform Platform, int32 Indent = 0) const = 0;`
- L145 _public prototype_ `virtual void LogAuthInfo(const EOS_HPlatform Platform, const EOS_EpicAccountId LoggedInAccount, int32 Indent = 0) const = 0;`
- L146 _public prototype_ `virtual void LogUserInfo(const EOS_HPlatform Platform, const EOS_EpicAccountId LoggedInAccount, const EOS_EpicAccountId TargetAccount, int32 Indent = 0) const = 0;`
- L147 _public prototype_ `virtual void LogPresenceInfo(const EOS_HPlatform Platform, const EOS_EpicAccountId LoggedInAccount, const EOS_EpicAccountId TargetAccount, int32 Indent = 0) const = 0;`
- L148 _public prototype_ `virtual void LogFriendsInfo(const EOS_HPlatform Platform, const EOS_EpicAccountId LoggedInAccount, int32 Indent = 0) const = 0;`
- L149 _public prototype_ `virtual void LogConnectInfo(const EOS_HPlatform Platform, const EOS_ProductUserId LoggedInAccount, int32 Indent = 0) const = 0;`
- L152 _public prototype_ `virtual void AddCallbackObject(TUniquePtr<class FCallbackBase> CallbackObj) = 0;` — Assign ownership of a callback object, to be free'd after EOS_Shutdown
- L154 _public prototype_ `virtual TSharedRef<IEOSFastTickLock> GetFastTickLock() = 0;`
- L156 _public member_ `FEOSSDKManagerOnPreInitializeSDK OnPreInitializeSDK;`
- L157 _public member_ `FEOSSDKManagerOnPreInitializeSDK2 OnPreInitializeSDK2;`
- L158 _public member_ `FEOSSDKManagerOnPostInitializeSDK OnPostInitializeSDK;`
- L159 _public member_ `FEOSSDKManagerOnDefaultPlatformConfigNameChanged OnDefaultPlatformConfigNameChanged;`
- L160 _public member_ `FEOSSDKManagerOnPreCreateNamedPlatform OnPreCreateNamedPlatform;`
- L161 _public member_ `FEOSSDKManagerOnPreCreatePlatform OnPreCreatePlatform;`
- L162 _public member_ `FEOSSDKManagerOnPlatformCreated OnPlatformCreated;`
- L163 _public member_ `FEOSSDKManagerOnPreReleasePlatform OnPreReleasePlatform;`
- L164 _public member_ `FEOSSDKManagerOnRequestRuntimeLibraryName OnRequestRuntimeLibraryName;`
- L165 _public member_ `FEOSSDKManagerOnNetworkStatusChanged OnNetworkStatusChanged;`

#### Free symbols / members of external scopes

- L81 _typedef_ `using IEOSPlatformHandlePtr = TSharedPtr<IEOSPlatformHandle, ESPMode::ThreadSafe>;`
- L82 _typedef_ `using IEOSPlatformHandleWeakPtr = TWeakPtr<IEOSPlatformHandle, ESPMode::ThreadSafe>;`
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPreInitializeSDK, EOS_InitializeOptions& Options);` — This callback lets you modify the options struct
- L85 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPreInitializeSDK, EOS_InitializeOptions& Options);` — This callback lets you modify the options struct
- L87 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPreInitializeSDK2, EOS_InitializeOptions*& InOutOptions);` — This callback lets you modify or replace the options struct
- L87 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPreInitializeSDK2, EOS_InitializeOptions*& InOutOptions);` — This callback lets you modify or replace the options struct
- L88 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPostInitializeSDK, EOS_EResult Result);`
- L88 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPostInitializeSDK, EOS_EResult Result);`
- L89 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FEOSSDKManagerOnDefaultPlatformConfigNameChanged, const FString& NewName, const FString& OldName);`
- L89 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FEOSSDKManagerOnDefaultPlatformConfigNameChanged, const FString& NewName, const FString& OldName);`
- L90 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FEOSSDKManagerOnPreCreateNamedPlatform, const FEOSSDKPlatformConfig& Config, EOS_Platform_Options& Options);`
- L90 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FEOSSDKManagerOnPreCreateNamedPlatform, const FEOSSDKPlatformConfig& Config, EOS_Platform_Options& Options);`
- L91 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPreCreatePlatform, EOS_Platform_Options& Options);`
- L91 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPreCreatePlatform, EOS_Platform_Options& Options);`
- L92 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPlatformCreated, const IEOSPlatformHandlePtr& PlatformHandle);`
- L92 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPlatformCreated, const IEOSPlatformHandlePtr& PlatformHandle);`
- L93 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPreReleasePlatform, const EOS_HPlatform& PlatformHandle);`
- L93 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FEOSSDKManagerOnPreReleasePlatform, const EOS_HPlatform& PlatformHandle);`
- L94 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FEOSSDKManagerOnNetworkStatusChanged, const EOS_ENetworkStatus OldNetworkStatus, const EOS_ENetworkStatus NewNetworkStatus);`
- L94 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FEOSSDKManagerOnNetworkStatusChanged, const EOS_ENetworkStatus OldNetworkStatus, const EOS_ENetworkStatus NewNetworkStatus);`
- L95 _delegate_ `DECLARE_DELEGATE_RetVal(FString, FEOSSDKManagerOnRequestRuntimeLibraryName);`
- L95 _prototype_ `DECLARE_DELEGATE_RetVal(FString, FEOSSDKManagerOnRequestRuntimeLibraryName);`
