# Plugins / DisplayClusterReplication

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterReplication`
- headers: 3; symbols: 56
- symbol kinds: class=2, delegate=1, member=35, prototype=17, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, NetCore, OnlineSubsystem, OnlineSubsystemUtils, Sockets
- PublicDependencyModuleNames: Core, CoreUObject, DisplayCluster, DisplayClusterConfiguration, Engine

### `Plugins/Runtime/nDisplay/Source/DisplayClusterReplication/Private/DisplayClusterNetDriverLog.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterNetDriver, Log, All);` — Module-wide log categories
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterNetDriver, Log, All);` — Module-wide log categories

### `Plugins/Runtime/nDisplay/Source/DisplayClusterReplication/Public/DisplayClusterNetConnection.h` (Public)


#### class `UDisplayClusterNetConnection`  
`class UDisplayClusterNetConnection : public UIpConnection`  
_L19-67_
- reflection: `UCLASS(transient, config = Engine)`
- inherits: `UIpConnection`
- L24 _private prototype_ `virtual void ReceivedPacket(FBitReader& Reader, bool bIsReinjectedPacket = false, bool bDispatchPacket = true) override;`
- L25 _private prototype_ `virtual void SetClientLoginState(const EClientLoginState::Type NewState) override;`
- L30 _public member_ `FString NodeName;` — The name of the node, parsed from node URL address
- L33 _public member_ `FString NodeAddress;` — The ip address of the node, converted to FString from current NetConnection
- L36 _public member_ `uint32 ClientId;` — Cluster client unique identifier, HashString from NetConnection Challenge
- L39 _public member_ `uint32 ClusterId;` — Cluster unique identifier, HashString from node config file path
- L42 _public member_ `uint32 ClusterNodesNum;` — Cluster nodes number
- L45 _public member_ `uint16 NodePort;` — Cluster node port for binary cluster events
- L48 _public member_ `bool bNodeIsPrimary;` — Whether current connection belongs to primary cluster node
- L51 _public member_ `bool bIsClusterConnection;` — Whether current connection belongs to cluster node
- L54 _public member_ `bool bSynchronousMode;` — Whether current connection works in synchronous mode
- L59 _public prototype_ `void ProcessPacket(int32 PacketId);` — Process accumulated packets in the packet queue until PacketId @param PacketId identified of packet
- L63 _protected member_ `TArray<int32> PacketIDs;` — Storage for InPackets map keys, prevents reallocs
- L66 _protected member_ `TSortedMap<int32, FBitReader> InPackets;` — Data associated with each packet id

### `Plugins/Runtime/nDisplay/Source/DisplayClusterReplication/Public/DisplayClusterNetDriver.h` (Public)


#### struct `FDisplayClusterReplicationState`  
`struct FDisplayClusterReplicationState`  
_L28-42_
- desc: Helper structure to cache PriorityActor list for additional replication in order to equalize number of replicated actors among all synced connections
- L31 _public member_ `int32 FinalSortedCount = 0;` — Number of actors that were prioritized
- L34 _public member_ `int32 MaxLastProcessedActor = -1;` — Max processed actor among all synced connections
- L37 _public member_ `FActorPriority* PriorityList = nullptr;` — Cached priority lists
- L38 _public member_ `FActorPriority** PriorityActors = nullptr;`
- L41 _public member_ `TMap<uint32, int32> LastProcessedActors;` — Last processed actor for each sync connection

#### class `UDisplayClusterNetDriver`  
`class UDisplayClusterNetDriver : public UIpNetDriver`  
_L50-151_
- reflection: `UCLASS(transient, config = Engine)`
- inherits: `UIpNetDriver`
- desc: Custom NetDriver for DisplayCluster. Responsible for synchronous application of network packets across display cluster nodes. Results in seamless image when used with Actor replication system.
- L54 _private prototype_ `virtual ~UDisplayClusterNetDriver();`
- L57 _private prototype_ `virtual bool InitListen(FNetworkNotify* InNotify, FURL& ListenURL, bool bReuseAddressAndPort, FString& Error) override;`
- L58 _private prototype_ `virtual void TickDispatch(float DeltaTime) override;`
- L59 _private prototype_ `virtual void TickFlush(float DeltaSeconds) override;`
- L66 _public prototype_ `void HandleEvent(FDisplayClusterClusterEventBinary const& InEvent);` — Performs Cluster Event handling: sync mode start and packet processing on client side @param Binary event to handle
- L72 _public prototype_ `void AddNodeConnection(UDisplayClusterNetConnection* NetConnection);` — Adds connection to nDisplay connection TSet @param NetConnection connection to add
- L78 _public prototype_ `void RemoveNodeConnection(UDisplayClusterNetConnection* NetConnection);` — Removes connection from nDisplay connection TSet and from synchronized connections @param NetConnection connection to remove
- L82 _protected member_ `TMap<int32, TDeque<int32>> OutPacketsQueues;` — Contains queue of non-processed packets for specific connection (key - connectionID, value - packetID)
- L85 _protected member_ `TMap<int32, int32> ReadyOutPackets;` — Holds packets that are ready for replication (key - connectionID, value - packetID)
- L88 _protected member_ `TMap<uint32, int32> PacketsParams;` — Holds ready packets for each client. Member of the class to prevent runtime reallocations.
- L91 _protected member_ `TArray<uint8> ClusterEventData;` — Binary event data. Member of the class to prevent runtime reallocations
- L94 _protected member_ `TSet<UDisplayClusterNetConnection*> NodeConnections;` — nDisplay node connections
- L97 _protected member_ `TSet<UDisplayClusterNetConnection*> PrimaryNodeConnections;` — nDisplay Primary node connections
- L100 _protected member_ `TMap<uint32, TArray<UDisplayClusterNetConnection*>> ClusterConnections;` — nDisplay Node connections which corresponds to specific cluster
- L103 _protected member_ `TSet<UDisplayClusterNetConnection*> SyncConnections;` — nDisplay node connections that participate in synchronous replication
- L106 _protected member_ `TArray<FNetViewer> PivotNodeConnectionViewers;` — ConnectionViewers for Pivot node (primary node connection)
- L109 _protected member_ `TUniquePtr<FDisplayClusterNetDriverHelper> ClusterNetworkDriverHelper;` — NetDriver helper for Display Cluster Events
- L112 _protected member_ `FDisplayClusterReplicationState ClusterReplicationState;` — Stores replication state to produce additional replication in order to equalize number of actors for each sync connection
- L115 _protected member_ `FOnClusterEventBinaryListener EventBinaryListener;` — Binary event listener
- L118 _protected member_ `bool bClusterHasConnected;` — True if cluster has connected
- L121 _protected member_ `bool bLastBunchWasAcked;` — Used to control state of acked packets queue
- L124 _protected member_ `bool bConnectionViewersAreReady;` — Checks if connections viewers for Primary node were formed
- L127 _protected member_ `int32 ListenClusterId;` — ClusterId for listen Server
- L130 _protected member_ `int32 ListenClusterNodesNum;` — Num cluster nodes for listen Server
- L133 _protected member_ `inline static const int NodeSyncEvent = GetTypeHash(FStringView(TEXT("nDCRN` — Cluster event id, used to start synchrosonus packets processing
- L136 _protected member_ `inline static const int PacketSyncEvent = GetTypeHash(FStringView(TEXT("nDCRP` — Cluster event id, used to identify packet data blob for sync
- L140 _protected prototype_ `void PreListUpdate(ConsiderListUpdateParams const& UpdateParams, int& OutUpdated, const TArray<FNetworkObjectInfo*>& ConsiderList);`
- L141 _protected prototype_ `void PostListUpdate(ConsiderListUpdateParams const& UpdateParams, int& OutUpdated, const TArray<FNetworkObjectInfo*>& ConsiderList);`
- L142 _protected prototype_ `void ListUpdate(ConsiderListUpdateParams const& UpdateParams, int& OutUpdated, const TArray<FNetworkObjectInfo*>& ConsiderList);`
- L146 _protected prototype_ `bool NotifyClusterAsReadyForSync(int32 ClusterId);` — Helper functions used by server side to notify cluster via cluster event that it is are ready for sync
- L149 _protected prototype_ `void GenerateClusterCommandsEvent(FDisplayClusterClusterEventBinary& NetworkDriverSyncEvent, int32 EventId);` — Helper functions for parameters serialization into binary event data
- L150 _protected prototype_ `void GenerateClusterCommandsEvent(FDisplayClusterClusterEventBinary& NetworkDriverSyncEvent, int32 EventId, const TMap<uint32, int32>& Parameters);`
