# Developer / Zen

- module root: `Source/Developer/Zen`
- headers: 14; symbols: 739
- symbol kinds: class=14, enum=16, enumerator=70, function=41, macro=6, member=255, namespace=45, prototype=240, struct=39, typedef=12, variable=1
- PrivateDependencyModuleNames: Core, DevHttp, HTTP, Json, SSL, Sockets, StudioTelemetry
- PrivateIncludePathModuleNames: Analytics, DesktopPlatform
- PublicDependencyModuleNames: XCurl

### `Source/Developer/Zen/Internal/ZenAsyncCbPackageReceiver.h` (Internal)


#### class `UE::Zen::FAsyncCbPackageReceiver`  
`class FAsyncCbPackageReceiver : public IHttpReceiver`  
_L15-52_
- inherits: `IHttpReceiver`
- L18 _public typedef_ `using FOnComplete = TUniqueFunction<void(FAsyncCbPackageReceiver* Receiver)>;`
- L20 _public prototype_ `FAsyncCbPackageReceiver(const FAsyncCbPackageReceiver&) = delete;`
- L21 _public prototype_ `FAsyncCbPackageReceiver& operator=(const FAsyncCbPackageReceiver&) = delete;`
- L23 _public prototype_ `FAsyncCbPackageReceiver( THttpUniquePtr<IHttpRequest>&& InRequest, FZenServiceInstance& InZenServiceInstance, FOnComplete&& InOnComplete, int InMaxAttempts, bool InUseSoftRecovery);`
- L30 _public prototype_ `const IHttpResponse& GetHttpResponse();`
- L31 _public prototype_ `const FCbPackage& GetResponsePackage();`
- L33 _public prototype_ `void SendAsync();`
- L35 _public prototype_ `FString GetPayloadAsString() const;`
- L39 _protected prototype_ `IHttpReceiver* OnCreate(IHttpResponse& LocalResponse);`
- L40 _protected prototype_ `IHttpReceiver* OnComplete(IHttpResponse& LocalResponse);`
- L43 _protected member_ `THttpUniquePtr<IHttpRequest> Request;`
- L44 _protected member_ `THttpUniquePtr<IHttpResponse> Response;`
- L45 _protected member_ `FZenServiceInstance& ZenServiceInstance;`
- L46 _protected member_ `FCbPackage Package;`
- L47 _protected member_ `UE::Zen::FCbPackageReceiver BaseReceiver;`
- L48 _protected member_ `FOnComplete OnCompleteCallback;`
- L49 _protected member_ `const int MaxAttempts;`
- L50 _protected member_ `const bool UseSoftRecovery;`
- L51 _protected member_ `int Attempt;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Zen` (scope `UE`)

### `Source/Developer/Zen/Internal/ZenBackendUtils.h` (Internal)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Zen` (scope `UE`)
- L15 _function_ `inline void Memcpy(void* Dest, const FCompositeBuffer& Source, size_t SourceOffset, size_t Size)` (scope `UE::Zen`) — Copy Size bytes from Source at offset SourceOffset into Dest at offset 0.

### `Source/Developer/Zen/Internal/ZenBuildUtils.h` (Internal)


#### struct `UE::Zen::Build::FBuildState`  
`struct FBuildState`  
_L12-16_
- L14 _public member_ `FString Namespace;`
- L15 _public member_ `TArray<UE::Zen::Build::FBuildServiceInstance::FBuildRecord> Results;`

#### struct `UE::Zen::Build::FListBuildsState`  
`struct FListBuildsState`  
_L18-22_
- L20 _public member_ `std::atomic<uint32> PendingQueries;`
- L21 _public member_ `TArray<FBuildState> QueryState;`

#### struct `UE::Zen::Build::FBuildReference`  
`struct FBuildReference`  
_L24-29_
- L26 _public member_ `FString Namespace;`
- L27 _public member_ `FString Bucket;`
- L28 _public member_ `FCbObjectId BuildId;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ZEN_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Zen` (scope `UE`)
- L9 _namespace_ `namespace Build` (scope `UE::Zen`)
- L31 _prototype_ `bool TryParseBuildReferenceFromUrl(FStringView Url, FBuildReference& OutReference);` (scope `UE::Zen::Build`)

### `Source/Developer/Zen/Internal/ZenCbPackageReceiver.h` (Internal)


#### class `UE::Zen::FCbPackageReceiver`  
`class FCbPackageReceiver final : public IHttpReceiver`  
_L15-41_
- inherits: `IHttpReceiver`
- L18 _public prototype_ `FCbPackageReceiver(const FCbPackageReceiver&) = delete;`
- L19 _public prototype_ `FCbPackageReceiver& operator=(const FCbPackageReceiver&) = delete;`
- L21 _public prototype_ `explicit FCbPackageReceiver(FCbPackage& OutPackage, IHttpReceiver* InNext = nullptr);`
- L23 _public prototype_ `void Reset();`
- L24 _public prototype_ `const FMemoryView Body() const;`
- L26 _public prototype_ `bool ShouldRetry(FZenServiceInstance& ZenServiceInstance, IHttpResponse& LocalResponse, bool UseSoftRecovery) const;`
- L28 _public prototype_ `static FString GetPayloadAsString(EHttpMediaType ContentType, FMemoryView BodyView);`
- L31 _private prototype_ `IHttpReceiver* OnCreate(IHttpResponse& Response) final;`
- L32 _private prototype_ `IHttpReceiver* OnComplete(IHttpResponse& Response) final;`
- L34 _private prototype_ `bool TryRecover(Zen::FZenServiceInstance& ZenServiceInstance, bool UseSoftRecovery) const;`
- L37 _private member_ `FCbPackage& Package;`
- L38 _private member_ `IHttpReceiver* Next;`
- L39 _private member_ `TArray64<uint8> BodyArray;`
- L40 _private member_ `FHttpByteArrayReceiver BodyReceiver{BodyArray, this};`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Zen` (scope `UE`)

### `Source/Developer/Zen/Internal/ZenClient.h` (Internal)


#### enum `UE::Zen::EZenStreamStatus`  
`enum class EZenStreamStatus`  
_L14-20_
- desc: The stream response status.
- L16 _public enumerator_ `Ok`
- L17 _public enumerator_ `Error`
- L18 _public enumerator_ `Canceled`
- L19 _public enumerator_ `Completed`

#### struct `UE::Zen::FZenStreamResponse`  
`struct FZenStreamResponse`  
_L25-29_
- desc: Stream response.
- L27 _public member_ `FCbPackage Response;`
- L28 _public member_ `EZenStreamStatus Status = EZenStreamStatus::Error;`

#### class `UE::Zen::IZenClient`  
`class IZenClient`  
_L37-51_
- desc: Zen server web socket client.
- L40 _public prototype_ `virtual ~IZenClient() = default;`
- L42 _public prototype_ `virtual bool Connect(FStringView Host, int32 Port) = 0;`
- L43 _public prototype_ `virtual void Disconnect() = 0;`
- L44 _public prototype_ `virtual bool IsConnected() const = 0;`
- L46 _public prototype_ `virtual bool SendRequest(FCbPackage&& Request, FOnStreamResponse&& OnResponse) = 0;`
- L47 _public prototype_ `virtual bool SendRequest(FCbObject&& Request, FOnStreamResponse&& OnResponse) = 0;`
- L48 _public prototype_ `virtual bool SendStreamRequest(FCbObject&& Request, FOnStreamResponse&& OnStreamResponse) = 0;`
- L50 _public prototype_ `static TUniquePtr<IZenClient> Create();`

#### class `UE::Zen::IZenClientPool`  
`class IZenClientPool`  
_L56-70_
- desc: Zen server client pool.
- L59 _public prototype_ `virtual ~IZenClientPool() = default;`
- L61 _public prototype_ `virtual bool Connect(FStringView Host, int32 Port, int32 PoolSize = 8) = 0;`
- L62 _public prototype_ `virtual void Disconnect() = 0;`
- L63 _public prototype_ `virtual bool IsConnected() const = 0;`
- L65 _public prototype_ `virtual bool SendRequest(FCbPackage&& Request, FOnStreamResponse&& OnResponse) = 0;`
- L66 _public prototype_ `virtual bool SendRequest(FCbObject&& Request, FOnStreamResponse&& OnResponse) = 0;`
- L67 _public prototype_ `virtual bool SendStreamRequest(FCbObject&& Request, FOnStreamResponse&& OnStreamResponse) = 0;`
- L69 _public prototype_ `static TUniquePtr<IZenClientPool> Create();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Zen` (scope `UE`)
- L32 _typedef_ `using FOnStreamResponse = TUniqueFunction<void(FZenStreamResponse&& Response)>;` (scope `UE::Zen`) — Stream response callback.

### `Source/Developer/Zen/Internal/ZenSerialization.h` (Internal)


#### enum `UE::Zen::Http::RpcAcceptOptions`  
`enum class RpcAcceptOptions : uint32_t`  
_L28-33_
- L30 _public enumerator_ `kNone = 0`
- L31 _public enumerator_ `kAllowLocalReferences = (1u << 0)`
- L32 _public enumerator_ `kAllowPartialCacheChunks = (1u << 2)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Zen` (scope `UE`)
- L16 _namespace_ `namespace OpLog` (scope `UE::Zen`)
- L18 _prototype_ `void SaveCbAttachment(const FCbAttachment& Attachment, FCbWriter& Writer);` (scope `UE::Zen::OpLog`)
- L19 _prototype_ `void SaveCbPackage(const FCbPackage& Package, FCbWriter& Writer);` (scope `UE::Zen::OpLog`)
- L20 _prototype_ `void SaveCbPackage(const FCbPackage& Package, FArchive& Ar);` (scope `UE::Zen::OpLog`)
- L21 _prototype_ `bool TryLoadCbPackage(FCbPackage& Package, FArchive& Ar, FCbBufferAllocator Allocator = FUniqueBuffer::Alloc);` (scope `UE::Zen::OpLog`)
- L24 _namespace_ `namespace Http` (scope `UE::Zen`)
- L26 _variable_ `static const uint32 kCbPkgMagic = 0xaa77aacc;` (scope `UE::Zen::Http`)
- L35 _prototype_ `void SaveCbPackage(const FCbPackage& Package, FArchive& Ar);` (scope `UE::Zen::Http`)
- L36 _prototype_ `bool TryLoadCbPackage(FCbPackage& Package, FArchive& Ar, FCbBufferAllocator Allocator = FUniqueBuffer::Alloc);` (scope `UE::Zen::Http`)

### `Source/Developer/Zen/Internal/ZenServerHttp.h` (Internal)


#### enum `UE::Zen::EContentType`  
`enum class EContentType`  
_L40-52_
- L42 _public enumerator_ `Binary = 0`
- L43 _public enumerator_ `Text = 1`
- L44 _public enumerator_ `JSON = 2`
- L45 _public enumerator_ `CbObject = 3`
- L46 _public enumerator_ `CbPackage = 4`
- L47 _public enumerator_ `YAML = 5`
- L48 _public enumerator_ `CbPackageOffer = 6`
- L49 _public enumerator_ `CompressedBinary = 7`
- L50 _public enumerator_ `UnknownContentType = 8`
- L51 _public enumerator_ `Count`

#### class `UE::Zen::FZenHttpRequest`  
`class FZenHttpRequest`  
_L86-265_
- L89 _public prototype_ `FZenHttpRequest(const FZenServiceEndpoint& InDomain, bool bInLogErrors, uint32 InConnectTimeoutMS = 0, uint32 InTimeoutMS = 0);`
- L90 _public prototype_ `~FZenHttpRequest();`
- L95 _public prototype_ `void Reset();` — Resets all options on the request except those that should always be set.
- L100 _public prototype_ `void Initialize(bool bInLogErrors);` — Initializes a previously-allocated FZenHttpRequest with the options that can vary between requests
- L103 _public function_ `inline const int GetResponseCode() const` — Returns the HTTP response code.
- L108 _public function_ `inline const int GetErrorCode() const`
- L113 _public prototype_ `FAnsiStringView GetError() const;`
- L115 _public prototype_ `FString GetDetailedResultString(FStringView Uri) const;`
- L117 _public function_ `inline const bool GetResponseFormatValid() const`
- L123 _public function_ `inline const size_t GetBytesSent() const` — Returns the number of bytes sent during this request (headers withstanding).
- L144 _public prototype_ `Result PerformBlockingPut(const TCHAR* Uri, const FCompositeBuffer& Buffer, EContentType ContentType);` — Upload buffer using the request, using PUT verb @param Uri Url to use. @param Buffer Data to upload @param ContentType The content MIME type. @return Result of the request
- L154 _public prototype_ `Result PerformBlockingDownload(FStringView Uri, TArray64<uint8>* Buffer, EContentType AcceptType);` — Download an url into a buffer using the request. @param Uri Url to use. @param Buffer Optional buffer where data should be downloaded to. If this is null then downloaded data will be stored in an internal buffer and accessed via GetResponseAsString @param ContentType The MIME type to accept. @return Result of the request
- L162 _public prototype_ `Result PerformBlockingDownload(const TCHAR* Uri, FCbPackage& OutPackage);` — Download an url into a buffer using the request. @param Uri Url to use. @param OutPackage Package instance which will receive the data @result Request success/failure status
- L170 _public prototype_ `Result PerformBlockingHead(FStringView Uri, EContentType AcceptType);` — Query an url using the request. Queries can use either "Head" or "Delete" verbs. @param Uri Url to use. @param ContentType The MIME type to accept. @return Result of the request
- L177 _public prototype_ `Result PerformBlockingDelete(FStringView Uri);` — Query an url using the request. Queries can use either "Head" or "Delete" verbs. @param Uri Url to use. @return Result of the request
- L179 _public prototype_ `Result PerformBlockingPostPackage(FStringView Uri, const FCbPackage& Package, EContentType AcceptType = EContentType::UnknownContentType);`
- L181 _public prototype_ `Result PerformBlockingPost(FStringView Uri, FCbObjectView Obj, EContentType AcceptType = EContentType::UnknownContentType);`
- L183 _public prototype_ `Result PerformBlockingPost(FStringView Uri, FMemoryView Payload, EContentType ContentType = EContentType::Binary, EContentType AcceptType = EContentType::UnknownContentType);`
- L186 _public prototype_ `Result PerformRpc(FStringView Uri, FCbObjectView Request, FCbPackage &OutResponse);`
- L187 _public prototype_ `Result PerformRpc(FStringView Uri, const FCbPackage& Request, FCbPackage& OutResponse);`
- L192 _public prototype_ `FString GetResponseAsString() const;` — Returns the response buffer as a string. Note that if the request is performed with an external buffer as target buffer this string will be empty.
- L197 _public function_ `inline const TArray64<uint8>& GetResponseBuffer() const` — Returns the response buffer. Note that if the request is performed with an external buffer as target buffer this will be empty.
- L202 _public prototype_ `FCbObjectView GetResponseAsObject() const;`
- L203 _public prototype_ `FCbPackage GetResponseAsPackage() const;`
- L205 _public prototype_ `bool GetHeader(const ANSICHAR* Header, FString& OutValue) const;`
- L207 _public prototype_ `static FAnsiStringView LexResponseCodeToString(int HttpCode);`
- L211 _private member_ `CURL* Curl = nullptr;`
- L215 _private member_ `long CurlResult;`
- L216 _private member_ `long ResponseCode = 0;`
- L217 _private member_ `size_t BytesSent = 0;`
- L218 _private member_ `size_t BytesReceived = 0;`
- L219 _private member_ `bool bLogErrors = false;`
- L220 _private member_ `bool bResponseFormatValid = false;`
- L221 _private member_ `uint32 ConnectTimeoutMS = 0;`
- L222 _private member_ `uint32 TimeoutMS = 0;`
- L224 _private member_ `const FCompositeBuffer* ReadDataView = nullptr;`
- L225 _private member_ `TArray64<uint8>* WriteDataBufferPtr = nullptr;`
- L226 _private member_ `FCbPackage* WriteDataPackage = nullptr;`
- L227 _private member_ `TArray64<uint8>* WriteHeaderBufferPtr = nullptr;`
- L229 _private member_ `TArray64<uint8> ResponseHeader;`
- L230 _private member_ `TArray64<uint8> ResponseBuffer;` — If no other response buffer is set, this is where the response payload goes
- L231 _private member_ `TArray<FString> Headers;`
- L232 _private member_ `FString Domain;`
- L233 _private member_ `const FZenServiceEndpoint& Endpoint;`
- L235 _private prototype_ `void AddHeader(FStringView Header, FStringView Value);`
- L249 _private prototype_ `void LogResult(long Result, const TCHAR* Uri, RequestVerb Verb) const;`
- L258 _private prototype_ `Result PerformBlocking(FStringView Uri, RequestVerb Verb, uint64 ContentLength);` — Performs the request, blocking until finished. @param Uri Address on the domain to query @param Verb HTTP verb to use @param Buffer Optional buffer to directly receive the result of the request. If unset the response body will be stored in the request.
- L260 _private prototype_ `FZenHttpRequest::Result ParseRpcResponse(FZenHttpRequest::Result ResultFromPost, FCbPackage& OutResponse);`
- L262 _private prototype_ `static FString GetAnsiBufferAsString(const TArray64<uint8>& Buffer);`

#### enum `UE::Zen::FZenHttpRequest::Result`  
`enum class Result`  
_L131-135_
- desc: Convenience result type interpreted from HTTP response code.
- L133 _public enumerator_ `Success`
- L134 _public enumerator_ `Failed`

#### enum `UE::Zen::FZenHttpRequest::RequestVerb`  
`enum class RequestVerb`  
_L240-247_
- desc: Supported request verb
- L242 _public enumerator_ `Get`
- L243 _public enumerator_ `Put`
- L244 _public enumerator_ `Post`
- L245 _public enumerator_ `Delete`
- L246 _public enumerator_ `Head`

#### struct `UE::Zen::FZenHttpRequestPool`  
`struct FZenHttpRequestPool`  
_L273-297_
- desc: Pool which manages a fixed set of requests. Users are required to release requests that have been acquired. Intended to be used with \ref FScopedRequestPtr which handles lifetime management transparently
- L275 _public prototype_ `explicit FZenHttpRequestPool(const FZenServiceEndpoint& Endpoint, uint32 PoolEntryCount = 16);`
- L276 _public prototype_ `~FZenHttpRequestPool();`
- L282 _public prototype_ `FZenHttpRequest* WaitForFreeRequest();` — Block until a request is free. Once a request has been returned it is "owned by the caller and need to release it to the pool when work has been completed. @return Usable request instance.
- L287 _public prototype_ `void ReleaseRequestToPool(FZenHttpRequest* Request);` — Release request to the pool. @param Request Request that should be freed. Note that any buffer owned by the request can now be reset.
- L296 _private member_ `TArray<FEntry> Pool;`

#### struct `UE::Zen::FZenHttpRequestPool::FEntry`  
`struct FEntry`  
_L290-294_
- L292 _public member_ `std::atomic<uint8> IsAllocated;`
- L293 _public member_ `FZenHttpRequest* Request;`

#### struct `UE::Zen::FZenScopedRequestPtr`  
`struct FZenScopedRequestPtr`  
_L302-339_
- desc: Utility class to manage requesting and releasing requests from the \ref FRequestPool.
- L305 _public function_ `FZenScopedRequestPtr(FZenHttpRequestPool* InPool, bool bLogErrors=true) : Request(InPool->WaitForFreeRequest()) , Pool(InPool)`
- L312 _public function_ `~FZenScopedRequestPtr()`
- L317 _public function_ `inline bool IsValid() const`
- L322 _public function_ `inline operator bool() const`
- L324 _public function_ `FZenHttpRequest* operator->()`
- L330 _public function_ `FZenHttpRequest& operator*()`
- L337 _private member_ `FZenHttpRequest* Request;`
- L338 _private member_ `FZenHttpRequestPool* Pool;`

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Zen` (scope `UE`)
- L35 _function_ `static bool IsSuccessCode(int ResponseCode)` (scope `UE::Zen`)
- L54 _function_ `inline FStringView GetMimeType(EContentType Type)` (scope `UE::Zen`)

### `Source/Developer/Zen/Internal/ZenVersion.h` (Internal)


#### struct `UE::Zen::FZenVersion`  
`struct FZenVersion`  
_L11-23_
- L13 _public member_ `uint32 MajorVersion = 0;`
- L14 _public member_ `uint32 MinorVersion = 0;`
- L15 _public member_ `uint32 PatchVersion = 0;`
- L16 _public member_ `FString Details;`
- L18 _public prototype_ `void Reset();`
- L19 _public prototype_ `bool TryParse(const TCHAR* InString);`
- L20 _public prototype_ `FString ToString(bool bDetailed = true) const;`
- L21 _public prototype_ `bool operator<(FZenVersion& Other) const;`
- L22 _public prototype_ `operator bool() const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Zen` (scope `UE`)

### `Source/Developer/Zen/Private/ZenServerState.h` (Private)


#### class `ZenServerState`  
`class ZenServerState`  
_L10-56_
- L13 _public prototype_ `ZenServerState(bool ReadOnly);`
- L14 _public prototype_ `~ZenServerState();`
- L39 _public prototype_ `const ZenServerEntry* LookupByDesiredListenPort(int DesiredListenPort) const;`
- L40 _public prototype_ `ZenServerEntry* LookupByDesiredListenPort(int DesiredListenPort);`
- L41 _public prototype_ `const ZenServerEntry* LookupByEffectiveListenPort(int EffectiveListenPort) const;`
- L42 _public prototype_ `ZenServerEntry* LookupByEffectiveListenPort(int EffectiveListenPort);`
- L43 _public prototype_ `const ZenServerEntry* LookupByPid(uint32 Pid) const;`
- L45 _public prototype_ `static bool IsProcessRunning(uint32 Pid);`
- L46 _public prototype_ `static bool Terminate(uint32 Pid);`
- L47 _public prototype_ `static bool FindRunningProcessId(const TCHAR* ExecutablePath, uint32* OutPid);`
- L50 _private prototype_ `const ZenServerEntry* LookupByDesiredListenPortInternal(int DesiredListenPort) const;`
- L51 _private prototype_ `const ZenServerEntry* LookupByEffectiveListenPortInternal(int EffectiveListenPort) const;`
- L52 _private member_ `void* m_hMapFile = nullptr;`
- L53 _private member_ `ZenServerEntry* m_Data = nullptr;`
- L54 _private member_ `int m_MaxEntryCount = 65536 / sizeof(ZenServerEntry);`
- L55 _private member_ `bool m_IsReadOnly = true;`

#### struct `ZenServerState::ZenServerEntry`  
`struct ZenServerEntry`  
_L16-36_
- L21 _public member_ `std::atomic<uint32> Pid;` — This matches the structure found in the Zen server https://github.com/EpicGames/zen/blob/main/zenutil/include/zenutil/zenserverprocess.h#L91
- L22 _public member_ `std::atomic<uint16> DesiredListenPort;`
- L23 _public member_ `std::atomic<uint16> Flags;`
- L24 _public member_ `uint8 SessionId[12];`
- L25 _public member_ `std::atomic<uint32> SponsorPids[8];`
- L26 _public member_ `std::atomic<uint16> EffectiveListenPort;`
- L27 _public member_ `uint8 Padding[10];`
- L35 _public prototype_ `bool AddSponsorProcess(uint32 PidToAdd);`

#### enum `ZenServerState::ZenServerEntry::FlagsEnum`  
`enum class FlagsEnum : uint16`  
_L29-33_
- L31 _public enumerator_ `kShutdownPlease = 1 << 0`
- L32 _public enumerator_ `kIsReady = 1 << 1`

#### class `ZenSharedEvent`  
`class ZenSharedEvent`  
_L58-92_
- L61 _public prototype_ `ZenSharedEvent() = delete;`
- L62 _public prototype_ `ZenSharedEvent(const ZenSharedEvent&) = delete;`
- L63 _public prototype_ `ZenSharedEvent(ZenSharedEvent&&) = delete;`
- L64 _public prototype_ `ZenSharedEvent& operator =(const ZenSharedEvent&) = delete;`
- L65 _public prototype_ `ZenSharedEvent& operator =(ZenSharedEvent&&) = delete;`
- L67 _public prototype_ `explicit ZenSharedEvent(FStringView EventName);`
- L68 _public prototype_ `~ZenSharedEvent();`
- L70 _public prototype_ `bool Create();`
- L71 _public prototype_ `bool Exists() const;`
- L72 _public prototype_ `bool Open();`
- L73 _public prototype_ `bool Wait(int TimeoutMs = -1);`
- L74 _public prototype_ `bool Set();`
- L75 _public prototype_ `void Close();`
- L77 _public prototype_ `static FString GetShutdownEventName(uint16 EffectiveListenPort);`
- L78 _public prototype_ `static FString GetStartupEventName();`
- L81 _private member_ `FString m_EventName;`
- L84 _private prototype_ `FString GetFullEventName() const;`
- L85 _private member_ `void* m_EventHandle = NULL;`
- L87 _private prototype_ `FAnsiString GetEventPath() const;`
- L88 _private member_ `int m_Fd = -1;`
- L89 _private member_ `int m_Semaphore = -1;`
- L90 _private member_ `FAnsiString m_EventPath;`

#### struct `ZenLockFileData`  
`struct ZenLockFileData`  
_L94-106_
- L96 _public member_ `uint32 ProcessId = 0;`
- L97 _public member_ `FCbObjectId SessionId;`
- L98 _public member_ `uint16 EffectivePort = 0;`
- L99 _public member_ `bool IsReady = false;`
- L100 _public member_ `FString DataDir;`
- L101 _public member_ `FString ExecutablePath;`
- L102 _public member_ `bool IsValid = false;`
- L104 _public prototype_ `static bool IsLockFileLocked(const TCHAR* FileName, bool bAttemptCleanUp = false);`
- L105 _public prototype_ `static ZenLockFileData ReadCbLockFile(const TCHAR* FileName);`

### `Source/Developer/Zen/Public/Experimental/BuildListRetriever.h` (Public)


#### class `UE::Zen::Build::FBuildListRetriever`  
`class FBuildListRetriever : public TSharedFromThis<FBuildListRetriever>`  
_L20-102_
- inherits: `TSharedFromThis<FBuildListRetriever>`
- desc: Helper class to query a list of builds for a project of a specified build type in a P4 stream. Call ConnectToBuildService() first to establish connection, before calling QueryBuilds() to retrieve the builds, build query is asynchronous.
- L38 _public prototype_ `FBuildListRetriever();`
- L39 _public typedef_ `typedef TMap<FString, TArray<int32>> FPlatformBuildsMap;`
- L40 _public typedef_ `typedef TUniqueFunction<void()> FOnReadyForQuery;`
- L41 _public typedef_ `typedef TUniqueFunction<void(const FPlatformBuildsMap&)> FOnQueriesComplete;`
- L42 _public typedef_ `typedef TUniqueFunction<void(const TArrayView<TSharedRef<FBuildGroup>>&)> FOnGroupQueriesComplete;`
- L43 _public prototype_ `void ConnectToBuildService();`
- L44 _public prototype_ `bool IsConnected() const;`
- L45 _public prototype_ `bool QueryBuilds(const FString& InProjectName, const FString& InBuildType, const FString& InStream, FOnQueriesComplete&& InOnQueriesCompleteCallback);`
- L46 _public prototype_ `bool QueryBuildGroups(const FString& InProjectName, const FString& InBuildType, const FString& InStream, FOnGroupQueriesComplete&& InOnQueriesCompleteCallback);`
- L47 _public prototype_ `bool IsReadyForQuery() const;`
- L48 _public prototype_ `void SetOnReadyForQuery( FOnReadyForQuery&& InOnReadyForQuery );`
- L49 _public prototype_ `void Refresh();`
- L51 _public prototype_ `TSharedRef<FBuildServiceInstance> GetServiceInstance() const;`
- L71 _public prototype_ `TMap<FString,TSharedRef<FBuildType, ESPMode::ThreadSafe>> GenerateBuildTypesMap() const;`
- L81 _public prototype_ `static bool GetBucketInfo( const FString& BucketId, FBucketInfo& OutBucketInfo );`
- L84 _private prototype_ `void OnNamespacesAndBucketsRefreshed();`
- L85 _private prototype_ `void IssueBuildQueries(bool bIsGroupQuery);`
- L86 _private prototype_ `void ExtractBuildsFromQueryResult(FListBuildsState& ListBuildsState);`
- L87 _private prototype_ `TArray<TSharedRef<FBuildGroup>> ExtractBuildGroupsFromQueryResult(FListBuildsState& ListBuildsState);`
- L88 _private prototype_ `TSharedRef<FBuildType, ESPMode::ThreadSafe> MakeBuildType(const FString& InBuildTypeName) const;`
- L91 _private member_ `FString ProjectName;`
- L92 _private member_ `FString BuildType;`
- L93 _private member_ `FString Stream;`
- L95 _private member_ `mutable TSharedPtr<FBuildServiceInstance> ServiceInstance;`
- L96 _private member_ `FPlatformBuildsMap PerPlatformBuilds;`
- L97 _private member_ `FOnReadyForQuery OnReadyForQuery;`
- L98 _private member_ `FOnQueriesComplete OnQueriesCompleteCallback;`
- L99 _private member_ `FOnGroupQueriesComplete OnGroupQueriesCompleteCallback;`
- L100 _private member_ `bool ReadyToIssueBuildQuery = false;` — Should only be accessed from the game thread
- L101 _private member_ `bool bConnected = false;`

#### struct `UE::Zen::Build::FBuildListRetriever::FBuildGroup`  
`struct FBuildGroup : public TSharedFromThis<FBuildGroup>`  
_L23-35_
- inherits: `TSharedFromThis<FBuildGroup>`
- L25 _public member_ `FString Namespace;`
- L26 _public member_ `FString DisplayName;`
- L27 _public member_ `FString CommitIdentifier;`
- L28 _public member_ `int32 Changelist;`
- L29 _public member_ `FDateTime CreatedAt;`
- L30 _public member_ `FString Category;`
- L31 _public member_ `FString Job;`
- L32 _public member_ `FString Suffix;`
- L33 _public member_ `TMap<FString, UE::Zen::Build::FBuildServiceInstance::FBuildRecord> NamedArtifacts;`
- L34 _public member_ `bool bIsPreflight;`

#### enum `UE::Zen::Build::FBuildListRetriever::EBuildType`  
`enum class EBuildType`  
_L54-63_
- L56 _public enumerator_ `Oplog`
- L57 _public enumerator_ `StagedBuild`
- L58 _public enumerator_ `PackagedBuild`
- L59 _public enumerator_ `EditorPreCompiledBinary`
- L60 _public enumerator_ `EditorInstalledBuild`
- L61 _public enumerator_ `Unknown`
- L62 _public enumerator_ `Count`

#### struct `UE::Zen::Build::FBuildListRetriever::FBuildType`  
`struct FBuildType : TSharedFromThis<FBuildType>`  
_L64-69_
- inherits: `TSharedFromThis<FBuildType>`
- L66 _public member_ `EBuildType Type;`
- L67 _public member_ `FText DisplayName;`
- L68 _public member_ `int Order;`

#### struct `UE::Zen::Build::FBuildListRetriever::FBucketInfo`  
`struct FBucketInfo`  
_L74-80_
- L76 _public member_ `FString Project;`
- L77 _public member_ `FString BuildType;`
- L78 _public member_ `FString Stream;`
- L79 _public member_ `FString Platform;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ZEN_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Zen` (scope `UE`)
- L14 _namespace_ `namespace Build` (scope `UE::Zen`)

### `Source/Developer/Zen/Public/Experimental/BuildServerInterface.h` (Public)


#### struct `UE::Zen::Build::FServiceSettings`  
`struct FServiceSettings`  
_L37-50_
- L40 _public prototype_ `bool ReadFromConfig();`
- L41 _public prototype_ `bool ReadFromURL(FStringView InstanceURL);`
- L43 _public function_ `inline const FString& GetHost() const`
- L44 _public function_ `inline const FString& GetAuthScheme() const`
- L45 _public function_ `inline const FString& GetOAuthProviderIdentifier() const`
- L47 _private member_ `FString Host;`
- L48 _private member_ `FString AuthScheme;`
- L49 _private member_ `FString OAuthProviderIdentifier;`

#### enum `UE::Zen::Build::EBuildTransferRequestFlags`  
`enum class EBuildTransferRequestFlags`  
_L52-63_
- L54 _public enumerator_ `None = 0`
- L55 _public enumerator_ `Clean = 1 << 0`
- L56 _public enumerator_ `Force = 1 << 1`
- L57 _public enumerator_ `Scavenge = 1 << 2`
- L58 _public enumerator_ `Verify = 1 << 3`
- L59 _public enumerator_ `BoostWorkerCount = 1 << 4`
- L60 _public enumerator_ `BoostWorkerMemory = 1 << 5`
- L61 _public enumerator_ `BoostWorkers = BoostWorkerCount | BoostWorkerMemory`
- L62 _public enumerator_ `Append = 1 << 6`

#### class `UE::Zen::Build::FBuildServiceInstance`  
`class FBuildServiceInstance`  
_L66-252_
- L150 _public typedef_ `typedef TUniqueFunction<void(EConnectionState, EConnectionFailureReason)> FOnConnectionComplete;`
- L151 _public typedef_ `typedef TUniqueFunction<void()> FOnRefreshNamespacesAndBucketsComplete;`
- L152 _public typedef_ `typedef TUniqueFunction<void(TArray<FBuildRecord>&& ListBuildRecords)> FOnListBuildsComplete;`
- L153 _public typedef_ `typedef TUniqueFunction<void(TMap<FString, FBuildPart>&& BuildContents)> FOnListBuildContentsComplete;`
- L156 _public prototype_ `FBuildServiceInstance();`
- L157 _public prototype_ `FBuildServiceInstance(FStringView InstanceURL);`
- L159 _public prototype_ `virtual ~FBuildServiceInstance();`
- L161 _public function_ `const FServiceSettings& GetSettings() const`
- L166 _public prototype_ `void Connect(bool bAllowInteractive, FOnConnectionComplete&& OnConnectionComplete = {});`
- L167 _public prototype_ `void RefreshNamespacesAndBuckets(FOnRefreshNamespacesAndBucketsComplete&& InOnRefreshNamespacesAndBucketsComplete = {});`
- L168 _public prototype_ `[[nodiscard]] EConnectionState GetConnectionState() const;`
- L169 _public prototype_ `[[nodiscard]] FAnsiStringView GetEffectiveDomain() const;`
- L171 _public function_ `[[nodiscard]] TMulticastDelegateRegistration<void()>& OnRefreshNamespacesAndBucketsComplete()`
- L173 _public function_ `inline const TMultiMap<FString, FString>& GetNamespacesAndBuckets() const`
- L175 _public prototype_ `void ListBuilds(FStringView Namespace, FStringView Bucket, FCbObject&& Query, FOnListBuildsComplete&& InOnListBuildsComplete);`
- L176 _public prototype_ `void ListBuildsAcrossBuckets(FStringView Namespace, FStringView BucketRegex, FCbObject&& Query, FOnListBuildsComplete&& InOnListBuildsComplete);`
- L177 _public prototype_ `void ListBuildContents(FStringView Namespace, FStringView Bucket, FStringView BuildId, FOnListBuildContentsComplete&& InOnListBuildContentsComplete);`
- L179 _public prototype_ `FBuildTransfer StartBuildTransfer( const FCbObjectId& BuildId, FStringView Name, FStringView DestinationFolder, FStringView Namespace, FStringView Bucket, FStringView IncludeFilter = FStringView(), FStringView ExcludeFilter = FStringView(), FString&& DownloadSpecJSONContents = FString(), TArray<FString>&& PartIds = TArray<FString>(), TArray<FString>&& PartNames = TArray<FString>(), FStringView HostOverride = FStringView(), EBuildTransferRequestFlags RequestFlags = EBuildTransferRequestFlags::Scavenge );`
- L193 _public prototype_ `FBuildTransfer StartOplogBuildTransfer( const FCbObjectId& BuildId, FStringView Name, FStringView DestinationProjectId, FStringView DestinationOplogId, FStringView RootDir, FStringView EngineDir, FStringView ProjectFilePath, FStringView Namespace, FStringView Bucket, FName TargetPlatformName, FStringView HostOverride = FStringView(), EBuildTransferRequestFlags RequestFlags = EBuildTransferRequestFlags::Clean );`
- L207 _public prototype_ `FBuildTransfer RepeatBuildTransfer(FBuildTransfer ExistingTransfer);`
- L209 _private typedef_ `typedef TUniqueFunction<void(FString& CommandLineArgs)> FPreZenUtilityInvocation;`
- L210 _private typedef_ `typedef TUniqueFunction<void(bool)> FOnZenUtilityInvocationComplete;`
- L212 _private prototype_ `void Initialize();`
- L213 _private prototype_ `bool AcquireAccessToken(EDesktopLoginInteractionLevel InteractionLevel);`
- L214 _private prototype_ `void SetAccessTokenAndUnlock(FScopeLock &Lock, FStringView Token, double RefreshDelay = 0.0);`
- L215 _private prototype_ `[[nodiscard]] FString GetAccessToken() const;`
- L216 _private prototype_ `FString AddZenUtilityBuildServerArguments(const TCHAR* InCommandLineArgs) const;`
- L217 _private prototype_ `bool InvokeZenUtilitySync(FStringView CommandlineArgs, FString* Output = nullptr);`
- L218 _private prototype_ `void InvokeZenUtility(FStringView CommandlineArgs, FPreZenUtilityInvocation&& PreInvocation, FOnZenUtilityInvocationComplete&& OnComplete);`
- L219 _private prototype_ `void CallOnRefreshNamespacesAndBucketsComplete(FOnRefreshNamespacesAndBucketsComplete&& InOnRefreshNamespacesAndBucketsComplete);`
- L221 _private prototype_ `void RecordAcquireAccessTokenEvent(bool Succeeded, const FString& MessageString = {});`
- L222 _private prototype_ `void RecordConnectionEvent(bool Succeeded, const FString& MessageString = {});`
- L223 _private prototype_ `void RecordZenServerEvent(bool Succeeded, const FString& MessageString = {});`
- L224 _private prototype_ `void RecordTransferStateEvent(TSharedRef<Private::FBuildTransferState> State);`
- L226 _private prototype_ `void KickBuildTransferThread();`
- L227 _private prototype_ `void BuildTransferThreadLoop();`
- L229 _private member_ `TMulticastDelegate<void()> RefreshNamespacesAndBucketsComplete;`
- L230 _private member_ `std::atomic<EConnectionState> ConnectionState = EConnectionState::NotStarted;`
- L232 _private member_ `FCriticalSection AccessCs;`
- L233 _private member_ `TUniquePtr<Private::FAccessToken> Access;`
- L234 _private member_ `FTSTicker::FDelegateHandle RefreshAccessTokenHandle;`
- L235 _private member_ `double RefreshAccessTokenTime = 0.0;`
- L236 _private member_ `uint32 LoginAttempts = 0;`
- L237 _private member_ `uint32 FailedLoginAttempts = 0;`
- L238 _private member_ `uint32 InteractiveLoginAttempts = 0;`
- L240 _private member_ `FRWLock NamespacesAndBucketsLock;`
- L241 _private member_ `TMultiMap<FString, FString> NamespacesAndBuckets;`
- L243 _private member_ `TPimplPtr<FScopeZenService> ZenService;`
- L245 _private member_ `TMpscQueue<TSharedRef<Private::FBuildTransferState>> BuildTransferThreadStates;`
- L246 _private member_ `FThread BuildTransferThread;`
- L247 _private member_ `std::atomic<bool> bBuildTransferThreadStarting = false;`
- L248 _private member_ `std::atomic<bool> bBuildTransferThreadStopping = false;`
- L250 _private member_ `FServiceSettings Settings;`
- L251 _private member_ `FAnsiString EffectiveDomain;`

#### enum `UE::Zen::Build::FBuildServiceInstance::EBuildTransferStatus`  
`enum class EBuildTransferStatus`  
_L70-78_
- L72 _public enumerator_ `Invalid`
- L73 _public enumerator_ `Queued`
- L74 _public enumerator_ `Active`
- L75 _public enumerator_ `Failed`
- L76 _public enumerator_ `Canceled`
- L77 _public enumerator_ `Succeeded`

#### enum `UE::Zen::Build::FBuildServiceInstance::EConnectionState`  
`enum class EConnectionState`  
_L80-86_
- L82 _public enumerator_ `NotStarted`
- L83 _public enumerator_ `ConnectionInProgress`
- L84 _public enumerator_ `ConnectionSucceeded`
- L85 _public enumerator_ `ConnectionFailed`

#### enum `UE::Zen::Build::FBuildServiceInstance::EConnectionFailureReason`  
`enum class EConnectionFailureReason`  
_L88-96_
- L90 _public enumerator_ `MissingHost`
- L91 _public enumerator_ `FailedToResolveHost`
- L92 _public enumerator_ `FailedToAcquireAccessToken`
- L93 _public enumerator_ `UnexpectedState`
- L94 _public enumerator_ `Unknown`
- L95 _public enumerator_ `None`

#### struct `UE::Zen::Build::FBuildServiceInstance::FBuildRecord`  
`struct FBuildRecord`  
_L98-106_
- L100 _public member_ `FCbObjectId BuildId;`
- L101 _public member_ `FString BucketId;`
- L102 _public member_ `FCbObject Metadata;`
- L104 _public prototype_ `FString GetCommitIdentifier() const;`
- L105 _public prototype_ `FString GetCookPlatform() const;`

#### struct `UE::Zen::Build::FBuildServiceInstance::FBuildFile`  
`struct FBuildFile`  
_L108-113_
- L110 _public member_ `FString Name;`
- L111 _public member_ `uint64 RawSize = 0;`
- L112 _public member_ `uint32 Attributes = 0;`

#### struct `UE::Zen::Build::FBuildServiceInstance::FBuildPart`  
`struct FBuildPart`  
_L115-119_
- L117 _public member_ `FCbObjectId Id;`
- L118 _public member_ `TArray<FBuildFile> Files;`

#### struct `UE::Zen::Build::FBuildServiceInstance::FBuildTransfer`  
`struct FBuildTransfer`  
_L121-148_
- L131 _public prototype_ `EType GetType() const;`
- L132 _public prototype_ `FString GetDestination() const;`
- L134 _public prototype_ `FString GetDescription() const;`
- L135 _public prototype_ `FString GetRecentOutput() const;`
- L136 _public prototype_ `EBuildTransferStatus GetStatus() const;`
- L137 _public prototype_ `FString GetLogFilename() const;`
- L139 _public prototype_ `FMonotonicTimeSpan GetTransferDuration() const;`
- L141 _public prototype_ `bool GetCurrentProgress(FString& OutLabel, FString& OutDetail, float& OutPercent) const;`
- L142 _public prototype_ `bool GetOverallProgress(FString& OutLabel, FString& OutDetail, float& OutPercent) const;`
- L144 _public prototype_ `void RequestCancel();`
- L146 _private member_ `TSharedPtr<Private::FBuildTransferState> State;`

#### enum `UE::Zen::Build::FBuildServiceInstance::FBuildTransfer::EType`  
`enum class EType`  
_L124-129_
- L126 _public enumerator_ `Files`
- L127 _public enumerator_ `Oplog`
- L128 _public enumerator_ `Count`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API ZEN_API`
- L29 _namespace_ `namespace UE`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Zen` (scope `UE`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace Zen` (scope `UE`)
- L31 _namespace_ `namespace Build` (scope `UE::Zen`)
- L31 _namespace_ `namespace Private` (scope `UE::Zen::Build`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Zen` (scope `UE`)
- L32 _namespace_ `namespace Build` (scope `UE::Zen`)
- L32 _namespace_ `namespace Private` (scope `UE::Zen::Build`)
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace Zen` (scope `UE`)
- L34 _namespace_ `namespace Build` (scope `UE::Zen`)
- L64 _prototype_ `ENUM_CLASS_FLAGS(EBuildTransferRequestFlags);` (scope `UE::Zen::Build`)
- L254 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FBuildServiceInstance::FBuildRecord& OutBuildRecord);` (scope `UE::Zen::Build`)

### `Source/Developer/Zen/Public/Experimental/ZenProjectStoreWriter.h` (Public)


#### class `UE::Zen::FZenProjectStoreWriter`  
`class FZenProjectStoreWriter`  
_L14-23_
- L17 _public prototype_ `FZenProjectStoreWriter(const TCHAR* TargetFileName);`
- L18 _public prototype_ `~FZenProjectStoreWriter() = default;`
- L20 _public prototype_ `bool Write(FStringView ServiceHostName, uint16 ServicePort, const FString& HostAuthJson, bool bIsRunningLocally, FStringView ProjectId, FStringView OplogId, FName TargetPlatformName);`
- L22 _private member_ `TUniquePtr<FArchive> OplogMarker;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ZEN_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Zen` (scope `UE`)

### `Source/Developer/Zen/Public/Experimental/ZenServerInterface.h` (Public)


#### enum `UE::Zen::ERemoteNetworkService`  
`enum class ERemoteNetworkService : uint8`  
_L29-34_
- L31 _public enumerator_ `None`
- L32 _public enumerator_ `Unsecured`
- L33 _public enumerator_ `GeneratedStaticKey`

#### struct `UE::Zen::FServiceConnectSettings`  
`struct FServiceConnectSettings`  
_L36-40_
- L38 _public member_ `FString HostName;`
- L39 _public member_ `uint16 Port = 8558;`

#### struct `UE::Zen::FServicePluginSettings`  
`struct FServicePluginSettings`  
_L42-52_
- L44 _public member_ `FString Name;`
- L45 _public member_ `FString AbsPath;`
- L46 _public member_ `TMap<FName, FString> Options;`
- L47 _public member_ `bool bNeedsInstall = false;`
- L49 _public prototype_ `bool ReadFromConfig(const FString& InPluginName);`
- L50 _public prototype_ `bool ReadFromCompactBinary(FCbFieldView Field);`
- L51 _public prototype_ `void WriteToCompactBinary(FCbWriter& Writer) const;`

#### struct `UE::Zen::FServiceAutoLaunchSettings`  
`struct FServiceAutoLaunchSettings`  
_L54-71_
- L56 _public member_ `FString DataPath;`
- L57 _public member_ `FString ExtraArgs;`
- L58 _public member_ `uint16 DesiredPort = 8558;`
- L59 _public member_ `TArray<FServicePluginSettings> Plugins;`
- L60 _public member_ `bool bShowConsole = false;`
- L61 _public member_ `bool bIsDefaultDataPath = false;`
- L62 _public member_ `bool bLimitProcessLifetime = false;`
- L63 _public member_ `ERemoteNetworkService RemoteNetworkService = ERemoteNetworkService::None;`
- L64 _public member_ `bool bSendUnattendedBugReports = false;`
- L65 _public member_ `bool bIsDefaultSharedRunContext = true;`
- L70 _public member_ `} InstallMode = EInstallMode::Copy;`

#### enum `UE::Zen::FServiceAutoLaunchSettings::EInstallMode`  
`enum class EInstallMode`  
_L66-70_
- L68 _public enumerator_ `Copy`
- L69 _public enumerator_ `Link`

#### struct `UE::Zen::FSystemServiceSettings`  
`struct FSystemServiceSettings`  
_L73-81_
- L75 _public member_ `FString InstallPath;`
- L76 _public member_ `FString DataPath;`
- L77 _public member_ `FString ExtraArgs;`
- L78 _public member_ `uint16 DesiredPort = 8558;`
- L79 _public member_ `bool bSendUnattendedBugReports = false;`
- L80 _public member_ `ERemoteNetworkService RemoteNetworkService = ERemoteNetworkService::None;`

#### struct `UE::Zen::FServiceSettings`  
`struct FServiceSettings`  
_L83-108_
- L85 _public member_ `bool bSystemService = false;`
- L86 _public member_ `FSystemServiceSettings SystemServiceSettings;`
- L87 _public member_ `TVariant<FServiceAutoLaunchSettings, FServiceConnectSettings> SettingsVariant;`
- L89 _public function_ `inline bool IsSystemService() const`
- L90 _public function_ `inline bool IsAutoLaunch() const`
- L91 _public function_ `inline bool IsConnectExisting() const`
- L92 _public function_ `inline bool IsRequirePlugins() const`
- L93 _public function_ `inline ERemoteNetworkService GetRemoteNetworkService() const`
- L100 _public prototype_ `bool ReadFromConfig();`
- L101 _public prototype_ `bool ReadFromCompactBinary(FCbFieldView Field);`
- L102 _public prototype_ `bool ReadFromURL(FStringView InstanceURL);`
- L104 _public prototype_ `void WriteToCompactBinary(FCbWriter& Writer) const;`
- L107 _private prototype_ `bool TryApplyAutoLaunchOverride();`

#### struct `UE::Zen::FZenWorkspaces`  
`struct FZenWorkspaces`  
_L110-171_
- L128 _public member_ `TArray<Workspace> ZenWorkspaces;`
- L129 _public member_ `bool bIsValid = false;`
- L131 _public function_ `bool operator==(const FZenWorkspaces& Other) const`

#### struct `UE::Zen::FZenWorkspaces::Share`  
`struct Share`  
_L112-117_
- L114 _public member_ `FString Id;`
- L115 _public member_ `FString Dir;`
- L116 _public member_ `FString Alias;`

#### struct `UE::Zen::FZenWorkspaces::Workspace`  
`struct Workspace`  
_L119-126_
- L121 _public member_ `FString Id;`
- L122 _public member_ `FString BaseDir;`
- L123 _public member_ `bool bDynamicShare;`
- L125 _public member_ `TArray<Share> WorkspaceShares;`

#### class `UE::Zen::FZenLocalServiceRunContext`  
`class FZenLocalServiceRunContext`  
_L198-229_
- L201 _public function_ `FString GetExecutable() const`
- L202 _public function_ `FString GetCommandlineArguments() const`
- L203 _public function_ `FString GetWorkingDirectory() const`
- L204 _public function_ `FString GetDataPath() const`
- L205 _public function_ `bool GetShowConsole() const`
- L206 _public function_ `bool GetLimitProcessLifetime() const`
- L214 _private member_ `FString Executable;`
- L215 _private member_ `FString CommandlineArguments;`
- L216 _private member_ `FString WorkingDirectory;`
- L217 _private member_ `FString DataPath;`
- L218 _private member_ `bool bShowConsole = false;`
- L219 _private member_ `bool bLimitProcessLifetime = false;`
- L221 _private prototype_ `bool ReadFromJson(FJsonObject& JsonObject);`
- L222 _private prototype_ `void WriteToJson(TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>& Writer) const;`
- L224 _private prototype_ `bool ReadFromJsonFile(const TCHAR* Filename);`
- L225 _private prototype_ `bool WriteToJsonFile(const TCHAR* Filename) const;`

#### struct `UE::Zen::FGCStatus`  
`struct FGCStatus`  
_L241-244_
- L243 _public member_ `FString Description;`

#### class `UE::Zen::FZenServiceEndpoint`  
`class FZenServiceEndpoint`  
_L246-267_
- L255 _public prototype_ `FZenServiceEndpoint() = default;`
- L256 _public prototype_ `FZenServiceEndpoint(FStringView InName, uint16 InPort);`
- L257 _public function_ `ESocketType GetSocketType() const`
- L258 _public function_ `FStringView GetName() const`
- L259 _public prototype_ `FStringView GetHostName() const;`
- L260 _public prototype_ `FString GetURL() const;`
- L261 _public function_ `uint16 GetPort() const`
- L264 _private member_ `FString Name = TEXT("loc`
- L265 _private member_ `uint16 Port = 8558;`
- L266 _private member_ `ESocketType SocketType = ESocketType::Tcp;`

#### enum `UE::Zen::FZenServiceEndpoint::ESocketType`  
`enum class ESocketType : uint8`  
_L249-253_
- L251 _public enumerator_ `Tcp`
- L252 _public enumerator_ `Unix`

#### class `UE::Zen::FScopeZenService`  
`class FScopeZenService`  
_L275-290_
- desc: Type used to declare usage of a Zen server instance whether the shared default instance or a unique non-default instance. Used to help manage launch, and optionally in the future, shutdown a shared default instance.  Use the default constructor to reference the default instance (which may be launched on demand), or use the non-default constructors with a specific URL or HostName/Port pair which is required to pre-exist (will not be auto-launched).
- L278 _public prototype_ `FScopeZenService();`
- L279 _public prototype_ `FScopeZenService(FStringView InstanceURL);`
- L280 _public prototype_ `FScopeZenService(FServiceSettings&& InSettings);`
- L281 _public prototype_ `~FScopeZenService();`
- L284 _public function_ `const FZenServiceInstance& GetInstance() const`
- L285 _public function_ `FZenServiceInstance& GetInstance()`
- L288 _private member_ `FZenServiceInstance* ServiceInstance;`
- L289 _private member_ `TUniquePtr<UE::Zen::FZenServiceInstance> UniqueNonDefaultInstance;`

#### class `UE::Zen::FZenServiceInstance`  
`class FZenServiceInstance`  
_L312-385_
- desc: A representation of a Zen service instance.  Generally not accessed directly, but via FScopeZenService.
- L316 _public prototype_ `FZenServiceInstance();`
- L317 _public prototype_ `FZenServiceInstance(FStringView InstanceURL);`
- L318 _public prototype_ `FZenServiceInstance(FServiceSettings&& InSettings);`
- L319 _public prototype_ `~FZenServiceInstance();`
- L321 _public prototype_ `const FString GetPath() const;`
- L322 _public function_ `inline const FServiceSettings& GetServiceSettings() const`
- L323 _public prototype_ `bool IsServiceRunning();`
- L324 _public prototype_ `bool IsServiceReady();`
- L325 _public function_ `bool IsServiceRunningLocally() const`
- L326 _public function_ `const FZenServiceEndpoint& GetEndpoint() const`
- L334 _public prototype_ `bool TryRecovery(ERecoveryMode RecoveryMode);`
- L336 _public prototype_ `bool GetCacheStats(FZenCacheStats& Stats);`
- L337 _public prototype_ `bool GetProjectStats(FZenProjectStats& Stats);`
- L338 _public prototype_ `bool GatherAnalytics(TArray<FAnalyticsEventAttribute>& Attributes);`
- L340 _public prototype_ `int32 GetWorkspaceCount() const;`
- L341 _public prototype_ `bool GetWorkspaces(FZenWorkspaces& Workspaces) const;`
- L343 _public prototype_ `bool GetGCStatus(FGCStatus& Status);`
- L344 _public prototype_ `bool RequestGC(const bool* OverrideCollectSmallObjects = nullptr, const uint32* OverrideMaxCacheDuration = nullptr);`
- L346 _public prototype_ `bool AddSponsorProcessIDs(TArrayView<uint32> SponsorProcessIDs);`
- L348 _public prototype_ `static uint16 GetAutoLaunchedPort();`
- L352 _private prototype_ `void Initialize();`
- L353 _private prototype_ `bool ConditionalUpdateLocalInstall(FServiceAutoLaunchSettings::EInstallMode InstallMode);`
- L354 _private prototype_ `bool WriteLocalPluginsConfig();`
- L355 _private prototype_ `static bool AutoLaunch(const FServiceAutoLaunchSettings& InSettings, const FString& ExecutablePath, const FString& ExecutionContextFilePath, FZenServiceEndpoint& OutEndpoint);`
- L356 _private prototype_ `bool ConditionalUpdateSystemServiceInstall(const FSystemServiceSettings& InSettings);`
- L357 _private prototype_ `bool PingService(uint32_t AttemptCount, bool Silent);`
- L359 _private member_ `mutable TFuture<TOptional<FGCStatus>> GCStatusRequest;`
- L360 _private member_ `mutable TOptional<FGCStatus> LastGCStatus;`
- L361 _private member_ `mutable uint64 LastGCStatusTime = 0;`
- L363 _private member_ `mutable TFuture<FZenCacheStats> CacheStatsRequest;`
- L364 _private member_ `mutable uint64 LastCacheStatsTime = 0;`
- L365 _private member_ `mutable FMutex LastCacheStatsMutex;`
- L366 _private member_ `mutable FZenCacheStats LastCacheStats;`
- L368 _private member_ `mutable TFuture<FZenProjectStats> ProjectStatsRequest;`
- L369 _private member_ `mutable uint64 LastProjectStatsTime = 0;`
- L370 _private member_ `mutable FMutex LastProjectStatsMutex;`
- L371 _private member_ `mutable FZenProjectStats LastProjectStats;`
- L373 _private member_ `mutable TFuture<FZenWorkspaces> WorkspacesRequest;`
- L375 _private member_ `FServiceSettings Settings;`
- L377 _private member_ `FZenServiceEndpoint Endpoint;`
- L378 _private member_ `static uint16 AutoLaunchedPort;`
- L379 _private member_ `static uint32 AutoLaunchedPid;`
- L380 _private member_ `static const uint32 DefaultSmallOperationConnectTimeoutMS;`
- L381 _private member_ `static const uint32 DefaultSmallOperationTimeoutMS;`
- L382 _private member_ `bool bHasLaunchedLocal = false;`
- L383 _private member_ `bool bHasLaunchedSystemService = false;`
- L384 _private member_ `bool bIsRunningLocally = true;`

#### enum `UE::Zen::FZenServiceInstance::ERecoveryMode`  
`enum class ERecoveryMode`  
_L328-332_
- L330 _public enumerator_ `Soft` — Try to recover if we haven't done so recently and be relaxed if it fails
- L331 _public enumerator_ `Hard` — Try to recover always and put more effort and retries to it

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API ZEN_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Zen` (scope `UE`)
- L175 _namespace_ `namespace UE`
- L175 _namespace_ `namespace Zen` (scope `UE`)
- L178 _namespace_ `namespace Private` (scope `UE::Zen`)
- L180 _prototype_ `bool IsLocalAutoLaunched(FStringView InstanceURL);` (scope `UE::Zen::Private`)
- L181 _prototype_ `bool GetLocalDataCachePathOverride(FString& OutDataPath);` (scope `UE::Zen::Private`)
- L189 _prototype_ `FString GetLocalInstallPathOverride();` (scope `UE::Zen::Private`) — For testing purposes only. This is a bit of a hack, to avoid issues in unit tests where we attempt to remove a copied binary when testing install in link mode, or vice versa. During unit tests, we need to run those installations sandboxed to their own install directory so as not to interfere with an actual running zenserver that is being used outside of the unit tests.
- L190 _prototype_ `void SetLocalInstallPathOverride(const FString& Path);` (scope `UE::Zen::Private`)
- L196 _prototype_ `bool TryGetLocalServiceRunContext(FZenLocalServiceRunContext& OutContext);` (scope `UE::Zen`)
- L208 _function_ `friend inline bool operator==(FZenLocalServiceRunContext LHS, FZenLocalServiceRunContext RHS)` (scope `UE::Zen`)
- L231 _prototype_ `bool IsLocalServiceRunning(const TCHAR* DataPath, uint16* OutPort = nullptr);` (scope `UE::Zen`)
- L232 _prototype_ `bool StartLocalService(const FZenLocalServiceRunContext& Context);` (scope `UE::Zen`)
- L233 _prototype_ `bool StopLocalService(const TCHAR* DataPath, double MaximumWaitDurationSeconds = 25.0);` (scope `UE::Zen`)
- L235 _prototype_ `FString GetLocalServiceInstallPath();` (scope `UE::Zen`)
- L236 _prototype_ `FString GetLocalServiceInstallVersion(bool bDetailed = true);` (scope `UE::Zen`)
- L237 _prototype_ `FString GetLocalInstallUtilityPath();` (scope `UE::Zen`)
- L239 _prototype_ `bool GetLocalServiceHostAuth(FString& OutAuthJson);` (scope `UE::Zen`)
- L306 _prototype_ `FZenServiceInstance& GetDefaultServiceInstance();` (scope `UE::Zen`) — Gets the default Zen service instance.  The default instance is configured through ZenServiceInstance INI section. The default instance can (depending on configuration): - Auto-launched on demand (optionally elevated on Windows) - Be copied out of the workspace tree before execution - Shared between multiple tools running concurrently (implemented by launching multiple instances and expecting them to communicate and shutdown as needed) - Instigate self-shutdown when all processes that requested it have terminated - Use a subdirectory of the existing local DDC cache path as Zen's data path - Use an upstream Zen service - Be overridden by commandline arguments to reference an existing running instance instead of auto-launching a new instance. Note that no assumptions should be made about the hostname/port of the default instance.  Calling code should instead expect that the instance is authoritative over the hostname/port that it will end up using and should query that information from the instance as needed.
- L307 _prototype_ `bool IsDefaultServicePresent();` (scope `UE::Zen`)

### `Source/Developer/Zen/Public/Experimental/ZenStatistics.h` (Public)


#### struct `UE::Zen::FZenSizeStats`  
`struct FZenSizeStats`  
_L14-18_
- L16 _public member_ `double Disk = 0;`
- L17 _public member_ `double Memory = 0;`

#### struct `UE::Zen::FZenCIDSizeStats`  
`struct FZenCIDSizeStats`  
_L20-26_
- L22 _public member_ `int64 Tiny = 0;`
- L23 _public member_ `int64 Small = 0;`
- L24 _public member_ `int64 Large = 0;`
- L25 _public member_ `int64 Total = 0;`

#### struct `UE::Zen::FZenCIDStats`  
`struct FZenCIDStats`  
_L28-31_
- L30 _public member_ `FZenCIDSizeStats Size;`

#### struct `UE::Zen::FZenCacheStats`  
`struct FZenCacheStats`  
_L33-85_
- L79 _public member_ `FGeneralStats General;`
- L80 _public member_ `FRequestStats Request;`
- L81 _public member_ `FUpstreamStats Upstream;`
- L82 _public member_ `FRequestStats UpstreamRequest;`
- L83 _public member_ `FZenCIDStats CID;`
- L84 _public member_ `bool bIsValid = false;`

#### struct `UE::Zen::FZenCacheStats::FGeneralStats`  
`struct FGeneralStats`  
_L35-46_
- L37 _public member_ `FZenSizeStats Size;`
- L38 _public member_ `int64 Hits = 0;`
- L39 _public member_ `int64 Misses = 0;`
- L40 _public member_ `int64 Writes = 0;`
- L41 _public member_ `double HitRatio = 0.0;`
- L42 _public member_ `int64 CidHits = 0;`
- L43 _public member_ `int64 CidMisses = 0;`
- L44 _public member_ `int64 CidWrites = 0;`
- L45 _public member_ `int64 BadRequestCount = 0;`

#### struct `UE::Zen::FZenCacheStats::FRequestStats`  
`struct FRequestStats`  
_L48-55_
- L50 _public member_ `int64 Count = 0;`
- L51 _public member_ `double RateMean = 0.0;`
- L52 _public member_ `double TAverage = 0.0;`
- L53 _public member_ `double TMin = 0.0;`
- L54 _public member_ `double TMax = 0.0;`

#### struct `UE::Zen::FZenCacheStats::FEndPointStats`  
`struct FEndPointStats`  
_L57-66_
- L59 _public member_ `FString Name;`
- L60 _public member_ `FString Url;`
- L61 _public member_ `FString Health;`
- L62 _public member_ `double HitRatio = 0.0;`
- L63 _public member_ `double DownloadedMB = 0;`
- L64 _public member_ `double UploadedMB = 0;`
- L65 _public member_ `int64 ErrorCount = 0;`

#### struct `UE::Zen::FZenCacheStats::FUpstreamStats`  
`struct FUpstreamStats`  
_L68-77_
- L70 _public member_ `bool Reading = false;`
- L71 _public member_ `bool Writing = false;`
- L72 _public member_ `int64 WorkerThreads = 0;`
- L73 _public member_ `int64 QueueCount = 0;`
- L74 _public member_ `double TotalUploadedMB = 0;`
- L75 _public member_ `double TotalDownloadedMB = 0;`
- L76 _public member_ `TArray<FEndPointStats> EndPoint;`

#### struct `UE::Zen::FZenProjectStats`  
`struct FZenProjectStats`  
_L87-114_
- L111 _public member_ `FGeneralStats General;`
- L112 _public member_ `FZenCIDStats CID;`
- L113 _public member_ `bool bIsValid = false;`

#### struct `UE::Zen::FZenProjectStats::FReadWriteDeleteStats`  
`struct FReadWriteDeleteStats`  
_L89-94_
- L91 _public member_ `int64 ReadCount;`
- L92 _public member_ `int64 WriteCount;`
- L93 _public member_ `int64 DeleteCount;`

#### struct `UE::Zen::FZenProjectStats::FHitMissWriteStats`  
`struct FHitMissWriteStats`  
_L95-100_
- L97 _public member_ `int64 HitCount;`
- L98 _public member_ `int64 MissCount;`
- L99 _public member_ `int64 WriteCount;`

#### struct `UE::Zen::FZenProjectStats::FGeneralStats`  
`struct FGeneralStats`  
_L101-110_
- L103 _public member_ `FZenSizeStats Size;`
- L104 _public member_ `FReadWriteDeleteStats Project;`
- L105 _public member_ `FReadWriteDeleteStats Oplog;`
- L106 _public member_ `FHitMissWriteStats Op;`
- L107 _public member_ `FHitMissWriteStats Chunk;`
- L108 _public member_ `int64 RequestCount;`
- L109 _public member_ `int64 BadRequestCount;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ZEN_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Zen` (scope `UE`)
- L116 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenSizeStats& OutValue);` (scope `UE::Zen`)
- L117 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenCIDSizeStats& OutValue);` (scope `UE::Zen`)
- L118 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenCIDStats& OutValue);` (scope `UE::Zen`)
- L120 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenCacheStats::FGeneralStats& OutValue);` (scope `UE::Zen`)
- L121 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenCacheStats::FRequestStats& OutValue);` (scope `UE::Zen`)
- L122 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenCacheStats::FEndPointStats& OutValue);` (scope `UE::Zen`)
- L123 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenCacheStats::FUpstreamStats& OutValue);` (scope `UE::Zen`)
- L124 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenCacheStats& OutValue);` (scope `UE::Zen`)
- L126 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenProjectStats::FReadWriteDeleteStats& OutValue);` (scope `UE::Zen`)
- L127 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenProjectStats::FHitMissWriteStats& OutValue);` (scope `UE::Zen`)
- L128 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenProjectStats::FGeneralStats& OutValue);` (scope `UE::Zen`)
- L129 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FZenProjectStats& OutValue);` (scope `UE::Zen`)
