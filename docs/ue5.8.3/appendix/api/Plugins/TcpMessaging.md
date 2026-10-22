# Plugins / TcpMessaging

- module root: `Plugins/Messaging/TcpMessaging/Source/TcpMessaging`
- headers: 8; symbols: 158
- symbol kinds: class=7, delegate=2, enum=2, enumerator=10, function=9, macro=5, member=57, namespace=1, prototype=62, struct=1, typedef=2
- DynamicallyLoadedModuleNames: Messaging, Settings
- PrivateDependencyModuleNames: CoreUObject, Networking, Serialization, Sockets
- PrivateIncludePathModuleNames: Messaging, MessagingCommon, Settings
- PublicDependencyModuleNames: Core

### `Plugins/Messaging/TcpMessaging/Source/TcpMessaging/Private/Settings/TcpMessagingSettings.h` (Private)


#### class `UTcpMessagingSettings`  
`class UTcpMessagingSettings : public UObject`  
_L9-74_
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- L17 _public prototype_ `bool IsTransportEnabled() const;` — Returns true if our transport is enabled
- L20 _public prototype_ `FString GetListenEndpoint() const;` — Gets the listen endpoint
- L23 _public prototype_ `void GetConnectToEndpoints(TArray<FString>& Endpoints) const;` — Returns array of connect endpoints
- L26 _public prototype_ `int32 GetConnectionRetryDelay() const;` — Returns reconnection delay
- L29 _public prototype_ `int32 GetConnectionRetryPeriod() const;` — Returns reconnection period
- L32 _public prototype_ `bool ShouldStopServiceWhenAppDeactivates() const;` — Returns whether to stop the transport service when the application deactivates
- L38 _private member_ `bool EnableTransport;` — `UPROPERTY(config, EditAnywhere, Category = Transport)` — Whether the TCP transport channel is enabled
- L46 _private member_ `FString ListenEndpoint;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — The IP endpoint to listen for incoming connections. The format is IP_ADDRESS:PORT_NUMBER or blank to disable listening.
- L55 _private member_ `TArray<FString> ConnectToEndpoints;` — `UPROPERTY(config, EditAnywhere, Category=Transport)` — The IP endpoints to try to establish outgoing connection to. Use this setting to connect to a remote peer. The format is IP_ADDRESS:PORT_NUMBER.
- L62 _private member_ `int32 ConnectionRetryDelay;` — `UPROPERTY(config, EditAnywhere, Category = Transport)` — Delay time between attempts to re-establish outgoing connections that become disconnected or fail to connect 0 disables reconnection
- L69 _private member_ `int32 ConnectionRetryPeriod;` — `UPROPERTY(config, EditAnywhere, Category = Transport)` — Period time during which attempts to re-establish outgoing connections that become disconnected or fail to connect 0 means it will be retried only once
- L73 _private member_ `bool bStopServiceWhenAppDeactivates = true;` — `UPROPERTY(config)` — Whether to stop the transport service when the application deactivates, and restart it when the application is reactivated

### `Plugins/Messaging/TcpMessaging/Source/TcpMessaging/Private/TcpMessagingPrivate.h` (Private)


#### enum `ETcpMessagingVersion::Type`  
`enum Type`  
_L31-43_
- L33 _public enumerator_ `Initial`
- L34 _public enumerator_ `ChangedMessageLengthToInt32`
- L35 _public enumerator_ `ChangedMessageContext`
- L39 _public enumerator_ `VersionPlusOne` — -----<new versions can be added before this line>------------------------------------------------- - this needs to be the last line (see note below)
- L40 _public enumerator_ `LatestVersion = VersionPlusOne - 1`
- L42 _public enumerator_ `OldestSupportedVersion = ChangedMessageLengthToInt32` — bump this when break need to break compatibility.

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTcpMessaging, Log, All);` — Declares a log category for this module.
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTcpMessaging, Log, All);` — Declares a log category for this module.
- L14 _macro_ `#define TCP_MESSAGING_MAX_ANNOTATIONS 128` — Defines the maximum number of annotations a message can have.
- L17 _macro_ `#define TCP_MESSAGING_MAX_RECIPIENTS 1024` — Defines the maximum number of recipients a message can have.
- L20 _macro_ `#define TCP_MESSAGING_SEND_BUFFER_SIZE 2 * 1024 * 1024` — Defines the desired size of socket send buffers (in bytes).
- L23 _macro_ `#define TCP_MESSAGING_RECEIVE_BUFFER_SIZE 2 * 1024 * 1024` — Defines the desired size of socket receive buffers (in bytes).
- L26 _macro_ `#define TCP_MESSAGING_TRANSPORT_PROTOCOL_MAGIC 0x45504943` — Defines a magic number for the the TCP message transport.
- L29 _namespace_ `namespace ETcpMessagingVersion`

### `Plugins/Messaging/TcpMessaging/Source/TcpMessaging/Private/Transport/TcpDeserializedMessage.h` (Private)


#### class `FTcpDeserializedMessage`  
`class FTcpDeserializedMessage : public IMessageContext`  
_L13-85_
- inherits: `IMessageContext`
- desc: Holds a deserialized message.
- L23 _public prototype_ `FTcpDeserializedMessage(const TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe>& InAttachment);` — Creates and initializes a new instance. @param InAttachment An optional message attachment.
- L36 _public prototype_ `bool Deserialize(const TSharedPtr<FArrayReader, ESPMode::ThreadSafe>& Message);` — Deserializes the given reassembled message. @param ReassembledMessage The reassembled message to deserialize. @return true on success, false otherwise.
- L42 _public prototype_ `virtual const TMap<FName, FString>& GetAnnotations() const override;`
- L43 _public prototype_ `virtual TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> GetAttachment() const override;`
- L44 _public prototype_ `virtual const FDateTime& GetExpiration() const override;`
- L45 _public prototype_ `virtual const void* GetMessage() const override;`
- L46 _public prototype_ `virtual const TWeakObjectPtr<UScriptStruct>& GetMessageTypeInfo() const override;`
- L47 _public prototype_ `virtual TSharedPtr<IMessageContext, ESPMode::ThreadSafe> GetOriginalContext() const override;`
- L48 _public prototype_ `virtual const TArray<FMessageAddress>& GetRecipients() const override;`
- L49 _public prototype_ `virtual EMessageScope GetScope() const override;`
- L50 _public prototype_ `virtual EMessageFlags GetFlags() const override;`
- L51 _public prototype_ `virtual const FMessageAddress& GetSender() const override;`
- L52 _public prototype_ `virtual const FMessageAddress& GetForwarder() const override;`
- L53 _public prototype_ `virtual ENamedThreads::Type GetSenderThread() const override;`
- L54 _public prototype_ `virtual const FDateTime& GetTimeForwarded() const override;`
- L55 _public prototype_ `virtual const FDateTime& GetTimeSent() const override;`
- L60 _private member_ `TMap<FName, FString> Annotations;` — Holds the optional message annotations.
- L63 _private member_ `TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> Attachment;` — Holds a pointer to attached binary data.
- L66 _private member_ `FDateTime Expiration;` — Holds the expiration time.
- L69 _private member_ `void* MessageData;` — Holds the message.
- L72 _private member_ `TArray<FMessageAddress> Recipients;` — Holds the message recipients.
- L75 _private member_ `EMessageScope Scope;` — Holds the message's scope.
- L78 _private member_ `FMessageAddress Sender;` — Holds the sender's identifier.
- L81 _private member_ `FDateTime TimeSent;` — Holds the time at which the message was sent.
- L84 _private member_ `TWeakObjectPtr<UScriptStruct> TypeInfo;` — Holds the message's type information.

### `Plugins/Messaging/TcpMessaging/Source/TcpMessaging/Private/Transport/TcpMessageTransport.h` (Private)


#### struct `FNodeConnectionMapUpdate`  
`struct FNodeConnectionMapUpdate`  
_L17-32_
- desc: Entry specfying addition or removal to/from the NodeConnectionMap
- L19 _public function_ `FNodeConnectionMapUpdate(bool bInNewNode, const FGuid& InNodeId, const TWeakPtr<FTcpMessageTransportConnection>& InConnection) : bNewNode(bInNewNode) , NodeId(InNodeId) , Connection(InConnection)`
- L25 _public function_ `FNodeConnectionMapUpdate() : bNewNode(false)`
- L29 _public member_ `bool bNewNode;`
- L30 _public member_ `FGuid NodeId;`
- L31 _public member_ `TWeakPtr<FTcpMessageTransportConnection> Connection;`

#### class `FTcpMessageTransport`  
`class FTcpMessageTransport : FRunnable , public IMessageTransport`  
_L42-129_
- inherits: `FRunnable,IMessageTransport`
- desc: Implements a message transport technology using an Tcp network connection. On platforms that support multiple processes, the transport is using two sockets, one for per-process unicast sending/receiving, and one for multicast receiving. Console and mobile platforms use a single multicast socket for all sending and receiving.
- L52 _public prototype_ `FTcpMessageTransport(const FIPv4Endpoint& InListenEndpoint, const TArray<FIPv4Endpoint>& InConnectToEndpoints, int32 InConnectionRetryDelay, int32 InConnectionRetryPeriod = 0);` — Creates and initializes a new instance.
- L55 _public prototype_ `virtual ~FTcpMessageTransport();` — Virtual destructor.
- L59 _public prototype_ `void AddOutgoingConnection(const FIPv4Endpoint& Endpoint);`
- L60 _public prototype_ `void RemoveOutgoingConnection(const FIPv4Endpoint& Endpoint);`
- L66 _public function_ `virtual FName GetDebugName() const override`
- L71 _public prototype_ `virtual bool StartTransport(IMessageTransportHandler& Handler) override;`
- L72 _public prototype_ `virtual void StopTransport() override;`
- L73 _public prototype_ `virtual bool TransportMessage(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, const TArray<FGuid>& Recipients) override;`
- L79 _public prototype_ `virtual void Exit() override;`
- L80 _public prototype_ `virtual bool Init() override;`
- L81 _public prototype_ `virtual uint32 Run() override;`
- L82 _public prototype_ `virtual void Stop() override;`
- L87 _private prototype_ `bool HandleListenerConnectionAccepted(FSocket* ClientSocket, const FIPv4Endpoint& ClientEndpoint);` — Callback for accepted connections to the local server.
- L90 _private prototype_ `void HandleConnectionStateChanged(TSharedPtr<FTcpMessageTransportConnection> Connection);` — Callback from connections for node discovery/loss
- L95 _private member_ `FIPv4Endpoint ListenEndpoint;` — Current settings
- L96 _private member_ `TArray<FIPv4Endpoint> ConnectToEndpoints;`
- L97 _private member_ `int32 ConnectionRetryDelay;`
- L98 _private member_ `int32 ConnectionRetryPeriod;`
- L101 _private member_ `bool bStopping;` — For the thread
- L104 _private member_ `ISocketSubsystem* SocketSubsystem;` — Holds a pointer to the socket sub-system.
- L107 _private member_ `FTcpListener* Listener;` — Holds the local listener for incoming tunnel connections.
- L110 _private member_ `TArray<TSharedPtr<FTcpMessageTransportConnection>> Connections;` — Current connections
- L113 _private member_ `TMap<FGuid, TSharedPtr<FTcpMessageTransportConnection>> NodeConnectionMap;` — Map nodes to connections. We do not transport unicast messages for unknown nodes.
- L116 _private member_ `TQueue<FNodeConnectionMapUpdate, EQueueMode::Mpsc> NodeConnectionMapUpdates;` — Holds a queue of changes to NodeConnectionMap.
- L119 _private member_ `TQueue<TSharedPtr<FTcpMessageTransportConnection>, EQueueMode::Mpsc> PendingConnections;` — Holds a queue of pending connections.
- L122 _private member_ `TQueue<FIPv4Endpoint, EQueueMode::Mpsc> ConnectionEndpointsToRemove;` — Queue of enpoints describing connection we want to remove
- L125 _private member_ `FRunnableThread* Thread;` — Holds the thread object.
- L128 _private member_ `IMessageTransportHandler* TransportHandler;` — Message transport handler.

### `Plugins/Messaging/TcpMessaging/Source/TcpMessaging/Private/Transport/TcpMessageTransportConnection.h` (Private)


#### class `FTcpMessageTransportConnection`  
`class FTcpMessageTransportConnection : public FRunnable , public TSharedFromThis<FTcpMessageTransportConnection>`  
_L22-231_
- inherits: `FRunnable,TSharedFromThis<FTcpMessageTransportConnection>`
- desc: Implements a TCP message tunnel connection.
- L45 _public prototype_ `FTcpMessageTransportConnection(FSocket* InSocket, const FIPv4Endpoint& InRemoteEndpoint, int32 InConnectionRetryDelay, int32 InConnectionRetryPeriod = 0);` — Creates and initializes a new instance. @param InSocket The socket to use for this connection. @param InRemoteAddress The IP endpoint of the remote client. @param int32 InConnectionRetryDelay Delay before retrying connection, 0 disables @param int32 InConnectionRetryPeriod period during which retrying connection, 0 means to retry only once
- L48 _public prototype_ `virtual ~FTcpMessageTransportConnection();` — Virtual destructor.
- L54 _public prototype_ `void Start();` — Starts processing of the connection. Needs to be called immediately after construction
- L63 _public prototype_ `bool Receive(TSharedPtr<FTcpDeserializedMessage, ESPMode::ThreadSafe>& OutMessage, FGuid& OutSenderNodeId);` — Receives a message from the connection's inbox. @param OutMessage will hold the received message, if any. @return true if a message was returned, false otherwise. @see Send
- L71 _public prototype_ `bool Send(FTcpSerializedMessagePtr Message);` — Sends a serialized message through this connection. @param Message The message to send. @see Receive
- L74 _public prototype_ `void Close();` — Closes this connection.
- L81 _public prototype_ `uint64 GetTotalBytesReceived() const;` — Gets the total number of bytes received from this connection. @return Number of bytes.
- L88 _public prototype_ `uint64 GetTotalBytesSent() const;` — Gets the total number of bytes received from this connection. @return Number of bytes.
- L95 _public prototype_ `FText GetName() const;` — Gets the human readable name of the connection. @return Connection name.
- L102 _public prototype_ `FTimespan GetUptime() const;` — Gets the amount of time that the connection has been established. @return Time span.
- L109 _public prototype_ `EConnectionState GetConnectionState() const;` — Gets the current state of the connection. @return EConnectionState current state.
- L116 _public prototype_ `FGuid GetRemoteNodeId() const;` — Gets the remote node's id @return FGuid the remote node's id, or and invalid FGuid if there is no current valid remote node id.
- L123 _public function_ `FIPv4Endpoint GetRemoteEndpoint() const` — Gets the IP address and port of the remote connection @return FIPv4Endpoint remote connection's IP address and port
- L130 _public function_ `FOnTcpMessageTransportConnectionStateChanged& OnTcpMessageTransportConnectionStateChanged()` — Gets the delegate which will be called whenever the connection state changes @return FOnTcpMessageTransportConnectionStateChanged delegate
- L143 _protected prototype_ `bool ReceiveMessages();` — Receives all pending messages from the socket. @return true on success, false otherwise. @see SendMessages
- L150 _protected prototype_ `bool SendHeader();` — Sends header to the socket. @return true on success, false otherwise.
- L156 _private prototype_ `virtual bool Init() override;`
- L157 _private prototype_ `virtual uint32 Run() override;`
- L158 _private prototype_ `virtual void Stop() override;`
- L159 _private prototype_ `virtual void Exit() override;`
- L164 _private prototype_ `bool ChunkedBlockingSend(const TArray<uint8>& Payload);` — Split the send data into chunks until all data is sent.
- L167 _private prototype_ `bool BlockingSend(const uint8* Data, int32 BytesToSend);` — Try to send data, but if all data is not sent in one go, block on send until data is sent or an error occurs
- L170 _private member_ `FOnTcpMessageTransportConnectionStateChanged ConnectionStateChangedDelegate;` — Connection state changed delegate
- L173 _private member_ `EConnectionState ConnectionState;` — Current connection state
- L176 _private member_ `FDateTime ClosedTime;` — Holds the time at which the connection was closed.
- L179 _private member_ `TQueue<TSharedPtr<FTcpDeserializedMessage, ESPMode::ThreadSafe>, EQueueMode::Mpsc> Inbox;` — Holds the collection of received Messages.
- L182 _private member_ `FDateTime OpenedTime;` — Holds the time at which the connection was opened.
- L185 _private member_ `FIPv4Endpoint RemoteEndpoint;` — Holds the IP endpoint of the remote client.
- L188 _private member_ `FGuid LocalNodeId;` — Local Node Id
- L191 _private member_ `FGuid RemoteNodeId;` — Remote Node Id
- L194 _private member_ `bool bSentHeader;` — Whether we've sent the initial header to the remote end
- L197 _private member_ `bool bReceivedHeader;` — Whether we've received the initial header from the remote end
- L200 _private member_ `uint32 RemoteProtocolVersion;` — Peer's value for of ETcpMessagingVersion::LatestVersion
- L203 _private member_ `FSocket* Socket;` — Holds the connection socket.
- L206 _private member_ `FRunnableThread* Thread;` — Holds the thread object.
- L209 _private member_ `uint64 TotalBytesReceived;` — Holds the total number of bytes received from the connection.
- L212 _private member_ `uint64 TotalBytesSent;` — Holds the total number of bytes sent to the connection.
- L215 _private member_ `bool bRun;` — thread should continue running.
- L218 _private member_ `int32 ConnectionRetryDelay;` — Delay before re-establishing connection if it drops, 0 disables
- L221 _private member_ `int32 ConnectionRetryPeriod;` — Period during which re-establishing connection if it drops, 0 means it will retry only once
- L224 _private member_ `TSharedPtr<FArrayReader, ESPMode::ThreadSafe> RecvMessageData;` — Message data we're currently in the process of receiving, if any
- L227 _private member_ `int32 RecvMessageDataRemaining;` — The number of bytes of incoming message data we're still waiting on before we have a complete message
- L230 _private member_ `FCriticalSection SendCriticalSection;` — Critical section preventing multiple threads from sending simultaneously

#### enum `FTcpMessageTransportConnection::EConnectionState`  
`enum EConnectionState`  
_L29-35_
- desc: Connection state
- L31 _public enumerator_ `STATE_Connecting` — connecting but don't yet have RemoteNodeId
- L32 _public enumerator_ `STATE_Connected` — connected and RemoteNodeId is valid
- L33 _public enumerator_ `STATE_DisconnectReconnectPending` — disconnected with reconnect pending. Previous RemoteNodeId is retained
- L34 _public enumerator_ `STATE_Disconnected` — disconnected. Previous RemoteNodeId is retained

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE(FOnTcpMessageTransportConnectionStateChanged) class FTcpMessageTransportConnection : public FRunnable , public TSharedFromThis<FTcpMessageTransportConnection> { public: enum EConnectionState { STATE_Connecting,` — Delegate type for announcing a connection state change

### `Plugins/Messaging/TcpMessaging/Source/TcpMessaging/Private/Transport/TcpSerializeMessageTask.h` (Private)


#### class `FTcpSerializeMessageTask`  
`class FTcpSerializeMessageTask`  
_L16-73_
- desc: Implements an asynchronous task for serializing a message.
- L26 _public function_ `FTcpSerializeMessageTask(TSharedRef<IMessageContext, ESPMode::ThreadSafe> InMessageContext, FTcpSerializedMessageRef InSerializedMessage, const TArray<TSharedPtr<FTcpMessageTransportConnection>>& InRecipientConnections) : MessageContext(InMessageContext) , SerializedMessage(InSerializedMessage) , RecipientConnections(InRecipientConnections)` — Creates and initializes a new instance. @param InMessageContext The context of the message to serialize. @param InSerializedMessage Will hold the serialized message data.
- L40 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);` — Performs the actual task. @param CurrentThread The thread that this task is executing on. @param MyCompletionGraphEvent The completion event.
- L47 _public prototype_ `ENamedThreads::Type GetDesiredThread();` — Returns the name of the thread that this task should run on. @return Thread name.
- L54 _public prototype_ `TStatId GetStatId() const;` — Gets the task's stats tracking identifier. @return Stats identifier.
- L61 _public prototype_ `static ESubsequentsMode::Type GetSubsequentsMode();` — Gets the mode for tracking subsequent tasks. @return Always track subsequent tasks.
- L66 _private member_ `TSharedRef<IMessageContext, ESPMode::ThreadSafe> MessageContext;` — Holds the context of the message to serialize.
- L69 _private member_ `FTcpSerializedMessageRef SerializedMessage;` — Holds a reference to the serialized message data.
- L72 _private member_ `TArray<TSharedPtr<FTcpMessageTransportConnection>> RecipientConnections;` — Connections we're going to enqueue the serialized message for

### `Plugins/Messaging/TcpMessaging/Source/TcpMessaging/Private/Transport/TcpSerializedMessage.h` (Private)


#### class `FTcpSerializedMessage`  
`class FTcpSerializedMessage : public FMemoryWriter`  
_L12-51_
- inherits: `FMemoryWriter`
- desc: Holds serialized message data.
- L18 _public function_ `FTcpSerializedMessage() : FMemoryWriter(DataArray, true)` — Default constructor.
- L31 _public function_ `FArchive* CreateReader()` — Creates an archive reader to the data. The caller is responsible for deleting the returned object. @return An archive reader.
- L42 _public function_ `const TArray<uint8>& GetDataArray()` — Get the serialized message data. @return Byte array of message data. @see GetState
- L50 _private member_ `TArray<uint8> DataArray;` — Holds the serialized data.

#### Free symbols / members of external scopes

- L55 _typedef_ `typedef TSharedPtr<FTcpSerializedMessage, ESPMode::ThreadSafe> FTcpSerializedMessagePtr;` — Type definition for shared pointers to instances of FTcpSerializedMessage.
- L58 _typedef_ `typedef TSharedRef<FTcpSerializedMessage, ESPMode::ThreadSafe> FTcpSerializedMessageRef;` — Type definition for shared references to instances of FTcpSerializedMessage.

### `Plugins/Messaging/TcpMessaging/Source/TcpMessaging/Public/ITcpMessagingModule.h` (Public)


#### class `ITcpMessagingModule`  
`class ITcpMessagingModule : public IModuleInterface`  
_L13-20_
- inherits: `IModuleInterface`
- desc: IConnectionBasedMessagingModule interface allows adding/removing of connections.
- L18 _public prototype_ `virtual void AddOutgoingConnection(const FString& Endpoint) = 0;`
- L19 _public prototype_ `virtual void RemoveOutgoingConnection(const FString& Endpoint) = 0;`
