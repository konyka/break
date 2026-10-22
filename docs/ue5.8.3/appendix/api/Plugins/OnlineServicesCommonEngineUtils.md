# Plugins / OnlineServicesCommonEngineUtils

- module root: `Plugins/Online/OnlineServices/Source/OnlineServicesCommonEngineUtils`
- headers: 3; symbols: 49
- symbol kinds: class=4, function=5, macro=1, member=5, namespace=5, prototype=27, typedef=2
- PrivateDependencyModuleNames: Core, CoreOnline, CoreUObject, OnlineBase, OnlineServicesCommon, OnlineServicesInterface, Sockets
- PublicDependencyModuleNames: Engine

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommonEngineUtils/Public/Online/OnlineServicesCommonEngineUtils.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L11 _prototype_ `int32 GetPortFromNetDriver(FName InstanceName);` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommonEngineUtils/Public/Online/SessionsLAN.h` (Public)


#### class `UE::Online::FOnlineSessionIdRegistryLAN`  
`class FOnlineSessionIdRegistryLAN : public FOnlineSessionIdStringRegistry`  
_L18-27_
- inherits: `FOnlineSessionIdStringRegistry`
- L21 _public prototype_ `static FOnlineSessionIdRegistryLAN& GetChecked(EOnlineServices ServicesType);`
- L23 _public prototype_ `FOnlineSessionId GetNextSessionId();`
- L26 _protected prototype_ `FOnlineSessionIdRegistryLAN(EOnlineServices ServicesType);`

#### class `UE::Online::FSessionLAN`  
`class FSessionLAN : public FSessionCommon`  
_L29-45_
- inherits: `FSessionCommon`
- L32 _public prototype_ `FSessionLAN();`
- L34 _public prototype_ `static FSessionLAN& Cast(FSessionCommon& InSession);`
- L35 _public prototype_ `static const FSessionLAN& Cast(const ISession& InSession);`
- L37 _public prototype_ `virtual void DumpState() const override;`
- L40 _private prototype_ `void Initialize();`
- L44 _public member_ `TSharedPtr<FInternetAddr> OwnerInternetAddr;` — The IP address for the session owner

#### class `UE::Online::FSessionsLAN`  
`class FSessionsLAN : public FSessionsCommon`  
_L54-86_
- inherits: `FSessionsCommon`
- L57 _public typedef_ `using Super = FSessionsCommon;`
- L59 _public prototype_ `FSessionsLAN(FOnlineServicesCommon& InServices);`
- L62 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L65 _public prototype_ `virtual TFuture<TOnlineResult<FCreateSession>> CreateSessionImpl(const FCreateSession::Params& Params) override;` — FSessionsCommon
- L66 _public prototype_ `virtual TFuture<TOnlineResult<FUpdateSessionSettings>> UpdateSessionSettingsImpl(const FUpdateSessionSettings::Params& Params) override;`
- L67 _public prototype_ `virtual TFuture<TOnlineResult<FLeaveSession>> LeaveSessionImpl(const FLeaveSession::Params& Params) override;`
- L68 _public prototype_ `virtual TFuture<TOnlineResult<FFindSessions>> FindSessionsImpl(const FFindSessions::Params& Params) override;`
- L69 _public prototype_ `virtual TFuture<TOnlineResult<FJoinSession>> JoinSessionImpl(const FJoinSession::Params& Params) override;`
- L72 _protected typedef_ `using FHostSessionResult = TValueOrError<void, FOnlineError>;`
- L74 _protected prototype_ `FHostSessionResult TryHostLANSession();`
- L75 _protected prototype_ `TSharedRef<FSessionLAN> AddLANSession(const FCreateSession::Params& Params);`
- L76 _protected prototype_ `void FindLANSessions(const FAccountId& LocalAccountId);`
- L77 _protected prototype_ `void StopLANSession();`
- L78 _protected prototype_ `void OnValidQueryPacketReceived(uint8* PacketData, int32 PacketLength, uint64 ClientNonce);`
- L79 _protected prototype_ `void OnValidResponsePacketReceived(uint8* PacketData, int32 PacketLength, const FAccountId LocalAccountId);`
- L80 _protected prototype_ `void OnLANSearchTimeout(const FAccountId LocalAccountId);`
- L81 _protected prototype_ `virtual void AppendSessionToPacket(FNboSerializeToBuffer& Packet, const FSessionLAN& Session) = 0;`
- L82 _protected prototype_ `virtual void ReadSessionFromPacket(FNboSerializeFromBuffer& Packet, FSessionLAN& Session) = 0;`
- L84 _protected member_ `TSharedPtr<FSessionLAN> HostedLANSession = nullptr;`
- L85 _protected member_ `TSharedRef<FLANSession> LANSessionManager;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ONLINESERVICESCOMMONENGINEUTILS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)
- L47 _namespace_ `namespace NboSerializerLANSvc` (scope `UE::Online`)
- L49 _prototype_ `void SerializeToBuffer(FNboSerializeToBuffer& Packet, const FSessionLAN& Session);` (scope `UE::Online::NboSerializerLANSvc`)
- L50 _prototype_ `void SerializeFromBuffer(FNboSerializeFromBuffer& Packet, FSessionLAN& Session);` (scope `UE::Online::NboSerializerLANSvc`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesCommonEngineUtils/Public/Online/WorldContextScopedObjectCache.h` (Public)


#### class `FWorldContextScopedObjectCache`  
`template<typename ObjectType> class FWorldContextScopedObjectCache`  
_L18-79_
- desc: Object cache keyed by world context name that verifies a world context exists before creating a new entry. It also automatically cleans up objects when PIE worlds end after the world contexts have been destroyed.
- L21 _public function_ `FWorldContextScopedObjectCache()`
- L40 _public function_ `~FWorldContextScopedObjectCache()`
- L47 _public function_ `TSharedPtr<ObjectType> FindOrAdd(FName ContextName, const TFunctionRef<TSharedRef<ObjectType>()>& Create, bool bSkipWorldContextCheck = false)`
- L69 _public function_ `void Clear(FName ContextName)` — Explicitly clear an object for the given context name. Expected to only be used in strictly controlled scenarios, such as automated tests.
- L75 _private member_ `TMap<FName, TSharedRef<ObjectType>> Objects;`
- L77 _private member_ `FDelegateHandle EndPlayMapDelegateHandle;`

#### Free symbols / members of external scopes

- L26 _function_ `` (scope `FWorldContextScopedObjectCache::FWorldContextScopedObjectCache`)
