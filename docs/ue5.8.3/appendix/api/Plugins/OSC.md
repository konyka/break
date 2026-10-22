# Plugins / OSC

- module root: `Plugins/Runtime/OSC/Source/OSC`
- headers: 16; symbols: 503
- symbol kinds: class=20, delegate=9, enum=2, enumerator=28, externvar=2, function=48, member=50, namespace=26, prototype=306, struct=5, typedef=5, union=2
- PrivateDependencyModuleNames: InputCore, Networking, Sockets
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/OSC/Source/OSC/Private/OSCBundlePacket.h` (Private)


#### class `UE::OSC::FBundlePacket`  
`class FBundlePacket : public FPacketBase`  
_L11-43_
- inherits: `FPacketBase`
- L14 _public prototype_ `FBundlePacket(FIPv4Endpoint InEndpoint = FIPv4Endpoint::Any);`
- L16 _public prototype_ `virtual ~FBundlePacket() = default;`
- L19 _public prototype_ `void SetTimeTag(uint64 NewTimeTag);` — Set the bundle time tag.
- L22 _public prototype_ `uint64 GetTimeTag() const;` — Get the bundle time tag.
- L25 _public prototype_ `TArray<TSharedRef<UE::OSC::IPacket>>& GetPackets();` — Get OSC packet bundle.
- L27 _public prototype_ `virtual bool IsBundle() override;`
- L28 _public prototype_ `virtual bool IsMessage() override;`
- L31 _public prototype_ `virtual void WriteData(FStream& Stream) override;` — Writes bundle data into the OSC stream.
- L35 _public prototype_ `virtual void ReadData(FStream& Stream) override;` — Reads bundle data from provided OSC stream, adding packet data to internal packet bundle.
- L39 _private member_ `TArray<TSharedRef<UE::OSC::IPacket>> Packets;` — Array of OSC packets.
- L42 _private member_ `FOSCData TimeTag;` — Bundle time tag.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace OSC` (scope `UE`)

### `Plugins/Runtime/OSC/Source/OSC/Private/OSCClientProxy.h` (Private)


#### class `UE::OSC::FClientProxy`  
`class FClientProxy : public IClientProxy`  
_L17-51_
- inherits: `IClientProxy`
- L20 _public prototype_ `FClientProxy(const FString& InClientName);`
- L21 _public prototype_ `virtual ~FClientProxy();`
- L24 _public function_ `virtual void GetSendIPAddress(FString& InIPAddress, int32& Port) const` — `UE_DEPRECATED(5.5, "Use GetSendIPEndpoint instead")`
- L27 _public function_ `virtual bool SetSendIPAddress(const FString& InIPAddress, const int32 Port)` — `UE_DEPRECATED(5.5, "Use SetSendIPEndpoint instead")`
- L29 _public prototype_ `virtual const FIPv4Endpoint& GetSendIPEndpoint() const override;`
- L30 _public prototype_ `virtual void SetSendIPEndpoint(const FIPv4Endpoint& InEndpoint) override;`
- L32 _public prototype_ `bool IsActive() const override;`
- L34 _public prototype_ `void SendMessage(const FOSCMessage& Message) override;`
- L35 _public prototype_ `void SendBundle(const FOSCBundle& Bundle) override;`
- L37 _public prototype_ `void Stop() override;`
- L39 _public prototype_ `void SendPacket(UE::OSC::IPacket& Packet);`
- L43 _private member_ `FSocket* Socket = nullptr;` — Socket used to send the OSC packets.
- L46 _private member_ `FIPv4Endpoint IPEndpoint;` — IP Address used by socket.
- L49 _private member_ `FString DestroyedSocketDesc;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace OSC` (scope `UE`)

### `Plugins/Runtime/OSC/Source/OSC/Private/OSCMessagePacket.h` (Private)


#### class `UE::OSC::FPacketBase`  
`class FPacketBase : public IPacket`  
_L12-24_
- inherits: `IPacket`
- L15 _public prototype_ `FPacketBase(FIPv4Endpoint InEndpoint = FIPv4Endpoint::Any);`
- L17 _public prototype_ `virtual ~FPacketBase() = default;`
- L20 _public prototype_ `virtual const FIPv4Endpoint& GetIPEndpoint() const override;` — Get endpoint IP address and port responsible for creation/forwarding of packet
- L23 _protected member_ `FIPv4Endpoint IPEndpoint;`

#### class `UE::OSC::FMessagePacket`  
`class FMessagePacket : public FPacketBase`  
_L27-70_
- inherits: `FPacketBase`
- L30 _public prototype_ `FMessagePacket() = default;`
- L31 _public prototype_ `FMessagePacket(const FIPv4Endpoint& InEndpoint);`
- L32 _public prototype_ `virtual ~FMessagePacket() = default;`
- L35 _public prototype_ `void AddArgument(FOSCData OSCData);` — Adds argument to argument array
- L38 _public prototype_ `void EmptyArguments();` — Empties all arguments
- L41 _public prototype_ `void SetAddress(FOSCAddress InAddress);` — Set OSC message address.
- L44 _public prototype_ `void SetArguments(TArray<FOSCData> Args);` — Sets argument array to the given values
- L47 _public prototype_ `virtual const FOSCAddress& GetAddress() const;` — Get OSC message address.
- L50 _public prototype_ `virtual const TArray<FOSCData>& GetArguments() const;` — Get arguments array.
- L53 _public prototype_ `virtual bool IsBundle();` — Returns false to indicate type is not OSC bundle.
- L56 _public prototype_ `virtual bool IsMessage();` — Returns true to indicate its an OSC message.
- L59 _public prototype_ `virtual void WriteData(FStream& Stream) override;` — Write message data into an OSC stream.
- L62 _public prototype_ `virtual void ReadData(FStream& Stream) override;` — Reads message data from an OSC stream and creates new argument.
- L66 _private member_ `FOSCAddress Address;` — OSC address.
- L69 _private member_ `TArray<FOSCData> Arguments;` — List of argument data types.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace OSC` (scope `UE`)

### `Plugins/Runtime/OSC/Source/OSC/Private/OSCModule.h` (Private)


#### class `UE::OSC::FModule`  
`class FModule : public IModuleInterface`  
_L10-14_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace OSC` (scope `UE`)

### `Plugins/Runtime/OSC/Source/OSC/Private/OSCServerProxy.h` (Private)


#### class `UE::OSC::FServerProxy`  
`class FServerProxy : public IServerProxy , public TSharedFromThis<FServerProxy>`  
_L15-72_
- inherits: `IServerProxy,TSharedFromThis<FServerProxy>`
- L18 _public prototype_ `FServerProxy();`
- L19 _public prototype_ `virtual ~FServerProxy();`
- L22 _public prototype_ `virtual void AddClientToAllowList(const FString& InIPAddress) override;`
- L23 _public prototype_ `virtual void AddClientEndpointToAllowList(const FIPv4Endpoint& InIPv4Endpoint) override;`
- L25 _public prototype_ `virtual bool CanProcessPacket(TSharedRef<UE::OSC::IPacket> Packet) const override;`
- L26 _public prototype_ `virtual void ClearClientEndpointAllowList() override;`
- L28 _public prototype_ `virtual const TSet<FIPv4Endpoint>& GetClientEndpointAllowList() const override;`
- L29 _public prototype_ `virtual FString GetDescription() const override;`
- L30 _public prototype_ `virtual const FIPv4Endpoint& GetIPEndpoint() const override;`
- L31 _public prototype_ `virtual bool GetMulticastLoopback() const override;`
- L34 _public prototype_ `virtual FString GetIpAddress() const override;` — `UE_DEPRECATED(5.5, "Use GetIPEndpoint instead")`
- L37 _public prototype_ `virtual int32 GetPort() const override;` — `UE_DEPRECATED(5.5, "Use GetIPEndpoint instead")`
- L39 _public prototype_ `virtual bool IsActive() const override;`
- L41 _public prototype_ `virtual void Listen(const FString& InServerName) override;`
- L43 _public prototype_ `virtual bool SetIPEndpoint(const FIPv4Endpoint& InEndpoint) override;`
- L44 _public prototype_ `virtual bool SetMulticastLoopback(bool bInMulticastLoopback) override;`
- L45 _public prototype_ `virtual void SetOnDispatchPacket(TSharedPtr<FOnDispatchPacket> OnDispatch) override;`
- L46 _public prototype_ `virtual void Stop() override;`
- L48 _public prototype_ `virtual void RemoveClientFromAllowList(const FString& InIPAddress) override;`
- L49 _public prototype_ `virtual void RemoveClientEndpointFromAllowList(const FIPv4Endpoint& InIPv4Endpoint) override;`
- L51 _public prototype_ `virtual void SetFilterClientsByAllowList(bool bInEnabled) override;`
- L56 _private prototype_ `void OnPacketReceived(FConstPacketDataRef InData, const FIPv4Endpoint& InEndpoint);` — Callback that receives data from a socket.
- L58 _private member_ `mutable FCriticalSection MutateDispatchFunctionCritSec;`
- L60 _private member_ `TSharedPtr<FServerReceiver> ServerReceiver;`
- L63 _private member_ `TSet<FIPv4Endpoint> ClientAllowList;` — Only packets from this list of client addresses will be processed if bFilterClientsByAllowList is true.
- L66 _private member_ `FIPv4Endpoint Endpoint = FIPv4Endpoint::Any;` — Endpoint to listen for OSC packets on. If set to 'Any', defaults to LocalHost
- L69 _private member_ `bool bMulticastLoopback = false;` — Whether or not to loopback if address provided is multicast
- L71 _private member_ `TSharedPtr<FOnDispatchPacket> OnDispatchFunction;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace OSC` (scope `UE`)

### `Plugins/Runtime/OSC/Source/OSC/Private/OSCServerReceiver.h` (Private)


#### class `UE::OSC::FServerReceiver`  
`class FServerReceiver : public TSharedFromThis<FServerReceiver> , public FRunnable , private FSingleThreadRunnable`  
_L26-73_
- inherits: `TSharedFromThis<FServerReceiver>,FRunnable,FSingleThreadRunnable`
- L45 _public prototype_ `explicit FServerReceiver(FPrivateToken, FOptions InOptions);`
- L46 _public prototype_ `virtual ~FServerReceiver();`
- L48 _public prototype_ `static TSharedRef<FServerReceiver> Launch(const FString& InName, const FIPv4Endpoint& InEndpoint, FOptions InOptions);`
- L50 _public prototype_ `FString GetDescription() const;`
- L53 _protected prototype_ `virtual uint32 Run() override;`
- L54 _protected prototype_ `virtual void Tick() override;`
- L57 _private prototype_ `bool BindSocket(ISocketSubsystem& SocketSubsystem, const FIPv4Endpoint& InEndpoint, TSharedRef<FInternetAddr> RemoteAddr, const FString& InName);`
- L58 _private prototype_ `bool InitMulticast(ISocketSubsystem& SocketSubsystem, const FIPv4Endpoint& InEndpoint, TSharedRef<FInternetAddr> RemoteAddr, const FString& InName);`
- L59 _private prototype_ `bool InitSocket(const FString& InName, FIPv4Endpoint InEndpoint);`
- L60 _private prototype_ `void StartThread(const FString& InName, const FIPv4Endpoint& InEndpoint);`
- L62 _private member_ `std::atomic<bool> bStopping { false };`
- L65 _private member_ `FUniqueSocket Socket;` — The network socket.
- L68 _private member_ `TSharedPtr<FRunnableThread> Thread;` — Dedicated thread for server to run on.
- L70 _private member_ `FString InvalidReceiverName;`
- L72 _private member_ `const FOptions Options;`

#### struct `UE::OSC::FServerReceiver::FPrivateToken`  
`struct FPrivateToken`  
_L31-31_
- L31 _public prototype_ `struct FPrivateToken`

#### struct `UE::OSC::FServerReceiver::FOptions`  
`struct FOptions`  
_L34-43_
- L36 _public member_ `FOnServerReceivedData ReceivedDataDelegate;`
- L37 _public member_ `bool bMulticastLoopback = false;`
- L39 _public member_ `EThreadPriority Priority = EThreadPriority::TPri_AboveNormal;`
- L40 _public member_ `int32 StackSize = 128 * 1024;`
- L41 _public member_ `FTimespan WaitTime = FTimespan::FromMilliseconds(100);`
- L42 _public member_ `uint32 MaxReadBufferSize = 65507u;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace OSC` (scope `UE`)
- L22 _typedef_ `using FPacketDataRef = TSharedRef<TArray<uint8>>;` (scope `UE::OSC`)
- L23 _typedef_ `using FConstPacketDataRef = TSharedRef<const TArray<uint8>>;` (scope `UE::OSC`)
- L24 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnServerReceivedData, FConstPacketDataRef, const FIPv4Endpoint&);`
- L24 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnServerReceivedData, FConstPacketDataRef, const FIPv4Endpoint&);` (scope `UE::OSC`)

### `Plugins/Runtime/OSC/Source/OSC/Public/OSCAddress.h` (Public)


#### struct `FOSCAddress`  
`struct FOSCAddress`  
_L19-156_
- reflection: `USTRUCT(BlueprintType)`
- L25 _private member_ `TArray<FString> Containers;` — Ordered array of container names
- L28 _private member_ `FString Method;` — Method name of string
- L31 _private member_ `bool bIsValidPattern;` — Cached values for validity and hash
- L32 _private member_ `bool bIsValidPath;`
- L33 _private member_ `uint32 Hash;`
- L35 _private prototype_ `void CacheAggregates();`
- L38 _public prototype_ `FOSCAddress();`
- L39 _public prototype_ `FOSCAddress(const FString& InValue);`
- L42 _public prototype_ `bool IsValidPattern() const;` — Returns whether address is valid pattern
- L45 _public prototype_ `bool IsValidPath() const;` — Returns whether address is valid path
- L50 _public prototype_ `bool Matches(const FOSCAddress& InAddress) const;` — Returns if this address is a pattern that matches InAddress' path. If passed address is not a valid path, returns false.
- L53 _public prototype_ `bool PushContainer(FString Container);` — Pushes container onto end of address' ordered array of containers
- L56 _public prototype_ `bool PushContainers(TArray<FString> NewContainers);` — Pushes containers onto end of address' ordered array of containers
- L59 _public prototype_ `FString PopContainer();` — Pops container from ordered array of containers
- L62 _public prototype_ `bool PopContainer(FString& OutContainer);` — Pops container from ordered array of containers
- L65 _public prototype_ `TArray<FString> PopContainers(int32 NumToPop);` — Pops containers off end of address' ordered array of containers
- L68 _public prototype_ `bool PopContainers(int32 NumToPop, TArray<FString>& OutContainers);` — Pops containers off end of address' ordered array of containers
- L71 _public prototype_ `bool RemoveContainers(int32 InIndex, int32 InCount);` — Removes containers from container array at index until count
- L74 _public prototype_ `void ClearContainers();` — Clears ordered array of containers
- L77 _public prototype_ `const FString& GetMethod() const;` — Get method name of address
- L80 _public prototype_ `bool GetNumericPrefix(int32& OutPrefix) const;` — Returns numeric prefix of OSC method if is numeric
- L83 _public prototype_ `bool GetNumericSuffix(int32& OutSuffix) const;` — Returns numeric suffix of OSC method if is numeric
- L86 _public prototype_ `bool Set(TArray<FString> NewContainers, FString NewMethod);` — Sets the address to the given array of containers and provided method
- L89 _public prototype_ `bool SetMethod(FString NewMethod);` — Sets the method name of address
- L92 _public prototype_ `FString GetContainerPath() const;` — Returns container path of OSC address in the form '/Container1/Container2'
- L95 _public prototype_ `FString GetContainer(int32 Index) const;` — Returns container at provided Index.  If Index is out-of-bounds, returns empty string.
- L98 _public prototype_ `void GetContainers(TArray<FString>& OutContainers) const;` — Builds referenced array of address of containers in order
- L101 _public prototype_ `FString GetFullPath() const;` — Returns full path of OSC address in the form '/Container1/Container2/Method'
- L103 _public function_ `bool operator== (const FOSCAddress& InAddress) const`
- L131 _public function_ `FOSCAddress& operator/= (const FOSCAddress& InAddress)`
- L142 _public function_ `FOSCAddress operator/ (const FOSCAddress& InAddress) const`
- L155 _private prototype_ `bool PushContainersInternal(TArray<FString>&& InContainers);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace OSC` (scope `UE`)
- L13 _externvar_ `extern const FString BundleTag;` (scope `UE::OSC`)
- L14 _externvar_ `extern const FString PathSeparator;` (scope `UE::OSC`)
- L149 _function_ `friend uint32 GetTypeHash(const FOSCAddress& InAddress)`

### `Plugins/Runtime/OSC/Source/OSC/Public/OSCBundle.h` (Public)


#### struct `FOSCBundle`  
`struct FOSCBundle`  
_L9-33_
- reflection: `USTRUCT(BlueprintType)`
- L13 _public prototype_ `FOSCBundle();`
- L14 _public prototype_ `explicit FOSCBundle(const TSharedRef<UE::OSC::IPacket>& InPacket);`
- L17 _public prototype_ `FOSCBundle(const TSharedPtr<UE::OSC::IPacket>& InPacket);` — `UE_DEPRECATED(5.5, "Use explicit shared ref constructor instead")`
- L19 _public prototype_ `~FOSCBundle() = default;`
- L22 _public prototype_ `void SetPacket(TSharedPtr<UE::OSC::IPacket>& InPacket);` — `UE_DEPRECATED(5.5, "Use shared ref setter instead")`
- L24 _public prototype_ `void SetPacket(const TSharedRef<UE::OSC::IPacket>& InPacket);`
- L27 _public prototype_ `const TSharedPtr<UE::OSC::IPacket>& GetPacket() const;` — `UE_DEPRECATED(5.5, "Use shared ref getter instead")`
- L29 _public prototype_ `const TSharedRef<UE::OSC::IPacket>& GetPacketRef() const;`
- L32 _private member_ `TSharedRef<UE::OSC::IPacket> Packet;`

### `Plugins/Runtime/OSC/Source/OSC/Public/OSCClient.h` (Public)


#### class `UE::OSC::IClientProxy`  
`class IClientProxy`  
_L16-39_
- desc: Interface for internal network implementation of sending OSC messages & bundles as a client.
- L20 _public prototype_ `static TUniquePtr<IClientProxy> Create(const FString& ClientName);` — Creates a new client proxy that can be used by any system where the provided dispatch callback is called on a worker thread.
- L22 _public prototype_ `virtual ~IClientProxy() = default;`
- L25 _public prototype_ `virtual void GetSendIPAddress(FString& InIPAddress, int32& Port) const = 0;` — `UE_DEPRECATED(5.5, "Use GetSendIPEndpoint instead")`
- L28 _public prototype_ `virtual bool SetSendIPAddress(const FString& InIPAddress, const int32 Port) = 0;` — `UE_DEPRECATED(5.5, "Use SetSendIPEndpoint instead")`
- L30 _public prototype_ `virtual const FIPv4Endpoint& GetSendIPEndpoint() const = 0;`
- L31 _public prototype_ `virtual void SetSendIPEndpoint(const FIPv4Endpoint& InEndpoint) = 0;`
- L33 _public prototype_ `virtual bool IsActive() const = 0;`
- L35 _public prototype_ `virtual void SendMessage(const FOSCMessage& Message) = 0;`
- L36 _public prototype_ `virtual void SendBundle(const FOSCBundle& Bundle) = 0;`
- L38 _public prototype_ `virtual void Stop() = 0;`

#### class `IOSCClientProxy`  
`class IOSCClientProxy : public UE::OSC::IClientProxy`  
_L43-50_
- inherits: `UE::OSC::IClientProxy`
- desc: For backward compat.  To be deprecated
- L47 _public prototype_ `IOSCClientProxy() = default;` — `UE_DEPRECATED(5.5, "Use UE::OSC::IClientProxy instead")`
- L49 _public prototype_ `virtual ~IOSCClientProxy() = default;`

#### class `UOSCClient`  
`class UOSCClient : public UObject`  
_L53-87_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L58 _public prototype_ `void Connect();`
- L60 _public prototype_ `bool IsActive() const;`
- L64 _public prototype_ `void GetSendIPAddress(UPARAM(ref) FString& IPAddress, UPARAM(ref) int32& Port);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Gets the OSC Client IP address and port.
- L69 _public prototype_ `bool SetSendIPAddress(const FString& IPAddress, const int32 Port);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Sets the OSC Client IP address and port. Returns whether address and port was successfully set.
- L73 _public prototype_ `void SendOSCMessage(UPARAM(ref) FOSCMessage& Message);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Send OSC message to  a specific address.
- L77 _public prototype_ `void SendOSCBundle(UPARAM(ref) FOSCBundle& Bundle);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Send OSC Bundle over the network.
- L80 _protected prototype_ `void BeginDestroy() override;`
- L83 _protected prototype_ `void Stop();` — Stop and tidy up network socket.
- L86 _protected member_ `TUniquePtr<UE::OSC::IClientProxy> ClientProxy;` — Pointer to internal implementation of client proxy

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace OSC` (scope `UE`)

### `Plugins/Runtime/OSC/Source/OSC/Public/OSCLog.h` (Public)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOSC, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOSC, Log, All);`

### `Plugins/Runtime/OSC/Source/OSC/Public/OSCManager.h` (Public)


#### class `UOSCManager`  
`class UOSCManager : public UBlueprintFunctionLibrary`  
_L25-250_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L34 _public prototype_ `static UOSCServer* CreateOSCServer(FString ReceiveIPAddress, int32 Port, bool bMulticastLoopback, bool bStartListening, FString ServerName, UObject* Outer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Creates an OSC Server.  If ReceiveIPAddress left empty (or '0'), attempts to use LocalHost IP address. If StartListening set, immediately begins listening on creation.
- L39 _public prototype_ `static UOSCClient* CreateOSCClient(FString SendIPAddress, int32 Port, FString ClientName, UObject* Outer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Creates an OSC Client.  If SendIPAddress left empty (or '0') attempts to use LocalHost IP address.
- L43 _public prototype_ `static UPARAM(DisplayName = "Bundle") FOSCBundle& AddMessageToBundle(const FOSCMessage& Message, UPARAM(ref) FOSCBundle& Bu` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Add OSC Message to Bundle", Keywords = "osc message bundle"))` — Adds provided message packet to bundle.
- L47 _public prototype_ `static UPARAM(DisplayName = "OutBundle") FOSCBundle& AddBundleToBundle(const FOSCBundle& InBundle, UPARAM(ref) FOSCBundle& Ou` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Add OSC Bundle to Bundle", Keywords = "osc message"))` — Adds bundle packet to bundle.
- L51 _public prototype_ `static UPARAM(DisplayName = "Bundles") TArray<FOSCBundle> GetBundlesFromBundle(const FOSCBundle& B` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Bundles From Bundle", Keywords = "osc bundle"))` — Fills array with child bundles found in bundle.
- L55 _public prototype_ `static UPARAM(DisplayName = "Message") FOSCMessage GetMessageFromBundle(const FOSCBundle& Bundle, int32 Index, bool& bSucc` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message From Bundle At Index", Keywords = "osc bundle message"))` — Returns message found in bundle at ordered index.
- L59 _public prototype_ `static UPARAM(DisplayName = "Messages") TArray<FOSCMessage> GetMessagesFromBundle(const FOSCBundle&` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Messages From Bundle", Keywords = "osc bundle message"))` — Fills array with messages found in bundle.
- L63 _public prototype_ `static UPARAM(DisplayName = "Message") FOSCMessage& ClearMessage(UPARAM(ref) FOSCMessage& Me` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Clear OSC Message", Keywords = "osc message"))` — Clears provided message of all arguments.
- L67 _public prototype_ `static UPARAM(DisplayName = "Bundle") FOSCBundle& ClearBundle(UPARAM(ref) FOSCBundle& Bu` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Clear OSC Bundle", Keywords = "osc message"))` — Clears provided bundle of all internal messages/bundle packets.
- L71 _public prototype_ `static UPARAM(DisplayName = "Message") FOSCMessage& AddFloat(UPARAM(ref) FOSCMessage& Message, float` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Add Float to OSC Message", Keywords = "osc message"))` — Adds float value to end of OSCMessage
- L75 _public prototype_ `static UPARAM(DisplayName = "Message") FOSCMessage& AddInt32(UPARAM(ref) FOSCMessage& Message, int32` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Add Integer to OSC Message", Keywords = "osc message"))` — Adds Int32 value to end of OSCMessage
- L79 _public prototype_ `static UPARAM(DisplayName = "Message") FOSCMessage& AddInt64(UPARAM(ref) FOSCMessage& Message, int64` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Add Integer (64-bit) to OSC Message", Keywords = "osc message"))` — Adds Int64 value to end of OSCMessage
- L83 _public prototype_ `static UPARAM(DisplayName = "Message") FOSCMessage& AddAddress(UPARAM(ref) FOSCMessage& Message, const FOSCAddress&` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Add OSC Address (As String) to OSC Message", Keywords = "osc message"))` — Adds address (packed as string) value to end of OSCMessage
- L87 _public prototype_ `static UPARAM(DisplayName = "Message") FOSCMessage& AddString(UPARAM(ref) FOSCMessage& Message, UPARAM(ref) FString` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Add String to OSC Message", Keywords = "osc message"))` — Adds string value to end of OSCMessage
- L91 _public prototype_ `static UPARAM(DisplayName = "Message") FOSCMessage& AddBlob(UPARAM(ref) FOSCMessage& Message, const TArray<uint8>&` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Add Blob to OSC Message", Keywords = "osc message"))` — Adds blob value to end of OSCMessage
- L95 _public prototype_ `static UPARAM(DisplayName = "Message") FOSCMessage& AddBool(UPARAM(ref) FOSCMessage& Message, bool` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Add Bool to OSC Message", Keywords = "osc message"))` — Adds boolean value to end of OSCMessage
- L101 _public prototype_ `static UPARAM(DisplayName = "Succeeded") bool GetAddress(const FOSCMessage& Message, const int32 Index, FOSCAddress` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Address At Index", Keywords = "osc message"))` — Sets Value to address at provided Index in OSCMessage if in bounds and OSC type matches 'String' (Does NOT return address of message, rather string packed in message and casts to OSC address). Returns if string found at index and is valid OSC address path.
- L107 _public prototype_ `static void GetAllAddresses(const FOSCMessage& Message, TArray<FOSCAddress>& Values);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Addresses", Keywords = "osc message"))` — Returns all strings that are valid address paths in order received from OSCMessage (Does NOT include address of message, just strings packed in message that are valid paths).
- L113 _public prototype_ `static UPARAM(DisplayName = "Succeeded") bool GetFloat(const FOSCMessage& Message, const int32 Index, float` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Float At Index", Keywords = "osc message"))` — Set Value to float at provided Index in OSCMessage if in bounds and type matches
- L117 _public prototype_ `static void GetAllFloats(const FOSCMessage& Message, TArray<float>& Values);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Floats", Keywords = "osc message"))` — Returns all float values in order of received from OSCMessage
- L121 _public prototype_ `static UPARAM(DisplayName = "Succeeded") bool GetInt32(const FOSCMessage& Message, const int32 Index, int32` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Integer at Index", Keywords = "osc message"))` — Set Value to integer at provided Index in OSCMessage if in bounds and type matches
- L125 _public prototype_ `static void GetAllInt32s(const FOSCMessage& Message, TArray<int32>& Values);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Integers", Keywords = "osc message"))` — Returns all integer values in order of received from OSCMessage
- L129 _public prototype_ `static UPARAM(DisplayName = "Succeeded") bool GetInt64(const FOSCMessage& Message, const int32 Index, int64` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Integer (64-bit) at Index", Keywords = "osc message"))` — Set Value to Int64 at provided Index in OSCMessage if in bounds and type matches
- L133 _public prototype_ `static void GetAllInt64s(const FOSCMessage& Message, TArray<int64>& Values);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Integers (64-bit)", Keywords = "osc message"))` — Returns all Int64 values in order of received from OSCMessage
- L137 _public prototype_ `static UPARAM(DisplayName = "Succeeded") bool GetString(const FOSCMessage& Message, const int32 Index, FString` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message String at Index", Keywords = "osc message"))` — Set Value to string at provided Index in OSCMessage if in bounds and type matches
- L141 _public prototype_ `static void GetAllStrings(const FOSCMessage& Message, TArray<FString>& Values);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Strings", Keywords = "osc message"))` — Returns all string values in order of received from OSCMessage
- L145 _public prototype_ `static UPARAM(DisplayName = "Succeeded") bool GetBool(const FOSCMessage& Message, const int32 Index, bool` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Bool At Index", Keywords = "osc message"))` — Sets Value to boolean at provided Index from OSCMessage if in bounds and type matches
- L149 _public prototype_ `static void GetAllBools(const FOSCMessage& Message, TArray<bool>& Values);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Bools", Keywords = "osc message"))` — Returns all boolean values in order of received from OSCMessage
- L153 _public prototype_ `static UPARAM(DisplayName = "Succeeded") bool GetBlob(const FOSCMessage& Message, const int32 Index, TArray<uint8>` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Sets Value to blob at provided Index from OSCMessage if in bounds and type matches
- L157 _public prototype_ `static bool OSCAddressIsValidPath(const FOSCAddress& Address);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Is OSC Address Valid Path", Keywords = "valid osc address path address"))` — Returns whether OSC Address is valid path
- L161 _public prototype_ `static bool OSCAddressIsValidPattern(const FOSCAddress& Address);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Is OSC Address Valid Pattern", Keywords = "valid osc address pattern address"))` — Returns whether OSC Address is valid pattern to match against
- L165 _public prototype_ `static UPARAM(DisplayName = "Address") FOSCAddress ConvertStringToOSCAddress(const FString& S` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Converts string to OSC Address
- L171 _public prototype_ `static UPARAM(DisplayName = "Is Match") bool OSCAddressPathMatchesPattern(const FOSCAddress& Pattern, const FOSCAddress` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "OSC Address Path Matches Pattern", Keywords = "matches osc address path address"))` — Returns if address pattern matches the provided address path. If passed address is not a valid path, returns false.
- L177 _public prototype_ `static UPARAM(DisplayName = "Object") UObject* FindObjectAtOSCAddress(const FOSCAddress& Add` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Find Object at OSC Address", Keywords = "osc address path uobject"))` — Finds an object with the given OSC Address in path form, where containers correspond to path folders and the the address method to the object's name. Only supports parent objects.
- L183 _public prototype_ `static UPARAM(DisplayName = "Address") FOSCAddress OSCAddressFromObjectPath(UObject* O` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Convert Object Path to OSC Address", Keywords = "osc address path uobject"))` — Converts object path to OSC Address, converting folders to address containers and the object's name to the address method. Only supports parent objects (See UObjectBaseUtility::GetPathName and UObjectBaseUtility::GetFullName).
- L189 _public prototype_ `static UPARAM(DisplayName = "Address") FOSCAddress OSCAddressFromObjectPathString(const FString& Pat` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Convert Object Path (String) to OSC Address", Keywords = "osc address path uobject"))` — Converts object path string to OSC Address, converting folders to address containers and the object's name to the address method. Only supports parent objects (See UObjectBaseUtility::GetPathName and UObjectBaseUtility::GetFullName).
- L193 _public prototype_ `static UPARAM(DisplayName = "Path") FString ObjectPathFromOSCAddress(const FOSCAddress& Addre` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Convert OSC Address to Object Path", Keywords = "osc address path uobject"))` — Converts OSC Address to an object path.
- L197 _public prototype_ `static UPARAM(DisplayName = "Address") FOSCAddress& OSCAddressPushContainer(UPARAM(ref) FOSCAddress& Address, const FString& Cont` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Push Container to OSC Address", Keywords = "push osc address container"))` — Pushes container onto address' ordered array of containers
- L201 _public prototype_ `static UPARAM(DisplayName = "Address") FOSCAddress& OSCAddressPushContainers(UPARAM(ref) FOSCAddress& Address, const TArray<FString>& Conta` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Push Container Array to OSC Address", Keywords = "push osc address container"))` — Pushes container onto address' ordered array of containers
- L205 _public prototype_ `static UPARAM(DisplayName = "Container") FString OSCAddressPopContainer(UPARAM(ref) FOSCAddress&` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Pop Container from OSC Address", Keywords = "pop osc address container"))` — Pops container from ordered array of containers. If no containers, returns empty string
- L209 _public prototype_ `static UPARAM(DisplayName = "Containers") TArray<FString> OSCAddressPopContainers(UPARAM(ref) FOSCAddress& Address, int32 NumCo` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Pop Containers from OSC Address", Keywords = "pop osc address container"))` — Pops container from ordered array of containers. If NumContainers is greater than or equal to the number of containers in address, returns all containers.
- L213 _public prototype_ `static UPARAM(DisplayName = "Address") FOSCAddress& OSCAddressRemoveContainers(UPARAM(ref) FOSCAddress& Address, int32 Index, int32` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Remove Containers from OSC Address", Keywords = "remove osc address container"))` — Remove containers from ordered array of containers at index up to count of containers.
- L217 _public prototype_ `static UPARAM(DisplayName = "Address") FOSCAddress GetOSCMessageAddress(const FOSCMessage& Me` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Address", Keywords = "osc address"))` — Returns copy of message's OSC Address
- L221 _public prototype_ `static UPARAM(DisplayName = "Message") FOSCMessage& SetOSCMessageAddress(UPARAM(ref) FOSCMessage& Message, const FOSCAddress& Ad` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Sets the OSC Address of the provided message
- L225 _public prototype_ `static UPARAM(DisplayName = "Container") FString GetOSCAddressContainer(const FOSCAddress& Address, const int3` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Address Container At Index", Keywords = "osc address container path"))` — Returns the OSC Address container at the provided 'Index.' Returns empty string if index is out-of-bounds.
- L229 _public prototype_ `static UPARAM(DisplayName = "Containers") TArray<FString> GetOSCAddressContainers(const FOSCAddress&` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Address Containers", Keywords = "osc address container path"))` — Builds referenced array of address of containers in order
- L233 _public prototype_ `static UPARAM(DisplayName = "Path") FString GetOSCAddressContainerPath(const FOSCAddress& Addre` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Returns full path of OSC address in the form '/Container1/Container2/Method'
- L237 _public prototype_ `static UPARAM(DisplayName = "Full Path") FString GetOSCAddressFullPath(const FOSCAddress&` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Convert OSC Address To String"))` — Returns full path of OSC address in the form '/Container1/Container2'
- L241 _public prototype_ `static UPARAM(DisplayName = "Method") FString GetOSCAddressMethod(const FOSCAddress& Add` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Address Method"))` — Returns method name of OSC Address provided
- L245 _public prototype_ `static UPARAM(DisplayName = "Address") FOSCAddress& ClearOSCAddressContainers(UPARAM(ref) FOSCAddress& Ad` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Clear OSC Address Containers", Keywords = "osc address clear"))` — Clears containers of OSC Address provided
- L249 _public prototype_ `static UPARAM(DisplayName = "Address") FOSCAddress& SetOSCAddressMethod(UPARAM(ref) FOSCAddress& Address, const FString& M` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Set OSC Address Method", Keywords = "osc method"))` — Sets the method name of the OSC Address provided

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace OSC` (scope `UE`)
- L20 _prototype_ `int32 GetDefaultClientPort();` (scope `UE::OSC`)
- L21 _prototype_ `int32 GetDefaultServerPort();` (scope `UE::OSC`)

### `Plugins/Runtime/OSC/Source/OSC/Public/OSCMessage.h` (Public)


#### struct `FOSCMessage`  
`struct FOSCMessage`  
_L16-47_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public prototype_ `FOSCMessage();`
- L21 _public prototype_ `FOSCMessage(FOSCAddress Address, TArray<UE::OSC::FOSCData> Args);`
- L22 _public prototype_ `FOSCMessage(const TSharedRef<UE::OSC::IPacket>& InPacket);`
- L25 _public prototype_ `FOSCMessage(const TSharedPtr<UE::OSC::IPacket>& InPacket);` — `UE_DEPRECATED(5.5, "Use shared ref ctor instead")`
- L27 _public prototype_ `~FOSCMessage() = default;`
- L30 _public prototype_ `const TArray<UE::OSC::FOSCData>& GetArgumentsChecked() const;` — Returns arguments, asserting if the message's packet is unset.
- L33 _public prototype_ `void SetPacket(TSharedPtr<UE::OSC::IPacket>& InPacket);` — `UE_DEPRECATED(5.5, "Use shared ref setter instead")`
- L35 _public prototype_ `void SetPacket(TSharedRef<UE::OSC::IPacket>& InPacket);`
- L38 _public prototype_ `const TSharedPtr<UE::OSC::IPacket>& GetPacket() const;` — `UE_DEPRECATED(5.5, "Use shared ref getter instead")`
- L40 _public prototype_ `const TSharedRef<UE::OSC::IPacket>& GetPacketRef() const;`
- L42 _public prototype_ `bool SetAddress(const FOSCAddress& InAddress);`
- L43 _public prototype_ `const FOSCAddress& GetAddress() const;`
- L46 _private member_ `TSharedRef<UE::OSC::IPacket> Packet;`

### `Plugins/Runtime/OSC/Source/OSC/Public/OSCPacket.h` (Public)


#### class `UE::OSC::IPacket`  
`class IPacket : public TSharedFromThis<IPacket>`  
_L16-52_
- inherits: `TSharedFromThis<IPacket>`
- L19 _public prototype_ `IPacket() = default;`
- L20 _public prototype_ `virtual ~IPacket() = default;`
- L23 _public prototype_ `virtual void WriteData(FStream& OutStream) = 0;` — Write packet data into stream
- L26 _public prototype_ `virtual void ReadData(FStream& OutStream) = 0;` — Read packet data from stream
- L29 _public prototype_ `virtual bool IsMessage() = 0;` — Returns true if packet is message
- L32 _public prototype_ `virtual bool IsBundle() = 0;` — Returns true if packet is bundle
- L35 _public function_ `virtual const FString& GetIPAddress() const` — `UE_DEPRECATED(5.5, "Packet port can now be accessed via GetIPEndpoint() call.")`
- L43 _public function_ `virtual uint16 GetPort() const` — `UE_DEPRECATED(5.5, "Packet address can now be accessed via GetIPEndpoint() call.")`
- L48 _public prototype_ `virtual const FIPv4Endpoint& GetIPEndpoint() const = 0;`
- L51 _public prototype_ `static TSharedPtr<IPacket> CreatePacket(const uint8* InPacketType, const FIPv4Endpoint& InEndpoint);` — Create an OSC packet according to the input data.

#### class `IOSCPacket`  
`class IOSCPacket : public UE::OSC::IPacket`  
_L56-63_
- inherits: `UE::OSC::IPacket`
- desc: Exists for back compat.  To be deprecated
- L60 _public prototype_ `IOSCPacket() = default;` — `UE_DEPRECATED(5.5, "Use UE::OSC::IPacket instead")`
- L62 _public prototype_ `virtual ~IOSCPacket() = default;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace OSC` (scope `UE`)

### `Plugins/Runtime/OSC/Source/OSC/Public/OSCServer.h` (Public)


#### class `UE::OSC::IServerProxy`  
`class IServerProxy`  
_L46-130_
- desc: Interface for internal networking implementation.  See UOSCServer for details
- L49 _public typedef_ `using FOnDispatchPacket = TUniqueFunction<void(TSharedRef<UE::OSC::IPacket>)>;`
- L52 _public prototype_ `static TSharedPtr<IServerProxy> Create();` — Creates a new server proxy that can be used by any system where the provided dispatch callback is called on a worker thread.
- L54 _public function_ `virtual ~IServerProxy()`
- L57 _public prototype_ `virtual bool CanProcessPacket(TSharedRef<UE::OSC::IPacket> Packet) const = 0;` — Returns whether or not packet can be processed, i.e. is valid and allowlisted.
- L60 _public prototype_ `virtual FString GetDescription() const = 0;` — Returns debug description of server proxy
- L63 _public function_ `virtual FString GetIpAddress() const` — `UE_DEPRECATED(5.5, "Use GetIPEndpoint instead")`
- L65 _public prototype_ `virtual const FIPv4Endpoint& GetIPEndpoint() const = 0;`
- L68 _public function_ `virtual int32 GetPort() const` — `UE_DEPRECATED(5.5, "Use GetIPEndpoint instead")`
- L71 _public prototype_ `virtual bool GetMulticastLoopback() const = 0;` — Returns whether or not loopback is enabled
- L74 _public prototype_ `virtual bool IsActive() const = 0;` — Returns whether or not the server is currently active (listening)
- L77 _public prototype_ `virtual void Listen(const FString& ServerName) = 0;` — Starts the server, causing it to actively listen and dispatch OSC messages
- L80 _public prototype_ `virtual bool SetAddress(const FString& InReceiveIPAddress, int32 InPort);` — `UE_DEPRECATED(5.5, "Use SetIPEndpoint instead")`
- L84 _public prototype_ `virtual bool SetIPEndpoint(const FIPv4Endpoint& InEndpoint) = 0;` — Sets the current server's endpoint.  Ignores request and returns false if server is currently active.
- L88 _public prototype_ `virtual bool SetMulticastLoopback(bool bInMulticastLoopback) = 0;` — Sets whether or not loopback is enabled.  Returns false and request is ignored if server is currently active.
- L92 _public function_ `virtual void SetOnDispatchPacket(TSharedPtr<FOnDispatchPacket> OnDispatch)` — Sets dispatch function to be called when OSC packet is received (thread safe and can be mutated while server is running)
- L96 _public function_ `virtual void SetTickableInEditor(bool bInTickInEditor)` — `UE_DEPRECATED(5.5, "ServerProxies are no longer independently ticked objects only and can now be accessed by threads other than the GameThread via the 'SetOnDispatchPacket' setter.")`
- L100 _public prototype_ `virtual void Stop() = 0;` — Stops the server
- L103 _public function_ `virtual void AddClientToAllowList(const FString& InIPAddress)` — `UE_DEPRECATED(5.5, "AllowList is now managed as IPv4Endpoints. Use API that works with endpoint struct directly")`
- L106 _public function_ `virtual void RemoveClientFromAllowList(const FString& IPAddress)` — `UE_DEPRECATED(5.5, "AllowList is now managed as IPv4Endpoints. Use API that works with endpoint struct directly")`
- L109 _public function_ `virtual void ClearClientAllowList()` — `UE_DEPRECATED(5.5, "AllowList is now managed as IPv4Endpoints. Use API that works with endpoint struct directly")`
- L112 _public function_ `virtual TSet<FString> GetClientAllowList() const` — `UE_DEPRECATED(5.5, "AllowList is now managed as IPv4Endpoints. Use API that works with endpoint struct directly")`
- L115 _public prototype_ `virtual void AddClientEndpointToAllowList(const FIPv4Endpoint& InIPv4Endpoint) = 0;` — Adds the given endpoint to the client allow list
- L118 _public prototype_ `virtual void RemoveClientEndpointFromAllowList(const FIPv4Endpoint& InIPv4Endpoint) = 0;` — Removes the given endpoint from the client allow list
- L121 _public prototype_ `virtual void ClearClientEndpointAllowList() = 0;` — Empties the given address to the client allow list
- L124 _public prototype_ `virtual const TSet<FIPv4Endpoint>& GetClientEndpointAllowList() const = 0;` — Returns Client Address allow list if it is enabled, else returns nullptr
- L129 _public prototype_ `virtual void SetFilterClientsByAllowList(bool bEnabled) = 0;` — Sets whether or not allow list is active.  If disabled, entries are not cleared however GetClientAddressAllowList will no longer return a valid reference to the given set of allow list members.

#### class `IOSCServerProxy`  
`class IOSCServerProxy : public UE::OSC::IServerProxy`  
_L135-142_
- inherits: `UE::OSC::IServerProxy`
- desc: For backward compat.  To be deprecated
- L139 _public prototype_ `IOSCServerProxy() = default;` — `UE_DEPRECATED(5.5, "Use UE::OSC::IServerProxy instead")`
- L141 _public prototype_ `virtual ~IOSCServerProxy() = default;`

#### class `UOSCServer`  
`class UOSCServer : public UObject`  
_L146-282_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L153 _public prototype_ `bool GetMulticastLoopback() const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Gets whether or not to loopback if ReceiveIPAddress provided is multicast.
- L157 _public prototype_ `bool IsActive() const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Returns whether server is actively listening to incoming messages.
- L161 _public prototype_ `void Listen();` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Sets the IP address and port to listen for OSC data.
- L165 _public prototype_ `bool SetAddress(const FString& ReceiveIPAddress, int32 Port);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Set the address and port of server. Fails if server is currently active.
- L169 _public prototype_ `void SetMulticastLoopback(bool bMulticastLoopback);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Set whether or not to loopback if ReceiveIPAddress provided is multicast.
- L173 _public prototype_ `void Stop();` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Stop and tidy up network socket.
- L177 _public member_ `FOSCReceivedMessageEvent OnOscMessageReceived;` — `UPROPERTY(BlueprintAssignable, Category = "Audio|OSC")` — Event that gets called when an OSC message is received.
- L180 _public member_ `FOSCReceivedMessageNativeEvent OnOscMessageReceivedNative;` — Native event that gets called when an OSC message is received.
- L184 _public member_ `FOSCReceivedBundleEvent OnOscBundleReceived;` — `UPROPERTY(BlueprintAssignable, Category = "Audio|OSC")` — Event that gets called when an OSC bundle is received.
- L187 _public member_ `FOSCReceivedBundleNativeEvent OnOscBundleReceivedNative;` — Native event that gets called when an OSC bundle is received.
- L193 _public prototype_ `void SetAllowlistClientsEnabled(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — When set to true, server will only process received messages from allowlisted clients.
- L197 _public prototype_ `void AddAllowlistedClient(const FString& IPAddress, int32 IPPort = 0);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Adds client to allowlist of clients to listen for.
- L201 _public prototype_ `void RemoveAllowlistedClient(const FString& IPAddress, int32 IPPort = 0);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Removes allowlisted client to listen for.
- L205 _public prototype_ `void ClearAllowlistedClients();` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Clears client allowlist to listen for.
- L209 _public prototype_ `FString GetIpAddress(bool bIncludePort) const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Returns the IP for the server if connected as a string.
- L213 _public prototype_ `int32 GetPort() const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Returns the port for the server if connected.
- L217 _public prototype_ `TSet<FString> GetAllowlistedClients(bool bIncludePort = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Returns set of allowlisted endpoint clients as strings with (optional) port included.
- L221 _public prototype_ `void BindEventToOnOSCAddressPatternMatchesPath(const FOSCAddress& OSCAddressPattern, const FOSCDispatchMessageEventBP& Event);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Adds event to dispatch when OSCAddressPattern is matched.
- L225 _public prototype_ `void UnbindEventFromOnOSCAddressPatternMatchesPath(const FOSCAddress& OSCAddressPattern, const FOSCDispatchMessageEventBP& Event);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Unbinds specific event from OSCAddress pattern.
- L229 _public prototype_ `void UnbindAllEventsFromOnOSCAddressPatternMatchesPath(const FOSCAddress& OSCAddressPattern);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Removes OSCAddressPattern from sending dispatch events.
- L233 _public prototype_ `void UnbindAllEventsFromOnOSCAddressPatternMatching();` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Removes all events from OSCAddressPatterns to dispatch.
- L237 _public prototype_ `TArray<FOSCAddress> GetBoundOSCAddressPatterns() const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC")` — Returns set of OSCAddressPatterns currently listening for matches to dispatch.
- L244 _public prototype_ `void SetTickInEditor(bool bInTickInEditor);` — `UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (Deprecated = "5.5", DeprecationMessage = "Servers are now implemented as dispatchers, which are pumped on an async task upon calling 'Listen' at a provided rate (i.e. no longer 'ticked' on the game thread). See 'SetUpdateRate'"))` — Set whether server instance can be ticked in-editor (editor only and available to blueprint for use in editor utility scripts/script actions).
- L248 _public prototype_ `void ClearPackets();` — `UE_DEPRECATED(5.5, "Clearing packets directly is not thread-safe and no longer supported.")`
- L251 _public function_ `void EnqueuePacket(TSharedPtr<UE::OSC::IPacket> InPacket)` — `UE_DEPRECATED(5.5, "Enqueuing packets is now handled privately")`
- L254 _public function_ `void PumpPacketQueue(const TSet<uint32>* InAllowlistedClients)` — `UE_DEPRECATED(5.5, "Pumping packets is now handled privately")`
- L257 _protected prototype_ `virtual void BeginDestroy() override;`
- L258 _protected prototype_ `virtual void PostInitProperties() override;`
- L261 _private prototype_ `void ClearPacketsInternal();`
- L263 _private typedef_ `using FPacketQueue = TSpscQueue<TSharedPtr<UE::OSC::IPacket>>;`
- L264 _private prototype_ `void PumpPacketQueue();`
- L267 _private prototype_ `void BroadcastBundle(const FOSCBundle& InBundle);` — Broadcasts provided bundle received to be dispatched on the GameThread
- L270 _private prototype_ `void BroadcastMessage(const FOSCMessage& InMessage);` — Broadcasts provided message received to be dispatched on the GameThread
- L273 _private member_ `TSharedPtr<UE::OSC::IServerProxy> ServerProxy;` — Pointer to internal implementation of server proxy
- L276 _private member_ `TSharedPtr<FPacketQueue> OSCPackets;` — Queue stores incoming OSC packet requests to process on the game thread.
- L279 _private member_ `TMap<FOSCAddress, FOSCDispatchMessageEvent> AddressPatterns;` — Address pattern hash to check against when dispatching incoming messages
- L281 _private member_ `FTSTicker::FDelegateHandle TickHandle;`

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOSCReceivedMessageEvent, const FOSCMessage&, Message, const FString&, IPAddress, int32, Port);` — Delegates
- L30 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOSCReceivedMessageEvent, const FOSCMessage&, Message, const FString&, IPAddress, int32, Port);` — Delegates
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOSCReceivedMessageNativeEvent, const FOSCMessage&, const FString& , uint16 );`
- L31 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOSCReceivedMessageNativeEvent, const FOSCMessage&, const FString& , uint16 );`
- L32 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOSCDispatchMessageEvent, const FOSCAddress&, AddressPattern, const FOSCMessage&, Message, const FString&, IPAddress, int32, Port);`
- L32 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOSCDispatchMessageEvent, const FOSCAddress&, AddressPattern, const FOSCMessage&, Message, const FString&, IPAddress, int32, Port);`
- L33 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOSCReceivedBundleEvent, const FOSCBundle&, Bundle, const FString&, IPAddress, int32, Port);`
- L33 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOSCReceivedBundleEvent, const FOSCBundle&, Bundle, const FString&, IPAddress, int32, Port);`
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOSCReceivedBundleNativeEvent, const FOSCBundle&, const FString& , uint16 );`
- L34 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOSCReceivedBundleNativeEvent, const FOSCBundle&, const FString& , uint16 );`
- L35 _delegate_ `DECLARE_DYNAMIC_DELEGATE_FourParams(FOSCDispatchMessageEventBP, const FOSCAddress&, AddressPattern, const FOSCMessage&, Message, const FString&, IPAddress, int32, Port);`
- L35 _prototype_ `DECLARE_DYNAMIC_DELEGATE_FourParams(FOSCDispatchMessageEventBP, const FOSCAddress&, AddressPattern, const FOSCMessage&, Message, const FString&, IPAddress, int32, Port);`
- L37 _delegate_ `DECLARE_STATS_GROUP(TEXT("OSC Commands"), STATGROUP_OSCNetworkCommands, STATCA`
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace OSC` (scope `UE`)

### `Plugins/Runtime/OSC/Source/OSC/Public/OSCStream.h` (Public)


#### class `UE::OSC::FStream`  
`class FStream`  
_L10-154_
- L13 _public prototype_ `FStream();`
- L14 _public prototype_ `FStream(const uint8* InData, int32 InSize);`
- L17 _public prototype_ `const uint8* GetData() const;` — Returns the stream buffer data
- L20 _public prototype_ `int32 GetLength() const;` — Returns the stream's length
- L23 _public prototype_ `bool HasReachedEnd() const;` — Returns true if stream has reached the end, false if not
- L26 _public prototype_ `int32 GetPosition() const;` — Get current stream position.
- L29 _public prototype_ `void SetPosition(int32 InPosition);` — Set stream position.
- L32 _public prototype_ `TCHAR ReadChar();` — Read Char from the stream
- L35 _public prototype_ `void WriteChar(TCHAR Char);` — Write an ansi char into the stream
- L38 _public prototype_ `void WriteColor(FColor Color);` — Write Color into the stream
- L41 _public prototype_ `FColor ReadColor();` — Read Color from the stream
- L44 _public prototype_ `int32 ReadInt32();` — Read Int32 from the stream
- L47 _public prototype_ `void WriteInt32(int32 Value);` — Write Int32 into the stream
- L50 _public prototype_ `double ReadDouble();` — Read Double from the stream
- L53 _public prototype_ `void WriteDouble(uint64 Value);` — Write Double into the stream
- L56 _public prototype_ `int64 ReadInt64();` — Read Int64 from the stream
- L59 _public prototype_ `void WriteInt64(int64 Value);` — Write Int64 into the stream
- L62 _public prototype_ `uint64 ReadUInt64();` — Read UInt64 from the stream
- L65 _public prototype_ `void WriteUInt64(uint64 Value);` — Write UInt64 into the stream
- L68 _public prototype_ `float ReadFloat();` — Read Float from the stream
- L71 _public prototype_ `void WriteFloat(float Value);` — Write Int64 into the stream
- L74 _public prototype_ `FString ReadString();` — Read String from the stream
- L77 _public prototype_ `void WriteString(const FString& String);` — Write String into the stream
- L80 _public prototype_ `TArray<uint8> ReadBlob();` — Read blob from the stream
- L83 _public prototype_ `void WriteBlob(TArray<uint8>& Blob);` — Write blob into the stream
- L87 _private function_ `template <typename TNumericType> TNumericType ReadNumeric()`
- L115 _private function_ `template <typename TNumericType> void WriteNumeric(TNumericType InValue)`
- L141 _private prototype_ `int32 Read(uint8* OutBuffer, int32 InSize);` — Read data from stream into a provided buffer.
- L144 _private prototype_ `int32 Write(const uint8* InBuffer, int32 InSize);` — Write data into stream from provided buffer.
- L147 _private member_ `TArray<uint8> Data;` — Stream data.
- L150 _private member_ `int32 Position = 0;` — Current buffer position.
- L153 _private member_ `bool bIsReadStream = false;` — Whether stream is used to read (true) or write (false)

#### union `UE::OSC::FStream::ReadNumeric::(anonymous)`  
``  
_L95-98_

#### union `UE::OSC::FStream::WriteNumeric::(anonymous)`  
``  
_L122-125_

#### class `FOSCStream`  
`class FOSCStream : public UE::OSC::FStream`  
_L157-165_
- inherits: `UE::OSC::FStream`
- L161 _public prototype_ `FOSCStream() = default;` — `UE_DEPRECATED(5.5, "Use UE::OSC::FStream instead")`
- L164 _public function_ `FOSCStream(const uint8* InData, int32 InSize) : UE::OSC::FStream(InData, InSize)` — `UE_DEPRECATED(5.5, "Use UE::OSC::FStream instead")`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace OSC` (scope `UE`)
- L96 _member_ `TNumericType Number;` (scope `UE::OSC::FStream::ReadNumeric::__anonf4978357010a`)
- L97 _member_ `uint8 Data[sizeof(TNumericType)];` (scope `UE::OSC::FStream::ReadNumeric::__anonf4978357010a`)
- L123 _member_ `TNumericType Number;` (scope `UE::OSC::FStream::WriteNumeric::__anonf4978357020a`)
- L124 _member_ `uint8 Data[sizeof(TNumericType)];` (scope `UE::OSC::FStream::WriteNumeric::__anonf4978357020a`)

### `Plugins/Runtime/OSC/Source/OSC/Public/OSCTypes.h` (Public)


#### enum `UE::OSC::EDataType`  
`enum class EDataType : uint8`  
_L13-29_
- L15 _public enumerator_ `Blob = 'b'`
- L16 _public enumerator_ `Char = 'c'`
- L17 _public enumerator_ `Color = 'r'`
- L18 _public enumerator_ `Double = 'd'`
- L19 _public enumerator_ `False = 'F'`
- L20 _public enumerator_ `Float = 'f'`
- L21 _public enumerator_ `Infinitum = 'I'`
- L22 _public enumerator_ `Int32 = 'i'`
- L23 _public enumerator_ `Int64 = 'h'`
- L24 _public enumerator_ `NilValue = 'N'`
- L25 _public enumerator_ `String = 's'`
- L26 _public enumerator_ `Terminate = '\0'`
- L27 _public enumerator_ `Time = 't'`
- L28 _public enumerator_ `True = 'T'`

#### class `UE::OSC::FOSCData`  
`class FOSCData`  
_L33-105_
- L36 _public prototype_ `FOSCData() = default;`
- L38 _public prototype_ `explicit FOSCData(const TArray<uint8>& Value);`
- L39 _public prototype_ `explicit FOSCData(TArray<uint8>&& Value);`
- L40 _public prototype_ `explicit FOSCData(bool Value);`
- L41 _public prototype_ `explicit FOSCData(ANSICHAR Value);`
- L42 _public prototype_ `explicit FOSCData(FColor Value);`
- L43 _public prototype_ `explicit FOSCData(double Value);`
- L44 _public prototype_ `explicit FOSCData(float Value);`
- L45 _public prototype_ `explicit FOSCData(int32 Value);`
- L46 _public prototype_ `explicit FOSCData(int64 Value);`
- L47 _public prototype_ `explicit FOSCData(FString Value);`
- L48 _public prototype_ `explicit FOSCData(uint64 Value);`
- L51 _public prototype_ `explicit FOSCData(EDataType DataType);` — `UE_DEPRECATED(5.5, "Use applicable explicitly typed constructor or static construction function")`
- L53 _public prototype_ `static const FOSCData& NilData();`
- L54 _public prototype_ `static const FOSCData& Infinitum();`
- L55 _public prototype_ `static const FOSCData& Terminate();`
- L56 _public prototype_ `static bool IsNil(const FOSCData& InType);`
- L58 _public prototype_ `EDataType GetDataType() const;`
- L60 _public function_ `inline bool IsBlob() const`
- L61 _public function_ `inline bool IsBool() const`
- L62 _public function_ `inline bool IsChar() const`
- L63 _public function_ `inline bool IsColor() const`
- L64 _public function_ `inline bool IsDouble() const`
- L65 _public function_ `inline bool IsFloat() const`
- L66 _public function_ `inline bool IsInfinitum() const`
- L67 _public function_ `inline bool IsInt32() const`
- L68 _public function_ `inline bool IsInt64() const`
- L69 _public function_ `inline bool IsNil() const`
- L70 _public function_ `inline bool IsString() const`
- L71 _public function_ `inline bool IsTimeTag() const`
- L72 _public function_ `inline bool IsTerminate() const`
- L74 _public prototype_ `TArray<uint8> GetBlob() const;`
- L75 _public prototype_ `bool GetBool() const;`
- L76 _public prototype_ `ANSICHAR GetChar() const;`
- L77 _public prototype_ `FColor GetColor() const;`
- L78 _public prototype_ `double GetDouble() const;`
- L79 _public prototype_ `float GetFloat() const;`
- L80 _public prototype_ `int32 GetInt32() const;`
- L81 _public prototype_ `int64 GetInt64() const;`
- L82 _public prototype_ `FString GetString() const;`
- L83 _public prototype_ `uint64 GetTimeTag() const;`
- L85 _public prototype_ `TArrayView<const uint8> GetBlobArrayView() const;`
- L86 _public prototype_ `FStringView GetStringView() const;`
- L88 _public typedef_ `using FVariant = TVariant < TArray<uint8>,`
- L103 _protected member_ `EDataType DataType = EDataType::NilValue;`
- L104 _protected member_ `FVariant Data;`

#### enum `EOSCTypeTag`  
`enum EOSCTypeTag`  
_L110-126_
- desc: Exists for back compat.  To be deprecated
- L112 _public enumerator_ `OSC_BLOB = 'b'`
- L113 _public enumerator_ `OSC_CHAR = 'c'`
- L114 _public enumerator_ `OSC_COLOR = 'r'`
- L115 _public enumerator_ `OSC_DOUBLE = 'd'`
- L116 _public enumerator_ `OSC_FALSE = 'F'`
- L117 _public enumerator_ `OSC_FLOAT = 'f'`
- L118 _public enumerator_ `OSC_INFINITUM = 'I'`
- L119 _public enumerator_ `OSC_INT32 = 'i'`
- L120 _public enumerator_ `OSC_INT64 = 'h'`
- L121 _public enumerator_ `OSC_NIL = 'N'`
- L122 _public enumerator_ `OSC_STRING = 's'`
- L123 _public enumerator_ `OSC_TERMINATE = '\0'`
- L124 _public enumerator_ `OSC_TIME = 't'`
- L125 _public enumerator_ `OSC_TRUE = 'T'`

#### class `FOSCType`  
`class FOSCType : public UE::OSC::FOSCData`  
_L128-205_
- inherits: `UE::OSC::FOSCData`
- L132 _public function_ `explicit FOSCType(const TArray<uint8>& Value) : UE::OSC::FOSCData(Value)` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L138 _public function_ `explicit FOSCType(TArray<uint8>&& Value) : UE::OSC::FOSCData(MoveTemp(Value))` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L144 _public function_ `explicit FOSCType(bool Value) : UE::OSC::FOSCData(Value)` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L150 _public function_ `explicit FOSCType(ANSICHAR Value) : UE::OSC::FOSCData(Value)` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L156 _public function_ `explicit FOSCType(FColor Value) : UE::OSC::FOSCData(Value)` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L162 _public function_ `explicit FOSCType(double Value) : UE::OSC::FOSCData(Value)` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L168 _public function_ `explicit FOSCType(float Value) : UE::OSC::FOSCData(Value)` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L174 _public function_ `explicit FOSCType(int32 Value) : UE::OSC::FOSCData(Value)` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L180 _public function_ `explicit FOSCType(int64 Value) : UE::OSC::FOSCData(Value)` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L186 _public function_ `explicit FOSCType(const FString& Value) : UE::OSC::FOSCData(Value)` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L192 _public function_ `explicit FOSCType(FString&& Value) : UE::OSC::FOSCData(MoveTemp(Value))` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L198 _public function_ `explicit FOSCType(uint64 Value) : UE::OSC::FOSCData(Value)` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData instead")`
- L204 _public function_ `int32 GetTypeTag() const` — `UE_DEPRECATED(5.5, "Use UE::OSC::FOSCData::GetDataType() instead")`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace OSC` (scope `UE`)
- L31 _prototype_ `const TCHAR* LexToString(EDataType DataType);` (scope `UE::OSC`)
