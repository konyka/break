# Plugins / MQTTCore

- module root: `Plugins/Protocols/MQTT/Source/MQTTCore`
- headers: 15; symbols: 631
- symbol kinds: class=28, delegate=17, enum=12, enumerator=132, function=89, macro=5, member=141, namespace=2, prototype=175, struct=23, typedef=6, variable=1

### `Plugins/Protocols/MQTT/Source/MQTTCore/Private/MQTTClient.h` (Private)


#### class `FMQTTClient`  
`class FMQTTClient final : public IMQTTClient , public TSharedFromThis<FMQTTClient, ESPMode::ThreadSafe>`  
_L11-64_
- inherits: `IMQTTClient,TSharedFromThis<FMQTTClient,ESPMode::ThreadSafe>`
- L16 _public prototype_ `explicit FMQTTClient(const FMQTTURL& InURL);`
- L20 _public function_ `virtual FOnConnect& OnConnect() override`
- L21 _public function_ `virtual FOnDisconnect& OnDisconnect() override`
- L22 _public function_ `virtual FOnPublish& OnPublish() override`
- L23 _public function_ `virtual FOnMessage& OnMessage() override`
- L24 _public function_ `virtual FOnSubscribe& OnSubscribe() override`
- L25 _public function_ `virtual FOnUnsubscribe& OnUnsubscribe() override`
- L27 _public function_ `virtual FGuid GetClientId() const override`
- L29 _public function_ `virtual const FMQTTURL& GetURL() const override`
- L31 _public prototype_ `virtual TFuture<EMQTTConnectReturnCode> Connect(bool bCleanSession = true) override;`
- L32 _public prototype_ `virtual TFuture<void> Disconnect() override;`
- L34 _public prototype_ `virtual TFuture<bool> Publish(const FString& InTopic, const TArray<uint8>& InPayload, EMQTTQualityOfService InQoS = EMQTTQualityOfService::Once, const bool bInRetain = false) override;`
- L35 _public prototype_ `virtual TFuture<bool> Publish(const FString& InTopic, const FString& InPayload, EMQTTQualityOfService InQoS = EMQTTQualityOfService::Once, const bool bInRetain = false) override;`
- L36 _public prototype_ `virtual TFuture<TArray<FMQTTSubscribeResult>> Subscribe(const TArray<TPair<FString, EMQTTQualityOfService>>& InTopicFilterQoSPairs) override;`
- L37 _public prototype_ `virtual TFuture<bool> Unsubscribe(const TSet<FString>& InTopicFilters) override;`
- L38 _public prototype_ `virtual TFuture<bool> Ping(const float& InTimeout = 2.0f) override;`
- L40 _public prototype_ `virtual bool IsConnected() const override;`
- L42 _public prototype_ `virtual bool IsValid() const override;`
- L46 _protected prototype_ `TSharedPtr<FMQTTSubscription, ESPMode::ThreadSafe>& MakeSubscription(const FString& InTopicFilter, EMQTTQualityOfService InGrantedQoS);`
- L47 _protected prototype_ `void OnMessagePacket(const FMQTTPublishPacket& InPacket);`
- L50 _private member_ `TSharedPtr<FMQTTConnection, ESPMode::ThreadSafe> Connection;`
- L52 _private member_ `FOnConnect OnConnectDelegate;`
- L53 _private member_ `FOnDisconnect OnDisconnectDelegate;`
- L54 _private member_ `FOnPublish OnPublishDelegate;`
- L55 _private member_ `FOnSubscribe OnSubscribeDelegate;`
- L56 _private member_ `FOnUnsubscribe OnUnsubscribeDelegate;`
- L57 _private member_ `FOnMessage OnMessageDelegate;`
- L59 _private member_ `FGuid ClientId;`
- L60 _private member_ `FMQTTURL URL;`
- L62 _private member_ `mutable FCriticalSection SubscriptionsLock;`
- L63 _private member_ `TMap<FName, TSharedPtr<FMQTTSubscription, ESPMode::ThreadSafe>> Subscriptions;`

### `Plugins/Protocols/MQTT/Source/MQTTCore/Private/MQTTConnection.h` (Private)


#### class `FMQTTPacketIdGenerator`  
`class FMQTTPacketIdGenerator`  
_L30-44_
- desc: A wrapped unique (per client) id generator.
- L33 _public prototype_ `FMQTTPacketIdGenerator();`
- L35 _public prototype_ `uint16 Pop();`
- L37 _public prototype_ `void Push(const uint16 InValue);`
- L40 _protected member_ `static constexpr uint16 Max = TNumericLimits<uint16>::Max();`
- L41 _protected member_ `std::atomic<uint16> Min;` — Current index of next slot to be returned
- L42 _protected member_ `std::atomic<uint16> Position;` — Current index of slot ready to go
- L43 _protected member_ `TStaticArray<uint16, Max> ValueStore;`

#### class `FMQTTConnection`  
`class FMQTTConnection final : public FRunnable , public FSingleThreadRunnable , public TSharedFromThis<FMQTTConnection, ESPMode::ThreadSafe>`  
_L47-149_
- inherits: `FRunnable,FSingleThreadRunnable,TSharedFromThis<FMQTTConnection,ESPMode::ThreadSafe>`
- desc: Socket connection.
- L57 _protected prototype_ `explicit FMQTTConnection( FSocket& InSocket, TSharedRef<FInternetAddr> InAddr);` — Constructor. Hidden on purpose, use Create instead.
- L64 _public prototype_ `static TSharedPtr<FMQTTConnection, ESPMode::ThreadSafe> TryCreate(const TSharedPtr<FInternetAddr>& InAddr);`
- L67 _public prototype_ `template <class OperationType> auto QueueOperation(typename OperationType::FRequestType&& InRequestPacket) -> TFuture<typename OperationType::FResponseType>;`
- L69 _public function_ `EMQTTState GetState() const`
- L70 _public prototype_ `void SetState(const EMQTTState InState);`
- L73 _public prototype_ `uint16 PopId();` — Get new message Id.
- L76 _public prototype_ `void PushId(uint16 InValue);` — Add message Id back to pool.
- L78 _public prototype_ `bool IsConnected() const;`
- L80 _public function_ `DECLARE_DELEGATE_OneParam(FOnMessage, const FMQTTPublishPacket& ) FOnMessage& OnMessage()`
- L85 _protected prototype_ `virtual bool Init() override;`
- L86 _protected prototype_ `virtual uint32 Run() override;`
- L87 _protected prototype_ `virtual void Stop() override;`
- L88 _protected prototype_ `virtual void Exit() override;`
- L92 _protected prototype_ `virtual void Tick() override;`
- L93 _protected prototype_ `virtual class FSingleThreadRunnable* GetSingleThreadInterface() override;`
- L97 _protected prototype_ `bool UpdateConnection();` — Updates the socket connection and resulting state. Return true if connected.
- L98 _protected prototype_ `void ProcessMessages();`
- L100 _protected prototype_ `void OpenSocket();`
- L102 _protected member_ `FCriticalSection OutgoingQueueLock;`
- L103 _protected member_ `FCriticalSection IncomingQueueLock;`
- L104 _protected member_ `TQueue<TUniquePtr<IMQTTOperation>, EQueueMode::Spsc> OutgoingOperations;`
- L105 _protected member_ `TUniquePtr<TMQTTOperation<FMQTTConnectPacket, FMQTTConnectAckPacket>> PendingConnectOperation;`
- L106 _protected member_ `TUniquePtr<IMQTTOperation> PendingPingOperation;`
- L107 _protected member_ `TMap<uint16, TUniquePtr<IMQTTOperation>> PendingIncomingOperations;` — Waiting for ack's, etc.
- L109 _protected member_ `std::atomic<EMQTTSocketState> SocketState;`
- L110 _protected member_ `std::atomic<EMQTTState> MQTTState;`
- L112 _protected member_ `FCriticalSection MessageIdGeneratorLock;`
- L113 _protected member_ `FMQTTPacketIdGenerator MessageIdGenerator;`
- L116 _private prototype_ `void AbandonOperations();`
- L117 _private prototype_ `void HandleMessage(EMQTTPacketType InMessageType, const TSharedRef<FArrayReader>& InPacketReader);`
- L118 _private prototype_ `void HandleConnectAcknowledge(const TSharedRef<FArrayReader>& InPacketReader);`
- L119 _private prototype_ `void HandleSubscribeAcknowledge(const TSharedRef<FArrayReader>& InPacketReader);`
- L120 _private prototype_ `void HandleUnsubscribeAcknowledge(const TSharedRef<FArrayReader>& InPacketReader);`
- L121 _private prototype_ `void HandlePingResponse(const TSharedRef<FArrayReader>& InPacketReader);`
- L122 _private prototype_ `void HandlePublish(const TSharedRef<FArrayReader>& InPacketReader);`
- L123 _private prototype_ `void HandlePublishAcknowledge(const TSharedRef<FArrayReader>& InPacketReader);`
- L124 _private prototype_ `void HandlePublishReceived(const TSharedRef<FArrayReader>& InPacketReader);`
- L125 _private prototype_ `void HandlePublishRelease(const TSharedRef<FArrayReader>& InPacketReader);`
- L126 _private prototype_ `void HandlePublishComplete(const TSharedRef<FArrayReader>& InPacketReader);`
- L130 _private member_ `FSocket* Socket;` — The network socket (incoming).
- L133 _private member_ `TSharedPtr<FInternetAddr> EndpointInternetAddr;` — The endpoint internet addr
- L136 _private member_ `FRunnableThread* Thread;` — The thread object.
- L139 _private member_ `FString ThreadName;` — The receiver thread's name.
- L142 _private member_ `FOnMessage OnMessageDelegate;` — Used when any message is received (publish packet).
- L144 _private member_ `float SocketConnectionTimeout = 10.0f;` — in seconds
- L145 _private member_ `float MQTTConnectionTimeout = 10.0f;` — in seconds
- L146 _private member_ `double LastConnectRequestTime = 0.0f;` — in seconds
- L147 _private member_ `float KeepAliveInterval = 60.0f;` — in seconds
- L148 _private member_ `double LastKeepAliveTime = 0.0f;`
- L152 _function_ `template <class OperationType> auto FMQTTConnection::QueueOperation(typename OperationType::FRequestType&& InRequestPacket) -> TFuture<typename OperationType::FResponseType>`

#### Free symbols / members of external scopes

- L80 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMessage, const FMQTTPublishPacket& ) FOnMessage& OnMessage() { return OnMessageDelegate; } protected:`
- L155 _typedef_ `using RequestType = typename OperationType::FRequestType;` (scope `FMQTTConnection::QueueOperation`)
- L156 _typedef_ `using ResponseType = typename OperationType::FResponseType;` (scope `FMQTTConnection::QueueOperation`)

### `Plugins/Protocols/MQTT/Source/MQTTCore/Private/MQTTCoreLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMQTTCore, VeryVerbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMQTTCore, VeryVerbose, All);`

### `Plugins/Protocols/MQTT/Source/MQTTCore/Private/MQTTCoreModule.h` (Private)


#### class `FMQTTCoreModule`  
`class FMQTTCoreModule : public IMQTTCoreModule`  
_L10-48_
- inherits: `IMQTTCoreModule`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `virtual TSharedPtr<IMQTTClient, ESPMode::ThreadSafe> GetOrCreateClient(bool bForceNew = false) override;`
- L20 _public prototype_ `virtual TSharedPtr<IMQTTClient, ESPMode::ThreadSafe> GetOrCreateClient(const FMQTTURL& InURL, bool bForceNew = false) override;`
- L25 _private prototype_ `void RegisterConsoleCommands();` — Register console commands.
- L28 _private prototype_ `void UnregisterConsoleCommands();` — Unregister console commands.
- L30 _private prototype_ `void OnCreateClientCommand(const TArray<FString>& InArgs);`
- L31 _private prototype_ `void OnDestroyClientCommand(const TArray<FString>& InArgs);`
- L33 _private prototype_ `void OnClientSubscribeCommand(const TArray<FString>& InArgs);`
- L34 _private prototype_ `void OnClientUnsubscribeCommand(const TArray<FString>& InArgs);`
- L35 _private prototype_ `void OnClientPublishCommand(const TArray<FString>& InArgs);`
- L37 _private prototype_ `void OnEndPlay();`
- L40 _protected prototype_ `TSharedPtr<IMQTTClient, ESPMode::ThreadSafe> FindClient(FGuid InId);`
- L41 _protected prototype_ `virtual int32 GetClientNum() const override;`
- L44 _private member_ `TMap<FGuid, TWeakPtr<IMQTTClient, ESPMode::ThreadSafe>> MQTTClients;`
- L47 _private member_ `TArray<TUniquePtr<FAutoConsoleCommand>> ConsoleCommands;` — Console commands handles.

### `Plugins/Protocols/MQTT/Source/MQTTCore/Private/MQTTCoreStats.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_STATS_GROUP(TEXT("MQTT"), STATGROUP_MQTT, STATCAT_Advanc`

### `Plugins/Protocols/MQTT/Source/MQTTCore/Private/MQTTOperations.h` (Private)


#### struct `FMQTTFixedHeader`  
`struct FMQTTFixedHeader`  
_L12-42_
- L14 _public member_ `uint8 PacketType = static_cast<uint8>(EMQTTPacketType::Connect);`
- L15 _public member_ `uint8 Reserved = 0;`
- L16 _public member_ `uint8 LengthFieldSize = 1;` — 1 - 4 depending on int precision
- L17 _public member_ `uint16 RemainingLength = 0;` — Length of variable header (10 bytes) + payload length
- L18 _public member_ `uint16 TotalLength = 0;`
- L20 _public function_ `EMQTTPacketType GetPacketType() const`
- L25 _public function_ `void SetPacketType(EMQTTPacketType InPacketType)`
- L30 _public prototype_ `int64 HeaderSize() const;`
- L31 _public prototype_ `int64 TotalSize() const;`
- L33 _public prototype_ `void Serialize(FArchive& Ar);`
- L38 _protected prototype_ `static uint8 ReadHeader(FArchive& InArchive, FMQTTFixedHeader& OutHeader);` — Reads from Archive and writes to Header. Returns size of Length field (1-4 bytes).
- L41 _protected prototype_ `static uint8 WriteHeader(FArchive& InArchive, const FMQTTFixedHeader& InHeader);` — Reads from Header and writes to Archive. Returns size of Length field (1-4 bytes).

#### struct `FMQTTPacket`  
`struct FMQTTPacket`  
_L44-57_
- L47 _public member_ `uint16 PacketId = 0;` — Not needed for certain packets, but practical for templating purposes
- L49 _public prototype_ `FMQTTPacket() = default;`
- L50 _public prototype_ `virtual ~FMQTTPacket() = default;`
- L53 _public function_ `int32 GetLength() const` — Get's the "RemainingLength" field. Mainly used for testing/verification.
- L56 _protected member_ `FMQTTFixedHeader FixedHeader;`

#### struct `FMQTTConnectPacket`  
`struct FMQTTConnectPacket : FMQTTPacket`  
_L59-98_
- inherits: `FMQTTPacket`
- L61 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::Connect;`
- L63 _public function_ `explicit FMQTTConnectPacket( FString InClientId, const uint16 InKeepAliveSeconds = 60, FString InUserName = "", FString InPassword = "", const bool bInCleanSession = false, const bool bInRetainWill = false, FString InWillTopic = "", FString InWillMessage = "", const EMQTTQualityOfService InWillQoS = EMQTTQualityOfService::Once) : ClientId(MoveTemp(InClientId)) , KeepAliveSeconds(InKeepAliveSeconds) , UserName(MoveTemp(InUserName)) , Password(MoveTemp(InPassword)) , bCleanSession(bInCleanSession) , bRetainWill(bInRetainWill) , WillTopic(MoveTemp(InWillTopic)) , WillMessage(MoveTemp(InWillMessage)) , WillQoS(InWillQoS)`
- L85 _public member_ `FString ClientId;`
- L86 _public member_ `uint16 KeepAliveSeconds = 60;`
- L87 _public member_ `FString UserName;`
- L88 _public member_ `FString Password;`
- L89 _public member_ `bool bCleanSession;`
- L90 _public member_ `bool bRetainWill;`
- L91 _public member_ `FString WillTopic;`
- L92 _public member_ `FString WillMessage;`
- L93 _public member_ `EMQTTQualityOfService WillQoS;`
- L95 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTConnectAckPacket`  
`struct FMQTTConnectAckPacket : FMQTTPacket`  
_L100-119_
- inherits: `FMQTTPacket`
- L102 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::ConnectAcknowledge;`
- L104 _public prototype_ `FMQTTConnectAckPacket() = default;`
- L107 _public function_ `explicit FMQTTConnectAckPacket(const EMQTTConnectReturnCode& InReturnCode) : Flags(0) , ReturnCode(InReturnCode)` — Short circuit when there's a connection error.
- L113 _public member_ `uint8 Flags;` — if clean session from client is 1, this should be 0, if from client is 0, this should be 1 if client session stored, or 0 if not
- L114 _public member_ `EMQTTConnectReturnCode ReturnCode;`
- L116 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTPublishPacket`  
`struct FMQTTPublishPacket : FMQTTPacket`  
_L122-153_
- inherits: `FMQTTPacket`
- desc: @todo: for MQTT 5, properties, end of the message, pg25 of spec
- L124 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::Publish;`
- L126 _public prototype_ `FMQTTPublishPacket() = default;`
- L128 _public function_ `explicit FMQTTPublishPacket( const uint16 InPacketId, FString InTopic, const TArray<uint8> InPayload, const EMQTTQualityOfService InQoS, const bool bInRetain) : QoS(InQoS) , bRetain(bInRetain) , Topic(std::move(InTopic)) , Payload(InPayload)`
- L142 _public member_ `bool bIsDuplicate = false;` — msg is a retry
- L143 _public member_ `EMQTTQualityOfService QoS = EMQTTQualityOfService::Once;`
- L144 _public member_ `bool bRetain = false;`
- L145 _public member_ `FString Topic = "";` — utf8, no wildcards
- L147 _public member_ `TArray<uint8> Payload;` — RemainingLength - VariableLength, can be 0
- L148 _public member_ `uint8 Response = 0;` — depends on QoS, 0 = none, 1 = PUBACK, 2 = PUBREC
- L150 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTPublishAckPacket`  
`struct FMQTTPublishAckPacket : FMQTTPacket`  
_L155-163_
- inherits: `FMQTTPacket`
- L157 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::PublishAcknowledge;`
- L158 _public member_ `uint8 Length = 2;`
- L160 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTPublishReceivedPacket`  
`struct FMQTTPublishReceivedPacket : FMQTTPacket`  
_L165-172_
- inherits: `FMQTTPacket`
- L167 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::PublishReceived;`
- L169 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTPublishReleasePacket`  
`struct FMQTTPublishReleasePacket : FMQTTPacket`  
_L174-188_
- inherits: `FMQTTPacket`
- L176 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::PublishRelease;`
- L178 _public prototype_ `FMQTTPublishReleasePacket() = default;`
- L180 _public function_ `explicit FMQTTPublishReleasePacket(const uint16 InPacketId)`
- L185 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTPublishCompletePacket`  
`struct FMQTTPublishCompletePacket : FMQTTPacket`  
_L190-199_
- inherits: `FMQTTPacket`
- L192 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::PublishComplete;`
- L193 _public member_ `FString Topic;`
- L194 _public member_ `TArray<uint8> Payload;`
- L196 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTSubscribePacket`  
`struct FMQTTSubscribePacket : FMQTTPacket`  
_L201-223_
- inherits: `FMQTTPacket`
- L203 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::Subscribe;`
- L205 _public prototype_ `FMQTTSubscribePacket() = default;`
- L207 _public function_ `explicit FMQTTSubscribePacket( const uint16 InPacketId, const TArray<FString>& InTopics, const TArray<EMQTTQualityOfService>& InRequestedQoS) : Topics(InTopics) , RequestedQoS(InRequestedQoS)`
- L217 _public member_ `TArray<FString> Topics;` — utf8
- L218 _public member_ `TArray<EMQTTQualityOfService> RequestedQoS;`
- L220 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTSubscribeAckPacket`  
`struct FMQTTSubscribeAckPacket : FMQTTPacket`  
_L225-233_
- inherits: `FMQTTPacket`
- L227 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::SubscribeAcknowledge;`
- L228 _public member_ `TArray<uint8> ReturnCodes;`
- L230 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTUnsubscribePacket`  
`struct FMQTTUnsubscribePacket : FMQTTPacket`  
_L235-253_
- inherits: `FMQTTPacket`
- L237 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::Unsubscribe;`
- L238 _public member_ `TArray<FString> Topics;` — utf8
- L240 _public prototype_ `FMQTTUnsubscribePacket() = default;`
- L242 _public function_ `explicit FMQTTUnsubscribePacket( const uint16 InPacketId, const TArray<FString>& InTopics) : Topics(InTopics)`
- L250 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTUnsubscribeAckPacket`  
`struct FMQTTUnsubscribeAckPacket : FMQTTPacket`  
_L255-262_
- inherits: `FMQTTPacket`
- L257 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::UnsubscribeAcknowledge;`
- L259 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTPingRequestPacket`  
`struct FMQTTPingRequestPacket : FMQTTPacket`  
_L264-271_
- inherits: `FMQTTPacket`
- L266 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::PingRequest;`
- L268 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTPingResponsePacket`  
`struct FMQTTPingResponsePacket : FMQTTPacket`  
_L273-280_
- inherits: `FMQTTPacket`
- L275 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::PingResponse;`
- L277 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FMQTTDisconnectPacket`  
`struct FMQTTDisconnectPacket : FMQTTPacket`  
_L282-289_
- inherits: `FMQTTPacket`
- L284 _public member_ `constexpr static EMQTTPacketType PacketType = EMQTTPacketType::Disconnect;`
- L286 _public prototype_ `void Serialize(FArchive& Ar);`

#### class `IMQTTOperation`  
`class IMQTTOperation`  
_L296-370_
- desc: An operation defines a message flow and encapsulates one or more packets.
- L298 _private member_ `constexpr static EMQTTPacketType NullPacketType = EMQTTPacketType::None;`
- L301 _public function_ `explicit IMQTTOperation( const uint16 InPacketId = 0, const EMQTTState& InStateDependency = EMQTTState::Connected) : StateDependency(InStateDependency) #if WITH_EDITORONLY_DATA , TimeQueued(FDateTime::UtcNow()) , TimeExecuted(0) #endif , PacketId(InPacketId) , bCompleted(false)`
- L314 _public prototype_ `virtual ~IMQTTOperation() = default;`
- L316 _public function_ `virtual EMQTTPacketType GetPacketType() const`
- L321 _public function_ `virtual EMQTTPacketType GetPendingPacketType() const`
- L326 _public function_ `const uint16& GetPacketId() const`
- L332 _public function_ `virtual void Pack(FBufferArchive& InArchive)` — Serialize to provided archive.
- L337 _public function_ `virtual uint16 Complete()` — Flags task as complete and returns the PacketId, if any.
- L343 _public function_ `virtual void Abandon()` — Abandon task.
- L348 _public prototype_ `virtual const FString& GetTypeName() const;` — Returns the operation type name for debug purposes.
- L350 _public member_ `EMQTTState StateDependency = EMQTTState::None;`
- L353 _public member_ `FDateTime TimeQueued;`
- L354 _public member_ `FDateTime TimeExecuted;`
- L356 _public function_ `uint32 GetTimeToExecution() const`
- L361 _public function_ `void MarkExecuted()`
- L368 _protected member_ `uint16 PacketId = 0;`
- L369 _protected member_ `std::atomic<bool> bCompleted;`

#### class `IMQTTPersistentOperation`  
`class IMQTTPersistentOperation`  
_L373-375_
- desc: Persisted as Session State.

#### class `TMQTTOperation`  
`template <typename RequestType, typename ResponseType> class TMQTTOperation : public IMQTTOperation`  
_L378-425_
- inherits: `IMQTTOperation`
- L381 _public typedef_ `typedef RequestType FRequestType;`
- L382 _public typedef_ `typedef ResponseType FResponseType;`
- L384 _public function_ `explicit TMQTTOperation( RequestType&& InRequest, const uint16 InPacketId = 0, const EMQTTState& InStateDependency = EMQTTState::Connected) : IMQTTOperation(InPacketId, InStateDependency) , Packet(MoveTemp(InRequest))`
- L395 _public function_ `virtual EMQTTPacketType GetPacketType() const override`
- L400 _public function_ `virtual EMQTTPacketType GetPendingPacketType() const override`
- L406 _public function_ `virtual void Pack(FBufferArchive& InArchive) override` — Serialize to provided archive.
- L411 _public function_ `TFuture<ResponseType> GetFuture()`
- L416 _public prototype_ `virtual uint16 Complete() override;`
- L417 _public prototype_ `virtual uint16 Complete(ResponseType&& InResponse);`
- L420 _public prototype_ `virtual void Abandon() override;` — Abandon task.
- L423 _protected member_ `RequestType Packet;`
- L424 _protected member_ `TPromise<ResponseType> Promise;`
- L432 _public typedef_ `typedef void FResponseType;`
- L453 _public function_ `TFuture<void> GetFuture()`
- L461 _public function_ `virtual void Abandon() override` — Abandon task.
- L471 _protected member_ `TPromise<void> Promise;`
- L475 _function_ `template <typename RequestType, typename ResponseType> TMQTTOperation<RequestType, ResponseType>::~TMQTTOperation()`
- L480 _function_ `template <typename RequestType, typename ResponseType> uint16 TMQTTOperation<RequestType, ResponseType>::Complete()`
- L488 _function_ `template <typename RequestType> uint16 TMQTTOperation<RequestType, void>::Complete()`
- L496 _function_ `template <typename RequestType, typename ResponseType> uint16 TMQTTOperation<RequestType, ResponseType>::Complete(ResponseType&& InResponse)`
- L504 _function_ `template <typename RequestType, typename ResponseType> void TMQTTOperation<RequestType, ResponseType>::Abandon()`

#### class `TMQTTOperation`  
`template <typename RequestType> class TMQTTOperation<RequestType, void> : public IMQTTOperation`  
_L428-472_
- inherits: `IMQTTOperation`
- L381 _public typedef_ `typedef RequestType FRequestType;`
- L382 _public typedef_ `typedef ResponseType FResponseType;`
- L384 _public function_ `explicit TMQTTOperation( RequestType&& InRequest, const uint16 InPacketId = 0, const EMQTTState& InStateDependency = EMQTTState::Connected) : IMQTTOperation(InPacketId, InStateDependency) , Packet(MoveTemp(InRequest))`
- L395 _public function_ `virtual EMQTTPacketType GetPacketType() const override`
- L400 _public function_ `virtual EMQTTPacketType GetPendingPacketType() const override`
- L406 _public function_ `virtual void Pack(FBufferArchive& InArchive) override` — Serialize to provided archive.
- L411 _public function_ `TFuture<ResponseType> GetFuture()`
- L416 _public prototype_ `virtual uint16 Complete() override;`
- L417 _public prototype_ `virtual uint16 Complete(ResponseType&& InResponse);`
- L420 _public prototype_ `virtual void Abandon() override;` — Abandon task.
- L423 _protected member_ `RequestType Packet;`
- L424 _protected member_ `TPromise<ResponseType> Promise;`
- L432 _public typedef_ `typedef void FResponseType;`
- L453 _public function_ `TFuture<void> GetFuture()`
- L461 _public function_ `virtual void Abandon() override` — Abandon task.
- L471 _protected member_ `TPromise<void> Promise;`
- L475 _function_ `template <typename RequestType, typename ResponseType> TMQTTOperation<RequestType, ResponseType>::~TMQTTOperation()`
- L480 _function_ `template <typename RequestType, typename ResponseType> uint16 TMQTTOperation<RequestType, ResponseType>::Complete()`
- L488 _function_ `template <typename RequestType> uint16 TMQTTOperation<RequestType, void>::Complete()`
- L496 _function_ `template <typename RequestType, typename ResponseType> uint16 TMQTTOperation<RequestType, ResponseType>::Complete(ResponseType&& InResponse)`
- L504 _function_ `template <typename RequestType, typename ResponseType> void TMQTTOperation<RequestType, ResponseType>::Abandon()`

#### class `FMQTTConnectOperation`  
`class FMQTTConnectOperation : public TMQTTOperation<FMQTTConnectPacket, FMQTTConnectAckPacket>`  
_L512-524_
- inherits: `TMQTTOperation<FMQTTConnectPacket,FMQTTConnectAckPacket>`
- L515 _public function_ `explicit FMQTTConnectOperation(FMQTTConnectPacket&& InRequest, const uint16 InPacketId = 0) : TMQTTOperation<FMQTTConnectPacket, FMQTTConnectAckPacket>(MoveTemp(InRequest), InPacketId, EMQTTState::None)`
- L520 _public prototype_ `virtual void Abandon() override;`
- L522 _public member_ `static FString TypeName;`
- L523 _public function_ `virtual const FString& GetTypeName() const override`

#### class `FMQTTDisconnectOperation`  
`class FMQTTDisconnectOperation : public TMQTTOperation<FMQTTDisconnectPacket, void>`  
_L526-536_
- inherits: `TMQTTOperation<FMQTTDisconnectPacket,void>`
- L529 _public function_ `explicit FMQTTDisconnectOperation(FMQTTDisconnectPacket&& InRequest, const uint16 InPacketId = 0) : TMQTTOperation<FMQTTDisconnectPacket, void>(MoveTemp(InRequest), InPacketId, EMQTTState::None)`
- L534 _public member_ `static FString TypeName;`
- L535 _public function_ `virtual const FString& GetTypeName() const override`

#### class `FMQTTPublishOperationQoS0`  
`class FMQTTPublishOperationQoS0 : public TMQTTOperation<FMQTTPublishPacket, void>`  
_L538-548_
- inherits: `TMQTTOperation<FMQTTPublishPacket,void>`
- L541 _public function_ `explicit FMQTTPublishOperationQoS0(FMQTTPublishPacket&& InRequest, const uint16 InPacketId = 0) : TMQTTOperation<FMQTTPublishPacket, void>(MoveTemp(InRequest), InPacketId, EMQTTState::Connected)`
- L546 _public member_ `static FString TypeName;`
- L547 _public function_ `virtual const FString& GetTypeName() const override`

#### class `FMQTTPublishOperationQoS1`  
`class FMQTTPublishOperationQoS1 : public TMQTTOperation<FMQTTPublishPacket, FMQTTPublishAckPacket>`  
_L550-560_
- inherits: `TMQTTOperation<FMQTTPublishPacket,FMQTTPublishAckPacket>`
- L553 _public function_ `explicit FMQTTPublishOperationQoS1(FMQTTPublishPacket&& InRequest, const uint16 InPacketId = 0) : TMQTTOperation<FMQTTPublishPacket, FMQTTPublishAckPacket>(MoveTemp(InRequest), InPacketId, EMQTTState::Connected)`
- L558 _public member_ `static FString TypeName;`
- L559 _public function_ `virtual const FString& GetTypeName() const override`

#### class `FMQTTPublishOperationQoS2`  
`class FMQTTPublishOperationQoS2 final : public TMQTTOperation<FMQTTPublishPacket, FMQTTPublishCompletePacket>, public IMQTTPersistentOperation`  
_L563-603_
- inherits: `TMQTTOperation<FMQTTPublishPacket,FMQTTPublishCompletePacket>,IMQTTPersistentOperation`
- desc: Wraps all steps FMQTTPublishPacket -> FMQTTPublishCompletePacket
- L568 _public function_ `explicit FMQTTPublishOperationQoS2(FMQTTPublishPacket&& InRequest, const uint16 InPacketId = 0) : TMQTTOperation<FMQTTPublishPacket, FMQTTPublishCompletePacket>(MoveTemp(InRequest), InPacketId, EMQTTState::Connected) , PublishReceivedPacket() , PublishReleasePacket()`
- L576 _public prototype_ `virtual void Pack(FBufferArchive& InArchive) override;` — Serialize to provided archive. Packet serialized depends on current step.
- L578 _public function_ `virtual EMQTTPacketType GetPacketType() const override`
- L583 _public function_ `virtual EMQTTPacketType GetPendingPacketType() const override`
- L588 _public prototype_ `uint16 CompleteStep(FMQTTPublishReceivedPacket&& InResponse);`
- L589 _public prototype_ `uint16 CompleteStep(FMQTTPublishReleasePacket&& InResponse);`
- L591 _public member_ `static FString TypeName;`
- L592 _public function_ `virtual const FString& GetTypeName() const override`
- L595 _protected member_ `static constexpr EMQTTPacketType StepPacketTypes[] = {EMQTTPacketType::PublishReceived, EMQTTPacketType::PublishRelease, EMQTTPacketType::PublishComplete};`
- L596 _protected member_ `EMQTTPacketType CurrentPacketType = EMQTTPacketType::Publish;`
- L597 _protected member_ `EMQTTPacketType PendingPacketType = EMQTTPacketType::PublishReceived;`
- L599 _protected member_ `FMQTTPublishReceivedPacket PublishReceivedPacket;`
- L600 _protected member_ `FMQTTPublishReleasePacket PublishReleasePacket;`
- L602 _protected prototype_ `void NextStep();`

#### class `FMQTTPublishOperationQoS2_Step1`  
`class FMQTTPublishOperationQoS2_Step1 : public TMQTTOperation<FMQTTPublishPacket, FMQTTPublishReceivedPacket>, public IMQTTPersistentOperation`  
_L606-618_
- inherits: `TMQTTOperation<FMQTTPublishPacket,FMQTTPublishReceivedPacket>,IMQTTPersistentOperation`
- desc: FMQTTPublishPacket -> FMQTTPublishReceivedPacket
- L611 _public function_ `explicit FMQTTPublishOperationQoS2_Step1(FMQTTPublishPacket&& InRequest, const uint16 InPacketId = 0) : TMQTTOperation<FMQTTPublishPacket, FMQTTPublishReceivedPacket>(MoveTemp(InRequest), InPacketId, EMQTTState::Connected)`
- L616 _public member_ `static FString TypeName;`
- L617 _public function_ `virtual const FString& GetTypeName() const override`

#### class `FMQTTPublishOperationQoS2_Step2`  
`class FMQTTPublishOperationQoS2_Step2 : public TMQTTOperation<FMQTTPublishReceivedPacket, FMQTTPublishReleasePacket>, public IMQTTPersistentOperation`  
_L621-633_
- inherits: `TMQTTOperation<FMQTTPublishReceivedPacket,FMQTTPublishReleasePacket>,IMQTTPersistentOperation`
- desc: FMQTTPublishReceivedPacket -> FMQTTPublishReleasePacket
- L626 _public function_ `explicit FMQTTPublishOperationQoS2_Step2(FMQTTPublishReceivedPacket&& InRequest, const uint16 InPacketId = 0) : TMQTTOperation<FMQTTPublishReceivedPacket, FMQTTPublishReleasePacket>(MoveTemp(InRequest), InPacketId, EMQTTState::Connected)`
- L631 _public member_ `static FString TypeName;`
- L632 _public function_ `virtual const FString& GetTypeName() const override`

#### class `FMQTTPublishOperationQoS2_Step3`  
`class FMQTTPublishOperationQoS2_Step3 : public TMQTTOperation<FMQTTPublishReleasePacket, FMQTTPublishCompletePacket>, public IMQTTPersistentOperation`  
_L636-648_
- inherits: `TMQTTOperation<FMQTTPublishReleasePacket,FMQTTPublishCompletePacket>,IMQTTPersistentOperation`
- desc: FMQTTPublishReleasePacket -> FMQTTPublishCompletePacket
- L641 _public function_ `explicit FMQTTPublishOperationQoS2_Step3(FMQTTPublishReleasePacket&& InRequest, const uint16 InPacketId = 0) : TMQTTOperation<FMQTTPublishReleasePacket, FMQTTPublishCompletePacket>(MoveTemp(InRequest), InPacketId, EMQTTState::Connected)`
- L646 _public member_ `static FString TypeName;`
- L647 _public function_ `virtual const FString& GetTypeName() const override`

#### class `FMQTTSubscribeOperation`  
`class FMQTTSubscribeOperation : public TMQTTOperation<FMQTTSubscribePacket, FMQTTSubscribeAckPacket>`  
_L650-660_
- inherits: `TMQTTOperation<FMQTTSubscribePacket,FMQTTSubscribeAckPacket>`
- L653 _public function_ `explicit FMQTTSubscribeOperation(FMQTTSubscribePacket&& InRequest, const uint16 InPacketId = 0) : TMQTTOperation<FMQTTSubscribePacket, FMQTTSubscribeAckPacket>(MoveTemp(InRequest), InPacketId, EMQTTState::Connected)`
- L658 _public member_ `static FString TypeName;`
- L659 _public function_ `virtual const FString& GetTypeName() const override`

#### class `FMQTTUnsubscribeOperation`  
`class FMQTTUnsubscribeOperation : public TMQTTOperation<FMQTTUnsubscribePacket, FMQTTUnsubscribeAckPacket>`  
_L662-672_
- inherits: `TMQTTOperation<FMQTTUnsubscribePacket,FMQTTUnsubscribeAckPacket>`
- L665 _public function_ `explicit FMQTTUnsubscribeOperation(FMQTTUnsubscribePacket&& InRequest, const uint16 InPacketId = 0) : TMQTTOperation<FMQTTUnsubscribePacket, FMQTTUnsubscribeAckPacket>(MoveTemp(InRequest), InPacketId, EMQTTState::Connected)`
- L670 _public member_ `static FString TypeName;`
- L671 _public function_ `virtual const FString& GetTypeName() const override`

#### class `FMQTTPingOperation`  
`class FMQTTPingOperation : public TMQTTOperation<FMQTTPingRequestPacket, FMQTTPingResponsePacket>`  
_L674-684_
- inherits: `TMQTTOperation<FMQTTPingRequestPacket,FMQTTPingResponsePacket>`
- L677 _public function_ `explicit FMQTTPingOperation(FMQTTPingRequestPacket&& InRequest, const uint16 InPacketId = 0) : TMQTTOperation<FMQTTPingRequestPacket, FMQTTPingResponsePacket>(MoveTemp(InRequest), InPacketId, EMQTTState::Connected)`
- L682 _public member_ `static FString TypeName;`
- L683 _public function_ `virtual const FString& GetTypeName() const override`

### `Plugins/Protocols/MQTT/Source/MQTTCore/Private/MQTTSharedInternal.h` (Private)


#### enum `EMQTTSocketState`  
`enum class EMQTTSocketState : uint8`  
_L28-35_
- desc: Connection socket state
- L30 _public enumerator_ `Connecting = 0`
- L31 _public enumerator_ `Connected = 1` — SCS_Connected
- L32 _public enumerator_ `Error = 2` — Couldn't connect / SCS_ConnectionError
- L33 _public enumerator_ `ConnectionRejected = 3` — Could connect, but was refused or rejected
- L34 _public enumerator_ `Stopping = 8` — Force stop/shutdown

#### enum `EMQTTState`  
`enum class EMQTTState : uint8`  
_L38-48_
- desc: MQTT protocol state
- L40 _public enumerator_ `Unknown = 0`
- L41 _public enumerator_ `Connected = 1`
- L42 _public enumerator_ `Connecting = 2`
- L43 _public enumerator_ `Disconnected = 3`
- L44 _public enumerator_ `Disconnecting = 4`
- L45 _public enumerator_ `Stopping = 8` — Force stop/shutdown
- L47 _public enumerator_ `None = 127` — Used for state dependency to indicate there is none

#### class `IMQTTTask`  
`class IMQTTTask`  
_L60-68_
- desc: An arbitrary task allowing the storage/calls and ResultType to be separate (vs. a raw TPromise).
- L63 _public prototype_ `virtual ~IMQTTTask() = default;`
- L64 _public prototype_ `virtual void Execute() = 0;`
- L65 _public prototype_ `virtual void Abandon() = 0;`
- L67 _public member_ `EMQTTState StateDependency = EMQTTState::None;`

#### class `TMQTTTask`  
`template <typename ResultType> class TMQTTTask final : public IMQTTTask`  
_L71-100_
- inherits: `IMQTTTask`
- L74 _public function_ `TMQTTTask(TUniqueFunction<ResultType()>&& InFunction, const EMQTTState& InStateDependency = EMQTTState::Connected) : Function(MoveTemp(InFunction))`
- L80 _public function_ `virtual ~TMQTTTask() override`
- L84 _public function_ `virtual void Execute() override`
- L89 _public function_ `virtual void Abandon() override`
- L99 _private member_ `TUniqueFunction<ResultType()> Function;` — The function to execute.

#### Free symbols / members of external scopes

- L11 _macro_ `#define REGISTER_MQTT_ARCHIVE(MQTTPacket) \`
- L18 _macro_ `#define REGISTER_MQTT_PACK(MQTTPacket) \`
- L50 _namespace_ `namespace MQTT`
- L52 _prototype_ `const TCHAR* GetSocketConnectionStateName(ESocketConnectionState InConnectionState);` (scope `MQTT`)
- L53 _prototype_ `const TCHAR* GetMQTTPacketTypeName(EMQTTPacketType InMessageType);` (scope `MQTT`)
- L54 _prototype_ `const TCHAR* GetMQTTStateName(EMQTTState InState);` (scope `MQTT`)
- L55 _prototype_ `const TCHAR* GetMQTTConnectReturnCodeDescription(EMQTTConnectReturnCode InConnectReturnCode);` (scope `MQTT`)
- L56 _prototype_ `const TCHAR* GetMQTTSubscribeReturnCodeName(EMQTTSubscribeReturnCode InSubscribeReturnCode);` (scope `MQTT`)
- L102 _namespace_ `namespace MQTT`
- L105 _function_ `template <typename CallableType> auto CreateTask(CallableType&& InCallable, const EMQTTState& InStateDependency) -> TSharedPtr<TMQTTTask<decltype(Forward<CallableType>(InCallable)())>>` (scope `MQTT`)
- L107 _typedef_ `using ResultType = decltype(Forward<CallableType>(InCallable)());` (scope `MQTT::CreateTask`)

### `Plugins/Protocols/MQTT/Source/MQTTCore/Public/IMQTTClient.h` (Public)


#### class `IMQTTClient`  
`class IMQTTClient`  
_L15-73_
- L18 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConnect, EMQTTConnectReturnCode) virtual FOnConnect& OnConnect() = 0;`
- L21 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDisconnect) virtual FOnDisconnect& OnDisconnect() = 0;`
- L24 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPublish) virtual FOnPublish& OnPublish() = 0;`
- L27 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubscribe, TArray<FMQTTSubscribeResult> ) virtual FOnSubscribe& OnSubscribe() = 0;`
- L30 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnUnsubscribe) virtual FOnUnsubscribe& OnUnsubscribe() = 0;`
- L33 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMessage, const FMQTTClientMessage& ) virtual FOnMessage& OnMessage() = 0;`
- L37 _public prototype_ `virtual ~IMQTTClient() = default;`
- L41 _public prototype_ `virtual TFuture<EMQTTConnectReturnCode> Connect(bool bCleanSession = true) = 0;` — Connect using the clients URL. Set bCleanSession = false to resume previous session.
- L43 _public prototype_ `virtual TFuture<void> Disconnect() = 0;`
- L46 _public prototype_ `virtual TFuture<bool> Publish(const FString& InTopic, const TArray<uint8>& InPayload, EMQTTQualityOfService InQoS = EMQTTQualityOfService::Once, const bool bInRetain = false) = 0;` — Return true if the entire operation was successful (depends on QoS)
- L49 _public prototype_ `virtual TFuture<bool> Publish(const FString& InTopic, const FString& InPayload, EMQTTQualityOfService InQoS = EMQTTQualityOfService::Once, const bool bInRetain = false) = 0;` — Return true if the entire operation was successful (depends on QoS)
- L51 _public prototype_ `virtual TFuture<TArray<FMQTTSubscribeResult>> Subscribe(const TArray<TPair<FString, EMQTTQualityOfService>>& InTopicFilterQoSPairs) = 0;`
- L55 _public prototype_ `template <typename CallableType> TFuture<FMQTTSubscribeResult> Subscribe(const FString& InTopicFilter, CallableType&& InOnMessage, EMQTTQualityOfService InQoS = EMQTTQualityOfService::Once);` — only for single sub
- L57 _public prototype_ `virtual TFuture<bool> Unsubscribe(const TSet<FString>& InTopicFilters) = 0;`
- L60 _public prototype_ `virtual TFuture<bool> Ping(const float& InTimeout = 2.0f) = 0;` — Returns true if response received before timeout.
- L63 _public prototype_ `virtual FGuid GetClientId() const = 0;` — Unique Id for this client.
- L66 _public prototype_ `virtual const FMQTTURL& GetURL() const = 0;` — URL for this client.
- L69 _public prototype_ `virtual bool IsConnected() const = 0;` — Is client currently connected?
- L72 _public prototype_ `virtual bool IsValid() const = 0;` — Validity of this client.
- L76 _function_ `template <typename CallableType> TFuture<FMQTTSubscribeResult> IMQTTClient::Subscribe(const FString& InTopicFilter, CallableType&& InOnMessage, EMQTTQualityOfService InQoS)`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConnect, EMQTTConnectReturnCode) virtual FOnConnect& OnConnect() = 0;`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDisconnect) virtual FOnDisconnect& OnDisconnect() = 0;`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPublish) virtual FOnPublish& OnPublish() = 0;`
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubscribe, TArray<FMQTTSubscribeResult> ) virtual FOnSubscribe& OnSubscribe() = 0;`
- L30 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnUnsubscribe) virtual FOnUnsubscribe& OnUnsubscribe() = 0;`
- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMessage, const FMQTTClientMessage& ) virtual FOnMessage& OnMessage() = 0;`
- L80 _function_ `` (scope `IMQTTClient::Subscribe`)
- L97 _function_ `inline uint32 GetTypeHash(const IMQTTClient& InClient)`

### `Plugins/Protocols/MQTT/Source/MQTTCore/Public/IMQTTCoreModule.h` (Public)


#### class `IMQTTCoreModule`  
`class IMQTTCoreModule : public IModuleInterface`  
_L13-42_
- inherits: `IModuleInterface`
- L22 _public function_ `static IMQTTCoreModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L29 _public prototype_ `virtual TSharedPtr<IMQTTClient, ESPMode::ThreadSafe> GetOrCreateClient(bool bForceNew = false) = 0;` — Get or creates an MQTT client that uses the project default URL. An existing client is returned for a matching URL.
- L32 _public prototype_ `virtual TSharedPtr<IMQTTClient, ESPMode::ThreadSafe> GetOrCreateClient(const FMQTTURL& InURL, bool bForceNew = false) = 0;` — Creates an MQTT client from a URL. An existing client is returned for a matching URL. bForceNew = recreate if existing
- L41 _protected prototype_ `virtual int32 GetClientNum() const = 0;`

### `Plugins/Protocols/MQTT/Source/MQTTCore/Public/MQTTClientMessage.h` (Public)


#### struct `FMQTTClientMessage`  
`struct FMQTTClientMessage`  
_L12-55_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `FDateTime TimeStamp = FDateTime::UtcNow();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MQTT")` — TimeStamp as UTC.
- L22 _public member_ `FString Topic;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MQTT")` — Packet topic.
- L27 _public member_ `TArray<uint8> Payload;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MQTT")` — Packet content.
- L31 _public member_ `bool bRetain = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MQTT")` — Retain flag.
- L35 _public member_ `EMQTTQualityOfService QoS = EMQTTQualityOfService::Once;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MQTT", meta = (DisplayName = "Quality of Service"))` — Quality of Service.
- L38 _public function_ `const FString& GetPayloadAsString() const` — Get's the payload as a string, ie. for Json.
- L41 _public prototype_ `bool GetPayloadAsJson(TSharedPtr<FJsonObject>& OutJson) const;` — Get's the payload as a Json object, first converting to string. Returns false if unsuccessful.
- L44 _public prototype_ `void SetPayloadFromString(const FString& InPayloadString);` — Set's the payload from the input string.
- L47 _public function_ `bool IsValid() const` — Gets the validity of the Packet.
- L54 _protected member_ `FString PayloadString;` — `UPROPERTY()` — Cached payload-as-string, ie. Json.

### `Plugins/Protocols/MQTT/Source/MQTTCore/Public/MQTTClientObject.h` (Public)


#### class `UMQTTSubscriptionObject`  
`class UMQTTSubscriptionObject final : public UObject`  
_L14-50_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "MQTT Subscription"))`
- inherits: `UObject`
- L21 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMessageDelegate, const FMQTTClientMessage&, Message);`
- L24 _public prototype_ `void Initialize(const TSharedPtr<FMQTTSubscription, ESPMode::ThreadSafe>& InSubscription);` — Initialize from C++ subscription
- L27 _public prototype_ `void SetOnMessageHandler(const FOnMessageDelegate& OnMessageCallback);` — `UFUNCTION(BlueprintCallable, Category = "MQTT")`
- L30 _public function_ `bool IsValid() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MQTT")`
- L44 _protected member_ `FOnMessageDelegate OnMessageDelegate;` — `UPROPERTY()`
- L47 _private member_ `TSharedPtr<FMQTTSubscription, ESPMode::ThreadSafe> MqttSubscriptionPtr;`
- L49 _private prototype_ `void OnMessage(const FMQTTClientMessage& InMessage) const;`

#### class `UMQTTClientObject`  
`class UMQTTClientObject final : public UObject`  
_L53-129_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "MQTT Client"))`
- inherits: `UObject`
- L60 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnConnectDelegate, EMQTTConnectReturnCode, ReturnCode);`
- L61 _public prototype_ `DECLARE_DYNAMIC_DELEGATE(FOnDisconnectDelegate);`
- L62 _public prototype_ `DECLARE_DYNAMIC_DELEGATE(FOnPublishDelegate);`
- L63 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSubscribeDelegate, EMQTTSubscribeReturnCode, ReturnCode);`
- L64 _public prototype_ `DECLARE_DYNAMIC_DELEGATE(FOnUnsubscribeDelegate);`
- L65 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMessageDelegate, const FMQTTClientMessage&, Message);`
- L68 _public prototype_ `void Initialize(const FMQTTURL& InURL);` — Initialize from URL
- L70 _public prototype_ `void InitDelegates();`
- L71 _public prototype_ `void RemoveDelegates() const;`
- L73 _public prototype_ `virtual void BeginDestroy() override;`
- L75 _public prototype_ `TSharedPtr<IMQTTClient, ESPMode::ThreadSafe> GetClientImpl() const;`
- L78 _public prototype_ `void Connect(UPARAM(DisplayName = "OnConnect") const FOnConnectDelegate& InOn` — `UFUNCTION(BlueprintCallable, Category = "MQTT")`
- L81 _public prototype_ `void Disconnect(UPARAM(DisplayName = "OnDisconnect") const FOnDisconnectDelegate& InOn` — `UFUNCTION(BlueprintCallable, Category = "MQTT")`
- L86 _public prototype_ `UPARAM(DisplayName = "Topic") const FString& InTopic, UPARAM(DisplayName = "Payload") const TArray<uint8>& InPayload, UPARAM(DisplayName = "Quality of Service") EMQTTQualityOfService InQoS = EMQTTQualityOfService::Once, const bool bInRetain = false);`
- L94 _public prototype_ `UPARAM(DisplayName = "Topic") const FString& InTopic, UPARAM(DisplayName = "Quality of Service") EMQTTQualityOfService InQoS = EMQTTQualit`
- L100 _public prototype_ `UPARAM(DisplayName = "Topics") const TArray<FString>& InTopics, UPARAM(DisplayName = "Quality of Services") const TArray<EMQTTQualit`
- L105 _public prototype_ `void Unsubscribe(UPARAM(DisplayName = "Topic") const FString& InTo` — `UFUNCTION(BlueprintCallable, Category = "MQTT")` — OutMessageId can be used to match this request with the callback response.
- L108 _public prototype_ `FString GetClientId() const;` — `UFUNCTION(BlueprintPure, Category = "MQTT")`
- L112 _public prototype_ `FMQTTURL GetURL() const;` — `UFUNCTION(BlueprintPure, Category = "MQTT")` — URL for this client.
- L116 _protected member_ `FOnConnectDelegate OnConnectDelegate;` — `UPROPERTY()`
- L119 _protected member_ `FOnDisconnectDelegate OnDisconnectDelegate;` — `UPROPERTY()`
- L122 _protected member_ `FOnMessageDelegate OnMessageDelegate;` — `UPROPERTY()`
- L125 _protected member_ `TArray<TObjectPtr<UMQTTSubscriptionObject>> Subscriptions;` — `UPROPERTY()`
- L128 _private member_ `TSharedPtr<IMQTTClient, ESPMode::ThreadSafe> MqttClientPtr;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMessageDelegate, const FMQTTClientMessage&, Message);`
- L32 _function_ `friend uint32 GetTypeHash(const UMQTTSubscriptionObject* InSubscription)`
- L60 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnConnectDelegate, EMQTTConnectReturnCode, ReturnCode);`
- L61 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FOnDisconnectDelegate);`
- L62 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FOnPublishDelegate);`
- L63 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSubscribeDelegate, EMQTTSubscribeReturnCode, ReturnCode);`
- L64 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FOnUnsubscribeDelegate);`
- L65 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMessageDelegate, const FMQTTClientMessage&, Message);`

### `Plugins/Protocols/MQTT/Source/MQTTCore/Public/MQTTClientSettings.h` (Public)


#### class `UMQTTClientSettings`  
`class UMQTTClientSettings final : public UObject`  
_L15-26_
- reflection: `UCLASS(Config = MQTT)`
- inherits: `UObject`
- desc: MQTT Client Settings
- L21 _public member_ `FMQTTURL DefaultURL;` — `UPROPERTY(EditAnywhere, Config, Category = "Connection")`
- L25 _public member_ `uint32 PublishRate = 60;` — `UPROPERTY(EditAnywhere, Config, Category = "Bandwidth")` — Maximum messages to publish per second.

### `Plugins/Protocols/MQTT/Source/MQTTCore/Public/MQTTProtocol.h` (Public)


#### class `FMQTTProtocol`  
`class FMQTTProtocol`  
_L14-16_

#### enum `EMQTTProtocolLevel`  
`enum class EMQTTProtocolLevel : uint8`  
_L23-27_
- L25 _public enumerator_ `MQTT311 = 4`
- L26 _public enumerator_ `MQTT5 = 5`

#### enum `EMQTTPacketType`  
`enum class EMQTTPacketType : uint8`  
_L30-55_
- desc: Control packet types
- L32 _public enumerator_ `Connect = 0x10U`
- L33 _public enumerator_ `ConnectAcknowledge = 0x20U`
- L35 _public enumerator_ `Publish = 0x30U`
- L36 _public enumerator_ `PublishAcknowledge = 0x40U`
- L37 _public enumerator_ `PublishReceived = 0x50U`
- L38 _public enumerator_ `PublishRelease = 0x60U`
- L39 _public enumerator_ `PublishComplete = 0x70U`
- L41 _public enumerator_ `Subscribe = 0x80U`
- L42 _public enumerator_ `SubscribeAcknowledge = 0x90U`
- L44 _public enumerator_ `Unsubscribe = 0xA0U`
- L45 _public enumerator_ `UnsubscribeAcknowledge = 0xB0U`
- L47 _public enumerator_ `PingRequest = 0xC0U`
- L48 _public enumerator_ `PingResponse = 0xD0U`
- L50 _public enumerator_ `Disconnect = 0xE0U`
- L51 _public enumerator_ `Authorize = 0xF0U`
- L54 _public enumerator_ `None = 0` — non-spec entries

#### enum `EMQTTConnectReturnCode`  
`enum class EMQTTConnectReturnCode : uint8`  
_L59-81_
- reflection: `UENUM(BlueprintType)`
- desc: MQTT v3.1.1
- L62 _public enumerator_ `Accepted = 0x00U` — Connection accepted.
- L64 _public enumerator_ `RefusedProtocolVersion = 0x01U` — The Server does not the support the level of the MQTT protocol requested by the Client.
- L66 _public enumerator_ `RefusedIdentifierRejected = 0x02U` — The Client identifier is correct UTF-8 but not allowed by the Server.
- L68 _public enumerator_ `RefusedServerUnavailable = 0x03U` — The Network Connection has been made but the MQTT service is unavailable.
- L70 _public enumerator_ `RefusedBadUsernamePassword = 0x04U` — The data in the user name or password is malformed.
- L72 _public enumerator_ `RefusedNotAuthorized = 0x05U` — The Client is not authorized to connect.
- L76 _public enumerator_ `AlreadyConnected` — The Client is already connected to the Server.
- L78 _public enumerator_ `InvalidURL` — The provided URL is malformed.
- L80 _public enumerator_ `SocketError` — Socket error.

#### enum `EMQTTSubscribeReturnCode`  
`enum class EMQTTSubscribeReturnCode : uint8`  
_L85-91_
- reflection: `UENUM(BlueprintType)`
- desc: MQTT v3.1.1
- L87 _public enumerator_ `Success_QoS0 = 0x00U`
- L88 _public enumerator_ `Success_QoS1 = 0x01U` — Success_QoS0 = 0x00U,             SubscribeAcknowledge
- L89 _public enumerator_ `Success_QoS2 = 0x02U` — Success_QoS1 = 0x01U,             SubscribeAcknowledge
- L90 _public enumerator_ `Failure = 0x80U` — Success_QoS2 = 0x02U,             SubscribeAcknowledge

#### enum `EMQTTReasonCode`  
`enum class EMQTTReasonCode : uint8`  
_L95-143_
- desc: @note: conflicting codes a differentiated by what they're returned from
- L97 _public enumerator_ `Success = 0x00U`
- L98 _public enumerator_ `NormalDisconnection = 0x00U` — Success = 0x00U,						          ConnectAcknowledge, PublishAcknowledge, PublishReceive, PublishRelease, PublishComplete, UnsubscribeAcknowledge, Authorize
- L99 _public enumerator_ `Granted_QoS0 = 0x00U` — NormalDisconnection = 0x00U,			          Disconnect
- L100 _public enumerator_ `Granted_QoS1 = 0x01U` — Granted_QoS0 = 0x00U,					          SubscribeAcknowledge
- L101 _public enumerator_ `Granted_QoS2 = 0x02U` — Granted_QoS1 = 0x01U,					          SubscribeAcknowledge
- L102 _public enumerator_ `DisconnectWithWillMsg = 0x04U` — Granted_QoS2 = 0x02U,					          SubscribeAcknowledge
- L103 _public enumerator_ `NoMatchingSubscribers = 0x10U` — DisconnectWithWillMsg = 0x04U,		              Disconnect
- L104 _public enumerator_ `NoSubscriptionExisted = 0x11U` — NoMatchingSubscribers = 0x10U,		              PublishAcknowledge, PublishReceive
- L105 _public enumerator_ `ContinueAuthentication = 0x18U` — NoSubscriptionExisted = 0x11U,		              UnsubscribeAcknowledge
- L106 _public enumerator_ `ReAuthenticate = 0x19U` — ContinueAuthentication = 0x18U,					  Authorize
- L108 _public enumerator_ `Unspecified = 0x80U`
- L109 _public enumerator_ `MalformedPacket = 0x19U` — Unspecified = 0x80U,					          ConnectAcknowledge, PublishAcknowledge, PublishReceive, SubscribeAcknowledge, UnsubscribeAcknowledge, Disconnect
- L110 _public enumerator_ `ProtocolError = 0x82U` — MalformedPacket = 0x19U,				          ConnectAcknowledge, Disconnect
- L111 _public enumerator_ `ImplementationSpecific = 0x83U` — ProtocolError = 0x82U,							  Disconnect
- L112 _public enumerator_ `UnsupportedProtocolVersion = 0x84U` — ImplementationSpecific = 0x83U,					  ConnectAcknowledge, PublishAcknowledge, PublishReceive, SubscribeAcknowledge, UnsubscribeAcknowledge, Disconnect
- L113 _public enumerator_ `ClientIdNotValid = 0x85U` — UnsupportedProtocolVersion = 0x84U,				  ConnectAcknowledge
- L114 _public enumerator_ `BadUsernameOrPassword = 0x86U` — ClientIdNotValid = 0x85U,			              ConnectAcknowledge
- L115 _public enumerator_ `NotAuthorized = 0x87U` — BadUsernameOrPassword = 0x86U,					  ConnectAcknowledge
- L116 _public enumerator_ `ServerUnavailable = 0x88U` — NotAuthorized = 0x87U,							  ConnectAcknowledge, PublishAcknowledge, PublishReceive, SubscribeAcknowledge, UnsubscribeAcknowledge, Disconnect
- L117 _public enumerator_ `ServerBusy = 0x89U` — ServerUnavailable = 0x88U,						  ConnectAcknowledge
- L118 _public enumerator_ `Banned = 0x8AU` — ServerBusy = 0x89U,								  ConnectAcknowledge, Disconnect
- L119 _public enumerator_ `ServerShuttingDown = 0x8BU` — Banned = 0x8AU,									  ConnectAcknowledge
- L120 _public enumerator_ `BadAuthenticationMethod = 0x8CU` — ServerShuttingDown = 0x8BU,						  Disconnect
- L121 _public enumerator_ `KeepAliveTimeout = 0x8DU` — BadAuthenticationMethod = 0x8CU,				  ConnectAcknowledge
- L122 _public enumerator_ `SessionTakenOver = 0x8EU` — KeepAliveTimeout = 0x8DU,			              Disconnect
- L123 _public enumerator_ `TopicFilterInvalid = 0x8FU` — SessionTakenOver = 0x8EU,			              Disconnect
- L124 _public enumerator_ `TopicNameInvalid = 0x90U` — TopicFilterInvalid = 0x8FU,						  SubscribeAcknowledge, UnsubscribeAcknowledge, Disconnect
- L125 _public enumerator_ `PacketIdInUse = 0x91U` — TopicNameInvalid = 0x90U,			              ConnectAcknowledge, PublishAcknowledge, PublishReceive, Disconnect
- L126 _public enumerator_ `PacketIdNotFound = 0x92U` — PacketIdInUse = 0x91U,							  PublishAcknowledge, SubscribeAcknowledge, UnsubscribeAcknowledge
- L127 _public enumerator_ `ReceiveMaximumExceeded = 0x93U` — PacketIdNotFound = 0x92U,			              PublishRelease, PublishComplete
- L128 _public enumerator_ `TopicAliasInvalid = 0x94U` — ReceiveMaximumExceeded = 0x93U,					  Disconnect
- L129 _public enumerator_ `PacketTooLarge = 0x95U` — TopicAliasInvalid = 0x94U,						  Disconnect
- L130 _public enumerator_ `MessageRateTooHigh = 0x96U` — PacketTooLarge = 0x95U,							  ConnectAcknowledge, PublishAcknowledge, PublishReceive, Disconnect
- L131 _public enumerator_ `QuotaExceeded = 0x97U` — MessageRateTooHigh = 0x96U,						  Disconnect
- L132 _public enumerator_ `AdministrativeAction = 0x98U` — QuotaExceeded = 0x97U,							  PublishAcknowledge, PublishReceive, SubscribeAcknowledge, Disconnect
- L133 _public enumerator_ `PayloadFormatInvalid = 0x99U` — AdministrativeAction = 0x98U,		              Disconnect
- L134 _public enumerator_ `RetainNotSupported = 0x9AU` — PayloadFormatInvalid = 0x99U,		              ConnectAcknowledge, Disconnect
- L135 _public enumerator_ `QoSNotSupported = 0x9BU` — RetainNotSupported = 0x9AU,						  ConnectAcknowledge, Disconnect
- L136 _public enumerator_ `UseAnotherServer = 0x9CU` — QoSNotSupported = 0x9BU,			              ConnectAcknowledge, Disconnect
- L137 _public enumerator_ `ServerMoved = 0x9DU` — UseAnotherServer = 0x9CU,			              ConnectAcknowledge, Disconnect
- L138 _public enumerator_ `SharedSubscriptionNotSupported = 0x9EU` — ServerMoved = 0x9DU,					          ConnectAcknowledge, Disconnect
- L139 _public enumerator_ `ConnectionRateExceeded = 0x9FU` — SharedSubscriptionNotSupported = 0x9EU,			  SubscribeAcknowledge, Disconnect
- L140 _public enumerator_ `MaximumConnectTime = 0xA0U` — ConnectionRateExceeded = 0x9FU,					  ConnectAcknowledge, Disconnect
- L141 _public enumerator_ `SubscriptionIdsNotSupported = 0xA1U` — MaximumConnectTime = 0xA0U,						  Disconnect
- L142 _public enumerator_ `WildcardSubscriptionNotSupported = 0xA2U` — SubscriptionIdsNotSupported = 0xA1U,			  SubscribeAcknowledge, Disconnect

#### enum `FMQTT5Property`  
`enum class FMQTT5Property: uint8`  
_L145-174_
- L147 _public enumerator_ `PayloadFormatIndicator = 1`
- L148 _public enumerator_ `MessageExpiryInterval = 2` — PayloadFormatIndicator = 1,		      Byte :				Publish, Will Properties
- L149 _public enumerator_ `ContentType = 3` — MessageExpiryInterval = 2,		      4 Byte Int :			Publish, Will Properties
- L150 _public enumerator_ `ResponseTopic = 8` — ContentType = 3,					  Utf-8 String :		Publish, Will Properties
- L151 _public enumerator_ `CorrelationData = 9` — ResponseTopic = 8,				      Utf-8 String :		Publish, Will Properties
- L152 _public enumerator_ `SubscriptionIdentifier = 11` — CorrelationData = 9,				  Binary Data :		Publish, Will Properties
- L153 _public enumerator_ `SessionExpiryInterval = 17` — SubscriptionIdentifier = 11,		  Variable Byte Int :	Publish, Subscribe
- L154 _public enumerator_ `AssignedClientIdentifier = 18` — SessionExpiryInterval = 17,		      4 Byte Int :			Connect, ConnectAcknowledge, Disconnect
- L155 _public enumerator_ `ServerKeepAlive = 19` — AssignedClientIdentifier = 18,	      Utf-8 String :		ConnectAcknowledge
- L156 _public enumerator_ `AuthenticationMethod = 21` — ServerKeepAlive = 19,			      2 Byte Int :			ConnectAcknowledge
- L157 _public enumerator_ `AuthenticationData = 22` — AuthenticationMethod = 21,		      Utf-8 String :		Connect, ConnectAcknowledge, Authorize
- L158 _public enumerator_ `RequestProblemInformation = 23` — AuthenticationData = 22,			  Binary Data :		Connect, ConnectAcknowledge, Authorize
- L159 _public enumerator_ `WillDelayInterval = 24` — RequestProblemInformation = 23,	      Byte :				Connect
- L160 _public enumerator_ `RequestResponseInformation = 25` — WillDelayInterval = 24,			      4 Byte Int :			Will Properties
- L161 _public enumerator_ `ResponseInformation = 26` — RequestResponseInformation = 25,      Byte :				Connect
- L162 _public enumerator_ `ServerReference = 28` — ResponseInformation = 26,		      Utf-8 String :		ConnectAcknowledge
- L163 _public enumerator_ `ReasonString = 31` — ServerReference = 28,			      Utf-8 String :		ConnectAcknowledge, Disconnect
- L164 _public enumerator_ `ReceiveMaximum = 33` — ReasonString = 31,				      Utf-8 String :		All Except Will Properties
- L165 _public enumerator_ `TopicAliasMaximum = 34` — ReceiveMaximum = 33,				  2 Byte Int :			Connect, ConnectAcknowledge
- L166 _public enumerator_ `TopicAlias = 35` — TopicAliasMaximum = 34,			      2 Byte Int :			Connect, ConnectAcknowledge
- L167 _public enumerator_ `MaximumQoS = 36` — TopicAlias = 35,					  2 Byte Int :			Publish
- L168 _public enumerator_ `RetainAvailable = 37` — MaximumQoS = 36,					  Byte :				ConnectAcknowledge
- L169 _public enumerator_ `UserProperty = 38` — RetainAvailable = 37,			      Byte :				ConnectAcknowledge
- L170 _public enumerator_ `MaximumPacketSize = 39` — UserProperty = 38,				      Utf-8 String Pair :	All
- L171 _public enumerator_ `WildcardSubscriptionAvailable = 40` — MaximumPacketSize = 39,			      4 Byte Int :			Connect, ConnectAcknowledge
- L172 _public enumerator_ `SubscriptionIdAvailable = 41` — WildcardSubscriptionAvailable = 40,   Byte :				ConnectAcknowledge
- L173 _public enumerator_ `SharedSubscriptionAvailable = 42` — SubscriptionIdAvailable = 41,	      Byte :				ConnectAcknowledge

#### enum `FMQTTPropertyType`  
`enum class FMQTTPropertyType : uint8`  
_L176-185_
- L178 _public enumerator_ `Byte = 1`
- L179 _public enumerator_ `Int16 = 2`
- L180 _public enumerator_ `Int32 = 3`
- L181 _public enumerator_ `VarInt = 4`
- L182 _public enumerator_ `Binary = 5`
- L183 _public enumerator_ `String = 6`
- L184 _public enumerator_ `StringPair = 7`

#### enum `FMQTTSubscriptionOption`  
`enum class FMQTTSubscriptionOption`  
_L187-194_
- L189 _public enumerator_ `NoLocal = 0x04`
- L190 _public enumerator_ `RetainAsPublished = 0x08` — NoLocal = 0x04,				  Won't receive own messages.
- L191 _public enumerator_ `SendRetainAlways = 0x00` — RetainAsPublished = 0x08,
- L192 _public enumerator_ `SendRetainNew = 0x10`
- L193 _public enumerator_ `SendRetainNever = 0x20`

#### Free symbols / members of external scopes

- L18 _macro_ `#define PROTOCOL_NAME "MQTT"`
- L20 _macro_ `#define PROTOCOL_VERSION_v311 4`
- L21 _macro_ `#define PROTOCOL_VERSION_v5 5`
- L197 _variable_ `constexpr static uint32 GMQTTMaxPayload = 268435455U;` — 256MB MQTT v3.1.1: 2.2.3

### `Plugins/Protocols/MQTT/Source/MQTTCore/Public/MQTTShared.h` (Public)


#### enum `EMQTTScheme`  
`enum class EMQTTScheme : uint8`  
_L18-27_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `MQTT = 0`
- L21 _public enumerator_ `MQTTS = 1` — Secure

#### enum `EMQTTQualityOfService`  
`enum class EMQTTQualityOfService : uint8`  
_L30-35_
- reflection: `UENUM(BlueprintType)`
- L32 _public enumerator_ `Once = 0 UMETA(DisplayName = "QoS 0", Description = "Once (not guaranteed)")`
- L33 _public enumerator_ `AtLeastOnce = 1 UMETA(DisplayName = "QoS 1", Description = "At Least Once (guaranteed)")`
- L34 _public enumerator_ `ExactlyOnce = 2 UMETA(DisplayName = "QoS 2", Description = "Exactly Once (guaranteed)")`

#### struct `FMQTTURL`  
`struct FMQTTURL`  
_L39-99_
- reflection: `USTRUCT(BlueprintType)`
- desc: mqtt[s]://[username][:password]@host.domain[:port]
- L44 _public member_ `FString Host = TEXT("loc` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="URL")`
- L48 _public member_ `int32 Port = 1883;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, AdvancedDisplay, Category="URL")` — Default port is 1883 for MQTT scheme, 8883 for MQTTS.
- L51 _public member_ `FString Username;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="URL")`
- L54 _public member_ `FString Password;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="URL", meta = (EditCondition = "Username"))`
- L57 _public member_ `EMQTTScheme Scheme = EMQTTScheme::MQTT;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, AdvancedDisplay, Category="URL")`
- L59 _public prototype_ `FMQTTURL() = default;`
- L62 _public function_ `explicit FMQTTURL( const FString& InHost, const uint32 InPort = 1883, const FString& InUsername = TEXT(""), const FString& InPassword = TEXT(""), const EMQTTScheme InScheme = EMQTTScheme::MQTT) : Host(InHost), Port(InPort), Username(InUsername), Password(InPassword), Scheme(InScheme)` — Construct from components.
- L77 _public prototype_ `bool GetAddress(ISocketSubsystem* InSocketSubsystem, TSharedPtr<FInternetAddr>& OutAddress) const;`
- L80 _public prototype_ `FGuid ToGuid() const;` — Deterministic FGuid based on the URL.
- L83 _public prototype_ `bool IsValid() const;` — Gets the validity of the URL.
- L86 _public prototype_ `bool IsValid(FText& OutMessage) const;` — Gets the validity of the URL with message.
- L89 _public function_ `void SetInvalid()` — Flags this URL as invalid.
- L92 _public prototype_ `static FMQTTURL FromString(const FString& InURL);` — Parses the input string.
- L95 _public prototype_ `FString ToString() const;` — Get the URL as a string.
- L98 _protected member_ `bool bFlaggedInvalid = false;`

#### struct `FMQTTTopic`  
`struct FMQTTTopic`  
_L107-147_
- reflection: `USTRUCT(BlueprintType)`
- L112 _public member_ `FString Path;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Topic")`
- L114 _public prototype_ `FMQTTTopic() = default;`
- L117 _public function_ `FMQTTTopic(const FString& InPath) : Path(InPath)` — Construct from path.
- L122 _public prototype_ `virtual ~FMQTTTopic() = default;`
- L125 _public prototype_ `static bool IsValid(const FString& InTopic);` — Gets the validity of the input Topic.
- L128 _public prototype_ `virtual bool IsValid() const;` — Gets the validity of the Topic.
- L131 _public prototype_ `virtual void MakeValid();` — Attempts to make the topic valid.
- L134 _public prototype_ `virtual FString ToString() const;` — Get the Topic as a string.
- L137 _public member_ `static constexpr TCHAR TopicLevelSeparatorChar = '/';` — U+002F
- L140 _public member_ `static constexpr TCHAR SingleLevelWildcardChar = '+';` — '+' Must occupy entire level of the filter if it's used
- L143 _public member_ `static constexpr TCHAR MultiLevelWildcardChar = '#';` — '#' Must be specified either on its own or following a topic level separator, must be the last character in the Topic Filter
- L146 _public member_ `static constexpr TCHAR SystemChar = '$';` — Not part of spec, but widely used by servers.

#### struct `FMQTTTopicFilter`  
`struct FMQTTTopicFilter : public FMQTTTopic`  
_L150-165_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMQTTTopic`
- L154 _public function_ `FMQTTTopicFilter()`
- L155 _public prototype_ `virtual ~FMQTTTopicFilter() override = default;`
- L158 _public prototype_ `virtual bool IsValid() const override;` — Gets the validity of the TopicFilter.
- L161 _public prototype_ `virtual void MakeValid() override;` — Attempts to make the topic TopicFilter.
- L164 _public prototype_ `virtual FString ToString() const override;` — Get the TopicFilter as a string.

#### struct `FMQTTTopicTemplate`  
`struct FMQTTTopicTemplate : public FMQTTTopic`  
_L169-175_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMQTTTopic`
- desc: An MQTT Topic tokenized template
- L173 _public prototype_ `bool PopulateTemplate(const FStringFormatNamedArguments& InArgs, FMQTTTopic& OutTopic) const;`

#### struct `FMQTTSubscription`  
`struct FMQTTSubscription`  
_L177-210_
- L180 _public function_ `FMQTTSubscription(const FMQTTTopic& InTopic, const EMQTTQualityOfService InGrantedQoS) : Topic(InTopic) , GrantedQoS(InGrantedQoS)` — Construct from path.
- L186 _public prototype_ `static bool Matches(const FString& InTopic, const FString& InSubscription);`
- L187 _public prototype_ `bool Matches(const FString& InTopic) const;`
- L189 _public function_ `const FMQTTTopic& GetTopic() const`
- L192 _public prototype_ `bool IsValid() const;` — Gets the validity of the Subscription.
- L194 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubscriptionMessage, const FMQTTClientMessage& );`
- L195 _public function_ `FOnSubscriptionMessage& OnSubscriptionMessage()`
- L197 _public function_ `EMQTTQualityOfService GetGrantedQoS() const`
- L207 _private member_ `FMQTTTopic Topic;`
- L208 _private member_ `EMQTTQualityOfService GrantedQoS;`
- L209 _private member_ `FOnSubscriptionMessage OnSubscriptionMessageDelegate;`

#### struct `FMQTTSubscribeResult`  
`struct FMQTTSubscribeResult`  
_L212-226_
- L214 _public prototype_ `FMQTTSubscribeResult() = default;`
- L216 _public function_ `FMQTTSubscribeResult( const EMQTTSubscribeReturnCode InReturnCode, TSharedPtr<FMQTTSubscription, ESPMode::ThreadSafe> InSubscription) : ReturnCode(InReturnCode) , Subscription(MoveTemp(InSubscription))`
- L224 _public member_ `EMQTTSubscribeReturnCode ReturnCode;`
- L225 _public member_ `TSharedPtr<FMQTTSubscription, ESPMode::ThreadSafe> Subscription;`

#### Free symbols / members of external scopes

- L101 _function_ `inline uint32 GetTypeHash(const FMQTTURL& InURL)`
- L194 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubscriptionMessage, const FMQTTClientMessage& );`
- L199 _function_ `friend uint32 GetTypeHash(const FMQTTSubscription& InSubscription)`

### `Plugins/Protocols/MQTT/Source/MQTTCore/Public/MQTTSubsystem.h` (Public)


#### class `UMQTTSubsystem`  
`class UMQTTSubsystem final : public UEngineSubsystem`  
_L21-41_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UEngineSubsystem`
- desc: Provides persistent access to clients
- L27 _public prototype_ `static UMQTTClientObject* GetOrCreateClient_WithProjectURL(UPARAM(DisplayName = "Parent") UObject* InPa` — `UFUNCTION(BlueprintCallable, Category = "MQTT", meta = (DefaultToSelf = "InParent", DisplayName = "Create Client (From Project URL)"))`
- L30 _public prototype_ `static UMQTTClientObject* GetOrCreateClient(UPARAM(DisplayName = "Parent") UObject* InParent, UPARAM(DisplayName = "URL") const FMQTTURL` — `UFUNCTION(BlueprintCallable, Category = "MQTT", meta = (DefaultToSelf = "InParent", DisplayName = "Create Client (From URL)"))`
- L33 _public prototype_ `static FString GetPayloadString(UPARAM(DisplayName = "ClientMessage") const FMQTTClientMessage& InCl` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MQTT")`
- L36 _public prototype_ `static bool GetPayloadJson(UPARAM(DisplayName = "Parent") UObject* InParent, UPARAM(DisplayName = "ClientMessage") const FMQTTClientMessage& InClientMessage, FJsonObjec` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MQTT", meta = (DefaultToSelf = "InParent"))`
- L40 _private member_ `TMap<FGuid, TObjectPtr<UMQTTClientObject>> Clients;` — `UPROPERTY(Transient)`
