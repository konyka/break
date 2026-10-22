# Plugins / SteamSockets

- module root: `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets`
- headers: 12; symbols: 221
- symbol kinds: class=9, function=48, macro=10, member=37, prototype=113, struct=2, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, NetCore, OnlineSubsystem, OnlineSubsystemSteam, PacketHandler, Sockets, SteamShared

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Private/IPAddressSteamSockets.h` (Private)


#### class `FInternetAddrSteamSockets`  
`class FInternetAddrSteamSockets : public FInternetAddr`  
_L17-173_
- inherits: `FInternetAddr`
- L21 _private member_ `int32 P2PVirtualPort;`
- L22 _private member_ `FName ProtocolType;`
- L25 _public function_ `FInternetAddrSteamSockets(const FName RequestedProtocol = NAME_None) : P2PVirtualPort(0), ProtocolType(RequestedProtocol)`
- L32 _public function_ `FInternetAddrSteamSockets(const SteamNetworkingIdentity& NewAddress) : Addr(NewAddress), P2PVirtualPort(0), ProtocolType(NewAddress.GetIPAddr() == nullptr ? FNetworkProtocolTypes::SteamSocketsP2P : FNetworkProtocolTypes::SteamSocketsIP)`
- L39 _public function_ `FInternetAddrSteamSockets(const SteamNetworkingIPAddr& IPAddr) : P2PVirtualPort(0), ProtocolType(FNetworkProtocolTypes::SteamSocketsIP)`
- L46 _public function_ `explicit FInternetAddrSteamSockets(uint64& SteamID) : P2PVirtualPort(0), ProtocolType(FNetworkProtocolTypes::SteamSocketsP2P)`
- L53 _public prototype_ `virtual TArray<uint8> GetRawIp() const override;`
- L55 _public prototype_ `virtual void SetRawIp(const TArray<uint8>& RawAddr) override;`
- L57 _public function_ `virtual void SetIp(uint32 InAddr) override`
- L67 _public prototype_ `virtual void SetIp(const TCHAR* InAddr, bool& bIsValid) override;` — Sets the ip address from a string ("A.B.C.D") or a steam id "steam.STEAMID" or "STEAMID:PORT" @param InAddr the string containing the new ip address to use
- L74 _public function_ `virtual void GetIp(uint32& OutAddr) const override` — Copies the network byte order ip address to a host byte order dword @param OutAddr the out param receiving the ip address
- L84 _public prototype_ `virtual void SetPort(int32 InPort) override;` — Sets the port number from a host byte order int @param InPort the new port to use (must convert to network byte order)
- L89 _public prototype_ `virtual int32 GetPort() const override;` — Returns the port number from this address in host byte order
- L94 _public function_ `virtual void SetPlatformPort(int32 InPort) override` — Set Platform specific port data
- L102 _public function_ `virtual int32 GetPlatformPort() const override` — Get platform specific port data.
- L108 _public prototype_ `virtual void SetAnyAddress() override;` — Sets the address to be any address
- L111 _public function_ `virtual void SetBroadcastAddress() override` — Sets the address to broadcast
- L117 _public function_ `virtual void SetLoopbackAddress() override` — Sets the address to loopback
- L127 _public prototype_ `virtual FString ToString(bool bAppendPort) const override;` — Converts this internet ip address to string form @param bAppendPort whether to append the port information or not
- L134 _public function_ `virtual bool operator==(const FInternetAddr& Other) const override` — Compares two internet ip addresses for equality @param Other the address to compare against
- L140 _public prototype_ `virtual uint32 GetTypeHash() const override;`
- L142 _public prototype_ `virtual FName GetProtocolType() const override;`
- L144 _public function_ `virtual bool IsValid() const override`
- L149 _public function_ `operator const SteamNetworkingIPAddr() const`
- L161 _public function_ `operator const SteamNetworkingIdentity() const`
- L166 _public function_ `virtual TSharedRef<FInternetAddr> Clone() const override`

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Private/SteamSocket.h` (Private)


#### class `FSteamSocket`  
`class FSteamSocket : public FSocket`  
_L10-98_
- inherits: `FSocket`
- L14 _private member_ `HSteamNetConnection InternalHandle;`
- L16 _private member_ `FInternetAddrSteamSockets BindAddress;` — Binding address to determine the Steam Socket protocol we'll be using
- L17 _private member_ `int32 SendMode;`
- L18 _private member_ `bool bShouldLingerOnClose;`
- L20 _private member_ `bool bIsListenSocket;` — Flag to differentiate which calls can be performed on this socket
- L22 _private member_ `bool bIsLANSocket;` — Flag to make sure we set the weaker authentication (skips SDR validation) in a LAN environment.
- L24 _private member_ `bool bHasPendingData;` — Easy flag to quickly determine if the pending data needs to be taken before expiration.
- L27 _private member_ `ESteamNetConnectionEnd ClosureReason;` — Steam Internal value used for shutting off a socket
- L32 _private member_ `SteamNetworkingMessage_t* PendingData;` — This is used for peeking and looking at pending data Data is already internally handled in a queue on the SteamAPI side, this will give us whatever is at the top Only set if called with HasPendingData or Recv with a Peek flag.
- L34 _private member_ `class FSteamSocketsSubsystem* SocketSubsystem;`
- L37 _private prototype_ `void SetLanOptions();` — Makes sure that sockets are properly set up in LAN environments.
- L41 _public prototype_ `FSteamSocket(ESocketType InSocketType, const FString& InSocketDescription, const FName& InSocketProtocol);` — FSocket implementation
- L42 _public prototype_ `virtual ~FSteamSocket();`
- L44 _public prototype_ `virtual bool Close() override;`
- L46 _public prototype_ `virtual bool Bind(const FInternetAddr& Addr) override;`
- L47 _public prototype_ `virtual bool Connect(const FInternetAddr& Addr) override;`
- L48 _public prototype_ `virtual bool Listen(int32 MaxBacklog) override;`
- L50 _public prototype_ `virtual class FSocket* Accept(const FString& InSocketDescription) override;`
- L51 _public function_ `virtual class FSocket* Accept(FInternetAddr& OutAddr, const FString& InSocketDescription) override`
- L53 _public prototype_ `virtual bool SendTo(const uint8* Data, int32 Count, int32& BytesSent, const FInternetAddr& Destination) override;`
- L55 _public prototype_ `virtual bool Send(const uint8* Data, int32 Count, int32& BytesSent) override;`
- L56 _public prototype_ `virtual bool Recv(uint8* Data, int32 BufferSize, int32& BytesRead, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;`
- L58 _public prototype_ `virtual bool HasPendingData(uint32& PendingDataSize) override;`
- L59 _public prototype_ `virtual ESocketConnectionState GetConnectionState() override;`
- L61 _public function_ `virtual void GetAddress(FInternetAddr& OutAddr) override`
- L62 _public prototype_ `virtual bool GetPeerAddress(FInternetAddr& OutAddr) override;`
- L64 _public prototype_ `virtual bool SetNoDelay(bool bIsNoDelay = true) override;`
- L65 _public prototype_ `virtual bool SetLinger(bool bShouldLinger = true, int32 Timeout = 0) override;`
- L67 _public prototype_ `virtual bool SetSendBufferSize(int32 Size, int32& NewSize) override;`
- L68 _public prototype_ `virtual bool SetReceiveBufferSize(int32 Size, int32& NewSize) override;`
- L70 _public function_ `virtual int32 GetPortNo() override`
- L76 _public prototype_ `virtual bool Shutdown(ESocketShutdownMode Mode) override;` — Unsupported functions
- L77 _public prototype_ `virtual bool Wait(ESocketWaitConditions::Type Condition, FTimespan WaitTime) override;`
- L78 _public prototype_ `virtual bool WaitForPendingConnection(bool& bHasPendingConnection, const FTimespan& WaitTime) override;`
- L79 _public prototype_ `virtual bool SetReuseAddr(bool bAllowReuse = true) override;`
- L80 _public prototype_ `virtual bool SetRecvErr(bool bUseErrorQueue = true) override;`
- L81 _public prototype_ `virtual bool SetNonBlocking(bool bIsNonBlocking = true) override;`
- L82 _public prototype_ `virtual bool SetBroadcast(bool bAllowBroadcast = true) override;`
- L83 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress) override;`
- L84 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;`
- L85 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress) override;`
- L86 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress);`
- L87 _public prototype_ `virtual bool SetMulticastLoopback(bool bLoopback) override;`
- L88 _public prototype_ `virtual bool SetMulticastTtl(uint8 TimeToLive) override;`
- L89 _public prototype_ `virtual bool SetMulticastInterface(const FInternetAddr& InterfaceAddress) override;`
- L93 _public prototype_ `bool RecvRaw(SteamNetworkingMessage_t*& Data, int32 MaxMessages, int32& MessagesRead, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None);`
- L95 _public function_ `void SetClosureReason(ESteamNetConnectionEnd NewClosureReason)`
- L96 _public prototype_ `void SetSendMode(int32 NewSendMode);`

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Private/SteamSocketsPing.h` (Private)


#### class `FSteamSocketsPing`  
`class FSteamSocketsPing : public FOnlinePingInterfaceSteam`  
_L10-26_
- inherits: `FOnlinePingInterfaceSteam`
- desc: Steam Sockets ping interface implementation. See OnlinePingInterfaceSteam.h for information
- L13 _public function_ `FSteamSocketsPing(class FSteamSocketsSubsystem* InSocketSub, class FOnlineSubsystemSteam* InOnlineSub) : FOnlinePingInterfaceSteam(InOnlineSub), SocketSub(InSocketSub)`
- L19 _public prototype_ `virtual bool IsUsingP2PRelays() const override;`
- L20 _public prototype_ `virtual FString GetHostPingData() const override;`
- L21 _public prototype_ `virtual int32 GetPingFromHostData(const FString& HostPingStr) const override;`
- L22 _public prototype_ `virtual bool IsRecalculatingPing() const override;`
- L25 _protected member_ `class FSteamSocketsSubsystem* SocketSub;`

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Private/SteamSocketsPrivate.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define STEAM_URL_PREFIX TEXT("steam.")`
- L34 _macro_ `#define STEAM_SDK_IGNORE_REDUNDANCY_START \`
- L38 _macro_ `#define STEAM_SDK_IGNORE_REDUNDANCY_END \`

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Private/SteamSocketsTaskManager.h` (Private)


#### class `FSteamSocketsTaskManager`  
`class FSteamSocketsTaskManager : public FSteamSocketsTaskManagerInterface`  
_L12-38_
- inherits: `FSteamSocketsTaskManagerInterface`
- desc: A glorified event manager for handling status updates about SteamSockets we hold.
- L15 _public function_ `FSteamSocketsTaskManager(FSteamSocketsSubsystem* SocketSub) : FSteamSocketsTaskManagerInterface(SocketSub), OnConnectionStatusChangedCallback(this, &FSteamSocketsTaskManager::OnConnectionStatusChanged), OnConnectionStatusChangedGSCallback(this, &FSteamSocketsTaskManager::OnConnectionStatusChangedGS)`
- L23 _public function_ `virtual ~FSteamSocketsTaskManager()`
- L28 _public prototype_ `virtual void Tick() override;`
- L32 _private prototype_ `STEAM_CALLBACK(FSteamSocketsTaskManager, OnConnectionStatusChanged, SteamNetConnectionStatusChangedCallback_t, OnConnectionStatusChangedCallback);`
- L33 _private prototype_ `STEAM_GAMESERVER_CALLBACK(FSteamSocketsTaskManager, OnConnectionStatusChangedGS, SteamNetConnectionStatusChangedCallback_t, OnConnectionStatusChangedGSCallback);`
- L37 _private member_ `TQueue<SteamNetConnectionStatusChangedCallback_t> MessageQueue;` — A copied queue of our messages we get from the SteamAPI. There's no difference between client and server messages just how they are registered.

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Public/SteamSocketsModule.h` (Public)


#### class `FSteamSocketsModule`  
`class FSteamSocketsModule : public IModuleInterface`  
_L11-49_
- inherits: `IModuleInterface`
- L15 _public function_ `FSteamSocketsModule() : bEnabled(false)`
- L20 _public function_ `virtual ~FSteamSocketsModule()`
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _public function_ `virtual bool SupportsDynamicReloading() override`
- L34 _public function_ `static inline class FSteamSocketsModule& Get()`
- L39 _public function_ `static inline bool IsAvailable()`
- L44 _public function_ `bool IsSteamSocketsEnabled() const`
- L48 _private member_ `bool bEnabled;` — Allows for easier configuration of which SteamSockets system to use.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STEAMSOCKETS_API`

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Public/SteamSocketsNetConnection.h` (Public)


#### class `USteamSocketsNetConnection`  
`class USteamSocketsNetConnection : public UNetConnection`  
_L17-53_
- reflection: `UCLASS(MinimalAPI, transient, config=Engine)`
- inherits: `UNetConnection`
- L23 _public function_ `USteamSocketsNetConnection() : ConnectionSocket(nullptr), bInConnectionlessHandshake(false)`
- L30 _public prototype_ `virtual void CleanUp() override;`
- L31 _public prototype_ `virtual void InitBase(UNetDriver* InDriver, FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L32 _public prototype_ `virtual void InitRemoteConnection(UNetDriver* InDriver, FSocket* InSocket, const FURL& InURL, const FInternetAddr& InRemoteAddr, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L34 _public prototype_ `virtual void InitLocalConnection(UNetDriver* InDriver, FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L35 _public prototype_ `virtual void LowLevelSend(void* Data, int32 CountBits, FOutPacketTraits& Traits) override;`
- L36 _public prototype_ `FString LowLevelGetRemoteAddress(bool bAppendPort=false) override;`
- L37 _public prototype_ `FString LowLevelDescribe() override;`
- L41 _private function_ `const FSteamSocket* GetRawSocket() const`
- L43 _private prototype_ `void HandleRecvMessage(void* InData, int32 SizeOfData, const FInternetAddr* InFormattedAddress);`
- L45 _private function_ `void FlagForHandshake()`
- L47 _private function_ `void ClearSocket()`
- L49 _private member_ `FSteamSocket* ConnectionSocket;`
- L50 _private member_ `bool bInConnectionlessHandshake;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STEAMSOCKETS_API`

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Public/SteamSocketsNetDriver.h` (Public)


#### class `USteamSocketsNetDriver`  
`class USteamSocketsNetDriver : public UNetDriver`  
_L17-61_
- reflection: `UCLASS(MinimalAPI, transient, config=Engine)`
- inherits: `UNetDriver`
- L23 _public function_ `USteamSocketsNetDriver() : Socket(nullptr), bIsDelayedNetworkAccess(false)`
- L30 _public prototype_ `virtual void PostInitProperties() override;`
- L34 _public prototype_ `virtual void Shutdown() override;`
- L35 _public prototype_ `virtual bool IsAvailable() const override;`
- L36 _public prototype_ `virtual bool InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error) override;`
- L37 _public prototype_ `virtual bool InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error) override;`
- L38 _public prototype_ `virtual bool InitListen(FNetworkNotify* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error) override;`
- L39 _public prototype_ `virtual void TickDispatch(float DeltaTime) override;`
- L40 _public prototype_ `virtual void LowLevelSend(TSharedPtr<const FInternetAddr> Address, void* Data, int32 CountBits, FOutPacketTraits& Traits) override;`
- L41 _public prototype_ `virtual void LowLevelDestroy() override;`
- L42 _public prototype_ `virtual class ISocketSubsystem* GetSocketSubsystem() override;`
- L43 _public prototype_ `virtual bool IsNetResourceValid(void) override;`
- L46 _public prototype_ `bool ArePacketHandlersDisabled() const;`
- L49 _protected member_ `class FSteamSocket* Socket;`
- L50 _protected member_ `bool bIsDelayedNetworkAccess;`
- L52 _protected prototype_ `void ResetSocketInfo(const class FSteamSocket* RemovedSocket);`
- L54 _protected prototype_ `UNetConnection* FindClientConnectionForHandle(SteamSocketHandles SocketHandle);`
- L56 _protected prototype_ `void OnConnectionCreated(SteamSocketHandles ListenParentHandle, SteamSocketHandles SocketHandle);`
- L57 _protected prototype_ `void OnConnectionUpdated(SteamSocketHandles SocketHandle, int32 NewState);`
- L58 _protected prototype_ `void OnConnectionDisconnected(SteamSocketHandles SocketHandle);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API STEAMSOCKETS_API`

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Public/SteamSocketsPackage.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define PACKAGE_SCOPE public`
- L14 _macro_ `#define PACKAGE_SCOPE protected`

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Public/SteamSocketsSubsystem.h` (Public)


#### class `FSteamSocketsSubsystem`  
`class FSteamSocketsSubsystem : public ISocketSubsystem, public FTSTickerObjectBase, public FSelfRegisteringExec`  
_L28-205_
- inherits: `ISocketSubsystem,FTSTickerObjectBase,FSelfRegisteringExec`
- desc: Steam Sockets specific socket subsystem implementation. This class can only be used with the SteamSocketsNetDriver and the SteamSocketsNetConnection classes. This subsystem does not support mixing any other NetDriver/NetConnection format. Doing so will cause this protocol to not function.
- L32 _public function_ `FSteamSocketsSubsystem() : LastSocketError(0), bShouldTestPeek(false), SteamEventManager(nullptr), bUseRelays(true), SteamAPIClientHandle(nullptr), SteamAPIServerHandle(nullptr)`
- L43 _public prototype_ `virtual bool Init(FString& Error) override;`
- L44 _public prototype_ `virtual void Shutdown() override;`
- L46 _public prototype_ `virtual class FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, const FName& ProtocolType) override;`
- L47 _public prototype_ `virtual void DestroySocket(class FSocket* Socket) override;`
- L49 _public prototype_ `virtual FAddressInfoResult GetAddressInfo(const TCHAR* HostName, const TCHAR* ServiceName = nullptr, EAddressInfoFlags QueryFlags = EAddressInfoFlags::Default, const FName ProtocolTypeName = NAME_None, ESocketType SocketType = ESocketType::SOCKTYPE_Unknown) override;`
- L53 _public prototype_ `virtual TSharedPtr<FInternetAddr> GetAddressFromString(const FString& IPAddress) override;`
- L55 _public prototype_ `virtual bool GetHostName(FString& HostName) override;`
- L57 _public prototype_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr() override;`
- L58 _public prototype_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr(const FName RequestedProtocol) override;`
- L60 _public prototype_ `virtual const TCHAR* GetSocketAPIName() const override;`
- L62 _public function_ `virtual ESocketErrors GetLastErrorCode() override`
- L63 _public function_ `virtual ESocketErrors TranslateErrorCode(int32 Code) override`
- L65 _public prototype_ `virtual bool GetLocalAdapterAddresses(TArray<TSharedPtr<FInternetAddr>>& OutAddresses) override;`
- L66 _public prototype_ `virtual TArray<TSharedRef<FInternetAddr>> GetLocalBindAddresses() override;`
- L67 _public function_ `virtual bool HasNetworkDevice() override`
- L68 _public function_ `virtual bool IsSocketWaitSupported() const override`
- L69 _public function_ `virtual bool RequiresChatDataBeSeparate() override`
- L70 _public function_ `virtual bool RequiresEncryptedPackets() override`
- L74 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L78 _public function_ `bool IsUsingRelayNetwork() const` — Returns if the application is using the SteamSocket relays
- L81 _public function_ `bool IsSteamInitialized() const` — Basic function to determine if Steam has been initialized properly.
- L83 _public prototype_ `static class ISteamNetworkingSockets* GetSteamSocketsInterface();`
- L132 _public prototype_ `FSteamSocketInformation* GetSocketInfo(SteamSocketHandles InternalSocketHandle);` — Steam socket queriers
- L133 _public prototype_ `FSteamSocketInformation* GetSocketInfo(const FInternetAddr& ForAddress);`
- L136 _public prototype_ `void AddSocket(const FInternetAddr& ForAddr, FSteamSocket* NewSocket, FSteamSocket* ParentSocket = nullptr);` — Steam socket bookkeeping modifiers
- L137 _public prototype_ `void RemoveSocketsForListener(FSteamSocket* ListenerSocket);`
- L138 _public prototype_ `void QueueRemoval(SteamSocketHandles SocketHandle);`
- L139 _public prototype_ `void LinkNetDriver(FSocket* Socket, USteamSocketsNetDriver* NewNetDriver);`
- L142 _public prototype_ `void AddDelayedListener(FSteamSocket* ListenSocket, USteamSocketsNetDriver* NewNetDriver);` — Delayed listen socket helpers.
- L143 _public prototype_ `void OnServerLoginComplete(bool bWasSuccessful);`
- L146 _public prototype_ `TSharedPtr<FInternetAddr> GetIdentityAddress();` — Returns this machine's identity in the form of a FInternetAddrSteamSockets
- L149 _public prototype_ `bool IsLoggedInToSteam() const;` — Returns if our account is currently logged into the Steam network
- L152 _public member_ `int32 LastSocketError;` — Last error set by the socket subsystem or one of its sockets
- L155 _public prototype_ `static FSteamSocketsSubsystem* Create();` — Singleton helpers
- L156 _public prototype_ `static void Destroy();`
- L159 _public prototype_ `void SteamSocketEventHandler(struct SteamNetConnectionStatusChangedCallback_t* ConnectionEvent);` — SteamAPI internals handler
- L162 _public member_ `bool bShouldTestPeek;` — Flag for testing peek messaging (only usable in non-shipping builds)
- L166 _protected prototype_ `virtual bool Exec_Dev(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L169 _protected prototype_ `void CleanSocketInformation(bool bForceClean);`
- L170 _protected prototype_ `void DumpSocketInformationMap() const;`
- L173 _protected member_ `static FSteamSocketsSubsystem* SocketSingleton;` — Single instantiation of this subsystem
- L176 _protected member_ `TUniquePtr<class FSteamSocketsTaskManagerInterface> SteamEventManager;` — Event manager for Steam tasks
- L179 _protected member_ `bool bUseRelays;` — Determines if the connections are going to be using the relay network
- L182 _protected member_ `TSharedPtr<class FSteamClientInstanceHandler> SteamAPIClientHandle;` — Steam Client API Handle
- L185 _protected member_ `TSharedPtr<class FSteamServerInstanceHandler> SteamAPIServerHandle;` — Steam Server API Handle
- L188 _protected typedef_ `typedef TMap<SteamSocketHandles, FSteamSocketInformation> SocketHandleInfoMap;` — Active connection bookkeeping
- L189 _protected member_ `SocketHandleInfoMap SocketInformationMap;`
- L201 _protected member_ `TArray<FSteamPendingSocketInformation> PendingListenerArray;` — Array of listeners we need to activate.
- L204 _protected member_ `FDelegateHandle SteamServerLoginDelegateHandle;` — Delegate handle for handling when a dedicated server logs into the Steam platform

#### struct `FSteamSocketsSubsystem::FSteamSocketInformation`  
`struct FSteamSocketInformation`  
_L87-129_
- desc: A struct for holding steam socket information and managing bookkeeping on the protocol.
- L89 _public function_ `FSteamSocketInformation(TSharedPtr<FInternetAddr> InAddr, FSteamSocket* InSocket, FSteamSocket* InParent = nullptr) : Addr(InAddr), Socket(InSocket), Parent(InParent), NetDriver(nullptr), bMarkedForDeletion(false)`
- L98 _public prototype_ `void MarkForDeletion();`
- L100 _public function_ `bool IsMarkedForDeletion() const`
- L102 _public function_ `bool operator==(const FSteamSocket* RHS) const`
- L107 _public prototype_ `bool operator==(const FInternetAddr& InAddr) const;`
- L109 _public function_ `bool operator==(const FSteamSocketInformation& RHS) const`
- L114 _public function_ `bool IsValid() const`
- L119 _public prototype_ `FString ToString() const;`
- L121 _public member_ `TSharedPtr<FInternetAddr> Addr;`
- L122 _public member_ `FSteamSocket* Socket;`
- L124 _public member_ `FSteamSocket* Parent;` — Sockets created from a listener have a parent
- L126 _public member_ `TWeakObjectPtr<USteamSocketsNetDriver> NetDriver;` — The NetDriver for this connection.
- L128 _private member_ `bool bMarkedForDeletion;`

#### struct `FSteamSocketsSubsystem::FSteamPendingSocketInformation`  
`struct FSteamPendingSocketInformation`  
_L192-198_
- desc: Structure for handling sockets that cannot be established due to platform login (for listener sockets)
- L194 _public member_ `FSteamSocket* Socket;`
- L195 _public member_ `TWeakObjectPtr<USteamSocketsNetDriver> NetDriver;`
- L197 _public prototype_ `FString ToString() const;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API STEAMSOCKETS_API`

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Public/SteamSocketsTaskManagerInterface.h` (Public)


#### class `FSteamSocketsTaskManagerInterface`  
`class FSteamSocketsTaskManagerInterface`  
_L10-25_
- desc: A base task manager interface for handling messages from the Steamworks SDK to pipe to the SteamSocketsSubsystem This is mostly an empty interface used to allow for creation of uniqueptrs of the task manager interface without exposing Steam data types.
- L13 _public function_ `FSteamSocketsTaskManagerInterface(class FSteamSocketsSubsystem* SocketSub) : SocketSubsystem(SocketSub)`
- L18 _public prototype_ `virtual ~FSteamSocketsTaskManagerInterface() = default;`
- L21 _public prototype_ `virtual void Tick() = 0;` — A function that will be called on every update tick of the SteamSocketsSubsystem
- L24 _protected member_ `class FSteamSocketsSubsystem* SocketSubsystem;`

### `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Public/SteamSocketsTypes.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define STEAM_SOCKETS_SUBSYSTEM FName(TEXT("SteamSockets"))`
- L11 _typedef_ `typedef uint32 SteamSocketHandles;`
