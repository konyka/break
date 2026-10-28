# Plugins / OnlineFrameworkCommon

- module root: `Plugins/Online/OnlineFrameworkCommon/Source/OnlineFrameworkCommon`
- headers: 5; symbols: 142
- symbol kinds: class=5, delegate=5, enum=1, enumerator=4, function=16, member=26, namespace=12, prototype=53, struct=5, typedef=15
- PrivateDependencyModuleNames: OnlineServicesCommonEngineUtils, OnlineServicesInterface, OnlineServicesNull, OnlineServicesOSSAdapter, OnlineSubsystem
- PublicDependencyModuleNames: Core, CoreOnline, CoreUObject, Engine

### `Plugins/Online/OnlineFrameworkCommon/Source/OnlineFrameworkCommon/Private/OnlineFramework/CommonModule.h` (Private)


#### struct `UE::OnlineFramework::FOnlineFrameworkCommonConfig`  
`struct FOnlineFrameworkCommonConfig`  
_L21-25_
- desc: Config for OnlineFrameworkCommon
- L24 _public member_ `TMap<TPair<FName, ECommonConfigContextType>, FCommonConfigInstance> FrameworkConfigs;` — Framework configs. Map of FrameworkInstance name+type to config instance.

#### class `UE::OnlineFramework::FOnlineFrameworkCommonModule`  
`class FOnlineFrameworkCommonModule : public IModuleInterface`  
_L27-47_
- inherits: `IModuleInterface`
- L30 _public prototype_ `~FOnlineFrameworkCommonModule();`
- L32 _public prototype_ `static FOnlineFrameworkCommonModule* Get();`
- L33 _public function_ `const FOnlineFrameworkCommonConfig& GetConfig() const`
- L35 _public member_ `FWorldContextScopedObjectCache<FCommonAccountManager> CachedAccountManagers;`
- L38 _private prototype_ `virtual void StartupModule() override;`
- L39 _private prototype_ `virtual void ShutdownModule() override;`
- L42 _private prototype_ `void OnConfigSectionsChanged(const FString& IniFilename, const TSet<FString>& SectionNames);`
- L43 _private prototype_ `void UpdateFromConfig();`
- L46 _private member_ `FOnlineFrameworkCommonConfig Config;` — CommonConfig config

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineFrameworkCommon, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineFrameworkCommon, Log, All);`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace OnlineFramework` (scope `UE`)
- L17 _typedef_ `using FCommonAccountManagerPtr = TSharedPtr<FCommonAccountManager>;` (scope `UE::OnlineFramework`)
- L18 _typedef_ `using FCommonAccountManagerRef = TSharedRef<FCommonAccountManager>;` (scope `UE::OnlineFramework`)

### `Plugins/Online/OnlineFrameworkCommon/Source/OnlineFrameworkCommon/Public/OnlineFramework/CommonAccount.h` (Public)


#### class `UE::OnlineFramework::FCommonAccount`  
`class FCommonAccount : public TSharedFromThis<FCommonAccount>`  
_L19-107_
- inherits: `TSharedFromThis<FCommonAccount>`
- desc: Class that identifies a unique account and has the collection of account ids linked to that account
- L30 _public prototype_ `[[nodiscard]] UE::Online::FAccountId GetId(FName FrameworkInstance) const;` — Get the cached id for a framework instance @see GetIdAsync @see FCommonConfig @param FrameworkInstance the type of account id to retrieve @return the cached account id, or a default constructed id if there is no cached id
- L39 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnGetIdAsyncComplete, const FCommonAccountRef& , UE::Online::FAccountId );` — Completion delegate for GetIdAsync @param Account the account instance that currently represents this account. This is not guaranteed to be the account that GetIdAsync was called on. For example, if we found a corresponding account id, that id may belong to another registered account. In that case, we must perform a reconciliation and we may prefer the other account instance over this one. @param AccountId the looked up account id. This may be an invalid id if there is no association.
- L48 _public prototype_ `void GetIdAsync(FName FrameworkInstance, FOnGetIdAsyncComplete&& OnComplete);` — Lookup an account id for this account. This will prefer any cached values, then call all registered lookup methods for the registered ids. @see GetId @see FCommonConfig @param FrameworkInstance the type of account id to retrieve @param OnComplete completion delegate to call on complete
- L56 _public prototype_ `bool AddId(FName FrameworkInstance, UE::Online::FAccountId AccountId);` — Add an account id for this account. If the id already exists for the framework instance, or if the manager or framework instance not valid, no changes are made and this returns false. @param FrameworkInstance the type of account id to add @param AccountId the account ID to add @return whether the account id was added
- L64 _public prototype_ `bool Equals(const FCommonAccount& OtherAccount) const;` — Check if the target account equals this one. Generally, there should only be one common account associated with an account id, but after GetIdAsync we may merge them and systems may have lingering references to the replaced common account @param OtherAccount the account to test @return true if they are the same, false if not
- L74 _public prototype_ `FString ToLogString() const;` — Get a loggable version of this account @return a loggable version of this account
- L85 _public function_ `const FCommonConfig& GetCommonConfig()`
- L91 _private typedef_ `using FCommonAccountIdType = TTuple<UE::Online::EOnlineServices , FName >;`
- L92 _private prototype_ `void AddAccountId(UE::Online::FAccountId AccountId, const FCommonAccountIdType& AccountIdType);`
- L97 _private member_ `TWeakPtr<FCommonAccount> RedirectAccount;` — In the case of a conflict, this account could be replaced by another account. In that case, GetId and GetIdAsync for this instance will be redirected to the kept account. This is for the convenience of users for Common Account. The expected usage is to use the result of GetIdAsync or bind to FOnCommonAccountDuplicateDetected to handle account replacements.
- L98 _private member_ `TWeakPtr<FCommonAccountManager> Manager;`
- L99 _private member_ `FCommonConfig CommonConfig;`
- L100 _private member_ `TMap<FCommonAccountIdType, UE::Online::FAccountId> AccountIds;`
- L106 _public prototype_ `explicit FCommonAccount(FPrivateToken, const FCommonAccountManagerRef& Inmanager, const FCommonConfig& InCommonConfig);`

#### struct `UE::OnlineFramework::FCommonAccount::FPrivateToken`  
`struct FPrivateToken`  
_L104-104_
- L104 _public prototype_ `struct FPrivateToken`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace OnlineFramework` (scope `UE`)
- L11 _typedef_ `using FCommonAccountPtr = TSharedPtr<FCommonAccount>;` (scope `UE::OnlineFramework`)
- L12 _typedef_ `using FCommonAccountRef = TSharedRef<FCommonAccount>;` (scope `UE::OnlineFramework`)
- L14 _typedef_ `using FCommonAccountManagerRef = TSharedRef<FCommonAccountManager>;` (scope `UE::OnlineFramework`)
- L39 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetIdAsyncComplete, const FCommonAccountRef& , UE::Online::FAccountId );` — Completion delegate for GetIdAsync @param Account the account instance that currently represents this account. This is not guaranteed to be the account that GetIdAsync was called on. For example, if we found a corresponding account id, that id may belong to another registered account. In that case, we must perform a reconciliation and we may prefer the other account instance over this one. @param AccountId the looked up account id. This may be an invalid id if there is no association.
- L65 _function_ `friend bool operator==(const FCommonAccount& Lhs, const FCommonAccount& Rhs)` (scope `UE::OnlineFramework`)
- L76 _function_ `friend FString ToLogString(const FCommonAccount& InCommonAccount)` (scope `UE::OnlineFramework`)
- L80 _function_ `friend uint32 GetTypeHash(const FCommonAccount& InCommonAccount)` (scope `UE::OnlineFramework`)

### `Plugins/Online/OnlineFrameworkCommon/Source/OnlineFrameworkCommon/Public/OnlineFramework/CommonAccountManager.h` (Public)


#### class `UE::OnlineFramework::FCommonAccountLookupAccountIdFnHandle`  
`class FCommonAccountLookupAccountIdFnHandle final : public FNoncopyable`  
_L23-39_
- inherits: `FNoncopyable`
- desc: Handle for registered lookup function. Automatically unregisters on destruction, or explicitly by calling Unbind.
- L26 _public function_ `FCommonAccountLookupAccountIdFnHandle()`
- L27 _public function_ `FCommonAccountLookupAccountIdFnHandle(FCommonAccountLookupAccountIdFnHandle&& InHandle)`
- L28 _public function_ `FCommonAccountLookupAccountIdFnHandle& operator=(FCommonAccountLookupAccountIdFnHandle&& InHandle)`
- L29 _public function_ `~FCommonAccountLookupAccountIdFnHandle()`
- L31 _public prototype_ `void Unbind();`
- L33 _private prototype_ `void Reassign(FCommonAccountLookupAccountIdFnHandle&& InHandle);`
- L35 _private prototype_ `FCommonAccountLookupAccountIdFnHandle(FCommonAccountManagerRef InManager, int InRegisteredId);`
- L37 _private member_ `TWeakPtr<FCommonAccountManager> Manager;`
- L38 _private member_ `int RegisteredId = 0;`

#### class `UE::OnlineFramework::FCommonAccountManager`  
`class FCommonAccountManager : public TSharedFromThis<FCommonAccountManager>`  
_L64-153_
- inherits: `TSharedFromThis<FCommonAccountManager>`
- desc: Class to manage creation of and links between FCommonAccount
- L69 _public prototype_ `~FCommonAccountManager();`
- L76 _public prototype_ `static FCommonAccountManagerPtr Get(const FCommonConfig& InCommonConfig);` — Get the account manager for a context @param InContext the context to get the account manager for. @return the common account manager for the context
- L82 _public prototype_ `static void ClearRegistered(const FCommonConfig& InCommonConfig);` — Clear the account manager for a context. Expected to only be used in strictly controlled scenarios, such as automated tests. @param InContext the context to clear the account manager for.
- L90 _public prototype_ `[[nodiscard]] FCommonAccountPtr GetAccount(UE::Online::FAccountId AccountId, FName FrameworkInstance);` — Get an existing or create a new account given an account id and FrameworkInstance @param AccountId the account id for the account @param FrameworkInstance the framework instance that defines the account id's type @return the common account for the id. Will return nullptr only if AccountId is invalid.
- L96 _public prototype_ `[[nodiscard]] FCommonAccountLookupAccountIdFnHandle RegisterAccountIdLookup(FStringView Name, FCommonAccountLookupAccountIdFn&& InAccountIdFn);` — Register a function to perform lookups @param Name the name of the function for debugging
- L98 _public function_ `FOnCommonAccountCreated& OnCommonAccountCreated()`
- L99 _public function_ `FOnCommonAccountIdAdded& OnCommonAccountIdAdded()`
- L100 _public function_ `FOnCommonAccountDuplicateDetected& OnCommonAccountDuplicateDetected()`
- L105 _private prototype_ `FCommonAccountRef CreateNewAccount(UE::Online::FAccountId AccountId, FName FrameworkInstance);` — Create a new account
- L107 _private prototype_ `FCommonAccountPtr FindExistingAccount(UE::Online::FAccountId AccountId) const;` — Find an existing account
- L109 _private typedef_ `using FLookupIdAsync = TTuple<FCommonAccountRef, UE::Online::FAccountId>;` — Lookup an id for a account
- L110 _private prototype_ `TFuture<FLookupIdAsync> LookupIdAsync(const FCommonAccountRef& InAccount, FName FrameworkInstance);`
- L112 _private prototype_ `void ExecuteNextLookup(const FCommonAccountRef& InAccount, TSharedRef<TPromise<FLookupIdAsync>> Promise, FName FrameworkInstance, FCommonConfigInstance&& ConfigInstance, int LastRegisteredId);` — Continue a lookup on the next registered function
- L114 _private prototype_ `void HandleAccountIdFound(const FCommonAccountRef& Account, UE::Online::FAccountId AccountId, FCommonConfigInstance&& ConfigInstance, const TSharedRef<TPromise<FLookupIdAsync>>& LookupPromise);` — Handle an async lookup completing
- L116 _private prototype_ `FCommonAccountRef AddAccountId(const FCommonAccountRef& Account, UE::Online::FAccountId AccountId, FCommonConfigInstance&& ConfigInstance);` — Add a new account ID
- L118 _private prototype_ `FCommonAccountRef ResolveAccountIdAssociationConflict(const FCommonAccountRef& Account, UE::Online::FAccountId ConflictingAccountId);` — Resolve an account id association conflict where we find out two common accounts are actually the same account after discovering a linked account
- L121 _private prototype_ `void Unbind(int RegisteredId);` — Unbind a registered function
- L123 _private prototype_ `void FailPendingLookups();` — Complete all pending lookups. Called on destruction to ensure we have no unfulfilled promises.
- L126 _private member_ `FCommonConfig CommonConfig;` — Common config to resolve FrameworkInstance to online services
- L128 _private member_ `TMap<UE::Online::FAccountId, FCommonAccountRef> Accounts;` — Registered accounts. Note that while FAccountId lacks context to know which framework instance it is for, FAccountId is unique enough to index on.
- L135 _private function_ `friend bool operator==(const FRegisteredLookupFunction& This, int InRegisteredId)`
- L137 _private member_ `TArray<FRegisteredLookupFunction> AccountIdLookups;`
- L139 _private member_ `TMap<TSharedRef<TPromise<FLookupIdAsync>>, FCommonAccountPtr> PendingLookups;` — In progress lookups
- L140 _private member_ `static int32 RegisteredIdCounter;`
- L142 _private member_ `bool bCanPerformAsyncLookup = true;` — Whether we can accept new async lookup requests or not
- L144 _private member_ `FOnCommonAccountCreated OnCommonAccountCreatedEvent;`
- L145 _private member_ `FOnCommonAccountIdAdded OnCommonAccountIdAddedEvent;`
- L146 _private member_ `FOnCommonAccountDuplicateDetected OnCommonAccountDuplicateDetectedEvent;`
- L152 _public prototype_ `explicit FCommonAccountManager(FPrivateToken, const FCommonConfig& InCommonConfig);` — Constructor: Do not construct directly. Use Create instead.

#### struct `UE::OnlineFramework::FCommonAccountManager::FRegisteredLookupFunction`  
`struct FRegisteredLookupFunction`  
_L130-136_
- desc: Registered account id lookups
- L132 _public member_ `FString Name;`
- L133 _public member_ `FCommonAccountLookupAccountIdFn Function;`
- L134 _public member_ `int RegisteredId;`

#### struct `UE::OnlineFramework::FCommonAccountManager::FPrivateToken`  
`struct FPrivateToken`  
_L149-149_
- L149 _public prototype_ `struct FPrivateToken`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace OnlineFramework` (scope `UE`)
- L14 _typedef_ `using FCommonAccountPtr = TSharedPtr<FCommonAccount>;` (scope `UE::OnlineFramework`)
- L15 _typedef_ `using FCommonAccountRef = TSharedRef<FCommonAccount>;` (scope `UE::OnlineFramework`)
- L17 _typedef_ `using FCommonAccountManagerPtr = TSharedPtr<FCommonAccountManager>;` (scope `UE::OnlineFramework`)
- L18 _typedef_ `using FCommonAccountManagerRef = TSharedRef<FCommonAccountManager>;` (scope `UE::OnlineFramework`)
- L20 _typedef_ `using FCommonAccountLookupAccountIdFn = TFunction<TFuture<UE::Online::FAccountId>(FCommonAccount& , FName , const FCommonConfigInstance& )>;` (scope `UE::OnlineFramework`)
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCommonAccountCreated, const FCommonAccountRef& );` — Event triggered when a common account is created @param Account the created account
- L45 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCommonAccountCreated, const FCommonAccountRef& );` (scope `UE::OnlineFramework`) — Event triggered when a common account is created @param Account the created account
- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCommonAccountIdAdded, const FCommonAccountRef& , UE::Online::FAccountId );` — Event triggered when a common account has an account id added @param Account the account that has an account id added @param NewAccountId the new account id
- L51 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCommonAccountIdAdded, const FCommonAccountRef& , UE::Online::FAccountId );` (scope `UE::OnlineFramework`) — Event triggered when a common account has an account id added @param Account the account that has an account id added @param NewAccountId the new account id
- L59 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCommonAccountDuplicateDetected, const FCommonAccountRef& , const FCommonAccountRef& );` — Event triggered when two common accounts have been identified to represent the same account For example, if account1 is created for account A, and account2 for account B, and something later calls GetIdAsync for account1 for the type of account B, we may find that the accounts are linked and therefore are the same account In this case, one account will be kept and the other account will be removed. Integrations are expected to update any local mappings that reference the removed account to reference the kept account. @param KeptAccount the account that was kept @param RemovedAccount the account that was removed
- L59 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCommonAccountDuplicateDetected, const FCommonAccountRef& , const FCommonAccountRef& );` (scope `UE::OnlineFramework`) — Event triggered when two common accounts have been identified to represent the same account For example, if account1 is created for account A, and account2 for account B, and something later calls GetIdAsync for account1 for the type of account B, we may find that the accounts are linked and therefore are the same account In this case, one account will be kept and the other account will be removed. Integrations are expected to update any local mappings that reference the removed account to reference the kept account. @param KeptAccount the account that was kept @param RemovedAccount the account that was removed

### `Plugins/Online/OnlineFrameworkCommon/Source/OnlineFrameworkCommon/Public/OnlineFramework/CommonAccountUtils.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace OnlineFramework` (scope `UE`)
- L13 _typedef_ `using FCommonAccountRef = TSharedRef<FCommonAccount>;` (scope `UE::OnlineFramework`)
- L14 _typedef_ `using FCommonAccountPtr = TSharedPtr<FCommonAccount>;` (scope `UE::OnlineFramework`)
- L20 _typedef_ `using FCommonAccountIdType = TTuple<UE::Online::EOnlineServices , FName >;` (scope `UE::OnlineFramework`) — Tuple that uniquely identifies an account id type
- L21 _prototype_ `[[nodiscard]] FCommonAccountIdType GetCommonAccountIdType(const FCommonConfig& CommonConfig, FName FrameworkInstance);` (scope `UE::OnlineFramework`)
- L22 _prototype_ `[[nodiscard]] FCommonAccountIdType GetCommonAccountIdType(const FCommonConfigInstance& CommonConfigInstance);` (scope `UE::OnlineFramework`)
- L23 _prototype_ `[[nodiscard]] UE::Online::FAccountId GetAccountV2FromV1(const FCommonConfig& CommonConfig, const FUniqueNetIdPtr& InId, FName FrameworkInstance);` (scope `UE::OnlineFramework`)
- L24 _prototype_ `[[nodiscard]] FCommonAccountPtr GetCommonAccountFromV1(const FCommonConfig& CommonConfig, const FUniqueNetIdPtr& InId, FName FrameworkInstance);` (scope `UE::OnlineFramework`)
- L25 _prototype_ `[[nodiscard]] FCommonAccountPtr GetCommonAccountFromV2(const FCommonConfig& CommonConfig, const UE::Online::FAccountId& InAccountId, FName FrameworkInstance);` (scope `UE::OnlineFramework`)
- L26 _prototype_ `[[nodiscard]] FUniqueNetIdPtr GetV1FromCommonAccount(const FCommonAccountRef& CommonAccount, FName FrameworkInstance);` (scope `UE::OnlineFramework`)
- L36 _prototype_ `[[nodiscard]] FName GetFirstFrameworkInstanceName(const FUniqueNetIdWrapper& InId);` (scope `UE::OnlineFramework`) — Get the first framework instance that matches the input account id. Unsafe if the account id's type could have multiple, incompatible online services instances associated with it. Otherwise, generally safe. For V1 net ids, requires a common config entry with Name=OnlineSubsystemName Prefer having your system know by config or other inputs what the framework instance is. Intended to be a utility while converting existing systems over to using newer online frameworks. @param InId the account id to get the framework instance name for @return the first framework instance that matches the input's type, or NAME_None if none is found.

### `Plugins/Online/OnlineFrameworkCommon/Source/OnlineFrameworkCommon/Public/OnlineFramework/CommonConfig.h` (Public)


#### enum `UE::OnlineFramework::ECommonConfigContextType`  
`enum class ECommonConfigContextType : uint8`  
_L16-26_
- desc: Context type
- L19 _public enumerator_ `Default` — No specific meaning or context
- L21 _public enumerator_ `Client` — Client (including listen server)
- L23 _public enumerator_ `Server` — Dedicated Server
- L25 _public enumerator_ `Editor` — Editor

#### struct `UE::OnlineFramework::FCommonConfigInstance`  
`struct FCommonConfigInstance`  
_L32-40_
- L35 _public member_ `UE::Online::EOnlineServices OnlineServices = UE::Online::EOnlineServices::None;` — The OnlineServices type
- L37 _public member_ `FName OnlineServicesInstanceConfigName;` — The config to use for this OnlineServices instance (could be NAME_None depending on the implementation)
- L39 _public member_ `ECommonConfigContextType Type = ECommonConfigContextType::Default;` — The context this config instance applies to

#### class `UE::OnlineFramework::FCommonConfig`  
`class FCommonConfig`  
_L42-96_
- L46 _public function_ `FCommonConfig(FName InWorldContextName, ECommonConfigContextType InContextType) : WorldContextName(InWorldContextName) , ContextType(InContextType)` — Constructor to explicitly set fields
- L52 _public prototype_ `FCommonConfig(const UObject* ContextObject);` — Constructor to determine the context from a UObject. Intentionally implicit.
- L54 _public prototype_ `FCommonConfig() = delete;`
- L61 _public prototype_ `TOptional<FCommonConfigInstance> GetFrameworkInstanceConfig(FName FrameworkInstance) const;` — Get the config for a framework instance @param FrameworkInstance the framework instance name @return the config, or an unset optional if the config is not present.
- L68 _public prototype_ `TSharedPtr<UE::Online::IOnlineServices> GetServices(FName FrameworkInstance) const;` — Get the online services configured for a framework instance @param FrameworkInstance the framework instance name @return the online services. May be null if the framework instance is not configured, or if the online services is unavailable
- L74 _public function_ `FName GetWorldContextName() const` — Get the world context for this online config instance. @return the world context
- L83 _public function_ `ECommonConfigContextType GetContextType() const` — Get the context type for this online config instance. @return the context type
- L89 _private prototype_ `const FCommonConfigInstance* FindFrameworkInstanceConfig(FName FrameworkInstance) const;`
- L92 _private member_ `FName WorldContextName;` — World context name. Expected to be NAME_None, except for PIE where it will be the world's context name.
- L95 _private member_ `ECommonConfigContextType ContextType;` — Context type

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace OnlineFramework` (scope `UE`)
- L28 _prototype_ `const TCHAR* LexToString(const ECommonConfigContextType Value);` (scope `UE::OnlineFramework`)
- L29 _prototype_ `bool LexTryParseString(ECommonConfigContextType& OutValue, FStringView StringView);` (scope `UE::OnlineFramework`)
- L30 _prototype_ `void LexFromString(ECommonConfigContextType& OutValue, FStringView StringView);` (scope `UE::OnlineFramework`)
