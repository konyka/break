# Plugins / DMXProtocolsACN

- module root: `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolSACN`
- headers: 8; symbols: 180
- symbol kinds: class=6, enum=7, enumerator=34, function=9, macro=1, member=55, prototype=64, struct=4
- PrivateDependencyModuleNames: CoreUObject, Engine, Json, Networking, Sockets
- PublicDependencyModuleNames: Core, DMXProtocol

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolSACN/Private/DMXProtocolSACN.h` (Private)


#### class `FDMXProtocolSACN`  
`class FDMXProtocolSACN : public IDMXProtocol`  
_L15-76_
- inherits: `IDMXProtocol`
- L19 _public prototype_ `explicit FDMXProtocolSACN(const FName& InProtocolName);`
- L23 _public prototype_ `virtual bool Init() override;`
- L24 _public prototype_ `virtual bool Shutdown() override;`
- L25 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L30 _public prototype_ `virtual bool IsEnabled() const override;`
- L31 _public prototype_ `virtual const FName& GetProtocolName() const override;`
- L32 _public prototype_ `virtual const TArray<EDMXCommunicationType> GetInputPortCommunicationTypes() const override;`
- L33 _public prototype_ `virtual const TArray<EDMXCommunicationType> GetOutputPortCommunicationTypes() const override;`
- L34 _public prototype_ `virtual int32 GetMinUniverseID() const override;`
- L35 _public prototype_ `virtual int32 GetMaxUniverseID() const override;`
- L36 _public prototype_ `virtual bool IsValidUniverseID(int32 UniverseID) const override;`
- L37 _public prototype_ `virtual int32 MakeValidUniverseID(int32 DesiredUniverseID) const override;`
- L38 _public prototype_ `virtual bool SupportsPrioritySettings() const override;`
- L39 _public prototype_ `virtual bool RegisterInputPort(const TSharedRef<FDMXInputPort, ESPMode::ThreadSafe>& InputPort) override;`
- L40 _public prototype_ `virtual void UnregisterInputPort(const TSharedRef<FDMXInputPort, ESPMode::ThreadSafe>& InputPort) override;`
- L41 _public prototype_ `virtual TArray<TSharedPtr<IDMXSender>> RegisterOutputPort(const TSharedRef<FDMXOutputPort, ESPMode::ThreadSafe>& OutputPort) override;`
- L42 _public prototype_ `virtual bool IsCausingLoopback(EDMXCommunicationType InCommunicationType) override;`
- L43 _public prototype_ `virtual void UnregisterOutputPort(const TSharedRef<FDMXOutputPort, ESPMode::ThreadSafe>& OutputPort) override;`
- L47 _public member_ `static const TArray<EDMXCommunicationType> InputPortCommunicationTypes;` — The supported input port communication types
- L50 _public member_ `static const TArray<EDMXCommunicationType> OutputPortCommunicationTypes;` — The supported output port communication types
- L54 _private prototype_ `TSharedPtr<FDMXProtocolSACNSender> FindExistingMulticastSender(const FString& NetworkInterfaceAddress) const;` — Returns the sender for specified endpoint or nullptr if none exists
- L57 _private prototype_ `TSharedPtr<FDMXProtocolSACNSender> FindExistingUnicastSender(const FString& NetworkInterfaceAddress, const FString& DestinationAddress) const;` — Returns the sender for specified endpoint or nullptr if none exists
- L60 _private prototype_ `TSharedPtr<FDMXProtocolSACNReceiver> FindExistingReceiver(const FString& IPAddress, EDMXCommunicationType CommunicationType) const;` — Returns the receiver for specified endpoint or nullptr if none exists
- L63 _private member_ `TSet<FDMXInputPortSharedRef> CachedInputPorts;` — Set of all DMX input ports currently in use
- L66 _private member_ `TSet<FDMXOutputPortSharedRef> CachedOutputPorts;` — Set of all DMX input ports currently in use
- L69 _private member_ `TSet<TSharedPtr<FDMXProtocolSACNReceiver>> Receivers;` — Set of receivers currently in use
- L72 _private member_ `TSet<TSharedPtr<FDMXProtocolSACNSender>> Senders;` — Set of receivers currently in use
- L75 _private member_ `FName ProtocolName;`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolSACN/Private/DMXProtocolSACNConstants.h` (Private)


#### enum `(anonymous)`  
``  
_L11-18_

#### enum `(anonymous)`  
``  
_L21-25_

#### enum `(anonymous)`  
``  
_L28-31_

#### enum `(anonymous)`  
``  
_L34-43_

#### enum `(anonymous)`  
``  
_L46-57_

#### enum `(anonymous)`  
``  
_L60-65_

#### enum `(anonymous)`  
``  
_L68-70_

#### Free symbols / members of external scopes

- L8 _macro_ `#define DMX_PROTOCOLNAME_SACN "sACN"`
- L12 _enumerator_ `VECTOR_ROOT_E131_DATA = 0x00000004` (scope `__anon523a81120103`)
- L13 _enumerator_ `VECTOR_ROOT_E131_EXTENDED = 0x00000008` (scope `__anon523a81120103`)
- L14 _enumerator_ `VECTOR_E131_EXTENDED_SYNCHRONIZATION = 0x00000001` (scope `__anon523a81120103`)
- L15 _enumerator_ `VECTOR_E131_EXTENDED_DISCOVERY = 0x00000002` (scope `__anon523a81120103`)
- L16 _enumerator_ `VECTOR_E131_DATA_PACKET = 0x00000002` (scope `__anon523a81120103`)
- L17 _enumerator_ `VECTOR_DMP_SET_PROPERTY = 0x02` (scope `__anon523a81120103`)
- L22 _enumerator_ `ACN_PORT = 5568` (scope `__anon523a81120203`)
- L23 _enumerator_ `ACN_UNIVERSE_IP_0 = 239` (scope `__anon523a81120203`)
- L24 _enumerator_ `ACN_UNIVERSE_IP_1 = 255` (scope `__anon523a81120203`)
- L29 _enumerator_ `ACN_MIN_UNIVERSE = 1` (scope `__anon523a81120303`)
- L30 _enumerator_ `ACN_MAX_UNIVERSE = 63999` (scope `__anon523a81120303`)
- L35 _enumerator_ `ACN_HEADER_SIZE = 126` (scope `__anon523a81120403`)
- L36 _enumerator_ `ACN_DMX_SIZE = 512` (scope `__anon523a81120403`)
- L37 _enumerator_ `ACN_IDENTIFIER_SIZE = 12` (scope `__anon523a81120403`)
- L38 _enumerator_ `ACN_RLP_PREAMBLE_SIZE = 16` (scope `__anon523a81120403`)
- L39 _enumerator_ `ACN_CIDBYTES = 16` (scope `__anon523a81120403`)
- L40 _enumerator_ `ACN_SOURCE_NAME_SIZE = 64` (scope `__anon523a81120403`)
- L41 _enumerator_ `ACN_ADDRESS_INC = 1` (scope `__anon523a81120403`)
- L42 _enumerator_ `ACN_ADDRESS_ROOT_VECTOR = 18` (scope `__anon523a81120403`)
- L47 _enumerator_ `ACN_DMX_PACKAGE_SIZE = 638` (scope `__anon523a81120503`)
- L48 _enumerator_ `ACN_DMX_ROOT_PACKAGE_SIZE = 38` (scope `__anon523a81120503`)
- L49 _enumerator_ `ACN_DMX_PDU_FRAMING_PACKAGE_SIZE = 77` (scope `__anon523a81120503`)
- L50 _enumerator_ `ACN_DMX_PDU_DMP_PACKAGE_SIZE = 523` (scope `__anon523a81120503`)
- L51 _enumerator_ `ACN_DMX_UDP_FRAMING_PACKAGE_SIZE = 74` (scope `__anon523a81120503`)
- L52 _enumerator_ `ACN_DMX_UDP_DISCOVERY_PACKAGE_SIZE = 1032` (scope `__anon523a81120503`)
- L53 _enumerator_ `ACN_DMX_MIN_PACKAGE_SIZE = ACN_DMX_ROOT_PACKAGE_SIZE + ACN_DMX_PDU_FRAMING_PACKAGE_SIZE + (ACN_DMX_PDU_DMP_PACKAGE_SIZE - ACN_DMX_SIZE)` (scope `__anon523a81120503`)
- L54 _enumerator_ `ACN_DMX_ROOT_FLAGS_AND_LENGTH_SIZE = 622` (scope `__anon523a81120503`)
- L55 _enumerator_ `ACN_DMX_FRAMING_FLAGS_AND_LENGTH_SIZE = 600` (scope `__anon523a81120503`)
- L56 _enumerator_ `ACN_DMX_DMP_FLAGS_AND_LENGTH_SIZE = 523` (scope `__anon523a81120503`)
- L61 _enumerator_ `VHD_L_FLAG = 0x80` (scope `__anon523a81120603`)
- L62 _enumerator_ `VHD_V_FLAG = 0x40` (scope `__anon523a81120603`)
- L63 _enumerator_ `VHD_H_FLAG = 0x20` (scope `__anon523a81120603`)
- L64 _enumerator_ `VHD_D_FLAG = 0x10` (scope `__anon523a81120603`)
- L69 _enumerator_ `ACN_DMX_START_CODE_PER_ADDRESS_PRIORITY = 0xDD` (scope `__anon523a81120703`)

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolSACN/Private/DMXProtocolSACNReceiver.h` (Private)


#### class `FDMXProtocolSACNReceiver`  
`class FDMXProtocolSACNReceiver : public FRunnable , public FSingleThreadRunnable`  
_L23-130_
- inherits: `FRunnable,FSingleThreadRunnable`
- L29 _protected prototype_ `FDMXProtocolSACNReceiver(const TSharedPtr<FDMXProtocolSACN, ESPMode::ThreadSafe>& InSACNProtocol, FSocket& InSocket, TSharedRef<FInternetAddr> InEndpointInternetAddr);` — Constructor. Hidden on purpose, use Create instead.
- L33 _public prototype_ `virtual ~FDMXProtocolSACNReceiver();` — Destructor
- L40 _public prototype_ `static TSharedPtr<FDMXProtocolSACNReceiver> TryCreate(const TSharedPtr<FDMXProtocolSACN, ESPMode::ThreadSafe>& SACNProtocol, const FString& IPAddress);` — Creates a new receiver for the specified IP address. returns null if no receiver can be created. Note: Doesn't test if another receiver on same IP already exists. Use HandlesInputPort to test other instances. If another receiver exists that handles IPAddress, reuse that instead.
- L44 _public prototype_ `bool EqualsEndpoint(const FString& IPAddress) const;` — Returns true if the receiver uses specified IP address
- L47 _public prototype_ `void AssignInputPort(const TSharedPtr<FDMXInputPort, ESPMode::ThreadSafe>& InputPort);` — Assigns an input port to be handled by this receiver
- L50 _public prototype_ `void UnassignInputPort(const TSharedPtr<FDMXInputPort, ESPMode::ThreadSafe>& InputPort);` — Unassigns an input port from this receiver
- L53 _public function_ `bool ContainsInputPort(const TSharedPtr<FDMXInputPort, ESPMode::ThreadSafe>& InputPort) const` — Returns true if the input port is currently assigned to this receiver
- L56 _public function_ `int32 GetNumAssignedInputPorts() const` — Gets the num input ports currently assigned to this receiver
- L59 _public function_ `const TSet<TSharedPtr<FDMXInputPort, ESPMode::ThreadSafe>>& GetAssignedInputPorts() const` — Returns the input ports assigned to the receiver
- L63 _public prototype_ `static uint32 GetIpForUniverseID(uint16 InUniverseID);` — `UE_DEPRECATED(5.0, "Deprecated in favor of the more generic FDMXProtocolSACNUtils::GetIPForUniverseID")` — Returns the IP address of a universe
- L67 _private member_ `TSet<TSharedPtr<FDMXInputPort, ESPMode::ThreadSafe>> AssignedInputPorts;` — The input ports the receiver uses
- L70 _private member_ `FCriticalSection AccessInputPortsMutex;` — Mutex access to the input ports array
- L74 _protected prototype_ `virtual bool Init() override;`
- L75 _protected prototype_ `virtual uint32 Run() override;`
- L76 _protected prototype_ `virtual void Stop() override;`
- L77 _protected prototype_ `virtual void Exit() override;`
- L81 _protected prototype_ `virtual void Tick() override;`
- L82 _protected prototype_ `virtual class FSingleThreadRunnable* GetSingleThreadInterface() override;`
- L90 _private prototype_ `void Update(const FTimespan& SocketWaitTime);` — Updates the thread with data from the socket. The socket will wait for specified time unless data is received.
- L93 _private prototype_ `void DistributeReceivedData(uint16 UniverseID, const TSharedRef<FArrayReader>& PacketReader);` — Distributes received data to the protocol to be processed further
- L96 _private prototype_ `void HandleDataPacket(uint16 UniverseID, const TSharedRef<FArrayReader>& PacketReader);` — Handles a received sACN data packet
- L99 _private prototype_ `uint32 GetRootPacketType(const TSharedPtr<FArrayReader>& Buffer);` — Returns the type of the root packet
- L102 _private member_ `TMap<uint32 , uint16 > MulticastGroupAddrToUniverseIDMap;` — Map of universes with their sender IP
- L105 _private member_ `TSharedPtr<FDMXProtocolSACN, ESPMode::ThreadSafe> Protocol;` — The owning sACN protocol
- L108 _private member_ `FSocket* Socket = nullptr;` — The network socket.
- L111 _private member_ `TSharedPtr<FInternetAddr> EndpointInternetAddr;` — The endpoint internet addr (usually the network interface card IP Address)
- L114 _private member_ `TSharedPtr<FInternetAddr> ReceivedSenderInternetAddr;` — The sender when packets are received
- L117 _private member_ `TSharedPtr<FInternetAddr> ReceivedDestinationInternetAddr;` — The destination when packets are received
- L120 _private member_ `TAtomic<bool> bStopping;` — Flag indicating that the thread is stopping.
- L123 _private member_ `FRunnableThread* Thread = nullptr;` — The thread object.
- L126 _private member_ `FString ThreadName;` — The receiver thread's name.
- L129 _private member_ `TMap<uint16, TArray<uint8>> PropertiesCacheValues;` — Cache of Universe properties

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolSACN/Private/DMXProtocolSACNSender.h` (Private)


#### class `FDMXProtocolSACNSender`  
`class FDMXProtocolSACNSender : public IDMXSender`  
_L24-112_
- inherits: `IDMXSender`
- L28 _protected prototype_ `FDMXProtocolSACNSender& operator=(const FDMXProtocolSACNSender&) = delete;`
- L29 _protected prototype_ `FDMXProtocolSACNSender(const FDMXProtocolSACNSender&) = delete;`
- L32 _protected prototype_ `FDMXProtocolSACNSender(const TSharedPtr<FDMXProtocolSACN, ESPMode::ThreadSafe>& InSACNProtocol, FSocket& InSocket, TSharedRef<FInternetAddr> InNetworkInternetAddr, TSharedRef<FInternetAddr> InDestinationInternetAddr, const bool bInIsMulticast);` — Constructor. Hidden on purpose, use TryCreateUnicastSender and TryCreateMulticastSender instead.
- L36 _public prototype_ `virtual ~FDMXProtocolSACNSender();` — Destructor
- L47 _public prototype_ `static TSharedPtr<FDMXProtocolSACNSender> TryCreateUnicastSender(const TSharedPtr<FDMXProtocolSACN, ESPMode::ThreadSafe>& SACNProtocol, const FString& InNetworkInterfaceIP, const FString& InUnicastIP);` — Creates a new unicast sender for the specified IP address. Returns null if no sender can be created. Note: Doesn't test if another sender on same IP already exists. Use EqualsEndpoint method to test other instances. If another sender exists that handles IPAddress, reuse that instead. @param SACNProtocol			The protocol instance that wants to create the sender @param InNetworkInterfaceIP		The IP address of the network interface that is used to send data @param InUnicastIP				The IP address to unicast to.
- L57 _public prototype_ `static TSharedPtr<FDMXProtocolSACNSender> TryCreateMulticastSender(const TSharedPtr<FDMXProtocolSACN, ESPMode::ThreadSafe>& SACNProtocol, const FString& InNetworkInterfaceIP, const uint8 TTL);` — Creates a new multicast sender for the specified IP address. Returns null if no sender can be created. Note: Doesn't test if another sender on same IP already exists. Use EqualsEndpoint method to test other instances. If another sender exists that handles IPAddress, reuse that instead. @param SACNProtocol			The protocol instance that wants to create the sender @param InNetworkInterfaceIP		The IP address of the network interface that is used to send data
- L60 _public prototype_ `virtual void SendDMXSignal(const FDMXSignalSharedRef& DMXSignal) override;`
- L65 _public prototype_ `bool IsCausingLoopback() const;` — Returns true if the sender causes loopbacks over the network
- L68 _public prototype_ `bool EqualsEndpoint(const FString& NetworkInterfaceIP, const FString& DestinationIPAddress) const;` — Returns true if the sender uses specified endpoint
- L71 _public prototype_ `void AssignOutputPort(const TSharedPtr<FDMXOutputPort, ESPMode::ThreadSafe>& OutputPort);` — Assigns an output port to be handled by this sender
- L74 _public prototype_ `void UnassignOutputPort(const TSharedPtr<FDMXOutputPort, ESPMode::ThreadSafe>& OutputPort);` — Unassigns an output port from this sender
- L77 _public function_ `bool ContainsOutputPort(const TSharedPtr<FDMXOutputPort, ESPMode::ThreadSafe>& OutputPort) const` — Returns true if the output port is currently assigned to this sender
- L80 _public function_ `int32 GetNumAssignedOutputPorts() const` — Gets the num output ports currently assigned to this sender
- L83 _public function_ `const TSet<TSharedPtr<FDMXOutputPort, ESPMode::ThreadSafe>>& GetAssignedOutputPorts() const` — Returns the output ports assigned to the sender
- L87 _private member_ `TSet<TSharedPtr<FDMXOutputPort, ESPMode::ThreadSafe>> AssignedOutputPorts;` — The Output ports the receiver uses
- L90 _private member_ `TMap<int32 , uint8 > UniverseIDToSequenceNumberMap;` — Map of universes with their current sequence number
- L93 _private member_ `TSharedPtr<FDMXProtocolSACN, ESPMode::ThreadSafe> Protocol;` — The sACN protocol instance
- L96 _private member_ `FSocket* Socket = nullptr;` — Holds the network socket used to sender packages.
- L99 _private member_ `FCriticalSection SendDMXCriticalSection;` — Critical section to be used during SendDMXSignal, as it may be called concurrently from many threads
- L102 _private member_ `TSharedPtr<FInternetAddr> NetworkInterfaceInternetAddr;` — The network interface internet addr
- L105 _private member_ `TSharedPtr<FInternetAddr> DestinationInternetAddr;` — The endpoint interface internet addr
- L108 _private member_ `EDMXCommunicationType CommunicationType;` — Communication type used for the network traffic
- L111 _private member_ `const bool bIsMulticast;` — Is a Multicast sender ?

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolSACN/Private/DMXProtocolSACNTypes.h` (Private)


#### struct `FDMXProtocolSACNSequenceNumber`  
`struct FDMXProtocolSACNSequenceNumber`  
_L8-26_
- L10 _public function_ `FDMXProtocolSACNSequenceNumber() : Curr(0x00)`
- L14 _public function_ `uint8 Increment()`
- L25 _private member_ `uint8 Curr;`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolSACN/Private/DMXProtocolSACNUtils.h` (Private)


#### class `FDMXProtocolSACNUtils`  
`class FDMXProtocolSACNUtils`  
_L12-20_
- L16 _public prototype_ `static uint32 GetIpForUniverseID(uint16 InUniverseID);` — Returns the SACN specific IP for a Universe ID
- L19 _public prototype_ `FDMXProtocolSACNUtils() = delete;` — Can't instantiate this class

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolSACN/Private/Packets/DMXProtocolE131PDUPacket.h` (Private)


#### struct `FDMXProtocolE131RootLayerPacket`  
`struct FDMXProtocolE131RootLayerPacket : public IDMXProtocolPacket`  
_L9-26_
- inherits: `IDMXProtocolPacket`
- L14 _public prototype_ `virtual TSharedPtr<FBufferArchive> Pack(const uint16 PropertiesNum) override;`
- L17 _public prototype_ `void Serialize(FArchive& Ar, uint16& PayloadLength);`
- L20 _public member_ `uint16 PreambleSize = ACN_RLP_PREAMBLE_SIZE;`
- L21 _public member_ `uint16 PostambleSize = 0;`
- L22 _public member_ `TArray<uint8, TInlineAllocator<ACN_IDENTIFIER_SIZE>> ACNPacketIdentifier = { 'A', 'S', 'C', '-', 'E', '1', '.', '1', '7', '\0', '\0', '\0' };`
- L23 _public member_ `uint16 FlagsAndLength = ACN_DMX_ROOT_FLAGS_AND_LENGTH_SIZE;`
- L24 _public member_ `uint32 Vector = VECTOR_ROOT_E131_DATA;`
- L25 _public member_ `TArray<uint8, TInlineAllocator<ACN_CIDBYTES>> CID = { 0 };`

#### struct `FDMXProtocolE131FramingLayerPacket`  
`struct FDMXProtocolE131FramingLayerPacket : public IDMXProtocolPacket`  
_L28-47_
- inherits: `IDMXProtocolPacket`
- L33 _public prototype_ `virtual TSharedPtr<FBufferArchive> Pack(const uint16 PropertiesNum) override;`
- L36 _public prototype_ `void Serialize(FArchive& Ar, uint16& PayloadLength);`
- L39 _public member_ `uint16 FlagsAndLength = ACN_DMX_FRAMING_FLAGS_AND_LENGTH_SIZE;`
- L40 _public member_ `uint32 Vector = VECTOR_E131_DATA_PACKET;`
- L41 _public member_ `TArray<uint8, TInlineAllocator<ACN_SOURCE_NAME_SIZE>> SourceName = { 'U', 'E', '5', '\0' };`
- L42 _public member_ `uint8 Priority = 1;`
- L43 _public member_ `uint16 SynchronizationAddress = 0;`
- L44 _public member_ `uint8 SequenceNumber = 0;`
- L45 _public member_ `uint8 Options = 0;`
- L46 _public member_ `uint16 Universe = 0;`

#### struct `FDMXProtocolE131DMPLayerPacket`  
`struct FDMXProtocolE131DMPLayerPacket : public IDMXProtocolPacket`  
_L49-74_
- inherits: `IDMXProtocolPacket`
- L53 _public function_ `FDMXProtocolE131DMPLayerPacket()`
- L60 _public prototype_ `virtual TSharedPtr<FBufferArchive> Pack(const uint16 PropertiesNum) override;`
- L63 _public prototype_ `void Serialize(FArchive& Ar, uint16& PayloadLength);`
- L66 _public member_ `uint16 FlagsAndLength = ACN_DMX_DMP_FLAGS_AND_LENGTH_SIZE;`
- L67 _public member_ `uint8 Vector = VECTOR_DMP_SET_PROPERTY;`
- L68 _public member_ `uint8 AddressTypeAndDataType = 0xa1;` — The const from SACN protocol documentation
- L69 _public member_ `uint16 FirstPropertyAddress = 0;`
- L70 _public member_ `uint16 AddressIncrement = 0;`
- L71 _public member_ `uint16 PropertyValueCount = 0;`
- L72 _public member_ `uint8 STARTCode = 0;`
- L73 _public member_ `TArray<uint8, TInlineAllocator<ACN_DMX_SIZE>> DMX;`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolSACN/Public/DMXProtocolSACNModule.h` (Public)


#### class `FDMXProtocolFactorySACN`  
`class FDMXProtocolFactorySACN : public IDMXProtocolFactory`  
_L16-20_
- inherits: `IDMXProtocolFactory`
- L19 _public prototype_ `virtual IDMXProtocolPtr CreateProtocol(const FName& ProtocolName) override;`

#### class `FDMXProtocolSACNModule`  
`class FDMXProtocolSACNModule : public IModuleInterface`  
_L24-73_
- inherits: `IModuleInterface`
- L29 _private member_ `TUniquePtr<FDMXProtocolFactorySACN> FactorySACN;` — Class responsible for creating instance(s) of the protocol
- L33 _public member_ `static FName const NAME_SACN;` — `UE_DEPRECATED(4.27, "Use DMX_PROTOCOLNAME_SACN instead, see DMXProtocolSACNConstants.h")`
- L37 _public prototype_ `virtual void StartupModule() override;`
- L38 _public prototype_ `virtual void ShutdownModule() override;`
- L41 _public prototype_ `FDMXProtocolSACNModule& Get();`
- L45 _private prototype_ `void RegisterWithProtocolModule(TArray<FDMXProtocolRegistrationParams>& InOutProtocolRegistrationParamsArray);` — Registers this sACN implementation with the Protocol Module
- L57 _private prototype_ `static void SendDMXCommandHandler(const TArray<FString>& Args);` — Sending DMX through console command Command structure is DMX.SACN.SendDMX [UniverseID] Channel:Value Channel:Value Channel:Value ... Example: DMX.SACN.SendDMX 7 25:156 26:0 27:10 28:15 It will send the DMX to Universe 7. It could be any value from 0 to 64214 And it update the channels values for channel 25, 26, 27, 28 with values 156, 0, 10, 15 Channel could be any value from 0 to 511 Value could be any value from 0 to 255
- L65 _private prototype_ `static void ResetDMXSendUniverseHandler(const TArray<FString>& Args);` — Reset DMX through console command Command structure is DMX.SACN.ResetDMXSend [UniverseID] Example: DMX.SACN.ResetDMXSend 7
- L69 _private member_ `static FAutoConsoleCommand SendDMXCommand;` — Command for sending DMX through the console
- L72 _private member_ `static FAutoConsoleCommand ResetDMXSendUniverseCommand;` — Command for reset DMX universe through the console
