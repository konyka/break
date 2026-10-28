# Plugins / SocketSubsystemEOS

- module root: `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS`
- headers: 8; symbols: 169
- symbol kinds: class=8, delegate=1, function=12, macro=4, member=24, prototype=116, typedef=4
- PrivateDependencyModuleNames: CoreOnline, CoreUObject, EOSSDK, EOSShared
- PublicDependencyModuleNames: Core, EOSShared, Engine, NetCore, OnlineSubsystemUtils, Sockets

### `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS/Private/NetConnectionEOS.h` (Private)


#### class `UNetConnectionEOS`  
`class UNetConnectionEOS : public UIpConnection`  
_L11-32_
- reflection: `UCLASS(MinimalAPI, Transient, Config=Engine)`
- inherits: `UIpConnection`
- L17 _public prototype_ `explicit UNetConnectionEOS(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual void InitLocalConnection(UNetDriver* InDriver, FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L21 _public prototype_ `virtual void InitRemoteConnection(UNetDriver* InDriver, FSocket* InSocket, const FURL& InURL, const FInternetAddr& InRemoteAddr, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;`
- L22 _public prototype_ `virtual void CleanUp() override;`
- L25 _public prototype_ `void DestroyEOSConnection();`
- L28 _public member_ `bool bIsPassthrough;`
- L31 _protected member_ `bool bHasP2PSession;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SOCKETSUBSYSTEMEOS_API`

### `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS/Private/SocketSubsystemEOSModule.h` (Private)


#### class `FSocketSubsystemEOSModule`  
`class FSocketSubsystemEOSModule: public IModuleInterface`  
_L7-18_
- inherits: `IModuleInterface`
- L10 _public prototype_ `FSocketSubsystemEOSModule() = default;`
- L11 _public prototype_ `~FSocketSubsystemEOSModule() = default;`
- L15 _private prototype_ `virtual void StartupModule() override;`
- L16 _private prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS/Public/InternetAddrEOS.h` (Public)


#### class `FInternetAddrEOS`  
`class FInternetAddrEOS : public FInternetAddr`  
_L20-123_
- inherits: `FInternetAddr`
- L24 _public prototype_ `FInternetAddrEOS();`
- L27 _public prototype_ `FInternetAddrEOS(const FString& InRemoteUserId, const FString& InSocketName, const int32 InChannel);` — `UE_DEPRECATED(5.6, "InSocketName and InChannel have been removed from FInternetAddrEOS, please use the new constructor.")`
- L28 _public prototype_ `FInternetAddrEOS(const FString& InRemoteUserId);`
- L31 _public prototype_ `FInternetAddrEOS(const EOS_ProductUserId InRemoteUserId, const FString& InSocketName, const int32 InChannel);` — `UE_DEPRECATED(5.6, "InSocketName and InChannel have been removed from FInternetAddrEOS, please use the new constructor.")`
- L32 _public prototype_ `FInternetAddrEOS(const EOS_ProductUserId InRemoteUserId);`
- L34 _public prototype_ `FInternetAddrEOS(void* const InRemoteUserId);`
- L36 _public prototype_ `virtual ~FInternetAddrEOS() = default;`
- L39 _public prototype_ `virtual void SetIp(uint32 InAddr) override;`
- L40 _public prototype_ `virtual void SetIp(const TCHAR* InAddr, bool& bIsValid) override;`
- L41 _public prototype_ `virtual void GetIp(uint32& OutAddr) const override;`
- L42 _public prototype_ `virtual bool IsPortValid(int32 InPort) const override;`
- L43 _public prototype_ `virtual void SetPort(int32 InPort) override;`
- L44 _public prototype_ `virtual int32 GetPort() const override;`
- L45 _public prototype_ `virtual void SetRawIp(const TArray<uint8>& RawAddr) override;`
- L46 _public prototype_ `virtual TArray<uint8> GetRawIp() const override;`
- L47 _public prototype_ `virtual void SetAnyAddress() override;`
- L48 _public prototype_ `virtual void SetBroadcastAddress() override;`
- L49 _public prototype_ `virtual void SetLoopbackAddress() override;`
- L50 _public prototype_ `virtual FString ToString(bool bAppendPort) const override;`
- L51 _public prototype_ `virtual uint32 GetTypeHash() const override;`
- L52 _public prototype_ `virtual bool IsValid() const override;`
- L53 _public prototype_ `virtual TSharedRef<FInternetAddr> Clone() const override;`
- L54 _public prototype_ `virtual FName GetProtocolType() const override;`
- L57 _public function_ `inline FInternetAddrEOS& operator=(const FInternetAddrEOS& Other)`
- L63 _public function_ `inline virtual bool operator==(const FInternetAddr& Other) const override`
- L94 _public function_ `void SetProductUserId(EOS_ProductUserId InProductUserId)`
- L99 _public function_ `EOS_ProductUserId GetProductUserId() const`
- L104 _public function_ `void SetProductUserId(void* InProductUserId)`
- L109 _public function_ `void* GetProductUserId() const`
- L117 _private member_ `EOS_ProductUserId ProductUserId;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSocketSubsystemEOS, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSocketSubsystemEOS, Log, All);`
- L18 _macro_ `#define EOS_SOCKET_NAME_SIZE 33`
- L73 _function_ `inline friend bool operator==(const FInternetAddrEOS& A, const FInternetAddrEOS& B)`
- L78 _function_ `inline friend bool operator!=(const FInternetAddrEOS& A, const FInternetAddrEOS& B)`
- L83 _function_ `inline friend uint32 GetTypeHash(const FInternetAddrEOS& Address)`
- L88 _function_ `friend bool operator<(const FInternetAddrEOS& Left, const FInternetAddrEOS& Right)`

### `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS/Public/NetDriverEOS.h` (Public)


#### class `UNetDriverEOS`  
`class UNetDriverEOS : public UIpNetDriver`  
_L14-41_
- reflection: `UCLASS(MinimalAPI, Transient, Config=Engine)`
- inherits: `UIpNetDriver`
- L20 _public prototype_ `UNetDriverEOS(const FObjectInitializer& ObjectInitializer);`
- L23 _public prototype_ `virtual bool IsAvailable() const override;`
- L24 _public prototype_ `virtual bool InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error) override;`
- L25 _public prototype_ `virtual bool InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error) override;`
- L26 _public prototype_ `virtual bool InitListen(FNetworkNotify* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error) override;`
- L27 _public prototype_ `virtual ISocketSubsystem* GetSocketSubsystem() override;`
- L28 _public prototype_ `virtual void Shutdown() override;`
- L29 _public prototype_ `virtual int GetClientPort() override;`
- L32 _public prototype_ `UWorld* FindWorld() const;`
- L36 _public member_ `bool bIsPassthrough = false;` — `UPROPERTY()`
- L40 _public member_ `bool bIsUsingP2PSockets = true;` — `UE_DEPRECATED(5.6, "bIsUsingP2PSockets is deprecated. All code that used it now operates as if it were true")` — `UPROPERTY(Config, meta=(DeprecatedProperty, DeprecationMessage="This property is obsolete. All code that used it now operates as if it were true"))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SOCKETSUBSYSTEMEOS_API`

### `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS/Public/NetDriverEOSBase.h` (Public)


#### class `UNetDriverEOSBase`  
`class UE_DEPRECATED(5.6, "UNetDriverEOSBase is deprecated, please use UNetDriverEOS") UNetDriverEOSBase : public UNetDriverEOS`  
_L12-18_
- reflection: `UCLASS(Transient, Config=Engine)`
- inherits: `UNetDriverEOS`

### `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS/Public/SocketEOS.h` (Public)


#### class `FSocketEOS`  
`class FSocketEOS : public FSocket`  
_L18-113_
- inherits: `FSocket`
- L22 _public prototype_ `FSocketEOS(FSocketSubsystemEOS& SocketSubsystem, const FString& InSocketDescription);`
- L23 _public prototype_ `virtual ~FSocketEOS();`
- L26 _public prototype_ `virtual bool Shutdown(ESocketShutdownMode Mode) override;`
- L27 _public prototype_ `virtual bool Close() override;`
- L28 _public prototype_ `virtual bool Bind(const FInternetAddr& Addr) override;`
- L29 _public prototype_ `virtual bool Connect(const FInternetAddr& Addr) override;`
- L30 _public prototype_ `virtual bool Listen(int32 MaxBacklog) override;`
- L31 _public prototype_ `virtual bool WaitForPendingConnection(bool& bHasPendingConnection, const FTimespan& WaitTime) override;`
- L32 _public prototype_ `virtual bool HasPendingData(uint32& PendingDataSize) override;`
- L33 _public prototype_ `virtual class FSocket* Accept(const FString& InSocketDescription) override;`
- L34 _public prototype_ `virtual class FSocket* Accept(FInternetAddr& OutAddr, const FString& InSocketDescription) override;`
- L35 _public prototype_ `virtual bool SendTo(const uint8* Data, int32 Count, int32& BytesSent, const FInternetAddr& Destination) override;`
- L36 _public prototype_ `virtual bool Send(const uint8* Data, int32 Count, int32& BytesSent) override;`
- L37 _public prototype_ `virtual bool RecvFrom(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;`
- L38 _public prototype_ `virtual bool Recv(uint8* Data, int32 BufferSize, int32& BytesRead, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;`
- L39 _public prototype_ `virtual bool Wait(ESocketWaitConditions::Type Condition, FTimespan WaitTime) override;`
- L40 _public prototype_ `virtual ESocketConnectionState GetConnectionState() override;`
- L41 _public prototype_ `virtual void GetAddress(FInternetAddr& OutAddr) override;`
- L42 _public prototype_ `virtual bool GetPeerAddress(FInternetAddr& OutAddr) override;`
- L43 _public prototype_ `virtual bool SetNonBlocking(bool bIsNonBlocking = true) override;`
- L44 _public prototype_ `virtual bool SetBroadcast(bool bAllowBroadcast = true) override;`
- L45 _public prototype_ `virtual bool SetNoDelay(bool bIsNoDelay = true) override;`
- L46 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress) override;`
- L47 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress) override;`
- L48 _public prototype_ `virtual bool SetMulticastLoopback(bool bLoopback) override;`
- L49 _public prototype_ `virtual bool SetMulticastTtl(uint8 TimeToLive) override;`
- L50 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;`
- L51 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;`
- L52 _public prototype_ `virtual bool SetMulticastInterface(const FInternetAddr& InterfaceAddress) override;`
- L53 _public prototype_ `virtual bool SetReuseAddr(bool bAllowReuse = true) override;`
- L54 _public prototype_ `virtual bool SetLinger(bool bShouldLinger = true, int32 Timeout = 0) override;`
- L55 _public prototype_ `virtual bool SetRecvErr(bool bUseErrorQueue = true) override;`
- L56 _public prototype_ `virtual bool SetSendBufferSize(int32 Size, int32& NewSize) override;`
- L57 _public prototype_ `virtual bool SetReceiveBufferSize(int32 Size, int32& NewSize) override;`
- L58 _public prototype_ `virtual int32 GetPortNo() override;`
- L61 _public prototype_ `void SetLocalAddress(const FInternetAddrEOS& InLocalAddress);`
- L63 _public prototype_ `void SetSocketName(const FString& InSocketName);`
- L65 _public prototype_ `bool Close(const FInternetAddrEOS& RemoteAddress);`
- L67 _public function_ `bool WasClosed(const FInternetAddrEOS& RemoteAddress)`
- L73 _public prototype_ `void RegisterClosedNotification();`
- L78 _private prototype_ `void OnNetworkStatusChanged(EOS_ENetworkStatus OldNetworkStatus, EOS_ENetworkStatus NewNetworkStatus);` — Rebind connection request handler when network goes from offline to online, and cleanup objects when network goes from online to offline
- L81 _private member_ `TSharedPtr<FCallbackBase> CallbackAliveTracker;` — Used to track our aliveness and make it possible to use the callback interface
- L84 _private member_ `FSocketSubsystemEOS& SocketSubsystem;` — Reference to our subsystem
- L87 _private member_ `FInternetAddrEOS LocalAddress;` — Our local address; session/port will be invalid when not bound
- L90 _private member_ `FString SocketName;` — Name of the NetDriver that will use the socket
- L93 _private member_ `bool bIsListening;` — Are we currently listening?
- L95 _private member_ `TArray<FInternetAddrEOS> ClosedRemotes;`
- L98 _private typedef_ `typedef TEOSGlobalCallback<EOS_P2P_OnIncomingConnectionRequestCallback, EOS_P2P_OnIncomingConnectionRequestInfo, FCallbackBase> FConnectNotifyCallback;`
- L99 _private typedef_ `typedef TEOSGlobalCallback<EOS_P2P_OnRemoteConnectionClosedCallback, EOS_P2P_OnRemoteConnectionClosedInfo, FCallbackBase> FClosedNotifyCallback;`
- L101 _private member_ `FConnectNotifyCallback* ConnectNotifyCallback;`
- L102 _private member_ `EOS_NotificationId ConnectNotifyId;`
- L104 _private member_ `FClosedNotifyCallback* ClosedNotifyCallback;`
- L105 _private member_ `EOS_NotificationId ClosedNotifyId;`
- L108 _private member_ `EOS_EPacketReliability PacketReliability = EOS_EPacketReliability::EOS_PR_UnreliableUnordered;` — Default packet reliability type used in EOS_P2P_SendPacketOptions
- L111 _private member_ `FDelegateHandle NetworkStatusChangedDelegateHandle;` — Delegate fired when the EOS SDK network status changes

### `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS/Public/SocketSubsystemEOS.h` (Public)


#### class `FSocketSubsystemEOS`  
`class FSocketSubsystemEOS : public ISocketSubsystem`  
_L33-124_
- inherits: `ISocketSubsystem`
- L37 _public prototype_ `FSocketSubsystemEOS(IEOSPlatformHandlePtr InPlatformHandle, ISocketSubsystemEOSUtilsPtr InUtils);`
- L38 _public prototype_ `virtual ~FSocketSubsystemEOS();`
- L41 _public prototype_ `virtual bool Init(FString& Error) override;`
- L42 _public prototype_ `virtual void Shutdown() override;`
- L43 _public prototype_ `virtual FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, const FName& ProtocolType) override;`
- L44 _public prototype_ `virtual FResolveInfoCached* CreateResolveInfoCached(TSharedPtr<FInternetAddr> Addr) const override;`
- L45 _public prototype_ `virtual void DestroySocket(FSocket* Socket) override;`
- L46 _public prototype_ `virtual FAddressInfoResult GetAddressInfo(const TCHAR* HostName, const TCHAR* ServiceName = nullptr, EAddressInfoFlags QueryFlags = EAddressInfoFlags::Default, const FName ProtocolTypeName = NAME_None, ESocketType SocketType = ESocketType::SOCKTYPE_Unknown) override;`
- L47 _public prototype_ `virtual bool RequiresChatDataBeSeparate() override;`
- L48 _public prototype_ `virtual bool RequiresEncryptedPackets() override;`
- L49 _public prototype_ `virtual bool GetHostName(FString& HostName) override;`
- L50 _public prototype_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr() override;`
- L51 _public prototype_ `virtual TSharedPtr<FInternetAddr> GetAddressFromString(const FString& InString) override;`
- L52 _public prototype_ `virtual bool HasNetworkDevice() override;`
- L53 _public prototype_ `virtual const TCHAR* GetSocketAPIName() const override;`
- L54 _public prototype_ `virtual ESocketErrors GetLastErrorCode() override;`
- L55 _public prototype_ `virtual ESocketErrors TranslateErrorCode(int32 Code) override;`
- L56 _public prototype_ `virtual bool GetLocalAdapterAddresses(TArray<TSharedPtr<FInternetAddr>>& OutAdresses) override;`
- L57 _public prototype_ `virtual TSharedRef<FInternetAddr> GetLocalBindAddr(FOutputDevice& Out) override;`
- L58 _public prototype_ `virtual TArray<TSharedRef<FInternetAddr>> GetLocalBindAddresses() override;`
- L59 _public prototype_ `TSharedRef<FInternetAddr> GetLocalBindAddr(const UWorld* const OwningWorld, FOutputDevice& Out);`
- L60 _public prototype_ `virtual bool IsSocketWaitSupported() const override;`
- L63 _public prototype_ `void SetLastSocketError(const ESocketErrors NewSocketError);`
- L66 _public prototype_ `EOS_HP2P GetP2PHandle();`
- L67 _public prototype_ `EOS_ProductUserId GetLocalUserId();`
- L75 _public prototype_ `bool BindSocketName(const FString& SocketName);` — Bind our socket name and ensure no other connections are using this combination @return True if we bound successfully, false if not and LastSocketError will be set with a reason
- L82 _public prototype_ `bool UnbindSocketName(const FString& SocketName);` — Unbind a previously bound socket name. @return True if we released the port successfully, false if not and LastSocketError will be set with a reason
- L91 _public prototype_ `FSocketSubsystemEOS* GetSocketSubsystemForWorld(UWorld* InWorld);` — Returns the FSocketSubsytemEOS instance corresponding with the UWorld* parameter. If no entry exists for the given UWorld*, it will add it if a valid instance is found. @param InWorld UWorld* to be used in the search @return The FSocketSubsystemEOS instance associated with InWorld
- L98 _public function_ `ISocketSubsystemEOSUtilsPtr GetSocketSubsystemEOSUtils()` — Returns the utils for this SocketSubsystemEOS @return The ISocketSubsystemEOSUtilsPtr for this SocketSubsystemEOS
- L102 _private prototype_ `void RemoveFromStaticContainers();` — Removes the FSocketSubsystemEOS instance from SocketSubsystemEOSInstances and all related entries from SocketSubsystemEOSPerWorldMap
- L106 _private member_ `EOS_HP2P P2PHandle = nullptr;`
- L108 _private member_ `ISocketSubsystemEOSUtilsPtr Utils;`
- L111 _private member_ `TArray<TUniquePtr<FSocketEOS>> TrackedSockets;` — All sockets allocated by this subsystem
- L114 _private member_ `TSet<FString> BoundSocketNames;` — All bound socket names
- L117 _private member_ `ESocketErrors LastSocketError;` — The last error we received
- L120 _private member_ `static TArray<FSocketSubsystemEOS*> SocketSubsystemEOSInstances;` — Static array of all instances of FSocketSubsystemEOS running concurrently (can be more than one in PIE)
- L123 _private member_ `static TMap<UWorld*, FSocketSubsystemEOS*> SocketSubsystemEOSPerWorldMap;` — Static map of world to corresponding FSocketSubsystemeOS instance

#### Free symbols / members of external scopes

- L20 _macro_ `#define EOS_SOCKETSUBSYSTEM FName(TEXT("EOS"))`
- L31 _typedef_ `typedef TSet<uint8> FChannelSet;`

### `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS/Public/SocketSubsystemEOSUtils.h` (Public)


#### class `ISocketSubsystemEOSUtils`  
`class ISocketSubsystemEOSUtils`  
_L16-29_
- L19 _public prototype_ `virtual ~ISocketSubsystemEOSUtils() = default;`
- L22 _public prototype_ `virtual EOS_ProductUserId GetLocalUserId() = 0;`
- L24 _public prototype_ `virtual FString GetSessionId() = 0;`
- L26 _public prototype_ `virtual FName GetSubsystemInstanceName() = 0;`
- L28 _public prototype_ `virtual bool IsLoggedIn() = 0;`

#### Free symbols / members of external scopes

- L30 _typedef_ `typedef TSharedPtr<ISocketSubsystemEOSUtils, ESPMode::ThreadSafe> ISocketSubsystemEOSUtilsPtr;`
