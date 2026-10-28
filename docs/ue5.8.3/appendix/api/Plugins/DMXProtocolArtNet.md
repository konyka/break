# Plugins / DMXProtocolArtNet

- module root: `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolArtNet`
- headers: 6; symbols: 323
- symbol kinds: class=5, enum=10, enumerator=77, function=6, macro=3, member=140, prototype=73, struct=8, typedef=1
- PrivateDependencyModuleNames: CoreUObject, Engine, Json, Networking, Sockets
- PublicDependencyModuleNames: Core, DMXProtocol

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolArtNet/Private/DMXProtocolArtNet.h` (Private)


#### class `FDMXProtocolArtNet`  
`class FDMXProtocolArtNet : public IDMXProtocol`  
_L16-76_
- inherits: `IDMXProtocol`
- desc: Implements the Art-Net DMX Protocol
- L20 _public prototype_ `explicit FDMXProtocolArtNet(const FName& InProtocolName);`
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
- L37 _public prototype_ `int32 MakeValidUniverseID(int32 DesiredUniverseID) const override;`
- L38 _public prototype_ `virtual bool SupportsPrioritySettings() const override;`
- L39 _public prototype_ `virtual bool RegisterInputPort(const FDMXInputPortSharedRef& InputPort) override;`
- L40 _public prototype_ `virtual void UnregisterInputPort(const FDMXInputPortSharedRef& InputPort) override;`
- L41 _public prototype_ `virtual TArray<TSharedPtr<IDMXSender>> RegisterOutputPort(const FDMXOutputPortSharedRef& OutputPort) override;`
- L42 _public prototype_ `virtual void UnregisterOutputPort(const FDMXOutputPortSharedRef& OutputPort) override;`
- L43 _public prototype_ `virtual bool IsCausingLoopback(EDMXCommunicationType InCommunicationType) override;`
- L47 _public member_ `static const TArray<EDMXCommunicationType> InputPortCommunicationTypes;` — The supported input port communication types
- L50 _public member_ `static const TArray<EDMXCommunicationType> OutputPortCommunicationTypes;` — The supported output port communication types
- L54 _private prototype_ `TSharedPtr<FDMXProtocolArtNetSender> FindExistingBroadcastSender(const FString& NetworkInterfaceAddress) const;` — Returns the sender for specified endpoint or nullptr if none exists
- L57 _private prototype_ `TSharedPtr<FDMXProtocolArtNetSender> FindExistingUnicastSender(const FString& NetworkInterfaceAddress, const FString& DestinationAddress) const;` — Returns the sender for specified endpoint or nullptr if none exists
- L60 _private prototype_ `TSharedPtr<FDMXProtocolArtNetReceiver> FindExistingReceiver(const FString& IPAddress, EDMXCommunicationType CommunicationType) const;` — Returns the receiver for specified endpoint or nullptr if none exists
- L63 _private member_ `TSet<FDMXInputPortSharedRef> CachedInputPorts;` — Set of all DMX input ports currently in use
- L66 _private member_ `TSet<FDMXOutputPortSharedRef> CachedOutputPorts;` — Set of all DMX input ports currently in use
- L69 _private member_ `TSet<TSharedPtr<FDMXProtocolArtNetReceiver>> Receivers;` — Set of receivers currently in use
- L72 _private member_ `TSet<TSharedPtr<FDMXProtocolArtNetSender>> Senders;` — Set of receivers currently in use
- L75 _private member_ `FName ProtocolName;`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolArtNet/Private/DMXProtocolArtNetConstants.h` (Private)


#### enum `(anonymous)`  
``  
_L9-12_

#### enum `(anonymous)`  
``  
_L25-34_

#### enum `(anonymous)`  
`enum`  
_L36-58_

#### enum `(anonymous)`  
``  
_L61-65_

#### enum `(anonymous)`  
``  
_L68-71_

#### enum `(anonymous)`  
``  
_L74-78_

#### enum `(anonymous)`  
`typedef enum`  
_L81-84_
- desc: TOD actions

#### enum `(anonymous)`  
``  
_L89-99_

#### enum `(anonymous)`  
``  
_L103-105_

#### enum `(anonymous)`  
``  
_L108-141_

#### Free symbols / members of external scopes

- L10 _enumerator_ `LOW_BYTE = 0x00FF` (scope `__anonf9d503240103`)
- L11 _enumerator_ `HIGH_BYTE = 0xFF00` (scope `__anonf9d503240103`)
- L15 _macro_ `#define DMX_SHORT_GET_HIGH_BIT(x) ((HIGH_BYTE & x) >> 8)`
- L19 _macro_ `#define DMX_SHORT_GET_LOW_BYTE(x) (LOW_BYTE & x)`
- L22 _macro_ `#define DMX_PROTOCOLNAME_ARTNET "Art-Net"`
- L26 _enumerator_ `ARTNET_LONG_NAME_LENGTH = 64` (scope `__anonf9d503240203`)
- L27 _enumerator_ `ARTNET_MAX_PORTS = 4` (scope `__anonf9d503240203`)
- L28 _enumerator_ `ARTNET_MAX_RDM_ADDRESS_COUNT = 32` (scope `__anonf9d503240203`)
- L29 _enumerator_ `ARTNET_MAX_RDM_DATA = 512` (scope `__anonf9d503240203`)
- L30 _enumerator_ `ARTNET_MAX_UID_COUNT = 200` (scope `__anonf9d503240203`)
- L31 _enumerator_ `ARTNET_REPORT_LENGTH = 64` (scope `__anonf9d503240203`)
- L32 _enumerator_ `ARTNET_SHORT_NAME_LENGTH = 18` (scope `__anonf9d503240203`)
- L33 _enumerator_ `ARTNET_UNIVERSE_ADDRESS = 14` (scope `__anonf9d503240203`)
- L37 _enumerator_ `ARTNET_POLL = 0x2000` (scope `__anonf9d503240303`)
- L38 _enumerator_ `ARTNET_REPLY = 0x2100` (scope `__anonf9d503240303`)
- L39 _enumerator_ `ARTNET_DMX = 0x5000` (scope `__anonf9d503240303`)
- L40 _enumerator_ `ARTNET_ADDRESS = 0x6000` (scope `__anonf9d503240303`)
- L41 _enumerator_ `ARTNET_INPUT = 0x7000` (scope `__anonf9d503240303`)
- L42 _enumerator_ `ARTNET_TODREQUEST = 0x8000` (scope `__anonf9d503240303`)
- L43 _enumerator_ `ARTNET_TODDATA = 0x8100` (scope `__anonf9d503240303`)
- L44 _enumerator_ `ARTNET_TODCONTROL = 0x8200` (scope `__anonf9d503240303`)
- L45 _enumerator_ `ARTNET_RDM = 0x8300` (scope `__anonf9d503240303`)
- L46 _enumerator_ `ARTNET_VIDEOSTEUP = 0xa010` (scope `__anonf9d503240303`)
- L47 _enumerator_ `ARTNET_VIDEOPALETTE = 0xa020` (scope `__anonf9d503240303`)
- L48 _enumerator_ `ARTNET_VIDEODATA = 0xa040` (scope `__anonf9d503240303`)
- L49 _enumerator_ `ARTNET_MACMASTER = 0xf000` (scope `__anonf9d503240303`)
- L50 _enumerator_ `ARTNET_MACSLAVE = 0xf100` (scope `__anonf9d503240303`)
- L51 _enumerator_ `ARTNET_FIRMWAREMASTER = 0xf200` (scope `__anonf9d503240303`)
- L52 _enumerator_ `ARTNET_FIRMWAREREPLY = 0xf300` (scope `__anonf9d503240303`)
- L53 _enumerator_ `ARTNET_IPPROG = 0xf800` (scope `__anonf9d503240303`)
- L54 _enumerator_ `ARTNET_IPREPLY = 0xf900` (scope `__anonf9d503240303`)
- L55 _enumerator_ `ARTNET_MEDIA = 0x9000` (scope `__anonf9d503240303`)
- L56 _enumerator_ `ARTNET_MEDIAPATCH = 0x9200` (scope `__anonf9d503240303`)
- L57 _enumerator_ `ARTNET_MEDIACONTROLREPLY = 0x9300` (scope `__anonf9d503240303`)
- L62 _enumerator_ `ARTNET_DMX_LENGTH = 512` (scope `__anonf9d503240403`)
- L63 _enumerator_ `ARTNET_DMX_PACKAGE_SIZE = 530` (scope `__anonf9d503240403`)
- L64 _enumerator_ `ARTNET_POLL_PACKAGE_SIZE = 14` (scope `__anonf9d503240403`)
- L69 _enumerator_ `ARTNET_MIN_UNIVERSE = 0` (scope `__anonf9d503240503`)
- L70 _enumerator_ `ARTNET_MAX_UNIVERSE = 32767` (scope `__anonf9d503240503`)
- L75 _enumerator_ `ARTNET_TTM_DEFAULT = 0xFF` (scope `__anonf9d503240603`)
- L76 _enumerator_ `ARTNET_TTM_PRIVATE = 0xFE` (scope `__anonf9d503240603`) — ARTNET_TTM_DEFAULT = 0xFF,   < default, ArtPollReplies are broadcast, and nodes won't send a ArtPollReply when conditions change
- L77 _enumerator_ `ARTNET_TTM_noauto = 0xFD` (scope `__anonf9d503240603`) — ARTNET_TTM_PRIVATE = 0xFE,   < ArtPollReplies aren't broadcast
- L82 _enumerator_ `ARTNET_TOD_FULL = 0x00` (scope `__anonf9d503240703`)
- L83 _enumerator_ `ARTNET_TOD_FLUSH = 0x01` (scope `__anonf9d503240703`)
- L84 _typedef_ `ARTNET_TOD_FULL = 0x00, ARTNET_TOD_FLUSH = 0x01, } artnet_tod_command_code;`
- L90 _enumerator_ `ARTNET_RDM_VERSION = 0x01` (scope `__anonf9d503240803`)
- L91 _enumerator_ `ARTNET_MAX_RDM_ADCOUNT = 32` (scope `__anonf9d503240803`)
- L98 _enumerator_ `ARTNET_RDM_UID_WIDTH = 6` (scope `__anonf9d503240803`) — ARTNET_RDM_UID_WIDTH are 6 bytes, the first two bytes are the [manufacturer code](http://tsp.esta.org/tsp/working_groups/CP/mfctrIDs.php) and the last 4 bytes are the device id. UIDs are written as: XXXX:YYYYYYYY
- L104 _enumerator_ `ARTNET_RDM_PROCESS_PACKET = 0x00` (scope `__anonf9d503240903`)
- L109 _enumerator_ `ARTNET_ADDRESS_NO_CHANGE = 0x7f` (scope `__anonf9d503240a03`)
- L110 _enumerator_ `ARTNET_PORT = 6454` (scope `__anonf9d503240a03`)
- L111 _enumerator_ `ARTNET_SENDER_PORT = 3330` (scope `__anonf9d503240a03`)
- L112 _enumerator_ `ARTNET_STRING_SIZE = 8` (scope `__anonf9d503240a03`)
- L113 _enumerator_ `ARTNET_VERSION = 14` (scope `__anonf9d503240a03`)
- L114 _enumerator_ `OEM_HI = 0x04` (scope `__anonf9d503240a03`)
- L115 _enumerator_ `OEM_LO = 0x30` (scope `__anonf9d503240a03`)
- L116 _enumerator_ `ESTA_HI = 'z'` (scope `__anonf9d503240a03`)
- L117 _enumerator_ `ESTA_LO = 'p'` (scope `__anonf9d503240a03`)
- L118 _enumerator_ `TTM_BEHAVIOUR_MASK = 0x02` (scope `__anonf9d503240a03`)
- L119 _enumerator_ `TTM_REPLY_MASK = 0x01` (scope `__anonf9d503240a03`)
- L120 _enumerator_ `PROGRAM_NO_CHANGE = 0x7f` (scope `__anonf9d503240a03`)
- L121 _enumerator_ `PROGRAM_DEFAULTS = 0x00` (scope `__anonf9d503240a03`)
- L122 _enumerator_ `PROGRAM_CHANGE_MASK = 0x80` (scope `__anonf9d503240a03`)
- L123 _enumerator_ `STATUS_PROG_AUTH_MASK = 0x30` (scope `__anonf9d503240a03`)
- L124 _enumerator_ `PORT_STATUS_LPT_MODE = 0x02` (scope `__anonf9d503240a03`)
- L125 _enumerator_ `PORT_STATUS_SHORT = 0x04` (scope `__anonf9d503240a03`)
- L126 _enumerator_ `PORT_STATUS_ERROR = 0x04` (scope `__anonf9d503240a03`)
- L127 _enumerator_ `PORT_STATUS_DISABLED_MASK = 0x08` (scope `__anonf9d503240a03`)
- L128 _enumerator_ `PORT_STATUS_MERGE = 0x08` (scope `__anonf9d503240a03`)
- L129 _enumerator_ `PORT_STATUS_DMXEXT = 0x10` (scope `__anonf9d503240a03`)
- L130 _enumerator_ `PORT_STATUS_DMX_SIP = 0x20` (scope `__anonf9d503240a03`)
- L131 _enumerator_ `PORT_STATUS_DMXEST = 0x40` (scope `__anonf9d503240a03`)
- L132 _enumerator_ `PORT_STATUS_ACT_MASK = 0x80` (scope `__anonf9d503240a03`)
- L133 _enumerator_ `PORT_DISABLE_MASK = 0x01` (scope `__anonf9d503240a03`)
- L134 _enumerator_ `TOD_RESPONSE_FULL = 0x00` (scope `__anonf9d503240a03`)
- L135 _enumerator_ `TOD_RESPONSE_NAK = 0x00` (scope `__anonf9d503240a03`)
- L136 _enumerator_ `MIN_PACKET_SIZE = 10` (scope `__anonf9d503240a03`)
- L137 _enumerator_ `MERGEIMEOUT_SECONDS = 10` (scope `__anonf9d503240a03`)
- L138 _enumerator_ `FIRMWAREIMEOUT_SECONDS = 20` (scope `__anonf9d503240a03`)
- L139 _enumerator_ `RECV_NO_DATA = 1` (scope `__anonf9d503240a03`)
- L140 _enumerator_ `MAX_NODE_BCAST_LIMIT = 30` (scope `__anonf9d503240a03`) — always bcast after this point

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolArtNet/Private/DMXProtocolArtNetReceiver.h` (Private)


#### class `FDMXProtocolArtNetReceiver`  
`class FDMXProtocolArtNetReceiver : public FRunnable , public FSingleThreadRunnable`  
_L23-127_
- inherits: `FRunnable,FSingleThreadRunnable`
- L29 _protected prototype_ `FDMXProtocolArtNetReceiver(const TSharedPtr<FDMXProtocolArtNet, ESPMode::ThreadSafe>& InArtNetProtocol, FSocket& InSocket, TSharedRef<FInternetAddr> InEndpointInternetAddr);` — Constructor. Hidden on purpose, use Create instead.
- L33 _public prototype_ `virtual ~FDMXProtocolArtNetReceiver();` — Destructor
- L40 _public prototype_ `static TSharedPtr<FDMXProtocolArtNetReceiver> TryCreate(const TSharedPtr<FDMXProtocolArtNet, ESPMode::ThreadSafe>& ArtNetProtocol, const FString& IPAddress);` — Creates a new receiver for the specified IP address. returns null if no receiver can be created. Note: Doesn't test if another receiver on same IP already exists. Use HandlesInputPort to test other instances. If another receiver exists that handles IPAddress, reuse that instead.
- L44 _public prototype_ `bool EqualsEndpoint(const FString& IPAddress) const;` — Returns true if the receiver uses specified IP address
- L47 _public prototype_ `void AssignInputPort(const TSharedPtr<FDMXInputPort, ESPMode::ThreadSafe>& InputPort);` — Assigns an input port to be handled by this receiver
- L50 _public prototype_ `void UnassignInputPort(const TSharedPtr<FDMXInputPort, ESPMode::ThreadSafe>& InputPort);` — Unassigns an input port from this receiver
- L53 _public function_ `bool ContainsInputPort(const TSharedPtr<FDMXInputPort, ESPMode::ThreadSafe>& InputPort) const` — Returns true if the input port is currently assigned to this receiver
- L56 _public function_ `int32 GetNumAssignedInputPorts() const` — Gets the num input ports currently assigned to this receiver
- L59 _public function_ `const TSet<TSharedPtr<FDMXInputPort, ESPMode::ThreadSafe>>& GetAssignedInputPorts() const` — Returns the input ports assigned to the receiver
- L63 _private member_ `TSet<TSharedPtr<FDMXInputPort, ESPMode::ThreadSafe>> AssignedInputPorts;` — The input ports the receiver uses
- L66 _private member_ `FCriticalSection AccessInputPortsMutex;` — Mutex access to the input ports array
- L70 _protected prototype_ `virtual bool Init() override;`
- L71 _protected prototype_ `virtual uint32 Run() override;`
- L72 _protected prototype_ `virtual void Stop() override;`
- L73 _protected prototype_ `virtual void Exit() override;`
- L77 _protected prototype_ `virtual void Tick() override;`
- L78 _protected prototype_ `virtual class FSingleThreadRunnable* GetSingleThreadInterface() override;`
- L86 _protected prototype_ `void Update(const FTimespan& SocketWaitTime);` — Updates the thread with data from the socket. The socket will wait for specified time unless data is received.
- L89 _protected prototype_ `void DistributeReceivedData(const TSharedRef<FArrayReader>& PacketReader);` — Distributes received data to the protocol to be processed further
- L92 _protected prototype_ `uint16 GetPacketOpCode(const TSharedRef<FArrayReader>& PacketReader) const;` — Get package 2 bytes ID from the buffer, as it was received
- L95 _protected prototype_ `void HandleDataPacket(const TSharedRef<FArrayReader>& PacketReader);` — Handles a received Art-Net data packet
- L99 _protected prototype_ `void HandlePool(const TSharedRef<FArrayReader>& PacketReader);` — Handlers for recognized but not implemented packages
- L100 _protected prototype_ `void HandleReplyPacket(const TSharedRef<FArrayReader>& PacketReader);`
- L101 _protected prototype_ `void HandleTodRequest(const TSharedRef<FArrayReader>& PacketReader);`
- L102 _protected prototype_ `void HandleTodData(const TSharedRef<FArrayReader>& PacketReader);`
- L103 _protected prototype_ `void HandleTodControl(const TSharedRef<FArrayReader>& PacketReader);`
- L104 _protected prototype_ `void HandleRdm(const TSharedRef<FArrayReader>& PacketReader);`
- L108 _private member_ `TSharedPtr<FDMXProtocolArtNet, ESPMode::ThreadSafe> Protocol;` — The owning Art-Net protocol
- L111 _private member_ `FSocket* Socket = nullptr;` — The network socket.
- L114 _private member_ `TSharedPtr<FInternetAddr> EndpointInternetAddr;` — The endpoint internet addr (usually the network interface card IP Address)
- L117 _private member_ `TSharedPtr<FInternetAddr> ReceivedSenderInternetAddr;` — The sender when packets were received
- L120 _private member_ `TAtomic<bool> bStopping;` — Flag indicating that the thread is stopping.
- L123 _private member_ `FRunnableThread* Thread = nullptr;` — The thread object.
- L126 _private member_ `FString ThreadName;` — The receiver thread's name.

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolArtNet/Private/DMXProtocolArtNetSender.h` (Private)


#### class `FDMXProtocolArtNetSender`  
`class FDMXProtocolArtNetSender : public IDMXSender`  
_L23-105_
- inherits: `IDMXSender`
- L28 _protected prototype_ `FDMXProtocolArtNetSender(const TSharedPtr<FDMXProtocolArtNet, ESPMode::ThreadSafe>& InArtNetProtocol, FSocket& InSocket, TSharedRef<FInternetAddr> InNetworkInternetAddr, TSharedRef<FInternetAddr> InDestinationInternetAddr);` — Constructor. Hidden on purpose, use Create instead.
- L32 _public prototype_ `virtual ~FDMXProtocolArtNetSender();` — Destructor
- L43 _public prototype_ `static TSharedPtr<FDMXProtocolArtNetSender> TryCreateUnicastSender(const TSharedPtr<FDMXProtocolArtNet, ESPMode::ThreadSafe>& ArtNetProtocol, const FString& InNetworkInterfaceIP, const FString& InUnicastIP);` — Creates a new unicast sender for the specified IP address. Returns null if no sender can be created. Note: Doesn't test if another sender on same IP already exists. Use EqualsEndpoint method to test other instances. If another sender exists that handles IPAddress, reuse that instead. @param ArtNetProtocol			The protocol instance that wants to create the sender @param InNetworkInterfaceIP		The IP address of the network interface that is used to send data @param InUnicastIP				The IP address to unicast to.
- L53 _public prototype_ `static TSharedPtr<FDMXProtocolArtNetSender> TryCreateBroadcastSender(const TSharedPtr<FDMXProtocolArtNet, ESPMode::ThreadSafe>& ArtNetProtocol, const FString& InNetworkInterfaceIP);` — Creates a new broadcast sender for the specified IP address. Returns null if no sender can be created. Note: Doesn't test if another sender on same IP already exists. Use EqualsEndpoint method to test other instances. If another sender exists that handles IPAddress, reuse that instead. @param ArtNetProtocol			The protocol instance that wants to create the sender @param InNetworkInterfaceIP		The IP address of the network interface that is used to send data
- L56 _public prototype_ `virtual void SendDMXSignal(const FDMXSignalSharedRef& DMXSignal) override;`
- L61 _public prototype_ `bool IsCausingLoopback() const;` — Returns true if the sender causes loopbacks over the network
- L64 _public prototype_ `bool EqualsEndpoint(const FString& NetworkInterfaceIP, const FString& DestinationIPAddress) const;` — Returns true if the sender uses specified endpoint
- L67 _public prototype_ `void AssignOutputPort(const TSharedPtr<FDMXOutputPort, ESPMode::ThreadSafe>& OutputPort);` — Assigns an output port to be handled by this sender
- L70 _public prototype_ `void UnassignOutputPort(const TSharedPtr<FDMXOutputPort, ESPMode::ThreadSafe>& OutputPort);` — Unassigns an output port from this sender
- L73 _public function_ `bool ContainsOutputPort(const TSharedPtr<FDMXOutputPort, ESPMode::ThreadSafe>& OutputPort) const` — Returns true if the output port is currently assigned to this sender
- L76 _public function_ `int32 GetNumAssignedOutputPorts() const` — Gets the num output ports currently assigned to this sender
- L79 _public function_ `const TSet<TSharedPtr<FDMXOutputPort, ESPMode::ThreadSafe>>& GetAssignedOutputPorts() const` — Returns the output ports assigned to the sender
- L83 _private prototype_ `static TSharedRef<FInternetAddr> CreateBroadcastInternetAddr(int32 Port);` — Helper to create a broadcast internet address.
- L86 _private member_ `TSet<TSharedPtr<FDMXOutputPort, ESPMode::ThreadSafe>> AssignedOutputPorts;` — The Output ports the receiver uses
- L89 _private member_ `TSharedPtr<FDMXProtocolArtNet, ESPMode::ThreadSafe> Protocol;` — The Art-Net protocol instance
- L92 _private member_ `FSocket* Socket = nullptr;` — Holds the network socket used to sender packages.
- L95 _private member_ `FCriticalSection SendDMXCriticalSection;` — Critical section to be used during SendDMXSignal, as it may be called concurrently from many threads
- L98 _private member_ `TSharedPtr<FInternetAddr> NetworkInterfaceInternetAddr;` — The network interface internet addr
- L101 _private member_ `TSharedPtr<FInternetAddr> DestinationInternetAddr;` — The endpoint interface internet addr
- L104 _private member_ `EDMXCommunicationType CommunicationType;` — Communication type used for the network traffic

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolArtNet/Private/Packets/DMXProtocolArtNetPackets.h` (Private)


#### struct `FDMXProtocolArtNetPacket`  
`struct FDMXProtocolArtNetPacket : public IDMXProtocolPacket`  
_L9-14_
- inherits: `IDMXProtocolPacket`
- L13 _public member_ `uint8 ID[ARTNET_STRING_SIZE] = DMX_PROTOCOLNAME_ARTNET;`

#### struct `FDMXProtocolArtNetDMXPacket`  
`struct FDMXProtocolArtNetDMXPacket : public FDMXProtocolArtNetPacket`  
_L16-38_
- inherits: `FDMXProtocolArtNetPacket`
- L21 _public prototype_ `virtual TSharedPtr<FBufferArchive> Pack(const uint16 NumProperties) override;`
- L24 _public prototype_ `void Serialize(FArchive& Ar);`
- L28 _public member_ `uint16 OpCode = ARTNET_DMX;`
- L30 _public member_ `uint8 VerH = 0;`
- L31 _public member_ `uint8 Ver = ARTNET_VERSION;`
- L32 _public member_ `uint8 Sequence = 0;`
- L33 _public member_ `uint8 Physical = 0;`
- L34 _public member_ `uint16 Universe = 0;`
- L35 _public member_ `uint8 LengthHi = DMX_SHORT_GET_HIGH_BIT(ARTNET_DMX_LENGTH);`
- L36 _public member_ `uint8 Length = DMX_SHORT_GET_LOW_BYTE(ARTNET_DMX_LENGTH);`
- L37 _public member_ `uint8 Data[ARTNET_DMX_LENGTH] = { 0 };`

#### struct `FDMXProtocolArtNetPollPacket`  
`struct FDMXProtocolArtNetPollPacket : public FDMXProtocolArtNetPacket`  
_L40-57_
- inherits: `FDMXProtocolArtNetPacket`
- L45 _public prototype_ `virtual TSharedPtr<FBufferArchive> Pack(const uint16 NumProperties) override;`
- L48 _public prototype_ `void Serialize(FArchive& Ar);`
- L52 _public member_ `uint16 OpCode = ARTNET_POLL;`
- L53 _public member_ `uint8 VerH = 0;`
- L54 _public member_ `uint8 Ver = ARTNET_VERSION;`
- L55 _public member_ `uint8 TalkToMe = ARTNET_TTM_DEFAULT;`
- L56 _public member_ `uint8 Priority = 0;`

#### struct `FDMXProtocolArtNetPacketReply`  
`struct FDMXProtocolArtNetPacketReply : public FDMXProtocolArtNetPacket`  
_L59-99_
- inherits: `FDMXProtocolArtNetPacket`
- L63 _public prototype_ `void Serialize(FArchive& Ar);`
- L67 _public member_ `uint16 OpCode = 0;`
- L69 _public member_ `uint8 Ip[4] = { 0 };`
- L70 _public member_ `uint16 Port = 0;`
- L71 _public member_ `uint16 Version = 0;`
- L72 _public member_ `uint8 NetAddress = 0;`
- L73 _public member_ `uint8 SubnetAddress = 0;`
- L74 _public member_ `uint16 Oem = 0;`
- L75 _public member_ `uint8 Ubea = 0;`
- L76 _public member_ `uint8 Status1 = 0;`
- L77 _public member_ `uint16 EstaId = 0;`
- L78 _public member_ `uint8 ShortName[ARTNET_SHORT_NAME_LENGTH] = { 0 };`
- L79 _public member_ `uint8 LongName[ARTNET_LONG_NAME_LENGTH] = { 0 };`
- L80 _public member_ `uint8 NodeReport[ARTNET_REPORT_LENGTH] = { 0 };`
- L81 _public member_ `uint8 NumberPorts[2] = { 0 };`
- L82 _public member_ `uint8 PortTypes[ARTNET_MAX_PORTS] = { 0 };`
- L83 _public member_ `uint8 GoodInput[ARTNET_MAX_PORTS] = { 0 };`
- L84 _public member_ `uint8 GoodOutput[ARTNET_MAX_PORTS] = { 0 };`
- L85 _public member_ `uint8 SwIn[ARTNET_MAX_PORTS] = { 0 };`
- L86 _public member_ `uint8 SwOut[ARTNET_MAX_PORTS] = { 0 };`
- L87 _public member_ `uint8 SwVideo = 0;`
- L88 _public member_ `uint8 SwMacro = 0;`
- L89 _public member_ `uint8 SwRemote = 0;`
- L90 _public member_ `uint8 Spare1 = 0;`
- L91 _public member_ `uint8 Spare2 = 0;`
- L92 _public member_ `uint8 Spare3 = 0;`
- L93 _public member_ `uint8 Style = 0;`
- L94 _public member_ `uint8 Mac[6] = { 0 };`
- L95 _public member_ `uint8 BindIp[4] = { 0 };`
- L96 _public member_ `uint8 BindIndex = 0;`
- L97 _public member_ `uint8 Status2 = 0;`
- L98 _public member_ `uint8 Filler[26] = { 0 };`

#### struct `FDMXProtocolArtNetTodRequest`  
`struct FDMXProtocolArtNetTodRequest : public FDMXProtocolArtNetPacket`  
_L101-130_
- inherits: `FDMXProtocolArtNetPacket`
- L106 _public prototype_ `virtual TSharedPtr<FBufferArchive> Pack(uint16) override;`
- L109 _public prototype_ `void Serialize(FArchive& Ar);`
- L113 _public member_ `uint16 OpCode = ARTNET_TODREQUEST;`
- L115 _public member_ `uint8 VerH = 0;`
- L116 _public member_ `uint8 Ver = ARTNET_VERSION;`
- L117 _public member_ `uint8 Filler1 = 0;`
- L118 _public member_ `uint8 Filler2 = 0;`
- L119 _public member_ `uint8 Spare1 = 0;`
- L120 _public member_ `uint8 Spare2 = 0;`
- L121 _public member_ `uint8 Spare3 = 0;`
- L122 _public member_ `uint8 Spare4 = 0;`
- L123 _public member_ `uint8 Spare5 = 0;`
- L124 _public member_ `uint8 Spare6 = 0;`
- L125 _public member_ `uint8 Spare7 = 0;`
- L126 _public member_ `uint8 Net = 0;`
- L127 _public member_ `uint8 Command = ARTNET_TOD_FULL;`
- L128 _public member_ `uint8 AdCount = 0;`
- L129 _public member_ `uint8 Address[ARTNET_MAX_RDM_ADCOUNT] = { 0 };`

#### struct `FDMXProtocolArtNetTodData`  
`struct FDMXProtocolArtNetTodData : public FDMXProtocolArtNetPacket`  
_L132-165_
- inherits: `FDMXProtocolArtNetPacket`
- L137 _public prototype_ `virtual TSharedPtr<FBufferArchive> Pack(const uint16 NumProperties) override;`
- L140 _public prototype_ `void Serialize(FArchive& Ar);`
- L144 _public member_ `uint16 OpCode = ARTNET_TODDATA;`
- L146 _public member_ `uint8 VerH = 0;`
- L147 _public member_ `uint8 Ver = ARTNET_VERSION;`
- L148 _public member_ `uint8 RDMVer = ARTNET_RDM_VERSION;`
- L149 _public member_ `uint8 Port = 0;`
- L150 _public member_ `uint8 Spare1 = 0;`
- L151 _public member_ `uint8 Spare2 = 0;`
- L152 _public member_ `uint8 Spare3 = 0;`
- L153 _public member_ `uint8 Spare4 = 0;`
- L154 _public member_ `uint8 Spare5 = 0;`
- L155 _public member_ `uint8 Spare6 = 0;`
- L156 _public member_ `uint8 Spare7 = 0;`
- L157 _public member_ `uint8 Net = 0;`
- L158 _public member_ `uint8 CmdRes = ARTNET_TOD_FULL;`
- L159 _public member_ `uint8 Address = 0;`
- L160 _public member_ `uint8 UidTotalHi = 0;`
- L161 _public member_ `uint8 UidTotal = 0;`
- L162 _public member_ `uint8 BlockCount = 0;`
- L163 _public member_ `uint8 UidCount = 0;`
- L164 _public member_ `uint8 Tod[ARTNET_MAX_UID_COUNT][ARTNET_RDM_UID_WIDTH] = { { 0 } };`

#### struct `FDMXProtocolArtNetTodControl`  
`struct FDMXProtocolArtNetTodControl : public FDMXProtocolArtNetPacket`  
_L171-199_
- inherits: `FDMXProtocolArtNetPacket`
- desc: The ArtTodControl packet is used to send RDM control parameters over Art-Net. The response is ArtTodData.
- L176 _public prototype_ `virtual TSharedPtr<FBufferArchive> Pack(const uint16 NumProperties) override;`
- L179 _public prototype_ `void Serialize(FArchive& Ar);`
- L183 _public member_ `uint16 OpCode = ARTNET_TODCONTROL;`
- L185 _public member_ `uint8 VerH = 0;`
- L186 _public member_ `uint8 Ver = ARTNET_VERSION;`
- L187 _public member_ `uint8 Filler1 = 0;`
- L188 _public member_ `uint8 Filler2 = 0;`
- L189 _public member_ `uint8 Spare1 = 0;`
- L190 _public member_ `uint8 Spare2 = 0;`
- L191 _public member_ `uint8 Spare3 = 0;`
- L192 _public member_ `uint8 Spare4 = 0;`
- L193 _public member_ `uint8 Spare5 = 0;`
- L194 _public member_ `uint8 Spare6 = 0;`
- L195 _public member_ `uint8 Spare7 = 0;`
- L196 _public member_ `uint8 Net = 0;`
- L197 _public member_ `uint8 Cmd = 0;`
- L198 _public member_ `uint8 Address = 0;`

#### struct `FDMXProtocolArtNetRDM`  
`struct FDMXProtocolArtNetRDM : public FDMXProtocolArtNetPacket`  
_L201-230_
- inherits: `FDMXProtocolArtNetPacket`
- L206 _public prototype_ `virtual TSharedPtr<FBufferArchive> Pack(const uint16 NumProperties) override;`
- L209 _public prototype_ `void Serialize(FArchive& Ar);`
- L213 _public member_ `uint16 OpCode = ARTNET_RDM;`
- L215 _public member_ `uint8 VerH = 0;`
- L216 _public member_ `uint8 Ver = ARTNET_VERSION;`
- L217 _public member_ `uint8 RdmVer = 0;`
- L218 _public member_ `uint8 Filler2 = 0;`
- L219 _public member_ `uint8 Spare1 = 0;`
- L220 _public member_ `uint8 Spare2 = 0;`
- L221 _public member_ `uint8 Spare3 = 0;`
- L222 _public member_ `uint8 Spare4 = 0;`
- L223 _public member_ `uint8 Spare5 = 0;`
- L224 _public member_ `uint8 Spare6 = 0;`
- L225 _public member_ `uint8 Spare7 = 0;`
- L226 _public member_ `uint8 Net = 0;`
- L227 _public member_ `uint8 Cmd = ARTNET_RDM_PROCESS_PACKET;`
- L228 _public member_ `uint8 Address = 0;`
- L229 _public member_ `uint8 Data[ARTNET_MAX_RDM_DATA] = { 0 };`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolArtNet/Public/DMXProtocolArtNetModule.h` (Public)


#### class `FDMXProtocolFactoryArtNet`  
`class FDMXProtocolFactoryArtNet : public IDMXProtocolFactory`  
_L16-20_
- inherits: `IDMXProtocolFactory`
- L19 _public prototype_ `virtual IDMXProtocolPtr CreateProtocol(const FName& ProtocolName) override;`

#### class `FDMXProtocolArtNetModule`  
`class FDMXProtocolArtNetModule : public IModuleInterface`  
_L25-76_
- inherits: `IModuleInterface`
- L31 _private member_ `TUniquePtr<FDMXProtocolFactoryArtNet> FactoryArtNet;` — Class responsible for creating instance(s) of the protocol
- L35 _public member_ `static FName const NAME_Artnet;` — `UE_DEPRECATED(4.27, "Use DMX_PROTOCOLNAME_ARTNET instead")`
- L39 _public prototype_ `virtual void StartupModule() override;`
- L40 _public prototype_ `virtual void ShutdownModule() override;`
- L44 _public prototype_ `static FDMXProtocolArtNetModule& Get();` — Get the instance of this module.
- L48 _private prototype_ `void RegisterWithProtocolModule(TArray<FDMXProtocolRegistrationParams>& InOutProtocolRegistrationParamsArray);` — Registers the Art-Net implementation here with the Protocol Module
- L60 _private prototype_ `static void SendDMXCommandHandler(const TArray<FString>& Args);` — Sending DMX through console command Command structure is DMX.ArtNet.SendDMX [UniverseID] Channel:Value Channel:Value Channel:Value ... Example: DMX.ArtNet.SendDMX 17 10:6 11:7 12:8 13:9 It will send the DMX to Universe 17. It could be any value from 0 to 32767 And it update the channels values for channel 10, 11, 12, 13 with values 6, 7, 8, 9 Channel could be any value from 0 to 511 Value could be any value from 0 to 255
- L68 _private prototype_ `static void ResetDMXSendUniverseHandler(const TArray<FString>& Args);` — Reset DMX through console command Command structure is DMX.ArtNet.ResetDMXSend [UniverseID] Example: DMX.ArtNet.ResetDMXSend 7
- L72 _private member_ `static FAutoConsoleCommand SendDMXCommand;` — Command for sending DMX through the console
- L75 _private member_ `static FAutoConsoleCommand ResetDMXSendUniverseCommand;` — Command for reset DMX universe through the console
