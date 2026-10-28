# Runtime / CoreOnline

- module root: `Source/Runtime/CoreOnline`
- headers: 6; symbols: 368
- symbol kinds: class=10, enum=2, enumerator=36, function=120, macro=5, member=29, namespace=8, prototype=86, struct=18, typedef=54
- PublicDependencyModuleNames: Core, CoreUObject, Json
- PublicIncludePathModuleNames: CoreUObject

### `Source/Runtime/CoreOnline/Private/Online/CoreOnlinePrivate.h` (Private)


#### enum `ECoreOnlineDummy`  
`enum class ECoreOnlineDummy : uint8`  
_L12-15_
- reflection: `UENUM(BlueprintType)`
- desc: This exists purely to guarantee a package is created, or the engine will not boot.
- L14 _public enumerator_ `Dummy`

#### class `UE::Online::FOnlineForeignAccountIdRegistry`  
`class FOnlineForeignAccountIdRegistry`  
_L30-45_
- desc: Registry for storing account id's for unregistered services implementations.
- L33 _public prototype_ `FString ToString(const FAccountId& AccountId) const;`
- L34 _public prototype_ `FString ToLogString(const FAccountId& AccountId) const;`
- L35 _public prototype_ `TArray<uint8> ToReplicationData(const FAccountId& AccountId) const;`
- L36 _public prototype_ `FAccountId FromReplicationData(EOnlineServices Services, const TArray<uint8>& RepData);`
- L44 _private member_ `TMap<EOnlineServices, FRepData> OnlineServicesToRepData;`

#### struct `UE::Online::FOnlineForeignAccountIdRegistry::FRepData`  
`struct FRepData`  
_L39-43_
- L41 _public member_ `TMap<TArray<uint8>, FAccountId> RepDataToHandle;`
- L42 _public member_ `TArray<TArray<uint8>> RepDataArray;`

#### Free symbols / members of external scopes

- L17 _function_ `static uint32 GetTypeHash(const TArray<uint8>& Array)`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Online` (scope `UE`)

### `Source/Runtime/CoreOnline/Public/Online/CoreOnline.h` (Public)


#### struct `FJoinabilitySettings`  
`struct FJoinabilitySettings`  
_L43-95_
- reflection: `USTRUCT(noexport)`
- L49 _public member_ `FName SessionName;` — `UPROPERTY()` — Name of session these settings affect
- L52 _public member_ `bool bPublicSearchable;` — `UPROPERTY()` — Is this session now publicly searchable
- L55 _public member_ `bool bAllowInvites;` — `UPROPERTY()` — Does this session allow invites
- L58 _public member_ `bool bJoinViaPresence;` — `UPROPERTY()` — Does this session allow public join via presence
- L61 _public member_ `bool bJoinViaPresenceFriendsOnly;` — `UPROPERTY()` — Does this session allow friends to join via presence
- L64 _public member_ `int32 MaxPlayers;` — `UPROPERTY()` — Current max players in this session
- L67 _public member_ `int32 MaxPartySize;` — `UPROPERTY()` — Current max party size in this session
- L69 _public function_ `FJoinabilitySettings() : SessionName(NAME_None), bPublicSearchable(false), bAllowInvites(false), bJoinViaPresence(false), bJoinViaPresenceFriendsOnly(false), MaxPlayers(0), MaxPartySize(0)`
- L80 _public function_ `bool operator==(const FJoinabilitySettings& Other) const`
- L91 _public function_ `bool operator!=(const FJoinabilitySettings& Other) const`

#### class `FUniqueNetId`  
`class FUniqueNetId : public TSharedFromThis<FUniqueNetId>`  
_L101-201_
- inherits: `TSharedFromThis<FUniqueNetId>`
- desc: Abstraction of a profile service online Id The class is meant to be opaque
- L106 _protected prototype_ `FUniqueNetId() = default;` — Only constructible by derived type
- L108 _protected prototype_ `FUniqueNetId(const FUniqueNetId& Src) = default;`
- L109 _protected prototype_ `FUniqueNetId& operator=(const FUniqueNetId& Src) = default;`
- L111 _protected function_ `virtual bool Compare(const FUniqueNetId& Other) const`
- L120 _public prototype_ `virtual ~FUniqueNetId() = default;`
- L141 _public function_ `virtual FName GetType() const` — Get the type token for this opaque data This is useful for inferring UniqueId subclasses and knowing which OSS it "goes with" @return FName representing the Type
- L149 _public prototype_ `virtual const uint8* GetBytes() const = 0;` — Get the raw byte representation of this opaque data This data is platform dependent and shouldn't be manipulated directly @return byte array of size GetSize()
- L156 _public prototype_ `virtual int32 GetSize() const = 0;` — Get the size of the opaque data @return size in bytes of the data representation
- L163 _public prototype_ `virtual bool IsValid() const = 0;` — Check the validity of the opaque data @return true if this is well formed data, false otherwise
- L170 _public prototype_ `virtual FString ToString() const = 0;` — Platform specific conversion to string representation of data @return data in string form
- L178 _public prototype_ `virtual FString ToDebugString() const = 0;` — Get a human readable representation of the opaque data Shouldn't be used for anything other than logging/debugging @return data in string form
- L180 _public function_ `virtual uint32 GetTypeHash() const`
- L188 _public function_ `FString GetHexEncodedString() const` — @return hex encoded string representation of unique id

#### struct `UE::Online::OnlineIdHandleTags::FAccount`  
`struct FAccount`  
_L210-210_

#### struct `UE::Online::OnlineIdHandleTags::FSession`  
`struct FSession`  
_L211-211_

#### struct `UE::Online::OnlineIdHandleTags::FSessionInvite`  
`struct FSessionInvite`  
_L212-212_

#### struct `UE::Online::OnlineIdHandleTags::FLobby`  
`struct FLobby`  
_L213-213_

#### struct `UE::Online::OnlineIdHandleTags::FVerifiedAuthTicket`  
`struct FVerifiedAuthTicket`  
_L214-214_

#### struct `UE::Online::OnlineIdHandleTags::FVerifiedAuthSession`  
`struct FVerifiedAuthSession`  
_L215-215_

#### struct `UE::Online::OnlineIdHandleTags::FLoginContinuation`  
`struct FLoginContinuation`  
_L216-216_

#### enum `UE::Online::EOnlineServices`  
`enum class EOnlineServices : uint8`  
_L219-289_
- L222 _public enumerator_ `Null` — Null, Providing minimal functionality when no backend services are required
- L224 _public enumerator_ `Epic` — Epic Online Services, merges Epic Account Services and Epic Game Services. Note this will be deprecated in favor of separating out the services
- L226 _public enumerator_ `Xbox` — Xbox services
- L228 _public enumerator_ `PSN` — PlayStation Network
- L230 _public enumerator_ `Nintendo` — Nintendo
- L232 _public enumerator_ `Reserved_5` — Unused,
- L234 _public enumerator_ `Steam` — Steam
- L236 _public enumerator_ `Google` — Google
- L238 _public enumerator_ `GooglePlay` — GooglePlay
- L240 _public enumerator_ `Apple` — Apple
- L242 _public enumerator_ `AppleGameKit` — GameKit
- L244 _public enumerator_ `Samsung` — Samsung
- L246 _public enumerator_ `Oculus` — Oculus
- L248 _public enumerator_ `Tencent` — Tencent
- L250 _public enumerator_ `EpicAccount` — Epic Account Services (friends, presence, etc)
- L252 _public enumerator_ `EpicGame` — Epic Game Services (lobbies, achievements, etc)
- L254 _public enumerator_ `Reserved_16` — Reserved for future use/platform extensions
- L255 _public enumerator_ `Reserved_17`
- L256 _public enumerator_ `Reserved_18`
- L257 _public enumerator_ `Reserved_19`
- L258 _public enumerator_ `Reserved_20`
- L259 _public enumerator_ `Reserved_21`
- L260 _public enumerator_ `Reserved_22`
- L261 _public enumerator_ `Reserved_23`
- L262 _public enumerator_ `Reserved_24`
- L263 _public enumerator_ `Reserved_25`
- L264 _public enumerator_ `Reserved_26`
- L265 _public enumerator_ `Reserved_27`
- L279 _public enumerator_ `GameDefined_0 = 28` — For game specific Online Services To make use of GameDefined_x, ideally it should do all these steps in module startup: 1. Read the EOnlineServices value from config, to avoid conflict with any other plugin while keeping it data-driven; EOnlineServices XxxServices = EOnlineServices::GameDefined_0; FString ConfigStr; if (GConfig->GetString(TEXT("OnlineServicesXxx"), TEXT("ServicesEnumEntry"), ConfigStr, GEngineIni)) { LexFromString(XxxServices, *ConfigStr); } 2. Register the factory with that value; FOnlineServicesRegistry::Get().RegisterServicesFactory(XxxServices, ...); 3. Optionally register the alias based on the value read from config RegisterAliasForGameDefined(XxxServices, TEXT("Xxx"));
- L280 _public enumerator_ `GameDefined_1`
- L281 _public enumerator_ `GameDefined_2`
- L282 _public enumerator_ `GameDefined_3`
- L284 _public enumerator_ `None = 253` — None, used internally to resolve Platform or Default if they are not configured
- L286 _public enumerator_ `Platform = 254` — Platform native, may not exist for all platforms
- L288 _public enumerator_ `Default = 255` — Default, configured via ini, TODO: List specific ini section/key

#### class `UE::Online::TOnlineId`  
`template<typename IdType> class TOnlineId`  
_L308-329_
- desc: A handle to an id which uniquely identifies a persistent or transient online resource, i.e. account/session/party etc, within a given Online Services provider. At most one id, and therefore one handle, exists for any given resource. The id and handle persist until the OnlineServices module is unloaded. Passed to and returned from OnlineServices APIs.
- L311 _public prototype_ `TOnlineId() = default;`
- L312 _public function_ `TOnlineId(EOnlineServices Type, uint32 Handle)`
- L318 _public function_ `inline bool IsValid() const`
- L319 _public function_ `inline explicit operator bool() const`
- L321 _public function_ `EOnlineServices GetOnlineServicesType() const`
- L322 _public function_ `uint32 GetHandle() const`
- L324 _public function_ `bool operator==(const TOnlineId& Other) const`
- L325 _public function_ `bool operator!=(const TOnlineId& Other) const`
- L328 _private member_ `uint32 Value = uint32(EOnlineServices::Null) << 24;`

#### class `UE::Online::IOnlineIdRegistry`  
`template<typename IdType> class IOnlineIdRegistry`  
_L364-374_
- L367 _public prototype_ `virtual ~IOnlineIdRegistry() = default;`
- L369 _public prototype_ `virtual FString ToString(const TOnlineId<IdType>& OnlineId) const = 0;`
- L370 _public prototype_ `virtual FString ToLogString(const TOnlineId<IdType>& OnlineId) const = 0;`
- L371 _public prototype_ `virtual TArray<uint8> ToReplicationData(const TOnlineId<IdType>& OnlineId) const = 0;`
- L372 _public prototype_ `virtual TOnlineId<IdType> FromReplicationData(const TArray<uint8>& ReplicationData) = 0;`
- L373 _public prototype_ `virtual TOnlineId<IdType> FromStringData(const FString& StringData) = 0;`

#### class `UE::Online::FOnlineIdRegistryRegistry`  
`class FOnlineIdRegistryRegistry`  
_L380-498_
- L388 _public prototype_ `static FOnlineIdRegistryRegistry& Get();` — Get the FOnlineIdRegistryRegistry singleton @return The FOnlineIdRegistryRegistry singleton instance
- L393 _public prototype_ `static void TearDown();` — Tear down the singleton instance
- L402 _public prototype_ `void RegisterAccountIdRegistry(EOnlineServices OnlineServices, IOnlineAccountIdRegistry* Registry, int32 Priority = 0);` — Register a registry for a given OnlineServices implementation and IOnlineAccountIdHandle type @param OnlineServices Services that the registry is for @param Registry the registry of online account ids @param Priority Integer priority, allows an existing registry to be extended and registered with a higher priority so it is used instead
- L410 _public prototype_ `void UnregisterAccountIdRegistry(EOnlineServices OnlineServices, int32 Priority = 0);` — Unregister a previously registered Account Id registry @param OnlineServices Services that the registry is for @param Priority Integer priority, will be unregistered only if the priority matches the one that is registered
- L413 _public prototype_ `FString ToString(const FAccountId& AccountId) const;` — TODO Might be worth these being templates
- L414 _public prototype_ `FString ToLogString(const FAccountId& AccountId) const;`
- L415 _public prototype_ `TArray<uint8> ToReplicationData(const FAccountId& AccountId) const;`
- L416 _public prototype_ `FAccountId ToAccountId(EOnlineServices Services, const TArray<uint8>& RepData) const;`
- L417 _public prototype_ `FAccountId ToAccountId(EOnlineServices Services, const FString& StringData) const;`
- L419 _public prototype_ `IOnlineAccountIdRegistry* GetAccountIdRegistry(EOnlineServices OnlineServices) const;`
- L428 _public prototype_ `void RegisterSessionIdRegistry(EOnlineServices OnlineServices, IOnlineSessionIdRegistry* Registry, int32 Priority = 0);` — Register a registry for a given OnlineServices implementation and IOnlineSessionIdHandle type @param OnlineServices Services that the registry is for @param Registry the registry of online session ids @param Priority Integer priority, allows an existing registry to be extended and registered with a higher priority so it is used instead
- L436 _public prototype_ `void UnregisterSessionIdRegistry(EOnlineServices OnlineServices, int32 Priority = 0);` — Unregister a previously registered Session Id registry @param OnlineServices Services that the registry is for @param Priority Integer priority, will be unregistered only if the priority matches the one that is registered
- L438 _public prototype_ `FString ToString(const FOnlineSessionId& SessionId) const;`
- L439 _public prototype_ `FString ToLogString(const FOnlineSessionId& SessionId) const;`
- L440 _public prototype_ `TArray<uint8> ToReplicationData(const FOnlineSessionId& SessionId) const;`
- L441 _public prototype_ `FOnlineSessionId ToSessionId(EOnlineServices Services, const TArray<uint8>& RepData) const;`
- L443 _public prototype_ `IOnlineSessionIdRegistry* GetSessionIdRegistry(EOnlineServices OnlineServices) const;`
- L452 _public prototype_ `void RegisterSessionInviteIdRegistry(EOnlineServices OnlineServices, IOnlineSessionInviteIdRegistry* Registry, int32 Priority = 0);` — Register a registry for a given OnlineServices implementation and IOnlineSessionInviteIdHandle type @param OnlineServices Services that the registry is for @param Registry the registry of online session ids @param Priority Integer priority, allows an existing registry to be extended and registered with a higher priority so it is used instead
- L460 _public prototype_ `void UnregisterSessionInviteIdRegistry(EOnlineServices OnlineServices, int32 Priority = 0);` — Unregister a previously registered Session Invite Id registry @param OnlineServices Services that the registry is for @param Priority Integer priority, will be unregistered only if the priority matches the one that is registered
- L462 _public prototype_ `FString ToLogString(const FSessionInviteId& SessionInviteId) const;`
- L463 _public prototype_ `TArray<uint8> ToReplicationData(const FSessionInviteId& SessionInviteId) const;`
- L464 _public prototype_ `FSessionInviteId ToSessionInviteId(EOnlineServices Services, const TArray<uint8>& RepData) const;`
- L466 _public prototype_ `IOnlineSessionInviteIdRegistry* GetSessionInviteIdRegistry(EOnlineServices OnlineServices) const;`
- L482 _private typedef_ `typedef FOnlineIdRegistryAndPriority<OnlineIdHandleTags::FAccount> FAccountIdRegistryAndPriority;`
- L483 _private typedef_ `typedef FOnlineIdRegistryAndPriority<OnlineIdHandleTags::FSession> FSessionIdRegistryAndPriority;`
- L484 _private typedef_ `typedef FOnlineIdRegistryAndPriority<OnlineIdHandleTags::FSessionInvite> FSessionInviteIdRegistryAndPriority;`
- L486 _private member_ `TMap<EOnlineServices, FAccountIdRegistryAndPriority> AccountIdRegistries;`
- L487 _private member_ `TUniquePtr<FOnlineForeignAccountIdRegistry> ForeignAccountIdRegistry;`
- L489 _private member_ `TMap<EOnlineServices, FSessionIdRegistryAndPriority> SessionIdRegistries;`
- L491 _private member_ `TMap<EOnlineServices, FSessionInviteIdRegistryAndPriority> SessionInviteIdRegistries;`
- L497 _private prototype_ `~FOnlineIdRegistryRegistry();`

#### struct `UE::Online::FOnlineIdRegistryRegistry::FOnlineIdRegistryAndPriority`  
`template<typename IdType> struct FOnlineIdRegistryAndPriority`  
_L471-480_
- L473 _public function_ `FOnlineIdRegistryAndPriority(IOnlineIdRegistry<IdType>* InRegistry, int32 InPriority) : Registry(InRegistry), Priority(InPriority)`
- L476 _public prototype_ `virtual ~FOnlineIdRegistryAndPriority() = default;`
- L478 _public member_ `IOnlineIdRegistry<IdType>* Registry;`
- L479 _public member_ `int32 Priority;`

#### struct `FUniqueNetIdWrapper`  
`struct FUniqueNetIdWrapper`  
_L503-776_
- reflection: `USTRUCT(noexport)`
- L507 _public typedef_ `using FVariantType = TVariant<FUniqueNetIdPtr, UE::Online::FAccountId>;`
- L509 _public prototype_ `FUniqueNetIdWrapper() = default;`
- L510 _public prototype_ `virtual ~FUniqueNetIdWrapper() = default;`
- L514 _public function_ `FUniqueNetIdWrapper(const FUniqueNetIdRef& InUniqueNetId)`
- L519 _public function_ `FUniqueNetIdWrapper(const FUniqueNetIdPtr& InUniqueNetId)`
- L524 _public function_ `FUniqueNetIdWrapper(const FVariantType& InVariant) : Variant(InVariant)`
- L529 _public function_ `FUniqueNetIdWrapper(const UE::Online::FAccountId& AccountId)`
- L535 _public function_ `FUniqueNetIdWrapper(const FUniqueNetId& InUniqueNetId)` — temporarily restored implicit conversion from FUniqueNetId
- L540 _public function_ `bool IsV1() const`
- L545 _public function_ `FUniqueNetIdPtr GetV1() const`
- L556 _public function_ `const FUniqueNetIdPtr& GetV1Unsafe() const` — Getter to be used only when the variant index has already been confirmed
- L561 _public function_ `bool IsV2() const`
- L566 _public function_ `UE::Online::FAccountId GetV2() const`
- L577 _public function_ `const UE::Online::FAccountId& GetV2Unsafe() const` — Getter to be used only when the variant index has already been confirmed
- L582 _public function_ `FName GetType() const`
- L593 _public prototype_ `FString ToString() const;` — Convert this value to a string
- L596 _public prototype_ `FString ToDebugString() const;` — Convert this value to a string with additional information
- L599 _public function_ `bool IsValid() const` — Is the Variant wrapped in this object valid
- L618 _public function_ `virtual void SetUniqueNetId(const FUniqueNetIdPtr& InUniqueNetId)` — Assign a unique id to this wrapper object @param InUniqueNetId id to associate
- L623 _public function_ `virtual void SetAccountId(const UE::Online::FAccountId& AccountId)`
- L629 _public function_ `FUniqueNetIdPtr GetUniqueNetId() const` — @return unique id associated with this wrapper object
- L637 _public function_ `const FUniqueNetId& operator*() const` — Dereference operator returns a reference to the FUniqueNetId
- L645 _public function_ `const FUniqueNetId* operator->() const` — Arrow operator returns a pointer to this FUniqueNetId
- L674 _public function_ `static FUniqueNetIdWrapper Invalid()`
- L775 _protected member_ `FVariantType Variant;` — Actual unique id

#### struct `TUniqueNetIdMapKeyFuncs`  
`template <typename ValueType> struct TUniqueNetIdMapKeyFuncs : public TDefaultMapKeyFuncs<FUniqueNetIdRef, ValueType, false>`  
_L779-784_
- inherits: `TDefaultMapKeyFuncs<FUniqueNetIdRef,ValueType,false>`
- L781 _public function_ `static FORCEINLINE FUniqueNetIdRef GetSetKey(TPair<FUniqueNetIdRef, ValueType> const& Element)`
- L782 _public function_ `static FORCEINLINE uint32 GetKeyHash(FUniqueNetIdRef const& Key)`
- L783 _public function_ `static FORCEINLINE bool Matches(FUniqueNetIdRef const& A, FUniqueNetIdRef const& B)`

#### struct `FUniqueNetIdKeyFuncs`  
`struct FUniqueNetIdKeyFuncs : public DefaultKeyFuncs<FUniqueNetIdRef>`  
_L789-794_
- inherits: `DefaultKeyFuncs<FUniqueNetIdRef>`
- L791 _public function_ `static FORCEINLINE FUniqueNetIdRef GetSetKey(FUniqueNetIdRef const& Element)`
- L792 _public function_ `static FORCEINLINE uint32 GetKeyHash(FUniqueNetIdRef const& Key)`
- L793 _public function_ `static FORCEINLINE bool Matches(FUniqueNetIdRef const& A, FUniqueNetIdRef const& B)`

#### Free symbols / members of external scopes

- L33 _macro_ `#define MAX_LOCAL_PLAYERS PLATFORM_MAX_LOCAL_PLAYERS`
- L35 _macro_ `#define MAX_LOCAL_PLAYERS 4`
- L37 _macro_ `#define MAX_LOCAL_PLAYERS 1`
- L125 _function_ `friend bool operator==(const FUniqueNetId& Lhs, const FUniqueNetId& Rhs)` — Comparison operator
- L130 _function_ `friend bool operator!=(const FUniqueNetId& Lhs, const FUniqueNetId& Rhs)`
- L197 _function_ `friend inline uint32 GetTypeHash(const FUniqueNetId& Value)`
- L203 _namespace_ `namespace UE`
- L203 _namespace_ `namespace Online` (scope `UE`)
- L208 _namespace_ `namespace OnlineIdHandleTags` (scope `UE::Online`)
- L291 _prototype_ `void RegisterAliasForGameDefined(EOnlineServices Value, const TCHAR* InStr);` (scope `UE::Online`)
- L292 _prototype_ `const TCHAR* LexToString(EOnlineServices Value);` (scope `UE::Online`)
- L293 _prototype_ `void LexFromString(EOnlineServices& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L300 _prototype_ `bool TEMP_ShouldUseEpicModularPlugins();` (scope `UE::Online`) — Temporary Signals that the EOnlineServices::Epic monolithic plugins should not be used, and EOnlineServices::EpicAccount/EpicGame should be used instead. This is a stepping stone to promoting the EOnlineServices::EpicAccount/EpicGame modular plugins and deprecating the monolithic ones.
- L331 _typedef_ `using FAccountId = TOnlineId<OnlineIdHandleTags::FAccount>;` (scope `UE::Online`)
- L332 _typedef_ `using FLobbyId = TOnlineId<OnlineIdHandleTags::FLobby>;` (scope `UE::Online`)
- L334 _typedef_ `using FOnlineSessionId = TOnlineId<OnlineIdHandleTags::FSession>;` (scope `UE::Online`) — TODO rename to FSessionId
- L335 _typedef_ `using FSessionInviteId = TOnlineId<OnlineIdHandleTags::FSessionInvite>;` (scope `UE::Online`)
- L336 _typedef_ `using FVerifiedAuthTicketId = TOnlineId<OnlineIdHandleTags::FVerifiedAuthTicket>;` (scope `UE::Online`)
- L337 _typedef_ `using FVerifiedAuthSessionId = TOnlineId<OnlineIdHandleTags::FVerifiedAuthSession>;` (scope `UE::Online`)
- L338 _typedef_ `using FLoginContinuationId = TOnlineId<OnlineIdHandleTags::FLoginContinuation>;` (scope `UE::Online`)
- L340 _prototype_ `FString ToString(const FAccountId& Id);` (scope `UE::Online`)
- L341 _prototype_ `FString ToString(const FOnlineSessionId& Id);` (scope `UE::Online`)
- L348 _prototype_ `FString ToLogString(const FAccountId& Id);` (scope `UE::Online`)
- L349 _prototype_ `FString ToLogString(const FLobbyId& Id);` (scope `UE::Online`)
- L350 _prototype_ `FString ToLogString(const FOnlineSessionId& Id);` (scope `UE::Online`)
- L351 _prototype_ `FString ToLogString(const FSessionInviteId& Id);` (scope `UE::Online`)
- L352 _prototype_ `FString ToLogString(const FVerifiedAuthTicketId& Id);` (scope `UE::Online`)
- L353 _prototype_ `FString ToLogString(const FVerifiedAuthSessionId& Id);` (scope `UE::Online`)
- L354 _prototype_ `FString ToLogString(const FLoginContinuationId& Id);` (scope `UE::Online`)
- L357 _function_ `template<typename IdType> inline uint32 GetTypeHash(const TOnlineId<IdType>& OnlineId)` (scope `UE::Online`)
- L376 _typedef_ `using IOnlineAccountIdRegistry = IOnlineIdRegistry<OnlineIdHandleTags::FAccount>;` (scope `UE::Online`)
- L377 _typedef_ `using IOnlineSessionIdRegistry = IOnlineIdRegistry<OnlineIdHandleTags::FSession>;` (scope `UE::Online`)
- L378 _typedef_ `using IOnlineSessionInviteIdRegistry = IOnlineIdRegistry<OnlineIdHandleTags::FSessionInvite>;` (scope `UE::Online`)
- L653 _function_ `friend inline uint32 GetTypeHash(const FUniqueNetIdWrapper& Value)` — Friend function for using FUniqueNetIdWrapper as a hashable key
- L669 _function_ `friend FString LexToString(const FUniqueNetIdWrapper& Value)`
- L680 _function_ `friend bool operator==(const FUniqueNetIdWrapper& Lhs, const FUniqueNetIdWrapper& Rhs)`
- L710 _function_ `friend bool operator!=(const FUniqueNetIdWrapper& Lhs, const FUniqueNetIdWrapper& Rhs)`
- L715 _function_ `friend bool operator==(const FUniqueNetIdWrapper& Lhs, const FUniqueNetId& Rhs)`
- L736 _function_ `friend bool operator!=(const FUniqueNetIdWrapper& Lhs, const FUniqueNetId& Rhs)`
- L741 _function_ `friend bool operator==(const FUniqueNetId& Lhs, const FUniqueNetIdWrapper& Rhs)`
- L746 _function_ `friend bool operator!=(const FUniqueNetId& Lhs, const FUniqueNetIdWrapper& Rhs)`
- L752 _function_ `friend bool operator==(const FUniqueNetIdWrapper& NetIdWrapper, TYPE_OF_NULLPTR)` — comparison with nullptr (alternative to IsValid)
- L757 _function_ `friend bool operator!=(const FUniqueNetIdWrapper& NetIdWrapper, TYPE_OF_NULLPTR)`
- L762 _function_ `friend bool operator==(TYPE_OF_NULLPTR, const FUniqueNetIdWrapper& NetIdWrapper)`
- L767 _function_ `friend bool operator!=(TYPE_OF_NULLPTR, const FUniqueNetIdWrapper& NetIdWrapper)`
- L787 _typedef_ `template <typename ValueType> using TUniqueNetIdMap = TMap<FUniqueNetIdRef, ValueType, FDefaultSetAllocator, TUniqueNetIdMapKeyFuncs<ValueType>>;`
- L796 _typedef_ `using FUniqueNetIdSet = TSet<FUniqueNetIdRef, FUniqueNetIdKeyFuncs>;`

### `Source/Runtime/CoreOnline/Public/Online/CoreOnlineFwd.h` (Public)


#### Free symbols / members of external scopes

- L10 _typedef_ `using FUniqueNetIdPtr = TSharedPtr<const FUniqueNetId>;`
- L11 _typedef_ `using FUniqueNetIdRef = TSharedRef<const FUniqueNetId>;`
- L12 _typedef_ `using FUniqueNetIdWeakPtr = TWeakPtr<const FUniqueNetId>;`

### `Source/Runtime/CoreOnline/Public/Online/CoreOnlinePackage.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define PACKAGE_SCOPE public`
- L9 _macro_ `#define PACKAGE_SCOPE protected`

### `Source/Runtime/CoreOnline/Public/Online/NestedVariant.h` (Public)


#### class `TVariantArray`  
`template<typename... ValueTypes> class TVariantArray : public TArray<TVariant<ValueTypes...>>, public TSharedFromThis<TVariantArray<ValueTypes...>>`  
_L56-126_
- inherits: `TArray<TVariant<ValueTypes...>>,TSharedFromThis<TVariantArray<ValueTypes...>>`
- desc: TArray that holds a TVariant with helper functions for working with variant types.
- L59 _public typedef_ `using VariantType = TVariant<ValueTypes...>;`
- L60 _public typedef_ `using ArrayType = TArray<VariantType>;`
- L62 _public function_ `static TSharedRef<TVariantArray<ValueTypes...>> CreateVariant()`
- L68 _public function_ `template<typename ValueType, typename VariantValueType = std::remove_cv_t<std::remove_reference_t<ValueType>>> VariantValueType& AddVariant(ValueType&& Value)`
- L74 _public function_ `template<typename ValueType> void AddVariantArray(const TArray<ValueType>& Array)`
- L83 _public function_ `template<typename ValueType> bool GetVariant(ArrayType::SizeType Index, TSharedPtr<ValueType>& OutValue) const`
- L98 _public function_ `template<typename ValueType> bool GetVariant(ArrayType::SizeType Index, ValueType& OutValue) const`
- L113 _public function_ `template<typename ValueType> bool GetVariantArray(TArray<ValueType>& OutValue) const`

#### class `TVariantMap`  
`template<typename KeyType, typename... ValueTypes> class TVariantMap : public TMap<KeyType, TVariant<ValueTypes...>>, public TSharedFromThis<TVariantMap<KeyType, ValueTypes...>>`  
_L130-200_
- inherits: `TMap<KeyType,TVariant<ValueTypes...>>,TSharedFromThis<TVariantMap<KeyType,ValueTypes...>>`
- desc: TMap that holds a TVariant with helper functions for working with variant types.
- L133 _public typedef_ `using VariantType = TVariant<ValueTypes...>;`
- L134 _public typedef_ `using MapType = TMap<KeyType, VariantType>;`
- L136 _public function_ `static TSharedRef<TVariantMap<KeyType, ValueTypes...>> CreateVariant()`
- L142 _public function_ `template<typename ValueType, typename AddKeyType, typename VariantValueType = std::remove_cv_t<std::remove_reference_t<ValueType>>> VariantValueType& AddVariant(AddKeyType&& Key, ValueType&& Value)`
- L148 _public function_ `template<typename ValueType> void AddVariantMap(const TMap<KeyType, ValueType>& Map)`
- L157 _public function_ `template<typename ValueType, typename GetKeyType> bool GetVariant(const GetKeyType& Key, TSharedPtr<ValueType>& OutValue) const`
- L172 _public function_ `template<typename ValueType, typename GetKeyType> bool GetVariant(const GetKeyType& Key, ValueType& OutValue) const`
- L187 _public function_ `template<typename ValueType> bool GetVariantMap(TMap<KeyType, ValueType>& OutValue) const`

#### struct `UE::Online::NestedVariant::TRecursionScope`  
`template<typename VisitType, int32 MaxDepth> struct TRecursionScope`  
_L266-332_
- desc: Recursion protection for nested composites.
- L268 _public member_ `TGuardType<VisitType>& Visited;`
- L269 _public member_ `VisitType ID;`
- L270 _public member_ `bool bSuccess = false;`
- L272 _public prototype_ `TRecursionScope() = delete;`
- L274 _public function_ `TRecursionScope(TGuardType<VisitType>& InVisited, const void* InID) : Visited(InVisited), ID(MakeID(InID))`
- L279 _public function_ `TRecursionScope(TGuardType<VisitType>& InVisited, const void* InLeft, const void* InRight) : Visited(InVisited), ID(MakeID(InLeft, InRight))`
- L284 _public function_ `~TRecursionScope()`
- L293 _public function_ `[[nodiscard]] explicit operator bool() const`
- L295 _public function_ `[[nodiscard]] FString GetError() const`
- L315 _private function_ `void Enter()`

#### class `TNestedVariantArray`  
`template<typename KeyType, typename... ValueTypes> class TNestedVariantArray : public TVariantArray<ValueTypes..., TNestedVariantArrayRef<KeyType, ValueTypes...>, TNestedVariantMapRef<KeyType, ValueTypes...>>`  
_L627-657_
- inherits: `TVariantArray<ValueTypes...,TNestedVariantArrayRef<KeyType,ValueTypes...>,TNestedVariantMapRef<KeyType,ValueTypes...>>`
- desc: Nested TVariantArray that can hold all provided types plus nested array and map references.
- L630 _public function_ `static TNestedVariantArrayRef<KeyType, ValueTypes...> CreateVariant()`
- L634 _public function_ `bool operator==(const TNestedVariantArray& Other) const`
- L641 _public function_ `bool operator!=(const TNestedVariantArray& Other) const`
- L647 _public function_ `template<int32 MaxDepth = 32, int32 TabOffset = 0> void ToDebugString(FString& OutString) const`

#### class `TNestedVariantMap`  
`template<typename KeyType, typename... ValueTypes> class TNestedVariantMap : public TVariantMap<KeyType, ValueTypes..., TNestedVariantArrayRef<KeyType, ValueTypes...>, TNestedVariantMapRef<KeyType, ValueTypes...>>`  
_L661-691_
- inherits: `TVariantMap<KeyType,ValueTypes...,TNestedVariantArrayRef<KeyType,ValueTypes...>,TNestedVariantMapRef<KeyType,ValueTypes...>>`
- desc: Nested TVariantMap that can hold all provided types plus nested array and map references.
- L664 _public function_ `static TNestedVariantMapRef<KeyType, ValueTypes...> CreateVariant()`
- L668 _public function_ `bool operator==(const TNestedVariantMap& Other) const`
- L675 _public function_ `bool operator!=(const TNestedVariantMap& Other) const`
- L681 _public function_ `template<int32 MaxDepth = 32, int32 TabOffset = 0> void ToDebugString(FString& OutString) const`

#### class `TNestedVariant`  
`template<typename KeyType, typename... ValueTypes> class TNestedVariant`  
_L695-707_
- desc: Convenience class to declare all nested types at once.
- L698 _public typedef_ `using FArray = TNestedVariantArray<KeyType, ValueTypes...>;`
- L699 _public typedef_ `using FArrayRef = TNestedVariantArrayRef<KeyType, ValueTypes...>;`
- L700 _public typedef_ `using FArrayPtr = TNestedVariantArrayPtr<KeyType, ValueTypes...>;`
- L702 _public typedef_ `using FMap = TNestedVariantMap<KeyType, ValueTypes...>;`
- L703 _public typedef_ `using FMapRef = TNestedVariantMapRef<KeyType, ValueTypes...>;`
- L704 _public typedef_ `using FMapPtr = TNestedVariantMapPtr<KeyType, ValueTypes...>;`
- L706 _public typedef_ `using FValue = FNestedVariantValue<KeyType, ValueTypes...>;`

#### Free symbols / members of external scopes

- L207 _typedef_ `template<typename KeyType, typename... ValueTypes> class TNestedVariantArray;`
- L208 _typedef_ `template<typename KeyType, typename... ValueTypes> class TNestedVariantArray;`
- L211 _typedef_ `template<typename KeyType, typename... ValueTypes> class TNestedVariantMap;`
- L212 _typedef_ `template<typename KeyType, typename... ValueTypes> class TNestedVariantMap;`
- L214 _typedef_ `template<typename KeyType, typename... ValueTypes> using FNestedVariantValue = TVariant<ValueTypes..., TNestedVariantArrayRef<KeyType, ValueTypes...>, TNestedVariantMapRef<KeyType, ValueTypes...>>;`
- L218 _namespace_ `namespace UE`
- L218 _namespace_ `namespace Online` (scope `UE`)
- L218 _namespace_ `namespace NestedVariant` (scope `UE::Online`)
- L221 _typedef_ `template<typename VisitType> using TGuardType = TSet<VisitType>;` (scope `UE::Online::NestedVariant`)
- L224 _typedef_ `using FSingleType = const void*;` (scope `UE::Online::NestedVariant`) — Single void* methods for use with AppendArray and AppendMap.
- L225 _typedef_ `using FSingleVisit = TGuardType<FSingleType>;` (scope `UE::Online::NestedVariant`)
- L227 _function_ `[[nodiscard]] inline FSingleType MakeID(const void* InID)` (scope `UE::Online::NestedVariant`)
- L232 _function_ `[[nodiscard]] inline bool ContainsID(const FSingleVisit& VisitSet, FSingleType ID)` (scope `UE::Online::NestedVariant`)
- L237 _function_ `[[nodiscard]] inline FString ToString(FSingleType InID)` (scope `UE::Online::NestedVariant`)
- L244 _typedef_ `using FDualType = TPair<const void*, const void*>;` (scope `UE::Online::NestedVariant`) — Dual void* methods for use with Array and Map operator==.
- L245 _typedef_ `using FDualVisit = TGuardType<FDualType>;` (scope `UE::Online::NestedVariant`)
- L247 _function_ `[[nodiscard]] inline FDualType MakeID(const void* Left, const void* Right)` (scope `UE::Online::NestedVariant`)
- L252 _function_ `[[nodiscard]] inline bool ContainsID(const FDualVisit& VisitSet, FDualType& ID)` (scope `UE::Online::NestedVariant`)
- L258 _function_ `[[nodiscard]] inline FString ToString(FDualType InPair)` (scope `UE::Online::NestedVariant`)
- L336 _function_ `template<int32 MaxDepth, typename KeyType, typename... ValueTypes, typename T> [[nodiscard]] bool Compare(const T& Lhs, const T& Rhs, FDualVisit& )` (scope `UE::Online::NestedVariant`) — Comparison functions for use with operator==.
- L343 _prototype_ `template<int32 MaxDepth, typename KeyType, typename... ValueTypes> [[nodiscard]] bool CompareVariants(const FNestedVariantValue<KeyType, ValueTypes...>& Lhs, const FNestedVariantValue<KeyType, ValueTypes...>& Rhs, FDualVisit& VisitedSet);` (scope `UE::Online::NestedVariant`) — Forward declaration for use in various Compare functions.
- L347 _function_ `template<int32 MaxDepth, typename KeyType, typename... ValueTypes> [[nodiscard]] bool Compare(const TNestedVariantArray<KeyType, ValueTypes...>& Lhs, const TNestedVariantArray<KeyType, ValueTypes...>& Rhs, FDualVisit& Visited)` (scope `UE::Online::NestedVariant`) — TNestedVariantArray comparison.
- L349 _typedef_ `using ThisType = TVariantArray<ValueTypes..., TNestedVariantArrayRef<KeyType, ValueTypes...>, TNestedVariantMapRef<KeyType, ValueTypes...>>;` (scope `UE::Online::NestedVariant::Compare`)
- L386 _function_ `template<int32 MaxDepth, typename KeyType, typename... ValueTypes> [[nodiscard]] bool Compare(const TNestedVariantArrayRef<KeyType, ValueTypes...>& Lhs, const TNestedVariantArrayRef<KeyType, ValueTypes...>& Rhs, FDualVisit& Visited)` (scope `UE::Online::NestedVariant`) — Dereference TNestedVariantArrayRef to TNestedVariantArray.
- L393 _function_ `template<int32 MaxDepth, typename KeyType, typename... ValueTypes> [[nodiscard]] bool Compare(const TNestedVariantMap<KeyType, ValueTypes...>& Lhs, const TNestedVariantMap<KeyType, ValueTypes...>& Rhs, FDualVisit& Visited)` (scope `UE::Online::NestedVariant`) — TNestedVariantMap comparison.
- L395 _typedef_ `using ThisType = TVariantMap<KeyType, ValueTypes..., TNestedVariantArrayRef<KeyType, ValueTypes...>, TNestedVariantMapRef<KeyType, ValueTypes...>>;` (scope `UE::Online::NestedVariant::Compare`)
- L396 _typedef_ `using MapType = typename ThisType::MapType;` (scope `UE::Online::NestedVariant::Compare`)
- L397 _typedef_ `using VariantType = typename ThisType::VariantType;` (scope `UE::Online::NestedVariant::Compare`)
- L443 _function_ `template<int32 MaxDepth, typename KeyType, typename... ValueTypes> [[nodiscard]] bool Compare(const TNestedVariantMapRef<KeyType, ValueTypes...>& Lhs, const TNestedVariantMapRef<KeyType, ValueTypes...>& Rhs, FDualVisit& Visited)` (scope `UE::Online::NestedVariant`) — Dereference TNestedVariantMapRef to TNestedVariantMap.
- L449 _function_ `template<int32 MaxDepth, typename KeyType, typename... ValueTypes> [[nodiscard]] bool CompareVariants(const FNestedVariantValue<KeyType, ValueTypes...>& Lhs, const FNestedVariantValue<KeyType, ValueTypes...>& Rhs, FDualVisit& VisitedSet)` (scope `UE::Online::NestedVariant`)
- L452 _function_ `` (scope `UE::Online::NestedVariant::CompareVariants`)
- L453 _typedef_ `using LeftDecayed = std::decay_t<decltype(LVisited)>;` (scope `UE::Online::NestedVariant::CompareVariants::__anon98f97cb60102`)
- L454 _typedef_ `using RightDecayed = std::decay_t<decltype(RVisited)>;` (scope `UE::Online::NestedVariant::CompareVariants::__anon98f97cb60102`)
- L467 _function_ `inline void AppendIndent(FString& OutString, int32 TabDepth)` (scope `UE::Online::NestedVariant`) — String appending methods for use with ToDebugString().
- L477 _prototype_ `template<int32 MaxDepth, int32 TabOffset, typename KeyType, typename... ValueTypes> void AppendArray(const TNestedVariantArray<KeyType, ValueTypes...>& Array, FString& OutString, FSingleVisit& Visited);` (scope `UE::Online::NestedVariant`) — Forward declarations used in AppendVariant.
- L480 _prototype_ `template<int32 MaxDepth, int32 TabOffset, typename KeyType, typename... ValueTypes> void AppendMap(const TNestedVariantMap<KeyType, ValueTypes...>& Map, FString& OutString, FSingleVisit& Visited);` (scope `UE::Online::NestedVariant`)
- L483 _function_ `template<typename T> inline void AppendValue(FString& OutString, const T& V)` (scope `UE::Online::NestedVariant`)
- L488 _function_ `inline void AppendValue(FString& OutString, const FString& S)` (scope `UE::Online::NestedVariant`)
- L493 _function_ `inline void AppendValue(FString& OutString, double Double, int32 Precision)` (scope `UE::Online::NestedVariant`)
- L499 _function_ `template<int32 MaxDepth, int32 TabOffset, bool bAfterKey, typename KeyType, typename... ValueTypes> void AppendVariant(const FNestedVariantValue<KeyType, ValueTypes...>& Variant, FString& OutString, FSingleVisit& VisitedSet)` (scope `UE::Online::NestedVariant`)
- L502 _function_ `` (scope `UE::Online::NestedVariant::AppendVariant`)
- L503 _typedef_ `using DecayedType = std::decay_t<decltype(Visited)>;` (scope `UE::Online::NestedVariant::AppendVariant::__anon98f97cb60202`)
- L550 _function_ `template<int32 MaxDepth, int32 TabOffset, typename KeyType, typename... ValueTypes> void AppendArray(const TNestedVariantArray<KeyType, ValueTypes...>& Array, FString& OutString, FSingleVisit& Visited)` (scope `UE::Online::NestedVariant`)
- L584 _function_ `template<int32 MaxDepth, int32 TabOffset, typename KeyType, typename... ValueTypes> void AppendMap(const TNestedVariantMap<KeyType, ValueTypes...>& Map, FString& OutString, FSingleVisit& Visited)` (scope `UE::Online::NestedVariant`)
- L586 _typedef_ `using ThisType = TVariantMap<KeyType, ValueTypes..., TNestedVariantArrayRef<KeyType, ValueTypes...>, TNestedVariantMapRef <KeyType, ValueTypes...>>;` (scope `UE::Online::NestedVariant::AppendMap`)
- L587 _typedef_ `using MapType = typename ThisType::MapType;` (scope `UE::Online::NestedVariant::AppendMap`)
- L588 _typedef_ `using VariantType = FNestedVariantValue<KeyType, ValueTypes...>;` (scope `UE::Online::NestedVariant::AppendMap`)

### `Source/Runtime/CoreOnline/Public/Online/NestedVariantJson.h` (Public)


#### struct `FJsonSerializerPolicy_NestedVariant`  
`struct FJsonSerializerPolicy_NestedVariant`  
_L28-312_
- L30 _public typedef_ `using FValue = FNestedVariantJson::FValue;`
- L31 _public typedef_ `using FArrayOfValues = FNestedVariantJson::FArrayPtr;`
- L32 _public typedef_ `using FMapOfValues = FNestedVariantJson::FMapPtr;`
- L80 _public prototype_ `static bool GetValueFromState(const FStackState& State, FValue& OutValue);`
- L81 _public prototype_ `static bool GetValueFromState(const FStackState& State, FArrayOfValues& OutArray);`
- L82 _public prototype_ `static bool GetValueFromState(const FStackState& State, FMapOfValues& OutMap);`
- L83 _public prototype_ `static void ResetValue(FValue& OutValue);`
- L84 _public prototype_ `static void ReadObjectStart(FStackState& State);`
- L85 _public prototype_ `static void ReadObjectEnd(FStackState& State, FValue& OutValue);`
- L86 _public prototype_ `static void ReadArrayStart(FStackState& State);`
- L87 _public prototype_ `static void ReadArrayEnd(FStackState& State, FValue& OutValue);`
- L90 _public function_ `template<class CharType> static void ReadBoolean(TJsonReader<CharType>& Reader, FValue& OutValue)`
- L96 _public function_ `template<class CharType> static void ReadString(TJsonReader<CharType>& Reader, FValue& OutValue)`
- L102 _public function_ `template<class CharType> static void ReadNumberAsString(TJsonReader<CharType>& Reader, FValue& OutValue)`
- L108 _public function_ `template<class CharType> static bool IsNumberStringInteger(const CharType* Str)`
- L133 _public function_ `template<class CharType> static void ReadNumber(TJsonReader<CharType>& Reader, FValue& OutValue)`
- L146 _public prototype_ `static void ReadNull(FValue& OutValue);`
- L147 _public prototype_ `static void AddValueToObject(FStackState& State, const FString& Identifier, FValue& NewValue);`
- L148 _public prototype_ `static void AddValueToArray(FStackState& State, FValue& NewValue);`
- L151 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfBool(TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`
- L171 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfNumber(TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`
- L204 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfString(TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`
- L224 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfNull(TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`
- L230 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfArray(TArray<TSharedRef<FElement>>& ElementStack, TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`
- L267 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfObject(TArray<TSharedRef<FElement>>& ElementStack, TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`

#### struct `FJsonSerializerPolicy_NestedVariant::FGlobalState`  
`struct FGlobalState`  
_L34-36_

#### struct `FJsonSerializerPolicy_NestedVariant::FStackState`  
`struct FStackState`  
_L38-47_
- L40 _public prototype_ `FStackState() = default;`
- L41 _public function_ `explicit FStackState(const FGlobalState&)`
- L43 _public member_ `EJson Type;`
- L44 _public member_ `FString Identifier;`
- L45 _public member_ `FNestedVariantJson::FArrayPtr Array;`
- L46 _public member_ `FNestedVariantJson::FMapPtr Object;`

#### struct `FJsonSerializerPolicy_NestedVariant::FElement`  
`struct FElement`  
_L49-78_
- L51 _public function_ `FElement( const FValue& InValue ) : Identifier() , Value(InValue)`
- L56 _public function_ `FElement( const FMapOfValues& Object ) : Identifier()`
- L62 _public function_ `FElement( const FArrayOfValues& Array ) : Identifier()`
- L68 _public function_ `FElement( const FString& InIdentifier, const FValue& InValue ) : Identifier( InIdentifier ) , Value( InValue ) , bIsKeyValuePair( true )`
- L74 _public member_ `FString Identifier;`
- L75 _public member_ `FValue Value;`
- L76 _public member_ `bool bHasBeenProcessed = false;`
- L77 _public member_ `bool bIsKeyValuePair = false;`

#### Free symbols / members of external scopes

- L13 _typedef_ `using FNestedVariantJson = TNestedVariant<FString, bool, int64, double, FString>;`
- L17 _prototype_ `FString NestedVariantToJson(const FNestedVariantJson::FMapPtr& Map);`
- L18 _prototype_ `TSharedRef<FJsonObject> NestedVariantToJsonObject(const FNestedVariantJson::FMapRef& Map);`
- L19 _prototype_ `TSharedRef<FJsonObject> NestedVariantToJsonObject(const FNestedVariantJson::FMap& Map);`
- L21 _prototype_ `void NestedVariantFromJson(const char* InJson, FNestedVariantJson::FMapRef& Map);`
- L22 _prototype_ `void NestedVariantFromJson(const char* InJson, FNestedVariantJson::FMap& Map);`
- L23 _prototype_ `void NestedVariantFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject, FNestedVariantJson::FMapRef& Map);`
- L24 _prototype_ `void NestedVariantFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject, FNestedVariantJson::FMap& Map);`
- L26 _prototype_ `void LexFromString(FNestedVariantJson::FMap& OutValue, const TCHAR* InString);`
