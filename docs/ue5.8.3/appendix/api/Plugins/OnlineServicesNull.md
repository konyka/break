# Plugins / OnlineServicesNull

- module root: `Plugins/Online/OnlineServicesNull/Source`
- headers: 14; symbols: 223
- symbol kinds: class=16, function=16, macro=7, member=31, namespace=28, prototype=106, struct=5, typedef=14
- PrivateDependencyModuleNames: ApplicationCore, OnlineBase, OnlineServicesCommonEngineUtils
- PublicDependencyModuleNames: Core, CoreOnline, OnlineServicesCommon, OnlineServicesInterface, OnlineSubsystem, Sockets

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/AchievementsNull.h` (Public)


#### struct `UE::Online::FAchievementsNullConfig`  
`struct FAchievementsNullConfig`  
_L14-17_
- L16 _public member_ `TArray<FAchievementDefinition> AchievementDefinitions;`

#### class `UE::Online::FAchievementsNull`  
`class FAchievementsNull : public FAchievementsCommon`  
_L27-55_
- inherits: `FAchievementsCommon`
- L30 _public typedef_ `using Super = FAchievementsCommon;`
- L32 _public prototype_ `FAchievementsNull(FOnlineServicesNull& InOwningSubsystem);`
- L35 _public prototype_ `virtual void UpdateConfig() override;` — IOnlineComponent
- L38 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementDefinitions> QueryAchievementDefinitions(FQueryAchievementDefinitions::Params&& Params) override;` — IAchievements
- L39 _public prototype_ `virtual TOnlineResult<FGetAchievementIds> GetAchievementIds(FGetAchievementIds::Params&& Params) override;`
- L40 _public prototype_ `virtual TOnlineResult<FGetAchievementDefinition> GetAchievementDefinition(FGetAchievementDefinition::Params&& Params) override;`
- L41 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementStates> QueryAchievementStates(FQueryAchievementStates::Params&& Params) override;`
- L42 _public prototype_ `virtual TOnlineResult<FGetAchievementState> GetAchievementState(FGetAchievementState::Params&& Params) const override;`
- L43 _public prototype_ `virtual TOnlineAsyncOpHandle<FUnlockAchievements> UnlockAchievements(FUnlockAchievements::Params&& Params) override;`
- L44 _public prototype_ `virtual TOnlineResult<FDisplayAchievementUI> DisplayAchievementUI(FDisplayAchievementUI::Params&& Params) override;`
- L47 _protected typedef_ `using FAchievementDefinitionMap = TMap<FString, FAchievementDefinition>;`
- L48 _protected typedef_ `using FAchievementStateMap = TMap<FString, FAchievementState>;`
- L50 _protected member_ `bool bAchievementDefinitionsQueried = false;`
- L52 _protected member_ `FAchievementsNullConfig Config;`
- L54 _protected prototype_ `const FAchievementDefinition* FindAchievementDefinition(const FString& AchievementId) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESNULL_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L19 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/AuthNull.h` (Public)


#### class `UE::Online::FOnlineAccountIdRegistryNull`  
`class FOnlineAccountIdRegistryNull : public IOnlineAccountIdRegistry`  
_L16-38_
- inherits: `IOnlineAccountIdRegistry`
- L20 _public prototype_ `static FOnlineAccountIdRegistryNull& Get();`
- L22 _public prototype_ `FAccountId Find(const FString& AccountId) const;`
- L23 _public prototype_ `FAccountId FindOrAddAccountId(const FString& AccountId);`
- L26 _public prototype_ `virtual FString ToString(const FAccountId& AccountId) const override;`
- L27 _public prototype_ `virtual FString ToLogString(const FAccountId& AccountId) const override;`
- L28 _public prototype_ `virtual TArray<uint8> ToReplicationData(const FAccountId& AccountId) const override;`
- L29 _public prototype_ `virtual FAccountId FromReplicationData(const TArray<uint8>& ReplicationString) override;`
- L30 _public prototype_ `virtual FAccountId FromStringData(const FString& StringData) override;`
- L33 _public prototype_ `virtual ~FOnlineAccountIdRegistryNull() = default;`
- L36 _private prototype_ `FOnlineAccountIdRegistryNull();`
- L37 _private member_ `TOnlineBasicAccountIdRegistry<FString> Registry;`

#### struct `UE::Online::FAccountInfoNull`  
`struct FAccountInfoNull final : public FAccountInfo`  
_L41-43_
- inherits: `FAccountInfo`

#### class `UE::Online::FAccountInfoRegistryNULL`  
`class FAccountInfoRegistryNULL final : public FAccountInfoRegistry`  
_L48-60_
- inherits: `FAccountInfoRegistry`
- desc: Auth NULL is implemented in a way similar to console platforms where there is not an explicit login / logout from online services. On those platforms the user account is picked either before the game has started or as a part of selecting an input device.
- L51 _public typedef_ `using Super = FAccountInfoRegistry;`
- L53 _public prototype_ `virtual ~FAccountInfoRegistryNULL() = default;`
- L55 _public prototype_ `TSharedPtr<FAccountInfoNull> Find(FPlatformUserId PlatformUserId) const;`
- L56 _public prototype_ `TSharedPtr<FAccountInfoNull> Find(FAccountId AccountIdHandle) const;`
- L58 _public prototype_ `void Register(const TSharedRef<FAccountInfoNull>&UserAuthData);`
- L59 _public prototype_ `void Unregister(FAccountId AccountId);`

#### class `UE::Online::FAuthNull`  
`class FAuthNull : public FAuthCommon`  
_L62-79_
- inherits: `FAuthCommon`
- L65 _public typedef_ `using Super = FAuthCommon;`
- L67 _public prototype_ `FAuthNull(FOnlineServicesNull& InOwningSubsystem);`
- L68 _public prototype_ `virtual void Initialize() override;`
- L69 _public prototype_ `virtual void PreShutdown() override;`
- L72 _protected prototype_ `virtual const FAccountInfoRegistry& GetAccountInfoRegistry() const override;`
- L74 _protected prototype_ `void InitializeUsers();`
- L75 _protected prototype_ `void UninitializeUsers();`
- L76 _protected prototype_ `void OnInputDeviceConnectionChange(EInputDeviceConnectionState NewConnectionState, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId);`
- L78 _protected member_ `FAccountInfoRegistryNULL AccountInfoRegistryNULL;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ONLINESERVICESNULL_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/LeaderboardsNull.h` (Public)


#### struct `UE::Online::FUserScoreNull`  
`struct FUserScoreNull`  
_L15-19_
- L17 _public member_ `FAccountId AccountId;`
- L18 _public member_ `uint64 Score;`

#### struct `UE::Online::FLeaderboardDataNull`  
`struct FLeaderboardDataNull`  
_L21-25_
- L23 _public member_ `FString Name;`
- L24 _public member_ `TDoubleLinkedList<FUserScoreNull> UserScoreList;`

#### class `UE::Online::FLeaderboardsNull`  
`class FLeaderboardsNull : public FLeaderboardsCommon`  
_L27-44_
- inherits: `FLeaderboardsCommon`
- L30 _public typedef_ `using Super = FLeaderboardsCommon;`
- L32 _public prototype_ `FLeaderboardsNull(FOnlineServicesNull& InOwningSubsystem);`
- L35 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesForUsers> ReadEntriesForUsers(FReadEntriesForUsers::Params&& Params) override;` — ILeaderboards
- L36 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesAroundRank> ReadEntriesAroundRank(FReadEntriesAroundRank::Params&& Params) override;`
- L37 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesAroundUser> ReadEntriesAroundUser(FReadEntriesAroundUser::Params&& Params) override;`
- L40 _public prototype_ `virtual TOnlineAsyncOpHandle<FWriteLeaderboardScores> WriteLeaderboardScores(FWriteLeaderboardScores::Params&& Params) override;` — FLeaderboardsCommon
- L43 _protected member_ `TArray<FLeaderboardDataNull> LeaderboardsData;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESERVICESNULL_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/LobbiesNull.h` (Public)


#### class `UE::Online::FLobbyNull`  
`class FLobbyNull`  
_L16-27_
- L19 _public prototype_ `FLobbyNull();`
- L22 _public member_ `TSharedRef<FLobby> Data;`
- L23 _public member_ `int32 PingInMs;`
- L24 _public member_ `TSharedPtr<class FInternetAddr> HostAddr;`
- L25 _public member_ `uint32 HostAddrIp;`
- L26 _public member_ `int32 HostAddrPort;`

#### class `UE::Online::FLobbiesNull`  
`class FLobbiesNull : public FLobbiesCommon`  
_L29-154_
- inherits: `FLobbiesCommon`
- L34 _public prototype_ `FLobbiesNull(FOnlineServicesNull& InServices);`
- L36 _public prototype_ `virtual void Initialize() override;`
- L37 _public prototype_ `virtual void PreShutdown() override;`
- L38 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L40 _public prototype_ `virtual TOnlineAsyncOpHandle<FCreateLobby> CreateLobby(FCreateLobby::Params&& Params) override;`
- L41 _public prototype_ `virtual TOnlineAsyncOpHandle<FFindLobbies> FindLobbies(FFindLobbies::Params&& Params) override;`
- L42 _public prototype_ `virtual TOnlineAsyncOpHandle<FJoinLobby> JoinLobby(FJoinLobby::Params&& Params) override;`
- L43 _public prototype_ `virtual TOnlineAsyncOpHandle<FLeaveLobby> LeaveLobby(FLeaveLobby::Params&& Params) override;`
- L44 _public prototype_ `virtual TOnlineResult<FGetJoinedLobbies> GetJoinedLobbies(FGetJoinedLobbies::Params&& Params) override;`
- L47 _private prototype_ `bool NeedsToAdvertise();` — LAN
- L48 _private prototype_ `bool IsSessionJoinable( const TSharedRef<FLobbyNull>& Session) const;`
- L49 _private prototype_ `uint32 UpdateLANStatus();`
- L50 _private prototype_ `uint32 JoinLANSession(int32 PlayerNum, TSharedRef<FLobbyNull>& Lobby);`
- L51 _private prototype_ `uint32 FindLANSession();`
- L52 _private prototype_ `uint32 FinalizeLANSearch();`
- L53 _private prototype_ `void AppendLobbyToPacket(FNboSerializeToBuffer& Packet, const TSharedRef<FLobbyNull>& Lobby);`
- L55 _private prototype_ `void ReadLobbyFromPacket(FNboSerializeFromBuffer& Packet, const TSharedRef<FLobbyNull>& Session);` — void AppendSessionSettingsToPacket(class FNboSerializeToBufferNull& Packet, FOnlineSessionSettings* SessionSettings);
- L57 _private prototype_ `void OnValidQueryPacketReceived(uint8* PacketData, int32 PacketLength, uint64 ClientNonce);` — void ReadSettingsFromPacket(class FNboSerializeFromBufferNull& Packet, FOnlineSessionSettings& SessionSettings);
- L58 _private prototype_ `void OnValidResponsePacketReceived(uint8* PacketData, int32 PacketLength);`
- L59 _private prototype_ `void OnLANSearchTimeout();`
- L62 _private member_ `FOnlineServicesNull& Services;`
- L64 _private member_ `TMap<FName, TSharedRef<FLobbyNull>> NamedLobbies;`
- L65 _private member_ `TMap<FLobbyId, TSharedRef<FLobbyNull>> AllLobbies;` — todo: this should be moved to the lobby id registry (replication made this tricky to get implemented asap)
- L66 _private member_ `TSharedPtr<FFindLobbies::Result> CurrentLobbySearch;`
- L67 _private member_ `TSharedPtr<TOnlineAsyncOp<FFindLobbies>> CurrentLobbySearchHandle;`
- L68 _private member_ `FLANSession LANSessionManager;`
- L73 _private prototype_ `TSharedRef<FLobbyNull> CreateNamedLobby(const FCreateLobby::Params& Params);` — Lobby list management
- L75 _private function_ `TSharedPtr<const FLobbyNull> GetNamedLobby(const FName& LobbyName) const`
- L88 _private function_ `TSharedPtr<FLobbyNull> GetNamedLobby(const FName& LobbyName)`
- L101 _private function_ `TSharedPtr<FLobbyNull> GetLobby(const FLobbyId LobbyId)`
- L114 _private function_ `void AddNamedLobby(const TSharedRef<FLobbyNull>& Lobby, FName Name)`
- L123 _private function_ `bool RemoveLobbyFromRef(const TSharedRef<FLobbyNull>& Lobby)` — returns true if a named lobby was removed
- L129 _private function_ `bool RemoveLobbyFromId(const FLobbyId& LobbyId)` — returns true if a named lobby was removed
- L142 _private function_ `bool RemoveLobbyFromName(const FName& Name)` — returns true if a named lobby was removed

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/LobbyRegistryNull.h` (Public)


#### class `UE::Online::FOnlineLobbyIdRegistryNull`  
`class FOnlineLobbyIdRegistryNull : public IOnlineLobbyIdRegistry`  
_L10-34_
- inherits: `IOnlineLobbyIdRegistry`
- L13 _public prototype_ `static FOnlineLobbyIdRegistryNull& Get();`
- L15 _public prototype_ `const FLobbyId* Find(FString LobbyIdStr);`
- L16 _public prototype_ `FLobbyId FindOrAdd(FString LobbyIdStr);`
- L17 _public prototype_ `FLobbyId GetNext();`
- L20 _public prototype_ `virtual FString ToString(const FLobbyId& LobbyId) const override;`
- L21 _public prototype_ `virtual FString ToLogString(const FLobbyId& LobbyId) const override;`
- L22 _public prototype_ `virtual TArray<uint8> ToReplicationData(const FLobbyId& LobbyId) const override;`
- L23 _public prototype_ `virtual FLobbyId FromReplicationData(const TArray<uint8>& ReplicationString) override;`
- L24 _public prototype_ `virtual FLobbyId FromStringData(const FString& StringData) override;`
- L27 _public prototype_ `virtual ~FOnlineLobbyIdRegistryNull() = default;`
- L31 _private prototype_ `const FString* GetInternal(const FLobbyId& LobbyId) const;` — TODO use TOnlineBasicIdRegistry
- L32 _private member_ `TArray<FString> Ids;`
- L33 _private member_ `TMap<FString, FLobbyId> StringToId;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L9 _typedef_ `using IOnlineLobbyIdRegistry = IOnlineIdRegistry<OnlineIdHandleTags::FLobby>;` (scope `UE::Online`) — todo: remove this when its added to the global scope

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/NboSerializerNullSvc.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Online` (scope `UE`)
- L18 _namespace_ `namespace NboSerializerNullSvc` (scope `UE::Online`)
- L22 _function_ `inline void SerializeToBuffer(FNboSerializeToBuffer& Ar, const FAccountId& UniqueId)` (scope `UE::Online::NboSerializerNullSvc`)
- L29 _function_ `inline void SerializeToBuffer(FNboSerializeToBuffer& Ar, const FOnlineSessionId& SessionId)` (scope `UE::Online::NboSerializerNullSvc`)
- L36 _function_ `inline void SerializeToBuffer(FNboSerializeToBuffer& Packet, const FSessionMemberIdsSet& SessionMembersSet)` (scope `UE::Online::NboSerializerNullSvc`)
- L46 _function_ `inline void SerializeToBuffer(FNboSerializeToBuffer& Ar, const TMap<FSchemaAttributeId, FSchemaVariant>& Map)` (scope `UE::Online::NboSerializerNullSvc`)
- L58 _function_ `inline void SerializeFromBuffer(FNboSerializeFromBuffer& Ar, FAccountId& UniqueId)` (scope `UE::Online::NboSerializerNullSvc`)
- L68 _function_ `inline void SerializeFromBuffer(FNboSerializeFromBuffer& Ar, FOnlineSessionId& SessionId)` (scope `UE::Online::NboSerializerNullSvc`)
- L78 _function_ `inline void SerializeFromBuffer(FNboSerializeFromBuffer& Packet, FSessionMemberIdsSet& SessionMembersSet)` (scope `UE::Online::NboSerializerNullSvc`)
- L92 _function_ `inline void SerializeFromBuffer(FNboSerializeFromBuffer& Ar, TMap<FSchemaAttributeId, FSchemaVariant>& Map)` (scope `UE::Online::NboSerializerNullSvc`)

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/OnlineServicesNull.h` (Public)


#### class `UE::Online::FOnlineServicesNull`  
`class FOnlineServicesNull : public FOnlineServicesCommon`  
_L11-23_
- inherits: `FOnlineServicesCommon`
- L14 _public typedef_ `using Super = FOnlineServicesCommon;`
- L16 _public prototype_ `FOnlineServicesNull(FName InInstanceName, FName InInstanceConfigName);`
- L17 _public prototype_ `virtual void RegisterComponents() override;`
- L18 _public prototype_ `virtual void Initialize() override;`
- L19 _public prototype_ `virtual void PreShutdown() override;`
- L20 _public prototype_ `virtual TOnlineResult<FGetResolvedConnectString> GetResolvedConnectString(FGetResolvedConnectString::Params&& Params) override;`
- L21 _public function_ `virtual EOnlineServices GetServicesProvider() const override`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ONLINESERVICESNULL_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/OnlineServicesNullModule.h` (Public)


#### class `UE::Online::FOnlineServicesNullModule`  
`class FOnlineServicesNullModule : public IModuleInterface`  
_L9-19_
- inherits: `IModuleInterface`
- L12 _public prototype_ `static int GetRegistryPriority();`
- L16 _private prototype_ `virtual void StartupModule() override;`
- L17 _private prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/OnlineServicesNullTypes.h` (Public)
_(no declarations extracted)_

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/PresenceNull.h` (Public)


#### class `UE::Online::FPresenceNull`  
`class FPresenceNull : public FPresenceCommon`  
_L12-28_
- inherits: `FPresenceCommon`
- L15 _public prototype_ `FPresenceNull(FOnlineServicesNull& InServices);`
- L17 _public prototype_ `virtual void Initialize() override;`
- L18 _public prototype_ `virtual void PreShutdown() override;`
- L20 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryPresence> QueryPresence(FQueryPresence::Params&& Params) override;`
- L21 _public prototype_ `virtual TOnlineResult<FGetCachedPresence> GetCachedPresence(FGetCachedPresence::Params&& Params) override;`
- L22 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdatePresence> UpdatePresence(FUpdatePresence::Params&& Params) override;`
- L23 _public prototype_ `virtual TOnlineAsyncOpHandle<FPartialUpdatePresence> PartialUpdatePresence(FPartialUpdatePresence::Params&& Params) override;`
- L26 _protected member_ `TMap<FAccountId, TSharedRef<const FUserPresence>> Presences;`
- L27 _protected member_ `TMap<FAccountId, TSet<FAccountId>> PresenceListeners;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/SessionsNull.h` (Public)


#### class `UE::Online::FOnlineSessionIdRegistryNull`  
`class FOnlineSessionIdRegistryNull : public FOnlineSessionIdRegistryLAN`  
_L10-17_
- inherits: `FOnlineSessionIdRegistryLAN`
- L13 _public prototype_ `static FOnlineSessionIdRegistryNull& Get();`
- L16 _private prototype_ `FOnlineSessionIdRegistryNull();`

#### class `UE::Online::FSessionsNull`  
`class FSessionsNull : public FSessionsLAN`  
_L21-33_
- inherits: `FSessionsLAN`
- L24 _public typedef_ `using Super = FSessionsLAN;`
- L26 _public prototype_ `FSessionsNull(FOnlineServicesNull& InServices);`
- L27 _public prototype_ `virtual ~FSessionsNull() = default;`
- L31 _private prototype_ `virtual void AppendSessionToPacket(FNboSerializeToBuffer& Packet, const FSessionLAN& Session) override;` — FSessionsLAN
- L32 _private prototype_ `virtual void ReadSessionFromPacket(FNboSerializeFromBuffer& Packet, FSessionLAN& Session) override;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Online` (scope `UE`)
- L19 _typedef_ `typedef FSessionLAN FSessionNull;` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/StatsNull.h` (Public)


#### class `UE::Online::FStatsNull`  
`class FStatsNull : public FStatsCommon`  
_L13-19_
- inherits: `FStatsCommon`
- L16 _public typedef_ `using Super = FStatsCommon;`
- L18 _public prototype_ `FStatsNull(FOnlineServicesNull& InOwningSubsystem);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ONLINESERVICESNULL_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/TitleFileNull.h` (Public)


#### class `UE::Online::FTitleFileNull`  
`class FTitleFileNull : public FTitleFileCommon`  
_L14-33_
- inherits: `FTitleFileCommon`
- L17 _public typedef_ `using Super = FTitleFileCommon;`
- L19 _public prototype_ `FTitleFileNull(FOnlineServicesNull& InOwningSubsystem);`
- L22 _public prototype_ `virtual void UpdateConfig() override;` — IOnlineComponent
- L25 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileEnumerateFiles> EnumerateFiles(FTitleFileEnumerateFiles::Params&& Params) override;` — ITitleFile
- L26 _public prototype_ `virtual TOnlineResult<FTitleFileGetEnumeratedFiles> GetEnumeratedFiles(FTitleFileGetEnumeratedFiles::Params&& Params) override;`
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileReadFile> ReadFile(FTitleFileReadFile::Params&& Params) override;`
- L30 _protected member_ `TMap<FString, FTitleFileContentsRef> TitleFiles;`
- L32 _protected member_ `bool bEnumerated = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESNULL_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesNull/Source/Public/Online/UserFileNull.h` (Public)


#### class `UE::Online::FUserFileNull`  
`class FUserFileNull : public FUserFileCommon`  
_L14-45_
- inherits: `FUserFileCommon`
- L17 _public typedef_ `using Super = FUserFileCommon;`
- L19 _public prototype_ `FUserFileNull(FOnlineServicesNull& InOwningSubsystem);`
- L22 _public prototype_ `virtual void UpdateConfig() override;` — IOnlineComponent
- L25 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileEnumerateFiles> EnumerateFiles(FUserFileEnumerateFiles::Params&& Params) override;` — IUserFile
- L26 _public prototype_ `virtual TOnlineResult<FUserFileGetEnumeratedFiles> GetEnumeratedFiles(FUserFileGetEnumeratedFiles::Params&& Params) override;`
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileReadFile> ReadFile(FUserFileReadFile::Params&& Params) override;`
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileWriteFile> WriteFile(FUserFileWriteFile::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileCopyFile> CopyFile(FUserFileCopyFile::Params&& Params) override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileDeleteFile> DeleteFile(FUserFileDeleteFile::Params&& Params) override;`
- L33 _protected typedef_ `using FUserFileMap = TMap<FString, FUserFileContentsRef>;`
- L41 _protected member_ `TMap<FAccountId, FUserState> UserStates;`
- L42 _protected prototype_ `FUserState& GetUserState(const FAccountId AccountId);`
- L44 _protected member_ `FUserFileMap InitialFileStateFromConfig;`

#### struct `UE::Online::FUserFileNull::FUserState`  
`struct FUserState`  
_L35-39_
- L37 _public member_ `bool bEnumerated = false;`
- L38 _public member_ `FUserFileMap Files;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESNULL_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
