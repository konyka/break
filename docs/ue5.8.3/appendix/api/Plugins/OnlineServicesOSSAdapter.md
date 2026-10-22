# Plugins / OnlineServicesOSSAdapter

- module root: `Plugins/Online/OnlineServicesOSSAdapter/Source`
- headers: 20; symbols: 397
- symbol kinds: class=35, function=37, macro=2, member=56, namespace=45, prototype=170, struct=5, typedef=37, variable=10
- PrivateDependencyModuleNames: CoreOnline
- PublicDependencyModuleNames: Core, Json, OnlineServicesCommon, OnlineServicesInterface, OnlineSubsystem

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/AchievementsOSSAdapter.h` (Public)


#### class `UE::Online::FAchievementsOSSAdapter`  
`class FAchievementsOSSAdapter : public FAchievementsCommon`  
_L14-42_
- inherits: `FAchievementsCommon`
- L17 _public typedef_ `using Super = FAchievementsCommon;`
- L22 _public prototype_ `virtual void Initialize() override;` — IOnlineComponent
- L23 _public prototype_ `virtual void PostInitialize() override;`
- L24 _public prototype_ `virtual void PreShutdown() override;`
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementDefinitions> QueryAchievementDefinitions(FQueryAchievementDefinitions::Params&& Params) override;` — IAchievements
- L28 _public prototype_ `virtual TOnlineResult<FGetAchievementIds> GetAchievementIds(FGetAchievementIds::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineResult<FGetAchievementDefinition> GetAchievementDefinition(FGetAchievementDefinition::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementStates> QueryAchievementStates(FQueryAchievementStates::Params&& Params) override;`
- L31 _public prototype_ `virtual TOnlineResult<FGetAchievementState> GetAchievementState(FGetAchievementState::Params&& Params) const override;`
- L34 _public prototype_ `virtual TOnlineResult<FDisplayAchievementUI> DisplayAchievementUI(FDisplayAchievementUI::Params&& Params) override;` — Intentionally unimplemented, all v1 achis are stats based virtual TOnlineAsyncOpHandle<FUnlockAchievements> UnlockAchievements(FUnlockAchievements::Params&& Params) override;
- L37 _protected member_ `IOnlineAchievementsPtr AchievementsInterface = nullptr;`
- L38 _protected member_ `IOnlineExternalUIPtr ExternalUIInterface = nullptr;`
- L40 _protected typedef_ `using FAchievementDefinitionMap = TMap<FString, FAchievementDefinition>;`
- L41 _protected member_ `TOptional<FAchievementDefinitionMap> AchievementDefinitions;`

#### Free symbols / members of external scopes

- L9 _typedef_ `using IOnlineAchievementsPtr = TSharedPtr<class IOnlineAchievements>;`
- L10 _typedef_ `using IOnlineExternalUIPtr = TSharedPtr<class IOnlineExternalUI>;`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/AuthOSSAdapter.h` (Public)


#### struct `UE::Online::FAuthHandleLoginStatusChangedImpl`  
`struct FAuthHandleLoginStatusChangedImpl`  
_L19-33_
- L21 _public member_ `static constexpr TCHAR Name[] = TEXT("Han`

#### struct `UE::Online::FAuthHandleLoginStatusChangedImpl::Params`  
`struct Params`  
_L23-28_
- L25 _public member_ `FPlatformUserId PlatformUserId;`
- L26 _public member_ `FAccountId AccountId;`
- L27 _public member_ `ELoginStatus NewLoginStatus;`

#### struct `UE::Online::FAuthHandleLoginStatusChangedImpl::Result`  
`struct Result`  
_L30-32_

#### struct `UE::Online::FAccountInfoOSSAdapter`  
`struct FAccountInfoOSSAdapter final : public FAccountInfo`  
_L35-39_
- inherits: `FAccountInfo`
- L37 _public member_ `FUniqueNetIdPtr UniqueNetId;`
- L38 _public member_ `int32 LocalUserNum = INDEX_NONE;`

#### class `UE::Online::FAccountInfoRegistryOSSAdapter`  
`class FAccountInfoRegistryOSSAdapter final : public FAccountInfoRegistry`  
_L41-53_
- inherits: `FAccountInfoRegistry`
- L44 _public typedef_ `using Super = FAccountInfoRegistry;`
- L46 _public prototype_ `virtual ~FAccountInfoRegistryOSSAdapter() = default;`
- L48 _public prototype_ `TSharedPtr<FAccountInfoOSSAdapter> Find(FPlatformUserId PlatformUserId) const;`
- L49 _public prototype_ `TSharedPtr<FAccountInfoOSSAdapter> Find(FAccountId AccountId) const;`
- L51 _public prototype_ `void Register(const TSharedRef<FAccountInfoOSSAdapter>&UserAuthData);`
- L52 _public prototype_ `void Unregister(FAccountId AccountId);`

#### class `UE::Online::FAuthOSSAdapter`  
`class FAuthOSSAdapter : public FAuthCommon`  
_L57-96_
- inherits: `FAuthCommon`
- L60 _public typedef_ `using Super = FAuthCommon;`
- L65 _public prototype_ `virtual void PostInitialize() override;` — IOnlineComponent
- L66 _public prototype_ `virtual void PreShutdown() override;`
- L69 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLogin> Login(FAuthLogin::Params&& Params) override;` — IAuth
- L70 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLogout> Logout(FAuthLogout::Params&& Params) override;`
- L71 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryExternalServerAuthTicket> QueryExternalServerAuthTicket(FAuthQueryExternalServerAuthTicket::Params&& Params) override;`
- L72 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryExternalAuthToken> QueryExternalAuthToken(FAuthQueryExternalAuthToken::Params&& Params) override;`
- L74 _public prototype_ `FUniqueNetIdPtr GetUniqueNetId(FAccountId AccountId) const;`
- L75 _public prototype_ `FAccountId GetAccountId(const FUniqueNetIdRef& UniqueNetId) const;`
- L76 _public prototype_ `int32 GetLocalUserNum(FAccountId AccountId) const;`
- L80 _protected prototype_ `static void CheckMetadata();`
- L83 _protected prototype_ `virtual const FAccountInfoRegistry& GetAccountInfoRegistry() const override;`
- L85 _protected prototype_ `const FOnlineServicesOSSAdapter& GetOnlineServicesOSSAdapter() const;`
- L86 _protected prototype_ `FOnlineServicesOSSAdapter& GetOnlineServicesOSSAdapter();`
- L87 _protected prototype_ `const IOnlineSubsystem& GetSubsystem() const;`
- L88 _protected prototype_ `IOnlineIdentityPtr GetIdentityInterface() const;`
- L90 _protected prototype_ `TOnlineAsyncOpHandle<FAuthHandleLoginStatusChangedImpl> HandleLoginStatusChangedImplOp(FAuthHandleLoginStatusChangedImpl::Params&& Params);`
- L92 _protected prototype_ `bool PopulateAttributes(FAccountInfoOSSAdapter& AccountInfoOSSAdapter) const;`
- L94 _protected member_ `FAccountInfoRegistryOSSAdapter AccountInfoRegistryOSSAdapter;`
- L95 _protected member_ `FDelegateHandle OnLoginStatusChangedHandle[MAX_LOCAL_PLAYERS];`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESERVICESOSSADAPTER_API`
- L13 _typedef_ `using IOnlineIdentityPtr = TSharedPtr<IOnlineIdentity>;`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)
- L55 _typedef_ `using FAuthOSSAdapterPtr = TSharedPtr<class FAuthOSSAdapter>;` (scope `UE::Online`)
- L98 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/CommerceOSSAdapter.h` (Public)


#### class `UE::Online::FCommerceOSSAdapter`  
`class FCommerceOSSAdapter : public FCommerceCommon`  
_L17-50_
- inherits: `FCommerceCommon`
- L20 _public typedef_ `using Super = FCommerceCommon;`
- L24 _public prototype_ `virtual void PostInitialize() override;` — IOnlineComponent
- L25 _public prototype_ `virtual void PreShutdown() override;`
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryOffers> QueryOffers(FCommerceQueryOffers::Params&& Params) override;` — ICommerce
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryOffersById> QueryOffersById(FCommerceQueryOffersById::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineResult<FCommerceGetOffers> GetOffers(FCommerceGetOffers::Params&& Params) override;`
- L31 _public prototype_ `virtual TOnlineResult<FCommerceGetOffersById> GetOffersById(FCommerceGetOffersById::Params&& Params) override;`
- L32 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceShowStoreUI> ShowStoreUI(FCommerceShowStoreUI::Params&& Params) override;`
- L33 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceCheckout> Checkout(FCommerceCheckout::Params&& Params) override;`
- L34 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryTransactionEntitlements> QueryTransactionEntitlements(FCommerceQueryTransactionEntitlements::Params&& Params) override;`
- L35 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryEntitlements> QueryEntitlements(FCommerceQueryEntitlements::Params&& Params) override;`
- L36 _public prototype_ `virtual TOnlineResult<FCommerceGetEntitlements> GetEntitlements(FCommerceGetEntitlements::Params&& Params) override;`
- L37 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceRedeemEntitlement> RedeemEntitlement(FCommerceRedeemEntitlement::Params&& Params) override;`
- L38 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceRetrieveS2SToken> RetrieveS2SToken(FCommerceRetrieveS2SToken::Params&& Params) override;`
- L42 _protected prototype_ `const FOnlineServicesOSSAdapter& GetOnlineServicesOSSAdapter() const;`
- L43 _protected prototype_ `FOnlineServicesOSSAdapter& GetOnlineServicesOSSAdapter();`
- L44 _protected prototype_ `const IOnlineSubsystem& GetSubsystem() const;`
- L45 _protected prototype_ `IOnlinePurchasePtr GetPurchaseInterface() const;`
- L46 _protected prototype_ `IOnlineStoreV2Ptr GetStoreInterface() const;`
- L47 _protected prototype_ `IOnlineExternalUIPtr GetExternalUIInterface() const;`
- L49 _protected member_ `FAuthOSSAdapter* Auth;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/ConnectivityOSSAdapter.h` (Public)


#### class `UE::Online::FConnectivityOSSAdapter`  
`class FConnectivityOSSAdapter : public FConnectivityCommon`  
_L9-26_
- inherits: `FConnectivityCommon`
- L12 _public typedef_ `using Super = FConnectivityCommon;`
- L17 _public prototype_ `virtual void PostInitialize() override;` — IOnlineComponent
- L18 _public prototype_ `virtual void PreShutdown() override;`
- L21 _public prototype_ `virtual TOnlineResult<FGetConnectionStatus> GetConnectionStatus(FGetConnectionStatus::Params&& Params) override;` — IConnectivity
- L24 _protected member_ `FDelegateHandle OnConnectionStatusChangedHandle;`
- L25 _protected member_ `TMap<FString, EOnlineServicesConnectionStatus> CurrentStatus;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/DelegateAdapter.h` (Public)


#### class `UE::Online::TDelegateAdapter`  
`template<typename ComponentType, typename... LambdaArgs> class TDelegateAdapter : public TSharedFromThis<TDelegateAdapter<ComponentType, LambdaArgs...>>`  
_L31-79_
- inherits: `TSharedFromThis<TDelegateAdapter<ComponentType,LambdaArgs...>>`
- L36 _public function_ `TDelegateAdapter(TSharedRef<ComponentType>& InParent) : Parent(TWeakPtr<ComponentType>(InParent))`
- L41 _public function_ `void SetupDelegate(TUniqueFunction<void(LambdaArgs...)>&& InCallback)`
- L51 _public function_ `operator TDelegate<void(LambdaArgs...)>()`
- L63 _public function_ `operator TTSDelegate<void(LambdaArgs...)>()`
- L76 _private member_ `TWeakPtr<ComponentType> Parent;`
- L77 _private member_ `TUniqueFunction<void(LambdaArgs...)> Callback;`
- L78 _private member_ `FDelegateHandle Handle;`

#### class `UE::Online::Private::TDAConverterHelper2`  
`template <typename... Params> class TDAConverterHelper2`  
_L86-88_
- L95 _public function_ `TUniqueFunction<TResultType(ParamTypes...)> GetUniqueFn(CallableObject&& Callable)`
- L101 _public function_ `template<typename ComponentType> TSharedPtr<TDelegateAdapter<ComponentType, ParamTypes...>> Construct(TSharedRef<ComponentType> Interface, CallableObject&& InCallback)`

#### class `UE::Online::Private::TDAConverterHelper2`  
`template <typename CallableObject, typename TResultType, typename... ParamTypes> class TDAConverterHelper2<CallableObject, TResultType, ParamTypes...>`  
_L91-107_
- L95 _public function_ `TUniqueFunction<TResultType(ParamTypes...)> GetUniqueFn(CallableObject&& Callable)`
- L101 _public function_ `template<typename ComponentType> TSharedPtr<TDelegateAdapter<ComponentType, ParamTypes...>> Construct(TSharedRef<ComponentType> Interface, CallableObject&& InCallback)`

#### class `UE::Online::Private::TDAConverterHelper`  
`template <typename CallableObject, typename = void> class TDAConverterHelper`  
_L110-112_

#### class `UE::Online::Private::TDAConverterHelper`  
`template <typename CallableObject, typename ReturnType, typename... ParamTypes> class TDAConverterHelper<CallableObject, ReturnType(ParamTypes...)> : public TDAConverterHelper2<CallableObject, ReturnType, ParamTypes...>`  
_L115-118_
- inherits: `TDAConverterHelper2<CallableObject,ReturnType,ParamTypes...>`

#### class `UE::Online::Private::TDAConverterHelper`  
`template <typename CallableObject, typename ReturnType, typename ObjectType, typename... ParamTypes> class TDAConverterHelper<CallableObject, ReturnType(ObjectType::*)(ParamTypes...)> : public TDAConverterHelper2<CallableObject, ReturnType, ParamTypes...>`  
_L122-125_
- inherits: `TDAConverterHelper2<CallableObject,ReturnType,ParamTypes...>`

#### class `UE::Online::Private::TDAConverterHelper`  
`template <typename CallableObject, typename ReturnType, typename ObjectType, typename... ParamTypes> class TDAConverterHelper<CallableObject, ReturnType(ObjectType::*)(ParamTypes...) const> : public TDAConverterHelper2<CallableObject, ReturnType, ParamTypes...>`  
_L128-131_
- inherits: `TDAConverterHelper2<CallableObject,ReturnType,ParamTypes...>`

#### class `UE::Online::Private::TDAConverter`  
`template <typename CallableObject> class TDAConverter : public TDAConverterHelper<CallableObject, decltype(&std::remove_reference_t<CallableObject>::operator())>`  
_L134-137_
- inherits: `TDAConverterHelper<CallableObject,decltype(&std::remove_reference_t<CallableObject>::operator())>`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Online` (scope `UE`)
- L45 _function_ `` (scope `UE::Online::TDelegateAdapter::SetupDelegate`)
- L55 _function_ `` (scope `UE::Online::TDelegateAdapter::operator TDelegate<void(LambdaArgs...)>`)
- L67 _function_ `` (scope `UE::Online::TDelegateAdapter::operator TTSDelegate<void(LambdaArgs...)>`)
- L84 _namespace_ `namespace Private` (scope `UE::Online`)
- L142 _function_ `template<typename ComponentType, typename Callback> auto MakeDelegateAdapter(TSharedRef<ComponentType> Interface, Callback&& InCallback)` (scope `UE::Online`)
- L148 _function_ `template<typename ComponentType, typename Callback> auto MakeDelegateAdapter(TSharedPtr<ComponentType> Interface, Callback&& InCallback)` (scope `UE::Online`)
- L155 _function_ `template<typename ComponentType, typename Callback> auto MakeDelegateAdapter(ComponentType* Interface, Callback&& InCallback)` (scope `UE::Online`)
- L161 _function_ `template<typename ComponentType, typename Callback> auto MakeDelegateAdapter(ComponentType& Interface, Callback&& InCallback)` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/ErrorsOSSAdapter.h` (Public)


#### Free symbols / members of external scopes

- L6 _typedef_ `using FOnlineErrorOss = ::FOnlineError;`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L8 _namespace_ `namespace Errors` (scope `UE::Online`)
- L11 _prototype_ `FOnlineError FromOssError(const FOnlineErrorOss& Result);` (scope `UE::Online::Errors`)
- L12 _prototype_ `FOnlineError FromOssErrorCode(const FString& ErrorCode);` (scope `UE::Online::Errors`)
- L15 _typedef_ `using TOssPlatformErrorHandler = TUniqueFunction<TOptional<FOnlineError>(const FOnlineError&, const FOnlineErrorOss&)>;` (scope `UE::Online::Errors`) — if you would like to add a parser that transforms custom platform errors into readable online service types, you can call this in your platform's error handler
- L16 _prototype_ `void AddOssPlatformErrorHandler(TOssPlatformErrorHandler&& InFunction);` (scope `UE::Online::Errors`)
- L22 _prototype_ `bool operator==(const UE::Online::FOnlineError& Left, const FOnlineErrorOss& Right);`
- L23 _prototype_ `bool operator==(const FOnlineErrorOss& Left, const UE::Online::FOnlineError& Right);`
- L24 _prototype_ `bool operator!=(const UE::Online::FOnlineError& Left, const FOnlineErrorOss& Right);`
- L25 _prototype_ `bool operator!=(const FOnlineErrorOss& Left, const UE::Online::FOnlineError& Right);`

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/ExternalUIOSSAdapter.h` (Public)


#### class `UE::Online::FExternalUIOSSAdapter`  
`class FExternalUIOSSAdapter : public FExternalUICommon`  
_L12-31_
- inherits: `FExternalUICommon`
- L15 _public typedef_ `using Super = FExternalUICommon;`
- L20 _public prototype_ `virtual void PostInitialize() override;` — TOnlineComponent
- L21 _public prototype_ `virtual void PreShutdown() override;`
- L24 _public prototype_ `virtual TOnlineAsyncOpHandle<FExternalUIShowLoginUI> ShowLoginUI(FExternalUIShowLoginUI::Params&& Params) override;` — IExternalUI
- L25 _public prototype_ `virtual TOnlineAsyncOpHandle<FExternalUIShowFriendsUI> ShowFriendsUI(FExternalUIShowFriendsUI::Params&& Params) override;`
- L27 _public prototype_ `IOnlineExternalUIPtr GetExternalUIInterface() const;`
- L30 _protected member_ `FDelegateHandle OnExternalUIChangeHandle;`

#### Free symbols / members of external scopes

- L8 _typedef_ `using IOnlineExternalUIPtr = TSharedPtr<IOnlineExternalUI>;`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/LeaderboardsOSSAdapter.h` (Public)


#### class `UE::Online::FLeaderboardsOSSAdapter`  
`class FLeaderboardsOSSAdapter : public FLeaderboardsCommon`  
_L15-37_
- inherits: `FLeaderboardsCommon`
- L18 _public typedef_ `using Super = FLeaderboardsCommon;`
- L23 _public prototype_ `virtual void PostInitialize() override;` — IOnlineComponent
- L26 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesForUsers> ReadEntriesForUsers(FReadEntriesForUsers::Params&& Params) override;` — ILeaderboards
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesAroundRank> ReadEntriesAroundRank(FReadEntriesAroundRank::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesAroundUser> ReadEntriesAroundUser(FReadEntriesAroundUser::Params&& Params) override;`
- L31 _protected prototype_ `TOptional<FOnlineError> PrepareLeaderboardReadObject(const FString& BoardName);`
- L32 _protected prototype_ `void ReadLeaderboardsResultFromV1ToV2(const FString& BoardName, TArray<FLeaderboardEntry>& OutEntries);`
- L34 _protected member_ `const FAuthOSSAdapter* Auth;`
- L35 _protected member_ `IOnlineLeaderboardsPtr LeaderboardsInterface;`
- L36 _protected member_ `FOnlineLeaderboardReadPtr ReadObject;`

#### Free symbols / members of external scopes

- L11 _typedef_ `using IOnlineLeaderboardsPtr = TSharedPtr<IOnlineLeaderboards>;`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/MulticastAdapter.h` (Public)


#### class `UE::Online::TMulticastDelegateAdapter`  
`template<typename ComponentType, typename DelegateType, typename LambdaRet, typename... LambdaArgs> class TMulticastDelegateAdapter : public TSharedFromThis<TMulticastDelegateAdapter<ComponentType, DelegateType, LambdaRet, LambdaArgs...>>`  
_L24-83_
- inherits: `TSharedFromThis<TMulticastDelegateAdapter<ComponentType,DelegateType,LambdaRet,LambdaArgs...>>`
- L29 _public function_ `TMulticastDelegateAdapter(TSharedRef<ComponentType>& InParent, DelegateType& InDelegate) : Parent(TWeakPtr<ComponentType>(InParent)) , Delegate(InDelegate)`
- L35 _public function_ `void SetupDelegate(TUniqueFunction<LambdaRet(LambdaArgs...)>&& InCallback)`
- L68 _public function_ `FDelegateHandle GetHandle()`
- L73 _public function_ `TWeakPtr<TMulticastDelegateAdapter<ComponentType, DelegateType, LambdaRet, LambdaArgs...>> AsWeak()`
- L79 _private member_ `TWeakPtr<ComponentType> Parent;`
- L80 _private member_ `TUniqueFunction<LambdaRet(LambdaArgs...)> Callback;`
- L81 _private member_ `DelegateType& Delegate;`
- L82 _private member_ `FDelegateHandle Handle;`

#### class `UE::Online::Private::TMAConverterHelper2`  
`template <typename... Params> class TMAConverterHelper2`  
_L91-93_
- L100 _public function_ `TUniqueFunction<TResultType(ParamTypes...)> GetUniqueFn(CallableObject&& Callable)`
- L106 _public function_ `template<typename ComponentType, typename DelegateType> TSharedPtr<TMulticastDelegateAdapter<ComponentType, DelegateType, TResultType, ParamTypes...>> Construct(TSharedRef<ComponentType> Interface, DelegateType& InDelegate, CallableObject&& InCallback)`

#### class `UE::Online::Private::TMAConverterHelper2`  
`template <typename CallableObject, typename TResultType, typename... ParamTypes> class TMAConverterHelper2<CallableObject, TResultType, ParamTypes...>`  
_L96-112_
- L100 _public function_ `TUniqueFunction<TResultType(ParamTypes...)> GetUniqueFn(CallableObject&& Callable)`
- L106 _public function_ `template<typename ComponentType, typename DelegateType> TSharedPtr<TMulticastDelegateAdapter<ComponentType, DelegateType, TResultType, ParamTypes...>> Construct(TSharedRef<ComponentType> Interface, DelegateType& InDelegate, CallableObject&& InCallback)`

#### class `UE::Online::Private::TMAConverterHelper`  
`template <typename CallableObject, typename = void> class TMAConverterHelper`  
_L115-117_

#### class `UE::Online::Private::TMAConverterHelper`  
`template <typename CallableObject, typename ReturnType, typename... ParamTypes> class TMAConverterHelper<CallableObject, ReturnType(ParamTypes...)> : public TMAConverterHelper2<CallableObject, ReturnType, ParamTypes...>`  
_L120-123_
- inherits: `TMAConverterHelper2<CallableObject,ReturnType,ParamTypes...>`

#### class `UE::Online::Private::TMAConverterHelper`  
`template <typename CallableObject, typename ReturnType, typename ObjectType, typename... ParamTypes> class TMAConverterHelper<CallableObject, ReturnType(ObjectType::*)(ParamTypes...)> : public TMAConverterHelper2<CallableObject, ReturnType, ParamTypes...>`  
_L127-130_
- inherits: `TMAConverterHelper2<CallableObject,ReturnType,ParamTypes...>`

#### class `UE::Online::Private::TMAConverterHelper`  
`template <typename CallableObject, typename ReturnType, typename ObjectType, typename... ParamTypes> class TMAConverterHelper<CallableObject, ReturnType(ObjectType::*)(ParamTypes...) const> : public TMAConverterHelper2<CallableObject, ReturnType, ParamTypes...>`  
_L133-136_
- inherits: `TMAConverterHelper2<CallableObject,ReturnType,ParamTypes...>`

#### class `UE::Online::Private::TMAConverter`  
`template <typename CallableObject> class TMAConverter : public TMAConverterHelper<CallableObject, decltype(&std::remove_reference_t<CallableObject>::operator())>`  
_L139-142_
- inherits: `TMAConverterHelper<CallableObject,decltype(&std::remove_reference_t<CallableObject>::operator())>`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Online` (scope `UE`)
- L41 _function_ `` (scope `UE::Online::TMulticastDelegateAdapter::SetupDelegate`)
- L88 _namespace_ `namespace Private` (scope `UE::Online`)
- L146 _function_ `template<typename ComponentType, typename DelegateType, typename Callback> auto MakeMulticastAdapter(TSharedRef<ComponentType> Interface, DelegateType& InDelegate, Callback&& InCallback)` (scope `UE::Online`)
- L152 _function_ `template<typename ComponentType, typename DelegateType, typename Callback> auto MakeMulticastAdapter(TSharedPtr<ComponentType> Interface, DelegateType& InDelegate, Callback&& InCallback)` (scope `UE::Online`)
- L159 _function_ `template<typename ComponentType, typename DelegateType, typename Callback> auto MakeMulticastAdapter(ComponentType* Interface, DelegateType& InDelegate, Callback&& InCallback)` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/OnlineIdOSSAdapter.h` (Public)


#### class `UE::Online::TOnlineUniqueNetIdRegistry`  
`template<typename IdType> class TOnlineUniqueNetIdRegistry : public IOnlineIdRegistry<IdType>`  
_L15-123_
- inherits: `IOnlineIdRegistry<IdType>`
- desc: A net id registry suitable for use with OSS FUniqueNetIds
- L18 _public function_ `TOnlineUniqueNetIdRegistry(EOnlineServices InOnlineServicesType) : OnlineServicesType(InOnlineServicesType)`
- L23 _public prototype_ `virtual ~TOnlineUniqueNetIdRegistry() = default;`
- L25 _public function_ `TOnlineId<IdType> FindOrAddHandle(const FUniqueNetIdRef& IdValue)`
- L63 _public function_ `FUniqueNetIdPtr GetIdValue(const TOnlineId<IdType> OnlineId) const` — Returns a copy as it's not thread safe to return a pointer/ref to an element of an array that can be relocated by another thread.
- L76 _public function_ `FUniqueNetIdRef GetIdValueChecked(const TOnlineId<IdType> OnlineId) const`
- L81 _public function_ `bool IsHandleExpired(const FOnlineSessionId& InSessionId) const`
- L87 _public function_ `virtual FString ToString(const TOnlineId<IdType>& OnlineId) const override`
- L93 _public function_ `virtual FString ToLogString(const TOnlineId<IdType>& OnlineId) const override`
- L99 _public function_ `virtual TArray<uint8> ToReplicationData(const TOnlineId<IdType>& OnlineId) const override`
- L105 _public function_ `virtual TOnlineId<IdType> FromReplicationData(const TArray<uint8>& OnlineId) override`
- L110 _public function_ `virtual TOnlineId<IdType> FromStringData(const FString& StringData) override`
- L118 _private member_ `mutable FTransactionallySafeRWLock Lock;`
- L120 _private member_ `EOnlineServices OnlineServicesType;`
- L121 _private member_ `TArray<FUniqueNetIdRef> IdValues;`
- L122 _private member_ `TUniqueNetIdMap<uint32> IdValueToHandleMap;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L125 _typedef_ `using FOnlineAccountIdRegistryOSSAdapter = TOnlineUniqueNetIdRegistry<OnlineIdHandleTags::FAccount>;` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/OnlineServicesOSSAdapter.h` (Public)


#### class `UE::Online::FOnlineServicesOSSAdapter`  
`class FOnlineServicesOSSAdapter : public FOnlineServicesCommon`  
_L15-35_
- inherits: `FOnlineServicesCommon`
- L18 _public typedef_ `using Super = FOnlineServicesCommon;`
- L20 _public prototype_ `FOnlineServicesOSSAdapter(EOnlineServices InServicesType, const FString& InServiceConfigName, FName InInstanceName, IOnlineSubsystem* InSubsystem);`
- L22 _public prototype_ `virtual void RegisterComponents() override;`
- L23 _public prototype_ `virtual void Initialize() override;`
- L24 _public function_ `virtual EOnlineServices GetServicesProvider() const override`
- L25 _public prototype_ `virtual TOnlineResult<FGetResolvedConnectString> GetResolvedConnectString(FGetResolvedConnectString::Params&& Params) override;`
- L27 _public function_ `IOnlineSubsystem& GetSubsystem() const`
- L28 _public function_ `FOnlineAccountIdRegistryOSSAdapter& GetAccountIdRegistry() const`
- L29 _public function_ `FOnlineAccountIdRegistryOSSAdapter& GetAccountIdRegistry()`
- L32 _protected member_ `EOnlineServices ServicesType;`
- L33 _protected member_ `IOnlineSubsystem* Subsystem;`
- L34 _protected member_ `FOnlineAccountIdRegistryOSSAdapter* AccountIdRegistry;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESERVICESOSSADAPTER_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/OnlineServicesOSSAdapterModule.h` (Public)


#### class `UE::Online::FOnlineServicesOSSAdapterModule`  
`class FOnlineServicesOSSAdapterModule : public IModuleInterface`  
_L12-38_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public prototype_ `void GetAllAdapters(TArray<TSharedPtr<FOnlineServicesOSSAdapter>>& OutOSSAdapters);` — Get list of all instantiated OnlineServicesAdapter @param OutOSSAdapters Array of online services adapters to fill
- L30 _public prototype_ `void RegisterOSSAdapter(const TSharedPtr<FOnlineServicesOSSAdapter> OnlineServicesOSSAdapter);` — Register a new OnlineServicesAdapter to keep track of it @param OnlineServicesOSSAdapter Online service adapter to track
- L33 _protected prototype_ `void OnSubsystemPreReload(IOnlineSubsystem* OnlineSubsystem);`
- L35 _protected member_ `FDelegateHandle OnSubsystemPreReloadHandle;`
- L36 _protected member_ `TArray<TWeakPtr<FOnlineServicesOSSAdapter>> OSSAdapters;`
- L37 _protected member_ `TArray<struct FOSSAdapterService> CachedServices;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/PresenceOSSAdapter.h` (Public)


#### class `UE::Online::FPresenceOSSAdapter`  
`class FPresenceOSSAdapter : public FPresenceCommon`  
_L15-45_
- inherits: `FPresenceCommon`
- L18 _public typedef_ `using Super = FPresenceCommon;`
- L23 _public prototype_ `virtual void PostInitialize() override;` — IOnlineComponent
- L24 _public prototype_ `virtual void PreShutdown() override;`
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryPresence> QueryPresence(FQueryPresence::Params&& Params) override;` — IPresence
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FBatchQueryPresence> BatchQueryPresence(FBatchQueryPresence::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineResult<FGetCachedPresence> GetCachedPresence(FGetCachedPresence::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdatePresence> UpdatePresence(FUpdatePresence::Params&& Params) override;`
- L31 _public prototype_ `virtual TOnlineAsyncOpHandle<FPartialUpdatePresence> PartialUpdatePresence(FPartialUpdatePresence::Params&& Params) override;`
- L33 _public prototype_ `FUniqueNetIdRef GetUniqueNetId(FAccountId AccountId) const;`
- L34 _public prototype_ `int32 GetLocalUserNum(FAccountId AccountId) const;`
- L36 _public prototype_ `static EUserPresenceStatus StatusV1toV2(EOnlinePresenceState::Type Status);`
- L37 _public prototype_ `static EOnlinePresenceState::Type StatusV2toV1(EUserPresenceStatus Status);`
- L40 _protected member_ `const FAuthOSSAdapter* Auth;`
- L41 _protected member_ `IOnlinePresencePtr PresenceInt;`
- L43 _protected prototype_ `TSharedRef<FUserPresence> PresenceV1toV2(FAccountId Accountid, FOnlineUserPresence& Presence);`
- L44 _protected prototype_ `TSharedRef<FOnlineUserPresence> PresenceV2toV1(FUserPresence& Presence);`

#### Free symbols / members of external scopes

- L11 _typedef_ `using IOnlinePresencePtr = TSharedPtr<IOnlinePresence>;`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/PrivilegesOSSAdapter.h` (Public)


#### class `UE::Online::FPrivilegesOSSAdapter`  
`class FPrivilegesOSSAdapter : public FPrivilegesCommon`  
_L12-28_
- inherits: `FPrivilegesCommon`
- L15 _public typedef_ `using Super = FPrivilegesCommon;`
- L20 _public prototype_ `virtual void PostInitialize() override;` — TOnlineComponent
- L21 _public prototype_ `virtual void PreShutdown() override;`
- L24 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryUserPrivilege> QueryUserPrivilege(FQueryUserPrivilege::Params&& Params) override;` — IPermission
- L27 _protected prototype_ `IOnlineIdentityPtr GetIdentityInterface() const;`

#### Free symbols / members of external scopes

- L8 _typedef_ `using IOnlineIdentityPtr = TSharedPtr<IOnlineIdentity>;`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/SessionsOSSAdapter.h` (Public)


#### class `UE::Online::FSessionOSSAdapter`  
`class FSessionOSSAdapter : public FSessionCommon`  
_L36-51_
- inherits: `FSessionCommon`
- L39 _public prototype_ `FSessionOSSAdapter() = default;`
- L40 _public prototype_ `FSessionOSSAdapter(const FSessionOSSAdapter& InSession) = default;`
- L41 _public prototype_ `FSessionOSSAdapter(const FOnlineSession& InSession, const FOnlineSessionId& InSessionId);`
- L43 _public prototype_ `static const FSessionOSSAdapter& Cast(const ISession& InSession);`
- L45 _public prototype_ `const FOnlineSession& GetV1Session() const;`
- L47 _public prototype_ `virtual void DumpState() const override;`
- L50 _private member_ `FOnlineSession V1Session;`

#### class `UE::Online::FSessionsOSSAdapter`  
`class FSessionsOSSAdapter : public FSessionsCommon`  
_L53-121_
- inherits: `FSessionsCommon`
- L56 _public typedef_ `using Super = FSessionsCommon;`
- L60 _public prototype_ `FSessionsOSSAdapter(FOnlineServicesOSSAdapter& InOwningSubsystem);`
- L61 _public prototype_ `virtual ~FSessionsOSSAdapter() = default;`
- L64 _public prototype_ `virtual void Initialize() override;` — IOnlineComponent
- L65 _public prototype_ `virtual void Shutdown() override;`
- L68 _public prototype_ `virtual TFuture<TOnlineResult<FCreateSession>> CreateSessionImpl(const FCreateSession::Params& Params) override;` — FSessionsCommon
- L69 _public prototype_ `virtual TFuture<TOnlineResult<FUpdateSessionSettings>> UpdateSessionSettingsImpl(const FUpdateSessionSettings::Params& Params) override;`
- L70 _public prototype_ `virtual TFuture<TOnlineResult<FLeaveSession>> LeaveSessionImpl(const FLeaveSession::Params& Params) override;`
- L71 _public prototype_ `virtual TFuture<TOnlineResult<FFindSessions>> FindSessionsImpl(const FFindSessions::Params& Params) override;`
- L72 _public prototype_ `virtual TFuture<TOnlineResult<FStartMatchmaking>> StartMatchmakingImpl(const FStartMatchmaking::Params& Params) override;`
- L73 _public prototype_ `virtual TFuture<TOnlineResult<FJoinSession>> JoinSessionImpl(const FJoinSession::Params& Params) override;`
- L74 _public prototype_ `virtual TFuture<TOnlineResult<FAddSessionMember>> AddSessionMemberImpl(const FAddSessionMember::Params& Params) override;`
- L75 _public prototype_ `virtual TFuture<TOnlineResult<FRemoveSessionMember>> RemoveSessionMemberImpl(const FRemoveSessionMember::Params& Params) override;`
- L76 _public prototype_ `virtual TFuture<TOnlineResult<FSendSessionInvite>> SendSessionInviteImpl(const FSendSessionInvite::Params& Params) override;`
- L78 _public prototype_ `TOnlineResult<FGetResolvedConnectString> GetResolvedConnectString(const FGetResolvedConnectString::Params& Params);`
- L81 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FFindSessions::Params& Params) const override;`
- L82 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FJoinSession::Params& Params) const override;`
- L83 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FSendSessionInvite::Params& Params) const override;`
- L87 _private prototype_ `bool UpdateV2Session(const FName& SessionName);` — Updates a local session's state by retrieving the equivalent from the OSS
- L90 _private prototype_ `FOnlineSessionSettings BuildV1SettingsForCreate(const FCreateSession::Params& Params) const;` — Builds a V1 Session Settings data type from V2 session creation parameters
- L92 _private prototype_ `FOnlineSessionSettings BuildV1SettingsForUpdate(const FAccountId& LocalAccountId, const TSharedRef<ISession>& Session, const FSessionSettings& SessionSettings) const;` — Builds a V1 Session Settings data type from V2 session data
- L94 _private prototype_ `void WriteV2SessionSettingsFromV1Session(const FOnlineSession* InSession, TSharedRef<FSessionOSSAdapter>& OutSession) const;` — Writes V1 Session Settings information into the passed V2 equivalent
- L96 _private prototype_ `void WriteV2SessionSettingsFromV1NamedSession(const FNamedOnlineSession* InSession, TSharedRef<FSessionOSSAdapter>& OutSession) const;` — Writes V1 Session Settings information contained in Named session type into the passed V2 equivalent
- L98 _private prototype_ `FOnlineSession BuildV1Session(const TSharedRef<const ISession> InSession) const;` — Builds a V1 Session data type from a V2 equivalent
- L100 _private prototype_ `TSharedRef<FSessionCommon> BuildV2Session(const FNamedOnlineSession* InSession) const;` — Builds a V2 Session data type from a V1 equivalent
- L101 _private prototype_ `TSharedRef<FSessionCommon> BuildV2Session(const FOnlineSession* InSession) const;`
- L103 _private prototype_ `TArray<TSharedRef<FSessionCommon>> BuildV2SessionSearchResults(const TArray<FOnlineSessionSearchResult>& SessionSearchResults) const;` — Builds a V2 Session Search Results array from the passed V1 equivalent types
- L106 _private prototype_ `bool GetAccountIdAndSessionIdFromNamedSession(const FName& SessionName, FAccountId& AccountId, FOnlineSessionId& OnlineSessionId) const;` — Helper to get access to the account id and session id for V1 named sessions
- L108 _private prototype_ `bool GetV2SessionIdFromV1NamedSession(const FName& SessionName, FOnlineSessionId& OnlineSessionId) const;` — Helper to get the V2 session id from a v1 named session
- L110 _private prototype_ `bool GetV2SessionCreatorFromV1NamedSession(const FName& SessionName, FAccountId& AccountId) const;` — Helper to get the V2 session creator account id from a v1 named session
- L112 _private prototype_ `FOnlineSessionIdRegistryOSSAdapter& GetSessionIdRegistry() const;`
- L113 _private prototype_ `FOnlineSessionInviteIdRegistryOSSAdapter& GetSessionInviteIdRegistry() const;`
- L116 _protected member_ `IOnlineSessionPtr SessionsInterface;`
- L117 _protected member_ `IOnlineIdentityPtr IdentityInterface;`
- L120 _protected member_ `TMap<FAccountId, TSharedRef<FOnlineSessionSearch>> PendingV1SessionSearchesPerUser;` — Cache of session search information to be used by ongoing session searches, indexed per user. Entries are removed upon search completion.

#### Free symbols / members of external scopes

- L12 _typedef_ `using IOnlineSessionPtr = TSharedPtr<class IOnlineSession>;`
- L13 _typedef_ `using IOnlineIdentityPtr = TSharedPtr<class IOnlineIdentity>;`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)
- L20 _typedef_ `using FOnlineSessionIdRegistryOSSAdapter = TOnlineUniqueNetIdRegistry<OnlineIdHandleTags::FSession>;` (scope `UE::Online`) — Registry of V1 session ids in FUniqueNetIdRef format, indexed by FOnlineSessionId
- L22 _typedef_ `using FOnlineSessionInviteIdRegistryOSSAdapter = FOnlineSessionInviteIdStringRegistry;` (scope `UE::Online`)
- L24 _variable_ `static FName OSS_ADAPTER_SESSIONS_ALLOW_SANCTIONED_PLAYERS = TEXT("OSS` (scope `UE::Online`)
- L25 _variable_ `static FName OSS_ADAPTER_SESSIONS_ALLOW_UNREGISTERED_PLAYERS = TEXT("OSS` (scope `UE::Online`)
- L26 _variable_ `static FName OSS_ADAPTER_SESSIONS_USE_LOBBIES_IF_AVAILABLE = TEXT("OSS` (scope `UE::Online`)
- L27 _variable_ `static FName OSS_ADAPTER_SESSIONS_USE_LOBBIES_VOICE_CHAT_IF_AVAILABLE = TEXT("OSS` (scope `UE::Online`)
- L28 _variable_ `static FName OSS_ADAPTER_SESSIONS_USES_STATS = TEXT("OSS` (scope `UE::Online`)
- L29 _variable_ `static FName OSS_ADAPTER_SESSIONS_SCHEMA_NAME = TEXT("OSS` (scope `UE::Online`)
- L30 _variable_ `static FName OSS_ADAPTER_SESSIONS_BUILD_UNIQUE_ID = TEXT("OSS` (scope `UE::Online`)
- L31 _variable_ `static FName OSS_ADAPTER_SESSIONS_PING_IN_MS = TEXT("OSS` (scope `UE::Online`)
- L33 _variable_ `static FName OSS_ADAPTER_SESSION_SEARCH_PING_BUCKET_SIZE = TEXT("OSS` (scope `UE::Online`)
- L34 _variable_ `static FName OSS_ADAPTER_SESSION_SEARCH_PLATFORM_HASH = TEXT("OSS` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/SocialOSSAdapter.h` (Public)


#### class `UE::Online::FSocialOSSAdapter`  
`class FSocialOSSAdapter : public FSocialCommon`  
_L13-47_
- inherits: `FSocialCommon`
- L16 _public typedef_ `using Super = FSocialCommon;`
- L21 _public prototype_ `virtual void PostInitialize() override;` — IOnlineComponent
- L22 _public prototype_ `virtual void PreShutdown() override;`
- L25 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryFriends> QueryFriends(FQueryFriends::Params&& Params) override;` — ISocial
- L26 _public prototype_ `virtual TOnlineResult<FGetFriends> GetFriends(FGetFriends::Params&& Params) override;`
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FSendFriendInvite> SendFriendInvite(FSendFriendInvite::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FAcceptFriendInvite> AcceptFriendInvite(FAcceptFriendInvite::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FRejectFriendInvite> RejectFriendInvite(FRejectFriendInvite::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryBlockedUsers> QueryBlockedUsers(FQueryBlockedUsers::Params&& Params) override;`
- L31 _public prototype_ `virtual TOnlineResult<FGetBlockedUsers> GetBlockedUsers(FGetBlockedUsers::Params&& Params) override;`
- L32 _public prototype_ `virtual TOnlineAsyncOpHandle<FBlockUser> BlockUser(FBlockUser::Params&& Params) override;`
- L35 _protected prototype_ `FAccountId GetAccountId(int32 LocalUserNum);`
- L36 _protected prototype_ `void OnFriendsChanged();`
- L37 _protected prototype_ `void OnBlockListChanged(int32 LocalUserNum, const FString& ListName);`
- L39 _protected member_ `FDelegateHandle OnFriendsChangedDelegateHandles[MAX_LOCAL_PLAYERS];`
- L40 _protected member_ `FDelegateHandle OnBlockListChangedDelegateHandles[MAX_LOCAL_PLAYERS];`
- L42 _protected member_ `TMap<FAccountId, TMap<FAccountId, ERelationship>> Friends;`
- L43 _protected member_ `TMap<FAccountId, TSet<FAccountId>> BlockedUsers;`
- L45 _protected member_ `const FAuthOSSAdapter* Auth = nullptr;`
- L46 _protected member_ `IOnlineFriendsPtr FriendsInt;`

#### Free symbols / members of external scopes

- L9 _typedef_ `using IOnlineFriendsPtr = TSharedPtr<IOnlineFriends>;`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/StatsOSSAdapter.h` (Public)


#### class `UE::Online::FStatsOSSAdapter`  
`class FStatsOSSAdapter : public FStatsCommon`  
_L15-40_
- inherits: `FStatsCommon`
- L18 _public typedef_ `using Super = FStatsCommon;`
- L23 _public prototype_ `virtual void PostInitialize() override;` — IOnlineComponent
- L26 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdateStats> UpdateStats(FUpdateStats::Params&& Params) override;` — IStats
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryStats> QueryStats(FQueryStats::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FBatchQueryStats> BatchQueryStats(FBatchQueryStats::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FResetStats> ResetStats(FResetStats::Params&& Params) override;`
- L34 _private prototype_ `FOnlineError ConvertUpdateUsersStatsV2toV1(const TArray<FUserStats>& UpdateUsersStats, TArray<FOnlineStatsUserUpdatedStats>& OutUpdateUserStatsV1);`
- L35 _private prototype_ `void ConvertStatValueV2ToStatUpdateV1(const FString& StatName, const FStatValue& StatValue, FOnlineStatUpdate& OutOnlineStatUpdate);`
- L36 _private prototype_ `void ConvertStatValueV1ToStatValueV2(const FOnlineStatValue& OnlineStatValue, FStatValue& OutStatValue);`
- L38 _private member_ `const FAuthOSSAdapter* Auth;`
- L39 _private member_ `IOnlineStatsPtr StatsInterface;`

#### Free symbols / members of external scopes

- L11 _typedef_ `using IOnlineStatsPtr = TSharedPtr<IOnlineStats>;`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/TitleFileOSSAdapter.h` (Public)


#### class `UE::Online::FTitleFileOSSAdapter`  
`class FTitleFileOSSAdapter : public FTitleFileCommon`  
_L13-32_
- inherits: `FTitleFileCommon`
- L16 _public typedef_ `using Super = FTitleFileCommon;`
- L21 _public prototype_ `virtual void PostInitialize() override;` — IOnlineComponent
- L24 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileEnumerateFiles> EnumerateFiles(FTitleFileEnumerateFiles::Params&& Params) override;` — ITitleFile
- L25 _public prototype_ `virtual TOnlineResult<FTitleFileGetEnumeratedFiles> GetEnumeratedFiles(FTitleFileGetEnumeratedFiles::Params&& Params) override;`
- L26 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileReadFile> ReadFile(FTitleFileReadFile::Params&& Params) override;`
- L29 _protected member_ `IOnlineTitleFilePtr TitleFileInterface = nullptr;`
- L31 _protected member_ `TOptional<TArray<FString>> EnumeratedFiles;`

#### Free symbols / members of external scopes

- L9 _typedef_ `using IOnlineTitleFilePtr = TSharedPtr<class IOnlineTitleFile>;`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/UserFileOSSAdapter.h` (Public)


#### struct `UE::Online::FUserFileOSSAdapterConfig`  
`struct FUserFileOSSAdapterConfig`  
_L13-16_
- L15 _public member_ `bool bCompressBeforeUpload = false;`

#### class `UE::Online::FUserFileOSSAdapter`  
`class FUserFileOSSAdapter : public FUserFileCommon`  
_L25-48_
- inherits: `FUserFileCommon`
- L28 _public typedef_ `using Super = FUserFileCommon;`
- L33 _public prototype_ `virtual void PostInitialize() override;` — IOnlineComponent
- L34 _public prototype_ `virtual void UpdateConfig() override;`
- L37 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileEnumerateFiles> EnumerateFiles(FUserFileEnumerateFiles::Params&& Params) override;` — IUserFile
- L38 _public prototype_ `virtual TOnlineResult<FUserFileGetEnumeratedFiles> GetEnumeratedFiles(FUserFileGetEnumeratedFiles::Params&& Params) override;`
- L39 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileReadFile> ReadFile(FUserFileReadFile::Params&& Params) override;`
- L40 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileWriteFile> WriteFile(FUserFileWriteFile::Params&& Params) override;`
- L42 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileDeleteFile> DeleteFile(FUserFileDeleteFile::Params&& Params) override;` — virtual TOnlineAsyncOpHandle<FUserFileCopyFile> CopyFile(FUserFileCopyFile::Params&& Params) override; // Unimplemented
- L45 _protected member_ `FUserFileOSSAdapterConfig Config;`
- L46 _protected member_ `IOnlineUserCloudPtr UserCloudInterface = nullptr;`
- L47 _protected member_ `TMap<FAccountId, TArray<FString>> EnumeratedFiles;`

#### Free symbols / members of external scopes

- L9 _typedef_ `using IOnlineUserCloudPtr = TSharedPtr<class IOnlineUserCloud>;`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L18 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesOSSAdapter/Source/Public/Online/UserInfoOSSAdapter.h` (Public)


#### class `UE::Online::FUserInfoOSSAdapter`  
`class FUserInfoOSSAdapter : public FUserInfoCommon`  
_L13-29_
- inherits: `FUserInfoCommon`
- L16 _public typedef_ `using Super = FUserInfoCommon;`
- L21 _public prototype_ `virtual void Initialize() override;` — IOnlineComponent
- L24 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryUserInfo> QueryUserInfo(FQueryUserInfo::Params&& Params) override;` — IUserInfo
- L25 _public prototype_ `virtual TOnlineResult<FGetUserInfo> GetUserInfo(FGetUserInfo::Params&& Params) override;`
- L28 _protected member_ `IOnlineUserPtr UserInterface = nullptr;`

#### Free symbols / members of external scopes

- L9 _typedef_ `using IOnlineUserPtr = TSharedPtr<class IOnlineUser>;`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
