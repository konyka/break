# Plugins / UdpMessaging

- module root: `Plugins/Messaging/UdpMessaging/Source/UdpMessaging`
- headers: 25; symbols: 829
- symbol kinds: class=20, delegate=9, enum=7, enumerator=39, function=147, macro=14, member=304, namespace=24, prototype=228, struct=27, typedef=7, variable=3
- DynamicallyLoadedModuleNames: Settings
- PrivateDependencyModuleNames: ApplicationCore, Cbor, CoreUObject, EditorStyle, Engine, InputCore, Json, Messaging, Projects, PropertyEditor, Serialization, Slate, SlateCore, Sockets, TraceLog, UnrealEd
- PrivateIncludePathModuleNames: MessagingCommon, Settings
- PublicDependencyModuleNames: AtomicQueue, Core, Networking

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Internal/Trace/UdpMessagingTrace.h` (Internal)


#### enum `UE::UdpMessaging::Trace::EUdpMessageLifecycleEvent`  
`enum class EUdpMessageLifecycleEvent : uint8`  
_L24-43_
- L27 _public enumerator_ `EnqueueOutbound` — Send lifecycle
- L28 _public enumerator_ `BeginSerialize`
- L29 _public enumerator_ `EndSerialize`
- L30 _public enumerator_ `ConsumeOutbound`
- L31 _public enumerator_ `Complete`
- L34 _public enumerator_ `FirstSegmentEnqueueInbound` — Receive lifecycle
- L35 _public enumerator_ `BeginReassembly`
- L36 _public enumerator_ `EndReassembly`
- L37 _public enumerator_ `PendingDelivery`
- L38 _public enumerator_ `BeginDeserialize`
- L39 _public enumerator_ `Delivered`
- L42 _public enumerator_ `Discarded` — Exceptional (send or receive)

#### Free symbols / members of external scopes

- L18 _macro_ `# define UDPMESSAGINGTRACE_ENABLED MESSAGINGTRACE_ENABLED`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UdpMessaging` (scope `UE`)
- L22 _namespace_ `namespace Trace` (scope `UE::UdpMessaging`)
- L45 _prototype_ `const TCHAR* LexToString(EUdpMessageLifecycleEvent InEvent);` (scope `UE::UdpMessaging::Trace`)
- L52 _namespace_ `namespace UE`
- L52 _namespace_ `namespace UdpMessaging` (scope `UE`)
- L52 _namespace_ `namespace Trace` (scope `UE::UdpMessaging`)
- L54 _prototype_ `void OutputDiscoveredNode(uint16 ShortId, uint16 DiscoveredByShortId, const FGuid& NodeId, const FIPv4Endpoint& Endpoint, uint8 ProtocolVersion);` (scope `UE::UdpMessaging::Trace`)
- L56 _prototype_ `void OutputMessageSummary(uint16 SenderShortId, uint16 RecipientShortId, uint32 MessageId, uint64 Size, uint32 NumSegments, EMessageFlags Flags);` (scope `UE::UdpMessaging::Trace`)
- L57 _prototype_ `void OutputMessageTypeInfo(uint16 SenderShortId, uint16 RecipientShortId, uint32 MessageId, const TVariant<FName, FTopLevelAssetPath>& TypeInfo);` (scope `UE::UdpMessaging::Trace`)
- L58 _prototype_ `void OutputMessageLifecycle(uint64 Cycle, uint16 SenderShortId, uint16 RecipientShortId, uint32 MessageId, EUdpMessageLifecycleEvent Event);` (scope `UE::UdpMessaging::Trace`)
- L62 _macro_ `#define TRACE_UDPMESSAGING_DISCOVERED_NODE(ShortId, DiscoveredByShortId, NodeId, Endpoint, ProtocolVersion) \`
- L65 _macro_ `#define TRACE_UDPMESSAGING_MESSAGE_SUMMARY(SenderShortId, RecipientShortId, MessageId, Size, NumSegments, Flags) \`
- L68 _macro_ `#define TRACE_UDPMESSAGING_MESSAGE_TYPEINFO(SenderShortId, RecipientShortId, MessageId, TypeInfo) \`
- L71 _macro_ `#define TRACE_UDPMESSAGING_MESSAGE_LIFECYCLE(Cycle, SenderShortId, RecipientShortId, MessageId, Event) \`
- L78 _macro_ `#define TRACE_UDPMESSAGING_DISCOVERED_NODE(...)`
- L79 _macro_ `#define TRACE_UDPMESSAGING_MESSAGE_SUMMARY(...)`
- L80 _macro_ `#define TRACE_UDPMESSAGING_MESSAGE_TYPEINFO(...)`
- L81 _macro_ `#define TRACE_UDPMESSAGING_MESSAGE_LIFECYCLE(...)`

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Customization/SIpAddressComboBox.h` (Private)


#### class `SIpAddressComboBox`  
`class SIpAddressComboBox : public SCompoundWidget`  
_L16-50_
- inherits: `SCompoundWidget`
- L20 _public function_ `DECLARE_DELEGATE_OneParam(FOnChooseIP, FString) SLATE_BEGIN_ARGS(SIpAddressComboBox)`
- L24 _public prototype_ `SLATE_ARGUMENT(FString, InitialValue) SLATE_EVENT(FOnChooseIP, OnIPAddressSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L32 _private member_ `TArray<TSharedPtr<FString>> LocalAdapterAddressSource;`
- L34 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> LocalAdapterAddressComboBox;`
- L37 _private member_ `TSharedPtr<SEditableText> IPAddressEditableTextBlock;` — Text box shown on top of the local adapter address address combo box
- L40 _private member_ `FOnChooseIP OnIPAddressSelectedDelegate;` — Delegate executed when a local IP address was selected
- L43 _private prototype_ `void OnIpAddressSelected(TSharedPtr<FString> InAddress, ESelectInfo::Type InType);` — Handles changes in the local adapter address combo box
- L46 _private prototype_ `void OnIPAddressTextCommmited(const FText&, ETextCommit::Type);` — Called when the IP Address was commited in the editable text block
- L49 _private prototype_ `TSharedRef<SWidget> GenerateLocalAdapterAddressComboBoxEntry(TSharedPtr<FString> InAddress);` — Generates an entry in the local adapter address combo box

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ESelectInfo`
- L11 _namespace_ `namespace ETextCommit`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnChooseIP, FString) SLATE_BEGIN_ARGS(SIpAddressComboBox) {} SLATE_ARGUMENT(FString, InitialValue) SLATE_EVENT(FOnChooseIP, OnIPAddressSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Customization/UdpSettingsDetailsCustomization.h` (Private)


#### class `FUdpSettingsDetailsCustomization`  
`class FUdpSettingsDetailsCustomization : public IDetailCustomization`  
_L10-23_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L22 _private prototype_ `void CustomizeStringAsIpDropDown(const FString& InitialValue, TSharedPtr<IPropertyHandle> PropertyHandle, IDetailLayoutBuilder& DetailBuilder);`

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Shared/SocketSender.h` (Private)


#### class `UE::UdpMessaging::FSocketSender`  
`class FSocketSender : public FRunnable , private FSingleThreadRunnable`  
_L26-185_
- inherits: `FRunnable,FSingleThreadRunnable`
- desc: Asynchronously sends data to a UDP socket.
- L91 _public prototype_ `FSocketSender(FSocket* InSocket, const TCHAR* InDescription, const FOptions& InOptions = FOptions());` — Creates and initializes a new socket sender. @param InSocket The UDP socket to use for sending data. @param InDescription The description text (for debugging). @param InOptions Other configuration.
- L94 _public prototype_ `virtual ~FSocketSender();` — Virtual destructor.
- L105 _public prototype_ `bool Send( const TSharedRef<TArray<uint8>>& InData, const FIPv4Endpoint& InRecipient, bool bAllowSegmentation = false, bool bHighPriority = false );` — Sends data to the specified recipient. @param InData The data to send. @param InRecipient The recipient. @param bAllowSegmentation Pass true if you are intentionally sending more than `GetSegmentOffloadSize()` bytes. @param bHighPriority Packets in this queue are always sent first. @return true if the data will be sent, false otherwise.
- L113 _public function_ `const TSharedRef<FInternetAddr>& GetAddress() const` — Get the address to which this socket is bound.
- L116 _public function_ `uint16 GetSegmentOffloadSize() const` — If send segmentation offload is enabled, returns the max datagram payload. Otherwise 0.
- L119 _public function_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override`
- L124 _public function_ `virtual bool Init() override`
- L129 _public prototype_ `virtual uint32 Run() override;`
- L130 _public prototype_ `virtual void Stop() override;`
- L131 _public function_ `virtual void Exit() override`
- L134 _public function_ `virtual void Tick() override`
- L145 _protected prototype_ `EUpdateResult Update(const FTimespan& InSocketWaitTime);` — Update this socket sender. @param InSocketWaitTime Time to wait for socket write conditions.
- L147 _protected prototype_ `void TryEnableSegmentationOffload(uint16 InSegmentOffloadSize);`
- L151 _private member_ `TMpscQueue<FPacket> SendQueue;` — The send queue.
- L154 _private member_ `TMpscQueue<FPacket> PrioritySendQueue;` — High-priority send queue.
- L157 _private member_ `FSocket* Socket;` — The network socket.
- L160 _private member_ `ISocketSubsystem* SocketSubsystem;` — Cached pointer to the platform socket subsystem.
- L163 _private member_ `TSharedRef<FInternetAddr> SocketAddr;` — Cached socket binding address.
- L166 _private member_ `std::atomic<bool> bStopping;` — Flag indicating that the thread is stopping.
- L169 _private member_ `FRunnableThread* Thread;` — The thread object.
- L172 _private member_ `FTimespan WaitTime;` — Maximum time to wait for the socket to be ready to send.
- L175 _private member_ `FEvent* WorkEvent;` — An event signaling that outbound messages need to be processed.
- L178 _private member_ `FString Description;` — Description of this sender (for debugging).
- L181 _private member_ `uint16 SegmentOffloadSize;` — Datagram payload size for segmentation offload. 0 means disabled or unsupported.
- L184 _private member_ `FLockFreeTokenBucket TokenBucket;` — Token bucket for egress shaping.

#### struct `UE::UdpMessaging::FSocketSender::FPacket`  
`struct FPacket`  
_L31-47_
- desc: Structure for outbound packets.
- L34 _public member_ `TSharedPtr<TArray<uint8>> Data;` — Holds the packet's data.
- L37 _public member_ `FIPv4Endpoint Recipient;` — Holds the recipient.
- L40 _public function_ `FPacket()` — Default constructor.
- L43 _public function_ `FPacket(const TSharedRef<TArray<uint8>>& InData, const FIPv4Endpoint& InRecipient) : Data(InData) , Recipient(InRecipient)` — Creates and initializes a new instance.

#### enum `UE::UdpMessaging::FSocketSender::EUpdateResult`  
`enum class EUpdateResult`  
_L49-59_
- L52 _public enumerator_ `Done` — The queued was emptied, and we can await new work.
- L55 _public enumerator_ `Retry` — There was a transient failure, and we should attempt to service the queue again soon.
- L58 _public enumerator_ `Fatal` — Tear down this FSocketSender and percolate the failure to the caller.

#### struct `UE::UdpMessaging::FSocketSender::FOptions`  
`struct FOptions`  
_L62-82_
- L64 _public member_ `int32 SendBufferSize = 512 * 1024;`
- L65 _public member_ `FTimespan WaitTime = FTimespan::FromMilliseconds(100);`
- L68 _public member_ `uint16 SegmentOffloadSize = 0;` — Datagram payload size for UDP segmentation offload; 0 disables USO. Ignored if unsupported.
- L71 _public member_ `int64 BytesPerSec = 100 * 1024 * 1024;` — Token bucket: steady state send bytes per second / replenishment rate.
- L74 _public member_ `int64 MaxBurstBytes = 10 * 1024 * 1024;` — Token bucket: max bucket reserve capacity.
- L76 _public function_ `FOptions()`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace UdpMessaging` (scope `UE`)

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Shared/TokenBucket.h` (Private)


#### class `UE::UdpMessaging::FLockFreeTokenBucket`  
`class FLockFreeTokenBucket`  
_L14-78_
- L17 _public function_ `FLockFreeTokenBucket(int64 InTokensPerSec, int64 InMaxBurstTokens) : TokensPerSec(InTokensPerSec) , MaxBurstTokens(InMaxBurstTokens)`
- L27 _public function_ `int64 Max() const`
- L32 _public function_ `bool TryConsume(int64 InConsumeTokens)`
- L62 _public function_ `void Credit(int64 InCreditTokens)`
- L73 _private member_ `const int64 TokensPerSec;`
- L74 _private member_ `const int64 MaxBurstTokens;`
- L77 _private member_ `std::atomic<int64> FullAtTimeCycles;` — A single atomic value that represents the current state. If <= now, the bucket is full.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UdpMessaging` (scope `UE`)

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Shared/UdpMessageSegment.h` (Private)


#### enum `EUdpMessageSegments`  
`enum class EUdpMessageSegments : uint8`  
_L14-53_
- desc: Enumerates message segment types.
- L17 _public enumerator_ `None` — None.
- L20 _public enumerator_ `Abort` — Request to abort the sending of a message.
- L23 _public enumerator_ `Acknowledge` — Acknowledges that the message was received successfully.
- L26 _public enumerator_ `Bye` — Notifies the bus that an endpoint has left.
- L29 _public enumerator_ `Data` — A message data segment.
- L32 _public enumerator_ `Hello` — Notifies the bus that an endpoint has joined.
- L35 _public enumerator_ `Retransmit` — Request to retransmit selected data segments.
- L38 _public enumerator_ `Timeout` — Notification that an inbound message timed out.
- L41 _public enumerator_ `AcknowledgeSegments` — Acknowledges that message segments were received successfully
- L44 _public enumerator_ `Ping` — Announces existence to static endpoints.
- L47 _public enumerator_ `Pong` — Answers back to ping segment.
- L50 _public enumerator_ `Mesh` — Used to share endpoints for fully meshing networks.

#### struct `FUdpMessageSegment::FHeader`  
`struct FHeader`  
_L61-99_
- desc: Structure for the header of all segments.
- L64 _public member_ `uint8 ProtocolVersion;` — Holds the protocol version.
- L67 _public member_ `FGuid RecipientNodeId;` — Holds the recipient's node identifier (empty = multicast).
- L70 _public member_ `FGuid SenderNodeId;` — Holds the sender's node identifier.
- L77 _public member_ `EUdpMessageSegments SegmentType;` — Holds the segment type. @see EUdpMessageSegments
- L79 _public member_ `static constexpr uint32 SerializedBytes = ( sizeof(ProtocolVersion) + sizeof(RecipientNodeId) + sizeof(SenderNodeId) + sizeof(SegmentType) );`

#### struct `FUdpMessageSegment::FAbortChunk`  
`struct FAbortChunk`  
_L104-121_
- desc: Structure for the sub-header of Abort segments.
- L107 _public member_ `int32 MessageId;` — Holds the identifier of the message to abort.
- L117 _public function_ `void Serialize(FArchive& Ar, uint8 )` — Serializes the given header from or to the specified archive for the specified version. @param Ar The archive to serialize from or into. @param ProtocolVersion The protocol version we want to serialize the Chunk in.

#### struct `FUdpMessageSegment::FAcknowledgeChunk`  
`struct FAcknowledgeChunk`  
_L127-143_
- desc: Structure for the header of Acknowledge segments.
- L130 _public member_ `int32 MessageId;` — Holds the identifier of the message that was received successfully.
- L139 _public function_ `void Serialize(FArchive& Ar, uint8 )` — Serializes the given header from or to the specified archive for the specified version. @param Ar The archive to serialize from or into. @param ProtocolVersion The protocol version we want to serialize the Chunk in.

#### struct `FUdpMessageSegment::FAcknowledgeSegmentsChunk`  
`struct FAcknowledgeSegmentsChunk`  
_L149-226_
- desc: Structure for the header of AcknowledgeSegments segments.
- L187 _public member_ `int32 MessageId;` — Holds the identifier of the message that received segments successfully.
- L190 _public member_ `TArray<uint32> Segments;` — List of Acknowledged segments
- L192 _public member_ `static constexpr uint32 FixedSerializedBytes = ( sizeof(MessageId) + sizeof(decltype(Segments)::SizeType) );`
- L198 _public prototype_ `FAcknowledgeSegmentsChunk() = default;`
- L200 _public function_ `FAcknowledgeSegmentsChunk(int32 InMessageId, TArray<uint32>&& InSegments) : MessageId(InMessageId) , Segments(MoveTemp(InSegments))`
- L211 _public function_ `void Serialize(FArchive& Ar, uint8 ProtocolVersion)` — Serializes the given header from or to the specified archive for the specified version. @param Ar The archive to serialize from or into. @param ProtocolVersion The protocol version we want to serialize the Chunk in.

#### struct `FUdpMessageSegment::FAcknowledgeSegmentsChunk::FV10_11`  
`struct FV10_11`  
_L153-183_
- desc: Previous version serialization struct
- L155 _public member_ `int32 MessageId;`
- L156 _public member_ `TArray<uint16> Segments;`
- L157 _public member_ `FAcknowledgeSegmentsChunk& Chunk;` — Reference for loading
- L159 _public function_ `FV10_11(FAcknowledgeSegmentsChunk& InChunk) : MessageId(InChunk.MessageId) , Chunk(InChunk)`
- L169 _public function_ `void Serialize(FArchive& Ar, uint8)`

#### struct `FUdpMessageSegment::FDataChunk`  
`struct FDataChunk`  
_L232-353_
- desc: Structure for the header of Data segments.
- L289 _public member_ `int32 MessageId;` — Holds the identifier of the message that the data belongs to.
- L292 _public member_ `int64 MessageSize;` — Holds the total size of the message.
- L295 _public member_ `EMessageFlags MessageFlags;` — Holds the message flags.
- L298 _public member_ `uint32 SegmentNumber;` — Holds the sequence number of this segment.
- L301 _public member_ `uint64 SegmentOffset;` — Holds the segment's offset within the message.
- L304 _public member_ `uint32 TotalSegments;` — Holds the total number of data segments being sent.
- L307 _public member_ `uint64 Sequence;` — Holds the message sequence number (0 = not sequential).
- L310 _public member_ `TArray<uint8> Data;` — Holds the segment data.
- L312 _public member_ `static constexpr uint32 FixedSerializedBytes = ( sizeof(MessageId) + sizeof(MessageSize) + sizeof(MessageFlags) + sizeof(SegmentNumber) + sizeof(SegmentOffset) + sizeof(TotalSegments) + sizeof(Sequence) + sizeof(decltype(Data)::SizeType) );`
- L324 _public prototype_ `FDataChunk() = default;`
- L332 _public function_ `void Serialize(FArchive& Ar, uint8 ProtocolVersion)` — Serializes the given header from or to the specified archive for the specified version. @param Ar The archive to serialize from or into. @param ProtocolVersion The protocol version we want to serialize the Chunk in.

#### struct `FUdpMessageSegment::FDataChunk::FV10_11`  
`struct FV10_11`  
_L236-285_
- desc: Previous version serialization struct
- L238 _public member_ `int32 MessageId;`
- L239 _public member_ `int32 MessageSize;`
- L240 _public member_ `uint16 SegmentNumber;`
- L241 _public member_ `uint32 SegmentOffset;`
- L242 _public member_ `uint64 Sequence;`
- L243 _public member_ `uint16 TotalSegments;`
- L245 _public member_ `EMessageFlags MessageFlags;` — TArray<uint8> Data;		// Taken from the actual chunk, listed here for reference
- L246 _public member_ `FDataChunk& Chunk;` — Reference for loading
- L249 _public function_ `FV10_11(FDataChunk& InChunk) : MessageId(InChunk.MessageId) , MessageSize((int32)InChunk.MessageSize) , SegmentNumber((uint16)InChunk.SegmentNumber) , SegmentOffset((uint32)InChunk.SegmentOffset) , Sequence(InChunk.Sequence) , TotalSegments((uint16)InChunk.TotalSegments) , MessageFlags(InChunk.MessageFlags) , Chunk(InChunk)`
- L260 _public function_ `void Serialize(FArchive& Ar, uint8 ProtocolVersion)`

#### struct `FUdpMessageSegment::FRetransmitChunk`  
`struct FRetransmitChunk`  
_L363-390_
- desc: Structure for the sub-header of Retransmit segments. Retransmit segments are sent from a message recipient to a message sender in order to indicate that selected message segments are to be retransmitted, i.e. if they got lost on the network or if the recipient was unable to handle them previously.
- L366 _public member_ `int32 MessageId;` — Holds the identifier of the message for which data needs to be retransmitted.
- L369 _public member_ `TArray<uint16> Segments;` — Holds the list of data segments that need to be retransmitted.
- L379 _public function_ `void Serialize(FArchive& Ar, uint8 )` — Serializes the given header from or to the specified archive for the specified version. @param Ar The archive to serialize from or into. @param ProtocolVersion The protocol version we want to serialize the Chunk in.
- L384 _public function_ `int32 GetMessageId(FArchive& Ar)`

#### struct `FUdpMessageSegment::FTimeoutChunk`  
`struct FTimeoutChunk`  
_L396-413_
- desc: Structure for the header of Timeout packets.
- L399 _public member_ `int32 MessageId;` — Holds the identifier of the message that timed out.
- L409 _public function_ `void Serialize(FArchive& Ar, uint8 )` — Serializes the given header from or to the specified archive for the specified version. @param Ar The archive to serialize from or into. @param ProtocolVersion The protocol version we want to serialize the Chunk in.

#### Free symbols / members of external scopes

- L56 _namespace_ `namespace FUdpMessageSegment`
- L95 _function_ `friend FArchive& operator<<(FArchive& Ar, FHeader& Header)` (scope `FUdpMessageSegment`) — Serializes the given header from or into the specified archive. @param Ar The archive to serialize from or into. @param Header The header to serialize. @return The archive.
- L164 _function_ `` (scope `FUdpMessageSegment::FAcknowledgeSegmentsChunk::FV10_11::FV10_11`)
- L178 _function_ `` (scope `FUdpMessageSegment::FAcknowledgeSegmentsChunk::FV10_11::Serialize`)

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Shared/UdpMessagingTime.h` (Private)


#### struct `FUdpMessagingTime`  
`struct FUdpMessagingTime`  
_L11-58_
- desc: Thin wrapper to help migrate from FDateTime to FPlatformTime for relative measurements.
- L13 _public member_ `int64 Cycles = 0;`
- L15 _public function_ `static FUdpMessagingTime Now()`
- L20 _public function_ `FDateTime EstimatedLocalDateTime() const`
- L27 _public function_ `FTimespan operator-(FUdpMessagingTime Other) const`
- L32 _public prototype_ `auto operator+(FUdpMessagingTime Other) const = delete;`
- L33 _public prototype_ `auto operator+=(FUdpMessagingTime Other) const = delete;`
- L35 _public function_ `FUdpMessagingTime operator-(FTimespan Other) const`
- L41 _public function_ `FUdpMessagingTime operator+(FTimespan Other) const`
- L51 _public function_ `bool operator==(FUdpMessagingTime Other) const`
- L52 _public function_ `bool operator!=(FUdpMessagingTime Other) const`
- L53 _public function_ `bool operator>(FUdpMessagingTime Other) const`
- L54 _public function_ `bool operator>=(FUdpMessagingTime Other) const`
- L55 _public function_ `bool operator<(FUdpMessagingTime Other) const`
- L56 _public function_ `bool operator<=(FUdpMessagingTime Other) const`

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Transport/UdpCircularQueue.h` (Private)


#### class `TUdpCircularQueue`  
`template<typename ElementType> class TUdpCircularQueue`  
_L17-224_
- desc: Implements a first-in first-out queue using a circular array. This class is not thread safe and should be used  only in single-producer single-consumer scenarios. The number of items that can be enqueued is one less than the queue's capacity, because one item will be used for detecting full and empty states. @param ElementType The type of elements held in the queue.
- L26 _public function_ `explicit TUdpCircularQueue(uint32 CapacityPlusOne) : Buffer(CapacityPlusOne) , Head(0) , Tail(0)` — Constructor. @param CapacityPlusOne The number of elements that the queue can hold (will be rounded up to the next power of 2).
- L42 _public function_ `uint32 Count() const` — Gets the number of elements in the queue. Can be called from any thread. The result reflects the calling thread's current view. Since no locking is used, different threads may return different results. @return Number of queued elements.
- L60 _public function_ `bool Dequeue(ElementType& OutElement)` — Removes an item from the front of the queue. @param OutElement Will contain the element if the queue is not empty. @return true if an element has been returned, false if the queue was empty.
- L80 _public function_ `bool Dequeue()` — Removes an item from the front of the queue. @return true if an element has been removed, false if the queue was empty.
- L99 _public function_ `void Empty()` — Empties the queue. @see IsEmpty
- L110 _public function_ `bool Enqueue(const ElementType& Element)` — Adds an item to the end of the queue. @param Element The element to add. @return true if the item was added, false if the queue was full.
- L132 _public function_ `bool Enqueue(ElementType&& Element)` — Adds an item to the end of the queue. @param Element The element to add. @return true if the item was added, false if the queue was full.
- L157 _public function_ `FORCEINLINE bool IsEmpty() const` — Checks whether the queue is empty. Can be called from any thread. The result reflects the calling thread's current view. Since no locking is used, different threads may return different results. @return true if the queue is empty, false otherwise. @see Empty, IsFull
- L171 _public function_ `bool IsFull() const` — Checks whether the queue is full. Can be called from any thread. The result reflects the calling thread's current view. Since no locking is used, different threads may return different results. @return true if the queue is full, false otherwise. @see IsEmpty
- L182 _public function_ `bool Peek(ElementType& OutItem) const` — Returns the oldest item in the queue without removing it. @param OutItem Will contain the item if the queue is not empty. @return true if an item has been returned, false if the queue was empty.
- L202 _public function_ `const ElementType* Peek() const` — Returns the oldest item in the queue without removing it. @return an ElementType pointer if an item has been returned, nullptr if the queue was empty. @note The return value is only valid until Dequeue, Empty, or the destructor has been called.
- L217 _private member_ `TCircularBuffer<ElementType> Buffer;` — Holds the buffer.
- L220 _private member_ `uint32 Head;` — Holds the index to the first item in the buffer.
- L223 _private member_ `uint32 Tail;` — Holds the index to the last item in the buffer.

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Transport/UdpDeserializedMessage.h` (Private)


#### class `FUdpDeserializedMessage`  
`class FUdpDeserializedMessage : public IMessageContext`  
_L19-102_
- inherits: `IMessageContext`
- desc: Holds a deserialized message.
- L29 _public prototype_ `FUdpDeserializedMessage(const TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe>& InAttachment);` — Creates and initializes a new instance. @param InAttachment An optional message attachment.
- L42 _public prototype_ `bool Deserialize(const FUdpReassembledMessage& ReassembledMessage);` — Deserializes the given reassembled message. @param ReassembledMessage The reassembled message to deserialize. @return true on success, false otherwise.
- L47 _public prototype_ `static FNameOrFTopLevel PeekMessageTypeInfoName(const FUdpReassembledMessage& ReassembledMessage);` — Called early by the message processor to peek at the typeinfo name.
- L48 _public prototype_ `static TWeakObjectPtr<UScriptStruct> ResolvePath(const FNameOrFTopLevel& Path);`
- L54 _public prototype_ `virtual const TMap<FName, FString>& GetAnnotations() const override;`
- L55 _public prototype_ `virtual TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> GetAttachment() const override;`
- L56 _public prototype_ `virtual const FDateTime& GetExpiration() const override;`
- L57 _public prototype_ `virtual const void* GetMessage() const override;`
- L58 _public prototype_ `virtual const TWeakObjectPtr<UScriptStruct>& GetMessageTypeInfo() const override;`
- L59 _public prototype_ `virtual TSharedPtr<IMessageContext, ESPMode::ThreadSafe> GetOriginalContext() const override;`
- L60 _public prototype_ `virtual const TArray<FMessageAddress>& GetRecipients() const override;`
- L61 _public prototype_ `virtual EMessageScope GetScope() const override;`
- L62 _public prototype_ `virtual EMessageFlags GetFlags() const override;`
- L64 _public prototype_ `virtual const FMessageAddress& GetSender() const override;`
- L65 _public prototype_ `virtual const FMessageAddress& GetForwarder() const override;`
- L66 _public prototype_ `virtual ENamedThreads::Type GetSenderThread() const override;`
- L67 _public prototype_ `virtual const FDateTime& GetTimeForwarded() const override;`
- L68 _public prototype_ `virtual const FDateTime& GetTimeSent() const override;`
- L74 _private member_ `TMap<FName, FString> Annotations;` — Holds the optional message annotations.
- L77 _private member_ `TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> Attachment;` — Holds a pointer to attached binary data.
- L80 _private member_ `FDateTime Expiration;` — Holds the expiration time.
- L83 _private member_ `void* MessageData;` — Holds the message.
- L86 _private member_ `TArray<FMessageAddress> Recipients;` — Holds the message recipients.
- L89 _private member_ `EMessageScope Scope;` — Holds the message's scope.
- L92 _private member_ `EMessageFlags Flags;` — Holds the message's flags.
- L95 _private member_ `FMessageAddress Sender;` — Holds the sender's identifier.
- L98 _private member_ `FDateTime TimeSent;` — Holds the time at which the message was sent.
- L101 _private member_ `TWeakObjectPtr<UScriptStruct> TypeInfo;` — Holds the message's type information.

#### Free symbols / members of external scopes

- L15 _typedef_ `using FNameOrFTopLevel = TVariant<FName, FTopLevelAssetPath>;`

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Transport/UdpMessageBeacon.h` (Private)


#### class `FUdpMessageBeacon`  
`class FUdpMessageBeacon : public FRunnable , private FSingleThreadRunnable`  
_L25-184_
- inherits: `FRunnable,FSingleThreadRunnable`
- desc: Implements a beacon sender thread.
- L38 _public prototype_ `FUdpMessageBeacon( UE::UdpMessaging::FSocketSender* InSocketSender, const FGuid& InSocketId, const FIPv4Endpoint& InMulticastEndpoint );` — Creates and initializes a new beacon sender. @param InSocketSender The network socket sender used to send Hello segments. @param InSocketId The network socket identifier (used to detect unicast endpoint). @param InMulticastEndpoint The multicast group endpoint to transport messages to.
- L45 _public prototype_ `virtual ~FUdpMessageBeacon();` — Virtual destructor.
- L54 _public function_ `FTimespan GetBeaconInterval()` — Gets the current time interval between Hello segments. @return Beacon interval.
- L64 _public prototype_ `void SetEndpointCount(int32 EndpointCount);` — Sets the number of known IP endpoints. @param EndpointCount The current number of known endpoints.
- L70 _public prototype_ `bool HasSocketError() const;` — Get the socket error flag. @return if there were any socket error
- L76 _public prototype_ `void AddStaticEndpoint(const FIPv4Endpoint& InEndpoint);` — Add a static endpoint to the beacon @param InEndpoint the endpoint to add
- L82 _public prototype_ `void RemoveStaticEndpoint(const FIPv4Endpoint& InEndpoint);` — Remove a static endpoint from the beacon @param InEndpoint the endpoint to remove
- L88 _public prototype_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override;`
- L89 _public prototype_ `virtual bool Init() override;`
- L90 _public prototype_ `virtual uint32 Run() override;`
- L91 _public prototype_ `virtual void Stop() override;`
- L92 _public function_ `virtual void Exit() override`
- L103 _protected prototype_ `bool SendSegment(EUdpMessageSegments SegmentType, const FTimespan& SocketWaitTime);` — Sends the specified segment. @param SegmentType The type of segment to send (Hello or Bye). @param SocketWaitTime Maximum time to wait for the socket to be ready. @return true on success, false otherwise.
- L109 _protected prototype_ `bool SendPing(const FTimespan& SocketWaitTime);` — Sends a ping segment to static addresses. @return true on success, false otherwise.
- L117 _protected prototype_ `void Update(const FDateTime& CurrentTime, const FTimespan& SocketWaitTime);` — Update the beacon sender. @param CurrentTime The current time (in UTC). @param SocketWaitTime Maximum time to wait for the socket to be ready.
- L123 _protected prototype_ `virtual void Tick() override;`
- L127 _private prototype_ `void ProcessStaticEndpointQueue();` — Add pending endpoints to the list of static addresses.
- L130 _private prototype_ `void AddLocalEndpoints();` — Add local static endpoints to discover other processes bound to other local network adapters.
- L133 _private member_ `std::atomic<FTimespan> BeaconInterval;` — Holds the calculated interval between Hello segments.
- L136 _private member_ `FEvent* EndpointLeftEvent;` — Holds an event signaling that an endpoint left.
- L139 _private member_ `int32 LastEndpointCount;` — Holds the number of known endpoints when NextHelloTime was last calculated.
- L142 _private member_ `FDateTime LastHelloSent;` — Holds the time at which the last Hello segment was sent.
- L145 _private member_ `TSharedPtr<FInternetAddr> MulticastAddress;` — Holds the multicast address and port number to send to.
- L155 _private member_ `TSpscQueue<FPendingEndpoint> StaticEndpointQueue;` — Static endpoint queue to add/remove static endpoints.
- L158 _private member_ `TArray<TSharedPtr<FInternetAddr>> StaticAddresses;` — Holds the static addresses to broadcast ping to.
- L161 _private member_ `FDateTime NextHelloTime;` — Holds the time at which the next Hello segment must be sent.
- L164 _private member_ `FGuid NodeId;` — Holds local node identifier.
- L167 _private member_ `UE::UdpMessaging::FSocketSender* SocketSender;` — Holds the socket sender used to send Hello segments.
- L170 _private member_ `bool Stopping;` — Holds a flag indicating that the thread is stopping.
- L173 _private member_ `bool bSocketError;` — Holds a flag indicating if we encountered socket sending error.
- L176 _private member_ `FRunnableThread* Thread;` — Holds the thread object.
- L180 _private member_ `static const FTimespan IntervalPerEndpoint;` — Defines the time interval per endpoint.
- L183 _private member_ `static const FTimespan MinimumInterval;` — Defines the minimum interval for Hello segments.

#### struct `FUdpMessageBeacon::FPendingEndpoint`  
`struct FPendingEndpoint`  
_L148-152_
- desc: Pending static endpoint to send to the beacon.
- L150 _public member_ `FIPv4Endpoint StaticEndpoint;`
- L151 _public member_ `bool bAdd;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UdpMessaging` (scope `UE`)

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Transport/UdpMessageProcessor.h` (Private)


#### struct `FUdpSegmenterStats`  
`struct FUdpSegmenterStats`  
_L50-57_
- desc: Holds the current statistics for a given message segmenter.
- L52 _public member_ `FGuid NodeId;`
- L53 _public member_ `int32 MessageId = 0;`
- L54 _public member_ `uint32 SegmentsSent = 0;`
- L55 _public member_ `uint32 SegmentsAcked = 0;`
- L56 _public member_ `uint32 TotalSegments = 0;`

#### struct `FSentData`  
`struct FSentData`  
_L60-69_
- desc: Information about what was sent over the wire.
- L62 _public member_ `int32 MessageId = 0;`
- L63 _public member_ `uint32 SegmentNumber = 0;`
- L65 _public member_ `uint64 SequenceNumber = 0;`
- L66 _public member_ `bool bIsReliable = false;`
- L68 _public member_ `FUdpMessagingTime TimeSent;`

#### struct `FSegmentSendExpiry`  
`struct FSegmentSendExpiry`  
_L72-77_
- desc: Lightweight tracking of segment transmit times to expedite maintenance of send window.
- L74 _public member_ `FUdpMessagingTime TimeSent;`
- L75 _public member_ `int32 MessageId = 0;`
- L76 _public member_ `uint32 SegmentNumber = 0;`

#### struct `FMessageDeliverExpiry`  
`struct FMessageDeliverExpiry`  
_L80-84_
- desc: Lightweight tracking of message delivery times to prevent double delivery.
- L82 _public member_ `FUdpMessagingTime TimeDelivered;`
- L83 _public member_ `int32 MessageId = 0;`

#### struct `FSentSegmentInfo`  
`struct FSentSegmentInfo`  
_L87-111_
- desc: Returned by the segment processor. It provides details on what was sent and how it was sent.
- L89 _public prototype_ `FSentSegmentInfo() = delete;`
- L90 _public function_ `FSentSegmentInfo(int32 InMessageId) : MessageId(InMessageId)`
- L95 _public member_ `int32 MessageId;`
- L96 _public member_ `uint64 SequenceNumber = 0;`
- L97 _public member_ `uint32 BytesSent = 0;`
- L98 _public member_ `uint32 SegmentsSent = 0;`
- L100 _public member_ `bool bIsReliable = false;`
- L101 _public member_ `bool bRequiresRequeue = false;`
- L102 _public member_ `bool bSendSocketError = false;`
- L103 _public member_ `bool bFullySent = false;`
- L104 _public member_ `bool bIsTraced = false;`
- L105 _public member_ `bool bIsReady = false;`
- L107 _public function_ `bool WasSent() const`

#### class `FUdpMessagingRangeChecklessHeapAllocator`  
`class FUdpMessagingRangeChecklessHeapAllocator : public FHeapAllocator`  
_L132-137_
- inherits: `FHeapAllocator`
- desc: Heap allocator to avoid range checks for performance reasons.

#### enum `FUdpMessagingRangeChecklessHeapAllocator::(anonymous)`  
`enum`  
_L136-136_
- desc: Don't want to lose performance on range checks in performance-critical code.

#### class `FUdpMessageProcessor`  
`class FUdpMessageProcessor : public FRunnable , private FSingleThreadRunnable`  
_L142-1181_
- inherits: `FRunnable,FSingleThreadRunnable`
- desc: Implements a message processor for UDP messages.
- L605 _private prototype_ `bool FillDataChunk(FUdpMessageSegment::FDataChunk& OutDataChunk, FNodeInfo& NodeInfo, TSharedPtr<FUdpMessageSegmenter>& Segmenter, int32 MessageId);`
- L608 _private prototype_ `TSharedPtr<FUdpMessageSegmenter>* GetSegmenter(FNodeInfo& NodeInfo, int32 MessageId);` — Returns the specified segmenter if valid, and attempts to initialize it if necessary.
- L610 _private prototype_ `int32 ClampMaxSegments(int32 MaxSegments, const TSharedPtr<FUdpMessageSegmenter>& Segmenter, const FNodeInfo& NodeInfo) const;`
- L613 _private prototype_ `FSentSegmentInfo SendNextSegmentsForMessageId(FNodeInfo& NodeInfo, FUdpMessageSegment::FHeader& Header, int32 MessageId, int32 MaxSegments = 1);` — Send one or more segments out for the given message id. Send state is provided by the return value.
- L616 _private prototype_ `void RemoveDeadNodes();` — Remove any nodes we have not heard from in a while.
- L619 _private prototype_ `void UpdateNetworkStatistics();` — Update network statistics table that callers can use to gather info about running connections.
- L622 _private prototype_ `void SendSegmenterStatsToListeners(int32 MessageId, FGuid NodeId, const TSharedPtr<FUdpMessageSegmenter>& Segmenter);` — Send a segmenter stats to listeners
- L633 _public prototype_ `FUdpMessageProcessor(FSocket& InSocket, const FGuid& InNodeId, const FIPv4Endpoint& InMulticastEndpoint);` — Creates and initializes a new message processor. @param InSocket The network socket used to transport messages. @param InNodeId The local node identifier (used to detect the unicast endpoint). @param InMulticastEndpoint The multicast group endpoint to transport messages to.
- L636 _public prototype_ `virtual ~FUdpMessageProcessor();` — Virtual destructor.
- L642 _public prototype_ `void AddStaticEndpoint(const FIPv4Endpoint& InEndpoint);` — Add a static endpoint to the processor @param InEndpoint the endpoint to add
- L648 _public prototype_ `void RemoveStaticEndpoint(const FIPv4Endpoint& InEndpoint);` — Remove a static endpoint from the processor @param InEndpoint the endpoint to remove
- L656 _public prototype_ `TMap<uint8, TArray<FGuid>> GetRecipientsPerProtocolVersion(const TArray<FGuid>& Recipients);` — Get a list of Nodes Ids split by supported Protocol version @param Recipients The list of recipients Ids @return A map of protocol version -> list of node ids for that protocol
- L665 _public prototype_ `bool EnqueueInboundSegment(const TSharedPtr<FArrayReader, ESPMode::ThreadSafe>& Data, const FIPv4Endpoint& Sender);` — Queues up an inbound message segment. @param Data The segment data. @param Sender The sender's network endpoint. @return true if the segment was queued up, false otherwise.
- L674 _public prototype_ `bool EnqueueOutboundMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& MessageContext, const TArray<FGuid>& Recipients);` — Queues up an outbound message. @param MessageContext The message to serialize and send. @param Recipients The recipients ids to send to. @return true if the message was queued up, false otherwise.
- L681 _public function_ `const TSharedPtr<FEvent, ESPMode::ThreadSafe>& GetWorkEvent() const` — Get the event used to signal the message processor that work is available. @return The event.
- L690 _public prototype_ `void WaitAsyncTaskCompletion();` — Waits for all serialization tasks fired by this processor to complete. Expected to be called when the application exit to prevent serialized (UStruct) object to being use after the UObject system is shutdown.
- L695 _public prototype_ `FMessageTransportStatistics GetStats(FGuid Node) const;` — Get the current running network statistics for the given node.
- L697 _public function_ `void SetShareKnownNodesState(bool bInShareKnownNodes)`
- L704 _public typedef_ `typedef TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> IMessageAttachmentPtr;` — @todo gmp: remove the need for this typedef
- L711 _public function_ `DECLARE_DELEGATE_ThreeParams(FOnMessageReassembled, FUdpReassembledMessageSharedPtr , const IMessageAttachmentPtr& , const FGuid& ) FOnMessageReassembled& OnMessageReassembled()` — Returns a delegate that is executed when message data has been received. @return The delegate.
- L723 _public function_ `DECLARE_DELEGATE_OneParam(FOnNodeDiscovered, const FGuid& ) FOnNodeDiscovered& OnNodeDiscovered()` — Returns a delegate that is executed when a remote node has been discovered. @return The delegate. @see OnNodeLost
- L735 _public function_ `DECLARE_DELEGATE_OneParam(FOnNodeLost, const FGuid& ) FOnNodeLost& OnNodeLost()` — Returns a delegate that is executed when a remote node was closed or timed out. @return The delegate. @see OnNodeDiscovered
- L747 _public function_ `DECLARE_DELEGATE(FOnError) FOnError& OnError()` — Returns a delegate that is executed when a socket error happened. @return The delegate. @note this delegate is broadcasted from the processor thread.
- L753 _public function_ `void SetEnableMessageDelegates(bool bShouldEnable)`
- L763 _public function_ `DECLARE_TS_MULTICAST_DELEGATE_FourParams(FOnInboundSegment, const FInboundSegment&, const FGuid&, EUdpMessageSegments, bool) FOnInboundSegment& OnInboundSegmentReceived_UdpMessageProcessorThread()` — Inbound segment delegate inspector @return The delegate.
- L775 _public function_ `DECLARE_DELEGATE_TwoParams(FOnErrorSendingToEndpoint, const FGuid& , const FIPv4Endpoint& ) FOnErrorSendingToEndpoint& OnErrorSendingToEndpoint_UdpMessageProcessorThread()` — Returns a delegate that is executed when a socket fails to communicate upon sending to a target endpoint. @return The delegate @note this delegate is broadcasted from the processor thread.
- L787 _public function_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanAcceptEndpoint, const FGuid& , const FIPv4Endpoint& ) FCanAcceptEndpoint& OnCanAcceptEndpoint_UdpMessageProcessorThread()` — Returns a delegate that is executed when a socket fails to communicate upon sending to a target endpoint. @return The delegate @note this delegate is broadcasted from the processor thread.
- L793 _public prototype_ `TArray<FIPv4Endpoint> GetKnownEndpoints() const;`
- L799 _public prototype_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override;`
- L800 _public prototype_ `virtual bool Init() override;`
- L801 _public prototype_ `virtual uint32 Run() override;`
- L802 _public prototype_ `virtual void Stop() override;`
- L803 _public function_ `virtual void Exit() override`
- L814 _protected prototype_ `void AcknowledgeReceipt(int32 MessageId, const FNodeInfo& NodeInfo);` — Acknowledges receipt of a message. @param MessageId The identifier of the message to acknowledge. @param NodeInfo Details for the node to send the acknowledgment to. @todo gmp: batch multiple of these into a single message
- L821 _protected prototype_ `FTimespan CalculateWaitTime() const;` — Calculates the time span that the thread should wait for work. @return Wait time.
- L824 _protected prototype_ `void ConsumeInboundSegments();` — Consumes all inbound segments.
- L827 _protected prototype_ `void ConsumeOutboundMessages();` — Consumes all outbound messages.
- L837 _protected prototype_ `bool FilterSegment(const FUdpMessageSegment::FHeader& Header, const FIPv4Endpoint& Sender);` — Filters the specified message segment. @param Header The segment header. @param Data The segment data. @param Sender The segment sender. @return true if the segment passed the filter, false otherwise.
- L845 _protected prototype_ `void ProcessAbortSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo);` — Processes an Abort segment. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment.
- L853 _protected prototype_ `void ProcessAcknowledgeSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo);` — Processes an Acknowledgement segment. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment.
- L861 _protected prototype_ `void ProcessAcknowledgeSegmentsSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo);` — Processes an AcknowledgmentSegments segment. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment.
- L869 _protected prototype_ `void ProcessByeSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo);` — Processes a Bye segment. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment.
- L877 _protected prototype_ `void ProcessDataSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo);` — Processes a Ping segment. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment.
- L885 _protected prototype_ `void ProcessHelloSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo);` — Processes a Hello segment. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment.
- L893 _protected prototype_ `void ProcessPingSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo);` — Processes a Ping segment. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment.
- L901 _protected prototype_ `void ProcessPongSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo);` — Processes a Pong segment. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment.
- L909 _protected prototype_ `void ProcessRetransmitSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo);` — Processes a Retransmit segment. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment.
- L917 _protected prototype_ `void ProcessTimeoutSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo);` — Processes a Timeout segment. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment.
- L925 _protected prototype_ `void ProcessMeshSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo);` — Processes a Mesh segment. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment.
- L934 _protected prototype_ `void ProcessUnknownSegment(FInboundSegment& Segment, FNodeInfo& NodeInfo, uint8 SegmentType);` — Processes an unknown segment type. @param Segment The segment to process. @param NodeInfo Details for the node that sent the segment. @param SegmentType The segment type.
- L942 _protected prototype_ `void TryDeliverMessage(const TSharedPtr<FUdpReassembledMessage>& ReassembledMessage, FNodeInfo& NodeInfo);` — Try to deliver the message to the transport layer. @param ReassembledMessage The message to deliver. @param NodeInfo Details of the node that sent the message.
- L947 _protected prototype_ `bool LookupAndCacheMessageType(TSharedPtr<FUdpReassembledMessage>& ReassembledMessage);` — Lookup the reassembled message type and try to determine the source struct type.
- L954 _protected prototype_ `void RemoveKnownNode(const FGuid& NodeId);` — Removes the specified node from the list of known remote endpoints. @param NodeId The identifier of the node to remove.
- L958 _protected prototype_ `void UpdateKnownNodes();` — Updates all known remote nodes.
- L966 _protected prototype_ `int32 UpdateSegmenters(FNodeInfo& NodeInfo);` — Updates all segmenters of the specified node. @param NodeInfo Details for the node to update. @return The actual number of bytes written or -1 if error
- L974 _protected prototype_ `bool UpdateReassemblers(FNodeInfo& NodeInfo);` — Updates all reassemblers of the specified node. @param NodeInfo Details for the node to update. @return true if the update was successful
- L977 _protected prototype_ `void UpdateNodesPerVersion();` — Updates nodes per protocol version map
- L984 _protected prototype_ `virtual void Tick() override;`
- L1003 _protected function_ `TArray<FShallowNodeInfo> GetKnownNodesAsSnapshot()` — Return a shallow copy of the known nodes as seen by the processor. This is used and accessible by debugging logging utils.
- L1028 _private prototype_ `TOptional<FSentSegmentInfoArray> DrainQueue(FNodeInfo& NodeInfo, FNodeInfo::FWorkQueue& WorkQueue, int64 DrainCount, const bool bDrainOverflow);` — Drain a given send queue to the drain limit specified on the parameter listed. Also drain the overflow bucket if requested. Overflow may occasionally fill from pending acks or work queue overflowing.
- L1034 _private prototype_ `int32 RequeueWork(FNodeInfo& NodeInfo, FNodeInfo::FWorkQueue& WorkQueue, const FSentSegmentInfoArray& ProcessedMessages);` — Refill the given queue with new work based on the processed messages. They will be put back in the queue to be processed later in the next round to ensure fairness in the sending of data.
- L1040 _private prototype_ `bool ProcessQueue(FNodeInfo& NodeInfo, FNodeInfo::FWorkQueue& WorkQueue, int64 DrainLimit, int32& BytesSent, bool bShouldDrainOverflowQueue = false);` — Process a given queue.  This calls into DrainQueue and RequeueWork repeatedly until we reach the drain limit which is the minimum value of of send capacity.  For example, if DrainLimit is 0 then we work until the send capacity is 0.
- L1043 _private prototype_ `void SendKnownNodesToKnownNodes();` — Send our list of known nodes to the known nodes.
- L1046 _private prototype_ `bool CanSendKnownNodesToKnownNodes() const;` — Do we support sending known nodes to our known nodes.
- L1049 _private prototype_ `void StartThread();` — Start the message processor thread.
- L1052 _private prototype_ `void OnPluginLoadingPhaseComplete(ELoadingPhase::Type LoadingPhase, bool bPhaseSuccessful);` — Delegate invoke when plugin phase has been completed.
- L1055 _private prototype_ `void HandleSocketError(const TCHAR* ErrorReference, const FNodeInfo& NodeInfo) const;` — Handles a communication error to a particular endpoint.
- L1058 _private prototype_ `bool MoreToSend();` — Checks all known nodes to see if any have both segmenters and send windows ready to transmit.
- L1061 _private prototype_ `int32 AssignNextMessageId();` — Increments and returns the running message ID, bounding it to be non-negative.
- L1064 _private prototype_ `void ConsumeOneOutboundMessage(const FOutboundMessage& OutboundMessage);` — Consume an Outbound Message for processing.
- L1067 _private member_ `TMpscQueue<FInboundSegment> InboundSegments;` — Holds the queue of outbound messages.
- L1070 _private member_ `TMpscQueue<FOutboundMessage> OutboundMessages;` — Holds the queue of outbound messages.
- L1073 _private member_ `TUniquePtr<FUdpMessageBeacon> Beacon;` — Holds the hello sender.
- L1076 _private member_ `FTimespan DeltaTime;` — Holds the delta time between two ticks.
- L1079 _private member_ `TArray<uint8> SupportedProtocolVersions;` — Holds the protocol version that can be communicated in.
- L1082 _private member_ `mutable FCriticalSection StatisticsCS;` — Mutex protecting access to the Statistics map.
- L1085 _private member_ `TMap<FGuid, FMessageTransportStatistics> NodeStats;` — Map that holds latest statistics for network transmission
- L1088 _private member_ `mutable FCriticalSection NodeVersionCS;` — Mutex protecting access to the NodeVersions map.
- L1091 _private member_ `TMap<FGuid, uint8> NodeVersions;` — Holds the protocol version of each nodes separately for safe access (NodeId -> Protocol Version).
- L1094 _private member_ `TMap<FGuid, FNodeInfo> KnownNodes;` — Holds the collection of known remote nodes.
- L1097 _private member_ `bool bAddedNewKnownNodes = false;` — Indicate if we added new nodes during this frame.
- L1101 _private member_ `static std::atomic<uint16> NextNodeTraceId;` — FNodeInfo trace ID. 0 == invalid.
- L1104 _private member_ `uint16 LocalNodeTraceId;` — Holds the local node trace ID.
- L1108 _private member_ `FGuid LocalNodeId;` — Holds the local node identifier.
- L1111 _private member_ `int32 LastSentMessage;` — Holds the last sent message number.
- L1114 _private member_ `FIPv4Endpoint MulticastEndpoint;` — Holds the multicast endpoint.
- L1117 _private member_ `FSocket* Socket;` — Holds the network socket used to transport messages.
- L1120 _private member_ `TUniquePtr<UE::UdpMessaging::FSocketSender> SocketSender;` — Holds the socket sender.
- L1123 _private member_ `bool bShareKnownNodes = false;` — Enable sharing of our known nodes.
- L1126 _private member_ `bool bStopping;` — Holds a flag indicating that the thread is stopping.
- L1129 _private member_ `bool bIsInitialized;` — Holds a flag indicating if the processor is initialized.
- L1132 _private member_ `TUniquePtr<FRunnableThread> Thread;` — Holds the thread object.
- L1135 _private member_ `TSharedPtr<FEvent, ESPMode::ThreadSafe> WorkEvent;` — Holds an event signaling that inbound messages need to be processed.
- L1138 _private member_ `FOnMessageReassembled MessageReassembledDelegate;` — Holds a delegate to be invoked when a message was received on the transport channel.
- L1141 _private member_ `FOnNodeDiscovered NodeDiscoveredDelegate;` — Holds a delegate to be invoked when a network node was discovered.
- L1144 _private member_ `FOnNodeLost NodeLostDelegate;` — Holds a delegate to be invoked when a network node was lost.
- L1147 _private member_ `FOnError ErrorDelegate;` — Holds a delegate to be invoked when a socket error happen.
- L1150 _private member_ `FOnErrorSendingToEndpoint ErrorSendingToEndpointDelegate;` — Holds a delegate to be invoked when a socket error occurs sending to a given endpoint.
- L1153 _private member_ `FCanAcceptEndpoint CanAcceptEndpointDelegate;` — Holds a delegate to be invoked when checking the validity of a given endpoint address.
- L1156 _private member_ `FOnInboundSegment InboundSegmentDelegate;` — Holds a delegate to allow logger to inspect inbound segments.
- L1159 _private member_ `std::atomic<bool> bEnableMessageDelegates = false;` — Enable / disable inbound segment delegates.
- L1162 _private member_ `EUdpMessageFormat MessageFormat;` — The configured message format (from UUdpMessagingSettings).
- L1165 _private member_ `TMap<FString, TWeakObjectPtr<UScriptStruct>> CachedTypeInfoMap;` — Stores a cache of discovered UScriptStruct types found during message processing.
- L1168 _private member_ `TSet<FUdpReassembledMessageSharedPtr> PendingTypeLookup;` — Stores messages pending type lookup.
- L1171 _private member_ `float MemoryLoggingThresholdMB = -1;` — How much memory (MB) should be used before periodically logging information about nodes' memory usage.
- L1174 _private member_ `double LastReassemblersLogTime = 0.0;` — Timestamp used to keep track of the last time we logged the active reassemblers. (A negative value will disable logging)
- L1177 _private member_ `static const int32 DeadHelloIntervals;` — Defines the maximum number of Hello segments that can be dropped before a remote endpoint is considered dead.
- L1180 _private member_ `static const FTimespan StaleReassemblyInterval;` — Defines a timespan after which non fully reassembled messages that have stopped receiving segments are dropped.

#### struct `FUdpMessageProcessor::FNodeInfo`  
`struct FNodeInfo`  
_L147-543_
- desc: Structure for known remote endpoints.
- L150 _public member_ `FIPv4Endpoint Endpoint;` — Holds the node's IP endpoint.
- L153 _public member_ `FUdpMessagingTime LastSegmentReceivedTime;` — Holds the time at which we last received any segment from this node.
- L156 _public member_ `FGuid NodeId;` — Holds the endpoint's node identifier.
- L159 _public member_ `uint8 ProtocolVersion;` — Holds the protocol version this node is communicating with
- L162 _public member_ `uint16 MaxSegmentSize;` — The maximum datagram payload (UDP SDU) this node is capable of receiving. Clamped to USO size if enabled.
- L165 _public member_ `TMap<int32, TSharedPtr<FUdpReassembledMessage>> ReassembledMessages;` — Holds the collection of reassembled messages.
- L168 _public member_ `TMap<int32, TSharedPtr<FUdpMessageSegmenter>> Segmenters;` — Holds the collection of message segmenters.
- L170 _public typedef_ `using FWorkQueue = TRingBuffer<int32, FUdpMessagingRangeChecklessHeapAllocator>;`
- L173 _public member_ `FWorkQueue ReliableWorkQueue;` — Holds of queue of MessageIds to send for reliable messages. They are processed in round-robin fashion.
- L176 _public member_ `FWorkQueue UnreliableWorkQueue;` — Holds of queue of MessageIds to send for unreliable messages. They are processed in round-robin fashion.
- L179 _public member_ `TArray<int32> OverflowForPendingAck;` — Holds the list of messages that are still pending acknowledgement.
- L182 _public member_ `TMap<uint64, FSentData> InflightSegments;` — A map from sequence id to information about what was sent. The size of this map is the size of our sending window.
- L185 _public member_ `TRingBuffer<FSegmentSendExpiry> ReliableExpiry;` — Send timings for outgoing reliable segments.
- L188 _public member_ `TRingBuffer<FSegmentSendExpiry> UnreliableExpiry;` — Send timings for outgoing unreliable segments.
- L191 _public member_ `TSet<int32> RecentlyDeliveredMessages;` — Messages delivered recently enough to track and suppress double delivery.
- L194 _public member_ `TRingBuffer<FMessageDeliverExpiry> DeliveryExpiry;` — Delivery times for recently delivered messages.
- L197 _public member_ `uint64 SequenceId = 0;` — Unique sequence id for every packet sent.
- L200 _public member_ `uint64 WindowSize = 1024;` — Maximum number of segments we can have in flight. Start with a middle of the road value and adjust based on network performance.
- L203 _public member_ `uint64 MaxWindowSize = 2048;` — Maximum window size that can be set.
- L206 _public member_ `double SmoothedRTT = -1.0;` — A smoothed calculated RTT that is effectively the weighted average.
- L209 _public member_ `double RTTVariance = 0.0;` — Measured variance of the RTT to be used to calculate a retransmission timeout.
- L217 _public member_ `double RetransmissionTimeout = 1.0f;` — Set a high retransmission timeout on init until we start measuring speed and overall jitter. The default is 1 second. In other words, if we don't get an ack within 1 second, we assume it was lost and thus should be marked for retransmission. This value will adjust lower as we compute new data especially on a fast network.
- L220 _public member_ `FMessageTransportStatistics Statistics;` — Various transport statistics for this endpoint
- L224 _public member_ `uint16 NodeTraceId;` — ID used for trace events.
- L228 _public prototype_ `FNodeInfo();` — Default constructor.
- L233 _public function_ `uint64 Remap(uint32 MessageId, uint32 SegmentId)` — Remap a MessageId and SegmentId pair into a 64 bit number using Szudzik pairing calculation.
- L251 _public function_ `TSharedPtr<FUdpMessageSegmenter> MarkAcksOnSegmenter(int32 MessageId, const TArray<uint32>& Segments, const FUdpMessagingTime InCurrentTime)` — Update the segmenter with the given acks. If all acks have been received then remove it from the list of segmenters.
- L274 _public function_ `template <typename PredFunc> void RemoveInflightIf(PredFunc&& Pred)` — Helper template to allow us to remove types of segments in flight.
- L288 _public function_ `void CalculateNewRTT(const FTimespan& NewSpan)` — Update the calculated round trip time based on the computed span of inflight packet.
- L326 _public function_ `void ComputeWindowSize(uint32 NumAcks, uint32 SegmentLoss = 0)` — Compute the new window size for the connection.  We use a AIMD algorithm: https://en.wikipedia.org/wiki/Additive_increase/multiplicative_decrease
- L345 _public function_ `void AddInflight(const FSentData& SentData)` — Called on transmit. Keeps expiry queues in sync with InflightSegments map.
- L359 _public function_ `void RemoveInflight(const FSentData& SentData)` — Undo a previous AddInflight. This frees up send window, but leaves the harmless stale expiry.
- L372 _public function_ `uint32 RemoveAllInflightFromMessageId(int32 MessageId)` — Remove all segments in the inflight buffer that match the given MessageId.
- L386 _public function_ `void MarkComplete(int32 MessageId, const FUdpMessagingTime InCurrentTime)` — Make a given MessageId as complete and recompute the desired window size based on any loss / acks received.
- L398 _public function_ `bool MarkAcks(int32 MessageId, const TArray<uint32>& Segments, const FUdpMessagingTime InCurrentTime)` — For a given list of segments to acknowledge record how long it took to receive a response and update our average round trip time. We also use this opportunity to calculate any loss and update our window size. @return true if the message has been fully acknowledged, false otherwise.
- L440 _public function_ `void MarkSegmenterSegmentLoss(const FSentData& Data)` — Mark a segment for retransmission because it was deemed lost.
- L454 _public function_ `uint32 ExpireSegments(const FUdpMessagingTime InCurrentTime)` — Iterate over all segments and discover any potential segments that may be lost.  A lost segment is determined using 2 times the average round trip time.  If an ack has not been received in that time frame then it is lost and we must resend it.
- L504 _public function_ `void ExpireRecentDeliveries()` — Cull old redelivery guards.
- L518 _public function_ `bool HasSegmenterThatCanSend(const FUdpMessagingTime InCurrentTime)` — Does this node have any segmenters that can send data for the current time frame.
- L534 _public function_ `bool CanSendSegments() const` — Do we still have room in our outbound window to send data.
- L539 _public function_ `int64 SendCapacity() const`

#### struct `FUdpMessageProcessor::FInboundSegment`  
`struct FInboundSegment`  
_L547-571_
- desc: Structure for inbound segments.
- L550 _public member_ `TSharedPtr<FArrayReader> Data;` — Holds the segment data.
- L553 _public member_ `FIPv4Endpoint Sender;` — Holds the sender's network endpoint.
- L556 _public member_ `const FUdpMessagingTime EnqueueTime;`
- L560 _public function_ `FInboundSegment( const TSharedPtr<FArrayReader>& InData, const FIPv4Endpoint& InSender, FUdpMessagingTime InEnqueueTime ) : Data(InData) , Sender(InSender) #if UDPMESSAGINGTRACE_ENABLED , EnqueueTime(InEnqueueTime) #endif` — Creates and initializes a new instance.

#### struct `FUdpMessageProcessor::FOutboundMessage`  
`struct FOutboundMessage`  
_L575-603_
- desc: Structure for outbound messages.
- L578 _public member_ `TSharedPtr<FUdpSerializedMessage> SerializedMessage;` — Holds the serialized message.
- L581 _public member_ `TArray<FGuid> RecipientIds;` — Holds the recipients.
- L583 _public member_ `EMessageFlags MessageFlags;`
- L586 _public member_ `const FUdpMessagingTime EnqueueTime;`
- L590 _public function_ `FOutboundMessage( const TSharedRef<FUdpSerializedMessage>& InSerializedMessage, const TArray<FGuid>& InRecipientIds, EMessageFlags InFlags, FUdpMessagingTime InEnqueueTime ) : SerializedMessage(InSerializedMessage) , RecipientIds(InRecipientIds) , MessageFlags(InFlags) #if UDPMESSAGINGTRACE_ENABLED , EnqueueTime(InEnqueueTime) #endif` — Creates and initializes a new instance.

#### struct `FUdpMessageProcessor::FShallowNodeInfo`  
`struct FShallowNodeInfo`  
_L987-1000_
- desc: A shallow copy of NodeInfo for use by the logger.
- L990 _public member_ `FIPv4Endpoint Endpoint;` — Holds the node's IP endpoint.
- L993 _public member_ `FUdpMessagingTime LastSegmentReceivedTime;` — Holds the time at which we last received any segment from this node.
- L996 _public member_ `FGuid NodeId;` — Holds the endpoint's node identifier.
- L999 _public member_ `uint8 ProtocolVersion;` — Holds the protocol version this node is communicating with

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace FUdpMessageSegment`
- L32 _namespace_ `namespace FUdpMessageSegment`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace UdpMessaging` (scope `UE`)
- L46 _typedef_ `using FUdpReassembledMessageSharedPtr = TSharedPtr<FUdpReassembledMessage, ESPMode::ThreadSafe>;`
- L113 _typedef_ `using FSentSegmentInfoArray = TArray<FSentSegmentInfo, TInlineAllocator<64>>;`
- L115 _namespace_ `namespace UE`
- L115 _namespace_ `namespace Private` (scope `UE`)
- L115 _namespace_ `namespace MessageProcessor` (scope `UE::Private`)
- L120 _prototype_ `FOnOutboundTransferDataUpdated &OnSegmenterUpdated();` (scope `UE::Private::MessageProcessor`) — Global delegate for handling segmenter (aka sent data) updates.
- L125 _prototype_ `FOnInboundTransferDataUpdated &OnReassemblerUpdated();` (scope `UE::Private::MessageProcessor`) — Global delegate for handling reassembler (aka received data) updates.
- L136 _enumerator_ `enum { RequireRangeCheck = false };` (scope `FUdpMessagingRangeChecklessHeapAllocator::__anone80c480a0103`) — Don't want to lose performance on range checks in performance-critical code.
- L376 _function_ `` (scope `FUdpMessageProcessor::FNodeInfo::RemoveAllInflightFromMessageId`)
- L460 _function_ `` (scope `FUdpMessageProcessor::FNodeInfo::ExpireSegments`)
- L520 _typedef_ `using FSegmenterTuple = TTuple<int32,TSharedPtr<FUdpMessageSegmenter>>;` (scope `FUdpMessageProcessor::FNodeInfo::HasSegmenterThatCanSend`)
- L711 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnMessageReassembled, FUdpReassembledMessageSharedPtr , const IMessageAttachmentPtr& , const FGuid& ) FOnMessageReassembled& OnMessageReassembled() { return MessageReassembledDelegate; } DECLARE_DELEGATE_OneParam(FOnNodeDiscovered, const FGuid& ) FOnNodeDiscovered& OnNodeDiscovered() { return NodeDiscoveredDelegate; } DECLARE_DELEGATE_OneParam(FOnNodeLost, const FGuid& ) FOnNodeLost& OnNodeLost() { return NodeLostDelegate; } DECLARE_DELEGATE(FOnError) FOnError& OnError() { return ErrorDelegate;` — Returns a delegate that is executed when message data has been received. @return The delegate.
- L723 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNodeDiscovered, const FGuid& ) FOnNodeDiscovered& OnNodeDiscovered() { return NodeDiscoveredDelegate; } DECLARE_DELEGATE_OneParam(FOnNodeLost, const FGuid& ) FOnNodeLost& OnNodeLost() { return NodeLostDelegate; } DECLARE_DELEGATE(FOnError) FOnError& OnError() { return ErrorDelegate; } void SetEnableMessageDelegates(bool bShouldEnable) { bEnableMessageDelegates = bShouldEnable; }` — Returns a delegate that is executed when a remote node has been discovered. @return The delegate. @see OnNodeLost
- L735 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNodeLost, const FGuid& ) FOnNodeLost& OnNodeLost() { return NodeLostDelegate; } DECLARE_DELEGATE(FOnError) FOnError& OnError() { return ErrorDelegate; } void SetEnableMessageDelegates(bool bShouldEnable) { bEnableMessageDelegates = bShouldEnable; } DECLARE_TS_MULTICAST_DELEGATE_FourParams(FOnInboundSegment, const FInboundSegment&, const FGuid&, EUdpMessageSegments, bool) FOnInboundSegment& OnInboundSegmentReceived_UdpMessageProcessorThread() { return InboundSegmentDelegate; }` — Returns a delegate that is executed when a remote node was closed or timed out. @return The delegate. @see OnNodeDiscovered
- L747 _delegate_ `DECLARE_DELEGATE(FOnError) FOnError& OnError() { return ErrorDelegate; } void SetEnableMessageDelegates(bool bShouldEnable) { bEnableMessageDelegates = bShouldEnable; } DECLARE_TS_MULTICAST_DELEGATE_FourParams(FOnInboundSegment, const FInboundSegment&, const FGuid&, EUdpMessageSegments, bool) FOnInboundSegment& OnInboundSegmentReceived_UdpMessageProcessorThread() { return InboundSegmentDelegate; } DECLARE_DELEGATE_TwoParams(FOnErrorSendingToEndpoint, const FGuid& , const FIPv4Endpoint& ) FOnErrorSendingToEndpoint& OnErrorSendingToEndpoint_UdpMessageProcessorThread() { return ErrorSendingToEndpointDelegate; }` — Returns a delegate that is executed when a socket error happened. @return The delegate. @note this delegate is broadcasted from the processor thread.
- L763 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_FourParams(FOnInboundSegment, const FInboundSegment&, const FGuid&, EUdpMessageSegments, bool) FOnInboundSegment& OnInboundSegmentReceived_UdpMessageProcessorThread() { return InboundSegmentDelegate; } DECLARE_DELEGATE_TwoParams(FOnErrorSendingToEndpoint, const FGuid& , const FIPv4Endpoint& ) FOnErrorSendingToEndpoint& OnErrorSendingToEndpoint_UdpMessageProcessorThread() { return ErrorSendingToEndpointDelegate; } DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanAcceptEndpoint, const FGuid& , const FIPv4Endpoint& ) FCanAcceptEndpoint& OnCanAcceptEndpoint_UdpMessageProcessorThread() { return CanAcceptEndpointDelegate; } TArray<FIPv4Endpoint> GetKnownEndpoints() const;` — Inbound segment delegate inspector @return The delegate.
- L775 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnErrorSendingToEndpoint, const FGuid& , const FIPv4Endpoint& ) FOnErrorSendingToEndpoint& OnErrorSendingToEndpoint_UdpMessageProcessorThread() { return ErrorSendingToEndpointDelegate; } DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanAcceptEndpoint, const FGuid& , const FIPv4Endpoint& ) FCanAcceptEndpoint& OnCanAcceptEndpoint_UdpMessageProcessorThread() { return CanAcceptEndpointDelegate; } TArray<FIPv4Endpoint> GetKnownEndpoints() const;` — Returns a delegate that is executed when a socket fails to communicate upon sending to a target endpoint. @return The delegate @note this delegate is broadcasted from the processor thread.
- L787 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanAcceptEndpoint, const FGuid& , const FIPv4Endpoint& ) FCanAcceptEndpoint& OnCanAcceptEndpoint_UdpMessageProcessorThread() { return CanAcceptEndpointDelegate; } TArray<FIPv4Endpoint> GetKnownEndpoints() const;` — Returns a delegate that is executed when a socket fails to communicate upon sending to a target endpoint. @return The delegate @note this delegate is broadcasted from the processor thread.

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Transport/UdpMessageProcessorLogger.h` (Private)


#### struct `FUdpMessageProcessorLogger`  
`struct FUdpMessageProcessorLogger`  
_L11-33_
- L13 _public prototype_ `FUdpMessageProcessorLogger(FIPv4Endpoint InEndpoint, uint16 PortNo, FUdpMessageProcessor* InProcessor);`
- L14 _public prototype_ `~FUdpMessageProcessorLogger();`
- L17 _public prototype_ `void StartLogging();` — Start enhanced logging for UdpMessageProcessor
- L20 _public prototype_ `void StopLogging();` — Stop enhanced logging for UdpMessageProcessor
- L23 _public prototype_ `bool IsLogging() const;` — Report the current logging state.
- L26 _public prototype_ `void DumpKnownNodeInfo();` — Dump a report of the current known nodes from the system.
- L29 _private member_ `FIPv4Endpoint Endpoint;`
- L31 _private member_ `FUdpMessageProcessor* Processor;`
- L32 _private member_ `TUniquePtr<FUdpMessageLoggingImpl> Impl;`

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Transport/UdpMessageResequencer.h` (Private)


#### class `FUdpMessageResequencer`  
`class FUdpMessageResequencer`  
_L11-95_
- desc: Implements a re-sequencer for messages received over the UDP transport.
- L16 _public function_ `FUdpMessageResequencer()` — Default constructor.
- L23 _public function_ `FUdpMessageResequencer(uint16 InWindowSize) : NextSequence(1)` — Creates and initializes a new message resequencer. @param InWindowSize The maximum resequencing window size.
- L34 _public function_ `uint64 GetNextSequence() const` — Gets the next expected sequence number. @return Next sequence.
- L44 _public function_ `bool Pop(TSharedPtr<FUdpReassembledMessage, ESPMode::ThreadSafe>& OutMessage)` — Extracts the next available message in the sequence. @return true if a message was returned, false otherwise.
- L63 _public function_ `bool Resequence(const TSharedPtr<FUdpReassembledMessage, ESPMode::ThreadSafe>& Message)` — Resequences the specified message. @param Message The message to resequence. @return true if the message is in sequence, false otherwise.
- L71 _public function_ `void Reset()` — Resets the re-sequencer.
- L91 _private member_ `uint64 NextSequence;` — Holds the next expected sequence number.
- L94 _private member_ `TArray<TSharedPtr<FUdpReassembledMessage, ESPMode::ThreadSafe>> MessageHeap;` — Holds the messages that need to be resequenced.

#### struct `FUdpMessageResequencer::FSequenceComparer`  
`struct FSequenceComparer`  
_L80-86_
- desc: Helper for ordering messages by their sequence numbers.
- L82 _public function_ `bool operator()(const TSharedPtr<FUdpReassembledMessage, ESPMode::ThreadSafe>& A, const TSharedPtr<FUdpReassembledMessage, ESPMode::ThreadSafe>& B) const`

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Transport/UdpMessageSegmenter.h` (Private)


#### class `FUdpMessageSegmenter`  
`class FUdpMessageSegmenter`  
_L25-296_
- desc: Implements a message segmenter. This class breaks up a message into smaller sized segments that fit into UDP datagrams. It also tracks the segments that still need to be sent.
- L37 _public prototype_ `FUdpMessageSegmenter( const TSharedRef<FUdpSerializedMessage>& InSerializedMessage, uint16 InSegmentSize );` — Creates and initializes a new message segmenter. Segment size includes UdpMessaging headers (\see GetDataSegmentHeaderSize), but not UDP/IP headers. @param InMessage The serialized message to segment. @param InSegmentSize The target total segment size to divide messages into.
- L43 _public prototype_ `~FUdpMessageSegmenter();` — Destructor.
- L52 _public prototype_ `int64 GetMessageSize() const;` — Gets the total size of the message in bytes. @return Message size.
- L61 _public prototype_ `bool GetNextPendingSegment(TArray<uint8>& OutData, uint32& OutSegment) const;` — Gets the next pending segment. @param OutData Will hold the segment data. @param OutSegment Will hold the segment number. @return true if a segment was returned, false if there are no more pending segments.
- L70 _public prototype_ `bool GetPendingSegment(uint32 InSegment, TArray<uint8>& OutData) const;` — Gets the pending segment at. @param InSegment the segment number we are requesting the data for. @param OutData Will hold the segment data. @return true if a segment was returned, false if that segment is no longer pending or the segment number is invalid.
- L77 _public function_ `const TBitArray<>& GetPendingSendSegments() const` — Get the pending segments array. @return the list of pending segments flags.
- L87 _public function_ `uint32 GetPendingSendSegmentsCount() const` — Gets the number of segments that haven't been received yet. @return Number of pending segments.
- L96 _public function_ `const TBitArray<>& GetAcknowledgedSegments() const` — Get the array of acknowledged segments. True represents acknowledgement. This array will be empty for unreliable messages @return the list of segments.
- L106 _public function_ `uint32 GetAcknowledgedSegmentsCount() const` — Gets the number of segments that have been acknowledged. Always zero for unreliable messages @return Number of acknowledged segments.
- L116 _public function_ `uint32 GetSegmentCount() const` — Gets the total number of segments that make up the message. @return Segment count.
- L126 _public function_ `uint16 GetTotalSegmentSize() const` — Gets the total segment size including headers. @return Segment size in bytes.
- L136 _public function_ `static constexpr uint16 GetDataSegmentHeaderSize()` — Gets the size of the headers that are prepended to each segment. @return Header size in bytes.
- L147 _public function_ `uint16 GetSegmentPayloadSize() const` — Gets the number of actual message data bytes per segment, excluding headers (goodput). @return Segment payload size in bytes.
- L157 _public prototype_ `bool TryInitialize();` — Attempt to initialize an uninitialized segmenter. @return true if the segmenter was uninitialized and serialization is complete, false otherwise.
- L164 _public function_ `bool IsSendingComplete() const` — Checks whether all segments have been sent. @return true if all segments were sent, false otherwise.
- L174 _public function_ `bool AreAcknowledgementsComplete() const` — Checks whether all outstanding acknowledgments have been received. Always true for an unreliable message once its sent @return true if all acknowledgments are received
- L184 _public function_ `bool IsInitialized() const` — Checks whether this segmenter has been initialized. @return true if it is initialized, false otherwise.
- L194 _public prototype_ `bool IsInvalid() const;` — Checks whether this segmenter is invalid. @return true if the segmenter is invalid, false otherwise.
- L197 _public prototype_ `uint8 GetProtocolVersion() const;` — Return the Protocol Version for this segmenter.
- L200 _public prototype_ `EMessageFlags GetMessageFlags() const;` — @return the message flags.
- L207 _public prototype_ `void MarkAsSent(uint32 SegmentId);` — Marks the given segment id as sent. @param Segment id.
- L214 _public prototype_ `void MarkAsSent(const TArray<uint32>& Segments);` — Marks the specified segments as sent @param Segments The acknowledged segments.
- L221 _public prototype_ `void MarkAsAcknowledged(uint32 SegmentId);` — Marks the given segment id as acknowledged. @param Segment id.
- L228 _public prototype_ `void MarkAsAcknowledged(const TArray<uint32>& Segments);` — Marks the specified segments as acknowledged. @param Segments The acknowledged segments.
- L233 _public prototype_ `void MarkForRetransmission();` — Marks the entire message for retransmission. This does not reset acknowledgements as we only need an acknowledgment for a segement once
- L238 _public prototype_ `void MarkForRetransmission(uint32 SegmentId);` — Marks a given segment id for retransmission
- L246 _public prototype_ `void MarkForRetransmission(const TArray<uint16>& Segments);` — Marks the specified segments for retransmission. @param Segments The data segments to retransmit. @note this function is kept for legacy reasons to be used with FRetransmitChunk which still encodes its segment count on uint16. FRetransmitChunk aren't used in protocol 12 and newer.
- L249 _public prototype_ `bool WasRetransmitted(uint32 SegmentId) const;` — Return whether a segment has been retransmitted.
- L259 _public prototype_ `bool IsMessageSerializationDone() const;` — Checks whether the serialization of the message to segment and send completed. The serialization may be performing asynchronously and can may succeed or fail. The message cannot be segmented and sent until it was serialized sucessfully. @return true if the message is serialization is done, false if it still serializing. @see TryInitialize() @see IsInvalid() @see IsInitialized()
- L263 _public prototype_ `void EmitPostInitializeTraceEvents(uint16 InSenderTraceId, uint16 InRecipientTraceId, int32 InMessageId);` — Once serialization completes, the processor passes in context we use to record facts about this message.
- L268 _private member_ `FArchive* MessageReader = nullptr;` — Used to seek and output portions of SerializedMessage.
- L271 _private member_ `TBitArray<> PendingSendSegments;` — Holds an array of bits where true indicates which segments still need to be sent.
- L274 _private member_ `TBitArray<> AcknowledgeSegments;` — Holds an array of bits where true indicates a segment has been acknowledged. Will always zero-length for an unreliable segment.
- L277 _private member_ `uint32 PendingSendSegmentsCount = 0;` — Holds the number of segments that haven't been sent yet.
- L280 _private member_ `uint32 AcknowledgeSegmentsCount = 0;` — Holds the number of segments that haven't been acknowledged yet. Will always be zero for an unreliable message
- L283 _private member_ `int32 EarliestUnackedSegmentId = 0;` — Holds the earliest segment for which we have not received an acknowledgment. Useful to narrow search.
- L286 _private member_ `uint16 SegmentSize = 0;` — Holds the segment size (including the FHeader and FDataChunk fields).
- L289 _private member_ `uint16 RetransmitCount = 0;` — Holds the number of retransmits.
- L292 _private member_ `TSharedPtr<FUdpSerializedMessage, ESPMode::ThreadSafe> SerializedMessage;` — Holds the message.
- L295 _private member_ `TSet<uint32> RetransmittedSegments;` — Keep a record of any segments we've retransmitted.

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Transport/UdpMessageTransport.h` (Private)


#### class `FUdpMessageTransport`  
`class FUdpMessageTransport : public TSharedFromThis<FUdpMessageTransport, ESPMode::ThreadSafe> , public IMessageTransport`  
_L39-200_
- inherits: `TSharedFromThis<FUdpMessageTransport,ESPMode::ThreadSafe>,IMessageTransport`
- desc: Implements a message transport technology using an UDP network connection. On platforms that support multiple processes, the transport is using two sockets, one for per-process unicast sending/receiving, and one for multicast receiving. Console and mobile platforms use a single multicast socket for all sending and receiving.
- L54 _public prototype_ `FUdpMessageTransport(const FIPv4Endpoint& InLocalEndpoint, const FIPv4Endpoint& InMulticastEndpoint, TArray<FIPv4Endpoint> InStaticEndpoints, TArray<FString> InExcludedEndpointsAsString, uint8 InMulticastTtl);` — Creates and initializes a new instance. @param InLocalEndpoint The local IP endpoint to receive messages on. @param InMulticastEndpoint The multicast group endpoint to transport messages to. @param InStaticEndpoints array of endpoints to include in communication @param InExcludedEndpoints array of string formatted endpoints to exclude in communication. @param InMulticastTtl The multicast time-to-live.
- L61 _public prototype_ `virtual ~FUdpMessageTransport();` — Virtual destructor.
- L64 _public prototype_ `void OnAppPreExit();` — Notifies the transport that the application is about to exit.
- L70 _public prototype_ `static bool MatchesEndpoint(const FString& SourceEndpoint, const FIPv4Endpoint& TargetEndpoint);` — Helper method to detect if a given target endpoint matches the wildcard deliminted source endpoint. The source endpoint should be in IPv4 format.  A.B.C.D:<OptionalPortNumber>.  Wildcard characters are allowed.
- L77 _public prototype_ `void AddStaticEndpoint(const FIPv4Endpoint& InEndpoint);` — Add a static endpoint to the transport @param InEndpoint the endpoint to add
- L83 _public prototype_ `void RemoveStaticEndpoint(const FIPv4Endpoint& InEndpoint);` — Remove a static endpoint from the transport @param InEndpoint the endpoint to remove
- L86 _public prototype_ `virtual FName GetDebugName() const override;`
- L87 _public prototype_ `virtual bool StartTransport(IMessageTransportHandler& Handler) override;`
- L88 _public prototype_ `virtual void StopTransport() override;`
- L89 _public prototype_ `virtual bool TransportMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const TArray<FGuid>& Recipients) override;`
- L94 _public prototype_ `TArray<FIPv4Endpoint> GetListeningAddresses() const;` — Get the IPv4Endpoint listening addresses.
- L100 _public prototype_ `TArray<FIPv4Endpoint> GetKnownEndpoints() const;` — Get the known endpoints that are in active communication with the UDP transport. This is information known by the processor.
- L105 _public prototype_ `FMessageTransportStatistics GetLatestStatistics(FGuid NodeId) const;` — Retrieve the latest network statistics for the given node.
- L110 _private prototype_ `void HandleProcessorMessageReassembled(FUdpReassembledMessageSharedPtr ReassembledMessagePtr, const TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe>& Attachment, const FGuid& NodeId);` — Handles received transport messages.
- L113 _private prototype_ `void HandleProcessorNodeDiscovered(const FGuid& DiscoveredNodeId);` — Handles discovered transport endpoints.
- L116 _private prototype_ `void HandleProcessorNodeLost(const FGuid& LostNodeId);` — Handles lost transport endpoints.
- L119 _private prototype_ `void HandleProcessorError();`
- L122 _private prototype_ `bool HandleProcessorEndpointCheck(const FGuid& EndpointNodeId, const FIPv4Endpoint& SenderIpAddress);` — Returns true if we can add this endpoint to the list of nodes we communicate with.
- L125 _private prototype_ `void HandleEndpointCommunicationError(const FGuid& EndpointId, const FIPv4Endpoint& EndpointIdAddress);` — Handle endpoint communication error.
- L128 _private prototype_ `void StartAutoRepairRoutine(uint32 MaxRetryAttempt);` — Launches a routine that attempts to restart the transport.
- L131 _private prototype_ `void StopAutoRepairRoutine();` — Halts any currently running transport restart routine.
- L137 _private prototype_ `bool RestartTransport();` — Restart the transport using the same Transport handler. @return true if the restart was successful
- L140 _private prototype_ `void HandleSocketDataReceived(const TSharedPtr<FArrayReader, ESPMode::ThreadSafe>& Data, const FIPv4Endpoint& Sender);` — Handles received socket data.
- L143 _private prototype_ `void HandleMulticastSocketDataReceived(const TSharedPtr<FArrayReader, ESPMode::ThreadSafe>& Data, const FIPv4Endpoint& Sender);` — Handles received socket data for multicast receiver.
- L147 _private prototype_ `void DoClearDenyCandidateList();` — Clear the deny list
- L150 _private member_ `TFuture<void> ErrorFuture;` — Holds any pending restart request.
- L153 _private member_ `FTSTicker::FDelegateHandle AutoRepairHandle;` — Holds the delegate handle for the auto repair routine.
- L156 _private member_ `FUdpMessageProcessor* MessageProcessor;` — Holds the message processor.
- L159 _private member_ `FIPv4Endpoint MulticastEndpoint;` — Holds the multicast endpoint.
- L162 _private member_ `FUdpSocketReceiver* MulticastReceiver;` — Holds the multicast socket receiver.
- L165 _private member_ `FSocket* MulticastSocket;` — Holds the multicast socket.
- L168 _private member_ `uint8 MulticastTtl;` — Holds the multicast time to live.
- L171 _private member_ `ISocketSubsystem* SocketSubsystem;` — Holds a pointer to the socket sub-system.
- L174 _private member_ `IMessageTransportHandler* TransportHandler;` — Message transport handler.
- L177 _private member_ `FIPv4Endpoint UnicastEndpoint;` — Holds the local endpoint to receive messages on.
- L181 _private member_ `FUdpSocketReceiver* UnicastReceiver;` — Holds the unicast socket receiver.
- L184 _private member_ `FSocket* UnicastSocket;` — Holds the unicast socket.
- L188 _private member_ `TSet<FIPv4Endpoint> StaticEndpoints;` — Holds the static endpoints.
- L191 _private member_ `TArray<FString> ExcludedEndpoints;` — Excluded list of IP addresses as string value (can contain wildcards) not allowed to talk to UDP processor
- L194 _private member_ `TUniquePtr<UE::Tasks::FTaskConcurrencyLimiter> DeserializationTasks;` — Async task queue for running deserialization of reassembled messages.
- L198 _private member_ `TUniquePtr<FUdpMessageProcessorLogger> MessageLogger;` — Logging class to enable inspection of message data.

#### Free symbols / members of external scopes

- L30 _typedef_ `using FUdpReassembledMessageSharedPtr = TSharedPtr<FUdpReassembledMessage, ESPMode::ThreadSafe>;`

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Transport/UdpReassembledMessage.h` (Private)


#### class `FUdpReassembledMessage`  
`class FUdpReassembledMessage`  
_L17-432_
- desc: Implements a reassembled message.
- L37 _public function_ `FUdpReassembledMessage(uint8 InProtocolVersion, EMessageFlags InFlags, int64 MessageSize, uint32 SegmentCount, uint64 InSequence, const FIPv4Endpoint& InSender) : ProtocolVersion(InProtocolVersion) , MessageFlags(InFlags) , PendingSegmentsCount(SegmentCount) , ReceivedBytes(0) , DeliveryStatus(EDeliveryStatus::NotDelivered) , RetransmitRequestsCount(0) , Sender(InSender) , Sequence(InSequence)` — Creates and initializes a new inbound message info. @param ProtocolVersion The protocol version the message is serialized in. @param MessageFlags The message flags of the reassembled message. @param MessageSize The total size of the message in bytes. @param SegmentCount The total number of segments that need to be received for this message. @param InSequence The message sequence number. @param InSender The IPv4 endpoint of the sender.
- L72 _public prototype_ `~FUdpReassembledMessage() = default;`
- L81 _public function_ `uint8 GetProtocolVersion() const` — Gets the message protocol version. @return The Message protocol version.
- L91 _public function_ `EMessageFlags GetFlags() const` — Gets the message flags @return The Message flags.
- L101 _public function_ `const TArray<uint8>& GetData() const` — Gets the message data. @return Message data.
- L111 _public function_ `FUdpMessagingTime GetLastSegmentTime() const` — Gets the time at which the last segment was received. @return Last receive time.
- L121 _public function_ `TArray<uint16> GetPendingSegments() const` — Gets the list of segments that haven't been received yet. @return List of pending segment numbers.
- L142 _public function_ `uint32 GetTotalSegmentsCount() const` — Gets the total number of segments. @return Number of total segments.
- L152 _public function_ `uint32 GetPendingSegmentsCount() const` — Gets the number of segments that haven't been received yet. @return Number of pending segments.
- L162 _public function_ `int32 GetRetransmitRequestsCount() const` — Gets the number of retransmit requests that were sent for this payload. @return Number of retransmit requests.
- L172 _public function_ `uint64 GetSequence() const` — Gets the message's sequence number. @return Sequence number.
- L182 _public function_ `bool IsComplete() const` — Checks whether this message is complete. @return true if the message is complete, false otherwise.
- L192 _public function_ `bool IsInitialized() const` — Checks whether this message has been initialized. @return true if the message is initialized, false otherwise.
- L200 _public function_ `int32 NumPendingAcknowledgements() const` — @return How many acknowledgments are currently pending send.
- L208 _public function_ `FUdpMessagingTime GetLastAckTime() const` — @return The time at which any acknowledgments were last transmitted for this message.
- L218 _public function_ `TArray<uint32> TakePendingAcknowledgments(int32 MaxAckNum, FUdpMessagingTime CurrentTime)` — Gets at most the specified number of pending acknowledgments and clears them, updating LastAckTime. @return The array of pending acknowledgments removed.
- L241 _public function_ `bool IsDelivered() const` — Get if the message has been delivered. @return true if the message has been marked delivered.
- L249 _public function_ `bool IsPendingDelivery() const` — Get if the message is pending delivery through the transport layer.
- L257 _public function_ `void MarkDelivered()` — Mark the reasembled message as delivered.
- L265 _public function_ `void MarkPendingDelivery()` — Mark the reasembled message as pending delivery.
- L273 _public function_ `bool HasFirstSegment() const` — Indicates if the first segment of the data is ready.
- L290 _public function_ `void Reassemble(int32 SegmentNumber, int32 SegmentOffset, const TArray<uint8>& SegmentData, const FUdpMessagingTime CurrentTime)` — Reassembles a segment into the specified message. @param SegmentNumber The number of the message segment. @param SegmentOffset The segment's offset within the message. @param SegmentData The segment data. @param CurrentTime The current time.
- L330 _public function_ `const bool IsReliable() const` — True if this message is reliably delivered.
- L339 _public function_ `const bool IsMalformed() const` — Indicates whether or not this message was found to be malformed. Once we detect a message is malformed, we will not attempt to process any data for it.
- L344 _public function_ `FString Describe() const`
- L349 _public function_ `int32 GetReceivedBytes() const`
- L354 _public function_ `TWeakObjectPtr<UScriptStruct> GetMessageTypeInfo() const`
- L359 _public function_ `void SetMessageTypeInfo(TWeakObjectPtr<UScriptStruct> InTypeInfo)`
- L372 _public function_ `const FTraceMetadata& GetTraceMetadata() const`
- L377 _public function_ `FTraceMetadata& GetTraceMetadata()`
- L385 _private member_ `TWeakObjectPtr<UScriptStruct> TypeInfo;` — Holds the message's type information.
- L388 _private member_ `uint8 ProtocolVersion;` — Holds the message protocol version.
- L391 _private member_ `EMessageFlags MessageFlags;`
- L394 _private member_ `TArray<uint8> Data;` — Holds the message data.
- L397 _private member_ `FUdpMessagingTime LastSegmentTime;` — Holds the time at which the last segment was received.
- L400 _private member_ `TBitArray<> PendingSegments;` — Holds an array of bits that indicate which segments still need to be received.
- L403 _private member_ `uint32 PendingSegmentsCount;` — Holds the number of segments that haven't been received yet.
- L406 _private member_ `TArray<uint32> PendingAcknowledgments;` — Acknowledgment yet to be sent about segments we received
- L409 _private member_ `FUdpMessagingTime LastAckTime;` — Holds the time at which any pending acknowledgments were last transmitted.
- L412 _private member_ `int32 ReceivedBytes;` — Holds the number of bytes received so far.
- L415 _private member_ `std::atomic<EDeliveryStatus> DeliveryStatus;` — Holds if the reassembled message delivery status. This may get set from another thread which is why it is atomic.
- L418 _private member_ `int32 RetransmitRequestsCount;` — Holds the number of retransmit requests that were sent since the last segment was received.
- L421 _private member_ `FIPv4Endpoint Sender;` — Holds the sender.
- L424 _private member_ `uint64 Sequence;` — Holds the message sequence.
- L427 _private member_ `bool bIsMalformed = false;` — Indicates whether or not this message is malformed.
- L430 _private member_ `FTraceMetadata TraceMetadata;`

#### enum `FUdpReassembledMessage::EDeliveryStatus`  
`enum class EDeliveryStatus : uint8`  
_L20-25_
- L22 _public enumerator_ `NotDelivered = 0`
- L23 _public enumerator_ `PendingDelivery`
- L24 _public enumerator_ `Delivered`

#### struct `FUdpReassembledMessage::FTraceMetadata`  
`struct FTraceMetadata`  
_L365-370_
- L367 _public member_ `uint16 SenderShortId = 0;`
- L368 _public member_ `uint16 RecipientShortId = 0;`
- L369 _public member_ `int32 MessageId = 0;`

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Transport/UdpSerializeMessageTask.h` (Private)


#### class `FUdpSerializeMessageTask`  
`class FUdpSerializeMessageTask`  
_L17-74_
- desc: Implements an asynchronous task for serializing a message.
- L27 _public function_ `FUdpSerializeMessageTask(TSharedRef<IMessageContext, ESPMode::ThreadSafe> InMessageContext, TSharedRef<FUdpSerializedMessage, ESPMode::ThreadSafe> InSerializedMessage, TSharedPtr<FEvent, ESPMode::ThreadSafe> InCompletionEvent) : CompletionEventPtr(InCompletionEvent) , MessageContext(InMessageContext) , SerializedMessage(InSerializedMessage)` — Creates and initializes a new instance. @param InMessageContext The context of the message to serialize. @param InSerializedMessage Will hold the serialized message data.
- L41 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);` — Performs the actual task. @param CurrentThread The thread that this task is executing on. @param MyCompletionGraphEvent The completion event.
- L48 _public prototype_ `ENamedThreads::Type GetDesiredThread();` — Returns the name of the thread that this task should run on. @return Thread name.
- L55 _public prototype_ `TStatId GetStatId() const;` — Gets the task's stats tracking identifier. @return Stats identifier.
- L62 _public prototype_ `static ESubsequentsMode::Type GetSubsequentsMode();` — Gets the mode for tracking subsequent tasks. @return Always track subsequent tasks.
- L67 _private member_ `TWeakPtr<FEvent, ESPMode::ThreadSafe> CompletionEventPtr;` — An event signaling that the message was serialized.
- L70 _private member_ `TSharedRef<IMessageContext, ESPMode::ThreadSafe> MessageContext;` — The context of the message to serialize.
- L73 _private member_ `TSharedRef<FUdpSerializedMessage, ESPMode::ThreadSafe> SerializedMessage;` — A reference to the serialized message data.

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Transport/UdpSerializedMessage.h` (Private)


#### enum `EUdpSerializedMessageState`  
`enum class EUdpSerializedMessageState`  
_L20-30_
- desc: Enumerates possible states of a serialized message. @see FUdpSerializedMessage
- L23 _public enumerator_ `Complete` — The message data is complete.
- L26 _public enumerator_ `Incomplete` — The message data is incomplete.
- L29 _public enumerator_ `Invalid` — The message data is invalid.

#### class `FUdpSerializedMessage`  
`class FUdpSerializedMessage : public FMemoryWriter`  
_L36-158_
- inherits: `FMemoryWriter`
- desc: Holds serialized message data.
- L41 _public function_ `FUdpSerializedMessage(EUdpMessageFormat InMessageFormat, uint8 InProtocolVersion, EMessageFlags InFlags) : FMemoryWriter(DataArray, true) , State(EUdpSerializedMessageState::Incomplete) , Flags(InFlags) , Format(InMessageFormat) , ProtocolVersion(InProtocolVersion)` — Default constructor.
- L64 _public function_ `FArchive* CreateReader()` — Creates an archive reader to the data. The caller is responsible for deleting the returned object. @return An archive reader.
- L75 _public function_ `const TArray<uint8>& GetDataArray()` — Get the serialized message data. @return Byte array of message data. @see GetState
- L86 _public function_ `EUdpSerializedMessageState GetState() const` — Gets the state of the message data. @return Message data state. @see GetData, UpdateState
- L97 _public function_ `void UpdateState(EUdpSerializedMessageState InState)` — Updates the state of this message data. @param InState The state to set. @see GetState
- L103 _public function_ `EMessageFlags GetFlags() const` — @return the message flags.
- L109 _public function_ `uint8 GetProtocolVersion() const` — @return the message protocol version.
- L115 _public function_ `EUdpMessageFormat GetFormat() const` — @return the format used to encode the message.
- L128 _public function_ `const FTraceMetadata& GetTraceMetadata() const`
- L133 _public function_ `FTraceMetadata& GetTraceMetadata()`
- L141 _private member_ `TArray<uint8> DataArray;` — Holds the serialized data.
- L144 _private member_ `std::atomic<EUdpSerializedMessageState> State;` — Holds the message data state.
- L147 _private member_ `EMessageFlags Flags;` — Holds message flags, captured from context.
- L150 _private member_ `EUdpMessageFormat Format;` — The format used to serialize the message.
- L153 _private member_ `uint8 ProtocolVersion;` — Holds the Protocol Version the message will be serialized in.
- L156 _private member_ `FTraceMetadata TraceMetadata;`

#### struct `FUdpSerializedMessage::FTraceMetadata`  
`struct FTraceMetadata`  
_L121-126_
- L123 _public member_ `FTopLevelAssetPath TypeInfo;`
- L124 _public member_ `FUdpMessagingTime SerializationStartTime;`
- L125 _public member_ `FUdpMessagingTime SerializationEndTime;`

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Tunnel/UdpMessageTunnel.h` (Private)


#### class `FUdpMessageTunnel`  
`class FUdpMessageTunnel : public FRunnable , public IUdpMessageTunnel , private FSingleThreadRunnable`  
_L22-165_
- inherits: `FRunnable,IUdpMessageTunnel,FSingleThreadRunnable`
- desc: Implements a bi-directional tunnel to send UDP messages over a TCP connection.
- L48 _public prototype_ `FUdpMessageTunnel(const FIPv4Endpoint& InUnicastEndpoint, const FIPv4Endpoint& InMulticastEndpoint);` — Creates and initializes a new instance. @param InUnicastEndpoint The local IP endpoint to receive messages on. @param InMulticastEndpoint The multicast group endpoint to transport messages to.
- L51 _public prototype_ `virtual ~FUdpMessageTunnel();` — Virtual destructor.
- L57 _public prototype_ `virtual FSingleThreadRunnable* GetSingleThreadInterface() override;`
- L58 _public prototype_ `virtual bool Init() override;`
- L59 _public prototype_ `virtual uint32 Run() override;`
- L60 _public prototype_ `virtual void Stop() override;`
- L61 _public prototype_ `virtual void Exit() override;`
- L67 _public prototype_ `virtual bool Connect(const FIPv4Endpoint& RemoteEndpoint) override;`
- L68 _public prototype_ `virtual int32 GetConnections(TArray<TSharedPtr<IUdpMessageTunnelConnection>>& OutConnections) override;`
- L69 _public prototype_ `virtual uint64 GetTotalInboundBytes() const override;`
- L70 _public prototype_ `virtual uint64 GetTotalOutboundBytes() const override;`
- L71 _public prototype_ `virtual bool IsServerRunning() const override;`
- L72 _public prototype_ `virtual FSimpleDelegate& OnConnectionsChanged() override;`
- L73 _public prototype_ `virtual void StartServer(const FIPv4Endpoint& LocalEndpoint) override;`
- L74 _public prototype_ `virtual void StopServer() override;`
- L83 _protected prototype_ `void RemoveExpiredNodes(TMap<FGuid, FNodeInfo>& Nodes);` — Removes expired nodes from the specified collection of node infos. @param Nodes The collection of nodes to clean up.
- L90 _protected prototype_ `void TcpToUdp();` — Receives all pending payloads from the tunnels and forwards them to the local message bus. @see UdpToTcp
- L98 _protected prototype_ `void UdpToTcp(FSocket* Socket);` — Receives all buffered datagrams from the specified socket and forwards them to the tunnels. @param Socket The socket to receive from. @see TcpToUdp
- L101 _protected prototype_ `void Update();` — Update the tunnel.
- L104 _protected prototype_ `void UpdateConnections();` — Updates all active and pending connections.
- L110 _protected prototype_ `virtual void Tick() override;`
- L115 _private prototype_ `bool HandleListenerConnectionAccepted(FSocket* ClientSocket, const FIPv4Endpoint& ClientEndpoint);` — Callback for accepted connections to the local tunnel server.
- L120 _private member_ `TArray<TSharedPtr<FUdpMessageTunnelConnection>> Connections;` — Holds the list of open tunnel connections.
- L123 _private member_ `FCriticalSection CriticalSection;` — Holds a critical section for serializing access to the connections list.
- L126 _private member_ `FDateTime CurrentTime;` — Holds the current time.
- L129 _private member_ `FTcpListener* Listener;` — Holds the local listener for incoming tunnel connections.
- L132 _private member_ `TMap<FGuid, FNodeInfo> LocalNodes;` — Holds a collection of information for local transport nodes.
- L135 _private member_ `FIPv4Endpoint MulticastEndpoint;` — Holds the multicast endpoint.
- L138 _private member_ `FSocket* MulticastSocket;` — Holds the multicast socket.
- L141 _private member_ `TMpscQueue<TSharedPtr<FUdpMessageTunnelConnection>> PendingConnections;` — Holds a queue of pending connections.
- L144 _private member_ `TMap<FGuid, FNodeInfo> RemoteNodes;` — Holds a collection of information for remote transport nodes.
- L147 _private member_ `bool Stopping;` — Holds a flag indicating that the thread is stopping.
- L150 _private member_ `FRunnableThread* Thread;` — Holds the thread object.
- L153 _private member_ `uint64 TotalInboundBytes;` — Holds the total number of bytes that were received from tunnels.
- L156 _private member_ `uint64 TotalOutboundBytes;` — Holds the total number of bytes that were sent out through tunnels.
- L159 _private member_ `FSocket* UnicastSocket;` — Holds the unicast socket.
- L164 _private member_ `FSimpleDelegate ConnectionsChangedDelegate;` — Holds a delegate that is executed when the list of incoming connections changed.

#### struct `FUdpMessageTunnel::FNodeInfo`  
`struct FNodeInfo`  
_L28-38_
- desc: Structure for transport node information.
- L31 _public member_ `TSharedPtr<FUdpMessageTunnelConnection> Connection;` — Holds the connection that owns the node (only used for remote nodes).
- L34 _public member_ `FIPv4Endpoint Endpoint;` — Holds the node's IP endpoint (only used for local nodes).
- L37 _public member_ `FDateTime LastDatagramReceivedTime;` — Holds the time at which the last datagram was received.

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/Tunnel/UdpMessageTunnelConnection.h` (Private)


#### class `FUdpMessageTunnelConnection`  
`class FUdpMessageTunnelConnection : public FRunnable , public TSharedFromThis<FUdpMessageTunnelConnection> , public IUdpMessageTunnelConnection`  
_L20-126_
- inherits: `FRunnable,TSharedFromThis<FUdpMessageTunnelConnection>,IUdpMessageTunnelConnection`
- desc: Implements a UDP message tunnel connection.
- L33 _public prototype_ `FUdpMessageTunnelConnection(FSocket* InSocket, const FIPv4Endpoint& InRemoteEndpoint);` — Creates and initializes a new instance. @param InSocket The socket to use for this connection. @param InRemoteAddress The IP endpoint of the remote client.
- L36 _public prototype_ `virtual ~FUdpMessageTunnelConnection();` — Virtual destructor.
- L47 _public prototype_ `bool Receive(TSharedPtr<FArrayReader, ESPMode::ThreadSafe>& OutPayload);` — Receives a payload from the connection's inbox. @param OutPayload Will hold the received payload, if any. @return true if a payload was returned, false otherwise. @see Send
- L55 _public prototype_ `bool Send(const TSharedPtr<FArrayReader, ESPMode::ThreadSafe>& Payload);` — Sends a payload through this connection. @param Payload The payload to send. @see Receive
- L61 _public prototype_ `virtual bool Init() override;`
- L62 _public prototype_ `virtual uint32 Run() override;`
- L63 _public prototype_ `virtual void Stop() override;`
- L64 _public prototype_ `virtual void Exit() override;`
- L70 _public prototype_ `virtual void Close() override;`
- L71 _public prototype_ `virtual uint64 GetTotalBytesReceived() const override;`
- L72 _public prototype_ `virtual uint64 GetTotalBytesSent() const override;`
- L73 _public prototype_ `virtual FText GetName() const override;`
- L74 _public prototype_ `virtual FTimespan GetUptime() const override;`
- L75 _public prototype_ `virtual bool IsOpen() const override;`
- L85 _protected prototype_ `bool ReceivePayloads();` — Receives all pending payloads from the socket. @return true on success, false otherwise. @see SendPayloads
- L93 _protected prototype_ `bool SendPayloads();` — Sends all pending payloads to the socket. @return true on success, false otherwise. @see ReceivePayloads
- L98 _private member_ `FDateTime ClosedTime;` — Holds the time at which the connection was closed.
- L101 _private member_ `TSpscQueue<TSharedPtr<FArrayReader, ESPMode::ThreadSafe>> Inbox;` — Holds the collection of received payloads.
- L104 _private member_ `FDateTime OpenedTime;` — Holds the time at which the connection was opened.
- L107 _private member_ `TSpscQueue<TSharedPtr<FArrayReader, ESPMode::ThreadSafe>> Outbox;` — Holds the collection of outbound payloads.
- L110 _private member_ `FIPv4Endpoint RemoteEndpoint;` — Holds the IP endpoint of the remote client.
- L113 _private member_ `FSocket* Socket;` — Holds the connection socket.
- L116 _private member_ `FRunnableThread* Thread;` — Holds the thread object.
- L119 _private member_ `uint64 TotalBytesReceived;` — Holds the total number of bytes received from the connection.
- L122 _private member_ `uint64 TotalBytesSent;` — Holds the total number of bytes sent to the connection.
- L125 _private member_ `bool bRun;` — thread should continue running.

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Private/UdpMessagingPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUdpMessaging, Log, All);` — Declares a log category for this module.
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUdpMessaging, Log, All);` — Declares a log category for this module.
- L13 _macro_ `#define UDP_MESSAGING_DEFAULT_MULTICAST_ENDPOINT FIPv4Endpoint(FIPv4Address(230, 0, 0, 1), 6666)` — Defines the default IP endpoint for multicast traffic.
- L16 _macro_ `#define UDP_MESSAGING_MAX_ANNOTATIONS 128` — Defines the maximum number of annotations a message can have.
- L19 _macro_ `#define UDP_MESSAGING_MAX_RECIPIENTS 1024` — Defines the maximum number of recipients a message can have.
- L22 _macro_ `#define UDP_MESSAGING_RECEIVE_BUFFER_SIZE 2 * 1024 * 1024` — Defines the desired size of socket receive buffers (in bytes).
- L28 _macro_ `#define UDP_MESSAGING_TRANSPORT_PROTOCOL_VERSION 18` — Defines the protocol version of the UDP message transport. @note When changing the version, ensure to update the serialization/deserialization code in UdpSerializeMessageTask.cpp/UdpDeserializedMessage.cpp and the supported versions in FUdpMessageProcessor::Init().
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace UdpMessaging` (scope `UE`)
- L70 _variable_ `constexpr uint16 Ipv4HeaderBytes = 20;` (scope `UE::UdpMessaging`) — Technically minimum, but almost always holds in practice.
- L71 _variable_ `constexpr uint16 UdpHeaderBytes = 8;` (scope `UE::UdpMessaging`)
- L72 _variable_ `constexpr uint16 PacketHeaderBytes = Ipv4HeaderBytes + UdpHeaderBytes;` (scope `UE::UdpMessaging`)

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Public/IUdpMessageTunnel.h` (Public)


#### class `IUdpMessageTunnel`  
`class IUdpMessageTunnel`  
_L15-89_
- desc: Interface for message tunnels.
- L26 _public prototype_ `virtual bool Connect(const FIPv4Endpoint& RemoteEndpoint) = 0;` — Establishes a tunnel with a remote server. @param RemoteEndpoint The endpoint of the server to connect to. @return true if the connection has been established, false otherwise. @see GetConnections
- L34 _public prototype_ `virtual void StartServer(const FIPv4Endpoint& LocalEndpoint) = 0;` — Starts the tunnel server. @param LocalEndpoint The IP endpoint to listen for incoming connections on. @see IsServerRunning, StopServer
- L41 _public prototype_ `virtual void StopServer() = 0;` — Stops the tunnel server. @see IsServerRunning, StartServer
- L52 _public prototype_ `virtual int32 GetConnections(TArray<TSharedPtr<IUdpMessageTunnelConnection>>& OutConnections) = 0;` — Gets the list of all open tunnel connections. @param OutConnections Will hold the list of connections. @return The number of connections returned. @see Connect
- L59 _public prototype_ `virtual uint64 GetTotalInboundBytes() const = 0;` — Gets the total number of bytes that were received from tunnels. @return Number of bytes.
- L66 _public prototype_ `virtual uint64 GetTotalOutboundBytes() const = 0;` — Gets the total number of bytes that were sent out through tunnels. @return Number of bytes.
- L74 _public prototype_ `virtual bool IsServerRunning() const = 0;` — Checks whether the tunnel server is running. @return true if the tunnel server is running, false otherwise. @see StartServer, StopServer
- L83 _public prototype_ `virtual FSimpleDelegate& OnConnectionsChanged() = 0;` — Gets a delegate that is executed when the list of incoming connections changed. @return The delegate.
- L88 _public prototype_ `virtual ~IUdpMessageTunnel() = default;` — Virtual destructor.

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Public/IUdpMessageTunnelConnection.h` (Public)


#### class `IUdpMessageTunnelConnection`  
`class IUdpMessageTunnelConnection`  
_L14-60_
- desc: Interface for message tunnel connections.
- L19 _public prototype_ `virtual void Close() = 0;` — Closes this connection.
- L26 _public prototype_ `virtual uint64 GetTotalBytesReceived() const = 0;` — Gets the total number of bytes received from this connection. @return Number of bytes.
- L33 _public prototype_ `virtual uint64 GetTotalBytesSent() const = 0;` — Gets the total number of bytes received from this connection. @return Number of bytes.
- L40 _public prototype_ `virtual FText GetName() const = 0;` — Gets the human readable name of the connection. @return Connection name.
- L47 _public prototype_ `virtual FTimespan GetUptime() const = 0;` — Gets the amount of time that the connection has been established. @return Time span.
- L54 _public prototype_ `virtual bool IsOpen() const = 0;` — Checks whether this connection is open. @return true if the connection is open, false otherwise.
- L59 _public prototype_ `virtual ~IUdpMessageTunnelConnection() = default;` — Virtual destructor.

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Public/Shared/UdpMessagingSettings.h` (Public)


#### enum `EUdpMessageFormat`  
`enum class EUdpMessageFormat : uint8`  
_L10-32_
- reflection: `UENUM()`
- desc: Defines the UDP message format available (how the message data is encoded).
- L13 _public enumerator_ `None = 0 UMETA(Hidden)` — No format specified. Legacy - Not exposed to user.
- L16 _public enumerator_ `Json UMETA(Hidden)` — JSON format specified. Legacy - Not exposed to user.
- L19 _public enumerator_ `TaggedProperty UMETA(Hidden)` — Tagged property format specified. Legacy - Not exposed to user.
- L25 _public enumerator_ `CborPlatformEndianness UMETA(DisplayName="CBOR (Platform Endianness)")` — UDP messages are encoded in CBOR, using the platform endianness. This is the fastest and preferred option, but the CBOR data will not be readable by an external standard-compliant CBOR parser if generated from a little endian platform. If the data needs to be consumed outside the Unreal Engine, consider using CborStandardEndianness format instead.
- L31 _public enumerator_ `CborStandardEndianness UMETA(DisplayName="CBOR (Standard Endianness)")` — UDP messages are encoded in CBOR, using the CBOR standard-complinant endianness (big endian). It will perform slower on a little-endian platform, but the data will be readable by standard CBOR parsers. Useful if the UDP messages needs to be analyzed/consumed outside the Unreal Engine.

#### class `UUdpMessagingSettings`  
`class UUdpMessagingSettings : public UObject`  
_L35-233_
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- L50 _public member_ `bool EnabledByDefault = false;` — `UPROPERTY(config, EditAnywhere, Category = Availability)` — Whether UDP messaging is enabled by default. If false -messaging will need to be added to the commandline when running non-editor builds. (Note - in Shipping builds ALLOW_UDP_MESSAGING_SHIPPING=1 must also be defined in TargetRules for messaging to be available with or without this setting)
- L57 _public member_ `bool EnableTransport;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — Whether the UDP transport channel is enabled. Can be specified on the command line with `-UDPMESSAGING_TRANSPORT_ENABLE=`
- L61 _public member_ `bool bAutoRepair = true;` — `UPROPERTY(config, EditAnywhere, Category=Transport, AdvancedDisplay)` — Whether the UDP transport channel should try to auto repair when in error.
- L75 _public member_ `float MaxSendRate = 1.0f;` — `UPROPERTY(config, EditAnywhere, Category=Transport, meta = (ClampMin="0.01", ClampMax="100.0"), AdvancedDisplay)` — Maximum sustained transmission rate in Gbit / s. The default value is 1 Gbit/s. This is to control transmission of larger packages over the network. Without a limit, it is possible for packet data loss to occur because more data may be sent then may be supported by your network card. Adjust this value higher or lower depending on your network capacity.
- L77 _public member_ `static constexpr float MaxSendRate_Min = 0.01f;`
- L78 _public member_ `static constexpr float MaxSendRate_Max = 100.0f;`
- L81 _public function_ `float GetMaxSendRate() const` — Accessor that ensures MaxSendRate is clamped to the expected bounds.
- L88 _public member_ `uint32 AutoRepairAttemptLimit = 10;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — The number of consecutive attempt the auto repair routine will try to repair.
- L92 _public member_ `uint16 WorkQueueSize = 1024;` — `UE_DEPRECATED(5.8, "UDP Messaging work queues are no longer fixed size.")` — `UPROPERTY(meta=(DeprecatedProperty))`
- L103 _public member_ `uint16 MaxPacketSize = 1130;` — `UPROPERTY(config, EditAnywhere, Category = Transport, meta = (ClampMin="576", ClampMax="65535"), AdvancedDisplay)` — The maximum packet size to use for message segments (including presumed 20 byte IPv4 + 8 byte UDP headers). This should be less than or equal to your path maximum transmission unit (PMTU) to avoid fragmentation. Previous versions of UDP Messaging were hard-coded to 1130, which is a conservative, internet-safe value. If your traffic is restricted to the local network, support for an MTU of 1500 is common. This can be increased further by enabling jumbo frames on supported hardware.
- L105 _public member_ `static constexpr uint16 MaxPacketSize_Min = 576;`
- L106 _public member_ `static constexpr uint16 MaxPacketSize_Max = 65535;`
- L109 _public function_ `uint16 GetMaxPacketSize() const` — Accessor that ensures MaxPacketSize is clamped to the expected bounds.
- L116 _public member_ `bool bSegmentationOffload = false;` — `UPROPERTY(config, EditAnywhere, Category = Transport, AdvancedDisplay)` — Enable UDP segmentation offload.
- L123 _public member_ `float ReliableQueuePriority = 75.0f;` — `UPROPERTY(config, EditAnywhere, Category = Transport, meta = (ClampMin="5", ClampMax="95"), AdvancedDisplay)` — Reliable queue priority specified as a percentage with a range from 5-95%. Setting values above or below can completely starve unreliable messages.
- L127 _public member_ `bool bStopServiceWhenAppDeactivates = true;` — `UPROPERTY(config)` — Whether to stop the transport service when the application deactivates, and restart it when the application is reactivated
- L140 _public member_ `FString UnicastEndpoint;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — The IP endpoint to listen to and send packets from. The format is IP_ADDRESS:PORT_NUMBER. 0.0.0.0:0 will bind to the default network adapter on Windows, and all available network adapters on other operating systems. Specifying an interface IP here, will use that interface for multicasting and static endpoint *might* also reach this client through <unicast ip:multicast port> Specifying both the IP and Port will allow usage of static endpoint to reach this client Can be specified on the command line with `-UDPMESSAGING_TRANSPORT_UNICAST=`
- L150 _public member_ `FString MulticastEndpoint;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — The IP endpoint to send multicast packets to. The format is IP_ADDRESS:PORT_NUMBER. The multicast IP address must be in the range 224.0.0.0 to 239.255.255.255. Can be specified on the command line with `-UDPMESSAGING_TRANSPORT_MULTICAST=`
- L154 _public member_ `EUdpMessageFormat MessageFormat = EUdpMessageFormat::CborPlatformEndianness;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — The format used to serialize the UDP message payload.
- L158 _public member_ `uint8 MulticastTimeToLive;` — `UPROPERTY(config, EditAnywhere, Category=Transport, AdvancedDisplay)` — The time-to-live (TTL) for sent multicast packets.
- L167 _public member_ `TArray<FString> StaticEndpoints;` — `UPROPERTY(config, EditAnywhere, Category=Transport, AdvancedDisplay)` — The IP endpoints of static devices. Use this setting to reach devices on other subnets, such as mobile phones on a WiFi network. The format is IP_ADDRESS:PORT_NUMBER.
- L179 _public member_ `TArray<FString> ExcludedEndpoints;` — `UPROPERTY(config, EditAnywhere, Category=Transport, AdvancedDisplay)` — List of IP addresses that are banned from communicating with this client. Wildcard IPv4 addresses can be specified by using '*' and '?' characters. For example, 192.168.12.* will deny all addresses on the .12 subnet for the class C network. The string 192.16?.12.10 will deny all addresses in the range 192.160.12.10-192.169.12.10. The format is IP_ADDRESS:PORT_NUMBER.  If port number is 0 then all ports are blocked.
- L185 _public member_ `bool bShareKnownNodesWithActiveConnections = false;` — `UPROPERTY(config, EditAnywhere, Category=Transport, AdvancedDisplay)` — Whether to share our list of known endpoints with those endpoints.  This allows message processors to completely mesh their networks.
- L192 _public member_ `uint32 MaxConcurrentDeserializationTasks = 8;` — `UPROPERTY(config, EditAnywhere, Category=Transport, meta = (ClampMax="32"), AdvancedDisplay)` — Maximum number of deserialization tasks that can be performed in parallel. A value of 0 or 1 means that concurrent deserialization is disabled, which will make the message processor behave similar to releases pre-5.6.
- L200 _public member_ `float ConnectionTimeoutPeriod = 5.0f;` — `UPROPERTY(config, EditAnywhere, Category=Transport, meta = (ClampMin="0"), AdvancedDisplay)` — The period of time to consider an active connection to be timed-out. A regular heart beat is expected from connected endpoints and this will expire that connection if no data is received after a period of time.  If zero is specified the endpoints are never timed out (this should only be used for debugging purposes).
- L206 _public member_ `bool EnableTunnel;` — `UPROPERTY(config, EditAnywhere, Category=Tunnel)` — Whether the UDP tunnel is enabled.
- L214 _public member_ `FString TunnelUnicastEndpoint;` — `UPROPERTY(config, EditAnywhere, Category=Tunnel)` — The local IP endpoint to listen to and send packets from. The format is IP_ADDRESS:PORT_NUMBER.
- L223 _public member_ `FString TunnelMulticastEndpoint;` — `UPROPERTY(config, EditAnywhere, Category=Tunnel)` — The IP endpoint to send multicast packets to. The format is IP_ADDRESS:PORT_NUMBER. The multicast IP address must be in the range 224.0.0.0 to 239.255.255.255.
- L232 _public member_ `TArray<FString> RemoteTunnelEndpoints;` — `UPROPERTY(config, EditAnywhere, Category=Tunnel, AdvancedDisplay)` — The IP endpoints of remote tunnel nodes. Use this setting to connect to remote tunnel services. The format is IP_ADDRESS:PORT_NUMBER.

### `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Public/UdpMessagingTracing.h` (Public)
_(no declarations extracted)_
