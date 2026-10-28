# Plugins / OnlineServicesXbl

- module root: `Plugins/Online/Microsoft/OnlineServicesXbl/Source`
- headers: 15; symbols: 303
- symbol kinds: class=20, enum=3, enumerator=10, function=5, macro=2, member=68, namespace=33, prototype=134, struct=9, typedef=18, variable=1

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Private/Online/EventsXbl.h` (Private)


#### class `UE::Online::FEventsXbl`  
`class FEventsXbl : public TSharedFromThis<FEventsXbl, ESPMode::ThreadSafe>`  
_L29-47_
- inherits: `TSharedFromThis<FEventsXbl,ESPMode::ThreadSafe>`
- desc: class FEventsXbl : public IOnlineEvents
- L32 _public function_ `FEventsXbl(FOnlineServicesXbl* InService)`
- L34 _public prototype_ `virtual ~FEventsXbl() = default;`
- L44 _public prototype_ `virtual bool TriggerEvent(const FAccountId& PlayerId, const TCHAR* EventName, const FOnlineEventParams& EventParams);` — Calls an event @param PlayerId	- Id of the player to call the event on @param Name		- Name of requested event @param Parms		- Parameters that will be passed directly to the event
- L46 _private member_ `FOnlineServicesXbl* Service;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Online` (scope `UE`)
- L22 _typedef_ `typedef TMap<FString, FSchemaVariant> FOnlineEventParams;` (scope `UE::Online`)
- L49 _typedef_ `typedef TSharedPtr<FEventsXbl, ESPMode::ThreadSafe> FEventsXblPtr;` (scope `UE::Online`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/AchievementsXbl.h` (Public)


#### class `FAchievementsConfig`  
`class FAchievementsConfig : public FJsonSerializable`  
_L12-22_
- inherits: `FJsonSerializable`
- L15 _public member_ `FString AchievementEventName;`
- L16 _public member_ `FJsonSerializableKeyValueMapInt AchievementMap;`

#### enum `UE::Online::EXblAchievementMode`  
`enum class EXblAchievementMode : uint16`  
_L26-34_
- L29 _public enumerator_ `Mode2013 = 2013` — 2013 achievements are driven via events
- L31 _public enumerator_ `Mode2017 = 2017` — 2017 achievements are title-managed
- L33 _public enumerator_ `Default = Mode2013` — Default mode to use if not specified

#### struct `UE::Online::FAchievementsXblConfig`  
`struct FAchievementsXblConfig`  
_L36-39_
- L38 _public member_ `EXblAchievementMode AchivementMode = EXblAchievementMode::Default;`

#### class `UE::Online::FAchievementsXbl`  
`class FAchievementsXbl : public FAchievementsCommon`  
_L49-83_
- inherits: `FAchievementsCommon`
- L52 _public typedef_ `using Super = FAchievementsCommon;`
- L56 _public prototype_ `virtual void Initialize() override;`
- L57 _public prototype_ `virtual void PreShutdown() override;`
- L60 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementDefinitions> QueryAchievementDefinitions(FQueryAchievementDefinitions::Params&& Params) override;` — IAchievements
- L61 _public prototype_ `virtual TOnlineResult<FGetAchievementIds> GetAchievementIds(FGetAchievementIds::Params&& Params) override;`
- L62 _public prototype_ `virtual TOnlineResult<FGetAchievementDefinition> GetAchievementDefinition(FGetAchievementDefinition::Params&& Params) override;`
- L63 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementStates> QueryAchievementStates(FQueryAchievementStates::Params&& Params) override;`
- L64 _public prototype_ `virtual TOnlineResult<FGetAchievementState> GetAchievementState(FGetAchievementState::Params&& Params) const override;`
- L65 _public prototype_ `virtual TOnlineAsyncOpHandle<FUnlockAchievements> UnlockAchievements(FUnlockAchievements::Params&& Params) override;`
- L68 _public prototype_ `void AchievementUnlockNotificationHandler(const FAchievementUpdate& Update);`
- L72 _protected prototype_ `const FString& GetAchievementNameFromId(int32 AchievementId);`
- L73 _protected prototype_ `int32 GetAchievementIdFromName(const FString& AchievementName);`
- L74 _protected prototype_ `const FString& GetAchievementEventName();`
- L75 _protected prototype_ `bool LoadAndInitFromJsonConfig(const TCHAR* JsonConfigName);`
- L77 _protected typedef_ `using FAchievementDefinitionMap = TMap<FString, FAchievementDefinition>;`
- L78 _protected member_ `TOptional<FAchievementDefinitionMap> AchievementDefinitions;`
- L79 _protected member_ `FAchievementsConfig AchievementsConfig;`
- L80 _protected member_ `FAchievementsXblConfig Config;`
- L81 _protected member_ `FOnlineEventDelegateHandle AchievementUpdateHandle;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Online` (scope `UE`)
- L41 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/AuthXbl.h` (Public)


#### class `UE::Online::FOnlineAccountIdXbl`  
`class FOnlineAccountIdXbl`  
_L19-24_
- L22 _public member_ `FAccountId AccountId;`
- L23 _public member_ `uint64 XUID;`

#### class `UE::Online::FOnlineAccountIdRegistryXbl`  
`class FOnlineAccountIdRegistryXbl : public IOnlineAccountIdRegistry`  
_L26-55_
- inherits: `IOnlineAccountIdRegistry`
- L29 _public prototype_ `static FOnlineAccountIdRegistryXbl& Get();`
- L31 _public prototype_ `FAccountId Find(const uint64 XUID) const;`
- L32 _public prototype_ `FAccountId FindOrAddAccountId(const uint64 XUID);`
- L34 _public prototype_ `uint64 Find(const FAccountId& AccountId) const;`
- L37 _public prototype_ `virtual FString ToString(const FAccountId& AccountId) const override;`
- L38 _public prototype_ `virtual FString ToLogString(const FAccountId& AccountId) const override;`
- L39 _public prototype_ `virtual TArray<uint8> ToReplicationData(const FAccountId& AccountId) const override;`
- L40 _public prototype_ `virtual FAccountId FromReplicationData(const TArray<uint8>& ReplicationString) override;`
- L41 _public prototype_ `virtual FAccountId FromStringData(const FString& StringData) override;`
- L44 _public prototype_ `virtual ~FOnlineAccountIdRegistryXbl() = default;`
- L48 _private prototype_ `const FOnlineAccountIdXbl* FindNoLock(const FAccountId& AccountId) const;` — Retrieve an entry with no lock. For internal use only.
- L49 _private prototype_ `const FOnlineAccountIdXbl* FindNoLock(const uint64 XUID) const;`
- L51 _private member_ `mutable FRWLock Lock;`
- L52 _private member_ `TArray<FOnlineAccountIdXbl> Ids;`
- L53 _private member_ `TMap<uint64, FOnlineAccountIdXbl*> XUIDIndex;`

#### struct `UE::Online::FAccountInfoXbl`  
`struct FAccountInfoXbl final : public FAccountInfo`  
_L57-60_
- inherits: `FAccountInfo`
- L59 _public member_ `FGDKUserHandle UserHandle;`

#### class `UE::Online::FAccountInfoRegistryXbl`  
`class FAccountInfoRegistryXbl final : public FAccountInfoRegistry`  
_L62-75_
- inherits: `FAccountInfoRegistry`
- L65 _public typedef_ `using Super = FAccountInfoRegistry;`
- L67 _public prototype_ `virtual ~FAccountInfoRegistryXbl() = default;`
- L69 _public prototype_ `TSharedPtr<FAccountInfoXbl> FindOrCreate(FPlatformUserId PlatformUserId, FOnlineServicesXbl& Service);`
- L70 _public prototype_ `TSharedPtr<FAccountInfoXbl> Find(FPlatformUserId PlatformUserId) const;`
- L71 _public prototype_ `TSharedPtr<FAccountInfoXbl> Find(FAccountId AccountIdHandle) const;`
- L73 _public prototype_ `void Register(const TSharedRef<FAccountInfoXbl>&UserAuthData);`
- L74 _public prototype_ `void Unregister(FAccountId AccountId);`

#### class `UE::Online::FAuthXbl`  
`class FAuthXbl : public FAuthCommon`  
_L77-100_
- inherits: `FAuthCommon`
- L80 _public typedef_ `using Super = FAuthCommon;`
- L82 _public prototype_ `FAuthXbl(FOnlineServicesXbl& InOwningSubsystem);`
- L83 _public prototype_ `virtual void Initialize() override;`
- L84 _public prototype_ `virtual void PreShutdown() override;`
- L87 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLogin> Login(FAuthLogin::Params&& Params) override;`
- L88 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryExternalAuthToken> QueryExternalAuthToken(FAuthQueryExternalAuthToken::Params&& Params) override;`
- L92 _public prototype_ `virtual const FAccountInfoRegistry& GetAccountInfoRegistry() const override;`
- L95 _protected prototype_ `void InitializeUsers();`
- L96 _protected prototype_ `void UninitializeUsers();`
- L97 _protected prototype_ `void OnInputDeviceConnectionChange(EInputDeviceConnectionState NewConnectionState, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId);`
- L99 _protected member_ `FAccountInfoRegistryXbl AccountInfoRegistry;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/CommerceXbl.h` (Public)


#### class `UE::Online::FCommerceXbl`  
`class FCommerceXbl : public FCommerceCommon`  
_L22-72_
- inherits: `FCommerceCommon`
- L25 _public typedef_ `using Super = FCommerceCommon;`
- L27 _public prototype_ `FCommerceXbl(FOnlineServicesXbl& InServices);`
- L30 _public prototype_ `virtual void Initialize() override;` — TOnlineComponent
- L32 _public prototype_ `virtual void Shutdown() override;` — void Tick(float DeltaSeconds) override;
- L35 _public prototype_ `TOnlineAsyncOpHandle<FCommerceQueryOffers> QueryOffers(FCommerceQueryOffers::Params&& Params) override;`
- L36 _public prototype_ `TOnlineAsyncOpHandle<FCommerceQueryOffersById> QueryOffersById(FCommerceQueryOffersById::Params&& Params) override;`
- L38 _public prototype_ `TOnlineResult<FCommerceGetOffers> GetOffers(FCommerceGetOffers::Params&& Params) override;`
- L39 _public prototype_ `TOnlineResult<FCommerceGetOffersById> GetOffersById(FCommerceGetOffersById::Params&& Params) override;`
- L41 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceShowStoreUI> ShowStoreUI(FCommerceShowStoreUI::Params&& Params) override;`
- L44 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryEntitlements> QueryEntitlements(FCommerceQueryEntitlements::Params&& Params) override;`
- L45 _public prototype_ `virtual TOnlineResult<FCommerceGetEntitlements> GetEntitlements(FCommerceGetEntitlements::Params&& Params) override;`
- L47 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceRedeemEntitlement> RedeemEntitlement(FCommerceRedeemEntitlement::Params&& Params) override;`
- L49 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceCheckout> Checkout(FCommerceCheckout::Params&& Params) override;`
- L53 _protected prototype_ `bool ParseProducts(FAccountId LocalAccountId, XStoreProductQueryHandle ProductQueryHandle, TArray<FOfferId>* OfferIds);`
- L55 _protected prototype_ `XStoreContextHandle GetStoreContextHandle(FGDKUserHandle GDKUser);`
- L56 _protected prototype_ `void CleanupContextHandles();`
- L57 _protected prototype_ `void HandleSuspend();`
- L59 _protected member_ `TMap<FGDKUserHandle, XStoreContextHandle> StoreContexts;`
- L60 _protected member_ `mutable FCriticalSection StoreContextsLock;`
- L62 _protected member_ `bool bStoreContextHandlesInvalidated = false;`
- L64 _protected member_ `TMap<FAccountId, TMap<FOfferId,FOffer>> CachedOffers;`
- L65 _protected member_ `TMap<FAccountId, TMap<FEntitlementId, FEntitlement>> CachedEntitlements;`
- L67 _protected member_ `mutable FCriticalSection CachedOffersLock;`
- L68 _protected member_ `mutable FCriticalSection CachedEntitlementsLock;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/ConnectivityXbl.h` (Public)


#### class `UE::Online::FConnectivityXbl`  
`class FConnectivityXbl : public FConnectivityCommon`  
_L12-26_
- inherits: `FConnectivityCommon`
- L15 _public typedef_ `using Super = FConnectivityCommon;`
- L20 _public prototype_ `virtual void PostInitialize() override;` — TOnlineComponent
- L21 _public prototype_ `virtual void PreShutdown() override;`
- L25 _protected prototype_ `void OnNetworkConnectionStatusChanged(ENetworkConnectionStatus LastConnectionState, ENetworkConnectionStatus ConnectionState);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/EventsXbl.h` (Public)


#### class `UE::Online::FEventsXbl`  
`class FEventsXbl : public TSharedFromThis<FEventsXbl, ESPMode::ThreadSafe>`  
_L29-47_
- inherits: `TSharedFromThis<FEventsXbl,ESPMode::ThreadSafe>`
- desc: class FEventsXbl : public IOnlineEvents
- L32 _public function_ `FEventsXbl(FOnlineServicesXbl* InService)`
- L34 _public prototype_ `virtual ~FEventsXbl() = default;`
- L44 _public prototype_ `virtual bool TriggerEvent(const FAccountId& PlayerId, const TCHAR* EventName, const FOnlineEventParams& EventParams);` — Calls an event @param PlayerId	- Id of the player to call the event on @param Name		- Name of requested event @param Parms		- Parameters that will be passed directly to the event
- L46 _private member_ `FOnlineServicesXbl* Service;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Online` (scope `UE`)
- L22 _typedef_ `typedef TMap<FString, FSchemaVariant> FOnlineEventParams;` (scope `UE::Online`)
- L49 _typedef_ `typedef TSharedPtr<FEventsXbl, ESPMode::ThreadSafe> FEventsXblPtr;` (scope `UE::Online`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/OnlineServicesXbl.h` (Public)


#### enum `UE::Online::EOnlineEnvironment`  
`enum class EOnlineEnvironment : uint8`  
_L26-37_
- L29 _public enumerator_ `Development` — Dev environment
- L31 _public enumerator_ `Certification` — Cert environment
- L33 _public enumerator_ `Production` — Prod environment
- L35 _public enumerator_ `Unknown` — Not determined yet

#### class `UE::Online::FOnlineServicesXbl`  
`class FOnlineServicesXbl : public FOnlineServicesCommon`  
_L40-61_
- inherits: `FOnlineServicesCommon`
- L43 _public typedef_ `using Super = FOnlineServicesCommon;`
- L45 _public prototype_ `FOnlineServicesXbl(FName InInstanceName, FName InInstanceConfigName);`
- L46 _public prototype_ `virtual void RegisterComponents() override;`
- L47 _public function_ `virtual EOnlineServices GetServicesProvider() const override`
- L48 _public prototype_ `virtual void Initialize();`
- L49 _public prototype_ `virtual void PostInitialize();`
- L50 _public prototype_ `virtual void PreShutdown();`
- L52 _public prototype_ `virtual EOnlineEnvironment GetOnlineEnvironment() const;`
- L54 _public member_ `TSharedRef<FUserContextsManagerXbl> ContextManager;`
- L55 _public member_ `TSharedRef<FEventsXbl> EventLauncher;`
- L58 _private prototype_ `void InitializeXblByConfig();`
- L60 _private member_ `XblFunctionContext ServiceCallRoutedHandlerContext = 0;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_XBL_ASYNC_BLOCK_KEY_NAME TEXT("AsyncBlock")`
- L21 _macro_ `#define UE_XBL_ACCOUNT_INFO_KEY_NAME TEXT("AccountInfo")`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Online` (scope `UE`)
- L38 _prototype_ `ENUM_CLASS_FLAGS(EOnlineEnvironment);` (scope `UE::Online`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/PresenceXbl.h` (Public)


#### class `UE::Online::FPresenceXbl`  
`class FPresenceXbl : public FPresenceCommon`  
_L14-44_
- inherits: `FPresenceCommon`
- L19 _public prototype_ `FPresenceXbl(FOnlineServicesXbl& InServices);`
- L21 _public prototype_ `virtual void Initialize() override;`
- L22 _public prototype_ `virtual void PreShutdown() override;`
- L23 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L26 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryPresence> QueryPresence(FQueryPresence::Params&& Params) override;` — IPresence
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FBatchQueryPresence> BatchQueryPresence(FBatchQueryPresence::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineResult<FGetCachedPresence> GetCachedPresence(FGetCachedPresence::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdatePresence> UpdatePresence(FUpdatePresence::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FPartialUpdatePresence> PartialUpdatePresence(FPartialUpdatePresence::Params&& Params) override;`
- L33 _private member_ `uint32 TitleId = 0;`
- L34 _private member_ `FOnlineServicesXbl& Services;`
- L35 _private member_ `TMap<FAccountId, TMap<FAccountId, TSharedRef<FUserPresence>>> PresenceLists;`
- L36 _private prototype_ `TSharedRef<FUserPresence> FindOrCreatePresence(FAccountId LocalAccountId, FAccountId PresenceAccountId);`
- L37 _private prototype_ `void FindPresenceEntriesAndObservingLocalUsers(FAccountId PresenceAccountId, TArray<TSharedRef<FUserPresence>>& OutEntries, TArray<FAccountId>& OutObservers);`
- L39 _private member_ `FOnlineEventDelegateHandle TitleStatusUpdatedHandle;`
- L40 _private member_ `FOnlineEventDelegateHandle OnlineStatusUpdateHandle;`
- L41 _private prototype_ `void OnlineStatusUpdate(const FOnlineStatusUpdate& Update);`
- L42 _private prototype_ `void TitleStatusUpdate(const FTitleStatusUpdate& Update);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/PrivilegesXbl.h` (Public)


#### struct `UE::Online::FPrivilegesXblConfig`  
`struct FPrivilegesXblConfig`  
_L18-22_
- L20 _public member_ `bool bXBLGoldRequired = true;`
- L21 _public member_ `TArray<FString> IgnoredErrorCodes;`

#### class `UE::Online::FPrivilegesXbl`  
`class FPrivilegesXbl : public FPrivilegesCommon`  
_L34-50_
- inherits: `FPrivilegesCommon`
- L37 _public typedef_ `using Super = FPrivilegesCommon;`
- L39 _public prototype_ `FPrivilegesXbl(FOnlineServicesXbl& InOwningSubsystem);`
- L40 _public prototype_ `virtual void Initialize() override;`
- L41 _public prototype_ `virtual void PreShutdown() override;`
- L45 _public prototype_ `TOnlineAsyncOpHandle<FQueryUserPrivilege> QueryUserPrivilege(FQueryUserPrivilege::Params&& Params);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)
- L24 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/SocialXbl.h` (Public)


#### class `UE::Online::FSocialXbl`  
`class FSocialXbl : public FSocialCommon`  
_L12-37_
- inherits: `FSocialCommon`
- L16 _public prototype_ `FSocialXbl(FOnlineServicesXbl& InServices);`
- L19 _public prototype_ `virtual void Initialize() override;` — TOnlineComponent
- L20 _public prototype_ `virtual void PreShutdown() override;`
- L21 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L24 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryFriends> QueryFriends(FQueryFriends::Params&& Params) override;`
- L25 _public prototype_ `virtual TOnlineResult<FGetFriends> GetFriends(FGetFriends::Params&& Params) override;`
- L26 _public prototype_ `virtual TOnlineAsyncOpHandle<FSendFriendInvite> SendFriendInvite(FSendFriendInvite::Params&& Params) override;`
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryBlockedUsers> QueryBlockedUsers(FQueryBlockedUsers::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineResult<FGetBlockedUsers> GetBlockedUsers(FGetBlockedUsers::Params&& Params) override;`
- L33 _private member_ `FOnlineServicesXbl& Services;`
- L34 _private member_ `TMap<FAccountId, TMap<FAccountId, TSharedRef<FFriend>>> FriendsLists;`
- L35 _private member_ `TMap<FAccountId, TArray<FAccountId>> AvoidLists;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/StatsXbl.h` (Public)


#### enum `UE::Online::EXblStatMode`  
`enum class EXblStatMode : uint16`  
_L12-20_
- L15 _public enumerator_ `Mode2013 = 2013` — 2013 stats are driven via events
- L17 _public enumerator_ `Mode2017 = 2017` — 2017 stats are title-managed
- L19 _public enumerator_ `Default = Mode2013` — Default mode to use if not specified

#### struct `UE::Online::FStatsXblConfig`  
`struct FStatsXblConfig`  
_L22-25_
- L24 _public member_ `EXblStatMode StatMode = EXblStatMode::Default;`

#### class `UE::Online::FStatsXbl`  
`class FStatsXbl : public FStatsCommon`  
_L36-59_
- inherits: `FStatsCommon`
- L39 _public typedef_ `using Super = FStatsCommon;`
- L43 _public prototype_ `virtual void Initialize() override;`
- L44 _public prototype_ `virtual void PreShutdown() override;`
- L47 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdateStats> UpdateStats(FUpdateStats::Params&& Params) override;` — IStats
- L48 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryStats> QueryStats(FQueryStats::Params&& Params) override;`
- L49 _public prototype_ `virtual TOnlineAsyncOpHandle<FBatchQueryStats> BatchQueryStats(FBatchQueryStats::Params&& Params) override;`
- L50 _public prototype_ `virtual TOnlineAsyncOpHandle<FTriggerEvent> TriggerEvent(FTriggerEvent::Params&& Params) override;`
- L54 _protected prototype_ `TOnlineAsyncOpRef<FBatchQueryStats> BatchQueryStatsImpl(FBatchQueryStats::Params&& InParams);`
- L56 _protected member_ `FStatsXblConfig Config;`
- L57 _protected member_ `FOnlineEventDelegateHandle StatUpdateHandle;`
- L58 _protected prototype_ `void OnlineStatUpdate(const FOnlineStatUpdate& Update);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L27 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/TitleFileXbl.h` (Public)


#### class `UE::Online::FTitleFileXbl`  
`class FTitleFileXbl : public FTitleFileCommon`  
_L20-37_
- inherits: `FTitleFileCommon`
- L23 _public typedef_ `using Super = FTitleFileCommon;`
- L25 _public prototype_ `FTitleFileXbl(FOnlineServicesXbl& InOwningSubsystem);`
- L26 _public prototype_ `virtual ~FTitleFileXbl() = default;`
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileEnumerateFiles> EnumerateFiles(FTitleFileEnumerateFiles::Params&& Params) override;` — ITitleFile
- L30 _public prototype_ `virtual TOnlineResult<FTitleFileGetEnumeratedFiles> GetEnumeratedFiles(FTitleFileGetEnumeratedFiles::Params&& Params) override;`
- L31 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileReadFile> ReadFile(FTitleFileReadFile::Params&& Params) override;`
- L35 _protected member_ `TOptional<TArray<XblTitleStorageBlobMetadata>> EnumeratedFiles;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/UserContextsManagerXbl.h` (Public)


#### class `UE::Online::UserContextWrapper`  
`class UserContextWrapper : public TSharedFromThis<UserContextWrapper, ESPMode::ThreadSafe>`  
_L34-45_
- inherits: `TSharedFromThis<UserContextWrapper,ESPMode::ThreadSafe>`
- desc: Wrapper class representing a GDK user context. Required as some delegates eg XblStatisticChangedHandler don't admit variable capture, and we can only pass a single pointer in to the delegate, when we need both service instance and User Id.
- L37 _public function_ `UserContextWrapper(TWeakPtr<FUserContextsManagerXbl, ESPMode::ThreadSafe> InManager, uint64 InXUID)`
- L43 _public member_ `TWeakPtr<FUserContextsManagerXbl, ESPMode::ThreadSafe> Manager;`
- L44 _public member_ `uint64 XUID = 0;`

#### struct `UE::Online::FTitleStatusUpdate`  
`struct FTitleStatusUpdate`  
_L51-59_
- desc: Struct for TitleStatusUpdate event
- L54 _public member_ `uint64 XUID;` — The affected account.
- L56 _public member_ `uint64 TitleId;` — The active title.
- L58 _public member_ `uint32 TitleState;` — The new title state.

#### struct `UE::Online::FOnlineStatusUpdate`  
`struct FOnlineStatusUpdate`  
_L62-68_
- desc: Struct for TitleStatusUpdate event
- L65 _public member_ `uint64 XUID;` — The affected account.
- L67 _public member_ `bool bOnline = false;` — Is the user online.

#### struct `UE::Online::FOnlineStatUpdate`  
`struct FOnlineStatUpdate`  
_L71-82_
- desc: Struct for TitleStatusUpdate event
- L74 _public member_ `uint64 XUID;` — The affected account.
- L76 _public member_ `FString StatisticName;` — The affected stat.
- L78 _public member_ `FString StatisticType;` — The type of the affected stat.
- L80 _public member_ `FString StatisticValue;` — The stats new value.

#### struct `UE::Online::FAchievementUpdate`  
`struct FAchievementUpdate`  
_L84-90_
- L87 _public member_ `uint64 XUID;` — The affected account.
- L89 _public member_ `TArray<FAchievementState> AchievementUpdates;` — The updated achievements.

#### struct `UE::Online::FGDKContextInfo`  
`struct FGDKContextInfo`  
_L93-100_
- desc: Store single XboxGDKContext per user
- L95 _public member_ `FGDKContextHandle Handle;`
- L96 _public member_ `XblFunctionContext AchievementChangedContext = INVALID_XBL_FUNCTION_CONTEXT;`
- L97 _public member_ `XblFunctionContext DevicePresenceChangedContext = INVALID_XBL_FUNCTION_CONTEXT;`
- L98 _public member_ `XblFunctionContext TitlePresenceChangedContext = INVALID_XBL_FUNCTION_CONTEXT;`
- L99 _public member_ `XblFunctionContext StatisticChangedContext = INVALID_XBL_FUNCTION_CONTEXT;`

#### class `UE::Online::FUserContextsManagerXbl`  
`class FUserContextsManagerXbl : public TSharedFromThis<FUserContextsManagerXbl, ESPMode::ThreadSafe>`  
_L102-136_
- inherits: `TSharedFromThis<FUserContextsManagerXbl,ESPMode::ThreadSafe>`
- L106 _public function_ `FUserContextsManagerXbl(FOnlineServicesXbl* InService)`
- L107 _public prototype_ `virtual ~FUserContextsManagerXbl() = default;`
- L109 _public prototype_ `void CreateGDKContext(FGDKUserHandle GDKUser);`
- L110 _public prototype_ `void DeleteGDKContext(FGDKUserHandle GDKUser);`
- L111 _public prototype_ `void Shutdown();`
- L114 _public prototype_ `FGDKContextHandle GetGDKContext(FPlatformUserId UserId);` — Returns the GDK context for the given user, or null if the input could not be found/was invalid.
- L115 _public prototype_ `FGDKContextHandle GetGDKContext(uint64 XUID);`
- L116 _public prototype_ `FGDKContextHandle GetGDKContext(FGDKUserHandle GDKUser);`
- L118 _public prototype_ `virtual TOnlineEvent<void(const FTitleStatusUpdate&)> OnTitleStatusUpdate();`
- L119 _public prototype_ `virtual TOnlineEvent<void(const FOnlineStatusUpdate&)> OnOnlineStatusUpdate();`
- L120 _public prototype_ `virtual TOnlineEvent<void(const FOnlineStatUpdate&)> OnStatUpdate();`
- L121 _public prototype_ `virtual TOnlineEvent<void(const FAchievementUpdate&)> OnAchievementUpdate();`
- L125 _private prototype_ `void UnsubscribeContextHandles(uint64 Xuid, FGDKContextInfo& ContextInfo) const;`
- L127 _private member_ `FOnlineServicesXbl* Service;`
- L128 _private member_ `TArray<UserContextWrapperPtr> UserContextWrappers;`
- L129 _private member_ `TMap<uint64, FGDKContextInfo> CachedGDKContexts;`
- L130 _private member_ `mutable FCriticalSection GDKContextsLock;`
- L132 _private member_ `TOnlineEventCallable<void(const FTitleStatusUpdate&)> OnTitleStatusUpdateEvent;`
- L133 _private member_ `TOnlineEventCallable<void(const FOnlineStatusUpdate&)> OnOnlineStatusUpdateEvent;`
- L134 _private member_ `TOnlineEventCallable<void(const FOnlineStatUpdate&)> OnStatUpdateEvent;`
- L135 _private member_ `TOnlineEventCallable<void(const FAchievementUpdate&)> OnAchievementUpdateEvent;`

#### Free symbols / members of external scopes

- L21 _prototype_ `SETHANDLETYPETRAITS(XblContextHandle, XblContextDuplicateHandle, XblContextCloseHandle);`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Online` (scope `UE`)
- L27 _variable_ `static const XblFunctionContext INVALID_XBL_FUNCTION_CONTEXT = 0;` (scope `UE::Online`)
- L47 _typedef_ `typedef TSharedPtr<UserContextWrapper, ESPMode::ThreadSafe> UserContextWrapperPtr;` (scope `UE::Online`)
- L48 _typedef_ `typedef TGDKHandle<XblContextHandle> FGDKContextHandle;` (scope `UE::Online`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/UserFileXbl.h` (Public)


#### class `UE::Online::FUserFileXbl`  
`class FUserFileXbl : public FUserFileCommon`  
_L13-31_
- inherits: `FUserFileCommon`
- L16 _public typedef_ `using Super = FUserFileCommon;`
- L18 _public prototype_ `FUserFileXbl(FOnlineServicesXbl& InOwningSubsystem);`
- L21 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileEnumerateFiles> EnumerateFiles(FUserFileEnumerateFiles::Params&& Params) override;` — IUserFile
- L22 _public prototype_ `virtual TOnlineResult<FUserFileGetEnumeratedFiles> GetEnumeratedFiles(FUserFileGetEnumeratedFiles::Params&& Params) override;`
- L23 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileReadFile> ReadFile(FUserFileReadFile::Params&& Params) override;`
- L24 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileWriteFile> WriteFile(FUserFileWriteFile::Params&& Params) override;`
- L25 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileDeleteFile> DeleteFile(FUserFileDeleteFile::Params&& Params) override;`
- L29 _protected member_ `TMap<FAccountId, TArray<FString>> UserToFiles;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/Microsoft/OnlineServicesXbl/Source/Public/Online/UserInfoXbl.h` (Public)


#### class `UE::Online::FUserInfoXbl`  
`class FUserInfoXbl : public FUserInfoCommon`  
_L12-31_
- inherits: `FUserInfoCommon`
- L15 _public typedef_ `using Super = FUserInfoCommon;`
- L20 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryUserInfo> QueryUserInfo(FQueryUserInfo::Params&& Params) override;` — IUserInfo
- L21 _public prototype_ `virtual TOnlineResult<FGetUserInfo> GetUserInfo(FGetUserInfo::Params&& Params) override;`
- L22 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryUserAvatar> QueryUserAvatar(FQueryUserAvatar::Params&& Params) override;`
- L23 _public prototype_ `virtual TOnlineResult<FGetUserAvatar> GetUserAvatar(FGetUserAvatar::Params&& Params) override;`
- L24 _public prototype_ `virtual TOnlineAsyncOpHandle<FShowUserProfile> ShowUserProfile(FShowUserProfile::Params&& Params) override;`
- L29 _protected member_ `TMap<uint64, TSharedPtr<XblUserProfile>> UserProfileCache;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
