# Plugins / PlayTimeLimit

- module root: `Plugins/Online/OnlineFramework/Source/PlayTimeLimit`
- headers: 4; symbols: 78
- symbol kinds: class=4, delegate=2, function=12, macro=2, member=20, prototype=34, struct=1, typedef=3
- PrivateDependencyModuleNames: OnlineSubsystem
- PublicDependencyModuleNames: Core, CoreOnline, CoreUObject

### `Plugins/Online/OnlineFramework/Source/PlayTimeLimit/Public/PlayTimeLimitImpl.h` (Public)


#### struct `FOnlinePlayLimitConfigEntry`  
`struct FOnlinePlayLimitConfigEntry`  
_L14-29_
- desc: Configuration
- L17 _public function_ `FOnlinePlayLimitConfigEntry(int32 InTimeStartMinutes, int32 InNotificationRateMinutes, float InRewardRate) : TimeStartMinutes(InTimeStartMinutes) , NotificationRateMinutes(InNotificationRateMinutes) , RewardRate(InRewardRate)` — Constructor
- L24 _public member_ `int32 TimeStartMinutes;` — Number of minutes the user must play before this is effective
- L26 _public member_ `int32 NotificationRateMinutes;` — Number of minutes between notifications to the user about their play time
- L28 _public member_ `float RewardRate;` — Reward rate at this limit

#### class `FPlayTimeLimitImpl`  
`class FPlayTimeLimitImpl : public IOnlinePlayTimeLimit`  
_L34-150_
- inherits: `IOnlinePlayTimeLimit`
- desc: Implementation of IOnlinePlayTimeLimit
- L41 _public prototype_ `FPlayTimeLimitImpl();` — Default constructor
- L43 _public prototype_ `virtual ~FPlayTimeLimitImpl();` — Destructor
- L49 _public prototype_ `static FPlayTimeLimitImpl& Get();` — Get the singleton @return Singleton instance
- L54 _public prototype_ `void Initialize();` — Initialize
- L59 _public prototype_ `void Shutdown();` — Shutdown
- L64 _public prototype_ `bool Tick(float Delta);` — Tick - update users and execute warn time delegates
- L66 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FPlayTimeLimitUserRawPtr, OnRequestCreateUserDelegate, const FUniqueNetId&);`
- L71 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGameExitRequested);` — Delegate called when a game exit is requested
- L72 _public typedef_ `typedef FOnGameExitRequested::FDelegate FOnGameExitRequestedDelegate;`
- L79 _public prototype_ `void RegisterUser(const FUniqueNetId& NewUser);` — Register a user to monitor their play time @see UnregisterUser @param NewUser the user to register
- L86 _public prototype_ `void UnregisterUser(const FUniqueNetId& UserId);` — Unregister a user @see RegisterUser @param UserId the user id
- L92 _public prototype_ `void MockUser(const FUniqueNetId& UserId, const bool bHasTimeLimit, const double CurrentPlayTimeMinutes);` — Override a user's play time For testing the system without needing to potentially wait hours - waiting to accumulate time and waiting for the time to reset
- L97 _public prototype_ `void NotifyNow();` — Cheat function to trigger the notification to players of their play time immediately
- L100 _public prototype_ `virtual bool HasTimeLimit(const FUniqueNetId& UserId) override;`
- L101 _public prototype_ `virtual int32 GetPlayTimeMinutes(const FUniqueNetId& UserId) override;`
- L102 _public prototype_ `virtual float GetRewardRate(const FUniqueNetId& UserId) override;`
- L103 _public prototype_ `virtual FWarnUserPlayTime& GetWarnUserPlayTimeDelegate() override;`
- L104 _public prototype_ `void GameExitByRequest();`
- L112 _public prototype_ `const FOnlinePlayLimitConfigEntry* GetConfigEntry(const int32 PlayTimeMinutes) const;` — Get the config entry that corresponds to the number of minutes played @param PlayTimeMinutes the number of minutes played to get the entry for @return the entry corresponding to the number of minutes played
- L117 _public prototype_ `void DumpState();` — Dump state to log
- L119 _public member_ `OnRequestCreateUserDelegate OnRequestCreateUser;`
- L122 _public member_ `FOnGameExitRequested OnGameExitRequestedDelegate;` — Delegate used to request a game exit
- L129 _protected prototype_ `void UpdateNextNotificationTime(FPlayTimeLimitUser& User, const int32 PlayTimeMinutes) const;` — Update the next notification time for a user based on their current play time @param User the user to update
- L132 _protected member_ `FWarnUserPlayTime WarnUserPlayTimeDelegate;` — Delegate used to display a warning to the user about their play time
- L135 _protected member_ `TArray<FPlayTimeLimitUserPtr> Users;` — List of users we are monitoring
- L138 _protected member_ `double LastTickLogicTime = 0.0;` — Last time we performed tick logic
- L141 _protected member_ `TArray<FOnlinePlayLimitConfigEntry> ConfigRates;` — Configuration to control notification rate at different levels of play time
- L144 _protected member_ `FTSTicker::FDelegateHandle TickHandle;` — Delegate for callbacks to Tick
- L148 _private prototype_ `FPlayTimeLimitImpl(const FPlayTimeLimitImpl& Other) = delete;` — Not copyable
- L149 _private prototype_ `FPlayTimeLimitImpl& operator=(FPlayTimeLimitImpl& Other) = delete;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PLAYTIMELIMIT_API`
- L66 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FPlayTimeLimitUserRawPtr, OnRequestCreateUserDelegate, const FUniqueNetId&);`
- L71 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGameExitRequested);` — Delegate called when a game exit is requested

### `Plugins/Online/OnlineFramework/Source/PlayTimeLimit/Public/PlayTimeLimitModule.h` (Public)


#### class `FPlayTimeLimitModule`  
`class FPlayTimeLimitModule : public IModuleInterface, public FSelfRegisteringExec`  
_L12-60_
- inherits: `IModuleInterface,FSelfRegisteringExec`
- desc: Module for reducing rewards based on play time
- L23 _public function_ `static inline FPlayTimeLimitModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L40 _protected prototype_ `virtual bool Exec_Runtime(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FSelfRegisteringExec
- L50 _private prototype_ `virtual void StartupModule() override;` — Called when party module is loaded Initialize platform specific parts of voice handling
- L56 _private prototype_ `virtual void ShutdownModule() override;` — Called when party module is unloaded Shutdown platform specific parts of voice handling
- L59 _private member_ `bool bPlayTimeLimitEnabled = false;` — Is this feature enabled?

#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlayTimeLimit, Log, All);`

### `Plugins/Online/OnlineFramework/Source/PlayTimeLimit/Public/PlayTimeLimitUser.h` (Public)


#### class `FPlayTimeLimitUser`  
`class FPlayTimeLimitUser : public TSharedFromThis<FPlayTimeLimitUser, ESPMode::ThreadSafe>`  
_L10-104_
- inherits: `TSharedFromThis<FPlayTimeLimitUser,ESPMode::ThreadSafe>`
- desc: Information about a user we are observing the play time and instituting limits for
- L15 _public function_ `explicit FPlayTimeLimitUser(const FUniqueNetIdRef& InUserId) : UserId(InUserId) , NextNotificationTime(0) , LastKnownRewardRate(0.0f)` — Constructor
- L21 _public function_ `virtual void Init()`
- L27 _public prototype_ `virtual ~FPlayTimeLimitUser() = default;` — Destructor
- L33 _public function_ `FUniqueNetIdRef GetUserId() const` — Get the user's unique id @return the user's unique id
- L38 _public function_ `virtual void Tick()` — Tick
- L44 _public prototype_ `virtual bool HasTimeLimit() const = 0;` — Check if the user has a play time limit @return if this user has a play time limit
- L50 _public prototype_ `virtual int32 GetPlayTimeMinutes() const = 0;` — Get the number of minutes this user has played @return number of minutes this user has played
- L56 _public prototype_ `virtual float GetRewardRate() const = 0;` — Get the current reward rate @return the current reward rate
- L63 _public function_ `TOptional<double> GetNextNotificationTime() const` — Get the next time we are scheduled to send the user a notification This is for the periodic notification; if the reward rate changes we will immediately display a notification @return the time (compared to FPlatformTime::Seconds()) for the next notification, or empty if this user should not receive periodic notifications
- L70 _public function_ `virtual void SetNextNotificationTime(const TOptional<double>& InNextNotificationTime)` — Set the next time to send the user a notification @see GetNextNotificationTime @param InNextNotificationTime the next notification time, or empty if this user should not receive periodic notifications
- L76 _public function_ `float GetLastKnownRewardRate() const` — Get the last known reward rate @return the last known reward rate
- L82 _public function_ `void SetLastKnownRewardRate(float InLastKnownRewardRate)` — Set the last known reward rate @param InLastKnownRewardRate the last known reward rate
- L87 _public function_ `virtual void ClearDialogOverrideText()` — Clear override dialog text
- L93 _public member_ `FString OverrideDialogTitle;`
- L94 _public member_ `FString OverrideDialogText;`
- L95 _public member_ `FString OverrideButtonText;`
- L99 _protected member_ `FUniqueNetIdRef UserId;` — The user id
- L101 _protected member_ `TOptional<double> NextNotificationTime;` — Time for the next notification (or empty for no notification)
- L103 _protected member_ `float LastKnownRewardRate;` — Last known reward rate so we can alert on changes

#### Free symbols / members of external scopes

- L106 _typedef_ `typedef FPlayTimeLimitUser* FPlayTimeLimitUserRawPtr;`
- L107 _typedef_ `typedef TSharedPtr<FPlayTimeLimitUser, ESPMode::ThreadSafe> FPlayTimeLimitUserPtr;`

### `Plugins/Online/OnlineFramework/Source/PlayTimeLimit/Public/PlayTimeLimitUserMock.h` (Public)


#### class `FPlayTimeLimitUserMock`  
`class FPlayTimeLimitUserMock : public FPlayTimeLimitUser`  
_L15-34_
- inherits: `FPlayTimeLimitUser`
- desc: Mock implementation of FPlayTimeLimitUser
- L19 _public prototype_ `FPlayTimeLimitUserMock(const FUniqueNetIdRef& InUserId, const bool bInHasTimeLimit, const double InPlayTimeMinutes);`
- L22 _public prototype_ `virtual bool HasTimeLimit() const override;`
- L23 _public prototype_ `virtual int32 GetPlayTimeMinutes() const override;`
- L24 _public prototype_ `virtual float GetRewardRate() const override;`
- L29 _protected member_ `const bool bHasTimeLimit;` — Do the time limits apply to the user?
- L31 _protected member_ `const double PlayTimeMinutesStart;` — Override time played. Effective time played is PlayTimeMinutesStart + (Now - TimeOverrideSet)
- L33 _protected member_ `const double TimeOverrideSet;` — The time this override was set. Effective time played is PlayTimeMinutesStart + (Now - TimeOverrideSet)

#### Free symbols / members of external scopes

- L8 _macro_ `#define ALLOW_PLAY_LIMIT_MOCK (!(UE_BUILD_SHIPPING))`
