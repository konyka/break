# Plugins / OnlineSubsystemSteam

- module root: `Plugins/Online/OnlineSubsystemSteam/Source`
- headers: 30; symbols: 1036
- symbol kinds: class=60, delegate=11, enum=6, enumerator=37, externvar=1, function=170, macro=27, member=218, namespace=3, prototype=453, struct=11, typedef=39
- PrivateDependencyModuleNames: AudioMixer, Core, CoreUObject, Engine, Json, NetCore, OnlineBase, OnlineSubsystem, PacketHandler, Projects, Sockets, SteamShared, Voice
- PublicDependencyModuleNames: OnlineSubsystemUtils

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/NboSerializerSteam.h` (Private)


#### class `FNboSerializeToBufferSteam`  
`class FNboSerializeToBufferSteam : public FNboSerializeToBufferOSS`  
_L11-37_
- inherits: `FNboSerializeToBufferOSS`
- desc: Serializes data in network byte order form into a buffer
- L15 _public function_ `FNboSerializeToBufferSteam() : FNboSerializeToBufferOSS(512)` — Default constructor zeros num bytes
- L21 _public function_ `FNboSerializeToBufferSteam(uint32 Size) : FNboSerializeToBufferOSS(Size)` — Constructor specifying the size to use

#### class `FNboSerializeFromBufferSteam`  
`class FNboSerializeFromBufferSteam : public FNboSerializeFromBufferOSS`  
_L42-69_
- inherits: `FNboSerializeFromBufferOSS`
- desc: Class used to write data into packets for sending via system link
- L48 _public function_ `FNboSerializeFromBufferSteam(uint8* Packet,int32 Length) : FNboSerializeFromBufferOSS(Packet,Length)` — Initializes the buffer, size, and zeros the read offset

#### Free symbols / members of external scopes

- L29 _function_ `friend inline FNboSerializeToBufferSteam& operator<<(FNboSerializeToBufferSteam& Ar, const FOnlineSessionInfoSteam& SessionInfo)` — Adds Steam session info to the buffer
- L56 _function_ `friend inline FNboSerializeFromBufferSteam& operator>>(FNboSerializeFromBufferSteam& Ar, FOnlineSessionInfoSteam& SessionInfo)` — Reads Steam session info from the buffer

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineAchievementsInterfaceSteam.h` (Private)


#### class `FOnlineAchievementsSteam`  
`class FOnlineAchievementsSteam : public IOnlineAchievements`  
_L14-164_
- inherits: `IOnlineAchievements`
- desc: IOnlineAchievements - Interface class for acheivements
- L93 _private member_ `class FOnlineSubsystemSteam* SteamSubsystem;` — Reference to the owning subsystem
- L96 _private member_ `class FOnlineLeaderboardsSteam* StatsInt;` — Reference to leaderboard interface (internal class)
- L99 _private function_ `FOnlineAchievementsSteam()` — hide the default constructor, we need a reference to our OSS
- L102 _private member_ `TUniqueNetIdMap<TArray<FOnlineAchievement>> PlayerAchievements;` — Mapping of players to their achievements
- L105 _private member_ `TMap<FString, FOnlineAchievementDesc> AchievementDescriptions;` — Cached achievement descriptions for an Id
- L108 _private member_ `TArray<FOnlineAchievementSteam> Achievements;` — Achievements configured in the config (not player-specific)
- L111 _private member_ `bool bHaveConfiguredAchievements;` — Whether we have achievements specified in the .ini
- L114 _private prototype_ `bool ReadAchievementsFromConfig();` — Initializes achievements from config. Returns true if there is at least one achievement
- L136 _private prototype_ `void OnWriteAchievementsComplete(const FUniqueNetIdSteam& PlayerId, bool bWasSuccessful, FOnlineAchievementsWritePtr & WriteObject, const FOnAchievementsWrittenDelegate& Delegate);` — ** INTERNAL ** Called by an async task after completing an achievement write. Used to conditionally unlock achievements in case the write was successful. @param PlayerId - id of a player we were making read for @param bWasSuccessful - whether the read completed successfully @param WriteObject - achievements we have been writing (unlocking) @param Delegate - delegate back to the game code indicating the write is completed
- L141 _public prototype_ `virtual void WriteAchievements(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate = FOnAchievementsWrittenDelegate()) override;`
- L142 _public prototype_ `virtual void QueryAchievements(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate()) override;`
- L143 _public prototype_ `virtual void QueryAchievementDescriptions( const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate = FOnQueryAchievementsCompleteDelegate() ) override;`
- L144 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievement(const FUniqueNetId& PlayerId, const FString& AchievementId, FOnlineAchievement& OutAchievement) override;`
- L145 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievements(const FUniqueNetId& PlayerId, TArray<FOnlineAchievement> & OutAchievements) override;`
- L146 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc& OutAchievementDesc) override;`
- L148 _public prototype_ `virtual bool ResetAchievements( const FUniqueNetId& PlayerId ) override;`
- L157 _public prototype_ `FOnlineAchievementsSteam(class FOnlineSubsystemSteam* InSubsystem);` — Constructor @param InSubsystem - A reference to the owning subsystem
- L163 _public function_ `virtual ~FOnlineAchievementsSteam()` — Default destructor

#### struct `FOnlineAchievementsSteam::FOnlineAchievementSteam`  
`struct FOnlineAchievementSteam : public FOnlineAchievement, public FOnlineAchievementDesc`  
_L19-33_
- inherits: `FOnlineAchievement,FOnlineAchievementDesc`
- desc: Structure describing a Steam achievement
- L22 _public member_ `bool bReadFromSteam;` — Whether achievement info has been read from Steam
- L25 _public function_ `FString ToDebugString() const` — Returns debugging string to print out achievement info

#### struct `FOnlineAchievementsSteam::FSteamAchievementsConfig`  
`struct FSteamAchievementsConfig`  
_L38-90_
- desc: A helper class for configuring achievements in ini
- L44 _public function_ `FSteamAchievementsConfig() : IniName(GEngineIni) , SectionName(TEXT("OnlineSubsystemSteam"))` — Create a config using the default values: IniName - GEngineIni
- L51 _public function_ `FString GetKey(const FString& KeyName)` — Returns empty string if couldn't read
- L61 _public function_ `bool ReadAchievements(TArray<FOnlineAchievementSteam> & OutArray)`
- L87 _public member_ `FString IniName;` — Ini file name to find the config values
- L89 _public member_ `FString SectionName;` — Section name for Steam

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineAsyncTaskManagerSteam.h` (Private)


#### class `FOnlineAsyncTaskSteam`  
`class FOnlineAsyncTaskSteam : public FOnlineAsyncTaskBasic<class FOnlineSubsystemSteam>`  
_L12-37_
- inherits: `FOnlineAsyncTaskBasic<classFOnlineSubsystemSteam>`
- desc: Base class that holds a delegate to fire when a given async task is complete
- L20 _private function_ `FOnlineAsyncTaskSteam() : FOnlineAsyncTaskBasic(NULL), CallbackHandle(k_uAPICallInvalid)` — Hidden on purpose
- L28 _public function_ `FOnlineAsyncTaskSteam(class FOnlineSubsystemSteam* InSteamSubsystem, SteamAPICall_t InCallbackHandle) : FOnlineAsyncTaskBasic(InSteamSubsystem), CallbackHandle(InCallbackHandle)`
- L34 _public function_ `virtual ~FOnlineAsyncTaskSteam()`

#### class `FOnlineAsyncTaskManagerSteam`  
`class FOnlineAsyncTaskManagerSteam : public FOnlineAsyncTaskManager`  
_L42-135_
- inherits: `FOnlineAsyncTaskManager`
- desc: Steam version of the async task manager to register the various Steam callbacks with the engine
- L47 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnSteamServersConnected, SteamServersConnected_t, OnSteamServersConnectedCallback);` — Delegate registered with Steam to trigger when a user (client API) is connected to the Steam servers  (usually don't get this because we're already connected externally)
- L49 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnSteamServersDisconnected, SteamServersDisconnected_t, OnSteamServersDisconnectedCallback);` — Delegate registered with Steam to trigger when a user (client API) is disconnected from the Steam servers.  All realtime services are disabled until a connect event above
- L51 _private prototype_ `STEAM_GAMESERVER_CALLBACK(FOnlineAsyncTaskManagerSteam, OnSteamServersDisconnectedGS, SteamServersDisconnected_t, OnSteamServersDisconnectedGSCallback);` — Delegate registered with Steam to trigger when a server (gameserver API) is disconnected from Steam.  Will occur on DestroySession()
- L53 _private prototype_ `STEAM_GAMESERVER_CALLBACK(FOnlineAsyncTaskManagerSteam, OnSteamServersConnectFailureGS, SteamServerConnectFailure_t, OnSteamServersConnectFailureGSCallback);` — Delegate registered with Steam to trigger when a server (gameserver API) connection fails.
- L55 _private prototype_ `STEAM_GAMESERVER_CALLBACK(FOnlineAsyncTaskManagerSteam, OnPolicyResponseGS, GSPolicyResponse_t, OnPolicyResponseGSCallback);` — Delegate registered with Steam to trigger when a server (gameserver API) is properly connected to Steam servers, logon isn't complete until this occurs
- L58 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnGetTicketForWebApiResponse, GetTicketForWebApiResponse_t, OnGetTicketForWebApiResponseCallback);` — Delegate registered with Steam to trigger when a user (client API) gets a response for a GetTicketForWebApiResponse request
- L60 _private prototype_ `STEAM_GAMESERVER_CALLBACK(FOnlineAsyncTaskManagerSteam, OnAuthenticationResponseGS, ValidateAuthTicketResponse_t, OnAuthenticationResponseGSCallback);` — Delegate registered with Steam to trigger when a server (gameserver API) gets a response for a Steam session authentication ticket request
- L62 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnAuthenticationResponse, ValidateAuthTicketResponse_t, OnAuthenticationResponseCallback);` — Delegate registered with Steam to trigger when a user (client API) gets a response for a Steam session authentication ticket request
- L65 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnInviteAccepted, GameRichPresenceJoinRequested_t, OnInviteAcceptedCallback);` — Delegate registered with Steam to trigger when a user accepts an invite request to a non lobby session
- L67 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnLobbyInviteAccepted, GameLobbyJoinRequested_t, OnLobbyInviteAcceptedCallback);` — Delegate registered with Steam to trigger when a user attempts JIP (via Steam client) or accepts an invite request (via Steam client) to a lobby session
- L69 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnLobbyEnter, LobbyEnter_t, OnLobbyEnterCallback);` — Delegate registered with Steam to trigger when a user joins a lobby (successfully or not)
- L71 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnLobbyChatUpdate, LobbyChatUpdate_t, OnLobbyChatUpdateCallback);` — Delegate registered with Steam to trigger when a lobby chat update occurs (usually users joining/leaving lobby)
- L77 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnLobbyDataUpdate, LobbyDataUpdate_t, OnLobbyDataUpdateCallback);` — Delegate registered with Steam to trigger when a lobby update occurs As host (or any client joined to the lobby), any call to SetLobbyData will trigger this As client searching for lobbies, once per call to RequestLobbyData
- L79 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnUserStatsReceived, UserStatsReceived_t, OnUserStatsReceivedCallback);` — Delegate registered with Steam to trigger when the currently logged in user receives their stats from RequestStats()
- L81 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnUserStatsStored, UserStatsStored_t, OnUserStatsStoredCallback);` — Delegate registered with Steam to trigger when the currently logged in user has their stats stored
- L83 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnUserStatsUnloaded, UserStatsUnloaded_t, OnUserStatsUnloadedCallback);` — Delegate registered with Steam to trigger when any previously requested user's stat are unloaded by the system
- L85 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnExternalUITriggered, GameOverlayActivated_t, OnExternalUITriggeredCallback);` — Delegate registered with Steam to trigger when the Steam Overlay is activated
- L87 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnSteamShutdown, SteamShutdown_t, OnSteamShutdownCallback);` — Delegate registered with Steam to trigger when Steam is shutting down
- L89 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnRichPresenceUpdate, FriendRichPresenceUpdate_t, OnRichPresenceUpdateCallback);` — Delegate registered with Steam to trigger when Steam gets updates about user rich presence
- L91 _private prototype_ `STEAM_CALLBACK(FOnlineAsyncTaskManagerSteam, OnFriendStatusUpdate, PersonaStateChange_t, OnFriendStatusUpdateCallback);` — Delegate registered with Steam to trigger when Steam gets updates about friends status
- L98 _protected member_ `class FOnlineSubsystemSteam* SteamSubsystem;` — Cached reference to the main online subsystem
- L102 _public function_ `FOnlineAsyncTaskManagerSteam(class FOnlineSubsystemSteam* InOnlineSubsystem) : OnSteamServersConnectedCallback(this, &FOnlineAsyncTaskManagerSteam::OnSteamServersConnected), OnSteamServersDisconnectedCallback(this, &FOnlineAsyncTaskManagerSteam::OnSteamServersDisconnected), OnSteamServersDisconnectedGSCallback(this, &FOnlineAsyncTaskManagerSteam::OnSteamServersDisconnectedGS), OnSteamServersConnectFailureGSCallback(this, &FOnlineAsyncTaskManagerSteam::OnSteamServersConnectFailureGS), OnPolicyResponseGSCallback(this, &FOnlineAsyncTaskManagerSteam::OnPolicyResponseGS), OnGetTicketForWebApiResponseCallback(this, &FOnlineAsyncTaskManagerSteam::OnGetTicketForWebApiResponse), OnAuthenticationResponseGSCallback(this, &FOnlineAsyncTaskManagerSteam::OnAuthenticationResponseGS), OnAuthenticationResponseCallback(this, &FOnlineAsyncTaskManagerSteam::OnAuthenticationResponse), OnInviteAcceptedCallback(this, &FOnlineAsyncTaskManagerSteam::OnInviteAccepted), OnLobbyInviteAcceptedCallback(this, &FOnlineAsyncTaskManagerSteam::OnLobbyInviteAccepted), OnLobbyEnterCallback(this, &FOnlineAsyncTaskManagerSteam::OnLobbyEnter), OnLobbyChatUpdateCallback(this, &FOnlineAsyncTaskManagerSteam::OnLobbyChatUpdate), OnLobbyDataUpdateCallback(this, &FOnlineAsyncTaskManagerSteam::OnLobbyDataUpdate), OnUserStatsReceivedCallback(this, &FOnlineAsyncTaskManagerSteam::OnUserStatsReceived), OnUserStatsStoredCallback(this, &FOnlineAsyncTaskManagerSteam::OnUserStatsStored), OnUserStatsUnloadedCallback(this, &FOnline ...`
- L127 _public function_ `~FOnlineAsyncTaskManagerSteam()`
- L132 _public prototype_ `virtual void OnlineTick() override;` — FOnlineAsyncTaskManager

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineAuthHandlerSteam.h` (Private)


#### class `FSteamAuthHandlerComponent`  
`class FSteamAuthHandlerComponent : public HandlerComponent`  
_L15-61_
- inherits: `HandlerComponent`
- L18 _public prototype_ `FSteamAuthHandlerComponent();`
- L19 _public prototype_ `virtual ~FSteamAuthHandlerComponent();`
- L20 _public prototype_ `virtual void CountBytes(FArchive& Ar) const override;`
- L21 _public prototype_ `virtual void Initialize() override;`
- L22 _public prototype_ `virtual void NotifyHandshakeBegin() override;`
- L24 _public prototype_ `virtual bool IsValid() const override;`
- L26 _public prototype_ `virtual void Incoming(FBitReader& Packet) override;`
- L27 _public prototype_ `virtual void Outgoing(FBitWriter& Packet, FOutPacketTraits& Traits) override;`
- L29 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L31 _public prototype_ `virtual int32 GetReservedPacketBits() const override;`
- L33 _public prototype_ `virtual bool SupportsParallelConnectionOutgoing() const override;`
- L44 _protected function_ `void SetState(ESteamAuthHandlerState NewState)`
- L45 _protected prototype_ `void SetComponentReady();`
- L46 _protected prototype_ `void SendAuthKey(bool bGenerateNewKey);`
- L47 _protected prototype_ `bool SendAuthResult();`
- L48 _protected prototype_ `void SendPacket(FBitWriter& OutboundPacket);`
- L49 _protected prototype_ `void RequestResend();`
- L51 _protected member_ `FOnlineAuthSteamPtr AuthInterface;`
- L52 _protected member_ `class ISteamUser* SteamUserPtr;`
- L54 _protected member_ `ESteamAuthHandlerState State;`
- L55 _protected member_ `bool bIsEnabled;`
- L56 _protected member_ `float LastTimestamp;`
- L58 _protected member_ `FString UserTicket;`
- L59 _protected member_ `uint32 TicketHandle;`
- L60 _protected member_ `FUniqueNetIdSteamRef SteamId;`

#### enum `FSteamAuthHandlerComponent::ESteamAuthHandlerState`  
`enum class ESteamAuthHandlerState : uint8`  
_L36-42_
- L38 _public enumerator_ `Uninitialized`
- L39 _public enumerator_ `WaitingForKey`
- L40 _public enumerator_ `SentAuthKey` — WaitingForKey,   Server jumps to this immediately
- L41 _public enumerator_ `Initialized` — SentAuthKey,   Client hops here, should their key work, they get another message that allows them to continue

#### class `USteamAuthComponentModuleInterface`  
`class USteamAuthComponentModuleInterface : public UHandlerComponentFactory`  
_L64-70_
- reflection: `UCLASS()`
- inherits: `UHandlerComponentFactory`
- L69 _public prototype_ `virtual TSharedPtr<HandlerComponent> CreateComponentInstance(FString& Options) override;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineAuthInterfaceSteam.h` (Private)


#### enum `ESteamAuthStatus`  
`enum class ESteamAuthStatus : uint8`  
_L17-26_
- L19 _public enumerator_ `None = 0`
- L20 _public enumerator_ `AuthSuccess = 1 << 0`
- L21 _public enumerator_ `AuthFail = 1 << 1`
- L22 _public enumerator_ `ValidationStarted = 1 << 2`
- L23 _public enumerator_ `KickUser = 1 << 3`
- L24 _public enumerator_ `FailKick = AuthFail | KickUser`
- L25 _public enumerator_ `HasOrIsPendingAuth = AuthSuccess | ValidationStarted`

#### class `FOnlineAuthSteam`  
`class FOnlineAuthSteam`  
_L38-121_
- L53 _private typedef_ `typedef TSharedPtr<FSteamAuthUser, ESPMode::NotThreadSafe> SharedAuthUserSteamPtr;`
- L55 _private prototype_ `SharedAuthUserSteamPtr GetUser(const FUniqueNetId& InUserId);`
- L56 _private prototype_ `SharedAuthUserSteamPtr GetOrCreateUser(const FUniqueNetId& InUserId);`
- L58 _private prototype_ `bool AuthenticateUser(const FUniqueNetId& InUserId);`
- L59 _private prototype_ `void EndAuthentication(const FUniqueNetId& InUserId);`
- L60 _private prototype_ `void MarkPlayerForKick(const FUniqueNetId& InUserId);`
- L61 _private prototype_ `void RevokeTicket(const uint32& Handle);`
- L62 _private prototype_ `void RevokeAllTickets();`
- L63 _private prototype_ `void RemoveUser(const FUniqueNetId& TargetUser);`
- L66 _private prototype_ `FString GetAuthTicket(uint32& AuthTokenHandle);` — Generates Steam auth tickets
- L67 _private prototype_ `void GetAuthTicketForWebApi(const FString& RemoteServiceIdentity, FOnGetAuthTicketForWebApiCompleteDelegate CompletionDelegate);`
- L69 _private prototype_ `bool Tick(float DeltaTime);`
- L70 _private prototype_ `bool Exec(const TCHAR* Cmd);`
- L73 _private prototype_ `void OnGetTicketForWebResponse(uint32 AuthTicketHandle, const FString& ResultToken);` — Callbacks from Steam
- L74 _private prototype_ `void OnAuthResult(const FUniqueNetId& TargetId, int32 Response);`
- L76 _private prototype_ `void ExecuteResultDelegate(const FUniqueNetId& TargetId, bool bWasSuccessful, ESteamAuthResponseCode ResponseCode);`
- L79 _private typedef_ `typedef TUniqueNetIdMap<SharedAuthUserSteamPtr> SteamAuthentications;`
- L80 _private member_ `SteamAuthentications AuthUsers;`
- L81 _private member_ `TArray<uint32> SteamTicketHandles;`
- L82 _private member_ `TMap<uint32, FOnGetAuthTicketForWebApiCompleteDelegate> ActiveAuthTicketForWebApiRequests;`
- L85 _private function_ `FORCEINLINE bool IsServer() const` — Utility functions
- L89 _private prototype_ `bool KickPlayer(const FUniqueNetId& InUserId, bool bSuppressFailure);`
- L91 _private prototype_ `FOnlineAuthSteam();`
- L94 _private member_ `class ISteamUser* SteamUserPtr;` — Steam Interfaces
- L95 _private member_ `class ISteamGameServer* SteamServerPtr;`
- L98 _private member_ `FOnlineSubsystemSteam* SteamSubsystem;` — Cached pointer to owning subsystem
- L99 _private member_ `FOnlineAuthSteamUtilsPtr AuthUtils;`
- L102 _private member_ `bool bEnabled;` — Settings
- L107 _private member_ `bool bReuseKey;` — Always send out the same key
- L108 _private member_ `bool bBadWrite;` — Always make the bit writers have errors
- L109 _private member_ `bool bDropAll;` — Drop all packets
- L110 _private member_ `bool bRandomDrop;` — Randomly drop packets.
- L111 _private member_ `bool bNeverSendKey;` — Client never sends their key.
- L112 _private member_ `bool bSendBadId;` — Always send invalid steam ids.
- L115 _private function_ `bool IsSessionAuthEnabled() const` — Setting Getters
- L118 _public prototype_ `virtual ~FOnlineAuthSteam();`
- L120 _public prototype_ `static uint32 GetMaxTicketSizeInBytes();`

#### struct `FOnlineAuthSteam::FSteamAuthUser`  
`struct FSteamAuthUser`  
_L44-51_
- desc: Data pertaining the current authentication state of the users in the game
- L46 _public function_ `FSteamAuthUser() : Status(ESteamAuthStatus::None)`
- L47 _public prototype_ `void SetKey(const FString& NewKey);`
- L49 _public member_ `FString RecvTicket;` — String representation of another user's ticket. Stored only temporarily
- L50 _public member_ `ESteamAuthStatus Status;`

#### Free symbols / members of external scopes

- L28 _prototype_ `ENUM_CLASS_FLAGS(ESteamAuthStatus);`
- L36 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetAuthTicketForWebApiCompleteDelegate, uint32 , const FString& );` — Delegate executed when we complete a GetAuthTicketForWebApi call @param AuthTokenHandle The handle for the auth ticket @param AuthTicket the auth ticket returned by the api
- L36 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGetAuthTicketForWebApiCompleteDelegate, uint32 , const FString& );` — Delegate executed when we complete a GetAuthTicketForWebApi call @param AuthTokenHandle The handle for the auth ticket @param AuthTicket the auth ticket returned by the api

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineExternalUIInterfaceSteam.h` (Private)


#### class `FOnlineAsyncEventSteamExternalUITriggered`  
`class FOnlineAsyncEventSteamExternalUITriggered : public FOnlineAsyncEvent<FOnlineSubsystemSteam>`  
_L14-47_
- inherits: `FOnlineAsyncEvent<FOnlineSubsystemSteam>`
- desc: Async event that notifies when the STEAM external UI has been activated
- L17 _private member_ `bool bIsActive;` — Is the External UI activating
- L20 _private function_ `FOnlineAsyncEventSteamExternalUITriggered() : FOnlineAsyncEvent(NULL), bIsActive(false)` — Hidden on purpose
- L28 _public function_ `FOnlineAsyncEventSteamExternalUITriggered(FOnlineSubsystemSteam* InSteamSubsystem, bool bInIsActive) : FOnlineAsyncEvent(InSteamSubsystem), bIsActive(bInIsActive)`
- L34 _public function_ `virtual ~FOnlineAsyncEventSteamExternalUITriggered()`
- L41 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L46 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineExternalUISteam`  
`class FOnlineExternalUISteam : public IOnlineExternalUI`  
_L52-99_
- inherits: `IOnlineExternalUI`
- desc: Implementation for the STEAM external UIs
- L57 _private member_ `class FOnlineSubsystemSteam* SteamSubsystem;` — Reference to the main Steam subsystem
- L60 _private prototype_ `FOnlineExternalUISteam() = delete;` — Hidden on purpose
- L71 _private member_ `bool bMessageSent;` — If a message was successfully sent via the Steam UI
- L74 _private member_ `FOnProfileUIClosedDelegate ProfileUIClosedDelegate;` — Triggered when the steam overlay is closed if it was opened via ShowProfileUI. Delegate will be unbound after it is executed.
- L75 _private member_ `FOnShowWebUrlClosedDelegate ShowWebUrlClosedDelegate;`
- L76 _private member_ `FOnShowSendMessageUIClosedDelegate ShowMessageClosedDelegate;`
- L77 _private member_ `FOnShowStoreUIClosedDelegate ShowStoreClosedDelegate;`
- L81 _public function_ `virtual ~FOnlineExternalUISteam()`
- L86 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI
- L87 _public prototype_ `virtual bool ShowAccountCreationUI(const int ControllerIndex, const FOnAccountCreationUIClosedDelegate& Delegate = FOnAccountCreationUIClosedDelegate()) override;`
- L88 _public prototype_ `virtual bool ShowFriendsUI(int32 LocalUserNum) override;`
- L89 _public prototype_ `virtual bool ShowInviteUI(int32 LocalUserNum, FName SessionName = NAME_GameSession) override;`
- L90 _public prototype_ `virtual bool ShowAchievementsUI(int32 LocalUserNum) override;`
- L91 _public prototype_ `virtual bool ShowLeaderboardUI(const FString& LeaderboardName) override;`
- L92 _public prototype_ `virtual bool ShowWebURL(const FString& Url, const FShowWebUrlParams& ShowParams, const FOnShowWebUrlClosedDelegate& Delegate = FOnShowWebUrlClosedDelegate()) override;`
- L93 _public prototype_ `virtual bool CloseWebURL() override;`
- L94 _public prototype_ `virtual bool ShowProfileUI(const FUniqueNetId& Requestor, const FUniqueNetId& Requestee, const FOnProfileUIClosedDelegate& Delegate = FOnProfileUIClosedDelegate()) override;`
- L95 _public prototype_ `virtual bool ShowAccountUpgradeUI(const FUniqueNetId& UniqueId) override;`
- L96 _public prototype_ `virtual bool ShowStoreUI(int32 LocalUserNum, const FShowStoreParams& ShowParams, const FOnShowStoreUIClosedDelegate& Delegate = FOnShowStoreUIClosedDelegate()) override;`
- L97 _public prototype_ `virtual bool ShowSendMessageUI(int32 LocalUserNum, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate()) override;`
- L98 _public prototype_ `virtual bool ShowSendMessageToUserUI(int32 LocalUserNum, const FUniqueNetId& Recipient, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate()) override;`

#### Free symbols / members of external scopes

- L101 _typedef_ `typedef TSharedPtr<FOnlineExternalUISteam, ESPMode::ThreadSafe> FOnlineExternalUISteamPtr;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineFriendsInterfaceSteam.h` (Private)


#### class `FOnlineFriendSteam`  
`class FOnlineFriendSteam : public FOnlineFriend`  
_L15-68_
- inherits: `FOnlineFriend`
- desc: Info associated with an online friend on the Steam service
- L22 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;`
- L23 _public prototype_ `virtual FString GetRealName() const override;`
- L24 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;`
- L25 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L29 _public prototype_ `virtual EInviteStatus::Type GetInviteStatus() const override;`
- L30 _public prototype_ `virtual const FOnlineUserPresence& GetPresence() const override;`
- L37 _public prototype_ `FOnlineFriendSteam(const CSteamID& InUserId=CSteamID());` — Init/default constructor
- L40 _public function_ `virtual ~FOnlineFriendSteam()` — Virtual destructor to keep clang happy
- L50 _public function_ `inline bool GetAccountData(const FString& Key, FString& OutVal) const` — Get account data attribute @param Key account data entry key @param OutVal [out] value that was found @return true if entry was found
- L62 _public member_ `FUniqueNetIdRef UserId;` — User Id represented as a FUniqueNetId
- L64 _public member_ `TMap<FString, FString> AccountData;` — Any addition account data associated with the friend
- L67 _public member_ `static const FOnlineUserPresence EmptyPresence;` — A backup presence we can use if we are unable to get a friend's presence for any reason.

#### class `FOnlineFriendsSteam`  
`class FOnlineFriendsSteam : public IOnlineFriends`  
_L73-128_
- inherits: `IOnlineFriends`
- desc: Implements the Steam specific interface for friends
- L77 _private member_ `class FOnlineSubsystemSteam* SteamSubsystem;` — Reference to the main Steam subsystem
- L79 _private member_ `class ISteamUser* SteamUserPtr;` — The steam user interface to use when interacting with steam
- L81 _private member_ `class ISteamFriends* SteamFriendsPtr;` — The steam friends interface to use when interacting with steam
- L88 _private member_ `TMap<int32, FSteamFriendsList> FriendsLists;` — map of local user idx to friends
- L103 _public prototype_ `FOnlineFriendsSteam(FOnlineSubsystemSteam* InSteamSubsystem);` — Initializes the various interfaces @param InSteamSubsystem the subsystem that owns this object
- L105 _public function_ `virtual ~FOnlineFriendsSteam()`
- L109 _public prototype_ `virtual bool ReadFriendsList(int32 LocalUserNum, const FString& ListName, const FOnReadFriendsListComplete& Delegate = FOnReadFriendsListComplete()) override;`
- L110 _public prototype_ `virtual bool DeleteFriendsList(int32 LocalUserNum, const FString& ListName, const FOnDeleteFriendsListComplete& Delegate = FOnDeleteFriendsListComplete()) override;`
- L111 _public prototype_ `virtual bool SendInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnSendInviteComplete& Delegate = FOnSendInviteComplete()) override;`
- L112 _public prototype_ `virtual bool AcceptInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnAcceptInviteComplete& Delegate = FOnAcceptInviteComplete()) override;`
- L113 _public prototype_ `virtual bool RejectInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L114 _public prototype_ `virtual void SetFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FString& Alias, const FOnSetFriendAliasComplete& Delegate = FOnSetFriendAliasComplete()) override;`
- L115 _public prototype_ `virtual void DeleteFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnDeleteFriendAliasComplete& Delegate = FOnDeleteFriendAliasComplete()) override;`
- L116 _public prototype_ `virtual bool DeleteFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L117 _public prototype_ `virtual bool GetFriendsList(int32 LocalUserNum, const FString& ListName, TArray< TSharedRef<FOnlineFriend> >& OutFriends) override;`
- L118 _public prototype_ `virtual TSharedPtr<FOnlineFriend> GetFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L119 _public prototype_ `virtual bool IsFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L120 _public prototype_ `virtual bool QueryRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace) override;`
- L121 _public prototype_ `virtual bool GetRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace, TArray< TSharedRef<FOnlineRecentPlayer> >& OutRecentPlayers) override;`
- L122 _public prototype_ `virtual void DumpRecentPlayers() const override;`
- L123 _public prototype_ `virtual bool BlockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L124 _public prototype_ `virtual bool UnblockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L125 _public prototype_ `virtual bool QueryBlockedPlayers(const FUniqueNetId& UserId) override;`
- L126 _public prototype_ `virtual bool GetBlockedPlayers(const FUniqueNetId& UserId, TArray< TSharedRef<FOnlineBlockedPlayer> >& OutBlockedPlayers) override;`
- L127 _public prototype_ `virtual void DumpBlockedPlayers() const override;`

#### struct `FOnlineFriendsSteam::FSteamFriendsList`  
`struct FSteamFriendsList`  
_L83-86_
- desc: list of friends
- L85 _public member_ `TArray< TSharedRef<FOnlineFriendSteam> > Friends;`

#### class `FOnlineAsyncTaskSteamReadFriendsList`  
`class FOnlineAsyncTaskSteamReadFriendsList : public FOnlineAsyncTask`  
_L135-201_
- inherits: `FOnlineAsyncTask`
- desc: Fires the delegates for the task on the game thread
- L139 _private member_ `FOnlineFriendsSteam* FriendsPtr;` — Interface pointer to trigger the delegates on
- L141 _private member_ `int32 LocalUserNum;` — The user that is triggering the event
- L143 _private member_ `EFriendsLists::Type FriendsListFilter;` — The type of list we are trying to fetch
- L145 _private member_ `FOnReadFriendsListComplete Delegate;`
- L147 _private prototype_ `bool CanAddUserToList(bool bIsOnline, bool bIsPlayingThisGame, bool bIsPlayingGameInSession);`
- L157 _public function_ `FOnlineAsyncTaskSteamReadFriendsList(FOnlineFriendsSteam* InFriendsPtr, int32 InLocalUserNum, const FString& InFriendsListFilter, const FOnReadFriendsListComplete& InDelegate) : FriendsPtr(InFriendsPtr), LocalUserNum(InLocalUserNum), Delegate(InDelegate)` — Inits the pointer used to trigger the delegates on @param InFriendsPtr the interface to call the delegates on @param InLocalUserNum the local user that requested the read @param InDelegate the delegate that will be called when reading the friends list is complete
- L184 _public function_ `virtual FString ToString(void) const override`
- L189 _public function_ `virtual bool IsDone(void) const override`
- L194 _public function_ `virtual bool WasSuccessful(void) const override`
- L199 _public prototype_ `virtual void Finalize() override;`
- L200 _public prototype_ `virtual void TriggerDelegates(void) override;`

#### Free symbols / members of external scopes

- L130 _typedef_ `typedef TSharedPtr<FOnlineFriendsSteam, ESPMode::ThreadSafe> FOnlineFriendsSteamPtr;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineIdentityInterfaceSteam.h` (Private)


#### class `FOnlineIdentitySteam`  
`class FOnlineIdentitySteam : public IOnlineIdentity`  
_L12-50_
- inherits: `IOnlineIdentity`
- L16 _private member_ `class ISteamUser* SteamUserPtr;` — The steam user interface to use when interacting with steam
- L18 _private member_ `class ISteamFriends* SteamFriendsPtr;` — The steam friends interface to use when interacting with steam
- L21 _private member_ `FOnlineSubsystemSteam* SteamSubsystem;` — Cached pointer to owning subsystem
- L28 _public function_ `virtual ~FOnlineIdentitySteam()`
- L32 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L33 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L34 _public prototype_ `virtual bool AutoLogin(int32 LocalUserNum) override;`
- L35 _public prototype_ `virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const override;`
- L36 _public prototype_ `virtual TArray<TSharedPtr<FUserOnlineAccount> > GetAllUserAccounts() const override;`
- L37 _public prototype_ `virtual FUniqueNetIdPtr GetUniquePlayerId(int32 LocalUserNum) const override;`
- L38 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(uint8* Bytes, int32 Size) override;`
- L39 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(const FString& Str) override;`
- L40 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;`
- L41 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const override;`
- L42 _public prototype_ `virtual FString GetPlayerNickname(int32 LocalUserNum) const override;`
- L43 _public prototype_ `virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const override;`
- L44 _public prototype_ `virtual FString GetAuthToken(int32 LocalUserNum) const override;`
- L45 _public prototype_ `virtual void RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate) override;`
- L46 _public prototype_ `virtual void GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI=EShowPrivilegeResolveUI::Default) override;`
- L47 _public prototype_ `virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const override;`
- L48 _public prototype_ `virtual FString GetAuthType() const override;`
- L49 _public prototype_ `virtual void GetLinkedAccountAuthToken(int32 LocalUserNum, const FString& TokenType, const FOnGetLinkedAccountAuthTokenCompleteDelegate& Delegate) const override;`

#### Free symbols / members of external scopes

- L52 _typedef_ `typedef TSharedPtr<FOnlineIdentitySteam, ESPMode::ThreadSafe> FOnlineIdentitySteamPtr;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineLeaderboardInterfaceSteam.h` (Private)


#### struct `FUserStatsStateSteam`  
`struct FUserStatsStateSteam`  
_L16-33_
- desc: Keeps track of the download state of any stats requests/unloads Requests typically initiate in game, but Steam may unload stats at any time
- L20 _private prototype_ `FUserStatsStateSteam() = delete;` — Hidden on purpose
- L24 _public member_ `FUniqueNetIdSteamRef UserId;` — User Id
- L26 _public member_ `EOnlineAsyncTaskState::Type StatsState;` — Current stats state for this user
- L28 _public function_ `FUserStatsStateSteam(const FUniqueNetIdSteam& InUserId, EOnlineAsyncTaskState::Type InState) : UserId(InUserId.AsShared()), StatsState(InState)`

#### class `FOnlineLeaderboardsSteam`  
`class FOnlineLeaderboardsSteam : public IOnlineLeaderboards`  
_L40-138_
- inherits: `IOnlineLeaderboards`
- desc: Interface definition for the online services leaderboard services
- L44 _private member_ `class FOnlineSubsystemSteam* SteamSubsystem;` — Reference to the main Steam subsystem
- L47 _private member_ `TArray<FLeaderboardMetadataSteam> Leaderboards;` — Array of known leaderboards (may be more that haven't been requested from)
- L49 _private function_ `FOnlineLeaderboardsSteam() : SteamSubsystem(NULL)`
- L59 _private member_ `FCriticalSection UserStatsStoredLock;` — Critical section for thread safe operation of the stats stored state
- L61 _private member_ `FOnSteamUserStatsStoreStatsFinished UserStatsStoreStatsFinishedDelegate;` — Called when the event from SteamUserStats()->StoreStats() finishing is triggered
- L63 _private function_ `FOnlineLeaderboardsSteam(FOnlineSubsystemSteam* InSteamSubsystem) : SteamSubsystem(InSteamSubsystem)`
- L75 _private prototype_ `FLeaderboardMetadataSteam* GetLeaderboardMetadata(const FString& LeaderboardName);` — Get the leaderboard metadata for a given leaderboard If the data doesn't exist, the game hasn't asked to Create or Find the leaderboard below @param LeaderboardName name of leaderboard to get information for @return leaderboard metadata if it exists, else NULL
- L84 _private prototype_ `void CreateLeaderboard(const FString& LeaderboardName, ELeaderboardSort::Type SortMethod, ELeaderboardFormat::Type DisplayFormat);` — Start an async task to create a leaderboard with the Steam backend If the leaderboard already exists, the leaderboard data will still be retrieved @param LeaderboardName name of leaderboard to create @param SortMethod method the leaderboard scores will be sorted, ignored if leaderboard exists @param DisplayFormat type of data the leaderboard represents, ignored if leaderboard exists
- L91 _private prototype_ `void FindLeaderboard(const FString& LeaderboardName);` — Start an async task to find a leaderboard with the Steam backend If the leaderboard doesn't exist, a warning will be generated @param LeaderboardName name of leaderboard to create
- L99 _private prototype_ `EOnlineAsyncTaskState::Type GetUserStatsState(const FUniqueNetIdSteam& UserId);` — Get the received stats state for a given user (game thread only) @param User user to check if stats have been received @return State of the stats download for a given user, or NotStarted if user isn't found
- L107 _private prototype_ `void SetUserStatsState(const FUniqueNetIdSteam& UserId, EOnlineAsyncTaskState::Type NewState);` — Set the received stats state for a given user (game thread only) @param User user to set state of stats received @param NewState state of the stats download for a given user
- L115 _private prototype_ `void WriteAchievementsInternal(const FUniqueNetIdSteam& UserId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& OnWriteFinishedDelegate);` — Commits any changes in the online stats cache to the permanent storage (internal helper for FOnlineAchievementsSteam::WriteAchievements) @param UserId user to set state of stats stored @param WriteObject object to track the state of stats
- L123 _private prototype_ `void QueryAchievementsInternal(const FUniqueNetIdSteam& UserId, const FOnQueryAchievementsCompleteDelegate& AchievementDelegate);` — Reads achievements for user (internal helper for FOnlineAchievementsSteam::QueryAchievements) @param UserId user to set state of stats stored @param bTriggerDescriptionsDelegatesInstead - async task will normally trigger OnAchievementsRead delegates, this bool tells it to trigger OnAchievementDescriptionsRead instead
- L127 _public function_ `virtual ~FOnlineLeaderboardsSteam()`
- L130 _public prototype_ `virtual bool ReadLeaderboards(const TArray< FUniqueNetIdRef >& Players, FOnlineLeaderboardReadRef& ReadObject) override;` — IOnlineLeaderboards
- L131 _public prototype_ `virtual bool ReadLeaderboardsForFriends(int32 LocalUserNum, FOnlineLeaderboardReadRef& ReadObject) override;`
- L132 _public prototype_ `virtual bool ReadLeaderboardsAroundRank(int32 Rank, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L133 _public prototype_ `virtual bool ReadLeaderboardsAroundUser(FUniqueNetIdRef Player, uint32 Range, FOnlineLeaderboardReadRef& ReadObject) override;`
- L134 _public prototype_ `virtual void FreeStats(FOnlineLeaderboardRead& ReadObject) override;`
- L135 _public prototype_ `virtual bool WriteLeaderboards(const FName& SessionName, const FUniqueNetId& Player, FOnlineLeaderboardWrite& WriteObject) override;`
- L136 _public prototype_ `virtual bool FlushLeaderboards(const FName& SessionName) override;`
- L137 _public prototype_ `virtual bool WriteOnlinePlayerRatings(const FName& SessionName, int32 LeaderboardId, const TArray<FOnlinePlayerScore>& PlayerScores) override;`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSteamUserStatsStoreStatsFinished, EOnlineAsyncTaskState::Type);`
- L35 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSteamUserStatsStoreStatsFinished, EOnlineAsyncTaskState::Type);`
- L140 _typedef_ `typedef TSharedPtr<FOnlineLeaderboardsSteam, ESPMode::ThreadSafe> FOnlineLeaderboardsSteamPtr;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlinePresenceInterfaceSteam.h` (Private)


#### class `FOnlineUserPresenceSteam`  
`class FOnlineUserPresenceSteam : public FOnlineUserPresence`  
_L10-22_
- inherits: `FOnlineUserPresence`
- L13 _public member_ `uint32 bIsAFriend:1;`
- L15 _public function_ `FOnlineUserPresenceSteam()`
- L21 _public prototype_ `void Update(const FUniqueNetIdSteam& FriendId);`

#### class `FOnlinePresenceSteam`  
`class FOnlinePresenceSteam : public IOnlinePresence`  
_L25-58_
- inherits: `IOnlinePresence`
- L28 _private member_ `class ISteamFriends* SteamFriendsPtr;` — The steam friends interface to use when interacting with Steam
- L31 _private member_ `class FOnlineSubsystemSteam* SteamSubsystem;` — Cached pointer to owning subsystem
- L34 _private prototype_ `FOnlinePresenceSteam();` — Hide the default constructor
- L37 _private member_ `TUniqueNetIdMap<TSharedRef<FOnlineUserPresenceSteam>> CachedPresence;` — All cached presence data we ever get
- L40 _private member_ `TUniqueNetIdMap<TSharedRef<const FOnPresenceTaskCompleteDelegate>> DelayedPresenceDelegates;` — Delegates for non-friend users that were called with QueryPresence
- L46 _private prototype_ `void UpdatePresenceForUser(const FUniqueNetId& User);` — Called from Steam callback events
- L51 _public prototype_ `virtual void SetPresence(const FUniqueNetId& User, const FOnlineUserPresenceStatus& Status, const FOnPresenceTaskCompleteDelegate& Delegate = FOnPresenceTaskCompleteDelegate()) override;`
- L52 _public prototype_ `virtual void QueryPresence(const FUniqueNetId& User, const FOnPresenceTaskCompleteDelegate& Delegate = FOnPresenceTaskCompleteDelegate()) override;`
- L53 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedPresence(const FUniqueNetId& User, TSharedPtr<FOnlineUserPresence>& OutPresence) override;`
- L54 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedPresenceForApp(const FUniqueNetId& LocalUserId, const FUniqueNetId& User, const FString& AppId, TSharedPtr<FOnlineUserPresence>& OutPresence) override;`
- L57 _public function_ `virtual ~FOnlinePresenceSteam()`

#### Free symbols / members of external scopes

- L60 _typedef_ `typedef TSharedPtr<FOnlinePresenceSteam, ESPMode::ThreadSafe> FOnlinePresenceSteamPtr;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineSessionAsyncLobbySteam.h` (Private)


#### class `FOnlineAsyncTaskSteamCreateLobby`  
`class FOnlineAsyncTaskSteamCreateLobby : public FOnlineAsyncTaskSteam`  
_L15-74_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task for creating a Steam backend lobby as host and defining the proper settings
- L20 _private member_ `bool bInit;` — Has this request been started
- L22 _private member_ `FName SessionName;` — Name of session being created
- L24 _private member_ `ELobbyType LobbyType;` — Type of lobby to create
- L26 _private member_ `int32 MaxLobbyMembers;` — Max number of players allowed
- L29 _private function_ `FOnlineAsyncTaskSteamCreateLobby() : bInit(false), SessionName(NAME_None), LobbyType(k_ELobbyTypePublic), MaxLobbyMembers(0)` — Hidden on purpose
- L44 _public function_ `FOnlineAsyncTaskSteamCreateLobby(class FOnlineSubsystemSteam* InSubsystem, FName InSessionName, ELobbyType InLobbyType, int32 InMaxLobbyMembers) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), bInit(false), SessionName(InSessionName), LobbyType(InLobbyType), MaxLobbyMembers(InMaxLobbyMembers)`
- L56 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L62 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L68 _public prototype_ `virtual void Finalize() override;` — Give the async task a chance to marshal its data back to the game thread Can only be called on the game thread by the async task manager
- L73 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamUpdateLobby`  
`class FOnlineAsyncTaskSteamUpdateLobby : public FOnlineAsyncTaskSteam`  
_L79-123_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task to update a single Steam lobby
- L84 _private member_ `FName SessionName;` — Name of session being created
- L86 _private member_ `FOnlineSessionSettings NewSessionSettings;` — New session settings to apply
- L88 _private member_ `bool bUpdateOnlineData;` — Should the online platform refresh as well
- L91 _private function_ `FOnlineAsyncTaskSteamUpdateLobby() : SessionName(NAME_None), bUpdateOnlineData(false)` — Hidden on purpose
- L100 _public function_ `FOnlineAsyncTaskSteamUpdateLobby(class FOnlineSubsystemSteam* InSubsystem, FName InSessionName, bool bInUpdateOnlineData, const FOnlineSessionSettings& InNewSessionSettings) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), SessionName(InSessionName), NewSessionSettings(InNewSessionSettings), bUpdateOnlineData(bInUpdateOnlineData)` — Constructor
- L111 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L117 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L122 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamJoinLobby`  
`class FOnlineAsyncTaskSteamJoinLobby : public FOnlineAsyncTaskSteam`  
_L128-179_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task to join a single Steam lobby
- L133 _private member_ `bool bInit;` — Has this request been started
- L135 _private member_ `FName SessionName;` — Name of session being created
- L137 _private member_ `FUniqueNetIdSteamRef LobbyId;` — Lobby to join
- L140 _private prototype_ `FOnlineAsyncTaskSteamJoinLobby() = delete;` — Hidden on purpose
- L150 _public function_ `FOnlineAsyncTaskSteamJoinLobby(class FOnlineSubsystemSteam* InSubsystem, FName InSessionName, const FUniqueNetIdSteam& InLobbyId) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), bInit(false), SessionName(InSessionName), LobbyId(InLobbyId.AsShared())` — Constructor
- L161 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L167 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L173 _public prototype_ `virtual void Finalize() override;` — Give the async task a chance to marshal its data back to the game thread Can only be called on the game thread by the async task manager
- L178 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamLeaveLobby`  
`class FOnlineAsyncTaskSteamLeaveLobby : public FOnlineAsyncTaskSteam`  
_L184-215_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task for leaving a single lobby
- L189 _private member_ `FName SessionName;` — Name of session lobby
- L191 _private member_ `FUniqueNetIdSteamRef LobbyId;` — LobbyId to end
- L194 _private prototype_ `FOnlineAsyncTaskSteamLeaveLobby() = delete;` — Hidden on purpose
- L198 _public function_ `FOnlineAsyncTaskSteamLeaveLobby(class FOnlineSubsystemSteam* InSubsystem, FName InSessionName, const FUniqueNetIdSteam& InLobbyId) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), SessionName(InSessionName), LobbyId(InLobbyId.AsShared())`
- L208 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L214 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread

#### class `FOnlineAsyncTaskSteamFindLobbiesBase`  
`class FOnlineAsyncTaskSteamFindLobbiesBase : public FOnlineAsyncTaskSteam`  
_L220-286_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task for any search query to find Steam lobbies based on search criteria
- L224 _private member_ `ISteamMatchmaking* SteamMatchmakingPtr;` — Cached instance of Steam interface
- L227 _private function_ `FOnlineAsyncTaskSteamFindLobbiesBase() : SteamMatchmakingPtr(NULL)` — Hidden on purpose
- L235 _private prototype_ `virtual void CreateQuery();` — Create and trigger the lobby query from the defined search settings
- L249 _private member_ `TSharedPtr<class FOnlineSessionSearch> SearchSettings;` — Search settings specified for the query
- L251 _private member_ `EFindLobbiesState FindLobbiesState;`
- L253 _private member_ `LobbyMatchList_t CallbackResults;` — Lobby search callback data
- L255 _private member_ `TArray<CSteamID> LobbyIDs;`
- L260 _public function_ `FOnlineAsyncTaskSteamFindLobbiesBase(class FOnlineSubsystemSteam* InSubsystem, const TSharedPtr<FOnlineSessionSearch>& InSearchSettings) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), SteamMatchmakingPtr(SteamMatchmaking()), SearchSettings(InSearchSettings), FindLobbiesState(EFindLobbiesState::Init)` — Constructor
- L273 _public prototype_ `void ParseSearchResult(const FUniqueNetIdSteam& LobbyId);` — Create a search result from a specified lobby id @param LobbyId lobby to create the search result for
- L279 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L285 _public prototype_ `virtual void Finalize() override;` — Give the async task a chance to marshal its data back to the game thread Can only be called on the game thread by the async task manager

#### enum `FOnlineAsyncTaskSteamFindLobbiesBase::EFindLobbiesState`  
`enum class EFindLobbiesState : uint8`  
_L239-246_
- L241 _public enumerator_ `Init`
- L242 _public enumerator_ `RequestLobbyList`
- L243 _public enumerator_ `RequestLobbyData`
- L244 _public enumerator_ `WaitForRequestLobbyData`
- L245 _public enumerator_ `Finished`

#### class `FOnlineAsyncTaskSteamFindLobbies`  
`class FOnlineAsyncTaskSteamFindLobbies : public FOnlineAsyncTaskSteamFindLobbiesBase`  
_L291-311_
- inherits: `FOnlineAsyncTaskSteamFindLobbiesBase`
- desc: Async task for any search query to find Steam lobbies based on search criteria
- L297 _public function_ `FOnlineAsyncTaskSteamFindLobbies(class FOnlineSubsystemSteam* InSubsystem, const TSharedPtr<FOnlineSessionSearch>& InSearchSettings) : FOnlineAsyncTaskSteamFindLobbiesBase(InSubsystem, InSearchSettings)` — Constructor
- L305 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L310 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamFindLobbiesForInviteSession`  
`class FOnlineAsyncTaskSteamFindLobbiesForInviteSession : public FOnlineAsyncTaskSteamFindLobbiesBase`  
_L316-345_
- inherits: `FOnlineAsyncTaskSteamFindLobbiesBase`
- L320 _public function_ `FOnlineAsyncTaskSteamFindLobbiesForInviteSession(class FOnlineSubsystemSteam* InSubsystem, const FUniqueNetIdSteam& InLobbyId, const TSharedPtr<FOnlineSessionSearch>& InSearchSettings, int32 InLocalUserNum, const FOnAsyncFindLobbyCompleteWithNetId& InOnFindLobbyCompleteDelegates) : FOnlineAsyncTaskSteamFindLobbiesBase(InSubsystem, InSearchSettings), LocalUserNum(InLocalUserNum), OnFindLobbyCompleteWithNetIdDelegate(InOnFindLobbyCompleteDelegates)` — Constructor
- L332 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L337 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates
- L342 _private member_ `int32 LocalUserNum;` — User initiating the request
- L344 _private member_ `FOnAsyncFindLobbyCompleteWithNetId OnFindLobbyCompleteWithNetIdDelegate;`

#### class `FOnlineAsyncTaskSteamFindLobbiesForFriendSession`  
`class FOnlineAsyncTaskSteamFindLobbiesForFriendSession : public FOnlineAsyncTaskSteamFindLobbiesBase`  
_L347-376_
- inherits: `FOnlineAsyncTaskSteamFindLobbiesBase`
- L351 _public function_ `FOnlineAsyncTaskSteamFindLobbiesForFriendSession(class FOnlineSubsystemSteam* InSubsystem, const FUniqueNetIdSteam& InLobbyId, const TSharedPtr<FOnlineSessionSearch>& InSearchSettings, int32 InLocalUserNum, const FOnFindFriendSessionComplete& InOnFindFriendSessionCompleteDelegate) : FOnlineAsyncTaskSteamFindLobbiesBase(InSubsystem, InSearchSettings), LocalUserNum(InLocalUserNum), OnFindFriendSessionCompleteDelegate(InOnFindFriendSessionCompleteDelegate)` — Constructor
- L363 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L368 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates
- L373 _private member_ `int32 LocalUserNum;` — User initiating the request
- L375 _private member_ `FOnFindFriendSessionComplete OnFindFriendSessionCompleteDelegate;`

#### class `FOnlineAsyncEventSteamLobbyInviteAccepted`  
`class FOnlineAsyncEventSteamLobbyInviteAccepted : public FOnlineAsyncEvent<FOnlineSubsystemSteam>`  
_L381-416_
- inherits: `FOnlineAsyncEvent<FOnlineSubsystemSteam>`
- desc: Turns a friends accepted invite request into a valid search result (lobby version)
- L384 _private member_ `FUniqueNetIdSteamRef FriendId;` — Friend that invited
- L386 _private member_ `FUniqueNetIdSteamRef LobbyId;` — Lobby to go to
- L388 _private member_ `int32 LocalUserNum;` — User initiating the request
- L391 _private prototype_ `FOnlineAsyncEventSteamLobbyInviteAccepted() = delete;` — Hidden on purpose
- L394 _public function_ `FOnlineAsyncEventSteamLobbyInviteAccepted(FOnlineSubsystemSteam* InSubsystem, const FUniqueNetIdSteam& InFriendId, const FUniqueNetIdSteam& InLobbyId) : FOnlineAsyncEvent(InSubsystem), FriendId(InFriendId.AsShared()), LobbyId(InLobbyId.AsShared()), LocalUserNum(0)`
- L402 _public function_ `virtual ~FOnlineAsyncEventSteamLobbyInviteAccepted()`
- L409 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L415 _public prototype_ `virtual void Finalize() override;` — Give the async task a chance to marshal its data back to the game thread Can only be called on the game thread by the async task manager

#### Free symbols / members of external scopes

- L313 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnAsyncFindLobbyCompleteWithNetId, const bool, const int32, FUniqueNetIdPtr, const class FOnlineSessionSearchResult&);`
- L313 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnAsyncFindLobbyCompleteWithNetId, const bool, const int32, FUniqueNetIdPtr, const class FOnlineSessionSearchResult&);`
- L314 _typedef_ `typedef FOnAsyncFindLobbyCompleteWithNetId::FDelegate FOnAsyncFindLobbyCompleteDelegateWithNetId;`
- L425 _prototype_ `ELobbyType BuildLobbyType(FOnlineSessionSettings* SessionSettings);` — Generate the proper lobby type from session settings @param SessionSettings current settings for the session @return type of lobby to generate, defaulting to private if not advertising and public otherwise
- L438 _prototype_ `bool FillSessionFromLobbyData(FOnlineSubsystemSteam* SteamSubsystem, const FUniqueNetIdSteam& LobbyId, class FOnlineSession& Session, FOnlineSessionSearchResult* SearchData = nullptr);` — Populate an FSession data structure from the data stored with a lobby Expects a certain number of keys to be present otherwise this will fail @param SteamSubsystem the online subsystem to use @param LobbyId the Steam lobby to fill data from @param Session empty session structure to fill in @param SearchData if this is provided and the Steam session supports SteamSockets, the ping for the lobby will be written into the search result data. @return true if successful, false otherwise
- L448 _prototype_ `bool FillMembersFromLobbyData(const FUniqueNetIdSteam& LobbyId, class FNamedOnlineSession& Session);` — Populate an FSession data structure from the data stored with the members of the lobby @param LobbyId the Steam lobby to fill data from @param Session session structure to fill in @return true if successful, false otherwise

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineSessionAsyncServerSteam.h` (Private)


#### class `FOnlineAsyncTaskSteamCreateServer`  
`class FOnlineAsyncTaskSteamCreateServer : public FOnlineAsyncTaskSteam`  
_L17-59_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task for creating a Steam advertised server
- L22 _private member_ `bool bInit;` — Has this request been started
- L24 _private member_ `FName SessionName;` — Name of session being created
- L27 _private prototype_ `FOnlineAsyncTaskSteamCreateServer() = delete;` — Hidden on purpose
- L31 _public function_ `FOnlineAsyncTaskSteamCreateServer(class FOnlineSubsystemSteam* InSubsystem, FName InSessionName) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), bInit(false), SessionName(InSessionName)`
- L41 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L47 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L53 _public prototype_ `virtual void Finalize() override;` — Give the async task a chance to marshal its data back to the game thread Can only be called on the game thread by the async task manager
- L58 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamUpdateServer`  
`class FOnlineAsyncTaskSteamUpdateServer : public FOnlineAsyncTaskSteam`  
_L64-108_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task to update a single Steam lobby
- L69 _private member_ `FName SessionName;` — Name of session being created
- L71 _private member_ `FOnlineSessionSettings NewSessionSettings;` — New session settings to apply
- L73 _private member_ `bool bUpdateOnlineData;` — Should the online platform refresh as well
- L76 _private function_ `FOnlineAsyncTaskSteamUpdateServer() : SessionName(NAME_None), bUpdateOnlineData(false)` — Hidden on purpose
- L85 _public function_ `FOnlineAsyncTaskSteamUpdateServer(class FOnlineSubsystemSteam* InSubsystem, FName InSessionName, bool bInUpdateOnlineData, const FOnlineSessionSettings& InNewSessionSettings) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), SessionName(InSessionName), NewSessionSettings(InNewSessionSettings), bUpdateOnlineData(bInUpdateOnlineData)` — Constructor
- L96 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L102 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L107 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamLogoffServer`  
`class FOnlineAsyncTaskSteamLogoffServer : public FOnlineAsyncTaskSteam`  
_L113-149_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task for shutting down an advertised game erver
- L118 _private member_ `bool bInit;` — Has this request been started
- L120 _private member_ `FName SessionName;` — Name of session
- L123 _private function_ `FOnlineAsyncTaskSteamLogoffServer() : bInit(false), SessionName(NAME_None)` — Hidden on purpose
- L132 _public function_ `FOnlineAsyncTaskSteamLogoffServer(class FOnlineSubsystemSteam* InSubsystem, FName InSessionName) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), bInit(false), SessionName(InSessionName)` — Constructor
- L142 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L148 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread

#### class `FPendingSearchResultSteam`  
`class FPendingSearchResultSteam final : public ISteamMatchmakingRulesResponse`  
_L156-225_
- inherits: `ISteamMatchmakingRulesResponse`
- desc: Container for a single search result returned by the initial server query currently waiting for the Steam rules to be returned before creating a final search result to associate with the currently running query
- L159 _private prototype_ `FPendingSearchResultSteam() = delete;` — Hidden on purpose
- L164 _private member_ `class FOnlineAsyncTaskSteamFindServerBase* ParentQuery;` — Reference to original search query
- L166 _private member_ `HServerQuery ServerQueryHandle;` — Handle to current rules response request with Steam
- L168 _private member_ `FUniqueNetIdSteamRef ServerId;` — Steam Id of the server result
- L170 _private member_ `TSharedPtr<FInternetAddr> HostAddr;` — Host address of the server result (PublicIP)
- L172 _private member_ `FSteamSessionKeyValuePairs ServerRules;` — Placeholder for all returned rules until RulesRefreshComplete call
- L174 _private member_ `FOnlineSessionSearchResult PendingSearchResult;` — Proxy search result until it is known to be valid
- L181 _private prototype_ `bool FillSessionFromServerRules();` — Fills in the proxy search result with all the rules returned by the aux query @return true if session was successfully created, false otherwise
- L186 _private prototype_ `void RemoveSelf();` — Remove this search result from the parent's list of pending entries
- L191 _public function_ `FPendingSearchResultSteam(class FOnlineAsyncTaskSteamFindServerBase* InParentQuery): ParentQuery(InParentQuery), ServerQueryHandle(HSERVERQUERY_INVALID), ServerId(FUniqueNetIdSteam::EmptyId())` — Constructor
- L199 _public function_ `~FPendingSearchResultSteam()`
- L208 _public prototype_ `virtual void RulesResponded(const char *pchRule, const char *pchValue);` — Got data on a rule on the server -- you'll get one of these per rule defined on the server you are querying
- L213 _public prototype_ `virtual void RulesFailedToRespond();` — The server failed to respond to the request for rule details
- L219 _public prototype_ `virtual void RulesRefreshComplete();` — The server has finished responding to the rule details request (ie, you won't get any more RulesResponded callbacks)
- L224 _public prototype_ `void CancelQuery();` — Cancel this rules request

#### class `FOnlineAsyncTaskSteamFindServerBase`  
`class FOnlineAsyncTaskSteamFindServerBase : public FOnlineAsyncTaskSteam, public ISteamMatchmakingServerListResponse`  
_L230-317_
- inherits: `FOnlineAsyncTaskSteam,ISteamMatchmakingServerListResponse`
- desc: Base Async task for finding game servers advertised on the Steam backend (no delegates triggered)
- L235 _private member_ `bool bInit;` — Has this request been started
- L237 _private member_ `bool bServerRefreshComplete;` — Did the initial request complete
- L239 _private member_ `ISteamMatchmakingServers* SteamMatchmakingServersPtr;` — Cached pointer to Steam interface
- L242 _private function_ `FOnlineAsyncTaskSteamFindServerBase() : bInit(false), bServerRefreshComplete(false), SteamMatchmakingServersPtr(NULL), ElapsedTime(0.0f), SearchSettings(NULL), ServerListRequestHandle(NULL)` — Hidden on purpose
- L257 _private member_ `TIndirectArray<FPendingSearchResultSteam> PendingSearchResults;` — Array of search results returned but waiting for rules response
- L259 _private member_ `TSharedPtr<class FOnlineSessionSearch> SearchSettings;` — Search settings specified for the query
- L261 _private member_ `HServerListRequest ServerListRequestHandle;` — Server list request handle
- L265 _public function_ `FOnlineAsyncTaskSteamFindServerBase(class FOnlineSubsystemSteam* InSubsystem, const TSharedPtr<class FOnlineSessionSearch>& InSearchSettings) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), bInit(false), bServerRefreshComplete(false), SteamMatchmakingServersPtr(NULL), ElapsedTime(0.0f), SearchSettings(InSearchSettings), ServerListRequestHandle(NULL)`
- L282 _public prototype_ `virtual void CreateQuery(MatchMakingKeyValuePair_t** OutFilter, int32& NumFilters);` — Create the proper query for the server list based on the given search settings @param OutFilter Steam structure containing the proper filters @param NumFilters number of filters contained in the array above
- L289 _public prototype_ `void ParseSearchResult(class gameserveritem_t* ServerDetails);` — Create a proxy search result from a server response, triggers additional rules query @param ServerDetails Steam server details
- L295 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L300 _public prototype_ `void ServerResponded(HServerListRequest Request, int iServer) override;` — Called by the SteamAPI when a server has successfully responded
- L305 _public prototype_ `void ServerFailedToRespond(HServerListRequest Request, int iServer) override;` — Called by the SteamAPI when a server has failed to respond
- L310 _public prototype_ `void RefreshComplete(HServerListRequest Request, EMatchMakingServerResponse Response) override;` — Called by the SteamAPI when all server requests for the list have completed
- L316 _public prototype_ `virtual void Finalize() override;` — Give the async task a chance to marshal its data back to the game thread Can only be called on the game thread by the async task manager

#### class `FOnlineAsyncTaskSteamFindServerForInviteSession`  
`class FOnlineAsyncTaskSteamFindServerForInviteSession : public FOnlineAsyncTaskSteamFindServerBase`  
_L323-348_
- inherits: `FOnlineAsyncTaskSteamFindServerBase`
- L327 _protected member_ `int32 LocalUserNum;` — User initiating the request
- L329 _protected member_ `FOnAsyncFindServerInviteCompleteWithNetId FindServerInviteCompleteWithUserIdDelegates;`
- L332 _public function_ `FOnlineAsyncTaskSteamFindServerForInviteSession(class FOnlineSubsystemSteam* InSubsystem, const TSharedPtr<class FOnlineSessionSearch>& InSearchSettings, int32 InLocalUserNum, FOnAsyncFindServerInviteCompleteWithNetId& InDelegates) : FOnlineAsyncTaskSteamFindServerBase(InSubsystem, InSearchSettings) , LocalUserNum(InLocalUserNum) , FindServerInviteCompleteWithUserIdDelegates(InDelegates)`
- L342 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L347 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamFindServerForFriendSession`  
`class FOnlineAsyncTaskSteamFindServerForFriendSession : public FOnlineAsyncTaskSteamFindServerBase`  
_L350-375_
- inherits: `FOnlineAsyncTaskSteamFindServerBase`
- L354 _protected member_ `int32 LocalUserNum;` — User initiating the request
- L356 _protected member_ `FOnFindFriendSessionComplete FindServerInviteCompleteDelegates;`
- L359 _public function_ `FOnlineAsyncTaskSteamFindServerForFriendSession(class FOnlineSubsystemSteam* InSubsystem, const TSharedPtr<class FOnlineSessionSearch>& InSearchSettings, int32 InLocalUserNum, FOnFindFriendSessionComplete& InDelegates) : FOnlineAsyncTaskSteamFindServerBase(InSubsystem, InSearchSettings) , LocalUserNum(InLocalUserNum) , FindServerInviteCompleteDelegates(InDelegates)`
- L369 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L374 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamFindServers`  
`class FOnlineAsyncTaskSteamFindServers : public FOnlineAsyncTaskSteamFindServerBase`  
_L388-412_
- inherits: `FOnlineAsyncTaskSteamFindServerBase`
- desc: Async task for finding multiple servers and signaling the proper delegate on completion
- L393 _protected member_ `FOnAsyncFindServersComplete FindServersCompleteDelegates;` — General "find servers" delegate
- L397 _public function_ `FOnlineAsyncTaskSteamFindServers(class FOnlineSubsystemSteam* InSubsystem, const TSharedPtr<class FOnlineSessionSearch>& InSearchSettings, FOnAsyncFindServersComplete& InDelegates) : FOnlineAsyncTaskSteamFindServerBase(InSubsystem, InSearchSettings), FindServersCompleteDelegates(InDelegates)`
- L406 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L411 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncEventSteamInviteAccepted`  
`class FOnlineAsyncEventSteamInviteAccepted : public FOnlineAsyncEvent<FOnlineSubsystemSteam>`  
_L417-456_
- inherits: `FOnlineAsyncEvent<FOnlineSubsystemSteam>`
- desc: Turns a friends accepted invite request into a valid search result (server list version)
- L420 _private member_ `FUniqueNetIdSteamRef FriendId;` — Friend who invited the user
- L422 _private member_ `FString ConnectionURL;` — Connection string
- L424 _private member_ `int32 LocalUserNum;` — User initiating the request
- L427 _private prototype_ `FOnlineAsyncEventSteamInviteAccepted() = delete;` — Hidden on purpose
- L431 _public function_ `FOnlineAsyncEventSteamInviteAccepted(FOnlineSubsystemSteam* InSubsystem, const FUniqueNetIdSteam& InFriendId, const FString& InConnectionURL) : FOnlineAsyncEvent(InSubsystem), FriendId(FUniqueNetIdSteam::EmptyId()), ConnectionURL(InConnectionURL), LocalUserNum(0)`
- L439 _public function_ `~FOnlineAsyncEventSteamInviteAccepted()`
- L446 _public function_ `virtual FString ToString() const override` — Get a human readable description of task
- L455 _public prototype_ `virtual void Finalize() override;` — Give the async task a chance to marshal its data back to the game thread Can only be called on the game thread by the async task manager

#### Free symbols / members of external scopes

- L12 _macro_ `#define SEARCH_STEAM_HOSTIP TEXT("SteamHostIp")` — Well defined keys for use with Steam game servers
- L320 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnAsyncFindServerInviteCompleteWithNetId, const bool, const int32, FUniqueNetIdPtr, const class FOnlineSessionSearchResult&);`
- L320 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnAsyncFindServerInviteCompleteWithNetId, const bool, const int32, FUniqueNetIdPtr, const class FOnlineSessionSearchResult&);`
- L321 _typedef_ `typedef FOnAsyncFindServerInviteCompleteWithNetId::FDelegate FOnAsyncFindServerInviteCompleteWithNetIdDelegate;`
- L382 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAsyncFindServersComplete, bool);` — Delegate fired when the search for servers has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L382 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAsyncFindServersComplete, bool);` — Delegate fired when the search for servers has completed @param bWasSuccessful true if the async action completed without error, false if there was an error
- L383 _typedef_ `typedef FOnAsyncFindServersComplete::FDelegate FOnAsyncFindServersCompleteDelegate;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineSessionInterfaceSteam.h` (Private)


#### class `FOnlineSessionSteam`  
`class FOnlineSessionSteam : public IOnlineSession`  
_L22-555_
- inherits: `IOnlineSession`
- desc: Interface definition for the online services session services Session services are defined as anything related managing a session and its state within a platform service
- L27 _private member_ `class FOnlineSubsystemSteam* SteamSubsystem;` — Reference to the main Steam subsystem
- L30 _private member_ `class FLANSession* LANSession;` — Instance of a LAN session for hosting/client searches
- L33 _private function_ `FOnlineSessionSteam() : SteamSubsystem(NULL), LANSession(NULL), bSteamworksGameServerConnected(false), GameServerSteamId(NULL), bPolicyResponseReceived(false), CurrentSessionSearch(NULL)` — Hidden on purpose
- L47 _private prototype_ `void TickLanTasks(float DeltaTime);` — Ticks any lan beacon background tasks @param DeltaTime the time since the last tick
- L53 _private prototype_ `void TickPendingInvites(float DeltaTime);` — Tick invites captured from the command line Waits for a delegate to be listening before triggering
- L63 _private prototype_ `uint32 CreateLobbySession(int32 HostingPlayerNum, class FNamedOnlineSession* Session);` — Create a lobby session, advertised on the Steam backend @param HostingPlayerNum local index of the user initiating the request @param Session newly allocated session to create @return ONLINE_SUCCESS if successful, an error code otherwise
- L73 _private prototype_ `uint32 CreateInternetSession(int32 HostingPlayerNum, class FNamedOnlineSession* Session);` — Create a game server session, advertised on the Steam backend @param HostingPlayerNum local index of the user initiating the request @param Session newly allocated session to create @return ONLINE_SUCCESS if successful, an error code otherwise
- L84 _private prototype_ `uint32 JoinLobbySession(int32 PlayerNum, class FNamedOnlineSession* Session, const FOnlineSession* SearchSession);` — Join a lobby session, advertised on the Steam backend @param PlayerNum local index of the user initiating the request @param Session newly allocated session with join information @param SearchSession the desired session to join @return ONLINE_SUCCESS if successful, an error code otherwise
- L95 _private prototype_ `uint32 JoinInternetSession(int32 PlayerNum, FNamedOnlineSession* Session, const FOnlineSession* SearchSession);` — Join a game server session, advertised on the Steam backend @param PlayerNum local index of the user initiating the request @param Session newly allocated session with join information @param SearchSession the desired session to join @return ONLINE_SUCCESS if successful, an error code otherwise
- L105 _private prototype_ `uint32 EndInternetSession(class FNamedOnlineSession* Session);` — End an internet session, advertised on the Steam backend NOTE: Lobby sessions remain active until DestroyOnlineSession @param Session session to end @return ONLINE_SUCCESS if successful, an error code otherwise
- L114 _private prototype_ `uint32 DestroyLobbySession(class FNamedOnlineSession* Session, const FOnDestroySessionCompleteDelegate& CompletionDelegate);` — Destroy a lobby session, advertised on the Steam backend @param Session session to destroy @return ONLINE_SUCCESS if successful, an error code otherwise
- L123 _private prototype_ `uint32 DestroyInternetSession(class FNamedOnlineSession* Session, const FOnDestroySessionCompleteDelegate& CompletionDelegate);` — Destroy an internet session, advertised on the Steam backend @param Session session to destroy @return ONLINE_SUCCESS if successful, an error code otherwise
- L133 _private prototype_ `uint32 CreateLANSession(int32 HostingPlayerNum, class FNamedOnlineSession* Session);` — Create a local LAN session, managed by a beacon on the host @param HostingPlayerNum local index of the user initiating the request @param Session newly allocated session to create @return ONLINE_SUCCESS if successful, an error code otherwise
- L144 _private prototype_ `uint32 JoinLANSession(int32 PlayerNum, class FNamedOnlineSession* Session, const class FOnlineSession* SearchSession);` — Join a LAN session @param PlayerNum local index of the user initiating the request @param Session newly allocated session with join information @param SearchSession the desired session to join @return ONLINE_SUCCESS if successful, an error code otherwise
- L151 _private prototype_ `uint32 FindInternetSession(const TSharedRef<FOnlineSessionSearch>& SearchSettings);` — Builds a Steamworks query and submits it to the Steamworks backend @return an Error/success code
- L158 _private prototype_ `uint32 FindLANSession(const TSharedRef<FOnlineSessionSearch>& SearchSettings);` — Builds a LAN search query and broadcasts it @return ONLINE_SUCCESS if successful, an error code otherwise
- L167 _private prototype_ `void AppendSessionToPacket(class FNboSerializeToBufferSteam& Packet, class FOnlineSession* Session);` — Adds the game session data to the packet that is sent by the host in response to a server query @param Packet the writer object that will encode the data @param Session the session to add to the packet
- L176 _private prototype_ `void AppendSessionSettingsToPacket(class FNboSerializeToBufferSteam& Packet, FOnlineSessionSettings* SessionSettings);` — Adds the game settings data to the packet that is sent by the host in response to a server query @param Packet the writer object that will encode the data @param SessionSettings the session settings to add to the packet
- L185 _private prototype_ `void ReadSessionFromPacket(class FNboSerializeFromBufferSteam& Packet, class FOnlineSession* Session);` — Reads the settings data from the packet and applies it to the specified object @param Packet the reader object that will read the data @param SessionSettings the session settings to copy the data to
- L194 _private prototype_ `void ReadSettingsFromPacket(class FNboSerializeFromBufferSteam& Packet, FOnlineSessionSettings& SessionSettings);` — Reads the settings data from the packet and applies it to the specified object @param Packet the reader object that will read the data @param SessionSettings the session settings to copy the data to
- L203 _private prototype_ `void OnValidQueryPacketReceived(uint8* PacketData, int32 PacketLength, uint64 ClientNonce);` — Delegate triggered when the LAN beacon has detected a valid client request has been received @param PacketData packet data sent by the requesting client with header information removed @param PacketLength length of the packet not including header size @param ClientNonce the nonce returned by the client to return with the server packet
- L211 _private prototype_ `void OnValidResponsePacketReceived(uint8* PacketData, int32 PacketLength);` — Delegate triggered when the LAN beacon has detected a valid host response to a client request has been received @param PacketData packet data sent by the requesting client with header information removed @param PacketLength length of the packet not including header size
- L216 _private prototype_ `void OnLANSearchTimeout();` — Delegate triggered when the LAN beacon has finished searching (some time after last received host packet)
- L223 _private prototype_ `void RegisterVoice(const FUniqueNetId& PlayerId);` — Registers and updates voice data for the given player id @param PlayerId player to register with the voice subsystem
- L230 _private prototype_ `void UnregisterVoice(const FUniqueNetId& PlayerId);` — Unregisters a given player id from the voice subsystem @param PlayerId player to unregister with the voice subsystem
- L238 _private member_ `TArray<FNamedOnlineSession> Sessions;` — Current session settings
- L241 _private member_ `bool bSteamworksGameServerConnected;` — Whether or not the Steam game server API is fully logged in and connected (GameServerSteamId is valid)
- L244 _private member_ `FUniqueNetIdSteamPtr GameServerSteamId;` — CSteamId assigned on game server login (only valid if bSteamworksGameServerConnected is true)
- L247 _private member_ `bool bPolicyResponseReceived;` — Has the GSPolicyResponse callback triggered
- L250 _private member_ `TSharedPtr<FOnlineSessionSearch> CurrentSessionSearch;` — Current search object
- L270 _private member_ `FPendingInviteData PendingInvite;` — Contains information about a join/invite parsed from the commandline
- L273 _private member_ `TArray<FUniqueNetIdSteamRef> PendingSearchLobbyIds;` — List of lobby data that is available for parsing (READ/WRITE game thread READONLY online thread)
- L276 _private member_ `FCriticalSection JoinedLobbyLock;` — Critical sections for thread safe operation of the lobby lists
- L279 _private member_ `TArray<FUniqueNetIdSteamRef> JoinedLobbyList;` — List of lobbies this client is a member of
- L281 _private function_ `FOnlineSessionSteam(class FOnlineSubsystemSteam* InSubsystem) : SteamSubsystem(InSubsystem), LANSession(NULL), bSteamworksGameServerConnected(false), GameServerSteamId(NULL), bPolicyResponseReceived(false), CurrentSessionSearch(NULL)`
- L293 _private prototype_ `void Tick(float DeltaTime);` — Session tick for various background tasks
- L303 _private function_ `class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSessionSettings& SessionSettings) override` — Adds a new named session to the list (new session) @param SessionName the name to search for @param GameSettings the game settings to add @return a pointer to the struct that was added
- L317 _private function_ `class FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSession& Session) override` — Adds a new named session to the list (from existing session data) @param SessionName the name to search for @param GameSettings the game settings to add @return a pointer to the struct that was added
- L330 _private function_ `inline FNamedOnlineSession* GetNamedSessionFromLobbyId(const FUniqueNetIdSteam& LobbyId)` — Searches the named session array for the specified session @param LobbyId the lobby id to search for @return pointer to the struct if found, NULL otherwise
- L354 _private function_ `inline FNamedOnlineSession* GetGameServerSession()` — Return the game server based session NOTE: Assumes there is at most one, non-lobby session @return pointer to the struct if found, NULL otherwise
- L376 _private prototype_ `void SyncLobbies();` — Debug function to make sure that the sessions and lobbies are in sync Leaves any lobby that doesn't have a session associated with it
- L383 _private function_ `void JoinedLobby(const FUniqueNetIdSteam& LobbyId)` — Keep track of lobbies joined @param LobbyId lobby being joined
- L394 _private function_ `void LeftLobby(const FUniqueNetIdSteam& LobbyId)` — Keep track of lobbies left @param LobbyId lobby being left
- L415 _private function_ `bool IsMemberOfLobby(const FUniqueNetIdSteam& LobbyId)` — Has a particular lobby been joined already @param LobbyId lobby to query @return true if member of lobby, else false
- L436 _private prototype_ `FString GetSteamConnectionString(FName SessionName);` — Create the proper connection string so another user can connect to the given session @param SessionName the session to create the string for @return the proper connection string for this session
- L441 _private prototype_ `void CheckPendingSessionInvite();` — Parse the command line for invite/join information at launch
- L448 _private prototype_ `void RegisterLocalPlayers(class FNamedOnlineSession* Session);` — Registers all local players with the current session @param Session the session that they are registering in
- L457 _private prototype_ `FString GetCustomDedicatedServerName() const;` — Parses the dedicated server custom name launch argument as specified by the -SteamServerName= flag. @return the custom name if the value of the launch argument is specified and less than 64 characters otherwise returns empty string
- L461 _public function_ `virtual ~FOnlineSessionSteam()`
- L463 _public prototype_ `virtual FUniqueNetIdPtr CreateSessionIdFromString(const FString& SessionIdStr) override;`
- L465 _public function_ `FNamedOnlineSession* GetNamedSession(FName SessionName) override`
- L478 _public function_ `virtual void RemoveNamedSession(FName SessionName) override`
- L491 _public function_ `virtual EOnlineSessionState::Type GetSessionState(FName SessionName) const override`
- L505 _public function_ `virtual bool HasPresenceSession() override`
- L520 _public prototype_ `virtual bool CreateSession(int32 HostingPlayerNum, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;` — IOnlineSession
- L521 _public prototype_ `virtual bool CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;`
- L522 _public prototype_ `virtual bool StartSession(FName SessionName) override;`
- L523 _public prototype_ `virtual bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData = true) override;`
- L524 _public prototype_ `virtual bool EndSession(FName SessionName) override;`
- L525 _public prototype_ `virtual bool DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate = FOnDestroySessionCompleteDelegate()) override;`
- L526 _public prototype_ `virtual bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId) override;`
- L527 _public prototype_ `virtual bool StartMatchmaking(const TArray< FUniqueNetIdRef >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L528 _public prototype_ `virtual bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName) override;`
- L529 _public prototype_ `virtual bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName) override;`
- L530 _public prototype_ `virtual bool FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L531 _public prototype_ `virtual bool FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;`
- L532 _public prototype_ `virtual bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate) override;`
- L533 _public prototype_ `virtual bool CancelFindSessions() override;`
- L534 _public prototype_ `virtual bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult) override;`
- L535 _public prototype_ `virtual bool JoinSession(int32 PlayerNum, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L536 _public prototype_ `virtual bool JoinSession(const FUniqueNetId& PlayerId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;`
- L537 _public prototype_ `virtual bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend) override;`
- L538 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend) override;`
- L539 _public prototype_ `virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList) override;`
- L540 _public prototype_ `virtual bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend) override;`
- L541 _public prototype_ `virtual bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend) override;`
- L542 _public prototype_ `virtual bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L543 _public prototype_ `virtual bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< FUniqueNetIdRef >& Friends) override;`
- L544 _public prototype_ `virtual bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType) override;`
- L545 _public prototype_ `virtual bool GetResolvedConnectString(const FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo) override;`
- L546 _public prototype_ `virtual FOnlineSessionSettings* GetSessionSettings(FName SessionName) override;`
- L547 _public prototype_ `virtual bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited) override;`
- L548 _public prototype_ `virtual bool RegisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players, bool bWasInvited = false) override;`
- L549 _public prototype_ `virtual bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId) override;`
- L550 _public prototype_ `virtual bool UnregisterPlayers(FName SessionName, const TArray< FUniqueNetIdRef >& Players) override;`
- L551 _public prototype_ `virtual void RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate) override;`
- L552 _public prototype_ `virtual void UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate) override;`
- L553 _public prototype_ `virtual int32 GetNumSessions() override;`
- L554 _public prototype_ `virtual void DumpSessionState() override;`

#### struct `FOnlineSessionSteam::FPendingInviteData`  
`struct FPendingInviteData`  
_L253-267_
- desc: Any invite/join from the command line
- L256 _public member_ `ESteamSession::Type PendingInviteType;` — What kind of invite is this
- L258 _public member_ `FUniqueNetIdSteamRef LobbyId;` — Lobby invite information
- L260 _public member_ `FString ServerIp;` — Server invite information
- L262 _public function_ `FPendingInviteData() : PendingInviteType(ESteamSession::None), LobbyId(FUniqueNetIdSteam::EmptyId())`

#### Free symbols / members of external scopes

- L12 _macro_ `#define ASYNC_TASK_TIMEOUT 15.0f` — Async Task timeout value
- L15 _typedef_ `typedef FOnlineKeyValuePairs<FString, FString> FSteamSessionKeyValuePairs;` — Structure to hold key value pairs (as FStrings) for Steam
- L557 _typedef_ `typedef TSharedPtr<FOnlineSessionSteam, ESPMode::ThreadSafe> FOnlineSessionSteamPtr;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineSharedCloudInterfaceSteam.h` (Private)


#### class `FOnlineAsyncTaskSteamReadSharedFile`  
`class FOnlineAsyncTaskSteamReadSharedFile : public FOnlineAsyncTaskSteam`  
_L11-62_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task for reading/downloading a single publicly shared cloud file
- L16 _private member_ `bool bInit;` — Has this request been started
- L18 _private member_ `FSharedContentHandleSteam SharedHandle;` — Steam representation of handle
- L21 _private function_ `FOnlineAsyncTaskSteamReadSharedFile() : bInit(false), SharedHandle(k_UGCHandleInvalid)` — Hidden on purpose
- L34 _public function_ `FOnlineAsyncTaskSteamReadSharedFile(class FOnlineSubsystemSteam* InSubsystem, const FSharedContentHandleSteam& InSharedHandle) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), bInit(false), SharedHandle(InSharedHandle)`
- L44 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L50 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L56 _public prototype_ `virtual void Finalize() override;` — Give the async task a chance to marshal its data back to the game thread Can only be called on the game thread by the async task manager
- L61 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamWriteSharedFile`  
`class FOnlineAsyncTaskSteamWriteSharedFile : public FOnlineAsyncTaskSteamWriteUserFile`  
_L67-110_
- inherits: `FOnlineAsyncTaskSteamWriteUserFile`
- desc: Async task for writing to disk then sharing a user's cloud file
- L72 _private member_ `bool bInit;` — Has this request been started
- L75 _private prototype_ `FOnlineAsyncTaskSteamWriteSharedFile() = delete;` — Hidden on purpose
- L84 _public function_ `FOnlineAsyncTaskSteamWriteSharedFile(class FOnlineSubsystemSteam* InSubsystem, const FUniqueNetIdSteam& InUserId, const FString& InFileName, const TArray<uint8>& InContents) : FOnlineAsyncTaskSteamWriteUserFile(InSubsystem, InUserId, InFileName, InContents), bInit(false)`
- L93 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L99 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L104 _public prototype_ `virtual void Finalize() override;` — Write out the state of the request
- L109 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineSharedCloudSteam`  
`class FOnlineSharedCloudSteam : public IOnlineSharedCloud`  
_L115-160_
- inherits: `IOnlineSharedCloud`
- desc: Provides the interface for sharing files already on the cloud with other users
- L120 _protected member_ `class FOnlineSubsystemSteam* SteamSubsystem;` — Reference to the main Steam subsystem
- L122 _protected member_ `TArray<struct FCloudFileSteam*> SharedFileCache;` — Array of all files downloaded/cached by the system
- L124 _protected function_ `FOnlineSharedCloudSteam() : SteamSubsystem(NULL)`
- L144 _protected prototype_ `struct FCloudFileSteam* GetSharedCloudFile(const FSharedContentHandle& SharedHandle);` — **INTERNAL** Get the file entry related to a shared download @param SharedHandle the handle to search for @return the struct with the metadata about the requested shared data, will always return a valid struct, creating one if necessary
- L148 _public function_ `virtual ~FOnlineSharedCloudSteam()`
- L154 _public prototype_ `virtual bool GetSharedFileContents(const FSharedContentHandle& SharedHandle, TArray<uint8>& FileContents) override;` — IOnlineSharedCloud
- L155 _public prototype_ `virtual bool ClearSharedFiles() override final;`
- L156 _public prototype_ `virtual bool ClearSharedFile(const FSharedContentHandle& SharedHandle) override;`
- L157 _public prototype_ `virtual bool ReadSharedFile(const FSharedContentHandle& SharedHandle) override;`
- L158 _public prototype_ `virtual bool WriteSharedFile(const FUniqueNetId& UserId, const FString& Filename, TArray<uint8>& FileContents) override;`
- L159 _public prototype_ `virtual void GetDummySharedHandlesForTest(TArray< TSharedRef<FSharedContentHandle> > & OutHandles) override;`

#### Free symbols / members of external scopes

- L162 _typedef_ `typedef TSharedPtr<FOnlineSharedCloudSteam, ESPMode::ThreadSafe> FOnlineSharedCloudSteamPtr;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineStoreInterfaceSteam.h` (Private)


#### class `FOnlineStoreSteam`  
`class FOnlineStoreSteam : public IOnlineStoreV2, public TSharedFromThis<FOnlineStoreSteam, ESPMode::ThreadSafe>`  
_L16-38_
- inherits: `IOnlineStoreV2,TSharedFromThis<FOnlineStoreSteam,ESPMode::ThreadSafe>`
- desc: Implementation for online store via Steam
- L21 _public prototype_ `FOnlineStoreSteam(FOnlineSubsystemSteam* InSteamSubsystem);`
- L22 _public prototype_ `virtual ~FOnlineStoreSteam();`
- L25 _public prototype_ `virtual void QueryCategories(const FUniqueNetId& UserId, const FOnQueryOnlineStoreCategoriesComplete& Delegate) override;`
- L26 _public prototype_ `virtual void GetCategories(TArray<FOnlineStoreCategory>& OutCategories) const override;`
- L27 _public prototype_ `virtual void QueryOffersByFilter(const FUniqueNetId& UserId, const FOnlineStoreFilter& Filter, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L28 _public prototype_ `virtual void QueryOffersById(const FUniqueNetId& UserId, const TArray<FUniqueOfferId>& OfferIds, const FOnQueryOnlineStoreOffersComplete& Delegate) override;`
- L29 _public prototype_ `virtual void GetOffers(TArray<FOnlineStoreOfferRef>& OutOffers) const override;`
- L30 _public prototype_ `virtual TSharedPtr<FOnlineStoreOffer> GetOffer(const FUniqueOfferId& OfferId) const override;`
- L35 _public member_ `TSharedPtr<FOnlinePurchaseSteam> SteamPurchaseInt;`
- L36 _public member_ `TArray<FOnlineStoreCategory> CachedCategories;`
- L37 _public member_ `TMap<FUniqueOfferId, FOnlineStoreOfferRef> CachedOffers;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineSubsystemSteamPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define INVALID_INDEX -1`
- L11 _macro_ `#define STEAM_URL_PREFIX TEXT("steam.")` — URL Prefix when using Steam socket connection
- L15 _macro_ `#define ONLINE_LOG_PREFIX TEXT("STEAM: ")`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineSubsystemSteamTypes.h` (Private)


#### enum `ESteamSession::Type`  
`enum Type`  
_L13-25_
- L16 _public enumerator_ `None` — Session is undefined
- L18 _public enumerator_ `LobbySession` — Session managed as a lobby on backend
- L20 _public enumerator_ `AdvertisedSessionHost` — Session managed by the server list
- L22 _public enumerator_ `AdvertisedSessionClient` — Session client of a game server session
- L24 _public enumerator_ `LANSession` — Session managed by LAN beacon

#### class `FUniqueNetIdSteam`  
`class FUniqueNetIdSteam : public FUniqueNetId`  
_L63-261_
- inherits: `FUniqueNetId`
- desc: Steam specific implementation of the unique net id
- L72 _public function_ `template<typename... TArgs> static FUniqueNetIdSteamRef Create(TArgs&&... Args)`
- L77 _public function_ `static const FUniqueNetIdSteam& Cast(const FUniqueNetId& NetId)`
- L82 _public function_ `FUniqueNetIdSteamRef AsShared() const`
- L87 _public function_ `virtual FName GetType() const override`
- L98 _public function_ `virtual const uint8* GetBytes() const override` — Get the raw byte representation of this net id This data is platform dependent and shouldn't be manipulated directly @return byte array of size GetSize()
- L108 _public function_ `virtual int32 GetSize() const override` — Get the size of the id @return size in bytes of the id representation
- L118 _public function_ `virtual bool IsValid() const override` — Check the validity of the id @return true if this is a well formed ID, false otherwise
- L128 _public function_ `virtual FString ToString() const override` — Platform specific conversion to string representation of data @return data in string form
- L139 _public function_ `virtual FString ToDebugString() const override` — Get a human readable representation of the net id Shouldn't be used for anything other than logging/debugging @return id in string form
- L163 _public function_ `static FString ToDebugString(CSteamID SteamID)`
- L169 _public function_ `virtual uint32 GetTypeHash() const override`
- L175 _public function_ `static const FUniqueNetIdSteamRef& EmptyId()` — global static instance of invalid (zero) id
- L182 _public function_ `operator CSteamID()` — Convenience cast to CSteamID
- L188 _public function_ `operator const CSteamID() const` — Convenience cast to CSteamID
- L194 _public function_ `operator CSteamID*()` — Convenience cast to CSteamID pointer
- L200 _public function_ `operator const CSteamID*() const` — Convenience cast to CSteamID pointer
- L207 _private function_ `FUniqueNetIdSteam() : UniqueNetId(0)` — Hidden on purpose
- L217 _private function_ `explicit FUniqueNetIdSteam(const FUniqueNetIdSteam& Src) : UniqueNetId(Src.UniqueNetId)` — Copy Constructor @param Src the id to copy
- L227 _private function_ `explicit FUniqueNetIdSteam(uint64 InUniqueNetId) : UniqueNetId(InUniqueNetId)` — Constructs this object with the specified net id @param InUniqueNetId the id to set ours to
- L237 _private function_ `explicit FUniqueNetIdSteam(CSteamID InSteamId) : UniqueNetId(InSteamId.ConvertToUint64())` — Constructs this object with the steam id @param InUniqueNetId the id to set ours to
- L247 _private function_ `explicit FUniqueNetIdSteam(const FString& Str) : UniqueNetId(FCString::Atoi64(*Str))` — Constructs this object with the specified net id @param String textual representation of an id
- L257 _private function_ `explicit FUniqueNetIdSteam(const FUniqueNetId& InUniqueNetId) : UniqueNetId(*(uint64*)InUniqueNetId.GetBytes())` — Constructs this object with the specified net id @param InUniqueNetId the id to set ours to (assumed to be FUniqueNetIdSteam in fact)

#### enum `FSteamConnectionMethod`  
`enum class FSteamConnectionMethod : int8`  
_L264-270_
- desc: Data regarding preferred session connection methods
- L266 _public enumerator_ `None=0`
- L267 _public enumerator_ `Direct`
- L268 _public enumerator_ `P2P`
- L269 _public enumerator_ `PartnerHosted`

#### class `FOnlineSessionInfoSteam`  
`class FOnlineSessionInfoSteam : public FOnlineSessionInfo`  
_L279-376_
- inherits: `FOnlineSessionInfo`
- desc: Implementation of session information
- L284 _protected prototype_ `FOnlineSessionInfoSteam(const FOnlineSessionInfoSteam& Src) = delete;` — Hidden on purpose
- L285 _protected prototype_ `FOnlineSessionInfoSteam& operator=(const FOnlineSessionInfoSteam& Src) = delete;`
- L293 _protected prototype_ `FOnlineSessionInfoSteam(ESteamSession::Type SessionType, const FUniqueNetIdSteam& InSessionId);` — Constructor for sessions that represent a Steam lobby or an advertised server session
- L298 _protected prototype_ `void Init();` — Initialize a Steam session info with the address of this machine
- L303 _protected prototype_ `void InitLAN();` — Initialize a Steam session info with the address of this machine
- L306 _protected member_ `ESteamSession::Type SessionType;` — Type of session this is, affects interpretation of id below
- L308 _protected member_ `TSharedPtr<class FInternetAddr> HostAddr;` — The ip & port that the host is listening on (valid for LAN/GameServer)
- L310 _protected member_ `TSharedPtr<class FInternetAddr> SteamP2PAddr;` — The Steam P2P address that the host is listening on (valid for GameServer/Lobby)
- L312 _protected member_ `FUniqueNetIdSteamRef SessionId;` — Steam Lobby Id or Gameserver Id if applicable
- L314 _protected member_ `FSteamConnectionMethod ConnectionMethod;` — How this session should be connected to
- L318 _public function_ `virtual ~FOnlineSessionInfoSteam()`
- L323 _public function_ `bool operator==(const FOnlineSessionInfoSteam& Other) const` — Comparison operator
- L328 _public function_ `virtual const uint8* GetBytes() const override`
- L333 _public function_ `virtual int32 GetSize() const override`
- L343 _public function_ `virtual bool IsValid() const override`
- L359 _public function_ `virtual FString ToString() const override`
- L364 _public function_ `virtual FString ToDebugString() const override`
- L372 _public function_ `virtual const FUniqueNetId& GetSessionId() const override`

#### class `FSharedContentHandleSteam`  
`class FSharedContentHandleSteam : public FSharedContentHandle`  
_L381-462_
- inherits: `FSharedContentHandle`
- desc: Steam specific implementation of a shared file handle
- L386 _private member_ `const UGCHandle_t SharedContentHandle;` — Holds the handle to the shared content
- L389 _private prototype_ `FSharedContentHandleSteam() = delete;` — Hidden on purpose
- L398 _public function_ `FSharedContentHandleSteam(UGCHandle_t InSharedContentHandle) : SharedContentHandle(InSharedContentHandle)` — Constructs this object with the specified shared content id @param InUniqueNetId the id to set ours to
- L406 _public function_ `bool operator==(const FSharedContentHandleSteam& Other) const` — Comparison operator
- L417 _public function_ `virtual const uint8* GetBytes() const override` — Get the raw byte representation of this shared content handle This data is platform dependent and shouldn't be manipulated directly @return byte array of size GetSize()
- L427 _public function_ `virtual int32 GetSize() const override` — Get the size of this shared content handle @return size in bytes of the id representation
- L437 _public function_ `virtual bool IsValid() const override` — Check the validity of this shared content handle @return true if this is a well formed ID, false otherwise
- L447 _public function_ `virtual FString ToString() const override` — Platform specific conversion to string representation of data @return data in string form
- L458 _public function_ `virtual FString ToDebugString() const override` — Get a human readable representation of this shared content handle Shouldn't be used for anything other than logging/debugging @return handle in string form

#### struct `FCloudFileSteam`  
`struct FCloudFileSteam : public FCloudFile`  
_L465-482_
- inherits: `FCloudFile`
- desc: Holds the data used in downloading a file asynchronously from the online service
- L468 _public member_ `const FSharedContentHandleSteam SharedHandle;` — The name of the file as requested
- L471 _public function_ `FCloudFileSteam() : SharedHandle(k_UGCHandleInvalid)` — Constructors
- L476 _public function_ `FCloudFileSteam(const FSharedContentHandleSteam& InSharedHandle) : SharedHandle(InSharedHandle)`
- L481 _public function_ `~FCloudFileSteam()`

#### struct `FSteamUserCloudData`  
`struct FSteamUserCloudData`  
_L491-659_
- desc: Record containing the state of cloud files for a given user as requested from <Enumerate/Read/Write/Delete><User/Shared>Files Does not necessarily represent the full state of all files for a given user This is an ASYNC data structure, make sure proper locks are in place before manipulating
- L494 _public member_ `TArray<struct FCloudFileHeader> CloudMetadata;` — File metadata
- L496 _public member_ `TArray<struct FCloudFile> CloudFileData;` — File cache
- L500 _public member_ `const FUniqueNetIdSteamRef UserId;` — Owning user for these files
- L503 _public function_ `FSteamUserCloudData(const FUniqueNetIdSteam& InUserId) : UserId(InUserId.AsShared())` — Constructors
- L508 _public function_ `~FSteamUserCloudData()`
- L519 _public function_ `bool ClearFiles()` — Clear out all cached data for a given user Doesn't touch metadata @return true if successful, false otherwise
- L538 _public function_ `bool ClearFileData(const FString& FileName)` — Clear out cached data of a given file for a given user Doesn't touch metadata @param FileName file data to clear @return true if file was cleared, false otherwise
- L569 _public function_ `void ClearMetadata()` — Clear out all file metadata Doesn't touch actual cached file data contents
- L579 _public function_ `void ClearMetadata(const FString& FileName)` — Clear out metadata for a given file Doesn't touch actual cached file data contents @param FileName file metadata to clear
- L607 _public function_ `struct FCloudFileHeader* GetFileMetadata(const FString& FileName, bool bCreateIfMissing=false)` — Get the metadata related to a given user's file on Steam This information is only available after calling EnumerateUserFiles @param FileName the file to get metadata about @param bCreateIfMissing create an entry if not found @return the struct with the metadata about the requested file, NULL otherwise
- L637 _public function_ `struct FCloudFile* GetFileData(const FString& FileName, bool bCreateIfMissing=false)` — Get physical/logical file information for a given user's cloud file @param FileName the file to search for @param bCreateIfMissing create an entry if not found @return the file details, NULL otherwise

#### class `FLeaderboardMetadataSteam`  
`class FLeaderboardMetadataSteam`  
_L664-702_
- desc: Basic leaderboard representation
- L666 _private function_ `FLeaderboardMetadataSteam()`
- L671 _public member_ `FString LeaderboardName;` — Name of leaderboard, matches Steam backend
- L673 _public member_ `ELeaderboardSort::Type SortMethod;` — Sort Method
- L675 _public member_ `ELeaderboardFormat::Type DisplayFormat;` — Display Type
- L677 _public member_ `int32 TotalLeaderboardRows;` — Number of entries on leaderboard
- L679 _public member_ `SteamLeaderboard_t LeaderboardHandle;` — Handle to leaderboard
- L681 _public member_ `EOnlineAsyncTaskState::Type AsyncState;` — State of the leaderboard handle download
- L683 _public function_ `FLeaderboardMetadataSteam(const FString& InLeaderboardName, ELeaderboardSort::Type InSortMethod, ELeaderboardFormat::Type InDisplayFormat) : LeaderboardName(InLeaderboardName), SortMethod(InSortMethod), DisplayFormat(InDisplayFormat), TotalLeaderboardRows(0), LeaderboardHandle(-1), AsyncState(EOnlineAsyncTaskState::NotStarted)`
- L693 _public function_ `FLeaderboardMetadataSteam(const FString& InLeaderboardName) : LeaderboardName(InLeaderboardName), SortMethod(ELeaderboardSort::None), DisplayFormat(ELeaderboardFormat::Number), TotalLeaderboardRows(0), LeaderboardHandle(-1), AsyncState(EOnlineAsyncTaskState::NotStarted)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESteamSession`
- L28 _function_ `inline const TCHAR* ToString(ESteamSession::Type SessionType)` (scope `ESteamSession`) — @return the stringified version of the enum passed in
- L57 _typedef_ `using FUniqueNetIdSteamRef = TSharedRef<const class FUniqueNetIdSteam>;`
- L58 _typedef_ `using FUniqueNetIdSteamPtr = TSharedPtr<const class FUniqueNetIdSteam>;`
- L273 _prototype_ `FString LexToString(const FSteamConnectionMethod Method);` — Functionality for converting a connection method type between formats
- L274 _prototype_ `FSteamConnectionMethod ToConnectionMethod(const FString& InString);`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/OnlineUserCloudInterfaceSteam.h` (Private)


#### class `FOnlineAsyncTaskSteamEnumerateUserFiles`  
`class FOnlineAsyncTaskSteamEnumerateUserFiles : public FOnlineAsyncTaskSteam`  
_L12-42_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task for enumerating all cloud files for a given user
- L15 _private member_ `FUniqueNetIdSteamRef UserId;` — UserId for file enumeration
- L18 _private prototype_ `FOnlineAsyncTaskSteamEnumerateUserFiles() = delete;` — Hidden on purpose
- L21 _public function_ `FOnlineAsyncTaskSteamEnumerateUserFiles(class FOnlineSubsystemSteam* InSubsystem, const FUniqueNetIdSteam& InUserId) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), UserId(InUserId.AsShared())`
- L30 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L36 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L41 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamReadUserFile`  
`class FOnlineAsyncTaskSteamReadUserFile : public FOnlineAsyncTaskSteam`  
_L47-83_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task for reading into memory a single cloud files for a given user
- L54 _private member_ `FString FileName;` — Filename shared
- L57 _private prototype_ `FOnlineAsyncTaskSteamReadUserFile() = delete;` — Hidden on purpose
- L61 _public function_ `FOnlineAsyncTaskSteamReadUserFile(class FOnlineSubsystemSteam* InSubsystem, const FUniqueNetIdSteam& InUserId, const FString& InFileName) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), UserId(InUserId.AsShared()), FileName(InFileName)`
- L71 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L77 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L82 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamWriteUserFile`  
`class FOnlineAsyncTaskSteamWriteUserFile : public FOnlineAsyncTaskSteam`  
_L88-138_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task for writing a single cloud file to disk for a given user
- L95 _private member_ `FUniqueNetIdSteamRef UserId;` — UserId making the request
- L97 _private member_ `FString FileName;` — File being written
- L100 _private prototype_ `FOnlineAsyncTaskSteamWriteUserFile() = delete;` — Hidden on purpose
- L111 _private prototype_ `bool WriteUserFile(const FUniqueNetId& UserId, const FString& FileToWrite, const TArray<uint8>& Contents);` — Write the specified user file to the network platform's file store @param UserId User owning the storage @param FileToWrite the name of the file to write @param FileContents the out buffer to copy the data into @return true if the calls starts successfully, false otherwise
- L115 _public function_ `FOnlineAsyncTaskSteamWriteUserFile(class FOnlineSubsystemSteam* InSubsystem, const FUniqueNetIdSteam& InUserId, const FString& InFileName, const TArray<uint8>& InContents) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), Contents(InContents), UserId(InUserId.AsShared()), FileName(InFileName)`
- L126 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L132 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L137 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineAsyncTaskSteamDeleteUserFile`  
`class FOnlineAsyncTaskSteamDeleteUserFile : public FOnlineAsyncTaskSteam`  
_L143-182_
- inherits: `FOnlineAsyncTaskSteam`
- desc: Async task for deleting a single cloud file for a given user
- L146 _private member_ `bool bShouldCloudDelete;` — Should the file be deleted from the cloud record
- L148 _private member_ `bool bShouldLocallyDelete;` — Should the local copy of the file be deleted
- L150 _private member_ `FUniqueNetIdSteamRef UserId;` — UserId making the request
- L152 _private member_ `FString FileName;` — File being deleted
- L155 _private prototype_ `FOnlineAsyncTaskSteamDeleteUserFile() = delete;` — Hidden on purpose
- L158 _public function_ `FOnlineAsyncTaskSteamDeleteUserFile(class FOnlineSubsystemSteam* InSubsystem, const FUniqueNetIdSteam& InUserId, const FString& InFileName, bool bInShouldCloudDelete, bool bInShouldLocallyDelete) : FOnlineAsyncTaskSteam(InSubsystem, k_uAPICallInvalid), bShouldCloudDelete(bInShouldCloudDelete), bShouldLocallyDelete(bInShouldLocallyDelete), UserId(InUserId.AsShared()), FileName(InFileName)`
- L170 _public prototype_ `virtual FString ToString() const override;` — Get a human readable description of task
- L176 _public prototype_ `virtual void Tick() override;` — Give the async task time to do its work Can only be called on the async task manager thread
- L181 _public prototype_ `virtual void TriggerDelegates() override;` — Async task is given a chance to trigger it's delegates

#### class `FOnlineUserCloudSteam`  
`class FOnlineUserCloudSteam : public IOnlineUserCloud`  
_L187-223_
- inherits: `IOnlineUserCloud`
- desc: Provides access to per user cloud file storage
- L191 _private member_ `class FOnlineSubsystemSteam* SteamSubsystem;` — Reference to the main Steam subsystem
- L193 _private function_ `FOnlineUserCloudSteam() : SteamSubsystem(NULL)`
- L207 _public prototype_ `virtual ~FOnlineUserCloudSteam();`
- L210 _public prototype_ `virtual bool GetFileContents(const FUniqueNetId& UserId, const FString& FileName, TArray<uint8>& FileContents) override;` — IOnlineUserCloud
- L211 _public prototype_ `virtual bool ClearFiles(const FUniqueNetId& UserId) override;`
- L212 _public prototype_ `virtual bool ClearFile(const FUniqueNetId& UserId, const FString& FileName) override;`
- L213 _public prototype_ `virtual void EnumerateUserFiles(const FUniqueNetId& UserId) override;`
- L214 _public prototype_ `virtual void GetUserFileList(const FUniqueNetId& UserId, TArray<FCloudFileHeader>& UserFiles) override;`
- L215 _public prototype_ `virtual bool ReadUserFile(const FUniqueNetId& UserId, const FString& FileName) override;`
- L216 _public prototype_ `virtual bool WriteUserFile(const FUniqueNetId& UserId, const FString& FileName, TArray<uint8>& FileContents, bool bCompressBeforeUpload = false) override;`
- L217 _public prototype_ `virtual void CancelWriteUserFile(const FUniqueNetId& UserId, const FString& FileName) override;`
- L218 _public prototype_ `virtual bool DeleteUserFile(const FUniqueNetId& UserId, const FString& FileName, bool bShouldCloudDelete, bool bShouldLocallyDelete) override;`
- L219 _public prototype_ `virtual bool RequestUsageInfo(const FUniqueNetId& UserId) override;`
- L220 _public prototype_ `virtual void DumpCloudState(const FUniqueNetId& UserId) override;`
- L221 _public prototype_ `virtual void DumpCloudFileState(const FUniqueNetId& UserId, const FString& FileName) override;`

#### Free symbols / members of external scopes

- L225 _typedef_ `typedef TSharedPtr<FOnlineUserCloudSteam, ESPMode::ThreadSafe> FOnlineUserCloudSteamPtr;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/SteamSessionKeys.h` (Private)


#### Free symbols / members of external scopes

- L12 _macro_ `#define STEAMKEY_NUMPUBLICCONNECTIONS "NUMPUBCONN"` — Well defined lobby/server keys for use with Steam lobby/server data (NOTE: Steam expects UTF8)
- L13 _macro_ `#define STEAMKEY_NUMPRIVATECONNECTIONS "NUMPRIVCONN"`
- L14 _macro_ `#define STEAMKEY_SESSIONFLAGS "SESSIONFLAGS"`
- L15 _macro_ `#define STEAMKEY_OWNINGUSERID "OWNINGID"`
- L16 _macro_ `#define STEAMKEY_OWNINGUSERNAME "OWNINGNAME"`
- L17 _macro_ `#define STEAMKEY_NUMOPENPRIVATECONNECTIONS "NUMOPENPRIVCONN"`
- L18 _macro_ `#define STEAMKEY_NUMOPENPUBLICCONNECTIONS "NUMOPENPUBCONN"`
- L19 _macro_ `#define STEAMKEY_BUILDUNIQUEID "BUILDID"`
- L22 _macro_ `#define STEAMKEY_NUMREQUIREDLOBBYKEYS 9` — Number of keys above required for valid lobby session
- L23 _macro_ `#define STEAMKEY_NUMREQUIREDSERVERKEYS 4`
- L26 _macro_ `#define STEAMKEY_HOSTIP "HOSTIP"` — Optional keys (depends on lobby/advertised server session)
- L27 _macro_ `#define STEAMKEY_HOSTPORT "HOSTPORT"`
- L28 _macro_ `#define STEAMKEY_P2PADDR "P2PADDR"`
- L29 _macro_ `#define STEAMKEY_P2PPORT "P2PPORT"`
- L30 _macro_ `#define STEAMKEY_P2PPING "P2PPING"`
- L31 _macro_ `#define STEAMKEY_CONNECTIONMETHOD "CONMETHOD"`
- L43 _function_ `inline bool SessionKeyToSteamKey(const FName Key, const FVariantData& Data, FString& KeyStr)` — Converts an engine key and its data type to an appropriate Steam key for use with lobbies/gameservers Encoded as key in the form <keyname>_<datatype> so that it is known client side @param Key online key @param Data data associated with the key @param KeyStr output Steam key for use with Steam lobbies @return true if successful, false if data type unknown/unsupported
- L85 _function_ `inline bool SteamKeyToSessionSetting(const TCHAR* SteamKey, const ANSICHAR* SteamValue, FName& Key, FOnlineSessionSetting& Setting)` — Converts Steam key/value data back to its appropriate online key and its associated data see SessionKeyToSteamKey() above @param SteamKey key in Steam string format @param SteamValue data associated with the SteamKey @param Key output key for use with online subsystem @param Setting output data associated with Key @return true if successful, false if data type unknown/unsupported

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/SteamUtilities.h` (Private)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace EOnlineServerConnectionStatus`
- L26 _prototype_ `FString SteamResultString(EResult Result);` — Takes a Steam EResult value, and converts it into a string (with extra debug info) @param Result	The EResult value to convert to a string @return the converted string for the given result
- L34 _prototype_ `FString SteamChatMemberStateChangeString(EChatMemberStateChange StateChange);` — Takes a Steam EChatMemberStateChange value, and converts it into a string (with extra debug info) @param StateChange	The EChatMemberStateChange value to convert to a string @return the converted string for the given state change
- L42 _prototype_ `FString SteamChatRoomEnterResponseString(EChatRoomEnterResponse Response);` — Takes a Steam EChatRoomEnterResponse value, and converts it into a string (with extra debug info) @param Response	The EChatRoomEnterResponse value to convert to a string @return the converted string for the given response
- L50 _prototype_ `FString SteamMatchMakingServerResponseString(EMatchMakingServerResponse Response);` — Takes a Steam EMatchMakingServerResponse value, and converts it into a string (with extra debug info) @param Response	The EMatchMakingServerResponse value to convert to a string @return the converted string for the given response
- L57 _prototype_ `FString SteamP2PConnectError(EP2PSessionError InError);` — Converts a Steam EP2PSessionError value to a readable/descriptive string @param InError	The EP2PSessionError value to convert to a string @return the converted string for the given error
- L64 _prototype_ `FString SteamVoiceResult(EVoiceResult Result);` — Converts a Steam EVoiceResult value to a readable/descriptive string @param Result	The EVoiceResult value to convert to a string @return the converted string for the given error
- L71 _prototype_ `EOnlineServerConnectionStatus::Type SteamConnectionResult(const EResult Result);` — Takes a Steam EResult value, and converts it to an online connection state @param Result	The EResult value to convert to a connection state @return the connection state for the given result

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/VoiceEngineSteam.h` (Private)


#### class `FVoiceEngineSteam`  
`class FVoiceEngineSteam : public FVoiceEngineImpl`  
_L15-41_
- inherits: `FVoiceEngineImpl`
- desc: Generic implementation of voice engine, using Voice module for capture/codec
- L18 _private member_ `class ISteamUser* SteamUserPtr;` — Steam User interface
- L20 _private member_ `class ISteamFriends* SteamFriendsPtr;` — Steam Friends interface
- L23 _private prototype_ `virtual void StartRecording() const override;` — Start capturing voice data
- L26 _private prototype_ `virtual void StoppedRecording() const override;` — Called when "last half second" is over
- L39 _public prototype_ `FVoiceEngineSteam(IOnlineSubsystem* InSubsystem);`
- L40 _public prototype_ `virtual ~FVoiceEngineSteam();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define INVALID_INDEX -1`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/VoiceInterfaceSteam.h` (Private)


#### class `FOnlineVoiceSteam`  
`class FOnlineVoiceSteam : public FOnlineVoiceImpl`  
_L12-34_
- inherits: `FOnlineVoiceImpl`
- L21 _public function_ `FOnlineVoiceSteam(class IOnlineSubsystem* InOnlineSubsystem) : FOnlineVoiceImpl(InOnlineSubsystem)` — Constructor
- L27 _public function_ `virtual IVoiceEnginePtr CreateVoiceEngine() override`
- L33 _public function_ `virtual ~FOnlineVoiceSteam() override` — Virtual destructor to force proper child cleanup

#### Free symbols / members of external scopes

- L36 _typedef_ `typedef TSharedPtr<FOnlineVoiceSteam, ESPMode::ThreadSafe> FOnlineVoiceSteamPtr;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Private/VoicePacketSteam.h` (Private)


#### class `FVoicePacketSteam`  
`class UE_DEPRECATED(4.25, "Steam Voice is now handled by the default voice implementation, FOnlineVoiceImpl. This code is no longer used.") FVoicePacketSteam : public FVoicePacket`  
_L9-49_
- inherits: `FVoicePacket`
- desc: Defines the data involved in a Steam voice packet
- L17 _private member_ `TArray<uint8> Buffer;` — The data that is to be sent/processed
- L19 _private member_ `uint16 Length;` — The current amount of space used in the buffer for this packet
- L23 _public function_ `FVoicePacketSteam() : Sender(NULL), Length(0)` — Zeros members and validates the assumptions
- L31 _public function_ `virtual ~FVoicePacketSteam()` — Should only be used by TSharedPtr and FVoiceData
- L40 _public prototype_ `FVoicePacketSteam(const FVoicePacketSteam& Other);` — Copies another packet @param Other packet to copy
- L43 _public prototype_ `virtual uint16 GetTotalPacketSize() override;`
- L44 _public prototype_ `virtual uint16 GetBufferSize() override;`
- L45 _public prototype_ `virtual FUniqueNetIdPtr GetSender() override;`
- L46 _public function_ `virtual bool IsReliable() override`
- L47 _public prototype_ `virtual void Serialize(class FArchive& Ar) override;`

#### struct `FVoiceDataSteam_DEPRECATED`  
`struct FVoiceDataSteam_DEPRECATED`  
_L52-56_
- L55 _public member_ `FVoicePacketSteam LocalPackets[MAX_SPLITSCREEN_TALKERS];` — Data used by the local talkers before sent

#### struct `FVoiceDataSteam`  
`struct UE_DEPRECATED(4.25, "Voice functionality on Steam no longer requires platform specific code.") FVoiceDataSteam : public FVoiceDataSteam_DEPRECATED`  
_L61-68_
- inherits: `FVoiceDataSteam_DEPRECATED`
- desc: Holds the current voice packet data state
- L64 _public member_ `FVoicePacketList RemotePackets;` — Holds the set of received packets that need to be processed
- L66 _public function_ `FVoiceDataSteam()`
- L67 _public function_ `~FVoiceDataSteam()`

### `Plugins/Online/OnlineSubsystemSteam/Source/Public/OnlineAuthInterfaceUtilsSteam.h` (Public)


#### enum `ESteamAuthResponseCode`  
`enum class ESteamAuthResponseCode : uint8`  
_L8-23_
- desc: Status flags of SteamAuth response codes, mapped 1:1 with SteamAPI
- L10 _public enumerator_ `OK = 0`
- L11 _public enumerator_ `NotConnectedToSteam = 1`
- L12 _public enumerator_ `NoOwnership = 2`
- L13 _public enumerator_ `VACBanned = 3`
- L14 _public enumerator_ `LoggedInElsewhere = 4`
- L15 _public enumerator_ `VACCheckTimeout = 5`
- L16 _public enumerator_ `TicketCancelled = 6`
- L17 _public enumerator_ `TicketAlreadyUsed = 7`
- L18 _public enumerator_ `TicketInvalid = 8`
- L19 _public enumerator_ `PublisherBanned = 9`
- L21 _public enumerator_ `FailedToCreateUser = 20` — ... space given for future steam codes ...
- L22 _public enumerator_ `Count`

#### class `FOnlineAuthUtilsSteam`  
`class FOnlineAuthUtilsSteam`  
_L49-75_
- desc: A class for interfacing with SteamAuth outside of the SteamOSS.
- L53 _public function_ `~FOnlineAuthUtilsSteam()`
- L67 _public prototype_ `bool IsSteamAuthEnabled() const;` — Checks to see if Steam Authentication is enabled due to being defined in any PacketHandlerComponent list. @return the true if SteamAuth is enabled.
- L72 _public member_ `FOnSteamAuthFailureDelegate OverrideFailureDelegate;` — Attach to this delegate to control the behavior of the Steam authentication failure. This overrides the default behavior (kick).
- L73 _public member_ `FOnSteamAuthResultDelegate OnAuthenticationResultDelegate;`
- L74 _public member_ `FOnSteamAuthResultWithCodeDelegate OnAuthenticationResultWithCodeDelegate;`

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSteamAuthFailure, const class FUniqueNetId& );` — When authentication has failed and we are about to take action on the user, this delegate is fired. For the auth interface, overriding the delegate exposed in the class allows a game to override the default behavior, which is to kick anyone who fails authentication. If you would like to receive analytics as to the success/failure for users we can identify (have their unique net id), use the result delegate instead.
- L32 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSteamAuthFailure, const class FUniqueNetId& );` — When authentication has failed and we are about to take action on the user, this delegate is fired. For the auth interface, overriding the delegate exposed in the class allows a game to override the default behavior, which is to kick anyone who fails authentication. If you would like to receive analytics as to the success/failure for users we can identify (have their unique net id), use the result delegate instead.
- L33 _typedef_ `typedef FOnSteamAuthFailure::FDelegate FOnSteamAuthFailureDelegate;`
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSteamAuthResult, const class FUniqueNetId& , bool );` — This delegate dictates the success or failure of an authentication result. This means we got a result, but we won't be taking action yet.
- L38 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSteamAuthResult, const class FUniqueNetId& , bool );` — This delegate dictates the success or failure of an authentication result. This means we got a result, but we won't be taking action yet.
- L39 _typedef_ `typedef FOnSteamAuthResult::FDelegate FOnSteamAuthResultDelegate;`
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSteamAuthResultWithCode, const class FUniqueNetId& , bool , ESteamAuthResponseCode );` — This delegate dictates the success or failure of an authentication result with an additional flag that explains the result. This is fired at the same time as the above delegate but includes additional data. Should a project be listening to result delegate calls, it is recommended to listen to one of these two (but not both).
- L45 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSteamAuthResultWithCode, const class FUniqueNetId& , bool , ESteamAuthResponseCode );` — This delegate dictates the success or failure of an authentication result with an additional flag that explains the result. This is fired at the same time as the above delegate but includes additional data. Should a project be listening to result delegate calls, it is recommended to listen to one of these two (but not both).
- L46 _typedef_ `typedef FOnSteamAuthResultWithCode::FDelegate FOnSteamAuthResultWithCodeDelegate;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Public/OnlineEncryptedAppTicketInterfaceSteam.h` (Public)


#### class `FOnlineEncryptedAppTicketSteam`  
`class FOnlineEncryptedAppTicketSteam : public FSelfRegisteringExec`  
_L34-85_
- inherits: `FSelfRegisteringExec`
- L39 _private prototype_ `virtual ~FOnlineEncryptedAppTicketSteam();`
- L47 _private prototype_ `void OnAPICallComplete(bool bEncryptedDataAvailable, int32 ResultCode);` — Callback function informed of a result of the latest successful call to RequestEncryptedAppTicket. @param bEncryptedDataAvailable - True if function call was a success and the data is available, else false. @param ResultCode - Steam API EResult code describing the result of the API call.
- L60 _public prototype_ `bool RequestEncryptedAppTicket(void* DataToEncrypt, int SizeOfDataToEncrypt);` — Requests data encrypting with Steam Encrypted Application ticket API. The encryption key used is the one configured on the App Admin page for your app on Steam portal. There can only be one data encrypting request pending, and this call is subject to a 60 second rate limit. @param DataToEncrypt - Data to encrypt. @param SizeOfDataToEncrypt - Length of data to encrypt. @return True on success, false on failure.
- L69 _public prototype_ `bool GetEncryptedAppTicket(TArray<uint8>& OutEncryptedData);` — Retrieve encrypted data once it's available. @param OutEncryptedData - Upon successful call, contains the encrypted application ticket data. @return True if the function call was successful, otherwise false. @warning Only call this after OnDataEncryptResultDelegate has reported the data to be available.
- L72 _public member_ `FOnEncryptedAppTicketResponse OnEncryptedAppTicketResultDelegate;` — Attach to this delegate to get notified about the encrypted application ticket results.
- L76 _protected prototype_ `virtual bool Exec_Dev(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FSelfRegisteringExec
- L81 _private member_ `FOnlineSubsystemSteam* SteamSubsystem;` — Reference to the main Steam subsystem
- L84 _private member_ `ESteamEncryptedAppTicketState TicketState;` — Describes the state of the object.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ONLINESUBSYSTEMSTEAM_API`
- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEncryptedAppTicketResponse, bool , int32 );` — This delegate dictates the success or failure of data encrypting result. On success, this means that the encrypted data is now available and can be retrieved via call to GetEncryptedAppTicket. @param bEncryptedDataAvailable - True if function call was a success and the data is available, else false. @param ResultCode - Steam API EResult code describing the result of the API call.
- L32 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEncryptedAppTicketResponse, bool , int32 );` — This delegate dictates the success or failure of data encrypting result. On success, this means that the encrypted data is now available and can be retrieved via call to GetEncryptedAppTicket. @param bEncryptedDataAvailable - True if function call was a success and the data is available, else false. @param ResultCode - Steam API EResult code describing the result of the API call.

### `Plugins/Online/OnlineSubsystemSteam/Source/Public/OnlinePingInterfaceSteam.h` (Public)


#### class `FOnlinePingInterfaceSteam`  
`class FOnlinePingInterfaceSteam`  
_L11-64_
- desc: An abstract ping interface for Steam ideally usable with the new SteamSocket internet protocol
- L14 _public function_ `FOnlinePingInterfaceSteam(class FOnlineSubsystemSteam* InSubsystem) : Subsystem(InSubsystem)`
- L19 _public function_ `virtual ~FOnlinePingInterfaceSteam()`
- L31 _public prototype_ `virtual bool IsUsingP2PRelays() const = 0;` — Returns if this application is set up to use the Steam P2P Relay Network for communication. Uses OnlineSubsystemSteam.bAllowP2PPacketRelay @return true if relays are enabled for P2P connections.
- L40 _public prototype_ `virtual FString GetHostPingData() const = 0;` — Returns the P2P relay ping information for the current machine. This information can be serialized over the network and used to calculate the ping data between a client and a host. @return relay information blob stored as a string for relaying over the network. If an error occurred, the return is an empty string.
- L50 _public prototype_ `virtual int32 GetPingFromHostData(const FString& HostPingStr) const = 0;` — Calculates the ping of this client using the given host's ping data obtained from GetHostPingData. @param HostPingStr The relay information blob we got from the host. This information should be directly serialized over the network and not tampered with. @return The ping value to the given host if it can be calculated, otherwise -1 on error.
- L60 _public prototype_ `virtual bool IsRecalculatingPing() const = 0;` — An informative member that allows us to check if we are recalculating our ping information over the Valve network. Data is additively modified during recalculation such that we do not need to block on this function returning false before using ping data. @return true if we're recalculating our ping within the Valve relay network.
- L63 _protected member_ `FOnlineSubsystemSteam* Subsystem;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Public/OnlinePurchaseInterfaceSteam.h` (Public)


#### struct `FSteamPurchaseDef`  
`struct FSteamPurchaseDef`  
_L32-38_
- L36 _public member_ `FOnlineStoreOfferRef Mtxn;`
- L37 _public member_ `int32_t Quantity;`

#### class `ISteamPurchasingServerLink`  
`class ISteamPurchasingServerLink`  
_L48-83_
- L52 _public prototype_ `virtual ~ISteamPurchasingServerLink() = default;`
- L59 _public prototype_ `virtual void InitiateTransaction(const FUniqueNetId& UserId, TArray<FSteamPurchaseDef> Mtxns, const FOnPurchaseCheckoutComplete& Delegate) = 0;` — Required virtual function, and the main use case of the server link. Use this to call into your server to use the Steam Web API and complete the microtransaction purchase request. Your backend server should be using the InitTxn API
- L64 _public member_ `FOnOffersUpdatedDelegate OffersUpdatedDelegate;` — To use offer enumeration in the purchase interface, you must call these delegates after connecting the server link to refresh the purchase and store interface's offers.
- L72 _public function_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId)` — Overrride this function if your game uses the FinalizePurchase functionality to consume a microtransaction and mark it as properly used. Your backend server should be calling the FinalizeTxn API, if it did not do so as part of the InitiateTransaction flow
- L80 _public function_ `virtual void FinalizeReceiptValidationInfo(const FUniqueNetId& UserId, FString& InReceiptValidationInfo, const FOnFinalizeReceiptValidationInfoComplete& Delegate)` — Overrride this function if your game uses the FinalizeReceiptValidationInfo. The Steam API does not directly provide anything useful for this call (other platforms would provide something like a JWT token). It is generally recommended to simply make that connection on the backend using the web API

#### class `FOnlinePurchaseSteam`  
`class FOnlinePurchaseSteam : public IOnlinePurchase , public TSharedFromThis<FOnlinePurchaseSteam, ESPMode::ThreadSafe>`  
_L100-137_
- inherits: `IOnlinePurchase,TSharedFromThis<FOnlinePurchaseSteam,ESPMode::ThreadSafe>`
- L105 _public prototype_ `FOnlinePurchaseSteam(FOnlineSubsystemSteam* InSteamSubsystem);`
- L106 _public prototype_ `virtual ~FOnlinePurchaseSteam();`
- L110 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId) override;`
- L111 _public prototype_ `virtual bool IsAllowedToPurchase(const FUniqueNetId& UserId, FOnlineError& Error) override;`
- L112 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseCheckoutComplete& Delegate) override;`
- L113 _public prototype_ `virtual void Checkout(const FUniqueNetId& UserId, const FPurchaseCheckoutRequest& CheckoutRequest, const FOnPurchaseReceiptlessCheckoutComplete& Delegate) override;`
- L114 _public prototype_ `virtual void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId) override;`
- L115 _public prototype_ `virtual void RedeemCode(const FUniqueNetId& UserId, const FRedeemCodeRequest& RedeemCodeRequest, const FOnPurchaseRedeemCodeComplete& Delegate) override;`
- L116 _public prototype_ `virtual void QueryReceipts(const FUniqueNetId& UserId, bool bRestoreReceipts, const FOnQueryReceiptsComplete& Delegate) override;`
- L117 _public prototype_ `virtual void GetReceipts(const FUniqueNetId& UserId, TArray<FPurchaseReceipt>& OutReceipts) const override;`
- L118 _public prototype_ `virtual void FinalizeReceiptValidationInfo(const FUniqueNetId& UserId, FString& InReceiptValidationInfo, const FOnFinalizeReceiptValidationInfoComplete& Delegate) override;`
- L121 _public prototype_ `void RegisterServerLink(TSharedRef<ISteamPurchasingServerLink> InServerLink);`
- L123 _public prototype_ `void GetStoreCategories(TArray<FOnlineStoreCategory>& OutCategories) const;`
- L124 _public prototype_ `void GetStoreOffers(TArray<FOnlineStoreOfferRef>& OutOffers) const;`
- L125 _public prototype_ `TSharedPtr<FOnlineStoreOffer> GetStoreOffer(const FUniqueOfferId& OfferId) const;`
- L128 _private member_ `FOnlineSubsystemSteam* SteamSubsystem;`
- L129 _private member_ `TSharedPtr<ISteamPurchasingServerLink> ServerLink;`
- L131 _private member_ `TArray<FOnlineStoreOfferRef> CachedMtxns;`
- L132 _private member_ `TArray<FString> CachedCategories;`
- L133 _private member_ `TArray<FPurchaseReceipt> CachedDLC;`
- L135 _private prototype_ `void OnServerLinkOffersUpdated(TArray<FString> Categories, TArray<FOnlineStoreOfferRef> Mtxns);`

#### class `FSteamPurchasingServerLinkDebug`  
`class FSteamPurchasingServerLinkDebug : public ISteamPurchasingServerLink`  
_L142-153_
- inherits: `ISteamPurchasingServerLink`
- L146 _public prototype_ `FSteamPurchasingServerLinkDebug();`
- L147 _public prototype_ `virtual ~FSteamPurchasingServerLinkDebug() = default;`
- L149 _public prototype_ `virtual void InitiateTransaction(const FUniqueNetId& UserId, TArray<FSteamPurchaseDef> Mtxns, const FOnPurchaseCheckoutComplete& Delegate) override;`
- L151 _public member_ `TArray<FOnlineStoreOfferRef> ConfigMtxns;`
- L152 _public member_ `TArray<FString> ConfigCategories;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define USE_STEAM_DEBUG_PURCHASING_LINK 1`
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOffersUpdated, TArray<FString> , TArray<FOnlineStoreOfferRef> );` — Delegate called when the server wants to update our list of offers. @param bWasSuccessful whether the async call completed properly or not
- L45 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOffersUpdated, TArray<FString> , TArray<FOnlineStoreOfferRef> );` — Delegate called when the server wants to update our list of offers. @param bWasSuccessful whether the async call completed properly or not
- L46 _typedef_ `typedef FOnOffersUpdated::FDelegate FOnOffersUpdatedDelegate;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Public/OnlineSubsystemSteam.h` (Public)


#### class `FOnlineSubsystemSteam`  
`class FOnlineSubsystemSteam : public FOnlineSubsystemImpl`  
_L59-367_
- inherits: `FOnlineSubsystemImpl`
- desc: OnlineSubsystemSteam - Implementation of the online subsystem for STEAM services
- L65 _protected member_ `bool bSteamworksClientInitialized;` — Has the STEAM client APIs been initialized
- L68 _protected member_ `bool bSteamworksGameServerInitialized;` — Whether or not the Steam game server API is initialized
- L71 _protected member_ `bool bUsingSteamNetworking;` — If we are using the SteamNetworking protocol or not.
- L74 _protected member_ `uint32 SteamAppID;` — Steam App ID for the running game
- L77 _protected member_ `int32 GameServerGamePort;` — Game port - the port that clients will connect to for gameplay
- L80 _protected member_ `int32 GameServerQueryPort;` — Query port - the port that will manage server browser related duties and info
- L83 _protected member_ `TArray<struct FSteamUserCloudData*> UserCloudData;` — Array of the files in the cloud for a given user
- L86 _protected member_ `FOnlineSessionSteamPtr SessionInterface;` — Interface to the session services
- L89 _protected member_ `FOnlineIdentitySteamPtr IdentityInterface;` — Interface to the profile services
- L92 _protected member_ `FOnlineFriendsSteamPtr FriendInterface;` — Interface to the friend services
- L95 _protected member_ `FOnlineSharedCloudSteamPtr SharedCloudInterface;` — Interface to the shared cloud services
- L98 _protected member_ `FOnlineUserCloudSteamPtr UserCloudInterface;` — Interface to the user cloud services
- L101 _protected member_ `FOnlineLeaderboardsSteamPtr LeaderboardsInterface;` — Interface to the leaderboard services
- L104 _protected member_ `mutable IOnlineVoicePtr VoiceInterface;` — Interface to the voice engine
- L107 _protected member_ `mutable bool bVoiceInterfaceInitialized;` — Interface for voice communication
- L110 _protected member_ `FOnlineExternalUISteamPtr ExternalUIInterface;` — Interface to the external UI services
- L113 _protected member_ `FOnlineAchievementsSteamPtr AchievementsInterface;` — Interface for achievements
- L116 _protected member_ `FOnlinePresenceSteamPtr PresenceInterface;` — Interface for presence
- L119 _protected member_ `FOnlineAuthSteamPtr AuthInterface;` — Interface for Steam Session Auth
- L120 _protected member_ `FOnlineAuthSteamUtilsPtr AuthInterfaceUtils;`
- L123 _protected member_ `FOnlinePingSteamPtr PingInterface;` — Interface for dynamically calculating SteamNetworking ping based off protocol
- L126 _protected member_ `FOnlineEncryptedAppTicketSteamPtr EncryptedAppTicketInterface;` — Interface for Steam encrypted application tickets.
- L129 _protected member_ `FOnlinePurchaseSteamPtr PurchaseInterface;` — Interface for the Purchase interface
- L132 _protected member_ `FOnlineStoreSteamPtr StoreInterface;` — Interface for the Store interface
- L135 _protected member_ `class FOnlineAsyncTaskManagerSteam* OnlineAsyncTaskThreadRunnable;` — Online async task runnable
- L138 _protected member_ `class FRunnableThread* OnlineAsyncTaskThread;` — Online async task thread
- L141 _protected member_ `TSharedPtr<class FSteamClientInstanceHandler> SteamAPIClientHandle;` — Steam Client API Handle
- L144 _protected member_ `TSharedPtr<class FSteamServerInstanceHandler> SteamAPIServerHandle;` — Steam Server API Handle
- L150 _protected function_ `FOnlineSubsystemSteam(FName InInstanceName) : FOnlineSubsystemImpl(STEAM_SUBSYSTEM, InInstanceName), bSteamworksClientInitialized(false), bSteamworksGameServerInitialized(false), bUsingSteamNetworking(false), SteamAppID(0), GameServerGamePort(0), GameServerQueryPort(0), SessionInterface(nullptr), IdentityInterface(nullptr), FriendInterface(nullptr), SharedCloudInterface(nullptr), UserCloudInterface(nullptr), LeaderboardsInterface(nullptr), VoiceInterface(nullptr), bVoiceInterfaceInitialized(false), ExternalUIInterface(nullptr), PresenceInterface(nullptr), AuthInterface(nullptr), AuthInterfaceUtils(nullptr), PingInterface(nullptr), EncryptedAppTicketInterface(nullptr), PurchaseInterface(nullptr), StoreInterface(nullptr), OnlineAsyncTaskThreadRunnable(nullptr), OnlineAsyncTaskThread(nullptr), SteamAPIClientHandle(nullptr), SteamAPIServerHandle(nullptr)`
- L181 _protected member_ `FCriticalSection UserCloudDataLock;` — Critical sections for thread safe operation of the cloud files
- L187 _protected prototype_ `bool InitSteamworksClient(bool bRelaunchInSteam, int32 SteamAppId);` — Initialize the client side APIs for Steam @return true if the API was initialized successfully, false otherwise
- L193 _protected prototype_ `bool InitSteamworksServer();` — Initialize the server side APIs for Steam @return true if the API was initialized successfully, false otherwise
- L198 _protected prototype_ `void ShutdownSteamworks();` — Shutdown the Steam APIs
- L204 _protected prototype_ `void QueueAsyncTask(class FOnlineAsyncTask* AsyncTask);` — Add an async task onto the task queue for processing @param AsyncTask - new heap allocated task to process on the async task thread
- L210 _protected prototype_ `void QueueAsyncOutgoingItem(class FOnlineAsyncItem* AsyncItem);` — Add an async task onto the outgoing task queue for processing @param AsyncItem - new heap allocated task to process on the async task thread
- L221 _protected prototype_ `struct FSteamUserCloudData* GetUserCloudEntry(const FUniqueNetId& UserId);` — **INTERNAL** Get the metadata related to a given user This information is only available after calling EnumerateUserFiles @param UserId the UserId to search for @return the struct with the metadata about the requested user, will always return a valid struct, creating one if necessary
- L234 _protected prototype_ `bool ClearUserCloudMetadata(const FUniqueNetId& UserId, const FString& Filename);` — **INTERNAL** Clear the metadata related to a given user's file on Steam This information is only available after calling EnumerateUserFiles It doesn't actually delete any of the actual data on disk @param UserId the UserId for the file to search for @param Filename the file to get metadata about @return the true if the delete was successful, false otherwise
- L239 _protected prototype_ `void ClearUserCloudFiles();` — Clear out all the data related to user cloud storage
- L247 _protected prototype_ `FOnlineLeaderboardsSteam * GetInternalLeaderboardsInterface();` — **INTERNAL** Get the interface for accessing leaderboards/stats @return pointer for the appropriate class
- L251 _public function_ `virtual ~FOnlineSubsystemSteam()`
- L255 _public prototype_ `virtual FOnlineEncryptedAppTicketSteamPtr GetEncryptedAppTicketInterface() const;`
- L257 _public prototype_ `virtual FOnlineAuthSteamPtr GetAuthInterface() const;`
- L258 _public prototype_ `virtual FOnlineAuthSteamUtilsPtr GetAuthInterfaceUtils() const;`
- L260 _public prototype_ `virtual FOnlinePingSteamPtr GetPingInterface() const;`
- L261 _public prototype_ `virtual void SetPingInterface(FOnlinePingSteamPtr InPingInterface);`
- L265 _public prototype_ `virtual IOnlineSessionPtr GetSessionInterface() const override;`
- L266 _public prototype_ `virtual IOnlineFriendsPtr GetFriendsInterface() const override;`
- L267 _public prototype_ `virtual IOnlinePartyPtr GetPartyInterface() const override;`
- L268 _public prototype_ `virtual IOnlineGroupsPtr GetGroupsInterface() const override;`
- L269 _public prototype_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;`
- L270 _public prototype_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;`
- L271 _public prototype_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;`
- L272 _public prototype_ `virtual IOnlineVoicePtr GetVoiceInterface() const override;`
- L273 _public prototype_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;`
- L274 _public prototype_ `virtual IOnlineTimePtr GetTimeInterface() const override;`
- L275 _public prototype_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override;`
- L276 _public prototype_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;`
- L277 _public prototype_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;`
- L278 _public prototype_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;`
- L279 _public prototype_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override;`
- L280 _public prototype_ `virtual IOnlineEventsPtr GetEventsInterface() const override;`
- L281 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;`
- L282 _public prototype_ `virtual IOnlineSharingPtr GetSharingInterface() const override;`
- L283 _public prototype_ `virtual IOnlineUserPtr GetUserInterface() const override;`
- L284 _public prototype_ `virtual IOnlineMessagePtr GetMessageInterface() const override;`
- L285 _public prototype_ `virtual IOnlinePresencePtr GetPresenceInterface() const override;`
- L286 _public prototype_ `virtual IOnlineChatPtr GetChatInterface() const override;`
- L287 _public prototype_ `virtual IOnlineStatsPtr GetStatsInterface() const override;`
- L288 _public prototype_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;`
- L289 _public prototype_ `virtual IOnlineTournamentPtr GetTournamentInterface() const override;`
- L290 _public prototype_ `virtual bool IsLocalPlayer(const FUniqueNetId& UniqueId) const override;`
- L291 _public prototype_ `virtual bool Init() override;`
- L292 _public prototype_ `virtual bool Shutdown() override;`
- L293 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L294 _public prototype_ `virtual bool IsEnabled() const override;`
- L295 _public prototype_ `virtual FString GetAppId() const override;`
- L296 _public prototype_ `virtual FText GetOnlineServiceName() const override;`
- L300 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L310 _public function_ `inline bool IsSteamClientAvailable()` — Whether or not the Steam Client interfaces are available; these interfaces are only available, if the Steam Client program is running NOTE: These interfaces are made unavailable, when running a dedicated server @return	Whether or not the Steam Client interfaces are available
- L322 _public function_ `inline bool IsSteamServerAvailable()` — Whether or not the Steam game server interfaces are available; these interfaces are always available, so long as they were initialized correctly NOTE: The Steam Client does not need to be running for the game server interfaces to initialize NOTE: These interfaces are made unavailable, when not running a server @return	Whether or not the Steam game server interfaces are available
- L332 _public function_ `inline uint32 GetSteamAppId() const` — @return the steam app id for this app
- L340 _public function_ `inline int32 GetGameServerGamePort() const` — @return the port the game has registered for play
- L348 _public function_ `inline int32 GetGameServerQueryPort() const` — @return the port the game has registered for incoming server queries
- L357 _public function_ `inline bool IsUsingSteamNetworking() const` — @return if this subsystem is using SteamNetworking functionality or another network layer like SteamSockets
- L366 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnSteamServerLoginCompleted, bool);` — This delegate fires whenever a steam login has succeeded or failed its async task. Useful for modules that need to check to see if a user is logged in before running other behavior

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ONLINESUBSYSTEMSTEAM_API`
- L30 _typedef_ `typedef TSharedPtr<class FOnlineSessionSteam, ESPMode::ThreadSafe> FOnlineSessionSteamPtr;` — Forward declarations of all interface classes
- L31 _typedef_ `typedef TSharedPtr<class FOnlineIdentitySteam, ESPMode::ThreadSafe> FOnlineIdentitySteamPtr;`
- L32 _typedef_ `typedef TSharedPtr<class FOnlineFriendsSteam, ESPMode::ThreadSafe> FOnlineFriendsSteamPtr;`
- L33 _typedef_ `typedef TSharedPtr<class FOnlineSharedCloudSteam, ESPMode::ThreadSafe> FOnlineSharedCloudSteamPtr;`
- L34 _typedef_ `typedef TSharedPtr<class FOnlineUserCloudSteam, ESPMode::ThreadSafe> FOnlineUserCloudSteamPtr;`
- L35 _typedef_ `typedef TSharedPtr<class FOnlineLeaderboardsSteam, ESPMode::ThreadSafe> FOnlineLeaderboardsSteamPtr;`
- L36 _typedef_ `typedef TSharedPtr<class FOnlineVoiceSteam, ESPMode::ThreadSafe> FOnlineVoiceSteamPtr;`
- L37 _typedef_ `typedef TSharedPtr<class FOnlineExternalUISteam, ESPMode::ThreadSafe> FOnlineExternalUISteamPtr;`
- L38 _typedef_ `typedef TSharedPtr<class FOnlineAchievementsSteam, ESPMode::ThreadSafe> FOnlineAchievementsSteamPtr;`
- L39 _typedef_ `typedef TSharedPtr<class FOnlinePresenceSteam, ESPMode::ThreadSafe> FOnlinePresenceSteamPtr;`
- L40 _typedef_ `typedef TSharedPtr<class FOnlineAuthSteam, ESPMode::ThreadSafe> FOnlineAuthSteamPtr;`
- L41 _typedef_ `typedef TSharedPtr<class FOnlineAuthUtilsSteam, ESPMode::ThreadSafe> FOnlineAuthSteamUtilsPtr;`
- L42 _typedef_ `typedef TSharedPtr<class FOnlinePingInterfaceSteam, ESPMode::ThreadSafe> FOnlinePingSteamPtr;`
- L43 _typedef_ `typedef TSharedPtr<class FOnlineEncryptedAppTicketSteam, ESPMode::ThreadSafe> FOnlineEncryptedAppTicketSteamPtr;`
- L44 _typedef_ `typedef TSharedPtr<class FOnlinePurchaseSteam, ESPMode::ThreadSafe> FOnlinePurchaseSteamPtr;`
- L45 _typedef_ `typedef TSharedPtr<class FOnlineStoreSteam, ESPMode::ThreadSafe> FOnlineStoreSteamPtr;`
- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSteamServerLoginCompleted, bool );` — Delegate fired when a Steam Game Server has completed its login tasks with the Steam backend. @param bWasSuccessful if the login completed successfully
- L52 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSteamServerLoginCompleted, bool );` — Delegate fired when a Steam Game Server has completed its login tasks with the Steam backend. @param bWasSuccessful if the login completed successfully
- L53 _typedef_ `typedef FOnSteamServerLoginCompleted::FDelegate FOnSteamServerLoginCompletedDelegate;`
- L369 _namespace_ `namespace FNetworkProtocolTypes`
- L371 _externvar_ `extern const FLazyName Steam;` (scope `FNetworkProtocolTypes`)
- L374 _typedef_ `typedef TSharedPtr<FOnlineSubsystemSteam, ESPMode::ThreadSafe> FOnlineSubsystemSteamPtr;`

### `Plugins/Online/OnlineSubsystemSteam/Source/Public/OnlineSubsystemSteamModule.h` (Public)


#### class `FOnlineSubsystemSteamModule`  
`class FOnlineSubsystemSteamModule : public IModuleInterface`  
_L12-41_
- inherits: `IModuleInterface`
- desc: Online subsystem module class  (STEAM Implementation) Code related to the loading of the STEAM module
- L17 _private member_ `class FOnlineFactorySteam* SteamFactory;` — Class responsible for creating instance(s) of the subsystem
- L21 _public function_ `FOnlineSubsystemSteamModule() : SteamFactory(NULL)`
- L25 _public function_ `virtual ~FOnlineSubsystemSteamModule()`
- L29 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L32 _public function_ `virtual bool SupportsDynamicReloading() override`
- L37 _public function_ `virtual bool SupportsAutomaticShutdown() override`

### `Plugins/Online/OnlineSubsystemSteam/Source/Public/OnlineSubsystemSteamPackage.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define PACKAGE_SCOPE public`
- L14 _macro_ `#define PACKAGE_SCOPE protected`
