# Plugins / SocketSubsystemSteamIP

- module root: `Plugins/Online/SocketSubsystemSteamIP/Source/SocketSubsystemSteamIP`
- headers: 7; symbols: 133
- symbol kinds: class=5, externvar=1, function=19, macro=4, member=22, prototype=81, struct=1
- PrivateDependencyModuleNames: CoreOnline, CoreUObject, SteamShared
- PublicDependencyModuleNames: Core, Engine, NetCore, OnlineSubsystemUtils, Sockets

### `Plugins/Online/SocketSubsystemSteamIP/Source/SocketSubsystemSteamIP/Private/SocketsSteam.h` (Private)


#### class `FSocketSteam`  
`class FSocketSteam : public FSocket`  
_L17-289_
- inherits: `FSocket`
- desc: This is the Windows specific socket class
- L23 _private member_ `class FSocketSubsystemSteam* SocketSubsystem;` — Reference to the socket subsystem
- L31 _private member_ `int32 SteamChannel;` — Channel this socket receives data on (similar to port number)
- L34 _private member_ `EP2PSend SteamSendMode;` — Current send mode for SendTo() see EP2PSend in Steam headers
- L37 _private member_ `ISteamNetworking* SteamNetworkingPtr;` — Steam P2P interface (depends on client/server)
- L44 _private function_ `void SetSteamSendMode(EP2PSend NewSendMode)` — Changes the Steam send mode @param NewSendMode send mode to set
- L58 _public function_ `FSocketSteam(ISteamNetworking* InSteamNetworkingPtr, const CSteamID& InLocalSteamId, const FString& InSocketDescription, const FName& InSocketProtocol) : FSocket(SOCKTYPE_Datagram, InSocketDescription, InSocketProtocol), LocalSteamId(InLocalSteamId), SteamChannel(0), SteamSendMode(k_EP2PSendUnreliable), SteamNetworkingPtr(InSteamNetworkingPtr)` — Creates a Steam socket @param InSocket the socket to assign to this object @param InSocketType the type of socket that was created @param InSocketDescription the debug description of the socket @param InSocketProtocol the protocol used to create this socket.
- L69 _public function_ `virtual ~FSocketSteam()` — Closes the socket if it is still open
- L74 _public prototype_ `virtual bool Shutdown(ESocketShutdownMode Mode) override;`
- L81 _public prototype_ `virtual bool Close() override final;` — Closes the socket @param true if it closes without errors, false otherwise
- L90 _public prototype_ `virtual bool Bind(const FInternetAddr& Addr) override;` — Binds a socket to a network byte ordered address @param Addr the address to bind to @return true if successful, false otherwise
- L99 _public prototype_ `virtual bool Connect(const FInternetAddr& Addr) override;` — Connects a socket to a network byte ordered address @param Addr the address to connect to @return true if successful, false otherwise
- L108 _public prototype_ `virtual bool Listen(int32 MaxBacklog) override;` — Places the socket into a state to listen for incoming connections @param MaxBacklog the number of connections to queue before refusing them @return true if successful, false otherwise
- L110 _public prototype_ `virtual bool WaitForPendingConnection(bool& bHasPendingConnection, const FTimespan& WaitTime) override;`
- L119 _public prototype_ `virtual bool HasPendingData(uint32& PendingDataSize) override;` — Queries the socket to determine if there is pending data on the queue @param PendingDataSize out parameter indicating how much data is on the pipe for a single recv call @return true if the socket has data, false otherwise
- L127 _public prototype_ `virtual class FSocket* Accept(const FString& SocketDescription) override;` — Accepts a connection that is pending @param		SocketDescription debug description of socket @return		The new (heap-allocated) socket, or NULL if unsuccessful.
- L137 _public prototype_ `virtual class FSocket* Accept(FInternetAddr& OutAddr, const FString& SocketDescription) override;` — Accepts a connection that is pending @param OutAddr the address of the connection @param		SocketDescription debug description of socket @return		The new (heap-allocated) socket, or NULL if unsuccessful.
- L147 _public prototype_ `virtual bool SendTo(const uint8* Data, int32 Count, int32& BytesSent, const FInternetAddr& Destination) override;` — Sends a buffer to a network byte ordered address @param Data the buffer to send @param Count the size of the data to send @param BytesSent out param indicating how much was sent @param Destination the network byte ordered address to send to
- L156 _public prototype_ `virtual bool Send(const uint8* Data, int32 Count, int32& BytesSent) override;` — Sends a buffer on a connected socket @param Data the buffer to send @param Count the size of the data to send @param BytesSent out param indicating how much was sent
- L167 _public prototype_ `virtual bool RecvFrom(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;` — Reads a chunk of data from the socket. Gathers the source address too @param Data the buffer to read into @param BufferSize the max size of the buffer @param BytesRead out param indicating how many bytes were read from the socket @param Source out param receiving the address of the sender of the data @param Flags the receive flags (must be ESocketReceiveFlags::None)
- L177 _public prototype_ `virtual bool Recv(uint8* Data,int32 BufferSize,int32& BytesRead, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;` — Reads a chunk of data from a connected socket @param Data the buffer to read into @param BufferSize the max size of the buffer @param BytesRead out param indicating how many bytes were read from the socket @param Flags the receive flags
- L179 _public prototype_ `virtual bool Wait(ESocketWaitConditions::Type Condition, FTimespan WaitTime) override;`
- L184 _public prototype_ `virtual ESocketConnectionState GetConnectionState() override;` — Determines the connection state of the socket
- L191 _public prototype_ `virtual void GetAddress(FInternetAddr& OutAddr) override;` — Reads the address the socket is bound to and returns it @param OutAddr address the socket is bound to
- L198 _public prototype_ `virtual bool GetPeerAddress(FInternetAddr& OutAddr) override;` — Reads the address of the peer the socket is connected to and returns it @param OutAddr address of the peer the socket is connected to
- L207 _public prototype_ `virtual bool SetNonBlocking(bool bIsNonBlocking = true) override;` — Sets this socket into non-blocking mode @param bIsNonBlocking whether to enable blocking or not @return true if successful, false otherwise
- L216 _public prototype_ `virtual bool SetBroadcast(bool bAllowBroadcast = true) override;` — Sets a socket into broadcast mode (UDP only) @param bAllowBroadcast whether to enable broadcast or not @return true if successful, false otherwise
- L218 _public function_ `virtual bool SetNoDelay(bool bIsNoDelay = true) override`
- L223 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress) override;`
- L225 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress) override;`
- L227 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;`
- L229 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;`
- L231 _public prototype_ `virtual bool SetMulticastLoopback(bool bLoopback) override;`
- L233 _public prototype_ `virtual bool SetMulticastTtl(uint8 TimeToLive) override;`
- L235 _public prototype_ `virtual bool SetMulticastInterface(const FInternetAddr& InterfaceAddress) override;`
- L244 _public prototype_ `virtual bool SetReuseAddr(bool bAllowReuse = true) override;` — Sets whether a socket can be bound to an address in use @param bAllowReuse whether to allow reuse or not @return true if the call succeeded, false otherwise
- L254 _public prototype_ `virtual bool SetLinger(bool bShouldLinger = true, int32 Timeout = 0) override;` — Sets whether and how long a socket will linger after closing @param bShouldLinger whether to have the socket remain open for a time period after closing or not @param Timeout the amount of time to linger before closing @return true if the call succeeded, false otherwise
- L263 _public prototype_ `virtual bool SetRecvErr(bool bUseErrorQueue = true) override;` — Enables error queue support for the socket @param bUseErrorQueue whether to enable error queueing or not @return true if the call succeeded, false otherwise
- L273 _public prototype_ `virtual bool SetSendBufferSize(int32 Size,int32& NewSize) override;` — Sets the size of the send buffer to use @param Size the size to change it to @param NewSize the out value returning the size that was set (in case OS can't set that) @return true if the call succeeded, false otherwise
- L283 _public prototype_ `virtual bool SetReceiveBufferSize(int32 Size,int32& NewSize) override;` — Sets the size of the receive buffer to use @param Size the size to change it to @param NewSize the out value returning the size that was set (in case OS can't set that) @return true if the call succeeded, false otherwise
- L288 _public prototype_ `virtual int32 GetPortNo() override;` — Reads the port this socket is bound to.

### `Plugins/Online/SocketSubsystemSteamIP/Source/SocketSubsystemSteamIP/Public/SocketSubsystemSteam.h` (Public)


#### class `FSocketSubsystemSteam`  
`class FSocketSubsystemSteam : public ISocketSubsystem, public FTSTickerObjectBase, public FSelfRegisteringExec`  
_L35-455_
- inherits: `ISocketSubsystem,FTSTickerObjectBase,FSelfRegisteringExec`
- desc: Windows specific socket subsystem implementation
- L40 _protected member_ `static FSocketSubsystemSteam* SocketSingleton;` — Single instantiation of this subsystem
- L43 _protected member_ `TArray<class FSocketSteam*> SteamSockets;` — Tracks existing Steamworks sockets, for connection failure/timeout resolution
- L46 _protected member_ `TArray<struct FWeakObjectPtr> SteamConnections;` — Tracks existing Steamworks connections, for connection failure/timeout resolution
- L49 _protected member_ `CSteamID GameServerCSID = CSteamID();` — Tracks the game server's steam ID given to us by the session interface
- L87 _protected member_ `TMap<uint64, FSteamP2PConnectionInfo> AcceptedConnections;` — List of Steam P2P connections we have As connections at start do not have a channel id, the key is just the accounts connected to us.
- L94 _protected member_ `TMap<FInternetAddrSteam, double> DeadConnections;` — List of Steam P2P connections to shutdown. If the FInternetAddrSteam has a channel id of -1, all connections are dropped from the user. Also tracked is the time in which the connection was marked to be removed (for linger purposes)
- L100 _protected member_ `bool bAllowP2PPacketRelay;` — Should Steam P2P sockets all fall back to Steam servers relay if a direct connection fails read from [OnlineSubsystemSteam.bAllowP2PPacketRelay]
- L106 _protected member_ `float P2PConnectionTimeout;` — Timeout (in seconds) period for any P2P session read from [OnlineSubsystemSteam.P2PConnectionTimeout] (should be at least as long as NetDriver::ConnectionTimeout)
- L108 _protected member_ `double P2PDumpCounter;` — Accumulated time before next dump of connection info
- L110 _protected member_ `double P2PDumpInterval;` — Connection info output interval
- L118 _protected member_ `double P2PCleanupTimeout;` — The timeout (in seconds) between when a connection/channel is marked as destroyed and when it's cleaned up. This allows for catching lingering messages from other users. If set to 0, all dead connections will be cleaned up each tick. read from [OnlineSubsystemSteam.P2PCleanupTimeout]
- L125 _protected function_ `void AddSocket(class FSocketSteam* InSocket)` — Adds a steam socket for tracking @param InSocket	The socket to add for tracking
- L135 _protected function_ `void RemoveSocket(class FSocketSteam* InSocket)` — Removes a steam socket from tracking @param InSocket	The socket to remove from tracking
- L151 _protected prototype_ `static void Destroy();` — Performs Windows specific socket clean up
- L159 _protected prototype_ `void CleanupDeadConnections(bool bSkipLinger);` — Iterate through the pending dead connections and permanently remove any that have been around long enough to flush their contents @param bSkipLinger skips the timeout reserved for lingering connection information to a race condition
- L166 _protected prototype_ `void FixupSockets(const CSteamID& GameServerId);` — Associate the game server steam id with any sockets that were created prior to successful login @param GameServerId id assigned to this game server
- L173 _protected prototype_ `void RegisterConnection(class USteamNetConnection* Connection);` — Adds a steam connection for tracking @param Connection The connection to add for tracking
- L180 _protected prototype_ `void UnregisterConnection(class USteamNetConnection* Connection);` — Removes a steam connection from tracking @param Connection The connection to remove from tracking
- L187 _protected prototype_ `void ConnectFailure(const CSteamID& RemoteId);` — Notification from the Steam event layer that a remote connection has completely failed @param RemoteId failure address
- L197 _protected prototype_ `bool AcceptP2PConnection(ISteamNetworking* SteamNetworkingPtr, const CSteamID& RemoteId);` — Potentially accept an incoming connection from a Steam P2P request @param SteamNetworkingPtr the interface for access the P2P calls (Client/GameServer) @param RemoteId the id of the incoming request @return true if accepted, false otherwise
- L208 _protected prototype_ `bool P2PTouch(ISteamNetworking* SteamNetworkingPtr, const CSteamID& SessionId, int32 ChannelId = -1);` — Add/update a Steam P2P connection as being recently accessed @param SteamNetworkingPtr proper networking interface that this session is communicating on @param SessionId P2P session recently heard from @param ChannelId the channel id that the update happened on @return true if the connection is active, false if this is in the dead connections list
- L216 _protected prototype_ `void P2PRemove(const CSteamID& SessionId, int32 Channel = -1);` — Remove a Steam P2P session from tracking and close the connection @param SessionId P2P session to remove @param Channel channel to close, -1 to close all communication
- L227 _protected prototype_ `bool IsConnectionPendingRemoval(const CSteamID& SteamId, int32 Channel);` — Checks to see if a Steam P2P Connection is pending close on the given channel. Before checking the given channel, this function checks if the session is marked for global disconnection. @param SessionId the user id tied to the session disconnection @param Channel the communications channel id for the user if it exists
- L241 _protected prototype_ `bool ShouldOverrideDefaultSubsystem() const;` — Determines if the SocketSubsystemSteam should override the platform socket subsystem. This means ISocketSubsystem::Get() will return this subsystem by default. However, the platform subsystem will still be accessible by specifying ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM) as well as via passthrough operations. If the project does not want to use SteamNetworking features, add bUseSteamNetworking=false to your OnlineSubsystemSteam configuration @return if SteamNetworking should be the default socketsubsystem.
- L248 _protected prototype_ `void DumpSteamP2PSessionInfo(P2PSessionState_t& SessionInfo);` — Dumps the Steam P2P networking information for a given session state @param SessionInfo struct from Steam call to GetP2PSessionState
- L253 _protected prototype_ `void DumpAllOpenSteamSessions();` — Dumps all connection information for each user connection over SteamNet.
- L260 _protected prototype_ `STEAM_GAMESERVER_CALLBACK(FSocketSubsystemSteam, OnSteamServersConnectedGS, SteamServersConnected_t, OnSteamServersConnectedGSCallback);` — Delegate registered with Steam to trigger when a server (gameserver API) is connected to the Steam servers.  Initiated with a LogOnAnonymous() call
- L264 _protected prototype_ `STEAM_CALLBACK(FSocketSubsystemSteam, OnP2PSessionRequest, P2PSessionRequest_t, OnP2PSessionRequestCallback);` — Delegate registered with Steam to trigger when another Steam client makes a P2P call to this instance
- L266 _protected prototype_ `STEAM_CALLBACK(FSocketSubsystemSteam, OnP2PSessionConnectFail, P2PSessionConnectFail_t, OnP2PSessionConnectFailCallback);` — Delegate registered with Steam to trigger when a connection between two steam P2P endpoints fails
- L268 _protected prototype_ `STEAM_GAMESERVER_CALLBACK(FSocketSubsystemSteam, OnP2PSessionRequestGS, P2PSessionRequest_t, OnP2PSessionRequestGSCallback);` — Delegate registered with Steam to trigger when another Steam client makes a P2P call to this instance (gameserver API)
- L270 _protected prototype_ `STEAM_GAMESERVER_CALLBACK(FSocketSubsystemSteam, OnP2PSessionConnectFailGS, P2PSessionConnectFail_t, OnP2PSessionConnectFailGSCallback);` — Delegate registered with Steam to trigger when a connection between two steam P2P endpoints fails (gameserver API)
- L277 _public function_ `void UpdateGameServerId(const CSteamID& InGameServerCSID)` — If the session interface wishes to bring up a game server socket, it must call this first when the policy response has been received to update us with the corresponding SteamId to use in the socket layer
- L283 _public member_ `int32 LastSocketError;` — Last error set by the socket subsystem or one of its sockets
- L287 _public function_ `FSocketSubsystemSteam() : bAllowP2PPacketRelay(false), P2PConnectionTimeout(45.0f), P2PDumpCounter(0.0), P2PDumpInterval(10.0), P2PCleanupTimeout(1.5), OnSteamServersConnectedGSCallback(this, &FSocketSubsystemSteam::OnSteamServersConnectedGS), OnP2PSessionRequestCallback(this, &FSocketSubsystemSteam::OnP2PSessionRequest), OnP2PSessionConnectFailCallback(this, &FSocketSubsystemSteam::OnP2PSessionConnectFail), OnP2PSessionRequestGSCallback(this, &FSocketSubsystemSteam::OnP2PSessionRequestGS), OnP2PSessionConnectFailGSCallback(this, &FSocketSubsystemSteam::OnP2PSessionConnectFailGS), LastSocketError(0)`
- L309 _public prototype_ `virtual bool Init(FString& Error) override;` — Does Windows platform initialization of the sockets library @param Error a string that is filled with error information @return true if initialized ok, false otherwise
- L314 _public prototype_ `virtual void Shutdown() override;` — Performs platform specific socket clean up
- L326 _public prototype_ `virtual class FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, const FName& ProtocolType) override;`
- L333 _public prototype_ `virtual void DestroySocket(class FSocket* Socket) override;` — Cleans up a socket class @param Socket the socket object to destroy
- L350 _public prototype_ `virtual FAddressInfoResult GetAddressInfo(const TCHAR* HostName, const TCHAR* ServiceName = nullptr, EAddressInfoFlags QueryFlags = EAddressInfoFlags::Default, const FName ProtocolTypeName = NAME_None, ESocketType SocketType = ESocketType::SOCKTYPE_Unknown) override;` — Gets the address information of the given hostname and outputs it into an array of resolvable addresses. It is up to the caller to determine which one is valid for their environment. @param HostName string version of the queryable hostname or ip address @param ServiceName string version of a service name ("http") or a port number ("80") @param QueryFlags What flags are used in making the getaddrinfo call. Several flags can be used at once by ORing the values together. Platforms are required to translate this value into a the correct flag representation. @param ProtocolType this is used to limit results from the call. Specifying None will search all valid protocols. Callers will find they rarely have to specify this flag. @param SocketType What socket type should the results be formatted for. This typically does not change any formatting results and can be safely left to the default value. @return the array of results from GetAddrInfo
- L370 _public prototype_ `virtual TSharedPtr<FInternetAddr> GetAddressFromString(const FString& IPAddress) override;` — Serializes a string that only contains an address. On Steam, this will take SteamIDs and serialize them into FInternetAddrSteam if it is determined the input string is an ID. Otherwise, this will give you back a FInternetAddrBSD. This is a what you see is what you get, there is no DNS resolution of the input string, so only use this if you know you already have a valid ip address. Otherwise, feed the address to GetAddressInfo for guaranteed results. @param IPAddress the ip address to serialize @return The FInternetAddr of the given string address. This will point to nullptr on failure.
- L377 _public function_ `virtual bool RequiresChatDataBeSeparate() override` — Some platforms require chat data (voice, text, etc.) to be placed into packets in a special way. This function tells the net connection whether this is required for this platform
- L386 _public function_ `virtual bool RequiresEncryptedPackets() override` — Some platforms require packets be encrypted. This function tells the net connection whether this is required for this platform
- L398 _public prototype_ `virtual bool GetHostName(FString& HostName) override;` — Determines the name of the local machine @param HostName the string that receives the data @return true if successful, false otherwise
- L403 _public prototype_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr() override;` — Create a proper FInternetAddr representation
- L408 _public prototype_ `virtual bool HasNetworkDevice() override;` — @return Whether the machine has a properly configured network device or not
- L414 _public prototype_ `virtual const TCHAR* GetSocketAPIName() const override;` — Get the name of the socket subsystem @return a string naming this subsystem
- L419 _public prototype_ `virtual ESocketErrors GetLastErrorCode() override;` — Returns the last error that has happened
- L424 _public prototype_ `virtual ESocketErrors TranslateErrorCode(int32 Code) override;` — Translates the platform error code to a ESocketErrors enum
- L433 _public prototype_ `virtual bool GetLocalAdapterAddresses(TArray<TSharedPtr<FInternetAddr>>& OutAddresses) override;` — Gets the list of addresses associated with the adapters on the local computer. @param OutAdresses - Will hold the address list. @return true on success, false otherwise.
- L438 _public prototype_ `virtual TArray<TSharedRef<FInternetAddr>> GetLocalBindAddresses() override;` — Get local IP to bind to
- L445 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — Chance for the socket subsystem to get some time @param DeltaTime time since last tick
- L450 _public function_ `virtual bool IsSocketWaitSupported() const override` — Waiting on a socket is not supported.
- L454 _protected prototype_ `virtual bool Exec_Dev(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FSelfRegisteringExec

#### struct `FSocketSubsystemSteam::FSteamP2PConnectionInfo`  
`struct FSteamP2PConnectionInfo`  
_L52-81_
- desc: Holds Steam connection information for each user
- L55 _public member_ `ISteamNetworking* SteamNetworkingPtr;` — Steam networking interface responsible for this connection
- L61 _public member_ `double LastReceivedTime;` — Last time the user's p2p session had activity (RecvFrom, etc). The value of this member is always the max value of the ConnectedChannels object
- L66 _public member_ `TArray<int32> ConnectedChannels;` — Channel connection ids for this user
- L68 _public function_ `FSteamP2PConnectionInfo(ISteamNetworking* InNetworkPtr=nullptr) : SteamNetworkingPtr(InNetworkPtr), LastReceivedTime(FPlatformTime::Seconds())`
- L76 _public function_ `void AddOrUpdateChannel(int32 InChannel, double InTime)` — This helper function automatically updates LastRecievedTime

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SOCKETSUBSYSTEMSTEAMIP_API`
- L20 _externvar_ `extern const FName STEAMIP_SUBSYSTEMNAME;`
- L25 _prototype_ `extern FName CreateSteamSocketSubsystem();` — Create the socket subsystem for the given platform service
- L30 _prototype_ `extern void DestroySteamSocketSubsystem();` — Tear down the socket subsystem for the given platform service

### `Plugins/Online/SocketSubsystemSteamIP/Source/SocketSubsystemSteamIP/Public/SocketSubsystemSteamIPModule.h` (Public)


#### class `FSocketSubsystemSteamIPModule`  
`class FSocketSubsystemSteamIPModule : public IModuleInterface`  
_L11-48_
- inherits: `IModuleInterface`
- L15 _public function_ `FSocketSubsystemSteamIPModule() : bEnabled(false)`
- L20 _public function_ `virtual ~FSocketSubsystemSteamIPModule()`
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _public function_ `virtual bool SupportsDynamicReloading() override`
- L34 _public function_ `static inline class FSocketSubsystemSteamIPModule& Get()`
- L39 _public function_ `static inline bool IsAvailable()`
- L44 _public function_ `bool IsEnabled() const`
- L47 _private member_ `bool bEnabled;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SOCKETSUBSYSTEMSTEAMIP_API`

### `Plugins/Online/SocketSubsystemSteamIP/Source/SocketSubsystemSteamIP/Public/SocketSubsystemSteamIPPackage.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define PACKAGE_SCOPE public`
- L7 _macro_ `#define PACKAGE_SCOPE protected`

### `Plugins/Online/SocketSubsystemSteamIP/Source/SocketSubsystemSteamIP/Public/SocketSubsystemSteamTypes.h` (Public)
_(no declarations extracted)_

### `Plugins/Online/SocketSubsystemSteamIP/Source/SocketSubsystemSteamIP/Public/SteamNetConnection.h` (Public)


#### class `USteamNetConnection`  
`class USteamNetConnection : public UIpConnection`  
_L15-31_
- reflection: `UCLASS(transient, config=Engine)`
- inherits: `UIpConnection`
- L20 _private prototype_ `virtual void InitRemoteConnection(class UNetDriver* InDriver, class FSocket* InSocket, const FURL& InURL, const class FInternetAddr& InRemoteAddr, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L21 _private prototype_ `virtual void InitLocalConnection(class UNetDriver* InDriver, class FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L22 _private prototype_ `virtual void CleanUp() override;`
- L27 _private member_ `bool bIsPassthrough;` — `UPROPERTY()` — Is this net connection passthrough to IpConnection

### `Plugins/Online/SocketSubsystemSteamIP/Source/SocketSubsystemSteamIP/Public/SteamNetDriver.h` (Public)


#### class `USteamNetDriver`  
`class USteamNetDriver : public UIpNetDriver`  
_L18-41_
- reflection: `UCLASS(transient, config=Engine)`
- inherits: `UIpNetDriver`
- L23 _private member_ `bool bIsPassthrough;` — Should this net driver behave as a passthrough to normal IP
- L26 _private prototype_ `virtual void PostInitProperties() override;`
- L31 _private prototype_ `virtual class ISocketSubsystem* GetSocketSubsystem() override;`
- L32 _private prototype_ `virtual bool IsAvailable() const override;`
- L33 _private prototype_ `virtual bool InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error) override;`
- L34 _private prototype_ `virtual bool InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error) override;`
- L35 _private prototype_ `virtual bool InitListen(FNetworkNotify* InNotify, FURL& ListenURL, bool bReuseAddressAndPort, FString& Error) override;`
- L36 _private prototype_ `virtual void Shutdown() override;`
- L37 _private prototype_ `virtual bool IsNetResourceValid() override;`
