# Runtime / HTTP

- module root: `Source/Runtime/Online/HTTP`
- headers: 49; symbols: 1442
- symbol kinds: class=53, delegate=7, enum=10, enumerator=70, externvar=4, function=72, macro=9, member=329, namespace=7, prototype=812, struct=19, typedef=48, variable=2
- PrivateDependencyModuleNames: BackgroundHTTPFileHash, BackgroundHttpIOS, EventLoop, SSL, Sockets
- PublicDependencyModuleNames: Core, XCurl

### `Source/Runtime/Online/HTTP/Internal/WinHttp/Support/WinHttpConnection.h` (Internal)


#### class `IWinHttpConnection`  
`class IWinHttpConnection : public TSharedFromThis<IWinHttpConnection, ESPMode::ThreadSafe>`  
_L13-86_
- inherits: `TSharedFromThis<IWinHttpConnection,ESPMode::ThreadSafe>`
- L17 _public prototype_ `virtual ~IWinHttpConnection() = default;`
- L26 _public prototype_ `virtual bool IsValid() const = 0;` — [Call on Any Thread] Is this object available to use? If this is false, StartRequest will always fail. @return True if the connection is valid to use, false if not
- L35 _public prototype_ `virtual const FString& GetRequestUrl() const = 0;` — [Call on Any Thread] Get the request URL for this connection @return A reference to the request URL for this connection
- L44 _public prototype_ `virtual void* GetHandle() = 0;` — [Call on Any Thread in Request Callback] Get the request handle for this connection. This is only safe to call in a callback for this connection. @return The request handle, or nullptr if not available
- L53 _public prototype_ `virtual bool StartRequest() = 0;` — [Call on Main Thread only] Start this connection if possible. No callbacks will be fired if StartRequest does not return true. @return True if the connection was able to start, false if not
- L62 _public prototype_ `virtual bool CancelRequest() = 0;` — [Call on Any Thread] Cancel this connection and start the teardown of any handles owned by this connection @return True if the connection is able to cancel, false if it can't
- L71 _public prototype_ `virtual bool IsComplete() const = 0;` — [Call on Any Thread] Has this connection reached a final state (success or failure)? @return True if the connection has finished, false if it hasn't started or is still processing
- L78 _public prototype_ `virtual void PumpMessages() = 0;` — [Call on Main Thread only] Process and call delegates events that are queued for the main thread
- L85 _public prototype_ `virtual void PumpStates() = 0;` — [Call on Any Thread] Pump the state machine and advance the request's state

#### Free symbols / members of external scopes

- L10 _typedef_ `using HINTERNET = void*;`
- L11 _typedef_ `using LPVOID = void*;`

### `Source/Runtime/Online/HTTP/Internal/WinHttp/Support/WinHttpConnectionHttp.h` (Internal)


#### class `FWinHttpConnectionHttp`  
`class FWinHttpConnectionHttp : public IWinHttpConnection`  
_L28-342_
- inherits: `IWinHttpConnection`
- L32 _public prototype_ `static TSharedPtr<FWinHttpConnectionHttp, ESPMode::ThreadSafe> CreateHttpConnection( FWinHttpSession& Session, const FString& Verb, const FString& Url, const TMap<FString, FString>& Headers, const TSharedPtr<FRequestPayload, ESPMode::ThreadSafe>& Payload);`
- L39 _public prototype_ `virtual ~FWinHttpConnectionHttp();`
- L40 _public prototype_ `FWinHttpConnectionHttp(const FWinHttpConnectionHttp& Other) = delete;`
- L41 _public prototype_ `FWinHttpConnectionHttp(FWinHttpConnectionHttp&& Other) = delete;`
- L42 _public prototype_ `FWinHttpConnectionHttp& operator=(const FWinHttpConnectionHttp& Other) = delete;`
- L43 _public prototype_ `FWinHttpConnectionHttp& operator=(FWinHttpConnectionHttp&& Other) = delete;`
- L46 _public prototype_ `virtual bool IsValid() const override;`
- L47 _public prototype_ `virtual const FString& GetRequestUrl() const override;`
- L48 _public prototype_ `virtual void* GetHandle() override;`
- L49 _public prototype_ `virtual bool StartRequest() override;`
- L50 _public prototype_ `virtual bool CancelRequest() override;`
- L51 _public prototype_ `virtual bool IsComplete() const override;`
- L52 _public prototype_ `virtual void PumpMessages() override;`
- L53 _public prototype_ `virtual void PumpStates() override;`
- L57 _public function_ `EHttpResponseCodes::Type GetResponseCode() const` — Provides the current known response code.
- L62 _public function_ `TArray<uint8>& GetLastChunk()` — Gets the last chunk that is ready for processing on the game thread. The caller should either use MoveTemp or call Reset after retrieving the data.
- L64 _public function_ `uint64 GetResponseContentLength() const` — Provides the current known response content length.
- L66 _public function_ `const TMap<FString, FString>& GetHeadersReceived() const` — Provides the current known headers received.
- L75 _public prototype_ `void SetDataTransferredHandler(FWinHttpConnectionHttpOnDataTransferred&& Handler);` — Bind a handler that is called each tick we receive or send data @param Handler The Handler to call when we receive or send data
- L81 _public prototype_ `void SetHeaderReceivedHandler(FWinHttpConnectionHttpOnHeaderReceived&& Handler);` — Bind a handler that is called each tick we receive a new header @param Handler The Handler to call when we receive a new header
- L87 _public prototype_ `void SetRequestCompletedHandler(FWinHttpConnectionHttpOnRequestComplete&& Handler);` — Bind a handler that is called when the request completes @param Handler The Handler to call when the request completes
- L90 _protected prototype_ `FWinHttpConnectionHttp( FWinHttpSession& Session, const FString& Url, const FString& Verb, const bool bIsSecure, const FString& Domain, const TOptional<uint16> Port, const FString& PathAndQuery, const TMap<FString, FString>& Headers, const TSharedPtr<FRequestPayload, ESPMode::ThreadSafe>& Payload);`
- L110 _protected prototype_ `bool SetHeaders(const TMap<FString, FString>& Headers);` — Add to our request's headers. These new headers will be added to the existing headers set, and will replace any values that already exist with the same header name. @param Headers Key/Value Map of headers to add to our request @return True if we could set the headers, false otherwise
- L120 _protected prototype_ `bool SetHeader(const FString& Key, const FString& Value);` — Add to our request's headers. Theis new header will be added to the existing headers set, and will replace any values that already exist with the same header name. @param Key Key of header to add to our request @param Value Value of header to set on our request @return True if we could set the header, false otherwise
- L127 _protected prototype_ `bool SetPayload(const TSharedRef<FRequestPayload, ESPMode::ThreadSafe>& NewPayload);` — Set the payload object of our request. This may only be called before StartRequest is called. @param NewPayload the Payload object to set (it should not be modified during the request!) @return True if we were able to set the payload, false otherwise
- L136 _protected prototype_ `bool SendRequest();` — Reset our data sent and fire off a send request again @return True if we could start the request, or false otherwise
- L142 _protected prototype_ `void IncrementSentByteCounts(const uint64 AmountSent);` — Increment our bytes-sent counters @param AmountSent The amount of bytes to increment our counters by
- L148 _protected prototype_ `void IncrementReceivedByteCounts(const uint64 AmountReceived);` — Increment our bytes-received counters @param AmountReceived The amount of bytes to increment our counters by
- L154 _protected prototype_ `bool HasRequestBodyToSend() const;` — Check if we have more data to send @return True if we have data to send, or false otherwise
- L160 _protected prototype_ `bool SendAdditionalRequestBody();` — Gives WinHttp the next check of data. @param True if we asked WinHttp to send the data, or false if we could not send the next chunk
- L169 _protected prototype_ `bool RequestResponse();` — Tell WinHttp that we are ready for the response of our request @return True if the action completed successfully, false otherwise
- L175 _protected prototype_ `bool ProcessResponseHeaders();` — Read our HTTP response headers and store the results @return True if the action completed successfully, false otherwise
- L181 _protected prototype_ `bool RequestNextResponseBodyChunkSize();` — Ask WinHttp to asynchronously tell us how large the next chunk will be. If it's 0, we're done. @return True if the action completed successfully, false otherwise
- L187 _protected prototype_ `bool RequestNextResponseBodyChunkData();` — Ask WinHttp to asynchronously write the next chunk directly into our response object @return True if the action completed successfully, false otherwise
- L192 _protected prototype_ `virtual bool FinishRequest(const EHttpRequestStatus::Type FinalState);` — Set our request as finished and set state to the specified state. This also releases the WinHttp handles.
- L197 _protected prototype_ `virtual void HandleConnectedToServer(const wchar_t* ServerIP);` — Handles storing the server's IP Address if needed
- L199 _protected prototype_ `void HandleSendingRequest();` — Handles validating request now that we have server information (certificates, etc)
- L201 _protected prototype_ `void HandleWriteComplete(const uint64 NumBytesSent);` — Handles SOMETHING not sure yet
- L203 _protected prototype_ `void HandleSendRequestComplete();` — Handles completing the request so we may read the headers and body of the response
- L205 _protected prototype_ `virtual void HandleHeadersAvailable();` — Handles reading the response headers
- L207 _protected prototype_ `void HandleDataAvailable(const uint64 NumBytesAvailable);` — Handles writing the http response body to our response body
- L209 _protected prototype_ `void HandleReadComplete(const uint64 NumBytesRead);` — Handles querying the next chunk of our http response body
- L211 _protected prototype_ `void HandleRequestError(const uint32 ErrorApiId, const uint32 ErrorCode);` — Handles shutting down the request when there was an error
- L213 _protected prototype_ `virtual void HandleHandleClosing();` — Handles our request object closing, ending this request
- L224 _private prototype_ `void HandleHttpStatusCallback(HINTERNET ResourceHandle, EWinHttpCallbackStatus Status, void* StatusInformation, uint32 StatusInformationLength);` — Handle receiving HTTP status callbacks from WinHttp @param ResourceHandle The handle of the resource which generated this Status @param InternetStatus The event that is being triggered @param StatusInformation Pointer to optional data for this event, if there is any @param StatusInformationLength The length of data available to read in StatusInformation or 0 if not used
- L230 _private prototype_ `void ReleasePayloadData();` — Reset both PayloadBuffer and Payload when we don't need them anymore, releasing the memory
- L234 _protected member_ `mutable FCriticalSection SyncObject;` — Critical section used to synchronize access to the below properties across multiple threads
- L238 _protected member_ `FWinHttpHandle ConnectionHandle;` — Handle to our connection object (do not reuse across requests!)
- L240 _protected member_ `FWinHttpHandle RequestHandle;` — Handle to our request object (do not reuse across requests!)
- L242 _protected member_ `TSharedPtr<FWinHttpConnectionHttp, ESPMode::ThreadSafe> KeepAlive;` — Keep-alive for this object, to ensure it does not destruct while a request is in progress
- L245 _protected member_ `TOptional<EHttpRequestStatus::Type> FinalState;` — The current request state
- L247 _protected member_ `bool bConnectedToServer = false;` — Has this request successfully connected to the server?
- L249 _protected member_ `bool bRequestCancelled = false;` — Has this request been cancelled?
- L251 _protected member_ `std::atomic<bool> bHasPendingDelegate{false};` — If true, we have a pending event that needs to be broadcast on the game thread
- L254 _private member_ `FString RequestUrl;`
- L298 _private member_ `EState CurrentAction = EState::WaitToStart;`
- L303 _private member_ `TSharedPtr<FRequestPayload, ESPMode::ThreadSafe> Payload;` — Payload body
- L305 _private member_ `uint64 NumBytesSuccessfullySent = 0;` — Amount of bytes from payload that has been sent successfully
- L307 _private member_ `TArray<uint8> PayloadBuffer;` — Data from the payload currently trying to be written
- L312 _private member_ `EHttpResponseCodes::Type ResponseCode = EHttpResponseCodes::Unknown;` — The response code received from our request
- L314 _private member_ `TMap<FString, FString> HeadersReceived;` — The headers we received from our request
- L316 _private member_ `TArray<uint8> CurrentChunk;` — The current chunk being built in the WinHTTP thread. Always access within a critical section.
- L318 _private member_ `TArray<uint8> GameThreadChunk;` — The current chunk being built for consumption on the game thread. Only access on the game thread.
- L320 _private member_ `uint64 ResponseContentLength = 0;` — The content length from the response headers, or 0.
- L322 _private member_ `uint64 BytesWrittenToGameThreadChunk = 0;`
- L324 _private member_ `TOptional<uint64> ResponseBytesAvailable;` — The amount of bytes that are available to read from WinHttpReadData now
- L329 _private member_ `FWinHttpConnectionHttpOnDataTransferred OnDataTransferredHandler;` — Called on the game thread during tick if we have sent or received data since last tick
- L331 _private member_ `TOptional<uint64> BytesToReportSent;` — Data to report to the game thread about how many bytes have been sent since last tick (not total received)
- L333 _private member_ `TOptional<uint64> BytesToReportReceived;` — Data to report to the game thread about how many bytes have been received since last tick (not total received)
- L336 _private member_ `FWinHttpConnectionHttpOnHeaderReceived OnHeaderReceivedHandler;` — Called on the game thread during tick if we have received header data since last tick
- L338 _private member_ `TArray<FString> HeaderKeysToReportReceived;` — List of headers we have received that we haven't told the game thread about yet
- L341 _private member_ `FWinHttpConnectionHttpOnRequestComplete OnRequestCompleteHandler;` — Called on the game thread if the request has completed since last tick

#### enum `FWinHttpConnectionHttp::EState`  
`enum class EState : uint8`  
_L256-296_
- L261 _public enumerator_ `WaitToStart` — We have not started the request
- L266 _public enumerator_ `SendRequest` — Send our request (or resend it due to redirect to a different host)
- L268 _public enumerator_ `WaitForSendComplete` — Waiting for our request headers and/or body to be completely written to the connection
- L270 _public enumerator_ `SendAdditionalRequestBody` — Send an additional chunk of request body
- L275 _public enumerator_ `RequestResponse` — Request the response now that we've finished writing our request
- L277 _public enumerator_ `WaitForResponseHeaders` — Wait for the response headers to be received from the server
- L279 _public enumerator_ `ProcessResponseHeaders` — Read values from our response headers
- L284 _public enumerator_ `RequestNextResponseBodyChunkSize` — Request the size of the next chunk of our response body
- L286 _public enumerator_ `WaitForNextResponseBodyChunkSize` — Wait for a size of the next chunk from the response body
- L288 _public enumerator_ `RequestNextResponseBodyChunkData` — Request the data for the next chunk from the response body to written to our buffer
- L290 _public enumerator_ `WaitForNextResponseBodyChunkData` — Waiting for data from the next chunk to be written to our buffer
- L295 _public enumerator_ `Finished` — We are done

#### Free symbols / members of external scopes

- L22 _typedef_ `using FStringKeyValueMap = TMap<FString, FString>;`
- L24 _delegate_ `DECLARE_DELEGATE_TwoParams(FWinHttpConnectionHttpOnDataTransferred, int32 , int32 );`
- L24 _prototype_ `DECLARE_DELEGATE_TwoParams(FWinHttpConnectionHttpOnDataTransferred, int32 , int32 );`
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FWinHttpConnectionHttpOnHeaderReceived, const FString& , const FString& );`
- L25 _prototype_ `DECLARE_DELEGATE_TwoParams(FWinHttpConnectionHttpOnHeaderReceived, const FString& , const FString& );`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FWinHttpConnectionHttpOnRequestComplete, EHttpRequestStatus::Type );`
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FWinHttpConnectionHttpOnRequestComplete, EHttpRequestStatus::Type );`

### `Source/Runtime/Online/HTTP/Internal/WinHttp/Support/WinHttpErrorHelper.h` (Internal)


#### class `FWinHttpErrorHelper`  
`class FWinHttpErrorHelper`  
_L9-113_
- L17 _public prototype_ `static void LogWinHttpOpenFailure(const uint32 ErrorCode);` — Log that an WinHttpOpen call failed with the specified ErrorCode @param ErrorCode The error that occured
- L24 _public prototype_ `static void LogWinHttpCloseHandleFailure(const uint32 ErrorCode);` — Log that an WinHttpCloseHandle call failed with the specified ErrorCode @param ErrorCode The error that occured
- L31 _public prototype_ `static void LogWinHttpSetTimeoutsFailure(const uint32 ErrorCode);` — Log that an WinHttpSetTimeouts call failed with the specified ErrorCode @param ErrorCode The error that occured
- L38 _public prototype_ `static void LogWinHttpConnectFailure(const uint32 ErrorCode);` — Log that an WinHttpConnect call failed with the specified ErrorCode @param ErrorCode The error that occured
- L45 _public prototype_ `static void LogWinHttpOpenRequestFailure(const uint32 ErrorCode);` — Log that an WinHttpOpenRequest call failed with the specified ErrorCode @param ErrorCode The error that occured
- L52 _public prototype_ `static void LogWinHttpSetOptionFailure(const uint32 ErrorCode);` — Log that an WinHttpSetOption call failed with the specified ErrorCode @param ErrorCode The error that occured
- L59 _public prototype_ `static void LogWinHttpAddRequestHeadersFailure(const uint32 ErrorCode);` — Log that an WinHttpAddRequestHeaders call failed with the specified ErrorCode @param ErrorCode The error that occured
- L66 _public prototype_ `static void LogWinHttpSetStatusCallbackFailure(const uint32 ErrorCode);` — Log that an WinHttpSetStatusCallback call failed with the specified ErrorCode @param ErrorCode The error that occured
- L73 _public prototype_ `static void LogWinHttpSendRequestFailure(const uint32 ErrorCode);` — Log that an WinHttpSendRequest call failed with the specified ErrorCode @param ErrorCode The error that occured
- L80 _public prototype_ `static void LogWinHttpReceiveResponseFailure(const uint32 ErrorCode);` — Log that an WinHttpReceiveResponse call failed with the specified ErrorCode @param ErrorCode The error that occured
- L87 _public prototype_ `static void LogWinHttpQueryHeadersFailure(const uint32 ErrorCode);` — Log that an WinHttpQueryHeaders call failed with the specified ErrorCode @param ErrorCode The error that occured
- L94 _public prototype_ `static void LogWinHttpQueryDataAvailableFailure(const uint32 ErrorCode);` — Log that an WinHttpQueryDataAvailable call failed with the specified ErrorCode @param ErrorCode The error that occured
- L101 _public prototype_ `static void LogWinHttpReadDataFailure(const uint32 ErrorCode);` — Log that an WinHttpReadData call failed with the specified ErrorCode @param ErrorCode The error that occured
- L108 _public prototype_ `static void LogWinHttpWriteDataFailure(const uint32 ErrorCode);` — Log that an WinHttpWriteData call failed with the specified ErrorCode @param ErrorCode The error that occured
- L112 _private prototype_ `FWinHttpErrorHelper() = delete;` — This class should not be instantiated

### `Source/Runtime/Online/HTTP/Internal/WinHttp/Support/WinHttpHandle.h` (Internal)


#### class `FWinHttpHandle`  
`class FWinHttpHandle`  
_L11-74_
- L17 _public prototype_ `FWinHttpHandle() = default;` — Construct an invalid object
- L22 _public prototype_ `explicit FWinHttpHandle(HINTERNET NewHandle);` — Wrap a new HINTERNET Handle
- L27 _public prototype_ `~FWinHttpHandle();` — Destroy any currently held object
- L30 _public prototype_ `FWinHttpHandle(const FWinHttpHandle& Other) = delete;` — Copy/Move constructors
- L31 _public prototype_ `FWinHttpHandle(FWinHttpHandle&& Other);`
- L32 _public prototype_ `FWinHttpHandle& operator=(const FWinHttpHandle& Other) = delete;`
- L33 _public prototype_ `FWinHttpHandle& operator=(FWinHttpHandle&& Other);`
- L41 _public prototype_ `FWinHttpHandle& operator=(HINTERNET NewHandle);` — Wrap a new handle (destroying any previously held object) @param NewHandle The new handle to wrap (must not be wrapped by anything else) @return A reference to this object that now wraps NewHandle
- L46 _public prototype_ `void Reset();` — Destroy our current handle and reset our state to holding nothing
- L53 _public prototype_ `explicit operator bool() const;` — Do we contain a valid handle? @return True if we have a valid handle, false otherwise
- L60 _public prototype_ `bool IsValid() const;` — Do we contain a valid handle? @return True if we have a valid handle, false otherwise
- L67 _public prototype_ `HINTERNET Get() const;` — Get the underlying handle for use @return The HINTERNET handle we're wrapping
- L73 _protected member_ `HINTERNET Handle = nullptr;` — The handle we're wrap (if we have one)

#### Free symbols / members of external scopes

- L9 _typedef_ `using HINTERNET = void*;`

### `Source/Runtime/Online/HTTP/Internal/WinHttp/Support/WinHttpSession.h` (Internal)


#### class `FWinHttpSession`  
`class FWinHttpSession`  
_L14-54_
- L20 _public prototype_ `FWinHttpSession(const uint32 SecurityProtocolFlags, const bool bForceSecureConnections);` — Construct a new WinHttp session with the specified security protocols flags
- L25 _public prototype_ `FWinHttpSession(const FWinHttpSession& Other) = delete;` — FWinHttpSession is move-only
- L26 _public prototype_ `FWinHttpSession(FWinHttpSession&& Other) = default;`
- L27 _public prototype_ `FWinHttpSession& operator=(const FWinHttpSession& Other) = delete;`
- L28 _public prototype_ `FWinHttpSession& operator=(FWinHttpSession&& Other) = default;`
- L33 _public prototype_ `bool IsValid() const;` — Did this session initialize successfully?
- L40 _public prototype_ `HINTERNET Get() const;` — Get the underlying session handle @return the HINTERNET for this session
- L47 _public prototype_ `bool AreOnlySecureConnectionsAllowed() const;` — Are we only allowed to make secure connection requests (HTTPS, etc) @return True if the platform does not allow for insecure messages
- L51 _private member_ `FWinHttpHandle SessionHandle;` — The handle for our session that we are wrapping
- L53 _private member_ `bool bForceSecureConnections = false;` — Should we force connections to be secure?

#### Free symbols / members of external scopes

- L12 _typedef_ `using HINTERNET = void*;`

### `Source/Runtime/Online/HTTP/Internal/WinHttp/Support/WinHttpTypes.h` (Internal)


#### enum `EWinHttpCallbackStatus`  
`enum class EWinHttpCallbackStatus : uint32`  
_L18-47_
- L20 _public enumerator_ `ResolvingName = WINHTTP_CALLBACK_STATUS_RESOLVING_NAME`
- L21 _public enumerator_ `NameResolved = WINHTTP_CALLBACK_STATUS_NAME_RESOLVED`
- L22 _public enumerator_ `ConnectingToServer = WINHTTP_CALLBACK_STATUS_CONNECTING_TO_SERVER`
- L23 _public enumerator_ `ConnectedToServer = WINHTTP_CALLBACK_STATUS_CONNECTED_TO_SERVER`
- L24 _public enumerator_ `SendingRequest = WINHTTP_CALLBACK_STATUS_SENDING_REQUEST`
- L25 _public enumerator_ `RequestSent = WINHTTP_CALLBACK_STATUS_REQUEST_SENT`
- L26 _public enumerator_ `ReceivingResponse = WINHTTP_CALLBACK_STATUS_RECEIVING_RESPONSE`
- L27 _public enumerator_ `ResponseReceived = WINHTTP_CALLBACK_STATUS_RESPONSE_RECEIVED`
- L28 _public enumerator_ `ClosingConnection = WINHTTP_CALLBACK_STATUS_CLOSING_CONNECTION`
- L29 _public enumerator_ `ConnectionClosed = WINHTTP_CALLBACK_STATUS_CONNECTION_CLOSED`
- L30 _public enumerator_ `HandleCreated = WINHTTP_CALLBACK_STATUS_HANDLE_CREATED`
- L31 _public enumerator_ `HandleClosing = WINHTTP_CALLBACK_STATUS_HANDLE_CLOSING`
- L32 _public enumerator_ `DetectingProxy = WINHTTP_CALLBACK_STATUS_DETECTING_PROXY`
- L33 _public enumerator_ `Redirect = WINHTTP_CALLBACK_STATUS_REDIRECT`
- L34 _public enumerator_ `IntermediateResponse = WINHTTP_CALLBACK_STATUS_INTERMEDIATE_RESPONSE`
- L35 _public enumerator_ `SecureFailure = WINHTTP_CALLBACK_STATUS_SECURE_FAILURE`
- L36 _public enumerator_ `HeadersAvailable = WINHTTP_CALLBACK_STATUS_HEADERS_AVAILABLE`
- L37 _public enumerator_ `DataAvailable = WINHTTP_CALLBACK_STATUS_DATA_AVAILABLE`
- L38 _public enumerator_ `ReadComplete = WINHTTP_CALLBACK_STATUS_READ_COMPLETE`
- L39 _public enumerator_ `WriteComplete = WINHTTP_CALLBACK_STATUS_WRITE_COMPLETE`
- L40 _public enumerator_ `RequestError = WINHTTP_CALLBACK_STATUS_REQUEST_ERROR`
- L41 _public enumerator_ `SendRequestComplete = WINHTTP_CALLBACK_STATUS_SENDREQUEST_COMPLETE`
- L42 _public enumerator_ `GetProxyForUrlComplete = WINHTTP_CALLBACK_STATUS_GETPROXYFORURL_COMPLETE`
- L43 _public enumerator_ `CloseComplete = WINHTTP_CALLBACK_STATUS_CLOSE_COMPLETE`
- L44 _public enumerator_ `ShutdownComplete = WINHTTP_CALLBACK_STATUS_SHUTDOWN_COMPLETE`
- L45 _public enumerator_ `SettingsWriteComplete = WINHTTP_CALLBACK_STATUS_SETTINGS_WRITE_COMPLETE`
- L46 _public enumerator_ `SettingsReadComplete = WINHTTP_CALLBACK_STATUS_SETTINGS_READ_COMPLETE`

#### Free symbols / members of external scopes

- L49 _prototype_ `const TCHAR* LexToString(const EWinHttpCallbackStatus Status);`
- L50 _prototype_ `bool IsValidStatus(const EWinHttpCallbackStatus Status);`
- L52 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWinHttp, Log, All);`

### `Source/Runtime/Online/HTTP/Internal/WinHttp/WinHttpHttpManager.h` (Internal)


#### class `FWinHttpHttpManager`  
`class FWinHttpHttpManager : public FTSTickerObjectBase`  
_L16-50_
- inherits: `FTSTickerObjectBase`
- L19 _public prototype_ `static FWinHttpHttpManager* GetManager();`
- L21 _public prototype_ `FWinHttpHttpManager();`
- L22 _public prototype_ `virtual ~FWinHttpHttpManager();`
- L30 _public prototype_ `virtual void QuerySessionForUrl(const FString& Url, FWinHttpQuerySessionComplete&& Delegate) = 0;` — Asynchronously finds an existing WinHttp session for the provided URL, or creates a new one for it. @param Url The URL to find or create a WinHttp session for @param Delegate The delegate that is called with the WinHttp session pointer if successful, or null otherwise
- L40 _public prototype_ `virtual bool ValidateRequestCertificates(IWinHttpConnection& Connection) = 0;` — Validate the provided connection before we start sending our request. NOTE: this is called on multiple threads, and should be written in a way that handles this safely! @param Connection the connection to validate @return True if the request validated successfully, false if not
- L49 _public prototype_ `virtual void ReleaseRequestResources(IWinHttpConnection& Connection) = 0;` — Release any resources that were pinned for this request. NOTE: this is a no-op on Windows builds, but does things on other platforms. @param Connection The connection to release resources for

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FWinHttpQuerySessionComplete, FWinHttpSession* );`
- L12 _prototype_ `DECLARE_DELEGATE_OneParam(FWinHttpQuerySessionComplete, FWinHttpSession* );`

### `Source/Runtime/Online/HTTP/Private/Apple/AppleEventLoopHttpThread.h` (Private)


#### class `FAppleHTTPIOAccess`  
`class FAppleHTTPIOAccess final`  
_L15-31_
- L18 _public function_ `explicit FAppleHTTPIOAccess(TSharedRef<UE::FManualResetEvent> Event) :SharedEvent(MoveTemp(Event))`
- L23 _public function_ `void Notify()`
- L30 _private member_ `TSharedRef<UE::FManualResetEvent> SharedEvent;`

#### class `FAppleHTTPIOManager`  
`class FAppleHTTPIOManager final: public UE::EventLoop::IIOManager`  
_L33-84_
- inherits: `UE::EventLoop::IIOManager`
- L36 _public typedef_ `using FIOAccess = FAppleHTTPIOAccess;`
- L43 _public function_ `FAppleHTTPIOManager(UE::EventLoop::IEventLoop& EventLoop, FParams&& Params) : Event(MakeShared<UE::FManualResetEvent>()) , IOAccess(Event) , Params(MoveTemp(Params))`
- L50 _public prototype_ `virtual ~FAppleHTTPIOManager() = default;`
- L52 _public function_ `virtual bool Init() override`
- L57 _public function_ `virtual void Shutdown() override`
- L61 _public function_ `virtual void Notify() override`
- L66 _public function_ `virtual void Poll(FTimespan WaitTime) override`
- L75 _public function_ `FIOAccess& GetIOAccess()`
- L81 _private member_ `TSharedRef<UE::FManualResetEvent> Event;`
- L82 _private member_ `FIOAccess IOAccess;`
- L83 _private member_ `FParams Params;`

#### struct `FAppleHTTPIOManager::FParams`  
`struct FParams`  
_L38-41_
- L40 _public member_ `TUniqueFunction<void()> ProcessRequests;`

#### class `FAppleEventLoopHttpThread`  
`class FAppleEventLoopHttpThread : public FEventLoopHttpThread`  
_L86-103_
- inherits: `FEventLoopHttpThread`
- L91 _protected prototype_ `virtual bool StartThreadedRequest(FHttpRequestCommon* Request) override;`
- L92 _protected prototype_ `virtual void CompleteThreadedRequest(FHttpRequestCommon* Request) override;`
- L95 _protected prototype_ `virtual void CreateEventLoop() override;`
- L96 _protected prototype_ `virtual void DestroyEventLoop() override;`
- L97 _protected prototype_ `virtual void UpdateEventLoopConfigs() override;`
- L99 _protected prototype_ `virtual UE::EventLoop::IEventLoop* GetEventLoop() override;`
- L100 _protected prototype_ `virtual UE::EventLoop::IEventLoop& GetEventLoopChecked() override;`
- L102 _protected member_ `TOptional<UE::EventLoop::TEventLoop<FAppleHTTPIOManager>> EventLoop;`

### `Source/Runtime/Online/HTTP/Private/Apple/AppleHttp.h` (Private)


#### class `FAppleHttpRequest`  
`class FAppleHttpRequest : public FHttpRequestCommon`  
_L23-142_
- inherits: `FHttpRequestCommon`
- desc: Apple implementation of an Http request
- L30 _public prototype_ `virtual TArray<FString> GetAllHeaders() const override;`
- L31 _public prototype_ `virtual FString GetContentType() const override;`
- L32 _public prototype_ `virtual uint64 GetContentLength() const override;`
- L33 _public prototype_ `virtual const TArray<uint8>& GetContent() const override;`
- L37 _public prototype_ `virtual FString GetVerb() const override;`
- L38 _public prototype_ `virtual void SetVerb(const FString& Verb) override;`
- L39 _public prototype_ `virtual void SetContent(const TArray<uint8>& ContentPayload) override;`
- L40 _public prototype_ `virtual void SetContent(TArray<uint8>&& ContentPayload) override;`
- L41 _public prototype_ `virtual void SetContentAsString(const FString& ContentString) override;`
- L42 _public prototype_ `virtual bool SetContentAsStreamedFile(const FString& Filename) override;`
- L43 _public prototype_ `virtual bool SetContentFromStream(TSharedRef<FArchive> Stream) override;`
- L44 _public prototype_ `virtual void SetHeader(const FString& HeaderName, const FString& HeaderValue) override;`
- L45 _public prototype_ `virtual void AppendToHeader(const FString& HeaderName, const FString& AdditionalHeaderValue) override;`
- L46 _public prototype_ `virtual bool ProcessRequest() override;`
- L47 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L51 _public prototype_ `virtual bool StartThreadedRequest() override;`
- L52 _public prototype_ `virtual void FinishRequest() override;`
- L53 _public prototype_ `virtual bool IsThreadedRequestComplete() override;`
- L54 _public prototype_ `virtual void TickThreadedRequest(float DeltaSeconds) override;`
- L63 _public prototype_ `FAppleHttpRequest(NSURLSession* InSession, NSURLSession* InBackgroundSession);` — Constructor @param InSession - NSURLSession session used to create NSURLSessionTask to retrieve the response @param InBackgroundSession - NSURLSession session used to create NSURLSessionTask to retrieve the response in the background
- L68 _public prototype_ `virtual ~FAppleHttpRequest();` — Destructor. Clean up any connection/request handles
- L81 _public prototype_ `bool IsInitializedWithValidStream() const;`
- L83 _public prototype_ `void HandleResponseHeadersReceived(TMap<FString, FString>&& ResponseHeaders);`
- L84 _public prototype_ `bool HandleResponseBodyDataReceived(uint8* Ptr, uint64 Size);`
- L90 _private prototype_ `void CheckProgressDelegate();` — Trigger the request progress delegate if progress has changed
- L97 _private prototype_ `virtual bool SetupRequest() override;` — Create the session connection and initiate the web request @return true if the request was started
- L99 _private prototype_ `virtual FHttpResponsePtr CreateResponse() override;`
- L100 _private prototype_ `virtual void MockResponseData() override;`
- L102 _private prototype_ `virtual void AbortRequest() override;`
- L107 _private prototype_ `virtual void CleanupRequest() override;` — Close session/request handles and unregister callbacks
- L111 _private member_ `NSMutableURLRequest* Request;` — This is the NSMutableURLRequest, all our Apple functionality will deal with this.
- L114 _private member_ `NSURLSession* Session;` — This is the session our request belongs to (depending on the RequestMode option)
- L116 _private member_ `NSURLSession* BackgroundSession;` — This is the background session our request belongs to (depending on the RequestMode option)
- L119 _private member_ `NSURLSessionTask* Task;` — This is the Task associated to the sessionin charge of our request
- L129 _private member_ `TVariant<FNoStreamSource, FInvalidStreamSource, FString, TSharedRef<FArchive>> StreamedContentSource;` — Source to create stream from FNoStreamedSource: No streamed data FString: Filename set from SetContentAsStreamedFile TSharedRef<FArchive>: Stream set from SetContentFromStream
- L132 _private member_ `uint64 ContentBytesLength;` — The request payload length in bytes. This must be tracked separately for a file stream
- L135 _private member_ `mutable TArray<uint8> StorageForGetContent;` — Array used to retrieve back content set on the ObjC request when calling GetContent
- L138 _private member_ `int32 LastReportedBytesWritten;` — Last reported bytes written
- L141 _private member_ `int32 LastReportedBytesRead;` — Last reported bytesread

#### struct `FAppleHttpRequest::FNoStreamSource`  
`struct FNoStreamSource`  
_L122-122_

#### struct `FAppleHttpRequest::FInvalidStreamSource`  
`struct FInvalidStreamSource`  
_L123-123_

#### class `FAppleHttpResponse`  
`class FAppleHttpResponse : public FHttpResponseCommon`  
_L149-218_
- inherits: `FHttpResponseCommon`
- desc: Apple implementation of an Http response
- L153 _public prototype_ `virtual TArray<FString> GetAllHeaders() const override;`
- L154 _public prototype_ `virtual FString GetContentType() const override;`
- L155 _public prototype_ `virtual uint64 GetContentLength() const override;`
- L161 _public prototype_ `bool IsReady() const;` — Check whether a response is ready or not.
- L166 _public prototype_ `const uint64 GetNumBytesReceived() const;` — Get the number of bytes received so far
- L171 _public prototype_ `const uint64 GetNumBytesWritten() const;` — Get the number of bytes sent so far
- L176 _public prototype_ `void CleanSharedObjects();` — Cleans internal shared objects between request and response
- L182 _public prototype_ `void SetNewAppleHttpEventDelegate(FNewAppleHttpEventDelegate&& Delegate);` — Sets delegate invoked when  URLSession:dataTask:didReceiveData or URLSession:task:didCompleteWithError: are triggered Should be set right before task is started
- L184 _public prototype_ `void SetHeaders(TMap<FString, FString>&& InHeaders);`
- L186 _public prototype_ `FAppleHttpResponseDelegate* GetResponseDelegate() const;`
- L195 _public prototype_ `FAppleHttpResponse(FAppleHttpRequest& InRequest);` — Constructor @param InRequest - original request that created this response
- L200 _public prototype_ `virtual ~FAppleHttpResponse();` — Destructor
- L209 _private prototype_ `EHttpRequestStatus::Type GetStatusFromDelegate() const;` — Get status from the internal delegate
- L214 _private prototype_ `EHttpFailureReason GetFailureReasonFromDelegate() const;` — Get reason of failure from the internal delegate
- L217 _private member_ `FAppleHttpResponseDelegate* ResponseDelegate;` — Delegate implementation. Keeps the response state and data

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE(FNewAppleHttpEventDelegate);` — Delegate invoked when in progress Task completes. It is invoked in an out of our control thread
- L16 _prototype_ `DECLARE_DELEGATE(FNewAppleHttpEventDelegate);` — Delegate invoked when in progress Task completes. It is invoked in an out of our control thread

### `Source/Runtime/Online/HTTP/Private/Apple/AppleHttpBackgroundSession.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/Online/HTTP/Private/Apple/AppleHttpManager.h` (Private)


#### class `FAppleHttpManager`  
`class FAppleHttpManager : public FHttpManager`  
_L9-15_
- inherits: `FHttpManager`
- L13 _protected prototype_ `virtual FHttpThreadBase* CreateHttpThread() override;`

### `Source/Runtime/Online/HTTP/Private/Apple/AppleHttpObjc.h` (Private)


#### Free symbols / members of external scopes

- L25 _variable_ `BOOL bAnyHttpActivity;` — Have we received any data?

### `Source/Runtime/Online/HTTP/Private/Curl/CurlHttp.h` (Private)


#### class `FCurlHttpRequest`  
`class FCurlHttpRequest : public FHttpRequestCommon`  
_L41-318_
- inherits: `FHttpRequestCommon`
- desc: Curl implementation of an HTTP request
- L49 _public prototype_ `virtual TArray<FString> GetAllHeaders() const override;`
- L50 _public prototype_ `virtual FString GetContentType() const override;`
- L51 _public prototype_ `virtual uint64 GetContentLength() const override;`
- L52 _public prototype_ `virtual const TArray<uint8>& GetContent() const override;`
- L56 _public prototype_ `virtual FString GetVerb() const override;`
- L57 _public prototype_ `virtual void SetVerb(const FString& InVerb) override;`
- L58 _public prototype_ `virtual void SetOption(const FName Option, const FString& OptionValue) override;`
- L59 _public prototype_ `virtual void SetContent(const TArray<uint8>& ContentPayload) override;`
- L60 _public prototype_ `virtual void SetContent(TArray<uint8>&& ContentPayload) override;`
- L61 _public prototype_ `virtual void SetContentAsString(const FString& ContentString) override;`
- L62 _public prototype_ `virtual bool SetContentAsStreamedFile(const FString& Filename) override;`
- L63 _public prototype_ `virtual bool SetContentFromStream(TSharedRef<FArchive, ESPMode::ThreadSafe> Stream) override;`
- L64 _public prototype_ `virtual void AppendToHeader(const FString& HeaderName, const FString& AdditionalHeaderValue) override;`
- L65 _public prototype_ `virtual bool ProcessRequest() override;`
- L66 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L70 _public prototype_ `virtual bool StartThreadedRequest() override;`
- L71 _public prototype_ `virtual void FinishRequest() override;`
- L72 _public prototype_ `virtual bool IsThreadedRequestComplete() override;`
- L73 _public prototype_ `virtual void TickThreadedRequest(float DeltaSeconds) override;`
- L79 _public prototype_ `void CleanupRequestHttpThread();` — Perform the http-thread cleanup of the request
- L86 _public function_ `inline CURL * GetEasyHandle() const` — Returns libcurl's easy handle - needed for HTTP manager. @return libcurl's easy handle
- L99 _public prototype_ `void MarkAsCompleted(CURLcode InCurlCompletionResult);` — Marks request as completed (set by HTTP manager). Note that this method is intended to be lightweight, more processing will be done in Tick() @param CurlCompletionResult Operation result code as returned by libcurl
- L104 _public function_ `void SetAddToCurlMultiResult(CURLMcode Result)` — Set the result for adding the easy handle to curl multi
- L112 _public prototype_ `FCurlHttpRequest();` — Constructor
- L117 _public prototype_ `virtual ~FCurlHttpRequest();` — Destructor. Clean up any connection/request handles
- L125 _protected prototype_ `virtual bool SetupRequest() override;` — Perform the game-thread setup of the request @return true if the request was successfully setup
- L135 _private prototype_ `bool InitEasyHandle();` — Initialize the curl easy handle and apply all static options. Called either from the constructor (legacy path) or SetupRequest (deferred path). @return true if the handle was successfully created
- L141 _private prototype_ `void DestroyEasyHandle();` — Destroy the curl easy handle and free the header list. Called either from the destructor (legacy path) or CleanupRequest (deferred path).
- L152 _private prototype_ `static size_t StaticUploadCallback(void* Ptr, size_t SizeInBlocks, size_t BlockSizeInBytes, void* UserData);` — Static callback to be used as read function (CURLOPT_READFUNCTION), will dispatch the call to proper instance @param Ptr buffer to copy data to (allocated and managed by libcurl) @param SizeInBlocks size of above buffer, in 'blocks' @param BlockSizeInBytes size of a single block @param UserData data we associated with request (will be a pointer to FCurlHttpRequest instance) @return number of bytes actually written to buffer, or CURL_READFUNC_ABORT to abort the operation
- L162 _private prototype_ `size_t UploadCallback(void* Ptr, size_t SizeInBlocks, size_t BlockSizeInBytes);` — Method called when libcurl wants us to supply more data (see CURLOPT_READFUNCTION) @param Ptr buffer to copy data to (allocated and managed by libcurl) @param SizeInBlocks size of above buffer, in 'blocks' @param BlockSizeInBytes size of a single block @return number of bytes actually written to buffer, or CURL_READFUNC_ABORT to abort the operation
- L172 _private prototype_ `static int StaticSeekCallback(void* UserData, curl_off_t Offset, int Origin);` — Static callback to be used as seek function (CURLOPT_SEEKFUNCTION), will dispatch the call to proper instance @param UserData data we associated with request (will be a pointer to FCurlHttpRequest instance) @param Offset offset from Origin to seek to @param Origin where to seek to. Can be SEEK_SET, SEEK_CUR, or SEEK_END @return CURL_SEEKFUNC_OK if the seek was successful, CURL_SEEKFUNC_FAIL if the request should be failed due to inability to seek, or CURL_SEEKFUNC_CANTSEEK to allow curl to try to workaround the inability to seek
- L181 _private prototype_ `int SeekCallback(curl_off_t Offset, int Origin);` — Method called when libcurl wants us to seek to a position in the stream (see CURLOPT_SEEKFUNCTION) @param Offset offset from Origin to seek to @param Origin where to seek to. Can be SEEK_SET, SEEK_CUR, or SEEK_END @return CURL_SEEKFUNC_OK if the seek was successful, CURL_SEEKFUNC_FAIL if the request should be failed due to inability to seek, or CURL_SEEKFUNC_CANTSEEK to allow curl to try to workaround the inability to seek
- L192 _private prototype_ `static size_t StaticReceiveResponseHeaderCallback(void* Ptr, size_t SizeInBlocks, size_t BlockSizeInBytes, void* UserData);` — Static callback to be used as header function (CURLOPT_HEADERFUNCTION), will dispatch the call to proper instance @param Ptr buffer to copy data to (allocated and managed by libcurl) @param SizeInBlocks size of above buffer, in 'blocks' @param BlockSizeInBytes size of a single block @param UserData data we associated with request (will be a pointer to FCurlHttpRequest instance) @return number of bytes actually processed, error is triggered if it does not match number of bytes passed
- L204 _private prototype_ `size_t ReceiveResponseHeaderCallback(void* Ptr, size_t SizeInBlocks, size_t BlockSizeInBytes);` — Method called when libcurl wants us to receive response header (see CURLOPT_HEADERFUNCTION). Headers will be passed line by line (i.e. this callback will be called with a full line), not necessarily zero-terminated. This callback will be also passed any intermediate headers, not only final response's ones. @param Ptr buffer to copy data to (allocated and managed by libcurl) @param SizeInBlocks size of above buffer, in 'blocks' @param BlockSizeInBytes size of a single block @return number of bytes actually processed, error is triggered if it does not match number of bytes passed
- L215 _private prototype_ `static size_t StaticReceiveResponseBodyCallback(void* Ptr, size_t SizeInBlocks, size_t BlockSizeInBytes, void* UserData);` — Static callback to be used as write function (CURLOPT_WRITEFUNCTION), will dispatch the call to proper instance @param Ptr buffer to copy data to (allocated and managed by libcurl) @param SizeInBlocks size of above buffer, in 'blocks' @param BlockSizeInBytes size of a single block @param UserData data we associated with request (will be a pointer to FCurlHttpRequest instance) @return number of bytes actually processed, error is triggered if it does not match number of bytes passed
- L225 _private prototype_ `size_t ReceiveResponseBodyCallback(void* Ptr, size_t SizeInBlocks, size_t BlockSizeInBytes);` — Method called when libcurl wants us to receive response body (see CURLOPT_WRITEFUNCTION) @param Ptr buffer to copy data to (allocated and managed by libcurl) @param SizeInBlocks size of above buffer, in 'blocks' @param BlockSizeInBytes size of a single block @return number of bytes actually processed, error is triggered if it does not match number of bytes passed
- L237 _private prototype_ `static size_t StaticDebugCallback(CURL * Handle, curl_infotype DebugInfoType, char * DebugInfo, size_t DebugInfoSize, void* UserData);` — Static callback to be used as debug function (CURLOPT_DEBUGFUNCTION), will dispatch the call to proper instance @param Handle handle to which the debug information applies @param DebugInfoType type of information (CURLINFO_*) @param DebugInfo debug information itself (may NOT be text, may NOT be zero-terminated) @param DebugInfoSize exact size of debug information @param UserData data we associated with request (will be a pointer to FCurlHttpRequest instance) @return must return 0
- L248 _private prototype_ `size_t DebugCallback(CURL * Handle, curl_infotype DebugInfoType, char * DebugInfo, size_t DebugInfoSize);` — Method called with debug information about libcurl activities (see CURLOPT_DEBUGFUNCTION) @param Handle handle to which the debug information applies @param DebugInfoType type of information (CURLINFO_*) @param DebugInfo debug information itself (may NOT be text, may NOT be zero-terminated) @param DebugInfoSize exact size of debug information @return must return 0
- L250 _private prototype_ `virtual void AbortRequest() override;`
- L255 _private prototype_ `void CheckProgressDelegate();` — Trigger the request progress delegate if progress has changed
- L258 _private prototype_ `void BroadcastNewlyReceivedHeaders();` — Broadcast newly received headers
- L261 _private prototype_ `static FString CombineHeaderKeyValue(const FString& HeaderKey, const FString& HeaderValue);` — Combine a header's key/value in the format "Key: Value"
- L263 _private prototype_ `virtual void CleanupRequest() override;`
- L265 _private prototype_ `void OnAnyActivityOccur(FStringView Reason);`
- L267 _private prototype_ `virtual void ClearInCaseOfRetry() override;`
- L269 _private prototype_ `virtual FHttpResponsePtr CreateResponse() override;`
- L270 _private prototype_ `virtual void MockResponseData() override;`
- L272 _private prototype_ `void SetupOptionUnixSocketPath();`
- L273 _private prototype_ `void SetupOptionHttpVersion();`
- L274 _private prototype_ `void SetupOptionEnableCookies();`
- L276 _private prototype_ `void LogCurlErrors();`
- L281 _private member_ `CURL * EasyHandle;` — Pointer to an easy handle specific to this request
- L283 _private member_ `curl_slist * HeaderList;` — List of custom headers to be passed to CURL
- L285 _private member_ `FString Verb;` — Cached verb
- L287 _private member_ `std::atomic<bool> bCurlRequestCompleted;` — Set to true when request has been completed
- L289 _private member_ `bool bRedirected;` — Set to true when request has "30* Multiple Choices" (e.g. 301 Moved Permanently, 302 temporary redirect, 308 Permanent Redirect, etc.)
- L291 _private member_ `CURLMcode CurlAddToMultiResult;` — Set to true if request failed to be added to curl multi
- L293 _private member_ `CURLcode CurlCompletionResult;` — Operation result code as returned by libcurl
- L295 _private member_ `bool bIsRequestPayloadSeekable = false;` — Is the request payload seekable?
- L297 _private member_ `bool bAnyHttpActivity;` — Have we had any HTTP activity with the host? Sending headers, SSL handshake, etc
- L299 _private member_ `TSpscQueue<TPair<FString, FString>> NewlyReceivedHeaders;` — Newly received headers we need to inform listeners about
- L301 _private member_ `std::atomic<int64> BytesSent;` — Number of bytes sent already
- L303 _private member_ `std::atomic<int64> TotalBytesSent;` — Total number of bytes sent already (includes data re-sent by seek attempts)
- L305 _private member_ `std::atomic<int64> TotalBytesRead;` — Caches how many bytes of the response we've read so far
- L307 _private member_ `uint64 LastReportedBytesRead;` — Last bytes read reported to progress delegate
- L309 _private member_ `uint64 LastReportedBytesSent;` — Last bytes sent reported to progress delegate
- L311 _private member_ `static const constexpr int32 NumberOfInfoMessagesToCache = 50;` — Number of info channel messages to cache
- L313 _private member_ `int32 LeastRecentlyCachedInfoMessageIndex;` — Index of least recently cached message
- L315 _private member_ `FCriticalSection InfoMessageCacheCriticalSection;` — Critical section for accessing InfoMessageCache
- L317 _private member_ `TArray<FString, TFixedAllocator<NumberOfInfoMessagesToCache>> InfoMessageCache;` — Cache of info messages from libcurl

#### class `FCurlHttpResponse`  
`class FCurlHttpResponse : public FHttpResponseCommon`  
_L323-347_
- inherits: `FHttpResponseCommon`
- desc: Curl implementation of an HTTP response
- L330 _public prototype_ `virtual TArray<FString> GetAllHeaders() const override;`
- L331 _public prototype_ `virtual FString GetContentType() const override;`
- L332 _public prototype_ `virtual uint64 GetContentLength() const override;`
- L340 _public prototype_ `FCurlHttpResponse(const FCurlHttpRequest& InRequest);` — Constructor @param InRequest - original request that created this response
- L344 _private member_ `uint64 ContentLength;` — Cached content length from completed response
- L346 _private member_ `int32 volatile bSucceeded;` — True if the response was successfully received/processed

#### Free symbols / members of external scopes

- L31 _macro_ `#define CURL_ENABLE_DEBUG_CALLBACK 0`
- L35 _macro_ `#define CURL_ENABLE_NO_TIMEOUTS_OPTION 0`

### `Source/Runtime/Online/HTTP/Private/Curl/CurlHttpManager.h` (Private)


#### class `FCurlHttpManager`  
`class FCurlHttpManager : public FHttpManager`  
_L22-76_
- inherits: `FHttpManager`
- L25 _public prototype_ `static void InitCurl();`
- L26 _public prototype_ `static void ShutdownCurl();`
- L27 _public prototype_ `static bool IsInit();`
- L29 _public member_ `static CURLSH* GShareHandle;`
- L31 _public member_ `static CURLM * GMultiHandle;`
- L63 _public member_ `CurlRequestOptions;`
- L66 _public prototype_ `virtual void OnBeforeFork() override;`
- L67 _public prototype_ `virtual void OnAfterFork() override;`
- L68 _public prototype_ `virtual void OnEndFramePostFork() override;`
- L69 _public prototype_ `virtual void UpdateConfigs() override;`
- L72 _public prototype_ `virtual bool SupportsDynamicProxy() const override;`
- L74 _protected prototype_ `virtual FHttpThreadBase* CreateHttpThread() override;`

#### struct `FCurlHttpManager::FCurlRequestOptions`  
`static struct FCurlRequestOptions`  
_L33-62_
- L35 _public function_ `FCurlRequestOptions() : bVerifyPeer(true) , bAcceptCompressedContent(true) , MaxHostConnections(0) , BufferSize(64*1024)`
- L43 _public prototype_ `void Log();` — Prints out the options to the log
- L46 _public member_ `bool bVerifyPeer;` — Whether or not should verify peer certificate (disable to allow self-signed certs)
- L49 _public member_ `bool bAcceptCompressedContent;` — Allow servers to send compressed content.  Can have a very small cpu cost, and huge bandwidth and response time savings from correctly configured servers.
- L52 _public member_ `int32 MaxHostConnections;` — The maximum number of connections to a particular host
- L55 _public member_ `FString LocalHostAddr;` — Local address to use when making request, respects MULTIHOME command line option
- L58 _public member_ `int32 BufferSize;` — Receive buffer size
- L61 _public member_ `bool bAllowSeekFunction = false;` — Do we allow seeking?

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef void CURLSH;`
- L17 _typedef_ `typedef struct Curl_multi CURLM;`
- L19 _typedef_ `typedef void CURLM;`

### `Source/Runtime/Online/HTTP/Private/Curl/CurlHttpThread.h` (Private)


#### class `FCurlHttpThread`  
`class FCurlHttpThread : public FLegacyHttpThread`  
_L29-46_
- inherits: `FLegacyHttpThread`
- L34 _public prototype_ `FCurlHttpThread();`
- L38 _protected prototype_ `virtual void HttpThreadTick(float DeltaSeconds) override;`
- L39 _protected prototype_ `virtual bool StartThreadedRequest(FHttpRequestCommon* Request) override;`
- L40 _protected prototype_ `virtual void CompleteThreadedRequest(FHttpRequestCommon* Request) override;`
- L45 _protected member_ `TMap<CURL*, FHttpRequestCommon*> HandlesToRequests;` — Mapping of libcurl easy handles to HTTP requests

### `Source/Runtime/Online/HTTP/Private/Curl/CurlMultiPollEventLoopHttpThread.h` (Private)


#### class `FCurlMultiPollIOManagerIOAccess`  
`class FCurlMultiPollIOManagerIOAccess final : public FNoncopyable`  
_L29-38_
- inherits: `FNoncopyable`
- L32 _public prototype_ `FCurlMultiPollIOManagerIOAccess(FCurlMultiPollIOManager& InIOManager);`
- L37 _private member_ `FCurlMultiPollIOManager& IOManager;`

#### class `FCurlMultiPollIOManager`  
`class FCurlMultiPollIOManager final : public UE::EventLoop::IIOManager`  
_L40-69_
- inherits: `UE::EventLoop::IIOManager`
- L43 _public typedef_ `using FIOAccess = FCurlMultiPollIOManagerIOAccess;`
- L51 _public prototype_ `FCurlMultiPollIOManager(UE::EventLoop::IEventLoop& EventLoop, FParams&& Params);`
- L52 _public prototype_ `virtual ~FCurlMultiPollIOManager() = default;`
- L53 _public prototype_ `virtual bool Init() override;`
- L54 _public prototype_ `virtual void Shutdown() override;`
- L55 _public prototype_ `virtual void Notify() override;`
- L56 _public prototype_ `virtual void Poll(FTimespan WaitTime) override;`
- L58 _public function_ `FIOAccess& GetIOAccess()`
- L64 _private prototype_ `void CheckMultiCodeOk(const CURLMcode Code);`
- L66 _private member_ `FIOAccess IOAccess;`
- L67 _private member_ `UE::EventLoop::IEventLoop& EventLoop;`
- L68 _private member_ `FParams Params;`

#### struct `FCurlMultiPollIOManager::FParams`  
`struct FParams`  
_L45-49_
- L47 _public member_ `CURLM* MultiHandle = nullptr;`
- L48 _public member_ `TUniqueFunction<void()> ProcessCurlRequests;`

#### class `FCurlMultiPollEventLoopHttpThread`  
`class FCurlMultiPollEventLoopHttpThread : public FEventLoopHttpThread`  
_L71-96_
- inherits: `FEventLoopHttpThread`
- L76 _public prototype_ `FCurlMultiPollEventLoopHttpThread();`
- L80 _protected prototype_ `virtual bool StartThreadedRequest(FHttpRequestCommon* Request) override;`
- L81 _protected prototype_ `virtual void CompleteThreadedRequest(FHttpRequestCommon* Request) override;`
- L84 _protected prototype_ `virtual void CreateEventLoop() override;`
- L85 _protected prototype_ `virtual void DestroyEventLoop() override;`
- L86 _protected prototype_ `virtual void UpdateEventLoopConfigs() override;`
- L87 _protected prototype_ `virtual UE::EventLoop::IEventLoop* GetEventLoop() override;`
- L88 _protected prototype_ `virtual UE::EventLoop::IEventLoop& GetEventLoopChecked() override;`
- L90 _protected prototype_ `void ProcessCurlRequests();`
- L92 _protected member_ `TOptional<UE::EventLoop::TEventLoop<FCurlMultiPollIOManager>> EventLoop;`
- L95 _protected member_ `TMap<CURL*, FHttpRequestCommon*> HandlesToRequests;` — Mapping of libcurl easy handles to HTTP requests

### `Source/Runtime/Online/HTTP/Private/Curl/CurlMultiWaitEventLoopHttpThread.h` (Private)


#### class `FCurlMultiWaitIOManagerIOAccess`  
`class FCurlMultiWaitIOManagerIOAccess final : public FNoncopyable`  
_L30-39_
- inherits: `FNoncopyable`
- L33 _public prototype_ `FCurlMultiWaitIOManagerIOAccess(FCurlMultiWaitIOManager& InIOManager);`
- L38 _private member_ `FCurlMultiWaitIOManager& IOManager;`

#### class `FCurlMultiWaitIOManager`  
`class FCurlMultiWaitIOManager final : public UE::EventLoop::IIOManager`  
_L41-72_
- inherits: `UE::EventLoop::IIOManager`
- L44 _public typedef_ `using FIOAccess = FCurlMultiWaitIOManagerIOAccess;`
- L52 _public prototype_ `FCurlMultiWaitIOManager(UE::EventLoop::IEventLoop& EventLoop, FParams&& Params);`
- L53 _public prototype_ `virtual ~FCurlMultiWaitIOManager() = default;`
- L54 _public prototype_ `virtual bool Init() override;`
- L55 _public prototype_ `virtual void Shutdown() override;`
- L56 _public prototype_ `virtual void Notify() override;`
- L57 _public prototype_ `virtual void Poll(FTimespan WaitTime) override;`
- L59 _public function_ `FIOAccess& GetIOAccess()`
- L65 _private prototype_ `void CheckMultiCodeOk(const CURLMcode Code);`
- L67 _private member_ `FIOAccess IOAccess;`
- L68 _private member_ `UE::EventLoop::IEventLoop& EventLoop;`
- L69 _private member_ `FParams Params;`
- L70 _private member_ `int32 EmptySequentialWaitCount;`
- L71 _private member_ `UE::EventLoop::FEventLoopNotifier EventLoopNotifier;`

#### struct `FCurlMultiWaitIOManager::FParams`  
`struct FParams`  
_L46-50_
- L48 _public member_ `CURLM* MultiHandle = nullptr;`
- L49 _public member_ `TUniqueFunction<void()> ProcessCurlRequests;`

#### class `FCurlMultiWaitEventLoopHttpThread`  
`class FCurlMultiWaitEventLoopHttpThread : public FEventLoopHttpThread`  
_L74-99_
- inherits: `FEventLoopHttpThread`
- L79 _public prototype_ `FCurlMultiWaitEventLoopHttpThread();`
- L83 _protected prototype_ `virtual bool StartThreadedRequest(FHttpRequestCommon* Request) override;`
- L84 _protected prototype_ `virtual void CompleteThreadedRequest(FHttpRequestCommon* Request) override;`
- L87 _protected prototype_ `virtual void CreateEventLoop() override;`
- L88 _protected prototype_ `virtual void DestroyEventLoop() override;`
- L89 _protected prototype_ `virtual void UpdateEventLoopConfigs() override;`
- L90 _protected prototype_ `virtual UE::EventLoop::IEventLoop* GetEventLoop() override;`
- L91 _protected prototype_ `virtual UE::EventLoop::IEventLoop& GetEventLoopChecked() override;`
- L93 _protected prototype_ `void ProcessCurlRequests();`
- L95 _protected member_ `TOptional<UE::EventLoop::TEventLoop<FCurlMultiWaitIOManager>> EventLoop;`
- L98 _protected member_ `TMap<CURL*, FHttpRequestCommon*> HandlesToRequests;` — Mapping of libcurl easy handles to HTTP requests

### `Source/Runtime/Online/HTTP/Private/Curl/CurlSocketEventLoopHttpThread.h` (Private)


#### class `FCurlSocketEventLoopHttpThread`  
`class FCurlSocketEventLoopHttpThread : public FEventLoopHttpThread`  
_L29-71_
- inherits: `FEventLoopHttpThread`
- L34 _public prototype_ `FCurlSocketEventLoopHttpThread();`
- L38 _protected prototype_ `virtual void HttpThreadTick(float DeltaSeconds) override;`
- L39 _protected prototype_ `virtual bool StartThreadedRequest(FHttpRequestCommon* Request) override;`
- L40 _protected prototype_ `virtual void CompleteThreadedRequest(FHttpRequestCommon* Request) override;`
- L43 _protected prototype_ `virtual void CreateEventLoop() override;`
- L44 _protected prototype_ `virtual void DestroyEventLoop() override;`
- L45 _protected prototype_ `virtual void UpdateEventLoopConfigs() override;`
- L46 _protected prototype_ `virtual UE::EventLoop::IEventLoop* GetEventLoop() override;`
- L47 _protected prototype_ `virtual UE::EventLoop::IEventLoop& GetEventLoopChecked() override;`
- L49 _protected prototype_ `static int CurlSocketCallback(CURL* CurlE, curl_socket_t Socket, int EventFlags, void* UserData, void* SocketData);`
- L50 _protected prototype_ `int HandleCurlSocketCallback(CURL* CurlE, curl_socket_t Socket, int EventFlags, void* SocketData);`
- L52 _protected prototype_ `static int CurlTimerCallback(CURLM* CurlM, long TimeoutMS, void* UserData);`
- L53 _protected prototype_ `int HandleCurlTimerCallback(CURLM* CurlM, long TimeoutMS);`
- L55 _protected prototype_ `void ProcessCurlSocketActions(curl_socket_t Socket, int EventFlags);`
- L56 _protected prototype_ `void ProcessCurlSocketEvent(curl_socket_t Socket, UE::EventLoop::ESocketIoRequestStatus Status, UE::EventLoop::EIOFlags Flags);`
- L57 _protected prototype_ `void ProcessCurlRequests();`
- L66 _protected member_ `TMap<CURL*, FHttpRequestCommon*> HandlesToRequests;` — Mapping of libcurl easy handles to HTTP requests
- L68 _protected member_ `UE::EventLoop::FTimerHandle RequestTimeoutTimer;`
- L70 _protected member_ `TOptional<UE::EventLoop::TEventLoop<UE::EventLoop::FIOManagerBSDSocket>> EventLoop;`

#### struct `FCurlSocketEventLoopHttpThread::FCurlSocketData`  
`struct FCurlSocketData`  
_L59-63_
- L61 _public member_ `curl_socket_t Socket;`
- L62 _public member_ `UE::EventLoop::FIORequestHandle IORequestHandle;`

### `Source/Runtime/Online/HTTP/Private/EventLoopHttpThread.h` (Private)


#### class `FEventLoopHttpThread`  
`class FEventLoopHttpThread : public FHttpThreadBase`  
_L9-51_
- inherits: `FHttpThreadBase`
- L13 _public prototype_ `FEventLoopHttpThread();`
- L14 _public prototype_ `virtual ~FEventLoopHttpThread();`
- L16 _public prototype_ `virtual void StartThread() override final;`
- L17 _public prototype_ `virtual void StopThread() override final;`
- L18 _public prototype_ `virtual void UpdateConfigs() override final;`
- L19 _public prototype_ `virtual void AddRequest(FHttpRequestCommon* Request) override final;`
- L20 _public prototype_ `virtual void CancelRequest(FHttpRequestCommon* Request) override final;`
- L21 _public prototype_ `virtual void GetCompletedRequests(TArray<FHttpRequestCommon*>& OutCompletedRequests) override final;`
- L25 _public prototype_ `virtual void Tick() override final;` — Cannot be overridden to ensure identical behavior with the threaded tick
- L29 _protected prototype_ `virtual void CreateEventLoop() = 0;`
- L30 _protected prototype_ `virtual void DestroyEventLoop() = 0;`
- L31 _protected prototype_ `virtual void UpdateEventLoopConfigs() = 0;`
- L32 _protected prototype_ `virtual UE::EventLoop::IEventLoop* GetEventLoop() = 0;`
- L33 _protected prototype_ `virtual UE::EventLoop::IEventLoop& GetEventLoopChecked() = 0;`
- L36 _protected prototype_ `virtual bool Init() override;`
- L38 _protected prototype_ `virtual uint32 Run() override final;` — Cannot be overridden to ensure identical behavior with the single threaded tick
- L41 _protected prototype_ `void ResetTickTimer();`
- L43 _protected prototype_ `virtual TSharedPtr<IHttpTaskTimerHandle> AddHttpThreadTask(TFunction<void()>&& Task, float InDelay) override;`
- L45 _protected prototype_ `virtual void RemoveTimerHandle(FTSTicker::FDelegateHandle DelegateHandle) override;`
- L47 _protected prototype_ `virtual void RemoveTimerHandle(UE::EventLoop::FTimerHandle EventLoopTimerHandle) override;`
- L50 _protected member_ `UE::EventLoop::FTimerHandle RequestTickTimer;`

### `Source/Runtime/Online/HTTP/Private/GenericPlatform/HttpRequestCommon.h` (Private)


#### class `FHttpRequestCommon`  
`class FHttpRequestCommon : public FHttpRequestImpl`  
_L14-213_
- inherits: `FHttpRequestImpl`
- desc: Contains implementation of some common functions that don't vary between implementations of different platforms
- L17 _public prototype_ `FHttpRequestCommon();`
- L20 _public prototype_ `virtual FString GetURLParameter(const FString& ParameterName) const override;` — IHttpBase
- L23 _public prototype_ `virtual void SetHeader(const FString& HeaderName, const FString& HeaderValue) override;` — IHttpRequest
- L24 _public prototype_ `virtual FString GetHeader(const FString& HeaderName) const override;`
- L25 _public prototype_ `virtual EHttpRequestStatus::Type GetStatus() const override;`
- L26 _public prototype_ `virtual const FString& GetEffectiveURL() const override;`
- L27 _public prototype_ `virtual EHttpFailureReason GetFailureReason() const override;`
- L28 _public prototype_ `virtual void SetDelegateThreadPolicy(EHttpRequestDelegateThreadPolicy InDelegateThreadPolicy) override;`
- L29 _public prototype_ `virtual EHttpRequestDelegateThreadPolicy GetDelegateThreadPolicy() const override;`
- L30 _public prototype_ `virtual FString GetOption(const FName Option) const override;`
- L31 _public prototype_ `virtual void SetOption(const FName Option, const FString & OptionValue) override;`
- L33 _public prototype_ `virtual void SetTimeout(float InTimeoutSecs) override;`
- L34 _public prototype_ `virtual void ClearTimeout() override;`
- L35 _public prototype_ `virtual void ResetTimeoutStatus() override;`
- L36 _public prototype_ `virtual TOptional<float> GetTimeout() const override;`
- L37 _public prototype_ `float GetTimeoutOrDefault() const;`
- L39 _public prototype_ `virtual void SetActivityTimeout(float InTimeoutSecs) override;`
- L41 _public prototype_ `virtual const FHttpResponsePtr GetResponse() const override;`
- L44 _public prototype_ `virtual void FinishRequest() = 0;` — Can be called on game thread or http thread depend on the delegate thread policy
- L46 _public prototype_ `virtual void CancelRequest() override;`
- L48 _public prototype_ `virtual void Shutdown() override;`
- L50 _public prototype_ `virtual void ProcessRequestUntilComplete() override;`
- L52 _public prototype_ `virtual bool SetResponseBodyReceiveStream(TSharedRef<FArchive> Stream) override;`
- L54 _public prototype_ `virtual float GetElapsedTime() const override;`
- L56 _public prototype_ `virtual bool IsThreadedRequestComplete() = 0;`
- L57 _public prototype_ `virtual bool StartThreadedRequest();`
- L58 _public prototype_ `virtual void TickThreadedRequest(float DeltaSeconds) = 0;`
- L60 _public prototype_ `void StartWaitingInQueue();`
- L61 _public prototype_ `double GetTimeStartedWaitingInQueue() const;`
- L63 _public prototype_ `virtual void SetURL(const FString& InURL) override;`
- L64 _public prototype_ `virtual const FString& GetURL() const override;`
- L66 _public prototype_ `virtual void SetPriority(EHttpRequestPriority InPriority) override;`
- L67 _public prototype_ `virtual EHttpRequestPriority GetPriority() const override;`
- L69 _public prototype_ `virtual void ClearInCaseOfRetry();`
- L71 _public prototype_ `void SetStatus(EHttpRequestStatus::Type InCompletionStatus);`
- L72 _public prototype_ `void SetFailureReason(EHttpFailureReason InFailureReason);`
- L78 _protected prototype_ `bool PreProcess();` — Check if this request is valid or allowed, before actually process the request
- L79 _protected prototype_ `void PostProcess();`
- L80 _protected prototype_ `void PopulateUserAgentHeader();`
- L81 _protected prototype_ `virtual bool SetupRequest() = 0;`
- L82 _protected prototype_ `bool PreCheck() const;`
- L87 _protected prototype_ `void FinishRequestNotInHttpManager();` — Finish the request when it's not in http manager
- L89 _protected prototype_ `void HandleRequestSucceed();`
- L90 _protected prototype_ `void HandleRequestFailed();`
- L92 _protected prototype_ `void StartActivityTimeoutTimer();`
- L93 _protected prototype_ `void StartActivityTimeoutTimerBy(double DelayToTrigger);`
- L94 _protected prototype_ `void ResetActivityTimeoutTimer(FStringView Reason);`
- L95 _protected prototype_ `void OnActivityTimeoutTimerTaskTrigger();`
- L96 _protected prototype_ `void StopActivityTimeoutTimer();`
- L97 _protected prototype_ `void StartTotalTimeoutTimer();`
- L98 _protected prototype_ `void StopTotalTimeoutTimer();`
- L99 _protected prototype_ `void OnTotalTimeoutTimerTaskTrigger();`
- L101 _protected prototype_ `virtual void AbortRequest() = 0;`
- L103 _protected prototype_ `virtual void CleanupRequest() = 0;`
- L105 _protected prototype_ `void HandleStatusCodeReceived(int32 StatusCode);`
- L106 _protected prototype_ `void TriggerStatusCodeReceivedDelegate(int32 StatusCode);`
- L108 _protected prototype_ `void SetEffectiveURL(const FString& InEffectiveURL);`
- L110 _protected prototype_ `bool PassReceivedDataToStream(void* Ptr, int64 Length);`
- L111 _protected prototype_ `void StopPassingReceivedData();`
- L113 _protected prototype_ `float GetActivityTimeoutOrDefault() const;`
- L115 _protected prototype_ `bool SetContentAsStreamedFileDefaultImpl(const FString& Filename);`
- L116 _protected prototype_ `bool OpenRequestPayloadDefaultImpl();`
- L117 _protected prototype_ `void CloseRequestPayloadDefaultImpl();`
- L119 _protected prototype_ `void LogFailure() const;`
- L120 _protected prototype_ `void LogRequest() const;`
- L121 _protected prototype_ `void LogResponse(const TSharedPtr<FHttpResponseCommon>& InResponse) const;`
- L122 _protected prototype_ `void LogHeaders(const TMap<FString, FString>& Headers, bool bShouldLogAsWarning, bool bIsResponse) const;`
- L123 _protected prototype_ `void LogContent(bool bShouldLogDetails, const IHttpBase& HttpBase, bool bIsResponse) const;`
- L124 _protected prototype_ `bool TriggerMockResponse();`
- L126 _protected prototype_ `void InitResponse();`
- L128 _protected prototype_ `virtual FHttpResponsePtr CreateResponse() = 0;`
- L130 _protected prototype_ `virtual void MockResponseData() = 0;` — The function for each impl to make sure when mocking response code, the internal state is valid for finishing request successfully
- L132 _protected prototype_ `void OnFinishRequest(bool bSucceeded);`
- L136 _protected member_ `EHttpRequestStatus::Type CompletionStatus = EHttpRequestStatus::NotStarted;` — Current status of request being processed
- L139 _protected member_ `EHttpFailureReason FailureReason = EHttpFailureReason::None;` — Reason of failure of the HTTP request
- L142 _protected member_ `EHttpRequestDelegateThreadPolicy DelegateThreadPolicy = EHttpRequestDelegateThreadPolicy::CompleteOnGameThread;` — Thread policy about which thread to complete this request
- L145 _protected member_ `TOptional<float> TimeoutSecs;` — Timeout in seconds for the entire HTTP request to complete
- L148 _protected member_ `TOptional<float> ActivityTimeoutSecs;` — Timeout in seconds for the HTTP request activity timeout
- L151 _protected member_ `std::atomic<bool> bTimedOut = false;` — Indicate the request is timed out, it should quit and fail with EHttpFailureReason::TimedOut
- L153 _protected member_ `std::atomic<bool> bActivityTimedOut = false;` — Indicate the request is activity timed out, it should quit and fail with EHttpFailureReason::ConnectionError
- L155 _protected member_ `std::atomic<bool> bCanceled = false;` — Indicate the request is cancelled, it should quit and fail with EHttpFailureReason::Cancelled
- L158 _protected member_ `bool bUsePlatformActivityTimeout = true;` — TODO: Move this feature into CurlHttp
- L161 _protected member_ `double RequestStartTimeAbsoluteSeconds;` — Record when this request started
- L164 _protected member_ `double ActivityTimeoutAt;` — Record when this request will activity timeout
- L167 _protected member_ `TSharedPtr<IHttpTaskTimerHandle> TotalTimeoutHttpTaskTimerHandle;` — Holder the timer handle, if the request get destroyed before triggering the timeout, use this to remove the timer
- L169 _protected member_ `TSharedPtr<IHttpTaskTimerHandle> ActivityTimeoutHttpTaskTimerHandle;` — Holder the timer handle, if the request get destroyed before triggering the timeout, use this to remove the timer
- L171 _protected member_ `FCriticalSection HttpTaskTimerHandleCriticalSection;` — Critical section for accessing HttpTaskTimerHandle
- L174 _protected member_ `double StartProcessTime = 0.0;` — Record when the request start to process
- L177 _protected member_ `double ConnectTime = -1.0;` — Record how long it take to connect to the endpoint
- L179 _protected member_ `FString URL;`
- L182 _protected member_ `FString EffectiveURL;` — Cache the effective URL. When redirected, it will be different with original URL
- L185 _protected member_ `TSharedPtr<FHttpResponseCommon> ResponseCommon;` — The response object which we will use to pair with this request
- L188 _protected member_ `TSharedPtr<FArchive> ResponseBodyReceiveStream;` — The stream to receive response body
- L191 _protected member_ `FCriticalSection ResponseBodyReceiveStreamCriticalSection;` — Critical section for accessing ResponseBodyReceiveStream
- L195 _protected member_ `std::atomic<bool> bInitializedWithValidStream = false;` — Flag to indicate the request was initialized with stream. In that case even if stream was set to null later on internally, the request itself won't cache received data anymore
- L198 _protected member_ `TMap<FString, FString> RequestHeaders;` — Mapping of header section to values.
- L201 _protected member_ `TUniquePtr<FRequestPayload> RequestPayload;` — Payload to use with the request. Typically for POST, PUT, or PATCH
- L204 _protected member_ `TMap<const FName, FString> Options;` — Options for this request.
- L207 _protected member_ `float ElapsedTime = 0.0f;` — Total elapsed time in seconds since the start of the request
- L210 _protected member_ `double TimeStartedWaitingInQueue = 0.0;` — Record the time started to wait in the queue
- L212 _protected member_ `EHttpRequestPriority Priority = EHttpRequestPriority::Normal;`

### `Source/Runtime/Online/HTTP/Private/GenericPlatform/HttpResponseCommon.h` (Private)


#### class `FHttpResponseCommon`  
`class FHttpResponseCommon : public IHttpResponse`  
_L12-47_
- inherits: `IHttpResponse`
- desc: Contains implementation of some common functions that don't vary between implementations of different platforms
- L17 _public prototype_ `FHttpResponseCommon(const FHttpRequestCommon& HttpRequest);`
- L20 _public prototype_ `virtual FString GetURLParameter(const FString& ParameterName) const override;` — IHttpBase
- L21 _public prototype_ `virtual const FString& GetURL() const override;`
- L22 _public prototype_ `virtual const FString& GetEffectiveURL() const override;`
- L23 _public prototype_ `virtual EHttpRequestStatus::Type GetStatus() const override;`
- L24 _public prototype_ `virtual EHttpFailureReason GetFailureReason() const override;`
- L25 _public prototype_ `virtual int32 GetResponseCode() const override;`
- L26 _public prototype_ `virtual FUtf8StringView GetContentAsUtf8StringView() const override;`
- L27 _public prototype_ `virtual FString GetHeader(const FString& HeaderName) const override;`
- L28 _public prototype_ `virtual const TArray<uint8>& GetContent() const override;`
- L29 _public prototype_ `virtual TArray<uint8> TakeContent() override;`
- L30 _public prototype_ `virtual FString GetContentAsString() const override;`
- L33 _protected prototype_ `void SetRequestStatus(EHttpRequestStatus::Type InCompletionStatus);`
- L34 _protected prototype_ `void SetRequestFailureReason(EHttpFailureReason InFailureReason);`
- L35 _protected prototype_ `void SetEffectiveURL(const FString& InEffectiveURL);`
- L36 _protected prototype_ `void SetResponseCode(int32 InResponseCode);`
- L37 _protected prototype_ `void AppendToPayload(const uint8* Ptr, int64 Size);`
- L39 _protected member_ `FString URL;`
- L40 _protected member_ `FString EffectiveURL;`
- L41 _protected member_ `EHttpRequestStatus::Type CompletionStatus;`
- L42 _protected member_ `EHttpFailureReason FailureReason;`
- L43 _protected member_ `int32 ResponseCode = EHttpResponseCodes::Unknown;`
- L44 _protected member_ `TArray<uint8> Payload;`
- L45 _protected member_ `TMap<FString, FString> Headers;`
- L46 _protected member_ `bool bIsReady = false;`

### `Source/Runtime/Online/HTTP/Private/HttpPrivate.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/Online/HTTP/Private/HttpTests.h` (Private)


#### class `FHttpTest`  
`class FHttpTest`  
_L11-44_
- desc: Test an Http request to a specified endpoint Url
- L23 _public prototype_ `FHttpTest(const FString& InVerb, const FString& InPayload, const FString& InUrl, int32 InIterations);` — Constructor @param Verb - verb to use for request (GET,POST,DELETE,etc) @param Payload - optional payload string @param Url - url address to connect to @param InIterations - total test iterations to run
- L28 _public prototype_ `void Run(void);` — Kick off the Http request for the test and wait for delegate to be called
- L37 _public prototype_ `void RequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);` — Delegate called when the request completes @param HttpRequest - object that started/processed the request @param HttpResponse - optional response object if request completed @param bSucceeded - true if Url connection was made and response was received
- L40 _private member_ `FString Verb;`
- L41 _private member_ `FString Payload;`
- L42 _private member_ `FString Url;`
- L43 _private member_ `int32 TestsToRun;`

### `Source/Runtime/Online/HTTP/Private/HttpThread.h` (Private)


#### class `IHttpTaskTimerHandle`  
`class IHttpTaskTimerHandle`  
_L21-27_
- L24 _public prototype_ `virtual ~IHttpTaskTimerHandle() = default;`
- L26 _public prototype_ `virtual void RemoveTaskFrom(FHttpThreadBase* HttpThreadBase) = 0;`

#### class `FHttpThreadBase`  
`class FHttpThreadBase : FRunnable, FSingleThreadRunnable`  
_L33-199_
- inherits: `FRunnable,FSingleThreadRunnable`
- desc: Manages Http thread Assumes any requests entering the system will remain valid (not deleted) until they exit the system
- L38 _public prototype_ `FHttpThreadBase();`
- L39 _public prototype_ `virtual ~FHttpThreadBase();`
- L44 _public prototype_ `virtual void StartThread();` — Start the HTTP thread.
- L49 _public prototype_ `virtual void StopThread();` — Stop the HTTP thread.  Blocks until thread has stopped.
- L54 _public function_ `bool IsStopped() const` — Is the HTTP thread started or stopped.
- L61 _public prototype_ `virtual void AddRequest(FHttpRequestCommon* Request);` — Add a request to begin processing on HTTP thread. @param Request the request to be processed on the HTTP thread
- L68 _public prototype_ `virtual void CancelRequest(FHttpRequestCommon* Request);` — Mark a request as cancelled.    Called on non-HTTP thread. @param Request the request to be processed on the HTTP thread
- L75 _public prototype_ `virtual void GetCompletedRequests(TArray<FHttpRequestCommon*>& OutCompletedRequests);` — Get completed requests.  Clears internal arrays.  Called on non-HTTP thread. @param OutCompletedRequests array of requests that have been completed
- L78 _public prototype_ `virtual void Tick() override;`
- L85 _public prototype_ `bool NeedsSingleThreadTick() const;` — When true the owner of the HTTPThread needs to manually call Tick() since no automomous threads are executing the runnable object
- L90 _public prototype_ `virtual void UpdateConfigs();` — Update configuration. Called when config has been updated and we need to apply any changes.
- L99 _public prototype_ `virtual TSharedPtr<IHttpTaskTimerHandle> AddHttpThreadTask(TFunction<void()>&& Task, float InDelay) = 0;` — Add task to be ran on the http thread next tick @param Task The task to be ran @param InDelay The delay to wait before running the task @return The handle of the timer, which could be used to remove the task before it get triggered
- L101 _public prototype_ `virtual void RemoveTimerHandle(FTSTicker::FDelegateHandle DelegateHandle) = 0;`
- L103 _public prototype_ `virtual void RemoveTimerHandle(UE::EventLoop::FTimerHandle EventLoopTimerHandle) = 0;`
- L110 _protected prototype_ `virtual void HttpThreadTick(float DeltaSeconds);` — Tick on http thread
- L115 _protected prototype_ `virtual bool StartThreadedRequest(FHttpRequestCommon* Request);` — Start processing a request on the http thread
- L120 _protected prototype_ `virtual void CompleteThreadedRequest(FHttpRequestCommon* Request);` — Complete a request on the http thread
- L127 _protected prototype_ `virtual bool Init() override;`
- L128 _protected prototype_ `virtual uint32 Run() override;`
- L129 _protected prototype_ `virtual void Stop() override;`
- L130 _protected prototype_ `virtual void Exit() override;`
- L133 _protected prototype_ `void Process(TArray<FHttpRequestCommon*>& RequestsToCancel, TArray<FHttpRequestCommon*>& RequestsToComplete);`
- L139 _protected function_ `virtual class FSingleThreadRunnable* GetSingleThreadInterface() override` — FSingleThreadRunnable accessor for ticking this FRunnable when multi-threading is disabled. @return FSingleThreadRunnable Interface for this FRunnable object.
- L142 _private prototype_ `void ConsumeCanceledRequestsAndNewRequests(TArray<FHttpRequestCommon*>& RequestsToCancel, TArray<FHttpRequestCommon*>& RequestsToComplete);`
- L143 _private prototype_ `void InsertToRateLimitedRequestsAccordingToPriority(FHttpRequestCommon* Request);`
- L144 _private prototype_ `void MoveCompletingRequestsToCompletedRequests(TArray<FHttpRequestCommon*>& RequestsToComplete);`
- L145 _private prototype_ `void StartRequestsWaitingInQueue(TArray<FHttpRequestCommon*>& RequestsToComplete);`
- L146 _private prototype_ `void FinishRequestsFromHttpThreadWithCallbacks(TArray<FHttpRequestCommon*>& RequestsToComplete);`
- L147 _private prototype_ `void UpdateThreadPriorityIfNeeded();`
- L151 _protected member_ `FRunnableThread* Thread;` — Pointer to Runnable Thread
- L155 _private member_ `bool bIsSingleThread;` — Are we holding a fake thread and we need to be ticked manually when Flushing
- L158 _private member_ `bool bIsStopped;` — Tells if the runnable thread is running or stopped
- L161 _private member_ `double LastTime;` — Last time the thread has been processed. Used in the non-game thread.
- L164 _private member_ `EThreadPriority CurrentThreadPriority;` — Current thread priority of the thread. Used to detect when a priority change is requested
- L167 _private member_ `int32 MaxConcurrentRequests;` — Max concurrent requests the thread can run, the rest of the requests will wait in the queue
- L174 _protected member_ `TMpscQueue<FHttpRequestCommon*> NewThreadedRequests;` — Threaded requests that are waiting to be processed on the http thread. Added to on (any) non-HTTP thread, processed then cleared on HTTP thread.
- L180 _protected member_ `TMpscQueue<FHttpRequestCommon*> CancelledThreadedRequests;` — Threaded requests that are waiting to be cancelled on the http thread. Added to on (any) non-HTTP thread, processed then cleared on HTTP thread.
- L186 _protected member_ `TArray<FHttpRequestCommon*> RateLimitedThreadedRequests;` — Threaded requests that are ready to run, but waiting due to the running request limit (not in any of the other lists, except potentially CancelledThreadedRequests). Only accessed on the HTTP thread.
- L192 _protected member_ `TArray<FHttpRequestCommon*> RunningThreadedRequests;` — Currently running threaded requests (not in any of the other lists, except potentially CancelledThreadedRequests). Only accessed on the HTTP thread.
- L198 _protected member_ `TSpscQueue<FHttpRequestCommon*> CompletedThreadedRequests;` — Threaded requests that have completed and are waiting for the game thread to process. Added to on HTTP thread, processed then cleared on game thread (Single producer, single consumer)

#### class `FLegacyHttpThread`  
`class FLegacyHttpThread : public FHttpThreadBase`  
_L201-247_
- inherits: `FHttpThreadBase`
- L205 _public prototype_ `FLegacyHttpThread();`
- L206 _public prototype_ `virtual ~FLegacyHttpThread();`
- L208 _public prototype_ `virtual void StartThread() override final;`
- L209 _public prototype_ `virtual void StopThread() override final;`
- L210 _public prototype_ `virtual void AddRequest(FHttpRequestCommon* Request) override final;`
- L211 _public prototype_ `virtual void CancelRequest(FHttpRequestCommon* Request) override final;`
- L212 _public prototype_ `virtual void GetCompletedRequests(TArray<FHttpRequestCommon*>& OutCompletedRequests) override final;`
- L216 _public prototype_ `virtual void Tick() override final;` — Cannot be overridden to ensure identical behavior with the threaded tick
- L221 _protected prototype_ `virtual bool Init() override;`
- L223 _protected prototype_ `virtual uint32 Run() override final;` — Cannot be overridden to ensure identical behavior with the single threaded tick
- L224 _protected prototype_ `virtual void Stop() override;`
- L227 _protected prototype_ `virtual TSharedPtr<IHttpTaskTimerHandle> AddHttpThreadTask(TFunction<void()>&& Task, float InDelay) override;`
- L228 _protected prototype_ `virtual void HttpThreadTick(float DeltaSeconds) override;`
- L230 _protected prototype_ `virtual void RemoveTimerHandle(FTSTicker::FDelegateHandle DelegateHandle) override;`
- L231 _protected prototype_ `virtual void RemoveTimerHandle(UE::EventLoop::FTimerHandle EventLoopTimerHandle) override;`
- L234 _protected member_ `FThreadSafeCounter ExitRequest;` — signal request to stop and exit thread
- L237 _protected member_ `double HttpThreadActiveFrameTimeInSeconds;` — Time in seconds to use as frame time when actively processing requests. 0 means no frame time.
- L239 _protected member_ `double HttpThreadActiveMinimumSleepTimeInSeconds;` — Time in seconds to sleep minimally when actively processing requests.
- L241 _protected member_ `double HttpThreadIdleFrameTimeInSeconds;` — Time in seconds to use as frame time when idle, waiting for requests. 0 means no frame time.
- L243 _protected member_ `double HttpThreadIdleMinimumSleepTimeInSeconds;` — Time in seconds to sleep minimally when idle, waiting for requests.
- L246 _protected member_ `FTSTicker Ticker;` — Ticker for functions to run in HTTP thread

### `Source/Runtime/Online/HTTP/Private/NullHttp.h` (Private)


#### class `FNullHttpRequest`  
`class FNullHttpRequest : public FHttpRequestImpl`  
_L12-77_
- inherits: `FHttpRequestImpl`
- desc: Null (mock) implementation of an HTTP request
- L17 _public prototype_ `virtual const FString& GetURL() const override;` — IHttpBase
- L18 _public prototype_ `virtual FString GetURLParameter(const FString& ParameterName) const override;`
- L19 _public prototype_ `virtual FString GetHeader(const FString& HeaderName) const override;`
- L20 _public prototype_ `virtual TArray<FString> GetAllHeaders() const override;`
- L21 _public prototype_ `virtual FString GetContentType() const override;`
- L22 _public prototype_ `virtual uint64 GetContentLength() const override;`
- L23 _public prototype_ `virtual const TArray<uint8>& GetContent() const override;`
- L25 _public prototype_ `virtual FString GetVerb() const override;` — IHttpRequest
- L26 _public prototype_ `virtual void SetVerb(const FString& InVerb) override;`
- L27 _public prototype_ `virtual void SetURL(const FString& InURL) override;`
- L28 _public prototype_ `virtual FString GetOption(const FName Option) const override;`
- L29 _public prototype_ `virtual void SetOption(const FName Option, const FString& OptionValue) override;`
- L30 _public prototype_ `virtual void SetContent(const TArray<uint8>& ContentPayload) override;`
- L31 _public prototype_ `virtual void SetContent(TArray<uint8>&& ContentPayload) override;`
- L32 _public prototype_ `virtual void SetContentAsString(const FString& ContentString) override;`
- L33 _public prototype_ `virtual bool SetContentAsStreamedFile(const FString& Filename) override;`
- L34 _public prototype_ `virtual bool SetContentFromStream(TSharedRef<FArchive, ESPMode::ThreadSafe> Stream) override;`
- L35 _public prototype_ `virtual bool SetResponseBodyReceiveStream(TSharedRef<FArchive> Stream) override;`
- L36 _public prototype_ `virtual void SetHeader(const FString& HeaderName, const FString& HeaderValue) override;`
- L37 _public prototype_ `virtual void AppendToHeader(const FString& HeaderName, const FString& AdditionalHeaderValue) override;`
- L38 _public prototype_ `virtual bool ProcessRequest() override;`
- L39 _public prototype_ `virtual void CancelRequest() override;`
- L40 _public prototype_ `virtual EHttpRequestStatus::Type GetStatus() const override;`
- L41 _public prototype_ `virtual EHttpFailureReason GetFailureReason() const override;`
- L42 _public prototype_ `virtual const FString& GetEffectiveURL() const override;`
- L43 _public prototype_ `virtual const FHttpResponsePtr GetResponse() const override;`
- L44 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L45 _public prototype_ `virtual float GetElapsedTime() const override;`
- L46 _public prototype_ `virtual void SetDelegateThreadPolicy(EHttpRequestDelegateThreadPolicy InThreadPolicy) override;`
- L47 _public prototype_ `virtual EHttpRequestDelegateThreadPolicy GetDelegateThreadPolicy() const override;`
- L48 _public prototype_ `virtual void SetPriority(EHttpRequestPriority InPriority) override;`
- L49 _public prototype_ `virtual EHttpRequestPriority GetPriority() const override;`
- L50 _public prototype_ `virtual void SetTimeout(float InTimeoutSecs) override;`
- L51 _public prototype_ `virtual void ClearTimeout() override;`
- L52 _public prototype_ `virtual void ResetTimeoutStatus() override;`
- L53 _public prototype_ `virtual TOptional<float> GetTimeout() const override;`
- L54 _public prototype_ `virtual void SetActivityTimeout(float InTimeoutSecs) override;`
- L55 _public prototype_ `virtual void ProcessRequestUntilComplete() override;`
- L57 _public function_ `FNullHttpRequest() : CompletionStatus(EHttpRequestStatus::NotStarted) , FailureReason(EHttpFailureReason::None) , ElapsedTime(0)`
- L62 _public prototype_ `virtual ~FNullHttpRequest() = default;`
- L65 _private prototype_ `void FinishedRequest();`
- L67 _private member_ `FString Url;`
- L68 _private member_ `FString EffectiveUrl;`
- L69 _private member_ `FString Verb;`
- L70 _private member_ `TArray<uint8> Payload;`
- L71 _private member_ `EHttpRequestStatus::Type CompletionStatus;`
- L72 _private member_ `EHttpFailureReason FailureReason;`
- L73 _private member_ `TMap<FString, FString> Headers;`
- L74 _private member_ `TMap<const FName, FString> Options;`
- L75 _private member_ `float ElapsedTime;`
- L76 _private member_ `TOptional<float> TimeoutSecs;`

#### class `FNullHttpResponse`  
`class FNullHttpResponse : public IHttpResponse`  
_L82-103_
- inherits: `IHttpResponse`
- desc: Null (mock) implementation of an HTTP request
- L85 _private prototype_ `virtual const FString& GetURL() const override;` — IHttpBase
- L86 _private prototype_ `virtual FString GetURLParameter(const FString& ParameterName) const override;`
- L87 _private prototype_ `virtual FString GetHeader(const FString& HeaderName) const override;`
- L88 _private prototype_ `virtual TArray<FString> GetAllHeaders() const override;`
- L89 _private prototype_ `virtual FString GetContentType() const override;`
- L90 _private prototype_ `virtual uint64 GetContentLength() const override;`
- L91 _private prototype_ `virtual const TArray<uint8>& GetContent() const override;`
- L93 _private prototype_ `virtual int32 GetResponseCode() const override;`
- L94 _private prototype_ `virtual FString GetContentAsString() const override;`
- L95 _private prototype_ `virtual FUtf8StringView GetContentAsUtf8StringView() const override;`
- L97 _private function_ `FNullHttpResponse()`
- L98 _private prototype_ `virtual ~FNullHttpResponse() = default;`
- L101 _private member_ `TArray<uint8> Payload;`
- L102 _private member_ `FString URL;`

### `Source/Runtime/Online/HTTP/Private/TransactionallySafeHttpRequest.h` (Private)


#### class `FTransactionallySafeHttpRequest`  
`class FTransactionallySafeHttpRequest : public IHttpRequest`  
_L16-81_
- inherits: `IHttpRequest`
- desc: Wraps a FPlatformHttp request when one is created inside an AutoRTFM transaction. Basic getters and setters are cached and played back when the transaction succeeds. Once the transaction is committed, a real HttpRequest is instantiated and all calls are passed through as-is.
- L19 _public prototype_ `FTransactionallySafeHttpRequest();`
- L20 _public prototype_ `virtual ~FTransactionallySafeHttpRequest() = default;`
- L23 _public prototype_ `const FString& GetURL() const override;` — IHttpBase
- L24 _public prototype_ `FString GetURLParameter(const FString& ParameterName) const override;`
- L25 _public prototype_ `FString GetHeader(const FString& HeaderName) const override;`
- L26 _public prototype_ `TArray<FString> GetAllHeaders() const override;`
- L27 _public prototype_ `FString GetContentType() const override;`
- L28 _public prototype_ `uint64 GetContentLength() const override;`
- L29 _public prototype_ `const TArray<uint8>& GetContent() const override;`
- L32 _public prototype_ `FString GetVerb() const override;` — IHttpRequest
- L33 _public prototype_ `void SetVerb(const FString& InVerb) override;`
- L34 _public prototype_ `void SetURL(const FString& InURL) override;`
- L35 _public prototype_ `FString GetOption(const FName Option) const override;`
- L36 _public prototype_ `void SetOption(const FName Option, const FString& OptionValue) override;`
- L37 _public prototype_ `void SetContent(const TArray<uint8>& ContentPayload) override;`
- L38 _public prototype_ `void SetContent(TArray<uint8>&& ContentPayload) override;`
- L39 _public prototype_ `void SetContentAsString(const FString& ContentString) override;`
- L40 _public prototype_ `bool SetContentAsStreamedFile(const FString& Filename) override;`
- L41 _public prototype_ `bool SetContentFromStream(TSharedRef<FArchive, ESPMode::ThreadSafe> Stream) override;`
- L42 _public prototype_ `bool SetResponseBodyReceiveStream(TSharedRef<FArchive> Stream) override;`
- L43 _public prototype_ `void SetHeader(const FString& HeaderName, const FString& HeaderValue) override;`
- L44 _public prototype_ `void AppendToHeader(const FString& HeaderName, const FString& AdditionalHeaderValue) override;`
- L45 _public prototype_ `bool ProcessRequest() override;`
- L46 _public prototype_ `void CancelRequest() override;`
- L47 _public prototype_ `EHttpRequestStatus::Type GetStatus() const override;`
- L48 _public prototype_ `EHttpFailureReason GetFailureReason() const override;`
- L49 _public prototype_ `const FString& GetEffectiveURL() const override;`
- L50 _public prototype_ `const FHttpResponsePtr GetResponse() const override;`
- L51 _public prototype_ `void Tick(float DeltaSeconds) override;`
- L52 _public prototype_ `float GetElapsedTime() const override;`
- L53 _public prototype_ `void SetDelegateThreadPolicy(EHttpRequestDelegateThreadPolicy InThreadPolicy) override;`
- L54 _public prototype_ `EHttpRequestDelegateThreadPolicy GetDelegateThreadPolicy() const override;`
- L55 _public prototype_ `virtual void SetPriority(EHttpRequestPriority InPriority) override;`
- L56 _public prototype_ `virtual EHttpRequestPriority GetPriority() const override;`
- L57 _public prototype_ `void SetTimeout(float InTimeoutSecs) override;`
- L58 _public prototype_ `void ClearTimeout() override;`
- L59 _public prototype_ `void ResetTimeoutStatus() override;`
- L60 _public prototype_ `TOptional<float> GetTimeout() const override;`
- L61 _public prototype_ `void SetActivityTimeout(float InTimeoutSecs) override;`
- L62 _public prototype_ `void ProcessRequestUntilComplete() override;`
- L64 _public prototype_ `FHttpRequestCompleteDelegate& OnProcessRequestComplete() override;`
- L65 _public prototype_ `FHttpRequestProgressDelegate64& OnRequestProgress64() override;`
- L66 _public prototype_ `FHttpRequestWillRetryDelegate& OnRequestWillRetry() override;`
- L67 _public prototype_ `FHttpRequestHeaderReceivedDelegate& OnHeaderReceived() override;`
- L68 _public prototype_ `FHttpRequestStatusCodeReceivedDelegate& OnStatusCodeReceived() override;`
- L77 _private member_ `TSharedPtr<IHttpRequest> InnerRequest;` — The InnerRequest can be one of two things: * An FClosedHttpRequest, which is created when a transactionally-safe HTTP request is created from inside of a transaction. A closed request will queue up work and then play it back into a PlatformRequest when the transaction commits. * An real request created from a call to FPlatformHttp::ConstructRequest. This replaces the original InnerRequest once we reach the open.

### `Source/Runtime/Online/HTTP/Public/Android/AndroidPlatformHttp.h` (Public)


#### class `FAndroidPlatformHttp`  
`class FAndroidPlatformHttp : public FGenericPlatformHttp`  
_L9-59_
- inherits: `FGenericPlatformHttp`
- desc: Platform specific Http implementations
- L16 _public prototype_ `static void Init();` — Platform initialization step
- L23 _public prototype_ `static FHttpManager* CreatePlatformHttpManager();` — Creates a platform-specific HTTP manager. @return NULL if default implementation is to be used
- L28 _public prototype_ `static void Shutdown();` — Platform shutdown step
- L35 _public prototype_ `static IHttpRequest* ConstructRequest();` — Creates a new Http request instance for the current platform @return request object
- L42 _public prototype_ `static FString GetConfiguredProxyAddress();` — Get the proxy address from the highest-priority available source: command-line (-httpproxy=), INI ([HTTP] HttpProxyAddress), or OS proxy settings. It's to ensure FAndroidPlatformHttp::GetOperatingSystemProxyAddress() is called.
- L49 _public prototype_ `static TOptional<FString> GetOperatingSystemProxyAddress();` — Get the proxy address specified by the operating system @return optional FString: If unset: we are unable to get information from the operating system. If set: the proxy address set by the operating system (may be blank)
- L58 _public prototype_ `static bool IsOperatingSystemProxyInformationSupported();` — Check if getting proxy information from the current operating system is supported Useful for "Network Settings" type pages.  GetProxyAddress may return an empty or populated string but that does not imply the operating system does or does not support proxies (or that it has been implemented here) @return true if we are able to get proxy information from the current operating system, false if not

#### Free symbols / members of external scopes

- L62 _typedef_ `typedef FAndroidPlatformHttp FPlatformHttp;`

### `Source/Runtime/Online/HTTP/Public/Apple/ApplePlatformHttp.h` (Public)


#### class `FApplePlatformHttp`  
`class FApplePlatformHttp : public FGenericPlatformHttp`  
_L13-56_
- inherits: `FGenericPlatformHttp`
- desc: Platform specific Http implementations
- L19 _public prototype_ `static void Init();` — Platform initialization step
- L26 _public prototype_ `static FHttpManager* CreatePlatformHttpManager();` — Creates a platform-specific HTTP manager. @return NULL if default implementation is to be used
- L31 _public prototype_ `static void Shutdown();` — Platform shutdown step
- L38 _public prototype_ `static IHttpRequest* ConstructRequest();` — Creates a new Http request instance for the current platform @return request object
- L40 _public prototype_ `static bool IsBackgroundRequestFeatureEnabled();`
- L42 _public prototype_ `static TSharedPtr<class FAppleHttpRequest>& Add(NSURLSessionTask* Task, const TSharedPtr<class FAppleHttpRequest>& Request);`
- L43 _public prototype_ `static bool Find(NSURLSessionTask* Task, OUT TSharedPtr<class FAppleHttpRequest>& Request);`
- L44 _public prototype_ `static bool RemoveAndCopyValue(NSURLSessionTask* Task, OUT TSharedPtr<class FAppleHttpRequest>& Request);`
- L48 _private member_ `static inline NSURLSession* Session = nullptr;` — Session used to create Apple based requests
- L49 _private member_ `static inline NSURLSession* BackgroundSession = nullptr;`
- L51 _private member_ `static FRWLock TaskRequestMapLock;`
- L52 _private member_ `static TMap<NSURLSessionTask*, TSharedPtr<class FAppleHttpRequest>> TaskRequestMap;`
- L54 _private prototype_ `static void InitWithNSUrlSession();`
- L55 _private prototype_ `static void ShutdownWithNSUrlSession();`

#### Free symbols / members of external scopes

- L59 _typedef_ `typedef FApplePlatformHttp FPlatformHttp;`

### `Source/Runtime/Online/HTTP/Public/GenericPlatform/GenericPlatformHttp.h` (Public)


#### class `FDefaultUserAgentBuilder`  
`class FDefaultUserAgentBuilder`  
_L21-51_
- desc: Utility structure to help with building the HTTP user agent string.
- L24 _public prototype_ `FDefaultUserAgentBuilder();`
- L28 _public prototype_ `FString BuildUserAgentString(const TSet<FString>* AllowedProjectCommentsFilter = nullptr, const TSet<FString>* AllowedPlatformCommentsFilter = nullptr) const;` — Build the user agent string. Passing a filter will limit the comments to only those allowed. Passing nullptr for a filter implies that all comments are allowed.
- L30 _public prototype_ `void SetProjectName(const FString& InProjectName);`
- L31 _public prototype_ `void SetProjectVersion(const FString& InProjectVersion);`
- L32 _public prototype_ `void AddProjectComment(const FString& InComment);`
- L33 _public prototype_ `void SetPlatformName(const FString& InPlatformName);`
- L34 _public prototype_ `void SetPlatformVersion(const FString& InPlatformVersion);`
- L35 _public prototype_ `void AddPlatformComment(const FString& InComment);`
- L39 _public prototype_ `uint32 GetAgentVersion() const;` — Get the builder version. The version is used for tracking app changes to the default user agent and is not included in the user agent string.
- L42 _private prototype_ `static FString BuildCommentString(const TArray<FString>& Comments, const TSet<FString>* AllowedCommentsFilter);`
- L44 _private member_ `FString ProjectName;`
- L45 _private member_ `FString ProjectVersion;`
- L46 _private member_ `TArray<FString> ProjectComments;`
- L47 _private member_ `FString PlatformName;`
- L48 _private member_ `FString PlatformVersion;`
- L49 _private member_ `TArray<FString> PlatformComments;`
- L50 _private member_ `uint32 AgentVersion;`

#### class `FGenericPlatformHttp`  
`class FGenericPlatformHttp`  
_L57-259_
- desc: Platform specific Http implementations Intended usage is to use FPlatformHttp instead of FGenericPlatformHttp
- L64 _public prototype_ `static void Init();` — Platform initialization step
- L71 _public function_ `static FHttpManager* CreatePlatformHttpManager()` — Creates a platform-specific HTTP manager. @return nullptr if default implementation is to be used
- L79 _public prototype_ `static void Shutdown();` — Platform shutdown step
- L84 _public function_ `static void ShutdownPlatformCustomSsl()` — Platform shutdown custom ssl if supported
- L91 _public prototype_ `static IHttpRequest* ConstructRequest();` — Creates a new Http request instance for the current platform @return request object
- L99 _public prototype_ `static FString UrlEncode(const FStringView UnencodedString);` — Returns a percent-encoded version of the passed in string @param UnencodedString The unencoded string to convert to percent-encoding @return The percent-encoded string
- L107 _public prototype_ `static FString UrlDecode(const FStringView EncodedString);` — Returns a decoded version of the percent-encoded passed in string @param EncodedString The percent encoded string to convert to string @return The decoded string
- L115 _public prototype_ `static FString HtmlEncode(const FStringView UnencodedString);` — Returns the &lt; &gt...etc encoding for strings between HTML elements. @param UnencodedString The unencoded string to convert to html encoding. @return The html encoded string
- L122 _public prototype_ `static FString GetUrlDomainAndPort(const FStringView Url);` — Returns the domain and port portion of the URL, e.g., "a.b.c:d" of "http://a.b.c:d/e" @param Url the URL to return the domain and port of @return the domain and port of the specified URL
- L129 _public prototype_ `static FString GetUrlDomain(const FStringView Url);` — Returns the domain portion of the URL, e.g., "a.b.c" of "http://a.b.c:d/e" @param Url the URL to return the domain of @return the domain of the specified URL
- L136 _public prototype_ `static FString GetUrlBase(const FStringView Url);` — Returns the base of the URL, e.g., "http://a.b.c:d" of "http://a.b.c:d/e" @param Url the URL to return the base of @return the base of the specified URL
- L142 _public prototype_ `static FString GetMimeType(const FString& FilePath);` — Get the mime type for the file @return the mime type for the file.
- L152 _public prototype_ `static FString GetDefaultUserAgent();` — Returns the default User-Agent string to use in HTTP requests. Requests that explicitly set the User-Agent header will not use this value. The default User-Agent is built in the format "project/version (comments) platform/OS version (comments)" @return the default User-Agent string that requests should use.
- L153 _public prototype_ `static FString EscapeUserAgentString(const FString& UnescapedString);`
- L158 _public prototype_ `static void AddDefaultUserAgentProjectComment(const FString& Comment);` — Add a comment to be included in the project section of the default User-Agent string.
- L163 _public prototype_ `static void AddDefaultUserAgentPlatformComment(const FString& Comment);` — Add a comment to be included in the platform section of the default User-Agent string.
- L171 _public prototype_ `static uint32 GetDefaultUserAgentVersion();` — Get the version of the default user agent. The version is incremented any time the default user agent is changed. Used to invalidate any cached user agent value. @return the current version of the default user agent.
- L177 _public prototype_ `static FDefaultUserAgentBuilder GetDefaultUserAgentBuilder();` — Gets a copy of the values used to build the default user agent string. Used for modifying default user agent values before sending HTTP requests.
- L193 _public prototype_ `static FString GetConfiguredProxyAddress();` — Get the configured proxy address, using the same precedence as the HTTP module: 1. Command-line: -httpproxy= 2. INI: [HTTP] HttpProxyAddress 3. Operating system proxy @return the proxy address, or an empty string if none is configured
- L200 _public prototype_ `static TOptional<FString> GetOperatingSystemProxyAddress();` — Get the proxy address specified by the operating system @return optional FString: If unset: we are unable to get information from the operating system. If set: the proxy address set by the operating system (may be blank)
- L209 _public prototype_ `static bool IsOperatingSystemProxyInformationSupported();` — Check if getting proxy information from the current operating system is supported Useful for "Network Settings" type pages.  GetProxyAddress may return an empty or populated string but that does not imply the operating system does or does not support proxies (or that it has been implemented here) @return true if we are able to get proxy information from the current operating system, false if not
- L218 _public prototype_ `static TOptional<FString> GetProxyAddressFromConfig();` — Internal helper that checks command-line and INI config for a proxy address. Returns the proxy if found (set), or unset if neither cmdline nor INI has a proxy. Callers use this to determine whether to fallback to OS-specific proxy queries. @return Set with proxy address if found in cmdline/INI, unset otherwise
- L223 _public prototype_ `static bool IsURLEncoded(const TArray<uint8>& Payload);` — Helper function for checking if a byte array is in URL encoded format.
- L232 _public prototype_ `static TOptional<FString> GetUrlParameter(const FStringView Url, const FStringView ParameterName);` — Extract the URL-Decoded value of the specified ParameterName from Url. An unset return means the parameter was not present in Url, while an empty value means it was present, but had no value. @param Url The URL to parse for ParameterName @param ParameterName The parameter name to look for @return If ParameterName was found, the string value of its value (in URL Decoded format), otherwise the return value is unset
- L239 _public prototype_ `static TOptional<uint16> GetUrlPort(const FStringView Url);` — Extract the Port part of a URL, or an unset object if there was non specified. Example: "http://example.org:23/" would return 23, while "https://example.org/" would return an unset object @param Url The URL to parse for a Port
- L250 _public prototype_ `static FString GetUrlPath(const FStringView Url, const bool bIncludeQueryString = false, const bool bIncludeFragment = false);` — Extract the Path portion of a URL, optionally including the Query String, and optionally including the Fragment (when also including the query string.) The return value will always contain a leading forward slash, even if no path is found. If bIncludeFragment is set true, bIncludeQueryString must also be true @param Url The URL to parse for a Path @param bIncludeQueryString include the URL's query string in the return value (if one is found) @param bIncludeFragment include the URL's fragement in the return value (if one is found)
- L258 _public prototype_ `static TOptional<bool> IsSecureProtocol(const FStringView Url);` — Check the protocol of the provided URL to determine if this is for a secure connection (HTTPS, WSS, etc) @param The URL to check for a scheme @return True if secure, false if insecure, unset if unknown

### `Source/Runtime/Online/HTTP/Public/GenericPlatform/HttpRequestImpl.h` (Public)


#### class `FHttpRequestImpl`  
`class FHttpRequestImpl : public IHttpRequest`  
_L11-48_
- inherits: `IHttpRequest`
- desc: Contains implementation of some common functions that don't vary between implementation
- L15 _public prototype_ `virtual FHttpRequestCompleteDelegate& OnProcessRequestComplete() override;` — IHttpRequest
- L16 _public prototype_ `virtual FHttpRequestProgressDelegate64& OnRequestProgress64() override;`
- L17 _public prototype_ `virtual FHttpRequestStatusCodeReceivedDelegate& OnStatusCodeReceived() override;`
- L18 _public prototype_ `virtual FHttpRequestHeaderReceivedDelegate& OnHeaderReceived() override;`
- L19 _public prototype_ `virtual FHttpRequestWillRetryDelegate& OnRequestWillRetry() override;`
- L24 _public prototype_ `virtual void Shutdown();` — Clear callbacks before http module get deleted
- L31 _protected prototype_ `void BroadcastResponseHeadersReceived();` — Broadcast all of our response's headers as having been received Used when we don't know when we receive headers in our HTTP implementation
- L35 _protected member_ `FHttpRequestCompleteDelegate RequestCompleteDelegate;` — Delegate that will get called once request completes or on any error
- L38 _protected member_ `FHttpRequestProgressDelegate64 RequestProgressDelegate64;` — Delegate that will get called once per tick with bytes downloaded so far
- L41 _protected member_ `FHttpRequestStatusCodeReceivedDelegate StatusCodeReceivedDelegate;` — Delegate that will get called when status code received
- L44 _protected member_ `FHttpRequestHeaderReceivedDelegate HeaderReceivedDelegate;` — Delegate that will get called for each new header received
- L47 _protected member_ `FHttpRequestWillRetryDelegate OnRequestWillRetryDelegate;` — Delegate that will get called when request will be retried

### `Source/Runtime/Online/HTTP/Public/GenericPlatform/HttpRequestPayload.h` (Public)


#### class `FRequestPayload`  
`class FRequestPayload`  
_L16-49_
- desc: Abstraction that encapsulates the location of a request payload
- L19 _public prototype_ `virtual ~FRequestPayload() = default;`
- L21 _public prototype_ `virtual uint64 GetContentLength() const = 0;` — Get the total content length of the request payload in bytes
- L23 _public prototype_ `virtual const TArray<uint8>& GetContent() const = 0;` — Return a reference to the underlying memory buffer. Only valid for in-memory request payloads
- L25 _public prototype_ `virtual bool IsURLEncoded() const = 0;` — Check if the request payload is URL encoded. This check is only performed for in-memory request payloads
- L33 _public prototype_ `virtual size_t FillOutputBuffer(void* OutputBuffer, size_t MaxOutputBufferSize, size_t SizeAlreadySent) = 0;` — Read part of the underlying request payload into an output buffer. @param OutputBuffer - the destination memory address where the payload should be copied @param MaxOutputBufferSize - capacity of OutputBuffer in bytes @param SizeAlreadySent - how much of payload has previously been sent. @return Returns the number of bytes copied into OutputBuffer
- L42 _public prototype_ `virtual size_t FillOutputBuffer(TArrayView<uint8> OutputBuffer, size_t SizeAlreadySent) = 0;` — Read part of the underlying request payload into an output buffer. @param OutputBuffer - the destination memory address where the payload should be copied @param MaxOutputBufferSize - capacity of OutputBuffer in bytes @param SizeAlreadySent - how much of payload has previously been sent. @return Returns the number of bytes copied into OutputBuffer
- L45 _public prototype_ `virtual bool Open() = 0;` — Open the upload payload before start
- L48 _public prototype_ `virtual void Close() = 0;` — Close the upload payload when the http request don't need to use it anymore

#### class `FRequestPayloadInFileStream`  
`class FRequestPayloadInFileStream : public FRequestPayload`  
_L51-69_
- inherits: `FRequestPayload`
- L54 _public prototype_ `FRequestPayloadInFileStream(const FString& InFilename);`
- L55 _public prototype_ `FRequestPayloadInFileStream(TSharedRef<FArchive> InFile, bool bInCloseWhenComplete = false);`
- L56 _public prototype_ `virtual ~FRequestPayloadInFileStream();`
- L57 _public prototype_ `virtual uint64 GetContentLength() const override;`
- L58 _public prototype_ `virtual const TArray<uint8>& GetContent() const override;`
- L59 _public prototype_ `virtual bool IsURLEncoded() const override;`
- L60 _public prototype_ `virtual size_t FillOutputBuffer(void* OutputBuffer, size_t MaxOutputBufferSize, size_t SizeAlreadySent) override;`
- L61 _public prototype_ `virtual size_t FillOutputBuffer(TArrayView<uint8> OutputBuffer, size_t SizeAlreadySent) override;`
- L62 _public prototype_ `virtual bool Open() override;`
- L63 _public prototype_ `virtual void Close() override;`
- L66 _private member_ `FString Filename;`
- L67 _private member_ `TSharedPtr<FArchive> File;`
- L68 _private member_ `bool bCloseWhenComplete = false;`

#### class `FRequestPayloadInMemory`  
`class FRequestPayloadInMemory : public FRequestPayload`  
_L71-86_
- inherits: `FRequestPayload`
- L74 _public prototype_ `FRequestPayloadInMemory(const TArray<uint8>& Array);`
- L75 _public prototype_ `FRequestPayloadInMemory(TArray<uint8>&& Array);`
- L76 _public prototype_ `virtual ~FRequestPayloadInMemory();`
- L77 _public prototype_ `virtual uint64 GetContentLength() const override;`
- L78 _public prototype_ `virtual const TArray<uint8>& GetContent() const override;`
- L79 _public prototype_ `virtual bool IsURLEncoded() const override;`
- L80 _public prototype_ `virtual size_t FillOutputBuffer(void* OutputBuffer, size_t MaxOutputBufferSize, size_t SizeAlreadySent) override;`
- L81 _public prototype_ `virtual size_t FillOutputBuffer(TArrayView<uint8> OutputBuffer, size_t SizeAlreadySent) override;`
- L82 _public prototype_ `virtual bool Open() override;`
- L83 _public prototype_ `virtual void Close() override;`
- L85 _private member_ `TArray<uint8> Buffer;`

### `Source/Runtime/Online/HTTP/Public/Http.h` (Public)


#### Free symbols / members of external scopes

- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttp, Display, All);`

### `Source/Runtime/Online/HTTP/Public/HttpConstants.h` (Public)


#### struct `FHttpConstants`  
`struct FHttpConstants`  
_L12-60_
- desc: Universal HTTP Constants
- L15 _public member_ `static const TCHAR* const AUTH_BASIC;` — Basic auth
- L17 _public member_ `static const TCHAR* const AUTH_BEARER;` — Bearer auth
- L20 _public member_ `static const TCHAR* const VERB_DELETE;` — DELETE
- L22 _public member_ `static const TCHAR* const VERB_GET;` — GET
- L24 _public member_ `static const TCHAR* const VERB_HEAD;` — HEAD
- L26 _public member_ `static const TCHAR* const VERB_PATCH;` — PATCH
- L28 _public member_ `static const TCHAR* const VERB_POST;` — POST
- L30 _public member_ `static const TCHAR* const VERB_PUT;` — PUT
- L33 _public member_ `static const TCHAR* const HEADER_ACCEPT;` — Accept
- L35 _public member_ `static const TCHAR* const HEADER_ACCEPT_ENCODING;` — Accept-Encoding
- L37 _public member_ `static const TCHAR* const HEADER_AUTHORIZATION;` — Authorization
- L39 _public member_ `static const TCHAR* const HEADER_CONTENT_LENGTH;` — Content-Length
- L41 _public member_ `static const TCHAR* const HEADER_CONTENT_TYPE;` — Content-Type
- L43 _public member_ `static const TCHAR* const HEADER_DATE;` — Server Date
- L45 _public member_ `static const TCHAR* const HEADER_USER_AGENT;` — User Agent
- L48 _public member_ `static const TCHAR* const MEDIATYPE_JSON;` — application/json
- L50 _public member_ `static const TCHAR* const MEDIATYPE_FORM_URLENCODED;` — application/x-www-form-urlencoded
- L52 _public member_ `static const TCHAR* const MEDIATYPE_OCTET_STREAM;` — application/octet-stream
- L55 _public member_ `static const TCHAR* const MEDIAENCODING_GZIP;` — gzip
- L58 _public member_ `static const TCHAR* const VERSION_2TLS;` — version
- L59 _public member_ `static const TCHAR* const VERSION_1_1;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HTTP_API`

### `Source/Runtime/Online/HTTP/Public/HttpFwd.h` (Public)


#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> FHttpRequestPtr;`
- L13 _typedef_ `typedef TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;`
- L15 _typedef_ `typedef TSharedRef<IHttpRequest, ESPMode::ThreadSafe> FHttpRequestRef;`
- L16 _typedef_ `typedef TSharedRef<IHttpResponse, ESPMode::ThreadSafe> FHttpResponseRef;`
- L18 _namespace_ `namespace FHttpRetrySystem`
- L20 _typedef_ `using RetryLimitCountType = uint32;` (scope `FHttpRetrySystem`)
- L21 _typedef_ `using RetryTimeoutRelativeSecondsType = double;` (scope `FHttpRetrySystem`)
- L23 _typedef_ `using FRandomFailureRateSetting = TOptional<float>;` (scope `FHttpRetrySystem`)
- L24 _typedef_ `using FRetryLimitCountSetting = TOptional<RetryLimitCountType>;` (scope `FHttpRetrySystem`)
- L25 _typedef_ `using FRetryTimeoutRelativeSecondsSetting = TOptional<RetryTimeoutRelativeSecondsType>;` (scope `FHttpRetrySystem`)
- L26 _typedef_ `using FRetryResponseCodes = TSet<int32>;` (scope `FHttpRetrySystem`)
- L27 _typedef_ `using FRetryVerbs = TSet<FName>;` (scope `FHttpRetrySystem`)
- L30 _typedef_ `using FRetryDomainsPtr = TSharedPtr<FRetryDomains, ESPMode::ThreadSafe>;` (scope `FHttpRetrySystem`)

### `Source/Runtime/Online/HTTP/Public/HttpManager.h` (Public)


#### enum `EHttpFlushReason`  
`enum class EHttpFlushReason : uint8`  
_L27-36_
- L30 _public enumerator_ `Default` — Reasonable, typically higher time limits
- L32 _public enumerator_ `Shutdown` — Shorter time limits depending on platform requirements
- L34 _public enumerator_ `FullFlush` — Infinite wait, should only be used in non-game scenarios where longer waits are acceptable
- L35 _public enumerator_ `Count`

#### struct `FHttpStatsPlatformMemoryPool`  
`struct FHttpStatsPlatformMemoryPool`  
_L52-57_
- L54 _public member_ `uint64 PoolSize = 0;`
- L55 _public member_ `uint64 MaxInUseSize = 0;`
- L56 _public member_ `uint64 CurrentInUseSize = 0;`

#### struct `FHttpStatsPlatform`  
`struct FHttpStatsPlatform`  
_L59-64_
- L61 _public member_ `FHttpStatsPlatformMemoryPool MemoryPoolConnection;`
- L62 _public member_ `FHttpStatsPlatformMemoryPool MemoryPoolSsl;`
- L63 _public member_ `FHttpStatsPlatformMemoryPool MemoryPoolNet;`

#### struct `FHttpStats`  
`struct FHttpStats`  
_L66-119_
- L72 _public member_ `std::atomic<int32> RequestsInQueue = 0;` — The number of requests waiting in queue in http manager
- L74 _public member_ `std::atomic<int32> RequestsInFlight = 0;` — The number of requests in flight in http manager
- L76 _public member_ `std::atomic<float> MaxTimeToConnect = -1.0f;` — The max time to successfully connect the backend
- L78 _public member_ `std::atomic<uint32> MaxRequestsInQueue = 0;` — The max waiting queue in http manager
- L80 _public member_ `std::atomic<uint32> MaxRequestsInFlight = 0;` — The max number of requests in flight in http manager
- L82 _public member_ `std::atomic<float> MaxTimeToWaitInQueue = 0.0f;` — The max waiting time in queue of http manager
- L84 _public member_ `std::atomic<int64> TotalDownloadedBytes = 0;` — The total bytes downloaded so far
- L86 _public member_ `std::atomic<int64> BandwidthMbps = 0;` — Approximate download bandwidth used
- L88 _public member_ `std::atomic<int64> HttpDurationMsAvg = 0;` — Avg duration (in milliseconds) from request to response
- L90 _public member_ `TOptional<FHttpStatsPlatform> PlatformStats;` — The optional http stats on specific platform
- L96 _public member_ `std::atomic<int64> RequestResults[static_cast<uint8>(EHttpFailureReason::Count)] = {};` — Request completion counters indexed by EHttpFailureReason. Index 0 (None) counts succeeded requests; indices 1+ count each failure reason.
- L98 _public function_ `FHttpStats()`
- L102 _public function_ `FHttpStats(const FHttpStats& Other) : RequestsInQueue(Other.RequestsInQueue.load()) , RequestsInFlight(Other.RequestsInFlight.load()) , MaxTimeToConnect(Other.MaxTimeToConnect.load()) , MaxRequestsInQueue(Other.MaxRequestsInQueue.load()) , MaxRequestsInFlight(Other.MaxRequestsInFlight.load()) , MaxTimeToWaitInQueue(Other.MaxTimeToWaitInQueue.load()) , TotalDownloadedBytes(Other.TotalDownloadedBytes.load()) , BandwidthMbps(Other.BandwidthMbps.load()) , HttpDurationMsAvg(Other.HttpDurationMsAvg.load()) , PlatformStats(Other.PlatformStats)`

#### class `FHttpManager`  
`class FHttpManager : public FTSTickerObjectBase`  
_L124-484_
- inherits: `FTSTickerObjectBase`
- desc: Manages Http request that are currently being processed
- L134 _public prototype_ `FHttpManager();` — Constructor
- L139 _public prototype_ `virtual ~FHttpManager();` — Destructor
- L144 _public prototype_ `void Initialize();` — Initialize
- L149 _public prototype_ `void Shutdown();` — Shutdown logic should be called before quiting
- L156 _public prototype_ `void SetRequestAddedDelegate(const FHttpManagerRequestAddedDelegate& Delegate);` — Set a delegate to be triggered when an http request added to http manager. NOTE: The delegate can be triggered from different threads, depends on which thread the request created. So make sure the delegate set here is thread-safe.
- L163 _public prototype_ `void SetRequestCompletedDelegate(const FHttpManagerRequestCompletedDelegate& Delegate);` — Set a delegate to be triggered when an http request completed. NOTE: The delegate can be triggered from different threads, it depends on the delegate policy set to each http request. So make sure the delegate set here is thread-safe.
- L171 _public prototype_ `void RemoveRequest(const FHttpRequestRef& Request);` — Removes an Http request instance from the manager Presumably it is done being processed @param Request - the request object to remove
- L180 _public prototype_ `bool IsValidRequest(const IHttpRequest* RequestPtr) const;` — Find an Http request in the lists of current valid requests @param RequestPtr - ptr to the http request object to find @return true if the request is being tracked, false if not
- L187 _public prototype_ `void Flush(EHttpFlushReason FlushReason);` — Block until all pending requests are finished processing @param FlushReason the flush reason will influence times waited to cancel ongoing http requests
- L196 _public prototype_ `bool Tick(float DeltaSeconds) override;` — FTSTicker callback @param DeltaSeconds - time in seconds since the last tick @return false if no longer needs ticking
- L203 _public prototype_ `virtual void FlushTick(float DeltaSeconds);` — Tick called during Flush @param DeltaSeconds - time in seconds since the last tick
- L210 _public prototype_ `void AddThreadedRequest(const TSharedRef<FHttpRequestCommon, ESPMode::ThreadSafe>& Request);` — Add a http request to be executed on the http thread @param Request - the request object to add
- L217 _public prototype_ `void CancelThreadedRequest(const TSharedRef<FHttpRequestCommon, ESPMode::ThreadSafe>& Request);` — Mark a threaded http request as cancelled to be removed from the http thread @param Request - the request object to cancel
- L224 _public prototype_ `void DumpRequests(FOutputDevice& Ar) const;` — List all of the Http requests currently being processed @param Ar - output device to log with
- L231 _public prototype_ `virtual bool SupportsDynamicProxy() const;` — Method to check dynamic proxy setting support. @returns Whether this http implementation supports dynamic proxy setting.
- L240 _public prototype_ `void SetCorrelationIdMethod(TFunction<FString()> InCorrelationIdMethod);` — Set the method used to set a Correlation id on each request, if one is not already specified. This method allows you to override the Engine default method. @param InCorrelationIdMethod The method to use when sending a request, if no Correlation id is already set
- L247 _public prototype_ `FString CreateCorrelationId() const;` — Create a new correlation id for a request @return The new correlationid string
- L256 _public prototype_ `bool IsDomainAllowed(const FString& Url) const;` — Determine if the domain is allowed to be accessed @param Url the path to check domain on @return true if domain is allowed
- L263 _public prototype_ `static TFunction<FString()> GetDefaultCorrelationIdMethod();` — Get the default method for creating new correlation ids for a request @return The default correlationid creation method
- L268 _public prototype_ `virtual void OnBeforeFork();` — Inform that HTTP Manager that we are about to fork(). Will block to flush all outstanding http requests
- L273 _public prototype_ `virtual void OnAfterFork();` — Inform that HTTP Manager that we have completed a fork(). Must be called in both the client and parent process
- L278 _public prototype_ `virtual void OnEndFramePostFork();` — Inform the HTTP Manager that we finished ticking right after forking. Only called on the forked process
- L284 _public prototype_ `virtual void UpdateConfigs();` — Update configuration. Called when config has been updated and we need to apply any changes.
- L291 _public prototype_ `void AddGameThreadTask(TFunction<void()>&& Task, float Delay = 0.0f);` — Add task to be ran on the game thread next tick @param Task The task to be ran next tick
- L300 _public prototype_ `TSharedPtr<IHttpTaskTimerHandle> AddHttpThreadTask(TFunction<void()>&& Task, float InDelay = 0.0f);` — Add task to be ran on the http thread @param Task The task to be ran @param InDelay The delay to wait before running the task @return The handle of the timer, which could be used to remove the task before it's triggered
- L307 _public prototype_ `void RemoveHttpThreadTask(TSharedPtr<IHttpTaskTimerHandle> HttpTaskTimerHandle);` — Remove the task from the http thread before it's triggered @param HttpTaskTimerHandle The handle of the timer
- L314 _public function_ `void SetURLRequestFilter(const UE::Core::FURLRequestFilter& InURLRequestFilter)` — Set url request filter through code, instead of setting it through config. @param InURLRequestFilter The request filter to set
- L316 _public function_ `FHttpStats GetHttpStats() const`
- L324 _protected prototype_ `virtual FHttpThreadBase* CreateHttpThread();` — Create HTTP thread object @return the HTTP thread object
- L326 _protected prototype_ `void ReloadFlushTimeLimits();`
- L328 _protected prototype_ `bool HasAnyBoundDelegate() const;`
- L330 _protected prototype_ `void UpdateUrlPatternsToInspect(IConsoleVariable* CVar);`
- L331 _protected prototype_ `void UpdateUrlPatternsToDisableFailedLog(IConsoleVariable* CVar);`
- L332 _protected prototype_ `void UpdateUrlPatternsToMockResponse(IConsoleVariable* CVar);`
- L336 _protected member_ `TArray<FHttpRequestRef> Requests;` — List of Http requests that are actively being processed
- L338 _protected member_ `FHttpThreadBase* Thread;`
- L341 _protected member_ `TFunction<FString()> CorrelationIdMethod;` — This method will be called to generate a CorrelationId on all requests being sent if one is not already set
- L344 _protected member_ `FTSTicker GameThreadTicker;` — Ticker to run game thread tasks
- L345 _protected member_ `FCriticalSection GameThreadTickerLock;`
- L348 _protected member_ `bool bFlushing;` — This variable is set to true in Flush(EHttpFlushReason), and prevents new Http requests from being launched
- L351 _protected member_ `FHttpManagerRequestAddedDelegate RequestAddedDelegate;` — Delegate that will get called once request added
- L354 _protected member_ `FHttpManagerRequestCompletedDelegate RequestCompletedDelegate;` — Delegate that will get called when a request completes
- L357 _protected member_ `UE::Core::FURLRequestFilter URLRequestFilter;` — Url request filter, if specified in the config, it will launch http request only when the url is in the allowlist
- L383 _protected member_ `TMap<EHttpFlushReason, FHttpFlushTimeLimit> FlushTimeLimitsMap;`
- L385 _protected member_ `FHttpStats HttpStats;`
- L398 _protected member_ `FHttpStatsHistory HttpStatsHistory;`
- L400 _protected member_ `bool bUseEventLoop = true;`
- L402 _protected member_ `TArray<FString> UrlPatternsToInspect;`
- L403 _protected member_ `mutable FCriticalSection UrlPatternsToInspectCriticalSection;`
- L405 _protected member_ `TArray<FString> UrlPatternsToDisableFailedLog;`
- L406 _protected member_ `mutable FCriticalSection UrlPatternsToDisableFailedLogCriticalSection;`
- L409 _protected member_ `mutable FCriticalSection ThreadsCompletingRequestCriticalSection;`
- L410 _protected member_ `TMap<uint32, bool> ThreadsCompletingRequest;`
- L428 _protected member_ `mutable FCriticalSection RequestLock;` — Used to lock access to add/remove/find requests
- L431 _protected member_ `FCriticalSection CompletedRequestLock;` — Used to lock access to get completed requests
- L438 _protected prototype_ `void BroadcastHttpRequestCompleted(const FHttpRequestRef& Request);` — Broadcast that a non-threaded HTTP request is complete. Called automatically internally for threaded requests. Called explicitly by non-threaded requests
- L443 _protected prototype_ `FHttpThreadBase* GetThread();` — Access http thread of http manager for internal usage
- L446 _protected prototype_ `void RecordStatTimeToConnect(float Duration);` — Record the time to connect, to have a general idea how long the client usually take to connect for success requests, to adjust the connection timeout
- L449 _protected prototype_ `void RecordStatRequestsInFlight(uint32 RequestsInFlight);` — Record the requests waiting in flight, to have an idea if there are too many concurrent requests
- L452 _protected prototype_ `void RecordStatRequestsInQueue(uint32 RequestsInQueue);` — Record the requests waiting in queue, to have an idea if there are too many requests or if request number limit is too small
- L455 _protected prototype_ `void RecordMaxTimeToWaitInQueue(float Duration);` — Record the time to wait in queue, to have a general idea how long the client usually wait before actually starting, to adjust the requests
- L458 _protected prototype_ `void RecordStatRequestSucceeded();` — Record a succeeded request
- L461 _protected prototype_ `void RecordStatRequestFailed(EHttpFailureReason Reason);` — Record a failed request by its failure reason
- L464 _protected prototype_ `void RecordPlatformStats(const FHttpStatsPlatform& PlatformStats);` — Record platform specific stats
- L466 _protected prototype_ `bool ShouldInspect(FStringView Url) const;`
- L467 _protected prototype_ `bool ShouldDisableFailedLog(FStringView Url) const;`
- L469 _protected prototype_ `TOptional<FMockResponse> GetMockResponse(FStringView Url, FStringView Verb) const;`
- L471 _protected prototype_ `void MarkCurrentThreadCompletingRequest(bool bCompleting);`
- L472 _protected prototype_ `bool IsCurrentThreadCompletingRequest() const;`
- L479 _protected prototype_ `void AddRequest(const FHttpRequestRef& Request);` — Add a http request to the manager without enqueueing the threaded execution @param Request - the request object to add
- L482 _protected member_ `TArray<TPair<FUrlToMatch, FMockResponse>> UrlPatternsToMockResponse;`
- L483 _protected member_ `mutable FCriticalSection UrlPatternsToMockResponseCriticalSection;`

#### struct `FHttpManager::FHttpFlushTimeLimit`  
`struct FHttpFlushTimeLimit`  
_L359-381_
- L367 _public member_ `double SoftLimitSeconds;` — Designates the amount of time we will wait during a flush before we try to cancel the request. This MUST be strictly < FlushTimeHardLimitSeconds for the logic to work and actually cancel the request, since we must Tick at least one time for the cancel to work. Setting this to 0 will immediately cancel all ongoing requests. A hard limit is still required for this to work. Setting this to < 0 will disable the cancel, but FlushTimeHardLimitSeconds can still be used to stop waiting on requests.
- L376 _public member_ `double HardLimitSeconds;` — After we hit the soft time limit and cancel the requests, we wait some additional time for the canceled requests to go away. If they don't go away in time, we will hit this "hard" time limit that will just stop waiting. If we are shutting down, this is probably fine. If we are flushing for other reasons, This could indicate things lying around, and we'll put out some warning log messages to indicate this. Setting this to < 0 will disable all time limits and the code will wait infinitely for all requests to complete.
- L378 _public function_ `FHttpFlushTimeLimit(double InSoftLimitSeconds, double InHardLimitSeconds) : SoftLimitSeconds(InSoftLimitSeconds), HardLimitSeconds(InHardLimitSeconds)`

#### struct `FHttpManager::FHttpStatsHistory`  
`struct FHttpStatsHistory`  
_L386-397_
- L388 _public member_ `static constexpr int32 HttpHistoryCount = 16;`
- L389 _public member_ `int32 HistoryIndex = 0;`
- L391 _public member_ `int64 DownloadedBytes[HttpHistoryCount] = { 0 };`
- L392 _public member_ `int64 DurationMs[HttpHistoryCount] = { 0 };`
- L394 _public member_ `int64 TotalDownloadedBytes = 0;`
- L395 _public member_ `int64 TotalUploadedBytes = 0;`
- L396 _public member_ `int64 TotalDuration = 0;`

#### struct `FHttpManager::FMockResponse`  
`struct FMockResponse`  
_L414-419_
- L416 _public member_ `int32 StatusCode = 0;`
- L417 _public member_ `FUtf8String ResponsePayload;`
- L418 _public member_ `TMap<FString, FString> ResponseHeaders;`

#### struct `FHttpManager::FUrlToMatch`  
`struct FUrlToMatch`  
_L421-425_
- L423 _public member_ `FString Str;`
- L424 _public member_ `FString Verb;`

#### Free symbols / members of external scopes

- L37 _prototype_ `ENUM_RANGE_BY_COUNT(EHttpFlushReason, EHttpFlushReason::Count) const TCHAR* LexToString(const EHttpFlushReason& FlushReason);`
- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FHttpManagerRequestAddedDelegate, const FHttpRequestRef& );` — Delegate called when an Http request added. Intended to be used for analytics. Called from the thread that adds the HTTP request. @param Request Http request that was added
- L44 _prototype_ `DECLARE_DELEGATE_OneParam(FHttpManagerRequestAddedDelegate, const FHttpRequestRef& );` — Delegate called when an Http request added. Intended to be used for analytics. Called from the thread that adds the HTTP request. @param Request Http request that was added
- L50 _delegate_ `DECLARE_DELEGATE_OneParam(FHttpManagerRequestCompletedDelegate, const FHttpRequestRef& );` — Delegate called when an Http request completes. Intended to be used for analytics. Called from the game thread. @param Request Http request that completed
- L50 _prototype_ `DECLARE_DELEGATE_OneParam(FHttpManagerRequestCompletedDelegate, const FHttpRequestRef& );` — Delegate called when an Http request completes. Intended to be used for analytics. Called from the game thread. @param Request Http request that completed

### `Source/Runtime/Online/HTTP/Public/HttpModule.h` (Public)


#### class `FHttpModule`  
`class FHttpModule : public IModuleInterface, public FSelfRegisteringExec`  
_L25-372_
- inherits: `IModuleInterface,FSelfRegisteringExec`
- desc: Module for Http request implementations Use FHttpFactory to create a new Http request
- L42 _protected prototype_ `virtual bool Exec_Runtime(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — Handle exec commands starting with "HTTP" @param InWorld	the world context @param Cmd		the exec command being executed @param Ar		the archive to log results to @return true if the handler consumed the input, false to continue searching handlers
- L49 _public prototype_ `bool HandleHTTPCommand( const TCHAR* Cmd, FOutputDevice& Ar );` — Exec command handlers
- L59 _public prototype_ `static FHttpModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L64 _public prototype_ `void UpdateConfigs();` — Update all config-based values
- L71 _public prototype_ `virtual TSharedRef<IHttpRequest, ESPMode::ThreadSafe> CreateRequest();` — Instantiates a new Http request for the current platform @return new Http request instance
- L78 _public function_ `inline FHttpManager& GetHttpManager()` — Only meant to be used by Http request/response implementations @return Http request manager used by the module
- L87 _public function_ `inline float GetHttpTotalTimeout() const` — @return total timeout in seconds for the entire http request to complete
- L95 _public function_ `inline float GetHttpConnectionTimeout() const` — @return timeout in seconds to establish the connection
- L103 _public function_ `inline float GetHttpActivityTimeout() const` — @return timeout in seconds to check there is any ongoing activity on the established connection
- L111 _public function_ `inline int32 GetHttpMaxConnectionsPerServer() const` — @return max number of simultaneous connections to a specific server
- L119 _public function_ `inline int32 GetMaxReadBufferSize() const` — @return max read buffer size for http requests
- L128 _public function_ `inline void SetMaxReadBufferSize(int32 SizeInBytes)` — Sets the maximum size for the read buffer @param SizeInBytes	The maximum number of bytes to use for the read buffer
- L136 _public function_ `inline bool IsHttpEnabled() const` — @return true if http requests are enabled
- L144 _public function_ `inline void ToggleNullHttp(bool bEnabled)` — toggle null http implementation
- L152 _public function_ `inline bool IsNullHttpEnabled() const` — @return true if null http is being used
- L160 _public function_ `inline float GetHttpDelayTime() const` — @return min delay time for each http request
- L168 _public function_ `inline void SetHttpDelayTime(float InHttpDelayTime)` — Set the min delay time for each http request
- L176 _public function_ `inline float GetHttpThreadActiveFrameTimeInSeconds() const` — @return Target tick rate of an active http thread
- L184 _public function_ `inline void SetHttpThreadActiveFrameTimeInSeconds(float InHttpThreadActiveFrameTimeInSeconds)` — Set the target tick rate of an active http thread
- L192 _public function_ `inline float GetHttpThreadActiveMinimumSleepTimeInSeconds() const` — @return Minimum sleep time of an active http thread
- L200 _public function_ `inline void SetHttpThreadActiveMinimumSleepTimeInSeconds(float InHttpThreadActiveMinimumSleepTimeInSeconds)` — Set the minimum sleep time of an active http thread
- L208 _public function_ `inline float GetHttpThreadIdleFrameTimeInSeconds() const` — @return Target tick rate of an idle http thread
- L216 _public function_ `inline void SetHttpThreadIdleFrameTimeInSeconds(float InHttpThreadIdleFrameTimeInSeconds)` — Set the target tick rate of an idle http thread
- L224 _public function_ `inline float GetHttpThreadIdleMinimumSleepTimeInSeconds() const` — @return Minimum sleep time when idle, waiting for requests
- L232 _public function_ `inline void SetHttpThreadIdleMinimumSleepTimeInSeconds(float InHttpThreadIdleMinimumSleepTimeInSeconds)` — Set the minimum sleep time when idle, waiting for requests
- L240 _public function_ `inline float GetHttpEventLoopThreadTickIntervalInSeconds() const` — @return Duration between explicit tick calls when running an event loop http thread.
- L249 _public function_ `const TMap<FString, FString>& GetDefaultHeaders() const` — Get the default headers that are appended to every request @return the default headers
- L257 _public function_ `void AddDefaultHeader(const FString& HeaderName, const FString& HeaderValue)` — Add a default header to be appended to future requests If a request already specifies this header, then the defaulted version will not be used @param HeaderName - Name of the header (e.g., "Content-Type") @param HeaderValue - Value of the header
- L262 _public function_ `inline const FString& GetProxyAddress() const` — @returns The current proxy address.
- L271 _public function_ `inline void SetProxyAddress(const FString& InProxyAddress)` — Setter for the proxy address. @param InProxyAddress - New proxy address to use.
- L279 _public function_ `inline const FString& GetHttpNoProxy() const` — @returns the domains which won't use proxy even if ProxyAddress is set
- L288 _public function_ `inline bool SupportsDynamicProxy() const` — Method to check dynamic proxy setting support. @returns Whether this http implementation supports dynamic proxy setting.
- L299 _public prototype_ `virtual void StartupModule() override;` — Called when Http module is loaded load dependant modules
- L305 _public prototype_ `virtual void PostLoadCallback() override;` — Called after Http module is loaded Initialize platform specific parts of Http handling
- L311 _public prototype_ `virtual void PreUnloadCallback() override;` — Called before Http module is unloaded Shutdown platform specific parts of Http handling
- L316 _public prototype_ `virtual void ShutdownModule() override;` — Called when Http module is unloaded
- L320 _protected member_ `float HttpConnectionTimeout;` — timeout in seconds to establish the connection
- L322 _protected member_ `float HttpTotalTimeout;` — timeout in seconds for the entire http request to complete. 0 is no timeout
- L324 _protected member_ `float HttpActivityTimeout;` — timeout in seconds to check there is any ongoing activity on the established connection
- L330 _private prototype_ `void OnConfigSectionsChanged(const FString& IniFilename, const TSet<FString>& SectionNames);` — Delegate for config file changes.
- L333 _private member_ `FHttpManager* HttpManager = nullptr;` — Keeps track of Http requests while they are being processed
- L335 _private member_ `float HttpReceiveTimeout;` — timeout in seconds to receive a response on the connection
- L337 _private member_ `float HttpSendTimeout;` — timeout in seconds to send a request on the connection
- L339 _private member_ `float HttpDelayTime;` — total time to delay the request
- L341 _private member_ `float HttpThreadActiveFrameTimeInSeconds;` — Time in seconds to use as frame time when actively processing requests. 0 means no frame time.
- L343 _private member_ `float HttpThreadActiveMinimumSleepTimeInSeconds;` — Time in seconds to sleep minimally when actively processing requests.
- L345 _private member_ `float HttpThreadIdleFrameTimeInSeconds;` — Time in seconds to use as frame time when idle, waiting for requests. 0 means no frame time.
- L347 _private member_ `float HttpThreadIdleMinimumSleepTimeInSeconds;` — Time in seconds to sleep minimally when idle, waiting for requests.
- L349 _private member_ `float HttpEventLoopThreadTickIntervalInSeconds;` — Time in seconds between explicit calls to tick requests when using an event loop to run http requests.
- L351 _private member_ `int32 HttpMaxConnectionsPerServer;` — Max number of simultaneous connections to a specific server
- L353 _private member_ `int32 MaxReadBufferSize;` — Max buffer size for individual http reads
- L355 _private member_ `bool bEnableHttp;` — toggles http requests
- L357 _private member_ `bool bUseNullHttp;` — toggles null (mock) http requests
- L359 _private member_ `TMap<FString, FString> DefaultHeaders;` — Default headers - each request will include these headers, using the default value if not overridden
- L361 _private member_ `static FHttpModule* Singleton;` — singleton for the module while loaded and available
- L363 _private member_ `static bool bWasEverLoaded;` — true once StartupModule has been called at least once; prevents Get() from auto-loading after shutdown
- L365 _private member_ `FString ProxyAddress;` — The address to use for proxy, in format IPADDRESS:PORT
- L367 _private member_ `FString HttpNoProxy;` — The domains which won't use proxy even if the ProxyAddress is set, in format "127.0.0.1,localhost,example.com"
- L369 _private member_ `bool bSupportsDynamicProxy;` — Whether or not the http implementation we are using supports dynamic proxy setting.
- L371 _private member_ `TArray<FString> AllowedDomains;` — List of domains that can be accessed. If Empty then no filtering is applied

### `Source/Runtime/Online/HTTP/Public/HttpPackage.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define PACKAGE_SCOPE public`
- L14 _macro_ `#define PACKAGE_SCOPE private`

### `Source/Runtime/Online/HTTP/Public/HttpRequestAdapter.h` (Public)


#### class `FHttpRequestAdapterBase`  
`class FHttpRequestAdapterBase : public FHttpRequestImpl`  
_L13-59_
- inherits: `FHttpRequestImpl`
- L16 _public prototype_ `FHttpRequestAdapterBase(const TSharedRef<IHttpRequest>& InHttpRequest);`
- L17 _public prototype_ `~FHttpRequestAdapterBase();`
- L20 _public prototype_ `virtual const FString& GetURL() const override;` — IHttpRequest interface
- L21 _public prototype_ `virtual FString GetURLParameter(const FString& ParameterName) const override;`
- L22 _public prototype_ `virtual FString GetHeader(const FString& HeaderName) const override;`
- L23 _public prototype_ `virtual TArray<FString> GetAllHeaders() const override;`
- L24 _public prototype_ `virtual FString GetContentType() const override;`
- L25 _public prototype_ `virtual uint64 GetContentLength() const override;`
- L26 _public prototype_ `virtual const TArray<uint8>& GetContent() const override;`
- L27 _public prototype_ `virtual FString GetVerb() const override;`
- L28 _public prototype_ `virtual FString GetOption(const FName Option) const override;`
- L29 _public prototype_ `virtual void SetVerb(const FString& Verb) override;`
- L30 _public prototype_ `virtual void SetURL(const FString& URL) override;`
- L31 _public prototype_ `virtual void SetOption(const FName Option, const FString& OptionValue) override;`
- L32 _public prototype_ `virtual void SetContent(const TArray<uint8>& ContentPayload) override;`
- L33 _public prototype_ `virtual void SetContent(TArray<uint8>&& ContentPayload) override;`
- L34 _public prototype_ `virtual void SetContentAsString(const FString& ContentString) override;`
- L35 _public prototype_ `virtual bool SetContentAsStreamedFile(const FString& Filename) override;`
- L36 _public prototype_ `virtual bool SetContentFromStream(TSharedRef<FArchive, ESPMode::ThreadSafe> Stream) override;`
- L37 _public prototype_ `virtual bool SetResponseBodyReceiveStream(TSharedRef<FArchive> Stream) override;`
- L38 _public prototype_ `virtual void SetHeader(const FString& HeaderName, const FString& HeaderValue) override;`
- L39 _public prototype_ `virtual void AppendToHeader(const FString& HeaderName, const FString& AdditionalHeaderValue) override;`
- L40 _public prototype_ `virtual void SetTimeout(float InTimeoutSecs) override;`
- L41 _public prototype_ `virtual void ClearTimeout() override;`
- L42 _public prototype_ `virtual void ResetTimeoutStatus() override;`
- L43 _public prototype_ `virtual TOptional<float> GetTimeout() const override;`
- L44 _public prototype_ `virtual void SetActivityTimeout(float InTimeoutSecs) override;`
- L45 _public prototype_ `virtual void ProcessRequestUntilComplete() override;`
- L46 _public prototype_ `virtual const FHttpResponsePtr GetResponse() const override;`
- L47 _public prototype_ `virtual float GetElapsedTime() const override;`
- L48 _public prototype_ `virtual EHttpRequestStatus::Type GetStatus() const override;`
- L49 _public prototype_ `virtual EHttpFailureReason GetFailureReason() const override;`
- L50 _public prototype_ `virtual const FString& GetEffectiveURL() const override;`
- L51 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L52 _public prototype_ `virtual void SetDelegateThreadPolicy(EHttpRequestDelegateThreadPolicy InThreadPolicy) override;`
- L53 _public prototype_ `virtual EHttpRequestDelegateThreadPolicy GetDelegateThreadPolicy() const override;`
- L54 _public prototype_ `virtual void SetPriority(EHttpRequestPriority InPriority) override;`
- L55 _public prototype_ `virtual EHttpRequestPriority GetPriority() const override;`
- L58 _protected member_ `TSharedRef<IHttpRequest> HttpRequest;`

### `Source/Runtime/Online/HTTP/Public/HttpRetrySystem.h` (Public)


#### struct `FHttpRetrySystem::FRetryDomains`  
`struct FRetryDomains`  
_L46-73_
- L48 _public function_ `FRetryDomains(TArray<FString>&& InDomains) : Domains(MoveTemp(InDomains)) , ActiveIndex(0)`
- L53 _public function_ `FRetryDomains(TArray<FString>&& InDomains, const int32 InActiveIndex, const FString& InConfigSection, const FString& InConfigKeyName) : Domains(MoveTemp(InDomains)) , ActiveIndex(InActiveIndex) , ConfigSection(InConfigSection) , ConfigKeyName(InConfigKeyName)`
- L61 _public member_ `TArray<FString> Domains;` — The domains to use
- L66 _public member_ `TAtomic<int32> ActiveIndex;` — Index into Domains to attempt Domains are cycled through on some errors, and when we succeed on one domain, we remain on that domain until that domain results in an error
- L69 _public member_ `const FString ConfigSection;` — Config section name that can be used for storing active domain for reusing during next sessions
- L72 _public member_ `const FString ConfigKeyName;` — Config key name that can be used for storing active domain for reusing during next sessions

#### struct `FHttpRetrySystem::FExponentialBackoffCurve`  
`struct FExponentialBackoffCurve`  
_L83-98_
- desc: Model for computing exponential backoff using the formula: Base**(CurrentRetryAttempt + Bias) Then applying jitter to the backoff. Jitter application is performed by selecting a random value in the [Min, Max] range and multiplying it against the computed backoff. Half jitter can be implemented using { 0.5, 1.0 }, which becomes Backoff' = Backoff * Rand(0.5, 1.0) = Backoff/2 + Rand(0, Backoff/2) Full jitter can be implemented using { 0.0, 1.0 }, which becomes Backoff' = Backoff * Rand(0.0, 1.0) = Rand(0.0, Backoff) No jitter can be implemented using { 0.0, 0.0 } or any pair that where Min > Max. Backoff' = Backoff
- L86 _public member_ `float Base = 2.0f;` — Exponential backoff base
- L88 _public member_ `float ExponentBias = 1.0f;` — Exponential backoff bias added to the current retry number
- L90 _public member_ `float MinCoefficient = 0.5f;` — Exponential backoff jitter coefficient minimum value. Defaults to half jitter
- L92 _public member_ `float MaxCoefficient = 1.0f;` — Exponential backoff jitter coefficient maximum value. Defaults to half jitter
- L94 _public member_ `float MaxBackoffSeconds = 60.0f;` — Max back off seconds
- L96 _public prototype_ `bool IsValid() const;`
- L97 _public prototype_ `float Compute(uint32 RetryNumber) const;`

#### class `FHttpRetrySystem::FRequest`  
`class FRequest : public FHttpRequestAdapterBase`  
_L115-191_
- inherits: `FHttpRequestAdapterBase`
- desc: class FRequest is what the retry system accepts as inputs
- L135 _public prototype_ `virtual bool ProcessRequest() override;` — IHttpRequest interface
- L136 _public prototype_ `virtual void CancelRequest() override;`
- L139 _public function_ `EStatus::Type GetRetryStatus() const` — FRequest
- L144 _protected prototype_ `FRequest( TSharedRef<FManager, ESPMode::ThreadSafe> InManager, const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& HttpRequest, const FRetryLimitCountSetting& InRetryLimitCountOverride = FRetryLimitCountSetting(), const FRetryTimeoutRelativeSecondsSetting& InRetryTimeoutRelativeSecondsOverride = FRetryTimeoutRelativeSecondsSetting(), const FRetryResponseCodes& InRetryResponseCodes = FRetryResponseCodes(), const FRetryVerbs& InRetryVerbs = FRetryVerbs(), const FRetryDomainsPtr& InRetryDomains = FRetryDomainsPtr(), const FRetryLimitCountSetting& InRetryLimitCountForConnectionErrorOverride = FRetryLimitCountSetting(), const FExponentialBackoffCurve& InExponentialBackoffCurve = FExponentialBackoffCurve() );`
- L156 _protected prototype_ `void HttpOnRequestProgress(FHttpRequestPtr InHttpRequest, uint64 BytesSent, uint64 BytesRcv);`
- L157 _protected prototype_ `void HttpOnProcessRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L158 _protected prototype_ `void HttpOnStatusCodeReceived(FHttpRequestPtr Request, int32 StatusCode);`
- L159 _protected prototype_ `void HttpOnHeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue);`
- L162 _protected prototype_ `void SetUrlFromRetryDomains();` — Update our HTTP request's URL's domain from our RetryDomains
- L164 _protected prototype_ `void MoveToNextRetryDomain();` — Move to the next retry domain from our RetryDomains
- L166 _protected prototype_ `void BindAdaptorDelegates();`
- L168 _protected member_ `EStatus::Type RetryStatus;`
- L170 _protected member_ `FRetryLimitCountSetting RetryLimitCountOverride;`
- L171 _protected member_ `FRetryLimitCountSetting RetryLimitCountForConnectionErrorOverride;`
- L172 _protected member_ `FRetryTimeoutRelativeSecondsSetting RetryTimeoutRelativeSecondsOverride;`
- L173 _protected member_ `FRetryResponseCodes RetryResponseCodes;`
- L174 _protected member_ `FRetryVerbs RetryVerbs;`
- L175 _protected member_ `FRetryDomainsPtr RetryDomains;`
- L177 _protected member_ `int32 RetryDomainsIndex = 0;` — The current index in RetryDomains we are attempting
- L179 _protected member_ `FString OriginalUrl;` — The original URL before replacing anything from RetryDomains
- L181 _protected member_ `TWeakPtr<FManager> RetryManager;`
- L183 _protected member_ `FHttpResponsePtr LastResponse;` — Save the last response before the retry
- L184 _protected member_ `EHttpFailureReason LastFailureReason = EHttpFailureReason::None;`
- L185 _protected member_ `bool bLastSucceeded = false;`
- L188 _protected member_ `FExponentialBackoffCurve RetryExponentialBackoffCurve;` — Exponential backoff curve
- L190 _protected member_ `bool bBoundAdaptorDelegates = false;`

#### struct `FHttpRetrySystem::FRequest::EStatus`  
`struct EStatus`  
_L119-131_

#### enum `FHttpRetrySystem::FRequest::EStatus::Type`  
`enum Type`  
_L121-130_
- L123 _public enumerator_ `NotStarted = 0`
- L124 _public enumerator_ `Processing`
- L125 _public enumerator_ `ProcessingLockout`
- L126 _public enumerator_ `Cancelled`
- L127 _public enumerator_ `FailedRetry`
- L128 _public enumerator_ `FailedTimeout`
- L129 _public enumerator_ `Succeeded`

#### class `FHttpRetrySystem::FManager`  
`class FManager : public TSharedFromThis<FManager>`  
_L197-313_
- inherits: `TSharedFromThis<FManager>`
- L201 _public prototype_ `FManager( const FRetryLimitCountSetting& InRetryLimitCountDefault, const FRetryTimeoutRelativeSecondsSetting& InRetryTimeoutRelativeSecondsDefault, const FRetryLimitCountSetting& InRetryLimitCountForConnectionErrorDefault = FRetryLimitCountSetting() );` — FManager
- L210 _public prototype_ `TSharedRef<class FHttpRetrySystem::FRequest, ESPMode::ThreadSafe> CreateRequest( const FRetryLimitCountSetting& InRetryLimitCountOverride = FRetryLimitCountSetting(), const FRetryTimeoutRelativeSecondsSetting& InRetryTimeoutRelativeSecondsOverride = FRetryTimeoutRelativeSecondsSetting(), const FRetryResponseCodes& InRetryResponseCodes = FRetryResponseCodes(), const FRetryVerbs& InRetryVerbs = FRetryVerbs(), const FRetryDomainsPtr& InRetryDomains = FRetryDomainsPtr(), const FRetryLimitCountSetting& InRetryLimitCountForConnectionErrorOverride = FRetryLimitCountSetting(), const FExponentialBackoffCurve & InExponentialBackoffCurve = FExponentialBackoffCurve() );` — Create a new http request with retries
- L220 _public prototype_ `virtual ~FManager();`
- L222 _public function_ `void SetRandomFailureRate(float Value)`
- L223 _public function_ `void SetDefaultRetryLimit(uint32 Value)`
- L226 _public prototype_ `void BlockUntilFlushed(float TimeoutSec);` — @return Block the current process until all requests are flushed, or timeout has elapsed
- L269 _protected prototype_ `bool ProcessRequest(TSharedRef<FRequest, ESPMode::ThreadSafe>& HttpRequest);`
- L270 _protected prototype_ `void CancelRequest(TSharedRef<FRequest, ESPMode::ThreadSafe>& HttpRequest);`
- L274 _protected prototype_ `bool ShouldRetry(const FHttpRetryRequestEntry& HttpRetryRequestEntry) const;` — @return true if there is a no formal response to the request @TODO return true if a variety of 5xx errors are the result of a formal response
- L277 _protected prototype_ `bool CanRetry(const FHttpRetryRequestEntry& HttpRetryRequestEntry) const;` — @return true if retry chances have not been exhausted
- L280 _protected prototype_ `bool HasTimedOut(const FHttpRetryRequestEntry& HttpRetryRequestEntry, const double NowAbsoluteSeconds);` — @return true if the retry request has timed out
- L286 _protected prototype_ `void RetryHttpRequest(FHttpRetryRequestEntry& RequestEntry);` — Retry an HTTP request @param RequestEntry request to retry
- L294 _protected prototype_ `void RetryHttpRequestWithDelay(FManager::FHttpRetryRequestEntry& RequestEntry, float InDelay, bool bWasSucceeded);` — Retry an HTTP request with delay @param RequestEntry request retry @param InDelay the delay to wait before retrying @param bWasSucceeded was the request succeeded before retry
- L296 _protected prototype_ `void HttpRequestTimeoutAfterDelay(FManager::FHttpRetryRequestEntry& RequestEntry, bool bWasSucceeded, float Delay);`
- L299 _protected prototype_ `float GetLockoutPeriodSeconds(const FHttpRetryRequestEntry& HttpRetryRequestEntry);` — @return number of seconds to lockout for
- L301 _protected prototype_ `bool RetryLimitForConnectionErrorIsSet(const FHttpRetryRequestEntry& HttpRetryRequestEntry) const;`
- L302 _protected prototype_ `bool CanRetryForConnectionError(const FHttpRetryRequestEntry& HttpRetryRequestEntry) const;`
- L303 _protected prototype_ `bool CanRetryInGeneral(const FHttpRetryRequestEntry& HttpRetryRequestEntry) const;`
- L306 _protected member_ `FRandomFailureRateSetting RandomFailureRate;` — Default configuration for the retry system
- L307 _protected member_ `FRetryLimitCountSetting RetryLimitCountDefault;`
- L308 _protected member_ `FRetryLimitCountSetting RetryLimitCountForConnectionErrorDefault;`
- L309 _protected member_ `FRetryTimeoutRelativeSecondsSetting RetryTimeoutRelativeSecondsDefault;`
- L311 _protected member_ `TArray<FHttpRetryRequestEntry> RequestList;`
- L312 _protected member_ `FCriticalSection RequestListLock;`

#### struct `FHttpRetrySystem::FManager::FHttpRetryRequestEntry`  
`struct FHttpRetryRequestEntry`  
_L231-241_
- L233 _public prototype_ `FHttpRetryRequestEntry(TSharedRef<FRequest, ESPMode::ThreadSafe>& InRequest);`
- L235 _public member_ `uint32 CurrentRetryCount;`
- L236 _public member_ `uint32 CurrentRetryCountForConnectionError;`
- L237 _public member_ `double RequestStartTimeAbsoluteSeconds;`
- L238 _public member_ `double LockoutEndTimeAbsoluteSeconds;`
- L240 _public member_ `TSharedRef<FRequest, ESPMode::ThreadSafe> Request;`

#### class `FHttpRetrySystem::FManager::FHttpLogVerbosityTracker`  
`class FHttpLogVerbosityTracker`  
_L243-267_
- L246 _public prototype_ `FHttpLogVerbosityTracker();`
- L247 _public prototype_ `~FHttpLogVerbosityTracker();`
- L250 _public prototype_ `void IncrementRetriedRequests();` — Mark that a request is being retried
- L252 _public prototype_ `void DecrementRetriedRequests();` — Mark that a retried request is no longer being retried
- L253 _public prototype_ `static FHttpLogVerbosityTracker& Get();`
- L256 _protected prototype_ `void UpdateSettingsFromConfig();` — Update settings from config
- L257 _protected prototype_ `void OnConfigSectionsChanged(const FString& IniFilename, const TSet<FString>& SectionName);`
- L260 _protected member_ `int32 NumRetriedRequests = 0;` — Number of requests that are in a retried state.  When this is non-zero, verbosity will be adjusted.
- L262 _protected member_ `FCriticalSection NumRetriedRequestsLock;` — DecrementRetriedRequests can be called from game thread or http thread depends on the http request thread policy, make sure it's thread-safe
- L264 _protected member_ `ELogVerbosity::Type OriginalVerbosity = ELogVerbosity::Error;` — Verbosity to restore to when there are no requests being retried
- L266 _protected member_ `ELogVerbosity::Type TargetVerbosity = ELogVerbosity::NoLogging;` — Config driven target verbosity to set to when requests are being retried.  NoLogging means the verbosity will not be modified.

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace FHttpRetrySystem`
- L27 _typedef_ `typedef uint32 RetryLimitCountType;` (scope `FHttpRetrySystem`)
- L28 _typedef_ `typedef double RetryTimeoutRelativeSecondsType;` (scope `FHttpRetrySystem`)
- L30 _function_ `inline RetryLimitCountType RetryLimitCount(uint32 Value)` (scope `FHttpRetrySystem`)
- L31 _function_ `inline RetryTimeoutRelativeSecondsType RetryTimeoutRelativeSeconds(double Value)` (scope `FHttpRetrySystem`)
- L34 _prototype_ `template <typename IntrinsicType> IntrinsicType TZero();` (scope `FHttpRetrySystem`)
- L36 _function_ `template <> inline float TZero<float>()` (scope `FHttpRetrySystem`)
- L40 _typedef_ `typedef TOptional<float> FRandomFailureRateSetting;` (scope `FHttpRetrySystem`)
- L41 _typedef_ `typedef TOptional<RetryLimitCountType> FRetryLimitCountSetting;` (scope `FHttpRetrySystem`)
- L42 _typedef_ `typedef TOptional<RetryTimeoutRelativeSecondsType> FRetryTimeoutRelativeSecondsSetting;` (scope `FHttpRetrySystem`)
- L43 _typedef_ `typedef TSet<int32> FRetryResponseCodes;` (scope `FHttpRetrySystem`)
- L44 _typedef_ `typedef TSet<FName> FRetryVerbs;` (scope `FHttpRetrySystem`)
- L74 _typedef_ `typedef TSharedPtr<FRetryDomains, ESPMode::ThreadSafe> FRetryDomainsPtr;` (scope `FHttpRetrySystem`)
- L99 _typedef_ `using FRetryExponentialBackoffCurvePtr = TSharedPtr<FExponentialBackoffCurve, ESPMode::ThreadSafe>;` (scope `FHttpRetrySystem`)
- L106 _prototype_ `TOptional<double> ReadThrottledTimeFromResponseInSeconds(FHttpResponsePtr Response);` (scope `FHttpRetrySystem`) — Read the number of seconds a HTTP request is throttled for from the response @param Response the HTTP response to read the value from @return If found, the number of seconds the request is rate limited for.  If not found, an unset TOptional
- L110 _namespace_ `namespace FHttpRetrySystem`
- L194 _namespace_ `namespace FHttpRetrySystem`

### `Source/Runtime/Online/HTTP/Public/IOS/IOSPlatformHttp.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Online/HTTP/Public/Interfaces/IHttpBase.h` (Public)


#### enum `EHttpRequestStatus::Type`  
`enum Type`  
_L12-22_
- desc: Enumerates the current state of an Http request
- L15 _public enumerator_ `NotStarted` — Has not been started via ProcessRequest()
- L17 _public enumerator_ `Processing` — Currently being ticked and processed
- L19 _public enumerator_ `Failed` — Finished but failed
- L21 _public enumerator_ `Succeeded` — Finished and was successful

#### enum `EHttpFailureReason`  
`enum class EHttpFailureReason : uint8`  
_L58-72_
- desc: The reason of the failure when HTTP request failed
- L60 _public enumerator_ `None = 0`
- L61 _public enumerator_ `ConnectionError`
- L62 _public enumerator_ `Cancelled`
- L68 _public enumerator_ `TimedOut` — This acts differently than the platform timeout. It's the time out of the entire request including retries, which configured by the user. The platform timeout has different meanings/APIs on different platforms, such as resolve host timeout, connect timeout, send timeout, receive timeout, entire request timeout etc. It's not practical to unify to same behavior between them through their APIs. When user's configured time is up, it's TimedOut no matter which step this Http request is in.
- L69 _public enumerator_ `Other`
- L70 _public enumerator_ `ResponseTooLarge`
- L71 _public enumerator_ `Count`

#### class `IHttpBase`  
`class IHttpBase`  
_L92-173_
- desc: Base interface for Http Requests and Responses.
- L100 _public prototype_ `virtual const FString& GetURL() const = 0;` — Get the URL used to send the request. @return the URL string.
- L107 _public prototype_ `virtual const FString& GetEffectiveURL() const = 0;` — Get the effective URL in case of redirected. If not redirected, it's the same as GetURL @return the effective URL string.
- L114 _public prototype_ `virtual EHttpRequestStatus::Type GetStatus() const = 0;` — Get the current status of the request being processed @return the current status
- L121 _public prototype_ `virtual EHttpFailureReason GetFailureReason() const = 0;` — Get the reason of th failure if GetStatus returns Failed @return the reason of the failure
- L131 _public prototype_ `virtual FString GetURLParameter(const FString& ParameterName) const = 0;` — Gets an URL parameter. expected format is ?Key=Value&Key=Value... If that format is not used, this function will not work. @param ParameterName - the parameter to request. @return the parameter value string.
- L138 _public prototype_ `virtual FString GetHeader(const FString& HeaderName) const = 0;` — Gets the value of a header, or empty string if not found. @param HeaderName - name of the header to set.
- L145 _public prototype_ `virtual TArray<FString> GetAllHeaders() const = 0;` — Return all headers in an array in "Name: Value" format. @return the header array of strings
- L152 _public prototype_ `virtual FString GetContentType() const = 0;` — Shortcut to get the Content-Type header value (if available) @return the content type.
- L160 _public prototype_ `virtual uint64 GetContentLength() const = 0;` — Shortcut to get the Content-Length header value. Will not always return non-zero. If you want the real length of the payload, get the payload and check it's length. @return the content length (if available)
- L167 _public prototype_ `virtual const TArray<uint8>& GetContent() const = 0;` — Get the content payload of the request or response. @param Content - array that will be filled with the content.
- L172 _public prototype_ `virtual ~IHttpBase() = default;` — Destructor for overrides

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace EHttpRequestStatus`
- L25 _function_ `inline const TCHAR* ToString(EHttpRequestStatus::Type EnumVal)` (scope `EHttpRequestStatus`) — @return the stringified version of the enum passed in
- L49 _function_ `inline bool IsFinished(const EHttpRequestStatus::Type Value)` (scope `EHttpRequestStatus`)
- L75 _function_ `inline const TCHAR* LexToString(EHttpFailureReason HttpFailureReason)` — @return the stringified version of the enum passed in
- L176 _macro_ `#define UE_HTTP_CONNECTION_TIMEOUT_SUPPORT_RETRY UE_DEPRECATED_MACRO(5.6, "UE_HTTP_CONNECTION_TIMEOUT_SUPPORT_RETRY has been deprecated because it is no longer necessary.") 1`

### `Source/Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h` (Public)


#### enum `EHttpRequestDelegateThreadPolicy`  
`enum class EHttpRequestDelegateThreadPolicy : uint8`  
_L14-18_
- desc: Enumerates thread policy about which thread to complete the http request
- L16 _public enumerator_ `CompleteOnGameThread = 0`
- L17 _public enumerator_ `CompleteOnHttpThread`

#### enum `EHttpRequestPriority`  
`enum class EHttpRequestPriority : uint8`  
_L24-31_
- desc: Enumerates priority to decide how the request will be queued when max concurrent limit reached The priority will be compared through value, so it's important to keep the order from low to high
- L26 _public enumerator_ `Lowest = 0`
- L27 _public enumerator_ `Low`
- L28 _public enumerator_ `Normal`
- L29 _public enumerator_ `High`
- L30 _public enumerator_ `Highest`

#### class `FArchiveWithDelegate`  
`class UE_DEPRECATED(5.5, "FArchiveWithDelegate is deprecated and will be moved to internal") FArchiveWithDelegate final : public FArchive`  
_L121-139_
- inherits: `FArchive`
- desc: Delegate version of FArchive, for streaming interface
- L124 _public function_ `FArchiveWithDelegate(FHttpRequestStreamDelegate InStreamDelegate) : StreamDelegate(InStreamDelegate)`
- L129 _public function_ `virtual void Serialize(void* V, int64 Length) override`
- L138 _private member_ `FHttpRequestStreamDelegate StreamDelegate;`

#### enum `EHttpRequestMode`  
`enum class EHttpRequestMode : uint8`  
_L157-163_
- desc: Mode that can be specified through IHttpRequest::SetOption(HttpRequestOptions::RequestMode, LexToString(EHttpRequestMode::Value));
- L160 _public enumerator_ `ThreadedRequest` — The request will be enqueued to the http manager thread system
- L162 _public enumerator_ `ImmediateRequest` — The request will be immediately sent when the platform supports it

#### class `IHttpRequest`  
`class IHttpRequest : public IHttpBase, public TSharedFromThis<IHttpRequest, ESPMode::ThreadSafe>`  
_L170-459_
- inherits: `IHttpBase,TSharedFromThis<IHttpRequest,ESPMode::ThreadSafe>`
- desc: Interface for Http requests (created using FHttpFactory)
- L180 _public prototype_ `virtual FString GetVerb() const = 0;` — Gets the verb (GET, PUT, POST) used by the request. @return the verb string
- L190 _public prototype_ `virtual void SetVerb(const FString& Verb) = 0;` — Sets the verb used by the request. Eg. (GET, PUT, POST) Should be set before calling ProcessRequest. If not specified then a GET is assumed. @param Verb - verb to use.
- L199 _public prototype_ `virtual void SetURL(const FString& URL) = 0;` — Sets the URL for the request Eg. (http://my.domain.com/something.ext?key=value&key2=value). Must be set before calling ProcessRequest. @param URL - URL to use.
- L206 _public prototype_ `virtual FString GetOption(const FName Option) const = 0;` — Get the current value for the given option @return the current value set for this option or an empty string if no value has been specified
- L215 _public prototype_ `virtual void SetOption(const FName Option, const FString& OptionValue) = 0;` — Sets the given option for this Request Must be set before calling ProcessRequest. @param Option - The option to set, see 'HttpRequestOptions' for supported options @param OptionValue - The value of the option to set
- L223 _public prototype_ `virtual void SetContent(const TArray<uint8>& ContentPayload) = 0;` — Sets the content of the request (optional data). Usually only set for POST requests. @param ContentPayload - payload to set.
- L233 _public prototype_ `virtual void SetContent(TArray<uint8>&& ContentPayload) = 0;` — Sets the content of the request (optional data). Usually only set for POST requests. This version lets the API take ownership of the payload directly, helpful for larger payloads. @param ContentPayload - payload to set.
- L240 _public prototype_ `virtual void SetContentAsString(const FString& ContentString) = 0;` — Sets the content of the request as a string encoded as UTF8. @param ContentString - payload to set.
- L248 _public prototype_ `virtual bool SetContentAsStreamedFile(const FString& Filename) = 0;` — Sets the content of the request to stream from a file. @param FileName - filename from which to stream the body. @return True if the file is valid and will be used to stream the request. False otherwise.
- L257 _public prototype_ `virtual bool SetContentFromStream(TSharedRef<FArchive, ESPMode::ThreadSafe> Stream) = 0;` — Sets the content of the request to stream directly from an archive. NOTE: The Stream->Serialize will be called from another thread other than the game thread @param Stream - archive from which the payload should be streamed. @return True if the archive can be used to stream the request. False otherwise.
- L271 _public prototype_ `virtual bool SetResponseBodyReceiveStream(TSharedRef<FArchive> Stream) = 0;` — Sets the stream to receive the response body. Make sure to handle the cleanup of stream when Serialize generated error(Stream->GetError returns true after Stream->Serialize call), this http request will fail and quit. NOTE: Once set, the data will no longer be cached in response, IHttpResponse::GetContent() and IHttpResponse::GetContentAsString() will return empty result. The Stream->Serialize will be called from another thread other than the game thread @param Stream - will be used to receive the response body @return True if the stream can be used. False otherwise.
- L284 _public prototype_ `bool SetResponseBodyReceiveStreamDelegateV2(FHttpRequestStreamDelegateV2 StreamDelegate);` — Sets the delegate to receive the response body. Make sure to handle the cleanup of received data when failed to process the data(StreamDelegate return false), this http request will fail and quit. NOTE: Once set, the data will no longer be cached in response, IHttpResponse::GetContent() and IHttpResponse::GetContentAsString() will return empty result. The delegate will be called from another thread other than the game thread @param StreamDelegate - will be used to receive the response body @return True if the delegate can be used. False otherwise.
- L297 _public prototype_ `virtual void SetHeader(const FString& HeaderName, const FString& HeaderValue) = 0;` — Sets optional header info. SetHeader for a given HeaderName will overwrite any previous values Use AppendToHeader to append more values for the same header Content-Length is the only header set for you. Required headers depends on the request itself. Eg. "multipart/form-data" needed for a form post @param HeaderName - Name of the header (ie, Content-Type) @param HeaderValue - Value of the header
- L310 _public prototype_ `virtual void AppendToHeader(const FString& HeaderName, const FString& AdditionalHeaderValue) = 0;` — Appends to the value already set in the header. If there is already content in that header, a comma delimiter is used. If the header is as of yet unset, the result is the same as calling SetHeader Content-Length is the only header set for you. Also see: SetHeader() @param HeaderName - Name of the header (ie, Content-Type) @param AdditionalHeaderValue - Value to add to the existing contents of the specified header. comma is inserted between old value and new value, per HTTP specifications
- L318 _public prototype_ `virtual void SetTimeout(float InTimeoutSecs) = 0;` — Sets an optional timeout in seconds for this entire HTTP request to complete. If set, this value overrides the default HTTP timeout set via FHttpModule::SetTimeout(). @param InTimeoutSecs - Timeout for this HTTP request instance, in seconds
- L328 _public prototype_ `virtual void SetActivityTimeout(float InTimeoutSecs) = 0;` — Sets an optional activity timeout in seconds for this HTTP request. After connecting to web server, if there is no activity(send or receive) happen for this time period, it will trigger activity timeout If set, this value overrides the default HTTP activity timeout @param InTimeoutSecs - Timeout for this HTTP request instance, in seconds
- L334 _public prototype_ `virtual void ClearTimeout() = 0;` — Clears the optional timeout in seconds for this HTTP request, causing the default value from FHttpModule::GetTimeout() to be used.
- L339 _public prototype_ `virtual void ResetTimeoutStatus() = 0;` — Reset the elapsed timeout duration and flag, after the request completed and need to be reused
- L347 _public prototype_ `virtual TOptional<float> GetTimeout() const = 0;` — Gets the optional timeout in seconds for this entire HTTP request to complete. If valid, this value overrides the default HTTP timeout set via FHttpModule::SetTimeout(). @return the timeout for this HTTP request instance, in seconds
- L356 _public prototype_ `virtual bool ProcessRequest() = 0;` — Called to begin processing the request. OnProcessRequestComplete delegate is always called when the request completes or on error if it is bound. A request can be re-used but not while still being processed. @return if the request was successfully started.
- L361 _public prototype_ `virtual FHttpRequestCompleteDelegate& OnProcessRequestComplete() = 0;` — Delegate called when the request is complete. See FHttpRequestCompleteDelegate
- L366 _public prototype_ `virtual FHttpRequestProgressDelegate64& OnRequestProgress64() = 0;` — Delegate called to update the request/response progress. See FHttpRequestProgressDelegate64
- L371 _public prototype_ `virtual FHttpRequestWillRetryDelegate& OnRequestWillRetry() = 0;` — Delegate called when the request will be retried
- L376 _public prototype_ `virtual FHttpRequestHeaderReceivedDelegate& OnHeaderReceived() = 0;` — Delegate called to signal the receipt of a header.  See FHttpRequestHeaderReceivedDelegate
- L381 _public prototype_ `virtual FHttpRequestStatusCodeReceivedDelegate& OnStatusCodeReceived() = 0;` — Delegate called to signal the receipt of a header.  See FHttpRequestStatusCodeReceivedDelegate
- L386 _public prototype_ `virtual void CancelRequest() = 0;` — Called to cancel a request that is still being processed
- L393 _public prototype_ `virtual const FHttpResponsePtr GetResponse() const = 0;` — Get the associated Response @return the response
- L400 _public prototype_ `virtual void Tick(float DeltaSeconds) = 0;` — Used to tick the request @param DeltaSeconds - seconds since last ticked
- L407 _public prototype_ `virtual float GetElapsedTime() const = 0;` — Gets the time that it took for the server to fully respond to the request. @return elapsed time in seconds.
- L419 _public prototype_ `virtual void SetDelegateThreadPolicy(EHttpRequestDelegateThreadPolicy InThreadPolicy) = 0;` — Set thread policy about which thread to trigger the delegates, set by FHttpManager::SetRequestCompletedDelegate, IHttpRequest::OnStatusCodeReceived, IHttpRequest::OnHeaderReceived, IHttpRequest::OnRequestProgress64 and IHttpRequest::OnProcessRequestComplete. Note that when set it as CompleteOnHttpThread, the thread to trigger delegates could be any thread depends on the implementation. User code should make the delegate thread-safe and shouldn't assume it's triggered by the thread where this request get created. @param InThreadPolicy - The thread policy to indicate which thread to trigger the delegates
- L426 _public prototype_ `virtual EHttpRequestDelegateThreadPolicy GetDelegateThreadPolicy() const = 0;` — Get thread policy about which thread to complete this request @return The thread policy
- L439 _public prototype_ `virtual void ProcessRequestUntilComplete() = 0;` — Blocking call to wait the request until it's completed WARNINGS: - This is a blocking call, DON'T use this in a time-sensitive context - Complete delegate will be used in this function so customized complete delegate is not supported - This will force the usage of EHttpRequestDelegateThreadPolicy::CompleteOnHttpThread to make sure the request can complete, when this function get called from main thread. So if any other delegate is bound, make sure the bound delegate can handle the custom logic in a thread-safe way
- L446 _public prototype_ `virtual void SetPriority(EHttpRequestPriority InPriority) = 0;` — Set priority of the request, which will be used to decide the position in the queue when max concurrent limit reached @param InHttpRequestPriority - The priority to set
- L453 _public prototype_ `virtual EHttpRequestPriority GetPriority() const = 0;` — Get request priority, which is used to decide the position in the queue when max concurrent limit reached @return The request priority
- L458 _public prototype_ `virtual ~IHttpRequest() = default;` — Destructor for overrides

#### Free symbols / members of external scopes

- L36 _typedef_ `typedef TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> FHttpRequestPtr;`
- L37 _typedef_ `typedef TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;`
- L39 _typedef_ `typedef TSharedRef<IHttpRequest, ESPMode::ThreadSafe> FHttpRequestRef;`
- L40 _typedef_ `typedef TSharedRef<IHttpResponse, ESPMode::ThreadSafe> FHttpResponseRef;`
- L55 _typedef_ `using FHttpRequestCompleteDelegate = TTSDelegate<void(FHttpRequestPtr , FHttpResponsePtr , bool )>;` — Delegate called when an Http request completes @param Request original Http request that started things @param Response response received from the server if a successful connection was established. Note that even if response is not null, it doesn't mean the request was processed successfully. Use Response->GetStatus(), Response->GetFailureReason() and Response->GetResponseCode() to decide how to handle it @param bProcessedSuccessfully this flag indicates whether or not the request was able to be processed successfully. It could be connect error, timeout error or platform http error. Note that when this flag is true doesn't mean the http request get 2xx success status code, it just means this request got response from http server and completed the processing
- L63 _typedef_ `using FHttpRequestStatusCodeReceivedDelegate = TTSDelegate<void(FHttpRequestPtr , int32 )>;` — Delegate called when an Http request receives status code @param Request original Http request that started things @param status code
- L72 _typedef_ `using FHttpRequestHeaderReceivedDelegate = TTSDelegate<void(FHttpRequestPtr , const FString& , const FString& )>;` — Delegate called when an Http request receives a header @param Request original Http request that started things @param HeaderName the name of the header @param NewHeaderValue the value of the header
- L81 _typedef_ `using FHttpRequestProgressDelegate = TTSDelegate<void(FHttpRequestPtr , int32 , int32 )>;` — Delegate called per tick to update an Http request upload or download size progress @param Request original Http request that started things @param BytesSent the number of bytes sent / uploaded in the request so far. @param BytesReceived the number of bytes received / downloaded in the response so far.
- L90 _typedef_ `using FHttpRequestProgressDelegate64 = TTSDelegate<void(FHttpRequestPtr , uint64 , uint64 )>;` — Delegate called per tick to update an Http request upload or download size progress @param Request original Http request that started things @param BytesSent the number of bytes sent / uploaded in the request so far. @param BytesReceived the number of bytes received / downloaded in the response so far.
- L99 _typedef_ `using FHttpRequestWillRetryDelegate = TTSDelegate<void(FHttpRequestPtr , FHttpResponsePtr , float )>;` — Delegate called when an Http request will be retried in the future @param Request - original Http request that started things @param Response - response received from the server if a successful connection was established @param SecondsToRetry - seconds in the future when the response will be retried
- L108 _typedef_ `using FHttpRequestStreamDelegate = TTSDelegate<bool(void* , int64 )>;` — Delegate called when an Http request will send/recv data through stream @param Ptr - The buffer ptr to read/write @param Length - The length of buffer to read/write @return true if succeed, false if failed to read/write data
- L116 _typedef_ `using FHttpRequestStreamDelegateV2 = TTSDelegate<void(void* , int64& )>;` — Delegate called when an Http request will send/recv data through stream @param Ptr - The buffer ptr to read/write @param InOutLength - The int64 reference length of buffer to read/write, if there is any error when serialize set it to 0
- L144 _namespace_ `namespace HttpRequestOptions`
- L146 _externvar_ `extern const FName HttpVersion;` (scope `HttpRequestOptions`)
- L147 _externvar_ `extern const FName RequestMode;` (scope `HttpRequestOptions`)
- L149 _externvar_ `extern const FName UnixSocketPath;` (scope `HttpRequestOptions`)
- L151 _externvar_ `extern const FName EnableCookies;` (scope `HttpRequestOptions`)
- L165 _prototype_ `const TCHAR* LexToString(EHttpRequestMode Mode);`

### `Source/Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h` (Public)


#### enum `EHttpResponseCodes::Type`  
`#define HTTP_RESPONSE_CODE(Name, Value) Name = Value, enum Type`  
_L17-20_
- desc: Response codes that can come back from an Http request

#### class `IHttpResponse`  
`class IHttpResponse : public IHttpBase`  
_L110-147_
- inherits: `IHttpBase`
- desc: Interface for Http responses that come back after starting an Http request
- L118 _public prototype_ `virtual TArray<uint8> TakeContent() = 0;` — Return the content with a MoveTemp if possible. @return - The content array
- L126 _public prototype_ `virtual int32 GetResponseCode() const = 0;` — Gets the response code returned by the requested server. See EHttpResponseCodes for known response codes @return the response code.
- L133 _public prototype_ `virtual FString GetContentAsString() const = 0;` — Returns the payload as a string, assuming the payload is UTF8. @return the payload as a string.
- L141 _public prototype_ `virtual FUtf8StringView GetContentAsUtf8StringView() const = 0;` — Returns the payload as a utf8 string view. This does not validate that the response is valid utf8. It is the caller's responsibility, for example, by checking the Content-Type header @return the payload as a utf8 string view.
- L146 _public prototype_ `virtual ~IHttpResponse() = default;` — Destructor for overrides

#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "IHttpResponse"`
- L10 _namespace_ `namespace EHttpResponseCodes`
- L12 _variable_ `static constexpr TCHAR ErrorNamespace[] = TEXT("err` (scope `EHttpResponseCodes`)
- L16 _macro_ `#define HTTP_RESPONSE_CODE(Name, Value) Name = Value,` — Response codes that can come back from an Http request
- L24 _macro_ `#define HTTP_RESPONSE_CODE(Name,Value) case Name: return TEXT(#Value":"#Name);`
- L25 _function_ `inline FString ResponseCodeToString(Type ResponseCode)` (scope `EHttpResponseCodes`)
- L38 _function_ `inline bool IsOk(int32 StatusCode)` (scope `EHttpResponseCodes`) — @param StatusCode http response code to check @return true if the status code is an Ok response
- L43 _function_ `inline FString GetResponseCodeAsErrorCode(int32 StatusCode)` (scope `EHttpResponseCodes`)
- L52 _function_ `inline FText GetDescription(EHttpResponseCodes::Type StatusCode)` (scope `EHttpResponseCodes`) — @param StatusCode http response code to retrieve @return The status code description

### `Source/Runtime/Online/HTTP/Public/Interfaces/IHttpResponseCodes.inl` (Public)
_(no declarations extracted)_

### `Source/Runtime/Online/HTTP/Public/Linux/LinuxPlatformHttp.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Online/HTTP/Public/Mac/MacPlatformHttp.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Online/HTTP/Public/PlatformHttp.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Online/HTTP/Public/Unix/UnixPlatformHttp.h` (Public)


#### class `FUnixPlatformHttp`  
`class FUnixPlatformHttp : public FGenericPlatformHttp`  
_L14-41_
- inherits: `FGenericPlatformHttp`
- desc: Platform specific Http implementations
- L21 _public prototype_ `static void Init();` — Platform initialization step
- L28 _public prototype_ `static FHttpManager* CreatePlatformHttpManager();` — Creates a platform-specific HTTP manager. @return NULL if default implementation is to be used
- L33 _public prototype_ `static void Shutdown();` — Platform shutdown step
- L40 _public prototype_ `static IHttpRequest* ConstructRequest();` — Creates a new Http request instance for the current platform @return request object

#### Free symbols / members of external scopes

- L44 _typedef_ `typedef FUnixPlatformHttp FPlatformHttp;`

### `Source/Runtime/Online/HTTP/Public/Windows/WindowsPlatformHttp.h` (Public)


#### class `FWindowsPlatformHttp`  
`class FWindowsPlatformHttp : public FGenericPlatformHttp`  
_L11-69_
- inherits: `FGenericPlatformHttp`
- desc: Platform specific HTTP implementations.
- L16 _public prototype_ `static void Init();` — Platform initialization step.
- L23 _public prototype_ `static FHttpManager* CreatePlatformHttpManager();` — Creates a platform-specific HTTP manager. @return nullptr if default implementation is to be used.
- L26 _public prototype_ `static void Shutdown();` — Platform shutdown step.
- L33 _public prototype_ `static IHttpRequest* ConstructRequest();` — Creates a new HTTP request instance for the current platform. @return The request object.
- L38 _public prototype_ `static FString GetMimeType(const FString& FilePath);` — @return the mime type for the file.
- L45 _public prototype_ `static FString GetConfiguredProxyAddress();` — Get the proxy address from the highest-priority available source: command-line (-httpproxy=), INI ([HTTP] HttpProxyAddress), or OS proxy settings. It's to ensure FWindowsPlatformHttp::GetOperatingSystemProxyAddress() is called.
- L52 _public prototype_ `static TOptional<FString> GetOperatingSystemProxyAddress();` — Get the proxy address specified by the operating system @return optional FString: If unset: we are unable to get information from the operating system. If set: the proxy address set by the operating system (may be blank)
- L61 _public prototype_ `static bool IsOperatingSystemProxyInformationSupported();` — Check if getting proxy information from the current operating system is supported Useful for "Network Settings" type pages.  GetProxyAddress may return an empty or populated string but that does not imply the operating system does or does not support proxies (or that it has been implemented here) @return true if we are able to get proxy information from the current operating system, false if not
- L68 _public prototype_ `static bool VerifyPeerSslCertificate(bool verify);` — Verify Peer Ssl Certificate @return optional bool: the previous value

#### Free symbols / members of external scopes

- L72 _typedef_ `typedef FWindowsPlatformHttp FPlatformHttp;`
