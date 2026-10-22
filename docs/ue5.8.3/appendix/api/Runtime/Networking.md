# Runtime / Networking

- module root: `Source/Runtime/Networking`
- headers: 13; symbols: 243
- symbol kinds: class=8, delegate=2, enum=1, enumerator=4, function=128, member=73, namespace=1, prototype=15, struct=8, typedef=1, union=2
- PublicDependencyModuleNames: Core, Sockets

### `Source/Runtime/Networking/Private/NetworkingModule.h` (Private)


#### class `FNetworkingModule`  
`class FNetworkingModule : public INetworkingModule`  
_L11-21_
- inherits: `INetworkingModule`
- desc: Implements the Networking module.
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public prototype_ `virtual bool SupportsDynamicReloading() override;`

### `Source/Runtime/Networking/Public/Common/TcpListener.h` (Public)


#### class `FTcpListener`  
`class FTcpListener : public FRunnable`  
_L27-233_
- inherits: `FRunnable`
- desc: Implements a runnable that listens for incoming TCP connections.
- L39 _public function_ `FTcpListener(const FIPv4Endpoint& LocalEndpoint, const FTimespan& InSleepTime = FTimespan::FromSeconds(1), bool bInReusable = true) : bDeleteSocket(true) , Endpoint(LocalEndpoint) , SleepTime(InSleepTime) , Socket(nullptr) , bStopping(false) , bSocketReusable(bInReusable)` — Creates and initializes a new instance from the specified IP endpoint. @param LocalEndpoint The local IP endpoint to listen on. @param SleepTime The maximum time to wait for a pending connection inside the polling loop (default = 1 second). @param Toggles socket-reusability which allows for other sockets to use the same address (default = true).
- L57 _public function_ `FTcpListener(FSocket& InSocket, const FTimespan& InSleepTime = FTimespan::FromSeconds(1), bool bInReusable = true) : bDeleteSocket(false) , SleepTime(InSleepTime) , Socket(&InSocket) , bStopping(false) , bSocketReusable(bInReusable)` — Creates and initializes a new instance from the specified socket. @param InSocket The socket to listen on. @param SleepTime SleepTime The maximum time to wait for a pending connection inside the polling loop (default = 1 second). @param bInReusable Toggles socket-reusability which allows for other sockets to use the same address (default = true).
- L72 _public function_ `~FTcpListener()` — Destructor.
- L94 _public function_ `const FIPv4Endpoint& GetLocalEndpoint() const` — Gets the listener's local IP endpoint. @return IP endpoint.
- L104 _public function_ `FSocket* GetSocket() const` — Gets the listener's network socket. @return Network socket.
- L114 _public function_ `bool IsActive() const` — Checks whether the listener is listening for incoming connections. @return true if it is listening, false otherwise.
- L129 _public function_ `FOnTcpListenerConnectionAccepted& OnConnectionAccepted()` — Gets a delegate to be invoked when an incoming connection has been accepted. If this delegate is not bound, the listener will reject all incoming connections. To temporarily disable accepting connections, use the Enable() and Disable() methods. @return The delegate.
- L138 _public function_ `virtual bool Init() override`
- L152 _public function_ `virtual uint32 Run() override`
- L199 _public function_ `virtual void Stop() override`
- L204 _public function_ `virtual void Exit() override`
- L209 _private member_ `bool bDeleteSocket;` — Holds a flag indicating whether the socket should be deleted in the destructor.
- L212 _private member_ `FIPv4Endpoint Endpoint;` — Holds the server endpoint.
- L215 _private member_ `FTimespan SleepTime;` — Holds the time to sleep between checking for pending connections.
- L218 _private member_ `FSocket* Socket;` — Holds the server socket.
- L221 _private member_ `bool bStopping;` — Holds a flag indicating that the thread is stopping.
- L224 _private member_ `bool bSocketReusable;` — Holds a flag indicating if the bound address can be used by other sockets.
- L227 _private member_ `FRunnableThread* Thread;` — Holds the thread object.
- L232 _private member_ `FOnTcpListenerConnectionAccepted ConnectionAcceptedDelegate;` — Holds a delegate to be invoked when an incoming connection has been accepted.

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnTcpListenerConnectionAccepted, FSocket*, const FIPv4Endpoint&) class FTcpListener : public FRunnable { public: FTcpListener(const FIPv4Endpoint& LocalEndpoint, const FTimespan& InSleepTime = FTimespan::FromSeconds(1), bool bInReusable = true) : bDeleteSocket(true) , Endpoint(LocalEndpoint) , SleepTime(InSleepTime) , Socket(nullptr) , bStopping(false) , bSocketReusable(bInReusable) { Thread = FRunnableThread::Create(this, TEXT("FTcpListener"), 8 * 1024, TPri_Normal); } FTcpListener(FSocket& InSocket, const FTimespan& InSleepTime = FTimespan::FromSeconds(1), bool bInReusable = true) : bDeleteSocket(false) , SleepTime(InSleepTime) , Socket(&InSocket)` — Delegate type for accepted TCP connections. The first parameter is the socket for the accepted connection. The second parameter is the remote IP endpoint of the accepted connection. The return value indicates whether the connection should be accepted.

### `Source/Runtime/Networking/Public/Common/TcpSocketBuilder.h` (Public)


#### class `FTcpSocketBuilder`  
`class FTcpSocketBuilder`  
_L18-320_
- desc: Implements a fluent builder for TCP sockets.
- L27 _public function_ `FTcpSocketBuilder(const FString& InDescription) : Blocking(false) , Bound(false) , BoundEndpoint(FIPv4Address::Any, 0) , Description(InDescription) , Linger(false) , LingerTimeout(0) , Listen(false) , ReceiveBufferSize(0) , Reusable(false) , SendBufferSize(0)` — Creates and initializes a new instance. @param InDescription Debug description for the socket.
- L48 _public function_ `FTcpSocketBuilder AsBlocking()` — Sets socket operations to be blocking. @return This instance (for method chaining). @see AsNonBlocking, AsReusable
- L61 _public function_ `FTcpSocketBuilder AsNonBlocking()` — Sets socket operations to be non-blocking. @return This instance (for method chaining). @see AsBlocking, AsReusable
- L74 _public function_ `FTcpSocketBuilder AsReusable()` — Makes the bound address reusable by other sockets. @return This instance (for method chaining). @see AsNonBlocking, AsNonBlocking
- L88 _public function_ `FTcpSocketBuilder AsReusable(bool bInReusable)` — Sets re-usability of the bound address by other sockets. @param bInReusable Whether to enable or disable re-usability of the bound address. @return This instance (for method chaining). @see AsNonBlocking, AsNonBlocking
- L105 _public function_ `FTcpSocketBuilder BoundToAddress(const FIPv4Address& Address)` — Sets the local address to bind the socket to. Unless specified in a subsequent call to BoundToPort(), a random port number will be assigned by the underlying provider. @param Address The IP address to bind the socket to. @return This instance (for method chaining). @see BoundToEndpoint, BoundToPort
- L120 _public function_ `FTcpSocketBuilder BoundToEndpoint(const FIPv4Endpoint& Endpoint)` — Sets the local endpoint to bind the socket to. @param Endpoint The IP endpoint to bind the socket to. @return This instance (for method chaining). @see BoundToAddress, BoundToPort
- L138 _public function_ `FTcpSocketBuilder BoundToPort(uint16 Port)` — Sets the local port to bind the socket to. Unless specified in a subsequent call to BoundToAddress(), the local address will be determined automatically by the underlying provider. @param Port The local port number to bind the socket to. @return This instance (for method chaining). @see BoundToAddress, BoundToEndpoint
- L152 _public function_ `FTcpSocketBuilder Lingering(int32 Timeout)` — Sets how long the socket will linger after closing. @param Timeout The amount of time to linger before closing. @return This instance (for method chaining).
- L166 _public function_ `FTcpSocketBuilder Listening(int32 MaxBacklog)` — Sets the socket into a listening state for incoming connections. @param MaxBacklog The number of connections to queue before refusing them. @return This instance (for method chaining).
- L184 _public function_ `FTcpSocketBuilder WithReceiveBufferSize(int32 SizeInBytes)` — Specifies the desired size of the receive buffer in bytes (0 = default). The socket creation will not fail if the desired size cannot be set or if the actual size is less than the desired size. @param SizeInBytes The size of the buffer. @return This instance (for method chaining). @see WithSendBufferSize
- L201 _public function_ `FTcpSocketBuilder WithSendBufferSize(int32 SizeInBytes)` — Specifies the desired size of the send buffer in bytes (0 = default). The socket creation will not fail if the desired size cannot be set or if the actual size is less than the desired size. @param SizeInBytes The size of the buffer. @return This instance (for method chaining). @see WithReceiveBufferSize
- L215 _public function_ `operator FSocket*() const` — Implicit conversion operator that builds the socket as configured. @return The built socket.
- L225 _public function_ `FSocket* Build() const` — Builds the socket as configured. @return The built socket.
- L289 _private member_ `bool Blocking;` — Holds a flag indicating whether socket operations are blocking.
- L292 _private member_ `bool Bound;` — Holds a flag indicating whether the socket should be bound.
- L295 _private member_ `FIPv4Endpoint BoundEndpoint;` — Holds the IP address (and port) that the socket will be bound to.
- L298 _private member_ `FString Description;` — Holds the socket's debug description text.
- L301 _private member_ `bool Linger;` — Holds a flag indicating whether the socket should linger after closing.
- L304 _private member_ `int32 LingerTimeout;` — Holds the amount of time the socket will linger before closing.
- L307 _private member_ `bool Listen;` — Holds a flag indicating whether the socket should listen for incoming connections.
- L310 _private member_ `int32 ListenBacklog;` — Holds the number of connections to queue up before refusing them.
- L313 _private member_ `int32 ReceiveBufferSize;` — The desired size of the receive buffer in bytes (0 = default).
- L316 _private member_ `bool Reusable;` — Holds a flag indicating whether the bound address can be reused by other sockets.
- L319 _private member_ `int32 SendBufferSize;` — The desired size of the send buffer in bytes (0 = default).

### `Source/Runtime/Networking/Public/Common/UdpSocketBuilder.h` (Public)


#### class `FUdpSocketBuilder`  
`class FUdpSocketBuilder`  
_L17-448_
- desc: Implements a fluent builder for UDP sockets.
- L26 _public function_ `FUdpSocketBuilder(const FString& InDescription) : AllowBroadcast(false) , Blocking(false) , Bound(false) , BoundEndpoint(FIPv4Address::Any, 0) , Description(InDescription) , MulticastInterface(FIPv4Address::Any) , MulticastLoopback(false) , MulticastTtl(1) , ReceiveBufferSize(0) , Reusable(false) , SendBufferSize(0)` — Creates and initializes a new instance. @param InDescription Debug description for the socket.
- L48 _public function_ `FUdpSocketBuilder& AsBlocking()` — Sets socket operations to be blocking. @return This instance (for method chaining). @see AsNonBlocking, AsReusable
- L61 _public function_ `FUdpSocketBuilder& AsNonBlocking()` — Sets socket operations to be non-blocking. @return This instance (for method chaining). @see AsBlocking, AsReusable
- L74 _public function_ `FUdpSocketBuilder& AsReusable()` — Makes the bound address reusable by other sockets. @return This instance (for method chaining). @see AsBlocking, AsNonBlocking
- L91 _public function_ `FUdpSocketBuilder& BoundToAddress(const FIPv4Address& Address)` — Sets the local address to bind the socket to. Unless specified in a subsequent call to BoundToPort(), a random port number will be assigned by the underlying provider. @param Address The IP address to bind the socket to. @return This instance (for method chaining). @see BoundToEndpoint, BoundToPort
- L106 _public function_ `FUdpSocketBuilder& BoundToEndpoint(const FIPv4Endpoint& Endpoint)` — Sets the local endpoint to bind the socket to. @param Endpoint The IP endpoint to bind the socket to. @return This instance (for method chaining). @see BoundToAddress, BoundToPort
- L124 _public function_ `FUdpSocketBuilder& BoundToPort(uint16 Port)` — Sets the local port to bind the socket to. Unless specified in a subsequent call to BoundToAddress(), the local address will be determined automatically by the underlying provider. @param Port The local port number to bind the socket to. @return This instance (for method chaining). @see BoundToAddress
- L139 _public function_ `FUdpSocketBuilder& JoinedToGroup(const FIPv4Address& GroupAddress)` — Joins the socket to the specified multicast group. @param GroupAddress The IP address of the multicast group to join. @return This instance (for method chaining). @see WithMulticastLoopback, WithMulticastTtl
- L152 _public function_ `FUdpSocketBuilder& JoinedToGroup(const FIPv4Address& GroupAddress, const FIPv4Address& InterfaceAddress)` — Joins the socket to the specified multicast group. @param GroupAddress The IP address of the multicast group to join. @param InterfaceAddress The IP address of the interface to join the multicast group on. @return This instance (for method chaining). @see WithMulticastLoopback, WithMulticastTtl
- L164 _public function_ `FUdpSocketBuilder& WithBroadcast()` — Enables broadcasting. @return This instance (for method chaining).
- L179 _public function_ `FUdpSocketBuilder& WithMulticastLoopback()` — Enables multicast loopback. @param AllowLoopback Whether to allow multicast loopback. @param TimeToLive The time to live. @return This instance (for method chaining). @see JoinedToGroup, WithMulticastTtl
- L193 _public function_ `FUdpSocketBuilder& WithMulticastTtl(uint8 TimeToLive)` — Sets the multicast time-to-live. @param TimeToLive The time to live. @return This instance (for method chaining). @see JoinedToGroup, WithMulticastLoopback
- L207 _public function_ `FUdpSocketBuilder& WithMulticastInterface(const FIPv4Address& InterfaceAddress)` — Sets the multicast outgoing interface. @param InterfaceAddress The interface to use to send multicast datagrams. @return This instance (for method chaining). @see JoinedToGroup, WithMulticastLoopback
- L225 _public function_ `FUdpSocketBuilder& WithReceiveBufferSize(int32 SizeInBytes)` — Specifies the desired size of the receive buffer in bytes (0 = default). The socket creation will not fail if the desired size cannot be set or if the actual size is less than the desired size. @param SizeInBytes The size of the buffer. @return This instance (for method chaining). @see WithSendBufferSize
- L242 _public function_ `FUdpSocketBuilder& WithSendBufferSize(int32 SizeInBytes)` — Specifies the desired size of the send buffer in bytes (0 = default). The socket creation will not fail if the desired size cannot be set or if the actual size is less than the desired size. @param SizeInBytes The size of the buffer. @return This instance (for method chaining). @see WithReceiveBufferSize
- L256 _public function_ `operator FSocket*() const` — Implicit conversion operator that builds the socket as configured. @return The built socket.
- L266 _public function_ `FSocket* Build() const` — Builds the socket as configured. @return The built socket.
- L409 _private member_ `bool AllowBroadcast;` — Holds a flag indicating whether broadcasts will be enabled.
- L412 _private member_ `bool Blocking;` — Holds a flag indicating whether socket operations are blocking.
- L415 _private member_ `bool Bound;` — Holds a flag indicating whether the socket should be bound.
- L418 _private member_ `FIPv4Endpoint BoundEndpoint;` — Holds the IP address (and port) that the socket will be bound to.
- L421 _private member_ `FString Description;` — Holds the socket's debug description text.
- L424 _private member_ `FIPv4Address MulticastInterface;` — Holds the IP address of the interface to use for outgoing multicast datagrams.
- L432 _private member_ `TArray<FMulticastGroup> JoinedGroups;`
- L435 _private member_ `bool MulticastLoopback;` — Holds a flag indicating whether multicast loopback will be enabled.
- L438 _private member_ `uint8 MulticastTtl;` — Holds the multicast time to live.
- L441 _private member_ `int32 ReceiveBufferSize;` — The desired size of the receive buffer in bytes (0 = default).
- L444 _private member_ `bool Reusable;` — Holds a flag indicating whether the bound address can be reused by other sockets.
- L447 _private member_ `int32 SendBufferSize;` — The desired size of the send buffer in bytes (0 = default).

#### struct `FUdpSocketBuilder::FMulticastGroup`  
`struct FMulticastGroup`  
_L427-431_
- desc: Holds the list of joined multicast groups.
- L429 _public member_ `FIPv4Address GroupAddress;`
- L430 _public member_ `FIPv4Address InterfaceAddress;`

### `Source/Runtime/Networking/Public/Common/UdpSocketReceiver.h` (Public)


#### class `FUdpSocketReceiver`  
`class FUdpSocketReceiver : public FRunnable , private FSingleThreadRunnable`  
_L35-205_
- inherits: `FRunnable,FSingleThreadRunnable`
- desc: Asynchronously receives data from an UDP socket.
- L48 _public function_ `FUdpSocketReceiver(FSocket* InSocket, const FTimespan& InWaitTime, const TCHAR* InThreadName) : Socket(InSocket) , bStopping(false) , Thread(nullptr) , ThreadName(InThreadName) , WaitTime(InWaitTime)` — Creates and initializes a new socket receiver. @param InSocket The UDP socket to receive data from. @param InWaitTime The amount of time to wait for the socket to be readable. @param InThreadName The receiver thread name (for debugging).
- L62 _public function_ `virtual ~FUdpSocketReceiver()` — Virtual destructor.
- L74 _public function_ `void SetMaxReadBufferSize(uint32 InMaxReadBufferSize)` — Set the maximum size allocated to read off of the socket.
- L80 _public function_ `void SetThreadStackSize(uint32 InTheadStackSize)` — Set the desired Thread Stack Size. Only read when Start() is called.
- L86 _public function_ `void Start()` — Start the receiver thread.
- L99 _public function_ `FOnSocketDataReceived& OnDataReceived()` — Returns a delegate that is executed when data has been received. This delegate must be bound before the receiver thread is started with the Start() method. It cannot be unbound while the thread is running. @return The delegate.
- L109 _public function_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override`
- L114 _public function_ `virtual bool Init() override`
- L119 _public function_ `virtual uint32 Run() override`
- L129 _public function_ `virtual void Stop() override`
- L134 _public function_ `virtual void Exit() override`
- L139 _protected function_ `void Update(const FTimespan& SocketWaitTime)` — Update this socket receiver.
- L170 _protected function_ `virtual void Tick() override`
- L178 _private member_ `FSocket* Socket;` — The network socket.
- L181 _private member_ `ISocketSubsystem* SocketSubsystem;` — Pointer to the socket sub-system.
- L184 _private member_ `std::atomic<bool> bStopping;` — Flag indicating that the thread is stopping.
- L187 _private member_ `FRunnableThread* Thread;` — The thread object.
- L190 _private member_ `FString ThreadName;` — The receiver thread's name.
- L193 _private member_ `FTimespan WaitTime;` — The amount of time to wait for inbound packets.
- L196 _private member_ `uint32 MaxReadBufferSize = 65507u;` — The maximum read buffer size used to read the socket.
- L199 _private member_ `uint32 ThreadStackSize = 128 * 1024;` — Thread stack size to use.
- L204 _private member_ `FOnSocketDataReceived DataReceivedDelegate;` — Holds the data received delegate.

#### Free symbols / members of external scopes

- L21 _typedef_ `typedef TSharedPtr<FArrayReader, ESPMode::ThreadSafe> FArrayReaderPtr;` — Temporary fix for concurrency crashes. This whole class will be redesigned.
- L29 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSocketDataReceived, const FArrayReaderPtr&, const FIPv4Endpoint&);` — Delegate type for received data. The first parameter is the received data. The second parameter is sender's IP endpoint.
- L29 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSocketDataReceived, const FArrayReaderPtr&, const FIPv4Endpoint&);` — Delegate type for received data. The first parameter is the received data. The second parameter is sender's IP endpoint.

### `Source/Runtime/Networking/Public/Common/UdpSocketSender.h` (Public)


#### class `FUdpSocketSender`  
`class FUdpSocketSender : public FRunnable , private FSingleThreadRunnable`  
_L21-249_
- inherits: `FRunnable,FSingleThreadRunnable`
- desc: Asynchronously sends data to an UDP socket. @todo networking: gmp: implement rate limits
- L52 _public function_ `FUdpSocketSender(FSocket* InSocket, const TCHAR* ThreadDescription) : SendRate(0) , Socket(InSocket) , Stopping(false) , WaitTime(FTimespan::FromMilliseconds(100))` — Creates and initializes a new socket sender. @param InSocket The UDP socket to use for sending data. @param ThreadDescription The thread description text (for debugging).
- L69 _public function_ `virtual ~FUdpSocketSender()` — Virtual destructor.
- L88 _public function_ `uint32 GetSendRate() const` — Gets the maximum send rate (in bytes per second). @return Current send rate.
- L98 _public function_ `uint32 GetThroughput() const` — Gets the current throughput (in bytes per second). @return Current throughput.
- L110 _public function_ `bool Send(const TSharedRef<TArray<uint8>, ESPMode::ThreadSafe>& Data, const FIPv4Endpoint& Recipient)` — Sends data to the specified recipient. @param Data The data to send. @param Recipient The recipient. @return true if the data will be sent, false otherwise.
- L128 _public function_ `void SetSendRate(uint32 Rate)` — Sets the send rate (in bytes per second). @param Rate The new send rate (0 = unlimited). @see SetWaitTime
- L139 _public function_ `void SetWaitTime(const FTimespan& Timespan)` — Sets the maximum time span to wait for work items. @param Timespan The wait time. @see SetSendRate
- L148 _public function_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override`
- L153 _public function_ `virtual bool Init() override`
- L158 _public function_ `virtual uint32 Run() override`
- L175 _public function_ `virtual void Stop() override`
- L181 _public function_ `virtual void Exit() override`
- L191 _protected function_ `bool Update(const FTimespan& SocketWaitTime)` — Update this socket sender. @param Time to wait for the socket. @return true on success, false otherwise.
- L219 _protected function_ `virtual void Tick() override`
- L227 _private member_ `TQueue<FPacket, EQueueMode::Mpsc> SendQueue;` — The send queue.
- L230 _private member_ `uint32 SendRate;` — The send rate.
- L233 _private member_ `FSocket* Socket;` — The network socket.
- L236 _private member_ `bool Stopping;` — Flag indicating that the thread is stopping.
- L239 _private member_ `FRunnableThread* Thread;` — The thread object.
- L242 _private member_ `uint32 Throughput;` — The current throughput.
- L245 _private member_ `FTimespan WaitTime;` — The amount of time to wait for inbound packets.
- L248 _private member_ `FEvent* WorkEvent;` — An event signaling that inbound messages need to be processed.

#### struct `FUdpSocketSender::FPacket`  
`struct FPacket`  
_L26-42_
- desc: Structure for outbound packets.
- L29 _public member_ `TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> Data;` — Holds the packet's data.
- L32 _public member_ `FIPv4Endpoint Recipient;` — Holds the recipient.
- L35 _public function_ `FPacket()` — Default constructor.
- L38 _public function_ `FPacket(const TSharedRef<TArray<uint8>, ESPMode::ThreadSafe>& InData, const FIPv4Endpoint& InRecipient) : Data(InData) , Recipient(InRecipient)` — Creates and initializes a new instance.

### `Source/Runtime/Networking/Public/Interfaces/INetworkingModule.h` (Public)


#### class `INetworkingModule`  
`class INetworkingModule : public IModuleInterface`  
_L11-17_
- inherits: `IModuleInterface`
- desc: Interface for networking modules.
- L16 _protected function_ `INetworkingModule()`

### `Source/Runtime/Networking/Public/Interfaces/IPv4/IPv4Address.h` (Public)


#### struct `FIPv4Address`  
`struct FIPv4Address`  
_L15-306_
- desc: Implements an IPv4 address.
- L41 _public function_ `FIPv4Address()` — Default constructor.
- L53 _public function_ `FIPv4Address(uint8 InA, uint8 InB, uint8 InC, uint8 InD) #if PLATFORM_LITTLE_ENDIAN : D(InD) , C(InC) , B(InB) , A(InA) #else : A(InA) , B(InB) , C(InC) , D(InD) #endif` — Creates and initializes a new IPv4 address with the specified components. The created IP address has the value A.B.C.D. @param InA The first component. @param InB The second component. @param InC The third component. @param InD The fourth component.
- L72 _public function_ `FIPv4Address(uint32 InValue) : Value(InValue)` — Creates and initializes a new IPv4 address with the specified value. @param InValue The address value (in host byte order).
- L84 _public function_ `bool operator==(const FIPv4Address& Other) const` — Compares this IPv4 address with the given address for equality. @param Other The address to compare with. @return true if the addresses are equal, false otherwise.
- L95 _public function_ `bool operator!=(const FIPv4Address& Other) const` — Compares this IPv4 address with the given address for inequality. @param Other The address to compare with. @return true if the addresses are not equal, false otherwise.
- L106 _public function_ `FIPv4Address operator|(const FIPv4SubnetMask& SubnetMask) const` — OR operator for masking IP addresses with a subnet mask. @param SubnetMask The subnet mask. @return The masked IP address.
- L117 _public function_ `FIPv4Address operator&(const FIPv4SubnetMask& SubnetMask) const` — AND operator for masking IP addresses with a subnet mask. @param SubnetMask The subnet mask. @return The masked IP address.
- L144 _public function_ `bool IsGlobalMulticast() const` — Checks whether this IP address is a global multicast address. Global multicast addresses are in the range 224.0.1.0 to 238.255.255.255. @return true if it is a global multicast address, false otherwise. @see IsLinkLocalMulticast, IsOrganizationLocalMulticast, IsSiteLocalMulticast
- L156 _public function_ `bool IsLinkLocal() const` — Checks whether this IP address is link local. Link local addresses are in the range 169.254.0.0/16 @return true if it is link local, false otherwise.
- L169 _public function_ `bool IsLinkLocalMulticast() const` — Checks whether this IP address is a link local multicast address. Link local multicast addresses have the form 224.0.0.x. @return true if it is a link local multicast address, false otherwise. @see IsGlobalMulticast, IsOrganizationLocalMulticast, IsSiteLocalMulticast
- L182 _public function_ `bool IsLoopbackAddress() const` — Checks whether this IP address is a loopback address. Loopback addresses have the form 127.x.x.x @return true if it is a loopback address, false otherwise. @see IsMulticastAddress
- L195 _public function_ `bool IsMulticastAddress() const` — Checks whether this IP address is a multicast address. Multicast addresses are in the range 224.0.0.0 to 239.255.255.255. @return true if it is a multicast address, false otherwise. @see IsLoopbackAddress
- L208 _public function_ `bool IsOrganizationLocalMulticast() const` — Checks whether this IP address is a organization local multicast address. Organization local multicast addresses are in the range 239.192.x.x to 239.195.x.x. @return true if it is a site local multicast address, false otherwise. @see IsGlobalMulticast, IsLinkLocalMulticast, IsSiteLocalMulticast
- L223 _public function_ `bool IsSiteLocalAddress() const` — Checks whether this IP address is a site local address. Site local addresses have one of the following forms: 10.x.x.x 172.16-31.x.x 192.168.x.x @return true if it is a site local address, false otherwise.
- L236 _public function_ `bool IsSiteLocalMulticast() const` — Checks whether this IP address is a site local multicast address. Site local multicast addresses have the form 239.255.0.x. @return true if it is a site local multicast address, false otherwise. @see IsGlobalMulticast, IsLinkLocalMulticast, IsOrganizationLocalMulticast
- L247 _public function_ `bool IsSessionFrontendMulticast() const` — Checks whether this IP address is the multicast address we use for the Session Frontend Which is 230.0.0.1 @return true if this address matches, false otherwise.
- L258 _public prototype_ `FString ToString() const;` — Gets the string representation for this address. @return String representation. @see Parse, ToText
- L266 _public function_ `FText ToText() const` — Gets the display text representation. @return Text representation. @see ToString
- L294 _public prototype_ `static bool Parse(const FString& AddressString, FIPv4Address& OutAddress);` — Converts a string to an IPv4 address. @param AddressString The string to convert. @param OutAddress Will contain the parsed address. @return true if the string was converted successfully, false otherwise. @see ToString
- L299 _public member_ `static const FIPv4Address Any;` — Defines the wild card address, which is 0.0.0.0
- L302 _public member_ `static const FIPv4Address InternalLoopback;` — Defines the internal loopback address, which is 127.0.0.1
- L305 _public member_ `static const FIPv4Address LanBroadcast;` — Defines the broadcast address for the 'zero network' (i.e. LAN), which is 255.255.255.255.

#### union `FIPv4Address::(anonymous)`  
``  
_L18-36_

#### struct `FIPv4Address::__anond76de3b2010a::(anonymous)`  
``  
_L21-32_

#### Free symbols / members of external scopes

- L24 _member_ `uint8 D, C, B, A;` (scope `FIPv4Address::__anond76de3b2010a::__anond76de3b20208`)
- L24 _member_ `uint8 D, C, B, A;` (scope `FIPv4Address::__anond76de3b2010a::__anond76de3b20208`)
- L24 _member_ `uint8 D, C, B, A;` (scope `FIPv4Address::__anond76de3b2010a::__anond76de3b20208`)
- L24 _member_ `uint8 D, C, B, A;` (scope `FIPv4Address::__anond76de3b2010a::__anond76de3b20208`)
- L35 _member_ `uint32 Value;` (scope `FIPv4Address::__anond76de3b2010a`) — The IP address value in host byte order.
- L129 _function_ `friend FArchive& operator<<(FArchive& Ar, FIPv4Address& IpAddress)` — Serializes the given IPv4 address from or into the specified archive. @param Ar The archive to serialize from or into. @param IpAddress The address to serialize. @return The archive.
- L279 _function_ `friend uint32 GetTypeHash(const FIPv4Address& Address)` — Gets the hash for specified IPv4 address. @param Address The address to get the hash for. @return Hash value.

### `Source/Runtime/Networking/Public/Interfaces/IPv4/IPv4Endpoint.h` (Public)


#### struct `FIPv4Endpoint`  
`struct FIPv4Endpoint`  
_L26-215_
- desc: Implements an endpoint for IPv4 networks. An endpoint consists of an IPv4 address and a port number. @todo gmp: add IPv6 support and rename this to FIpEndpoint?
- L29 _public member_ `FIPv4Address Address;` — Holds the endpoint's IP address.
- L32 _public member_ `uint16 Port;` — Holds the endpoint's port number.
- L37 _public function_ `FIPv4Endpoint()` — Default constructor.
- L45 _public function_ `FIPv4Endpoint(const FIPv4Address& InAddress, uint16 InPort) : Address(InAddress) , Port(InPort)` — Creates and initializes a new IPv4 endpoint with the specified NetID and port. @param InAddress The endpoint's IP address. @param InPort The endpoint's port number.
- L57 _public function_ `FIPv4Endpoint(const TSharedPtr<FInternetAddr>& InternetAddr)` — Creates and initializes a new IPv4 endpoint from a given FInternetAddr object. Note: this constructor will be removed after the socket subsystem has been refactored. @param InternetAddr The Internet address.
- L75 _public function_ `bool operator==(const FIPv4Endpoint& Other) const` — Compares this IPv4 endpoint with the given endpoint for equality. @param Other The endpoint to compare with. @return true if the endpoints are equal, false otherwise.
- L86 _public function_ `bool operator!=(const FIPv4Endpoint& Other) const` — Compares this IPv4 address with the given endpoint for inequality. @param Other The endpoint to compare with. @return true if the endpoints are not equal, false otherwise.
- L112 _public function_ `TSharedRef<FInternetAddr> ToInternetAddr() const` — Converts this endpoint to an FInternetAddr object. Note: this method will be removed after the socket subsystem is refactored. @return Internet address object representing this endpoint.
- L132 _public function_ `TSharedRef<FInternetAddr> ToInternetAddrIPV4() const` — Converts this endpoint to an FInternetAddr object. Note: this method will be removed after the socket subsystem is refactored. @return Internet address object representing this endpoint.
- L156 _public prototype_ `FString ToString() const;` — Gets a string representation for this endpoint. @return String representation. @see Parse, ToText
- L164 _public function_ `FText ToText() const` — Gets the display text representation. @return Text representation. @see ToString
- L185 _public prototype_ `static void Initialize();` — Initializes the IP endpoint functionality.
- L195 _public prototype_ `static bool Parse(const FString& EndpointString, FIPv4Endpoint& OutEndpoint);` — Converts a string to an IPv4 endpoint. @param EndpointString The string to convert. @param OutEndpoint Will contain the parsed endpoint. @return true if the string was converted successfully, false otherwise. @see ToString
- L204 _public prototype_ `static bool FromHostAndPort(const FString& HostAndPortString, FIPv4Endpoint& OutEndpoint);` — Resolves a hostname and port to an IPv4 endpoint. @param HostAndPortString The host and port to resolve. @param OutEndpoint Will contain the resolved endpoint. @return true if the host and port were parsed and resolved successfully, false otherwise.
- L209 _public member_ `static const FIPv4Endpoint Any;` — Defines the wild card endpoint, which is 0.0.0.0:0
- L214 _private member_ `static ISocketSubsystem* CachedSocketSubsystem;` — ISocketSubsystem::Get() is not thread-safe, so we cache it here.

#### Free symbols / members of external scopes

- L98 _function_ `friend FArchive& operator<<(FArchive& Ar, FIPv4Endpoint& Endpoint)` — Serializes the given endpoint from or into the specified archive. @param Ar The archive to serialize from or into. @param Endpoint The endpoint to serialize. @return The archive.
- L177 _function_ `friend uint32 GetTypeHash(const FIPv4Endpoint& Endpoint)` — Gets the hash for specified IPv4 endpoint. @param Endpoint The endpoint to get the hash for. @return Hash value.

### `Source/Runtime/Networking/Public/Interfaces/IPv4/IPv4Subnet.h` (Public)


#### struct `FIPv4Subnet`  
`struct FIPv4Subnet`  
_L19-145_
- desc: Implements a IPv4 subnet descriptor. @todo gmp: add IsValid() method
- L22 _public member_ `FIPv4Address Address;` — Holds the subnet's address.
- L25 _public member_ `FIPv4SubnetMask Mask;` — Holds the subnet's mask.
- L30 _public function_ `FIPv4Subnet()` — Default constructor.
- L38 _public function_ `FIPv4Subnet(const FIPv4Address& InAddress, const FIPv4SubnetMask& InMask) : Address(InAddress) , Mask(InMask)` — Creates and initializes a new IPv4 subnet with the specified address and mask. @param InAddress The subnet's address. @param InMask The subnet's mask.
- L51 _public function_ `bool operator==(const FIPv4Subnet& Other) const` — Compares this IPv4 subnet descriptor with the given subnet for equality. @param Other The subnet to compare with. @return true if the subnets are equal, false otherwise.
- L62 _public function_ `bool operator!=(const FIPv4Subnet& Other) const` — Compares this IPv4 subnet descriptor with the given subnet for inequality. @param Other The subnet to compare with. @return true if the subnets are not equal, false otherwise.
- L86 _public function_ `FIPv4Address BroadcastAddress() const` — Get the broadcast address for this subnet. @return The broadcast address.
- L97 _public function_ `bool ContainsAddress(const FIPv4Address& TestAddress)` — Checks whether the subnet contains the specified IP address. @param TestAddress The address to check. @return true if the subnet contains the address, false otherwise.
- L108 _public prototype_ `FString ToString() const;` — Converts this IP subnet to its string representation. @return String representation. @see Parse, ToText
- L116 _public function_ `FText ToText() const` — Gets the display text representation. @return Text representation. @see ToString
- L144 _public prototype_ `static bool Parse(const FString& SubnetString, FIPv4Subnet& OutSubnet);` — Converts a string to an IPv4 subnet. @param SubnetString The string to convert. @param OutSubnet Will contain the parsed subnet. @return true if the string was converted successfully, false otherwise. @see ToString

#### Free symbols / members of external scopes

- L74 _function_ `friend FArchive& operator<<(FArchive& Ar, FIPv4Subnet& Subnet)` — Serializes the given subnet descriptor from or into the specified archive. @param Ar The archive to serialize from or into. @param Subnet The subnet descriptor to serialize. @return The archive.
- L129 _function_ `friend uint32 GetTypeHash(const FIPv4Subnet& Subnet)` — Gets the hash for specified IPv4 subnet. @param Subnet The subnet to get the hash for. @return Hash value.

### `Source/Runtime/Networking/Public/Interfaces/IPv4/IPv4SubnetMask.h` (Public)


#### enum `EIPv4SubnetClasses::Type`  
`enum Type`  
_L17-30_
- desc: Enumerates IPv4 subnet classes.
- L20 _public enumerator_ `Invalid` — Invalid subnet mask.
- L23 _public enumerator_ `ClassA` — Class A subnet.
- L26 _public enumerator_ `ClassB` — Class B subnet.
- L29 _public enumerator_ `ClassC` — Class C subnet.

#### struct `FIPv4SubnetMask`  
`struct FIPv4SubnetMask`  
_L37-214_
- desc: Implements an IPv4 subnet mask.
- L63 _public function_ `FIPv4SubnetMask()` — Default constructor.
- L75 _public function_ `FIPv4SubnetMask(uint8 InA, uint8 InB, uint8 InC, uint8 InD) #if PLATFORM_LITTLE_ENDIAN : D(InD) , C(InC) , B(InB) , A(InA) #else : A(InA) , B(InB) , C(InC) , D(InD) #endif` — Creates and initializes a new IPv4 subnet mask with the specified components. The created subnet mask has the value A.B.C.D. @param InA The first component. @param InB The second component. @param InC The third component. @param InD The fourth component.
- L94 _public function_ `FIPv4SubnetMask(uint32 InValue) : Value(InValue)` — Creates and initializes a new IPv4 subnet mask with the specified value. @param InValue The address value (in host byte order).
- L106 _public function_ `bool operator==(const FIPv4SubnetMask& Other) const` — Compares this subnet mask with the given mask for equality. @param Other The subnet mask to compare with. @return true if the subnet masks are equal, false otherwise.
- L117 _public function_ `bool operator!=(const FIPv4SubnetMask& Other) const` — Compares this subnet mask with the given address for inequality. @param Other The subnet mask to compare with. @return true if the subnet masks are not equal, false otherwise.
- L127 _public function_ `FIPv4SubnetMask operator~() const` — Returns an inverted subnet mask. @return Inverted subnet mask.
- L151 _public function_ `EIPv4SubnetClasses::Type GetClass() const` — Gets the subnet class that this mask specifies. @return Subnet class.
- L177 _public prototype_ `FString ToString() const;` — Converts this IP address to its string representation. @return String representation. @see Parse, ToText
- L185 _public function_ `FText ToText() const` — Gets the display text representation. @return Text representation. @see ToString
- L213 _public prototype_ `static bool Parse(const FString& MaskString, FIPv4SubnetMask& OutMask);` — Converts a string to an IPv4 subnet mask. @param MaskString The string to convert. @param OutMask Will contain the parsed subnet mask. @return true if the string was converted successfully, false otherwise. @see ToString

#### union `FIPv4SubnetMask::(anonymous)`  
``  
_L40-58_

#### struct `FIPv4SubnetMask::__anon235f3e89010a::(anonymous)`  
``  
_L43-54_

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace EIPv4SubnetClasses`
- L46 _member_ `uint8 D, C, B, A;` (scope `FIPv4SubnetMask::__anon235f3e89010a::__anon235f3e890208`)
- L46 _member_ `uint8 D, C, B, A;` (scope `FIPv4SubnetMask::__anon235f3e89010a::__anon235f3e890208`)
- L46 _member_ `uint8 D, C, B, A;` (scope `FIPv4SubnetMask::__anon235f3e89010a::__anon235f3e890208`)
- L46 _member_ `uint8 D, C, B, A;` (scope `FIPv4SubnetMask::__anon235f3e89010a::__anon235f3e890208`)
- L57 _member_ `int32 Value;` (scope `FIPv4SubnetMask::__anon235f3e89010a`) — The subnet mask value in host byte order.
- L139 _function_ `friend FArchive& operator<<(FArchive& Ar, FIPv4SubnetMask& SubnetMask)` — Serializes the given subnet mask from or into the specified archive. @param Ar The archive to serialize from or into. @param SubnetMask The subnet mask to serialize. @return The archive.
- L198 _function_ `friend uint32 GetTypeHash(const FIPv4SubnetMask& SubnetMask)` — Gets the hash for specified IPv4 subnet mask. @param SubnetMask The subnet mask to get the hash for. @return Hash value.

### `Source/Runtime/Networking/Public/Interfaces/Steam/SteamEndpoint.h` (Public)


#### class `FSteamEndpoint`  
`class FSteamEndpoint`  
_L14-121_
- desc: Implements a Steam endpoint.
- L19 _public function_ `FSteamEndpoint()` — Default constructor.
- L27 _public function_ `FSteamEndpoint(uint64 InUniqueNetId, int32 InSteamChannel) : SteamChannel(InSteamChannel) , UniqueNetId(InUniqueNetId)` — Creates and initializes a new Steam address with the specified components. @param InUniqueNetId The unique network identifier. @param InSteamChannel The Steam channel number.
- L40 _public function_ `bool operator==(const FSteamEndpoint& Other) const` — Compares this Steam address with the given address for equality. @param Other The address to compare with. @return true if the addresses are equal, false otherwise.
- L51 _public function_ `bool operator!=(const FSteamEndpoint& Other) const` — Compares this Steam address with the given address for inequality. @param Other The address to compare with. @return true if the addresses are not equal, false otherwise.
- L76 _public function_ `int32 GetSteamChannel() const` — Gets the Steam channel number. @return Steam channel number. @see GetUniqueNetId
- L87 _public function_ `uint64 GetUniqueNetId() const` — Gets the unique network identifier. @return Unique network identifier. @see GetSteamChannel
- L98 _public prototype_ `FString ToString() const;` — Gets the string representation for this address. @return String representation.
- L117 _private member_ `int32 SteamChannel;` — Holds the Steam channel number.
- L120 _private member_ `uint64 UniqueNetId;` — Holds the unique network identifier.

#### Free symbols / members of external scopes

- L63 _function_ `friend FArchive& operator<<(FArchive& Ar, FSteamEndpoint& SteamEndpoint)` — Serializes the given Steam address from or into the specified archive. @param Ar The archive to serialize from or into. @param IpAddress The address to serialize. @return The archive.
- L109 _function_ `friend uint32 GetTypeHash(const FSteamEndpoint& Address)` — Gets the hash for specified Steam address. @param Address - The address to get the hash for. @return Hash value.

### `Source/Runtime/Networking/Public/Networking.h` (Public)
_(no declarations extracted)_
