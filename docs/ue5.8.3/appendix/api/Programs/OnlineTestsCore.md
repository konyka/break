# Programs / OnlineTestsCore

- module root: `Source/Programs/Online/OnlineTestsCore/Source`
- headers: 59; symbols: 804
- symbol kinds: class=26, enum=6, enumerator=19, function=224, macro=14, member=245, namespace=9, prototype=86, struct=74, typedef=98, variable=3
- PublicDependencyModuleNames: ApplicationCore, Core, CoreUObject, EOSSDK, EOSShared, EngineSettings, HTTP, Json, JsonUtilities, OnlineServicesCommon, OnlineServicesInterface, OnlineServicesOSSAdapter, OnlineSubsystem, Projects, SSL

### `Source/Programs/Online/OnlineTestsCore/Source/Private/TestUtilities.h` (Private)


#### class `FTestUtilities`  
`class FTestUtilities`  
_L8-24_
- L11 _public function_ `static FString GetUniqueTestString()`
- L18 _public function_ `static int32 GetUniqueTestInteger()`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/AsyncTestStep.h` (Public)


#### class `TestSafePromiseDeleter`  
`class TestSafePromiseDeleter`  
_L16-42_
- desc: Class to protect unfilled promises made due to a test exiting early on a failed assert during a callback. This will make sure the promise created by this class is always filled out to at least be false.
- L19 _public function_ `TestSafePromiseDeleter()`
- L23 _public function_ `~TestSafePromiseDeleter()`
- L30 _public function_ `void SetValue(bool Result)`
- L35 _public function_ `TFuture<bool> GetFuture()`
- L40 _protected member_ `TPromise<bool> Promise;`
- L41 _protected member_ `bool bPromiseCalled;`

#### class `FAsyncTestStep`  
`class FAsyncTestStep : public FTestPipeline::FStep`  
_L46-90_
- inherits: `FTestPipeline::FStep`
- desc: Helper class for doing async test steps instead of normal tick-driven test steps
- L50 _public prototype_ `virtual void Run(FAsyncStepResult Result, const IOnlineServicesPtr& OnlineServices) = 0;` — main entry point function- OnlineSubsystem will be V2. The future bool in Result is whether to continue the test (essentially just a requirement)
- L52 _public function_ `virtual ~FAsyncTestStep() override`
- L61 _public function_ `virtual EContinuance Tick(const IOnlineServicesPtr& OnlineServices) override`
- L86 _protected member_ `bool bInitialized = false;`
- L87 _protected member_ `TAtomic<bool> bComplete = false;`
- L88 _protected member_ `FAsyncStepResult ResultPromise{};`
- L89 _protected member_ `TSharedPtr<TFuture<bool>> FuturePtr{};`

#### Free symbols / members of external scopes

- L43 _typedef_ `using FAsyncStepResult = TSharedPtr<TestSafePromiseDeleter>;`
- L69 _function_ `` (scope `FAsyncTestStep::Tick`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/AuthAutoLogin.h` (Public)


#### struct `FAuthAutoLoginStep`  
`struct FAuthAutoLoginStep : public FAsyncTestStep`  
_L18-57_
- inherits: `FAsyncTestStep`
- L20 _public function_ `FAuthAutoLoginStep(int32 inLocalUserNum) : LocalUserNum(inLocalUserNum)`
- L25 _public function_ `virtual ~FAuthAutoLoginStep()`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L56 _protected member_ `int32 LocalUserNum = 0;`

#### Free symbols / members of external scopes

- L47 _function_ `.OnComplete([this, Promise = MoveTemp(Promise)](const TOnlineResult<UE::Online::FAuthLogin>& Result) { CHECK_OP(Result); Promise->SetValue(true); });` (scope `FAuthAutoLoginStep::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Achievements/CheckAchievementStateHelper.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)
- L9 _function_ `inline void CheckAchievementState_Fixture(const FAsyncLambdaResult& Promise, const IOnlineServicesPtr& Services, const FAccountId& AccountId, const FString& AchievementId, float AchievementProgress)` (scope `UE::Online`)
- L13 _function_ `` (scope `UE::Online::CheckAchievementState_Fixture`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Achievements/QueryAchievementDefinitionsHelper.h` (Public)


#### struct `FQueryAchievementDefinitionsHelper`  
`struct FQueryAchievementDefinitionsHelper : public FTestPipeline::FStep`  
_L12-68_
- inherits: `FTestPipeline::FStep`
- L14 _public typedef_ `using ParamsType = UE::Online::FQueryAchievementDefinitions::Params;`
- L15 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FQueryAchievementDefinitions>;`
- L23 _public function_ `FQueryAchievementDefinitionsHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L28 _public prototype_ `virtual ~FQueryAchievementDefinitionsHelper() = default;`
- L30 _public member_ `enum class EState { Init, Called, Done } State = EState::Init;`
- L32 _public function_ `virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override`
- L65 _protected member_ `FHelperParams HelperParams;`
- L67 _protected member_ `UE::Online::IAchievementsPtr AchievementsInterface = nullptr;`

#### struct `FQueryAchievementDefinitionsHelper::FHelperParams`  
`struct FHelperParams`  
_L17-21_
- L19 _public member_ `ParamsType OpParams;`
- L20 _public member_ `TOptional<ResultType> ExpectedError;`

#### enum `FQueryAchievementDefinitionsHelper::EState`  
`enum class EState`  
_L30-30_
- L30 _public enumerator_ `enum class EState { Init, Called, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L30 _public enumerator_ `enum class EState { Init, Called, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L30 _public enumerator_ `enum class EState { Init, Called, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`

#### Free symbols / members of external scopes

- L44 _function_ `` (scope `FQueryAchievementDefinitionsHelper::Tick`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Achievements/QueryAchievementStatesHelper.h` (Public)


#### struct `FQueryAchievementStatesHelper`  
`struct FQueryAchievementStatesHelper : public FTestPipeline::FStep`  
_L13-70_
- inherits: `FTestPipeline::FStep`
- L15 _public typedef_ `using ParamsType = UE::Online::FQueryAchievementStates::Params;`
- L16 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FQueryAchievementStates>;`
- L24 _public function_ `FQueryAchievementStatesHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L30 _public prototype_ `virtual ~FQueryAchievementStatesHelper() = default;`
- L32 _public member_ `enum class EState { Init, Called, Done } State = EState::Init;`
- L34 _public function_ `virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override`
- L67 _protected member_ `FHelperParams HelperParams;`
- L69 _protected member_ `UE::Online::IAchievementsPtr AchievementsInterface = nullptr;`

#### struct `FQueryAchievementStatesHelper::FHelperParams`  
`struct FHelperParams`  
_L18-22_
- L20 _public member_ `ParamsType OpParams;`
- L21 _public member_ `TOptional<ResultType> ExpectedError;`

#### enum `FQueryAchievementStatesHelper::EState`  
`enum class EState`  
_L32-32_
- L32 _public enumerator_ `enum class EState { Init, Called, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L32 _public enumerator_ `enum class EState { Init, Called, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L32 _public enumerator_ `enum class EState { Init, Called, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`

#### Free symbols / members of external scopes

- L46 _function_ `` (scope `FQueryAchievementStatesHelper::Tick`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Achievements/UnlockAchievementsHelper.h` (Public)


#### struct `FUnlockAchievementsHelper`  
`struct FUnlockAchievementsHelper : public FTestPipeline::FStep`  
_L12-103_
- inherits: `FTestPipeline::FStep`
- L14 _public typedef_ `using ParamsType = UE::Online::FUnlockAchievements::Params;`
- L15 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FUnlockAchievements>;`
- L23 _public function_ `FUnlockAchievementsHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L29 _public prototype_ `virtual ~FUnlockAchievementsHelper() = default;`
- L31 _public member_ `enum class EState { Init, Called, AwaitEvent, Done } State = EState::Init;`
- L33 _public function_ `virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override`
- L88 _public function_ `void OnAchievementStateUpdated(const UE::Online::FAchievementStateUpdated& EventParams)`
- L96 _protected member_ `FHelperParams HelperParams;`
- L98 _protected member_ `UE::Online::FAchievementStateUpdated ExpectedEventParams;`
- L99 _protected member_ `UE::Online::FOnlineEventDelegateHandle EventHandle;`
- L100 _protected member_ `bool bEventFired = false;`
- L102 _protected member_ `UE::Online::IAchievementsPtr AchievementsInterface = nullptr;`

#### struct `FUnlockAchievementsHelper::FHelperParams`  
`struct FHelperParams`  
_L17-21_
- L19 _public member_ `ParamsType OpParams;`
- L20 _public member_ `TOptional<ResultType> ExpectedError;`

#### enum `FUnlockAchievementsHelper::EState`  
`enum class EState`  
_L31-31_
- L31 _public enumerator_ `enum class EState { Init, Called, AwaitEvent, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L31 _public enumerator_ `enum class EState { Init, Called, AwaitEvent, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L31 _public enumerator_ `enum class EState { Init, Called, AwaitEvent, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L31 _public enumerator_ `enum class EState { Init, Called, AwaitEvent, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`

#### Free symbols / members of external scopes

- L50 _function_ `` (scope `FUnlockAchievementsHelper::Tick`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Auth/AuthLogin.h` (Public)


#### struct `FAuthLoginStep`  
`struct FAuthLoginStep : public FAsyncTestStep`  
_L15-62_
- inherits: `FAsyncTestStep`
- L17 _public function_ `FAuthLoginStep(UE::Online::FAuthLogin::Params&& InLocalAccount) : LocalAccount(MoveTemp(InLocalAccount))`
- L22 _public prototype_ `virtual ~FAuthLoginStep() = default;`
- L24 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L59 _protected member_ `int32 LocalUserNum = 0;`
- L60 _protected member_ `UE::Online::FAuthLogin::Params LocalAccount;`
- L61 _protected member_ `UE::Online::IAuthPtr OnlineAuthPtr = nullptr;`

#### Free symbols / members of external scopes

- L40 _function_ `` (scope `FAuthLoginStep::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Auth/AuthLogout.h` (Public)


#### struct `FAuthLogoutStep`  
`struct FAuthLogoutStep : public FAsyncTestStep`  
_L15-60_
- inherits: `FAsyncTestStep`
- L17 _public function_ `FAuthLogoutStep(FPlatformUserId InPlatformUserId) : PlatformUserId(InPlatformUserId)`
- L21 _public function_ `FAuthLogoutStep(TSharedPtr<FPlatformUserId>&& InPlatformUserIdPtr) : PlatformUserIdPtr(MoveTemp(InPlatformUserIdPtr))`
- L26 _public prototype_ `virtual ~FAuthLogoutStep() = default;`
- L28 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L57 _protected member_ `TSharedPtr<FPlatformUserId> PlatformUserIdPtr = nullptr;`
- L58 _protected member_ `FPlatformUserId PlatformUserId;`
- L59 _protected member_ `UE::Online::IAuthPtr OnlineAuthPtr = nullptr;`

#### Free symbols / members of external scopes

- L46 _function_ `` (scope `FAuthLogoutStep::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Auth/AuthQueryExternalAuthToken.h` (Public)


#### struct `FAuthQueryExternalAuthTokenStep`  
`struct FAuthQueryExternalAuthTokenStep : public FAsyncTestStep`  
_L18-54_
- inherits: `FAsyncTestStep`
- L20 _public function_ `FAuthQueryExternalAuthTokenStep(UE::Online::FAuthQueryExternalAuthToken::Params&& InQueryParams) : QueryParams(MoveTemp(InQueryParams))`
- L25 _public function_ `virtual ~FAuthQueryExternalAuthTokenStep()`
- L33 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L51 _protected member_ `int32 LocalUserNum = 0;`
- L52 _protected member_ `UE::Online::FAuthQueryExternalAuthToken::Params QueryParams;`
- L53 _protected member_ `UE::Online::IAuthPtr OnlineAuthPtr = nullptr;`

#### Free symbols / members of external scopes

- L40 _function_ `` (scope `FAuthQueryExternalAuthTokenStep::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Commerce/CheckoutHelper.h` (Public)


#### struct `FCheckoutHelper`  
`struct FCheckoutHelper : public FAsyncTestStep`  
_L9-53_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FCommerceCheckout::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<FCommerceCheckout>;`
- L20 _public function_ `FCheckoutHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FCheckoutHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L50 _protected member_ `FHelperParams HelperParams;`
- L51 _protected member_ `UE::Online::ICommercePtr CommerceInterface = nullptr;`
- L52 _protected member_ `TOptional<FString> TransactionId;`

#### struct `FCheckoutHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FCheckoutHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Commerce/GetEntitlementsHelper.h` (Public)


#### struct `FGetEntitlementsHelper`  
`struct FGetEntitlementsHelper : public FAsyncTestStep`  
_L9-57_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FCommerceGetEntitlements::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FCommerceGetEntitlements>;`
- L20 _public function_ `FGetEntitlementsHelper(FHelperParams&& InHelperParams, const TOptional<uint32_t> InExpectedEntitlementsNum = TOptional<uint32_t>()) : HelperParams(MoveTemp(InHelperParams)) , ExpectedEntitlementsNum(InExpectedEntitlementsNum)`
- L28 _public prototype_ `virtual ~FGetEntitlementsHelper() = default;`
- L30 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L53 _protected member_ `FHelperParams HelperParams;`
- L54 _protected member_ `TOptional<uint32_t> ExpectedEntitlementsNum = TOptional<uint32_t>();`
- L55 _protected member_ `UE::Online::ICommercePtr CommerceInterface = nullptr;`
- L56 _protected member_ `TArray<FEntitlement> Entitlements;`

#### struct `FGetEntitlementsHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Commerce/GetOffersByIdHelper.h` (Public)


#### struct `FGetOffersByIdHelper`  
`struct FGetOffersByIdHelper : public FAsyncTestStep`  
_L9-57_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FCommerceGetOffersById::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FCommerceGetOffersById>;`
- L20 _public function_ `FGetOffersByIdHelper(FHelperParams&& InHelperParams, const TOptional<uint32_t> InExpectedOffersNum = TOptional<uint32_t>()) : HelperParams(MoveTemp(InHelperParams)) , ExpectedOffersNum(InExpectedOffersNum)`
- L28 _public prototype_ `virtual ~FGetOffersByIdHelper() = default;`
- L30 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L53 _protected member_ `FHelperParams HelperParams;`
- L54 _protected member_ `TOptional<uint32_t> ExpectedOffersNum = TOptional<uint32_t>();`
- L55 _protected member_ `UE::Online::ICommercePtr CommerceInterface = nullptr;`
- L56 _protected member_ `TArray<FOffer> Offers;`

#### struct `FGetOffersByIdHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Commerce/GetOffersHelper.h` (Public)


#### struct `FGetOffersHelper`  
`struct FGetOffersHelper : public FAsyncTestStep`  
_L9-57_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FCommerceGetOffers::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FCommerceGetOffers>;`
- L20 _public function_ `FGetOffersHelper(FHelperParams&& InHelperParams, const TOptional<uint32_t> InExpectedOffersNum = TOptional<uint32_t>()) : HelperParams(MoveTemp(InHelperParams)) , ExpectedOffersNum(InExpectedOffersNum)`
- L28 _public prototype_ `virtual ~FGetOffersHelper() = default;`
- L30 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L53 _protected member_ `FHelperParams HelperParams;`
- L54 _protected member_ `TOptional<uint32_t> ExpectedOffersNum = TOptional<uint32_t>();`
- L55 _protected member_ `UE::Online::ICommercePtr CommerceInterface = nullptr;`
- L56 _protected member_ `TArray<FOffer> Offers;`

#### struct `FGetOffersHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Commerce/QueryEntitlementsHelper.h` (Public)


#### struct `FQueryEntitlementsHelper`  
`struct FQueryEntitlementsHelper : public FAsyncTestStep`  
_L9-52_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FCommerceQueryEntitlements::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FCommerceQueryEntitlements>;`
- L20 _public function_ `FQueryEntitlementsHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FQueryEntitlementsHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L50 _protected member_ `FHelperParams HelperParams;`
- L51 _protected member_ `UE::Online::ICommercePtr CommerceInterface = nullptr;`

#### struct `FQueryEntitlementsHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FQueryEntitlementsHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Commerce/QueryOffersByIdHelper.h` (Public)


#### struct `FQueryOffersByIdHelper`  
`struct FQueryOffersByIdHelper : public FAsyncTestStep`  
_L9-52_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FCommerceQueryOffersById::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FCommerceQueryOffersById>;`
- L20 _public function_ `FQueryOffersByIdHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FQueryOffersByIdHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L50 _protected member_ `FHelperParams HelperParams;`
- L51 _protected member_ `UE::Online::ICommercePtr CommerceInterface = nullptr;`

#### struct `FQueryOffersByIdHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FQueryOffersByIdHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Commerce/QueryOffersHelper.h` (Public)


#### struct `FQueryOffersHelper`  
`struct FQueryOffersHelper : public FAsyncTestStep`  
_L9-52_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FCommerceQueryOffers::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FCommerceQueryOffers>;`
- L20 _public function_ `FQueryOffersHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FQueryOffersHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L50 _protected member_ `FHelperParams HelperParams;`
- L51 _protected member_ `UE::Online::ICommercePtr CommerceInterface = nullptr;`

#### struct `FQueryOffersHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FQueryOffersHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Commerce/RedeemEntitlementsHelper.h` (Public)


#### struct `FRedeemEntitlementsHelper`  
`struct FRedeemEntitlementsHelper : public FAsyncTestStep`  
_L10-66_
- inherits: `FAsyncTestStep`
- L12 _public typedef_ `using ParamsType = UE::Online::FCommerceRedeemEntitlement::Params;`
- L13 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FCommerceRedeemEntitlement>;`
- L21 _public function_ `FRedeemEntitlementsHelper(FHelperParams&& InHelperParams, TSharedPtr<FString> InEntitlementId) : HelperParams(MoveTemp(InHelperParams)) , EntitlementId(InEntitlementId)`
- L29 _public prototype_ `virtual ~FRedeemEntitlementsHelper() = default;`
- L31 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L63 _protected member_ `FHelperParams HelperParams;`
- L64 _protected member_ `TSharedPtr<FString> EntitlementId;`
- L65 _protected member_ `UE::Online::ICommercePtr CommerceInterface = nullptr;`

#### struct `FRedeemEntitlementsHelper::FHelperParams`  
`struct FHelperParams`  
_L15-19_
- L17 _public member_ `ParamsType* OpParams = nullptr;`
- L18 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L42 _function_ `` (scope `FRedeemEntitlementsHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Identity/IdentityGetLoginByUserId.h` (Public)


#### struct `FIdentityGetUniquePlayerIdStep`  
`struct FIdentityGetUniquePlayerIdStep : public FTestPipeline::FStep`  
_L16-46_
- inherits: `FTestPipeline::FStep`
- L18 _public function_ `FIdentityGetUniquePlayerIdStep(int32 InLocalUserNum, TFunction<void(UE::Online::FAccountInfo)>&& InStateSaver) : LocalUserNum(InLocalUserNum) , StateSaver(MoveTemp(InStateSaver))`
- L23 _public function_ `FIdentityGetUniquePlayerIdStep(int32 InLocalUserNum) : LocalUserNum(InLocalUserNum) , StateSaver([](UE::Online::FAccountInfo) {})`
- L25 _public function_ `, StateSaver([](UE::Online::FAccountInfo) {})`
- L28 _public prototype_ `virtual ~FIdentityGetUniquePlayerIdStep() = default;`
- L30 _public function_ `virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override`
- L44 _protected member_ `int32 LocalUserNum = 0;`
- L45 _protected member_ `TFunction<void(UE::Online::FAccountInfo)> StateSaver;`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/LambdaStep.h` (Public)


#### struct `FLambdaStep`  
`struct FLambdaStep : public FTestPipeline::FStep`  
_L6-23_
- inherits: `FTestPipeline::FStep`
- L8 _public function_ `FLambdaStep(TFunction<void(IOnlineServicesPtr)>&& InFunction) : Function(MoveTemp(InFunction))`
- L13 _public prototype_ `virtual ~FLambdaStep() = default;`
- L15 _public function_ `virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override`
- L22 _protected member_ `TFunction<void(IOnlineServicesPtr)> Function;`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Lobby/LobbyCreateHelper.h` (Public)


#### struct `FLobbyCreateHelper`  
`struct FLobbyCreateHelper : public FTestPipeline::FStep`  
_L13-89_
- inherits: `FTestPipeline::FStep`
- L15 _public function_ `FLobbyCreateHelper(UE::Online::FCreateLobby::Params* Params,const bool& bShouldPass = true) : CreateParams(Params) , bShouldPass(bShouldPass)`
- L20 _public function_ `FLobbyCreateHelper(UE::Online::FCreateLobby::Params* Params, TFunction<void(UE::Online::FLobby)>&& LobbyGetter, const bool& bShouldPass = true) : CreateParams(Params) , LobbyGetter(MoveTemp(LobbyGetter)) , bShouldPass(bShouldPass)`
- L27 _public prototype_ `virtual ~FLobbyCreateHelper() = default;`
- L29 _public member_ `enum class EState { Init, CreateLobbyCalled, CreateLobbyInProgress, CreateLobbyComplete, Done } State = EState::Init;`
- L31 _public function_ `virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override`
- L83 _protected member_ `UE::Online::FCreateLobby::Params* CreateParams;`
- L84 _protected member_ `TFunction<void(UE::Online::FLobby)> LobbyGetter;`
- L85 _protected member_ `bool bShouldPass;`
- L87 _protected member_ `UE::Online::ILobbiesPtr OnlineLobbiesPtr = nullptr;`

#### enum `FLobbyCreateHelper::EState`  
`enum class EState`  
_L29-29_
- L29 _public enumerator_ `enum class EState { Init, CreateLobbyCalled, CreateLobbyInProgress, CreateLobbyComplete, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L29 _public enumerator_ `enum class EState { Init, CreateLobbyCalled, CreateLobbyInProgress, CreateLobbyComplete, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L29 _public enumerator_ `enum class EState { Init, CreateLobbyCalled, CreateLobbyInProgress, CreateLobbyComplete, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L29 _public enumerator_ `enum class EState { Init, CreateLobbyCalled, CreateLobbyInProgress, CreateLobbyComplete, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L29 _public enumerator_ `enum class EState { Init, CreateLobbyCalled, CreateLobbyInProgress, CreateLobbyComplete, Done } State = EState::Init; virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override { switch (State) { case EState::Init: {`

#### Free symbols / members of external scopes

- L45 _function_ `` (scope `FLobbyCreateHelper::Tick`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Lobby/LobbyJoinHelper.h` (Public)


#### struct `FLobbyJoinHelper`  
`struct FLobbyJoinHelper : public FAsyncTestStep`  
_L16-65_
- inherits: `FAsyncTestStep`
- L18 _public typedef_ `using ParamsType = UE::Online::FJoinLobby::Params;`
- L19 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FJoinLobby>;`
- L27 _public function_ `FLobbyJoinHelper(FHelperParams&& InHelperParams, const bool& bShouldPass = true) : HelperParams(MoveTemp(InHelperParams)) ,bShouldPass(bShouldPass)`
- L35 _public prototype_ `virtual ~FLobbyJoinHelper() = default;`
- L37 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L61 _protected member_ `FHelperParams HelperParams;`
- L62 _protected member_ `bool bShouldPass;`
- L64 _protected member_ `UE::Online::ILobbiesPtr LobbyInterface = nullptr;`

#### struct `FLobbyJoinHelper::FHelperParams`  
`struct FHelperParams`  
_L21-25_
- L23 _public member_ `ParamsType* OpParams;`
- L24 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L44 _function_ `` (scope `FLobbyJoinHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/OnlineHelpers.h` (Public)


#### enum `UE::TestCommon::ESleepBehavior`  
`enum class ESleepBehavior : uint8`  
_L24-30_
- desc: Sleep behavior for BlockUntil Complete
- L27 _public enumerator_ `NoSleep` — No sleeps
- L29 _public enumerator_ `Sleep` — Sleep every tick

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TestCommon` (scope `UE`)
- L15 _variable_ `constexpr const int32 TickFrequencyMs = (1000 / 30);` (scope `UE::TestCommon`) — 30 ticks per second
- L16 _variable_ `constexpr const int32 BlockUntilCompleteDefaultMaxTicks = (1000 * 30) / TickFrequencyMs;` (scope `UE::TestCommon`) — Default timeout if 30 seconds
- L21 _prototype_ `void Tick();` (scope `UE::TestCommon`) — Tick core systems that cause functionality to progress (eg core ticker)
- L40 _function_ `template<typename ResultType> void BlockUntilComplete(TArrayView<const TFuture<ResultType>> Futures, TOptional<int32> MaxTicks = BlockUntilCompleteDefaultMaxTicks, ESleepBehavior SleepBehavior = ESleepBehavior::NoSleep)` (scope `UE::TestCommon`) — Tick core systems until a future is set, or the operation has timed out. Note: Unfulfilled promises are disastrous, so this fails the test if a timeout occurs. @param Futures futures to wait for @param MaxTicks maximum number of ticks before deciding the operation timed out. @param SleepBehavior sleep behavior while ticking
- L63 _function_ `template<typename ResultType> void BlockUntilComplete(const TArray<TFuture<ResultType>>& Futures, TOptional<int32> MaxTicks = BlockUntilCompleteDefaultMaxTicks, ESleepBehavior SleepBehavior = ESleepBehavior::NoSleep)` (scope `UE::TestCommon`) — Overload that takes a TArray of non-const futures
- L70 _function_ `template<typename ResultType> void BlockUntilComplete(const TFuture<ResultType>& Future, TOptional<int32> MaxTicks = BlockUntilCompleteDefaultMaxTicks, ESleepBehavior SleepBehavior = ESleepBehavior::NoSleep)` (scope `UE::TestCommon`) — Overload that takes a single future
- L77 _function_ `template <typename ResultType> ResultType GetFutureValueBlocking(TFuture<ResultType>& InFuture, TOptional<int32> MaxTicks = BlockUntilCompleteDefaultMaxTicks, ESleepBehavior SleepBehavior = ESleepBehavior::NoSleep)` (scope `UE::TestCommon`) — Block until a future is complete, and return its value
- L86 _function_ `template<typename OpType> [[nodiscard]] UE::Online::FOnlineError GetErrorFromResult(UE::Online::TOnlineResult<OpType>&& InResult)` (scope `UE::TestCommon`) — Overload that takes TOnlineResult
- L93 _function_ `template<typename SuccessType> [[nodiscard]] UE::Online::FOnlineError GetErrorFromResult(TValueOrError<SuccessType, UE::Online::FOnlineError>&& InResult)` (scope `UE::TestCommon`) — Overload that takes TValueOrError where Error is FOnlineError
- L99 _function_ `[[nodiscard]] inline UE::Online::FOnlineError GetErrorFromResult(UE::Online::FOnlineError&& InError)` (scope `UE::TestCommon`) — Overload that takes FOnlineError
- L109 _function_ `template<typename TResultType> void FulfillPromise(TPromise<UE::Online::FOnlineError>& InPromise, TResultType&& InResult)` (scope `UE::TestCommon`) — Fulfill a promise of type FOnlineError
- L120 _function_ `template<typename OpType> [[nodiscard]] OpType::Result GetOpResultChecked(UE::Online::TOnlineResult<OpType>&& InResult)` (scope `UE::TestCommon`) — Check that a synchronous online operation completed successfully, and return the successful result. @param InResult the result @return the result of the op
- L133 _function_ `template<typename OpType> UE::Online::TOnlineResult<OpType> GetAsyncOpResultBlocking(UE::Online::TOnlineAsyncOpHandle<OpType> InAsyncOp, TOptional<int32> MaxTicks = BlockUntilCompleteDefaultMaxTicks, ESleepBehavior SleepBehavior = ESleepBehavior::NoSleep)` (scope `UE::TestCommon`) — Block until an async op completes. Will fail if the async op does not complete in a timely manner. @param InAsyncOp the async op to wait for @return the result of the async op
- L139 _function_ `` (scope `UE::TestCommon::GetAsyncOpResultBlocking`)
- L152 _function_ `template<typename OpType> [[nodiscard]] OpType::Result GetAsyncOpResultChecked(UE::Online::TOnlineAsyncOpHandle<OpType> InAsyncOp, TOptional<int32> MaxTicks = BlockUntilCompleteDefaultMaxTicks, ESleepBehavior SleepBehavior = ESleepBehavior::NoSleep)` (scope `UE::TestCommon`) — Block until an async op completes and returns the successful variant of the result. Will fail if the async op fails, or the async op does not complete in a timely manner. @param InAsyncOp the async op to wait for @return the result of the async op

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Presence/BatchQueryPresenceHelper.h` (Public)


#### class `FBatchQueryPresenceHelper`  
`class FBatchQueryPresenceHelper : public FAsyncTestStep`  
_L9-39_
- inherits: `FAsyncTestStep`
- L12 _public function_ `FBatchQueryPresenceHelper(FAccountId InLocalAccountId, TArray<FAccountId>& InTargetAccountIds, TArray<TSharedRef<const FUserPresence>>& InOutPresences, bool inBListenForChanges = false) : LocalAccountId(InLocalAccountId) , TargetAccountIds(InTargetAccountIds) , OutPresences(InOutPresences) , bListenForChanges(inBListenForChanges)`
- L21 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L35 _protected member_ `FAccountId LocalAccountId;`
- L36 _protected member_ `TArray<FAccountId>& TargetAccountIds;`
- L37 _protected member_ `TArray<TSharedRef<const FUserPresence>>& OutPresences;`
- L38 _protected member_ `bool bListenForChanges;`

#### Free symbols / members of external scopes

- L27 _function_ `` (scope `FBatchQueryPresenceHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Presence/CommonPresenceHelpers.h` (Public)


#### class `FComparePresencesHelper`  
`class FComparePresencesHelper : public FAsyncTestStep`  
_L95-129_
- inherits: `FAsyncTestStep`
- desc: Presence2 is static because this is intended for the first passed in presence to be something queried and the second value to be the static presence taht it is expected to be
- L98 _public function_ `FComparePresencesHelper(TSharedPtr<const FUserPresence>& InPresence1, TSharedRef<const FUserPresence> InPresence2, bool inBShouldBeEqual = true) : Presence1(InPresence1) , Presence2(InPresence2) , bShouldBeEqual(inBShouldBeEqual)`
- L106 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L126 _protected member_ `TSharedPtr<const FUserPresence>& Presence1;`
- L127 _protected member_ `TSharedRef<const FUserPresence> Presence2;`
- L128 _protected member_ `bool bShouldBeEqual;`

#### Free symbols / members of external scopes

- L8 _function_ `inline TSharedRef<FUserPresence> GetGenericPresenceA(FAccountId AccountId)`
- L23 _function_ `inline TSharedRef<FUserPresence> GetGenericPresenceB(FAccountId AccountId)`
- L38 _function_ `inline FPartialUpdatePresence::Params GetGenericPresenceMutationAtoB(FAccountId AccountId)`
- L54 _function_ `inline void CheckPresenceAreEqual(const FUserPresence& Presence1, const FUserPresence& Presence2)`
- L76 _function_ `inline void CheckPresencesNotEqual(const FUserPresence& Presence1, const FUserPresence& Presence2)` — don't check user ids here- may be used to check for an update on a specific user

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Presence/GetCachedPresenceHelper.h` (Public)


#### class `FGetCachedPresenceHelper`  
`class FGetCachedPresenceHelper : public FAsyncTestStep`  
_L8-40_
- inherits: `FAsyncTestStep`
- L11 _public function_ `FGetCachedPresenceHelper(FAccountId InLocalAccountId, FAccountId InTargetAccountId, TSharedPtr<const FUserPresence>& InOutPresence) : LocalAccountId(InLocalAccountId) , TargetAccountId(InTargetAccountId) , OutPresence(InOutPresence)`
- L20 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L37 _protected member_ `FAccountId LocalAccountId;`
- L38 _protected member_ `FAccountId TargetAccountId;`
- L39 _protected member_ `TSharedPtr<const FUserPresence>& OutPresence;`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Presence/PartialUpdatePresenceHelper.h` (Public)


#### class `FPartialUpdatePresenceHelper`  
`class FPartialUpdatePresenceHelper : public FAsyncTestStep`  
_L9-32_
- inherits: `FAsyncTestStep`
- L12 _public function_ `FPartialUpdatePresenceHelper(FPartialUpdatePresence::Params&& InParams) : Params(MoveTemp(InParams))`
- L18 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L31 _protected member_ `FPartialUpdatePresence::Params Params;`

#### Free symbols / members of external scopes

- L24 _function_ `` (scope `FPartialUpdatePresenceHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Presence/QueryPresenceHelper.h` (Public)


#### class `FQueryPresenceHelper`  
`class FQueryPresenceHelper : public FAsyncTestStep`  
_L9-41_
- inherits: `FAsyncTestStep`
- L12 _public function_ `FQueryPresenceHelper(FAccountId InLocalAccountId, FAccountId InTargetAccountId, TSharedPtr<const FUserPresence>& InOutPresence, bool inBListenToChanges = false) : LocalAccountId(InLocalAccountId) , TargetAccountId(InTargetAccountId) , OutPresence(InOutPresence) , bListenToChanges(inBListenToChanges)`
- L21 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L37 _protected member_ `FAccountId LocalAccountId;`
- L38 _protected member_ `FAccountId TargetAccountId;`
- L39 _protected member_ `TSharedPtr<const FUserPresence>& OutPresence;`
- L40 _protected member_ `bool bListenToChanges;`

#### Free symbols / members of external scopes

- L26 _function_ `` (scope `FQueryPresenceHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Presence/UpdatePresenceHelper.h` (Public)


#### class `FUpdatePresenceHelper`  
`class FUpdatePresenceHelper : public FAsyncTestStep`  
_L9-33_
- inherits: `FAsyncTestStep`
- L12 _public function_ `FUpdatePresenceHelper(FAccountId InLocalAccountId, TSharedRef<FUserPresence> InPresence) : LocalAccountId(InLocalAccountId) , Presence(InPresence)`
- L19 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L31 _protected member_ `FAccountId LocalAccountId;`
- L32 _protected member_ `TSharedRef<FUserPresence> Presence;`

#### Free symbols / members of external scopes

- L24 _function_ `` (scope `FUpdatePresenceHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Sessions/AddRemoveSessionMemberHelper.h` (Public)


#### struct `FAddSessionMemberHelper`  
`struct FAddSessionMemberHelper : public FAsyncTestStep`  
_L9-56_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FAddSessionMember::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FAddSessionMember>;`
- L20 _public function_ `FAddSessionMemberHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FAddSessionMemberHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L53 _protected member_ `FHelperParams HelperParams;`
- L54 _protected member_ `UE::Online::ISessionsPtr SessionsInterface = nullptr;`

#### struct `FAddSessionMemberHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### struct `FRemoveSessionMemberHelper`  
`struct FRemoveSessionMemberHelper : public FAsyncTestStep`  
_L58-105_
- inherits: `FAsyncTestStep`
- L60 _public typedef_ `using ParamsType = UE::Online::FRemoveSessionMember::Params;`
- L61 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FRemoveSessionMember>;`
- L69 _public function_ `FRemoveSessionMemberHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L76 _public prototype_ `virtual ~FRemoveSessionMemberHelper() = default;`
- L78 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L102 _protected member_ `FHelperParams HelperParams;`
- L103 _protected member_ `UE::Online::ISessionsPtr SessionsInterface = nullptr;`

#### struct `FRemoveSessionMemberHelper::FHelperParams`  
`struct FHelperParams`  
_L63-67_
- L65 _public member_ `ParamsType* OpParams = nullptr;`
- L66 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FAddSessionMemberHelper::Run`)
- L85 _function_ `` (scope `FRemoveSessionMemberHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Sessions/CreateSessionHelper.h` (Public)


#### struct `FCreateSessionHelper`  
`struct FCreateSessionHelper : public FAsyncTestStep`  
_L8-54_
- inherits: `FAsyncTestStep`
- L10 _public typedef_ `using ParamsType = UE::Online::FCreateSession::Params;`
- L11 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FCreateSession>;`
- L19 _public function_ `FCreateSessionHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L26 _public prototype_ `virtual ~FCreateSessionHelper() = default;`
- L28 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L51 _protected member_ `FHelperParams HelperParams;`
- L52 _protected member_ `UE::Online::ISessionsPtr SessionsInterface = nullptr;`

#### struct `FCreateSessionHelper::FHelperParams`  
`struct FHelperParams`  
_L13-17_
- L15 _public member_ `ParamsType* OpParams = nullptr;`
- L16 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L35 _function_ `` (scope `FCreateSessionHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Sessions/FindSessionsHelper.h` (Public)


#### struct `FFindSessionsHelper`  
`struct FFindSessionsHelper : public FAsyncTestStep`  
_L9-82_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FFindSessions::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FFindSessions>;`
- L20 _public function_ `FFindSessionsHelper(FHelperParams&& InHelperParams, const TOptional<uint32_t> InExpecetedSessionsFound = TOptional<uint32_t>(), TFunction<void()>&& InLogPrinter = []() {}) : HelperParams(MoveTemp(InHelperParams)) , ExpecetedSessionsFound(InExpecetedSessionsFound) , LogPrinter(InLogPrinter)`
- L20 _public function_ `FFindSessionsHelper(FHelperParams&& InHelperParams, const TOptional<uint32_t> InExpecetedSessionsFound = TOptional<uint32_t>(), TFunction<void()>&& InLogPrinter = []() {}) : HelperParams(MoveTemp(InHelperParams)) , ExpecetedSessionsFound(InExpecetedSessionsFound) , LogPrinter(InLogPrinter)`
- L29 _public prototype_ `virtual ~FFindSessionsHelper() = default;`
- L31 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L78 _protected member_ `FHelperParams HelperParams;`
- L79 _protected member_ `UE::Online::ISessionsPtr SessionsInterface = nullptr;`
- L80 _protected member_ `TOptional<uint32_t> ExpecetedSessionsFound = TOptional<uint32_t>();`
- L81 _protected member_ `TFunction<void()> LogPrinter;`

#### struct `FFindSessionsHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L38 _function_ `` (scope `FFindSessionsHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Sessions/JoinSessionHelper.h` (Public)


#### struct `FJoinSessionHelper`  
`struct FJoinSessionHelper : public FAsyncTestStep`  
_L9-56_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FJoinSession::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FJoinSession>;`
- L20 _public function_ `FJoinSessionHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FJoinSessionHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L53 _protected member_ `FHelperParams HelperParams;`
- L54 _protected member_ `UE::Online::ISessionsPtr SessionsInterface = nullptr;`

#### struct `FJoinSessionHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FJoinSessionHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Sessions/LeaveSessionHelper.h` (Public)


#### struct `FLeaveSessionHelper`  
`struct FLeaveSessionHelper : public FAsyncTestStep`  
_L9-56_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FLeaveSession::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FLeaveSession>;`
- L20 _public function_ `FLeaveSessionHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FLeaveSessionHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L53 _protected member_ `FHelperParams HelperParams;`
- L54 _protected member_ `UE::Online::ISessionsPtr SessionsInterface = nullptr;`

#### struct `FLeaveSessionHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FLeaveSessionHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Sessions/SendRejectSessionInviteHelper.h` (Public)


#### struct `FSendSessionInviteHelper`  
`struct FSendSessionInviteHelper : public FAsyncTestStep`  
_L9-68_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FSendSessionInvite::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FSendSessionInvite>;`
- L20 _public function_ `FSendSessionInviteHelper(FHelperParams&& InHelperParams, TFunction<void(const UE::Online::FSessionInviteId&)>&& InStateSaver = [](const UE::Online::FSessionInviteId&) {}) : HelperParams(MoveTemp(InHelperParams)) , StateSaver(InStateSaver)`
- L20 _public function_ `FSendSessionInviteHelper(FHelperParams&& InHelperParams, TFunction<void(const UE::Online::FSessionInviteId&)>&& InStateSaver = [](const UE::Online::FSessionInviteId&) {}) : HelperParams(MoveTemp(InHelperParams)) , StateSaver(InStateSaver)`
- L28 _public function_ `virtual ~FSendSessionInviteHelper()`
- L33 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L64 _protected member_ `FHelperParams HelperParams;`
- L65 _protected member_ `UE::Online::ISessionsPtr SessionsInterface = nullptr;`
- L66 _protected member_ `TFunction<void(const UE::Online::FSessionInviteId&)> StateSaver;`
- L67 _protected member_ `UE::Online::FOnlineEventDelegateHandle SessionsInviteReceivedHandle;`

#### struct `FSendSessionInviteHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### struct `FRejectSessionInviteHelper`  
`struct FRejectSessionInviteHelper : public FAsyncTestStep`  
_L70-116_
- inherits: `FAsyncTestStep`
- L72 _public typedef_ `using ParamsType = UE::Online::FRejectSessionInvite::Params;`
- L73 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FRejectSessionInvite>;`
- L81 _public function_ `FRejectSessionInviteHelper(FHelperParams&& InHelperParams, TFunction<void(const UE::Online::FSessionInviteId&)>&& InStateSaver = [](const UE::Online::FSessionInviteId&) {}) : HelperParams(MoveTemp(InHelperParams))`
- L81 _public function_ `FRejectSessionInviteHelper(FHelperParams&& InHelperParams, TFunction<void(const UE::Online::FSessionInviteId&)>&& InStateSaver = [](const UE::Online::FSessionInviteId&) {}) : HelperParams(MoveTemp(InHelperParams))`
- L88 _public prototype_ `virtual ~FRejectSessionInviteHelper() = default;`
- L90 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L114 _protected member_ `FHelperParams HelperParams;`
- L115 _protected member_ `UE::Online::ISessionsPtr SessionsInterface = nullptr;`

#### struct `FRejectSessionInviteHelper::FHelperParams`  
`struct FHelperParams`  
_L75-79_
- L77 _public member_ `ParamsType* OpParams = nullptr;`
- L78 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L40 _function_ `` (scope `FSendSessionInviteHelper::Run`)
- L97 _function_ `` (scope `FRejectSessionInviteHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Sessions/StartMatchmakingSessionHelper.h` (Public)


#### struct `FStartMatchmakingHelper`  
`struct FStartMatchmakingHelper : public FAsyncTestStep`  
_L9-55_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FStartMatchmaking::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FStartMatchmaking>;`
- L20 _public function_ `FStartMatchmakingHelper(FHelperParams&& InHelperParams, TFunction<void(const UE::Online::FSessionInviteId&)>&& InStateSaver = [](const UE::Online::FSessionInviteId&) {}) : HelperParams(MoveTemp(InHelperParams))`
- L20 _public function_ `FStartMatchmakingHelper(FHelperParams&& InHelperParams, TFunction<void(const UE::Online::FSessionInviteId&)>&& InStateSaver = [](const UE::Online::FSessionInviteId&) {}) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FStartMatchmakingHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L53 _protected member_ `FHelperParams HelperParams;`
- L54 _protected member_ `UE::Online::ISessionsPtr SessionsInterface = nullptr;`

#### struct `FStartMatchmakingHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FStartMatchmakingHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Sessions/UpdateSessionSettingsHelper.h` (Public)


#### struct `FUpdateSessionSettingsHelper`  
`struct FUpdateSessionSettingsHelper : public FAsyncTestStep`  
_L9-56_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FUpdateSessionSettings::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FUpdateSessionSettings>;`
- L20 _public function_ `FUpdateSessionSettingsHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FUpdateSessionSettingsHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L53 _protected member_ `FHelperParams HelperParams;`
- L54 _protected member_ `UE::Online::ISessionsPtr SessionsInterface = nullptr;`

#### struct `FUpdateSessionSettingsHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FUpdateSessionSettingsHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Social/AcceptFriendInviteHelper.h` (Public)


#### struct `FAcceptFriendInviteHelper`  
`struct FAcceptFriendInviteHelper : public FAsyncTestStep`  
_L9-52_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FAcceptFriendInvite::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FAcceptFriendInvite>;`
- L20 _public function_ `FAcceptFriendInviteHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FAcceptFriendInviteHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L50 _protected member_ `FHelperParams HelperParams;`
- L51 _protected member_ `UE::Online::ISocialPtr SocialInterface = nullptr;`

#### struct `FAcceptFriendInviteHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FAcceptFriendInviteHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Social/BlockUserHelper.h` (Public)


#### struct `FBlockUserHelper`  
`struct FBlockUserHelper : public FAsyncTestStep`  
_L9-52_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FBlockUser::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FBlockUser>;`
- L20 _public function_ `FBlockUserHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FBlockUserHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L50 _protected member_ `FHelperParams HelperParams;`
- L51 _protected member_ `UE::Online::ISocialPtr SocialInterface = nullptr;`

#### struct `FBlockUserHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FBlockUserHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Social/GetBlockedUsersHelper.h` (Public)


#### struct `FGetBlockedUsersHelper`  
`struct FGetBlockedUsersHelper : public FAsyncTestStep`  
_L9-56_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FGetBlockedUsers::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FGetBlockedUsers>;`
- L20 _public function_ `FGetBlockedUsersHelper(FHelperParams&& InHelperParams, const TOptional<uint32_t> InExpectedBlockedUsersNum = TOptional<uint32_t>()) : HelperParams(MoveTemp(InHelperParams)) , ExpectedBlockedUsersNum(InExpectedBlockedUsersNum)`
- L28 _public prototype_ `virtual ~FGetBlockedUsersHelper() = default;`
- L30 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L53 _protected member_ `FHelperParams HelperParams;`
- L54 _protected member_ `TOptional<uint32_t> ExpectedBlockedUsersNum = TOptional<uint32_t>();`
- L55 _protected member_ `UE::Online::ISocialPtr SocialInterface = nullptr;`

#### struct `FGetBlockedUsersHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Social/GetFriendsHelper.h` (Public)


#### struct `FGetFriendsHelper`  
`struct FGetFriendsHelper : public FAsyncTestStep`  
_L9-56_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FGetFriends::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FGetFriends>;`
- L20 _public function_ `FGetFriendsHelper(FHelperParams&& InHelperParams, const TOptional<uint32_t> InExpectedFriendsNum = TOptional<uint32_t>()) : HelperParams(MoveTemp(InHelperParams)) , ExpectedFriendsNum(InExpectedFriendsNum)`
- L28 _public prototype_ `virtual ~FGetFriendsHelper() = default;`
- L30 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L53 _protected member_ `FHelperParams HelperParams;`
- L54 _protected member_ `TOptional<uint32_t> ExpectedFriendsNum = TOptional<uint32_t>();`
- L55 _protected member_ `UE::Online::ISocialPtr SocialInterface = nullptr;`

#### struct `FGetFriendsHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Social/QueryBlockedUsersHelper.h` (Public)


#### struct `FQueryBlockedUsersHelper`  
`struct FQueryBlockedUsersHelper : public FAsyncTestStep`  
_L9-52_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FQueryBlockedUsers::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FQueryBlockedUsers>;`
- L20 _public function_ `FQueryBlockedUsersHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FQueryBlockedUsersHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L50 _protected member_ `FHelperParams HelperParams;`
- L51 _protected member_ `UE::Online::ISocialPtr SocialInterface = nullptr;`

#### struct `FQueryBlockedUsersHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FQueryBlockedUsersHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Social/QueryFriendsHelper.h` (Public)


#### struct `FQueryFriendsHelper`  
`struct FQueryFriendsHelper : public FAsyncTestStep`  
_L9-52_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FQueryFriends::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FQueryFriends>;`
- L20 _public function_ `FQueryFriendsHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FQueryFriendsHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L50 _protected member_ `FHelperParams HelperParams;`
- L51 _protected member_ `UE::Online::ISocialPtr SocialInterface = nullptr;`

#### struct `FQueryFriendsHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FQueryFriendsHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Social/RejectFriendInviteHelper.h` (Public)


#### struct `FRejectFriendInviteHelper`  
`struct FRejectFriendInviteHelper : public FAsyncTestStep`  
_L9-52_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FRejectFriendInvite::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FRejectFriendInvite>;`
- L20 _public function_ `FRejectFriendInviteHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FRejectFriendInviteHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L50 _protected member_ `FHelperParams HelperParams;`
- L51 _protected member_ `UE::Online::ISocialPtr SocialInterface = nullptr;`

#### struct `FRejectFriendInviteHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FRejectFriendInviteHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Social/SendFriendInviteHelper.h` (Public)


#### struct `FSendFriendInviteHelper`  
`struct FSendFriendInviteHelper : public FAsyncTestStep`  
_L9-52_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FSendFriendInvite::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FSendFriendInvite>;`
- L20 _public function_ `FSendFriendInviteHelper(FHelperParams&& InHelperParams) : HelperParams(MoveTemp(InHelperParams))`
- L27 _public prototype_ `virtual ~FSendFriendInviteHelper() = default;`
- L29 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L50 _protected member_ `FHelperParams HelperParams;`
- L51 _protected member_ `UE::Online::ISocialPtr SocialInterface = nullptr;`

#### struct `FSendFriendInviteHelper::FHelperParams`  
`struct FHelperParams`  
_L14-18_
- L16 _public member_ `ParamsType* OpParams = nullptr;`
- L17 _public member_ `TOptional<ResultType> ExpectedError;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FSendFriendInviteHelper::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/Stats/UpdateStatsHelper.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)
- L10 _function_ `inline void UpdateStats_Fixture(FAsyncLambdaResult Promise, const IOnlineServicesPtr& Services, const FAccountId& AccountId, const TArray<FUserStats>& UpdateUsersStats)` (scope `UE::Online`)
- L13 _function_ `` (scope `UE::Online::UpdateStats_Fixture`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/TickForTime.h` (Public)


#### struct `FTickForTime`  
`struct FTickForTime : public FTestPipeline::FStep`  
_L7-40_
- inherits: `FTestPipeline::FStep`
- L10 _public function_ `FTickForTime(const FTimespan InTimeToWaitMilliseconds) : TimeToWaitMilliseconds(InTimeToWaitMilliseconds)`
- L15 _public function_ `virtual EContinuance Tick(const IOnlineServicesPtr& OnlineSubsystem) override`
- L34 _public prototype_ `virtual ~FTickForTime() = default;`
- L37 _protected member_ `double StartTime;`
- L38 _protected member_ `bool bHasSetStartTime = false;`
- L39 _protected member_ `FTimespan TimeToWaitMilliseconds;`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/TitleFile/AsyncTitleFileEnumerateFiles.h` (Public)


#### class `FAsyncTitleFileEnumerateFiles`  
`class FAsyncTitleFileEnumerateFiles : public FAsyncTestStep`  
_L8-50_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FTitleFileEnumerateFiles::Params;`
- L12 _public typedef_ `using OpResultType = UE::Online::FTitleFileEnumerateFiles::Result;`
- L13 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FTitleFileEnumerateFiles>;`
- L15 _public function_ `FAsyncTitleFileEnumerateFiles(ParamsType&& InParams) : Params(MoveTemp(InParams)) , ExpectedResult(OpResultType())`
- L22 _public function_ `template <typename ResultParam> FAsyncTitleFileEnumerateFiles(ParamsType&& InParams, ResultParam&& InExpectedResult) : Params(MoveTemp(InParams)) , ExpectedResult(MoveTemp(InExpectedResult))`
- L28 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L48 _protected member_ `ParamsType Params;`
- L49 _protected member_ `ResultType ExpectedResult;`

#### Free symbols / members of external scopes

- L35 _function_ `` (scope `FAsyncTitleFileEnumerateFiles::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/TitleFile/AsyncTitleFileGetEnumeratedFiles.h` (Public)


#### class `FAsyncTitleFileGetEnumeratedFiles`  
`class FAsyncTitleFileGetEnumeratedFiles : public FAsyncTestStep`  
_L7-42_
- inherits: `FAsyncTestStep`
- L10 _public typedef_ `using ParamsType = UE::Online::FTitleFileGetEnumeratedFiles::Params;`
- L11 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FTitleFileGetEnumeratedFiles>;`
- L14 _public function_ `template <typename ResultParam> FAsyncTitleFileGetEnumeratedFiles(ParamsType&& InParams, ResultParam&& InExpectedResult) : Params(MoveTemp(InParams)) , ExpectedResult(MoveTemp(InExpectedResult))`
- L20 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L40 _public member_ `ParamsType Params;`
- L41 _public member_ `ResultType ExpectedResult;`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/TitleFile/AsyncTitleFileReadFile.h` (Public)


#### class `FAsyncTitleFileReadFile`  
`class FAsyncTitleFileReadFile : public FAsyncTestStep`  
_L8-45_
- inherits: `FAsyncTestStep`
- L11 _public typedef_ `using ParamsType = UE::Online::FTitleFileReadFile::Params;`
- L12 _public typedef_ `using ResultType = UE::Online::TOnlineResult<UE::Online::FTitleFileReadFile>;`
- L15 _public function_ `template <typename ResultParam> FAsyncTitleFileReadFile(ParamsType&& InParams, ResultParam&& InExpectedResult) : Params(MoveTemp(InParams)) , ExpectedResult(MoveTemp(InExpectedResult))`
- L21 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L43 _protected member_ `ParamsType Params;`
- L44 _protected member_ `ResultType ExpectedResult;`

#### Free symbols / members of external scopes

- L28 _function_ `` (scope `FAsyncTitleFileReadFile::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/UserFile/AsyncUserFileCopyFile.h` (Public)


#### class `FAsyncUserFileCopyFile`  
`class FAsyncUserFileCopyFile : public FAsyncTestStep`  
_L7-50_
- inherits: `FAsyncTestStep`
- L10 _public typedef_ `using OpType = UE::Online::FUserFileCopyFile;`
- L11 _public typedef_ `using OpParamsType = OpType::Params;`
- L12 _public typedef_ `using OpResultType = OpType::Result;`
- L13 _public typedef_ `using OnlineResultType = UE::Online::TOnlineResult<OpType>;`
- L15 _public function_ `FAsyncUserFileCopyFile(OpParamsType&& InParams) : Params(MoveTemp(InParams)) , ExpectedResult(OpResultType())`
- L22 _public function_ `template <typename ResultParam> FAsyncUserFileCopyFile(OpParamsType&& InParams, ResultParam&& InExpectedResult) : Params(MoveTemp(InParams)) , ExpectedResult(MoveTemp(InExpectedResult))`
- L28 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L48 _protected member_ `OpParamsType Params;`
- L49 _protected member_ `OnlineResultType ExpectedResult;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FAsyncUserFileCopyFile::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/UserFile/AsyncUserFileDeleteFile.h` (Public)


#### class `FAsyncUserFileDeleteFile`  
`class FAsyncUserFileDeleteFile : public FAsyncTestStep`  
_L7-76_
- inherits: `FAsyncTestStep`
- L10 _public typedef_ `using OpType = UE::Online::FUserFileDeleteFile;`
- L11 _public typedef_ `using OpParamsType = OpType::Params;`
- L12 _public typedef_ `using OpResultType = OpType::Result;`
- L13 _public typedef_ `using OnlineResultType = UE::Online::TOnlineResult<OpType>;`
- L15 _public function_ `FAsyncUserFileDeleteFile(OpParamsType&& InParams) : Params(MoveTemp(InParams))`
- L22 _public function_ `template <typename ResultParam> FAsyncUserFileDeleteFile(OpParamsType&& InParams, ResultParam&& InExpectedResult) : Params(MoveTemp(InParams))`
- L29 _public function_ `template <typename ResultParam> FAsyncUserFileDeleteFile(OpParamsType&& InParams, TArray<ResultParam>&& InExpectedResults) : Params(MoveTemp(InParams)) , ExpectedResults(MoveTemp(InExpectedResults))`
- L35 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L74 _protected member_ `OpParamsType Params;`
- L75 _protected member_ `TArray<OnlineResultType> ExpectedResults;`

#### Free symbols / members of external scopes

- L43 _function_ `` (scope `FAsyncUserFileDeleteFile::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/UserFile/AsyncUserFileEnumerateFiles.h` (Public)


#### class `FAsyncUserFileEnumerateFiles`  
`class FAsyncUserFileEnumerateFiles : public FAsyncTestStep`  
_L9-59_
- inherits: `FAsyncTestStep`
- L12 _public typedef_ `using OpType = UE::Online::FUserFileEnumerateFiles;`
- L13 _public typedef_ `using OpParamsType = OpType::Params;`
- L14 _public typedef_ `using OpResultType = OpType::Result;`
- L15 _public typedef_ `using OnlineResultType = UE::Online::TOnlineResult<OpType>;`
- L17 _public function_ `FAsyncUserFileEnumerateFiles(OpParamsType&& InParams) : Params(MoveTemp(InParams)) , ExpectedResult(OpResultType())`
- L24 _public function_ `template <typename ResultParam> FAsyncUserFileEnumerateFiles(OpParamsType&& InParams, ResultParam&& InExpectedResult) : Params(MoveTemp(InParams)) , ExpectedResult(MoveTemp(InExpectedResult))`
- L30 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L57 _protected member_ `OpParamsType Params;`
- L58 _protected member_ `OnlineResultType ExpectedResult;`

#### Free symbols / members of external scopes

- L38 _function_ `` (scope `FAsyncUserFileEnumerateFiles::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/UserFile/AsyncUserFileGetEnumeratedFiles.h` (Public)


#### class `FAsyncUserFileGetEnumeratedFiles`  
`class FAsyncUserFileGetEnumeratedFiles : public FAsyncTestStep`  
_L7-50_
- inherits: `FAsyncTestStep`
- L10 _public typedef_ `using OpType = UE::Online::FUserFileGetEnumeratedFiles;`
- L11 _public typedef_ `using OpParamsType = OpType::Params;`
- L12 _public typedef_ `using OpResultType = OpType::Result;`
- L13 _public typedef_ `using OnlineResultType = UE::Online::TOnlineResult<OpType>;`
- L15 _public function_ `FAsyncUserFileGetEnumeratedFiles(OpParamsType&& InParams) : Params(MoveTemp(InParams)) , ExpectedResult(OpResultType())`
- L22 _public function_ `template <typename ResultParam> FAsyncUserFileGetEnumeratedFiles(OpParamsType&& InParams, ResultParam&& InExpectedResult) : Params(MoveTemp(InParams)) , ExpectedResult(MoveTemp(InExpectedResult))`
- L28 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L48 _public member_ `OpParamsType Params;`
- L49 _public member_ `OnlineResultType ExpectedResult;`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/UserFile/AsyncUserFileReadFile.h` (Public)


#### class `FAsyncUserFileReadFile`  
`class FAsyncUserFileReadFile : public FAsyncTestStep`  
_L7-54_
- inherits: `FAsyncTestStep`
- L10 _public typedef_ `using OpType = UE::Online::FUserFileReadFile;`
- L11 _public typedef_ `using OpParamsType = OpType::Params;`
- L12 _public typedef_ `using OpResultType = OpType::Result;`
- L13 _public typedef_ `using OnlineResultType = UE::Online::TOnlineResult<OpType>;`
- L15 _public function_ `FAsyncUserFileReadFile(OpParamsType&& InParams) : Params(MoveTemp(InParams)) , ExpectedResult(OpResultType())`
- L22 _public function_ `template <typename ResultParam> FAsyncUserFileReadFile(OpParamsType&& InParams, ResultParam&& InExpectedResult) : Params(MoveTemp(InParams)) , ExpectedResult(MoveTemp(InExpectedResult))`
- L28 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L52 _protected member_ `OpParamsType Params;`
- L53 _protected member_ `OnlineResultType ExpectedResult;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FAsyncUserFileReadFile::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/Helpers/UserFile/AsyncUserFileWriteFile.h` (Public)


#### class `FAsyncUserFileWriteFile`  
`class FAsyncUserFileWriteFile : public FAsyncTestStep`  
_L7-53_
- inherits: `FAsyncTestStep`
- L10 _public typedef_ `using OpType = UE::Online::FUserFileWriteFile;`
- L11 _public typedef_ `using OpParamsType = OpType::Params;`
- L12 _public typedef_ `using OpResultType = OpType::Result;`
- L13 _public typedef_ `using OnlineResultType = UE::Online::TOnlineResult<OpType>;`
- L15 _public function_ `FAsyncUserFileWriteFile(OpParamsType&& InParams) : Params(MoveTemp(InParams)) , ExpectedResult(OpResultType())`
- L22 _public function_ `template <typename ResultParam> FAsyncUserFileWriteFile(OpParamsType&& InParams, ResultParam&& InExpectedResult) : Params(MoveTemp(InParams)) , ExpectedResult(MoveTemp(InExpectedResult))`
- L28 _public function_ `virtual void Run(FAsyncStepResult Promise, const IOnlineServicesPtr& Services) override`
- L51 _protected member_ `OpParamsType Params;`
- L52 _protected member_ `OnlineResultType ExpectedResult;`

#### Free symbols / members of external scopes

- L36 _function_ `` (scope `FAsyncUserFileWriteFile::Run`)

### `Source/Programs/Online/OnlineTestsCore/Source/Public/OnlineCatchHelper.h` (Public)


#### class `OnlineTestBase`  
`class OnlineTestBase : public Catch::ITestInvoker`  
_L26-114_
- inherits: `Catch::ITestInvoker`
- L29 _public prototype_ `void ConstructInternal(FString ServiceName, UE::Online::EOnlineServices ServiceType);`
- L32 _public prototype_ `virtual ~OnlineTestBase();` — must be public so that Catch2::Detail::unique_ptr can call the destructor
- L35 _public prototype_ `static void LoadServiceModules();` — Loads all necessary services for the current test run
- L38 _public prototype_ `static void UnloadServiceModules();` — Unloads all necessary services for the current test run
- L42 _public prototype_ `static bool ReturnAccounts(int32 TestAccountIndex = -1);` — Returning accounts to the pool
- L45 _public prototype_ `FTestPipeline& GetLoginPipeline(std::initializer_list<std::reference_wrapper<FAccountId>> AccountIds) const;`
- L47 _public prototype_ `FTestPipeline& GetLoginPipeline(uint32 UserNumToLogin, std::initializer_list<std::reference_wrapper<FAccountId>> AccountIds) const;`
- L49 _public typedef_ `typedef UE::Online::FAccountId FAccountId;`
- L53 _public prototype_ `void AssignLoginUsers(int32 LocalUserId, FAccountId& OutAccountId) const;` — Attempts to assign OutAccountId to what LocalUserId is logged in as.
- L56 _public prototype_ `TArray<FString> GetExternalAuthAccountIds(int32 TestAccountIndex) const;`
- L59 _public prototype_ `FTestPipeline& GetPipeline() const;`
- L62 _protected prototype_ `OnlineTestBase();`
- L65 _protected prototype_ `bool DeleteAccounts(int32 TestAccountIndex = -1) const;` — Helper function to delete accounts from TestDataService
- L68 _protected prototype_ `void DestroyCurrentServiceModule() const;` — Helper function to destroy the current OnlineService module which stores some state that maybe needs to be reset
- L71 _protected prototype_ `bool ResetAccountStatus(int32 TestAccountIndex = -1) const;` — Proxy function to the DestroyCurrentServiceModule()
- L74 _protected prototype_ `FString GetService() const;` — Returns the name of the service we're currently testing
- L75 _protected prototype_ `UE::Online::EOnlineServices GetServiceType() const;`
- L76 _protected prototype_ `IOnlineServicesPtr GetServices() const;`
- L81 _protected prototype_ `TArray<UE::Online::FAuthLogin::Params> CustomCredentials(int32 LocalUserNum, int32 NumUsers) const;` — This will provide a parameters to pass to the OSS Auth interface.
- L85 _protected prototype_ `bool CustomResetAccounts(int32 TestAccountIndex) const;` — When called should "reset" accounts to default state for Stats, Achivements, Lobbies and other stateful interfaces to work.
- L90 _protected prototype_ `bool CustomDeleteAccounts(int32 TestAccountIndex) const;` — When called will *remove* the account from the underlying service. This is generally called to test new-user login or first-time setup. To be called rare-ly.
- L93 _protected prototype_ `TArray<UE::Online::FAuthLogin::Params> GetIniCredentials(int32 TestAccountIndex) const;`
- L95 _protected prototype_ `TArray<UE::Online::FAuthLogin::Params> GetCredentials(int32 TestAccountIndex, int32 NumUsers) const;`
- L98 _protected prototype_ `FString GetLoginCredentialCategory() const;` — Returns the ini login category name for the configured service
- L100 _protected prototype_ `void RunToCompletion(bool bLogout = true) const;`
- L103 _protected prototype_ `virtual void invoke() const override = 0;` — ITestInvoker
- L106 _private member_ `FString Tags;`
- L107 _private member_ `FString Service;`
- L108 _private member_ `UE::Online::EOnlineServices ServiceType;`
- L110 _private member_ `mutable FTestDriver Driver;` — Catch's ITestInvoker is a const interface but we'll be changing stuff (emplacing steps into the driver, setting flags, etc.) so we make these mutable
- L111 _private member_ `mutable TSharedPtr<FTestPipeline> Pipeline;`
- L112 _private member_ `mutable uint32 NumLocalUsers = -1;`
- L113 _private member_ `mutable uint32 TestAccountID = -1;`

#### class `OnlineAutoReg`  
`class OnlineAutoReg`  
_L118-165_
- L136 _public prototype_ `static bool CheckAllTagsIsIn(const TArray<FString>& TestTags, const FString& RawTagString);` — Helper function that calls CheckAllTagsIsIn(const TArray<FString>&, const TArray<FString>&); @param  TestTags			The array of test tags we wish to test against. @param  RawTagString		Comma seperated string of elemnets we wish to convert to an array. @return true if all elements of RawTagString prased as an comma sperated array is in TestTags.
- L147 _public prototype_ `static bool CheckAllTagsIsIn(const TArray<FString>& TestTags, const TArray<FString>& InputTags);` — Checks if every element of InputTags is in TestTags. @param  TestTags       The array of test tags we wish to test against. @param  InputTags	  The array of tags we wish to see if all elements of are present in TestTags. @return  true if all elements of InputTags is in TestTags.
- L149 _public prototype_ `static FString GenerateTags(const FString& ServiceName, const FReportingSkippableTags& SkippableTags, const TCHAR* InTag);`
- L150 _public prototype_ `static bool ShouldDisableTest(const FString& ServiceName, const FReportingSkippableTags& SkippableTags, const TCHAR* InTag);`
- L151 _public prototype_ `static bool ShouldSkipTest(const FString& TagsToCheck);`
- L152 _public prototype_ `static void CheckRunningTestSkipOnTags();`
- L155 _public prototype_ `OnlineAutoReg(OnlineTestConstructor TestCtor, Catch::SourceLineInfo LineInfo, const char* Name, const char* Tags, const char* AddlOnlineInfo);` — This code is kept identical to Catch internals so that there is as little deviation from OSS_TESTS and Online_OSS_TESTS as possible
- L164 _public prototype_ `static TArray<FApplicableServicesConfig> GetApplicableServices();`

#### struct `OnlineAutoReg::FReportingSkippableTags`  
`struct FReportingSkippableTags`  
_L121-126_
- L123 _public member_ `TArray<FString> MayFailTags;`
- L124 _public member_ `TArray<FString> ShouldFailTags;`
- L125 _public member_ `TArray<FString> DisableTestTags;`

#### struct `OnlineAutoReg::FApplicableServicesConfig`  
`struct FApplicableServicesConfig`  
_L157-162_
- L159 _public member_ `FString Tag;`
- L160 _public member_ `EOnlineServices ServicesType;`
- L161 _public member_ `TArray<FString> ModulesToLoad;`

#### Free symbols / members of external scopes

- L116 _typedef_ `typedef OnlineTestBase* (*OnlineTestConstructor)();`
- L167 _prototype_ `TArray<TFunction<void()>>* GetGlobalInitalizers();`
- L171 _macro_ `#define INTERNAL_ONLINE_TEST_CASE_NAMED(RegName, Name, Tags, ...)\`
- L184 _macro_ `#define ONLINE_TEST_CASE(Name, Tags, ...) \`
- L189 _macro_ `#define CHECK_OP(Op)\`
- L194 _macro_ `#define CHECK_OP_EQ(Op, Arg)\` — also passes if the op is a success
- L199 _macro_ `#define CHECK_STR(Str)\`
- L203 _macro_ `#define CHECK_STR_EMPTY(Str)\`
- L208 _macro_ `#define REQUIRE_OP(Op)\`
- L213 _macro_ `#define REQUIRE_OP_EQ(Op, Arg)\` — also passes if the op is a success
- L218 _macro_ `#define REQUIRE_STR(Str)\`
- L222 _macro_ `#define REQUIRE_STR_EMPTY(Str)\`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/OnlineCatchStringMakers.h` (Public)


#### struct `Catch::StringMaker`  
`template<> struct StringMaker<UE::Online::FOnlineError>`  
_L16-19_
- L18 _public prototype_ `static std::string convert(UE::Online::FOnlineError const& Error);`
- L24 _public function_ `static std::string convert(UE::Online::TOnlineResult<T> const& Result)`

#### struct `Catch::StringMaker`  
`template <typename T> struct StringMaker<UE::Online::TOnlineResult<T>>`  
_L22-28_
- L18 _public prototype_ `static std::string convert(UE::Online::FOnlineError const& Error);`
- L24 _public function_ `static std::string convert(UE::Online::TOnlineResult<T> const& Result)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L13 _namespace_ `namespace Catch`

### `Source/Programs/Online/OnlineTestsCore/Source/Public/TestDriver.h` (Public)


#### struct `FPipelineTestContextInitOptions`  
`struct FPipelineTestContextInitOptions`  
_L32-36_
- L34 _public member_ `FName ServiceName;`
- L35 _public member_ `UE::Online::EOnlineServices ServiceType;`

#### class `FPipelineTestContext`  
`class FPipelineTestContext`  
_L38-50_
- L42 _public member_ `FPipelineTestContextInitOptions InitOptions;`
- L44 _public function_ `FPipelineTestContext(const FName& ServiceName, const UE::Online::EOnlineServices ServiceType)`

#### class `FTestPipeline`  
`class FTestPipeline`  
_L55-286_
- L120 _public typedef_ `using FStepPtr = TUniquePtr<FStep>;`
- L188 _public prototype_ `FTestPipeline(FTestPipeline&&) = default;`
- L189 _public prototype_ `FTestPipeline(const FTestPipeline&) = delete;`
- L192 _public function_ `FTestPipeline&& WithTimeout(FTimespan&& InTimeout)` — Adds an overall test timeout value to the pipeline.
- L199 _public function_ `FTestPipeline&& WithoutEvaluateTickCheck()` — Disables the per tick timer checks.
- L206 _public function_ `FTestPipeline&& WithEvaluateTickCheck(FTimespan&& InExpectedAverageTick, FTimespan&& InAbsoluteMaximumTick, uint32_t InMinimumTickCount = 10)` — Changes and enables the per tick timer checks based on the provided arguments.
- L214 _public function_ `template <typename T, typename... TArguments> FTestPipeline&& EmplaceStep(TArguments&&... Args)` — Adds a test step.
- L225 _public function_ `FTestPipeline&& EmplaceLambda(TUniqueFunction<void(IOnlineServicesPtr)> Lambda)` — Adds a custom test step. This function will run and resolve immediately
- L230 _public function_ `FTestPipeline&& EmplaceAsyncLambda(TUniqueFunction<void(FAsyncLambdaResult, IOnlineServicesPtr)> Lambda)`
- L236 _public prototype_ `FString InfoString() const;` — Generates a string suitable for INFO which will help identify where and when a specific failure has occurred.
- L238 _public prototype_ `void operator()(const IOnlineServicesPtr& Services);`
- L240 _public prototype_ `void OnPreRelease();`
- L249 _public function_ `void Start()`
- L255 _private function_ `FTestPipeline(FTestDriver& InDriver, FTimespan&& InTimeout) : Driver(InDriver) , PipelineTimeout(MoveTemp(InTimeout))`
- L261 _private function_ `FTestPipeline(FTestDriver& InDriver, FTimespan&& InTimeout, FEvaluateTickConfig&& InEvaluateTickConfig) : Driver(InDriver) , PipelineTimeout(MoveTemp(InTimeout)) , EvaluateTickConfig(MoveTemp(InEvaluateTickConfig))`
- L269 _private prototype_ `void EvaluatePlatformTickTime(double&& TickTime);` — Given the duration of the call to Tick, perform the configured excess tick check.
- L271 _private member_ `FTestDriver& Driver;`
- L272 _private member_ `TArray<FStepPtr> TestSteps;`
- L273 _private member_ `TArray<FStepPtr> CompletedSteps;`
- L274 _private member_ `TArray<FStepPtr> TimedoutSteps;`
- L275 _private member_ `TArray<FStepPtr> DeletePostReleaseSteps;`
- L276 _private member_ `FTimespan PipelineTimeout;`
- L277 _private member_ `double PipelineStartTime = 0.0;`
- L279 _private member_ `FEvaluateTickConfig EvaluateTickConfig;` — Current excess tick config.
- L281 _private member_ `FTimespan ServiceTickSum = FTimespan::FromMilliseconds(0);` — Sum of time to process all calls to Service Tick.
- L283 _private member_ `uint32 ServiceTickCount = 0;` — Number of calls to Service Tick.

#### struct `FTestPipeline::FEvaluateTickConfig`  
`struct FEvaluateTickConfig`  
_L63-106_
- desc: Defines the configuration used when checking for excess tick lengths. The default setup is relatively lenient.  We should tighten this up then determine the specific test cases that are allowed to deviate.
- L66 _public member_ `bool bEvaluateTickCheckActive = false;` — If true then the excess tick check will be used.
- L72 _public member_ `FTimespan ExpectedAverageTick = FTimespan::FromMilliseconds(5);` — The expected average tick length. After the MinimumTickCount ticks, if the average tick exceeds this value then a CHECK failure will occur. The default is changed for debug.
- L78 _public member_ `FTimespan AbsoluteMaximumTick = FTimespan::FromMilliseconds(75);` — The absolute maximum tick length. If the current tick exceeds this value then a CHECK failure will occur. The default is changed for debug.
- L83 _public member_ `uint32_t MinimumTickCount = 10;` — The minimum number of ticks per test before the average tick is evaluated against ExpectedAverageTick. The default is changed for debug.
- L89 _public function_ `FEvaluateTickConfig(bool bInEvaluateTickCheckActive = false) : bEvaluateTickCheckActive(bInEvaluateTickCheckActive) #if defined(UE_BUILD_DEBUG) && UE_BUILD_DEBUG , ExpectedAverageTick(FTimespan::FromMilliseconds(10)) , AbsoluteMaximumTick(FTimespan::FromMilliseconds(150)) , MinimumTickCount(10) #endif` — Basic constructor used as the default with enabled tick check and settings, or when disabling the tick check.
- L99 _public function_ `FEvaluateTickConfig(FTimespan&& InExpectedAverageTick, FTimespan&& InAbsoluteMaximumTick, uint32_t InMinimumTickCount = 10) : bEvaluateTickCheckActive(true) , ExpectedAverageTick(MoveTemp(InExpectedAverageTick)) , AbsoluteMaximumTick(MoveTemp(InAbsoluteMaximumTick)) , MinimumTickCount(InMinimumTickCount)` — Full constructor which allows changing all settings for an enabled tick check.

#### class `FTestPipeline::FStep`  
`class FStep`  
_L108-119_
- L111 _public member_ `uint32_t Index = 0;`
- L113 _public function_ `virtual ~FStep()`
- L114 _public function_ `virtual bool IsOptional() const`
- L115 _public function_ `virtual bool RequiresDeletePostRelease() const`
- L117 _public function_ `virtual void OnPreRelease()` — Called only if RequestDeletePostRelease is true and the FStep is being stored.
- L118 _public prototype_ `virtual EContinuance Tick(const IOnlineServicesPtr& Services) = 0;`

#### enum `FTestPipeline::FStep::EContinuance`  
`enum class EContinuance`  
_L112-112_
- L112 _public enumerator_ `enum class EContinuance { ContinueStepping, Done }; virtual ~FStep() {} virtual bool IsOptional() const { return false; } virtual bool RequiresDeletePostRelease() const { return false; } virtual void OnPreRelease() {} virtual EContinuance Tick(const IOnlineServicesPtr& Services) = 0;`
- L112 _public enumerator_ `enum class EContinuance { ContinueStepping, Done }; virtual ~FStep() {} virtual bool IsOptional() const { return false; } virtual bool RequiresDeletePostRelease() const { return false; } virtual void OnPreRelease() {} virtual EContinuance Tick(const IOnlineServicesPtr& Services) = 0;`

#### class `FTestPipeline::FLambdaStep`  
`class FLambdaStep : public FStep`  
_L122-137_
- inherits: `FStep`
- L125 _public function_ `FLambdaStep(TUniqueFunction<void(IOnlineServicesPtr)>&& InLambda) : Lambda(MoveTemp(InLambda))`
- L129 _public function_ `virtual EContinuance Tick(const IOnlineServicesPtr& Services) override`
- L136 _private member_ `TUniqueFunction<void(IOnlineServicesPtr)> Lambda;`

#### class `FTestPipeline::FAsyncLambdaStep`  
`class FAsyncLambdaStep : public FStep`  
_L139-186_
- inherits: `FStep`
- L142 _public function_ `FAsyncLambdaStep(TUniqueFunction<void(FAsyncLambdaResult, IOnlineServicesPtr)>&& InLambda) : Lambda(MoveTemp(InLambda))`
- L147 _public function_ `virtual ~FAsyncLambdaStep() override`
- L156 _public function_ `virtual EContinuance Tick(const IOnlineServicesPtr& Services) override`
- L181 _private member_ `TUniqueFunction<void(FAsyncLambdaResult, IOnlineServicesPtr)> Lambda;`
- L182 _private member_ `bool bRan = false;`
- L183 _private member_ `TAtomic<bool> bComplete = false;`
- L184 _private member_ `FAsyncLambdaResult ResultPromise{};`
- L185 _private member_ `TSharedPtr<TFuture<bool>> FuturePtr{};`

#### class `FTestDriver`  
`class FTestDriver`  
_L288-335_
- L291 _public typedef_ `using FServicesInstanceMap = TMap<IOnlineServicesPtr, FTestPipeline>;`
- L293 _public prototype_ `~FTestDriver();`
- L296 _public function_ `template <typename Func> void ForeachServicesInstance(Func&& Fn)`
- L304 _public function_ `FTestPipeline MakePipeline()`
- L310 _public function_ `template <typename... TArgs> FTestPipeline MakePipeline(TArgs&&... Args)`
- L315 _public prototype_ `bool AddPipeline(FTestPipeline&& Pipeline, const FPipelineTestContext& TestContext = FPipelineTestContext(TEXT("NULL"), UE::Online::EOnlineServices::Nul`
- L317 _public prototype_ `void MarkComplete(IOnlineServicesPtr Key);`
- L319 _public prototype_ `void RunToCompletion();`
- L321 _public function_ `void SetDriverTimedOut(bool InValue)`
- L323 _public prototype_ `FString TimeoutFailedTestInfo() const;`
- L325 _public member_ `int32 FailedStepNum = 0;`
- L329 _private prototype_ `void FlushCompleted();`
- L331 _private member_ `FServicesInstanceMap ServicesInstances;`
- L332 _private member_ `TSet<IOnlineServicesPtr> CompletedInstances;`
- L333 _private member_ `bool bDidTimeout = false;`
- L334 _private member_ `double LastTickTime = 0.0;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_BUILD_DEBUG 0`
- L18 _typedef_ `typedef TSharedPtr<UE::Online::IOnlineServices> IOnlineServicesPtr;`
- L19 _typedef_ `typedef TSharedPtr<TPromise<bool>> FAsyncLambdaResult;`
- L21 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogOnlineTests, Log, Log);`
- L23 _macro_ `#define UE_LOG_ONLINETESTS(Verbosity, Format, ...) \`
- L28 _variable_ `static const FTimespan TICK_DURATION = FTimespan::FromMilliseconds(1);`
- L52 _macro_ `#define INFO_TEST_STEP() INFO("Test Step Index: " << Index)`
- L53 _macro_ `#define INFO_TEST_STEP_OF(InTestStep) INFO("Test Step Index: " << InTestStep->Index)`
- L164 _function_ `` (scope `FTestPipeline::FAsyncLambdaStep::Tick`)
