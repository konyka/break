# Plugins / Lobby

- module root: `Plugins/Online/OnlineFramework/Source/Lobby`
- headers: 7; symbols: 175
- symbol kinds: class=5, delegate=10, enum=2, enumerator=4, function=25, macro=6, member=36, prototype=84, struct=3
- PrivateDependencyModuleNames: Core, CoreOnline, CoreUObject, Engine, NetCore, OnlineSubsystem, OnlineSubsystemUtils

### `Plugins/Online/OnlineFramework/Source/Lobby/Public/Lobby.h` (Public)
_(no declarations extracted)_

### `Plugins/Online/OnlineFramework/Source/Lobby/Public/LobbyBeaconClient.h` (Public)


#### enum `ELobbyBeaconJoinState`  
`enum class ELobbyBeaconJoinState : uint8`  
_L44-52_
- reflection: `UENUM()`
- L47 _public enumerator_ `None` — Unknown, beacon may be connected but no intent to actually join the server
- L49 _public enumerator_ `SentJoinRequest` — Join request has been sent, waiting for a response
- L51 _public enumerator_ `JoinRequestAcknowledged` — Join request has been acknowledged

#### class `ALobbyBeaconClient`  
`class ALobbyBeaconClient : public AOnlineBeaconClient`  
_L58-258_
- reflection: `UCLASS(MinimalAPI, transient, config=Engine, notplaceable)`
- inherits: `AOnlineBeaconClient`
- desc: A beacon client used for quality timings to a specified session
- L64 _private member_ `TObjectPtr<ALobbyBeaconState> LobbyState;` — `UPROPERTY(Replicated)` — Client view of the lobby state
- L67 _private member_ `TObjectPtr<ALobbyBeaconPlayerState> PlayerState;` — `UPROPERTY(Replicated)` — Player state associated with this beacon (@todo not splitscreen safe)
- L70 _private prototype_ `virtual void EndPlay(EEndPlayReason::Type Reason) override;` — Clear out any references to this in PlayerState
- L73 _private prototype_ `virtual void OnConnected() override;`
- L81 _private prototype_ `virtual void ConnectToLobby(const FOnlineSessionSearchResult& DesiredHost);` — Initiate a connection to the lobby host beacon @param DesiredHost desired host destination
- L87 _private prototype_ `virtual void ClientJoinGame();` — `UFUNCTION(client, reliable)` — Tell the client to join the game
- L92 _private prototype_ `virtual void DisconnectFromLobby();` — Graceful disconnect from server with no intent of joining further
- L97 _private prototype_ `virtual void JoiningServer();` — Graceful notification that this client is going to join the server
- L105 _private prototype_ `void KickPlayer(const FUniqueNetIdRepl& PlayerToKick, const FText& Reason);` — Ask the server to kick a given player (may not succeed) @param PlayerToKick player kick request @param Reason reason for the kick to tell client if this succeeds
- L113 _private prototype_ `virtual void SetPartyOwnerId(const FUniqueNetIdRepl& InUniqueId, const FUniqueNetIdRepl& InPartyOwnerId);` — Tell the server to set a party owner @param InUniqueId unique id of the player making the change @param InPartyOwnerId unique id of the party owner
- L117 _private prototype_ `void ClientSetInviteFlags(const FJoinabilitySettings& Settings);` — `UFUNCTION(reliable, client)` — Send updated session settings to client
- L120 _private function_ `FOnLobbyConnectionEstablished& OnLobbyConnectionEstablished()` — @return delegate fired when a connection with the lobby beacon is established
- L122 _private function_ `FOnLobbyLoginComplete& OnLoginComplete()` — @return delegate fired when login handshaking is complete
- L124 _private function_ `FOnLobbyPlayerJoined& OnPlayerJoined()` — @return delegate fired when a new player joins the lobby
- L126 _private function_ `FOnLobbyPlayerLeft& OnPlayerLeft()` — @return delegate fired when an existing player leaves the lobby
- L128 _private function_ `FOnJoiningGame& OnJoiningGame()` — @return delegate fired when this player is told to join the game by the server
- L130 _private function_ `FOnJoiningGame& OnJoiningGameAck()` — @return delegate fired when the server acknowledges the client request to join the server
- L134 _private function_ `bool IsLoggedIn() const` — @return true if this client is correctly logged in to the beacon, false otherwise
- L138 _private prototype_ `void ServerCheat(const FString& Msg);` — `UFUNCTION(Reliable, Server, WithValidation)` — Run a cheat command on the server
- L143 _protected member_ `bool bLoggedIn;` — Has this beacon been properly logged in
- L147 _protected member_ `ELobbyBeaconJoinState LobbyJoinServerState;` — `UPROPERTY()` — True once the server has acknowledged our join intent
- L150 _protected member_ `FString DestSessionId;` — Session Id of the destination host
- L153 _protected member_ `FOnLobbyConnectionEstablished LobbyConnectionEstablished;` — Delegate broadcast when first connected to the lobby beacon (clientside)
- L155 _protected member_ `FOnLobbyLoginComplete LoginCompleteDelegate;` — Delegate broadcast when login is complete (clientside)
- L157 _protected member_ `FOnLobbyPlayerJoined PlayerJoinedDelegate;` — Delegate broadcast when a new player joins (clientside)
- L159 _protected member_ `FOnLobbyPlayerLeft PlayerLeftDelegate;` — Delegate broadcast when an existing player leaves (clientside)
- L161 _protected member_ `FOnJoiningGame JoiningGame;` — Delegate broadcast when this player is told to join the game by the server (clientside)
- L163 _protected member_ `FOnJoiningGame JoiningGameAck;` — Delegate broadcast when the server acknowledges the client request to join the server (clientside)
- L169 _protected prototype_ `void SetLobbyState(ALobbyBeaconState* InLobbyState);` — Set the lobby state for this client beacon @param InLobbyState reference to the lobby state
- L174 _protected prototype_ `virtual void LoginLocalPlayers();` — Internal function to log in a local players when first connected to the beacon
- L184 _protected prototype_ `virtual void ServerLoginPlayer(const FString& InSessionId, const FUniqueNetIdRepl& InUniqueId, const FString& UrlString);` — `UFUNCTION(server, reliable, WithValidation)` — Attempt to login a single local player with the lobby beacon @param InSessionId session id that the client is expecting to connect with @param InUniqueId unique id of the new player @param UrlString URL containing player options (name, etc)
- L190 _protected prototype_ `virtual void ServerDisconnectFromLobby();` — `UFUNCTION(server, reliable, WithValidation)` — Make a graceful disconnect with the server
- L196 _protected prototype_ `virtual void ServerNotifyJoiningServer();` — `UFUNCTION(server, reliable, WithValidation)` — Make a graceful request to actually join the server
- L201 _protected prototype_ `void AckJoiningServer();` — Acknowledge that client is traveling
- L203 _protected prototype_ `virtual void ClientAckJoiningServer();` — `UFUNCTION(client, reliable)`
- L212 _protected prototype_ `virtual void ServerKickPlayer(const FUniqueNetIdRepl& PlayerToKick, const FText& Reason);` — `UFUNCTION(server, reliable, WithValidation)` — Make a request to kick a given player @param PlayerToKick player kick request @param Reason reason for the kick to tell client if this succeeds
- L221 _protected prototype_ `virtual void ServerSetPartyOwner(const FUniqueNetIdRepl& InUniqueId, const FUniqueNetIdRepl& InPartyOwnerId);` — `UFUNCTION(Server, Reliable, WithValidation)` — Make a request to set the party owner for the given player @param InUniqueId id of the requesting player @param PartyOwnerUniqueId id the party owner
- L230 _protected prototype_ `void ClientLoginComplete(const FUniqueNetIdRepl& InUniqueId, bool bWasSuccessful);` — `UFUNCTION(client, reliable)` — Client notification result for a single login attempt @param InUniqueId id of player involved @param bWasSuccessful result of the login attempt
- L238 _protected prototype_ `void ClientWasKicked(const FText& KickReason);` — `UFUNCTION(client, reliable)` — This was client was kicked by the server @param KickReason reason the server kicked the local player
- L247 _protected prototype_ `virtual void ClientPlayerJoined(const FText& NewPlayerName, const FUniqueNetIdRepl& InUniqueId);` — `UFUNCTION(client, reliable)` — Client notification that another player has joined the lobby @param NewPlayerName display name of new player @param InUniqueId unique id of new player
- L255 _protected prototype_ `virtual void ClientPlayerLeft(const FUniqueNetIdRepl& InUniqueId);` — `UFUNCTION(client, reliable)` — Client notification that another player has left the lobby @param InUniqueId unique id of new player

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LOBBY_API`
- L21 _delegate_ `DECLARE_DELEGATE(FOnLobbyConnectionEstablished);` — Delegate called a connection with the lobby beacon is established (but not logged in yet)
- L21 _prototype_ `DECLARE_DELEGATE(FOnLobbyConnectionEstablished);` — Delegate called a connection with the lobby beacon is established (but not logged in yet)
- L26 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnLobbyPlayerJoined, const FText& , const FUniqueNetIdRepl& );` — Delegate called when a player joins the lobby
- L26 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnLobbyPlayerJoined, const FText& , const FUniqueNetIdRepl& );` — Delegate called when a player joins the lobby
- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLobbyPlayerLeft, const FUniqueNetIdRepl& );` — Delegate called when a player leaves the lobby
- L31 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLobbyPlayerLeft, const FUniqueNetIdRepl& );` — Delegate called when a player leaves the lobby
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLobbyLoginComplete, bool );` — Delegate called when the login handshake for this client is complete
- L36 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLobbyLoginComplete, bool );` — Delegate called when the login handshake for this client is complete
- L41 _delegate_ `DECLARE_DELEGATE(FOnJoiningGame);` — Delegate called when the player is joining the game from the lobby
- L41 _prototype_ `DECLARE_DELEGATE(FOnJoiningGame);` — Delegate called when the player is joining the game from the lobby

### `Plugins/Online/OnlineFramework/Source/Lobby/Public/LobbyBeaconHost.h` (Public)


#### class `ALobbyBeaconHost`  
`class ALobbyBeaconHost : public AOnlineBeaconHostObject`  
_L24-161_
- reflection: `UCLASS(MinimalAPI, transient, config=Engine)`
- inherits: `AOnlineBeaconHostObject`
- desc: Host object for maintaining a lobby before players actually join a server ready to receive them
- L29 _private prototype_ `void NotifyClientDisconnected(AOnlineBeaconClient* LeavingClientActor);`
- L37 _private prototype_ `virtual bool Init(FName InSessionName);` — Initialize the lobby beacon, creating an object to maintain state @param InSessionName name of session the beacon is associated with
- L44 _private prototype_ `virtual void SetupLobbyState(int32 InMaxPlayers);` — Create the lobby game state and associate it with the game @param InMaxPlayers max number of players allowed in the lobby
- L52 _private prototype_ `void UpdatePartyLeader(const FUniqueNetIdRepl& PartyMemberId, const FUniqueNetIdRepl& NewPartyLeaderId);` — Update the party leader for a given player @param PartyMemberId player reporting a new party leader @param NewPartyLeaderId the new party leader
- L60 _private prototype_ `void KickPlayer(ALobbyBeaconClient* ClientActor, const FText& KickReason);` — Actually kick a given player from the lobby @param ClientActor client connection to kick @param KickReason reason for the kick
- L67 _private prototype_ `virtual void HandlePlayerLogout(const FUniqueNetIdRepl& InUniqueId);` — Handle a detected disconnect of an existing player on the server @param InUniqueId unique id of the player
- L74 _private prototype_ `virtual void AdvertiseSessionJoinability(const FJoinabilitySettings& Settings);` — Tell all connected beacon clients about the current joinability settings @param Setting current joinability settings
- L83 _private prototype_ `bool DoesSessionMatch(const FString& InSessionId) const;` — Does the session associated with the beacon match the incoming request @param InSessionId incoming session id @return true if sessions match, false otherwise
- L88 _private prototype_ `void DumpState() const;` — Output current state of beacon to log
- L93 _protected member_ `FName SessionName;` — Name of session this beacon is associated with
- L97 _protected member_ `TSoftClassPtr<ALobbyBeaconState> LobbyStateClass;` — `UPROPERTY()` — Class to use for the lobby beacon state
- L101 _protected member_ `TObjectPtr<ALobbyBeaconState> LobbyState;` — `UPROPERTY()` — Actor representing the state of the lobby (similar to AGameState)
- L104 _protected prototype_ `virtual bool PreLogin(const FUniqueNetIdRepl& InUniqueId, const FString& Options);`
- L111 _protected prototype_ `virtual void PostLogin(ALobbyBeaconClient* ClientActor);` — Notification call that a new lobby connection has been successfully establish @param ClientActor new lobby client connection
- L121 _protected prototype_ `void ProcessLogin(ALobbyBeaconClient* ClientActor, const FString& InSessionId, const FUniqueNetIdRepl& InUniqueId, const FString& UrlString);` — Process the login for a given connection @param Client client beacon making the request @param InSessionId id of the session that is being checked @param InUniqueId id of the player logging in @param UrlString URL containing player options (name, etc)
- L128 _protected prototype_ `virtual bool ProcessJoinServer(ALobbyBeaconClient* ClientActor);` — Handle a request from a client when they are actually joining the server (needed for keeping player around when lobby beacon disconnects) @param ClientActor client that is making the request
- L136 _protected prototype_ `void ProcessDisconnect(ALobbyBeaconClient* ClientActor);` — Handle a request to disconnect a given client from the lobby beacon Notifies the owning beacon host to do its own cleanup @param ClientActor client that is making the request
- L147 _protected prototype_ `virtual bool ProcessKickPlayer(ALobbyBeaconClient* Instigator, const FUniqueNetIdRepl& PlayerToKick, const FText& Reason);` — Handle a request from a client to kick another player (may not succeed) @param Instigator player making the request @param PlayerToKick id of the player to kick @param Reason reason for the kick @return true if the player was kicked, false if not
- L158 _protected prototype_ `virtual ALobbyBeaconPlayerState* HandlePlayerLogin(ALobbyBeaconClient* ClientActor, const FUniqueNetIdRepl& InUniqueId, const FString& Options);` — Handle a player logging in via the host beacon @param ClientActor client that is making the request @param InUniqueId unique id of the player @param Options game options passed in by the client at login @return new player state object for the logged in player, null if there was any failure

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LOBBY_API`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLobbyBeacon, Log, All);`

### `Plugins/Online/OnlineFramework/Source/Lobby/Public/LobbyBeaconPlayerState.h` (Public)


#### class `ALobbyBeaconPlayerState`  
`class ALobbyBeaconPlayerState : public AInfo`  
_L19-86_
- reflection: `UCLASS(MinimalAPI, transient, config = Game, notplaceable)`
- inherits: `AInfo`
- desc: Lightweight representation of a player while connected to the game through the lobby exists for the lifetime of a player whether they are in the lobby or not assumption that the data here doesn't change often and locks when they actually join the server
- L24 _private prototype_ `virtual void PostInitializeComponents() override;`
- L25 _private prototype_ `virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;`
- L29 _private prototype_ `bool IsValid() const;` — @return true if this data structure is valid
- L33 _private member_ `FText DisplayName;` — `UPROPERTY(Replicated)` — Visible friendly player name
- L37 _private member_ `FUniqueNetIdRepl UniqueId;` — `UPROPERTY(ReplicatedUsing = OnRep_UniqueId)` — Player unique id
- L41 _private member_ `FUniqueNetIdRepl PartyOwnerUniqueId;` — `UPROPERTY(ReplicatedUsing = OnRep_PartyOwner)` — Party owner id
- L45 _private member_ `bool bInLobby;` — `UPROPERTY(ReplicatedUsing = OnRep_InLobby)` — Is the player in the lobby or game
- L49 _private member_ `TObjectPtr<AOnlineBeaconClient> ClientActor;` — `UPROPERTY(Replicated)` — Reference to the beacon actor related to this player
- L56 _private prototype_ `DECLARE_EVENT_OneParam( ALobbyBeaconPlayerState, FOnPlayerStateChanged, const FUniqueNetIdRepl& );` — Delegate fired when this player state has changed in some way @param UniqueId id of the player that changed
- L59 _private function_ `inline FOnPlayerStateChanged& OnUniqueIdReplicated()` — @return delegate fired when the unique id of the player has been replicated
- L61 _private function_ `inline FOnPlayerStateChanged& OnPlayerStateChanged()` — @return delegate fired when the state of the player has changed in some way
- L63 _private function_ `inline FOnPlayerStateChanged& OnPartyOwnerChanged()` — @return delegate fired when the party owner of this player has changed
- L69 _protected prototype_ `void OnRep_UniqueId();` — `UFUNCTION()` — Unique Id has replicated
- L73 _protected prototype_ `void OnRep_PartyOwner();` — `UFUNCTION()` — Party owner has changed
- L77 _protected prototype_ `void OnRep_InLobby();` — `UFUNCTION()` — Player has joined or left the lobby
- L81 _private member_ `FOnPlayerStateChanged UniqueIdReplicatedEvent;` — Delegate fired when player unique id is replicated
- L83 _private member_ `FOnPlayerStateChanged PlayerStateChangedEvent;` — Delegate fired when player state changes
- L85 _private member_ `FOnPlayerStateChanged PartyOwnerChangedEvent;` — Delegate fired when party owner changes

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LOBBY_API`
- L56 _delegate_ `DECLARE_EVENT_OneParam( ALobbyBeaconPlayerState, FOnPlayerStateChanged, const FUniqueNetIdRepl& );` — Delegate fired when this player state has changed in some way @param UniqueId id of the player that changed

### `Plugins/Online/OnlineFramework/Source/Lobby/Public/LobbyBeaconState.h` (Public)


#### struct `FLobbyPlayerStateActorInfo`  
`struct FLobbyPlayerStateActorInfo : public FFastArraySerializerItem`  
_L40-76_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializerItem`
- desc: Replication structure for a single beacon player state
- L47 _public function_ `FLobbyPlayerStateActorInfo() : LobbyPlayerState(nullptr)` — Constructors
- L51 _public function_ `FLobbyPlayerStateActorInfo(ALobbyBeaconPlayerState* InPlayerState) : LobbyPlayerState(InPlayerState)`
- L57 _public member_ `TObjectPtr<ALobbyBeaconPlayerState> LobbyPlayerState;` — `UPROPERTY()` — Actual player state actor
- L60 _public prototype_ `void PreReplicatedRemove(const FLobbyPlayerStateInfoArray& InArraySerializer);` — Player state removal
- L67 _public prototype_ `void PostReplicatedAdd(const FLobbyPlayerStateInfoArray& InArraySerializer);` — Player state additions This may only be a notification that the array is growing and the actor data isn't available yet, in which case the actual element will be null
- L75 _public prototype_ `void PostReplicatedChange(const FLobbyPlayerStateInfoArray& InArraySerializer);` — Player state element has changed In this specific case only happens when the actor pointer is set. This should only occur if the player state actor was already serialized to the client at the time of the PostReplicatedAdd call

#### struct `FLobbyPlayerStateInfoArray`  
`struct FLobbyPlayerStateInfoArray : public FFastArraySerializer`  
_L80-153_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializer`
- desc: Struct for fast TArray replication of lobby player state
- L85 _public function_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms)` — Implement support for fast TArray replication
- L98 _public prototype_ `ALobbyBeaconPlayerState* AddPlayer(const FText& PlayerName, const FUniqueNetIdRepl& UniqueId);` — Create and replicate the appropriate player state for the new player @param PlayerName display name of new player @param UniqueId unique id of the new player @return player state representation of the new player
- L105 _public prototype_ `void RemovePlayer(const FUniqueNetIdRepl& UniqueId);` — Remove an existing player from the lobby @param UniqueId unique id of the player to remove
- L114 _public prototype_ `ALobbyBeaconPlayerState* GetPlayer(const FUniqueNetIdRepl& UniqueId);` — Get an existing player @param UniqueId unique id for the player of interest @return player state representation of an existing player
- L123 _public prototype_ `ALobbyBeaconPlayerState* GetPlayer(const AOnlineBeaconClient* ClientActor);` — Get an existing player @param ClientActor beacon actor for the player of interest @return player state representation of an existing player
- L130 _public function_ `TArray<FLobbyPlayerStateActorInfo>& GetAllPlayers()` — Get all players in the lobby @return all player representations in the lobby
- L131 _public function_ `const TArray<FLobbyPlayerStateActorInfo>& GetAllPlayers() const`
- L134 _public function_ `int32 GetNumPlayers() const` — @return number of players currently in the lobby
- L139 _public prototype_ `void DumpState() const;` — Output current state of players to log
- L145 _private member_ `TArray<FLobbyPlayerStateActorInfo> Players;` — `UPROPERTY()` — All of the players in the lobby
- L149 _private member_ `TObjectPtr<ALobbyBeaconState> ParentState = nullptr;` — `UPROPERTY(NotReplicated)` — Owning lobby beacon for this array of players

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FLobbyPlayerStateInfoArray> : public TStructOpsTypeTraitsBase2<FLobbyPlayerStateInfoArray>`  
_L157-163_
- inherits: `TStructOpsTypeTraitsBase2<FLobbyPlayerStateInfoArray>`
- desc: Specified to allow fast TArray replication

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L160-162_

#### class `ALobbyBeaconState`  
`class ALobbyBeaconState : public AInfo`  
_L171-356_
- reflection: `UCLASS(MinimalAPI, transient, config = Game, notplaceable)`
- inherits: `AInfo`
- desc: Shared state of the game from the lobby perspective Duplicates much of the data in the traditional AGameState object for sharing with players connected via beacon only
- L176 _private prototype_ `virtual void PostInitProperties() override;`
- L180 _private prototype_ `virtual void PostInitializeComponents() override;`
- L181 _private prototype_ `virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;`
- L187 _private prototype_ `void StartLobby();` — Start the lobby for incoming players
- L192 _private prototype_ `virtual void StartWaiting();` — Start the waiting for other players (first player logged in success)
- L199 _private prototype_ `virtual bool RequireFullLobbyToStart() const;` — Determines whether the beacon state requires a full game before allowing a lobby to start; False by default @return Whether the beacon state requires a full game before allowing a lobby to start; False by default
- L209 _private prototype_ `ALobbyBeaconPlayerState* AddPlayer(const FText& PlayerName, const FUniqueNetIdRepl& UniqueId);` — Create and replicate the appropriate player state for the new player @param PlayerName display name of new player @param UniqueId unique id of the new player @return player state representation of the new player
- L216 _private prototype_ `void RemovePlayer(const FUniqueNetIdRepl& UniqueId);` — Remove an existing player from the lobby @param UniqueId unique id of the player to remove
- L224 _private prototype_ `void UpdatePartyLeader(const FUniqueNetIdRepl& PartyMemberId, const FUniqueNetIdRepl& NewPartyLeaderId);` — Update the party leader for a given player @param PartyMemberId player reporting a new party leader @param NewPartyLeaderId the new party leader
- L233 _private prototype_ `ALobbyBeaconPlayerState* GetPlayer(const FUniqueNetIdRepl& UniqueId);` — Get an existing player in the lobby @param UniqueId unique id for the player of interest @return player state representation of an existing player
- L242 _private prototype_ `ALobbyBeaconPlayerState* GetPlayer(const FString& UniqueId);` — Get an existing player in the lobby @param UniqueId unique id for the player of interest passed as string @return player state representation of an existing player
- L251 _private prototype_ `ALobbyBeaconPlayerState* GetPlayer(const AOnlineBeaconClient* ClientActor);` — Get an existing player in the lobby @param ClientActor beacon actor for the player of interest @return player state representation of an existing player
- L254 _private function_ `FOnPlayerLobbyStateChanged& OnPlayerLobbyStateAdded()` — @return delegate fired when a player is added to the lobby
- L257 _private function_ `FOnPlayerLobbyStateChanged& OnPlayerLobbyStateRemoved()` — @return delegate fired when a player is removed from the lobby
- L260 _private function_ `FOnLobbyStarted& OnLobbyStarted()` — @return delegate fired when the lobby is started
- L263 _private function_ `FOnLobbyWaitingForPlayersUpdate& OnLobbyWaitingForPlayersUpdate()` — @return delegate fired as time counts down waiting for players
- L266 _private function_ `bool HasLobbyStarted() const` — @return true if the lobby has started, false otherwise
- L269 _private function_ `int32 GetNumPlayers() const` — @return number of players currently in the lobby
- L272 _private function_ `int32 GetMaxPlayers() const` — @return number of players total allowed in the lobby
- L277 _private prototype_ `void DumpState() const;` — Output current state of lobby to log
- L283 _protected member_ `int32 MaxPlayers;` — `UPROPERTY()` — Total number of players allowed in the lobby
- L287 _protected member_ `TSubclassOf<ALobbyBeaconPlayerState> LobbyBeaconPlayerStateClass;` — `UPROPERTY()` — Class to use for lobby beacon player states
- L290 _protected member_ `double LastTickTime;` — Time that last tick occurred for calculating wait time
- L294 _protected member_ `bool bLobbyStarted;` — `UPROPERTY(ReplicatedUsing = OnRep_LobbyStarted)` — Has the lobby already been started
- L298 _protected member_ `float WaitForPlayersTimeRemaining;` — `UPROPERTY(config, ReplicatedUsing = OnRep_WaitForPlayersTimeRemaining)` — Amount of time waiting for other players before starting the lobby
- L302 _protected member_ `FLobbyPlayerStateInfoArray Players;` — `UPROPERTY(Replicated)` — Array of players currently in the game, lobby or otherwise
- L306 _protected prototype_ `void OnRep_LobbyStarted();` — `UFUNCTION()` — Handle the lobby starting
- L310 _protected prototype_ `void OnRep_WaitForPlayersTimeRemaining();` — `UFUNCTION()` — Handle notification of time left to wait for lobby to start
- L313 _protected member_ `FOnLobbyStarted LobbyStarted;` — Delegate fired when the lobby starts
- L316 _protected member_ `FOnLobbyWaitingForPlayersUpdate LobbyWaitingForPlayersUpdate;` — Delegate fired as time counts down waiting for players in the lobby
- L319 _protected member_ `FOnPlayerLobbyStateChanged PlayerLobbyStateAdded;` — Delegate fired when a player is added to the lobby
- L322 _protected member_ `FOnPlayerLobbyStateChanged PlayerLobbyStateRemoved;` — Delegate fired when a player is removed from the lobby
- L325 _protected member_ `FTimerHandle OneSecTimerHandle;` — Handle to manage a one sec timer
- L335 _protected prototype_ `virtual ALobbyBeaconPlayerState* CreateNewPlayer(const FText& PlayerName, const FUniqueNetIdRepl& UniqueId);` — Create a new player for this lobby beacon state @param PlayerName name of the player @param UniqueId uniqueid of the player @return new player state actor or nullptr if the player should be disconnected
- L338 _protected prototype_ `void OneSecTick();` — One sec tick function to handle countdowns
- L345 _protected prototype_ `virtual void OnPreLobbyStartedTickInternal(double DeltaTime);` — Internal helper function called as part of OneSecTick if the lobby hasn't been started yet @param DeltaTime	Time slice since last tick
- L352 _protected prototype_ `virtual void OnPostLobbyStartedTickInternal(double DeltaTime);` — Internal helper function called as part of OneSecTick if the lobby has been started already @Param DeltaTime	Time slice since last tick

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LOBBY_API`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnLobbyStarted);` — Delegate fired when the lobby is open to players
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnLobbyStarted);` — Delegate fired when the lobby is open to players
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnLobbyWaitingForPlayersUpdate) DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerLobbyStateChanged, ALobbyBeaconPlayerState* );` — Delegate fired as time counts down waiting for players in the lobby
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerLobbyStateChanged, ALobbyBeaconPlayerState* );` — Delegate fired when the player state in the lobby has changed (add/remove/etc) @param PlayerState player of interest (post addition / pre removal)
- L34 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerLobbyStateChanged, ALobbyBeaconPlayerState* );` — Delegate fired when the player state in the lobby has changed (add/remove/etc) @param PlayerState player of interest (post addition / pre removal)
- L161 _enumerator_ `WithNetDeltaSerializer = true` (scope `TStructOpsTypeTraits::__anon082a6fc90103`)

### `Plugins/Online/OnlineFramework/Source/Lobby/Public/LobbyModule.h` (Public)


#### class `FLobbyModule`  
`class FLobbyModule : public IModuleInterface`  
_L19-61_
- inherits: `IModuleInterface`
- desc: Module for lobbies via online beacon
- L31 _public function_ `static inline FLobbyModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L41 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L54 _private prototype_ `virtual void StartupModule() override;` — Called when lobby module is loaded Initialize platform specific parts of Lobby handling
- L60 _private prototype_ `virtual void ShutdownModule() override;` — Called when lobby module is unloaded Shutdown platform specific parts of Lobby handling

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLobby, Display, All);` — Logging related to parties
- L12 _delegate_ `DECLARE_STATS_GROUP(TEXT("Lobby"), STATGROUP_Lobby, STATCAT_Advan` — Lobby module stats

### `Plugins/Online/OnlineFramework/Source/Lobby/Public/LobbyPackage.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define PACKAGE_SCOPE public`
- L12 _macro_ `#define PACKAGE_SCOPE protected`
