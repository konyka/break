# Plugins / MultiServerReplication

- module root: `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication`
- headers: 10; symbols: 387
- symbol kinds: class=18, delegate=4, enum=3, enumerator=14, function=28, member=130, namespace=3, prototype=179, struct=8
- PrivateDependencyModuleNames: Core, CoreOnline, CoreUObject, Engine, IrisCore, MultiServerConfiguration, NetCore, Sockets
- PublicDependencyModuleNames: OnlineSubsystemUtils

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Private/MultiServerBeaconHost.h` (Private)


#### class `AMultiServerBeaconHost`  
`class AMultiServerBeaconHost : public AOnlineBeaconHost`  
_L13-29_
- reflection: `UCLASS(transient, config=Engine)`
- inherits: `AOnlineBeaconHost`
- desc: An online beacon that helps manage connecting to MultiServer networks, and replicating metadata about the MultiServer network.
- L18 _public prototype_ `AMultiServerBeaconHost(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual bool InitHost() override;`
- L21 _public prototype_ `virtual void NotifyControlMessage(UNetConnection* Connection, uint8 MessageType, FInBunch& Bunch) override;`
- L24 _public prototype_ `virtual bool AtCapacity() const;` — @return Whether or not this Node already has the maximum number of allowable connections.
- L28 _protected member_ `int32 MaxConnections;` — `UPROPERTY(config)`

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Private/MultiServerBeaconHostObject.h` (Private)


#### class `AMultiServerBeaconHostObject`  
`class AMultiServerBeaconHostObject : public AOnlineBeaconHostObject`  
_L14-32_
- reflection: `UCLASS(transient, config=Engine)`
- inherits: `AOnlineBeaconHostObject`
- L19 _public prototype_ `AMultiServerBeaconHostObject(const FObjectInitializer& ObjectInitializer);`
- L21 _public prototype_ `void SetClientBeaconActorClass(TSubclassOf<AOnlineBeaconClient> InClientBeaconActorClass);`
- L22 _public function_ `void SetOwningNode(UMultiServerNode* InOwningNode)`
- L24 _public prototype_ `virtual void OnClientConnected(AOnlineBeaconClient* NewClientActor, UNetConnection* ClientConnection) override;`
- L26 _public prototype_ `virtual void NotifyClientDisconnected(AOnlineBeaconClient* LeavingClientActor) override;`
- L31 _private member_ `TObjectPtr<UMultiServerNode> OwningNode;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMultiServerBeacon, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMultiServerBeacon, Log, All);`

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Private/MultiServerNetDriver.h` (Private)


#### class `UMultiServerNetDriver`  
`class UMultiServerNetDriver : public UIpNetDriver`  
_L26-32_
- reflection: `UCLASS(Transient)`
- inherits: `UIpNetDriver`
- desc: Multi-server nodes need to use UMultiServerNetDriver (or a subclass) because they control the ticking of their NetDrivers directly instead of letting the world tick them. Use this MultiServerNetDriver as the DriverClassName for the MultiServerNetDriver definition in your project's NetDriverDefinitions engine config, for example: [/Script/Engine.Engine] +NetDriverDefinitions=(DefName="MultiServerNetDriver", DriverClassName="/Script/MultiServerReplication.MultiServerNetDriver", DriverClassNameFallback="/Script/MultiServerReplication.MultiServerNetDriver") This allows control over the timing of the Tick(Flush|Dispatch) and PostTick(Flush|Dispatch) functions to ensure they're always called as atomic units. Since MultiServer drivers might be ticked from within a NetDriver that's being ticked by the world, and the world ticks in passes (all netdrivers Tick, then all netdrivers PostTick), we could end up in a situation where a MultiServer driver has Ticked, and is Ticked again before the corresponding PostTick was called (if the world was allowed to tick the MultiServer drivers). This is not compatible with Iris replication. We use a NetDriver subclass so we can override SetWorld and undo the normal world tick registration.
- L31 _public prototype_ `virtual void SetWorld(UWorld* InWorld) override;`

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Private/MultiServerPeerConnection.h` (Private)


#### class `UMultiServerPeerConnection`  
`class UMultiServerPeerConnection : public UObject`  
_L16-48_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Net connection class specific to MultiServer Networking.
- L21 _public prototype_ `UMultiServerPeerConnection();`
- L23 _public prototype_ `void InitClientBeacon();`
- L24 _public prototype_ `void DestroyClientBeacon();`
- L25 _public prototype_ `void ClearConnectRetryTimer();`
- L27 _public prototype_ `float GetRetryDelay();`
- L29 _public prototype_ `void OnBeaconConnectionFailure();`
- L32 _public member_ `TObjectPtr<AMultiServerBeaconClient> BeaconClient;` — `UPROPERTY()`
- L34 _public function_ `void SetOwningNode(UMultiServerNode* InOwningNode)`
- L35 _public function_ `void SetRemoteAddress(FString InRemoteAddress)`
- L36 _public function_ `void SetLocalPeerId(FString InLocalPeerId)`
- L39 _private member_ `int ConnectAttemptNum = 0;`
- L41 _private member_ `FTimerHandle ConnectRetryTimerHandle;`
- L44 _private member_ `TObjectPtr<UMultiServerNode> OwningNode;` — `UPROPERTY()`
- L46 _private member_ `FString RemoteAddress;`
- L47 _private member_ `FString LocalPeerId;`

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Public/MultiServerBeaconClient.h` (Public)


#### class `AMultiServerBeaconClient`  
`class AMultiServerBeaconClient : public AOnlineBeaconClient`  
_L21-92_
- reflection: `UCLASS(transient, config=Engine, notplaceable)`
- inherits: `AOnlineBeaconClient`
- desc: An online beacon that helps manage connecting to MultiServer Networks, and replicating metadata about the MultiServer Network. This Actor will exist on All MultiServer Nodes, and multiple MultiServerBeaconClient Actors may exist on non-Client Nodes, one for each other connected node.
- L26 _public prototype_ `AMultiServerBeaconClient();`
- L29 _public prototype_ `virtual void DestroyBeacon() override;`
- L30 _public prototype_ `virtual void OnConnected() override;`
- L31 _public prototype_ `virtual void OnFailure() override;`
- L35 _public prototype_ `virtual bool InitBase() override;`
- L45 _public prototype_ `virtual void ConnectToServer(const FString& ConnectInfo);` — Attempt to connect to another specified MultiServer node. AOnlineBeaconClient::OnFailure will be called immediately if there's a problem within this call. @param ConnectionInfo	Information
- L47 _public function_ `void SetOwningNode(UMultiServerNode* InOwningNode)`
- L50 _public prototype_ `virtual void ServerUpdateLevelVisibility(const FUpdateLevelVisibilityLevelInfo& LevelVisibility);` — `UFUNCTION(Reliable, Server, WithValidation)`
- L53 _public prototype_ `void ServerUpdateMultipleLevelsVisibility(const TArray<FUpdateLevelVisibilityLevelInfo>& LevelVisibilities);` — `UFUNCTION(Reliable, Server, WithValidation, SealedEvent)`
- L56 _public prototype_ `FString GetRemotePeerId() const;` — The Id on the other side of the connection
- L59 _public prototype_ `FString GetLocalPeerId() const;` — The Id on the local side of the connection
- L67 _public prototype_ `bool IsAuthorityBeacon() const;` — Actor Role on client beacons stays as authority, so this function can be used to determine whether this instance is acting as an authority. Currently, can be used to know whether a Client or Server RPC should be called from this instance. But once a new RPC type that supports both clients and servers simultaneously is added, this concept will be abstracted and we shouldn't need this function anymore.
- L71 _protected member_ `FString RemotePeerId;` — `UPROPERTY()`
- L73 _protected prototype_ `virtual void OnLevelRemovedFromWorld(class ULevel* Level, class UWorld* World);`
- L74 _protected prototype_ `virtual void OnLevelAddedToWorld(class ULevel* Level, class UWorld* World);`
- L76 _protected member_ `FDelegateHandle OnLevelRemovedFromWorldHandle;`
- L77 _protected member_ `FDelegateHandle OnLevelAddedToWorldHandle;`
- L79 _protected prototype_ `FName NetworkRemapPath(FName InPackageName, bool bReading);`
- L85 _private prototype_ `void ClientPeerConnected(const FString& NewRemotePeerId, AMultiServerBeaconClient* Beacon);` — `UFUNCTION(Client, Reliable)`
- L88 _private prototype_ `void ServerSetRemotePeerId(const FString& NewRemotePeerId);` — `UFUNCTION(Reliable, Server)`
- L91 _private member_ `TObjectPtr<UMultiServerNode> OwningNode;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE(FOnMultiServerConnectionEstablished);`
- L11 _prototype_ `DECLARE_DELEGATE(FOnMultiServerConnectionEstablished);`

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Public/MultiServerNode.h` (Public)


#### struct `FMultiServerNodeCreateParams`  
`struct FMultiServerNodeCreateParams`  
_L23-48_
- desc: Parameters for initializing a UMultiServerNode
- L26 _public member_ `UWorld* World = nullptr;` — World in which to create the node
- L29 _public member_ `FString LocalPeerId;` — String identifier of this node. Must be unique among all nodes that will connect to each other.
- L32 _public member_ `FString ListenIp;` — The local IP address of this node, only used so it can find itself in the PeerAddresses list.
- L35 _public member_ `uint16 ListenPort = 0;` — The port on which this node will listen for new connections.
- L38 _public member_ `uint32 NumServers = 1;` — The number of servers we're expecting in the cluster
- L41 _public member_ `TArray<FString> PeerAddresses;` — List of addresses of other nodes to attempt to connect to.
- L44 _public member_ `TSubclassOf<AMultiServerBeaconClient> UserBeaconClass;` — Beacon client class that will be instantiated for each connection. Can implement its own RPCs.
- L47 _public member_ `FOnMultiServerConnectedEvent OnMultiServerConnected;` — Callback invoked when a connection to a remote node is established.

#### class `UMultiServerNode`  
`class UMultiServerNode : public UObject`  
_L65-167_
- reflection: `UCLASS(Config=Engine, Transient, DisplayName = "MultiServer Node")`
- inherits: `UObject`
- desc: The MultiServer node is a system / control scheme for connecting multiple dedicated server processes to each other and allowing them to communicate via online beacons. The basic usage pattern is to create a UMultiServerNode in project code via UMultiServerNode::Create. For a typical UE game, a good place might be in an AGameSession subclass in the RegisterServer override. The node manages all the connections to other servers, and will attempt to establish them upon creation based on the PeerAddresses in the FMultiServerNodeCreateParams. The main user-extension point is to subclass AMultiServerBeaconClient. This subclass can implement its own RPCs to send custom messages to other servers connected to the node. The OnMultiServerConnected callback in the FMultiServerNodeCreateParams will be called when a new connection is established, with the instance of the user beacon as an argument. The user code can call its RPCs on the instance.
- L70 _public prototype_ `UMultiServerNode();`
- L72 _public prototype_ `static UMultiServerNode* Create(const FMultiServerNodeCreateParams& Params);`
- L74 _public prototype_ `static void ParseCommandLineIntoCreateParams(FMultiServerNodeCreateParams& InOutParams);`
- L76 _public prototype_ `virtual void BeginDestroy() override;`
- L79 _public prototype_ `bool AreAllServersConnected() const;` — @return true if all of the servers we are expecting have connected and registered with this node
- L81 _public prototype_ `bool RegisterServer(const FMultiServerNodeCreateParams& Params);`
- L83 _public prototype_ `AMultiServerBeaconClient* GetBeaconClientForRemotePeer(FStringView RemotePeerId) const;`
- L86 _public prototype_ `template<class T> T* GetBeaconClientForRemotePeer(FStringView RemotePeerId) const;`
- L88 _public prototype_ `AMultiServerBeaconClient* GetBeaconClientForURL(const FString& InURL) const;`
- L91 _public prototype_ `template<class T> T* GetBeaconClientForURL(const FString& InURL) const;`
- L93 _public function_ `FString GetLocalPeerId() const`
- L95 _public function_ `float GetRetryConnectDelay() const`
- L96 _public function_ `float GetRetryConnectMaxDelay() const`
- L98 _public function_ `TSubclassOf<AMultiServerBeaconClient> GetUserBeaconClass() const`
- L100 _public prototype_ `void ForEachBeaconClient(TFunctionRef<void(AMultiServerBeaconClient*)> Operation) const;`
- L102 _public prototype_ `void ForEachNetDriver(TFunctionRef<void(UNetDriver*)> Operation) const;`
- L105 _public prototype_ `uint32 GetConnectionCount() const;` — How many acknolwedged connections do we have?
- L108 _public function_ `uint32 GetNumExpectedConnections() const` — How many connections are we expecting?
- L111 _public prototype_ `void NotifyMultiServerConnected(const FString& LocalServerId, const FString& ConnectedRemoteServerId, AMultiServerBeaconClient* ConnectionToServer);` — Notify this MultiServerNode that a Beacon has connected to it
- L114 _public function_ `TMulticastDelegateRegistration<void(UMultiServerNode*)>& OnAllServersConnected()` — Allow users to register a delegate for when all servers are connected
- L119 _public function_ `void BroadcastAllServersConnected()`
- L125 _private member_ `FOnAllServersConnectedEvent OnAllServersConnectedEvent;`
- L127 _private member_ `FOnMultiServerConnectedEvent OnMultiServerConnectedEvent;`
- L129 _private member_ `FString LocalPeerId;`
- L132 _private member_ `TObjectPtr<AMultiServerBeaconHost> BeaconHost;` — `UPROPERTY()`
- L135 _private member_ `TObjectPtr<AMultiServerBeaconHostObject> BeaconHostObject;` — `UPROPERTY()`
- L138 _private member_ `TArray<TObjectPtr<UMultiServerPeerConnection>> PeerConnections;` — `UPROPERTY()`
- L141 _private member_ `float RetryConnectDelay;` — `UPROPERTY(Config)`
- L144 _private member_ `float RetryConnectMaxDelay;` — `UPROPERTY(Config)`
- L146 _private member_ `TSubclassOf<AMultiServerBeaconClient> UserBeaconClass;`
- L149 _private member_ `uint32 NumExpectedServers = 1;` — How many servers are we expecting (including ourselves). This should be at least 1.
- L159 _private member_ `FDelegateHandle TickDispatchDelegateHandle;` — Multi-server nodes handle ticking of their NetDrivers directly instead of letting the world tick them. This allows us to control the timing of the Tick(Flush|Dispatch) and PostTick(Flush|Dispatch) functions to ensure they're always called as atomic units. Since MultiServer drivers might be ticked from within a NetDriver that's being ticked by the world, and the world ticks in passes (all netdrivers Tick, then all netdrivers PostTick), we could end up in a situation where a MultiServer driver has Ticked, and is Ticked again before the corresponding PostTick was called (if the world was allowed to tick the MultiServer drivers). Note UMultiServerNetDriver::SetWorld unregisters from world tick events. See UMultiServerNetDriver.
- L160 _private member_ `FDelegateHandle TickFlushDelegateHandle;`
- L162 _private prototype_ `void RegisterTickEvents();`
- L163 _private prototype_ `void UnregisterTickEvents();`
- L165 _private prototype_ `void InternalTickDispatch(float DeltaSeconds);`
- L166 _private prototype_ `void InternalTickFlush(float DeltaSeconds);`
- L170 _function_ `template<class T> T* UMultiServerNode::GetBeaconClientForRemotePeer(FStringView RemotePeerId) const`
- L176 _function_ `template<class T> T* UMultiServerNode::GetBeaconClientForURL(const FString& InURL) const`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnMultiServerConnectedEvent, const FString&, const FString&, AMultiServerBeaconClient*);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnMultiServerConnectedEvent, const FString&, const FString&, AMultiServerBeaconClient*);`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAllServersConnectedEvent, UMultiServerNode*);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAllServersConnectedEvent, UMultiServerNode*);`

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Public/MultiServerProxy.h` (Public)


#### struct `UE::MultiServerProxy::Private::FPendingBroadcastRPC`  
`struct FPendingBroadcastRPC`  
_L19-37_
- L21 _public member_ `TObjectKey<const UFunction> Function;`
- L23 _public member_ `TArray<uint8> Parms;`
- L25 _public member_ `TObjectKey<const UObject> SubObject;`
- L27 _public prototype_ `FPendingBroadcastRPC() = default;`
- L28 _public prototype_ `FPendingBroadcastRPC(FPendingBroadcastRPC&& Other) = default;`
- L29 _public prototype_ `FPendingBroadcastRPC& operator=(FPendingBroadcastRPC&& Other) = default;`
- L31 _public prototype_ `FPendingBroadcastRPC(const UFunction* InFunction, const void* InParms, const UObject* InSubObject);`
- L32 _public prototype_ `FPendingBroadcastRPC(const FPendingBroadcastRPC& Other);`
- L33 _public prototype_ `FPendingBroadcastRPC& operator=(const FPendingBroadcastRPC& Other);`
- L34 _public prototype_ `~FPendingBroadcastRPC();`
- L36 _public prototype_ `void DestroyParms();`

#### enum `EProxyConnectionState`  
`enum class EProxyConnectionState : uint8`  
_L41-50_
- L43 _public enumerator_ `Disconnected`
- L44 _public enumerator_ `Connecting`
- L45 _public enumerator_ `ConnectingPrimary`
- L46 _public enumerator_ `Connected`
- L47 _public enumerator_ `ConnectedPrimary`
- L48 _public enumerator_ `PendingReassign`
- L49 _public enumerator_ `PendingClose`

#### class `FProxyNetGUIDCache`  
`class FProxyNetGUIDCache : public FNetGUIDCache`  
_L56-66_
- inherits: `FNetGUIDCache`
- desc: A NetGUID cache used by UProxyNetDriver that doesn't assign new NetGUIDs but uses an already assigned NetGUID from a backend server connection's NetGUID cache.
- L59 _public prototype_ `FProxyNetGUIDCache(UNetDriver* NetDriver);`
- L61 _public prototype_ `virtual FNetworkGUID AssignNewNetGUID_Server(UObject* Object);`
- L62 _public prototype_ `virtual FNetworkGUID AssignNewNetGUIDFromPath_Server(const FString& PathName, UObject* ObjOuter, UClass* ObjClass);`
- L65 _private prototype_ `FNetworkGUID LookupNetGUIDFromBackendCache(UObject *Object);`

#### class `FProxyBackendNetGUIDCache`  
`class FProxyBackendNetGUIDCache : public FNetGUIDCache`  
_L68-74_
- inherits: `FNetGUIDCache`
- L71 _public prototype_ `FProxyBackendNetGUIDCache(UNetDriver* NetDriver);`
- L73 _public prototype_ `virtual bool IsNetGUIDAuthority() const;`

#### struct `FGameServerSplitJoinRequest`  
`struct FGameServerSplitJoinRequest`  
_L77-87_
- reflection: `USTRUCT()`
- L82 _public member_ `TObjectPtr<class ULocalPlayer> Player;` — `UPROPERTY()`
- L84 _public member_ `UE::Net::EJoinFlags Flags;`
- L86 _public member_ `uint32 ClientHandshakeId;`

#### struct `FGameServerConnectionState`  
`struct FGameServerConnectionState`  
_L95-127_
- reflection: `USTRUCT()`
- desc: A physical connection from the proxy server to a single game server. All proxy client connections are multiplexed to backend servers through this physical connection.
- L99 _public function_ `FGameServerConnectionState(const FURL& InGameServerURL) : GameServerURL(InGameServerURL)`
- L106 _public member_ `FURL GameServerURL;` — `UPROPERTY()` — The URL address of the Game Server (does not indicate a live connection, only intent)
- L109 _public member_ `TObjectPtr<class UWorld> World;` — `UPROPERTY()`
- L112 _public member_ `TObjectPtr<class UProxyBackendNetDriver> NetDriver;` — `UPROPERTY()`
- L114 _public member_ `FName NetDriverName;`
- L117 _public member_ `TArray<TObjectPtr<class ULocalPlayer>> Players;` — `UPROPERTY()`
- L120 _public member_ `TObjectPtr<UGameServerNotify> GameServerNotify;` — `UPROPERTY()`
- L123 _public member_ `TArray<FGameServerSplitJoinRequest> PendingSplitJoinRequests;` — `UPROPERTY()`
- L126 _public prototype_ `FGameServerConnectionState() = default;` — We are only valid with a URL, but a default constructor is needed for serialization

#### struct `FMultiServerProxyInternalConnectionRoute`  
`struct FMultiServerProxyInternalConnectionRoute`  
_L133-173_
- reflection: `USTRUCT()`
- desc: A route from a proxy client connection to a single game server.
- L137 _public member_ `uint32 ClientHandshakeId;`
- L141 _public member_ `TObjectPtr<UNetConnection> ProxyConnection;` — `UPROPERTY()` — The client connection to the proxy (the beginning of the route).
- L145 _public member_ `TObjectPtr<UNetConnection> ParentGameServerConnection;` — `UPROPERTY()` — The parent connection to the backend server.
- L149 _public member_ `TObjectPtr<UNetConnection> GameServerConnection;` — `UPROPERTY()` — The actual connection to the backend server.
- L153 _public member_ `TObjectPtr<class ULocalPlayer> Player;` — `UPROPERTY()` — The player used to represent this route in the game systems.
- L156 _public member_ `TArray<UE::MultiServerProxy::Private::FPendingBroadcastRPC> PendingBroadcastRPCs;` — Queue to hold RPCs that will be broadcast to all game servers using BroadcastToAllClientConnectedGameServers().
- L169 _public member_ `mutable EProxyConnectionState State = EProxyConnectionState::Disconnected;` — The state of the route.
- L171 _public member_ `mutable double LastUpdateViewTargetSec;`
- L172 _public member_ `mutable FVector LastViewTargetPos;`

#### struct `FPlayerControllerReassignment`  
`struct FPlayerControllerReassignment`  
_L179-194_
- reflection: `USTRUCT()`
- desc: State associated with the reassignment or migration of a player controller from one game server to another.
- L183 _public member_ `bool bReceivedNoPawnPlayerController = false;`
- L184 _public member_ `bool bReceivedGamePlayerController = false;`
- L186 _public member_ `uint64 PreviousClientHandshakeId = 0;`
- L187 _public member_ `uint64 ClientHandshakeId = 0;`
- L190 _public member_ `TObjectPtr<class ULocalPlayer> PreviousPrimaryPlayer;` — `UPROPERTY()`
- L193 _public member_ `TObjectPtr<class ULocalPlayer> PrimaryPlayer;` — `UPROPERTY()`

#### class `UGameServerNotify`  
`class UGameServerNotify : public UPendingNetGame`  
_L207-234_
- reflection: `UCLASS()`
- inherits: `UPendingNetGame`
- desc: Intercept outgoing connection requests to game servers from the proxy server. Ensure that NMT_Join is sent after receiving NMT_Welcome from a game server. Normally NMT_Join will be sent after a level is loaded but the proxy doesn't currently handle loading levels when connecting to a server. Defaults to the behavior in UPendingNetGame which normally handles all outgoing connections to a game server.
- L213 _public prototype_ `virtual void NotifyAcceptedConnection(UNetConnection* Connection) override;`
- L214 _public prototype_ `virtual EAcceptConnection::Type NotifyAcceptingConnection() override;`
- L215 _public prototype_ `virtual bool NotifyAcceptingChannel(class UChannel* Channel) override;`
- L216 _public prototype_ `virtual void NotifyControlMessage(UNetConnection* GameServerConnection, uint8 MessageType, class FInBunch& Bunch) override;`
- L217 _public prototype_ `virtual class ULocalPlayer* GetFirstGamePlayer();`
- L219 _public prototype_ `void SetProxyNetDriver(TObjectPtr<class UProxyNetDriver> InProxyNetDriver);`
- L220 _public function_ `void SetFlags(UE::Net::EJoinFlags InFlags)`
- L223 _public prototype_ `void SetFirstPlayer(TObjectPtr<class ULocalPlayer> Player);` — Set the value to be returned by GetFirstGamePlayer().
- L227 _private member_ `UE::Net::EJoinFlags Flags;`
- L230 _private member_ `TObjectPtr<class ULocalPlayer> FirstPlayer;` — `UPROPERTY()`
- L233 _private member_ `TObjectPtr<class UProxyNetDriver> ProxyNetDriver;` — `UPROPERTY()`

#### class `UProxyListenerNotify`  
`class UProxyListenerNotify : public UObject, public FNetworkNotify`  
_L247-271_
- reflection: `UCLASS()`
- inherits: `UObject,FNetworkNotify`
- desc: Intecept incoming from clients to the proxy server. Intercept NMT_Join when a client connects to the proxy, establishes a connection to a game server and performs the logic required to associate these two connections and forward state replicated from the game server to the client. Defaults to the behavior in UWorld which normally handles all incoming game server connections.
- L254 _public prototype_ `void SetProxyNetDriver(TObjectPtr<class UProxyNetDriver> InProxyNetDriver);`
- L256 _public prototype_ `virtual void NotifyAcceptedConnection(UNetConnection* Connection) override;`
- L257 _public prototype_ `virtual EAcceptConnection::Type NotifyAcceptingConnection() override;`
- L258 _public prototype_ `virtual bool NotifyAcceptingChannel(class UChannel* Channel) override;`
- L259 _public prototype_ `virtual void NotifyControlMessage(UNetConnection* ProxyConnection, uint8 MessageType, class FInBunch& Bunch) override;`
- L264 _private prototype_ `void ConnectToGameServer(UNetConnection* ProxyConnection, int32 GameServerConnectionStateIndex, FGameServerConnectionState* GameServerConnectionState, UE::Net::EJoinFlags Flags);` — Start connecting an incoming proxy connection to a game server.
- L270 _private member_ `TObjectPtr<class UProxyNetDriver> ProxyNetDriver;` — `UPROPERTY()`

#### class `UProxyBackendNetConnection`  
`class UProxyBackendNetConnection : public UIpConnection`  
_L277-284_
- reflection: `UCLASS()`
- inherits: `UIpConnection`
- desc: A network connection used by UProxyBackendNetDriver.
- L283 _public prototype_ `virtual void HandleClientPlayer(APlayerController* PC, UNetConnection* NetConnection);`

#### class `UProxyBackendChildNetConnection`  
`class UProxyBackendChildNetConnection : public UChildConnection`  
_L290-301_
- reflection: `UCLASS()`
- inherits: `UChildConnection`
- desc: A child network connection used by UProxyBackendNetDriver.
- L296 _public prototype_ `virtual void HandleClientPlayer(APlayerController* PC, UNetConnection* NetConnection);`
- L300 _protected prototype_ `virtual void RemoveLocalPlayer(UGameInstance* GameInstance, ULocalPlayer* LocalPlayer) override;`

#### class `UProxyBackendNetDriver`  
`class UProxyBackendNetDriver : public UIpNetDriver`  
_L307-339_
- reflection: `UCLASS()`
- inherits: `UIpNetDriver`
- desc: A driver that is used by UProxyNetDriver to connect to backend game servers.
- L313 _public prototype_ `void SetProxyNetDriver(TObjectPtr<UProxyNetDriver> InParentNetDriver);`
- L314 _public prototype_ `TObjectPtr<UProxyNetDriver> GetProxyNetDriver();`
- L316 _public prototype_ `virtual bool InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error);`
- L317 _public prototype_ `virtual void Shutdown() override;`
- L318 _public prototype_ `virtual void ForwardRemoteFunction(UObject* RootObject, UObject* SubObject, UFunction* Function, void* Parms) override;`
- L319 _public prototype_ `virtual bool ShouldSkipRepNotifies() const override;`
- L320 _public prototype_ `virtual bool ShouldClientDestroyActor(AActor* Actor, EChannelCloseReason CloseReason) const;`
- L322 _public prototype_ `virtual bool ShouldUpdateStats() const override;`
- L323 _public prototype_ `virtual bool ShouldRegisterMetricsDatabaseListeners() const override;`
- L327 _private prototype_ `void OnIrisRootObjectPostInit(UE::Net::FNetRefHandle RootHandle, UObject* RootObject, UE::Net::FNetObjectFactoryId FactoryId);`
- L328 _private prototype_ `void OnIrisRootObjectDetached(UE::Net::FNetRefHandle RootHandle, UObject* RootObject, UE::Net::EDetachReason Reason);`
- L329 _private prototype_ `void OnIrisSubObjectPostInit(UE::Net::FNetRefHandle SubObjectHandle, UObject* SubObject, UE::Net::FNetRefHandle RootObjectHandle, UObject* RootObject, UE::Net::FNetObjectFactoryId FactoryId);`
- L330 _private prototype_ `void OnIrisSubObjectDetached(UE::Net::FNetRefHandle SubObjectHandle, UObject* SubObject, UE::Net::FNetRefHandle RootObjectHandle, UObject* RootObject, UE::Net::EDetachReason Reason);`
- L333 _private member_ `TObjectPtr<UProxyNetDriver> ProxyNetDriver;` — `UPROPERTY()`
- L335 _private member_ `FDelegateHandle OnIrisRootObjectPostInitHandle;`
- L336 _private member_ `FDelegateHandle OnIrisRootObjectDetachedHandle;`
- L337 _private member_ `FDelegateHandle OnIrisSubObjectPostInitHandle;`
- L338 _private member_ `FDelegateHandle OnIrisSubObjectDetachedHandle;`

#### class `UProxyNetDriver`  
`class UProxyNetDriver : public UIpNetDriver`  
_L369-575_
- reflection: `UCLASS()`
- inherits: `UIpNetDriver`
- desc: A network proxy that intercepts and forwards UE game network connections to backend game servers. The proxy externally behaves the same as a normal game server when game clients connect and as a normal client when connecting to game servers. This means that there is no need for the clients and game servers that the proxy is connected to have any special proxy-aware configuration. Internally, the proxy is made up of an instance of UProxyNetDriver that listens for incoming connections, known as proxy connections, and an instance of UProxyBackendNetDriver for each connection to a backend game server. State from the backend servers is replicated into a single, shared UWorld and the listening UProxyNetDriver replicates that state out to proxy connections. All actors replicated to the proxy from remote game servers will have the same role as a client (ROLE_SimulatedProxy or ROLE_AutonomousProxy) and will be replicated as-is to the proxy client. When a proxy connection (UNetConnection) is opened in UProxyNetDriver it opens a game server connection (UNetConnection) to each registered backend server. For each proxy connection one of the game servers are considered the primary game server. This is the game server that spawns the proxy client's pawn, player controller, receive RPCs from the proxy connection, and send RPCs to the proxy connection. The other game servers are considered non-primary game servers and only replicate state relevant to that connection to the proxy. When connect
- L376 _public prototype_ `void RegisterGameServer(const FURL& GameServerURL);` — Register a game server.
- L379 _public prototype_ `void SetCyclePrimaryGameServer(bool bEnable);` — Cycle through game servers as primary game servers each time a client connects to the proxy.
- L382 _public prototype_ `bool IsConnectedToAllGameServers() const;` — Return true if all registered servers are connected.
- L385 _public prototype_ `int32 GetGameServerConnectionCount() const;` — Enumerate through all outgoing connections to game servers.
- L386 _public prototype_ `FGameServerConnectionState* GetGameServerConnection(int32 Index);`
- L389 _public prototype_ `int32 GetGameServerChildConnectionCount() const;` — Return the number of child connections to the game servers.
- L392 _public prototype_ `virtual bool InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error) override;` — UNetDriver interface function.
- L393 _public prototype_ `virtual void SetupNetworkMetrics() override;`
- L394 _public prototype_ `virtual bool InitConnect(class FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error) override;`
- L395 _public prototype_ `virtual void ForwardRemoteFunction(UObject* RootObject, UObject* SubObject, UFunction* Function, void* Parms) override;`
- L396 _public prototype_ `virtual bool ShouldReplicateFunction(AActor* Actor, UFunction* Function) const override;`
- L397 _public prototype_ `virtual void AddNetworkActor(AActor* Actor) override;`
- L398 _public prototype_ `virtual void RemoveNetworkActor(AActor* Actor) override;`
- L399 _public prototype_ `virtual bool ShouldCallRemoteFunction(UObject* Object, UFunction* Function, const FReplicationFlags& RepFlags) const;`
- L400 _public prototype_ `virtual int32 ServerReplicateActors(float DeltaSeconds) override;`
- L401 _public prototype_ `virtual bool CanDowngradeActorRole(UNetConnection* ProxyConnection, AActor* Actor) const override;`
- L402 _public prototype_ `virtual void Shutdown() override;`
- L403 _public prototype_ `virtual void FinishDestroy() override;`
- L404 _public prototype_ `virtual void TickFlush(float DeltaSeconds) override;`
- L407 _public prototype_ `int32 GetNextGameServerClientId();` — Get the next identifier for outgoing connections to game servers.
- L410 _public prototype_ `uint32 GetNextClientHandshakeId();` — Get the next connection handshake id.
- L413 _public prototype_ `void GameServerAssignPlayerController(UNetConnection* ChildGameServerConnection, UNetConnection* ParentGameServerConnection, APlayerController* PlayerController);` — Called when the player controller associated with a connection is changed (either at the end of initial connection handshake, or if changed after successfully connected).
- L416 _public prototype_ `TSharedPtr<FNetGUIDCache> GetSharedBackendNetGuidCache();` — Return a pointer to the shared NetGUID cache used by backend network connections.
- L419 _public prototype_ `void BroadcastToAllClientConnectedGameServers(const ULocalPlayer* Player, const UFunction* Function, const void* Parms, const UObject* SubObject);` — Forward an RPC to all primary and non-primary game servers for a proxy client connection using PlayerToProxyConnection.
- L422 _public prototype_ `UNetConnection* GetProxyConnectionForPlayer(const ULocalPlayer* Player) const;` — Return the proxy connection for a local player, or nullptr if not found.
- L425 _public prototype_ `void HandleClosedProxyConnection(UNetConnection* ProxyConnection);` — Called when an incoming proxy connection has been closed and closes connections to backend servers.
- L428 _public prototype_ `void FlushSplitJoinRequests(FGameServerConnectionState* GameServerConnectionState);` — Send any split join requests that have been queued up to the game server.
- L431 _public prototype_ `void FlushPendingBroadcastRPCs(FMultiServerProxyInternalConnectionRoute* Route);` — Flush any broadcast RPCs that were queued while a route was not yet connected.
- L450 _private prototype_ `void CloseAndCleanUpConnectionRoute(const FMultiServerProxyInternalConnectionRoute* Route);` — Close a route's connection and perform any clean up.
- L453 _private prototype_ `void FinalizeGameServerConnection(FMultiServerProxyInternalConnectionRoute* Route, UNetConnection* GameServerConnection, APlayerController* PlayerController);` — Called when the connection handshake to a game server is completed (i.e. the first player controller has been replicated on that connection).
- L456 _private prototype_ `void ReassignPlayerController(const FMultiServerProxyInternalConnectionRoute* Route, UNetConnection* GameServerConnection, APlayerController* PlayerController);` — Called when a player controller is switching on the remote game server (i.e. during migration).
- L458 _private prototype_ `void ProcessConnectionState_Connecting(FMultiServerProxyInternalConnectionRoute* Route, UNetConnection* GameServerConnection, APlayerController* PlayerController);`
- L459 _private prototype_ `void ProcessConnectionState_ConnectingPrimary(FMultiServerProxyInternalConnectionRoute* Route, UNetConnection* GameServerConnection, APlayerController* PlayerController);`
- L460 _private prototype_ `void ProcessConnectionState_Connected(const FMultiServerProxyInternalConnectionRoute* Route, UNetConnection* GameServerConnection, APlayerController* PlayerController);`
- L461 _private prototype_ `void ProcessConnectionState_ConnectedPrimary(const FMultiServerProxyInternalConnectionRoute* Route, UNetConnection* GameServerConnection, APlayerController* PlayerController);`
- L462 _private prototype_ `void ProcessConnectionState_Reassign(const FMultiServerProxyInternalConnectionRoute* Route, UNetConnection* GameServerConnection, APlayerController* PlayerController);`
- L463 _private prototype_ `void ProcessConnectionState_PendingClose(FMultiServerProxyInternalConnectionRoute* Route, UNetConnection* GameServerConnection, APlayerController* PlayerController);`
- L465 _private prototype_ `void UpdateProxyNetworkMetrics();`
- L466 _private prototype_ `void AggregateBackendNetDriverMetrics();`
- L467 _private prototype_ `void ResetProxyNetworkMetrics();`
- L470 _private prototype_ `void PreGarbageCollect();` — Clean up any internal data structures that hold weak object references that are now invalid.
- L471 _private prototype_ `void PostGarbageCollect();`
- L479 _private prototype_ `void RedirectRPCToProxyConnection(AActor* Actor, UFunction* Function, TFunction<void(UNetConnection*)> RPCSendingFunction);` — Send an RPC correct proxy connection based on the actor's owner and local player. This function won't perform logic to send the RPC; that logic is expected to be called as part of the function argument RPCSendingFunction. RPCSendingFunction will be provided the derived proxy connection, if one can be found, as an argument.
- L482 _private prototype_ `void SetProxyConnectionAsOwner(UNetConnection* ProxyConnection, const AActor* Actor);` — (Iris only) Configure the connection to own this particular actor (required for replication conditionals and internal filtering logic).
- L489 _private prototype_ `void ReceivedReassignedGamePlayerController(const FMultiServerProxyInternalConnectionRoute* Route);` — Receive a new game player controller for an already open route. This route becomes a route to a primary game server.
- L496 _private prototype_ `void ReceivedReassignedNoPawnPlayerController(const FMultiServerProxyInternalConnectionRoute* Route);` — Receive a new no-pawn player controller for an already open route. This route stops being a route to a primary game server.
- L499 _private prototype_ `void FinalizePlayerControllerReassignment(UNetConnection* ProxyConnection, const FPlayerControllerReassignment& Migration);` — Perform any logic that depends on the order of game and no pawn player controllers being re-assigned.
- L502 _private prototype_ `void DisableActorLogicAndGameCode();` — Set all of the configuration options that disable executing actor functionality or game specific code.
- L505 _private prototype_ `void PrepareStateForRelevancy();` — Prepare state on the proxy to be used for relevancy when replicating to proxy connections.
- L508 _private prototype_ `void UpdateLocalViewTarget(const APlayerController* PrimaryPlayerController);` — Update the view target on player controllers used by proxy client connections.
- L511 _private prototype_ `void SetRemoteViewTarget(const class ANoPawnPlayerController* PlayerController, FVector ViewTargetPos);` — Set the view target on no pawn connections to the game server.
- L514 _private prototype_ `UNetConnection* GetProxyConnectionFromPrimaryPlayer(ULocalPlayer* Player);` — Return a proxy connection from a primary player (a player on a primary game server).
- L517 _private prototype_ `const FMultiServerProxyInternalConnectionRoute* GetRouteWithPlayerController(const APlayerController* PlayerController);` — Returns the internal route that uses a player controller.
- L527 _private member_ `TMap<uint32, FMultiServerProxyInternalConnectionRoute> InternalRoutes;` — `UPROPERTY()` — Map client handshake ids to a route data structure. The size of this map is (m*n), where m is the number of proxy connections and n is the number of game servers. For this reason enumerating of this map should be avoided and rather use the functions GetRouteWithPlayerController(), GetRouteWithClientHandshakeId(), and other internal map data structures.
- L531 _private member_ `TMap<TObjectPtr<class ULocalPlayer>, TObjectPtr<const APlayerController>> PlayerToPrimaryGameServerPlayerController;` — `UPROPERTY()` — Map a player to it's primary game server player controller.
- L534 _private member_ `TMap<TObjectKey<class ULocalPlayer>, TObjectPtr<UNetConnection>> PlayerToProxyConnection;` — Map a local player to it's proxy net connection. Multiple players will point to the same proxy net connection.
- L536 _private member_ `FDelegateHandle ProxyPostGarbageCollectHandle;`
- L537 _private member_ `FDelegateHandle ProxyPreGarbageCollectHandle;`
- L540 _private member_ `TMap<TObjectPtr<UNetConnection>, FPlayerControllerReassignment> DeferredReassignment;` — `UPROPERTY()`
- L544 _private member_ `TMap<TObjectPtr<UNetConnection>, TObjectPtr<const APlayerController>> ProxyConnectionToPrimaryGameServerPlayerController;` — `UPROPERTY()` — Map a proxy connection to the primary game server player controller.
- L548 _private member_ `TArray<FGameServerConnectionState> GameServerConnections;` — `UPROPERTY()` — Net drivers and associated state used to connect to backend game servers.
- L552 _private member_ `TObjectPtr<UProxyListenerNotify> ProxyListenerNotify;` — `UPROPERTY()` — Proxy listener handshake logic.
- L555 _private member_ `TSharedPtr<FNetGUIDCache> SharedBackendNetGuidCache;` — A single NetGUID cache used by all netdrivers used to connect to backend servers.
- L557 _private member_ `int32 NextGameServerClientId = 0;`
- L559 _private member_ `uint32 NextClientHandshakeId = 123;`
- L562 _private member_ `int32 PrimaryGameServerForNextClient = 0;` — The primary game server to use for the next primary game client.
- L565 _private member_ `bool bCyclePrimaryGameServer = false;` — After a client connects to the proxy increment the value of PrimaryGameServerForNextClient.
- L568 _private member_ `bool bRandomizePrimaryGameServerForNextClient = false;` — As a client connects to the proxy, randomize PrimaryGameServerForNextClient to one of the known game servers.
- L571 _private member_ `TSet<FSoftObjectPath> BroadcastToAllGameServersFunctions;` — RPCs from the client that must be forwarded to all game servers (not just the primary).
- L574 _private member_ `TSet<FSoftObjectPath> AllowListedProxyFunctions;` — RPCs that are allow-listed to be executed on the proxy when forwarding (both client->server and server->client).

#### class `UProxyNetConnection`  
`class UProxyNetConnection : public UIpConnection`  
_L581-588_
- reflection: `UCLASS()`
- inherits: `UIpConnection`
- desc: A network connection used by UProxyNetDriver.
- L587 _public prototype_ `virtual void CleanUp() override;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MultiServerProxy` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::MultiServerProxy`)

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Public/MultiServerReplicationModule.h` (Public)


#### class `FMultiServerReplicationModule`  
`class FMultiServerReplicationModule : public IModuleInterface`  
_L8-44_
- inherits: `IModuleInterface`
- desc: See MultiServerNode for more details about multi-server networking as a whole.
- L12 _public function_ `FMultiServerReplicationModule()`
- L13 _public function_ `virtual ~FMultiServerReplicationModule()`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L17 _public function_ `virtual void ShutdownModule() override`
- L18 _public function_ `virtual bool SupportsDynamicReloading() override`
- L19 _public function_ `virtual bool SupportsAutomaticShutdown() override`
- L26 _public prototype_ `static bool IsRunningAsProxy();` — Return true if the process is running as a proxy. This function should *NOT* be used in code that is intended to run from within PIE.
- L43 _private prototype_ `void SetupProxy();` — Configures a game server to act as a proxy. A game server is configured as a proxy when the cvar `net.proxy.Enabled` is set to `true` at start up. These are the methods in which code on a game server can determine if it's running as a proxy: * UReplicationSystem::GetProxyType() or UNetDriver::GetProxyType() * FMultiServerReplicationModule::IsRunningAsProxy() * Read the value of the cvar `net.proxy.Enabled`. The preferred method is to use `GetProxyType()` which is world-scoped, and only use `IsRunningAsProxy()` or reading the cvar directly when `GetProxyType()` is unavailable (e.g. before the driver has been initialized).

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Public/MultiServerReplicationTypes.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMultiServerReplication, Log, All);`

### `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Public/MultiServerTransport.h` (Public)


#### class `UMultiServerTransportEndpoint`  
`class UMultiServerTransportEndpoint : public UObject`  
_L19-38_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This is the base class for MultiServerTransport endpoints. You are meant to derive from this and put your RPCs in the derived class
- L24 _private member_ `int32 PeerIndex = -1;` — this indexes into the internal FMultiServerTransport PeerStates array
- L25 _private member_ `FMultiServerTransport* Transport = nullptr;`
- L30 _public prototype_ `FString GetLocalPeerId() const;`
- L31 _public prototype_ `FString GetRemotePeerId() const;`
- L33 _public prototype_ `UWorld* GetWorld() const;`
- L36 _public prototype_ `virtual int32 GetFunctionCallspace( UFunction* Function, FFrame* Stack ) override;` — UObject overrides to redirect RPCs
- L37 _public prototype_ `virtual bool CallRemoteFunction( UFunction* Function, void* Parms, struct FOutParmRec* OutParms, FFrame* Stack ) override;`
- L222 _function_ `inline UWorld* UMultiServerTransportEndpoint::GetWorld() const`

#### class `FMultiServerTransport`  
`class FMultiServerTransport : public FRunnable, public FGCObject`  
_L40-214_
- inherits: `FRunnable,FGCObject`
- L45 _public prototype_ `FMultiServerTransport( const FString& SharedSessionKeySecretString, const FString& LocalPeerId, uint16 ListenPort, const FString& LocalServerAddress, const TArray<FString>& AllServerAddresses, TSubclassOf<UMultiServerTransportEndpoint> EndpointClass);`
- L53 _public prototype_ `~FMultiServerTransport();`
- L56 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L57 _public prototype_ `virtual FString GetReferencerName() const override;`
- L60 _public prototype_ `virtual uint32 Run() override;` — FRunnable interface
- L62 _public function_ `virtual void Stop() override`
- L68 _public function_ `int32 GetNumExpectedConnections() const`
- L74 _public function_ `void SetWorld(UWorld* InWorld)`
- L79 _public function_ `UWorld* GetWorld() const`
- L84 _public function_ `FString GetLocalPeerId() const`
- L92 _public prototype_ `bool GameThreadTick();` — Processes incoming RPCs on all peer endpoints. Returns true if the transport is still operational. Returns false if a peer disconnected (transport is now dormant).
- L94 _public prototype_ `UMultiServerTransportEndpoint* GetEndpointForRemotePeer(FStringView RemotePeerId) const;`
- L97 _public prototype_ `template<class T> T* GetEndpointForRemotePeer(FStringView RemotePeerId) const;`
- L99 _public prototype_ `void ForEachEndpoint(TFunctionRef<void(UMultiServerTransportEndpoint*)> Operation) const;`
- L102 _private member_ `static constexpr uint32 MagicNumber = 0x5cbdc807u;`
- L103 _private member_ `static constexpr uint32 NonceSize = 12;`
- L104 _private member_ `static constexpr uint32 SharedSessionKeySize = 32;`
- L105 _private member_ `static constexpr uint32 HMACHashSize = 20;` — SHA-1 output
- L106 _private member_ `static constexpr uint32 AuthMessageSize = NonceSize + HMACHashSize;`
- L107 _private member_ `static constexpr double ConnectTimeout = 30.0;` — 30-second timeout
- L187 _private prototype_ `void InitiateOutboundConnections();`
- L188 _private prototype_ `void CreatePendingPeerState(FUniqueSocket&& PeerSocket);`
- L189 _private prototype_ `void CreatePeerState(FUniqueSocket&& PeerSocket, const uint8* AuthMessageBytes, uint32 AuthMessageBytesSize);`
- L190 _private prototype_ `void SendToPeer(int32 PeerIndex, TArray<uint8>&& Message);`
- L191 _private prototype_ `void SignalThreadWake();`
- L193 _private member_ `uint8 SharedSessionKeySecret[SharedSessionKeySize];`
- L194 _private member_ `UWorld* World = nullptr;`
- L196 _private member_ `TArray<TUniquePtr<FPendingPeer>> PendingPeerStates;`
- L197 _private member_ `TArray<TUniquePtr<FPeer>> PeerStates;`
- L198 _private member_ `int32 ConnectedEndpointCount = 0;`
- L200 _private member_ `TAtomic<bool> bIsRunning;`
- L201 _private member_ `TUniquePtr<FRunnableThread> TransportThread;`
- L202 _private member_ `TSpscQueue<bool> AllEndpointsConnectedEventQueue;`
- L204 _private member_ `FUniqueSocket ListenSocket;`
- L208 _private member_ `FUniqueSocket LoopbackSendSocket;` — this is a loopback socket used to signal the transport thread to wake up when the game thread pushes a message to send into the queue
- L209 _private member_ `FUniqueSocket LoopbackRecvSocket;` — this is the endpoint that the net thread reads from
- L211 _private member_ `TArray<FString> AllServerAddresses;`
- L212 _private member_ `int32 LocalPeerIndex = 0;` — our index into AllServerAddresses
- L213 _private member_ `FString LocalPeerId;`
- L217 _function_ `template<class T> T* FMultiServerTransport::GetEndpointForRemotePeer(FStringView RemotePeerId) const`

#### struct `FMultiServerTransport::FPendingPeer`  
`struct FPendingPeer`  
_L109-130_
- L111 _public member_ `double CreationTimeSeconds = 0.0;`
- L112 _public member_ `FUniqueSocket Socket;`
- L114 _public member_ `uint32 MagicNumberBuffer = 0;`
- L115 _public member_ `uint32 MagicNumberOffset = 0;`
- L117 _public member_ `uint8 AuthMessageBuffer[AuthMessageSize];`
- L118 _public member_ `uint32 AuthMessageBufferOffset = 0;`
- L128 _public prototype_ `EPendingPeerTickResult TickPendingPeer(const uint8* SharedSessionKeySecret);`
- L129 _public prototype_ `void HandlePendingPeerRecv();`

#### enum `FMultiServerTransport::FPendingPeer::EPendingPeerTickResult`  
`enum class EPendingPeerTickResult`  
_L120-126_
- L122 _public enumerator_ `StillPending`
- L123 _public enumerator_ `IsInvalid`
- L124 _public enumerator_ `TimedOut`
- L125 _public enumerator_ `PromoteToPeer`

#### struct `FMultiServerTransport::FPeer`  
`struct FPeer`  
_L132-185_
- L134 _public member_ `TObjectPtr<UMultiServerTransportEndpoint> Endpoint;`
- L135 _public member_ `FUniqueSocket Socket;`
- L137 _public member_ `FString RemotePeerId;`
- L141 _public member_ `static const uint32 SendStagingBufferSize = 2*1024*1024;` — this is a fixed size circular buffer of bytes ready to be send out of the socket.
- L142 _public member_ `TUniquePtr<uint8[]> SendStagingBuffer;`
- L143 _public member_ `uint32 SendStagingBufferPutIndex = 0;`
- L144 _public member_ `uint32 SendStagingBufferGetIndex = 0;`
- L151 _public member_ `int32 SendStagingBufferPendingMessageOffset = -1;` — we can be in a state where we haven't fully copied the next message to go out from the message queue into the staging buffer. We try to stage as much as possible, and this offset lets us keep track of how far into the message we have staged so far.
- L154 _public member_ `TSpscQueue<TArray<uint8>> SendMessageQueue;` — send queue
- L157 _public member_ `TSpscQueue<TArray<uint8>> RecvMessageQueue;` — recv queue
- L163 _public member_ `static const uint32 RecvStagingBufferSize = 2*1024*1024;` — Fixed-size receive buffer. The socket reads directly into this buffer, and then we assemble messages out of it. This allows assembling more than one message per socket pump when messages are small.
- L164 _public member_ `TUniquePtr<uint8[]> RecvStagingBuffer;`
- L165 _public member_ `uint32 RecvStagingBufferPutIndex = 0;`
- L166 _public member_ `uint32 RecvStagingBufferGetIndex = 0;`
- L172 _public member_ `TArray<uint8> RecvMessageBuffer;` — Message being assembled from the receive buffer. When Num()==0, we are waiting for a 4-byte size header. When Num()>0, we are filling the body, and RecvMessageBufferOffset tracks how far along we are.
- L173 _public member_ `uint32 RecvMessageBufferOffset = 0;`
- L182 _public prototype_ `void StageOutgoingMessages();`
- L183 _public prototype_ `bool HandlePeerSend();`
- L184 _public prototype_ `EPeerRecvResult HandlePeerRecv();`

#### enum `FMultiServerTransport::FPeer::EPeerRecvResult`  
`enum class EPeerRecvResult`  
_L175-180_
- L177 _public enumerator_ `Ok`
- L178 _public enumerator_ `Disconnected`
- L179 _public enumerator_ `HandshakeReceived`
