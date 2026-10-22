# Plugins / StormSyncTransportServer

- module root: `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportServer`
- headers: 8; symbols: 161
- symbol kinds: class=7, delegate=2, enum=1, enumerator=2, function=7, member=49, prototype=87, struct=5, typedef=1
- PrivateDependencyModuleNames: Engine, Json, JsonUtilities, Networking, Slate, Sockets, StormSyncCore, StormSyncTransportCore
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportServer/Private/ServiceDiscovery/StormSyncDiscoveryManager.h` (Private)


#### struct `FStormSyncConnectedMessageBusAddress`  
`struct FStormSyncConnectedMessageBusAddress`  
_L12-31_
- desc: Data holder for an active message bus connection over storm sync bus
- L18 _public member_ `bool bIsValid = false;` — Updated each time connection becomes active or inactive and reflects whether elapsed time since LastActivityTime exceeded the heartbeat timeout configured in Storm Sync Transport Settings.
- L21 _public member_ `double LastActivityTime = 0.0;` — Represents the time of last activity. Updated on connection and on each incoming heartbeat message
- L24 _public member_ `bool bIsServerRunning = false;` — Represents remote server local endpoint status. Whether it is currently running and able to receive incoming connections
- L27 _public member_ `bool bReceivedConnectionInfo = false;` — Indicate if a connection info has been received for this connection.
- L30 _public prototype_ `FStormSyncConnectedMessageBusAddress() = default;` — Default constructor

#### struct `FStormSyncDelegateItem`  
`struct FStormSyncDelegateItem`  
_L41-70_
- desc: Data holder for delegate message queue. Holds the type of delegate to broadcast, message address and state. Introduced to prevent firing off delegate within a critical section in DiscoverManager Run(). Instead, it's now building up a queue of delegates to fire off when stepping out critical section path.
- L51 _public member_ `EDelegateType DelegateType;` — Which type of event to trigger
- L54 _public member_ `FMessageAddress Address;` — Message address of the remote connection
- L61 _public member_ `EStormSyncConnectedDeviceState State;` — Hold the state of the connection to broadcast with StateChanges (either responsive or unresponsive) Only relevant with StateChange type.
- L64 _public function_ `FStormSyncDelegateItem(const EDelegateType InDelegateType, const FMessageAddress& InAddress, const EStormSyncConnectedDeviceState InState) : DelegateType(InDelegateType) , Address(InAddress) , State(InState)` — Default constructor

#### enum `FStormSyncDelegateItem::EDelegateType`  
`enum EDelegateType`  
_L44-48_
- desc: Simple enum to list possible types of delegate handled by the queue
- L46 _public enumerator_ `StateChange`
- L47 _public enumerator_ `Disconnection`

#### class `FStormSyncDiscoveryManager`  
`class FStormSyncDiscoveryManager : public FRunnable`  
_L73-164_
- inherits: `FRunnable`
- desc: A class to asynchronously discover message bus sources.
- L76 _public prototype_ `FStormSyncDiscoveryManager(double InHeartbeatTimeout, double InInactiveSourceTimeout, float InTickInterval, bool bInEnableDiscoveryPeriodicPublish);`
- L77 _public prototype_ `~FStormSyncDiscoveryManager();`
- L80 _public prototype_ `virtual uint32 Run() override;`
- L81 _public prototype_ `virtual void Stop() override;`
- L85 _public prototype_ `void PublishConnectMessage();` — Broadcasts / Publish a FStormSyncTransportConnectMessage over the network
- L87 _public prototype_ `void SendWakeUp();`
- L90 _public prototype_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> GetMessageEndpoint() const;` — Returns the underlying endpoint so that outside code could send message directly to it (w/o relying on publish)
- L94 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the message endpoint.
- L97 _private member_ `std::atomic<bool> bRunning;` — Thread safe bool for stopping the thread
- L100 _private member_ `FRunnableThread* Thread;` — For the thread
- L107 _private member_ `TMap<FMessageAddress, FStormSyncConnectedMessageBusAddress> ConnectedAddresses;` — Map of currently connected message bus recipients. Key is the message address, value is a FStormSyncConnectedMessageBusAddress with info like last active time and status.
- L110 _private member_ `FCriticalSection ConnectionLastActiveSection;` — Critical section to allow for ThreadSafe updating of the connection time
- L113 _private member_ `double DefaultHeartbeatTimeout;` — Cached setting for MessageBusHeartbeatTimeout
- L116 _private member_ `double DefaultDeadSourceTimeout;` — Cached setting for MessageBusTimeBeforeRemovingInactiveSource
- L119 _private member_ `float DefaultTickInterval;` — Cached setting for DiscoveryManagerTickInterval
- L122 _private member_ `bool bEnableDiscoveryPeriodicPublish;` — Cached setting for bEnableDiscoveryPeriodicPublish
- L125 _private member_ `double LastPublishTime = 0.0;` — Represents the time of last connect message publish. Only relevant if periodic publish is enabled (bEnableDiscoveryPeriodicPublish true)
- L131 _private prototype_ `static void BroadcastCoreDelegatesFromQueue(const TArray<FStormSyncDelegateItem>& InDelegateQueue);` — Goes through the delegate queue and broadcast appropriate core delegate to notify outside code of any changes in service discovery.
- L134 _private prototype_ `void HandleConnectMessage(const FStormSyncTransportConnectMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& MessageContext);` — Callback handler to receive FStormSyncTransportConnectMessage messages
- L136 _private prototype_ `void HandleWakeupMessage(const FStormSyncTransportWakeupRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& MessageContext);`
- L138 _private function_ `bool IsConnectionRegistered(const FMessageAddress& InMessageAddress)`
- L150 _private prototype_ `void RegisterConnection(const FMessageAddress& InMessageAddress, bool bInIsServerRunning);` — Handles an incoming connect message by registering a new connection internally (adding to ConnectedAddresses), starting heartbeats for this recipient and sending back a connect message to original sender. You must ensure connection is not already registered before calling this method.
- L153 _private prototype_ `void HandleHeartbeatMessage(const FStormSyncTransportHeartbeatMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& MessageContext);` — Callback handler to receive FStormSyncTransportHeartbeatMessage messages
- L156 _private prototype_ `void UpdateConnectionLastActive(const FMessageAddress& InAddress);` — ThreadSafe update of the last active time
- L163 _private prototype_ `bool UpdateServerStatus(const FMessageAddress& InAddress, const bool bIsServerRunning);` — ThreadSafe update of the server status for remote address. Returns whether server running state changed since last heartbeat, and whether server status change event should be broadcast.

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportServer/Private/ServiceDiscovery/StormSyncHeartbeatEmitter.h` (Private)


#### class `FStormSyncHeartbeatEmitter`  
`class FStormSyncHeartbeatEmitter : public FRunnable`  
_L20-72_
- inherits: `FRunnable`
- desc: Heavily based on FLiveLinkHeartbeatEmitter Sends out heartbeat signals at the rate defined by StormSyncTransportSettings::MessageBusHeartbeatFrequency to all recipients. Recipients for the heartbeat can be added by calling StartHeartbeat(). On the first call to StartHeartbeat a thread is spawned that keeps sending the heartbeat to everyone. The heartbeats and the sender thread can be stopped by calling Exit().
- L23 _public prototype_ `FStormSyncHeartbeatEmitter();`
- L30 _public prototype_ `void StartHeartbeat(const FMessageAddress& RecipientAddress, const TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe>& MessageEndpoint);` — Start sending a heartbeat to the specified Recipient by using the given MessageEndpoint. @note This will spawn a new thread when first called. @note It is assumed that each source that sends out heartbeats has its own MessageEndpoint.
- L35 _public prototype_ `void StopHeartbeat(const FMessageAddress& RecipientAddress, const TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe>& MessageEndpoint);` — Stop sending a heartbeat to the specified Recipient.
- L38 _public prototype_ `virtual uint32 Run() override;`
- L39 _public prototype_ `virtual void Exit() override;`
- L56 _private member_ `mutable FCriticalSection CriticalSection;` — Critical section for heartbeat recipients access
- L59 _private member_ `TArray<FHeartbeatRecipient> HeartbeatRecipients;` — List of registered recipients for heartbeat messages. Added and removed respectively with StartHeartbeat / StopHeartbeat
- L62 _private member_ `std::atomic<bool> bIsRunning;` — Whether this runnable should continue running
- L65 _private member_ `float HeartbeatFrequencyInMs;` — Cached heartbeat frequency (tied to Storm Sync Transport Settings MessageBusHeartbeatFrequency) to send heartbeats at a fixed interval
- L68 _private member_ `FEvent* HeartbeatEvent;` — Waitable event for heartbeats
- L71 _private member_ `TUniquePtr<FRunnableThread> Thread;` — Unique pointer to our thread, first started on the first StartHeartbeat

#### struct `FStormSyncHeartbeatEmitter::FHeartbeatRecipient`  
`struct FHeartbeatRecipient`  
_L44-53_
- desc: Data holder for a remote heartbeat recipient
- L47 _public member_ `TWeakPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Weak pointer to the message endpoint for this recipient. Used to send heartbeats at a regular interval to the connection address
- L50 _public member_ `FMessageAddress ConnectionAddress;` — Message address for the remote recipient
- L52 _public prototype_ `bool operator==(const FHeartbeatRecipient& Other) const;`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportServer/Private/Socket/StormSyncTransportTcpServer.h` (Private)


#### struct `FClientConnection`  
`struct FClientConnection`  
_L14-48_
- desc: Holds connection data for a client endpoint
- L17 _public member_ `TSharedPtr<FSocket> Socket;` — Currently connected and active client socket
- L20 _public member_ `uint32 InactiveTimeout;` — Default inactive timeout in seconds for a connect client
- L23 _public member_ `double LastActivityTime;` — Platform time of last activity for a connected client (updated when receiving data)
- L26 _public member_ `uint32 BufferExpectedSize;` — Expected buffer size for a connected client. Used to determine when a buffer has been fully received
- L29 _public member_ `TArray<uint8> ReceiveBuffer;` — Raw buffer received so far for a connected client.
- L37 _public member_ `double BufferStartTime;` — Start time for a connected client. Not used right now, but could be used to display the amount of time it took to transfer the buffer and / or send back this info to clients.
- L40 _public function_ `explicit FClientConnection(const TSharedPtr<FSocket>& Socket) : Socket(Socket) , InactiveTimeout(0) , LastActivityTime(0) , BufferExpectedSize(0) , BufferStartTime(0)` — Default constructor. A connection must have an associated socket.

#### class `FStormSyncTransportTcpServer`  
`class FStormSyncTransportTcpServer : public FRunnable`  
_L57-187_
- inherits: `FRunnable`
- desc: Implements a TCP listener able to receive incoming connections. Heavily based on FSwitchboardListener implementation. Mainly used to receive a raw buffer serialized from StormSyncCoreUtils methods to transfer a content spak.
- L60 _public prototype_ `explicit FStormSyncTransportTcpServer(const FIPv4Address& InEndpointAddress, const uint16 InEndpointPort, const uint32 InInactiveTimeoutSeconds);`
- L64 _public prototype_ `virtual bool Init() override;`
- L65 _public prototype_ `virtual void Stop() override;`
- L66 _public prototype_ `virtual uint32 Run() override;`
- L76 _public prototype_ `DECLARE_EVENT_ThreeParams(FStormSyncServerListener, FOnReceivedBufferEvent, const FIPv4Endpoint&, const TSharedPtr<FSocket>&, const FStormSyncBufferPtr&);` — Event delegate that is executed when a buffer is fully received and ready to be extracted @param Endpoint The first parameter is the client endpoint. @param Socket The second parameter is the client socket. @param Buffer The third parameter is a shared pointer to fully received buffer.
- L79 _public function_ `FOnReceivedBufferEvent& OnReceivedBuffer()` — Event a buffer is fully received and ready to be extracted
- L90 _public prototype_ `bool Tick();` — Main tick handler and throttled by Run(). Dequeues pending connections, parse incoming data and cleans up disconnected clients. Returns false if RequestEngineExit was called.
- L99 _public prototype_ `bool StartListening();` — Creates a new FTcpListener from configured Endpoint. Must be called (once) from outside code. @return true if we were able to create the listener
- L104 _public prototype_ `void StopListening();` — Stops the runnable (Run() will go through on next tick), dispose of created socket listener and close any active connect clients.
- L107 _public prototype_ `FString GetEndpointAddress() const;` — Returns endpoint address we're currently listening on (ip:port) or empty string if not active.
- L110 _public prototype_ `bool IsActive() const;` — Returns whether underlying FTcpListener has been created, is currently active and listening for incoming connections
- L114 _private member_ `uint32 DefaultInactiveTimeoutSeconds;` — The amount of time in seconds to consider a client to be inactive, if it has not sent data in this interval.
- L117 _private member_ `FIPv4Endpoint DesiredEndpoint;` — The desired endpoint for creating the tcp listener. The actual endpoint may be different in case of collision.
- L123 _private member_ `TUniquePtr<FSocket, FSocketDeleter> Socket;`
- L126 _private member_ `TUniquePtr<FTcpListener> SocketListener;` — Our instance of tcp listener, created in StartListening()
- L129 _private member_ `TQueue<TPair<FIPv4Endpoint, TSharedPtr<FSocket>>, EQueueMode::Spsc> PendingConnections;` — Queue of remote pending connections added when tcp listener is accepting a new connection
- L132 _private member_ `TQueue<FIPv4Endpoint, EQueueMode::Spsc> PendingConnectionsToDisconnect;` — Queue of remote endpoints to dispose and disconnect
- L135 _private member_ `TMap<FIPv4Endpoint, TUniquePtr<FClientConnection>> ClientConnections;` — Map of currently connected and active clients
- L138 _private member_ `std::atomic<bool> bStopping = false;` — For the thread
- L141 _private member_ `FRunnableThread* Thread;` — Holds the thread object.
- L144 _private member_ `FOnReceivedBufferEvent ReceivedBufferEvent;` — Multicast delegate that will broadcast a notification when a buffer is fully received and ready to be extracted
- L147 _private prototype_ `bool OnIncomingConnection(FSocket* InSocket, const FIPv4Endpoint& InEndpoint);` — Handler for tcp listener OnConnectionAccepted. Queues the incoming socket / endpoint to pending connections
- L155 _private prototype_ `void HandleIncomingBuffer(const FIPv4Endpoint& InEndpoint, const TSharedPtr<FSocket>& InClientSocket, const TArray<uint8>& InBytes);` — Called from Tick and handles an incoming chunk of data for a given connection. We respond back to clients the overall number of bytes we received so far, and checks against expected size (parsed from tcp stream "header") if we fully received the buffer in which case we trigger the ReceivedBufferEvent delegate.
- L158 _private prototype_ `void HandleReceivedBuffer(const FIPv4Endpoint& InEndpoint, const TSharedPtr<FSocket>& InClientSocket, const TArray<uint8>& InBytes);` — Called from HandleIncomingBuffer() and simply broadcast ReceivedBufferEvent delegate with endpoint, connected socket and received buffer.
- L165 _private prototype_ `void CleanUpDisconnectedSockets();` — Called from Tick() and checks if any connected clients has been inactive more than our DefaultInactiveTimeoutSeconds (5 seconds). If it's inactive, clears up the connect by calling DisconnectClient()
- L168 _private prototype_ `void DisconnectClient(const FIPv4Endpoint& InClientEndpoint);` — Clears up the connected client by disposing every map related to that client endpoint
- L172 _private function_ `template <typename InStructType> FString CreateMessage(const InStructType& InStruct)` — Template helper to serialize a given struct into JSON for sending over tcp socket
- L186 _private prototype_ `bool SendMessage(const FString& InMessage, const FIPv4Endpoint& InEndpoint);` — To use in conjunction with CreateMessage() Takes a raw string and send it on provided endpoint, if we have a current active connection for it (in ClientConnections map)

#### struct `FStormSyncTransportTcpServer::FSocketDeleter`  
`struct FSocketDeleter`  
_L119-122_
- L121 _public prototype_ `void operator()(FSocket* InSocket) const;`

#### Free symbols / members of external scopes

- L76 _delegate_ `DECLARE_EVENT_ThreeParams(FStormSyncServerListener, FOnReceivedBufferEvent, const FIPv4Endpoint&, const TSharedPtr<FSocket>&, const FStormSyncBufferPtr&);` — Event delegate that is executed when a buffer is fully received and ready to be extracted @param Endpoint The first parameter is the client endpoint. @param Socket The second parameter is the client socket. @param Buffer The third parameter is a shared pointer to fully received buffer.

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportServer/Private/StormSyncTransportServerEndpoint.h` (Private)


#### class `FStormSyncTransportServerEndpoint`  
`class FStormSyncTransportServerEndpoint : public IStormSyncTransportServerLocalEndpoint`  
_L20-84_
- inherits: `IStormSyncTransportServerLocalEndpoint`
- desc: Implements a local endpoint for Storm Sync
- L23 _public prototype_ `FStormSyncTransportServerEndpoint();`
- L28 _public prototype_ `virtual bool StartTcpListener(const FIPv4Endpoint& InEndpoint) override;` — Creates and starts tcp listener
- L31 _public prototype_ `virtual bool StartTcpListener() override;` — Creates and starts tcp listener with endpoint configured in project settings
- L34 _public prototype_ `virtual bool IsRunning() const override;` — Returns whether message endpoint is currently active
- L37 _public prototype_ `virtual bool IsTcpServerActive() const override;` — Returns whether underlying FTcpListener has been created, is currently active and listening for incoming connections
- L40 _public prototype_ `virtual FString GetTcpServerEndpointAddress() const override;` — Returns endpoint address tcp server is currently listening on (ip:port), empty string otherwise (if not active / listening)
- L43 _public prototype_ `virtual TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> GetMessageEndpoint() const override;` — Returns underlying message endpoint
- L47 _public prototype_ `void InitializeMessaging(const FString& InEndpointFriendlyName = TEXT("Defa` — Initializes the message endpoint.
- L51 _protected prototype_ `void ShutdownMessaging();` — Shutdown the message endpoint.
- L54 _protected prototype_ `void ShutdownTcpListener();` — Shutdown the tcp server listener.
- L58 _private member_ `TUniquePtr<FStormSyncTransportTcpServer> TcpServer;` — Our instance of tcp listener wrapper
- L65 _private member_ `TWeakPtr<IMessageBus, ESPMode::ThreadSafe> MessageBusPtr;` — Holds a weak pointer to the message bus. @note Since we're using the default message bus, this might be not necessary
- L68 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the message endpoint.
- L71 _private prototype_ `void HandlePingMessage(const FStormSyncTransportPingMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InMessageContext);` — Callback handler to receive FStormSyncTransportPingMessage messages
- L74 _private prototype_ `void HandlePongMessage(const FStormSyncTransportPongMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InMessageContext);` — Callback handler to receive FStormSyncTransportPongMessage messages
- L77 _private prototype_ `void HandleReceivedTcpBuffer(const FIPv4Endpoint& InEndpoint, const TSharedPtr<FSocket>& InSocket, const FStormSyncBufferPtr& InBuffer);` — Callback handler executed when a buffer is fully received over tcp socket and ready to be extracted
- L80 _private prototype_ `void HandleSyncRequestMessage(const FStormSyncTransportSyncRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InMessageContext);` — Callback handler to receive FStormSyncTransportSyncRequest messages
- L83 _private prototype_ `void SendSyncResponse(const FStormSyncTransportSyncRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InMessageContext) const;` — Figures out the diffing state between remote package dependencies and local, and sends back a sync (push) response to sender to kick in the transfer process

#### Free symbols / members of external scopes

- L15 _typedef_ `using IMessageBusPtr = TSharedPtr<IMessageBus, ESPMode::ThreadSafe>;`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportServer/Private/StormSyncTransportServerLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncServer, Display, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncServer, Display, All);`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportServer/Private/StormSyncTransportServerModule.h` (Private)


#### class `FStormSyncTransportServerModule`  
`class FStormSyncTransportServerModule : public IStormSyncTransportServerModule`  
_L12-78_
- inherits: `IStormSyncTransportServerModule`
- desc: Implements the StormSyncTransportServer module.
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `virtual void StartDiscoveryManager() override;`
- L20 _public prototype_ `virtual void StartServerEndpoint(const FString& InEndpointFriendlyName) override;`
- L21 _public prototype_ `virtual TSharedPtr<IStormSyncTransportServerLocalEndpoint> CreateServerLocalEndpoint(const FString& InEndpointFriendlyName) const override;`
- L22 _public prototype_ `virtual FString GetServerEndpointMessageAddressId() const override;`
- L23 _public prototype_ `virtual FString GetDiscoveryManagerMessageAddressId() const override;`
- L24 _public prototype_ `virtual FStormSyncHeartbeatEmitter& GetHeartbeatEmitter() const override;`
- L25 _public prototype_ `virtual bool IsRunning() const override;`
- L26 _public prototype_ `virtual bool GetServerStatus(FText& OutStatusText) const override;`
- L31 _private prototype_ `FString GetCurrentTcpServerEndpointAddress() const;` — Returns the current address (ip:port) the tcp server is bound to.
- L34 _private prototype_ `void ConditionalStartHeartBeatEmitter();` — Starts the heart beat emitter if it was not started already.
- L37 _private prototype_ `void ConditionalStartDiscoveryManager();` — Starts the discovery manager if it was not started already.
- L40 _private prototype_ `void RegisterConsoleCommands();` — Called from StartupModule and sets up console commands for the plugin via IConsoleManager
- L43 _private prototype_ `void UnregisterConsoleCommands();` — Called from ShutdownModule and clears out previously registered console commands
- L46 _private prototype_ `void OnPostEngineInit();` — Event handler to kick in operations once engine is fully initialized (to publish a connect message)
- L49 _private prototype_ `void PublishConnectMessage() const;` — Notify network this client is ready by sending a connect message and starting heartbeats
- L52 _private prototype_ `void PublishPingMessage() const;` — Publishes the ping message for the server endpoint.
- L55 _private prototype_ `void ExecuteStartServer(const TArray<FString>& InArgs);` — Command handler for "StormSync.Server.Start"
- L58 _private prototype_ `void ExecuteStopServer(const TArray<FString>& InArgs);` — Command handler for "StormSync.Server.Stop"
- L61 _private prototype_ `void ExecuteServerStatus(const TArray<FString>& InArgs) const;` — Command handler for "StormSync.Server.Status"
- L65 _private member_ `TSharedPtr<IStormSyncTransportServerLocalEndpoint, ESPMode::ThreadSafe> ServerEndpoint;` — Our message endpoint provider
- L68 _private member_ `TUniquePtr<FStormSyncHeartbeatEmitter> HeartbeatEmitter;` — Unique ptr to our Heartbeat Emitter (Runnable sending heartbeat messages at a fixed interval to subscribed recipients)
- L71 _private member_ `TUniquePtr<FStormSyncDiscoveryManager> DiscoveryManager;` — Unique ptr to our Discovery Manager
- L74 _private member_ `TArray<IConsoleObject*> ConsoleCommands;` — References of registered console commands via IConsoleManager
- L77 _private member_ `bool bEngineInitComplete = false;` — Indicates when the engine init is complete. This is used to know when pending messages can be published.

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportServer/Public/IStormSyncTransportServerLocalEndpoint.h` (Public)


#### class `IStormSyncTransportServerLocalEndpoint`  
`class IStormSyncTransportServerLocalEndpoint : public IStormSyncTransportLocalEndpoint`  
_L10-24_
- inherits: `IStormSyncTransportLocalEndpoint`
- desc: Local Endpoint interface for Storm Sync Server
- L14 _public prototype_ `virtual FString GetTcpServerEndpointAddress() const = 0;` — Returns endpoint address tcp server is currently listening on (ip:port), empty string otherwise (if not active / listening)
- L17 _public prototype_ `virtual bool IsTcpServerActive() const = 0;` — Returns whether underlying FTcpListener has been created, is currently active and listening for incoming connections
- L20 _public prototype_ `virtual bool StartTcpListener(const FIPv4Endpoint& InEndpoint) = 0;` — Start TCP server and start listening with passed in endpoint
- L23 _public prototype_ `virtual bool StartTcpListener() = 0;` — Start TCP server and start listening with configured endpoint in project settings

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportServer/Public/IStormSyncTransportServerModule.h` (Public)


#### class `IStormSyncTransportServerModule`  
`class IStormSyncTransportServerModule : public IModuleInterface`  
_L11-70_
- inherits: `IModuleInterface`
- L20 _public function_ `static IStormSyncTransportServerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L42 _public prototype_ `virtual void StartDiscoveryManager() = 0;` — Starts the discovery manager. This is necessary for clients and servers to see each other. It must be called even if the server endpoint is not created.
- L48 _public prototype_ `virtual void StartServerEndpoint(const FString& InEndpointFriendlyName) = 0;` — Starts a local transport endpoint. This will automatically start the discovery manager.
- L54 _public prototype_ `virtual TSharedPtr<IStormSyncTransportServerLocalEndpoint> CreateServerLocalEndpoint(const FString& InEndpointFriendlyName) const = 0;` — Creates a local transport endpoint. @remark Should be used for tests only.
- L57 _public prototype_ `virtual FString GetServerEndpointMessageAddressId() const = 0;` — Returns Message Address UID for server endpoint if it is currently running, empty string otherwise
- L60 _public prototype_ `virtual FString GetDiscoveryManagerMessageAddressId() const = 0;` — Returns Message Address UID for discovery manager endpoint
- L63 _public prototype_ `virtual FStormSyncHeartbeatEmitter& GetHeartbeatEmitter() const = 0;` — Returns implementation of StormSync Heartbeat Emitter runnable
- L66 _public prototype_ `virtual bool IsRunning() const = 0;` — Returns whether Storm Sync Server endpoint is currently active and running
- L69 _public prototype_ `virtual bool GetServerStatus(FText& OutStatusText) const = 0;` — Returns whether Storm Sync Server endpoint is currently active and running, along with a status text indicating current status and endpoint addresses (message bus and tcp server)
