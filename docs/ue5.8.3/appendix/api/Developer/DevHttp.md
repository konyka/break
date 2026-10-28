# Developer / DevHttp

- module root: `Source/Developer/DevHttp`
- headers: 2; symbols: 173
- symbol kinds: class=10, enum=5, enumerator=31, function=8, member=35, namespace=17, prototype=61, struct=5, typedef=1
- PrivateDependencyModuleNames: Core, HTTP, SSL
- PublicDependencyModuleNames: XCurl

### `Source/Developer/DevHttp/Internal/Http/HttpClient.h` (Internal)


#### struct `UE::Http::Private::THttpDestroyer`  
`template <typename T> struct THttpDestroyer`  
_L30-39_
- L32 _public function_ `void operator()(void* Object) const`

#### enum `UE::EHttpMethod`  
`enum class EHttpMethod : uint8`  
_L49-56_
- L51 _public enumerator_ `Get`
- L52 _public enumerator_ `Put`
- L53 _public enumerator_ `Post`
- L54 _public enumerator_ `Head`
- L55 _public enumerator_ `Delete`

#### enum `UE::EHttpMediaType`  
`enum class EHttpMediaType : uint8`  
_L61-73_
- L63 _public enumerator_ `Any`
- L64 _public enumerator_ `Binary`
- L65 _public enumerator_ `Text`
- L66 _public enumerator_ `Json`
- L67 _public enumerator_ `Yaml`
- L68 _public enumerator_ `CbObject`
- L69 _public enumerator_ `CbPackage`
- L70 _public enumerator_ `CbPackageOffer`
- L71 _public enumerator_ `CompressedBinary`
- L72 _public enumerator_ `FormUrlEncoded`

#### enum `UE::EHttpVersion`  
`enum class EHttpVersion : uint8`  
_L78-90_
- L81 _public enumerator_ `None = 0` — Determine version automatically.
- L83 _public enumerator_ `V1_0` — Use HTTP/1.0
- L85 _public enumerator_ `V1_1` — Use HTTP/1.1
- L87 _public enumerator_ `V2` — Try HTTP/2 with fallback to HTTP/1.1
- L89 _public enumerator_ `V2Only` — Use HTTP/2

#### enum `UE::EHttpTlsLevel`  
`enum class EHttpTlsLevel : uint8`  
_L92-100_
- L95 _public enumerator_ `None = 0` — Do not use TLS.
- L97 _public enumerator_ `Try` — Try to use TLS and fall back to none.
- L99 _public enumerator_ `All` — Require TLS.

#### enum `UE::EHttpErrorCode`  
`enum class EHttpErrorCode : uint8`  
_L102-120_
- L105 _public enumerator_ `None = 0` — Success.
- L107 _public enumerator_ `Unknown` — Unknown. Check IHttpResponse::GetError().
- L109 _public enumerator_ `Canceled` — Request was canceled.
- L111 _public enumerator_ `ResolveHost` — Failed to resolve the host.
- L113 _public enumerator_ `Connect` — Failed to establish a connection.
- L115 _public enumerator_ `TlsConnect` — Failed to establish a TLS connection.
- L117 _public enumerator_ `TlsPeerVerification` — Failed to verify the certificate of the peer.
- L119 _public enumerator_ `TimedOut` — Failed because the timeout period was exceeded.

#### class `UE::IHttpManager`  
`class IHttpManager`  
_L125-131_
- L128 _public prototype_ `static IHttpManager& Get();`
- L130 _public prototype_ `[[nodiscard]] virtual THttpUniquePtr<IHttpConnectionPool> CreateConnectionPool(const FHttpConnectionPoolParams& Params) = 0;`

#### class `UE::IHttpConnectionPool`  
`class IHttpConnectionPool`  
_L133-142_
- L136 _public prototype_ `[[nodiscard]] virtual THttpUniquePtr<IHttpClient> CreateClient(const FHttpClientParams& Params) = 0;`
- L140 _protected prototype_ `virtual ~IHttpConnectionPool() = default;`
- L141 _protected prototype_ `virtual void Destroy() = 0;`

#### struct `UE::FHttpConnectionPoolParams`  
`struct FHttpConnectionPoolParams final`  
_L144-157_
- L147 _public member_ `uint32 MaxConnections = 0;` — Maximum number of concurrent connections created by the pool. Use 0 for the default limit.
- L150 _public member_ `uint32 MinConnections = 0;` — Minimum number of concurrent connections maintained by the pool for reuse. Use 0 for the default limit.
- L153 _public member_ `uint32 MaxRequestsPerConnection = 0;` — Maximum number of concurrent requests in flight for a connection when multiplexing. Use 0 for the default limit.
- L156 _public member_ `bool bAllowAsync = true;` — Allow requests to send async using the pool. Requests will block on execution when this is disabled.

#### class `UE::IHttpClient`  
`class IHttpClient`  
_L159-175_
- L169 _public prototype_ `[[nodiscard]] virtual THttpUniquePtr<IHttpRequest> TryCreateRequest(const FHttpRequestParams& Params) = 0;` — Try to create a request. The request is counted against the maximum request count as soon as it is created. Returns null when the maximum request count has been reached. Retry after destroying a request.
- L173 _protected prototype_ `virtual ~IHttpClient() = default;`
- L174 _protected prototype_ `virtual void Destroy() = 0;`

#### struct `UE::FHttpClientParams`  
`struct FHttpClientParams final`  
_L177-231_
- L180 _public member_ `TFunction<void()> OnDestroyRequest;` — Invoked whenever a request from this client is destroyed. This may be used to retry creating a request.
- L183 _public member_ `uint32 MaxRequests = 0;` — Maximum number of concurrent requests created by the client. Use 0 for the default limit.
- L186 _public member_ `uint32 MinRequests = 0;` — Minimum number of concurrent requests maintained by the client for reuse. Use 0 for the default limit.
- L189 _public member_ `uint32 DnsCacheTimeout = 60;` — Domain name cache timeout in seconds. Use 0 to disable the cache.
- L192 _public member_ `uint32 ConnectTimeoutMs = 0;` — Connection timeout in milliseconds. Use 0 for the default timeout.
- L195 _public member_ `uint32 TotalTimeoutMs = 0;` — Total timeout in milliseconds. Use 0 for no timeout.
- L198 _public member_ `uint32 LowSpeedLimit = 0;` — Average transfer speed in bytes/s below which a request will abort. Use 0 to disable.
- L201 _public member_ `uint32 LowSpeedTime = 0;` — Time in seconds after which a request will abort if it stays below LowSpeedLimit. Use 0 to disable.
- L204 _public member_ `EHttpVersion Version = EHttpVersion::None;` — HTTP version to use for requests created by the client.
- L207 _public member_ `EHttpTlsLevel TlsLevel = EHttpTlsLevel::None;` — Level of TLS to use for requests created by the client.
- L210 _public member_ `bool bFollowRedirects : 1;` — Follow redirects in responses automatically.
- L212 _public member_ `bool bFollow301Post : 1;` — Follow redirects of the corresponding status code without rewriting POST to GET.
- L213 _public member_ `bool bFollow302Post : 1;`
- L214 _public member_ `bool bFollow303Post : 1;`
- L217 _public member_ `bool bBypassProxy : 1;` — Avoid use of configured proxy on the client.
- L220 _public member_ `bool bVerbose : 1;` — Verbose logging for requests created by the client.
- L222 _public function_ `inline FHttpClientParams() : bFollowRedirects(false) , bFollow301Post(false) , bFollow302Post(false) , bFollow303Post(false) , bBypassProxy(false) , bVerbose(false)`

#### class `UE::IHttpRequest`  
`class IHttpRequest`  
_L233-294_
- L241 _public prototype_ `virtual void Reset() = 0;` — Reset the request to an empty state equivalent to when it was created. The request must be idle to be reset, which means any associated response must have completed.
- L244 _public prototype_ `virtual void SetUri(FAnsiStringView Uri) = 0;` — Set the URI used for the request, including the scheme and authority.
- L247 _public prototype_ `virtual void SetUnixSocketPath(FAnsiStringView SocketPath) = 0;` — Set a Unix socket path that should be used for sending requests
- L250 _public prototype_ `virtual void SetMethod(EHttpMethod Method) = 0;` — Set the method used for the request. Defaults to GET.
- L257 _public prototype_ `virtual void SetBody(const FCompositeBuffer& Body) = 0;` — Set the body for PUT and POST requests. Body must be owned or otherwise remain valid until the request is complete.
- L260 _public prototype_ `void SetContentType(EHttpMediaType Type, FAnsiStringView Param = {});` — Set the Content-Type header with a known media type. Use AddHeader() for other types.
- L263 _public prototype_ `void AddAcceptType(EHttpMediaType Type, float Weight = 1.0);` — Add an Accept header with a known media type. Use AddHeader() for other types.
- L266 _public prototype_ `virtual void AddHeader(FAnsiStringView Name, FAnsiStringView Value) = 0;` — Add the header. An empty value removes the header.
- L276 _public prototype_ `virtual void Send(IHttpReceiver* Receiver, THttpUniquePtr<IHttpResponse>& OutResponse) = 0;` — Send the request on the client that it was created from, and wait for it to complete before returning. Request must be idle to send, which means any previous response must be complete. Receiver must remain valid until OnComplete is called or until it returns another receiver to be used for subsequent events.
- L288 _public prototype_ `virtual void SendAsync(IHttpReceiver* Receiver, THttpUniquePtr<IHttpResponse>& OutResponse) = 0;` — Asynchronously send the request on the client that it was created from. Request must be idle to send, which means any previous response must be complete. Receiver must remain valid until OnComplete is called or until it returns another receiver to be used for subsequent events. Response must be kept alive until OnComplete is called. Cancel to complete immediately.
- L292 _protected prototype_ `virtual ~IHttpRequest() = default;`
- L293 _protected prototype_ `virtual void Destroy() = 0;`

#### struct `UE::FHttpRequestParams`  
`struct FHttpRequestParams final`  
_L296-300_
- L299 _public member_ `bool bIgnoreMaxRequests = false;` — Whether to force creation of the request even if it would exceed the configured maximum.

#### class `UE::IHttpResponseMonitor`  
`class IHttpResponseMonitor`  
_L302-316_
- L306 _public prototype_ `virtual void Cancel() = 0;` — Cancels the request associated with this response.
- L309 _public prototype_ `virtual void Wait() const = 0;` — Waits for the request associated with this response to be complete.
- L312 _public prototype_ `[[nodiscard]] virtual bool Poll() const = 0;` — Returns true if the request associated with this response is complete, and false otherwise.
- L314 _public prototype_ `virtual void AddRef() const = 0;`
- L315 _public prototype_ `virtual void Release() const = 0;`

#### class `UE::IHttpResponse`  
`class IHttpResponse`  
_L318-381_
- L322 _public prototype_ `[[nodiscard]] virtual TRefCountPtr<IHttpResponseMonitor> GetMonitor() = 0;` — Returns a monitor for the response that can poll, wait, or cancel it.
- L325 _public prototype_ `virtual void Cancel() = 0;` — Cancels the request associated with this response.
- L328 _public prototype_ `virtual void Wait() const = 0;` — Waits for the request associated with this response to be complete.
- L331 _public prototype_ `[[nodiscard]] virtual bool Poll() const = 0;` — Returns true if the request associated with this response is complete, and false otherwise.
- L334 _public prototype_ `[[nodiscard]] virtual FAnsiStringView GetUri() const = 0;` — Get the URI used for the request associated with this response. Always available.
- L337 _public prototype_ `[[nodiscard]] virtual EHttpMethod GetMethod() const = 0;` — Get the method used for the request associated with this response. Always available.
- L345 _public prototype_ `[[nodiscard]] virtual int32 GetStatusCode() const = 0;` — Returns the status code of the response. Available once the response status has been received. The return value is negative until the response status has been received. The return value is 0 if an error occurred. See GetError().
- L348 _public prototype_ `[[nodiscard]] virtual EHttpErrorCode GetErrorCode() const = 0;` — Returns the error code from the HTTP stack. Available when the response is complete.
- L351 _public prototype_ `[[nodiscard]] virtual FAnsiStringView GetError() const = 0;` — Returns the optional error message from the HTTP stack. Available when the status code is 0.
- L354 _public prototype_ `[[nodiscard]] virtual const FHttpResponseStats& GetStats() const = 0;` — Returns information about the request such as size, rate, and duration. Available when complete.
- L357 _public prototype_ `[[nodiscard]] virtual TConstArrayView<FAnsiStringView> GetAllHeaders() const = 0;` — Returns every header in the response. Available once OnHeaders() has been invoked.
- L360 _public prototype_ `[[nodiscard]] FAnsiStringView GetHeader(FAnsiStringView Name) const;` — Returns the value of the first header matching the name, or empty if there was no matching header.
- L367 _public prototype_ `[[nodiscard]] int32 GetHeaders(FAnsiStringView Name, TArrayView<FAnsiStringView> OutValues) const;` — Fills the array of header values and returns the total number of headers matching the name. The return value can be greater than the array size if there are more matching headers than the array can hold.
- L370 _public prototype_ `[[nodiscard]] EHttpMediaType GetContentType() const;` — Returns the content type of the response, or Any if there was no matching header.
- L373 _public prototype_ `[[nodiscard]] uint64 GetContentLength() const;` — Returns the content length of the response, or MAX_uint64 if there was no matching header.
- L377 _protected prototype_ `virtual ~IHttpResponse() = default;`
- L380 _protected prototype_ `virtual void Destroy() = 0;` — Cancel() if not yet invoking OnComplete(), and then Release().

#### struct `UE::FHttpResponseStats`  
`struct FHttpResponseStats final`  
_L386-415_
- L389 _public member_ `uint64 SendSize = 0;` — Total size of data sent to the server, in bytes.
- L391 _public member_ `uint64 RecvSize = 0;` — Total size of data received from the server, in bytes.
- L393 _public member_ `uint64 SendRate = 0;` — Average rate at which data was sent to the server, in bytes/s.
- L395 _public member_ `uint64 RecvRate = 0;` — Average rate at which data was received from the server, in bytes/s.
- L398 _public member_ `double NameResolveTime = 0.0;` — Time from the start of the request until the name was resolved, in seconds.
- L400 _public member_ `double ConnectTime = 0.0;` — Time from the start of the request until the connection was established, in seconds.
- L402 _public member_ `double TlsConnectTime = 0.0;` — Time from the start of the request until the TLS connection was complete, in seconds.
- L404 _public member_ `double PreTransferTime = 0.0;` — Time from the start of the request until the request was sent but before the first byte was received, in seconds.
- L406 _public member_ `double StartTransferTime = 0.0;` — Time from the start of the request until the first byte was received, in seconds.
- L408 _public member_ `double TotalTime = 0.0;` — Time from the start of the request until response was complete, in seconds.
- L411 _public function_ `double GetLatency() const` — Time from when the request was sent until the first byte was received, in seconds. If no byte has been received, latency is 0.

#### class `UE::IHttpReceiver`  
`class IHttpReceiver`  
_L423-462_
- desc: Interface to receive the headers and body of the response. Functions on this interface must be implemented to do the minimal work possible, because their execution can block other requests from being processed.
- L426 _public prototype_ `virtual ~IHttpReceiver() = default;`
- L433 _public function_ `virtual IHttpReceiver* OnCreate(IHttpResponse& Response)` — Invoked when the response has been created, before it begins executing. Returns the receiver to use for the next part of the response and can return itself.
- L440 _public function_ `virtual IHttpReceiver* OnHeaders(IHttpResponse& Response)` — Invoked when every header has been received for the response. Returns the receiver to use for the next part of the response and can return itself.
- L450 _public function_ `virtual IHttpReceiver* OnBody(IHttpResponse& Response, FMemoryView& Data)` — Invoked when a part of the body has been received. The Data parameter can be reassigned to point to the tail of the view that is not consumed by this receiver, and will be passed to the receiver that is returned. Returns the receiver to use for the next part of the response and can return itself.
- L461 _public function_ `virtual IHttpReceiver* OnComplete(IHttpResponse& Response)` — Invoked when the response is complete. Always invoked exactly once for each response. Check the status code to detect errors. Can retry using the same request. It is valid for implementations of this function to delete the response. Returns the next receiver to handle OnComplete, or null if there are no others.

#### class `UE::FHttpByteArrayReceiver`  
`class FHttpByteArrayReceiver final : public IHttpReceiver`  
_L466-477_
- inherits: `IHttpReceiver`
- L469 _public prototype_ `explicit FHttpByteArrayReceiver(TArray64<uint8>& OutArray, IHttpReceiver* Next = nullptr);`
- L471 _public prototype_ `IHttpReceiver* OnBody(IHttpResponse& Response, FMemoryView& Data) final;`
- L472 _public function_ `IHttpReceiver* OnComplete(IHttpResponse& Response) final`
- L475 _private member_ `TArray64<uint8>& Array;`
- L476 _private member_ `IHttpReceiver* Next;`

#### class `UE::FHttpRequestQueue`  
`class FHttpRequestQueue final`  
_L482-495_
- desc: Manages a client by letting callers queue to receive a request when one is not immediately available.
- L486 _public prototype_ `FHttpRequestQueue() = default;` — Create a null request queue. Asserts if CreateRequest is called.
- L488 _public prototype_ `FHttpRequestQueue(IHttpConnectionPool& ConnectionPool, const FHttpClientParams& ClientParams);`
- L491 _public prototype_ `[[nodiscard]] THttpUniquePtr<IHttpRequest> CreateRequest(const FHttpRequestParams& Params);` — Blocks until a request can be created on the underlying client.
- L494 _private member_ `TPimplPtr<Http::Private::FHttpRequestQueueData> Data;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UE`
- L21 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Http` (scope `UE`)
- L24 _namespace_ `namespace Private` (scope `UE::Http`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Http` (scope `UE`)
- L26 _namespace_ `namespace Private` (scope `UE::Http`)
- L43 _namespace_ `namespace UE`
- L47 _typedef_ `template <typename Type, typename BaseType = Type> using THttpUniquePtr = TUniquePtr<Type, Http::Private::THttpDestroyer<BaseType>>;` (scope `UE`)
- L58 _prototype_ `FAnsiStringView LexToString(EHttpMethod Method);` (scope `UE`)
- L59 _prototype_ `bool TryLexFromString(EHttpMethod& OutMethod, FAnsiStringView View);` (scope `UE`)
- L75 _prototype_ `FAnsiStringView LexToString(EHttpMediaType MediaType);` (scope `UE`)
- L76 _prototype_ `bool TryLexFromString(EHttpMediaType& OutMediaType, FAnsiStringView View);` (scope `UE`)
- L122 _prototype_ `FAnsiStringView LexToString(EHttpErrorCode ErrorCode);` (scope `UE`)
- L123 _prototype_ `bool TryLexFromString(EHttpErrorCode& OutErrorCode, FAnsiStringView View);` (scope `UE`)
- L384 _prototype_ `FStringBuilderBase& operator<<(FStringBuilderBase& Builder, const IHttpResponse& Response);` (scope `UE`) — Appends the URI, method, status code, and optional error from the response to the builder.

### `Source/Developer/DevHttp/Internal/Http/HttpHostBuilder.h` (Internal)


#### class `UE::FHttpHostBuilder`  
`class FHttpHostBuilder`  
_L13-31_
- L17 _public prototype_ `void AddFromString(FAnsiStringView HostList);` — accept a semicolon seperated list of hosts to pick from
- L18 _public prototype_ `void AddFromString(FStringView HostList);`
- L21 _public prototype_ `void AddFromEndpoint(FAnsiStringView HostUrl, FAnsiStringView AccessToken);` — a url that is expected to host a /status/peers endpoint with endpoints we should attempt to use
- L24 _public prototype_ `FString GetHostCandidatesString() const;` — produces a string of all the host candidates used for display purposes
- L26 _public prototype_ `bool ResolveHost(double WarningTimeoutSeconds, double TimeoutSeconds, FAnsiStringBuilderBase& OutHost, double& OutLatency);`
- L28 _private prototype_ `static bool BenchmarkHostList(TConstArrayView<FString> HostCandidates, double WarningTimeoutSeconds, double TimeoutSeconds, FAnsiStringBuilderBase& OutHost, double& OutLatency);`
- L30 _private member_ `TArray<FString> HostCandidates;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
