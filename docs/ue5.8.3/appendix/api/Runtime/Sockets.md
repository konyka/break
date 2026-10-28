# Runtime / Sockets

- module root: `Source/Runtime/Sockets`
- headers: 30; symbols: 682
- symbol kinds: class=30, delegate=2, enum=19, enumerator=78, externvar=3, function=126, macro=13, member=88, namespace=5, prototype=297, struct=11, typedef=10
- PrivateDependencyModuleNames: Core, NetCommon
- PublicIncludePathModuleNames: NetCommon

### `Source/Runtime/Sockets/Private/Android/SocketSubsystemAndroid.h` (Private)


#### class `FSocketSubsystemAndroid`  
`class FSocketSubsystemAndroid : public FSocketSubsystemBSD`  
_L12-90_
- inherits: `FSocketSubsystemBSD`
- desc: Android specific socket subsystem implementation
- L17 _protected member_ `static FSocketSubsystemAndroid* SocketSingleton;` — Single instantiation of this subsystem
- L20 _protected member_ `bool bTriedToInit;` — Whether Init() has been called before or not
- L25 _protected prototype_ `virtual class FSocketBSD* InternalBSDSocketFactory( SOCKET Socket, ESocketType SocketType, const FString& SocketDescription, const FName& SocketProtocol) override;` — Create a FSocketBSD sub class capable of acquiring WifiManager.MulticastLock if needed.
- L35 _public prototype_ `static FSocketSubsystemAndroid* Create();` — Singleton interface for this subsystem @return the only instance of this subsystem
- L40 _public prototype_ `static void Destroy();` — Performs Android specific socket clean up
- L44 _public function_ `FSocketSubsystemAndroid() : bTriedToInit(false)`
- L49 _public prototype_ `virtual ~FSocketSubsystemAndroid() = default;`
- L58 _public prototype_ `virtual bool Init(FString& Error) override;` — Does Android platform initialization of the sockets library @param Error a string that is filled with error information @return TRUE if initialized ok, FALSE otherwise
- L63 _public prototype_ `virtual void Shutdown() override;` — Performs platform specific socket clean up
- L68 _public prototype_ `virtual bool HasNetworkDevice() override;` — @return Whether the device has a properly configured network device or not
- L74 _public prototype_ `virtual const TCHAR* GetSocketAPIName() const override;` — Get the name of the socket subsystem @return a string naming this subsystem
- L80 _public prototype_ `virtual int32 GetAddressInfoHintFlag(EAddressInfoFlags InFlags) const override;`
- L82 _public prototype_ `virtual FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, const FName& ProtocolType) override;`
- L84 _public prototype_ `virtual bool GetLocalAdapterAddresses(TArray<TSharedPtr<FInternetAddr>>& OutAddresses) override;`
- L86 _public function_ `virtual FName GetDefaultSocketProtocolFamily() const override`

### `Source/Runtime/Sockets/Private/Android/SocketsAndroid.h` (Private)


#### class `FSocketAndroid`  
`class FSocketAndroid : public FSocketBSD`  
_L7-26_
- inherits: `FSocketBSD`
- L17 _public prototype_ `virtual bool SetBroadcast(bool bAllowBroadcast = true) override;` — FSocket overrides already overriden by FSocketBSD Those will wrap the FSocketBSD implementation and acquire the multicast lock if needed
- L18 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress) override;`
- L19 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;`
- L22 _private prototype_ `void AcquireMulticastLock();`
- L23 _private prototype_ `void ReleaseMulticastLock();`
- L25 _private member_ `bool bIsMulticastLockAcquired = false;`

### `Source/Runtime/Sockets/Private/BSDSockets/IPAddressBSD.h` (Private)


#### class `FInternetAddrBSD`  
`class FInternetAddrBSD : public FInternetAddr`  
_L19-299_
- inherits: `FInternetAddr`
- desc: Represents an internet ip address with support for ipv4/v6. All data is in network byte order
- L22 _private member_ `sockaddr_storage Addr;` — The internet ip address structure
- L26 _protected member_ `FSocketSubsystemBSD* SocketSubsystem;` — The Subsystem that created this address
- L28 _protected prototype_ `void Clear();`
- L29 _protected prototype_ `void ResetScopeId();`
- L50 _protected function_ `virtual void SetIp(const in6_addr& IPv6Addr)` — Sets the ip address using a network byte order ipv6 address @param IpAddr the new ip address to use
- L61 _public prototype_ `FInternetAddrBSD();` — Constructor. Sets address to default state
- L63 _public prototype_ `FInternetAddrBSD(FSocketSubsystemBSD* InSocketSubsystem, FName RequestedProtocol=NAME_None);`
- L73 _public prototype_ `virtual bool CompareEndpoints(const FInternetAddr& InAddr) const override;` — Compares FInternetAddrs together, comparing the logical net addresses (endpoints) of the data stored, rather than doing a memory comparison like the equality operator does. @Param InAddr The address to compare with. @return true if the endpoint stored in this FInternetAddr is the same as the input.
- L80 _public prototype_ `virtual void SetRawIp(const TArray<uint8>& RawAddr) override;` — Sets the ip address from a raw network byte order array. @param RawAddr the new address to use (must be converted to network byte order)
- L87 _public prototype_ `virtual TArray<uint8> GetRawIp() const override;` — Gets the ip address in a raw array stored in network byte order. @return The raw address stored in an array
- L95 _public prototype_ `virtual void SetIp(uint32 InAddr) override;` — Sets the ip address from a host byte order uint32. Will attempt to determine platform compatibility for best way to store address @param InAddr the new address to use (must convert to network byte order)
- L107 _public prototype_ `virtual void SetIp(const TCHAR* InAddr, bool& bIsValid) override;` — Sets the ip address from a string IPv6 or IPv4 address. Ports may be included using the form Address:Port, or excluded and set manually. IPv6 - [1111:2222:3333:4444:5555:6666:7777:8888]:PORT || [1111:2222:3333::]:PORT || [::ffff:IPv4]:PORT || any of these without the brackets and port IPv4 - aaa.bbb.ccc.ddd:PORT || 127.0.0.1:PORT @param InAddr the string containing the new ip address to use @param bIsValid will be set to true if InAddr was a valid IPv6 or IPv4 address, false if not.
- L114 _public prototype_ `void SetIp(const sockaddr_storage& IpAddr);` — Sets the ip address using a generic sockaddr_storage @param IpAddr the new ip address to use (assumes already in the correct byte order).
- L122 _public prototype_ `virtual void Set(const sockaddr_storage& AddrData);` — Sets the address data via a sockaddr_storage Can only really safely set with a sockaddr_storage @param AddrData the new data to use
- L131 _public prototype_ `virtual void Set(const sockaddr_storage& AddrData, SOCKLEN AddrSize);` — Sets the address data via a sockaddr_storage. Uses memcpy to assign the data. @param AddrData the new data to use @param AddrSize size of the addr data being passed in.
- L139 _public function_ `void GetIp(in6_addr& OutAddr) const` — Copies the network byte order ip address @param OutAddr the out param receiving the ip address
- L155 _public function_ `void GetIp(in_addr& OutAddr) const` — Copies the network byte order ip address @param OutAddr the out param receiving the ip address
- L171 _public prototype_ `virtual void GetIp(uint32& OutAddr) const override;` — Copies the network byte order ip address to a host byte order dword. Does nothing if we are currently not storing an ipv4 addr in some capacity @param OutAddr the out param receiving the ip address
- L173 _public function_ `sockaddr_storage* GetRawAddr()`
- L183 _public prototype_ `virtual void SetPort(int32 InPort) override;` — Sets the port number from a host byte order int @param InPort the new port to use (must convert to network byte order)
- L186 _public prototype_ `virtual bool IsPortValid(int32 InPort) const override;` — Report whether the port is in a valid range for SetPort.
- L189 _public prototype_ `virtual int32 GetPort() const override;` — Returns the port number from this address in host byte order
- L198 _public prototype_ `virtual void SetAnyAddress() override;` — Sets the address structure to be bindable to any IP address. Uses the protocol the address structure was created with (or currently set to) to determine the address protocol type used. To skip assumptions, you can call the designated version explicitly below.
- L201 _public prototype_ `virtual void SetAnyIPv4Address();` — Explicit set to any IPv4 address
- L204 _public prototype_ `virtual void SetAnyIPv6Address();` — Explicit set to any IPv6 address
- L213 _public prototype_ `virtual void SetBroadcastAddress() override;` — Sets the address structure to be bound to the multicast ip address. Uses the protocol the address structure was created with (or currently set to) to determine the address protocol type used. To skip assumptions, you can call the designated version explicitly below.
- L216 _public prototype_ `virtual void SetIPv4BroadcastAddress();` — Explicit set to multicast IPv4 address
- L219 _public prototype_ `virtual void SetIPv6BroadcastAddress();` — Explicit set to multicast IPv6 address
- L228 _public prototype_ `virtual void SetLoopbackAddress() override;` — Sets the address structure to be bound to the loopback ip address. Uses the protocol the address structure was created with (or currently set to) to determine the address protocol type used. To skip assumptions, you can call the designated version explicitly below.
- L231 _public prototype_ `virtual void SetIPv4LoopbackAddress();` — Explicit set to loopback IPv4 address
- L234 _public prototype_ `virtual void SetIPv6LoopbackAddress();` — Explicit set to loopback IPv6 address
- L241 _public prototype_ `virtual FString ToString(bool bAppendPort) const override;` — Converts this internet ip address to string form. String will be enclosed in square braces. @param bAppendPort whether to append the port information or not
- L248 _public prototype_ `virtual bool operator==(const FInternetAddr& Other) const override;` — Compares two internet ip addresses for equality @param Other the address to compare against
- L255 _public prototype_ `virtual bool IsValid() const override;` — Is this a well formed internet address, the only criteria being non-zero @return true if a valid IP, false otherwise
- L262 _public prototype_ `virtual TSharedRef<FInternetAddr> Clone() const override;` — Creates a new structure with the same data as this structure @return The new structure
- L269 _public prototype_ `virtual FName GetProtocolType() const override;` — Returns the protocol family of the address data currently stored in this struct @return The type of the address. If it's not known or overridden, the address passes None.
- L277 _public prototype_ `virtual SOCKLEN GetStorageSize() const;` — Returns the size of the amount of data that is being used to hold the address information. Useful for functions like bind/connect @return size of addr
- L286 _public prototype_ `virtual void SetScopeId(uint32 NewScopeId);` — Sets the scope interface id of the currently held address if this address is an IPv6 address internally. If it is not, no data will be assigned. The NewScopeId must be in host byte order. @param NewScopeId the new scope interface id to set this address to
- L294 _public prototype_ `virtual uint32 GetScopeId() const;` — Returns the IPv6 scope interface id of the currently held address if the address is an IPv6 address. @return the scope interface id
- L296 _public prototype_ `virtual uint32 GetTypeHash() const override;`

### `Source/Runtime/Sockets/Private/BSDSockets/SocketSubsystemBSD.h` (Private)


#### class `FSocketSubsystemBSD`  
`class FSocketSubsystemBSD : public ISocketSubsystem`  
_L22-145_
- inherits: `ISocketSubsystem`
- desc: Standard BSD specific socket subsystem implementation
- L35 _public function_ `virtual FName GetDefaultSocketProtocolFamily() const` — Specifies the default socket protocol family to use when creating a socket without explicitly passing in the protocol type on creation. This function is mostly here for backwards compatibility. For best practice, moving to the new CreateSocket that takes a protocol is advised. All sockets created using the base class's CreateSocket will use this function to determine domain.
- L42 _public prototype_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr() override;` — ISocketSubsystem interface
- L43 _public prototype_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr(const FName ProtocolType) override;`
- L45 _public function_ `virtual class FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, bool bForceUDP = false) override`
- L50 _public prototype_ `virtual class FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, const FName& ProtocolType) override;`
- L52 _public prototype_ `virtual void DestroySocket( class FSocket* Socket ) override;`
- L54 _public prototype_ `virtual FAddressInfoResult GetAddressInfo(const TCHAR* HostName, const TCHAR* ServiceName = nullptr, EAddressInfoFlags QueryFlags = EAddressInfoFlags::Default, const FName ProtocolTypeName = NAME_None, ESocketType SocketType = ESocketType::SOCKTYPE_Unknown) override;`
- L59 _public prototype_ `virtual TSharedPtr<FInternetAddr> GetAddressFromString(const FString& InAddress) override;`
- L61 _public prototype_ `virtual bool GetMultihomeAddress(TSharedRef<FInternetAddr>& Addr) override;`
- L63 _public prototype_ `virtual bool GetHostName(FString& HostName) override;`
- L64 _public prototype_ `virtual ESocketErrors GetLastErrorCode() override;`
- L66 _public prototype_ `virtual const TCHAR* GetSocketAPIName() const override;`
- L68 _public function_ `virtual bool RequiresChatDataBeSeparate() override`
- L73 _public function_ `virtual bool RequiresEncryptedPackets() override`
- L78 _public prototype_ `virtual ESocketErrors TranslateErrorCode( int32 Code ) override;`
- L80 _public prototype_ `virtual bool IsSocketWaitSupported() const override;`
- L82 _public prototype_ `virtual TSharedRef<FInternetAddr> GetLocalHostAddr(FOutputDevice& Out, bool& bCanBindAll) override;`
- L88 _public prototype_ `virtual int32 GetProtocolFamilyValue(ESocketProtocolFamily InProtocol) const;` — `UE_DEPRECATED(4.23, "Switch to the FName version for scalable protocol support")` — Translates an ESocketProtocolFamily code into a value usable by raw socket apis.
- L89 _public prototype_ `virtual int32 GetProtocolFamilyValue(const FName& InProtocol) const;`
- L94 _public prototype_ `virtual const FName GetProtocolFamilyTypeName(int32 InProtocol) const;` — Translates an raw socket family type value into a protocol name that can be used by the network layer.
- L97 _public prototype_ `virtual ESocketProtocolFamily GetProtocolFamilyType(int32 InProtocol) const;` — `UE_DEPRECATED(4.23, "Use GetProtocolFamilyTypeName")`
- L103 _public prototype_ `virtual ESocketType GetSocketType(int32 InSocketType) const;` — Translates an raw socket protocol type value into an enum that can be used by the network layer.
- L108 _public prototype_ `virtual int32 GetAddressInfoHintFlag(EAddressInfoFlags InFlags) const;` — Translates an ESocketAddressInfoFlags into a value usable by getaddrinfo
- L113 _public prototype_ `void QuerySocketStateMany(TArrayView<FSocket*> Sockets, TArray<ESocketStateFlags>& InOutSocketStates, FTimespan WaitTime) const override;` — Polls multiple sockets for readability, writability, and error states using poll() or select(). InOutSocketStates is used as both input (requested flags) and output (resulting flags).
- L119 _protected prototype_ `ESocketErrors TranslateGAIErrorCode(int32 Code) const;` — Translates return values of getaddrinfo() to socket error enum
- L124 _protected prototype_ `virtual class FSocketBSD* InternalBSDSocketFactory( SOCKET Socket, ESocketType SocketType, const FString& SocketDescription, const FName& SocketProtocol);` — Allows a subsystem subclass to create a FSocketBSD sub class.
- L130 _protected function_ `virtual class FSocketBSD* InternalBSDSocketFactory(SOCKET Socket, ESocketType SocketType, const FString& SocketDescription)` — `UE_DEPRECATED(4.22, "To support multiple stack types, move to the constructor that allows for specifying the protocol stack to initialize the socket on.")` — Allows a subsystem subclass to create a FSocketBSD sub class.
- L141 _protected prototype_ `bool GetLocalHostAddrViaConnect(TSharedRef<FInternetAddr>& HostAddr);` — Helper function that attempts to determine the host address via socket connect @param HostAddr The address if successful @return true if successful, false otherwise

#### Free symbols / members of external scopes

- L15 _externvar_ `extern TAutoConsoleVariable<int32> CVarDisableIPv6;`

### `Source/Runtime/Sockets/Private/BSDSockets/SocketSubsystemBSDPrivate.h` (Private)


#### Free symbols / members of external scopes

- L14 _typedef_ `typedef int32 SOCKLEN;`
- L32 _macro_ `#define USE_SOCKET_FEATURE_POLL 1`
- L43 _macro_ `#define ioctlsocket ioctl`
- L46 _macro_ `#define SOCKET_ERROR -1`
- L47 _macro_ `#define INVALID_SOCKET -1`
- L49 _typedef_ `typedef socklen_t SOCKLEN;`
- L50 _typedef_ `typedef int32 SOCKET;`
- L51 _typedef_ `typedef sockaddr_in SOCKADDR_IN;`
- L52 _typedef_ `typedef struct timeval TIMEVAL;`
- L54 _function_ `inline int32 closesocket(SOCKET Socket)`
- L64 _function_ `inline int TranslateFlags(ESocketReceiveFlags::Type Flags)` — Since the flag constants may have different values per-platform, translate into corresponding system constants. For example, MSG_WAITALL is 0x8 on Windows, but 0x100 on other platforms.

### `Source/Runtime/Sockets/Private/BSDSockets/SocketsBSD.h` (Private)


#### enum `ESocketBSDParam`  
`enum class ESocketBSDParam : uint8`  
_L21-26_
- desc: Enumerates BSD socket state parameters.
- L23 _public enumerator_ `CanRead`
- L24 _public enumerator_ `CanWrite`
- L25 _public enumerator_ `HasError`

#### enum `ESocketBSDReturn`  
`enum class ESocketBSDReturn : uint8`  
_L32-37_
- desc: Enumerates BSD socket state return values.
- L34 _public enumerator_ `Yes`
- L35 _public enumerator_ `No`
- L36 _public enumerator_ `EncounteredError`

#### class `FSocketBSD`  
`class FSocketBSD : public FSocket`  
_L43-151_
- inherits: `FSocket`
- desc: Implements a BSD network socket.
- L56 _public function_ `FSocketBSD(SOCKET InSocket, ESocketType InSocketType, const FString& InSocketDescription, const FName& InSocketProtocol, ISocketSubsystem * InSubsystem) : FSocket(InSocketType, InSocketDescription, InSocketProtocol) , Socket(InSocket) , LastActivityTime(0.0) , SocketSubsystem(InSubsystem)` — Assigns a BSD socket to this object. @param InSocket the socket to assign to this object. @param InSocketType the type of socket that was created. @param InSocketDescription the debug description of the socket. @param InSocketProtocol the protocol this socket is initialized with
- L68 _public function_ `virtual ~FSocketBSD()` — Destructor. Closes the socket if it is still open
- L80 _public function_ `SOCKET GetNativeSocket()` — Gets the Socket for anyone who knows they have an FSocketBSD. @return The native socket.
- L89 _public prototype_ `virtual bool Shutdown(ESocketShutdownMode Mode) override;`
- L90 _public prototype_ `virtual bool Close() override;`
- L91 _public prototype_ `virtual bool Bind(const FInternetAddr& Addr) override;`
- L92 _public prototype_ `virtual bool Connect(const FInternetAddr& Addr) override;`
- L93 _public prototype_ `virtual bool Listen(int32 MaxBacklog) override;`
- L94 _public prototype_ `virtual bool WaitForPendingConnection(bool& bHasPendingConnection, const FTimespan& WaitTime) override;`
- L95 _public prototype_ `virtual bool HasPendingData(uint32& PendingDataSize) override;`
- L96 _public prototype_ `virtual class FSocket* Accept(const FString& SocketDescription) override;`
- L97 _public prototype_ `virtual class FSocket* Accept(FInternetAddr& OutAddr, const FString& SocketDescription) override;`
- L98 _public prototype_ `virtual bool SendTo(const uint8* Data, int32 Count, int32& BytesSent, const FInternetAddr& Destination) override;`
- L99 _public prototype_ `virtual bool Send(const uint8* Data, int32 Count, int32& BytesSent) override;`
- L100 _public prototype_ `virtual bool RecvFrom(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;`
- L101 _public prototype_ `virtual bool Recv(uint8* Data,int32 BufferSize,int32& BytesRead, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;`
- L102 _public prototype_ `virtual bool Wait(ESocketWaitConditions::Type Condition, FTimespan WaitTime) override;`
- L103 _public prototype_ `virtual ESocketConnectionState GetConnectionState() override;`
- L104 _public prototype_ `virtual void GetAddress(FInternetAddr& OutAddr) override;`
- L105 _public prototype_ `virtual bool GetPeerAddress(FInternetAddr& OutAddr) override;`
- L106 _public prototype_ `virtual bool SetNonBlocking(bool bIsNonBlocking = true) override;`
- L107 _public prototype_ `virtual bool SetNoDelay(bool bIsNoDelay = true) override;`
- L108 _public prototype_ `virtual bool SetBroadcast(bool bAllowBroadcast = true) override;`
- L109 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress) override;`
- L110 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;`
- L111 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress) override;`
- L112 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;`
- L113 _public prototype_ `virtual bool SetMulticastLoopback(bool bLoopback) override;`
- L114 _public prototype_ `virtual bool SetMulticastTtl(uint8 TimeToLive) override;`
- L115 _public prototype_ `virtual bool SetMulticastInterface(const FInternetAddr& InterfaceAddress) override;`
- L116 _public prototype_ `virtual bool SetReuseAddr(bool bAllowReuse = true) override;`
- L117 _public prototype_ `virtual bool SetLinger(bool bShouldLinger = true, int32 Timeout = 0) override;`
- L118 _public prototype_ `virtual bool SetRecvErr(bool bUseErrorQueue = true) override;`
- L119 _public prototype_ `virtual bool SetSendBufferSize(int32 Size,int32& NewSize) override;`
- L120 _public prototype_ `virtual bool SetReceiveBufferSize(int32 Size,int32& NewSize) override;`
- L121 _public prototype_ `virtual bool SetSendSegmentationOffloadSize(uint16 InSegmentPayloadBytes) override;`
- L122 _public prototype_ `virtual int32 GetPortNo() override;`
- L123 _public prototype_ `virtual bool SetIpPktInfo(bool bEnable) override;`
- L124 _public prototype_ `virtual bool RecvFromWithPktInfo(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, FInternetAddr& Destination, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;`
- L125 _public prototype_ `[[nodiscard]] virtual UPTRINT ReleaseNativeSocket() override;`
- L127 _public prototype_ `bool SetIPv6Only(bool bIPv6Only);`
- L132 _protected prototype_ `virtual ESocketBSDReturn HasState(ESocketBSDParam State, FTimespan WaitTime = FTimespan::Zero());` — This is generally select(), but makes it easier for platforms without select to replace it.
- L135 _protected function_ `FORCEINLINE void UpdateActivity()` — Updates this socket's time of last activity.
- L141 _protected member_ `SOCKET Socket;` — Holds the BSD socket object.
- L144 _protected member_ `std::atomic<double> LastActivityTime { 0.0 };` — Last activity time.
- L147 _protected member_ `int SendFlags = 0;` — Flags which will be passed to send and sendto.
- L150 _protected member_ `ISocketSubsystem* SocketSubsystem;` — Pointer to the subsystem that created it.

### `Source/Runtime/Sockets/Private/IOS/IPAddressBSDIOS.h` (Private)


#### class `FInternetAddrBSDIOS`  
`class FInternetAddrBSDIOS : public FInternetAddrBSD`  
_L12-65_
- inherits: `FInternetAddrBSD`
- L16 _public function_ `FInternetAddrBSDIOS(FSocketSubsystemBSD* InSocketSubsystem, FName RequestedProtocol = NAME_None) : FInternetAddrBSD(InSocketSubsystem, RequestedProtocol)`
- L22 _public function_ `virtual void SetIPv6BroadcastAddress() override` — Sets the address to broadcast

### `Source/Runtime/Sockets/Private/IOS/SocketSubsystemIOS.h` (Private)


#### class `FSocketSubsystemIOS`  
`class FSocketSubsystemIOS : public FSocketSubsystemBSD`  
_L12-62_
- inherits: `FSocketSubsystemBSD`
- desc: iOS specific socket subsystem implementation
- L16 _protected member_ `static FSocketSubsystemIOS* SocketSingleton;` — Single instantiation of this subsystem
- L19 _protected member_ `bool bTriedToInit;` — Whether Init() has been called before or not
- L29 _public prototype_ `static FSocketSubsystemIOS* Create();` — Singleton interface for this subsystem @return the only instance of this subsystem
- L34 _public prototype_ `static void Destroy();` — Performs iOS specific socket clean up
- L37 _public function_ `virtual FName GetDefaultSocketProtocolFamily() const override`
- L44 _public function_ `FSocketSubsystemIOS() : bTriedToInit(false)`
- L49 _public function_ `virtual ~FSocketSubsystemIOS()`
- L53 _public prototype_ `virtual bool Init(FString& Error) override;`
- L54 _public prototype_ `virtual void Shutdown() override;`
- L55 _public prototype_ `virtual bool HasNetworkDevice() override;`
- L56 _public prototype_ `virtual FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, const FName& ProtocolType) override;`
- L57 _public prototype_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr() override;`
- L58 _public prototype_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr(const FName RequiredProtocol) override;`
- L59 _public prototype_ `virtual bool GetLocalAdapterAddresses(TArray<TSharedPtr<FInternetAddr>>& OutAddresses) override;`
- L60 _public prototype_ `virtual TArray<TSharedRef<FInternetAddr>> GetLocalBindAddresses() override;`
- L61 _public prototype_ `virtual class FSocketBSD* InternalBSDSocketFactory(SOCKET Socket, ESocketType SocketType, const FString& SocketDescription, const FName& SocketProtocol) override;`

### `Source/Runtime/Sockets/Private/IOS/SocketsBSDIOS.h` (Private)


#### class `FSocketBSDIOS`  
`class FSocketBSDIOS : public FSocketBSD`  
_L16-53_
- inherits: `FSocketBSD`
- desc: Implements a BSD network socket on IOS.
- L21 _public function_ `FSocketBSDIOS(SOCKET InSocket, ESocketType InSocketType, const FString& InSocketDescription, const FName& InSocketProtocol, ISocketSubsystem* InSubsystem) :FSocketBSD(InSocket, InSocketType, InSocketDescription, InSocketProtocol, InSubsystem)`
- L26 _public function_ `virtual ~FSocketBSDIOS()`
- L31 _public function_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override`
- L43 _public function_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override`

### `Source/Runtime/Sockets/Private/Mac/SocketSubsystemMac.h` (Private)


#### class `FSocketSubsystemMac`  
`class FSocketSubsystemMac : public FSocketSubsystemBSD`  
_L13-72_
- inherits: `FSocketSubsystemBSD`
- desc: Mac specific socket subsystem implementation
- L18 _protected member_ `static FSocketSubsystemMac* SocketSingleton;` — Single instantiation of this subsystem
- L21 _protected member_ `bool bTriedToInit;` — Whether Init() has been called before or not
- L34 _protected prototype_ `static void Destroy();` — Performs Mac specific socket clean up
- L39 _protected prototype_ `virtual class FSocketBSD* InternalBSDSocketFactory(SOCKET Socket, ESocketType SocketType, const FString& SocketDescription, const FName& SocketProtocol);` — Allows a subsystem subclass to create a FSocketBSD sub class
- L43 _public function_ `FSocketSubsystemMac() : bTriedToInit(false)`
- L48 _public function_ `virtual ~FSocketSubsystemMac()`
- L59 _public prototype_ `virtual bool Init(FString& Error) override;` — Does Mac platform initialization of the sockets library @param Error a string that is filled with error information @return true if initialized ok, false otherwise
- L64 _public prototype_ `virtual void Shutdown() override;` — Performs platform specific socket clean up
- L69 _public prototype_ `virtual bool HasNetworkDevice() override;` — @return Whether the machine has a properly configured network device or not
- L71 _public prototype_ `virtual bool GetLocalAdapterAddresses(TArray<TSharedPtr<FInternetAddr>>& OutAddresses) override;`

#### class `FSocketMac`  
`class FSocketMac : public FSocketBSD`  
_L77-103_
- inherits: `FSocketBSD`
- desc: Mac specific socket implementation
- L88 _public function_ `FSocketMac(SOCKET InSocket, ESocketType InSocketType, const FString& InSocketDescription, const FName& InSocketProtocol, ISocketSubsystem * InSubsystem) : FSocketBSD(InSocket, InSocketType, InSocketDescription, InSocketProtocol, InSubsystem)` — Assigns a BSD socket to this object @param InSocket the socket to assign to this object @param InSocketType the type of socket that was created @param InSocketDescription the debug description of the socket
- L93 _public function_ `~FSocketMac()`
- L98 _public function_ `virtual bool SetReuseAddr(bool bAllowReuse) override`

### `Source/Runtime/Sockets/Private/SocketsPrivate.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/Sockets/Private/Unix/SocketSubsystemUnix.h` (Private)


#### class `FSocketSubsystemUnix`  
`class FSocketSubsystemUnix : public FSocketSubsystemBSD`  
_L15-57_
- inherits: `FSocketSubsystemBSD`
- desc: Unix specific socket subsystem implementation
- L20 _protected member_ `static FSocketSubsystemUnix* SocketSingleton;` — Single instantiation of this subsystem
- L23 _protected member_ `bool bTriedToInit;` — Whether Init() has been called before or not
- L36 _protected prototype_ `static void Destroy();` — Performs Unix specific socket clean up
- L40 _public function_ `FSocketSubsystemUnix() : bTriedToInit(false)`
- L45 _public prototype_ `virtual ~FSocketSubsystemUnix() = default;`
- L48 _public prototype_ `virtual bool Init(FString& Error) override;` — ISocketSubsystem
- L49 _public prototype_ `virtual void Shutdown() override;`
- L50 _public prototype_ `virtual bool HasNetworkDevice() override;`
- L51 _public prototype_ `virtual class FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, const FName& ProtocolType) override;`
- L52 _public prototype_ `virtual bool GetLocalAdapterAddresses(TArray<TSharedPtr<FInternetAddr> >& OutAddresses) override;`
- L53 _public prototype_ `virtual class FSocketBSD* InternalBSDSocketFactory( SOCKET Socket, ESocketType SocketType, const FString& SocketDescription, const FName& SocketProtocol) override;`
- L54 _public prototype_ `virtual TUniquePtr<FRecvMulti> CreateRecvMulti(int32 MaxNumPackets, int32 MaxPacketSize, ERecvMultiFlags Flags) override;`
- L55 _public prototype_ `virtual bool IsSocketRecvMultiSupported() const override;`
- L56 _public prototype_ `virtual double TranslatePacketTimestamp(const FPacketTimestamp& Timestamp, ETimestampTranslation Translation) override;`

### `Source/Runtime/Sockets/Private/Unix/SocketsUnix.h` (Private)


#### struct `FUnixRecvMulti`  
`struct FUnixRecvMulti : public FRecvMulti`  
_L13-38_
- inherits: `FRecvMulti`
- desc: Implements platform specific data/buffers for RecvMulti in Linux
- L19 _protected member_ `TUniquePtr<mmsghdr[]> Headers;` — Persistently stores preconfigured mmsghdr struct values, for use with recvmmsg
- L22 _protected member_ `TUniquePtr<uint8[]> RawTimestampData;` — Buffer for receiving/storing packet kernel timestamp data, during the call to recvmmsg
- L27 _private member_ `TUniquePtr<iovec[]> BufferMaps;` — Maps sections of DataBuffer for receiving packet data, within Headers
- L30 _private member_ `TUniquePtr<uint8[]> DataBuffer;` — The raw data buffer where all packet data is received/stored.
- L34 _public prototype_ `FUnixRecvMulti(ISocketSubsystem* SocketSubsystem, int32 InMaxNumPackets, int32 InMaxPacketSize, ERecvMultiFlags InitFlags);`
- L36 _public prototype_ `virtual bool GetPacketTimestamp(int32 PacketIdx, FPacketTimestamp& OutTimestamp) const override;`
- L37 _public prototype_ `virtual void CountBytes(FArchive& Ar) const override;`

#### class `FSocketUnix`  
`class FSocketUnix : public FSocketBSD`  
_L45-59_
- inherits: `FSocketBSD`
- desc: Unix specific socket implementation - primarily, adds support for recvmmsg
- L51 _public function_ `FSocketUnix(SOCKET InSocket, ESocketType InSocketType, const FString& InSocketDescription, const FName& InSocketProtocol, ISocketSubsystem* InSubsystem) : FSocketBSD(InSocket, InSocketType, InSocketDescription, InSocketProtocol, InSubsystem)` — Base constructor
- L57 _public prototype_ `virtual bool RecvMulti(FRecvMulti& MultiData, ESocketReceiveFlags::Type Flags) override;`
- L58 _public prototype_ `virtual bool SetRetrieveTimestamp(bool bRetrieveTimestamp) override;`

### `Source/Runtime/Sockets/Private/Windows/SocketSubsystemWindows.h` (Private)


#### class `FSocketSubsystemWindows`  
`class FSocketSubsystemWindows : public FSocketSubsystemBSD`  
_L13-60_
- inherits: `FSocketSubsystemBSD`
- desc: Windows specific socket subsystem implementation.
- L19 _public function_ `FSocketSubsystemWindows() : bTriedToInit(false)` — Default constructor.
- L24 _public prototype_ `virtual ~FSocketSubsystemWindows() = default;` — Virtual destructor.
- L30 _public prototype_ `virtual class FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, const FName& ProtocolType) override;`
- L31 _public prototype_ `virtual bool HasNetworkDevice() override;`
- L32 _public prototype_ `virtual ESocketErrors GetLastErrorCode() override;`
- L33 _public prototype_ `virtual bool GetLocalAdapterAddresses( TArray<TSharedPtr<FInternetAddr> >& OutAdresses ) override;`
- L34 _public prototype_ `virtual const TCHAR* GetSocketAPIName() const override;`
- L35 _public prototype_ `virtual bool Init( FString& Error ) override;`
- L36 _public prototype_ `virtual void Shutdown() override;`
- L37 _public prototype_ `virtual ESocketErrors TranslateErrorCode( int32 Code ) override;`
- L49 _public prototype_ `static void Destroy();` — Performs Windows specific socket clean up.
- L53 _protected prototype_ `virtual FSocketBSD* InternalBSDSocketFactory(SOCKET Socket, ESocketType SocketType, const FString& SocketDescription, const FName& SocketProtocol) override;`
- L56 _protected member_ `bool bTriedToInit;` — Holds a flag indicating whether Init() has been called before or not.
- L59 _protected member_ `static FSocketSubsystemWindows* SocketSingleton;` — Holds the single instantiation of this subsystem.

### `Source/Runtime/Sockets/Private/Windows/SocketsWindows.h` (Private)


#### class `FSocketWindows`  
`class FSocketWindows : public FSocketBSD`  
_L17-33_
- inherits: `FSocketBSD`
- desc: Implements a Windows/BSD network socket.
- L21 _public function_ `FSocketWindows(SOCKET InSocket, ESocketType InSocketType, const FString& InSocketDescription, const FName& InSocketProtocol, ISocketSubsystem* InSubsystem) : FSocketBSD(InSocket, InSocketType, InSocketDescription, InSocketProtocol, InSubsystem)`
- L27 _public prototype_ `virtual bool Shutdown(ESocketShutdownMode Mode) override;`
- L28 _public prototype_ `virtual bool SetIpPktInfo(bool bEnable) override;`
- L29 _public prototype_ `virtual bool RecvFromWithPktInfo(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, FInternetAddr& Destination, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;`
- L32 _protected member_ `LPFN_WSARECVMSG WSARecvMsg = nullptr;`

### `Source/Runtime/Sockets/Public/AddressInfoTypes.h` (Public)


#### enum `EAddressInfoFlags`  
`enum class EAddressInfoFlags : uint16`  
_L11-38_
- L14 _public enumerator_ `AllResults = 1 << 0` — Return all addresses regardless of spec.
- L19 _public enumerator_ `NoResolveHost = 1 << 1` — Don't use DNS resolution of the string (AI_NUMERICHOST), this makes the address resolution non-blocking, requiring the hostname to be in the form of an ip address already
- L23 _public enumerator_ `NoResolveService = 1 << 2` — Don't resolve the service name (requires the service argument to be nullptr or a string based representation of a number). This is also-nonblocking.
- L25 _public enumerator_ `OnlyUsableAddresses = 1 << 3` — Only return addresses that adapters on this machine can use (AI_ADDRCONFIG)
- L27 _public enumerator_ `BindableAddress = 1 << 4` — Return bindable addresses (AI_PASSIVE). Only works if the hostname argument is null.
- L29 _public enumerator_ `CanonicalName = 1 << 5` — Include the canonical name of the host with the results list
- L31 _public enumerator_ `FQDomainName = 1 << 6` — Include the fully qualified domain name of the host with the results list
- L33 _public enumerator_ `AllowV4MappedAddresses = 1 << 7` — Allow for IPv4 mapped IPv6 addresses
- L35 _public enumerator_ `AllResultsWithMapping = AllowV4MappedAddresses | AllResults` — Get all addresses, but return V4 mapped IPv6 addresses
- L37 _public enumerator_ `Default = 0` — The default value of a hints flag for the platform (typically just 0)

#### struct `FAddressInfoResultData`  
`struct FAddressInfoResultData`  
_L42-97_
- L45 _public function_ `FAddressInfoResultData(TSharedRef<FInternetAddr> InAddr, SIZE_T InAddrLen, ESocketProtocolFamily InProtocol, ESocketType InSocketConfiguration) : AddressProtocol(InProtocol), AddressProtocolName(NAME_None), SocketConfiguration(InSocketConfiguration), AddressLen(InAddrLen), Address(InAddr)` — `UE_DEPRECATED(4.23, "Use constructor that supports an FName as the AddressProtocol property is now deprecated. AddressProtocolName supports multiple protocol types as should be used instead.")`
- L54 _public function_ `FAddressInfoResultData(TSharedRef<FInternetAddr> InAddr, SIZE_T InAddrLen, const FName InProtocol, ESocketType InSocketConfiguration) : AddressProtocol(ESocketProtocolFamily::None), AddressProtocolName(InProtocol), SocketConfiguration(InSocketConfiguration), AddressLen(InAddrLen), Address(InAddr)`
- L63 _public function_ `FName GetSocketTypeName() const`
- L80 _public function_ `bool operator==(const FAddressInfoResultData& rhs) const`
- L88 _public member_ `ESocketProtocolFamily AddressProtocol;` — The protocol of the address stored
- L90 _public member_ `FName AddressProtocolName;` — The protocol name of the address stored
- L92 _public member_ `ESocketType SocketConfiguration;` — Streaming or datagram
- L94 _public member_ `SIZE_T AddressLen;` — Length of the returned address data
- L96 _public member_ `TSharedRef<FInternetAddr> Address;` — The address associated with this result

#### struct `FAddressInfoResult`  
`struct FAddressInfoResult`  
_L99-118_
- L101 _public function_ `FAddressInfoResult(const TCHAR* InHostName, const TCHAR* InServiceName) : QueryHostName(InHostName), QueryServiceName(InServiceName), ReturnCode(SE_NO_DATA)`
- L109 _public member_ `FString QueryHostName;` — The hostname/ip that generated these results
- L111 _public member_ `FString QueryServiceName;` — The service name that was used in the query
- L113 _public member_ `FString CanonicalNameResult;` — The Canonical Name of the query (empty unless FQDomainName or CanonicalName are specified)
- L115 _public member_ `ESocketErrors ReturnCode;` — The return code of the query
- L117 _public member_ `TArray<FAddressInfoResultData> Results;` — The list of results

#### Free symbols / members of external scopes

- L40 _prototype_ `ENUM_CLASS_FLAGS(EAddressInfoFlags);`
- L120 _typedef_ `typedef TFunction<void(FAddressInfoResult)> FAsyncGetAddressInfoCallback;`

### `Source/Runtime/Sockets/Public/IPAddress.h` (Public)


#### class `FInternetAddr`  
`class FInternetAddr`  
_L21-190_
- desc: Represents an internet address. All data is in network byte order
- L25 _protected function_ `FInternetAddr()` — Hidden on purpose
- L31 _public prototype_ `virtual ~FInternetAddr() = default;`
- L43 _public function_ `virtual bool CompareEndpoints(const FInternetAddr& InAddr) const` — Compares FInternetAddrs together, comparing the logical net addresses (endpoints) of the data stored, rather than doing a memory comparison like the equality operator does. If it is not explicitly implemented, this falls back to just doing the same behavior of the comparison operator. @Param InAddr The address to compare with. @return true if the endpoint stored in this FInternetAddr is the same as the input.
- L53 _public prototype_ `virtual void SetIp(uint32 InAddr) = 0;` — Sets the ip address from a host byte order uint32 @param InAddr the new address to use (must convert to network byte order)
- L60 _public prototype_ `virtual void SetIp(const TCHAR* InAddr, bool& bIsValid) = 0;` — Sets the ip address from a string ("A.B.C.D") @param InAddr the string containing the new ip address to use
- L67 _public prototype_ `virtual void GetIp(uint32& OutAddr) const = 0;` — Copies the network byte order ip address to a host byte order dword @param OutAddr the out param receiving the ip address
- L74 _public prototype_ `virtual void SetPort(int32 InPort) = 0;` — Sets the port number from a host byte order int @param InPort the new port to use (must convert to network byte order)
- L77 _public function_ `virtual bool IsPortValid(int32 InPort) const` — Report whether the port is in a valid range for SetPort.
- L84 _public function_ `virtual void GetPort(int32& OutPort) const` — Copies the port number from this address and places it into a host byte order int @param OutPort the host byte order int that receives the port
- L92 _public prototype_ `virtual int32 GetPort() const = 0;` — Returns the port number from this address in host byte order
- L97 _public function_ `virtual void SetPlatformPort(int32 InPort)` — Set Platform specific port data
- L105 _public function_ `virtual int32 GetPlatformPort() const` — Get platform specific port data.
- L115 _public prototype_ `virtual void SetRawIp(const TArray<uint8>& RawAddr) = 0;` — Sets the ip address from a raw network byte order array. @param RawAddr the new address to use (must be converted to network byte order)
- L122 _public prototype_ `virtual TArray<uint8> GetRawIp() const = 0;` — Gets the ip address in a raw array stored in network byte order. @return The raw address stored in an array
- L125 _public prototype_ `virtual void SetAnyAddress() = 0;` — Sets the address to be any address
- L128 _public prototype_ `virtual void SetBroadcastAddress() = 0;` — Sets the address to broadcast
- L131 _public prototype_ `virtual void SetLoopbackAddress() = 0;` — Sets the address to loopback
- L138 _public prototype_ `virtual FString ToString(bool bAppendPort) const = 0;` — Converts this internet ip address to string form @param bAppendPort whether to append the port information or not
- L145 _public function_ `virtual bool operator==(const FInternetAddr& Other) const` — Compares two internet ip addresses for equality @param Other the address to compare against
- L157 _public prototype_ `virtual uint32 GetTypeHash() const = 0;` — Hash function for use with TMap's - exposed through FInternetAddrMapRef @return	The value to use for the hash
- L164 _public prototype_ `virtual bool IsValid() const = 0;` — Is this a well formed internet address @return true if a valid IP, false otherwise
- L171 _public prototype_ `virtual TSharedRef<FInternetAddr> Clone() const = 0;` — Creates a new structure with the same data as this structure @return The new structure
- L179 _public function_ `virtual FName GetProtocolType() const` — Returns the protocol type name of the address data currently stored in this struct @return The type of the address. If it's not known or overridden in a derived class, the return is None.
- L184 _public prototype_ `virtual void DumpAddrData() const;`

#### struct `FInternetAddrKeyMapFuncs`  
`template<typename ValueType> struct FInternetAddrKeyMapFuncs : public BaseKeyFuncs<ValueType, TSharedRef<FInternetAddr>, false>`  
_L199-215_
- inherits: `BaseKeyFuncs<ValueType,TSharedRef<FInternetAddr>,false>`
- desc: KeyFuncs for mapping/hashing FInternetAddr shared references NOTE: Implements TSharedRef over TSharedPtr, as this is required for performance critical code
- L201 _public function_ `static inline const TSharedRef<FInternetAddr>& GetSetKey(const TPair<TSharedRef<FInternetAddr>, ValueType>& Element)`
- L206 _public function_ `static inline bool Matches(const TSharedRef<FInternetAddr>& A, const TSharedRef<FInternetAddr>& B)`
- L211 _public function_ `static inline uint32 GetKeyHash(const TSharedRef<FInternetAddr>& Key)`

#### struct `FInternetAddrConstKeyMapFuncs`  
`template<typename ValueType> struct FInternetAddrConstKeyMapFuncs : public BaseKeyFuncs<ValueType, TSharedRef<const FInternetAddr>, false>`  
_L218-234_
- inherits: `BaseKeyFuncs<ValueType,TSharedRef<constFInternetAddr>,false>`
- L220 _public function_ `static inline const TSharedRef<const FInternetAddr>& GetSetKey(const TPair<TSharedRef<const FInternetAddr>, ValueType>& Element)`
- L225 _public function_ `static inline bool Matches(const TSharedRef<const FInternetAddr>& A, const TSharedRef<const FInternetAddr>& B)`
- L230 _public function_ `static inline uint32 GetKeyHash(const TSharedRef<const FInternetAddr>& Key)`

#### Free symbols / members of external scopes

- L186 _function_ `friend inline uint32 GetTypeHash(const FInternetAddr& InAddr)`

### `Source/Runtime/Sockets/Public/IPAddressAsyncResolve.h` (Public)


#### class `FResolveInfo`  
`class FResolveInfo`  
_L13-45_
- desc: Abstract interface used by clients to get async host name resolution to work in a cross-platform way
- L17 _protected function_ `FResolveInfo()` — Hidden on purpose
- L23 _public prototype_ `virtual ~FResolveInfo() = default;` — Virtual destructor for child classes to overload
- L30 _public prototype_ `virtual bool IsComplete() const = 0;` — Whether the async process has completed or not @return true if it completed successfully, false otherwise
- L37 _public prototype_ `virtual int32 GetErrorCode() const = 0;` — The error that occurred when trying to resolve @return error code from the operation
- L44 _public prototype_ `virtual const FInternetAddr& GetResolvedAddress() const = 0;` — Returns a copy of the resolved address @return the resolved IP address

#### class `FResolveInfoCached`  
`class FResolveInfoCached : public FResolveInfo`  
_L48-96_
- inherits: `FResolveInfo`
- desc: A non-async resolve info for returning cached results
- L52 _protected member_ `TSharedPtr<FInternetAddr> Addr;` — The address that was resolved
- L55 _protected function_ `FResolveInfoCached()` — Hidden on purpose
- L63 _public prototype_ `FResolveInfoCached(const FInternetAddr& InAddr);` — Sets the address to return to the caller @param InAddr the address that is being cached
- L72 _public function_ `virtual bool IsComplete() const` — Whether the async process has completed or not @return true if it completed successfully, false otherwise
- L82 _public function_ `virtual int32 GetErrorCode() const` — The error that occurred when trying to resolve @return error code from the operation
- L92 _public function_ `virtual const FInternetAddr& GetResolvedAddress() const` — Returns a copy of the resolved address @return the resolved IP address

#### class `FResolveInfoAsync`  
`class FResolveInfoAsync : public FResolveInfo`  
_L101-208_
- inherits: `FResolveInfo`
- desc: Class for creating a background thread to resolve a host.
- L145 _private member_ `TSharedPtr<FInternetAddr> Addr;` — Variables.
- L146 _private member_ `ANSICHAR HostName[256];`
- L148 _private member_ `int32 ErrorCode;` — Error code returned by GetHostByName.
- L150 _private member_ `volatile int32 bShouldAbandon;` — Tells the worker thread whether it should abandon it's work or not
- L152 _private member_ `FAsyncTask<FResolveInfoAsyncWorker> AsyncTask;` — Async task for async resolve
- L160 _public prototype_ `FResolveInfoAsync(const ANSICHAR* InHostName);` — Copies the host name for async resolution @param InHostName the host name to resolve
- L165 _public function_ `void StartAsyncTask()` — Start the async work and perform it synchronously if no thread pool is available
- L174 _public prototype_ `void DoWork();` — Resolves the specified host name
- L183 _public function_ `virtual bool IsComplete() const` — Whether the async process has completed or not @return true if it completed successfully, false otherwise
- L194 _public function_ `virtual int32 GetErrorCode() const` — The error that occurred when trying to resolve @return error code from the operation
- L204 _public function_ `virtual const FInternetAddr& GetResolvedAddress() const` — Returns a copy of the resolved address @return the resolved IP address

#### class `FResolveInfoAsync::FResolveInfoAsyncWorker`  
`class FResolveInfoAsyncWorker`  
_L107-143_
- desc: A simple wrapper task that calls back to FResolveInfoAsync to do the actual work
- L111 _public member_ `FResolveInfoAsync* Parent;` — Pointer to FResolveInfoAsync to call for async work
- L116 _public function_ `FResolveInfoAsyncWorker(FResolveInfoAsync* InParent) : Parent(InParent)` — Constructor @param InParent the FResolveInfoAsync to route the async call to
- L122 _public function_ `void DoWork()` — Call DoWork on the parent
- L127 _public function_ `inline TStatId GetStatId() const`
- L133 _public function_ `bool CanAbandon()` — Indicates to the thread pool that this task is abandonable
- L139 _public function_ `void Abandon()` — Effects the ending of the async resolve

### `Source/Runtime/Sockets/Public/MultichannelTCP.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Sockets/Public/MultichannelTcpGlobals.h` (Public)


#### enum `(anonymous)`  
``  
_L13-15_

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMultichannelTCP, Log, All);`
- L14 _enumerator_ `MultichannelMagic = 0xa692339f` (scope `__anonc8f46b070103`)

### `Source/Runtime/Sockets/Public/MultichannelTcpReceiver.h` (Public)


#### class `FMultichannelTcpReceiver`  
`class FMultichannelTcpReceiver : public FRunnable`  
_L27-131_
- inherits: `FRunnable`
- desc: Implements a receiver for multichannel TCP sockets.
- L38 _public function_ `FMultichannelTcpReceiver( FSocket* InSocket, const FOnMultichannelTcpReceive& InReceiveDelegate ) : Socket(InSocket) , ReceiveDelegate(InReceiveDelegate)` — Creates and initializes a new instance. @param InSocket The socket to receive from. @param InReceiveDelegate Delete to handle data as it becomes available, called from the receive thread.
- L46 _public function_ `~FMultichannelTcpReceiver()` — Destructor.
- L60 _public function_ `int32 GetBytesReceived()` — Gets the number of payload bytes actually sent to the socket.
- L69 _public function_ `virtual bool Init( )`
- L74 _public function_ `virtual uint32 Run( )`
- L113 _public function_ `virtual void Stop( )`
- L114 _public function_ `virtual void Exit( )`
- L119 _private member_ `int32 BytesReceived;` — Holds the number of bytes received so far.
- L122 _private member_ `FSocket* Socket;` — Holds the socket to use for communication.
- L125 _private member_ `FRunnableThread* Thread;` — Holds the thread we are running on.
- L130 _private member_ `FOnMultichannelTcpReceive ReceiveDelegate;` — Holds a delegate to be invoked when data has been received.

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnMultichannelTcpReceive, const TArray<uint8>&, uint32, bool);` — Declares a delegate to be invoked when data has been received. The first parameter will hold the received data. The second parameter is the number of bytes received. The third parameter indicates whether byte swapping is needed on the received data.
- L21 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnMultichannelTcpReceive, const TArray<uint8>&, uint32, bool);` — Declares a delegate to be invoked when data has been received. The first parameter will hold the received data. The second parameter is the number of bytes received. The third parameter indicates whether byte swapping is needed on the received data.

### `Source/Runtime/Sockets/Public/MultichannelTcpSender.h` (Public)


#### class `FMultichannelTcpSender`  
`class FMultichannelTcpSender : public FRunnable`  
_L29-252_
- inherits: `FRunnable`
- desc: Implements a sender for multichannel TCP sockets.
- L46 _public function_ `FMultichannelTcpSender( FSocket* InSocket, const FOnMultichannelTcpOkToSend& InOkToSendDelegate ) : BytesSent(0) , Socket(InSocket) , OkToSendDelegate(InOkToSendDelegate)` — Creates and initializes a new instance. @param InSocket The socket to send to. @param InOkToSendDelegate Delegate to ask if it is ok to send a packet.
- L55 _public function_ `~FMultichannelTcpSender( )` — Destructor.
- L67 _public function_ `void AttemptResumeSending( )` — Call when bandwidth tests should be retried, possibly sending data if there is available bandwidth.
- L76 _public function_ `int32 GetBytesSent()` — Gets the number of payload bytes actually sent to the socket.
- L89 _public function_ `void Send( const uint8* Data, int32 Count, uint32 Channel )` — Sends data through the given channel. This method does not block on bandwidth and never fails. @param Data The buffer containing the data to send. @param Count The number of bytes to send from the buffer.
- L115 _public function_ `virtual bool Init( )`
- L120 _public function_ `virtual uint32 Run( )`
- L203 _public function_ `virtual void Stop( )`
- L205 _public function_ `virtual void Exit( )`
- L218 _protected function_ `void AttemptResumeSendingInternal( )` — Internal call similar to AttemptResumeSending, but does not do the requisite lock.
- L231 _private member_ `int32 BytesSent;` — Holds the total number of payload bytes sent to the socket.
- L234 _private member_ `FScopedEvent* EventToRestart;` — Holds an event to trigger when bandwidth has freed up.
- L237 _private member_ `TMap<uint32, TArray<uint8>*> SendBuffers;` — Holds the buffers to hold pending per-channel data.
- L240 _private member_ `FCriticalSection SendBuffersCriticalSection;` — Holds the critical section to guard the send buffers.
- L243 _private member_ `FSocket* Socket;` — Holds the socket to use.
- L246 _private member_ `FRunnableThread* Thread;` — Holds the thread that is running this instance.
- L251 _private member_ `FOnMultichannelTcpOkToSend OkToSendDelegate;` — Holds a delegate to be invoked when checking if there is sufficient bandwidth to send.

#### enum `FMultichannelTcpSender::(anonymous)`  
``  
_L33-36_

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnMultichannelTcpOkToSend, int32, uint32);` — Declares a delegate to be invoked when checking if bandwidth permits sending a packet The first parameter is the size of the packet to send. The second parameter is the channel that the packet would be sent on.
- L23 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnMultichannelTcpOkToSend, int32, uint32);` — Declares a delegate to be invoked when checking if bandwidth permits sending a packet The first parameter is the size of the packet to send. The second parameter is the channel that the packet would be sent on.
- L35 _enumerator_ `MaxPacket = 128 * 1024 - 8` (scope `FMultichannelTcpSender::__anon68c1aec40103`) — Defines the maximum payload size per packet (in bytes).

### `Source/Runtime/Sockets/Public/MultichannelTcpSocket.h` (Public)


#### class `FMultichannelTcpSocket`  
`class FMultichannelTcpSocket`  
_L22-297_
- desc: Class to multiplex several streams on a single TCP socket. The primary feature here is to allow blocking reads to multiple channels simultaneously without interference. Generally one of these is created on both sides of the connection, immediately after the connection is established
- L42 _public function_ `FMultichannelTcpSocket( FSocket* InSocket, uint64 InBandwidthLatencyProduct ) : BandwidthLatencyProduct(InBandwidthLatencyProduct) , RemoteReceiverBytesReceived(0) , Receiver(InSocket, FOnMultichannelTcpReceive::CreateRaw(this, &FMultichannelTcpSocket::HandleReceiverReceive)) , Sender(InSocket, FOnMultichannelTcpOkToSend::CreateRaw(this, &FMultichannelTcpSocket::HandleSenderOkToSend)) , Socket(InSocket)` — Creates and initializes a new instance. @param InSocket The underlying socket to use. @param InBandwidthLatencyProduct The maximum amount of unacknowledged data to send.
- L61 _public function_ `int32 BlockingReceive( uint8* Data, int32 Count, uint32 Channel )` — Block until data is available to receive. Can be called from any thread, but not multiple threads for one channel at once. @param Data The buffer to fill. @param Count The number of bytes to receive. @param Channel The channel to receive on.
- L125 _public function_ `int32 DataAvailable( uint32 Channel )` — Non-blocking test of available data. Can be called from any thread, but realize that if this returns > 0, another thread could steal the data. @param Channel The channel to check. @return The number of bytes in the receive buffer.
- L145 _public function_ `int32 PollingReceive( uint8* Data, int32 MaxCount, uint32 Channel )` — Non-blocking return of available data. Can be called from any thread, but realize that multiple threads hammering a channel at once is unlikely to give useful results. @param Data The buffer to hold the results, if any. @param MaxCount the number of bytes in the receive buffer. @param Channel The channel to check. @return The number of bytes written into Data.
- L186 _public function_ `void Send( const uint8* Data, int32 Count, uint32 Channel )` — Send data out a given channel, this does not block on bandwidth, and never fails. Can be called from any thread, but if you are calling from multiple threads, make sure you are sending an atomic unit. @param Data The buffer containing the data to send. @param Count The number of bytes to send. @param Channel The channel to send on.
- L214 _private function_ `void HandleReceiverReceive( const TArray<uint8>& Payload, uint32 Channel, bool bForceByteswapping )` — Callback for receiving data from the receiver thread.
- L263 _private function_ `bool HandleSenderOkToSend( int32 PayloadSize, uint32 Channel )` — Callback for checking if the sender thread is permitted to send a packet.
- L278 _private member_ `uint64 BandwidthLatencyProduct;` — Holds the maximum amount of unacknowledged data to send.
- L281 _private member_ `TMap<uint32, FReceiveBuffer*> ReceiveBuffers;` — Holds the buffers for incoming per-channel data.
- L284 _private member_ `FCriticalSection ReceiveBuffersCriticalSection;` — Holds a critical section to guard the receive buffers.
- L287 _private member_ `int64 RemoteReceiverBytesReceived;` — Holds the total number of bytes received by the client (comes from an 'Ack' on the control channel).
- L290 _private member_ `FMultichannelTcpReceiver Receiver;` — Holds the receiver thread.
- L293 _private member_ `FMultichannelTcpSender Sender;` — Holds the sender thread.
- L296 _private member_ `FSocket* Socket;` — Holds the socket used for actual transfers.

#### enum `FMultichannelTcpSocket::(anonymous)`  
``  
_L25-32_

#### struct `FMultichannelTcpSocket::FReceiveBuffer`  
`struct FReceiveBuffer`  
_L195-211_
- desc: Helper struct for a receive buffer per channel
- L198 _public member_ `TArray<uint8> Buffer;` — buffer of data not yet accepted by anyone
- L201 _public member_ `int32 BytesRequiredToResume;` — number of bytes a thread is blocked, waiting to read (or zero if nobody is blocked)
- L204 _public member_ `FScopedEvent* EventToResumeWhenDataIsReady;` — Event to release some thread, once we have at least BytesRequiredToResume
- L207 _public function_ `FReceiveBuffer( ) : BytesRequiredToResume(0) , EventToResumeWhenDataIsReady(NULL)` — Constructor, sets the "nobody is waiting" state

#### Free symbols / members of external scopes

- L31 _enumerator_ `ControlChannel = 0` (scope `FMultichannelTcpSocket::__anon515e036c0103`) — Defines the control channel. The control channel is for Acks, highest priority and not subject to bandwidth limits.

### `Source/Runtime/Sockets/Public/NetworkMessage.h` (Public)


#### enum `(anonymous)`  
``  
_L21-24_

#### enum `NFS_Messages::Type`  
`enum Type`  
_L32-60_
- L34 _public enumerator_ `SyncFile`
- L35 _public enumerator_ `DeleteFile`
- L36 _public enumerator_ `MoveFile`
- L37 _public enumerator_ `SetReadOnly`
- L38 _public enumerator_ `OpenRead`
- L39 _public enumerator_ `OpenWrite`
- L40 _public enumerator_ `OpenAppend`
- L41 _public enumerator_ `CreateDirectory`
- L42 _public enumerator_ `DeleteDirectory`
- L43 _public enumerator_ `IterateDirectory`
- L44 _public enumerator_ `IterateDirectoryRecursively`
- L45 _public enumerator_ `DeleteDirectoryRecursively`
- L46 _public enumerator_ `CopyFile`
- L47 _public enumerator_ `GetFileInfo`
- L48 _public enumerator_ `Read`
- L49 _public enumerator_ `ReadAt`
- L50 _public enumerator_ `Write`
- L51 _public enumerator_ `Close`
- L52 _public enumerator_ `Seek`
- L53 _public enumerator_ `SetTimeStamp`
- L54 _public enumerator_ `ToAbsolutePathForRead`
- L55 _public enumerator_ `ToAbsolutePathForWrite`
- L56 _public enumerator_ `ReportLocalFiles`
- L57 _public enumerator_ `GetFileList`
- L58 _public enumerator_ `Heartbeat`
- L59 _public enumerator_ `RecompileShaders`

#### enum `NFS_Channels::Type`  
`enum Type`  
_L66-71_
- L68 _public enumerator_ `Main = 100`
- L69 _public enumerator_ `UnsolicitedFiles = 101`
- L70 _public enumerator_ `Heatbeat = 102`

#### enum `EConnectionFlags`  
`enum class EConnectionFlags : uint8`  
_L76-81_
- L78 _public enumerator_ `None = 0x00000000`
- L79 _public enumerator_ `Streaming = 0x00000001`
- L80 _public enumerator_ `PreCookedIterative = 0x00000002` — DEPRECATED

#### class `FSimpleAbstractSocket`  
`class FSimpleAbstractSocket`  
_L89-110_
- desc: Simple abstraction for sockets that allows FNFSMessageHeader to use either an ordinary socket or a mutichannel socket
- L98 _public prototype_ `virtual bool Receive(uint8 *Results, int32 Size) const = 0;` — Block until we receive data from the socket @param Results		Buffer of at least Size size, used to hold the results @param Size			Number of bytes to read @return				true if read is successful
- L105 _public prototype_ `virtual bool Send(const uint8 *Buffer, int32 Size) const = 0;` — Send bytes out the socket @param Buffer			Buffer containing bytes to send @param Size			Number of bytes to send @return				true if read is successful
- L107 _public prototype_ `virtual uint32 GetMagic() const = 0;` — return the magic number for this message, also used for endian correction on the archives
- L109 _public prototype_ `virtual ~FSimpleAbstractSocket() = default;` — Destructor

#### class `FSimpleAbstractSocket_FSocket`  
`class FSimpleAbstractSocket_FSocket : public FSimpleAbstractSocket`  
_L115-134_
- inherits: `FSimpleAbstractSocket`
- desc: Ordinary socket version of FSimpleAbstractSocket
- L118 _private member_ `class FSocket* Socket;` — Ordinary socket to forward requests to
- L124 _public function_ `FSimpleAbstractSocket_FSocket(class FSocket* InSocket) : Socket(InSocket)` — Constructor @param InSocket		Ordinary socket to forward requests to
- L128 _public prototype_ `virtual bool Receive(uint8 *Results, int32 Size) const;`
- L129 _public prototype_ `virtual bool Send(const uint8 *Buffer, int32 Size) const;`
- L130 _public function_ `virtual uint32 GetMagic() const`

#### class `FSimpleAbstractSocket_FMultichannelTCPSocket`  
`class FSimpleAbstractSocket_FMultichannelTCPSocket : public FSimpleAbstractSocket`  
_L139-168_
- inherits: `FSimpleAbstractSocket`
- desc: Multichannel socket version of FSimpleAbstractSocket
- L142 _private member_ `class FMultichannelTcpSocket* Socket;` — Multichannel socket to forward requests to
- L144 _private member_ `uint32 SendChannel;` — Channel to send to
- L146 _private member_ `uint32 ReceiveChannel;` — Channel to receive from
- L154 _public function_ `FSimpleAbstractSocket_FMultichannelTCPSocket(class FMultichannelTcpSocket* InSocket, uint32 InSendChannel, uint32 InReceiveChannel = 0) : Socket(InSocket) , SendChannel(InSendChannel) , ReceiveChannel(InReceiveChannel ? InReceiveChannel : InSendChannel)` — Constructor @param InSocket			Multichannel socket to forward requests to @param InSendChannel		Channel to send to @param InReceiveChannel	Channel to receive from, defaults to the sending channel
- L162 _public prototype_ `virtual bool Receive(uint8 *Results, int32 Size) const;`
- L163 _public prototype_ `virtual bool Send(const uint8 *Buffer, int32 Size) const;`
- L164 _public function_ `virtual uint32 GetMagic() const`

#### struct `FNFSMessageHeader`  
`struct FNFSMessageHeader`  
_L173-261_
- desc: Simple wrapper for sending and receiving atomic packets
- L176 _public member_ `uint32 Magic;` — Magic number, used for error checking and endianess checking
- L178 _public member_ `uint32 PayloadSize;` — Size of payload
- L180 _public member_ `uint32 PayloadCrc;` — CRC of payload
- L183 _public function_ `FNFSMessageHeader(const FSimpleAbstractSocket& InSocket) : Magic(InSocket.GetMagic()) , PayloadSize(0) , PayloadCrc(0)` — Constructor for empty header
- L191 _public function_ `FNFSMessageHeader(const FSimpleAbstractSocket& InSocket, const TArray<uint8>& Payload) : Magic(InSocket.GetMagic())` — Constructor for a header of a given payload
- L237 _public prototype_ `static bool WrapAndSendPayload(const TArray<uint8>& Payload, const FSimpleAbstractSocket& Socket);` — This function will create a header for the payload, then send the header and payload over the network @param Payload Bytes to send over the network @param Socket Connection to send the header and payload @return true if successful
- L247 _public prototype_ `static bool ReceivePayload(FArrayReader& OutPayload, const FSimpleAbstractSocket& Socket);` — This function will receive a header, and then the payload array from the network @param OutPayload The archive to read into (the response is APPENDed to any data in the archive already, and the archive will be seeked to the start of new data) @param Socket The socket to read from @return true if successful
- L259 _public prototype_ `static bool SendPayloadAndReceiveResponse(const TArray<uint8>& Payload, class FArrayReader& Response, const FSimpleAbstractSocket& Socket);` — This function will send a payload data (with header) and wait for a response, serializing the response to a FBufferArchive @param Payload Bytes to send over the network @param Response The archive to read the response into @param Socket Connection to send the header and payload @return true if successful

#### struct `FFileInfo`  
`struct FFileInfo`  
_L267-283_
- desc: A helper class for storing all available file info.
- L269 _public member_ `bool FileExists;`
- L270 _public member_ `bool ReadOnly;`
- L271 _public member_ `FDateTime TimeStamp;`
- L272 _public member_ `FDateTime AccessTimeStamp;`
- L273 _public member_ `int64 Size;`
- L275 _public function_ `FFileInfo() : FileExists(false) , ReadOnly(false) , TimeStamp(FDateTime::MinValue()) , AccessTimeStamp(FDateTime::MinValue()) , Size(-1)`

#### class `FNetworkFileArchive`  
`class FNetworkFileArchive : public FBufferArchive`  
_L288-304_
- inherits: `FBufferArchive`
- desc: A helper class for wrapping some of the network file payload specifics
- L291 _public function_ `FNetworkFileArchive(uint32 Command)`

#### Free symbols / members of external scopes

- L22 _enumerator_ `DEFAULT_TCP_FILE_SERVING_PORT=41899` (scope `__anon07fd3da70103`) — default port to use when making file server tcp connections (used if no protocol is specified)
- L23 _enumerator_ `DEFAULT_HTTP_FILE_SERVING_PORT=41898` (scope `__anon07fd3da70103`) — port that the network file server uses
- L27 _macro_ `#define USE_MCSOCKET_FOR_NFS (0)` — transitional define. Set to zero to avoid using multichannel TCP for the file server and client.
- L30 _namespace_ `namespace NFS_Messages`
- L64 _namespace_ `namespace NFS_Channels`
- L82 _prototype_ `ENUM_CLASS_FLAGS(EConnectionFlags);`
- L201 _function_ `friend FArchive& operator<<(FArchive& Ar, FNFSMessageHeader& Header)` — Serializer for header
- L298 _function_ `inline friend FNetworkFileArchive& operator<<(FNetworkFileArchive& Ar, const TCHAR*& Str)` — helper to serialize TCHAR* (there are a lot)

### `Source/Runtime/Sockets/Public/ServerTOC.h` (Public)


#### struct `FServerTOC`  
`struct FServerTOC`  
_L14-60_
- desc: Helper struct to hold and quickly access server TOC.
- L17 _public typedef_ `typedef TMap<FString, FDateTime> FDirectory;` — List of files in a directory.
- L20 _public member_ `TMap<FString, FDirectory*> Directories;` — This is the "TOC" of the server
- L23 _public prototype_ `~FServerTOC();` — Destructor. Destroys directories.
- L31 _public prototype_ `void AddFileOrDirectory(const FString& Filename, const FDateTime& Timestamp);` — Adds a file or directory to TOC. @param Filename File name or directory name to add. @param Timestamp File timestamp. Directories should have this set to 0.
- L39 _public prototype_ `const FDateTime* FindFile(const FString& Filename) const;` — Finds a file in TOC. @param Filename File name to find. @return Pointer to a timestamp if the file was found, NULL otherwise.
- L47 _public prototype_ `const FDirectory* FindDirectory(const FString& Directory) const;` — Finds a directory in TOC. @param Directory Directory to find. @return Pointer to a FDirectory if the directory was found, NULL otherwise.
- L56 _public prototype_ `FDirectory* FindDirectory(const FString& Directory);` — Finds a directory in TOC non const version used internally see FindDirectory @param Directory Directory to find @return pointer to a FDirectory if the directory was found, null otherwise
- L59 _public prototype_ `int32 RemoveFileOrDirectory(const FString& Filename);`

### `Source/Runtime/Sockets/Public/SocketSubsystem.h` (Public)


#### class `ISocketSubsystem`  
`class ISocketSubsystem`  
_L57-534_
- desc: This is the base interface to abstract platform specific sockets API differences.
- L64 _public prototype_ `static ISocketSubsystem* Get(const FName& SubsystemName=NAME_None);` — Get the singleton socket subsystem for the given named subsystem
- L69 _public prototype_ `static void ShutdownAllSystems();` — Shutdown all registered subsystems
- L72 _public prototype_ `ISocketSubsystem();`
- L73 _public prototype_ `virtual ~ISocketSubsystem();`
- L82 _public prototype_ `virtual bool Init(FString& Error) = 0;` — Does per platform initialization of the sockets library @param Error a string that is filled with error information @return true if initialized ok, false otherwise
- L87 _public prototype_ `virtual void Shutdown() = 0;` — Performs platform specific socket clean up
- L98 _public function_ `virtual FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, bool bForceUDP = false)` — Creates a socket @Param SocketType type of socket to create (DGram, Stream, etc) @param SocketDescription debug description @param bForceUDP overrides any platform specific protocol with UDP instead @return the new socket or NULL if failed
- L114 _public function_ `virtual FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, ESocketProtocolFamily ProtocolType)` — `UE_DEPRECATED(4.23, "Use the CreateSocket with the FName parameter for support for multiple protocol types.")` — Creates a socket @Param SocketType type of socket to create (DGram, Stream, etc) @param SocketDescription debug description @param ProtocolType the socket protocol to be used. Each subsystem must handle the None case and output a valid socket regardless. @return the new socket or NULL if failed
- L128 _public prototype_ `virtual FSocket* CreateSocket(const FName& SocketType, const FString& SocketDescription, const FName& ProtocolName) = 0;` — Creates a socket using the given protocol name. @Param SocketType type of socket to create (DGram, Stream, etc) @param SocketDescription debug description @param ProtocolName the name of the internet protocol to use for this socket. None should be handled. @return the new socket or NULL if failed
- L140 _public prototype_ `FUniqueSocket CreateUniqueSocket(const FName& SocketType, const FString& SocketDescription, bool bForceUDP = false);` — Creates a socket wrapped in a unique pointer that will call DestroySocket automatically - do not call it explicitly! This SocketSubsystem must also outlive the sockets it creates. @Param SocketType type of socket to create (DGram, Stream, etc) @param SocketDescription debug description @param bForceUDP overrides any platform specific protocol with UDP instead @return the new socket or NULL if failed
- L152 _public prototype_ `FUniqueSocket CreateUniqueSocket(const FName& SocketType, const FString& SocketDescription, const FName& ProtocolName);` — Creates a socket using the given protocol name,  wrapped in a unique pointer that will call DestroySocket automatically - do not call it explicitly! This SocketSubsystem must also outlive the sockets it creates. @Param SocketType type of socket to create (DGram, Stream, etc) @param SocketDescription debug description @param ProtocolName the name of the internet protocol to use for this socket. None should be handled. @return the new socket or NULL if failed
- L161 _public prototype_ `virtual class FResolveInfoCached* CreateResolveInfoCached(TSharedPtr<FInternetAddr> Addr) const;` — Creates a resolve info cached struct to hold the resolved address @Param Addr address to resolve for the socket subsystem @return the new resolved address or NULL if failed
- L168 _public prototype_ `virtual void DestroySocket(FSocket* Socket) = 0;` — Cleans up a socket class @param Socket the socket object to destroy
- L187 _public function_ `virtual FAddressInfoResult GetAddressInfo(const TCHAR* HostName, const TCHAR* ServiceName = nullptr, EAddressInfoFlags QueryFlags = EAddressInfoFlags::Default, ESocketProtocolFamily ProtocolType = ESocketProtocolFamily::None, ESocketType SocketType = ESocketType::SOCKTYPE_Unknown)` — `UE_DEPRECATED(4.23, "Migrate to GetAddressInfo that takes an FName as the protocol specification.")` — Gets the address information of the given hostname and outputs it into an array of resolvable addresses. It is up to the caller to determine which one is valid for their environment. @param HostName string version of the queryable hostname or ip address @param ServiceName string version of a service name ("http") or a port number ("80") @param QueryFlags What flags are used in making the getaddrinfo call. Several flags can be used at once by bitwise OR-ing the flags together. Platforms are required to translate this value into a the correct flag representation. @param ProtocolType Used to limit results from the call. Specifying None will search all valid protocols. Callers will find they rarely have to specify this flag. @param SocketType What socket type should the results be formatted for. This typically does not change any formatting results and can be safely left to the default value. @return the results structure containing the array of address results to this query
- L214 _public prototype_ `virtual FAddressInfoResult GetAddressInfo(const TCHAR* HostName, const TCHAR* ServiceName = nullptr, EAddressInfoFlags QueryFlags = EAddressInfoFlags::Default, const FName ProtocolTypeName = NAME_None, ESocketType SocketType = ESocketType::SOCKTYPE_Unknown) = 0;` — Gets the address information of the given hostname and outputs it into an array of resolvable addresses. It is up to the caller to determine which one is valid for their environment. This function allows for specifying FNames for the protocol type, allowing for support of other platform protocols @param HostName string version of the queryable hostname or ip address @param ServiceName string version of a service name ("http") or a port number ("80") @param QueryFlags What flags are used in making the getaddrinfo call. Several flags can be used at once by bitwise OR-ing the flags together. Platforms are required to translate this value into a the correct flag representation. @param ProtocolTypeName Used to limit results from the call. Specifying None will search all valid protocols. Callers will find they rarely have to specify this flag. @param SocketType What socket type should the results be formatted for. This typically does not change any formatting results and can be safely left to the default value. @return the results structure containing the array of address results to this query
- L242 _public prototype_ `virtual void GetAddressInfoAsync(FAsyncGetAddressInfoCallback Callback, const TCHAR* HostName, const TCHAR* ServiceName = nullptr, EAddressInfoFlags QueryFlags = EAddressInfoFlags::Default, const FName ProtocolTypeName = NAME_None, ESocketType SocketType = ESocketType::SOCKTYPE_Unknown);` — Async variant of GetAddressInfo that fetches the data from the above function in an asynchronous task executed on an available background thread. On Completion, this fires a callback function that will be executed on the same thread as the task's execution. The caller is responsible for either dispatching the result to the thread of their choosing or to allow the result callback execute on the task's thread. This function allows for specifying FNames for the protocol type, allowing for support of other platform protocols @param Callback the callback function to fire when this query completes. Contains the FAddressInfoResult structure. @param HostName string version of the queryable hostname or ip address @param ServiceName string version of a service name ("http") or a port number ("80") @param QueryFlags What flags are used in making the getaddrinfo call. Several flags can be used at once by bitwise OR-ing the flags together. Platforms are required to translate this value into a the correct flag representation. @param ProtocolTypeName Used to limit results from the call. Specifying None will search all valid protocols. Callers will find they rarely have to specify this flag. @param SocketType What socket type should the results be formatted for. This typically does not change any formatting results and can be safely left to the default value.
- L258 _public prototype_ `virtual TSharedPtr<FInternetAddr> GetAddressFromString(const FString& InAddress) = 0;` — Serializes a string that only contains an address. This is a what you see is what you get, there is no DNS resolution of the input string, so only use this if you know you already have a valid address and will not need to convert. Otherwise, feed the address to GetAddressInfo for guaranteed results. @param InAddress the address to serialize @return The FInternetAddr of the given string address. This will point to nullptr on failure.
- L268 _public function_ `virtual ESocketErrors GetHostByName(const ANSICHAR* HostName, FInternetAddr& OutAddr)` — `UE_DEPRECATED(4.23, "Please use GetAddressInfo to query hostnames")` — Does a DNS look up of a host name This code assumes a lot, and as such, it's not guaranteed that the results provided by it are correct. @param HostName the name of the host to look up @param Addr the address to copy the IP address to
- L287 _public prototype_ `virtual class FResolveInfo* GetHostByName(const ANSICHAR* HostName);` — Creates a platform specific async hostname resolution object @param HostName the name of the host to look up @return the resolve info to query for the address
- L294 _public prototype_ `virtual bool RequiresChatDataBeSeparate() = 0;` — Some platforms require chat data (voice, text, etc.) to be placed into packets in a special way. This function tells the net connection whether this is required for this platform
- L300 _public prototype_ `virtual bool RequiresEncryptedPackets() = 0;` — Some platforms require packets be encrypted. This function tells the net connection whether this is required for this platform
- L309 _public prototype_ `virtual bool GetHostName(FString& HostName) = 0;` — Determines the name of the local machine @param HostName the string that receives the data @return true if successful, false otherwise
- L317 _public function_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr(uint32 Address, uint32 Port = 0)` — `UE_DEPRECATED(4.23, "To support different address sizes, use CreateInternetAddr with no arguments and call SetIp/SetRawIp and SetPort on the returned object")` — Create a proper FInternetAddr representation @param Address host address @param Port host port
- L330 _public prototype_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr() = 0;` — Create a proper FInternetAddr representation
- L335 _public function_ `virtual TSharedRef<FInternetAddr> CreateInternetAddr(const FName ProtocolType)` — Create a FInternetAddr of the desired protocol
- L349 _public prototype_ `virtual TUniquePtr<FRecvMulti> CreateRecvMulti(int32 MaxNumPackets, int32 MaxPacketSize, ERecvMultiFlags Flags=ERecvMultiFlags::None);` — Create a platform specific FRecvMulti representation @param MaxNumPackets			The maximum number of packet receives supported @param MaxPacketSize			The maximum supported packet size @param Flags					Flags for specifying how FRecvMulti should be initialized (for e.g. retrieving timestamps) @return						Returns the platform specific FRecvMulti instance
- L355 _public prototype_ `virtual bool HasNetworkDevice() = 0;` — @return Whether the machine has a properly configured network device or not
- L361 _public prototype_ `virtual const TCHAR* GetSocketAPIName() const = 0;` — Get the name of the socket subsystem @return a string naming this subsystem
- L366 _public prototype_ `virtual ESocketErrors GetLastErrorCode() = 0;` — Returns the last error that has happened
- L371 _public prototype_ `virtual ESocketErrors TranslateErrorCode(int32 Code) = 0;` — Translates the platform error code to a ESocketErrors enum
- L381 _public prototype_ `const TCHAR* GetSocketError(ESocketErrors Code = SE_GET_LAST_ERROR_CODE);` — Returns a human readable string from an error code @param Code the error code to check
- L392 _public prototype_ `virtual bool GetLocalAdapterAddresses(TArray<TSharedPtr<FInternetAddr>>& OutAddresses);` — Gets the list of addresses associated with the adapters on the local computer. Unlike GetLocalHostAddr, this function does not give preferential treatment to multihome options in results. It's encouraged that users check for multihome before using the results of this function. @param OutAddresses - Will hold the address list. @return true on success, false otherwise.
- L400 _public prototype_ `virtual TSharedRef<FInternetAddr> GetLocalBindAddr(FOutputDevice& Out);` — Get a local IP to bind to. Typically, it is better to use GetLocalBindAddresses as it better supports hybrid network functionality and less chances for connections to fail due to mismatched protocols.
- L409 _public prototype_ `virtual TArray<TSharedRef<FInternetAddr>> GetLocalBindAddresses();` — Get bindable addresses that this machine can use as reported by GetAddressInfo with the BindableAddress flag. This will return the various any address for usage. If multihome has been specified, only the multihome address will be returned in the array. @return If GetAddressInfo succeeded or multihome is specified, an array of addresses that can be binded on. Failure returns an empty array.
- L421 _public prototype_ `int32 BindNextPort(FSocket* Socket, FInternetAddr& Addr, int32 PortCount, int32 PortIncrement);` — Bind to next available port. @param Socket The socket that that will bind to the port @param Addr The local address and port that is being bound to (usually the result of GetLocalBindAddr()). This addresses port number will be modified in place @param PortCount How many ports to try @param PortIncrement The amount to increase the port number by on each attempt @return The bound port number, or 0 on failure
- L435 _public prototype_ `virtual TSharedRef<FInternetAddr> GetLocalHostAddr(FOutputDevice& Out, bool& bCanBindAll);` — Uses the platform specific look up to determine the host address To better support multiple network interfaces and remove ambiguity between address protocols, it is encouraged to use GetLocalAdapterAddresses to determine machine addresses. Be sure to check GetMultihomeAddress ahead of time. @param Out the output device to log messages to @param bCanBindAll true if all can be bound (no primarynet), false otherwise @return The local host address
- L445 _public prototype_ `virtual bool GetMultihomeAddress(TSharedRef<FInternetAddr>& Addr);` — Returns the multihome address if the flag is present and valid. For ease of use, this function will check validity of the address for the caller. @param Addr the address structure which will have the Multihome address in it if set. @return If the multihome address was set and valid
- L455 _public prototype_ `bool GetHostByNameFromCache(const ANSICHAR* HostName, TSharedPtr<class FInternetAddr>& Addr);` — Checks the host name cache for an existing entry (faster than resolving again) @param HostName the host name to search for @param Addr the out param that the IP will be copied to @return true if the host was found, false otherwise
- L463 _public prototype_ `void AddHostNameToCache(const ANSICHAR* HostName, TSharedPtr<class FInternetAddr> Addr);` — Stores the ip address with the matching host name @param HostName the host name to search for @param Addr the IP that will be copied from
- L470 _public prototype_ `void RemoveHostNameFromCache(const ANSICHAR* HostName);` — Removes the host name to ip mapping from the cache @param HostName the host name to search for
- L475 _public prototype_ `virtual bool IsSocketRecvMultiSupported() const;` — Returns true if FSocket::RecvMulti is supported by this socket subsystem
- L481 _public prototype_ `virtual bool IsSocketWaitSupported() const = 0;` — Returns true if FSocket::Wait and QuerySocketStateMany is supported by this socket subsystem.
- L491 _public prototype_ `virtual double TranslatePacketTimestamp(const FPacketTimestamp& Timestamp, ETimestampTranslation Translation=ETimestampTranslation::LocalTimestamp);` — Converts a platform packet timestamp, into a local timestamp, or into a time delta etc. @param Timestamp		The timestamp to translate @param Translation	The type of translation to perform on the timestamp (time delta is usually faster than local timestamp) @return				Returns the translated timestamp or delta
- L497 _public prototype_ `virtual bool IsRecvFromWithPktInfoSupported() const;` — Returns true if FSocket::RecvFromWithPktInfo is supported by this socket subsystem.
- L516 _public prototype_ `virtual void QuerySocketStateMany(TArrayView<FSocket*> Sockets, TArray<ESocketStateFlags>& InOutSocketStates, FTimespan WaitTime) const;` — Queries the state of multiple sockets in a single call (equivalent to poll/select). Not supported on all platforms: check IsSocketWaitSupported() before calling. @param Sockets            The sockets to query. @param InOutSocketStates  On input, the flags to query per socket (Readable, Writable, Error). On output, the flags that are actually set. Must be the same length as Sockets. @param WaitTime           Maximum time to block waiting for any socket to become ready. Pass FTimespan(-1) to block indefinitely, or FTimespan::Zero() to poll without blocking.
- L524 _protected prototype_ `virtual ESocketProtocolFamily GetProtocolFamilyFromName(const FName& InProtocolName) const;` — Conversion functions from the SocketProtocolFamily enum to the new FName system. For now, both are supported, but it's better to use the FName when possible.
- L525 _protected prototype_ `virtual FName GetProtocolNameFromFamily(ESocketProtocolFamily InProtocolFamily) const;`
- L530 _private member_ `FCriticalSection HostNameCacheSync;` — Used to provide threadsafe access to the host name cache
- L533 _private member_ `TMap<FString, TSharedPtr<FInternetAddr> > HostNameCache;` — Stores a resolved IP address for a given host name

#### enum `ISocketSubsystem::ESocketStateFlags`  
`enum class ESocketStateFlags : uint8`  
_L499-504_
- L501 _public enumerator_ `Readable = 1 << 0`
- L502 _public enumerator_ `Writable = 1 << 1`
- L503 _public enumerator_ `Error = 1 << 2`

#### class `FSocketDeleter`  
`class FSocketDeleter`  
_L537-560_
- desc: Deleter object that can be used with unique & shared pointers that store FSockets. The SocketSubsystem must be valid when the call operator is invoked!
- L540 _public function_ `FSocketDeleter() : Subsystem(nullptr)`
- L545 _public function_ `FSocketDeleter(ISocketSubsystem* InSubsystem) : Subsystem(InSubsystem)`
- L550 _public function_ `void operator()(FSocket* Socket) const`
- L559 _private member_ `ISocketSubsystem* Subsystem;`

#### Free symbols / members of external scopes

- L28 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSockets, Log, All);`
- L34 _macro_ `#define PLATFORM_SOCKETSUBSYSTEM FName("WINDOWS")`
- L36 _macro_ `#define PLATFORM_SOCKETSUBSYSTEM FName("MAC")`
- L38 _macro_ `#define PLATFORM_SOCKETSUBSYSTEM FName("IOS")`
- L40 _macro_ `#define PLATFORM_SOCKETSUBSYSTEM FName("UNIX")`
- L42 _macro_ `#define PLATFORM_SOCKETSUBSYSTEM FName("ANDROID")`
- L44 _macro_ `#define PLATFORM_SOCKETSUBSYSTEM FName()`
- L51 _typedef_ `using FUniqueSocket = TUniquePtr<FSocket, FSocketDeleter>;`
- L562 _typedef_ `typedef TSharedPtr<ISocketSubsystem> IOnlineSocketPtr;`

### `Source/Runtime/Sockets/Public/SocketSubsystemModule.h` (Public)


#### class `FSocketSubsystemModule`  
`class FSocketSubsystemModule : public IModuleInterface`  
_L12-85_
- inherits: `IModuleInterface`
- desc: Socket subsystem module class Wraps the loading of an socket subsystem by name and allows new services to register themselves for use
- L17 _private member_ `FName DefaultSocketSubsystem;` — Name of the default socket subsystem defined by the platform
- L20 _private member_ `TMap<FName, class ISocketSubsystem*> SocketSubsystems;` — Mapping of all currently loaded subsystems to their name
- L24 _public function_ `FSocketSubsystemModule()`
- L25 _public prototype_ `virtual ~FSocketSubsystemModule() = default;`
- L35 _public prototype_ `virtual class ISocketSubsystem* GetSocketSubsystem(const FName InSubsystemName = NAME_None);` — Main entry point for accessing a socket subsystem by name Will load the appropriate module if the subsystem isn't currently loaded It's possible that the subsystem doesn't exist and therefore can return NULL @param SubsystemName - name of subsystem as referenced by consumers @return Requested socket subsystem, or NULL if that subsystem was unable to load or doesn't exist
- L43 _public prototype_ `virtual void RegisterSocketSubsystem(const FName FactoryName, class ISocketSubsystem* Factory, bool bMakeDefault=false);` — Register a new socket subsystem interface with the base level factory provider @param FactoryName - name of subsystem as referenced by consumers @param Factory - instantiation of the socket subsystem interface, this will take ownership @param bMakeDefault - make this subsystem the default
- L49 _public prototype_ `virtual void UnregisterSocketSubsystem(const FName FactoryName);` — Unregister an existing online subsystem interface from the base level factory provider @param FactoryName - name of subsystem as referenced by consumers
- L58 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created Overloaded to allow the default subsystem a chance to load
- L64 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed. Overloaded to shut down all loaded online subsystems
- L71 _public function_ `virtual bool SupportsDynamicReloading() override` — Override this to set whether your module is allowed to be unloaded on the fly @return	Whether the module supports shutdown separate from the rest of the engine.
- L81 _public function_ `virtual bool SupportsAutomaticShutdown() override` — Override this to set whether your module would like cleanup on application shutdown @return	Whether the module supports shutdown on application exit

#### Free symbols / members of external scopes

- L88 _typedef_ `typedef TSharedPtr<FSocketSubsystemModule> FSocketSubsystemModulePtr;` — Public references to the socket subsystem module pointer should use this

### `Source/Runtime/Sockets/Public/SocketSubsystemPackage.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define PACKAGE_SCOPE public`
- L14 _macro_ `#define PACKAGE_SCOPE protected`

### `Source/Runtime/Sockets/Public/SocketTypes.h` (Public)


#### enum `ESocketProtocolFamily`  
`enum class ESocketProtocolFamily : uint8`  
_L15-22_
- desc: Indicates the socket protocol of socket being used, typically for BSD Sockets
- L18 _public enumerator_ `None` — No protocol family specification. Typically defined as AF_UNSPEC
- L20 _public enumerator_ `IPv4` — IPv4 and IPv6 respectively.
- L21 _public enumerator_ `IPv6`

#### enum `ESocketType`  
`enum ESocketType`  
_L32-40_
- desc: Indicates the type of socket being used (streaming or datagram)
- L35 _public enumerator_ `SOCKTYPE_Unknown` — Not bound to a protocol yet
- L37 _public enumerator_ `SOCKTYPE_Datagram` — A UDP type socket
- L39 _public enumerator_ `SOCKTYPE_Streaming` — A TCP type socket

#### enum `ESocketConnectionState`  
`enum ESocketConnectionState`  
_L43-49_
- desc: Indicates the connection state of the socket
- L45 _public enumerator_ `SCS_NotConnected`
- L46 _public enumerator_ `SCS_Connected`
- L48 _public enumerator_ `SCS_ConnectionError` — Indicates that the end point refused the connection or couldn't be reached

#### enum `ESocketReceiveFlags::Type`  
`enum Type`  
_L57-75_
- desc: Enumerates socket receive flags.
- L63 _public enumerator_ `None = 0` — Return as much data as is currently available in the input queue, up to the specified size of the receive buffer.
- L68 _public enumerator_ `Peek = 2` — Copy received data into the buffer without removing it from the input queue.
- L74 _public enumerator_ `WaitAll = 0x100` — Block the receive call until either the supplied buffer is full, the connection has been closed, the request has been canceled, or an error occurred.

#### enum `ESocketWaitConditions::Type`  
`enum Type`  
_L84-100_
- desc: Enumerates socket wait conditions.
- L89 _public enumerator_ `WaitForRead` — Wait until data is available for reading.
- L94 _public enumerator_ `WaitForWrite` — Wait until data can be written.
- L99 _public enumerator_ `WaitForReadOrWrite` — Wait until data is available for reading or can be written.

#### enum `ESocketShutdownMode`  
`enum class ESocketShutdownMode`  
_L106-122_
- desc: Enumerates socket shutdown modes.
- L111 _public enumerator_ `Read` — Disables reading on the socket.
- L116 _public enumerator_ `Write` — Disables writing on the socket.
- L121 _public enumerator_ `ReadWrite` — Disables reading and writing on the socket.

#### enum `ETimestampTranslation`  
`enum class ETimestampTranslation : uint8`  
_L130-147_
- desc: Specifies how a platform specific timestamp (in this case, a packet timestamp) should be translated
- L138 _public enumerator_ `LocalTimestamp` — Translates the timestamp into a local timestamp, comparable (with accuracy caveats) to other local timestamps. Use this to get a value comparable to FPlatformTime::Seconds() - if the platform timestamp uses a different clock, this has both a performance (2x internal clock reads i.e. 2x FPlatformTime::Seconds() calls) and accuracy caveat.
- L146 _public enumerator_ `TimeDelta` — The delta between present platform time vs timestamp - faster than local translation, less accuracy caveats. This is the most accurate measure of time passed since the packet was recorded at an OS/NIC/Thread level, to TranslatePacketTimestamp being called for the packets timestamp - and performs faster (1x FPlatformTime::Seconds() call).

#### enum `ERecvMultiFlags`  
`enum class ERecvMultiFlags : uint32`  
_L152-156_
- desc: Flags for specifying how an FRecvMulti instance should be initialized
- L154 _public enumerator_ `None = 0x00000000`
- L155 _public enumerator_ `RetrieveTimestamps = 0x00000001` — Whether or not to support retrieving timestamps

#### struct `FRecvMulti`  
`struct FRecvMulti : public FNoncopyable, public FVirtualDestructor`  
_L165-266_
- inherits: `FNoncopyable,FVirtualDestructor`
- desc: Stores the persistent state and packet buffers/data, for receiving packets with FSocket::RecvMulti. To optimize performance, use only once instance of this struct, for the lifetime of the socket.
- L197 _private member_ `TUniquePtr<FRecvData[]> Packets;` — The current list of received packets
- L200 _private member_ `int32 NumPackets;` — The number of packets received
- L204 _public member_ `const int32 MaxNumPackets;` — The maximum number of packets this FRecvMulti instance can support
- L207 _public member_ `const int32 MaxPacketSize;` — The maximum packet size this FRecvMulti instance can support
- L219 _private prototype_ `FRecvMulti(ISocketSubsystem* SocketSubsystem, int32 InMaxNumPackets, int32 InMaxPacketSize, ERecvMultiFlags InitFlags=ERecvMultiFlags::None);` — Initialize an FRecvMulti instance, supporting the specified maximum packet count/sizes @param SocketSubsystem		The socket subsystem initializing this FRecvMulti instance @param InMaxNumPackets		The maximum number of packet receives supported @param InMaxPacketSize		The maximum supported packet size @param bRetrieveTimestamps	Whether or not to support retrieving timestamps
- L230 _public function_ `void GetPacket(int32 PacketIdx, FReceivedPacketView& OutPacket)` — Retrieves the information for the specified packet @param PacketIdx		The RecvMulti index for the packet to be retrieved @param OutPacket		Outputs a view to the received packet
- L249 _public prototype_ `virtual bool GetPacketTimestamp(int32 PacketIdx, FPacketTimestamp& OutTimestamp) const = 0;` — Returns the platform specific timestamp for when the specified packet was received by the operating system @param PacketIdx		The index into Packets, of the packet to be checked @param OutTimestamp	The timestamp for the specified packet @return				Whether or not the timestamp was retrieved successfully
- L254 _public function_ `int32 GetNumPackets() const` — Retrieves the current number of received packets
- L265 _public prototype_ `virtual void CountBytes(FArchive& Ar) const;` — Calculates the total memory consumption of this FRecvMulti instance, including platform-specific data @param Ar	The archive being used to count the memory consumption

#### struct `FRecvMulti::FRecvData`  
`struct FRecvData`  
_L174-192_
- desc: Receive data for each individual packet
- L177 _public member_ `TSharedPtr<FInternetAddr> Source;` — The source address for the packet
- L180 _public member_ `const uint8* Data;` — Pointer to the packet data
- L183 _public member_ `const uint32* BytesReadPtr;` — Internal pointer specifying the number of bytes read
- L186 _public function_ `FRecvData() : Source() , Data(nullptr) , BytesReadPtr(nullptr)`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace FNetworkProtocolTypes`
- L27 _externvar_ `extern const FLazyName IPv4;` (scope `FNetworkProtocolTypes`)
- L28 _externvar_ `extern const FLazyName IPv6;` (scope `FNetworkProtocolTypes`)
- L52 _namespace_ `namespace ESocketReceiveFlags`
- L79 _namespace_ `namespace ESocketWaitConditions`
- L158 _prototype_ `ENUM_CLASS_FLAGS(ERecvMultiFlags);`

### `Source/Runtime/Sockets/Public/Sockets.h` (Public)


#### class `FSocket`  
`class FSocket : public TSharedFromThis<FSocket, ESPMode::ThreadSafe>`  
_L18-494_
- inherits: `TSharedFromThis<FSocket,ESPMode::ThreadSafe>`
- desc: This is our abstract base class that hides the platform specific socket implementation
- L23 _protected member_ `const ESocketType SocketType;` — Indicates the type of socket this is
- L26 _protected member_ `FString SocketDescription;` — Debug description of socket usage.
- L29 _protected member_ `FName SocketProtocol;` — Protocol used in creation of a socket
- L34 _public prototype_ `FSocket();` — Default constructor.
- L43 _public function_ `inline FSocket(ESocketType InSocketType, const FString& InSocketDescription) : SocketType(InSocketType), SocketDescription(InSocketDescription), SocketProtocol(NAME_None)` — `UE_DEPRECATED(4.22, "Please migrate to the constructor that specifies protocol stack")` — Specifies the type of socket being created @param InSocketType The type of socket being created @param InSocketDescription The debug description of the socket
- L50 _public function_ `inline FSocket(ESocketType InSocketType, const FString& InSocketDescription, ESocketProtocolFamily InSocketProtocol) : SocketType(InSocketType), SocketDescription(InSocketDescription)` — `UE_DEPRECATED(4.23, "Please migrate to the constructor that takes an FName for the protocol stack")`
- L75 _public prototype_ `FSocket(ESocketType InSocketType, const FString& InSocketDescription, const FName& InSocketProtocol);` — Specifies the type of socket being created @param InSocketType The type of socket being created @param InSocketDescription The debug description of the socket @param InSocketProtocol the protocol stack this socket should be created on.
- L78 _public prototype_ `virtual ~FSocket();` — Virtual destructor.
- L86 _public prototype_ `virtual bool Shutdown(ESocketShutdownMode Mode) = 0;` — Shuts down the socket, making it unusable for reads and/or writes. This does not close the socket! @param Types @return true if successful, false otherwise.
- L93 _public prototype_ `virtual bool Close() = 0;` — Closes the socket @return true if it closes without errors, false otherwise.
- L101 _public function_ `[[nodiscard]] virtual UPTRINT ReleaseNativeSocket()` — Releases the underlying socket implementation for use with native APIs. The user of this class must know the underlying implementation details in order to cast the return value properly. If this function succeeds, the FSocket instance no longer controls the connection (it will not Close()). @return a non-zero value upon success, or zero if not implemented/failure to release ownership.
- L109 _public prototype_ `virtual bool Bind(const FInternetAddr& Addr) = 0;` — Binds a socket to a network byte ordered address. @param Addr The address to bind to. @return true if successful, false otherwise.
- L117 _public prototype_ `virtual bool Connect(const FInternetAddr& Addr) = 0;` — Connects a socket to a network byte ordered address. @param Addr The address to connect to. @return true if successful, false otherwise.
- L125 _public prototype_ `virtual bool Listen(int32 MaxBacklog) = 0;` — Places the socket into a state to listen for incoming connections. @param MaxBacklog The number of connections to queue before refusing them. @return true if successful, false otherwise.
- L135 _public prototype_ `virtual bool WaitForPendingConnection(bool& bHasPendingConnection, const FTimespan& WaitTime) = 0;` — Waits for a pending connection on the socket. @param out bHasPendingConnection Will indicate whether a connection is pending or not. @param WaitTime The maximum time to wait for a connection. If zero, the function will not wait and will return immediately with a value in bHasPendingConnection. @return true if successful, false otherwise.
- L143 _public function_ `bool HasPendingConnection(bool& bHasPendingConnection)` — Queries the socket to determine if there is a pending connection. @param bHasPendingConnection Will indicate whether a connection is pending or not. @return true if successful, false otherwise.
- L154 _public prototype_ `virtual bool HasPendingData(uint32& PendingDataSize) = 0;` — Queries the socket to determine if there is pending data on the queue. @param PendingDataSize Will indicate how much data is on the pipe for a single recv call. @return true if the socket has data, false otherwise.
- L162 _public prototype_ `virtual class FSocket* Accept(const FString& InSocketDescription) = 0;` — Accepts a connection that is pending. @param SocketDescription Debug description of socket, @return The new (heap-allocated) socket, or nullptr if unsuccessful.
- L171 _public prototype_ `virtual class FSocket* Accept(FInternetAddr& OutAddr, const FString& InSocketDescription) = 0;` — Accepts a connection that is pending. @param OutAddr The address of the connection. @param SocketDescription Debug description of socket. @return The new (heap-allocated) socket, or nullptr if unsuccessful.
- L181 _public prototype_ `virtual bool SendTo(const uint8* Data, int32 Count, int32& BytesSent, const FInternetAddr& Destination);` — Sends a buffer to a network byte ordered address. @param Data The buffer to send. @param Count The size of the data to send. @param BytesSent Will indicate how much was sent. @param Destination The network byte ordered address to send to.
- L190 _public prototype_ `virtual bool Send(const uint8* Data, int32 Count, int32& BytesSent);` — Sends a buffer on a connected socket. @param Data The buffer to send. @param Count The size of the data to send. @param BytesSent Will indicate how much was sent.
- L206 _public prototype_ `virtual bool RecvFrom(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None);` — Reads a chunk of data from the socket and gathers the source address. A return value of 'true' does not necessarily mean that data was returned. Callers must check the 'BytesRead' parameter for the actual amount of data returned. A value of zero indicates that there was no data available for reading. @param Data The buffer to read into. @param BufferSize The max size of the buffer. @param BytesRead Will indicate how many bytes were read from the socket. @param Source Will contain the receiving the address of the sender of the data. @param Flags The receive flags. @return true on success, false in case of a closed socket or an unrecoverable error.
- L221 _public prototype_ `virtual bool Recv(uint8* Data, int32 BufferSize, int32& BytesRead, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None);` — Reads a chunk of data from a connected socket A return value of 'true' does not necessarily mean that data was returned. Callers must check the 'BytesRead' parameter for the actual amount of data returned. A value of zero indicates that there was no data available for reading. @param Data The buffer to read into @param BufferSize The max size of the buffer @param BytesRead Will indicate how many bytes were read from the socket @param Flags the receive flags @return true on success, false in case of a closed socket or an unrecoverable error.
- L232 _public prototype_ `virtual bool RecvMulti(FRecvMulti& MultiData, ESocketReceiveFlags::Type Flags=ESocketReceiveFlags::None);` — Reads multiple packets from the socket at once, gathering the source address and other optional platform specific data. Use ISocketSubsystem::IsSocketRecvMultiSupported to check if the current socket platform supports this. NOTE: For optimal performance, one FRecvMulti instance should be used, for the lifetime of the socket. @param MultiData		The FRecvMulti instance that receives packet data and holds platform specific buffers for receiving data. @param Flags			The receive flags. @return				Whether or not data was successfully received
- L241 _public prototype_ `virtual bool Wait(ESocketWaitConditions::Type Condition, FTimespan WaitTime) = 0;` — Blocks until the specified condition is met. @param Condition The condition to wait for. @param WaitTime The maximum time to wait. @return true if the condition was met, false if the time limit expired or an error occurred.
- L248 _public prototype_ `virtual ESocketConnectionState GetConnectionState() = 0;` — Determines the connection state of the socket. @return Connection state.
- L255 _public prototype_ `virtual void GetAddress(FInternetAddr& OutAddr) = 0;` — Reads the address the socket is bound to and returns it. @param OutAddr The address the socket is bound to.
- L263 _public prototype_ `virtual bool GetPeerAddress(FInternetAddr& OutAddr) = 0;` — Reads the address of the peer the socket is connected to. @param OutAddr Address of the peer the socket is connected to. @return true if the address was retrieved correctly, false otherwise.
- L271 _public prototype_ `virtual bool SetNonBlocking(bool bIsNonBlocking = true) = 0;` — Sets this socket into non-blocking mode. @param bIsNonBlocking Whether to enable blocking or not. @return true if successful, false otherwise.
- L279 _public prototype_ `virtual bool SetBroadcast(bool bAllowBroadcast = true) = 0;` — Sets a socket into broadcast mode (UDP only). @param bAllowBroadcast Whether to enable broadcast or not. @return true if successful, false otherwise.
- L287 _public prototype_ `virtual bool SetNoDelay(bool bIsNoDelay = true) = 0;` — Sets this socket into TCP_NODELAY mode (TCP only). @param bIsNoDelay Whether to enable no delay mode. @return true if successful, false otherwise.
- L298 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress) = 0;` — Joins this socket to the specified multicast group. The multicast group address must be in the range 224.0.0.0 to 239.255.255.255. @param GroupAddress The IP address of the multicast group. @return true on success, false otherwise. @see LeaveMulticastGroup, SetMulticastLoopback, SetMulticastTtl
- L310 _public prototype_ `virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) = 0;` — Joins this socket to the specified multicast group on the specified interface. The multicast group address must be in the range 224.0.0.0 to 239.255.255.255. @param GroupAddress The IP address of the multicast group. @param InterfaceAddress The address representing the interface. @return true on success, false otherwise. @see LeaveMulticastGroup, SetMulticastLoopback, SetMulticastTtl
- L319 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress) = 0;` — Removes this UDP client from the specified multicast group. @param The multicast group address to leave. @return true on success, false otherwise. @see JoinMulticastGroup, SetMulticastLoopback, SetMulticastTtl
- L329 _public prototype_ `virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) = 0;` — Removes this UDP client from the specified multicast group on the specified interface. @param GroupAddress The multicast group address to leave. @param InterfaceAddress The address representing the interface. @return true on success, false otherwise. @see JoinMulticastGroup, SetMulticastLoopback, SetMulticastTtl
- L342 _public prototype_ `virtual bool SetMulticastLoopback(bool bLoopback) = 0;` — Enables or disables multicast loopback on the socket (UDP only). This setting determines whether multicast datagrams are looped back to the sending socket. By default, multicast loopback is enabled. It must be enabled if more than one listener is present on a host. @param bLoopback Whether loopback should be enabled. @see LeaveMulticastGroup, JoinMulticastGroup, SetMulticastTtl
- L355 _public prototype_ `virtual bool SetMulticastTtl(uint8 TimeToLive) = 0;` — Sets the time to live (TTL) for multicast datagrams. The default TTL for multicast datagrams is 1, which prevents them from being forwarded beyond the local subnet. Higher values will allow multicast datagrams to be sent into neighboring subnets, if multicast capable routers are present. @param TimeToLive Number of hops the datagram can make. @see LeaveMulticastGroup, JoinMulticastGroup, SetMulticastLoopback
- L366 _public prototype_ `virtual bool SetMulticastInterface(const FInternetAddr& InterfaceAddress) = 0;` — Sets the interface used to send outgoing multicast datagrams. Multicast traffic is sent using the default interface, this allows to explicitly set the interface used to send outgoing multicast datagrams. @param InterfaceAddress The interface address. @return true if the call succeeded, false otherwise.
- L374 _public prototype_ `virtual bool SetReuseAddr(bool bAllowReuse = true) = 0;` — Sets whether a socket can be bound to an address in use. @param bAllowReuse Whether to allow reuse or not. @return true if the call succeeded, false otherwise.
- L383 _public prototype_ `virtual bool SetLinger(bool bShouldLinger = true, int32 Timeout = 0) = 0;` — Sets whether and how long a socket will linger after closing. @param bShouldLinger Whether to have the socket remain open for a time period after closing or not. @param Timeout The amount of time to linger before closing. @return true if the call succeeded, false otherwise.
- L391 _public prototype_ `virtual bool SetRecvErr(bool bUseErrorQueue = true) = 0;` — Enables error queue support for the socket. @param bUseErrorQueue Whether to enable error queuing or not. @return true if the call succeeded, false otherwise.
- L400 _public prototype_ `virtual bool SetSendBufferSize(int32 Size, int32& NewSize) = 0;` — Sets the size of the send buffer to use. @param Size The size to change it to. @param NewSize Will contain the size that was set (in case OS can't set that). @return true if the call succeeded, false otherwise.
- L409 _public prototype_ `virtual bool SetReceiveBufferSize(int32 Size, int32& NewSize) = 0;` — Sets the size of the receive buffer to use. @param Size The size to change it to. @param NewSize Will contain the size that was set (in case OS can't set that). @return true if the call succeeded, false otherwise.
- L417 _public prototype_ `virtual bool SetRetrieveTimestamp(bool bRetrieveTimestamp=true);` — Sets whether to retrieve the system-level receive timestamp, for sockets @param bRetrieveTimestamp	Whether to retrieve the timestamp upon receive @return						True if the call succeeded, false otherwise.
- L427 _public prototype_ `virtual bool SetSendSegmentationOffloadSize(uint16 InSegmentPayloadBytes);` — Attempt to enable UDP segmentation offload (USO). Where supported, this reduces overhead by automatically splitting "superpackets" which exceed the specified segment size into multiple datagrams. @param InSegmentPayloadBytes Number of payload bytes for each split segment. @return True if the call succeeded, false otherwise.
- L435 _public prototype_ `virtual int32 GetPortNo() = 0;` — Reads the port this socket is bound to. @return Port number. @see GetSocketType, GetDescription
- L443 _public prototype_ `virtual bool SetIpPktInfo(bool bEnable);` — Sets whether to enable IP_PKTINFO support @param bEnable	Whether to enable/disable @return True if the call succeeded, false otherwise.
- L460 _public prototype_ `virtual bool RecvFromWithPktInfo(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, FInternetAddr& Destination, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None);` — Reads a chunk of data from the socket and gathers the source address and the destination using IP_PKTINFO A return value of 'true' does not necessarily mean that data was returned. Callers must check the 'BytesRead' parameter for the actual amount of data returned. A value of zero indicates that there was no data available for reading. @param Data The buffer to read into. @param BufferSize The max size of the buffer. @param BytesRead Will indicate how many bytes were read from the socket. @param Source Will contain the receiving the address of the sender of the data. @param Destination Will contain the destination address used by the sender of the data. @param Flags The receive flags. @return true on success, false in case of a closed socket or an unrecoverable error.
- L468 _public function_ `inline ESocketType GetSocketType() const` — Get the type of protocol the socket is bound to @return Socket type. @see GetDescription, GetPortNo
- L479 _public function_ `inline FString GetDescription() const` — Get the debug description of the socket. @return Debug string. @see GetPortNo, GetSocketType
- L490 _public function_ `inline FName GetProtocol() const` — Get the type of protocol the socket is bound to @return Socket type. @see GetDescription, GetPortNo
