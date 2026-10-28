# Plugins / OnlineServicesCommon

- module root: `Plugins/Online/OnlineServices/Source/OnlineServicesCommon`
- headers: 31; symbols: 1444
- symbol kinds: class=74, delegate=1, enum=6, enumerator=18, externvar=4, function=368, macro=22, member=272, namespace=94, prototype=444, struct=88, typedef=51, variable=2
- PrivateDependencyModuleNames: Core, CoreUObject
- PublicDependencyModuleNames: CoreOnline, OnlineBase, OnlineServicesInterface

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Private/Online/LobbiesCommonTests.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)
- L15 _prototype_ `TOnlineAsyncOpHandle<FFunctionalTestLobbies> RunLobbyFunctionalTest(IAuth& AuthInterface, FLobbiesCommon& LobbiesCommon, FLobbyEvents& LobbyEvents);` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/AchievementsCommon.h` (Public)


#### struct `UE::Online::FAchievementUnlockCondition`  
`struct FAchievementUnlockCondition`  
_L15-19_
- L17 _public member_ `FString StatName;`
- L18 _public member_ `FStatValue UnlockThreshold;` — The unlock rule depends on Stat modification type

#### struct `UE::Online::FAchievementUnlockRule`  
`struct FAchievementUnlockRule`  
_L21-27_
- L23 _public member_ `FString AchievementId;`
- L24 _public member_ `TArray<FAchievementUnlockCondition> Conditions;`
- L26 _public prototype_ `bool ContainsStat(const FString& StatName) const;`

#### struct `UE::Online::FAchievementsCommonConfig`  
`struct FAchievementsCommonConfig`  
_L29-33_
- L31 _public member_ `bool bIsTitleManaged = false;`
- L32 _public member_ `TArray<FAchievementUnlockRule> UnlockRules;`

#### class `UE::Online::FAchievementsCommon`  
`class FAchievementsCommon : public TOnlineComponent<IAchievements>`  
_L55-94_
- inherits: `TOnlineComponent<IAchievements>`
- L58 _public typedef_ `using Super = IAchievements;`
- L60 _public prototype_ `FAchievementsCommon(FOnlineServicesCommon& InServices);`
- L63 _public prototype_ `virtual void Initialize() override;` — TOnlineComponent
- L64 _public prototype_ `virtual void Shutdown() override;`
- L65 _public prototype_ `virtual void UpdateConfig() override;`
- L66 _public prototype_ `virtual void RegisterCommands() override;`
- L69 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementDefinitions> QueryAchievementDefinitions(FQueryAchievementDefinitions::Params&& Params) override;` — IAchievements
- L70 _public prototype_ `virtual TOnlineResult<FGetAchievementIds> GetAchievementIds(FGetAchievementIds::Params&& Params) override;`
- L71 _public prototype_ `virtual TOnlineResult<FGetAchievementDefinition> GetAchievementDefinition(FGetAchievementDefinition::Params&& Params) override;`
- L72 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementStates> QueryAchievementStates(FQueryAchievementStates::Params&& Params) override;`
- L73 _public prototype_ `virtual TOnlineResult<FGetAchievementState> GetAchievementState(FGetAchievementState::Params&& Params) const override;`
- L74 _public prototype_ `virtual TOnlineAsyncOpHandle<FUnlockAchievements> UnlockAchievements(FUnlockAchievements::Params&& Params) override;`
- L75 _public prototype_ `virtual TOnlineResult<FDisplayAchievementUI> DisplayAchievementUI(FDisplayAchievementUI::Params&& Params) override;`
- L76 _public prototype_ `virtual TOnlineEvent<void(const FAchievementStateUpdated&)> OnAchievementStateUpdated() override;`
- L79 _protected member_ `TOnlineEventCallable<void(const FAchievementStateUpdated&)> OnAchievementStateUpdatedEvent;`
- L81 _protected prototype_ `void OnAchievementStatesQueried(const FAccountId& AccountId);`
- L83 _protected prototype_ `void UnlockAchievementsByStats(const FStatsUpdated& StatsUpdated);`
- L84 _protected prototype_ `void ExecuteUnlockRulesRelatedToStat(const FAccountId& AccountId, const FString& StatName, const TMap<FString, FStatValue>& Stats, TArray<FString>& OutAchievementsToUnlock);`
- L85 _protected prototype_ `bool MeetUnlockCondition(const FAchievementUnlockRule& AchievementUnlockRule, const TMap<FString, FStatValue>& Stats);`
- L86 _protected prototype_ `bool IsUnlocked(const FAccountId& AccountId, const FString& AchievementName) const;`
- L88 _protected member_ `FOnlineEventDelegateHandle StatEventHandle;`
- L90 _protected member_ `FAchievementsCommonConfig Config;`
- L92 _protected typedef_ `using FAchievementStateMap = TMap<FString, FAchievementState>;`
- L93 _protected member_ `TMap<FAccountId, FAchievementStateMap> AchievementStates;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L35 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/AuthCommon.h` (Public)


#### class `UE::Online::FAccountInfoRegistry`  
`class FAccountInfoRegistry`  
_L13-35_
- L16 _public prototype_ `virtual ~FAccountInfoRegistry() = default;`
- L18 _public prototype_ `TSharedPtr<FAccountInfo> Find(FPlatformUserId PlatformUserId) const;`
- L19 _public prototype_ `TSharedPtr<FAccountInfo> Find(FAccountId AccountId) const;`
- L21 _public prototype_ `TArray<TSharedRef<FAccountInfo>> GetAllAccountInfo(TFunction<bool(const TSharedRef<FAccountInfo>&)> Predicate) const;`
- L24 _protected prototype_ `TSharedPtr<FAccountInfo> FindNoLock(FPlatformUserId PlatformUserId) const;`
- L25 _protected prototype_ `TSharedPtr<FAccountInfo> FindNoLock(FAccountId AccountId) const;`
- L27 _protected prototype_ `virtual void DoRegister(const TSharedRef<FAccountInfo>& AccountInfo);`
- L28 _protected prototype_ `virtual void DoUnregister(const TSharedRef<FAccountInfo>& AccountInfo);`
- L30 _protected member_ `mutable FRWLock IndexLock;`
- L33 _private member_ `TMap<FPlatformUserId, TSharedRef<FAccountInfo>> AuthDataByPlatformUserId;`
- L34 _private member_ `TMap<FAccountId, TSharedRef<FAccountInfo>> AuthDataByOnlineAccountIdHandle;`

#### class `UE::Online::FAuthCommon`  
`class FAuthCommon : public TOnlineComponent<IAuth>`  
_L37-76_
- inherits: `TOnlineComponent<IAuth>`
- L40 _public typedef_ `using Super = IAuth;`
- L42 _public prototype_ `FAuthCommon(FOnlineServicesCommon& InServices);`
- L45 _public prototype_ `virtual void RegisterCommands() override;` — IOnlineComponent
- L48 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLogin> Login(FAuthLogin::Params&& Params) override;` — IAuth
- L49 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLogout> Logout(FAuthLogout::Params&& Params) override;`
- L50 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthCreateAccount> CreateAccount(FAuthCreateAccount::Params&& Params) override;`
- L51 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLinkAccount> LinkAccount(FAuthLinkAccount::Params&& Params) override;`
- L52 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthModifyAccountAttributes> ModifyAccountAttributes(FAuthModifyAccountAttributes::Params&& Params) override;`
- L53 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryExternalServerAuthTicket> QueryExternalServerAuthTicket(FAuthQueryExternalServerAuthTicket::Params&& Params) override;`
- L54 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryExternalAuthToken> QueryExternalAuthToken(FAuthQueryExternalAuthToken::Params&& Params) override;`
- L55 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryVerifiedAuthTicket> QueryVerifiedAuthTicket(FAuthQueryVerifiedAuthTicket::Params&& Params) override;`
- L56 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthCancelVerifiedAuthTicket> CancelVerifiedAuthTicket(FAuthCancelVerifiedAuthTicket::Params&& Params) override;`
- L57 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthBeginVerifiedAuthSession> BeginVerifiedAuthSession(FAuthBeginVerifiedAuthSession::Params&& Params) override;`
- L58 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthEndVerifiedAuthSession> EndVerifiedAuthSession(FAuthEndVerifiedAuthSession::Params&& Params) override;`
- L59 _public prototype_ `virtual TOnlineResult<FAuthGetLocalOnlineUserByOnlineAccountId> GetLocalOnlineUserByOnlineAccountId(FAuthGetLocalOnlineUserByOnlineAccountId::Params&& Params) const override;`
- L60 _public prototype_ `virtual TOnlineResult<FAuthGetLocalOnlineUserByPlatformUserId> GetLocalOnlineUserByPlatformUserId(FAuthGetLocalOnlineUserByPlatformUserId::Params&& Params) const override;`
- L61 _public prototype_ `virtual TOnlineResult<FAuthGetAllLocalOnlineUsers> GetAllLocalOnlineUsers(FAuthGetAllLocalOnlineUsers::Params&& Params) const override;`
- L62 _public prototype_ `virtual TOnlineResult<FAuthGetLinkAccountContinuationId> GetLinkAccountContinuationId(FAuthGetLinkAccountContinuationId::Params&& Params) const override;`
- L63 _public prototype_ `virtual TOnlineResult<FAuthGetRelyingParty> GetRelyingParty(FAuthGetRelyingParty::Params&& Params) const override;`
- L64 _public prototype_ `virtual TOnlineEvent<void(const FAuthLoginStatusChanged&)> OnLoginStatusChanged() override;`
- L65 _public prototype_ `virtual TOnlineEvent<void(const FAuthPendingAuthExpiration&)> OnPendingAuthExpiration() override;`
- L66 _public prototype_ `virtual TOnlineEvent<void(const FAuthAccountAttributesChanged&)> OnAccountAttributesChanged() override;`
- L67 _public prototype_ `virtual bool IsLoggedIn(const FAccountId& AccountId) const override;`
- L68 _public prototype_ `virtual bool IsLoggedIn(const FPlatformUserId& PlatformUserId) const override;`
- L71 _protected prototype_ `virtual const FAccountInfoRegistry& GetAccountInfoRegistry() const = 0;`
- L73 _protected member_ `TOnlineEventCallable<void(const FAuthLoginStatusChanged&)> OnAuthLoginStatusChangedEvent;`
- L74 _protected member_ `TOnlineEventCallable<void(const FAuthPendingAuthExpiration&)> OnAuthPendingAuthExpirationEvent;`
- L75 _protected member_ `TOnlineEventCallable<void(const FAuthAccountAttributesChanged&)> OnAuthAccountAttributesChangedEvent;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/CommerceCommon.h` (Public)


#### class `UE::Online::FCommerceCommon`  
`class FCommerceCommon : public TOnlineComponent<ICommerce>`  
_L14-43_
- inherits: `TOnlineComponent<ICommerce>`
- L17 _public typedef_ `using Super = ICommerce;`
- L19 _public prototype_ `FCommerceCommon(FOnlineServicesCommon& InServices);`
- L22 _public prototype_ `virtual void RegisterCommands() override;` — IOnlineComponent
- L25 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryOffers> QueryOffers(FCommerceQueryOffers::Params&& Params) override;` — ICommerce
- L26 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryOffersById> QueryOffersById(FCommerceQueryOffersById::Params&& Params) override;`
- L27 _public prototype_ `virtual TOnlineResult<FCommerceGetOffers> GetOffers(FCommerceGetOffers::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineResult<FCommerceGetOffersById> GetOffersById(FCommerceGetOffersById::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceShowStoreUI> ShowStoreUI(FCommerceShowStoreUI::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceCheckout> Checkout(FCommerceCheckout::Params&& Params) override;`
- L31 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryTransactionEntitlements> QueryTransactionEntitlements(FCommerceQueryTransactionEntitlements::Params&& Params) override;`
- L32 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryEntitlements> QueryEntitlements(FCommerceQueryEntitlements::Params&& Params) override;`
- L33 _public prototype_ `virtual TOnlineResult<FCommerceGetEntitlements> GetEntitlements(FCommerceGetEntitlements::Params&& Params) override;`
- L34 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceRedeemEntitlement> RedeemEntitlement(FCommerceRedeemEntitlement::Params&& Params) override;`
- L35 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceRetrieveS2SToken> RetrieveS2SToken(FCommerceRetrieveS2SToken::Params&& Params) override;`
- L36 _public prototype_ `virtual TOnlineEvent<void(const FCommerceOnPurchaseComplete&)> OnPurchaseCompleted() override;`
- L39 _public prototype_ `FText GetFormattedPrice(uint64 Price, int32 DecimalPoint, FString CurrencyCode);` — CommerceCommon
- L42 _protected member_ `TOnlineEventCallable<void(const FCommerceOnPurchaseComplete&)> OnPurchaseCompletedEvent;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/ConnectivityCommon.h` (Public)


#### class `UE::Online::FConnectivityCommon`  
`class FConnectivityCommon : public TOnlineComponent<IConnectivity>`  
_L14-32_
- inherits: `TOnlineComponent<IConnectivity>`
- L17 _public typedef_ `using Super = IConnectivity;`
- L19 _public prototype_ `FConnectivityCommon(FOnlineServicesCommon& InServices);`
- L22 _public prototype_ `virtual void RegisterCommands() override;` — TOnlineComponent
- L25 _public prototype_ `virtual TOnlineResult<FGetConnectionStatus> GetConnectionStatus(FGetConnectionStatus::Params&& Params) override;` — IConnectivity
- L26 _public prototype_ `virtual TOnlineEvent<void(const FConnectionStatusChanged&)> OnConnectionStatusChanged() override;`
- L29 _protected member_ `EOnlineServicesConnectionStatus ConnectionStatus = EOnlineServicesConnectionStatus::NotConnected;`
- L31 _protected member_ `TOnlineEventCallable<void(const FConnectionStatusChanged&)> OnConnectionStatusChangedEvent;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/ExternalUICommon.h` (Public)


#### class `UE::Online::FExternalUICommon`  
`class FExternalUICommon : public TOnlineComponent<IExternalUI>`  
_L14-31_
- inherits: `TOnlineComponent<IExternalUI>`
- L17 _public typedef_ `using Super = IExternalUI;`
- L19 _public prototype_ `FExternalUICommon(FOnlineServicesCommon& InServices);`
- L22 _public prototype_ `virtual void RegisterCommands() override;` — TOnlineComponent
- L25 _public prototype_ `virtual TOnlineAsyncOpHandle<FExternalUIShowLoginUI> ShowLoginUI(FExternalUIShowLoginUI::Params&& Params) override;` — IExternalUI
- L26 _public prototype_ `virtual TOnlineAsyncOpHandle<FExternalUIShowFriendsUI> ShowFriendsUI(FExternalUIShowFriendsUI::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineEvent<void(const FExternalUIStatusChanged&)> OnExternalUIStatusChanged() override;`
- L30 _protected member_ `TOnlineEventCallable<void(const FExternalUIStatusChanged&)> OnExternalUIStatusChangedEvent;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/IOnlineComponent.h` (Public)


#### class `UE::Online::IOnlineComponent`  
`class IOnlineComponent`  
_L8-24_
- L11 _public prototype_ `virtual ~IOnlineComponent() = default;`
- L13 _public prototype_ `virtual void Initialize() = 0;` — Called after component has been constructed. It is not safe to reference other components at this time
- L15 _public prototype_ `virtual void PostInitialize() = 0;` — Called after all components have been initialized
- L17 _public prototype_ `virtual void UpdateConfig() = 0;` — Called whenever we need to reload data from config
- L19 _public prototype_ `virtual void Tick(float DeltaSeconds) = 0;` — Called every Tick
- L21 _public prototype_ `virtual void PreShutdown() = 0;` — Called before any component has been shutdown
- L23 _public prototype_ `virtual void Shutdown() = 0;` — Called right before the component is destroyed. It is not safe to reference any other components at this time

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/LeaderboardsCommon.h` (Public)


#### enum `UE::Online::ELeaderboardUpdateMethod`  
`enum class ELeaderboardUpdateMethod : uint8`  
_L13-19_
- L16 _public enumerator_ `KeepBest` — If current leaderboard score is better than the uploaded one, keep the current one
- L18 _public enumerator_ `Force` — Leaderboard score is always replaced with uploaded value

#### enum `UE::Online::ELeaderboardOrderMethod`  
`enum ELeaderboardOrderMethod : uint8`  
_L24-28_
- L26 _public enumerator_ `Ascending`
- L27 _public enumerator_ `Descending`

#### struct `UE::Online::FLeaderboardDefinition`  
`struct FLeaderboardDefinition`  
_L33-43_
- L36 _public member_ `FString Name;` — The name of the leaderboard
- L38 _public member_ `int32 Id = 0;` — Corresponding leaderboard id on the platform if needed
- L40 _public member_ `ELeaderboardUpdateMethod UpdateMethod = ELeaderboardUpdateMethod::Force;` — How the leaderboard score will be updated
- L42 _public member_ `ELeaderboardOrderMethod OrderMethod = ELeaderboardOrderMethod::Descending;` — How the leaderboard score will be ordered

#### struct `UE::Online::FLeaderboardsCommonConfig`  
`struct FLeaderboardsCommonConfig`  
_L45-49_
- L47 _public member_ `bool bIsTitleManaged = false;`
- L48 _public member_ `TArray<FLeaderboardDefinition> LeaderboardDefinitions;`

#### struct `UE::Online::FWriteLeaderboardScores`  
`struct FWriteLeaderboardScores`  
_L68-82_
- L70 _public member_ `static constexpr TCHAR Name[] = TEXT("Wri`

#### struct `UE::Online::FWriteLeaderboardScores::Params`  
`struct Params`  
_L72-77_
- L74 _public member_ `FAccountId LocalAccountId;`
- L75 _public member_ `FString BoardName;`
- L76 _public member_ `uint64 Score;`

#### struct `UE::Online::FWriteLeaderboardScores::Result`  
`struct Result`  
_L79-81_

#### class `UE::Online::FLeaderboardsCommon`  
`class FLeaderboardsCommon : public TOnlineComponent<ILeaderboards>`  
_L84-110_
- inherits: `TOnlineComponent<ILeaderboards>`
- L87 _public typedef_ `using Super = TOnlineComponent<ILeaderboards>;`
- L89 _public prototype_ `FLeaderboardsCommon(FOnlineServicesCommon& InServices);`
- L92 _public prototype_ `virtual void Initialize() override;` — TOnlineComponent
- L93 _public prototype_ `virtual void UpdateConfig() override;`
- L94 _public prototype_ `virtual void RegisterCommands() override;`
- L97 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesForUsers> ReadEntriesForUsers(FReadEntriesForUsers::Params&& Params) override;` — ILeaderboards
- L98 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesAroundRank> ReadEntriesAroundRank(FReadEntriesAroundRank::Params&& Params) override;`
- L99 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesAroundUser> ReadEntriesAroundUser(FReadEntriesAroundUser::Params&& Params) override;`
- L102 _public prototype_ `virtual TOnlineAsyncOpHandle<FWriteLeaderboardScores> WriteLeaderboardScores(FWriteLeaderboardScores::Params&& Params);` — Internal use only, for stats common implementation
- L105 _protected prototype_ `void WriteLeaderboardsByStats(const FStatsUpdated& StatsUpdated);`
- L107 _protected member_ `TMap<FString, FLeaderboardDefinition> LeaderboardDefinitions;`
- L108 _protected member_ `FOnlineEventDelegateHandle StatEventHandle;`
- L109 _protected member_ `bool bIsTitleManaged = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L21 _prototype_ `const TCHAR* LexToString(ELeaderboardUpdateMethod Value);` (scope `UE::Online`)
- L22 _prototype_ `void LexFromString(ELeaderboardUpdateMethod& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L30 _prototype_ `const TCHAR* LexToString(ELeaderboardOrderMethod Value);` (scope `UE::Online`)
- L31 _prototype_ `void LexFromString(ELeaderboardOrderMethod& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L51 _namespace_ `namespace Meta` (scope `UE::Online`)
- L112 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/LobbiesCommon.h` (Public)


#### class `UE::Online::FLobbiesCommon`  
`class FLobbiesCommon : public TOnlineComponent<ILobbies>`  
_L14-64_
- inherits: `TOnlineComponent<ILobbies>`
- L17 _public typedef_ `using Super = ILobbies;`
- L19 _public prototype_ `FLobbiesCommon(FOnlineServicesCommon& InServices);`
- L22 _public prototype_ `virtual void Initialize() override;` — TOnlineComponent
- L23 _public prototype_ `virtual void RegisterCommands() override;`
- L26 _public prototype_ `virtual TOnlineAsyncOpHandle<FCreateLobby> CreateLobby(FCreateLobby::Params&& Params) override;` — ILobbies
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FFindLobbies> FindLobbies(FFindLobbies::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FRestoreLobbies> RestoreLobbies(FRestoreLobbies::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FJoinLobby> JoinLobby(FJoinLobby::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FLeaveLobby> LeaveLobby(FLeaveLobby::Params&& Params) override;`
- L31 _public prototype_ `virtual TOnlineAsyncOpHandle<FInviteLobbyMember> InviteLobbyMember(FInviteLobbyMember::Params&& Params) override;`
- L32 _public prototype_ `virtual TOnlineAsyncOpHandle<FDeclineLobbyInvitation> DeclineLobbyInvitation(FDeclineLobbyInvitation::Params&& Params) override;`
- L33 _public prototype_ `virtual TOnlineAsyncOpHandle<FKickLobbyMember> KickLobbyMember(FKickLobbyMember::Params&& Params) override;`
- L34 _public prototype_ `virtual TOnlineAsyncOpHandle<FPromoteLobbyMember> PromoteLobbyMember(FPromoteLobbyMember::Params&& Params) override;`
- L35 _public prototype_ `virtual TOnlineAsyncOpHandle<FModifyLobbySchema> ModifyLobbySchema(FModifyLobbySchema::Params&& Params) override;`
- L36 _public prototype_ `virtual TOnlineAsyncOpHandle<FModifyLobbyJoinPolicy> ModifyLobbyJoinPolicy(FModifyLobbyJoinPolicy::Params&& Params) override;`
- L37 _public prototype_ `virtual TOnlineAsyncOpHandle<FModifyLobbyAttributes> ModifyLobbyAttributes(FModifyLobbyAttributes::Params&& Params) override;`
- L38 _public prototype_ `virtual TOnlineAsyncOpHandle<FModifyLobbyMemberAttributes> ModifyLobbyMemberAttributes(FModifyLobbyMemberAttributes::Params&& Params) override;`
- L39 _public prototype_ `virtual TOnlineResult<FGetPresenceLobby> GetPresenceLobby(FGetPresenceLobby::Params&& Params) override;`
- L40 _public prototype_ `virtual TOnlineResult<FIsPresenceLobby> IsPresenceLobby(FIsPresenceLobby::Params&& Params) override;`
- L41 _public prototype_ `virtual TOnlineResult<FGetJoinedLobbies> GetJoinedLobbies(FGetJoinedLobbies::Params&& Params) override;`
- L42 _public prototype_ `virtual TOnlineResult<FGetReceivedInvitations> GetReceivedInvitations(FGetReceivedInvitations::Params&& Params) override;`
- L44 _public prototype_ `virtual TOnlineEvent<void(const FLobbyJoined&)> OnLobbyJoined() override;`
- L45 _public prototype_ `virtual TOnlineEvent<void(const FLobbyLeft&)> OnLobbyLeft() override;`
- L46 _public prototype_ `virtual TOnlineEvent<void(const FLobbyMemberJoined&)> OnLobbyMemberJoined() override;`
- L47 _public prototype_ `virtual TOnlineEvent<void(const FLobbyMemberLeft&)> OnLobbyMemberLeft() override;`
- L48 _public prototype_ `virtual TOnlineEvent<void(const FLobbyLeaderChanged&)> OnLobbyLeaderChanged() override;`
- L49 _public prototype_ `virtual TOnlineEvent<void(const FLobbySchemaChanged&)> OnLobbySchemaChanged() override;`
- L50 _public prototype_ `virtual TOnlineEvent<void(const FLobbyAttributesChanged&)> OnLobbyAttributesChanged() override;`
- L51 _public prototype_ `virtual TOnlineEvent<void(const FLobbyMemberAttributesChanged&)> OnLobbyMemberAttributesChanged() override;`
- L52 _public prototype_ `virtual TOnlineEvent<void(const FLobbyInvitationAdded&)> OnLobbyInvitationAdded() override;`
- L53 _public prototype_ `virtual TOnlineEvent<void(const FLobbyInvitationRemoved&)> OnLobbyInvitationRemoved() override;`
- L54 _public prototype_ `virtual TOnlineEvent<void(const FUILobbyJoinRequested&)> OnUILobbyJoinRequested() override;`
- L58 _protected prototype_ `TOnlineAsyncOpHandle<FFunctionalTestLobbies> FunctionalTest(FFunctionalTestLobbies::Params&& Params);`
- L61 _protected member_ `TMap<FAccountId, FLobbyId> PresenceLobbiesUserMap;`
- L62 _protected member_ `TSharedRef<FSchemaRegistry> SchemaRegistry;`
- L63 _protected member_ `FLobbyEvents LobbyEvents;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/LobbiesCommonTypes.h` (Public)


#### struct `UE::Online::FLobbyEvents`  
`struct FLobbyEvents final`  
_L22-35_
- L24 _public member_ `TOnlineEventCallable<void(const FLobbyJoined&)> OnLobbyJoined;`
- L25 _public member_ `TOnlineEventCallable<void(const FLobbyLeft&)> OnLobbyLeft;`
- L26 _public member_ `TOnlineEventCallable<void(const FLobbyMemberJoined&)> OnLobbyMemberJoined;`
- L27 _public member_ `TOnlineEventCallable<void(const FLobbyMemberLeft&)> OnLobbyMemberLeft;`
- L28 _public member_ `TOnlineEventCallable<void(const FLobbyLeaderChanged&)> OnLobbyLeaderChanged;`
- L29 _public member_ `TOnlineEventCallable<void(const FLobbySchemaChanged&)> OnLobbySchemaChanged;`
- L30 _public member_ `TOnlineEventCallable<void(const FLobbyAttributesChanged&)> OnLobbyAttributesChanged;`
- L31 _public member_ `TOnlineEventCallable<void(const FLobbyMemberAttributesChanged&)> OnLobbyMemberAttributesChanged;`
- L32 _public member_ `TOnlineEventCallable<void(const FLobbyInvitationAdded&)> OnLobbyInvitationAdded;`
- L33 _public member_ `TOnlineEventCallable<void(const FLobbyInvitationRemoved&)> OnLobbyInvitationRemoved;`
- L34 _public member_ `TOnlineEventCallable<void(const FUILobbyJoinRequested&)> OnUILobbyJoinRequested;`

#### struct `UE::Online::WhenAll::FWhenAllState`  
`struct FWhenAllState`  
_L41-46_
- L43 _public member_ `TArray<TFuture<AwaitedType>> Futures;`
- L44 _public member_ `TArray<AwaitedType> Results;`
- L45 _public member_ `TPromise<TArray<AwaitedType>> FinalPromise;`

#### class `UE::Online::FSchemaCategoryInstanceLobbySnapshotAccessor`  
`class FSchemaCategoryInstanceLobbySnapshotAccessor`  
_L77-92_
- desc: Accessor for using the public lobby attributes directly when committing schema changes.
- L80 _public function_ `FSchemaCategoryInstanceLobbySnapshotAccessor(TMap<FSchemaAttributeId, FSchemaVariant>& InClientSnapshot) : ClientSnapshot(InClientSnapshot)`
- L85 _public function_ `TMap<FSchemaAttributeId, FSchemaVariant>& GetMutableClientSnapshot()`
- L91 _private member_ `TMap<FSchemaAttributeId, FSchemaVariant>& ClientSnapshot;`

#### struct `UE::Online::FLobbyInternal`  
`struct FLobbyInternal : public FLobby`  
_L102-111_
- inherits: `FLobby`
- desc: Lobby data structure as seen by the client with additional fields for internal use.
- L104 _public function_ `FLobbyInternal(const TSharedRef<const FSchemaRegistry>& SchemaRegistry) : FLobby() , SchemaData(FSchemaId(), LobbyBaseSchemaId, LobbySchemaCategoryId, SchemaRegistry, Attributes)`
- L110 _public member_ `FLobbiesSchemaCategoryInstance SchemaData;`

#### struct `UE::Online::FLobbyMemberInternal`  
`struct FLobbyMemberInternal : public FLobbyMember`  
_L116-125_
- inherits: `FLobbyMember`
- desc: Lobby member data structure as seen by the client with additional fields for internal use.
- L118 _public function_ `FLobbyMemberInternal(const TSharedRef<const FSchemaRegistry>& SchemaRegistry, const FSchemaId& DerivedSchemaId = FSchemaId()) : FLobbyMember() , SchemaData(DerivedSchemaId, LobbyBaseSchemaId, LobbyMemberSchemaCategoryId, SchemaRegistry, Attributes)`
- L124 _public member_ `FLobbiesSchemaCategoryInstance SchemaData;`

#### struct `UE::Online::FLobbyClientAttributeChanges`  
`struct FLobbyClientAttributeChanges`  
_L127-133_
- L130 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> UpdatedAttributes;` — New or changed attributes.
- L132 _public member_ `TSet<FSchemaAttributeId> RemovedAttributes;` — Attributes to be removed.

#### struct `UE::Online::FLobbyClientMemberAttributeChanges`  
`struct FLobbyClientMemberAttributeChanges`  
_L135-141_
- L138 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> UpdatedAttributes;` — New or changed attributes.
- L140 _public member_ `TSet<FSchemaAttributeId> RemovedAttributes;` — Attributes to be removed.

#### struct `UE::Online::FLobbyClientChanges`  
`struct FLobbyClientChanges`  
_L146-164_
- desc: Local changes to a lobby to be applied to the service.
- L149 _public member_ `TOptional<FName> LocalName;` — Local name for the lobby.
- L151 _public member_ `TOptional<ELobbyJoinPolicy> JoinPolicy;` — Setting for new join policy.
- L153 _public member_ `TOptional<FAccountId> OwnerAccountId;` — Setting for lobby ownership change.
- L155 _public member_ `TOptional<FSchemaId> LobbySchema;` — Setting for lobby schema change.
- L157 _public member_ `TOptional<FLobbyClientAttributeChanges> Attributes;` — Setting for changing lobby attributes.
- L159 _public member_ `TOptional<FLobbyClientMemberAttributeChanges> MemberAttributes;` — Setting for adding or updating the local user.
- L161 _public member_ `TOptional<ELobbyMemberLeaveReason> LocalUserLeaveReason;` — Setting for removing the local user.
- L163 _public member_ `TOptional<FAccountId> KickedTargetMember;` — Setting for kicking the target lobby member.

#### struct `UE::Online::FLobbyClientServiceChanges`  
`struct FLobbyClientServiceChanges`  
_L169-185_
- desc: Local changes to a lobby translated to the changes which will be applied to the service.
- L172 _public member_ `TOptional<ELobbyJoinPolicy> JoinPolicy;` — Setting for new join policy.
- L174 _public member_ `TOptional<FAccountId> OwnerAccountId;` — Setting for lobby ownership change.
- L176 _public member_ `TOptional<FAccountId> KickedTargetMember;` — Target member to be kicked.
- L178 _public member_ `TMap<FSchemaServiceAttributeId, FSchemaServiceAttributeData> UpdatedAttributes;` — Added or changed lobby attributes and their values.
- L180 _public member_ `TSet<FSchemaServiceAttributeId> RemovedAttributes;` — Removed lobby attribute ids.
- L182 _public member_ `TMap<FSchemaServiceAttributeId, FSchemaServiceAttributeData> UpdatedMemberAttributes;` — Added or changed lobby member attributes and their values.
- L184 _public member_ `TSet<FSchemaServiceAttributeId> RemovedMemberAttributes;` — Removed lobby member attribute ids.

#### struct `UE::Online::FLobbyServiceSnapshot`  
`struct FLobbyServiceSnapshot`  
_L190-197_
- desc: Full snapshot of lobby data excluding the individual member attributes
- L192 _public member_ `FAccountId OwnerAccountId;`
- L193 _public member_ `int32 MaxMembers;`
- L194 _public member_ `ELobbyJoinPolicy JoinPolicy;`
- L195 _public member_ `FSchemaServiceSnapshot SchemaServiceSnapshot;`
- L196 _public member_ `TSet<FAccountId> Members;`

#### struct `UE::Online::FLobbyMemberServiceSnapshot`  
`struct FLobbyMemberServiceSnapshot`  
_L202-206_
- desc: Full snapshot of a lobby member.
- L204 _public member_ `FAccountId AccountId;`
- L205 _public member_ `FSchemaServiceSnapshot SchemaServiceSnapshot;`

#### struct `UE::Online::FLobbyClientDataPrepareServiceSnapshot`  
`struct FLobbyClientDataPrepareServiceSnapshot`  
_L208-223_

#### struct `UE::Online::FLobbyClientDataPrepareServiceSnapshot::Params`  
`struct Params`  
_L210-218_
- L213 _public member_ `FLobbyServiceSnapshot LobbySnapshot;` — Full snapshot from the service.
- L215 _public member_ `TMap<FAccountId, FLobbyMemberServiceSnapshot> LobbyMemberSnapshots;` — Full snapshot for each member from the service.
- L217 _public member_ `TMap<FAccountId, ELobbyMemberLeaveReason> LeaveReasons;` — Any leaving members notified by the service.

#### struct `UE::Online::FLobbyClientDataPrepareServiceSnapshot::Result`  
`struct Result`  
_L220-222_

#### struct `UE::Online::FLobbyClientDataCommitServiceSnapshot`  
`struct FLobbyClientDataCommitServiceSnapshot`  
_L225-238_

#### struct `UE::Online::FLobbyClientDataCommitServiceSnapshot::Params`  
`struct Params`  
_L227-231_
- L230 _public member_ `FLobbyEvents* LobbyEvents = nullptr;` — Notifier for signaling client events on data change.

#### struct `UE::Online::FLobbyClientDataCommitServiceSnapshot::Result`  
`struct Result`  
_L233-237_
- L236 _public member_ `TArray<FAccountId> LeavingLocalMembers;` — List of local members leaving the lobby.

#### struct `UE::Online::FLobbyClientDataPrepareClientChanges`  
`struct FLobbyClientDataPrepareClientChanges`  
_L240-255_

#### struct `UE::Online::FLobbyClientDataPrepareClientChanges::Params`  
`struct Params`  
_L242-248_
- L245 _public member_ `FAccountId LocalAccountId;` — The local user who is making the changes.
- L247 _public member_ `FLobbyClientChanges ClientChanges;` — Changes to be applied to service data.

#### struct `UE::Online::FLobbyClientDataPrepareClientChanges::Result`  
`struct Result`  
_L250-254_
- L253 _public member_ `FLobbyClientServiceChanges ServiceChanges;` — Translated changes to be applied to the service.

#### struct `UE::Online::FLobbyClientDataCommitClientChanges`  
`struct FLobbyClientDataCommitClientChanges`  
_L257-270_

#### struct `UE::Online::FLobbyClientDataCommitClientChanges::Params`  
`struct Params`  
_L259-263_
- L262 _public member_ `FLobbyEvents* LobbyEvents = nullptr;` — Notifier for signaling client events on data change.

#### struct `UE::Online::FLobbyClientDataCommitClientChanges::Result`  
`struct Result`  
_L265-269_
- L268 _public member_ `TArray<FAccountId> LeavingLocalMembers;` — List of local members leaving the lobby.

#### struct `UE::Online::FLobbyClientData`  
`struct FLobbyClientData final`  
_L273-360_
- desc: Lobby data as seen by the client.
- L276 _public prototype_ `FLobbyClientData(FLobbyId LobbyId, const TSharedRef<const FSchemaRegistry>& InSchemaRegistry);`
- L278 _public function_ `TSharedRef<const FLobby> GetPublicDataPtr() const`
- L279 _public function_ `const FLobby& GetPublicData() const`
- L281 _public prototype_ `TSharedPtr<const FLobbyMemberInternal> GetMemberData(FAccountId MemberAccountId) const;`
- L288 _public prototype_ `TOnlineResult<FLobbyClientDataPrepareServiceSnapshot> PrepareServiceSnapshot(FLobbyClientDataPrepareServiceSnapshot::Params&& Params) const;` — Apply updated lobby data and generate changes. The LeaveReason provides context for members who have left since the most recent snapshot. Changing a lobby generates events for the local client.
- L289 _public prototype_ `FLobbyClientDataCommitServiceSnapshot::Result CommitServiceSnapshot(FLobbyClientDataCommitServiceSnapshot::Params&& Params);`
- L291 _public prototype_ `TOnlineResult<FLobbyClientDataPrepareClientChanges> PrepareClientChanges(FLobbyClientDataPrepareClientChanges::Params&& Params) const;`
- L292 _public prototype_ `FLobbyClientDataCommitClientChanges::Result CommitClientChanges(FLobbyClientDataCommitClientChanges::Params&& Params);`
- L295 _private prototype_ `void ResetPreparedChanges() const;`
- L296 _private prototype_ `void AddMember(const TSharedRef<FLobbyMemberInternal>& Member);`
- L297 _private prototype_ `void RemoveMember(const TSharedRef<FLobbyMemberInternal>& Member);`
- L340 _private member_ `TSharedRef<const FSchemaRegistry> SchemaRegistry;` — The schema registry is needed to initialize new members.
- L346 _private member_ `TSharedRef<FLobbyInternal> InternalPublicData;` — The shared pointer given back to user code with lobby operation results and notifications. Any changes to this data are immediately available to users.
- L349 _private member_ `TMap<FAccountId, TSharedRef<FLobbyMemberInternal>> MemberDataStorage;` — Mutable lobby member data storage.
- L355 _private member_ `TSet<FAccountId> LocalMembers;` — Keep track of which members are local to the client. When all local members have been removed all members will be removed.
- L358 _private member_ `mutable TOptional<FPreparedServiceChanges> PreparedServiceChanges;` — Updates which have been applied but not yet committed.
- L359 _private member_ `mutable TOptional<FPreparedClientChanges> PreparedClientChanges;`

#### struct `UE::Online::FLobbyClientData::FPreparedServiceChanges`  
`struct FPreparedServiceChanges`  
_L299-313_
- L302 _public member_ `TOptional<FAccountId> OwnerAccountId;` — Set when there is a change in lobby ownership.
- L304 _public member_ `TOptional<int32> MaxMembers;` — Set when there is a change in max members.
- L306 _public member_ `TOptional<ELobbyJoinPolicy> JoinPolicy;` — Set when there is a change in join policy.
- L308 _public member_ `TArray<TSharedRef<FLobbyMemberInternal>> NewMemberDataStorage;` — Members who did not already have a local representation.
- L310 _public member_ `TArray<TSharedRef<FLobbyMemberInternal>> UpdatedMemberDataStorage;` — Members who already exist in the lobby.
- L312 _public member_ `TArray<TPair<TSharedRef<FLobbyMemberInternal>, ELobbyMemberLeaveReason>> LeavingMembers;` — Any leaving members and their reason.

#### struct `UE::Online::FLobbyClientData::FPreparedClientChanges`  
`struct FPreparedClientChanges`  
_L315-335_
- L318 _public member_ `FAccountId LocalAccountId;` — The local user associated with the change.
- L320 _public member_ `TOptional<FName> LocalName;` — Local name for the lobby.
- L322 _public member_ `TOptional<ELobbyJoinPolicy> JoinPolicy;` — Setting for new join policy.
- L324 _public member_ `TOptional<FAccountId> OwnerAccountId;` — Setting for lobby ownership change.
- L326 _public member_ `TOptional<FAccountId> KickedTargetMember;` — Target member to be kicked.
- L328 _public member_ `TSharedPtr<FLobbyMemberInternal> JoiningLocalMember;` — Access to local member when joining and assigning initial attributes.
- L330 _public member_ `TSharedPtr<FLobbyMemberInternal> UpdatedLocalMember;` — Access to local member when updating attributes.
- L332 _public member_ `TOptional<ELobbyMemberLeaveReason> LocalUserLeaveReason;` — Reason to be set when the local member is leaving.
- L334 _public member_ `bool bLobbyAttributesChanged = false;` — Whether there are waiting lobby attribute changes to be committed.

#### struct `UE::Online::FFunctionalTestLobbies`  
`struct FFunctionalTestLobbies`  
_L363-374_
- L365 _public member_ `static constexpr TCHAR Name[] = TEXT("Fun`

#### struct `UE::Online::FFunctionalTestLobbies::Params`  
`struct Params`  
_L367-369_

#### struct `UE::Online::FFunctionalTestLobbies::Result`  
`struct Result`  
_L371-373_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L14 _macro_ `#define LOBBIES_FUNCTIONAL_TEST_ENABLED !UE_BUILD_SHIPPING`
- L16 _externvar_ `extern FSchemaId LobbyBaseSchemaId;` (scope `UE::Online`)
- L17 _externvar_ `extern FSchemaCategoryId LobbySchemaCategoryId;` (scope `UE::Online`)
- L18 _externvar_ `extern FSchemaCategoryId LobbyMemberSchemaCategoryId;` (scope `UE::Online`)
- L39 _function_ `template <typename AwaitedType> TFuture<TArray<AwaitedType>> WhenAll(TArray<TFuture<AwaitedType>>&& Futures)` (scope `UE::Online`) — Todo: put this somewhere else
- L60 _function_ `` (scope `UE::Online::WhenAll`)
- L97 _typedef_ `using FLobbiesSchemaCategoryInstance = TSchemaCategoryInstance<FSchemaCategoryInstanceLobbySnapshotAccessor>;` (scope `UE::Online`) — Alias for schema category instance used by lobby and lobby member data.
- L377 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/NboSerializerCommonSvc.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Online` (scope `UE`)
- L18 _namespace_ `namespace NboSerializerCommonSvc` (scope `UE::Online`)
- L22 _prototype_ `void SerializeToBuffer(FNboSerializeToBuffer& Packet, const FSchemaVariant& Data);` (scope `UE::Online::NboSerializerCommonSvc`)
- L23 _prototype_ `void SerializeToBuffer(FNboSerializeToBuffer& Packet, const FCustomSessionSetting& CustomSessionSetting);` (scope `UE::Online::NboSerializerCommonSvc`)
- L24 _prototype_ `void SerializeToBuffer(FNboSerializeToBuffer& Packet, const FCustomSessionSettingsMap& CustomSessionSettingsMap);` (scope `UE::Online::NboSerializerCommonSvc`)
- L25 _prototype_ `void SerializeToBuffer(FNboSerializeToBuffer& Packet, const FSessionSettings& SessionSettings);` (scope `UE::Online::NboSerializerCommonSvc`)
- L26 _prototype_ `void SerializeToBuffer(FNboSerializeToBuffer& Packet, const FSessionCommon& Session);` (scope `UE::Online::NboSerializerCommonSvc`)
- L30 _prototype_ `void SerializeFromBuffer(FNboSerializeFromBuffer& Packet, FSchemaVariant& Data);` (scope `UE::Online::NboSerializerCommonSvc`)
- L31 _prototype_ `void SerializeFromBuffer(FNboSerializeFromBuffer& Packet, FCustomSessionSetting& CustomSessionSetting);` (scope `UE::Online::NboSerializerCommonSvc`)
- L32 _prototype_ `void SerializeFromBuffer(FNboSerializeFromBuffer& Packet, FCustomSessionSettingsMap& CustomSessionSettingsMap);` (scope `UE::Online::NboSerializerCommonSvc`)
- L33 _prototype_ `void SerializeFromBuffer(FNboSerializeFromBuffer& Packet, FSessionSettings& SessionSettings);` (scope `UE::Online::NboSerializerCommonSvc`)
- L34 _prototype_ `void SerializeFromBuffer(FNboSerializeFromBuffer& Packet, FSessionCommon& Session);` (scope `UE::Online::NboSerializerCommonSvc`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineAsyncOp.h` (Public)


#### enum `UE::Online::EOnlineAsyncExecutionPolicy`  
`enum class EOnlineAsyncExecutionPolicy : uint8`  
_L25-32_
- L27 _public enumerator_ `RunOnGameThread` — Run on the game thread, will execute immediately if we are already on the game thread
- L28 _public enumerator_ `RunOnNextTick` — Run on the game thread next time we tick
- L29 _public enumerator_ `RunOnThreadPool` — Run on a specified thread pool
- L30 _public enumerator_ `RunOnTaskGraph` — Run on the task graph
- L31 _public enumerator_ `RunImmediately` — Call immediately, in the current thread

#### class `UE::Online::FOnlineAsyncExecutionPolicy`  
`class FOnlineAsyncExecutionPolicy`  
_L34-52_
- L37 _public function_ `FOnlineAsyncExecutionPolicy(EOnlineAsyncExecutionPolicy InExecutionPolicy) : ExecutionPolicy(InExecutionPolicy)`
- L42 _public function_ `static FOnlineAsyncExecutionPolicy RunOnGameThread()`
- L43 _public function_ `static FOnlineAsyncExecutionPolicy RunOnNextTick()`
- L44 _public function_ `static FOnlineAsyncExecutionPolicy RunOnThreadPool()` — TODO: allow thread pool to be specified
- L45 _public function_ `static FOnlineAsyncExecutionPolicy RunOnTaskGraph()`
- L46 _public function_ `static FOnlineAsyncExecutionPolicy RunImmediately()`
- L48 _public function_ `const EOnlineAsyncExecutionPolicy& GetExecutionPolicy() const`
- L51 _private member_ `EOnlineAsyncExecutionPolicy ExecutionPolicy;`

#### class `UE::Online::TDefaultErrorResultInternal`  
`template <typename Result> class TDefaultErrorResultInternal : public TResult<Result, FOnlineError>`  
_L56-65_
- inherits: `TResult<Result,FOnlineError>`
- desc: For use when we need to put a TOnlineResult in an object that needs to be default constructed such as a TPromise
- L61 _public function_ `TDefaultErrorResultInternal() : TResult<Result, FOnlineError>(Errors::Unknown())`

#### class `UE::Online::TDefaultErrorResult`  
`template <typename OpType> class TDefaultErrorResult : public TOnlineResult<OpType>`  
_L68-77_
- inherits: `TOnlineResult<OpType>`
- L73 _public function_ `TDefaultErrorResult() : TOnlineResult<OpType>(Errors::Unknown())`

#### struct `UE::Online::TContinuationResult`  
`template <typename TResultType> struct TContinuationResult`  
_L80-97_
- L83 _public function_ `static TContinuationResult Repeat()`
- L84 _public function_ `static TContinuationResult Complete(TResultType&& InResult)`
- L85 _public function_ `bool IsComplete() const`
- L86 _public function_ `TResultType& GetResult()`
- L87 _public function_ `const TResultType& GetResult() const`
- L90 _private function_ `TContinuationResult()`
- L93 _private function_ `TContinuationResult(TResultType&& InResult) : Result(InResult)`
- L96 _private member_ `TOptional<TResultType> Result;`
- L104 _public function_ `static TContinuationResult Complete()`
- L112 _private function_ `TContinuationResult(const FIsCompleteTag&) : bIsComplete(true)`
- L115 _private member_ `bool bIsComplete = false;`

#### struct `UE::Online::TContinuationResult`  
`template <> struct TContinuationResult<void>`  
_L100-116_
- L83 _public function_ `static TContinuationResult Repeat()`
- L84 _public function_ `static TContinuationResult Complete(TResultType&& InResult)`
- L85 _public function_ `bool IsComplete() const`
- L86 _public function_ `TResultType& GetResult()`
- L87 _public function_ `const TResultType& GetResult() const`
- L90 _private function_ `TContinuationResult()`
- L93 _private function_ `TContinuationResult(TResultType&& InResult) : Result(InResult)`
- L96 _private member_ `TOptional<TResultType> Result;`
- L104 _public function_ `static TContinuationResult Complete()`
- L112 _private function_ `TContinuationResult(const FIsCompleteTag&) : bIsComplete(true)`
- L115 _private member_ `bool bIsComplete = false;`

#### struct `UE::Online::TContinuationResult::FIsCompleteTag`  
`struct FIsCompleteTag`  
_L107-107_

#### struct `UE::Online::TContinuationResultType`  
`template <typename T> struct TContinuationResultType`  
_L119-122_
- L121 _public typedef_ `using ResultType = T;`

#### struct `UE::Online::TContinuationResultType`  
`template <typename T> struct TContinuationResultType<TContinuationResult<T>>`  
_L125-128_
- L121 _public typedef_ `using ResultType = T;`

#### class `UE::Online::Private::FOnlineOperationData`  
`class FOnlineOperationData`  
_L149-248_
- desc: Map of (TypeName,Key)->(data of any Type)
- L153 _public function_ `template <typename T> void Set(const FString& Key, T&& InData)`
- L159 _public function_ `template <typename T> void Set(const FString& Key, const T& InData)`
- L165 _public function_ `template <typename T> const T* Get(const FString& Key) const`
- L176 _public function_ `template <typename T> T* Get(const FString& Key)`
- L247 _private member_ `TMap<FOperationDataKey, TUniquePtr<IData>> Data;`

#### struct `UE::Online::Private::FOnlineOperationData::FOperationDataKey`  
`struct FOperationDataKey`  
_L186-195_
- L188 _public member_ `FOnlineTypeName TypeName;`
- L189 _public member_ `FString Key;`
- L191 _public function_ `bool operator==(const FOperationDataKey& Other) const`

#### class `UE::Online::Private::FOnlineOperationData::IData`  
`class IData`  
_L198-215_
- L201 _public prototype_ `virtual ~IData() = default;`
- L202 _public prototype_ `virtual FOnlineTypeName GetTypeName() = 0;`
- L203 _public prototype_ `virtual void* GetData() = 0;`
- L206 _public function_ `template <typename T> const T* Get()`

#### class `UE::Online::Private::FOnlineOperationData::TData`  
`template <typename T> class TData : public IData`  
_L218-243_
- inherits: `IData`
- L221 _public function_ `TData(const T& InData) : Data(InData)`
- L226 _public function_ `TData(T&& InData) : Data(MoveTemp(InData))`
- L231 _public function_ `virtual FOnlineTypeName GetTypeName() override`
- L236 _public function_ `virtual void* GetData() override`
- L242 _private member_ `T Data;`

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraitsHelper2`  
`template <typename... Params> struct TOnlineAsyncOpCallableTraitsHelper2`  
_L257-259_
- L264 _public typedef_ `using ParamType = void;`
- L265 _public typedef_ `using ResultType = TResultType;`
- L266 _public member_ `static constexpr bool bAsyncResult = false;`
- L267 _public member_ `static constexpr bool bRequiresPromise = false;`
- L273 _public typedef_ `using ParamType = TParamType;`
- L284 _public member_ `static constexpr bool bAsyncResult = true;`
- L303 _public member_ `static constexpr bool bRequiresPromise = true;`

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraitsHelper2`  
`template <typename TResultType, typename OpType> struct TOnlineAsyncOpCallableTraitsHelper2<TResultType, OpType&>`  
_L262-268_
- L264 _public typedef_ `using ParamType = void;`
- L265 _public typedef_ `using ResultType = TResultType;`
- L266 _public member_ `static constexpr bool bAsyncResult = false;`
- L267 _public member_ `static constexpr bool bRequiresPromise = false;`
- L273 _public typedef_ `using ParamType = TParamType;`
- L284 _public member_ `static constexpr bool bAsyncResult = true;`
- L303 _public member_ `static constexpr bool bRequiresPromise = true;`

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraitsHelper2`  
`template <typename TResultType, typename OpType, typename TParamType> struct TOnlineAsyncOpCallableTraitsHelper2<TResultType, OpType&, TParamType>`  
_L271-277_
- L264 _public typedef_ `using ParamType = void;`
- L265 _public typedef_ `using ResultType = TResultType;`
- L266 _public member_ `static constexpr bool bAsyncResult = false;`
- L267 _public member_ `static constexpr bool bRequiresPromise = false;`
- L273 _public typedef_ `using ParamType = TParamType;`
- L284 _public member_ `static constexpr bool bAsyncResult = true;`
- L303 _public member_ `static constexpr bool bRequiresPromise = true;`

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraitsHelper2`  
`template <typename TResultType, typename OpType> struct TOnlineAsyncOpCallableTraitsHelper2<TFuture<TResultType>, OpType&>`  
_L280-286_
- L264 _public typedef_ `using ParamType = void;`
- L265 _public typedef_ `using ResultType = TResultType;`
- L266 _public member_ `static constexpr bool bAsyncResult = false;`
- L267 _public member_ `static constexpr bool bRequiresPromise = false;`
- L273 _public typedef_ `using ParamType = TParamType;`
- L284 _public member_ `static constexpr bool bAsyncResult = true;`
- L303 _public member_ `static constexpr bool bRequiresPromise = true;`

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraitsHelper2`  
`template <typename TResultType, typename OpType, typename TParamType> struct TOnlineAsyncOpCallableTraitsHelper2<TFuture<TResultType>, OpType&, TParamType>`  
_L289-295_
- L264 _public typedef_ `using ParamType = void;`
- L265 _public typedef_ `using ResultType = TResultType;`
- L266 _public member_ `static constexpr bool bAsyncResult = false;`
- L267 _public member_ `static constexpr bool bRequiresPromise = false;`
- L273 _public typedef_ `using ParamType = TParamType;`
- L284 _public member_ `static constexpr bool bAsyncResult = true;`
- L303 _public member_ `static constexpr bool bRequiresPromise = true;`

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraitsHelper2`  
`template <typename TResultType, typename OpType> struct TOnlineAsyncOpCallableTraitsHelper2<void, OpType&, TPromise<TResultType>&&>`  
_L298-304_
- L264 _public typedef_ `using ParamType = void;`
- L265 _public typedef_ `using ResultType = TResultType;`
- L266 _public member_ `static constexpr bool bAsyncResult = false;`
- L267 _public member_ `static constexpr bool bRequiresPromise = false;`
- L273 _public typedef_ `using ParamType = TParamType;`
- L284 _public member_ `static constexpr bool bAsyncResult = true;`
- L303 _public member_ `static constexpr bool bRequiresPromise = true;`

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraitsHelper2`  
`template <typename TResultType, typename OpType, typename TParamType> struct TOnlineAsyncOpCallableTraitsHelper2<void, OpType&, TParamType, TPromise<TResultType>&&>`  
_L307-313_
- L264 _public typedef_ `using ParamType = void;`
- L265 _public typedef_ `using ResultType = TResultType;`
- L266 _public member_ `static constexpr bool bAsyncResult = false;`
- L267 _public member_ `static constexpr bool bRequiresPromise = false;`
- L273 _public typedef_ `using ParamType = TParamType;`
- L284 _public member_ `static constexpr bool bAsyncResult = true;`
- L303 _public member_ `static constexpr bool bRequiresPromise = true;`

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraitsHelper`  
`template <typename CallableType> struct TOnlineAsyncOpCallableTraitsHelper`  
_L316-318_

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraitsHelper`  
`template <typename ReturnType, typename... ParamTypes> struct TOnlineAsyncOpCallableTraitsHelper<ReturnType(ParamTypes...)> : public TOnlineAsyncOpCallableTraitsHelper2<ReturnType, ParamTypes...>`  
_L321-324_
- inherits: `TOnlineAsyncOpCallableTraitsHelper2<ReturnType,ParamTypes...>`

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraitsHelper`  
`template <typename ReturnType, typename ObjectType, typename... ParamTypes> struct TOnlineAsyncOpCallableTraitsHelper<ReturnType(ObjectType::*)(ParamTypes...)> : public TOnlineAsyncOpCallableTraitsHelper2<ReturnType, ParamTypes...>`  
_L327-330_
- inherits: `TOnlineAsyncOpCallableTraitsHelper2<ReturnType,ParamTypes...>`

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraitsHelper`  
`template <typename ReturnType, typename ObjectType, typename... ParamTypes> struct TOnlineAsyncOpCallableTraitsHelper<ReturnType(ObjectType::*)(ParamTypes...) const> : public TOnlineAsyncOpCallableTraitsHelper2<ReturnType, ParamTypes...>`  
_L333-336_
- inherits: `TOnlineAsyncOpCallableTraitsHelper2<ReturnType,ParamTypes...>`

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraits`  
`template <typename CallableType, typename = void> struct TOnlineAsyncOpCallableTraits`  
_L339-341_

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraits`  
`template <typename CallableFunction> struct TOnlineAsyncOpCallableTraits<CallableFunction, std::enable_if_t<std::is_function_v<std::remove_pointer_t<CallableFunction>>, void>> : public TOnlineAsyncOpCallableTraitsHelper<CallableFunction>`  
_L345-348_
- inherits: `TOnlineAsyncOpCallableTraitsHelper<CallableFunction>`
- desc: function pointers

#### struct `UE::Online::Private::TOnlineAsyncOpCallableTraits`  
`template <typename CallableObject> struct TOnlineAsyncOpCallableTraits<CallableObject, std::enable_if_t<!std::is_function_v<std::remove_pointer_t<CallableObject>>, void>> : public TOnlineAsyncOpCallableTraitsHelper<decltype(&std::remove_reference_t<CallableObject>::operator())>`  
_L352-355_
- inherits: `TOnlineAsyncOpCallableTraitsHelper<decltype(&std::remove_reference_t<CallableObject>::operator())>`
- desc: lambdas, TFunction, functor objects (anything with operator())

#### class `UE::Online::Private::IStep`  
`class IStep`  
_L358-364_
- L361 _public prototype_ `virtual ~IStep() = default;`
- L362 _public prototype_ `virtual const FOnlineAsyncExecutionPolicy& GetExecutionPolicy() const = 0;`
- L363 _public prototype_ `virtual void Execute() = 0;`

#### class `UE::Online::Private::TStep`  
`template <typename ResultType> class TStep : public IStep`  
_L367-503_
- inherits: `IStep`
- L370 _public function_ `TStep(FOnlineAsyncExecutionPolicy&& InExecutionPolicy) : ExecutionPolicy(MoveTemp(InExecutionPolicy))`
- L375 _public function_ `~TStep()`
- L384 _public function_ `template <typename OpType, typename LastResultType, typename CallableType> void SetExecFunction(TOnlineAsyncOp<OpType>& InOperation, LastResultType&& InLastResult, CallableType&& InCallable)`
- L429 _public function_ `template <typename OpType, typename CallableType> void SetExecFunction(TOnlineAsyncOp<OpType>& InOperation, CallableType&& InCallable)`
- L473 _public function_ `virtual const FOnlineAsyncExecutionPolicy& GetExecutionPolicy() const override`
- L478 _public function_ `virtual void Execute() override`
- L485 _public function_ `ResultType& GetResultRef()`
- L492 _private function_ `template<typename... ArgTypes> void EmplaceResult(ArgTypes&&... Args)`
- L499 _private member_ `FOnlineAsyncExecutionPolicy ExecutionPolicy;`
- L500 _private member_ `TUniqueFunction<void()> ExecFunction;`
- L501 _private member_ `TTypeCompatibleBytes<ResultType> Result;`
- L502 _private member_ `bool bResultSet = false;`

#### class `UE::Online::Private::TStep`  
`template <> class TStep<void> : public IStep`  
_L507-585_
- inherits: `IStep`
- L370 _public function_ `TStep(FOnlineAsyncExecutionPolicy&& InExecutionPolicy) : ExecutionPolicy(MoveTemp(InExecutionPolicy))`
- L375 _public function_ `~TStep()`
- L384 _public function_ `template <typename OpType, typename LastResultType, typename CallableType> void SetExecFunction(TOnlineAsyncOp<OpType>& InOperation, LastResultType&& InLastResult, CallableType&& InCallable)`
- L429 _public function_ `template <typename OpType, typename CallableType> void SetExecFunction(TOnlineAsyncOp<OpType>& InOperation, CallableType&& InCallable)`
- L473 _public function_ `virtual const FOnlineAsyncExecutionPolicy& GetExecutionPolicy() const override`
- L478 _public function_ `virtual void Execute() override`
- L485 _public function_ `ResultType& GetResultRef()`
- L492 _private function_ `template<typename... ArgTypes> void EmplaceResult(ArgTypes&&... Args)`
- L499 _private member_ `FOnlineAsyncExecutionPolicy ExecutionPolicy;`
- L500 _private member_ `TUniqueFunction<void()> ExecFunction;`
- L501 _private member_ `TTypeCompatibleBytes<ResultType> Result;`
- L502 _private member_ `bool bResultSet = false;`

#### class `UE::Online::Private::TStep`  
`template <typename ResultType> class TStep<TContinuationResult<ResultType>> : public IStep`  
_L588-768_
- inherits: `IStep`
- L370 _public function_ `TStep(FOnlineAsyncExecutionPolicy&& InExecutionPolicy) : ExecutionPolicy(MoveTemp(InExecutionPolicy))`
- L375 _public function_ `~TStep()`
- L384 _public function_ `template <typename OpType, typename LastResultType, typename CallableType> void SetExecFunction(TOnlineAsyncOp<OpType>& InOperation, LastResultType&& InLastResult, CallableType&& InCallable)`
- L429 _public function_ `template <typename OpType, typename CallableType> void SetExecFunction(TOnlineAsyncOp<OpType>& InOperation, CallableType&& InCallable)`
- L473 _public function_ `virtual const FOnlineAsyncExecutionPolicy& GetExecutionPolicy() const override`
- L478 _public function_ `virtual void Execute() override`
- L485 _public function_ `ResultType& GetResultRef()`
- L492 _private function_ `template<typename... ArgTypes> void EmplaceResult(ArgTypes&&... Args)`
- L499 _private member_ `FOnlineAsyncExecutionPolicy ExecutionPolicy;`
- L500 _private member_ `TUniqueFunction<void()> ExecFunction;`
- L501 _private member_ `TTypeCompatibleBytes<ResultType> Result;`
- L502 _private member_ `bool bResultSet = false;`

#### class `UE::Online::Private::TStep`  
`template <> class TStep<TContinuationResult<void>> : public IStep`  
_L771-880_
- inherits: `IStep`
- L370 _public function_ `TStep(FOnlineAsyncExecutionPolicy&& InExecutionPolicy) : ExecutionPolicy(MoveTemp(InExecutionPolicy))`
- L375 _public function_ `~TStep()`
- L384 _public function_ `template <typename OpType, typename LastResultType, typename CallableType> void SetExecFunction(TOnlineAsyncOp<OpType>& InOperation, LastResultType&& InLastResult, CallableType&& InCallable)`
- L429 _public function_ `template <typename OpType, typename CallableType> void SetExecFunction(TOnlineAsyncOp<OpType>& InOperation, CallableType&& InCallable)`
- L473 _public function_ `virtual const FOnlineAsyncExecutionPolicy& GetExecutionPolicy() const override`
- L478 _public function_ `virtual void Execute() override`
- L485 _public function_ `ResultType& GetResultRef()`
- L492 _private function_ `template<typename... ArgTypes> void EmplaceResult(ArgTypes&&... Args)`
- L499 _private member_ `FOnlineAsyncExecutionPolicy ExecutionPolicy;`
- L500 _private member_ `TUniqueFunction<void()> ExecFunction;`
- L501 _private member_ `TTypeCompatibleBytes<ResultType> Result;`
- L502 _private member_ `bool bResultSet = false;`

#### class `UE::Online::Private::TForEachStepBase`  
`template <typename ResultElementType> class TForEachStepBase : public IStep`  
_L885-925_
- inherits: `IStep`
- L888 _public typedef_ `using ResultType = TArray<ResultElementType>;`
- L890 _public function_ `TForEachStepBase(FOnlineAsyncExecutionPolicy&& InExecutionPolicy) : ExecutionPolicy(MoveTemp(InExecutionPolicy))`
- L895 _public function_ `~TForEachStepBase()`
- L903 _public function_ `virtual const FOnlineAsyncExecutionPolicy& GetExecutionPolicy() const override`
- L908 _public function_ `virtual void Execute() override`
- L914 _public function_ `ResultType& GetResultRef()`
- L920 _protected member_ `FOnlineAsyncExecutionPolicy ExecutionPolicy;`
- L921 _protected member_ `TUniqueFunction<void()> ExecFunction;`
- L922 _protected member_ `TTypeCompatibleBytes<ResultType> Result;`
- L923 _protected member_ `std::atomic<int32> NumResultsSet = 0;`
- L924 _protected member_ `bool bResultConstructed = false;`

#### class `UE::Online::Private::TForEachStep`  
`template <typename ResultElementType> class TForEachStep : public TForEachStepBase<ResultElementType>`  
_L928-1002_
- inherits: `TForEachStepBase<ResultElementType>`
- L933 _public function_ `TForEachStep(FOnlineAsyncExecutionPolicy&& InExecutionPolicy) : TForEachStepBase<ResultElementType>(MoveTemp(InExecutionPolicy))`
- L939 _public function_ `template <typename OpType, typename LastResultType, typename CallableType> void SetExecFunction(TOnlineAsyncOp<OpType>& InOperation, LastResultType&& InLastResult, CallableType&& InCallable)`

#### struct `UE::Online::Private::Private::TForEachNResultElementType`  
`template <typename ResultType, typename = void> struct TForEachNResultElementType`  
_L1008-1012_
- desc: Primary template with a dependent static_assert that only fails when instantiated
- L1017 _public typedef_ `using ResultElementType = TElementType_T<ResultType>;`
- L1023 _public typedef_ `using ResultElementType = ResultType;`

#### struct `UE::Online::Private::Private::TForEachNResultElementType`  
`template <typename ResultType> struct TForEachNResultElementType<ResultType, std::enable_if_t<TIsContiguousContainer<ResultType>::Value, void >>`  
_L1015-1018_
- L1017 _public typedef_ `using ResultElementType = TElementType_T<ResultType>;`
- L1023 _public typedef_ `using ResultElementType = ResultType;`

#### struct `UE::Online::Private::Private::TForEachNResultElementType`  
`template <typename ResultType> struct TForEachNResultElementType<ResultType, std::enable_if_t<!TIsContiguousContainer<ResultType>::Value, void>>`  
_L1021-1024_
- L1017 _public typedef_ `using ResultElementType = TElementType_T<ResultType>;`
- L1023 _public typedef_ `using ResultElementType = ResultType;`

#### class `UE::Online::Private::TForEachNStep`  
`template <typename CallableResultType, typename ResultElementType = Private::TForEachNResultElementType_T<CallableResultType>> class TForEachNStep : public TForEachStepBase<ResultElementType>`  
_L1032-1180_
- inherits: `TForEachStepBase<ResultElementType>`
- L1037 _public function_ `TForEachNStep(int32 InBatchSize, FOnlineAsyncExecutionPolicy&& InExecutionPolicy) : TForEachStepBase<ResultElementType>(MoveTemp(InExecutionPolicy)) , BatchSize(InBatchSize)`
- L1044 _public function_ `template <typename OpType, typename LastResultType, typename CallableType> void SetExecFunction(TOnlineAsyncOp<OpType>& InOperation, LastResultType&& InLastResult, CallableType&& InCallable)`
- L1179 _private member_ `int32 BatchSize;`

#### class `UE::Online::Private::TOnlineAsyncOpBase`  
`template <typename Outer, typename OpType, typename LastResultType> class TOnlineAsyncOpBase`  
_L1184-1243_
- desc: Provides Then continuation for both TOnlineAsyncOp and TOnlineChainableAsyncOp
- L1187 _public function_ `TOnlineAsyncOpBase(LastResultType& InLastResult) : LastResult(InLastResult)`
- L1207 _public prototype_ `template <typename CallableType> auto Then(CallableType&& Callable, FOnlineAsyncExecutionPolicy ExecutionPolicy = FOnlineAsyncExecutionPolicy::RunOnGameThread());` — Callable can take one of the following forms, where the second form is used when an asynchronous call can set the promise with a value that is only valid for the duration of the Callable call ResultType(AsyncOp, LastResult) AsyncOp is a FOnlineAsyncOp& or TOnlineAsyncOp<OpType>& LastResult is a LastResultType or const LastResultType& ResultType is any type, or a TFuture to allow for an asynchronous result void(AsyncOp, LastResult, TPromise<ResultType>&&) AsyncOp is a FOnlineAsyncOp& or TOnlineAsyncOp<OpType>& LastResult is a LastResultType or const LastResultType& ResultType is any non-void type For either ResultType can be TContinuationResult<T>. Retuning TContinuationResult<T>::Repeat() will cause the step to repeat. Returning TContinuationResult<T>::Complete(T) will complete the step and allow the task to proceed to the next. The type T in TContinuationResult<T>::Complete(T) will be the LastResult type for a subsequent step.
- L1224 _public prototype_ `template <typename CallableType>`
- L1239 _public prototype_ `template <typename CallableType>` — Callable can take one of the following forms, where the second form is used when an asynchronous call can set the promise with a value that is only valid for the duration of the Callable call. This can be used when the previous continuation returned a TArray. The Callable will be called once per BatchSize elements in the previous result. The results will be combined into a TArray ResultType(AsyncOp, LastResultElements) AsyncOp is a FOnlineAsyncOp& or TOnlineAsyncOp<OpType>& LastResultElements is a TArray<LastResultElementType> or const TArray<LastResultElementType>& ResultType is any type, or a TFuture to allow for an asynchronous result void(AsyncOp, LastResultElements, TPromise<ResultType>&&) AsyncOp is a FOnlineAsyncOp& or TOnlineAsyncOp<OpType>& LastResultElements is a TArray<LastResultElementType> or const TArray<LastResultElementType>& ResultType is any non-void type
- L1242 _protected member_ `LastResultType& LastResult;`
- L1249 _public function_ `TOnlineAsyncOpBase()`
- L1921 _function_ `template <typename Outer, typename OpType, typename LastResultType> template <typename CallableType> auto TOnlineAsyncOpBase<Outer, OpType, LastResultType>::Then(CallableType&& InCallable, FOnlineAsyncExecutionPolicy ExecutionPolicy)`
- L1945 _function_ `template <typename Outer, typename OpType, typename LastResultType> template <typename CallableType> auto TOnlineAsyncOpBase<Outer, OpType, LastResultType>::ForEach(CallableType&& InCallable, FOnlineAsyncExecutionPolicy ExecutionPolicy)`
- L1962 _function_ `template <typename Outer, typename OpType, typename LastResultType> template <typename CallableType> auto TOnlineAsyncOpBase<Outer, OpType, LastResultType>::ForEachN(int32 BatchSize, CallableType&& InCallable, FOnlineAsyncExecutionPolicy ExecutionPolicy)`
- L1980 _function_ `template <typename Outer, typename OpType> template <typename CallableType> auto TOnlineAsyncOpBase<Outer, OpType, void>::Then(CallableType&& InCallable, FOnlineAsyncExecutionPolicy ExecutionPolicy)`

#### class `UE::Online::Private::TOnlineAsyncOpBase`  
`template <typename Outer, typename OpType> class TOnlineAsyncOpBase<Outer, OpType, void>`  
_L1246-1262_
- L1187 _public function_ `TOnlineAsyncOpBase(LastResultType& InLastResult) : LastResult(InLastResult)`
- L1207 _public prototype_ `template <typename CallableType> auto Then(CallableType&& Callable, FOnlineAsyncExecutionPolicy ExecutionPolicy = FOnlineAsyncExecutionPolicy::RunOnGameThread());` — Callable can take one of the following forms, where the second form is used when an asynchronous call can set the promise with a value that is only valid for the duration of the Callable call ResultType(AsyncOp, LastResult) AsyncOp is a FOnlineAsyncOp& or TOnlineAsyncOp<OpType>& LastResult is a LastResultType or const LastResultType& ResultType is any type, or a TFuture to allow for an asynchronous result void(AsyncOp, LastResult, TPromise<ResultType>&&) AsyncOp is a FOnlineAsyncOp& or TOnlineAsyncOp<OpType>& LastResult is a LastResultType or const LastResultType& ResultType is any non-void type For either ResultType can be TContinuationResult<T>. Retuning TContinuationResult<T>::Repeat() will cause the step to repeat. Returning TContinuationResult<T>::Complete(T) will complete the step and allow the task to proceed to the next. The type T in TContinuationResult<T>::Complete(T) will be the LastResult type for a subsequent step.
- L1224 _public prototype_ `template <typename CallableType>`
- L1239 _public prototype_ `template <typename CallableType>` — Callable can take one of the following forms, where the second form is used when an asynchronous call can set the promise with a value that is only valid for the duration of the Callable call. This can be used when the previous continuation returned a TArray. The Callable will be called once per BatchSize elements in the previous result. The results will be combined into a TArray ResultType(AsyncOp, LastResultElements) AsyncOp is a FOnlineAsyncOp& or TOnlineAsyncOp<OpType>& LastResultElements is a TArray<LastResultElementType> or const TArray<LastResultElementType>& ResultType is any type, or a TFuture to allow for an asynchronous result void(AsyncOp, LastResultElements, TPromise<ResultType>&&) AsyncOp is a FOnlineAsyncOp& or TOnlineAsyncOp<OpType>& LastResultElements is a TArray<LastResultElementType> or const TArray<LastResultElementType>& ResultType is any non-void type
- L1242 _protected member_ `LastResultType& LastResult;`
- L1249 _public function_ `TOnlineAsyncOpBase()`
- L1921 _function_ `template <typename Outer, typename OpType, typename LastResultType> template <typename CallableType> auto TOnlineAsyncOpBase<Outer, OpType, LastResultType>::Then(CallableType&& InCallable, FOnlineAsyncExecutionPolicy ExecutionPolicy)`
- L1945 _function_ `template <typename Outer, typename OpType, typename LastResultType> template <typename CallableType> auto TOnlineAsyncOpBase<Outer, OpType, LastResultType>::ForEach(CallableType&& InCallable, FOnlineAsyncExecutionPolicy ExecutionPolicy)`
- L1962 _function_ `template <typename Outer, typename OpType, typename LastResultType> template <typename CallableType> auto TOnlineAsyncOpBase<Outer, OpType, LastResultType>::ForEachN(int32 BatchSize, CallableType&& InCallable, FOnlineAsyncExecutionPolicy ExecutionPolicy)`
- L1980 _function_ `template <typename Outer, typename OpType> template <typename CallableType> auto TOnlineAsyncOpBase<Outer, OpType, void>::Then(CallableType&& InCallable, FOnlineAsyncExecutionPolicy ExecutionPolicy)`

#### class `UE::Online::TOnlineChainableAsyncOp`  
`template <typename OpType, typename T> class TOnlineChainableAsyncOp : public Private::TOnlineAsyncOpBase<TOnlineChainableAsyncOp<OpType, T>, OpType, TContinuationResultType_T<T>>`  
_L1268-1305_
- inherits: `Private::TOnlineAsyncOpBase<TOnlineChainableAsyncOp<OpType,T>,OpType,TContinuationResultType_T<T>>`
- L1271 _public typedef_ `using Super = Private::TOnlineAsyncOpBase<TOnlineChainableAsyncOp<OpType, T>, OpType, TContinuationResultType_T<T>>;`
- L1273 _public function_ `TOnlineChainableAsyncOp(TOnlineAsyncOp<OpType>& InOwningOperation, std::enable_if_t<!std::is_same_v<TContinuationResultType_T<T>, void>, TContinuationResultType_T<T>>& InLastResult) : Super(InLastResult) , OwningOperation(InOwningOperation)`
- L1279 _public function_ `TOnlineChainableAsyncOp(TOnlineChainableAsyncOp&& Other) : OwningOperation(Other.OwningOperation)`
- L1284 _public function_ `TOnlineChainableAsyncOp& operator=(TOnlineChainableAsyncOp&& Other)`
- L1292 _public function_ `template <typename QueueType> void Enqueue(QueueType& Queue, double DelayInSeconds = 0.0)`
- L1298 _public function_ `TOnlineAsyncOp<OpType>& GetOwningOperation()`
- L1304 _protected member_ `TOnlineAsyncOp<OpType>& OwningOperation;`
- L1311 _public typedef_ `using Super = Private::TOnlineAsyncOpBase<TOnlineChainableAsyncOp<OpType, void>, OpType, void>;`
- L1313 _public function_ `TOnlineChainableAsyncOp(TOnlineAsyncOp<OpType>& InOwningOperation) : Super() , OwningOperation(InOwningOperation)`

#### class `UE::Online::TOnlineChainableAsyncOp`  
`template <typename OpType> class TOnlineChainableAsyncOp<OpType, void> : public Private::TOnlineAsyncOpBase<TOnlineChainableAsyncOp<OpType, void>, OpType, void>`  
_L1308-1344_
- inherits: `Private::TOnlineAsyncOpBase<TOnlineChainableAsyncOp<OpType,void>,OpType,void>`
- L1271 _public typedef_ `using Super = Private::TOnlineAsyncOpBase<TOnlineChainableAsyncOp<OpType, T>, OpType, TContinuationResultType_T<T>>;`
- L1273 _public function_ `TOnlineChainableAsyncOp(TOnlineAsyncOp<OpType>& InOwningOperation, std::enable_if_t<!std::is_same_v<TContinuationResultType_T<T>, void>, TContinuationResultType_T<T>>& InLastResult) : Super(InLastResult) , OwningOperation(InOwningOperation)`
- L1279 _public function_ `TOnlineChainableAsyncOp(TOnlineChainableAsyncOp&& Other) : OwningOperation(Other.OwningOperation)`
- L1284 _public function_ `TOnlineChainableAsyncOp& operator=(TOnlineChainableAsyncOp&& Other)`
- L1292 _public function_ `template <typename QueueType> void Enqueue(QueueType& Queue, double DelayInSeconds = 0.0)`
- L1298 _public function_ `TOnlineAsyncOp<OpType>& GetOwningOperation()`
- L1304 _protected member_ `TOnlineAsyncOp<OpType>& OwningOperation;`
- L1311 _public typedef_ `using Super = Private::TOnlineAsyncOpBase<TOnlineChainableAsyncOp<OpType, void>, OpType, void>;`
- L1313 _public function_ `TOnlineChainableAsyncOp(TOnlineAsyncOp<OpType>& InOwningOperation) : Super() , OwningOperation(InOwningOperation)`

#### class `UE::Online::FOnlineAsyncOp`  
`class FOnlineAsyncOp`  
_L1346-1436_
- L1349 _public prototype_ `virtual ~FOnlineAsyncOp() = default;`
- L1351 _public member_ `Private::FOnlineOperationData Data;`
- L1353 _public prototype_ `virtual void SetError(FOnlineError&& Error) = 0;`
- L1354 _public prototype_ `virtual void Cancel(const FOnlineError& Reason) = 0;`
- L1355 _public prototype_ `virtual void ClearCallback() = 0;`
- L1357 _public function_ `void AddStep(TUniquePtr<Private::IStep>&& Step)`
- L1364 _protected function_ `template <typename CallableType> void ExecuteImpl(const TCHAR* DebugName, FOnlineAsyncExecutionPolicy ExecutionPolicy, CallableType&& Callable)`
- L1401 _protected function_ `void ExecuteNextStepImpl(const TCHAR* DebugName, const TSharedRef<FOnlineAsyncOp>& SharedThis)`
- L1418 _protected function_ `void ExecuteRepeatStepImpl(const TCHAR* DebugName, const TSharedRef<FOnlineAsyncOp>& SharedThis)`
- L1434 _protected member_ `TArray<TUniquePtr<Private::IStep>> Steps;`
- L1435 _protected member_ `int32 NextStep = 0;`

#### class `UE::Online::TOnlineAsyncOp`  
`template <typename OpType> class TOnlineAsyncOp : public Private::TOnlineAsyncOpBase<TOnlineAsyncOp<OpType>, OpType, void> , public FOnlineAsyncOp , public TSharedFromThis<TOnlineAsyncOp<OpType>>`  
_L1441-1834_
- inherits: `Private::TOnlineAsyncOpBase<TOnlineAsyncOp<OpType>,OpType,void>,FOnlineAsyncOp,TSharedFromThis<TOnlineAsyncOp<OpType>>`
- desc: This class represents an async operation on the public interface There may be one or more handles pointing to one instance
- L1447 _public typedef_ `using ParamsType = typename OpType::Params;`
- L1448 _public typedef_ `using ResultType = typename OpType::Result;`
- L1450 _public function_ `TOnlineAsyncOp(IOnlineServices& InServices, ParamsType&& Params) : Services(InServices) , SharedState(MakeShared<FAsyncOpSharedState>(MoveTemp(Params))) , OpStartTimeAbsoluteSeconds(FPlatformTime::Seconds())`
- L1457 _public prototype_ `~TOnlineAsyncOp() = default;`
- L1459 _public function_ `bool IsReady() const`
- L1464 _public function_ `bool IsComplete() const`
- L1469 _public function_ `EAsyncOpState GetState() const`
- L1474 _public function_ `const ParamsType& GetParams() const`
- L1479 _public function_ `TOnlineAsyncOp<OpType>& GetOwningOperation()`
- L1484 _public function_ `static TOnlineAsyncOp<OpType> CreateError(const FOnlineError& Error)`
- L1486 _public function_ `TOnlineAsyncOpHandle<OpType> GetHandle()`
- L1492 _public function_ `template<typename OtherOpType> TOnlineAsyncOpHandle<OtherOpType> GetWrappedHandle(TFunction<TOnlineResult<OtherOpType>(const TOnlineResult<OpType>&)> ResultConversionFunction)`
- L1497 _public function_ `virtual void ClearCallback() override`
- L1510 _public function_ `virtual void Cancel(const FOnlineError& Reason) override`
- L1518 _public function_ `void SetResult(ResultType&& InResult)`
- L1526 _public function_ `virtual void SetError(FOnlineError&& Error) override`
- L1535 _public function_ `FOnlineServicesCommon& GetServices() const` — `UE_DEPRECATED(5.6, "GetServices has been deprecated and we will no longer return FOnlineServicesCommon, use GetOnlineServices() instead and convert to FOnlineServicesCommon when needed")`
- L1540 _public function_ `IOnlineServices& GetOnlineServices() const`
- L1543 _public function_ `template <typename QueueType> void Enqueue(QueueType& Queue, double DelayInSeconds = 0.0)`
- L1551 _public function_ `void Start()`
- L1559 _public function_ `void ExecuteNextStep()`
- L1567 _public function_ `void ExecuteRepeatStep()`
- L1576 _public function_ `template <typename CallableType> void Execute(FOnlineAsyncExecutionPolicy ExecutionPolicy, CallableType&& Callable)`
- L1581 _public function_ `TOnlineEvent<void(const TOnlineAsyncOp<OpType>&)> OnStart()`
- L1582 _public function_ `TOnlineEvent<void(const TOnlineAsyncOp<OpType>&, const TOnlineResult<OpType>&)> OnComplete()`
- L1584 _public function_ `const FString& GetInterfaceName()`
- L1585 _public function_ `void SetInterfaceName(FStringView InName)`
- L1588 _protected member_ `IOnlineServices& Services;`
- L1590 _protected function_ `void SetResultAndState(TOnlineResult<OpType>&& Result, EAsyncOpState State)`
- L1618 _protected function_ `void TriggerOnComplete(const TOnlineResult<OpType>& Result)`
- L1805 _protected function_ `void Detach(const TSharedRef<FAsyncOpSharedHandleState>& SharedHandleState)`
- L1810 _protected function_ `TSharedRef<Private::IOnlineAsyncOpSharedState<OpType>> CreateSharedState()`
- L1818 _protected function_ `template <typename OtherOpType> TSharedRef<Private::IOnlineAsyncOpSharedState<OtherOpType>> WrapSharedState(TFunction<TOnlineResult<OtherOpType>(const TOnlineResult<OpType>&)>&& ResultConversionFunction)`
- L1825 _protected member_ `TSharedRef<FAsyncOpSharedState> SharedState;`
- L1826 _protected member_ `TArray<TSharedRef<FAsyncOpSharedHandleState>> SharedHandleStates;`
- L1827 _protected member_ `TOnlineEventCallable<void(const TOnlineAsyncOp<OpType>&)> OnStartEvent;`
- L1828 _protected member_ `TOnlineEventCallable<void(const TOnlineAsyncOp<OpType>&, const TOnlineResult<OpType>&)> OnCompleteEvent;`
- L1829 _protected member_ `double OpStartTimeAbsoluteSeconds;`
- L1832 _protected member_ `FOnlineEventDelegateHandle OpCacheHandle;` — Delegate handle for FOnlineAsyncOpCache internal usage
- L1833 _protected member_ `FString InterfaceName;`

#### class `UE::Online::TOnlineAsyncOp::FAsyncOpSharedState`  
`class FAsyncOpSharedState`  
_L1655-1672_
- L1658 _public function_ `FAsyncOpSharedState(ParamsType&& InParams) : Params(MoveTemp(InParams))`
- L1663 _public member_ `ParamsType Params;`
- L1665 _public member_ `TOnlineResult<OpType> Result{ Errors::Unknown() };` — This will need to be protected with a mutex if we want to allow this to be set from multiple threads (eg, set result from a task graph thread, while allowing this to be cancelled from the game thread)
- L1666 _public member_ `EAsyncOpState State = EAsyncOpState::Invalid;`
- L1668 _public function_ `bool IsComplete() const`

#### class `UE::Online::TOnlineAsyncOp::FAsyncOpSharedHandleState`  
`class FAsyncOpSharedHandleState : public Private::IOnlineAsyncOpSharedState<OpType>, public TSharedFromThis<FAsyncOpSharedHandleState>`  
_L1674-1774_
- inherits: `Private::IOnlineAsyncOpSharedState<OpType>,TSharedFromThis<FAsyncOpSharedHandleState>`
- L1677 _public function_ `FAsyncOpSharedHandleState(const TSharedRef<TOnlineAsyncOp<OpType>>& InAsyncOp) : SharedState(InAsyncOp->SharedState) , AsyncOp(InAsyncOp)`
- L1683 _public function_ `~FAsyncOpSharedHandleState()`
- L1688 _public function_ `virtual void Cancel(const FOnlineError& Reason) override`
- L1707 _public function_ `virtual EAsyncOpState GetState() const override`
- L1712 _public function_ `virtual void SetOnProgress(TDelegate<void(const FAsyncProgress&)>&& Function) override`
- L1717 _public function_ `virtual void SetOnWillRetry(TDelegate<void(TOnlineAsyncOpHandle<OpType>& Handle, const FWillRetry&)>&& Function) override`
- L1722 _public function_ `virtual void SetOnComplete(TDelegate<void(const TOnlineResult<OpType>&)>&& Function) override`
- L1731 _public function_ `void TriggerOnProgress(const FAsyncProgress& Progress)`
- L1736 _public function_ `void TriggerOnWillRetry(const FWillRetry& RetryDetails)`
- L1745 _public function_ `void TriggerOnComplete(const TOnlineResult<OpType>& Result)`
- L1757 _private function_ `void Detach()`
- L1767 _private member_ `TDelegate<void(const FAsyncProgress&)> OnProgressFn;`
- L1768 _private member_ `TDelegate<void(TOnlineAsyncOpHandle<OpType>& Handle, const FWillRetry&)> OnWillRetryFn;`
- L1769 _private member_ `TDelegate<void(const TOnlineResult<OpType>&)> OnCompleteFn;`
- L1771 _private member_ `bool bCancelled = false;`
- L1772 _private member_ `TSharedRef<FAsyncOpSharedState> SharedState;`
- L1773 _private member_ `TWeakPtr<TOnlineAsyncOp<OpType>> AsyncOp;`

#### class `UE::Online::TOnlineAsyncOp::TWrappedAsyncOpSharedHandleState`  
`template <typename OtherOpType> class TWrappedAsyncOpSharedHandleState : public Private::IOnlineAsyncOpSharedState<OtherOpType>`  
_L1779-1792_
- inherits: `Private::IOnlineAsyncOpSharedState<OtherOpType>`
- L1782 _public prototype_ `TWrappedAsyncOpSharedHandleState(TWrappedAsyncOpSharedHandleStateContainer<OtherOpType>& InSharedHandleState, TFunction<TOnlineResult<OtherOpType>(const TOnlineResult<OpType>&)>&& InResultConversionFunction);`
- L1783 _public prototype_ `virtual void Cancel(const FOnlineError& Reason) override;`
- L1784 _public prototype_ `virtual EAsyncOpState GetState() const override;`
- L1785 _public prototype_ `virtual void SetOnProgress(TDelegate<void(const FAsyncProgress&)>&& Function) override;`
- L1786 _public prototype_ `virtual void SetOnWillRetry(TDelegate<void(TOnlineAsyncOpHandle<OtherOpType>&, const FWillRetry&)>&& WillRetryFunction) override;`
- L1787 _public prototype_ `virtual void SetOnComplete(TDelegate<void(const TOnlineResult<OtherOpType>&)>&& OnCompleteFunction) override;`
- L1790 _protected member_ `TWrappedAsyncOpSharedHandleStateContainer<OtherOpType>& SharedHandleState;`
- L1791 _protected member_ `TFunction<TOnlineResult<OtherOpType>(const TOnlineResult<OpType>&)> ResultConversionFunction;`
- L1838 _function_ `template <typename OpType> template <typename OtherOpType> TOnlineAsyncOp<OpType>::TWrappedAsyncOpSharedHandleState<OtherOpType>::TWrappedAsyncOpSharedHandleState(TOnlineAsyncOp<OpType>::TWrappedAsyncOpSharedHandleStateContainer<OtherOpType>& InSharedHandleState, TFunction<TOnlineResult<OtherOpType>(const TOnlineResult<OpType>&)>&& InResultConversionFunction) : SharedHandleState(InSharedHandleState) , ResultConversionFunction(MoveTemp(InResultConversionFunction))`
- L1847 _function_ `template <typename OpType> template <typename OtherOpType> void TOnlineAsyncOp<OpType>::TWrappedAsyncOpSharedHandleState<OtherOpType>::Cancel(const FOnlineError& Reason)`
- L1854 _function_ `template <typename OpType> template <typename OtherOpType> EAsyncOpState TOnlineAsyncOp<OpType>::TWrappedAsyncOpSharedHandleState<OtherOpType>::GetState() const`
- L1861 _function_ `template <typename OpType> template <typename OtherOpType> void TOnlineAsyncOp<OpType>::TWrappedAsyncOpSharedHandleState<OtherOpType>::SetOnProgress(TDelegate<void(const FAsyncProgress&)>&& Function)`
- L1868 _function_ `template <typename OpType> template <typename OtherOpType> void TOnlineAsyncOp<OpType>::TWrappedAsyncOpSharedHandleState<OtherOpType>::SetOnWillRetry(TDelegate<void(TOnlineAsyncOpHandle<OtherOpType>&, const FWillRetry&)>&& WillRetryFunction)`
- L1883 _function_ `template <typename OpType> template <typename OtherOpType> void TOnlineAsyncOp<OpType>::TWrappedAsyncOpSharedHandleState<OtherOpType>::SetOnComplete(TDelegate<void(const TOnlineResult<OtherOpType>&)>&& OnCompleteFunction)`

#### class `UE::Online::TOnlineAsyncOp::TWrappedAsyncOpSharedHandleStateContainer`  
`template <typename OtherOpType> class TWrappedAsyncOpSharedHandleStateContainer : public FAsyncOpSharedHandleState`  
_L1795-1803_
- inherits: `FAsyncOpSharedHandleState`
- L1798 _public prototype_ `TWrappedAsyncOpSharedHandleStateContainer(const TSharedRef<TOnlineAsyncOp<OpType>>& InAsyncOp, TFunction<TOnlineResult<OtherOpType>(const TOnlineResult<OpType>&)>&& InResultConversionFunction);`
- L1799 _public prototype_ `TSharedRef<TWrappedAsyncOpSharedHandleState<OtherOpType>> GetWrappedState();`
- L1802 _private member_ `TWrappedAsyncOpSharedHandleState<OtherOpType> WrappedState;`
- L1898 _function_ `template <typename OpType> template <typename OtherOpType> TOnlineAsyncOp<OpType>::TWrappedAsyncOpSharedHandleStateContainer<OtherOpType>::TWrappedAsyncOpSharedHandleStateContainer(const TSharedRef<TOnlineAsyncOp<OpType>>& InAsyncOp, TFunction<TOnlineResult<OtherOpType>(const TOnlineResult<OpType>&)>&& InResultConversionFunction) : FAsyncOpSharedHandleState(InAsyncOp) , WrappedState(*this, MoveTemp(InResultConversionFunction))`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Online` (scope `UE`)
- L131 _typedef_ `template <typename T> using TContinuationResultType_T = typename TContinuationResultType<T>::ResultType;` (scope `UE::Online`)
- L134 _function_ `template <typename T> FString ToLogString(const TDefaultErrorResultInternal<T>& Result)` (scope `UE::Online`)
- L146 _namespace_ `namespace Private` (scope `UE::Online`)
- L250 _function_ `inline uint32 GetTypeHash(const FOnlineOperationData::FOperationDataKey& Key)` (scope `UE::Online::Private`)
- L387 _function_ `` (scope `UE::Online::Private::TStep::SetExecFunction`)
- L397 _function_ `` (scope `UE::Online::Private::TStep::SetExecFunction::__anon98821a8e0102`)
- L442 _function_ `` (scope `UE::Online::Private::TStep::SetExecFunction::__anon98821a8e0402`)
- L527 _function_ `` (scope `UE::Online::Private::TStep::SetExecFunction::__anon98821a8e0702`)
- L555 _function_ `` (scope `UE::Online::Private::TStep::SetExecFunction::__anon98821a8e0902`)
- L618 _function_ `` (scope `UE::Online::Private::TStep::SetExecFunction::__anon98821a8e0b02`)
- L684 _function_ `` (scope `UE::Online::Private::TStep::SetExecFunction::__anon98821a8e0e02`)
- L791 _function_ `` (scope `UE::Online::Private::TStep::SetExecFunction::__anon98821a8e1102`)
- L833 _function_ `` (scope `UE::Online::Private::TStep::SetExecFunction::__anon98821a8e1302`)
- L942 _function_ `` (scope `UE::Online::Private::TForEachStep::SetExecFunction`)
- L959 _function_ `` (scope `UE::Online::Private::TForEachStep::SetExecFunction::__anon98821a8e1502`)
- L1004 _namespace_ `namespace Private` (scope `UE::Online::Private`)
- L1027 _typedef_ `template <typename ResultType> using TForEachNResultElementType_T = typename TForEachNResultElementType<ResultType>::ResultElementType;` (scope `UE::Online::Private::Private`)
- L1047 _function_ `` (scope `UE::Online::Private::TForEachNStep::SetExecFunction`)
- L1076 _function_ `` (scope `UE::Online::Private::TForEachNStep::SetExecFunction::__anon98821a8e1802`)
- L1381 _function_ `` (scope `UE::Online::FOnlineAsyncOp::ExecuteImpl`)
- L1409 _function_ `` (scope `UE::Online::FOnlineAsyncOp::ExecuteNextStepImpl`)
- L1425 _function_ `` (scope `UE::Online::FOnlineAsyncOp::ExecuteRepeatStepImpl`)
- L1609 _function_ `` (scope `UE::Online::TOnlineAsyncOp::SetResultAndState`)
- L1872 _function_ `` (scope `UE::Online::TOnlineAsyncOp::TWrappedAsyncOpSharedHandleState::SetOnWillRetry`)
- L1887 _function_ `` (scope `UE::Online::TOnlineAsyncOp::TWrappedAsyncOpSharedHandleState::SetOnComplete`)
- L1913 _typedef_ `template <typename OpType> using TOnlineAsyncOpRef = TSharedRef<TOnlineAsyncOp<OpType>>;` (scope `UE::Online`)
- L1915 _typedef_ `template <typename OpType> using TOnlineAsyncOpPtr = TSharedPtr<TOnlineAsyncOp<OpType>>;` (scope `UE::Online`)
- L1917 _namespace_ `namespace Private` (scope `UE::Online`)
- L1923 _typedef_ `using ResultType = typename TOnlineAsyncOpCallableTraits<CallableType>::ResultType;` (scope `UE::Online::Private::TOnlineAsyncOpBase::Then`)
- L1947 _typedef_ `using ResultType = typename TOnlineAsyncOpCallableTraits<CallableType>::ResultType;` (scope `UE::Online::Private::TOnlineAsyncOpBase::ForEach`)
- L1964 _typedef_ `using CallableResultType = typename TOnlineAsyncOpCallableTraits<CallableType>::ResultType;` (scope `UE::Online::Private::TOnlineAsyncOpBase::ForEachN`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineAsyncOpCache.h` (Public)


#### struct `UE::Online::CLocalAccountIdDefined`  
`struct CLocalAccountIdDefined`  
_L12-16_
- L15 _public prototype_ `template <typename T> auto Requires() -> decltype(T::LocalAccountId);`

#### enum `UE::Online::EOperationCacheExpirationPolicy`  
`enum class EOperationCacheExpirationPolicy : uint8`  
_L18-26_
- L21 _public enumerator_ `UponCompletion` — Expire when the operation completes
- L23 _public enumerator_ `Duration` — Expire after a certain amount of time has elapsed
- L25 _public enumerator_ `Never` — Only expire if the cache is cleared

#### struct `UE::Online::FOperationConfig`  
`struct FOperationConfig`  
_L44-49_
- L46 _public member_ `EOperationCacheExpirationPolicy CacheExpiration = EOperationCacheExpirationPolicy::UponCompletion;`
- L47 _public member_ `double CacheExpirySeconds = 0.0f;`
- L48 _public member_ `bool bCacheError = false;`

#### class `UE::Online::IOnlineAnyData`  
`class IOnlineAnyData`  
_L51-78_
- L54 _public prototype_ `virtual ~IOnlineAnyData() = default;`
- L55 _public prototype_ `virtual FOnlineTypeName GetTypeName() const = 0;`
- L58 _public function_ `template <typename T> const T* Get() const`
- L69 _public function_ `template <typename T> const T& GetRef() const`
- L77 _protected prototype_ `virtual const void* GetData() const = 0;`

#### class `UE::Online::TOnlineAnyData`  
`template <typename T, typename BaseType = IOnlineAnyData> class TOnlineAnyData : public BaseType`  
_L81-113_
- inherits: `BaseType`
- L84 _public typedef_ `using ValueType = std::remove_reference_t<T>;`
- L86 _public function_ `TOnlineAnyData(const ValueType& InData) : Data(InData)`
- L91 _public function_ `TOnlineAnyData(ValueType&& InData) : Data(MoveTemp(InData))`
- L96 _public function_ `virtual FOnlineTypeName GetTypeName() const override`
- L101 _public function_ `const T& GetDataRef() const`
- L107 _protected function_ `virtual const void* GetData() const override`
- L112 _protected member_ `T Data;`

#### struct `UE::Online::Private::COnlineGetTypeHashable`  
`struct COnlineGetTypeHashable`  
_L133-154_
- desc: Different than the standard CGetTypeHashable as we want to detect GetTypeHash using more than the standard name lookup rules
- L136 _public prototype_ `template <typename T> auto Requires(uint32& Result, const T& Val) -> decltype( Result = GetTypeHash(Val) );`
- L141 _public prototype_ `template <typename T> auto Requires(uint32& Result, const T& Val) -> decltype( Result = ::GetTypeHash(Val) );`
- L146 _public prototype_ `template <typename T> auto Requires(uint32& Result, const T& Val) -> decltype( Result = ::UE::Online::GetTypeHash(Val) );`
- L151 _public prototype_ `template <typename T> auto Requires(uint32& Result, const T& Val) -> decltype( Result = ::UE::Online::Private::GetTypeHash(Val) );`

#### struct `UE::Online::TJoinableOpParamsFuncs`  
`template <typename OpType> struct TJoinableOpParamsFuncs`  
_L159-183_
- L161 _public function_ `inline static bool Compare(const typename OpType::Params& First, const typename OpType::Params& Second)`
- L171 _public function_ `inline static uint32 GetTypeHash(const typename OpType::Params& Params)`

#### struct `UE::Online::TMergeableOpParamsFuncs`  
`template <typename OpType> struct TMergeableOpParamsFuncs`  
_L187-237_
- desc: MergeableOps Params contain a field of Mutations that implements operator+= that performs the merge
- L189 _public function_ `inline static bool Compare(const typename OpType::Params& First, const typename OpType::Params& Second)`
- L210 _public function_ `inline static uint32 GetTypeHash(const typename OpType::Params& Params)`
- L233 _public function_ `inline static void Merge(typename OpType::Params& CurrentParams, typename OpType::Params&& NewParams)`

#### class `UE::Online::FOnlineAsyncOpCache`  
`class FOnlineAsyncOpCache`  
_L239-564_
- L242 _public function_ `FOnlineAsyncOpCache(const FString& ConfigPath, class FOnlineServicesCommon& InServices) : Services(InServices)`
- L249 _public function_ `template <typename OpType> TOnlineAsyncOpRef<OpType> GetOp(typename OpType::Params&& Params, const TArray<FString>& ConfigSectionHierarchy)` — Create an operation
- L279 _public function_ `template <typename OpType, typename ParamsFuncsType > TOnlineAsyncOpRef<OpType> GetJoinableOp(typename OpType::Params&& Params, const TArray<FString>& ConfigSectionHierarchy)` — Join an existing operation or use a non-expired cached result, or create an operation that can later be joined
- L355 _public function_ `template <typename OpType, typename ParamsFuncsType > TOnlineAsyncOpRef<OpType> GetMergeableOp(typename OpType::Params&& Params, const TArray<FString>& ConfigSectionHierarchy)` — Merge with a pending operation, or create an operation
- L403 _public function_ `void SetLoadConfigFn(TUniqueFunction<bool(FOperationConfig&, const TArray<FString>&)>&& InLoadConfigFn)`
- L408 _public member_ `FOnlineServicesCommon& Services;`
- L412 _public prototype_ `void ClearAllCallbacks();` — Internal use only { TODO: Move into package scope instead
- L413 _public prototype_ `void CancelAll();`
- L414 _public prototype_ `bool HasAnyRunningOperation() const;`
- L418 _private prototype_ `TSharedRef<FOnlineAsyncOpCache> GetSharedThis();`
- L420 _private member_ `TUniqueFunction<bool(FOperationConfig&, const TArray<FString>&)> LoadConfigFn;`
- L423 _private function_ `template <typename OpType, typename ParamsFuncsType> TOnlineAsyncOpRef<OpType> CreateOp(typename OpType::Params&& Params)`
- L557 _private prototype_ `bool HasAnyRunningOperationIn(const TMap<FWrappedOperationKey, TUniquePtr<IWrappedOperation>>& InOperations) const;`
- L558 _private prototype_ `void ClearCallbacks(const TMap<FWrappedOperationKey, TUniquePtr<IWrappedOperation>>& InOperations);`
- L559 _private prototype_ `void CancelOperations(const TMap<FWrappedOperationKey, TUniquePtr<IWrappedOperation>>& InOperations);`
- L561 _private member_ `TMap<FWrappedOperationKey, TUniquePtr<IWrappedOperation>> Operations;`
- L562 _private member_ `TMap<FAccountId, TMap<FWrappedOperationKey, TUniquePtr<IWrappedOperation>>> UserOperations;`
- L563 _private member_ `TArray<TUniquePtr<IWrappedOperation>> IndependentOperations;`

#### class `UE::Online::FOnlineAsyncOpCache::IWrappedOperation`  
`class IWrappedOperation : public IOnlineAnyData`  
_L444-451_
- inherits: `IOnlineAnyData`
- L447 _public prototype_ `virtual bool IsExpired() = 0;`
- L448 _public prototype_ `virtual void Cancel() = 0;`
- L449 _public prototype_ `virtual void ClearCallback() = 0;`
- L450 _public prototype_ `virtual EAsyncOpState GetAsyncOpState() const = 0;`

#### class `UE::Online::FOnlineAsyncOpCache::TWrappedOperation`  
`template <typename OpType> class TWrappedOperation : public TOnlineAnyData<TSharedRef<TOnlineAsyncOp<OpType>>, IWrappedOperation>`  
_L454-489_
- inherits: `TOnlineAnyData<TSharedRef<TOnlineAsyncOp<OpType>>,IWrappedOperation>`
- L458 _public function_ `template <typename... ParamTypes> TWrappedOperation(ParamTypes&&... Params) : TOnlineAnyData<TSharedRef<TOnlineAsyncOp<OpType>>, IWrappedOperation>(MakeShared<TOnlineAsyncOp<OpType>>(Forward<ParamTypes>(Params)...))`
- L463 _public function_ `virtual EAsyncOpState GetAsyncOpState() const override`
- L468 _public function_ `virtual bool IsExpired() override`
- L480 _public function_ `virtual void ClearCallback() override`
- L485 _public function_ `virtual void Cancel() override`

#### class `UE::Online::FOnlineAsyncOpCache::FWrappedOperationKey`  
`class FWrappedOperationKey`  
_L491-553_
- L495 _public function_ `template<typename OpType, typename ParamsFuncsType> static FWrappedOperationKey Create(const typename OpType::Params& Params)`
- L500 _public function_ `bool operator==(const FWrappedOperationKey& Other) const`
- L505 _public function_ `uint32 GetTypeHash() const`
- L518 _private function_ `FWrappedOperationKey(TUniquePtr<IWrappedOperationKeyImpl>&& InImpl) : Impl(MoveTemp(InImpl))`
- L552 _private member_ `TUniquePtr<IWrappedOperationKeyImpl> Impl;`

#### class `UE::Online::FOnlineAsyncOpCache::FWrappedOperationKey::IWrappedOperationKeyImpl`  
`class IWrappedOperationKeyImpl : public IOnlineAnyData`  
_L511-516_
- inherits: `IOnlineAnyData`
- L514 _public prototype_ `virtual bool Compare(const IWrappedOperationKeyImpl& Other) const = 0;`
- L515 _public prototype_ `virtual uint32 GetTypeHash() const = 0;`

#### class `UE::Online::FOnlineAsyncOpCache::FWrappedOperationKey::TWrappedOperationKeyImpl`  
`template <typename OpType, typename ParamsFuncsType> class TWrappedOperationKeyImpl : public TOnlineAnyData<const typename OpType::Params&, IWrappedOperationKeyImpl>`  
_L524-550_
- inherits: `TOnlineAnyData<consttypenameOpType::Params&,IWrappedOperationKeyImpl>`
- L527 _public typedef_ `using DataType = const typename OpType::Params&;`
- L528 _public typedef_ `using ValueType = const typename OpType::Params;`
- L530 _public function_ `TWrappedOperationKeyImpl(DataType& ParamsRef) : TOnlineAnyData<DataType&, IWrappedOperationKeyImpl>(ParamsRef)`
- L535 _public function_ `virtual bool Compare(const IWrappedOperationKeyImpl& Other) const override`
- L545 _public function_ `virtual uint32 GetTypeHash() const override`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L28 _function_ `inline void LexFromString(EOperationCacheExpirationPolicy& Value, const TCHAR* const String)` (scope `UE::Online`)
- L115 _namespace_ `namespace Private` (scope `UE::Online`)
- L121 _function_ `template <typename T> inline uint32 GetTypeHash(const TArray<T>& Array)` (scope `UE::Online::Private`) — TArray GetTypeHash specialization used for TAsyncOpParamsFuncs::GetTypeHash
- L165 _function_ `` (scope `UE::Online::TJoinableOpParamsFuncs::Compare`)
- L178 _function_ `` (scope `UE::Online::TJoinableOpParamsFuncs::GetTypeHash`)
- L193 _function_ `` (scope `UE::Online::TMergeableOpParamsFuncs::Compare`)
- L216 _function_ `` (scope `UE::Online::TMergeableOpParamsFuncs::GetTypeHash`)
- L260 _function_ `Op->OpCacheHandle = Op->OnComplete().Add(GetSharedThis(), [this](const TOnlineAsyncOp<OpType>& ThisOp, const TOnlineResult<OpType>& Result) { const TOnlineAsyncOp<OpType>* ThisOpPtr = &ThisOp; IndependentOperations.RemoveAll([ThisOpPtr](const TUniquePtr<IWrappedOperation>& WrappedOp) { const TSharedRef<TOnlineAsyncOp<OpType>>* Op = WrappedOp->Get<TSharedRef<TOnlineAsyncOp<OpType>>>(); if (Op) { return ThisOpPtr == &(*Op).Get(); } return false; }); });` (scope `UE::Online::FOnlineAsyncOpCache::GetOp`)
- L262 _function_ `IndependentOperations.RemoveAll([ThisOpPtr](const TUniquePtr<IWrappedOperation>& WrappedOp) { const TSharedRef<TOnlineAsyncOp<OpType>>* Op = WrappedOp->Get<TSharedRef<TOnlineAsyncOp<OpType>>>(); if (Op) { return ThisOpPtr == &(*Op).Get(); } return false; });` (scope `UE::Online::FOnlineAsyncOpCache::GetOp::__anon728bf8020502`)
- L313 _function_ `` (scope `UE::Online::FOnlineAsyncOpCache::GetJoinableOp`)
- L331 _function_ `FTSTicker::GetCoreTicker().AddTicker(TEXT("OnlineAsyncOpCacheExpiry"), Config.CacheExpirySeconds, [this, WeakOp = ThisOp.AsWeak()](float) { TSharedPtr<const TOnlineAsyncOp<OpType>> PinnedOp = WeakOp.Pin(); if (PinnedOp.IsValid()) { if constexpr (TModels_V<CLocalAccountIdDefined, typename OpType::Params>) { UserOperations.FindOrAdd(PinnedOp->GetParams().LocalAccountId).Remove(FWrappedOperationKey::Create<OpType, ParamsFuncsType>(PinnedOp->GetParams())); } else { Operations.Remove(FWrappedOperationKey::Create<OpType, ParamsFuncsType>(PinnedOp->GetParams())); } } return false; });` (scope `UE::Online::FOnlineAsyncOpCache::GetJoinableOp::__anon728bf8020702`) — Set timer with duration to remove cached operation
- L388 _function_ `` (scope `UE::Online::FOnlineAsyncOpCache::GetMergeableOp`)
- L566 _function_ `inline uint32 GetTypeHash(const FOnlineAsyncOpCache::FWrappedOperationKey& Key)` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineAsyncOpCache_Meta.inl` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L8 _namespace_ `namespace Meta` (scope `UE::Online`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineAsyncOpQueue.h` (Public)


#### class `UE::Online::FOnlineAsyncOpQueue`  
`class FOnlineAsyncOpQueue`  
_L15-132_
- L18 _public function_ `FOnlineAsyncOpQueue()`
- L22 _public function_ `virtual ~FOnlineAsyncOpQueue()`
- L31 _public function_ `template <typename OpType> void Enqueue(TOnlineAsyncOp<OpType>& Op, double DelayInSeconds = 0.0)`
- L37 _public prototype_ `virtual bool IsIdle() const = 0;`
- L39 _public prototype_ `virtual void TryStartOperations() = 0;`
- L131 _protected member_ `TTransactionallySafeSpscQueue<TSharedRef<IWrappedOp>> QueuedOperations;`

#### class `UE::Online::FOnlineAsyncOpQueue::IWrappedOp`  
`class IWrappedOp`  
_L42-50_
- L45 _public prototype_ `virtual ~IWrappedOp() = default;`
- L46 _public prototype_ `virtual void Start() = 0;`
- L47 _public prototype_ `virtual void Cancel(const FOnlineError& Reason) = 0;`
- L48 _public prototype_ `virtual bool IsComplete() const = 0;`
- L49 _public prototype_ `virtual TOnlineEvent<void(void)> OnComplete() = 0;`

#### class `UE::Online::FOnlineAsyncOpQueue::TWrappedOp`  
`template <typename OpType> class TWrappedOp : public IWrappedOp, public TSharedFromThis<TWrappedOp<OpType>>`  
_L53-129_
- inherits: `IWrappedOp,TSharedFromThis<TWrappedOp<OpType>>`
- L56 _public prototype_ `virtual ~TWrappedOp() = default;`
- L58 _public function_ `TWrappedOp(TOnlineAsyncOp<OpType>& InOp, double InDelayInSeconds) : Op(InOp.AsShared()) , DelayInSeconds(InDelayInSeconds) , EnqueueCycles(InDelayInSeconds > 0.0 ? FPlatformTime::Cycles64() : 0)`
- L65 _public function_ `virtual void Start() override final`
- L102 _public function_ `virtual void Cancel(const FOnlineError& Reason) override final`
- L112 _public function_ `virtual bool IsComplete() const override final`
- L117 _public function_ `virtual TOnlineEvent<void(void)> OnComplete() override final`
- L123 _private member_ `TSharedRef<TOnlineAsyncOp<OpType>> Op;`
- L124 _private member_ `const double DelayInSeconds = 0.0;`
- L125 _private member_ `const uint64 EnqueueCycles = 0;`
- L126 _private member_ `TOnlineEventCallable<void(void)> OnCompleteEvent;`
- L127 _private member_ `FOnlineEventDelegateHandle OnCompleteHandle;`
- L128 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`

#### class `UE::Online::FOnlineAsyncOpQueueParallel`  
`class FOnlineAsyncOpQueueParallel : public FOnlineAsyncOpQueue`  
_L134-179_
- inherits: `FOnlineAsyncOpQueue`
- L137 _public function_ `virtual void TryStartOperations() override`
- L141 _public function_ `virtual bool IsIdle() const override`
- L148 _public function_ `void Enqueue(TSharedRef<IWrappedOp>& Operation)`
- L153 _public function_ `void Tick(float DeltaSeconds)`
- L174 _public function_ `void SetMaxConcurrentOperations(int InMaxConcurrentOperations)`
- L177 _protected member_ `TArray<TPair<TSharedRef<IWrappedOp>, FOnlineEventDelegateHandle>> InFlightOperations;`
- L178 _protected member_ `int MaxConcurrentOperations = 16;`

#### class `UE::Online::FOnlineAsyncOpQueueSerial`  
`class FOnlineAsyncOpQueueSerial : public FOnlineAsyncOpQueue`  
_L181-227_
- inherits: `FOnlineAsyncOpQueue`
- L184 _public function_ `FOnlineAsyncOpQueueSerial(FOnlineAsyncOpQueueParallel& InParentQueue) : ParentQueue(InParentQueue)`
- L189 _public function_ `~FOnlineAsyncOpQueueSerial()`
- L198 _public function_ `virtual void TryStartOperations() override`
- L217 _public function_ `virtual bool IsIdle() const override`
- L223 _protected member_ `FOnlineAsyncOpQueueParallel& ParentQueue;`
- L225 _protected member_ `TSharedPtr<IWrappedOp> InFlightOperation;`
- L226 _protected member_ `FOnlineEventDelegateHandle ContinuationDelegateHandle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L68 _function_ `` (scope `UE::Online::FOnlineAsyncOpQueue::TWrappedOp::Start`)
- L164 _function_ `` (scope `UE::Online::FOnlineAsyncOpQueueParallel::Tick`)
- L166 _function_ `` (scope `UE::Online::FOnlineAsyncOpQueueParallel::Tick::__anond70dc9130302`)
- L209 _function_ `` (scope `UE::Online::FOnlineAsyncOpQueueSerial::TryStartOperations`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineComponent.h` (Public)


#### class `UE::Online::TOnlineComponent`  
`template <typename ComponentType> class TOnlineComponent : public ComponentType , public IOnlineComponent`  
_L12-238_
- inherits: `ComponentType,IOnlineComponent`
- L17 _public typedef_ `using Super = ComponentType;`
- L19 _public prototype_ `TOnlineComponent(const TOnlineComponent&) = delete;`
- L20 _public prototype_ `TOnlineComponent(TOnlineComponent&&) = delete;`
- L24 _public function_ `TOnlineComponent(const FString& ComponentName, FOnlineServicesCommon& InServices) : Services(InServices) , WeakThis(TSharedPtr<ComponentType>(InServices.AsShared(), static_cast<ComponentType*>(this))) , InterfaceName(ComponentName) , SerialQueue(InServices.GetParallelQueue())`
- L32 _public function_ `virtual void Initialize() override`
- L38 _public function_ `virtual void PostInitialize() override`
- L39 _public function_ `virtual void UpdateConfig() override`
- L40 _public function_ `virtual void Tick(float DeltaSeconds) override`
- L41 _public function_ `virtual void PreShutdown() override`
- L42 _public function_ `virtual void Shutdown() override`
- L45 _public function_ `template <typename StructType> bool LoadConfig(StructType& Struct, const FString& OperationName = FString()) const`
- L50 _public function_ `const FString& GetConfigName() const`
- L53 _public function_ `template <typename OpType> TOnlineAsyncOpRef<OpType> GetOp(typename OpType::Params&& Params)`
- L61 _public function_ `template <typename OpType, typename ParamsFuncsType = TJoinableOpParamsFuncs<OpType>> TOnlineAsyncOpRef<OpType> GetJoinableOp(typename OpType::Params&& Params)`
- L69 _public function_ `template <typename OpType, typename ParamsFuncsType = TMergeableOpParamsFuncs<OpType>> TOnlineAsyncOpRef<OpType> GetMergeableOp(typename OpType::Params&& Params)`
- L77 _public function_ `template <typename ServicesType = FOnlineServicesCommon> ServicesType& GetServices()`
- L83 _public function_ `template <typename ServicesType = FOnlineServicesCommon> const ServicesType& GetServices() const`
- L89 _public function_ `FOnlineAsyncOpQueue& GetSerialQueue()` — Queue for executing tasks in serial
- L95 _public function_ `FOnlineAsyncOpQueue& GetSerialQueue(const FAccountId& AccountId)` — Queues for executing per-user tasks in serial
- L107 _public function_ `TArray<FString> GetConfigSectionHeiarchy(const FString& OperationName = FString())` — `UE_DEPRECATED(5.6, "GetConfigSectionHeiarchy has been renamed GetConfigSectionHierarchy")`
- L113 _public function_ `TArray<FString> GetConfigSectionHeirarchy(const FString& OperationName = FString())` — `UE_DEPRECATED(5.8, "GetConfigSectionHeirarchy has been renamed GetConfigSectionHierarchy")`
- L118 _public function_ `TArray<FString> GetConfigSectionHierarchy(const FString& OperationName = FString())`
- L135 _public function_ `virtual void RegisterCommands()`
- L139 _public function_ `template <typename T> void RegisterCommand(T MemberFunction)` — Default handler: generic parsing of Params, log Result
- L149 _public function_ `template <typename InterfaceType, typename T> void RegisterCommand(InterfaceType* Interface, T MemberFunction)` — Default handler: generic parsing of Params, log Result
- L158 _public function_ `void RegisterExecHandler(const FString& Name, TUniquePtr<IOnlineExecHandler>&& Handler)` — Custom handler
- L163 _public function_ `bool Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar)`
- L181 _public function_ `bool Help(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar)`
- L192 _public function_ `TSharedRef<ComponentType> AsShared()` — TSharedFromThis-like behavior
- L199 _public function_ `TSharedRef<ComponentType const> AsShared() const`
- L206 _public function_ `TWeakPtr<ComponentType> AsWeak()`
- L211 _public function_ `TWeakPtr<ComponentType const> AsWeak() const`
- L218 _protected function_ `template <class OtherType> static TSharedRef<OtherType> SharedThis(OtherType* ThisPtr)`
- L224 _protected function_ `template <class OtherType> static TSharedRef<OtherType const> SharedThis(const OtherType* ThisPtr)`
- L229 _protected member_ `FOnlineServicesCommon& Services;`
- L232 _private member_ `TWeakPtr<ComponentType> WeakThis;`
- L233 _private member_ `FString InterfaceName;`
- L234 _private member_ `TMap<FString, TUniquePtr<IOnlineExecHandler>> ExecCommands;`
- L236 _private member_ `FOnlineAsyncOpQueueSerial SerialQueue;`
- L237 _private member_ `TMap<FAccountId, TUniquePtr<FOnlineAsyncOpQueueSerial>> PerUserSerialQueue;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L141 _typedef_ `using InterfaceType = typename Private::TOnlineInterfaceOperationMemberFunctionPtrTraits<T>::InterfaceType;` (scope `UE::Online::TOnlineComponent::RegisterCommand`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineComponentRegistry.h` (Public)


#### class `UE::Online::FOnlineComponentRegistry`  
`class FOnlineComponentRegistry`  
_L14-148_
- L21 _public function_ `template <typename ComponentType, typename... ParamTypes> void Register(ParamTypes&&... Params)` — Create and register a component of type ComponentType if one has not already been registered
- L35 _public function_ `template <typename ComponentType> void Unregister()` — Destroy and unregister a component of type ComponentType
- L48 _public function_ `template <typename ComponentType> ComponentType* Get() const` — Get the component of type ComponentType @return The component or null if one of ComponentType has not been registered
- L61 _public function_ `void AssignBaseSharedPtr(const FOnlineTypeName& TypeName, void* OutBaseInterfaceSP)` — Internal use only. Used to implement IOnlineServices::GetInterface()
- L74 _public function_ `template <typename CallableType, typename... ParamTypes> void Visit(CallableType&& Callable, ParamTypes&&... Params)` — Call a callable for each of the components
- L147 _private member_ `TArray<TUniquePtr<IComponentWrapper>> Components;`

#### class `UE::Online::FOnlineComponentRegistry::IComponentWrapper`  
`class IComponentWrapper`  
_L83-97_
- L86 _public prototype_ `virtual ~IComponentWrapper() = default;`
- L87 _public prototype_ `virtual void* GetBase() = 0;`
- L88 _public prototype_ `virtual void AssignBaseSharedPtr(void* OutSP) = 0;`
- L89 _public prototype_ `virtual bool IsA(FOnlineTypeName TypeName) const = 0;`
- L90 _public prototype_ `virtual FOnlineTypeName GetTypeName() const = 0;`
- L91 _public prototype_ `virtual IOnlineComponent* Get() = 0;`
- L92 _public prototype_ `virtual const IOnlineComponent* Get() const = 0;`
- L93 _public function_ `IOnlineComponent& operator*()`
- L94 _public function_ `const IOnlineComponent& operator*() const`
- L95 _public function_ `IOnlineComponent* operator->()`
- L96 _public function_ `const IOnlineComponent* operator->() const`

#### class `UE::Online::FOnlineComponentRegistry::TComponentWrapper`  
`template <typename T> class TComponentWrapper : public IComponentWrapper`  
_L100-145_
- inherits: `IComponentWrapper`
- L104 _public function_ `template <typename... TArgs> TComponentWrapper(TArgs&&... Args) : Object(Forward<TArgs>(Args)...)`
- L109 _public prototype_ `virtual ~TComponentWrapper() = default;`
- L111 _public function_ `virtual void* GetBase() override final`
- L116 _public function_ `virtual void AssignBaseSharedPtr(void* OutSP) override final`
- L123 _public function_ `virtual bool IsA(FOnlineTypeName TypeName) const override final`
- L128 _public function_ `virtual FOnlineTypeName GetTypeName() const override final`
- L133 _public function_ `virtual IOnlineComponent* Get() override final`
- L138 _public function_ `virtual const IOnlineComponent* Get() const override final`
- L144 _private member_ `T Object;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L38 _function_ `` (scope `UE::Online::FOnlineComponentRegistry::Unregister`)
- L51 _function_ `const TUniquePtr<IComponentWrapper>* WrappedComponent = Components.FindByPredicate([&TypeName](const TUniquePtr<IComponentWrapper>& WrappedComponent) { return WrappedComponent->IsA(TypeName); });` (scope `UE::Online::FOnlineComponentRegistry::Get`)
- L63 _function_ `const TUniquePtr<IComponentWrapper>* WrappedComponent = Components.FindByPredicate([&TypeName](const TUniquePtr<IComponentWrapper>& WrappedComponent) { return WrappedComponent->IsA(TypeName); });` (scope `UE::Online::FOnlineComponentRegistry::AssignBaseSharedPtr`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineConfig.h` (Public)


#### class `UE::Online::IOnlineConfigStruct`  
`class IOnlineConfigStruct`  
_L79-156_
- L82 _public prototype_ `virtual ~IOnlineConfigStruct() = default;`
- L84 _public prototype_ `virtual bool GetValue(const TCHAR* Key, FString& Value) = 0;`
- L85 _public prototype_ `virtual int32 GetValue(const TCHAR* Key, TArray<FString>& Value) = 0;`
- L86 _public prototype_ `virtual bool GetValue(const TCHAR* Key, IOnlineConfigStructPtr& Value) = 0;`
- L87 _public prototype_ `virtual int32 GetValue(const TCHAR* Key, TArray<IOnlineConfigStructPtr>& Value) = 0;`
- L90 _public function_ `template <typename T> bool GetValue(const TCHAR* Key, T& Value)`
- L120 _public function_ `template <typename T> int32 GetValue(const TCHAR* Key, TArray<T>& Value)`

#### class `UE::Online::IOnlineConfigProvider`  
`class IOnlineConfigProvider`  
_L178-275_
- desc: Interface for retrieving config values used by OnlineServices implementations For all the GetValue functions, Section will correspond to the section in an ini file, but can be interpreted in other ways by an IOnlineConfigProvider implementation to allow for OnlineServices implementations to use an alternative configuration file. By convention, all sections of the OnlineServices implementations will take the following format: OnlineServices.<ServicesProvider>.<OptionalInterface>.<OptionalOperation> <OptionalOverride> For example, valid sections include the following: OnlineServices.Null OnlineServices.Null.Auth OnlineServices.Null.Auth.Login OnlineServices.Null.Auth.Login Prod Implementations must at a minimum implement the FString and TArray<FString> GetValue. The others are optional, and the default implementation will convert strings to the appropriate data type, but can be overridden in cases where the underlying configuration system stores integers, floats, etc directly instead of as strings
- L181 _public prototype_ `virtual ~IOnlineConfigProvider() = default;`
- L192 _public prototype_ `virtual bool GetValue(const TCHAR* Section, const TCHAR* Key, FString& Value) = 0;` — Get a FString value @param Section Section to read the value from @param Key Key in the section for the value @param Value FString value read from the config. Will be unchanged if not present @return true if a value was read
- L203 _public prototype_ `virtual int32 GetValue(const TCHAR* Section, const TCHAR* Key, TArray<FString>& Value) = 0;` — Get an value consisting of a TArray of FStrings @param Section Section to read the value from @param Key Key in the section for the value @param Value Array of FStrings read from the config. Will be empty if not present @return number of values in the array
- L205 _public prototype_ `virtual bool GetValue(const TCHAR* Section, const TCHAR* Key, IOnlineConfigStructPtr& Value) = 0;`
- L207 _public prototype_ `virtual int32 GetValue(const TCHAR* Section, const TCHAR* Key, TArray<IOnlineConfigStructPtr>& Value) = 0;`
- L210 _public function_ `template <typename T> bool GetValue(const TCHAR* Section, const TCHAR* Key, T& Value)`
- L240 _public function_ `template <typename T> int32 GetValue(const TCHAR* Section, const TCHAR* Key, TArray<T>& Value)`

#### class `UE::Online::FOnlineConfigStructGConfig`  
`class FOnlineConfigStructGConfig : public IOnlineConfigStruct`  
_L277-304_
- inherits: `IOnlineConfigStruct`
- L280 _public prototype_ `virtual ~FOnlineConfigStructGConfig() = default;`
- L282 _public prototype_ `virtual bool GetValue(const TCHAR* Key, FString& Value) override;`
- L283 _public prototype_ `virtual int32 GetValue(const TCHAR* Key, TArray<FString>& Value) override;`
- L284 _public prototype_ `virtual bool GetValue(const TCHAR * Key, IOnlineConfigStructPtr& Value) override;`
- L285 _public prototype_ `virtual int32 GetValue(const TCHAR* Key, TArray<IOnlineConfigStructPtr>& Value) override;`
- L291 _public function_ `FOnlineConfigStructGConfig(FPrivateToken)`
- L298 _private prototype_ `static IOnlineConfigStructPtr CreateStruct(const FString& InConfigValue);`
- L299 _private prototype_ `static TArray<IOnlineConfigStructPtr> CreateStructArray(const FString& InConfigValue);`
- L300 _private prototype_ `static const TCHAR* ParseStruct(const TCHAR* InStr, IOnlineConfigStructPtr& OutPtr);`
- L301 _private prototype_ `static TArray<FString> CreateValueArray(const FString& InConfigValue);`
- L303 _private member_ `TMap<FString, FString> StructMembers;`

#### struct `UE::Online::FOnlineConfigStructGConfig::FPrivateToken`  
`struct FPrivateToken`  
_L288-288_
- L288 _public prototype_ `struct FPrivateToken`

#### class `UE::Online::FOnlineConfigProviderGConfig`  
`class FOnlineConfigProviderGConfig : public IOnlineConfigProvider`  
_L309-325_
- inherits: `IOnlineConfigProvider`
- desc: IOnlineConfigProvider implementation that uses GConfig to retrieve values
- L312 _public function_ `FOnlineConfigProviderGConfig(const FString& InConfigFile) : ConfigFile(InConfigFile)`
- L316 _public prototype_ `virtual ~FOnlineConfigProviderGConfig() = default;`
- L318 _public prototype_ `virtual bool GetValue(const TCHAR* Section, const TCHAR* Key, FString& Value) override;`
- L319 _public prototype_ `virtual int32 GetValue(const TCHAR* Section, const TCHAR* Key, TArray<FString>& Value) override;`
- L320 _public prototype_ `virtual bool GetValue(const TCHAR* Section, const TCHAR* Key, IOnlineConfigStructPtr& Value) override;`
- L321 _public prototype_ `virtual int32 GetValue(const TCHAR* Section, const TCHAR* Key, TArray<IOnlineConfigStructPtr>& Value) override;`
- L324 _private member_ `FString ConfigFile;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Online`)
- L17 _variable_ `template <typename T> constexpr bool MissingCase = false;` (scope `UE::Online::Private`)
- L20 _function_ `template <typename T> T ParseValueFromString(const FString& StringValue)` (scope `UE::Online::Private`)
- L77 _typedef_ `using IOnlineConfigStructPtr = TSharedPtr<IOnlineConfigStruct>;` (scope `UE::Online`)
- L100 _function_ `` (scope `UE::Online::IOnlineConfigStruct::GetValue`)
- L220 _function_ `` (scope `UE::Online::IOnlineConfigProvider::GetValue`)
- L327 _namespace_ `namespace Private` (scope `UE::Online`)
- L330 _function_ `template <typename T> bool LoadConfigStructMemberValue(IOnlineConfigStruct& ConfigStruct, const TCHAR* Key, T& Value)` (scope `UE::Online::Private`)
- L344 _function_ `template <typename T> bool LoadConfigValue(IOnlineConfigProvider& Provider, const TCHAR* Section, const TCHAR* Key, T& Value)` (scope `UE::Online::Private`)
- L370 _function_ `template <typename T> auto LoadConfig(IOnlineConfigProvider& Provider, const FString& Section, T& Value) -> std::enable_if_t<TModels_V<Meta::COnlineMetadataAvailable, T>, bool>` (scope `UE::Online`) — Populate a struct from a config provider. Loads each field in the struct by matching field names with keys in the config section. Requires that the type metadata is specified for StructType @param Provider The config provider @param Section The section of the config to load the values from @param Value The struct whose fields will be loaded from config @return true if any values were loaded
- L376 _function_ `` (scope `UE::Online::LoadConfig`)
- L393 _function_ `template <typename T> auto LoadConfig(IOnlineConfigProvider& Provider, const TArray<FString>& SectionHierarchy, T& Value) -> std::enable_if_t<TModels_V<Meta::COnlineMetadataAvailable, T>, bool>` (scope `UE::Online`) — Populate a struct from a config provider. Iterates through each section in SectionHierarchy, loading each field in the struct by matching field names with keys in the section. Requires that the type metadata is specified for StructType @param Provider The config provider @param SectionHierarchy The config sections to load values from @param Value The struct whose fields will be loaded from config @return true if any values were loaded
- L421 _function_ `template <typename T> auto LoadConfig(IOnlineConfigProvider& Provider, const FString& Section, const TCHAR* Key, T& OutValue) -> std::enable_if_t<TModels_V<Meta::COnlineMetadataAvailable, T>, bool>` (scope `UE::Online`) — Populate a struct from a config provider. Loads the struct from the _value_ of the given key in the given config section. Requires that the type metadata is specified for StructType, and that the config value is in config struct syntax. @param Provider The config provider @param Section The section of the config where the struct resides @param Key The key in the config section where the struct resides @param Value The struct whose fields will be loaded from config @return true if any values were loaded
- L454 _function_ `template <typename T> auto LoadConfig(IOnlineConfigProvider& Provider, const TArray<FString>& SectionHierarchy, const TCHAR* Key, T& Value) -> std::enable_if_t<TModels_V<Meta::COnlineMetadataAvailable, T>, bool>` (scope `UE::Online`) — Populate a struct from a config provider. Iterates through each section in SectionHierarchy, loading the struct from the _value_ of the given key in the given config section. Requires that the type metadata is specified for StructType, and that the config value is in config struct syntax. @param Provider The config provider @param SectionHierarchy The config sections to load values from @param Key The key in the config section where the struct resides @param Value The struct whose fields will be loaded from config @return true if any values were loaded

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineExecHandler.h` (Public)


#### class `UE::Online::IOnlineExecHandler`  
`class IOnlineExecHandler`  
_L66-72_
- L69 _public prototype_ `virtual ~IOnlineExecHandler() = default;`
- L70 _public prototype_ `virtual bool Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) = 0;`
- L71 _public prototype_ `virtual bool Help(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) = 0;`

#### struct `UE::Online::Private::TOnlineInterfaceOperationMemberFunctionPtrTraits`  
`template <typename TInterface, typename TOp> struct TOnlineInterfaceOperationMemberFunctionPtrTraits<TOnlineResult<TOp>(TInterface::*)(typename TOp::Params&&)>`  
_L80-85_
- L82 _public typedef_ `using InterfaceType = TInterface;`
- L83 _public typedef_ `using OpType = TOp;`
- L84 _public member_ `static constexpr bool bAsync = false;`
- L100 _public member_ `static constexpr bool bAsync = true;`

#### struct `UE::Online::Private::TOnlineInterfaceOperationMemberFunctionPtrTraits`  
`template <typename TInterface, typename TOp> struct TOnlineInterfaceOperationMemberFunctionPtrTraits<TOnlineResult<TOp>(TInterface::*)(typename TOp::Params&&) const>`  
_L88-93_
- L82 _public typedef_ `using InterfaceType = TInterface;`
- L83 _public typedef_ `using OpType = TOp;`
- L84 _public member_ `static constexpr bool bAsync = false;`
- L100 _public member_ `static constexpr bool bAsync = true;`

#### struct `UE::Online::Private::TOnlineInterfaceOperationMemberFunctionPtrTraits`  
`template <typename TInterface, typename TOp> struct TOnlineInterfaceOperationMemberFunctionPtrTraits<TOnlineAsyncOpHandle<TOp>(TInterface::*)(typename TOp::Params&&)>`  
_L96-101_
- L82 _public typedef_ `using InterfaceType = TInterface;`
- L83 _public typedef_ `using OpType = TOp;`
- L84 _public member_ `static constexpr bool bAsync = false;`
- L100 _public member_ `static constexpr bool bAsync = true;`

#### struct `UE::Online::Private::TOnlineInterfaceOperationMemberFunctionPtrTraits`  
`template <typename TInterface, typename TOp> struct TOnlineInterfaceOperationMemberFunctionPtrTraits<TOnlineAsyncOpHandle<TOp>(TInterface::*)(typename TOp::Params&&) const>`  
_L104-109_
- L82 _public typedef_ `using InterfaceType = TInterface;`
- L83 _public typedef_ `using OpType = TOp;`
- L84 _public member_ `static constexpr bool bAsync = false;`
- L100 _public member_ `static constexpr bool bAsync = true;`

#### struct `UE::Online::Private::TOnlineVariantVisitInfo`  
`template<typename T, typename VariantObject> struct TOnlineVariantVisitInfo`  
_L133-145_
- L139 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("[GAR`
- L141 _public function_ `static bool Assign(FString& VariantValue, VariantObject& Variant, IOnlineServices* Services)`
- L151 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i"),TEXT("i64"),TEXT("int"),TEXT`
- L164 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i32"),TEXT("in`
- L178 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("d"),TEXT("doub`
- L191 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("f"),TEXT("floa`
- L204 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("b"),TEXT("bool"),TEXT("`
- L218 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("s"),TEXT("str"),TEXT("s`
- L231 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("u"),TEXT("use`

#### struct `UE::Online::Private::TOnlineVariantVisitInfo`  
`template< typename VariantObject > struct TOnlineVariantVisitInfo<int64, VariantObject>`  
_L148-158_
- L139 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("[GAR`
- L141 _public function_ `static bool Assign(FString& VariantValue, VariantObject& Variant, IOnlineServices* Services)`
- L151 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i"),TEXT("i64"),TEXT("int"),TEXT`
- L164 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i32"),TEXT("in`
- L178 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("d"),TEXT("doub`
- L191 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("f"),TEXT("floa`
- L204 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("b"),TEXT("bool"),TEXT("`
- L218 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("s"),TEXT("str"),TEXT("s`
- L231 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("u"),TEXT("use`

#### struct `UE::Online::Private::TOnlineVariantVisitInfo`  
`template< typename VariantObject > struct TOnlineVariantVisitInfo<int32, VariantObject>`  
_L161-171_
- L139 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("[GAR`
- L141 _public function_ `static bool Assign(FString& VariantValue, VariantObject& Variant, IOnlineServices* Services)`
- L151 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i"),TEXT("i64"),TEXT("int"),TEXT`
- L164 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i32"),TEXT("in`
- L178 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("d"),TEXT("doub`
- L191 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("f"),TEXT("floa`
- L204 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("b"),TEXT("bool"),TEXT("`
- L218 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("s"),TEXT("str"),TEXT("s`
- L231 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("u"),TEXT("use`

#### struct `UE::Online::Private::TOnlineVariantVisitInfo`  
`template< typename VariantObject > struct TOnlineVariantVisitInfo<double, VariantObject>`  
_L175-185_
- L139 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("[GAR`
- L141 _public function_ `static bool Assign(FString& VariantValue, VariantObject& Variant, IOnlineServices* Services)`
- L151 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i"),TEXT("i64"),TEXT("int"),TEXT`
- L164 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i32"),TEXT("in`
- L178 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("d"),TEXT("doub`
- L191 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("f"),TEXT("floa`
- L204 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("b"),TEXT("bool"),TEXT("`
- L218 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("s"),TEXT("str"),TEXT("s`
- L231 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("u"),TEXT("use`

#### struct `UE::Online::Private::TOnlineVariantVisitInfo`  
`template< typename VariantObject > struct TOnlineVariantVisitInfo<float, VariantObject>`  
_L188-198_
- L139 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("[GAR`
- L141 _public function_ `static bool Assign(FString& VariantValue, VariantObject& Variant, IOnlineServices* Services)`
- L151 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i"),TEXT("i64"),TEXT("int"),TEXT`
- L164 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i32"),TEXT("in`
- L178 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("d"),TEXT("doub`
- L191 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("f"),TEXT("floa`
- L204 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("b"),TEXT("bool"),TEXT("`
- L218 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("s"),TEXT("str"),TEXT("s`
- L231 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("u"),TEXT("use`

#### struct `UE::Online::Private::TOnlineVariantVisitInfo`  
`template< typename VariantObject > struct TOnlineVariantVisitInfo<bool, VariantObject>`  
_L201-211_
- L139 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("[GAR`
- L141 _public function_ `static bool Assign(FString& VariantValue, VariantObject& Variant, IOnlineServices* Services)`
- L151 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i"),TEXT("i64"),TEXT("int"),TEXT`
- L164 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i32"),TEXT("in`
- L178 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("d"),TEXT("doub`
- L191 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("f"),TEXT("floa`
- L204 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("b"),TEXT("bool"),TEXT("`
- L218 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("s"),TEXT("str"),TEXT("s`
- L231 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("u"),TEXT("use`

#### struct `UE::Online::Private::TOnlineVariantVisitInfo`  
`template< typename VariantObject > struct TOnlineVariantVisitInfo<FString, VariantObject>`  
_L215-225_
- L139 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("[GAR`
- L141 _public function_ `static bool Assign(FString& VariantValue, VariantObject& Variant, IOnlineServices* Services)`
- L151 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i"),TEXT("i64"),TEXT("int"),TEXT`
- L164 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i32"),TEXT("in`
- L178 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("d"),TEXT("doub`
- L191 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("f"),TEXT("floa`
- L204 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("b"),TEXT("bool"),TEXT("`
- L218 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("s"),TEXT("str"),TEXT("s`
- L231 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("u"),TEXT("use`

#### struct `UE::Online::Private::TOnlineVariantVisitInfo`  
`template< typename VariantObject > struct TOnlineVariantVisitInfo<FAccountId, VariantObject>`  
_L228-244_
- L139 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("[GAR`
- L141 _public function_ `static bool Assign(FString& VariantValue, VariantObject& Variant, IOnlineServices* Services)`
- L151 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i"),TEXT("i64"),TEXT("int"),TEXT`
- L164 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("i32"),TEXT("in`
- L178 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("d"),TEXT("doub`
- L191 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("f"),TEXT("floa`
- L204 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("b"),TEXT("bool"),TEXT("`
- L218 _public member_ `inline static const TCHAR* Prefixes[] = { TEXT("s"),TEXT("str"),TEXT("s`
- L231 _public member_ `inline static const TCHAR* Prefixes[] = {TEXT("u"),TEXT("use`

#### class `UE::Online::TOnlineInterfaceOperationExecHandler`  
`template <typename InterfaceType, typename MemberFunctionPtrType> class TOnlineInterfaceOperationExecHandler : public IOnlineExecHandler`  
_L907-978_
- inherits: `IOnlineExecHandler`
- L910 _public typedef_ `using OpType = typename Private::TOnlineInterfaceOperationMemberFunctionPtrTraits<MemberFunctionPtrType>::OpType;`
- L912 _public function_ `TOnlineInterfaceOperationExecHandler(InterfaceType* InInterface, MemberFunctionPtrType InFunction) : Interface(InInterface) , Function(InFunction)`
- L918 _public function_ `virtual bool Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) override`
- L961 _public function_ `virtual bool Help(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) override`
- L976 _private member_ `InterfaceType* Interface;`
- L977 _private member_ `MemberFunctionPtrType Function;`

#### class `UE::Online::TOnlineComponentExecHandler`  
`template <typename T> class TOnlineComponentExecHandler : public IOnlineExecHandler`  
_L982-1002_
- inherits: `IOnlineExecHandler`
- desc: Creates an exec handler for an object that provides Exec and Help
- L985 _public function_ `TOnlineComponentExecHandler(T* InComponent) : Component(InComponent)`
- L990 _public function_ `virtual bool Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) override`
- L995 _public function_ `virtual bool Help(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) override`
- L1001 _private member_ `T* Component;`

#### class `UE::Online::FOnlineFunctionExecHandler`  
`class FOnlineFunctionExecHandler : public IOnlineExecHandler`  
_L1005-1037_
- inherits: `IOnlineExecHandler`
- desc: Creates an exec handler for anything that can be stored in a TFunction
- L1008 _public typedef_ `using FunctionType = TFunction<bool(UWorld*,const TCHAR*,FOutputDevice&)>;`
- L1010 _public function_ `FOnlineFunctionExecHandler(FunctionType&& InFunction, FString&& InHelpString) : Function(MoveTemp(InFunction)) , HelpString(MoveTemp(InHelpString))`
- L1016 _public function_ `virtual bool Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) override`
- L1028 _public function_ `virtual bool Help(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) override`
- L1035 _private member_ `FunctionType Function;`
- L1036 _private member_ `FString HelpString;`

#### class `UE::Online::TOnlineMemberFunctionExecHandler`  
`template <typename T> class TOnlineMemberFunctionExecHandler : public IOnlineExecHandler`  
_L1041-1068_
- inherits: `IOnlineExecHandler`
- desc: Creates an exec handler that calls a class member function
- L1044 _public typedef_ `using MemberFunctionPtrType = bool(T::*)(UWorld*,const TCHAR*,FOutputDevice&);`
- L1046 _public function_ `TOnlineMemberFunctionExecHandler(T* InObject, MemberFunctionPtrType InFunction, FString&& InHelpString) : Object(InObject) , Function(InFunction) , HelpString(MoveTemp(InHelpString))`
- L1053 _public function_ `virtual bool Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) override`
- L1058 _public function_ `virtual bool Help(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) override`
- L1065 _private member_ `T* Object;`
- L1066 _private member_ `MemberFunctionPtrType Function;`
- L1067 _private member_ `FString HelpString;`

#### Free symbols / members of external scopes

- L64 _namespace_ `namespace UE`
- L64 _namespace_ `namespace Online` (scope `UE`)
- L74 _namespace_ `namespace Private` (scope `UE::Online`)
- L112 _prototype_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, FString& Value, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`) — Forward declarations for dependent type resolution
- L113 _prototype_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, FName& Value, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L114 _prototype_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, uint8& Value, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L115 _prototype_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, int32& Value, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L116 _prototype_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, uint32& Value, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L117 _prototype_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, int64& Value, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L118 _prototype_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, uint64& Value, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L119 _prototype_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, bool& Value, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L120 _prototype_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, FDateTime& Value, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L121 _prototype_ `template <typename T> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TArray<T>& Array, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L125 _prototype_ `template <typename T, typename U> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TMap<T, U>& Map, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L126 _prototype_ `template <typename T> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TSet<T>& Set, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L127 _prototype_ `template <typename T> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TSharedPtr<T>& Ptr, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L128 _prototype_ `template <typename T> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TSharedRef<T>& Ref, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L129 _prototype_ `template <typename T> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TOptional<T>& Optional, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L130 _prototype_ `template <typename... Ts> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TVariant<Ts...>& Variant, IOnlineServices* Services = nullptr);` (scope `UE::Online::Private`)
- L247 _macro_ `#define MAKE_VARIANT_ENUM_INFO_SHORTNAME(EnumName, ShortName) template< typename VariantObject >\`
- L261 _macro_ `#define MAKE_VARIANT_ENUM_INFO(EnumName) MAKE_VARIANT_ENUM_INFO_SHORTNAME(EnumName, EnumName);`
- L264 _function_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, FString& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L274 _function_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, FName& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L286 _function_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, FUtf8String& Value, IOnlineServices* Services = nullptr)` (scope `UE::Online::Private`)
- L298 _function_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, uint8& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L313 _function_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, int32& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L328 _function_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, uint32& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L343 _function_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, int64& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L358 _function_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, uint64& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L373 _function_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, bool& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L388 _function_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, FDateTime& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L401 _function_ `inline bool ParseOnlineExecParams(const TCHAR*& Cmd, FPlatformUserId& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L416 _function_ `inline TCHAR PeekNextChar(const TCHAR* Cmd)` (scope `UE::Online::Private`)
- L427 _function_ `inline bool ParseTokenExt(const TCHAR*& Str, FString& Arg, bool UseEscape, bool bCommaSeparated = false, bool bIncludeDelimiters = false)` (scope `UE::Online::Private`) — taken from FParse::Token, functionality added (possibly can be merged back?)
- L585 _function_ `template <typename T> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TArray<T>& Array, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L612 _function_ `template <typename T, typename U> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TMap<T, U>& Map, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L667 _function_ `template <typename T> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TSet<T>& Set, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L694 _function_ `template <typename T> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TSharedPtr<T>& Ptr, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L717 _function_ `template <typename T> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TSharedRef<T>& Ref, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L723 _function_ `template <typename T> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TOptional<T>& Optional, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L749 _function_ `template<typename VariantType, typename LastType> static bool VisitVariantTypes(VariantType& Variant, FString& VariantPrefix, FString& VariantValue, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L762 _function_ `template<typename VariantType, typename FirstType, typename SecondType, typename... RemainingTypes> inline bool VisitVariantTypes(VariantType& Variant, FString& VariantPrefix, FString& VariantValue, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L776 _function_ `template <typename... Ts> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TVariant<Ts...>& Variant, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L793 _function_ `template<typename IdType> inline bool ParseOnlineExecParams(const TCHAR*& Cmd, TOnlineId<IdType>& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L815 _function_ `template<> inline bool ParseOnlineExecParams<OnlineIdHandleTags::FAccount>(const TCHAR*& Cmd, TOnlineId<OnlineIdHandleTags::FAccount>& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L861 _function_ `template <typename T> std::enable_if_t<!TModels_V<Meta::COnlineMetadataAvailable, T>, bool> ParseOnlineExecParams(const TCHAR*& Cmd, T& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L878 _function_ `template <typename T> std::enable_if_t<TModels_V<Meta::COnlineMetadataAvailable, T>, bool> ParseOnlineExecParams(const TCHAR*& Cmd, T& Value, IOnlineServices* Services)` (scope `UE::Online::Private`)
- L887 _function_ `` (scope `UE::Online::Private::ParseOnlineExecParams`)
- L925 _function_ `` (scope `UE::Online::TOnlineInterfaceOperationExecHandler::Exec`)
- L965 _function_ `` (scope `UE::Online::TOnlineInterfaceOperationExecHandler::Help`)
- L1071 _function_ `inline TUniquePtr<IOnlineExecHandler> MakeExecHandler(TFunction<bool(UWorld*, const TCHAR*, FOutputDevice&)>&& Function, FString&& HelpString = FString())` (scope `UE::Online`) — Creates an exec handler for anything that can be stored in a TFunction
- L1078 _function_ `template <typename T> TUniquePtr<IOnlineExecHandler> MakeExecHandler(T* Object, bool(T::*Function)(UWorld*, const TCHAR*, FOutputDevice&), FString&& HelpString = FString())` (scope `UE::Online`) — Creates an exec handler that calls a class member function

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineIdCommon.h` (Public)


#### class `UE::Online::TOnlineBasicIdRegistry`  
`template<typename IdType, typename IdValueType> class TOnlineBasicIdRegistry`  
_L17-93_
- desc: A net id registry suitable for use with trivial immutable keys
- L20 _public function_ `TOnlineBasicIdRegistry(EOnlineServices InOnlineServicesType) : OnlineServicesType(InOnlineServicesType)`
- L26 _public prototype_ `virtual ~TOnlineBasicIdRegistry() = default;`
- L28 _public typedef_ `using HandleType = TOnlineId<IdType>;`
- L30 _public function_ `HandleType GetInvalidHandle() const`
- L35 _public function_ `HandleType FindHandle(const IdValueType& IdValue) const`
- L45 _public function_ `HandleType FindOrAddHandle(const IdValueType& IdValue)`
- L68 _public function_ `IdValueType FindIdValue(const HandleType& Handle) const` — Returns a copy as it's not thread safe to return a pointer/ref to an element of an array that can be relocated by another thread.
- L81 _public function_ `inline bool ValidateOnlineId(const HandleType& Handle) const`
- L87 _private member_ `EOnlineServices OnlineServicesType;`
- L89 _private member_ `mutable FTransactionallySafeRWLock Lock;`
- L91 _private member_ `TArray<IdValueType> IdValues;`
- L92 _private member_ `TMap<IdValueType, HandleType> IdValueToHandleMap;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L96 _typedef_ `template<typename IdValueType> using TOnlineBasicAccountIdRegistry = TOnlineBasicIdRegistry<OnlineIdHandleTags::FAccount, IdValueType>;` (scope `UE::Online`)
- L99 _typedef_ `template<typename IdValueType> using TOnlineBasicSessionIdRegistry = TOnlineBasicIdRegistry<OnlineIdHandleTags::FSession, IdValueType>;` (scope `UE::Online`)
- L102 _typedef_ `template<typename IdValueType> using TOnlineBasicSessionInviteIdRegistry = TOnlineBasicIdRegistry<OnlineIdHandleTags::FSessionInvite, IdValueType>;` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineServicesCommon.h` (Public)


#### class `UE::Online::FOnlineServicesCommon`  
`class FOnlineServicesCommon : public IOnlineServices , public FTSTickerObjectBase , public FSelfRegisteringExec`  
_L19-408_
- inherits: `IOnlineServices,FTSTickerObjectBase,FSelfRegisteringExec`
- L25 _public typedef_ `using Super = IOnlineServices;`
- L27 _public prototype_ `FOnlineServicesCommon(const FString& InServiceConfigName, FName InInstanceName, FName InInstanceConfigName);`
- L28 _public prototype_ `FOnlineServicesCommon(const FOnlineServicesCommon&) = delete;`
- L29 _public prototype_ `FOnlineServicesCommon(FOnlineServicesCommon&&) = delete;`
- L30 _public prototype_ `virtual ~FOnlineServicesCommon();`
- L33 _public prototype_ `virtual void Init() override;` — IOnlineServices
- L34 _public prototype_ `virtual void Destroy() override;`
- L35 _public prototype_ `virtual IAchievementsPtr GetAchievementsInterface() override;`
- L36 _public prototype_ `virtual IAuthPtr GetAuthInterface() override;`
- L37 _public prototype_ `virtual IUserInfoPtr GetUserInfoInterface() override;`
- L38 _public prototype_ `virtual ICommercePtr GetCommerceInterface() override;`
- L39 _public prototype_ `virtual ISocialPtr GetSocialInterface() override;`
- L40 _public prototype_ `virtual IPresencePtr GetPresenceInterface() override;`
- L41 _public prototype_ `virtual IExternalUIPtr GetExternalUIInterface() override;`
- L42 _public prototype_ `virtual ILeaderboardsPtr GetLeaderboardsInterface() override;`
- L43 _public prototype_ `virtual ILobbiesPtr GetLobbiesInterface() override;`
- L44 _public prototype_ `virtual ISessionsPtr GetSessionsInterface() override;`
- L45 _public prototype_ `virtual IStatsPtr GetStatsInterface() override;`
- L46 _public prototype_ `virtual IConnectivityPtr GetConnectivityInterface() override;`
- L47 _public prototype_ `virtual IPrivilegesPtr GetPrivilegesInterface() override;`
- L48 _public prototype_ `virtual ITitleFilePtr GetTitleFileInterface() override;`
- L49 _public prototype_ `virtual IUserFilePtr GetUserFileInterface() override;`
- L50 _public prototype_ `virtual TOnlineResult<FGetResolvedConnectString> GetResolvedConnectString(FGetResolvedConnectString::Params&& Params) override;`
- L51 _public prototype_ `virtual FName GetInstanceName() const override;`
- L52 _public prototype_ `virtual FName GetInstanceConfigName() const override;`
- L53 _public prototype_ `virtual void AssignBaseInterfaceSharedPtr(const FOnlineTypeName& TypeName, void* OutBaseInterfaceSP) override final;`
- L61 _public function_ `template <typename ComponentType> ComponentType* Get()` — Retrieve any of the Interface IOnlineComponents
- L69 _public prototype_ `virtual void RegisterComponents();` — Called to register all the IOnlineComponents with the IOnlineService, called after this is constructed
- L74 _public prototype_ `virtual void Initialize();` — Calls Initialize on all the components, called after RegisterComponents
- L79 _public prototype_ `virtual void PostInitialize();` — Calls PostInitialize on all the components, called after Initialize
- L84 _public prototype_ `virtual void UpdateConfig();` — Calls UpdateConfig on all the components
- L89 _public prototype_ `virtual bool Tick(float DeltaSeconds) override;` — Calls Tick on all the components
- L94 _public prototype_ `virtual void PreShutdown();` — Calls PreShutdown on all the components, called prior to Shutdown
- L99 _public prototype_ `virtual void Shutdown();` — Calls Shutdown on all the components, called before this is destructed
- L105 _public function_ `template <typename CallableType> void Execute(FOnlineAsyncExecutionPolicy ExecutionPolicy, CallableType&& Callable)` — Call a callable according to a specified execution policy
- L135 _public function_ `template <typename CallableType> void ExecuteOnGameThread(CallableType&& Callable)` — Call a callable on the game thread
- L150 _public function_ `void SetConfigProvider(TUniquePtr<IOnlineConfigProvider>&& InConfigProvider)` — Override the default config provider (FOnlineConfigProviderGConfig(GEngineini))
- L158 _public function_ `void ResetConfigSectionOverrides()` — Clear the list of config overrides
- L166 _public function_ `void AddConfigSectionOverride(const FString& Override)` — Add a config section override. These will be used in the order they are added
- L174 _public function_ `const FString& GetServiceConfigName() const` — Get the ini config name for the Subsystem
- L177 _public function_ `TArray<FString> GetConfigSectionHeiarchy(const FString& OperationName = FString()) const` — `UE_DEPRECATED(5.6, "GetConfigSectionHeiarchy has been renamed GetConfigSectionHierarchy")`
- L183 _public function_ `TArray<FString> GetConfigSectionHeirarchy(const FString& OperationName = FString()) const` — `UE_DEPRECATED(5.8, "GetConfigSectionHeirarchy has been renamed GetConfigSectionHierarchy")`
- L188 _public function_ `TArray<FString> GetConfigSectionHierarchy(const FString& OperationName = FString()) const`
- L223 _public function_ `template <typename StructType> bool LoadConfig(StructType& Struct, const FString& InterfaceName = FString(), const FString& OperationName = FString()) const` — Load a config struct for an interface + operation Will load values from the following sections, skipping all with any empty strings: OnlineServices OnlineServices.<InterfaceName> OnlineServices.<InterfaceName>.<OperationName> OnlineServices.<ServiceProvider> OnlineServices.<ServiceProvider>.<InterfaceName> OnlineServices.<ServiceProvider>.<InterfaceName>.<OperationName> OnlineServices.<ServiceProvider>.<InstanceConfigName> OnlineServices.<ServiceProvider>.<InstanceConfigName>.<InterfaceName> OnlineServices.<ServiceProvider>.<InstanceConfigName>.<InterfaceName>.<OperationName> @param Struct Struct to populate with values from config @param InterfaceName Optional interface name to append to the config section name @param OperationName Optional operation name to append to the config section name @return true if a value was loaded
- L252 _public function_ `TArray<FString> GetConfigSectionHeirachWithOverrides(const TArray<FString>& SectionHierarchy) const` — `UE_DEPRECATED(5.6, "GetConfigSectionHeirachWithOverrides has been renamed GetConfigSectionHierarchyWithOverrides")`
- L258 _public function_ `TArray<FString> GetConfigSectionHeirarchyWithOverrides(const TArray<FString>& SectionHierarchy) const` — `UE_DEPRECATED(5.8, "GetConfigSectionHeirarchyWithOverrides has been renamed GetConfigSectionHierarchyWithOverrides")`
- L270 _public function_ `TArray<FString> GetConfigSectionHierarchyWithOverrides(const TArray<FString>& SectionHierarchy) const` — Get an array of a config section with the overrides added in @param SectionHierarchy Array of config sections to load values from @return Array of the sections with overrides for values to be loaded from
- L307 _public function_ `template <typename StructType> bool LoadConfig(StructType& Struct, const TArray<FString>& SectionHierarchy) const` — Load a config struct for a section hierarchy, also using the ConfigSectionOverrides @param Struct Struct to populate with values from config @param SectionHierarchy Array of config sections to load values from @return true if a value was loaded
- L314 _public function_ `template <typename OpType> TOnlineAsyncOpRef<OpType> GetOp(typename OpType::Params&& Params)` — Get op (OnlineServices)
- L321 _public function_ `template <typename OpType, typename ParamsFuncsType = TJoinableOpParamsFuncs<OpType>> TOnlineAsyncOpRef<OpType> GetJoinableOp(typename OpType::Params&& Params)`
- L328 _public function_ `template <typename OpType, typename ParamsFuncsType = TMergeableOpParamsFuncs<OpType>> TOnlineAsyncOpRef<OpType> GetMergeableOp(typename OpType::Params&& Params)`
- L336 _public function_ `template <typename OpType> TOnlineAsyncOpRef<OpType> GetOp(typename OpType::Params&& Params, const TArray<FString>& ConfigSectionHierarchy)` — Get op (Interface)
- L343 _public function_ `template <typename OpType, typename ParamsFuncsType = TJoinableOpParamsFuncs<OpType>> TOnlineAsyncOpRef<OpType> GetJoinableOp(typename OpType::Params&& Params, const TArray<FString>& ConfigSectionHierarchy)`
- L350 _public function_ `template <typename OpType, typename ParamsFuncsType = TMergeableOpParamsFuncs<OpType>> TOnlineAsyncOpRef<OpType> GetMergeableOp(typename OpType::Params&& Params, const TArray<FString>& ConfigSectionHierarchy)`
- L357 _public prototype_ `FOnlineAsyncOpQueueParallel& GetParallelQueue();` — Queue for executing tasks in parallel. Serial queues feed into this
- L360 _public prototype_ `FOnlineAsyncOpQueue& GetSerialQueue();` — Queue for executing tasks in serial
- L363 _public prototype_ `FOnlineAsyncOpQueue& GetSerialQueue(const FAccountId& AccountId);` — Queues for executing per-user tasks in serial
- L365 _public prototype_ `void RegisterExecHandler(const FString& Name, TUniquePtr<IOnlineExecHandler>&& Handler);`
- L368 _public prototype_ `virtual bool Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L371 _public member_ `FOnlineAsyncOpCache OpCache;`
- L381 _protected function_ `template <typename OpType> void LogErrorIfOnlineServicesHasShutdown()`
- L386 _protected prototype_ `void Flush(EAsyncOpFlushReason FlushReason);`
- L387 _protected prototype_ `virtual void FlushTick(float DeltaSeconds);`
- L388 _protected prototype_ `void LoadCommonConfig();`
- L390 _protected member_ `TMap<FString, TUniquePtr<IOnlineExecHandler>> ExecCommands;`
- L392 _protected member_ `static uint32 NextInstanceIndex;`
- L393 _protected member_ `uint32 InstanceIndex;`
- L394 _protected member_ `FName InstanceName;`
- L395 _protected member_ `FName InstanceConfigName;`
- L397 _protected member_ `FOnlineComponentRegistry Components;`
- L398 _protected member_ `TUniquePtr<IOnlineConfigProvider> ConfigProvider;`
- L401 _protected member_ `TArray<FString> ConfigSectionOverrides;` — Config section overrides
- L402 _protected member_ `FString ServiceConfigName;`
- L404 _protected member_ `FOnlineAsyncOpQueueParallel ParallelQueue;`
- L405 _protected member_ `FOnlineAsyncOpQueueSerial SerialQueue;`
- L406 _protected member_ `TMap<FAccountId, TUniquePtr<FOnlineAsyncOpQueueSerial>> PerUserSerialQueue;`
- L407 _protected member_ `bool bPreShutdownComplete;`

#### enum `UE::Online::FOnlineServicesCommon::EAsyncOpFlushReason`  
`enum class EAsyncOpFlushReason : uint8`  
_L374-378_
- L376 _public enumerator_ `Default`
- L377 _public enumerator_ `Shutdown`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Online` (scope `UE`)
- L228 _function_ `` (scope `UE::Online::FOnlineServicesCommon::LoadConfig`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineServicesCommonDelegates.h` (Public)


#### struct `UE::Online::FOnOnlineAsyncOpCompletedParams`  
`struct FOnOnlineAsyncOpCompletedParams`  
_L15-35_
- desc: Notification params of OnOnlineAsyncOpCompletedV2 delegate
- L23 _public prototype_ `FOnOnlineAsyncOpCompletedParams(FOnlineServicesCommon& InOnlineServicesCommon, const TOptional<FOnlineError>& InOnlineError);` — FOnOnlineAsyncOpCompletedParams ctor @param OnlineServicesCommon the OnlineServices instance @param OnlineError the result of completed operation
- L26 _public member_ `FString OpName;` — The name of completed operation
- L28 _public member_ `FString InterfaceName;` — The name of interface
- L30 _public member_ `TWeakPtr<FOnlineServicesCommon> OnlineServicesCommon;` — The OnlineServices instance
- L32 _public member_ `TOptional<UE::Online::FOnlineError> OnlineError;` — The result of completed operation
- L34 _public member_ `double DurationInSeconds = -1.0;` — The duration of the operation from start to complete

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineAsyncOpCompletedV2, const FOnOnlineAsyncOpCompletedParams& Params);` — Notification that an online operation has completed !!!NOTE!!! The notification can happen on off-game threads, make sure the callbacks are thread-safe @param Params the struct FOnOnlineAsyncOpCompletedParams which contains related info
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineAsyncOpCompletedV2, const FOnOnlineAsyncOpCompletedParams& Params);` (scope `UE::Online`) — Notification that an online operation has completed !!!NOTE!!! The notification can happen on off-game threads, make sure the callbacks are thread-safe @param Params the struct FOnOnlineAsyncOpCompletedParams which contains related info
- L46 _externvar_ `extern FOnOnlineAsyncOpCompletedV2 OnOnlineAsyncOpCompletedV2;` (scope `UE::Online`) — `UE_DEPRECATED(5.7, "OnOnlineAsyncOpCompletedV2 has been deprecated, use OnAsyncOpCompleted instead")`

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/OnlineUtilsCommon.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)
- L10 _function_ `template <typename DataType, typename OpType> const DataType& GetOpDataChecked(const TOnlineAsyncOp<OpType>& Op, const FString& Key)` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/PresenceCommon.h` (Public)


#### class `UE::Online::FPresenceCommon`  
`class FPresenceCommon : public TOnlineComponent<IPresence>`  
_L14-37_
- inherits: `TOnlineComponent<IPresence>`
- L17 _public typedef_ `using Super = IPresence;`
- L19 _public prototype_ `FPresenceCommon(FOnlineServicesCommon& InServices);`
- L22 _public prototype_ `virtual void RegisterCommands() override;` — IOnlineComponent
- L23 _public prototype_ `virtual void UpdateConfig() override;`
- L26 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryPresence> QueryPresence(FQueryPresence::Params&& Params) override;` — IPresence
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FBatchQueryPresence> BatchQueryPresence(FBatchQueryPresence::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineResult<FGetCachedPresence> GetCachedPresence(FGetCachedPresence::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdatePresence> UpdatePresence(FUpdatePresence::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FPartialUpdatePresence> PartialUpdatePresence(FPartialUpdatePresence::Params&& Params) override;`
- L31 _public prototype_ `virtual TOnlineEvent<void(const FPresenceUpdated&)> OnPresenceUpdated() override;`
- L34 _protected member_ `FOnlineServicesCommon& Services;`
- L36 _protected member_ `TOnlineEventCallable<void(const FPresenceUpdated&)> OnPresenceUpdatedEvent;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/PrivilegesCommon.h` (Public)


#### class `UE::Online::FPrivilegesCommon`  
`class FPrivilegesCommon : public TOnlineComponent<IPrivileges>`  
_L14-28_
- inherits: `TOnlineComponent<IPrivileges>`
- L17 _public typedef_ `using Super = IPrivileges;`
- L19 _public prototype_ `FPrivilegesCommon(FOnlineServicesCommon& InServices);`
- L22 _public prototype_ `virtual void RegisterCommands() override;`
- L26 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryUserPrivilege> QueryUserPrivilege(FQueryUserPrivilege::Params&& Params) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/SessionsCommon.h` (Public)


#### class `UE::Online::FOnlineSessionIdStringRegistry`  
`class FOnlineSessionIdStringRegistry : public IOnlineSessionIdRegistry`  
_L17-85_
- inherits: `IOnlineSessionIdRegistry`
- L21 _public function_ `virtual inline FString ToString(const FOnlineSessionId& SessionId) const override`
- L33 _public function_ `virtual inline FString ToLogString(const FOnlineSessionId& SessionId) const override`
- L38 _public function_ `virtual inline TArray<uint8> ToReplicationData(const FOnlineSessionId& SessionId) const override`
- L51 _public function_ `virtual inline FOnlineSessionId FromReplicationData(const TArray<uint8>& ReplicationData) override`
- L58 _public function_ `virtual inline FOnlineSessionId FromStringData(const FString& StringData) override`
- L70 _public function_ `inline bool IsSessionIdExpired(const FOnlineSessionId& InSessionId) const`
- L75 _public function_ `FOnlineSessionIdStringRegistry(EOnlineServices OnlineServicesType) : BasicRegistry(OnlineServicesType)`
- L81 _public prototype_ `virtual ~FOnlineSessionIdStringRegistry() = default;`
- L84 _public member_ `TOnlineBasicSessionIdRegistry<FString> BasicRegistry;`

#### class `UE::Online::FOnlineSessionInviteIdStringRegistry`  
`class FOnlineSessionInviteIdStringRegistry : public IOnlineSessionInviteIdRegistry`  
_L87-150_
- inherits: `IOnlineSessionInviteIdRegistry`
- L91 _public function_ `virtual inline FString ToString(const FSessionInviteId& SessionInviteId) const override`
- L103 _public function_ `virtual inline FString ToLogString(const FSessionInviteId& SessionInviteId) const override`
- L108 _public function_ `virtual inline TArray<uint8> ToReplicationData(const FSessionInviteId& SessionInviteId) const override`
- L121 _public function_ `virtual inline FSessionInviteId FromReplicationData(const TArray<uint8>& ReplicationData) override`
- L128 _public function_ `virtual inline FSessionInviteId FromStringData(const FString& StringData) override`
- L140 _public function_ `FOnlineSessionInviteIdStringRegistry(EOnlineServices OnlineServicesType) : BasicRegistry(OnlineServicesType)`
- L146 _public prototype_ `virtual ~FOnlineSessionInviteIdStringRegistry() = default;`
- L149 _public member_ `TOnlineBasicSessionInviteIdRegistry<FString> BasicRegistry;`

#### class `UE::Online::FSessionCommon`  
`class FSessionCommon : public ISession`  
_L152-194_
- inherits: `ISession`
- L155 _public prototype_ `FSessionCommon() = default;`
- L156 _public prototype_ `FSessionCommon(const FSessionCommon& InSession) = default;`
- L157 _public prototype_ `virtual ~FSessionCommon() = default;`
- L160 _public function_ `virtual const FAccountId GetOwnerAccountId() const override` — ISession
- L161 _public function_ `virtual const FOnlineSessionId GetSessionId() const override`
- L162 _public function_ `virtual const uint32 GetNumOpenConnections() const override`
- L163 _public function_ `virtual const FSessionInfo& GetSessionInfo() const override`
- L164 _public function_ `virtual const FSessionSettings& GetSessionSettings() const override`
- L165 _public function_ `virtual const FSessionMemberIdsSet& GetSessionMembers() const override`
- L167 _public function_ `virtual bool IsJoinable() const override`
- L169 _public prototype_ `virtual FString ToLogString() const override;`
- L171 _public prototype_ `virtual void DumpState() const override;`
- L174 _protected prototype_ `void DumpMemberData() const;`
- L175 _protected prototype_ `void DumpSessionInfo() const;`
- L176 _protected prototype_ `void DumpSessionSettings() const;`
- L180 _public member_ `FSessionInfo SessionInfo;` — Session information that will remain constant throughout the session's lifetime
- L185 _public member_ `FAccountId OwnerAccountId;` — The user who currently owns the session
- L188 _public member_ `FSessionSettings SessionSettings;` — Set of session properties that can be altered by the session owner
- L191 _public member_ `FSessionMemberIdsSet SessionMembers;` — Set containing user ids for all the session members
- L193 _public prototype_ `FSessionCommon& operator+=(const FSessionUpdate& SessionUpdate);`

#### class `UE::Online::FSessionInviteCommon`  
`class FSessionInviteCommon : public ISessionInvite`  
_L196-221_
- inherits: `ISessionInvite`
- L199 _public prototype_ `FSessionInviteCommon() = default;`
- L200 _public prototype_ `FSessionInviteCommon(const FAccountId& InRecipientId, const FAccountId& InSenderId, const FSessionInviteId& InInviteId, const FOnlineSessionId& InSessionId);`
- L202 _public function_ `virtual const FAccountId GetRecipientId() const override`
- L203 _public function_ `virtual const FAccountId GetSenderId() const override`
- L204 _public function_ `virtual const FSessionInviteId GetInviteId() const override`
- L205 _public function_ `virtual const FOnlineSessionId GetSessionId() const override`
- L207 _public prototype_ `virtual FString ToLogString() const override;`
- L211 _public member_ `FAccountId RecipientId;` — The id handle for the user which the invite got sent to
- L214 _public member_ `FAccountId SenderId;` — The id handle for the user which sent the invite
- L217 _public member_ `FSessionInviteId InviteId;` — The invite id handle, needed for retrieving invite information and rejecting the invite
- L220 _public member_ `FOnlineSessionId SessionId;` — The session id handle, needed for retrieving the session information

#### struct `UE::Online::FGetMutableSessionByName`  
`struct FGetMutableSessionByName`  
_L223-236_
- L225 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetMutableSessionByName::Params`  
`struct Params`  
_L227-230_
- L229 _public member_ `FName LocalName;`

#### struct `UE::Online::FGetMutableSessionByName::Result`  
`struct Result`  
_L232-235_
- L234 _public member_ `TSharedRef<FSessionCommon> Session;`

#### struct `UE::Online::FGetMutableSessionById`  
`struct FGetMutableSessionById`  
_L238-251_
- L240 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetMutableSessionById::Params`  
`struct Params`  
_L242-245_
- L244 _public member_ `FOnlineSessionId SessionId;`

#### struct `UE::Online::FGetMutableSessionById::Result`  
`struct Result`  
_L247-250_
- L249 _public member_ `TSharedRef<FSessionCommon> Session;`

#### class `UE::Online::FSessionsCommon`  
`class FSessionsCommon : public TOnlineComponent<ISessions>`  
_L253-394_
- inherits: `TOnlineComponent<ISessions>`
- L256 _public typedef_ `using Super = ISessions;`
- L258 _public prototype_ `FSessionsCommon(FOnlineServicesCommon& InServices);`
- L261 _public prototype_ `virtual void Initialize() override;` — TOnlineComponent
- L262 _public prototype_ `virtual void RegisterCommands() override;`
- L265 _public prototype_ `virtual TOnlineResult<FGetAllSessions> GetAllSessions(FGetAllSessions::Params&& Params) const override;` — ISessions
- L266 _public prototype_ `virtual TOnlineResult<FGetSessionByName> GetSessionByName(FGetSessionByName::Params&& Params) const override;`
- L267 _public prototype_ `virtual TOnlineResult<FGetSessionName> GetSessionName(FGetSessionName::Params&& Params) const override;`
- L268 _public prototype_ `virtual TOnlineResult<FGetSessionById> GetSessionById(FGetSessionById::Params&& Params) const override;`
- L269 _public prototype_ `virtual TOnlineResult<FGetPresenceSession> GetPresenceSession(FGetPresenceSession::Params&& Params) const override;`
- L270 _public prototype_ `virtual TOnlineResult<FIsPresenceSession> IsPresenceSession(FIsPresenceSession::Params&& Params) const override;`
- L271 _public prototype_ `virtual TOnlineResult<FSetPresenceSession> SetPresenceSession(FSetPresenceSession::Params&& Params) override;`
- L272 _public prototype_ `virtual TOnlineResult<FClearPresenceSession> ClearPresenceSession(FClearPresenceSession::Params&& Params) override;`
- L273 _public prototype_ `virtual TOnlineAsyncOpHandle<FCreateSession> CreateSession(FCreateSession::Params&& Params) override;`
- L274 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdateSessionSettings> UpdateSessionSettings(FUpdateSessionSettings::Params&& Params) override;`
- L275 _public prototype_ `virtual TOnlineAsyncOpHandle<FLeaveSession> LeaveSession(FLeaveSession::Params&& Params) override;`
- L276 _public prototype_ `virtual TOnlineAsyncOpHandle<FFindSessions> FindSessions(FFindSessions::Params&& Params) override;`
- L277 _public prototype_ `virtual TOnlineAsyncOpHandle<FStartMatchmaking> StartMatchmaking(FStartMatchmaking::Params&& Params) override;`
- L278 _public prototype_ `virtual TOnlineAsyncOpHandle<FJoinSession> JoinSession(FJoinSession::Params&& Params) override;`
- L279 _public prototype_ `virtual TOnlineAsyncOpHandle<FAddSessionMember> AddSessionMember(FAddSessionMember::Params&& Params) override;`
- L280 _public prototype_ `virtual TOnlineAsyncOpHandle<FRemoveSessionMember> RemoveSessionMember(FRemoveSessionMember::Params&& Params) override;`
- L281 _public prototype_ `virtual TOnlineAsyncOpHandle<FSendSessionInvite> SendSessionInvite(FSendSessionInvite::Params&& Params) override;`
- L282 _public prototype_ `virtual TOnlineResult<FGetSessionInviteById> GetSessionInviteById(FGetSessionInviteById::Params&& Params) override;`
- L283 _public prototype_ `virtual TOnlineResult<FGetAllSessionInvites> GetAllSessionInvites(FGetAllSessionInvites::Params&& Params) override;`
- L284 _public prototype_ `virtual TOnlineAsyncOpHandle<FRejectSessionInvite> RejectSessionInvite(FRejectSessionInvite::Params&& Params) override;`
- L286 _public prototype_ `virtual TOnlineEvent<void(const FSessionCreated&)> OnSessionCreated() override;`
- L287 _public prototype_ `virtual TOnlineEvent<void(const FSessionJoined&)> OnSessionJoined() override;`
- L288 _public prototype_ `virtual TOnlineEvent<void(const FSessionLeft&)> OnSessionLeft() override;`
- L289 _public prototype_ `virtual TOnlineEvent<void(const FSessionUpdated&)> OnSessionUpdated() override;`
- L290 _public prototype_ `virtual TOnlineEvent<void(const FSessionInviteReceived&)> OnSessionInviteReceived() override;`
- L291 _public prototype_ `virtual TOnlineEvent<void(const FUISessionJoinRequested&)> OnUISessionJoinRequested() override;`
- L295 _protected prototype_ `TOnlineResult<FGetMutableSessionByName> GetMutableSessionByName(FGetMutableSessionByName::Params&& Params) const;` — Auxiliary methods
- L296 _protected prototype_ `TOnlineResult<FGetMutableSessionById> GetMutableSessionById(FGetMutableSessionById::Params&& Params) const;`
- L298 _protected prototype_ `void AddSessionInvite(const TSharedRef<FSessionInviteCommon> SessionInvite, const TSharedRef<FSessionCommon> Session, const FAccountId& LocalAccountId);`
- L299 _protected prototype_ `void AddSearchResult(const TSharedRef<FSessionCommon> Session, const FAccountId& LocalAccountId);`
- L300 _protected prototype_ `void AddSessionWithReferences(const TSharedRef<FSessionCommon> Session, const FName& SessionName, const FAccountId& LocalAccountId, bool bIsPresenceSession);`
- L301 _protected prototype_ `void AddSessionReferences(const FOnlineSessionId SessionId, const FName& SessionName, const FAccountId& LocalAccountId, bool bIsPresenceSession);`
- L303 _protected prototype_ `void ClearSessionInvitesForSession(const FAccountId& LocalAccountId, const FOnlineSessionId SessionId);`
- L304 _protected prototype_ `void ClearSessionReferences(const FOnlineSessionId SessionId, const FName& SessionName, const FAccountId& LocalAccountId);`
- L306 _protected prototype_ `FSessionUpdate BuildSessionUpdate(const TSharedRef<FSessionCommon>& Session, const FSessionSettingsUpdate& UpdatedValues) const;`
- L310 _protected prototype_ `virtual TOnlineResult<FSetPresenceSession> SetPresenceSessionImpl(FSetPresenceSession::Params&& Params);`
- L311 _protected prototype_ `virtual TOnlineResult<FClearPresenceSession> ClearPresenceSessionImpl(FClearPresenceSession::Params&& Params);`
- L313 _protected prototype_ `virtual TFuture<TOnlineResult<FCreateSession>> CreateSessionImpl(const FCreateSession::Params& Params);`
- L314 _protected prototype_ `virtual TOptional<FOnlineError> CheckParams(const FCreateSession::Params& Params) const;`
- L315 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FCreateSession::Params& Params) const;`
- L317 _protected prototype_ `virtual TFuture<TOnlineResult<FUpdateSessionSettings>> UpdateSessionSettingsImpl(const FUpdateSessionSettings::Params& Params);`
- L318 _protected prototype_ `virtual TOptional<FOnlineError> CheckParams(const FUpdateSessionSettings::Params& Params) const;`
- L319 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FUpdateSessionSettings::Params& Params) const;`
- L321 _protected prototype_ `virtual TFuture<TOnlineResult<FLeaveSession>> LeaveSessionImpl(const FLeaveSession::Params& Params);`
- L322 _protected prototype_ `virtual TOptional<FOnlineError> CheckParams(const FLeaveSession::Params& Params) const;`
- L323 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FLeaveSession::Params& Params) const;`
- L325 _protected prototype_ `virtual TFuture<TOnlineResult<FFindSessions>> FindSessionsImpl(const FFindSessions::Params& Params);`
- L326 _protected prototype_ `virtual TOptional<FOnlineError> CheckParams(const FFindSessions::Params& Params) const;`
- L327 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FFindSessions::Params& Params) const;`
- L329 _protected prototype_ `virtual TFuture<TOnlineResult<FStartMatchmaking>> StartMatchmakingImpl(const FStartMatchmaking::Params& Params);`
- L330 _protected prototype_ `virtual TOptional<FOnlineError> CheckParams(const FStartMatchmaking::Params& Params) const;`
- L331 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FStartMatchmaking::Params& Params) const;`
- L333 _protected prototype_ `virtual TFuture<TOnlineResult<FJoinSession>> JoinSessionImpl(const FJoinSession::Params& Params);`
- L334 _protected prototype_ `virtual TOptional<FOnlineError> CheckParams(const FJoinSession::Params& Params) const;`
- L335 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FJoinSession::Params& Params) const;`
- L337 _protected prototype_ `virtual TFuture<TOnlineResult<FAddSessionMember>> AddSessionMemberImpl(const FAddSessionMember::Params& Params);`
- L338 _protected prototype_ `virtual TOptional<FOnlineError> CheckParams(const FAddSessionMember::Params& Params) const;`
- L339 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FAddSessionMember::Params& Params) const;`
- L340 _protected prototype_ `TOnlineResult<FAddSessionMember> AddSessionMemberInternal(const FAddSessionMember::Params& Params);`
- L342 _protected prototype_ `virtual TFuture<TOnlineResult<FRemoveSessionMember>> RemoveSessionMemberImpl(const FRemoveSessionMember::Params& Params);`
- L343 _protected prototype_ `virtual TOptional<FOnlineError> CheckParams(const FRemoveSessionMember::Params& Params) const;`
- L344 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FRemoveSessionMember::Params& Params) const;`
- L345 _protected prototype_ `TOnlineResult<FRemoveSessionMember> RemoveSessionMemberInternal(const FRemoveSessionMember::Params& Params);`
- L347 _protected prototype_ `virtual TFuture<TOnlineResult<FSendSessionInvite>> SendSessionInviteImpl(const FSendSessionInvite::Params& Params);`
- L348 _protected prototype_ `virtual TOptional<FOnlineError> CheckParams(const FSendSessionInvite::Params& Params) const;`
- L349 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FSendSessionInvite::Params& Params) const;`
- L351 _protected prototype_ `virtual TFuture<TOnlineResult<FRejectSessionInvite>> RejectSessionInviteImpl(const FRejectSessionInvite::Params& Params);`
- L352 _protected prototype_ `virtual TOptional<FOnlineError> CheckParams(const FRejectSessionInvite::Params& Params) const;`
- L353 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FRejectSessionInvite::Params& Params) const;`
- L357 _private prototype_ `template<typename MethodStruct> TOnlineAsyncOpHandle<MethodStruct> ExecuteAsyncSessionsMethod(typename MethodStruct::Params&& Params, TFuture<TOnlineResult<MethodStruct>>(FSessionsCommon::* ImplFunc)(const typename MethodStruct::Params& Params), bool bUseParallelQueue = false);`
- L359 _private prototype_ `void ClearSessionByName(const FName& SessionName);`
- L360 _private prototype_ `void ClearSessionById(const FOnlineSessionId& SessionId);`
- L372 _protected member_ `} SessionEvents;`
- L375 _protected member_ `TMap<FAccountId, TArray<FName>> NamedSessionUserMap;` — Map of named sessions a user is part of, indexed by user
- L378 _protected member_ `TMap<FName, FOnlineSessionId> LocalSessionsByName;` — Map of sessions that local users are part of, indexed by their local name
- L381 _protected member_ `TMap<FAccountId, FOnlineSessionId> PresenceSessionsUserMap;` — Map of sessions that local users have set as their presence session to appear in the platform UI. A user may not have set any session as their presence session.
- L384 _protected member_ `TMap<FAccountId, TMap<FSessionInviteId, TSharedRef<FSessionInviteCommon>>> SessionInvitesUserMap;` — Cache for received session invites, mapped per user
- L387 _protected member_ `TMap<FAccountId, TArray<FOnlineSessionId>> SearchResultsUserMap;` — Cache for the last set of session search results, mapped per user
- L390 _protected member_ `TMap<FAccountId, TPromise<TOnlineResult<FFindSessions>>> CurrentSessionSearchPromisesUserMap;` — Handle for an ongoing session search operation, mapped per user
- L393 _protected member_ `TMap<FOnlineSessionId, TSharedRef<FSessionCommon>> AllSessionsById;` — Set of every distinct FSession found, indexed by Id

#### struct `UE::Online::FSessionsCommon::FSessionEvents`  
`struct FSessionEvents`  
_L364-372_
- L366 _public member_ `TOnlineEventCallable<void(const FSessionCreated&)> OnSessionCreated;`
- L367 _public member_ `TOnlineEventCallable<void(const FSessionJoined&)> OnSessionJoined;`
- L368 _public member_ `TOnlineEventCallable<void(const FSessionLeft&)> OnSessionLeft;`
- L369 _public member_ `TOnlineEventCallable<void(const FSessionUpdated&)> OnSessionUpdated;`
- L370 _public member_ `TOnlineEventCallable<void(const FSessionInviteReceived&)> OnSessionInviteReceived;`
- L371 _public member_ `TOnlineEventCallable<void(const FUISessionJoinRequested&)> OnUISessionJoinRequested;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L15 _variable_ `static FName CONNECT_STRING_TAG = TEXT("CON` (scope `UE::Online`)
- L396 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/SocialCommon.h` (Public)


#### class `UE::Online::FSocialCommon`  
`class FSocialCommon : public TOnlineComponent<ISocial>`  
_L14-38_
- inherits: `TOnlineComponent<ISocial>`
- L17 _public typedef_ `using Super = ISocial;`
- L19 _public prototype_ `FSocialCommon(FOnlineServicesCommon& InServices);`
- L22 _public prototype_ `virtual void RegisterCommands() override;` — TOnlineComponent
- L25 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryFriends> QueryFriends(FQueryFriends::Params&& Params) override;` — ISocial
- L26 _public prototype_ `virtual TOnlineResult<FGetFriends> GetFriends(FGetFriends::Params&& Params) override;`
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FSendFriendInvite> SendFriendInvite(FSendFriendInvite::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FAcceptFriendInvite> AcceptFriendInvite(FAcceptFriendInvite::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FRejectFriendInvite> RejectFriendInvite(FRejectFriendInvite::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineEvent<void(const FRelationshipUpdated&)> OnRelationshipUpdated() override;`
- L31 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryBlockedUsers> QueryBlockedUsers(FQueryBlockedUsers::Params&& Params) override;`
- L32 _public prototype_ `virtual TOnlineResult<FGetBlockedUsers> GetBlockedUsers(FGetBlockedUsers::Params&& Params) override;`
- L33 _public prototype_ `virtual TOnlineAsyncOpHandle<FBlockUser> BlockUser(FBlockUser::Params&& Params) override;`
- L36 _protected prototype_ `void BroadcastRelationshipUpdated(FAccountId LocalAccountId, FAccountId RemoteAccountId, ERelationship OldRelationship, ERelationship NewRelationship);`
- L37 _protected member_ `TOnlineEventCallable<void(const FRelationshipUpdated&)> OnRelationshipUpdatedEvent;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/StatsCommon.h` (Public)


#### enum `UE::Online::EStatModifyMethod`  
`enum class EStatModifyMethod : uint8`  
_L12-22_
- L15 _public enumerator_ `Sum` — Add the new value to the previous value
- L17 _public enumerator_ `Set` — Overwrite previous value with the new value
- L19 _public enumerator_ `Largest` — Only replace previous value if new value is larger
- L21 _public enumerator_ `Smallest` — Only replace previous value if new value is smaller

#### struct `UE::Online::FStatDefinition`  
`struct FStatDefinition`  
_L27-37_
- L30 _public member_ `FString Name;` — The name of the stat
- L32 _public member_ `int32 Id = 0;` — Corresponding stat id on the platform if needed
- L34 _public member_ `EStatModifyMethod ModifyMethod = EStatModifyMethod::Set;` — How the stat will be modified
- L36 _public member_ `FStatValue DefaultValue = FStatValue(static_cast<int64>(0));` — Store the default type and value

#### struct `UE::Online::FStatsCommonConfig`  
`struct FStatsCommonConfig`  
_L39-42_
- L41 _public member_ `TArray<FStatDefinition> StatDefinitions;`

#### struct `UE::Online::FFindUserStatsByAccountId`  
`struct FFindUserStatsByAccountId`  
_L59-72_
- L61 _public function_ `FFindUserStatsByAccountId(const FAccountId& InAccountId) : AccountId(InAccountId)`
- L66 _public function_ `bool operator()(const FUserStats& UserStats) const`
- L71 _public member_ `FAccountId AccountId;`

#### class `UE::Online::FStatsCommon`  
`class FStatsCommon : public TOnlineComponent<IStats>`  
_L74-114_
- inherits: `TOnlineComponent<IStats>`
- L77 _public typedef_ `using Super = IStats;`
- L79 _public prototype_ `FStatsCommon(FOnlineServicesCommon& InServices);`
- L82 _public prototype_ `virtual void UpdateConfig() override;` — TOnlineComponent
- L83 _public prototype_ `virtual void RegisterCommands() override;`
- L86 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdateStats> UpdateStats(FUpdateStats::Params&& Params) override;` — IStats
- L87 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryStats> QueryStats(FQueryStats::Params&& Params) override;`
- L88 _public prototype_ `virtual TOnlineAsyncOpHandle<FBatchQueryStats> BatchQueryStats(FBatchQueryStats::Params&& Params) override;`
- L95 _public prototype_ `virtual TOnlineAsyncOpHandle<FTriggerEvent> TriggerEvent(FTriggerEvent::Params&& Params) override;` — Example implementation that uses the event to stats mapping rules In this version we assume that FTriggerEvent::Params is a mapping of property names to values, Assumes that FTriggerEvent::Params is defined as TMap<FString, FSchemaVariant> and that each stat referenced in the event has a defined modify rule: Set, Sum, Largest, Smallest After applying the stat changes to the base class cache, we're also broadcasting an update through OnStatsUpdatedEvent.Broadcast().
- L98 _public prototype_ `virtual TOnlineAsyncOpHandle<FResetStats> ResetStats(FResetStats::Params&& Params) override;`
- L100 _public prototype_ `virtual TOnlineResult<FGetCachedStats> GetCachedStats(FGetCachedStats::Params&& Params) const override;`
- L102 _public prototype_ `virtual TOnlineEvent<void(const FStatsUpdated&)> OnStatsUpdated() override;`
- L103 _public prototype_ `const FStatDefinition* GetStatDefinition(const FString& StatName) const;`
- L106 _protected prototype_ `virtual TOnlineAsyncOpRef<FUpdateStats> UpdateStats_Implementation(FUpdateStats::Params&& Params);`
- L107 _protected prototype_ `virtual void ReadStatsFromCache(const FUserStats* ExistingUserStats, const TArray<FString>& StatNames, TMap<FString, FStatValue>& OutStats) const;`
- L108 _protected prototype_ `virtual void CacheUserStats(const FUserStats& UserStats);`
- L110 _protected member_ `TMap<FString, FStatDefinition> StatDefinitions;`
- L111 _protected member_ `TOnlineEventCallable<void(const FStatsUpdated& StatsUpdated)> OnStatsUpdatedEvent;`
- L113 _protected member_ `TArray<FUserStats> CachedUsersStats;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L24 _prototype_ `const TCHAR* LexToString(EStatModifyMethod Value);` (scope `UE::Online`)
- L25 _prototype_ `void LexFromString(EStatModifyMethod& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L44 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/TitleFileCommon.h` (Public)


#### class `UE::Online::FTitleFileCommon`  
`class FTitleFileCommon : public TOnlineComponent<ITitleFile>`  
_L14-28_
- inherits: `TOnlineComponent<ITitleFile>`
- L17 _public typedef_ `using Super = ITitleFile;`
- L19 _public prototype_ `FTitleFileCommon(FOnlineServicesCommon& InServices);`
- L22 _public prototype_ `virtual void RegisterCommands() override;` — TOnlineComponent
- L25 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileEnumerateFiles> EnumerateFiles(FTitleFileEnumerateFiles::Params&& Params) override;` — ITitleFile
- L26 _public prototype_ `virtual TOnlineResult<FTitleFileGetEnumeratedFiles> GetEnumeratedFiles(FTitleFileGetEnumeratedFiles::Params&& Params) override;`
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileReadFile> ReadFile(FTitleFileReadFile::Params&& Params) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/UserFileCommon.h` (Public)


#### class `UE::Online::FUserFileCommon`  
`class FUserFileCommon : public TOnlineComponent<IUserFile>`  
_L14-31_
- inherits: `TOnlineComponent<IUserFile>`
- L17 _public typedef_ `using Super = IUserFile;`
- L19 _public prototype_ `FUserFileCommon(FOnlineServicesCommon& InServices);`
- L22 _public prototype_ `virtual void RegisterCommands() override;` — TOnlineComponent
- L25 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileEnumerateFiles> EnumerateFiles(FUserFileEnumerateFiles::Params&& Params) override;` — IUserFile
- L26 _public prototype_ `virtual TOnlineResult<FUserFileGetEnumeratedFiles> GetEnumeratedFiles(FUserFileGetEnumeratedFiles::Params&& Params) override;`
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileReadFile> ReadFile(FUserFileReadFile::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileWriteFile> WriteFile(FUserFileWriteFile::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileCopyFile> CopyFile(FUserFileCopyFile::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileDeleteFile> DeleteFile(FUserFileDeleteFile::Params&& Params) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommon/Public/Online/UserInfoCommon.h` (Public)


#### class `UE::Online::FUserInfoCommon`  
`class FUserInfoCommon : public TOnlineComponent<IUserInfo>`  
_L14-30_
- inherits: `TOnlineComponent<IUserInfo>`
- L17 _public typedef_ `using Super = IUserInfo;`
- L19 _public prototype_ `FUserInfoCommon(FOnlineServicesCommon& InServices);`
- L22 _public prototype_ `virtual void RegisterCommands() override;` — TOnlineComponent
- L25 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryUserInfo> QueryUserInfo(FQueryUserInfo::Params&& Params) override;` — IUserInfo
- L26 _public prototype_ `virtual TOnlineResult<FGetUserInfo> GetUserInfo(FGetUserInfo::Params&& Params) override;`
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryUserAvatar> QueryUserAvatar(FQueryUserAvatar::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineResult<FGetUserAvatar> GetUserAvatar(FGetUserAvatar::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FShowUserProfile> ShowUserProfile(FShowUserProfile::Params&& Params) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESCOMMON_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
