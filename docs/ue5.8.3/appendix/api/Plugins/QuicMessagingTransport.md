# Plugins / QuicMessagingTransport

- module root: `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport`
- headers: 16; symbols: 426
- symbol kinds: class=6, delegate=14, enum=12, enumerator=56, function=51, macro=5, member=131, namespace=2, prototype=124, struct=15, typedef=10
- PrivateDependencyModuleNames: Messaging, Networking, SSL
- PublicDependencyModuleNames: Core, MsQuic, MsQuicRuntime

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Private/QuicBuffers.h` (Private)


#### struct `FInboundBuffer`  
`struct FInboundBuffer`  
_L16-51_
- L19 _public member_ `bool bHeaderDeserialized;` — Flag indicating whether the header was deserialized.
- L22 _public member_ `QUIC_ADDR HandlerAddress;` — Holds the Quic handler address.
- L25 _public member_ `FIPv4Endpoint HandlerEndpoint;` — Holds the Quic handler endpoint.
- L28 _public member_ `FMessageHeader MessageHeader;` — Holds the message header.
- L31 _public member_ `FQuicPayloadPtr InboundData;` — Holds the inbound data.
- L34 _public function_ `FInboundBuffer() : bHeaderDeserialized(false) , HandlerAddress(QUIC_ADDR()) , HandlerEndpoint(FIPv4Endpoint::Any) , MessageHeader(FMessageHeader()) , InboundData(nullptr)` — Default constructor.
- L43 _public function_ `FInboundBuffer(const QUIC_ADDR InHandlerAddress, const FIPv4Endpoint InHandlerEndpoint, const FQuicPayloadPtr InInboundData) : bHeaderDeserialized(false) , HandlerAddress(InHandlerAddress) , HandlerEndpoint(InHandlerEndpoint) , MessageHeader(FMessageHeader()) , InboundData(InInboundData)` — Creates and initializes a new instance.

#### struct `FInboundQuicBuffer`  
`struct FInboundQuicBuffer`  
_L53-94_
- L56 _public member_ `uint64 StreamId;` — Holds the Quic stream ID.
- L59 _public member_ `HQUIC Stream;` — Holds the Quic stream handle.
- L62 _public member_ `bool bEndOfStream;` — Flag indicating whether this is the end of the Quic stream.
- L65 _public member_ `FIPv4Endpoint PeerAddress;` — Holds the peer address.
- L68 _public member_ `uint64 BufferLength;` — Holds the total length of all buffers.
- L71 _public member_ `TMap<uint8*, uint32> Data;` — Holds buffer pointers and buffer sizes.
- L74 _public function_ `FInboundQuicBuffer() : StreamId(0) , Stream(nullptr) , bEndOfStream(false) , PeerAddress(FIPv4Endpoint::Any) , BufferLength(0) , Data(TMap<uint8*, uint32>())` — Default constructor.
- L84 _public function_ `FInboundQuicBuffer(const uint64 InStreamId, HQUIC InStream, const bool bInEndOfStream, const FIPv4Endpoint InPeerAddress, const uint64 InBufferLength) : StreamId(InStreamId) , Stream(InStream) , bEndOfStream(bInEndOfStream) , PeerAddress(InPeerAddress) , BufferLength(InBufferLength) , Data(TMap<uint8*, uint32>())` — Creates and initializes a new instance.

#### Free symbols / members of external scopes

- L13 _typedef_ `using FQuicPayloadPtr = TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe>;`

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Private/QuicCertificate.h` (Private)


#### struct `QuicCertificateUtils::QUIC_CREDENTIAL_CONFIG_HELPER`  
`typedef struct QUIC_CREDENTIAL_CONFIG_HELPER`  
_L19-25_
- desc: Helper to setup a QUIC credential config.
- L21 _public member_ `QUIC_CREDENTIAL_CONFIG CredConfig;`
- L23 _public member_ `QUIC_CERTIFICATE_FILE CertificateFile;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace QuicCertificateUtils`
- L25 _typedef_ `} QUIC_CREDENTIAL_CONFIG_HELPER;` (scope `QuicCertificateUtils`)
- L33 _function_ `inline bool GeneratePrivateKey(EVP_PKEY* PrivateKey)` (scope `QuicCertificateUtils`) — Generate a 2048-bit RSA key. @param PrivateKey The private key struct
- L65 _function_ `inline char* PrivateKeyToString(EVP_PKEY* PrivateKey)` (scope `QuicCertificateUtils`) — Converts a private key to a string. @param PrivateKey The private key struct
- L96 _function_ `inline bool GenerateCertificate(EVP_PKEY* PrivateKey, X509* x509)` (scope `QuicCertificateUtils`) — Generate self-signed x509 certificate. @param PrivateKey The private key struct @param x509 The certificate struct
- L141 _function_ `inline char* X509ToString(X509* x509)` (scope `QuicCertificateUtils`) — Convert a certificate to a string. @param x509 The certificate struct
- L160 _function_ `inline TTuple<FString, FString> GetSelfSignedPaths()` (scope `QuicCertificateUtils`) — Get the paths for self-signed certificate and key.
- L179 _function_ `inline bool CreateSelfSigned()` (scope `QuicCertificateUtils`) — Generates a self-signed certificate and returns paths to (certificate, private key).

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Private/QuicClient.h` (Private)


#### class `FQuicClient`  
`class FQuicClient : public FQuicEndpoint , public FQuicQueues`  
_L15-225_
- inherits: `FQuicEndpoint,FQuicQueues`
- desc: Implements the QuicClient.
- L22 _public prototype_ `FQuicClient() = delete;`
- L27 _public function_ `FQuicClient(TSharedRef<FQuicClientConfig> InClientConfig, HQUIC InQuicConfig, const QUIC_API_TABLE* InMsQuic, HQUIC InRegistration, const TCHAR* InThreadName) : FQuicEndpoint(InClientConfig, InQuicConfig, InMsQuic, InRegistration, InThreadName) , ClientConnection(nullptr) , ClientConfig(InClientConfig)` — Creates and initializes a new quic client.
- L41 _protected prototype_ `virtual void StartEndpoint() override;` — Starts the configured QUIC client.
- L48 _public prototype_ `virtual void StopEndpoint() override;` — Stops the QUIC client.
- L53 _public prototype_ `virtual bool IsEndpointReady() override;` — Indicates if the client is connected and ready to send/receive messages.
- L60 _public prototype_ `virtual void UpdateEndpoint() override;` — Periodically called to update the endpoint (consume messages).
- L68 _protected prototype_ `virtual void ConsumeInboundMessages() override;` — Dequeue inbound messages until MaxConsumeTime is reached. Inbound messages are passed to QuicEndpointManager for validation.
- L74 _protected prototype_ `virtual void ProcessInboundBuffers() override;` — Dequeue inbound buffers until MaxConsumeTime is reached. Inbound buffers via QUIC are copied into our buffers until the stream end is indicated.
- L80 _protected prototype_ `virtual void ConsumeOutboundMessages() override;` — Dequeue outbound messages until MaxConsumeTime is reached. Outbound messages will then be sent via QUIC.
- L87 _protected prototype_ `virtual void CollectStatistics() override;` — Collects, converts and passes QUIC connection stats to the EndpointManager.
- L96 _public prototype_ `virtual void EnqueueOutboundMessage(const FOutboundMessage& OutboundMessage) override;` — Enqueues an outbound message on the client. @param OutboundMessage The outbound message
- L103 _public prototype_ `virtual void SendHello(FIPv4Endpoint RemoteEndpoint) override;` — Sends a hello message to the remote endpoint. @param RemoteEndpoint The remote endpoint
- L108 _public prototype_ `virtual void SendBye() override;` — Sends a bye message to the remote endpoint.
- L119 _protected prototype_ `_Function_class_(QUIC_CONNECTION_CALLBACK) static QUIC_STATUS ClientConnectionCallback(HQUIC Connection, void* Context, QUIC_CONNECTION_EVENT* Event);` — Callback for client connections. @param Connection The QUIC connection handle @param Context The app context (FQuicServer) @param Event The connection event
- L130 _protected prototype_ `_Function_class_(QUIC_STREAM_CALLBACK) static QUIC_STATUS ClientStreamCallback(HQUIC Stream, void* Context, QUIC_STREAM_EVENT* Event);` — Callback for client streams. @param Stream The QUIC stream handle @param Context The app context (FQuicServer) @param Event The stream event
- L139 _protected prototype_ `void OnConnectionConnected();` — Handles a connection after the handshake was completed.
- L146 _protected prototype_ `void OnConnectionShutdownByTransport(QuicUtils::HRESULT Status);` — Handles a connection after it was killed due to idle timeout. @param Status The shutdown event status
- L153 _protected prototype_ `void OnConnectionShutdownByPeer(QUIC_UINT62 ErrorCode);` — Handles a connection after it was killed by the peer. @param ErrorCode The QUIC error code
- L161 _protected prototype_ `void OnConnectionShutdownComplete(HQUIC Connection, BOOLEAN AppCloseInProgress);` — Handles a connection after its shutdown was completed, ready for cleanup. @param Connection The connection handle @param AppCloseInProgress Boolean indicating whether app close is already in progress
- L168 _protected prototype_ `void OnConnectionResumptionTicketReceived();` — Handles a received connection resumption ticket. @note Does not do anything at this time
- L175 _protected prototype_ `void OnConnectionPeerStreamStarted(HQUIC Stream);` — Handles when a peer started a stream. @param Stream The stream handle
- L182 _protected prototype_ `void OnStreamShutdownComplete(HQUIC Stream) const;` — Handles a stream when both directions have been shut down, safe for cleanup. @param Stream The stream handle
- L191 _protected prototype_ `void SendToStream(const FOutboundMessage& OutboundMessage);` — Sends the outbound buffers to the remote endpoint. @param OutboundMessage The outbound message
- L202 _protected prototype_ `bool ReceiveFromStream(const FInboundQuicBuffer& QuicBuffer);` — Copy data from a stream buffer. @param QuicBuffer The inbound QUIC buffer @return Whether the operation succeeded
- L209 _protected prototype_ `void ReachedEndOfStream(const FInboundQuicBuffer& QuicBuffer);` — Prepares inbound data for processing. @param QuicBuffer The inbound QUIC buffer
- L214 _protected member_ `HQUIC ClientConnection;` — Holds the QUIC API client connection handle.
- L217 _protected member_ `EQuicClientState ConnectionState = EQuicClientState::Connecting;` — Current client connection state.
- L220 _protected member_ `bool bTransportClosed = false;` — Indicates whether the transport is closed.
- L223 _protected member_ `TSharedRef<FQuicClientConfig> ClientConfig;` — Holds the client config.

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Private/QuicEndpoint.h` (Private)


#### class `FQuicEndpoint`  
`class FQuicEndpoint : public FRunnable , private FSingleThreadRunnable`  
_L45-502_
- inherits: `FRunnable,FSingleThreadRunnable`
- desc: The base class for FQuicServers and FQuicClients.
- L52 _protected prototype_ `FQuicEndpoint() = delete;`
- L63 _protected function_ `FQuicEndpoint(TSharedRef<FQuicEndpointConfig> InEndpointConfig, HQUIC InQuicConfig, const QUIC_API_TABLE* InMsQuic, HQUIC InRegistration, const TCHAR* InThreadName) : Endpoint(InEndpointConfig->Endpoint) , LocalNodeId(InEndpointConfig->LocalNodeId) , QuicConfig(InQuicConfig) , MsQuic(InMsQuic) , Registration(InRegistration) , bStopping(false) , Thread(nullptr) , ThreadName(InThreadName) , InboundBuffers(TMap<FAddrStream, FInboundBuffer>())` — Creates and initializes a quic endpoint. @param InEndpointConfig The endpoint config @param InQuicConfig The QUIC API endpoint config @param InMsQuic The QUIC API table handle @param InRegistration The QUIC API registration handle @param InThreadName The thread name
- L80 _protected function_ `virtual ~FQuicEndpoint()` — Destruct QUIC endpoint.
- L94 _public prototype_ `void Start();` — Start the thread and QUIC endpoint.
- L101 _public prototype_ `uint32 Run() override;` — Continuously updates the endpoint.
- L103 _public prototype_ `void Stop() override;`
- L110 _protected prototype_ `virtual void StartEndpoint() = 0;` — Starts the configured QUIC endpoint.
- L117 _public prototype_ `virtual void StopEndpoint() = 0;` — Stops the QUIC endpoint.
- L122 _public prototype_ `virtual bool IsEndpointReady() = 0;` — Indicates if the endpoint is ready to send and receive messages.
- L127 _public function_ `bool IsStopping() const` — Indicates whether the endpoint is stopping.
- L138 _public function_ `virtual bool HasHandler(const FIPv4Endpoint HandlerEndpoint)` — Checks if a QuicServer has a handler with this endpoint. @param HandlerEndpoint The handler endpoint @note This is only valid for QuicServers
- L145 _public prototype_ `virtual void UpdateEndpoint() = 0;` — Periodically called to update the endpoint (consume messages and ping).
- L152 _protected prototype_ `void UpdateStatistics();` — Periodically called within UpdateEndpoint to updated QUIC connection stats.
- L157 _protected prototype_ `virtual void CollectStatistics() = 0;` — Collects, converts and passes QUIC connection stats to the EndpointManager.
- L167 _public function_ `virtual void SetHandlerAuthenticated(const FIPv4Endpoint& Handler)` — Marks a handler of a QuicServer as authenticated. @param Handler The handler endpoint @note This is only valid for QuicServers
- L175 _public function_ `virtual void DisconnectHandler(const FIPv4Endpoint& HandlerEndpoint)` — Disconnects a handler. @param HandlerEndpoint The handler endpoint @note This is only valid for QuicServer
- L184 _public prototype_ `virtual void EnqueueOutboundMessage(const FOutboundMessage& OutboundMessage) = 0;` — Enqueues an outbound message on the endpoint. @param OutboundMessage The outbound message
- L191 _public prototype_ `virtual void SendHello(FIPv4Endpoint RemoteEndpoint) = 0;` — Sends a hello message to the remote endpoint. @param RemoteEndpoint The remote endpoint
- L196 _public prototype_ `virtual void SendBye() = 0;` — Sends a bye message to the remote endpoint(s).
- L205 _protected prototype_ `uint64 GetStreamId(HQUIC Stream) const;` — Helper to get the streamId from a QUIC stream. @param Stream The QUIC stream handle
- L213 _protected prototype_ `QUIC_STATUS GetConnectionStats( HQUIC Connection, QUIC_STATISTICS& ConnectionStats);` — Helper to get the connection level stats. @param Connection The connection handle @param ConnectionStats The QUIC statistics container
- L222 _protected prototype_ `FMessageTransportStatistics ConvertStatistics( FIPv4Endpoint StatsEndpoint, QUIC_STATISTICS& QuicStats);` — Helper to convert QUIC endpoint statistics to MessageTransportStatistics. @param StatsEndpoint The endpoint which the statistics originate from @param QuicStats The QUIC endpoint statistics
- L247 _protected prototype_ `void OnStreamSendComplete(const HQUIC Stream, void* Context);` — Handles a stream when all data has been sent and the buffers can be released. @param Stream The stream handle @param Context The app context (QUIC_ADDR)
- L256 _protected prototype_ `void OnStreamReceive(const HQUIC Stream, const FIPv4Endpoint PeerAddress, const QUIC_STREAM_EVENT* Event);` — Handles received data from the peer. @param Stream The stream handle @param PeerAddress The peer address @param Event The stream event
- L264 _protected prototype_ `void OnStreamPeerSendAborted(const HQUIC Stream) const;` — Handles a stream when the peer has aborted sending. @param Stream The stream handle
- L278 _protected prototype_ `void RegisterStreamMessage( const uint64 StreamId, const FIPv4Endpoint PeerAddress, const bool bIsMetaOnly, const FOutboundMessage& OutboundMessage, const FQuicBufferRef& MetaBuffer, const FQuicBufferRef& MessageBuffer);` — Register a stream with a MessageId and buffers for cleanup reference. @param StreamId The stream ID @param PeerAddress The peer address @param bIsMetaOnly Flag indicating whether the message is meta-only @param OutboundMessage The outbound message @param MetaBuffer SharedRef to the meta buffer @param MessageBuffer SharedRef to the message buffer
- L290 _protected prototype_ `QUIC_ADDR GetAddressFromEndpoint(FIPv4Endpoint RemoteEndpoint) const;` — Convert an endpoint to a QUIC address. @param RemoteEndpoint The endpoint to convert
- L297 _protected prototype_ `FIPv4Endpoint GetEndpointFromAddress(QUIC_ADDR RemoteAddress) const;` — Convert a QUIC address to an endpoint. @param RemoteAddress The address to convert
- L309 _public function_ `FOnMessageInbound& OnMessageInbound()` — Delegate for when a message has been received by the endpoint and needs to be checked. This delegate must be bound before the endpoint thread is started with the Start() method. It cannot be unbound while the thread is running. @return The delegate
- L324 _public function_ `FOnSerializeHeader& OnSerializeHeader()` — Delegate for when a header needs to be serialized. This delegate must be bound before the endpoint thread is started with the Start() method. It cannot be unbound while the thread is running. @return The delegate
- L337 _public function_ `FOnDeserializeHeader& OnDeserializeHeader()` — Delegate for when a header needs to be deserialized. This delegate must be bound before the endpoint thread is started with the Start() method. It cannot be unbound while the thread is running. @return The delegate
- L352 _public function_ `FOnEndpointDisconnected& OnEndpointDisconnected()` — Delegate for when an endpoint has disconnected or the connection failed. This delegate must be bound before the endpoint thread is started with the Start() method. It cannot be unbound while the thread is running. @return The delegate
- L367 _public function_ `FOnEndpointConnected& OnEndpointConnected()` — Delegate for when an endpoint has connected. This delegate must be bound before the endpoint thread is started with the Start() method. It cannot be unbound while the thread is running. @return The delegate
- L382 _public function_ `FOnStatisticsUpdated& OnStatisticsUpdated()` — Delegate for when the statistics for an endpoint are updated. This delegate must be bound before the endpoint thread is started with the Start() method. It cannot be unbound while the thread is running. @return The delegate
- L391 _protected function_ `virtual void Tick() override`
- L399 _protected member_ `FIPv4Endpoint Endpoint;` — Holds the IP address (and port) that the socket will be bound to.
- L402 _protected member_ `FGuid LocalNodeId;` — Holds the local node identifier.
- L405 _protected member_ `HQUIC QuicConfig;` — Holds the QUIC API config.
- L408 _protected member_ `const QUIC_API_TABLE* MsQuic;` — Holds the QUIC API handle.
- L411 _protected member_ `HQUIC Registration;` — Holds the QUIC API registration handle.
- L414 _protected member_ `bool bStopping;` — Flag indicating that thread is stopping.
- L417 _protected member_ `FRunnableThread* Thread;` — The thread object.
- L420 _protected member_ `FString ThreadName;` — The endpoint thread's name.
- L423 _protected member_ `EQuicEndpointError EndpointError = EQuicEndpointError::Normal;` — Current endpoint error.
- L457 _protected member_ `TMap<FAddrStream, FMessageMeta> StreamMessages;` — Holds QUIC streamIds and associated messages.
- L460 _protected member_ `mutable FCriticalSection StreamMessagesCS;` — Holds the StreamMessages critical section.
- L463 _protected member_ `TMap<FAddrStream, FInboundBuffer> InboundBuffers;` — Holds the inbound buffers.
- L466 _protected member_ `mutable FCriticalSection InboundBuffersCS;` — Holds the InboundBuffers critical section.
- L469 _protected member_ `TQueue<FInboundQuicBuffer> InboundQuicBuffers;` — Holds the inbound MsQuic buffers.
- L474 _protected member_ `bool bUpdatingStatistics = false;` — Flag indicating if statistics are currently being updated.
- L477 _protected member_ `double LastStatsPoll = FPlatformTime::Seconds();` — Holds timestamp of when statistics have last been updated.
- L480 _protected member_ `const FTimespan StatsPollInterval = 10000000;` — Holds the interval for statistics updates.
- L485 _protected member_ `FOnMessageInbound MessageInboundDelegate;` — Holds the message inbound delegate.
- L488 _protected member_ `FOnSerializeHeader SerializeHeaderDelegate;` — Holds the serialize header delegate.
- L491 _protected member_ `FOnDeserializeHeader DeserializeHeaderDelegate;` — Holds the deserialize header delegate.
- L494 _protected member_ `FOnEndpointDisconnected EndpointDisconnectedDelegate;` — Holds the endpoint disconnected delegate.
- L497 _protected member_ `FOnEndpointConnected EndpointConnectedDelegate;` — Holds the endpoint connected delegate.
- L500 _protected member_ `FOnStatisticsUpdated StatisticsUpdatedDelegate;` — Holds the statistics updated delegate.

#### struct `FQuicEndpoint::FStreamCallbackInfo`  
`struct FStreamCallbackInfo`  
_L230-237_
- desc: Struct for QuicCallbacks to pass information to event handlers.
- L233 _public member_ `FIPv4Endpoint* PeerAddress;` — Holds a pointer to the peer address.
- L236 _public member_ `FQuicEndpoint* Endpoint;` — Holds a pointer to either the FQuicServer or FQuicClient.

#### struct `FQuicEndpoint::FMessageMeta`  
`struct FMessageMeta`  
_L427-454_
- L430 _public member_ `bool bIsMetaOnly;` — Holds a flag indicating whether there is only a meta buffer.
- L433 _public member_ `bool bMetaSent;` — Holds a flag indicating whether the meta buffer has been sent.
- L436 _public member_ `FOutboundMessage OutboundMessage;` — Holds the outbound message.
- L439 _public member_ `FQuicBufferRef MetaBuffer;` — Holds the meta buffer.
- L442 _public member_ `FQuicBufferRef MessageBuffer;` — Holds the message buffer.
- L445 _public function_ `FMessageMeta( const bool bInIsMetaOnly, const FOutboundMessage InOutboundMessage, const FQuicBufferRef InMetaBuffer, const FQuicBufferRef InMessageBuffer) : bIsMetaOnly(bInIsMetaOnly) , bMetaSent(false) , OutboundMessage(InOutboundMessage) , MetaBuffer(InMetaBuffer) , MessageBuffer(InMessageBuffer)` — Creates and initializes a new instance.

#### Free symbols / members of external scopes

- L25 _typedef_ `using FQuicBufferRef = TSharedRef<QUIC_BUFFER, ESPMode::ThreadSafe>;`
- L26 _typedef_ `using FAddrStream = TPair<FIPv4Endpoint, uint64>;`
- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMessageInbound, const FInboundMessage ) DECLARE_DELEGATE_RetVal_OneParam(FQuicPayloadPtr, FOnSerializeHeader, FMessageHeader& ) DECLARE_DELEGATE_RetVal_OneParam(FMessageHeader, FOnDeserializeHeader, FQuicPayloadPtr ) DECLARE_DELEGATE_TwoParams(FOnEndpointDisconnected, const FIPv4Endpoint , EQuicEndpointError ) DECLARE_DELEGATE_OneParam(FOnEndpointConnected, const FIPv4Endpoint& ) DECLARE_DELEGATE_OneParam(FOnStatisticsUpdated, const FMessageTransportStatistics ) class FQuicEndpoint : public FRunnable , private FSingleThreadRunnable { protected: FQuicEndpoint() = delete; FQuicEndpoint(TSharedRef<FQuicEndpointConfig> InEndpointConfig, HQUIC InQuicConfig, const QUIC_API_TABLE* InMsQuic, HQUIC InRegistration, const TCHAR* InThreadName) : Endpoint(InEndpointConfig->Endpoint) , LocalNodeId(InEndpointConfig->LocalNodeId) , QuicConfig(InQuicConfig)`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FQuicPayloadPtr, FOnSerializeHeader, FMessageHeader& ) DECLARE_DELEGATE_RetVal_OneParam(FMessageHeader, FOnDeserializeHeader, FQuicPayloadPtr ) DECLARE_DELEGATE_TwoParams(FOnEndpointDisconnected, const FIPv4Endpoint , EQuicEndpointError ) DECLARE_DELEGATE_OneParam(FOnEndpointConnected, const FIPv4Endpoint& ) DECLARE_DELEGATE_OneParam(FOnStatisticsUpdated, const FMessageTransportStatistics ) class FQuicEndpoint : public FRunnable , private FSingleThreadRunnable { protected: FQuicEndpoint() = delete; FQuicEndpoint(TSharedRef<FQuicEndpointConfig> InEndpointConfig, HQUIC InQuicConfig, const QUIC_API_TABLE* InMsQuic, HQUIC InRegistration, const TCHAR* InThreadName) : Endpoint(InEndpointConfig->Endpoint) , LocalNodeId(InEndpointConfig->LocalNodeId) , QuicConfig(InQuicConfig) , MsQuic(InMsQuic) , Registration(InRegistration)`
- L33 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FMessageHeader, FOnDeserializeHeader, FQuicPayloadPtr ) DECLARE_DELEGATE_TwoParams(FOnEndpointDisconnected, const FIPv4Endpoint , EQuicEndpointError ) DECLARE_DELEGATE_OneParam(FOnEndpointConnected, const FIPv4Endpoint& ) DECLARE_DELEGATE_OneParam(FOnStatisticsUpdated, const FMessageTransportStatistics ) class FQuicEndpoint : public FRunnable , private FSingleThreadRunnable { protected: FQuicEndpoint() = delete; FQuicEndpoint(TSharedRef<FQuicEndpointConfig> InEndpointConfig, HQUIC InQuicConfig, const QUIC_API_TABLE* InMsQuic, HQUIC InRegistration, const TCHAR* InThreadName) : Endpoint(InEndpointConfig->Endpoint) , LocalNodeId(InEndpointConfig->LocalNodeId) , QuicConfig(InQuicConfig) , MsQuic(InMsQuic) , Registration(InRegistration) , bStopping(false) , Thread(nullptr)`
- L35 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnEndpointDisconnected, const FIPv4Endpoint , EQuicEndpointError ) DECLARE_DELEGATE_OneParam(FOnEndpointConnected, const FIPv4Endpoint& ) DECLARE_DELEGATE_OneParam(FOnStatisticsUpdated, const FMessageTransportStatistics ) class FQuicEndpoint : public FRunnable , private FSingleThreadRunnable { protected: FQuicEndpoint() = delete; FQuicEndpoint(TSharedRef<FQuicEndpointConfig> InEndpointConfig, HQUIC InQuicConfig, const QUIC_API_TABLE* InMsQuic, HQUIC InRegistration, const TCHAR* InThreadName) : Endpoint(InEndpointConfig->Endpoint) , LocalNodeId(InEndpointConfig->LocalNodeId) , QuicConfig(InQuicConfig) , MsQuic(InMsQuic) , Registration(InRegistration) , bStopping(false) , Thread(nullptr) , ThreadName(InThreadName) , InboundBuffers(TMap<FAddrStream, FInboundBuffer>())`
- L37 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEndpointConnected, const FIPv4Endpoint& ) DECLARE_DELEGATE_OneParam(FOnStatisticsUpdated, const FMessageTransportStatistics ) class FQuicEndpoint : public FRunnable , private FSingleThreadRunnable { protected: FQuicEndpoint() = delete; FQuicEndpoint(TSharedRef<FQuicEndpointConfig> InEndpointConfig, HQUIC InQuicConfig, const QUIC_API_TABLE* InMsQuic, HQUIC InRegistration, const TCHAR* InThreadName) : Endpoint(InEndpointConfig->Endpoint) , LocalNodeId(InEndpointConfig->LocalNodeId) , QuicConfig(InQuicConfig) , MsQuic(InMsQuic) , Registration(InRegistration) , bStopping(false) , Thread(nullptr) , ThreadName(InThreadName) , InboundBuffers(TMap<FAddrStream, FInboundBuffer>()) { }`
- L39 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStatisticsUpdated, const FMessageTransportStatistics ) class FQuicEndpoint : public FRunnable , private FSingleThreadRunnable { protected: FQuicEndpoint() = delete; FQuicEndpoint(TSharedRef<FQuicEndpointConfig> InEndpointConfig, HQUIC InQuicConfig, const QUIC_API_TABLE* InMsQuic, HQUIC InRegistration, const TCHAR* InThreadName) : Endpoint(InEndpointConfig->Endpoint) , LocalNodeId(InEndpointConfig->LocalNodeId) , QuicConfig(InQuicConfig) , MsQuic(InMsQuic) , Registration(InRegistration) , bStopping(false) , Thread(nullptr) , ThreadName(InThreadName) , InboundBuffers(TMap<FAddrStream, FInboundBuffer>()) { } /** * Destruct QUIC endpoint.`

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Private/QuicIncludes.h` (Private)


#### Free symbols / members of external scopes

- L27 _macro_ `#define QUIC_API_ENABLE_INSECURE_FEATURES` — This define is needed to provide optional local non-encrypted traffic
- L42 _macro_ `#define UNREFERENCED_PARAMETER(P) (void)(P)`
- L45 _macro_ `#define UI UI_ST`

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Private/QuicMessagingTransportPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogQuicMessagingTransport, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogQuicMessagingTransport, Log, All);`

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Private/QuicQueues.h` (Private)


#### class `FQuicQueues`  
`class FQuicQueues`  
_L12-71_
- L17 _protected prototype_ `FQuicQueues() = default;`
- L19 _protected prototype_ `virtual ~FQuicQueues() = default;`
- L27 _public prototype_ `void ConsumeMessages();` — Periodically called to consume local inbound and outbound messages. Consumes messages every ConsumeInterval microseconds.
- L35 _protected prototype_ `virtual void ConsumeInboundMessages() = 0;` — Dequeue inbound messages until MaxConsumeTime is reached. Inbound messages are passed to QuicEndpointManager for validation.
- L41 _protected prototype_ `virtual void ProcessInboundBuffers() = 0;` — Dequeue inbound buffers until MaxConsumeTime is reached. Inbound buffers via QUIC are copied into our buffers until the stream end is indicated.
- L47 _protected prototype_ `virtual void ConsumeOutboundMessages() = 0;` — Dequeue outbound messages until MaxConsumeTime is reached. Outbound messages will then be sent via QUIC.
- L52 _protected member_ `TQueue<FInboundMessage> InboundMessages;` — Queue for inbound messages ready to be consumed.
- L55 _protected member_ `TQueue<FOutboundMessage> OutboundMessages;` — Queue for outbound message ready to be sent.
- L60 _protected member_ `const FTimespan MaxConsumeTime = 5000;` — Holds current message consume time in microseconds.
- L63 _protected member_ `const FTimespan ConsumeInterval = 10000;` — Holds the interval for message consume.
- L66 _protected member_ `double LastConsumed = FPlatformTime::Seconds();` — Holds timestamp of when messages have last been consumed.
- L69 _protected member_ `uint32 InboundMessagesId = 0;` — Current id for InboundMessages.

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Private/QuicServer.h` (Private)


#### class `FQuicServer`  
`class FQuicServer : public FQuicEndpoint , public FQuicQueues`  
_L34-388_
- inherits: `FQuicEndpoint,FQuicQueues`
- desc: Implements the QuicServer.
- L41 _public prototype_ `FQuicServer() = delete;`
- L46 _public function_ `FQuicServer(TSharedRef<FQuicServerConfig> InServerConfig, HQUIC InQuicConfig, const QUIC_API_TABLE* InMsQuic, HQUIC InRegistration, const TCHAR* InThreadName, const QUIC_BUFFER InAlpn) : FQuicEndpoint(InServerConfig, InQuicConfig, InMsQuic, InRegistration, InThreadName) , ServerListener(nullptr) , ServerConnection(nullptr) , Alpn(InAlpn) , AuthenticationMode(InServerConfig->AuthenticationMode) , ServerConfig(InServerConfig) , Handlers(TMap<FIPv4Endpoint, FQuicServerHandlerPtr>()) , ConnectionCooldown(TMap<FIPv4Endpoint, uint64>()) , ConnectionAttempts(TMap<FIPv4Endpoint, FConnectionAttempts>())` — Creates a new QUIC server.
- L66 _protected prototype_ `virtual void StartEndpoint() override;` — Starts the configured QUIC server.
- L73 _public prototype_ `virtual void StopEndpoint() override;` — Stops the QUIC server.
- L78 _public prototype_ `virtual bool IsEndpointReady() override;` — Indicates if the server is ready to send/receive messages.
- L85 _public prototype_ `virtual void UpdateEndpoint() override;` — Periodically called to update the endpoint (consume messages).
- L93 _protected prototype_ `virtual void ConsumeInboundMessages() override;` — Dequeue inbound messages until MaxConsumeTime is reached. Inbound messages are passed to QuicEndpointManager for validation.
- L99 _protected prototype_ `virtual void ProcessInboundBuffers() override;` — Dequeue inbound buffers until MaxConsumeTime is reached. Inbound buffers via QUIC are copied into our buffers until the stream end is indicated.
- L105 _protected prototype_ `virtual void ConsumeOutboundMessages() override;` — Dequeue outbound messages until MaxConsumeTime is reached. Outbound messages will then be sent via QUIC.
- L114 _protected prototype_ `bool CanHandlerConnect(const FIPv4Endpoint& ConnectingEndpoint) const;` — Determines if a handler can connect by checking the connection cooldown list. @param ConnectingEndpoint The connecting endpoint's address
- L121 _protected prototype_ `void AddConnectionAttempt(const FIPv4Endpoint& ConnectingEndpoint);` — Adds a new connection attempt and triggers connection cooldown if enabled. @param ConnectingEndpoint The connecting endpoint's address
- L126 _protected prototype_ `void CheckConnectionCooldown();` — Regularly checks and cleans up connection cooldown entries.
- L131 _protected prototype_ `virtual void CollectStatistics() override;` — Collects, converts and passes QUIC connection stats to the EndpointManager.
- L141 _public prototype_ `virtual void SetHandlerAuthenticated(const FIPv4Endpoint& HandlerEndpoint) override;` — Marks a handler as authenticated. @param HandlerEndpoint The handler endpoint @see QuicEndpointManager / Authentication
- L148 _public prototype_ `virtual void DisconnectHandler(const FIPv4Endpoint& HandlerEndpoint) override;` — Disconnects a handler. @param HandlerEndpoint The handler endpoint
- L155 _protected prototype_ `void ShutdownAllHandlers() const;` — Shutdown every handler's connection.
- L162 _protected prototype_ `void ShutdownHandler(const HQUIC HandlerConnection) const;` — Shutdown a handler's connection. @param HandlerConnection The handler connection
- L171 _public prototype_ `virtual void EnqueueOutboundMessage(const FOutboundMessage& OutboundMessage) override;` — Enqueues an outbound message on the server. @param OutboundMessage The outbound message
- L178 _public prototype_ `virtual void SendHello(FIPv4Endpoint RemoteEndpoint) override;` — Sends a hello message to the remote endpoint. @param RemoteEndpoint The remote endpoint
- L183 _public prototype_ `virtual void SendBye() override;` — Sends a bye message to all handlers.
- L190 _public prototype_ `void SendBye(const FIPv4Endpoint& HandlerEndpoint);` — Sends a bye message to the specified handler. @param HandlerEndpoint The handler endpoint
- L201 _protected prototype_ `_Function_class_(QUIC_LISTENER_CALLBACK) static QUIC_STATUS ServerListenerCallback(HQUIC Listener, void* Context, QUIC_LISTENER_EVENT* Event);` — Callback for server listeners. @param Listener The QUIC listener handle @param Context The app context (FQuicServer) @param Event The listener event
- L212 _protected prototype_ `_Function_class_(QUIC_CONNECTION_CALLBACK) static QUIC_STATUS ServerConnectionCallback(HQUIC Connection, void* Context, QUIC_CONNECTION_EVENT* Event);` — Callback for server connections. @param Connection The QUIC connection handle @param Context The app context (FQuicServer) @param Event The connection event
- L223 _protected prototype_ `_Function_class_(QUIC_STREAM_CALLBACK) static QUIC_STATUS ServerStreamCallback(HQUIC Stream, void* Context, QUIC_STREAM_EVENT* Event);` — Callback for server streams. @param Stream The QUIC stream handle @param Context The app context (FQuicServer) @param Event The stream event
- L234 _protected prototype_ `QUIC_STATUS OnListenerNewConnection(QUIC_LISTENER_EVENT* Event);` — Handles a connection attempt by a client. @param Event The listener event
- L241 _protected prototype_ `void OnConnectionConnected(HQUIC Connection);` — Handles a connection after the handshake was completed. @param Connection The connection handle
- L249 _protected prototype_ `void OnConnectionShutdownByTransport(HQUIC Connection, QuicUtils::HRESULT Status);` — Handles a connection after it was killed due to idle timeout. @param Connection The connection handle @param Status The shutdown event status
- L257 _protected prototype_ `void OnConnectionShutdownByPeer(HQUIC Connection, QUIC_UINT62 ErrorCode);` — Handles a connection after it was killed by the peer. @param Connection The connection handle @param ErrorCode The QUIC error code
- L265 _protected prototype_ `void OnConnectionShutdownComplete(HQUIC Connection, BOOLEAN AppCloseInProgress);` — Handles a connection after its shutdown was completed, ready for cleanup. @param Connection The connection handle @param AppCloseInProgress Boolean indicating whether app close is already in progress
- L273 _protected prototype_ `void OnConnectionPeerStreamStarted(HQUIC Connection, HQUIC Stream);` — Handles when a peer started a stream. @param Connection The connection handle @param Stream The stream handle
- L278 _protected prototype_ `void OnConnectionResumed();` — Handles a succeeded TLS resumption of a previous session.
- L285 _protected prototype_ `void OnStreamShutdownComplete(HQUIC Stream) const;` — Closes a stream when both directions have been shut down. @param Stream The stream handle
- L295 _protected prototype_ `void SendToStream( const HQUIC Connection, const FOutboundMessage OutboundMessage);` — Sends the outbound buffers to the remote endpoint. @param Connection The QUIC connection handle @param OutboundMessage The outbound message
- L307 _protected prototype_ `bool ReceiveFromStream(const FInboundQuicBuffer& QuicBuffer);` — Copy data from a stream buffer. @param QuicBuffer The inbound QUIC buffer @return Whether the operation succeeded
- L314 _protected prototype_ `void ReachedEndOfStream(const FInboundQuicBuffer& QuicBuffer);` — Prepares inbound data for processing. @param QuicBuffer The inbound QUIC buffer
- L323 _protected prototype_ `QUIC_ADDR GetRemoteAddress(HQUIC Connection) const;` — Get the remote address from a connection. @param Connection The QUIC connection handle
- L330 _protected prototype_ `static FIPv4Endpoint ClearEndpointPort(const FIPv4Endpoint& Endpoint);` — Sets the endpoints port to zero. @param Endpoint The endpoint address
- L335 _protected member_ `HQUIC ServerListener;` — Holds the QUIC API server listener handle.
- L338 _protected member_ `HQUIC ServerConnection;` — Holds the QUIC API server connection handle.
- L341 _protected member_ `EQuicServerState ConnectionState = EQuicServerState::Starting;` — Current server state.
- L344 _protected member_ `QUIC_BUFFER Alpn;` — Holds the protocol name for ALPN.
- L347 _protected member_ `EAuthenticationMode AuthenticationMode;` — Holds the server authentication mode.
- L350 _protected member_ `TSharedRef<FQuicServerConfig> ServerConfig;` — Holds the server config.
- L355 _protected member_ `TMap<FIPv4Endpoint, FQuicServerHandlerPtr> Handlers;` — Holds the QuicServerHandlers.
- L358 _protected member_ `mutable FCriticalSection HandlersCS;` — Holds the handlers critical section.
- L361 _protected member_ `FTSTicker::FDelegateHandle ConnectionCooldownCheckHandle;` — Holds the handle for the connection cooldown check.
- L364 _protected member_ `mutable FCriticalSection ConnectionCooldownCS;` — Holds the connection cooldown critical section.
- L367 _protected member_ `TMap<FIPv4Endpoint, uint64> ConnectionCooldown;` — Holds a map of IPv4 addresses and connection cooldown timestamps.
- L386 _protected member_ `TMap<FIPv4Endpoint, FConnectionAttempts> ConnectionAttempts;` — Holds a map of connection attempts.

#### struct `FQuicServer::FConnectionAttempts`  
`struct FConnectionAttempts`  
_L370-383_
- desc: Struct for data concerning connection attempts.
- L373 _public member_ `uint32 NumCooldowns;` — Holds the number of previous cooldowns.
- L376 _public member_ `TArray<uint64> AttemptTimestamps;` — Holds the attempt timestamps.
- L379 _public function_ `FConnectionAttempts() : NumCooldowns(0) , AttemptTimestamps(TArray<uint64>())` — Default constructor.

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef TSharedPtr<FQuicServerHandler, ESPMode::ThreadSafe> FQuicServerHandlerPtr;`

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Private/QuicServerHandler.h` (Private)


#### struct `FQuicServerHandler`  
`struct FQuicServerHandler`  
_L15-107_
- L19 _public member_ `bool bSentHello;` — Holds a flag indicating whether a hello message was sent.
- L22 _public member_ `bool bAuthenticated;` — Holds a flag indicating whether the handler is authenticated.
- L25 _public member_ `EQuicHandlerState ConnectionState;` — Holds the current handler state.
- L28 _public member_ `FIPv4Endpoint Endpoint;` — Holds the handler endpoint.
- L31 _public member_ `QUIC_ADDR Address;` — Holds the handler address.
- L34 _public member_ `HQUIC Connection;` — Holds the handler connection.
- L37 _public member_ `EQuicEndpointError Error;` — Holds the handler error.
- L40 _public member_ `TArray<uint32> RttMeasurements;` — Holds the latest RTT measurements.
- L43 _public member_ `double RttStart;` — Holds the time when the RTT measurement sequence started.
- L46 _public function_ `FQuicServerHandler() : bSentHello(false) , bAuthenticated(false) , ConnectionState(EQuicHandlerState::Starting) , Endpoint(FIPv4Endpoint::Any) , Address({}) , Connection(nullptr) , Error(EQuicEndpointError::Normal) , RttMeasurements(TArray<uint32>()) , RttStart(FPlatformTime::Seconds())` — Default constructor.
- L59 _public function_ `FQuicServerHandler(const FIPv4Endpoint& InEndpoint, QUIC_ADDR InAddress, const HQUIC InConnection) : bSentHello(false) , bAuthenticated(false) , ConnectionState(EQuicHandlerState::Starting) , Endpoint(InEndpoint) , Address(InAddress) , Connection(InConnection) , Error(EQuicEndpointError::Normal) , RttMeasurements(TArray<uint32>()) , RttStart(FPlatformTime::Seconds())` — Creates and initializes a new instance.
- L72 _public function_ `bool IsStarting() const`
- L77 _public function_ `bool IsRunning() const`
- L82 _public function_ `bool IsStopping() const`
- L87 _public function_ `bool NeedRttReset() const`
- L95 _public function_ `double GetAverageRtt() const` — Gets the average RTT measurement.

#### Free symbols / members of external scopes

- L12 _macro_ `#define QUIC_STATS_RTTAVG_RESET_AFTER 300000000`

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Private/QuicUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace QuicUtils`
- L12 _typedef_ `typedef long HRESULT;` (scope `QuicUtils`)
- L22 _prototype_ `FString ConvertResult(HRESULT Result);` (scope `QuicUtils`) — Convert HRESULT to FString. @note Most HRESULT values are overriden/extended by msquic https://github.com/microsoft/msquic/blob/main/docs/TSG.md#understanding-error-codes https://github.com/microsoft/msquic/blob/main/src/inc/msquic_winuser.h
- L27 _prototype_ `EQuicEndpointError ConvertQuicStatus(HRESULT Status);` (scope `QuicUtils`) — Convert HRESULT msquic status.
- L29 _prototype_ `FString GetEndpointErrorString(EQuicEndpointError Error);` (scope `QuicUtils`)

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Public/IQuicMessagingTransportModule.h` (Public)


#### class `IQuicMessagingTransportModule`  
`class IQuicMessagingTransportModule : public IModuleInterface`  
_L12-21_
- inherits: `IModuleInterface`
- desc: Interface for QuicMessagingTransport module
- L16 _public function_ `static IQuicMessagingTransportModule& Get()` — Get the QuicMessagingTransport module

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Public/QuicEndpointConfig.h` (Public)


#### struct `FQuicEndpointConfig`  
`struct FQuicEndpointConfig`  
_L18-33_
- L22 _public member_ `FIPv4Endpoint Endpoint = FIPv4Endpoint::Any;` — Holds the local/remote endpoint.
- L25 _public member_ `FGuid LocalNodeId = FGuid::NewGuid();` — Holds the local node id.
- L28 _public member_ `EEncryptionMode EncryptionMode = EEncryptionMode::Enabled;` — Holds flag indicating whether encryption is enabled.
- L31 _public member_ `uint32 DiscoveryTimeoutSec = 0;` — Holds the discovery timeout in seconds.

#### struct `FQuicServerConfig`  
`struct FQuicServerConfig : FQuicEndpointConfig`  
_L36-67_
- inherits: `FQuicEndpointConfig`
- L41 _public member_ `FString Certificate = "";` — Holds the certificate for Quic communication.
- L44 _public member_ `FString PrivateKey = "";` — Holds the private key.
- L47 _public member_ `uint32 MaxAuthenticationMessageSize = 0;` — Holds the maximum authentication message size.
- L50 _public member_ `EAuthenticationMode AuthenticationMode = EAuthenticationMode::Disabled;` — Holds flag indicating whether the server should authenticate clients.
- L53 _public member_ `EConnectionCooldownMode ConnCooldownMode = EConnectionCooldownMode::Enabled;` — Holds flag indicating whether there is a cooldown for connection attempts.
- L56 _public member_ `uint32 ConnCooldownMaxAttempts = 5;` — Holds the maximum attempts until the connection cooldown is triggered.
- L59 _public member_ `uint32 ConnCooldownPeriodSec = 30;` — Holds the time period in seconds within the max attempts must happen.
- L62 _public member_ `uint32 ConnCooldownSec = 30;` — Holds the connection cooldown in seconds.
- L65 _public member_ `uint32 ConnCooldownMaxSec = 3600;` — Holds the maximum connection cooldown in seconds.

#### struct `FQuicClientConfig`  
`struct FQuicClientConfig : FQuicEndpointConfig`  
_L70-77_
- inherits: `FQuicEndpointConfig`
- L75 _public member_ `EQuicClientVerificationMode ClientVerificationMode = EQuicClientVerificationMode::Verify;` — Holds flag indicating whether the client should verify the server certificate.

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Public/QuicEndpointManager.h` (Public)


#### class `FQuicEndpointManager`  
`class FQuicEndpointManager`  
_L50-482_
- desc: QUIC endpoint manager Authentication: - If AuthenticationMode is Enabled, QuicServerHandler will discard any message with MessageType other than "Authentication" until the node associated with the handler is marked as authenticated - Messages with type "Authentication" or "AuthenticationResponse" can be sent via the extension methods found in IQuicNetworkMessagingExtension.h - The MaxAuthenticationMessageSize limit can be set to avoid reading potentially large malicious authentication messages Client/Server: - The EndpointManager will start in client mode by default and is converted to a server endpoint when SetServerMode is called with additional parameters needed to run a server - QuicServerHandlers will continuously ping the connected client to keep the connection alive
- L55 _public prototype_ `FQuicEndpointManager() = delete;`
- L62 _public prototype_ `FQuicEndpointManager( TSharedRef<FQuicEndpointConfig> InEndpointConfig);` — Initialize endpoint manager with default mode as client. @param InEndpointConfig The endpoint config
- L68 _public prototype_ `~FQuicEndpointManager();` — Default destructor.
- L75 _public prototype_ `void Shutdown();` — Shutdown endpoint manager and kill client/server threads.
- L82 _private prototype_ `HQUIC LoadClientConfiguration() const;` — Load the client configuration.
- L90 _private prototype_ `HQUIC LoadServerConfiguration( FString CertificatePath, FString PrivateKeyPath) const;` — Load the server configuration. @param CertificatePath Path to the certificate @param PrivateKeyPath Path to the private key
- L100 _public prototype_ `void InitializeServer();` — Set endpoint manager to operate in server mode and initialize server. @see Authentication
- L109 _public prototype_ `void AddClient(const FIPv4Endpoint& ClientEndpoint);` — Add remote endpoint client. @param ClientEndpoint The client endpoint that will be connected to
- L116 _public prototype_ `void RemoveClient(const FIPv4Endpoint& ClientEndpoint);` — Remove remote endpoint client. @param ClientEndpoint The client endpoint that will be removed
- L123 _public prototype_ `void ReconnectClient(const FIPv4Endpoint ClientEndpoint);` — Reconnect remote endpoint client. @param ClientEndpoint The client endpoint that will be reconnected
- L135 _public prototype_ `bool IsEndpointAuthenticated(const FGuid& NodeId) const;` — Check if a QuicServerHandler endpoint is authenticated. @param NodeId The endpoint associated with this node @return True if the endpoint is authenticated @note This is only used for QuicServers @see Authentication
- L144 _public prototype_ `void SetEndpointAuthenticated(const FGuid& NodeId);` — Set QuicServerHandler endpoint as authenticated. @param NodeId The endpoint associated with this node @note This is only used for QuicServers @see Authentication
- L151 _public prototype_ `void DisconnectNode(const FGuid& NodeId);` — Disconnect a node. @param NodeId The node identifier
- L158 _public prototype_ `void DisconnectEndpoint(const FIPv4Endpoint& Endpoint);` — Disconnect an endpoint. @param Endpoint The endpoint address
- L170 _public prototype_ `void EnqueueOutboundMessages(FQuicPayloadPtr Data, const TArray<TTuple<FGuid, uint32>>& MessageMetas, const EQuicMessageType MessageType);` — Enqueues outbound messages on all recipient endpoints. @param Data The message data @param MessageMetas The message recipient node identifiers and associated message ID @param MessageType The message type @see Authentication and EQuicMessageType
- L178 _public function_ `DECLARE_DELEGATE_OneParam(FOnMessageDelivered, const uint32 ) FOnMessageDelivered& OnMessageDelivered()` — Delegate for when a message has been delivered. @return The delegate
- L191 _protected prototype_ `void ValidateInboundMessage(const FInboundMessage InboundMessage);` — Validates InboundMessage and passes it to MessageProcessor. @param InboundMessage The inbound message
- L198 _protected prototype_ `bool IsMessageValid(const FInboundMessage InboundMessage);` — Checks if a message is valid. @param InboundMessage The inbound message
- L205 _protected prototype_ `void SendEndpointHello(const FInboundMessage& InboundMessage);` — Instructs the appropriate endpoint or handler to send a hello message. @param InboundMessage The inbound message
- L214 _public function_ `DECLARE_DELEGATE_OneParam(FOnMessageValidated, const FInboundMessage ) FOnMessageValidated& OnMessageValidated()` — Delegate for when a message has been received and validated. @return The delegate
- L227 _protected prototype_ `FQuicPayloadPtr SerializeHeader( FMessageHeader& MessageHeader) const;` — Forward for the serialize header delegate. @param MessageHeader The message header
- L235 _protected prototype_ `FMessageHeader DeserializeHeader( const FQuicPayloadPtr HeaderData) const;` — Forward for the deserialize header delegate. @param HeaderData The header data
- L245 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(FQuicPayloadPtr, FOnSerializeHeader, FMessageHeader& ) FOnSerializeHeader& OnSerializeHeader()` — Delegate for when a header needs to be serialized. @return The delegate
- L256 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(FMessageHeader, FOnDeserializeHeader, FQuicPayloadPtr ) FOnDeserializeHeader& OnDeserializeHeader()` — Delegate for when a header needs to be deserialized. @return The delegate
- L271 _public prototype_ `void EndpointNodeDiscovered(const FGuid NodeId, const FIPv4Endpoint& NodeEndpoint, const FIPv4Endpoint& LocalEndpoint);` — Register discovered endpoint node. @param NodeId The node ID @param NodeEndpoint The node endpoint address @param LocalEndpoint The local endpoint
- L280 _public prototype_ `void EndpointNodeLost(const FGuid NodeId, const FIPv4Endpoint LostEndpoint);` — De-register lost endpoint node. @param NodeId The node ID @param LostEndpoint The lost endpoint address
- L287 _public function_ `DECLARE_DELEGATE_OneParam(FOnEndpointNodeDiscovered, const FGuid& ) FOnEndpointNodeDiscovered& OnEndpointNodeDiscovered()` — Delegate for when a node was discovered. @return The delegate
- L298 _public function_ `DECLARE_DELEGATE_OneParam(FOnEndpointNodeLost, const FGuid& ) FOnEndpointNodeLost& OnEndpointNodeLost()` — Delegate for when a node was lost. @return The delegate
- L309 _public function_ `DECLARE_DELEGATE_ThreeParams(FOnClientConnectionChanged, const FGuid& , const FIPv4Endpoint& , const EQuicClientConnectionChange ) FOnClientConnectionChanged& OnClientConnectionChanged()` — Delegate for when a client connection changes. @return The delegate
- L324 _public prototype_ `TOptional<FGuid> GetKnownNodeId(const FIPv4Endpoint& Endpoint) const;` — Get the NodeId of a known endpoint. @param Endpoint The endpoint @return Optional FGuid if the node was found
- L329 _public prototype_ `TArray<FGuid> GetKnownNodeIds() const;` — Get a list of known NodeIds.
- L336 _public prototype_ `bool IsEndpointKnown(const FIPv4Endpoint Endpoint) const;` — Check if an endpoint is associated with a known node. @param Endpoint The endpoint
- L341 _public prototype_ `TArray<FIPv4Endpoint> GetKnownEndpoints() const;` — Get a list of the known endpoints.
- L348 _public prototype_ `FMessageTransportStatistics GetStats(FGuid NodeId) const;` — Get the network/transport statistics for a node. @param NodeId The node ID
- L358 _protected prototype_ `void EndpointDisconnected( const FIPv4Endpoint DisconnectedEndpoint, EQuicEndpointError Reason);` — Removes a disconnected endpoint. @param DisconnectedEndpoint The disconnected endpoint @param Reason The disconnect reason
- L366 _protected prototype_ `void CheckLoseNode(const FIPv4Endpoint LostEndpoint);` — Checks if the lost endpoint node is still registered and removes it. @param LostEndpoint The lost endpoint
- L373 _protected prototype_ `void EndpointConnected(const FIPv4Endpoint& ConnectedEndpoint);` — Adds a DiscoveryTimeout entry if discovery timeouts are enabled. @param ConnectedEndpoint The connected endpoint
- L380 _protected prototype_ `void CheckDiscoveryTimeout();` — Regularly called to check if any of the endpoints have reached the discovery timeout. Timed out endpoints will be disconnected.
- L387 _protected prototype_ `void EndpointStatisticsUpdated( const FMessageTransportStatistics TransportStats);` — Updates a KnownNode with new endpoint transport statistics. @param TransportStats The endpoint transport statistics
- L393 _private member_ `const QUIC_API_TABLE* MsQuic;` — Holds the QUIC API table handle.
- L396 _private member_ `HQUIC Registration;` — Holds the QUIC API registration handle.
- L399 _private member_ `HQUIC CurrentConfiguration;` — Holds the current QUIC API configuration handle.
- L404 _private member_ `FGuid LocalNodeId;` — Holds the local node identifier.
- L407 _private member_ `FIPv4Endpoint ServerEndpoint;` — Holds the local server endpoint that the socket will be bound to.
- L410 _private member_ `EEndpointMode EndpointMode;` — Flag indicating the endpoint mode.
- L413 _private member_ `TSharedRef<FQuicEndpointConfig> EndpointConfig;` — Holds the endpoint config.
- L416 _private member_ `TMap<FIPv4Endpoint, uint32> ReconnectAttempts;` — Holds the collection of reconnect attempts.
- L419 _private member_ `TMap<FIPv4Endpoint, FQuicEndpointPtr> Endpoints;` — Holds the collection of active QUIC endpoints.
- L422 _private member_ `mutable FCriticalSection EndpointsCS;` — Mutex protecting access to the endpoints map.
- L425 _private member_ `TMap<FGuid, FQuicNodeInfo> KnownNodes;` — Holds the collection of known remote nodes.
- L428 _private member_ `mutable FCriticalSection NodesCS;` — Mutex protecting access to the nodes map.
- L433 _private member_ `FTSTicker::FDelegateHandle DiscoveryTimeoutTickHandle;` — Holds the handle for the discovery timeout tick.
- L447 _private member_ `TArray<FDiscoveryTimeoutEntry> DiscoveryTimeouts;` — Holds the connection timestamps for discovery timeout purposes.
- L450 _private member_ `mutable FCriticalSection DiscoveryTimeoutCS;` — Mutex protecting the discovery timeouts array.
- L455 _private member_ `FOnMessageDelivered MessageDeliveredDelegate;` — Holds a delegate to be invoked when a message was delivered to all endpoints.
- L461 _private member_ `FOnMessageValidated MessageValidatedDelegate;` — Holds a delegate to be invoked when a message has been received and validated, ready to be serialized by the local endpoint.
- L466 _private member_ `FOnSerializeHeader SerializeHeaderDelegate;` — Holds the serialize header delegate.
- L469 _private member_ `FOnDeserializeHeader DeserializeHeaderDelegate;` — Holds the deserialize header delegate.
- L474 _private member_ `FOnEndpointNodeDiscovered EndpointNodeDiscoveredDelegate;` — Holds a delegate to be invoked when a node was discovered.
- L477 _private member_ `FOnEndpointNodeLost EndpointNodeLostDelegate;` — Holds a delegate to be invoked when a node was lost.
- L480 _private member_ `FOnClientConnectionChanged ClientConnectionChangedDelegate;` — Holds a delegate to be invoked when a client connection has changed.

#### struct `FQuicEndpointManager::FDiscoveryTimeoutEntry`  
`struct FDiscoveryTimeoutEntry`  
_L435-444_
- L439 _public member_ `FIPv4Endpoint Endpoint = FIPv4Endpoint::Any;` — Holds the address of the connected endpoint.
- L442 _public member_ `double Timestamp = 0;` — Holds the connection timestamp.

#### Free symbols / members of external scopes

- L24 _typedef_ `typedef QUIC_HANDLE* HQUIC;`
- L27 _typedef_ `using FQuicEndpointPtr = TSharedPtr<FQuicEndpoint, ESPMode::ThreadSafe>;`
- L178 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMessageDelivered, const uint32 ) FOnMessageDelivered& OnMessageDelivered() { return MessageDeliveredDelegate; } protected: void ValidateInboundMessage(const FInboundMessage InboundMessage);` — Delegate for when a message has been delivered. @return The delegate
- L214 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMessageValidated, const FInboundMessage ) FOnMessageValidated& OnMessageValidated() { return MessageValidatedDelegate; } protected: FQuicPayloadPtr SerializeHeader( FMessageHeader& MessageHeader) const;` — Delegate for when a message has been received and validated. @return The delegate
- L245 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FQuicPayloadPtr, FOnSerializeHeader, FMessageHeader& ) FOnSerializeHeader& OnSerializeHeader() { return SerializeHeaderDelegate; } DECLARE_DELEGATE_RetVal_OneParam(FMessageHeader, FOnDeserializeHeader, FQuicPayloadPtr ) FOnDeserializeHeader& OnDeserializeHeader() { return DeserializeHeaderDelegate; } public: void EndpointNodeDiscovered(const FGuid NodeId, const FIPv4Endpoint& NodeEndpoint, const FIPv4Endpoint& LocalEndpoint);` — Delegate for when a header needs to be serialized. @return The delegate
- L256 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FMessageHeader, FOnDeserializeHeader, FQuicPayloadPtr ) FOnDeserializeHeader& OnDeserializeHeader() { return DeserializeHeaderDelegate; } public: void EndpointNodeDiscovered(const FGuid NodeId, const FIPv4Endpoint& NodeEndpoint, const FIPv4Endpoint& LocalEndpoint);` — Delegate for when a header needs to be deserialized. @return The delegate
- L287 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEndpointNodeDiscovered, const FGuid& ) FOnEndpointNodeDiscovered& OnEndpointNodeDiscovered() { return EndpointNodeDiscoveredDelegate; } DECLARE_DELEGATE_OneParam(FOnEndpointNodeLost, const FGuid& ) FOnEndpointNodeLost& OnEndpointNodeLost() { return EndpointNodeLostDelegate; } DECLARE_DELEGATE_ThreeParams(FOnClientConnectionChanged, const FGuid& , const FIPv4Endpoint& , const EQuicClientConnectionChange ) FOnClientConnectionChanged& OnClientConnectionChanged() { return ClientConnectionChangedDelegate; } TOptional<FGuid> GetKnownNodeId(const FIPv4Endpoint& Endpoint) const;` — Delegate for when a node was discovered. @return The delegate
- L298 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEndpointNodeLost, const FGuid& ) FOnEndpointNodeLost& OnEndpointNodeLost() { return EndpointNodeLostDelegate; } DECLARE_DELEGATE_ThreeParams(FOnClientConnectionChanged, const FGuid& , const FIPv4Endpoint& , const EQuicClientConnectionChange ) FOnClientConnectionChanged& OnClientConnectionChanged() { return ClientConnectionChangedDelegate; } TOptional<FGuid> GetKnownNodeId(const FIPv4Endpoint& Endpoint) const;` — Delegate for when a node was lost. @return The delegate
- L309 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnClientConnectionChanged, const FGuid& , const FIPv4Endpoint& , const EQuicClientConnectionChange ) FOnClientConnectionChanged& OnClientConnectionChanged() { return ClientConnectionChangedDelegate; } TOptional<FGuid> GetKnownNodeId(const FIPv4Endpoint& Endpoint) const;` — Delegate for when a client connection changes. @return The delegate

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Public/QuicFlags.h` (Public)


#### enum `EEndpointMode`  
`enum class EEndpointMode : uint8`  
_L12-19_
- desc: Enumerates endpoint mode.
- L15 _public enumerator_ `Client` — EndpointManager acts as a client.
- L18 _public enumerator_ `Server` — EndpointManager acts as a server.

#### enum `EAuthenticationMode`  
`enum class EAuthenticationMode : uint8`  
_L25-32_
- desc: Enumerates authentication mode.
- L28 _public enumerator_ `Enabled` — Client nodes have to be authenticated before sending MessageType.
- L31 _public enumerator_ `Disabled` — Authentication is disabled, all nodes can connect and send data.

#### enum `EEncryptionMode`  
`enum class EEncryptionMode : uint8`  
_L43-50_
- desc: Enumerates encryption mode. When disabled, encryption will only be used for the handshake. Further communication will be unencrypted. @note Both endpoints must have the same setting to successfully connect.
- L46 _public enumerator_ `Enabled` — Encryption is enabled.
- L49 _public enumerator_ `Disabled` — Encryption is disabled.

#### enum `EConnectionCooldownMode`  
`enum class EConnectionCooldownMode : uint8`  
_L61-68_
- desc: Enumerates connection cooldown mode. When enabled, multiple successive attempts to connect from the same IP address will trigger a cooldown. @note This is a server-only flag
- L64 _public enumerator_ `Enabled` — Connection cooldown is enabled.
- L67 _public enumerator_ `Disabled` — Connection cooldown is disabled.

#### enum `EQuicClientState`  
`enum class EQuicClientState : uint8`  
_L74-93_
- desc: Enumerates client connection state.
- L77 _public enumerator_ `Connecting` — Client is setting up connection.
- L80 _public enumerator_ `Connected` — Client is connected and running.
- L83 _public enumerator_ `Failed` — Client could not connect.
- L86 _public enumerator_ `Disconnected` — Client is disconnected.
- L89 _public enumerator_ `Closed` — Client connection is closed.
- L92 _public enumerator_ `Stopped` — Client is being destroyed.

#### enum `EQuicClientConnectionChange`  
`enum class EQuicClientConnectionChange : uint8`  
_L99-106_
- desc: Enumerates client connection changes.
- L102 _public enumerator_ `Connected` — Client has connected.
- L105 _public enumerator_ `Disconnected` — Client has disconnected.

#### enum `EQuicClientVerificationMode`  
`enum class EQuicClientVerificationMode : uint8`  
_L112-119_
- desc: Enumerates client certificate verification.
- L115 _public enumerator_ `Verify` — Verify server certificate.
- L118 _public enumerator_ `Pass` — Pass server certificate verification.

#### enum `EQuicClientSelfSignedCertificate`  
`enum class EQuicClientSelfSignedCertificate : uint8`  
_L125-132_
- desc: Enumerates client self signed certificates mode.
- L128 _public enumerator_ `Reject` — Reject self-signed certificates.
- L131 _public enumerator_ `Allow` — Allow self-signed certificates.

#### enum `EQuicServerState`  
`enum class EQuicServerState : uint8`  
_L138-151_
- desc: Enumerates server state.
- L141 _public enumerator_ `Starting` — Server is starting.
- L144 _public enumerator_ `Running` — Server is running.
- L147 _public enumerator_ `Failed` — Server encountered error and can't recover.
- L150 _public enumerator_ `Stopped` — Server is stopped.

#### enum `EQuicHandlerState`  
`enum class EQuicHandlerState : uint8`  
_L157-173_
- desc: Enumerates server handler state.
- L160 _public enumerator_ `Starting` — Handler is starting.
- L163 _public enumerator_ `Running` — Handler is running.
- L166 _public enumerator_ `Stopping` — Handler is stopping.
- L169 _public enumerator_ `Failed` — Handler connection failed.
- L172 _public enumerator_ `Disconnected` — Handler has disconnected.

#### enum `EQuicMessageType`  
`enum class EQuicMessageType : uint8`  
_L181-198_
- desc: Enumerates message type. @see QuicEndpointManager - Authentication
- L184 _public enumerator_ `Hello` — Hello, header-only.
- L187 _public enumerator_ `Authentication` — Authentication (from client to server)
- L190 _public enumerator_ `AuthenticationResponse` — Authentication response (from server to client)
- L193 _public enumerator_ `Data` — Data
- L196 _public enumerator_ `Bye` — Bye, header-only.

#### enum `EQuicEndpointError`  
`enum class EQuicEndpointError : uint16`  
_L204-272_
- desc: Enumerates endpoint error.
- L207 _public enumerator_ `Normal` — No endpoint error.
- L210 _public enumerator_ `OutOfMemory` — QUIC ran out of memory.
- L213 _public enumerator_ `InvalidParameter` — Invalid parameter supplied.
- L216 _public enumerator_ `InvalidState` — Invalid state encountered.
- L219 _public enumerator_ `NotSupported` — Operation not supported.
- L222 _public enumerator_ `NotFound` — Object was not found.
- L225 _public enumerator_ `BufferTooSmall` — Buffer is too small.
- L228 _public enumerator_ `ConnectionHandshake` — Connection handshake failed.
- L231 _public enumerator_ `ConnectionAbort` — Connection was aborted by transport.
- L234 _public enumerator_ `AddressInUse` — Client address/port already in use.
- L237 _public enumerator_ `InvalidAddress` — Remote address/port invalid.
- L240 _public enumerator_ `ConnectionTimeout` — Connection timed out while waiting for a response from peer.
- L243 _public enumerator_ `ConnectionIdle` — Connection timed out from inactivity.
- L246 _public enumerator_ `InternalError` — Internal error.
- L249 _public enumerator_ `ServerUnreachable` — Server is unreachable.
- L252 _public enumerator_ `ConnectionRefused` — Connection was refused.
- L255 _public enumerator_ `Protocol` — Encountered protocol error.
- L258 _public enumerator_ `VersionNegotiation` — Encountered error during version negotiation.
- L261 _public enumerator_ `UserCanceled` — User canceled handshake.
- L264 _public enumerator_ `AlpnNegotiation` — Handshake failed to negotiate common ALPN.
- L267 _public enumerator_ `StreamLimit` — Stream limit was reached.
- L270 _public enumerator_ `Unknown` — Unknown error.

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Public/QuicMessages.h` (Public)


#### struct `FMessageHeader`  
`struct FMessageHeader`  
_L25-55_
- desc: Structure for QUIC message headers.
- L28 _public member_ `EQuicMessageType MessageType;` — Holds the message type.
- L31 _public member_ `FGuid RecipientId;` — Holds the recipient node id.
- L34 _public member_ `FGuid SenderId;` — Holds the sender node id.
- L37 _public member_ `uint32 SerializedMessageSize;` — Holds the serialized message size.
- L40 _public function_ `FMessageHeader() : MessageType(EQuicMessageType::Hello) , RecipientId(FGuid::NewGuid()) , SenderId(FGuid::NewGuid()) , SerializedMessageSize(0)` — Default constructor.
- L48 _public function_ `FMessageHeader(const EQuicMessageType InMessageType, const FGuid InRecipientId, const FGuid InSenderId, const uint32 InSerializedMessageSize) : MessageType(InMessageType) , RecipientId(InRecipientId) , SenderId(InSenderId) , SerializedMessageSize(InSerializedMessageSize)` — Creates and initializes a new instance.

#### struct `FInboundMessage`  
`struct FInboundMessage`  
_L61-93_
- desc: Structure for unserialized inbound messages.
- L64 _public member_ `FQuicPayloadPtr UnserializedMessage;` — Holds the message data.
- L67 _public member_ `FMessageHeader MessageHeader;` — Holds the message header.
- L70 _public member_ `FIPv4Endpoint Sender;` — Holds the sender's network endpoint.
- L73 _public member_ `FIPv4Endpoint Receiver;` — Holds the receiver's network endpoint.
- L76 _public function_ `FInboundMessage() : UnserializedMessage(nullptr) , MessageHeader(FMessageHeader()) , Sender(FIPv4Endpoint::Any) , Receiver(FIPv4Endpoint::Any)` — Default constructor.
- L84 _public function_ `FInboundMessage( FQuicPayloadPtr InUnserializedMessage, const FMessageHeader& InMessageHeader, const FIPv4Endpoint& InSender, const FIPv4Endpoint& InReceiver) : UnserializedMessage(InUnserializedMessage) , MessageHeader(InMessageHeader) , Sender(InSender) , Receiver(InReceiver)` — Creates and initializes a new instance.

#### struct `FOutboundMessage`  
`struct FOutboundMessage`  
_L99-139_
- desc: Structure for serialized outbound messages.
- L102 _public member_ `FIPv4Endpoint Recipient;` — Holds the recipient endpoint address.
- L105 _public member_ `bool bHasPayload;` — Flag indicating whether this message has a payload.
- L108 _public member_ `FQuicPayloadPtr SerializedPayload;` — Holds the serialized payload data.
- L111 _public member_ `FQuicPayloadPtr SerializedHeader;` — Holds the serialized message header.
- L114 _public function_ `FOutboundMessage() : Recipient(FIPv4Endpoint::Any) , bHasPayload(false) , SerializedPayload(nullptr) , SerializedHeader(nullptr)` — Default constructor.
- L122 _public function_ `FOutboundMessage(const FIPv4Endpoint InRecipient, const FQuicPayloadPtr InSerializedMessage, const FQuicPayloadPtr InSerializedHeader) : Recipient(InRecipient) , bHasPayload(true) , SerializedPayload(InSerializedMessage) , SerializedHeader(InSerializedHeader)` — Creates and initializes a new instance.
- L132 _public function_ `FOutboundMessage(const FIPv4Endpoint InRecipient, const FQuicPayloadPtr InSerializedHeader) : Recipient(InRecipient) , bHasPayload(false) , SerializedPayload(nullptr) , SerializedHeader(InSerializedHeader)` — Creates and initializes a new header-only instance.

#### Free symbols / members of external scopes

- L16 _macro_ `#define QUIC_MESSAGE_HEADER_SIZE 96`
- L18 _typedef_ `using FQuicPayload = TArray<uint8>;`
- L19 _typedef_ `using FQuicPayloadPtr = TSharedPtr<FQuicPayload, ESPMode::ThreadSafe>;`

### `Plugins/Experimental/QuicMessaging/Source/QuicMessagingTransport/Public/QuicNodeInfo.h` (Public)


#### struct `FQuicNodeInfo`  
`struct FQuicNodeInfo`  
_L13-48_
- desc: Structure for known remote endpoints.
- L16 _public member_ `FIPv4Endpoint Endpoint;` — Holds the node's endpoint.
- L19 _public member_ `FGuid NodeId;` — Holds the endpoint's node identifier.
- L22 _public member_ `FIPv4Endpoint LocalEndpoint;` — Holds the node's local quic endpoint.
- L25 _public member_ `bool bIsAuthenticated;` — Denotes wheter this remote node is authenticated or not.
- L28 _public member_ `FMessageTransportStatistics Statistics;` — Various transport statistics for this endpoint
- L31 _public function_ `FQuicNodeInfo() : Endpoint(FIPv4Endpoint::Any) , NodeId(FGuid::NewGuid()) , LocalEndpoint(FIPv4Endpoint::Any) , bIsAuthenticated(false) , Statistics({})` — Default constructor.
- L40 _public function_ `FQuicNodeInfo(const FIPv4Endpoint& InEndpoint, const FGuid& InNodeId, const FIPv4Endpoint& InLocalEndpoint) : Endpoint(InEndpoint) , NodeId(InNodeId) , LocalEndpoint(InLocalEndpoint) , bIsAuthenticated(false) , Statistics({})` — Creates and initializes a new instance.
