# Plugins / OnlineSubsystemEOS

- module root: `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS`
- headers: 30; symbols: 1075
- symbol kinds: class=44, delegate=7, enum=2, enumerator=11, function=141, macro=23, member=247, namespace=2, prototype=499, struct=15, typedef=82, variable=2
- PrivateDependencyModuleNames: Core, CoreOnline, CoreUObject, EOSVoiceChat, Engine, Json, NetCore, OnlineBase, OnlineSubsystem, OnlineSubsystemUtils, SocketSubsystemEOS, Sockets, VoiceChat
- PublicDependencyModuleNames: EOSSDK, EOSShared

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/Android/AndroidEOSHelpers.h` (Private)


#### class `FAndroidEOSHelpers`  
`class FAndroidEOSHelpers : public FEOSHelpers`  
_L9-13_
- inherits: `FEOSHelpers`
- L12 _public prototype_ `virtual void PlatformTriggerLoginUI(FOnlineSubsystemEOS* EOSSubsystem, const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate) override;`

#### Free symbols / members of external scopes

- L15 _typedef_ `using FPlatformEOSHelpers = FAndroidEOSHelpers;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/EOSHelpers.h` (Private)


#### class `FEOSHelpers`  
`class FEOSHelpers`  
_L18-36_
- L21 _public prototype_ `virtual ~FEOSHelpers() = default;`
- L23 _public prototype_ `virtual void GetSystemAuthCredentialsOptions(void*& OutCredentialsOptions);`
- L24 _public prototype_ `virtual void PlatformTriggerLoginUI(FOnlineSubsystemEOS* EOSSubsystem, const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate);`
- L25 _public prototype_ `virtual IEOSPlatformHandlePtr CreatePlatform(EOS_Platform_Options& PlatformOptions);`
- L26 _public prototype_ `virtual void AddProductUserIdMapping(IEOSPlatformHandlePtr PlatformHandlePtr, const EOS_ProductUserId& ProductUserId, int32 LocalUserNum);`
- L27 _public prototype_ `virtual void AddExternalAccountMapping(IEOSPlatformHandlePtr PlatformHandlePtr, const EOS_EpicAccountId& EpicAccountId, int32 LocalUserNum);`
- L31 _protected prototype_ `void ShowAccountPortalUI(FOnlineSubsystemEOS* InEOSSubsystem, const int ControllerIndex, const FOnLoginUIClosedDelegate& Delegate);` — Shared LoginUI logic that can be used by platforms that support LoginUI
- L35 _private prototype_ `void OnAccountPortalLoginComplete(int ControllerIndex, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& ErrorString, FOnlineSubsystemEOS* InEOSSubsystem, const FOnLoginUIClosedDelegate LoginUIClosedDelegate, FDelegateHandle* LoginDelegateHandle) const;` — Completion handler for ShowAccountPortalUI

#### Free symbols / members of external scopes

- L16 _typedef_ `using IEOSPlatformHandlePtr = TSharedPtr<class IEOSPlatformHandle, ESPMode::ThreadSafe>;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/IOS/IOSEOSHelpers.h` (Private)


#### class `FIOSEOSHelpers`  
`class FIOSEOSHelpers : public FEOSHelpers`  
_L14-24_
- inherits: `FEOSHelpers`
- L17 _public prototype_ `virtual ~FIOSEOSHelpers();`
- L19 _public prototype_ `virtual void GetSystemAuthCredentialsOptions(void*& OutCredentialsOptions) override;`
- L20 _public prototype_ `virtual void PlatformTriggerLoginUI(FOnlineSubsystemEOS* EOSSubsystem, const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate) override;`
- L23 _private member_ `EOS_IOS_Auth_CredentialsOptions CredentialsOptions;`

#### Free symbols / members of external scopes

- L26 _typedef_ `using FPlatformEOSHelpers = FIOSEOSHelpers;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/Linux/LinuxEOSHelpers.h` (Private)


#### Free symbols / members of external scopes

- L9 _typedef_ `using FPlatformEOSHelpers = FEOSHelpers;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/Mac/MacEOSHelpers.h` (Private)


#### Free symbols / members of external scopes

- L9 _typedef_ `using FPlatformEOSHelpers = FEOSHelpers;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/NboSerializerEOS.h` (Private)


#### class `FNboSerializeToBufferEOS`  
`class FNboSerializeToBufferEOS : public FNboSerializeToBufferOSS`  
_L14-49_
- inherits: `FNboSerializeToBufferOSS`
- desc: Serializes data in network byte order form into a buffer
- L18 _public function_ `FNboSerializeToBufferEOS() : FNboSerializeToBufferOSS(512)` — Default constructor zeros num bytes
- L24 _public function_ `FNboSerializeToBufferEOS(uint32 Size) : FNboSerializeToBufferOSS(Size)` — Constructor specifying the size to use

#### class `FNboSerializeFromBufferEOS`  
`class FNboSerializeFromBufferEOS : public FNboSerializeFromBufferOSS`  
_L54-90_
- inherits: `FNboSerializeFromBufferOSS`
- desc: Class used to write data into packets for sending via system link
- L60 _public function_ `FNboSerializeFromBufferEOS(uint8* Packet,int32 Length) : FNboSerializeFromBufferOSS(Packet,Length)` — Initializes the buffer, size, and zeros the read offset

#### Free symbols / members of external scopes

- L32 _function_ `friend inline FNboSerializeToBufferEOS& operator<<(FNboSerializeToBufferEOS& Ar, const FOnlineSessionInfoEOS& SessionInfo)` — Adds EOS session info to the buffer
- L44 _function_ `friend inline FNboSerializeToBufferEOS& operator<<(FNboSerializeToBufferEOS& Ar, const FUniqueNetIdString& UniqueId)` — Adds string Unique Id to the buffer
- L68 _function_ `friend inline FNboSerializeFromBufferEOS& operator>>(FNboSerializeFromBufferEOS& Ar, FOnlineSessionInfoEOS& SessionInfo)` — Reads EOS session info from the buffer
- L85 _function_ `friend inline FNboSerializeFromBufferEOS& operator>>(FNboSerializeFromBufferEOS& Ar, FUniqueNetIdString& UniqueId)` — Reads string Unique Id from the buffer

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineAchievementsEOS.h` (Private)


#### class `FOnlineAchievementsEOS`  
`class FOnlineAchievementsEOS : public IOnlineAchievements , public TSharedFromThis<FOnlineAchievementsEOS, ESPMode::ThreadSafe>`  
_L18-52_
- inherits: `IOnlineAchievements,TSharedFromThis<FOnlineAchievementsEOS,ESPMode::ThreadSafe>`
- desc: Interface for interacting with EOS achievements
- L23 _public prototype_ `FOnlineAchievementsEOS() = delete;`
- L24 _public prototype_ `virtual ~FOnlineAchievementsEOS() = default;`
- L26 _public prototype_ `FOnlineAchievementsEOS(FOnlineSubsystemEOS* InSubsystem);`
- L29 _public prototype_ `virtual void WriteAchievements(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate = FOnAchievementsWrittenDelegate()) override;` — IOnlineAchievements Interface
- L30 _public prototype_ `virtual void QueryAchievements(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate()) override;`
- L31 _public prototype_ `virtual void QueryAchievementDescriptions(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate()) override;`
- L32 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievement(const FUniqueNetId& PlayerId, const FString& AchievementId, FOnlineAchievement& OutAchievement) override;`
- L33 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievements(const FUniqueNetId& PlayerId, TArray<FOnlineAchievement>& OutAchievements) override;`
- L34 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc& OutAchievementDesc) override;`
- L36 _public prototype_ `virtual bool ResetAchievements(const FUniqueNetId& PlayerId) override;`
- L41 _private prototype_ `void UnlockAchievements(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate);`
- L45 _private member_ `FOnlineSubsystemEOS* EOSSubsystem;` — Reference to the main EOS subsystem
- L47 _private member_ `TUniqueNetIdMap<TArray<FOnlineAchievement>> CachedAchievementsMap;` — Holds the cached info from the last time this was called
- L49 _private member_ `TArray<FOnlineAchievementDesc> CachedAchievementDefinitions;` — Holds the cached info from the last time this was called
- L51 _private member_ `TMap<FString, FOnlineAchievementDesc*> CachedAchievementDefinitionsMap;` — Hack to work around the fact the description doesn't include the ID

#### Free symbols / members of external scopes

- L54 _typedef_ `typedef TSharedPtr<FOnlineAchievementsEOS, ESPMode::ThreadSafe> FOnlineAchievementsEOSPtr;`
- L55 _typedef_ `typedef TWeakPtr<FOnlineAchievementsEOS, ESPMode::ThreadSafe> FOnlineAchievementsEOSWeakPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineEntitlementsEOS.h` (Private)


#### class `FOnlineEntitlementsEOS`  
`class FOnlineEntitlementsEOS : public IOnlineEntitlements, public TSharedFromThis<FOnlineEntitlementsEOS, ESPMode::ThreadSafe>`  
_L18-43_
- inherits: `IOnlineEntitlements,TSharedFromThis<FOnlineEntitlementsEOS,ESPMode::ThreadSafe>`
- desc: Query entitlements
- L23 _public prototype_ `virtual ~FOnlineEntitlementsEOS() = default;`
- L25 _public prototype_ `virtual bool QueryEntitlements(const FUniqueNetId& UserId, const FString& Namespace, const FPagedQuery& Page = FPagedQuery()) override;`
- L26 _public prototype_ `virtual TSharedPtr<FOnlineEntitlement> GetEntitlement(const FUniqueNetId& UserId, const FUniqueEntitlementId& EntitlementId) override;`
- L27 _public prototype_ `virtual TSharedPtr<FOnlineEntitlement> GetItemEntitlement(const FUniqueNetId& UserId, const FString& ItemId) override;`
- L28 _public prototype_ `virtual void GetAllEntitlements(const FUniqueNetId& UserId, const FString& Namespace, TArray<TSharedRef<FOnlineEntitlement>>& OutUserEntitlements) override;`
- L30 _public prototype_ `FOnlineEntitlementsEOS(FOnlineSubsystemEOS* InSubsystem);`
- L32 _public prototype_ `bool HandleEntitlementsExec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L36 _private prototype_ `FOnlineEntitlementsEOS() = delete;` — Default constructor disabled
- L39 _private member_ `TMap<FUniqueNetIdRef, TArray<TSharedRef<FOnlineEntitlement>>> CachedEntitlementsMap;` — List of entitlements for the player
- L42 _private member_ `FOnlineSubsystemEOS* EOSSubsystem;` — Reference to the main EOS subsystem

#### Free symbols / members of external scopes

- L45 _typedef_ `typedef TSharedPtr<FOnlineEntitlementsEOS, ESPMode::ThreadSafe> FOnlineEntitlementsEOSPtr;`
- L46 _typedef_ `typedef TWeakPtr<FOnlineEntitlementsEOS, ESPMode::ThreadSafe> FOnlineEntitlementsEOSWeakPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineLeaderboardsEOS.h` (Private)


#### class `FOnlineLeaderboardsEOS`  
`class FOnlineLeaderboardsEOS : public IOnlineLeaderboards , public TSharedFromThis<FOnlineLeaderboardsEOS, ESPMode::ThreadSafe>`  
_L18-48_
- inherits: `IOnlineLeaderboards,TSharedFromThis<FOnlineLeaderboardsEOS,ESPMode::ThreadSafe>`
- desc: Interface for interacting with EOS stats
- L23 _public prototype_ `FOnlineLeaderboardsEOS() = delete;`
- L24 _public prototype_ `virtual ~FOnlineLeaderboardsEOS() = default;`
- L27 _public prototype_ `virtual bool ReadLeaderboards(const TArray< FUniqueNetIdRef >& Players, FOnlineLeaderboardReadRef& ReadObject) override;` — IOnlineLeaderboards Interface
- L28 _public prototype_ `virtual bool ReadLeaderboardsForFriends(int32 LocalUserNum, FOnlineLeaderboardReadRef& ReadObject) override;`
- L29 _public prototype_ `virtual bool ReadLeaderboardsAroundRank(int32 Rank, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L30 _public prototype_ `virtual bool ReadLeaderboardsAroundUser(FUniqueNetIdRef Player, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L31 _public prototype_ `virtual void FreeStats(FOnlineLeaderboardRead& ReadObject) override;`
- L32 _public prototype_ `virtual bool WriteLeaderboards(const FName& SessionName, const FUniqueNetId& Player, FOnlineLeaderboardWrite& WriteObject) override;`
- L33 _public prototype_ `virtual bool FlushLeaderboards(const FName& SessionName) override;`
- L34 _public prototype_ `virtual bool WriteOnlinePlayerRatings(const FName& SessionName, int32 LeaderboardId, const TArray<FOnlinePlayerScore>& PlayerScores) override;`
- L37 _public function_ `FOnlineLeaderboardsEOS(FOnlineSubsystemEOS* InSubsystem) : EOSSubsystem(InSubsystem)`
- L42 _public prototype_ `bool HandleLeaderboardsExec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L47 _private member_ `FOnlineSubsystemEOS* EOSSubsystem;` — Reference to the main EOS subsystem

#### Free symbols / members of external scopes

- L13 _macro_ `#define EOS_MAX_NUM_RANKINGS 1000`
- L50 _typedef_ `typedef TSharedPtr<FOnlineLeaderboardsEOS, ESPMode::ThreadSafe> FOnlineLeaderboardsEOSPtr;`
- L51 _typedef_ `typedef TWeakPtr<FOnlineLeaderboardsEOS, ESPMode::ThreadSafe> FOnlineLeaderboardsEOSWeakPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlinePlayerReportEOS.h` (Private)


#### class `FOnlinePlayerReportEOS`  
`class FOnlinePlayerReportEOS : public IOnlinePlayerReportEOS , public TSharedFromThis<FOnlinePlayerReportEOS, ESPMode::ThreadSafe>`  
_L23-38_
- inherits: `IOnlinePlayerReportEOS,TSharedFromThis<FOnlinePlayerReportEOS,ESPMode::ThreadSafe>`
- desc: Interface for interacting with EOS player reports
- L28 _public prototype_ `FOnlinePlayerReportEOS() = delete;`
- L29 _public prototype_ `virtual ~FOnlinePlayerReportEOS() = default;`
- L31 _public prototype_ `FOnlinePlayerReportEOS(FOnlineSubsystemEOS* InSubsystem);`
- L33 _public prototype_ `virtual void SendPlayerReport(const FUniqueNetId& LocalUserId, const FUniqueNetId& TargetUserId, FSendPlayerReportSettings&& SendPlayerReportSettings, FOnSendPlayerReportComplete&& Delegate) override;`
- L37 _private member_ `FOnlineSubsystemEOS* EOSSubsystem;` — Reference to the main EOS subsystem

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlinePlayerReportEOS, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlinePlayerReportEOS, Log, All);`
- L11 _macro_ `#define UE_LOG_ONLINE_PLAYERREPORTEOS(Verbosity, Format, ...) \`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlinePlayerSanctionEOS.h` (Private)


#### class `FOnlinePlayerSanctionEOS`  
`class FOnlinePlayerSanctionEOS : public IOnlinePlayerSanctionEOS , public TSharedFromThis<FOnlinePlayerSanctionEOS, ESPMode::ThreadSafe>`  
_L23-46_
- inherits: `IOnlinePlayerSanctionEOS,TSharedFromThis<FOnlinePlayerSanctionEOS,ESPMode::ThreadSafe>`
- desc: Interface for interacting with EOS sanctions
- L28 _public prototype_ `FOnlinePlayerSanctionEOS() = delete;`
- L29 _public prototype_ `virtual ~FOnlinePlayerSanctionEOS() = default;`
- L31 _public prototype_ `FOnlinePlayerSanctionEOS(FOnlineSubsystemEOS* InSubsystem);`
- L33 _public prototype_ `virtual void CreatePlayerSanctionAppeal(const FUniqueNetId& LocalUserId, FPlayerSanctionAppealSettings&& SanctionAppealSettings, FOnCreatePlayerSanctionAppealComplete&& Delegate) override;`
- L35 _public prototype_ `virtual void QueryActivePlayerSanctions(const FUniqueNetId& LocalUserId, const FUniqueNetId& TargetUserId, FOnQueryActivePlayerSanctionsComplete&& Delegate) override;`
- L37 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedActivePlayerSanctions(const FUniqueNetId& TargetUserId, TArray<FOnlinePlayerSanction>& OutPlayerSanctions) override;`
- L42 _private member_ `FOnlineSubsystemEOS* EOSSubsystem;` — Reference to the main EOS subsystem
- L45 _private member_ `TUniqueNetIdMap<TArray<FOnlinePlayerSanction>> CachedPlayerSanctionsMap;` — Holds the cached info from the last time this was called

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlinePlayerSanctionEOS, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlinePlayerSanctionEOS, Log, All);`
- L11 _macro_ `#define UE_LOG_ONLINE_PLAYERSANCTIONEOS(Verbosity, Format, ...) \`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlinePurchaseEOS.h` (Private)


#### class `FOnlinePurchaseEOS`  
`class FOnlinePurchaseEOS : public IOnlinePurchase, public TSharedFromThis<FOnlinePurchaseEOS, ESPMode::ThreadSafe>`  
_L19-61_
- inherits: `IOnlinePurchase,TSharedFromThis<FOnlinePurchaseEOS,ESPMode::ThreadSafe>`
- L24 _public prototype_ `virtual ~FOnlinePurchaseEOS() = default;`
- L26 _public function_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId) override`
- L27 _public function_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId, FOnlineError& Error) override`
- L33 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseCheckoutComplete& Delegate) override;` — Checkout store offers and return a receipt. Receipt contains the EOS_Ecom_EntitlementId in the LineItem.ValidationInfo which can be redeemed via FinalizeReceiptValidationInfo
- L35 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseReceiptlessCheckoutComplete& Delegate) override;` — Checkout store offers
- L37 _public prototype_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId) override;` — Not implemented
- L39 _public prototype_ `virtual void RedeemCode(const FUniqueNetId& UserId, const FRedeemCodeRequest& RedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& Delegate) override;` — Not implemented
- L41 _public prototype_ `virtual void QueryReceipts(const FUniqueNetId& UserId, bool , const FOnQueryReceiptsComplete& Delegate) override;` — Retrieve and cache ownership data only - To retrieve entitlements use QueryEntitlements in the OnlineEntitlements interface
- L43 _public prototype_ `virtual void GetReceipts(const FUniqueNetId& UserId, TArray<FPurchaseReceipt>& OutReceipts) const override;` — Retrieve cached ownership data
- L45 _public prototype_ `virtual void FinalizeReceiptValidationInfo(const FUniqueNetId& UserId, FString& InReceiptValidationInfo, const FOnFinalizeReceiptValidationInfoComplete& Delegate) override;` — Used to redeem an entitlement - Pass in the EntitlementId in InReceiptValidationInfo - The EntitlementId is provided in the CheckoutCallback with receipt in LineItem.ValidationInfo and is provided in GetAllEntitlements, GetEntitlement, and GetItemEntitlement in the OnlineEntitlements interface
- L47 _public prototype_ `FOnlinePurchaseEOS(FOnlineSubsystemEOS* InSubsystem);`
- L49 _public prototype_ `bool HandlePurchaseExec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L53 _private prototype_ `FOnlinePurchaseEOS() = delete;` — Default constructor disabled
- L56 _private member_ `FOnlineSubsystemEOS* EOSSubsystem;` — Reference to the main EOS subsystem
- L60 _private member_ `TArray<FPurchaseReceipt> CachedReceipts;` — @todo joeg - make this support multiple users

#### Free symbols / members of external scopes

- L63 _typedef_ `typedef TSharedPtr<FOnlinePurchaseEOS, ESPMode::ThreadSafe> FOnlinePurchaseEOSPtr;`
- L64 _typedef_ `typedef TWeakPtr<FOnlinePurchaseEOS, ESPMode::ThreadSafe> FOnlinePurchaseEOSWeakPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineSessionEOS.h` (Private)


#### struct `FSessionSearchEOS`  
`struct FSessionSearchEOS`  
_L22-35_
- L24 _public member_ `EOS_HSessionSearch SearchHandle;`
- L26 _public function_ `FSessionSearchEOS(EOS_HSessionSearch InSearchHandle) : SearchHandle(InSearchHandle)`
- L31 _public function_ `virtual ~FSessionSearchEOS()`

#### class `FOnlineSessionEOS`  
`class FOnlineSessionEOS : public IOnlineSession , public TSharedFromThis<FOnlineSessionEOS, ESPMode::ThreadSafe>`  
_L40-355_
- inherits: `IOnlineSession,TSharedFromThis<FOnlineSessionEOS,ESPMode::ThreadSafe>`
- desc: Interface for interacting with EOS sessions
- L45 _public prototype_ `FOnlineSessionEOS() = delete;`
- L46 _public prototype_ `virtual ~FOnlineSessionEOS();`
- L48 _public prototype_ `virtual FUniqueNetIdPtr CreateSessionIdFromString(const FString& SessionIdStr) override;`
- L50 _public function_ `FNamedOnlineSession* GetNamedSession(FName SessionName) override`
- L63 _public function_ `virtual void RemoveNamedSession(FName SessionName) override`
- L76 _public function_ `virtual EOnlineSessionState::Type GetSessionState(FName SessionName) const override`
- L90 _public function_ `virtual bool HasPresenceSession() override`
- L107 _public prototype_ `virtual bool CreateSession(int32 HostingPlayerNum, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;` — The BucketId for the session can be specified via adding a custom session setting with the key OSSEOS_BUCKET_ID_ATTRIBUTE_KEY. A default value will be used otherwise
- L109 _public prototype_ `virtual bool CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;` — The BucketId for the session can be specified via adding a custom session setting with the key OSSEOS_BUCKET_ID_ATTRIBUTE_KEY. A default value will be used otherwise
- L110 _public prototype_ `virtual bool StartSession(FName SessionName) override;`
- L111 _public prototype_ `virtual bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData = true) override;`
- L112 _public prototype_ `virtual bool EndSession(FName SessionName) override;`
- L113 _public prototype_ `virtual bool DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate = FOnDestroySessionCompleteDelegate()) override;`
- L114 _public prototype_ `virtual bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId) override;`
- L115 _public prototype_ `virtual bool StartMatchmaking(const TArray< FUniqueNetIdRef >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L116 _public prototype_ `virtual bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName) override;`
- L117 _public prototype_ `virtual bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName) override;`
- L119 _public prototype_ `virtual bool FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;` — The BucketId to be used in the search can be specified via adding a custom search filter with the key OSSEOS_BUCKET_ID_ATTRIBUTE_KEY. A default value will be used otherwise
- L121 _public prototype_ `virtual bool FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;` — The BucketId to be used in the search can be specified via adding a custom search filter with the key OSSEOS_BUCKET_ID_ATTRIBUTE_KEY. A default value will be used otherwise
- L122 _public prototype_ `virtual bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate) override;`
- L123 _public prototype_ `virtual bool CancelFindSessions() override;`
- L124 _public prototype_ `virtual bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult) override;`
- L125 _public prototype_ `virtual bool JoinSession(int32 PlayerNum, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L126 _public prototype_ `virtual bool JoinSession(const FUniqueNetId& PlayerId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L127 _public prototype_ `virtual bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend) override;`
- L128 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend) override;`
- L129 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList) override;`
- L130 _public prototype_ `virtual bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend) override;`
- L131 _public prototype_ `virtual bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend) override;`
- L132 _public prototype_ `virtual bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L133 _public prototype_ `virtual bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L134 _public prototype_ `virtual bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType) override;`
- L135 _public prototype_ `virtual bool GetResolvedConnectString(const FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo) override;`
- L136 _public prototype_ `virtual FOnlineSessionSettings* GetSessionSettings(FName SessionName) override;`
- L137 _public prototype_ `virtual FString GetVoiceChatRoomName(int32 LocalUserNum, const FName& SessionName) override;`
- L138 _public prototype_ `virtual bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited) override;`
- L139 _public prototype_ `virtual bool RegisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players, bool bWasInvited = false) override;`
- L140 _public prototype_ `virtual bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId) override;`
- L141 _public prototype_ `virtual bool UnregisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players) override;`
- L142 _public prototype_ `virtual void RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate) override;`
- L143 _public prototype_ `virtual void UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate) override;`
- L144 _public prototype_ `virtual void RemovePlayerFromSession(int32 LocalUserNum, FName SessionName, const FUniqueNetId& TargetPlayerId) override;`
- L145 _public prototype_ `virtual int32 GetNumSessions() override;`
- L146 _public prototype_ `virtual void DumpSessionState() override;`
- L150 _public member_ `mutable FCriticalSection SessionLock;` — Critical sections for thread safe operation of session lists
- L153 _public member_ `TArray<FNamedOnlineSession> Sessions;` — Current session settings
- L156 _public member_ `TSharedPtr<FOnlineSessionSearch> CurrentSessionSearch;` — Current search object
- L159 _public member_ `double SessionSearchStartInSeconds;` — Current search start time.
- L161 _public function_ `FOnlineSessionEOS(FOnlineSubsystemEOS* InSubsystem) : CurrentSessionSearch(nullptr) , SessionSearchStartInSeconds(0) , EOSSubsystem(InSubsystem)`
- L171 _public prototype_ `void Tick(float DeltaTime);` — Session tick for various background tasks
- L174 _public function_ `class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSessionSettings& SessionSettings) override` — IOnlineSession
- L180 _public function_ `class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSession& Session) override`
- L186 _public prototype_ `void CheckPendingSessionInvite();`
- L188 _public prototype_ `void UpdateOrAddLobbyMember(const FUniqueNetIdEOSLobbyRef& LobbyNetId, const FUniqueNetIdEOSRef& PlayerId);`
- L189 _public prototype_ `bool AddOnlineSessionMember(FName SessionName, const FUniqueNetIdRef& PlayerId);`
- L190 _public prototype_ `bool RemoveOnlineSessionMember(FName SessionName, const FUniqueNetIdRef& PlayerId);`
- L192 _public prototype_ `void RegisterLocalPlayers(class FNamedOnlineSession* Session);`
- L194 _public prototype_ `void Init();`
- L196 _public prototype_ `bool HandleSessionExec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L201 _private member_ `EOS_HLobby LobbyHandle;`
- L202 _private member_ `TArray<TSharedRef<FLobbyDetailsEOS>> LobbySearchResultsPendingIdResolution;`
- L205 _private member_ `FCallbackBase* LobbyCreatedCallback;` — Lobby session callbacks and methods
- L206 _private member_ `FCallbackBase* LobbySearchFindCallback;`
- L207 _private member_ `FCallbackBase* LobbyJoinedCallback;`
- L208 _private member_ `FCallbackBase* LobbyLeftCallback;`
- L209 _private member_ `FCallbackBase* LobbyDestroyedCallback;`
- L210 _private member_ `FCallbackBase* LobbySendInviteCallback;`
- L212 _private prototype_ `uint32 CreateLobbySession(int32 HostingPlayerNum, FNamedOnlineSession* Session);`
- L213 _private prototype_ `void OnCreateLobbySessionUpdateComplete(FName SessionName, bool bWasSuccessful, int32 HostingPlayerNum);`
- L214 _private prototype_ `void DestroyLobbySessionOnCreationUpdateError(int32 LocalUserNum, FNamedOnlineSession* Session);`
- L215 _private prototype_ `uint32 FindLobbySession(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings);`
- L216 _private prototype_ `void StartLobbySearch(int32 SearchingPlayerNum, EOS_HLobbySearch LobbySearchHandle, const TSharedRef<FOnlineSessionSearch>& SearchSettings, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate);`
- L217 _private prototype_ `uint32 JoinLobbySession(int32 PlayerNum, FNamedOnlineSession* Session, const FOnlineSession* SearchSession);`
- L218 _private prototype_ `uint32 UpdateLobbySession(FNamedOnlineSession* Session, const FOnUpdateSessionCompleteDelegate& CompletionDelegate);`
- L219 _private prototype_ `uint32 StartLobbySession(FNamedOnlineSession* Session);`
- L220 _private prototype_ `uint32 EndLobbySession(FNamedOnlineSession* Session);`
- L221 _private prototype_ `uint32 DestroyLobbySession(int32 LocalUserNum, FNamedOnlineSession* Session, const FOnDestroySessionCompleteDelegate& CompletionDelegate);`
- L222 _private prototype_ `bool SendLobbyInvite(FName SessionName, EOS_ProductUserId SenderId, EOS_ProductUserId ReceiverId);`
- L225 _private member_ `EOS_NotificationId LobbyUpdateReceivedId;` — Lobby notification callbacks and methods
- L226 _private member_ `FCallbackBase* LobbyUpdateReceivedCallback;`
- L227 _private member_ `EOS_NotificationId LobbyMemberUpdateReceivedId;`
- L228 _private member_ `FCallbackBase* LobbyMemberUpdateReceivedCallback;`
- L229 _private member_ `EOS_NotificationId LobbyMemberStatusReceivedId;`
- L230 _private member_ `FCallbackBase* LobbyMemberStatusReceivedCallback;`
- L231 _private member_ `EOS_NotificationId LobbyInviteReceivedId;`
- L232 _private member_ `FCallbackBase* LobbyInviteReceivedCallback;`
- L233 _private member_ `EOS_NotificationId LobbyInviteAcceptedId;`
- L234 _private member_ `FCallbackBase* LobbyInviteAcceptedCallback;`
- L235 _private member_ `EOS_NotificationId JoinLobbyAcceptedId;`
- L236 _private member_ `FCallbackBase* JoinLobbyAcceptedCallback;`
- L237 _private member_ `EOS_NotificationId LeaveLobbyRequestedId;`
- L238 _private member_ `FCallbackBase* LeaveLobbyRequestedCallback;`
- L240 _private prototype_ `void OnLobbyUpdateReceived(const EOS_LobbyId& LobbyId);`
- L241 _private prototype_ `void OnLobbyMemberUpdateReceived(const EOS_LobbyId& LobbyId, const EOS_ProductUserId& TargetUserId);`
- L242 _private prototype_ `void OnMemberStatusReceived(const EOS_LobbyId& LobbyId, const EOS_ProductUserId& TargetUserId, EOS_ELobbyMemberStatus CurrentStatus);`
- L243 _private prototype_ `void OnLobbyInviteReceived(const EOS_Lobby_LobbyInviteReceivedCallbackInfo* Data);`
- L244 _private prototype_ `void OnLobbyInviteAccepted(const EOS_Lobby_LobbyInviteAcceptedCallbackInfo* Data);`
- L245 _private prototype_ `void OnJoinLobbyAccepted(const EOS_Lobby_JoinLobbyAcceptedCallbackInfo* Data);`
- L246 _private prototype_ `void OnLeaveLobbyRequested(const EOS_Lobby_LeaveLobbyRequestedCallbackInfo* Data);`
- L249 _private prototype_ `void SetLobbyPermissionLevel(EOS_HLobbyModification LobbyModificationHandle, FNamedOnlineSession* Session);` — Methods to update an API Lobby from an OSS Lobby
- L250 _private prototype_ `void SetLobbyMaxMembers(EOS_HLobbyModification LobbyModificationHandle, FNamedOnlineSession* Session);`
- L251 _private prototype_ `void SetLobbyAttributes(EOS_HLobbyModification LobbyModificationHandle, FNamedOnlineSession* Session);`
- L252 _private prototype_ `void AddLobbyAttribute(EOS_HLobbyModification LobbyModificationHandle, const EOS_Lobby_AttributeData* Attribute);`
- L253 _private prototype_ `void SetLobbyMemberAttributes(EOS_HLobbyModification LobbyModificationHandle, FUniqueNetIdRef LobbyMemberId, FNamedOnlineSession& Session);`
- L254 _private prototype_ `void AddLobbyMemberAttribute(EOS_HLobbyModification LobbyModificationHandle, const EOS_Lobby_AttributeData* Attribute);`
- L257 _private typedef_ `typedef TFunction<void(bool bWasSuccessful)> FOnCopyLobbyDataCompleteCallback;` — Methods to update an OSS Lobby from an API Lobby
- L258 _private prototype_ `void CopyLobbyData(const TSharedRef<FLobbyDetailsEOS>& LobbyDetails, EOS_LobbyDetails_Info* LobbyDetailsInfo, FOnlineSession& OutSession, bool bCopyMemberData, FOnCopyLobbyDataCompleteCallback&& Callback);`
- L259 _private prototype_ `void CopyLobbyAttributes(const FLobbyDetailsEOS& LobbyDetails, FOnlineSession& OutSession);`
- L260 _private prototype_ `void CopyLobbyMemberAttributes(const FLobbyDetailsEOS& LobbyDetails, const EOS_ProductUserId& TargetUserId, FSessionSettings& OutSessionSettings);`
- L263 _private prototype_ `void AddLobbySearchAttribute(EOS_HLobbySearch LobbySearchHandle, const EOS_Lobby_AttributeData* Attribute, EOS_EOnlineComparisonOp ComparisonOp);` — Lobby search
- L264 _private prototype_ `void AddLobbySearchResult(const TSharedRef<FLobbyDetailsEOS>& LobbyDetails, const TSharedRef<FOnlineSessionSearch>& SearchSettings, FOnCopyLobbyDataCompleteCallback&& Callback);`
- L267 _private typedef_ `typedef TFunction<void(const EOS_ProductUserId& ProductUserId, EOS_EpicAccountId& EpicAccountId)> GetEpicAccountIdAsyncCallback;` — Helper methods
- L269 _private prototype_ `void RegisterSessionNotifications();`
- L270 _private prototype_ `void OnSessionInviteReceived(const EOS_Sessions_SessionInviteReceivedCallbackInfo* Data);`
- L271 _private prototype_ `void OnSessionInviteAccepted(const EOS_Sessions_SessionInviteAcceptedCallbackInfo* Data);`
- L272 _private prototype_ `void OnJoinSessionAccepted(const EOS_Sessions_JoinSessionAcceptedCallbackInfo* Data);`
- L273 _private prototype_ `void OnLeaveSessionRequested(const EOS_Sessions_LeaveSessionRequestedCallbackInfo* Data);`
- L275 _private prototype_ `void RegisterLobbyNotifications();`
- L276 _private prototype_ `FNamedOnlineSession* GetNamedSessionFromLobbyId(const FUniqueNetIdEOSLobby& LobbyId);`
- L277 _private prototype_ `FOnlineSessionSearchResult* GetSearchResultFromLobbyId(const FUniqueNetIdEOSLobby& LobbyId);`
- L278 _private prototype_ `FOnlineSession* GetOnlineSessionFromLobbyId(const FUniqueNetIdEOSLobby& LobbyId);`
- L279 _private prototype_ `EOS_ELobbyPermissionLevel GetLobbyPermissionLevelFromSessionSettings(const FOnlineSessionSettings& SessionSettings);`
- L280 _private prototype_ `uint32_t GetLobbyMaxMembersFromSessionSettings(const FOnlineSessionSettings& SessionSettings);`
- L281 _private prototype_ `static FString GetBucketId(const FOnlineSessionSettings& SessionSettings);`
- L282 _private prototype_ `static FString GetBucketId(const FOnlineSessionSearch& SessionSettings);`
- L285 _private member_ `TArray<TSharedRef<FSessionDetailsEOS>> SessionSearchResultsPendingIdResolution;` — EOS Sessions
- L287 _private prototype_ `uint32 CreateEOSSession(int32 HostingPlayerNum, FNamedOnlineSession* Session);`
- L288 _private prototype_ `uint32 JoinEOSSession(int32 PlayerNum, FNamedOnlineSession* Session);`
- L289 _private prototype_ `uint32 StartEOSSession(FNamedOnlineSession* Session);`
- L290 _private prototype_ `uint32 UpdateEOSSession(FNamedOnlineSession* Session);`
- L291 _private prototype_ `uint32 EndEOSSession(FNamedOnlineSession* Session);`
- L292 _private prototype_ `uint32 DestroyEOSSession(FNamedOnlineSession* Session, const FOnDestroySessionCompleteDelegate& CompletionDelegate);`
- L293 _private prototype_ `uint32 FindEOSSession(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings);`
- L294 _private prototype_ `bool SendEOSSessionInvite(FName SessionName, EOS_ProductUserId SenderId, EOS_ProductUserId ReceiverId);`
- L295 _private prototype_ `void FindEOSSessionById(int32 SearchingPlayerNum, const FUniqueNetId& SessionId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate);`
- L297 _private prototype_ `bool SendSessionInvite(FName SessionName, EOS_ProductUserId SenderId, EOS_ProductUserId ReceiverId);`
- L299 _private prototype_ `void BeginSessionAnalytics(FNamedOnlineSession* Session);`
- L300 _private prototype_ `void EndSessionAnalytics();`
- L302 _private typedef_ `typedef TFunction<void(bool bWasSuccessful)> FOnCopySessionDataCompleteCallback;`
- L303 _private prototype_ `void AddSearchResult(const TSharedRef<FSessionDetailsEOS>& SessionHandle, const TSharedRef<FOnlineSessionSearch>& SearchSettings, FOnCopySessionDataCompleteCallback&& Callback);`
- L304 _private prototype_ `void AddSearchAttribute(EOS_HSessionSearch SearchHandle, const EOS_Sessions_AttributeData* Attribute, EOS_EOnlineComparisonOp ComparisonOp);`
- L305 _private prototype_ `void CopyAttributes(const FSessionDetailsEOS& SessionHandle, FOnlineSession& OutSession);`
- L307 _private prototype_ `void SetPermissionLevel(EOS_HSessionModification SessionModHandle, FNamedOnlineSession* Session);`
- L308 _private prototype_ `void SetMaxPlayers(EOS_HSessionModification SessionModHandle, FNamedOnlineSession* Session);`
- L309 _private prototype_ `void SetInvitesAllowed(EOS_HSessionModification SessionModHandle, FNamedOnlineSession* Session);`
- L310 _private prototype_ `void SetJoinInProgress(EOS_HSessionModification SessionModHandle, FNamedOnlineSession* Session);`
- L311 _private prototype_ `void AddAttribute(EOS_HSessionModification SessionModHandle, const EOS_Sessions_AttributeData* Attribute);`
- L312 _private prototype_ `void SetAttributes(EOS_HSessionModification SessionModHandle, FNamedOnlineSession* Session);`
- L313 _private typedef_ `typedef TEOSCallback<EOS_Sessions_OnUpdateSessionCallback, EOS_Sessions_UpdateSessionCallbackInfo, FOnlineSessionEOS> FUpdateSessionCallback;`
- L314 _private prototype_ `uint32 SharedSessionUpdate(EOS_HSessionModification SessionModHandle, FNamedOnlineSession* Session, FUpdateSessionCallback* Callback);`
- L316 _private prototype_ `void TickLanTasks(float DeltaTime);`
- L317 _private prototype_ `uint32 CreateLANSession(int32 HostingPlayerNum, FNamedOnlineSession* Session);`
- L318 _private prototype_ `uint32 JoinLANSession(int32 PlayerNum, class FNamedOnlineSession* Session, const class FOnlineSession* SearchSession);`
- L319 _private prototype_ `uint32 FindLANSession();`
- L321 _private prototype_ `void AppendSessionToPacket(class FNboSerializeToBufferEOS& Packet, class FOnlineSession* Session);`
- L322 _private prototype_ `void AppendSessionSettingsToPacket(class FNboSerializeToBufferEOS& Packet, FOnlineSessionSettings* SessionSettings);`
- L323 _private prototype_ `void ReadSessionFromPacket(class FNboSerializeFromBufferEOS& Packet, class FOnlineSession* Session);`
- L324 _private prototype_ `void ReadSettingsFromPacket(class FNboSerializeFromBufferEOS& Packet, FOnlineSessionSettings& SessionSettings);`
- L325 _private prototype_ `void OnValidQueryPacketReceived(uint8* PacketData, int32 PacketLength, uint64 ClientNonce);`
- L326 _private prototype_ `void OnValidResponsePacketReceived(uint8* PacketData, int32 PacketLength);`
- L327 _private prototype_ `void OnLANSearchTimeout();`
- L328 _private prototype_ `static void SetPortFromNetDriver(const FOnlineSubsystemEOS& Subsystem, const TSharedPtr<FOnlineSessionInfo>& SessionInfo);`
- L329 _private prototype_ `bool IsHost(const FNamedOnlineSession& Session) const;`
- L331 _private prototype_ `int32 GetDefaultLocalUserForLobby(const FUniqueNetIdString& SessionId);`
- L334 _private member_ `FOnlineSubsystemEOS* EOSSubsystem;` — Reference to the main EOS subsystem
- L337 _private member_ `TSharedPtr<FLANSession> LANSession;` — Handles advertising sessions over LAN and client searches
- L339 _private member_ `TSharedPtr<FSessionSearchEOS> CurrentSearchHandle;` — EOS handle wrapper to hold onto it for scope of the search
- L341 _private member_ `TSharedPtr<FOnlineSessionSearch> LastInviteSearch;` — The last accepted invite search. It searches by session id
- L344 _private member_ `bool bAggregatedAddSearchResultSuccessful;` — Used to track adding asynchronous session search results
- L347 _private member_ `EOS_NotificationId SessionInviteReceivedId;` — Notification state for SDK events
- L348 _private member_ `FCallbackBase* SessionInviteReceivedCallback;`
- L349 _private member_ `EOS_NotificationId SessionInviteAcceptedId;`
- L350 _private member_ `FCallbackBase* SessionInviteAcceptedCallback;`
- L351 _private member_ `EOS_NotificationId JoinSessionAcceptedId;`
- L352 _private member_ `FCallbackBase* JoinSessionAcceptedCallback;`
- L353 _private member_ `EOS_NotificationId LeaveSessionRequestedId;`
- L354 _private member_ `FCallbackBase* LeaveSessionRequestedCallback;`

#### Free symbols / members of external scopes

- L17 _variable_ `static FName EOS_SESSION_ID = TEXT("EOS`
- L18 _variable_ `static FName EOS_LOBBY_ID = TEXT("EOS`
- L19 _prototype_ `TEMP_UNIQUENETIDSTRING_SUBCLASS(FUniqueNetIdEOSSession, EOS_SESSION_ID);`
- L20 _prototype_ `TEMP_UNIQUENETIDSTRING_SUBCLASS(FUniqueNetIdEOSLobby, EOS_LOBBY_ID);`
- L357 _typedef_ `typedef TSharedPtr<FOnlineSessionEOS, ESPMode::ThreadSafe> FOnlineSessionEOSPtr;`
- L358 _typedef_ `typedef TWeakPtr<FOnlineSessionEOS, ESPMode::ThreadSafe> FOnlineSessionEOSWeakPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineStatsEOS.h` (Private)


#### class `FOnlineStatsEOS`  
`class FOnlineStatsEOS : public IOnlineStats , public TSharedFromThis<FOnlineStatsEOS, ESPMode::ThreadSafe>`  
_L16-46_
- inherits: `IOnlineStats,TSharedFromThis<FOnlineStatsEOS,ESPMode::ThreadSafe>`
- desc: Interface for interacting with EOS stats
- L21 _public prototype_ `FOnlineStatsEOS() = delete;`
- L22 _public prototype_ `virtual ~FOnlineStatsEOS() = default;`
- L25 _public prototype_ `virtual void QueryStats(const FUniqueNetIdRef LocalUserId, const FUniqueNetIdRef StatsUser, const FOnlineStatsQueryUserStatsComplete& Delegate) override;` — IOnlineStats Interface
- L26 _public prototype_ `virtual void QueryStats(const FUniqueNetIdRef LocalUserId, const TArray<FUniqueNetIdRef>& StatUsers, const TArray<FString>& StatNames, const FOnlineStatsQueryUsersStatsComplete& Delegate) override;`
- L27 _public prototype_ `virtual TSharedPtr<const FOnlineStatsUserStats> GetStats(const FUniqueNetIdRef StatsUserId) const override;`
- L28 _public prototype_ `virtual void UpdateStats(const FUniqueNetIdRef LocalUserId, const TArray<FOnlineStatsUserUpdatedStats>& UpdatedUserStats, const FOnlineStatsUpdateStatsComplete& Delegate) override;`
- L30 _public prototype_ `virtual void ResetStats(const FUniqueNetIdRef StatsUserId) override;`
- L34 _public function_ `FOnlineStatsEOS(FOnlineSubsystemEOS* InSubsystem) : EOSSubsystem(InSubsystem)`
- L40 _private prototype_ `void WriteStats(EOS_ProductUserId LocalUserId, EOS_ProductUserId UserId, const FOnlineStatsUserUpdatedStats& PlayerStats);`
- L43 _private member_ `FOnlineSubsystemEOS* EOSSubsystem;` — Reference to the main EOS subsystem
- L45 _private member_ `TUniqueNetIdMap<TSharedRef<FOnlineStatsUserStats>> StatsCache;` — Cached list of stats for users as they arrive

#### Free symbols / members of external scopes

- L48 _typedef_ `typedef TSharedPtr<FOnlineStatsEOS, ESPMode::ThreadSafe> FOnlineStatsEOSPtr;`
- L49 _typedef_ `typedef TWeakPtr<FOnlineStatsEOS, ESPMode::ThreadSafe> FOnlineStatsEOSWeakPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineStoreEOS.h` (Private)


#### class `FOnlineStoreEOS`  
`class FOnlineStoreEOS : public IOnlineStoreV2, public IOnlinePurchase, public TSharedFromThis<FOnlineStoreEOS, ESPMode::ThreadSafe>`  
_L19-74_
- inherits: `IOnlineStoreV2,IOnlinePurchase,TSharedFromThis<FOnlineStoreEOS,ESPMode::ThreadSafe>`
- desc: Implementation for online store via EGS
- L25 _public prototype_ `virtual ~FOnlineStoreEOS() = default;`
- L28 _public prototype_ `virtual void QueryCategories(const FUniqueNetId& UserId, const FOnQueryOnlineStoreCategoriesComplete& Delegate) override;`
- L29 _public prototype_ `virtual void GetCategories(TArray<FOnlineStoreCategory>& OutCategories) const override;`
- L30 _public prototype_ `virtual void QueryOffersByFilter(const FUniqueNetId& UserId, const FOnlineStoreFilter& Filter, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L31 _public prototype_ `virtual void QueryOffersById(const FUniqueNetId& UserId, const TArray<FUniqueOfferId>& OfferIds, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L32 _public prototype_ `virtual void GetOffers(TArray<FOnlineStoreOfferRef>& OutOffers) const override;`
- L33 _public prototype_ `virtual TSharedPtr<FOnlineStoreOffer> GetOffer(const FUniqueOfferId& OfferId) const override;`
- L37 _public function_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId) override`
- L38 _public function_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId, FOnlineError& Error) override`
- L44 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseCheckoutComplete& Delegate) override;`
- L45 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseReceiptlessCheckoutComplete& Delegate) override;`
- L46 _public prototype_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId) override;`
- L47 _public prototype_ `virtual void RedeemCode(const FUniqueNetId& UserId, const FRedeemCodeRequest& RedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& Delegate) override;`
- L48 _public prototype_ `virtual void QueryReceipts(const FUniqueNetId& UserId, bool bRestoreReceipts, const FOnQueryReceiptsComplete& Delegate) override;`
- L49 _public prototype_ `virtual void GetReceipts(const FUniqueNetId& UserId, TArray<FPurchaseReceipt>& OutReceipts) const override;`
- L50 _public prototype_ `virtual void FinalizeReceiptValidationInfo(const FUniqueNetId& UserId, FString& InReceiptValidationInfo, const FOnFinalizeReceiptValidationInfoComplete& Delegate) override;`
- L53 _public prototype_ `FOnlineStoreEOS(FOnlineSubsystemEOS* InSubsystem);`
- L55 _public prototype_ `bool HandleEcomExec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L59 _private prototype_ `FOnlineStoreEOS() = delete;` — Default constructor disabled
- L61 _private prototype_ `void QueryOffers(const FUniqueNetId& UserId, const FOnQueryOnlineStoreOffersComplete& Delegate);`
- L64 _private member_ `FOnlineSubsystemEOS* EOSSubsystem;` — Reference to the main EOS subsystem
- L67 _private member_ `TArray<FOnlineStoreOfferRef> CachedOffers;` — The set of offers for this title
- L69 _private member_ `TArray<FUniqueOfferId> CachedOfferIds;` — List of offer ids for this title
- L73 _private member_ `TArray<FPurchaseReceipt> CachedReceipts;` — @todo joeg - make this support multiple users

#### Free symbols / members of external scopes

- L76 _typedef_ `typedef TSharedPtr<FOnlineStoreEOS, ESPMode::ThreadSafe> FOnlineStoreEOSPtr;`
- L77 _typedef_ `typedef TWeakPtr<FOnlineStoreEOS, ESPMode::ThreadSafe> FOnlineStoreEOSWeakPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineStoreEOSV2.h` (Private)


#### class `FOnlineStoreEOSV2`  
`class FOnlineStoreEOSV2 : public IOnlineStoreV2, public TSharedFromThis<FOnlineStoreEOSV2, ESPMode::ThreadSafe>`  
_L18-50_
- inherits: `IOnlineStoreV2,TSharedFromThis<FOnlineStoreEOSV2,ESPMode::ThreadSafe>`
- desc: Retrieve offers from store. Offers can be checked out using the OnlinePurchase interface
- L23 _public prototype_ `virtual ~FOnlineStoreEOSV2() = default;`
- L25 _public prototype_ `virtual void QueryCategories(const FUniqueNetId& UserId, const FOnQueryOnlineStoreCategoriesComplete& Delegate) override;`
- L26 _public prototype_ `virtual void GetCategories(TArray<FOnlineStoreCategory>& OutCategories) const override;`
- L27 _public prototype_ `virtual void QueryOffersByFilter(const FUniqueNetId& UserId, const FOnlineStoreFilter& Filter, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L28 _public prototype_ `virtual void QueryOffersById(const FUniqueNetId& UserId, const TArray<FUniqueOfferId>& OfferIds, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L29 _public prototype_ `virtual void GetOffers(TArray<FOnlineStoreOfferRef>& OutOffers) const override;`
- L30 _public prototype_ `virtual TSharedPtr<FOnlineStoreOffer> GetOffer(const FUniqueOfferId& OfferId) const override;`
- L32 _public prototype_ `FOnlineStoreEOSV2(FOnlineSubsystemEOS* InSubsystem);`
- L34 _public prototype_ `bool HandleEcomExec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L38 _private prototype_ `FOnlineStoreEOSV2() = delete;` — Default constructor disabled
- L41 _private prototype_ `void QueryOffers(const FUniqueNetId& UserId, const FOnQueryOnlineStoreOffersComplete& Delegate);` — Retrieve Epic Games Store offers
- L44 _private member_ `FOnlineSubsystemEOS* EOSSubsystem;` — Reference to the main EOS subsystem
- L47 _private member_ `TArray<FOnlineStoreOfferRef> CachedOffers;` — The set of offers for this title
- L49 _private member_ `TArray<FUniqueOfferId> CachedOfferIds;` — List of offer ids for this title

#### Free symbols / members of external scopes

- L52 _typedef_ `typedef TSharedPtr<FOnlineStoreEOSV2, ESPMode::ThreadSafe> FOnlineStoreEOSV2Ptr;`
- L53 _typedef_ `typedef TWeakPtr<FOnlineStoreEOSV2, ESPMode::ThreadSafe> FOnlineStoreEOSV2WeakPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineSubsystemEOS.h` (Private)


#### class `FOnlineSubsystemEOS`  
`class FOnlineSubsystemEOS : public IOnlineSubsystemEOS`  
_L71-194_
- inherits: `IOnlineSubsystemEOS`
- desc: OnlineSubsystemEOS - Implementation of the online subsystem for EOS services
- L75 _public prototype_ `virtual ~FOnlineSubsystemEOS() = default;`
- L78 _public prototype_ `static void ModuleInit();` — Used to be called before RHIInit()
- L79 _public prototype_ `static void ModuleShutdown();`
- L81 _public function_ `FPlatformEOSHelpersPtr GetEOSHelpers()`
- L84 _public prototype_ `virtual IVoiceChatUser* GetVoiceChatUserInterface(const FUniqueNetId& LocalUserId) override;` — IOnlineSubsystemEOS
- L85 _public function_ `virtual IEOSPlatformHandlePtr GetEOSPlatformHandle() const override`
- L86 _public prototype_ `virtual void QueryUniqueNetId(int32 LocalUserNum, const EOS_ProductUserId& ProductUserId, const FOnQueryUniqueNetIdComplete & Callback) override;`
- L89 _public prototype_ `virtual IOnlineSessionPtr GetSessionInterface() const override;` — IOnlineSubsystem
- L90 _public prototype_ `virtual IOnlineFriendsPtr GetFriendsInterface() const override;`
- L91 _public prototype_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;`
- L92 _public prototype_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;`
- L93 _public prototype_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;`
- L94 _public prototype_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;`
- L95 _public prototype_ `virtual IOnlineVoicePtr GetVoiceInterface() const override;`
- L96 _public prototype_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;`
- L97 _public prototype_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override;`
- L98 _public prototype_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;`
- L99 _public prototype_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;`
- L100 _public prototype_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override;`
- L101 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;`
- L102 _public prototype_ `virtual IOnlineUserPtr GetUserInterface() const override;`
- L103 _public prototype_ `virtual IOnlinePresencePtr GetPresenceInterface() const override;`
- L104 _public prototype_ `virtual FText GetOnlineServiceName() const override;`
- L105 _public prototype_ `virtual IOnlineStatsPtr GetStatsInterface() const override;`
- L106 _public prototype_ `virtual IOnlinePlayerSanctionEOSPtr GetPlayerSanctionEOSInterface() const override;`
- L107 _public prototype_ `virtual IOnlinePlayerReportEOSPtr GetPlayerReportEOSInterface() const override;`
- L108 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L109 _public prototype_ `virtual void ReloadConfigs(const TSet<FString>& ConfigSections) override;`
- L111 _public function_ `virtual IOnlineGroupsPtr GetGroupsInterface() const override`
- L112 _public function_ `virtual IOnlinePartyPtr GetPartyInterface() const override`
- L113 _public function_ `virtual IOnlineTimePtr GetTimeInterface() const override`
- L114 _public function_ `virtual IOnlineEventsPtr GetEventsInterface() const override`
- L115 _public function_ `virtual IOnlineSharingPtr GetSharingInterface() const override`
- L116 _public function_ `virtual IOnlineMessagePtr GetMessageInterface() const override`
- L117 _public function_ `virtual IOnlineChatPtr GetChatInterface() const override`
- L118 _public function_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override`
- L119 _public function_ `virtual IOnlineTournamentPtr GetTournamentInterface() const override`
- L122 _public prototype_ `virtual bool Init() override;`
- L123 _public prototype_ `virtual bool Shutdown() override;`
- L124 _public prototype_ `virtual FString GetAppId() const override;`
- L127 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L130 _public prototype_ `FOnlineSubsystemEOS() = delete;` — Only the factory makes instances
- L131 _public prototype_ `explicit FOnlineSubsystemEOS(FName InInstanceName);`
- L133 _public member_ `FString ProductId;`
- L135 _public member_ `IEOSSDKManager* EOSSDKManager;`
- L138 _public member_ `IEOSPlatformHandlePtr EOSPlatformHandle;` — EOS handles
- L139 _public member_ `EOS_HAuth AuthHandle;`
- L140 _public member_ `EOS_HUI UIHandle;`
- L141 _public member_ `EOS_HFriends FriendsHandle;`
- L142 _public member_ `EOS_HUserInfo UserInfoHandle;`
- L143 _public member_ `EOS_HPresence PresenceHandle;`
- L144 _public member_ `EOS_HConnect ConnectHandle;`
- L145 _public member_ `EOS_HSessions SessionsHandle;`
- L146 _public member_ `EOS_HStats StatsHandle;`
- L147 _public member_ `EOS_HLeaderboards LeaderboardsHandle;`
- L148 _public member_ `EOS_HMetrics MetricsHandle;`
- L149 _public member_ `EOS_HAchievements AchievementsHandle;`
- L150 _public member_ `EOS_HEcom EcomHandle;`
- L151 _public member_ `EOS_HTitleStorage TitleStorageHandle;`
- L152 _public member_ `EOS_HPlayerDataStorage PlayerDataStorageHandle;`
- L153 _public member_ `EOS_HSanctions PlayerSanctionHandle;`
- L154 _public member_ `EOS_HReports PlayerReportHandle;`
- L157 _public member_ `FUserManagerEOSPtr UserManager;` — Manager that handles all user interfaces
- L159 _public member_ `FOnlineSessionEOSPtr SessionInterfacePtr;` — The session interface object
- L161 _public member_ `FOnlineStatsEOSPtr StatsInterfacePtr;` — Stats interface pointer
- L163 _public member_ `FOnlineLeaderboardsEOSPtr LeaderboardsInterfacePtr;` — Leaderboards interface pointer
- L164 _public member_ `FOnlineAchievementsEOSPtr AchievementsInterfacePtr;`
- L166 _public member_ `FOnlineStoreEOSPtr StoreInterfacePtr;` — EGS store interface pointer
- L168 _public member_ `FOnlineTitleFileEOSPtr TitleFileInterfacePtr;` — Title File interface pointer
- L170 _public member_ `FOnlineUserCloudEOSPtr UserCloudInterfacePtr;` — User Cloud interface pointer
- L172 _public member_ `FOnlinePlayerSanctionEOSPtr PlayerSanctionEOSPtr;` — Player sanction interface pointer
- L174 _public member_ `FOnlinePlayerReportEOSPtr PlayerReportInterfacePtr;` — Player Report interface pointer
- L176 _public member_ `FOnlineEntitlementsEOSPtr EntitlementsInterfacePtr;` — Entitlements interface pointer - only valid if bUseNewEcomFlow is true
- L178 _public member_ `FOnlinePurchaseEOSPtr PurchaseInterfacePtr;` — Purchase interface pointer - only valid if bUseNewEcomFlow is true
- L180 _public member_ `FOnlineStoreEOSV2Ptr StoreInterfaceV2Ptr;` — Store interface pointer used to retrieve EGS offers - only valid if bUseNewEcomFlow is true
- L182 _public member_ `TSharedPtr<FSocketSubsystemEOS, ESPMode::ThreadSafe> SocketSubsystem;`
- L184 _public member_ `static FPlatformEOSHelpersPtr EOSHelpersPtr;`
- L186 _public prototype_ `FEOSVoiceChatUser* GetEOSVoiceChatUserInterface(const FUniqueNetId& LocalUserId);`
- L187 _public prototype_ `void ReleaseVoiceChatUserInterface(const FUniqueNetId& LocalUserId);`
- L190 _private prototype_ `bool PlatformCreate();`
- L192 _private member_ `IVoiceChatPtr VoiceChatInterface;`
- L193 _private member_ `TUniqueNetIdMap<FOnlineSubsystemEOSVoiceChatUserWrapperRef> LocalVoiceChatUsers;`
- L202 _public function_ `explicit FOnlineSubsystemEOS(FName InInstanceName) : FOnlineSubsystemImpl(EOS_SUBSYSTEM, InInstanceName)`
- L209 _public function_ `virtual IOnlineSessionPtr GetSessionInterface() const override`
- L210 _public function_ `virtual IOnlineFriendsPtr GetFriendsInterface() const override`
- L213 _public function_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override`
- L214 _public function_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override`
- L215 _public function_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override`
- L216 _public function_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override`
- L217 _public function_ `virtual IOnlineVoicePtr GetVoiceInterface() const override`
- L218 _public function_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override`
- L220 _public function_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override`
- L221 _public function_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override`
- L222 _public function_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override`
- L223 _public function_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override`
- L226 _public function_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override`
- L228 _public function_ `virtual IOnlineUserPtr GetUserInterface() const override`
- L230 _public function_ `virtual IOnlinePresencePtr GetPresenceInterface() const override`
- L232 _public function_ `virtual IOnlineStatsPtr GetStatsInterface() const override`
- L235 _public function_ `virtual FText GetOnlineServiceName() const override`
- L237 _public function_ `virtual bool Init() override`
- L238 _public function_ `virtual bool Shutdown() override`
- L239 _public function_ `virtual FString GetAppId() const override`

#### class `FOnlineSubsystemEOS`  
`class FOnlineSubsystemEOS : public FOnlineSubsystemImpl`  
_L198-240_
- inherits: `FOnlineSubsystemImpl`
- L75 _public prototype_ `virtual ~FOnlineSubsystemEOS() = default;`
- L78 _public prototype_ `static void ModuleInit();` — Used to be called before RHIInit()
- L79 _public prototype_ `static void ModuleShutdown();`
- L81 _public function_ `FPlatformEOSHelpersPtr GetEOSHelpers()`
- L84 _public prototype_ `virtual IVoiceChatUser* GetVoiceChatUserInterface(const FUniqueNetId& LocalUserId) override;` — IOnlineSubsystemEOS
- L85 _public function_ `virtual IEOSPlatformHandlePtr GetEOSPlatformHandle() const override`
- L86 _public prototype_ `virtual void QueryUniqueNetId(int32 LocalUserNum, const EOS_ProductUserId& ProductUserId, const FOnQueryUniqueNetIdComplete & Callback) override;`
- L89 _public prototype_ `virtual IOnlineSessionPtr GetSessionInterface() const override;` — IOnlineSubsystem
- L90 _public prototype_ `virtual IOnlineFriendsPtr GetFriendsInterface() const override;`
- L91 _public prototype_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;`
- L92 _public prototype_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;`
- L93 _public prototype_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;`
- L94 _public prototype_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;`
- L95 _public prototype_ `virtual IOnlineVoicePtr GetVoiceInterface() const override;`
- L96 _public prototype_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;`
- L97 _public prototype_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override;`
- L98 _public prototype_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;`
- L99 _public prototype_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;`
- L100 _public prototype_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override;`
- L101 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;`
- L102 _public prototype_ `virtual IOnlineUserPtr GetUserInterface() const override;`
- L103 _public prototype_ `virtual IOnlinePresencePtr GetPresenceInterface() const override;`
- L104 _public prototype_ `virtual FText GetOnlineServiceName() const override;`
- L105 _public prototype_ `virtual IOnlineStatsPtr GetStatsInterface() const override;`
- L106 _public prototype_ `virtual IOnlinePlayerSanctionEOSPtr GetPlayerSanctionEOSInterface() const override;`
- L107 _public prototype_ `virtual IOnlinePlayerReportEOSPtr GetPlayerReportEOSInterface() const override;`
- L108 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L109 _public prototype_ `virtual void ReloadConfigs(const TSet<FString>& ConfigSections) override;`
- L111 _public function_ `virtual IOnlineGroupsPtr GetGroupsInterface() const override`
- L112 _public function_ `virtual IOnlinePartyPtr GetPartyInterface() const override`
- L113 _public function_ `virtual IOnlineTimePtr GetTimeInterface() const override`
- L114 _public function_ `virtual IOnlineEventsPtr GetEventsInterface() const override`
- L115 _public function_ `virtual IOnlineSharingPtr GetSharingInterface() const override`
- L116 _public function_ `virtual IOnlineMessagePtr GetMessageInterface() const override`
- L117 _public function_ `virtual IOnlineChatPtr GetChatInterface() const override`
- L118 _public function_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override`
- L119 _public function_ `virtual IOnlineTournamentPtr GetTournamentInterface() const override`
- L122 _public prototype_ `virtual bool Init() override;`
- L123 _public prototype_ `virtual bool Shutdown() override;`
- L124 _public prototype_ `virtual FString GetAppId() const override;`
- L127 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L130 _public prototype_ `FOnlineSubsystemEOS() = delete;` — Only the factory makes instances
- L131 _public prototype_ `explicit FOnlineSubsystemEOS(FName InInstanceName);`
- L133 _public member_ `FString ProductId;`
- L135 _public member_ `IEOSSDKManager* EOSSDKManager;`
- L138 _public member_ `IEOSPlatformHandlePtr EOSPlatformHandle;` — EOS handles
- L139 _public member_ `EOS_HAuth AuthHandle;`
- L140 _public member_ `EOS_HUI UIHandle;`
- L141 _public member_ `EOS_HFriends FriendsHandle;`
- L142 _public member_ `EOS_HUserInfo UserInfoHandle;`
- L143 _public member_ `EOS_HPresence PresenceHandle;`
- L144 _public member_ `EOS_HConnect ConnectHandle;`
- L145 _public member_ `EOS_HSessions SessionsHandle;`
- L146 _public member_ `EOS_HStats StatsHandle;`
- L147 _public member_ `EOS_HLeaderboards LeaderboardsHandle;`
- L148 _public member_ `EOS_HMetrics MetricsHandle;`
- L149 _public member_ `EOS_HAchievements AchievementsHandle;`
- L150 _public member_ `EOS_HEcom EcomHandle;`
- L151 _public member_ `EOS_HTitleStorage TitleStorageHandle;`
- L152 _public member_ `EOS_HPlayerDataStorage PlayerDataStorageHandle;`
- L153 _public member_ `EOS_HSanctions PlayerSanctionHandle;`
- L154 _public member_ `EOS_HReports PlayerReportHandle;`
- L157 _public member_ `FUserManagerEOSPtr UserManager;` — Manager that handles all user interfaces
- L159 _public member_ `FOnlineSessionEOSPtr SessionInterfacePtr;` — The session interface object
- L161 _public member_ `FOnlineStatsEOSPtr StatsInterfacePtr;` — Stats interface pointer
- L163 _public member_ `FOnlineLeaderboardsEOSPtr LeaderboardsInterfacePtr;` — Leaderboards interface pointer
- L164 _public member_ `FOnlineAchievementsEOSPtr AchievementsInterfacePtr;`
- L166 _public member_ `FOnlineStoreEOSPtr StoreInterfacePtr;` — EGS store interface pointer
- L168 _public member_ `FOnlineTitleFileEOSPtr TitleFileInterfacePtr;` — Title File interface pointer
- L170 _public member_ `FOnlineUserCloudEOSPtr UserCloudInterfacePtr;` — User Cloud interface pointer
- L172 _public member_ `FOnlinePlayerSanctionEOSPtr PlayerSanctionEOSPtr;` — Player sanction interface pointer
- L174 _public member_ `FOnlinePlayerReportEOSPtr PlayerReportInterfacePtr;` — Player Report interface pointer
- L176 _public member_ `FOnlineEntitlementsEOSPtr EntitlementsInterfacePtr;` — Entitlements interface pointer - only valid if bUseNewEcomFlow is true
- L178 _public member_ `FOnlinePurchaseEOSPtr PurchaseInterfacePtr;` — Purchase interface pointer - only valid if bUseNewEcomFlow is true
- L180 _public member_ `FOnlineStoreEOSV2Ptr StoreInterfaceV2Ptr;` — Store interface pointer used to retrieve EGS offers - only valid if bUseNewEcomFlow is true
- L182 _public member_ `TSharedPtr<FSocketSubsystemEOS, ESPMode::ThreadSafe> SocketSubsystem;`
- L184 _public member_ `static FPlatformEOSHelpersPtr EOSHelpersPtr;`
- L186 _public prototype_ `FEOSVoiceChatUser* GetEOSVoiceChatUserInterface(const FUniqueNetId& LocalUserId);`
- L187 _public prototype_ `void ReleaseVoiceChatUserInterface(const FUniqueNetId& LocalUserId);`
- L190 _private prototype_ `bool PlatformCreate();`
- L192 _private member_ `IVoiceChatPtr VoiceChatInterface;`
- L193 _private member_ `TUniqueNetIdMap<FOnlineSubsystemEOSVoiceChatUserWrapperRef> LocalVoiceChatUsers;`
- L202 _public function_ `explicit FOnlineSubsystemEOS(FName InInstanceName) : FOnlineSubsystemImpl(EOS_SUBSYSTEM, InInstanceName)`
- L209 _public function_ `virtual IOnlineSessionPtr GetSessionInterface() const override`
- L210 _public function_ `virtual IOnlineFriendsPtr GetFriendsInterface() const override`
- L213 _public function_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override`
- L214 _public function_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override`
- L215 _public function_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override`
- L216 _public function_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override`
- L217 _public function_ `virtual IOnlineVoicePtr GetVoiceInterface() const override`
- L218 _public function_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override`
- L220 _public function_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override`
- L221 _public function_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override`
- L222 _public function_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override`
- L223 _public function_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override`
- L226 _public function_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override`
- L228 _public function_ `virtual IOnlineUserPtr GetUserInterface() const override`
- L230 _public function_ `virtual IOnlinePresencePtr GetPresenceInterface() const override`
- L232 _public function_ `virtual IOnlineStatsPtr GetStatsInterface() const override`
- L235 _public function_ `virtual FText GetOnlineServiceName() const override`
- L237 _public function_ `virtual bool Init() override`
- L238 _public function_ `virtual bool Shutdown() override`
- L239 _public function_ `virtual FString GetAppId() const override`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_STATS_GROUP(TEXT("EOS"), STATGROUP_EOS, STATCAT_Advance`
- L19 _typedef_ `using IEOSPlatformHandlePtr = TSharedPtr<class IEOSPlatformHandle, ESPMode::ThreadSafe>;`
- L23 _typedef_ `using IVoiceChatPtr = TSharedPtr<class IVoiceChat, ESPMode::ThreadSafe>;`
- L24 _typedef_ `using FOnlineSubsystemEOSVoiceChatUserWrapperRef = TSharedRef<class FOnlineSubsystemEOSVoiceChatUserWrapper, ESPMode::ThreadSafe>;`
- L27 _typedef_ `typedef TSharedPtr<class FUserManagerEOS, ESPMode::ThreadSafe> FUserManagerEOSPtr;`
- L30 _typedef_ `typedef TSharedPtr<class FOnlineSessionEOS, ESPMode::ThreadSafe> FOnlineSessionEOSPtr;`
- L33 _typedef_ `typedef TSharedPtr<class FOnlineStatsEOS, ESPMode::ThreadSafe> FOnlineStatsEOSPtr;`
- L36 _typedef_ `typedef TSharedPtr<class FOnlineLeaderboardsEOS, ESPMode::ThreadSafe> FOnlineLeaderboardsEOSPtr;`
- L39 _typedef_ `typedef TSharedPtr<class FOnlineAchievementsEOS, ESPMode::ThreadSafe> FOnlineAchievementsEOSPtr;`
- L42 _typedef_ `typedef TSharedPtr<class FOnlineStoreEOS, ESPMode::ThreadSafe> FOnlineStoreEOSPtr;`
- L45 _typedef_ `typedef TSharedPtr<class FOnlineTitleFileEOS, ESPMode::ThreadSafe> FOnlineTitleFileEOSPtr;`
- L48 _typedef_ `typedef TSharedPtr<class FOnlineUserCloudEOS, ESPMode::ThreadSafe> FOnlineUserCloudEOSPtr;`
- L51 _typedef_ `typedef TSharedPtr<class FOnlinePlayerSanctionEOS, ESPMode::ThreadSafe> FOnlinePlayerSanctionEOSPtr;`
- L54 _typedef_ `typedef TSharedPtr<class FOnlinePlayerReportEOS, ESPMode::ThreadSafe> FOnlinePlayerReportEOSPtr;`
- L58 _typedef_ `typedef TSharedPtr<class FOnlineEntitlementsEOS, ESPMode::ThreadSafe> FOnlineEntitlementsEOSPtr;`
- L61 _typedef_ `typedef TSharedPtr<class FOnlinePurchaseEOS, ESPMode::ThreadSafe> FOnlinePurchaseEOSPtr;`
- L64 _typedef_ `typedef TSharedPtr<class FOnlineStoreEOSV2, ESPMode::ThreadSafe> FOnlineStoreEOSV2Ptr;`
- L66 _typedef_ `typedef TSharedPtr<FPlatformEOSHelpers, ESPMode::ThreadSafe> FPlatformEOSHelpersPtr;`
- L244 _typedef_ `typedef TSharedPtr<FOnlineSubsystemEOS, ESPMode::ThreadSafe> FOnlineSubsystemEOSPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineSubsystemEOSPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define INVALID_INDEX -1`
- L12 _macro_ `#define EOS_URL_PREFIX TEXT("EOS.")` — URL Prefix when using EOS socket connection
- L16 _macro_ `#define ONLINE_LOG_PREFIX TEXT("EOS: ")`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineSubsystemEOSTypes.h` (Private)


#### class `FUniqueNetIdEOS`  
`class FUniqueNetIdEOS : public IUniqueNetIdEOS`  
_L37-77_
- inherits: `IUniqueNetIdEOS`
- desc: Unique net id wrapper for a EOS account ids.
- L40 _public prototype_ `static const FUniqueNetIdEOS& Cast(const FUniqueNetId& NetId);`
- L43 _public prototype_ `static const FUniqueNetIdEOSRef& EmptyId();` — global static instance of invalid (zero) id
- L44 _public prototype_ `static const FUniqueNetIdEOSRef& DedicatedServerId();`
- L46 _public prototype_ `static FName GetTypeStatic();`
- L48 _public prototype_ `virtual FName GetType() const override;`
- L49 _public prototype_ `virtual const uint8* GetBytes() const override;`
- L50 _public prototype_ `virtual int32 GetSize() const override;`
- L52 _public prototype_ `virtual bool IsValid() const override;`
- L53 _public prototype_ `virtual uint32 GetTypeHash() const override;`
- L54 _public prototype_ `virtual FString ToString() const override;`
- L55 _public prototype_ `virtual FString ToDebugString() const override;`
- L56 _public prototype_ `virtual const EOS_EpicAccountId GetEpicAccountId() const override;`
- L57 _public prototype_ `virtual const EOS_ProductUserId GetProductUserId() const override;`
- L60 _private member_ `EOS_EpicAccountId EpicAccountId = nullptr;`
- L61 _private member_ `EOS_ProductUserId ProductUserId = nullptr;`
- L62 _private member_ `uint8 RawBytes[EOS_ID_BYTE_SIZE] = { 0 };`
- L67 _private function_ `template<typename... TArgs> static FUniqueNetIdEOSRef Create(TArgs&&... Args)`
- L72 _private prototype_ `FUniqueNetIdEOS() = default;`
- L74 _private prototype_ `bool IsDSValue() const;`
- L75 _private prototype_ `explicit FUniqueNetIdEOS(const uint8* Bytes, int32 Size);`
- L76 _private prototype_ `explicit FUniqueNetIdEOS(EOS_EpicAccountId InEpicAccountId, EOS_ProductUserId InProductUserId);`

#### class `FUniqueNetIdEOSRegistry`  
`class FUniqueNetIdEOSRegistry`  
_L79-108_
- L82 _public function_ `static FUniqueNetIdEOSRef FindOrAdd(const FString& NetIdStr)`
- L83 _public function_ `static FUniqueNetIdEOSRef FindOrAdd(const uint8* Bytes, int32 Size)`
- L84 _public function_ `static FUniqueNetIdEOSRef FindOrAdd(EOS_EpicAccountId EpicAccountId, EOS_ProductUserId ProductUserId)`
- L86 _public function_ `static FUniqueNetIdEOSPtr Find(EOS_EpicAccountId EpicAccountId)`
- L87 _public function_ `static FUniqueNetIdEOSPtr Find(EOS_ProductUserId ProductUserId)`
- L89 _public function_ `static FUniqueNetIdEOSRef FindChecked(EOS_EpicAccountId EpicAccountId)`
- L90 _public function_ `static FUniqueNetIdEOSRef FindChecked(EOS_ProductUserId ProductUserId)`
- L93 _private member_ `FRWLock Lock;`
- L94 _private member_ `TMap<EOS_EpicAccountId, FUniqueNetIdEOSRef> EasToNetId;`
- L95 _private member_ `TMap<EOS_ProductUserId, FUniqueNetIdEOSRef> PuidToNetId;`
- L97 _private prototype_ `static FUniqueNetIdEOSRegistry& Get();`
- L99 _private prototype_ `FUniqueNetIdEOSRef FindOrAddImpl(const FString& NetIdStr);`
- L100 _private prototype_ `FUniqueNetIdEOSRef FindOrAddImpl(const uint8* Bytes, int32 Size);`
- L101 _private prototype_ `FUniqueNetIdEOSRef FindOrAddImpl(EOS_EpicAccountId EpicAccountId, EOS_ProductUserId ProductUserId);`
- L103 _private prototype_ `FUniqueNetIdEOSPtr FindImpl(EOS_EpicAccountId EpicAccountId);`
- L104 _private prototype_ `FUniqueNetIdEOSPtr FindImpl(EOS_ProductUserId ProductUserId);`
- L106 _private prototype_ `FUniqueNetIdEOSRef FindCheckedImpl(EOS_EpicAccountId EpicAccountId);`
- L107 _private prototype_ `FUniqueNetIdEOSRef FindCheckedImpl(EOS_ProductUserId ProductUserId);`

#### class `IAttributeAccessInterface`  
`class IAttributeAccessInterface`  
_L129-149_
- desc: Used to update all types of FOnlineUser classes, irrespective of leaf most class type
- L132 _public function_ `virtual TMap<FString, FString> GetInternalAttributes() const`
- L137 _public function_ `virtual void UpdateInternalAttributes(const TMap<FString, FString>& InternalAttributes)`
- L141 _public function_ `virtual void SetInternalAttribute(const FString& AttrName, const FString& AttrValue)`
- L145 _public function_ `virtual FUniqueNetIdEOSPtr GetUniqueNetIdEOS() const`

#### class `TOnlineUserEOS`  
`template<class BaseClass, class AttributeAccessClass> class TOnlineUserEOS : public BaseClass , public AttributeAccessClass`  
_L163-239_
- inherits: `BaseClass,AttributeAccessClass`
- desc: Implementation of FOnlineUser that can be shared across multiple class hiearchies
- L170 _public function_ `TOnlineUserEOS(const FUniqueNetIdEOSRef& InNetIdRef, const FOnlineSubsystemEOS& InSubsystem) : UserIdRef(InNetIdRef) , EOSSubsystem(InSubsystem)`
- L176 _public function_ `TOnlineUserEOS(const FUniqueNetIdEOSRef& InNetIdRef, const TMap<FString, FString>& InUserAttributes, const FOnlineSubsystemEOS& InSubsystem) : UserIdRef(InNetIdRef) , UserAttributes(InUserAttributes) , EOSSubsystem(InSubsystem)`
- L183 _public prototype_ `virtual ~TOnlineUserEOS() = default;`
- L186 _public function_ `virtual FUniqueNetIdRef GetUserId() const override` — FOnlineUser
- L191 _public function_ `virtual FString GetRealName() const override`
- L196 _public function_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override`
- L201 _public function_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override`
- L212 _public function_ `virtual TMap<FString, FString> GetInternalAttributes() const override`
- L217 _public function_ `virtual void UpdateInternalAttributes(const TMap<FString, FString>& InternalAttributes) override`
- L222 _public function_ `virtual void SetInternalAttribute(const FString& AttrName, const FString& AttrValue)`
- L227 _public function_ `virtual FUniqueNetIdEOSPtr GetUniqueNetIdEOS() const`
- L234 _protected member_ `FUniqueNetIdEOSRef UserIdRef;` — User Id represented as a FUniqueNetId
- L236 _protected member_ `TMap<FString, FString> UserAttributes;` — Additional key/value pair data related to user attribution
- L238 _protected member_ `const FOnlineSubsystemEOS& EOSSubsystem;`

#### class `TUserOnlineAccountEOS`  
`template<class BaseClass> class TUserOnlineAccountEOS : public TOnlineUserEOS<BaseClass, IAttributeAccessInterface>`  
_L245-301_
- inherits: `TOnlineUserEOS<BaseClass,IAttributeAccessInterface>`
- desc: Implementation of FUserOnlineAccount methods that adds in the online user template to complete the interface
- L248 _private typedef_ `using Super = TOnlineUserEOS<BaseClass, IAttributeAccessInterface>;`
- L251 _public function_ `TUserOnlineAccountEOS(const FUniqueNetIdEOSRef& InNetIdRef, const FOnlineSubsystemEOS& InSubsystem) : Super(InNetIdRef, InSubsystem)`
- L257 _public function_ `virtual FString GetAccessToken() const override` — FUserOnlineAccount
- L270 _public function_ `virtual bool GetAuthAttribute(const FString& AttrName, FString& OutAttrValue) const override`
- L281 _public function_ `virtual bool SetUserAttribute(const FString& AttrName, const FString& AttrValue) override`
- L293 _public function_ `void SetAuthAttribute(const FString& AttrName, const FString& AttrValue)`
- L300 _protected member_ `TMap<FString, FString> AdditionalAuthData;` — Additional key/value pair data related to auth

#### class `TOnlineFriendEOS`  
`template<class BaseClass> class TOnlineFriendEOS : public TOnlineUserEOS<BaseClass, IAttributeAccessInterface>`  
_L309-355_
- inherits: `TOnlineUserEOS<BaseClass,IAttributeAccessInterface>`
- desc: Implementation of FOnlineFriend methods that adds in the online user template to complete the interface
- L313 _public function_ `TOnlineFriendEOS(const FUniqueNetIdEOSRef& InNetIdRef, const FOnlineSubsystemEOS& InSubsystem) : TOnlineUserEOS<BaseClass, IAttributeAccessInterface>(InNetIdRef, InSubsystem)`
- L318 _public function_ `TOnlineFriendEOS(const FUniqueNetIdEOSRef& InNetIdRef, const TMap<FString, FString>& InUserAttributes, const FOnlineSubsystemEOS& InSubsystem) : TOnlineUserEOS<BaseClass, IAttributeAccessInterface>(InNetIdRef, InUserAttributes, InSubsystem)`
- L327 _public function_ `virtual EInviteStatus::Type GetInviteStatus() const override` — @return the current invite status of a friend wrt to user that queried
- L335 _public function_ `virtual const FOnlineUserPresence& GetPresence() const override` — @return presence info for an online friend
- L341 _public function_ `void SetInviteStatus(EInviteStatus::Type InStatus)`
- L346 _public function_ `void SetPresence(FOnlineUserPresenceRef InPresence)`
- L353 _protected member_ `FOnlineUserPresence Presence;`
- L354 _protected member_ `EInviteStatus::Type InviteStatus;`

#### class `TEOSCallbackWithNested1`  
`class TEOSCallbackWithNested1 : public TEOSCallback<CallbackFuncType, CallbackType, OwningType>`  
_L384-422_
- inherits: `TEOSCallback<CallbackFuncType,CallbackType,OwningType>`
- L388 _public function_ `TEOSCallbackWithNested1(TWeakPtr<OwningType> InOwner) : TEOSCallback<CallbackFuncType, CallbackType, OwningType>(InOwner)`
- L392 _public prototype_ `virtual ~TEOSCallbackWithNested1() = default;`
- L395 _public function_ `Nested1CallbackFuncType GetNested1CallbackPtr()`
- L400 _public function_ `void SetNested1CallbackLambda(TFunction<Nested1ReturnType(const Nested1CallbackType*)> InLambda)`
- L406 _private member_ `TFunction<Nested1ReturnType(const Nested1CallbackType*)> Nested1CallbackLambda;`
- L408 _private function_ `static Nested1ReturnType EOS_CALL Nested1CallbackImpl(const Nested1CallbackType* Data)`

#### class `TEOSCallbackWithNested2`  
`class TEOSCallbackWithNested2 : public TEOSCallbackWithNested1<CallbackFuncType, CallbackType, OwningType, Nested1CallbackFuncType, Nested1CallbackType, Nested1ReturnType>`  
_L431-467_
- inherits: `TEOSCallbackWithNested1<CallbackFuncType,CallbackType,OwningType,Nested1CallbackFuncType,Nested1CallbackType,Nested1ReturnType>`
- L435 _public function_ `TEOSCallbackWithNested2(TWeakPtr<OwningType> InOwner) : TEOSCallbackWithNested1<CallbackFuncType, CallbackType, OwningType, Nested1CallbackFuncType, Nested1CallbackType, Nested1ReturnType>(InOwner)`
- L439 _public prototype_ `virtual ~TEOSCallbackWithNested2() = default;`
- L442 _public function_ `Nested2CallbackFuncType GetNested2CallbackPtr()`
- L447 _public function_ `void SetNested2CallbackLambda(TFunction<void(const Nested2CallbackType*)> InLambda)`
- L453 _private member_ `TFunction<void(const Nested2CallbackType*)> Nested2CallbackLambda;`
- L455 _private function_ `static void EOS_CALL Nested2CallbackImpl(const Nested2CallbackType* Data)`

#### class `TEOSCallbackWithNested1Param3`  
`class TEOSCallbackWithNested1Param3 : public TEOSCallback<CallbackFuncType, CallbackType, OwningType>`  
_L475-513_
- inherits: `TEOSCallback<CallbackFuncType,CallbackType,OwningType>`
- L479 _public function_ `TEOSCallbackWithNested1Param3(TWeakPtr<OwningType> InOwner) : TEOSCallback<CallbackFuncType, CallbackType, OwningType>(InOwner)`
- L483 _public prototype_ `virtual ~TEOSCallbackWithNested1Param3() = default;`
- L486 _public function_ `Nested1CallbackFuncType GetNested1CallbackPtr()`
- L491 _public function_ `void SetNested1CallbackLambda(TFunction<Nested1ReturnType(const Nested1CallbackType*, void*, uint32_t*)> InLambda)`
- L497 _private member_ `TFunction<Nested1ReturnType(const Nested1CallbackType*, void*, uint32_t*)> Nested1CallbackLambda;`
- L499 _private function_ `static Nested1ReturnType EOS_CALL Nested1CallbackImpl(const Nested1CallbackType* Data, void* OutDataBuffer, uint32_t* OutDataWritten)`

#### class `TEOSCallbackWithNested2ForNested1Param3`  
`class TEOSCallbackWithNested2ForNested1Param3 : public TEOSCallbackWithNested1Param3<CallbackFuncType, CallbackType, OwningType, Nested1CallbackFuncType, Nested1CallbackType, Nested1ReturnType>`  
_L522-558_
- inherits: `TEOSCallbackWithNested1Param3<CallbackFuncType,CallbackType,OwningType,Nested1CallbackFuncType,Nested1CallbackType,Nested1ReturnType>`
- L526 _public function_ `TEOSCallbackWithNested2ForNested1Param3(TWeakPtr<OwningType> InOwner) : TEOSCallbackWithNested1Param3<CallbackFuncType, CallbackType, OwningType, Nested1CallbackFuncType, Nested1CallbackType, Nested1ReturnType>(InOwner)`
- L530 _public prototype_ `virtual ~TEOSCallbackWithNested2ForNested1Param3() = default;`
- L533 _public function_ `Nested2CallbackFuncType GetNested2CallbackPtr()`
- L538 _public function_ `void SetNested2CallbackLambda(TFunction<void(const Nested2CallbackType*)> InLambda)`
- L544 _private member_ `TFunction<void(const Nested2CallbackType*)> Nested2CallbackLambda;`
- L546 _private function_ `static void EOS_CALL Nested2CallbackImpl(const Nested2CallbackType* Data)`

#### struct `FSessionDetailsEOS`  
`struct FSessionDetailsEOS : FNoncopyable`  
_L560-573_
- inherits: `FNoncopyable`
- L562 _public member_ `EOS_HSessionDetails SessionDetailsHandle;`
- L564 _public function_ `FSessionDetailsEOS(EOS_HSessionDetails InSessionDetailsHandle) : SessionDetailsHandle(InSessionDetailsHandle)`
- L569 _public function_ `virtual ~FSessionDetailsEOS()`

#### struct `FLobbyDetailsEOS`  
`struct FLobbyDetailsEOS : FNoncopyable`  
_L575-588_
- inherits: `FNoncopyable`
- L577 _public member_ `EOS_HLobbyDetails LobbyDetailsHandle;`
- L579 _public function_ `FLobbyDetailsEOS(EOS_HLobbyDetails InLobbyDetailsHandle) : LobbyDetailsHandle(InLobbyDetailsHandle)`
- L584 _public function_ `virtual ~FLobbyDetailsEOS()`

#### class `FOnlineSessionInfoEOS`  
`class FOnlineSessionInfoEOS : public FOnlineSessionInfo`  
_L593-661_
- inherits: `FOnlineSessionInfo`
- desc: Implementation of session information
- L598 _protected function_ `FOnlineSessionInfoEOS& operator=(const FOnlineSessionInfoEOS& Src)` — Hidden on purpose
- L607 _protected prototype_ `FOnlineSessionInfoEOS(const FOnlineSessionInfoEOS&) = default;`
- L609 _protected prototype_ `static FOnlineSessionInfoEOS Create(FUniqueNetIdStringRef UniqueNetId);`
- L610 _protected prototype_ `static FOnlineSessionInfoEOS Create(FUniqueNetIdStringRef UniqueNetId, const TSharedPtr<FSessionDetailsEOS>& SessionHandle);`
- L611 _protected prototype_ `static FOnlineSessionInfoEOS Create(FUniqueNetIdStringRef UniqueNetId, const TSharedPtr<FLobbyDetailsEOS>& LobbyHandle);`
- L616 _protected prototype_ `void InitLAN(FOnlineSubsystemEOS* Subsystem);` — Initialize LAN session
- L619 _protected member_ `TSharedPtr<class FInternetAddr> HostAddr = nullptr;` — The ip & port that the host is listening on (valid for LAN/GameServer)
- L621 _protected member_ `FUniqueNetIdStringRef SessionId = FUniqueNetIdString::EmptyId();` — Unique Id for this session
- L623 _protected member_ `TSharedPtr<FSessionDetailsEOS> SessionHandle = nullptr;` — EOS session handle. The same handle can be shared between a local session and a search result. The struct type will call the release API automatically upon destruction
- L625 _protected member_ `TSharedPtr<FLobbyDetailsEOS> LobbyHandle = nullptr;` — EOS lobby handle. The same handle can be shared between a local session and a search result. The struct type will call the release API automatically upon destruction
- L628 _public prototype_ `virtual ~FOnlineSessionInfoEOS() = default;`
- L630 _public function_ `bool operator==(const FOnlineSessionInfoEOS& Other) const`
- L634 _public function_ `virtual const uint8* GetBytes() const override`
- L638 _public function_ `virtual int32 GetSize() const override`
- L642 _public function_ `virtual bool IsValid() const override`
- L647 _public function_ `virtual FString ToString() const override`
- L651 _public function_ `virtual FString ToDebugString() const override`
- L657 _public function_ `virtual const FUniqueNetId& GetSessionId() const override`

#### Free symbols / members of external scopes

- L22 _macro_ `#define EOS_OSS_BUCKET_ID_STRING_LENGTH 60`
- L23 _macro_ `#define EOS_OSS_STRING_BUFFER_LENGTH 256 + 1 // 256 plus null terminator`
- L27 _macro_ `#define EOS_ID_SEPARATOR TEXT("|")`
- L28 _macro_ `#define ID_HALF_BYTE_SIZE 16`
- L29 _macro_ `#define EOS_ID_BYTE_SIZE (ID_HALF_BYTE_SIZE * 2)`
- L31 _typedef_ `typedef TSharedPtr<const class FUniqueNetIdEOS> FUniqueNetIdEOSPtr;`
- L32 _typedef_ `typedef TSharedRef<const class FUniqueNetIdEOS> FUniqueNetIdEOSRef;`
- L111 _macro_ `#define AUTH_ATTR_REFRESH_TOKEN TEXT("refresh_token")`
- L114 _macro_ `#define AUTH_ATTR_ID_TOKEN TEXT("id_token")`
- L117 _macro_ `#define AUTH_ATTR_AUTHORIZATION_CODE TEXT("authorization_code")`
- L120 _macro_ `#define USER_ATTR_DISPLAY_NAME TEXT("display_name")`
- L121 _macro_ `#define USER_ATTR_COUNTRY TEXT("country")`
- L122 _macro_ `#define USER_ATTR_LANG TEXT("language")`
- L124 _macro_ `#define SESSION_ATTR_SERVERPORT TEXT("port")`
- L151 _typedef_ `typedef TSharedPtr<IAttributeAccessInterface> IAttributeAccessInterfacePtr;`
- L152 _typedef_ `typedef TSharedRef<IAttributeAccessInterface> IAttributeAccessInterfaceRef;`
- L154 _namespace_ `namespace OnlineSubsystemEOSTypesPrivate`
- L156 _prototype_ `FString GetBestDisplayName(const FOnlineSubsystemEOS& EOSSubsystem, const EOS_EpicAccountId TargetUserId, const FStringView Platform);` (scope `OnlineSubsystemEOSTypesPrivate`)
- L303 _typedef_ `typedef TSharedRef<FOnlineUserPresence> FOnlineUserPresenceRef;`
- L357 _namespace_ `namespace OSSInternalCallback`
- L361 _function_ `template <typename DelegateType, typename OwnerType, typename... CallbackArgs> [[nodiscard]] DelegateType Create(const TSharedPtr<OwnerType, ESPMode::ThreadSafe>& InOwner, const TFunction<void(CallbackArgs...)>& InUserCallback)` (scope `OSSInternalCallback`) — Create a callback for a non-SDK function that is tied to the lifetime of an arbitrary shared pointer.
- L365 _function_ `[WeakOwner = TWeakPtr<OwnerType, ESPMode::ThreadSafe>(InOwner), InUserCallback](CallbackArgs... Payload)` (scope `OSSInternalCallback::Create`)

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineTitleFileEOS.h` (Private)


#### struct `FEOSTitleFile`  
`struct FEOSTitleFile`  
_L15-30_
- L17 _public member_ `TArray<uint8> Contents;`
- L18 _public member_ `size_t ContentSize;`
- L19 _public member_ `size_t ContentIndex;`
- L20 _public member_ `bool bIsLoaded;`
- L21 _public member_ `bool bInProgress;`
- L22 _public member_ `FString Filename;`
- L23 _public member_ `EOS_HTitleStorageFileTransferRequest FileTransferRequest;` — TODO: Mark.Fitt this does not auto release
- L25 _public function_ `FEOSTitleFile() : ContentSize(0), ContentIndex(0), bIsLoaded(false), bInProgress(false)`
- L29 _public prototype_ `void Unload();`

#### class `FOnlineTitleFileEOS`  
`class FOnlineTitleFileEOS : public IOnlineTitleFile, public TSharedFromThis<FOnlineTitleFileEOS, ESPMode::ThreadSafe>`  
_L34-66_
- inherits: `IOnlineTitleFile,TSharedFromThis<FOnlineTitleFileEOS,ESPMode::ThreadSafe>`
- L38 _public prototype_ `FOnlineTitleFileEOS() = delete;`
- L39 _public prototype_ `virtual ~FOnlineTitleFileEOS() = default;`
- L42 _public prototype_ `virtual bool GetFileContents(const FString& FileName, TArray<uint8>& FileContents) override;`
- L43 _public prototype_ `virtual bool ClearFiles() override;`
- L44 _public prototype_ `virtual bool ClearFile(const FString& FileName) override;`
- L45 _public prototype_ `virtual void DeleteCachedFiles(bool bSkipEnumerated) override;`
- L46 _public prototype_ `virtual bool EnumerateFiles(const FPagedQuery& Page = FPagedQuery()) override;`
- L47 _public prototype_ `virtual void GetFileList(TArray<FCloudFileHeader>& Files) override;`
- L48 _public prototype_ `virtual bool ReadFile(const FString& FileName) override;`
- L51 _public function_ `FOnlineTitleFileEOS(FOnlineSubsystemEOS* InSubsystem) : EOSSubsystem(InSubsystem)`
- L56 _public prototype_ `bool HandleTitleFileExec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L59 _protected member_ `FOnlineSubsystemEOS* EOSSubsystem;`
- L63 _private member_ `TArray<FCloudFileHeader> QueryFileSet;` — Results of the last file enumeration
- L65 _private member_ `FTitleFileCollection FileSet;` — The list of available files, indexed by filename that have been or are loaded

#### Free symbols / members of external scopes

- L32 _typedef_ `using FTitleFileCollection = TMap<FString, FEOSTitleFile>;`
- L68 _typedef_ `typedef TSharedPtr<FOnlineTitleFileEOS, ESPMode::ThreadSafe> FOnlineTitleFileEOSPtr;`
- L69 _typedef_ `typedef TWeakPtr<FOnlineTitleFileEOS, ESPMode::ThreadSafe> FOnlineTitleFileEOSWeakPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/OnlineUserCloudEOS.h` (Private)


#### struct `FEOSUserCloudFile`  
`struct FEOSUserCloudFile`  
_L15-30_
- L17 _public member_ `TArray<uint8> Contents;`
- L18 _public member_ `size_t ContentSize;`
- L19 _public member_ `size_t ContentIndex;`
- L20 _public member_ `bool bIsLoaded;`
- L21 _public member_ `bool bInProgress;`
- L22 _public member_ `FString Filename;`
- L23 _public member_ `EOS_HPlayerDataStorageFileTransferRequest FileTransferRequest;`
- L25 _public function_ `FEOSUserCloudFile() : ContentSize(0), ContentIndex(0), bIsLoaded(false), bInProgress(false)`
- L29 _public prototype_ `void Unload();`

#### class `FOnlineUserCloudEOS`  
`class FOnlineUserCloudEOS : public IOnlineUserCloud, public TSharedFromThis<FOnlineUserCloudEOS, ESPMode::ThreadSafe>`  
_L34-72_
- inherits: `IOnlineUserCloud,TSharedFromThis<FOnlineUserCloudEOS,ESPMode::ThreadSafe>`
- L38 _public prototype_ `FOnlineUserCloudEOS() = delete;`
- L39 _public prototype_ `virtual ~FOnlineUserCloudEOS() = default;`
- L42 _public prototype_ `virtual bool GetFileContents(const FUniqueNetId& UserId, const FString& FileName, TArray<uint8>& FileContents) override;`
- L43 _public prototype_ `virtual bool ClearFiles(const FUniqueNetId& UserId) override;`
- L44 _public prototype_ `virtual bool ClearFile(const FUniqueNetId& UserId, const FString& FileName) override;`
- L45 _public prototype_ `virtual void EnumerateUserFiles(const FUniqueNetId& UserId) override;`
- L46 _public prototype_ `virtual void GetUserFileList(const FUniqueNetId& UserId, TArray<FCloudFileHeader>& UserFiles) override;`
- L47 _public prototype_ `virtual bool ReadUserFile(const FUniqueNetId& UserId, const FString& FileName) override;`
- L48 _public prototype_ `virtual bool WriteUserFile(const FUniqueNetId& UserId, const FString& FileName, TArray<uint8>& FileContents, bool bCompressBeforeUpload = false) override;`
- L49 _public prototype_ `virtual void CancelWriteUserFile(const FUniqueNetId& UserId, const FString& FileName) override;`
- L50 _public prototype_ `virtual bool DeleteUserFile(const FUniqueNetId& UserId, const FString& FileName, bool bShouldCloudDelete, bool bShouldLocallyDelete) override;`
- L51 _public prototype_ `virtual bool RequestUsageInfo(const FUniqueNetId& UserId) override;`
- L52 _public prototype_ `virtual void DumpCloudState(const FUniqueNetId& UserId) override;`
- L53 _public prototype_ `virtual void DumpCloudFileState(const FUniqueNetId& UserId, const FString& FileName) override;`
- L56 _public function_ `FOnlineUserCloudEOS(FOnlineSubsystemEOS* InSubsystem) : EOSSubsystem(InSubsystem)`
- L61 _public prototype_ `bool HandleUserCloudExec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L64 _protected member_ `FOnlineSubsystemEOS* EOSSubsystem;`
- L68 _private member_ `TUniqueNetIdMap<TArray<FCloudFileHeader>> QueryFileSetsPerUser;` — Results of the last file enumeration per user
- L71 _private member_ `TUniqueNetIdMap<FUserCloudFileCollection> FileSetsPerUser;` — The lists of available files per user, indexed by filename that have been or are loaded

#### Free symbols / members of external scopes

- L32 _typedef_ `typedef TMap<FString, FEOSUserCloudFile> FUserCloudFileCollection;`
- L74 _typedef_ `typedef TSharedPtr<FOnlineUserCloudEOS, ESPMode::ThreadSafe> FOnlineUserCloudEOSPtr;`
- L75 _typedef_ `typedef TWeakPtr<FOnlineUserCloudEOS, ESPMode::ThreadSafe> FOnlineUserCloudEOSWeakPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/SocketSubsystemEOSUtils_OnlineSubsystemEOS.h` (Private)


#### class `FSocketSubsystemEOSUtils_OnlineSubsystemEOS`  
`class FSocketSubsystemEOSUtils_OnlineSubsystemEOS : public ISocketSubsystemEOSUtils`  
_L9-24_
- inherits: `ISocketSubsystemEOSUtils`
- L12 _public prototype_ `FSocketSubsystemEOSUtils_OnlineSubsystemEOS(FOnlineSubsystemEOS& InSubsystemEOS);`
- L16 _public prototype_ `virtual EOS_ProductUserId GetLocalUserId() override;`
- L18 _public prototype_ `virtual FString GetSessionId() override;`
- L19 _public prototype_ `virtual FName GetSubsystemInstanceName() override;`
- L20 _public prototype_ `virtual bool IsLoggedIn() override;`
- L23 _private member_ `FOnlineSubsystemEOS& SubsystemEOS;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/UserManagerEOS.h` (Private)


#### class `FOnlineUserEOS`  
`class FOnlineUserEOS : public TOnlineUserEOS<FOnlineUser, IAttributeAccessInterface>`  
_L29-38_
- inherits: `TOnlineUserEOS<FOnlineUser,IAttributeAccessInterface>`
- desc: Concrete online user class built from the reusable templates
- L33 _public function_ `FOnlineUserEOS(FUniqueNetIdEOSRef InUserId, const FOnlineSubsystemEOS& InSubsystem) : TOnlineUserEOS<FOnlineUser, IAttributeAccessInterface>(InUserId, InSubsystem)`
- L37 _public prototype_ `virtual ~FOnlineUserEOS() = default;`

#### class `FUserOnlineAccountEOS`  
`class FUserOnlineAccountEOS : public TUserOnlineAccountEOS<FUserOnlineAccount>`  
_L46-55_
- inherits: `TUserOnlineAccountEOS<FUserOnlineAccount>`
- desc: Info associated with an user account generated by this online service
- L50 _public function_ `FUserOnlineAccountEOS(FUniqueNetIdEOSRef InUserId, FOnlineSubsystemEOS& InSubsystem) : TUserOnlineAccountEOS<FUserOnlineAccount>(InUserId, InSubsystem)`
- L54 _public prototype_ `virtual ~FUserOnlineAccountEOS() = default;`

#### class `FOnlineFriendEOS`  
`class FOnlineFriendEOS : public TOnlineFriendEOS<FOnlineFriend>`  
_L63-78_
- inherits: `TOnlineFriendEOS<FOnlineFriend>`
- desc: Concrete friend class built from the reusable templates
- L67 _public function_ `FOnlineFriendEOS(FUniqueNetIdEOSRef InUserId, const FOnlineSubsystemEOS& InSubsystem) : TOnlineFriendEOS<FOnlineFriend>(InUserId, InSubsystem)`
- L72 _public function_ `FOnlineFriendEOS(FUniqueNetIdEOSRef InUserId, const TMap<FString, FString>& InUserAttributes, const FOnlineSubsystemEOS& InSubsystem) : TOnlineFriendEOS<FOnlineFriend>(InUserId, InUserAttributes, InSubsystem)`
- L77 _public prototype_ `virtual ~FOnlineFriendEOS() = default;`

#### class `TOnlinePlayerList`  
`template<class ListClass, class ListClassReturnType> class TOnlinePlayerList`  
_L84-143_
- L87 _private member_ `int32 LocalUserNum;` — The user that owns this list
- L89 _private member_ `FUniqueNetIdEOSRef OwningNetId;` — The net id that owns this list
- L91 _private member_ `TArray<ListClass> ListEntries;` — The array of list class entries
- L93 _private member_ `TUniqueNetIdMap<ListClass> UniqueIdToListEntryMap;` — Indexed by unique id for fast look up
- L96 _public function_ `TOnlinePlayerList(int32 InLocalUserNum, FUniqueNetIdEOSRef InOwningNetId) : LocalUserNum(InLocalUserNum) , OwningNetId(InOwningNetId)`
- L102 _public function_ `const TArray<ListClass>& GetList()`
- L107 _public function_ `void Add(const FUniqueNetIdRef& InNetId, ListClass InListEntry)`
- L113 _public function_ `void Remove(const FUniqueNetIdRef& InNetId, ListClass InListEntry)`
- L119 _public function_ `void Empty(int32 Slack = 0)`
- L125 _public function_ `ListClassReturnType GetByIndex(int32 Index)`
- L134 _public function_ `ListClassReturnType GetByNetId(const FUniqueNetIdRef& NetId)`

#### class `FFriendsListEOS`  
`class FFriendsListEOS : public TOnlinePlayerList<FOnlineFriendEOSRef, FOnlineFriendEOSPtr>`  
_L145-154_
- inherits: `TOnlinePlayerList<FOnlineFriendEOSRef,FOnlineFriendEOSPtr>`
- L149 _public function_ `FFriendsListEOS(int32 InLocalUserNum, FUniqueNetIdEOSRef InOwningNetId) : TOnlinePlayerList<FOnlineFriendEOSRef, FOnlineFriendEOSPtr>(InLocalUserNum, InOwningNetId)`
- L153 _public prototype_ `virtual ~FFriendsListEOS() = default;`

#### struct `FNotificationIdCallbackPair`  
`struct FNotificationIdCallbackPair`  
_L158-173_
- L160 _public member_ `EOS_NotificationId NotificationId;`
- L161 _public member_ `FCallbackBase* Callback;`
- L163 _public function_ `FNotificationIdCallbackPair() : NotificationId(EOS_INVALID_NOTIFICATIONID) , Callback(nullptr)`
- L169 _public function_ `virtual ~FNotificationIdCallbackPair()`

#### struct `ReadUserListInfo`  
`struct ReadUserListInfo`  
_L176-191_
- desc: Cache for the info passed on to ReadFriendsList, kept while user info queries complete
- L178 _public member_ `const int32 LocalUserNum;`
- L179 _public member_ `const FString ListName;`
- L180 _public member_ `const FOnReadFriendsListComplete Delegate;`
- L182 _public function_ `ReadUserListInfo(int32 InLocalUserNum, const FString& InListName, FOnReadFriendsListComplete InDelegate) : LocalUserNum(InLocalUserNum), ListName(InListName), Delegate(MoveTemp(InDelegate))`
- L187 _public function_ `void ExecuteDelegateIfBound(bool bWasSuccessful, const FString& ErrorStr) const`

#### struct `FLocalUserEOS`  
`struct FLocalUserEOS`  
_L194-241_
- desc: Created when a new local user starts a login process, keeps the state for the login session and ongoing operations, and gets destroyed when login fails or the user logs out
- L197 _public member_ `FUniqueNetIdEOSPtr UniqueNetId;` — UniqueNetId for the local user, set after successful authentication
- L200 _public member_ `FUserOnlineAccountEOSPtr UserOnlineAccount;` — Online Account information for the local user
- L203 _public member_ `FFriendsListEOSPtr FriendsList;` — Friends information for the local user. Populated by ReadFriendsList
- L206 _public member_ `TArray<EOS_EpicAccountId> OngoingQueryUserInfoAccounts;` — Epic ids for users with ongoing queries
- L225 _public member_ `} OngoingQueryUserInfoResults;`
- L228 _public member_ `TArray<FString> OngoingPlayerQueryExternalMappings;` — External ids still in process of resolution for local user
- L231 _public member_ `TArray<ReadUserListInfo> CachedReadUserListInfo;` — This keeps track of all delegates passed on to calls to ReadFriendsList, so they will all be executed once the process finishes
- L234 _public member_ `TSharedPtr<FOnlineAccountCredentials> LastLoginCredentials_Legacy;` — Last Login Credentials used for a login attempt
- L237 _public member_ `TOptional<FString> UserProvidedConnectAuthToken;` — If set, Connect Login will be re-attempted with it. If this attempt fails, a new token will need to be provided
- L240 _public member_ `bool bIsLoggingOut = false;` — Track if the player is in the process of logging out to avoid calling EOS SDK logout APIs multiple times

#### struct `FLocalUserEOS::FReadUserInfoResults`  
`struct FReadUserInfoResults`  
_L208-225_
- L211 _public member_ `TArray<FUniqueNetIdEOSRef> ProcessedIds;` — UniqueNetIds gathered as a result of successful queries
- L214 _public member_ `bool bAllWasSuccessful = true;` — Whether all queries for this given operation were successful
- L217 _public member_ `FString AllErrorStr;` — Combined error str for all operations
- L219 _public function_ `void Reset()`

#### class `FUserManagerEOS`  
`class FUserManagerEOS : public IOnlineIdentity , public IOnlineExternalUI , public IOnlineFriends , public IOnlinePresence , public IOnlineUser , public TSharedFromThis<FUserManagerEOS, ESPMode::ThreadSafe>`  
_L248-473_
- inherits: `IOnlineIdentity,IOnlineExternalUI,IOnlineFriends,IOnlinePresence,IOnlineUser,TSharedFromThis<FUserManagerEOS,ESPMode::ThreadSafe>`
- desc: EOS service implementation of the online identity, friends, and user info interfaces Centrally managed since they share common data
- L262 _public prototype_ `FUserManagerEOS(FOnlineSubsystemEOS* InSubsystem);` — Constructor @param InSubsystem online subsystem being used
- L267 _public prototype_ `virtual ~FUserManagerEOS();` — Destructor
- L269 _public prototype_ `void Init();`
- L270 _public prototype_ `void Shutdown();`
- L273 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;` — IOnlineIdentity Interface
- L274 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L275 _public prototype_ `virtual bool AutoLogin(int32 LocalUserNum) override;`
- L276 _public prototype_ `virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const override;`
- L277 _public prototype_ `virtual TArray<TSharedPtr<FUserOnlineAccount>> GetAllUserAccounts() const override;`
- L278 _public prototype_ `virtual FUniqueNetIdPtr GetUniquePlayerId(int32 LocalUserNum) const override;`
- L279 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(uint8* Bytes, int32 Size) override;`
- L280 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(const FString& Str) override;`
- L281 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;`
- L282 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const override;`
- L283 _public prototype_ `virtual FString GetPlayerNickname(int32 LocalUserNum) const override;`
- L284 _public prototype_ `virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const override;`
- L285 _public prototype_ `virtual FString GetAuthToken(int32 LocalUserNum) const override;`
- L286 _public prototype_ `virtual void GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI = EShowPrivilegeResolveUI::Default) override;`
- L287 _public prototype_ `virtual FString GetAuthType() const override;`
- L288 _public prototype_ `virtual void RevokeAuthToken(const FUniqueNetId& LocalUserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate) override;`
- L289 _public prototype_ `virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const override;`
- L290 _public prototype_ `virtual void GetLinkedAccountAuthToken(int32 LocalUserNum, const FString& TokenType, const FOnGetLinkedAccountAuthTokenCompleteDelegate& Delegate) const override;`
- L293 _public prototype_ `ELoginStatus::Type GetLoginStatus(const FUniqueNetIdEOS& UserId) const;`
- L296 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI Interface
- L297 _public prototype_ `virtual bool ShowAccountCreationUI(const int ControllerIndex, const FOnAccountCreationUIClosedDelegate& Delegate = FOnAccountCreationUIClosedDelegate()) override;`
- L298 _public prototype_ `virtual bool ShowFriendsUI(int32 LocalUserNum) override;`
- L299 _public prototype_ `virtual bool ShowInviteUI(int32 LocalUserNum, FName SessionName = NAME_GameSession) override;`
- L300 _public prototype_ `virtual bool ShowAchievementsUI(int32 LocalUserNum) override;`
- L301 _public prototype_ `virtual bool ShowLeaderboardUI(const FString& LeaderboardName) override;`
- L302 _public prototype_ `virtual bool ShowWebURL(const FString& Url, const FShowWebUrlParams& ShowParams, const FOnShowWebUrlClosedDelegate& Delegate = FOnShowWebUrlClosedDelegate()) override;`
- L303 _public prototype_ `virtual bool CloseWebURL() override;`
- L304 _public prototype_ `virtual bool ShowProfileUI(const FUniqueNetId& Requestor, const FUniqueNetId& Requestee, const FOnProfileUIClosedDelegate& Delegate = FOnProfileUIClosedDelegate()) override;`
- L305 _public prototype_ `virtual bool ShowAccountUpgradeUI(const FUniqueNetId& UniqueId) override;`
- L306 _public prototype_ `virtual bool ShowStoreUI(int32 LocalUserNum, const FShowStoreParams& ShowParams, const FOnShowStoreUIClosedDelegate& Delegate = FOnShowStoreUIClosedDelegate()) override;`
- L307 _public prototype_ `virtual bool ShowSendMessageUI(int32 LocalUserNum, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate()) override;`
- L311 _public prototype_ `virtual bool ReadFriendsList(int32 LocalUserNum, const FString& ListName, const FOnReadFriendsListComplete& Delegate = FOnReadFriendsListComplete()) override;` — IOnlineFriends Interface
- L312 _public prototype_ `virtual bool DeleteFriendsList(int32 LocalUserNum, const FString& ListName, const FOnDeleteFriendsListComplete& Delegate = FOnDeleteFriendsListComplete()) override;`
- L313 _public prototype_ `virtual bool SendInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnSendInviteComplete& Delegate = FOnSendInviteComplete()) override;`
- L314 _public prototype_ `virtual bool AcceptInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnAcceptInviteComplete& Delegate = FOnAcceptInviteComplete()) override;`
- L315 _public prototype_ `virtual bool RejectInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L316 _public prototype_ `virtual bool DeleteFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L317 _public prototype_ `virtual bool GetFriendsList(int32 LocalUserNum, const FString& ListName, TArray< TSharedRef<FOnlineFriend> >& OutFriends) override;`
- L318 _public prototype_ `virtual TSharedPtr<FOnlineFriend> GetFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L319 _public prototype_ `virtual bool IsFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L320 _public prototype_ `virtual bool QueryRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace) override;`
- L321 _public prototype_ `virtual bool GetRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace, TArray< TSharedRef<FOnlineRecentPlayer> >& OutRecentPlayers) override;`
- L322 _public prototype_ `virtual bool BlockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L323 _public prototype_ `virtual bool UnblockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L324 _public prototype_ `virtual bool QueryBlockedPlayers(const FUniqueNetId& UserId) override;`
- L325 _public prototype_ `virtual bool GetBlockedPlayers(const FUniqueNetId& UserId, TArray< TSharedRef<FOnlineBlockedPlayer> >& OutBlockedPlayers) override;`
- L326 _public prototype_ `virtual void DumpBlockedPlayers() const override;`
- L327 _public prototype_ `virtual void SetFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FString& Alias, const FOnSetFriendAliasComplete& Delegate = FOnSetFriendAliasComplete()) override;`
- L328 _public prototype_ `virtual void DeleteFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnDeleteFriendAliasComplete& Delegate = FOnDeleteFriendAliasComplete()) override;`
- L329 _public prototype_ `virtual void DumpRecentPlayers() const override;`
- L332 _public prototype_ `bool HandleFriendsExec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L335 _public prototype_ `virtual void SetPresence(const FUniqueNetId& User, const FOnlineUserPresenceStatus& Status, const FOnPresenceTaskCompleteDelegate& Delegate = FOnPresenceTaskCompleteDelegate()) override;` — IOnlinePresence Interface
- L336 _public prototype_ `virtual void QueryPresence(const FUniqueNetId& User, const FOnPresenceTaskCompleteDelegate& Delegate = FOnPresenceTaskCompleteDelegate()) override;`
- L337 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedPresence(const FUniqueNetId& User, TSharedPtr<FOnlineUserPresence>& OutPresence) override;`
- L338 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedPresenceForApp(const FUniqueNetId& LocalUserId, const FUniqueNetId& User, const FString& AppId, TSharedPtr<FOnlineUserPresence>& OutPresence) override;`
- L342 _public prototype_ `virtual bool QueryUserInfo(int32 LocalUserNum, const TArray<FUniqueNetIdRef>& UserIds) override;` — IOnlineUser Interface
- L343 _public prototype_ `virtual bool GetAllUserInfo(int32 LocalUserNum, TArray<TSharedRef<class FOnlineUser>>& OutUsers) override;`
- L344 _public prototype_ `virtual TSharedPtr<FOnlineUser> GetUserInfo(int32 LocalUserNum, const class FUniqueNetId& UserId) override;`
- L345 _public prototype_ `virtual bool QueryUserIdMapping(const FUniqueNetId& UserId, const FString& DisplayNameOrEmail, const FOnQueryUserMappingComplete& Delegate = FOnQueryUserMappingComplete()) override;`
- L346 _public prototype_ `virtual bool QueryExternalIdMappings(const FUniqueNetId& UserId, const FExternalIdQueryOptions& QueryOptions, const TArray<FString>& ExternalIds, const FOnQueryExternalIdMappingsComplete& Delegate = FOnQueryExternalIdMappingsComplete()) override;`
- L347 _public prototype_ `virtual void GetExternalIdMappings(const FExternalIdQueryOptions& QueryOptions, const TArray<FString>& ExternalIds, TArray<FUniqueNetIdPtr>& OutIds) override;`
- L348 _public prototype_ `virtual FUniqueNetIdPtr GetExternalIdMapping(const FExternalIdQueryOptions& QueryOptions, const FString& ExternalId) override;`
- L351 _public prototype_ `const FUniqueNetIdEOSPtr GetLocalUniqueNetIdEOS(int32 LocalUserNum) const;`
- L352 _public prototype_ `EOS_EpicAccountId GetLocalEpicAccountId(int32 LocalUserNum) const;`
- L353 _public prototype_ `EOS_ProductUserId GetLocalProductUserId(int32 LocalUserNum) const;`
- L355 _public prototype_ `int32 GetLocalUserNumFromUniqueNetId(const FUniqueNetId& NetId) const;`
- L356 _public prototype_ `int32 GetLocalUserNumFromEpicAccountId(const EOS_EpicAccountId& EpicAccountId) const;`
- L357 _public prototype_ `int32 GetLocalUserNumFromProductUserId(const EOS_ProductUserId& ProductUserId) const;`
- L359 _public prototype_ `const FUniqueNetIdEOSPtr GetLocalUniqueNetIdEOS(const EOS_EpicAccountId& EpicAccountId) const;`
- L360 _public prototype_ `const FUniqueNetIdEOSPtr GetLocalUniqueNetIdEOS(const EOS_ProductUserId& ProductUserId) const;`
- L362 _public prototype_ `bool IsLocalUser(const FUniqueNetId& NetId) const;`
- L363 _public prototype_ `bool IsLocalUser(const EOS_EpicAccountId& EpicAccountId) const;`
- L364 _public prototype_ `bool IsLocalUser(const EOS_ProductUserId& ProductUserId) const;`
- L366 _public typedef_ `using FResolveUniqueNetIdsCallback = TFunction<void(TMap<EOS_ProductUserId, FUniqueNetIdEOSRef> ResolvedUniqueNetIds, const FOnlineError& Error)>;`
- L367 _public typedef_ `using FResolveEpicAccountIdsCallback = TFunction<void(bool bWasSuccessful, TMap<EOS_EpicAccountId, FUniqueNetIdEOSRef> ResolvedUniqueNetIds, const FOnlineError& Error)>;`
- L368 _public typedef_ `using FResolveUniqueNetIdCallback = TFunction<void(FUniqueNetIdEOSRef ResolvedUniqueNetId, const FOnlineError& Error)>;`
- L370 _public prototype_ `bool GetEpicAccountIdFromProductUserId(int32 LocalUserNum, const EOS_ProductUserId& ProductUserId, EOS_EpicAccountId& OutEpicAccountId, FOnlineError& Error) const;`
- L371 _public prototype_ `void ResolveUniqueNetId(int32 LocalUserNum, const EOS_ProductUserId& ProductUserId, const FResolveUniqueNetIdCallback& Callback) const;`
- L372 _public prototype_ `void ResolveUniqueNetIds(int32 LocalUserNum, const TArray<EOS_ProductUserId>& ProductUserIds, const FResolveUniqueNetIdsCallback& Callback) const;`
- L373 _public prototype_ `void ResolveUniqueNetId(int32 LocalUserNum, const EOS_EpicAccountId& EpicAccountId, const FResolveUniqueNetIdCallback& Callback);`
- L374 _public prototype_ `void ResolveUniqueNetIds(int32 LocalUserNum, const TArray<EOS_EpicAccountId>& EpicAccountId, const FResolveEpicAccountIdsCallback& Callback);`
- L376 _public prototype_ `FOnlineUserPtr GetLocalOnlineUser(int32 LocalUserNum) const;`
- L377 _public prototype_ `FOnlineUserPtr GetOnlineUser(EOS_ProductUserId UserId) const;`
- L378 _public prototype_ `FOnlineUserPtr GetOnlineUser(EOS_EpicAccountId AccountId) const;`
- L383 _public prototype_ `FUserManagerEOS() = delete;` — Should use the initialization constructor instead
- L385 _public prototype_ `bool ConnectLoginEAS(int32 LocalUserNum, EOS_EpicAccountId AccountId);`
- L386 _public prototype_ `void LoginViaPersistentAuth(int32 LocalUserNum);`
- L387 _public prototype_ `void LoginViaExternalAuth(int32 LocalUserNum);`
- L388 _public prototype_ `void CreateConnectedLogin(int32 LocalUserNum, EOS_EpicAccountId AccountId, EOS_ContinuanceToken Token);`
- L389 _public prototype_ `void LinkEAS(int32 LocalUserNum, EOS_ContinuanceToken Token);`
- L390 _public prototype_ `void AutoRefreshConnectLogin(const EOS_Connect_AuthExpirationCallbackInfo* Data);`
- L391 _public prototype_ `bool ConnectLoginNoEAS(int32 LocalUserNum);`
- L393 _public prototype_ `void FullLoginCallback(int32 LocalUserNum, EOS_EpicAccountId AccountId, EOS_ProductUserId UserId);`
- L394 _public prototype_ `void FriendStatusChanged(const EOS_Friends_OnFriendsUpdateInfo* Data);`
- L395 _public prototype_ `void FriendStatusChangedImpl(EOS_EpicAccountId LocalUserId, EOS_EpicAccountId TargetUserId, EOS_EFriendsStatus PreviousStatus, EOS_EFriendsStatus CurrentStatus);`
- L396 _public prototype_ `void AuthLoginStatusChanged(const EOS_Auth_LoginStatusChangedCallbackInfo* Data);`
- L397 _public prototype_ `void ConnectLoginStatusChanged(const EOS_Connect_LoginStatusChangedCallbackInfo* Data);`
- L398 _public prototype_ `void PresenceChanged(const EOS_Presence_PresenceChangedCallbackInfo* Data);`
- L400 _public function_ `int32 GetDefaultLocalUser() const`
- L402 _public prototype_ `FString GetBestDisplayName(EOS_EpicAccountId TargetUserId, const FStringView& RequestedPlatform) const;`
- L405 _private prototype_ `bool IsLocalUserValid(int32 LocalUserNum) const ;`
- L406 _private prototype_ `FLocalUserEOS& GetLocalUserChecked(int32 LocalUserNum);`
- L408 _private prototype_ `void CallEOSAuthLogin(int32 LocalUserNum, const FOnlineAccountCredentials& Credentials, bool bIsAutoLogin);`
- L409 _private prototype_ `void CopyAndSaveEpicAuthToken(int32 LocalUserNum, const EOS_EpicAccountId& EpicAccountId);`
- L410 _private prototype_ `void OnEOSAuthLoginComplete(int32 LocalUserNum, const EOS_ELoginCredentialType LoginCredentialType, const bool bIsAutoLogin, const EOS_Auth_LoginCallbackInfo* Data);`
- L411 _private prototype_ `void CallEOSConnectLogin(int32 LocalUserNum, const FOnlineAccountCredentials& Credentials);`
- L413 _private prototype_ `void CallEOSAuthLogout(int32 LocalUserNum, FUniqueNetIdEOSPtr UserId);`
- L414 _private prototype_ `void CallEOSConnectLogout(int32 LocalUserNum, FUniqueNetIdEOSPtr UserId);`
- L416 _private prototype_ `FLocalUserEOS& AddLocalUser(int32 LocalUserNum);`
- L417 _private prototype_ `FLocalUserEOS& UpdateLocalUser(int32 LocalUserNum, EOS_EpicAccountId EpicAccountId, EOS_ProductUserId UserId);`
- L418 _private prototype_ `void RemoveLocalUser(int32 LocalUserNum);`
- L420 _private typedef_ `typedef TFunction<void(bool bWasSuccessful, FUniqueNetIdEOSRef RemotePlayerNetId, const FString& ErrorStr)> FRemoteUserProcessedCallback;`
- L421 _private prototype_ `void AddRemotePlayer(int32 LocalUserNum, EOS_EpicAccountId EpicAccountId, const FRemoteUserProcessedCallback& Callback);`
- L422 _private typedef_ `typedef TFunction<void(bool bWasSuccessful, TArray<FUniqueNetIdEOSRef> RemotePlayerNetIds, const FString& ErrorStr)> FRemoteUsersProcessedCallback;`
- L423 _private prototype_ `void AddRemotePlayers(int32 LocalUserNum, TArray<EOS_EpicAccountId> EpicAccountIds, const FRemoteUsersProcessedCallback& Callback);`
- L424 _private prototype_ `void ReadUserInfo(int32 LocalUserNum, EOS_EpicAccountId EpicAccountId, const FRemoteUserProcessedCallback& Callback);`
- L427 _private prototype_ `FOnlineFriendEOSRef AddFriend(int32 LocalUserNum, const FUniqueNetIdEOS& FriendNetId);` — This method does not call AddRemotePlayer, only registers an already existing remote player as a friend for a local user
- L429 _private prototype_ `void UpdateUserInfo(IAttributeAccessInterfaceRef AttriubteAccessRef, EOS_EpicAccountId LocalId, EOS_EpicAccountId TargetId);`
- L430 _private prototype_ `bool IsFriendQueryUserInfoOngoing(int32 LocalUserNum);`
- L431 _private prototype_ `void ProcessReadFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ErrorStr);`
- L433 _private prototype_ `void UpdatePresence(int32 LocalUserNum, EOS_EpicAccountId AccountId);`
- L434 _private prototype_ `void UpdateFriendPresence(const FUniqueNetIdEOSRef& FriendId, FOnlineUserPresenceRef Presence);`
- L436 _private prototype_ `void GetPlatformAuthToken(int32 LocalUserNum, const FOnGetLinkedAccountAuthTokenCompleteDelegate& Delegate) const;`
- L437 _private prototype_ `FString GetPlatformDisplayName(int32 LocalUserNum) const;`
- L440 _private prototype_ `FString GetEOSAuthTokenFilename();` — Get the file name for the Epic Auth Token file used in Persistent Auth
- L443 _private member_ `FOnlineSubsystemEOS* EOSSubsystem;` — Cached pointer to owning subsystem
- L446 _private member_ `int32 DefaultLocalUser;` — Default local user when no local user is specified
- L449 _private member_ `EOS_NotificationId AuthLoginStatusChangedNotificationId = EOS_INVALID_NOTIFICATIONID;` — Notification state for SDK events
- L450 _private member_ `FCallbackBase* AuthLoginStatusChangedNotificationCallback = nullptr;`
- L451 _private member_ `EOS_NotificationId ConnectLoginStatusChangedNotificationId = EOS_INVALID_NOTIFICATIONID;`
- L452 _private member_ `FCallbackBase* ConnectLoginStatusChangedNotificationCallback = nullptr;`
- L453 _private member_ `EOS_NotificationId ConnectLoginExpiredNotificationId = EOS_INVALID_NOTIFICATIONID;`
- L454 _private member_ `FCallbackBase* ConnectLoginExpiredNotificationCallback = nullptr;`
- L455 _private member_ `EOS_NotificationId FriendsNotificationId = EOS_INVALID_NOTIFICATIONID;`
- L456 _private member_ `FCallbackBase* FriendsNotificationCallback = nullptr;`
- L457 _private member_ `EOS_NotificationId PresenceNotificationId = EOS_INVALID_NOTIFICATIONID;`
- L458 _private member_ `FCallbackBase* PresenceNotificationCallback = nullptr;`
- L459 _private member_ `EOS_NotificationId DisplaySettingsUpdatedId = EOS_INVALID_NOTIFICATIONID;`
- L460 _private member_ `FCallbackBase* DisplaySettingsUpdatedCallback = nullptr;`
- L461 _private member_ `bool bLastReportedExclusiveInput = false;`
- L464 _private member_ `TLocalUserArray<FLocalUserEOS> LocalUsers;` — Information related to ongoing operations and state for local users
- L469 _private member_ `TUniqueNetIdMap<FOnlineUserEOSRef> UniqueNetIdToUserRefMap;` — Ids mapped to attribute access information for any user
- L472 _private member_ `TUniqueNetIdMap<FOnlineUserPresenceRef> UniqueNetIdToOnlineUserPresenceMap;` — Ids mapped to user presence information for any user

#### Free symbols / members of external scopes

- L15 _macro_ `#define INVALID_LOCAL_USER -1`
- L18 _typedef_ `template <typename ValueType> using TLocalUserArray = TSparseArray<ValueType, TInlineSparseArrayAllocator<MAX_LOCAL_PLAYERS>>;`
- L23 _typedef_ `typedef TSharedPtr<FOnlineUser> FOnlineUserPtr;`
- L24 _typedef_ `typedef TSharedRef<FOnlineUser> FOnlineUserRef;`
- L40 _typedef_ `typedef TSharedPtr<FOnlineUserEOS> FOnlineUserEOSPtr;`
- L41 _typedef_ `typedef TSharedRef<FOnlineUserEOS> FOnlineUserEOSRef;`
- L57 _typedef_ `typedef TSharedPtr<FUserOnlineAccountEOS> FUserOnlineAccountEOSPtr;`
- L58 _typedef_ `typedef TSharedRef<FUserOnlineAccountEOS> FUserOnlineAccountEOSRef;`
- L80 _typedef_ `typedef TSharedPtr<FOnlineFriendEOS> FOnlineFriendEOSPtr;`
- L81 _typedef_ `typedef TSharedRef<FOnlineFriendEOS> FOnlineFriendEOSRef;`
- L155 _typedef_ `typedef TSharedRef<FFriendsListEOS> FFriendsListEOSRef;`
- L156 _typedef_ `typedef TSharedPtr<FFriendsListEOS> FFriendsListEOSPtr;`
- L475 _typedef_ `typedef TSharedPtr<FUserManagerEOS, ESPMode::ThreadSafe> FUserManagerEOSPtr;`
- L476 _typedef_ `typedef TWeakPtr<FUserManagerEOS, ESPMode::ThreadSafe> FUserManagerEOSWeakPtr;`
- L477 _typedef_ `typedef TWeakPtr<const FUserManagerEOS, ESPMode::ThreadSafe> FUserManagerEOSConstWeakPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/Windows/WindowsEOSHelpers.h` (Private)


#### class `FWindowsEOSHelpers`  
`class FWindowsEOSHelpers : public FEOSHelpers`  
_L9-15_
- inherits: `FEOSHelpers`
- L12 _public prototype_ `virtual ~FWindowsEOSHelpers() = default;`
- L14 _public prototype_ `virtual IEOSPlatformHandlePtr CreatePlatform(EOS_Platform_Options& PlatformOptions) override;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using FPlatformEOSHelpers = FWindowsEOSHelpers;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Public/EOSSettings.h` (Public)


#### struct `FEOSArtifactSettings`  
`struct FEOSArtifactSettings`  
_L14-23_
- desc: Native version of the UObject based config data
- L16 _public member_ `FString ArtifactName;`
- L17 _public member_ `FString ClientId;`
- L18 _public member_ `FString ClientSecret;`
- L19 _public member_ `FString ProductId;`
- L20 _public member_ `FString SandboxId;`
- L21 _public member_ `FString DeploymentId;`
- L22 _public member_ `FString EncryptionKey;`

#### class `UDEPRECATED_EOSArtifactSettings`  
`class UDEPRECATED_EOSArtifactSettings : public UDataAsset`  
_L26-35_
- reflection: `UCLASS(Deprecated)`
- inherits: `UDataAsset`
- L32 _public function_ `UDEPRECATED_EOSArtifactSettings()`

#### struct `FArtifactSettings`  
`struct FArtifactSettings`  
_L38-67_
- reflection: `USTRUCT(BlueprintType)`
- L45 _public member_ `FString ArtifactName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — This needs to match what the launcher passes in the -epicapp command line arg
- L48 _public member_ `FString ClientId;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Artifact Settings")`
- L51 _public member_ `FString ClientSecret;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Artifact Settings")`
- L54 _public member_ `FString ProductId;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Artifact Settings")`
- L57 _public member_ `FString SandboxId;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Artifact Settings")`
- L60 _public member_ `FString DeploymentId;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Artifact Settings")`
- L64 _public member_ `FString ClientEncryptionKey;` — Config key renamed to ClientEncryptionKey as EncryptionKey gets removed from packaged builds due to IniKeyDenylist=EncryptionKey entry in BaseGame.ini.
- L66 _public prototype_ `FEOSArtifactSettings ToNative() const;`

#### struct `FEOSSettings`  
`struct FEOSSettings`  
_L70-101_
- desc: Native version of the UObject based config data
- L72 _public prototype_ `FEOSSettings();`
- L75 _public prototype_ `FEOSSettings(const FEOSSettings& Other) = default;`
- L76 _public prototype_ `FEOSSettings(FEOSSettings&& Other) = default;`
- L79 _public member_ `FString CacheDir;`
- L80 _public member_ `FString DefaultArtifactName;`
- L81 _public member_ `FString SteamTokenType;`
- L82 _public member_ `FString NintendoTokenType;`
- L83 _public member_ `FString PlatformConfigName;`
- L84 _public member_ `EOS_ERTCBackgroundMode RTCBackgroundMode;`
- L85 _public member_ `int32 TickBudgetInMilliseconds;`
- L86 _public member_ `int32 TitleStorageReadChunkLength;`
- L87 _public member_ `bool bEnableOverlay;`
- L88 _public member_ `bool bEnableSocialOverlay;`
- L89 _public member_ `bool bEnableEditorOverlay;`
- L90 _public member_ `bool bPreferPersistentAuth;`
- L91 _public member_ `bool bUseEAS;`
- L92 _public member_ `bool bUseEOSConnect;`
- L93 _public member_ `bool bUseEOSRTC;`
- L94 _public member_ `bool bUseNamedPlatformConfig;`
- L95 _public member_ `bool bUseNewEcomFlow;`
- L97 _public member_ `bool bUseNewLoginFlow;` — `UE_DEPRECATED(5.7, "bUseNewLoginFlow is deprecated, the legacy login flow has been removed from UserManagerEOS.")`
- L98 _public member_ `TArray<FEOSArtifactSettings> Artifacts;`
- L99 _public member_ `TArray<FString> TitleStorageTags;`
- L100 _public member_ `TArray<FString> AuthScopeFlags;`

#### class `UEOSSettings`  
`class UEOSSettings : public URuntimeOptionsBase`  
_L104-244_
- reflection: `UCLASS(MinimalAPI, Config=Engine, DefaultConfig)`
- inherits: `URuntimeOptionsBase`
- L116 _public member_ `FString CacheDir = TEXT("Cac` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — The directory any PDS/TDS files are cached into. This is per artifact e.g.: <UserDir>/<ArtifactId>/<CacheDir>
- L120 _public member_ `FString DefaultArtifactName;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — Used when launched from a store other than EGS or when the specified artifact name was not present
- L124 _public member_ `FString PlatformConfigName;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — When bUseNamedPlatformConfig is true, specifies the platform config name to use
- L128 _public member_ `FString RTCBackgroundMode;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — The preferred background mode to be used by RTC services
- L132 _public member_ `int32 TickBudgetInMilliseconds = 0;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — Used to throttle how much time EOS ticking can take
- L136 _public member_ `bool bEnableOverlay = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — Set to true to enable the overlay (ecom features)
- L140 _public member_ `bool bEnableSocialOverlay = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — Set to true to enable the social overlay (friends, invites, etc.)
- L144 _public member_ `bool bEnableEditorOverlay = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "EOS Settings")` — Set to true to enable the overlay when running in the editor
- L148 _public member_ `bool bPreferPersistentAuth = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — Set to true to prefer persistent auth over external authentication during Login
- L152 _public member_ `TArray<FString> TitleStorageTags;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — Tag combinations for paged queries in title file enumerations, separate tags within groups using `+`
- L156 _public member_ `int32 TitleStorageReadChunkLength = 0;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — Chunk size used when reading a title file
- L160 _public member_ `TArray<FArtifactSettings> Artifacts;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — Per artifact SDK settings. A game might have a FooStaging, FooQA, and public Foo artifact
- L164 _public member_ `TArray<FString> AuthScopeFlags;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "EOS Settings")` — Auth scopes to request during login
- L168 _public member_ `bool bUseEAS = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings", DisplayName="Login to EOS Auth, and use Epic Account Services")` — Set to true to login to EOS_Auth (required to use Epic Account Services)
- L172 _public member_ `bool bUseEOSConnect = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings", DisplayName="Login to EOS Connect, and use EOS Game Services")` — Set to true to login to EOS_Connect (required to use Epic Game Services)
- L176 _public member_ `bool bUseEOSRTC = true;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings", DisplayName="Enable Real-Time chat")` — Whether real-time chat is initialized when creating the EOS platform
- L184 _public member_ `bool bUseNamedPlatformConfig = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Settings")` — Set to true to use the IEOSSDKManager "named platform config" mechanism, rather than loading a config from OSSEOS ini. Specify the platform config name to use with the "PlatformConfigName" setting.
- L188 _public member_ `bool bUseNewEcomFlow = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "EOS Ecom Settings", DisplayName = "Use new Ecom flow")` — New Epic Games Store Ecom integration - Use IOnlineEntitlements, IOnlinePurchase and IOnlineStoreV2 for a complete feature set of the Ecom interface in the EOS SDK
- L193 _public member_ `bool bUseNewLoginFlow = false;` — `UE_DEPRECATED(5.7, "bUseNewLoginFlow is deprecated, the legacy login flow has been removed from UserManagerEOS.")` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="EOS Login Settings", DisplayName="Use new Login flow, which doesn't rely on EOSPlus")` — Set to true to use new EOS login flow
- L206 _public member_ `FString SteamTokenType = TEXT("Ses` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Crossplay Settings")` — When running with Steam, defines what TokenType OSSEOS will request from OSSSteam to login with. Please see EOS documentation at https://dev.epicgames.com/docs/dev-portal/identity-provider-management#steam for more information. Note the default is currently "Session" but this is deprecated. Please migrate to WebApi. Possible values: "App" -> [DEPRECATED] Use Steam Encryption Application Tickets from ISteamUser::GetEncryptedAppTicket. "Session" -> [DEPRECATED] Use Steam Auth Session Tickets from ISteamUser::GetAuthSessionTicket. "WebApi" -> Use Steam Auth Tickets from ISteamUser::GetAuthTicketForWebApi, using the default remote service identity configured for OSSSteam. "WebApi:<remoteserviceidentity>" -> Use Steam Auth Tickets from ISteamUser::GetAuthTicketForWebApi, using an explicit remote service identity.
- L216 _public member_ `FString NintendoTokenType = TEXT("Nin` — `UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Crossplay Settings")` — When running with Nintendo, defines what ExternalType will be used during ExternalAuth Login. The default is currently "NintendoServiceAccount". Possible values: "NintendoServiceAccount" -> Use the EOS_ECT_NINTENDO_NSA_ID_TOKEN token type. "NintendoAccount" -> Use the EOS_ECT_NINTENDO_ID_TOKEN token type.
- L219 _public prototype_ `static bool GetSelectedArtifactSettings(FEOSArtifactSettings& OutSettings);` — Get the settings for the selected artifact
- L221 _public prototype_ `static FEOSSettings GetSettings();`
- L222 _public prototype_ `FEOSSettings ToNative() const;`
- L226 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L229 _private prototype_ `static FString GetDefaultArtifactName();`
- L231 _private prototype_ `static bool GetArtifactSettings(const FString& ArtifactName, FEOSArtifactSettings& OutSettings);`
- L232 _private prototype_ `static bool GetArtifactSettings(const FString& ArtifactName, const FString& SandboxId, FEOSArtifactSettings& OutSettings);`
- L233 _private prototype_ `static bool GetArtifactSettings(const FString& ArtifactName, const FString& SandboxId, const FString& DeploymentId, FEOSArtifactSettings& OutSettings);`
- L234 _private prototype_ `static bool GetArtifactSettingsImpl(const FString& ArtifactName, const TOptional<FString>& SandboxId, const TOptional<FString>& DeploymentId, FEOSArtifactSettings& OutSettings);`
- L236 _private prototype_ `static const TArray<FEOSArtifactSettings>& GetCachedArtifactSettings();`
- L238 _private prototype_ `static FEOSSettings AutoGetSettings();`
- L239 _private prototype_ `static const FEOSSettings& ManualGetSettings();`
- L242 _private prototype_ `static void ModuleInit();`
- L243 _private prototype_ `static void ModuleShutdown();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ONLINESUBSYSTEMEOS_API`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Public/IOnlineSubsystemEOS.h` (Public)


#### class `IOnlineSubsystemEOS`  
`class IOnlineSubsystemEOS : public FOnlineSubsystemImpl`  
_L22-35_
- inherits: `FOnlineSubsystemImpl`
- desc: OnlineSubsystemEOS - Implementation of the online subsystem for EOS services
- L26 _public function_ `IOnlineSubsystemEOS(FName InSubsystemName, FName InInstanceName) : FOnlineSubsystemImpl(InSubsystemName, InInstanceName)`
- L27 _public prototype_ `virtual ~IOnlineSubsystemEOS() = default;`
- L29 _public prototype_ `virtual IVoiceChatUser* GetVoiceChatUserInterface(const FUniqueNetId& LocalUserId) = 0;`
- L30 _public prototype_ `virtual IEOSPlatformHandlePtr GetEOSPlatformHandle() const = 0;`
- L31 _public prototype_ `virtual IOnlinePlayerSanctionEOSPtr GetPlayerSanctionEOSInterface() const = 0;`
- L32 _public prototype_ `virtual IOnlinePlayerReportEOSPtr GetPlayerReportEOSInterface() const = 0;`
- L34 _public prototype_ `virtual void QueryUniqueNetId(int32 LocalUserNum, const EOS_ProductUserId& ProductUserId, const FOnQueryUniqueNetIdComplete & Callback) = 0;`

#### Free symbols / members of external scopes

- L10 _typedef_ `using IEOSPlatformHandlePtr = TSharedPtr<class IEOSPlatformHandle, ESPMode::ThreadSafe>;`
- L11 _typedef_ `using IOnlinePlayerSanctionEOSPtr = TSharedPtr<class IOnlinePlayerSanctionEOS, ESPMode::ThreadSafe>;`
- L12 _typedef_ `using IOnlinePlayerReportEOSPtr = TSharedPtr<class IOnlinePlayerReportEOS, ESPMode::ThreadSafe>;`
- L14 _typedef_ `using FUniqueNetIdEOSRef = TSharedRef<const class FUniqueNetIdEOS>;`
- L15 _typedef_ `using EOS_ProductUserId = struct EOS_ProductUserIdDetails*;`
- L17 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnQueryUniqueNetIdComplete, FUniqueNetIdEOSRef , const FOnlineError& );`
- L17 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnQueryUniqueNetIdComplete, FUniqueNetIdEOSRef , const FOnlineError& );`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Public/Interfaces/OnlinePlayerReportEOSInterface.h` (Public)


#### class `IOnlinePlayerReportEOS`  
`class IOnlinePlayerReportEOS`  
_L19-60_
- desc: Public Interface for interacting with EOS player reports
- L22 _public prototype_ `virtual ~IOnlinePlayerReportEOS() = default;`
- L59 _public prototype_ `virtual void SendPlayerReport(const FUniqueNetId& LocalUserId, const FUniqueNetId& TargetUserId, FSendPlayerReportSettings&& SendPlayerReportSettings, FOnSendPlayerReportComplete&& Delegate) = 0;` — Send a player report for a player cheating, misconduct, etc... @param LocalUserId the player id of the player sending the player report @param TargetUserId the player id the report is for @param FSendPlayerReportSettings the data to include in the player report.

#### enum `IOnlinePlayerReportEOS::EPlayerReportCategory`  
`enum class EPlayerReportCategory`  
_L27-36_
- desc: Enum to set the category on the player report
- L29 _public enumerator_ `Cheating`
- L30 _public enumerator_ `Exploiting`
- L31 _public enumerator_ `OffensiveProfile`
- L32 _public enumerator_ `VerbalAbuse`
- L33 _public enumerator_ `Scamming`
- L34 _public enumerator_ `Spamming`
- L35 _public enumerator_ `Other`

#### struct `IOnlinePlayerReportEOS::FSendPlayerReportSettings`  
`struct FSendPlayerReportSettings`  
_L41-51_
- desc: Struct for player report data
- L44 _public member_ `EPlayerReportCategory Category;` — Required - The category of the player
- L47 _public member_ `FString Message;` — Optional - Message from the player descripting the issue being reported
- L50 _public member_ `FString Context;` — Optional - Context information around the issue being reported the game can send. This needs to be in a valid JSON format otherwise the EOS SDK will throw an error

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSendPlayerReportComplete, const bool );` — Delegate fired when the player report report was sent @param bWasSuccessful true if the player report was successfully received
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSendPlayerReportComplete, const bool );` — Delegate fired when the player report report was sent @param bWasSuccessful true if the player report was successfully received
- L61 _typedef_ `typedef TSharedPtr<IOnlinePlayerReportEOS, ESPMode::ThreadSafe> IOnlinePlayerReportEOSPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Public/Interfaces/OnlinePlayerSanctionEOSInterface.h` (Public)


#### class `IOnlinePlayerSanctionEOS`  
`class IOnlinePlayerSanctionEOS`  
_L25-92_
- desc: Public Interface for interacting with EOS player sanctions
- L28 _public prototype_ `virtual ~IOnlinePlayerSanctionEOS() = default;`
- L77 _public prototype_ `virtual void CreatePlayerSanctionAppeal(const FUniqueNetId& LocalUserId, FPlayerSanctionAppealSettings&& SanctionAppealSettings, FOnCreatePlayerSanctionAppealComplete&& Delegate) = 0;` — Send a player sanction appeal @param LocalUserId the player id of the local user sending the sanction appeal. @param SanctionAppealSettings the settings needed to create the sanction appeal.
- L84 _public prototype_ `virtual void QueryActivePlayerSanctions(const FUniqueNetId& LocalUserId, const FUniqueNetId& TargetUserId, FOnQueryActivePlayerSanctionsComplete&& Delegate) = 0;` — Query active player sanction. The sanctions will be cached locally and can be retrieved using GetCachedActivePlayerSanctions @param LocalUserId the player id of the local user querying the sanctions. @param TargetUserId the player id of the player we are querying sanctions for.
- L91 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedActivePlayerSanctions(const FUniqueNetId& TargetUserId, TArray<FOnlinePlayerSanction>& OutPlayerSanctions) = 0;` — Retrieve cached player sanctions @param TargetUserId the player id we want to retrieve the sanctions for. @param OutPlayerSanctions the array to store the sanctions.

#### enum `IOnlinePlayerSanctionEOS::EPlayerSanctionAppealReason`  
`enum class EPlayerSanctionAppealReason`  
_L34-40_
- desc: Enum to set the appeal reason when creating a sanction appeal
- L36 _public enumerator_ `IncorrectSanction`
- L37 _public enumerator_ `CompromisedAccount`
- L38 _public enumerator_ `UnfairPunishment`
- L39 _public enumerator_ `AppealForForgivenesss`

#### struct `IOnlinePlayerSanctionEOS::FPlayerSanctionAppealSettings`  
`struct FPlayerSanctionAppealSettings`  
_L45-52_
- desc: Struct for the settings of sanction appeal
- L48 _public member_ `EPlayerSanctionAppealReason Reason;` — The reason of the appeal
- L51 _public member_ `FString ReferenceId;` — The sanction id for the sanction that is being appealed

#### struct `IOnlinePlayerSanctionEOS::FOnlinePlayerSanction`  
`struct FOnlinePlayerSanction`  
_L57-70_
- desc: Struct for player sanctions
- L60 _public member_ `int64_t TimePlaced;` — The time the sanction was placed
- L63 _public member_ `int64_t TimeExpires;` — The time the sanction expires
- L66 _public member_ `FString Action;` — The action associated with this sanction
- L69 _public member_ `FString ReferenceId;` — The sanction id for the sanction that is being appealed. This needs to be set

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCreatePlayerSanctionAppealComplete, const bool );` — Delegate fired when a player sanction appeal has been created @param bWasSuccessful true if creating the sanction appel was successful
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCreatePlayerSanctionAppealComplete, const bool );` — Delegate fired when a player sanction appeal has been created @param bWasSuccessful true if creating the sanction appel was successful
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueryActivePlayerSanctionsComplete, const bool );` — Delegate fired when player sanctions have been cached locally @param bWasSuccessful true if sanctions are available in local cache
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FOnQueryActivePlayerSanctionsComplete, const bool );` — Delegate fired when player sanctions have been cached locally @param bWasSuccessful true if sanctions are available in local cache
- L93 _typedef_ `typedef TSharedPtr<IOnlinePlayerSanctionEOS, ESPMode::ThreadSafe> IOnlinePlayerSanctionEOSPtr;`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Public/OnlineSubsystemEOSPackage.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define PACKAGE_SCOPE public`
- L14 _macro_ `#define PACKAGE_SCOPE protected`

### `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Public/OnlineSubsystemEOSTypesPublic.h` (Public)


#### class `IUniqueNetIdEOS`  
`class IUniqueNetIdEOS : public FUniqueNetId`  
_L16-29_
- inherits: `FUniqueNetId`
- desc: Unique net id for OnlineSubsystemEOS
- L23 _public prototype_ `virtual const EOS_EpicAccountId GetEpicAccountId() const = 0;` — Get the Epic Account Id. May be null. @return the Epic Account Id, or null.
- L28 _public prototype_ `virtual const EOS_ProductUserId GetProductUserId() const = 0;` — Get the Product User Id. May be null. @return the Product User Id, or null.

#### Free symbols / members of external scopes

- L31 _macro_ `#define OSSEOS_BUCKET_ID_ATTRIBUTE_KEY FName("OSSEOS_BUCKET_ID_ATTRIBUTE_KEY")`
