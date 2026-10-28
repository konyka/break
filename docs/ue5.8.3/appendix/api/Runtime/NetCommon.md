# Runtime / NetCommon

- module root: `Source/Runtime/Net/Common`
- headers: 3; symbols: 95
- symbol kinds: class=1, enum=3, enumerator=59, function=7, member=17, namespace=3, struct=5
- PublicDependencyModuleNames: Core

### `Source/Runtime/Net/Common/Public/Net/Common/Packets/PacketTraits.h` (Public)


#### struct `FOutPacketTraits`  
`struct FOutPacketTraits`  
_L20-41_
- desc: Contains metadata and flags, which provide information on the traits of a packet - what it contains and how to process it.
- L25 _public member_ `bool bAllowCompression = true;` — Whether or not the packet can/should be compressed
- L31 _public member_ `uint32 NumAckBits = 0;` — The number of ack bits in the packet - reflecting UNetConnection.NumAckBits
- L34 _public member_ `uint32 NumBunchBits = 0;` — The number of bunch bits in the packet - reflecting UNetConnection.NumBunchBits
- L37 _public member_ `bool bIsKeepAlive = false;` — Whether or not this is a keepalive packet
- L40 _public member_ `bool bIsCompressed = false;` — Whether or not the packet has been compressed

#### struct `FInPacketTraits`  
`struct FInPacketTraits`  
_L46-58_
- desc: Contains metadata and flags, which provide information on the traits of a packet - what it contains and how to process it.
- L51 _public member_ `bool bConnectionlessPacket = false;` — This packet is not associated with a connection
- L54 _public member_ `bool bFromRecentlyDisconnected = false;` — This is a connectionless packet, from a recently disconnected connection.
- L57 _public member_ `TPimplPtr<UE::Net::FNetResult, EPimplPtrMode::DeepCopy> ExtendedError;` — If there was an error processing the incoming packet, any additional error information is stored here

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Net` (scope `UE`)

### `Source/Runtime/Net/Common/Public/Net/Common/Packets/PacketView.h` (Public)


#### struct `FPacketBufferView`  
`struct FPacketBufferView`  
_L18-28_
- desc: Represents a view of a buffer for storing packets. Buffer contents may be modified, but the allocation can not be resized. Should only be stored as a local variable within functions that handle received packets.
- L21 _public member_ `const TArrayView<uint8> Buffer;` — View of the packet buffer, with Num() representing allocated size. Internal buffer data can be modified, but not view/size.
- L24 _public function_ `FPacketBufferView(uint8* InData, int32 MaxBufferSize) : Buffer(MakeArrayView<uint8>(InData, MaxBufferSize))`

#### enum `ECountUnits::BitType`  
`enum BitType`  
_L32-35_
- L34 _public enumerator_ `Bits`

#### enum `ECountUnits::ByteType`  
`enum ByteType`  
_L37-40_
- L39 _public enumerator_ `Bytes`

#### class `FPacketDataView`  
`class FPacketDataView`  
_L47-105_
- desc: Represent a restricted view of packet data, with bit-based size, allowing data to be reassigned to point elsewhere, but not allowing the data being pointed to, to be modified.
- L53 _private member_ `TArrayView<const uint8> Data;` — View of the raw packet data
- L56 _private member_ `int32 CountBits;` — The size of the data in bits
- L66 _public function_ `FPacketDataView(const uint8* InData, int32 InCountBits, ECountUnits::BitType) : Data(MakeArrayView(InData, FMath::DivideAndRoundUp(InCountBits, 8))) , CountBits(InCountBits)` — Constructs a view of packet data with bit-based size. @param InData		Pointer to the packet data @param InCountBits	The packet size, in bits @param CountUnits	Whether or not the size is specified in bits (ECountUnits::Bits) or bytes (ECountUnits::Bytes)
- L79 _public function_ `FPacketDataView(const uint8* InData, int32 InCountBytes, ECountUnits::ByteType) : Data(MakeArrayView(InData, InCountBytes)) , CountBits(InCountBytes * 8)` — Constructs a view of packet data with byte-based size. @param InData		Pointer to the packet data @param InCountBytes	The packet size, in bytes @param CountUnits	Whether or not the size is specified in bits (ECountUnits::Bits) or bytes (ECountUnits::Bytes)
- L85 _public function_ `const uint8* GetData() const`
- L91 _public function_ `uint8* GetMutableData() const` — @todo: Remove this when the PacketHandler code is updated
- L96 _public function_ `int32 NumBits() const`
- L101 _public function_ `int32 NumBytes() const`

#### struct `FReceivedPacketView`  
`struct FReceivedPacketView`  
_L112-129_
- desc: Represents a view of a received packet, which may be modified to update Data it points to and Data size, as a packet is processed. Should only be stored as a local variable within functions that handle received packets.
- L115 _public member_ `FPacketDataView DataView = {nullptr, 0, ECountUnits::Bits};` — View of packet data - can reassign to point elsewhere, but don't use to modify packet data
- L119 _public member_ `TArrayView<const uint8>& Data = DataView.Data;` — `UE_DEPRECATED(4.26, "Data is deprecated, use DataView instead")` — @todo: When removing deprecation, remove FReceivedPacketView's friend access to FPacketDataView
- L122 _public member_ `TSharedPtr<const FInternetAddr> Address;` — Receive address for the packet
- L125 _public member_ `ESocketErrors Error;` — Error if receiving a packet failed
- L128 _public member_ `FInPacketTraits Traits;` — Metadata and flags for the received packet, indicating what it contains and how to process it

#### struct `FPacketTimestamp`  
`struct FPacketTimestamp`  
_L134-138_
- desc: Stores a platform-specific timestamp for a packet. Can be translated for local use by ISocketSubsystem::TranslatePacketTimestamp.
- L137 _public member_ `FTimespan Timestamp;` — The internal platform specific timestamp (does NOT correspond to FPlatformTime::Seconds, may use a different clock source).

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace ECountUnits`

### `Source/Runtime/Net/Common/Public/Net/Common/Sockets/SocketErrors.h` (Public)


#### enum `ESocketErrors`  
`enum ESocketErrors`  
_L8-69_
- desc: All supported error types by the engine, mapped from platform specific values
- L10 _public enumerator_ `SE_NO_ERROR`
- L11 _public enumerator_ `SE_EINTR`
- L12 _public enumerator_ `SE_EBADF`
- L13 _public enumerator_ `SE_EACCES`
- L14 _public enumerator_ `SE_EFAULT`
- L15 _public enumerator_ `SE_EINVAL`
- L16 _public enumerator_ `SE_EMFILE`
- L17 _public enumerator_ `SE_EWOULDBLOCK`
- L18 _public enumerator_ `SE_EINPROGRESS`
- L19 _public enumerator_ `SE_EALREADY`
- L20 _public enumerator_ `SE_ENOTSOCK`
- L21 _public enumerator_ `SE_EDESTADDRREQ`
- L22 _public enumerator_ `SE_EMSGSIZE`
- L23 _public enumerator_ `SE_EPROTOTYPE`
- L24 _public enumerator_ `SE_ENOPROTOOPT`
- L25 _public enumerator_ `SE_EPROTONOSUPPORT`
- L26 _public enumerator_ `SE_ESOCKTNOSUPPORT`
- L27 _public enumerator_ `SE_EOPNOTSUPP`
- L28 _public enumerator_ `SE_EPFNOSUPPORT`
- L29 _public enumerator_ `SE_EAFNOSUPPORT`
- L30 _public enumerator_ `SE_EADDRINUSE`
- L31 _public enumerator_ `SE_EADDRNOTAVAIL`
- L32 _public enumerator_ `SE_ENETDOWN`
- L33 _public enumerator_ `SE_ENETUNREACH`
- L34 _public enumerator_ `SE_ENETRESET`
- L35 _public enumerator_ `SE_ECONNABORTED`
- L36 _public enumerator_ `SE_ECONNRESET`
- L37 _public enumerator_ `SE_ENOBUFS`
- L38 _public enumerator_ `SE_EISCONN`
- L39 _public enumerator_ `SE_ENOTCONN`
- L40 _public enumerator_ `SE_ESHUTDOWN`
- L41 _public enumerator_ `SE_ETOOMANYREFS`
- L42 _public enumerator_ `SE_ETIMEDOUT`
- L43 _public enumerator_ `SE_ECONNREFUSED`
- L44 _public enumerator_ `SE_ELOOP`
- L45 _public enumerator_ `SE_ENAMETOOLONG`
- L46 _public enumerator_ `SE_EHOSTDOWN`
- L47 _public enumerator_ `SE_EHOSTUNREACH`
- L48 _public enumerator_ `SE_ENOTEMPTY`
- L49 _public enumerator_ `SE_EPROCLIM`
- L50 _public enumerator_ `SE_EUSERS`
- L51 _public enumerator_ `SE_EDQUOT`
- L52 _public enumerator_ `SE_ESTALE`
- L53 _public enumerator_ `SE_EREMOTE`
- L54 _public enumerator_ `SE_EDISCON`
- L55 _public enumerator_ `SE_SYSNOTREADY`
- L56 _public enumerator_ `SE_VERNOTSUPPORTED`
- L57 _public enumerator_ `SE_NOTINITIALISED`
- L58 _public enumerator_ `SE_HOST_NOT_FOUND`
- L59 _public enumerator_ `SE_TRY_AGAIN`
- L60 _public enumerator_ `SE_NO_RECOVERY`
- L61 _public enumerator_ `SE_NO_DATA`
- L62 _public enumerator_ `SE_UDP_ERR_PORT_UNREACH`
- L63 _public enumerator_ `SE_ADDRFAMILY`
- L64 _public enumerator_ `SE_SYSTEM`
- L65 _public enumerator_ `SE_NODEV`
- L68 _public enumerator_ `SE_GET_LAST_ERROR_CODE` — this is a special error which means to lookup the most recent error (via GetLastErrorCode())
