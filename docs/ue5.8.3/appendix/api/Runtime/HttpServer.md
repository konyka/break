# Runtime / HttpServer

- module root: `Source/Runtime/Online/HTTPServer`
- headers: 21; symbols: 353
- symbol kinds: class=5, delegate=7, enum=7, enumerator=74, function=26, macro=17, member=82, namespace=1, prototype=114, struct=15, typedef=5
- PrivateDependencyModuleNames: Core, HTTP, Sockets

### `Source/Runtime/Online/HTTPServer/Private/HttpConnection.h` (Private)


#### struct `FHttpConnection`  
`struct FHttpConnection final : public TSharedFromThis<FHttpConnection>`  
_L22-270_
- inherits: `TSharedFromThis<FHttpConnection>`
- L31 _public prototype_ `FHttpConnection(FSocket* InSocket, TSharedPtr<FHttpRouter> InRouter, uint32 InOriginPort, uint32 InConnectionId);` — Constructor @param InSocket The underlying file descriptor
- L35 _public prototype_ `~FHttpConnection();` — Destructor
- L42 _public prototype_ `void Tick(float DeltaTime);` — Ticks the connection to drive internal state @param DeltaTime The elapsed time since the last Tick()
- L47 _public function_ `FORCEINLINE EHttpConnectionState GetState() const` — Returns the current state of the connection
- L57 _public prototype_ `void RequestDestroy(bool bGraceful);` — Signals the connection to destroy itself @param bGraceful Whether to gracefully destroy pending current operations
- L62 _public function_ `FORCEINLINE bool IsHttpKeepAliveEnabled() const` — Determines whether this connection should remain open after writing
- L67 _public function_ `FORCEINLINE bool operator==(const FHttpConnection& Other) const`
- L99 _private prototype_ `void ChangeState(EHttpConnectionState NewState);` — Changes the internal state of the connection to NewState @param NewState The state to transition to
- L107 _private prototype_ `void TransferState(EHttpConnectionState CurrentState, EHttpConnectionState NextState);` — Changes the internal state from the caller-supplied current state to the next state @param CurrentState The expected current state @param NextState    The next state
- L114 _private prototype_ `void BeginRead(float DeltaTime);` — Begins a read operation @param DeltaTime The elapsed time since the last invocation
- L121 _private prototype_ `void ContinueRead(float DeltaTime);` — Continues an in-progress read operation @param DeltaTime The elapsed time since the last invocation
- L128 _private prototype_ `void CompleteRead(const TSharedPtr<FHttpServerRequest>& Request);` — Completes a previously begun read operation @param Request The instantiated request object
- L136 _private prototype_ `void ProcessRequest(const TSharedPtr<FHttpServerRequest>& Request, const FHttpResultCallback& OnProcessingComplete);` — Proxies the respective request to a bound handler @param Request              The request to process @param OnProcessingComplete The callback to be invoked upon completion @return                     true if the request was accepted by a handler, false otherwise
- L144 _private prototype_ `void BeginWrite(TUniquePtr<FHttpServerResponse>&& Response, uint32 RequestNumber);` — Begins a write operation @param Response      The response to write @param RequestNumber The expected and unique request number
- L151 _private prototype_ `void ContinueWrite(float DeltaTime);` — Continues an in-progress write operation @param DeltaTime The elapsed time since the last invocation
- L156 _private prototype_ `void CompleteWrite();` — Completes a previously begun write operation
- L162 _private prototype_ `void Destroy(EConnectionDestroyReason DestroyReason);` — Closes and nullifies the underlying connection @param DestroyReason The reason why the connection should be destroyed.
- L170 _private prototype_ `void HandleReadError(EHttpServerResponseCodes ErrorCode, const TCHAR* ErrorCodeStr);` — Logs and responds with the caller-supplied error code @param ErrorCode The HTTP error code @param ErrorCodeStr The machine-readable error description
- L177 _private prototype_ `void HandleWriteError(const TCHAR* ErrorCodeStr);` — Logs the caller-supplied error code and closes the connection @param ErrorCodeStr The machine-readable error description
- L186 _private prototype_ `static bool ResolveKeepAlive(HttpVersion::EHttpServerHttpVersion HttpVersion, const TArray<FString>& ConnectionHeaders);` — Determines whether KeepAlive is set based on the caller-supplied http version and connection headers @param HttpVersion         The http version of the request @param ConnectionHeaders   The request "Connection:" headers @return                    true if KeepAlive should be set, false otherwise
- L193 _private function_ `static const TCHAR* LexToString(EConnectionDestroyReason DestroyReason)` — Convert a connection destroy reason to a string. @param DestroyReason The reason why the connection was destroyed. @return				The output string.
- L222 _private member_ `FSocket* Socket;` — Accepted external socket
- L225 _private member_ `EHttpConnectionState State = EHttpConnectionState::AwaitingRead;` — State of the connection
- L228 _private member_ `const TSharedPtr<FHttpRouter> Router;` — Routing mechanism
- L231 _private member_ `uint32 OriginPort;` — The origin port on which this connection was accepted
- L234 _private member_ `uint32 ConnectionId;` — The connection identifier (used for logging purposes)
- L237 _private member_ `FHttpConnectionRequestReadContext ReadContext;` — Helper reader context to track the state of streaming request reads
- L240 _private member_ `FHttpConnectionResponseWriteContext WriteContext;` — Helper writer context to track the state of streaming response writes
- L243 _private member_ `bool bKeepAlive = true;` — Whether to keep this connection alive after writing
- L246 _private member_ `bool bGracefulDestroyRequested = false;` — Whether to gracefully close pending current operations
- L249 _private member_ `uint32 LastRequestNumber = 0;` — Internal state tracker (incremented per-request-read) used to validate request/response throughput
- L260 _private member_ `TUniquePtr<FHttpServerResponse> PendingResponse;` — Single-slot pending response captured by `OnProcessingComplete` while the connection is still draining a previous write (state == `Writing`). `CompleteWrite` drains it once the in-flight response finishes; a `checkf(!PendingResponse)` at the queue site enforces the two-deep `FHttpResultCallback` contract. Silently dropped if the connection transitions to teardown before the drain runs: `bGracefulDestroyRequested`, `!bKeepAlive`, or `HandleWriteError`. A `Verbose` log is emitted on the drop path so the disappearance is traceable in production logs.
- L263 _private member_ `static constexpr float ConnectionTimeout = 5.0f;` — The duration (seconds) at which connections are forcefully timed out
- L266 _private member_ `static constexpr float ConnectionKeepAliveTimeout = 15.0f;` — The duration (seconds) at which idle keep-alive connections are forcefully timed out
- L269 _private member_ `FHttpServerConnectionConfig Config;` — Connection configuration data

#### enum `FHttpConnection::EConnectionDestroyReason`  
`enum class EConnectionDestroyReason : uint8`  
_L81-90_
- desc: The reason why the connection was destroyed.
- L83 _public enumerator_ `WriteError`
- L84 _public enumerator_ `AwaitReadTimeout`
- L85 _public enumerator_ `BeginReadTimeout`
- L86 _public enumerator_ `ReadTimeout`
- L87 _public enumerator_ `WriteTimeout`
- L88 _public enumerator_ `WriteComplete`
- L89 _public enumerator_ `DestroyRequest`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpConnection, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpConnection, Log, All);`
- L72 _function_ `friend uint32 GetTypeHash(const FHttpConnection& Conn)`

### `Source/Runtime/Online/HTTPServer/Private/HttpConnectionContext.h` (Private)


#### enum `EHttpConnectionContextState`  
`enum class EHttpConnectionContextState`  
_L7-12_
- L9 _public enumerator_ `Continue`
- L10 _public enumerator_ `Done`
- L11 _public enumerator_ `Error`

#### struct `FHttpConnectionContext`  
`struct FHttpConnectionContext`  
_L15-78_
- L25 _public prototype_ `void AddElapsedIdleTime(float DeltaTime);` — Adds to the context elapsed time @param DeltaTime The elapsed time (seconds) to add
- L30 _public function_ `FORCEINLINE float GetElapsedIdleTime() const` — Gets the elapsed time (seconds) since last activity
- L38 _public function_ `FORCEINLINE EHttpServerResponseCodes GetErrorCode() const` — Gets the respective error code
- L46 _public function_ `FORCEINLINE const FString& GetErrorStr() const` — Gets the cumulative error string
- L56 _protected prototype_ `FHttpConnectionContext();` — Constructor
- L61 _protected prototype_ `virtual ~FHttpConnectionContext();` — Destructor
- L68 _protected prototype_ `void AddError(const FString& ErrorCodeStr, EHttpServerResponseCodes ErrorCode = EHttpServerResponseCodes::Unknown);` — Adds the caller-supplied error to the context @param ErrorCode The machine-readable error code
- L71 _protected member_ `float ElapsedIdleTime = 0.0f;` — Tracks time since last read/write activity
- L74 _protected member_ `EHttpServerResponseCodes ErrorCode = EHttpServerResponseCodes::Unknown;` — Tracks the respective ErrorCode
- L77 _protected member_ `FStringOutputDevice ErrorBuilder;` — Tracks cumulative context errors

### `Source/Runtime/Online/HTTPServer/Private/HttpConnectionRequestReadContext.h` (Private)


#### struct `FHttpConnectionRequestReadContext`  
`struct FHttpConnectionRequestReadContext final : public FHttpConnectionContext`  
_L13-133_
- inherits: `FHttpConnectionContext`
- L22 _public prototype_ `FHttpConnectionRequestReadContext(FSocket* InSocket);` — Constructor @param Socket The underlying connection
- L30 _public prototype_ `EHttpConnectionContextState ReadStream(float DeltaTime);` — Reads a request from the connection @param DeltaTime The elapsed time since the last invocation @return The state of the read context
- L35 _public function_ `FORCEINLINE TSharedPtr<FHttpServerRequest> GetRequest() const` — Gets the internally stored request object
- L44 _public prototype_ `void ResetContext();` — Resets the internal state. Should be called for every read.
- L49 _public function_ `float GetSecondsWaitingForReadableSocket() const` — Get the time in seconds spent waiting for the socket to be readable.
- L57 _public function_ `void AddSecondsWaitingForReadableSocket(float Seconds)` — Add time (in seconds) spent waiting for the socket to be readable.
- L65 _public function_ `void ResetSecondsWaitingForReadableSocket()` — Reset the time spent waiting for the socket to be readable.
- L79 _private prototype_ `bool ParseHeader(uint8* ByteBuffer, int32 BufferLen);` — Parses the request header @param  ByteBuffer The bytes to parse @param  BufferLen The length of the supplied byte buffer @return true if no error was encountered, false otherwise
- L88 _private prototype_ `bool ParseBody(uint8* ByteBuffer, int32 BufferLen);` — Parses the request body @param  ByteBuffer The bytes to parse @param  BufferLen The length of the supplied byte buffer @return true if no error was encountered, false otherwise
- L98 _private prototype_ `bool IsRequestValid(const FHttpServerRequest& InRequest);` — Determines whether the member Request object is valid @param InRequest The request to validate eg: POST requests with ContentLength > 0 are invalid eg: Body-capable requests with mismatched content-length headers and bodies are invalid @return true if the current Request object is valid, false otherwise
- L106 _private prototype_ `TSharedPtr<FHttpServerRequest> BuildRequest(const FString& RequestHeader);` — Builds an FHttpServerRequest from the caller-supplied http header string @param RequestHeader The complete http request header string @return An instantiated request object with valid input, nullptr otherwise
- L115 _private prototype_ `static bool ParseContentLength(const FHttpServerRequest& InRequest, int32& OutContentLength);` — Gets the expected Content-Length from the member Request object @param InRequest The request to validate @param OutContentLength Set to the respective content length when returns true @return true if content length is specified, false otherwise
- L120 _private member_ `FSocket* Socket;` — The underlying connection
- L122 _private member_ `TSharedPtr<FHttpServerRequest> Request;` — Internal request state.
- L124 _private member_ `bool bParseHeaderComplete = false;` — Whether the header has been fully parsed
- L126 _private member_ `bool bParseBodyComplete = false;` — Whether the body has been fully parsed
- L128 _private member_ `TArray<uint8> HeaderBytes;` — State variable which stores incoming header bytes
- L130 _private member_ `int32 IncomingRequestBodyBytesToRead = 0;` — State variable which tracks bytes read for an incoming request
- L132 _private member_ `float SecondsWaitingForReadableSocket = 0.f;` — The time spent waiting for the socket to be readable.

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpConnectionRequestReadContext, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpConnectionRequestReadContext, Log, All);`

### `Source/Runtime/Online/HTTPServer/Private/HttpConnectionResponseWriteContext.h` (Private)


#### struct `FHttpConnectionResponseWriteContext`  
`struct FHttpConnectionResponseWriteContext final : public FHttpConnectionContext`  
_L13-112_
- inherits: `FHttpConnectionContext`
- L22 _public prototype_ `FHttpConnectionResponseWriteContext(FSocket* InSocket);` — Constructor @param InSocket The underlying connection
- L30 _public prototype_ `EHttpConnectionContextState WriteStream(float DeltaTime);` — Writes to the connection @param DeltaTime The elapsed time since the last invocation @return The state of the write context
- L38 _public prototype_ `void ResetContext(TUniquePtr<FHttpServerResponse>&& Response);` — Resets the internal state. Should be called before every write. @param Response The response to be written
- L47 _public function_ `bool IsMultipleWriteStream() const` — Determine if the connection should expect multiple writes as part of this response before the next read/close by re-using an existing FHttpResultCallback.  Streams should issue the first response callback with an empty body to write headers. @return true if there are multiple writes expected
- L54 _public function_ `bool HasAdditionalWrites() const` — Determine if the context's current state is expecting additional body writes @return true if there are more writes
- L61 _public function_ `bool ShouldCloseAfterWrite() const` — Determine if the connection should be destroyed once this response finishes writing. @return true if the current response carries the `CloseAfterWrite` flag
- L73 _private prototype_ `bool WriteBytes(const uint8* Bytes, int32 BytesLen, int32 &OutBytesWritten);` — Writes the caller-supplied Bytes up to BytesLen as permitted by the socket @param  Bytes The bytes to write @param  The desired number of bytes to write @param  OutBytesWritten The number of bytes actually written @return true if the write was successful, false otherwise
- L80 _private prototype_ `bool IsWriteHeaderComplete() const;` — Determines whether the header has been completely written @return true if the header has been completely written, false otherwise
- L86 _private prototype_ `bool IsWriteBodyComplete() const;` — Determines whether the body has been completely written @return true if the body has been completely written, false otherwise
- L96 _private prototype_ `static TArray<uint8> SerializeHeadersUtf8(HttpVersion::EHttpServerHttpVersion HttpVersion, EHttpServerResponseCodes ResponseCode, const TMap<FString, TArray<FString>>& HeadersMap);` — Creates a UTF8-serialized HTTP header in byte representation @param  HttpVersion  The HTTP version @param  ResponseCode The HTTP response code @param  HeadersMap   The associative header key to values map @return              The UTF8-encoded byte representation
- L101 _private member_ `FSocket* Socket;` — The underlying connection
- L103 _private member_ `TUniquePtr<FHttpServerResponse> Response;` — The response to write
- L105 _private member_ `TArray<uint8> HeaderBytes;` — State
- L107 _private member_ `int32 HeaderBytesWritten = 0;` — The total number of header bytes written
- L109 _private member_ `int32 BodyBytesWritten = 0;` — The total number of body bytes written
- L111 _private member_ `bool bStreamingHeadersPending = false;` — For streaming responses, defer sending headers until first chunk arrives

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpConnectionResponseWriteContext, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpConnectionResponseWriteContext, Log, All);`

### `Source/Runtime/Online/HTTPServer/Private/HttpConnectionTypes.h` (Private)


#### enum `EHttpConnectionState`  
`enum class EHttpConnectionState`  
_L21-33_
- desc: FHttpConnection state model
- L24 _public enumerator_ `AwaitingRead` — Awaiting available data
- L26 _public enumerator_ `Reading` — Reading available data
- L28 _public enumerator_ `AwaitingProcessing` — Awaiting request handler completion
- L30 _public enumerator_ `Writing` — Writing response to client
- L32 _public enumerator_ `Destroyed` — Awaiting destruction via listener

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef FGuid HttpConnectionIdType;` — Utility unique identifier for FHttpConnections
- L16 _typedef_ `typedef TSet<TSharedPtr<FHttpConnection>> FHttpConnectionPool;` — FHttpConnectionPool

### `Source/Runtime/Online/HTTPServer/Private/HttpListener.h` (Private)


#### class `FHttpListener`  
`class FHttpListener final`  
_L15-117_
- L25 _public prototype_ `FHttpListener(uint32 InListenPort);` — Constructor @param InListenPort The port on which to listen for incoming connections
- L30 _public prototype_ `~FHttpListener();` — Destructor
- L37 _public prototype_ `bool StartListening();` — Starts listening for and accepting incoming connections @return true if the listener was able to start listening, false otherwise
- L42 _public prototype_ `void StopListening();` — Stops listening for and accepting incoming connections
- L49 _public prototype_ `void Tick(float DeltaTime);` — Tick the listener to otherwise commence connection flows @param DeltaTime The elapsed time since the last tick
- L56 _public prototype_ `bool HasPendingConnections() const;` — Determines whether this listener has pending connections in-flight @return true if there are pending connections, false otherwise
- L62 _public function_ `FORCEINLINE bool IsListening() const` — Determines whether the listener has been initialized @return true if this listener is bound and listening, false otherwise
- L71 _public function_ `FORCEINLINE TSharedPtr<IHttpRouter> GetRouter() const` — Gets the respective router @return The respective router
- L81 _private prototype_ `void AcceptConnections();` — Accepts available connection(s)
- L88 _private prototype_ `void TickConnections(float DeltaTime);` — Ticks connections in reading/writing phases @param DeltaTime The elapsed time since the last tick
- L93 _private prototype_ `void RemoveDestroyedConnections();` — Removes connections that have been destroyed
- L98 _private member_ `bool bIsListening = false;` — Whether this listeners has begun listening
- L101 _private member_ `uint32 ListenPort = 0;` — The port on which the binding socket listens
- L104 _private member_ `FUniqueSocket ListenSocket;` — The binding socket which accepts incoming connections
- L107 _private member_ `TSharedPtr<FHttpRouter> Router = nullptr;` — The mechanism that routes requests to respective handlers
- L110 _private member_ `FHttpConnectionPool Connections;` — The collection of unique connections
- L113 _private member_ `uint32 NumConnectionsAccepted = 0;` — The total number of connections accepted by this listener
- L116 _private member_ `FHttpServerListenerConfig Config;` — Listener configuration data

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpListener, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpListener, Log, All);`

### `Source/Runtime/Online/HTTPServer/Private/HttpRequestHandlerIterator.h` (Private)


#### struct `FHttpRequestHandlerIterator`  
`struct FHttpRequestHandlerIterator final`  
_L15-82_
- desc: Utility to iterate qualified FHttpRequestHandlers
- L58 _public prototype_ `FHttpRequestHandlerIterator(TSharedPtr<FHttpServerRequest> InRequest, const FHttpRequestHandlerRegistrar& InRequestHandlerRegistrar, TArray<FHttpRequestHandler> InRequestPreprocessors = {});` — Constructor
- L64 _public prototype_ `const FHttpRequestHandler* const Next();` — Determines the next registered request handler @return The next registered request handler if found, nullptr otherwise
- L69 _private member_ `FHttpPathIterator HttpPathIterator;` — Utility to iterate FHttpRoutes in-place
- L72 _private member_ `const TSharedPtr<FHttpServerRequest> Request;` — The basis request
- L75 _private member_ `const FHttpRequestHandlerRegistrar& RequestHandlerRegistrar;` — The associative route/handler registration
- L78 _private member_ `TArray<FHttpRequestHandler> RequestPreprocessors;` — Handlers that should be queried before routing the http request
- L81 _private member_ `int32 CurrentPreprocessorIndex = 0;` — The index to the next preprocessor to execute with the request.

#### struct `FHttpRequestHandlerIterator::FHttpPathIterator`  
`struct FHttpPathIterator final`  
_L21-50_
- desc: Utility (internal) to iterate FHttpPaths in-place
- L28 _public prototype_ `FHttpPathIterator(const FHttpPath& HttpPath);` — Constructor @param HttpPath The iterator starting path
- L34 _public prototype_ `const FString& Next();` — Gets the next route @return The base path of the current path
- L40 _public prototype_ `FORCEINLINE bool HasNext() const;` — Determines whether there is a Next() path to get @return true if there is a next path, false otherwise
- L45 _public member_ `TArray<FString> ParsedTokens;` — Holds the tokens that were removed from the end of the path.
- L47 _private member_ `FString NextPath;`
- L48 _private member_ `bool bFirstIteration = true;`
- L49 _private member_ `bool bLastIteration = false;`

### `Source/Runtime/Online/HTTPServer/Private/HttpRequestHandlerRegistrar.h` (Private)


#### struct `FRouteQueryResult`  
`struct FRouteQueryResult`  
_L13-29_
- desc: The result of a Registrar query.
- L15 _public function_ `operator bool()`
- L23 _public member_ `FHttpRouteHandle RouteHandle = nullptr;` — The query's matching route handle if found, nullptr otherwise.
- L28 _public member_ `TMap<FString, FString> PathParams;` — The parsed parameters, if the query was successful.

#### class `FHttpRequestHandlerRegistrar`  
`class FHttpRequestHandlerRegistrar`  
_L35-115_
- desc: FHttpRequestHandlerRegistrar Represents the associative relationship between Http request paths and respective route handles
- L42 _public prototype_ `void AddRoute(const FHttpRouteHandle& Handle);` — Add a route to the registrar. @param Handle The new route's handle.
- L48 _public prototype_ `void RemoveRoute(const FHttpRouteHandle& Handle);` — Remove a route from the registrar. @param Handle The handle of the route to delete.
- L56 _public prototype_ `bool ContainsRoute(const FHttpPath& RoutePath, EHttpServerRequestVerbs Verb);` — Check if the registrar contains a route. @param RoutePath the HttpPath of the target route. @param Verb the verb associated with the target route. @return Whether the route was found.
- L65 _public prototype_ `FRouteQueryResult QueryRoute(const FString& Query, EHttpServerRequestVerbs Verb, const TArray<FString>* Parsedtokens = nullptr) const;` — Query the registrar for a route, parsing the path parameters if any. @param Query the path to search for in the registry. @param Verb the handler's verb to look for. (A route might have multiple handlers each with a different verb.) @param ParsedTokens An optional list of tokens that were removed from the end of the path. @return The query's result, indicating if a match was found and parsed path parameters.
- L81 _private prototype_ `TTuple<TArray<FHttpRouteHandle>*, int64> FindStaticRoute(const FString& RoutePath, EHttpServerRequestVerbs Verb);` — Find a static route in the registrar. @return The route's container and index.
- L87 _private prototype_ `TTuple<TArray<FDynamicRouteHandleWrapper>*, int64> FindDynamicRoute(const FString& RoutePath, EHttpServerRequestVerbs Verb);` — Find a dynamic route in the registrar. @return The route's container and index.
- L90 _private prototype_ `bool ContainsStaticRoute(const FHttpPath& RoutePath, EHttpServerRequestVerbs Verb);` — Checks if the registrar contains a static route given a path and verb.
- L93 _private prototype_ `bool ContainsDynamicRoute(const FHttpPath& RoutePath, EHttpServerRequestVerbs Verb);` — Checks if the registrar contains a dynamic route given a path and verb.
- L96 _private prototype_ `bool RemoveStaticRoute(const FHttpPath& RoutePath, EHttpServerRequestVerbs Verb);` — Removes a static route given a path and verb.
- L99 _private prototype_ `bool RemoveDynamicRoute(const FHttpPath& RoutePath, EHttpServerRequestVerbs Verb);` — Removes a dynamic route given a path and verb.
- L102 _private prototype_ `bool MatchesPath(const TArray<FString>& InPath, const TArray<FString>& TemplatePath) const;` — Checks whether a given path template matches an input path.
- L104 _private prototype_ `TMap<FString, FString> ParsePathParameters(const TArray<FString>& InPath, const TArray<FString>& TemplatePath) const;` — Extract the path parameters from the path.
- L108 _private member_ `TMap<const FString, TArray<FHttpRouteHandle>> StaticRoutes;` — Map of static routes to a list of handlers for different HTTP verbs for this route.
- L114 _private member_ `TMap<const FString, TArray<FDynamicRouteHandleWrapper>> DynamicRoutes;` — Map of subgroups of dynamic path handlers. A dynamic path is a path containing a path parameter. The subgroup consists of the portion of the dynamic path that does not contain path parameters, identified by ':'.

#### struct `FHttpRequestHandlerRegistrar::FDynamicRouteHandleWrapper`  
`struct FDynamicRouteHandleWrapper`  
_L67-75_
- L69 _public prototype_ `FDynamicRouteHandleWrapper(FHttpRouteHandle Handle);`
- L72 _public member_ `FHttpRouteHandle Handle;` — The handler for thi;s route.
- L74 _public member_ `TArray<FString> DynamicPathSectionTokens;` — Path tokens starting from the first colon in the path

### `Source/Runtime/Online/HTTPServer/Private/HttpRouter.h` (Private)


#### class `FHttpRouter`  
`class FHttpRouter final : public IHttpRouter`  
_L12-37_
- inherits: `IHttpRouter`
- L17 _public prototype_ `bool Query(const TSharedPtr<FHttpServerRequest>& Request, const FHttpResultCallback& OnProcessingComplete) override;` — IHttpRouter Overrides
- L18 _public prototype_ `FHttpRouteHandle BindRoute(const FHttpPath& HttpPath, const EHttpServerRequestVerbs& RequestVerbs, const FHttpRequestHandler& Handler) override;`
- L19 _public prototype_ `void UnbindRoute(const FHttpRouteHandle& RouteHandle) override;`
- L20 _public prototype_ `FDelegateHandle RegisterRequestPreprocessor(FHttpRequestHandler RequestPreprocessor) override;`
- L21 _public prototype_ `void UnregisterRequestPreprocessor(const FDelegateHandle& RequestPreprocessorHandle) override;`
- L28 _public prototype_ `FHttpRequestHandlerIterator CreateRequestHandlerIterator(const TSharedPtr<FHttpServerRequest>& Request) const;` — Creates a request handler iterator to facilitate http routing @param Request The basis request for which matching request handlers are found @return The instantiated FHttpRequestHandlerIterator
- L33 _private member_ `FHttpRequestHandlerRegistrar RequestHandlerRegistrar;` — The associative pairing of Http routes to respective request handlers
- L36 _private member_ `TMap<FDelegateHandle, FHttpRequestHandler> RequestPreprocessors;` — Holds the list of request preprocessors.

### `Source/Runtime/Online/HTTPServer/Private/HttpServerConfig.h` (Private)


#### struct `FHttpServerListenerConfig`  
`struct FHttpServerListenerConfig`  
_L10-22_
- L13 _public member_ `FString BindAddress = FString("loc` — The address to bind
- L15 _public member_ `int32 BufferSize = 512 * 1024;` — Maximum send buffer size
- L17 _public member_ `int32 ConnectionsBacklogSize = 16;` — Number of pending connections to queue
- L19 _public member_ `int32 MaxConnectionsAcceptPerFrame = 1;` — Max Number of connections to accept per frame
- L21 _public member_ `bool bReuseAddressAndPort = false;` — If true, call FSocket::SetReuseAddr when binding to allow the use of an already bound address/port

#### struct `FHttpServerConnectionConfig`  
`struct FHttpServerConnectionConfig`  
_L24-28_
- L27 _public member_ `float BeginReadWaitTimeMS = 1;` — Time in milliseconds to wait for data to be available when ticking the connection.

#### struct `FHttpServerConfig`  
`struct FHttpServerConfig`  
_L30-51_
- L38 _public prototype_ `static const FHttpServerListenerConfig GetListenerConfig(uint32 Port);` — Gets the listener configuration for the caller-supplied Port @param Port The respective listener port @return The per-port configuration if configured, or default configuration
- L45 _public prototype_ `static const FHttpServerConnectionConfig GetConnectionConfig();` — Gets the connection configuration @return The configuration if configured, or default configuration
- L50 _public prototype_ `static void OnConfigSectionsChanged(const FString& IniFilename, const TSet<FString>& SectionNames);` — Callback when the IniConfig is updated so that the internal cache can be updated

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpServerConfig, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpServerConfig, Log, All);`

### `Source/Runtime/Online/HTTPServer/Private/HttpServerConstantsPrivate.h` (Private)


#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_HTTP_SERVER_HEADER_KEYS_CONTENT_TYPE TEXT("content-type")`
- L7 _macro_ `#define UE_HTTP_SERVER_HEADER_KEYS_CONTENT_LENGTH TEXT("content-length")`
- L8 _macro_ `#define UE_HTTP_SERVER_HEADER_KEYS_CONNECTION TEXT("connection")`
- L9 _macro_ `#define UE_HTTP_SERVER_HEADER_KEYS_KEEP_ALIVE TEXT("keep-alive")`
- L12 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_SOCKET_CLOSED_FAILURE TEXT("errors.com.epicgames.httpserver.socket_closed_failure")` — Connection
- L13 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_SOCKET_RECV_FAILURE TEXT("errors.com.epicgames.httpserver.socket_recv_failure")`
- L14 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_SOCKET_SEND_FAILURE TEXT("errors.com.epicgames.httpserver.socket_send_failure")`
- L17 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_ROUTE_HANDLER_NOT_FOUND TEXT("errors.com.epicgames.httpserver.route_handler_not_found")` — Routing
- L20 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_MALFORMED_REQUEST_SIZE TEXT("errors.com.epicgames.httpserver.malformed_request_size")` — Serialization
- L21 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_MALFORMED_REQUEST_HEADER TEXT("errors.com.epicgames.httpserver.malformed_request_header")`
- L22 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_MISSING_REQUEST_HEADERS TEXT("errors.com.epicgames.httpserver.missing_request_headers")`
- L23 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_MALFORMED_REQUEST_BODY TEXT("errors.com.epicgames.httpserver.malformed_request_body")`
- L24 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_UNKNOWN_REQUEST_VERB TEXT("errors.com.epicgames.httpserver.unknown_request_verb")`
- L25 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_UNSUPPORTED_HTTP_VERSION TEXT("errors.com.epicgames.httpserver.unsupported_http_version")`
- L26 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_INVALID_CONTENT_LENGTH_HEADER TEXT("errors.com.epicgames.httpserver.invalid_content_length_header")`
- L27 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_MISSING_CONTENT_LENGTH_HEADER TEXT("errors.com.epicgames.httpserver.missing_content_length_header")`
- L28 _macro_ `#define UE_HTTP_SERVER_ERROR_STR_MISMATCHED_CONTENT_LENGTH_BODY_TOO_LARGE TEXT("errors.com.epicgames.httpserver.mismatched_content_length_body_too_large")`

### `Source/Runtime/Online/HTTPServer/Public/HttpPath.h` (Public)


#### struct `FHttpPath`  
`struct FHttpPath`  
_L11-88_
- L19 _public prototype_ `FHttpPath();` — Constructor
- L26 _public prototype_ `FHttpPath(FString InPath);` — Constructor @param Path - The http path
- L31 _public prototype_ `const FString& GetPath() const;` — Gets the respective http path as a string
- L39 _public prototype_ `uint32 ParsePathTokens(TArray<FString>& OutPathTokens) const;` — Parses the respective http path into a caller-supplied array @param OutPathTokens The caller-allocated tokens array @return The number of tokens parsed
- L46 _public prototype_ `void SetPath(FString Path);` — Sets the server-relative http path @param Path the new path to assign
- L51 _public prototype_ `bool IsValidPath() const;` — Determines if the path is valid
- L56 _public prototype_ `bool IsRoot() const;` — Determines if the path is /
- L64 _public prototype_ `void MakeRelative(const FString& OtherPath);` — Re-path this path sans the path of another MakeRelative(/a/b/c/d, /a/b) => /c/d @param OtherPath The path to make relative against
- L67 _public function_ `bool operator==(const FHttpPath& Other) const` — TMap<> Comparer
- L83 _private prototype_ `void NormalizePath();` — Normalizes the internally stored Path
- L86 _private member_ `FString Path = "/"` — The respective Http path

#### Free symbols / members of external scopes

- L73 _function_ `friend uint32 GetTypeHash(const FHttpPath& InPath)`

### `Source/Runtime/Online/HTTPServer/Public/HttpRequestHandler.h` (Public)


#### Free symbols / members of external scopes

- L19 _typedef_ `using FHttpRequestHandler = TDelegate<bool(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete)>;` — FHttpRequestHandler NOTE - Returning true implies that the delegate will eventually invoke OnComplete NOTE - Returning false implies that the delegate will never invoke OnComplete @param Request The incoming http request to be handled @param OnComplete The callback to invoke to write an http response @return True if the request has been handled, false otherwise

### `Source/Runtime/Online/HTTPServer/Public/HttpResultCallback.h` (Public)


#### Free symbols / members of external scopes

- L19 _typedef_ `typedef TFunction<void(TUniquePtr<FHttpServerResponse>&& Response)> FHttpResultCallback;` — FHttpResultCallback This callback is intended to be invoked exclusively by FHttpRequestHandler delegates. Synchronous reentry contract: a streaming handler using `MultipleWriteStream | HasAdditionalWrites` may invoke this callback up to twice on the same call stack (e.g. SSE open + a single follow-up frame). The second invocation is captured into the connection's single-slot pending response and drained once the in-flight write finishes. A third synchronous invocation asserts via `checkf`. Cross-tick invocations are not bounded. @param Response The response to write

### `Source/Runtime/Online/HTTPServer/Public/HttpRouteHandle.h` (Public)


#### struct `FHttpRouteHandleInternal`  
`struct FHttpRouteHandleInternal`  
_L6-20_
- L8 _public function_ `FHttpRouteHandleInternal(FString InPath, EHttpServerRequestVerbs InVerbs, FHttpRequestHandler InHandler) : Path(MoveTemp(InPath)) , Verbs(InVerbs) , Handler(MoveTemp(InHandler))`
- L15 _public member_ `const FString Path;` — The respective bound http path
- L17 _public member_ `const EHttpServerRequestVerbs Verbs;` — The qualifying http verbs for which this route is valid
- L19 _public member_ `const FHttpRequestHandler Handler;` — The respective handler to be invoked

#### Free symbols / members of external scopes

- L27 _typedef_ `typedef TSharedPtr<const FHttpRouteHandleInternal> FHttpRouteHandle;` — FHttpRouteHandle Returned by IHttpRouter BindRoute() invocations. Clients may test this value to validate and relinquish http router bindings

### `Source/Runtime/Online/HTTPServer/Public/HttpServerConstants.h` (Public)


#### enum `EHttpServerResponseCodes`  
`enum class EHttpServerResponseCodes : uint16`  
_L5-92_
- L11 _public enumerator_ `Unknown = 0` — status code not set yet
- L13 _public enumerator_ `Continue = 100` — the request can be continued.
- L15 _public enumerator_ `SwitchProtocol = 101` — the server has switched protocols in an upgrade header.
- L17 _public enumerator_ `Ok = 200` — the request completed successfully.
- L19 _public enumerator_ `Created = 201` — the request has been fulfilled and resulted in the creation of a new resource.
- L21 _public enumerator_ `Accepted = 202` — the request has been accepted for processing, but the processing has not been completed.
- L23 _public enumerator_ `Partial = 203` — the returned meta information in the entity-header is not the definitive set available from the origin server.
- L25 _public enumerator_ `NoContent = 204` — the server has fulfilled the request, but there is no new information to send back.
- L27 _public enumerator_ `ResetContent = 205` — the request has been completed, and the client program should reset the document view that caused the request to be sent to allow the user to easily initiate another input action.
- L29 _public enumerator_ `PartialContent = 206` — the server has fulfilled the partial get request for the resource.
- L31 _public enumerator_ `Ambiguous = 300` — the server couldn't decide what to return.
- L33 _public enumerator_ `Moved = 301` — the requested resource has been assigned to a new permanent uri (uniform resource identifier), and any future references to this resource should be done using one of the returned uris.
- L35 _public enumerator_ `Redirect = 302` — the requested resource resides temporarily under a different uri (uniform resource identifier).
- L37 _public enumerator_ `RedirectMethod = 303` — the response to the request can be found under a different uri (uniform resource identifier) and should be retrieved using a get http verb on that resource.
- L39 _public enumerator_ `NotModified = 304` — the requested resource has not been modified.
- L41 _public enumerator_ `UseProxy = 305` — the requested resource must be accessed through the proxy given by the location field.
- L43 _public enumerator_ `RedirectKeepVerb = 307` — the redirected request keeps the same http verb. http/1.1 behavior.
- L45 _public enumerator_ `BadRequest = 400` — the request could not be processed by the server due to invalid syntax.
- L47 _public enumerator_ `Denied = 401` — the requested resource requires user authentication.
- L49 _public enumerator_ `PaymentReq = 402` — not currently implemented in the http protocol.
- L51 _public enumerator_ `Forbidden = 403` — the server understood the request, but is refusing to fulfill it.
- L53 _public enumerator_ `NotFound = 404` — the server has not found anything matching the requested uri (uniform resource identifier).
- L55 _public enumerator_ `BadMethod = 405` — the http verb used is not allowed.
- L57 _public enumerator_ `NoneAcceptable = 406` — no responses acceptable to the client were found.
- L59 _public enumerator_ `ProxyAuthReq = 407` — proxy authentication required.
- L61 _public enumerator_ `RequestTimeout = 408` — the server timed out waiting for the request.
- L63 _public enumerator_ `Conflict = 409` — the request could not be completed due to a conflict with the current state of the resource. the user should resubmit with more information.
- L65 _public enumerator_ `Gone = 410` — the requested resource is no longer available at the server, and no forwarding address is known.
- L67 _public enumerator_ `LengthRequired = 411` — the server refuses to accept the request without a defined content length.
- L69 _public enumerator_ `PrecondFailed = 412` — the precondition given in one or more of the request header fields evaluated to false when it was tested on the server.
- L71 _public enumerator_ `RequestTooLarge = 413` — the server is refusing to process a request because the request entity is larger than the server is willing or able to process.
- L73 _public enumerator_ `UriTooLong = 414` — the server is refusing to service the request because the request uri (uniform resource identifier) is longer than the server is willing to interpret.
- L75 _public enumerator_ `UnsupportedMedia = 415` — the server is refusing to service the request because the entity of the request is in a format not supported by the requested resource for the requested method.
- L77 _public enumerator_ `TooManyRequests = 429` — too many requests, the server is throttling
- L79 _public enumerator_ `RetryWith = 449` — the request should be retried after doing the appropriate action.
- L81 _public enumerator_ `ServerError = 500` — the server encountered an unexpected condition that prevented it from fulfilling the request.
- L83 _public enumerator_ `NotSupported = 501` — the server does not support the functionality required to fulfill the request.
- L85 _public enumerator_ `BadGateway = 502` — the server, while acting as a gateway or proxy, received an invalid response from the upstream server it accessed in attempting to fulfill the request.
- L87 _public enumerator_ `ServiceUnavail = 503` — the service is temporarily overloaded.
- L89 _public enumerator_ `GatewayTimeout = 504` — the request was timed out waiting for a gateway.
- L91 _public enumerator_ `VersionNotSup = 505` — the server does not support, or refuses to support, the http protocol version that was used in the request message.

### `Source/Runtime/Online/HTTPServer/Public/HttpServerHttpVersion.h` (Public)


#### enum `HttpVersion::EHttpServerHttpVersion`  
`enum class EHttpServerHttpVersion : uint8`  
_L8-13_
- L10 _public enumerator_ `HTTP_VERSION_UNKNOWN`
- L11 _public enumerator_ `HTTP_VERSION_1_0`
- L12 _public enumerator_ `HTTP_VERSION_1_1`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace HttpVersion`
- L15 _function_ `static bool FromString(const FString& HttpVersionStr, EHttpServerHttpVersion& OutHttpVersion)` (scope `HttpVersion`)
- L35 _function_ `static FString ToString(EHttpServerHttpVersion& InHttpVersion)` (scope `HttpVersion`)

### `Source/Runtime/Online/HTTPServer/Public/HttpServerModule.h` (Public)


#### class `FHttpServerModule`  
`class FHttpServerModule : public IModuleInterface ,public FTSTickerObjectBase`  
_L24-102_
- inherits: `IModuleInterface,FTSTickerObjectBase`
- desc: Module for HtttpServer Implementation
- L30 _public prototype_ `FHttpServerModule();`
- L31 _public prototype_ `~FHttpServerModule();`
- L38 _public prototype_ `static bool IsAvailable();` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L46 _public prototype_ `static FHttpServerModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L55 _public prototype_ `TSharedPtr<IHttpRouter> GetHttpRouter(uint32 Port, bool bFailOnBindFailure = false);` — Per-port-binding access to an http router @param  Port The listener's bound port @param  bFailOnBindFailure if true, return nullptr if we fail to bind/listen on the given port @return An IHttpRouter instance that can be leveraged to respond to HTTP requests
- L63 _public prototype_ `bool Tick(float DeltaTime) override;` — FTSTicker callback @param DeltaTime  The time in seconds since the last tick @return           false if no longer needs ticking, true otherwise
- L68 _public prototype_ `void StartAllListeners();` — Starts all listeners
- L73 _public prototype_ `void StopAllListeners();` — Stops all listeners
- L80 _public prototype_ `bool HasPendingListeners() const;` — Determines if any listeners are pending operations @return true if there are pending listeners, false otherwise
- L88 _public prototype_ `virtual void StartupModule() override;` — Called when voice module is loaded Initialize platform specific parts of template handling
- L94 _public prototype_ `virtual void ShutdownModule() override;` — Called when voice module is unloaded Shutdown platform specific parts of template handling
- L99 _private member_ `static FHttpServerModule* Singleton;` — Singleton Instance
- L101 _private member_ `FHttpServerModuleImpl* Impl;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpServerModule, Log, All);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpServerModule, Log, All);`

### `Source/Runtime/Online/HTTPServer/Public/HttpServerRequest.h` (Public)


#### enum `EHttpServerRequestVerbs`  
`enum class EHttpServerRequestVerbs : uint16`  
_L10-22_
- L12 _public enumerator_ `VERB_NONE = 0`
- L13 _public enumerator_ `VERB_GET = 1 << 0`
- L14 _public enumerator_ `VERB_POST = 1 << 1`
- L15 _public enumerator_ `VERB_PUT = 1 << 2`
- L16 _public enumerator_ `VERB_PATCH = 1 << 3`
- L17 _public enumerator_ `VERB_DELETE = 1 << 4`
- L18 _public enumerator_ `VERB_OPTIONS = 1 << 5`
- L19 _public enumerator_ `VERB_HEAD = 1 << 6`
- L20 _public enumerator_ `VERB_TRACE = 1 << 7`
- L21 _public enumerator_ `VERB_CONNECT = 1 << 8`

#### struct `FHttpServerRequest`  
`struct FHttpServerRequest`  
_L26-60_
- L31 _public function_ `FHttpServerRequest()` — Constructor
- L34 _public member_ `TSharedPtr<FInternetAddr> PeerAddress;` — The IP address of the peer that initiated the request.
- L37 _public member_ `FHttpPath FullPath;` — The full HTTP path as originally received
- L40 _public member_ `FHttpPath RelativePath;` — The handler-route-relative HTTP path
- L43 _public member_ `EHttpServerRequestVerbs Verb = EHttpServerRequestVerbs::VERB_NONE;` — The HTTP-compliant verb
- L46 _public member_ `HttpVersion::EHttpServerHttpVersion HttpVersion = HttpVersion::EHttpServerHttpVersion::HTTP_VERSION_1_1;` — The request HTTP protocol version
- L49 _public member_ `TMap<FString, TArray<FString>> Headers;` — The HTTP headers
- L52 _public member_ `TMap<FString, FString> QueryParams;` — The query parameters
- L55 _public member_ `TMap<FString, FString> PathParams;` — The path parameters
- L58 _public member_ `TArray<uint8> Body;` — The raw body contents

#### Free symbols / members of external scopes

- L24 _prototype_ `ENUM_CLASS_FLAGS(EHttpServerRequestVerbs);`

### `Source/Runtime/Online/HTTPServer/Public/HttpServerResponse.h` (Public)


#### enum `EHttpServerResponseFlags`  
`enum class EHttpServerResponseFlags : uint8`  
_L19-42_
- L21 _public enumerator_ `None = 0`
- L24 _public enumerator_ `MultipleWriteStream = 1 << 0` — Used to indicate the response body will consist of multiple writes before another read/close (possibly an SSE stream)
- L27 _public enumerator_ `HasAdditionalWrites = 1 << 1` — Used to indicate if additional stream writes are expected, used with MultipleWriteStream
- L30 _public enumerator_ `SkipHeaderWrite = 1 << 2` — Used to indicate if the next response write should skip including headers, used with MultipleWriteStream
- L41 _public enumerator_ `CloseAfterWrite = 1 << 3` — Destroy the connection immediately after this response is written, bypassing the keep-alive return to `AwaitingRead`. Required for streaming responses (`MultipleWriteStream`) that emit neither `Content-Length` nor `Transfer-Encoding: chunked` framing: HTTP/1.1 clients fall back to read-to-EOF semantics for unframed bodies, so the socket close is the only end-of-message signal they receive. Without this flag, the socket idles until `FHttpConnection::ConnectionKeepAliveTimeout` (15s) elapses, masking the response delivery. Set on the final write of a streaming sequence.

#### struct `FHttpServerResponse`  
`struct FHttpServerResponse final`  
_L46-152_
- L52 _public function_ `FHttpServerResponse()` — Constructor
- L61 _public function_ `FHttpServerResponse(TArray<uint8>&& InBody) : Body(MoveTemp(InBody))` — Constructor Facilitates in-place body construction @param InBody The r-value body data
- L66 _public member_ `HttpVersion::EHttpServerHttpVersion HttpVersion = HttpVersion::EHttpServerHttpVersion::HTTP_VERSION_UNKNOWN;` — Http protocol version
- L69 _public member_ `EHttpServerResponseCodes Code = EHttpServerResponseCodes::Unknown;` — Http Response Code
- L72 _public member_ `TMap<FString, TArray<FString>> Headers;` — Http Headers
- L75 _public member_ `TArray<uint8> Body;` — Http Body Content
- L78 _public member_ `EHttpServerResponseFlags Flags = EHttpServerResponseFlags::None;` — Response flags
- L86 _public member_ `TSharedPtr<TQueue<TArray<uint8>, EQueueMode::Spsc>> StreamingBodyQueue;` — Optional: streaming body queue. When set, WriteStream will drain this queue chunk-by-chunk in addition to (after) the initial Body content.  Must be an SPSC queue: one producer thread enqueues chunks, the game thread (WriteStream) dequeues. Set bStreamingBodyComplete to true after all chunks have been enqueued.
- L87 _public member_ `TSharedPtr<TAtomic<bool>> StreamingBodyComplete;`
- L98 _public prototype_ `static TUniquePtr<FHttpServerResponse> Create(const FString& Text, const FString& ContentType);` — Creates an FHttpServerResponse from a string @param  Text         The text to serialize @param  ContentType  The HTTP response content type @return              A unique pointer to an initialized response object
- L107 _public prototype_ `static TUniquePtr<FHttpServerResponse> Create(const FUtf8String& Text, const FString& ContentType);` — Creates an FHttpServerResponse from a string @param  Text         The text to serialize @param  ContentType  The HTTP response content type @return              A unique pointer to an initialized response object
- L116 _public prototype_ `static TUniquePtr<FHttpServerResponse> Create(FUtf8String&& Text, const FString& ContentType);` — Creates an FHttpServerResponse from a string @param  Text         The text to serialize @param  ContentType  The HTTP response content type @return              A unique pointer to an initialized response object
- L125 _public prototype_ `static TUniquePtr<FHttpServerResponse> Create(TArray<uint8>&& RawBytes, FString ContentType);` — Creates an FHttpServerResponse from a raw byte buffer @param  RawBytes     The byte buffer to serialize @param  ContentType  The HTTP response content type @return              A unique pointer to an initialized response object
- L134 _public prototype_ `static TUniquePtr<FHttpServerResponse> Create(const TArrayView<uint8>& RawBytes, FString ContentType);` — Creates an FHttpServerResponse from a raw byte buffer @param  RawBytes     The byte buffer view to serialize @param  ContentType  The HTTP response content type @return              A unique pointer to an initialized response object
- L141 _public prototype_ `static TUniquePtr<FHttpServerResponse> Ok();` — Creates an FHttpServerResponse 204 @return A unique pointer to an initialized response object
- L151 _public prototype_ `static TUniquePtr<FHttpServerResponse> Error(EHttpServerResponseCodes ResponseCode, const FString& ErrorCode = TEXT(""), const FString& ErrorMessage = TEXT(""));` — Creates an FHttpServerResponse with the caller-supplied response and error codes @param ResponseCode The HTTP response code @param ErrorCode    The machine-readable error code @param ErrorMessage The contextually descriptive error message @return A unique pointer to an initialized response object

#### Free symbols / members of external scopes

- L44 _prototype_ `ENUM_CLASS_FLAGS(EHttpServerResponseFlags);`

### `Source/Runtime/Online/HTTPServer/Public/IHttpRouter.h` (Public)


#### class `IHttpRouter`  
`class IHttpRouter : public TSharedFromThis<IHttpRouter>`  
_L15-63_
- inherits: `TSharedFromThis<IHttpRouter>`
- L25 _public prototype_ `virtual bool Query(const TSharedPtr<FHttpServerRequest>& Request, const FHttpResultCallback& OnProcessingComplete) = 0;` — Query the router with a request. @param Request the request to route. @param OnComplete the callback called when @return	 An FHttpRouteHandle on success, nullptr otherwise.
- L34 _public prototype_ `virtual FHttpRouteHandle BindRoute(const FHttpPath& HttpPath, const EHttpServerRequestVerbs& HttpVerbs, const FHttpRequestHandler& Handler) = 0;` — Binds the caller-supplied Uri to the caller-supplied handler @param  HttpPath   The respective http path to bind @param  HttpVerbs  The respective HTTP verbs to bind @param  Handler    The caller-defined closure to execute when the binding is invoked @return            An FHttpRouteHandle on success, nullptr otherwise.
- L41 _public prototype_ `virtual void UnbindRoute(const FHttpRouteHandle& RouteHandle) = 0;` — Unbinds the caller-supplied Route @param  RouteHandle The handle to the route to unbind (callers must retain from BindRoute)
- L49 _public prototype_ `virtual FDelegateHandle RegisterRequestPreprocessor(FHttpRequestHandler RequestPreprocessor) = 0;` — Register a request preprocessor. Useful for cases where you want to drop or handle incoming requests before they are dispatched to their respective handler. @param RequestPreprocessor The function called to process the incoming request. @return FDelegateHandle The handle to the delegate, used for unregistering preprocessors.
- L55 _public prototype_ `virtual void UnregisterRequestPreprocessor(const FDelegateHandle& RequestPreprocessorHandle) = 0;` — Unregister a request preprocessor. @param RequestPreprocessorHandle The handle to the preprocessor delegate to unregister.
- L62 _protected prototype_ `virtual ~IHttpRouter();` — Destructor

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnPreprocessHttpRequest, const TSharedPtr<FHttpServerRequest>& , const FHttpResultCallback& );`
- L13 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnPreprocessHttpRequest, const TSharedPtr<FHttpServerRequest>& , const FHttpResultCallback& );`
