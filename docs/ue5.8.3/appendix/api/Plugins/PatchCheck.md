# Plugins / PatchCheck

- module root: `Plugins/Online/OnlineFramework/Source/PatchCheck`
- headers: 2; symbols: 69
- symbol kinds: class=4, delegate=2, enum=1, enumerator=5, function=6, macro=1, member=14, prototype=35, struct=1
- PrivateDependencyModuleNames: Core, OnlineSubsystem
- PublicIncludePathModuleNames: OnlineSubsystem

### `Plugins/Online/OnlineFramework/Source/PatchCheck/Public/PatchCheck.h` (Public)


#### enum `EPatchCheckResult`  
`enum class EPatchCheckResult : uint8`  
_L16-27_
- desc: Possible outcomes at the end of just the patch check
- L19 _public enumerator_ `NoPatchRequired` — No patch required
- L21 _public enumerator_ `PatchRequired` — Patch required to continue
- L23 _public enumerator_ `NoLoggedInUser` — Logged in user required for a patch check
- L25 _public enumerator_ `PatchCheckFailure` — Patch check failed
- L26 _public enumerator_ `Count`

#### class `IPatchCheckStatsCollector`  
`class IPatchCheckStatsCollector`  
_L30-46_
- L33 _public prototype_ `virtual ~IPatchCheckStatsCollector() = default;`
- L36 _public prototype_ `virtual void OnPatchCheckStarted() = 0;` — Overall process/
- L37 _public prototype_ `virtual void OnPatchCheckComplete(EPatchCheckResult Result) = 0;`
- L40 _public prototype_ `virtual void OnPatchCheckStep_DetectEnvironmentStarted() = 0;` — Individual stages.
- L41 _public prototype_ `virtual void OnPatchCheckStep_DetectEnvironmentComplete(bool bSuccess, const FString& Error) = 0;`
- L42 _public prototype_ `virtual void OnPatchCheckStep_CheckPlatformPatchStarted() = 0;`
- L43 _public prototype_ `virtual void OnPatchCheckStep_CheckPlatformPatchComplete(bool bSuccess, const FString& Error) = 0;`
- L44 _public prototype_ `virtual void OnPatchCheckStep_CheckOnlineServicePatchStarted() = 0;`
- L45 _public prototype_ `virtual void OnPatchCheckStep_CheckOnlineServicePatchComplete(bool bSuccess, const FString& Error) = 0;`

#### class `FPatchCheck`  
`class FPatchCheck`  
_L53-141_
- L56 _public prototype_ `static FPatchCheck& Get();`
- L58 _public prototype_ `virtual ~FPatchCheck();`
- L61 _protected prototype_ `FPatchCheck();`
- L64 _private prototype_ `FPatchCheck(const FPatchCheck& Other) = delete;`
- L66 _private prototype_ `FPatchCheck& operator=(const FPatchCheck& Other) = delete;`
- L69 _public prototype_ `void StartPatchCheck();`
- L71 _public prototype_ `void AddEnvironmentWantsPatchCheckBackCompatDelegate(FName Tag, FEnvironmentWantsPatchCheck Delegate);`
- L72 _public prototype_ `void RemoveEnvironmentWantsPatchCheckBackCompatDelegate(FName Tag);`
- L74 _public function_ `FOnPatchCheckComplete& GetOnComplete()`
- L75 _public function_ `TOptional<EPatchCheckResult> GetLastPatchCheckResult() const`
- L77 _public prototype_ `void RegisterStatsCollector(const TSharedPtr<IPatchCheckStatsCollector>& InStats);`
- L80 _protected prototype_ `void RefreshConfig();`
- L81 _protected prototype_ `virtual void StartPlatformOSSPatchCheck();`
- L82 _protected prototype_ `virtual void StartOSSPatchCheck();`
- L83 _protected prototype_ `void HandleOSSPatchCheck();`
- L84 _protected prototype_ `virtual bool EnvironmentWantsPatchCheck() const;`
- L85 _protected prototype_ `virtual bool EditorWantsPatchCheck() const;`
- L86 _protected prototype_ `bool SkipPatchCheck() const;`
- L87 _protected prototype_ `void OnCheckForPatchComplete(const FUniqueNetId& UniqueId, EUserPrivileges::Type Privilege, uint32 PrivilegeResult, bool bConsoleCheck);`
- L88 _protected prototype_ `virtual void PatchCheckComplete(EPatchCheckResult PatchResult);`
- L95 _protected prototype_ `bool DetectPlatformEnvironment();` — Platform specific implementation of platform environment detection @return true if the detection began.  false if the detection did not begin and we should continue the checks.
- L100 _protected prototype_ `virtual void DetectPlatformEnvironment_OnLoginConsoleComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);` — Platform specific callback for logging in on console which is needed for the platform environment detection
- L105 _protected prototype_ `void OnDetectPlatformEnvironmentComplete(const FOnlineError& Result);` — Callback when detecting platform environment completes
- L114 _protected member_ `TWeakPtr<IPatchCheckStatsCollector> Stats;`
- L115 _protected member_ `TOptional<FPreviousSuccessInfo> PreviousPlatformSuccess;`
- L116 _protected member_ `TOptional<FPreviousSuccessInfo> PreviousOnlineServiceSuccess;`
- L117 _protected member_ `TOptional<EPatchCheckResult> LastPatchCheckResult;`
- L119 _protected member_ `FOnPatchCheckComplete OnComplete;`
- L122 _protected member_ `TMap<FName, FEnvironmentWantsPatchCheck> BackCompatEnvironmentWantsPatchCheckDelegates;` — For backwards compatibility with UUpdateManager
- L125 _protected member_ `bool bIsCheckInProgress = false;` — Track whether we can start a new check
- L128 _protected member_ `bool bCheckPlatformOSSForUpdate = true;` — Check the platform OSS for an update
- L130 _protected member_ `bool bCheckOSSForUpdate = true;` — Check the default OSS for an update
- L133 _protected member_ `FDelegateHandle OnLoginConsoleCompleteHandle;`
- L137 _protected member_ `bool bPlatformEnvironmentDetected = !PATCH_CHECK_PLATFORM_ENVIRONMENT_DETECTION;` — true if we've already detected the backend environment
- L138 _protected member_ `bool bPlatformEnvironmentDetectionEnabled = true;`

#### struct `FPatchCheck::FPreviousSuccessInfo`  
`struct FPreviousSuccessInfo`  
_L109-112_
- L111 _public member_ `double ResultTime = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PATCHCHECK_API`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPatchCheck, Log, All);`
- L28 _prototype_ `const TCHAR* LexToString(EPatchCheckResult Value);`
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPatchCheckComplete, EPatchCheckResult );`
- L48 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPatchCheckComplete, EPatchCheckResult );`
- L51 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FEnvironmentWantsPatchCheck);` — For backwards compatibility only!
- L51 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FEnvironmentWantsPatchCheck);` — For backwards compatibility only!

### `Plugins/Online/OnlineFramework/Source/PatchCheck/Public/PatchCheckModule.h` (Public)


#### class `IPatchCheckModule`  
`class IPatchCheckModule : public IModuleInterface`  
_L11-40_
- inherits: `IModuleInterface`
- L14 _public function_ `virtual void StartupModule() override`
- L26 _public function_ `virtual void PreUnloadCallback() override`
- L31 _public prototype_ `virtual FPatchCheck* MakePatchCheck() = 0;`
- L33 _public function_ `FPatchCheck* GetPatchCheck()`
- L39 _protected member_ `TUniquePtr<FPatchCheck> PatchCheck;`

#### class `TPatchCheckModule`  
`template<class PatchCheckClass> class TPatchCheckModule : public IPatchCheckModule`  
_L43-54_
- inherits: `IPatchCheckModule`
- L46 _public function_ `virtual FPatchCheck* MakePatchCheck() override`
