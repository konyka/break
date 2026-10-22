# Plugins / OnlineServicesEOS

- module root: `Plugins/Online/OnlineServicesEOS/Source`
- headers: 13; symbols: 199
- symbol kinds: class=13, externvar=1, function=1, macro=1, member=30, namespace=28, prototype=112, struct=2, typedef=11
- PrivateDependencyModuleNames: CoreOnline, CoreUObject, EOSSDK, EOSShared, OnlineServicesEpicCommon
- PublicDependencyModuleNames: Core, OnlineServicesCommon, OnlineServicesEOSGS, OnlineServicesInterface

### `Plugins/Online/OnlineServicesEOS/Source/Private/Online/OnlineIdEOS.h` (Private)


#### class `UE::Online::FOnlineAccountIdDataEOS`  
`class FOnlineAccountIdDataEOS`  
_L16-21_
- L19 _public member_ `EOS_EpicAccountId EpicAccountId = nullptr;`
- L20 _public member_ `EOS_ProductUserId ProductUserId = nullptr;`

#### class `UE::Online::FOnlineAccountIdRegistryEOS`  
`class FOnlineAccountIdRegistryEOS : public IOnlineAccountIdRegistryEOSGS`  
_L26-70_
- inherits: `IOnlineAccountIdRegistryEOSGS`
- desc: Account id registry specifically for EOS id's which are an EOS_EpicAccountId/EOS_ProductUserId pair.
- L29 _public prototype_ `virtual ~FOnlineAccountIdRegistryEOS() = default;`
- L32 _public prototype_ `virtual FString ToString(const FAccountId& AccountId) const override;`
- L33 _public prototype_ `virtual FString ToLogString(const FAccountId& AccountId) const override;`
- L34 _public prototype_ `virtual TArray<uint8> ToReplicationData(const FAccountId& AccountId) const override;`
- L35 _public prototype_ `virtual FAccountId FromReplicationData(const TArray<uint8>& ReplicationString) override;`
- L36 _public prototype_ `virtual FAccountId FromStringData(const FString& StringData) override;`
- L40 _public prototype_ `virtual FAccountId FindOrAddAccountId(const EOS_ProductUserId ProductUserId) override;`
- L41 _public prototype_ `virtual FAccountId FindAccountId(const EOS_ProductUserId ProductUserId) const override;`
- L42 _public prototype_ `virtual EOS_ProductUserId GetProductUserId(const FAccountId& AccountId) const override;`
- L45 _public prototype_ `FAccountId FindAccountId(const EOS_EpicAccountId EpicAccountId) const;`
- L46 _public prototype_ `FAccountId FindOrAddAccountId(const EOS_EpicAccountId EpicAccountId, const EOS_ProductUserId ProductUserId);`
- L49 _public prototype_ `FOnlineAccountIdDataEOS GetAccountIdData(const FAccountId& AccountId) const;` — Return copies as it is not thread safe to return pointers/references to array elements, in case the array is grown+relocated on another thread.
- L51 _public prototype_ `static FOnlineAccountIdRegistryEOS& Get();`
- L54 _public function_ `template<typename IdType> static inline bool ValidateOnlineId(const TOnlineId<IdType> OnlineId)`
- L64 _private member_ `mutable FTransactionallySafeRWLock Lock;`
- L66 _private member_ `TArray<FOnlineAccountIdDataEOS> AccountIdData;` — Actual container for the info, indexed by the handle
- L68 _private member_ `TMap<EOS_EpicAccountId, FAccountId> EpicAccountIdToAccountId;` — Map of EOS_EpicAccountId to the associated handle.
- L69 _private member_ `TMap<EOS_ProductUserId, FAccountId> ProductUserIdToAccountId;` — Map of EOS_ProductUserId to the associated handle.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/AccountIdEOS.h` (Public)


#### class `UE::Online::IOnlineAccountIdRegistryEpicAccount`  
`class IOnlineAccountIdRegistryEpicAccount : public IOnlineAccountIdRegistry`  
_L12-17_
- inherits: `IOnlineAccountIdRegistry`
- L15 _public prototype_ `virtual FAccountId GetAccountId(EOS_EpicAccountId EpicAccountId) = 0;`
- L16 _public prototype_ `virtual EOS_EpicAccountId GetEpicAccountId(const FAccountId& AccountId) const = 0;`

#### Free symbols / members of external scopes

- L7 _typedef_ `typedef struct EOS_EpicAccountIdDetails* EOS_EpicAccountId;`
- L8 _typedef_ `typedef struct EOS_ProductUserIdDetails* EOS_ProductUserId;`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L19 _prototype_ `EOS_EpicAccountId GetEpicAccountId(const FAccountId& AccountId);` (scope `UE::Online`)
- L20 _prototype_ `EOS_EpicAccountId GetEpicAccountIdChecked(const FAccountId& AccountId);` (scope `UE::Online`)
- L23 _prototype_ `FAccountId FindAccountId(const EOS_EpicAccountId EpicAccountId);` (scope `UE::Online`) — `UE_DEPRECATED(5.6, "This method is deprecated, please use the new version taking a EOnlineServices parameter")`
- L24 _prototype_ `FAccountId FindAccountId(EOnlineServices Services, const EOS_EpicAccountId EpicAccountId);` (scope `UE::Online`)
- L27 _prototype_ `FAccountId FindAccountIdChecked(const EOS_EpicAccountId EpicAccountId);` (scope `UE::Online`) — `UE_DEPRECATED(5.6, "This method is deprecated, please use the new version taking a EOnlineServices parameter")`
- L28 _prototype_ `FAccountId FindAccountIdChecked(EOnlineServices Services, const EOS_EpicAccountId EpicAccountId);` (scope `UE::Online`)
- L30 _prototype_ `FAccountId CreateAccountId(const EOS_EpicAccountId EpicAccountId, const EOS_ProductUserId ProductUserId);` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/AuthEOS.h` (Public)


#### class `UE::Online::FAuthEOS`  
`class FAuthEOS : public FAuthEOSGS`  
_L21-54_
- inherits: `FAuthEOSGS`
- L24 _public typedef_ `using Super = FAuthEOSGS;`
- L26 _public prototype_ `FAuthEOS(FOnlineServicesCommon& InOwningSubsystem);`
- L27 _public prototype_ `virtual ~FAuthEOS() = default;`
- L30 _public prototype_ `virtual void Initialize() override;`
- L34 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLogin> Login(FAuthLogin::Params&& Params) override;`
- L35 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLinkAccount> LinkAccount(FAuthLinkAccount::Params&& Params) override;`
- L36 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryExternalServerAuthTicket> QueryExternalServerAuthTicket(FAuthQueryExternalServerAuthTicket::Params&& Params) override;`
- L37 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryExternalAuthToken> QueryExternalAuthToken(FAuthQueryExternalAuthToken::Params&& Params) override;`
- L38 _public prototype_ `virtual TOnlineResult<FAuthGetLinkAccountContinuationId> GetLinkAccountContinuationId(FAuthGetLinkAccountContinuationId::Params&& Params) const;`
- L41 _public prototype_ `TFuture<TArray<FAccountId>> ResolveAccountIds(const FAccountId& LocalAccountId, const TArray<EOS_EpicAccountId>& EpicAccountIds);`
- L42 _public prototype_ `TFuture<TArray<FAccountId>> ResolveAccountIds(const FAccountId& LocalAccountId, const TArray<EOS_ProductUserId>& ProductUserIds);`
- L45 _protected prototype_ `void ProcessSuccessfulLogin(TOnlineAsyncOp<FAuthLogin>& InAsyncOp);`
- L46 _protected prototype_ `void OnEASLoginStatusChanged(FAccountId LocalAccountId, ELoginStatus PreviousStatus, ELoginStatus CurrentStatus);`
- L48 _protected prototype_ `FAccountId FindAccountId(const EOS_ProductUserId ProductUserId);`
- L49 _protected prototype_ `FAccountId FindAccountId(const EOS_EpicAccountId EpicAccountId);`
- L51 _protected prototype_ `static FAccountId CreateAccountId(const EOS_EpicAccountId EpicAccountId, const EOS_ProductUserId ProductUserId);`
- L53 _protected member_ `EOS_HUserInfo UserInfoHandle = nullptr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESERVICESEOS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L15 _namespace_ `namespace ELinkAccountTag` (scope `UE::Online`)
- L18 _externvar_ `extern const FName InternalAccount;` (scope `UE::Online::ELinkAccountTag`) — An internal account is an account which has nothing external allowing the user to login on the epicgames.com website.
- L56 _typedef_ `using FAuthEOSPtr = TSharedPtr<FAuthEOS>;` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/CommerceEOS.h` (Public)


#### class `UE::Online::FCommerceEOS`  
`class FCommerceEOS : public FCommerceCommon`  
_L16-46_
- inherits: `FCommerceCommon`
- L19 _public typedef_ `using Super = FCommerceCommon;`
- L23 _public prototype_ `virtual void PostInitialize() override;` — IOnlineComponent
- L24 _public prototype_ `virtual void PreShutdown() override;`
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryOffers> QueryOffers(FCommerceQueryOffers::Params&& Params) override;` — ICommerce
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryOffersById> QueryOffersById(FCommerceQueryOffersById::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineResult<FCommerceGetOffers> GetOffers(FCommerceGetOffers::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineResult<FCommerceGetOffersById> GetOffersById(FCommerceGetOffersById::Params&& Params) override;`
- L31 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceShowStoreUI> ShowStoreUI(FCommerceShowStoreUI::Params&& Params) override;`
- L32 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceCheckout> Checkout(FCommerceCheckout::Params&& Params) override;`
- L33 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryTransactionEntitlements> QueryTransactionEntitlements(FCommerceQueryTransactionEntitlements::Params&& Params) override;`
- L34 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryEntitlements> QueryEntitlements(FCommerceQueryEntitlements::Params&& Params) override;`
- L35 _public prototype_ `virtual TOnlineResult<FCommerceGetEntitlements> GetEntitlements(FCommerceGetEntitlements::Params&& Params) override;`
- L36 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceRedeemEntitlement> RedeemEntitlement(FCommerceRedeemEntitlement::Params&& Params) override;`
- L37 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceRetrieveS2SToken> RetrieveS2SToken(FCommerceRetrieveS2SToken::Params&& Params) override;`
- L40 _private prototype_ `void EOSOfferToOssOffer(FOffer& InOffer, EOS_Ecom_CatalogOffer* EosOffer);`
- L41 _private prototype_ `void EOSEntitlementToOssEntitlement(FEntitlement& OutEntitlement, EOS_Ecom_Entitlement* EosEntitlement);`
- L43 _private member_ `EOS_HEcom EcomHandle;`
- L44 _private member_ `TMap<FAccountId, TArray<FEntitlement>> CachedEntitlements;`
- L45 _private member_ `TMap<FAccountId, TArray<FOffer>> CachedOffers;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/EpicAccountIdResolverEOS.h` (Public)


#### class `UE::Online::FEpicAccountIdResolverEOS`  
`class FEpicAccountIdResolverEOS : public TOnlineComponent<IEpicAccountIdResolver>`  
_L10-19_
- inherits: `TOnlineComponent<IEpicAccountIdResolver>`
- L13 _public prototype_ `FEpicAccountIdResolverEOS(class FOnlineServicesEOS& InServices);`
- L16 _public prototype_ `virtual TFuture<FAccountId> ResolveAccountId(const FAccountId LocalAccountId, const EOS_EpicAccountId EpicAccountId) override;`
- L17 _public prototype_ `virtual TFuture<TArray<FAccountId>> ResolveAccountIds(const FAccountId LocalAccountId, const TArray<EOS_EpicAccountId>& EpicAccountIds) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/EpicProductUserIdResolverEOS.h` (Public)


#### class `UE::Online::FEpicProductUserIdResolverEOS`  
`class FEpicProductUserIdResolverEOS : public TOnlineComponent<IEpicProductUserIdResolver>`  
_L10-19_
- inherits: `TOnlineComponent<IEpicProductUserIdResolver>`
- L13 _public prototype_ `FEpicProductUserIdResolverEOS(class FOnlineServicesEOS& InServices);`
- L16 _public prototype_ `virtual TFuture<FAccountId> ResolveAccountId(const FAccountId LocalAccountId, const EOS_ProductUserId ProductUserId) override;`
- L17 _public prototype_ `virtual TFuture<TArray<FAccountId>> ResolveAccountIds(const FAccountId LocalAccountId, const TArray<EOS_ProductUserId>& ProductUserIds) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/ExternalUIEOS.h` (Public)


#### struct `UE::Online::FExternalUIEOSConfig`  
`struct FExternalUIEOSConfig`  
_L14-18_
- L17 _public member_ `bool bShowLoginUIEnabled = true;` — Is ShowLoginUI enabled?

#### class `UE::Online::FExternalUIEOS`  
`class FExternalUIEOS : public FExternalUIEOSGS`  
_L22-41_
- inherits: `FExternalUIEOSGS`
- L25 _public typedef_ `using Super = FExternalUIEOSGS;`
- L27 _public prototype_ `FExternalUIEOS(FOnlineServicesEpicCommon& InOwningSubsystem);`
- L28 _public prototype_ `virtual ~FExternalUIEOS();`
- L30 _public prototype_ `virtual void Initialize() override;`
- L31 _public prototype_ `virtual void UpdateConfig() override;`
- L33 _public prototype_ `virtual TOnlineAsyncOpHandle<FExternalUIShowLoginUI> ShowLoginUI(FExternalUIShowLoginUI::Params&& Params) override;`
- L34 _public prototype_ `virtual TOnlineAsyncOpHandle<FExternalUIShowFriendsUI> ShowFriendsUI(FExternalUIShowFriendsUI::Params&& Params) override;`
- L38 _protected member_ `EOS_HUI UIHandle;` — Handle to EOS UI
- L40 _protected member_ `FExternalUIEOSConfig Config;` — Config

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L43 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/OnlineServicesEOS.h` (Public)


#### class `UE::Online::FOnlineServicesEOS`  
`class FOnlineServicesEOS : public FOnlineServicesEOSGS`  
_L20-29_
- inherits: `FOnlineServicesEOSGS`
- L23 _public typedef_ `using Super = FOnlineServicesEOSGS;`
- L25 _public prototype_ `FOnlineServicesEOS(FName InInstanceName, FName InInstanceConfigName);`
- L26 _public prototype_ `virtual ~FOnlineServicesEOS() = default;`
- L28 _public prototype_ `virtual void RegisterComponents() override;`

#### Free symbols / members of external scopes

- L16 _typedef_ `using IEOSPlatformHandlePtr = TSharedPtr<class IEOSPlatformHandle>;`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/OnlineServicesEOSModule.h` (Public)


#### class `UE::Online::FOnlineServicesEOSModule`  
`class FOnlineServicesEOSModule : public IModuleInterface`  
_L9-19_
- inherits: `IModuleInterface`
- L12 _public prototype_ `static int GetRegistryPriority();`
- L16 _private prototype_ `virtual void StartupModule() override;`
- L17 _private prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/OnlineServicesEOSTypes.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/PresenceEOS.h` (Public)


#### class `UE::Online::FPresenceEOS`  
`class FPresenceEOS : public FPresenceCommon`  
_L19-109_
- inherits: `FPresenceCommon`
- L22 _public typedef_ `using Super = FPresenceCommon;`
- L24 _public prototype_ `FPresenceEOS(FOnlineServicesEpicCommon& InServices);`
- L25 _public prototype_ `virtual ~FPresenceEOS();`
- L27 _public prototype_ `virtual void Initialize() override;`
- L28 _public prototype_ `virtual void PreShutdown() override;`
- L29 _public prototype_ `virtual void UpdateConfig() override;`
- L30 _public prototype_ `virtual void RegisterCommands() override;`
- L32 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryPresence> QueryPresence(FQueryPresence::Params&& Params) override;`
- L33 _public prototype_ `virtual TOnlineResult<FGetCachedPresence> GetCachedPresence(FGetCachedPresence::Params&& Params) override;`
- L34 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdatePresence> UpdatePresence(FUpdatePresence::Params&& Params) override;`
- L35 _public prototype_ `virtual TOnlineAsyncOpHandle<FPartialUpdatePresence> PartialUpdatePresence(FPartialUpdatePresence::Params&& Params) override;`
- L39 _protected prototype_ `TSharedRef<FUserPresence> FindOrCreatePresence(FAccountId LocalAccountId, FAccountId PresenceAccountId);` — Get a user's presence, creating entries if missing
- L41 _protected prototype_ `void UpdateUserPresence(FAccountId LocalAccountId, FAccountId PresenceAccountId);` — Update a user's presence from EOS's current value
- L43 _protected prototype_ `void HandleAuthLoginStatusChanged(const FAuthLoginStatusChanged& EventParameters);` — Performs queued presence updates after a user's login completes
- L45 _protected prototype_ `void HandlePresenceChanged(const EOS_Presence_PresenceChangedCallbackInfo* Data);`
- L47 _protected prototype_ `FAccountId FindAccountId(const EOS_EpicAccountId EpicAccountId);`
- L50 _protected prototype_ `virtual void ModifyPresenceUpdate(TSharedRef<FUserPresence>& Presence);` — Allow derived classes to modify the content of presence updates
- L52 _protected prototype_ `virtual void ModifyPartialPresenceUpdate(FPartialUpdatePresence::Params::FMutations& Mutations);` — Allow derived classes to modify the content of partial presence updates
- L54 _protected prototype_ `static EOnlinePlatformType IntegratedPlatform_To_OnlinePlatformType(const FString& IntegratedPlatformStr);`
- L55 _protected prototype_ `virtual bool ReadOnlinePlatformType(const EOS_Presence_Info* PresenceInfo, EOnlinePlatformType& OutOnlinePlatformType);`
- L57 _protected member_ `EOS_HPresence PresenceHandle = nullptr;`
- L60 _protected member_ `FOnlineEventDelegateHandle LoginStatusChangedHandle;` — Login status changed event handle
- L62 _protected member_ `TMap<EOS_EpicAccountId, TArray<EOS_EpicAccountId>> PendingPresenceUpdates;`
- L63 _protected member_ `TMap<FAccountId, TMap<FAccountId, TSharedRef<FUserPresence>>> PresenceLists;`
- L65 _protected member_ `FEOSEventRegistrationPtr OnPresenceChanged;`
- L67 _protected member_ `double AsyncOpEnqueueDelay = 0.0;`
- L74 _protected prototype_ `void ApplyMutationsToCache(FAccountId LocalAccountId, const FPartialUpdatePresence::Params::FMutations& Mutations);` — Apply partial presence mutations to the local cache and broadcast OnPresenceUpdatedEvent if there was a change.
- L79 _protected prototype_ `void ApplyFullPresenceToCache(FAccountId LocalAccountId, const FUserPresence& NewPresence);` — Apply a full presence replacement to the local cache and broadcast OnPresenceUpdatedEvent if there was a change.
- L82 _protected prototype_ `FPartialUpdatePresence::Params::FMutations BuildPresenceDelta(const EOS_Presence_Info* EOSPresenceInfo, const FUserPresence& DesiredPresence);` — Build a FMutations representing the delta between the EOS SDK's presence state and a desired presence.
- L85 _protected prototype_ `void SchedulePresenceRetry(FAccountId LocalAccountId);` — Mark a user's presence as needing a retry push to the EOS backend.
- L88 _protected prototype_ `void StartPresenceRetry();` — Execute pending presence retries by pushing the current cache state to EOS.
- L91 _protected prototype_ `void CancelPresenceRetry(FAccountId LocalAccountId);` — Cancel the next scheduled retry for a user without resetting the retry counter.
- L94 _protected prototype_ `void ClearPresenceRetry(FAccountId LocalAccountId);` — Fully remove pending retry state for a user. Called on success, max retries exceeded, or logout.
- L105 _protected member_ `TMap<FAccountId, FPendingPresenceRetry> PendingRetries;`
- L106 _protected member_ `FTSTicker::FDelegateHandle RetryTickerHandle;`
- L107 _protected member_ `double PresenceRetryDelaySec = 5.0;`
- L108 _protected member_ `int32 MaxPresenceRetries = 3;`

#### struct `UE::Online::FPresenceEOS::FPendingPresenceRetry`  
`struct FPendingPresenceRetry`  
_L97-103_
- desc: Pending retry state for a user whose presence failed to push to EOS.
- L99 _public member_ `int32 RetryCount = 0;`
- L102 _public member_ `bool bPendingRetry = true;` — Whether this entry should fire on the next ticker tick. Set to false when a presence update method is called; RetryCount is preserved so any later failure in the same operation continues counting.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/SocialEOS.h` (Public)


#### class `UE::Online::FSocialEOS`  
`class FSocialEOS : public FSocialCommon`  
_L18-45_
- inherits: `FSocialCommon`
- L21 _public typedef_ `using Super = FSocialCommon;`
- L23 _public prototype_ `FSocialEOS(FOnlineServicesEpicCommon& InServices);`
- L25 _public prototype_ `virtual void Initialize() override;`
- L26 _public prototype_ `virtual void PreShutdown() override;`
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryFriends> QueryFriends(FQueryFriends::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineResult<FGetFriends> GetFriends(FGetFriends::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FSendFriendInvite> SendFriendInvite(FSendFriendInvite::Params&& Params) override;`
- L31 _public prototype_ `virtual TOnlineAsyncOpHandle<FAcceptFriendInvite> AcceptFriendInvite(FAcceptFriendInvite::Params&& Params) override;`
- L32 _public prototype_ `virtual TOnlineAsyncOpHandle<FRejectFriendInvite> RejectFriendInvite(FRejectFriendInvite::Params&& Params) override;`
- L33 _public prototype_ `virtual TOnlineAsyncOpHandle<FBlockUser> BlockUser(FBlockUser::Params&& Params) override;`
- L36 _protected prototype_ `void HandleFriendsUpdate(const EOS_Friends_OnFriendsUpdateInfo* Data);`
- L38 _protected prototype_ `FAccountId FindAccountId(const EOS_EpicAccountId EpicAccountId);`
- L40 _protected member_ `TMap<FAccountId, TMap<FAccountId, TSharedRef<FFriend>>> FriendsLists;`
- L41 _protected member_ `EOS_HFriends FriendsHandle = nullptr;`
- L42 _protected member_ `EOS_HUI UIHandle = nullptr;`
- L44 _protected member_ `FEOSEventRegistrationPtr OnFriendsUpdate;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOS/Source/Public/Online/UserInfoEOS.h` (Public)


#### class `UE::Online::FUserInfoEOS`  
`class FUserInfoEOS : public FUserInfoCommon`  
_L16-33_
- inherits: `FUserInfoCommon`
- L19 _public typedef_ `using Super = FUserInfoCommon;`
- L21 _public prototype_ `FUserInfoEOS(FOnlineServicesEpicCommon& InServices);`
- L22 _public prototype_ `virtual ~FUserInfoEOS() = default;`
- L25 _public prototype_ `virtual void Initialize() override;` — IOnlineComponent
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryUserInfo> QueryUserInfo(FQueryUserInfo::Params&& Params) override;` — IUserInfo
- L29 _public prototype_ `virtual TOnlineResult<FGetUserInfo> GetUserInfo(FGetUserInfo::Params&& Params) override;`
- L32 _protected member_ `EOS_HUserInfo UserInfoHandle = nullptr;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
